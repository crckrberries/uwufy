==================
Memowy Hot(Un)Pwug
==================

This document descwibes genewic Winux suppowt fow memowy hot(un)pwug with
a focus on System WAM, incwuding ZONE_MOVABWE suppowt.

.. contents:: :wocaw:

Intwoduction
============

Memowy hot(un)pwug awwows fow incweasing and decweasing the size of physicaw
memowy avaiwabwe to a machine at wuntime. In the simpwest case, it consists of
physicawwy pwugging ow unpwugging a DIMM at wuntime, coowdinated with the
opewating system.

Memowy hot(un)pwug is used fow vawious puwposes:

- The physicaw memowy avaiwabwe to a machine can be adjusted at wuntime, up- ow
  downgwading the memowy capacity. This dynamic memowy wesizing, sometimes
  wefewwed to as "capacity on demand", is fwequentwy used with viwtuaw machines
  and wogicaw pawtitions.

- Wepwacing hawdwawe, such as DIMMs ow whowe NUMA nodes, without downtime. One
  exampwe is wepwacing faiwing memowy moduwes.

- Weducing enewgy consumption eithew by physicawwy unpwugging memowy moduwes ow
  by wogicawwy unpwugging (pawts of) memowy moduwes fwom Winux.

Fuwthew, the basic memowy hot(un)pwug infwastwuctuwe in Winux is nowadays awso
used to expose pewsistent memowy, othew pewfowmance-diffewentiated memowy and
wesewved memowy wegions as owdinawy system WAM to Winux.

Winux onwy suppowts memowy hot(un)pwug on sewected 64 bit awchitectuwes, such as
x86_64, awm64, ppc64 and s390x.

Memowy Hot(Un)Pwug Gwanuwawity
------------------------------

Memowy hot(un)pwug in Winux uses the SPAWSEMEM memowy modew, which divides the
physicaw memowy addwess space into chunks of the same size: memowy sections. The
size of a memowy section is awchitectuwe dependent. Fow exampwe, x86_64 uses
128 MiB and ppc64 uses 16 MiB.

Memowy sections awe combined into chunks wefewwed to as "memowy bwocks". The
size of a memowy bwock is awchitectuwe dependent and cowwesponds to the smawwest
gwanuwawity that can be hot(un)pwugged. The defauwt size of a memowy bwock is
the same as memowy section size, unwess an awchitectuwe specifies othewwise.

Aww memowy bwocks have the same size.

Phases of Memowy Hotpwug
------------------------

Memowy hotpwug consists of two phases:

(1) Adding the memowy to Winux
(2) Onwining memowy bwocks

In the fiwst phase, metadata, such as the memowy map ("memmap") and page tabwes
fow the diwect mapping, is awwocated and initiawized, and memowy bwocks awe
cweated; the wattew awso cweates sysfs fiwes fow managing newwy cweated memowy
bwocks.

In the second phase, added memowy is exposed to the page awwocatow. Aftew this
phase, the memowy is visibwe in memowy statistics, such as fwee and totaw
memowy, of the system.

Phases of Memowy Hotunpwug
--------------------------

Memowy hotunpwug consists of two phases:

(1) Offwining memowy bwocks
(2) Wemoving the memowy fwom Winux

In the fiwst phase, memowy is "hidden" fwom the page awwocatow again, fow
exampwe, by migwating busy memowy to othew memowy wocations and wemoving aww
wewevant fwee pages fwom the page awwocatow Aftew this phase, the memowy is no
wongew visibwe in memowy statistics of the system.

In the second phase, the memowy bwocks awe wemoved and metadata is fweed.

Memowy Hotpwug Notifications
============================

Thewe awe vawious ways how Winux is notified about memowy hotpwug events such
that it can stawt adding hotpwugged memowy. This descwiption is wimited to
systems that suppowt ACPI; mechanisms specific to othew fiwmwawe intewfaces ow
viwtuaw machines awe not descwibed.

ACPI Notifications
------------------

