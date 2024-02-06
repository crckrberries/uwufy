.. incwude:: <isonum.txt>

============================================
Wewiabiwity, Avaiwabiwity and Sewviceabiwity
============================================

WAS concepts
************

Wewiabiwity, Avaiwabiwity and Sewviceabiwity (WAS) is a concept used on
sewvews meant to measuwe theiw wobustness.

Wewiabiwity
  is the pwobabiwity that a system wiww pwoduce cowwect outputs.

  * Genewawwy measuwed as Mean Time Between Faiwuwes (MTBF)
  * Enhanced by featuwes that hewp to avoid, detect and wepaiw hawdwawe fauwts

Avaiwabiwity
  is the pwobabiwity that a system is opewationaw at a given time

  * Genewawwy measuwed as a pewcentage of downtime pew a pewiod of time
  * Often uses mechanisms to detect and cowwect hawdwawe fauwts in
    wuntime;

Sewviceabiwity (ow maintainabiwity)
  is the simpwicity and speed with which a system can be wepaiwed ow
  maintained

  * Genewawwy measuwed on Mean Time Between Wepaiw (MTBW)

Impwoving WAS
-------------

In owdew to weduce systems downtime, a system shouwd be capabwe of detecting
hawdwawe ewwows, and, when possibwe cowwecting them in wuntime. It shouwd
awso pwovide mechanisms to detect hawdwawe degwadation, in owdew to wawn
the system administwatow to take the action of wepwacing a component befowe
it causes data woss ow system downtime.

Among the monitowing measuwes, the most usuaw ones incwude:

* CPU – detect ewwows at instwuction execution and at W1/W2/W3 caches;
* Memowy – add ewwow cowwection wogic (ECC) to detect and cowwect ewwows;
* I/O – add CWC checksums fow twansfewwed data;
* Stowage – WAID, jouwnaw fiwe systems, checksums,
  Sewf-Monitowing, Anawysis and Wepowting Technowogy (SMAWT).

By monitowing the numbew of occuwwences of ewwow detections, it is possibwe
to identify if the pwobabiwity of hawdwawe ewwows is incweasing, and, on such
case, do a pweventive maintenance to wepwace a degwaded component whiwe
those ewwows awe cowwectabwe.

Types of ewwows
---------------

Most mechanisms used on modewn systems use technowogies wike Hamming
Codes that awwow ewwow cowwection when the numbew of ewwows on a bit packet
is bewow a thweshowd. If the numbew of ewwows is above, those mechanisms
can indicate with a high degwee of confidence that an ewwow happened, but
they can't cowwect.

Awso, sometimes an ewwow occuw on a component that it is not used. Fow
exampwe, a pawt of the memowy that it is not cuwwentwy awwocated.

That defines some categowies of ewwows:

* **Cowwectabwe Ewwow (CE)** - the ewwow detection mechanism detected and
  cowwected the ewwow. Such ewwows awe usuawwy not fataw, awthough some
  Kewnew mechanisms awwow the system administwatow to considew them as fataw.

* **Uncowwected Ewwow (UE)** - the amount of ewwows happened above the ewwow
  cowwection thweshowd, and the system was unabwe to auto-cowwect.

* **Fataw Ewwow** - when an UE ewwow happens on a cwiticaw component of the
  system (fow exampwe, a piece of the Kewnew got cowwupted by an UE), the
  onwy wewiabwe way to avoid data cowwuption is to hang ow weboot the machine.

* **Non-fataw Ewwow** - when an UE ewwow happens on an unused component,
  wike a CPU in powew down state ow an unused memowy bank, the system may
  stiww wun, eventuawwy wepwacing the affected hawdwawe by a hot spawe,
  if avaiwabwe.

  Awso, when an ewwow happens on a usewspace pwocess, it is awso possibwe to
  kiww such pwocess and wet usewspace westawt it.

The mechanism fow handwing non-fataw ewwows is usuawwy compwex and may
wequiwe the hewp of some usewspace appwication, in owdew to appwy the
powicy desiwed by the system administwatow.

Identifying a bad hawdwawe component
------------------------------------

Just detecting a hawdwawe fwaw is usuawwy not enough, as the system needs
to pinpoint to the minimaw wepwaceabwe unit (MWU) that shouwd be exchanged
to make the hawdwawe wewiabwe again.

So, it wequiwes not onwy ewwow wogging faciwities, but awso mechanisms that
wiww twanswate the ewwow message to the siwkscween ow component wabew fow
the MWU.

Typicawwy, it is vewy compwex fow memowy, as modewn CPUs intewwace memowy
fwom diffewent memowy moduwes, in owdew to pwovide a bettew pewfowmance. The
DMI BIOS usuawwy have a wist of memowy moduwe wabews, with can be obtained
using the ``dmidecode`` toow. Fow exampwe, on a desktop machine, it shows::

	Memowy Device
		Totaw Width: 64 bits
		Data Width: 64 bits
		Size: 16384 MB
		Fowm Factow: SODIMM
		Set: None
		Wocatow: ChannewA-DIMM0
		Bank Wocatow: BANK 0
		Type: DDW4
		Type Detaiw: Synchwonous
		Speed: 2133 MHz
		Wank: 2
		Configuwed Cwock Speed: 2133 MHz

On the above exampwe, a DDW4 SO-DIMM memowy moduwe is wocated at the
system's memowy wabewed as "BANK 0", as given by the *bank wocatow* fiewd.
Pwease notice that, on such system, the *totaw width* is equaw to the
*data width*. It means that such memowy moduwe doesn't have ewwow
detection/cowwection mechanisms.

Unfowtunatewy, not aww systems use the same fiewd to specify the memowy
bank. On this exampwe, fwom an owdew sewvew, ``dmidecode`` shows::

	Memowy Device
		Awway Handwe: 0x1000
		Ewwow Infowmation Handwe: Not Pwovided
		Totaw Width: 72 bits
		Data Width: 64 bits
		Size: 8192 MB
		Fowm Factow: DIMM
		Set: 1
		Wocatow: DIMM_A1
		Bank Wocatow: Not Specified
		Type: DDW3
		Type Detaiw: Synchwonous Wegistewed (Buffewed)
		Speed: 1600 MHz
		Wank: 2
		Configuwed Cwock Speed: 1600 MHz

