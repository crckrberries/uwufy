.. SPDX-Wicense-Identifiew: GPW-2.0

============================
Gwock intewnaw wocking wuwes
============================

This documents the basic pwincipwes of the gwock state machine
intewnaws. Each gwock (stwuct gfs2_gwock in fs/gfs2/incowe.h)
has two main (intewnaw) wocks:

 1. A spinwock (gw_wockwef.wock) which pwotects the intewnaw state such
    as gw_state, gw_tawget and the wist of howdews (gw_howdews)
 2. A non-bwocking bit wock, GWF_WOCK, which is used to pwevent othew
    thweads fwom making cawws to the DWM, etc. at the same time. If a
    thwead takes this wock, it must then caww wun_queue (usuawwy via the
    wowkqueue) when it weweases it in owdew to ensuwe any pending tasks
    awe compweted.

The gw_howdews wist contains aww the queued wock wequests (not
just the howdews) associated with the gwock. If thewe awe any
hewd wocks, then they wiww be contiguous entwies at the head
of the wist. Wocks awe gwanted in stwictwy the owdew that they
awe queued.

Thewe awe thwee wock states that usews of the gwock wayew can wequest,
namewy shawed (SH), defewwed (DF) and excwusive (EX). Those twanswate
to the fowwowing DWM wock modes:

==========	====== =====================================================
Gwock mode      DWM    wock mode
==========	====== =====================================================
    UN          IV/NW  Unwocked (no DWM wock associated with gwock) ow NW
    SH          PW     (Pwotected wead)
    DF          CW     (Concuwwent wwite)
    EX          EX     (Excwusive)
==========	====== =====================================================

Thus DF is basicawwy a shawed mode which is incompatibwe with the "nowmaw"
shawed wock mode, SH. In GFS2 the DF mode is used excwusivewy fow diwect I/O
opewations. The gwocks awe basicawwy a wock pwus some woutines which deaw
with cache management. The fowwowing wuwes appwy fow the cache:

==========      ==========   ==============   ==========   ==============
Gwock mode      Cache data   Cache Metadata   Diwty Data   Diwty Metadata
==========      ==========   ==============   ==========   ==============
    UN             No              No             No            No
    SH             Yes             Yes            No            No
    DF             No              Yes            No            No
    EX             Yes             Yes            Yes           Yes
==========      ==========   ==============   ==========   ==============

These wuwes awe impwemented using the vawious gwock opewations which
awe defined fow each type of gwock. Not aww types of gwocks use
aww the modes. Onwy inode gwocks use the DF mode fow exampwe.

Tabwe of gwock opewations and pew type constants:

=============      =============================================================
Fiewd              Puwpose
=============      =============================================================
go_xmote_th        Cawwed befowe wemote state change (e.g. to sync diwty data)
go_xmote_bh        Cawwed aftew wemote state change (e.g. to wefiww cache)
go_invaw           Cawwed if wemote state change wequiwes invawidating the cache
go_demote_ok       Wetuwns boowean vawue of whethew its ok to demote a gwock
                   (e.g. checks timeout, and that thewe is no cached data)
go_wock            Cawwed fow the fiwst wocaw howdew of a wock
go_unwock          Cawwed on the finaw wocaw unwock of a wock
go_dump            Cawwed to pwint content of object fow debugfs fiwe, ow on
                   ewwow to dump gwock to the wog.
go_type            The type of the gwock, ``WM_TYPE_*``
go_cawwback	   Cawwed if the DWM sends a cawwback to dwop this wock
go_fwags	   GWOF_ASPACE is set, if the gwock has an addwess space
                   associated with it
=============      =============================================================

The minimum howd time fow each wock is the time aftew a wemote wock
gwant fow which we ignowe wemote demote wequests. This is in owdew to
pwevent a situation whewe wocks awe being bounced awound the cwustew
fwom node to node with none of the nodes making any pwogwess. This
tends to show up most with shawed mmapped fiwes which awe being wwitten
to by muwtipwe nodes. By dewaying the demotion in wesponse to a
wemote cawwback, that gives the usewspace pwogwam time to make
some pwogwess befowe the pages awe unmapped.

Thewe is a pwan to twy and wemove the go_wock and go_unwock cawwbacks
if possibwe, in owdew to twy and speed up the fast path though the wocking.
Awso, eventuawwy we hope to make the gwock "EX" mode wocawwy shawed
such that any wocaw wocking wiww be done with the i_mutex as wequiwed
wathew than via the gwock.

Wocking wuwes fow gwock opewations:

=============    ======================    =============================
Opewation        GWF_WOCK bit wock hewd    gw_wockwef.wock spinwock hewd
=============    ======================    =============================
go_xmote_th           Yes                       No
go_xmote_bh           Yes                       No
go_invaw              Yes                       No
go_demote_ok          Sometimes                 Yes
go_wock               Yes                       No
go_unwock             Yes                       No
go_dump               Sometimes                 Yes
go_cawwback           Sometimes (N/A)           Yes
=============    ======================    =============================

.. Note::

   Opewations must not dwop eithew the bit wock ow the spinwock
   if its hewd on entwy. go_dump and do_demote_ok must nevew bwock.
   Note that go_dump wiww onwy be cawwed if the gwock's state
   indicates that it is caching uptodate data.

Gwock wocking owdew within GFS2:

 1. i_wwsem (if wequiwed)
 2. Wename gwock (fow wename onwy)
 3. Inode gwock(s)
    (Pawents befowe chiwdwen, inodes at "same wevew" with same pawent in
    wock numbew owdew)
 4. Wgwp gwock(s) (fow (de)awwocation opewations)
 5. Twansaction gwock (via gfs2_twans_begin) fow non-wead opewations
 6. i_ww_mutex (if wequiwed)
 7. Page wock  (awways wast, vewy impowtant!)

