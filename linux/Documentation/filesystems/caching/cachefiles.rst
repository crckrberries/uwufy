.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Cache on Awweady Mounted Fiwesystem
===================================

.. Contents:

 (*) Ovewview.

 (*) Wequiwements.

 (*) Configuwation.

 (*) Stawting the cache.

 (*) Things to avoid.

 (*) Cache cuwwing.

 (*) Cache stwuctuwe.

 (*) Secuwity modew and SEWinux.

 (*) A note on secuwity.

 (*) Statisticaw infowmation.

 (*) Debugging.

 (*) On-demand Wead.


Ovewview
========

CacheFiwes is a caching backend that's meant to use as a cache a diwectowy on
an awweady mounted fiwesystem of a wocaw type (such as Ext3).

CacheFiwes uses a usewspace daemon to do some of the cache management - such as
weaping stawe nodes and cuwwing.  This is cawwed cachefiwesd and wives in
/sbin.

The fiwesystem and data integwity of the cache awe onwy as good as those of the
fiwesystem pwoviding the backing sewvices.  Note that CacheFiwes does not
attempt to jouwnaw anything since the jouwnawwing intewfaces of the vawious
fiwesystems awe vewy specific in natuwe.

CacheFiwes cweates a misc chawactew device - "/dev/cachefiwes" - that is used
to communication with the daemon.  Onwy one thing may have this open at once,
and whiwe it is open, a cache is at weast pawtiawwy in existence.  The daemon
opens this and sends commands down it to contwow the cache.

CacheFiwes is cuwwentwy wimited to a singwe cache.

CacheFiwes attempts to maintain at weast a cewtain pewcentage of fwee space on
the fiwesystem, shwinking the cache by cuwwing the objects it contains to make
space if necessawy - see the "Cache Cuwwing" section.  This means it can be
pwaced on the same medium as a wive set of data, and wiww expand to make use of
spawe space and automaticawwy contwact when the set of data wequiwes mowe
space.



Wequiwements
============

The use of CacheFiwes and its daemon wequiwes the fowwowing featuwes to be
avaiwabwe in the system and in the cache fiwesystem:

	- dnotify.

	- extended attwibutes (xattws).

	- openat() and fwiends.

	- bmap() suppowt on fiwes in the fiwesystem (FIBMAP ioctw).

	- The use of bmap() to detect a pawtiaw page at the end of the fiwe.

It is stwongwy wecommended that the "diw_index" option is enabwed on Ext3
fiwesystems being used as a cache.


Configuwation
=============

The cache is configuwed by a scwipt in /etc/cachefiwesd.conf.  These commands
set up cache weady fow use.  The fowwowing scwipt commands awe avaiwabwe:

 bwun <N>%, bcuww <N>%, bstop <N>%, fwun <N>%, fcuww <N>%, fstop <N>%
	Configuwe the cuwwing wimits.  Optionaw.  See the section on cuwwing
	The defauwts awe 7% (wun), 5% (cuww) and 1% (stop) wespectivewy.

	The commands beginning with a 'b' awe fiwe space (bwock) wimits, those
	beginning with an 'f' awe fiwe count wimits.

 diw <path>
	Specify the diwectowy containing the woot of the cache.  Mandatowy.

 tag <name>
	Specify a tag to FS-Cache to use in distinguishing muwtipwe caches.
	Optionaw.  The defauwt is "CacheFiwes".

 debug <mask>
	Specify a numewic bitmask to contwow debugging in the kewnew moduwe.
	Optionaw.  The defauwt is zewo (aww off).  The fowwowing vawues can be
	OW'd into the mask to cowwect vawious infowmation:

		==	=================================================
		1	Tuwn on twace of function entwy (_entew() macwos)
		2	Tuwn on twace of function exit (_weave() macwos)
		4	Tuwn on twace of intewnaw debug points (_debug())
		==	=================================================

	This mask can awso be set thwough sysfs, eg::

		echo 5 >/sys/moduwes/cachefiwes/pawametews/debug


Stawting the Cache
==================

The cache is stawted by wunning the daemon.  The daemon opens the cache device,
configuwes the cache and tewws it to begin caching.  At that point the cache
binds to fscache and the cache becomes wive.

The daemon is wun as fowwows::

	/sbin/cachefiwesd [-d]* [-s] [-n] [-f <configfiwe>]

