#include <jni.h>
#include <limits.h>
#include "io_ibillxia_hellojni_HelloCal.h"

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloSay
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring Java_io_ibillxia_hellojni_HelloCal_helloSay
  (JNIEnv *env, jobject thiz){
    return env->NewStringUTF((char *)"Hello JNI!\nThe result of calculation is: ");
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloAdd
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloAdd
  (JNIEnv *env, jobject thiz, jint a, jint b){
	if(a>0 && INT_MAX-a<b){ // 上溢
		return INT_MAX;
	}else if(a<0 && INT_MIN-a>b){ // 下溢
		return INT_MIN;
	}
	return a+b;
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloSub
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloSub
  (JNIEnv *env, jobject thiz, jint a, jint b){
	if(a>0 && INT_MAX-a<-b){ // 上溢
		return INT_MAX;
	}else if(a<0 && INT_MIN-a>-b){ // 下溢
		return INT_MIN;
	}
	return a-b;
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloMul
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloMul
  (JNIEnv *env, jobject thiz, jint a, jint b){
	if(a>0 ){
		if(INT_MAX/a<b){ // 上溢
			return INT_MAX;
		}else if(INT_MIN/a>b){ // 下溢
			return INT_MIN;
		}
	}else if(a<0){
		if(INT_MIN/a<b){ // 下溢
			return INT_MIN;
		} else if(INT_MAX/a>b){ // 上溢
			return INT_MAX;
		}
	}
	return a*b;
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloDiv
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloDiv
  (JNIEnv *env, jobject thiz, jint a, jint b){
	if(b) return a/b;
	if(a>0) return INT_MAX; // b=0,a>0
	return INT_MIN; // b=0,a<0
}
