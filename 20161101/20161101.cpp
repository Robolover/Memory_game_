#include<stdio.h>
#include<Windows.h> 
#include<string.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h> 
#include <time.h> 

void GameStart(); //�������� �޸𸮰����� �����մϴ�.
void HowToPlay(); //���ӹ���� �����ݴϴ�.
void gotoxy(int, int); //��ǥ�Լ�
void Backgrond(); //����ǥ�� ������ݴϴ�.
void Cursor(); //Ŀ���̵�
void InitUser(int, int); // User[j][i]�� ����� ���� ���� ������ ���
void InitCom(int, int); // Com[j][i]�� ����� ���� ���� ������ ���
void random(int); //�������� �����Ͽ� Com[3][4] �迭�� ������ ���� ����
void Count(); // 3�ʸ� ī��Ʈ�ϰ� ������ �����.
int Match(); //��ǻ�Ͱ� �� ������ ����ڰ� �Է��� ���� ���Ͽ� ����/������ ������.
void Heart(int); //��� ǥ��
void Fresh(); //�迭�� �ʱ�ȭ�Ѵ�.

int Com[3][4]; //��ǻ�Ͱ� �� ������ �����ϴ� �迭
int User[3][4]; //����ڰ� �Է��� ���� �����ϴ� �迭
int Point; //���� ������ ������ 1�� �ö󰡴� ���� ����
int h = 3; //ó�� ��� 3 
int r;

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} //��ǥ�Լ�

int main(void)
{
	system("mode con: cols=40 lines=11"); //�ܼ�â ������
	char k; //���� ���� �޴� ���� 

			//���ϴ� ��ġ�� �޴� ���
	gotoxy(4, 1);
	printf("�١ڡ�2015 �޸� ���ӡ١ڡ� \n");
	gotoxy(7, 2);
	printf("made by �躸��\n\n");
	gotoxy(12, 4);
	printf("���ӽ��� S");
	gotoxy(12, 5);
	printf("���ӹ�� H");
	gotoxy(12, 6);
	printf("����E");
	gotoxy(1, 8);

	while (1)
	{
		srand((unsigned)time(NULL)); //main�� ���۰� �Բ� ������ ������ ���� ������ �����Ѵ�.
									 //�Է��� ���� ���� ���� �� �޴��� �ش��ϴ� �������� �Ѿ��.
		printf("Select menu! --> ");
		k = getchar();
		if (k == 'S' || k == 's') {
			while (getchar() != '\n'); //ä�͸�����
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
			printf("\n�ٽ� �Է����ּ���.\n");
		}
	}
}

