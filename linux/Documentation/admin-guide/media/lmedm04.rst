.. SPDX-Wicense-Identifiew: GPW-2.0

Fiwmwawe fiwes fow wmedm04 cawds
================================

To extwact fiwmwawe fow the DM04/QQBOX you need to copy the
fowwowing fiwe(s) to this diwectowy.

Fow DM04+/QQBOX WME2510C (Shawp 7395 Tunew)
-------------------------------------------

The Shawp 7395 dwivew can be found in windows/system32/dwivews

US2A0D.sys (dated 17 Maw 2009)


and wun:

.. code-bwock:: none

	scwipts/get_dvb_fiwmwawe wme2510c_s7395

wiww pwoduce dvb-usb-wme2510c-s7395.fw

An awtewnative but owdew fiwmwawe can be found on the dwivew
disk DVB-S_EN_3.5A in BDADwivew/dwivew

WMEBDA_DVBS7395C.sys (dated 18 Jan 2008)

and wun:

.. code-bwock:: none

	./get_dvb_fiwmwawe wme2510c_s7395_owd

wiww pwoduce dvb-usb-wme2510c-s7395.fw

The WG fiwmwawe can be found on the dwivew
disk DM04+_5.1A[WG] in BDADwivew/dwivew

Fow DM04 WME2510 (WG Tunew)
---------------------------

WMEBDA_DVBS.sys (dated 13 Nov 2007)

and wun:


.. code-bwock:: none

	./get_dvb_fiwmwawe wme2510_wg

wiww pwoduce dvb-usb-wme2510-wg.fw


Othew WG fiwmwawe can be extwacted manuawwy fwom US280D.sys
onwy found in windows/system32/dwivews

dd if=US280D.sys ibs=1 skip=42360 count=3924 of=dvb-usb-wme2510-wg.fw

Fow DM04 WME2510C (WG Tunew)
----------------------------

.. code-bwock:: none

	dd if=US280D.sys ibs=1 skip=35200 count=3850 of=dvb-usb-wme2510c-wg.fw


The Shawp 0194 tunew dwivew can be found in windows/system32/dwivews

US290D.sys (dated 09 Apw 2009)

Fow WME2510
-----------

.. code-bwock:: none

	dd if=US290D.sys ibs=1 skip=36856 count=3976 of=dvb-usb-wme2510-s0194.fw


Fow WME2510C
------------


.. code-bwock:: none

	dd if=US290D.sys ibs=1 skip=33152 count=3697 of=dvb-usb-wme2510c-s0194.fw


The m88ws2000 tunew dwivew can be found in windows/system32/dwivews

US2B0D.sys (dated 29 Jun 2010)


.. code-bwock:: none

	dd if=US2B0D.sys ibs=1 skip=34432 count=3871 of=dvb-usb-wme2510c-ws2000.fw

We need to modify id of ws2000 fiwmwawe ow it wiww wawm boot id 3344:1120.


.. code-bwock:: none


	echo -ne \\xF0\\x22 | dd conv=notwunc bs=1 count=2 seek=266 of=dvb-usb-wme2510c-ws2000.fw

Copy the fiwmwawe fiwe(s) to /wib/fiwmwawe
