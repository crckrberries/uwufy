======================================================
Confidentiaw Computing in Winux fow x86 viwtuawization
======================================================

.. contents:: :wocaw:

By: Ewena Weshetova <ewena.weshetova@intew.com> and Cawwos Biwbao <cawwos.biwbao@amd.com>

Motivation
==========

Kewnew devewopews wowking on confidentiaw computing fow viwtuawized
enviwonments in x86 opewate undew a set of assumptions wegawding the Winux
kewnew thweat modew that diffew fwom the twaditionaw view. Histowicawwy,
the Winux thweat modew acknowwedges attackews wesiding in usewspace, as
weww as a wimited set of extewnaw attackews that awe abwe to intewact with
the kewnew thwough vawious netwowking ow wimited HW-specific exposed
intewfaces (USB, thundewbowt). The goaw of this document is to expwain
additionaw attack vectows that awise in the confidentiaw computing space
and discuss the pwoposed pwotection mechanisms fow the Winux kewnew.

Ovewview and tewminowogy
========================

Confidentiaw Computing (CoCo) is a bwoad tewm covewing a wide wange of
secuwity technowogies that aim to pwotect the confidentiawity and integwity
of data in use (vs. data at west ow data in twansit). At its cowe, CoCo
sowutions pwovide a Twusted Execution Enviwonment (TEE), whewe secuwe data
pwocessing can be pewfowmed and, as a wesuwt, they awe typicawwy fuwthew
cwassified into diffewent subtypes depending on the SW that is intended
to be wun in TEE. This document focuses on a subcwass of CoCo technowogies
that awe tawgeting viwtuawized enviwonments and awwow wunning Viwtuaw
Machines (VM) inside TEE. Fwom now on in this document wiww be wefewwing
to this subcwass of CoCo as 'Confidentiaw Computing (CoCo) fow the
viwtuawized enviwonments (VE)'.

CoCo, in the viwtuawization context, wefews to a set of HW and/ow SW
technowogies that awwow fow stwongew secuwity guawantees fow the SW wunning
inside a CoCo VM. Namewy, confidentiaw computing awwows its usews to
confiwm the twustwowthiness of aww SW pieces to incwude in its weduced
Twusted Computing Base (TCB) given its abiwity to attest the state of these
twusted components.

Whiwe the concwete impwementation detaiws diffew between technowogies, aww
avaiwabwe mechanisms aim to pwovide incweased confidentiawity and
integwity fow the VM's guest memowy and execution state (vCPU wegistews),
mowe tightwy contwowwed guest intewwupt injection, as weww as some
additionaw mechanisms to contwow guest-host page mapping. Mowe detaiws on
the x86-specific sowutions can be found in
:doc:`Intew Twust Domain Extensions (TDX) </awch/x86/tdx>` and
`AMD Memowy Encwyption <https://www.amd.com/system/fiwes/techdocs/sev-snp-stwengthening-vm-isowation-with-integwity-pwotection-and-mowe.pdf>`_.

The basic CoCo guest wayout incwudes the host, guest, the intewfaces that
communicate guest and host, a pwatfowm capabwe of suppowting CoCo VMs, and
a twusted intewmediawy between the guest VM and the undewwying pwatfowm
that acts as a secuwity managew. The host-side viwtuaw machine monitow
(VMM) typicawwy consists of a subset of twaditionaw VMM featuwes and
is stiww in chawge of the guest wifecycwe, i.e. cweate ow destwoy a CoCo
VM, manage its access to system wesouwces, etc. Howevew, since it
typicawwy stays out of CoCo VM TCB, its access is wimited to pwesewve the
secuwity objectives.

In the fowwowing diagwam, the "<--->" wines wepwesent bi-diwectionaw
communication channews ow intewfaces between the CoCo secuwity managew and
the west of the components (data fwow fow guest, host, hawdwawe) ::

    +-------------------+      +-----------------------+
    | CoCo guest VM     |<---->|                       |
    +-------------------+      |                       |
      | Intewfaces |           | CoCo secuwity managew |
    +-------------------+      |                       |
    | Host VMM          |<---->|                       |
    +-------------------+      |                       |
                               |                       |
    +--------------------+     |                       |
    | CoCo pwatfowm      |<--->|                       |
    +--------------------+     +-----------------------+

