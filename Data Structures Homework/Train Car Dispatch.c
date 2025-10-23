#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack{
    int top;
    char order[26];
}stack;

int main(){
    stack st1,st2,st3;
    st3.top=-1;
    scanf("%s\n%s",st1.order,st2.order);
    st1.top=strlen(st1.order)-1;
    st2.top=st1.top;
    int path[100][2],record=-1,top1=0,top2=0;
    while(1){
        if(st1.order[top1]==st2.order[top2]){
            record++;
            path[record][0]=1;
            path[record][1]=2;
            top1++;
            top2++;
        }
        else if(st3.top!=-1&&st3.order[st3.top]==st2.order[top2]){
            record++;
            path[record][0]=3;
            path[record][1]=2;
            top2++;
            st3.top--;
        }
        else{
            st3.top++;
            st3.order[st3.top]=st1.order[top1];
            top1++;
            record++;
            path[record][0]=1;
            path[record][1]=3;
        }
        if(top1>st1.top){
            break;
        }
    }
    for(;st3.top>=0;st3.top--,top2++){
        if(st3.order[st3.top]==st2.order[top2]){
            record++;
            path[record][0]=3;
            path[record][1]=2;
        }
        else{
            printf("Are you kidding me?");
            return 0;
        }
    }
    for(int i=0;i<=record;i++){
        printf("%d->%d\n",path[i][0],path[i][1]);
    }
    return 0;
}