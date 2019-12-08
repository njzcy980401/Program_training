package com.example.asus.mdzs;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class ChooseChapter extends AppCompatActivity {
  private  long lastBack;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choose_chapter);
        findViewById(R.id.button3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChooseChapter.this,ChpaterStart00.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                finish();
            }
        });
        findViewById(R.id.button4).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChooseChapter.this,ChapterStart02.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                finish();
            }
        });

        findViewById(R.id.button5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChooseChapter.this,Video_view.class);
                startActivity(intent);
            }
        });
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(ChooseChapter.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }
}
