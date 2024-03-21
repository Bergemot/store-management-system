#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
/*������Ʒ�ṹ��*/
typedef struct good
{
    int order;      //��Ʒ˳����
    char name[20];  //��Ʒ��
    int list;       //��Ʒ���
    char sort[20];  //��Ʒ����
    char state[20]; //��Ʒ״̬
    int time;       //�����ʱ��
    char offer[20]; //�̼�����
    int num;        //��Ʒ����
    int price;      //��Ʒ���
    char man[20];   //������
    struct good* next;
}GOOD;
/*�����û�����*/
typedef struct user
{
    char name[20];  //�û���
    int key;       //�û�����
    struct user* next;

}USER;


/******************************��������******************************/
/*ϵͳ��ҳ��*/
int system_UI(void)
{
    int n=3,choose;
    printf("\n\n\n\n                      -------��ӭʹ�ó�������ϵͳ-----\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |        1. ��Ʒ��Ϣ��ѯ         |\n");
    printf("                      |                                |\n");
    printf("                      |        2. ��Ʒ����鿴         |\n");
    printf("                      |                                |\n");
    printf("                      |        3. ��Ʒ��Ϣ�޸�         |\n");
    printf("                      |                                |\n");
    printf("                      |        4. �鿴ȫ����Ʒ         |\n");
    printf("                      |                                |\n");
    printf("                      |        5. ����Աϵͳ           |\n");
    printf("                      |                                |\n");
    printf("                      |        6. �˳�ϵͳ             |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);//�û�ѡ����
    system("cls");
    return choose;
}
/******************************�ļ�����******************************/
/*data�ļ���ȡ*/
GOOD* readFile()
{
	FILE *fp;
	GOOD*head, *p , *q;
        p = q = (GOOD*)malloc(sizeof(GOOD));//���ٿռ丳ָ��
	if( ( fp = fopen("data.txt","r") ) == NULL )//�ļ�ָ�븳ֵΪNULL
	{
		printf( "can't open file\n" );
		exit(0);
	}
	head = p;//ͷָ�븳ֵ������
	fscanf( fp,"%d %s %d %s %s %d %s %d %d %s\n",&q->order,q->name,&q->list,q->sort,q->state,&q->time,q->offer,&q->num,&q->price,q->man);
	//1. �����½ڵ� 2. �ṹ�帳ֵ 3. ָ�븳ֵ
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
/*data�ļ����� */
void saveFile(GOOD* L)
{
	if (L == NULL)//ͷָ���
	{
		printf("can't save file\n");
		return;
	}
	FILE* fp = fopen("data.txt", "wb");
	if (fp == NULL)//�ļ�ָ���
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	//�������
	//�����ݣ�ָ��������
	GOOD* p = L;
	while (p != NULL)
	{
		fprintf(fp,"%d %s %d %s %s %d %s %d %d %s\n",p->order,p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
		p = p->next;
	}
	//��β����
	fclose(fp);
	fp = NULL;

}
/*key�ļ���ȡ*/
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
/*key�ļ����� */
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
		printf("���ļ�ʧ��\n");
		return;
	}
	//�������
	USER* p = L;
	while (p != NULL)
	{
		fprintf(fp,"%s %d\n",p->name,p->key);
		p = p->next;
	}
	//��β����
	fclose(fp);
	fp = NULL;

}
/******************************��ѯ�Ӻ���******************************/
/*��Ʒ������ѯ*/
void seek_num(GOOD* L)
{
    GOOD* p=L;
    int num;
    int sum=0;
    int count=0;
    char name[20];
    printf("                            �����������ѯ��Ʒ���(eg��1001)��");
    scanf("%d",&num);
    system("cls");
    while(p->next!=NULL)
    {
        if(p->list==num)
        {
            if(strcmp(p->state,"���")==0)sum+=p->num;//�ҵ�Ŀ��sum����
            if(strcmp(p->state,"����")==0)sum-=p->num;
            strcpy(name,p->name);
            count=1;
        }
        p=p->next;
    }
    if(count==1&&sum!=0)//�п��
    printf("\n\n\n\n\n\n                         %d ����Ʒ %s ʣ�� %d",num,name,sum);
    else printf("\n\n\n\n\n\n                                              �޿��");
}
/*��Ʒ���Ʋ�ѯ*/
void seek_name(GOOD* L)
{
    GOOD* p=L;
    char name[20];
    int count=0;
    printf("                            �������ѯ��Ʒ���ƣ�");
    scanf("%s",name);
    system("cls");
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    while(p->next!=NULL)
    {
        if(strcmp(p->name,name)==0)//ƥ�䵽��ѯĿ��
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
        printf("                                                      �޿��\n");
}
/*��Ʒ�۸��ѯ*/
void seek_price(GOOD* L)
{
    GOOD* p=L;
    int price;
    int count=0;
    printf("                            �������ѯ��Ʒ�۸�");
    scanf("%d",&price);
    system("cls");
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
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
        printf("                                                      �޿��\n");
}
/*��Ʒ����+״̬��ѯ*/
void seek_name_state(GOOD* L)
{
    GOOD* p=L;
    char state[20];
    int count=0;
    char name[20];
    printf("                            �������ѯ��Ʒ���ƣ�");
    scanf("%s",name);
    printf("                            �������ѯ��Ʒ״̬��");
    scanf("%s",state);
    system("cls");
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
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
        printf("                                                      �޿��\n");
}
/*��Ʒ״̬+ʱ���ѯ*/
void seek_state_time(GOOD* L)
{
    GOOD* p=L;
    int time1,time2;
    int count=0;
    char state[20];
    printf("                            �������ѯ��Ʒ״̬��");
    scanf("%s",state);
    printf("                            �������ѯ��Ʒʱ�䷶Χ��(����20200201-20200301)");
    scanf("%d-%d",&time1,&time2);
    system("cls");
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
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
        printf("                                                      �޿��\n");
}
/******************************�޸��Ӻ���******************************/
/*����������Ʒ��Ϣ*/
void add_good(GOOD* head)
{
    system("cls");
	GOOD gd;
	printf("\n\n\n\n                            ������������Ʒ�����Ϣ\n");
	printf("                              ��Ʒ����:");
	scanf("%s",gd.name);
	printf("                              ��Ʒ��ţ�(1xxx:���Լ��ܱ�;2xxx��������;3xxx:ʳƷ��;4xxx:�������)");
	scanf("%d",&gd.list);
	printf("                              ��Ʒ����:");
	scanf("%s",gd.sort);
	printf("                              ��Ʒ״̬:");
	scanf("%s",gd.state);
	if(strcmp(gd.state,"���")!=0&&strcmp(gd.state,"����")!=0)
    {
        printf("                             error\n");
        printf("                              ��Ʒ״̬:");
        scanf("%s",gd.state);
    }
	printf("                              �����ʱ��(����20200201):");
	scanf("%d",&gd.time);
	if(gd.time<=20000000||gd.time>=30000000)
    {
        printf("                              error\n");
        printf("                              �����ʱ��(����20200201):");
        scanf("%d",&gd.time);
    }
	printf("                              �̼�����:");
	scanf("%s",gd.offer);
    printf("                              ��Ʒ����:");
	scanf("%d",&gd.num);
	printf("                              ��Ʒ���:");
	scanf("%d",&gd.price);
	printf("                              ������:");
	scanf("%s",gd.man);
	insert_good(head,gd);
}
/*ɾ����Ʒ*/
GOOD* goods_deleat(GOOD* L)
{

    GOOD* p=L;
    GOOD* q;
    int num,i;
    int n,flag=0;
    int order;
    printf("\n\n\n\n\n                         ������Ҫɾ������Ʒ��ţ�");
    scanf("%d",&num);
	while(1)
    {
        if(p->order==num)break;//�ҵ����ߵ�ͷ��break
        if(p->next==NULL)break;
        q=p;
        p=p->next;

    }
    if(p->order==num)//�ҵ���
    {
        printf("                           ���ҵ���ɾ����Ϣ��\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                           ȷ���Ƿ�ɾ������Y:1 N:0��");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==L)
                L=p->next;//ɾͷָ��
            else
                q->next=p->next;
            p=L;
            p->order=1;
            for(i=2;p->next!=NULL;i++)//��order
            {
                p=p->next;
                p->order=i;
            }
        }
        saveFile(L);
        flag=1;
    }
    if(p->next==NULL&&flag==0) printf("                                ɾ����Ϣ������\n");
	return L;
}
/*������Ʒ��Ϣ */
void insert_good(GOOD *L,GOOD e)
{
	GOOD* p=L;
	int i;
	GOOD *s=(GOOD *)malloc(sizeof(GOOD));//���½ڵ㣬����
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
        for(i=2;p->next!=NULL;i++)//��ֵorder
        {
            p=p->next;
            p->order=i;
        }


	saveFile(L);
}
/*�޸Ĺ�������Ϣ*/
void cover_offer(GOOD* L)
{

    int num;
    GOOD* p=L;
    char offer[20];
    printf("\n\n\n\n\n\n                     ��������޸���Ʒ��ţ�");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;

    }
    if(p->order==num)
    {
        printf("                     ���ҵ����޸���Ϣ\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     ��������ĺ�Ĺ�������Ϣ��");
        scanf("%s",offer);
        strcpy(p->offer,offer);
        printf("                     ���ĺ����ϢΪ��\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
    if(p->next==NULL)printf("                     δ�ҵ����޸���Ϣ\n");
}
/*�޸���Ʒ����*/
void cover_num(GOOD* L)
{
    int num;
    GOOD* p=L;
    int cover;
    printf("\n\n\n\n\n\n                     ��������޸���Ʒ��ţ�");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     ���ҵ����޸���Ϣ\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     ��������ĺ����Ʒ������");
        scanf("%d",&cover);
        p->num=cover;
        printf("                     ���ĺ����ϢΪ��\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
    if(p->next==NULL)printf("                     δ�ҵ����޸���Ϣ\n");
}
/*�޸���Ʒ�۸�*/
void cover_price(GOOD* L)
{
    int num;
    GOOD* p=L;
    int money;
    printf("\n\n\n\n\n\n                     ��������޸���Ʒ��ţ�");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     ���ҵ����޸���Ϣ\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     ��������ĺ����Ʒ�۸�");
        scanf("%d",&money);
        p->price=money;
        printf("                     ���ĺ����ϢΪ��\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
        if(p->next==NULL)printf("                     δ�ҵ����޸���Ϣ\n");
}
/*�޸���Ʒ������*/
void cover_man(GOOD* L)
{
    int num;
    GOOD* p=L;
    char name[20];
    printf("\n\n\n\n\n\n                     ��������޸���Ʒ��ţ�");
    scanf("%d",&num);
    while(1)
    {
        if(p->order==num)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(p->order==num)
    {
        printf("                     ���ҵ����޸���Ϣ\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
        printf("                     ��������ĺ�ľ�������Ϣ��");
        scanf("%s",name);
        strcpy(p->man,name);
        printf("                     ���ĺ����ϢΪ��\n");
        printf("                            %s %d %s %s %d %s %d %d %s\n",p->name,p->list,p->sort,p->state,p->time,p->offer,p->num,p->price,p->man);
    }
        if(p->next==NULL)printf("                     δ�ҵ����޸���Ϣ\n");
}
/*�޸���Ʒ��Ϣ*/
void goods_change(GOOD* L)
{
    int n=3,choose;
    int mark;
    system("cls");
    printf("                      ----------��ѡ���޸�����---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ����������        |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��Ʒ����          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. ��Ʒ�۸�          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. ������            |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);
    system("cls");
    switch(choose)//whileѭ����ʾѭ���޸�
    {
        case 1:
            while(1)
            {
                    cover_offer(L);
                    printf("                            �Ƿ�����޸Ĺ�������Ϣ����Y:1 N:0��");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 2:
            while(1)
            {
                    cover_num(L);
                    printf("                            �Ƿ�����޸���Ʒ��������Y:1 N:0��");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 3:
            while(1)
            {
                    cover_price(L);
                    printf("                            �Ƿ�����޸���Ʒ�۸񣿣�Y:1 N:0��");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        case 4:
            while(1)
            {
                    cover_man(L);
                    printf("                            �Ƿ�����޸ľ�������Ϣ����Y:1 N:0��");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
            }break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/******************************�����Ӻ���******************************/
//�������
void sort_num(GOOD* L)
{
    GOOD* p=L;
    int num[100]={0};
    int order[100];
    int i;
    for(i=0;;i++)//num��order�浽������
    {
        num[i]=p->list;
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){num[i+1]=p->list;order[i+1]=p->order;break;}
    }
    int n=3,choose;
    system("cls");
    printf("\n\n\n\n                      ----------��ѡ����������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��������          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_num(num,order,L);break;
        case 2:sort_desc_num(num,order,L);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*�����������*/
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
            if(num[j]>num[j+1])//ð������
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
    system("cls");//�������
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
    {
        p=L;
        while(p->list!=num[i]||p->order!=order[i])p=p->next;
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        if(i!=0&&(i+1)%10==0)
        {
            system ("pause");
            system("cls");
            printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
            printf("                ��������������������������������������������������������������������������������������\n");
        }
    }



}
/*��Ž�������*/
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
            if(num[j]<num[j+1])//ð������
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
    {
        p=L;
        while(p->list!=num[i]||p->order!=order[i])p=p->next;
        printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
        if(i!=0&&(i+1)%10==0)
        {
            system ("pause");
            system("cls");
            printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
            printf("                ��������������������������������������������������������������������������������������\n");
        }
    }




}
//��������
void sort_name(GOOD* L)
{
    GOOD* p=L;
    char name[100][100];
    char (*name_p)[100];
    int order[100];
    int i;
    for(i=0;;i++)//��name��order
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
    printf("\n\n\n\n                      ----------��ѡ����������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��������          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_name(name_p,L,order,tag);break;
        case 2:sort_desc_name(name_p,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*������������*/
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
            if(strcmp(name[j],name[j+1])>0)//����ð��
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(name[i],p->name)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
/*���ƽ�������*/
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(name[i],p->name)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
//��������
void sort_time(GOOD* L)
{
    GOOD* p=L;
    int time[100]={0};
    int order[100];
    int i;
    for(i=0;;i++)//time��order������
    {
        time[i]=p->time;
        order[i]=p->order;
        p=p->next;
        if(p->next==NULL){time[i+1]=p->time;order[i+1]=p->order;break;}
    }
    int tag=i+2;
    int n=3,choose;
    system("cls");
    printf("\n\n\n\n                      ----------��ѡ����������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��������          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_time(time,L,order,tag);break;
        case 2:sort_desc_time(time,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*������������*/
void sort_pose_time(int time[],GOOD* L,int order[],int n)
{
    int i,j;
    int temp;
    GOOD* p=L;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(time[j]>time[j+1])//��ð��*3
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(p->time!=time[i]||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
/*���ڽ�������*/
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(p->time!=time[i]||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
//����������
void sort_offer(GOOD* L)
{
    GOOD* p=L;
    char offer[100][100];
    char (*offer_p)[100];
    int order[100];
    int i;
    for(i=0;;i++)//��������
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
    printf("\n\n\n\n                      ----------��ѡ����������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��������          |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                 ��ѡ��:");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:sort_pose_offer(offer_p,L,order,tag);break;
        case 2:sort_desc_offer(offer_p,L,order,tag);break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*��������������*/
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
            if(strcmp(offer[j],offer[j+1])>0)//��򵥵�ð��
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(offer[i],p->offer)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
/*�����̽�������*/
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
    printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
    printf("                ��������������������������������������������������������������������������������������\n");
    for(i=0;i<n;i++)
        {
            p=L;
            while(strcmp(offer[i],p->offer)!=0||order[i]!=p->order)p=p->next;
            printf("                |%6s|%6d|%10s|%6s|%10d|%19s|%6d|%6d|%8s|\n",p->name,p->list, p->sort,p->state,p->time,p->offer,p->num,p-> price,p->man );
            if(i!=0&&(i+1)%10==0)
            {
                system ("pause");
                system("cls");
                printf("\n\n\n\n                | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
                printf("                ��������������������������������������������������������������������������������������\n");
            }
        }
}
/******************************����Ա����******************************/
/*�������Ա*/
void add_user(USER* head)//������Ʒ������
{
    system("cls");
	USER us;
	printf("\n\n\n\n                            ��������������Ա��Ϣ\n");
	printf("                              ����Ա�˺�:");
	scanf("%s",us.name);
	printf("                              ����Ա���룺");
	scanf("%d",&us.key);
	insert_user(head,us);
}
/*ɾ������Ա*/
USER* user_deleat(USER* L)//������Ʒ��ɾ��
{

    USER* p=L;
    USER* q;
    int i;
    char name[100];
    int n,flag=0;
    printf("                         ������Ҫɾ���Ĺ���Ա������");
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
        printf("                           ���ҵ���ɾ����Ϣ��\n");
        printf("                            %s %d\n",p->name,p->key);
        printf("                           ȷ���Ƿ�ɾ������Y:1 N:0��");
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
    if(p->next==NULL&&flag==0) printf("                                ɾ����Ϣ������\n");
	return L;
}
/*�������Ա*/
void insert_user(USER *L,USER e)//������Ʒ�Ĳ���
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
/*�鿴ȫ������Ա*/
void user_list(USER* head)//������Ʒ��ȫ���鿴
{
     USER* p;
     p=head;
     printf("\n\n\n\n                                        |  �˺�  |  ����  |\n");
     printf("                                        |%8s|%8d|\n",p->name,p->key);
     while(p->next!=NULL)
     {
         p=p->next;
         printf("                                        |%8s|%8d|\n",p->name,p->key);
     }
}
/*�޸Ĺ���Ա����*/
void user_key(USER* L)//������Ʒ���޸�
{
    int key;
    USER* p=L;
    char name[20];
    printf("\n\n\n\n\n\n                     ��������޸Ĺ���Ա�˻���");
    scanf("%s",name);
    while(1)
    {
        if(strcmp(p->name,name)==0)break;
        if(p->next==NULL)break;
        p=p->next;
    }
    if(strcmp(p->name,name)==0)
    {
        printf("                     ���ҵ����޸���Ϣ\n");
        printf("                            %s %d\n",p->name,p->key);
        printf("                     ��������ĺ�Ĺ���Ա���룺");
        scanf("%d",&key);
        p->key=key;
        printf("                     ���ĺ����ϢΪ��\n");
        printf("                            %s %d\n",p->name,p->key);
    }
    if(p->next==NULL)printf("                     δ�ҵ����޸���Ϣ\n");
    key_saveFile(L);
}
/******************************�鿴ȫ��******************************/
/*����*/
void sort_all(GOOD* L)//ѡ�����������������򱣴�
{
    GOOD *p;
    GOOD *q;
    for(p=L;p!=NULL;p=p->next)
        {
        for(q=p;q!=NULL;q=q->next)
        {
			if(p->time>q->time)
			{
				//����������
				GOOD t=*p;
				*p=*q;
				*q=t;
				//����ָ����
				t.next=p->next;
				p->next=q->next;
				q->next=t.next;
			}
		}

	}
	p=L;
	p->order=1;//��order
	for(int i=2;p->next!=NULL;i++)
    {
        p=p->next;
        p->order=i;
    }
	saveFile(L);//save

}
/*�鿴ȫ����Ʒ*/
void goods_list(GOOD* q)
{

     system("cls");

     sort_all(q);
    while(q!=NULL)//����������
    {
        printf("\n\n\n\n                | ��� | ���� | ��� |   ����   | ״̬ |   ʱ��   |      ������       | ���� | �۸� | ������ |\n");
        printf("                ������������������������������������������������������������������������������������������������\n");
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
/******************************��ҳ��******************************/
/*��Ʒ��Ϣ��ѯ��ҳ��*/
int goods_seek(GOOD* L)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------��ѡ���ѯ����---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ������ѯ          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ���Ʋ�ѯ          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. �۸��ѯ          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. ����+״̬��ѯ     |\n");
    printf("                      |                                |\n");
    printf("                      |           5. ״̬+ʱ���ѯ     |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   ��ѡ��:");
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
/*��Ʒ����鿴��ҳ��*/
int goods_sort(GOOD* L)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------��ѡ����������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. �������          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           3. ��������          |\n");
    printf("                      |                                |\n");
    printf("                      |           4. ����������        |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   ��ѡ��:");
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
/*��Ʒ��Ϣ�޸���ҳ��*/
void goods_cover(GOOD* head,USER* user)
{
    int n=3,choose;
    printf("\n\n\n\n                      ----------��ѡ���޸�����---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ������Ʒ          |\n");
    printf("                      |                                |\n");
    printf("                      |           2. �޸���Ʒ��Ϣ      |\n");
    printf("                      |                                |\n");
    printf("                      |           3. ɾ����Ʒ          |\n");
    n=3;
     while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                    ��ѡ��:");
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
                    printf("                            �Ƿ������ӣ���Y:1 N:0��");
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
                    printf("                            �Ƿ�������ģ���Y:1 N:0��");
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
                    printf("                            �Ƿ����ɾ������Y:1 N:0��");
                    scanf("%d",&choose);
                    if(choose==0){system("cls");break;}
                    if(choose==1)continue;
                }
            }
            break;
            default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}
/*����Աϵͳ��ҳ��*/
USER* administer(USER* head)
    {
    USER* p=head;
    int n=3,choose;
    printf("\n\n\n\n                      ----------��ѡ���������---------\n");
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      |           1. ��������Ա        |\n");
    printf("                      |                                |\n");
    printf("                      |           2. ɾ������Ա        |\n");
    printf("                      |                                |\n");
    printf("                      |           3. �޸Ĺ���Ա����    |\n");
    printf("                      |                                |\n");
    printf("                      |           4. �鿴ȫ������Ա    |\n");
    n=3;
    while(n)
    {
    printf("                      |                                |\n");
    n--;
    }
    printf("                      ----------------------------------\n");
    printf("                                   ��ѡ��:");
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
        printf("��֤ʧ��");

}

/******************************��������******************************/
/*�˳�*/
void goodbye()
{
    system("cls");
	printf("\n\n\n\n\n\n\n\n                                       ��ӭ�´�ʹ��~");
	exit(0);
}
/*����û�*/
int allow(USER* head)
{
    USER*p=head;
    char name[20];
    int key;
    printf("\n\n\n\n\n\n\n\n\n                              �������û�����");
    scanf("%s",&name);
    printf("                              ���������룺");
    scanf("%d",&key);
    if(strcmp(name,p->name)==0 && key==p->key)
    {
        printf("                                   ��֤�ɹ�\n");
        system("pause");
        system("cls");
        return 1;
    }
    while(p->next!=NULL)
    {
        p=p->next;
        if(strcmp(name,p->name)==0 && key==p->key)
    {
        printf("                                   ��֤�ɹ�\n");
        system("pause");
        system("cls");
        return 1;
    }
    }
        printf("                                   ��֤ʧ��\n");
        system("pause");
        system("cls");
        return 0;


}

/*******************************������*******************************/
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
    printf("\n                                      �Ƿ����ʹ��ϵͳ����Y:1 N:0) ");
    scanf("%d",&choose);
    system("cls");
    if(choose==0){goodbye();break;}
    else continue;
    }
}



