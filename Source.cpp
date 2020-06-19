#include <conio.h>
#include <stdio.h>
#define FIELD_WIDTH 8
#define FIELD_HEIGHT 17
#define COLUMS_MAX 3
#define COLUMS_DEFAULT_X 4
#define COLUMS_DEFAULT_X 1

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
char colums[COLUMS_MAX];

void resetColums() {

}

int main() {
	for (int i = 0; i < FIELD_HEIGHT; i++) 
		fieldCells[i][0] = fieldCells[i][FIELD_WIDTH-1]=CELL_WALL;
	for (int i = 1; i < FIELD_WIDTH; i++)
		fieldCells[0][i]= fieldCells[FIELD_HEIGHT-1][i]= CELL_WALL;
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j=0;j<FIELD_WIDTH;j++)
			printf("%s",cellAA[fieldCells[i][j]]);
		printf("\n");
	}
	_getch();


}
//test