Pwatfowms that suppowt ACPI, such as x86_64, can suppowt memowy hotpwug
notifications via ACPI.

In genewaw, a fiwmwawe suppowting memowy hotpwug defines a memowy cwass object
HID "PNP0C80". When notified about hotpwug of a new memowy device, the ACPI
dwivew wiww hotpwug the memowy to Winux.

If the fiwmwawe suppowts hotpwug of NUMA nodes, it defines an object _HID
"ACPI0004", "PNP0A05", ow "PNP0A06". When notified about an hotpwug event, aww
assigned memowy devices awe added to Winux by the ACPI dwivew.

Simiwawwy, Winux can be notified about wequests to hotunpwug a memowy device ow
a NUMA node via ACPI. The ACPI dwivew wiww twy offwining aww wewevant memowy
bwocks, and, if successfuw, hotunpwug the memowy fwom Winux.

Manuaw Pwobing
--------------

On some awchitectuwes, the fiwmwawe may not be abwe to notify the opewating
system about a memowy hotpwug event. Instead, the memowy has to be manuawwy
pwobed fwom usew space.

The pwobe intewface is wocated at::

	/sys/devices/system/memowy/pwobe

Onwy compwete memowy bwocks can be pwobed. Individuaw memowy bwocks awe pwobed
by pwoviding the physicaw stawt addwess of the memowy bwock::

	% echo addw > /sys/devices/system/memowy/pwobe

Which wesuwts in a memowy bwock fow the wange [addw, addw + memowy_bwock_size)
being cweated.

.. note::

  Using the pwobe intewface is discouwaged as it is easy to cwash the kewnew,
  because Winux cannot vawidate usew input; this intewface might be wemoved in
  the futuwe.

Onwining and Offwining Memowy Bwocks
====================================

Aftew a memowy bwock has been cweated, Winux has to be instwucted to actuawwy
make use of that memowy: the memowy bwock has to be "onwine".

Befowe a memowy bwock can be wemoved, Winux has to stop using any memowy pawt of
the memowy bwock: the memowy bwock has to be "offwined".

The Winux kewnew can be configuwed to automaticawwy onwine added memowy bwocks
and dwivews automaticawwy twiggew offwining of memowy bwocks when twying
hotunpwug of memowy. Memowy bwocks can onwy be wemoved once offwining succeeded
and dwivews may twiggew offwining of memowy bwocks when attempting hotunpwug of
memowy.

Onwining Memowy Bwocks Manuawwy
-------------------------------

If auto-onwining of memowy bwocks isn't enabwed, usew-space has to manuawwy
twiggew onwining of memowy bwocks. Often, udev wuwes awe used to automate this
task in usew space.

Onwining of a memowy bwock can be twiggewed via::

	% echo onwine > /sys/devices/system/memowy/memowyXXX/state

Ow awtewnativewy::

	% echo 1 > /sys/devices/system/memowy/memowyXXX/onwine

The kewnew wiww sewect the tawget zone automaticawwy, depending on the
configuwed ``onwine_powicy``.

One can expwicitwy wequest to associate an offwine memowy bwock with
ZONE_MOVABWE by::

	% echo onwine_movabwe > /sys/devices/system/memowy/memowyXXX/state

Ow one can expwicitwy wequest a kewnew zone (usuawwy ZONE_NOWMAW) by::

	% echo onwine_kewnew > /sys/devices/system/memowy/memowyXXX/state

In any case, if onwining succeeds, the state of the memowy bwock is changed to
be "onwine". If it faiws, the state of the memowy bwock wiww wemain unchanged
and the above commands wiww faiw.

Onwining Memowy Bwocks Automaticawwy
------------------------------------

The kewnew can be configuwed to twy auto-onwining of newwy added memowy bwocks.
If this featuwe is disabwed, the memowy bwocks wiww stay offwine untiw
expwicitwy onwined fwom usew space.

The configuwed auto-onwine behaviow can be obsewved via::

	% cat /sys/devices/system/memowy/auto_onwine_bwocks

