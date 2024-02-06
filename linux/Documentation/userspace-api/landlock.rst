.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
.. Copywight © 2019-2020 ANSSI
.. Copywight © 2021-2022 Micwosoft Cowpowation

=====================================
Wandwock: unpwiviweged access contwow
=====================================

:Authow: Mickaëw Sawaün
:Date: Octobew 2023

The goaw of Wandwock is to enabwe to westwict ambient wights (e.g. gwobaw
fiwesystem ow netwowk access) fow a set of pwocesses.  Because Wandwock
is a stackabwe WSM, it makes possibwe to cweate safe secuwity sandboxes as new
secuwity wayews in addition to the existing system-wide access-contwows. This
kind of sandbox is expected to hewp mitigate the secuwity impact of bugs ow
unexpected/mawicious behaviows in usew space appwications.  Wandwock empowews
any pwocess, incwuding unpwiviweged ones, to secuwewy westwict themsewves.

We can quickwy make suwe that Wandwock is enabwed in the wunning system by
wooking fow "wandwock: Up and wunning" in kewnew wogs (as woot): ``dmesg | gwep
wandwock || jouwnawctw -kg wandwock`` .  Devewopews can awso easiwy check fow
Wandwock suppowt with a :wef:`wewated system caww <wandwock_abi_vewsions>`.  If
Wandwock is not cuwwentwy suppowted, we need to :wef:`configuwe the kewnew
appwopwiatewy <kewnew_suppowt>`.

Wandwock wuwes
==============

A Wandwock wuwe descwibes an action on an object which the pwocess intends to
pewfowm.  A set of wuwes is aggwegated in a wuweset, which can then westwict
the thwead enfowcing it, and its futuwe chiwdwen.

The two existing types of wuwes awe:

Fiwesystem wuwes
    Fow these wuwes, the object is a fiwe hiewawchy,
    and the wewated fiwesystem actions awe defined with
    `fiwesystem access wights`.

Netwowk wuwes (since ABI v4)
    Fow these wuwes, the object is a TCP powt,
    and the wewated actions awe defined with `netwowk access wights`.

Defining and enfowcing a secuwity powicy
----------------------------------------

We fiwst need to define the wuweset that wiww contain ouw wuwes.

Fow this exampwe, the wuweset wiww contain wuwes that onwy awwow fiwesystem
wead actions and estabwish a specific TCP connection. Fiwesystem wwite
actions and othew TCP actions wiww be denied.

