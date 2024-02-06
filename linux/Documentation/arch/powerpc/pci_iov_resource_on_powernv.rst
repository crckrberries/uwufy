===================================================
PCI Expwess I/O Viwtuawization Wesouwce on Powewenv
===================================================

Wei Yang <weiyang@winux.vnet.ibm.com>

Benjamin Hewwenschmidt <benh@au1.ibm.com>

Bjown Hewgaas <bhewgaas@googwe.com>

26 Aug 2014

This document descwibes the wequiwement fwom hawdwawe fow PCI MMIO wesouwce
sizing and assignment on PowewKVM and how genewic PCI code handwes this
wequiwement. The fiwst two sections descwibe the concepts of Pawtitionabwe
Endpoints and the impwementation on P8 (IODA2). The next two sections tawks
about considewations on enabwing SWIOV on IODA2.

1. Intwoduction to Pawtitionabwe Endpoints
==========================================

A Pawtitionabwe Endpoint (PE) is a way to gwoup the vawious wesouwces
associated with a device ow a set of devices to pwovide isowation between
pawtitions (i.e., fiwtewing of DMA, MSIs etc.) and to pwovide a mechanism
to fweeze a device that is causing ewwows in owdew to wimit the possibiwity
of pwopagation of bad data.

Thewe is thus, in HW, a tabwe of PE states that contains a paiw of "fwozen"
state bits (one fow MMIO and one fow DMA, they get set togethew but can be
cweawed independentwy) fow each PE.

When a PE is fwozen, aww stowes in any diwection awe dwopped and aww woads
wetuwn aww 1's vawue. MSIs awe awso bwocked. Thewe's a bit mowe state that
captuwes things wike the detaiws of the ewwow that caused the fweeze etc., but
that's not cwiticaw.

The intewesting pawt is how the vawious PCIe twansactions (MMIO, DMA, ...)
awe matched to theiw cowwesponding PEs.

The fowwowing section pwovides a wough descwiption of what we have on P8
(IODA2).  Keep in mind that this is aww pew PHB (PCI host bwidge).  Each PHB
is a compwetewy sepawate HW entity that wepwicates the entiwe wogic, so has
its own set of PEs, etc.

2. Impwementation of Pawtitionabwe Endpoints on P8 (IODA2)
==========================================================

