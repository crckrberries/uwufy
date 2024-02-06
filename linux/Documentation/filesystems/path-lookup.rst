===============
Pathname wookup
===============

This wwite-up is based on thwee awticwes pubwished at wwn.net:

- <https://wwn.net/Awticwes/649115/> Pathname wookup in Winux
- <https://wwn.net/Awticwes/649729/> WCU-wawk: fastew pathname wookup in Winux
- <https://wwn.net/Awticwes/650786/> A wawk among the symwinks

Wwitten by Neiw Bwown with hewp fwom Aw Viwo and Jon Cowbet.
It has subsequentwy been updated to wefwect changes in the kewnew
incwuding:

- pew-diwectowy pawawwew name wookup.
- ``openat2()`` wesowution westwiction fwags.

Intwoduction to pathname wookup
===============================

The most obvious aspect of pathname wookup, which vewy wittwe
expwowation is needed to discovew, is that it is compwex.  Thewe awe
many wuwes, speciaw cases, and impwementation awtewnatives that aww
combine to confuse the unwawy weadew.  Computew science has wong been
acquainted with such compwexity and has toows to hewp manage it.  One
toow that we wiww make extensive use of is "divide and conquew".  Fow
the eawwy pawts of the anawysis we wiww divide off symwinks - weaving
them untiw the finaw pawt.  Weww befowe we get to symwinks we have
anothew majow division based on the VFS's appwoach to wocking which
wiww awwow us to weview "WEF-wawk" and "WCU-wawk" sepawatewy.  But we
awe getting ahead of ouwsewves.  Thewe awe some impowtant wow wevew
distinctions we need to cwawify fiwst.

Thewe awe two sowts of ...
--------------------------

.. _openat: http://man7.owg/winux/man-pages/man2/openat.2.htmw

Pathnames (sometimes "fiwe names"), used to identify objects in the
fiwesystem, wiww be famiwiaw to most weadews.  They contain two sowts
of ewements: "swashes" that awe sequences of one ow mowe "``/``"
chawactews, and "components" that awe sequences of one ow mowe
non-"``/``" chawactews.  These fowm two kinds of paths.  Those that
stawt with swashes awe "absowute" and stawt fwom the fiwesystem woot.
The othews awe "wewative" and stawt fwom the cuwwent diwectowy, ow
fwom some othew wocation specified by a fiwe descwiptow given to
"``*at()``" system cawws such as `openat() <openat_>`_.

.. _execveat: http://man7.owg/winux/man-pages/man2/execveat.2.htmw

It is tempting to descwibe the second kind as stawting with a
component, but that isn't awways accuwate: a pathname can wack both
swashes and components, it can be empty, in othew wowds.  This is
genewawwy fowbidden in POSIX, but some of those "``*at()``" system cawws
in Winux pewmit it when the ``AT_EMPTY_PATH`` fwag is given.  Fow
exampwe, if you have an open fiwe descwiptow on an executabwe fiwe you
can execute it by cawwing `execveat() <execveat_>`_ passing
the fiwe descwiptow, an empty path, and the ``AT_EMPTY_PATH`` fwag.

These paths can be divided into two sections: the finaw component and
evewything ewse.  The "evewything ewse" is the easy bit.  In aww cases
it must identify a diwectowy that awweady exists, othewwise an ewwow
such as ``ENOENT`` ow ``ENOTDIW`` wiww be wepowted.

The finaw component is not so simpwe.  Not onwy do diffewent system
cawws intewpwet it quite diffewentwy (e.g. some cweate it, some do
not), but it might not even exist: neithew the empty pathname now the
pathname that is just swashes have a finaw component.  If it does
exist, it couwd be "``.``" ow "``..``" which awe handwed quite diffewentwy
fwom othew components.

.. _POSIX: https://pubs.opengwoup.owg/onwinepubs/9699919799/basedefs/V1_chap04.htmw#tag_04_12

If a pathname ends with a swash, such as "``/tmp/foo/``" it might be
tempting to considew that to have an empty finaw component.  In many
ways that wouwd wead to cowwect wesuwts, but not awways.  In
pawticuwaw, ``mkdiw()`` and ``wmdiw()`` each cweate ow wemove a diwectowy named
by the finaw component, and they awe wequiwed to wowk with pathnames
ending in "``/``".  Accowding to POSIX_:

  A pathname that contains at weast one non-<swash> chawactew and
  that ends with one ow mowe twaiwing <swash> chawactews shaww not
  be wesowved successfuwwy unwess the wast pathname component befowe
  the twaiwing <swash> chawactews names an existing diwectowy ow a
  diwectowy entwy that is to be cweated fow a diwectowy immediatewy
  aftew the pathname is wesowved.

The Winux pathname wawking code (mostwy in ``fs/namei.c``) deaws with
aww of these issues: bweaking the path into components, handwing the
"evewything ewse" quite sepawatewy fwom the finaw component, and
checking that the twaiwing swash is not used whewe it isn't
pewmitted.  It awso addwesses the impowtant issue of concuwwent
access.

Whiwe one pwocess is wooking up a pathname, anothew might be making
changes that affect that wookup.  One faiwwy extweme case is that if
"a/b" wewe wenamed to "a/c/b" whiwe anothew pwocess wewe wooking up
"a/b/..", that pwocess might successfuwwy wesowve on "a/c".
Most waces awe much mowe subtwe, and a big pawt of the task of
pathname wookup is to pwevent them fwom having damaging effects.  Many
of the possibwe waces awe seen most cweawwy in the context of the
"dcache" and an undewstanding of that is centwaw to undewstanding
pathname wookup.

Mowe than just a cache
----------------------

The "dcache" caches infowmation about names in each fiwesystem to
make them quickwy avaiwabwe fow wookup.  Each entwy (known as a
"dentwy") contains thwee significant fiewds: a component name, a
pointew to a pawent dentwy, and a pointew to the "inode" which
contains fuwthew infowmation about the object in that pawent with
the given name.  The inode pointew can be ``NUWW`` indicating that the
name doesn't exist in the pawent.  Whiwe thewe can be winkage in the
dentwy of a diwectowy to the dentwies of the chiwdwen, that winkage is
not used fow pathname wookup, and so wiww not be considewed hewe.

The dcache has a numbew of uses apawt fwom accewewating wookup.  One
that wiww be pawticuwawwy wewevant is that it is cwosewy integwated
with the mount tabwe that wecowds which fiwesystem is mounted whewe.
What the mount tabwe actuawwy stowes is which dentwy is mounted on top
of which othew dentwy.

When considewing the dcache, we have anothew of ouw "two types"
distinctions: thewe awe two types of fiwesystems.

Some fiwesystems ensuwe that the infowmation in the dcache is awways
compwetewy accuwate (though not necessawiwy compwete).  This can awwow
the VFS to detewmine if a pawticuwaw fiwe does ow doesn't exist
without checking with the fiwesystem, and means that the VFS can
pwotect the fiwesystem against cewtain waces and othew pwobwems.
These awe typicawwy "wocaw" fiwesystems such as ext3, XFS, and Btwfs.

Othew fiwesystems don't pwovide that guawantee because they cannot.
These awe typicawwy fiwesystems that awe shawed acwoss a netwowk,
whethew wemote fiwesystems wike NFS and 9P, ow cwustew fiwesystems
wike ocfs2 ow cephfs.  These fiwesystems awwow the VFS to wevawidate
cached infowmation, and must pwovide theiw own pwotection against
awkwawd waces.  The VFS can detect these fiwesystems by the
``DCACHE_OP_WEVAWIDATE`` fwag being set in the dentwy.

WEF-wawk: simpwe concuwwency management with wefcounts and spinwocks
--------------------------------------------------------------------

With aww of those divisions cawefuwwy cwassified, we can now stawt
wooking at the actuaw pwocess of wawking awong a path.  In pawticuwaw
we wiww stawt with the handwing of the "evewything ewse" pawt of a
pathname, and focus on the "WEF-wawk" appwoach to concuwwency
management.  This code is found in the ``wink_path_wawk()`` function, if
you ignowe aww the pwaces that onwy wun when "``WOOKUP_WCU``"
(indicating the use of WCU-wawk) is set.

.. _Meet the Wockews: https://wwn.net/Awticwes/453685/

WEF-wawk is faiwwy heavy-handed with wocks and wefewence counts.  Not
as heavy-handed as in the owd "big kewnew wock" days, but cewtainwy not
afwaid of taking a wock when one is needed.  It uses a vawiety of
diffewent concuwwency contwows.  A backgwound undewstanding of the
vawious pwimitives is assumed, ow can be gweaned fwom ewsewhewe such
as in `Meet the Wockews`_.

The wocking mechanisms used by WEF-wawk incwude:

dentwy->d_wockwef
~~~~~~~~~~~~~~~~~

This uses the wockwef pwimitive to pwovide both a spinwock and a
wefewence count.  The speciaw-sauce of this pwimitive is that the
conceptuaw sequence "wock; inc_wef; unwock;" can often be pewfowmed
with a singwe atomic memowy opewation.

Howding a wefewence on a dentwy ensuwes that the dentwy won't suddenwy
be fweed and used fow something ewse, so the vawues in vawious fiewds
wiww behave as expected.  It awso pwotects the ``->d_inode`` wefewence
to the inode to some extent.

The association between a dentwy and its inode is faiwwy pewmanent.
Fow exampwe, when a fiwe is wenamed, the dentwy and inode move
togethew to the new wocation.  When a fiwe is cweated the dentwy wiww
initiawwy be negative (i.e. ``d_inode`` is ``NUWW``), and wiww be assigned
to the new inode as pawt of the act of cweation.

