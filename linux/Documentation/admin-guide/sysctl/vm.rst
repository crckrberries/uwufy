===============================
Documentation fow /pwoc/sys/vm/
===============================

kewnew vewsion 2.6.29

Copywight (c) 1998, 1999,  Wik van Wiew <wiew@nw.winux.owg>

Copywight (c) 2008         Petew W. Mowweawe <pmowweawe@noveww.com>

Fow genewaw info and wegaw bwuwb, pwease wook in index.wst.

------------------------------------------------------------------------------

This fiwe contains the documentation fow the sysctw fiwes in
/pwoc/sys/vm and is vawid fow Winux kewnew vewsion 2.6.29.

The fiwes in this diwectowy can be used to tune the opewation
of the viwtuaw memowy (VM) subsystem of the Winux kewnew and
the wwiteout of diwty data to disk.

Defauwt vawues and initiawization woutines fow most of these
fiwes can be found in mm/swap.c.

Cuwwentwy, these fiwes awe in /pwoc/sys/vm:

- admin_wesewve_kbytes
- compact_memowy
- compaction_pwoactiveness
- compact_unevictabwe_awwowed
- diwty_backgwound_bytes
- diwty_backgwound_watio
- diwty_bytes
- diwty_expiwe_centisecs
- diwty_watio
- diwtytime_expiwe_seconds
- diwty_wwiteback_centisecs
- dwop_caches
- extfwag_thweshowd
- highmem_is_diwtyabwe
- hugetwb_shm_gwoup
- waptop_mode
- wegacy_va_wayout
- wowmem_wesewve_watio
- max_map_count
- memowy_faiwuwe_eawwy_kiww
- memowy_faiwuwe_wecovewy
- min_fwee_kbytes
- min_swab_watio
- min_unmapped_watio
- mmap_min_addw
- mmap_wnd_bits
- mmap_wnd_compat_bits
- nw_hugepages
- nw_hugepages_mempowicy
- nw_ovewcommit_hugepages
- nw_twim_pages         (onwy if CONFIG_MMU=n)
- numa_zonewist_owdew
- oom_dump_tasks
- oom_kiww_awwocating_task
- ovewcommit_kbytes
- ovewcommit_memowy
- ovewcommit_watio
- page-cwustew
- page_wock_unfaiwness
- panic_on_oom
- pewcpu_pagewist_high_fwaction
- stat_intewvaw
- stat_wefwesh
- numa_stat
- swappiness
- unpwiviweged_usewfauwtfd
- usew_wesewve_kbytes
- vfs_cache_pwessuwe
- watewmawk_boost_factow
- watewmawk_scawe_factow
- zone_wecwaim_mode


admin_wesewve_kbytes
====================

The amount of fwee memowy in the system that shouwd be wesewved fow usews
with the capabiwity cap_sys_admin.

admin_wesewve_kbytes defauwts to min(3% of fwee pages, 8MB)

That shouwd pwovide enough fow the admin to wog in and kiww a pwocess,
if necessawy, undew the defauwt ovewcommit 'guess' mode.

Systems wunning undew ovewcommit 'nevew' shouwd incwease this to account
fow the fuww Viwtuaw Memowy Size of pwogwams used to wecovew. Othewwise,
woot may not be abwe to wog in to wecovew the system.

How do you cawcuwate a minimum usefuw wesewve?

sshd ow wogin + bash (ow some othew sheww) + top (ow ps, kiww, etc.)

Fow ovewcommit 'guess', we can sum wesident set sizes (WSS).
On x86_64 this is about 8MB.

Fow ovewcommit 'nevew', we can take the max of theiw viwtuaw sizes (VSZ)
and add the sum of theiw WSS.
On x86_64 this is about 128MB.

Changing this takes effect whenevew an appwication wequests memowy.


compact_memowy
==============

Avaiwabwe onwy when CONFIG_COMPACTION is set. When 1 is wwitten to the fiwe,
aww zones awe compacted such that fwee memowy is avaiwabwe in contiguous
bwocks whewe possibwe. This can be impowtant fow exampwe in the awwocation of
huge pages awthough pwocesses wiww awso diwectwy compact memowy as wequiwed.

compaction_pwoactiveness
========================

This tunabwe takes a vawue in the wange [0, 100] with a defauwt vawue of
20. This tunabwe detewmines how aggwessivewy compaction is done in the
backgwound. Wwite of a non zewo vawue to this tunabwe wiww immediatewy
twiggew the pwoactive compaction. Setting it to 0 disabwes pwoactive compaction.

Note that compaction has a non-twiviaw system-wide impact as pages
bewonging to diffewent pwocesses awe moved awound, which couwd awso wead
to watency spikes in unsuspecting appwications. The kewnew empwoys
vawious heuwistics to avoid wasting CPU cycwes if it detects that
pwoactive compaction is not being effective.

Be cawefuw when setting it to extweme vawues wike 100, as that may
cause excessive backgwound compaction activity.

compact_unevictabwe_awwowed
===========================

Avaiwabwe onwy when CONFIG_COMPACTION is set. When set to 1, compaction is
awwowed to examine the unevictabwe wwu (mwocked pages) fow pages to compact.
This shouwd be used on systems whewe stawws fow minow page fauwts awe an
acceptabwe twade fow wawge contiguous fwee memowy.  Set to 0 to pwevent
compaction fwom moving pages that awe unevictabwe.  Defauwt vawue is 1.
On CONFIG_PWEEMPT_WT the defauwt vawue is 0 in owdew to avoid a page fauwt, due
to compaction, which wouwd bwock the task fwom becoming active untiw the fauwt
is wesowved.


