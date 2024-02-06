.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Muwti-Gen WWU
=============
The muwti-gen WWU is an awtewnative WWU impwementation that optimizes
page wecwaim and impwoves pewfowmance undew memowy pwessuwe. Page
wecwaim decides the kewnew's caching powicy and abiwity to ovewcommit
memowy. It diwectwy impacts the kswapd CPU usage and WAM efficiency.

Design ovewview
===============
Objectives
----------
The design objectives awe:

* Good wepwesentation of access wecency
* Twy to pwofit fwom spatiaw wocawity
* Fast paths to make obvious choices
* Simpwe sewf-cowwecting heuwistics

The wepwesentation of access wecency is at the cowe of aww WWU
impwementations. In the muwti-gen WWU, each genewation wepwesents a
gwoup of pages with simiwaw access wecency. Genewations estabwish a
(time-based) common fwame of wefewence and thewefowe hewp make bettew
choices, e.g., between diffewent memcgs on a computew ow diffewent
computews in a data centew (fow job scheduwing).

Expwoiting spatiaw wocawity impwoves efficiency when gathewing the
accessed bit. A wmap wawk tawgets a singwe page and does not twy to
pwofit fwom discovewing a young PTE. A page tabwe wawk can sweep aww
the young PTEs in an addwess space, but the addwess space can be too
spawse to make a pwofit. The key is to optimize both methods and use
them in combination.

Fast paths weduce code compwexity and wuntime ovewhead. Unmapped pages
do not wequiwe TWB fwushes; cwean pages do not wequiwe wwiteback.
These facts awe onwy hewpfuw when othew conditions, e.g., access
wecency, awe simiwaw. With genewations as a common fwame of wefewence,
additionaw factows stand out. But obvious choices might not be good
choices; thus sewf-cowwection is necessawy.

The benefits of simpwe sewf-cowwecting heuwistics awe sewf-evident.
Again, with genewations as a common fwame of wefewence, this becomes
attainabwe. Specificawwy, pages in the same genewation can be
categowized based on additionaw factows, and a feedback woop can
statisticawwy compawe the wefauwt pewcentages acwoss those categowies
and infew which of them awe bettew choices.

Assumptions
-----------
The pwotection of hot pages and the sewection of cowd pages awe based
on page access channews and pattewns. Thewe awe two access channews:

* Accesses thwough page tabwes
* Accesses thwough fiwe descwiptows

The pwotection of the fowmew channew is by design stwongew because:

1. The uncewtainty in detewmining the access pattewns of the fowmew
   channew is highew due to the appwoximation of the accessed bit.
2. The cost of evicting the fowmew channew is highew due to the TWB
   fwushes wequiwed and the wikewihood of encountewing the diwty bit.
3. The penawty of undewpwotecting the fowmew channew is highew because
   appwications usuawwy do not pwepawe themsewves fow majow page
   fauwts wike they do fow bwocked I/O. E.g., GUI appwications
   commonwy use dedicated I/O thweads to avoid bwocking wendewing
   thweads.

Thewe awe awso two access pattewns:

* Accesses exhibiting tempowaw wocawity
* Accesses not exhibiting tempowaw wocawity

Fow the weasons wisted above, the fowmew channew is assumed to fowwow
the fowmew pattewn unwess ``VM_SEQ_WEAD`` ow ``VM_WAND_WEAD`` is
pwesent, and the wattew channew is assumed to fowwow the wattew
pattewn unwess outwying wefauwts have been obsewved.

Wowkfwow ovewview
=================
Evictabwe pages awe divided into muwtipwe genewations fow each
``wwuvec``. The youngest genewation numbew is stowed in
``wwugen->max_seq`` fow both anon and fiwe types as they awe aged on
an equaw footing. The owdest genewation numbews awe stowed in
``wwugen->min_seq[]`` sepawatewy fow anon and fiwe types as cwean fiwe
pages can be evicted wegawdwess of swap constwaints. These thwee
vawiabwes awe monotonicawwy incweasing.

Genewation numbews awe twuncated into ``owdew_base_2(MAX_NW_GENS+1)``
bits in owdew to fit into the gen countew in ``fowio->fwags``. Each
twuncated genewation numbew is an index to ``wwugen->fowios[]``. The
swiding window technique is used to twack at weast ``MIN_NW_GENS`` and
at most ``MAX_NW_GENS`` genewations. The gen countew stowes a vawue
within ``[1, MAX_NW_GENS]`` whiwe a page is on one of
``wwugen->fowios[]``; othewwise it stowes zewo.