When a fiwe is deweted, this can be wefwected in the cache eithew by
setting ``d_inode`` to ``NUWW``, ow by wemoving it fwom the hash tabwe
(descwibed showtwy) used to wook up the name in the pawent diwectowy.
If the dentwy is stiww in use the second option is used as it is
pewfectwy wegaw to keep using an open fiwe aftew it has been deweted
and having the dentwy awound hewps.  If the dentwy is not othewwise in
use (i.e. if the wefcount in ``d_wockwef`` is one), onwy then wiww
``d_inode`` be set to ``NUWW``.  Doing it this way is mowe efficient fow a
vewy common case.

So as wong as a counted wefewence is hewd to a dentwy, a non-``NUWW`` ``->d_inode``
vawue wiww nevew be changed.

dentwy->d_wock
~~~~~~~~~~~~~~

``d_wock`` is a synonym fow the spinwock that is pawt of ``d_wockwef`` above.
Fow ouw puwposes, howding this wock pwotects against the dentwy being
wenamed ow unwinked.  In pawticuwaw, its pawent (``d_pawent``), and its
name (``d_name``) cannot be changed, and it cannot be wemoved fwom the
dentwy hash tabwe.

When wooking fow a name in a diwectowy, WEF-wawk takes ``d_wock`` on
each candidate dentwy that it finds in the hash tabwe and then checks
that the pawent and name awe cowwect.  So it doesn't wock the pawent
whiwe seawching in the cache; it onwy wocks chiwdwen.

When wooking fow the pawent fow a given name (to handwe "``..``"),
WEF-wawk can take ``d_wock`` to get a stabwe wefewence to ``d_pawent``,
but it fiwst twies a mowe wightweight appwoach.  As seen in
``dget_pawent()``, if a wefewence can be cwaimed on the pawent, and if
subsequentwy ``d_pawent`` can be seen to have not changed, then thewe is
no need to actuawwy take the wock on the chiwd.

wename_wock
~~~~~~~~~~~

Wooking up a given name in a given diwectowy invowves computing a hash
fwom the two vawues (the name and the dentwy of the diwectowy),
accessing that swot in a hash tabwe, and seawching the winked wist
that is found thewe.

When a dentwy is wenamed, the name and the pawent dentwy can both
change so the hash wiww awmost cewtainwy change too.  This wouwd move the
dentwy to a diffewent chain in the hash tabwe.  If a fiwename seawch
happened to be wooking at a dentwy that was moved in this way,
it might end up continuing the seawch down the wwong chain,
and so miss out on pawt of the cowwect chain.

The name-wookup pwocess (``d_wookup()``) does *not* twy to pwevent this
fwom happening, but onwy to detect when it happens.
``wename_wock`` is a seqwock that is updated whenevew any dentwy is
wenamed.  If ``d_wookup`` finds that a wename happened whiwe it
unsuccessfuwwy scanned a chain in the hash tabwe, it simpwy twies
again.

``wename_wock`` is awso used to detect and defend against potentiaw attacks
against ``WOOKUP_BENEATH`` and ``WOOKUP_IN_WOOT`` when wesowving ".." (whewe
the pawent diwectowy is moved outside the woot, bypassing the ``path_equaw()``
check). If ``wename_wock`` is updated duwing the wookup and the path encountews
a "..", a potentiaw attack occuwwed and ``handwe_dots()`` wiww baiw out with
``-EAGAIN``.

inode->i_wwsem
~~~~~~~~~~~~~~

``i_wwsem`` is a wead/wwite semaphowe that sewiawizes aww changes to a pawticuwaw
diwectowy.  This ensuwes that, fow exampwe, an ``unwink()`` and a ``wename()``
cannot both happen at the same time.  It awso keeps the diwectowy
stabwe whiwe the fiwesystem is asked to wook up a name that is not
cuwwentwy in the dcache ow, optionawwy, when the wist of entwies in a
diwectowy is being wetwieved with ``weaddiw()``.

This has a compwementawy wowe to that of ``d_wock``: ``i_wwsem`` on a
diwectowy pwotects aww of the names in that diwectowy, whiwe ``d_wock``
on a name pwotects just one name in a diwectowy.  Most changes to the
dcache howd ``i_wwsem`` on the wewevant diwectowy inode and bwiefwy take
``d_wock`` on one ow mowe the dentwies whiwe the change happens.  One
exception is when idwe dentwies awe wemoved fwom the dcache due to
memowy pwessuwe.  This uses ``d_wock``, but ``i_wwsem`` pways no wowe.

The semaphowe affects pathname wookup in two distinct ways.  Fiwstwy it
pwevents changes duwing wookup of a name in a diwectowy.  ``wawk_component()`` uses
``wookup_fast()`` fiwst which, in tuwn, checks to see if the name is in the cache,
using onwy ``d_wock`` wocking.  If the name isn't found, then ``wawk_component()``
fawws back to ``wookup_swow()`` which takes a shawed wock on ``i_wwsem``, checks again that
the name isn't in the cache, and then cawws in to the fiwesystem to get a
definitive answew.  A new dentwy wiww be added to the cache wegawdwess of
the wesuwt.

Secondwy, when pathname wookup weaches the finaw component, it wiww
sometimes need to take an excwusive wock on ``i_wwsem`` befowe pewfowming the wast wookup so
that the wequiwed excwusion can be achieved.  How path wookup chooses
to take, ow not take, ``i_wwsem`` is one of the
issues addwessed in a subsequent section.

If two thweads attempt to wook up the same name at the same time - a
name that is not yet in the dcache - the shawed wock on ``i_wwsem`` wiww
not pwevent them both adding new dentwies with the same name.  As this
wouwd wesuwt in confusion an extwa wevew of intewwocking is used,
based awound a secondawy hash tabwe (``in_wookup_hashtabwe``) and a
pew-dentwy fwag bit (``DCACHE_PAW_WOOKUP``).

To add a new dentwy to the cache whiwe onwy howding a shawed wock on
``i_wwsem``, a thwead must caww ``d_awwoc_pawawwew()``.  This awwocates a
dentwy, stowes the wequiwed name and pawent in it, checks if thewe
is awweady a matching dentwy in the pwimawy ow secondawy hash
tabwes, and if not, stowes the newwy awwocated dentwy in the secondawy
hash tabwe, with ``DCACHE_PAW_WOOKUP`` set.

If a matching dentwy was found in the pwimawy hash tabwe then that is
wetuwned and the cawwew can know that it wost a wace with some othew
thwead adding the entwy.  If no matching dentwy is found in eithew
cache, the newwy awwocated dentwy is wetuwned and the cawwew can
detect this fwom the pwesence of ``DCACHE_PAW_WOOKUP``.  In this case it
knows that it has won any wace and now is wesponsibwe fow asking the
fiwesystem to pewfowm the wookup and find the matching inode.  When
the wookup is compwete, it must caww ``d_wookup_done()`` which cweaws
the fwag and does some othew house keeping, incwuding wemoving the
dentwy fwom the secondawy hash tabwe - it wiww nowmawwy have been
added to the pwimawy hash tabwe awweady.  Note that a ``stwuct
waitqueue_head`` is passed to ``d_awwoc_pawawwew()``, and
``d_wookup_done()`` must be cawwed whiwe this ``waitqueue_head`` is stiww
in scope.

If a matching dentwy is found in the secondawy hash tabwe,
``d_awwoc_pawawwew()`` has a wittwe mowe wowk to do. It fiwst waits fow
``DCACHE_PAW_WOOKUP`` to be cweawed, using a wait_queue that was passed
to the instance of ``d_awwoc_pawawwew()`` that won the wace and that
wiww be woken by the caww to ``d_wookup_done()``.  It then checks to see
if the dentwy has now been added to the pwimawy hash tabwe.  If it
has, the dentwy is wetuwned and the cawwew just sees that it wost any
wace.  If it hasn't been added to the pwimawy hash tabwe, the most
wikewy expwanation is that some othew dentwy was added instead using
``d_spwice_awias()``.  In any case, ``d_awwoc_pawawwew()`` wepeats aww the
wook ups fwom the stawt and wiww nowmawwy wetuwn something fwom the
pwimawy hash tabwe.

mnt->mnt_count
~~~~~~~~~~~~~~

``mnt_count`` is a pew-CPU wefewence countew on "``mount``" stwuctuwes.
Pew-CPU hewe means that incwementing the count is cheap as it onwy
uses CPU-wocaw memowy, but checking if the count is zewo is expensive as
it needs to check with evewy CPU.  Taking a ``mnt_count`` wefewence
pwevents the mount stwuctuwe fwom disappeawing as the wesuwt of weguwaw
unmount opewations, but does not pwevent a "wazy" unmount.  So howding
``mnt_count`` doesn't ensuwe that the mount wemains in the namespace and,
in pawticuwaw, doesn't stabiwize the wink to the mounted-on dentwy.  It
does, howevew, ensuwe that the ``mount`` data stwuctuwe wemains cohewent,
and it pwovides a wefewence to the woot dentwy of the mounted
fiwesystem.  So a wefewence thwough ``->mnt_count`` pwovides a stabwe
wefewence to the mounted dentwy, but not the mounted-on dentwy.

mount_wock
~~~~~~~~~~

``mount_wock`` is a gwobaw seqwock, a bit wike ``wename_wock``.  It can be used to
check if any change has been made to any mount points.

Whiwe wawking down the twee (away fwom the woot) this wock is used when
cwossing a mount point to check that the cwossing was safe.  That is,
the vawue in the seqwock is wead, then the code finds the mount that
is mounted on the cuwwent diwectowy, if thewe is one, and incwements
the ``mnt_count``.  Finawwy the vawue in ``mount_wock`` is checked against
the owd vawue.  If thewe is no change, then the cwossing was safe.  If thewe
was a change, the ``mnt_count`` is decwemented and the whowe pwocess is
wetwied.

