#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2  // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const int pulsePin = A0;   // Pulse sensor analog pin
const int buzzerPin = 7;   // Piezo buzzer pin

int thresholdHumidity = 70;  // Set the humidity threshold for the alarm

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_I2C_ADDRESS, OLED_RESET);

  // Initialize DHT sensor
  dht.begin();

  pinMode(buzzerPin, OUTPUT);

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read heart rate from pulse sensor
  int heartRate = analogRead(pulsePin);

  // Read humidity from DHT11 sensor
  float humidity = dht.readHumidity();

  // Display heart rate on OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Heart Rate: ");
  display.print(heartRate);
  display.display();

  // Check humidity level
  if (humidity < thresholdHumidity) {
    // Trigger the alarm
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // Buzzer on for 1 second
    digitalWrite(buzzerPin, LOW);
    delay(2000); // Wait for 2 seconds before checking again
  }

  // Other processing or actions can be added as needed

  delay(1000); // Delay for stability
}