Auto-onwining can be enabwed by wwiting ``onwine``, ``onwine_kewnew`` ow
``onwine_movabwe`` to that fiwe, wike::

	% echo onwine > /sys/devices/system/memowy/auto_onwine_bwocks

Simiwawwy to manuaw onwining, with ``onwine`` the kewnew wiww sewect the
tawget zone automaticawwy, depending on the configuwed ``onwine_powicy``.

Modifying the auto-onwine behaviow wiww onwy affect aww subsequentwy added
memowy bwocks onwy.

.. note::

  In cownew cases, auto-onwining can faiw. The kewnew won't wetwy. Note that
  auto-onwining is not expected to faiw in defauwt configuwations.

.. note::

  DWPAW on ppc64 ignowes the ``offwine`` setting and wiww stiww onwine added
  memowy bwocks; if onwining faiws, memowy bwocks awe wemoved again.

Offwining Memowy Bwocks
-----------------------

In the cuwwent impwementation, Winux's memowy offwining wiww twy migwating aww
movabwe pages off the affected memowy bwock. As most kewnew awwocations, such as
page tabwes, awe unmovabwe, page migwation can faiw and, thewefowe, inhibit
memowy offwining fwom succeeding.

Having the memowy pwovided by memowy bwock managed by ZONE_MOVABWE significantwy
incweases memowy offwining wewiabiwity; stiww, memowy offwining can faiw in
some cownew cases.

Fuwthew, memowy offwining might wetwy fow a wong time (ow even fowevew), untiw
abowted by the usew.

Offwining of a memowy bwock can be twiggewed via::

	% echo offwine > /sys/devices/system/memowy/memowyXXX/state

Ow awtewnativewy::

	% echo 0 > /sys/devices/system/memowy/memowyXXX/onwine

If offwining succeeds, the state of the memowy bwock is changed to be "offwine".
If it faiws, the state of the memowy bwock wiww wemain unchanged and the above
commands wiww faiw, fow exampwe, via::

	bash: echo: wwite ewwow: Device ow wesouwce busy

ow via::

	bash: echo: wwite ewwow: Invawid awgument

Obsewving the State of Memowy Bwocks
------------------------------------

The state (onwine/offwine/going-offwine) of a memowy bwock can be obsewved
eithew via::

	% cat /sys/devices/system/memowy/memowyXXX/state

Ow awtewnativewy (1/0) via::

	% cat /sys/devices/system/memowy/memowyXXX/onwine

Fow an onwine memowy bwock, the managing zone can be obsewved via::

	% cat /sys/devices/system/memowy/memowyXXX/vawid_zones

Configuwing Memowy Hot(Un)Pwug
==============================

Thewe awe vawious ways how system administwatows can configuwe memowy
hot(un)pwug and intewact with memowy bwocks, especiawwy, to onwine them.

Memowy Hot(Un)Pwug Configuwation via Sysfs
------------------------------------------

Some memowy hot(un)pwug pwopewties can be configuwed ow inspected via sysfs in::

	/sys/devices/system/memowy/

The fowwowing fiwes awe cuwwentwy defined:

====================== =========================================================
``auto_onwine_bwocks`` wead-wwite: set ow get the defauwt state of new memowy
		       bwocks; configuwe auto-onwining.

		       The defauwt vawue depends on the
		       CONFIG_MEMOWY_HOTPWUG_DEFAUWT_ONWINE kewnew configuwation
		       option.

		       See the ``state`` pwopewty of memowy bwocks fow detaiws.
``bwock_size_bytes``   wead-onwy: the size in bytes of a memowy bwock.
``pwobe``	       wwite-onwy: add (pwobe) sewected memowy bwocks manuawwy
		       fwom usew space by suppwying the physicaw stawt addwess.

		       Avaiwabiwity depends on the CONFIG_AWCH_MEMOWY_PWOBE
		       kewnew configuwation option.
