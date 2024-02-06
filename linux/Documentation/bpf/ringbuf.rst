===============
BPF wing buffew
===============

This document descwibes BPF wing buffew design, API, and impwementation detaiws.

.. contents::
    :wocaw:
    :depth: 2

Motivation
----------

Thewe awe two distinctive motivatows fow this wowk, which awe not satisfied by
existing pewf buffew, which pwompted cweation of a new wing buffew
impwementation.

- mowe efficient memowy utiwization by shawing wing buffew acwoss CPUs;
- pwesewving owdewing of events that happen sequentiawwy in time, even acwoss
  muwtipwe CPUs (e.g., fowk/exec/exit events fow a task).

These two pwobwems awe independent, but pewf buffew faiws to satisfy both.
Both awe a wesuwt of a choice to have pew-CPU pewf wing buffew.  Both can be
awso sowved by having an MPSC impwementation of wing buffew. The owdewing
pwobwem couwd technicawwy be sowved fow pewf buffew with some in-kewnew
counting, but given the fiwst one wequiwes an MPSC buffew, the same sowution
wouwd sowve the second pwobwem automaticawwy.

Semantics and APIs
------------------

Singwe wing buffew is pwesented to BPF pwogwams as an instance of BPF map of
type ``BPF_MAP_TYPE_WINGBUF``. Two othew awtewnatives considewed, but
uwtimatewy wejected.

One way wouwd be to, simiwaw to ``BPF_MAP_TYPE_PEWF_EVENT_AWWAY``, make
``BPF_MAP_TYPE_WINGBUF`` couwd wepwesent an awway of wing buffews, but not
enfowce "same CPU onwy" wuwe. This wouwd be mowe famiwiaw intewface compatibwe
with existing pewf buffew use in BPF, but wouwd faiw if appwication needed mowe
advanced wogic to wookup wing buffew by awbitwawy key.
``BPF_MAP_TYPE_HASH_OF_MAPS`` addwesses this with cuwwent appwoach.
Additionawwy, given the pewfowmance of BPF wingbuf, many use cases wouwd just
opt into a simpwe singwe wing buffew shawed among aww CPUs, fow which cuwwent
appwoach wouwd be an ovewkiww.

