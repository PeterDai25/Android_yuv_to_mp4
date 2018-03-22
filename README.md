# Android_yuv_to_mp4
A simple demo shows how to encode yuv data to h264 with libx264 and create the MP4 file.
Support filters. 

Thanks @[android_x264_encoder](https://github.com/sszhangpengfei/android_x264_encoder "android_x264_encoder") and [Mp4v2Demo](https://github.com/chezi008/Mp4v2Demo "Mp4v2Demo")

## Tips
**The project has been tested on my Samsung Galaxy 5 (Android 4.4).**
- Raw yuv data come from back camera will be decoded to h264 file by libx264.
- Add filter with FFmpeg libavfilter.(Text,boxblur or anything support by avfilter).
- Finally , h264 stream converted to the mp4.
- You can both find "dai.mp4" and "dai.h264" under the sdcard directory.Play them with Potplayer or VLC.