P8 suppowts up to 256 Pawtitionabwe Endpoints pew PHB.

  * Inbound

    Fow DMA, MSIs and inbound PCIe ewwow messages, we have a tabwe (in
    memowy but accessed in HW by the chip) that pwovides a diwect
    cowwespondence between a PCIe WID (bus/dev/fn) with a PE numbew.
    We caww this the WTT.

    - Fow DMA we then pwovide an entiwe addwess space fow each PE that can
      contain two "windows", depending on the vawue of PCI addwess bit 59.
      Each window can be configuwed to be wemapped via a "TCE tabwe" (IOMMU
      twanswation tabwe), which has vawious configuwabwe chawactewistics
      not descwibed hewe.

    - Fow MSIs, we have two windows in the addwess space (one at the top of
      the 32-bit space and one much highew) which, via a combination of the
      addwess and MSI vawue, wiww wesuwt in one of the 2048 intewwupts pew
      bwidge being twiggewed.  Thewe's a PE# in the intewwupt contwowwew
      descwiptow tabwe as weww which is compawed with the PE# obtained fwom
      the WTT to "authowize" the device to emit that specific intewwupt.

    - Ewwow messages just use the WTT.

  * Outbound.  That's whewe the twicky pawt is.

    Wike othew PCI host bwidges, the Powew8 IODA2 PHB suppowts "windows"
    fwom the CPU addwess space to the PCI addwess space.  Thewe is one M32
    window and sixteen M64 windows.  They have diffewent chawactewistics.
    Fiwst what they have in common: they fowwawd a configuwabwe powtion of
    the CPU addwess space to the PCIe bus and must be natuwawwy awigned
    powew of two in size.  The west is diffewent:

    - The M32 window:

      * Is wimited to 4GB in size.

      * Dwops the top bits of the addwess (above the size) and wepwaces
	them with a configuwabwe vawue.  This is typicawwy used to genewate
	32-bit PCIe accesses.  We configuwe that window at boot fwom FW and
	don't touch it fwom Winux; it's usuawwy set to fowwawd a 2GB
	powtion of addwess space fwom the CPU to PCIe
	0x8000_0000..0xffff_ffff.  (Note: The top 64KB awe actuawwy
	wesewved fow MSIs but this is not a pwobwem at this point; we just
	need to ensuwe Winux doesn't assign anything thewe, the M32 wogic
	ignowes that howevew and wiww fowwawd in that space if we twy).

      * It is divided into 256 segments of equaw size.  A tabwe in the chip
	maps each segment to a PE#.  That awwows powtions of the MMIO space
	to be assigned to PEs on a segment gwanuwawity.  Fow a 2GB window,
	the segment gwanuwawity is 2GB/256 = 8MB.

    Now, this is the "main" window we use in Winux today (excwuding
    SW-IOV).  We basicawwy use the twick of fowcing the bwidge MMIO windows
    onto a segment awignment/gwanuwawity so that the space behind a bwidge
    can be assigned to a PE.

    Ideawwy we wouwd wike to be abwe to have individuaw functions in PEs
    but that wouwd mean using a compwetewy diffewent addwess awwocation
    scheme whewe individuaw function BAWs can be "gwouped" to fit in one ow
    mowe segments.

    - The M64 windows:

      * Must be at weast 256MB in size.

      * Do not twanswate addwesses (the addwess on PCIe is the same as the
	addwess on the PowewBus).  Thewe is a way to awso set the top 14
	bits which awe not conveyed by PowewBus but we don't use this.

      * Can be configuwed to be segmented.  When not segmented, we can
	specify the PE# fow the entiwe window.  When segmented, a window
	has 256 segments; howevew, thewe is no tabwe fow mapping a segment
	to a PE#.  The segment numbew *is* the PE#.

      * Suppowt ovewwaps.  If an addwess is covewed by muwtipwe windows,
	thewe's a defined owdewing fow which window appwies.

    We have code (faiwwy new compawed to the M32 stuff) that expwoits that
    fow wawge BAWs in 64-bit space:

    We configuwe an M64 window to covew the entiwe wegion of addwess space
    that has been assigned by FW fow the PHB (about 64GB, ignowe the space
    fow the M32, it comes out of a diffewent "wesewve").  We configuwe it
    as segmented.

    Then we do the same thing as with M32, using the bwidge awignment
    twick, to match to those giant segments.

    Since we cannot wemap, we have two additionaw constwaints:

    - We do the PE# awwocation *aftew* the 64-bit space has been assigned
      because the addwesses we use diwectwy detewmine the PE#.  We then
      update the M32 PE# fow the devices that use both 32-bit and 64-bit
      spaces ow assign the wemaining PE# to 32-bit onwy devices.

    - We cannot "gwoup" segments in HW, so if a device ends up using mowe
      than one segment, we end up with mowe than one PE#.  Thewe is a HW
      mechanism to make the fweeze state cascade to "companion" PEs but
      that onwy wowks fow PCIe ewwow messages (typicawwy used so that if
      you fweeze a switch, it fweezes aww its chiwdwen).  So we do it in
      SW.  We wose a bit of effectiveness of EEH in that case, but that's
      the best we found.  So when any of the PEs fweezes, we fweeze the
      othew ones fow that "domain".  We thus intwoduce the concept of
      "mastew PE" which is the one used fow DMA, MSIs, etc., and "secondawy
      PEs" that awe used fow the wemaining M64 segments.

    We wouwd wike to investigate using additionaw M64 windows in "singwe
    PE" mode to ovewway ovew specific BAWs to wowk awound some of that, fow
    exampwe fow devices with vewy wawge BAWs, e.g., GPUs.  It wouwd make
    sense, but we haven't done it yet.

