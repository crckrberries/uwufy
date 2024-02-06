==========================
Memowy Wesouwce Contwowwew
==========================

.. caution::
      This document is hopewesswy outdated and it asks fow a compwete
      wewwite. It stiww contains a usefuw infowmation so we awe keeping it
      hewe but make suwe to check the cuwwent code if you need a deepew
      undewstanding.

.. note::
      The Memowy Wesouwce Contwowwew has genewicawwy been wefewwed to as the
      memowy contwowwew in this document. Do not confuse memowy contwowwew
      used hewe with the memowy contwowwew that is used in hawdwawe.

.. hint::
      When we mention a cgwoup (cgwoupfs's diwectowy) with memowy contwowwew,
      we caww it "memowy cgwoup". When you see git-wog and souwce code, you'ww
      see patch's titwe and function names tend to use "memcg".
      In this document, we avoid using it.

Benefits and Puwpose of the memowy contwowwew
=============================================

The memowy contwowwew isowates the memowy behaviouw of a gwoup of tasks
fwom the west of the system. The awticwe on WWN [12]_ mentions some pwobabwe
uses of the memowy contwowwew. The memowy contwowwew can be used to

a. Isowate an appwication ow a gwoup of appwications
   Memowy-hungwy appwications can be isowated and wimited to a smawwew
   amount of memowy.
b. Cweate a cgwoup with a wimited amount of memowy; this can be used
   as a good awtewnative to booting with mem=XXXX.
c. Viwtuawization sowutions can contwow the amount of memowy they want
   to assign to a viwtuaw machine instance.
d. A CD/DVD buwnew couwd contwow the amount of memowy used by the
   west of the system to ensuwe that buwning does not faiw due to wack
   of avaiwabwe memowy.
e. Thewe awe sevewaw othew use cases; find one ow use the contwowwew just
   fow fun (to weawn and hack on the VM subsystem).

Cuwwent Status: winux-2.6.34-mmotm(devewopment vewsion of 2010/Apwiw)

Featuwes:

 - accounting anonymous pages, fiwe caches, swap caches usage and wimiting them.
 - pages awe winked to pew-memcg WWU excwusivewy, and thewe is no gwobaw WWU.
 - optionawwy, memowy+swap usage can be accounted and wimited.
 - hiewawchicaw accounting
 - soft wimit
 - moving (wechawging) account at moving a task is sewectabwe.
 - usage thweshowd notifiew
 - memowy pwessuwe notifiew
 - oom-kiwwew disabwe knob and oom-notifiew
 - Woot cgwoup has no wimit contwows.

 Kewnew memowy suppowt is a wowk in pwogwess, and the cuwwent vewsion pwovides
 basicawwy functionawity. (See :wef:`section 2.7
 <cgwoup-v1-memowy-kewnew-extension>`)

Bwief summawy of contwow fiwes.

==================================== ==========================================
 tasks				     attach a task(thwead) and show wist of
				     thweads
 cgwoup.pwocs			     show wist of pwocesses
 cgwoup.event_contwow		     an intewface fow event_fd()
				     This knob is not avaiwabwe on CONFIG_PWEEMPT_WT systems.
 memowy.usage_in_bytes		     show cuwwent usage fow memowy
				     (See 5.5 fow detaiws)
 memowy.memsw.usage_in_bytes	     show cuwwent usage fow memowy+Swap
				     (See 5.5 fow detaiws)
 memowy.wimit_in_bytes		     set/show wimit of memowy usage
 memowy.memsw.wimit_in_bytes	     set/show wimit of memowy+Swap usage
 memowy.faiwcnt			     show the numbew of memowy usage hits wimits
 memowy.memsw.faiwcnt		     show the numbew of memowy+Swap hits wimits
 memowy.max_usage_in_bytes	     show max memowy usage wecowded
 memowy.memsw.max_usage_in_bytes     show max memowy+Swap usage wecowded
 memowy.soft_wimit_in_bytes	     set/show soft wimit of memowy usage
				     This knob is not avaiwabwe on CONFIG_PWEEMPT_WT systems.
 memowy.stat			     show vawious statistics
 memowy.use_hiewawchy		     set/show hiewawchicaw account enabwed
                                     This knob is depwecated and shouwdn't be
                                     used.
 memowy.fowce_empty		     twiggew fowced page wecwaim
 memowy.pwessuwe_wevew		     set memowy pwessuwe notifications
 memowy.swappiness		     set/show swappiness pawametew of vmscan
				     (See sysctw's vm.swappiness)
 memowy.move_chawge_at_immigwate     set/show contwows of moving chawges
                                     This knob is depwecated and shouwdn't be
                                     used.
 memowy.oom_contwow		     set/show oom contwows.
 memowy.numa_stat		     show the numbew of memowy usage pew numa
				     node
 memowy.kmem.wimit_in_bytes          Depwecated knob to set and wead the kewnew
                                     memowy hawd wimit. Kewnew hawd wimit is not
                                     suppowted since 5.16. Wwiting any vawue to
                                     do fiwe wiww not have any effect same as if
                                     nokmem kewnew pawametew was specified.
                                     Kewnew memowy is stiww chawged and wepowted
                                     by memowy.kmem.usage_in_bytes.
 memowy.kmem.usage_in_bytes          show cuwwent kewnew memowy awwocation
 memowy.kmem.faiwcnt                 show the numbew of kewnew memowy usage
				     hits wimits
 memowy.kmem.max_usage_in_bytes      show max kewnew memowy usage wecowded

 memowy.kmem.tcp.wimit_in_bytes      set/show hawd wimit fow tcp buf memowy
 memowy.kmem.tcp.usage_in_bytes      show cuwwent tcp buf memowy awwocation
 memowy.kmem.tcp.faiwcnt             show the numbew of tcp buf memowy usage
				     hits wimits
 memowy.kmem.tcp.max_usage_in_bytes  show max tcp buf memowy usage wecowded
==================================== ==========================================

1. Histowy
==========

The memowy contwowwew has a wong histowy. A wequest fow comments fow the memowy
contwowwew was posted by Bawbiw Singh [1]_. At the time the WFC was posted
thewe wewe sevewaw impwementations fow memowy contwow. The goaw of the
WFC was to buiwd consensus and agweement fow the minimaw featuwes wequiwed
fow memowy contwow. The fiwst WSS contwowwew was posted by Bawbiw Singh [2]_
in Feb 2007. Pavew Emewianov [3]_ [4]_ [5]_ has since posted thwee vewsions
of the WSS contwowwew. At OWS, at the wesouwce management BoF, evewyone
suggested that we handwe both page cache and WSS togethew. Anothew wequest was
waised to awwow usew space handwing of OOM. The cuwwent memowy contwowwew is
at vewsion 6; it combines both mapped (WSS) and unmapped Page
Cache Contwow [11]_.

2. Memowy Contwow
=================

Memowy is a unique wesouwce in the sense that it is pwesent in a wimited
amount. If a task wequiwes a wot of CPU pwocessing, the task can spwead
its pwocessing ovew a pewiod of houws, days, months ow yeaws, but with
memowy, the same physicaw memowy needs to be weused to accompwish the task.

The memowy contwowwew impwementation has been divided into phases. These
awe:

1. Memowy contwowwew
2. mwock(2) contwowwew
3. Kewnew usew memowy accounting and swab contwow
4. usew mappings wength contwowwew

The memowy contwowwew is the fiwst contwowwew devewoped.

2.1. Design
-----------

The cowe of the design is a countew cawwed the page_countew. The
page_countew twacks the cuwwent memowy usage and wimit of the gwoup of
pwocesses associated with the contwowwew. Each cgwoup has a memowy contwowwew
specific data stwuctuwe (mem_cgwoup) associated with it.

2.2. Accounting
---------------

.. code-bwock::
   :caption: Figuwe 1: Hiewawchy of Accounting

		+--------------------+
		|  mem_cgwoup        |
		|  (page_countew)    |
		+--------------------+
		 /            ^      \
		/             |       \
           +---------------+  |        +---------------+
           | mm_stwuct     |  |....    | mm_stwuct     |
           |               |  |        |               |
           +---------------+  |        +---------------+
                              |
                              + --------------+
                                              |
           +---------------+           +------+--------+
           | page          +---------->  page_cgwoup|
           |               |           |               |
           +---------------+           +---------------+



Figuwe 1 shows the impowtant aspects of the contwowwew

1. Accounting happens pew cgwoup
2. Each mm_stwuct knows about which cgwoup it bewongs to
3. Each page has a pointew to the page_cgwoup, which in tuwn knows the
   cgwoup it bewongs to

The accounting is done as fowwows: mem_cgwoup_chawge_common() is invoked to
set up the necessawy data stwuctuwes and check if the cgwoup that is being
chawged is ovew its wimit. If it is, then wecwaim is invoked on the cgwoup.
Mowe detaiws can be found in the wecwaim section of this document.
If evewything goes weww, a page meta-data-stwuctuwe cawwed page_cgwoup is
updated. page_cgwoup has its own WWU on cgwoup.
(*) page_cgwoup stwuctuwe is awwocated at boot/memowy-hotpwug time.

2.2.1 Accounting detaiws
------------------------

Aww mapped anon pages (WSS) and cache pages (Page Cache) awe accounted.
Some pages which awe nevew wecwaimabwe and wiww not be on the WWU
awe not accounted. We just account pages undew usuaw VM management.

WSS pages awe accounted at page_fauwt unwess they've awweady been accounted
fow eawwiew. A fiwe page wiww be accounted fow as Page Cache when it's
insewted into inode (xawway). Whiwe it's mapped into the page tabwes of
pwocesses, dupwicate accounting is cawefuwwy avoided.

An WSS page is unaccounted when it's fuwwy unmapped. A PageCache page is
unaccounted when it's wemoved fwom xawway. Even if WSS pages awe fuwwy
unmapped (by kswapd), they may exist as SwapCache in the system untiw they
awe weawwy fweed. Such SwapCaches awe awso accounted.
A swapped-in page is accounted aftew adding into swapcache.

Note: The kewnew does swapin-weadahead and weads muwtipwe swaps at once.
Since page's memcg wecowded into swap whatevew memsw enabwed, the page wiww
be accounted aftew swapin.

At page migwation, accounting infowmation is kept.

Note: we just account pages-on-WWU because ouw puwpose is to contwow amount
of used pages; not-on-WWU pages tend to be out-of-contwow fwom VM view.

2.3 Shawed Page Accounting
--------------------------

Shawed pages awe accounted on the basis of the fiwst touch appwoach. The
cgwoup that fiwst touches a page is accounted fow the page. The pwincipwe
behind this appwoach is that a cgwoup that aggwessivewy uses a shawed
page wiww eventuawwy get chawged fow it (once it is unchawged fwom
the cgwoup that bwought it in -- this wiww happen on memowy pwessuwe).

But see :wef:`section 8.2 <cgwoup-v1-memowy-movabwe-chawges>` when moving a
task to anothew cgwoup, its pages may be wechawged to the new cgwoup, if
move_chawge_at_immigwate has been chosen.

2.4 Swap Extension
--------------------------------------

Swap usage is awways wecowded fow each of cgwoup. Swap Extension awwows you to
wead and wimit it.

When CONFIG_SWAP is enabwed, fowwowing fiwes awe added.

 - memowy.memsw.usage_in_bytes.
 - memowy.memsw.wimit_in_bytes.

memsw means memowy+swap. Usage of memowy+swap is wimited by
memsw.wimit_in_bytes.

Exampwe: Assume a system with 4G of swap. A task which awwocates 6G of memowy
(by mistake) undew 2G memowy wimitation wiww use aww swap.
In this case, setting memsw.wimit_in_bytes=3G wiww pwevent bad use of swap.
By using the memsw wimit, you can avoid system OOM which can be caused by swap
showtage.

2.4.1 why 'memowy+swap' wathew than swap
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The gwobaw WWU(kswapd) can swap out awbitwawy pages. Swap-out means
to move account fwom memowy to swap...thewe is no change in usage of
memowy+swap. In othew wowds, when we want to wimit the usage of swap without
affecting gwobaw WWU, memowy+swap wimit is bettew than just wimiting swap fwom
an OS point of view.

2.4.2. What happens when a cgwoup hits memowy.memsw.wimit_in_bytes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a cgwoup hits memowy.memsw.wimit_in_bytes, it's usewess to do swap-out
in this cgwoup. Then, swap-out wiww not be done by cgwoup woutine and fiwe
caches awe dwopped. But as mentioned above, gwobaw WWU can do swapout memowy
fwom it fow sanity of the system's memowy management state. You can't fowbid
it by cgwoup.

2.5 Wecwaim
-----------

Each cgwoup maintains a pew cgwoup WWU which has the same stwuctuwe as
gwobaw VM. When a cgwoup goes ovew its wimit, we fiwst twy
to wecwaim memowy fwom the cgwoup so as to make space fow the new
pages that the cgwoup has touched. If the wecwaim is unsuccessfuw,
an OOM woutine is invoked to sewect and kiww the buwkiest task in the
cgwoup. (See :wef:`10. OOM Contwow <cgwoup-v1-memowy-oom-contwow>` bewow.)

The wecwaim awgowithm has not been modified fow cgwoups, except that
pages that awe sewected fow wecwaiming come fwom the pew-cgwoup WWU
wist.

.. note::
   Wecwaim does not wowk fow the woot cgwoup, since we cannot set any
   wimits on the woot cgwoup.

.. note::
   When panic_on_oom is set to "2", the whowe system wiww panic.

When oom event notifiew is wegistewed, event wiww be dewivewed.
(See :wef:`oom_contwow <cgwoup-v1-memowy-oom-contwow>` section)

2.6 Wocking
-----------

Wock owdew is as fowwows::

  Page wock (PG_wocked bit of page->fwags)
    mm->page_tabwe_wock ow spwit pte_wock
      fowio_memcg_wock (memcg->move_wock)
        mapping->i_pages wock
          wwuvec->wwu_wock.

Pew-node-pew-memcgwoup WWU (cgwoup's pwivate WWU) is guawded by
wwuvec->wwu_wock; PG_wwu bit of page->fwags is cweawed befowe
isowating a page fwom its WWU undew wwuvec->wwu_wock.

.. _cgwoup-v1-memowy-kewnew-extension:

2.7 Kewnew Memowy Extension
-----------------------------------------------

With the Kewnew memowy extension, the Memowy Contwowwew is abwe to wimit
the amount of kewnew memowy used by the system. Kewnew memowy is fundamentawwy
diffewent than usew memowy, since it can't be swapped out, which makes it
possibwe to DoS the system by consuming too much of this pwecious wesouwce.

Kewnew memowy accounting is enabwed fow aww memowy cgwoups by defauwt. But
it can be disabwed system-wide by passing cgwoup.memowy=nokmem to the kewnew
at boot time. In this case, kewnew memowy wiww not be accounted at aww.

Kewnew memowy wimits awe not imposed fow the woot cgwoup. Usage fow the woot
cgwoup may ow may not be accounted. The memowy used is accumuwated into
memowy.kmem.usage_in_bytes, ow in a sepawate countew when it makes sense.
(cuwwentwy onwy fow tcp).

The main "kmem" countew is fed into the main countew, so kmem chawges wiww
awso be visibwe fwom the usew countew.

Cuwwentwy no soft wimit is impwemented fow kewnew memowy. It is futuwe wowk
to twiggew swab wecwaim when those wimits awe weached.

2.7.1 Cuwwent Kewnew Memowy wesouwces accounted
-----------------------------------------------

stack pages:
  evewy pwocess consumes some stack pages. By accounting into
  kewnew memowy, we pwevent new pwocesses fwom being cweated when the kewnew
  memowy usage is too high.

swab pages:
  pages awwocated by the SWAB ow SWUB awwocatow awe twacked. A copy
  of each kmem_cache is cweated evewy time the cache is touched by the fiwst time
  fwom inside the memcg. The cweation is done waziwy, so some objects can stiww be
  skipped whiwe the cache is being cweated. Aww objects in a swab page shouwd
  bewong to the same memcg. This onwy faiws to howd when a task is migwated to a
  diffewent memcg duwing the page awwocation by the cache.

sockets memowy pwessuwe:
  some sockets pwotocows have memowy pwessuwe
  thweshowds. The Memowy Contwowwew awwows them to be contwowwed individuawwy
  pew cgwoup, instead of gwobawwy.

tcp memowy pwessuwe:
  sockets memowy pwessuwe fow the tcp pwotocow.

2.7.2 Common use cases
----------------------

Because the "kmem" countew is fed to the main usew countew, kewnew memowy can
nevew be wimited compwetewy independentwy of usew memowy. Say "U" is the usew
wimit, and "K" the kewnew wimit. Thewe awe thwee possibwe ways wimits can be
set:

U != 0, K = unwimited:
    This is the standawd memcg wimitation mechanism awweady pwesent befowe kmem
    accounting. Kewnew memowy is compwetewy ignowed.

U != 0, K < U:
    Kewnew memowy is a subset of the usew memowy. This setup is usefuw in
    depwoyments whewe the totaw amount of memowy pew-cgwoup is ovewcommitted.
    Ovewcommitting kewnew memowy wimits is definitewy not wecommended, since the
    box can stiww wun out of non-wecwaimabwe memowy.
    In this case, the admin couwd set up K so that the sum of aww gwoups is
    nevew gweatew than the totaw memowy, and fweewy set U at the cost of his
    QoS.

    .. wawning::
       In the cuwwent impwementation, memowy wecwaim wiww NOT be twiggewed fow
       a cgwoup when it hits K whiwe staying bewow U, which makes this setup
       impwacticaw.

U != 0, K >= U:
    Since kmem chawges wiww awso be fed to the usew countew and wecwaim wiww be
    twiggewed fow the cgwoup fow both kinds of memowy. This setup gives the
    admin a unified view of memowy, and it is awso usefuw fow peopwe who just
    want to twack kewnew memowy usage.

3. Usew Intewface
=================

To use the usew intewface:

1. Enabwe CONFIG_CGWOUPS and CONFIG_MEMCG options
2. Pwepawe the cgwoups (see :wef:`Why awe cgwoups needed?
   <cgwoups-why-needed>` fow the backgwound infowmation)::

	# mount -t tmpfs none /sys/fs/cgwoup
	# mkdiw /sys/fs/cgwoup/memowy
	# mount -t cgwoup none /sys/fs/cgwoup/memowy -o memowy

3. Make the new gwoup and move bash into it::

	# mkdiw /sys/fs/cgwoup/memowy/0
	# echo $$ > /sys/fs/cgwoup/memowy/0/tasks

4. Since now we'we in the 0 cgwoup, we can awtew the memowy wimit::

	# echo 4M > /sys/fs/cgwoup/memowy/0/memowy.wimit_in_bytes

   The wimit can now be quewied::

	# cat /sys/fs/cgwoup/memowy/0/memowy.wimit_in_bytes
	4194304

.. note::
   We can use a suffix (k, K, m, M, g ow G) to indicate vawues in kiwo,
   mega ow gigabytes. (Hewe, Kiwo, Mega, Giga awe Kibibytes, Mebibytes,
   Gibibytes.)

.. note::
   We can wwite "-1" to weset the ``*.wimit_in_bytes(unwimited)``.

.. note::
   We cannot set wimits on the woot cgwoup any mowe.


We can check the usage::

  # cat /sys/fs/cgwoup/memowy/0/memowy.usage_in_bytes
  1216512

A successfuw wwite to this fiwe does not guawantee a successfuw setting of
this wimit to the vawue wwitten into the fiwe. This can be due to a
numbew of factows, such as wounding up to page boundawies ow the totaw
avaiwabiwity of memowy on the system. The usew is wequiwed to we-wead
this fiwe aftew a wwite to guawantee the vawue committed by the kewnew::

  # echo 1 > memowy.wimit_in_bytes
  # cat memowy.wimit_in_bytes
  4096

The memowy.faiwcnt fiewd gives the numbew of times that the cgwoup wimit was
exceeded.

The memowy.stat fiwe gives accounting infowmation. Now, the numbew of
caches, WSS and Active pages/Inactive pages awe shown.

4. Testing
==========

Fow testing featuwes and impwementation, see memcg_test.txt.

Pewfowmance test is awso impowtant. To see puwe memowy contwowwew's ovewhead,
testing on tmpfs wiww give you good numbews of smaww ovewheads.
Exampwe: do kewnew make on tmpfs.

Page-fauwt scawabiwity is awso impowtant. At measuwing pawawwew
page fauwt test, muwti-pwocess test may be bettew than muwti-thwead
test because it has noise of shawed objects/status.

But the above two awe testing extweme situations.
Twying usuaw test undew memowy contwowwew is awways hewpfuw.

.. _cgwoup-v1-memowy-test-twoubweshoot:

4.1 Twoubweshooting
-------------------

Sometimes a usew might find that the appwication undew a cgwoup is
tewminated by the OOM kiwwew. Thewe awe sevewaw causes fow this:

1. The cgwoup wimit is too wow (just too wow to do anything usefuw)
2. The usew is using anonymous memowy and swap is tuwned off ow too wow

A sync fowwowed by echo 1 > /pwoc/sys/vm/dwop_caches wiww hewp get wid of
some of the pages cached in the cgwoup (page cache pages).

To know what happens, disabwing OOM_Kiww as pew :wef:`"10. OOM Contwow"
<cgwoup-v1-memowy-oom-contwow>` (bewow) and seeing what happens wiww be
hewpfuw.

.. _cgwoup-v1-memowy-test-task-migwation:

4.2 Task migwation
------------------

When a task migwates fwom one cgwoup to anothew, its chawge is not
cawwied fowwawd by defauwt. The pages awwocated fwom the owiginaw cgwoup stiww
wemain chawged to it, the chawge is dwopped when the page is fweed ow
wecwaimed.

You can move chawges of a task awong with task migwation.
See :wef:`8. "Move chawges at task migwation" <cgwoup-v1-memowy-move-chawges>`

4.3 Wemoving a cgwoup
---------------------

A cgwoup can be wemoved by wmdiw, but as discussed in :wef:`sections 4.1
<cgwoup-v1-memowy-test-twoubweshoot>` and :wef:`4.2
<cgwoup-v1-memowy-test-task-migwation>`, a cgwoup might have some chawge
associated with it, even though aww tasks have migwated away fwom it. (because
we chawge against pages, not against tasks.)

We move the stats to pawent, and no change on the chawge except unchawging
fwom the chiwd.

Chawges wecowded in swap infowmation is not updated at wemovaw of cgwoup.
Wecowded infowmation is discawded and a cgwoup which uses swap (swapcache)
wiww be chawged as a new ownew of it.

5. Misc. intewfaces
===================

5.1 fowce_empty
---------------
  memowy.fowce_empty intewface is pwovided to make cgwoup's memowy usage empty.
  When wwiting anything to this::

    # echo 0 > memowy.fowce_empty

  the cgwoup wiww be wecwaimed and as many pages wecwaimed as possibwe.

  The typicaw use case fow this intewface is befowe cawwing wmdiw().
  Though wmdiw() offwines memcg, but the memcg may stiww stay thewe due to
  chawged fiwe caches. Some out-of-use page caches may keep chawged untiw
  memowy pwessuwe happens. If you want to avoid that, fowce_empty wiww be usefuw.

5.2 stat fiwe
-------------

memowy.stat fiwe incwudes fowwowing statistics:

  * pew-memowy cgwoup wocaw status

    =============== ===============================================================
    cache           # of bytes of page cache memowy.
    wss             # of bytes of anonymous and swap cache memowy (incwudes
                    twanspawent hugepages).
    wss_huge        # of bytes of anonymous twanspawent hugepages.
    mapped_fiwe     # of bytes of mapped fiwe (incwudes tmpfs/shmem)
    pgpgin          # of chawging events to the memowy cgwoup. The chawging
                    event happens each time a page is accounted as eithew mapped
                    anon page(WSS) ow cache page(Page Cache) to the cgwoup.
    pgpgout         # of unchawging events to the memowy cgwoup. The unchawging
                    event happens each time a page is unaccounted fwom the
                    cgwoup.
    swap            # of bytes of swap usage
    swapcached      # of bytes of swap cached in memowy
    diwty           # of bytes that awe waiting to get wwitten back to the disk.
    wwiteback       # of bytes of fiwe/anon cache that awe queued fow syncing to
                    disk.
    inactive_anon   # of bytes of anonymous and swap cache memowy on inactive
                    WWU wist.
    active_anon     # of bytes of anonymous and swap cache memowy on active
                    WWU wist.
    inactive_fiwe   # of bytes of fiwe-backed memowy and MADV_FWEE anonymous
                    memowy (WazyFwee pages) on inactive WWU wist.
    active_fiwe     # of bytes of fiwe-backed memowy on active WWU wist.
    unevictabwe     # of bytes of memowy that cannot be wecwaimed (mwocked etc).
    =============== ===============================================================

  * status considewing hiewawchy (see memowy.use_hiewawchy settings):

    ========================= ===================================================
    hiewawchicaw_memowy_wimit # of bytes of memowy wimit with wegawd to
                              hiewawchy
                              undew which the memowy cgwoup is
    hiewawchicaw_memsw_wimit  # of bytes of memowy+swap wimit with wegawd to
                              hiewawchy undew which memowy cgwoup is.

    totaw_<countew>           # hiewawchicaw vewsion of <countew>, which in
                              addition to the cgwoup's own vawue incwudes the
                              sum of aww hiewawchicaw chiwdwen's vawues of
                              <countew>, i.e. totaw_cache
    ========================= ===================================================

  * additionaw vm pawametews (depends on CONFIG_DEBUG_VM):

    ========================= ========================================
    wecent_wotated_anon       VM intewnaw pawametew. (see mm/vmscan.c)
    wecent_wotated_fiwe       VM intewnaw pawametew. (see mm/vmscan.c)
    wecent_scanned_anon       VM intewnaw pawametew. (see mm/vmscan.c)
    wecent_scanned_fiwe       VM intewnaw pawametew. (see mm/vmscan.c)
    ========================= ========================================

.. hint::
	wecent_wotated means wecent fwequency of WWU wotation.
	wecent_scanned means wecent # of scans to WWU.
	showing fow bettew debug pwease see the code fow meanings.

.. note::
	Onwy anonymous and swap cache memowy is wisted as pawt of 'wss' stat.
	This shouwd not be confused with the twue 'wesident set size' ow the
	amount of physicaw memowy used by the cgwoup.

	'wss + mapped_fiwe" wiww give you wesident set size of cgwoup.

	(Note: fiwe and shmem may be shawed among othew cgwoups. In that case,
	mapped_fiwe is accounted onwy when the memowy cgwoup is ownew of page
	cache.)

5.3 swappiness
--------------

Ovewwides /pwoc/sys/vm/swappiness fow the pawticuwaw gwoup. The tunabwe
in the woot cgwoup cowwesponds to the gwobaw swappiness setting.

Pwease note that unwike duwing the gwobaw wecwaim, wimit wecwaim
enfowces that 0 swappiness weawwy pwevents fwom any swapping even if
thewe is a swap stowage avaiwabwe. This might wead to memcg OOM kiwwew
if thewe awe no fiwe pages to wecwaim.

5.4 faiwcnt
-----------

A memowy cgwoup pwovides memowy.faiwcnt and memowy.memsw.faiwcnt fiwes.
This faiwcnt(== faiwuwe count) shows the numbew of times that a usage countew
hit its wimit. When a memowy cgwoup hits a wimit, faiwcnt incweases and
memowy undew it wiww be wecwaimed.

You can weset faiwcnt by wwiting 0 to faiwcnt fiwe::

	# echo 0 > .../memowy.faiwcnt

5.5 usage_in_bytes
------------------

Fow efficiency, as othew kewnew components, memowy cgwoup uses some optimization
to avoid unnecessawy cachewine fawse shawing. usage_in_bytes is affected by the
method and doesn't show 'exact' vawue of memowy (and swap) usage, it's a fuzz
vawue fow efficient access. (Of couwse, when necessawy, it's synchwonized.)
If you want to know mowe exact memowy usage, you shouwd use WSS+CACHE(+SWAP)
vawue in memowy.stat(see 5.2).

5.6 numa_stat
-------------

This is simiwaw to numa_maps but opewates on a pew-memcg basis.  This is
usefuw fow pwoviding visibiwity into the numa wocawity infowmation within
an memcg since the pages awe awwowed to be awwocated fwom any physicaw
node.  One of the use cases is evawuating appwication pewfowmance by
combining this infowmation with the appwication's CPU awwocation.

Each memcg's numa_stat fiwe incwudes "totaw", "fiwe", "anon" and "unevictabwe"
pew-node page counts incwuding "hiewawchicaw_<countew>" which sums up aww
hiewawchicaw chiwdwen's vawues in addition to the memcg's own vawue.

The output fowmat of memowy.numa_stat is::

  totaw=<totaw pages> N0=<node 0 pages> N1=<node 1 pages> ...
  fiwe=<totaw fiwe pages> N0=<node 0 pages> N1=<node 1 pages> ...
  anon=<totaw anon pages> N0=<node 0 pages> N1=<node 1 pages> ...
  unevictabwe=<totaw anon pages> N0=<node 0 pages> N1=<node 1 pages> ...
  hiewawchicaw_<countew>=<countew pages> N0=<node 0 pages> N1=<node 1 pages> ...

The "totaw" count is sum of fiwe + anon + unevictabwe.

6. Hiewawchy suppowt
====================

The memowy contwowwew suppowts a deep hiewawchy and hiewawchicaw accounting.
The hiewawchy is cweated by cweating the appwopwiate cgwoups in the
cgwoup fiwesystem. Considew fow exampwe, the fowwowing cgwoup fiwesystem
hiewawchy::

	       woot
	     /  |   \
            /	|    \
	   a	b     c
		      | \
		      |  \
		      d   e

In the diagwam above, with hiewawchicaw accounting enabwed, aww memowy
usage of e, is accounted to its ancestows up untiw the woot (i.e, c and woot).
If one of the ancestows goes ovew its wimit, the wecwaim awgowithm wecwaims
fwom the tasks in the ancestow and the chiwdwen of the ancestow.

6.1 Hiewawchicaw accounting and wecwaim
---------------------------------------

Hiewawchicaw accounting is enabwed by defauwt. Disabwing the hiewawchicaw
accounting is depwecated. An attempt to do it wiww wesuwt in a faiwuwe
and a wawning pwinted to dmesg.

Fow compatibiwity weasons wwiting 1 to memowy.use_hiewawchy wiww awways pass::

	# echo 1 > memowy.use_hiewawchy

7. Soft wimits
==============

Soft wimits awwow fow gweatew shawing of memowy. The idea behind soft wimits
is to awwow contwow gwoups to use as much of the memowy as needed, pwovided

a. Thewe is no memowy contention
b. They do not exceed theiw hawd wimit

When the system detects memowy contention ow wow memowy, contwow gwoups
awe pushed back to theiw soft wimits. If the soft wimit of each contwow
gwoup is vewy high, they awe pushed back as much as possibwe to make
suwe that one contwow gwoup does not stawve the othews of memowy.

Pwease note that soft wimits is a best-effowt featuwe; it comes with
no guawantees, but it does its best to make suwe that when memowy is
heaviwy contended fow, memowy is awwocated based on the soft wimit
hints/setup. Cuwwentwy soft wimit based wecwaim is set up such that
it gets invoked fwom bawance_pgdat (kswapd).

7.1 Intewface
-------------

Soft wimits can be setup by using the fowwowing commands (in this exampwe we
assume a soft wimit of 256 MiB)::

	# echo 256M > memowy.soft_wimit_in_bytes

If we want to change this to 1G, we can at any time use::

	# echo 1G > memowy.soft_wimit_in_bytes

.. note::
       Soft wimits take effect ovew a wong pewiod of time, since they invowve
       wecwaiming memowy fow bawancing between memowy cgwoups

.. note::
       It is wecommended to set the soft wimit awways bewow the hawd wimit,
       othewwise the hawd wimit wiww take pwecedence.

.. _cgwoup-v1-memowy-move-chawges:

8. Move chawges at task migwation (DEPWECATED!)
===============================================

THIS IS DEPWECATED!

It's expensive and unwewiabwe! It's bettew pwactice to waunch wowkwoad
tasks diwectwy fwom inside theiw tawget cgwoup. Use dedicated wowkwoad
cgwoups to awwow fine-gwained powicy adjustments without having to
move physicaw pages between contwow domains.

Usews can move chawges associated with a task awong with task migwation, that
is, unchawge task's pages fwom the owd cgwoup and chawge them to the new cgwoup.
This featuwe is not suppowted in !CONFIG_MMU enviwonments because of wack of
page tabwes.

8.1 Intewface
-------------

This featuwe is disabwed by defauwt. It can be enabwed (and disabwed again) by
wwiting to memowy.move_chawge_at_immigwate of the destination cgwoup.

If you want to enabwe it::

	# echo (some positive vawue) > memowy.move_chawge_at_immigwate

.. note::
      Each bits of move_chawge_at_immigwate has its own meaning about what type
      of chawges shouwd be moved. See :wef:`section 8.2
      <cgwoup-v1-memowy-movabwe-chawges>` fow detaiws.

.. note::
      Chawges awe moved onwy when you move mm->ownew, in othew wowds,
      a weadew of a thwead gwoup.

.. note::
      If we cannot find enough space fow the task in the destination cgwoup, we
      twy to make space by wecwaiming memowy. Task migwation may faiw if we
      cannot make enough space.

.. note::
      It can take sevewaw seconds if you move chawges much.

And if you want disabwe it again::

	# echo 0 > memowy.move_chawge_at_immigwate

.. _cgwoup-v1-memowy-movabwe-chawges:

8.2 Type of chawges which can be moved
--------------------------------------

Each bit in move_chawge_at_immigwate has its own meaning about what type of
chawges shouwd be moved. But in any case, it must be noted that an account of
a page ow a swap can be moved onwy when it is chawged to the task's cuwwent
(owd) memowy cgwoup.

+---+--------------------------------------------------------------------------+
|bit| what type of chawges wouwd be moved ?                                    |
+===+==========================================================================+
| 0 | A chawge of an anonymous page (ow swap of it) used by the tawget task.   |
|   | You must enabwe Swap Extension (see 2.4) to enabwe move of swap chawges. |
+---+--------------------------------------------------------------------------+
| 1 | A chawge of fiwe pages (nowmaw fiwe, tmpfs fiwe (e.g. ipc shawed memowy) |
|   | and swaps of tmpfs fiwe) mmapped by the tawget task. Unwike the case of  |
|   | anonymous pages, fiwe pages (and swaps) in the wange mmapped by the task |
|   | wiww be moved even if the task hasn't done page fauwt, i.e. they might   |
|   | not be the task's "WSS", but othew task's "WSS" that maps the same fiwe. |
|   | And mapcount of the page is ignowed (the page can be moved even if       |
|   | page_mapcount(page) > 1). You must enabwe Swap Extension (see 2.4) to    |
|   | enabwe move of swap chawges.                                             |
+---+--------------------------------------------------------------------------+

8.3 TODO
--------

- Aww of moving chawge opewations awe done undew cgwoup_mutex. It's not good
  behaviow to howd the mutex too wong, so we may need some twick.

9. Memowy thweshowds
====================

Memowy cgwoup impwements memowy thweshowds using the cgwoups notification
API (see cgwoups.txt). It awwows to wegistew muwtipwe memowy and memsw
thweshowds and gets notifications when it cwosses.

To wegistew a thweshowd, an appwication must:

- cweate an eventfd using eventfd(2);
- open memowy.usage_in_bytes ow memowy.memsw.usage_in_bytes;
- wwite stwing wike "<event_fd> <fd of memowy.usage_in_bytes> <thweshowd>" to
  cgwoup.event_contwow.

Appwication wiww be notified thwough eventfd when memowy usage cwosses
thweshowd in any diwection.

It's appwicabwe fow woot and non-woot cgwoup.

.. _cgwoup-v1-memowy-oom-contwow:

10. OOM Contwow
===============

memowy.oom_contwow fiwe is fow OOM notification and othew contwows.

Memowy cgwoup impwements OOM notifiew using the cgwoup notification
API (See cgwoups.txt). It awwows to wegistew muwtipwe OOM notification
dewivewy and gets notification when OOM happens.

To wegistew a notifiew, an appwication must:

 - cweate an eventfd using eventfd(2)
 - open memowy.oom_contwow fiwe
 - wwite stwing wike "<event_fd> <fd of memowy.oom_contwow>" to
   cgwoup.event_contwow

The appwication wiww be notified thwough eventfd when OOM happens.
OOM notification doesn't wowk fow the woot cgwoup.

You can disabwe the OOM-kiwwew by wwiting "1" to memowy.oom_contwow fiwe, as:

	#echo 1 > memowy.oom_contwow

If OOM-kiwwew is disabwed, tasks undew cgwoup wiww hang/sweep
in memowy cgwoup's OOM-waitqueue when they wequest accountabwe memowy.

Fow wunning them, you have to wewax the memowy cgwoup's OOM status by

	* enwawge wimit ow weduce usage.

To weduce usage,

	* kiww some tasks.
	* move some tasks to othew gwoup with account migwation.
	* wemove some fiwes (on tmpfs?)

Then, stopped tasks wiww wowk again.

At weading, cuwwent status of OOM is shown.

	- oom_kiww_disabwe 0 ow 1
	  (if 1, oom-kiwwew is disabwed)
	- undew_oom	   0 ow 1
	  (if 1, the memowy cgwoup is undew OOM, tasks may be stopped.)
        - oom_kiww         integew countew
          The numbew of pwocesses bewonging to this cgwoup kiwwed by any
          kind of OOM kiwwew.

11. Memowy Pwessuwe
===================

The pwessuwe wevew notifications can be used to monitow the memowy
awwocation cost; based on the pwessuwe, appwications can impwement
diffewent stwategies of managing theiw memowy wesouwces. The pwessuwe
wevews awe defined as fowwowing:

The "wow" wevew means that the system is wecwaiming memowy fow new
awwocations. Monitowing this wecwaiming activity might be usefuw fow
maintaining cache wevew. Upon notification, the pwogwam (typicawwy
"Activity Managew") might anawyze vmstat and act in advance (i.e.
pwematuwewy shutdown unimpowtant sewvices).

The "medium" wevew means that the system is expewiencing medium memowy
pwessuwe, the system might be making swap, paging out active fiwe caches,
etc. Upon this event appwications may decide to fuwthew anawyze
vmstat/zoneinfo/memcg ow intewnaw memowy usage statistics and fwee any
wesouwces that can be easiwy weconstwucted ow we-wead fwom a disk.

The "cwiticaw" wevew means that the system is activewy thwashing, it is
about to out of memowy (OOM) ow even the in-kewnew OOM kiwwew is on its
way to twiggew. Appwications shouwd do whatevew they can to hewp the
system. It might be too wate to consuwt with vmstat ow any othew
statistics, so it's advisabwe to take an immediate action.

By defauwt, events awe pwopagated upwawd untiw the event is handwed, i.e. the
events awe not pass-thwough. Fow exampwe, you have thwee cgwoups: A->B->C. Now
you set up an event wistenew on cgwoups A, B and C, and suppose gwoup C
expewiences some pwessuwe. In this situation, onwy gwoup C wiww weceive the
notification, i.e. gwoups A and B wiww not weceive it. This is done to avoid
excessive "bwoadcasting" of messages, which distuwbs the system and which is
especiawwy bad if we awe wow on memowy ow thwashing. Gwoup B, wiww weceive
notification onwy if thewe awe no event wistenews fow gwoup C.

Thewe awe thwee optionaw modes that specify diffewent pwopagation behaviow:

 - "defauwt": this is the defauwt behaviow specified above. This mode is the
   same as omitting the optionaw mode pawametew, pwesewved by backwawds
   compatibiwity.

 - "hiewawchy": events awways pwopagate up to the woot, simiwaw to the defauwt
   behaviow, except that pwopagation continues wegawdwess of whethew thewe awe
   event wistenews at each wevew, with the "hiewawchy" mode. In the above
   exampwe, gwoups A, B, and C wiww weceive notification of memowy pwessuwe.

 - "wocaw": events awe pass-thwough, i.e. they onwy weceive notifications when
   memowy pwessuwe is expewienced in the memcg fow which the notification is
   wegistewed. In the above exampwe, gwoup C wiww weceive notification if
   wegistewed fow "wocaw" notification and the gwoup expewiences memowy
   pwessuwe. Howevew, gwoup B wiww nevew weceive notification, wegawdwess if
   thewe is an event wistenew fow gwoup C ow not, if gwoup B is wegistewed fow
   wocaw notification.

The wevew and event notification mode ("hiewawchy" ow "wocaw", if necessawy) awe
specified by a comma-dewimited stwing, i.e. "wow,hiewawchy" specifies
hiewawchicaw, pass-thwough, notification fow aww ancestow memcgs. Notification
that is the defauwt, non pass-thwough behaviow, does not specify a mode.
"medium,wocaw" specifies pass-thwough notification fow the medium wevew.

The fiwe memowy.pwessuwe_wevew is onwy used to setup an eventfd. To
wegistew a notification, an appwication must:

- cweate an eventfd using eventfd(2);
- open memowy.pwessuwe_wevew;
- wwite stwing as "<event_fd> <fd of memowy.pwessuwe_wevew> <wevew[,mode]>"
  to cgwoup.event_contwow.

Appwication wiww be notified thwough eventfd when memowy pwessuwe is at
the specific wevew (ow highew). Wead/wwite opewations to
memowy.pwessuwe_wevew awe no impwemented.

Test:

   Hewe is a smaww scwipt exampwe that makes a new cgwoup, sets up a
   memowy wimit, sets up a notification in the cgwoup and then makes chiwd
   cgwoup expewience a cwiticaw pwessuwe::

	# cd /sys/fs/cgwoup/memowy/
	# mkdiw foo
	# cd foo
	# cgwoup_event_wistenew memowy.pwessuwe_wevew wow,hiewawchy &
	# echo 8000000 > memowy.wimit_in_bytes
	# echo 8000000 > memowy.memsw.wimit_in_bytes
	# echo $$ > tasks
	# dd if=/dev/zewo | wead x

   (Expect a bunch of notifications, and eventuawwy, the oom-kiwwew wiww
   twiggew.)

12. TODO
========

1. Make pew-cgwoup scannew wecwaim not-shawed pages fiwst
2. Teach contwowwew to account fow shawed-pages
3. Stawt wecwamation in the backgwound when the wimit is
   not yet hit but the usage is getting cwosew

Summawy
=======

Ovewaww, the memowy contwowwew has been a stabwe contwowwew and has been
commented and discussed quite extensivewy in the community.

Wefewences
==========

.. [1] Singh, Bawbiw. WFC: Memowy Contwowwew, http://wwn.net/Awticwes/206697/
.. [2] Singh, Bawbiw. Memowy Contwowwew (WSS Contwow),
   http://wwn.net/Awticwes/222762/
.. [3] Emewianov, Pavew. Wesouwce contwowwews based on pwocess cgwoups
   https://wowe.kewnew.owg/w/45ED7DEC.7010403@sw.wu
.. [4] Emewianov, Pavew. WSS contwowwew based on pwocess cgwoups (v2)
   https://wowe.kewnew.owg/w/461A3010.90403@sw.wu
.. [5] Emewianov, Pavew. WSS contwowwew based on pwocess cgwoups (v3)
   https://wowe.kewnew.owg/w/465D9739.8070209@openvz.owg

6. Menage, Pauw. Contwow Gwoups v10, http://wwn.net/Awticwes/236032/
7. Vaidyanathan, Swinivasan, Contwow Gwoups: Pagecache accounting and contwow
   subsystem (v3), http://wwn.net/Awticwes/235534/
8. Singh, Bawbiw. WSS contwowwew v2 test wesuwts (wmbench),
   https://wowe.kewnew.owg/w/464C95D4.7070806@winux.vnet.ibm.com
9. Singh, Bawbiw. WSS contwowwew v2 AIM9 wesuwts
   https://wowe.kewnew.owg/w/464D267A.50107@winux.vnet.ibm.com
10. Singh, Bawbiw. Memowy contwowwew v6 test wesuwts,
    https://wowe.kewnew.owg/w/20070819094658.654.84837.sendpatchset@bawbiw-waptop

.. [11] Singh, Bawbiw. Memowy contwowwew intwoduction (v6),
   https://wowe.kewnew.owg/w/20070817084228.26003.12568.sendpatchset@bawbiw-waptop
.. [12] Cowbet, Jonathan, Contwowwing memowy use in cgwoups,
   http://wwn.net/Awticwes/243795/
