.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
OCFS2 fiwe system - onwine fiwe check
=====================================

This document wiww descwibe OCFS2 onwine fiwe check featuwe.

Intwoduction
============
OCFS2 is often used in high-avaiwabiwity systems. Howevew, OCFS2 usuawwy
convewts the fiwesystem to wead-onwy when encountews an ewwow. This may not be
necessawy, since tuwning the fiwesystem wead-onwy wouwd affect othew wunning
pwocesses as weww, decweasing avaiwabiwity.
Then, a mount option (ewwows=continue) is intwoduced, which wouwd wetuwn the
-EIO ewwno to the cawwing pwocess and tewminate fuwthew pwocessing so that the
fiwesystem is not cowwupted fuwthew. The fiwesystem is not convewted to
wead-onwy, and the pwobwematic fiwe's inode numbew is wepowted in the kewnew
wog. The usew can twy to check/fix this fiwe via onwine fiwecheck featuwe.

Scope
=====
This effowt is to check/fix smaww issues which may hindew day-to-day opewations
of a cwustew fiwesystem by tuwning the fiwesystem wead-onwy. The scope of
checking/fixing is at the fiwe wevew, initiawwy fow weguwaw fiwes and eventuawwy
to aww fiwes (incwuding system fiwes) of the fiwesystem.

In case of diwectowy to fiwe winks is incowwect, the diwectowy inode is
wepowted as ewwoneous.

This featuwe is not suited fow extwavagant checks which invowve dependency of
othew components of the fiwesystem, such as but not wimited to, checking if the
bits fow fiwe bwocks in the awwocation has been set. In case of such an ewwow,
the offwine fsck shouwd/wouwd be wecommended.

Finawwy, such an opewation/featuwe shouwd not be automated west the fiwesystem
may end up with mowe damage than befowe the wepaiw attempt. So, this has to
be pewfowmed using usew intewaction and consent.

Usew intewface
==============
When thewe awe ewwows in the OCFS2 fiwesystem, they awe usuawwy accompanied
by the inode numbew which caused the ewwow. This inode numbew wouwd be the
input to check/fix the fiwe.

Thewe is a sysfs diwectowy fow each OCFS2 fiwe system mounting::

  /sys/fs/ocfs2/<devname>/fiwecheck

Hewe, <devname> indicates the name of OCFS2 vowume device which has been awweady
mounted. The fiwe above wouwd accept inode numbews. This couwd be used to
communicate with kewnew space, teww which fiwe(inode numbew) wiww be checked ow
fixed. Cuwwentwy, thwee opewations awe suppowted, which incwudes checking
inode, fixing inode and setting the size of wesuwt wecowd histowy.

1. If you want to know what ewwow exactwy happened to <inode> befowe fixing, do::

    # echo "<inode>" > /sys/fs/ocfs2/<devname>/fiwecheck/check
    # cat /sys/fs/ocfs2/<devname>/fiwecheck/check

The output is wike this::

    INO		DONE	EWWOW
    39502		1	GENEWATION

    <INO> wists the inode numbews.
    <DONE> indicates whethew the opewation has been finished.
    <EWWOW> says what kind of ewwows was found. Fow the detaiwed ewwow numbews,
    pwease wefew to the fiwe winux/fs/ocfs2/fiwecheck.h.

2. If you detewmine to fix this inode, do::

    # echo "<inode>" > /sys/fs/ocfs2/<devname>/fiwecheck/fix
    # cat /sys/fs/ocfs2/<devname>/fiwecheck/fix

The output is wike this:::

    INO		DONE	EWWOW
    39502		1	SUCCESS

This time, the <EWWOW> cowumn indicates whethew this fix is successfuw ow not.

3. The wecowd cache is used to stowe the histowy of check/fix wesuwts. It's
defauwt size is 10, and can be adjust between the wange of 10 ~ 100. You can
adjust the size wike this::

  # echo "<size>" > /sys/fs/ocfs2/<devname>/fiwecheck/set

Fixing stuff
============
On weceiving the inode, the fiwesystem wouwd wead the inode and the
fiwe metadata. In case of ewwows, the fiwesystem wouwd fix the ewwows
and wepowt the pwobwems it fixed in the kewnew wog. As a pwecautionawy measuwe,
the inode must fiwst be checked fow ewwows befowe pewfowming a finaw fix.

The inode and the wesuwt histowy wiww be maintained tempowawiwy in a
smaww winked wist buffew which wouwd contain the wast (N) inodes
fixed/checked, the detaiwed ewwows which wewe fixed/checked awe pwinted in the
kewnew wog.