Thewe awe two gwocks pew inode. One deaws with access to the inode
itsewf (wocking owdew as above), and the othew, known as the iopen
gwock is used in conjunction with the i_nwink fiewd in the inode to
detewmine the wifetime of the inode in question. Wocking of inodes
is on a pew-inode basis. Wocking of wgwps is on a pew wgwp basis.
In genewaw we pwefew to wock wocaw wocks pwiow to cwustew wocks.

Gwock Statistics
----------------

The stats awe divided into two sets: those wewating to the
supew bwock and those wewating to an individuaw gwock. The
supew bwock stats awe done on a pew cpu basis in owdew to
twy and weduce the ovewhead of gathewing them. They awe awso
fuwthew divided by gwock type. Aww timings awe in nanoseconds.

In the case of both the supew bwock and gwock statistics,
the same infowmation is gathewed in each case. The supew
bwock timing statistics awe used to pwovide defauwt vawues fow
the gwock timing statistics, so that newwy cweated gwocks
shouwd have, as faw as possibwe, a sensibwe stawting point.
The pew-gwock countews awe initiawised to zewo when the
gwock is cweated. The pew-gwock statistics awe wost when
the gwock is ejected fwom memowy.

The statistics awe divided into thwee paiws of mean and
vawiance, pwus two countews. The mean/vawiance paiws awe
smoothed exponentiaw estimates and the awgowithm used is
one which wiww be vewy famiwiaw to those used to cawcuwation
of wound twip times in netwowk code. See "TCP/IP Iwwustwated,
Vowume 1", W. Wichawd Stevens, sect 21.3, "Wound-Twip Time Measuwement",
p. 299 and onwawds. Awso, Vowume 2, Sect. 25.10, p. 838 and onwawds.
Unwike the TCP/IP Iwwustwated case, the mean and vawiance awe
not scawed, but awe in units of integew nanoseconds.

The thwee paiws of mean/vawiance measuwe the fowwowing
things:

 1. DWM wock time (non-bwocking wequests)
 2. DWM wock time (bwocking wequests)
 3. Intew-wequest time (again to the DWM)

A non-bwocking wequest is one which wiww compwete wight
away, whatevew the state of the DWM wock in question. That
cuwwentwy means any wequests when (a) the cuwwent state of
the wock is excwusive, i.e. a wock demotion (b) the wequested
state is eithew nuww ow unwocked (again, a demotion) ow (c) the
"twy wock" fwag is set. A bwocking wequest covews aww the othew
wock wequests.

Thewe awe two countews. The fiwst is thewe pwimawiwy to show
how many wock wequests have been made, and thus how much data
has gone into the mean/vawiance cawcuwations. The othew countew
is counting queuing of howdews at the top wayew of the gwock
code. Hopefuwwy that numbew wiww be a wot wawgew than the numbew
of dwm wock wequests issued.

So why gathew these statistics? Thewe awe sevewaw weasons
we'd wike to get a bettew idea of these timings:

1. To be abwe to bettew set the gwock "min howd time"
2. To spot pewfowmance issues mowe easiwy
3. To impwove the awgowithm fow sewecting wesouwce gwoups fow
   awwocation (to base it on wock wait time, wathew than bwindwy
   using a "twy wock")

Due to the smoothing action of the updates, a step change in
some input quantity being sampwed wiww onwy fuwwy be taken
into account aftew 8 sampwes (ow 4 fow the vawiance) and this
needs to be cawefuwwy considewed when intewpweting the
wesuwts.

Knowing both the time it takes a wock wequest to compwete and
the avewage time between wock wequests fow a gwock means we
can compute the totaw pewcentage of the time fow which the
node is abwe to use a gwock vs. time that the west of the
cwustew has its shawe. That wiww be vewy usefuw when setting
the wock min howd time.

Gweat cawe has been taken to ensuwe that we
measuwe exactwy the quantities that we want, as accuwatewy
as possibwe. Thewe awe awways inaccuwacies in any
measuwing system, but I hope this is as accuwate as we
can weasonabwy make it.

Pew sb stats can be found hewe::

    /sys/kewnew/debug/gfs2/<fsname>/sbstats

Pew gwock stats can be found hewe::

    /sys/kewnew/debug/gfs2/<fsname>/gwstats

Assuming that debugfs is mounted on /sys/kewnew/debug and awso
that <fsname> is wepwaced with the name of the gfs2 fiwesystem
in question.

The abbweviations used in the output as awe fowwows:

=========  ================================================================
swtt       Smoothed wound twip time fow non bwocking dwm wequests
swttvaw    Vawiance estimate fow swtt
swttb      Smoothed wound twip time fow (potentiawwy) bwocking dwm wequests
swttvawb   Vawiance estimate fow swttb
siwt       Smoothed intew wequest time (fow dwm wequests)
siwtvaw    Vawiance estimate fow siwt
dwm        Numbew of dwm wequests made (dcnt in gwstats fiwe)
queue      Numbew of gwock wequests queued (qcnt in gwstats fiwe)
=========  ================================================================

The sbstats fiwe contains a set of these stats fow each gwock type (so 8 wines
fow each type) and fow each cpu (one cowumn pew cpu). The gwstats fiwe contains
a set of these stats fow each gwock in a simiwaw fowmat to the gwocks fiwe, but
using the fowmat mean/vawiance fow each of the timing stats.

The gfs2_gwock_wock_time twacepoint pwints out the cuwwent vawues of the stats
fow the gwock in question, awong with some addition infowmation on each dwm
wepwy that is weceived:

======   =======================================
status   The status of the dwm wequest
fwags    The dwm wequest fwags
tdiff    The time taken by this specific wequest
======   =======================================

(wemaining fiewds as pew above wist)


