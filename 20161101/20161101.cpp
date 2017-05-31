#include<stdio.h>
#include<Windows.h> 
#include<string.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h> 
#include <time.h> 

void GameStart(); //본격적인 메모리게임을 시작합니다.
void HowToPlay(); //게임방법을 보여줍니다.
void gotoxy(int, int); //좌표함수
void Backgrond(); //격자표를 출력해줍니다.
void Cursor(); //커서이동
void InitUser(int, int); // User[j][i]에 저장된 값에 따라 도형을 출력
void InitCom(int, int); // Com[j][i]에 저장된 값에 따라 도형을 출력
void random(int); //랜덤수를 생성하여 Com[3][4] 배열에 랜덤한 수를 저장
void Count(); // 3초를 카운트하고 문제를 지운다.
int Match(); //컴퓨터가 낸 문제와 사용자가 입력한 값을 비교하여 정답/오답을 가린다.
void Heart(int); //목숨 표시
void Fresh(); //배열을 초기화한다.

int Com[3][4]; //컴퓨터가 낸 문제를 저장하는 배열
int User[3][4]; //사용자가 입력한 값을 저장하는 배열
int Point; //한판 성공할 때마다 1씩 올라가는 점수 변수
int h = 3; //처음 목숨 3 
int r;

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} //좌표함수

int main(void)
{
	system("mode con: cols=40 lines=11"); //콘솔창 사이즈
	char k; //문자 값을 받는 변수 

			//원하는 위치에 메뉴 출력
	gotoxy(4, 1);
	printf("☆★☆2015 메모리 게임☆★☆ \n");
	gotoxy(7, 2);
	printf("made by 김보경\n\n");
	gotoxy(12, 4);
	printf("게임시작 S");
	gotoxy(12, 5);
	printf("게임방법 H");
	gotoxy(12, 6);
	printf("종료E");
	gotoxy(1, 8);

	while (1)
	{
		srand((unsigned)time(NULL)); //main문 시작과 함께 랜덤수 생성을 위한 난수를 생성한다.
									 //입력한 문자 값에 따라 각 메뉴에 해당하는 페이지로 넘어간다.
		printf("Select menu! --> ");
		k = getchar();
		if (k == 'S' || k == 's') {
			while (getchar() != '\n'); //채터링방지
			GameStart();
			break;
		}
		else if (k == 'H' || k == 'h') {
			while (getchar() != '\n');
			HowToPlay();
			break;
		}
		else if (k == 'E' || k == 'e')
		{
			break;
		}
		else
		{
			printf("\n다시 입력해주세요.\n");
		}
	}
}