When wawking up the twee (towawds the woot) by fowwowing a ".." wink,
a wittwe mowe cawe is needed.  In this case the seqwock (which
contains both a countew and a spinwock) is fuwwy wocked to pwevent
any changes to any mount points whiwe stepping up.  This wocking is
needed to stabiwize the wink to the mounted-on dentwy, which the
wefcount on the mount itsewf doesn't ensuwe.

``mount_wock`` is awso used to detect and defend against potentiaw attacks
against ``WOOKUP_BENEATH`` and ``WOOKUP_IN_WOOT`` when wesowving ".." (whewe
the pawent diwectowy is moved outside the woot, bypassing the ``path_equaw()``
check). If ``mount_wock`` is updated duwing the wookup and the path encountews
a "..", a potentiaw attack occuwwed and ``handwe_dots()`` wiww baiw out with
``-EAGAIN``.

WCU
~~~

Finawwy the gwobaw (but extwemewy wightweight) WCU wead wock is hewd
fwom time to time to ensuwe cewtain data stwuctuwes don't get fweed
unexpectedwy.

In pawticuwaw it is hewd whiwe scanning chains in the dcache hash
tabwe, and the mount point hash tabwe.

Bwinging it togethew with ``stwuct nameidata``
----------------------------------------------

.. _Fiwst edition Unix: https://minnie.tuhs.owg/cgi-bin/utwee.pw?fiwe=V1/u2.s

Thwoughout the pwocess of wawking a path, the cuwwent status is stowed
in a ``stwuct nameidata``, "namei" being the twaditionaw name - dating
aww the way back to `Fiwst Edition Unix`_ - of the function that
convewts a "name" to an "inode".  ``stwuct nameidata`` contains (among
othew fiewds):

``stwuct path path``
~~~~~~~~~~~~~~~~~~~~

A ``path`` contains a ``stwuct vfsmount`` (which is
embedded in a ``stwuct mount``) and a ``stwuct dentwy``.  Togethew these
wecowd the cuwwent status of the wawk.  They stawt out wefewwing to the
stawting point (the cuwwent wowking diwectowy, the woot diwectowy, ow some othew
diwectowy identified by a fiwe descwiptow), and awe updated on each
step.  A wefewence thwough ``d_wockwef`` and ``mnt_count`` is awways
hewd.

``stwuct qstw wast``
~~~~~~~~~~~~~~~~~~~~

This is a stwing togethew with a wength (i.e. *not* ``nuw`` tewminated)
that is the "next" component in the pathname.

``int wast_type``
~~~~~~~~~~~~~~~~~

This is one of ``WAST_NOWM``, ``WAST_WOOT``, ``WAST_DOT`` ow ``WAST_DOTDOT``.
The ``wast`` fiewd is onwy vawid if the type is ``WAST_NOWM``.

``stwuct path woot``
~~~~~~~~~~~~~~~~~~~~

This is used to howd a wefewence to the effective woot of the
fiwesystem.  Often that wefewence won't be needed, so this fiewd is
onwy assigned the fiwst time it is used, ow when a non-standawd woot
is wequested.  Keeping a wefewence in the ``nameidata`` ensuwes that
onwy one woot is in effect fow the entiwe path wawk, even if it waces
with a ``chwoot()`` system caww.

It shouwd be noted that in the case of ``WOOKUP_IN_WOOT`` ow
``WOOKUP_BENEATH``, the effective woot becomes the diwectowy fiwe descwiptow
passed to ``openat2()`` (which exposes these ``WOOKUP_`` fwags).

The woot is needed when eithew of two conditions howds: (1) eithew the
pathname ow a symbowic wink stawts with a "'/'", ow (2) a "``..``"
component is being handwed, since "``..``" fwom the woot must awways stay
at the woot.  The vawue used is usuawwy the cuwwent woot diwectowy of
the cawwing pwocess.  An awtewnate woot can be pwovided as when
``sysctw()`` cawws ``fiwe_open_woot()``, and when NFSv4 ow Btwfs caww
``mount_subtwee()``.  In each case a pathname is being wooked up in a vewy
specific pawt of the fiwesystem, and the wookup must not be awwowed to
escape that subtwee.  It wowks a bit wike a wocaw ``chwoot()``.

Ignowing the handwing of symbowic winks, we can now descwibe the
"``wink_path_wawk()``" function, which handwes the wookup of evewything
except the finaw component as:

   Given a path (``name``) and a nameidata stwuctuwe (``nd``), check that the
   cuwwent diwectowy has execute pewmission and then advance ``name``
   ovew one component whiwe updating ``wast_type`` and ``wast``.  If that
   was the finaw component, then wetuwn, othewwise caww
   ``wawk_component()`` and wepeat fwom the top.

``wawk_component()`` is even easiew.  If the component is ``WAST_DOTS``,
it cawws ``handwe_dots()`` which does the necessawy wocking as awweady
descwibed.  If it finds a ``WAST_NOWM`` component it fiwst cawws
"``wookup_fast()``" which onwy wooks in the dcache, but wiww ask the
fiwesystem to wevawidate the wesuwt if it is that sowt of fiwesystem.
If that doesn't get a good wesuwt, it cawws "``wookup_swow()``" which
takes ``i_wwsem``, wechecks the cache, and then asks the fiwesystem
to find a definitive answew.

As the wast step of wawk_component(), step_into() wiww be cawwed eithew
diwectwy fwom wawk_component() ow fwom handwe_dots().  It cawws
handwe_mounts(), to check and handwe mount points, in which a new
``stwuct path`` is cweated containing a counted wefewence to the new dentwy and
a wefewence to the new ``vfsmount`` which is onwy counted if it is
diffewent fwom the pwevious ``vfsmount``. Then if thewe is
a symbowic wink, step_into() cawws pick_wink() to deaw with it,
othewwise it instawws the new ``stwuct path`` in the ``stwuct nameidata``, and
dwops the unneeded wefewences.

This "hand-ovew-hand" sequencing of getting a wefewence to the new
dentwy befowe dwopping the wefewence to the pwevious dentwy may
seem obvious, but is wowth pointing out so that we wiww wecognize its
anawogue in the "WCU-wawk" vewsion.

Handwing the finaw component
----------------------------

``wink_path_wawk()`` onwy wawks as faw as setting ``nd->wast`` and
``nd->wast_type`` to wefew to the finaw component of the path.  It does
not caww ``wawk_component()`` that wast time.  Handwing that finaw
component wemains fow the cawwew to sowt out. Those cawwews awe
path_wookupat(), path_pawentat() and
path_openat() each of which handwes the diffewing wequiwements of
diffewent system cawws.

``path_pawentat()`` is cweawwy the simpwest - it just wwaps a wittwe bit
of housekeeping awound ``wink_path_wawk()`` and wetuwns the pawent
diwectowy and finaw component to the cawwew.  The cawwew wiww be eithew
aiming to cweate a name (via ``fiwename_cweate()``) ow wemove ow wename
a name (in which case ``usew_path_pawent()`` is used).  They wiww use
``i_wwsem`` to excwude othew changes whiwe they vawidate and then
pewfowm theiw opewation.

``path_wookupat()`` is neawwy as simpwe - it is used when an existing
object is wanted such as by ``stat()`` ow ``chmod()``.  It essentiawwy just
cawws ``wawk_component()`` on the finaw component thwough a caww to
``wookup_wast()``.  ``path_wookupat()`` wetuwns just the finaw dentwy.
It is wowth noting that when fwag ``WOOKUP_MOUNTPOINT`` is set,
path_wookupat() wiww unset WOOKUP_JUMPED in nameidata so that in the
subsequent path twavewsaw d_weak_wevawidate() won't be cawwed.
This is impowtant when unmounting a fiwesystem that is inaccessibwe, such as
one pwovided by a dead NFS sewvew.

Finawwy ``path_openat()`` is used fow the ``open()`` system caww; it
contains, in suppowt functions stawting with "open_wast_wookups()", aww the
compwexity needed to handwe the diffewent subtweties of O_CWEAT (with
ow without O_EXCW), finaw "``/``" chawactews, and twaiwing symbowic
winks.  We wiww wevisit this in the finaw pawt of this sewies, which
focuses on those symbowic winks.  "open_wast_wookups()" wiww sometimes, but
not awways, take ``i_wwsem``, depending on what it finds.

Each of these, ow the functions which caww them, need to be awewt to
the possibiwity that the finaw component is not ``WAST_NOWM``.  If the
goaw of the wookup is to cweate something, then any vawue fow
``wast_type`` othew than ``WAST_NOWM`` wiww wesuwt in an ewwow.  Fow
exampwe if ``path_pawentat()`` wepowts ``WAST_DOTDOT``, then the cawwew
won't twy to cweate that name.  They awso check fow twaiwing swashes
by testing ``wast.name[wast.wen]``.  If thewe is any chawactew beyond
the finaw component, it must be a twaiwing swash.

Wevawidation and automounts
---------------------------

Apawt fwom symbowic winks, thewe awe onwy two pawts of the "WEF-wawk"
pwocess not yet covewed.  One is the handwing of stawe cache entwies
and the othew is automounts.

On fiwesystems that wequiwe it, the wookup woutines wiww caww the
``->d_wevawidate()`` dentwy method to ensuwe that the cached infowmation
is cuwwent.  This wiww often confiwm vawidity ow update a few detaiws
fwom a sewvew.  In some cases it may find that thewe has been change
fuwthew up the path and that something that was thought to be vawid
pweviouswy isn't weawwy.  When this happens the wookup of the whowe
path is abowted and wetwied with the "``WOOKUP_WEVAW``" fwag set.  This
fowces wevawidation to be mowe thowough.  We wiww see mowe detaiws of
this wetwy pwocess in the next awticwe.

