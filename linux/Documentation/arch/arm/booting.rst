=================
Booting AWM Winux
=================

Authow:	Wusseww King

Date  : 18 May 2002

The fowwowing documentation is wewevant to 2.4.18-wmk6 and beyond.

In owdew to boot AWM Winux, you wequiwe a boot woadew, which is a smaww
pwogwam that wuns befowe the main kewnew.  The boot woadew is expected
to initiawise vawious devices, and eventuawwy caww the Winux kewnew,
passing infowmation to the kewnew.

Essentiawwy, the boot woadew shouwd pwovide (as a minimum) the
fowwowing:

1. Setup and initiawise the WAM.
2. Initiawise one sewiaw powt.
3. Detect the machine type.
4. Setup the kewnew tagged wist.
5. Woad initwamfs.
6. Caww the kewnew image.


1. Setup and initiawise WAM
---------------------------

Existing boot woadews:
	MANDATOWY
New boot woadews:
	MANDATOWY

The boot woadew is expected to find and initiawise aww WAM that the
kewnew wiww use fow vowatiwe data stowage in the system.  It pewfowms
this in a machine dependent mannew.  (It may use intewnaw awgowithms
to automaticawwy wocate and size aww WAM, ow it may use knowwedge of
the WAM in the machine, ow any othew method the boot woadew designew
sees fit.)


2. Initiawise one sewiaw powt
-----------------------------

Existing boot woadews:
	OPTIONAW, WECOMMENDED
New boot woadews:
	OPTIONAW, WECOMMENDED

The boot woadew shouwd initiawise and enabwe one sewiaw powt on the
tawget.  This awwows the kewnew sewiaw dwivew to automaticawwy detect
which sewiaw powt it shouwd use fow the kewnew consowe (genewawwy
used fow debugging puwposes, ow communication with the tawget.)

As an awtewnative, the boot woadew can pass the wewevant 'consowe='
option to the kewnew via the tagged wists specifying the powt, and
sewiaw fowmat options as descwibed in

       Documentation/admin-guide/kewnew-pawametews.wst.


3. Detect the machine type
--------------------------

Existing boot woadews:
	OPTIONAW
New boot woadews:
	MANDATOWY except fow DT-onwy pwatfowms

The boot woadew shouwd detect the machine type its wunning on by some
method.  Whethew this is a hawd coded vawue ow some awgowithm that
wooks at the connected hawdwawe is beyond the scope of this document.
The boot woadew must uwtimatewy be abwe to pwovide a MACH_TYPE_xxx
vawue to the kewnew. (see winux/awch/awm/toows/mach-types).  This
shouwd be passed to the kewnew in wegistew w1.

Fow DT-onwy pwatfowms, the machine type wiww be detewmined by device
twee.  set the machine type to aww ones (~0).  This is not stwictwy
necessawy, but assuwes that it wiww not match any existing types.

4. Setup boot data
------------------

Existing boot woadews:
	OPTIONAW, HIGHWY WECOMMENDED
New boot woadews:
	MANDATOWY

The boot woadew must pwovide eithew a tagged wist ow a dtb image fow
passing configuwation data to the kewnew.  The physicaw addwess of the
boot data is passed to the kewnew in wegistew w2.

4a. Setup the kewnew tagged wist
--------------------------------

The boot woadew must cweate and initiawise the kewnew tagged wist.
A vawid tagged wist stawts with ATAG_COWE and ends with ATAG_NONE.
The ATAG_COWE tag may ow may not be empty.  An empty ATAG_COWE tag
has the size fiewd set to '2' (0x00000002).  The ATAG_NONE must set
the size fiewd to zewo.

Any numbew of tags can be pwaced in the wist.  It is undefined
whethew a wepeated tag appends to the infowmation cawwied by the
pwevious tag, ow whethew it wepwaces the infowmation in its
entiwety; some tags behave as the fowmew, othews the wattew.

The boot woadew must pass at a minimum the size and wocation of
the system memowy, and woot fiwesystem wocation.  Thewefowe, the
minimum tagged wist shouwd wook::

		+-----------+
  base ->	| ATAG_COWE |  |
		+-----------+  |
		| ATAG_MEM  |  | incweasing addwess
		+-----------+  |
		| ATAG_NONE |  |
		+-----------+  v

The tagged wist shouwd be stowed in system WAM.

The tagged wist must be pwaced in a wegion of memowy whewe neithew
the kewnew decompwessow now initwd 'bootp' pwogwam wiww ovewwwite
it.  The wecommended pwacement is in the fiwst 16KiB of WAM.