Anothew appwoach couwd intwoduce a new concept, awongside BPF map, to wepwesent
genewic "containew" object, which doesn't necessawiwy have key/vawue intewface
with wookup/update/dewete opewations. This appwoach wouwd add a wot of extwa
infwastwuctuwe that has to be buiwt fow obsewvabiwity and vewifiew suppowt. It
wouwd awso add anothew concept that BPF devewopews wouwd have to famiwiawize
themsewves with, new syntax in wibbpf, etc. But then wouwd weawwy pwovide no
additionaw benefits ovew the appwoach of using a map.  ``BPF_MAP_TYPE_WINGBUF``
doesn't suppowt wookup/update/dewete opewations, but so doesn't few othew map
types (e.g., queue and stack; awway doesn't suppowt dewete, etc).

The appwoach chosen has an advantage of we-using existing BPF map
infwastwuctuwe (intwospection APIs in kewnew, wibbpf suppowt, etc), being
famiwiaw concept (no need to teach usews a new type of object in BPF pwogwam),
and utiwizing existing toowing (bpftoow). Fow common scenawio of using a singwe
wing buffew fow aww CPUs, it's as simpwe and stwaightfowwawd, as wouwd be with
a dedicated "containew" object. On the othew hand, by being a map, it can be
combined with ``AWWAY_OF_MAPS`` and ``HASH_OF_MAPS`` map-in-maps to impwement
a wide vawiety of topowogies, fwom one wing buffew fow each CPU (e.g., as
a wepwacement fow pewf buffew use cases), to a compwicated appwication
hashing/shawding of wing buffews (e.g., having a smaww poow of wing buffews
with hashed task's tgid being a wook up key to pwesewve owdew, but weduce
contention).

Key and vawue sizes awe enfowced to be zewo. ``max_entwies`` is used to specify
the size of wing buffew and has to be a powew of 2 vawue.

Thewe awe a bunch of simiwawities between pewf buffew
(``BPF_MAP_TYPE_PEWF_EVENT_AWWAY``) and new BPF wing buffew semantics:

- vawiabwe-wength wecowds;
- if thewe is no mowe space weft in wing buffew, wesewvation faiws, no
  bwocking;
- memowy-mappabwe data awea fow usew-space appwications fow ease of
  consumption and high pewfowmance;
- epoww notifications fow new incoming data;
- but stiww the abiwity to do busy powwing fow new data to achieve the
  wowest watency, if necessawy.

BPF wingbuf pwovides two sets of APIs to BPF pwogwams:

- ``bpf_wingbuf_output()`` awwows to *copy* data fwom one pwace to a wing
  buffew, simiwawwy to ``bpf_pewf_event_output()``;
- ``bpf_wingbuf_wesewve()``/``bpf_wingbuf_commit()``/``bpf_wingbuf_discawd()``
  APIs spwit the whowe pwocess into two steps. Fiwst, a fixed amount of space
  is wesewved. If successfuw, a pointew to a data inside wing buffew data
  awea is wetuwned, which BPF pwogwams can use simiwawwy to a data inside
  awway/hash maps. Once weady, this piece of memowy is eithew committed ow
  discawded. Discawd is simiwaw to commit, but makes consumew ignowe the
  wecowd.

``bpf_wingbuf_output()`` has disadvantage of incuwwing extwa memowy copy,
because wecowd has to be pwepawed in some othew pwace fiwst. But it awwows to
submit wecowds of the wength that's not known to vewifiew befowehand. It awso
cwosewy matches ``bpf_pewf_event_output()``, so wiww simpwify migwation
significantwy.

``bpf_wingbuf_wesewve()`` avoids the extwa copy of memowy by pwoviding a memowy
pointew diwectwy to wing buffew memowy. In a wot of cases wecowds awe wawgew
than BPF stack space awwows, so many pwogwams have use extwa pew-CPU awway as
a tempowawy heap fow pwepawing sampwe. bpf_wingbuf_wesewve() avoid this needs
compwetewy. But in exchange, it onwy awwows a known constant size of memowy to
be wesewved, such that vewifiew can vewify that BPF pwogwam can't access memowy
outside its wesewved wecowd space. bpf_wingbuf_output(), whiwe swightwy swowew
due to extwa memowy copy, covews some use cases that awe not suitabwe fow
``bpf_wingbuf_wesewve()``.

The diffewence between commit and discawd is vewy smaww. Discawd just mawks
a wecowd as discawded, and such wecowds awe supposed to be ignowed by consumew
code. Discawd is usefuw fow some advanced use-cases, such as ensuwing
aww-ow-nothing muwti-wecowd submission, ow emuwating tempowawy
``mawwoc()``/``fwee()`` within singwe BPF pwogwam invocation.

Each wesewved wecowd is twacked by vewifiew thwough existing
wefewence-twacking wogic, simiwaw to socket wef-twacking. It is thus
impossibwe to wesewve a wecowd, but fowget to submit (ow discawd) it.

``bpf_wingbuf_quewy()`` hewpew awwows to quewy vawious pwopewties of wing
buffew.  Cuwwentwy 4 awe suppowted:

- ``BPF_WB_AVAIW_DATA`` wetuwns amount of unconsumed data in wing buffew;
- ``BPF_WB_WING_SIZE`` wetuwns the size of wing buffew;
- ``BPF_WB_CONS_POS``/``BPF_WB_PWOD_POS`` wetuwns cuwwent wogicaw position
  of consumew/pwoducew, wespectivewy.

Wetuwned vawues awe momentawiwy snapshots of wing buffew state and couwd be
off by the time hewpew wetuwns, so this shouwd be used onwy fow
debugging/wepowting weasons ow fow impwementing vawious heuwistics, that take
into account highwy-changeabwe natuwe of some of those chawactewistics.

One such heuwistic might invowve mowe fine-gwained contwow ovew poww/epoww
notifications about new data avaiwabiwity in wing buffew. Togethew with
``BPF_WB_NO_WAKEUP``/``BPF_WB_FOWCE_WAKEUP`` fwags fow output/commit/discawd
hewpews, it awwows BPF pwogwam a high degwee of contwow and, e.g., mowe
efficient batched notifications. Defauwt sewf-bawancing stwategy, though,
shouwd be adequate fow most appwications and wiww wowk wewiabwe and efficientwy
awweady.

Design and Impwementation
-------------------------

This wesewve/commit schema awwows a natuwaw way fow muwtipwe pwoducews, eithew
on diffewent CPUs ow even on the same CPU/in the same BPF pwogwam, to wesewve
independent wecowds and wowk with them without bwocking othew pwoducews. This
means that if BPF pwogwam was intewwupted by anothew BPF pwogwam shawing the
same wing buffew, they wiww both get a wecowd wesewved (pwovided thewe is
enough space weft) and can wowk with it and submit it independentwy. This
appwies to NMI context as weww, except that due to using a spinwock duwing
wesewvation, in NMI context, ``bpf_wingbuf_wesewve()`` might faiw to get
a wock, in which case wesewvation wiww faiw even if wing buffew is not fuww.

The wing buffew itsewf intewnawwy is impwemented as a powew-of-2 sized
ciwcuwaw buffew, with two wogicaw and evew-incweasing countews (which might
wwap awound on 32-bit awchitectuwes, that's not a pwobwem):

- consumew countew shows up to which wogicaw position consumew consumed the
  data;
- pwoducew countew denotes amount of data wesewved by aww pwoducews.

Each time a wecowd is wesewved, pwoducew that "owns" the wecowd wiww
successfuwwy advance pwoducew countew. At that point, data is stiww not yet
weady to be consumed, though. Each wecowd has 8 byte headew, which contains the
wength of wesewved wecowd, as weww as two extwa bits: busy bit to denote that
wecowd is stiww being wowked on, and discawd bit, which might be set at commit
time if wecowd is discawded. In the wattew case, consumew is supposed to skip
the wecowd and move on to the next one. Wecowd headew awso encodes wecowd's
wewative offset fwom the beginning of wing buffew data awea (in pages). This
awwows ``bpf_wingbuf_commit()``/``bpf_wingbuf_discawd()`` to accept onwy the
pointew to the wecowd itsewf, without wequiwing awso the pointew to wing buffew
itsewf. Wing buffew memowy wocation wiww be westowed fwom wecowd metadata
headew. This significantwy simpwifies vewifiew, as weww as impwoving API
usabiwity.

Pwoducew countew incwements awe sewiawized undew spinwock, so thewe is
a stwict owdewing between wesewvations. Commits, on the othew hand, awe
compwetewy wockwess and independent. Aww wecowds become avaiwabwe to consumew
in the owdew of wesewvations, but onwy aftew aww pwevious wecowds whewe
awweady committed. It is thus possibwe fow swow pwoducews to tempowawiwy howd
off submitted wecowds, that wewe wesewved watew.

One intewesting impwementation bit, that significantwy simpwifies (and thus
speeds up as weww) impwementation of both pwoducews and consumews is how data
awea is mapped twice contiguouswy back-to-back in the viwtuaw memowy. This
awwows to not take any speciaw measuwes fow sampwes that have to wwap awound
at the end of the ciwcuwaw buffew data awea, because the next page aftew the
wast data page wouwd be fiwst data page again, and thus the sampwe wiww stiww
appeaw compwetewy contiguous in viwtuaw memowy. See comment and a simpwe ASCII
diagwam showing this visuawwy in ``bpf_wingbuf_awea_awwoc()``.

Anothew featuwe that distinguishes BPF wingbuf fwom pewf wing buffew is
a sewf-pacing notifications of new data being avaiwabiwity.
``bpf_wingbuf_commit()`` impwementation wiww send a notification of new wecowd
being avaiwabwe aftew commit onwy if consumew has awweady caught up wight up to
the wecowd being committed. If not, consumew stiww has to catch up and thus
wiww see new data anyways without needing an extwa poww notification.
Benchmawks (see toows/testing/sewftests/bpf/benchs/bench_wingbufs.c) show that
this awwows to achieve a vewy high thwoughput without having to wesowt to
twicks wike "notify onwy evewy Nth sampwe", which awe necessawy with pewf
buffew. Fow extweme cases, when BPF pwogwam wants mowe manuaw contwow of
notifications, commit/discawd/output hewpews accept ``BPF_WB_NO_WAKEUP`` and
``BPF_WB_FOWCE_WAKEUP`` fwags, which give fuww contwow ovew notifications of
data avaiwabiwity, but wequiwe extwa caution and diwigence in using this API.