void GameStart() //�������� �޸𸮰����� �����մϴ�.
{
	int m = 2;
	Sleep(1000); //1�� delay
	for (int t = 1; t<4; t++)
	{
		system("cls"); //���� ȭ���� ��� �����.
		gotoxy(20, 5); //��ǥ����
		printf("%d \n", t);
		Sleep(1000); //1�� ������ ���
	}// 1�� �� �� 3�ʸ� ī��Ʈ�Ѵ�.

	gotoxy(15, 6); //��ǥ����
	printf("START!");
	Sleep(1000);
	system("cls"); //ȭ���� ��� �����. 
	Backgrond(); //������ ����� �Ǵ� ���ڹ��� ���

	while (1) {
		random(m);//������ ���� �Է��Ͽ� �迭�� �������� �����ϰ� ����������.
		Count();// 3�ʸ� ī��Ʈ�ϰ� ������ �����.
		Cursor(); //Ŀ���� �����̸鼭 ������ �Է�
		Match();//�񱳸�ġ, Point ���� ��ȯ�Ѵ�. 

		if (h == 0) //����� 0�̸�
		{
			system("cls"); //���ȭ�������
			gotoxy(15, 5);
			printf("Game over\n");
			break; //while ���� �����鼭 game over ���α׷�����
		}
		// printf("%d", Point);
		Fresh(); //�迭 �ʱ�ȭ
				 //���̵����� m�� �����Լ��� ���� �����̴�. �� m�� ���������ν� �������� ����� ������ �����Ѵ�.
		if (Point<5) //5�� ����
			m = 2; //������ 2�� 0,1 �����. 
		else if (Point>4 && Point<10) //6��~10��
			m = 3; //������ 3�� 0,1,2 �����.
		else if (Point>9) //11��~ ����������
			m = 4; //������ 4�� 0,1,2,3 �����.
	}
}
void HowToPlay() //���ӹ���� �����ݴϴ�.
{
	int key; //ȭ���� �ѱ������ Ű���� ���� �޴� ����
	Sleep(1000); //1�� delay
	system("cls"); //���� ȭ���� �����
	printf("<���ӹ��>\n\n");

	while (_kbhit() != 1) //kbhit()�� � Ű�� �Է����� �����ϴ� �Լ��̴�. � Ű�� ���������� �ݺ�
	{
		printf("��ġ�� ������ ����ϼ���!\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //�� ǥ��
		puts("�ܻ������� 1");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		puts("���Ķ����� 2");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		puts("�ܳ������ 3�� space bar�� ��������");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //���� ȸ������ ���ƿ´�.
		gotoxy(33, 10);
		printf("Next��");

		key = _getch(); //� Ű�� �޴´�.

		if (_kbhit() == 0) //������ 
		{
			system("cls"); //���� ȭ���� ��� �����
			break; //while ���� ���´�.
		}
	}

	puts("\n�����¿��̵� - ȭ��ǥŰ\n��ϳ��� - �����̽���\n���� - ����\n��� - �����̽��� 4��\n"); //���ӹ�� 
	gotoxy(33, 10);
	printf("Menu��");

	key = _getch(); //� Ű�� �޴´�.
	system("cls");
	if (_kbhit() == 0) //������ 
	{
		system("cls"); //���� ȭ���� ��� �����
		Sleep(1000);
		main(); //�ʱ� ȭ������ ���ư���.
	}
}
void Backgrond(void) //���ڹ��̸� ����Ѵ�.
{
	unsigned char z = 0xa6;
	int a, b;

	// �� ���� �׸���
	printf("%c%c", z, 0xa3);
	for (a = 0; a<3; a++) {
		printf("%c%c", z, 0xa1);
		printf("%c%c", z, 0xa8);
	}
	printf("%c%c", z, 0xa1);
	printf("%c%c", z, 0xa4);
	//�߰�
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
	//�� �ش�
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
	Heart(3); //��ó������ ��� 3�� ���
}

void Fresh() //�迭 �ʱ�ȭ�Լ�
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

void InitUser(int i, int j) //i,j ���� �޾ƿͼ� User[j][i]�� ����� ���� ���� ������ ���
{
	int x = 4 * i + 3, y = 2 * j + 2; //i,j���� ���� ����ĭ���� �̵��ϱ� ����
	if (User[j][i] == 0)
	{
		gotoxy(x, y); //���� ĭ���� �̵��Ͽ�
		printf("  ");
	} //0 �̸� ������ ����Ѵ�

	else if (User[j][i] == 1)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("��");
	} //1 �̸� ���������� ���
	else if (User[j][i] == 2)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("��");
	}//2�� �Ķ�������
	else if (User[j][i] == 3)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("��");
	}//3�̸� ���������
	gotoxy(1, 7);
}
void InitCom(int i, int j) //i,j ���� �޾ƿͼ� Com[j][i]�� ����� ���� ���� ������ ���
{
	int x = 4 * i + 3, y = 2 * j + 2; //i,j���� ���� ����ĭ���� �̵��ϱ� ����

	if (Com[j][i] == 0)
	{
		gotoxy(x, y); //���� ĭ���� �̵��Ͽ�
		printf("  ");
	} //0 �̸� ������ ����Ѵ�.

	else if (Com[j][i] == 1)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("��");
	} //1 �̸� ���������� ���
	else if (Com[j][i] == 2)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("��");
	}//2�� �Ķ�������
	else if (Com[j][i] == 3)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("��");
	}//3�̸� ���������
}

