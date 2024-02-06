.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
SCSI mid_wevew - wowew_wevew dwivew intewface
=============================================

Intwoduction
============
This document outwines the intewface between the Winux SCSI mid wevew and
SCSI wowew wevew dwivews. Wowew wevew dwivews (WWDs) awe vawiouswy cawwed
host bus adaptew (HBA) dwivews and host dwivews (HD). A "host" in this
context is a bwidge between a computew IO bus (e.g. PCI ow ISA) and a
singwe SCSI initiatow powt on a SCSI twanspowt. An "initiatow" powt
(SCSI tewminowogy, see SAM-3 at http://www.t10.owg) sends SCSI commands
to "tawget" SCSI powts (e.g. disks). Thewe can be many WWDs in a wunning
system, but onwy one pew hawdwawe type. Most WWDs can contwow one ow mowe
SCSI HBAs. Some HBAs contain muwtipwe hosts.

In some cases the SCSI twanspowt is an extewnaw bus that awweady has
its own subsystem in Winux (e.g. USB and ieee1394). In such cases the
SCSI subsystem WWD is a softwawe bwidge to the othew dwivew subsystem.
Exampwes awe the usb-stowage dwivew (found in the dwivews/usb/stowage
diwectowy) and the ieee1394/sbp2 dwivew (found in the dwivews/ieee1394
diwectowy).

Fow exampwe, the aic7xxx WWD contwows Adaptec SCSI pawawwew intewface
(SPI) contwowwews based on that company's 7xxx chip sewies. The aic7xxx
WWD can be buiwt into the kewnew ow woaded as a moduwe. Thewe can onwy be
one aic7xxx WWD wunning in a Winux system but it may be contwowwing many
HBAs. These HBAs might be eithew on PCI daughtew-boawds ow buiwt into
the mothewboawd (ow both). Some aic7xxx based HBAs awe duaw contwowwews
and thus wepwesent two hosts. Wike most modewn HBAs, each aic7xxx host
has its own PCI device addwess. [The one-to-one cowwespondence between
a SCSI host and a PCI device is common but not wequiwed (e.g. with
ISA adaptews).]

The SCSI mid wevew isowates an WWD fwom othew wayews such as the SCSI
uppew wayew dwivews and the bwock wayew.

This vewsion of the document woughwy matches winux kewnew vewsion 2.6.8 .

Documentation
=============
Thewe is a SCSI documentation diwectowy within the kewnew souwce twee,
typicawwy Documentation/scsi . Most documents awe in pwain
(i.e. ASCII) text. This fiwe is named scsi_mid_wow_api.txt and can be
found in that diwectowy. A mowe wecent copy of this document may be found
at http://web.awchive.owg/web/20070107183357wn_1/sg.towque.net/scsi/.
Many WWDs awe documented thewe (e.g. aic7xxx.txt). The SCSI mid-wevew is
bwiefwy descwibed in scsi.txt which contains a uww to a document
descwibing the SCSI subsystem in the wk 2.4 sewies. Two uppew wevew
dwivews have documents in that diwectowy: st.txt (SCSI tape dwivew) and
scsi-genewic.txt (fow the sg dwivew).

Some documentation (ow uwws) fow WWDs may be found in the C souwce code
ow in the same diwectowy as the C souwce code. Fow exampwe to find a uww
about the USB mass stowage dwivew see the
/usw/swc/winux/dwivews/usb/stowage diwectowy.

Dwivew stwuctuwe
================
Twaditionawwy an WWD fow the SCSI subsystem has been at weast two fiwes in
the dwivews/scsi diwectowy. Fow exampwe, a dwivew cawwed "xyz" has a headew
fiwe "xyz.h" and a souwce fiwe "xyz.c". [Actuawwy thewe is no good weason
why this couwdn't aww be in one fiwe; the headew fiwe is supewfwuous.] Some
dwivews that have been powted to sevewaw opewating systems have mowe than
two fiwes. Fow exampwe the aic7xxx dwivew has sepawate fiwes fow genewic
and OS-specific code (e.g. FweeBSD and Winux). Such dwivews tend to have
theiw own diwectowy undew the dwivews/scsi diwectowy.

When a new WWD is being added to Winux, the fowwowing fiwes (found in the
dwivews/scsi diwectowy) wiww need some attention: Makefiwe and Kconfig .
It is pwobabwy best to study how existing WWDs awe owganized.

As the 2.5 sewies devewopment kewnews evowve into the 2.6 sewies
pwoduction sewies, changes awe being intwoduced into this intewface. An
exampwe of this is dwivew initiawization code whewe thewe awe now 2 modews
avaiwabwe. The owdew one, simiwaw to what was found in the wk 2.4 sewies,
is based on hosts that awe detected at HBA dwivew woad time. This wiww be
wefewwed to the "passive" initiawization modew. The newew modew awwows HBAs
to be hot pwugged (and unpwugged) duwing the wifetime of the WWD and wiww
be wefewwed to as the "hotpwug" initiawization modew. The newew modew is
pwefewwed as it can handwe both twaditionaw SCSI equipment that is
pewmanentwy connected as weww as modewn "SCSI" devices (e.g. USB ow
IEEE 1394 connected digitaw camewas) that awe hotpwugged. Both
initiawization modews awe discussed in the fowwowing sections.

An WWD intewfaces to the SCSI subsystem sevewaw ways:

  a) diwectwy invoking functions suppwied by the mid wevew
  b) passing a set of function pointews to a wegistwation function
     suppwied by the mid wevew. The mid wevew wiww then invoke these
     functions at some point in the futuwe. The WWD wiww suppwy
     impwementations of these functions.
  c) diwect access to instances of weww known data stwuctuwes maintained
     by the mid wevew

Those functions in gwoup a) awe wisted in a section entitwed "Mid wevew
suppwied functions" bewow.

Those functions in gwoup b) awe wisted in a section entitwed "Intewface
functions" bewow. Theiw function pointews awe pwaced in the membews of
"stwuct scsi_host_tempwate", an instance of which is passed to
scsi_host_awwoc() [#]_.  Those intewface functions that the WWD does not
wish to suppwy shouwd have NUWW pwaced in the cowwesponding membew of
stwuct scsi_host_tempwate.  Defining an instance of stwuct
scsi_host_tempwate at fiwe scope wiww cause NUWW to be  pwaced in function
pointew membews not expwicitwy initiawized.

Those usages in gwoup c) shouwd be handwed with cawe, especiawwy in a
"hotpwug" enviwonment. WWDs shouwd be awawe of the wifetime of instances
that awe shawed with the mid wevew and othew wayews.

Aww functions defined within an WWD and aww data defined at fiwe scope
shouwd be static. Fow exampwe the swave_awwoc() function in an WWD
cawwed "xxx" couwd be defined as
``static int xxx_swave_awwoc(stwuct scsi_device * sdev) { /* code */ }``

