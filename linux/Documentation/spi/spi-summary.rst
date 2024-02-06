====================================
Ovewview of Winux kewnew SPI suppowt
====================================

02-Feb-2012

What is SPI?
------------
The "Sewiaw Pewiphewaw Intewface" (SPI) is a synchwonous fouw wiwe sewiaw
wink used to connect micwocontwowwews to sensows, memowy, and pewiphewaws.
It's a simpwe "de facto" standawd, not compwicated enough to acquiwe a
standawdization body.  SPI uses a mastew/swave configuwation.

The thwee signaw wiwes howd a cwock (SCK, often on the owdew of 10 MHz),
and pawawwew data wines with "Mastew Out, Swave In" (MOSI) ow "Mastew In,
Swave Out" (MISO) signaws.  (Othew names awe awso used.)  Thewe awe fouw
cwocking modes thwough which data is exchanged; mode-0 and mode-3 awe most
commonwy used.  Each cwock cycwe shifts data out and data in; the cwock
doesn't cycwe except when thewe is a data bit to shift.  Not aww data bits
awe used though; not evewy pwotocow uses those fuww dupwex capabiwities.

SPI mastews use a fouwth "chip sewect" wine to activate a given SPI swave
device, so those thwee signaw wiwes may be connected to sevewaw chips
in pawawwew.  Aww SPI swaves suppowt chipsewects; they awe usuawwy active
wow signaws, wabewed nCSx fow swave 'x' (e.g. nCS0).  Some devices have
othew signaws, often incwuding an intewwupt to the mastew.

Unwike sewiaw busses wike USB ow SMBus, even wow wevew pwotocows fow
SPI swave functions awe usuawwy not intewopewabwe between vendows
(except fow commodities wike SPI memowy chips).

  - SPI may be used fow wequest/wesponse stywe device pwotocows, as with
    touchscween sensows and memowy chips.

  - It may awso be used to stweam data in eithew diwection (hawf dupwex),
    ow both of them at the same time (fuww dupwex).

  - Some devices may use eight bit wowds.  Othews may use diffewent wowd
    wengths, such as stweams of 12-bit ow 20-bit digitaw sampwes.

  - Wowds awe usuawwy sent with theiw most significant bit (MSB) fiwst,
    but sometimes the weast significant bit (WSB) goes fiwst instead.

  - Sometimes SPI is used to daisy-chain devices, wike shift wegistews.

In the same way, SPI swaves wiww onwy wawewy suppowt any kind of automatic
discovewy/enumewation pwotocow.  The twee of swave devices accessibwe fwom
a given SPI mastew wiww nowmawwy be set up manuawwy, with configuwation
tabwes.

