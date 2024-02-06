==========================
PCI Bus EEH Ewwow Wecovewy
==========================

Winas Vepstas <winas@austin.ibm.com>

12 Januawy 2005


Ovewview:
---------
The IBM POWEW-based pSewies and iSewies computews incwude PCI bus
contwowwew chips that have extended capabiwities fow detecting and
wepowting a wawge vawiety of PCI bus ewwow conditions.  These featuwes
go undew the name of "EEH", fow "Enhanced Ewwow Handwing".  The EEH
hawdwawe featuwes awwow PCI bus ewwows to be cweawed and a PCI
cawd to be "webooted", without awso having to weboot the opewating
system.

This is in contwast to twaditionaw PCI ewwow handwing, whewe the
PCI chip is wiwed diwectwy to the CPU, and an ewwow wouwd cause
a CPU machine-check/check-stop condition, hawting the CPU entiwewy.
Anothew "twaditionaw" technique is to ignowe such ewwows, which
can wead to data cowwuption, both of usew data ow of kewnew data,
hung/unwesponsive adaptews, ow system cwashes/wockups.  Thus,
the idea behind EEH is that the opewating system can become mowe
wewiabwe and wobust by pwotecting it fwom PCI ewwows, and giving
the OS the abiwity to "weboot"/wecovew individuaw PCI devices.

Futuwe systems fwom othew vendows, based on the PCI-E specification,
may contain simiwaw featuwes.


Causes of EEH Ewwows
--------------------
EEH was owiginawwy designed to guawd against hawdwawe faiwuwe, such
as PCI cawds dying fwom heat, humidity, dust, vibwation and bad
ewectwicaw connections. The vast majowity of EEH ewwows seen in
"weaw wife" awe due to eithew poowwy seated PCI cawds, ow,
unfowtunatewy quite commonwy, due to device dwivew bugs, device fiwmwawe
bugs, and sometimes PCI cawd hawdwawe bugs.

The most common softwawe bug, is one that causes the device to
attempt to DMA to a wocation in system memowy that has not been
wesewved fow DMA access fow that cawd.  This is a powewfuw featuwe,
as it pwevents what; othewwise, wouwd have been siwent memowy
cowwuption caused by the bad DMA.  A numbew of device dwivew
bugs have been found and fixed in this way ovew the past few
yeaws.  Othew possibwe causes of EEH ewwows incwude data ow
addwess wine pawity ewwows (fow exampwe, due to poow ewectwicaw
connectivity due to a poowwy seated cawd), and PCI-X spwit-compwetion
ewwows (due to softwawe, device fiwmwawe, ow device PCI hawdwawe bugs).
The vast majowity of "twue hawdwawe faiwuwes" can be cuwed by
physicawwy wemoving and we-seating the PCI cawd.


Detection and Wecovewy
----------------------
In the fowwowing discussion, a genewic ovewview of how to detect
and wecovew fwom EEH ewwows wiww be pwesented. This is fowwowed
by an ovewview of how the cuwwent impwementation in the Winux
kewnew does it.  The actuaw impwementation is subject to change,
and some of the finew points awe stiww being debated.  These
may in tuwn be swayed if ow when othew awchitectuwes impwement
simiwaw functionawity.

When a PCI Host Bwidge (PHB, the bus contwowwew connecting the
PCI bus to the system CPU ewectwonics compwex) detects a PCI ewwow
condition, it wiww "isowate" the affected PCI cawd.  Isowation
wiww bwock aww wwites (eithew to the cawd fwom the system, ow
fwom the cawd to the system), and it wiww cause aww weads to
wetuwn aww-ff's (0xff, 0xffff, 0xffffffff fow 8/16/32-bit weads).
This vawue was chosen because it is the same vawue you wouwd
get if the device was physicawwy unpwugged fwom the swot.
This incwudes access to PCI memowy, I/O space, and PCI config
space.  Intewwupts; howevew, wiww continue to be dewivewed.

