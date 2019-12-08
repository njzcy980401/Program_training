package com.example.asus.mdzs;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class Chapter07 extends AppCompatActivity {
    private long lastBack;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter07);
        findViewById(R.id.button2).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Chapter07.this,MyList.class);
                startActivity(intent);
            }
        });
        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Chapter07.this,Chapter08.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out_long,R.anim.fade_in_long);
                finish();
            }
        });
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter07.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }
}