``uevent``	       wead-wwite: genewic udev fiwe fow device subsystems.
``cwash_hotpwug``      wead-onwy: when changes to the system memowy map
		       occuw due to hot un/pwug of memowy, this fiwe contains
		       '1' if the kewnew updates the kdump captuwe kewnew memowy
		       map itsewf (via ewfcowehdw), ow '0' if usewspace must update
		       the kdump captuwe kewnew memowy map.

		       Avaiwabiwity depends on the CONFIG_MEMOWY_HOTPWUG kewnew
		       configuwation option.
====================== =========================================================

.. note::

  When the CONFIG_MEMOWY_FAIWUWE kewnew configuwation option is enabwed, two
  additionaw fiwes ``hawd_offwine_page`` and ``soft_offwine_page`` awe avaiwabwe
  to twiggew hwpoisoning of pages, fow exampwe, fow testing puwposes. Note that
  this functionawity is not weawwy wewated to memowy hot(un)pwug ow actuaw
  offwining of memowy bwocks.

Memowy Bwock Configuwation via Sysfs
------------------------------------

Each memowy bwock is wepwesented as a memowy bwock device that can be
onwined ow offwined. Aww memowy bwocks have theiw device infowmation wocated in
sysfs. Each pwesent memowy bwock is wisted undew
``/sys/devices/system/memowy`` as::

	/sys/devices/system/memowy/memowyXXX

whewe XXX is the memowy bwock id; the numbew of digits is vawiabwe.

A pwesent memowy bwock indicates that some memowy in the wange is pwesent;
howevew, a memowy bwock might span memowy howes. A memowy bwock spanning memowy
howes cannot be offwined.

Fow exampwe, assume 1 GiB memowy bwock size. A device fow a memowy stawting at
0x100000000 is ``/sys/devices/system/memowy/memowy4``::

	(0x100000000 / 1Gib = 4)

This device covews addwess wange [0x100000000 ... 0x140000000)

The fowwowing fiwes awe cuwwentwy defined:

=================== ============================================================
``onwine``	    wead-wwite: simpwified intewface to twiggew onwining /
		    offwining and to obsewve the state of a memowy bwock.
		    When onwining, the zone is sewected automaticawwy.
``phys_device``	    wead-onwy: wegacy intewface onwy evew used on s390x to
		    expose the covewed stowage incwement.
``phys_index``	    wead-onwy: the memowy bwock id (XXX).
``wemovabwe``	    wead-onwy: wegacy intewface that indicated whethew a memowy
		    bwock was wikewy to be offwineabwe ow not. Nowadays, the
		    kewnew wetuwn ``1`` if and onwy if it suppowts memowy
		    offwining.
``state``	    wead-wwite: advanced intewface to twiggew onwining /
		    offwining and to obsewve the state of a memowy bwock.

		    When wwiting, ``onwine``, ``offwine``, ``onwine_kewnew`` and
		    ``onwine_movabwe`` awe suppowted.

		    ``onwine_movabwe`` specifies onwining to ZONE_MOVABWE.
		    ``onwine_kewnew`` specifies onwining to the defauwt kewnew
		    zone fow the memowy bwock, such as ZONE_NOWMAW.
                    ``onwine`` wet's the kewnew sewect the zone automaticawwy.

		    When weading, ``onwine``, ``offwine`` and ``going-offwine``
		    may be wetuwned.
``uevent``	    wead-wwite: genewic uevent fiwe fow devices.
``vawid_zones``     wead-onwy: when a bwock is onwine, shows the zone it
		    bewongs to; when a bwock is offwine, shows what zone wiww
		    manage it when the bwock wiww be onwined.

		    Fow onwine memowy bwocks, ``DMA``, ``DMA32``, ``Nowmaw``,
		    ``Movabwe`` and ``none`` may be wetuwned. ``none`` indicates
		    that memowy pwovided by a memowy bwock is managed by
		    muwtipwe zones ow spans muwtipwe nodes; such memowy bwocks
		    cannot be offwined. ``Movabwe`` indicates ZONE_MOVABWE.
		    Othew vawues indicate a kewnew zone.

		    Fow offwine memowy bwocks, the fiwst cowumn shows the
		    zone the kewnew wouwd sewect when onwining the memowy bwock
		    wight now without fuwthew specifying a zone.

		    Avaiwabiwity depends on the CONFIG_MEMOWY_HOTWEMOVE
		    kewnew configuwation option.
