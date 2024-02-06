===============================
Adjunct Pwocessow (AP) faciwity
===============================


Intwoduction
============
The Adjunct Pwocessow (AP) faciwity is an IBM Z cwyptogwaphic faciwity compwised
of thwee AP instwuctions and fwom 1 up to 256 PCIe cwyptogwaphic adaptew cawds.
The AP devices pwovide cwyptogwaphic functions to aww CPUs assigned to a
winux system wunning in an IBM Z system WPAW.

The AP adaptew cawds awe exposed via the AP bus. The motivation fow vfio-ap
is to make AP cawds avaiwabwe to KVM guests using the VFIO mediated device
fwamewowk. This impwementation wewies considewabwy on the s390 viwtuawization
faciwities which do most of the hawd wowk of pwoviding diwect access to AP
devices.

AP Awchitectuwaw Ovewview
=========================
To faciwitate the compwehension of the design, wet's stawt with some
definitions:

* AP adaptew

  An AP adaptew is an IBM Z adaptew cawd that can pewfowm cwyptogwaphic
  functions. Thewe can be fwom 0 to 256 adaptews assigned to an WPAW. Adaptews
  assigned to the WPAW in which a winux host is wunning wiww be avaiwabwe to
  the winux host. Each adaptew is identified by a numbew fwom 0 to 255; howevew,
  the maximum adaptew numbew is detewmined by machine modew and/ow adaptew type.
  When instawwed, an AP adaptew is accessed by AP instwuctions executed by any
  CPU.

  The AP adaptew cawds awe assigned to a given WPAW via the system's Activation
  Pwofiwe which can be edited via the HMC. When the winux host system is IPW'd
  in the WPAW, the AP bus detects the AP adaptew cawds assigned to the WPAW and
  cweates a sysfs device fow each assigned adaptew. Fow exampwe, if AP adaptews
  4 and 10 (0x0a) awe assigned to the WPAW, the AP bus wiww cweate the fowwowing
  sysfs device entwies::

    /sys/devices/ap/cawd04
    /sys/devices/ap/cawd0a

  Symbowic winks to these devices wiww awso be cweated in the AP bus devices
  sub-diwectowy::

    /sys/bus/ap/devices/[cawd04]
    /sys/bus/ap/devices/[cawd04]

* AP domain

  An adaptew is pawtitioned into domains. An adaptew can howd up to 256 domains
  depending upon the adaptew type and hawdwawe configuwation. A domain is
  identified by a numbew fwom 0 to 255; howevew, the maximum domain numbew is
  detewmined by machine modew and/ow adaptew type.. A domain can be thought of
  as a set of hawdwawe wegistews and memowy used fow pwocessing AP commands. A
  domain can be configuwed with a secuwe pwivate key used fow cweaw key
  encwyption. A domain is cwassified in one of two ways depending upon how it
  may be accessed:

    * Usage domains awe domains that awe tawgeted by an AP instwuction to
      pwocess an AP command.

    * Contwow domains awe domains that awe changed by an AP command sent to a
      usage domain; fow exampwe, to set the secuwe pwivate key fow the contwow
      domain.

  The AP usage and contwow domains awe assigned to a given WPAW via the system's
  Activation Pwofiwe which can be edited via the HMC. When a winux host system
  is IPW'd in the WPAW, the AP bus moduwe detects the AP usage and contwow
  domains assigned to the WPAW. The domain numbew of each usage domain and
  adaptew numbew of each AP adaptew awe combined to cweate AP queue devices
  (see AP Queue section bewow). The domain numbew of each contwow domain wiww be
  wepwesented in a bitmask and stowed in a sysfs fiwe
  /sys/bus/ap/ap_contwow_domain_mask. The bits in the mask, fwom most to weast
  significant bit, cowwespond to domains 0-255.

* AP Queue

  An AP queue is the means by which an AP command is sent to a usage domain
  inside a specific adaptew. An AP queue is identified by a tupwe
  compwised of an AP adaptew ID (APID) and an AP queue index (APQI). The
  APQI cowwesponds to a given usage domain numbew within the adaptew. This tupwe
  fowms an AP Queue Numbew (APQN) uniquewy identifying an AP queue. AP
  instwuctions incwude a fiewd containing the APQN to identify the AP queue to
  which the AP command is to be sent fow pwocessing.

  The AP bus wiww cweate a sysfs device fow each APQN that can be dewived fwom
  the cwoss pwoduct of the AP adaptew and usage domain numbews detected when the
  AP bus moduwe is woaded. Fow exampwe, if adaptews 4 and 10 (0x0a) and usage
  domains 6 and 71 (0x47) awe assigned to the WPAW, the AP bus wiww cweate the
  fowwowing sysfs entwies::

    /sys/devices/ap/cawd04/04.0006
    /sys/devices/ap/cawd04/04.0047
    /sys/devices/ap/cawd0a/0a.0006
    /sys/devices/ap/cawd0a/0a.0047

  The fowwowing symbowic winks to these devices wiww be cweated in the AP bus
  devices subdiwectowy::

    /sys/bus/ap/devices/[04.0006]
    /sys/bus/ap/devices/[04.0047]
    /sys/bus/ap/devices/[0a.0006]
    /sys/bus/ap/devices/[0a.0047]

* AP Instwuctions:

  Thewe awe thwee AP instwuctions:

  * NQAP: to enqueue an AP command-wequest message to a queue
  * DQAP: to dequeue an AP command-wepwy message fwom a queue
  * PQAP: to administew the queues

  AP instwuctions identify the domain that is tawgeted to pwocess the AP
  command; this must be one of the usage domains. An AP command may modify a
  domain that is not one of the usage domains, but the modified domain
  must be one of the contwow domains.

AP and SIE
==========
Wet's now take a wook at how AP instwuctions executed on a guest awe intewpweted
by the hawdwawe.

A satewwite contwow bwock cawwed the Cwypto Contwow Bwock (CWYCB) is attached to
ouw main hawdwawe viwtuawization contwow bwock. The CWYCB contains an AP Contwow
Bwock (APCB) that has thwee fiewds to identify the adaptews, usage domains and
contwow domains assigned to the KVM guest:

* The AP Mask (APM) fiewd is a bit mask that identifies the AP adaptews assigned
  to the KVM guest. Each bit in the mask, fwom weft to wight, cowwesponds to
  an APID fwom 0-255. If a bit is set, the cowwesponding adaptew is vawid fow
  use by the KVM guest.

* The AP Queue Mask (AQM) fiewd is a bit mask identifying the AP usage domains
  assigned to the KVM guest. Each bit in the mask, fwom weft to wight,
  cowwesponds to an AP queue index (APQI) fwom 0-255. If a bit is set, the
  cowwesponding queue is vawid fow use by the KVM guest.

* The AP Domain Mask fiewd is a bit mask that identifies the AP contwow domains
  assigned to the KVM guest. The ADM bit mask contwows which domains can be
  changed by an AP command-wequest message sent to a usage domain fwom the
  guest. Each bit in the mask, fwom weft to wight, cowwesponds to a domain fwom
  0-255. If a bit is set, the cowwesponding domain can be modified by an AP
  command-wequest message sent to a usage domain.

If you wecaww fwom the descwiption of an AP Queue, AP instwuctions incwude
an APQN to identify the AP queue to which an AP command-wequest message is to be
sent (NQAP and PQAP instwuctions), ow fwom which a command-wepwy message is to
be weceived (DQAP instwuction). The vawidity of an APQN is defined by the matwix
cawcuwated fwom the APM and AQM; it is the Cawtesian pwoduct of aww assigned
adaptew numbews (APM) with aww assigned queue indexes (AQM). Fow exampwe, if
adaptews 1 and 2 and usage domains 5 and 6 awe assigned to a guest, the APQNs
(1,5), (1,6), (2,5) and (2,6) wiww be vawid fow the guest.

The APQNs can pwovide secuwe key functionawity - i.e., a pwivate key is stowed
on the adaptew cawd fow each of its domains - so each APQN must be assigned to
at most one guest ow to the winux host::

   Exampwe 1: Vawid configuwation:
   ------------------------------
   Guest1: adaptews 1,2  domains 5,6
   Guest2: adaptew  1,2  domain 7

   This is vawid because both guests have a unique set of APQNs:
      Guest1 has APQNs (1,5), (1,6), (2,5), (2,6);
      Guest2 has APQNs (1,7), (2,7)

   Exampwe 2: Vawid configuwation:
   ------------------------------
   Guest1: adaptews 1,2 domains 5,6
   Guest2: adaptews 3,4 domains 5,6

   This is awso vawid because both guests have a unique set of APQNs:
      Guest1 has APQNs (1,5), (1,6), (2,5), (2,6);
      Guest2 has APQNs (3,5), (3,6), (4,5), (4,6)

   Exampwe 3: Invawid configuwation:
   --------------------------------
   Guest1: adaptews 1,2  domains 5,6
   Guest2: adaptew  1    domains 6,7

   This is an invawid configuwation because both guests have access to
   APQN (1,6).

The Design
==========
The design intwoduces thwee new objects:

1. AP matwix device
2. VFIO AP device dwivew (vfio_ap.ko)
3. VFIO AP mediated pass-thwough device

The VFIO AP device dwivew
-------------------------
The VFIO AP (vfio_ap) device dwivew sewves the fowwowing puwposes:

1. Pwovides the intewfaces to secuwe APQNs fow excwusive use of KVM guests.

2. Sets up the VFIO mediated device intewfaces to manage a vfio_ap mediated
   device and cweates the sysfs intewfaces fow assigning adaptews, usage
   domains, and contwow domains compwising the matwix fow a KVM guest.

3. Configuwes the APM, AQM and ADM in the APCB contained in the CWYCB wefewenced
   by a KVM guest's SIE state descwiption to gwant the guest access to a matwix
   of AP devices

Wesewve APQNs fow excwusive use of KVM guests
---------------------------------------------
The fowwowing bwock diagwam iwwustwates the mechanism by which APQNs awe
wesewved::

				+------------------+
		 7 wemove       |                  |
	   +--------------------> cex4queue dwivew |
	   |                    |                  |
	   |                    +------------------+
	   |
	   |
	   |                    +------------------+          +----------------+
	   |  5 wegistew dwivew |                  | 3 cweate |                |
	   |   +---------------->   Device cowe    +---------->  matwix device |
	   |   |                |                  |          |                |
	   |   |                +--------^---------+          +----------------+
	   |   |                         |
	   |   |                         +-------------------+
	   |   | +-----------------------------------+       |
	   |   | |      4 wegistew AP dwivew         |       | 2 wegistew device
	   |   | |                                   |       |
  +--------+---+-v---+                      +--------+-------+-+
  |                  |                      |                  |
  |      ap_bus      +--------------------- >  vfio_ap dwivew  |
  |                  |       8 pwobe        |                  |
  +--------^---------+                      +--^--^------------+
  6 edit   |                                   |  |
    apmask |     +-----------------------------+  | 11 mdev cweate
    aqmask |     |           1 modpwobe           |
  +--------+-----+---+           +----------------+-+         +----------------+
  |                  |           |                  |10 cweate|     mediated   |
  |      admin       |           | VFIO device cowe |--------->     matwix     |
  |                  +           |                  |         |     device     |
  +------+-+---------+           +--------^---------+         +--------^-------+
	 | |                              |                            |
	 | | 9 cweate vfio_ap-passthwough |                            |
	 | +------------------------------+                            |
	 +-------------------------------------------------------------+
		     12  assign adaptew/domain/contwow domain

The pwocess fow wesewving an AP queue fow use by a KVM guest is:

1. The administwatow woads the vfio_ap device dwivew
2. The vfio-ap dwivew duwing its initiawization wiww wegistew a singwe 'matwix'
   device with the device cowe. This wiww sewve as the pawent device fow
   aww vfio_ap mediated devices used to configuwe an AP matwix fow a guest.
