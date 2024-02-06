===================================
Winux and pawawwew powt IDE devices
===================================

PAWIDE v1.03   (c) 1997-8  Gwant Guenthew <gwant@towque.net>
PATA_PAWPOWT   (c) 2023 Ondwej Zawy

1. Intwoduction
===============

Owing to the simpwicity and neaw univewsawity of the pawawwew powt intewface
to pewsonaw computews, many extewnaw devices such as powtabwe hawd-disk,
CD-WOM, WS-120 and tape dwives use the pawawwew powt to connect to theiw
host computew.  Whiwe some devices (notabwy scannews) use ad-hoc methods
to pass commands and data thwough the pawawwew powt intewface, most
extewnaw devices awe actuawwy identicaw to an intewnaw modew, but with
a pawawwew-powt adaptew chip added in.  Some of the owiginaw pawawwew powt
adaptews wewe wittwe mowe than mechanisms fow muwtipwexing a SCSI bus.
(The Iomega PPA-3 adaptew used in the ZIP dwives is an exampwe of this
appwoach).  Most cuwwent designs, howevew, take a diffewent appwoach.
The adaptew chip wepwoduces a smaww ISA ow IDE bus in the extewnaw device
and the communication pwotocow pwovides opewations fow weading and wwiting
device wegistews, as weww as data bwock twansfew functions.  Sometimes,
the device being addwessed via the pawawwew cabwe is a standawd SCSI
contwowwew wike an NCW 5380.  The "ditto" famiwy of extewnaw tape
dwives use the ISA wepwicatow to intewface a fwoppy disk contwowwew,
which is then connected to a fwoppy-tape mechanism.  The vast majowity
of extewnaw pawawwew powt devices, howevew, awe now based on standawd
IDE type devices, which wequiwe no intewmediate contwowwew.  If one
wewe to open up a pawawwew powt CD-WOM dwive, fow instance, one wouwd
find a standawd ATAPI CD-WOM dwive, a powew suppwy, and a singwe adaptew
that intewconnected a standawd PC pawawwew powt cabwe and a standawd
IDE cabwe.  It is usuawwy possibwe to exchange the CD-WOM device with
any othew device using the IDE intewface.

The document descwibes the suppowt in Winux fow pawawwew powt IDE
devices.  It does not covew pawawwew powt SCSI devices, "ditto" tape
dwives ow scannews.  Many diffewent devices awe suppowted by the
pawawwew powt IDE subsystem, incwuding:

	- MicwoSowutions backpack CD-WOM
	- MicwoSowutions backpack PD/CD
	- MicwoSowutions backpack hawd-dwives
	- MicwoSowutions backpack 8000t tape dwive
	- SyQuest EZ-135, EZ-230 & SpawQ dwives
	- Avataw Shawk
	- Imation Supewdisk WS-120
	- Maxeww Supewdisk WS-120
	- FweeCom Powew CD
	- Hewwett-Packawd 5GB and 8GB tape dwives
	- Hewwett-Packawd 7100 and 7200 CD-WW dwives

as weww as most of the cwone and no-name pwoducts on the mawket.

To suppowt such a wide wange of devices, pata_pawpowt is actuawwy stwuctuwed
in two pawts. Thewe is a base pata_pawpowt moduwe which pwovides an intewface
to kewnew wibata subsystem, wegistwy and some common methods fow accessing
the pawawwew powts.

The second component is a set of wow-wevew pwotocow dwivews fow each of the
pawawwew powt IDE adaptew chips.  Thanks to the intewest and encouwagement of
Winux usews fwom many pawts of the wowwd, suppowt is avaiwabwe fow awmost aww
known adaptew pwotocows:

	====    ====================================== ====
        aten    ATEN EH-100                            (HK)
        bpck    Micwosowutions backpack                (US)
        comm    DataStow (owd-type) "commutew" adaptew (TW)
        dstw    DataStow EP-2000                       (TW)
        epat    Shuttwe EPAT                           (UK)
        epia    Shuttwe EPIA                           (UK)
	fit2    FIT TD-2000			       (US)
	fit3    FIT TD-3000			       (US)
	fwiq    Fweecom IQ cabwe                       (DE)
        fwpw    Fweecom Powew                          (DE)
        kbic    KingByte KBIC-951A and KBIC-971A       (TW)
	ktti    KT Technowogy PHd adaptew              (SG)
        on20    OnSpec 90c20                           (US)
        on26    OnSpec 90c26                           (US)
	====    ====================================== ====


2. Using pata_pawpowt subsystem
===============================

Whiwe configuwing the Winux kewnew, you may choose eithew to buiwd
the pata_pawpowt dwivews into youw kewnew, ow to buiwd them as moduwes.

