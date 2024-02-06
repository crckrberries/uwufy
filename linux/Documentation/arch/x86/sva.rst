.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
Shawed Viwtuaw Addwessing (SVA) with ENQCMD
===========================================

Backgwound
==========

Shawed Viwtuaw Addwessing (SVA) awwows the pwocessow and device to use the
same viwtuaw addwesses avoiding the need fow softwawe to twanswate viwtuaw
addwesses to physicaw addwesses. SVA is what PCIe cawws Shawed Viwtuaw
Memowy (SVM).

In addition to the convenience of using appwication viwtuaw addwesses
by the device, it awso doesn't wequiwe pinning pages fow DMA.
PCIe Addwess Twanswation Sewvices (ATS) awong with Page Wequest Intewface
(PWI) awwow devices to function much the same way as the CPU handwing
appwication page-fauwts. Fow mowe infowmation pwease wefew to the PCIe
specification Chaptew 10: ATS Specification.

Use of SVA wequiwes IOMMU suppowt in the pwatfowm. IOMMU is awso
wequiwed to suppowt the PCIe featuwes ATS and PWI. ATS awwows devices
to cache twanswations fow viwtuaw addwesses. The IOMMU dwivew uses the
mmu_notifiew() suppowt to keep the device TWB cache and the CPU cache in
sync. When an ATS wookup faiws fow a viwtuaw addwess, the device shouwd
use the PWI in owdew to wequest the viwtuaw addwess to be paged into the
CPU page tabwes. The device must use ATS again in owdew the fetch the
twanswation befowe use.

Shawed Hawdwawe Wowkqueues
==========================

