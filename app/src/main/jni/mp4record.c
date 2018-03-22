//
//  mp4record.c
//

#import "mp4record.h"
#import <stdlib.h>
#import "string.h"


MP4V2_CONTEXT *initMp4Encoder(const char *filename, int width, int height, int fps) {
    MP4V2_CONTEXT *recordCtx = (MP4V2_CONTEXT *) malloc(sizeof(struct MP4V2_CONTEXT));
    if (!recordCtx) {
        printf("error : malloc context \n");
        return NULL;
    }

    recordCtx->m_vWidth = width;
    recordCtx->m_vHeight = height;
    recordCtx->m_vFrateR = fps;
    recordCtx->m_vTimeScale = 90000;
    recordCtx->m_vFrameDur = 3000;

    recordCtx->m_aTrackId = MP4_INVALID_TRACK_ID;


    recordCtx->m_mp4FHandle = MP4Create(filename, 0);
    if (recordCtx->m_mp4FHandle == MP4_INVALID_FILE_HANDLE) {
        LOGE("error : MP4Create  \n");
        return NULL;
    }
    //------------------------------------------------------------------------------------- Video track
    recordCtx->m_vTrackId = MP4AddH264VideoTrack(recordCtx->m_mp4FHandle, 90000, 90000 / fps, width,
                                                 height,
                                                 0x64, //sps[1] AVCProfileIndication
                                                 0x00, //sps[2] profile_compat
                                                 0x1f, //sps[3] AVCLevelIndication
                                                 3); // 4 bytes length before each NAL unit;
    MP4SetTimeScale(recordCtx->m_mp4FHandle, recordCtx->m_vTimeScale);
    LOGD("initMp4Encoder success\n");
    //------------------------------------------------------------------------------------- Audio track
    //You may need to build libfaac and add the audio track.
    /*
    recordCtx->m_aTrackId = MP4AddAudioTrack(recordCtx->m_mp4FHandle, 48000, 300000, MP4_MPEG4_AUDIO_TYPE);
    if (recordCtx->m_aTrackId == MP4_INVALID_TRACK_ID){
        LOGE("error : MP4AddAudioTrack  \n");
        return NULL;
    }

    MP4SetAudioProfileLevel(recordCtx->m_mp4FHandle, 2);// 2, 1//    uint8_t aacConfig[2] = {18,16};
    uint8_t aacConfig[2] = {0x14, 0x10};
    uint8_t aacConfig[2] = {0x15,0x88};
    MP4SetTrackESConfiguration(recordCtx->m_mp4FHandle,recordCtx->m_aTrackId,aacConfig,2);
    LOGV("ok  : initMp4Encoder file=%s  \n",filename);
    */
    return recordCtx;
}

int mp4VEncode(MP4V2_CONTEXT *recordCtx, uint8_t *_naluData, int _naluSize) {

    printf("mp4vencode\n");
    MP4WriteSample(recordCtx->m_mp4FHandle, recordCtx->m_vTrackId, _naluData, _naluSize,
                   MP4_INVALID_DURATION, 0, 1);
    return 0;
}


void closeMp4Encoder(MP4V2_CONTEXT *recordCtx) {
    if (recordCtx) {
        if (recordCtx->m_mp4FHandle != MP4_INVALID_FILE_HANDLE) {
            MP4Close(recordCtx->m_mp4FHandle, 0);
            recordCtx->m_mp4FHandle = NULL;
        }

        free(recordCtx);
        recordCtx = NULL;
    }

    LOGD("closeMp4Encoder\n");
}