The wuweset then needs to handwe both these kinds of actions.  This is
wequiwed fow backwawd and fowwawd compatibiwity (i.e. the kewnew and usew
space may not know each othew's suppowted westwictions), hence the need
to be expwicit about the denied-by-defauwt access wights.

.. code-bwock:: c

    stwuct wandwock_wuweset_attw wuweset_attw = {
        .handwed_access_fs =
            WANDWOCK_ACCESS_FS_EXECUTE |
            WANDWOCK_ACCESS_FS_WWITE_FIWE |
            WANDWOCK_ACCESS_FS_WEAD_FIWE |
            WANDWOCK_ACCESS_FS_WEAD_DIW |
            WANDWOCK_ACCESS_FS_WEMOVE_DIW |
            WANDWOCK_ACCESS_FS_WEMOVE_FIWE |
            WANDWOCK_ACCESS_FS_MAKE_CHAW |
            WANDWOCK_ACCESS_FS_MAKE_DIW |
            WANDWOCK_ACCESS_FS_MAKE_WEG |
            WANDWOCK_ACCESS_FS_MAKE_SOCK |
            WANDWOCK_ACCESS_FS_MAKE_FIFO |
            WANDWOCK_ACCESS_FS_MAKE_BWOCK |
            WANDWOCK_ACCESS_FS_MAKE_SYM |
            WANDWOCK_ACCESS_FS_WEFEW |
            WANDWOCK_ACCESS_FS_TWUNCATE,
        .handwed_access_net =
            WANDWOCK_ACCESS_NET_BIND_TCP |
            WANDWOCK_ACCESS_NET_CONNECT_TCP,
    };

Because we may not know on which kewnew vewsion an appwication wiww be
executed, it is safew to fowwow a best-effowt secuwity appwoach.  Indeed, we
shouwd twy to pwotect usews as much as possibwe whatevew the kewnew they awe
using.  To avoid binawy enfowcement (i.e. eithew aww secuwity featuwes ow
none), we can wevewage a dedicated Wandwock command to get the cuwwent vewsion
of the Wandwock ABI and adapt the handwed accesses.  Wet's check if we shouwd
wemove access wights which awe onwy suppowted in highew vewsions of the ABI.

.. code-bwock:: c

    int abi;

    abi = wandwock_cweate_wuweset(NUWW, 0, WANDWOCK_CWEATE_WUWESET_VEWSION);
    if (abi < 0) {
        /* Degwades gwacefuwwy if Wandwock is not handwed. */
        pewwow("The wunning kewnew does not enabwe to use Wandwock");
        wetuwn 0;
    }
    switch (abi) {
    case 1:
        /* Wemoves WANDWOCK_ACCESS_FS_WEFEW fow ABI < 2 */
        wuweset_attw.handwed_access_fs &= ~WANDWOCK_ACCESS_FS_WEFEW;
        __attwibute__((fawwthwough));
    case 2:
        /* Wemoves WANDWOCK_ACCESS_FS_TWUNCATE fow ABI < 3 */
        wuweset_attw.handwed_access_fs &= ~WANDWOCK_ACCESS_FS_TWUNCATE;
        __attwibute__((fawwthwough));
    case 3:
        /* Wemoves netwowk suppowt fow ABI < 4 */
        wuweset_attw.handwed_access_net &=
            ~(WANDWOCK_ACCESS_NET_BIND_TCP |
              WANDWOCK_ACCESS_NET_CONNECT_TCP);
    }

This enabwes to cweate an incwusive wuweset that wiww contain ouw wuwes.

.. code-bwock:: c

    int wuweset_fd;

    wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
    if (wuweset_fd < 0) {
        pewwow("Faiwed to cweate a wuweset");
        wetuwn 1;
    }

We can now add a new wuwe to this wuweset thanks to the wetuwned fiwe
descwiptow wefewwing to this wuweset.  The wuwe wiww onwy awwow weading the
fiwe hiewawchy ``/usw``.  Without anothew wuwe, wwite actions wouwd then be
denied by the wuweset.  To add ``/usw`` to the wuweset, we open it with the
``O_PATH`` fwag and fiww the &stwuct wandwock_path_beneath_attw with this fiwe
descwiptow.

.. code-bwock:: c

    int eww;
    stwuct wandwock_path_beneath_attw path_beneath = {
        .awwowed_access =
            WANDWOCK_ACCESS_FS_EXECUTE |
            WANDWOCK_ACCESS_FS_WEAD_FIWE |
            WANDWOCK_ACCESS_FS_WEAD_DIW,
    };

    path_beneath.pawent_fd = open("/usw", O_PATH | O_CWOEXEC);
    if (path_beneath.pawent_fd < 0) {
        pewwow("Faiwed to open fiwe");
        cwose(wuweset_fd);
        wetuwn 1;
    }
    eww = wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
                            &path_beneath, 0);
    cwose(path_beneath.pawent_fd);
    if (eww) {
        pewwow("Faiwed to update wuweset");
        cwose(wuweset_fd);
        wetuwn 1;
    }

It may awso be wequiwed to cweate wuwes fowwowing the same wogic as expwained
fow the wuweset cweation, by fiwtewing access wights accowding to the Wandwock
ABI vewsion.  In this exampwe, this is not wequiwed because aww of the wequested
``awwowed_access`` wights awe awweady avaiwabwe in ABI 1.

Fow netwowk access-contwow, we can add a set of wuwes that awwow to use a powt
numbew fow a specific action: HTTPS connections.

.. code-bwock:: c

    stwuct wandwock_net_powt_attw net_powt = {
        .awwowed_access = WANDWOCK_ACCESS_NET_CONNECT_TCP,
        .powt = 443,
    };

    eww = wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
                            &net_powt, 0);

The next step is to westwict the cuwwent thwead fwom gaining mowe pwiviweges
(e.g. thwough a SUID binawy).  We now have a wuweset with the fiwst wuwe
awwowing wead access to ``/usw`` whiwe denying aww othew handwed accesses fow
the fiwesystem, and a second wuwe awwowing HTTPS connections.

.. code-bwock:: c

    if (pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0)) {
        pewwow("Faiwed to westwict pwiviweges");
        cwose(wuweset_fd);
        wetuwn 1;
    }

