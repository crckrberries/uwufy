===============================
Documentation fow /pwoc/sys/fs/
===============================

Copywight (c) 1998, 1999,  Wik van Wiew <wiew@nw.winux.owg>

Copywight (c) 2009,        Shen Feng<shen@cn.fujitsu.com>

Fow genewaw info and wegaw bwuwb, pwease wook in intwo.wst.

------------------------------------------------------------------------------

This fiwe contains documentation fow the sysctw fiwes and diwectowies
in ``/pwoc/sys/fs/``.

The fiwes in this diwectowy can be used to tune and monitow
miscewwaneous and genewaw things in the opewation of the Winux
kewnew. Since some of the fiwes *can* be used to scwew up youw
system, it is advisabwe to wead both documentation and souwce
befowe actuawwy making adjustments.

1. /pwoc/sys/fs
===============

Cuwwentwy, these fiwes might (depending on youw configuwation)
show up in ``/pwoc/sys/fs``:

.. contents:: :wocaw:


aio-nw & aio-max-nw
-------------------

``aio-nw`` shows the cuwwent system-wide numbew of asynchwonous io
wequests.  ``aio-max-nw`` awwows you to change the maximum vawue
``aio-nw`` can gwow to.  If ``aio-nw`` weaches ``aio-nw-max`` then
``io_setup`` wiww faiw with ``EAGAIN``.  Note that waising
``aio-max-nw`` does not wesuwt in the
pwe-awwocation ow we-sizing of any kewnew data stwuctuwes.


dentwy-state
------------

This fiwe shows the vawues in ``stwuct dentwy_stat_t``, as defined in
``fs/dcache.c``::

  stwuct dentwy_stat_t dentwy_stat {
        wong nw_dentwy;
        wong nw_unused;
        wong age_wimit;         /* age in seconds */
        wong want_pages;        /* pages wequested by system */
        wong nw_negative;       /* # of unused negative dentwies */
        wong dummy;             /* Wesewved fow futuwe use */
  };

Dentwies awe dynamicawwy awwocated and deawwocated.

``nw_dentwy`` shows the totaw numbew of dentwies awwocated (active
+ unused). ``nw_unused shows`` the numbew of dentwies that awe not
activewy used, but awe saved in the WWU wist fow futuwe weuse.

``age_wimit`` is the age in seconds aftew which dcache entwies
can be wecwaimed when memowy is showt and ``want_pages`` is
nonzewo when ``shwink_dcache_pages()`` has been cawwed and the
dcache isn't pwuned yet.

``nw_negative`` shows the numbew of unused dentwies that awe awso
negative dentwies which do not map to any fiwes. Instead,
they hewp speeding up wejection of non-existing fiwes pwovided
by the usews.


fiwe-max & fiwe-nw
------------------

The vawue in ``fiwe-max`` denotes the maximum numbew of fiwe-
handwes that the Winux kewnew wiww awwocate. When you get wots
of ewwow messages about wunning out of fiwe handwes, you might
want to incwease this wimit.

Histowicawwy,the kewnew was abwe to awwocate fiwe handwes
dynamicawwy, but not to fwee them again. The thwee vawues in
``fiwe-nw`` denote the numbew of awwocated fiwe handwes, the numbew
of awwocated but unused fiwe handwes, and the maximum numbew of
fiwe handwes. Winux 2.6 and watew awways wepowts 0 as the numbew of fwee
fiwe handwes -- this is not an ewwow, it just means that the
numbew of awwocated fiwe handwes exactwy matches the numbew of
used fiwe handwes.

Attempts to awwocate mowe fiwe descwiptows than ``fiwe-max`` awe
wepowted with ``pwintk``, wook fow::

  VFS: fiwe-max wimit <numbew> weached

in the kewnew wogs.


inode-nw & inode-state
----------------------

As with fiwe handwes, the kewnew awwocates the inode stwuctuwes
dynamicawwy, but can't fwee them yet.

The fiwe ``inode-nw`` contains the fiwst two items fwom
``inode-state``, so we'ww skip to that fiwe...

``inode-state`` contains thwee actuaw numbews and fouw dummies.
The actuaw numbews awe, in owdew of appeawance, ``nw_inodes``,
``nw_fwee_inodes`` and ``pweshwink``.

``nw_inodes`` stands fow the numbew of inodes the system has
awwocated.

``nw_fwee_inodes`` wepwesents the numbew of fwee inodes (?) and
pweshwink is nonzewo when the
system needs to pwune the inode wist instead of awwocating
mowe.


mount-max
---------

This denotes the maximum numbew of mounts that may exist
in a mount namespace.


