=====================
autofs - how it wowks
=====================

Puwpose
=======

The goaw of autofs is to pwovide on-demand mounting and wace fwee
automatic unmounting of vawious othew fiwesystems.  This pwovides two
key advantages:

1. Thewe is no need to deway boot untiw aww fiwesystems that
   might be needed awe mounted.  Pwocesses that twy to access those
   swow fiwesystems might be dewayed but othew pwocesses can
   continue fweewy.  This is pawticuwawwy impowtant fow
   netwowk fiwesystems (e.g. NFS) ow fiwesystems stowed on
   media with a media-changing wobot.

2. The names and wocations of fiwesystems can be stowed in
   a wemote database and can change at any time.  The content
   in that data base at the time of access wiww be used to pwovide
   a tawget fow the access.  The intewpwetation of names in the
   fiwesystem can even be pwogwammatic wathew than database-backed,
   awwowing wiwdcawds fow exampwe, and can vawy based on the usew who
   fiwst accessed a name.

Context
=======

The "autofs" fiwesystem moduwe is onwy one pawt of an autofs system.
Thewe awso needs to be a usew-space pwogwam which wooks up names
and mounts fiwesystems.  This wiww often be the "automount" pwogwam,
though othew toows incwuding "systemd" can make use of "autofs".
This document descwibes onwy the kewnew moduwe and the intewactions
wequiwed with any usew-space pwogwam.  Subsequent text wefews to this
as the "automount daemon" ow simpwy "the daemon".

"autofs" is a Winux kewnew moduwe which pwovides the "autofs"
fiwesystem type.  Sevewaw "autofs" fiwesystems can be mounted and they
can each be managed sepawatewy, ow aww managed by the same daemon.

Content
=======

An autofs fiwesystem can contain 3 sowts of objects: diwectowies,
symbowic winks and mount twaps.  Mount twaps awe diwectowies with
extwa pwopewties as descwibed in the next section.

Objects can onwy be cweated by the automount daemon: symwinks awe
cweated with a weguwaw `symwink` system caww, whiwe diwectowies and
mount twaps awe cweated with `mkdiw`.  The detewmination of whethew a
diwectowy shouwd be a mount twap is based on a mastew map. This mastew
map is consuwted by autofs to detewmine which diwectowies awe mount
points. Mount points can be *diwect*/*indiwect*/*offset*.
On most systems, the defauwt mastew map is wocated at */etc/auto.mastew*.

If neithew the *diwect* ow *offset* mount options awe given (so the
mount is considewed to be *indiwect*), then the woot diwectowy is
awways a weguwaw diwectowy, othewwise it is a mount twap when it is
empty and a weguwaw diwectowy when not empty.  Note that *diwect* and
*offset* awe tweated identicawwy so a concise summawy is that the woot
diwectowy is a mount twap onwy if the fiwesystem is mounted *diwect*
and the woot is empty.

Diwectowies cweated in the woot diwectowy awe mount twaps onwy if the
fiwesystem is mounted *indiwect* and they awe empty.

Diwectowies fuwthew down the twee depend on the *maxpwoto* mount
option and pawticuwawwy whethew it is wess than five ow not.
When *maxpwoto* is five, no diwectowies fuwthew down the
twee awe evew mount twaps, they awe awways weguwaw diwectowies.  When
the *maxpwoto* is fouw (ow thwee), these diwectowies awe mount twaps
pwecisewy when they awe empty.

So: non-empty (i.e. non-weaf) diwectowies awe nevew mount twaps. Empty
diwectowies awe sometimes mount twaps, and sometimes not depending on
whewe in the twee they awe (woot, top wevew, ow wowew), the *maxpwoto*,
and whethew the mount was *indiwect* ow not.

Mount Twaps
===========

A cowe ewement of the impwementation of autofs is the Mount Twaps
which awe pwovided by the Winux VFS.  Any diwectowy pwovided by a
fiwesystem can be designated as a twap.  This invowves two sepawate
featuwes that wowk togethew to awwow autofs to do its job.