void GameStart() //본격적인 메모리게임을 시작합니다.
{
	int m = 2;
	Sleep(1000); //1초 delay
	for (int t = 1; t<4; t++)
	{
		system("cls"); //전의 화면을 모두 지운다.
		gotoxy(20, 5); //좌표설정
		printf("%d \n", t);
		Sleep(1000); //1초 단위로 출력
	}// 1초 씩 총 3초를 카운트한다.

	gotoxy(15, 6); //좌표설정
	printf("START!");
	Sleep(1000);
	system("cls"); //화면을 모두 지운다. 
	Backgrond(); //게임의 배경이 되는 격자무늬 출력

	while (1) {
		random(m);//렌덤한 수를 입력하여 배열에 렌덤수를 저장하고 문제를낸다.
		Count();// 3초를 카운트하고 문제를 지운다.
		Cursor(); //커서를 움직이면서 도형을 입력
		Match();//비교매치, Point 값을 반환한다. 

		if (h == 0) //목숨이 0이면
		{
			system("cls"); //모든화면지우고
			gotoxy(15, 5);
			printf("Game over\n");
			break; //while 문을 나가면서 game over 프로그램종료
		}
		// printf("%d", Point);
		Fresh(); //배열 초기화
				 //난이도조절 m은 렌덤함수에 들어가는 변수이다. 이 m을 조정함으로써 렌덤수를 만드는 범위를 조정한다.
		if (Point<5) //5판 깨면
			m = 2; //렌덤수 2개 0,1 만든다. 
		else if (Point>4 && Point<10) //6판~10판
			m = 3; //렌덤수 3개 0,1,2 만든다.
		else if (Point>9) //11판~ 죽을때까지
			m = 4; //렌덤수 4개 0,1,2,3 만든다.
	}
}
void HowToPlay() //게임방법을 보여줍니다.
{
	int key; //화면을 넘기기위해 키보드 값을 받는 변수
	Sleep(1000); //1초 delay
	system("cls"); //이전 화면을 지우고
	printf("<게임방법>\n\n");

	while (_kbhit() != 1) //kbhit()은 어떤 키도 입력으로 생각하는 함수이다. 어떤 키가 눌릴때까지 반복
	{
		printf("위치와 색상을 기억하세요!\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //색 표현
		puts("●빨간색은 1");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		puts("●파란색은 2");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		puts("●노란색은 3번 space bar를 누르세요");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //원래 회색으로 돌아온다.
		gotoxy(33, 10);
		printf("Next▶");

		key = _getch(); //어떤 키를 받는다.

		if (_kbhit() == 0) //누르면 
		{
			system("cls"); //이전 화면을 모두 지우고
			break; //while 문을 나온다.
		}
	}

	puts("\n상하좌우이동 - 화살표키\n블록놓기 - 스페이스바\n결정 - 엔터\n취소 - 스페이스바 4번\n"); //게임방법 
	gotoxy(33, 10);
	printf("Menu▶");

	key = _getch(); //어떤 키를 받는다.
	system("cls");
	if (_kbhit() == 0) //누르면 
	{
		system("cls"); //이전 화면을 모두 지우고
		Sleep(1000);
		main(); //초기 화면으로 돌아간다.
	}
}
void Backgrond(void) //격자무늬를 출력한다.
{
	unsigned char z = 0xa6;
	int a, b;

	// 맨 윗단 그리기
	printf("%c%c", z, 0xa3);
	for (a = 0; a<3; a++) {
		printf("%c%c", z, 0xa1);
		printf("%c%c", z, 0xa8);
	}
	printf("%c%c", z, 0xa1);
	printf("%c%c", z, 0xa4);
	//중간
	for (b = 0; b<2; b++)
	{
		printf("\n");
		for (a = 0; a<5; a++)
		{
			printf("%c%c", z, 0xa2);
			printf("  ");
		}
		printf("\n");
		printf("%c%c", z, 0xa7);
		for (a = 0; a<3; a++)
		{
			printf("%c%c", z, 0xa1);
			printf("%c%c", z, 0xab);
		}
		printf("%c%c", z, 0xa1);
		printf("%c%c", z, 0xa9);
	}
	//맨 밑단
	printf("\n");
	b = 2;
	for (a = 0; a<5; a++)
	{
		printf("%c%c", z, 0xa2);
		printf("  ");
	}
	printf("\n");
	printf("%c%c", z, 0xa6);
	for (a = 0; a<3; a++)
	{
		printf("%c%c", z, 0xa1);
		printf("%c%c", z, 0xaa);
	}
	printf("%c%c", z, 0xa1);
	printf("%c%c", z, 0xa5);
	Heart(3); //맨처음에는 목숨 3개 출력
}

void Fresh() //배열 초기화함수
{
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			User[a][b] = 0;
			Com[a][b] = 0;
		}
	}
}

void InitUser(int i, int j) //i,j 값을 받아와서 User[j][i]에 저장된 값에 따라 도형을 출력
{
	int x = 4 * i + 3, y = 2 * j + 2; //i,j값에 따른 격자칸으로 이동하기 위해
	if (User[j][i] == 0)
	{
		gotoxy(x, y); //격자 칸으로 이동하여
		printf("  ");
	} //0 이면 공백을 출력한다

	else if (User[j][i] == 1)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("●");
	} //1 이면 빨간색도형 출력
	else if (User[j][i] == 2)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("●");
	}//2면 파란색도형
	else if (User[j][i] == 3)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("●");
	}//3이면 노란색도형
	gotoxy(1, 7);
}
void InitCom(int i, int j) //i,j 값을 받아와서 Com[j][i]에 저장된 값에 따라 도형을 출력
{
	int x = 4 * i + 3, y = 2 * j + 2; //i,j값에 따른 격자칸으로 이동하기 위해

	if (Com[j][i] == 0)
	{
		gotoxy(x, y); //격자 칸으로 이동하여
		printf("  ");
	} //0 이면 공백을 출력한다.

	else if (Com[j][i] == 1)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("●");
	} //1 이면 빨간색도형 출력
	else if (Com[j][i] == 2)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("●");
	}//2면 파란색도형
	else if (Com[j][i] == 3)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("●");
	}//3이면 노란색도형
}

