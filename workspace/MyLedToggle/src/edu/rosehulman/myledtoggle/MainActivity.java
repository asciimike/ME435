package edu.rosehulman.myledtoggle;

import edu.rosehulman.me435.AccessoryActivity;
import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import android.widget.ToggleButton;

public class MainActivity extends AccessoryActivity implements OnClickListener {
	
	private ToggleButton mLEDToggle;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		this.mLEDToggle = (ToggleButton) findViewById(R.id.led_toggle_button);
		this.mLEDToggle.setOnClickListener(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.led_toggle_button:
			if (this.mLEDToggle.isChecked()) {
				// turn LED on
				Toast.makeText(this, "Turn LED On!", Toast.LENGTH_SHORT).show();
				this.sendCommand("ON");
			} else {
				// turn LED off
				Toast.makeText(this, "Turn LED Off!", Toast.LENGTH_SHORT).show();
				this.sendCommand("OFF");
			}
			break;

		default:
			//Um ..........
			break;
		}
		
	}

}