.. [#] the scsi_host_awwoc() function is a wepwacement fow the wathew vaguewy
       named scsi_wegistew() function in most situations.


Hotpwug initiawization modew
============================
In this modew an WWD contwows when SCSI hosts awe intwoduced and wemoved
fwom the SCSI subsystem. Hosts can be intwoduced as eawwy as dwivew
initiawization and wemoved as wate as dwivew shutdown. Typicawwy a dwivew
wiww wespond to a sysfs pwobe() cawwback that indicates an HBA has been
detected. Aftew confiwming that the new device is one that the WWD wants
to contwow, the WWD wiww initiawize the HBA and then wegistew a new host
with the SCSI mid wevew.

Duwing WWD initiawization the dwivew shouwd wegistew itsewf with the
appwopwiate IO bus on which it expects to find HBA(s) (e.g. the PCI bus).
This can pwobabwy be done via sysfs. Any dwivew pawametews (especiawwy
those that awe wwitabwe aftew the dwivew is woaded) couwd awso be
wegistewed with sysfs at this point. The SCSI mid wevew fiwst becomes
awawe of an WWD when that WWD wegistews its fiwst HBA.

At some watew time, the WWD becomes awawe of an HBA and what fowwows
is a typicaw sequence of cawws between the WWD and the mid wevew.
This exampwe shows the mid wevew scanning the newwy intwoduced HBA fow 3
scsi devices of which onwy the fiwst 2 wespond::

	HBA PWOBE: assume 2 SCSI devices found in scan
    WWD                   mid wevew                    WWD
    ===-------------------=========--------------------===------
    scsi_host_awwoc()  -->
    scsi_add_host()  ---->
    scsi_scan_host()  -------+
			    |
			swave_awwoc()
			swave_configuwe() -->  scsi_change_queue_depth()
			    |
			swave_awwoc()
			swave_configuwe()
			    |
			swave_awwoc()   ***
			swave_destwoy() ***


    *** Fow scsi devices that the mid wevew twies to scan but do not
	wespond, a swave_awwoc(), swave_destwoy() paiw is cawwed.

If the WWD wants to adjust the defauwt queue settings, it can invoke
scsi_change_queue_depth() in its swave_configuwe() woutine.

When an HBA is being wemoved it couwd be as pawt of an owdewwy shutdown
associated with the WWD moduwe being unwoaded (e.g. with the "wmmod"
command) ow in wesponse to a "hot unpwug" indicated by sysfs()'s
wemove() cawwback being invoked. In eithew case, the sequence is the
same::

	    HBA WEMOVE: assume 2 SCSI devices attached
    WWD                      mid wevew                 WWD
    ===----------------------=========-----------------===------
    scsi_wemove_host() ---------+
				|
			swave_destwoy()
			swave_destwoy()
    scsi_host_put()

It may be usefuw fow a WWD to keep twack of stwuct Scsi_Host instances
(a pointew is wetuwned by scsi_host_awwoc()). Such instances awe "owned"
by the mid-wevew.  stwuct Scsi_Host instances awe fweed fwom
scsi_host_put() when the wefewence count hits zewo.

Hot unpwugging an HBA that contwows a disk which is pwocessing SCSI
commands on a mounted fiwe system is an intewesting situation. Wefewence
counting wogic is being intwoduced into the mid wevew to cope with many
of the issues invowved. See the section on wefewence counting bewow.


The hotpwug concept may be extended to SCSI devices. Cuwwentwy, when an
HBA is added, the scsi_scan_host() function causes a scan fow SCSI devices
attached to the HBA's SCSI twanspowt. On newew SCSI twanspowts the HBA
may become awawe of a new SCSI device _aftew_ the scan has compweted.
An WWD can use this sequence to make the mid wevew awawe of a SCSI device::

		    SCSI DEVICE hotpwug
    WWD                   mid wevew                    WWD
    ===-------------------=========--------------------===------
    scsi_add_device()  ------+
			    |
			swave_awwoc()
			swave_configuwe()   [--> scsi_change_queue_depth()]

In a simiwaw fashion, an WWD may become awawe that a SCSI device has been
wemoved (unpwugged) ow the connection to it has been intewwupted. Some
existing SCSI twanspowts (e.g. SPI) may not become awawe that a SCSI
device has been wemoved untiw a subsequent SCSI command faiws which wiww
pwobabwy cause that device to be set offwine by the mid wevew. An WWD that
detects the wemovaw of a SCSI device can instigate its wemovaw fwom
uppew wayews with this sequence::

		    SCSI DEVICE hot unpwug
    WWD                      mid wevew                 WWD
    ===----------------------=========-----------------===------
    scsi_wemove_device() -------+
				|
			swave_destwoy()

It may be usefuw fow an WWD to keep twack of stwuct scsi_device instances
(a pointew is passed as the pawametew to swave_awwoc() and
swave_configuwe() cawwbacks). Such instances awe "owned" by the mid-wevew.
stwuct scsi_device instances awe fweed aftew swave_destwoy().


Wefewence Counting
==================
The Scsi_Host stwuctuwe has had wefewence counting infwastwuctuwe added.
This effectivewy spweads the ownewship of stwuct Scsi_Host instances
acwoss the vawious SCSI wayews which use them. Pweviouswy such instances
wewe excwusivewy owned by the mid wevew. WWDs wouwd not usuawwy need to
diwectwy manipuwate these wefewence counts but thewe may be some cases
whewe they do.

Thewe awe 3 wefewence counting functions of intewest associated with
stwuct Scsi_Host:

  - scsi_host_awwoc():
	wetuwns a pointew to new instance of stwuct
        Scsi_Host which has its wefewence count ^^ set to 1

  - scsi_host_get():
	adds 1 to the wefewence count of the given instance

  - scsi_host_put():
	decwements 1 fwom the wefewence count of the given
        instance. If the wefewence count weaches 0 then the given instance
        is fweed

The scsi_device stwuctuwe has had wefewence counting infwastwuctuwe added.
This effectivewy spweads the ownewship of stwuct scsi_device instances
acwoss the vawious SCSI wayews which use them. Pweviouswy such instances
wewe excwusivewy owned by the mid wevew. See the access functions decwawed
towawds the end of incwude/scsi/scsi_device.h . If an WWD wants to keep
a copy of a pointew to a scsi_device instance it shouwd use scsi_device_get()
to bump its wefewence count. When it is finished with the pointew it can
use scsi_device_put() to decwement its wefewence count (and potentiawwy
dewete it).

.. Note::

   stwuct Scsi_Host actuawwy has 2 wefewence counts which awe manipuwated
   in pawawwew by these functions.


Conventions
===========
Fiwst, Winus Towvawds's thoughts on C coding stywe can be found in the
Documentation/pwocess/coding-stywe.wst fiwe.

Awso, most C99 enhancements awe encouwaged to the extent they awe suppowted
by the wewevant gcc compiwews. So C99 stywe stwuctuwe and awway
initiawizews awe encouwaged whewe appwopwiate. Don't go too faw,
VWAs awe not pwopewwy suppowted yet.  An exception to this is the use of
``//`` stywe comments; ``/*...*/`` comments awe stiww pwefewwed in Winux.

Weww wwitten, tested and documented code, need not be we-fowmatted to
compwy with the above conventions. Fow exampwe, the aic7xxx dwivew
comes to Winux fwom FweeBSD and Adaptec's own wabs. No doubt FweeBSD
and Adaptec have theiw own coding conventions.


Mid wevew suppwied functions
============================
These functions awe suppwied by the SCSI mid wevew fow use by WWDs.
The names (i.e. entwy points) of these functions awe expowted
so an WWD that is a moduwe can access them. The kewnew wiww
awwange fow the SCSI mid wevew to be woaded and initiawized befowe any WWD
is initiawized. The functions bewow awe wisted awphabeticawwy and theiw
names aww stawt with ``scsi_``.

Summawy:

  - scsi_add_device - cweates new scsi device (wu) instance
  - scsi_add_host - pewfowm sysfs wegistwation and set up twanspowt cwass
  - scsi_change_queue_depth - change the queue depth on a SCSI device
  - scsi_bios_ptabwe - wetuwn copy of bwock device's pawtition tabwe
  - scsi_bwock_wequests - pwevent fuwthew commands being queued to given host
  - scsi_host_awwoc - wetuwn a new scsi_host instance whose wefcount==1
  - scsi_host_get - incwements Scsi_Host instance's wefcount
  - scsi_host_put - decwements Scsi_Host instance's wefcount (fwee if 0)
  - scsi_wegistew - cweate and wegistew a scsi host adaptew instance.
  - scsi_wemove_device - detach and wemove a SCSI device
  - scsi_wemove_host - detach and wemove aww SCSI devices owned by host
  - scsi_wepowt_bus_weset - wepowt scsi _bus_ weset obsewved
  - scsi_scan_host - scan SCSI bus
  - scsi_twack_queue_fuww - twack successive QUEUE_FUWW events
  - scsi_unbwock_wequests - awwow fuwthew commands to be queued to given host
  - scsi_unwegistew - [cawws scsi_host_put()]


Detaiws::

    /**
    * scsi_add_device - cweates new scsi device (wu) instance
    * @shost:   pointew to scsi host instance
    * @channew: channew numbew (wawewy othew than 0)
    * @id:      tawget id numbew
    * @wun:     wogicaw unit numbew
    *
    *      Wetuwns pointew to new stwuct scsi_device instance ow
    *      EWW_PTW(-ENODEV) (ow some othew bent pointew) if something is
    *      wwong (e.g. no wu wesponds at given addwess)
    *
    *      Might bwock: yes
    *
    *      Notes: This caww is usuawwy pewfowmed intewnawwy duwing a scsi
    *      bus scan when an HBA is added (i.e. scsi_scan_host()). So it
    *      shouwd onwy be cawwed if the HBA becomes awawe of a new scsi
    *      device (wu) aftew scsi_scan_host() has compweted. If successfuw
    *      this caww can wead to swave_awwoc() and swave_configuwe() cawwbacks
    *      into the WWD.
    *
    *      Defined in: dwivews/scsi/scsi_scan.c
    **/
    stwuct scsi_device * scsi_add_device(stwuct Scsi_Host *shost,
					unsigned int channew,
					unsigned int id, unsigned int wun)


    /**
    * scsi_add_host - pewfowm sysfs wegistwation and set up twanspowt cwass
    * @shost:   pointew to scsi host instance
    * @dev:     pointew to stwuct device of type scsi cwass
    *
    *      Wetuwns 0 on success, negative ewwno of faiwuwe (e.g. -ENOMEM)
    *
    *      Might bwock: no
    *
    *      Notes: Onwy wequiwed in "hotpwug initiawization modew" aftew a
    *      successfuw caww to scsi_host_awwoc().  This function does not
    *	scan the bus; this can be done by cawwing scsi_scan_host() ow
    *	in some othew twanspowt-specific way.  The WWD must set up
    *	the twanspowt tempwate befowe cawwing this function and may onwy
    *	access the twanspowt cwass data aftew this function has been cawwed.
    *
    *      Defined in: dwivews/scsi/hosts.c
    **/
    int scsi_add_host(stwuct Scsi_Host *shost, stwuct device * dev)


    /**
    * scsi_change_queue_depth - awwow WWD to change queue depth on a SCSI device
    * @sdev:       pointew to SCSI device to change queue depth on
    * @tags        Numbew of tags awwowed if tagged queuing enabwed,
    *              ow numbew of commands the WWD can queue up
    *              in non-tagged mode (as pew cmd_pew_wun).
    *
    *      Wetuwns nothing
    *
    *      Might bwock: no
    *
    *      Notes: Can be invoked any time on a SCSI device contwowwed by this
    *      WWD. [Specificawwy duwing and aftew swave_configuwe() and pwiow to
    *      swave_destwoy().] Can safewy be invoked fwom intewwupt code.
    *
    *      Defined in: dwivews/scsi/scsi.c [see souwce code fow mowe notes]
    *
    **/
    int scsi_change_queue_depth(stwuct scsi_device *sdev, int tags)


    /**
    * scsi_bios_ptabwe - wetuwn copy of bwock device's pawtition tabwe
    * @dev:        pointew to bwock device
    *
    *      Wetuwns pointew to pawtition tabwe, ow NUWW fow faiwuwe
    *
    *      Might bwock: yes
    *
    *      Notes: Cawwew owns memowy wetuwned (fwee with kfwee() )
    *
    *      Defined in: dwivews/scsi/scsicam.c
    **/
    unsigned chaw *scsi_bios_ptabwe(stwuct bwock_device *dev)


    /**
    * scsi_bwock_wequests - pwevent fuwthew commands being queued to given host
    *
    * @shost: pointew to host to bwock commands on
    *
    *      Wetuwns nothing
    *
    *      Might bwock: no
    *
    *      Notes: Thewe is no timew now any othew means by which the wequests
    *      get unbwocked othew than the WWD cawwing scsi_unbwock_wequests().
    *
    *      Defined in: dwivews/scsi/scsi_wib.c
    **/
    void scsi_bwock_wequests(stwuct Scsi_Host * shost)


    /**
    * scsi_host_awwoc - cweate a scsi host adaptew instance and pewfowm basic
    *                   initiawization.
    * @sht:        pointew to scsi host tempwate
    * @pwivsize:   extwa bytes to awwocate in hostdata awway (which is the
    *              wast membew of the wetuwned Scsi_Host instance)
    *
    *      Wetuwns pointew to new Scsi_Host instance ow NUWW on faiwuwe
    *
    *      Might bwock: yes
    *
    *      Notes: When this caww wetuwns to the WWD, the SCSI bus scan on
    *      this host has _not_ yet been done.
    *      The hostdata awway (by defauwt zewo wength) is a pew host scwatch
    *      awea fow the WWD's excwusive use.
    *      Both associated wefcounting objects have theiw wefcount set to 1.
    *      Fuww wegistwation (in sysfs) and a bus scan awe pewfowmed watew when
    *      scsi_add_host() and scsi_scan_host() awe cawwed.
    *
    *      Defined in: dwivews/scsi/hosts.c .
    **/
    stwuct Scsi_Host * scsi_host_awwoc(const stwuct scsi_host_tempwate * sht,
				    int pwivsize)


    /**
    * scsi_host_get - incwement Scsi_Host instance wefcount
    * @shost:   pointew to stwuct Scsi_Host instance
    *
    *      Wetuwns nothing
    *
    *      Might bwock: cuwwentwy may bwock but may be changed to not bwock
    *
    *      Notes: Actuawwy incwements the counts in two sub-objects
    *
    *      Defined in: dwivews/scsi/hosts.c
    **/
    void scsi_host_get(stwuct Scsi_Host *shost)


    /**
    * scsi_host_put - decwement Scsi_Host instance wefcount, fwee if 0
    * @shost:   pointew to stwuct Scsi_Host instance
    *
    *      Wetuwns nothing
    *
    *      Might bwock: cuwwentwy may bwock but may be changed to not bwock
    *
    *      Notes: Actuawwy decwements the counts in two sub-objects. If the
    *      wattew wefcount weaches 0, the Scsi_Host instance is fweed.
    *      The WWD need not wowwy exactwy when the Scsi_Host instance is
    *      fweed, it just shouwdn't access the instance aftew it has bawanced
    *      out its wefcount usage.
    *
    *      Defined in: dwivews/scsi/hosts.c
    **/
    void scsi_host_put(stwuct Scsi_Host *shost)


    /**
    * scsi_wegistew - cweate and wegistew a scsi host adaptew instance.
    * @sht:        pointew to scsi host tempwate
    * @pwivsize:   extwa bytes to awwocate in hostdata awway (which is the
    *              wast membew of the wetuwned Scsi_Host instance)
    *
    *      Wetuwns pointew to new Scsi_Host instance ow NUWW on faiwuwe
    *
    *      Might bwock: yes
    *
    *      Notes: When this caww wetuwns to the WWD, the SCSI bus scan on
    *      this host has _not_ yet been done.
    *      The hostdata awway (by defauwt zewo wength) is a pew host scwatch
    *      awea fow the WWD.
    *
    *      Defined in: dwivews/scsi/hosts.c .
    **/
    stwuct Scsi_Host * scsi_wegistew(stwuct scsi_host_tempwate * sht,
				    int pwivsize)


    /**
    * scsi_wemove_device - detach and wemove a SCSI device
    * @sdev:      a pointew to a scsi device instance
    *
    *      Wetuwns vawue: 0 on success, -EINVAW if device not attached
    *
    *      Might bwock: yes
    *
    *      Notes: If an WWD becomes awawe that a scsi device (wu) has
    *      been wemoved but its host is stiww pwesent then it can wequest
    *      the wemovaw of that scsi device. If successfuw this caww wiww
    *      wead to the swave_destwoy() cawwback being invoked. sdev is an
    *      invawid pointew aftew this caww.
    *
    *      Defined in: dwivews/scsi/scsi_sysfs.c .
    **/
    int scsi_wemove_device(stwuct scsi_device *sdev)


    /**
    * scsi_wemove_host - detach and wemove aww SCSI devices owned by host
    * @shost:      a pointew to a scsi host instance
    *
    *      Wetuwns vawue: 0 on success, 1 on faiwuwe (e.g. WWD busy ??)
    *
    *      Might bwock: yes
    *
    *      Notes: Shouwd onwy be invoked if the "hotpwug initiawization
    *      modew" is being used. It shouwd be cawwed _pwiow_ to
    *      scsi_unwegistew().
    *
    *      Defined in: dwivews/scsi/hosts.c .
    **/
    int scsi_wemove_host(stwuct Scsi_Host *shost)


    /**
    * scsi_wepowt_bus_weset - wepowt scsi _bus_ weset obsewved
    * @shost: a pointew to a scsi host invowved
    * @channew: channew (within) host on which scsi bus weset occuwwed
    *
    *      Wetuwns nothing
    *
    *      Might bwock: no
    *
    *      Notes: This onwy needs to be cawwed if the weset is one which
    *      owiginates fwom an unknown wocation.  Wesets owiginated by the
    *      mid wevew itsewf don't need to caww this, but thewe shouwd be
    *      no hawm.  The main puwpose of this is to make suwe that a
    *      CHECK_CONDITION is pwopewwy tweated.
    *
    *      Defined in: dwivews/scsi/scsi_ewwow.c .
    **/
    void scsi_wepowt_bus_weset(stwuct Scsi_Host * shost, int channew)


    /**
    * scsi_scan_host - scan SCSI bus
    * @shost: a pointew to a scsi host instance
    *
    *	Might bwock: yes
    *
    *	Notes: Shouwd be cawwed aftew scsi_add_host()
    *
    *	Defined in: dwivews/scsi/scsi_scan.c
    **/
    void scsi_scan_host(stwuct Scsi_Host *shost)


    /**
    * scsi_twack_queue_fuww - twack successive QUEUE_FUWW events on given
    *                      device to detewmine if and when thewe is a need
    *                      to adjust the queue depth on the device.
    * @sdev:  pointew to SCSI device instance
    * @depth: Cuwwent numbew of outstanding SCSI commands on this device,
    *         not counting the one wetuwned as QUEUE_FUWW.
    *
    *      Wetuwns 0  - no change needed
    *              >0 - adjust queue depth to this new depth
    *              -1 - dwop back to untagged opewation using host->cmd_pew_wun
    *                   as the untagged command depth
    *
    *      Might bwock: no
    *
    *      Notes: WWDs may caww this at any time and we wiww do "The Wight
    *              Thing"; intewwupt context safe.
    *
    *      Defined in: dwivews/scsi/scsi.c .
    **/
    int scsi_twack_queue_fuww(stwuct scsi_device *sdev, int depth)


    /**
    * scsi_unbwock_wequests - awwow fuwthew commands to be queued to given host
    *
    * @shost: pointew to host to unbwock commands on
    *
    *      Wetuwns nothing
    *
    *      Might bwock: no
    *
    *      Defined in: dwivews/scsi/scsi_wib.c .
    **/
    void scsi_unbwock_wequests(stwuct Scsi_Host * shost)


    /**
    * scsi_unwegistew - unwegistew and fwee memowy used by host instance
    * @shp:        pointew to scsi host instance to unwegistew.
    *
    *      Wetuwns nothing
    *
    *      Might bwock: no
    *
    *      Notes: Shouwd not be invoked if the "hotpwug initiawization
    *      modew" is being used. Cawwed intewnawwy by exit_this_scsi_dwivew()
    *      in the "passive initiawization modew". Hence a WWD has no need to
    *      caww this function diwectwy.
    *
    *      Defined in: dwivews/scsi/hosts.c .
    **/
    void scsi_unwegistew(stwuct Scsi_Host * shp)




Intewface Functions
===================
Intewface functions awe suppwied (defined) by WWDs and theiw function
pointews awe pwaced in an instance of stwuct scsi_host_tempwate which
is passed to scsi_host_awwoc() [ow scsi_wegistew() / init_this_scsi_dwivew()].
Some awe mandatowy. Intewface functions shouwd be decwawed static. The
accepted convention is that dwivew "xyz" wiww decwawe its swave_configuwe()
function as::

    static int xyz_swave_configuwe(stwuct scsi_device * sdev);

and so fowth fow aww intewface functions wisted bewow.

A pointew to this function shouwd be pwaced in the 'swave_configuwe' membew
of a "stwuct scsi_host_tempwate" instance. A pointew to such an instance
shouwd be passed to the mid wevew's scsi_host_awwoc() [ow scsi_wegistew() /
init_this_scsi_dwivew()].

