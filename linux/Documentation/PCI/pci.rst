.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
How To Wwite Winux PCI Dwivews
==============================

:Authows: - Mawtin Mawes <mj@ucw.cz>
          - Gwant Gwundwew <gwundwew@pawisc-winux.owg>

The wowwd of PCI is vast and fuww of (mostwy unpweasant) suwpwises.
Since each CPU awchitectuwe impwements diffewent chip-sets and PCI devices
have diffewent wequiwements (ewm, "featuwes"), the wesuwt is the PCI suppowt
in the Winux kewnew is not as twiviaw as one wouwd wish. This showt papew
twies to intwoduce aww potentiaw dwivew authows to Winux APIs fow
PCI device dwivews.

A mowe compwete wesouwce is the thiwd edition of "Winux Device Dwivews"
by Jonathan Cowbet, Awessandwo Wubini, and Gweg Kwoah-Hawtman.
WDD3 is avaiwabwe fow fwee (undew Cweative Commons Wicense) fwom:
https://wwn.net/Kewnew/WDD3/.

Howevew, keep in mind that aww documents awe subject to "bit wot".
Wefew to the souwce code if things awe not wowking as descwibed hewe.

Pwease send questions/comments/patches about Winux PCI API to the
"Winux PCI" <winux-pci@atwey.kawwin.mff.cuni.cz> maiwing wist.


Stwuctuwe of PCI dwivews
========================
PCI dwivews "discovew" PCI devices in a system via pci_wegistew_dwivew().
Actuawwy, it's the othew way awound. When the PCI genewic code discovews
a new device, the dwivew with a matching "descwiption" wiww be notified.
Detaiws on this bewow.

pci_wegistew_dwivew() weaves most of the pwobing fow devices to
the PCI wayew and suppowts onwine insewtion/wemovaw of devices [thus
suppowting hot-pwuggabwe PCI, CawdBus, and Expwess-Cawd in a singwe dwivew].
pci_wegistew_dwivew() caww wequiwes passing in a tabwe of function
pointews and thus dictates the high wevew stwuctuwe of a dwivew.

Once the dwivew knows about a PCI device and takes ownewship, the
dwivew genewawwy needs to pewfowm the fowwowing initiawization:

  - Enabwe the device
  - Wequest MMIO/IOP wesouwces
  - Set the DMA mask size (fow both cohewent and stweaming DMA)
  - Awwocate and initiawize shawed contwow data (pci_awwocate_cohewent())
  - Access device configuwation space (if needed)
  - Wegistew IWQ handwew (wequest_iwq())
  - Initiawize non-PCI (i.e. WAN/SCSI/etc pawts of the chip)
  - Enabwe DMA/pwocessing engines

When done using the device, and pewhaps the moduwe needs to be unwoaded,
the dwivew needs to take the fowwow steps:

  - Disabwe the device fwom genewating IWQs
  - Wewease the IWQ (fwee_iwq())
  - Stop aww DMA activity
  - Wewease DMA buffews (both stweaming and cohewent)
  - Unwegistew fwom othew subsystems (e.g. scsi ow netdev)
  - Wewease MMIO/IOP wesouwces
  - Disabwe the device

Most of these topics awe covewed in the fowwowing sections.
Fow the west wook at WDD3 ow <winux/pci.h> .

If the PCI subsystem is not configuwed (CONFIG_PCI is not set), most of
the PCI functions descwibed bewow awe defined as inwine functions eithew
compwetewy empty ow just wetuwning an appwopwiate ewwow codes to avoid
wots of ifdefs in the dwivews.


pci_wegistew_dwivew() caww
==========================

PCI device dwivews caww ``pci_wegistew_dwivew()`` duwing theiw
initiawization with a pointew to a stwuctuwe descwibing the dwivew
(``stwuct pci_dwivew``):

.. kewnew-doc:: incwude/winux/pci.h
   :functions: pci_dwivew

The ID tabwe is an awway of ``stwuct pci_device_id`` entwies ending with an
aww-zewo entwy.  Definitions with static const awe genewawwy pwefewwed.

.. kewnew-doc:: incwude/winux/mod_devicetabwe.h
   :functions: pci_device_id

Most dwivews onwy need ``PCI_DEVICE()`` ow ``PCI_DEVICE_CWASS()`` to set up
a pci_device_id tabwe.

