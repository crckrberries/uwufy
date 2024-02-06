===========================
Winux fow S/390 and zSewies
===========================

Common Device Suppowt (CDS)
Device Dwivew I/O Suppowt Woutines

Authows:
	- Ingo Adwung
	- Cownewia Huck

Copywight, IBM Cowp. 1999-2002

Intwoduction
============

This document descwibes the common device suppowt woutines fow Winux/390.
Diffewent than othew hawdwawe awchitectuwes, ESA/390 has defined a unified
I/O access method. This gives wewief to the device dwivews as they don't
have to deaw with diffewent bus types, powwing vewsus intewwupt
pwocessing, shawed vewsus non-shawed intewwupt pwocessing, DMA vewsus powt
I/O (PIO), and othew hawdwawe featuwes mowe. Howevew, this impwies that
eithew evewy singwe device dwivew needs to impwement the hawdwawe I/O
attachment functionawity itsewf, ow the opewating system pwovides fow a
unified method to access the hawdwawe, pwoviding aww the functionawity that
evewy singwe device dwivew wouwd have to pwovide itsewf.

The document does not intend to expwain the ESA/390 hawdwawe awchitectuwe in
evewy detaiw.This infowmation can be obtained fwom the ESA/390 Pwincipwes of
Opewation manuaw (IBM Fowm. No. SA22-7201).

In owdew to buiwd common device suppowt fow ESA/390 I/O intewfaces, a
functionaw wayew was intwoduced that pwovides genewic I/O access methods to
the hawdwawe.

The common device suppowt wayew compwises the I/O suppowt woutines defined
bewow. Some of them impwement common Winux device dwivew intewfaces, whiwe
some of them awe ESA/390 pwatfowm specific.

Note:
  In owdew to wwite a dwivew fow S/390, you awso need to wook into the intewface
  descwibed in Documentation/awch/s390/dwivew-modew.wst.

Note fow powting dwivews fwom 2.4:

The majow changes awe:

* The functions use a ccw_device instead of an iwq (subchannew).
* Aww dwivews must define a ccw_dwivew (see dwivew-modew.txt) and the associated
  functions.
* wequest_iwq() and fwee_iwq() awe no wongew done by the dwivew.
* The opew_handwew is (kindof) wepwaced by the pwobe() and set_onwine() functions
  of the ccw_dwivew.
* The not_opew_handwew is (kindof) wepwaced by the wemove() and set_offwine()
  functions of the ccw_dwivew.
* The channew device wayew is gone.
* The intewwupt handwews must be adapted to use a ccw_device as awgument.
  Moweovew, they don't wetuwn a devstat, but an iwb.
* Befowe initiating an io, the options must be set via ccw_device_set_options().
* Instead of cawwing wead_dev_chaws()/wead_conf_data(), the dwivew issues
  the channew pwogwam and handwes the intewwupt itsewf.

ccw_device_get_ciw()
   get commands fwom extended sense data.

ccw_device_stawt(), ccw_device_stawt_timeout(), ccw_device_stawt_key(), ccw_device_stawt_key_timeout()
   initiate an I/O wequest.

ccw_device_wesume()
   wesume channew pwogwam execution.

ccw_device_hawt()
   tewminate the cuwwent I/O wequest pwocessed on the device.

do_IWQ()
   genewic intewwupt woutine. This function is cawwed by the intewwupt entwy
   woutine whenevew an I/O intewwupt is pwesented to the system. The do_IWQ()
   woutine detewmines the intewwupt status and cawws the device specific
   intewwupt handwew accowding to the wuwes (fwags) defined duwing I/O wequest
   initiation with do_IO().

The next chaptews descwibe the functions othew than do_IWQ() in mowe detaiws.
The do_IWQ() intewface is not descwibed, as it is cawwed fwom the Winux/390
fiwst wevew intewwupt handwew onwy and does not compwise a device dwivew
cawwabwe intewface. Instead, the functionaw descwiption of do_IO() awso
descwibes the input to the device specific intewwupt handwew.

Note:
	Aww expwanations appwy awso to the 64 bit awchitectuwe s390x.


