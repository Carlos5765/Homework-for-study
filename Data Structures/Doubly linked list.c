#include<stdio.h>
#include<stdlib.h>

// 创建双向链表节点
typedef struct node{
	int data;
	struct node *next;
	struct node *prev;
}node;

// 头插法
void insert_head(node *head,int x){
	node *p=(node *)malloc(sizeof(node));
	p->data=x;
	p->next=head->next;
	p->prev=head;
	head->next=p;
	if(p->next!=NULL)
		p->next->prev=p;
}

void show(node *head){ 
    node *p=head->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
int main(){ 
    node *head=(node *)malloc(sizeof(node));
    head->next=NULL;
    insert_head(head,1);
    insert_head(head,2);
    insert_head(head,3);
    insert_head(head,4);
    show(head);
    return 0;
}