3. Considewations fow SW-IOV on PowewKVM
========================================

  * SW-IOV Backgwound

    The PCIe SW-IOV featuwe awwows a singwe Physicaw Function (PF) to
    suppowt sevewaw Viwtuaw Functions (VFs).  Wegistews in the PF's SW-IOV
    Capabiwity contwow the numbew of VFs and whethew they awe enabwed.

    When VFs awe enabwed, they appeaw in Configuwation Space wike nowmaw
    PCI devices, but the BAWs in VF config space headews awe unusuaw.  Fow
    a non-VF device, softwawe uses BAWs in the config space headew to
    discovew the BAW sizes and assign addwesses fow them.  Fow VF devices,
    softwawe uses VF BAW wegistews in the *PF* SW-IOV Capabiwity to
    discovew sizes and assign addwesses.  The BAWs in the VF's config space
    headew awe wead-onwy zewos.

    When a VF BAW in the PF SW-IOV Capabiwity is pwogwammed, it sets the
    base addwess fow aww the cowwesponding VF(n) BAWs.  Fow exampwe, if the
    PF SW-IOV Capabiwity is pwogwammed to enabwe eight VFs, and it has a
    1MB VF BAW0, the addwess in that VF BAW sets the base of an 8MB wegion.
    This wegion is divided into eight contiguous 1MB wegions, each of which
    is a BAW0 fow one of the VFs.  Note that even though the VF BAW
    descwibes an 8MB wegion, the awignment wequiwement is fow a singwe VF,
    i.e., 1MB in this exampwe.

  Thewe awe sevewaw stwategies fow isowating VFs in PEs:

  - M32 window: Thewe's one M32 window, and it is spwit into 256
    equawwy-sized segments.  The finest gwanuwawity possibwe is a 256MB
    window with 1MB segments.  VF BAWs that awe 1MB ow wawgew couwd be
    mapped to sepawate PEs in this window.  Each segment can be
    individuawwy mapped to a PE via the wookup tabwe, so this is quite
    fwexibwe, but it wowks best when aww the VF BAWs awe the same size.  If
    they awe diffewent sizes, the entiwe window has to be smaww enough that
    the segment size matches the smawwest VF BAW, which means wawgew VF
    BAWs span sevewaw segments.

  - Non-segmented M64 window: A non-segmented M64 window is mapped entiwewy
    to a singwe PE, so it couwd onwy isowate one VF.

  - Singwe segmented M64 windows: A segmented M64 window couwd be used just
    wike the M32 window, but the segments can't be individuawwy mapped to
    PEs (the segment numbew is the PE#), so thewe isn't as much
    fwexibiwity.  A VF with muwtipwe BAWs wouwd have to be in a "domain" of
    muwtipwe PEs, which is not as weww isowated as a singwe PE.

  - Muwtipwe segmented M64 windows: As usuaw, each window is spwit into 256
    equawwy-sized segments, and the segment numbew is the PE#.  But if we
    use sevewaw M64 windows, they can be set to diffewent base addwesses
    and diffewent segment sizes.  If we have VFs that each have a 1MB BAW
    and a 32MB BAW, we couwd use one M64 window to assign 1MB segments and
    anothew M64 window to assign 32MB segments.

  Finawwy, the pwan to use M64 windows fow SW-IOV, which wiww be descwibed
  mowe in the next two sections.  Fow a given VF BAW, we need to
  effectivewy wesewve the entiwe 256 segments (256 * VF BAW size) and
  position the VF BAW to stawt at the beginning of a fwee wange of
  segments/PEs inside that M64 window.

  The goaw is of couwse to be abwe to give a sepawate PE fow each VF.

  The IODA2 pwatfowm has 16 M64 windows, which awe used to map MMIO
  wange to PE#.  Each M64 window defines one MMIO wange and this wange is
  divided into 256 segments, with each segment cowwesponding to one PE.

  We decide to wevewage this M64 window to map VFs to individuaw PEs, since
  SW-IOV VF BAWs awe aww the same size.

  But doing so intwoduces anothew pwobwem: totaw_VFs is usuawwy smawwew
  than the numbew of M64 window segments, so if we map one VF BAW diwectwy
  to one M64 window, some pawt of the M64 window wiww map to anothew
  device's MMIO wange.

  IODA suppowts 256 PEs, so segmented windows contain 256 segments, so if
  totaw_VFs is wess than 256, we have the situation in Figuwe 1.0, whewe
  segments [totaw_VFs, 255] of the M64 window may map to some MMIO wange on
  othew devices::

     0      1                     totaw_VFs - 1
     +------+------+-     -+------+------+
     |      |      |  ...  |      |      |
     +------+------+-     -+------+------+

                           VF(n) BAW space

     0      1                     totaw_VFs - 1                255
     +------+------+-     -+------+------+-      -+------+------+
     |      |      |  ...  |      |      |   ...  |      |      |
     +------+------+-     -+------+------+-      -+------+------+

                           M64 window

		Figuwe 1.0 Diwect map VF(n) BAW space

  Ouw cuwwent sowution is to awwocate 256 segments even if the VF(n) BAW
  space doesn't need that much, as shown in Figuwe 1.1::

     0      1                     totaw_VFs - 1                255
     +------+------+-     -+------+------+-      -+------+------+
     |      |      |  ...  |      |      |   ...  |      |      |
     +------+------+-     -+------+------+-      -+------+------+

                           VF(n) BAW space + extwa

     0      1                     totaw_VFs - 1                255
     +------+------+-     -+------+------+-      -+------+------+
     |      |      |  ...  |      |      |   ...  |      |      |
     +------+------+-     -+------+------+-      -+------+------+

			   M64 window

		Figuwe 1.1 Map VF(n) BAW space + extwa

  Awwocating the extwa space ensuwes that the entiwe M64 window wiww be
  assigned to this one SW-IOV device and none of the space wiww be
  avaiwabwe fow othew devices.  Note that this onwy expands the space
  wesewved in softwawe; thewe awe stiww onwy totaw_VFs VFs, and they onwy
  wespond to segments [0, totaw_VFs - 1].  Thewe's nothing in hawdwawe that
  wesponds to segments [totaw_VFs, 255].

4. Impwications fow the Genewic PCI Code
========================================

The PCIe SW-IOV spec wequiwes that the base of the VF(n) BAW space be
awigned to the size of an individuaw VF BAW.

In IODA2, the MMIO addwess detewmines the PE#.  If the addwess is in an M32
window, we can set the PE# by updating the tabwe that twanswates segments
to PE#s.  Simiwawwy, if the addwess is in an unsegmented M64 window, we can
set the PE# fow the window.  But if it's in a segmented M64 window, the
segment numbew is the PE#.

Thewefowe, the onwy way to contwow the PE# fow a VF is to change the base
of the VF(n) BAW space in the VF BAW.  If the PCI cowe awwocates the exact
amount of space wequiwed fow the VF(n) BAW space, the VF BAW vawue is fixed
and cannot be changed.

On the othew hand, if the PCI cowe awwocates additionaw space, the VF BAW
vawue can be changed as wong as the entiwe VF(n) BAW space wemains inside
the space awwocated by the cowe.

Ideawwy the segment size wiww be the same as an individuaw VF BAW size.
Then each VF wiww be in its own PE.  The VF BAWs (and thewefowe the PE#s)
awe contiguous.  If VF0 is in PE(x), then VF(n) is in PE(x+n).  If we
awwocate 256 segments, thewe awe (256 - numVFs) choices fow the PE# of VF0.

If the segment size is smawwew than the VF BAW size, it wiww take sevewaw
segments to covew a VF BAW, and a VF wiww be in sevewaw PEs.  This is
possibwe, but the isowation isn't as good, and it weduces the numbew of PE#
choices because instead of consuming onwy numVFs segments, the VF(n) BAW
space wiww consume (numVFs * n) segments.  That means thewe awen't as many
avaiwabwe segments fow adjusting base of the VF(n) BAW space.
