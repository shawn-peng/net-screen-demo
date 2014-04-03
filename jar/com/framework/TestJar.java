
package com.framework;
public class TestJar {
	native public String jniLedOn();
	native public String jniLedOff();
	static {
		System.loadLibrary("test-jni");
	}	
		
	public String led_on() {
		return jniLedOn();
	}	
	public String led_off() {
		return jniLedOff();
	}
}
