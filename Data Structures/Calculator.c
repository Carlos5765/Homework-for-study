//��׺���ʽת��׺���ʽ��
//��������ֱ��������������ţ����������ȼ������ջ��������ȼ�����ջ�����ţ���ջ�������ջ��
//���ջ��������ȼ�С�ڵ���ջ�����ţ���ջ�����ų�ջ�����ѵ�ǰ������ջ��
//��������ջ����������ȼ�����ջ����������ȼ�
//���������ţ���ջ�����ų�ջ��ֱ��������Ϊֹ

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100
//����ջ����
typedef struct Stack{
    char data[MAX_SIZE];
    int top;
}stack;

//�������Ͷ���
typedef enum Operation_Type{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EMPTY
}Operation_Type;

//������ʽת��
char *Expression_Transformation(char *infix_expression);
//�������ȼ�����
int Operation_Priority(char operation);
//����
int Calculate(char *postfix_expression);
//�������ͻ���
Operation_Type Operation_Type_Division(char operation);

int main(){
    char *arithmetic_expression=(char *)malloc(sizeof(char)*MAX_SIZE);
    printf("������һ����׺���ʽ��\n");
    scanf("%s",arithmetic_expression);
    getchar();
    arithmetic_expression=Expression_Transformation(arithmetic_expression);
    // printf("ת����ĺ�׺���ʽΪ��%s\n",arithmetic_expression);
    printf("������Ϊ��%d\n",Calculate(arithmetic_expression));
    return 0;
}

//�������ȼ�����
int Operation_Priority(char operation){
    if(operation=='+'||operation=='-')
        return 1;
    else if(operation=='*'||operation=='/')
        return 2;
    else if(operation=='(')
        return 3;
    else if(operation==')')
        return 4;
    else
        return -1;
}

//������ʽת��
char *Expression_Transformation(char *infix_expression){
    char *postfix_expression=(char *)malloc(sizeof(char)*MAX_SIZE);
    stack symbol_stack;
    symbol_stack.top=-1;
    for(int i=0,n=0;infix_expression[i]!='\0';i++){
        if(Operation_Priority(infix_expression[i])==-1)
            postfix_expression[n++]=infix_expression[i];
        else{
            if(Operation_Priority(infix_expression[i])==4){
                while(symbol_stack.data[symbol_stack.top]!='('){
                    postfix_expression[n++]=symbol_stack.data[symbol_stack.top--];
                }
                symbol_stack.top--;
            }
            else if(symbol_stack.top==-1||symbol_stack.data[symbol_stack.top]=='('||Operation_Priority(infix_expression[i])>Operation_Priority(symbol_stack.data[symbol_stack.top])){
                symbol_stack.data[++symbol_stack.top]=infix_expression[i];
            }
            else if(Operation_Priority(symbol_stack.data[symbol_stack.top])!=3&&Operation_Priority(infix_expression[i])<=Operation_Priority(symbol_stack.data[symbol_stack.top])){
                postfix_expression[n++]=symbol_stack.data[symbol_stack.top--];
                symbol_stack.data[++symbol_stack.top]=infix_expression[i];
            }
        }
        if(infix_expression[i+1]=='\0'){
            while(symbol_stack.top!=-1){
                postfix_expression[n++]=symbol_stack.data[symbol_stack.top--];
            }
            postfix_expression[n]='\0';
        }
        // for(int q=0;q<=n;q++){
        //     printf("%c",postfix_expression[q]);
        // }
        // printf("\n");
    }
    free(infix_expression);
    return postfix_expression;
}

//�������ͻ���
Operation_Type Operation_Type_Division(char operation){ 
    switch(operation){
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        default:
            return EMPTY;
    }
}

//����
int Calculate(char *postfix_expression){
    int str_size=strlen(postfix_expression);
    stack number_stack;
    number_stack.top=-1;
    for(int i=0;i<str_size;i++){
        if(postfix_expression[i]>='0'&&postfix_expression[i]<='9'){
            number_stack.data[++number_stack.top]=postfix_expression[i]-'0';
        }
        else{
            switch(Operation_Type_Division(postfix_expression[i])){
                case PLUS:
                    number_stack.data[number_stack.top-1]+=number_stack.data[number_stack.top];
                    number_stack.top--;
                    break;
                case MINUS:
                    number_stack.data[number_stack.top-1]-=number_stack.data[number_stack.top];
                    number_stack.top--;
                    break;
                case MULTIPLY:
                    number_stack.data[number_stack.top-1]*=number_stack.data[number_stack.top];
                    number_stack.top--;
                    break;
                case DIVIDE:
                    number_stack.data[number_stack.top-1]/=number_stack.data[number_stack.top];
                    number_stack.top--;
                    break;
                case EMPTY:
                    break;
            }
        }
    }
    return number_stack.data[number_stack.top];
}