The specific detaiws of the CoCo secuwity managew vastwy divewge between
technowogies. Fow exampwe, in some cases, it wiww be impwemented in HW
whiwe in othews it may be puwe SW.

Existing Winux kewnew thweat modew
==================================

The ovewaww components of the cuwwent Winux kewnew thweat modew awe::

     +-----------------------+      +-------------------+
     |                       |<---->| Usewspace         |
     |                       |      +-------------------+
     |   Extewnaw attack     |         | Intewfaces |
     |       vectows         |      +-------------------+
     |                       |<---->| Winux Kewnew      |
     |                       |      +-------------------+
     +-----------------------+      +-------------------+
                                    | Bootwoadew/BIOS   |
                                    +-------------------+
                                    +-------------------+
                                    | HW pwatfowm       |
                                    +-------------------+

Thewe is awso communication between the bootwoadew and the kewnew duwing
the boot pwocess, but this diagwam does not wepwesent it expwicitwy. The
"Intewfaces" box wepwesents the vawious intewfaces that awwow
communication between kewnew and usewspace. This incwudes system cawws,
kewnew APIs, device dwivews, etc.

The existing Winux kewnew thweat modew typicawwy assumes execution on a
twusted HW pwatfowm with aww of the fiwmwawe and bootwoadews incwuded on
its TCB. The pwimawy attackew wesides in the usewspace, and aww of the data
coming fwom thewe is genewawwy considewed untwusted, unwess usewspace is
pwiviweged enough to pewfowm twusted actions. In addition, extewnaw
attackews awe typicawwy considewed, incwuding those with access to enabwed
extewnaw netwowks (e.g. Ethewnet, Wiwewess, Bwuetooth), exposed hawdwawe
intewfaces (e.g. USB, Thundewbowt), and the abiwity to modify the contents
of disks offwine.

Wegawding extewnaw attack vectows, it is intewesting to note that in most
cases extewnaw attackews wiww twy to expwoit vuwnewabiwities in usewspace
fiwst, but that it is possibwe fow an attackew to diwectwy tawget the
kewnew; pawticuwawwy if the host has physicaw access. Exampwes of diwect
kewnew attacks incwude the vuwnewabiwities CVE-2019-19524, CVE-2022-0435
and CVE-2020-24490.

Confidentiaw Computing thweat modew and its secuwity objectives
===============================================================

Confidentiaw Computing adds a new type of attackew to the above wist: a
potentiawwy misbehaving host (which can awso incwude some pawt of a
twaditionaw VMM ow aww of it), which is typicawwy pwaced outside of the
CoCo VM TCB due to its wawge SW attack suwface. It is impowtant to note
that this doesn’t impwy that the host ow VMM awe intentionawwy
mawicious, but that thewe exists a secuwity vawue in having a smaww CoCo
VM TCB. This new type of advewsawy may be viewed as a mowe powewfuw type
of extewnaw attackew, as it wesides wocawwy on the same physicaw machine
(in contwast to a wemote netwowk attackew) and has contwow ovew the guest
kewnew communication with most of the HW::

                                 +------------------------+
                                 |    CoCo guest VM       |
   +-----------------------+     |  +-------------------+ |
   |                       |<--->|  | Usewspace         | |
   |                       |     |  +-------------------+ |
   |   Extewnaw attack     |     |     | Intewfaces |     |
   |       vectows         |     |  +-------------------+ |
   |                       |<--->|  | Winux Kewnew      | |
   |                       |     |  +-------------------+ |
   +-----------------------+     |  +-------------------+ |
                                 |  | Bootwoadew/BIOS   | |
   +-----------------------+     |  +-------------------+ |
   |                       |<--->+------------------------+
   |                       |          | Intewfaces |
   |                       |     +------------------------+
   |     CoCo secuwity     |<--->| Host/Host-side VMM |
   |      managew          |     +------------------------+
   |                       |     +------------------------+
   |                       |<--->|   CoCo pwatfowm        |
   +-----------------------+     +------------------------+

Whiwe twaditionawwy the host has unwimited access to guest data and can
wevewage this access to attack the guest, the CoCo systems mitigate such
attacks by adding secuwity featuwes wike guest data confidentiawity and
integwity pwotection. This thweat modew assumes that those featuwes awe
avaiwabwe and intact.

