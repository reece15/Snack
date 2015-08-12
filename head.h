#ifndef STR_ALL_H
#define STR_ALL_H

#define MAP_MAX_COL 800
#define MAP_COL (MAP_MAX_COL - 160)
#define MAP_ROW 480
#define MAP_BLACK_COL ((MAP_COL - 40)/20)
#define MAP_BLACK_ROW ((MAP_ROW - 40)/20)
#define MAP_MAX (MAP_BLACK_COL*MAP_BLACK_ROW)

typedef struct st_snack 
{
	int x;
	int y;
	struct st_snack *next;
}st_snack;	//蛇的结构体

typedef struct st_food
{
	int x;
	int y;
	int gold_flag;
}st_food;	//食物结构体

#endif
