package edu.rosehulman.helloworld;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity implements OnClickListener {
	public final static String EXTRA_MESSAGE = "edu.rosehulman.helloworld.MESSAGE";
	
	private EditText mEditText;
	private Button mSendButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        this.mEditText = (EditText)findViewById(R.id.edit_message);
        this.mSendButton = (Button)findViewById(R.id.send_button);
        this.mSendButton.setOnClickListener(this);
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
		case R.id.send_button:
			Intent intent = new Intent(this, DisplayMessageActivity.class);
			String message = this.mEditText.getText().toString();
			intent.putExtra(EXTRA_MESSAGE, message);
			startActivity(intent);
			break;

		default:
			Log.d("ME435", "We should never have gotten here because there are no other buttons to click!");
			break;
		}
		
	}
    
}
