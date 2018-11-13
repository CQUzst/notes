#include <stdio.h>  
#include <windows.h>  
#include <time.h>  
#include <conio.h>     
#include <iostream.h>

//-------------------------------------------------------------------
void GotoXY(int x, int y)      //设定输出位置
{  
	COORD c;  
	c.X = x-1;  
	c.Y = y-1;  
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);  
} 
//-----------------------------------------------------------------
void color(int a)              //颜色函数
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
struct HeroList
{
	char Name[10];
	int Highscore;
}Hero[10];
//----------------------------------------------------------
void Save()                    //存储最高分及名字
{
	FILE *fp;
	if((fp=fopen("Hero_list","wb"))==NULL)
	{cout<<"can not open file!"<<endl;return;}
	if(fwrite(&Hero[0],sizeof(struct HeroList),1,fp)!=1)
		cout<<"file write error!"<<endl;
	fclose(fp);
}
//**********************************************************
class CSnake
{
     int image[20][20];        //游戏面板，即小蛇活动范围
     int FoodX;                //事物出现的X坐标
     int FoodY;                //事物出现的Y坐标
     int snakeX;               //记录小蛇的头部X坐标
     int snakeY;               //记录小蛇的头部Y坐标
     int head;                 //小蛇头部下标
     int tail;                 //小蛇尾部下标
     int snake[2][2000];         //记录小蛇所有身体的坐标
     int node;                 //小蛇的节数
	 int direction;            //小蛇头部的方向        
     int i,j;   	
	 int gamespeed;            //速度
	 int score;                //记录分数
	 char arrowKey;            //接受按键的变量
	 int GameOver;             //使游戏结束的变量
	 int level;                //设置等级
	 int length;               //为了设置等级而与node一样记录设的长度
public:
	 