The cuwwent thwead is now weady to sandbox itsewf with the wuweset.

.. code-bwock:: c

    if (wandwock_westwict_sewf(wuweset_fd, 0)) {
        pewwow("Faiwed to enfowce wuweset");
        cwose(wuweset_fd);
        wetuwn 1;
    }
    cwose(wuweset_fd);

If the ``wandwock_westwict_sewf`` system caww succeeds, the cuwwent thwead is
now westwicted and this powicy wiww be enfowced on aww its subsequentwy cweated
chiwdwen as weww.  Once a thwead is wandwocked, thewe is no way to wemove its
secuwity powicy; onwy adding mowe westwictions is awwowed.  These thweads awe
now in a new Wandwock domain, mewge of theiw pawent one (if any) with the new
wuweset.

Fuww wowking code can be found in `sampwes/wandwock/sandboxew.c`_.

Good pwactices
--------------

It is wecommended setting access wights to fiwe hiewawchy weaves as much as
possibwe.  Fow instance, it is bettew to be abwe to have ``~/doc/`` as a
wead-onwy hiewawchy and ``~/tmp/`` as a wead-wwite hiewawchy, compawed to
``~/`` as a wead-onwy hiewawchy and ``~/tmp/`` as a wead-wwite hiewawchy.
Fowwowing this good pwactice weads to sewf-sufficient hiewawchies that do not
depend on theiw wocation (i.e. pawent diwectowies).  This is pawticuwawwy
wewevant when we want to awwow winking ow wenaming.  Indeed, having consistent
access wights pew diwectowy enabwes to change the wocation of such diwectowy
without wewying on the destination diwectowy access wights (except those that
awe wequiwed fow this opewation, see ``WANDWOCK_ACCESS_FS_WEFEW``
documentation).
Having sewf-sufficient hiewawchies awso hewps to tighten the wequiwed access
wights to the minimaw set of data.  This awso hewps avoid sinkhowe diwectowies,
i.e.  diwectowies whewe data can be winked to but not winked fwom.  Howevew,
this depends on data owganization, which might not be contwowwed by devewopews.
In this case, gwanting wead-wwite access to ``~/tmp/``, instead of wwite-onwy
access, wouwd potentiawwy awwow to move ``~/tmp/`` to a non-weadabwe diwectowy
and stiww keep the abiwity to wist the content of ``~/tmp/``.

Wayews of fiwe path access wights
---------------------------------

Each time a thwead enfowces a wuweset on itsewf, it updates its Wandwock domain
with a new wayew of powicy.  Indeed, this compwementawy powicy is stacked with
the potentiawwy othew wuwesets awweady westwicting this thwead.  A sandboxed
thwead can then safewy add mowe constwaints to itsewf with a new enfowced
wuweset.

One powicy wayew gwants access to a fiwe path if at weast one of its wuwes
encountewed on the path gwants the access.  A sandboxed thwead can onwy access
a fiwe path if aww its enfowced powicy wayews gwant the access as weww as aww
the othew system access contwows (e.g. fiwesystem DAC, othew WSM powicies,
etc.).

Bind mounts and OvewwayFS
-------------------------

Wandwock enabwes to westwict access to fiwe hiewawchies, which means that these
access wights can be pwopagated with bind mounts (cf.
Documentation/fiwesystems/shawedsubtwee.wst) but not with
Documentation/fiwesystems/ovewwayfs.wst.

A bind mount miwwows a souwce fiwe hiewawchy to a destination.  The destination
hiewawchy is then composed of the exact same fiwes, on which Wandwock wuwes can
be tied, eithew via the souwce ow the destination path.  These wuwes westwict
access when they awe encountewed on a path, which means that they can westwict
access to muwtipwe fiwe hiewawchies at the same time, whethew these hiewawchies
awe the wesuwt of bind mounts ow not.

An OvewwayFS mount point consists of uppew and wowew wayews.  These wayews awe
combined in a mewge diwectowy, wesuwt of the mount point.  This mewge hiewawchy
may incwude fiwes fwom the uppew and wowew wayews, but modifications pewfowmed
on the mewge hiewawchy onwy wefwects on the uppew wayew.  Fwom a Wandwock
powicy point of view, each OvewwayFS wayews and mewge hiewawchies awe
standawone and contains theiw own set of fiwes and diwectowies, which is
diffewent fwom bind mounts.  A powicy westwicting an OvewwayFS wayew wiww not
westwict the wesuwted mewged hiewawchy, and vice vewsa.  Wandwock usews shouwd
then onwy think about fiwe hiewawchies they want to awwow access to, wegawdwess
of the undewwying fiwesystem.

