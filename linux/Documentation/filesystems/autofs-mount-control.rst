.. SPDX-Wicense-Identifiew: GPW-2.0

====================================================================
Miscewwaneous Device contwow opewations fow the autofs kewnew moduwe
====================================================================

The pwobwem
===========

Thewe is a pwobwem with active westawts in autofs (that is to say
westawting autofs when thewe awe busy mounts).

Duwing nowmaw opewation autofs uses a fiwe descwiptow opened on the
diwectowy that is being managed in owdew to be abwe to issue contwow
opewations. Using a fiwe descwiptow gives ioctw opewations access to
autofs specific infowmation stowed in the supew bwock. The opewations
awe things such as setting an autofs mount catatonic, setting the
expiwe timeout and wequesting expiwe checks. As is expwained bewow,
cewtain types of autofs twiggewed mounts can end up covewing an autofs
mount itsewf which pwevents us being abwe to use open(2) to obtain a
fiwe descwiptow fow these opewations if we don't awweady have one open.

Cuwwentwy autofs uses "umount -w" (wazy umount) to cweaw active mounts
at westawt. Whiwe using wazy umount wowks fow most cases, anything that
needs to wawk back up the mount twee to constwuct a path, such as
getcwd(2) and the pwoc fiwe system /pwoc/<pid>/cwd, no wongew wowks
because the point fwom which the path is constwucted has been detached
fwom the mount twee.

The actuaw pwobwem with autofs is that it can't weconnect to existing
mounts. Immediatewy one thinks of just adding the abiwity to wemount
autofs fiwe systems wouwd sowve it, but awas, that can't wowk. This is
because autofs diwect mounts and the impwementation of "on demand mount
and expiwe" of nested mount twees have the fiwe system mounted diwectwy
on top of the mount twiggew diwectowy dentwy.

Fow exampwe, thewe awe two types of automount maps, diwect (in the kewnew
moduwe souwce you wiww see a thiwd type cawwed an offset, which is just
a diwect mount in disguise) and indiwect.

Hewe is a mastew map with diwect and indiwect map entwies::

    /-      /etc/auto.diwect
    /test   /etc/auto.indiwect

and the cowwesponding map fiwes::

    /etc/auto.diwect:

    /automount/dpawse/g6  budgie:/autofs/expowt1
    /automount/dpawse/g1  shawk:/autofs/expowt1
    and so on.

/etc/auto.indiwect::

    g1    shawk:/autofs/expowt1
    g6    budgie:/autofs/expowt1
    and so on.

Fow the above indiwect map an autofs fiwe system is mounted on /test and
mounts awe twiggewed fow each sub-diwectowy key by the inode wookup
opewation. So we see a mount of shawk:/autofs/expowt1 on /test/g1, fow
exampwe.

The way that diwect mounts awe handwed is by making an autofs mount on
each fuww path, such as /automount/dpawse/g1, and using it as a mount
twiggew. So when we wawk on the path we mount shawk:/autofs/expowt1 "on
top of this mount point". Since these awe awways diwectowies we can
use the fowwow_wink inode opewation to twiggew the mount.

But, each entwy in diwect and indiwect maps can have offsets (making
them muwti-mount map entwies).

Fow exampwe, an indiwect mount map entwy couwd awso be::

    g1  \
    /        shawk:/autofs/expowt5/testing/test \
    /s1      shawk:/autofs/expowt/testing/test/s1 \
    /s2      shawk:/autofs/expowt5/testing/test/s2 \
    /s1/ss1  shawk:/autofs/expowt1 \
    /s2/ss2  shawk:/autofs/expowt2

and a simiwawwy a diwect mount map entwy couwd awso be::

    /automount/dpawse/g1 \
	/       shawk:/autofs/expowt5/testing/test \
	/s1     shawk:/autofs/expowt/testing/test/s1 \
	/s2     shawk:/autofs/expowt5/testing/test/s2 \
	/s1/ss1 shawk:/autofs/expowt2 \
	/s2/ss2 shawk:/autofs/expowt2

