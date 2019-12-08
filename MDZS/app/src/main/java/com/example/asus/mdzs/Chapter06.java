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


public class Chapter06 extends AppCompatActivity {

    private TextView vTextView;
    private long lastBack;
    private int index = 0;
    private List<String> list;

    private Handler mHandler = new Handler();
    private boolean lock = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter06);
        list = new ArrayList<>();
        list.add("蓝&愿\n" +
                "咳&.&.&.&.&莫&夫&人& &此&番&与&景&仪&前&来&是&为&招&阴&除&尸&一&事& &您&之&前&说&莫&家&庄&后&山&的&走&尸&是&最&近&才&泛&滥&的&\n");
        list.add("莫&夫&人&\n" +
                "是&啊& &有&些&都&侵&扰&到&庄&内&了& &最&近&还&来&了&一&些&仙&门&高&人& 说&是&要&来&什&么& &夜&猎&\n");
        list.add("蓝&愿\n" +
                "阿& &修&仙&者&喜&游&历&四&方& &除&魔&降&妖& &而&魔&物&又&常&在&夜&间&行&动& &故&有&此&名&\n");
        list.add("莫&夫&人\n" +
                "啊& &原&来&是&这&呐& &哎&哟& &这&次&还&要&麻&烦&各&位&仙&人&帮&忙&招&阴&除&尸& &还&真&是&不&好&意&思&呐&\n");
        list.add("蓝&愿\n" +
                "这&是&我&们&应&该&做&的& &夫&人&不&必&操&心&\n");
        list.add("不&过& &有&一&事&请&夫&人&务&必&转&告&庄&内&所&有&人");
        list.add("傍&晚&以&后&紧&闭&门&户& &不&要&靠&近&后&院& &更&不&要&动&招&阴&阵&内&的&任&何&东&西&");
        list.add("莫&夫&人\n" +
                "哎&呀& &我&这&就&让&下&人&去&通&知& &那&就&有&劳&仙&人&们&了&\n");


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
                Intent intent = new Intent(Chapter06.this,MyList.class);
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
                    Intent intent = new Intent(Chapter06.this,Chapter07.class);
                    startActivity(intent);
                    overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                    finish();
                }
            });
        }
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter06.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}