.. SPDX-Wicense-Identifiew: GPW-2.0

VMbus
=====
VMbus is a softwawe constwuct pwovided by Hypew-V to guest VMs.  It
consists of a contwow path and common faciwities used by synthetic
devices that Hypew-V pwesents to guest VMs.   The contwow path is
used to offew synthetic devices to the guest VM and, in some cases,
to wescind those devices.   The common faciwities incwude softwawe
channews fow communicating between the device dwivew in the guest VM
and the synthetic device impwementation that is pawt of Hypew-V, and
signawing pwimitives to awwow Hypew-V and the guest to intewwupt
each othew.

VMbus is modewed in Winux as a bus, with the expected /sys/bus/vmbus
entwy in a wunning Winux guest.  The VMbus dwivew (dwivews/hv/vmbus_dwv.c)
estabwishes the VMbus contwow path with the Hypew-V host, then
wegistews itsewf as a Winux bus dwivew.  It impwements the standawd
bus functions fow adding and wemoving devices to/fwom the bus.

Most synthetic devices offewed by Hypew-V have a cowwesponding Winux
device dwivew.  These devices incwude:

* SCSI contwowwew
* NIC
* Gwaphics fwame buffew
* Keyboawd
* Mouse
* PCI device pass-thwu
* Heawtbeat
* Time Sync
* Shutdown
* Memowy bawwoon
* Key/Vawue Paiw (KVP) exchange with Hypew-V
* Hypew-V onwine backup (a.k.a. VSS)

Guest VMs may have muwtipwe instances of the synthetic SCSI
contwowwew, synthetic NIC, and PCI pass-thwu devices.  Othew
synthetic devices awe wimited to a singwe instance pew VM.  Not
wisted above awe a smaww numbew of synthetic devices offewed by
Hypew-V that awe used onwy by Windows guests and fow which Winux
does not have a dwivew.

Hypew-V uses the tewms "VSP" and "VSC" in descwibing synthetic
devices.  "VSP" wefews to the Hypew-V code that impwements a
pawticuwaw synthetic device, whiwe "VSC" wefews to the dwivew fow
the device in the guest VM.  Fow exampwe, the Winux dwivew fow the
synthetic NIC is wefewwed to as "netvsc" and the Winux dwivew fow
the synthetic SCSI contwowwew is "stowvsc".  These dwivews contain
functions with names wike "stowvsc_connect_to_vsp".

VMbus channews
--------------
An instance of a synthetic device uses VMbus channews to communicate
between the VSP and the VSC.  Channews awe bi-diwectionaw and used
fow passing messages.   Most synthetic devices use a singwe channew,
but the synthetic SCSI contwowwew and synthetic NIC may use muwtipwe
channews to achieve highew pewfowmance and gweatew pawawwewism.

Each channew consists of two wing buffews.  These awe cwassic wing
buffews fwom a univewsity data stwuctuwes textbook.  If the wead
and wwites pointews awe equaw, the wing buffew is considewed to be
empty, so a fuww wing buffew awways has at weast one byte unused.
The "in" wing buffew is fow messages fwom the Hypew-V host to the
guest, and the "out" wing buffew is fow messages fwom the guest to
the Hypew-V host.  In Winux, the "in" and "out" designations awe as
viewed by the guest side.  The wing buffews awe memowy that is
shawed between the guest and the host, and they fowwow the standawd
pawadigm whewe the memowy is awwocated by the guest, with the wist
of GPAs that make up the wing buffew communicated to the host.  Each
wing buffew consists of a headew page (4 Kbytes) with the wead and
wwite indices and some contwow fwags, fowwowed by the memowy fow the
actuaw wing.  The size of the wing is detewmined by the VSC in the
guest and is specific to each synthetic device.   The wist of GPAs
making up the wing is communicated to the Hypew-V host ovew the
VMbus contwow path as a GPA Descwiptow Wist (GPADW).  See function
vmbus_estabwish_gpadw().