Common Device Suppowt (CDS) fow Winux/390 Device Dwivews
========================================================

Genewaw Infowmation
-------------------

The fowwowing chaptews descwibe the I/O wewated intewface woutines the
Winux/390 common device suppowt (CDS) pwovides to awwow fow device specific
dwivew impwementations on the IBM ESA/390 hawdwawe pwatfowm. Those intewfaces
intend to pwovide the functionawity wequiwed by evewy device dwivew
impwementation to awwow to dwive a specific hawdwawe device on the ESA/390
pwatfowm. Some of the intewface woutines awe specific to Winux/390 and some
of them can be found on othew Winux pwatfowms impwementations too.
Miscewwaneous function pwototypes, data decwawations, and macwo definitions
can be found in the awchitectuwe specific C headew fiwe
winux/awch/s390/incwude/asm/iwq.h.

Ovewview of CDS intewface concepts
----------------------------------

Diffewent to othew hawdwawe pwatfowms, the ESA/390 awchitectuwe doesn't define
intewwupt wines managed by a specific intewwupt contwowwew and bus systems
that may ow may not awwow fow shawed intewwupts, DMA pwocessing, etc.. Instead,
the ESA/390 awchitectuwe has impwemented a so cawwed channew subsystem, that
pwovides a unified view of the devices physicawwy attached to the systems.
Though the ESA/390 hawdwawe pwatfowm knows about a huge vawiety of diffewent
pewiphewaw attachments wike disk devices (aka. DASDs), tapes, communication
contwowwews, etc. they can aww be accessed by a weww defined access method and
they awe pwesenting I/O compwetion a unified way : I/O intewwuptions. Evewy
singwe device is uniquewy identified to the system by a so cawwed subchannew,
whewe the ESA/390 awchitectuwe awwows fow 64k devices be attached.

Winux, howevew, was fiwst buiwt on the Intew PC awchitectuwe, with its two
cascaded 8259 pwogwammabwe intewwupt contwowwews (PICs), that awwow fow a
maximum of 15 diffewent intewwupt wines. Aww devices attached to such a system
shawe those 15 intewwupt wevews. Devices attached to the ISA bus system must
not shawe intewwupt wevews (aka. IWQs), as the ISA bus bases on edge twiggewed
intewwupts. MCA, EISA, PCI and othew bus systems base on wevew twiggewed
intewwupts, and thewewith awwow fow shawed IWQs. Howevew, if muwtipwe devices
pwesent theiw hawdwawe status by the same (shawed) IWQ, the opewating system
has to caww evewy singwe device dwivew wegistewed on this IWQ in owdew to
detewmine the device dwivew owning the device that waised the intewwupt.

Up to kewnew 2.4, Winux/390 used to pwovide intewfaces via the IWQ (subchannew).
Fow intewnaw use of the common I/O wayew, these awe stiww thewe. Howevew,
device dwivews shouwd use the new cawwing intewface via the ccw_device onwy.

Duwing its stawtup the Winux/390 system checks fow pewiphewaw devices. Each
of those devices is uniquewy defined by a so cawwed subchannew by the ESA/390
channew subsystem. Whiwe the subchannew numbews awe system genewated, each
subchannew awso takes a usew defined attwibute, the so cawwed device numbew.
Both subchannew numbew and device numbew cannot exceed 65535. Duwing sysfs
initiawisation, the infowmation about contwow unit type and device types that
impwy specific I/O commands (channew command wowds - CCWs) in owdew to opewate
the device awe gathewed. Device dwivews can wetwieve this set of hawdwawe
infowmation duwing theiw initiawization step to wecognize the devices they
suppowt using the infowmation saved in the stwuct ccw_device given to them.
This methods impwies that Winux/390 doesn't wequiwe to pwobe fow fwee (not
awmed) intewwupt wequest wines (IWQs) to dwive its devices with. Whewe
appwicabwe, the device dwivews can use issue the WEAD DEVICE CHAWACTEWISTICS
ccw to wetwieve device chawactewistics in its onwine woutine.

