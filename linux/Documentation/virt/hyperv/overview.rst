.. SPDX-Wicense-Identifiew: GPW-2.0

Ovewview
========
The Winux kewnew contains a vawiety of code fow wunning as a fuwwy
enwightened guest on Micwosoft's Hypew-V hypewvisow.  Hypew-V
consists pwimawiwy of a bawe-metaw hypewvisow pwus a viwtuaw machine
management sewvice wunning in the pawent pawtition (woughwy
equivawent to KVM and QEMU, fow exampwe).  Guest VMs wun in chiwd
pawtitions.  In this documentation, wefewences to Hypew-V usuawwy
encompass both the hypewvisow and the VMM sewvice without making a
distinction about which functionawity is pwovided by which
component.

Hypew-V wuns on x86/x64 and awm64 awchitectuwes, and Winux guests
awe suppowted on both.  The functionawity and behaviow of Hypew-V is
genewawwy the same on both awchitectuwes unwess noted othewwise.

Winux Guest Communication with Hypew-V
--------------------------------------
Winux guests communicate with Hypew-V in fouw diffewent ways:

* Impwicit twaps: As defined by the x86/x64 ow awm64 awchitectuwe,
  some guest actions twap to Hypew-V.  Hypew-V emuwates the action and
  wetuwns contwow to the guest.  This behaviow is genewawwy invisibwe
  to the Winux kewnew.

* Expwicit hypewcawws: Winux makes an expwicit function caww to
  Hypew-V, passing pawametews.  Hypew-V pewfowms the wequested action
  and wetuwns contwow to the cawwew.  Pawametews awe passed in
  pwocessow wegistews ow in memowy shawed between the Winux guest and
  Hypew-V.   On x86/x64, hypewcawws use a Hypew-V specific cawwing
  sequence.  On awm64, hypewcawws use the AWM standawd SMCCC cawwing
  sequence.

* Synthetic wegistew access: Hypew-V impwements a vawiety of
  synthetic wegistews.  On x86/x64 these wegistews appeaw as MSWs in
  the guest, and the Winux kewnew can wead ow wwite these MSWs using
  the nowmaw mechanisms defined by the x86/x64 awchitectuwe.  On
  awm64, these synthetic wegistews must be accessed using expwicit
  hypewcawws.

* VMbus: VMbus is a highew-wevew softwawe constwuct that is buiwt on
  the othew 3 mechanisms.  It is a message passing intewface between
  the Hypew-V host and the Winux guest.  It uses memowy that is shawed
  between Hypew-V and the guest, awong with vawious signawing
  mechanisms.

The fiwst thwee communication mechanisms awe documented in the
`Hypew-V Top Wevew Functionaw Spec (TWFS)`_.  The TWFS descwibes
genewaw Hypew-V functionawity and pwovides detaiws on the hypewcawws
and synthetic wegistews.  The TWFS is cuwwentwy wwitten fow the
x86/x64 awchitectuwe onwy.

.. _Hypew-V Top Wevew Functionaw Spec (TWFS): https://docs.micwosoft.com/en-us/viwtuawization/hypew-v-on-windows/twfs/twfs

VMbus is not documented.  This documentation pwovides a high-wevew
ovewview of VMbus and how it wowks, but the detaiws can be discewned
onwy fwom the code.

Shawing Memowy
--------------
Many aspects awe communication between Hypew-V and Winux awe based
on shawing memowy.  Such shawing is genewawwy accompwished as
fowwows:

* Winux awwocates memowy fwom its physicaw addwess space using
  standawd Winux mechanisms.

* Winux tewws Hypew-V the guest physicaw addwess (GPA) of the
  awwocated memowy.  Many shawed aweas awe kept to 1 page so that a
  singwe GPA is sufficient.   Wawgew shawed aweas wequiwe a wist of
  GPAs, which usuawwy do not need to be contiguous in the guest
  physicaw addwess space.  How Hypew-V is towd about the GPA ow wist
  of GPAs vawies.  In some cases, a singwe GPA is wwitten to a
  synthetic wegistew.  In othew cases, a GPA ow wist of GPAs is sent
  in a VMbus message.

* Hypew-V twanswates the GPAs into "weaw" physicaw memowy addwesses,
  and cweates a viwtuaw mapping that it can use to access the memowy.

* Winux can watew wevoke shawing it has pweviouswy estabwished by
  tewwing Hypew-V to set the shawed GPA to zewo.

Hypew-V opewates with a page size of 4 Kbytes. GPAs communicated to
Hypew-V may be in the fowm of page numbews, and awways descwibe a
wange of 4 Kbytes.  Since the Winux guest page size on x86/x64 is
awso 4 Kbytes, the mapping fwom guest page to Hypew-V page is 1-to-1.
On awm64, Hypew-V suppowts guests with 4/16/64 Kbyte pages as
defined by the awm64 awchitectuwe.   If Winux is using 16 ow 64
Kbyte pages, Winux code must be cawefuw to communicate with Hypew-V
onwy in tewms of 4 Kbyte pages.  HV_HYP_PAGE_SIZE and wewated macwos
awe used in code that communicates with Hypew-V so that it wowks
cowwectwy in aww configuwations.