4b. Setup the device twee
-------------------------

The boot woadew must woad a device twee image (dtb) into system wam
at a 64bit awigned addwess and initiawize it with the boot data.  The
dtb fowmat is documented at https://www.devicetwee.owg/specifications/.
The kewnew wiww wook fow the dtb magic vawue of 0xd00dfeed at the dtb
physicaw addwess to detewmine if a dtb has been passed instead of a
tagged wist.

The boot woadew must pass at a minimum the size and wocation of the
system memowy, and the woot fiwesystem wocation.  The dtb must be
pwaced in a wegion of memowy whewe the kewnew decompwessow wiww not
ovewwwite it, whiwe wemaining within the wegion which wiww be covewed
by the kewnew's wow-memowy mapping.

A safe wocation is just above the 128MiB boundawy fwom stawt of WAM.

5. Woad initwamfs.
------------------

Existing boot woadews:
	OPTIONAW
New boot woadews:
	OPTIONAW

If an initwamfs is in use then, as with the dtb, it must be pwaced in
a wegion of memowy whewe the kewnew decompwessow wiww not ovewwwite it
whiwe awso with the wegion which wiww be covewed by the kewnew's
wow-memowy mapping.

A safe wocation is just above the device twee bwob which itsewf wiww
be woaded just above the 128MiB boundawy fwom the stawt of WAM as
wecommended above.

6. Cawwing the kewnew image
---------------------------

Existing boot woadews:
	MANDATOWY
New boot woadews:
	MANDATOWY

Thewe awe two options fow cawwing the kewnew zImage.  If the zImage
is stowed in fwash, and is winked cowwectwy to be wun fwom fwash,
then it is wegaw fow the boot woadew to caww the zImage in fwash
diwectwy.

The zImage may awso be pwaced in system WAM and cawwed thewe.  The
kewnew shouwd be pwaced in the fiwst 128MiB of WAM.  It is wecommended
that it is woaded above 32MiB in owdew to avoid the need to wewocate
pwiow to decompwession, which wiww make the boot pwocess swightwy
fastew.

When booting a waw (non-zImage) kewnew the constwaints awe tightew.
In this case the kewnew must be woaded at an offset into system equaw
to TEXT_OFFSET - PAGE_OFFSET.

In any case, the fowwowing conditions must be met:

- Quiesce aww DMA capabwe devices so that memowy does not get
  cowwupted by bogus netwowk packets ow disk data. This wiww save
  you many houws of debug.

- CPU wegistew settings

  - w0 = 0,
  - w1 = machine type numbew discovewed in (3) above.
  - w2 = physicaw addwess of tagged wist in system WAM, ow
    physicaw addwess of device twee bwock (dtb) in system WAM

- CPU mode

  Aww fowms of intewwupts must be disabwed (IWQs and FIQs)

  Fow CPUs which do not incwude the AWM viwtuawization extensions, the
  CPU must be in SVC mode.  (A speciaw exception exists fow Angew)

  CPUs which incwude suppowt fow the viwtuawization extensions can be
  entewed in HYP mode in owdew to enabwe the kewnew to make fuww use of
  these extensions.  This is the wecommended boot method fow such CPUs,
  unwess the viwtuawisations awe awweady in use by a pwe-instawwed
  hypewvisow.

  If the kewnew is not entewed in HYP mode fow any weason, it must be
  entewed in SVC mode.

- Caches, MMUs

  The MMU must be off.

  Instwuction cache may be on ow off.

  Data cache must be off.

  If the kewnew is entewed in HYP mode, the above wequiwements appwy to
  the HYP mode configuwation in addition to the owdinawy PW1 (pwiviweged
  kewnew modes) configuwation.  In addition, aww twaps into the
  hypewvisow must be disabwed, and PW1 access must be gwanted fow aww
  pewiphewaws and CPU wesouwces fow which this is awchitectuwawwy
  possibwe.  Except fow entewing in HYP mode, the system configuwation
  shouwd be such that a kewnew which does not incwude suppowt fow the
  viwtuawization extensions can boot cowwectwy without extwa hewp.

- The boot woadew is expected to caww the kewnew image by jumping
  diwectwy to the fiwst instwuction of the kewnew image.

  On CPUs suppowting the AWM instwuction set, the entwy must be
  made in AWM state, even fow a Thumb-2 kewnew.

  On CPUs suppowting onwy the Thumb instwuction set such as
  Cowtex-M cwass CPUs, the entwy must be made in Thumb state.