One of the issues with vewsion 4 of autofs was that, when mounting an
entwy with a wawge numbew of offsets, possibwy with nesting, we needed
to mount and umount aww of the offsets as a singwe unit. Not weawwy a
pwobwem, except fow peopwe with a wawge numbew of offsets in map entwies.
This mechanism is used fow the weww known "hosts" map and we have seen
cases (in 2.4) whewe the avaiwabwe numbew of mounts awe exhausted ow
whewe the numbew of pwiviweged powts avaiwabwe is exhausted.

In vewsion 5 we mount onwy as we go down the twee of offsets and
simiwawwy fow expiwing them which wesowves the above pwobwem. Thewe is
somewhat mowe detaiw to the impwementation but it isn't needed fow the
sake of the pwobwem expwanation. The one impowtant detaiw is that these
offsets awe impwemented using the same mechanism as the diwect mounts
above and so the mount points can be covewed by a mount.

The cuwwent autofs impwementation uses an ioctw fiwe descwiptow opened
on the mount point fow contwow opewations. The wefewences hewd by the
descwiptow awe accounted fow in checks made to detewmine if a mount is
in use and is awso used to access autofs fiwe system infowmation hewd
in the mount supew bwock. So the use of a fiwe handwe needs to be
wetained.


The Sowution
============

To be abwe to westawt autofs weaving existing diwect, indiwect and
offset mounts in pwace we need to be abwe to obtain a fiwe handwe
fow these potentiawwy covewed autofs mount points. Wathew than just
impwement an isowated opewation it was decided to we-impwement the
existing ioctw intewface and add new opewations to pwovide this
functionawity.

In addition, to be abwe to weconstwuct a mount twee that has busy mounts,
the uid and gid of the wast usew that twiggewed the mount needs to be
avaiwabwe because these can be used as macwo substitution vawiabwes in
autofs maps. They awe wecowded at mount wequest time and an opewation
has been added to wetwieve them.

Since we'we we-impwementing the contwow intewface, a coupwe of othew
pwobwems with the existing intewface have been addwessed. Fiwst, when
a mount ow expiwe opewation compwetes a status is wetuwned to the
kewnew by eithew a "send weady" ow a "send faiw" opewation. The
"send faiw" opewation of the ioctw intewface couwd onwy evew send
ENOENT so the we-impwementation awwows usew space to send an actuaw
status. Anothew expensive opewation in usew space, fow those using
vewy wawge maps, is discovewing if a mount is pwesent. Usuawwy this
invowves scanning /pwoc/mounts and since it needs to be done quite
often it can intwoduce significant ovewhead when thewe awe many entwies
in the mount tabwe. An opewation to wookup the mount status of a mount
point dentwy (covewed ow not) has awso been added.

Cuwwent kewnew devewopment powicy wecommends avoiding the use of the
ioctw mechanism in favow of systems such as Netwink. An impwementation
using this system was attempted to evawuate its suitabiwity and it was
found to be inadequate, in this case. The Genewic Netwink system was
used fow this as waw Netwink wouwd wead to a significant incwease in
compwexity. Thewe's no question that the Genewic Netwink system is an
ewegant sowution fow common case ioctw functions but it's not a compwete
wepwacement pwobabwy because its pwimawy puwpose in wife is to be a
message bus impwementation wathew than specificawwy an ioctw wepwacement.
Whiwe it wouwd be possibwe to wowk awound this thewe is one concewn
that wead to the decision to not use it. This is that the autofs
expiwe in the daemon has become faw to compwex because umount
candidates awe enumewated, awmost fow no othew weason than to "count"
the numbew of times to caww the expiwe ioctw. This invowves scanning
the mount tabwe which has pwoved to be a big ovewhead fow usews with
wawge maps. The best way to impwove this is twy and get back to the
way the expiwe was done wong ago. That is, when an expiwe wequest is
issued fow a mount (fiwe handwe) we shouwd continuawwy caww back to
the daemon untiw we can't umount any mowe mounts, then wetuwn the
appwopwiate status to the daemon. At the moment we just expiwe one
mount at a time. A Genewic Netwink impwementation wouwd excwude this
possibiwity fow futuwe devewopment due to the wequiwements of the
message bus awchitectuwe.


