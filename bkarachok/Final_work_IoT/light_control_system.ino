#include <Wire.h> 
#include <math.h>
#include <WString.h> 

int BH1750_Device = 0x23; // I2C address for light sensor
unsigned int Lux;
int lamp = 13;
int sm_mode = 0;
char inSerial[15];

void setup() //configuration settings
{
  Wire.begin();
  Serial.begin(9600);
  Configure_BH1750();
  pinMode(lamp, OUTPUT);
  pinMode(4, INPUT);    
  delay(300);
  
}

void loop() //main loop
{
  int i=0;
  Lux = BH1750_Read(); //get illumination level value
  Serial.print(Lux,DEC); //print to serial port
  Serial.println();  
  delay(300); 
  int m=0;
  if(Serial.available() > 0) {
    while (Serial.available() > 0) {
      inSerial[i]=Serial.read(); //read data from serial port
      i++;
    }
    Serial.println(); 
    inSerial[i] ='\0';
    Check_Protocol(inSerial); 
  }
  if (sm_mode == 1) { // smart mode definition
    if (Lux<20) digitalWrite(lamp, HIGH); // turn on lamp
    else {
      digitalWrite(lamp, LOW); // turn off lamp
    }
  }
  }

  void allpinslow()
  {
    digitalWrite(lamp, HIGH);
    digitalWrite(lamp, LOW);
  }

  void Check_Protocol(char inStr[]) { //check data from serial port
    int i=0;
    int m=0;
    Serial.println(inStr);

  if(!strcmp(inStr, "off")) { // command turn off lamp
    allpinslow();
    sm_mode = 0; // disable smart mode
    digitalWrite(lamp, LOW); // turn off lamp
    for(m=0;m<11;m++){
      inStr[m]=0;}
      i=0;}

    if(!strcmp(inStr, "on")) { //command turn on lamp
    allpinslow();
    sm_mode = 0; //disable smart mode
    digitalWrite(lamp, HIGH); // turn on lamp
    for(m=0;m<11;m++){
      inStr[m]=0;}
      i=0;}

    if(!strcmp(inStr, "sm")) { // command for smart mode 
    allpinslow();
    sm_mode = 1; //enable smart mode
    for(m=0;m<11;m++){
      inStr[m]=0;
      }
      i=0;
      }
      
    else {
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;
      
    }
  }

unsigned int BH1750_Read() // reading illumination level value in LUX
{
  unsigned int i=0;
  Wire.beginTransmission(BH1750_Device);
  Wire.requestFrom(BH1750_Device, 2);
  while(Wire.available()) 
  {
    i <<=8;
    i|= Wire.receive();  
  }
  Wire.endTransmission();  
  return i/1.2;  // Convert to Lux
}

void Configure_BH1750() // configuration settings for light sensor
{
  Wire.beginTransmission(BH1750_Device);
  Wire.send(0x10);      // Set resolution to 1 Lux
  Wire.endTransmission();
}

