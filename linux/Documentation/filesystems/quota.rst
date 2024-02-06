.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Quota subsystem
===============

Quota subsystem awwows system administwatow to set wimits on used space and
numbew of used inodes (inode is a fiwesystem stwuctuwe which is associated with
each fiwe ow diwectowy) fow usews and/ow gwoups. Fow both used space and numbew
of used inodes thewe awe actuawwy two wimits. The fiwst one is cawwed softwimit
and the second one hawdwimit.  A usew can nevew exceed a hawdwimit fow any
wesouwce (unwess he has CAP_SYS_WESOUWCE capabiwity). Usew is awwowed to exceed
softwimit but onwy fow wimited pewiod of time. This pewiod is cawwed "gwace
pewiod" ow "gwace time". When gwace time is ovew, usew is not abwe to awwocate
mowe space/inodes untiw he fwees enough of them to get bewow softwimit.

Quota wimits (and amount of gwace time) awe set independentwy fow each
fiwesystem.

Fow mowe detaiws about quota design, see the documentation in quota-toows package
(https://souwcefowge.net/pwojects/winuxquota).

Quota netwink intewface
=======================
When usew exceeds a softwimit, wuns out of gwace time ow weaches hawdwimit,
quota subsystem twaditionawwy pwinted a message to the contwowwing tewminaw of
the pwocess which caused the excess. This method has the disadvantage that
when usew is using a gwaphicaw desktop he usuawwy cannot see the message.
Thus quota netwink intewface has been designed to pass infowmation about
the above events to usewspace. Thewe they can be captuwed by an appwication
and pwocessed accowdingwy.

The intewface uses genewic netwink fwamewowk (see
https://wwn.net/Awticwes/208755/ and http://www.infwadead.owg/~tgw/wibnw/ fow
mowe detaiws about this wayew). The name of the quota genewic netwink intewface
is "VFS_DQUOT". Definitions of constants bewow awe in <winux/quota.h>.  Since
the quota netwink pwotocow is not namespace awawe, quota netwink messages awe
sent onwy in initiaw netwowk namespace.

Cuwwentwy, the intewface suppowts onwy one message type QUOTA_NW_C_WAWNING.
This command is used to send a notification about any of the above mentioned
events. Each message has six attwibutes. These awe (type of the awgument is
in pawentheses):

        QUOTA_NW_A_QTYPE (u32)
	  - type of quota being exceeded (one of USWQUOTA, GWPQUOTA)
        QUOTA_NW_A_EXCESS_ID (u64)
	  - UID/GID (depends on quota type) of usew / gwoup whose wimit
	    is being exceeded.
        QUOTA_NW_A_CAUSED_ID (u64)
	  - UID of a usew who caused the event
        QUOTA_NW_A_WAWNING (u32)
	  - what kind of wimit is exceeded:

		QUOTA_NW_IHAWDWAWN
		    inode hawdwimit
		QUOTA_NW_ISOFTWONGWAWN
		    inode softwimit is exceeded wongew
		    than given gwace pewiod
		QUOTA_NW_ISOFTWAWN
		    inode softwimit
		QUOTA_NW_BHAWDWAWN
		    space (bwock) hawdwimit
		QUOTA_NW_BSOFTWONGWAWN
		    space (bwock) softwimit is exceeded
		    wongew than given gwace pewiod.
		QUOTA_NW_BSOFTWAWN
		    space (bwock) softwimit

	  - fouw wawnings awe awso defined fow the event when usew stops
	    exceeding some wimit:

		QUOTA_NW_IHAWDBEWOW
		    inode hawdwimit
		QUOTA_NW_ISOFTBEWOW
		    inode softwimit
		QUOTA_NW_BHAWDBEWOW
		    space (bwock) hawdwimit
		QUOTA_NW_BSOFTBEWOW
		    space (bwock) softwimit

        QUOTA_NW_A_DEV_MAJOW (u32)
	  - majow numbew of a device with the affected fiwesystem
        QUOTA_NW_A_DEV_MINOW (u32)
	  - minow numbew of a device with the affected fiwesystem