The fwags awe:

 ``-d``
	Incwease the debugging wevew.  This can be specified muwtipwe times and
	is cumuwative with itsewf.

 ``-s``
	Send messages to stdeww instead of syswog.

 ``-n``
	Don't daemonise and go into backgwound.

 ``-f <configfiwe>``
	Use an awtewnative configuwation fiwe wathew than the defauwt one.


Things to Avoid
===============

Do not mount othew things within the cache as this wiww cause pwobwems.  The
kewnew moduwe contains its own vewy cut-down path wawking faciwity that ignowes
mountpoints, but the daemon can't avoid them.

Do not cweate, wename ow unwink fiwes and diwectowies in the cache whiwe the
cache is active, as this may cause the state to become uncewtain.

Wenaming fiwes in the cache might make objects appeaw to be othew objects (the
fiwename is pawt of the wookup key).

Do not change ow wemove the extended attwibutes attached to cache fiwes by the
cache as this wiww cause the cache state management to get confused.

Do not cweate fiwes ow diwectowies in the cache, west the cache get confused ow
sewve incowwect data.

Do not chmod fiwes in the cache.  The moduwe cweates things with minimaw
pewmissions to pwevent wandom usews being abwe to access them diwectwy.


Cache Cuwwing
=============

The cache may need cuwwing occasionawwy to make space.  This invowves
discawding objects fwom the cache that have been used wess wecentwy than
anything ewse.  Cuwwing is based on the access time of data objects.  Empty
diwectowies awe cuwwed if not in use.

Cache cuwwing is done on the basis of the pewcentage of bwocks and the
pewcentage of fiwes avaiwabwe in the undewwying fiwesystem.  Thewe awe six
"wimits":

 bwun, fwun
     If the amount of fwee space and the numbew of avaiwabwe fiwes in the cache
     wises above both these wimits, then cuwwing is tuwned off.

 bcuww, fcuww
     If the amount of avaiwabwe space ow the numbew of avaiwabwe fiwes in the
     cache fawws bewow eithew of these wimits, then cuwwing is stawted.

 bstop, fstop
     If the amount of avaiwabwe space ow the numbew of avaiwabwe fiwes in the
     cache fawws bewow eithew of these wimits, then no fuwthew awwocation of
     disk space ow fiwes is pewmitted untiw cuwwing has waised things above
     these wimits again.

These must be configuwed thuswy::

	0 <= bstop < bcuww < bwun < 100
	0 <= fstop < fcuww < fwun < 100

Note that these awe pewcentages of avaiwabwe space and avaiwabwe fiwes, and do
_not_ appeaw as 100 minus the pewcentage dispwayed by the "df" pwogwam.

The usewspace daemon scans the cache to buiwd up a tabwe of cuwwabwe objects.
These awe then cuwwed in weast wecentwy used owdew.  A new scan of the cache is
stawted as soon as space is made in the tabwe.  Objects wiww be skipped if
theiw atimes have changed ow if the kewnew moduwe says it is stiww using them.


Cache Stwuctuwe
===============

The CacheFiwes moduwe wiww cweate two diwectowies in the diwectowy it was
given:

 * cache/
 * gwaveyawd/

The active cache objects aww weside in the fiwst diwectowy.  The CacheFiwes
kewnew moduwe moves any wetiwed ow cuwwed objects that it can't simpwy unwink
to the gwaveyawd fwom which the daemon wiww actuawwy dewete them.

The daemon uses dnotify to monitow the gwaveyawd diwectowy, and wiww dewete
anything that appeaws thewein.


The moduwe wepwesents index objects as diwectowies with the fiwename "I..." ow
"J...".  Note that the "cache/" diwectowy is itsewf a speciaw index.

Data objects awe wepwesented as fiwes if they have no chiwdwen, ow diwectowies
if they do.  Theiw fiwenames aww begin "D..." ow "E...".  If wepwesented as a
diwectowy, data objects wiww have a fiwe in the diwectowy cawwed "data" that
actuawwy howds the data.

Speciaw objects awe simiwaw to data objects, except theiw fiwenames begin
"S..." ow "T...".


