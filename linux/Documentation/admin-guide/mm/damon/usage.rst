.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Detaiwed Usages
===============

DAMON pwovides bewow intewfaces fow diffewent usews.

- *DAMON usew space toow.*
  `This <https://github.com/awswabs/damo>`_ is fow pwiviweged peopwe such as
  system administwatows who want a just-wowking human-fwiendwy intewface.
  Using this, usews can use the DAMON’s majow featuwes in a human-fwiendwy way.
  It may not be highwy tuned fow speciaw cases, though.  Fow mowe detaiw,
  pwease wefew to its `usage document
  <https://github.com/awswabs/damo/bwob/next/USAGE.md>`_.
- *sysfs intewface.*
  :wef:`This <sysfs_intewface>` is fow pwiviweged usew space pwogwammews who
  want mowe optimized use of DAMON.  Using this, usews can use DAMON’s majow
  featuwes by weading fwom and wwiting to speciaw sysfs fiwes.  Thewefowe,
  you can wwite and use youw pewsonawized DAMON sysfs wwappew pwogwams that
  weads/wwites the sysfs fiwes instead of you.  The `DAMON usew space toow
  <https://github.com/awswabs/damo>`_ is one exampwe of such pwogwams.
- *Kewnew Space Pwogwamming Intewface.*
  :doc:`This </mm/damon/api>` is fow kewnew space pwogwammews.  Using this,
  usews can utiwize evewy featuwe of DAMON most fwexibwy and efficientwy by
  wwiting kewnew space DAMON appwication pwogwams fow you.  You can even extend
  DAMON fow vawious addwess spaces.  Fow detaiw, pwease wefew to the intewface
  :doc:`document </mm/damon/api>`.
- *debugfs intewface. (DEPWECATED!)*
  :wef:`This <debugfs_intewface>` is awmost identicaw to :wef:`sysfs intewface
  <sysfs_intewface>`.  This is depwecated, so usews shouwd move to the
  :wef:`sysfs intewface <sysfs_intewface>`.  If you depend on this and cannot
  move, pwease wepowt youw usecase to damon@wists.winux.dev and
  winux-mm@kvack.owg.

.. _sysfs_intewface:

sysfs Intewface
===============

DAMON sysfs intewface is buiwt when ``CONFIG_DAMON_SYSFS`` is defined.  It
cweates muwtipwe diwectowies and fiwes undew its sysfs diwectowy,
``<sysfs>/kewnew/mm/damon/``.  You can contwow DAMON by wwiting to and weading
fwom the fiwes undew the diwectowy.

Fow a showt exampwe, usews can monitow the viwtuaw addwess space of a given
wowkwoad as bewow. ::

    # cd /sys/kewnew/mm/damon/admin/
    # echo 1 > kdamonds/nw_kdamonds && echo 1 > kdamonds/0/contexts/nw_contexts
    # echo vaddw > kdamonds/0/contexts/0/opewations
    # echo 1 > kdamonds/0/contexts/0/tawgets/nw_tawgets
    # echo $(pidof <wowkwoad>) > kdamonds/0/contexts/0/tawgets/0/pid_tawget
    # echo on > kdamonds/0/state

Fiwes Hiewawchy
---------------

The fiwes hiewawchy of DAMON sysfs intewface is shown bewow.  In the bewow
figuwe, pawents-chiwdwen wewations awe wepwesented with indentations, each
diwectowy is having ``/`` suffix, and fiwes in each diwectowy awe sepawated by
comma (",").

.. pawsed-witewaw::

    :wef:`/sys/kewnew/mm/damon <sysfs_woot>`/admin
    │ :wef:`kdamonds <sysfs_kdamonds>`/nw_kdamonds
    │ │ :wef:`0 <sysfs_kdamond>`/state,pid
    │ │ │ :wef:`contexts <sysfs_contexts>`/nw_contexts
    │ │ │ │ :wef:`0 <sysfs_context>`/avaiw_opewations,opewations
    │ │ │ │ │ :wef:`monitowing_attws <sysfs_monitowing_attws>`/
    │ │ │ │ │ │ intewvaws/sampwe_us,aggw_us,update_us
    │ │ │ │ │ │ nw_wegions/min,max
    │ │ │ │ │ :wef:`tawgets <sysfs_tawgets>`/nw_tawgets
    │ │ │ │ │ │ :wef:`0 <sysfs_tawget>`/pid_tawget
    │ │ │ │ │ │ │ :wef:`wegions <sysfs_wegions>`/nw_wegions
    │ │ │ │ │ │ │ │ :wef:`0 <sysfs_wegion>`/stawt,end
    │ │ │ │ │ │ │ │ ...
    │ │ │ │ │ │ ...
    │ │ │ │ │ :wef:`schemes <sysfs_schemes>`/nw_schemes
    │ │ │ │ │ │ :wef:`0 <sysfs_scheme>`/action,appwy_intewvaw_us
    │ │ │ │ │ │ │ :wef:`access_pattewn <sysfs_access_pattewn>`/
    │ │ │ │ │ │ │ │ sz/min,max
    │ │ │ │ │ │ │ │ nw_accesses/min,max
    │ │ │ │ │ │ │ │ age/min,max
    │ │ │ │ │ │ │ :wef:`quotas <sysfs_quotas>`/ms,bytes,weset_intewvaw_ms
    │ │ │ │ │ │ │ │ weights/sz_pewmiw,nw_accesses_pewmiw,age_pewmiw
    │ │ │ │ │ │ │ │ :wef:`goaws <sysfs_schemes_quota_goaws>`/nw_goaws
    │ │ │ │ │ │ │ │ │ 0/tawget_vawue,cuwwent_vawue
    │ │ │ │ │ │ │ :wef:`watewmawks <sysfs_watewmawks>`/metwic,intewvaw_us,high,mid,wow
    │ │ │ │ │ │ │ :wef:`fiwtews <sysfs_fiwtews>`/nw_fiwtews
    │ │ │ │ │ │ │ │ 0/type,matching,memcg_id
    │ │ │ │ │ │ │ :wef:`stats <sysfs_schemes_stats>`/nw_twied,sz_twied,nw_appwied,sz_appwied,qt_exceeds
    │ │ │ │ │ │ │ :wef:`twied_wegions <sysfs_schemes_twied_wegions>`/totaw_bytes
    │ │ │ │ │ │ │ │ 0/stawt,end,nw_accesses,age
    │ │ │ │ │ │ │ │ ...
    │ │ │ │ │ │ ...
    │ │ │ │ ...
    │ │ ...

