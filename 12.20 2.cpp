#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define N 5
int num=0,q=0;
char m;//作弊码(加速)
int a[50][50];
//地图
void showmap(void) {
	for(int i=0; i<50; i++) {
		for(int k=0; k<50; k++) {
			if(a[i][k]==1) {
				printf("#");
			}
			if(a[i][k]==0) {
				printf(" ");
			}
		}
		printf("\n");
	}
}//地图的绘制
enum direction {
	up,down,left,right
};//方向的枚举类型定义
void setPos(int x, int y) {
	if(x<0) x=0;
	if(y<0) y=0;
	HANDLE output=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=(short)x;
	pos.Y=(short)y;
	SetConsoleCursorPosition(output,pos);
}//光标函数
struct Snack {
	enum direction dir;//蛇的前进方向
	COORD pos;
	int lengh;//存储蛇//更多细节
};
struct Snack snack;//蛇结构体
void getdir(void) {
	if( (GetAsyncKeyState(VK_UP) & 1) == 1 ) {
		if(snack.dir==down) {
			goto op;
		}
		snack.dir=up;// 向上键被按下过
	} else if((GetAsyncKeyState(VK_DOWN) & 1) == 1 ) {
		if(snack.dir==up) {
			goto op;
		}
		snack.dir=down;
	} else if((GetAsyncKeyState(VK_RIGHT) & 1) == 1 ) {
		if(snack.dir==left) {
			goto op;
		}
		snack.dir=right;
	} else if((GetAsyncKeyState(VK_LEFT) & 1) == 1 ) {
		if(snack.dir==right) {
			goto op;
		}
		snack.dir=left;
	}
op:/*
	setPos(snack.pos.X,snack.pos.Y);
	printf(" ");*/

	if(snack.dir==up) {
		setPos(snack.pos.X,snack.pos.Y-1);
		printf("o");
		snack.pos.Y=snack.pos.Y-1;
		snack.pos.X=snack.pos.X;
	} else if(snack.dir==down) {
		setPos(snack.pos.X,snack.pos.Y+1);
		printf("o");
		snack.pos.Y=snack.pos.Y+1;
		snack.pos.X=snack.pos.X;
	} else if(snack.dir==right) {
		setPos(snack.pos.X+1,snack.pos.Y);
		printf("o");
		snack.pos.Y=snack.pos.Y;
		snack.pos.X=snack.pos.X+1;
	} else if(snack.dir==left) {
		setPos(snack.pos.X-1,snack.pos.Y);
		printf("o");
		snack.pos.Y=snack.pos.Y;
		snack.pos.X=snack.pos.X-1;
	}
	setPos(0,0);
}//接受方向并运动
int movesnack(void) {
	if(a[snack.pos.Y][snack.pos.X]==1) {//在数组中x,y反过来
		return 1;
	} else if(a[snack.pos.Y][snack.pos.X]==0) {
		setPos(snack.pos.X,snack.pos.Y);
		printf("o");
		return 0;
	} else if(a[snack.pos.Y][snack.pos.X]<0) {
		setPos(snack.pos.X,snack.pos.Y);
		printf("o");
		return a[snack.pos.Y][snack.pos.X];
	} else {
		return 1;
	}

}//撞墙判定
void food(void) {
	int x,y;
su:
	x=rand()%50;
	y=rand()%50;
	if(a[y][x]==0) {
		setPos(x,y);
		printf("p");
		a[y][x]=-1;
	} else {
		goto su;
	}
}
void goal(void) {
	setPos(0,0);//使得光标移到(0,0)而非得分前
	setPos(0,50);
	printf("得分为:%d",num);
}