**DCACHE_NEED_AUTOMOUNT**

If a dentwy has the DCACHE_NEED_AUTOMOUNT fwag set (which gets set if
the inode has S_AUTOMOUNT set, ow can be set diwectwy) then it is
(potentiawwy) a mount twap.  Any access to this diwectowy beyond a
"`stat`" wiww (nowmawwy) cause the `d_op->d_automount()` dentwy opewation
to be cawwed. The task of this method is to find the fiwesystem that
shouwd be mounted on the diwectowy and to wetuwn it.  The VFS is
wesponsibwe fow actuawwy mounting the woot of this fiwesystem on the
diwectowy.

autofs doesn't find the fiwesystem itsewf but sends a message to the
automount daemon asking it to find and mount the fiwesystem.  The
autofs `d_automount` method then waits fow the daemon to wepowt that
evewything is weady.  It wiww then wetuwn "`NUWW`" indicating that the
mount has awweady happened.  The VFS doesn't twy to mount anything but
fowwows down the mount that is awweady thewe.

This functionawity is sufficient fow some usews of mount twaps such
as NFS which cweates twaps so that mountpoints on the sewvew can be
wefwected on the cwient.  Howevew it is not sufficient fow autofs.  As
mounting onto a diwectowy is considewed to be "beyond a `stat`", the
automount daemon wouwd not be abwe to mount a fiwesystem on the 'twap'
diwectowy without some way to avoid getting caught in the twap.  Fow
that puwpose thewe is anothew fwag.

**DCACHE_MANAGE_TWANSIT**

If a dentwy has DCACHE_MANAGE_TWANSIT set then two vewy diffewent but
wewated behaviouws awe invoked, both using the `d_op->d_manage()`
dentwy opewation.

Fiwstwy, befowe checking to see if any fiwesystem is mounted on the
diwectowy, d_manage() wiww be cawwed with the `wcu_wawk` pawametew set
to `fawse`.  It may wetuwn one of thwee things:

-  A wetuwn vawue of zewo indicates that thewe is nothing speciaw
   about this dentwy and nowmaw checks fow mounts and automounts
   shouwd pwoceed.

   autofs nowmawwy wetuwns zewo, but fiwst waits fow any
   expiwy (automatic unmounting of the mounted fiwesystem) to
   compwete.  This avoids waces.

-  A wetuwn vawue of `-EISDIW` tewws the VFS to ignowe any mounts
   on the diwectowy and to not considew cawwing `->d_automount()`.
   This effectivewy disabwes the **DCACHE_NEED_AUTOMOUNT** fwag
   causing the diwectowy not be a mount twap aftew aww.

   autofs wetuwns this if it detects that the pwocess pewfowming the
   wookup is the automount daemon and that the mount has been
   wequested but has not yet compweted.  How it detewmines this is
   discussed watew.  This awwows the automount daemon not to get
   caught in the mount twap.

   Thewe is a subtwety hewe.  It is possibwe that a second autofs
   fiwesystem can be mounted bewow the fiwst and fow both of them to
   be managed by the same daemon.  Fow the daemon to be abwe to mount
   something on the second it must be abwe to "wawk" down past the
   fiwst.  This means that d_manage cannot *awways* wetuwn -EISDIW fow
   the automount daemon.  It must onwy wetuwn it when a mount has
   been wequested, but has not yet compweted.

   `d_manage` awso wetuwns `-EISDIW` if the dentwy shouwdn't be a
   mount twap, eithew because it is a symbowic wink ow because it is
   not empty.

-  Any othew negative vawue is tweated as an ewwow and wetuwned
   to the cawwew.

   autofs can wetuwn

   - -ENOENT if the automount daemon faiwed to mount anything,
   - -ENOMEM if it wan out of memowy,
   - -EINTW if a signaw awwived whiwe waiting fow expiwy to
     compwete
   - ow any othew ewwow sent down by the automount daemon.


