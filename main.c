#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
/*命名商品结构体*/
typedef struct good
{
    int order;      //商品顺序编号
    char name[20];  //商品名
    int list;       //商品编号
    char sort[20];  //商品种类
    char state[20]; //商品状态
    int time;       //出入库时间
    char offer[20]; //商家名称
    int num;        //商品数量
    int price;      //商品金额
    char man[20];   //经手人
    struct good* next;
}GOOD;
/*定义用户数据*/
typedef struct user
{
    char name[20];  //用户名
    int key;       //用户密码
    struct user* next;

}USER;


/******************************函数定义******************************/
/*系统主页面*/
int system_UI(void)
{
    int n=3,choose;
    printf("\n\n\n\n                      -------欢迎使用出入库管理系统-----\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |        1. 商品信息查询         |\n");
    printf("                      |                                |\n");
    printf("                      |        2. 商品排序查看         |\n");
    printf("                      |                                |\n");
    printf("                      |        3. 商品信息修改         |\n");
    printf("                      |                                |\n");
    printf("                      |        4. 查看全部商品         |\n");
    printf("                      |                                |\n");
    printf("                      |        5. 管理员系统           |\n");
    printf("                      |                                |\n");
    printf("                      |        6. 退出系统             |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    return choose;
}
/******************************文件操作******************************/
/*data文件读取*/
GOOD* readFile()
{
	FILE *fp;
	GOOD*head, *p , *q;
        p = q = (GOOD*)malloc(sizeof(GOOD));//开辟空间赋指针
	if( ( fp = fopen("data.txt","r") ) == NULL )//文件指针赋值为NULL
	{
		printf( "can't open file\n" );
		exit(0);
	}
	head = p;//头指针赋值并读入
	fscanf( fp,"%d %s %d %s %s %d %s %d %d %s\n",&q->order,q->name,&q->list,q->sort,q->state,&q->time,q->offer,&q->num,&q->price,q->man);
	//1. 开辟新节点 2. 结构体赋值 3. 指针赋值
	while(!feof(fp))
	{
		q = (GOOD*)malloc(sizeof(GOOD));
		fscanf( fp,"%d %s %d %s %s %d %s %d %d %s\n",&q->order,q->name,&q->list,q->sort,q->state,&q->time,q->offer,&q->num,&q->price,q->man );
		p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	return head;
}
/*data文件保存 */
void saveFile(GOOD* L)
{
	if (L == NULL)//头指针空
	{
		printf("can't save file\n");
		return;
	}
	FILE* fp = fopen("data.txt", "wb");
	if (fp == NULL)//文件指针空
	{
		printf("打开文件失败\n");
		return;
	}
	//保存操作
	//存数据，指针往下移
	GOOD* p = L;
	while (p != NULL)
	{
		fprintf(fp,"%d %s %d %s %s %d %s %d %d %s\n",p->order,p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
		p = p->next;
	}
	//收尾处理
	fclose(fp);
	fp = NULL;

}
/*key文件读取*/
USER* key_readFile()
{
	FILE *fp;
	USER*head, *p , *q;
        p = q = (USER*)malloc(sizeof(USER));
	if( ( fp = fopen("key.txt","r") ) == NULL )
	{
		printf( "can't open file\n" );
		exit(0);
	}
	head = p;
	fscanf( fp,"%s %d\n",q->name,&q->key);
	while(!feof(fp))
	{
		q = (USER*)malloc(sizeof(USER));
		fscanf( fp,"%s %d\n",q->name,&q->key);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	return head;
}
/*key文件保存 */
void key_saveFile(USER* L)
{
	if (L == NULL)
	{
		printf("can't save file\n");
		return;
	}
	FILE* fp = fopen("key.txt", "wb");
	if (fp == NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	//保存操作
	USER* p = L;
	while (p != NULL)
	{
		fprintf(fp,"%s %d\n",p->name,p->key);
		p = p->next;
	}
	//收尾处理
	fclose(fp);
	fp = NULL;

}
/******************************查询子函数******************************/
/*商品存量查询*/
void seek_num(GOOD* L)
{
    GOOD* p=L;
    int num;
    int sum=0;
    int count=0;
    char name[20];
    printf("                            请输入存量查询商品编号(eg：1001)：");
    scanf("%d",&num);
    system("cls");
    while(p->next!=NULL)
    {
        if(p->list==num)
        {
            if(strcmp(p->state,"入库")==0)sum+=p->num;//找到目标sum计算
            if(strcmp(p->state,"出库")==0)sum-=p->num;
            strcpy(name,p->name);
            count=1;
        }
        p=p->next;
    }
    if(count==1&&sum!=0)//有库存
    printf("\n\n\n\n\n\n                         %d 号商品 %s 剩余 %d",num,name,sum);
    else printf("\n\n\n\n\n\n                                              无库存");
}
/*商品名称查询*/
void seek_name(GOOD* L)
{
    GOOD* p=L;
    char name[20];
    int count=0;
    printf("                            请输入查询商品名称：");
    scanf("%s",name);
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    while(p->next!=NULL)
    {
        if(strcmp(p->name,name)==0)//匹配到查询目标
            {
                printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
                count++;
            }
        p=p->next;
    }
    if(strcmp(p->name,name)==0)
    {   printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        count++;
    }
    if(count==0)
        printf("                                                      无库存\n");
}
/*商品价格查询*/
void seek_price(GOOD* L)
{
    GOOD* p=L;
    int price;
    int count=0;
    printf("                            请输入查询商品价格：");
    scanf("%d",&price);
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    while(p->next!=NULL)
    {
        if(p->price==price)
            {
                printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
                count++;
            }
        p=p->next;
    }
     if(p->price==price)
    {   printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        count++;
    }
    if(count==0)
        printf("                                                      无库存\n");
}
/*商品名称+状态查询*/
void seek_name_state(GOOD* L)
{
    GOOD* p=L;
    char state[20];
    int count=0;
    char name[20];
    printf("                            请输入查询商品名称：");
    scanf("%s",name);
    printf("                            请输入查询商品状态：");
    scanf("%s",state);
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    while(p->next!=NULL)
    {
        if(strcmp(p->state,state)==0&&strcmp(p->name,name)==0)
            {
                printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
                count++;
            }
        p=p->next;
    }
     if(strcmp(p->state,state)==0&&strcmp(p->name,name)==0)
    {
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        count++;
    }
    if(count==0)
        printf("                                                      无库存\n");
}
/*商品状态+时间查询*/
void seek_state_time(GOOD* L)
{
    GOOD* p=L;
    int time1,time2;
    int count=0;
    char state[20];
    printf("                            请输入查询商品状态：");
    scanf("%s",state);
    printf("                            请输入查询商品时间范围：(例：20200201-20200301)");
    scanf("%d-%d",&time1,&time2);
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    while(p->next!=NULL)
    {
        if(p->time<=time2&&p->time>=time1&&strcmp(p->state,state)==0)
            {
                printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
                count++;
            }
        p=p->next;
    }
     if(p->time<=time2&&p->time>=time1&&strcmp(p->state,state)==0)
    {
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        count++;
    }
    if(count==0)
        printf("                                                      无库存\n");
}
/******************************修改子函数******************************/
/*输入新增商品信息*/
void add_good(GOOD* head)
{
    system("cls");
	GOOD gd;
	printf("\n\n\n\n                            请输入新增商品相关信息\n");
	printf("                              商品名称:");
	scanf("%s",gd.name);
	printf("                              商品编号：(1xxx:电脑及周边;2xxx：生活类;3xxx:食品类;4xxx:宠物相关)");
	scanf("%d",&gd.list);
	printf("                              商品种类:");
	scanf("%s",gd.sort);
	printf("                              商品状态:");
	scanf("%s",gd.state);
	if(strcmp(gd.state,"入库")!=0&&strcmp(gd.state,"出库")!=0)
    {
        printf("                             error\n");
        printf("                              商品状态:");
        scanf("%s",gd.state);
    }
	printf("                              出入库时间(例：20200201):");
	scanf("%d",&gd.time);
	if(gd.time<=20000000||gd.time>=30000000)
    {
        printf("                              error\n");
        printf("                              出入库时间(例：20200201):");
        scanf("%d",&gd.time);
    }
	printf("                              商家名称:");
	scanf("%s",gd.offer);
    printf("                              商品数量:");
	scanf("%d",&gd.num);
	printf("                              商品金额:");
	scanf("%d",&gd.price);
	printf("                              经手人:");
	scanf("%s",gd.man);
	insert_good(head,gd);
}
/*删除商品*/
GOOD* goods_deleat(GOOD* L)
{

    GOOD* p=L;
    GOOD* q;
    int num,i;
    int n,flag=0;
    int order;
    printf("\n\n\n\n\n                         请输入要删除的商品序号：");
    scanf("%d",&num);
	while(1)
    {
        if(p->order==num)break;//找到或者到头了break
        if(p->next==NULL)break;
        q=p;
        p=p->next;

    }
    if(p->order==num)//找到了
    {
        printf("                           已找到待删除信息：\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                           确认是否删除？（Y:1 N:0）");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==L)
                L=p->next;//删头指针
            else
                q->next=p->next;
            p=L;
            p->order=1;
            for(i=2;p->next!=NULL;i++)//赋order
            {
                p=p->next;
                p->order=i;
            }
        }
        saveFile(L);
        flag=1;
    }
    if(p->next==NULL&&flag==0) printf("                                删除信息不存在\n");
	return L;
}
/*插入商品信息 */
void insert_good(GOOD *L,GOOD e)
{
	GOOD* p=L;
	int i;
	GOOD *s=(GOOD *)malloc(sizeof(GOOD));//开新节点，存入
	*s=e;
	s->next=NULL;
	int order;
	while(p->next!=NULL)
    {
        p=p->next;
    }
        p->next=s;
        p=L;
        p->order=1;
        for(i=2;p->next!=NULL;i++)//赋值order
        {
            p=p->next;
            p->order=i;
        }


	saveFile(L);
}
/*修改供货商信息*/
void cover_offer(GOOD* L)
{

    int num;
    GOOD* p=L;
    char offer[20];
    printf("\n\n\n\n\n\n                     请输入待修改商品序号：");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;

    }
    if(p->order==num)
    {
        printf("                     已找到待修改信息\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     请输入更改后的供货商信息：");
        scanf("%s",offer);
        strcpy(p->offer,offer);
        printf("                     更改后的信息为：\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
    if(p->next==NULL)printf("                     未找到待修改信息\n");
}
/*修改商品数量*/
void cover_num(GOOD* L)
{
    int num;
    GOOD* p=L;
    int cover;
    printf("\n\n\n\n\n\n                     请输入待修改商品序号：");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     已找到待修改信息\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     请输入更改后的商品数量：");
        scanf("%d",&cover);
        p->num=cover;
        printf("                     更改后的信息为：\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
    if(p->next==NULL)printf("                     未找到待修改信息\n");
}
/*修改商品价格*/
void cover_price(GOOD* L)
{
    int num;
    GOOD* p=L;
    int money;
    printf("\n\n\n\n\n\n                     请输入待修改商品编号：");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     已找到待修改信息\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     请输入更改后的商品价格：");
        scanf("%d",&money);
        p->price=money;
        printf("                     更改后的信息为：\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
        if(p->next==NULL)printf("                     未找到待修改信息\n");
}
/*修改商品经手人*/
void cover_man(GOOD* L)
{
    int num;
    GOOD* p=L;
    char name[20];
    printf("\n\n\n\n\n\n                     请输入待修改商品编号：");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     已找到待修改信息\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     请输入更改后的经手人信息：");
        scanf("%s",name);
        strcpy(p->man,name);
        printf("                     更改后的信息为：\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
        if(p->next==NULL)printf("                     未找到待修改信息\n");
}
/*修改商品信息*/
void goods_change(GOOD* L)
{
    int n=3,choose;
    int mark;
    system("cls");
    printf("                      ----------请选择修改类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 供货商名称        |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 商品数量          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. 商品价格          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. 经手人            |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);
    system("cls");
    switch(choose)//while循环提示循环修改
    {
        case 1:
            while(1)
            {
                    cover_offer(L);
                    printf("                            是否继续修改供货商信息？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 2:
            while(1)
            {
                    cover_num(L);
                    printf("                            是否继续修改商品数量？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 3:
            while(1)
            {
                    cover_price(L);
                    printf("                            是否继续修改商品价格？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 4:
            while(1)
            {
                    cover_man(L);
                    printf("                            是否继续修改经手人信息？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/******************************排序子函数******************************/
//序号排序
void sort_num(GOOD* L)
{
    GOOD* p=L;
    int num[100]={0};
    int order[100];
    int i;
    for(i=0;;i++)//num、order存到数组里
    {
        num[i]=p->list;
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){num[i+1]=p->list;order[i+1]=p->order;break;}
    }
    int n=3,choose;
    system("cls");
    printf("\n\n\n\n                      ----------请选择排序类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 升序排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 降序排序          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_num(num,order,L);break;
        case 2:sort_desc_num(num,order,L);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*序号升序排序*/
void sort_pose_num(int num[],int order[],GOOD* L)
{
    int n=0;
    int i,j;
    int temp;
    GOOD* p=L;
    for(i=0;;i++)
    {
        if(num[i]==0)break;
        n++;
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(num[j]>num[j+1])//冒泡排序
            {
                temp=num[j];
                num[j]=num[j+1];
                num[j+1]=temp;
                temp=order[j];
                order[j]=order[j+1];
                order[j+1]=temp;
            }
        }
    }
    system("cls");//清屏输出
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
    {
        p=L;
        while(p->list!=num[i]||p->order!=order[i])p=p->next;
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        if(i!=0&&(i+1)%10==0)
        {
            system ("pause");
            system("cls");
            printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
            printf("                ———————————————————————————————————————————\n");
        }
    }



}
/*序号降序排序*/
void sort_desc_num(int num[],int order[],GOOD* L)
{
    int n=0;
    int i,j;
    int temp;
    GOOD* p=L;
    for(i=0;;i++)
    {
        if(num[i]==0)break;
        n++;
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(num[j]<num[j+1])//冒泡排序
            {
                temp=num[j];
                num[j]=num[j+1];
                num[j+1]=temp;
                temp=order[j];
                order[j]=order[j+1];
                order[j+1]=temp;
            }
        }
    }
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
    {
        p=L;
        while(p->list!=num[i]||p->order!=order[i])p=p->next;
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        if(i!=0&&(i+1)%10==0)
        {
            system ("pause");
            system("cls");
            printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
            printf("                ———————————————————————————————————————————\n");
        }
    }




}
//名称排序
void sort_name(GOOD* L)
{
    GOOD* p=L;
    char name[100][100];
    char (*name_p)[100];
    int order[100];
    int i;
    for(i=0;;i++)//村name和order
    {
        strcpy(name[i],p->name);
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){strcpy(name[i+1],p->name);order[i+1]=p->order;break;}
    }
    int tag=i+2;
    name_p=name;
    int n=3,choose;
    system("cls");
    printf("\n\n\n\n                      ----------请选择排序类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 升序排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 降序排序          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_name(name_p,L,order,tag);break;
        case 2:sort_desc_name(name_p,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*名称升序排序*/
void sort_pose_name(char (*name)[100],GOOD* L,int order[],int n)
{
    int i,j;
    int order_sort;
    char temp[100];
    GOOD* p=L;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(strcmp(name[j],name[j+1])>0)//依旧冒泡
            {
                 strcpy(temp,name[j]);
                 strcpy(name[j],name[j+1]);
                 strcpy(name[j+1],temp);
                 order_sort=order[j];
                 order[j]=order[j+1];
                 order[j+1]=order_sort;
            }
        }
    }

    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(name[i],p->name)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
/*名称降序排序*/
void sort_desc_name(char (*name)[100],GOOD* L,int order[],int n)
{
     int i,j;
    int order_sort;
    char temp[100];
    GOOD* p=L;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(strcmp(name[j],name[j+1])<0)
            {
                 strcpy(temp,name[j]);
                 strcpy(name[j],name[j+1]);
                 strcpy(name[j+1],temp);
                 order_sort=order[j];
                 order[j]=order[j+1];
                 order[j+1]=order_sort;
            }
        }
    }

    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(name[i],p->name)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
//日期排序
void sort_time(GOOD* L)
{
    GOOD* p=L;
    int time[100]={0};
    int order[100];
    int i;
    for(i=0;;i++)//time、order存数组
    {
        time[i]=p->time;
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){time[i+1]=p->time;order[i+1]=p->order;break;}
    }
    int tag=i+2;
    int n=3,choose;
    system("cls");
    printf("\n\n\n\n                      ----------请选择排序类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 升序排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 降序排序          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_time(time,L,order,tag);break;
        case 2:sort_desc_time(time,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*日期升序排序*/
void sort_pose_time(int time[],GOOD* L,int order[],int n)
{
    int i,j;
    int temp;
    GOOD* p=L;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(time[j]>time[j+1])//简单冒泡*3
            {
                temp=time[j];
                time[j]=time[j+1];
                time[j+1]=temp;
                temp=order[j];
                order[j]=order[j+1];
                order[j+1]=temp;
            }
        }
    }
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(p->time!=time[i]||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
/*日期降序排序*/
void sort_desc_time(int time[],GOOD* L,int order[],int n)
{
    int i,j;
    int temp;
    GOOD* p=L;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(time[j]<time[j+1])
            {
                temp=time[j];
                time[j]=time[j+1];
                time[j+1]=temp;
                temp=order[j];
                order[j]=order[j+1];
                order[j+1]=temp;
            }
        }
    }
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(p->time!=time[i]||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
//供货商排序
void sort_offer(GOOD* L)
{
    GOOD* p=L;
    char offer[100][100];
    char (*offer_p)[100];
    int order[100];
    int i;
    for(i=0;;i++)//存入数组
    {
        strcpy(offer[i],p->offer);
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){strcpy(offer[i+1],p->offer);order[i+1]=p->order;break;}
    }
    offer_p=offer;
    int tag=i+2;
    int n=3,choose;

    system("cls");
    printf("\n\n\n\n                      ----------请选择排序类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 升序排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 降序排序          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_offer(offer_p,L,order,tag);break;
        case 2:sort_desc_offer(offer_p,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*供货商升序排序*/
void sort_pose_offer(char (*offer)[100],GOOD* L,int order[],int n)
{
    int i,j;
    char temp[100];
    GOOD* p=L;
    int order_sort;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(strcmp(offer[j],offer[j+1])>0)//简简单单冒泡
            {
                 strcpy(temp,offer[j]);
                 strcpy(offer[j],offer[j+1]);
                 strcpy(offer[j+1],temp);
                 order_sort=order[j];
                 order[j]=order[j+1];
                 order[j+1]=order_sort;
            }
        }
    }
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(offer[i],p->offer)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
/*供货商降序排序*/
void sort_desc_offer(char (*offer)[100],GOOD* L,int order[],int n)
{
     int i,j;
    char temp[100];
    GOOD* p=L;
    int order_sort;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(strcmp(offer[j],offer[j+1])<0)
            {
                 strcpy(temp,offer[j]);
                 strcpy(offer[j],offer[j+1]);
                 strcpy(offer[j+1],temp);
                 order_sort=order[j];
                 order[j]=order[j+1];
                 order[j+1]=order_sort;
            }
        }
    }
    system("cls");
    printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
    printf("                ———————————————————————————————————————————\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(offer[i],p->offer)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
                printf("                ———————————————————————————————————————————\n");
            }
        }
}
/******************************管理员操作******************************/
/*输入管理员*/
void add_user(USER* head)//类似商品的新增
{
    system("cls");
	USER us;
	printf("\n\n\n\n                            请输入新增管理员信息\n");
	printf("                              管理员账号:");
	scanf("%s",us.name);
	printf("                              管理员密码：");
	scanf("%d",&us.key);
	insert_user(head,us);
}
/*删除管理员*/
USER* user_deleat(USER* L)//类似商品的删除
{

    USER* p=L;
    USER* q;
    int i;
    char name[100];
    int n,flag=0;
    printf("                         请输入要删除的管理员姓名：");
    scanf("%s",name);
	while(1)
    {
        if(strcmp(p->name,name)==0)break;
        if(p->next==NULL)break;
        q=p;
        p=p->next;

    }
    if(strcmp(p->name,name)==0)
    {
        printf("                           已找到待删除信息：\n");
        printf("                            %s %d\n",p->name,p->key);
        printf("                           确认是否删除？（Y:1 N:0）");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==L)
                L=p->next;
            else
                q->next=p->next;
        }
        key_saveFile(L);
        flag=1;
    }
    if(p->next==NULL&&flag==0) printf("                                删除信息不存在\n");
	return L;
}
/*插入管理员*/
void insert_user(USER *L,USER e)//类似商品的插入
{
	USER* p=L;
	int i;
	USER *s=(USER *)malloc(sizeof(USER));
	*s=e;
	s->next=NULL;
	while(p->next!=NULL)
    {
        p=p->next;
    }
        p->next=s;


	key_saveFile(L);
}
/*查看全部管理员*/
void user_list(USER* head)//类似商品的全部查看
{
     USER* p;
     p=head;
     printf("\n\n\n\n                                        |  账号  |  密码  |\n");
     printf("                                        |%8s|%8d|\n",p->name,p->key);
     while(p->next!=NULL)
     {
         p=p->next;
         printf("                                        |%8s|%8d|\n",p->name,p->key);
     }
}
/*修改管理员密码*/
void user_key(USER* L)//类似商品的修改
{
    int key;
    USER* p=L;
    char name[20];
    printf("\n\n\n\n\n\n                     请输入待修改管理员账户：");
    scanf("%s",name);
    while(1)
    {
        if(strcmp(p->name,name)==0)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(strcmp(p->name,name)==0)
    {
        printf("                     已找到待修改信息\n");
        printf("                            %s %d\n",p->name,p->key);
        printf("                     请输入更改后的管理员密码：");
        scanf("%d",&key);
        p->key=key;
        printf("                     更改后的信息为：\n");
        printf("                            %s %d\n",p->name,p->key);
    }
    if(p->next==NULL)printf("                     未找到待修改信息\n");
    key_saveFile(L);
}
/******************************查看全部******************************/
/*排序*/
void sort_all(GOOD* L)//选择排序，链表整体排序保存
{
    GOOD *p;
    GOOD *q;
    for(p=L;p!=NULL;p=p->next)
        {
        for(q=p;q!=NULL;q=q->next)
        {
			if(p->time>q->time)
			{
				//交换数据域
				GOOD t=*p;
				*p=*q;
				*q=t;
				//处理指针域
				t.next=p->next;
				p->next=q->next;
				q->next=t.next;
			}
		}

	}
	p=L;
	p->order=1;//赋order
	for(int i=2;p->next!=NULL;i++)
    {
        p=p->next;
        p->order=i;
    }
	saveFile(L);//save

}
/*查看全部商品*/
void goods_list(GOOD* q)
{

     system("cls");

     sort_all(q);
    while(q!=NULL)//链表遍历输出
    {
        printf("\n\n\n\n                | 序号 | 名称 | 编号 |   种类   | 状态 |   时间   |      供货商       | 数量 | 价格 | 经手人 |\n");
        printf("                ————————————————————————————————————————————————\n");
        for(int i=0;i<10;i++)
        {
            printf("                |%6d|%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",q->order,q->name,q->list, q->sort,q->state,q->time,q->offer,q->num,q-> price,q->man );
            q=q->next;
            if(q->next==NULL){printf("                |%6d|%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",q->order,q->name,q->list, q->sort,q->state,q->time,q->offer,q->num,q-> price,q->man  );break;}
        }
        if(q->next==NULL)break;
        system ("pause");
        system("cls");
    }
    return 0;
}
/******************************主页面******************************/
/*商品信息查询主页面*/
int goods_seek(GOOD* L)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------请选择查询类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 存量查询          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 名称查询          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. 价格查询          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. 名称+状态查询     |\n");
    printf("                      |                                |\n");
    printf("                      |           5. 状态+时间查询     |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:seek_num(L);break;
        case 2:seek_name(L);break;
        case 3:seek_price(L);break;
        case 4:seek_name_state(L);break;
        case 5:seek_state_time(L);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*商品排序查看主页面*/
int goods_sort(GOOD* L)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------请选择排序类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 序号排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 名称排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. 日期排序          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. 供货商排序        |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   请选择:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_num(L);break;
        case 2:sort_name(L);break;
        case 3:sort_time(L);break;
        case 4:sort_offer(L);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*商品信息修改主页面*/
void goods_cover(GOOD* head,USER* user)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------请选择修改类型---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 增加商品          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 修改商品信息      |\n");
    printf("                      |                                |\n");
    printf("                      |           3. 删除商品          |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                    请选择:");
    scanf("%d",&choose);
    system("cls");
    switch(choose)
    {
        case 1:choose=allow(user);system("cls");
            if(choose==1)
            {
                while(1)
                {
                    add_good(head);
                    printf("                            是否继续添加？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
                }
            }
            break;
        case 2:choose=allow(user);system("cls");
            if(choose==1)
            {
                while(1)
                {
                    goods_change(head);
                    saveFile(head);
                    printf("                            是否继续更改？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
                }
            }
            break;
        case 3:choose=allow(user);system("cls");
            if(choose==1)
            {
                while(1)
                {
                    head=goods_deleat(head);
                    saveFile(head);
                    printf("                            是否继续删除？（Y:1 N:0）");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
                }
            }
            break;
            default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*管理员系统主页面*/
USER* administer(USER* head)
    {
    USER* p=head;
    int n=3,choose;
    printf("\n\n\n\n                      ----------请选择管理内容---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. 新增管理员        |\n");
    printf("                      |                                |\n");
    printf("                      |           2. 删除管理员        |\n");
    printf("                      |                                |\n");
    printf("                      |           3. 修改管理员密码    |\n");
    printf("                      |                                |\n");
    printf("                      |           4. 查看全部管理员    |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   请选择:");
    scanf("%d",&choose);
    system("cls");
    n=allow(p);
    if(n==1)
    {
          switch(choose)
        {
            case 1:add_user(p);break;
            case 2:user_deleat(p);break;
            case 3:user_key(p);break;
            case 4:user_list(p);break;
            default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
        }
    }
    else
        printf("验证失败");

}

/******************************其他函数******************************/
/*退出*/
void goodbye()
{
    system("cls");
	printf("\n\n\n\n\n\n\n\n                                       欢迎下次使用~");
	exit(0);
}
/*检测用户*/
int allow(USER* head)
{
    USER*p=head;
    char name[20];
    int key;
    printf("\n\n\n\n\n\n\n\n\n                              请输入用户名：");
    scanf("%s",&name);
    printf("                              请输入密码：");
    scanf("%d",&key);
    if(strcmp(name,p->name)==0 && key==p->key)
    {
        printf("                                   验证成功\n");
        system("pause");
        system("cls");
        return 1;
    }
    while(p->next!=NULL)
    {
        p=p->next;
        if(strcmp(name,p->name)==0 && key==p->key)
    {
        printf("                                   验证成功\n");
        system("pause");
        system("cls");
        return 1;
    }
    }
        printf("                                   验证失败\n");
        system("pause");
        system("cls");
        return 0;


}

/*******************************主函数*******************************/
int main()
{
    int choose;
    GOOD* q;
    USER* p;
    q = readFile();
    p=key_readFile();
    while(1)
    {
        choose=system_UI();
    switch(choose)
    {
        case 1:goods_seek(q);break;
        case 2:goods_sort(q);break;
        case 3:goods_cover(q,p);break;
        case 4: q = readFile();goods_list(q);break;
        case 5:administer(p);break;
        case 6:goodbye();break;
        default : printf("\n\n\n\n\n\n\n\n\n\n                                               error");break;
    }
    printf("\n                                      是否继续使用系统？（Y:1 N:0) ");
    scanf("%d",&choose);
    system("cls");
    if(choose==0){goodbye();break;}
    else continue;
    }
}



