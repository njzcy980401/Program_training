package com.example.asus.mdzs;


import android.content.Intent;
import android.graphics.Typeface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.awt.font.TextAttribute;

public class ChapterStart02 extends AppCompatActivity {
    private TextView texts;
    private  TextView text2;
    private Button mBtn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter_start02);
        texts = findViewById(R.id.textView);
        texts.setTypeface(Typeface.createFromAsset(getAssets(),"C299-苏新诗古印宋简.ttf"));
        texts.setEnabled(false);
       text2 = findViewById(R.id.textView2);
       text2.setTypeface(Typeface.createFromAsset(getAssets(),"C299-苏新诗古印宋简.ttf"));
       text2.setEnabled(false);
        mBtn = findViewById(R.id.blank);
        mBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChapterStart02.this,Chapter2.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                finish();
            }
        });
    }
}
