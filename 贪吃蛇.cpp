//	̰���� V1.1
//
//	VC++6.0		WIN7x64    Easyx������
//	
//	2015 1 21
//
//	by : 0xcc

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "head.h"	
#include <time.h>
#pragma comment(lib,"Winmm.lib")		//�������

int map_check[MAP_ROW/20][MAP_COL/20];	//��ͼ����   ʳ�� 2 �� 1 �� 0 �ϰ� 3
int music_flag = 1;		//���ֿ���
int length = 0;			//�߳�

void welcome(IMAGE *score_bk);		//��ӭ����
void draw_map(st_snack *snack, IMAGE *snack_body, IMAGE *food_always, IMAGE *bk_map, st_food *food, IMAGE *head);	//���Ƶ�ͼ
int draw_food(IMAGE *always, st_food *food);		//����ʳ��
int game_run(st_snack *snack, IMAGE *snack_body, IMAGE *food_always, IMAGE *bk_map, st_food *food, IMAGE *head);	//��Ϸ
void help(IMAGE *welcome_bk);		//����
int option();		//��������
void game_over(st_snack *snack);	//��Ϸ����

int main(void)
{
	initgraph(MAP_MAX_COL, MAP_ROW);
	IMAGE snack_body;
	IMAGE food_always;	//��ͨʳ��ͼƬ
	IMAGE score_bk;		//����������
	IMAGE bk_map;		//��ͼ����
	IMAGE head;		//��ͷ
	st_food food;		
	st_snack *snack;	
	
	srand((unsigned int)time(NULL));
	loadimage(&snack_body, "images/snack.jpg");
	loadimage(&food_always, "images/food_always.jpg");
	loadimage(&score_bk, "images/score_bk.jpg");
	loadimage(&bk_map, "images/caodi.jpg");
	loadimage(&head, "images/head.jpg");
	while (1)
	{
		snack = (st_snack *)malloc(sizeof(st_snack)); 
		snack->next = NULL;
		welcome(&score_bk);
		draw_map(snack, &snack_body, &food_always, &bk_map, &food, &head);
		if(1 == game_run(snack, &snack_body, &food_always, &bk_map, &food, &head))
		{
			game_over(snack);	
		}
	}
	closegraph();
	return 0;
}

void welcome(IMAGE *score_bk)
{
	MOUSEMSG m;
	IMAGE welcome_bk, temp;

	loadimage(&welcome_bk, "images/welcome.jpg");
	putimage(0, 0, &welcome_bk);
	if (music_flag)
	{
		mciSendString("open audio/welcome.mp3 alias welcome", NULL, 0, NULL);
		mciSendString("play welcome repeat", NULL, 0, NULL);
	}
	while(1)
	{
		m = GetMouseMsg();
		if (m.x <= 490 && m.x >= 290 && m.y >= 350 && m.y <= 410 && m.uMsg == WM_LBUTTONDOWN)
		{
			if (music_flag)
			{
				mciSendString("open audio/switch.mp3 alias switch", NULL, 0, NULL);
				mciSendString("play switch", NULL, 0, NULL);
				Sleep(300);
				mciSendString("stop switch", NULL, 0, NULL);
				mciSendString("close switch", NULL, 0, NULL);
			}
			break;		//������Ϸ
		}
		else if (m.x <= 119 && m.x >= 65 && m.y >= 226 && m.y <= 254 && m.uMsg == WM_LBUTTONDOWN)
		{
			if (music_flag)
			{
				mciSendString("open audio/switch.mp3 alias switch", NULL, 0, NULL);
				mciSendString("play switch", NULL, 0, NULL);
				Sleep(300);
				mciSendString("stop switch", NULL, 0, NULL);
				mciSendString("close switch", NULL, 0, NULL);
			}
			exit(1);		//�˳���Ϸ
		}
		else if (m.x <= 160 && m.x >= 60 && m.y >= 257 && m.y <= 287 && m.uMsg == WM_LBUTTONDOWN)
		{
			music_flag = (music_flag + 1) % 2;	//��������
			if (music_flag)
			{
				mciSendString("open audio/switch.mp3 alias switch", NULL, 0, NULL);
				mciSendString("play switch", NULL, 0, NULL);
				Sleep(300);
				mciSendString("stop switch", NULL, 0, NULL);
				mciSendString("close switch", NULL, 0, NULL);
			}
			if (music_flag)
			{
				mciSendString("open audio/welcome.mp3 alias welcome", NULL, 0, NULL);
				mciSendString("play welcome repeat", NULL, 0, NULL);
			}
			if (!music_flag)
			{
				mciSendString("stop welcome", NULL, 0, NULL);
				mciSendString("close welcome", NULL, 0, NULL);
			}
		}
		else if (m.x <= 181 && m.x >= 50 && m.y >= 294 && m.y <= 330 && m.uMsg == WM_LBUTTONDOWN)
		{
			if (music_flag)
			{
				mciSendString("open audio/switch.mp3 alias switch", NULL, 0, NULL);
				mciSendString("play switch", NULL, 0, NULL);
				Sleep(300);
				mciSendString("stop switch", NULL, 0, NULL);
				mciSendString("close switch", NULL, 0, NULL);
			}
			help(&welcome_bk);		//��������˵�
		}
	}
	if (music_flag)
	{
		mciSendString("stop welcome", NULL, 0, NULL);
		mciSendString("close welcome", NULL, 0, NULL);
	}
	putimage(640, 20, score_bk);
}

