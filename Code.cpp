#include "DHT.h" //It is necessary for us to include this library when we use DHT11/DHT22 sensor
#define DHTPIN 3 // Defining the data output pin to Arduino
#define DHTTYPE DHT11 // Specify the sensor type(DHT11 or DHT22)
#define FAN_THRESHOLD 10 // Set the temperature threshold for turning on the fan
#define fanPin 9 // Set the pin for the fan

DHT dht(DHTPIN, DHTTYPE); //Declaration for variables below...
bool fanOn = false; // Set the initial state of the fan to off

void setup() {
  Serial.begin(9600); //To engage serial monitor
  dht.begin(); //To initialise DHT sensor

  pinMode(fanPin, OUTPUT); // Initialize the fan pin as an output
}

void loop() {
  delay(1000);
  //Here h= Humidity; tC= Temperature in degree C; tF= Temperature in degree F
  float h= dht.readHumidity();
  float tC= dht.readTemperature();
  float tF= dht.readTemperature(true);

  if (isnan(h) || isnan(tC) || isnan(tF)){
    Serial.println("Failed to read the DHT sensor. Check connections");
  }
  else{
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%");
    Serial.print("  ||  ");
    Serial.print("Temperature: ");
    Serial.print(tC);
    Serial.print("C  ");
    Serial.print(tF);
    Serial.println("F"); 

    if (tC > FAN_THRESHOLD && !fanOn) {
      digitalWrite(fanPin, HIGH); // Turn on the fan
      fanOn = true; // Update the state of the fan
    } else if (tC <= FAN_THRESHOLD && fanOn) {
      digitalWrite(fanPin, LOW); // Turn off the fan
      fanOn = false; // Update the state of the fan
    }
  }
}    
