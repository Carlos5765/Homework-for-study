#include<stdio.h>
#include<stdlib.h>

// ����ṹ��
typedef struct linked_list
{
	int a;
	struct linked_list *next;
}linked_list;

// ��������
linked_list *create_linked_list()
{
	linked_list *head = (linked_list *)malloc(sizeof(linked_list));
	head->next = NULL;
	return head;
}

// ������ȡ����
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

// ��ȡĩ�ڵ�
linked_list *get_linked_list_tail(linked_list *head)
{
	linked_list *p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

// ���Ԫ��(ͷ�巨)
void add_linked_list_head(linked_list *head, int a)
{
	linked_list *p = (linked_list *)malloc(sizeof(linked_list));
	p->a = a;
	p->next = head->next;
	head->next = p;
}

// ���Ԫ��(β�巨)
linked_list *add_linked_list_tail(linked_list *head, int a)
{
	linked_list *q = (linked_list *)malloc(sizeof(linked_list));
	q->a = a;
	q->next = NULL;
	head->next = q;
	return q;
}

// չʾ����
void show_linked_list(linked_list *head)
{
	linked_list *p = head;
	while(p->next != NULL)
	{
		p = p->next;
		printf("%d ", p->a);
	}
}

// ɾ����n��Ԫ��
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

// ɾ��ָ��Ԫ��
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

// ��������
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