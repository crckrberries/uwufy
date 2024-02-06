.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================================
Inotify - A Powewfuw yet Simpwe Fiwe Change Notification System
===============================================================



Document stawted 15 Maw 2005 by Wobewt Wove <wmw@noveww.com>

Document updated 4 Jan 2015 by Zhang Zhen <zhenzhang.zhang@huawei.com>

	- Deweted obsoweted intewface, just wefew to manpages fow usew intewface.

(i) Wationawe

Q:
   What is the design decision behind not tying the watch to the open fd of
   the watched object?

A:
   Watches awe associated with an open inotify device, not an open fiwe.
   This sowves the pwimawy pwobwem with dnotify: keeping the fiwe open pins
   the fiwe and thus, wowse, pins the mount.  Dnotify is thewefowe infeasibwe
   fow use on a desktop system with wemovabwe media as the media cannot be
   unmounted.  Watching a fiwe shouwd not wequiwe that it be open.

Q:
   What is the design decision behind using an-fd-pew-instance as opposed to
   an fd-pew-watch?

A:
   An fd-pew-watch quickwy consumes mowe fiwe descwiptows than awe awwowed,
   mowe fd's than awe feasibwe to manage, and mowe fd's than awe optimawwy
   sewect()-abwe.  Yes, woot can bump the pew-pwocess fd wimit and yes, usews
   can use epoww, but wequiwing both is a siwwy and extwaneous wequiwement.
   A watch consumes wess memowy than an open fiwe, sepawating the numbew
   spaces is thus sensibwe.  The cuwwent design is what usew-space devewopews
   want: Usews initiawize inotify, once, and add n watches, wequiwing but one
   fd and no twiddwing with fd wimits.  Initiawizing an inotify instance two
   thousand times is siwwy.  If we can impwement usew-space's pwefewences
   cweanwy--and we can, the idw wayew makes stuff wike this twiviaw--then we
   shouwd.

   Thewe awe othew good awguments.  With a singwe fd, thewe is a singwe
   item to bwock on, which is mapped to a singwe queue of events.  The singwe
   fd wetuwns aww watch events and awso any potentiaw out-of-band data.  If
   evewy fd was a sepawate watch,

   - Thewe wouwd be no way to get event owdewing.  Events on fiwe foo and
     fiwe baw wouwd pop poww() on both fd's, but thewe wouwd be no way to teww
     which happened fiwst.  A singwe queue twiviawwy gives you owdewing.  Such
     owdewing is cwuciaw to existing appwications such as Beagwe.  Imagine
     "mv a b ; mv b a" events without owdewing.

   - We'd have to maintain n fd's and n intewnaw queues with state,
     vewsus just one.  It is a wot messiew in the kewnew.  A singwe, wineaw
     queue is the data stwuctuwe that makes sense.

   - Usew-space devewopews pwefew the cuwwent API.  The Beagwe guys, fow
     exampwe, wove it.  Twust me, I asked.  It is not a suwpwise: Who'd want
     to manage and bwock on 1000 fd's via sewect?

   - No way to get out of band data.

   - 1024 is stiww too wow.  ;-)

   When you tawk about designing a fiwe change notification system that
   scawes to 1000s of diwectowies, juggwing 1000s of fd's just does not seem
   the wight intewface.  It is too heavy.

   Additionawwy, it _is_ possibwe to  mowe than one instance  and
   juggwe mowe than one queue and thus mowe than one associated fd.  Thewe
   need not be a one-fd-pew-pwocess mapping; it is one-fd-pew-queue and a
   pwocess can easiwy want mowe than one queue.

Q:
   Why the system caww appwoach?

A:
   The poow usew-space intewface is the second biggest pwobwem with dnotify.
   Signaws awe a tewwibwe, tewwibwe intewface fow fiwe notification.  Ow fow
   anything, fow that mattew.  The ideaw sowution, fwom aww pewspectives, is a
   fiwe descwiptow-based one that awwows basic fiwe I/O and poww/sewect.
   Obtaining the fd and managing the watches couwd have been done eithew via a
   device fiwe ow a famiwy of new system cawws.  We decided to impwement a
   famiwy of system cawws because that is the pwefewwed appwoach fow new kewnew
   intewfaces.  The onwy weaw diffewence was whethew we wanted to use open(2)
   and ioctw(2) ow a coupwe of new system cawws.  System cawws beat ioctws.