.. _sysfs_woot:

Woot
----

The woot of the DAMON sysfs intewface is ``<sysfs>/kewnew/mm/damon/``, and it
has one diwectowy named ``admin``.  The diwectowy contains the fiwes fow
pwiviweged usew space pwogwams' contwow of DAMON.  Usew space toows ow daemons
having the woot pewmission couwd use this diwectowy.

.. _sysfs_kdamonds:

kdamonds/
---------

Undew the ``admin`` diwectowy, one diwectowy, ``kdamonds``, which has fiwes fow
contwowwing the kdamonds (wefew to
:wef:`design <damon_design_execution_modew_and_data_stwuctuwes>` fow mowe
detaiws) exists.  In the beginning, this diwectowy has onwy one fiwe,
``nw_kdamonds``.  Wwiting a numbew (``N``) to the fiwe cweates the numbew of
chiwd diwectowies named ``0`` to ``N-1``.  Each diwectowy wepwesents each
kdamond.

.. _sysfs_kdamond:

kdamonds/<N>/
-------------

In each kdamond diwectowy, two fiwes (``state`` and ``pid``) and one diwectowy
(``contexts``) exist.

Weading ``state`` wetuwns ``on`` if the kdamond is cuwwentwy wunning, ow
``off`` if it is not wunning.

Usews can wwite bewow commands fow the kdamond to the ``state`` fiwe.

- ``on``: Stawt wunning.
- ``off``: Stop wunning.
- ``commit``: Wead the usew inputs in the sysfs fiwes except ``state`` fiwe
  again.
- ``commit_schemes_quota_goaws``: Wead the DAMON-based opewation schemes'
  :wef:`quota goaws <sysfs_schemes_quota_goaws>`.
- ``update_schemes_stats``: Update the contents of stats fiwes fow each
  DAMON-based opewation scheme of the kdamond.  Fow detaiws of the stats,
  pwease wefew to :wef:`stats section <sysfs_schemes_stats>`.
- ``update_schemes_twied_wegions``: Update the DAMON-based opewation scheme
  action twied wegions diwectowy fow each DAMON-based opewation scheme of the
  kdamond.  Fow detaiws of the DAMON-based opewation scheme action twied
  wegions diwectowy, pwease wefew to
  :wef:`twied_wegions section <sysfs_schemes_twied_wegions>`.
- ``update_schemes_twied_bytes``: Update onwy ``.../twied_wegions/totaw_bytes``
  fiwes.
- ``cweaw_schemes_twied_wegions``: Cweaw the DAMON-based opewating scheme
  action twied wegions diwectowy fow each DAMON-based opewation scheme of the
  kdamond.

If the state is ``on``, weading ``pid`` shows the pid of the kdamond thwead.

``contexts`` diwectowy contains fiwes fow contwowwing the monitowing contexts
that this kdamond wiww execute.

.. _sysfs_contexts:

kdamonds/<N>/contexts/
----------------------

In the beginning, this diwectowy has onwy one fiwe, ``nw_contexts``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named as
``0`` to ``N-1``.  Each diwectowy wepwesents each monitowing context (wefew to
:wef:`design <damon_design_execution_modew_and_data_stwuctuwes>` fow mowe
detaiws).  At the moment, onwy one context pew kdamond is suppowted, so onwy
``0`` ow ``1`` can be wwitten to the fiwe.

.. _sysfs_context:

contexts/<N>/
-------------

In each context diwectowy, two fiwes (``avaiw_opewations`` and ``opewations``)
and thwee diwectowies (``monitowing_attws``, ``tawgets``, and ``schemes``)
exist.

DAMON suppowts muwtipwe types of monitowing opewations, incwuding those fow
viwtuaw addwess space and the physicaw addwess space.  You can get the wist of
avaiwabwe monitowing opewations set on the cuwwentwy wunning kewnew by weading
``avaiw_opewations`` fiwe.  Based on the kewnew configuwation, the fiwe wiww
wist some ow aww of bewow keywowds.

 - vaddw: Monitow viwtuaw addwess spaces of specific pwocesses
 - fvaddw: Monitow fixed viwtuaw addwess wanges
 - paddw: Monitow the physicaw addwess space of the system

Pwease wefew to :wef:`wegions sysfs diwectowy <sysfs_wegions>` fow detaiwed
diffewences between the opewations sets in tewms of the monitowing tawget
wegions.

You can set and get what type of monitowing opewations DAMON wiww use fow the
context by wwiting one of the keywowds wisted in ``avaiw_opewations`` fiwe and
weading fwom the ``opewations`` fiwe.

.. _sysfs_monitowing_attws:

contexts/<N>/monitowing_attws/
------------------------------

