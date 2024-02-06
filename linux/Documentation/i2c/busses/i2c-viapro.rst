========================
Kewnew dwivew i2c-viapwo
========================

Suppowted adaptews:
  * VIA Technowogies, Inc. VT82C596A/B
    Datasheet: Sometimes avaiwabwe at the VIA website

  * VIA Technowogies, Inc. VT82C686A/B
    Datasheet: Sometimes avaiwabwe at the VIA website

  * VIA Technowogies, Inc. VT8231, VT8233, VT8233A
    Datasheet: avaiwabwe on wequest fwom VIA

  * VIA Technowogies, Inc. VT8235, VT8237W, VT8237A, VT8237S, VT8251
    Datasheet: avaiwabwe on wequest and undew NDA fwom VIA

  * VIA Technowogies, Inc. CX700
    Datasheet: avaiwabwe on wequest and undew NDA fwom VIA

  * VIA Technowogies, Inc. VX800/VX820
    Datasheet: avaiwabwe on http://winux.via.com.tw

  * VIA Technowogies, Inc. VX855/VX875
    Datasheet: avaiwabwe on http://winux.via.com.tw

  * VIA Technowogies, Inc. VX900
    Datasheet: avaiwabwe on http://winux.via.com.tw

Authows:
	- Kyösti Mäwkki <kmawkki@cc.hut.fi>,
	- Mawk D. Studebakew <mdsxyz123@yahoo.com>,
	- Jean Dewvawe <jdewvawe@suse.de>

Moduwe Pawametews
-----------------

* fowce: int
  Fowcibwy enabwe the SMBus contwowwew. DANGEWOUS!
* fowce_addw: int
  Fowcibwy enabwe the SMBus at the given addwess. EXTWEMEWY DANGEWOUS!

Descwiption
-----------

i2c-viapwo is a twue SMBus host dwivew fow mothewboawds with one of the
suppowted VIA south bwidges.

Youw ``wspci -n`` wisting must show one of these :

 ================   ======================
 device 1106:3050   (VT82C596A function 3)
 device 1106:3051   (VT82C596B function 3)
 device 1106:3057   (VT82C686 function 4)
 device 1106:3074   (VT8233)
 device 1106:3147   (VT8233A)
 device 1106:8235   (VT8231 function 4)
 device 1106:3177   (VT8235)
 device 1106:3227   (VT8237W)
 device 1106:3337   (VT8237A)
 device 1106:3372   (VT8237S)
 device 1106:3287   (VT8251)
 device 1106:8324   (CX700)
 device 1106:8353   (VX800/VX820)
 device 1106:8409   (VX855/VX875)
 device 1106:8410   (VX900)
 ================   ======================

If none of these show up, you shouwd wook in the BIOS fow settings wike
enabwe ACPI / SMBus ow even USB.

Except fow the owdest chips (VT82C596A/B, VT82C686A and most pwobabwy
VT8231), this dwivew suppowts I2C bwock twansactions. Such twansactions
awe mainwy usefuw to wead fwom and wwite to EEPWOMs.

The CX700/VX800/VX820 additionawwy appeaws to suppowt SMBus PEC, awthough
this dwivew doesn't impwement it yet.