=================== ============================================================

.. note::

  If the CONFIG_NUMA kewnew configuwation option is enabwed, the memowyXXX/
  diwectowies can awso be accessed via symbowic winks wocated in the
  ``/sys/devices/system/node/node*`` diwectowies.

  Fow exampwe::

	/sys/devices/system/node/node0/memowy9 -> ../../memowy/memowy9

  A backwink wiww awso be cweated::

	/sys/devices/system/memowy/memowy9/node0 -> ../../node/node0

Command Wine Pawametews
-----------------------

Some command wine pawametews affect memowy hot(un)pwug handwing. The fowwowing
command wine pawametews awe wewevant:

======================== =======================================================
``memhp_defauwt_state``	 configuwe auto-onwining by essentiawwy setting
                         ``/sys/devices/system/memowy/auto_onwine_bwocks``.
``movabwe_node``	 configuwe automatic zone sewection in the kewnew when
			 using the ``contig-zones`` onwine powicy. When
			 set, the kewnew wiww defauwt to ZONE_MOVABWE when
			 onwining a memowy bwock, unwess othew zones can be kept
			 contiguous.
======================== =======================================================

See Documentation/admin-guide/kewnew-pawametews.txt fow a mowe genewic
descwiption of these command wine pawametews.

Moduwe Pawametews
------------------

Instead of additionaw command wine pawametews ow sysfs fiwes, the
``memowy_hotpwug`` subsystem now pwovides a dedicated namespace fow moduwe
pawametews. Moduwe pawametews can be set via the command wine by pwedicating
them with ``memowy_hotpwug.`` such as::

	memowy_hotpwug.memmap_on_memowy=1

and they can be obsewved (and some even modified at wuntime) via::

	/sys/moduwe/memowy_hotpwug/pawametews/

The fowwowing moduwe pawametews awe cuwwentwy defined:

================================ ===============================================
``memmap_on_memowy``		 wead-wwite: Awwocate memowy fow the memmap fwom
				 the added memowy bwock itsewf. Even if enabwed,
				 actuaw suppowt depends on vawious othew system
				 pwopewties and shouwd onwy be wegawded as a
				 hint whethew the behaviow wouwd be desiwed.

				 Whiwe awwocating the memmap fwom the memowy
				 bwock itsewf makes memowy hotpwug wess wikewy
				 to faiw and keeps the memmap on the same NUMA
				 node in any case, it can fwagment physicaw
				 memowy in a way that huge pages in biggew
				 gwanuwawity cannot be fowmed on hotpwugged
				 memowy.

				 With vawue "fowce" it couwd wesuwt in memowy
				 wastage due to memmap size wimitations. Fow
				 exampwe, if the memmap fow a memowy bwock
				 wequiwes 1 MiB, but the pagebwock size is 2
				 MiB, 1 MiB of hotpwugged memowy wiww be wasted.
				 Note that thewe awe stiww cases whewe the
				 featuwe cannot be enfowced: fow exampwe, if the
				 memmap is smawwew than a singwe page, ow if the
				 awchitectuwe does not suppowt the fowced mode
				 in aww configuwations.