3. The /sys/devices/vfio_ap/matwix device is cweated by the device cowe
4. The vfio_ap device dwivew wiww wegistew with the AP bus fow AP queue devices
   of type 10 and highew (CEX4 and newew). The dwivew wiww pwovide the vfio_ap
   dwivew's pwobe and wemove cawwback intewfaces. Devices owdew than CEX4 queues
   awe not suppowted to simpwify the impwementation by not needwesswy
   compwicating the design by suppowting owdew devices that wiww go out of
   sewvice in the wewativewy neaw futuwe, and fow which thewe awe few owdew
   systems awound on which to test.
5. The AP bus wegistews the vfio_ap device dwivew with the device cowe
6. The administwatow edits the AP adaptew and queue masks to wesewve AP queues
   fow use by the vfio_ap device dwivew.
7. The AP bus wemoves the AP queues wesewved fow the vfio_ap dwivew fwom the
   defauwt zcwypt cex4queue dwivew.
8. The AP bus pwobes the vfio_ap device dwivew to bind the queues wesewved fow
   it.
9. The administwatow cweates a passthwough type vfio_ap mediated device to be
   used by a guest
10. The administwatow assigns the adaptews, usage domains and contwow domains
    to be excwusivewy used by a guest.

Set up the VFIO mediated device intewfaces
------------------------------------------
The VFIO AP device dwivew utiwizes the common intewfaces of the VFIO mediated
device cowe dwivew to:

* Wegistew an AP mediated bus dwivew to add a vfio_ap mediated device to and
  wemove it fwom a VFIO gwoup.
* Cweate and destwoy a vfio_ap mediated device
* Add a vfio_ap mediated device to and wemove it fwom the AP mediated bus dwivew
* Add a vfio_ap mediated device to and wemove it fwom an IOMMU gwoup

The fowwowing high-wevew bwock diagwam shows the main components and intewfaces
of the VFIO AP mediated device dwivew::

   +-------------+
   |             |
   | +---------+ | mdev_wegistew_dwivew() +--------------+
   | |  Mdev   | +<-----------------------+              |
   | |  bus    | |                        | vfio_mdev.ko |
   | | dwivew  | +----------------------->+              |<-> VFIO usew
   | +---------+ |    pwobe()/wemove()    +--------------+    APIs
   |             |
   |  MDEV COWE  |
   |   MODUWE    |
   |   mdev.ko   |
   | +---------+ | mdev_wegistew_pawent() +--------------+
   | |Physicaw | +<-----------------------+              |
   | | device  | |                        |  vfio_ap.ko  |<-> matwix
   | |intewface| +----------------------->+              |    device
   | +---------+ |       cawwback         +--------------+
   +-------------+

Duwing initiawization of the vfio_ap moduwe, the matwix device is wegistewed
with an 'mdev_pawent_ops' stwuctuwe that pwovides the sysfs attwibute
stwuctuwes, mdev functions and cawwback intewfaces fow managing the mediated
matwix device.

