package com.example.asus.mdzs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.media.MediaPlayer;
import android.net.Uri;
import android.view.WindowManager;
import android.widget.Toast;
import android.widget.VideoView;

public class Video_view extends AppCompatActivity {
    private  VideoView vVideoView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(
                WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS,
                WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);// 全屏
        setContentView(R.layout.activity_video_view);

        vVideoView = findViewById(R.id.pv);

        vVideoView.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/raw/modzs"));
        vVideoView.start();

        vVideoView.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mp) {
                Toast.makeText(Video_view.this, "播放完成", Toast.LENGTH_SHORT).show();
                finish();
            }
        });
    }
}

