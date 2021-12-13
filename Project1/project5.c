#include <stdio.h>
#include <time.h>


//����Ⱑ 6�����ִ�
//�̵��� ���׿� ����ִµ� �縷�̴�.
//�縷�� �ʹ� ���� �����Ͽ� ���� ���� ������ �����Ѵ�.
//���� �� �����ϱ� ���� �������� ���׿� ���� �༭ ����⸦ ������Ѵ�.

int level;
int arrayFish[6];
int* cursor;

void initData();
void printFishes();
void decreaseWater();

int main(void)
{
	long startTime = 0; //���� ���� �ð�
	long totalElapsedTime = 0; //�� ��� �ð�
	long prevElapsedTime = 0; //���� ��� �ð�(�ֱٿ� ���� �� �ð� ����)

	int num; // �� �� ���׿� ���� �� ������, ����� �Է�
	initData();

	cursor = arrayFish; 

	startTime = clock(); //����ð��� ms ������ ��ȯ

	while (1)//���ѹݺ�
	{
		printFishes();
		printf("�� �� ���׿� ���� �ֽðھ��? \n");
		scanf_s("%d", &num);

		//�Է°� üũ
		if (num < 1 || num>6)
		{
			printf("�Է°��� �߸��Ǿ����ϴ�.\n");
			continue; //�ٽ� ���� �ö�
		}

		//�Ѱ���ð�
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC; //�Ѱ���ð� = ����ð� - starttime. CLOCKS_PER_SEC�� ms�� �ʴ����� �ٲ�
		printf("�� ��� �ð� : %ld ��\n", totalElapsedTime);

		//���� �� �� �ð� (���������� �� �ؽð�) ���ķ� �帥 �ð�
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("�ֱ� ��� �ð� : %ld ��\n", prevElapsedTime);

		//������ ���� ����(����)
		decreaseWater(prevElapsedTime);

		//����ڰ� �Է��� ���׿� ���� �ش�
		//1. ������ ���� 0�̸�? ���� ���� �ʴ´�. �̹� ����� ����
		if (cursor[num - 1] <= 0)
		{
			printf("%d�� ������ �̹� �׾����ϴ�. ���� ���� �ʽ��ϴ�.\n", num);
		}
		
		//2. ������ ���� 0�� �ƴѰ��. ���� �ش�.(100�� ���� �ʴ��� üũ)
		else if (cursor[num - 1] + 1 <= 100)
		{
			printf("%d �� ���׿� ���� �ݴϴ� \n\n",num);
			cursor[num - 1] += 1; //cursor[num-1] = cursor[num-1] + 1
		}

		//�������� �Ұ��� Ȯ��(�������� 20�ʸ��� �ѹ��� ����)
		if (totalElapsedTime / 20 > level-1)
		{
			level++;
			printf("*** �� ������ ! ���� %d �������� %d ������ ���׷��̵� ***\n\n", level - 1, level);

			//�������� : 5
			if (level == 5)
			{
				printf("\n\n�����մϴ�. �ְ� ������ �޼��Ͽ����ϴ�. ������ �����մϴ�.\n\n");
				exit(0);
			}
		}
	}

	//��� ����Ⱑ �׾����� Ȯ��
	if (checkFishAlive() == 0)
	{
		//����� ��� ����
		printf("��� ������ �׾����ϴ�\n\n");
		exit(0);
	}
	else
	{
		//�ּ� �Ѹ��� �̻��� ������ �������
		printf("������ ���� ����ֽ��ϴ�!\n");
	}
	prevElapsedTime = totalElapsedTime;

	return 0; 
}

void initData()
{
	level = 1; //���� ����(1~5)
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] = 100; //������ �� ����(0~100)
	}
}

void printFishes()
{
	printf(" %3d�� %3d�� %3d�� %3d�� %3d�� %3d��\n ", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++)
	{
		printf(" %4d ", arrayFish[i]);
	}
	printf("\n\n");
}

void decreaseWater(long elapsedTime)
{
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] -= (level * 3 * (int)elapsedTime); // 3�� ���̵� ������ ���� ��
		if (arrayFish[i] < 0)
		{
			arrayFish[i] = 0;
		}
	}
}

int checkFishAlive()
{
	for (int i = 0; i < 6; i++)
	{
		if (arrayFish[i] > 0)
			return 1;
	}
	return 0;
}