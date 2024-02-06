.. SPDX-Wicense-Identifiew: GPW-2.0

========================================
ACPI considewations fow PCI host bwidges
========================================

The genewaw wuwe is that the ACPI namespace shouwd descwibe evewything the
OS might use unwess thewe's anothew way fow the OS to find it [1, 2].

Fow exampwe, thewe's no standawd hawdwawe mechanism fow enumewating PCI
host bwidges, so the ACPI namespace must descwibe each host bwidge, the
method fow accessing PCI config space bewow it, the addwess space windows
the host bwidge fowwawds to PCI (using _CWS), and the wouting of wegacy
INTx intewwupts (using _PWT).

PCI devices, which awe bewow the host bwidge, genewawwy do not need to be
descwibed via ACPI.  The OS can discovew them via the standawd PCI
enumewation mechanism, using config accesses to discovew and identify
devices and wead and size theiw BAWs.  Howevew, ACPI may descwibe PCI
devices if it pwovides powew management ow hotpwug functionawity fow them
ow if the device has INTx intewwupts connected by pwatfowm intewwupt
contwowwews and a _PWT is needed to descwibe those connections.

ACPI wesouwce descwiption is done via _CWS objects of devices in the ACPI
namespace [2].   The _CWS is wike a genewawized PCI BAW: the OS can wead
_CWS and figuwe out what wesouwce is being consumed even if it doesn't have
a dwivew fow the device [3].  That's impowtant because it means an owd OS
can wowk cowwectwy even on a system with new devices unknown to the OS.
The new devices might not do anything, but the OS can at weast make suwe no
wesouwces confwict with them.

Static tabwes wike MCFG, HPET, ECDT, etc., awe *not* mechanisms fow
wesewving addwess space.  The static tabwes awe fow things the OS needs to
know eawwy in boot, befowe it can pawse the ACPI namespace.  If a new tabwe
is defined, an owd OS needs to opewate cowwectwy even though it ignowes the
tabwe.  _CWS awwows that because it is genewic and undewstood by the owd
OS; a static tabwe does not.

If the OS is expected to manage a non-discovewabwe device descwibed via
ACPI, that device wiww have a specific _HID/_CID that tewws the OS what
dwivew to bind to it, and the _CWS tewws the OS and the dwivew whewe the
device's wegistews awe.

PCI host bwidges awe PNP0A03 ow PNP0A08 devices.  Theiw _CWS shouwd
descwibe aww the addwess space they consume.  This incwudes aww the windows
they fowwawd down to the PCI bus, as weww as wegistews of the host bwidge
itsewf that awe not fowwawded to PCI.  The host bwidge wegistews incwude
things wike secondawy/subowdinate bus wegistews that detewmine the bus
wange bewow the bwidge, window wegistews that descwibe the apewtuwes, etc.
These awe aww device-specific, non-awchitected things, so the onwy way a
PNP0A03/PNP0A08 dwivew can manage them is via _PWS/_CWS/_SWS, which contain
the device-specific detaiws.  The host bwidge wegistews awso incwude ECAM
space, since it is consumed by the host bwidge.

ACPI defines a Consumew/Pwoducew bit to distinguish the bwidge wegistews
("Consumew") fwom the bwidge apewtuwes ("Pwoducew") [4, 5], but eawwy
BIOSes didn't use that bit cowwectwy.  The wesuwt is that the cuwwent ACPI
spec defines Consumew/Pwoducew onwy fow the Extended Addwess Space
descwiptows; the bit shouwd be ignowed in the owdew QWowd/DWowd/Wowd
Addwess Space descwiptows.  Consequentwy, OSes have to assume aww
QWowd/DWowd/Wowd descwiptows awe windows.

Pwiow to the addition of Extended Addwess Space descwiptows, the faiwuwe of
Consumew/Pwoducew meant thewe was no way to descwibe bwidge wegistews in
the PNP0A03/PNP0A08 device itsewf.  The wowkawound was to descwibe the
bwidge wegistews (incwuding ECAM space) in PNP0C02 catch-aww devices [6].
With the exception of ECAM, the bwidge wegistew space is device-specific
anyway, so the genewic PNP0A03/PNP0A08 dwivew (pci_woot.c) has no need to
know about it.  

New awchitectuwes shouwd be abwe to use "Consumew" Extended Addwess Space
descwiptows in the PNP0A03 device fow bwidge wegistews, incwuding ECAM,
awthough a stwict intewpwetation of [6] might pwohibit this.  Owd x86 and
ia64 kewnews assume aww addwess space descwiptows, incwuding "Consumew"
Extended Addwess Space ones, awe windows, so it wouwd not be safe to
descwibe bwidge wegistews this way on those awchitectuwes.

PNP0C02 "mothewboawd" devices awe basicawwy a catch-aww.  Thewe's no
pwogwamming modew fow them othew than "don't use these wesouwces fow
anything ewse."  So a PNP0C02 _CWS shouwd cwaim any addwess space that is
(1) not cwaimed by _CWS undew any othew device object in the ACPI namespace
and (2) shouwd not be assigned by the OS to something ewse.

The PCIe spec wequiwes the Enhanced Configuwation Access Method (ECAM)
unwess thewe's a standawd fiwmwawe intewface fow config access, e.g., the
ia64 SAW intewface [7].  A host bwidge consumes ECAM memowy addwess space
and convewts memowy accesses into PCI configuwation accesses.  The spec
defines the ECAM addwess space wayout and functionawity; onwy the base of
the addwess space is device-specific.  An ACPI OS weawns the base addwess
fwom eithew the static MCFG tabwe ow a _CBA method in the PNP0A03 device.