void draw_map(st_snack *snack, IMAGE *snack_body, IMAGE *food_always, IMAGE *bk_map, st_food *food, IMAGE *head)
{
	IMAGE wall;
	int i, j;
	st_snack *p = snack;
	
	if (music_flag)
	{
		mciSendString("open audio/bk_audio.mp3 alias bk", NULL, 0, NULL);
		mciSendString("play bk repeat", NULL, 0, NULL);
	}
	putimage(20, 20, bk_map);
	loadimage(&wall, "images/wall.bmp");
	for (i = 0; i < MAP_ROW; i+=20)
	{
		map_check[i/20][0] = 3;
		putimage(0, i, &wall);
		putimage(MAP_COL - 20, i, &wall);
		map_check[i/20][MAP_COL/20-1] = 3;
		putimage(MAP_MAX_COL - 20, i, &wall);
	}
	for (i = 0; i < MAP_MAX_COL; i+=20)
	{
		if (i < MAP_COL)
		{
			map_check[0][i/20] = 3;
			map_check[MAP_ROW/20-1][i/20] = 3;
		}
		putimage(i, 0, &wall);
		putimage(i, MAP_ROW - 20, &wall);
	}
	for (i = MAP_COL; i < MAP_MAX_COL; i+=20)
	{
		putimage(i, 100, &wall);
		putimage(i, 160, &wall);
		putimage(i, 260, &wall);
		putimage(i, 360, &wall);
	}
	//���Ʊ߿�
	for (i = 1, j = 300; i <= 4; i++, j-=20)
	{
		p->next = (st_snack *)malloc(sizeof(st_snack));
		length += 1;
		p = p->next;
		p->x = j;
		p->y = 240;
		if(p == snack->next)
		{
			putimage(p->x, p->y, head);
		}
		else
			putimage(p->x, p->y, snack_body);
		map_check[p->y/20][j/20] = 1;
	}
	p->next = NULL;
	//��ʼ����
	draw_food(food_always, food);
}
	
int draw_food(IMAGE *food_always,st_food *food)
{
	int i, j, k = 0, stop, break_flag =  0;

	
	stop = rand() % ((MAP_MAX - length - 1))+1;	//�����пո���ȡ��N���ո�
	for (i = 0; i <= (MAP_ROW/20 - 1 ) && !break_flag; i++)
	{
		for (j = 0; j <= (MAP_COL/20 - 1); j++)
		{
			if (map_check[i][j] == 0)
			{
				k++;
				if (k == stop)
				{
					food->x = j*20;
					food->y = i*20;
					break_flag = 1;
					break;
				}
			}
		}
	}
	food->gold_flag = 0;
	putimage(food->x, food->y, food_always);
	map_check[food->y/20][food->x/20] = 2;
	break_flag = 0;
// 	for (i = 0; i <= (MAP_ROW/20 - 1 ) && !break_flag; i++)
// 	{
// 		for (j = 0; j <= (MAP_COL/20 - 1); j++)
// 		{
// 			printf("%d",map_check[i][j]);
// 			if (map_check[i][j] == 0)
// 			{
// 				k++;
// 				if (k == stop)
// 				{
// 					food->x = j*20;
// 					food->y = i*20;
// // 					break_flag = 1;
// // 					break;
// 				}
// 			}
// 		}
// 		printf("\n");
// 	}
	return 0;
}