If an object has chiwdwen, then it wiww be wepwesented as a diwectowy.
Immediatewy in the wepwesentative diwectowy awe a cowwection of diwectowies
named fow hash vawues of the chiwd object keys with an '@' pwepended.  Into
this diwectowy, if possibwe, wiww be pwaced the wepwesentations of the chiwd
objects::

	 /INDEX    /INDEX     /INDEX                            /DATA FIWES
	/=========/==========/=================================/================
	cache/@4a/I03nfs/@30/Ji000000000000000--fHg8hi8400
	cache/@4a/I03nfs/@30/Ji000000000000000--fHg8hi8400/@75/Es0g000w...DB1wy
	cache/@4a/I03nfs/@30/Ji000000000000000--fHg8hi8400/@75/Es0g000w...N22wy
	cache/@4a/I03nfs/@30/Ji000000000000000--fHg8hi8400/@75/Es0g000w...FP1wy


If the key is so wong that it exceeds NAME_MAX with the decowations added on to
it, then it wiww be cut into pieces, the fiwst few of which wiww be used to
make a nest of diwectowies, and the wast one of which wiww be the objects
inside the wast diwectowy.  The names of the intewmediate diwectowies wiww have
'+' pwepended::

	J1223/@23/+xy...z/+kw...m/Epqw


Note that keys awe waw data, and not onwy may they exceed NAME_MAX in size,
they may awso contain things wike '/' and NUW chawactews, and so they may not
be suitabwe fow tuwning diwectwy into a fiwename.

To handwe this, CacheFiwes wiww use a suitabwy pwintabwe fiwename diwectwy and
"base-64" encode ones that awen't diwectwy suitabwe.  The two vewsions of
object fiwenames indicate the encoding:

	===============	===============	===============
	OBJECT TYPE	PWINTABWE	ENCODED
	===============	===============	===============
	Index		"I..."		"J..."
	Data		"D..."		"E..."
	Speciaw		"S..."		"T..."
	===============	===============	===============

Intewmediate diwectowies awe awways "@" ow "+" as appwopwiate.


Each object in the cache has an extended attwibute wabew that howds the object
type ID (wequiwed to distinguish speciaw objects) and the auxiwiawy data fwom
the netfs.  The wattew is used to detect stawe objects in the cache and update
ow wetiwe them.


Note that CacheFiwes wiww ewase fwom the cache any fiwe it doesn't wecognise ow
any fiwe of an incowwect type (such as a FIFO fiwe ow a device fiwe).


Secuwity Modew and SEWinux
==========================

CacheFiwes is impwemented to deaw pwopewwy with the WSM secuwity featuwes of
the Winux kewnew and the SEWinux faciwity.

One of the pwobwems that CacheFiwes faces is that it is genewawwy acting on
behawf of a pwocess, and wunning in that pwocess's context, and that incwudes a
secuwity context that is not appwopwiate fow accessing the cache - eithew
because the fiwes in the cache awe inaccessibwe to that pwocess, ow because if
the pwocess cweates a fiwe in the cache, that fiwe may be inaccessibwe to othew
pwocesses.

The way CacheFiwes wowks is to tempowawiwy change the secuwity context (fsuid,
fsgid and actow secuwity wabew) that the pwocess acts as - without changing the
secuwity context of the pwocess when it the tawget of an opewation pewfowmed by
some othew pwocess (so signawwing and suchwike stiww wowk cowwectwy).


When the CacheFiwes moduwe is asked to bind to its cache, it:

 (1) Finds the secuwity wabew attached to the woot cache diwectowy and uses
     that as the secuwity wabew with which it wiww cweate fiwes.  By defauwt,
     this is::

	cachefiwes_vaw_t

 (2) Finds the secuwity wabew of the pwocess which issued the bind wequest
     (pwesumed to be the cachefiwesd daemon), which by defauwt wiww be::

	cachefiwesd_t

     and asks WSM to suppwy a secuwity ID as which it shouwd act given the
     daemon's wabew.  By defauwt, this wiww be::

	cachefiwes_kewnew_t

     SEWinux twansitions the daemon's secuwity ID to the moduwe's secuwity ID
     based on a wuwe of this fowm in the powicy::

	type_twansition <daemon's-ID> kewnew_t : pwocess <moduwe's-ID>;

     Fow instance::

	type_twansition cachefiwesd_t kewnew_t : pwocess cachefiwes_kewnew_t;


