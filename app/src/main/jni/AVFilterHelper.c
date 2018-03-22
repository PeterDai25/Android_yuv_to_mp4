//
// Created by Dai on 2018/3/18.
//

#include "com_test_x264encoderdemo_AVFilterHelper.h"
#include "WaterMarker.h"

#define TAG "WaterMarker" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

jint JNICALL Java_com_test_x264encoderdemo_AVFilterHelper_initAVFilterHelper
        (JNIEnv *env, jclass class, jint width, jint height, jint fps) {
    return initAVFilter(width, height, fps);
}

jint JNICALL Java_com_test_x264encoderdemo_AVFilterHelper_addWatermark
        (JNIEnv *env, jclass class, jbyteArray in, jint length, jbyteArray out) {
    unsigned char *inbuf = (unsigned char *) (*env)->GetByteArrayElements(env, in, JNI_FALSE);
    unsigned char *outbuf = (unsigned char *) (*env)->GetByteArrayElements(env, out, JNI_FALSE);
    int reseult = addWaterMarker(inbuf, length, outbuf);
    (*env)->ReleaseByteArrayElements(env,in,inbuf,JNI_FALSE);
    (*env)->ReleaseByteArrayElements(env,out,outbuf,JNI_FALSE);
    return reseult;
}

void JNICALL Java_com_test_x264encoderdemo_AVFilterHelper_closeAVFilterHelper
        (JNIEnv *env, jclass class) {
    closeAVFilter();
}