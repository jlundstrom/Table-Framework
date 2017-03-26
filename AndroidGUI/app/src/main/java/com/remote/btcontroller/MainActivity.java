package com.remote.btcontroller;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.widget.TextView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.Set;

public class MainActivity extends AppCompatActivity
{
    // Initialization
    Button btnFind;
    ListView listDevices;

    private BluetoothAdapter mBluetooth = null;
    private Set<BluetoothDevice> pairedDevices;
    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mBluetooth = BluetoothAdapter.getDefaultAdapter();

        // Call the buttons
        btnFind     = (Button)findViewById(R.id.btnFind);
        listDevices = (ListView)findViewById(R.id.listDevices);

        if (mBluetooth == null)
        {
            // Show a message that the device has no bluetooth adapter
            Toast.makeText(getApplicationContext(), "Bluetooth adapter not detected.",
                    Toast.LENGTH_LONG).show();
            finish();
        }
        else if (!mBluetooth.isEnabled())
        {
            // Ask the user to turn the bluetooth on
            Intent btIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(btIntent, 1);
        }

        // Button to find devices
        btnFind.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                pairedDevicesList();
            }
        });
    }

    private void pairedDevicesList()
    {
        pairedDevices = mBluetooth.getBondedDevices();
        ArrayList list = new ArrayList();

        if (pairedDevices.size() > 0)
        {
            for (BluetoothDevice bt : pairedDevices)
            {
                // Get the device name and address
                list.add(bt.getName() + "\n" + bt.getAddress());
            }
        }

        else
        {
            Toast.makeText(getApplicationContext(), "Paired device not found.",
                    Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1,
                list);
        listDevices.setAdapter(adapter);
        listDevices.setOnItemClickListener(mListClickListener);
    }

    private AdapterView.OnItemClickListener mListClickListener = new AdapterView.OnItemClickListener()
    {
        public void onItemClick(AdapterView<?> av, View v, int arg2, long arg3)
        {
            // Get the device MAC address, the last 17 chars in the view
            String info    = ((TextView)v).getText().toString();
            String address = info.substring(info.length() - 17);

            // Make an intent to start next activity
            Intent i = new Intent(MainActivity.this, Controller.class);

            // Change the activity
            i.putExtra(EXTRA_ADDRESS, address);
            startActivity(i);
        }
    };
}