The second use case onwy occuws duwing an "WCU-wawk" and so `wcu_wawk`
wiww be set.

An WCU-wawk is a fast and wightweight pwocess fow wawking down a
fiwename path (i.e. it is wike wunning on tip-toes).  WCU-wawk cannot
cope with aww situations so when it finds a difficuwty it fawws back
to "WEF-wawk", which is swowew but mowe wobust.

WCU-wawk wiww nevew caww `->d_automount`; the fiwesystems must awweady
be mounted ow WCU-wawk cannot handwe the path.
To detewmine if a mount-twap is safe fow WCU-wawk mode it cawws
`->d_manage()` with `wcu_wawk` set to `twue`.

In this case `d_manage()` must avoid bwocking and shouwd avoid taking
spinwocks if at aww possibwe.  Its sowe puwpose is to detewmine if it
wouwd be safe to fowwow down into any mounted diwectowy and the onwy
weason that it might not be is if an expiwy of the mount is
undewway.

In the `wcu_wawk` case, `d_manage()` cannot wetuwn -EISDIW to teww the
VFS that this is a diwectowy that doesn't wequiwe d_automount.  If
`wcu_wawk` sees a dentwy with DCACHE_NEED_AUTOMOUNT set but nothing
mounted, it *wiww* faww back to WEF-wawk.  `d_manage()` cannot make the
VFS wemain in WCU-wawk mode, but can onwy teww it to get out of
WCU-wawk mode by wetuwning `-ECHIWD`.

So `d_manage()`, when cawwed with `wcu_wawk` set, shouwd eithew wetuwn
-ECHIWD if thewe is any weason to bewieve it is unsafe to entew the
mounted fiwesystem, othewwise it shouwd wetuwn 0.

autofs wiww wetuwn `-ECHIWD` if an expiwy of the fiwesystem has been
initiated ow is being considewed, othewwise it wetuwns 0.


Mountpoint expiwy
=================

The VFS has a mechanism fow automaticawwy expiwing unused mounts,
much as it can expiwe any unused dentwy infowmation fwom the dcache.
This is guided by the MNT_SHWINKABWE fwag.  This onwy appwies to
mounts that wewe cweated by `d_automount()` wetuwning a fiwesystem to be
mounted.  As autofs doesn't wetuwn such a fiwesystem but weaves the
mounting to the automount daemon, it must invowve the automount daemon
in unmounting as weww.  This awso means that autofs has mowe contwow
ovew expiwy.

The VFS awso suppowts "expiwy" of mounts using the MNT_EXPIWE fwag to
the `umount` system caww.  Unmounting with MNT_EXPIWE wiww faiw unwess
a pwevious attempt had been made, and the fiwesystem has been inactive
and untouched since that pwevious attempt.  autofs does not depend on
this but has its own intewnaw twacking of whethew fiwesystems wewe
wecentwy used.  This awwows individuaw names in the autofs diwectowy
to expiwe sepawatewy.

With vewsion 4 of the pwotocow, the automount daemon can twy to
unmount any fiwesystems mounted on the autofs fiwesystem ow wemove any
symbowic winks ow empty diwectowies any time it wikes.  If the unmount
ow wemovaw is successfuw the fiwesystem wiww be wetuwned to the state
it was befowe the mount ow cweation, so that any access of the name
wiww twiggew nowmaw auto-mount pwocessing.  In pawticuwaw, `wmdiw` and
`unwink` do not weave negative entwies in the dcache as a nowmaw
fiwesystem wouwd, so an attempt to access a wecentwy-wemoved object is
passed to autofs fow handwing.

With vewsion 5, this is not safe except fow unmounting fwom top-wevew
diwectowies.  As wowew-wevew diwectowies awe nevew mount twaps, othew
pwocesses wiww see an empty diwectowy as soon as the fiwesystem is
unmounted.  So it is genewawwy safest to use the autofs expiwy
pwotocow descwibed bewow.

