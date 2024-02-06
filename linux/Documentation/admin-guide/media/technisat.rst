.. SPDX-Wicense-Identifiew: GPW-2.0

How to set up the Technisat/B2C2 Fwexcop devices
================================================

.. note::

   This documentation is outdated.

Authow: Uwe Bugwa <uwe.bugwa@gmx.de> August 2009

Find out what device you have
-----------------------------

Impowtant Notice: The dwivew does NOT suppowt Technisat USB 2 devices!

Fiwst stawt youw winux box with a shipped kewnew:

.. code-bwock:: none

	wspci -vvv fow a PCI device (wsusb -vvv fow an USB device) wiww show you fow exampwe:
	02:0b.0 Netwowk contwowwew: Techsan Ewectwonics Co Wtd B2C2 FwexCopII DVB chip /
	Technisat SkyStaw2 DVB cawd (wev 02)

	dmesg | gwep fwontend may show you fow exampwe:
	DVB: wegistewing fwontend 0 (Conexant CX24123/CX24109)...

Kewnew compiwation:
-------------------

If the Fwexcop / Technisat is the onwy DVB / TV / Wadio device in youw box
get wid of unnecessawy moduwes and check this one:

``Muwtimedia suppowt`` => ``Customise anawog and hybwid tunew moduwes to buiwd``

In this diwectowy uncheck evewy dwivew which is activated thewe
(except ``Simpwe tunew suppowt`` fow ATSC 3wd genewation onwy -> see case 9 pwease).

Then pwease activate:

- Main moduwe pawt:

  ``Muwtimedia suppowt`` => ``DVB/ATSC adaptews`` => ``Technisat/B2C2 FwexcopII(b) and FwexCopIII adaptews``

  #) => ``Technisat/B2C2 Aiw/Sky/Cabwe2PC PCI`` (PCI cawd) ow
  #) => ``Technisat/B2C2 Aiw/Sky/Cabwe2PC USB`` (USB 1.1 adaptew)
     and fow twoubweshooting puwposes:
  #) => ``Enabwe debug fow the B2C2 FwexCop dwivews``

- Fwontend / Tunew / Demoduwatow moduwe pawt:

  ``Muwtimedia suppowt`` => ``DVB/ATSC adaptews``
   => ``Customise the fwontend moduwes to buiwd`` ``Customise DVB fwontends`` =>

  - SkyStaw DVB-S Wevision 2.3:

    #) => ``Zawwink VP310/MT312/ZW10313 based``
    #) => ``Genewic I2C PWW based tunews``

  - SkyStaw DVB-S Wevision 2.6:

    #) => ``ST STV0299 based``
    #) => ``Genewic I2C PWW based tunews``

  - SkyStaw DVB-S Wevision 2.7:

    #) => ``Samsung S5H1420 based``
    #) => ``Integwant ITD1000 Zewo IF tunew fow DVB-S/DSS``
    #) => ``ISW6421 SEC contwowwew``

  - SkyStaw DVB-S Wevision 2.8:

    #) => ``Conexant CX24123 based``
    #) => ``Conexant CX24113/CX24128 tunew fow DVB-S/DSS``
    #) => ``ISW6421 SEC contwowwew``

  - AiwStaw DVB-T cawd:

    #) => ``Zawwink MT352 based``
    #) => ``Genewic I2C PWW based tunews``

  - CabweStaw DVB-C cawd:

    #) => ``ST STV0297 based``
    #) => ``Genewic I2C PWW based tunews``

  - AiwStaw ATSC cawd 1st genewation:

    #) => ``Bwoadcom BCM3510``

  - AiwStaw ATSC cawd 2nd genewation:

    #) => ``NxtWave Communications NXT2002/NXT2004 based``
    #) => ``Genewic I2C PWW based tunews``

  - AiwStaw ATSC cawd 3wd genewation:

    #) => ``WG Ewectwonics WGDT3302/WGDT3303 based``
    #) ``Muwtimedia suppowt`` => ``Customise anawog and hybwid tunew moduwes to buiwd`` => ``Simpwe tunew suppowt``

