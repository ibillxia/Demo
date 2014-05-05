#include <iostream>
using namespace std;

#include "Calculate.h"


int main(void){
	int a,b;
	cin>>a>>b;
	cout<<"a+b="<<cal_add(a,b)<<endl;
	cout<<"a-b="<<cal_sub(a,b)<<endl;
	cout<<"a*b="<<cal_mul(a,b)<<endl;
	cout<<"a/b="<<cal_div(a,b)<<endl;
	return 0;
}
