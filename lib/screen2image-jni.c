#include <jni.h>

JNIEXPORT jint JNICALL Java_screen2image (JNIEnv *env,
		jobject thiz, jstring str)
{
	printf("hello string: %s\n", str);
	return 0;
}

