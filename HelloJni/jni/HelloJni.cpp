#include <jni.h>
#include "io_ibillxia_hellojni_HelloCal.h"

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloSay
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring Java_io_ibillxia_hellojni_HelloCal_helloSay
  (JNIEnv *env, jobject thiz){
    return env->NewStringUTF((char *)"Hello from JNI !");
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloAdd
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloAdd
  (JNIEnv *env, jobject thiz, jint a, jint b){
	return a+b;
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloSub
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloSub
  (JNIEnv *env, jobject thiz, jint a, jint b){
	return a-b;
}

/*
 * Class:     io_ibillxia_hellojni_HelloCal
 * Method:    helloMul
 * Signature: (II)I
 */
JNIEXPORT jint Java_io_ibillxia_hellojni_HelloCal_helloMul
  (JNIEnv *env, jobject thiz, jint a, jint b){
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
	if(a>0) return 0x7fffffff;
	return 0x80000000;
}
