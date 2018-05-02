#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define ROW_X 16
#define ROW 28
#define COLUMN 12
#define BEGIN_X 24
#define BEGIN_Y 0
#define D_TIMER 1
#define UP_TIMER 2

int game_array[ROW][COLUMN] = { 0 };//��Ϸ������
int forecast_array[4][4] = { 0 };//Ԥ��������
int Block[19][4][4];//��������
char Color[7];//��ɫ����

void SetXY(int x, int y);//���ù������
void Hidden(); //���ع��
void Display();////��ʾ��ʼ���棬��ʾ������Ϸ
void StartGame();//��Ϸ��ʼ����ʼ��
void DrawGameFrame();//����Ϸ�߿�
void DisplaySpace();//����ʾ��
void ForecastSpace();//��ʾ��һ���������
void CreateBlock();//�������䷽��
void GameSpace();//��Ϸ������ʾ
void Down();//��������
void FullSpace();//�̶�����
void Left();//��������
void Right();//��������
void Shape();//�������
void Contrl();//��Ϸ����
void SpeedUp();//�����������
int Change(int blockID);//�����µķ�����
int IsBottom();//�жϷ����Ƿ����䵽�ײ�
int IsRBorder();//�жϷ����Ƿ񵽴��ұ߽�
int IsLBorder();//�жϷ����Ƿ񵽴���߽�
int CheckDown();//�жϷ����Ƿ�������
int CheckAround();//�жϷ����Ƿ��������ƶ�
void IsOver();//�ж���Ϸ�Ƿ����
void RemoveRow();//��������
void GameOver();//��Ϸ����
void SetLevel();//���õȼ�
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);//��ʱ���ص�����

/*UINT_PTR SetTimer(  HWND hWnd,              // handle to window
UINT_PTR nIDEvent,      // timer identifier
UINT uElapse,           // time-out value
TIMERPROC lpTimerFunc   // timer procedure
);���ö�ʱ��

LONG yourWndProc(HWND hWnd,UINT uMessageType,WPARAM wP,LPARAM)

VOID CALLBACK TimerProc(
HWND hwnd,         // handle to window
UINT uMsg,         // WM_TIMER message
UINT_PTR idEvent,  // timer identifier
DWORD dwTime       // current system time
);��ʱ���ص�����*/


//��ɫ����
char Color[7] =
{
	(0x03),
	(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY),
	(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY),
	(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY),
	(FOREGROUND_RED | FOREGROUND_INTENSITY),
	(FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
};

//��������
int Block[19][4][4] = 
{
	{//0����
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 }
	},
	{//1����
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	},
	{//2����
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 }
	},
	
	{//3Z��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 1 }
	},
	{//4Z��
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 }
	},
	
	{//5��Z��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 1, 0 }
	},
	{//6��Z��
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 }
	},
	
	{//7L��
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 }
	},
	{//8L��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 }
	},
	{//9L��
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 }
	},
	{//10L��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 1, 0, 0 }
	},
	
	{//11��L��
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	},
	{//12��L��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 1 }
	},
	{//13��L��
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 }
	},
	{//14��L��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 0, 1 }
	},
	{//15T��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 1, 0 }
	},
	{//16T��
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 }
	},
	{//17T��
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 1 }
	},
	{//18T��
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 }
	},
};