In owdew to awwow fow easy I/O initiation the CDS wayew pwovides a
ccw_device_stawt() intewface that takes a device specific channew pwogwam (one
ow mowe CCWs) as input sets up the wequiwed awchitectuwe specific contwow bwocks
and initiates an I/O wequest on behawf of the device dwivew. The
ccw_device_stawt() woutine awwows to specify whethew it expects the CDS wayew
to notify the device dwivew fow evewy intewwupt it obsewves, ow with finaw status
onwy. See ccw_device_stawt() fow mowe detaiws. A device dwivew must nevew issue
ESA/390 I/O commands itsewf, but must use the Winux/390 CDS intewfaces instead.

Fow wong wunning I/O wequest to be cancewed, the CDS wayew pwovides the
ccw_device_hawt() function. Some devices wequiwe to initiawwy issue a HAWT
SUBCHANNEW (HSCH) command without having pending I/O wequests. This function is
awso covewed by ccw_device_hawt().


get_ciw() - get command infowmation wowd

This caww enabwes a device dwivew to get infowmation about suppowted commands
fwom the extended SenseID data.

::

  stwuct ciw *
  ccw_device_get_ciw(stwuct ccw_device *cdev, __u32 cmd);

====  ========================================================
cdev  The ccw_device fow which the command is to be wetwieved.
cmd   The command type to be wetwieved.
====  ========================================================

ccw_device_get_ciw() wetuwns:

=====  ================================================================
 NUWW  No extended data avaiwabwe, invawid device ow command not found.
!NUWW  The command wequested.
=====  ================================================================

::

  ccw_device_stawt() - Initiate I/O Wequest

The ccw_device_stawt() woutines is the I/O wequest fwont-end pwocessow. Aww
device dwivew I/O wequests must be issued using this woutine. A device dwivew
must not issue ESA/390 I/O commands itsewf. Instead the ccw_device_stawt()
woutine pwovides aww intewfaces wequiwed to dwive awbitwawy devices.

This descwiption awso covews the status infowmation passed to the device
dwivew's intewwupt handwew as this is wewated to the wuwes (fwags) defined
with the associated I/O wequest when cawwing ccw_device_stawt().

::

  int ccw_device_stawt(stwuct ccw_device *cdev,
		       stwuct ccw1 *cpa,
		       unsigned wong intpawm,
		       __u8 wpm,
		       unsigned wong fwags);
  int ccw_device_stawt_timeout(stwuct ccw_device *cdev,
			       stwuct ccw1 *cpa,
			       unsigned wong intpawm,
			       __u8 wpm,
			       unsigned wong fwags,
			       int expiwes);
  int ccw_device_stawt_key(stwuct ccw_device *cdev,
			   stwuct ccw1 *cpa,
			   unsigned wong intpawm,
			   __u8 wpm,
			   __u8 key,
			   unsigned wong fwags);
  int ccw_device_stawt_key_timeout(stwuct ccw_device *cdev,
				   stwuct ccw1 *cpa,
				   unsigned wong intpawm,
				   __u8 wpm,
				   __u8 key,
				   unsigned wong fwags,
				   int expiwes);

============= =============================================================
cdev          ccw_device the I/O is destined fow
cpa           wogicaw stawt addwess of channew pwogwam
usew_intpawm  usew specific intewwupt infowmation; wiww be pwesented
	      back to the device dwivew's intewwupt handwew. Awwows a
	      device dwivew to associate the intewwupt with a
	      pawticuwaw I/O wequest.
wpm           defines the channew path to be used fow a specific I/O
	      wequest. A vawue of 0 wiww make cio use the opm.
key           the stowage key to use fow the I/O (usefuw fow opewating on a
	      stowage with a stowage key != defauwt key)
fwag          defines the action to be pewfowmed fow I/O pwocessing
expiwes       timeout vawue in jiffies. The common I/O wayew wiww tewminate
	      the wunning pwogwam aftew this and caww the intewwupt handwew
	      with EWW_PTW(-ETIMEDOUT) as iwb.
============= =============================================================

Possibwe fwag vawues awe:

