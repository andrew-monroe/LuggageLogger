// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL3115A2.h>
#include <Adafruit_L3GD20_U.h>


// Used for software SPI
#define LIS3DH_CLK 3
//#define LIS3DH_MISO 12
#define LIS3DH_MOSI 2
// Used for hardware & software SPI
//#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  Serial.begin(9600);
  Serial.println("Adafruit_MPL3115A2 test!");

  Serial.begin(9600);
  Serial.println("Gyroscope Test"); Serial.println("");
  
  /* Enable auto-ranging */
  gyro.enableAutoRange(true);
  
  /* Initialise the sensor */
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop() {
  lis.read();      // get X Y and Z data at once

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event1; 
  lis.getEvent(&event1);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X Acceleration:\t");
  Serial.print(event1.acceleration.x);
  Serial.println("\tm/s^2");
  Serial.print("Y Acceleration:\t");
  Serial.print(event1.acceleration.y);
  Serial.println("\tm/s^2");
  Serial.print("Z Acceleration:\t");
  Serial.print(event1.acceleration.z);
  Serial.println("\tm/s^2");

  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  
  float pascals = baro.getPressure();
  // Our weather page presents pressure in Inches (Hg)
  // Use http://www.onlineconversion.com/pressure.htm for other units
  Serial.print("Pressure:\t");
  Serial.print(pascals);
  Serial.println("\tPascals");

  float altm = baro.getAltitude();
  Serial.print("Altitude:\t");
  Serial.print(altm);
  Serial.println("\tmeters");

  float tempC = baro.getTemperature();
  Serial.print("Temperature:\t");
  Serial.print(tempC);
  Serial.println("\t*C");

  /* Get a new sensor event */ 
  sensors_event_t event2; 
  gyro.getEvent(&event2);
 
  /* Display the results (speed is measured in rad/s) */
  Serial.print("X Rotation:\t"); Serial.print(event2.gyro.x); Serial.print("\trad/s\n");
  Serial.print("Y Rotation:\t"); Serial.print(event2.gyro.y); Serial.print("\trad/s\n");
  Serial.print("Z Rotation:\t"); Serial.print(event2.gyro.z); Serial.print("\trad/s\n");

  Serial.println();
  
  delay(4000);
}


/* Assign a unique ID to this sensor at the same time */


void displaySensorDetails(void)
{
  sensor_t sensor;
  gyro.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" rad/s");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" rad/s");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" rad/s");  
  Serial.println("------------------------------------");
  Serial.println("");
  
  delay(500);
}



