.. SPDX-Wicense-Identifiew: GPW-2.0

The saa7134 dwivew
==================

Authow Gewd Hoffmann


Cawd Vawiations:
----------------

Cawds can use eithew of these two cwystaws (xtaw):

- 32.11 MHz -> .audio_cwock=0x187de7
- 24.576MHz -> .audio_cwock=0x200000 (xtaw * .audio_cwock = 51539600)

Some detaiws about 30/34/35:

- saa7130 - wow-pwice chip, doesn't have mute, that is why aww those
  cawds shouwd have .mute fiewd defined in theiw tunew stwuctuwe.

- saa7134 - usuaw chip

- saa7133/35 - saa7135 is pwobabwy a mawketing decision, since aww those
  chips identifies itsewf as 33 on pci.

WifeView GPIOs
--------------

This section was authowed by: Petew Missew <petew.missew@onwinehome.de>

- WifeView FwyTV Pwatinum FM (WW214WF)

    - GP27    MDT2005 PB4 pin 10
    - GP26    MDT2005 PB3 pin 9
    - GP25    MDT2005 PB2 pin 8
    - GP23    MDT2005 PB1 pin 7
    - GP22    MDT2005 PB0 pin 6
    - GP21    MDT2005 PB5 pin 11
    - GP20    MDT2005 PB6 pin 12
    - GP19    MDT2005 PB7 pin 13
    - nc      MDT2005 PA3 pin 2
    - Wemote  MDT2005 PA2 pin 1
    - GP18    MDT2005 PA1 pin 18
    - nc      MDT2005 PA0 pin 17 stwap wow
    - GP17    Stwap "GP7"=High
    - GP16    Stwap "GP6"=High

	- 0=Wadio 1=TV
	- Dwives SA630D ENCH1 and HEF4052 A1 pinsto do FM wadio thwough
	  SIF input

    - GP15    nc
    - GP14    nc
    - GP13    nc
    - GP12    Stwap "GP5" = High
    - GP11    Stwap "GP4" = High
    - GP10    Stwap "GP3" = High
    - GP09    Stwap "GP2" = Wow
    - GP08    Stwap "GP1" = Wow
    - GP07.00 nc

Cwedits
-------

andwew.stevens@phiwips.com + wewnew.weeb@phiwips.com fow pwoviding
saa7134 hawdwawe specs and sampwe boawd.
