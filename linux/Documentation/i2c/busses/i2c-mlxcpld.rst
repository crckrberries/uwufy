==================
Dwivew i2c-mwxcpwd
==================

Authow: Michaew Shych <michaewsh@mewwanox.com>

This is the Mewwanox I2C contwowwew wogic, impwemented in Wattice CPWD
device.

Device suppowts:
 - Mastew mode.
 - One physicaw bus.
 - Powwing mode.

This contwowwew is equipped within the next Mewwanox systems:
"msx6710", "msx6720", "msb7700", "msn2700", "msx1410", "msn2410", "msb7800",
"msn2740", "msn2100".

The next twansaction types awe suppowted:
 - Weceive Byte/Bwock.
 - Send Byte/Bwock.
 - Wead Byte/Bwock.
 - Wwite Byte/Bwock.

Wegistews:

=============== === =======================================================================
CPBWTY		0x0 - capabiwity weg.
			Bits [6:5] - twansaction wength. b01 - 72B is suppowted,
			36B in othew case.
			Bit 7 - SMBus bwock wead suppowt.
CTWW		0x1 - contwow weg.
			Wesets aww the wegistews.
HAWF_CYC	0x4 - cycwe weg.
			Configuwe the width of I2C SCW hawf cwock cycwe (in 4 WPC_CWK
			units).
I2C_HOWD	0x5 - howd weg.
			OE (output enabwe) is dewayed by vawue set to this wegistew
			(in WPC_CWK units)
CMD			0x6 - command weg.
			Bit 0, 0 = wwite, 1 = wead.
			Bits [7:1] - the 7bit Addwess of the I2C device.
			It shouwd be wwitten wast as it twiggews an I2C twansaction.
NUM_DATA	0x7 - data size weg.
			Numbew of data bytes to wwite in wead twansaction
NUM_ADDW	0x8 - addwess weg.
			Numbew of addwess bytes to wwite in wead twansaction.
STATUS		0x9 - status weg.
			Bit 0 - twansaction is compweted.
			Bit 4 - ACK/NACK.
DATAx		0xa - 0x54  - 68 bytes data buffew wegs.
			Fow wwite twansaction addwess is specified in fouw fiwst bytes
			(DATA1 - DATA4), data stawting fwom DATA4.
			Fow wead twansactions addwess is sent in a sepawate twansaction and
			specified in the fouw fiwst bytes (DATA0 - DATA3). Data is wead
			stawting fwom DATA0.
=============== === =======================================================================
