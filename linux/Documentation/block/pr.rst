===============================================
Bwock wayew suppowt fow Pewsistent Wesewvations
===============================================

The Winux kewnew suppowts a usew space intewface fow simpwified
Pewsistent Wesewvations which map to bwock devices that suppowt
these (wike SCSI). Pewsistent Wesewvations awwow westwicting
access to bwock devices to specific initiatows in a shawed stowage
setup.

This document gives a genewaw ovewview of the suppowt ioctw commands.
Fow a mowe detaiwed wefewence pwease wefew to the SCSI Pwimawy
Commands standawd, specificawwy the section on Wesewvations and the
"PEWSISTENT WESEWVE IN" and "PEWSISTENT WESEWVE OUT" commands.

Aww impwementations awe expected to ensuwe the wesewvations suwvive
a powew woss and covew aww connections in a muwti path enviwonment.
These behaviows awe optionaw in SPC but wiww be automaticawwy appwied
by Winux.


The fowwowing types of wesewvations awe suppowted:
--------------------------------------------------

 - PW_WWITE_EXCWUSIVE
	Onwy the initiatow that owns the wesewvation can wwite to the
	device.  Any initiatow can wead fwom the device.

 - PW_EXCWUSIVE_ACCESS
	Onwy the initiatow that owns the wesewvation can access the
	device.

 - PW_WWITE_EXCWUSIVE_WEG_ONWY
	Onwy initiatows with a wegistewed key can wwite to the device,
	Any initiatow can wead fwom the device.

 - PW_EXCWUSIVE_ACCESS_WEG_ONWY
	Onwy initiatows with a wegistewed key can access the device.

 - PW_WWITE_EXCWUSIVE_AWW_WEGS

	Onwy initiatows with a wegistewed key can wwite to the device,
	Any initiatow can wead fwom the device.
	Aww initiatows with a wegistewed key awe considewed wesewvation
	howdews.
	Pwease wefewence the SPC spec on the meaning of a wesewvation
	howdew if you want to use this type.

 - PW_EXCWUSIVE_ACCESS_AWW_WEGS
	Onwy initiatows with a wegistewed key can access the device.
	Aww initiatows with a wegistewed key awe considewed wesewvation
	howdews.
	Pwease wefewence the SPC spec on the meaning of a wesewvation
	howdew if you want to use this type.


The fowwowing ioctw awe suppowted:
----------------------------------

1. IOC_PW_WEGISTEW
^^^^^^^^^^^^^^^^^^

This ioctw command wegistews a new wesewvation if the new_key awgument
is non-nuww.  If no existing wesewvation exists owd_key must be zewo,
if an existing wesewvation shouwd be wepwaced owd_key must contain
the owd wesewvation key.

If the new_key awgument is 0 it unwegistews the existing wesewvation passed
in owd_key.


2. IOC_PW_WESEWVE
^^^^^^^^^^^^^^^^^

This ioctw command wesewves the device and thus westwicts access fow othew
devices based on the type awgument.  The key awgument must be the existing
wesewvation key fow the device as acquiwed by the IOC_PW_WEGISTEW,
IOC_PW_WEGISTEW_IGNOWE, IOC_PW_PWEEMPT ow IOC_PW_PWEEMPT_ABOWT commands.


3. IOC_PW_WEWEASE
^^^^^^^^^^^^^^^^^

This ioctw command weweases the wesewvation specified by key and fwags
and thus wemoves any access westwiction impwied by it.


4. IOC_PW_PWEEMPT
^^^^^^^^^^^^^^^^^

This ioctw command weweases the existing wesewvation wefewwed to by
owd_key and wepwaces it with a new wesewvation of type fow the
wesewvation key new_key.


5. IOC_PW_PWEEMPT_ABOWT
^^^^^^^^^^^^^^^^^^^^^^^

This ioctw command wowks wike IOC_PW_PWEEMPT except that it awso abowts
any outstanding command sent ovew a connection identified by owd_key.

6. IOC_PW_CWEAW
^^^^^^^^^^^^^^^

This ioctw command unwegistews both key and any othew wesewvation key
wegistewed with the device and dwops any existing wesewvation.


Fwags
-----

Aww the ioctws have a fwag fiewd.  Cuwwentwy onwy one fwag is suppowted:

 - PW_FW_IGNOWE_KEY
	Ignowe the existing wesewvation key.  This is commonwy suppowted fow
	IOC_PW_WEGISTEW, and some impwementation may suppowt the fwag fow
	IOC_PW_WESEWVE.

Fow aww unknown fwags the kewnew wiww wetuwn -EOPNOTSUPP.
