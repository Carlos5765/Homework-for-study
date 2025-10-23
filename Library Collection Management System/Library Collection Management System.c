#include"Library.h"

int main(){
    int controller=1,translater;
    while(controller){
        system("cls");
        Menu();
        scanf("%d",&translater);
        controller=Menu_Jump(translater);
    }
    return 0;
}

void Clear_The_Buffer(){
    while (getchar()!= '\n') {//��������
    continue;
    }
}

void Menu(){//�ڳ���ʼ����ʱ����ӡ�˵�
    printf("--------------------------------\n|      ͼ��ݲ������ϵͳ      |\n|  (���¶�Ӧ�������ö�Ӧ����)  |\n|------------------------------|\n|1.¼���鼮��Ϣ  2.����鼮��Ϣ|\n|------------------------------|\n|3.�����鼮��Ϣ  4.�����鼮��Ϣ|\n|------------------------------|\n|5.����ͼ��Ǽ�  6.�黹ͼ��Ǽ�|\n|------------------------------|\n|7.�鿴�����¼  8.��������Ϣ|\n|------------------------------|\n|        0.�رչ���ϵͳ        |\n--------------------------------\n");
}

int Menu_Jump(int translater){//�ɳ���˵�������ģ�����ת
    switch(translater){
        case 1:
            system("cls");
            printf("�ԡ�ͼ�����ͣ���д��ĸ�� ���� ���� �������� 1/0����ʽ���������Ϣ��ÿ��ĩβ����1����֮��������룬����0�����ز˵����û��س��������\n");
            Information_Input();
            return 1;
            break;
        case 2:
            system("cls");
            printf("����ͼ�����ͣ���д��ĸ���鿴��Ӧ�����鼮��Ϣ\n����1�鿴���в�����Ϣ\n��0�������˵�\n");
            Information_Browsing();
            return 1;
            break;
        case 3:
            system("cls");
            printf("����ͼ�����ͣ���д��ĸ�� �����޸ĸ��������Ϣ �޷��޸�ͼ������\n��0�������˵�\n");
            Information_Update();
            return 1;
            break;
        case 4:
            system("cls");
            Information_Lookup();
            return 1;
            break;
        case 5:
            system("cls");
            printf("����ͼ�����ͣ���д��ĸ�� ���� �����������ɵǼ�\n��0�������˵�\n");
            Book_Borrowing();
            return 1;
            break;
        case 6:
            system("cls");
            printf("����ͼ�����ͣ���д��ĸ�� ���� �����������ɵǼ�\n��0�������˵�\n");
            Book_Returning();
            return 1;
            break;
        case 7:
            system("cls");
            printf("��������������Ҹö��ߵĽ����¼\n��1������н����¼\n");
            Borrowing_History();
            return 1;
            break;
        case 8:
            system("cls");
            printf("��������������Ҹö���Ŀǰ�������鼮\n��1������н����Ϣ\n");
            User_Searching();
            return 1;
            break;
        case 0:
            return 0;
            break;
        default:
            printf("����������������ȷ�����֣�\n");
            return 1;
            break;
    }
}

void Type_Code_Tips(){//��ʾͼ�������Ϣ
    printf("\n�й�ͼ����෨��\nA ���˼���� �������� ë��˼�� ��Сƽ����\nB ��ѧ �ڽ�\nC ����ѧ����\nD ���� ����\nE ����\nF ����\nG �Ļ� ��ѧ ���� ����\nH ���� ����\nI ��ѧ\nJ ����\nK ��ʷ ����\nN ��Ȼ��ѧ����\nO �����ѧ�ͻ�ѧ\nP ����ѧ �����ѧ\nQ �����ѧ\nR ҽҩ ����\nS ũҵ��ѧ\nT ��ҵ����\nU ��ͨ����\nV ���� ����\nX ������ѧ ��ȫ��ѧ\nZ �ۺ���ͼ��\n");
}

