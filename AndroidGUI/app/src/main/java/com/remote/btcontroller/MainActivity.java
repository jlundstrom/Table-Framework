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

        btnFind = (Button) findViewById(R.id.btnFind);
        listDevices = (ListView) findViewById(R.id.listDevices);
        mBluetooth = BluetoothAdapter.getDefaultAdapter();

        if (mBluetooth == null)
        {
            Toast.makeText(getApplicationContext(), "Bluetooth Adapter Not Available",
                    Toast.LENGTH_LONG).show();
            finish();
        }
        else if (!mBluetooth.isEnabled())
        {
            Intent btIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(btIntent, 1);
        }

        btnFind.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                pairedDevicesList();
            }
        });
    }

    private void pairedDevicesList()
    {
        pairedDevices = mBluetooth.getBondedDevices();
        ArrayList list = new ArrayList();

        if (pairedDevices.size()>0)
        {
            for(BluetoothDevice bt : pairedDevices)
            {
                list.add(bt.getName() + "\n" + bt.getAddress());
            }
        }

        else
        {
            Toast.makeText(getApplicationContext(), "No Paired Bluetooth Devices Found",
                    Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter adapter = new ArrayAdapter(this,android.R.layout.simple_list_item_1, list);
        listDevices.setAdapter(adapter);
        listDevices.setOnItemClickListener(mListClickListener);
    }

    private AdapterView.OnItemClickListener mListClickListener = new AdapterView.OnItemClickListener()
    {
        public void onItemClick (AdapterView<?> av, View v, int arg2, long arg3)
        {

            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);

            Intent i = new Intent(MainActivity.this, Controller.class);

            i.putExtra(EXTRA_ADDRESS, address);
            startActivity(i);
        }
    };
}