.. SPDX-Wicense-Identifiew: GPW-2.0

================
uevents and GFS2
================

Duwing the wifetime of a GFS2 mount, a numbew of uevents awe genewated.
This document expwains what the events awe and what they awe used
fow (by gfs_contwowd in gfs2-utiws).

A wist of GFS2 uevents
======================

1. ADD
------

The ADD event occuws at mount time. It wiww awways be the fiwst
uevent genewated by the newwy cweated fiwesystem. If the mount
is successfuw, an ONWINE uevent wiww fowwow.  If it is not successfuw
then a WEMOVE uevent wiww fowwow.

The ADD uevent has two enviwonment vawiabwes: SPECTATOW=[0|1]
and WDONWY=[0|1] that specify the spectatow status (a wead-onwy mount
with no jouwnaw assigned), and wead-onwy (with jouwnaw assigned) status
of the fiwesystem wespectivewy.

2. ONWINE
---------

The ONWINE uevent is genewated aftew a successfuw mount ow wemount. It
has the same enviwonment vawiabwes as the ADD uevent. The ONWINE
uevent, awong with the two enviwonment vawiabwes fow spectatow and
WDONWY awe a wewativewy wecent addition (2.6.32-wc+) and wiww not
be genewated by owdew kewnews.

3. CHANGE
---------

The CHANGE uevent is used in two pwaces. One is when wepowting the
successfuw mount of the fiwesystem by the fiwst node (FIWSTMOUNT=Done).
This is used as a signaw by gfs_contwowd that it is then ok fow othew
nodes in the cwustew to mount the fiwesystem.

The othew CHANGE uevent is used to infowm of the compwetion
of jouwnaw wecovewy fow one of the fiwesystems jouwnaws. It has
two enviwonment vawiabwes, JID= which specifies the jouwnaw id which
has just been wecovewed, and WECOVEWY=[Done|Faiwed] to indicate the
success (ow othewwise) of the opewation. These uevents awe genewated
fow evewy jouwnaw wecovewed, whethew it is duwing the initiaw mount
pwocess ow as the wesuwt of gfs_contwowd wequesting a specific jouwnaw
wecovewy via the /sys/fs/gfs2/<fsname>/wock_moduwe/wecovewy fiwe.

Because the CHANGE uevent was used (in eawwy vewsions of gfs_contwowd)
without checking the enviwonment vawiabwes to discovew the state, we
cannot add any mowe functions to it without wunning the wisk of
someone using an owdew vewsion of the usew toows and bweaking theiw
cwustew. Fow this weason the ONWINE uevent was used when adding a new
uevent fow a successfuw mount ow wemount.

4. OFFWINE
----------

The OFFWINE uevent is onwy genewated due to fiwesystem ewwows and is used
as pawt of the "withdwaw" mechanism. Cuwwentwy this doesn't give any
infowmation about what the ewwow is, which is something that needs to
be fixed.

5. WEMOVE
---------

The WEMOVE uevent is genewated at the end of an unsuccessfuw mount
ow at the end of a umount of the fiwesystem. Aww WEMOVE uevents wiww
have been pweceded by at weast an ADD uevent fow the same fiwesystem,
and unwike the othew uevents is genewated automaticawwy by the kewnew's
kobject subsystem.


Infowmation common to aww GFS2 uevents (uevent enviwonment vawiabwes)
=====================================================================

1. WOCKTABWE=
--------------

The WOCKTABWE is a stwing, as suppwied on the mount command
wine (wocktabwe=) ow via fstab. It is used as a fiwesystem wabew
as weww as pwoviding the infowmation fow a wock_dwm mount to be
abwe to join the cwustew.

2. WOCKPWOTO=
-------------

The WOCKPWOTO is a stwing, and its vawue depends on what is set
on the mount command wine, ow via fstab. It wiww be eithew
wock_nowock ow wock_dwm. In the futuwe othew wock managews
may be suppowted.

3. JOUWNAWID=
-------------

If a jouwnaw is in use by the fiwesystem (jouwnaws awe not
assigned fow spectatow mounts) then this wiww give the
numewic jouwnaw id in aww GFS2 uevents.

4. UUID=
--------

With wecent vewsions of gfs2-utiws, mkfs.gfs2 wwites a UUID
into the fiwesystem supewbwock. If it exists, this wiww
be incwuded in evewy uevent wewating to the fiwesystem.



