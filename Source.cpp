#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 17
#define COLUMS_MAX 3
#define COLUMS_DEFAULT_X 4
#define COLUMS_DEFAULT_Y 1
#define JEWEL_MAX 6

enum {
	CELL_NONE,
	CELL_WALL,
	CELL_JEWEL0,
	CELL_JEWEL1,
	CELL_JEWEL2,
	CELL_JEWEL3,
	CELL_JEWEL4,
	CELL_JEWEL5,
	CELL_MAX
};

char cellAA[][2 + 1] = {
	"Å@",//CELL_NONE,
	"Å°",//CELL_WALL,
	"Åõ",//CELL_JEWEL0,
	"Å¢",//CELL_JEWEL1,
	"Å§",//CELL_JEWEL2,
	"Å†",//CELL_JEWEL3,
	"Åû",//CELL_JEWEL4,
	"Åô"//CELL_JEWEL5,
};

char fieldCells[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];
char colums[COLUMS_MAX];
int columsX, columsY;

void resetColums() {
	columsX = COLUMS_DEFAULT_X;
	columsY = COLUMS_DEFAULT_Y;
	for (int i = 0; i < COLUMS_MAX; i++)
		colums[i] = CELL_JEWEL0 + rand() % JEWEL_MAX;
}
void display() {
	system("cls");
	memcpy(displayBuffer, fieldCells, sizeof(fieldCells));
	for (int i = 0; i < COLUMS_MAX; i++)
		displayBuffer[columsY + i][columsX] = colums[i];
	for (int i = 0; i < FIELD_HEIGHT; i++) {        //ï`âÊ
		for (int j = 0; j < FIELD_WIDTH; j++)
			printf("%s", cellAA[displayBuffer[i][j]]);
		printf("\n");
	}
}
int main() {
	srand((unsigned int)time(NULL));
	for (int  i = 0; i < FIELD_HEIGHT; i++) 
		fieldCells[i][0] = fieldCells[i][FIELD_WIDTH-1]=CELL_WALL;
	for (int i = 1; i < FIELD_WIDTH; i++)
		fieldCells[0][i]= fieldCells[FIELD_HEIGHT-1][i]= CELL_WALL;
	resetColums();

	time_t t = time(NULL);

	while (1) {
		if (time(NULL) > t) {
			t = time(NULL);
			columsY++;
			display();
		}
		if (_kbhit()) {
			switch (_getch()) {
				case'w':columsY--; break;
				case's':columsY++; break;
				case'a':columsX--; break;
				case'd':columsX++; break;
				case' ':colums; break;

			}
			display();
		}
	}
	_getch();


}
//test