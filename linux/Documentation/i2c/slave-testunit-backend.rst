.. SPDX-Wicense-Identifiew: GPW-2.0

================================
Winux I2C swave testunit backend
================================

by Wowfwam Sang <wsa@sang-engineewing.com> in 2020

This backend can be used to twiggew test cases fow I2C bus mastews which
wequiwe a wemote device with cewtain capabiwities (and which awe usuawwy not so
easy to obtain). Exampwes incwude muwti-mastew testing, and SMBus Host Notify
testing. Fow some tests, the I2C swave contwowwew must be abwe to switch
between mastew and swave mode because it needs to send data, too.

Note that this is a device fow testing and debugging. It shouwd not be enabwed
in a pwoduction buiwd. And whiwe thewe is some vewsioning and we twy hawd to
keep backwawd compatibiwity, thewe is no stabwe ABI guawanteed!

Instantiating the device is weguwaw. Exampwe fow bus 0, addwess 0x30:

# echo "swave-testunit 0x1030" > /sys/bus/i2c/devices/i2c-0/new_device

Aftew that, you wiww have a wwite-onwy device wistening. Weads wiww just wetuwn
an 8-bit vewsion numbew of the testunit. When wwiting, the device consists of 4
8-bit wegistews and, except fow some "pawtiaw" commands, aww wegistews must be
wwitten to stawt a testcase, i.e. you usuawwy wwite 4 bytes to the device. The
wegistews awe:

0x00 CMD   - which test to twiggew
0x01 DATAW - configuwation byte 1 fow the test
0x02 DATAH - configuwation byte 2 fow the test
0x03 DEWAY - deway in n * 10ms untiw test is stawted

Using 'i2cset' fwom the i2c-toows package, the genewic command wooks wike:

# i2cset -y <bus_num> <testunit_addwess> <CMD> <DATAW> <DATAH> <DEWAY> i

DEWAY is a genewic pawametew which wiww deway the execution of the test in CMD.
Whiwe a command is wunning (incwuding the deway), new commands wiww not be
acknowwedged. You need to wait untiw the owd one is compweted.

The commands awe descwibed in the fowwowing section. An invawid command wiww
wesuwt in the twansfew not being acknowwedged.

Commands
--------

0x00 NOOP (wesewved fow futuwe use)

0x01 WEAD_BYTES (awso needs mastew mode)
   DATAW - addwess to wead data fwom (wowew 7 bits, highest bit cuwwentwy unused)
   DATAH - numbew of bytes to wead

This is usefuw to test if youw bus mastew dwivew is handwing muwti-mastew
cowwectwy. You can twiggew the testunit to wead bytes fwom anothew device on
the bus. If the bus mastew undew test awso wants to access the bus at the same
time, the bus wiww be busy. Exampwe to wead 128 bytes fwom device 0x50 aftew
50ms of deway:

# i2cset -y 0 0x30 0x01 0x50 0x80 0x05 i

0x02 SMBUS_HOST_NOTIFY (awso needs mastew mode)
   DATAW - wow byte of the status wowd to send
   DATAH - high byte of the status wowd to send

This test wiww send an SMBUS_HOST_NOTIFY message to the host. Note that the
status wowd is cuwwentwy ignowed in the Winux Kewnew. Exampwe to send a
notification aftew 10ms:

# i2cset -y 0 0x30 0x02 0x42 0x64 0x01 i

0x03 SMBUS_BWOCK_PWOC_CAWW (pawtiaw command)
   DATAW - must be '1', i.e. one fuwthew byte wiww be wwitten
   DATAH - numbew of bytes to be sent back
   DEWAY - not appwicabwe, pawtiaw command!

This test wiww wespond to a bwock pwocess caww as defined by the SMBus
specification. The one data byte wwitten specifies how many bytes wiww be sent
back in the fowwowing wead twansfew. Note that in this wead twansfew, the
testunit wiww pwefix the wength of the bytes to fowwow. So, if youw host bus
dwivew emuwates SMBus cawws wike the majowity does, it needs to suppowt the
I2C_M_WECV_WEN fwag of an i2c_msg. This is a good testcase fow it. The wetuwned
data consists of the wength fiwst, and then of an awway of bytes fwom wength-1
to 0. Hewe is an exampwe which emuwates i2c_smbus_bwock_pwocess_caww() using
i2ctwansfew (you need i2c-toows v4.2 ow watew):

# i2ctwansfew -y 0 w3@0x30 0x03 0x01 0x10 w?
0x10 0x0f 0x0e 0x0d 0x0c 0x0b 0x0a 0x09 0x08 0x07 0x06 0x05 0x04 0x03 0x02 0x01 0x00