int game_run(st_snack *snack, IMAGE *snack_body, IMAGE *food_always, IMAGE *bk_map, st_food *food, IMAGE *head)
{
	int score = 0;
	int temp_x, temp_y, move_x, move_y;	//����任����  ����任����
	char target = 'd', last_target = 'd';	//��ͷ�����־	//��ͷ��һ������ 
	char temp_target;
	st_snack *p, *q;
	int speed = 5;
	IMAGE gameover;	//��Ϸ������ʾͼƬ
	IMAGE pause;	//��ͣͼƬ
	IMAGE running;	//����ͼƬ
	IMAGE score_bk_save;	//���ֱ�������
	IMAGE speed_bk_save;	//�ٶȱ�������
	char score_to_string[10];	//toString������
	LOGFONT f;			//�������Խṹ��
	int hit_flag = 0;		//�������ٰ������µ��쳣
	int eat_flag = 0;		//�Ե�ʳ��ı�־

	setbkmode(TRANSPARENT);		//�������ֱ���͸��
	getimage(&speed_bk_save, MAP_COL, 120, 140, 40);
	getimage(&score_bk_save, MAP_COL, 280, 140, 80);
	getfont(&f);                          
	f.lfHeight = 42;                     
	strcpy(f.lfFaceName, "����");        
	f.lfQuality = ANTIALIASED_QUALITY;    
	setfont(&f);                          // ����������ʽ
	outtextxy(MAP_COL + 40, 302, "0");
	outtextxy(MAP_COL + 40, 122, 48 + speed - 3);
	loadimage(&running, "images/run.jpg");
	loadimage(&pause, "images/pause.jpg");
	loadimage(&gameover, "images/gameover.jpg");
	putimage(MAP_MAX_COL - 20 -140, MAP_ROW - 20 - 70, &running);
	BeginBatchDraw();	//����������ͼ
	while(1)
	{
		while(!kbhit() || hit_flag)
		{
			hit_flag = 0;
			switch (target)		//�����־
			{
			case 'a': move_x = -20; move_y = 0; break;
			case 'w': move_x = 0; move_y = -20; break;
			case 'd': move_x = 20; move_y = 0; break;
			case 's': move_x = 0; move_y = 20; break;
			}
			putimage(20, 20, bk_map);
			putimage(food->x, food->y, food_always);
			temp_x = move_x + snack->next->x;
			temp_y = move_y + snack->next->y;
			
			for (p = snack->next; p; p = p->next)
			{
				if (p->x != temp_x)
				{
					p->x ^= temp_x;
					temp_x ^= p->x;
					p->x ^=temp_x;
				}
				if (p->y != temp_y)
				{
					p->y ^= temp_y;
					temp_y ^= p->y;
					p->y ^=temp_y;
				}
				if (p == snack->next)		
				{
					if (map_check[p->y/20][p->x/20] == 3 || map_check[p->y/20][p->x/20] == 1 )	//�߽���ײ��� //������ײ���
					{
						putimage(MAP_MAX_COL - 20 -140, MAP_ROW - 20 - 70, &gameover);		//��Ϸ����
						FlushBatchDraw();
						EndBatchDraw();
						return 1;
					}
					else if (map_check[p->y/20][p->x/20] == 2)
					{
						eat_flag = 1;
					}
					map_check[p->y/20][p->x/20] = 1;
					putimage(p->x, p->y, head);
				}
				else
				{
					putimage(p->x, p->y, snack_body);
				}
			}
			map_check[temp_y/20][temp_x/20] = 0;
			FlushBatchDraw();	//ˢ����Ļ
			p = snack;
			if (eat_flag) //���ߵõ�ʳ��ʱ
			{
				eat_flag = 0;
				while(p)
				{
					q = p;
					p = p->next;
				}
				score += 5 * (speed - 3) ;			//�������
				sprintf(score_to_string, "%d", score);
				putimage(MAP_COL, 280, &score_bk_save);
				outtextxy(MAP_COL + 40, 302, score_to_string);
				q->next = (st_snack *)malloc(sizeof(st_snack));   //�����߳�
				length += 1;
				q->next->x = temp_x;
				q->next->y = temp_y;
				q->next->next = NULL;  
				if (music_flag)
				{
					mciSendString("open audio/eat_food.mp3 alias eat", NULL, 0, NULL);
					mciSendString("play eat", NULL, 0, NULL);
					Sleep(1000 - speed * 100);
					mciSendString("stop eat", NULL, 0, NULL);
					mciSendString("close eat", NULL, 0, NULL);
				}
				else
				{
					Sleep(1000 - speed * 100);	//�ٶȿ���
				}
				draw_food(food_always, food);  //���»���ʳ��
			}
			else
				Sleep(1000 - speed * 100); 	//�ٶȿ���
		}
					//���̿���
		temp_target = getch();
		if ((temp_target == 'A' || temp_target == 'a') && target != 'd')  //&& ���ں��Զ��߽��еķ������ 
		{
			target = 'a';
			hit_flag = 1;
		}
		else if ((temp_target == 'W' || temp_target == 'w') && target != 's')
		{
			target = 'w';
			hit_flag = 1;
		}
		else if ((temp_target == 'D' || temp_target == 'd') && target != 'a')
		{
			target = 'd';
			hit_flag = 1;
		}
		else if ((temp_target == 'S' || temp_target == 's') && target != 'w')
		{
			target = 's';
			hit_flag = 1;
		}
		else if(temp_target == 27)
		{
			EndBatchDraw();
			return 1;	//�˳�
		}
		else if (temp_target == 'P' || temp_target == 'p')
		{
			putimage(MAP_MAX_COL - 20 -140, MAP_ROW - 20 - 70, &pause);			//��ͣ״̬
			if (music_flag)
			{
				mciSendString("stop bk", NULL, 0, NULL);
			}
			FlushBatchDraw();
			do{
				fflush(stdin);
				temp_target = getch();			
			}while (temp_target != 'o' && temp_target != 'O');
			putimage(MAP_MAX_COL - 20 -140, MAP_ROW - 20 - 70, &running);   //����״̬
			if (music_flag)
			{
				mciSendString("play bk repeat", NULL, 0, NULL);
			}
			FlushBatchDraw();
		}else if ((temp_target == 'i' || temp_target == 'I' ) && speed < 9)	//����
		{
			speed += 1;
			putimage(MAP_COL, 122, &speed_bk_save);
			outtextxy(MAP_COL + 40, 122, 48 + speed - 3);
			FlushBatchDraw();
		}
		else if ((temp_target == 'k' || temp_target == 'K') && speed > 4)	//����
		{
			speed -= 1;
			putimage(MAP_COL, 122, &speed_bk_save);
			outtextxy(MAP_COL + 40, 122, 48 + speed - 3);
			FlushBatchDraw();
		}
		fflush(stdin);
	}
	EndBatchDraw();
	return 0;
}