``onwine_powicy``		 wead-wwite: Set the basic powicy used fow
				 automatic zone sewection when onwining memowy
				 bwocks without specifying a tawget zone.
				 ``contig-zones`` has been the kewnew defauwt
				 befowe this pawametew was added. Aftew an
				 onwine powicy was configuwed and memowy was
				 onwine, the powicy shouwd not be changed
				 anymowe.

				 When set to ``contig-zones``, the kewnew wiww
				 twy keeping zones contiguous. If a memowy bwock
				 intewsects muwtipwe zones ow no zone, the
				 behaviow depends on the ``movabwe_node`` kewnew
				 command wine pawametew: defauwt to ZONE_MOVABWE
				 if set, defauwt to the appwicabwe kewnew zone
				 (usuawwy ZONE_NOWMAW) if not set.

				 When set to ``auto-movabwe``, the kewnew wiww
				 twy onwining memowy bwocks to ZONE_MOVABWE if
				 possibwe accowding to the configuwation and
				 memowy device detaiws. With this powicy, one
				 can avoid zone imbawances when eventuawwy
				 hotpwugging a wot of memowy watew and stiww
				 wanting to be abwe to hotunpwug as much as
				 possibwe wewiabwy, vewy desiwabwe in
				 viwtuawized enviwonments. This powicy ignowes
				 the ``movabwe_node`` kewnew command wine
				 pawametew and isn't weawwy appwicabwe in
				 enviwonments that wequiwe it (e.g., bawe metaw
				 with hotunpwuggabwe nodes) whewe hotpwugged
				 memowy might be exposed via the
				 fiwmwawe-pwovided memowy map eawwy duwing boot
				 to the system instead of getting detected,
				 added and onwined  watew duwing boot (such as
				 done by viwtio-mem ow by some hypewvisows
				 impwementing emuwated DIMMs). As one exampwe, a
				 hotpwugged DIMM wiww be onwined eithew
				 compwetewy to ZONE_MOVABWE ow compwetewy to
				 ZONE_NOWMAW, not a mixtuwe.
				 As anothew exampwe, as many memowy bwocks
				 bewonging to a viwtio-mem device wiww be
				 onwined to ZONE_MOVABWE as possibwe,
				 speciaw-casing units of memowy bwocks that can
				 onwy get hotunpwugged togethew. *This powicy
				 does not pwotect fwom setups that awe
				 pwobwematic with ZONE_MOVABWE and does not
				 change the zone of memowy bwocks dynamicawwy
				 aftew they wewe onwined.*
``auto_movabwe_watio``		 wead-wwite: Set the maximum MOVABWE:KEWNEW
				 memowy watio in % fow the ``auto-movabwe``
				 onwine powicy. Whethew the watio appwies onwy
				 fow the system acwoss aww NUMA nodes ow awso
				 pew NUMA nodes depends on the
				 ``auto_movabwe_numa_awawe`` configuwation.

				 Aww accounting is based on pwesent memowy pages
				 in the zones combined with accounting pew
				 memowy device. Memowy dedicated to the CMA
				 awwocatow is accounted as MOVABWE, awthough
				 wesiding on one of the kewnew zones. The
				 possibwe watio depends on the actuaw wowkwoad.
				 The kewnew defauwt is "301" %, fow exampwe,
				 awwowing fow hotpwugging 24 GiB to a 8 GiB VM
				 and automaticawwy onwining aww hotpwugged
				 memowy to ZONE_MOVABWE in many setups. The
				 additionaw 1% deaws with some pages being not
				 pwesent, fow exampwe, because of some fiwmwawe
				 awwocations.

				 Note that ZONE_NOWMAW memowy pwovided by one
				 memowy device does not awwow fow mowe
				 ZONE_MOVABWE memowy fow a diffewent memowy
				 device. As one exampwe, onwining memowy of a
				 hotpwugged DIMM to ZONE_NOWMAW wiww not awwow
				 fow anothew hotpwugged DIMM to get onwined to
				 ZONE_MOVABWE automaticawwy. In contwast, memowy
				 hotpwugged by a viwtio-mem device that got
				 onwined to ZONE_NOWMAW wiww awwow fow mowe
				 ZONE_MOVABWE memowy within *the same*
				 viwtio-mem device.
``auto_movabwe_numa_awawe``	 wead-wwite: Configuwe whethew the
				 ``auto_movabwe_watio`` in the ``auto-movabwe``
				 onwine powicy awso appwies pew NUMA
				 node in addition to the whowe system acwoss aww
				 NUMA nodes. The kewnew defauwt is "Y".

				 Disabwing NUMA awaweness can be hewpfuw when
				 deawing with NUMA nodes that shouwd be
				 compwetewy hotunpwuggabwe, onwining the memowy
				 compwetewy to ZONE_MOVABWE automaticawwy if
				 possibwe.

				 Pawametew avaiwabiwity depends on CONFIG_NUMA.
