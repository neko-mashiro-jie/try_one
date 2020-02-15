#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include <time.h>   
#define quit 0
#define fanyi 30
#define liangci 20+fanyi
#define xuan_zi 27+liangci
#define moxie 10+xuan_zi
#define xuan_ze 20+moxie
#define juzi 5+xuan_ze
#define yingyong 4+juzi

int menu();
int xuanze();
void yi_er();
void san_si();
void wu_liu();
int rollem(int, int);
int huida(int, int,const struct dati*);
void yunsuan(int, int, int);


struct  student {
	char name[6];
	int num;
	int grand;
	int score;
	char cn_ans[45];
	int ma_ans;
}your;
struct dati {
	char que[100];
	char cn_ans[45];
	int ma_ans;
}chu_ti[yingyong];
FILE* fp1;
FILE* fp2;

int main(void) {

	int c;
	srand((unsigned int)time(0));
	errno_t err;
	int num = 0;
	if (err = fopen_s(&fp1, ".\\que1.txt", "r"))
	{
		fputs("Can't open que1.txt file\n", stderr);
		exit(1);
	}
	while (fgets(chu_ti[num].que, sizeof(chu_ti[num].que), fp1)) {
		num++;
	}
	num = 0;
	if (err = fopen_s(&fp2, ".\\ans.txt", "r"))
	{
		fputs("Can't open ans.txt file\n", stderr);
		exit(2);
	}
	num = 0;
	while (num < yingyong) {
		if (num <= juzi) {
			fgets(chu_ti[num].cn_ans, sizeof(chu_ti[num].cn_ans), fp2);
			num++;
		}
		else {
			fscanf_s(fp2, "%d", &chu_ti[num].ma_ans);
			num++;
		}


	}
	while ((c = menu()) != quit) {
		switch (c)
		{
		case 1:
			yi_er();
			break;
		case 2:
			san_si();
			break;
		case 3:
			wu_liu();
			break;
		default:
			printf("请正确输入你的年级（使用1-6或0退出）：");
			break;
		}
		printf("%5s%2d年级%10d号\n", your.name, your.grand, your.num);
		printf("你的分数是：%5d\n", your.score);
		your.score = 0;
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}


int menu(void) {
	int c;
	printf("请输入你的姓名；");
	scanf_s("%s", your.name, 6);
	printf("请输入你的学号；");
	scanf_s("%d", &your.num);
	printf("请输入你的年级；");
	scanf_s("%d", &your.grand);
	printf("你可以选择以下等级的测试（可使用0退出）：");
	printf("（1)一二（低）年级   （2)三四（中）年级   （3）五六（高）年级\n");
	scanf_s("%d", &c);
	return c;
}

int xuanze(void) {
	int d;
	printf("  1、语文      2、数学\n");
	printf("请选择你想进行的测试：");
	while (((scanf_s("%d", &d)) != 1) || (d != 1 && d != 2)) {
		scanf_s("%*s");
		printf("请重新输入你想进行的测试（1或2）：");
	}
	return d;
}

void yi_er(void) {
	int c;
	int i = 0;
	int x;
	if ((c = xuanze()) == 1) {

		while (i < 5) {
			x = rollem(fanyi, 0);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 10, &chu_ti[x]);
			i++;
		}
		while (i > 4 && i < 10) {
			x = rollem(liangci, fanyi);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 10, &chu_ti[x]);
			i++;
		}
	}
	else {
		int a, b;
		int a1, b1;
		int n;
		for (i = 0;i < 2;i++) {
			printf("%d  %d\n", a = rollem(100, 0), b = rollem(100, 0));
			printf("请从大到小排列（两数用空格隔开）\n");
			for (n = 0;n < 3;n++) {

				scanf_s("%d %d", &a1, &b1);
				if (a1 > b1)
					break;
				else
					printf("回答错误，你还有%d次机会\n", 2 - n);
			}
		}
		yunsuan(20, 2, 6);
		yunsuan(100, 4, 2);
	}

}

void san_si() {
	int c;
	int i = 0;
	int x;
	if ((c = xuanze()) == 1) {

		while (i < 2) {
			do{
				x = rollem(xuan_zi, liangci);
			} while ( x % 3 != 0 );
			printf("%s", chu_ti[x - 1].que);
			printf("%s", chu_ti[x].que);			
			your.score += huida(c, 10, &chu_ti[x]);
			printf("%s", chu_ti[x + 1].que);
			your.score += huida(c, 10, &chu_ti[x + 1]);
			i++;
		}
		while (i > 1 && i < 4) {
			x = rollem(moxie, xuan_zi);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 20, &chu_ti[x]);
			i++;
		}
		if (i == 4) {
			do {
				x = rollem(xuan_ze, moxie);
			} while (x  % 3 != 1);
			printf("%s", chu_ti[x - 1].que);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 20, &chu_ti[x]);
			i++;
		}
	}
	else {
		yunsuan(100, 4, 8);
		x = rollem(yingyong, juzi);
		printf("%s", chu_ti[x].que);
		your.score += huida(c, 20, &chu_ti[x]);
	}
}

