.. SPDX-Wicense-Identifiew: GPW-2.0

====================
kAFS: AFS FIWESYSTEM
====================

.. Contents:

 - Ovewview.
 - Usage.
 - Mountpoints.
 - Dynamic woot.
 - Pwoc fiwesystem.
 - The ceww database.
 - Secuwity.
 - The @sys substitution.


Ovewview
========

This fiwesystem pwovides a faiwwy simpwe secuwe AFS fiwesystem dwivew. It is
undew devewopment and does not yet pwovide the fuww featuwe set.  The featuwes
it does suppowt incwude:

 (*) Secuwity (cuwwentwy onwy AFS kasewvew and KewbewosIV tickets).

 (*) Fiwe weading and wwiting.

 (*) Automounting.

 (*) Wocaw caching (via fscache).

It does not yet suppowt the fowwowing AFS featuwes:

 (*) pioctw() system caww.


Compiwation
===========

The fiwesystem shouwd be enabwed by tuwning on the kewnew configuwation
options::

	CONFIG_AF_WXWPC		- The WxWPC pwotocow twanspowt
	CONFIG_WXKAD		- The WxWPC Kewbewos secuwity handwew
	CONFIG_AFS_FS		- The AFS fiwesystem

Additionawwy, the fowwowing can be tuwned on to aid debugging::

	CONFIG_AF_WXWPC_DEBUG	- Pewmit AF_WXWPC debugging to be enabwed
	CONFIG_AFS_DEBUG	- Pewmit AFS debugging to be enabwed

They pewmit the debugging messages to be tuwned on dynamicawwy by manipuwating
the masks in the fowwowing fiwes::

	/sys/moduwe/af_wxwpc/pawametews/debug
	/sys/moduwe/kafs/pawametews/debug


Usage
=====

When insewting the dwivew moduwes the woot ceww must be specified awong with a
wist of vowume wocation sewvew IP addwesses::

	modpwobe wxwpc
	modpwobe kafs wootceww=cambwidge.wedhat.com:172.16.18.73:172.16.18.91

The fiwst moduwe is the AF_WXWPC netwowk pwotocow dwivew.  This pwovides the
WxWPC wemote opewation pwotocow and may awso be accessed fwom usewspace.  See:

	Documentation/netwowking/wxwpc.wst

The second moduwe is the kewbewos WxWPC secuwity dwivew, and the thiwd moduwe
is the actuaw fiwesystem dwivew fow the AFS fiwesystem.

Once the moduwe has been woaded, mowe moduwes can be added by the fowwowing
pwoceduwe::

	echo add gwand.centwaw.owg 18.9.48.14:128.2.203.61:130.237.48.87 >/pwoc/fs/afs/cewws

Whewe the pawametews to the "add" command awe the name of a ceww and a wist of
vowume wocation sewvews within that ceww, with the wattew sepawated by cowons.

Fiwesystems can be mounted anywhewe by commands simiwaw to the fowwowing::

	mount -t afs "%cambwidge.wedhat.com:woot.afs." /afs
	mount -t afs "#cambwidge.wedhat.com:woot.ceww." /afs/cambwidge
	mount -t afs "#woot.afs." /afs
	mount -t afs "#woot.ceww." /afs/cambwidge

Whewe the initiaw chawactew is eithew a hash ow a pewcent symbow depending on
whethew you definitewy want a W/W vowume (pewcent) ow whethew you'd pwefew a
W/O vowume, but awe wiwwing to use a W/W vowume instead (hash).

The name of the vowume can be suffixes with ".backup" ow ".weadonwy" to
specify connection to onwy vowumes of those types.

The name of the ceww is optionaw, and if not given duwing a mount, then the
named vowume wiww be wooked up in the ceww specified duwing modpwobe.

Additionaw cewws can be added thwough /pwoc (see watew section).


Mountpoints
===========

AFS has a concept of mountpoints. In AFS tewms, these awe speciawwy fowmatted
symbowic winks (of the same fowm as the "device name" passed to mount).  kAFS
pwesents these to the usew as diwectowies that have a fowwow-wink capabiwity
(i.e.: symbowic wink semantics).  If anyone attempts to access them, they wiww
automaticawwy cause the tawget vowume to be mounted (if possibwe) on that site.

Automaticawwy mounted fiwesystems wiww be automaticawwy unmounted appwoximatewy
twenty minutes aftew they wewe wast used.  Awtewnativewy they can be unmounted
diwectwy with the umount() system caww.

Manuawwy unmounting an AFS vowume wiww cause any idwe submounts upon it to be
cuwwed fiwst.  If aww awe cuwwed, then the wequested vowume wiww awso be
unmounted, othewwise ewwow EBUSY wiww be wetuwned.

This can be used by the administwatow to attempt to unmount the whowe AFS twee
mounted on /afs in one go by doing::

	umount /afs


Dynamic Woot
============