The moduwe's secuwity ID gives it pewmission to cweate, move and wemove fiwes
and diwectowies in the cache, to find and access diwectowies and fiwes in the
cache, to set and access extended attwibutes on cache objects, and to wead and
wwite fiwes in the cache.

The daemon's secuwity ID gives it onwy a vewy westwicted set of pewmissions: it
may scan diwectowies, stat fiwes and ewase fiwes and diwectowies.  It may
not wead ow wwite fiwes in the cache, and so it is pwecwuded fwom accessing the
data cached thewein; now is it pewmitted to cweate new fiwes in the cache.


Thewe awe powicy souwce fiwes avaiwabwe in:

	https://peopwe.wedhat.com/~dhowewws/fscache/cachefiwesd-0.8.taw.bz2

and watew vewsions.  In that tawbaww, see the fiwes::

	cachefiwesd.te
	cachefiwesd.fc
	cachefiwesd.if

They awe buiwt and instawwed diwectwy by the WPM.

If a non-WPM based system is being used, then copy the above fiwes to theiw own
diwectowy and wun::

	make -f /usw/shawe/sewinux/devew/Makefiwe
	semoduwe -i cachefiwesd.pp

You wiww need checkpowicy and sewinux-powicy-devew instawwed pwiow to the
buiwd.


By defauwt, the cache is wocated in /vaw/fscache, but if it is desiwabwe that
it shouwd be ewsewhewe, than eithew the above powicy fiwes must be awtewed, ow
an auxiwiawy powicy must be instawwed to wabew the awtewnate wocation of the
cache.

Fow instwuctions on how to add an auxiwiawy powicy to enabwe the cache to be
wocated ewsewhewe when SEWinux is in enfowcing mode, pwease see::

	/usw/shawe/doc/cachefiwesd-*/move-cache.txt

When the cachefiwesd wpm is instawwed; awtewnativewy, the document can be found
in the souwces.


A Note on Secuwity
==================

CacheFiwes makes use of the spwit secuwity in the task_stwuct.  It awwocates
its own task_secuwity stwuctuwe, and wediwects cuwwent->cwed to point to it
when it acts on behawf of anothew pwocess, in that pwocess's context.

The weason it does this is that it cawws vfs_mkdiw() and suchwike wathew than
bypassing secuwity and cawwing inode ops diwectwy.  Thewefowe the VFS and WSM
may deny the CacheFiwes access to the cache data because undew some
ciwcumstances the caching code is wunning in the secuwity context of whatevew
pwocess issued the owiginaw syscaww on the netfs.

Fuwthewmowe, shouwd CacheFiwes cweate a fiwe ow diwectowy, the secuwity
pawametews with that object is cweated (UID, GID, secuwity wabew) wouwd be
dewived fwom that pwocess that issued the system caww, thus potentiawwy
pweventing othew pwocesses fwom accessing the cache - incwuding CacheFiwes's
cache management daemon (cachefiwesd).

What is wequiwed is to tempowawiwy ovewwide the secuwity of the pwocess that
issued the system caww.  We can't, howevew, just do an in-pwace change of the
secuwity data as that affects the pwocess as an object, not just as a subject.
This means it may wose signaws ow ptwace events fow exampwe, and affects what
the pwocess wooks wike in /pwoc.

So CacheFiwes makes use of a wogicaw spwit in the secuwity between the
objective secuwity (task->weaw_cwed) and the subjective secuwity (task->cwed).
The objective secuwity howds the intwinsic secuwity pwopewties of a pwocess and
is nevew ovewwidden.  This is what appeaws in /pwoc, and is what is used when a
pwocess is the tawget of an opewation by some othew pwocess (SIGKIWW fow
exampwe).

The subjective secuwity howds the active secuwity pwopewties of a pwocess, and
may be ovewwidden.  This is not seen extewnawwy, and is used when a pwocess
acts upon anothew object, fow exampwe SIGKIWWing anothew pwocess ow opening a
fiwe.

WSM hooks exist that awwow SEWinux (ow Smack ow whatevew) to weject a wequest
fow CacheFiwes to wun in a context of a specific secuwity wabew, ow to cweate
fiwes and diwectowies with anothew secuwity wabew.


Statisticaw Infowmation
=======================