void Information_Input(){//���ı��ĵ��������鼮��Ϣ
    Type_Code_Tips();
    printf("\n");
    int translater=1,trans;
    while(translater){
        Book_Information input;
        input.borrowing_time=0;
        input.borrowing_number=0;
        Clear_The_Buffer();
        scanf("%c %s %s %d %d",&input.type,input.name,input.auther,&input.number,&trans);
        if(input.type=='L'||input.type=='M'||input.type=='W'||input.type=='Y'||input.type<'A'||input.type>'Z'){
            printf("����������������ȷ�Ĵ�д��ĸͼ�������\n");
            continue;
        }
        else{
            char filename[6];
            sprintf(filename,"%c.txt",input.type);
            FILE *fp=fopen(filename,"a"),*p=fopen("all.txt","a");
            fprintf(fp,"%c %s %s %d %d %d\n",input.type,input.name,input.auther,input.number,input.borrowing_number,input.borrowing_time);
            fprintf(p,"%c %s %s %d %d %d\n",input.type,input.name,input.auther,input.number,input.borrowing_number,input.borrowing_time);
            fclose(fp);
            fclose(p);
            printf("¼����Ϣ�ɹ�\n");
            if(trans==0){
                translater=0;
                system("pause");
            }
        }
    }
}

void Information_Browsing(){
    Type_Code_Tips();
    Clear_The_Buffer();
    printf("\n");
    char translater;
    scanf("%c",&translater);
    if(translater=='0');
    else if(translater=='1'){
        system("cls");
        FILE *fp=fopen("all.txt","r");
        if(fp==NULL){
            printf("���ļ�ʧ�ܣ����������˵���\n");
            fclose(fp);
            system("pause");
        }
        else{
            system("cls");
            Clear_The_Buffer();
            printf("���������Զ�Ӧ��ʽ����\n1.��Ĭ��˳������  2.��������������\n3.�������ȶ�����  4.�������������\n��0�˻����˵�\n");
            int sorted;
            scanf("%d",&sorted);
            switch (sorted){
                case 1:
                    Default_Sorting(fp);
                    break;
                case 2:
                    Quantity_Sorting(fp,"all.txt");
                    break;
                case 3:
                    Heat_Sorting(fp,"all.txt");
                    break;
                case 4:
                    Loan_Sorting(fp,"all.txt");
                    break;
                case 0:
                    break;
            }
        }
    }
    else if((translater>='A'&&translater<='K')||(translater>='N'&&translater<='V')||translater=='X'||translater=='Z'){
        system("cls");
        char filename[6];
        sprintf(filename,"%c.txt",translater);
        FILE *fp=fopen(filename,"r");
        if(fp==NULL){
            printf("���ļ�ʧ�ܣ����������˵���\n");
            fclose(fp);
            system("pause");
        }
        else{
            system("cls");
            Clear_The_Buffer();
            printf("���������Զ�Ӧ��ʽ����\n1.��Ĭ��˳������  2.��������������\n3.�������ȶ�����  4.�������������\n");
            int sorted;
            scanf("%d",&sorted);
            switch (sorted){
                case 1:
                    Default_Sorting(fp);
                    break;
                case 2:
                    Quantity_Sorting(fp,filename);
                    break;
                case 3:
                    Heat_Sorting(fp,filename);
                    break;
                case 4:
                    Loan_Sorting(fp,filename);
                    break;
            }
        }
    }
    else{
        system("cls");
        printf("������󣡽��������˵���\n");
        system("pause");
    }
}

void Default_Sorting(FILE *fp){
    Book_Information book;
    system("cls");
    while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
        printf("%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
    }
    fclose(fp);
    system("pause");
}

void Quantity_Sorting(FILE *fp,char *name){
    int number=0;
    Book_Information book;
    while(fscanf(fp,"%*c %*s %*s %d %*d %*d\n",&book.number)==1){
        if(book.number>number){
            number=book.number;
        }
    }
    fclose(fp);
    for(int i=number;i>0;i--){
        FILE *fp=fopen(name,"r");
        while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
            if(book.number==i){
                printf("%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
            }
        }
        fclose(fp);
    }
    system("pause");
}

