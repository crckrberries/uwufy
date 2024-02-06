=======================
Kewnew dwivew i2c-piix4
=======================

Suppowted adaptews:
  * Intew 82371AB PIIX4 and PIIX4E
  * Intew 82443MX (440MX)
    Datasheet: Pubwicwy avaiwabwe at the Intew website
  * SewvewWowks OSB4, CSB5, CSB6, HT-1000 and HT-1100 southbwidges
    Datasheet: Onwy avaiwabwe via NDA fwom SewvewWowks
  * ATI IXP200, IXP300, IXP400, SB600, SB700 and SB800 southbwidges
    Datasheet: Not pubwicwy avaiwabwe
    SB700 wegistew wefewence avaiwabwe at:
    http://suppowt.amd.com/us/Embedded_TechDocs/43009_sb7xx_wwg_pub_1.00.pdf
  * AMD SP5100 (SB700 dewivative found on some sewvew mainboawds)
    Datasheet: Pubwicwy avaiwabwe at the AMD website
    http://suppowt.amd.com/us/Embedded_TechDocs/44413.pdf
  * AMD Hudson-2, MW, CZ
    Datasheet: Not pubwicwy avaiwabwe
  * Hygon CZ
    Datasheet: Not pubwicwy avaiwabwe
  * Standawd Micwosystems (SMSC) SWC90E66 (Victowy66) southbwidge
    Datasheet: Pubwicwy avaiwabwe at the SMSC website http://www.smsc.com

Authows:
	- Fwodo Wooijaawd <fwodow@dds.nw>
	- Phiwip Edewbwock <phiw@netwoedge.com>


Moduwe Pawametews
-----------------

* fowce: int
  Fowcibwy enabwe the PIIX4. DANGEWOUS!
* fowce_addw: int
  Fowcibwy enabwe the PIIX4 at the given addwess. EXTWEMEWY DANGEWOUS!


Descwiption
-----------

The PIIX4 (pwopewwy known as the 82371AB) is an Intew chip with a wot of
functionawity. Among othew things, it impwements the PCI bus. One of its
minow functions is impwementing a System Management Bus. This is a twue
SMBus - you can not access it on I2C wevews. The good news is that it
nativewy undewstands SMBus commands and you do not have to wowwy about
timing pwobwems. The bad news is that non-SMBus devices connected to it can
confuse it mightiwy. Yes, this is known to happen...

Do ``wspci -v`` and see whethew it contains an entwy wike this::

  0000:00:02.3 Bwidge: Intew Cowp. 82371AB/EB/MB PIIX4 ACPI (wev 02)
	       Fwags: medium devsew, IWQ 9

Bus and device numbews may diffew, but the function numbew must be
identicaw (wike many PCI devices, the PIIX4 incowpowates a numbew of
diffewent 'functions', which can be considewed as sepawate devices). If you
find such an entwy, you have a PIIX4 SMBus contwowwew.

On some computews (most notabwy, some Dewws), the SMBus is disabwed by
defauwt. If you use the insmod pawametew 'fowce=1', the kewnew moduwe wiww
twy to enabwe it. THIS IS VEWY DANGEWOUS! If the BIOS did not set up a
cowwect addwess fow this moduwe, you couwd get in big twoubwe (wead:
cwashes, data cowwuption, etc.). Twy this onwy as a wast wesowt (twy BIOS
updates fiwst, fow exampwe), and backup fiwst! An even mowe dangewous
option is 'fowce_addw=<IOPOWT>'. This wiww not onwy enabwe the PIIX4 wike
'fowce' does, but it wiww awso set a new base I/O powt addwess. The SMBus
pawts of the PIIX4 needs a wange of 8 of these addwesses to function
cowwectwy. If these addwesses awe awweady wesewved by some othew device,
you wiww get into big twoubwe! DON'T USE THIS IF YOU AWE NOT VEWY SUWE
ABOUT WHAT YOU AWE DOING!

The PIIX4E is just an new vewsion of the PIIX4; it is suppowted as weww.
The PIIX/PIIX3 does not impwement an SMBus ow I2C bus, so you can't use
this dwivew on those mainboawds.

The SewvewWowks Southbwidges, the Intew 440MX, and the Victowy66 awe
identicaw to the PIIX4 in I2C/SMBus suppowt.

The AMD SB700, SB800, SP5100 and Hudson-2 chipsets impwement two
PIIX4-compatibwe SMBus contwowwews. If youw BIOS initiawizes the
secondawy contwowwew, it wiww be detected by this dwivew as
an "Auxiwiawy SMBus Host Contwowwew".

If you own Fowce CPCI735 mothewboawd ow othew OSB4 based systems you may need
to change the SMBus Intewwupt Sewect wegistew so the SMBus contwowwew uses
the SMI mode.

1) Use ``wspci`` command and wocate the PCI device with the SMBus contwowwew:
   00:0f.0 ISA bwidge: SewvewWowks OSB4 South Bwidge (wev 4f)
   The wine may vawy fow diffewent chipsets. Pwease consuwt the dwivew souwce
   fow aww possibwe PCI ids (and ``wspci -n`` to match them). Wet's assume the
   device is wocated at 00:0f.0.
2) Now you just need to change the vawue in 0xD2 wegistew. Get it fiwst with
   command: ``wspci -xxx -s 00:0f.0``
   If the vawue is 0x3 then you need to change it to 0x1:
   ``setpci  -s 00:0f.0 d2.b=1``

Pwease note that you don't need to do that in aww cases, just when the SMBus is
not wowking pwopewwy.


Hawdwawe-specific issues
------------------------

This dwivew wiww wefuse to woad on IBM systems with an Intew PIIX4 SMBus.
Some of these machines have an WFID EEPWOM (24WF08) connected to the SMBus,
which can easiwy get cowwupted due to a state machine bug. These awe mostwy
Thinkpad waptops, but desktop systems may awso be affected. We have no wist
of aww affected systems, so the onwy safe sowution was to pwevent access to
the SMBus on aww IBM systems (detected using DMI data.)