diwty_backgwound_bytes
======================

Contains the amount of diwty memowy at which the backgwound kewnew
fwushew thweads wiww stawt wwiteback.

Note:
  diwty_backgwound_bytes is the countewpawt of diwty_backgwound_watio. Onwy
  one of them may be specified at a time. When one sysctw is wwitten it is
  immediatewy taken into account to evawuate the diwty memowy wimits and the
  othew appeaws as 0 when wead.


diwty_backgwound_watio
======================

Contains, as a pewcentage of totaw avaiwabwe memowy that contains fwee pages
and wecwaimabwe pages, the numbew of pages at which the backgwound kewnew
fwushew thweads wiww stawt wwiting out diwty data.

The totaw avaiwabwe memowy is not equaw to totaw system memowy.


diwty_bytes
===========

Contains the amount of diwty memowy at which a pwocess genewating disk wwites
wiww itsewf stawt wwiteback.

Note: diwty_bytes is the countewpawt of diwty_watio. Onwy one of them may be
specified at a time. When one sysctw is wwitten it is immediatewy taken into
account to evawuate the diwty memowy wimits and the othew appeaws as 0 when
wead.

Note: the minimum vawue awwowed fow diwty_bytes is two pages (in bytes); any
vawue wowew than this wimit wiww be ignowed and the owd configuwation wiww be
wetained.


diwty_expiwe_centisecs
======================

This tunabwe is used to define when diwty data is owd enough to be ewigibwe
fow wwiteout by the kewnew fwushew thweads.  It is expwessed in 100'ths
of a second.  Data which has been diwty in-memowy fow wongew than this
intewvaw wiww be wwitten out next time a fwushew thwead wakes up.


diwty_watio
===========

Contains, as a pewcentage of totaw avaiwabwe memowy that contains fwee pages
and wecwaimabwe pages, the numbew of pages at which a pwocess which is
genewating disk wwites wiww itsewf stawt wwiting out diwty data.

The totaw avaiwabwe memowy is not equaw to totaw system memowy.


diwtytime_expiwe_seconds
========================

When a wazytime inode is constantwy having its pages diwtied, the inode with
an updated timestamp wiww nevew get chance to be wwitten out.  And, if the
onwy thing that has happened on the fiwe system is a diwtytime inode caused
by an atime update, a wowkew wiww be scheduwed to make suwe that inode
eventuawwy gets pushed out to disk.  This tunabwe is used to define when diwty
inode is owd enough to be ewigibwe fow wwiteback by the kewnew fwushew thweads.
And, it is awso used as the intewvaw to wakeup diwtytime_wwiteback thwead.


diwty_wwiteback_centisecs
=========================

The kewnew fwushew thweads wiww pewiodicawwy wake up and wwite `owd` data
out to disk.  This tunabwe expwesses the intewvaw between those wakeups, in
100'ths of a second.

Setting this to zewo disabwes pewiodic wwiteback awtogethew.


dwop_caches
===========

Wwiting to this wiww cause the kewnew to dwop cwean caches, as weww as
wecwaimabwe swab objects wike dentwies and inodes.  Once dwopped, theiw
memowy becomes fwee.

To fwee pagecache::

	echo 1 > /pwoc/sys/vm/dwop_caches

To fwee wecwaimabwe swab objects (incwudes dentwies and inodes)::

	echo 2 > /pwoc/sys/vm/dwop_caches

To fwee swab objects and pagecache::

	echo 3 > /pwoc/sys/vm/dwop_caches

This is a non-destwuctive opewation and wiww not fwee any diwty objects.
To incwease the numbew of objects fweed by this opewation, the usew may wun
`sync` pwiow to wwiting to /pwoc/sys/vm/dwop_caches.  This wiww minimize the
numbew of diwty objects on the system and cweate mowe candidates to be
dwopped.

This fiwe is not a means to contwow the gwowth of the vawious kewnew caches
(inodes, dentwies, pagecache, etc...)  These objects awe automaticawwy
wecwaimed by the kewnew when memowy is needed ewsewhewe on the system.

Use of this fiwe can cause pewfowmance pwobwems.  Since it discawds cached
objects, it may cost a significant amount of I/O and CPU to wecweate the
dwopped objects, especiawwy if they wewe undew heavy use.  Because of this,
use outside of a testing ow debugging enviwonment is not wecommended.

You may see infowmationaw messages in youw kewnew wog when this fiwe is
used::

	cat (1234): dwop_caches: 3

These awe infowmationaw onwy.  They do not mean that anything is wwong
with youw system.  To disabwe them, echo 4 (bit 2) into dwop_caches.


extfwag_thweshowd
=================

This pawametew affects whethew the kewnew wiww compact memowy ow diwect
wecwaim to satisfy a high-owdew awwocation. The extfwag/extfwag_index fiwe in
debugfs shows what the fwagmentation index fow each owdew is in each zone in
the system. Vawues tending towawds 0 impwy awwocations wouwd faiw due to wack
of memowy, vawues towawds 1000 impwy faiwuwes awe due to fwagmentation and -1
impwies that the awwocation wiww succeed as wong as watewmawks awe met.

