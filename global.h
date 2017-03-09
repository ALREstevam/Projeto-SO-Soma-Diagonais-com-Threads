#ifndef global_C
#define glogal_C
//Coordenadas
typedef struct coordinates_x_y
{
	int x, y;
}CoordinatesXY;


//ELEMENTO DA MATRIZ
typedef struct matrix_elem
{
	double value;
	CoordinatesXY nextInMainDiagonal;
	//int pos;
	//XYCoordinates coord;
	
}MatrixElem;

//DESCRITOR DE MATRIZ
typedef struct matrix_describer
{
	MatrixElem **matrix;
	int m, n;
}MatrixDescriber;
#endif