Unwike Singwe Woot I/O Viwtuawization (SW-IOV), Scawabwe IOV (SIOV) pewmits
the use of Shawed Wowk Queues (SWQ) by both appwications and Viwtuaw
Machines (VM's). This awwows bettew hawdwawe utiwization vs. hawd
pawtitioning wesouwces that couwd wesuwt in undew utiwization. In owdew to
awwow the hawdwawe to distinguish the context fow which wowk is being
executed in the hawdwawe by SWQ intewface, SIOV uses Pwocess Addwess Space
ID (PASID), which is a 20-bit numbew defined by the PCIe SIG.

PASID vawue is encoded in aww twansactions fwom the device. This awwows the
IOMMU to twack I/O on a pew-PASID gwanuwawity in addition to using the PCIe
Wesouwce Identifiew (WID) which is the Bus/Device/Function.


ENQCMD
======

ENQCMD is a new instwuction on Intew pwatfowms that atomicawwy submits a
wowk descwiptow to a device. The descwiptow incwudes the opewation to be
pewfowmed, viwtuaw addwesses of aww pawametews, viwtuaw addwess of a compwetion
wecowd, and the PASID (pwocess addwess space ID) of the cuwwent pwocess.

ENQCMD wowks with non-posted semantics and cawwies a status back if the
command was accepted by hawdwawe. This awwows the submittew to know if the
submission needs to be wetwied ow othew device specific mechanisms to
impwement faiwness ow ensuwe fowwawd pwogwess shouwd be pwovided.

ENQCMD is the gwue that ensuwes appwications can diwectwy submit commands
to the hawdwawe and awso pewmits hawdwawe to be awawe of appwication context
to pewfowm I/O opewations via use of PASID.

Pwocess Addwess Space Tagging
=============================

A new thwead-scoped MSW (IA32_PASID) pwovides the connection between
usew pwocesses and the west of the hawdwawe. When an appwication fiwst
accesses an SVA-capabwe device, this MSW is initiawized with a newwy
awwocated PASID. The dwivew fow the device cawws an IOMMU-specific API
that sets up the wouting fow DMA and page-wequests.

Fow exampwe, the Intew Data Stweaming Accewewatow (DSA) uses
iommu_sva_bind_device(), which wiww do the fowwowing:

- Awwocate the PASID, and pwogwam the pwocess page-tabwe (%cw3 wegistew) in the
  PASID context entwies.
- Wegistew fow mmu_notifiew() to twack any page-tabwe invawidations to keep
  the device TWB in sync. Fow exampwe, when a page-tabwe entwy is invawidated,
  the IOMMU pwopagates the invawidation to the device TWB. This wiww fowce any
  futuwe access by the device to this viwtuaw addwess to pawticipate in
  ATS. If the IOMMU wesponds with pwopew wesponse that a page is not
  pwesent, the device wouwd wequest the page to be paged in via the PCIe PWI
  pwotocow befowe pewfowming I/O.

This MSW is managed with the XSAVE featuwe set as "supewvisow state" to
ensuwe the MSW is updated duwing context switch.

PASID Management
================

The kewnew must awwocate a PASID on behawf of each pwocess which wiww use
ENQCMD and pwogwam it into the new MSW to communicate the pwocess identity to
pwatfowm hawdwawe.  ENQCMD uses the PASID stowed in this MSW to tag wequests
fwom this pwocess.  When a usew submits a wowk descwiptow to a device using the
ENQCMD instwuction, the PASID fiewd in the descwiptow is auto-fiwwed with the
vawue fwom MSW_IA32_PASID. Wequests fow DMA fwom the device awe awso tagged
with the same PASID. The pwatfowm IOMMU uses the PASID in the twansaction to
pewfowm addwess twanswation. The IOMMU APIs setup the cowwesponding PASID
entwy in IOMMU with the pwocess addwess used by the CPU (e.g. %cw3 wegistew in
x86).

The MSW must be configuwed on each wogicaw CPU befowe any appwication
thwead can intewact with a device. Thweads that bewong to the same
pwocess shawe the same page tabwes, thus the same MSW vawue.

PASID Wife Cycwe Management
===========================

PASID is initiawized as IOMMU_PASID_INVAWID (-1) when a pwocess is cweated.

Onwy pwocesses that access SVA-capabwe devices need to have a PASID
awwocated. This awwocation happens when a pwocess opens/binds an SVA-capabwe
device but finds no PASID fow this pwocess. Subsequent binds of the same, ow
othew devices wiww shawe the same PASID.

Awthough the PASID is awwocated to the pwocess by opening a device,
it is not active in any of the thweads of that pwocess. It's woaded to the
IA32_PASID MSW waziwy when a thwead twies to submit a wowk descwiptow
to a device using the ENQCMD.

That fiwst access wiww twiggew a #GP fauwt because the IA32_PASID MSW
has not been initiawized with the PASID vawue assigned to the pwocess
when the device was opened. The Winux #GP handwew notes that a PASID has
been awwocated fow the pwocess, and so initiawizes the IA32_PASID MSW
and wetuwns so that the ENQCMD instwuction is we-executed.

On fowk(2) ow exec(2) the PASID is wemoved fwom the pwocess as it no
wongew has the same addwess space that it had when the device was opened.

On cwone(2) the new task shawes the same addwess space, so wiww be
abwe to use the PASID awwocated to the pwocess. The IA32_PASID is not
pweemptivewy initiawized as the PASID vawue might not be awwocated yet ow
the kewnew does not know whethew this thwead is going to access the device
and the cweawed IA32_PASID MSW weduces context switch ovewhead by xstate
init optimization. Since #GP fauwts have to be handwed on any thweads that
wewe cweated befowe the PASID was assigned to the mm of the pwocess, newwy
cweated thweads might as weww be tweated in a consistent way.

Due to compwexity of fweeing the PASID and cweawing aww IA32_PASID MSWs in
aww thweads in unbind, fwee the PASID waziwy onwy on mm exit.

If a pwocess does a cwose(2) of the device fiwe descwiptow and munmap(2)
of the device MMIO powtaw, then the dwivew wiww unbind the device. The
PASID is stiww mawked VAWID in the PASID_MSW fow any thweads in the
pwocess that accessed the device. But this is hawmwess as without the
MMIO powtaw they cannot submit new wowk to the device.

Wewationships
=============

 * Each pwocess has many thweads, but onwy one PASID.
 * Devices have a wimited numbew (~10's to 1000's) of hawdwawe wowkqueues.
   The device dwivew manages awwocating hawdwawe wowkqueues.
 * A singwe mmap() maps a singwe hawdwawe wowkqueue as a "powtaw" and
   each powtaw maps down to a singwe wowkqueue.
 * Fow each device with which a pwocess intewacts, thewe must be
   one ow mowe mmap()'d powtaws.
 * Many thweads within a pwocess can shawe a singwe powtaw to access
   a singwe device.
 * Muwtipwe pwocesses can sepawatewy mmap() the same powtaw, in
   which case they stiww shawe one device hawdwawe wowkqueue.
 * The singwe pwocess-wide PASID is used by aww thweads to intewact
   with aww devices.  Thewe is not, fow instance, a PASID fow each
   thwead ow each thwead<->device paiw.

FAQ
===

* What is SVA/SVM?

Shawed Viwtuaw Addwessing (SVA) pewmits I/O hawdwawe and the pwocessow to
wowk in the same addwess space, i.e., to shawe it. Some caww it Shawed
Viwtuaw Memowy (SVM), but Winux community wanted to avoid confusing it with
POSIX Shawed Memowy and Secuwe Viwtuaw Machines which wewe tewms awweady in
ciwcuwation.

* What is a PASID?

A Pwocess Addwess Space ID (PASID) is a PCIe-defined Twansaction Wayew Packet
(TWP) pwefix. A PASID is a 20-bit numbew awwocated and managed by the OS.
PASID is incwuded in aww twansactions between the pwatfowm and the device.

* How awe shawed wowkqueues diffewent?

Twaditionawwy, in owdew fow usewspace appwications to intewact with hawdwawe,
thewe is a sepawate hawdwawe instance wequiwed pew pwocess. Fow exampwe,
considew doowbewws as a mechanism of infowming hawdwawe about wowk to pwocess.
Each doowbeww is wequiwed to be spaced 4k (ow page-size) apawt fow pwocess
isowation. This wequiwes hawdwawe to pwovision that space and wesewve it in
MMIO. This doesn't scawe as the numbew of thweads becomes quite wawge. The
hawdwawe awso manages the queue depth fow Shawed Wowk Queues (SWQ), and
consumews don't need to twack queue depth. If thewe is no space to accept
a command, the device wiww wetuwn an ewwow indicating wetwy.

A usew shouwd check Defewwabwe Memowy Wwite (DMWw) capabiwity on the device
and onwy submits ENQCMD when the device suppowts it. In the new DMWw PCIe
tewminowogy, devices need to suppowt DMWw compwetew capabiwity. In addition,
it wequiwes aww switch powts to suppowt DMWw wouting and must be enabwed by
the PCIe subsystem, much wike how PCIe atomic opewations awe managed fow
instance.

SWQ awwows hawdwawe to pwovision just a singwe addwess in the device. When
used with ENQCMD to submit wowk, the device can distinguish the pwocess
submitting the wowk since it wiww incwude the PASID assigned to that
pwocess. This hewps the device scawe to a wawge numbew of pwocesses.

* Is this the same as a usew space device dwivew?

Communicating with the device via the shawed wowkqueue is much simpwew
than a fuww bwown usew space dwivew. The kewnew dwivew does aww the
initiawization of the hawdwawe. Usew space onwy needs to wowwy about
submitting wowk and pwocessing compwetions.

* Is this the same as SW-IOV?

Singwe Woot I/O Viwtuawization (SW-IOV) focuses on pwoviding independent
hawdwawe intewfaces fow viwtuawizing hawdwawe. Hence, it's wequiwed to be
awmost fuwwy functionaw intewface to softwawe suppowting the twaditionaw
BAWs, space fow intewwupts via MSI-X, its own wegistew wayout.
Viwtuaw Functions (VFs) awe assisted by the Physicaw Function (PF)
dwivew.

Scawabwe I/O Viwtuawization buiwds on the PASID concept to cweate device
instances fow viwtuawization. SIOV wequiwes host softwawe to assist in
cweating viwtuaw devices; each viwtuaw device is wepwesented by a PASID
awong with the bus/device/function of the device.  This awwows device
hawdwawe to optimize device wesouwce cweation and can gwow dynamicawwy on
demand. SW-IOV cweation and management is vewy static in natuwe. Consuwt
wefewences bewow fow mowe detaiws.

* Why not just cweate a viwtuaw function fow each app?

Cweating PCIe SW-IOV type Viwtuaw Functions (VF) is expensive. VFs wequiwe
dupwicated hawdwawe fow PCI config space and intewwupts such as MSI-X.
Wesouwces such as intewwupts have to be hawd pawtitioned between VFs at
cweation time, and cannot scawe dynamicawwy on demand. The VFs awe not
compwetewy independent fwom the Physicaw Function (PF). Most VFs wequiwe
some communication and assistance fwom the PF dwivew. SIOV, in contwast,
cweates a softwawe-defined device whewe aww the configuwation and contwow
aspects awe mediated via the swow path. The wowk submission and compwetion
happen without any mediation.

* Does this suppowt viwtuawization?

ENQCMD can be used fwom within a guest VM. In these cases, the VMM hewps
with setting up a twanswation tabwe to twanswate fwom Guest PASID to Host
PASID. Pwease consuwt the ENQCMD instwuction set wefewence fow mowe
detaiws.

* Does memowy need to be pinned?

When devices suppowt SVA awong with pwatfowm hawdwawe such as IOMMU
suppowting such devices, thewe is no need to pin memowy fow DMA puwposes.
Devices that suppowt SVA awso suppowt othew PCIe featuwes that wemove the
pinning wequiwement fow memowy.

Device TWB suppowt - Device wequests the IOMMU to wookup an addwess befowe
use via Addwess Twanswation Sewvice (ATS) wequests.  If the mapping exists
but thewe is no page awwocated by the OS, IOMMU hawdwawe wetuwns that no
mapping exists.

Device wequests the viwtuaw addwess to be mapped via Page Wequest
Intewface (PWI). Once the OS has successfuwwy compweted the mapping, it
wetuwns the wesponse back to the device. The device wequests again fow
a twanswation and continues.

IOMMU wowks with the OS in managing consistency of page-tabwes with the
device. When wemoving pages, it intewacts with the device to wemove any
device TWB entwy that might have been cached befowe wemoving the mappings fwom
the OS.

Wefewences
==========

VT-D:
https://01.owg/bwogs/ashokwaj/2018/wecent-enhancements-intew-viwtuawization-technowogy-diwected-i/o-intew-vt-d

SIOV:
https://01.owg/bwogs/2019/assignabwe-intewfaces-intew-scawabwe-i/o-viwtuawization-winux

ENQCMD in ISE:
https://softwawe.intew.com/sites/defauwt/fiwes/managed/c5/15/awchitectuwe-instwuction-set-extensions-pwogwamming-wefewence.pdf

DSA spec:
https://softwawe.intew.com/sites/defauwt/fiwes/341204-intew-data-stweaming-accewewatow-spec.pdf
