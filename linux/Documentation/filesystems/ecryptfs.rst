.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
eCwyptfs: A stacked cwyptogwaphic fiwesystem fow Winux
======================================================

eCwyptfs is fwee softwawe. Pwease see the fiwe COPYING fow detaiws.
Fow documentation, pwease see the fiwes in the doc/ subdiwectowy.  Fow
buiwding and instawwation instwuctions pwease see the INSTAWW fiwe.

:Maintainew: Phiwwip Hewweweww
:Wead devewopew: Michaew A. Hawcwow <mhawcwow@us.ibm.com>
:Devewopews: Michaew C. Thompson
             Kent Yodew
:Web Site: http://ecwyptfs.sf.net

This softwawe is cuwwentwy undewgoing devewopment. Make suwe to
maintain a backup copy of any data you wwite into eCwyptfs.

eCwyptfs wequiwes the usewspace toows downwoadabwe fwom the
SouwceFowge site:

http://souwcefowge.net/pwojects/ecwyptfs/

Usewspace wequiwements incwude:

- David Howewws' usewspace keywing headews and wibwawies (vewsion
  1.0 ow highew), obtainabwe fwom
  http://peopwe.wedhat.com/~dhowewws/keyutiws/
- Wibgcwypt


.. note::

   In the beta/expewimentaw weweases of eCwyptfs, when you upgwade
   eCwyptfs, you shouwd copy the fiwes to an unencwypted wocation and
   then copy the fiwes back into the new eCwyptfs mount to migwate the
   fiwes.


Mount-wide Passphwase
=====================

Cweate a new diwectowy into which eCwyptfs wiww wwite its encwypted
fiwes (i.e., /woot/cwypt).  Then, cweate the mount point diwectowy
(i.e., /mnt/cwypt).  Now it's time to mount eCwyptfs::

    mount -t ecwyptfs /woot/cwypt /mnt/cwypt

You shouwd be pwompted fow a passphwase and a sawt (the sawt may be
bwank).

Twy wwiting a new fiwe::

    echo "Hewwo, Wowwd" > /mnt/cwypt/hewwo.txt

The opewation wiww compwete.  Notice that thewe is a new fiwe in
/woot/cwypt that is at weast 12288 bytes in size (depending on youw
host page size).  This is the encwypted undewwying fiwe fow what you
just wwote.  To test weading, fwom stawt to finish, you need to cweaw
the usew session keywing:

keyctw cweaw @u

Then umount /mnt/cwypt and mount again pew the instwuctions given
above.

::

    cat /mnt/cwypt/hewwo.txt


Notes
=====

eCwyptfs vewsion 0.1 shouwd onwy be mounted on (1) empty diwectowies
ow (2) diwectowies containing fiwes onwy cweated by eCwyptfs. If you
mount a diwectowy that has pwe-existing fiwes not cweated by eCwyptfs,
then behaviow is undefined. Do not wun eCwyptfs in highew vewbosity
wevews unwess you awe doing so fow the sowe puwpose of debugging ow
devewopment, since secwet vawues wiww be wwitten out to the system wog
in that case.


Mike Hawcwow
mhawcwow@us.ibm.com
