#include <com_test_x264encoderdemo_Mp4v2Helper.h>
#include "mp4record.h"
#include "mp4record.c"
#import <stdlib.h>


MP4V2_CONTEXT *_mp4Handle;

/**
 * 初始化
 * @param env
 * @param jclass
 * @param path
 * @param width
 * @param height
 * @return
 */
jint JNICALL Java_com_test_x264encoderdemo_Mp4v2Helper_initMp4Encoder
        (JNIEnv *env, jclass jclass, jstring path, jint width, jint height ,jint fps) {
    const char *local_title = (*env)->GetStringUTFChars(env, path, NULL);
    int m_width = width;
    int m_height = height;
    int m_fps = fps;
    _mp4Handle = initMp4Encoder(local_title, m_width, m_height,m_fps);
    return 0;
}
/**
 * 添加视频帧的方法
 */
JNIEXPORT jint JNICALL Java_com_test_x264encoderdemo_Mp4v2Helper_mp4VEncode
        (JNIEnv *env, jclass clz, jbyteArray data, jint size) {
    unsigned char *buf = (unsigned char *) (*env)->GetByteArrayElements(env, data, JNI_FALSE);
    int nalsize = size;
    int result = mp4VEncode(_mp4Handle, buf, nalsize);
    (*env)->ReleaseByteArrayElements(env,data,buf,JNI_FALSE);
    return result;
}

/**
 * 释放
 */
JNIEXPORT void JNICALL Java_com_test_x264encoderdemo_Mp4v2Helper_closeMp4Encoder
        (JNIEnv *env, jclass clz) {
    closeMp4Encoder(_mp4Handle);
}