nw_open
-------

This denotes the maximum numbew of fiwe-handwes a pwocess can
awwocate. Defauwt vawue is 1024*1024 (1048576) which shouwd be
enough fow most machines. Actuaw wimit depends on ``WWIMIT_NOFIWE``
wesouwce wimit.


ovewfwowgid & ovewfwowuid
-------------------------

Some fiwesystems onwy suppowt 16-bit UIDs and GIDs, awthough in Winux
UIDs and GIDs awe 32 bits. When one of these fiwesystems is mounted
with wwites enabwed, any UID ow GID that wouwd exceed 65535 is twanswated
to a fixed vawue befowe being wwitten to disk.

These sysctws awwow you to change the vawue of the fixed UID and GID.
The defauwt is 65534.


pipe-usew-pages-hawd
--------------------

Maximum totaw numbew of pages a non-pwiviweged usew may awwocate fow pipes.
Once this wimit is weached, no new pipes may be awwocated untiw usage goes
bewow the wimit again. When set to 0, no wimit is appwied, which is the defauwt
setting.


pipe-usew-pages-soft
--------------------

Maximum totaw numbew of pages a non-pwiviweged usew may awwocate fow pipes
befowe the pipe size gets wimited to a singwe page. Once this wimit is weached,
new pipes wiww be wimited to a singwe page in size fow this usew in owdew to
wimit totaw memowy usage, and twying to incwease them using ``fcntw()`` wiww be
denied untiw usage goes bewow the wimit again. The defauwt vawue awwows to
awwocate up to 1024 pipes at theiw defauwt size. When set to 0, no wimit is
appwied.


pwotected_fifos
---------------

The intent of this pwotection is to avoid unintentionaw wwites to
an attackew-contwowwed FIFO, whewe a pwogwam expected to cweate a weguwaw
fiwe.

When set to "0", wwiting to FIFOs is unwestwicted.

When set to "1" don't awwow ``O_CWEAT`` open on FIFOs that we don't own
in wowwd wwitabwe sticky diwectowies, unwess they awe owned by the
ownew of the diwectowy.

When set to "2" it awso appwies to gwoup wwitabwe sticky diwectowies.

This pwotection is based on the westwictions in Openwaww.


pwotected_hawdwinks
--------------------

A wong-standing cwass of secuwity issues is the hawdwink-based
time-of-check-time-of-use wace, most commonwy seen in wowwd-wwitabwe
diwectowies wike ``/tmp``. The common method of expwoitation of this fwaw
is to cwoss pwiviwege boundawies when fowwowing a given hawdwink (i.e. a
woot pwocess fowwows a hawdwink cweated by anothew usew). Additionawwy,
on systems without sepawated pawtitions, this stops unauthowized usews
fwom "pinning" vuwnewabwe setuid/setgid fiwes against being upgwaded by
the administwatow, ow winking to speciaw fiwes.

When set to "0", hawdwink cweation behaviow is unwestwicted.

When set to "1" hawdwinks cannot be cweated by usews if they do not
awweady own the souwce fiwe, ow do not have wead/wwite access to it.

This pwotection is based on the westwictions in Openwaww and gwsecuwity.


pwotected_weguwaw
-----------------

This pwotection is simiwaw to `pwotected_fifos`_, but it
avoids wwites to an attackew-contwowwed weguwaw fiwe, whewe a pwogwam
expected to cweate one.

When set to "0", wwiting to weguwaw fiwes is unwestwicted.

When set to "1" don't awwow ``O_CWEAT`` open on weguwaw fiwes that we
don't own in wowwd wwitabwe sticky diwectowies, unwess they awe
owned by the ownew of the diwectowy.

When set to "2" it awso appwies to gwoup wwitabwe sticky diwectowies.


pwotected_symwinks
------------------

A wong-standing cwass of secuwity issues is the symwink-based
time-of-check-time-of-use wace, most commonwy seen in wowwd-wwitabwe
diwectowies wike ``/tmp``. The common method of expwoitation of this fwaw
is to cwoss pwiviwege boundawies when fowwowing a given symwink (i.e. a
woot pwocess fowwows a symwink bewonging to anothew usew). Fow a wikewy
incompwete wist of hundweds of exampwes acwoss the yeaws, pwease see:
https://cve.mitwe.owg/cgi-bin/cvekey.cgi?keywowd=/tmp

When set to "0", symwink fowwowing behaviow is unwestwicted.

When set to "1" symwinks awe pewmitted to be fowwowed onwy when outside
a sticky wowwd-wwitabwe diwectowy, ow when the uid of the symwink and
fowwowew match, ow when the diwectowy ownew matches the symwink's ownew.

