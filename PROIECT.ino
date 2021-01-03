#include<OneWire.h>
#include<DallasTemperature.h>
#include<SoftwareSerial.h>
#include<NewPing.h>
#define SensorPin A2
#define Offset 0.00
unsigned long int avgValue;
#define ONE_WIRE_BUS 6
SoftwareSerial mySerial(7,8);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
int pingPin=22;
int sensorPin=A0;
int sensorValue=0;
int blue=5;
int red=7;
int green=6;
//int outputValue=0;
int analoginPin=A1;
//const int analogoutPin=9;
float phValue;
float temperatureC;
void setup(void)
{
  sensor.begin();
  Serial.begin(9600);
  pinMode(blue,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
}
void loop()
{
  sensor.requestTemperatures();
  Serial.println(sensor.getTempCByIndex(0));
  int reading=analogRead(sensorPin);
  float voltage=reading*5.0;
  voltage=voltage/1024.0;
  float temperatureC=(voltage-0.5)*100;
  PH();
  digitalWrite(blue,LOW);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  LEVEL();
  TURBIDITY();
  TEMPERATURA();
}
void PH()
{
  Serial.println(" ");
  digitalWrite(blue,LOW);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  //Serial.print("PH senzor");
  int buf[10];
  for(int i=0;i<10;i++)
  {
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)
   avgValue+=buf[i];
  float phValue=(float)avgValue*3.8/1030/6;
  phValue=3.3*phValue+Offset;
  Serial.println(" ");
  if(phValue>7.30)
  {
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
    Serial.print("PH: ");
    Serial.println(phValue);
    Serial.println("Apa alcalina!");
    delay(3000);
  }
   if(phValue >= 6.90 && phValue <= 7.19)
   {
    digitalWrite(blue, HIGH);
    digitalWrite(green,LOW);
    digitalWrite(red, LOW);
    Serial.print("PH: ");
    Serial.println(phValue);
    Serial.println("Apa neutra!");
    delay(3000);
   }
   if(phValue < 6.89)
   {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    Serial.print("PH: ");
    Serial.println(phValue);
    Serial.println("Apa acida!");
    delay(3000);
   }
  // delay(3000);
}
void LEVEL()
{

   sensorValue = analogRead(analoginPin);
  if(sensorValue<=100)
  {
    Serial.print("Gol");
   }
  else if(sensorValue>100 && sensorValue<=300)
  {
    Serial.print("Nivel scazut");
  }
  else if(sensorValue>300 && sensorValue<=330)
  {
    Serial.print("Nivel mediu");
  }
  else if(sensorValue>330)
  {
    Serial.print("Nivel inalt");
  }
  //delay(3000);
}
void TEMPERATURA()
{
  int reading=analogRead(sensorPin);
  float voltage=reading*5.0;
  voltage/=1024.0;
  float temperatureC=(voltage-0.5)*100;
  Serial.print(temperatureC); 
  Serial.print("grade C");
}
void TURBIDITY()
{
  Serial.println(" ");
  int turbidityV=analogRead(A3);
  float turbidity=turbidityV/100;
  if (turbidity>9)
  {
    Serial.print("Nivel turbiditate: ");
    Serial.print(turbidity);
    Serial.println(" NTU");
    Serial.println("Apa murdara");
    delay(3000);
  }
  if(turbidity>=6 &&turbidityV/100<=9)
  {
    Serial.print("Nivel turbiditate: ");
    Serial.print(turbidity);
    Serial.println(" NTU");
    Serial.println("Apa normala");
    delay(3000);
  }
  if(turbidity<6)
  {
    Serial.print("Nivel turbiditate: ");
    Serial.print(turbidity);
    Serial.println(" NTU");
    Serial.println("Apa curata");
    delay(3000);
  }
  delay(3000);
}
  