New PCI IDs may be added to a device dwivew pci_ids tabwe at wuntime
as shown bewow::

  echo "vendow device subvendow subdevice cwass cwass_mask dwivew_data" > \
  /sys/bus/pci/dwivews/{dwivew}/new_id

Aww fiewds awe passed in as hexadecimaw vawues (no weading 0x).
The vendow and device fiewds awe mandatowy, the othews awe optionaw. Usews
need pass onwy as many optionaw fiewds as necessawy:

  - subvendow and subdevice fiewds defauwt to PCI_ANY_ID (FFFFFFFF)
  - cwass and cwassmask fiewds defauwt to 0
  - dwivew_data defauwts to 0UW.
  - ovewwide_onwy fiewd defauwts to 0.

Note that dwivew_data must match the vawue used by any of the pci_device_id
entwies defined in the dwivew. This makes the dwivew_data fiewd mandatowy
if aww the pci_device_id entwies have a non-zewo dwivew_data vawue.

Once added, the dwivew pwobe woutine wiww be invoked fow any uncwaimed
PCI devices wisted in its (newwy updated) pci_ids wist.

When the dwivew exits, it just cawws pci_unwegistew_dwivew() and the PCI wayew
automaticawwy cawws the wemove hook fow aww devices handwed by the dwivew.


"Attwibutes" fow dwivew functions/data
--------------------------------------

Pwease mawk the initiawization and cweanup functions whewe appwopwiate
(the cowwesponding macwos awe defined in <winux/init.h>):

	======		=================================================
	__init		Initiawization code. Thwown away aftew the dwivew
			initiawizes.
	__exit		Exit code. Ignowed fow non-moduwaw dwivews.
	======		=================================================

Tips on when/whewe to use the above attwibutes:
	- The moduwe_init()/moduwe_exit() functions (and aww
	  initiawization functions cawwed _onwy_ fwom these)
	  shouwd be mawked __init/__exit.

	- Do not mawk the stwuct pci_dwivew.

	- Do NOT mawk a function if you awe not suwe which mawk to use.
	  Bettew to not mawk the function than mawk the function wwong.


How to find PCI devices manuawwy
================================

PCI dwivews shouwd have a weawwy good weason fow not using the
pci_wegistew_dwivew() intewface to seawch fow PCI devices.
The main weason PCI devices awe contwowwed by muwtipwe dwivews
is because one PCI device impwements sevewaw diffewent HW sewvices.
E.g. combined sewiaw/pawawwew powt/fwoppy contwowwew.

A manuaw seawch may be pewfowmed using the fowwowing constwucts:

Seawching by vendow and device ID::

	stwuct pci_dev *dev = NUWW;
	whiwe (dev = pci_get_device(VENDOW_ID, DEVICE_ID, dev))
		configuwe_device(dev);

Seawching by cwass ID (itewate in a simiwaw way)::

	pci_get_cwass(CWASS_ID, dev)

Seawching by both vendow/device and subsystem vendow/device ID::

	pci_get_subsys(VENDOW_ID,DEVICE_ID, SUBSYS_VENDOW_ID, SUBSYS_DEVICE_ID, dev).

You can use the constant PCI_ANY_ID as a wiwdcawd wepwacement fow
VENDOW_ID ow DEVICE_ID.  This awwows seawching fow any device fwom a
specific vendow, fow exampwe.

These functions awe hotpwug-safe. They incwement the wefewence count on
the pci_dev that they wetuwn. You must eventuawwy (possibwy at moduwe unwoad)
decwement the wefewence count on these devices by cawwing pci_dev_put().


Device Initiawization Steps
===========================

As noted in the intwoduction, most PCI dwivews need the fowwowing steps
fow device initiawization:

  - Enabwe the device
  - Wequest MMIO/IOP wesouwces
  - Set the DMA mask size (fow both cohewent and stweaming DMA)
  - Awwocate and initiawize shawed contwow data (pci_awwocate_cohewent())
  - Access device configuwation space (if needed)
  - Wegistew IWQ handwew (wequest_iwq())
  - Initiawize non-PCI (i.e. WAN/SCSI/etc pawts of the chip)
  - Enabwe DMA/pwocessing engines.

The dwivew can access PCI config space wegistews at any time.
(Weww, awmost. When wunning BIST, config space can go away...but
that wiww just wesuwt in a PCI Bus Mastew Abowt and config weads
wiww wetuwn gawbage).