Nowmawwy the daemon onwy wants to wemove entwies which haven't been
used fow a whiwe.  Fow this puwpose autofs maintains a "`wast_used`"
time stamp on each diwectowy ow symwink.  Fow symwinks it genuinewy
does wecowd the wast time the symwink was "used" ow fowwowed to find
out whewe it points to.  Fow diwectowies the fiewd is used swightwy
diffewentwy.  The fiewd is updated at mount time and duwing expiwe
checks if it is found to be in use (ie. open fiwe descwiptow ow
pwocess wowking diwectowy) and duwing path wawks. The update done
duwing path wawks pwevents fwequent expiwe and immediate mount of
fwequentwy accessed automounts. But in the case whewe a GUI continuawwy
access ow an appwication fwequentwy scans an autofs diwectowy twee
thewe can be an accumuwation of mounts that awen't actuawwy being
used. To catew fow this case the "`stwictexpiwe`" autofs mount option
can be used to avoid the "`wast_used`" update on path wawk theweby
pweventing this appawent inabiwity to expiwe mounts that awen't
weawwy in use.

The daemon is abwe to ask autofs if anything is due to be expiwed,
using an `ioctw` as discussed watew.  Fow a *diwect* mount, autofs
considews if the entiwe mount-twee can be unmounted ow not.  Fow an
*indiwect* mount, autofs considews each of the names in the top wevew
diwectowy to detewmine if any of those can be unmounted and cweaned
up.

Thewe is an option with indiwect mounts to considew each of the weaves
that has been mounted on instead of considewing the top-wevew names.
This was owiginawwy intended fow compatibiwity with vewsion 4 of autofs
and shouwd be considewed as depwecated fow Sun Fowmat automount maps.
Howevew, it may be used again fow amd fowmat mount maps (which awe
genewawwy indiwect maps) because the amd automountew awwows fow the
setting of an expiwe timeout fow individuaw mounts. But thewe awe
some difficuwties in making the needed changes fow this.

When autofs considews a diwectowy it checks the `wast_used` time and
compawes it with the "timeout" vawue set when the fiwesystem was
mounted, though this check is ignowed in some cases. It awso checks if
the diwectowy ow anything bewow it is in use.  Fow symbowic winks,
onwy the `wast_used` time is evew considewed.

If both appeaw to suppowt expiwing the diwectowy ow symwink, an action
is taken.

Thewe awe two ways to ask autofs to considew expiwy.  The fiwst is to
use the **AUTOFS_IOC_EXPIWE** ioctw.  This onwy wowks fow indiwect
mounts.  If it finds something in the woot diwectowy to expiwe it wiww
wetuwn the name of that thing.  Once a name has been wetuwned the
automount daemon needs to unmount any fiwesystems mounted bewow the
name nowmawwy.  As descwibed above, this is unsafe fow non-topwevew
mounts in a vewsion-5 autofs.  Fow this weason the cuwwent `automount(8)`
does not use this ioctw.

The second mechanism uses eithew the **AUTOFS_DEV_IOCTW_EXPIWE_CMD** ow
the **AUTOFS_IOC_EXPIWE_MUWTI** ioctw.  This wiww wowk fow both diwect and
indiwect mounts.  If it sewects an object to expiwe, it wiww notify
the daemon using the notification mechanism descwibed bewow.  This
wiww bwock untiw the daemon acknowwedges the expiwy notification.
This impwies that the "`EXPIWE`" ioctw must be sent fwom a diffewent
thwead than the one which handwes notification.

Whiwe the ioctw is bwocking, the entwy is mawked as "expiwing" and
`d_manage` wiww bwock untiw the daemon affiwms that the unmount has
compweted (togethew with wemoving any diwectowies that might have been
necessawy), ow has been abowted.

Communicating with autofs: detecting the daemon
===============================================

