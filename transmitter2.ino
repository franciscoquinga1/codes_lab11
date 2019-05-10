#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <DHT.h>

#define DHTPIN 5                // do not connect to pin 0 or pin 1
#define DHTTYPE DHT11           // Define DHT11 module
DHT dht(DHTPIN, DHTTYPE);       //create DHT object called dht

float temperature_old = 0;
float humidity_old = 0;

RF24 transmit (2,3);            //create RF24 object called transmit

byte address [5] = "00001";                     //set address to 00001

struct package
  {
    float temperature = 0;
    float humidity = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  dht.begin();
  transmit.begin();
  transmit.openWritingPipe(address);    //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MIN);             //set RF power output to minimum
  transmit.setDataRate(RF24_250KBPS);           //set data rate to 250kbps
  transmit.setChannel(100);             //set frequency to channel 100
  transmit.stopListening();

  }


void loop() {
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();
  
   if (data.temperature != temperature_old)
        {
          transmit.write(&data,sizeof(data));         //transmit the data
        }
        else if (data.humidity != humidity_old)
        {
          
          transmit.write(&data,sizeof(data));         //transmit the data
        }
  
  temperature_old = data.temperature;         //update temperature_old to new reading
  humidity_old = data.humidity;               //update humidity_old to new reading
  delay(300);                
  
}