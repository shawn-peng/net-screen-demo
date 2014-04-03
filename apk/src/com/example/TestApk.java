package com.example;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.view.View;
import android.view.View.OnClickListener;
import com.framework.TestJar;

public class TestApk extends Activity
{
    TextView  txt; 
    Button    btn_on, btn_off;
    OnClickListener  listener;
    TestJar    tj;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
	txt = (TextView)findViewById(R.id.txt);
	btn_on = (Button)findViewById(R.id.btn_on);
	btn_off = (Button)findViewById(R.id.btn_off);
	tj = new TestJar();

	txt.setText("LED OFF");
	btn_on.setText("ON");
	btn_off.setText("OFF");

	listener = new OnClickListener() {
		public void onClick(View v) {
			String str = null;

			if (v == btn_on) {
				str = tj.led_on();
			} else if (v == btn_off) {
				str = tj.led_off();
			}
			txt.setText(str);
		}
	};

	btn_on.setOnClickListener(listener);
	btn_off.setOnClickListener(listener);
    }
}