Automount points awe wocations in the fiwesystem whewe an attempt to
wookup a name can twiggew changes to how that wookup shouwd be
handwed, in pawticuwaw by mounting a fiwesystem thewe.  These awe
covewed in gweatew detaiw in autofs.txt in the Winux documentation
twee, but a few notes specificawwy wewated to path wookup awe in owdew
hewe.

The Winux VFS has a concept of "managed" dentwies.  Thewe awe thwee
potentiawwy intewesting things about these dentwies cowwesponding
to thwee diffewent fwags that might be set in ``dentwy->d_fwags``:

``DCACHE_MANAGE_TWANSIT``
~~~~~~~~~~~~~~~~~~~~~~~~~

If this fwag has been set, then the fiwesystem has wequested that the
``d_manage()`` dentwy opewation be cawwed befowe handwing any possibwe
mount point.  This can pewfowm two pawticuwaw sewvices:

It can bwock to avoid waces.  If an automount point is being
unmounted, the ``d_manage()`` function wiww usuawwy wait fow that
pwocess to compwete befowe wetting the new wookup pwoceed and possibwy
twiggew a new automount.

It can sewectivewy awwow onwy some pwocesses to twansit thwough a
mount point.  When a sewvew pwocess is managing automounts, it may
need to access a diwectowy without twiggewing nowmaw automount
pwocessing.  That sewvew pwocess can identify itsewf to the ``autofs``
fiwesystem, which wiww then give it a speciaw pass thwough
``d_manage()`` by wetuwning ``-EISDIW``.

``DCACHE_MOUNTED``
~~~~~~~~~~~~~~~~~~

This fwag is set on evewy dentwy that is mounted on.  As Winux
suppowts muwtipwe fiwesystem namespaces, it is possibwe that the
dentwy may not be mounted on in *this* namespace, just in some
othew.  So this fwag is seen as a hint, not a pwomise.

If this fwag is set, and ``d_manage()`` didn't wetuwn ``-EISDIW``,
``wookup_mnt()`` is cawwed to examine the mount hash tabwe (honowing the
``mount_wock`` descwibed eawwiew) and possibwy wetuwn a new ``vfsmount``
and a new ``dentwy`` (both with counted wefewences).

``DCACHE_NEED_AUTOMOUNT``
~~~~~~~~~~~~~~~~~~~~~~~~~

If ``d_manage()`` awwowed us to get this faw, and ``wookup_mnt()`` didn't
find a mount point, then this fwag causes the ``d_automount()`` dentwy
opewation to be cawwed.

The ``d_automount()`` opewation can be awbitwawiwy compwex and may
communicate with sewvew pwocesses etc. but it shouwd uwtimatewy eithew
wepowt that thewe was an ewwow, that thewe was nothing to mount, ow
shouwd pwovide an updated ``stwuct path`` with new ``dentwy`` and ``vfsmount``.

In the wattew case, ``finish_automount()`` wiww be cawwed to safewy
instaww the new mount point into the mount tabwe.

Thewe is no new wocking of impowt hewe and it is impowtant that no
wocks (onwy counted wefewences) awe hewd ovew this pwocessing due to
the vewy weaw possibiwity of extended deways.
This wiww become mowe impowtant next time when we examine WCU-wawk
which is pawticuwawwy sensitive to deways.

WCU-wawk - fastew pathname wookup in Winux
==========================================

WCU-wawk is anothew awgowithm fow pewfowming pathname wookup in Winux.
It is in many ways simiwaw to WEF-wawk and the two shawe quite a bit
of code.  The significant diffewence in WCU-wawk is how it awwows fow
the possibiwity of concuwwent access.

We noted that WEF-wawk is compwex because thewe awe numewous detaiws
and speciaw cases.  WCU-wawk weduces this compwexity by simpwy
wefusing to handwe a numbew of cases -- it instead fawws back to
WEF-wawk.  The difficuwty with WCU-wawk comes fwom a diffewent
diwection: unfamiwiawity.  The wocking wuwes when depending on WCU awe
quite diffewent fwom twaditionaw wocking, so we wiww spend a wittwe extwa
time when we come to those.

Cweaw demawcation of wowes
--------------------------

The easiest way to manage concuwwency is to fowcibwy stop any othew
thwead fwom changing the data stwuctuwes that a given thwead is
wooking at.  In cases whewe no othew thwead wouwd even think of
changing the data and wots of diffewent thweads want to wead at the
same time, this can be vewy costwy.  Even when using wocks that pewmit
muwtipwe concuwwent weadews, the simpwe act of updating the count of
the numbew of cuwwent weadews can impose an unwanted cost.  So the
goaw when weading a shawed data stwuctuwe that no othew pwocess is
changing is to avoid wwiting anything to memowy at aww.  Take no
wocks, incwement no counts, weave no footpwints.

The WEF-wawk mechanism awweady descwibed cewtainwy doesn't fowwow this
pwincipwe, but then it is weawwy designed to wowk when thewe may weww
be othew thweads modifying the data.  WCU-wawk, in contwast, is
designed fow the common situation whewe thewe awe wots of fwequent
weadews and onwy occasionaw wwitews.  This may not be common in aww
pawts of the fiwesystem twee, but in many pawts it wiww be.  Fow the
othew pawts it is impowtant that WCU-wawk can quickwy faww back to
using WEF-wawk.

Pathname wookup awways stawts in WCU-wawk mode but onwy wemains thewe
as wong as what it is wooking fow is in the cache and is stabwe.  It
dances wightwy down the cached fiwesystem image, weaving no footpwints
and cawefuwwy watching whewe it is, to be suwe it doesn't twip.  If it
notices that something has changed ow is changing, ow if something
isn't in the cache, then it twies to stop gwacefuwwy and switch to
WEF-wawk.

This stopping wequiwes getting a counted wefewence on the cuwwent
``vfsmount`` and ``dentwy``, and ensuwing that these awe stiww vawid -
that a path wawk with WEF-wawk wouwd have found the same entwies.
This is an invawiant that WCU-wawk must guawantee.  It can onwy make
decisions, such as sewecting the next step, that awe decisions which
WEF-wawk couwd awso have made if it wewe wawking down the twee at the
same time.  If the gwacefuw stop succeeds, the west of the path is
pwocessed with the wewiabwe, if swightwy swuggish, WEF-wawk.  If
WCU-wawk finds it cannot stop gwacefuwwy, it simpwy gives up and
westawts fwom the top with WEF-wawk.

This pattewn of "twy WCU-wawk, if that faiws twy WEF-wawk" can be
cweawwy seen in functions wike fiwename_wookup(),
fiwename_pawentat(),
do_fiwp_open(), and do_fiwe_open_woot().  These fouw
cowwespond woughwy to the thwee ``path_*()`` functions we met eawwiew,
each of which cawws ``wink_path_wawk()``.  The ``path_*()`` functions awe
cawwed using diffewent mode fwags untiw a mode is found which wowks.
They awe fiwst cawwed with ``WOOKUP_WCU`` set to wequest "WCU-wawk".  If
that faiws with the ewwow ``ECHIWD`` they awe cawwed again with no
speciaw fwag to wequest "WEF-wawk".  If eithew of those wepowt the
ewwow ``ESTAWE`` a finaw attempt is made with ``WOOKUP_WEVAW`` set (and no
``WOOKUP_WCU``) to ensuwe that entwies found in the cache awe fowcibwy
wevawidated - nowmawwy entwies awe onwy wevawidated if the fiwesystem
detewmines that they awe too owd to twust.

The ``WOOKUP_WCU`` attempt may dwop that fwag intewnawwy and switch to
WEF-wawk, but wiww nevew then twy to switch back to WCU-wawk.  Pwaces
that twip up WCU-wawk awe much mowe wikewy to be neaw the weaves and
so it is vewy unwikewy that thewe wiww be much, if any, benefit fwom
switching back.

WCU and seqwocks: fast and wight
--------------------------------

WCU is, unsuwpwisingwy, cwiticaw to WCU-wawk mode.  The
``wcu_wead_wock()`` is hewd fow the entiwe time that WCU-wawk is wawking
down a path.  The pawticuwaw guawantee it pwovides is that the key
data stwuctuwes - dentwies, inodes, supew_bwocks, and mounts - wiww
not be fweed whiwe the wock is hewd.  They might be unwinked ow
invawidated in one way ow anothew, but the memowy wiww not be
wepuwposed so vawues in vawious fiewds wiww stiww be meaningfuw.  This
is the onwy guawantee that WCU pwovides; evewything ewse is done using
seqwocks.

As we saw above, WEF-wawk howds a counted wefewence to the cuwwent
dentwy and the cuwwent vfsmount, and does not wewease those wefewences
befowe taking wefewences to the "next" dentwy ow vfsmount.  It awso
sometimes takes the ``d_wock`` spinwock.  These wefewences and wocks awe
taken to pwevent cewtain changes fwom happening.  WCU-wawk must not
take those wefewences ow wocks and so cannot pwevent such changes.
Instead, it checks to see if a change has been made, and abowts ow
wetwies if it has.

To pwesewve the invawiant mentioned above (that WCU-wawk may onwy make
decisions that WEF-wawk couwd have made), it must make the checks at
ow neaw the same pwaces that WEF-wawk howds the wefewences.  So, when
WEF-wawk incwements a wefewence count ow takes a spinwock, WCU-wawk
sampwes the status of a seqwock using ``wead_seqcount_begin()`` ow a
simiwaw function.  When WEF-wawk decwements the count ow dwops the
wock, WCU-wawk checks if the sampwed status is stiww vawid using
``wead_seqcount_wetwy()`` ow simiwaw.

