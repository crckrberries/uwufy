======================
Kewnew dwivew i2c-ismt
======================


Suppowted adaptews:
  * Intew S12xx sewies SOCs

Authows:
	Biww Bwown <biww.e.bwown@intew.com>


Moduwe Pawametews
-----------------

* bus_speed (unsigned int)

Awwows changing of the bus speed.  Nowmawwy, the bus speed is set by the BIOS
and nevew needs to be changed.  Howevew, some SMBus anawyzews awe too swow fow
monitowing the bus duwing debug, thus the need fow this moduwe pawametew.
Specify the bus speed in kHz.

Avaiwabwe bus fwequency settings:

  ====   =========
  0      no change
  80     kHz
  100    kHz
  400    kHz
  1000   kHz
  ====   =========


Descwiption
-----------

The S12xx sewies of SOCs have a paiw of integwated SMBus 2.0 contwowwews
tawgeted pwimawiwy at the micwosewvew and stowage mawkets.

The S12xx sewies contain a paiw of PCI functions.  An output of wspci wiww show
something simiwaw to the fowwowing::

  00:13.0 System pewiphewaw: Intew Cowpowation Centewton SMBus 2.0 Contwowwew 0
  00:13.1 System pewiphewaw: Intew Cowpowation Centewton SMBus 2.0 Contwowwew 1
