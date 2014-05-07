#include "Calculate.h"

void alert(int code,int line,const char *file){
	std::cerr<<"EXCEPTION: #ERR"<<code<<": CAN NOT CALCULATE "
			<<"On line "<<line<<", in file "<<file<<"."<<std::endl;
}

int cal_add(int a,int b){
	if(a>0 && INT_MAX-a<b){ // 上溢
		alert(ERR_UP_OVERFLOW,__LINE__,__FILE__);
		exit(1);
	}else if(a<0 && INT_MIN-a>b){ // 下溢
		alert(ERR_DOWN_OVERFLOW,__LINE__,__FILE__);
		exit(1);
	}
	return a+b;
}

int cal_sub(int a,int b){
	if(a>0 && INT_MAX-a<-b){ // 上溢
		alert(ERR_UP_OVERFLOW,__LINE__,__FILE__);
		exit(1);
	}else if(a<0 && INT_MIN-a>-b){ // 下溢
		alert(ERR_DOWN_OVERFLOW,__LINE__,__FILE__);
		exit(1);
	}
	return a-b;
}

int cal_mul(int a,int b){
	if(a>0 ){
		if(INT_MAX/a<b){ // 上溢
			alert(ERR_UP_OVERFLOW,__LINE__,__FILE__);
			exit(1);
		}else if(INT_MIN/a>b){ // 下溢
			alert(ERR_DOWN_OVERFLOW,__LINE__,__FILE__);
			exit(1);
		}
	}else if(a<0){
		if(INT_MIN/a<b){ // 下溢
			alert(ERR_DOWN_OVERFLOW,__LINE__,__FILE__);
			exit(1);
		} else if(INT_MAX/a>b){ // 上溢
			alert(ERR_UP_OVERFLOW,__LINE__,__FILE__);
			exit(1);
		}
	}
	return a*b;
}

int cal_div(int a,int b){
	if(!b){  // 判断是否除0
		alert(ERR_DIVBYZERO,__LINE__,__FILE__);
		exit(1);
	}
	return a/b;
}