void Cursor(void)  //Ŀ���̵�
{
	int i = 0, j = 0; //�迭�� ���� ����
	int x = 4 * i + 4, y = 2 * j + 2; //�迭�� ���� ����ĭ ��ǥ ��ġ, 
									  //����ĭ�� ��ġ�� �迭��ҵ��� ������Ű�� ���� �̷��� �����Ͽ���.
	int chr; //Ű���� ���� �޴� ����

	while (1)
	{
		gotoxy(x, y);
		chr = _getch();
		//Ű���� �� �����¿츦 �����ӿ� ���� i,j���� ���Ѵ�. �� �迭��Ҹ� ���Ѵ�.
		//��
		if (chr == 72)
		{
			j--;
			if (j<0)j = 0; //j�� 0���Ϸ� ���������ʵ����Ѵ�. ���ھȿ����� �����̵����ϱ� ����&������ �迭����3by4�Ƿ�
		}
		//��
		else if (chr == 80)
		{
			j++;
			if (j>2)j = 2; //j�� 2�̻����� �ö����ʵ����Ѵ�.���ھȿ����� �����̵����ϱ� ����&������ �迭����3by4�Ƿ�
		}
		//��
		else if (chr == 75)
		{
			i--;
			if (i<0)i = 0;//i�� 0���Ϸ� ���������ʵ����Ѵ�. ���ھȿ����� �����̵����ϱ� ����&������ �迭����3by4�Ƿ�
		}
		//��
		else if (chr == 77)
		{
			i++;
			if (i>3)i = 3;//i�� 3�̻����� �ö����ʵ����Ѵ�.���ھȿ����� �����̵����ϱ� ����&������ �迭����3by4�Ƿ�
		}

		x = 4 * i + 3, y = 2 * j + 2;
		gotoxy(x, y); // ������ ���� i,j ���� �̿��Ͽ� ��ǥ�� ���ϰ� �� ��ǥ�� �̵��Ѵ�.

		if (chr == 32)
		{ //�����̽��� �ƽ�Ű�ڵ� 32. �����̽��ٸ� ������
			User[j][i] += 1; //�ش� �迭�� 1�߰� 
			if (User[j][i]>3) //3����ũ�� �� �����̽��ٸ� 4�� ������
				User[j][i] = 0; //�ٽ� 0�����ʱ�ȭ 
		}
		InitUser(i, j); // ���� ���

		if (chr == 13) //Enter�ƽ�Ű�ڵ� 13. ���ʹ����� �Է¿Ϸ�.
			break;
	}
}

void random(int m) //�������� �����Ͽ� Com[3][4] �迭�� ������ ���� ����.
				   //m�� �����Լ��� ���� �����̴�. �� m�� ���������ν� �������� ����� ������ �����Ѵ�.
{
	int a, b, r;
	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 4; b++)
		{
			r = rand() % m;//�������� �����Ͽ���
			Com[a][b] = r; //�迭�� ����
			InitCom(b, a); //�������
		}
	}
}

void Count() // 3�ʸ� ī��Ʈ�ϰ� ������ �����.
{
	for (int k = 3; k>0; k--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //���� ȸ������     
		gotoxy(30, 5);
		printf("%d", k);
		Sleep(1000);
	} //3�� ī��Ʈ

	gotoxy(30, 5);
	printf("  ");// ���������

	int i = 0, j = 0;
	int x = 4 * i + 3, y = 2 * j + 2;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			gotoxy(4 * i + 3, 2 * j + 2);
			printf("  ");
		}
	}//������ �����.
}

int Match() //��ǻ�Ͱ� �� ������ ����ڰ� �Է��� ���� ���Ͽ� ����/������ ������.
{
	int a = 0;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (User[j][i] == Com[j][i])
				a += 1; //��ġ�ϸ� 1�߰�
			else if (User[j][i] != Com[j][i])
				a += 0; //����ġ�� 0�߰�
		}
	} //������ �迭��Ҹ� ���Ѵ�.
	if (a == 12) { //�� 12���� �迭��� ��� �� ���ٸ�
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); //���
		gotoxy(1, 8);
		Point += 1;
		printf("%d�� ���� ����!", Point); //������ �ϳ��� �ø���. �׸��� ���.
	}
	else if (a<12) //�ϳ��� �޶� 12���� �۴ٸ�
	{
		gotoxy(27, 4);
		printf("      "); //���� ��Ʈ ��µǾ��ִ����� �����
		--h; //����� �ϳ��� ���δ�.
		Heart(h); //��Ʈ���
	}
	return Point; //������ ��ȯ
}

void Heart(int h) //������� �޾ƿͼ�
{
	gotoxy(27, 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); //����SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int k = h; k > 0; k--) //����� �°� ��Ʈ���
		printf("��");
}