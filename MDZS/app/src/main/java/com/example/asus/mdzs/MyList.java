package com.example.asus.mdzs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * @Created by zsh on 2018/11/23 17:12
 * @des
 */
public class MyList extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_list);

        List<String> list = new ArrayList<>();
        list.add("莫&玄&羽\n" +
                "以&血&为&媒& 以&手&画&就& 肉&身&献&灵& 魂&归&大&地");
        list.add("在&此&恭&候&夷&陵&老&祖& 魏&无&羡&！&！&！");
        list.add("莫子渊\n" +
                "装&什&么&死&呢&你&！& 你&个&死&疯&子& 吃&我&家&的&住&我&家&的& 那&你&几&个&破&东&西&怎&么&了&？&！& 还&敢&去&告&状&？");
        list.add("死&疯&子 &一&天&到&晚&搞&这&些&邪&里&邪&气&的&东&西 &还&要&充&我&表&哥&？&！&别&做&梦&了&！");
        list.add("莫&玄&羽&—&—&魏&无&羡\n" +"&（&被&踹&醒&）&");
        list.add("我&.&.&我&这&是&在&哪&儿&？");
        list.add("莫&子&渊\n" +
                "今&天&你&就&给&我&好&好&呆&在&这&儿&！&家&里&有&重&要&的&客&人&来&，&别&滚&出&来&丢&人&现&眼&！\n");
        list.add("魏&无&羡&（&小&声&嘀&咕&）&\n" +
                "嘿&.&.&重&要&的&客&人& &有&趣&…&\n");
        list.add("莫&夫&人\n" +
                "久&闻&仙&门&世&家&子&弟&各&个&少&年&英&豪 &今&日&一&见& &哎&呦&~\n");
        list.add("果&然&是&仪&表&堂&堂& &器&宇&轩&昂& &意&气&风&发& &英&姿&飒&爽& &人&中&龙&凤&啊&");
        list.add("犬&子&也&曾&粗&习&过&仙&术& &怎&奈&得&师&傅&修&为&太&低& &没&能&进&仙&门& &我&看&呐&.&.");
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
        list.add("魏&无&羡\n" +
                "吼& &不&挺&好&的&一&张&脸&嘛& &画&的&跟&老&吊&爷&一&样&\n");
        list.add("不&过&嘛& &如&今&成&了&个&疯&子& &倒&也&挺&好& &还&好&巧&不&巧&的&碰&上&了&蓝&家&的&人&");


        ListView vListView = findViewById(R.id.listView);
        vListView.setAdapter(new ListAdapter(list));
    }


    private class ListAdapter extends BaseAdapter {

        private List<String> list;

        private ListAdapter(List<String> list) {
            this.list = list;
        }

        @Override
        public int getCount() {
            return list == null ? 0 : list.size();
        }

        @Override
        public Object getItem(int position) {
            return null;
        }

        @Override
        public long getItemId(int position) {
            return 0;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {

            ViewHolder holder;
            if (convertView == null) {
                convertView = getLayoutInflater().inflate(R.layout.item_list, parent, false);
                holder = new ViewHolder(convertView);
                convertView.setTag(holder);
            } else {
                holder = (ViewHolder) convertView.getTag();
            }

            String text = list.get(position).replaceAll("&","");
            holder.vContent.setText(text);

            return convertView;
        }

        class ViewHolder {
            TextView vContent;

            public ViewHolder(View view) {
                vContent = (TextView) view.findViewById(R.id.tv_content);
            }
        }
    }
}
