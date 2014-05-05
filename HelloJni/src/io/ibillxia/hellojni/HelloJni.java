package io.ibillxia.hellojni;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import io.ibillxia.hellojni.R;
import io.ibillxia.hellojni.HelloCal;

public class HelloJni extends Activity {
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.hello_jni);
        
        Button btn = (Button)findViewById(R.id.btn_cal);
        btn.setOnClickListener(new Button.OnClickListener() {
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				TextView tv1 = (TextView) findViewById(R.id.textView1);
				TextView tv2 = (TextView) findViewById(R.id.textView2);
				TextView tv3 = (TextView) findViewById(R.id.textView3);
				
				int a = Integer.parseInt(tv1.getText().toString());
				int b = Integer.parseInt(tv2.getText().toString());
				HelloCal cal = new HelloCal();
				int c = cal.helloAdd(a,b);
				tv3.setText("计算结果为： " + Integer.toString(c));
			}
        });
    }

}
