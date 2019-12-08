package com.example.asus.mdzs;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private long lastBack = 0;
    private Button mBtnks;
    private Button mBtnzzry;
    private ProgressBar vProgressBar;
    private Handler mHandler = new Handler();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mBtnzzry =(Button) findViewById(R.id.zzry);
        mBtnzzry.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this,Bgm_Set.class);
                startActivity(intent);
            }
        });
        findViewById(R.id.button7).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, zzry.class);
                startActivity(intent);
            }
        });
        mBtnks = (Button) findViewById(R.id.ks);
        mBtnks.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){

                mHandler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        Intent intent = new Intent(MainActivity.this,ChooseChapter.class);
                        startActivity(intent);
                        overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                        //vProgressBar.setVisibility(View.GONE);
                    }
                },500);
            }
        });
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(MainActivity.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}