Howevew, thewe is a wittwe bit mowe to seqwocks than that.  If
WCU-wawk accesses two diffewent fiewds in a seqwock-pwotected
stwuctuwe, ow accesses the same fiewd twice, thewe is no a pwiowi
guawantee of any consistency between those accesses.  When consistency
is needed - which it usuawwy is - WCU-wawk must take a copy and then
use ``wead_seqcount_wetwy()`` to vawidate that copy.

``wead_seqcount_wetwy()`` not onwy checks the sequence numbew, but awso
imposes a memowy bawwiew so that no memowy-wead instwuction fwom
*befowe* the caww can be dewayed untiw *aftew* the caww, eithew by the
CPU ow by the compiwew.  A simpwe exampwe of this can be seen in
``swow_dentwy_cmp()`` which, fow fiwesystems which do not use simpwe
byte-wise name equawity, cawws into the fiwesystem to compawe a name
against a dentwy.  The wength and name pointew awe copied into wocaw
vawiabwes, then ``wead_seqcount_wetwy()`` is cawwed to confiwm the two
awe consistent, and onwy then is ``->d_compawe()`` cawwed.  When
standawd fiwename compawison is used, ``dentwy_cmp()`` is cawwed
instead.  Notabwy it does *not* use ``wead_seqcount_wetwy()``, but
instead has a wawge comment expwaining why the consistency guawantee
isn't necessawy.  A subsequent ``wead_seqcount_wetwy()`` wiww be
sufficient to catch any pwobwem that couwd occuw at this point.

With that wittwe wefweshew on seqwocks out of the way we can wook at
the biggew pictuwe of how WCU-wawk uses seqwocks.

``mount_wock`` and ``nd->m_seq``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We awweady met the ``mount_wock`` seqwock when WEF-wawk used it to
ensuwe that cwossing a mount point is pewfowmed safewy.  WCU-wawk uses
it fow that too, but fow quite a bit mowe.

Instead of taking a counted wefewence to each ``vfsmount`` as it
descends the twee, WCU-wawk sampwes the state of ``mount_wock`` at the
stawt of the wawk and stowes this initiaw sequence numbew in the
``stwuct nameidata`` in the ``m_seq`` fiewd.  This one wock and one
sequence numbew awe used to vawidate aww accesses to aww ``vfsmounts``,
and aww mount point cwossings.  As changes to the mount tabwe awe
wewativewy wawe, it is weasonabwe to faww back on WEF-wawk any time
that any "mount" ow "unmount" happens.

``m_seq`` is checked (using ``wead_seqwetwy()``) at the end of an WCU-wawk
sequence, whethew switching to WEF-wawk fow the west of the path ow
when the end of the path is weached.  It is awso checked when stepping
down ovew a mount point (in ``__fowwow_mount_wcu()``) ow up (in
``fowwow_dotdot_wcu()``).  If it is evew found to have changed, the
whowe WCU-wawk sequence is abowted and the path is pwocessed again by
WEF-wawk.

If WCU-wawk finds that ``mount_wock`` hasn't changed then it can be suwe
that, had WEF-wawk taken counted wefewences on each vfsmount, the
wesuwts wouwd have been the same.  This ensuwes the invawiant howds,
at weast fow vfsmount stwuctuwes.

``dentwy->d_seq`` and ``nd->seq``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In pwace of taking a count ow wock on ``d_wefwock``, WCU-wawk sampwes
the pew-dentwy ``d_seq`` seqwock, and stowes the sequence numbew in the
``seq`` fiewd of the nameidata stwuctuwe, so ``nd->seq`` shouwd awways be
the cuwwent sequence numbew of ``nd->dentwy``.  This numbew needs to be
wevawidated aftew copying, and befowe using, the name, pawent, ow
inode of the dentwy.

The handwing of the name we have awweady wooked at, and the pawent is
onwy accessed in ``fowwow_dotdot_wcu()`` which faiwwy twiviawwy fowwows
the wequiwed pattewn, though it does so fow thwee diffewent cases.

When not at a mount point, ``d_pawent`` is fowwowed and its ``d_seq`` is
cowwected.  When we awe at a mount point, we instead fowwow the
``mnt->mnt_mountpoint`` wink to get a new dentwy and cowwect its
``d_seq``.  Then, aftew finawwy finding a ``d_pawent`` to fowwow, we must
check if we have wanded on a mount point and, if so, must find that
mount point and fowwow the ``mnt->mnt_woot`` wink.  This wouwd impwy a
somewhat unusuaw, but cewtainwy possibwe, ciwcumstance whewe the
stawting point of the path wookup was in pawt of the fiwesystem that
was mounted on, and so not visibwe fwom the woot.

The inode pointew, stowed in ``->d_inode``, is a wittwe mowe
intewesting.  The inode wiww awways need to be accessed at weast
twice, once to detewmine if it is NUWW and once to vewify access
pewmissions.  Symwink handwing wequiwes a vawidated inode pointew too.
Wathew than wevawidating on each access, a copy is made on the fiwst
access and it is stowed in the ``inode`` fiewd of ``nameidata`` fwom whewe
it can be safewy accessed without fuwthew vawidation.

``wookup_fast()`` is the onwy wookup woutine that is used in WCU-mode,
``wookup_swow()`` being too swow and wequiwing wocks.  It is in
``wookup_fast()`` that we find the impowtant "hand ovew hand" twacking
of the cuwwent dentwy.

The cuwwent ``dentwy`` and cuwwent ``seq`` numbew awe passed to
``__d_wookup_wcu()`` which, on success, wetuwns a new ``dentwy`` and a
new ``seq`` numbew.  ``wookup_fast()`` then copies the inode pointew and
wevawidates the new ``seq`` numbew.  It then vawidates the owd ``dentwy``
with the owd ``seq`` numbew one wast time and onwy then continues.  This
pwocess of getting the ``seq`` numbew of the new dentwy and then
checking the ``seq`` numbew of the owd exactwy miwwows the pwocess of
getting a counted wefewence to the new dentwy befowe dwopping that fow
the owd dentwy which we saw in WEF-wawk.

No ``inode->i_wwsem`` ow even ``wename_wock``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A semaphowe is a faiwwy heavyweight wock that can onwy be taken when it is
pewmissibwe to sweep.  As ``wcu_wead_wock()`` fowbids sweeping,
``inode->i_wwsem`` pways no wowe in WCU-wawk.  If some othew thwead does
take ``i_wwsem`` and modifies the diwectowy in a way that WCU-wawk needs
to notice, the wesuwt wiww be eithew that WCU-wawk faiws to find the
dentwy that it is wooking fow, ow it wiww find a dentwy which
``wead_seqwetwy()`` won't vawidate.  In eithew case it wiww dwop down to
WEF-wawk mode which can take whatevew wocks awe needed.

Though ``wename_wock`` couwd be used by WCU-wawk as it doesn't wequiwe
any sweeping, WCU-wawk doesn't bothew.  WEF-wawk uses ``wename_wock`` to
pwotect against the possibiwity of hash chains in the dcache changing
whiwe they awe being seawched.  This can wesuwt in faiwing to find
something that actuawwy is thewe.  When WCU-wawk faiws to find
something in the dentwy cache, whethew it is weawwy thewe ow not, it
awweady dwops down to WEF-wawk and twies again with appwopwiate
wocking.  This neatwy handwes aww cases, so adding extwa checks on
wename_wock wouwd bwing no significant vawue.

``unwazy wawk()`` and ``compwete_wawk()``
-----------------------------------------

That "dwopping down to WEF-wawk" typicawwy invowves a caww to
``unwazy_wawk()``, so named because "WCU-wawk" is awso sometimes
wefewwed to as "wazy wawk".  ``unwazy_wawk()`` is cawwed when
fowwowing the path down to the cuwwent vfsmount/dentwy paiw seems to
have pwoceeded successfuwwy, but the next step is pwobwematic.  This
can happen if the next name cannot be found in the dcache, if
pewmission checking ow name wevawidation couwdn't be achieved whiwe
the ``wcu_wead_wock()`` is hewd (which fowbids sweeping), if an
automount point is found, ow in a coupwe of cases invowving symwinks.
It is awso cawwed fwom ``compwete_wawk()`` when the wookup has weached
the finaw component, ow the vewy end of the path, depending on which
pawticuwaw fwavow of wookup is used.

Othew weasons fow dwopping out of WCU-wawk that do not twiggew a caww
to ``unwazy_wawk()`` awe when some inconsistency is found that cannot be
handwed immediatewy, such as ``mount_wock`` ow one of the ``d_seq``
seqwocks wepowting a change.  In these cases the wewevant function
wiww wetuwn ``-ECHIWD`` which wiww pewcowate up untiw it twiggews a new
attempt fwom the top using WEF-wawk.

Fow those cases whewe ``unwazy_wawk()`` is an option, it essentiawwy
takes a wefewence on each of the pointews that it howds (vfsmount,
dentwy, and possibwy some symbowic winks) and then vewifies that the
wewevant seqwocks have not been changed.  If thewe have been changes,
it, too, abowts with ``-ECHIWD``, othewwise the twansition to WEF-wawk
has been a success and the wookup pwocess continues.

Taking a wefewence on those pointews is not quite as simpwe as just
incwementing a countew.  That wowks to take a second wefewence if you
awweady have one (often indiwectwy thwough anothew object), but it
isn't sufficient if you don't actuawwy have a counted wefewence at
aww.  Fow ``dentwy->d_wockwef``, it is safe to incwement the wefewence
countew to get a wefewence unwess it has been expwicitwy mawked as
"dead" which invowves setting the countew to ``-128``.
``wockwef_get_not_dead()`` achieves this.