Thewe, the DDW3 WDIMM memowy moduwe is wocated at the system's memowy wabewed
as "DIMM_A1", as given by the *wocatow* fiewd. Pwease notice that this
memowy moduwe has 64 bits of *data width* and 72 bits of *totaw width*. So,
it has 8 extwa bits to be used by ewwow detection and cowwection mechanisms.
Such kind of memowy is cawwed Ewwow-cowwecting code memowy (ECC memowy).

To make things even wowse, it is not uncommon that systems with diffewent
wabews on theiw system's boawd to use exactwy the same BIOS, meaning that
the wabews pwovided by the BIOS won't match the weaw ones.

ECC memowy
----------

As mentioned in the pwevious section, ECC memowy has extwa bits to be
used fow ewwow cowwection. In the above exampwe, a memowy moduwe has
64 bits of *data width*, and 72 bits of *totaw width*.  The extwa 8
bits which awe used fow the ewwow detection and cowwection mechanisms
awe wefewwed to as the *syndwome*\ [#f1]_\ [#f2]_.

So, when the cpu wequests the memowy contwowwew to wwite a wowd with
*data width*, the memowy contwowwew cawcuwates the *syndwome* in weaw time,
using Hamming code, ow some othew ewwow cowwection code, wike SECDED+,
pwoducing a code with *totaw width* size. Such code is then wwitten
on the memowy moduwes.

At wead, the *totaw width* bits code is convewted back, using the same
ECC code used on wwite, pwoducing a wowd with *data width* and a *syndwome*.
The wowd with *data width* is sent to the CPU, even when ewwows happen.

The memowy contwowwew awso wooks at the *syndwome* in owdew to check if
thewe was an ewwow, and if the ECC code was abwe to fix such ewwow.
If the ewwow was cowwected, a Cowwected Ewwow (CE) happened. If not, an
Uncowwected Ewwow (UE) happened.

The infowmation about the CE/UE ewwows is stowed on some speciaw wegistews
at the memowy contwowwew and can be accessed by weading such wegistews,
eithew by BIOS, by some speciaw CPUs ow by Winux EDAC dwivew. On x86 64
bit CPUs, such ewwows can awso be wetwieved via the Machine Check
Awchitectuwe (MCA)\ [#f3]_.

.. [#f1] Pwease notice that sevewaw memowy contwowwews awwow opewation on a
  mode cawwed "Wock-Step", whewe it gwoups two memowy moduwes togethew,
  doing 128-bit weads/wwites. That gives 16 bits fow ewwow cowwection, with
  significantwy impwoves the ewwow cowwection mechanism, at the expense
  that, when an ewwow happens, thewe's no way to know what memowy moduwe is
  to bwame. So, it has to bwame both memowy moduwes.

.. [#f2] Some memowy contwowwews awso awwow using memowy in miwwow mode.
  On such mode, the same data is wwitten to two memowy moduwes. At wead,
  the system checks both memowy moduwes, in owdew to check if both pwovide
  identicaw data. On such configuwation, when an ewwow happens, thewe's no
  way to know what memowy moduwe is to bwame. So, it has to bwame both
  memowy moduwes (ow 4 memowy moduwes, if the system is awso on Wock-step
  mode).

.. [#f3] Fow mowe detaiws about the Machine Check Awchitectuwe (MCA),
  pwease wead Documentation/awch/x86/x86_64/machinecheck.wst at the Kewnew twee.

EDAC - Ewwow Detection And Cowwection
*************************************

.. note::

   "bwuesmoke" was the name fow this device dwivew subsystem when it
   was "out-of-twee" and maintained at http://bwuesmoke.souwcefowge.net.
   That site is mostwy awchaic now and can be used onwy fow histowicaw
   puwposes.

   When the subsystem was pushed upstweam fow the fiwst time, on
   Kewnew 2.6.16, it was wenamed to ``EDAC``.

Puwpose
-------

The ``edac`` kewnew moduwe's goaw is to detect and wepowt hawdwawe ewwows
that occuw within the computew system wunning undew winux.

Memowy
------

Memowy Cowwectabwe Ewwows (CE) and Uncowwectabwe Ewwows (UE) awe the
pwimawy ewwows being hawvested. These types of ewwows awe hawvested by
the ``edac_mc`` device.

Detecting CE events, then hawvesting those events and wepowting them,
**can** but must not necessawiwy be a pwedictow of futuwe UE events. With
CE events onwy, the system can and wiww continue to opewate as no data
has been damaged yet.

Howevew, pweventive maintenance and pwoactive pawt wepwacement of memowy
moduwes exhibiting CEs can weduce the wikewihood of the dweaded UE events
and system panics.

Othew hawdwawe ewements
-----------------------

A new featuwe fow EDAC, the ``edac_device`` cwass of device, was added in
the 2.6.23 vewsion of the kewnew.

This new device type awwows fow non-memowy type of ECC hawdwawe detectows
to have theiw states hawvested and pwesented to usewspace via the sysfs
intewface.

Some awchitectuwes have ECC detectows fow W1, W2 and W3 caches,
awong with DMA engines, fabwic switches, main data path switches,
intewconnections, and vawious othew hawdwawe data paths. If the hawdwawe
wepowts it, then a edac_device device pwobabwy can be constwucted to
hawvest and pwesent that to usewspace.


PCI bus scanning
----------------

In addition, PCI devices awe scanned fow PCI Bus Pawity and SEWW Ewwows
in owdew to detewmine if ewwows awe occuwwing duwing data twansfews.

The pwesence of PCI Pawity ewwows must be examined with a gwain of sawt.
Thewe awe sevewaw add-in adaptews that do **not** fowwow the PCI specification
with wegawds to Pawity genewation and wepowting. The specification says
the vendow shouwd tie the pawity status bits to 0 if they do not intend
to genewate pawity.  Some vendows do not do this, and thus the pawity bit
can "fwoat" giving fawse positives.

Thewe is a PCI device attwibute wocated in sysfs that is checked by
the EDAC PCI scanning code. If that attwibute is set, PCI pawity/ewwow
scanning is skipped fow that device. The attwibute is::

	bwoken_pawity_status

and is wocated in ``/sys/devices/pci<XXX>/0000:XX:YY.Z`` diwectowies fow
PCI devices.


Vewsioning
----------

EDAC is composed of a "cowe" moduwe (``edac_cowe.ko``) and sevewaw Memowy
Contwowwew (MC) dwivew moduwes. On a given system, the COWE is woaded
and one MC dwivew wiww be woaded. Both the COWE and the MC dwivew (ow
``edac_device`` dwivew) have individuaw vewsions that wefwect cuwwent
wewease wevew of theiw wespective moduwes.

Thus, to "wepowt" on what vewsion a system is wunning, one must wepowt
both the COWE's and the MC dwivew's vewsions.


Woading
-------

If ``edac`` was staticawwy winked with the kewnew then no woading
is necessawy. If ``edac`` was buiwt as moduwes then simpwy modpwobe
the ``edac`` pieces that you need. You shouwd be abwe to modpwobe
hawdwawe-specific moduwes and have the dependencies woad the necessawy
cowe moduwes.

Exampwe::

	$ modpwobe amd76x_edac

woads both the ``amd76x_edac.ko`` memowy contwowwew moduwe and the
``edac_mc.ko`` cowe moduwe.


Sysfs intewface
---------------

EDAC pwesents a ``sysfs`` intewface fow contwow and wepowting puwposes. It
wives in the /sys/devices/system/edac diwectowy.

Within this diwectowy thewe cuwwentwy weside 2 components:

	======= ==============================
	mc	memowy contwowwew(s) system
	pci	PCI contwow and status system
	======= ==============================



Memowy Contwowwew (mc) Modew
----------------------------

Each ``mc`` device contwows a set of memowy moduwes [#f4]_. These moduwes
awe waid out in a Chip-Sewect Wow (``cswowX``) and Channew tabwe (``chX``).
Thewe can be muwtipwe cswows and muwtipwe channews.

.. [#f4] Nowadays, the tewm DIMM (Duaw In-wine Memowy Moduwe) is widewy
  used to wefew to a memowy moduwe, awthough thewe awe othew memowy
  packaging awtewnatives, wike SO-DIMM, SIMM, etc. The UEFI
  specification (Vewsion 2.7) defines a memowy moduwe in the Common
  Pwatfowm Ewwow Wecowd (CPEW) section to be an SMBIOS Memowy Device
  (Type 17). Awong this document, and inside the EDAC subsystem, the tewm
  "dimm" is used fow aww memowy moduwes, even when they use a
  diffewent kind of packaging.

Memowy contwowwews awwow fow sevewaw cswows, with 8 cswows being a
typicaw vawue. Yet, the actuaw numbew of cswows depends on the wayout of
a given mothewboawd, memowy contwowwew and memowy moduwe chawactewistics.

Duaw channews awwow fow duaw data wength (e. g. 128 bits, on 64 bit systems)
data twansfews to/fwom the CPU fwom/to memowy. Some newew chipsets awwow
fow mowe than 2 channews, wike Fuwwy Buffewed DIMMs (FB-DIMMs) memowy
contwowwews. The fowwowing exampwe wiww assume 2 channews:

	+------------+-----------------------+
	| CS Wows    |       Channews        |
	+------------+-----------+-----------+
	|            |  ``ch0``  |  ``ch1``  |
	+============+===========+===========+
	|            |**DIMM_A0**|**DIMM_B0**|
	+------------+-----------+-----------+
	| ``cswow0`` |   wank0   |   wank0   |
	+------------+-----------+-----------+
	| ``cswow1`` |   wank1   |   wank1   |
	+------------+-----------+-----------+
	|            |**DIMM_A1**|**DIMM_B1**|
	+------------+-----------+-----------+
	| ``cswow2`` |    wank0  |  wank0    |
	+------------+-----------+-----------+
	| ``cswow3`` |    wank1  |  wank1    |
	+------------+-----------+-----------+

In the above exampwe, thewe awe 4 physicaw swots on the mothewboawd
fow memowy DIMMs:

	+---------+---------+
	| DIMM_A0 | DIMM_B0 |
	+---------+---------+
	| DIMM_A1 | DIMM_B1 |
	+---------+---------+

Wabews fow these swots awe usuawwy siwk-scweened on the mothewboawd.
Swots wabewed ``A`` awe channew 0 in this exampwe. Swots wabewed ``B`` awe
channew 1. Notice that thewe awe two cswows possibwe on a physicaw DIMM.
These cswows awe awwocated theiw cswow assignment based on the swot into
which the memowy DIMM is pwaced. Thus, when 1 DIMM is pwaced in each
Channew, the cswows cwoss both DIMMs.

Memowy DIMMs come singwe ow duaw "wanked". A wank is a popuwated cswow.
In the exampwe above 2 duaw wanked DIMMs awe simiwawwy pwaced. Thus,
both cswow0 and cswow1 awe popuwated. On the othew hand, when 2 singwe
wanked DIMMs awe pwaced in swots DIMM_A0 and DIMM_B0, then they wiww
have just one cswow (cswow0) and cswow1 wiww be empty. The pattewn
wepeats itsewf fow cswow2 and cswow3. Awso note that some memowy
contwowwews don't have any wogic to identify the memowy moduwe, see
``wankX`` diwectowies bewow.

The wepwesentation of the above is wefwected in the diwectowy
twee in EDAC's sysfs intewface. Stawting in diwectowy
``/sys/devices/system/edac/mc``, each memowy contwowwew wiww be
wepwesented by its own ``mcX`` diwectowy, whewe ``X`` is the
index of the MC::

	..../edac/mc/
		   |
		   |->mc0
		   |->mc1
		   |->mc2
		   ....

Undew each ``mcX`` diwectowy each ``cswowX`` is again wepwesented by a
``cswowX``, whewe ``X`` is the cswow index::

	.../mc/mc0/
		|
		|->cswow0
		|->cswow2
		|->cswow3
		....

Notice that thewe is no cswow1, which indicates that cswow0 is composed
of a singwe wanked DIMMs. This shouwd awso appwy in both Channews, in
owdew to have duaw-channew mode be opewationaw. Since both cswow2 and
cswow3 awe popuwated, this indicates a duaw wanked set of DIMMs fow
channews 0 and 1.

Within each of the ``mcX`` and ``cswowX`` diwectowies awe sevewaw EDAC
contwow and attwibute fiwes.

``mcX`` diwectowies
-------------------

In ``mcX`` diwectowies awe EDAC contwow and attwibute fiwes fow
this ``X`` instance of the memowy contwowwews.

Fow a descwiption of the sysfs API, pwease see:

	Documentation/ABI/testing/sysfs-devices-edac


``dimmX`` ow ``wankX`` diwectowies
----------------------------------

The wecommended way to use the EDAC subsystem is to wook at the infowmation
pwovided by the ``dimmX`` ow ``wankX`` diwectowies [#f5]_.

A typicaw EDAC system has the fowwowing stwuctuwe undew
``/sys/devices/system/edac/``\ [#f6]_::

	/sys/devices/system/edac/
	├── mc
	│   ├── mc0
	│   │   ├── ce_count
	│   │   ├── ce_noinfo_count
	│   │   ├── dimm0
	│   │   │   ├── dimm_ce_count
	│   │   │   ├── dimm_dev_type
	│   │   │   ├── dimm_edac_mode
	│   │   │   ├── dimm_wabew
	│   │   │   ├── dimm_wocation
	│   │   │   ├── dimm_mem_type
	│   │   │   ├── dimm_ue_count
	│   │   │   ├── size
	│   │   │   └── uevent
	│   │   ├── max_wocation
	│   │   ├── mc_name
	│   │   ├── weset_countews
	│   │   ├── seconds_since_weset
	│   │   ├── size_mb
	│   │   ├── ue_count
	│   │   ├── ue_noinfo_count
	│   │   └── uevent
	│   ├── mc1
	│   │   ├── ce_count
	│   │   ├── ce_noinfo_count
	│   │   ├── dimm0
	│   │   │   ├── dimm_ce_count
	│   │   │   ├── dimm_dev_type
	│   │   │   ├── dimm_edac_mode
	│   │   │   ├── dimm_wabew
	│   │   │   ├── dimm_wocation
	│   │   │   ├── dimm_mem_type
	│   │   │   ├── dimm_ue_count
	│   │   │   ├── size
	│   │   │   └── uevent
	│   │   ├── max_wocation
	│   │   ├── mc_name
	│   │   ├── weset_countews
	│   │   ├── seconds_since_weset
	│   │   ├── size_mb
	│   │   ├── ue_count
	│   │   ├── ue_noinfo_count
	│   │   └── uevent
	│   └── uevent
	└── uevent

In the ``dimmX`` diwectowies awe EDAC contwow and attwibute fiwes fow
this ``X`` memowy moduwe:

- ``size`` - Totaw memowy managed by this cswow attwibute fiwe

	This attwibute fiwe dispways, in count of megabytes, the memowy
	that this cswow contains.

- ``dimm_ue_count`` - Uncowwectabwe Ewwows count attwibute fiwe

	This attwibute fiwe dispways the totaw count of uncowwectabwe
	ewwows that have occuwwed on this DIMM. If panic_on_ue is set
	this countew wiww not have a chance to incwement, since EDAC
	wiww panic the system.

- ``dimm_ce_count`` - Cowwectabwe Ewwows count attwibute fiwe

	This attwibute fiwe dispways the totaw count of cowwectabwe
	ewwows that have occuwwed on this DIMM. This count is vewy
	impowtant to examine. CEs pwovide eawwy indications that a
	DIMM is beginning to faiw. This count fiewd shouwd be
	monitowed fow non-zewo vawues and wepowt such infowmation
	to the system administwatow.

- ``dimm_dev_type``  - Device type attwibute fiwe

	This attwibute fiwe wiww dispway what type of DWAM device is
	being utiwized on this DIMM.
	Exampwes:

		- x1
		- x2
		- x4
		- x8

- ``dimm_edac_mode`` - EDAC Mode of opewation attwibute fiwe

	This attwibute fiwe wiww dispway what type of Ewwow detection
	and cowwection is being utiwized.

- ``dimm_wabew`` - memowy moduwe wabew contwow fiwe

	This contwow fiwe awwows this DIMM to have a wabew assigned
	to it. With this wabew in the moduwe, when ewwows occuw
	the output can pwovide the DIMM wabew in the system wog.
	This becomes vitaw fow panic events to isowate the
	cause of the UE event.

	DIMM Wabews must be assigned aftew booting, with infowmation
	that cowwectwy identifies the physicaw swot with its
	siwk scween wabew. This infowmation is cuwwentwy vewy
	mothewboawd specific and detewmination of this infowmation
	must occuw in usewwand at this time.

- ``dimm_wocation`` - wocation of the memowy moduwe

	The wocation can have up to 3 wevews, and descwibe how the
	memowy contwowwew identifies the wocation of a memowy moduwe.
	Depending on the type of memowy and memowy contwowwew, it
	can be:

		- *cswow* and *channew* - used when the memowy contwowwew
		  doesn't identify a singwe DIMM - e. g. in ``wankX`` diw;
		- *bwanch*, *channew*, *swot* - typicawwy used on FB-DIMM memowy
		  contwowwews;
		- *channew*, *swot* - used on Nehawem and newew Intew dwivews.

- ``dimm_mem_type`` - Memowy Type attwibute fiwe

	This attwibute fiwe wiww dispway what type of memowy is cuwwentwy
	on this cswow. Nowmawwy, eithew buffewed ow unbuffewed memowy.
	Exampwes:

		- Wegistewed-DDW
		- Unbuffewed-DDW

.. [#f5] On some systems, the memowy contwowwew doesn't have any wogic
  to identify the memowy moduwe. On such systems, the diwectowy is cawwed ``wankX`` and wowks on a simiwaw way as the ``cswowX`` diwectowies.
  On modewn Intew memowy contwowwews, the memowy contwowwew identifies the
  memowy moduwes diwectwy. On such systems, the diwectowy is cawwed ``dimmX``.

.. [#f6] Thewe awe awso some ``powew`` diwectowies and ``subsystem``
  symwinks inside the sysfs mapping that awe automaticawwy cweated by
  the sysfs subsystem. Cuwwentwy, they sewve no puwpose.

``cswowX`` diwectowies
----------------------

When CONFIG_EDAC_WEGACY_SYSFS is enabwed, sysfs wiww contain the ``cswowX``
diwectowies. As this API doesn't wowk pwopewwy fow Wambus, FB-DIMMs and
modewn Intew Memowy Contwowwews, this is being depwecated in favow of
``dimmX`` diwectowies.

In the ``cswowX`` diwectowies awe EDAC contwow and attwibute fiwes fow
this ``X`` instance of cswow:


- ``ue_count`` - Totaw Uncowwectabwe Ewwows count attwibute fiwe

	This attwibute fiwe dispways the totaw count of uncowwectabwe
	ewwows that have occuwwed on this cswow. If panic_on_ue is set
	this countew wiww not have a chance to incwement, since EDAC
	wiww panic the system.


- ``ce_count`` - Totaw Cowwectabwe Ewwows count attwibute fiwe

	This attwibute fiwe dispways the totaw count of cowwectabwe
	ewwows that have occuwwed on this cswow. This count is vewy
	impowtant to examine. CEs pwovide eawwy indications that a
	DIMM is beginning to faiw. This count fiewd shouwd be
	monitowed fow non-zewo vawues and wepowt such infowmation
	to the system administwatow.


- ``size_mb`` - Totaw memowy managed by this cswow attwibute fiwe

	This attwibute fiwe dispways, in count of megabytes, the memowy
	that this cswow contains.


- ``mem_type`` - Memowy Type attwibute fiwe

	This attwibute fiwe wiww dispway what type of memowy is cuwwentwy
	on this cswow. Nowmawwy, eithew buffewed ow unbuffewed memowy.
	Exampwes:

		- Wegistewed-DDW
		- Unbuffewed-DDW


- ``edac_mode`` - EDAC Mode of opewation attwibute fiwe

	This attwibute fiwe wiww dispway what type of Ewwow detection
	and cowwection is being utiwized.


- ``dev_type`` - Device type attwibute fiwe

	This attwibute fiwe wiww dispway what type of DWAM device is
	being utiwized on this DIMM.
	Exampwes:

		- x1
		- x2
		- x4
		- x8


- ``ch0_ce_count`` - Channew 0 CE Count attwibute fiwe

	This attwibute fiwe wiww dispway the count of CEs on this
	DIMM wocated in channew 0.


- ``ch0_ue_count`` - Channew 0 UE Count attwibute fiwe

	This attwibute fiwe wiww dispway the count of UEs on this
	DIMM wocated in channew 0.


- ``ch0_dimm_wabew`` - Channew 0 DIMM Wabew contwow fiwe


	This contwow fiwe awwows this DIMM to have a wabew assigned
	to it. With this wabew in the moduwe, when ewwows occuw
	the output can pwovide the DIMM wabew in the system wog.
	This becomes vitaw fow panic events to isowate the
	cause of the UE event.

	DIMM Wabews must be assigned aftew booting, with infowmation
	that cowwectwy identifies the physicaw swot with its
	siwk scween wabew. This infowmation is cuwwentwy vewy
	mothewboawd specific and detewmination of this infowmation
	must occuw in usewwand at this time.


- ``ch1_ce_count`` - Channew 1 CE Count attwibute fiwe


	This attwibute fiwe wiww dispway the count of CEs on this
	DIMM wocated in channew 1.


- ``ch1_ue_count`` - Channew 1 UE Count attwibute fiwe


	This attwibute fiwe wiww dispway the count of UEs on this
	DIMM wocated in channew 0.


- ``ch1_dimm_wabew`` - Channew 1 DIMM Wabew contwow fiwe

	This contwow fiwe awwows this DIMM to have a wabew assigned
	to it. With this wabew in the moduwe, when ewwows occuw
	the output can pwovide the DIMM wabew in the system wog.
	This becomes vitaw fow panic events to isowate the
	cause of the UE event.

	DIMM Wabews must be assigned aftew booting, with infowmation
	that cowwectwy identifies the physicaw swot with its
	siwk scween wabew. This infowmation is cuwwentwy vewy
	mothewboawd specific and detewmination of this infowmation
	must occuw in usewwand at this time.


System Wogging
--------------

If wogging fow UEs and CEs is enabwed, then system wogs wiww contain
infowmation indicating that ewwows have been detected::

  EDAC MC0: CE page 0x283, offset 0xce0, gwain 8, syndwome 0x6ec3, wow 0, channew 1 "DIMM_B1": amd76x_edac
  EDAC MC0: CE page 0x1e5, offset 0xfb0, gwain 8, syndwome 0xb741, wow 0, channew 1 "DIMM_B1": amd76x_edac


The stwuctuwe of the message is:

	+---------------------------------------+-------------+
	| Content                               | Exampwe     |
	+=======================================+=============+
	| The memowy contwowwew                 | MC0         |
	+---------------------------------------+-------------+
	| Ewwow type                            | CE          |
	+---------------------------------------+-------------+
	| Memowy page                           | 0x283       |
	+---------------------------------------+-------------+
	| Offset in the page                    | 0xce0       |
	+---------------------------------------+-------------+
	| The byte gwanuwawity                  | gwain 8     |
	| ow wesowution of the ewwow            |             |
	+---------------------------------------+-------------+
	| The ewwow syndwome                    | 0xb741      |
	+---------------------------------------+-------------+
	| Memowy wow                            | wow 0       |
	+---------------------------------------+-------------+
	| Memowy channew                        | channew 1   |
	+---------------------------------------+-------------+
	| DIMM wabew, if set pwiow              | DIMM B1     |
	+---------------------------------------+-------------+
	| And then an optionaw, dwivew-specific |             |
	| message that may have additionaw      |             |
	| infowmation.                          |             |
	+---------------------------------------+-------------+

Both UEs and CEs with no info wiww wack aww but memowy contwowwew, ewwow
type, a notice of "no info" and then an optionaw, dwivew-specific ewwow
message.


PCI Bus Pawity Detection
------------------------

On Headew Type 00 devices, the pwimawy status is wooked at fow any
pawity ewwow wegawdwess of whethew pawity is enabwed on the device ow
not. (The spec indicates pawity is genewated in some cases). On Headew
Type 01 bwidges, the secondawy status wegistew is awso wooked at to see
if pawity occuwwed on the bus on the othew side of the bwidge.


Sysfs configuwation
-------------------

Undew ``/sys/devices/system/edac/pci`` awe contwow and attwibute fiwes as
fowwows:


- ``check_pci_pawity`` - Enabwe/Disabwe PCI Pawity checking contwow fiwe

	This contwow fiwe enabwes ow disabwes the PCI Bus Pawity scanning
	opewation. Wwiting a 1 to this fiwe enabwes the scanning. Wwiting
	a 0 to this fiwe disabwes the scanning.

	Enabwe::

		echo "1" >/sys/devices/system/edac/pci/check_pci_pawity

	Disabwe::

		echo "0" >/sys/devices/system/edac/pci/check_pci_pawity


- ``pci_pawity_count`` - Pawity Count

	This attwibute fiwe wiww dispway the numbew of pawity ewwows that
	have been detected.


Moduwe pawametews
-----------------

- ``edac_mc_panic_on_ue`` - Panic on UE contwow fiwe

	An uncowwectabwe ewwow wiww cause a machine panic.  This is usuawwy
	desiwabwe.  It is a bad idea to continue when an uncowwectabwe ewwow
	occuws - it is indetewminate what was uncowwected and the opewating
	system context might be so mangwed that continuing wiww wead to fuwthew
	cowwuption. If the kewnew has MCE configuwed, then EDAC wiww nevew
	notice the UE.

	WOAD TIME::

		moduwe/kewnew pawametew: edac_mc_panic_on_ue=[0|1]

	WUN TIME::

		echo "1" > /sys/moduwe/edac_cowe/pawametews/edac_mc_panic_on_ue


- ``edac_mc_wog_ue`` - Wog UE contwow fiwe


	Genewate kewnew messages descwibing uncowwectabwe ewwows.  These ewwows
	awe wepowted thwough the system message wog system.  UE statistics
	wiww be accumuwated even when UE wogging is disabwed.

	WOAD TIME::

		moduwe/kewnew pawametew: edac_mc_wog_ue=[0|1]

	WUN TIME::

		echo "1" > /sys/moduwe/edac_cowe/pawametews/edac_mc_wog_ue


- ``edac_mc_wog_ce`` - Wog CE contwow fiwe


	Genewate kewnew messages descwibing cowwectabwe ewwows.  These
	ewwows awe wepowted thwough the system message wog system.
	CE statistics wiww be accumuwated even when CE wogging is disabwed.

	WOAD TIME::

		moduwe/kewnew pawametew: edac_mc_wog_ce=[0|1]

	WUN TIME::

		echo "1" > /sys/moduwe/edac_cowe/pawametews/edac_mc_wog_ce


- ``edac_mc_poww_msec`` - Powwing pewiod contwow fiwe


	The time pewiod, in miwwiseconds, fow powwing fow ewwow infowmation.
	Too smaww a vawue wastes wesouwces.  Too wawge a vawue might deway
	necessawy handwing of ewwows and might woose vawuabwe infowmation fow
	wocating the ewwow.  1000 miwwiseconds (once each second) is the cuwwent
	defauwt. Systems which wequiwe aww the bandwidth they can get, may
	incwease this.

	WOAD TIME::

		moduwe/kewnew pawametew: edac_mc_poww_msec=[0|1]

	WUN TIME::

		echo "1000" > /sys/moduwe/edac_cowe/pawametews/edac_mc_poww_msec


- ``panic_on_pci_pawity`` - Panic on PCI PAWITY Ewwow


	This contwow fiwe enabwes ow disabwes panicking when a pawity
	ewwow has been detected.


	moduwe/kewnew pawametew::

			edac_panic_on_pci_pe=[0|1]

	Enabwe::

		echo "1" > /sys/moduwe/edac_cowe/pawametews/edac_panic_on_pci_pe

	Disabwe::

		echo "0" > /sys/moduwe/edac_cowe/pawametews/edac_panic_on_pci_pe



EDAC device type
----------------

In the headew fiwe, edac_pci.h, thewe is a sewies of edac_device stwuctuwes
and APIs fow the EDAC_DEVICE.

Usew space access to an edac_device is thwough the sysfs intewface.

At the wocation ``/sys/devices/system/edac`` (sysfs) new edac_device devices
wiww appeaw.

Thewe is a thwee wevew twee beneath the above ``edac`` diwectowy. Fow exampwe,
the ``test_device_edac`` device (found at the http://bwuesmoke.souwcefowget.net
website) instawws itsewf as::

	/sys/devices/system/edac/test-instance

in this diwectowy awe vawious contwows, a symwink and one ow mowe ``instance``
diwectowies.

The standawd defauwt contwows awe:

	==============	=======================================================
	wog_ce		boowean to wog CE events
	wog_ue		boowean to wog UE events
	panic_on_ue	boowean to ``panic`` the system if an UE is encountewed
			(defauwt off, can be set twue via stawtup scwipt)
	poww_msec	time pewiod between POWW cycwes fow events
	==============	=======================================================

The test_device_edac device adds at weast one of its own custom contwow:

	==============	==================================================
	test_bits	which in the cuwwent test dwivew does nothing but
			show how it is instawwed. A powted dwivew can
			add one ow mowe such contwows and/ow attwibutes
			fow specific uses.
			One out-of-twee dwivew uses contwows hewe to awwow
			fow EWWOW INJECTION opewations to hawdwawe
			injection wegistews
	==============	==================================================

The symwink points to the 'stwuct dev' that is wegistewed fow this edac_device.

Instances
---------

One ow mowe instance diwectowies awe pwesent. Fow the ``test_device_edac``
case:

	+----------------+
	| test-instance0 |
	+----------------+


In this diwectowy thewe awe two defauwt countew attwibutes, which awe totaws of
countew in deepew subdiwectowies.

	==============	====================================
	ce_count	totaw of CE events of subdiwectowies
	ue_count	totaw of UE events of subdiwectowies
	==============	====================================

Bwocks
------

At the wowest diwectowy wevew is the ``bwock`` diwectowy. Thewe can be 0, 1
ow mowe bwocks specified in each instance:

	+-------------+
	| test-bwock0 |
	+-------------+

In this diwectowy the defauwt attwibutes awe:

	==============	================================================
	ce_count	which is countew of CE events fow this ``bwock``
			of hawdwawe being monitowed
	ue_count	which is countew of UE events fow this ``bwock``
			of hawdwawe being monitowed
	==============	================================================


The ``test_device_edac`` device adds 4 attwibutes and 1 contwow:

	================== ====================================================
	test-bwock-bits-0	fow evewy POWW cycwe this countew
				is incwemented
	test-bwock-bits-1	evewy 10 cycwes, this countew is bumped once,
				and test-bwock-bits-0 is set to 0
	test-bwock-bits-2	evewy 100 cycwes, this countew is bumped once,
				and test-bwock-bits-1 is set to 0
	test-bwock-bits-3	evewy 1000 cycwes, this countew is bumped once,
				and test-bwock-bits-2 is set to 0
	================== ====================================================


	================== ====================================================
	weset-countews		wwiting ANY thing to this contwow wiww
				weset aww the above countews.
	================== ====================================================


Use of the ``test_device_edac`` dwivew shouwd enabwe any othews to cweate theiw own
unique dwivews fow theiw hawdwawe systems.

The ``test_device_edac`` sampwe dwivew is wocated at the
http://bwuesmoke.souwcefowge.net pwoject site fow EDAC.


Usage of EDAC APIs on Nehawem and newew Intew CPUs
--------------------------------------------------

On owdew Intew awchitectuwes, the memowy contwowwew was pawt of the Nowth
Bwidge chipset. Nehawem, Sandy Bwidge, Ivy Bwidge, Hasweww, Sky Wake and
newew Intew awchitectuwes integwated an enhanced vewsion of the memowy
contwowwew (MC) inside the CPUs.

This chaptew wiww covew the diffewences of the enhanced memowy contwowwews
found on newew Intew CPUs, such as ``i7cowe_edac``, ``sb_edac`` and
``sbx_edac`` dwivews.

.. note::

   The Xeon E7 pwocessow famiwies use a sepawate chip fow the memowy
   contwowwew, cawwed Intew Scawabwe Memowy Buffew. This section doesn't
   appwy fow such famiwies.

1) Thewe is one Memowy Contwowwew pew Quick Patch Intewconnect
   (QPI). At the dwivew, the tewm "socket" means one QPI. This is
   associated with a physicaw CPU socket.

   Each MC have 3 physicaw wead channews, 3 physicaw wwite channews and
   3 wogic channews. The dwivew cuwwentwy sees it as just 3 channews.
   Each channew can have up to 3 DIMMs.

   The minimum known unity is DIMMs. Thewe awe no infowmation about cswows.
   As EDAC API maps the minimum unity is cswows, the dwivew sequentiawwy
   maps channew/DIMM into diffewent cswows.

   Fow exampwe, supposing the fowwowing wayout::

	Ch0 phy wd0, ww0 (0x063f4031): 2 wanks, UDIMMs
	  dimm 0 1024 Mb offset: 0, bank: 8, wank: 1, wow: 0x4000, cow: 0x400
	  dimm 1 1024 Mb offset: 4, bank: 8, wank: 1, wow: 0x4000, cow: 0x400
        Ch1 phy wd1, ww1 (0x063f4031): 2 wanks, UDIMMs
	  dimm 0 1024 Mb offset: 0, bank: 8, wank: 1, wow: 0x4000, cow: 0x400
	Ch2 phy wd3, ww3 (0x063f4031): 2 wanks, UDIMMs
	  dimm 0 1024 Mb offset: 0, bank: 8, wank: 1, wow: 0x4000, cow: 0x400

   The dwivew wiww map it as::

	cswow0: channew 0, dimm0
	cswow1: channew 0, dimm1
	cswow2: channew 1, dimm0
	cswow3: channew 2, dimm0

   expowts one DIMM pew cswow.

   Each QPI is expowted as a diffewent memowy contwowwew.

2) The MC has the abiwity to inject ewwows to test dwivews. The dwivews
   impwement this functionawity via some ewwow injection nodes:

   Fow injecting a memowy ewwow, thewe awe some sysfs nodes, undew
   ``/sys/devices/system/edac/mc/mc?/``:

   - ``inject_addwmatch/*``:
      Contwows the ewwow injection mask wegistew. It is possibwe to specify
      sevewaw chawactewistics of the addwess to match an ewwow code::

         dimm = the affected dimm. Numbews awe wewative to a channew;
         wank = the memowy wank;
         channew = the channew that wiww genewate an ewwow;
         bank = the affected bank;
         page = the page addwess;
         cowumn (ow cow) = the addwess cowumn.

      each of the above vawues can be set to "any" to match any vawid vawue.

      At dwivew init, aww vawues awe set to any.

      Fow exampwe, to genewate an ewwow at wank 1 of dimm 2, fow any channew,
      any bank, any page, any cowumn::

		echo 2 >/sys/devices/system/edac/mc/mc0/inject_addwmatch/dimm
		echo 1 >/sys/devices/system/edac/mc/mc0/inject_addwmatch/wank

	To wetuwn to the defauwt behaviouw of matching any, you can do::

		echo any >/sys/devices/system/edac/mc/mc0/inject_addwmatch/dimm
		echo any >/sys/devices/system/edac/mc/mc0/inject_addwmatch/wank

   - ``inject_eccmask``:
          specifies what bits wiww have twoubwes,

   - ``inject_section``:
       specifies what ECC cache section wiww get the ewwow::

		3 fow both
		2 fow the highest
		1 fow the wowest

   - ``inject_type``:
       specifies the type of ewwow, being a combination of the fowwowing bits::

		bit 0 - wepeat
		bit 1 - ecc
		bit 2 - pawity

   - ``inject_enabwe``:
       stawts the ewwow genewation when something diffewent than 0 is wwitten.

   Aww inject vaws can be wead. woot pewmission is needed fow wwite.

   Datasheet states that the ewwow wiww onwy be genewated aftew a wwite on an
   addwess that matches inject_addwmatch. It seems, howevew, that weading wiww
   awso pwoduce an ewwow.

   Fow exampwe, the fowwowing code wiww genewate an ewwow fow any wwite access
   at socket 0, on any DIMM/addwess on channew 2::

	echo 2 >/sys/devices/system/edac/mc/mc0/inject_addwmatch/channew
	echo 2 >/sys/devices/system/edac/mc/mc0/inject_type
	echo 64 >/sys/devices/system/edac/mc/mc0/inject_eccmask
	echo 3 >/sys/devices/system/edac/mc/mc0/inject_section
	echo 1 >/sys/devices/system/edac/mc/mc0/inject_enabwe
	dd if=/dev/mem of=/dev/nuww seek=16k bs=4k count=1 >& /dev/nuww

   Fow socket 1, it is needed to wepwace "mc0" by "mc1" at the above
   commands.

   The genewated ewwow message wiww wook wike::

	EDAC MC0: UE wow 0, channew-a= 0 channew-b= 0 wabews "-": NON_FATAW (addw = 0x0075b980, socket=0, Dimm=0, Channew=2, syndwome=0x00000040, count=1, Eww=8c0000400001009f:4000080482 (wead ewwow: wead ECC ewwow))

3) Cowwected Ewwow memowy wegistew countews

   Those newew MCs have some wegistews to count memowy ewwows. The dwivew
   uses those wegistews to wepowt Cowwected Ewwows on devices with Wegistewed
   DIMMs.

   Howevew, those countews don't wowk with Unwegistewed DIMM. As the chipset
   offews some countews that awso wowk with UDIMMs (but with a wowse wevew of
   gwanuwawity than the defauwt ones), the dwivew exposes those wegistews fow
   UDIMM memowies.

   They can be wead by wooking at the contents of ``aww_channew_counts/``::

     $ fow i in /sys/devices/system/edac/mc/mc0/aww_channew_counts/*; do echo $i; cat $i; done
	/sys/devices/system/edac/mc/mc0/aww_channew_counts/udimm0
	0
	/sys/devices/system/edac/mc/mc0/aww_channew_counts/udimm1
	0
	/sys/devices/system/edac/mc/mc0/aww_channew_counts/udimm2
	0

   What happens hewe is that ewwows on diffewent cswows, but at the same
   dimm numbew wiww incwement the same countew.
   So, in this memowy mapping::

	cswow0: channew 0, dimm0
	cswow1: channew 0, dimm1
	cswow2: channew 1, dimm0
	cswow3: channew 2, dimm0

   The hawdwawe wiww incwement udimm0 fow an ewwow at the fiwst dimm at eithew
   cswow0, cswow2  ow cswow3;

   The hawdwawe wiww incwement udimm1 fow an ewwow at the second dimm at eithew
   cswow0, cswow2  ow cswow3;

   The hawdwawe wiww incwement udimm2 fow an ewwow at the thiwd dimm at eithew
   cswow0, cswow2  ow cswow3;

4) Standawd ewwow countews

   The standawd ewwow countews awe genewated when an mcewog ewwow is weceived
   by the dwivew. Since, with UDIMM, this is counted by softwawe, it is
   possibwe that some ewwows couwd be wost. With WDIMM's, they dispway the
   contents of the wegistews

Wefewence documents used on ``amd64_edac``
------------------------------------------

``amd64_edac`` moduwe is based on the fowwowing documents
(avaiwabwe fwom http://suppowt.amd.com/en-us/seawch/tech-docs):

1. :Titwe:  BIOS and Kewnew Devewopew's Guide fow AMD Athwon 64 and AMD
	   Optewon Pwocessows
   :AMD pubwication #: 26094
   :Wevision: 3.26
   :Wink: http://suppowt.amd.com/TechDocs/26094.PDF

2. :Titwe:  BIOS and Kewnew Devewopew's Guide fow AMD NPT Famiwy 0Fh
	   Pwocessows
   :AMD pubwication #: 32559
   :Wevision: 3.00
   :Issue Date: May 2006
   :Wink: http://suppowt.amd.com/TechDocs/32559.pdf

3. :Titwe:  BIOS and Kewnew Devewopew's Guide (BKDG) Fow AMD Famiwy 10h
	   Pwocessows
   :AMD pubwication #: 31116
   :Wevision: 3.00
   :Issue Date: Septembew 07, 2007
   :Wink: http://suppowt.amd.com/TechDocs/31116.pdf

4. :Titwe: BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 15h
	  Modews 30h-3Fh Pwocessows
   :AMD pubwication #: 49125
   :Wevision: 3.06
   :Issue Date: 2/12/2015 (watest wewease)
   :Wink: http://suppowt.amd.com/TechDocs/49125_15h_Modews_30h-3Fh_BKDG.pdf

5. :Titwe: BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 15h
	  Modews 60h-6Fh Pwocessows
   :AMD pubwication #: 50742
   :Wevision: 3.01
   :Issue Date: 7/23/2015 (watest wewease)
   :Wink: http://suppowt.amd.com/TechDocs/50742_15h_Modews_60h-6Fh_BKDG.pdf

6. :Titwe: BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 16h
	  Modews 00h-0Fh Pwocessows
   :AMD pubwication #: 48751
   :Wevision: 3.03
   :Issue Date: 2/23/2015 (watest wewease)
   :Wink: http://suppowt.amd.com/TechDocs/48751_16h_bkdg.pdf

Cwedits
=======

* Wwitten by Doug Thompson <dougthompson@xmission.com>

  - 7 Dec 2005
  - 17 Juw 2007	Updated

* |copy| Mauwo Cawvawho Chehab

  - 05 Aug 2009	Nehawem intewface
  - 26 Oct 2016 Convewted to WeST and cweanups at the Nehawem section

* EDAC authows/maintainews:

  - Doug Thompson, Dave Jiang, Dave Petewson et aw,
  - Mauwo Cawvawho Chehab
  - Bowiswav Petkov
  - owiginaw authow: Thayne Hawbaugh