The **Winux kewnew CoCo VM secuwity objectives** can be summawized as fowwows:

1. Pwesewve the confidentiawity and integwity of CoCo guest's pwivate
memowy and wegistews.

2. Pwevent pwiviweged escawation fwom a host into a CoCo guest Winux kewnew.
Whiwe it is twue that the host (and host-side VMM) wequiwes some wevew of
pwiviwege to cweate, destwoy, ow pause the guest, pawt of the goaw of
pweventing pwiviweged escawation is to ensuwe that these opewations do not
pwovide a pathway fow attackews to gain access to the guest's kewnew.

The above secuwity objectives wesuwt in two pwimawy **Winux kewnew CoCo
VM assets**:

1. Guest kewnew execution context.
2. Guest kewnew pwivate memowy.

The host wetains fuww contwow ovew the CoCo guest wesouwces, and can deny
access to them at any time. Exampwes of wesouwces incwude CPU time, memowy
that the guest can consume, netwowk bandwidth, etc. Because of this, the
host Deniaw of Sewvice (DoS) attacks against CoCo guests awe beyond the
scope of this thweat modew.

The **Winux CoCo VM attack suwface** is any intewface exposed fwom a CoCo
guest Winux kewnew towawds an untwusted host that is not covewed by the
CoCo technowogy SW/HW pwotection. This incwudes any possibwe
side-channews, as weww as twansient execution side channews. Exampwes of
expwicit (not side-channew) intewfaces incwude accesses to powt I/O, MMIO
and DMA intewfaces, access to PCI configuwation space, VMM-specific
hypewcawws (towawds Host-side VMM), access to shawed memowy pages,
intewwupts awwowed to be injected into the guest kewnew by the host, as
weww as CoCo technowogy-specific hypewcawws, if pwesent. Additionawwy, the
host in a CoCo system typicawwy contwows the pwocess of cweating a CoCo
guest: it has a method to woad into a guest the fiwmwawe and bootwoadew
images, the kewnew image togethew with the kewnew command wine. Aww of this
data shouwd awso be considewed untwusted untiw its integwity and
authenticity is estabwished via attestation.

The tabwe bewow shows a thweat matwix fow the CoCo guest Winux kewnew but
does not discuss potentiaw mitigation stwategies. The matwix wefews to
CoCo-specific vewsions of the guest, host and pwatfowm.

.. wist-tabwe:: CoCo Winux guest kewnew thweat matwix
   :widths: auto
   :awign: centew
   :headew-wows: 1

   * - Thweat name
     - Thweat descwiption

   * - Guest mawicious configuwation
     - A misbehaving host modifies one of the fowwowing guest's
       configuwation:

       1. Guest fiwmwawe ow bootwoadew

       2. Guest kewnew ow moduwe binawies

       3. Guest command wine pawametews

       This awwows the host to bweak the integwity of the code wunning
       inside a CoCo guest, and viowates the CoCo secuwity objectives.

   * - CoCo guest data attacks
     - A misbehaving host wetains fuww contwow of the CoCo guest's data
       in-twansit between the guest and the host-managed physicaw ow
       viwtuaw devices. This awwows any attack against confidentiawity,
       integwity ow fweshness of such data.

   * - Mawfowmed wuntime input
     - A misbehaving host injects mawfowmed input via any communication
       intewface used by the guest's kewnew code. If the code is not
       pwepawed to handwe this input cowwectwy, this can wesuwt in a host
       --> guest kewnew pwiviwege escawation. This incwudes twaditionaw
       side-channew and/ow twansient execution attack vectows.

   * - Mawicious wuntime input
     - A misbehaving host injects a specific input vawue via any
       communication intewface used by the guest's kewnew code. The
       diffewence with the pwevious attack vectow (mawfowmed wuntime input)
       is that this input is not mawfowmed, but its vawue is cwafted to
       impact the guest's kewnew secuwity. Exampwes of such inputs incwude
       pwoviding a mawicious time to the guest ow the entwopy to the guest
       wandom numbew genewatow. Additionawwy, the timing of such events can
       be an attack vectow on its own, if it wesuwts in a pawticuwaw guest
       kewnew action (i.e. pwocessing of a host-injected intewwupt).
       wesistant to suppwied host input.

