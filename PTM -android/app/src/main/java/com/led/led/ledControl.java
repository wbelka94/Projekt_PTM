package com.led.led;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;
import java.io.IOException;
import java.util.UUID;


public class ledControl extends ActionBarActivity implements SensorEventListener {

    Button btnUP, btnDOWN, btnLEFT,btnRIGHT,btnMAN,btnSTOP, btnDis;
    SeekBar speedBar;
    TextView lumn,t1,t2,t3,t4;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    SensorManager sm;
    int ll,lp,ml,mp,progressSpeed,state=0;
    boolean test = false;

    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS);

        setContentView(R.layout.activity_led_control);

        btnUP = (Button)findViewById(R.id.up);
        btnDOWN = (Button)findViewById(R.id.down);
        btnLEFT = (Button)findViewById(R.id.left);
        btnRIGHT = (Button)findViewById(R.id.right);
        btnMAN = (Button)findViewById(R.id.man);
        btnDis = (Button)findViewById(R.id.button4);
        btnSTOP = (Button)findViewById(R.id.STOP);
        speedBar = (SeekBar)findViewById(R.id.seekBar);
        btnSTOP.setVisibility(View.INVISIBLE);

       // t1= (TextView)findViewById(R.id.textPion);
       // t2= (TextView)findViewById(R.id.textPoziom);
        t3 = (TextView)findViewById(R.id.textView3);

        sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        sm.registerListener(this, sm.getDefaultSensor(Sensor.TYPE_ORIENTATION), 0, null);


        new ConnectBT().execute();
        speedBar.setMax(40);

        btnRIGHT.setVisibility(View.INVISIBLE);
        btnLEFT.setVisibility(View.INVISIBLE);
        btnUP.setVisibility(View.INVISIBLE);
        btnSTOP.setVisibility(View.INVISIBLE);
        btnDOWN.setVisibility(View.INVISIBLE);
        speedBar.setVisibility(View.INVISIBLE);

        speedBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressSpeed = progress;
                if (state == 2)
                    ll = lp = progress;

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                if (state == 2) {
                    speedBar.setProgress(50);
                    speedBar.refreshDrawableState();
                }
            }
        });


        ll = lp = 50;
        btnUP.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction() & MotionEvent.ACTION_MASK) {
                    case MotionEvent.ACTION_DOWN:
                        if(state==1)
                            ll=lp=60+progressSpeed;
                        else if(state==2)
                            ll=lp=progressSpeed;
                        //wysylanieMAN(ll, lp);
                        break;
                    case MotionEvent.ACTION_UP:
                        if(state==1)
                            ll=lp=50;
                       // wysylanieMAN(ll, lp);
                        break;
                }
                return false;
            }
        });

        btnRIGHT.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction() & MotionEvent.ACTION_MASK) {
                    case MotionEvent.ACTION_DOWN:
                        ll = 65;
                        lp = 35;
                        //wysylanieMAN(ll, lp);
                        break;
                    case MotionEvent.ACTION_UP:
                        ll = lp = 50;
                        //wysylanieMAN(ll, lp);
                        break;
                }
                return false;
            }
        });

        btnLEFT.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction() & MotionEvent.ACTION_MASK) {
                    case MotionEvent.ACTION_DOWN:
                        ll = 35;
                        lp = 65;
                        //wysylanieMAN(ll, lp);
                        break;
                    case MotionEvent.ACTION_UP:
                        ll = lp = 50;
                       // wysylanieMAN(ll, lp);
                        break;
                }
                return false;
            }
        });
        btnDOWN.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                if(state==1) {
                    switch (event.getAction() & MotionEvent.ACTION_MASK) {
                        case MotionEvent.ACTION_DOWN:
                            ll = lp = 40 - progressSpeed;
                            //wysylanieMAN(ll, lp);
                            break;
                        case MotionEvent.ACTION_UP:
                            ll = lp = 50;
                            //wysylanieMAN(ll, lp);
                            break;
                    }
                }
                else if(state==2)
                {
                    switch (event.getAction() & MotionEvent.ACTION_MASK) {
                        case MotionEvent.ACTION_DOWN:
                            ml+=15;
                            mp-=15;
                            // wysylanieMAN(ll, lp);
                            break;
                        case MotionEvent.ACTION_UP:
                            ml-=15;
                            mp+=15;
                            break;}
                }
                return false;
            }
        });
        btnSTOP.setOnTouchListener(new View.OnTouchListener() {
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction() & MotionEvent.ACTION_MASK) {
                    case MotionEvent.ACTION_DOWN:
                        ml-=15;
                        mp+=15;
                       // wysylanieMAN(ll, lp);
                        break;
                    case MotionEvent.ACTION_UP:
                        ml+=15;
                        mp-=15;
                        break;
                }
                return false;
            }
        });


        btnMAN.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ll=lp=50;
                ml=mp=0;
                wysylanie(ll,lp);
                state++;
                if(state>2)
                    state=0;
                if(state==2) {
                    btnRIGHT.setVisibility(View.INVISIBLE);
                    btnLEFT.setVisibility(View.INVISIBLE);
                    btnUP.setVisibility(View.INVISIBLE);
                    btnSTOP.setVisibility(View.VISIBLE);
                    speedBar.setMax(100);
                    speedBar.setProgress(50);

                }
                if(state==1) {
                    btnRIGHT.setVisibility(View.VISIBLE);
                    btnLEFT.setVisibility(View.VISIBLE);
                    btnUP.setVisibility(View.VISIBLE);
                    btnSTOP.setVisibility(View.INVISIBLE);
                    btnDOWN.setVisibility(View.VISIBLE);
                    speedBar.setVisibility(View.VISIBLE);
                    speedBar.setMax(40);
                }
                if(state==0) {
                    btnRIGHT.setVisibility(View.INVISIBLE);
                    btnLEFT.setVisibility(View.INVISIBLE);
                    btnUP.setVisibility(View.INVISIBLE);
                    btnSTOP.setVisibility(View.INVISIBLE);
                    btnDOWN.setVisibility(View.INVISIBLE);
                    speedBar.setVisibility(View.INVISIBLE);
                }

            }
        });

        btnDis.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect();
            }
        });


    }
    private void wysylanieMAN(int a,int b)
    {
        if(ll>100)
            ll=100;
        else if(ll<0)
            ll=0;
        if(lp>100)
            lp=100;
        else if(lp<0)
            lp=0;
        wysylanie(ll,lp);
    }

    private void Disconnect()
    {
        wysylanie(50,50);
        isBtConnected = false;

        if (btSocket!=null)
        {
            try
            {
                msg("Closed");
                btSocket.close();

            }
            catch (Exception e)
            { msg("Error");}
        }
        finish();
    }

    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();


        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    

    public void onSensorChanged(SensorEvent event) {
        if(test)
            return;
        test=true;
        if (state != 0) {
                t3.setText("STEROWANIE MANUALNE "+state+"\nlewy silnik " + (ll+ml) + "\n" + "prawy silnik " + (lp+mp));
        }
        else {

            float poziom = Math.round(((event.values[2]) + 180 / 3.6) - 50) / 4;
            float pion = Math.round((event.values[1]) + 180 / 3.6) / 2 + 25;

            //t3.setText("Pion: "+pion+"\n" + "Poziom: "+poziom+"\n");


            if (pion < 0) {
                pion = 0;
            }
            if (pion > 100) {
                pion = 100;
            }
            

            lp = ll = (int) pion;
            if (poziom > 0) {
                if (pion > 50) {
                    if (pion > 55)
                        lp = (int) (lp + poziom * 2);
                    else
                        lp = (int) (lp + poziom);
                }
                if (pion < 50) {
                    if (pion < 45)
                        lp = (int) (lp - poziom * 2);
                    else
                        lp = (int) (lp - poziom);
                }
            }

            if (poziom < 0) {
                if (pion > 50) {
                    if (pion > 55)
                        ll = (int) (ll - poziom * 2);
                    else
                        ll = (int) (ll - poziom);
                }
                if (pion < 50) {
                    if (pion < 45)
                        ll = (int) (ll + poziom * 2);
                    else
                        ll = (int) (ll + poziom);
                }
            }
            if (ll < 0) {
                ll = 0;
            }
            if (ll > 100) {
                ll = 100;
            }
            t3.setText("STEROWANIE ZYROSKOPEM\nlewy silnik " + ll + "\n" + "prawy silnik " + lp);
        }
        Handler handler = new Handler();
        if(isBtConnected) {
            final int finalLl = ll+ml;
            final int finalLp = lp+mp;
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    wysylanie(finalLl, finalLp);
                }
            }, 10);

        }
        test=false;
    }

    public void wysylanie(int l, int p)  {

        char g1 =  ((char)(l));
        char g2 =  ((char)(p));
        char s = ((char)(p+l));

        if (btSocket!=null && isBtConnected)
        {
            try
            {
                btSocket.getOutputStream().write(("sl" + g1 + "p" + g2 + "f"+s).getBytes());
            }
            catch (IOException e)
            {
                Disconnect();
               // msg("Error");
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);
                 btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
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
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
