package neshah.bluetooth1;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.widget.Toast;

import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.net.URI;
import java.util.ArrayList;
import java.util.List;

import java.io.OutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Method;
import java.util.Calendar;
import java.util.UUID;

public class Bluetooth extends Activity {
	private static final String TAG = "bluetooth";
	private static final String MAC = "00:06:66:6A:4D:6A";
	private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

	Button breakfast, lunch, dinner;
	Button morning_snack, afternoon_snack, night_snack;
	Button my_fitness_pal;

	private BluetoothAdapter adapter = null;
	private BluetoothSocket socket = null;
	private OutputStream outStream = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth);

	    adapter = BluetoothAdapter.getDefaultAdapter();
	    checkBluetooth();

	    final String apiKey = "S46FSOLJPJW409G8";

	    breakfast       = (Button) findViewById(R.id.breakfast);
	    lunch           = (Button) findViewById(R.id.lunch);
	    dinner          = (Button) findViewById(R.id.dinner);
	    morning_snack   = (Button) findViewById(R.id.morning_snack);
	    afternoon_snack = (Button) findViewById(R.id.afternoon_snack);
	    night_snack     = (Button) findViewById(R.id.night_snack);
	    my_fitness_pal  = (Button) findViewById(R.id.my_fitness_pal);

	    breakfast.setOnClickListener(new View.OnClickListener() {
		    @Override
		    public void onClick(View v) {
				//sendData("k"); // kill buzzer
			    try { // post meal to thingspeak
				    Calendar calendar = Calendar.getInstance();
				    String time = "" + calendar.get(Calendar.HOUR) + "-"
						    + calendar.get(Calendar.MINUTE) + ","
						    + calendar.get(Calendar.MONTH) + "-"
						    + calendar.get(Calendar.DAY_OF_MONTH) + "-"
						    + calendar.get(Calendar.YEAR);

				    HttpClient client = new DefaultHttpClient();
				    String url = "https://api.thingspeak.com/update";
				    HttpPost post = new HttpPost(url);

				    List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
					results.add(new BasicNameValuePair("key", apiKey));
				    results.add(new BasicNameValuePair("field1", "2"));
				    results.add(new BasicNameValuePair("field2", time));

				    try {
					    post.setEntity(new UrlEncodedFormEntity(results));
				    } catch (UnsupportedEncodingException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "Cannot set values for post", e);
				    }

				    try {
					    client.execute(post);
				    } catch (ClientProtocolException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "client protocol exception", e);
				    } catch (IOException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "io exception", e);
				    }
			    } catch (Exception e) {
				    e.printStackTrace();
			    }
		    }
	    });

		lunch.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				sendData("k"); // kill buzzer
				try { // post meal to thingspeak
					Calendar calendar = Calendar.getInstance();
					String time = "" + calendar.get(Calendar.HOUR) + "-"
							+ calendar.get(Calendar.MINUTE) + ","
							+ calendar.get(Calendar.MONTH) + "-"
							+ calendar.get(Calendar.DAY_OF_MONTH) + "-"
							+ calendar.get(Calendar.YEAR);

					HttpClient client = new DefaultHttpClient();
					String url = "https://api.thingspeak.com/update";
					HttpPost post = new HttpPost(url);

					List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
					results.add(new BasicNameValuePair("key", apiKey));
					results.add(new BasicNameValuePair("field1", "2"));
					results.add(new BasicNameValuePair("field2", time));

					try {
						post.setEntity(new UrlEncodedFormEntity(results));
					} catch (UnsupportedEncodingException e) {
						// Auto-generated catch block
						Log.e(TAG, "Cannot set values for post", e);
					}

					try {
						client.execute(post);
					} catch (ClientProtocolException e) {
						// Auto-generated catch block
						Log.e(TAG, "client protocol exception", e);
					} catch (IOException e) {
						// Auto-generated catch block
						Log.e(TAG, "io exception", e);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});

	    dinner.setOnClickListener(new View.OnClickListener() {
		    @Override
		    public void onClick(View v) {
			    sendData("k"); // kill buzzer
			    try { // post meal to thingspeak
				    Calendar calendar = Calendar.getInstance();
				    String time = "" + calendar.get(Calendar.HOUR) + "-"
						    + calendar.get(Calendar.MINUTE) + ","
						    + calendar.get(Calendar.MONTH) + "-"
						    + calendar.get(Calendar.DAY_OF_MONTH) + "-"
						    + calendar.get(Calendar.YEAR);

				    HttpClient client = new DefaultHttpClient();
				    String url = "https://api.thingspeak.com/update";
				    HttpPost post = new HttpPost(url);

				    List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
				    results.add(new BasicNameValuePair("key", apiKey));
				    results.add(new BasicNameValuePair("field1", "2"));
				    results.add(new BasicNameValuePair("field2", time));

				    try {
					    post.setEntity(new UrlEncodedFormEntity(results));
				    } catch (UnsupportedEncodingException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "Cannot set values for post", e);
				    }

				    try {
					    client.execute(post);
				    } catch (ClientProtocolException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "client protocol exception", e);
				    } catch (IOException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "io exception", e);
				    }
			    } catch (Exception e) {
				    e.printStackTrace();
			    }
		    }
	    });

		morning_snack.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				sendData("k"); // kill buzzer
				try { // post meal to thingspeak
					Calendar calendar = Calendar.getInstance();
					String time = "" + calendar.get(Calendar.HOUR) + "-"
							+ calendar.get(Calendar.MINUTE) + ","
							+ calendar.get(Calendar.MONTH) + "-"
							+ calendar.get(Calendar.DAY_OF_MONTH) + "-"
							+ calendar.get(Calendar.YEAR);

					HttpClient client = new DefaultHttpClient();
					String url = "https://api.thingspeak.com/update";
					HttpPost post = new HttpPost(url);

					List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
					results.add(new BasicNameValuePair("key", apiKey));
					results.add(new BasicNameValuePair("field1", "1"));
					results.add(new BasicNameValuePair("field2", time));

					try {
						post.setEntity(new UrlEncodedFormEntity(results));
					} catch (UnsupportedEncodingException e) {
						// Auto-generated catch block
						Log.e(TAG, "Cannot set values for post", e);
					}

					try {
						client.execute(post);
					} catch (ClientProtocolException e) {
						// Auto-generated catch block
						Log.e(TAG, "client protocol exception", e);
					} catch (IOException e) {
						// Auto-generated catch block
						Log.e(TAG, "io exception", e);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});

	    afternoon_snack.setOnClickListener(new View.OnClickListener() {
		    @Override
		    public void onClick(View v) {
			    sendData("k"); // kill buzzer
			    try { // post meal to thingspeak
				    Calendar calendar = Calendar.getInstance();
				    String time = "" + calendar.get(Calendar.HOUR) + "-"
						    + calendar.get(Calendar.MINUTE) + ","
						    + calendar.get(Calendar.MONTH) + "-"
						    + calendar.get(Calendar.DAY_OF_MONTH) + "-"
						    + calendar.get(Calendar.YEAR);

				    HttpClient client = new DefaultHttpClient();
				    String url = "https://api.thingspeak.com/update";
				    HttpPost post = new HttpPost(url);

				    List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
				    results.add(new BasicNameValuePair("key", apiKey));
				    results.add(new BasicNameValuePair("field1", "1"));
				    results.add(new BasicNameValuePair("field2", time));

				    try {
					    post.setEntity(new UrlEncodedFormEntity(results));
				    } catch (UnsupportedEncodingException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "Cannot set values for post", e);
				    }

				    try {
					    client.execute(post);
				    } catch (ClientProtocolException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "client protocol exception", e);
				    } catch (IOException e) {
					    // Auto-generated catch block
					    Log.e(TAG, "io exception", e);
				    }
			    } catch (Exception e) {
				    e.printStackTrace();
			    }
		    }
	    });

		night_snack.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				sendData("k"); // kill buzzer
				try { // post meal to thingspeak
					Calendar calendar = Calendar.getInstance();
					String time = "" + calendar.get(Calendar.HOUR) + "-"
							+ calendar.get(Calendar.MINUTE) + ","
							+ calendar.get(Calendar.MONTH) + "-"
							+ calendar.get(Calendar.DAY_OF_MONTH) + "-"
							+ calendar.get(Calendar.YEAR);

					HttpClient client = new DefaultHttpClient();
					String url = "https://api.thingspeak.com/update";
					HttpPost post = new HttpPost(url);

					List<BasicNameValuePair> results = new ArrayList<BasicNameValuePair>();
					results.add(new BasicNameValuePair("key", apiKey));
					results.add(new BasicNameValuePair("field1", "1"));
					results.add(new BasicNameValuePair("field2", time));

					try {
						post.setEntity(new UrlEncodedFormEntity(results));
					} catch (UnsupportedEncodingException e) {
						// Auto-generated catch block
						Log.e(TAG, "Cannot set values for post", e);
					}

					try {
						client.execute(post);
					} catch (ClientProtocolException e) {
						// Auto-generated catch block
						Log.e(TAG, "client protocol exception", e);
					} catch (IOException e) {
						// Auto-generated catch block
						Log.e(TAG, "io exception", e);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});

	    my_fitness_pal.setOnClickListener(new View.OnClickListener() {
		    @Override
		    public void onClick(View v) {
			    try {
					Uri uri = Uri.parse("http://www.myfitnesspal.com");
				    Intent browse = new Intent(Intent.ACTION_VIEW, uri);
				    startActivity(browse);
			    } catch (Exception e) {
				    e.printStackTrace();
			    }
		    }
	    });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_bluetooth, menu);
        return true;
    }

	@Override
	public void onResume() {
		super.onResume();

		// Set up a pointer to the remote node using it's address.
		BluetoothDevice device = adapter.getRemoteDevice(MAC);

		// Two things are needed to make a connection:
		//   A MAC address, which we have above.
		//   A Service ID or UUID.  In this case we are using the
		//     UUID for SPP.

		try {
			socket = createSocket(device);
		} catch (IOException e1) {
			exit("socket create failed");
		}
		adapter.cancelDiscovery();

		// Establish the connection.  This will block until it connects.
		Log.d(TAG, "Connecting");
		try {
			socket.connect();
			Log.d(TAG, "Connected");
		} catch (IOException e) {
			try {
				socket.close();
			} catch (IOException e2) {
				exit("Unable to close socket during connection failure");
			}
		}

		// Create a data stream so we can talk to server.
		Log.d(TAG, "Create Socket");
		try {
			outStream = socket.getOutputStream();
		} catch (IOException e) {
			exit("output stream creation failed");
		}
	}

	@Override
	public void onPause() {
		super.onPause();

		if (outStream != null) {
			try {
				outStream.flush();
			} catch (IOException e) {
				exit("failed to flush output stream");
			}
		}

		try     {
			socket.close();
		} catch (IOException e2) {
			exit("failed to close socket");
		}
	}

	private BluetoothSocket createSocket(BluetoothDevice device) throws IOException {
		if (Build.VERSION.SDK_INT >= 10) {
			try {
				final Method method = device.getClass().getMethod("createInsecureRFCommSocketToServiceRecord", new Class[] { UUID.class });
				return (BluetoothSocket) method.invoke(device, MY_UUID);
			} catch (Exception e) {
				Log.d(TAG, "Could not create insecure RFComm socket", e);
			}
		}
		return device.createRfcommSocketToServiceRecord(MY_UUID);
	}

	private void checkBluetooth() {
		if (adapter == null) {
			exit("device does not support bluetooth");
		} else {
			if (adapter.isEnabled()) {
				Log.d(TAG, "Bluetooth enabled");
			} else {
				Intent enableBluetoothIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
				startActivityForResult(enableBluetoothIntent, 1);
			}
		}
	}

	private void exit(String message) {
		if (message != null) {
			Toast.makeText(getBaseContext(), message, Toast.LENGTH_LONG).show();
			finish();
		}
	}

	private void sendData(String message) {
		byte[] msgBuffer = message.getBytes();
		Log.d(TAG, "Send data: " + message);

		try {
			outStream.write(msgBuffer);
		} catch (IOException e) {
			String msg = "In onResume() and an exception occurred during write: " + e.getMessage();
			if (MAC.equals("00:00:00:00:00:00")) {
				msg += ".\n\nUpdate your server address from 00:00:00:00:00:00 to the correct address on line 35 in the java code";
			}
			msg += ".\n\nCheck that the SPP UUID: " + MY_UUID.toString() + " exists on server.\n\n";

			exit(msg);
		}
	}
}