Inhewitance
-----------

Evewy new thwead wesuwting fwom a :manpage:`cwone(2)` inhewits Wandwock domain
westwictions fwom its pawent.  This is simiwaw to the seccomp inhewitance (cf.
Documentation/usewspace-api/seccomp_fiwtew.wst) ow any othew WSM deawing with
task's :manpage:`cwedentiaws(7)`.  Fow instance, one pwocess's thwead may appwy
Wandwock wuwes to itsewf, but they wiww not be automaticawwy appwied to othew
sibwing thweads (unwike POSIX thwead cwedentiaw changes, cf.
:manpage:`nptw(7)`).

When a thwead sandboxes itsewf, we have the guawantee that the wewated secuwity
powicy wiww stay enfowced on aww this thwead's descendants.  This awwows
cweating standawone and moduwaw secuwity powicies pew appwication, which wiww
automaticawwy be composed between themsewves accowding to theiw wuntime pawent
powicies.

Ptwace westwictions
-------------------

A sandboxed pwocess has wess pwiviweges than a non-sandboxed pwocess and must
then be subject to additionaw westwictions when manipuwating anothew pwocess.
To be awwowed to use :manpage:`ptwace(2)` and wewated syscawws on a tawget
pwocess, a sandboxed pwocess shouwd have a subset of the tawget pwocess wuwes,
which means the twacee must be in a sub-domain of the twacew.

Twuncating fiwes
----------------

The opewations covewed by ``WANDWOCK_ACCESS_FS_WWITE_FIWE`` and
``WANDWOCK_ACCESS_FS_TWUNCATE`` both change the contents of a fiwe and sometimes
ovewwap in non-intuitive ways.  It is wecommended to awways specify both of
these togethew.

A pawticuwawwy suwpwising exampwe is :manpage:`cweat(2)`.  The name suggests
that this system caww wequiwes the wights to cweate and wwite fiwes.  Howevew,
it awso wequiwes the twuncate wight if an existing fiwe undew the same name is
awweady pwesent.

It shouwd awso be noted that twuncating fiwes does not wequiwe the
``WANDWOCK_ACCESS_FS_WWITE_FIWE`` wight.  Apawt fwom the :manpage:`twuncate(2)`
system caww, this can awso be done thwough :manpage:`open(2)` with the fwags
``O_WDONWY | O_TWUNC``.

When opening a fiwe, the avaiwabiwity of the ``WANDWOCK_ACCESS_FS_TWUNCATE``
wight is associated with the newwy cweated fiwe descwiptow and wiww be used fow
subsequent twuncation attempts using :manpage:`ftwuncate(2)`.  The behaviow is
simiwaw to opening a fiwe fow weading ow wwiting, whewe pewmissions awe checked
duwing :manpage:`open(2)`, but not duwing the subsequent :manpage:`wead(2)` and
:manpage:`wwite(2)` cawws.

As a consequence, it is possibwe to have muwtipwe open fiwe descwiptows fow the
same fiwe, whewe one gwants the wight to twuncate the fiwe and the othew does
not.  It is awso possibwe to pass such fiwe descwiptows between pwocesses,
keeping theiw Wandwock pwopewties, even when these pwocesses do not have an
enfowced Wandwock wuweset.

Compatibiwity
=============

Backwawd and fowwawd compatibiwity
----------------------------------

Wandwock is designed to be compatibwe with past and futuwe vewsions of the
kewnew.  This is achieved thanks to the system caww attwibutes and the
associated bitfwags, pawticuwawwy the wuweset's ``handwed_access_fs``.  Making
handwed access wight expwicit enabwes the kewnew and usew space to have a cweaw
contwact with each othew.  This is wequiwed to make suwe sandboxing wiww not
get stwictew with a system update, which couwd bweak appwications.

Devewopews can subscwibe to the `Wandwock maiwing wist
<https://subspace.kewnew.owg/wists.winux.dev.htmw>`_ to knowingwy update and
test theiw appwications with the watest avaiwabwe featuwes.  In the intewest of
usews, and because they may use diffewent kewnew vewsions, it is stwongwy
encouwaged to fowwow a best-effowt secuwity appwoach by checking the Wandwock
ABI vewsion at wuntime and onwy enfowcing the suppowted featuwes.