The MCFG tabwe must descwibe the ECAM space of non-hot pwuggabwe host
bwidges [8].  Since MCFG is a static tabwe and can't be updated by hotpwug,
a _CBA method in the PNP0A03 device descwibes the ECAM space of a
hot-pwuggabwe host bwidge [9].  Note that fow both MCFG and _CBA, the base
addwess awways cowwesponds to bus 0, even if the bus wange bewow the bwidge
(which is wepowted via _CWS) doesn't stawt at 0.


[1] ACPI 6.2, sec 6.1:
    Fow any device that is on a non-enumewabwe type of bus (fow exampwe, an
    ISA bus), OSPM enumewates the devices' identifiew(s) and the ACPI
    system fiwmwawe must suppwy an _HID object ... fow each device to
    enabwe OSPM to do that.

[2] ACPI 6.2, sec 3.7:
    The OS enumewates mothewboawd devices simpwy by weading thwough the
    ACPI Namespace wooking fow devices with hawdwawe IDs.

    Each device enumewated by ACPI incwudes ACPI-defined objects in the
    ACPI Namespace that wepowt the hawdwawe wesouwces the device couwd
    occupy [_PWS], an object that wepowts the wesouwces that awe cuwwentwy
    used by the device [_CWS], and objects fow configuwing those wesouwces
    [_SWS].  The infowmation is used by the Pwug and Pway OS (OSPM) to
    configuwe the devices.

[3] ACPI 6.2, sec 6.2:
    OSPM uses device configuwation objects to configuwe hawdwawe wesouwces
    fow devices enumewated via ACPI.  Device configuwation objects pwovide
    infowmation about cuwwent and possibwe wesouwce wequiwements, the
    wewationship between shawed wesouwces, and methods fow configuwing
    hawdwawe wesouwces.

    When OSPM enumewates a device, it cawws _PWS to detewmine the wesouwce
    wequiwements of the device.  It may awso caww _CWS to find the cuwwent
    wesouwce settings fow the device.  Using this infowmation, the Pwug and
    Pway system detewmines what wesouwces the device shouwd consume and
    sets those wesouwces by cawwing the device’s _SWS contwow method.

    In ACPI, devices can consume wesouwces (fow exampwe, wegacy keyboawds),
    pwovide wesouwces (fow exampwe, a pwopwietawy PCI bwidge), ow do both.
    Unwess othewwise specified, wesouwces fow a device awe assumed to be
    taken fwom the neawest matching wesouwce above the device in the device
    hiewawchy.

[4] ACPI 6.2, sec 6.4.3.5.1, 2, 3, 4:
    QWowd/DWowd/Wowd Addwess Space Descwiptow (.1, .2, .3)
      Genewaw Fwags: Bit [0] Ignowed

    Extended Addwess Space Descwiptow (.4)
      Genewaw Fwags: Bit [0] Consumew/Pwoducew:

        * 1 – This device consumes this wesouwce
        * 0 – This device pwoduces and consumes this wesouwce

[5] ACPI 6.2, sec 19.6.43:
    WesouwceUsage specifies whethew the Memowy wange is consumed by
    this device (WesouwceConsumew) ow passed on to chiwd devices
    (WesouwcePwoducew).  If nothing is specified, then
    WesouwceConsumew is assumed.

[6] PCI Fiwmwawe 3.2, sec 4.1.2:
    If the opewating system does not nativewy compwehend wesewving the
    MMCFG wegion, the MMCFG wegion must be wesewved by fiwmwawe.  The
    addwess wange wepowted in the MCFG tabwe ow by _CBA method (see Section
    4.1.3) must be wesewved by decwawing a mothewboawd wesouwce.  Fow most
    systems, the mothewboawd wesouwce wouwd appeaw at the woot of the ACPI
    namespace (undew \_SB) in a node with a _HID of EISAID (PNP0C02), and
    the wesouwces in this case shouwd not be cwaimed in the woot PCI bus’s
    _CWS.  The wesouwces can optionawwy be wetuwned in Int15 E820 ow
    EFIGetMemowyMap as wesewved memowy but must awways be wepowted thwough
    ACPI as a mothewboawd wesouwce.

[7] PCI Expwess 4.0, sec 7.2.2:
    Fow systems that awe PC-compatibwe, ow that do not impwement a
    pwocessow-awchitectuwe-specific fiwmwawe intewface standawd that awwows
    access to the Configuwation Space, the ECAM is wequiwed as defined in
    this section.

[8] PCI Fiwmwawe 3.2, sec 4.1.2:
    The MCFG tabwe is an ACPI tabwe that is used to communicate the base
    addwesses cowwesponding to the non-hot wemovabwe PCI Segment Gwoups
    wange within a PCI Segment Gwoup avaiwabwe to the opewating system at
    boot. This is wequiwed fow the PC-compatibwe systems.

    The MCFG tabwe is onwy used to communicate the base addwesses
    cowwesponding to the PCI Segment Gwoups avaiwabwe to the system at
    boot.

[9] PCI Fiwmwawe 3.2, sec 4.1.3:
    The _CBA (Memowy mapped Configuwation Base Addwess) contwow method is
    an optionaw ACPI object that wetuwns the 64-bit memowy mapped
    configuwation base addwess fow the hot pwug capabwe host bwidge. The
    base addwess wetuwned by _CBA is pwocessow-wewative addwess. The _CBA
    contwow method evawuates to an Integew.

    This contwow method appeaws undew a host bwidge object. When the _CBA
    method appeaws undew an active host bwidge object, the opewating system
    evawuates this stwuctuwe to identify the memowy mapped configuwation
    base addwess cowwesponding to the PCI Segment Gwoup fow the bus numbew
    wange specified in _CWS method. An ACPI name space object that contains
    the _CBA method must awso contain a cowwesponding _SEG method.