void Heat_Sorting(FILE *fp,char *name){
    int time=0;
    Book_Information book;
    while(fscanf(fp,"%*c %*s %*s %*d %*d %d\n",&book.borrowing_time)==1){
        if(book.borrowing_time>time){
            time=book.borrowing_time;
        }
    }
    fclose(fp);
    for(int i=time;i>0;i--){
        FILE *fp=fopen(name,"r");
        while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
            if(book.borrowing_time==i){
                printf("%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
            }
        }
        fclose(fp);
    }
    system("pause");
}

void Loan_Sorting(FILE *fp,char *name){
    int borrow;
    Book_Information book;
    while(fscanf(fp,"%*c %*s %*s %*d %d %*d\n",&book.borrowing_number)==1){
        if(book.borrowing_number>borrow){
            borrow=book.borrowing_number;
        }
    }
    fclose(fp);
    for(int i=borrow;i>0;i--){
        FILE *fp=fopen(name,"r");
        while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
            if(book.borrowing_number==i){
                printf("%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
            }
        }
        fclose(fp);
    }
    system("pause");
}

void Information_Update(){
    while(1){
        system("cls");
        printf("����1�޸��鼮��Ϣ ����2ɾ����Ϣ ����0�˻����˵�\n");
        printf("\n");
        Clear_The_Buffer();
        int trans;
        scanf("%d",&trans);
        if(!trans){
            break;
        }
        else if(trans==1){
            Information_Change();
        }
        else if(trans==2){
            Information_Deletion();
        }
        else{
            printf("�������ִ���������\n");
        }
    }
}