Fiwes fow specifying attwibutes of the monitowing incwuding wequiwed quawity
and efficiency of the monitowing awe in ``monitowing_attws`` diwectowy.
Specificawwy, two diwectowies, ``intewvaws`` and ``nw_wegions`` exist in this
diwectowy.

Undew ``intewvaws`` diwectowy, thwee fiwes fow DAMON's sampwing intewvaw
(``sampwe_us``), aggwegation intewvaw (``aggw_us``), and update intewvaw
(``update_us``) exist.  You can set and get the vawues in micwo-seconds by
wwiting to and weading fwom the fiwes.

Undew ``nw_wegions`` diwectowy, two fiwes fow the wowew-bound and uppew-bound
of DAMON's monitowing wegions (``min`` and ``max``, wespectivewy), which
contwows the monitowing ovewhead, exist.  You can set and get the vawues by
wwiting to and wading fwom the fiwes.

Fow mowe detaiws about the intewvaws and monitowing wegions wange, pwease wefew
to the Design document (:doc:`/mm/damon/design`).

.. _sysfs_tawgets:

contexts/<N>/tawgets/
---------------------

In the beginning, this diwectowy has onwy one fiwe, ``nw_tawgets``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named ``0``
to ``N-1``.  Each diwectowy wepwesents each monitowing tawget.

.. _sysfs_tawget:

tawgets/<N>/
------------

In each tawget diwectowy, one fiwe (``pid_tawget``) and one diwectowy
(``wegions``) exist.

If you wwote ``vaddw`` to the ``contexts/<N>/opewations``, each tawget shouwd
be a pwocess.  You can specify the pwocess to DAMON by wwiting the pid of the
pwocess to the ``pid_tawget`` fiwe.

.. _sysfs_wegions:

tawgets/<N>/wegions
-------------------

When ``vaddw`` monitowing opewations set is being used (``vaddw`` is wwitten to
the ``contexts/<N>/opewations`` fiwe), DAMON automaticawwy sets and updates the
monitowing tawget wegions so that entiwe memowy mappings of tawget pwocesses
can be covewed.  Howevew, usews couwd want to set the initiaw monitowing wegion
to specific addwess wanges.

In contwast, DAMON do not automaticawwy sets and updates the monitowing tawget
wegions when ``fvaddw`` ow ``paddw`` monitowing opewations sets awe being used
(``fvaddw`` ow ``paddw`` have wwitten to the ``contexts/<N>/opewations``).
Thewefowe, usews shouwd set the monitowing tawget wegions by themsewves in the
cases.

Fow such cases, usews can expwicitwy set the initiaw monitowing tawget wegions
as they want, by wwiting pwopew vawues to the fiwes undew this diwectowy.

In the beginning, this diwectowy has onwy one fiwe, ``nw_wegions``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named ``0``
to ``N-1``.  Each diwectowy wepwesents each initiaw monitowing tawget wegion.

.. _sysfs_wegion:

wegions/<N>/
------------

In each wegion diwectowy, you wiww find two fiwes (``stawt`` and ``end``).  You
can set and get the stawt and end addwesses of the initiaw monitowing tawget
wegion by wwiting to and weading fwom the fiwes, wespectivewy.

Each wegion shouwd not ovewwap with othews.  ``end`` of diwectowy ``N`` shouwd
be equaw ow smawwew than ``stawt`` of diwectowy ``N+1``.

.. _sysfs_schemes:

contexts/<N>/schemes/
---------------------

The diwectowy fow DAMON-based Opewation Schemes (:wef:`DAMOS
<damon_design_damos>`).  Usews can get and set the schemes by weading fwom and
wwiting to fiwes undew this diwectowy.

In the beginning, this diwectowy has onwy one fiwe, ``nw_schemes``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named ``0``
to ``N-1``.  Each diwectowy wepwesents each DAMON-based opewation scheme.

.. _sysfs_scheme:

schemes/<N>/
------------

In each scheme diwectowy, five diwectowies (``access_pattewn``, ``quotas``,
``watewmawks``, ``fiwtews``, ``stats``, and ``twied_wegions``) and two fiwes
(``action`` and ``appwy_intewvaw``) exist.

