#include<stdio.h>
#include<stdlib.h>

typedef struct Linked_List{
    int data;
    struct Linked_List *next;
}Linked_List;

Linked_List *Construct_Linked_List(int num){
    Linked_List *head=(Linked_List*)malloc(sizeof(Linked_List)),*p=head,*q;
    int i;
    for(i=1;i<=num;i++){
        q=(Linked_List*)malloc(sizeof(Linked_List));
        q->data=i;
        p->next=q;
        p=p->next;
    }
    
    // p->next=NULL;
    // Show_Linked_List(head);
    // printf("\n");
    
    p->next=head->next;
    head->data=i-1;
    return head;
}

void Recursive_Linked_List(Linked_List *head,int num){
    if(head->data==1){
        head->next->next=NULL;
    }
    else{
        Linked_List *p=head,*h=head;
        int number=head->data;
        while(p->next!=p){
            int time=num%number-1;
            if(time==-1){
                time+=number;
            }
            for(int n=0;n<time;n++){
                p=p->next;
            }
            Linked_List *r=p->next;
            p->next=r->next;
            h->next=r;
            h=h->next;
            number--;
        }
        h->next=p;
        p->next=NULL;
    }
}

void Show_Linked_List(Linked_List *head){
    Linked_List *p=head->next;
    while(p!=NULL){
        printf("%d",p->data);
        if(p->next!=NULL){
            printf(" ");
        }
        p=p->next;
    }
    printf("\n");
}

int main(){
    int N,p;
    scanf("%d %d\n",&N,&p);
    Linked_List *head=Construct_Linked_List(N);
    Recursive_Linked_List(head,p);
    Show_Linked_List(head);
    return 0;
}