	CSnake()        //构造函数初始化部分变量
	{
        head=3;                //初始化头部下标
        tail=0;                //初始化尾部下标
        node=4;                //小蛇初始节数为4节
    	gamespeed=300;         //游戏速度（移动的间隔时间）
    	score=0;               //初始化分数为0
        direction=6;           //小蛇的初始方向向右
		GameOver=0;            //进入游戏初始化为0
		level=1;
		length=4;
	}
	~CSnake()     //析构函数
	{}	
	void Init();                //初始化游戏面板及小蛇的坐标
	int  DrawSnake();           //记录小蛇每次移动后头部及身体的下一坐标
	void  Automove();            //使小蛇自动移动
    int  Gameover();            //判断游戏是否结束
	int  Generatefood();        //产生食物
	void display();             //显示游戏面板
	void shiftLeft();           //控制左移
	void shiftRight();          //控制右移
	void shiftDown();           //控制下移
	void shiftUp();	            //控制上移
	int  PlayGame();            //执行游戏的函数
	void Setspeed();            //设置速度
	int Pause();                //游戏的暂停
};
//-------------------------------------- -------------------------------
 void CSnake::Init()             //初始化部分数据
{
	 
 for(i=0;i<20;i++)                   //初始化游戏面板
   for(j=0;j<20;j++)    
	image[i][j]=0;
 for(i=0;i<4;i++)                    //初始化小蛇初始位置
    { snake[0][i]=1;
      snake[1][i]=i+1;
    }
 for(i=1;i<=3;i++)                   //初始化小蛇坐标的显示值(即初始化小蛇显示图形对应的值)
        image[1][i]=3; 
   image[1][4]=1;
}
//---------------------------------------------------------------
int CSnake::Gameover()                //判断游戏是否结束
{
  if(snakeX<0 || snakeX>19 ||snakeY<0 || snakeY>19)                       // 碰到墙壁游戏结束
  {  
	  GotoXY(1,25);   
      cout << "Game over!" << endl;
      GameOver=1;
     return GameOver;
  }
  if((image[snakeX][snakeY]!=0)&&!(snakeX==FoodX&&snakeY==FoodY))         //蛇头碰到蛇身游戏结束
   { 
	  GotoXY(1,25); 
	  cout << "Game over!" << endl;
	  GameOver=1;
	  return GameOver;
  }
  return 0;
}
//----------------------------------------------------------------
int CSnake::DrawSnake()
{   if(snakeX==FoodX && snakeY==FoodY)                                  //若小蛇头部坐标与食物坐标重叠则吃掉食物
     {                                
      node++;                                                           // 小蛇节数增一
      score+=10;                                                        //分数增加  
	  length++;
	  if(length>=8)                                                     //当小蛇增长到8个时，等级加一
	  {length-=8;
	  level++;}
      image[snakeX][snakeY]=1;                                           //小蛇头部移动的下一位置头部图像对应的值赋给图像
      image[snake[0][head]][snake[1][head]] = 3;                         //小蛇头部其后紧跟的身体一格移动的下一位置头部图像对应的值赋给图像
      head=(head+1)%10000;
      snake[0][head] = snakeX;                                           //将小蛇头部此时的坐标值赋给记录头部坐标的snake[0][head]
      snake[1][head] = snakeY;
      Generatefood();                                                    //吃掉食物后再次随机分布食物
	  display();                                                         //刷新显示
       
      }
     else
     {                                                                    //没有吃食物
      image[snake[0][tail]][snake[1][tail]]=0;                            //擦去小蛇尾部
      tail=(tail+1)%10000;                                                
      image[snake[0][head]][snake[1][head]]=3;                            //小蛇头部其后紧跟的身体一格移动的下一位置头部图像对应的值赋给图像
      head=(head+1)%10000;
      snake[0][head]=snakeX;                                              //将小蛇头部此时的坐标值赋给记录头部坐标的snake[0][head]
      snake[1][head]=snakeY;
      image[snake[0][head]][snake[1][head]]=1;                            //小蛇头部移动的下一位置头部图像对应的值赋给图像
      display(); 
      }
 
  return 0;
}
//-----------------------------------------------------------
void CSnake::shiftLeft()                                                 //左移则小蛇蛇头方向向左
{	
    direction=4;       
}
//++++++++++++++++++++++++++
void CSnake::shiftRight()                                                //右移则小蛇蛇头方向向右
{
    direction=6;       
}
//+++++++++++++++++++++++++++
void CSnake::shiftUp()                                                    //上移则小蛇蛇头方向向上
{
    direction=8;       
}	
//+++++++++++++++++++++++++++
void CSnake::shiftDown()                                                  //下移则小蛇蛇头方向向下
{     
    direction=2;       
}
//------------------------------------------------------
void CSnake::Automove()
{
	switch(direction)
	{                                                                 
	case 6:snakeX= snake[0][head]; snakeY= snake[1][head]+1;break;          //接收到向右的信息小蛇头部Y坐标加一，X坐标不变并赋给记录头部坐标的变量
	case 4:snakeX= snake[0][head]; snakeY= snake[1][head]-1;break;         //接收到向左的信息小蛇头部Y坐标减一，X坐标不变并赋给记录头部坐标的变量
	case 8:snakeX= snake[0][head]-1; snakeY= snake[1][head];break;          //接收到向上的信息小蛇头部X坐标加一，Y坐标不变并赋给记录头部坐标的变量
	case 2:snakeX= snake[0][head]+1; snakeY= snake[1][head];break;          //接收到向下的信息小蛇头部X坐标加一，Y坐标不变并赋给记录头部坐标的变量
    default:;
	}
}
//--------------------------------------------------------------------- 
int CSnake::Generatefood()                                        // 产生食物
{  
	srand(time(0));                                               //以时间为种子生成随机序列
	do{ 
     FoodX=rand()%20;                                             //食物输出的X坐标
     FoodY=rand()%20;                                             //食物输出的Y坐标
	}while(image[FoodX][FoodY]!=0);                               //产生的食物坐标限定在游戏面板内，且食物坐标不与小蛇身体坐标重合
    image[FoodX][FoodY]=2;
 return image[FoodX][FoodY];
}
//----------------------------------------------------------------
void CSnake::display()                                            // 显示游戏面板（包括围墙、食物及小蛇）
{  
	color(10);
    GotoXY(1,1);
    for(i=0;i<22;i++)  
    printf("■");  
    GotoXY(1,2); 
    for(i=0;i<20;i++)  
	{	color(10);
	printf("■");  
	for(j=0;j<20;j++)  
	{
		switch(image[i][j])  
		{
		case 0:color(15);printf("  ");break;  
		case 1:color(11);printf("□");break;
		case 2:color(12);printf("☆");break; 
		case 3:color(13);printf("●");break;
		}
	}  color(10);
	printf("■\n");
}  
	color(10);
for(i=0;i<22;i++)  
printf("■");  color(13);
GotoXY(46,9); printf("SCORE:%d",score);         //记录分数
GotoXY(46,10); printf("LEVEL=%d",level);         //记录等级
color(12);
GotoXY(46,5); printf("本程序由张亚超编写！\n");
GotoXY(46,6); printf("版权所有！侵权必究！");
}
//----------------------------------------------------
void CSnake::Setspeed()                           //设置小蛇移动的速度
{  
	int Esc=0; 
	while(!Esc)
	{
		int speed;
				color(12);
				cout<<"1.Very Slow   2.Slow   3.Normal   4.Fast   5.Very Fast "<<endl;
				cout<<"请输入您的选择：";
				cin>>speed;
				switch(speed)
				{
				case 0:
					Esc=1;
					gamespeed=300;
					break;
				case 1:
					gamespeed=300;
					Esc=1;
					break;
				case 2:
					gamespeed=200;
					Esc=1;
					break;
				case 3:
					gamespeed=80;
					Esc=1;
					break;
			   case 4:
					gamespeed=30;
					Esc=1;
					break;
			  case 5:
					gamespeed=12;
					Esc=1;
					break;
				}
	}
}
//-----------------------------------------------------------
int CSnake::Pause()                   //暂停功能
{
    char c;  
   // GotoXY(1,25);printf("Pause! ");  
    do  
	{c=getch();}  
	while(c!='p');  
	arrowKey=0;
	return arrowKey;
} 
//--------------------------------------------   
//**************************************************************
int CSnake::PlayGame()                                        //执行游戏函数
 {
   Init();                                                    //初始化数据
   Generatefood();                                            //产生食物
   display();                                                 //显示游戏面板
	while (!GameOver) 		
    {		
        if(kbhit())                                            //接受按键
		{
          arrowKey = getch();
        }	
			if(direction==2||direction==8)                     //当小蛇的头部移动方向为上下时，左右键才起作用
			{
              switch(arrowKey)
              {
			  case'6':shiftRight();break;
			  case'4':shiftLeft();break;				  
			  case'e':exit(1);break;
			  case'p':Pause();break;
			  default:break;
               }		
			}
			else if(direction==4||direction==6)                 //当小蛇的头部移动方向为左右时，上下键才起作用
			{
		      switch(arrowKey)                        
			  {
			  case'8':shiftUp();break;
			  case'5':shiftDown();break;				 
			  case'e':exit(1);break;				  
			  case'p':Pause();break;
			  default:break;
			  }				
			}   
			Sleep(gamespeed);                                 //小蛇移动一格的速度
			Automove();			                              // 校舍自动移动
			Gameover();                                       //判断游戏是否结束
			if(GameOver==1)                                   //若游戏结束，则直接跳出循环
				break;
			DrawSnake();                                      //判断是否吃食物
			display();                                        //显示游戏面板
	}
	Hero[0].Highscore=score;
	getch();
	return 0;
}
//**************************************************************************
void Welcome(void)                                           //欢迎界面
{
	printf("                                                                                ");color(13);
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
	printf("                                                                                ");
	printf("                                                                                ");
	printf("                                                                                ");color(14);
	printf("                                                                                ");
	printf("  ■■■■■    ■■■        ■■      ■■■      ■■       ■  ■■■■■■ ");
	printf("■■■■■■■  ■■■■      ■■    ■■■■■    ■■      ■   ■■■■■■ ");
	printf("■■■  ■■■  ■■ ■■     ■■   ■■    ■■   ■■    ■     ■■         ");
	printf("■■■          ■■  ■■    ■■  ■■      ■■  ■■  ■       ■■         ");
	printf("  ■■■■      ■■   ■■   ■■  ■■      ■■  ■■ ■        ■■■■■■ ");
	printf("   ■■■■■   ■■    ■■  ■■  ■■■■■■■  ■■■         ■■■■■■ ");
	printf("        ■■■  ■■     ■■ ■■  ■■■■■■■  ■■ ■        ■■         ");
	printf("■■■  ■■■  ■■      ■■■■  ■■      ■■  ■■   ■      ■■         ");
	printf("■■■■■■■  ■■        ■■■  ■■      ■■  ■■     ■    ■■■■■■ ");
	printf("  ■■■■■    ■■          ■■  ■■      ■■  ■■      ■■ ■■■■■■ ");
	printf("                                                                                ");
	printf("                                                                                ");color(13);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");color(10);
	printf("【C++语言贪吃蛇游戏】张亚超编写!!! 版权所有，侵权必究!\n");
	printf("[上移：8 ；下移：5 ；左移：4 ；右移：6 ； 暂停：P； 退出：E]\n");								
	system("pause");
	system("cls");
}