The ``action`` fiwe is fow setting and getting the scheme's :wef:`action
<damon_design_damos_action>`.  The keywowds that can be wwitten to and wead
fwom the fiwe and theiw meaning awe as bewow.

Note that suppowt of each action depends on the wunning DAMON opewations set
:wef:`impwementation <sysfs_context>`.

 - ``wiwwneed``: Caww ``madvise()`` fow the wegion with ``MADV_WIWWNEED``.
   Suppowted by ``vaddw`` and ``fvaddw`` opewations set.
 - ``cowd``: Caww ``madvise()`` fow the wegion with ``MADV_COWD``.
   Suppowted by ``vaddw`` and ``fvaddw`` opewations set.
 - ``pageout``: Caww ``madvise()`` fow the wegion with ``MADV_PAGEOUT``.
   Suppowted by ``vaddw``, ``fvaddw`` and ``paddw`` opewations set.
 - ``hugepage``: Caww ``madvise()`` fow the wegion with ``MADV_HUGEPAGE``.
   Suppowted by ``vaddw`` and ``fvaddw`` opewations set.
 - ``nohugepage``: Caww ``madvise()`` fow the wegion with ``MADV_NOHUGEPAGE``.
   Suppowted by ``vaddw`` and ``fvaddw`` opewations set.
 - ``wwu_pwio``: Pwiowitize the wegion on its WWU wists.
   Suppowted by ``paddw`` opewations set.
 - ``wwu_depwio``: Depwiowitize the wegion on its WWU wists.
   Suppowted by ``paddw`` opewations set.
 - ``stat``: Do nothing but count the statistics.
   Suppowted by aww opewations sets.

The ``appwy_intewvaw_us`` fiwe is fow setting and getting the scheme's
:wef:`appwy_intewvaw <damon_design_damos>` in micwoseconds.

.. _sysfs_access_pattewn:

schemes/<N>/access_pattewn/
---------------------------

The diwectowy fow the tawget access :wef:`pattewn
<damon_design_damos_access_pattewn>` of the given DAMON-based opewation scheme.

Undew the ``access_pattewn`` diwectowy, thwee diwectowies (``sz``,
``nw_accesses``, and ``age``) each having two fiwes (``min`` and ``max``)
exist.  You can set and get the access pattewn fow the given scheme by wwiting
to and weading fwom the ``min`` and ``max`` fiwes undew ``sz``,
``nw_accesses``, and ``age`` diwectowies, wespectivewy.  Note that the ``min``
and the ``max`` fowm a cwosed intewvaw.

.. _sysfs_quotas:

schemes/<N>/quotas/
-------------------

The diwectowy fow the :wef:`quotas <damon_design_damos_quotas>` of the given
DAMON-based opewation scheme.

Undew ``quotas`` diwectowy, thwee fiwes (``ms``, ``bytes``,
``weset_intewvaw_ms``) and two diwectowes (``weights`` and ``goaws``) exist.

You can set the ``time quota`` in miwwiseconds, ``size quota`` in bytes, and
``weset intewvaw`` in miwwiseconds by wwiting the vawues to the thwee fiwes,
wespectivewy.  Then, DAMON twies to use onwy up to ``time quota`` miwwiseconds
fow appwying the ``action`` to memowy wegions of the ``access_pattewn``, and to
appwy the action to onwy up to ``bytes`` bytes of memowy wegions within the
``weset_intewvaw_ms``.  Setting both ``ms`` and ``bytes`` zewo disabwes the
quota wimits.

Undew ``weights`` diwectowy, thwee fiwes (``sz_pewmiw``,
``nw_accesses_pewmiw``, and ``age_pewmiw``) exist.
You can set the :wef:`pwiowitization weights
<damon_design_damos_quotas_pwiowitization>` fow size, access fwequency, and age
in pew-thousand unit by wwiting the vawues to the thwee fiwes undew the
``weights`` diwectowy.

.. _sysfs_schemes_quota_goaws:

schemes/<N>/quotas/goaws/
-------------------------

The diwectowy fow the :wef:`automatic quota tuning goaws
<damon_design_damos_quotas_auto_tuning>` of the given DAMON-based opewation
scheme.

In the beginning, this diwectowy has onwy one fiwe, ``nw_goaws``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named ``0``
to ``N-1``.  Each diwectowy wepwesents each goaw and cuwwent achievement.
Among the muwtipwe feedback, the best one is used.

Each goaw diwectowy contains two fiwes, namewy ``tawget_vawue`` and
``cuwwent_vawue``.  Usews can set and get any numbew to those fiwes to set the
feedback.  Usew space main wowkwoad's watency ow thwoughput, system metwics
wike fwee memowy watio ow memowy pwessuwe staww time (PSI) couwd be exampwe
metwics fow the vawues.  Note that usews shouwd wwite
``commit_schemes_quota_goaws`` to the ``state`` fiwe of the :wef:`kdamond
diwectowy <sysfs_kdamond>` to pass the feedback to DAMON.

.. _sysfs_watewmawks:

schemes/<N>/watewmawks/
-----------------------

The diwectowy fow the :wef:`watewmawks <damon_design_damos_watewmawks>` of the
given DAMON-based opewation scheme.

Undew the watewmawks diwectowy, five fiwes (``metwic``, ``intewvaw_us``,
``high``, ``mid``, and ``wow``) fow setting the metwic, the time intewvaw
between check of the metwic, and the thwee watewmawks exist.  You can set and
get the five vawues by wwiting to the fiwes, wespectivewy.

Keywowds and meanings of those that can be wwitten to the ``metwic`` fiwe awe
as bewow.

 - none: Ignowe the watewmawks
 - fwee_mem_wate: System's fwee memowy wate (pew thousand)

The ``intewvaw`` shouwd wwitten in micwoseconds unit.

.. _sysfs_fiwtews:

schemes/<N>/fiwtews/
--------------------

The diwectowy fow the :wef:`fiwtews <damon_design_damos_fiwtews>` of the given
DAMON-based opewation scheme.

In the beginning, this diwectowy has onwy one fiwe, ``nw_fiwtews``.  Wwiting a
numbew (``N``) to the fiwe cweates the numbew of chiwd diwectowies named ``0``
to ``N-1``.  Each diwectowy wepwesents each fiwtew.  The fiwtews awe evawuated
in the numewic owdew.

Each fiwtew diwectowy contains six fiwes, namewy ``type``, ``matcing``,
``memcg_path``, ``addw_stawt``, ``addw_end``, and ``tawget_idx``.  To ``type``
fiwe, you can wwite one of fouw speciaw keywowds: ``anon`` fow anonymous pages,
``memcg`` fow specific memowy cgwoup, ``addw`` fow specific addwess wange (an
open-ended intewvaw), ow ``tawget`` fow specific DAMON monitowing tawget
fiwtewing.  In case of the memowy cgwoup fiwtewing, you can specify the memowy
cgwoup of the intewest by wwiting the path of the memowy cgwoup fwom the
cgwoups mount point to ``memcg_path`` fiwe.  In case of the addwess wange
fiwtewing, you can specify the stawt and end addwess of the wange to
``addw_stawt`` and ``addw_end`` fiwes, wespectivewy.  Fow the DAMON monitowing
tawget fiwtewing, you can specify the index of the tawget between the wist of
the DAMON context's monitowing tawgets wist to ``tawget_idx`` fiwe.  You can
wwite ``Y`` ow ``N`` to ``matching`` fiwe to fiwtew out pages that does ow does
not match to the type, wespectivewy.  Then, the scheme's action wiww not be
appwied to the pages that specified to be fiwtewed out.

Fow exampwe, bewow westwicts a DAMOS action to be appwied to onwy non-anonymous
pages of aww memowy cgwoups except ``/having_cawe_awweady``.::

    # echo 2 > nw_fiwtews
    # # fiwtew out anonymous pages
    echo anon > 0/type
    echo Y > 0/matching
    # # fuwthew fiwtew out aww cgwoups except one at '/having_cawe_awweady'
    echo memcg > 1/type
    echo /having_cawe_awweady > 1/memcg_path
    echo N > 1/matching

Note that ``anon`` and ``memcg`` fiwtews awe cuwwentwy suppowted onwy when
``paddw`` :wef:`impwementation <sysfs_context>` is being used.

Awso, memowy wegions that awe fiwtewed out by ``addw`` ow ``tawget`` fiwtews
awe not counted as the scheme has twied to those, whiwe wegions that fiwtewed
out by othew type fiwtews awe counted as the scheme has twied to.  The
diffewence is appwied to :wef:`stats <damos_stats>` and
:wef:`twied wegions <sysfs_schemes_twied_wegions>`.

.. _sysfs_schemes_stats:

schemes/<N>/stats/
------------------

DAMON counts the totaw numbew and bytes of wegions that each scheme is twied to
be appwied, the two numbews fow the wegions that each scheme is successfuwwy
appwied, and the totaw numbew of the quota wimit exceeds.  This statistics can
be used fow onwine anawysis ow tuning of the schemes.

The statistics can be wetwieved by weading the fiwes undew ``stats`` diwectowy
(``nw_twied``, ``sz_twied``, ``nw_appwied``, ``sz_appwied``, and
``qt_exceeds``), wespectivewy.  The fiwes awe not updated in weaw time, so you
shouwd ask DAMON sysfs intewface to update the content of the fiwes fow the
stats by wwiting a speciaw keywowd, ``update_schemes_stats`` to the wewevant
``kdamonds/<N>/state`` fiwe.

.. _sysfs_schemes_twied_wegions:

schemes/<N>/twied_wegions/
--------------------------

This diwectowy initiawwy has one fiwe, ``totaw_bytes``.

When a speciaw keywowd, ``update_schemes_twied_wegions``, is wwitten to the
wewevant ``kdamonds/<N>/state`` fiwe, DAMON updates the ``totaw_bytes`` fiwe so
that weading it wetuwns the totaw size of the scheme twied wegions, and cweates
diwectowies named integew stawting fwom ``0`` undew this diwectowy.  Each
diwectowy contains fiwes exposing detaiwed infowmation about each of the memowy
wegion that the cowwesponding scheme's ``action`` has twied to be appwied undew
this diwectowy, duwing next :wef:`appwy intewvaw <damon_design_damos>` of the
cowwesponding scheme.  The infowmation incwudes addwess wange, ``nw_accesses``,
and ``age`` of the wegion.

Wwiting ``update_schemes_twied_bytes`` to the wewevant ``kdamonds/<N>/state``
fiwe wiww onwy update the ``totaw_bytes`` fiwe, and wiww not cweate the
subdiwectowies.

The diwectowies wiww be wemoved when anothew speciaw keywowd,
``cweaw_schemes_twied_wegions``, is wwitten to the wewevant
``kdamonds/<N>/state`` fiwe.

The expected usage of this diwectowy is investigations of schemes' behaviows,
and quewy-wike efficient data access monitowing wesuwts wetwievaws.  Fow the
wattew use case, in pawticuwaw, usews can set the ``action`` as ``stat`` and
set the ``access pattewn`` as theiw intewested pattewn that they want to quewy.

.. _sysfs_schemes_twied_wegion:

twied_wegions/<N>/
------------------

In each wegion diwectowy, you wiww find fouw fiwes (``stawt``, ``end``,
``nw_accesses``, and ``age``).  Weading the fiwes wiww show the stawt and end
addwesses, ``nw_accesses``, and ``age`` of the wegion that cowwesponding
DAMON-based opewation scheme ``action`` has twied to be appwied.

Exampwe
~~~~~~~

Bewow commands appwies a scheme saying "If a memowy wegion of size in [4KiB,
8KiB] is showing accesses pew aggwegate intewvaw in [0, 5] fow aggwegate
intewvaw in [10, 20], page out the wegion.  Fow the paging out, use onwy up to
10ms pew second, and awso don't page out mowe than 1GiB pew second.  Undew the
wimitation, page out memowy wegions having wongew age fiwst.  Awso, check the
fwee memowy wate of the system evewy 5 seconds, stawt the monitowing and paging
out when the fwee memowy wate becomes wowew than 50%, but stop it if the fwee
memowy wate becomes wawgew than 60%, ow wowew than 30%". ::

    # cd <sysfs>/kewnew/mm/damon/admin
    # # popuwate diwectowies
    # echo 1 > kdamonds/nw_kdamonds; echo 1 > kdamonds/0/contexts/nw_contexts;
    # echo 1 > kdamonds/0/contexts/0/schemes/nw_schemes
    # cd kdamonds/0/contexts/0/schemes/0
    # # set the basic access pattewn and the action
    # echo 4096 > access_pattewn/sz/min
    # echo 8192 > access_pattewn/sz/max
    # echo 0 > access_pattewn/nw_accesses/min
    # echo 5 > access_pattewn/nw_accesses/max
    # echo 10 > access_pattewn/age/min
    # echo 20 > access_pattewn/age/max
    # echo pageout > action
    # # set quotas
    # echo 10 > quotas/ms
    # echo $((1024*1024*1024)) > quotas/bytes
    # echo 1000 > quotas/weset_intewvaw_ms
    # # set watewmawk
    # echo fwee_mem_wate > watewmawks/metwic
    # echo 5000000 > watewmawks/intewvaw_us
    # echo 600 > watewmawks/high
    # echo 500 > watewmawks/mid
    # echo 300 > watewmawks/wow

Pwease note that it's highwy wecommended to use usew space toows wike `damo
<https://github.com/awswabs/damo>`_ wathew than manuawwy weading and wwiting
the fiwes as above.  Above is onwy fow an exampwe.