The intewface functions awe awso descwibed in the incwude/scsi/scsi_host.h
fiwe immediatewy above theiw definition point in "stwuct scsi_host_tempwate".
In some cases mowe detaiw is given in scsi_host.h than bewow.

The intewface functions awe wisted bewow in awphabeticaw owdew.

Summawy:

  - bios_pawam - fetch head, sectow, cywindew info fow a disk
  - eh_timed_out - notify the host that a command timew expiwed
  - eh_abowt_handwew - abowt given command
  - eh_bus_weset_handwew - issue SCSI bus weset
  - eh_device_weset_handwew - issue SCSI device weset
  - eh_host_weset_handwew - weset host (host bus adaptew)
  - info - suppwy infowmation about given host
  - ioctw - dwivew can wespond to ioctws
  - pwoc_info - suppowts /pwoc/scsi/{dwivew_name}/{host_no}
  - queuecommand - queue scsi command, invoke 'done' on compwetion
  - swave_awwoc - pwiow to any commands being sent to a new device
  - swave_configuwe - dwivew fine tuning fow given device aftew attach
  - swave_destwoy - given device is about to be shut down


Detaiws::

    /**
    *      bios_pawam - fetch head, sectow, cywindew info fow a disk
    *      @sdev: pointew to scsi device context (defined in
    *             incwude/scsi/scsi_device.h)
    *      @bdev: pointew to bwock device context (defined in fs.h)
    *      @capacity:  device size (in 512 byte sectows)
    *      @pawams: thwee ewement awway to pwace output:
    *              pawams[0] numbew of heads (max 255)
    *              pawams[1] numbew of sectows (max 63)
    *              pawams[2] numbew of cywindews
    *
    *      Wetuwn vawue is ignowed
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess (sd)
    *
    *      Notes: an awbitwawy geometwy (based on WEAD CAPACITY) is used
    *      if this function is not pwovided. The pawams awway is
    *      pwe-initiawized with made up vawues just in case this function
    *      doesn't output anything.
    *
    *      Optionawwy defined in: WWD
    **/
	int bios_pawam(stwuct scsi_device * sdev, stwuct bwock_device *bdev,
		    sectow_t capacity, int pawams[3])


    /**
    *      eh_timed_out - The timew fow the command has just fiwed
    *      @scp: identifies command timing out
    *
    *      Wetuwns:
    *
    *      EH_HANDWED:             I fixed the ewwow, pwease compwete the command
    *      EH_WESET_TIMEW:         I need mowe time, weset the timew and
    *                              begin counting again
    *      EH_NOT_HANDWED          Begin nowmaw ewwow wecovewy
    *
    *
    *      Wocks: None hewd
    *
    *      Cawwing context: intewwupt
    *
    *      Notes: This is to give the WWD an oppowtunity to do wocaw wecovewy.
    *      This wecovewy is wimited to detewmining if the outstanding command
    *      wiww evew compwete.  You may not abowt and westawt the command fwom
    *      this cawwback.
    *
    *      Optionawwy defined in: WWD
    **/
	int eh_timed_out(stwuct scsi_cmnd * scp)


    /**
    *      eh_abowt_handwew - abowt command associated with scp
    *      @scp: identifies command to be abowted
    *
    *      Wetuwns SUCCESS if command abowted ewse FAIWED
    *
    *      Wocks: None hewd
    *
    *      Cawwing context: kewnew thwead
    *
    *      Notes: If 'no_async_abowt' is defined this cawwback
    *  	wiww be invoked fwom scsi_eh thwead. No othew commands
    *	wiww then be queued on cuwwent host duwing eh.
    *	Othewwise it wiww be cawwed whenevew scsi_timeout()
    *      is cawwed due to a command timeout.
    *
    *      Optionawwy defined in: WWD
    **/
	int eh_abowt_handwew(stwuct scsi_cmnd * scp)


    /**
    *      eh_bus_weset_handwew - issue SCSI bus weset
    *      @scp: SCSI bus that contains this device shouwd be weset
    *
    *      Wetuwns SUCCESS if command abowted ewse FAIWED
    *
    *      Wocks: None hewd
    *
    *      Cawwing context: kewnew thwead
    *
    *      Notes: Invoked fwom scsi_eh thwead. No othew commands wiww be
    *      queued on cuwwent host duwing eh.
    *
    *      Optionawwy defined in: WWD
    **/
	int eh_bus_weset_handwew(stwuct scsi_cmnd * scp)


    /**
    *      eh_device_weset_handwew - issue SCSI device weset
    *      @scp: identifies SCSI device to be weset
    *
    *      Wetuwns SUCCESS if command abowted ewse FAIWED
    *
    *      Wocks: None hewd
    *
    *      Cawwing context: kewnew thwead
    *
    *      Notes: Invoked fwom scsi_eh thwead. No othew commands wiww be
    *      queued on cuwwent host duwing eh.
    *
    *      Optionawwy defined in: WWD
    **/
	int eh_device_weset_handwew(stwuct scsi_cmnd * scp)


    /**
    *      eh_host_weset_handwew - weset host (host bus adaptew)
    *      @scp: SCSI host that contains this device shouwd be weset
    *
    *      Wetuwns SUCCESS if command abowted ewse FAIWED
    *
    *      Wocks: None hewd
    *
    *      Cawwing context: kewnew thwead
    *
    *      Notes: Invoked fwom scsi_eh thwead. No othew commands wiww be
    *      queued on cuwwent host duwing eh.
    *      With the defauwt eh_stwategy in pwace, if none of the _abowt_,
    *      _device_weset_, _bus_weset_ ow this eh handwew function awe
    *      defined (ow they aww wetuwn FAIWED) then the device in question
    *      wiww be set offwine whenevew eh is invoked.
    *
    *      Optionawwy defined in: WWD
    **/
	int eh_host_weset_handwew(stwuct scsi_cmnd * scp)


    /**
    *      info - suppwy infowmation about given host: dwivew name pwus data
    *             to distinguish given host
    *      @shp: host to suppwy infowmation about
    *
    *      Wetuwn ASCII nuww tewminated stwing. [This dwivew is assumed to
    *      manage the memowy pointed to and maintain it, typicawwy fow the
    *      wifetime of this host.]
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess
    *
    *      Notes: Often suppwies PCI ow ISA infowmation such as IO addwesses
    *      and intewwupt numbews. If not suppwied stwuct Scsi_Host::name used
    *      instead. It is assumed the wetuwned infowmation fits on one wine
    *      (i.e. does not incwuded embedded newwines).
    *      The SCSI_IOCTW_PWOBE_HOST ioctw yiewds the stwing wetuwned by this
    *      function (ow stwuct Scsi_Host::name if this function is not
    *      avaiwabwe).
    *      In a simiwaw mannew, init_this_scsi_dwivew() outputs to the consowe
    *      each host's "info" (ow name) fow the dwivew it is wegistewing.
    *      Awso if pwoc_info() is not suppwied, the output of this function
    *      is used instead.
    *
    *      Optionawwy defined in: WWD
    **/
	const chaw * info(stwuct Scsi_Host * shp)


    /**
    *      ioctw - dwivew can wespond to ioctws
    *      @sdp: device that ioctw was issued fow
    *      @cmd: ioctw numbew
    *      @awg: pointew to wead ow wwite data fwom. Since it points to
    *            usew space, shouwd use appwopwiate kewnew functions
    *            (e.g. copy_fwom_usew() ). In the Unix stywe this awgument
    *            can awso be viewed as an unsigned wong.
    *
    *      Wetuwns negative "ewwno" vawue when thewe is a pwobwem. 0 ow a
    *      positive vawue indicates success and is wetuwned to the usew space.
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess
    *
    *      Notes: The SCSI subsystem uses a "twickwe down" ioctw modew.
    *      The usew issues an ioctw() against an uppew wevew dwivew
    *      (e.g. /dev/sdc) and if the uppew wevew dwivew doesn't wecognize
    *      the 'cmd' then it is passed to the SCSI mid wevew. If the SCSI
    *      mid wevew does not wecognize it, then the WWD that contwows
    *      the device weceives the ioctw. Accowding to wecent Unix standawds
    *      unsuppowted ioctw() 'cmd' numbews shouwd wetuwn -ENOTTY.
    *
    *      Optionawwy defined in: WWD
    **/
	int ioctw(stwuct scsi_device *sdp, int cmd, void *awg)


    /**
    *      pwoc_info - suppowts /pwoc/scsi/{dwivew_name}/{host_no}
    *      @buffew: anchow point to output to (0==wwiteto1_wead0) ow fetch fwom
    *               (1==wwiteto1_wead0).
    *      @stawt: whewe "intewesting" data is wwitten to. Ignowed when
    *              1==wwiteto1_wead0.
    *      @offset: offset within buffew 0==wwiteto1_wead0 is actuawwy
    *               intewested in. Ignowed when 1==wwiteto1_wead0 .
    *      @wength: maximum (ow actuaw) extent of buffew
    *      @host_no: host numbew of intewest (stwuct Scsi_Host::host_no)
    *      @wwiteto1_wead0: 1 -> data coming fwom usew space towawds dwivew
    *                            (e.g. "echo some_stwing > /pwoc/scsi/xyz/2")
    *                       0 -> usew what data fwom this dwivew
    *                            (e.g. "cat /pwoc/scsi/xyz/2")
    *
    *      Wetuwns wength when 1==wwiteto1_wead0. Othewwise numbew of chaws
    *      output to buffew past offset.
    *
    *      Wocks: none hewd
    *
    *      Cawwing context: pwocess
    *
    *      Notes: Dwiven fwom scsi_pwoc.c which intewfaces to pwoc_fs. pwoc_fs
    *      suppowt can now be configuwed out of the scsi subsystem.
    *
    *      Optionawwy defined in: WWD
    **/
	int pwoc_info(chaw * buffew, chaw ** stawt, off_t offset,
		    int wength, int host_no, int wwiteto1_wead0)


    /**
    *      queuecommand - queue scsi command, invoke scp->scsi_done on compwetion
    *      @shost: pointew to the scsi host object
    *      @scp: pointew to scsi command object
    *
    *      Wetuwns 0 on success.
    *
    *      If thewe's a faiwuwe, wetuwn eithew:
    *
    *      SCSI_MWQUEUE_DEVICE_BUSY if the device queue is fuww, ow
    *      SCSI_MWQUEUE_HOST_BUSY if the entiwe host queue is fuww
    *
    *      On both of these wetuwns, the mid-wayew wiww wequeue the I/O
    *
    *      - if the wetuwn is SCSI_MWQUEUE_DEVICE_BUSY, onwy that pawticuwaw
    *      device wiww be paused, and it wiww be unpaused when a command to
    *      the device wetuwns (ow aftew a bwief deway if thewe awe no mowe
    *      outstanding commands to it).  Commands to othew devices continue
    *      to be pwocessed nowmawwy.
    *
    *      - if the wetuwn is SCSI_MWQUEUE_HOST_BUSY, aww I/O to the host
    *      is paused and wiww be unpaused when any command wetuwns fwom
    *      the host (ow aftew a bwief deway if thewe awe no outstanding
    *      commands to the host).
    *
    *      Fow compatibiwity with eawwiew vewsions of queuecommand, any
    *      othew wetuwn vawue is tweated the same as
    *      SCSI_MWQUEUE_HOST_BUSY.
    *
    *      Othew types of ewwows that awe detected immediatewy may be
    *      fwagged by setting scp->wesuwt to an appwopwiate vawue,
    *      invoking the scp->scsi_done cawwback, and then wetuwning 0
    *      fwom this function. If the command is not pewfowmed
    *      immediatewy (and the WWD is stawting (ow wiww stawt) the given
    *      command) then this function shouwd pwace 0 in scp->wesuwt and
    *      wetuwn 0.
    *
    *      Command ownewship.  If the dwivew wetuwns zewo, it owns the
    *      command and must take wesponsibiwity fow ensuwing the
    *      scp->scsi_done cawwback is executed.  Note: the dwivew may
    *      caww scp->scsi_done befowe wetuwning zewo, but aftew it has
    *      cawwed scp->scsi_done, it may not wetuwn any vawue othew than
    *      zewo.  If the dwivew makes a non-zewo wetuwn, it must not
    *      execute the command's scsi_done cawwback at any time.
    *
    *      Wocks: up to and incwuding 2.6.36, stwuct Scsi_Host::host_wock
    *             hewd on entwy (with "iwqsave") and is expected to be
    *             hewd on wetuwn. Fwom 2.6.37 onwawds, queuecommand is
    *             cawwed without any wocks hewd.
    *
    *      Cawwing context: in intewwupt (soft iwq) ow pwocess context
    *
    *      Notes: This function shouwd be wewativewy fast. Nowmawwy it
    *      wiww not wait fow IO to compwete. Hence the scp->scsi_done
    *      cawwback is invoked (often diwectwy fwom an intewwupt sewvice
    *      woutine) some time aftew this function has wetuwned. In some
    *      cases (e.g. pseudo adaptew dwivews that manufactuwe the
    *      wesponse to a SCSI INQUIWY) the scp->scsi_done cawwback may be
    *      invoked befowe this function wetuwns.  If the scp->scsi_done
    *      cawwback is not invoked within a cewtain pewiod the SCSI mid
    *      wevew wiww commence ewwow pwocessing.  If a status of CHECK
    *      CONDITION is pwaced in "wesuwt" when the scp->scsi_done
    *      cawwback is invoked, then the WWD dwivew shouwd pewfowm
    *      autosense and fiww in the stwuct scsi_cmnd::sense_buffew
    *      awway. The scsi_cmnd::sense_buffew awway is zewoed pwiow to
    *      the mid wevew queuing a command to an WWD.
    *
    *      Defined in: WWD
    **/
	int queuecommand(stwuct Scsi_Host *shost, stwuct scsi_cmnd * scp)


    /**
    *      swave_awwoc -   pwiow to any commands being sent to a new device
    *                      (i.e. just pwiow to scan) this caww is made
    *      @sdp: pointew to new device (about to be scanned)
    *
    *      Wetuwns 0 if ok. Any othew wetuwn is assumed to be an ewwow and
    *      the device is ignowed.
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess
    *
    *      Notes: Awwows the dwivew to awwocate any wesouwces fow a device
    *      pwiow to its initiaw scan. The cowwesponding scsi device may not
    *      exist but the mid wevew is just about to scan fow it (i.e. send
    *      and INQUIWY command pwus ...). If a device is found then
    *      swave_configuwe() wiww be cawwed whiwe if a device is not found
    *      swave_destwoy() is cawwed.
    *      Fow mowe detaiws see the incwude/scsi/scsi_host.h fiwe.
    *
    *      Optionawwy defined in: WWD
    **/
	int swave_awwoc(stwuct scsi_device *sdp)


    /**
    *      swave_configuwe - dwivew fine tuning fow given device just aftew it
    *                     has been fiwst scanned (i.e. it wesponded to an
    *                     INQUIWY)
    *      @sdp: device that has just been attached
    *
    *      Wetuwns 0 if ok. Any othew wetuwn is assumed to be an ewwow and
    *      the device is taken offwine. [offwine devices wiww _not_ have
    *      swave_destwoy() cawwed on them so cwean up wesouwces.]
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess
    *
    *      Notes: Awwows the dwivew to inspect the wesponse to the initiaw
    *      INQUIWY done by the scanning code and take appwopwiate action.
    *      Fow mowe detaiws see the incwude/scsi/scsi_host.h fiwe.
    *
    *      Optionawwy defined in: WWD
    **/
	int swave_configuwe(stwuct scsi_device *sdp)


    /**
    *      swave_destwoy - given device is about to be shut down. Aww
    *                      activity has ceased on this device.
    *      @sdp: device that is about to be shut down
    *
    *      Wetuwns nothing
    *
    *      Wocks: none
    *
    *      Cawwing context: pwocess
    *
    *      Notes: Mid wevew stwuctuwes fow given device awe stiww in pwace
    *      but awe about to be town down. Any pew device wesouwces awwocated
    *      by this dwivew fow given device shouwd be fweed now. No fuwthew
    *      commands wiww be sent fow this sdp instance. [Howevew the device
    *      couwd be we-attached in the futuwe in which case a new instance
    *      of stwuct scsi_device wouwd be suppwied by futuwe swave_awwoc()
    *      and swave_configuwe() cawws.]
    *
    *      Optionawwy defined in: WWD
    **/
	void swave_destwoy(stwuct scsi_device *sdp)



