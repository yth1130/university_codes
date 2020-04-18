#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

void viewarray(int org[][80]);		//�迭�� ����ϴ� �Լ�
void nextgene(int org[][80]);		//�������븦 ���� �迭�� �����ϴ� �Լ�

int main() {
	int org_arr[22][80];			//22x80�� 2���� �迭�� �λ������� ������ ��Ÿ����
	int i, j;

	srand((unsigned int)time(NULL));			//�ð����� ������ ������Ű�� �����Լ�

	for (i = 0; i < 22; i++)
		for (j = 0; j < 80; j++)
			org_arr[i][j] = rand() % 2;			//�� ���鿡 0 �Ǵ� 1�� �Ҵ��Ѵ�

	viewarray(org_arr);							//������ ����� �����ش�
	for (i = 0; i < 500; i++) {
		nextgene(org_arr);
		viewarray(org_arr);
	}

}

void nextgene(int org[][80]) {
	int a, b, i, r, around = 0;
	int new_arr[22][80];

	for (i = 0; i < 22; i++) {			//���� ���θ� ���� Ȯ���ϴ� ���� for��
		for (r = 0; r < 80; r++) {

			for (a = -1; a < 2; a++) {			//� ���� �ֺ��� �����ϴ� �̿���(1)�� ��ִ��� Ȯ���ϱ����� ����for��
				for (b = -1; b < 2; b++) {

					if (i + a >= 0 && i + a < 22) {			//���� -1�̰ų� 22�� �Ѿ�� ��츦 ����
						if (r + b >= 0 && r + b < 80) {		//���� -1�̰ų� 80�� �Ѿ�� ��츦 ����
							if (a!=0 || b!=0)						//�׸��� �� �ڽ��� ���� ����
							around = around + org[i + a][r + b];	//���� around�� �̿��� �����ϴ� ��츦 �������� ����
						}
					}
				}	
			}

			if (around < 2 || around > 3)	//�ֺ��� �̿����� 0��, 1�� �̰ų� 3������ ������ �� ���� ���
				new_arr[i][r] = 0;
			else if (around == 3)			//�̿��� �� ������ ���ο� �������
				new_arr[i][r] = 1;
			else if (around == 2)			//�̿��� �ΰ��� ���� ���¸� ����
			{
				if (org[i][r] == 0)
					new_arr[i][r] = 0;
				else
					new_arr[i][r] = 1;
			}

			around = 0;			//around �ʱ�ȭ
		}
	}

	for (i = 0; i < 22; i++) {			//���ο� �迭�� ������ �迭�� �����Ѵ�
		for (r = 0; r < 80; r++)
			org[i][r] = new_arr[i][r];
	}
	for (i = 0; i < 22; i++)			//�ٽ� �Է¹޾ƾ��� �迭�� �ʱ�ȭ��Ų��
		for (r = 0; r < 80; r++)
			new_arr[i][r] = 0;

}

void viewarray(int org[][80]) {
	int i, r;

	for (i = 0; i < 22; i++) {		//���� �����ϸ� *��, ������ _�� ����Ѵ�
		for (r = 0; r < 80; r++) {
			if (org[i][r] == 1)
				cout << "*";
			else
				cout << "_";
		}
	}
	Sleep(300);		//300ms������
	system("cls");	//ȭ���� �����

}