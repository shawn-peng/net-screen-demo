
#include <jni.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>

jstring Java_com_framework_TestJar_jniLedOn(JNIEnv *env, 
			jclass thiz)
{
	int fd;
	fd = open("/dev/led_misc", O_RDWR);
	if (fd < 0) {
		return (*env)->NewStringUTF(env, "open failed");	
	}

	ioctl(fd, 555);
	close(fd);
	return (*env)->NewStringUTF(env, "LED ON");
}

jstring Java_com_framework_TestJar_jniLedOff(JNIEnv *env, 
			jclass thiz)
{
	int fd;
	fd = open("/dev/led_misc", O_RDWR);
	if (fd < 0) {
		return (*env)->NewStringUTF(env, "open failed");	
	}

	ioctl(fd, 666);
	close(fd);
	return (*env)->NewStringUTF(env, "LED OFF");
}


