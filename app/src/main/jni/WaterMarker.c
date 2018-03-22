//
// Created by Dai on 2018/3/18.
//

#include "WaterMarker.h"

AVFilterGraph *filter_graph;


AVFilterContext *buffersrc_ctx;

AVFilterContext *buffersink_ctx;

const char *filters_descr = "drawtext=fontfile=/system/fonts/Arial.ttf:fontcolor=white:fontsize=30:text='PeterDai25'";
//const char *filters_descr = "boxblur";
AVFrame *frame_in;

unsigned char *frame_buffer_in;

AVFrame *frame_out;

unsigned char *frame_buffer_out;

int initAVFilter(int width, int height, int fps){
    char args[512];
    int ret;
    av_register_all();
    avfilter_register_all();
    AVFilter *buffersrc  = avfilter_get_by_name("buffer");
    AVFilter *buffersink = avfilter_get_by_name("ffbuffersink");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs  = avfilter_inout_alloc();
    enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };
    AVBufferSinkParams *buffersink_params;
    filter_graph = avfilter_graph_alloc();
    if(!filter_graph){
        LOGE("alloc filter graph alloc failed\n");
    }
    /* buffer video source: the decoded frames from the decoder will be inserted here. */
    snprintf(args, sizeof(args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             width, height, AV_PIX_FMT_YUV420P,
             1, fps, width, height);
    LOGD("arg %s",args);
    ret = avfilter_graph_create_filter(&buffersrc_ctx, buffersrc, "in",
                                       args, NULL, filter_graph);
    if (ret < 0) {
        LOGE("Cannot create buffer source %d\n",ret);
        return ret;
    }

    /* buffer video sink: to terminate the filter chain. */
    buffersink_params = av_buffersink_params_alloc();
    buffersink_params->pixel_fmts = pix_fmts;
    ret = avfilter_graph_create_filter(&buffersink_ctx, buffersink, "out",
                                       NULL, buffersink_params, filter_graph);
    av_free(buffersink_params);
    if (ret < 0) {
        LOGE("Cannot create buffer sink\n");
        return ret;
    }
    /* Endpoints for the filter graph. */
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = buffersrc_ctx;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    inputs->name       = av_strdup("out");
    inputs->filter_ctx = buffersink_ctx;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filters_descr,
                                        &inputs, &outputs, NULL)) < 0){
        LOGE("parse_ptr_error %d\n",ret);
        return ret;
    }


    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0){
        LOGE("avfilter_graph_config %d\n",ret);
        return ret;
    }

    frame_in=av_frame_alloc();
    frame_buffer_in=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, width,height,1));
    av_image_fill_arrays(frame_in->data, frame_in->linesize,frame_buffer_in,
                         AV_PIX_FMT_YUV420P,width,height,1);

    frame_out=av_frame_alloc();
    frame_buffer_out=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, width,height,1));
    av_image_fill_arrays(frame_out->data, frame_out->linesize,frame_buffer_out,
                         AV_PIX_FMT_YUV420P,width, height,1);

    frame_in->width=width;
    frame_in->height=height;
    frame_in->format=AV_PIX_FMT_YUV420P;

    return 0;
}


int addWaterMarker(unsigned char* buf, int length,unsigned char* outbuf){
    unsigned char* frame_buffer_in = buf;
    int in_width = frame_in->width;
    int in_height = frame_in->height;
    if(length != (in_width*in_height*3/2)){
        return -1;
    }
    //input Y,U,V
    frame_in->data[0]=frame_buffer_in;
    frame_in->data[1]=frame_buffer_in+(in_width*in_height);
    frame_in->data[2]=frame_buffer_in+(in_width*in_height*5/4);

    if (av_buffersrc_add_frame(buffersrc_ctx, frame_in) < 0) {
        LOGE( "Error while add frame.\n");
        return -1;
    }

    /* pull filtered pictures from the filtergraph */
    int ret = av_buffersink_get_frame(buffersink_ctx, frame_out);
    if (ret < 0)
        return -1;

    //output Y,U,V
    int i = 0;
    if(frame_out->format==AV_PIX_FMT_YUV420P){
        memcpy(outbuf,frame_out->data[0],in_width*in_height);
        memcpy(outbuf+in_width*in_height,frame_out->data[1],in_width*in_height/4);
        memcpy(outbuf+in_width*in_height*5/4,frame_out->data[2],in_width*in_height/4);
    }

    av_frame_unref(frame_out);
    return 0;
}

void closeAVFilter(){
    av_frame_free(&frame_in);
    av_frame_free(&frame_out);
    avfilter_graph_free(&filter_graph);
    return;
}