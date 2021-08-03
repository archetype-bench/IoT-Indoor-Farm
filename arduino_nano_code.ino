/*
 * Project BOLT IOT FARM
 * Dated 22 April 2021
 * 
 * = Source code for INDOOR FARM MONITORING SYSTEM, using DHT11, soil moisture sensor and LDR
 *    to monitor and upload values on Bolt IoT Cloud.
 *    
 * Edits: #1 Added DHT11   
 *        #2 Added LDR
 *        #3 Added Relays
 *        #4 Added Moisture Sensor
 *        #5 Added Serial Connection to Bolt
 *        
 * 
 */


#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial mySerial(8,9);//(Rx of Bolt, Tx of Bolt)

//Constants
#define DHTPIN 2     // DHT connected to Pin 2
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


int ldr = 3;    //LDR connected to pin 3
int fan = 4;    // Fan relay connected to pin 4
int light = 5;  // Light relay connected to pin 5
int pump = 6;   // pump relay connected to pin 6


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  pinMode(DHTPIN,INPUT);
  pinMode(ldr,INPUT);
  pinMode(fan,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(pump,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  String data;
  int ldr_out;
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();
  //temp = temp * 1.8 + 32;


  
  if(digitalRead(ldr)==LOW){
    ldr_out=10;
    digitalWrite(light,HIGH);
  }
  else{
    ldr_out=0;  
    digitalWrite(light,LOW);  
  }

  if(hum>80){
    digitalWrite(fan,LOW);
  }
  else{
    digitalWrite(fan,HIGH);
  }

  int moist = analogRead(0);
  if(moist>500)
  {
    digitalWrite(pump,LOW);
  }
  else
  {
    digitalWrite(pump,HIGH);
  }


  
  data="Hum: "+ String(hum)+"%  Temp: "+String(temp)+" C  Ambience: "+ldr_out+" Moisture:"+String(moist);
  Serial.println(data);
  delay(1000);

  if (mySerial.available() > 0) {
    delay(50);
    String readData = "";
    Serial.print("Command from Bolt: ");
    while (mySerial.available() > 0 ) {
      readData = readData + (char)mySerial.read();
    }
    Serial.println(readData);
    if (readData.indexOf("RD") != -1) {
      String upload = String(temp)+","+String(hum)+","+ldr_out+","+String(moist);
      mySerial.print(upload);
      Serial.print("Data sent to Bolt: ");
      Serial.println(data);
    }
  }
}
