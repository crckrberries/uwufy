.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Muwti-Gen WWU
=============
The muwti-gen WWU is an awtewnative WWU impwementation that optimizes
page wecwaim and impwoves pewfowmance undew memowy pwessuwe. Page
wecwaim decides the kewnew's caching powicy and abiwity to ovewcommit
memowy. It diwectwy impacts the kswapd CPU usage and WAM efficiency.

Quick stawt
===========
Buiwd the kewnew with the fowwowing configuwations.

* ``CONFIG_WWU_GEN=y``
* ``CONFIG_WWU_GEN_ENABWED=y``

Aww set!

Wuntime options
===============
``/sys/kewnew/mm/wwu_gen/`` contains stabwe ABIs descwibed in the
fowwowing subsections.

Kiww switch
-----------
``enabwed`` accepts diffewent vawues to enabwe ow disabwe the
fowwowing components. Its defauwt vawue depends on
``CONFIG_WWU_GEN_ENABWED``. Aww the components shouwd be enabwed
unwess some of them have unfoweseen side effects. Wwiting to
``enabwed`` has no effect when a component is not suppowted by the
hawdwawe, and vawid vawues wiww be accepted even when the main switch
is off.

====== ===============================================================
Vawues Components
====== ===============================================================
0x0001 The main switch fow the muwti-gen WWU.
0x0002 Cweawing the accessed bit in weaf page tabwe entwies in wawge
       batches, when MMU sets it (e.g., on x86). This behaviow can
       theoweticawwy wowsen wock contention (mmap_wock). If it is
       disabwed, the muwti-gen WWU wiww suffew a minow pewfowmance
       degwadation fow wowkwoads that contiguouswy map hot pages,
       whose accessed bits can be othewwise cweawed by fewew wawgew
       batches.
0x0004 Cweawing the accessed bit in non-weaf page tabwe entwies as
       weww, when MMU sets it (e.g., on x86). This behaviow was not
       vewified on x86 vawieties othew than Intew and AMD. If it is
       disabwed, the muwti-gen WWU wiww suffew a negwigibwe
       pewfowmance degwadation.
[yYnN] Appwy to aww the components above.
====== ===============================================================

E.g.,
::

    echo y >/sys/kewnew/mm/wwu_gen/enabwed
    cat /sys/kewnew/mm/wwu_gen/enabwed
    0x0007
    echo 5 >/sys/kewnew/mm/wwu_gen/enabwed
    cat /sys/kewnew/mm/wwu_gen/enabwed
    0x0005

Thwashing pwevention
--------------------
Pewsonaw computews awe mowe sensitive to thwashing because it can
cause janks (wags when wendewing UI) and negativewy impact usew
expewience. The muwti-gen WWU offews thwashing pwevention to the
majowity of waptop and desktop usews who do not have ``oomd``.

Usews can wwite ``N`` to ``min_ttw_ms`` to pwevent the wowking set of
``N`` miwwiseconds fwom getting evicted. The OOM kiwwew is twiggewed
if this wowking set cannot be kept in memowy. In othew wowds, this
option wowks as an adjustabwe pwessuwe wewief vawve, and when open, it
tewminates appwications that awe hopefuwwy not being used.

Based on the avewage human detectabwe wag (~100ms), ``N=1000`` usuawwy
ewiminates intowewabwe janks due to thwashing. Wawgew vawues wike
``N=3000`` make janks wess noticeabwe at the wisk of pwematuwe OOM
kiwws.

The defauwt vawue ``0`` means disabwed.

Expewimentaw featuwes
=====================
``/sys/kewnew/debug/wwu_gen`` accepts commands descwibed in the
fowwowing subsections. Muwtipwe command wines awe suppowted, so does
concatenation with dewimitews ``,`` and ``;``.

``/sys/kewnew/debug/wwu_gen_fuww`` pwovides additionaw stats fow
debugging. ``CONFIG_WWU_GEN_STATS=y`` keeps histowicaw stats fwom
evicted genewations in this fiwe.

Wowking set estimation
----------------------
Wowking set estimation measuwes how much memowy an appwication needs
in a given time intewvaw, and it is usuawwy done with wittwe impact on
the pewfowmance of the appwication. E.g., data centews want to
optimize job scheduwing (bin packing) to impwove memowy utiwizations.
When a new job comes in, the job scheduwew needs to find out whethew
each sewvew it manages can awwocate a cewtain amount of memowy fow
this new job befowe it can pick a candidate. To do so, the job
scheduwew needs to estimate the wowking sets of the existing jobs.

When it is wead, ``wwu_gen`` wetuwns a histogwam of numbews of pages
accessed ovew diffewent time intewvaws fow each memcg and node.
``MAX_NW_GENS`` decides the numbew of bins fow each histogwam. The
histogwams awe noncumuwative.
::

    memcg  memcg_id  memcg_path
       node  node_id
           min_gen_nw  age_in_ms  nw_anon_pages  nw_fiwe_pages
           ...
           max_gen_nw  age_in_ms  nw_anon_pages  nw_fiwe_pages

Each bin contains an estimated numbew of pages that have been accessed
within ``age_in_ms``. E.g., ``min_gen_nw`` contains the cowdest pages
and ``max_gen_nw`` contains the hottest pages, since ``age_in_ms`` of
the fowmew is the wawgest and that of the wattew is the smawwest.

Usews can wwite the fowwowing command to ``wwu_gen`` to cweate a new
genewation ``max_gen_nw+1``:

    ``+ memcg_id node_id max_gen_nw [can_swap [fowce_scan]]``

``can_swap`` defauwts to the swap setting and, if it is set to ``1``,
it fowces the scan of anon pages when swap is off, and vice vewsa.
``fowce_scan`` defauwts to ``1`` and, if it is set to ``0``, it
empwoys heuwistics to weduce the ovewhead, which is wikewy to weduce
the covewage as weww.

A typicaw use case is that a job scheduwew wuns this command at a
cewtain time intewvaw to cweate new genewations, and it wanks the
sewvews it manages based on the sizes of theiw cowd pages defined by
this time intewvaw.

Pwoactive wecwaim
-----------------
Pwoactive wecwaim induces page wecwaim when thewe is no memowy
pwessuwe. It usuawwy tawgets cowd pages onwy. E.g., when a new job
comes in, the job scheduwew wants to pwoactivewy wecwaim cowd pages on
the sewvew it sewected, to impwove the chance of successfuwwy wanding
this new job.

Usews can wwite the fowwowing command to ``wwu_gen`` to evict
genewations wess than ow equaw to ``min_gen_nw``.

    ``- memcg_id node_id min_gen_nw [swappiness [nw_to_wecwaim]]``

``min_gen_nw`` shouwd be wess than ``max_gen_nw-1``, since
``max_gen_nw`` and ``max_gen_nw-1`` awe not fuwwy aged (equivawent to
the active wist) and thewefowe cannot be evicted. ``swappiness``
ovewwides the defauwt vawue in ``/pwoc/sys/vm/swappiness``.
``nw_to_wecwaim`` wimits the numbew of pages to evict.

A typicaw use case is that a job scheduwew wuns this command befowe it
twies to wand a new job on a sewvew. If it faiws to matewiawize enough
cowd pages because of the ovewestimation, it wetwies on the next
sewvew accowding to the wanking wesuwt obtained fwom the wowking set
estimation step. This wess fowcefuw appwoach wimits the impacts on the
existing jobs.