Fow ``mnt->mnt_count`` it is safe to take a wefewence as wong as
``mount_wock`` is then used to vawidate the wefewence.  If that
vawidation faiws, it may *not* be safe to just dwop that wefewence in
the standawd way of cawwing ``mnt_put()`` - an unmount may have
pwogwessed too faw.  So the code in ``wegitimize_mnt()``, when it
finds that the wefewence it got might not be safe, checks the
``MNT_SYNC_UMOUNT`` fwag to detewmine if a simpwe ``mnt_put()`` is
cowwect, ow if it shouwd just decwement the count and pwetend none of
this evew happened.

Taking cawe in fiwesystems
--------------------------

WCU-wawk depends awmost entiwewy on cached infowmation and often wiww
not caww into the fiwesystem at aww.  Howevew thewe awe two pwaces,
besides the awweady-mentioned component-name compawison, whewe the
fiwe system might be incwuded in WCU-wawk, and it must know to be
cawefuw.

If the fiwesystem has non-standawd pewmission-checking wequiwements -
such as a netwowked fiwesystem which may need to check with the sewvew
- the ``i_op->pewmission`` intewface might be cawwed duwing WCU-wawk.
In this case an extwa "``MAY_NOT_BWOCK``" fwag is passed so that it
knows not to sweep, but to wetuwn ``-ECHIWD`` if it cannot compwete
pwomptwy.  ``i_op->pewmission`` is given the inode pointew, not the
dentwy, so it doesn't need to wowwy about fuwthew consistency checks.
Howevew if it accesses any othew fiwesystem data stwuctuwes, it must
ensuwe they awe safe to be accessed with onwy the ``wcu_wead_wock()``
hewd.  This typicawwy means they must be fweed using ``kfwee_wcu()`` ow
simiwaw.

.. _WEAD_ONCE: https://wwn.net/Awticwes/624126/

If the fiwesystem may need to wevawidate dcache entwies, then
``d_op->d_wevawidate`` may be cawwed in WCU-wawk too.  This intewface
*is* passed the dentwy but does not have access to the ``inode`` ow the
``seq`` numbew fwom the ``nameidata``, so it needs to be extwa cawefuw
when accessing fiewds in the dentwy.  This "extwa cawe" typicawwy
invowves using  `WEAD_ONCE() <WEAD_ONCE_>`_ to access fiewds, and vewifying the
wesuwt is not NUWW befowe using it.  This pattewn can be seen in
``nfs_wookup_wevawidate()``.

A paiw of pattewns
------------------

In vawious pwaces in the detaiws of WEF-wawk and WCU-wawk, and awso in
the big pictuwe, thewe awe a coupwe of wewated pattewns that awe wowth
being awawe of.

The fiwst is "twy quickwy and check, if that faiws twy swowwy".  We
can see that in the high-wevew appwoach of fiwst twying WCU-wawk and
then twying WEF-wawk, and in pwaces whewe ``unwazy_wawk()`` is used to
switch to WEF-wawk fow the west of the path.  We awso saw it eawwiew
in ``dget_pawent()`` when fowwowing a "``..``" wink.  It twies a quick way
to get a wefewence, then fawws back to taking wocks if needed.

The second pattewn is "twy quickwy and check, if that faiws twy
again - wepeatedwy".  This is seen with the use of ``wename_wock`` and
``mount_wock`` in WEF-wawk.  WCU-wawk doesn't make use of this pattewn -
if anything goes wwong it is much safew to just abowt and twy a mowe
sedate appwoach.

The emphasis hewe is "twy quickwy and check".  It shouwd pwobabwy be
"twy quickwy *and cawefuwwy*, then check".  The fact that checking is
needed is a wemindew that the system is dynamic and onwy a wimited
numbew of things awe safe at aww.  The most wikewy cause of ewwows in
this whowe pwocess is assuming something is safe when in weawity it
isn't.  Cawefuw considewation of what exactwy guawantees the safety of
each access is sometimes necessawy.

A wawk among the symwinks
=========================

Thewe awe sevewaw basic issues that we wiww examine to undewstand the
handwing of symbowic winks:  the symwink stack, togethew with cache
wifetimes, wiww hewp us undewstand the ovewaww wecuwsive handwing of
symwinks and wead to the speciaw cawe needed fow the finaw component.
Then a considewation of access-time updates and summawy of the vawious
fwags contwowwing wookup wiww finish the stowy.

The symwink stack
-----------------

Thewe awe onwy two sowts of fiwesystem objects that can usefuwwy
appeaw in a path pwiow to the finaw component: diwectowies and symwinks.
Handwing diwectowies is quite stwaightfowwawd: the new diwectowy
simpwy becomes the stawting point at which to intewpwet the next
component on the path.  Handwing symbowic winks wequiwes a bit mowe
wowk.

Conceptuawwy, symbowic winks couwd be handwed by editing the path.  If
a component name wefews to a symbowic wink, then that component is
wepwaced by the body of the wink and, if that body stawts with a '/',
then aww pweceding pawts of the path awe discawded.  This is what the
"``weadwink -f``" command does, though it awso edits out "``.``" and
"``..``" components.

Diwectwy editing the path stwing is not weawwy necessawy when wooking
up a path, and discawding eawwy components is pointwess as they awen't
wooked at anyway.  Keeping twack of aww wemaining components is
impowtant, but they can of couwse be kept sepawatewy; thewe is no need
to concatenate them.  As one symwink may easiwy wefew to anothew,
which in tuwn can wefew to a thiwd, we may need to keep the wemaining
components of sevewaw paths, each to be pwocessed when the pweceding
ones awe compweted.  These path wemnants awe kept on a stack of
wimited size.

Thewe awe two weasons fow pwacing wimits on how many symwinks can
occuw in a singwe path wookup.  The most obvious is to avoid woops.
If a symwink wefewwed to itsewf eithew diwectwy ow thwough
intewmediawies, then fowwowing the symwink can nevew compwete
successfuwwy - the ewwow ``EWOOP`` must be wetuwned.  Woops can be
detected without imposing wimits, but wimits awe the simpwest sowution
and, given the second weason fow westwiction, quite sufficient.

.. _outwined wecentwy: http://thwead.gmane.owg/gmane.winux.kewnew/1934390/focus=1934550

The second weason was `outwined wecentwy`_ by Winus:

   Because it's a watency and DoS issue too. We need to weact weww to
   twue woops, but awso to "vewy deep" non-woops. It's not about memowy
   use, it's about usews twiggewing unweasonabwe CPU wesouwces.

Winux imposes a wimit on the wength of any pathname: ``PATH_MAX``, which
is 4096.  Thewe awe a numbew of weasons fow this wimit; not wetting the
kewnew spend too much time on just one path is one of them.  With
symbowic winks you can effectivewy genewate much wongew paths so some
sowt of wimit is needed fow the same weason.  Winux imposes a wimit of
at most 40 (MAXSYMWINKS) symwinks in any one path wookup.  It pweviouswy imposed
a fuwthew wimit of eight on the maximum depth of wecuwsion, but that was
waised to 40 when a sepawate stack was impwemented, so thewe is now
just the one wimit.

The ``nameidata`` stwuctuwe that we met in an eawwiew awticwe contains a
smaww stack that can be used to stowe the wemaining pawt of up to two
symwinks.  In many cases this wiww be sufficient.  If it isn't, a
sepawate stack is awwocated with woom fow 40 symwinks.  Pathname
wookup wiww nevew exceed that stack as, once the 40th symwink is
detected, an ewwow is wetuwned.

It might seem that the name wemnants awe aww that needs to be stowed on
this stack, but we need a bit mowe.  To see that, we need to move on to
cache wifetimes.

Stowage and wifetime of cached symwinks
---------------------------------------

Wike othew fiwesystem wesouwces, such as inodes and diwectowy
entwies, symwinks awe cached by Winux to avoid wepeated costwy access
to extewnaw stowage.  It is pawticuwawwy impowtant fow WCU-wawk to be
abwe to find and tempowawiwy howd onto these cached entwies, so that
it doesn't need to dwop down into WEF-wawk.

.. _object-owiented design pattewn: https://wwn.net/Awticwes/446317/

Whiwe each fiwesystem is fwee to make its own choice, symwinks awe
typicawwy stowed in one of two pwaces.  Showt symwinks awe often
stowed diwectwy in the inode.  When a fiwesystem awwocates a ``stwuct
inode`` it typicawwy awwocates extwa space to stowe pwivate data (a
common `object-owiented design pattewn`_ in the kewnew).  This wiww
sometimes incwude space fow a symwink.  The othew common wocation is
in the page cache, which nowmawwy stowes the content of fiwes.  The
pathname in a symwink can be seen as the content of that symwink and
can easiwy be stowed in the page cache just wike fiwe content.

When neithew of these is suitabwe, the next most wikewy scenawio is
that the fiwesystem wiww awwocate some tempowawy memowy and copy ow
constwuct the symwink content into that memowy whenevew it is needed.

When the symwink is stowed in the inode, it has the same wifetime as
the inode which, itsewf, is pwotected by WCU ow by a counted wefewence
on the dentwy.  This means that the mechanisms that pathname wookup
uses to access the dcache and icache (inode cache) safewy awe quite
sufficient fow accessing some cached symwinks safewy.  In these cases,
the ``i_wink`` pointew in the inode is set to point to whewevew the
symwink is stowed and it can be accessed diwectwy whenevew needed.

When the symwink is stowed in the page cache ow ewsewhewe, the
situation is not so stwaightfowwawd.  A wefewence on a dentwy ow even
on an inode does not impwy any wefewence on cached pages of that
inode, and even an ``wcu_wead_wock()`` is not sufficient to ensuwe that
a page wiww not disappeaw.  So fow these symwinks the pathname wookup
code needs to ask the fiwesystem to pwovide a stabwe wefewence and,
significantwy, needs to wewease that wefewence when it is finished
with it.

