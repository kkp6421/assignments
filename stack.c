#include<stdio.h>
#include<stdlib.h>

typedef struct cell{
    int item;
    struct cell *next;
}cell_t;

cell_t *lalloc(void){
    return ((cell_t *) malloc(sizeof(cell_t)));
}

cell_t *push(int x, cell_t *top){
    cell_t *p;
    p = lalloc();
    p->item = x;
    p->next = top;
    printf("%dを追加しました。\n", p->item);
    return (p);
}

cell_t *pop(cell_t *top){
    int x;
    if(top!=NULL){
        x = top->item;
        top = top->next;
        printf("データ: %d を取り出しました。\n", x);
    }else{
        printf("このスタックは空です\n");
    }
    return (top);
}

cell_t *show(cell_t *top){
    if(top==NULL){
        printf("]\n");
        return (top);
    }else{
        printf("%d, ", top->item);
        return (show(top->next));
    }
}

int main(void){
    cell_t *p_ = NULL;
    char msg;
    int num, k;
    while(1){
        scanf("%c%*c", &msg);
        if(msg=='i'){
            printf("入力したい整数をどうぞ。");
            scanf("%d%*c", &num);
            p_ = push(num, p_);
        }else if(msg=='d'){
            p_ = pop(p_);
            continue;
        }else if(msg=='m'){
            printf("削除したデータの個数をどうぞ。");
            scanf("%d%*c", &k);
            for(int i=0; i<k; i++){
                if (p_==NULL){
                    printf("このスタックは空です。\n");
                    break;
                }else{
                    printf("%d 個目: ", i+1);
                    p_ = pop(p_);
                }
            }
        }else if(msg=='p'){
            cell_t *_ = NULL;
            printf("[");
            _ = show(p_);
        }else if(msg=='q'){
            printf("動作を終了します。\n");
            break;
        }else{
            puts("i, d, m, p, qのいずれかを入力してください。");
        }
    }
    return 0;
}