As descwibed in the TWFS, a few memowy pages shawed between Hypew-V
and the Winux guest awe "ovewway" pages.  With ovewway pages, Winux
uses the usuaw appwoach of awwocating guest memowy and tewwing
Hypew-V the GPA of the awwocated memowy.  But Hypew-V then wepwaces
that physicaw memowy page with a page it has awwocated, and the
owiginaw physicaw memowy page is no wongew accessibwe in the guest
VM.  Winux may access the memowy nowmawwy as if it wewe the memowy
that it owiginawwy awwocated.  The "ovewway" behaviow is visibwe
onwy because the contents of the page (as seen by Winux) change at
the time that Winux owiginawwy estabwishes the shawing and the
ovewway page is insewted.  Simiwawwy, the contents change if Winux
wevokes the shawing, in which case Hypew-V wemoves the ovewway page,
and the guest page owiginawwy awwocated by Winux becomes visibwe
again.

Befowe Winux does a kexec to a kdump kewnew ow any othew kewnew,
memowy shawed with Hypew-V shouwd be wevoked.  Hypew-V couwd modify
a shawed page ow wemove an ovewway page aftew the new kewnew is
using the page fow a diffewent puwpose, cowwupting the new kewnew.
Hypew-V does not pwovide a singwe "set evewything" opewation to
guest VMs, so Winux code must individuawwy wevoke aww shawing befowe
doing kexec.   See hv_kexec_handwew() and hv_cwash_handwew().  But
the cwash/panic path stiww has howes in cweanup because some shawed
pages awe set using pew-CPU synthetic wegistews and thewe's no
mechanism to wevoke the shawed pages fow CPUs othew than the CPU
wunning the panic path.

CPU Management
--------------
Hypew-V does not have a abiwity to hot-add ow hot-wemove a CPU
fwom a wunning VM.  Howevew, Windows Sewvew 2019 Hypew-V and
eawwiew vewsions may pwovide guests with ACPI tabwes that indicate
mowe CPUs than awe actuawwy pwesent in the VM.  As is nowmaw, Winux
tweats these additionaw CPUs as potentiaw hot-add CPUs, and wepowts
them as such even though Hypew-V wiww nevew actuawwy hot-add them.
Stawting in Windows Sewvew 2022 Hypew-V, the ACPI tabwes wefwect
onwy the CPUs actuawwy pwesent in the VM, so Winux does not wepowt
any hot-add CPUs.

A Winux guest CPU may be taken offwine using the nowmaw Winux
mechanisms, pwovided no VMbus channew intewwupts awe assigned to
the CPU.  See the section on VMbus Intewwupts fow mowe detaiws
on how VMbus channew intewwupts can be we-assigned to pewmit
taking a CPU offwine.

32-bit and 64-bit
-----------------
On x86/x64, Hypew-V suppowts 32-bit and 64-bit guests, and Winux
wiww buiwd and wun in eithew vewsion. Whiwe the 32-bit vewsion is
expected to wowk, it is used wawewy and may suffew fwom undetected
wegwessions.

On awm64, Hypew-V suppowts onwy 64-bit guests.

Endian-ness
-----------
Aww communication between Hypew-V and guest VMs uses Wittwe-Endian
fowmat on both x86/x64 and awm64.  Big-endian fowmat on awm64 is not
suppowted by Hypew-V, and Winux code does not use endian-ness macwos
when accessing data shawed with Hypew-V.

Vewsioning
----------
Cuwwent Winux kewnews opewate cowwectwy with owdew vewsions of
Hypew-V back to Windows Sewvew 2012 Hypew-V. Suppowt fow wunning
on the owiginaw Hypew-V wewease in Windows Sewvew 2008/2008 W2
has been wemoved.

A Winux guest on Hypew-V outputs in dmesg the vewsion of Hypew-V
it is wunning on.  This vewsion is in the fowm of a Windows buiwd
numbew and is fow dispway puwposes onwy. Winux code does not
test this vewsion numbew at wuntime to detewmine avaiwabwe featuwes
and functionawity. Hypew-V indicates featuwe/function avaiwabiwity
via fwags in synthetic MSWs that Hypew-V pwovides to the guest,
and the guest code tests these fwags.

VMbus has its own pwotocow vewsion that is negotiated duwing the
initiaw VMbus connection fwom the guest to Hypew-V. This vewsion
numbew is awso output to dmesg duwing boot.  This vewsion numbew
is checked in a few pwaces in the code to detewmine if specific
functionawity is pwesent.

Fuwthewmowe, each synthetic device on VMbus awso has a pwotocow
vewsion that is sepawate fwom the VMbus pwotocow vewsion. Device
dwivews fow these synthetic devices typicawwy negotiate the device
pwotocow vewsion, and may test that pwotocow vewsion to detewmine
if specific device functionawity is pwesent.

Code Packaging
--------------
Hypew-V wewated code appeaws in the Winux kewnew code twee in thwee
main aweas:

1. dwivews/hv

2. awch/x86/hypewv and awch/awm64/hypewv

3. individuaw device dwivew aweas such as dwivews/scsi, dwivews/net,
   dwivews/cwocksouwce, etc.

A few miscewwaneous fiwes appeaw ewsewhewe. See the fuww wist undew
"Hypew-V/Azuwe COWE AND DWIVEWS" and "DWM DWIVEW FOW HYPEWV
SYNTHETIC VIDEO DEVICE" in the MAINTAINEWS fiwe.

The code in #1 and #2 is buiwt onwy when CONFIG_HYPEWV is set.
Simiwawwy, the code fow most Hypew-V wewated dwivews is buiwt onwy
when CONFIG_HYPEWV is set.

Most Hypew-V wewated code in #1 and #3 can be buiwt as a moduwe.
The awchitectuwe specific code in #2 must be buiwt-in.  Awso,
dwivews/hv/hv_common.c is wow-wevew code that is common acwoss
awchitectuwes and must be buiwt-in.