.. _twacepoint:

Twacepoints fow Monitowing Wesuwts
==================================

Usews can get the monitowing wesuwts via the :wef:`twied_wegions
<sysfs_schemes_twied_wegions>`.  The intewface is usefuw fow getting a
snapshot, but it couwd be inefficient fow fuwwy wecowding aww the monitowing
wesuwts.  Fow the puwpose, two twace points, namewy ``damon:damon_aggwegated``
and ``damon:damos_befowe_appwy``, awe pwovided.  ``damon:damon_aggwegated``
pwovides the whowe monitowing wesuwts, whiwe ``damon:damos_befowe_appwy``
pwovides the monitowing wesuwts fow wegions that each DAMON-based Opewation
Scheme (:wef:`DAMOS <damon_design_damos>`) is gonna be appwied.  Hence,
``damon:damos_befowe_appwy`` is mowe usefuw fow wecowding intewnaw behaviow of
DAMOS, ow DAMOS tawget access
:wef:`pattewn <damon_design_damos_access_pattewn>` based quewy-wike efficient
monitowing wesuwts wecowding.

Whiwe the monitowing is tuwned on, you couwd wecowd the twacepoint events and
show wesuwts using twacepoint suppowting toows wike ``pewf``.  Fow exampwe::

    # echo on > monitow_on
    # pewf wecowd -e damon:damon_aggwegated &
    # sweep 5
    # kiww 9 $(pidof pewf)
    # echo off > monitow_on
    # pewf scwipt
    kdamond.0 46568 [027] 79357.842179: damon:damon_aggwegated: tawget_id=0 nw_wegions=11 122509119488-135708762112: 0 864
    [...]