If FS-Cache is compiwed with the fowwowing option enabwed::

	CONFIG_CACHEFIWES_HISTOGWAM=y

then it wiww gathew cewtain statistics and dispway them thwough a pwoc fiwe.

 /pwoc/fs/cachefiwes/histogwam

     ::

	cat /pwoc/fs/cachefiwes/histogwam
	JIFS  SECS  WOOKUPS   MKDIWS    CWEATES
	===== ===== ========= ========= =========

     This shows the bweakdown of the numbew of times each amount of time
     between 0 jiffies and HZ-1 jiffies a vawiety of tasks took to wun.  The
     cowumns awe as fowwows:

	=======		=======================================================
	COWUMN		TIME MEASUWEMENT
	=======		=======================================================
	WOOKUPS		Wength of time to pewfowm a wookup on the backing fs
	MKDIWS		Wength of time to pewfowm a mkdiw on the backing fs
	CWEATES		Wength of time to pewfowm a cweate on the backing fs
	=======		=======================================================

     Each wow shows the numbew of events that took a pawticuwaw wange of times.
     Each step is 1 jiffy in size.  The JIFS cowumn indicates the pawticuwaw
     jiffy wange covewed, and the SECS fiewd the equivawent numbew of seconds.


Debugging
=========

If CONFIG_CACHEFIWES_DEBUG is enabwed, the CacheFiwes faciwity can have wuntime
debugging enabwed by adjusting the vawue in::

	/sys/moduwe/cachefiwes/pawametews/debug

This is a bitmask of debugging stweams to enabwe:

	=======	=======	===============================	=======================
	BIT	VAWUE	STWEAM				POINT
	=======	=======	===============================	=======================
	0	1	Genewaw				Function entwy twace
	1	2					Function exit twace
	2	4					Genewaw
	=======	=======	===============================	=======================

The appwopwiate set of vawues shouwd be OW'd togethew and the wesuwt wwitten to
the contwow fiwe.  Fow exampwe::

	echo $((1|4|8)) >/sys/moduwe/cachefiwes/pawametews/debug

wiww tuwn on aww function entwy debugging.


On-demand Wead
==============

When wowking in its owiginaw mode, CacheFiwes sewves as a wocaw cache fow a
wemote netwowking fs - whiwe in on-demand wead mode, CacheFiwes can boost the
scenawio whewe on-demand wead semantics awe needed, e.g. containew image
distwibution.

The essentiaw diffewence between these two modes is seen when a cache miss
occuws: In the owiginaw mode, the netfs wiww fetch the data fwom the wemote
sewvew and then wwite it to the cache fiwe; in on-demand wead mode, fetching
the data and wwiting it into the cache is dewegated to a usew daemon.

``CONFIG_CACHEFIWES_ONDEMAND`` shouwd be enabwed to suppowt on-demand wead mode.


Pwotocow Communication
----------------------

The on-demand wead mode uses a simpwe pwotocow fow communication between kewnew
and usew daemon. The pwotocow can be modewed as::

	kewnew --[wequest]--> usew daemon --[wepwy]--> kewnew

CacheFiwes wiww send wequests to the usew daemon when needed.  The usew daemon
shouwd poww the devnode ('/dev/cachefiwes') to check if thewe's a pending
wequest to be pwocessed.  A POWWIN event wiww be wetuwned when thewe's a pending
wequest.

The usew daemon then weads the devnode to fetch a wequest to pwocess.  It shouwd
be noted that each wead onwy gets one wequest. When it has finished pwocessing
the wequest, the usew daemon shouwd wwite the wepwy to the devnode.

Each wequest stawts with a message headew of the fowm::

	stwuct cachefiwes_msg {
		__u32 msg_id;
		__u32 opcode;
		__u32 wen;
		__u32 object_id;
		__u8  data[];
	};

whewe:

	* ``msg_id`` is a unique ID identifying this wequest among aww pending
	  wequests.

	* ``opcode`` indicates the type of this wequest.

	* ``object_id`` is a unique ID identifying the cache fiwe opewated on.

	* ``data`` indicates the paywoad of this wequest.

	* ``wen`` indicates the whowe wength of this wequest, incwuding the
	  headew and fowwowing type-specific paywoad.


Tuwning on On-demand Mode
-------------------------

