#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <SPI.h>
#include <Adafruit_MAX31855.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_A 5
#define ONE_WIRE_B 6
#define DO   2
#define CS   3
#define CLK  4
#define ENCODER 9
#define TARGET_TEMP 10
#define HOT_FLOW 11
#define COLD_FLOW 12
#define SERVO_A 7
#define SERVO_B 8

#define TARGET_TEMP_A 45
#define TARGET_TEMP_B 45

Adafruit_MAX31855 thermocouple(CLK, CS, DO);

Servo servoA;
Servo servoB;
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWireA(ONE_WIRE_A);
OneWire oneWireB(ONE_WIRE_B);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensorsA(&oneWireA);
DallasTemperature sensorsB(&oneWireB);

void setup(void)
{
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensorsA.begin();
  sensorsB.begin();
  
  servoA.attach(SERVO_A);
  servoB.attach(SERVO_B);
}
 
void loop(void)
{
  double targetTemp = digitalRead(TARGET_TEMP) ? TARGET_TEMP_A : TARGET_TEMP_B;
  boolean encoder = digitalRead(ENCODER);
  while (!encoder)
  {
    encoder = digitalRead(ENCODER);
    targetTemp = digitalRead(TARGET_TEMP) ? TARGET_TEMP_A : TARGET_TEMP_B;
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    sensorsA.requestTemperatures(); // Send the command to get temperatures
    sensorsB.requestTemperatures(); // Send the command to get temperatures
    double inTempA = sensorsA.getTempCByIndex(0);
    double inTempB = sensorsB.getTempCByIndex(0);
    
    double c = thermocouple.readCelsius();
     if (!isnan(c)) {
       double outTemp = c;
     }
  }
}

