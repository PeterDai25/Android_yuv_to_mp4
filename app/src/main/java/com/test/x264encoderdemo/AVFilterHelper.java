package com.test.x264encoderdemo;

/**
 * Created by Dai on 2018/3/18.
 */

public class AVFilterHelper {

    public static native int initAVFilterHelper(int width, int height, int fps);

    public static native int addWatermark(byte[] data, int size, byte[] outdata);


    public static native void closeAVFilterHelper();

    static {
        System.loadLibrary("AVFilterHelper");
    }
}
