#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void seeboard (int a[3][3]);
int victory (int b[3][3]);

int main (void)
{
	int x, y, i, j, sel, turn = 0, win = 0, go, ord, g, h;
	int board[3][3], turnnum[3][3];
	srand(time(NULL));

	printf("Tic-Tac-Toe 게임을 시작합니다.\n\nPlayer vs Player (1)\nPlayer vs Computer (2)\n:");
	scanf("%d", &sel);

	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
			board[i][j] = 0;
	}
	
	system("cls");
	printf("1P는 O, 2P는 X입니다.\n");

	if(sel == 1)                                                                   //*플레이어끼리*
	{
		while(turn < 9 && win == 0)
		{	
			go = 0;
			turn ++;
			printf("turn : %d\n", turn);

			seeboard(board);
			while(go == 0)
			{
				printf("1P의 차례입니다. O를 놓을 위치의 좌표를 입력해주세요. : ");
				scanf("%d %d", &x, &y);
				
				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 1;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				else if(x == 0 && y == 0 && turn > 2)                              //*undo기능*
				{
					for(g = 0;g < 3; g++)
						for(h = 0; h < 3; h++)
							if(turnnum[g][h] == turn-1)
								board[g][h] = 0;
					turn = turn - 2;
					system("cls");
					go = 1;
				}
			}
			win = victory(board);
			if(win == 1 || turn == 9) goto gameover1;



			go = 0;
			turn ++;
			printf("turn : %d\n", turn);

			seeboard(board);
			while(go == 0)
			{
				printf("2P의 차례입니다. X를 놓을 위치의 좌표를 입력해주세요. : ");
				scanf("%d %d", &x, &y);
				
				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 2;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				else if(x == 0 && y == 0 && turn > 2)
				{
					for(g = 0;g < 3; g++)
						for(h = 0; h < 3; h++)
							if(turnnum[g][h] == turn-1)
								board[g][h] = 0;
					turn = turn - 2;
					system("cls");
					go = 1;
				}
			}

			win = victory(board);

		}
gameover1:
		seeboard(board);
		if(win != 0)
			printf("승자는 %dP!\n", win);
		else printf("무승부!\n");
	}



	if(sel == 2)                                                               //*컴퓨터와*
	{
		printf("먼저 하시겠습니까, 뒤에 하시겠습니까?\n선공 (1), 후공 (2)\n:");
		scanf("%d", &ord);
		system("cls");

		if(ord == 1)                                                            //*선공*
		{
		while(turn < 9 && win == 0)
		{	
			go = 0;
			turn ++;
			printf("turn : %d\n", turn);

			seeboard(board);
			while(go == 0)
			{
				printf("1P의 차례입니다. O를 놓을 위치의 좌표를 입력해주세요. : ");
				scanf("%d %d", &x, &y);
				
				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 1;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				else if(x == 0 && y == 0 && turn > 2)
				{
					for(g = 0;g < 3; g++)
						for(h = 0; h < 3; h++)
							if(turnnum[g][h] == turn-1)
								board[g][h] = 0;
					turn = turn - 2;
					system("cls");
					go = 1;
				}
			}
			win = victory(board);
			if(win == 1 || turn == 9) goto gameover2;



			go = 0;
			turn ++;

			while(go == 0)
			{
				printf("2P의 차례입니다.");
				x = 1 + rand() % 3;
				y = 1 + rand() % 3;

				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 2;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				printf("turn : %d\n 2P가 놓은 말의 위치 : (%d, %d)\n", turn, x, y);
			}

			win = victory(board);

		}
		}

		if(ord == 2)                                                            //*후공*
		{
		while(turn < 9 && win == 0)
		{	
			go = 0;
			turn ++;

			while(go == 0)
			{
				printf("1P의 차례입니다.");
				x = 1 + rand() % 3;
				y = 1 + rand() % 3;
				
				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 1;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				printf("turn : %d\n 1P가 놓은 말의 위치 : (%d, %d)\n", turn, x, y);
			}
			win = victory(board);
			if(win == 1 || turn == 9) goto gameover3;



			go = 0;
			turn ++;
			printf("turn : %d\n", turn);

			seeboard(board);
			while(go == 0)
			{
				printf("2P의 차례입니다. X를 놓을 위치의 좌표를 입력해주세요. : ");
				scanf("%d %d", &x, &y);
				
				if(x > 0 && x < 4 && y > 0 && y < 4 && board[x-1][y-1] == 0)
				{
					board[x-1][y-1] = 2;
					turnnum[x-1][y-1] = turn;
					system("cls");
					go = 1;
				}
				else if(x == 0 && y == 0 && turn > 2)
				{
					for(g = 0;g < 3; g++)
						for(h = 0; h < 3; h++)
							if(turnnum[g][h] == turn-1)
								board[g][h] = 0;
					turn = turn - 2;
					system("cls");
					go = 1;
				}
			}

			win = victory(board);

		}
		}

gameover2:
gameover3:
		seeboard(board);
		if(win != 0)
			printf("승자는 %dP!\n", win);
		else printf("무승부!\n");
	}

}



void seeboard (int a[3][3]) //*판을 보는 함수*
{
	int c, d;

	for(c=0; c<3; c++)
	{
		for(d=0; d<3; d++)
		{
			if(a[c][d] == 0)
				printf("ㅁ ");
			else if(a[c][d] == 1)
				printf(" O ");
			else if(a[c][d] == 2)
				printf(" X ");
		}
		printf("\n");
	}
}

int victory (int b[3][3]) //*승부를 확인하는 함수*
{
	if(b[0][0] != 0)
	{
		if(b[0][0] == b[0][1] && b[0][0] == b[0][2])
			return b[0][0];
		if(b[0][0] == b[1][1] && b[0][0] == b[2][2])
			return b[0][0];
		if(b[0][0] == b[1][0] && b[0][0] == b[2][0])
			return b[0][0];
	}
	if(b[1][1] != 0)
	{
		if(b[1][1] == b[0][1] && b[1][1] == b[2][1])
			return b[1][1];
		if(b[1][1] == b[1][0] && b[1][1] == b[1][2])
			return b[1][1];
		if(b[1][1] == b[2][0] && b[1][1] == b[0][2])
			return b[1][1];
	}
	if(b[2][2] != 0)
	{
		if(b[2][2] == b[0][2] && b[2][2] == b[1][2])
			return b[2][2];
		if(b[2][2] == b[2][0] && b[2][2] == b[2][1])
			return b[2][2];
	}
	
	return 0;
}