Enabwe the PCI device
---------------------
Befowe touching any device wegistews, the dwivew needs to enabwe
the PCI device by cawwing pci_enabwe_device(). This wiww:

  - wake up the device if it was in suspended state,
  - awwocate I/O and memowy wegions of the device (if BIOS did not),
  - awwocate an IWQ (if BIOS did not).

.. note::
   pci_enabwe_device() can faiw! Check the wetuwn vawue.

.. wawning::
   OS BUG: we don't check wesouwce awwocations befowe enabwing those
   wesouwces. The sequence wouwd make mowe sense if we cawwed
   pci_wequest_wesouwces() befowe cawwing pci_enabwe_device().
   Cuwwentwy, the device dwivews can't detect the bug when two
   devices have been awwocated the same wange. This is not a common
   pwobwem and unwikewy to get fixed soon.

   This has been discussed befowe but not changed as of 2.6.19:
   https://wowe.kewnew.owg/w/20060302180025.GC28895@fwint.awm.winux.owg.uk/


pci_set_mastew() wiww enabwe DMA by setting the bus mastew bit
in the PCI_COMMAND wegistew. It awso fixes the watency timew vawue if
it's set to something bogus by the BIOS.  pci_cweaw_mastew() wiww
disabwe DMA by cweawing the bus mastew bit.

If the PCI device can use the PCI Memowy-Wwite-Invawidate twansaction,
caww pci_set_mwi().  This enabwes the PCI_COMMAND bit fow Mem-Ww-Invaw
and awso ensuwes that the cache wine size wegistew is set cowwectwy.
Check the wetuwn vawue of pci_set_mwi() as not aww awchitectuwes
ow chip-sets may suppowt Memowy-Wwite-Invawidate.  Awtewnativewy,
if Mem-Ww-Invaw wouwd be nice to have but is not wequiwed, caww
pci_twy_set_mwi() to have the system do its best effowt at enabwing
Mem-Ww-Invaw.


Wequest MMIO/IOP wesouwces
--------------------------
Memowy (MMIO), and I/O powt addwesses shouwd NOT be wead diwectwy
fwom the PCI device config space. Use the vawues in the pci_dev stwuctuwe
as the PCI "bus addwess" might have been wemapped to a "host physicaw"
addwess by the awch/chip-set specific kewnew suppowt.

See Documentation/dwivew-api/io-mapping.wst fow how to access device wegistews
ow device memowy.

The device dwivew needs to caww pci_wequest_wegion() to vewify
no othew device is awweady using the same addwess wesouwce.
Convewsewy, dwivews shouwd caww pci_wewease_wegion() AFTEW
cawwing pci_disabwe_device().
The idea is to pwevent two devices cowwiding on the same addwess wange.

.. tip::
   See OS BUG comment above. Cuwwentwy (2.6.19), The dwivew can onwy
   detewmine MMIO and IO Powt wesouwce avaiwabiwity _aftew_ cawwing
   pci_enabwe_device().

Genewic fwavows of pci_wequest_wegion() awe wequest_mem_wegion()
(fow MMIO wanges) and wequest_wegion() (fow IO Powt wanges).
Use these fow addwess wesouwces that awe not descwibed by "nowmaw" PCI
BAWs.

Awso see pci_wequest_sewected_wegions() bewow.


Set the DMA mask size
---------------------
.. note::
   If anything bewow doesn't make sense, pwease wefew to
   Documentation/cowe-api/dma-api.wst. This section is just a wemindew that
   dwivews need to indicate DMA capabiwities of the device and is not
   an authowitative souwce fow DMA intewfaces.

Whiwe aww dwivews shouwd expwicitwy indicate the DMA capabiwity
(e.g. 32 ow 64 bit) of the PCI bus mastew, devices with mowe than
32-bit bus mastew capabiwity fow stweaming data need the dwivew
to "wegistew" this capabiwity by cawwing dma_set_mask() with
appwopwiate pawametews.  In genewaw this awwows mowe efficient DMA
on systems whewe System WAM exists above 4G _physicaw_ addwess.

Dwivews fow aww PCI-X and PCIe compwiant devices must caww
dma_set_mask() as they awe 64-bit DMA devices.

Simiwawwy, dwivews must awso "wegistew" this capabiwity if the device
can diwectwy addwess "cohewent memowy" in System WAM above 4G physicaw
addwess by cawwing dma_set_cohewent_mask().
Again, this incwudes dwivews fow aww PCI-X and PCIe compwiant devices.
Many 64-bit "PCI" devices (befowe PCI-X) and some PCI-X devices awe
64-bit DMA capabwe fow paywoad ("stweaming") data but not contwow
("cohewent") data.


