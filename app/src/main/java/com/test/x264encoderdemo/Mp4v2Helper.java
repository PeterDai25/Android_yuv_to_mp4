package com.test.x264encoderdemo;

import android.util.Log;

/**
 * Created by dai on 2018/3/16.
 */

public class Mp4v2Helper {
    public static native int initMp4Encoder(String outputFilePath, int width, int height, int fps);

    public static native int mp4VEncode(byte[] data, int size);


    public static native void closeMp4Encoder();

    static {
        System.loadLibrary("Mp4v2Helper");
    }
}
