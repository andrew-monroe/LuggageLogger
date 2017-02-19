// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL3115A2.h>
#include <Adafruit_L3GD20_U.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

float pascals = 0;

void setup(void)
{
  #ifndef ESP8266
    while (!Serial);     //will pause Leonardo until serial console opens
  #endif
  
    Serial.begin(9600);
    
    
    if (! lis.begin(0x18)) 
    { 
      Serial.println("Couldnt start");
      while (1);
    }
    
    lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
    gyro.enableAutoRange(true);
    
    // Initialise the sensor 
    if(!gyro.begin())
    {
      while(1);
    }
    
  }
  
  void loop() {
  
      /* Get a new sensor event */ 
    sensors_event_t event2; 
    gyro.getEvent(&event2);
   
    
    
    lis.read();      // get X Y and Z data at once
  
    sensors_event_t event1; 
    lis.getEvent(&event1);
    
    
    
    if (! baro.begin()) 
    {
      return;
    }

    float newPascals = baro.getPressure();
    
    
     if(((newPascals >= pascals * 1.1 )|| (newPascals <= pascals * .9)) && (pascals != 0))
     {
       //Serial.print(pascals);
       //Serial.println();
     }
     else
     {
      Serial.print(sqrt((event2.gyro.x)*(event2.gyro.x)+(event2.gyro.y)*(event2.gyro.y)+(event2.gyro.z)*(event2.gyro.z)));
      Serial.print(" ");
      Serial.print(sqrt((event1.acceleration.x)*(event1.acceleration.x)+(event1.acceleration.y)*(event1.acceleration.y)+(event1.acceleration.z)*(event1.acceleration.z)));
      Serial.print(" ");
      Serial.print(newPascals);
      Serial.println();
      pascals = newPascals;
     }
     
  
    
    
    delay(10);
}





