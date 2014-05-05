#include <cstdlib>
#include <climits>
#include <iostream>
using namespace std;

#ifndef ERR_UP_OVERFLOW
#define ERR_UP_OVERFLOW 1
#endif

#ifndef ERR_DOWN_OVERFLOW
#define ERR_DOWN_OVERFLOW 2
#endif

#ifndef ERR_DIVBYZERO
#define ERR_DIVBYZERO 3
#endif

void alert(int,int,const char*);

int cal_add(int,int);
int cal_sub(int,int);
int cal_mul(int,int);
int cal_div(int,int);