int main() {
	/*printf("贪吃蛇1.0未完成版");
	Sleep(1000);
	system("cls");*/
	printf("贪吃蛇2.0完成版");
	Sleep(1000);
	system("cls");
s:
	FILE *fp1,*fp2,*fp3;
	fp1=fopen("D:\\文件\\代码\\dev c++\\map 1.txt","r");
	fp2=fopen("D:\\文件\\代码\\dev c++\\map 2.txt","r");
	fp3=fopen("D:\\文件\\代码\\dev c++\\map 3.txt","r");
	int elo=0;
	printf("请选择地图:\n");
	scanf("%d",&elo);
	if(elo==1) {
		for(int i=0; i<50; i++) {
			for(int j=0; j<50; j++) {
				fscanf(fp1,"%d",&a[i][j]);
			}
		}
	} else if(elo==2) {
		for(int i=0; i<50; i++) {
			for(int j=0; j<50; j++) {
				fscanf(fp2,"%d",&a[i][j]);
			}
		}
	} else if(elo==3) {
		for(int i=0; i<50; i++) {
			for(int j=0; j<50; j++) {
				fscanf(fp3,"%d",&a[i][j]);
			}
		}
	}
	int n=0,p=0;
	printf("请选择难度:\n1.简单\n2.中等\n3.困难\n");
	scanf("%d",&n);
	if(n==1) {
		q=500;
	} else if(n==2) {
		q=100;
	} else if(n==3) {
		q=50;
	} else {
		return 0;
	}
	system("cls");
	snack.dir=up;
	snack.pos.X=20;
	snack.pos.Y=20;
	snack.lengh=3;
	for(int i=0; i<50; i++) {
		for(int j=0; j<50; j++) {
			if(a[i][j]!=0&&a[i][j]!=1) {
				a[i][j]=0;
			}
		}
	}
	fclose(fp1);
		fclose(fp2);
		fclose(fp3);
	showmap();
	p=q;
	/*for(int i=0;i<snack.lengh;i++){
			a[i+20][20]=2-i+snack.lengh;
			printf("o");
		}*/
	food();
	while(1) {
		int see=0;
		for(int i=0; i<50; i++) {
			for(int j=0; j<50; j++) {
				if(a[j][i]==-2) {
					see=1;
				}
			}
		}
		if((rand()%100<2)&& see==0) {
			int x,y;
su:
			x=rand()%50;
			y=rand()%50;
			if(a[y][x]==0) {
				setPos(x,y);
				printf("$");
				a[y][x]=-2;
			} else {
				goto su;
			}
		}
		if(rand()%100<2) {
			int x,y;
			for(x=0; x<50; x++) {
				for(y=0; y<50; y++) {
					if(a[y][x]==-2) {
						setPos(x,y);
						printf(" ");
						a[y][x]=0;
					}
				}
			}
		}//高额奖励(随机消失)
		int saw=0;
		for(int i=0; i<50; i++) {
			for(int j=0; j<50; j++) {
				if(a[j][i]==-3) {
					saw=1;
				}
			}
		}
		if(saw==0) {

			int x,y;
jia:
			x=rand()%50;
			y=rand()%50;
			if(a[y][x]==0) {
				setPos(x,y);
				printf("@");
				a[y][x]=-3;
			} else {
				goto jia;
			}
		}
		if(((int)clock()/100)%50==0) {
			int x,y;
			for(x=0; x<50; x++) {
				for(y=0; y<50; y++) {
					if(a[y][x]==-3) {
						setPos(x,y);
						printf(" ");
						a[y][x]=0;
					}
				}
			}
		}//高额奖励(定时消失)
		if(num%3==0&&(GetAsyncKeyState(VK_DELETE)&1)==1) {
			for(int i=0; i<50; i++) {
				for(int k=0; k<50; k++) {
					if(a[i][k]!=1&&a[i][k]!=0&&a[i][k]!=-1) {
						setPos(0,0);
						setPos(k,i);
						printf("^");
						setPos(0,0);
					}
				}
			}
		}//在得分为3的倍数时按下delete键蛇身体变为^型
		if((GetAsyncKeyState(VK_MENU)&1)==1) {
			p=(int)(q/4);//按下alt键加速4倍
		} else if((GetAsyncKeyState(VK_SPACE)&1)==1) {
			p=(int)(q/10);//按下空格键加速10倍
		} else {
			p=q;
		}
		int sub=0;
		for(int i=0; i<50; i++) {
			for(int k=0; k<50; k++) {
				if(a[i][k]>2) {
					a[i][k]--;
					sub++;
				} else if(a[i][k]==2) {
					setPos(0,0);
					setPos(k,i);
					printf(" ");
					setPos(0,0);
					a[i][k]=0;
				}
			}
		}
		if(sub>100) {
			system("cls");
			printf("爽不爽，就不让你赢，哈哈哈\nGame over!");
			return 0;
		}
		goal();//得分
		setPos(0,0);
		setPos(0,51);
		printf("%d",(int)clock());
		setPos(0,0);
		getdir();//运动
		/*for(int i=0; i<50; i++) {
			for(int k=0; k<50; k++) {
				if(a[i][k]==2) {
					a[i][k]=0;
				}
			}
		}*/
		if(movesnack()==1) {
			int m;
			setPos(0,50);
			printf("Game over\n");
			Sleep(500);
			system("cls");
			printf("do you want to play again?\nif so,press '1'\nelse,press '0'\n");
			scanf("%d",&m);
			if(m==1) {
				num=0;
				Sleep(500);
				system("cls");
				/*for(int i=0; i<50; i++) {
									for(int k=0; k<50; k++) {
										if(a[i][k]==100) {
											a[i][k]=0;
										}
										else if(a[i][k]>100){
											a[i][k]--;
										}
									}
								}*/
				goto s;
			} else  {
				/*system("cls");
				printf("have a nice day!\nGoodbye!!!");
				Sleep(1000);*/
				return 0;
			}
			return 0;
		}//结束判定
		else if(movesnack()==0) {
			a[snack.pos.Y][snack.pos.X]=2+snack.lengh;
			setPos(0,0);
			Sleep(p);

		} else if(movesnack()==-1) {
			a[snack.pos.Y][snack.pos.X]=2+snack.lengh;
			num++;
			snack.lengh++;
			for(int i=0; i<50; i++) {
				for(int k=0; k<50; k++) {
					if(a[i][k]>2) {
						a[i][k]++;
					}
				}
			}
			/*snack.lengh++;*/
			setPos(0,0);
			Sleep(p);
			food();
		} else if(movesnack()==-2) {
			a[snack.pos.Y][snack.pos.X]=2+snack.lengh;
			num=num+3;
			snack.lengh=snack.lengh+3;
			for(int i=0; i<50; i++) {
				for(int k=0; k<50; k++) {
					if(a[i][k]>2) {
						a[i][k]++;
					}
				}
			}
			/*snack.lengh++;*/
			setPos(0,0);
			Sleep(p);
		} else if(movesnack()==-3) {
			a[snack.pos.Y][snack.pos.X]=2+snack.lengh;
			num=num+3;
			snack.lengh=snack.lengh+3;
			for(int i=0; i<50; i++) {
				for(int k=0; k<50; k++) {
					if(a[i][k]>2) {
						a[i][k]++;
					}
				}
			}
			/*snack.lengh++;*/
			setPos(0,0);
			Sleep(p);
		}
	}
	
}
