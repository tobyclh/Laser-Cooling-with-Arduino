/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
  int Red = 5;
  int Green = 3;
  int Blue = 6;
  float Upperlimit = 40;//MAX for LM35 (in this app mode)= 150C
  float Lowerlimit = 20;//MIN for LM35 (in this app mode) = 2C
  float range = (Upperlimit - Lowerlimit);
  float grouprange = range/5; 
    /*VOUT = 10 mv/°F × T
where
• VOUT is the LM35 output voltage
• T is the temperature in °C
*/
void setup() {
  analogReference(INTERNAL);
  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = map(sensorValue,0,1023,0,1100);//convert value to voltage in mV
  float temp = voltage /10;
  temp = max(temp,Lowerlimit);
  temp = min(temp,Upperlimit);// cut off value that fall outside the range
  Serial.print(temp);
  if (temp >= Lowerlimit + 4*grouprange)
    {int Y = -(temp- Lowerlimit- 4*grouprange)/grouprange*255;  //remap temperature to 0,255 scale within the small group, remap function isnt used here for the sake that it cannot handle float
    analogWrite(Red,255);
    analogWrite(Green,Y);
    analogWrite(Blue,0);
    Serial.print("\t");
    Serial.print("4");
    Serial.print("\t");
    Serial.println(Y);}// to print out temperature value through serial port
        else if(temp >= Lowerlimit + 3*grouprange)
    {int Y = -(temp-Lowerlimit- 3*grouprange)/grouprange*255;
    analogWrite(Red,255-Y);
    analogWrite(Green,255);
    analogWrite(Blue,0);
    Serial.print("\t");
    Serial.print("3");
    Serial.print("\t");
    Serial.println(Y);}
        else if(temp >= Lowerlimit + 2*grouprange)
    {int Y = -(temp- Lowerlimit- 2*grouprange)/grouprange*255;
    analogWrite(Red,0);
    analogWrite(Green,255); 
    analogWrite(Blue,Y);
    Serial.print("\t");
    Serial.print("2");
    Serial.print("\t");
    Serial.println(Y);}
        else if(temp >= Lowerlimit + 1*grouprange)
    {int Y = -(temp- Lowerlimit- grouprange)/grouprange*255;;
    analogWrite(Red,0);
    analogWrite(Green,255-Y);
    analogWrite(Blue,Y);
    Serial.print("\t");
    Serial.print(temp);
    Serial.print("\t");
    Serial.print("1");
    Serial.print("\t");
    Serial.println(Y);}
        else
   {int Y = -(temp-Lowerlimit)/grouprange*255;
    analogWrite(Red,Y);
    analogWrite(Green,0);
    analogWrite(Blue,255);
    Serial.print("\t");
    Serial.print("0");
    Serial.print("\t");
    Serial.println(Y);}
    // the temp is divided into 5 groups,algorithm here https://www.particleincell.com/2014/colormap/
  delay(100);
  // print out the value you read:

}
