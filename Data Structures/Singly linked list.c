#include<stdio.h>
#include<stdlib.h>

// 链表结构体
typedef struct linked_list
{
	int a;
	struct linked_list *next;
}linked_list;

// 创建链表
linked_list *create_linked_list()
{
	linked_list *head = (linked_list *)malloc(sizeof(linked_list));
	head->next = NULL;
	return head;
}

// 遍历获取长度
int get_linked_list_length(linked_list *head)
{
	linked_list *p = head;
	int count = 0;
	while(p->next != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}

// 获取末节点
linked_list *get_linked_list_tail(linked_list *head)
{
	linked_list *p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

// 添加元素(头插法)
void add_linked_list_head(linked_list *head, int a)
{
	linked_list *p = (linked_list *)malloc(sizeof(linked_list));
	p->a = a;
	p->next = head->next;
	head->next = p;
}

// 添加元素(尾插法)
linked_list *add_linked_list_tail(linked_list *head, int a)
{
	linked_list *q = (linked_list *)malloc(sizeof(linked_list));
	q->a = a;
	q->next = NULL;
	head->next = q;
	return q;
}

// 展示链表
void show_linked_list(linked_list *head)
{
	linked_list *p = head;
	while(p->next != NULL)
	{
		p = p->next;
		printf("%d ", p->a);
	}
}

// 删除第n个元素
void delete_linked_list_n(linked_list *head, int n)
{
	linked_list *p = head,*q=head;
	for(int i=0;i<n;i++){
		p = p->next;
	}
	for(int i=0;i<n-1;i++){
		q = q->next;
	}
	q->next = p->next;
	q=NULL;
	free(q);
	free(p);
}

// 删除指定元素
void delete_linked_list_search(linked_list *head, int a)
{
	linked_list *p = head,*q=head;
	while(p->next != NULL)
	{
		if(p->next->a == a)
		{
			q = p->next;
			p->next = q->next;
			q=NULL;
			free(q);
			break;
		}
		p = p->next;
	}
}

// 反向链表
void reverse_linked_list(linked_list *head){
	linked_list *first=head,*second=head->next,*third=head->next->next;
	while(third != NULL)
	{
		second->next = first;
		first = second;
		second = third;
		third = third->next;
	}
	second->next = first;
	head->next->next = NULL;
	head->next = second;                                                                                                                                                                                                                                                                                     
}
int main()
{
	linked_list *head = create_linked_list(),*q=head;
	q=add_linked_list_tail(q, 1);
	q=add_linked_list_tail(q, 2);
	q=add_linked_list_tail(q, 3);
	q=add_linked_list_tail(q, 4);
    q=NULL;
	free(q);
	show_linked_list(head);
	printf("\n");
	reverse_linked_list(head);
	show_linked_list(head);
	printf("\n");
	return 0;
}