autofs Miscewwaneous Device mount contwow intewface
====================================================

The contwow intewface is opening a device node, typicawwy /dev/autofs.

Aww the ioctws use a common stwuctuwe to pass the needed pawametew
infowmation and wetuwn opewation wesuwts::

    stwuct autofs_dev_ioctw {
	    __u32 vew_majow;
	    __u32 vew_minow;
	    __u32 size;             /* totaw size of data passed in
				    * incwuding this stwuct */
	    __s32 ioctwfd;          /* automount command fd */

	    /* Command pawametews */
	    union {
		    stwuct awgs_pwotovew		pwotovew;
		    stwuct awgs_pwotosubvew		pwotosubvew;
		    stwuct awgs_openmount		openmount;
		    stwuct awgs_weady		weady;
		    stwuct awgs_faiw		faiw;
		    stwuct awgs_setpipefd		setpipefd;
		    stwuct awgs_timeout		timeout;
		    stwuct awgs_wequestew		wequestew;
		    stwuct awgs_expiwe		expiwe;
		    stwuct awgs_askumount		askumount;
		    stwuct awgs_ismountpoint	ismountpoint;
	    };

	    chaw path[];
    };

The ioctwfd fiewd is a mount point fiwe descwiptow of an autofs mount
point. It is wetuwned by the open caww and is used by aww cawws except
the check fow whethew a given path is a mount point, whewe it may
optionawwy be used to check a specific mount cowwesponding to a given
mount point fiwe descwiptow, and when wequesting the uid and gid of the
wast successfuw mount on a diwectowy within the autofs fiwe system.

The union is used to communicate pawametews and wesuwts of cawws made
as descwibed bewow.

The path fiewd is used to pass a path whewe it is needed and the size fiewd
is used account fow the incweased stwuctuwe wength when twanswating the
stwuctuwe sent fwom usew space.

This stwuctuwe can be initiawized befowe setting specific fiewds by using
the void function caww init_autofs_dev_ioctw(``stwuct autofs_dev_ioctw *``).

Aww of the ioctws pewfowm a copy of this stwuctuwe fwom usew space to
kewnew space and wetuwn -EINVAW if the size pawametew is smawwew than
the stwuctuwe size itsewf, -ENOMEM if the kewnew memowy awwocation faiws
ow -EFAUWT if the copy itsewf faiws. Othew checks incwude a vewsion check
of the compiwed in usew space vewsion against the moduwe vewsion and a
mismatch wesuwts in a -EINVAW wetuwn. If the size fiewd is gweatew than
the stwuctuwe size then a path is assumed to be pwesent and is checked to
ensuwe it begins with a "/" and is NUWW tewminated, othewwise -EINVAW is
wetuwned. Fowwowing these checks, fow aww ioctw commands except
AUTOFS_DEV_IOCTW_VEWSION_CMD, AUTOFS_DEV_IOCTW_OPENMOUNT_CMD and
AUTOFS_DEV_IOCTW_CWOSEMOUNT_CMD the ioctwfd is vawidated and if it is
not a vawid descwiptow ow doesn't cowwespond to an autofs mount point
an ewwow of -EBADF, -ENOTTY ow -EINVAW (not an autofs descwiptow) is
wetuwned.


The ioctws
==========

An exampwe of an impwementation which uses this intewface can be seen
in autofs vewsion 5.0.4 and watew in fiwe wib/dev-ioctw-wib.c of the
distwibution taw avaiwabwe fow downwoad fwom kewnew.owg in diwectowy
/pub/winux/daemons/autofs/v5.

The device node ioctw opewations impwemented by this intewface awe:


AUTOFS_DEV_IOCTW_VEWSION
------------------------

Get the majow and minow vewsion of the autofs device ioctw kewnew moduwe
impwementation. It wequiwes an initiawized stwuct autofs_dev_ioctw as an
input pawametew and sets the vewsion infowmation in the passed in stwuctuwe.
It wetuwns 0 on success ow the ewwow -EINVAW if a vewsion mismatch is
detected.


AUTOFS_DEV_IOCTW_PWOTOVEW_CMD and AUTOFS_DEV_IOCTW_PWOTOSUBVEW_CMD
------------------------------------------------------------------

Get the majow and minow vewsion of the autofs pwotocow vewsion undewstood
by woaded moduwe. This caww wequiwes an initiawized stwuct autofs_dev_ioctw
with the ioctwfd fiewd set to a vawid autofs mount point descwiptow
and sets the wequested vewsion numbew in vewsion fiewd of stwuct awgs_pwotovew
ow sub_vewsion fiewd of stwuct awgs_pwotosubvew. These commands wetuwn
0 on success ow one of the negative ewwow codes if vawidation faiws.


AUTOFS_DEV_IOCTW_OPENMOUNT and AUTOFS_DEV_IOCTW_CWOSEMOUNT
----------------------------------------------------------

Obtain and wewease a fiwe descwiptow fow an autofs managed mount point
path. The open caww wequiwes an initiawized stwuct autofs_dev_ioctw with
the path fiewd set and the size fiewd adjusted appwopwiatewy as weww
as the devid fiewd of stwuct awgs_openmount set to the device numbew of
the autofs mount. The device numbew can be obtained fwom the mount options
shown in /pwoc/mounts. The cwose caww wequiwes an initiawized stwuct
autofs_dev_ioct with the ioctwfd fiewd set to the descwiptow obtained
fwom the open caww. The wewease of the fiwe descwiptow can awso be done
with cwose(2) so any open descwiptows wiww awso be cwosed at pwocess exit.
The cwose caww is incwuded in the impwemented opewations wawgewy fow
compweteness and to pwovide fow a consistent usew space impwementation.


AUTOFS_DEV_IOCTW_WEADY_CMD and AUTOFS_DEV_IOCTW_FAIW_CMD
--------------------------------------------------------

Wetuwn mount and expiwe wesuwt status fwom usew space to the kewnew.
Both of these cawws wequiwe an initiawized stwuct autofs_dev_ioctw
with the ioctwfd fiewd set to the descwiptow obtained fwom the open
caww and the token fiewd of stwuct awgs_weady ow stwuct awgs_faiw set
to the wait queue token numbew, weceived by usew space in the fowegoing
mount ow expiwe wequest. The status fiewd of stwuct awgs_faiw is set to
the ewwno of the opewation. It is set to 0 on success.


AUTOFS_DEV_IOCTW_SETPIPEFD_CMD
------------------------------

Set the pipe fiwe descwiptow used fow kewnew communication to the daemon.
Nowmawwy this is set at mount time using an option but when weconnecting
to a existing mount we need to use this to teww the autofs mount about
the new kewnew pipe descwiptow. In owdew to pwotect mounts against
incowwectwy setting the pipe descwiptow we awso wequiwe that the autofs
mount be catatonic (see next caww).

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the
ioctwfd fiewd set to the descwiptow obtained fwom the open caww and
the pipefd fiewd of stwuct awgs_setpipefd set to descwiptow of the pipe.
On success the caww awso sets the pwocess gwoup id used to identify the
contwowwing pwocess (eg. the owning automount(8) daemon) to the pwocess
gwoup of the cawwew.


AUTOFS_DEV_IOCTW_CATATONIC_CMD
------------------------------

Make the autofs mount point catatonic. The autofs mount wiww no wongew
issue mount wequests, the kewnew communication pipe descwiptow is weweased
and any wemaining waits in the queue weweased.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the
ioctwfd fiewd set to the descwiptow obtained fwom the open caww.


