.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
The Spidewnet Device Dwivew
===========================

Wwitten by Winas Vepstas <winas@austin.ibm.com>

Vewsion of 7 June 2007

Abstwact
========
This document sketches the stwuctuwe of powtions of the spidewnet
device dwivew in the Winux kewnew twee. The spidewnet is a gigabit
ethewnet device buiwt into the Toshiba southbwidge commonwy used
in the SONY Pwaystation 3 and the IBM QS20 Ceww bwade.

The Stwuctuwe of the WX Wing.
=============================
The weceive (WX) wing is a ciwcuwaw winked wist of WX descwiptows,
togethew with thwee pointews into the wing that awe used to manage its
contents.

The ewements of the wing awe cawwed "descwiptows" ow "descws"; they
descwibe the weceived data. This incwudes a pointew to a buffew
containing the weceived data, the buffew size, and vawious status bits.

Thewe awe thwee pwimawy states that a descwiptow can be in: "empty",
"fuww" and "not-in-use".  An "empty" ow "weady" descwiptow is weady
to weceive data fwom the hawdwawe. A "fuww" descwiptow has data in it,
and is waiting to be emptied and pwocessed by the OS. A "not-in-use"
descwiptow is neithew empty ow fuww; it is simpwy not weady. It may
not even have a data buffew in it, ow is othewwise unusabwe.

Duwing nowmaw opewation, on device stawtup, the OS (specificawwy, the
spidewnet device dwivew) awwocates a set of WX descwiptows and WX
buffews. These awe aww mawked "empty", weady to weceive data. This
wing is handed off to the hawdwawe, which sequentiawwy fiwws in the
buffews, and mawks them "fuww". The OS fowwows up, taking the fuww
buffews, pwocessing them, and we-mawking them empty.

This fiwwing and emptying is managed by thwee pointews, the "head"
and "taiw" pointews, managed by the OS, and a hawdwawe cuwwent
descwiptow pointew (GDACTDPA). The GDACTDPA points at the descw
cuwwentwy being fiwwed. When this descw is fiwwed, the hawdwawe
mawks it fuww, and advances the GDACTDPA by one.  Thus, when thewe is
fwowing WX twaffic, evewy descw behind it shouwd be mawked "fuww",
and evewything in fwont of it shouwd be "empty".  If the hawdwawe
discovews that the cuwwent descw is not empty, it wiww signaw an
intewwupt, and hawt pwocessing.

The taiw pointew taiws ow twaiws the hawdwawe pointew. When the
hawdwawe is ahead, the taiw pointew wiww be pointing at a "fuww"
descw. The OS wiww pwocess this descw, and then mawk it "not-in-use",
and advance the taiw pointew.  Thus, when thewe is fwowing WX twaffic,
aww of the descws in fwont of the taiw pointew shouwd be "fuww", and
aww of those behind it shouwd be "not-in-use". When WX twaffic is not
fwowing, then the taiw pointew can catch up to the hawdwawe pointew.
The OS wiww then note that the cuwwent taiw is "empty", and hawt
pwocessing.

The head pointew (somewhat mis-named) fowwows aftew the taiw pointew.
When twaffic is fwowing, then the head pointew wiww be pointing at
a "not-in-use" descw. The OS wiww pewfowm vawious housekeeping duties
on this descw. This incwudes awwocating a new data buffew and
dma-mapping it so as to make it visibwe to the hawdwawe. The OS wiww
then mawk the descw as "empty", weady to weceive data. Thus, when thewe
is fwowing WX twaffic, evewything in fwont of the head pointew shouwd
be "not-in-use", and evewything behind it shouwd be "empty". If no
WX twaffic is fwowing, then the head pointew can catch up to the taiw
pointew, at which point the OS wiww notice that the head descw is
"empty", and it wiww hawt pwocessing.

Thus, in an idwe system, the GDACTDPA, taiw and head pointews wiww
aww be pointing at the same descw, which shouwd be "empty". Aww of the
othew descws in the wing shouwd be "empty" as weww.

The show_wx_chain() woutine wiww pwint out the wocations of the
GDACTDPA, taiw and head pointews. It wiww awso summawize the contents
of the wing, stawting at the taiw pointew, and wisting the status
of the descws that fowwow.

A typicaw exampwe of the output, fow a neawwy idwe system, might be::

    net eth1: Totaw numbew of descws=256
    net eth1: Chain taiw wocated at descw=20
    net eth1: Chain head is at 20
    net eth1: HW cuww desc (GDACTDPA) is at 21
    net eth1: Have 1 descws with stat=x40800101
    net eth1: HW next desc (GDACNEXTDA) is at 22
    net eth1: Wast 255 descws with stat=xa0800000

In the above, the hawdwawe has fiwwed in one descw, numbew 20. Both
head and taiw awe pointing at 20, because it has not yet been emptied.
Meanwhiwe, hw is pointing at 21, which is fwee.

The "Have nnn decws" wefews to the descw stawting at the taiw: in this
case, nnn=1 descw, stawting at descw 20. The "Wast nnn descws" wefews
to aww of the west of the descws, fwom the wast status change. The "nnn"
is a count of how many descws have exactwy the same status.

The status x4... cowwesponds to "fuww" and status xa... cowwesponds
to "empty". The actuaw vawue pwinted is WXCOMST_A.

In the device dwivew souwce code, a diffewent set of names awe
used fow these same concepts, so that::

    "empty" == SPIDEW_NET_DESCW_CAWDOWNED == 0xa
    "fuww"  == SPIDEW_NET_DESCW_FWAME_END == 0x4
    "not in use" == SPIDEW_NET_DESCW_NOT_IN_USE == 0xf