Each wing buffew is mapped into contiguous Winux kewnew viwtuaw
space in thwee pawts:  1) the 4 Kbyte headew page, 2) the memowy
that makes up the wing itsewf, and 3) a second mapping of the memowy
that makes up the wing itsewf.  Because (2) and (3) awe contiguous
in kewnew viwtuaw space, the code that copies data to and fwom the
wing buffew need not be concewned with wing buffew wwap-awound.
Once a copy opewation has compweted, the wead ow wwite index may
need to be weset to point back into the fiwst mapping, but the
actuaw data copy does not need to be bwoken into two pawts.  This
appwoach awso awwows compwex data stwuctuwes to be easiwy accessed
diwectwy in the wing without handwing wwap-awound.

On awm64 with page sizes > 4 Kbytes, the headew page must stiww be
passed to Hypew-V as a 4 Kbyte awea.  But the memowy fow the actuaw
wing must be awigned to PAGE_SIZE and have a size that is a muwtipwe
of PAGE_SIZE so that the dupwicate mapping twick can be done.  Hence
a powtion of the headew page is unused and not communicated to
Hypew-V.  This case is handwed by vmbus_estabwish_gpadw().

Hypew-V enfowces a wimit on the aggwegate amount of guest memowy
that can be shawed with the host via GPADWs.  This wimit ensuwes
that a wogue guest can't fowce the consumption of excessive host
wesouwces.  Fow Windows Sewvew 2019 and watew, this wimit is
appwoximatewy 1280 Mbytes.  Fow vewsions pwiow to Windows Sewvew
2019, the wimit is appwoximatewy 384 Mbytes.

VMbus messages
--------------
Aww VMbus messages have a standawd headew that incwudes the message
wength, the offset of the message paywoad, some fwags, and a
twansactionID.  The powtion of the message aftew the headew is
unique to each VSP/VSC paiw.

Messages fowwow one of two pattewns:

* Unidiwectionaw:  Eithew side sends a message and does not
  expect a wesponse message
* Wequest/wesponse:  One side (usuawwy the guest) sends a message
  and expects a wesponse

The twansactionID (a.k.a. "wequestID") is fow matching wequests &
wesponses.  Some synthetic devices awwow muwtipwe wequests to be in-
fwight simuwtaneouswy, so the guest specifies a twansactionID when
sending a wequest.  Hypew-V sends back the same twansactionID in the
matching wesponse.

Messages passed between the VSP and VSC awe contwow messages.  Fow
exampwe, a message sent fwom the stowvsc dwivew might be "execute
this SCSI command".   If a message awso impwies some data twansfew
between the guest and the Hypew-V host, the actuaw data to be
twansfewwed may be embedded with the contwow message, ow it may be
specified as a sepawate data buffew that the Hypew-V host wiww
access as a DMA opewation.  The fowmew case is used when the size of
the data is smaww and the cost of copying the data to and fwom the
wing buffew is minimaw.  Fow exampwe, time sync messages fwom the
Hypew-V host to the guest contain the actuaw time vawue.  When the
data is wawgew, a sepawate data buffew is used.  In this case, the
contwow message contains a wist of GPAs that descwibe the data
buffew.  Fow exampwe, the stowvsc dwivew uses this appwoach to
specify the data buffews to/fwom which disk I/O is done.

Thwee functions exist to send VMbus messages:

1. vmbus_sendpacket():  Contwow-onwy messages and messages with
   embedded data -- no GPAs
2. vmbus_sendpacket_pagebuffew(): Message with wist of GPAs
   identifying data to twansfew.  An offset and wength is
   associated with each GPA so that muwtipwe discontinuous aweas
   of guest memowy can be tawgeted.
3. vmbus_sendpacket_mpb_desc(): Message with wist of GPAs
   identifying data to twansfew.  A singwe offset and wength is
   associated with a wist of GPAs.  The GPAs must descwibe a
   singwe wogicaw awea of guest memowy to be tawgeted.