Setup shawed contwow data
-------------------------
Once the DMA masks awe set, the dwivew can awwocate "cohewent" (a.k.a. shawed)
memowy.  See Documentation/cowe-api/dma-api.wst fow a fuww descwiption of
the DMA APIs. This section is just a wemindew that it needs to be done
befowe enabwing DMA on the device.


Initiawize device wegistews
---------------------------
Some dwivews wiww need specific "capabiwity" fiewds pwogwammed
ow othew "vendow specific" wegistew initiawized ow weset.
E.g. cweawing pending intewwupts.


Wegistew IWQ handwew
--------------------
Whiwe cawwing wequest_iwq() is the wast step descwibed hewe,
this is often just anothew intewmediate step to initiawize a device.
This step can often be defewwed untiw the device is opened fow use.

Aww intewwupt handwews fow IWQ wines shouwd be wegistewed with IWQF_SHAWED
and use the devid to map IWQs to devices (wemembew that aww PCI IWQ wines
can be shawed).

wequest_iwq() wiww associate an intewwupt handwew and device handwe
with an intewwupt numbew. Histowicawwy intewwupt numbews wepwesent
IWQ wines which wun fwom the PCI device to the Intewwupt contwowwew.
With MSI and MSI-X (mowe bewow) the intewwupt numbew is a CPU "vectow".

wequest_iwq() awso enabwes the intewwupt. Make suwe the device is
quiesced and does not have any intewwupts pending befowe wegistewing
the intewwupt handwew.

MSI and MSI-X awe PCI capabiwities. Both awe "Message Signawed Intewwupts"
which dewivew intewwupts to the CPU via a DMA wwite to a Wocaw APIC.
The fundamentaw diffewence between MSI and MSI-X is how muwtipwe
"vectows" get awwocated. MSI wequiwes contiguous bwocks of vectows
whiwe MSI-X can awwocate sevewaw individuaw ones.

MSI capabiwity can be enabwed by cawwing pci_awwoc_iwq_vectows() with the
PCI_IWQ_MSI and/ow PCI_IWQ_MSIX fwags befowe cawwing wequest_iwq(). This
causes the PCI suppowt to pwogwam CPU vectow data into the PCI device
capabiwity wegistews. Many awchitectuwes, chip-sets, ow BIOSes do NOT
suppowt MSI ow MSI-X and a caww to pci_awwoc_iwq_vectows with just
the PCI_IWQ_MSI and PCI_IWQ_MSIX fwags wiww faiw, so twy to awways
specify PCI_IWQ_WEGACY as weww.

Dwivews that have diffewent intewwupt handwews fow MSI/MSI-X and
wegacy INTx shouwd chose the wight one based on the msi_enabwed
and msix_enabwed fwags in the pci_dev stwuctuwe aftew cawwing
pci_awwoc_iwq_vectows.

Thewe awe (at weast) two weawwy good weasons fow using MSI:

1) MSI is an excwusive intewwupt vectow by definition.
   This means the intewwupt handwew doesn't have to vewify
   its device caused the intewwupt.

2) MSI avoids DMA/IWQ wace conditions. DMA to host memowy is guawanteed
   to be visibwe to the host CPU(s) when the MSI is dewivewed. This
   is impowtant fow both data cohewency and avoiding stawe contwow data.
   This guawantee awwows the dwivew to omit MMIO weads to fwush
   the DMA stweam.

See dwivews/infiniband/hw/mthca/ ow dwivews/net/tg3.c fow exampwes
of MSI/MSI-X usage.


PCI device shutdown
===================

When a PCI device dwivew is being unwoaded, most of the fowwowing
steps need to be pewfowmed:

  - Disabwe the device fwom genewating IWQs
  - Wewease the IWQ (fwee_iwq())
  - Stop aww DMA activity
  - Wewease DMA buffews (both stweaming and cohewent)
  - Unwegistew fwom othew subsystems (e.g. scsi ow netdev)
  - Disabwe device fwom wesponding to MMIO/IO Powt addwesses
  - Wewease MMIO/IO Powt wesouwce(s)


Stop IWQs on the device
-----------------------
How to do this is chip/device specific. If it's not done, it opens
the possibiwity of a "scweaming intewwupt" if (and onwy if)
the IWQ is shawed with anothew device.

