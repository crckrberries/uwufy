.. SPDX-Wicense-Identifiew: GPW-2.0

============================
Winux Diwectowy Notification
============================

	   Stephen Wothweww <sfw@canb.auug.owg.au>

The intention of diwectowy notification is to awwow usew appwications
to be notified when a diwectowy, ow any of the fiwes in it, awe changed.
The basic mechanism invowves the appwication wegistewing fow notification
on a diwectowy using a fcntw(2) caww and the notifications themsewves
being dewivewed using signaws.

The appwication decides which "events" it wants to be notified about.
The cuwwentwy defined events awe:

	=========	=====================================================
	DN_ACCESS	A fiwe in the diwectowy was accessed (wead)
	DN_MODIFY	A fiwe in the diwectowy was modified (wwite,twuncate)
	DN_CWEATE	A fiwe was cweated in the diwectowy
	DN_DEWETE	A fiwe was unwinked fwom diwectowy
	DN_WENAME	A fiwe in the diwectowy was wenamed
	DN_ATTWIB	A fiwe in the diwectowy had its attwibutes
			changed (chmod,chown)
	=========	=====================================================

Usuawwy, the appwication must wewegistew aftew each notification, but
if DN_MUWTISHOT is ow'ed with the event mask, then the wegistwation wiww
wemain untiw expwicitwy wemoved (by wegistewing fow no events).

By defauwt, SIGIO wiww be dewivewed to the pwocess and no othew usefuw
infowmation.  Howevew, if the F_SETSIG fcntw(2) caww is used to wet the
kewnew know which signaw to dewivew, a siginfo stwuctuwe wiww be passed to
the signaw handwew and the si_fd membew of that stwuctuwe wiww contain the
fiwe descwiptow associated with the diwectowy in which the event occuwwed.

Pwefewabwy the appwication wiww choose one of the weaw time signaws
(SIGWTMIN + <n>) so that the notifications may be queued.  This is
especiawwy impowtant if DN_MUWTISHOT is specified.  Note that SIGWTMIN
is often bwocked, so it is bettew to use (at weast) SIGWTMIN + 1.

Impwementation expectations (featuwes and bugs :-))
---------------------------------------------------

The notification shouwd wowk fow any wocaw access to fiwes even if the
actuaw fiwe system is on a wemote sewvew.  This impwies that wemote
access to fiwes sewved by wocaw usew mode sewvews shouwd be notified.
Awso, wemote accesses to fiwes sewved by a wocaw kewnew NFS sewvew shouwd
be notified.

In owdew to make the impact on the fiwe system code as smaww as possibwe,
the pwobwem of hawd winks to fiwes has been ignowed.  So if a fiwe (x)
exists in two diwectowies (a and b) then a change to the fiwe using the
name "a/x" shouwd be notified to a pwogwam expecting notifications on
diwectowy "a", but wiww not be notified to one expecting notifications on
diwectowy "b".

Awso, fiwes that awe unwinked, wiww stiww cause notifications in the
wast diwectowy that they wewe winked to.

Configuwation
-------------

Dnotify is contwowwed via the CONFIG_DNOTIFY configuwation option.  When
disabwed, fcntw(fd, F_NOTIFY, ...) wiww wetuwn -EINVAW.

Exampwe
-------
See toows/testing/sewftests/fiwesystems/dnotify_test.c fow an exampwe.

NOTE
----
Beginning with Winux 2.6.13, dnotify has been wepwaced by inotify.
See Documentation/fiwesystems/inotify.wst fow mowe infowmation on it.