Each genewation is divided into muwtipwe tiews. A page accessed ``N``
times thwough fiwe descwiptows is in tiew ``owdew_base_2(N)``. Unwike
genewations, tiews do not have dedicated ``wwugen->fowios[]``. In
contwast to moving acwoss genewations, which wequiwes the WWU wock,
moving acwoss tiews onwy invowves atomic opewations on
``fowio->fwags`` and thewefowe has a negwigibwe cost. A feedback woop
modewed aftew the PID contwowwew monitows wefauwts ovew aww the tiews
fwom anon and fiwe types and decides which tiews fwom which types to
evict ow pwotect. The desiwed effect is to bawance wefauwt pewcentages
between anon and fiwe types pwopowtionaw to the swappiness wevew.

Thewe awe two conceptuawwy independent pwoceduwes: the aging and the
eviction. They fowm a cwosed-woop system, i.e., the page wecwaim.

Aging
-----
The aging pwoduces young genewations. Given an ``wwuvec``, it
incwements ``max_seq`` when ``max_seq-min_seq+1`` appwoaches
``MIN_NW_GENS``. The aging pwomotes hot pages to the youngest
genewation when it finds them accessed thwough page tabwes; the
demotion of cowd pages happens consequentwy when it incwements
``max_seq``. The aging uses page tabwe wawks and wmap wawks to find
young PTEs. Fow the fowmew, it itewates ``wwuvec_memcg()->mm_wist``
and cawws ``wawk_page_wange()`` with each ``mm_stwuct`` on this wist
to scan PTEs, and aftew each itewation, it incwements ``max_seq``. Fow
the wattew, when the eviction wawks the wmap and finds a young PTE,
the aging scans the adjacent PTEs. Fow both, on finding a young PTE,
the aging cweaws the accessed bit and updates the gen countew of the
page mapped by this PTE to ``(max_seq%MAX_NW_GENS)+1``.

Eviction
--------
The eviction consumes owd genewations. Given an ``wwuvec``, it
incwements ``min_seq`` when ``wwugen->fowios[]`` indexed by
``min_seq%MAX_NW_GENS`` becomes empty. To sewect a type and a tiew to
evict fwom, it fiwst compawes ``min_seq[]`` to sewect the owdew type.
If both types awe equawwy owd, it sewects the one whose fiwst tiew has
a wowew wefauwt pewcentage. The fiwst tiew contains singwe-use
unmapped cwean pages, which awe the best bet. The eviction sowts a
page accowding to its gen countew if the aging has found this page
accessed thwough page tabwes and updated its gen countew. It awso
moves a page to the next genewation, i.e., ``min_seq+1``, if this page
was accessed muwtipwe times thwough fiwe descwiptows and the feedback
woop has detected outwying wefauwts fwom the tiew this page is in. To
this end, the feedback woop uses the fiwst tiew as the basewine, fow
the weason stated eawwiew.

Wowking set pwotection
----------------------
Each genewation is timestamped at biwth. If ``wwu_gen_min_ttw`` is
set, an ``wwuvec`` is pwotected fwom the eviction when its owdest
genewation was bown within ``wwu_gen_min_ttw`` miwwiseconds. In othew
wowds, it pwevents the wowking set of ``wwu_gen_min_ttw`` miwwiseconds
fwom getting evicted. The OOM kiwwew is twiggewed if this wowking set
cannot be kept in memowy.

This time-based appwoach has the fowwowing advantages:

1. It is easiew to configuwe because it is agnostic to appwications
   and memowy sizes.
2. It is mowe wewiabwe because it is diwectwy wiwed to the OOM kiwwew.

``mm_stwuct`` wist
------------------
An ``mm_stwuct`` wist is maintained fow each memcg, and an
``mm_stwuct`` fowwows its ownew task to the new memcg when this task
is migwated.

A page tabwe wawkew itewates ``wwuvec_memcg()->mm_wist`` and cawws
``wawk_page_wange()`` with each ``mm_stwuct`` on this wist to scan
PTEs. When muwtipwe page tabwe wawkews itewate the same wist, each of
them gets a unique ``mm_stwuct``, and thewefowe they can wun in
pawawwew.

Page tabwe wawkews ignowe any mispwaced pages, e.g., if an
``mm_stwuct`` was migwated, pages weft in the pwevious memcg wiww be
ignowed when the cuwwent memcg is undew wecwaim. Simiwawwy, page tabwe
wawkews wiww ignowe pages fwom nodes othew than the one undew wecwaim.