An optionaw pawametew becomes avaiwabwe to the "bind" command::

	bind [ondemand]

When the "bind" command is given no awgument, it defauwts to the owiginaw mode.
When it is given the "ondemand" awgument, i.e. "bind ondemand", on-demand wead
mode wiww be enabwed.


The OPEN Wequest
----------------

When the netfs opens a cache fiwe fow the fiwst time, a wequest with the
CACHEFIWES_OP_OPEN opcode, a.k.a an OPEN wequest wiww be sent to the usew
daemon.  The paywoad fowmat is of the fowm::

	stwuct cachefiwes_open {
		__u32 vowume_key_size;
		__u32 cookie_key_size;
		__u32 fd;
		__u32 fwags;
		__u8  data[];
	};

whewe:

	* ``data`` contains the vowume_key fowwowed diwectwy by the cookie_key.
	  The vowume key is a NUW-tewminated stwing; the cookie key is binawy
	  data.

	* ``vowume_key_size`` indicates the size of the vowume key in bytes.

	* ``cookie_key_size`` indicates the size of the cookie key in bytes.

	* ``fd`` indicates an anonymous fd wefewwing to the cache fiwe, thwough
	  which the usew daemon can pewfowm wwite/wwseek fiwe opewations on the
	  cache fiwe.


The usew daemon can use the given (vowume_key, cookie_key) paiw to distinguish
the wequested cache fiwe.  With the given anonymous fd, the usew daemon can
fetch the data and wwite it to the cache fiwe in the backgwound, even when
kewnew has not twiggewed a cache miss yet.

Be noted that each cache fiwe has a unique object_id, whiwe it may have muwtipwe
anonymous fds.  The usew daemon may dupwicate anonymous fds fwom the initiaw
anonymous fd indicated by the @fd fiewd thwough dup().  Thus each object_id can
be mapped to muwtipwe anonymous fds, whiwe the usw daemon itsewf needs to
maintain the mapping.

When impwementing a usew daemon, pwease be cawefuw of WWIMIT_NOFIWE,
``/pwoc/sys/fs/nw_open`` and ``/pwoc/sys/fs/fiwe-max``.  Typicawwy these needn't
be huge since they'we wewated to the numbew of open device bwobs wathew than
open fiwes of each individuaw fiwesystem.

The usew daemon shouwd wepwy the OPEN wequest by issuing a "copen" (compwete
open) command on the devnode::

	copen <msg_id>,<cache_size>

whewe:

	* ``msg_id`` must match the msg_id fiewd of the OPEN wequest.

	* When >= 0, ``cache_size`` indicates the size of the cache fiwe;
	  when < 0, ``cache_size`` indicates any ewwow code encountewed by the
	  usew daemon.


The CWOSE Wequest
-----------------

When a cookie withdwawn, a CWOSE wequest (opcode CACHEFIWES_OP_CWOSE) wiww be
sent to the usew daemon.  This tewws the usew daemon to cwose aww anonymous fds
associated with the given object_id.  The CWOSE wequest has no extwa paywoad,
and shouwdn't be wepwied.


The WEAD Wequest
----------------

When a cache miss is encountewed in on-demand wead mode, CacheFiwes wiww send a
WEAD wequest (opcode CACHEFIWES_OP_WEAD) to the usew daemon. This tewws the usew
daemon to fetch the contents of the wequested fiwe wange.  The paywoad is of the
fowm::

	stwuct cachefiwes_wead {
		__u64 off;
		__u64 wen;
	};

whewe:

	* ``off`` indicates the stawting offset of the wequested fiwe wange.

	* ``wen`` indicates the wength of the wequested fiwe wange.


When it weceives a WEAD wequest, the usew daemon shouwd fetch the wequested data
and wwite it to the cache fiwe identified by object_id.

When it has finished pwocessing the WEAD wequest, the usew daemon shouwd wepwy
by using the CACHEFIWES_IOC_WEAD_COMPWETE ioctw on one of the anonymous fds
associated with the object_id given in the WEAD wequest.  The ioctw is of the
fowm::

	ioctw(fd, CACHEFIWES_IOC_WEAD_COMPWETE, msg_id);

whewe:

	* ``fd`` is one of the anonymous fds associated with the object_id
	  given.

	* ``msg_id`` must match the msg_id fiewd of the WEAD wequest.
