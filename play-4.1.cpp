#include<bits/stdc++.h>
using namespace std;
#define KO 500
const int jie=17,xf=11,df=12,ft=13,xi=14,la=15,md=16;
const int xb=1,db=2,zm=3,dib=4,pb=5,pib=6,qb=7,qlb=8,jlb=10;
const int sh=9,qls=18,jls=19,sjmr=0;
int costx[25]={15,1,2,3,4,5,6,7,8,1,10,0,0,0,0,0,0,-1,1,1};
int costy[25]={15,1,2,3,4,5,6,7,8,1,10,0,0,0,0,0,0,-1,1,1};
const int biao[20][20]={0, 0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

						2, 0,1,2,2, 2,2,2,2,0, 2,0,0,2,0, 0,0,0,0,0,
						2, 0,0,1,2, 2,2,2,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,1, 2,2,2,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,0, 1,2,2,2,0, 2,0,0,0,0, 0,0,0,0,0, 
						2, 0,0,0,0, 0,1,2,2,0, 2,0,0,0,0, 0,0,0,0,0,
						
						2, 0,0,0,0, 0,0,1,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,0, 0,0,0,1,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,0, 0,0,0,0,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 2,2,2,2, 2,0,0,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						
						2, 0,0,2,2, 2,2,2,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 2,2,0,0, 0,2,2,2,0, 2,0,0,0,0, 0,1,0,0,0,
						2, 0,2,2,2, 2,2,2,2,0, 2,0,0,0,0, 0,0,0,0,0,
						2, 0,0,0,0, 0,2,2,2,0, 2,0,0,0,0, 2,0,0,0,0,
						2, 2,2,2,2, 2,2,2,2,0, 2,0,0,0,0, 0,1,0,0,0,
						
						2, 0,1,2,2, 2,2,2,2,0, 2,0,0,1,0, 0,0,0,0,0,
						2, 2,2,2,2, 2,2,2,2,0, 2,0,0,0,0, 0,1,0,0,0,
						2, 2,2,2,2, 2,2,2,0,0, 2,0,0,0,0, 0,1,0,0,0,
						2, 2,2,2,2, 2,2,2,2,0, 0,0,0,0,0, 0,1,0,0,0,
						
};//biao[x][y]: A use x B use y A lose blood? 
char s[20][15]={"[世界末日 -15]","[笑波 -1]","[电波 -2]","[致命 -3]","[地波 -4]","[骗波 -5]","[派波 -6]","[气波 -7]","[青龙波 -8]","[收 -1]","[金龙波 -10]","[小防 0]","[大防 0]","[反弹 0]","[吸 0]","[拉 0]","[免单 0]","[结 +1]","[青龙收 -1]","[金龙收 -1]"};
int bldx=2,bldy=2;
int ptx=2,pty=2;
bool usex_md=0,usey_md=0;
bool zb=0;
int win[30][30][20],lose[30][30][20];
double pc[30][30][20];

struct tt{
	int num;
	int id;
	bool operator <(const tt& pp) const{
		return num>pp.num;
	}
}tmp[33];
struct node{
	int ptx,pty,yy;
}ttt[505];
int qq=0;
int a[30],cnt;
double mn;
int sum[21];
int lose_blood(int x,int y)
{
	bldx-=x;
	bldy-=y;
	if(bldx<=0) return -1;
	if(bldy<=0) return 1;
	return 0;
}
int check(int x,int y)//x win 1  y win -1
{
	if(x==xi&&(y>=1&&y<=5)) ptx+=y;
	if(y==xi&&(x>=1&&x<=5)) pty+=x;
	return lose_blood(biao[x][y],biao[y][x]);
}
void p_lose_blood(int x,int y,int tmp)
{
	bldx-=x;
	bldy-=y;
	if(bldx<=0) sum[tmp]+=KO;
	if(bldy<=0) sum[tmp]-=KO;
	bldx+=x;
	bldy+=y;
}
void p_check(int x,int y,int tmp)//x win 1  y win -1
{
	if(x==xi&&(y>=1&&y<=5)) sum[tmp]-=y;
	if(y==xi&&(x>=1&&x<=5)) sum[tmp]+=x;
	p_lose_blood(biao[x][y],biao[y][x],tmp);
}
int cp_choose()
{
	memset(sum,-1,sizeof(sum));
	for(int i=0;i<=19;i++)
	{
		if(costy[i]>pty) continue;
		sum[i]=10000;
		for(int j=0;j<=19;j++)
		{
			if(costx[j]>ptx) continue;
			sum[i]=sum[i]+costx[j]-costy[i];
			p_check(j,i,i);
		}
		tmp[i].num=sum[i];
		tmp[i].id=i;
	}
	sort(tmp,tmp+20);
	int cnt=23;
	for(int i=1;i<=7;i++)  a[i]=tmp[1].id;
	for(int i=8;i<=12;i++)  a[i]=tmp[2].id;
	for(int i=13;i<=16;i++)  a[i]=tmp[3].id;
	for(int i=17;i<=19;i++)  a[i]=tmp[4].id;
	for(int i=20;i<=21;i++)  a[i]=tmp[5].id;
	a[22]=17;
	a[23]=tmp[6].id;
	int www;
	while(1)
	{
		www=rand()%cnt+1;
		int yy=a[www];
		if(costy[yy]>pty) continue;
		if(ptx<=5&&yy==sh) continue;
		if(ptx<=7&&yy==qls) continue;
		if(ptx<=9&&yy==jls) continue;
		if(ptx<=2&&yy==df) continue;
		if(pty==0&&yy==la) continue;
		if(costy[yy]<=pty) return yy;
	}
} 

void play()
{
	int xx,yy;
	printf("你的血量：%d/2 电脑血量：%d/2\n",bldx,bldy);
	printf("你的点数：%d 电脑点数：%d\n",ptx,pty);
	printf("请你选择：\n");
	yy=cp_choose();
	for(int i=0;i<=19;i++)
		if(costx[i]<=ptx) printf("%d: %s\n",i,s[i]);
	
	if(zb) printf("电脑选择 %s\n",s[yy]);
	scanf("%d",&xx);
	if(xx==114514)
	{
		printf("作弊模式开始！\n");
		zb=1;
		return;
	}
	if(costx[xx]>ptx||xx<0||xx>19)
	{
		printf("你自爆了。\n");
		system("pause");
		exit(0);
	}
	mn=-0.1;
	
	ttt[++qq]=node{ptx,pty,yy};
	printf("你选择了 %s, 电脑选择了 %s\n",s[xx],s[yy]);
	ptx-=costx[xx];
	pty-=costy[yy];
	if(xx==16) costx[16]=100000000;
	if(yy==16) costy[16]=100000000;
	int ggg=check(xx,yy);
	if(ggg==1)
	{
		printf("You Win!!!");
		system("pause");
		exit(0);
	}
	if(ggg==-1)
	{
		printf("You lose!!!");
		system("pause");
		exit(0);
	}
	if(ptx>=25)
	{
		printf("你已达点数上限：25\n");
		ptx=25; 
	}
	if(pty>=25)
	{
		printf("电脑已达点数上限：25\n");
		pty=25; 
	}
}
int main()
{ 
	srand(time(0));
//	int ta;
	printf("提示：输入114514进入作弊模式！\n");
	system("pause");
	while(1) play();
	return 0;
}