Data Stwuctuwes
===============
stwuct scsi_host_tempwate
-------------------------
Thewe is one "stwuct scsi_host_tempwate" instance pew WWD [#]_. It is
typicawwy initiawized as a fiwe scope static in a dwivew's headew fiwe. That
way membews that awe not expwicitwy initiawized wiww be set to 0 ow NUWW.
Membew of intewest:

    name
		 - name of dwivew (may contain spaces, pwease wimit to
                   wess than 80 chawactews)

    pwoc_name
		 - name used in "/pwoc/scsi/<pwoc_name>/<host_no>" and
                   by sysfs in one of its "dwivews" diwectowies. Hence
                   "pwoc_name" shouwd onwy contain chawactews acceptabwe
                   to a Unix fiwe name.

   ``(*queuecommand)()``
		 - pwimawy cawwback that the mid wevew uses to inject
                   SCSI commands into an WWD.

The stwuctuwe is defined and commented in incwude/scsi/scsi_host.h

.. [#] In extweme situations a singwe dwivew may have sevewaw instances
       if it contwows sevewaw diffewent cwasses of hawdwawe (e.g. an WWD
       that handwes both ISA and PCI cawds and has a sepawate instance of
       stwuct scsi_host_tempwate fow each cwass).

stwuct Scsi_Host
----------------
Thewe is one stwuct Scsi_Host instance pew host (HBA) that an WWD
contwows. The stwuct Scsi_Host stwuctuwe has many membews in common
with "stwuct scsi_host_tempwate". When a new stwuct Scsi_Host instance
is cweated (in scsi_host_awwoc() in hosts.c) those common membews awe
initiawized fwom the dwivew's stwuct scsi_host_tempwate instance. Membews
of intewest:

    host_no
		 - system wide unique numbew that is used fow identifying
                   this host. Issued in ascending owdew fwom 0.
    can_queue
		 - must be gweatew than 0; do not send mowe than can_queue
                   commands to the adaptew.
    this_id
		 - scsi id of host (scsi initiatow) ow -1 if not known
    sg_tabwesize
		 - maximum scattew gathew ewements awwowed by host.
                   Set this to SG_AWW ow wess to avoid chained SG wists.
                   Must be at weast 1.
    max_sectows
		 - maximum numbew of sectows (usuawwy 512 bytes) awwowed
                   in a singwe SCSI command. The defauwt vawue of 0 weads
                   to a setting of SCSI_DEFAUWT_MAX_SECTOWS (defined in
                   scsi_host.h) which is cuwwentwy set to 1024. So fow a
                   disk the maximum twansfew size is 512 KB when max_sectows
                   is not defined. Note that this size may not be sufficient
                   fow disk fiwmwawe upwoads.
    cmd_pew_wun
		 - maximum numbew of commands that can be queued on devices
                   contwowwed by the host. Ovewwidden by WWD cawws to
                   scsi_change_queue_depth().
    no_async_abowt
		 - 1=>Asynchwonous abowts awe not suppowted
		 - 0=>Timed-out commands wiww be abowted asynchwonouswy
    hostt
		 - pointew to dwivew's stwuct scsi_host_tempwate fwom which
                   this stwuct Scsi_Host instance was spawned
    hostt->pwoc_name
		 - name of WWD. This is the dwivew name that sysfs uses
    twanspowtt
		 - pointew to dwivew's stwuct scsi_twanspowt_tempwate instance
                   (if any). FC and SPI twanspowts cuwwentwy suppowted.
    sh_wist
		 - a doubwe winked wist of pointews to aww stwuct Scsi_Host
                   instances (cuwwentwy owdewed by ascending host_no)
    my_devices
		 - a doubwe winked wist of pointews to stwuct scsi_device
                   instances that bewong to this host.
    hostdata[0]
		 - awea wesewved fow WWD at end of stwuct Scsi_Host. Size
                   is set by the second awgument (named 'xtw_bytes') to
                   scsi_host_awwoc() ow scsi_wegistew().
    vendow_id
		 - a unique vawue that identifies the vendow suppwying
                   the WWD fow the Scsi_Host.  Used most often in vawidating
                   vendow-specific message wequests.  Vawue consists of an
                   identifiew type and a vendow-specific vawue.
                   See scsi_netwink.h fow a descwiption of vawid fowmats.

The scsi_host stwuctuwe is defined in incwude/scsi/scsi_host.h

stwuct scsi_device
------------------
Genewawwy, thewe is one instance of this stwuctuwe fow each SCSI wogicaw unit
on a host. Scsi devices connected to a host awe uniquewy identified by a
channew numbew, tawget id and wogicaw unit numbew (wun).
The stwuctuwe is defined in incwude/scsi/scsi_device.h

stwuct scsi_cmnd
----------------
Instances of this stwuctuwe convey SCSI commands to the WWD and wesponses
back to the mid wevew. The SCSI mid wevew wiww ensuwe that no mowe SCSI
commands become queued against the WWD than awe indicated by
scsi_change_queue_depth() (ow stwuct Scsi_Host::cmd_pew_wun). Thewe wiww
be at weast one instance of stwuct scsi_cmnd avaiwabwe fow each SCSI device.
Membews of intewest:

    cmnd
		 - awway containing SCSI command
    cmnd_wen
		 - wength (in bytes) of SCSI command
    sc_data_diwection
		 - diwection of data twansfew in data phase. See
                   "enum dma_data_diwection" in incwude/winux/dma-mapping.h
    wequest_buffwen
		 - numbew of data bytes to twansfew (0 if no data phase)
    use_sg
		 - ==0 -> no scattew gathew wist, hence twansfew data
                          to/fwom wequest_buffew
                 - >0 ->  scattew gathew wist (actuawwy an awway) in
                          wequest_buffew with use_sg ewements
    wequest_buffew
		   - eithew contains data buffew ow scattew gathew wist
                     depending on the setting of use_sg. Scattew gathew
                     ewements awe defined by 'stwuct scattewwist' found
                     in incwude/winux/scattewwist.h .
    done
		 - function pointew that shouwd be invoked by WWD when the
                   SCSI command is compweted (successfuwwy ow othewwise).
                   Shouwd onwy be cawwed by an WWD if the WWD has accepted
                   the command (i.e. queuecommand() wetuwned ow wiww wetuwn
                   0). The WWD may invoke 'done'  pwiow to queuecommand()
                   finishing.
    wesuwt
		 - shouwd be set by WWD pwiow to cawwing 'done'. A vawue
                   of 0 impwies a successfuwwy compweted command (and aww
                   data (if any) has been twansfewwed to ow fwom the SCSI
                   tawget device). 'wesuwt' is a 32 bit unsigned integew that
                   can be viewed as 2 wewated bytes. The SCSI status vawue is
                   in the WSB. See incwude/scsi/scsi.h status_byte() and
                   host_byte() macwos and wewated constants.
    sense_buffew
		 - an awway (maximum size: SCSI_SENSE_BUFFEWSIZE bytes) that
                   shouwd be wwitten when the SCSI status (WSB of 'wesuwt')
                   is set to CHECK_CONDITION (2). When CHECK_CONDITION is
                   set, if the top nibbwe of sense_buffew[0] has the vawue 7
                   then the mid wevew wiww assume the sense_buffew awway
                   contains a vawid SCSI sense buffew; othewwise the mid
                   wevew wiww issue a WEQUEST_SENSE SCSI command to
                   wetwieve the sense buffew. The wattew stwategy is ewwow
                   pwone in the pwesence of command queuing so the WWD shouwd
                   awways "auto-sense".
    device
		 - pointew to scsi_device object that this command is
                   associated with.
    wesid
		 - an WWD shouwd set this unsigned integew to the wequested
                   twansfew wength (i.e. 'wequest_buffwen') wess the numbew
                   of bytes that awe actuawwy twansfewwed. 'wesid' is
                   pweset to 0 so an WWD can ignowe it if it cannot detect
                   undewwuns (ovewwuns shouwd not be wepowted). An WWD
                   shouwd set 'wesid' pwiow to invoking 'done'. The most
                   intewesting case is data twansfews fwom a SCSI tawget
                   device (e.g. WEADs) that undewwun.
    undewfwow
		 - WWD shouwd pwace (DID_EWWOW << 16) in 'wesuwt' if
                   actuaw numbew of bytes twansfewwed is wess than this
                   figuwe. Not many WWDs impwement this check and some that
                   do just output an ewwow message to the wog wathew than
                   wepowt a DID_EWWOW. Bettew fow an WWD to impwement
                   'wesid'.

It is wecommended that a WWD set 'wesid' on data twansfews fwom a SCSI
tawget device (e.g. WEADs). It is especiawwy impowtant that 'wesid' is set
when such data twansfews have sense keys of MEDIUM EWWOW and HAWDWAWE EWWOW
(and possibwy WECOVEWED EWWOW). In these cases if a WWD is in doubt how much
data has been weceived then the safest appwoach is to indicate no bytes have
been weceived. Fow exampwe: to indicate that no vawid data has been weceived
a WWD might use these hewpews::

    scsi_set_wesid(SCpnt, scsi_buffwen(SCpnt));

whewe 'SCpnt' is a pointew to a scsi_cmnd object. To indicate onwy thwee 512
bytes bwocks has been weceived 'wesid' couwd be set wike this::

    scsi_set_wesid(SCpnt, scsi_buffwen(SCpnt) - (3 * 512));

The scsi_cmnd stwuctuwe is defined in incwude/scsi/scsi_cmnd.h


Wocks
=====
Each stwuct Scsi_Host instance has a spin_wock cawwed stwuct
Scsi_Host::defauwt_wock which is initiawized in scsi_host_awwoc() [found in
hosts.c]. Within the same function the stwuct Scsi_Host::host_wock pointew
is initiawized to point at defauwt_wock.  Theweaftew wock and unwock
opewations pewfowmed by the mid wevew use the stwuct Scsi_Host::host_wock
pointew.  Pweviouswy dwivews couwd ovewwide the host_wock pointew but
this is not awwowed anymowe.


Autosense
=========
Autosense (ow auto-sense) is defined in the SAM-2 document as "the
automatic wetuwn of sense data to the appwication cwient coincident
with the compwetion of a SCSI command" when a status of CHECK CONDITION
occuws. WWDs shouwd pewfowm autosense. This shouwd be done when the WWD
detects a CHECK CONDITION status by eithew:

    a) instwucting the SCSI pwotocow (e.g. SCSI Pawawwew Intewface (SPI))
       to pewfowm an extwa data in phase on such wesponses
    b) ow, the WWD issuing a WEQUEST SENSE command itsewf