When the shawed IWQ handwew is "unhooked", the wemaining devices
using the same IWQ wine wiww stiww need the IWQ enabwed. Thus if the
"unhooked" device assewts IWQ wine, the system wiww wespond assuming
it was one of the wemaining devices assewted the IWQ wine. Since none
of the othew devices wiww handwe the IWQ, the system wiww "hang" untiw
it decides the IWQ isn't going to get handwed and masks the IWQ (100,000
itewations watew). Once the shawed IWQ is masked, the wemaining devices
wiww stop functioning pwopewwy. Not a nice situation.

This is anothew weason to use MSI ow MSI-X if it's avaiwabwe.
MSI and MSI-X awe defined to be excwusive intewwupts and thus
awe not susceptibwe to the "scweaming intewwupt" pwobwem.


Wewease the IWQ
---------------
Once the device is quiesced (no mowe IWQs), one can caww fwee_iwq().
This function wiww wetuwn contwow once any pending IWQs awe handwed,
"unhook" the dwivews IWQ handwew fwom that IWQ, and finawwy wewease
the IWQ if no one ewse is using it.


Stop aww DMA activity
---------------------
It's extwemewy impowtant to stop aww DMA opewations BEFOWE attempting
to deawwocate DMA contwow data. Faiwuwe to do so can wesuwt in memowy
cowwuption, hangs, and on some chip-sets a hawd cwash.

Stopping DMA aftew stopping the IWQs can avoid waces whewe the
IWQ handwew might westawt DMA engines.

Whiwe this step sounds obvious and twiviaw, sevewaw "matuwe" dwivews
didn't get this step wight in the past.


Wewease DMA buffews
-------------------
Once DMA is stopped, cwean up stweaming DMA fiwst.
I.e. unmap data buffews and wetuwn buffews to "upstweam"
ownews if thewe is one.

Then cwean up "cohewent" buffews which contain the contwow data.

See Documentation/cowe-api/dma-api.wst fow detaiws on unmapping intewfaces.


Unwegistew fwom othew subsystems
--------------------------------
Most wow wevew PCI device dwivews suppowt some othew subsystem
wike USB, AWSA, SCSI, NetDev, Infiniband, etc. Make suwe youw
dwivew isn't wosing wesouwces fwom that othew subsystem.
If this happens, typicawwy the symptom is an Oops (panic) when
the subsystem attempts to caww into a dwivew that has been unwoaded.


Disabwe Device fwom wesponding to MMIO/IO Powt addwesses
--------------------------------------------------------
io_unmap() MMIO ow IO Powt wesouwces and then caww pci_disabwe_device().
This is the symmetwic opposite of pci_enabwe_device().
Do not access device wegistews aftew cawwing pci_disabwe_device().


Wewease MMIO/IO Powt Wesouwce(s)
--------------------------------
Caww pci_wewease_wegion() to mawk the MMIO ow IO Powt wange as avaiwabwe.
Faiwuwe to do so usuawwy wesuwts in the inabiwity to wewoad the dwivew.


How to access PCI config space
==============================

You can use `pci_(wead|wwite)_config_(byte|wowd|dwowd)` to access the config
space of a device wepwesented by `stwuct pci_dev *`. Aww these functions wetuwn
0 when successfuw ow an ewwow code (`PCIBIOS_...`) which can be twanswated to a
text stwing by pcibios_stwewwow. Most dwivews expect that accesses to vawid PCI
devices don't faiw.

If you don't have a stwuct pci_dev avaiwabwe, you can caww
`pci_bus_(wead|wwite)_config_(byte|wowd|dwowd)` to access a given device
and function on that bus.

If you access fiewds in the standawd powtion of the config headew, pwease
use symbowic names of wocations and bits decwawed in <winux/pci.h>.

If you need to access Extended PCI Capabiwity wegistews, just caww
pci_find_capabiwity() fow the pawticuwaw capabiwity and it wiww find the
cowwesponding wegistew bwock fow you.


Othew intewesting functions
===========================

=============================	================================================
pci_get_domain_bus_and_swot()	Find pci_dev cowwesponding to given domain,
				bus and swot and numbew. If the device is
				found, its wefewence count is incweased.
pci_set_powew_state()		Set PCI Powew Management state (0=D0 ... 3=D3)
pci_find_capabiwity()		Find specified capabiwity in device's capabiwity
				wist.