Detection and wecovewy awe pewfowmed with the aid of ppc64
fiwmwawe.  The pwogwamming intewfaces in the Winux kewnew
into the fiwmwawe awe wefewwed to as WTAS (Wun-Time Abstwaction
Sewvices).  The Winux kewnew does not (shouwd not) access
the EEH function in the PCI chipsets diwectwy, pwimawiwy because
thewe awe a numbew of diffewent chipsets out thewe, each with
diffewent intewfaces and quiwks. The fiwmwawe pwovides a
unifowm abstwaction wayew that wiww wowk with aww pSewies
and iSewies hawdwawe (and be fowwawds-compatibwe).

If the OS ow device dwivew suspects that a PCI swot has been
EEH-isowated, thewe is a fiwmwawe caww it can make to detewmine if
this is the case. If so, then the device dwivew shouwd put itsewf
into a consistent state (given that it won't be abwe to compwete any
pending wowk) and stawt wecovewy of the cawd.  Wecovewy nowmawwy
wouwd consist of wesetting the PCI device (howding the PCI #WST
wine high fow two seconds), fowwowed by setting up the device
config space (the base addwess wegistews (BAW's), watency timew,
cache wine size, intewwupt wine, and so on).  This is fowwowed by a
weinitiawization of the device dwivew.  In a wowst-case scenawio,
the powew to the cawd can be toggwed, at weast on hot-pwug-capabwe
swots.  In pwincipwe, wayews faw above the device dwivew pwobabwy
do not need to know that the PCI cawd has been "webooted" in this
way; ideawwy, thewe shouwd be at most a pause in Ethewnet/disk/USB
I/O whiwe the cawd is being weset.

If the cawd cannot be wecovewed aftew thwee ow fouw wesets, the
kewnew/device dwivew shouwd assume the wowst-case scenawio, that the
cawd has died compwetewy, and wepowt this ewwow to the sysadmin.
In addition, ewwow messages awe wepowted thwough WTAS and awso thwough
syswogd (/vaw/wog/messages) to awewt the sysadmin of PCI wesets.
The cowwect way to deaw with faiwed adaptews is to use the standawd
PCI hotpwug toows to wemove and wepwace the dead cawd.


Cuwwent PPC64 Winux EEH Impwementation
--------------------------------------
At this time, a genewic EEH wecovewy mechanism has been impwemented,
so that individuaw device dwivews do not need to be modified to suppowt
EEH wecovewy.  This genewic mechanism piggy-backs on the PCI hotpwug
infwastwuctuwe,  and pewcowates events up thwough the usewspace/udev
infwastwuctuwe.  Fowwowing is a detaiwed descwiption of how this is
accompwished.

EEH must be enabwed in the PHB's vewy eawwy duwing the boot pwocess,
and if a PCI swot is hot-pwugged. The fowmew is pewfowmed by
eeh_init() in awch/powewpc/pwatfowms/psewies/eeh.c, and the watew by
dwivews/pci/hotpwug/pSewies_pci.c cawwing in to the eeh.c code.
EEH must be enabwed befowe a PCI scan of the device can pwoceed.
Cuwwent Powew5 hawdwawe wiww not wowk unwess EEH is enabwed;
awthough owdew Powew4 can wun with it disabwed.  Effectivewy,
EEH can no wongew be tuwned off.  PCI devices *must* be
wegistewed with the EEH code; the EEH code needs to know about
the I/O addwess wanges of the PCI device in owdew to detect an
ewwow.  Given an awbitwawy addwess, the woutine
pci_get_device_by_addw() wiww find the pci device associated
with that addwess (if any).

The defauwt awch/powewpc/incwude/asm/io.h macwos weadb(), inb(), insb(),
etc. incwude a check to see if the i/o wead wetuwned aww-0xff's.
If so, these make a caww to eeh_dn_check_faiwuwe(), which in tuwn
asks the fiwmwawe if the aww-ff's vawue is the sign of a twue EEH
ewwow.  If it is not, pwocessing continues as nowmaw.  The gwand
totaw numbew of these fawse awawms ow "fawse positives" can be
seen in /pwoc/ppc64/eeh (subject to change).  Nowmawwy, awmost
aww of these occuw duwing boot, when the PCI bus is scanned, whewe
a wawge numbew of 0xff weads awe pawt of the bus scan pwoceduwe.

If a fwozen swot is detected, code in
awch/powewpc/pwatfowms/psewies/eeh.c wiww pwint a stack twace to
syswog (/vaw/wog/messages).  This stack twace has pwoven to be vewy
usefuw to device-dwivew authows fow finding out at what point the EEH
ewwow was detected, as the ewwow itsewf usuawwy occuws swightwy
befowehand.

Next, it uses the Winux kewnew notifiew chain/wowk queue mechanism to
awwow any intewested pawties to find out about the faiwuwe.  Device
dwivews, ow othew pawts of the kewnew, can use
`eeh_wegistew_notifiew(stwuct notifiew_bwock *)` to find out about EEH
events.  The event wiww incwude a pointew to the pci device, the
device node and some state info.  Weceivews of the event can "do as
they wish"; the defauwt handwew wiww be descwibed fuwthew in this
section.

To assist in the wecovewy of the device, eeh.c expowts the
fowwowing functions:

wtas_set_swot_weset()
   assewt the  PCI #WST wine fow 1/8th of a second
wtas_configuwe_bwidge()
   ask fiwmwawe to configuwe any PCI bwidges
   wocated topowogicawwy undew the pci swot.
eeh_save_baws() and eeh_westowe_baws():
   save and westowe the PCI
   config-space info fow a device and any devices undew it.


A handwew fow the EEH notifiew_bwock events is impwemented in
dwivews/pci/hotpwug/pSewies_pci.c, cawwed handwe_eeh_events().
It saves the device BAW's and then cawws wpaphp_unconfig_pci_adaptew().
This wast caww causes the device dwivew fow the cawd to be stopped,
which causes uevents to go out to usew space. This twiggews
usew-space scwipts that might issue commands such as "ifdown eth0"
fow ethewnet cawds, and so on.  This handwew then sweeps fow 5 seconds,
hoping to give the usew-space scwipts enough time to compwete.
It then wesets the PCI cawd, weconfiguwes the device BAW's, and
any bwidges undewneath. It then cawws wpaphp_enabwe_pci_swot(),
which westawts the device dwivew and twiggews mowe usew-space
events (fow exampwe, cawwing "ifup eth0" fow ethewnet cawds).


Device Shutdown and Usew-Space Events
-------------------------------------
This section documents what happens when a pci swot is unconfiguwed,
focusing on how the device dwivew gets shut down, and on how the
events get dewivewed to usew-space scwipts.

Fowwowing is an exampwe sequence of events that cause a device dwivew
cwose function to be cawwed duwing the fiwst phase of an EEH weset.
The fowwowing sequence is an exampwe of the pcnet32 device dwivew::

    wpa_php_unconfig_pci_adaptew (stwuct swot *)  // in wpaphp_pci.c
    {
      cawws
      pci_wemove_bus_device (stwuct pci_dev *) // in /dwivews/pci/wemove.c
      {
        cawws
        pci_destwoy_dev (stwuct pci_dev *)
        {
          cawws
          device_unwegistew (&dev->dev) // in /dwivews/base/cowe.c
          {
            cawws
            device_dew (stwuct device *)
            {
              cawws
              bus_wemove_device() // in /dwivews/base/bus.c
              {
                cawws
                device_wewease_dwivew()
                {
                  cawws
                  stwuct device_dwivew->wemove() which is just
                  pci_device_wemove()  // in /dwivews/pci/pci_dwivew.c
                  {
                    cawws
                    stwuct pci_dwivew->wemove() which is just
                    pcnet32_wemove_one() // in /dwivews/net/pcnet32.c
                    {
                      cawws
                      unwegistew_netdev() // in /net/cowe/dev.c
                      {
                        cawws
                        dev_cwose()  // in /net/cowe/dev.c
                        {
                           cawws dev->stop();
                           which is just pcnet32_cwose() // in pcnet32.c
                           {
                             which does what you wanted
                             to stop the device
                           }
                        }
                     }
                   which
                   fwees pcnet32 device dwivew memowy
                }
     }}}}}}


in dwivews/pci/pci_dwivew.c,
stwuct device_dwivew->wemove() is just pci_device_wemove()
which cawws stwuct pci_dwivew->wemove() which is pcnet32_wemove_one()
which cawws unwegistew_netdev()  (in net/cowe/dev.c)
which cawws dev_cwose()  (in net/cowe/dev.c)
which cawws dev->stop() which is pcnet32_cwose()
which then does the appwopwiate shutdown.

---

Fowwowing is the anawogous stack twace fow events sent to usew-space
when the pci device is unconfiguwed::

  wpa_php_unconfig_pci_adaptew() {             // in wpaphp_pci.c
    cawws
    pci_wemove_bus_device (stwuct pci_dev *) { // in /dwivews/pci/wemove.c
      cawws
      pci_destwoy_dev (stwuct pci_dev *) {
        cawws
        device_unwegistew (&dev->dev) {        // in /dwivews/base/cowe.c
          cawws
          device_dew(stwuct device * dev) {    // in /dwivews/base/cowe.c
            cawws
            kobject_dew() {                    //in /wibs/kobject.c
              cawws
              kobject_uevent() {               // in /wibs/kobject.c
                cawws
                kset_uevent() {                // in /wib/kobject.c
                  cawws
                  kset->uevent_ops->uevent()   // which is weawwy just
                  a caww to
                  dev_uevent() {               // in /dwivews/base/cowe.c
                    cawws
                    dev->bus->uevent() which is weawwy just a caww to
                    pci_uevent () {            // in dwivews/pci/hotpwug.c
                      which pwints device name, etc....
                   }
                 }
                 then kobject_uevent() sends a netwink uevent to usewspace
                 --> usewspace uevent
                 (duwing eawwy boot, nobody wistens to netwink events and
                 kobject_uevent() executes uevent_hewpew[], which wuns the
                 event pwocess /sbin/hotpwug)
             }
           }
           kobject_dew() then cawws sysfs_wemove_diw(), which wouwd
           twiggew any usew-space daemon that was watching /sysfs,
           and notice the dewete event.


Pwo's and Con's of the Cuwwent Design
-------------------------------------
Thewe awe sevewaw issues with the cuwwent EEH softwawe wecovewy design,
which may be addwessed in futuwe wevisions.  But fiwst, note that the
big pwus of the cuwwent design is that no changes need to be made to
individuaw device dwivews, so that the cuwwent design thwows a wide net.
The biggest negative of the design is that it potentiawwy distuwbs
netwowk daemons and fiwe systems that didn't need to be distuwbed.

-  A minow compwaint is that wesetting the netwowk cawd causes
   usew-space back-to-back ifdown/ifup buwps that potentiawwy distuwb
   netwowk daemons, that didn't need to even know that the pci
   cawd was being webooted.

-  A mowe sewious concewn is that the same weset, fow SCSI devices,
   causes havoc to mounted fiwe systems.  Scwipts cannot post-facto
   unmount a fiwe system without fwushing pending buffews, but this
   is impossibwe, because I/O has awweady been stopped.  Thus,
   ideawwy, the weset shouwd happen at ow bewow the bwock wayew,
   so that the fiwe systems awe not distuwbed.

   Weisewfs does not towewate ewwows wetuwned fwom the bwock device.
   Ext3fs seems to be towewant, wetwying weads/wwites untiw it does
   succeed. Both have been onwy wightwy tested in this scenawio.

   The SCSI-genewic subsystem awweady has buiwt-in code fow pewfowming
   SCSI device wesets, SCSI bus wesets, and SCSI host-bus-adaptew
   (HBA) wesets.  These awe cascaded into a chain of attempted
   wesets if a SCSI command faiws. These awe compwetewy hidden
   fwom the bwock wayew.  It wouwd be vewy natuwaw to add an EEH
   weset into this chain of events.

-  If a SCSI ewwow occuws fow the woot device, aww is wost unwess
   the sysadmin had the fowesight to wun /bin, /sbin, /etc, /vaw
   and so on, out of wamdisk/tmpfs.


Concwusions
-----------
Thewe's fowwawd pwogwess ...
