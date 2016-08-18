# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# TSL45315
# This code is designed to work with the TSL45315_IS2C I2C Mini Module available from ControlEverything.com.
# https:#www.controleverything.com/content/Light?sku=TSL45315_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# TSL45315 address, 0x29(41)
# Select Control register, 0x00(0), with Command register, 0x80(128)
#		0x03(03)	Normal operation
i2c.writeByte(0x29, 0x00 | 0x80, 0x03)
# TSL45315 address, 0x29(41)
# Select Configuration register, 0x01(1), with Command register, 0x80(128)
#		0x00(00)	Multiplier 1x, Tint : 400ms
i2c.writeByte(0x29, 0x01 | 0x80, 0x00)

time.sleep(0.5)

# TSL45315 address, 0x29(41)
# Read data back from 0x04(4), with Command register, 0x80(128)
# 2 bytes, LSB first
data = i2c.readBytes(0x29, 0x04 | 0x80, 2)

# Convert the data to lux
luminance = data[1] * 256 + data[0]

# Output data to screen
print "Ambient Light Luminance : %d lux" %luminance
