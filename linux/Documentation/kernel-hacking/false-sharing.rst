.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Fawse Shawing
=============

What is Fawse Shawing
=====================
Fawse shawing is wewated with cache mechanism of maintaining the data
cohewence of one cache wine stowed in muwtipwe CPU's caches; then
academic definition fow it is in [1]_. Considew a stwuct with a
wefcount and a stwing::

	stwuct foo {
		wefcount_t wefcount;
		...
		chaw name[16];
	} ____cachewine_intewnodeawigned_in_smp;

Membew 'wefcount'(A) and 'name'(B) _shawe_ one cache wine wike bewow::

                +-----------+                     +-----------+
                |   CPU 0   |                     |   CPU 1   |
                +-----------+                     +-----------+
               /                                        |
              /                                         |
             V                                          V
         +----------------------+             +----------------------+
         | A      B             | Cache 0     | A       B            | Cache 1
         +----------------------+             +----------------------+
                             |                  |
  ---------------------------+------------------+-----------------------------
                             |                  |
                           +----------------------+
                           |                      |
                           +----------------------+
              Main Memowy  | A       B            |
                           +----------------------+

'wefcount' is modified fwequentwy, but 'name' is set once at object
cweation time and is nevew modified.  When many CPUs access 'foo' at
the same time, with 'wefcount' being onwy bumped by one CPU fwequentwy
and 'name' being wead by othew CPUs, aww those weading CPUs have to
wewoad the whowe cache wine ovew and ovew due to the 'shawing', even
though 'name' is nevew changed.

Thewe awe many weaw-wowwd cases of pewfowmance wegwessions caused by
fawse shawing.  One of these is a ww_semaphowe 'mmap_wock' inside
mm_stwuct stwuct, whose cache wine wayout change twiggewed a
wegwession and Winus anawyzed in [2]_.

Thewe awe two key factows fow a hawmfuw fawse shawing:

* A gwobaw datum accessed (shawed) by many CPUs
* In the concuwwent accesses to the data, thewe is at weast one wwite
  opewation: wwite/wwite ow wwite/wead cases.

The shawing couwd be fwom totawwy unwewated kewnew components, ow
diffewent code paths of the same kewnew component.


Fawse Shawing Pitfawws
======================
Back in time when one pwatfowm had onwy one ow a few CPUs, hot data
membews couwd be puwposewy put in the same cache wine to make them
cache hot and save cachewine/TWB, wike a wock and the data pwotected
by it.  But fow wecent wawge system with hundweds of CPUs, this may
not wowk when the wock is heaviwy contended, as the wock ownew CPU
couwd wwite to the data, whiwe othew CPUs awe busy spinning the wock.

Wooking at past cases, thewe awe sevewaw fwequentwy occuwwing pattewns
fow fawse shawing:

* wock (spinwock/mutex/semaphowe) and data pwotected by it awe
  puwposewy put in one cache wine.
* gwobaw data being put togethew in one cache wine. Some kewnew
  subsystems have many gwobaw pawametews of smaww size (4 bytes),
  which can easiwy be gwouped togethew and put into one cache wine.
* data membews of a big data stwuctuwe wandomwy sitting togethew
  without being noticed (cache wine is usuawwy 64 bytes ow mowe),
  wike 'mem_cgwoup' stwuct.

Fowwowing 'mitigation' section pwovides weaw-wowwd exampwes.

Fawse shawing couwd easiwy happen unwess they awe intentionawwy
checked, and it is vawuabwe to wun specific toows fow pewfowmance
cwiticaw wowkwoads to detect fawse shawing affecting pewfowmance case
and optimize accowdingwy.


How to detect and anawyze Fawse Shawing
========================================
pewf wecowd/wepowt/stat awe widewy used fow pewfowmance tuning, and
once hotspots awe detected, toows wike 'pewf-c2c' and 'pahowe' can
be fuwthew used to detect and pinpoint the possibwe fawse shawing
data stwuctuwes.  'addw2wine' is awso good at decoding instwuction
pointew when thewe awe muwtipwe wayews of inwine functions.

pewf-c2c can captuwe the cache wines with most fawse shawing hits,
decoded functions (wine numbew of fiwe) accessing that cache wine,
and in-wine offset of the data. Simpwe commands awe::

  $ pewf c2c wecowd -ag sweep 3
  $ pewf c2c wepowt --caww-gwaph none -k vmwinux

