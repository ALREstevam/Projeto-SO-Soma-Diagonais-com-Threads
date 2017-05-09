#ifndef MATRIXDESCRIBER_H
#define MATRIXDESCRIBER_H

//Descritor de matriz

struct mxdccb;
typedef struct mxdccb{
    float ** data;
    int m, n, diagNum;
}MatrixDescriber;

#endif