/*
  AnalogReadSerial adapted for the AD8307 logarithmic sensor connected to A0
*/
// include the ITEAD Nextion library header file ONLY if touch command data will flow TO Arduino
// #include <nextion.h>

int sensorValue = 0;
float volts = 0.0;
float raw8307Voltage = 0.0;
String strValue = "";

// the setup routine runs once when you press reset:
void setup() {
  // initialize HW serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever
void loop() {
  // read the voltage input on analog pin 0:
  sensorValue = analogRead(A0);
  // Convert the digital sensor value to a voltage       
  volts = (sensorValue/1023.0) * 5.0;

  //
  // The following code blocks create a serial stream that the Nextion Display firmware will understand 
  // and interpret as commands. The conversions to percentage (%) and dBm units is made on the fly when loading the serial
  // data buffer with Serial.print(...).
  //
  
  // Display bar value
  Serial.print("j0.val=");
  Serial.print(int(volts * 37.0)-5); // Scale the bar
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  // Scale the raw voltage into A0
  raw8307Voltage = (volts * 39.0)-85.0; // Scale the dBm range
  
  // Serial.print("raw: " + String(raw8307Voltage) + "\n"); // Debug line

  //
  // Calibration table for 50 MHz, -80 to +17 dBm
  //
  if (raw8307Voltage > -80.0 && raw8307Voltage < -54.01){// -80 to -58 dBm
    raw8307Voltage = raw8307Voltage * 1.054;
  }
  if (raw8307Voltage > -54.00 && raw8307Voltage < -44.01){// -57 to -49 dBm
    raw8307Voltage = raw8307Voltage * 1.083;
  }
  if (raw8307Voltage > -44.0 && raw8307Voltage < -35.01){// -48 to -40 dBm
    raw8307Voltage = raw8307Voltage * 1.12;
  }
  if (raw8307Voltage > -35.0 && raw8307Voltage < -29.51){// -39 to -35 dBm
    raw8307Voltage = raw8307Voltage * 1.155;
  }
  if (raw8307Voltage > -29.5 && raw8307Voltage < -25.51){// -35 to -32 dBm
    raw8307Voltage = raw8307Voltage * 1.21;
  }
  if (raw8307Voltage > -25.5 && raw8307Voltage < -22.51){// -31 to -29 dBm
    raw8307Voltage = raw8307Voltage * 1.24;
  }
  if (raw8307Voltage > -22.5 && raw8307Voltage < -20.01){// -28 to -27 dBm
    raw8307Voltage = raw8307Voltage * 1.27;
  }
  if (raw8307Voltage > -20.0 && raw8307Voltage < -15.61){// -26 to - 22 dBm
    raw8307Voltage = raw8307Voltage * 1.355;
  }
  if (raw8307Voltage > -15.6 && raw8307Voltage < -13.61){// -26 to - 22 dBm
    raw8307Voltage = raw8307Voltage * 1.47;
  }
  if (raw8307Voltage > -13.6 && raw8307Voltage < -11.01){// -21 to -17 dBm
    raw8307Voltage = raw8307Voltage * 1.62;
  }
  if (raw8307Voltage > -11.0 && raw8307Voltage < -7.51){ // -16 to -14 dBm 
    raw8307Voltage = (raw8307Voltage * 1.1) - 6.8;
  }
  if (raw8307Voltage > -7.5 && raw8307Voltage < -3.1){ // -13 to -11 dBm
    raw8307Voltage = (raw8307Voltage * 1.1) - 7.0;
  }
  if (raw8307Voltage > -3.0 && raw8307Voltage < -1.1){ // -11 to -10 dBm
    raw8307Voltage = (raw8307Voltage * 1.1) - 8.0;
  }
  if (raw8307Voltage > -1.0 && raw8307Voltage < 4.99){ // -9 to -4 dBm 
    raw8307Voltage = (raw8307Voltage * 1.1) - 9.0;
  }
  if (raw8307Voltage > 5.0 && raw8307Voltage < 7.99){ // -4 to -1 dBm 
    raw8307Voltage = (raw8307Voltage * 1.1) - 10.0;
  }
  if (raw8307Voltage > 8.0 && raw8307Voltage < 12.99){ // 0 to +3 dBm
    raw8307Voltage = raw8307Voltage - 9.0;
  }
  if (raw8307Voltage > 13.00 && raw8307Voltage < 27.00){ // +4 to +17 dBm 
    raw8307Voltage = raw8307Voltage - 9.5;
  }
  
  //Serial.print("new: " + String(raw8307Voltage) + "\n"); // Debug line
  
  // Display dBm value
  strValue = String(raw8307Voltage);
  Serial.print("t1.txt=");
  Serial.print("\"" + strValue + "\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  // Delay in milliseconds to keep the update rate reasonable and not overrun the serial data buffer
  delay(100);
}
