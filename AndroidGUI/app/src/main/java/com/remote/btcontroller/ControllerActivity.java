package com.remote.btcontroller;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.os.AsyncTask;
import android.content.Intent;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.HapticFeedbackConstants;
import android.view.MotionEvent;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothSocket;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import java.io.IOException;
import java.util.UUID;
import java.util.Calendar;
import java.lang.Character;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class ControllerActivity extends AppCompatActivity implements OnTouchListener
{
    // Initialization
    int flag       = 0;
    String command = null;
    Toast message  = null;

    ImageButton btn_sync;
    Button btn_p1;
    Button btn_p2;
    Button btn_up;
    Button btn_down;
    Button btn_left;
    Button btn_right;
    Button btn_a;
    Button btn_b;
    Button btn_start;
    Button btn_select;

    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter mBluetooth   = null;
    BluetoothSocket btSocket      = null;
    private boolean isBtConnected = false;
    static final UUID mUUID       = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        // Receive the address of the bluetooth device
        Intent newIntent = getIntent();
        address = newIntent.getStringExtra(MainActivity.EXTRA_ADDRESS);

        setContentView(R.layout.activity_bt_controller);

        // Call the buttons
        btn_sync   = (ImageButton)findViewById(R.id.btn_sync);
        btn_p1     = (Button)findViewById(R.id.btn_p1);
        btn_p2     = (Button)findViewById(R.id.btn_p2);
        btn_up     = (Button)findViewById(R.id.btn_up);
        btn_down   = (Button)findViewById(R.id.btn_down);
        btn_left   = (Button)findViewById(R.id.btn_left);
        btn_right  = (Button)findViewById(R.id.btn_right);
        btn_a      = (Button)findViewById(R.id.btn_a);
        btn_b      = (Button)findViewById(R.id.btn_b);
        btn_start  = (Button)findViewById(R.id.btn_start);
        btn_select = (Button)findViewById(R.id.btn_select);

        // Call the class to connect
        new btConnect().execute();

        // Listen for button presses and send the commands
        btn_sync.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                view.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY);
                msg("Time synchronized");
                DateFormat df = new SimpleDateFormat("HH:mm:ss MM-dd-yy");
                String date = df.format(Calendar.getInstance().getTime());
                btWrite("z" + date + "\0");
            }
        });

        btn_p1.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                view.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY);
                msg("You are Player 1");
                disablePlayerButtons();
                flag = 1;
                command = "qwertyui";
            }
        });

        btn_p2.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                view.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY);
                msg("You are Player 2");
                disablePlayerButtons();
                flag = 1;
                command = "asdfghjk";
            }
        });

        btn_up.setOnTouchListener(this);
        btn_down.setOnTouchListener(this);
        btn_left.setOnTouchListener(this);
        btn_right.setOnTouchListener(this);
        btn_a.setOnTouchListener(this);
        btn_b.setOnTouchListener(this);
        btn_start.setOnTouchListener(this);
        btn_select.setOnTouchListener(this);
    }

    public void disablePlayerButtons()
    {
        btn_p1.setEnabled(false);
        btn_p1.setClickable(false);
        btn_p2.setEnabled(false);
        btn_p2.setClickable(false);
    }

    @Override
    public boolean onTouch(View view, MotionEvent event)
    {
        // If the button is pressed
        if (flag == 0)
        {
            msg("You must choose a player!");
            return true;
        }

        if (event.getActionMasked() == MotionEvent.ACTION_DOWN)
        {
            view.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY);
            switch (view.getId())
            {
                case R.id.btn_up:
                    btWrite(Character.toString(command.charAt(0)) + "\0");
                    break;

                case R.id.btn_down:
                    btWrite(Character.toString(command.charAt(1)) + "\0");
                    break;

                case R.id.btn_left:
                    btWrite(Character.toString(command.charAt(2)) + "\0");
                    break;

                case R.id.btn_right:
                    btWrite(Character.toString(command.charAt(3)) + "\0");
                    break;

                case R.id.btn_a:
                    btWrite(Character.toString(command.charAt(4)) + "\0");
                    break;

                case R.id.btn_b:
                    btWrite(Character.toString(command.charAt(5)) + "\0");
                    break;

                case R.id.btn_start:
                    btWrite(Character.toString(command.charAt(6)) + "\0");
                    break;

                case R.id.btn_select:
                    btWrite(Character.toString(command.charAt(7)) + "\0");
                    break;
            }
        }

        // If the button is released or dragged out of view
        if ((event.getActionMasked() == MotionEvent.ACTION_UP) ||
                (event.getActionMasked() == MotionEvent.ACTION_CANCEL))
        {
            switch (view.getId())
            {
                case R.id.btn_up:
                    btWrite(Character.toString(command.charAt(0)).toUpperCase() + "\0");
                    break;

                case R.id.btn_down:
                    btWrite(Character.toString(command.charAt(1)).toUpperCase() + "\0");
                    break;

                case R.id.btn_left:
                    btWrite(Character.toString(command.charAt(2)).toUpperCase() + "\0");
                    break;

                case R.id.btn_right:
                    btWrite(Character.toString(command.charAt(3)).toUpperCase() + "\0");
                    break;

                case R.id.btn_a:
                    btWrite(Character.toString(command.charAt(4)).toUpperCase() + "\0");
                    break;

                case R.id.btn_b:
                    btWrite(Character.toString(command.charAt(5)).toUpperCase() + "\0");
                    break;

                case R.id.btn_start:
                    btWrite(Character.toString(command.charAt(6)).toUpperCase() + "\0");
                    break;

                case R.id.btn_select:
                    btWrite(Character.toString(command.charAt(7)).toUpperCase() + "\0");
                    break;
            }
        }
        return true;
    }

    // Make a toast notification
    private void msg(String s)
    {
        if (message != null)
        {
            message.cancel();
        }
        message = Toast.makeText(getApplicationContext(), s, Toast.LENGTH_SHORT);
        message.show();
    }

    @Override
    public void onBackPressed()
    {
        btDisconnect();
    }

    private void btDisconnect()
    {
        // If the btSocket is busy
        if (btSocket != null)
        {
            try
            {
                // Close the connection
                msg("Disconnected");
                btSocket.close();
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }

        finish();
    }

    private void btWrite(String m)
    {
        // If the btSocket is busy
        if (btSocket != null)
        {
            try
            {
                // Write to the connected Bluetooth device
                btSocket.getOutputStream().write(m.toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private class btConnect extends AsyncTask<Void, Void, Void>
    {
        // Almost connected
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            // Show progress dialog
            progress = ProgressDialog.show(ControllerActivity.this, "Please Wait",
                    "Connecting to device...");
        }

        @Override
        protected Void doInBackground(Void ... devices)
        {
            // While progress dialog is shown, connection is done in background
            try
            {
                // If the btSocket is not busy or no device is connected
                if ((btSocket == null) || !isBtConnected)
                {
                    // Get the mobile bluetooth device
                    mBluetooth = BluetoothAdapter.getDefaultAdapter();
                    // Connect to the device address and checks if available
                    BluetoothDevice device = mBluetooth.getRemoteDevice(address);
                    // Create an SPP connection
                    btSocket = device.createInsecureRfcommSocketToServiceRecord(mUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    // Start the connection
                    btSocket.connect();
                }
            }
            catch (IOException e)
            {
                // If connection failed, check the exception
                ConnectSuccess = false;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result)
        {
            // Check if everything worked after connecting in the background
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection failed, try again");
                finish();
            }
            else
            {
                msg("Connected");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
