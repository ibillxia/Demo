package io.ibillxia.hellojni;

public class HelloCal {
	static {
		System.loadLibrary("HelloJni");
	}
	
	public native String helloSay();
	public native int helloAdd(int a,int b);
	public native int helloSub(int a,int b);
	public native int helloMul(int a,int b);
	public native int helloDiv(int a,int b);
}
