//
//  mp4record.h
//

#ifndef __RTSP_Player__mp4record__
#define __RTSP_Player__mp4record__

#import "mp4v2/mp4v2.h"
#include<android/log.h>

#define TAG "Mp4helper"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

#define  _NALU_SPS_  0
#define  _NALU_PPS_  1
#define  _NALU_I_    2
#define  _NALU_P_    3

typedef struct MP4V2_CONTEXT{
    int m_vWidth,m_vHeight,m_vFrateR,m_vTimeScale;
    MP4FileHandle m_mp4FHandle;
    MP4TrackId m_vTrackId,m_aTrackId;
    double m_vFrameDur;
} MP4V2_CONTEXT;

MP4V2_CONTEXT * initMp4Encoder(const char * filename,int width,int height,int fps);
int mp4VEncode(MP4V2_CONTEXT * recordCtx, uint8_t * data, int len);
int mp4AEncode(MP4V2_CONTEXT * recordCtx, uint8_t * data, int len);
void closeMp4Encoder(MP4V2_CONTEXT * recordCtx);

#endif 
