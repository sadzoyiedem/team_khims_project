#include <DHT.h>

#define DHTTYPE DHT22

const int dht_pin = 25;
const int trig_pin = 5;
const int echo_pin = 18;
const int ldr_pin = 32;

//constant variable to hold the speed of sound in cm per microsecond
const float speed_of_sound = 0.0343;

// Declaring dht object
DHT dht(dht_pin, DHTTYPE);


// Variable declaration to hold sensor values. 
long duration;
float distance_cm;
float temperature, humidity;
int ldr_value = 0;


void setup() {
  // setup up the display on the serial monitor
  Serial.begin(115200);

  // function call of the begin() method to initialize the DHT
  dht.begin();

  // pinMode setup the vaious GPIO pin allocations. 
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(ldr_pin, INPUT);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2); 
  // 2. TRIGGER THE SENSOR (The sequence of High, Low, sets the HC-SR04 to send a blast of ultrasonic waves)
  // A 10-microsecond HIGH pulse is the standard required to trigger the HC-SR04
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  // sending low signal
  digitalWrite(trig_pin, LOW);

  // 3. LISTEN FOR THE ECHO
  // pulseIn() waits for the echo pin to go HIGH, times how long it stays HIGH, 
  // and returns that time in microseconds.
  duration = pulseIn(echo_pin, HIGH);

  // 4. CALCULATE DISTANCE
  // We divide by 2 because the sound traveled OUT and BACK (twice the distance).
  distance_cm = (duration * speed_of_sound) / 2;

  //DHTpin- getting humdity and temp values
  temperature = dht.readTemperature();
  humidity =  dht.readHumidity();
  

  // Error checking. This is to check if ESP32 is getting reading from the microcontroller
   if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Error reading from DHT sensor");
    return;
  }

  // Getting analog reading from the LDR sensor
  ldr_value = analogRead(ldr_pin);

  // 5. PRINT THE RESULTS
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println("%"); 
  Serial.print("Light level: "); 
  Serial.println(ldr_value);
  
  if(ldr_value < 300 ) 
    Serial.println("Its dark");
  else 
    Serial.println("Its bright");
  Serial.println("------------------------------------");

  // A delay of 2 seconds before we take the next set of readings from the various sensors.
  delay(2000); 
}