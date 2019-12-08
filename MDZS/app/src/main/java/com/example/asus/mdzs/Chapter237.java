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



public class Chapter237 extends AppCompatActivity {

    private TextView vTextView;
    private long lastBack;
    private int index = 0;
    private List<String> list;

    private Handler mHandler = new Handler();
    private boolean lock = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chapter237);
        list = new ArrayList<>();
        list.add("金&家&弟&子&\n" +
                "那&蓝&安&谪&仙&一&般&，&不&知&他&的&天&定&之&人&，&是&何&等&超&凡&脱&俗&的&仙&子");
        list.add("如&今&仙&门&百&家&也&不&乏&清&丽&绝&伦&的&仙&子");
        list.add("子&轩&兄");
        list.add("你&看&哪&位&仙&子&最&优&？");

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
                Intent intent = new Intent(Chapter237.this,MyList.class);
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
                    Intent intent = new Intent(Chapter237.this,Chapter238.class);
                    startActivity(intent);
                    overridePendingTransition(R.anim.fade_out,R.anim.fade_in);
                    finish();
                }
            });
        }
    }
    public void onBackPressed(){
        if(lastBack == 0|| System.currentTimeMillis() - lastBack > 2000){
            Toast.makeText(Chapter237.this,"再按一次退出当前进度",Toast.LENGTH_LONG).show();
            lastBack = System.currentTimeMillis();
            return;
        }
        super.onBackPressed();

    }

}
