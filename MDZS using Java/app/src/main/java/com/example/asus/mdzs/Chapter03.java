package com.example.asus.mdzs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.content.Intent;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;


public class Chapter03 extends AppCompatActivity {

    private TextView vTextView;
    private long lastBack;
    private int index = 0;
    private List<String> list;

    private Handler mHandler = new Handler();
    private boolean lock = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter03);
        list = new ArrayList<>();
        list.add("魏&无&羡\n" +
                "啊&！&！ & 这&血&阵&！&是&以&自&残&完&成&愿&望&的&献&舍&禁&术&！\n");
        list.add("献&舍&禁&术&所&招&之&鬼&神&必&须&完&成&施&术&者&的&心&愿& 否&则&将&诅&咒&反&噬");
        list.add("这&血&阵& 这&伤&痕& 这&生&前&是&有&多&惨 &才&会&割&肉&献&身");
        list.add("不&过&.&. 这&招&了&我&也&就&罢&了 &莫&玄&羽& 那&也&起&码&告&诉&我&愿&望&是&什&么&吧& 是&暴&揍&一&顿&？&还&是");
        list.add("杀&&人&&灭&&门&&呢");

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
                Intent intent = new Intent(Chapter03.this,MyList.class);
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
                    Intent intent = new Intent(Chapter03.this,Chapter04.class);
                    startActivity(intent);
                    overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                    finish();
                }
            });
        }
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter03.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}