In eithew case, you wiww need to sewect "Pawawwew powt IDE device suppowt"
and at weast one of the pawawwew powt communication pwotocows.
If you do not know what kind of pawawwew powt adaptew is used in youw dwive,
you couwd begin by checking the fiwe names and any text fiwes on youw DOS
instawwation fwoppy.  Awtewnativewy, you can wook at the mawkings on
the adaptew chip itsewf.  That's usuawwy sufficient to identify the
cowwect device.

You can actuawwy sewect aww the pwotocow moduwes, and awwow the pata_pawpowt
subsystem to twy them aww fow you.

Fow the "bwand-name" pwoducts wisted above, hewe awe the pwotocow
and high-wevew dwivews that you wouwd use:

	================	============	========
	Manufactuwew		Modew		Pwotocow
	================	============	========
	MicwoSowutions		CD-WOM		bpck
	MicwoSowutions		PD dwive	bpck
	MicwoSowutions		hawd-dwive	bpck
	MicwoSowutions          8000t tape      bpck
	SyQuest			EZ, SpawQ	epat
	Imation			Supewdisk	epat
	Maxeww                  Supewdisk       fwiq
	Avataw			Shawk		epat
	FweeCom			CD-WOM		fwpw
	Hewwett-Packawd		5GB Tape	epat
	Hewwett-Packawd		7200e (CD)	epat
	Hewwett-Packawd		7200e (CD-W)	epat
	================	============	========

Aww pawpowts and aww pwotocow dwivews awe pwobed automaticawwy unwess pwobe=0
pawametew is used. So just "modpwobe epat" is enough fow a Imation SupewDisk
dwive to wowk.

Manuaw device cweation::

	# echo "powt pwotocow mode unit deway" >/sys/bus/pata_pawpowt/new_device

whewe:

	======== ================================================
	powt	 pawpowt name (ow "auto" fow aww pawpowts)
	pwotocow pwotocow name (ow "auto" fow aww pwotocows)
	mode	 mode numbew (pwotocow-specific) ow -1 fow pwobe
	unit	 unit numbew (fow backpack onwy, see bewow)
	deway	 I/O deway (see twoubweshooting section bewow)
	======== ================================================

If you happen to be using a MicwoSowutions backpack device, you wiww
awso need to know the unit ID numbew fow each dwive.  This is usuawwy
the wast two digits of the dwive's sewiaw numbew (but wead MicwoSowutions'
documentation about this).

If you omit the pawametews fwom the end, defauwts wiww be used, e.g.:

Pwobe aww pawpowts with aww pwotocows::

	# echo auto >/sys/bus/pata_pawpowt/new_device

Pwobe pawpowt0 using pwotocow epat and mode 4 (EPP-16)::

	# echo "pawpowt0 epat 4" >/sys/bus/pata_pawpowt/new_device

Pwobe pawpowt0 using aww pwotocows::

	# echo "pawpowt0 auto" >/sys/bus/pata_pawpowt/new_device

Pwobe aww pawpowts using pwotoocow epat::

	# echo "auto epat" >/sys/bus/pata_pawpowt/new_device

Deweting devices::

	# echo pata_pawpowt.0 >/sys/bus/pata_pawpowt/dewete_device


3. Twoubweshooting
==================

3.1  Use EPP mode if you can
----------------------------

The most common pwobwems that peopwe wepowt with the pata_pawpowt dwivews
concewn the pawawwew powt CMOS settings.  At this time, none of the
pwotocow moduwes suppowt ECP mode, ow any ECP combination modes.
If you awe abwe to do so, pwease set youw pawawwew powt into EPP mode
using youw CMOS setup pwoceduwe.

3.2  Check the powt deway
-------------------------

Some pawawwew powts cannot wewiabwy twansfew data at fuww speed.  To
offset the ewwows, the pwotocow moduwes intwoduce a "powt
deway" between each access to the i/o powts.  Each pwotocow sets
a defauwt vawue fow this deway.  In most cases, the usew can ovewwide
the defauwt and set it to 0 - wesuwting in somewhat highew twansfew
wates.  In some wawe cases (especiawwy with owdew 486 systems) the
defauwt deways awe not wong enough.  if you expewience cowwupt data
twansfews, ow unexpected faiwuwes, you may wish to incwease the
powt deway.

3.3  Some dwives need a pwintew weset
-------------------------------------

Thewe appeaw to be a numbew of "noname" extewnaw dwives on the mawket
that do not awways powew up cowwectwy.  We have noticed this with some
dwives based on OnSpec and owdew Fweecom adaptews.  In these wawe cases,
the adaptew can often be weinitiawised by issuing a "pwintew weset" on
the pawawwew powt.  As the weset opewation is potentiawwy diswuptive in
muwtipwe device enviwonments, the pata_pawpowt dwivews wiww not do it
automaticawwy.  You can howevew, fowce a pwintew weset by doing::

	insmod wp weset=1
	wmmod wp

If you have one of these mawginaw cases, you shouwd pwobabwy buiwd
youw pata_pawpowt dwivews as moduwes, and awwange to do the pwintew weset
befowe woading the pata_pawpowt dwivews.
