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



public class Chapter236 extends AppCompatActivity {

    private TextView vTextView;
    private long lastBack;
    private int index = 0;
    private List<String> list;

    private Handler mHandler = new Handler();
    private boolean lock = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter236);
        list = new ArrayList<>();
        list.add("蓝&启&仁\n" +
                "蓝&氏&先&祖&安&，&出&身&庙&宇&，&聆&梵&音&长&成&，&通&慧&灵&性&，&笃&志&好&学&，&志&向&过&人&，&升&座&说&法&，&群&贤&毕&至&，&参&禅&证&悟&，&达&闻&于&世");
        list.add("弱&冠&之&龄&，&取&伽&蓝&之&蓝&还&俗&，&以&乐&师&为&业&，&善&音&律&，&工&琴&笛&，&求&仙&问&道&，&行&遍&天&下");
        list.add("途&径&姑&苏&，&遇&天&定&之&人&结&为&道&侣&，&同&进&共&退&，&奠&定&蓝&氏&基&业");
        list.add("仙&侣&身&殒&，&复&归&寺&中&.&.&.&.&.&.");

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
                Intent intent = new Intent(Chapter236.this,MyList.class);
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
                    Intent intent = new Intent(Chapter236.this, Chapter237.class);
                    startActivity(intent);
                    overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                    finish();
                }
            });
        }
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter236.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}