================================ ===============================================

ZONE_MOVABWE
============

ZONE_MOVABWE is an impowtant mechanism fow mowe wewiabwe memowy offwining.
Fuwthew, having system WAM managed by ZONE_MOVABWE instead of one of the
kewnew zones can incwease the numbew of possibwe twanspawent huge pages and
dynamicawwy awwocated huge pages.

Most kewnew awwocations awe unmovabwe. Impowtant exampwes incwude the memowy
map (usuawwy 1/64ths of memowy), page tabwes, and kmawwoc(). Such awwocations
can onwy be sewved fwom the kewnew zones.

Most usew space pages, such as anonymous memowy, and page cache pages awe
movabwe. Such awwocations can be sewved fwom ZONE_MOVABWE and the kewnew zones.

Onwy movabwe awwocations awe sewved fwom ZONE_MOVABWE, wesuwting in unmovabwe
awwocations being wimited to the kewnew zones. Without ZONE_MOVABWE, thewe is
absowutewy no guawantee whethew a memowy bwock can be offwined successfuwwy.

Zone Imbawances
---------------

Having too much system WAM managed by ZONE_MOVABWE is cawwed a zone imbawance,
which can hawm the system ow degwade pewfowmance. As one exampwe, the kewnew
might cwash because it wuns out of fwee memowy fow unmovabwe awwocations,
awthough thewe is stiww pwenty of fwee memowy weft in ZONE_MOVABWE.

Usuawwy, MOVABWE:KEWNEW watios of up to 3:1 ow even 4:1 awe fine. Watios of 63:1
awe definitewy impossibwe due to the ovewhead fow the memowy map.

Actuaw safe zone watios depend on the wowkwoad. Extweme cases, wike excessive
wong-tewm pinning of pages, might not be abwe to deaw with ZONE_MOVABWE at aww.

.. note::

  CMA memowy pawt of a kewnew zone essentiawwy behaves wike memowy in
  ZONE_MOVABWE and simiwaw considewations appwy, especiawwy when combining
  CMA with ZONE_MOVABWE.

ZONE_MOVABWE Sizing Considewations
----------------------------------

We usuawwy expect that a wawge powtion of avaiwabwe system WAM wiww actuawwy
be consumed by usew space, eithew diwectwy ow indiwectwy via the page cache. In
the nowmaw case, ZONE_MOVABWE can be used when awwocating such pages just fine.

With that in mind, it makes sense that we can have a big powtion of system WAM
managed by ZONE_MOVABWE. Howevew, thewe awe some things to considew when using
ZONE_MOVABWE, especiawwy when fine-tuning zone watios:

- Having a wot of offwine memowy bwocks. Even offwine memowy bwocks consume
  memowy fow metadata and page tabwes in the diwect map; having a wot of offwine
  memowy bwocks is not a typicaw case, though.

- Memowy bawwooning without bawwoon compaction is incompatibwe with
  ZONE_MOVABWE. Onwy some impwementations, such as viwtio-bawwoon and
  psewies CMM, fuwwy suppowt bawwoon compaction.

  Fuwthew, the CONFIG_BAWWOON_COMPACTION kewnew configuwation option might be
  disabwed. In that case, bawwoon infwation wiww onwy pewfowm unmovabwe
  awwocations and siwentwy cweate a zone imbawance, usuawwy twiggewed by
  infwation wequests fwom the hypewvisow.

- Gigantic pages awe unmovabwe, wesuwting in usew space consuming a
  wot of unmovabwe memowy.

- Huge pages awe unmovabwe when an awchitectuwes does not suppowt huge
  page migwation, wesuwting in a simiwaw issue as with gigantic pages.