void Information_Change(){
    system("cls");
    printf("�������鼮���ͣ���д��ĸ�����������ո������������0 0������һҳ\n");
    Type_Code_Tips();
    printf("\n");
    while(1){
        char type,name[21],filename[6],temp_filename[11];
        int judge=1;
        fflush(stdin);
        scanf("%c %s",&type,name);
        if(type=='0'&&!strcmp(name,"0")){
            break;
        }
        else if(type=='L'||type=='M'||type=='W'||type=='Y'||type<'A'||type>'Z'){
            printf("����������������ȷ��ͼ�����ͣ���д��ĸ�� ��������޸��밴��ʽ��������\n");
        }
        else{
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            Book_Information book,temp_book;
            FILE *fp1=fopen(filename,"r"),*fp2=fopen("all.txt","r"),*temp_fp1=fopen(temp_filename,"w"),*temp_fp2=fopen("temp_all.txt","w");
            if(fp1==NULL||fp2==NULL){
                printf("���ļ�ʧ�ܣ�\n");
                continue;
            }
            while(fscanf(fp1,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                if(book.type==type&&!strcmp(book.name,name)){
                    fflush(stdin);
                    printf("ԭ�鼮��Ϣ���£�\n%c %s %s �ݲأ�%d ���裺%d ���������%d\n\n�������µ��鼮��Ϣ����ʽ��ͼ�����ͣ���д��ĸ�������ɸ��ģ� ���� ���� �������� �������� ���Ĵ�������\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    scanf("%c %s %s %d %d %d",&temp_book.type,temp_book.name,temp_book.auther,&temp_book.number,&temp_book.borrowing_number,&temp_book.borrowing_time);
                    fprintf(temp_fp1,"%c %s %s %d %d %d\n",temp_book.type,temp_book.name,temp_book.auther,temp_book.number,temp_book.borrowing_number,temp_book.borrowing_time);
                    judge=0;
                }
                else{
                    fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                }
            }
            if(judge){
                printf("����Ҫ�޸ĵ���Ϣ�����ڣ���������޸��밴��ʽ��������\n");
                continue;
            }
            else{
                while(fscanf(fp2,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                    if(book.type==type&&!strcmp(book.name,name)){
                        fprintf(temp_fp2,"%c %s %s %d %d %d\n",temp_book.type,temp_book.name,temp_book.auther,temp_book.number,temp_book.borrowing_number,temp_book.borrowing_time);
                    }
                    else{
                        fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    }
                }
                fclose(fp1);
                fclose(fp2);
                fclose(temp_fp1);
                fclose(temp_fp2);
                remove(filename);
                remove("all.txt");
                rename(temp_filename,filename);
                rename("temp_all.txt","all.txt");
                printf("�޸ĳɹ�����������޸��밴��ʽ��������\n");
            }
        }
    }
}

void Information_Deletion(){
    system("cls");
    printf("�������鼮���ͣ���д��ĸ�����������ո������������0 0������һҳ\n");
    Type_Code_Tips();
    printf("\n");
    while(1){
        Clear_The_Buffer();
        char type,name[21],filename[6],temp_filename[11];
        int judge=1;
        scanf("%c %s",&type,name);
        if(type=='0'&&!strcmp(name,"0")){
            break;
        }
        else if(type=='L'||type=='M'||type=='W'||type=='Y'||type<'A'||type>'Z'){
            printf("����������������ȷ��ͼ�����ͣ���д��ĸ�� �������ɾ���밴��ʽ��������\n");
        }
        else{
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            Book_Information book;
            FILE *fp1=fopen(filename,"r"),*fp2=fopen("all.txt","r"),*temp_fp1=fopen(temp_filename,"w"),*temp_fp2=fopen("temp_all.txt","w");
            if(fp1==NULL||fp2==NULL){
                printf("���ļ�ʧ�ܣ�\n");
                continue;
            }
            Clear_The_Buffer();
            while(fscanf(fp1,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                if(book.type==type&&!strcmp(book.name,name)){
                    judge=0;
                }
                else{
                    fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                }
            }
            if(judge){
                printf("����Ҫɾ������Ϣ�����ڣ��������ɾ���밴��ʽ��������\n");
                continue;
            }
            else{
                while(fscanf(fp2,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                    if(book.type==type&&!strcmp(book.name,name));
                    else{
                        fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    }
                }
                fclose(fp1);
                fclose(fp2);
                fclose(temp_fp1);
                fclose(temp_fp2);
                remove(filename);
                remove("all.txt");
                rename(temp_filename,filename);
                rename("temp_all.txt","all.txt");
                printf("ɾ���ɹ����������ɾ���밴��ʽ��������\n");
            }
        }
    }
}

void Information_Lookup(){
    while(1){
        system("cls");
        printf("����1�����������鼮 ����2�����߲����鼮 ����0�˻����˵�\n");
        printf("\n");
        Clear_The_Buffer();
        int trans;
        scanf("%d",&trans);
        if(!trans){
            break;
        }
        else if(trans==1){
            Book_Information_Lookup();
        }
        else if(trans==2){
            Author_Information_Lookup();
        }
        else{
            printf("�������ִ���������\n");
        }
    }
}

void Book_Information_Lookup(){
    system("cls");
    printf("�밴���ҷ�Χ��ͼ�����ͣ�����д��ĸ�� ��������ʽ����\n����1�������鼮�в���\n����0�˳�����һҳ\n");
    Type_Code_Tips();
    printf("\n");
    char name[21],type,filename[8];
    Book_Information book;
    while(1){
        int judge=1;
        Clear_The_Buffer();
        scanf("%c",&type);
        if(type=='0'){
            break;
        }
        else if((type>='A'&&type<='K')||(type>='N'&&type<='V')||type=='X'||type=='Z'||type=='1'){
            scanf("%s",name);
            if(type=='1'){
                sprintf(filename,"all.txt");
            }
            else{
                sprintf(filename,"%c.txt",type);
            }
            FILE *fp=fopen(filename,"r");
            while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                if((!strcmp(book.name,name)&&book.type==type)||(!strcmp(book.name,name)&&type=='1')){
                    printf("���ҳɹ��������ѯ�����鼮��Ϣ�����������ʽ����\n%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    judge=0;
                    break;
                }
            }
            fclose(fp);
            if(judge){
                printf("û�иò�����Ϣ�����������Ƿ���ȷ��\n");
            }
        }
        else{
            printf("ͼ�����ͣ���д��ĸ����������������������ʽ����\n");
        }
    }
}

void Author_Information_Lookup(){
    system("cls");
    printf("�밴���ҷ�Χ��ͼ�����ͣ�����д��ĸ�� ���ߵ���ʽ����\n����1�������鼮�в���\n����0�˳�����һҳ\n");
    Type_Code_Tips();
    printf("\n");
    char author[21],type,filename[8];
    Book_Information book;
    while(1){
        int judge=1;
        Clear_The_Buffer();
        scanf("%c",&type);
        if(type=='0'){
            break;
        }
        else if((type>='A'&&type<='K')||(type>='N'&&type<='V')||type=='X'||type=='Z'||type=='1'){
            scanf("%s",author);
            if(type=='1'){
                sprintf(filename,"all.txt");
            }
            else{
                sprintf(filename,"%c.txt",type);
            }
            FILE *fp=fopen(filename,"r");
            while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                if((!strcmp(book.auther,author)&&book.type==type)||(!strcmp(book.auther,author)&&type=='1')){
                    printf("%c %s %s �ݲأ�%d ���裺%d ���������%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    judge=0;
                }
            }
            fclose(fp);
            if(judge){
                printf("û�и�������Ϣ�����������Ƿ���ȷ��\n");
            }
            else{
                printf("���ҳɹ��������ѯ����������Ϣ�����������ʽ����\n");
            }
        }
        else{
            printf("����ͼ�����ͣ���д��ĸ������������������ʽ����\n");
        }
    }
}

void Book_Borrowing(){
    Type_Code_Tips();
    printf("\n");
    while(1){
        Clear_The_Buffer();
        char type,name[21],filename[6],temp_filename[11],reader[21];
        int judge=1;
        Book_Information book;
        scanf("%c",&type);
        if(type=='0'){
            break;
        }
        else{
            scanf("%s %s",name,reader);
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            FILE *fp1=fopen("all.txt","r"),*fp2=fopen(filename,"r"),*temp_fp1=fopen("temp_all.txt","w"),*temp_fp2=fopen(temp_filename,"w"),*borrowing_history=fopen("history.txt","a"),*borrowing=fopen("borrowing.txt","a");
            if(fp1==NULL||fp2==NULL){
                printf("���鲻����\n");
            }
            else{
                while(fscanf(fp1,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                    if(strcmp(book.name,name)==0){
                        if(book.number>book.borrowing_number){
                            fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number+1,book.borrowing_time+1);
                            fprintf(borrowing_history,"%c %s %s %s\n",book.type,book.name,book.auther,reader);
                            fprintf(borrowing,"%c %s %s %s\n",book.type,book.name,book.auther,reader);
                        }
                        else{
                            printf("�����ѱ�ȫ���������ȷ�������Ƿ���ȷ\n");
                            judge=0;
                            break;
                        }
                    }
                    else{
                        fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    }
                }
                if(judge){
                    while(fscanf(fp2,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                        if(strcmp(book.name,name)==0){
                                fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number+1,book.borrowing_time+1);
                        }
                        else{
                            fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                        }
                    }
                }
                fclose(fp1);
                fclose(fp2);
                fclose(temp_fp1);
                fclose(temp_fp2);
                fclose(borrowing);
                fclose(borrowing_history);
                remove("all.txt");
                remove(filename);
                rename("temp_all.txt","all.txt");
                rename(temp_filename,filename);
                printf("������������鼮�밴��ʽ��������\n");
            }
        }
    }
}

void Book_Returning(){
    Type_Code_Tips();
    printf("\n");
    while(1){
        Clear_The_Buffer();
        char type,name[21],filename[6],temp_filename[11],reader[21];
        int judge=1;
        Book_Information book;
        scanf("%c",&type);
        if(type=='0'){
            break;
        }
        else{
            scanf("%s %s",name,reader);
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            FILE *fp1=fopen("all.txt","r"),*fp2=fopen(filename,"r"),*temp_fp1=fopen("temp_all.txt","w"),*temp_fp2=fopen(temp_filename,"w"),*borrowing=fopen("borrowing.txt","r");
            if(fp1==NULL||fp2==NULL||borrowing==NULL){
                printf("���鲻����\n");
            }
            else{
                FILE *temp_borrowing=fopen("temp_borrowing.txt","w");
                while(fscanf(fp1,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                    if(strcmp(book.name,name)==0){
                        if(book.borrowing_number>0){
                            fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number-1,book.borrowing_time);
                            char borrowing_type,borrowing_name[21],borrowing_auther[21],borrowing_reader[21];
                            while(fscanf(borrowing,"%c %s %s %s\n",&borrowing_type,borrowing_name,borrowing_auther,borrowing_reader)==4){
                                if(strcmp(name,borrowing_name)==0&&strcmp(borrowing_reader,reader)==0){
                                    continue;
                                }
                                else{
                                    fprintf(temp_borrowing,"%c %s %s %s\n",borrowing_type,borrowing_name,borrowing_auther,borrowing_reader);
                                }
                            }
                        }
                        else{
                            printf("����ȫ���ڿ⣬��ȷ�������Ƿ���ȷ\n");
                            judge=0;
                            break;
                        }
                    }
                    else{
                        fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    }
                }
                fclose(temp_borrowing);
            }
            if(judge){
                while(fscanf(fp2,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                    if(strcmp(book.name,name)==0){
                            fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number-1,book.borrowing_time);
                    }
                    else{
                        fprintf(temp_fp2,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    }
                }
            }
            fclose(fp1);
            fclose(fp2);
            fclose(temp_fp1);
            fclose(temp_fp2);
            fclose(borrowing);
            remove("all.txt");
            remove(filename);
            remove("borrowing.txt");
            rename("temp_borrowing.txt","borrowing.txt");
            rename("temp_all.txt","all.txt");
            rename(temp_filename,filename);
            printf("��������黹�鼮�밴��ʽ��������\n");
        }
    }
}

void Borrowing_History(){
    Clear_The_Buffer();
    while(1){
        system("cls");
        printf("�����������Ҹö��߶�Ӧ����ʷ�����¼\n����1�鿴������ʷ�����¼\n����0�˻����˵�\n");
        char trans[21];
        scanf("%s",trans);
        if(strcmp(trans,"0")==0){
            break;
        }
        else if(strcmp(trans,"1")==0){
            Clear_The_Buffer();
            Print_All("history.txt");
        }
        else{
            Clear_The_Buffer();
            Print_Name("history.txt",trans);
        }
    }
}

void User_Searching(){
    Clear_The_Buffer();
    while(1){
        system("cls");
        printf("�����������Ҹö��ߵ�δ�黹�鼮\n����1�鿴����δ�黹�鼮\n����0�˻����˵�\n");
        char trans[21];
        scanf("%s",trans);
        if(strcmp(trans,"0")==0){
            break;
        }
        else if(strcmp(trans,"1")==0){
            Clear_The_Buffer();
            Print_All("borrowing.txt");
        }
        else{
            Clear_The_Buffer();
            Print_Name("borrowing.txt",trans);
        }
    }
}

void Print_All(char *filename){
    system("cls");
    FILE *fp=fopen(filename,"r");
    if(fp==NULL){
        printf("û�н����¼��\n");
    }
    else{
        char type,name[21],author[21],reader[21];
        while(fscanf(fp,"%c %s %s %s\n",&type,name,author,reader)==4){
            printf("%c %s %s ����������%s\n",type,name,author,reader);
        }
    }
    fclose(fp);
    system("pause");
}

void Print_Name(char *filename1,char *name1){
    system("cls");
    FILE *fp=fopen(filename1,"r");
    int jur=1;
    if(fp==NULL){
        printf("û�н����¼��\n");
    }
    else{
        char type,name[21],author[21],reader[21];
        while(fscanf(fp,"%c %s %s %s\n",&type,name,author,reader)==4){
            if(strcmp(reader,name1)==0){
                printf("%c %s %s ����������%s\n",type,name,author,reader);
                jur=0;
            }
        }
        if(jur){
            printf("û�иö��ߵĽ����¼��\n");
        }
    }
    fclose(fp);
    system("pause");
}
//����������˰�?_?