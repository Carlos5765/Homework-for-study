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
    while (getchar()!= '\n') {//清理缓冲区
    continue;
    }
}

void Menu(){//在程序开始运行时，打印菜单
    printf("--------------------------------\n|      图书馆藏书管理系统      |\n|  (按下对应数字启用对应功能)  |\n|------------------------------|\n|1.录入书籍信息  2.浏览书籍信息|\n|------------------------------|\n|3.更改书籍信息  4.查找书籍信息|\n|------------------------------|\n|5.借阅图书登记  6.归还图书登记|\n|------------------------------|\n|7.查看借书记录  8.浏览借出信息|\n|------------------------------|\n|        0.关闭管理系统        |\n--------------------------------\n");
}

int Menu_Jump(int translater){//由程序菜单到其他模块的跳转
    switch(translater){
        case 1:
            system("cls");
            printf("以“图书类型（大写字母） 书名 作者 该书数量 1/0”形式输入藏书信息，每行末尾输入1代表之后继续输入，输入0代表返回菜单，敲击回车完成输入\n");
            Information_Input();
            return 1;
            break;
        case 2:
            system("cls");
            printf("输入图书类型（大写字母）查看对应类型书籍信息\n输入1查看所有藏书信息\n按0返回主菜单\n");
            Information_Browsing();
            return 1;
            break;
        case 3:
            system("cls");
            printf("输入图书类型（大写字母） 书名修改该书相关信息 无法修改图书类型\n按0返回主菜单\n");
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
            printf("输入图书类型（大写字母） 书名 读者姓名即可登记\n按0返回主菜单\n");
            Book_Borrowing();
            return 1;
            break;
        case 6:
            system("cls");
            printf("输入图书类型（大写字母） 书名 读者姓名即可登记\n按0返回主菜单\n");
            Book_Returning();
            return 1;
            break;
        case 7:
            system("cls");
            printf("输入读者姓名查找该读者的借书记录\n按1浏览所有借书记录\n");
            Borrowing_History();
            return 1;
            break;
        case 8:
            system("cls");
            printf("输入读者姓名查找该读者目前的所借书籍\n按1浏览所有借出信息\n");
            User_Searching();
            return 1;
            break;
        case 0:
            return 0;
            break;
        default:
            printf("输入有误！请输入正确的数字！\n");
            return 1;
            break;
    }
}

void Type_Code_Tips(){//显示图书分类信息
    printf("\n中国图书分类法：\nA 马克思主义 列宁主义 毛泽东思想 邓小平理论\nB 哲学 宗教\nC 社会科学总论\nD 政治 法律\nE 军事\nF 经济\nG 文化 科学 教育 体育\nH 语言 文字\nI 文学\nJ 艺术\nK 历史 地理\nN 自然科学总论\nO 数理科学和化学\nP 天文学 地球科学\nQ 生物科学\nR 医药 卫生\nS 农业科学\nT 工业技术\nU 交通运输\nV 航空 航天\nX 环境科学 安全科学\nZ 综合性图书\n");
}

void Information_Input(){//在文本文档中输入书籍信息
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
            printf("输入有误！请输入正确的大写字母图书分类编号\n");
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
            printf("录入信息成功\n");
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
            printf("打开文件失败！将返回主菜单！\n");
            fclose(fp);
            system("pause");
        }
        else{
            system("cls");
            Clear_The_Buffer();
            printf("按下数字以对应方式排序\n1.按默认顺序排序  2.按藏书数量排序\n3.按借阅热度排序  4.按借出数量排序\n按0退回主菜单\n");
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
            printf("打开文件失败！将返回主菜单！\n");
            fclose(fp);
            system("pause");
        }
        else{
            system("cls");
            Clear_The_Buffer();
            printf("按下数字以对应方式排序\n1.按默认顺序排序  2.按藏书数量排序\n3.按借阅热度排序  4.按借出数量排序\n");
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
        printf("输入错误！将返回主菜单！\n");
        system("pause");
    }
}