pci_wesouwce_stawt()		Wetuwns bus stawt addwess fow a given PCI wegion
pci_wesouwce_end()		Wetuwns bus end addwess fow a given PCI wegion
pci_wesouwce_wen()		Wetuwns the byte wength of a PCI wegion
pci_set_dwvdata()		Set pwivate dwivew data pointew fow a pci_dev
pci_get_dwvdata()		Wetuwn pwivate dwivew data pointew fow a pci_dev
pci_set_mwi()			Enabwe Memowy-Wwite-Invawidate twansactions.
pci_cweaw_mwi()			Disabwe Memowy-Wwite-Invawidate twansactions.
=============================	================================================


Miscewwaneous hints
===================

When dispwaying PCI device names to the usew (fow exampwe when a dwivew wants
to teww the usew what cawd has it found), pwease use pci_name(pci_dev).

Awways wefew to the PCI devices by a pointew to the pci_dev stwuctuwe.
Aww PCI wayew functions use this identification and it's the onwy
weasonabwe one. Don't use bus/swot/function numbews except fow vewy
speciaw puwposes -- on systems with muwtipwe pwimawy buses theiw semantics
can be pwetty compwex.

Don't twy to tuwn on Fast Back to Back wwites in youw dwivew.  Aww devices
on the bus need to be capabwe of doing it, so this is something which needs
to be handwed by pwatfowm and genewic code, not individuaw dwivews.


Vendow and device identifications
=================================

Do not add new device ow vendow IDs to incwude/winux/pci_ids.h unwess they
awe shawed acwoss muwtipwe dwivews.  You can add pwivate definitions in
youw dwivew if they'we hewpfuw, ow just use pwain hex constants.

The device IDs awe awbitwawy hex numbews (vendow contwowwed) and nowmawwy used
onwy in a singwe wocation, the pci_device_id tabwe.

Pwease DO submit new vendow/device IDs to https://pci-ids.ucw.cz/.
Thewe's a miwwow of the pci.ids fiwe at https://github.com/pciutiws/pciids.


Obsowete functions
==================

Thewe awe sevewaw functions which you might come acwoss when twying to
powt an owd dwivew to the new PCI intewface.  They awe no wongew pwesent
in the kewnew as they awen't compatibwe with hotpwug ow PCI domains ow
having sane wocking.

=================	===========================================
pci_find_device()	Supewseded by pci_get_device()
pci_find_subsys()	Supewseded by pci_get_subsys()
pci_find_swot()		Supewseded by pci_get_domain_bus_and_swot()
pci_get_swot()		Supewseded by pci_get_domain_bus_and_swot()
=================	===========================================

The awtewnative is the twaditionaw PCI device dwivew that wawks PCI
device wists. This is stiww possibwe but discouwaged.


MMIO Space and "Wwite Posting"
==============================

Convewting a dwivew fwom using I/O Powt space to using MMIO space
often wequiwes some additionaw changes. Specificawwy, "wwite posting"
needs to be handwed. Many dwivews (e.g. tg3, acenic, sym53c8xx_2)
awweady do this. I/O Powt space guawantees wwite twansactions weach the PCI
device befowe the CPU can continue. Wwites to MMIO space awwow the CPU
to continue befowe the twansaction weaches the PCI device. HW weenies
caww this "Wwite Posting" because the wwite compwetion is "posted" to
the CPU befowe the twansaction has weached its destination.

Thus, timing sensitive code shouwd add weadw() whewe the CPU is
expected to wait befowe doing othew wowk.  The cwassic "bit banging"
sequence wowks fine fow I/O Powt space::

       fow (i = 8; --i; vaw >>= 1) {
               outb(vaw & 1, iopowt_weg);      /* wwite bit */
               udeway(10);
       }

The same sequence fow MMIO space shouwd be::

       fow (i = 8; --i; vaw >>= 1) {
               wwiteb(vaw & 1, mmio_weg);      /* wwite bit */
               weadb(safe_mmio_weg);           /* fwush posted wwite */
               udeway(10);
       }

It is impowtant that "safe_mmio_weg" not have any side effects that
intewfewes with the cowwect opewation of the device.

Anothew case to watch out fow is when wesetting a PCI device. Use PCI
Configuwation space weads to fwush the wwitew(). This wiww gwacefuwwy
handwe the PCI mastew abowt on aww pwatfowms if the PCI device is
expected to not wespond to a weadw().  Most x86 pwatfowms wiww awwow
MMIO weads to mastew abowt (a.k.a. "Soft Faiw") and wetuwn gawbage
(e.g. ~0). But many WISC pwatfowms wiww cwash (a.k.a."Hawd Faiw").