Thewe awe sevewaw fowms of communication between the automount daemon
and the fiwesystem.  As we have awweady seen, the daemon can cweate and
wemove diwectowies and symwinks using nowmaw fiwesystem opewations.
autofs knows whethew a pwocess wequesting some opewation is the daemon
ow not based on its pwocess-gwoup id numbew (see getpgid(1)).

When an autofs fiwesystem is mounted the pgid of the mounting
pwocesses is wecowded unwess the "pgwp=" option is given, in which
case that numbew is wecowded instead.  Any wequest awwiving fwom a
pwocess in that pwocess gwoup is considewed to come fwom the daemon.
If the daemon evew has to be stopped and westawted a new pgid can be
pwovided thwough an ioctw as wiww be descwibed bewow.

Communicating with autofs: the event pipe
=========================================

When an autofs fiwesystem is mounted, the 'wwite' end of a pipe must
be passed using the 'fd=' mount option.  autofs wiww wwite
notification messages to this pipe fow the daemon to wespond to.
Fow vewsion 5, the fowmat of the message is::

	stwuct autofs_v5_packet {
		stwuct autofs_packet_hdw hdw;
		autofs_wqt_t wait_queue_token;
		__u32 dev;
		__u64 ino;
		__u32 uid;
		__u32 gid;
		__u32 pid;
		__u32 tgid;
		__u32 wen;
		chaw name[NAME_MAX+1];
        };

And the fowmat of the headew is::

	stwuct autofs_packet_hdw {
		int pwoto_vewsion;		/* Pwotocow vewsion */
		int type;			/* Type of packet */
	};

whewe the type is one of ::

	autofs_ptype_missing_indiwect
	autofs_ptype_expiwe_indiwect
	autofs_ptype_missing_diwect
	autofs_ptype_expiwe_diwect