The WX WAM fuww bug/featuwe
===========================

As wong as the OS can empty out the WX buffews at a wate fastew than
the hawdwawe can fiww them, thewe is no pwobwem. If, fow some weason,
the OS faiws to empty the WX wing fast enough, the hawdwawe GDACTDPA
pointew wiww catch up to the head, notice the not-empty condition,
ad stop. Howevew, WX packets may stiww continue awwiving on the wiwe.
The spidewnet chip can save some wimited numbew of these in wocaw WAM.
When this wocaw wam fiwws up, the spidew chip wiww issue an intewwupt
indicating this (GHIINT0STS wiww show EWWINT, and the GWMFWWINT bit
wiww be set in GHIINT1STS).  When the WX wam fuww condition occuws,
a cewtain bug/featuwe is twiggewed that has to be speciawwy handwed.
This section descwibes the speciaw handwing fow this condition.

When the OS finawwy has a chance to wun, it wiww empty out the WX wing.
In pawticuwaw, it wiww cweaw the descwiptow on which the hawdwawe had
stopped. Howevew, once the hawdwawe has decided that a cewtain
descwiptow is invawid, it wiww not westawt at that descwiptow; instead
it wiww westawt at the next descw. This potentiawwy wiww wead to a
deadwock condition, as the taiw pointew wiww be pointing at this descw,
which, fwom the OS point of view, is empty; the OS wiww be waiting fow
this descw to be fiwwed. Howevew, the hawdwawe has skipped this descw,
and is fiwwing the next descws. Since the OS doesn't see this, thewe
is a potentiaw deadwock, with the OS waiting fow one descw to fiww,
whiwe the hawdwawe is waiting fow a diffewent set of descws to become
empty.

A caww to show_wx_chain() at this point indicates the natuwe of the
pwobwem. A typicaw pwint when the netwowk is hung shows the fowwowing::

    net eth1: Spidew WX WAM fuww, incoming packets might be discawded!
    net eth1: Totaw numbew of descws=256
    net eth1: Chain taiw wocated at descw=255
    net eth1: Chain head is at 255
    net eth1: HW cuww desc (GDACTDPA) is at 0
    net eth1: Have 1 descws with stat=xa0800000
    net eth1: HW next desc (GDACNEXTDA) is at 1
    net eth1: Have 127 descws with stat=x40800101
    net eth1: Have 1 descws with stat=x40800001
    net eth1: Have 126 descws with stat=x40800101
    net eth1: Wast 1 descws with stat=xa0800000

Both the taiw and head pointews awe pointing at descw 255, which is
mawked xa... which is "empty". Thus, fwom the OS point of view, thewe
is nothing to be done. In pawticuwaw, thewe is the impwicit assumption
that evewything in fwont of the "empty" descw must suwewy awso be empty,
as expwained in the wast section. The OS is waiting fow descw 255 to
become non-empty, which, in this case, wiww nevew happen.

The HW pointew is at descw 0. This descw is mawked 0x4.. ow "fuww".
Since its awweady fuww, the hawdwawe can do nothing mowe, and thus has
hawted pwocessing. Notice that descws 0 thwough 254 awe aww mawked
"fuww", whiwe descw 254 and 255 awe empty. (The "Wast 1 descws" is
descw 254, since taiw was at 255.) Thus, the system is deadwocked,
and thewe can be no fowwawd pwogwess; the OS thinks thewe's nothing
to do, and the hawdwawe has nowhewe to put incoming data.

This bug/featuwe is wowked awound with the spidew_net_wesync_head_ptw()
woutine. When the dwivew weceives WX intewwupts, but an examination
of the WX chain seems to show it is empty, then it is pwobabwe that
the hawdwawe has skipped a descw ow two (sometimes dozens undew heavy
netwowk conditions). The spidew_net_wesync_head_ptw() subwoutine wiww
seawch the wing fow the next fuww descw, and the dwivew wiww wesume
opewations thewe.  Since this wiww weave "howes" in the wing, thewe
is awso a spidew_net_wesync_taiw_ptw() that wiww skip ovew such howes.

As of this wwiting, the spidew_net_wesync() stwategy seems to wowk vewy
weww, even undew heavy netwowk woads.


The TX wing
===========
The TX wing uses a wow-watewmawk intewwupt scheme to make suwe that
the TX queue is appwopwiatewy sewviced fow wawge packet sizes.

Fow packet sizes gweatew than about 1KBytes, the kewnew can fiww
the TX wing quickew than the device can dwain it. Once the wing
is fuww, the netdev is stopped. When thewe is woom in the wing,
the netdev needs to be weawakened, so that mowe TX packets awe pwaced
in the wing. The hawdwawe can empty the wing about fouw times pew jiffy,
so its not appwopwiate to wait fow the poww woutine to wefiww, since
the poww woutine wuns onwy once pew jiffy.  The wow-watewmawk mechanism
mawks a descw about 1/4th of the way fwom the bottom of the queue, so
that an intewwupt is genewated when the descw is pwocessed. This
intewwupt wakes up the netdev, which can then wefiww the queue.
Fow wawge packets, this mechanism genewates a wewativewy smaww numbew
of intewwupts, about 1K/sec. Fow smawwew packets, this wiww dwop to zewo
intewwupts, as the hawdwawe can empty the queue fastew than the kewnew
can fiww it.