void wu_liu() {
	int c;
	int i = 0;
	int x;
	if ((c = xuanze()) == 1) {

		while (i < 2) {
			x = rollem(moxie, xuan_zi);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 10, &chu_ti[x]);
			i++;
		}
		while (i > 1 && i < 4) {
			do {
				x = rollem(xuan_ze, moxie);
			} while (x % 3 != 1);
			printf("%s", chu_ti[x].que);
			printf("%s", chu_ti[x + 1].que);
			your.score += huida(c, 20, &chu_ti[x + 1]);
			i++;
		}
		while (i > 3 && i < 5) {
			x = rollem(juzi, xuan_ze);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 20, &chu_ti[x]);
			i++;
		}
	}
	else {
		int a, b, d;
		int t, n;
		for (i = 0;i < 2;i++) {
			x = rollem(yingyong - 1, juzi);
			printf("%s", chu_ti[x].que);
			your.score += huida(c, 15, &chu_ti[x]);
		}
		for (;i < 6;i++) {
			do {
				a = rollem(8, 0);
				b = rollem(100, 0);
				d = rollem(100, 0);
			} while (d <= b && ((d - b) / 3 <= a));
			printf("%d x + %d = %d\n", a, b, d);
			for (n = 0;n < 3;n++) {
				printf("x（保留整数）=");
				scanf_s("%d", &t);
				if (t == ((d - b) / a)) {
					your.score += 10;
					break;
				}
				else
					printf("回答错误，你还有%d次机会\n", 2 - n);
			}
			if (n == 3)
				printf("抱歉，正确答案是%d\n", ((d - b) / a));
		}
	}
}

int rollem(int sides, int begin)
{
	int roll;
	do
	{
		roll = rand() % sides + 1;
	} while (roll <= begin);
	return roll;
}

int huida(int c, int s, const struct dati* q) {
	int n;
	if (c < 2) {
		for (n = 0;n < 3;n++) {
			scanf_s("%s", your.cn_ans, 30);
			if (*(your.cn_ans) == *(q->cn_ans))
				return s;
			else
				printf("回答错误，你还有%d次机会\n", 2 - n);
		}
		printf("抱歉，正确答案是%s\n", q->cn_ans);
		return 0;
	}
	else {
		for (n = 0;n < 3;n++) {
			scanf_s("%d", &your.ma_ans);
			if (your.ma_ans == (q->ma_ans))
				return s;
			else
				printf("回答错误，你还有%d次机会\n", 2 - n);
		}
		printf("抱歉，正确答案是%d\n", q->ma_ans);
		return 0;
	}
	return 0; 
}

void yunsuan(int d, int z, int n) {
	int a, b;
	int i;
	int c;
	for (i = 0;i < n / z;i++) {
		printf("%d + %d\n", a = rollem(d, 0), b = rollem(d, 0));

		for (c = 0;c < 3;c++) {
			scanf_s("%d", &your.ma_ans);
			if (your.ma_ans == (a + b)) {
				your.score += 10;
				break;
			}
			else
				printf("回答错误，你还有%d次机会\n", 2 - c);
		}
		if (c == 3)
			printf("抱歉，正确答案是%d\n", a + b);
	}
	for (;i < 2*(n / z) + 1;i++) {
		do {
			a = rollem(d, 0);
			b = rollem(d / 3, 0);
		} while (a <= b);
		printf("%d - %d\n", a, b);
		for (c = 0;c < 3;c++) {
			scanf_s("%d", &your.ma_ans);
			if (your.ma_ans == (a - b)) {
				your.score += 10;
				break;
			}
			else
				printf("回答错误，你还有%d次机会\n", 2 - c);
		}
		if (c == 3)
			printf("抱歉，正确答案是%d\n", a - b);
	}
	if (n < 3)
		return;
	for (;i < 3 * n / z;i++) {
		do {
			a = rollem(d, 0);
			b = rollem(d, 0);
		} while (a <= 2 * b);
		printf("%d / %d（保留整数）\n", a, b);

		for (c = 0;c < 3;c++) {
			scanf_s("%d", &your.ma_ans);
			if (your.ma_ans == (a / b)) {
				your.score += 10;
				break;
			}
			else
				printf("回答错误，你还有%d次机会\n", 2 - c);
		}

		if (c == 3)
			printf("抱歉，正确答案是%d\n", a / b);
	}
	for (;i < 3*(n / z) + 1;i++) {
		printf("%d * %d\n", a = rollem(d, 0), b = rollem(d, 0));

		for (c = 0;c < 3;c++) {
			scanf_s("%d", &your.ma_ans);
			if (your.ma_ans == (a * b)) {
				your.score += 10;
				break;
			}
			else
				printf("回答错误，你还有%d次机会\n", 2 - c);
		}
		if (c == 3)
			printf("抱歉，正确答案是%d\n", a * b);
	}
}