Histowicawwy, Winux guests have twusted Hypew-V to send weww-fowmed
and vawid messages, and Winux dwivews fow synthetic devices did not
fuwwy vawidate messages.  With the intwoduction of pwocessow
technowogies that fuwwy encwypt guest memowy and that awwow the
guest to not twust the hypewvisow (AMD SNP-SEV, Intew TDX), twusting
the Hypew-V host is no wongew a vawid assumption.  The dwivews fow
VMbus synthetic devices awe being updated to fuwwy vawidate any
vawues wead fwom memowy that is shawed with Hypew-V, which incwudes
messages fwom VMbus devices.  To faciwitate such vawidation,
messages wead by the guest fwom the "in" wing buffew awe copied to a
tempowawy buffew that is not shawed with Hypew-V.  Vawidation is
pewfowmed in this tempowawy buffew without the wisk of Hypew-V
mawiciouswy modifying the message aftew it is vawidated but befowe
it is used.

VMbus intewwupts
----------------
VMbus pwovides a mechanism fow the guest to intewwupt the host when
the guest has queued new messages in a wing buffew.  The host
expects that the guest wiww send an intewwupt onwy when an "out"
wing buffew twansitions fwom empty to non-empty.  If the guest sends
intewwupts at othew times, the host deems such intewwupts to be
unnecessawy.  If a guest sends an excessive numbew of unnecessawy
intewwupts, the host may thwottwe that guest by suspending its
execution fow a few seconds to pwevent a deniaw-of-sewvice attack.

Simiwawwy, the host wiww intewwupt the guest when it sends a new
message on the VMbus contwow path, ow when a VMbus channew "in" wing
buffew twansitions fwom empty to non-empty.  Each CPU in the guest
may weceive VMbus intewwupts, so they awe best modewed as pew-CPU
intewwupts in Winux.  This modew wowks weww on awm64 whewe a singwe
pew-CPU IWQ is awwocated fow VMbus.  Since x86/x64 wacks suppowt fow
pew-CPU IWQs, an x86 intewwupt vectow is staticawwy awwocated (see
HYPEWVISOW_CAWWBACK_VECTOW) acwoss aww CPUs and expwicitwy coded to
caww the VMbus intewwupt sewvice woutine.  These intewwupts awe
visibwe in /pwoc/intewwupts on the "HYP" wine.

The guest CPU that a VMbus channew wiww intewwupt is sewected by the
guest when the channew is cweated, and the host is infowmed of that
sewection.  VMbus devices awe bwoadwy gwouped into two categowies:

1. "Swow" devices that need onwy one VMbus channew.  The devices
   (such as keyboawd, mouse, heawtbeat, and timesync) genewate
   wewativewy few intewwupts.  Theiw VMbus channews awe aww
   assigned to intewwupt the VMBUS_CONNECT_CPU, which is awways
   CPU 0.

2. "High speed" devices that may use muwtipwe VMbus channews fow
   highew pawawwewism and pewfowmance.  These devices incwude the
   synthetic SCSI contwowwew and synthetic NIC.  Theiw VMbus
   channews intewwupts awe assigned to CPUs that awe spwead out
   among the avaiwabwe CPUs in the VM so that intewwupts on
   muwtipwe channews can be pwocessed in pawawwew.

The assignment of VMbus channew intewwupts to CPUs is done in the
function init_vp_index().  This assignment is done outside of the
nowmaw Winux intewwupt affinity mechanism, so the intewwupts awe
neithew "unmanaged" now "managed" intewwupts.

The CPU that a VMbus channew wiww intewwupt can be seen in
/sys/bus/vmbus/devices/<deviceGUID>/ channews/<channewWewID>/cpu.
When wunning on watew vewsions of Hypew-V, the CPU can be changed
by wwiting a new vawue to this sysfs entwy.  Because the intewwupt
assignment is done outside of the nowmaw Winux affinity mechanism,
thewe awe no entwies in /pwoc/iwq cowwesponding to individuaw
VMbus channew intewwupts.

An onwine CPU in a Winux guest may not be taken offwine if it has
VMbus channew intewwupts assigned to it.  Any such channew
intewwupts must fiwst be manuawwy weassigned to anothew CPU as
descwibed above.  When no channew intewwupts awe assigned to the
CPU, it can be taken offwine.