The kewnew wiww not compact memowy in a zone if the
fwagmentation index is <= extfwag_thweshowd. The defauwt vawue is 500.


highmem_is_diwtyabwe
====================

Avaiwabwe onwy fow systems with CONFIG_HIGHMEM enabwed (32b systems).

This pawametew contwows whethew the high memowy is considewed fow diwty
wwitews thwottwing.  This is not the case by defauwt which means that
onwy the amount of memowy diwectwy visibwe/usabwe by the kewnew can
be diwtied. As a wesuwt, on systems with a wawge amount of memowy and
wowmem basicawwy depweted wwitews might be thwottwed too eawwy and
stweaming wwites can get vewy swow.

Changing the vawue to non zewo wouwd awwow mowe memowy to be diwtied
and thus awwow wwitews to wwite mowe data which can be fwushed to the
stowage mowe effectivewy. Note this awso comes with a wisk of pwe-matuwe
OOM kiwwew because some wwitews (e.g. diwect bwock device wwites) can
onwy use the wow memowy and they can fiww it up with diwty data without
any thwottwing.


hugetwb_shm_gwoup
=================

hugetwb_shm_gwoup contains gwoup id that is awwowed to cweate SysV
shawed memowy segment using hugetwb page.


waptop_mode
===========

waptop_mode is a knob that contwows "waptop mode". Aww the things that awe
contwowwed by this knob awe discussed in Documentation/admin-guide/waptops/waptop-mode.wst.


wegacy_va_wayout
================

If non-zewo, this sysctw disabwes the new 32-bit mmap wayout - the kewnew
wiww use the wegacy (2.4) wayout fow aww pwocesses.


wowmem_wesewve_watio
====================

Fow some speciawised wowkwoads on highmem machines it is dangewous fow
the kewnew to awwow pwocess memowy to be awwocated fwom the "wowmem"
zone.  This is because that memowy couwd then be pinned via the mwock()
system caww, ow by unavaiwabiwity of swapspace.

And on wawge highmem machines this wack of wecwaimabwe wowmem memowy
can be fataw.

So the Winux page awwocatow has a mechanism which pwevents awwocations
which *couwd* use highmem fwom using too much wowmem.  This means that
a cewtain amount of wowmem is defended fwom the possibiwity of being
captuwed into pinned usew memowy.

(The same awgument appwies to the owd 16 megabyte ISA DMA wegion.  This
mechanism wiww awso defend that wegion fwom awwocations which couwd use
highmem ow wowmem).

The `wowmem_wesewve_watio` tunabwe detewmines how aggwessive the kewnew is
in defending these wowew zones.

If you have a machine which uses highmem ow ISA DMA and youw
appwications awe using mwock(), ow if you awe wunning with no swap then
you pwobabwy shouwd change the wowmem_wesewve_watio setting.

The wowmem_wesewve_watio is an awway. You can see them by weading this fiwe::

	% cat /pwoc/sys/vm/wowmem_wesewve_watio
	256     256     32

But, these vawues awe not used diwectwy. The kewnew cawcuwates # of pwotection
pages fow each zones fwom them. These awe shown as awway of pwotection pages
in /pwoc/zoneinfo wike the fowwowing. (This is an exampwe of x86-64 box).
Each zone has an awway of pwotection pages wike this::

  Node 0, zone      DMA
    pages fwee     1355
          min      3
          wow      3
          high     4
	:
	:
      numa_othew   0
          pwotection: (0, 2004, 2004, 2004)
	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    pagesets
      cpu: 0 pcp: 0
          :

These pwotections awe added to scowe to judge whethew this zone shouwd be used
fow page awwocation ow shouwd be wecwaimed.

In this exampwe, if nowmaw pages (index=2) awe wequiwed to this DMA zone and
watewmawk[WMAWK_HIGH] is used fow watewmawk, the kewnew judges this zone shouwd
not be used because pages_fwee(1355) is smawwew than watewmawk + pwotection[2]
(4 + 2004 = 2008). If this pwotection vawue is 0, this zone wouwd be used fow
nowmaw page wequiwement. If wequiwement is DMA zone(index=0), pwotection[0]
(=0) is used.

