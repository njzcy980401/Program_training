package com.example.asus.mdzs;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class Chapter18 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter18);
        findViewById(R.id.button6).setOnClickListener( new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Chapter18.this,Chapter19.class);
                startActivity(intent);
                overridePendingTransition(R.anim.fade_out_long,R.anim.fade_in_long);
                finish();
            }
        });
    }
}
