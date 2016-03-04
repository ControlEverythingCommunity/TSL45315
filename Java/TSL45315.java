import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class TSL45315
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, TSL45315 I2C address is 0x29(41)
		I2CDevice device = bus.getDevice(0x29);
		
		// Send start command
		device.write((byte)0x80);
		// Send measurement command
		device.write((byte)0x03);
		
		Thread.sleep(800);
		// Read 2 bytes of data from address 0x04(4), LSB first
		byte[] data = new byte[2];
		device.read(0x80 | 0x04, data, 0, 2);
		
		// Convert the data to lux
		int luminance = ((data[1] & 0xFF) * 256) + (data[0] & 0xFF);
		
		// Output data to screen
		System.out.printf("Total luminance is:  %d lux %n", luminance);
	}	
}
