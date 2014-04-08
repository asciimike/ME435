package edu.rosehulman.hellobutton;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {
	
	private Button mButton;
	private Button mResetButton;
	private Button mSubmitButton;
	private EditText mNameEditText;
	private TextView mTextView;
	
	private String name;
	private int pressCount;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		this.mButton = (Button) findViewById(R.id.press_button);
		this.mResetButton = (Button) findViewById(R.id.reset_button);
		this.mSubmitButton = (Button) findViewById(R.id.submit_name_button);
		
		this.mButton.setOnClickListener(this);
		this.mResetButton.setOnClickListener(this);
		this.mSubmitButton.setOnClickListener(this);
		
		this.mNameEditText = (EditText) findViewById(R.id.user_edit_text);
		this.mTextView = (TextView) findViewById(R.id.press_text);
		
		this.name = "You";
		this.mTextView.setText(String.format(this.getString(R.string.button_start_message),this.name));
		this.pressCount = 0;
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.press_button:
			this.pressCount++;
			String text;
			if (this.pressCount == 1) {
				 text = String.format(this.getString(R.string.button_press_message),this.name, this.pressCount);
			} else {
				text = String.format(this.getString(R.string.button_press_message_plural),this.name, this.pressCount);
			}
			mTextView.setText(text);
			Toast.makeText(this, "You pressed the button", Toast.LENGTH_SHORT).show();
			break;
			
		case R.id.reset_button:
			this.pressCount = 0;
			this.name = "You";
			this.mTextView.setText(String.format(this.getString(R.string.button_start_message),this.name));
			Toast.makeText(this, "You reset the count", Toast.LENGTH_SHORT).show();
			break;
			
		case R.id.submit_name_button:
			this.name = this.mNameEditText.getText().toString();
			Toast.makeText(this, "Name changed to " + this.name, Toast.LENGTH_SHORT).show();
			break;

		default:
			break;
		}
	}

}