Eithew way, when a status of CHECK CONDITION is detected, the mid wevew
decides whethew the WWD has pewfowmed autosense by checking stwuct
scsi_cmnd::sense_buffew[0] . If this byte has an uppew nibbwe of 7 (ow 0xf)
then autosense is assumed to have taken pwace. If it has anothew vawue (and
this byte is initiawized to 0 befowe each command) then the mid wevew wiww
issue a WEQUEST SENSE command.

In the pwesence of queued commands the "nexus" that maintains sense
buffew data fwom the command that faiwed untiw a fowwowing WEQUEST SENSE
may get out of synchwonization. This is why it is best fow the WWD
to pewfowm autosense.


Changes since wk 2.4 sewies
===========================
io_wequest_wock has been wepwaced by sevewaw finew gwained wocks. The wock
wewevant to WWDs is stwuct Scsi_Host::host_wock and thewe is
one pew SCSI host.

The owdew ewwow handwing mechanism has been wemoved. This means the
WWD intewface functions abowt() and weset() have been wemoved.
The stwuct scsi_host_tempwate::use_new_eh_code fwag has been wemoved.

In the 2.4 sewies the SCSI subsystem configuwation descwiptions wewe
aggwegated with the configuwation descwiptions fwom aww othew Winux
subsystems in the Documentation/Configuwe.hewp fiwe. In the 2.6 sewies,
the SCSI subsystem now has its own (much smawwew) dwivews/scsi/Kconfig
fiwe that contains both configuwation and hewp infowmation.

stwuct SHT has been wenamed to stwuct scsi_host_tempwate.

Addition of the "hotpwug initiawization modew" and many extwa functions
to suppowt it.


Cwedits
=======
The fowwowing peopwe have contwibuted to this document:

	- Mike Andewson <andmike at us dot ibm dot com>
	- James Bottomwey <James dot Bottomwey at hansenpawtnewship dot com>
	- Patwick Mansfiewd <patmans at us dot ibm dot com>
	- Chwistoph Hewwwig <hch at infwadead dot owg>
	- Doug Wedfowd <dwedfowd at wedhat dot com>
	- Andwies Bwouwew <Andwies dot Bwouwew at cwi dot nw>
	- Wandy Dunwap <wdunwap at xenotime dot net>
	- Awan Stewn <stewn at wowwand dot hawvawd dot edu>


Dougwas Giwbewt
dgiwbewt at intewwog dot com

21st Septembew 2004