void help(IMAGE *welcome_bk)
{
	MOUSEMSG m;

	loadimage(NULL, "images/help.jpg");
	while(1)
	{
		m = GetMouseMsg();
		if (m.x <= 490 && m.x >= 290 && m.y >= 350 && m.y <= 410 && m.uMsg == WM_LBUTTONDOWN)
		{
			if (music_flag)
			{
				mciSendString("open audio/switch.mp3 alias switch", NULL, 0, NULL);
				mciSendString("play switch", NULL, 0, NULL);
				Sleep(300);
				mciSendString("stop switch", NULL, 0, NULL);
				mciSendString("close switch", NULL, 0, NULL);
			}
			break;
		}
	}
	putimage(0, 0, welcome_bk);
}

void game_over(st_snack  *snack)
{
	st_snack *q = snack, *p = snack->next;
	IMAGE block[4];
	int i, j;

	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}		//�ͷ��ߵĿռ�
	for (i = 0; i <= (MAP_ROW/20 - 1 ); i++)
	{
		for (j = 0; j <= (MAP_COL/20 - 1); j++)
		{
			if (map_check[i][j] == 1 || map_check[i][j] == 2)
			{
				map_check[i][j] = 0;
			}
		}
	}//�ָ���ͼ
	if (music_flag)
	{
		mciSendString("stop bk", NULL, 0, NULL);
		mciSendString("close bk", NULL, 0, NULL);	//�رձ�������
	}
	if (music_flag)
	{
		mciSendString("open audio/over.mp3 alias over", NULL, 0, NULL);
		mciSendString("play over repeat", NULL, 0, NULL);
	}
	loadimage(&block[0], "images/wall.bmp");
	loadimage(&block[1], "images/wall_2.bmp");
	loadimage(&block[2], "images/wall_4.jpg");
	loadimage(&block[3], "images/snack.jpg");
	for (i = 0; i < MAP_ROW ; i += 20)
	{
		for (j = 0; j < MAP_MAX_COL; j += 20)
		{
			putimage(j, i, &block[rand()%4]);
			if (j % 40 == 0)
			{
				Sleep(10);
			}
		}
	}
	if (music_flag)
	{
		mciSendString("stop over", NULL, 0, NULL);
		mciSendString("close over", NULL, 0, NULL);
	}
}