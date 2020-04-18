#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

void viewarray(int org[][80]);		//배열을 출력하는 함수
void nextgene(int org[][80]);		//다음세대를 원래 배열에 저장하는 함수

int main() {
	int org_arr[22][80];			//22x80인 2차원 배열로 인생게임의 셀들을 나타낸다
	int i, j;

	srand((unsigned int)time(NULL));			//시간별로 난수를 생성시키는 랜덤함수

	for (i = 0; i < 22; i++)
		for (j = 0; j < 80; j++)
			org_arr[i][j] = rand() % 2;			//각 셀들에 0 또는 1을 할당한다

	viewarray(org_arr);							//최초의 모습을 보여준다
	for (i = 0; i < 500; i++) {
		nextgene(org_arr);
		viewarray(org_arr);
	}

}

void nextgene(int org[][80]) {
	int a, b, i, r, around = 0;
	int new_arr[22][80];

	for (i = 0; i < 22; i++) {			//가로 세로를 전부 확인하는 이중 for문
		for (r = 0; r < 80; r++) {

			for (a = -1; a < 2; a++) {			//어떤 셀의 주변에 존재하는 이웃셀(1)이 몇개있는지 확인하기위한 이중for문
				for (b = -1; b < 2; b++) {

					if (i + a >= 0 && i + a < 22) {			//행이 -1이거나 22를 넘어가는 경우를 배제
						if (r + b >= 0 && r + b < 80) {		//열이 -1이거나 80을 넘어가는 경우를 배제
							if (a!=0 || b!=0)						//그리고 그 자신의 셀을 배제
							around = around + org[i + a][r + b];	//변수 around에 이웃이 존재하는 경우를 차례차례 저장
						}
					}
				}	
			}

			if (around < 2 || around > 3)	//주변에 이웃셀이 0개, 1개 이거나 3개보다 많으면 그 셀은 사망
				new_arr[i][r] = 0;
			else if (around == 3)			//이웃이 딱 세개면 새로운 셀이출생
				new_arr[i][r] = 1;
			else if (around == 2)			//이웃이 두개면 원래 상태를 유지
			{
				if (org[i][r] == 0)
					new_arr[i][r] = 0;
				else
					new_arr[i][r] = 1;
			}

			around = 0;			//around 초기화
		}
	}

	for (i = 0; i < 22; i++) {			//새로운 배열을 원래의 배열에 저장한다
		for (r = 0; r < 80; r++)
			org[i][r] = new_arr[i][r];
	}
	for (i = 0; i < 22; i++)			//다시 입력받아야할 배열을 초기화시킨다
		for (r = 0; r < 80; r++)
			new_arr[i][r] = 0;

}

void viewarray(int org[][80]) {
	int i, r;

	for (i = 0; i < 22; i++) {		//셀이 존재하면 *을, 없으면 _를 출력한다
		for (r = 0; r < 80; r++) {
			if (org[i][r] == 1)
				cout << "*";
			else
				cout << "_";
		}
	}
	Sleep(300);		//300ms딜레이
	system("cls");	//화면을 지운다

}