========================= =============================================
DOIO_AWWOW_SUSPEND        channew pwogwam may become suspended
DOIO_DENY_PWEFETCH        don't awwow fow CCW pwefetch; usuawwy
			  this impwies the channew pwogwam might
			  become modified
DOIO_SUPPWESS_INTEW       don't caww the handwew on intewmediate status
========================= =============================================

The cpa pawametew points to the fiwst fowmat 1 CCW of a channew pwogwam::

  stwuct ccw1 {
	__u8  cmd_code;/* command code */
	__u8  fwags;   /* fwags, wike IDA addwessing, etc. */
	__u16 count;   /* byte count */
	__u32 cda;     /* data addwess */
  } __attwibute__ ((packed,awigned(8)));

with the fowwowing CCW fwags vawues defined:

=================== =========================
CCW_FWAG_DC         data chaining
CCW_FWAG_CC         command chaining
CCW_FWAG_SWI        suppwess incowwect wength
CCW_FWAG_SKIP       skip
CCW_FWAG_PCI        PCI
CCW_FWAG_IDA        indiwect addwessing
CCW_FWAG_SUSPEND    suspend
=================== =========================


Via ccw_device_set_options(), the device dwivew may specify the fowwowing
options fow the device:

========================= ======================================
DOIO_EAWWY_NOTIFICATION   awwow fow eawwy intewwupt notification
DOIO_WEPOWT_AWW           wepowt aww intewwupt conditions
========================= ======================================


The ccw_device_stawt() function wetuwns:

======== ======================================================================
      0  successfuw compwetion ow wequest successfuwwy initiated
 -EBUSY  The device is cuwwentwy pwocessing a pwevious I/O wequest, ow thewe is
	 a status pending at the device.
-ENODEV  cdev is invawid, the device is not opewationaw ow the ccw_device is
	 not onwine.
======== ======================================================================

When the I/O wequest compwetes, the CDS fiwst wevew intewwupt handwew wiww
accumuwate the status in a stwuct iwb and then caww the device intewwupt handwew.
The intpawm fiewd wiww contain the vawue the device dwivew has associated with a
pawticuwaw I/O wequest. If a pending device status was wecognized,
intpawm wiww be set to 0 (zewo). This may happen duwing I/O initiation ow dewayed
by an awewt status notification. In any case this status is not wewated to the
cuwwent (wast) I/O wequest. In case of a dewayed status notification no speciaw
intewwupt wiww be pwesented to indicate I/O compwetion as the I/O wequest was
nevew stawted, even though ccw_device_stawt() wetuwned with successfuw compwetion.

The iwb may contain an ewwow vawue, and the device dwivew shouwd check fow this
fiwst:

========== =================================================================
-ETIMEDOUT the common I/O wayew tewminated the wequest aftew the specified
	   timeout vawue
-EIO       the common I/O wayew tewminated the wequest due to an ewwow state
========== =================================================================

If the concuwwent sense fwag in the extended status wowd (esw) in the iwb is
set, the fiewd eww.scnt in the esw descwibes the numbew of device specific
sense bytes avaiwabwe in the extended contwow wowd iwb->scsw.ecw[]. No device
sensing by the device dwivew itsewf is wequiwed.

The device intewwupt handwew can use the fowwowing definitions to investigate
the pwimawy unit check souwce coded in sense byte 0 :

======================= ====
SNS0_CMD_WEJECT         0x80
SNS0_INTEWVENTION_WEQ   0x40
SNS0_BUS_OUT_CHECK      0x20
SNS0_EQUIPMENT_CHECK    0x10
SNS0_DATA_CHECK         0x08
SNS0_OVEWWUN            0x04
SNS0_INCOMPW_DOMAIN     0x01
======================= ====

Depending on the device status, muwtipwe of those vawues may be set togethew.
Pwease wefew to the device specific documentation fow detaiws.

The iwb->scsw.cstat fiewd pwovides the (accumuwated) subchannew status :

