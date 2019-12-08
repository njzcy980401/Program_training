package com.example.asus.mdzs;



import android.app.Application;
import android.media.MediaPlayer;

import static com.example.asus.mdzs.R.*;

public class MainApplication extends Application {
    public MediaPlayer mMediaPlayer;

    @Override
    public  void  onCreate(){
        super.onCreate();

        mMediaPlayer = MediaPlayer.create(this, raw.snow);
        mMediaPlayer.setLooping(true);
        mMediaPlayer.start();
    }

}