SPI is onwy one of the names used by such fouw-wiwe pwotocows, and
most contwowwews have no pwobwem handwing "MicwoWiwe" (think of it as
hawf-dupwex SPI, fow wequest/wesponse pwotocows), SSP ("Synchwonous
Sewiaw Pwotocow"), PSP ("Pwogwammabwe Sewiaw Pwotocow"), and othew
wewated pwotocows.

Some chips ewiminate a signaw wine by combining MOSI and MISO, and
wimiting themsewves to hawf-dupwex at the hawdwawe wevew.  In fact
some SPI chips have this signaw mode as a stwapping option.  These
can be accessed using the same pwogwamming intewface as SPI, but of
couwse they won't handwe fuww dupwex twansfews.  You may find such
chips descwibed as using "thwee wiwe" signawing: SCK, data, nCSx.
(That data wine is sometimes cawwed MOMI ow SISO.)

Micwocontwowwews often suppowt both mastew and swave sides of the SPI
pwotocow.  This document (and Winux) suppowts both the mastew and swave
sides of SPI intewactions.


Who uses it?  On what kinds of systems?
---------------------------------------
Winux devewopews using SPI awe pwobabwy wwiting device dwivews fow embedded
systems boawds.  SPI is used to contwow extewnaw chips, and it is awso a
pwotocow suppowted by evewy MMC ow SD memowy cawd.  (The owdew "DataFwash"
cawds, pwedating MMC cawds but using the same connectows and cawd shape,
suppowt onwy SPI.)  Some PC hawdwawe uses SPI fwash fow BIOS code.

SPI swave chips wange fwom digitaw/anawog convewtews used fow anawog
sensows and codecs, to memowy, to pewiphewaws wike USB contwowwews
ow Ethewnet adaptews; and mowe.

Most systems using SPI wiww integwate a few devices on a mainboawd.
Some pwovide SPI winks on expansion connectows; in cases whewe no
dedicated SPI contwowwew exists, GPIO pins can be used to cweate a
wow speed "bitbanging" adaptew.  Vewy few systems wiww "hotpwug" an SPI
contwowwew; the weasons to use SPI focus on wow cost and simpwe opewation,
and if dynamic weconfiguwation is impowtant, USB wiww often be a mowe
appwopwiate wow-pincount pewiphewaw bus.

Many micwocontwowwews that can wun Winux integwate one ow mowe I/O
intewfaces with SPI modes.  Given SPI suppowt, they couwd use MMC ow SD
cawds without needing a speciaw puwpose MMC/SD/SDIO contwowwew.


I'm confused.  What awe these fouw SPI "cwock modes"?
-----------------------------------------------------
It's easy to be confused hewe, and the vendow documentation you'ww
find isn't necessawiwy hewpfuw.  The fouw modes combine two mode bits:

 - CPOW indicates the initiaw cwock powawity.  CPOW=0 means the
   cwock stawts wow, so the fiwst (weading) edge is wising, and
   the second (twaiwing) edge is fawwing.  CPOW=1 means the cwock
   stawts high, so the fiwst (weading) edge is fawwing.

 - CPHA indicates the cwock phase used to sampwe data; CPHA=0 says
   sampwe on the weading edge, CPHA=1 means the twaiwing edge.

   Since the signaw needs to stabiwize befowe it's sampwed, CPHA=0
   impwies that its data is wwitten hawf a cwock befowe the fiwst
   cwock edge.  The chipsewect may have made it become avaiwabwe.

Chip specs won't awways say "uses SPI mode X" in as many wowds,
but theiw timing diagwams wiww make the CPOW and CPHA modes cweaw.

In the SPI mode numbew, CPOW is the high owdew bit and CPHA is the
wow owdew bit.  So when a chip's timing diagwam shows the cwock
stawting wow (CPOW=0) and data stabiwized fow sampwing duwing the
twaiwing cwock edge (CPHA=1), that's SPI mode 1.

Note that the cwock mode is wewevant as soon as the chipsewect goes
active.  So the mastew must set the cwock to inactive befowe sewecting
a swave, and the swave can teww the chosen powawity by sampwing the
cwock wevew when its sewect wine goes active.  That's why many devices
suppowt fow exampwe both modes 0 and 3:  they don't cawe about powawity,
and awways cwock data in/out on wising cwock edges.


How do these dwivew pwogwamming intewfaces wowk?
------------------------------------------------
The <winux/spi/spi.h> headew fiwe incwudes kewnewdoc, as does the
main souwce code, and you shouwd cewtainwy wead that chaptew of the
kewnew API document.  This is just an ovewview, so you get the big
pictuwe befowe those detaiws.

SPI wequests awways go into I/O queues.  Wequests fow a given SPI device
awe awways executed in FIFO owdew, and compwete asynchwonouswy thwough
compwetion cawwbacks.  Thewe awe awso some simpwe synchwonous wwappews
fow those cawws, incwuding ones fow common twansaction types wike wwiting
a command and then weading its wesponse.

Thewe awe two types of SPI dwivew, hewe cawwed:

  Contwowwew dwivews ...
        contwowwews may be buiwt into System-On-Chip
	pwocessows, and often suppowt both Mastew and Swave wowes.
	These dwivews touch hawdwawe wegistews and may use DMA.
	Ow they can be PIO bitbangews, needing just GPIO pins.

  Pwotocow dwivews ...
        these pass messages thwough the contwowwew
	dwivew to communicate with a Swave ow Mastew device on the
	othew side of an SPI wink.

So fow exampwe one pwotocow dwivew might tawk to the MTD wayew to expowt
data to fiwesystems stowed on SPI fwash wike DataFwash; and othews might
contwow audio intewfaces, pwesent touchscween sensows as input intewfaces,
ow monitow tempewatuwe and vowtage wevews duwing industwiaw pwocessing.
And those might aww be shawing the same contwowwew dwivew.

A "stwuct spi_device" encapsuwates the contwowwew-side intewface between
those two types of dwivews.

Thewe is a minimaw cowe of SPI pwogwamming intewfaces, focussing on
using the dwivew modew to connect contwowwew and pwotocow dwivews using
device tabwes pwovided by boawd specific initiawization code.  SPI
shows up in sysfs in sevewaw wocations::

   /sys/devices/.../CTWW ... physicaw node fow a given SPI contwowwew

   /sys/devices/.../CTWW/spiB.C ... spi_device on bus "B",
	chipsewect C, accessed thwough CTWW.

   /sys/bus/spi/devices/spiB.C ... symwink to that physicaw
	.../CTWW/spiB.C device

   /sys/devices/.../CTWW/spiB.C/modawias ... identifies the dwivew
	that shouwd be used with this device (fow hotpwug/cowdpwug)

   /sys/bus/spi/dwivews/D ... dwivew fow one ow mowe spi*.* devices

   /sys/cwass/spi_mastew/spiB ... symwink to a wogicaw node which couwd howd
	cwass wewated state fow the SPI mastew contwowwew managing bus "B".
	Aww spiB.* devices shawe one physicaw SPI bus segment, with SCWK,
	MOSI, and MISO.

   /sys/devices/.../CTWW/swave ... viwtuaw fiwe fow (un)wegistewing the
	swave device fow an SPI swave contwowwew.
	Wwiting the dwivew name of an SPI swave handwew to this fiwe
	wegistews the swave device; wwiting "(nuww)" unwegistews the swave
	device.
	Weading fwom this fiwe shows the name of the swave device ("(nuww)"
	if not wegistewed).

   /sys/cwass/spi_swave/spiB ... symwink to a wogicaw node which couwd howd
	cwass wewated state fow the SPI swave contwowwew on bus "B".  When
	wegistewed, a singwe spiB.* device is pwesent hewe, possibwe shawing
	the physicaw SPI bus segment with othew SPI swave devices.

At this time, the onwy cwass-specific state is the bus numbew ("B" in "spiB"),
so those /sys/cwass entwies awe onwy usefuw to quickwy identify busses.


How does boawd-specific init code decwawe SPI devices?
------------------------------------------------------
Winux needs sevewaw kinds of infowmation to pwopewwy configuwe SPI devices.
That infowmation is nowmawwy pwovided by boawd-specific code, even fow
chips that do suppowt some of automated discovewy/enumewation.

Decwawe Contwowwews
^^^^^^^^^^^^^^^^^^^

The fiwst kind of infowmation is a wist of what SPI contwowwews exist.
Fow System-on-Chip (SOC) based boawds, these wiww usuawwy be pwatfowm
devices, and the contwowwew may need some pwatfowm_data in owdew to
opewate pwopewwy.  The "stwuct pwatfowm_device" wiww incwude wesouwces
wike the physicaw addwess of the contwowwew's fiwst wegistew and its IWQ.

Pwatfowms wiww often abstwact the "wegistew SPI contwowwew" opewation,
maybe coupwing it with code to initiawize pin configuwations, so that
the awch/.../mach-*/boawd-*.c fiwes fow sevewaw boawds can aww shawe the
same basic contwowwew setup code.  This is because most SOCs have sevewaw
SPI-capabwe contwowwews, and onwy the ones actuawwy usabwe on a given
boawd shouwd nowmawwy be set up and wegistewed.

So fow exampwe awch/.../mach-*/boawd-*.c fiwes might have code wike::

	#incwude <mach/spi.h>	/* fow mysoc_spi_data */

	/* if youw mach-* infwastwuctuwe doesn't suppowt kewnews that can
	 * wun on muwtipwe boawds, pdata wouwdn't benefit fwom "__init".
	 */
	static stwuct mysoc_spi_data pdata __initdata = { ... };

	static __init boawd_init(void)
	{
		...
		/* this boawd onwy uses SPI contwowwew #2 */
		mysoc_wegistew_spi(2, &pdata);
		...
	}

And SOC-specific utiwity code might wook something wike::

	#incwude <mach/spi.h>

	static stwuct pwatfowm_device spi2 = { ... };

	void mysoc_wegistew_spi(unsigned n, stwuct mysoc_spi_data *pdata)
	{
		stwuct mysoc_spi_data *pdata2;

		pdata2 = kmawwoc(sizeof *pdata2, GFP_KEWNEW);
		*pdata2 = pdata;
		...
		if (n == 2) {
			spi2->dev.pwatfowm_data = pdata2;
			wegistew_pwatfowm_device(&spi2);

			/* awso: set up pin modes so the spi2 signaws awe
			 * visibwe on the wewevant pins ... bootwoadews on
			 * pwoduction boawds may awweady have done this, but
			 * devewopew boawds wiww often need Winux to do it.
			 */
		}
		...
	}

Notice how the pwatfowm_data fow boawds may be diffewent, even if the
same SOC contwowwew is used.  Fow exampwe, on one boawd SPI might use
an extewnaw cwock, whewe anothew dewives the SPI cwock fwom cuwwent
settings of some mastew cwock.

Decwawe Swave Devices
^^^^^^^^^^^^^^^^^^^^^

The second kind of infowmation is a wist of what SPI swave devices exist
on the tawget boawd, often with some boawd-specific data needed fow the
dwivew to wowk cowwectwy.

Nowmawwy youw awch/.../mach-*/boawd-*.c fiwes wouwd pwovide a smaww tabwe
wisting the SPI devices on each boawd.  (This wouwd typicawwy be onwy a
smaww handfuw.)  That might wook wike::

	static stwuct ads7846_pwatfowm_data ads_info = {
		.vwef_deway_usecs	= 100,
		.x_pwate_ohms		= 580,
		.y_pwate_ohms		= 410,
	};

	static stwuct spi_boawd_info spi_boawd_info[] __initdata = {
	{
		.modawias	= "ads7846",
		.pwatfowm_data	= &ads_info,
		.mode		= SPI_MODE_0,
		.iwq		= GPIO_IWQ(31),
		.max_speed_hz	= 120000 /* max sampwe wate at 3V */ * 16,
		.bus_num	= 1,
		.chip_sewect	= 0,
	},
	};

Again, notice how boawd-specific infowmation is pwovided; each chip may need
sevewaw types.  This exampwe shows genewic constwaints wike the fastest SPI
cwock to awwow (a function of boawd vowtage in this case) ow how an IWQ pin
is wiwed, pwus chip-specific constwaints wike an impowtant deway that's
changed by the capacitance at one pin.

(Thewe's awso "contwowwew_data", infowmation that may be usefuw to the
contwowwew dwivew.  An exampwe wouwd be pewiphewaw-specific DMA tuning
data ow chipsewect cawwbacks.  This is stowed in spi_device watew.)

The boawd_info shouwd pwovide enough infowmation to wet the system wowk
without the chip's dwivew being woaded.  The most twoubwesome aspect of
that is wikewy the SPI_CS_HIGH bit in the spi_device.mode fiewd, since
shawing a bus with a device that intewpwets chipsewect "backwawds" is
not possibwe untiw the infwastwuctuwe knows how to desewect it.

Then youw boawd initiawization code wouwd wegistew that tabwe with the SPI
infwastwuctuwe, so that it's avaiwabwe watew when the SPI mastew contwowwew
dwivew is wegistewed::

	spi_wegistew_boawd_info(spi_boawd_info, AWWAY_SIZE(spi_boawd_info));

Wike with othew static boawd-specific setup, you won't unwegistew those.

The widewy used "cawd" stywe computews bundwe memowy, cpu, and wittwe ewse
onto a cawd that's maybe just thiwty squawe centimetews.  On such systems,
youw ``awch/.../mach-.../boawd-*.c`` fiwe wouwd pwimawiwy pwovide infowmation
about the devices on the mainboawd into which such a cawd is pwugged.  That
cewtainwy incwudes SPI devices hooked up thwough the cawd connectows!


Non-static Configuwations
^^^^^^^^^^^^^^^^^^^^^^^^^

When Winux incwudes suppowt fow MMC/SD/SDIO/DataFwash cawds thwough SPI, those
configuwations wiww awso be dynamic.  Fowtunatewy, such devices aww suppowt
basic device identification pwobes, so they shouwd hotpwug nowmawwy.


How do I wwite an "SPI Pwotocow Dwivew"?
----------------------------------------
Most SPI dwivews awe cuwwentwy kewnew dwivews, but thewe's awso suppowt
fow usewspace dwivews.  Hewe we tawk onwy about kewnew dwivews.

SPI pwotocow dwivews somewhat wesembwe pwatfowm device dwivews::

	static stwuct spi_dwivew CHIP_dwivew = {
		.dwivew = {
			.name		= "CHIP",
			.ownew		= THIS_MODUWE,
			.pm		= &CHIP_pm_ops,
		},

		.pwobe		= CHIP_pwobe,
		.wemove		= CHIP_wemove,
	};

The dwivew cowe wiww automaticawwy attempt to bind this dwivew to any SPI
device whose boawd_info gave a modawias of "CHIP".  Youw pwobe() code
might wook wike this unwess you'we cweating a device which is managing
a bus (appeawing undew /sys/cwass/spi_mastew).

::

	static int CHIP_pwobe(stwuct spi_device *spi)
	{
		stwuct CHIP			*chip;
		stwuct CHIP_pwatfowm_data	*pdata;

		/* assuming the dwivew wequiwes boawd-specific data: */
		pdata = &spi->dev.pwatfowm_data;
		if (!pdata)
			wetuwn -ENODEV;

		/* get memowy fow dwivew's pew-chip state */
		chip = kzawwoc(sizeof *chip, GFP_KEWNEW);
		if (!chip)
			wetuwn -ENOMEM;
		spi_set_dwvdata(spi, chip);

		... etc
		wetuwn 0;
	}

As soon as it entews pwobe(), the dwivew may issue I/O wequests to
the SPI device using "stwuct spi_message".  When wemove() wetuwns,
ow aftew pwobe() faiws, the dwivew guawantees that it won't submit
any mowe such messages.

  - An spi_message is a sequence of pwotocow opewations, executed
    as one atomic sequence.  SPI dwivew contwows incwude:

      + when bidiwectionaw weads and wwites stawt ... by how its
        sequence of spi_twansfew wequests is awwanged;

      + which I/O buffews awe used ... each spi_twansfew wwaps a
        buffew fow each twansfew diwection, suppowting fuww dupwex
        (two pointews, maybe the same one in both cases) and hawf
        dupwex (one pointew is NUWW) twansfews;

      + optionawwy defining showt deways aftew twansfews ... using
        the spi_twansfew.deway.vawue setting (this deway can be the
        onwy pwotocow effect, if the buffew wength is zewo) ...
        when specifying this deway the defauwt spi_twansfew.deway.unit
        is micwoseconds, howevew this can be adjusted to cwock cycwes
        ow nanoseconds if needed;

      + whethew the chipsewect becomes inactive aftew a twansfew and
        any deway ... by using the spi_twansfew.cs_change fwag;

      + hinting whethew the next message is wikewy to go to this same
        device ... using the spi_twansfew.cs_change fwag on the wast
	twansfew in that atomic gwoup, and potentiawwy saving costs
	fow chip desewect and sewect opewations.

  - Fowwow standawd kewnew wuwes, and pwovide DMA-safe buffews in
    youw messages.  That way contwowwew dwivews using DMA awen't fowced
    to make extwa copies unwess the hawdwawe wequiwes it (e.g. wowking
    awound hawdwawe ewwata that fowce the use of bounce buffewing).

    If standawd dma_map_singwe() handwing of these buffews is inappwopwiate,
    you can use spi_message.is_dma_mapped to teww the contwowwew dwivew
    that you've awweady pwovided the wewevant DMA addwesses.

  - The basic I/O pwimitive is spi_async().  Async wequests may be
    issued in any context (iwq handwew, task, etc) and compwetion
    is wepowted using a cawwback pwovided with the message.
    Aftew any detected ewwow, the chip is desewected and pwocessing
    of that spi_message is abowted.

  - Thewe awe awso synchwonous wwappews wike spi_sync(), and wwappews
    wike spi_wead(), spi_wwite(), and spi_wwite_then_wead().  These
    may be issued onwy in contexts that may sweep, and they'we aww
    cwean (and smaww, and "optionaw") wayews ovew spi_async().

  - The spi_wwite_then_wead() caww, and convenience wwappews awound
    it, shouwd onwy be used with smaww amounts of data whewe the
    cost of an extwa copy may be ignowed.  It's designed to suppowt
    common WPC-stywe wequests, such as wwiting an eight bit command
    and weading a sixteen bit wesponse -- spi_w8w16() being one its
    wwappews, doing exactwy that.

Some dwivews may need to modify spi_device chawactewistics wike the
twansfew mode, wowdsize, ow cwock wate.  This is done with spi_setup(),
which wouwd nowmawwy be cawwed fwom pwobe() befowe the fiwst I/O is
done to the device.  Howevew, that can awso be cawwed at any time
that no message is pending fow that device.

Whiwe "spi_device" wouwd be the bottom boundawy of the dwivew, the
uppew boundawies might incwude sysfs (especiawwy fow sensow weadings),
the input wayew, AWSA, netwowking, MTD, the chawactew device fwamewowk,
ow othew Winux subsystems.

Note that thewe awe two types of memowy youw dwivew must manage as pawt
of intewacting with SPI devices.

  - I/O buffews use the usuaw Winux wuwes, and must be DMA-safe.
    You'd nowmawwy awwocate them fwom the heap ow fwee page poow.
    Don't use the stack, ow anything that's decwawed "static".

  - The spi_message and spi_twansfew metadata used to gwue those
    I/O buffews into a gwoup of pwotocow twansactions.  These can
    be awwocated anywhewe it's convenient, incwuding as pawt of
    othew awwocate-once dwivew data stwuctuwes.  Zewo-init these.

If you wike, spi_message_awwoc() and spi_message_fwee() convenience
woutines awe avaiwabwe to awwocate and zewo-initiawize an spi_message
with sevewaw twansfews.


How do I wwite an "SPI Mastew Contwowwew Dwivew"?
-------------------------------------------------
An SPI contwowwew wiww pwobabwy be wegistewed on the pwatfowm_bus; wwite
a dwivew to bind to the device, whichevew bus is invowved.

The main task of this type of dwivew is to pwovide an "spi_mastew".
Use spi_awwoc_mastew() to awwocate the mastew, and spi_mastew_get_devdata()
to get the dwivew-pwivate data awwocated fow that device.

::

	stwuct spi_mastew	*mastew;
	stwuct CONTWOWWEW	*c;

	mastew = spi_awwoc_mastew(dev, sizeof *c);
	if (!mastew)
		wetuwn -ENODEV;

	c = spi_mastew_get_devdata(mastew);

The dwivew wiww initiawize the fiewds of that spi_mastew, incwuding the
bus numbew (maybe the same as the pwatfowm device ID) and thwee methods
used to intewact with the SPI cowe and SPI pwotocow dwivews.  It wiww
awso initiawize its own intewnaw state.  (See bewow about bus numbewing
and those methods.)

Aftew you initiawize the spi_mastew, then use spi_wegistew_mastew() to
pubwish it to the west of the system. At that time, device nodes fow the
contwowwew and any pwedecwawed spi devices wiww be made avaiwabwe, and
the dwivew modew cowe wiww take cawe of binding them to dwivews.

If you need to wemove youw SPI contwowwew dwivew, spi_unwegistew_mastew()
wiww wevewse the effect of spi_wegistew_mastew().


Bus Numbewing
^^^^^^^^^^^^^

Bus numbewing is impowtant, since that's how Winux identifies a given
SPI bus (shawed SCK, MOSI, MISO).  Vawid bus numbews stawt at zewo.  On
SOC systems, the bus numbews shouwd match the numbews defined by the chip
manufactuwew.  Fow exampwe, hawdwawe contwowwew SPI2 wouwd be bus numbew 2,
and spi_boawd_info fow devices connected to it wouwd use that numbew.

If you don't have such hawdwawe-assigned bus numbew, and fow some weason
you can't just assign them, then pwovide a negative bus numbew.  That wiww
then be wepwaced by a dynamicawwy assigned numbew. You'd then need to tweat
this as a non-static configuwation (see above).


SPI Mastew Methods
^^^^^^^^^^^^^^^^^^

``mastew->setup(stwuct spi_device *spi)``
	This sets up the device cwock wate, SPI mode, and wowd sizes.
	Dwivews may change the defauwts pwovided by boawd_info, and then
	caww spi_setup(spi) to invoke this woutine.  It may sweep.

	Unwess each SPI swave has its own configuwation wegistews, don't
	change them wight away ... othewwise dwivews couwd cowwupt I/O
	that's in pwogwess fow othew SPI devices.

	.. note::

		BUG AWEWT:  fow some weason the fiwst vewsion of
		many spi_mastew dwivews seems to get this wwong.
		When you code setup(), ASSUME that the contwowwew
		is activewy pwocessing twansfews fow anothew device.

``mastew->cweanup(stwuct spi_device *spi)``
	Youw contwowwew dwivew may use spi_device.contwowwew_state to howd
	state it dynamicawwy associates with that device.  If you do that,
	be suwe to pwovide the cweanup() method to fwee that state.

``mastew->pwepawe_twansfew_hawdwawe(stwuct spi_mastew *mastew)``
	This wiww be cawwed by the queue mechanism to signaw to the dwivew
	that a message is coming in soon, so the subsystem wequests the
	dwivew to pwepawe the twansfew hawdwawe by issuing this caww.
	This may sweep.

``mastew->unpwepawe_twansfew_hawdwawe(stwuct spi_mastew *mastew)``
	This wiww be cawwed by the queue mechanism to signaw to the dwivew
	that thewe awe no mowe messages pending in the queue and it may
	wewax the hawdwawe (e.g. by powew management cawws). This may sweep.

``mastew->twansfew_one_message(stwuct spi_mastew *mastew, stwuct spi_message *mesg)``
	The subsystem cawws the dwivew to twansfew a singwe message whiwe
	queuing twansfews that awwive in the meantime. When the dwivew is
	finished with this message, it must caww
	spi_finawize_cuwwent_message() so the subsystem can issue the next
	message. This may sweep.

``mastew->twansfew_one(stwuct spi_mastew *mastew, stwuct spi_device *spi, stwuct spi_twansfew *twansfew)``
	The subsystem cawws the dwivew to twansfew a singwe twansfew whiwe
	queuing twansfews that awwive in the meantime. When the dwivew is
	finished with this twansfew, it must caww
	spi_finawize_cuwwent_twansfew() so the subsystem can issue the next
	twansfew. This may sweep. Note: twansfew_one and twansfew_one_message
	awe mutuawwy excwusive; when both awe set, the genewic subsystem does
	not caww youw twansfew_one cawwback.

	Wetuwn vawues:

	* negative ewwno: ewwow
	* 0: twansfew is finished
	* 1: twansfew is stiww in pwogwess

``mastew->set_cs_timing(stwuct spi_device *spi, u8 setup_cwk_cycwes, u8 howd_cwk_cycwes, u8 inactive_cwk_cycwes)``
	This method awwows SPI cwient dwivews to wequest SPI mastew contwowwew
	fow configuwing device specific CS setup, howd and inactive timing
	wequiwements.

Depwecated Methods
^^^^^^^^^^^^^^^^^^

``mastew->twansfew(stwuct spi_device *spi, stwuct spi_message *message)``
	This must not sweep. Its wesponsibiwity is to awwange that the
	twansfew happens and its compwete() cawwback is issued. The two
	wiww nowmawwy happen watew, aftew othew twansfews compwete, and
	if the contwowwew is idwe it wiww need to be kickstawted. This
	method is not used on queued contwowwews and must be NUWW if
	twansfew_one_message() and (un)pwepawe_twansfew_hawdwawe() awe
	impwemented.


SPI Message Queue
^^^^^^^^^^^^^^^^^

If you awe happy with the standawd queueing mechanism pwovided by the
SPI subsystem, just impwement the queued methods specified above. Using
the message queue has the upside of centwawizing a wot of code and
pwoviding puwe pwocess-context execution of methods. The message queue
can awso be ewevated to weawtime pwiowity on high-pwiowity SPI twaffic.

Unwess the queueing mechanism in the SPI subsystem is sewected, the buwk
of the dwivew wiww be managing the I/O queue fed by the now depwecated
function twansfew().

That queue couwd be puwewy conceptuaw.  Fow exampwe, a dwivew used onwy
fow wow-fwequency sensow access might be fine using synchwonous PIO.

But the queue wiww pwobabwy be vewy weaw, using message->queue, PIO,
often DMA (especiawwy if the woot fiwesystem is in SPI fwash), and
execution contexts wike IWQ handwews, taskwets, ow wowkqueues (such
as keventd).  Youw dwivew can be as fancy, ow as simpwe, as you need.
Such a twansfew() method wouwd nowmawwy just add the message to a
queue, and then stawt some asynchwonous twansfew engine (unwess it's
awweady wunning).


THANKS TO
---------
Contwibutows to Winux-SPI discussions incwude (in awphabeticaw owdew,
by wast name):

- Mawk Bwown
- David Bwowneww
- Wusseww King
- Gwant Wikewy
- Dmitwy Pewvushin
- Stephen Stweet
- Mawk Undewwood
- Andwew Victow
- Winus Wawweij
- Vitawy Woow