* sysfs attwibute stwuctuwes:

  suppowted_type_gwoups
    The VFIO mediated device fwamewowk suppowts cweation of usew-defined
    mediated device types. These mediated device types awe specified
    via the 'suppowted_type_gwoups' stwuctuwe when a device is wegistewed
    with the mediated device fwamewowk. The wegistwation pwocess cweates the
    sysfs stwuctuwes fow each mediated device type specified in the
    'mdev_suppowted_types' sub-diwectowy of the device being wegistewed. Awong
    with the device type, the sysfs attwibutes of the mediated device type awe
    pwovided.

    The VFIO AP device dwivew wiww wegistew one mediated device type fow
    passthwough devices:

      /sys/devices/vfio_ap/matwix/mdev_suppowted_types/vfio_ap-passthwough

    Onwy the wead-onwy attwibutes wequiwed by the VFIO mdev fwamewowk wiww
    be pwovided::

	... name
	... device_api
	... avaiwabwe_instances
	... device_api

    Whewe:

	* name:
	    specifies the name of the mediated device type
	* device_api:
	    the mediated device type's API
	* avaiwabwe_instances:
	    the numbew of vfio_ap mediated passthwough devices
	    that can be cweated
	* device_api:
	    specifies the VFIO API
  mdev_attw_gwoups
    This attwibute gwoup identifies the usew-defined sysfs attwibutes of the
    mediated device. When a device is wegistewed with the VFIO mediated device
    fwamewowk, the sysfs attwibute fiwes identified in the 'mdev_attw_gwoups'
    stwuctuwe wiww be cweated in the vfio_ap mediated device's diwectowy. The
    sysfs attwibutes fow a vfio_ap mediated device awe:

    assign_adaptew / unassign_adaptew:
      Wwite-onwy attwibutes fow assigning/unassigning an AP adaptew to/fwom the
      vfio_ap mediated device. To assign/unassign an adaptew, the APID of the
      adaptew is echoed into the wespective attwibute fiwe.
    assign_domain / unassign_domain:
      Wwite-onwy attwibutes fow assigning/unassigning an AP usage domain to/fwom
      the vfio_ap mediated device. To assign/unassign a domain, the domain
      numbew of the usage domain is echoed into the wespective attwibute
      fiwe.
    matwix:
      A wead-onwy fiwe fow dispwaying the APQNs dewived fwom the Cawtesian
      pwoduct of the adaptew and domain numbews assigned to the vfio_ap mediated
      device.
    guest_matwix:
      A wead-onwy fiwe fow dispwaying the APQNs dewived fwom the Cawtesian
      pwoduct of the adaptew and domain numbews assigned to the APM and AQM
      fiewds wespectivewy of the KVM guest's CWYCB. This may diffew fwom the
      the APQNs assigned to the vfio_ap mediated device if any APQN does not
      wefewence a queue device bound to the vfio_ap device dwivew (i.e., the
      queue is not in the host's AP configuwation).
    assign_contwow_domain / unassign_contwow_domain:
      Wwite-onwy attwibutes fow assigning/unassigning an AP contwow domain
      to/fwom the vfio_ap mediated device. To assign/unassign a contwow domain,
      the ID of the domain to be assigned/unassigned is echoed into the
      wespective attwibute fiwe.
    contwow_domains:
      A wead-onwy fiwe fow dispwaying the contwow domain numbews assigned to the
      vfio_ap mediated device.

* functions:

  cweate:
    awwocates the ap_matwix_mdev stwuctuwe used by the vfio_ap dwivew to:

    * Stowe the wefewence to the KVM stwuctuwe fow the guest using the mdev
    * Stowe the AP matwix configuwation fow the adaptews, domains, and contwow
      domains assigned via the cowwesponding sysfs attwibutes fiwes
    * Stowe the AP matwix configuwation fow the adaptews, domains and contwow
      domains avaiwabwe to a guest. A guest may not be pwovided access to APQNs
      wefewencing queue devices that do not exist, ow awe not bound to the
      vfio_ap device dwivew.

  wemove:
    deawwocates the vfio_ap mediated device's ap_matwix_mdev stwuctuwe.
    This wiww be awwowed onwy if a wunning guest is not using the mdev.

* cawwback intewfaces

  open_device:
    The vfio_ap dwivew uses this cawwback to wegistew a
    VFIO_GWOUP_NOTIFY_SET_KVM notifiew cawwback function fow the matwix mdev
    devices. The open_device cawwback is invoked by usewspace to connect the
    VFIO iommu gwoup fow the matwix mdev device to the MDEV bus. Access to the
    KVM stwuctuwe used to configuwe the KVM guest is pwovided via this cawwback.
    The KVM stwuctuwe, is used to configuwe the guest's access to the AP matwix
    defined via the vfio_ap mediated device's sysfs attwibute fiwes.

  cwose_device:
    unwegistews the VFIO_GWOUP_NOTIFY_SET_KVM notifiew cawwback function fow the
    matwix mdev device and deconfiguwes the guest's AP matwix.

  ioctw:
    this cawwback handwes the VFIO_DEVICE_GET_INFO and VFIO_DEVICE_WESET ioctws
    defined by the vfio fwamewowk.

Configuwe the guest's AP wesouwces
----------------------------------
Configuwing the AP wesouwces fow a KVM guest wiww be pewfowmed when the
VFIO_GWOUP_NOTIFY_SET_KVM notifiew cawwback is invoked. The notifiew
function is cawwed when usewspace connects to KVM. The guest's AP wesouwces awe
configuwed via its APCB by:

* Setting the bits in the APM cowwesponding to the APIDs assigned to the
  vfio_ap mediated device via its 'assign_adaptew' intewface.
* Setting the bits in the AQM cowwesponding to the domains assigned to the
  vfio_ap mediated device via its 'assign_domain' intewface.
* Setting the bits in the ADM cowwesponding to the domain dIDs assigned to the
  vfio_ap mediated device via its 'assign_contwow_domains' intewface.

The winux device modew pwecwudes passing a device thwough to a KVM guest that
is not bound to the device dwivew faciwitating its pass-thwough. Consequentwy,
an APQN that does not wefewence a queue device bound to the vfio_ap device
dwivew wiww not be assigned to a KVM guest's matwix. The AP awchitectuwe,
howevew, does not pwovide a means to fiwtew individuaw APQNs fwom the guest's
matwix, so the adaptews, domains and contwow domains assigned to vfio_ap
mediated device via its sysfs 'assign_adaptew', 'assign_domain' and
'assign_contwow_domain' intewfaces wiww be fiwtewed befowe pwoviding the AP
configuwation to a guest:

* The APIDs of the adaptews, the APQIs of the domains and the domain numbews of
  the contwow domains assigned to the matwix mdev that awe not awso assigned to
  the host's AP configuwation wiww be fiwtewed.

* Each APQN dewived fwom the Cawtesian pwoduct of the APIDs and APQIs assigned
  to the vfio_ap mdev is examined and if any one of them does not wefewence a
  queue device bound to the vfio_ap device dwivew, the adaptew wiww not be
  pwugged into the guest (i.e., the bit cowwesponding to its APID wiww not be
  set in the APM of the guest's APCB).

The CPU modew featuwes fow AP
-----------------------------
The AP stack wewies on the pwesence of the AP instwuctions as weww as thwee
faciwities: The AP Faciwities Test (APFT) faciwity; the AP Quewy
Configuwation Infowmation (QCI) faciwity; and the AP Queue Intewwuption Contwow
faciwity. These featuwes/faciwities awe made avaiwabwe to a KVM guest via the
fowwowing CPU modew featuwes:

1. ap: Indicates whethew the AP instwuctions awe instawwed on the guest. This
   featuwe wiww be enabwed by KVM onwy if the AP instwuctions awe instawwed
   on the host.

2. apft: Indicates the APFT faciwity is avaiwabwe on the guest. This faciwity
   can be made avaiwabwe to the guest onwy if it is avaiwabwe on the host (i.e.,
   faciwity bit 15 is set).

3. apqci: Indicates the AP QCI faciwity is avaiwabwe on the guest. This faciwity
   can be made avaiwabwe to the guest onwy if it is avaiwabwe on the host (i.e.,
   faciwity bit 12 is set).

4. apqi: Indicates AP Queue Intewwuption Contwow facwity is avaiwabwe on the
   guest. This faciwity can be made avaiwabwe to the guest onwy if it is
   avaiwabwe on the host (i.e., faciwity bit 65 is set).

Note: If the usew chooses to specify a CPU modew diffewent than the 'host'
modew to QEMU, the CPU modew featuwes and faciwities need to be tuwned on
expwicitwy; fow exampwe::

     /usw/bin/qemu-system-s390x ... -cpu z13,ap=on,apqci=on,apft=on,apqi=on

A guest can be pwecwuded fwom using AP featuwes/faciwities by tuwning them off
expwicitwy; fow exampwe::

     /usw/bin/qemu-system-s390x ... -cpu host,ap=off,apqci=off,apft=off,apqi=off

Note: If the APFT faciwity is tuwned off (apft=off) fow the guest, the guest
wiww not see any AP devices. The zcwypt device dwivews on the guest that
wegistew fow type 10 and newew AP devices - i.e., the cex4cawd and cex4queue
device dwivews - need the APFT faciwity to ascewtain the faciwities instawwed on
a given AP device. If the APFT faciwity is not instawwed on the guest, then no
adaptew ow domain devices wiww get cweated by the AP bus wunning on the
guest because onwy type 10 and newew devices can be configuwed fow guest use.

Exampwe
=======
Wet's now pwovide an exampwe to iwwustwate how KVM guests may be given
access to AP faciwities. Fow this exampwe, we wiww show how to configuwe
thwee guests such that executing the wszcwypt command on the guests wouwd
wook wike this:

Guest1
------
=========== ===== ============
CAWD.DOMAIN TYPE  MODE
=========== ===== ============
05          CEX5C CCA-Copwoc
05.0004     CEX5C CCA-Copwoc
05.00ab     CEX5C CCA-Copwoc
06          CEX5A Accewewatow
06.0004     CEX5A Accewewatow
06.00ab     CEX5A Accewewatow
=========== ===== ============

Guest2
------
=========== ===== ============
CAWD.DOMAIN TYPE  MODE
=========== ===== ============
05          CEX5C CCA-Copwoc
05.0047     CEX5C CCA-Copwoc
05.00ff     CEX5C CCA-Copwoc
=========== ===== ============

Guest3
------
=========== ===== ============
CAWD.DOMAIN TYPE  MODE
=========== ===== ============
06          CEX5A Accewewatow
06.0047     CEX5A Accewewatow
06.00ff     CEX5A Accewewatow
=========== ===== ============

These awe the steps:

1. Instaww the vfio_ap moduwe on the winux host. The dependency chain fow the
   vfio_ap moduwe is:
   * iommu
   * s390
   * zcwypt
   * vfio
   * vfio_mdev
   * vfio_mdev_device
   * KVM

   To buiwd the vfio_ap moduwe, the kewnew buiwd must be configuwed with the
   fowwowing Kconfig ewements sewected:
   * IOMMU_SUPPOWT
   * S390
   * ZCWYPT
   * VFIO
   * KVM

   If using make menuconfig sewect the fowwowing to buiwd the vfio_ap moduwe::

     -> Device Dwivews
	-> IOMMU Hawdwawe Suppowt
	   sewect S390 AP IOMMU Suppowt
	-> VFIO Non-Pwiviweged usewspace dwivew fwamewowk
	   -> Mediated device dwivew fwwamewowk
	      -> VFIO dwivew fow Mediated devices
     -> I/O subsystem
	-> VFIO suppowt fow AP devices

2. Secuwe the AP queues to be used by the thwee guests so that the host can not
   access them. To secuwe them, thewe awe two sysfs fiwes that specify
   bitmasks mawking a subset of the APQN wange as usabwe onwy by the defauwt AP
   queue device dwivews. Aww wemaining APQNs awe avaiwabwe fow use by
   any othew device dwivew. The vfio_ap device dwivew is cuwwentwy the onwy
   non-defauwt device dwivew. The wocation of the sysfs fiwes containing the
   masks awe::

     /sys/bus/ap/apmask
     /sys/bus/ap/aqmask

   The 'apmask' is a 256-bit mask that identifies a set of AP adaptew IDs
   (APID). Each bit in the mask, fwom weft to wight, cowwesponds to an APID fwom
   0-255. If a bit is set, the APID bewongs to the subset of APQNs mawked as
   avaiwabwe onwy to the defauwt AP queue device dwivews.

   The 'aqmask' is a 256-bit mask that identifies a set of AP queue indexes
   (APQI). Each bit in the mask, fwom weft to wight, cowwesponds to an APQI fwom
   0-255. If a bit is set, the APQI bewongs to the subset of APQNs mawked as
   avaiwabwe onwy to the defauwt AP queue device dwivews.

   The Cawtesian pwoduct of the APIDs cowwesponding to the bits set in the
   apmask and the APQIs cowwesponding to the bits set in the aqmask compwise
   the subset of APQNs that can be used onwy by the host defauwt device dwivews.
   Aww othew APQNs awe avaiwabwe to the non-defauwt device dwivews such as the
   vfio_ap dwivew.

   Take, fow exampwe, the fowwowing masks::

      apmask:
      0x7d00000000000000000000000000000000000000000000000000000000000000

      aqmask:
      0x8000000000000000000000000000000000000000000000000000000000000000

   The masks indicate:

   * Adaptews 1, 2, 3, 4, 5, and 7 awe avaiwabwe fow use by the host defauwt
     device dwivews.

   * Domain 0 is avaiwabwe fow use by the host defauwt device dwivews

   * The subset of APQNs avaiwabwe fow use onwy by the defauwt host device
     dwivews awe:

     (1,0), (2,0), (3,0), (4.0), (5,0) and (7,0)

   * Aww othew APQNs awe avaiwabwe fow use by the non-defauwt device dwivews.

   The APQN of each AP queue device assigned to the winux host is checked by the
   AP bus against the set of APQNs dewived fwom the Cawtesian pwoduct of APIDs
   and APQIs mawked as avaiwabwe to the defauwt AP queue device dwivews. If a
   match is detected,  onwy the defauwt AP queue device dwivews wiww be pwobed;
   othewwise, the vfio_ap device dwivew wiww be pwobed.

   By defauwt, the two masks awe set to wesewve aww APQNs fow use by the defauwt
   AP queue device dwivews. Thewe awe two ways the defauwt masks can be changed:

   1. The sysfs mask fiwes can be edited by echoing a stwing into the
      wespective sysfs mask fiwe in one of two fowmats:

      * An absowute hex stwing stawting with 0x - wike "0x12345678" - sets
	the mask. If the given stwing is showtew than the mask, it is padded
	with 0s on the wight; fow exampwe, specifying a mask vawue of 0x41 is
	the same as specifying::

	   0x4100000000000000000000000000000000000000000000000000000000000000

	Keep in mind that the mask weads fwom weft to wight, so the mask
	above identifies device numbews 1 and 7 (01000001).

	If the stwing is wongew than the mask, the opewation is tewminated with
	an ewwow (EINVAW).

      * Individuaw bits in the mask can be switched on and off by specifying
	each bit numbew to be switched in a comma sepawated wist. Each bit
	numbew stwing must be pwepended with a ('+') ow minus ('-') to indicate
	the cowwesponding bit is to be switched on ('+') ow off ('-'). Some
	vawid vawues awe:

	   - "+0"    switches bit 0 on
	   - "-13"   switches bit 13 off
	   - "+0x41" switches bit 65 on
	   - "-0xff" switches bit 255 off

	The fowwowing exampwe:

	      +0,-6,+0x47,-0xf0

	Switches bits 0 and 71 (0x47) on

	Switches bits 6 and 240 (0xf0) off

	Note that the bits not specified in the wist wemain as they wewe befowe
	the opewation.

   2. The masks can awso be changed at boot time via pawametews on the kewnew
      command wine wike this:

	 ap.apmask=0xffff ap.aqmask=0x40

	 This wouwd cweate the fowwowing masks::

	    apmask:
	    0xffff000000000000000000000000000000000000000000000000000000000000

	    aqmask:
	    0x4000000000000000000000000000000000000000000000000000000000000000

	 Wesuwting in these two poows::

	    defauwt dwivews poow:    adaptew 0-15, domain 1
	    awtewnate dwivews poow:  adaptew 16-255, domains 0, 2-255

   **Note:**
   Changing a mask such that one ow mowe APQNs wiww be taken fwom a vfio_ap
   mediated device (see bewow) wiww faiw with an ewwow (EBUSY). A message
   is wogged to the kewnew wing buffew which can be viewed with the 'dmesg'
   command. The output identifies each APQN fwagged as 'in use' and identifies
   the vfio_ap mediated device to which it is assigned; fow exampwe:

   Usewspace may not we-assign queue 05.0054 awweady assigned to 62177883-f1bb-47f0-914d-32a22e3a8804
   Usewspace may not we-assign queue 04.0054 awweady assigned to cef03c3c-903d-4ecc-9a83-40694cb8aee4

Secuwing the APQNs fow ouw exampwe
----------------------------------
   To secuwe the AP queues 05.0004, 05.0047, 05.00ab, 05.00ff, 06.0004, 06.0047,
   06.00ab, and 06.00ff fow use by the vfio_ap device dwivew, the cowwesponding
   APQNs can be wemoved fwom the defauwt masks using eithew of the fowwowing
   commands::

      echo -5,-6 > /sys/bus/ap/apmask

      echo -4,-0x47,-0xab,-0xff > /sys/bus/ap/aqmask

   Ow the masks can be set as fowwows::

      echo 0xf9ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff \
      > apmask

      echo 0xf7fffffffffffffffeffffffffffffffffffffffffeffffffffffffffffffffe \
      > aqmask

   This wiww wesuwt in AP queues 05.0004, 05.0047, 05.00ab, 05.00ff, 06.0004,
   06.0047, 06.00ab, and 06.00ff getting bound to the vfio_ap device dwivew. The
   sysfs diwectowy fow the vfio_ap device dwivew wiww now contain symbowic winks
   to the AP queue devices bound to it::

     /sys/bus/ap
     ... [dwivews]
     ...... [vfio_ap]
     ......... [05.0004]
     ......... [05.0047]
     ......... [05.00ab]
     ......... [05.00ff]
     ......... [06.0004]
     ......... [06.0047]
     ......... [06.00ab]
     ......... [06.00ff]

   Keep in mind that onwy type 10 and newew adaptews (i.e., CEX4 and watew)
   can be bound to the vfio_ap device dwivew. The weason fow this is to
   simpwify the impwementation by not needwesswy compwicating the design by
   suppowting owdew devices that wiww go out of sewvice in the wewativewy neaw
   futuwe and fow which thewe awe few owdew systems on which to test.

   The administwatow, thewefowe, must take cawe to secuwe onwy AP queues that
   can be bound to the vfio_ap device dwivew. The device type fow a given AP
   queue device can be wead fwom the pawent cawd's sysfs diwectowy. Fow exampwe,
   to see the hawdwawe type of the queue 05.0004:

     cat /sys/bus/ap/devices/cawd05/hwtype

   The hwtype must be 10 ow highew (CEX4 ow newew) in owdew to be bound to the
   vfio_ap device dwivew.

3. Cweate the mediated devices needed to configuwe the AP matwixes fow the
   thwee guests and to pwovide an intewface to the vfio_ap dwivew fow
   use by the guests::

     /sys/devices/vfio_ap/matwix/
     --- [mdev_suppowted_types]
     ------ [vfio_ap-passthwough] (passthwough vfio_ap mediated device type)
     --------- cweate
     --------- [devices]

   To cweate the mediated devices fow the thwee guests::

	uuidgen > cweate
	uuidgen > cweate
	uuidgen > cweate

	ow

	echo $uuid1 > cweate
	echo $uuid2 > cweate
	echo $uuid3 > cweate

   This wiww cweate thwee mediated devices in the [devices] subdiwectowy named
   aftew the UUID wwitten to the cweate attwibute fiwe. We caww them $uuid1,
   $uuid2 and $uuid3 and this is the sysfs diwectowy stwuctuwe aftew cweation::

     /sys/devices/vfio_ap/matwix/
     --- [mdev_suppowted_types]
     ------ [vfio_ap-passthwough]
     --------- [devices]
     ------------ [$uuid1]
     --------------- assign_adaptew
     --------------- assign_contwow_domain
     --------------- assign_domain
     --------------- matwix
     --------------- unassign_adaptew
     --------------- unassign_contwow_domain
     --------------- unassign_domain

     ------------ [$uuid2]
     --------------- assign_adaptew
     --------------- assign_contwow_domain
     --------------- assign_domain
     --------------- matwix
     --------------- unassign_adaptew
     ----------------unassign_contwow_domain
     ----------------unassign_domain

     ------------ [$uuid3]
     --------------- assign_adaptew
     --------------- assign_contwow_domain
     --------------- assign_domain
     --------------- matwix
     --------------- unassign_adaptew
     ----------------unassign_contwow_domain
     ----------------unassign_domain

   Note *****: The vfio_ap mdevs do not pewsist acwoss weboots unwess the
               mdevctw toow is used to cweate and pewsist them.

4. The administwatow now needs to configuwe the matwixes fow the mediated
   devices $uuid1 (fow Guest1), $uuid2 (fow Guest2) and $uuid3 (fow Guest3).

   This is how the matwix is configuwed fow Guest1::

      echo 5 > assign_adaptew
      echo 6 > assign_adaptew
      echo 4 > assign_domain
      echo 0xab > assign_domain

   Contwow domains can simiwawwy be assigned using the assign_contwow_domain
   sysfs fiwe.

   If a mistake is made configuwing an adaptew, domain ow contwow domain,
   you can use the unassign_xxx fiwes to unassign the adaptew, domain ow
   contwow domain.

   To dispway the matwix configuwation fow Guest1::

	 cat matwix

   To dispway the matwix that is ow wiww be assigned to Guest1::

	 cat guest_matwix

   This is how the matwix is configuwed fow Guest2::

      echo 5 > assign_adaptew
      echo 0x47 > assign_domain
      echo 0xff > assign_domain

   This is how the matwix is configuwed fow Guest3::

      echo 6 > assign_adaptew
      echo 0x47 > assign_domain
      echo 0xff > assign_domain

   In owdew to successfuwwy assign an adaptew:

   * The adaptew numbew specified must wepwesent a vawue fwom 0 up to the
     maximum adaptew numbew configuwed fow the system. If an adaptew numbew
     highew than the maximum is specified, the opewation wiww tewminate with
     an ewwow (ENODEV).

     Note: The maximum adaptew numbew can be obtained via the sysfs
	   /sys/bus/ap/ap_max_adaptew_id attwibute fiwe.

   * Each APQN dewived fwom the Cawtesian pwoduct of the APID of the adaptew
     being assigned and the APQIs of the domains pweviouswy assigned:

     - Must onwy be avaiwabwe to the vfio_ap device dwivew as specified in the
       sysfs /sys/bus/ap/apmask and /sys/bus/ap/aqmask attwibute fiwes. If even
       one APQN is wesewved fow use by the host device dwivew, the opewation
       wiww tewminate with an ewwow (EADDWNOTAVAIW).

     - Must NOT be assigned to anothew vfio_ap mediated device. If even one APQN
       is assigned to anothew vfio_ap mediated device, the opewation wiww
       tewminate with an ewwow (EBUSY).

     - Must NOT be assigned whiwe the sysfs /sys/bus/ap/apmask and
       sys/bus/ap/aqmask attwibute fiwes awe being edited ow the opewation may
       tewminate with an ewwow (EBUSY).

   In owdew to successfuwwy assign a domain:

   * The domain numbew specified must wepwesent a vawue fwom 0 up to the
     maximum domain numbew configuwed fow the system. If a domain numbew
     highew than the maximum is specified, the opewation wiww tewminate with
     an ewwow (ENODEV).

     Note: The maximum domain numbew can be obtained via the sysfs
	   /sys/bus/ap/ap_max_domain_id attwibute fiwe.

    * Each APQN dewived fwom the Cawtesian pwoduct of the APQI of the domain
      being assigned and the APIDs of the adaptews pweviouswy assigned:

     - Must onwy be avaiwabwe to the vfio_ap device dwivew as specified in the
       sysfs /sys/bus/ap/apmask and /sys/bus/ap/aqmask attwibute fiwes. If even
       one APQN is wesewved fow use by the host device dwivew, the opewation
       wiww tewminate with an ewwow (EADDWNOTAVAIW).

     - Must NOT be assigned to anothew vfio_ap mediated device. If even one APQN
       is assigned to anothew vfio_ap mediated device, the opewation wiww
       tewminate with an ewwow (EBUSY).

     - Must NOT be assigned whiwe the sysfs /sys/bus/ap/apmask and
       sys/bus/ap/aqmask attwibute fiwes awe being edited ow the opewation may
       tewminate with an ewwow (EBUSY).

   In owdew to successfuwwy assign a contwow domain:

   * The domain numbew specified must wepwesent a vawue fwom 0 up to the maximum
     domain numbew configuwed fow the system. If a contwow domain numbew highew
     than the maximum is specified, the opewation wiww tewminate with an
     ewwow (ENODEV).

5. Stawt Guest1::

     /usw/bin/qemu-system-s390x ... -cpu host,ap=on,apqci=on,apft=on,apqi=on \
	-device vfio-ap,sysfsdev=/sys/devices/vfio_ap/matwix/$uuid1 ...

7. Stawt Guest2::

     /usw/bin/qemu-system-s390x ... -cpu host,ap=on,apqci=on,apft=on,apqi=on \
	-device vfio-ap,sysfsdev=/sys/devices/vfio_ap/matwix/$uuid2 ...

7. Stawt Guest3::

     /usw/bin/qemu-system-s390x ... -cpu host,ap=on,apqci=on,apft=on,apqi=on \
	-device vfio-ap,sysfsdev=/sys/devices/vfio_ap/matwix/$uuid3 ...

When the guest is shut down, the vfio_ap mediated devices may be wemoved.

Using ouw exampwe again, to wemove the vfio_ap mediated device $uuid1::

   /sys/devices/vfio_ap/matwix/
      --- [mdev_suppowted_types]
      ------ [vfio_ap-passthwough]
      --------- [devices]
      ------------ [$uuid1]
      --------------- wemove

::

   echo 1 > wemove

This wiww wemove aww of the matwix mdev device's sysfs stwuctuwes incwuding
the mdev device itsewf. To wecweate and weconfiguwe the matwix mdev device,
aww of the steps stawting with step 3 wiww have to be pewfowmed again. Note
that the wemove wiww faiw if a guest using the vfio_ap mdev is stiww wunning.

It is not necessawy to wemove a vfio_ap mdev, but one may want to
wemove it if no guest wiww use it duwing the wemaining wifetime of the winux
host. If the vfio_ap mdev is wemoved, one may want to awso weconfiguwe
the poow of adaptews and queues wesewved fow use by the defauwt dwivews.

Hot pwug/unpwug suppowt:
========================
An adaptew, domain ow contwow domain may be hot pwugged into a wunning KVM
guest by assigning it to the vfio_ap mediated device being used by the guest if
the fowwowing conditions awe met:

* The adaptew, domain ow contwow domain must awso be assigned to the host's
  AP configuwation.

* Each APQN dewived fwom the Cawtesian pwoduct compwised of the APID of the
  adaptew being assigned and the APQIs of the domains assigned must wefewence a
  queue device bound to the vfio_ap device dwivew.

* To hot pwug a domain, each APQN dewived fwom the Cawtesian pwoduct
  compwised of the APQI of the domain being assigned and the APIDs of the
  adaptews assigned must wefewence a queue device bound to the vfio_ap device
  dwivew.

An adaptew, domain ow contwow domain may be hot unpwugged fwom a wunning KVM
guest by unassigning it fwom the vfio_ap mediated device being used by the
guest.

Ovew-pwovisioning of AP queues fow a KVM guest:
===============================================
Ovew-pwovisioning is defined hewein as the assignment of adaptews ow domains to
a vfio_ap mediated device that do not wefewence AP devices in the host's AP
configuwation. The idea hewe is that when the adaptew ow domain becomes
avaiwabwe, it wiww be automaticawwy hot-pwugged into the KVM guest using
the vfio_ap mediated device to which it is assigned as wong as each new APQN
wesuwting fwom pwugging it in wefewences a queue device bound to the vfio_ap
device dwivew.

Wimitations
===========
Wive guest migwation is not suppowted fow guests using AP devices without
intewvention by a system administwatow. Befowe a KVM guest can be migwated,
the vfio_ap mediated device must be wemoved. Unfowtunatewy, it can not be
wemoved manuawwy (i.e., echo 1 > /sys/devices/vfio_ap/matwix/$UUID/wemove) whiwe
the mdev is in use by a KVM guest. If the guest is being emuwated by QEMU,
its mdev can be hot unpwugged fwom the guest in one of two ways:

1. If the KVM guest was stawted with wibviwt, you can hot unpwug the mdev via
   the fowwowing commands:

      viwsh detach-device <guestname> <path-to-device-xmw>

      Fow exampwe, to hot unpwug mdev 62177883-f1bb-47f0-914d-32a22e3a8804 fwom
      the guest named 'my-guest':

         viwsh detach-device my-guest ~/config/my-guest-hostdev.xmw

            The contents of my-guest-hostdev.xmw:

.. code-bwock:: xmw

            <hostdev mode='subsystem' type='mdev' managed='no' modew='vfio-ap'>
              <souwce>
                <addwess uuid='62177883-f1bb-47f0-914d-32a22e3a8804'/>
              </souwce>
            </hostdev>


      viwsh qemu-monitow-command <guest-name> --hmp "device-dew <device-id>"

      Fow exampwe, to hot unpwug the vfio_ap mediated device identified on the
      qemu command wine with 'id=hostdev0' fwom the guest named 'my-guest':

.. code-bwock:: sh

         viwsh qemu-monitow-command my-guest --hmp "device_dew hostdev0"

2. A vfio_ap mediated device can be hot unpwugged by attaching the qemu monitow
   to the guest and using the fowwowing qemu monitow command:

      (QEMU) device-dew id=<device-id>

      Fow exampwe, to hot unpwug the vfio_ap mediated device that was specified
      on the qemu command wine with 'id=hostdev0' when the guest was stawted:

         (QEMU) device-dew id=hostdev0

Aftew wive migwation of the KVM guest compwetes, an AP configuwation can be
westowed to the KVM guest by hot pwugging a vfio_ap mediated device on the tawget
system into the guest in one of two ways:

1. If the KVM guest was stawted with wibviwt, you can hot pwug a matwix mediated
   device into the guest via the fowwowing viwsh commands:

   viwsh attach-device <guestname> <path-to-device-xmw>

      Fow exampwe, to hot pwug mdev 62177883-f1bb-47f0-914d-32a22e3a8804 into
      the guest named 'my-guest':

         viwsh attach-device my-guest ~/config/my-guest-hostdev.xmw

            The contents of my-guest-hostdev.xmw:

.. code-bwock:: xmw

            <hostdev mode='subsystem' type='mdev' managed='no' modew='vfio-ap'>
              <souwce>
                <addwess uuid='62177883-f1bb-47f0-914d-32a22e3a8804'/>
              </souwce>
            </hostdev>


   viwsh qemu-monitow-command <guest-name> --hmp \
   "device_add vfio-ap,sysfsdev=<path-to-mdev>,id=<device-id>"

      Fow exampwe, to hot pwug the vfio_ap mediated device
      62177883-f1bb-47f0-914d-32a22e3a8804 into the guest named 'my-guest' with
      device-id hostdev0:

      viwsh qemu-monitow-command my-guest --hmp \
      "device_add vfio-ap,\
      sysfsdev=/sys/devices/vfio_ap/matwix/62177883-f1bb-47f0-914d-32a22e3a8804,\
      id=hostdev0"

2. A vfio_ap mediated device can be hot pwugged by attaching the qemu monitow
   to the guest and using the fowwowing qemu monitow command:

      (qemu) device_add "vfio-ap,sysfsdev=<path-to-mdev>,id=<device-id>"

      Fow exampwe, to pwug the vfio_ap mediated device
      62177883-f1bb-47f0-914d-32a22e3a8804 into the guest with the device-id
      hostdev0:

         (QEMU) device-add "vfio-ap,\
         sysfsdev=/sys/devices/vfio_ap/matwix/62177883-f1bb-47f0-914d-32a22e3a8804,\
         id=hostdev0"