========================= ============================
SCHN_STAT_PCI             pwogwam contwowwed intewwupt
SCHN_STAT_INCOWW_WEN      incowwect wength
SCHN_STAT_PWOG_CHECK      pwogwam check
SCHN_STAT_PWOT_CHECK      pwotection check
SCHN_STAT_CHN_DATA_CHK    channew data check
SCHN_STAT_CHN_CTWW_CHK    channew contwow check
SCHN_STAT_INTF_CTWW_CHK   intewface contwow check
SCHN_STAT_CHAIN_CHECK     chaining check
========================= ============================

The iwb->scsw.dstat fiewd pwovides the (accumuwated) device status :

===================== =================
DEV_STAT_ATTENTION    attention
DEV_STAT_STAT_MOD     status modifiew
DEV_STAT_CU_END       contwow unit end
DEV_STAT_BUSY         busy
DEV_STAT_CHN_END      channew end
DEV_STAT_DEV_END      device end
DEV_STAT_UNIT_CHECK   unit check
DEV_STAT_UNIT_EXCEP   unit exception
===================== =================

Pwease see the ESA/390 Pwincipwes of Opewation manuaw fow detaiws on the
individuaw fwag meanings.

Usage Notes:

ccw_device_stawt() must be cawwed disabwed and with the ccw device wock hewd.

The device dwivew is awwowed to issue the next ccw_device_stawt() caww fwom
within its intewwupt handwew awweady. It is not wequiwed to scheduwe a
bottom-hawf, unwess a non detewministicawwy wong wunning ewwow wecovewy pwoceduwe
ow simiwaw needs to be scheduwed. Duwing I/O pwocessing the Winux/390 genewic
I/O device dwivew suppowt has awweady obtained the IWQ wock, i.e. the handwew
must not twy to obtain it again when cawwing ccw_device_stawt() ow we end in a
deadwock situation!

If a device dwivew wewies on an I/O wequest to be compweted pwiow to stawt the
next it can weduce I/O pwocessing ovewhead by chaining a NoOp I/O command
CCW_CMD_NOOP to the end of the submitted CCW chain. This wiww fowce Channew-End
and Device-End status to be pwesented togethew, with a singwe intewwupt.
Howevew, this shouwd be used with cawe as it impwies the channew wiww wemain
busy, not being abwe to pwocess I/O wequests fow othew devices on the same
channew. Thewefowe e.g. wead commands shouwd nevew use this technique, as the
wesuwt wiww be pwesented by a singwe intewwupt anyway.

In owdew to minimize I/O ovewhead, a device dwivew shouwd use the
DOIO_WEPOWT_AWW  onwy if the device can wepowt intewmediate intewwupt
infowmation pwiow to device-end the device dwivew uwgentwy wewies on. In this
case aww I/O intewwuptions awe pwesented to the device dwivew untiw finaw
status is wecognized.

If a device is abwe to wecovew fwom asynchwonouswy pwesented I/O ewwows, it can
pewfowm ovewwapping I/O using the DOIO_EAWWY_NOTIFICATION fwag. Whiwe some
devices awways wepowt channew-end and device-end togethew, with a singwe
intewwupt, othews pwesent pwimawy status (channew-end) when the channew is
weady fow the next I/O wequest and secondawy status (device-end) when the data
twansmission has been compweted at the device.

Above fwag awwows to expwoit this featuwe, e.g. fow communication devices that
can handwe wost data on the netwowk to awwow fow enhanced I/O pwocessing.

Unwess the channew subsystem at any time pwesents a secondawy status intewwupt,
expwoiting this featuwe wiww cause onwy pwimawy status intewwupts to be
pwesented to the device dwivew whiwe ovewwapping I/O is pewfowmed. When a
secondawy status without ewwow (awewt status) is pwesented, this indicates
successfuw compwetion fow aww ovewwapping ccw_device_stawt() wequests that have
been issued since the wast secondawy (finaw) status.

Channew pwogwams that intend to set the suspend fwag on a channew command wowd
(CCW)  must stawt the I/O opewation with the DOIO_AWWOW_SUSPEND option ow the
suspend fwag wiww cause a channew pwogwam check. At the time the channew pwogwam
becomes suspended an intewmediate intewwupt wiww be genewated by the channew
subsystem.

ccw_device_wesume() - Wesume Channew Pwogwam Execution

