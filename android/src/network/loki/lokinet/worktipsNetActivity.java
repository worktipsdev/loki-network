package network.worktips.worktipsnet;


import java.io.File;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.URL;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.app.Activity;

import android.content.Context;

import android.content.ComponentName;
import android.content.ServiceConnection;

import android.os.AsyncTask;
import android.content.Intent;
import android.os.Bundle;

import android.os.IBinder;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;


public class WorktipsNetActivity extends Activity {
	private static final String TAG = "worktipsnet-activity";
	private TextView textView;
	private static final String DefaultBootstrapURL = "https://seed.worktipsnet.org/bootstrap.signed";

	private AsyncBootstrap bootstrapper;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		textView = new TextView(this);
		setContentView(textView);
		System.loadLibrary("worktipsnetandroid");
	}


	private static void writeFile(File out, InputStream instream) throws IOException {
		OutputStream outstream = new FileOutputStream(out);
		byte[] buffer = new byte[512];
		int len;
		try {
			do {
				len = instream.read(buffer);
				if (len > 0) {
					outstream.write(buffer, 0, len);
				}
			}
			while (len != -1);
		} finally {
			outstream.close();
		}
	}

	public void startWorktipsnet()
	{
		if(bootstrapper != null)
			return;
		bootstrapper = new AsyncBootstrap();
		bootstrapper.execute(DefaultBootstrapURL);
	}

  
	public void runWorktipsnetService()
	{
		startService(new Intent(WorktipsNetActivity.this,
				WorktipsnetService.class));
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		textView = null;
	}

	public File getRootDir()
	{
		return getFilesDir();
	}

	private class AsyncBootstrap extends AsyncTask<String, String, String>
	{
		public String doInBackground(String ... urls) {
			try
			{
				File bootstrapFile = new File(getRootDir(), "bootstrap.signed");
				URL bootstrapURL = new URL(urls[0]);
				InputStream instream = bootstrapURL.openStream();
				writeFile(bootstrapFile, instream);
				instream.close();
				return getString(R.string.bootstrap_ok);
			}
			catch(Exception thrown)
			{
				return getString(R.string.bootstrap_fail) + ": " + throwableToString(thrown);
			}
		}
		public void onPostExecute(String val) {
			textView.setText(val);
			if(val.equals(getString(R.string.bootstrap_ok)))
				runWorktipsnetService();
			bootstrapDone();
		}
	}

	private void bootstrapDone()
	{
		bootstrapper = null;
	}

	private CharSequence throwableToString(Throwable tr) {
		StringWriter sw = new StringWriter(8192);
		PrintWriter pw = new PrintWriter(sw);
		tr.printStackTrace(pw);
		pw.close();
		return sw.toString();
	}

	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.options_main, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		
		switch(id){
			case R.id.action_start:
				startWorktipsnet();
				return true;
			case R.id.action_stop:
				return true;
		}
		
		return super.onOptionsItemSelected(item);
	}
	
}
