package com.example.asus.mdzs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.content.Intent;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.List;
import android.widget.Toast;


public class Chapter10 extends AppCompatActivity {

    private TextView vTextView;
    private long lastBack;
    private int index = 0;
    private List<String> list;

    private Handler mHandler = new Handler();
    private boolean lock = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter10);
        list = new ArrayList<>();
        list.add("魏&无&羡\n" +
                "这&招&阴&符&以&活&人&的&阳&气&为&饵&");
        list.add("看&来&这&俩&蓝&家&子&弟&是&要&用&自&己&引&出&走&尸&邪&祟&过&来& &一&网&打&尽&咯");
        list.add("嘿& &几&十&年&不&见& &蓝&家&也&会&用&这&种&法&子&了& &有&点&意&思& &反&正&也&无&聊& &跟&去&看&看&罢&");

        vTextView = findViewById(R.id.ChapterView00);

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!lock){
                    lock = true;
                    showNextText();
                }
            }
        });

        findViewById(R.id.button2).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Chapter10.this,MyList.class);
                startActivity(intent);
            }
        });
    }

    private void showNextText() {
        if (index<list.size()){
            vTextView.setText("");
            String result = list.get(index);
            final String[] spirtArr = result.split("&");
            new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < spirtArr.length; i++) {
                        try {
                            Thread.sleep(50);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                        final String s = spirtArr[i];
                        mHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                vTextView.setText(vTextView.getText().toString()+s);
                            }
                        });
                    }
                    index++;
                    lock = false;
                }
            }).start();
        }else{
            //不重复读取  去掉下面两行
            findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Intent intent = new Intent(Chapter10.this,Chapter1Evening.class);
                    startActivity(intent);
                    overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                    finish();
                }
            });
        }
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter10.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}