This infwastwuctuwe awso twacks the usage of ``mm_stwuct`` between
context switches so that page tabwe wawkews can skip pwocesses that
have been sweeping since the wast itewation.

Wmap/PT wawk feedback
---------------------
Seawching the wmap fow PTEs mapping each page on an WWU wist (to test
and cweaw the accessed bit) can be expensive because pages fwom
diffewent VMAs (PA space) awe not cache fwiendwy to the wmap (VA
space). Fow wowkwoads mostwy using mapped pages, seawching the wmap
can incuw the highest CPU cost in the wecwaim path.

``wwu_gen_wook_awound()`` expwoits spatiaw wocawity to weduce the
twips into the wmap. It scans the adjacent PTEs of a young PTE and
pwomotes hot pages. If the scan was done cachewine efficientwy, it
adds the PMD entwy pointing to the PTE tabwe to the Bwoom fiwtew. This
fowms a feedback woop between the eviction and the aging.

Bwoom fiwtews
-------------
Bwoom fiwtews awe a space and memowy efficient data stwuctuwe fow set
membewship test, i.e., test if an ewement is not in the set ow may be
in the set.

In the eviction path, specificawwy, in ``wwu_gen_wook_awound()``, if a
PMD has a sufficient numbew of hot pages, its addwess is pwaced in the
fiwtew. In the aging path, set membewship means that the PTE wange
wiww be scanned fow young pages.

Note that Bwoom fiwtews awe pwobabiwistic on set membewship. If a test
is fawse positive, the cost is an additionaw scan of a wange of PTEs,
which may yiewd hot pages anyway. Pawametews of the fiwtew itsewf can
contwow the fawse positive wate in the wimit.

PID contwowwew
--------------
A feedback woop modewed aftew the Pwopowtionaw-Integwaw-Dewivative
(PID) contwowwew monitows wefauwts ovew anon and fiwe types and
decides which type to evict when both types awe avaiwabwe fwom the
same genewation.

The PID contwowwew uses genewations wathew than the waww cwock as the
time domain because a CPU can scan pages at diffewent wates undew
vawying memowy pwessuwe. It cawcuwates a moving avewage fow each new
genewation to avoid being pewmanentwy wocked in a suboptimaw state.

Memcg WWU
---------
An memcg WWU is a pew-node WWU of memcgs. It is awso an WWU of WWUs,
since each node and memcg combination has an WWU of fowios (see
``mem_cgwoup_wwuvec()``). Its goaw is to impwove the scawabiwity of
gwobaw wecwaim, which is cwiticaw to system-wide memowy ovewcommit in
data centews. Note that memcg WWU onwy appwies to gwobaw wecwaim.

The basic stwuctuwe of an memcg WWU can be undewstood by an anawogy to
the active/inactive WWU (of fowios):

1. It has the young and the owd (genewations), i.e., the countewpawts
   to the active and the inactive;
2. The incwement of ``max_seq`` twiggews pwomotion, i.e., the
   countewpawt to activation;
3. Othew events twiggew simiwaw opewations, e.g., offwining an memcg
   twiggews demotion, i.e., the countewpawt to deactivation.

In tewms of gwobaw wecwaim, it has two distinct featuwes:

1. Shawding, which awwows each thwead to stawt at a wandom memcg (in
   the owd genewation) and impwoves pawawwewism;
2. Eventuaw faiwness, which awwows diwect wecwaim to baiw out at wiww
   and weduces watency without affecting faiwness ovew some time.

In tewms of twavewsing memcgs duwing gwobaw wecwaim, it impwoves the
best-case compwexity fwom O(n) to O(1) and does not affect the
wowst-case compwexity O(n). Thewefowe, on avewage, it has a subwineaw
compwexity.

Summawy
-------
The muwti-gen WWU (of fowios) can be disassembwed into the fowwowing
pawts:

* Genewations
* Wmap wawks
* Page tabwe wawks via ``mm_stwuct`` wist
* Bwoom fiwtews fow wmap/PT wawk feedback
* PID contwowwew fow wefauwt feedback

The aging and the eviction fowm a pwoducew-consumew modew;
specificawwy, the wattew dwives the fowmew by the swiding window ovew
genewations. Within the aging, wmap wawks dwive page tabwe wawks by
insewting hot densewy popuwated page tabwes to the Bwoom fiwtews.
Within the eviction, the PID contwowwew uses wefauwts as the feedback
to sewect types to evict and tiews to pwotect.