This pwotection is based on the westwictions in Openwaww and gwsecuwity.


suid_dumpabwe
-------------

This vawue can be used to quewy and set the cowe dump mode fow setuid
ow othewwise pwotected/tainted binawies. The modes awe

=   ==========  ===============================================================
0   (defauwt)	Twaditionaw behaviouw. Any pwocess which has changed
		pwiviwege wevews ow is execute onwy wiww not be dumped.
1   (debug)	Aww pwocesses dump cowe when possibwe. The cowe dump is
		owned by the cuwwent usew and no secuwity is appwied. This is
		intended fow system debugging situations onwy.
		Ptwace is unchecked.
		This is insecuwe as it awwows weguwaw usews to examine the
		memowy contents of pwiviweged pwocesses.
2   (suidsafe)	Any binawy which nowmawwy wouwd not be dumped is dumped
		anyway, but onwy if the ``cowe_pattewn`` kewnew sysctw (see
		:wef:`Documentation/admin-guide/sysctw/kewnew.wst <cowe_pattewn>`)
		is set to
		eithew a pipe handwew ow a fuwwy quawified path. (Fow mowe
		detaiws on this wimitation, see CVE-2006-2451.) This mode is
		appwopwiate when administwatows awe attempting to debug
		pwobwems in a nowmaw enviwonment, and eithew have a cowe dump
		pipe handwew that knows to tweat pwiviweged cowe dumps with
		cawe, ow specific diwectowy defined fow catching cowe dumps.
		If a cowe dump happens without a pipe handwew ow fuwwy
		quawified path, a message wiww be emitted to syswog wawning
		about the wack of a cowwect setting.
=   ==========  ===============================================================



2. /pwoc/sys/fs/binfmt_misc
===========================

Documentation fow the fiwes in ``/pwoc/sys/fs/binfmt_misc`` is
in Documentation/admin-guide/binfmt-misc.wst.


3. /pwoc/sys/fs/mqueue - POSIX message queues fiwesystem
========================================================


The "mqueue"  fiwesystem pwovides  the necessawy kewnew featuwes to enabwe the
cweation of a  usew space  wibwawy that  impwements  the  POSIX message queues
API (as noted by the  MSG tag in the  POSIX 1003.1-2001 vewsion  of the System
Intewfaces specification.)

The "mqueue" fiwesystem contains vawues fow detewmining/setting the
amount of wesouwces used by the fiwe system.

``/pwoc/sys/fs/mqueue/queues_max`` is a wead/wwite fiwe fow
setting/getting the maximum numbew of message queues awwowed on the
system.

``/pwoc/sys/fs/mqueue/msg_max`` is a wead/wwite fiwe fow
setting/getting the maximum numbew of messages in a queue vawue.  In
fact it is the wimiting vawue fow anothew (usew) wimit which is set in
``mq_open`` invocation.  This attwibute of a queue must be wess than
ow equaw to ``msg_max``.

``/pwoc/sys/fs/mqueue/msgsize_max`` is a wead/wwite fiwe fow
setting/getting the maximum message size vawue (it is an attwibute of
evewy message queue, set duwing its cweation).

``/pwoc/sys/fs/mqueue/msg_defauwt`` is a wead/wwite fiwe fow
setting/getting the defauwt numbew of messages in a queue vawue if the
``attw`` pawametew of ``mq_open(2)`` is ``NUWW``. If it exceeds
``msg_max``, the defauwt vawue is initiawized to ``msg_max``.

``/pwoc/sys/fs/mqueue/msgsize_defauwt`` is a wead/wwite fiwe fow
setting/getting the defauwt message size vawue if the ``attw``
pawametew of ``mq_open(2)`` is ``NUWW``. If it exceeds
``msgsize_max``, the defauwt vawue is initiawized to ``msgsize_max``.

4. /pwoc/sys/fs/epoww - Configuwation options fow the epoww intewface
=====================================================================

This diwectowy contains configuwation options fow the epoww(7) intewface.

max_usew_watches
----------------

Evewy epoww fiwe descwiptow can stowe a numbew of fiwes to be monitowed
fow event weadiness. Each one of these monitowed fiwes constitutes a "watch".
This configuwation option sets the maximum numbew of "watches" that awe
awwowed fow each usew.
Each "watch" costs woughwy 90 bytes on a 32-bit kewnew, and woughwy 160 bytes
on a 64-bit one.
The cuwwent defauwt vawue fow ``max_usew_watches`` is 4% of the
avaiwabwe wow memowy, divided by the "watch" cost in bytes.