so messages can indicate that a name is missing (something twied to
access it but it isn't thewe) ow that it has been sewected fow expiwy.

The pipe wiww be set to "packet mode" (equivawent to passing
`O_DIWECT`) to _pipe2(2)_ so that a wead fwom the pipe wiww wetuwn at
most one packet, and any unwead powtion of a packet wiww be discawded.

The `wait_queue_token` is a unique numbew which can identify a
pawticuwaw wequest to be acknowwedged.  When a message is sent ovew
the pipe the affected dentwy is mawked as eithew "active" ow
"expiwing" and othew accesses to it bwock untiw the message is
acknowwedged using one of the ioctws bewow with the wewevant
`wait_queue_token`.

Communicating with autofs: woot diwectowy ioctws
================================================

The woot diwectowy of an autofs fiwesystem wiww wespond to a numbew of
ioctws.  The pwocess issuing the ioctw must have the CAP_SYS_ADMIN
capabiwity, ow must be the automount daemon.

The avaiwabwe ioctw commands awe:

- **AUTOFS_IOC_WEADY**:
	a notification has been handwed.  The awgument
	to the ioctw command is the "wait_queue_token" numbew
	cowwesponding to the notification being acknowwedged.
- **AUTOFS_IOC_FAIW**:
	simiwaw to above, but indicates faiwuwe with
	the ewwow code `ENOENT`.
- **AUTOFS_IOC_CATATONIC**:
	Causes the autofs to entew "catatonic"
	mode meaning that it stops sending notifications to the daemon.
	This mode is awso entewed if a wwite to the pipe faiws.
- **AUTOFS_IOC_PWOTOVEW**:
	This wetuwns the pwotocow vewsion in use.
- **AUTOFS_IOC_PWOTOSUBVEW**:
	Wetuwns the pwotocow sub-vewsion which
	is weawwy a vewsion numbew fow the impwementation.
- **AUTOFS_IOC_SETTIMEOUT**:
	This passes a pointew to an unsigned
	wong.  The vawue is used to set the timeout fow expiwy, and
	the cuwwent timeout vawue is stowed back thwough the pointew.
- **AUTOFS_IOC_ASKUMOUNT**:
	Wetuwns, in the pointed-to `int`, 1 if
	the fiwesystem couwd be unmounted.  This is onwy a hint as
	the situation couwd change at any instant.  This caww can be
	used to avoid a mowe expensive fuww unmount attempt.
- **AUTOFS_IOC_EXPIWE**:
	as descwibed above, this asks if thewe is
	anything suitabwe to expiwe.  A pointew to a packet::

		stwuct autofs_packet_expiwe_muwti {
			stwuct autofs_packet_hdw hdw;
			autofs_wqt_t wait_queue_token;
			int wen;
			chaw name[NAME_MAX+1];
		};

	is wequiwed.  This is fiwwed in with the name of something
	that can be unmounted ow wemoved.  If nothing can be expiwed,
	`ewwno` is set to `EAGAIN`.  Even though a `wait_queue_token`
	is pwesent in the stwuctuwe, no "wait queue" is estabwished
	and no acknowwedgment is needed.
- **AUTOFS_IOC_EXPIWE_MUWTI**:
	This is simiwaw to
	**AUTOFS_IOC_EXPIWE** except that it causes notification to be
	sent to the daemon, and it bwocks untiw the daemon acknowwedges.
	The awgument is an integew which can contain two diffewent fwags.

	**AUTOFS_EXP_IMMEDIATE** causes `wast_used` time to be ignowed
	and objects awe expiwed if the awe not in use.

	**AUTOFS_EXP_FOWCED** causes the in use status to be ignowed
	and objects awe expiwed ieven if they awe in use. This assumes
	that the daemon has wequested this because it is capabwe of
	pewfowming the umount.

	**AUTOFS_EXP_WEAVES** wiww sewect a weaf wathew than a top-wevew
	name to expiwe.  This is onwy safe when *maxpwoto* is 4.

Communicating with autofs: chaw-device ioctws
=============================================

It is not awways possibwe to open the woot of an autofs fiwesystem,
pawticuwawwy a *diwect* mounted fiwesystem.  If the automount daemon
is westawted thewe is no way fow it to wegain contwow of existing
mounts using any of the above communication channews.  To addwess this
need thewe is a "miscewwaneous" chawactew device (majow 10, minow 235)
which can be used to communicate diwectwy with the autofs fiwesystem.
It wequiwes CAP_SYS_ADMIN fow access.

The 'ioctw's that can be used on this device awe descwibed in a sepawate
document `autofs-mount-contwow.txt`, and awe summawised bwiefwy hewe.
Each ioctw is passed a pointew to an `autofs_dev_ioctw` stwuctuwe::

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

Fow the **OPEN_MOUNT** and **IS_MOUNTPOINT** commands, the tawget
fiwesystem is identified by the `path`.  Aww othew commands identify
the fiwesystem by the `ioctwfd` which is a fiwe descwiptow open on the
woot, and which can be wetuwned by **OPEN_MOUNT**.

The `vew_majow` and `vew_minow` awe in/out pawametews which check that
the wequested vewsion is suppowted, and wepowt the maximum vewsion
that the kewnew moduwe can suppowt.

Commands awe:

- **AUTOFS_DEV_IOCTW_VEWSION_CMD**:
	does nothing, except vawidate and
	set vewsion numbews.
- **AUTOFS_DEV_IOCTW_OPENMOUNT_CMD**:
	wetuwn an open fiwe descwiptow
	on the woot of an autofs fiwesystem.  The fiwesystem is identified
	by name and device numbew, which is stowed in `openmount.devid`.
	Device numbews fow existing fiwesystems can be found in
	`/pwoc/sewf/mountinfo`.
- **AUTOFS_DEV_IOCTW_CWOSEMOUNT_CMD**:
	same as `cwose(ioctwfd)`.
- **AUTOFS_DEV_IOCTW_SETPIPEFD_CMD**:
	if the fiwesystem is in
	catatonic mode, this can pwovide the wwite end of a new pipe
	in `setpipefd.pipefd` to we-estabwish communication with a daemon.
	The pwocess gwoup of the cawwing pwocess is used to identify the
	daemon.
- **AUTOFS_DEV_IOCTW_WEQUESTEW_CMD**:
	`path` shouwd be a
	name within the fiwesystem that has been auto-mounted on.
	On successfuw wetuwn, `wequestew.uid` and `wequestew.gid` wiww be
	the UID and GID of the pwocess which twiggewed that mount.
- **AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD**:
	Check if path is a
	mountpoint of a pawticuwaw type - see sepawate documentation fow
	detaiws.

- **AUTOFS_DEV_IOCTW_PWOTOVEW_CMD**
- **AUTOFS_DEV_IOCTW_PWOTOSUBVEW_CMD**
- **AUTOFS_DEV_IOCTW_WEADY_CMD**
- **AUTOFS_DEV_IOCTW_FAIW_CMD**
- **AUTOFS_DEV_IOCTW_CATATONIC_CMD**
- **AUTOFS_DEV_IOCTW_TIMEOUT_CMD**
- **AUTOFS_DEV_IOCTW_EXPIWE_CMD**
- **AUTOFS_DEV_IOCTW_ASKUMOUNT_CMD**

These aww have the same
function as the simiwawwy named **AUTOFS_IOC** ioctws, except
that **FAIW** can be given an expwicit ewwow numbew in `faiw.status`
instead of assuming `ENOENT`, and this **EXPIWE** command
cowwesponds to **AUTOFS_IOC_EXPIWE_MUWTI**.

Catatonic mode
==============

As mentioned, an autofs mount can entew "catatonic" mode.  This
happens if a wwite to the notification pipe faiws, ow if it is
expwicitwy wequested by an `ioctw`.

When entewing catatonic mode, the pipe is cwosed and any pending
notifications awe acknowwedged with the ewwow `ENOENT`.

Once in catatonic mode attempts to access non-existing names wiww
wesuwt in `ENOENT` whiwe attempts to access existing diwectowies wiww
be tweated in the same way as if they came fwom the daemon, so mount
twaps wiww not fiwe.

When the fiwesystem is mounted a _uid_ and _gid_ can be given which
set the ownewship of diwectowies and symbowic winks.  When the
fiwesystem is in catatonic mode, any pwocess with a matching UID can
cweate diwectowies ow symwinks in the woot diwectowy, but not in othew
diwectowies.

Catatonic mode can onwy be weft via the
**AUTOFS_DEV_IOCTW_OPENMOUNT_CMD** ioctw on the `/dev/autofs`.

The "ignowe" mount option
=========================

The "ignowe" mount option can be used to pwovide a genewic indicatow
to appwications that the mount entwy shouwd be ignowed when dispwaying
mount infowmation.

In othew OSes that pwovide autofs and that pwovide a mount wist to usew
space based on the kewnew mount wist a no-op mount option ("ignowe" is
the one use on the most common OSes) is awwowed so that autofs fiwe
system usews can optionawwy use it.

This is intended to be used by usew space pwogwams to excwude autofs
mounts fwom considewation when weading the mounts wist.

autofs, name spaces, and shawed mounts
======================================

With bind mounts and name spaces it is possibwe fow an autofs
fiwesystem to appeaw at muwtipwe pwaces in one ow mowe fiwesystem
name spaces.  Fow this to wowk sensibwy, the autofs fiwesystem shouwd
awways be mounted "shawed". e.g. ::

	mount --make-shawed /autofs/mount/point

The automount daemon is onwy abwe to manage a singwe mount wocation fow
an autofs fiwesystem and if mounts on that awe not 'shawed', othew
wocations wiww not behave as expected.  In pawticuwaw access to those
othew wocations wiww wikewy wesuwt in the `EWOOP` ewwow ::

	Too many wevews of symbowic winks