//----------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////
void main()                                        //主函数
{ 	
	CSnake SNAKE;
	char Name[10]=" ";
//	int Highscore=0;
	char ch;
	char Get=0;
//	int i;
	Welcome();
	while(1)
	{    
		color(14);                                                  // 主界面
		cout<<"     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^     "<<endl;
		cout<<"   -----* - * - * - * - * - * - *----   "<<endl;
		cout<<"   $   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁   $      "<<endl;
		cout<<"   $   ▏                          ▏ $      "<<endl;
		cout<<"   $   ▏       1.开始游戏         ▏ $      "<<endl;
		cout<<"   $   ▏       2.设置速度         ▏ $      "<<endl;
		cout<<"   $   ▏       3.使用说明         ▏ $      "<<endl;
		cout<<"   $   ▏       4.英雄榜           ▏ $      "<<endl;
		cout<<"   $   ▏       5.退出             ▏ $      "<<endl;
		cout<<"   $   ▏                          ▏ $      "<<endl;
		cout<<"   $   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔   $      "<<endl;
		cout<<"   -----* - * - * - * - * - * - *----   "<<endl;
		cout<<"     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^     "<<endl;
		cin>>ch;
		
		if(ch=='1')
		{	
			system("cls");
			SNAKE.PlayGame();
			system("cls");
			if(Hero[0].Highscore<100)
			{cout<<"您还需努力哟!"<<endl;cout<<endl;}
			else if(400>Hero[0].Highscore&&Hero[0].Highscore>200)
			{cout<<"您一定是高手!"<<endl;cout<<endl;}
			else if(600>Hero[0].Highscore&&Hero[0].Highscore>400)
			{	cout<<"您实在太厉害了!"<<endl;cout<<endl;}
			else
			{	cout<<"您一定是骨灰级玩家!佩服!佩服!"<<endl;cout<<endl;}
			if(Hero[0].Highscore>200)
			{
			cout<<"请输入您的大名：";
			cin>>Hero[0].Name;			
			Save();		
			}
			system("pause");
			system("cls");	
			break;
		}
		else if(ch=='2')
		{
			system("cls");
			SNAKE.Setspeed();
			system("pause");
			system("cls");
			continue;
		}
		else if(ch=='3')                                               //详细使用说明
		{
			system("cls");
			cout<<"                                                    "<<endl;
			cout<<"                                                    "<<endl;color(14);
			cout<<"    *********************************************** "<<endl;color(12);
			cout<<"    *   上移：8 ;       左移：4 ;    暂停：P      * "<<endl;
			cout<<"    *   下移：5 ;       右移：6 ;    退出：E      * "<<endl;color(14); 
			cout<<"    *********************************************** "<<endl;color(12);
			cout<<"    $        按相应的键可以控制小蛇的移动!        $ "<<endl;
			cout<<"    $         通过控制小蛇的移动来吃食物！        $ "<<endl;
			cout<<"    $当小蛇的头部撞到墙壁或自己的身体时，游戏结束!$ "<<endl;color(14);
			cout<<"    #-------------------------------------------- # "<<endl;
			cout<<"    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
			cout<<"                                                    "<<endl;
			cout<<"                                                    "<<endl;
			system("pause");
			system("cls");
			continue;
		}
		else if(ch=='4')                                             // 记录最高分，显示英雄榜
		{
			system("cls");
			color(10);
			FILE *fp;
			fp=fopen("Hero_list","rb");
			fread(&Hero[0],sizeof(struct HeroList),1,fp);
			cout<<"$#######_---   英雄榜：  ---_#######$"<<endl;
			cout<<"               名字:"<<Hero[0].Name<<endl;
			cout<<"               最高分:"<<Hero[0].Highscore<<endl;
			cout<<"--------------------------------------------"<<endl;
			fclose(fp);
			system("pause");
			system("cls");			
			continue;
		}
		else if(ch=='5')
		{
			system("cls");
			exit(0);
		}
		else
		{
			system("cls");
			cout<<"请重新输入！"<<endl;	
			continue;
		}
	}	
		
} 
	
	