void Default_Sorting(FILE *fp){
    Book_Information book;
    system("cls");
    while(fscanf(fp,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
        printf("%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
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
                printf("%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
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
                printf("%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
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
                printf("%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
            }
        }
        fclose(fp);
    }
    system("pause");
}

void Information_Update(){
    while(1){
        system("cls");
        printf("输入1修改书籍信息 输入2删除信息 输入0退回主菜单\n");
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
            printf("输入数字错误！请重试\n");
        }
    }
}

void Information_Change(){
    system("cls");
    printf("请输入书籍类型（大写字母）和书名（空格隔开），输入0 0返回上一页\n");
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
            printf("输入有误！请输入正确的图书类型（大写字母） 如需继续修改请按格式继续输入\n");
        }
        else{
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            Book_Information book,temp_book;
            FILE *fp1=fopen(filename,"r"),*fp2=fopen("all.txt","r"),*temp_fp1=fopen(temp_filename,"w"),*temp_fp2=fopen("temp_all.txt","w");
            if(fp1==NULL||fp2==NULL){
                printf("打开文件失败！\n");
                continue;
            }
            while(fscanf(fp1,"%c %s %s %d %d %d\n",&book.type,book.name,book.auther,&book.number,&book.borrowing_number,&book.borrowing_time)==6){
                if(book.type==type&&!strcmp(book.name,name)){
                    fflush(stdin);
                    printf("原书籍信息如下：\n%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n\n请输入新的书籍信息（格式：图书类型（大写字母）（不可更改） 书名 作者 该书数量 借阅数量 借阅次数）：\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    scanf("%c %s %s %d %d %d",&temp_book.type,temp_book.name,temp_book.auther,&temp_book.number,&temp_book.borrowing_number,&temp_book.borrowing_time);
                    fprintf(temp_fp1,"%c %s %s %d %d %d\n",temp_book.type,temp_book.name,temp_book.auther,temp_book.number,temp_book.borrowing_number,temp_book.borrowing_time);
                    judge=0;
                }
                else{
                    fprintf(temp_fp1,"%c %s %s %d %d %d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                }
            }
            if(judge){
                printf("您所要修改的信息不存在！如需继续修改请按格式继续输入\n");
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
                printf("修改成功！如需继续修改请按格式继续输入\n");
            }
        }
    }
}

void Information_Deletion(){
    system("cls");
    printf("请输入书籍类型（大写字母）和书名（空格隔开），输入0 0返回上一页\n");
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
            printf("输入有误！请输入正确的图书类型（大写字母） 如需继续删除请按格式继续输入\n");
        }
        else{
            sprintf(filename,"%c.txt",type);
            sprintf(temp_filename,"temp_%c.txt",type);
            Book_Information book;
            FILE *fp1=fopen(filename,"r"),*fp2=fopen("all.txt","r"),*temp_fp1=fopen(temp_filename,"w"),*temp_fp2=fopen("temp_all.txt","w");
            if(fp1==NULL||fp2==NULL){
                printf("打开文件失败！\n");
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
                printf("您所要删除的信息不存在！如需继续删除请按格式继续输入\n");
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
                printf("删除成功！如需继续删除请按格式继续输入\n");
            }
        }
    }
}

void Information_Lookup(){
    while(1){
        system("cls");
        printf("输入1按书名查找书籍 输入2按作者查找书籍 输入0退回主菜单\n");
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
            printf("输入数字错误！请重试\n");
        }
    }
}

void Book_Information_Lookup(){
    system("cls");
    printf("请按查找范围（图书类型）（大写字母） 书名的形式输入\n输入1在所有书籍中查找\n输入0退出到上一页\n");
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
                    printf("查找成功！如需查询其他书籍信息，请继续按格式输入\n%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    judge=0;
                    break;
                }
            }
            fclose(fp);
            if(judge){
                printf("没有该藏书信息！请检查输入是否正确！\n");
            }
        }
        else{
            printf("图书类型（大写字母）输入有误！请检查后继续按格式输入\n");
        }
    }
}

void Author_Information_Lookup(){
    system("cls");
    printf("请按查找范围（图书类型）（大写字母） 作者的形式输入\n输入1在所有书籍中查找\n输入0退出到上一页\n");
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
                    printf("%c %s %s 馆藏：%d 出借：%d 借出次数：%d\n",book.type,book.name,book.auther,book.number,book.borrowing_number,book.borrowing_time);
                    judge=0;
                }
            }
            fclose(fp);
            if(judge){
                printf("没有该作者信息！请检查输入是否正确！\n");
            }
            else{
                printf("查找成功！如需查询其他作者信息，请继续按格式输入\n");
            }
        }
        else{
            printf("输入图书类型（大写字母）有误！请检查后继续按格式输入\n");
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
                printf("该书不存在\n");
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
                            printf("该书已被全部借出，请确认输入是否正确\n");
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
                printf("如需继续借阅书籍请按格式继续输入\n");
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
                printf("该书不存在\n");
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
                            printf("该书全部在库，请确认输入是否正确\n");
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
            printf("如需继续归还书籍请按格式继续输入\n");
        }
    }
}

void Borrowing_History(){
    Clear_The_Buffer();
    while(1){
        system("cls");
        printf("输入人名查找该读者对应的历史借书记录\n输入1查看所有历史借书记录\n输入0退回主菜单\n");
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
        printf("输入人名查找该读者的未归还书籍\n输入1查看所有未归还书籍\n输入0退回主菜单\n");
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
        printf("没有借书记录！\n");
    }
    else{
        char type,name[21],author[21],reader[21];
        while(fscanf(fp,"%c %s %s %s\n",&type,name,author,reader)==4){
            printf("%c %s %s 读者姓名：%s\n",type,name,author,reader);
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
        printf("没有借书记录！\n");
    }
    else{
        char type,name[21],author[21],reader[21];
        while(fscanf(fp,"%c %s %s %s\n",&type,name,author,reader)==4){
            if(strcmp(reader,name1)==0){
                printf("%c %s %s 读者姓名：%s\n",type,name,author,reader);
                jur=0;
            }
        }
        if(jur){
            printf("没有该读者的借书记录！\n");
        }
    }
    fclose(fp);
    system("pause");
}
//这回总完事了吧?_?