void Cursor(void)  //커서이동
{
	int i = 0, j = 0; //배열에 넣을 변수
	int x = 4 * i + 4, y = 2 * j + 2; //배열에 따라 격자칸 좌표 위치, 
									  //격자칸의 위치와 배열요소들을 대응시키기 위해 이렇게 선언하였다.
	int chr; //키보드 값을 받는 변수

	while (1)
	{
		gotoxy(x, y);
		chr = _getch();
		//키보드 값 상하좌우를 움직임에 따라 i,j값을 정한다. 즉 배열요소를 정한다.
		//상
		if (chr == 72)
		{
			j--;
			if (j<0)j = 0; //j가 0이하로 내려가지않도록한다. 격자안에서만 움직이도록하기 위함&선언한 배열값은3by4므로
		}
		//하
		else if (chr == 80)
		{
			j++;
			if (j>2)j = 2; //j가 2이상으로 올라가지않도록한다.격자안에서만 움직이도록하기 위함&선언한 배열값은3by4므로
		}
		//좌
		else if (chr == 75)
		{
			i--;
			if (i<0)i = 0;//i가 0이하로 내려가지않도록한다. 격자안에서만 움직이도록하기 위함&선언한 배열값은3by4므로
		}
		//우
		else if (chr == 77)
		{
			i++;
			if (i>3)i = 3;//i가 3이상으로 올라가지않도록한다.격자안에서만 움직이도록하기 위함&선언한 배열값은3by4므로
		}

		x = 4 * i + 3, y = 2 * j + 2;
		gotoxy(x, y); // 위에서 정한 i,j 값을 이용하여 좌표를 정하고 그 좌표로 이동한다.

		if (chr == 32)
		{ //스페이스바 아스키코드 32. 스페이스바를 누르면
			User[j][i] += 1; //해당 배열에 1추가 
			if (User[j][i]>3) //3보다크면 즉 스페이스바를 4번 누르면
				User[j][i] = 0; //다시 0으로초기화 
		}
		InitUser(i, j); // 도형 출력

		if (chr == 13) //Enter아스키코드 13. 엔터누르면 입력완료.
			break;
	}
}

void random(int m) //랜덤수를 생성하여 Com[3][4] 배열에 랜덤한 수를 저장.
				   //m은 렌덤함수에 들어가는 변수이다. 이 m을 조정함으로써 렌덤수를 만드는 범위를 조정한다.
{
	int a, b, r;
	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 4; b++)
		{
			r = rand() % m;//렌덤수를 생성하여서
			Com[a][b] = r; //배열에 저장
			InitCom(b, a); //도형출력
		}
	}
}

void Count() // 3초를 카운트하고 문제를 지운다.
{
	for (int k = 3; k>0; k--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //원래 회색으로     
		gotoxy(30, 5);
		printf("%d", k);
		Sleep(1000);
	} //3초 카운트

	gotoxy(30, 5);
	printf("  ");// 숫자지우기

	int i = 0, j = 0;
	int x = 4 * i + 3, y = 2 * j + 2;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			gotoxy(4 * i + 3, 2 * j + 2);
			printf("  ");
		}
	}//문제를 지운다.
}

int Match() //컴퓨터가 낸 문제와 사용자가 입력한 값을 비교하여 정답/오답을 가린다.
{
	int a = 0;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (User[j][i] == Com[j][i])
				a += 1; //일치하면 1추가
			else if (User[j][i] != Com[j][i])
				a += 0; //불일치시 0추가
		}
	} //각각의 배열요소를 비교한다.
	if (a == 12) { //즉 12개의 배열요소 모두 다 같다면
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); //녹색
		gotoxy(1, 8);
		Point += 1;
		printf("%d판 깨기 성공!", Point); //점수를 하나씩 올린다. 그리고 출력.
	}
	else if (a<12) //하나라도 달라서 12보다 작다면
	{
		gotoxy(27, 4);
		printf("      "); //원래 하트 출력되어있던것을 지우고
		--h; //목숨을 하나씩 줄인다.
		Heart(h); //하트출력
	}
	return Point; //점수를 반환
}

void Heart(int h) //목숨값을 받아와서
{
	gotoxy(27, 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); //적색SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int k = h; k > 0; k--) //목숨에 맞게 하트출력
		printf("♥");
}