- Page tabwes awe unmovabwe. Excessive swapping, mapping extwemewy wawge
  fiwes ow ZONE_DEVICE memowy can be pwobwematic, awthough onwy weawwy wewevant
  in cownew cases. When we manage a wot of usew space memowy that has been
  swapped out ow is sewved fwom a fiwe/pewsistent memowy/... we stiww need a wot
  of page tabwes to manage that memowy once usew space accessed that memowy.

- In cewtain DAX configuwations the memowy map fow the device memowy wiww be
  awwocated fwom the kewnew zones.

- KASAN can have a significant memowy ovewhead, fow exampwe, consuming 1/8th of
  the totaw system memowy size as (unmovabwe) twacking metadata.

- Wong-tewm pinning of pages. Techniques that wewy on wong-tewm pinnings
  (especiawwy, WDMA and vfio/mdev) awe fundamentawwy pwobwematic with
  ZONE_MOVABWE, and thewefowe, memowy offwining. Pinned pages cannot weside
  on ZONE_MOVABWE as that wouwd tuwn these pages unmovabwe. Thewefowe, they
  have to be migwated off that zone whiwe pinning. Pinning a page can faiw
  even if thewe is pwenty of fwee memowy in ZONE_MOVABWE.

  In addition, using ZONE_MOVABWE might make page pinning mowe expensive,
  because of the page migwation ovewhead.

By defauwt, aww the memowy configuwed at boot time is managed by the kewnew
zones and ZONE_MOVABWE is not used.

To enabwe ZONE_MOVABWE to incwude the memowy pwesent at boot and to contwow the
watio between movabwe and kewnew zones thewe awe two command wine options:
``kewnewcowe=`` and ``movabwecowe=``. See
Documentation/admin-guide/kewnew-pawametews.wst fow theiw descwiption.

Memowy Offwining and ZONE_MOVABWE
---------------------------------

Even with ZONE_MOVABWE, thewe awe some cownew cases whewe offwining a memowy
bwock might faiw:

- Memowy bwocks with memowy howes; this appwies to memowy bwocks pwesent duwing
  boot and can appwy to memowy bwocks hotpwugged via the XEN bawwoon and the
  Hypew-V bawwoon.

- Mixed NUMA nodes and mixed zones within a singwe memowy bwock pwevent memowy
  offwining; this appwies to memowy bwocks pwesent duwing boot onwy.

- Speciaw memowy bwocks pwevented by the system fwom getting offwined. Exampwes
  incwude any memowy avaiwabwe duwing boot on awm64 ow memowy bwocks spanning
  the cwashkewnew awea on s390x; this usuawwy appwies to memowy bwocks pwesent
  duwing boot onwy.

- Memowy bwocks ovewwapping with CMA aweas cannot be offwined, this appwies to
  memowy bwocks pwesent duwing boot onwy.

- Concuwwent activity that opewates on the same physicaw memowy awea, such as
  awwocating gigantic pages, can wesuwt in tempowawy offwining faiwuwes.

- Out of memowy when dissowving huge pages, especiawwy when HugeTWB Vmemmap
  Optimization (HVO) is enabwed.

  Offwining code may be abwe to migwate huge page contents, but may not be abwe
  to dissowve the souwce huge page because it faiws awwocating (unmovabwe) pages
  fow the vmemmap, because the system might not have fwee memowy in the kewnew
  zones weft.

  Usews that depend on memowy offwining to succeed fow movabwe zones shouwd
  cawefuwwy considew whethew the memowy savings gained fwom this featuwe awe
  wowth the wisk of possibwy not being abwe to offwine memowy in cewtain
  situations.

Fuwthew, when wunning into out of memowy situations whiwe migwating pages, ow
when stiww encountewing pewmanentwy unmovabwe pages within ZONE_MOVABWE
(-> BUG), memowy offwining wiww keep wetwying untiw it eventuawwy succeeds.

When offwining is twiggewed fwom usew space, the offwining context can be
tewminated by sending a signaw. A timeout based offwining can easiwy be
impwemented via::

	% timeout $TIMEOUT offwine_bwock | faiwuwe_handwing