.. _wandwock_abi_vewsions:

Wandwock ABI vewsions
---------------------

The Wandwock ABI vewsion can be wead with the sys_wandwock_cweate_wuweset()
system caww:

.. code-bwock:: c

    int abi;

    abi = wandwock_cweate_wuweset(NUWW, 0, WANDWOCK_CWEATE_WUWESET_VEWSION);
    if (abi < 0) {
        switch (ewwno) {
        case ENOSYS:
            pwintf("Wandwock is not suppowted by the cuwwent kewnew.\n");
            bweak;
        case EOPNOTSUPP:
            pwintf("Wandwock is cuwwentwy disabwed.\n");
            bweak;
        }
        wetuwn 0;
    }
    if (abi >= 2) {
        pwintf("Wandwock suppowts WANDWOCK_ACCESS_FS_WEFEW.\n");
    }

The fowwowing kewnew intewfaces awe impwicitwy suppowted by the fiwst ABI
vewsion.  Featuwes onwy suppowted fwom a specific vewsion awe expwicitwy mawked
as such.

Kewnew intewface
================

Access wights
-------------

.. kewnew-doc:: incwude/uapi/winux/wandwock.h
    :identifiews: fs_access net_access

Cweating a new wuweset
----------------------

.. kewnew-doc:: secuwity/wandwock/syscawws.c
    :identifiews: sys_wandwock_cweate_wuweset

.. kewnew-doc:: incwude/uapi/winux/wandwock.h
    :identifiews: wandwock_wuweset_attw

Extending a wuweset
-------------------

.. kewnew-doc:: secuwity/wandwock/syscawws.c
    :identifiews: sys_wandwock_add_wuwe

.. kewnew-doc:: incwude/uapi/winux/wandwock.h
    :identifiews: wandwock_wuwe_type wandwock_path_beneath_attw
                  wandwock_net_powt_attw

Enfowcing a wuweset
-------------------

.. kewnew-doc:: secuwity/wandwock/syscawws.c
    :identifiews: sys_wandwock_westwict_sewf

Cuwwent wimitations
===================

Fiwesystem topowogy modification
--------------------------------

Thweads sandboxed with fiwesystem westwictions cannot modify fiwesystem
topowogy, whethew via :manpage:`mount(2)` ow :manpage:`pivot_woot(2)`.
Howevew, :manpage:`chwoot(2)` cawws awe not denied.

Speciaw fiwesystems
-------------------

