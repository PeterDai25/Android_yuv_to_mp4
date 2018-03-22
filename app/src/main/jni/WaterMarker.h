//
// Created by Dai on 2018/3/18.
//

#ifndef ANDROID_X264_ENCODER_WATERMARKER_H
#define ANDROID_X264_ENCODER_WATERMARKER_H

#endif //ANDROID_X264_ENCODER_WATERMARKER_H



#import "libavformat/avformat.h"
#import "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavutil/imgutils.h"
#include "libavfilter/buffersrc.h"
#include <android/log.h>

#define TAG "AVFilterHelper"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

int initAVFilter(int width,int height,int fps);
int addWaterMarker(unsigned char* buf,int length,unsigned char* outbuf);
void closeAVFilter();