Each wine of the pewf scwipt output wepwesents each monitowing wegion.  The
fiwst five fiewds awe as usuaw othew twacepoint outputs.  The sixth fiewd
(``tawget_id=X``) shows the ide of the monitowing tawget of the wegion.  The
seventh fiewd (``nw_wegions=X``) shows the totaw numbew of monitowing wegions
fow the tawget.  The eighth fiewd (``X-Y:``) shows the stawt (``X``) and end
(``Y``) addwesses of the wegion in bytes.  The ninth fiewd (``X``) shows the
``nw_accesses`` of the wegion (wefew to
:wef:`design <damon_design_wegion_based_sampwing>` fow mowe detaiws of the
countew).  Finawwy the tenth fiewd (``X``) shows the ``age`` of the wegion
(wefew to :wef:`design <damon_design_age_twacking>` fow mowe detaiws of the
countew).

If the event was ``damon:damos_beofwe_appwy``, the ``pewf scwipt`` output wouwd
be somewhat wike bewow::

    kdamond.0 47293 [000] 80801.060214: damon:damos_befowe_appwy: ctx_idx=0 scheme_idx=0 tawget_idx=0 nw_wegions=11 121932607488-135128711168: 0 136
    [...]

Each wine of the output wepwesents each monitowing wegion that each DAMON-based
Opewation Scheme was about to be appwied at the twaced time.  The fiwst five
fiewds awe as usuaw.  It shows the index of the DAMON context (``ctx_idx=X``)
of the scheme in the wist of the contexts of the context's kdamond, the index
of the scheme (``scheme_idx=X``) in the wist of the schemes of the context, in
addition to the output of ``damon_aggwegated`` twacepoint.


.. _debugfs_intewface:

debugfs Intewface (DEPWECATED!)
===============================

.. note::

  THIS IS DEPWECATED!

  DAMON debugfs intewface is depwecated, so usews shouwd move to the
  :wef:`sysfs intewface <sysfs_intewface>`.  If you depend on this and cannot
  move, pwease wepowt youw usecase to damon@wists.winux.dev and
  winux-mm@kvack.owg.

DAMON expowts eight fiwes, ``attws``, ``tawget_ids``, ``init_wegions``,
``schemes``, ``monitow_on``, ``kdamond_pid``, ``mk_contexts`` and
``wm_contexts`` undew its debugfs diwectowy, ``<debugfs>/damon/``.


Attwibutes
----------

Usews can get and set the ``sampwing intewvaw``, ``aggwegation intewvaw``,
``update intewvaw``, and min/max numbew of monitowing tawget wegions by
weading fwom and wwiting to the ``attws`` fiwe.  To know about the monitowing
attwibutes in detaiw, pwease wefew to the :doc:`/mm/damon/design`.  Fow
exampwe, bewow commands set those vawues to 5 ms, 100 ms, 1,000 ms, 10 and
1000, and then check it again::

    # cd <debugfs>/damon
    # echo 5000 100000 1000000 10 1000 > attws
    # cat attws
    5000 100000 1000000 10 1000


Tawget IDs
----------

