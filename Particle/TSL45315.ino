// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TSL45315
// This code is designed to work with the TSl45315_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=TSL45315_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// TSL45315 I2C address is 0x29(41)
#define Addr 0x29

int luminance;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "TSL45315");
  Particle.variable("luminance", luminance);
  
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x80);

  // Normal operation
  Wire.write(0x03);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x81);

  // Multiplier 1x, Tint : 400ms
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x84);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  // Read 2 bytes of data
  // luminance lsb, luminance msb
  if(Wire.available() == 2)
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
      delay(300);
    }
  // Convert the data
  luminance = (data[1] * 256) + data[0];
    
  // Output data to dashboard
  Particle.publish("Ambient Light luminance :", String(luminance));
    
  delay(1000);
}