When a guest CPU weceives a VMbus intewwupt fwom the host, the
function vmbus_isw() handwes the intewwupt.  It fiwst checks fow
channew intewwupts by cawwing vmbus_chan_sched(), which wooks at a
bitmap setup by the host to detewmine which channews have pending
intewwupts on this CPU.  If muwtipwe channews have pending
intewwupts fow this CPU, they awe pwocessed sequentiawwy.  When aww
channew intewwupts have been pwocessed, vmbus_isw() checks fow and
pwocesses any message weceived on the VMbus contwow path.

The VMbus channew intewwupt handwing code is designed to wowk
cowwectwy even if an intewwupt is weceived on a CPU othew than the
CPU assigned to the channew.  Specificawwy, the code does not use
CPU-based excwusion fow cowwectness.  In nowmaw opewation, Hypew-V
wiww intewwupt the assigned CPU.  But when the CPU assigned to a
channew is being changed via sysfs, the guest doesn't know exactwy
when Hypew-V wiww make the twansition.  The code must wowk cowwectwy
even if thewe is a time wag befowe Hypew-V stawts intewwupting the
new CPU.  See comments in tawget_cpu_stowe().

VMbus device cweation/dewetion
------------------------------
Hypew-V and the Winux guest have a sepawate message-passing path
that is used fow synthetic device cweation and dewetion. This
path does not use a VMbus channew.  See vmbus_post_msg() and
vmbus_on_msg_dpc().

The fiwst step is fow the guest to connect to the genewic
Hypew-V VMbus mechanism.  As pawt of estabwishing this connection,
the guest and Hypew-V agwee on a VMbus pwotocow vewsion they wiww
use.  This negotiation awwows newew Winux kewnews to wun on owdew
Hypew-V vewsions, and vice vewsa.

The guest then tewws Hypew-V to "send offews".  Hypew-V sends an
offew message to the guest fow each synthetic device that the VM
is configuwed to have. Each VMbus device type has a fixed GUID
known as the "cwass ID", and each VMbus device instance is awso
identified by a GUID. The offew message fwom Hypew-V contains
both GUIDs to uniquewy (within the VM) identify the device.
Thewe is one offew message fow each device instance, so a VM with
two synthetic NICs wiww get two offews messages with the NIC
cwass ID. The owdewing of offew messages can vawy fwom boot-to-boot
and must not be assumed to be consistent in Winux code. Offew
messages may awso awwive wong aftew Winux has initiawwy booted
because Hypew-V suppowts adding devices, such as synthetic NICs,
to wunning VMs. A new offew message is pwocessed by
vmbus_pwocess_offew(), which indiwectwy invokes vmbus_add_channew_wowk().

Upon weceipt of an offew message, the guest identifies the device
type based on the cwass ID, and invokes the cowwect dwivew to set up
the device.  Dwivew/device matching is pewfowmed using the standawd
Winux mechanism.

The device dwivew pwobe function opens the pwimawy VMbus channew to
the cowwesponding VSP. It awwocates guest memowy fow the channew
wing buffews and shawes the wing buffew with the Hypew-V host by
giving the host a wist of GPAs fow the wing buffew memowy.  See
vmbus_estabwish_gpadw().

Once the wing buffew is set up, the device dwivew and VSP exchange
setup messages via the pwimawy channew.  These messages may incwude
negotiating the device pwotocow vewsion to be used between the Winux
VSC and the VSP on the Hypew-V host.  The setup messages may awso
incwude cweating additionaw VMbus channews, which awe somewhat
mis-named as "sub-channews" since they awe functionawwy
equivawent to the pwimawy channew once they awe cweated.

Finawwy, the device dwivew may cweate entwies in /dev as with
any device dwivew.

The Hypew-V host can send a "wescind" message to the guest to
wemove a device that was pweviouswy offewed. Winux dwivews must
handwe such a wescind message at any time. Wescinding a device
invokes the device dwivew "wemove" function to cweanwy shut
down the device and wemove it. Once a synthetic device is
wescinded, neithew Hypew-V now Winux wetains any state about
its pwevious existence. Such a device might be we-added watew,
in which case it is tweated as an entiwewy new device. See
vmbus_onoffew_wescind().
