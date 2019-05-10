#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 receive (2,3);     //create object called receive
byte address [5] = "00001"; //create an array with 5 elements, of 1 byte elements;

struct package
  {
    float temperature = 0;
    float humidity = 0;
    float rainfall = 0;
  };

  typedef struct package Package;
  Package data;

void setup() {
  Serial.begin(9600);
  Serial.print(“Starting Receiver \n”);
  receive.begin();
  receive.openReadingPipe(0,address);      //open reading pipe 0 at address 00001 
  receive.setPALevel(RF24_PA_MIN);         //Set RF output to minimum
  receive.setDataRate(RF24_250KBPS);       //set datarate to 250kbps
  receive.setChannel(100);                 //set frequency to channel 100 
  receive.startListening();                

  }

void loop() {

  if (receive.available())                //check when received data available
  {
    
    receive.read(&data, sizeof(data));
    Serial.print(data.temperature);                //print data to serial monitor
    Serial.print(” C  “);
    Serial.print(data.humidity);                   //print data to serial monitor
    Serial.print(” % \n “);
  }

}