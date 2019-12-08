package com.example.asus.mdzs;

import android.content.Intent;
import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


public class ChpaterStart00 extends AppCompatActivity {
     private TextView texts;
     private Button mBtn;
    private long lastBack;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chpater_start00);
        texts = findViewById(R.id.textView);
        texts.setTypeface(Typeface.createFromAsset(getAssets(),"C299-苏新诗古印宋简.ttf"));
        texts.setEnabled(false);
        mBtn = findViewById(R.id.blank);
        mBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChpaterStart00.this,Chapter00.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                finish();
            }
        });
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(ChpaterStart00.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }
}
