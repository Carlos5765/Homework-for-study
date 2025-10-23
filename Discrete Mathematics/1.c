#include<stdio.h>
#include <stdlib.h>

void clear_stdin() {
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}

void Main_menu(){
    printf("1.计算真值 2.计算命题公式真值表 0.退出\n");
}

int Negative_proposition(int a){
    return !a;
}

int Conjunctive_proposition(int a,int b){
    return a&&b;
}

int Disjunctive_proposition(int a,int b){
    return a||b;
}

int Conditional_proposition(int a,int b){
    return !a||b;
}

int Double_conditional_proposition(int a,int b){
    return (a&&b)||(!a&&!b);
}

void Atomic_propositional_operations(){
    int P,Q;
    printf("输入P的真值\n");
    scanf("%d",&P);
    clear_stdin();
    printf("输入Q的真值\n");
    scanf("%d",&Q);
    clear_stdin();
    printf("否P的真值为%d\n",Negative_proposition(P));
    printf("P合取Q的真值为%d\n",Conjunctive_proposition(P,Q));
    printf("P析取Q的真值为%d\n",Disjunctive_proposition(P,Q));
    printf("P条件Q的真值为%d\n",Conditional_proposition(P,Q));
    printf("P双条件Q的真值为%d\n",Double_conditional_proposition(P,Q));
    system("pause");
}

void Proposition_formula_calculation(){
    char formula[100];
    printf("请输入公式（！为否定，&为合取，|为析取，-为条件，@为双条件）（不可带有括号）\n");
    scanf("%s",formula);
    clear_stdin();
    char yunsuanfu[51],bianyuan[51],bianyuanshunxu[51];
    int yunnum=0,biannum=0,shunxu=0;
    for(int n=0;formula[n]!='\0';n++){
        if((formula[n]>='A'&&formula[n]<='Z')||(formula[n]>='a'&&formula[n]<='z')){
            bianyuanshunxu[shunxu]=formula[n];
            shunxu++;
            if(biannum==0){
                bianyuan[0]=formula[n];
                biannum++;
                continue;
            }
            for(int k=0;k<biannum;k++){
                if(bianyuan[k]==formula[n])
                break;
                else if(k==biannum-1){
                    bianyuan[biannum]=formula[n];
                    biannum++;
                    break;
                }
            }
        }
        else if(formula[n]=='!'||formula[n]=='&'||formula[n]=='|'||formula[n]=='-'||formula[n]=='@'){
            yunsuanfu[yunnum]=formula[n];
            yunnum++;
        }
    }

    bianyuanshunxu[shunxu]='\0';
    bianyuan[biannum]='\0';
    yunsuanfu[yunnum]='\0';
    
    int total=1<<biannum;
    int zhenzhibiao[total][biannum];
    for (int i = 0; i < total; i++){
        for (int j = 0; j < biannum; j++){
            zhenzhibiao[i][j]=(i >> j) & 1;
        }
    }

    for(int n=0;n<biannum;n++){
        printf("%c ",bianyuan[n]);
    }
    printf("%s\n",formula);
    int fuzhi[shunxu],cengshu=0;

    while(1){
        int fuhao[yunnum];
        for(int n=0;n<yunnum;n++){
            fuhao[n]=yunsuanfu[n];
        }
        int bbb=shunxu,yyy=yunnum;
        if(cengshu==total)
        break;
        for(int n=0;n<shunxu;n++){
            for(int i=0;i<biannum;i++){
                if(bianyuan[i]==bianyuanshunxu[n]){
                    fuzhi[n]=zhenzhibiao[cengshu][i];
                }
            }
        }

        fuzhi[0]=1,fuzhi[3]=1;

        for(int n=0;n<biannum;n++){
            printf("%d ",zhenzhibiao[cengshu][n]);
        }

        cengshu++;

        for(int n=0;n<yyy;n++){
            if(fuhao[n]=='!'){
                if(fuzhi[n]==0){
                    fuzhi[n]=1;
                }
                else{
                    fuzhi[n]=0;
                }
                for(int k=n;k<yyy-1;k++){
                    fuhao[k]=fuhao[k+1];
                }
                yyy--;
                fuhao[yyy]='\0';
                n--;
            }
        }

        for(int n=0;n<yyy;n++){
            if(fuhao[n]=='&'){
                fuzhi[n]=Conjunctive_proposition(fuzhi[n],fuzhi[n+1]);

                int k;
                for(k=n+1;k<bbb-1;k++){
                    fuzhi[k]=fuzhi[k+1];
                }
                if(k==bbb-1)
                    fuzhi[k+1]='\0';
                bbb--;
                for(int k=n;k<yyy-1;k++){
                    fuhao[k]=fuhao[k+1];
                }
                yyy--;
                fuhao[k+1]='\0';
                n--;
            }

        }

        for(int n=0;n<yyy;n++){///////
            if(fuhao[n]=='|'){
                fuzhi[n]=Disjunctive_proposition(fuzhi[n],fuzhi[n+1]);

                int k;
                for(k=n+1;k<bbb-1;k++){
                    fuzhi[k]=fuzhi[k+1];
                }
                if(k==bbb-1)
                    fuzhi[k+1]='\0';
                bbb--;
                for(int k=n;k<yyy-1;k++){
                    fuhao[k]=fuhao[k+1];
                }
                yyy--;
                fuhao[k+1]='\0';
                n--;
            }
        }

        for(int n=0;n<yyy;n++){
            if(fuhao[n]=='-'){
                fuzhi[n]=Conditional_proposition(fuzhi[n],fuzhi[n+1]);
                int k;
                for(k=n+1;k<bbb-1;k++){
                    fuzhi[k]=fuzhi[k+1];
                }
                if(k==bbb-1)
                    fuzhi[k+1]='\0';
                bbb--;
                for(int k=n;k<yyy-1;k++){
                    fuhao[k]=fuhao[k+1];
                }
                yyy--;
                fuhao[k+1]='\0';
                n--;
            }
        }

        for(int n=0;n<yyy;n++){
            if(fuhao[n]=='@'){
                fuzhi[n]=Double_conditional_proposition(fuzhi[n],fuzhi[n+1]);
                int k;
                for(k=n+1;k<bbb-1;k++){
                    fuzhi[k]=fuzhi[k+1];
                }
                if(k==bbb-1)
                    fuzhi[k+1]='\0';
                bbb--;
                for(int k=n;k<yyy-1;k++){
                    fuhao[k]=fuhao[k+1];
                }
                yyy--;
                fuhao[k+1]='\0';
                n--;
            }
        }

        printf("%d\n",fuzhi[0]);
    }
    system("pause");
}

int Menu_jumper(){
    int jump;
    scanf("%d",&jump);
    clear_stdin();
    switch (jump) {
        case 1:
        Atomic_propositional_operations();
        return 1;
        break;
        case 2:
        Proposition_formula_calculation();
        return 1;
        break;
        case 0:
        return 0;
        break;
        default:
        return 1;
        break;
    }
}

int main(){
    int control=1;
    while(control){
        system("cls");
        Main_menu();
        control=Menu_jumper();
    }
    return 0;
}