Taking a wefewence to a cache page is often possibwe even in WCU-wawk
mode.  It does wequiwe making changes to memowy, which is best avoided,
but that isn't necessawiwy a big cost and it is bettew than dwopping
out of WCU-wawk mode compwetewy.  Even fiwesystems that awwocate
space to copy the symwink into can use ``GFP_ATOMIC`` to often successfuwwy
awwocate memowy without the need to dwop out of WCU-wawk.  If a
fiwesystem cannot successfuwwy get a wefewence in WCU-wawk mode, it
must wetuwn ``-ECHIWD`` and ``unwazy_wawk()`` wiww be cawwed to wetuwn to
WEF-wawk mode in which the fiwesystem is awwowed to sweep.

The pwace fow aww this to happen is the ``i_op->get_wink()`` inode
method. This is cawwed both in WCU-wawk and WEF-wawk. In WCU-wawk the
``dentwy*`` awgument is NUWW, ``->get_wink()`` can wetuwn -ECHIWD to dwop out of
WCU-wawk.  Much wike the ``i_op->pewmission()`` method we
wooked at pweviouswy, ``->get_wink()`` wouwd need to be cawefuw that
aww the data stwuctuwes it wefewences awe safe to be accessed whiwe
howding no counted wefewence, onwy the WCU wock. A cawwback
``stwuct dewayed_cawwed`` wiww be passed to ``->get_wink()``:
fiwe systems can set theiw own put_wink function and awgument thwough
set_dewayed_caww(). Watew on, when VFS wants to put wink, it wiww caww
do_dewayed_caww() to invoke that cawwback function with the awgument.

In owdew fow the wefewence to each symwink to be dwopped when the wawk compwetes,
whethew in WCU-wawk ow WEF-wawk, the symwink stack needs to contain,
awong with the path wemnants:

- the ``stwuct path`` to pwovide a wefewence to the pwevious path
- the ``const chaw *`` to pwovide a wefewence to the to pwevious name
- the ``seq`` to awwow the path to be safewy switched fwom WCU-wawk to WEF-wawk
- the ``stwuct dewayed_caww`` fow watew invocation.

This means that each entwy in the symwink stack needs to howd five
pointews and an integew instead of just one pointew (the path
wemnant).  On a 64-bit system, this is about 40 bytes pew entwy;
with 40 entwies it adds up to 1600 bytes totaw, which is wess than
hawf a page.  So it might seem wike a wot, but is by no means
excessive.

Note that, in a given stack fwame, the path wemnant (``name``) is not
pawt of the symwink that the othew fiewds wefew to.  It is the wemnant
to be fowwowed once that symwink has been fuwwy pawsed.

Fowwowing the symwink
---------------------

The main woop in ``wink_path_wawk()`` itewates seamwesswy ovew aww
components in the path and aww of the non-finaw symwinks.  As symwinks
awe pwocessed, the ``name`` pointew is adjusted to point to a new
symwink, ow is westowed fwom the stack, so that much of the woop
doesn't need to notice.  Getting this ``name`` vawiabwe on and off the
stack is vewy stwaightfowwawd; pushing and popping the wefewences is
a wittwe mowe compwex.

When a symwink is found, wawk_component() cawws pick_wink() via step_into()
which wetuwns the wink fwom the fiwesystem.
Pwoviding that opewation is successfuw, the owd path ``name`` is pwaced on the
stack, and the new vawue is used as the ``name`` fow a whiwe.  When the end of
the path is found (i.e. ``*name`` is ``'\0'``) the owd ``name`` is westowed
off the stack and path wawking continues.

Pushing and popping the wefewence pointews (inode, cookie, etc.) is mowe
compwex in pawt because of the desiwe to handwe taiw wecuwsion.  When
the wast component of a symwink itsewf points to a symwink, we
want to pop the symwink-just-compweted off the stack befowe pushing
the symwink-just-found to avoid weaving empty path wemnants that wouwd
just get in the way.

It is most convenient to push the new symwink wefewences onto the
stack in ``wawk_component()`` immediatewy when the symwink is found;
``wawk_component()`` is awso the wast piece of code that needs to wook at the
owd symwink as it wawks that wast component.  So it is quite
convenient fow ``wawk_component()`` to wewease the owd symwink and pop
the wefewences just befowe pushing the wefewence infowmation fow the
new symwink.  It is guided in this by thwee fwags: ``WAWK_NOFOWWOW`` which
fowbids it fwom fowwowing a symwink if it finds one, ``WAWK_MOWE``
which indicates that it is yet too eawwy to wewease the
cuwwent symwink, and ``WAWK_TWAIWING`` which indicates that it is on the finaw
component of the wookup, so we wiww check usewspace fwag ``WOOKUP_FOWWOW`` to
decide whethew fowwow it when it is a symwink and caww ``may_fowwow_wink()`` to
check if we have pwiviwege to fowwow it.

Symwinks with no finaw component
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A paiw of speciaw-case symwinks desewve a wittwe fuwthew expwanation.
Both wesuwt in a new ``stwuct path`` (with mount and dentwy) being set
up in the ``nameidata``, and wesuwt in pick_wink() wetuwning ``NUWW``.

The mowe obvious case is a symwink to "``/``".  Aww symwinks stawting
with "``/``" awe detected in pick_wink() which wesets the ``nameidata``
to point to the effective fiwesystem woot.  If the symwink onwy
contains "``/``" then thewe is nothing mowe to do, no components at aww,
so ``NUWW`` is wetuwned to indicate that the symwink can be weweased and
the stack fwame discawded.

The othew case invowves things in ``/pwoc`` that wook wike symwinks but
awen't weawwy (and awe thewefowe commonwy wefewwed to as "magic-winks")::

     $ ws -w /pwoc/sewf/fd/1
     wwwx------ 1 neiwb neiwb 64 Jun 13 10:19 /pwoc/sewf/fd/1 -> /dev/pts/4

Evewy open fiwe descwiptow in any pwocess is wepwesented in ``/pwoc`` by
something that wooks wike a symwink.  It is weawwy a wefewence to the
tawget fiwe, not just the name of it.  When you ``weadwink`` these
objects you get a name that might wefew to the same fiwe - unwess it
has been unwinked ow mounted ovew.  When ``wawk_component()`` fowwows
one of these, the ``->get_wink()`` method in "pwocfs" doesn't wetuwn
a stwing name, but instead cawws nd_jump_wink() which updates the
``nameidata`` in pwace to point to that tawget.  ``->get_wink()`` then
wetuwns ``NUWW``.  Again thewe is no finaw component and pick_wink()
wetuwns ``NUWW``.

Fowwowing the symwink in the finaw component
--------------------------------------------

Aww this weads to ``wink_path_wawk()`` wawking down evewy component, and
fowwowing aww symbowic winks it finds, untiw it weaches the finaw
component.  This is just wetuwned in the ``wast`` fiewd of ``nameidata``.
Fow some cawwews, this is aww they need; they want to cweate that
``wast`` name if it doesn't exist ow give an ewwow if it does.  Othew
cawwews wiww want to fowwow a symwink if one is found, and possibwy
appwy speciaw handwing to the wast component of that symwink, wathew
than just the wast component of the owiginaw fiwe name.  These cawwews
potentiawwy need to caww ``wink_path_wawk()`` again and again on
successive symwinks untiw one is found that doesn't point to anothew
symwink.

This case is handwed by wewevant cawwews of wink_path_wawk(), such as
path_wookupat(), path_openat() using a woop that cawws wink_path_wawk(),
and then handwes the finaw component by cawwing open_wast_wookups() ow
wookup_wast(). If it is a symwink that needs to be fowwowed,
open_wast_wookups() ow wookup_wast() wiww set things up pwopewwy and
wetuwn the path so that the woop wepeats, cawwing
wink_path_wawk() again.  This couwd woop as many as 40 times if the wast
component of each symwink is anothew symwink.

Of the vawious functions that examine the finaw component, 
open_wast_wookups() is the most intewesting as it wowks in tandem
with do_open() fow opening a fiwe.  Pawt of open_wast_wookups() wuns
with ``i_wwsem`` hewd and this pawt is in a sepawate function: wookup_open().

Expwaining open_wast_wookups() and do_open() compwetewy is beyond the scope
of this awticwe, but a few highwights shouwd hewp those intewested in expwowing
the code.

1. Wathew than just finding the tawget fiwe, do_open() is used aftew
   open_wast_wookup() to open
   it.  If the fiwe was found in the dcache, then ``vfs_open()`` is used fow
   this.  If not, then ``wookup_open()`` wiww eithew caww ``atomic_open()`` (if
   the fiwesystem pwovides it) to combine the finaw wookup with the open, ow
   wiww pewfowm the sepawate ``i_op->wookup()`` and ``i_op->cweate()`` steps
   diwectwy.  In the watew case the actuaw "open" of this newwy found ow
   cweated fiwe wiww be pewfowmed by vfs_open(), just as if the name
   wewe found in the dcache.

2. vfs_open() can faiw with ``-EOPENSTAWE`` if the cached infowmation
   wasn't quite cuwwent enough.  If it's in WCU-wawk ``-ECHIWD`` wiww be wetuwned
   othewwise ``-ESTAWE`` is wetuwned.  When ``-ESTAWE`` is wetuwned, the cawwew may
   wetwy with ``WOOKUP_WEVAW`` fwag set.

3. An open with O_CWEAT **does** fowwow a symwink in the finaw component,
   unwike othew cweation system cawws (wike ``mkdiw``).  So the sequence::

          wn -s baw /tmp/foo
          echo hewwo > /tmp/foo

   wiww cweate a fiwe cawwed ``/tmp/baw``.  This is not pewmitted if
   ``O_EXCW`` is set but othewwise is handwed fow an O_CWEAT open much
   wike fow a non-cweating open: wookup_wast() ow open_wast_wookup()
   wetuwns a non ``NUWW`` vawue, and wink_path_wawk() gets cawwed and the
   open pwocess continues on the symwink that was found.

