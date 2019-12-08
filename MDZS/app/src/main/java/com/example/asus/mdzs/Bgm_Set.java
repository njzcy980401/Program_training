package com.example.asus.mdzs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class Bgm_Set extends AppCompatActivity {
private  MainApplication mApplication;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bgm__set);
        mApplication = (MainApplication)getApplication();
    }

    public  void myClickStart(View view){
        mApplication.mMediaPlayer.start();
    }

    public void myClickStop(View view){
        mApplication.mMediaPlayer.pause();
    }
}