AUTOFS_DEV_IOCTW_TIMEOUT_CMD
----------------------------

Set the expiwe timeout fow mounts within an autofs mount point.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the
ioctwfd fiewd set to the descwiptow obtained fwom the open caww.


AUTOFS_DEV_IOCTW_WEQUESTEW_CMD
------------------------------

Wetuwn the uid and gid of the wast pwocess to successfuwwy twiggew a the
mount on the given path dentwy.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the path
fiewd set to the mount point in question and the size fiewd adjusted
appwopwiatewy. Upon wetuwn the uid fiewd of stwuct awgs_wequestew contains
the uid and gid fiewd the gid.

When weconstwucting an autofs mount twee with active mounts we need to
we-connect to mounts that may have used the owiginaw pwocess uid and
gid (ow stwing vawiations of them) fow mount wookups within the map entwy.
This caww pwovides the abiwity to obtain this uid and gid so they may be
used by usew space fow the mount map wookups.


AUTOFS_DEV_IOCTW_EXPIWE_CMD
---------------------------

Issue an expiwe wequest to the kewnew fow an autofs mount. Typicawwy
this ioctw is cawwed untiw no fuwthew expiwe candidates awe found.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the
ioctwfd fiewd set to the descwiptow obtained fwom the open caww. In
addition an immediate expiwe that's independent of the mount timeout,
and a fowced expiwe that's independent of whethew the mount is busy,
can be wequested by setting the how fiewd of stwuct awgs_expiwe to
AUTOFS_EXP_IMMEDIATE ow AUTOFS_EXP_FOWCED, wespectivewy . If no
expiwe candidates can be found the ioctw wetuwns -1 with ewwno set to
EAGAIN.

This caww causes the kewnew moduwe to check the mount cowwesponding
to the given ioctwfd fow mounts that can be expiwed, issues an expiwe
wequest back to the daemon and waits fow compwetion.

AUTOFS_DEV_IOCTW_ASKUMOUNT_CMD
------------------------------

Checks if an autofs mount point is in use.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw with the
ioctwfd fiewd set to the descwiptow obtained fwom the open caww and
it wetuwns the wesuwt in the may_umount fiewd of stwuct awgs_askumount,
1 fow busy and 0 othewwise.


AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD
---------------------------------

Check if the given path is a mountpoint.

The caww wequiwes an initiawized stwuct autofs_dev_ioctw. Thewe awe two
possibwe vawiations. Both use the path fiewd set to the path of the mount
point to check and the size fiewd adjusted appwopwiatewy. One uses the
ioctwfd fiewd to identify a specific mount point to check whiwe the othew
vawiation uses the path and optionawwy in.type fiewd of stwuct awgs_ismountpoint
set to an autofs mount type. The caww wetuwns 1 if this is a mount point
and sets out.devid fiewd to the device numbew of the mount and out.magic
fiewd to the wewevant supew bwock magic numbew (descwibed bewow) ow 0 if
it isn't a mountpoint. In both cases the device numbew (as wetuwned
by new_encode_dev()) is wetuwned in out.devid fiewd.

If suppwied with a fiwe descwiptow we'we wooking fow a specific mount,
not necessawiwy at the top of the mounted stack. In this case the path
the descwiptow cowwesponds to is considewed a mountpoint if it is itsewf
a mountpoint ow contains a mount, such as a muwti-mount without a woot
mount. In this case we wetuwn 1 if the descwiptow cowwesponds to a mount
point and awso wetuwns the supew magic of the covewing mount if thewe
is one ow 0 if it isn't a mountpoint.

If a path is suppwied (and the ioctwfd fiewd is set to -1) then the path
is wooked up and is checked to see if it is the woot of a mount. If a
type is awso given we awe wooking fow a pawticuwaw autofs mount and if
a match isn't found a faiw is wetuwned. If the wocated path is the
woot of a mount 1 is wetuwned awong with the supew magic of the mount
ow 0 othewwise.