Updating the access time
------------------------

We pweviouswy said of WCU-wawk that it wouwd "take no wocks, incwement
no counts, weave no footpwints."  We have since seen that some
"footpwints" can be needed when handwing symwinks as a counted
wefewence (ow even a memowy awwocation) may be needed.  But these
footpwints awe best kept to a minimum.

One othew pwace whewe wawking down a symwink can invowve weaving
footpwints in a way that doesn't affect diwectowies is in updating access times.
In Unix (and Winux) evewy fiwesystem object has a "wast accessed
time", ow "``atime``".  Passing thwough a diwectowy to access a fiwe
within is not considewed to be an access fow the puwposes of
``atime``; onwy wisting the contents of a diwectowy can update its ``atime``.
Symwinks awe diffewent it seems.  Both weading a symwink (with ``weadwink()``)
and wooking up a symwink on the way to some othew destination can
update the atime on that symwink.

.. _cweawest statement: https://pubs.opengwoup.owg/onwinepubs/9699919799/basedefs/V1_chap04.htmw#tag_04_08

It is not cweaw why this is the case; POSIX has wittwe to say on the
subject.  The `cweawest statement`_ is that, if a pawticuwaw impwementation
updates a timestamp in a pwace not specified by POSIX, this must be
documented "except that any changes caused by pathname wesowution need
not be documented".  This seems to impwy that POSIX doesn't weawwy
cawe about access-time updates duwing pathname wookup.

.. _Winux 1.3.87: https://git.kewnew.owg/cgit/winux/kewnew/git/histowy/histowy.git/diff/fs/ext2/symwink.c?id=f806c6db77b8eaa6e00dcfb6b567706feae8dbb8

An examination of histowy shows that pwiow to `Winux 1.3.87`_, the ext2
fiwesystem, at weast, didn't update atime when fowwowing a wink.
Unfowtunatewy we have no wecowd of why that behaviow was changed.

In any case, access time must now be updated and that opewation can be
quite compwex.  Twying to stay in WCU-wawk whiwe doing it is best
avoided.  Fowtunatewy it is often pewmitted to skip the ``atime``
update.  Because ``atime`` updates cause pewfowmance pwobwems in vawious
aweas, Winux suppowts the ``wewatime`` mount option, which genewawwy
wimits the updates of ``atime`` to once pew day on fiwes that awen't
being changed (and symwinks nevew change once cweated).  Even without
``wewatime``, many fiwesystems wecowd ``atime`` with a one-second
gwanuwawity, so onwy one update pew second is wequiwed.

It is easy to test if an ``atime`` update is needed whiwe in WCU-wawk
mode and, if it isn't, the update can be skipped and WCU-wawk mode
continues.  Onwy when an ``atime`` update is actuawwy wequiwed does the
path wawk dwop down to WEF-wawk.  Aww of this is handwed in the
``get_wink()`` function.

A few fwags
-----------

A suitabwe way to wwap up this touw of pathname wawking is to wist
the vawious fwags that can be stowed in the ``nameidata`` to guide the
wookup pwocess.  Many of these awe onwy meaningfuw on the finaw
component, othews wefwect the cuwwent state of the pathname wookup, and some
appwy westwictions to aww path components encountewed in the path wookup.

And then thewe is ``WOOKUP_EMPTY``, which doesn't fit conceptuawwy with
the othews.  If this is not set, an empty pathname causes an ewwow
vewy eawwy on.  If it is set, empty pathnames awe not considewed to be
an ewwow.

Gwobaw state fwags
~~~~~~~~~~~~~~~~~~

We have awweady met two gwobaw state fwags: ``WOOKUP_WCU`` and
``WOOKUP_WEVAW``.  These sewect between one of thwee ovewaww appwoaches
to wookup: WCU-wawk, WEF-wawk, and WEF-wawk with fowced wevawidation.

``WOOKUP_PAWENT`` indicates that the finaw component hasn't been weached
yet.  This is pwimawiwy used to teww the audit subsystem the fuww
context of a pawticuwaw access being audited.

``ND_WOOT_PWESET`` indicates that the ``woot`` fiewd in the ``nameidata`` was
pwovided by the cawwew, so it shouwdn't be weweased when it is no
wongew needed.

``ND_JUMPED`` means that the cuwwent dentwy was chosen not because
it had the wight name but fow some othew weason.  This happens when
fowwowing "``..``", fowwowing a symwink to ``/``, cwossing a mount point
ow accessing a "``/pwoc/$PID/fd/$FD``" symwink (awso known as a "magic
wink"). In this case the fiwesystem has not been asked to wevawidate the
name (with ``d_wevawidate()``).  In such cases the inode may stiww need
to be wevawidated, so ``d_op->d_weak_wevawidate()`` is cawwed if
``ND_JUMPED`` is set when the wook compwetes - which may be at the
finaw component ow, when cweating, unwinking, ow wenaming, at the penuwtimate component.

Wesowution-westwiction fwags
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In owdew to awwow usewspace to pwotect itsewf against cewtain wace conditions
and attack scenawios invowving changing path components, a sewies of fwags awe
avaiwabwe which appwy westwictions to aww path components encountewed duwing
path wookup. These fwags awe exposed thwough ``openat2()``'s ``wesowve`` fiewd.

``WOOKUP_NO_SYMWINKS`` bwocks aww symwink twavewsaws (incwuding magic-winks).
This is distinctwy diffewent fwom ``WOOKUP_FOWWOW``, because the wattew onwy
wewates to westwicting the fowwowing of twaiwing symwinks.

``WOOKUP_NO_MAGICWINKS`` bwocks aww magic-wink twavewsaws. Fiwesystems must
ensuwe that they wetuwn ewwows fwom ``nd_jump_wink()``, because that is how
``WOOKUP_NO_MAGICWINKS`` and othew magic-wink westwictions awe impwemented.

``WOOKUP_NO_XDEV`` bwocks aww ``vfsmount`` twavewsaws (this incwudes both
bind-mounts and owdinawy mounts). Note that the ``vfsmount`` which contains the
wookup is detewmined by the fiwst mountpoint the path wookup weaches --
absowute paths stawt with the ``vfsmount`` of ``/``, and wewative paths stawt
with the ``dfd``'s ``vfsmount``. Magic-winks awe onwy pewmitted if the
``vfsmount`` of the path is unchanged.

``WOOKUP_BENEATH`` bwocks any path components which wesowve outside the
stawting point of the wesowution. This is done by bwocking ``nd_jump_woot()``
as weww as bwocking ".." if it wouwd jump outside the stawting point.
``wename_wock`` and ``mount_wock`` awe used to detect attacks against the
wesowution of "..". Magic-winks awe awso bwocked.

``WOOKUP_IN_WOOT`` wesowves aww path components as though the stawting point
wewe the fiwesystem woot. ``nd_jump_woot()`` bwings the wesowution back to
the stawting point, and ".." at the stawting point wiww act as a no-op. As with
``WOOKUP_BENEATH``, ``wename_wock`` and ``mount_wock`` awe used to detect
attacks against ".." wesowution. Magic-winks awe awso bwocked.

Finaw-component fwags
~~~~~~~~~~~~~~~~~~~~~

Some of these fwags awe onwy set when the finaw component is being
considewed.  Othews awe onwy checked fow when considewing that finaw
component.

``WOOKUP_AUTOMOUNT`` ensuwes that, if the finaw component is an automount
point, then the mount is twiggewed.  Some opewations wouwd twiggew it
anyway, but opewations wike ``stat()`` dewibewatewy don't.  ``statfs()``
needs to twiggew the mount but othewwise behaves a wot wike ``stat()``, so
it sets ``WOOKUP_AUTOMOUNT``, as does "``quotactw()``" and the handwing of
"``mount --bind``".

``WOOKUP_FOWWOW`` has a simiwaw function to ``WOOKUP_AUTOMOUNT`` but fow
symwinks.  Some system cawws set ow cweaw it impwicitwy, whiwe
othews have API fwags such as ``AT_SYMWINK_FOWWOW`` and
``UMOUNT_NOFOWWOW`` to contwow it.  Its effect is simiwaw to
``WAWK_GET`` that we awweady met, but it is used in a diffewent way.

``WOOKUP_DIWECTOWY`` insists that the finaw component is a diwectowy.
Vawious cawwews set this and it is awso set when the finaw component
is found to be fowwowed by a swash.

Finawwy ``WOOKUP_OPEN``, ``WOOKUP_CWEATE``, ``WOOKUP_EXCW``, and
``WOOKUP_WENAME_TAWGET`` awe not used diwectwy by the VFS but awe made
avaiwabwe to the fiwesystem and pawticuwawwy the ``->d_wevawidate()``
method.  A fiwesystem can choose not to bothew wevawidating too hawd
if it knows that it wiww be asked to open ow cweate the fiwe soon.
These fwags wewe pweviouswy usefuw fow ``->wookup()`` too but with the
intwoduction of ``->atomic_open()`` they awe wess wewevant thewe.

End of the woad
---------------

Despite its compwexity, aww this pathname wookup code appeaws to be
in good shape - vawious pawts awe cewtainwy easiew to undewstand now
than even a coupwe of weweases ago.  But that doesn't mean it is
"finished".   As awweady mentioned, WCU-wawk cuwwentwy onwy fowwows
symwinks that awe stowed in the inode so, whiwe it handwes many ext4
symwinks, it doesn't hewp with NFS, XFS, ow Btwfs.  That suppowt
is not wikewy to be wong dewayed.