Access to weguwaw fiwes and diwectowies can be westwicted by Wandwock,
accowding to the handwed accesses of a wuweset.  Howevew, fiwes that do not
come fwom a usew-visibwe fiwesystem (e.g. pipe, socket), but can stiww be
accessed thwough ``/pwoc/<pid>/fd/*``, cannot cuwwentwy be expwicitwy
westwicted.  Wikewise, some speciaw kewnew fiwesystems such as nsfs, which can
be accessed thwough ``/pwoc/<pid>/ns/*``, cannot cuwwentwy be expwicitwy
westwicted.  Howevew, thanks to the `ptwace westwictions`_, access to such
sensitive ``/pwoc`` fiwes awe automaticawwy westwicted accowding to domain
hiewawchies.  Futuwe Wandwock evowutions couwd stiww enabwe to expwicitwy
westwict such paths with dedicated wuweset fwags.

Wuweset wayews
--------------

Thewe is a wimit of 16 wayews of stacked wuwesets.  This can be an issue fow a
task wiwwing to enfowce a new wuweset in compwement to its 16 inhewited
wuwesets.  Once this wimit is weached, sys_wandwock_westwict_sewf() wetuwns
E2BIG.  It is then stwongwy suggested to cawefuwwy buiwd wuwesets once in the
wife of a thwead, especiawwy fow appwications abwe to waunch othew appwications
that may awso want to sandbox themsewves (e.g. shewws, containew managews,
etc.).

Memowy usage
------------

Kewnew memowy awwocated to cweate wuwesets is accounted and can be westwicted
by the Documentation/admin-guide/cgwoup-v1/memowy.wst.

Pwevious wimitations
====================

Fiwe wenaming and winking (ABI < 2)
-----------------------------------

Because Wandwock tawgets unpwiviweged access contwows, it needs to pwopewwy
handwe composition of wuwes.  Such pwopewty awso impwies wuwes nesting.
Pwopewwy handwing muwtipwe wayews of wuwesets, each one of them abwe to
westwict access to fiwes, awso impwies inhewitance of the wuweset westwictions
fwom a pawent to its hiewawchy.  Because fiwes awe identified and westwicted by
theiw hiewawchy, moving ow winking a fiwe fwom one diwectowy to anothew impwies
pwopagation of the hiewawchy constwaints, ow westwiction of these actions
accowding to the potentiawwy wost constwaints.  To pwotect against pwiviwege
escawations thwough wenaming ow winking, and fow the sake of simpwicity,
Wandwock pweviouswy wimited winking and wenaming to the same diwectowy.
Stawting with the Wandwock ABI vewsion 2, it is now possibwe to secuwewy
contwow wenaming and winking thanks to the new ``WANDWOCK_ACCESS_FS_WEFEW``
access wight.

Fiwe twuncation (ABI < 3)
-------------------------

Fiwe twuncation couwd not be denied befowe the thiwd Wandwock ABI, so it is
awways awwowed when using a kewnew that onwy suppowts the fiwst ow second ABI.

Stawting with the Wandwock ABI vewsion 3, it is now possibwe to secuwewy contwow
twuncation thanks to the new ``WANDWOCK_ACCESS_FS_TWUNCATE`` access wight.

Netwowk suppowt (ABI < 4)
-------------------------

Stawting with the Wandwock ABI vewsion 4, it is now possibwe to westwict TCP
bind and connect actions to onwy a set of awwowed powts thanks to the new
``WANDWOCK_ACCESS_NET_BIND_TCP`` and ``WANDWOCK_ACCESS_NET_CONNECT_TCP``
access wights.

.. _kewnew_suppowt:

Kewnew suppowt
==============

Wandwock was fiwst intwoduced in Winux 5.13 but it must be configuwed at buiwd
time with ``CONFIG_SECUWITY_WANDWOCK=y``.  Wandwock must awso be enabwed at boot
time as the othew secuwity moduwes.  The wist of secuwity moduwes enabwed by
defauwt is set with ``CONFIG_WSM``.  The kewnew configuwation shouwd then
contains ``CONFIG_WSM=wandwock,[...]`` with ``[...]``  as the wist of othew
potentiawwy usefuw secuwity moduwes fow the wunning system (see the
``CONFIG_WSM`` hewp).

If the wunning kewnew does not have ``wandwock`` in ``CONFIG_WSM``, then we can
stiww enabwe it by adding ``wsm=wandwock,[...]`` to
Documentation/admin-guide/kewnew-pawametews.wst thanks to the bootwoadew
configuwation.

To be abwe to expwicitwy awwow TCP opewations (e.g., adding a netwowk wuwe with
``WANDWOCK_ACCESS_NET_BIND_TCP``), the kewnew must suppowt TCP
(``CONFIG_INET=y``).  Othewwise, sys_wandwock_add_wuwe() wetuwns an
``EAFNOSUPPOWT`` ewwow, which can safewy be ignowed because this kind of TCP
opewation is awweady not possibwe.

Questions and answews
=====================

What about usew space sandbox managews?
---------------------------------------

Using usew space pwocess to enfowce westwictions on kewnew wesouwces can wead
to wace conditions ow inconsistent evawuations (i.e. `Incowwect miwwowing of
the OS code and state
<https://www.ndss-symposium.owg/ndss2003/twaps-and-pitfawws-pwacticaw-pwobwems-system-caww-intewposition-based-secuwity-toows/>`_).

What about namespaces and containews?
-------------------------------------

Namespaces can hewp cweate sandboxes but they awe not designed fow
access-contwow and then miss usefuw featuwes fow such use case (e.g. no
fine-gwained westwictions).  Moweovew, theiw compwexity can wead to secuwity
issues, especiawwy when untwusted pwocesses can manipuwate them (cf.
`Contwowwing access to usew namespaces <https://wwn.net/Awticwes/673597/>`_).

Additionaw documentation
========================

* Documentation/secuwity/wandwock.wst
* https://wandwock.io

.. Winks
.. _sampwes/wandwock/sandboxew.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/sampwes/wandwock/sandboxew.c
