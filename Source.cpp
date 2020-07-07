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
bool pass = false;

void resetColums() {
	columsX = COLUMS_DEFAULT_X;
	columsY = COLUMS_DEFAULT_Y;
	for (int i = 0; i < COLUMS_MAX; i++)
		colums[i] = CELL_JEWEL0 + rand() % JEWEL_MAX;
}
void display() {
	system("cls");
	memcpy(displayBuffer, fieldCells, sizeof(fieldCells));
	
	if(!pass)
		for (int i = 0; i < COLUMS_MAX; i++)
		displayBuffer[columsY + i][columsX] = colums[i];
	for (int i = 3; i < FIELD_HEIGHT; i++) {        //ï`âÊ
		for (int j = 0; j < FIELD_WIDTH; j++)
			printf("%s", cellAA[displayBuffer[i][j]]);
		printf("\n");
	}
}
int columsIntersecField(int _columsX,int _columsY) {
	return fieldCells[_columsY + COLUMS_MAX - 1][_columsX] != CELL_NONE;
}
bool erase() {
	bool erased = false;
	for (int i = 1; i < FIELD_HEIGHT - 1; i++)
		for (int j = 1; j < FIELD_WIDTH - 1; j++) {
			const int directionMax = 4;
			int directions[][2] = {
				{1,0},
				{0,1},
				{1,1},
				{1,-1} };
			for (int k = 0; k < directionMax; k++) {
				int conectCount = 0;
				char cell = fieldCells[i][j];
				for (int y = i, x = j;
					fieldCells[y][x] == cell;
					x += directions[k][0], y += directions[k][1])
					conectCount++;
				if (conectCount >= 3) {
					erased = true;
					for (int y = i, x = j;
						fieldCells[y][x] == cell;
						x += directions[k][0], y += directions[k][1])
						fieldCells[y][x] = CELL_NONE;
					;
				}
			}
		}
	return erased;
}

int main() {
	srand((unsigned int)time(NULL));
	for (int  i = 0; i < FIELD_HEIGHT; i++) 
		fieldCells[i][0] = fieldCells[i][FIELD_WIDTH-1]=CELL_WALL;
	for (int i = 1; i < FIELD_WIDTH; i++)
		fieldCells[0][i]= fieldCells[FIELD_HEIGHT-1][i]= CELL_WALL;
	resetColums();

	time_t t = time(NULL);
	bool pass = false;
	while (1) {
		if (time(NULL) > t) {
			t = time(NULL);

			if (pass) {
				bool fall = false;
				for(int i= FIELD_HEIGHT - 2;i>=1;i--)
					for (int j=1; j < FIELD_WIDTH-1; j++) {
						if ((fieldCells[i + 1][j] == CELL_NONE) && (fieldCells[i][j] != CELL_NONE)) {
							fall = true;
							fieldCells[i + 1][j] = fieldCells[i][j];
							fieldCells[i][j] = CELL_NONE;
						}
					}
				if (!fall)
					pass = false;
			}
			else if (columsIntersecField(columsX, columsY + 1)) {
				for (int i = 0; i < COLUMS_MAX; i++)
					fieldCells[columsY + i][columsX] = colums[i];
				for(int i=1;i<3;i++)
					for(int j=1;j<FIELD_WIDTH-1;j++)
						if (fieldCells[i][j] != CELL_NONE) {
							printf("GAME OVER\n");
							_getch();
							exit(0);
						}


				resetColums();

				if (erase())
					pass = true;
			}
			else
			columsY++;
			display();
		}
		if (_kbhit()) {
			if (pass)
				_getch();
			else {
				switch (_getch()) {
				case's':
					if (!columsIntersecField(columsX, columsY + 1))
						columsY++; break;
				case'd':
					if (!columsIntersecField(columsX + 1, columsY))
						columsX++; break;
				case'a':
					if (!columsIntersecField(columsX - 1, columsY))
						columsX--; break;

				case' ':
				{
					char temp[COLUMS_MAX];
					memcpy(temp, colums, sizeof colums);
					for (int i = 0; i < COLUMS_MAX; i++)
						colums[(i + 1) % COLUMS_MAX] = temp[i];
				}
				break;

				}
				display();
			}
		}
	}
	_getch();


}
//test