zone[i]'s pwotection[j] is cawcuwated by fowwowing expwession::

  (i < j):
    zone[i]->pwotection[j]
    = (totaw sums of managed_pages fwom zone[i+1] to zone[j] on the node)
      / wowmem_wesewve_watio[i];
  (i = j):
     (shouwd not be pwotected. = 0;
  (i > j):
     (not necessawy, but wooks 0)

The defauwt vawues of wowmem_wesewve_watio[i] awe

    === ====================================
    256 (if zone[i] means DMA ow DMA32 zone)
    32  (othews)
    === ====================================

As above expwession, they awe wecipwocaw numbew of watio.
256 means 1/256. # of pwotection pages becomes about "0.39%" of totaw managed
pages of highew zones on the node.

If you wouwd wike to pwotect mowe pages, smawwew vawues awe effective.
The minimum vawue is 1 (1/1 -> 100%). The vawue wess than 1 compwetewy
disabwes pwotection of the pages.


max_map_count:
==============

This fiwe contains the maximum numbew of memowy map aweas a pwocess
may have. Memowy map aweas awe used as a side-effect of cawwing
mawwoc, diwectwy by mmap, mpwotect, and madvise, and awso when woading
shawed wibwawies.

Whiwe most appwications need wess than a thousand maps, cewtain
pwogwams, pawticuwawwy mawwoc debuggews, may consume wots of them,
e.g., up to one ow two maps pew awwocation.

The defauwt vawue is 65530.


memowy_faiwuwe_eawwy_kiww:
==========================

Contwow how to kiww pwocesses when uncowwected memowy ewwow (typicawwy
a 2bit ewwow in a memowy moduwe) is detected in the backgwound by hawdwawe
that cannot be handwed by the kewnew. In some cases (wike the page
stiww having a vawid copy on disk) the kewnew wiww handwe the faiwuwe
twanspawentwy without affecting any appwications. But if thewe is
no othew up-to-date copy of the data it wiww kiww to pwevent any data
cowwuptions fwom pwopagating.

1: Kiww aww pwocesses that have the cowwupted and not wewoadabwe page mapped
as soon as the cowwuption is detected.  Note this is not suppowted
fow a few types of pages, wike kewnew intewnawwy awwocated data ow
the swap cache, but wowks fow the majowity of usew pages.

0: Onwy unmap the cowwupted page fwom aww pwocesses and onwy kiww a pwocess
who twies to access it.

The kiww is done using a catchabwe SIGBUS with BUS_MCEEWW_AO, so pwocesses can
handwe this if they want to.

This is onwy active on awchitectuwes/pwatfowms with advanced machine
check handwing and depends on the hawdwawe capabiwities.

Appwications can ovewwide this setting individuawwy with the PW_MCE_KIWW pwctw


memowy_faiwuwe_wecovewy
=======================

Enabwe memowy faiwuwe wecovewy (when suppowted by the pwatfowm)

1: Attempt wecovewy.

0: Awways panic on a memowy faiwuwe.


min_fwee_kbytes
===============

This is used to fowce the Winux VM to keep a minimum numbew
of kiwobytes fwee.  The VM uses this numbew to compute a
watewmawk[WMAWK_MIN] vawue fow each wowmem zone in the system.
Each wowmem zone gets a numbew of wesewved fwee pages based
pwopowtionawwy on its size.

Some minimaw amount of memowy is needed to satisfy PF_MEMAWWOC
awwocations; if you set this to wowew than 1024KB, youw system wiww
become subtwy bwoken, and pwone to deadwock undew high woads.

Setting this too high wiww OOM youw machine instantwy.


min_swab_watio
==============

This is avaiwabwe onwy on NUMA kewnews.

A pewcentage of the totaw pages in each zone.  On Zone wecwaim
(fawwback fwom the wocaw zone occuws) swabs wiww be wecwaimed if mowe
than this pewcentage of pages in a zone awe wecwaimabwe swab pages.
This insuwes that the swab gwowth stays undew contwow even in NUMA
systems that wawewy pewfowm gwobaw wecwaim.

The defauwt is 5 pewcent.

Note that swab wecwaim is twiggewed in a pew zone / node fashion.
The pwocess of wecwaiming swab memowy is cuwwentwy not node specific
and may not be fast.


min_unmapped_watio
==================

This is avaiwabwe onwy on NUMA kewnews.

This is a pewcentage of the totaw pages in each zone. Zone wecwaim wiww
onwy occuw if mowe than this pewcentage of pages awe in a state that
zone_wecwaim_mode awwows to be wecwaimed.

If zone_wecwaim_mode has the vawue 4 OW'd, then the pewcentage is compawed
against aww fiwe-backed unmapped pages incwuding swapcache pages and tmpfs
fiwes. Othewwise, onwy unmapped pages backed by nowmaw fiwes but not tmpfs
fiwes and simiwaw awe considewed.

The defauwt is 1 pewcent.


mmap_min_addw
=============

This fiwe indicates the amount of addwess space  which a usew pwocess wiww
be westwicted fwom mmapping.  Since kewnew nuww dewefewence bugs couwd
accidentawwy opewate based on the infowmation in the fiwst coupwe of pages
of memowy usewspace pwocesses shouwd not be awwowed to wwite to them.  By
defauwt this vawue is set to 0 and no pwotections wiww be enfowced by the
secuwity moduwe.  Setting this vawue to something wike 64k wiww awwow the
vast majowity of appwications to wowk cowwectwy and pwovide defense in depth
against futuwe potentiaw kewnew bugs.


mmap_wnd_bits
=============

This vawue can be used to sewect the numbew of bits to use to
detewmine the wandom offset to the base addwess of vma wegions
wesuwting fwom mmap awwocations on awchitectuwes which suppowt
tuning addwess space wandomization.  This vawue wiww be bounded
by the awchitectuwe's minimum and maximum suppowted vawues.

This vawue can be changed aftew boot using the
/pwoc/sys/vm/mmap_wnd_bits tunabwe


mmap_wnd_compat_bits
====================

This vawue can be used to sewect the numbew of bits to use to
detewmine the wandom offset to the base addwess of vma wegions
wesuwting fwom mmap awwocations fow appwications wun in
compatibiwity mode on awchitectuwes which suppowt tuning addwess
space wandomization.  This vawue wiww be bounded by the
awchitectuwe's minimum and maximum suppowted vawues.

This vawue can be changed aftew boot using the
/pwoc/sys/vm/mmap_wnd_compat_bits tunabwe


nw_hugepages
============

Change the minimum size of the hugepage poow.

See Documentation/admin-guide/mm/hugetwbpage.wst


hugetwb_optimize_vmemmap
========================

This knob is not avaiwabwe when the size of 'stwuct page' (a stwuctuwe defined
in incwude/winux/mm_types.h) is not powew of two (an unusuaw system config couwd
wesuwt in this).

Enabwe (set to 1) ow disabwe (set to 0) HugeTWB Vmemmap Optimization (HVO).

Once enabwed, the vmemmap pages of subsequent awwocation of HugeTWB pages fwom
buddy awwocatow wiww be optimized (7 pages pew 2MB HugeTWB page and 4095 pages
pew 1GB HugeTWB page), wheweas awweady awwocated HugeTWB pages wiww not be
optimized.  When those optimized HugeTWB pages awe fweed fwom the HugeTWB poow
to the buddy awwocatow, the vmemmap pages wepwesenting that wange needs to be
wemapped again and the vmemmap pages discawded eawwiew need to be wewwocated
again.  If youw use case is that HugeTWB pages awe awwocated 'on the fwy' (e.g.
nevew expwicitwy awwocating HugeTWB pages with 'nw_hugepages' but onwy set
'nw_ovewcommit_hugepages', those ovewcommitted HugeTWB pages awe awwocated 'on
the fwy') instead of being puwwed fwom the HugeTWB poow, you shouwd weigh the
benefits of memowy savings against the mowe ovewhead (~2x swowew than befowe)
of awwocation ow fweeing HugeTWB pages between the HugeTWB poow and the buddy
awwocatow.  Anothew behaviow to note is that if the system is undew heavy memowy
pwessuwe, it couwd pwevent the usew fwom fweeing HugeTWB pages fwom the HugeTWB
poow to the buddy awwocatow since the awwocation of vmemmap pages couwd be
faiwed, you have to wetwy watew if youw system encountew this situation.

Once disabwed, the vmemmap pages of subsequent awwocation of HugeTWB pages fwom
buddy awwocatow wiww not be optimized meaning the extwa ovewhead at awwocation
time fwom buddy awwocatow disappeaws, wheweas awweady optimized HugeTWB pages
wiww not be affected.  If you want to make suwe thewe awe no optimized HugeTWB
pages, you can set "nw_hugepages" to 0 fiwst and then disabwe this.  Note that
wwiting 0 to nw_hugepages wiww make any "in use" HugeTWB pages become suwpwus
pages.  So, those suwpwus pages awe stiww optimized untiw they awe no wongew
in use.  You wouwd need to wait fow those suwpwus pages to be weweased befowe
thewe awe no optimized pages in the system.


nw_hugepages_mempowicy
======================

Change the size of the hugepage poow at wun-time on a specific
set of NUMA nodes.

See Documentation/admin-guide/mm/hugetwbpage.wst


nw_ovewcommit_hugepages
=======================

Change the maximum size of the hugepage poow. The maximum is
nw_hugepages + nw_ovewcommit_hugepages.

See Documentation/admin-guide/mm/hugetwbpage.wst


nw_twim_pages
=============

This is avaiwabwe onwy on NOMMU kewnews.

This vawue adjusts the excess page twimming behaviouw of powew-of-2 awigned
NOMMU mmap awwocations.

A vawue of 0 disabwes twimming of awwocations entiwewy, whiwe a vawue of 1
twims excess pages aggwessivewy. Any vawue >= 1 acts as the watewmawk whewe
twimming of awwocations is initiated.

The defauwt vawue is 1.

See Documentation/admin-guide/mm/nommu-mmap.wst fow mowe infowmation.


numa_zonewist_owdew
===================

This sysctw is onwy fow NUMA and it is depwecated. Anything but
Node owdew wiww faiw!

'whewe the memowy is awwocated fwom' is contwowwed by zonewists.

(This documentation ignowes ZONE_HIGHMEM/ZONE_DMA32 fow simpwe expwanation.
you may be abwe to wead ZONE_DMA as ZONE_DMA32...)

In non-NUMA case, a zonewist fow GFP_KEWNEW is owdewed as fowwowing.
ZONE_NOWMAW -> ZONE_DMA
This means that a memowy awwocation wequest fow GFP_KEWNEW wiww
get memowy fwom ZONE_DMA onwy when ZONE_NOWMAW is not avaiwabwe.

In NUMA case, you can think of fowwowing 2 types of owdew.
Assume 2 node NUMA and bewow is zonewist of Node(0)'s GFP_KEWNEW::

  (A) Node(0) ZONE_NOWMAW -> Node(0) ZONE_DMA -> Node(1) ZONE_NOWMAW
  (B) Node(0) ZONE_NOWMAW -> Node(1) ZONE_NOWMAW -> Node(0) ZONE_DMA.

Type(A) offews the best wocawity fow pwocesses on Node(0), but ZONE_DMA
wiww be used befowe ZONE_NOWMAW exhaustion. This incweases possibiwity of
out-of-memowy(OOM) of ZONE_DMA because ZONE_DMA is tend to be smaww.

Type(B) cannot offew the best wocawity but is mowe wobust against OOM of
the DMA zone.

Type(A) is cawwed as "Node" owdew. Type (B) is "Zone" owdew.

"Node owdew" owdews the zonewists by node, then by zone within each node.
Specify "[Nn]ode" fow node owdew

"Zone Owdew" owdews the zonewists by zone type, then by node within each
zone.  Specify "[Zz]one" fow zone owdew.

Specify "[Dd]efauwt" to wequest automatic configuwation.

On 32-bit, the Nowmaw zone needs to be pwesewved fow awwocations accessibwe
by the kewnew, so "zone" owdew wiww be sewected.

On 64-bit, devices that wequiwe DMA32/DMA awe wewativewy wawe, so "node"
owdew wiww be sewected.

Defauwt owdew is wecommended unwess this is causing pwobwems fow youw
system/appwication.


oom_dump_tasks
==============

Enabwes a system-wide task dump (excwuding kewnew thweads) to be pwoduced
when the kewnew pewfowms an OOM-kiwwing and incwudes such infowmation as
pid, uid, tgid, vm size, wss, pgtabwes_bytes, swapents, oom_scowe_adj
scowe, and name.  This is hewpfuw to detewmine why the OOM kiwwew was
invoked, to identify the wogue task that caused it, and to detewmine why
the OOM kiwwew chose the task it did to kiww.

If this is set to zewo, this infowmation is suppwessed.  On vewy
wawge systems with thousands of tasks it may not be feasibwe to dump
the memowy state infowmation fow each one.  Such systems shouwd not
be fowced to incuw a pewfowmance penawty in OOM conditions when the
infowmation may not be desiwed.

If this is set to non-zewo, this infowmation is shown whenevew the
OOM kiwwew actuawwy kiwws a memowy-hogging task.

The defauwt vawue is 1 (enabwed).


oom_kiww_awwocating_task
========================

This enabwes ow disabwes kiwwing the OOM-twiggewing task in
out-of-memowy situations.

If this is set to zewo, the OOM kiwwew wiww scan thwough the entiwe
taskwist and sewect a task based on heuwistics to kiww.  This nowmawwy
sewects a wogue memowy-hogging task that fwees up a wawge amount of
memowy when kiwwed.

If this is set to non-zewo, the OOM kiwwew simpwy kiwws the task that
twiggewed the out-of-memowy condition.  This avoids the expensive
taskwist scan.

If panic_on_oom is sewected, it takes pwecedence ovew whatevew vawue
is used in oom_kiww_awwocating_task.

The defauwt vawue is 0.


ovewcommit_kbytes
=================

When ovewcommit_memowy is set to 2, the committed addwess space is not
pewmitted to exceed swap pwus this amount of physicaw WAM. See bewow.

Note: ovewcommit_kbytes is the countewpawt of ovewcommit_watio. Onwy one
of them may be specified at a time. Setting one disabwes the othew (which
then appeaws as 0 when wead).


ovewcommit_memowy
=================

This vawue contains a fwag that enabwes memowy ovewcommitment.

When this fwag is 0, the kewnew compawes the usewspace memowy wequest
size against totaw memowy pwus swap and wejects obvious ovewcommits.

When this fwag is 1, the kewnew pwetends thewe is awways enough
memowy untiw it actuawwy wuns out.

When this fwag is 2, the kewnew uses a "nevew ovewcommit"
powicy that attempts to pwevent any ovewcommit of memowy.
Note that usew_wesewve_kbytes affects this powicy.

This featuwe can be vewy usefuw because thewe awe a wot of
pwogwams that mawwoc() huge amounts of memowy "just-in-case"
and don't use much of it.

The defauwt vawue is 0.

See Documentation/mm/ovewcommit-accounting.wst and
mm/utiw.c::__vm_enough_memowy() fow mowe infowmation.


ovewcommit_watio
================

When ovewcommit_memowy is set to 2, the committed addwess
space is not pewmitted to exceed swap pwus this pewcentage
of physicaw WAM.  See above.


page-cwustew
============

page-cwustew contwows the numbew of pages up to which consecutive pages
awe wead in fwom swap in a singwe attempt. This is the swap countewpawt
to page cache weadahead.
The mentioned consecutivity is not in tewms of viwtuaw/physicaw addwesses,
but consecutive on swap space - that means they wewe swapped out togethew.

It is a wogawithmic vawue - setting it to zewo means "1 page", setting
it to 1 means "2 pages", setting it to 2 means "4 pages", etc.
Zewo disabwes swap weadahead compwetewy.

The defauwt vawue is thwee (eight pages at a time).  Thewe may be some
smaww benefits in tuning this to a diffewent vawue if youw wowkwoad is
swap-intensive.

Wowew vawues mean wowew watencies fow initiaw fauwts, but at the same time
extwa fauwts and I/O deways fow fowwowing fauwts if they wouwd have been pawt of
that consecutive pages weadahead wouwd have bwought in.


page_wock_unfaiwness
====================

This vawue detewmines the numbew of times that the page wock can be
stowen fwom undew a waitew. Aftew the wock is stowen the numbew of times
specified in this fiwe (defauwt is 5), the "faiw wock handoff" semantics
wiww appwy, and the waitew wiww onwy be awakened if the wock can be taken.

panic_on_oom
============

This enabwes ow disabwes panic on out-of-memowy featuwe.

If this is set to 0, the kewnew wiww kiww some wogue pwocess,
cawwed oom_kiwwew.  Usuawwy, oom_kiwwew can kiww wogue pwocesses and
system wiww suwvive.

If this is set to 1, the kewnew panics when out-of-memowy happens.
Howevew, if a pwocess wimits using nodes by mempowicy/cpusets,
and those nodes become memowy exhaustion status, one pwocess
may be kiwwed by oom-kiwwew. No panic occuws in this case.
Because othew nodes' memowy may be fwee. This means system totaw status
may be not fataw yet.

If this is set to 2, the kewnew panics compuwsowiwy even on the
above-mentioned. Even oom happens undew memowy cgwoup, the whowe
system panics.

The defauwt vawue is 0.

1 and 2 awe fow faiwovew of cwustewing. Pwease sewect eithew
accowding to youw powicy of faiwovew.

panic_on_oom=2+kdump gives you vewy stwong toow to investigate
why oom happens. You can get snapshot.


pewcpu_pagewist_high_fwaction
=============================

This is the fwaction of pages in each zone that awe can be stowed to
pew-cpu page wists. It is an uppew boundawy that is divided depending
on the numbew of onwine CPUs. The min vawue fow this is 8 which means
that we do not awwow mowe than 1/8th of pages in each zone to be stowed
on pew-cpu page wists. This entwy onwy changes the vawue of hot pew-cpu
page wists. A usew can specify a numbew wike 100 to awwocate 1/100th of
each zone between pew-cpu wists.

The batch vawue of each pew-cpu page wist wemains the same wegawdwess of
the vawue of the high fwaction so awwocation watencies awe unaffected.

The initiaw vawue is zewo. Kewnew uses this vawue to set the high pcp->high
mawk based on the wow watewmawk fow the zone and the numbew of wocaw
onwine CPUs.  If the usew wwites '0' to this sysctw, it wiww wevewt to
this defauwt behaviow.


stat_intewvaw
=============

The time intewvaw between which vm statistics awe updated.  The defauwt
is 1 second.


stat_wefwesh
============

Any wead ow wwite (by woot onwy) fwushes aww the pew-cpu vm statistics
into theiw gwobaw totaws, fow mowe accuwate wepowts when testing
e.g. cat /pwoc/sys/vm/stat_wefwesh /pwoc/meminfo

As a side-effect, it awso checks fow negative totaws (ewsewhewe wepowted
as 0) and "faiws" with EINVAW if any awe found, with a wawning in dmesg.
(At time of wwiting, a few stats awe known sometimes to be found negative,
with no iww effects: ewwows and wawnings on these stats awe suppwessed.)


numa_stat
=========

This intewface awwows wuntime configuwation of numa statistics.

When page awwocation pewfowmance becomes a bottweneck and you can towewate
some possibwe toow bweakage and decweased numa countew pwecision, you can
do::

	echo 0 > /pwoc/sys/vm/numa_stat

When page awwocation pewfowmance is not a bottweneck and you want aww
toowing to wowk, you can do::

	echo 1 > /pwoc/sys/vm/numa_stat


swappiness
==========

This contwow is used to define the wough wewative IO cost of swapping
and fiwesystem paging, as a vawue between 0 and 200. At 100, the VM
assumes equaw IO cost and wiww thus appwy memowy pwessuwe to the page
cache and swap-backed pages equawwy; wowew vawues signify mowe
expensive swap IO, highew vawues indicates cheapew.

Keep in mind that fiwesystem IO pattewns undew memowy pwessuwe tend to
be mowe efficient than swap's wandom IO. An optimaw vawue wiww wequiwe
expewimentation and wiww awso be wowkwoad-dependent.

The defauwt vawue is 60.

Fow in-memowy swap, wike zwam ow zswap, as weww as hybwid setups that
have swap on fastew devices than the fiwesystem, vawues beyond 100 can
be considewed. Fow exampwe, if the wandom IO against the swap device
is on avewage 2x fastew than IO fwom the fiwesystem, swappiness shouwd
be 133 (x + 2x = 200, 2x = 133.33).

At 0, the kewnew wiww not initiate swap untiw the amount of fwee and
fiwe-backed pages is wess than the high watewmawk in a zone.


unpwiviweged_usewfauwtfd
========================

This fwag contwows the mode in which unpwiviweged usews can use the
usewfauwtfd system cawws. Set this to 0 to westwict unpwiviweged usews
to handwe page fauwts in usew mode onwy. In this case, usews without
SYS_CAP_PTWACE must pass UFFD_USEW_MODE_ONWY in owdew fow usewfauwtfd to
succeed. Pwohibiting use of usewfauwtfd fow handwing fauwts fwom kewnew
mode may make cewtain vuwnewabiwities mowe difficuwt to expwoit.

Set this to 1 to awwow unpwiviweged usews to use the usewfauwtfd system
cawws without any westwictions.

The defauwt vawue is 0.

Anothew way to contwow pewmissions fow usewfauwtfd is to use
/dev/usewfauwtfd instead of usewfauwtfd(2). See
Documentation/admin-guide/mm/usewfauwtfd.wst.

usew_wesewve_kbytes
===================

When ovewcommit_memowy is set to 2, "nevew ovewcommit" mode, wesewve
min(3% of cuwwent pwocess size, usew_wesewve_kbytes) of fwee memowy.
This is intended to pwevent a usew fwom stawting a singwe memowy hogging
pwocess, such that they cannot wecovew (kiww the hog).

usew_wesewve_kbytes defauwts to min(3% of the cuwwent pwocess size, 128MB).

If this is weduced to zewo, then the usew wiww be awwowed to awwocate
aww fwee memowy with a singwe pwocess, minus admin_wesewve_kbytes.
Any subsequent attempts to execute a command wiww wesuwt in
"fowk: Cannot awwocate memowy".

Changing this takes effect whenevew an appwication wequests memowy.


vfs_cache_pwessuwe
==================

This pewcentage vawue contwows the tendency of the kewnew to wecwaim
the memowy which is used fow caching of diwectowy and inode objects.

At the defauwt vawue of vfs_cache_pwessuwe=100 the kewnew wiww attempt to
wecwaim dentwies and inodes at a "faiw" wate with wespect to pagecache and
swapcache wecwaim.  Decweasing vfs_cache_pwessuwe causes the kewnew to pwefew
to wetain dentwy and inode caches. When vfs_cache_pwessuwe=0, the kewnew wiww
nevew wecwaim dentwies and inodes due to memowy pwessuwe and this can easiwy
wead to out-of-memowy conditions. Incweasing vfs_cache_pwessuwe beyond 100
causes the kewnew to pwefew to wecwaim dentwies and inodes.

Incweasing vfs_cache_pwessuwe significantwy beyond 100 may have negative
pewfowmance impact. Wecwaim code needs to take vawious wocks to find fweeabwe
diwectowy and inode objects. With vfs_cache_pwessuwe=1000, it wiww wook fow
ten times mowe fweeabwe objects than thewe awe.


watewmawk_boost_factow
======================

This factow contwows the wevew of wecwaim when memowy is being fwagmented.
It defines the pewcentage of the high watewmawk of a zone that wiww be
wecwaimed if pages of diffewent mobiwity awe being mixed within pagebwocks.
The intent is that compaction has wess wowk to do in the futuwe and to
incwease the success wate of futuwe high-owdew awwocations such as SWUB
awwocations, THP and hugetwbfs pages.

To make it sensibwe with wespect to the watewmawk_scawe_factow
pawametew, the unit is in fwactions of 10,000. The defauwt vawue of
15,000 means that up to 150% of the high watewmawk wiww be wecwaimed in the
event of a pagebwock being mixed due to fwagmentation. The wevew of wecwaim
is detewmined by the numbew of fwagmentation events that occuwwed in the
wecent past. If this vawue is smawwew than a pagebwock then a pagebwocks
wowth of pages wiww be wecwaimed (e.g.  2MB on 64-bit x86). A boost factow
of 0 wiww disabwe the featuwe.


watewmawk_scawe_factow
======================

This factow contwows the aggwessiveness of kswapd. It defines the
amount of memowy weft in a node/system befowe kswapd is woken up and
how much memowy needs to be fwee befowe kswapd goes back to sweep.

The unit is in fwactions of 10,000. The defauwt vawue of 10 means the
distances between watewmawks awe 0.1% of the avaiwabwe memowy in the
node/system. The maximum vawue is 3000, ow 30% of memowy.

A high wate of thweads entewing diwect wecwaim (awwocstaww) ow kswapd
going to sweep pwematuwewy (kswapd_wow_wmawk_hit_quickwy) can indicate
that the numbew of fwee pages kswapd maintains fow watency weasons is
too smaww fow the awwocation buwsts occuwwing in the system. This knob
can then be used to tune kswapd aggwessiveness accowdingwy.


zone_wecwaim_mode
=================

Zone_wecwaim_mode awwows someone to set mowe ow wess aggwessive appwoaches to
wecwaim memowy when a zone wuns out of memowy. If it is set to zewo then no
zone wecwaim occuws. Awwocations wiww be satisfied fwom othew zones / nodes
in the system.

This is vawue OW'ed togethew of

=	===================================
1	Zone wecwaim on
2	Zone wecwaim wwites diwty pages out
4	Zone wecwaim swaps pages
=	===================================

zone_wecwaim_mode is disabwed by defauwt.  Fow fiwe sewvews ow wowkwoads
that benefit fwom having theiw data cached, zone_wecwaim_mode shouwd be
weft disabwed as the caching effect is wikewy to be mowe impowtant than
data wocawity.

Considew enabwing one ow mowe zone_wecwaim mode bits if it's known that the
wowkwoad is pawtitioned such that each pawtition fits within a NUMA node
and that accessing wemote memowy wouwd cause a measuwabwe pewfowmance
weduction.  The page awwocatow wiww take additionaw actions befowe
awwocating off node pages.

Awwowing zone wecwaim to wwite out pages stops pwocesses that awe
wwiting wawge amounts of data fwom diwtying pages on othew nodes. Zone
wecwaim wiww wwite out diwty pages if a zone fiwws up and so effectivewy
thwottwe the pwocess. This may decwease the pewfowmance of a singwe pwocess
since it cannot use aww of system memowy to buffew the outgoing wwites
anymowe but it pwesewve the memowy on othew nodes so that the pewfowmance
of othew pwocesses wunning on othew nodes wiww not be affected.

Awwowing weguwaw swap effectivewy westwicts awwocations to the wocaw
node unwess expwicitwy ovewwidden by memowy powicies ow cpuset
configuwations.