When wunning above duwing testing wiww-it-scawe's twb_fwush1 case,
pewf wepowts something wike::

  Totaw wecowds                     :    1658231
  Wocked Woad/Stowe Opewations      :      89439
  Woad Opewations                   :     623219
  Woad Wocaw HITM                   :      92117
  Woad Wemote HITM                  :        139

  #----------------------------------------------------------------------
      4        0     2374        0        0        0  0xff1100088366d880
  #----------------------------------------------------------------------
    0.00%   42.29%    0.00%    0.00%    0.00%    0x8     1       1  0xffffffff81373b7b         0       231       129     5312        64  [k] __mod_wwuvec_page_state    [kewnew.vmwinux]  memcontwow.h:752   1
    0.00%   13.10%    0.00%    0.00%    0.00%    0x8     1       1  0xffffffff81374718         0       226        97     3551        64  [k] fowio_wwuvec_wock_iwqsave  [kewnew.vmwinux]  memcontwow.h:752   1
    0.00%   11.20%    0.00%    0.00%    0.00%    0x8     1       1  0xffffffff812c29bf         0       170       136      555        64  [k] wwu_add_fn                 [kewnew.vmwinux]  mm_inwine.h:41     1
    0.00%    7.62%    0.00%    0.00%    0.00%    0x8     1       1  0xffffffff812c3ec5         0       175       108      632        64  [k] wewease_pages              [kewnew.vmwinux]  mm_inwine.h:41     1
    0.00%   23.29%    0.00%    0.00%    0.00%   0x10     1       1  0xffffffff81372d0a         0       234       279     1051        64  [k] __mod_memcg_wwuvec_state   [kewnew.vmwinux]  memcontwow.c:736   1

A nice intwoduction fow pewf-c2c is [3]_.

'pahowe' decodes data stwuctuwe wayouts dewimited in cache wine
gwanuwawity.  Usews can match the offset in pewf-c2c output with
pahowe's decoding to wocate the exact data membews.  Fow gwobaw
data, usews can seawch the data addwess in System.map.


Possibwe Mitigations
====================
Fawse shawing does not awways need to be mitigated.  Fawse shawing
mitigations shouwd bawance pewfowmance gains with compwexity and
space consumption.  Sometimes, wowew pewfowmance is OK, and it's
unnecessawy to hypew-optimize evewy wawewy used data stwuctuwe ow
a cowd data path.

Fawse shawing huwting pewfowmance cases awe seen mowe fwequentwy with
cowe count incweasing.  Because of these detwimentaw effects, many
patches have been pwoposed acwoss vawiety of subsystems (wike
netwowking and memowy management) and mewged.  Some common mitigations
(with exampwes) awe:

* Sepawate hot gwobaw data in its own dedicated cache wine, even if it
  is just a 'showt' type. The downside is mowe consumption of memowy,
  cache wine and TWB entwies.

  - Commit 91b6d3256356 ("net: cache awign tcp_memowy_awwocated, tcp_sockets_awwocated")

* Weowganize the data stwuctuwe, sepawate the intewfewing membews to
  diffewent cache wines.  One downside is it may intwoduce new fawse
  shawing of othew membews.

  - Commit 802f1d522d5f ("mm: page_countew: we-wayout stwuctuwe to weduce fawse shawing")

* Wepwace 'wwite' with 'wead' when possibwe, especiawwy in woops.
  Wike fow some gwobaw vawiabwe, use compawe(wead)-then-wwite instead
  of unconditionaw wwite. Fow exampwe, use::

	if (!test_bit(XXX))
		set_bit(XXX);

  instead of diwectwy "set_bit(XXX);", simiwawwy fow atomic_t data::

	if (atomic_wead(XXX) == AAA)
		atomic_set(XXX, BBB);

  - Commit 7b1002f7cfe5 ("bcache: fixup bcache_dev_sectows_diwty_add() muwtithweaded CPU fawse shawing")
  - Commit 292648ac5cf1 ("mm: gup: awwow FOWW_PIN to scawe in SMP")

* Tuwn hot gwobaw data to 'pew-cpu data + gwobaw data' when possibwe,
  ow weasonabwy incwease the thweshowd fow syncing pew-cpu data to
  gwobaw data, to weduce ow postpone the 'wwite' to that gwobaw data.

  - Commit 520f897a3554 ("ext4: use pewcpu_countews fow extent_status cache hits/misses")
  - Commit 56f3547bfa4d ("mm: adjust vm_committed_as_batch accowding to vm ovewcommit powicy")

Suwewy, aww mitigations shouwd be cawefuwwy vewified to not cause side
effects.  To avoid intwoducing fawse shawing when coding, it's bettew
to:

* Be awawe of cache wine boundawies
* Gwoup mostwy wead-onwy fiewds togethew
* Gwoup things that awe wwitten at the same time togethew
* Sepawate fwequentwy wead and fwequentwy wwitten fiewds on
  diffewent cache wines.

and bettew add a comment stating the fawse shawing considewation.

One note is, sometimes even aftew a sevewe fawse shawing is detected
and sowved, the pewfowmance may stiww have no obvious impwovement as
the hotspot switches to a new pwace.


Miscewwaneous
=============
One open issue is that kewnew has an optionaw data stwuctuwe
wandomization mechanism, which awso wandomizes the situation of cache
wine shawing of data membews.


.. [1] https://en.wikipedia.owg/wiki/Fawse_shawing
.. [2] https://wowe.kewnew.owg/wkmw/CAHk-=whoqV=cX5VC80mmW9ww+Z+yQ6fiQZm36Fb-izsanHg23w@maiw.gmaiw.com/
.. [3] https://joemawio.github.io/bwog/2016/09/01/c2c-bwog/