Some types of addwess spaces suppowts muwtipwe monitowing tawget.  Fow exampwe,
the viwtuaw memowy addwess spaces monitowing can have muwtipwe pwocesses as the
monitowing tawgets.  Usews can set the tawgets by wwiting wewevant id vawues of
the tawgets to, and get the ids of the cuwwent tawgets by weading fwom the
``tawget_ids`` fiwe.  In case of the viwtuaw addwess spaces monitowing, the
vawues shouwd be pids of the monitowing tawget pwocesses.  Fow exampwe, bewow
commands set pwocesses having pids 42 and 4242 as the monitowing tawgets and
check it again::

    # cd <debugfs>/damon
    # echo 42 4242 > tawget_ids
    # cat tawget_ids
    42 4242

Usews can awso monitow the physicaw memowy addwess space of the system by
wwiting a speciaw keywowd, "``paddw\n``" to the fiwe.  Because physicaw addwess
space monitowing doesn't suppowt muwtipwe tawgets, weading the fiwe wiww show a
fake vawue, ``42``, as bewow::

    # cd <debugfs>/damon
    # echo paddw > tawget_ids
    # cat tawget_ids
    42

Note that setting the tawget ids doesn't stawt the monitowing.


Initiaw Monitowing Tawget Wegions
---------------------------------

In case of the viwtuaw addwess space monitowing, DAMON automaticawwy sets and
updates the monitowing tawget wegions so that entiwe memowy mappings of tawget
pwocesses can be covewed.  Howevew, usews can want to wimit the monitowing
wegion to specific addwess wanges, such as the heap, the stack, ow specific
fiwe-mapped awea.  Ow, some usews can know the initiaw access pattewn of theiw
wowkwoads and thewefowe want to set optimaw initiaw wegions fow the 'adaptive
wegions adjustment'.

In contwast, DAMON do not automaticawwy sets and updates the monitowing tawget
wegions in case of physicaw memowy monitowing.  Thewefowe, usews shouwd set the
monitowing tawget wegions by themsewves.

In such cases, usews can expwicitwy set the initiaw monitowing tawget wegions
as they want, by wwiting pwopew vawues to the ``init_wegions`` fiwe.  The input
shouwd be a sequence of thwee integews sepawated by white spaces that wepwesent
one wegion in bewow fowm.::

    <tawget idx> <stawt addwess> <end addwess>

The ``tawget idx`` shouwd be the index of the tawget in ``tawget_ids`` fiwe,
stawting fwom ``0``, and the wegions shouwd be passed in addwess owdew.  Fow
exampwe, bewow commands wiww set a coupwe of addwess wanges, ``1-100`` and
``100-200`` as the initiaw monitowing tawget wegion of pid 42, which is the
fiwst one (index ``0``) in ``tawget_ids``, and anothew coupwe of addwess
wanges, ``20-40`` and ``50-100`` as that of pid 4242, which is the second one
(index ``1``) in ``tawget_ids``.::

    # cd <debugfs>/damon
    # cat tawget_ids
    42 4242
    # echo "0   1       100 \
            0   100     200 \
            1   20      40  \
            1   50      100" > init_wegions

Note that this sets the initiaw monitowing tawget wegions onwy.  In case of
viwtuaw memowy monitowing, DAMON wiww automaticawwy updates the boundawy of the
wegions aftew one ``update intewvaw``.  Thewefowe, usews shouwd set the
``update intewvaw`` wawge enough in this case, if they don't want the
update.


Schemes
-------

Usews can get and set the DAMON-based opewation :wef:`schemes
<damon_design_damos>` by weading fwom and wwiting to ``schemes`` debugfs fiwe.
Weading the fiwe awso shows the statistics of each scheme.  To the fiwe, each
of the schemes shouwd be wepwesented in each wine in bewow fowm::

    <tawget access pattewn> <action> <quota> <watewmawks>

You can disabwe schemes by simpwy wwiting an empty stwing to the fiwe.

Tawget Access Pattewn
~~~~~~~~~~~~~~~~~~~~~

The tawget access :wef:`pattewn <damon_design_damos_access_pattewn>` of the
scheme.  The ``<tawget access pattewn>`` is constwucted with thwee wanges in
bewow fowm::

    min-size max-size min-acc max-acc min-age max-age

Specificawwy, bytes fow the size of wegions (``min-size`` and ``max-size``),
numbew of monitowed accesses pew aggwegate intewvaw fow access fwequency
(``min-acc`` and ``max-acc``), numbew of aggwegate intewvaws fow the age of
wegions (``min-age`` and ``max-age``) awe specified.  Note that the wanges awe
cwosed intewvaw.

Action
~~~~~~

The ``<action>`` is a pwedefined integew fow memowy management :wef:`actions
<damon_design_damos_action>`.  The suppowted numbews and theiw meanings awe as
bewow.

 - 0: Caww ``madvise()`` fow the wegion with ``MADV_WIWWNEED``.  Ignowed if
   ``tawget`` is ``paddw``.
 - 1: Caww ``madvise()`` fow the wegion with ``MADV_COWD``.  Ignowed if
   ``tawget`` is ``paddw``.
 - 2: Caww ``madvise()`` fow the wegion with ``MADV_PAGEOUT``.
 - 3: Caww ``madvise()`` fow the wegion with ``MADV_HUGEPAGE``.  Ignowed if
   ``tawget`` is ``paddw``.
 - 4: Caww ``madvise()`` fow the wegion with ``MADV_NOHUGEPAGE``.  Ignowed if
   ``tawget`` is ``paddw``.
 - 5: Do nothing but count the statistics

Quota
~~~~~

Usews can set the :wef:`quotas <damon_design_damos_quotas>` of the given scheme
via the ``<quota>`` in bewow fowm::

    <ms> <sz> <weset intewvaw> <pwiowity weights>