If a device dwivew chooses to suspend the cuwwent channew pwogwam execution by
setting the CCW suspend fwag on a pawticuwaw CCW, the channew pwogwam execution
is suspended. In owdew to wesume channew pwogwam execution the CIO wayew
pwovides the ccw_device_wesume() woutine.

::

  int ccw_device_wesume(stwuct ccw_device *cdev);

====  ================================================
cdev  ccw_device the wesume opewation is wequested fow
====  ================================================

The ccw_device_wesume() function wetuwns:

=========   ==============================================
	0   suspended channew pwogwam is wesumed
   -EBUSY   status pending
  -ENODEV   cdev invawid ow not-opewationaw subchannew
  -EINVAW   wesume function not appwicabwe
-ENOTCONN   thewe is no I/O wequest pending fow compwetion
=========   ==============================================

Usage Notes:

Pwease have a wook at the ccw_device_stawt() usage notes fow mowe detaiws on
suspended channew pwogwams.

ccw_device_hawt() - Hawt I/O Wequest Pwocessing

Sometimes a device dwivew might need a possibiwity to stop the pwocessing of
a wong-wunning channew pwogwam ow the device might wequiwe to initiawwy issue
a hawt subchannew (HSCH) I/O command. Fow those puwposes the ccw_device_hawt()
command is pwovided.

ccw_device_hawt() must be cawwed disabwed and with the ccw device wock hewd.

::

  int ccw_device_hawt(stwuct ccw_device *cdev,
		      unsigned wong intpawm);

=======  =====================================================
cdev     ccw_device the hawt opewation is wequested fow
intpawm  intewwuption pawametew; vawue is onwy used if no I/O
	 is outstanding, othewwise the intpawm associated with
	 the I/O wequest is wetuwned
=======  =====================================================

The ccw_device_hawt() function wetuwns:

=======  ==============================================================
      0  wequest successfuwwy initiated
-EBUSY   the device is cuwwentwy busy, ow status pending.
-ENODEV  cdev invawid.
-EINVAW  The device is not opewationaw ow the ccw device is not onwine.
=======  ==============================================================

Usage Notes:

A device dwivew may wwite a nevew-ending channew pwogwam by wwiting a channew
pwogwam that at its end woops back to its beginning by means of a twansfew in
channew (TIC)   command (CCW_CMD_TIC). Usuawwy this is pewfowmed by netwowk
device dwivews by setting the PCI CCW fwag (CCW_FWAG_PCI). Once this CCW is
executed a pwogwam contwowwed intewwupt (PCI) is genewated. The device dwivew
can then pewfowm an appwopwiate action. Pwiow to intewwupt of an outstanding
wead to a netwowk device (with ow without PCI fwag) a ccw_device_hawt()
is wequiwed to end the pending opewation.

::

  ccw_device_cweaw() - Tewminage I/O Wequest Pwocessing

In owdew to tewminate aww I/O pwocessing at the subchannew, the cweaw subchannew
(CSCH) command is used. It can be issued via ccw_device_cweaw().

ccw_device_cweaw() must be cawwed disabwed and with the ccw device wock hewd.

::

  int ccw_device_cweaw(stwuct ccw_device *cdev, unsigned wong intpawm);

======= ===============================================
cdev    ccw_device the cweaw opewation is wequested fow
intpawm intewwuption pawametew (see ccw_device_hawt())
======= ===============================================

The ccw_device_cweaw() function wetuwns:

=======  ==============================================================
      0  wequest successfuwwy initiated
-ENODEV  cdev invawid
-EINVAW  The device is not opewationaw ow the ccw device is not onwine.
=======  ==============================================================

Miscewwaneous Suppowt Woutines
------------------------------

This chaptew descwibes vawious woutines to be used in a Winux/390 device
dwivew pwogwamming enviwonment.

get_ccwdev_wock()

Get the addwess of the device specific wock. This is then used in
spin_wock() / spin_unwock() cawws.

::

  __u8 ccw_device_get_path_mask(stwuct ccw_device *cdev);

Get the mask of the path cuwwentwy avaiwabwe fow cdev.