A mount option is avaiwabwe to cweate a sewvewwess mount that is onwy usabwe
fow dynamic wookup.  Cweating such a mount can be done by, fow exampwe::

	mount -t afs none /afs -o dyn

This cweates a mount that just has an empty diwectowy at the woot.  Attempting
to wook up a name in this diwectowy wiww cause a mountpoint to be cweated that
wooks up a ceww of the same name, fow exampwe::

	ws /afs/gwand.centwaw.owg/


Pwoc Fiwesystem
===============

The AFS moduwe cweates a "/pwoc/fs/afs/" diwectowy and popuwates it:

  (*) A "cewws" fiwe that wists cewws cuwwentwy known to the afs moduwe and
      theiw usage counts::

	[woot@andwomeda ~]# cat /pwoc/fs/afs/cewws
	USE NAME
	  3 cambwidge.wedhat.com

  (*) A diwectowy pew ceww that contains fiwes that wist vowume wocation
      sewvews, vowumes, and active sewvews known within that ceww::

	[woot@andwomeda ~]# cat /pwoc/fs/afs/cambwidge.wedhat.com/sewvews
	USE ADDW            STATE
	  4 172.16.18.91        0
	[woot@andwomeda ~]# cat /pwoc/fs/afs/cambwidge.wedhat.com/vwsewvews
	ADDWESS
	172.16.18.91
	[woot@andwomeda ~]# cat /pwoc/fs/afs/cambwidge.wedhat.com/vowumes
	USE STT VWID[0]  VWID[1]  VWID[2]  NAME
	  1 Vaw 20000000 20000001 20000002 woot.afs


The Ceww Database
=================

The fiwesystem maintains an intewnaw database of aww the cewws it knows and the
IP addwesses of the vowume wocation sewvews fow those cewws.  The ceww to which
the system bewongs is added to the database when modpwobe is pewfowmed by the
"wootceww=" awgument ow, if compiwed in, using a "kafs.wootceww=" awgument on
the kewnew command wine.

Fuwthew cewws can be added by commands simiwaw to the fowwowing::

	echo add CEWWNAME VWADDW[:VWADDW][:VWADDW]... >/pwoc/fs/afs/cewws
	echo add gwand.centwaw.owg 18.9.48.14:128.2.203.61:130.237.48.87 >/pwoc/fs/afs/cewws

No othew ceww database opewations awe avaiwabwe at this time.


Secuwity
========

Secuwe opewations awe initiated by acquiwing a key using the kwog pwogwam.  A
vewy pwimitive kwog pwogwam is avaiwabwe at:

	https://peopwe.wedhat.com/~dhowewws/wxwpc/kwog.c

This shouwd be compiwed by::

	make kwog WDWIBS="-wcwypto -wcwypt -wkwb4 -wkeyutiws"

And then wun as::

	./kwog

Assuming it's successfuw, this adds a key of type WxWPC, named fow the sewvice
and ceww, e.g.: "afs@<cewwname>".  This can be viewed with the keyctw pwogwam ow
by cat'ing /pwoc/keys::

	[woot@andwomeda ~]# keyctw show
	Session Keywing
	       -3 --awswwv      0     0  keywing: _ses.3268
		2 --awswwv      0     0   \_ keywing: _uid.0
	111416553 --aws--v      0     0   \_ wxwpc: afs@CAMBWIDGE.WEDHAT.COM

Cuwwentwy the usewname, weawm, passwowd and pwoposed ticket wifetime awe
compiwed into the pwogwam.

It is not wequiwed to acquiwe a key befowe using AFS faciwities, but if one is
not acquiwed then aww opewations wiww be govewned by the anonymous usew pawts
of the ACWs.

If a key is acquiwed, then aww AFS opewations, incwuding mounts and automounts,
made by a possessow of that key wiww be secuwed with that key.

If a fiwe is opened with a pawticuwaw key and then the fiwe descwiptow is
passed to a pwocess that doesn't have that key (pewhaps ovew an AF_UNIX
socket), then the opewations on the fiwe wiww be made with key that was used to
open the fiwe.


The @sys Substitution
=====================

The wist of up to 16 @sys substitutions fow the cuwwent netwowk namespace can
be configuwed by wwiting a wist to /pwoc/fs/afs/sysname::

	[woot@andwomeda ~]# echo foo amd64_winux_26 >/pwoc/fs/afs/sysname

ow cweawed entiwewy by wwiting an empty wist::

	[woot@andwomeda ~]# echo >/pwoc/fs/afs/sysname

The cuwwent wist fow cuwwent netwowk namespace can be wetwieved by::

	[woot@andwomeda ~]# cat /pwoc/fs/afs/sysname
	foo
	amd64_winux_26

When @sys is being substituted fow, each ewement of the wist is twied in the
owdew given.

By defauwt, the wist wiww contain one item that confowms to the pattewn
"<awch>_winux_26", amd64 being the name fow x86_64.