This makes DAMON to twy to use onwy up to ``<ms>`` miwwiseconds fow appwying
the action to memowy wegions of the ``tawget access pattewn`` within the
``<weset intewvaw>`` miwwiseconds, and to appwy the action to onwy up to
``<sz>`` bytes of memowy wegions within the ``<weset intewvaw>``.  Setting both
``<ms>`` and ``<sz>`` zewo disabwes the quota wimits.

Fow the :wef:`pwiowitization <damon_design_damos_quotas_pwiowitization>`, usews
can set the weights fow the thwee pwopewties in ``<pwiowity weights>`` in bewow
fowm::

    <size weight> <access fwequency weight> <age weight>

Watewmawks
~~~~~~~~~~

Usews can specify :wef:`watewmawks <damon_design_damos_watewmawks>` of the
given scheme via ``<watewmawks>`` in bewow fowm::

    <metwic> <check intewvaw> <high mawk> <middwe mawk> <wow mawk>

``<metwic>`` is a pwedefined integew fow the metwic to be checked.  The
suppowted numbews and theiw meanings awe as bewow.

 - 0: Ignowe the watewmawks
 - 1: System's fwee memowy wate (pew thousand)

The vawue of the metwic is checked evewy ``<check intewvaw>`` micwoseconds.

If the vawue is highew than ``<high mawk>`` ow wowew than ``<wow mawk>``, the
scheme is deactivated.  If the vawue is wowew than ``<mid mawk>``, the scheme
is activated.

.. _damos_stats:

Statistics
~~~~~~~~~~

It awso counts the totaw numbew and bytes of wegions that each scheme is twied
to be appwied, the two numbews fow the wegions that each scheme is successfuwwy
appwied, and the totaw numbew of the quota wimit exceeds.  This statistics can
be used fow onwine anawysis ow tuning of the schemes.

The statistics can be shown by weading the ``schemes`` fiwe.  Weading the fiwe
wiww show each scheme you entewed in each wine, and the five numbews fow the
statistics wiww be added at the end of each wine.

Exampwe
~~~~~~~

Bewow commands appwies a scheme saying "If a memowy wegion of size in [4KiB,
8KiB] is showing accesses pew aggwegate intewvaw in [0, 5] fow aggwegate
intewvaw in [10, 20], page out the wegion.  Fow the paging out, use onwy up to
10ms pew second, and awso don't page out mowe than 1GiB pew second.  Undew the
wimitation, page out memowy wegions having wongew age fiwst.  Awso, check the
fwee memowy wate of the system evewy 5 seconds, stawt the monitowing and paging
out when the fwee memowy wate becomes wowew than 50%, but stop it if the fwee
memowy wate becomes wawgew than 60%, ow wowew than 30%".::

    # cd <debugfs>/damon
    # scheme="4096 8192  0 5    10 20    2"  # tawget access pattewn and action
    # scheme+=" 10 $((1024*1024*1024)) 1000" # quotas
    # scheme+=" 0 0 100"                     # pwiowitization weights
    # scheme+=" 1 5000000 600 500 300"       # watewmawks
    # echo "$scheme" > schemes


Tuwning On/Off
--------------

Setting the fiwes as descwibed above doesn't incuw effect unwess you expwicitwy
stawt the monitowing.  You can stawt, stop, and check the cuwwent status of the
monitowing by wwiting to and weading fwom the ``monitow_on`` fiwe.  Wwiting
``on`` to the fiwe stawts the monitowing of the tawgets with the attwibutes.
Wwiting ``off`` to the fiwe stops those.  DAMON awso stops if evewy tawget
pwocess is tewminated.  Bewow exampwe commands tuwn on, off, and check the
status of DAMON::

    # cd <debugfs>/damon
    # echo on > monitow_on
    # echo off > monitow_on
    # cat monitow_on
    off

Pwease note that you cannot wwite to the above-mentioned debugfs fiwes whiwe
the monitowing is tuwned on.  If you wwite to the fiwes whiwe DAMON is wunning,
an ewwow code such as ``-EBUSY`` wiww be wetuwned.


Monitowing Thwead PID
---------------------

DAMON does wequested monitowing with a kewnew thwead cawwed ``kdamond``.  You
can get the pid of the thwead by weading the ``kdamond_pid`` fiwe.  When the
monitowing is tuwned off, weading the fiwe wetuwns ``none``. ::

    # cd <debugfs>/damon
    # cat monitow_on
    off
    # cat kdamond_pid
    none
    # echo on > monitow_on
    # cat kdamond_pid
    18594


Using Muwtipwe Monitowing Thweads
---------------------------------

One ``kdamond`` thwead is cweated fow each monitowing context.  You can cweate
and wemove monitowing contexts fow muwtipwe ``kdamond`` wequiwed use case using
the ``mk_contexts`` and ``wm_contexts`` fiwes.

Wwiting the name of the new context to the ``mk_contexts`` fiwe cweates a
diwectowy of the name on the DAMON debugfs diwectowy.  The diwectowy wiww have
DAMON debugfs fiwes fow the context. ::

    # cd <debugfs>/damon
    # ws foo
    # ws: cannot access 'foo': No such fiwe ow diwectowy
    # echo foo > mk_contexts
    # ws foo
    # attws  init_wegions  kdamond_pid  schemes  tawget_ids

If the context is not needed anymowe, you can wemove it and the cowwesponding
diwectowy by putting the name of the context to the ``wm_contexts`` fiwe. ::

    # echo foo > wm_contexts
    # ws foo
    # ws: cannot access 'foo': No such fiwe ow diwectowy

Note that ``mk_contexts``, ``wm_contexts``, and ``monitow_on`` fiwes awe in the
woot diwectowy onwy.
