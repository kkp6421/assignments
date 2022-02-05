
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1

typedef struct node {
    int num;
    struct node *left;
    struct node *right;
} node_t;

node_t *root;

void search(int num, node_t *root){
    if (root==NULL){
        printf("二分探索木に整数%dは存在しません。\n", num);
    }else if(root->num == num){
        printf("二分探索木に単語%dは存在します。\n", num);
    }else{
        if(num < root->num){
            search(num, root->left);
        }else{
            search(num, root->right);
        }
    }
}

node_t *talloc(void){
    return ((node_t *) malloc(sizeof(node_t)));
}

node_t *insert(int num, node_t *root){
    if (root == NULL){
        root = talloc();
        root->num = num;
        root->left = NULL;
        root->right = NULL;
    }else if(num == root->num){
        printf("整数%dはすでに挿入されています。\n", num);
    }else{
        if(num < root->num){
            root->left = insert(num, root->left);
        }else{
            root->right = insert(num, root->right);
        }
    }
    return(root);
}

char childeren_type(node_t *ptr){
    if(ptr->left == NULL){
        if(ptr->right == NULL){
            return('n');
        }else{
            return('r');
        }
    }else if(ptr->right==NULL){
        return('l');
    }else{
        return('b');
    }
}

node_t *delete_node(node_t *ptr){
    char c;
    node_t *p, *parent_of_p;
    c = childeren_type(ptr);
    //printf("%c\n", c);
    if(c=='n'){
        ptr = NULL;
    }else if (c=='r'){
        p = ptr->right;
        parent_of_p = p;
        while(p->left != NULL){
            parent_of_p = p;
            p = p->left;
        }
        ptr->num = p->num;
        free(p);
    }else{
        p = ptr->left;
        fprintf(stderr, "free(p) = %p\n", p);
        parent_of_p = p;
        while(p->right != NULL){
            parent_of_p = p;
            p = p->right;
            fprintf(stderr, "free(p) = %p\n", p);
        }
        ptr->num = p->num;
        fprintf(stderr, "free(p) = %p\n", p);
    }
    return(ptr);
}

node_t *delete_item(int num, node_t *root){
    if(root==NULL){
        printf("データ%dは二分探索木に存在しません。\n", num);
    }else if(num == root->num){
        root = delete_node(root);
    }else if(num < root->num){
        root->left = delete_item(num, root->left);
    }else{
        root->right = delete_item(num, root->right);
    }
    return (root);
}

void print_inorder(node_t *root){
    if(root!=NULL){
        print_inorder(root->left);
        printf("%d\n", root->num);
        print_inorder(root->right);
    }
}

int main(void){
    char c;
    int num;
    root = NULL;

    while(TRUE){
        printf(">");
        scanf("%1s", &c);
        switch(c){
            case 's':
                scanf("%d", &num);
                search(num, root);
                break;
            case 'i':
                scanf("%d", &num);
                root = insert(num, root);
                break;
            case 'd':
                scanf("%d", &num);
                root = delete_item(num, root);
                break;
            case 'p':
                print_inorder(root);
                break;
            case 'q':
                exit(0);
            default:
                printf("s, i, d, p, またはqを入力してください。\n");
        }
    }
    return 0;
}