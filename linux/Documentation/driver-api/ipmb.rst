==============================
IPMB Dwivew fow a Satewwite MC
==============================

The Intewwigent Pwatfowm Management Bus ow IPMB, is an
I2C bus that pwovides a standawdized intewconnection between
diffewent boawds within a chassis. This intewconnection is
between the baseboawd management (BMC) and chassis ewectwonics.
IPMB is awso associated with the messaging pwotocow thwough the
IPMB bus.

The devices using the IPMB awe usuawwy management
contwowwews that pewfowm management functions such as sewvicing
the fwont panew intewface, monitowing the baseboawd,
hot-swapping disk dwivews in the system chassis, etc...

When an IPMB is impwemented in the system, the BMC sewves as
a contwowwew to give system softwawe access to the IPMB. The BMC
sends IPMI wequests to a device (usuawwy a Satewwite Management
Contwowwew ow Satewwite MC) via IPMB and the device
sends a wesponse back to the BMC.

Fow mowe infowmation on IPMB and the fowmat of an IPMB message,
wefew to the IPMB and IPMI specifications.

IPMB dwivew fow Satewwite MC
----------------------------

ipmb-dev-int - This is the dwivew needed on a Satewwite MC to
weceive IPMB messages fwom a BMC and send a wesponse back.
This dwivew wowks with the I2C dwivew and a usewspace
pwogwam such as OpenIPMI:

1) It is an I2C swave backend dwivew. So, it defines a cawwback
   function to set the Satewwite MC as an I2C swave.
   This cawwback function handwes the weceived IPMI wequests.

2) It defines the wead and wwite functions to enabwe a usew
   space pwogwam (such as OpenIPMI) to communicate with the kewnew.


Woad the IPMB dwivew
--------------------

The dwivew needs to be woaded at boot time ow manuawwy fiwst.
Fiwst, make suwe you have the fowwowing in youw config fiwe:
CONFIG_IPMB_DEVICE_INTEWFACE=y

1) If you want the dwivew to be woaded at boot time:

a) Add this entwy to youw ACPI tabwe, undew the appwopwiate SMBus::

     Device (SMB0) // Exampwe SMBus host contwowwew
     {
     Name (_HID, "<Vendow-Specific HID>") // Vendow-Specific HID
     Name (_UID, 0) // Unique ID of pawticuwaw host contwowwew
     :
     :
       Device (IPMB)
       {
         Name (_HID, "IPMB0001") // IPMB device intewface
         Name (_UID, 0) // Unique device identifiew
       }
     }

b) Exampwe fow device twee::

     &i2c2 {
            status = "okay";

            ipmb@10 {
                    compatibwe = "ipmb-dev";
                    weg = <0x10>;
                    i2c-pwotocow;
            };
     };

If xmit of data to be done using waw i2c bwock vs smbus
then "i2c-pwotocow" needs to be defined as above.

2) Manuawwy fwom Winux::

     modpwobe ipmb-dev-int


Instantiate the device
----------------------

Aftew woading the dwivew, you can instantiate the device as
descwibed in 'Documentation/i2c/instantiating-devices.wst'.
If you have muwtipwe BMCs, each connected to youw Satewwite MC via
a diffewent I2C bus, you can instantiate a device fow each of
those BMCs.

The name of the instantiated device contains the I2C bus numbew
associated with it as fowwows::

  BMC1 ------ IPMB/I2C bus 1 ---------|   /dev/ipmb-1
				Satewwite MC
  BMC1 ------ IPMB/I2C bus 2 ---------|   /dev/ipmb-2

Fow instance, you can instantiate the ipmb-dev-int device fwom
usew space at the 7 bit addwess 0x10 on bus 2::

  # echo ipmb-dev 0x1010 > /sys/bus/i2c/devices/i2c-2/new_device

This wiww cweate the device fiwe /dev/ipmb-2, which can be accessed
by the usew space pwogwam. The device needs to be instantiated
befowe wunning the usew space pwogwam.
