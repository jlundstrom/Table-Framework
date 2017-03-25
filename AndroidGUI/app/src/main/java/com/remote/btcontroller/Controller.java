package com.remote.btcontroller;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;

import java.io.IOException;
import java.util.UUID;

public class Controller extends AppCompatActivity implements OnTouchListener {

    Button btn_start;
    Button btn_select;
    Button btn_a;
    Button btn_b;
    Button btn_up;
    Button btn_down;
    Button btn_left;
    Button btn_right;
    Button btn_disconnect;

    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter mBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;

    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bt_controller);

        Intent newIntent = getIntent();
        address = newIntent.getStringExtra(MainActivity.EXTRA_ADDRESS);

        btn_start = (Button) findViewById(R.id.btn_start);
        btn_select = (Button) findViewById(R.id.btn_select);
        btn_a = (Button) findViewById(R.id.btn_a);
        btn_b = (Button) findViewById(R.id.btn_b);
        btn_up = (Button) findViewById(R.id.btn_up);
        btn_down = (Button) findViewById(R.id.btn_down);
        btn_left = (Button) findViewById(R.id.btn_left);
        btn_right = (Button) findViewById(R.id.btn_right);
        btn_disconnect = (Button) findViewById(R.id.btn_disconnect);

        new btConnect().execute();

        btn_disconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btDisconnect();
            }
        });

        btn_start.setOnTouchListener(this);
        btn_select.setOnTouchListener(this);
        btn_a.setOnTouchListener(this);
        btn_b.setOnTouchListener(this);
        btn_up.setOnTouchListener(this);
        btn_down.setOnTouchListener(this);
        btn_left.setOnTouchListener(this);
        btn_right.setOnTouchListener(this);
    }

    @Override
    public boolean onTouch(View view, MotionEvent event) {
        if (event.getActionMasked() == MotionEvent.ACTION_DOWN) {
            switch (view.getId()) {
                case R.id.btn_start:
                    btWrite("h\0");
                    break;
                case R.id.btn_select:
                    btWrite("j\0");
                    break;
                case R.id.btn_a:
                    btWrite("q\0");
                    break;
                case R.id.btn_b:
                    btWrite("e\0");
                    break;
                case R.id.btn_up:
                    btWrite("w\0");
                    break;
                case R.id.btn_down:
                    btWrite("s\0");
                    break;
                case R.id.btn_left:
                    btWrite("a\0");
                    break;
                case R.id.btn_right:
                    btWrite("d\0");
                    break;
            }
        }

        if (event.getActionMasked() == MotionEvent.ACTION_UP ||
                event.getActionMasked() == MotionEvent.ACTION_CANCEL) {
            switch (view.getId()) {
                case R.id.btn_start:
                    btWrite("H\0");
                    break;
                case R.id.btn_select:
                    btWrite("J\0");
                    break;
                case R.id.btn_a:
                    btWrite("Q\0");
                    break;
                case R.id.btn_b:
                    btWrite("E\0");
                    break;
                case R.id.btn_up:
                    btWrite("W\0");
                    break;
                case R.id.btn_down:
                    btWrite("S\0");
                    break;
                case R.id.btn_left:
                    btWrite("A\0");
                    break;
                case R.id.btn_right:
                    btWrite("D\0");
                    break;
            }
        }
        return true;
    }

    private void btDisconnect()
    {
        if (btSocket != null)
        {
            try
            {
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
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write(m.toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_LONG).show();
    }

    private class btConnect extends AsyncTask<Void, Void, Void>
    {

        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(Controller.this, "Connecting...", "Please wait");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if ( btSocket == null || !isBtConnected )
                {
                    mBluetooth = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = mBluetooth.getRemoteDevice(address);
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID); //create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }

            }
            catch (IOException e)
            {
                ConnectSuccess = false;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result)
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection failed. Is it SPP Bluetooth? Try again.");
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
