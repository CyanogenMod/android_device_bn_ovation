/*
 * Simple and ugly USB Host switcher for twl6030-based devices that
 * have the ID forcing patch in the kernel.
 *
 * Original author: Oleg Drokin <green@linuxhacker.ru> (C) 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
package com.green.usbhostswitcher;

import android.view.Menu;
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.view.View;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;


public class USBSwitcherActivity extends Activity {
	private ToggleButton usbSwitch;
	private TextView usbState;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_usbswitcher);
        
        usbSwitch = (ToggleButton) findViewById(R.id.usbSwitch);
        usbState = (TextView) findViewById(R.id.usbState);
        
        usbSwitch.setChecked(isHostModeEnabled());
        refreshUsbStatusClick(null);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.usbswitcher, menu);
        return true;
    }
    
    public void usbSwitchClick(View view) {
        String mode;

        if (usbSwitch.isChecked()) {
                mode = "enable";
        } else {
                mode = "disable";
        }
/*
// This code is disabled for nowto avoid messing with root/su stuff.
        Process p;
                try {
                        p = Runtime.getRuntime().exec("/system/xbin/su");

                        DataOutputStream dos = new DataOutputStream(p.getOutputStream());

                        dos.writeBytes("echo " + mode + "> /sys/devices/platform/omap/omap_i2c.1/i2c-1/1-0048/twl6030_usb/usb_id\n");
                        dos.writeBytes("exit");
                dos.flush();
                dos.close();

                if (p.waitFor() != 0) {
                    usbState.setText("Error updating host mode - exec");
            } else {
                    refreshUsbStatusClick(view);
            }
            } catch (IOException e) {
                    usbState.setText("Error updating host mode - write");
            } catch (InterruptedException e) {
                    usbState.setText("Error updating host mode - interrupt");
            }
            try {
                    Thread.sleep(100);
            } catch (InterruptedException e) {
            }
*/
        try {
            OutputStream outstream = new FileOutputStream("/sys/devices/platform/omap/omap_i2c.1/i2c-1/1-0048/twl6030_usb/usb_id");

            OutputStreamWriter outputwriter = new OutputStreamWriter(outstream);

            outputwriter.write(mode + "\n");
            outputwriter.flush();
            outputwriter.close();

            outstream.close();
            refreshUsbStatusClick(view);

        } catch (java.io.FileNotFoundException e) {
        	usbState.setText("USB ID control file not found");
        } catch (java.io.IOException e) {
        	usbState.setText("Error writing to USB ID control file");
        }

    
    usbSwitch.setChecked(isHostModeEnabled());
}

    
    private String readUsbIDStatus() {
        try {
                InputStream instream = new FileInputStream("/sys/devices/platform/omap/omap_i2c.1/i2c-1/1-0048/twl6030_usb/usb_id");

                InputStreamReader inputreader = new InputStreamReader(instream);
                BufferedReader buffreader = new BufferedReader(inputreader);
                String line;

                line = buffreader.readLine();
                instream.close();

                return line;

        } catch (java.io.FileNotFoundException e) {
                return null;
        } catch (java.io.IOException e) {
                return null;
        }
    }

    private boolean isHostModeEnabled() {

        String line = readUsbIDStatus();

        if (line == null || line.isEmpty())
                return false;

        if (line.startsWith("enable")) {
                return true;
        } else {
                return false;
        }
    }

    public void refreshUsbStatusClick(View view) {
        String line;

        line = readUsbIDStatus();

        if (line == null || line.isEmpty())
                line = "Error reading status";
        usbState.setText(line);
    }

}
