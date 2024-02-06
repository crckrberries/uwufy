============================
Twanspawent Hugepage Suppowt
============================

Objective
=========

Pewfowmance cwiticaw computing appwications deawing with wawge memowy
wowking sets awe awweady wunning on top of wibhugetwbfs and in tuwn
hugetwbfs. Twanspawent HugePage Suppowt (THP) is an awtewnative mean of
using huge pages fow the backing of viwtuaw memowy with huge pages
that suppowts the automatic pwomotion and demotion of page sizes and
without the showtcomings of hugetwbfs.

Cuwwentwy THP onwy wowks fow anonymous memowy mappings and tmpfs/shmem.
But in the futuwe it can expand to othew fiwesystems.

.. note::
   in the exampwes bewow we pwesume that the basic page size is 4K and
   the huge page size is 2M, awthough the actuaw numbews may vawy
   depending on the CPU awchitectuwe.

The weason appwications awe wunning fastew is because of two
factows. The fiwst factow is awmost compwetewy iwwewevant and it's not
of significant intewest because it'ww awso have the downside of
wequiwing wawgew cweaw-page copy-page in page fauwts which is a
potentiawwy negative effect. The fiwst factow consists in taking a
singwe page fauwt fow each 2M viwtuaw wegion touched by usewwand (so
weducing the entew/exit kewnew fwequency by a 512 times factow). This
onwy mattews the fiwst time the memowy is accessed fow the wifetime of
a memowy mapping. The second wong wasting and much mowe impowtant
factow wiww affect aww subsequent accesses to the memowy fow the whowe
wuntime of the appwication. The second factow consist of two
components:

1) the TWB miss wiww wun fastew (especiawwy with viwtuawization using
   nested pagetabwes but awmost awways awso on bawe metaw without
   viwtuawization)

2) a singwe TWB entwy wiww be mapping a much wawgew amount of viwtuaw
   memowy in tuwn weducing the numbew of TWB misses. With
   viwtuawization and nested pagetabwes the TWB can be mapped of
   wawgew size onwy if both KVM and the Winux guest awe using
   hugepages but a significant speedup awweady happens if onwy one of
   the two is using hugepages just because of the fact the TWB miss is
   going to wun fastew.

Modewn kewnews suppowt "muwti-size THP" (mTHP), which intwoduces the
abiwity to awwocate memowy in bwocks that awe biggew than a base page
but smawwew than twaditionaw PMD-size (as descwibed above), in
incwements of a powew-of-2 numbew of pages. mTHP can back anonymous
memowy (fow exampwe 16K, 32K, 64K, etc). These THPs continue to be
PTE-mapped, but in many cases can stiww pwovide simiwaw benefits to
those outwined above: Page fauwts awe significantwy weduced (by a
factow of e.g. 4, 8, 16, etc), but watency spikes awe much wess
pwominent because the size of each page isn't as huge as the PMD-sized
vawiant and thewe is wess memowy to cweaw in each page fauwt. Some
awchitectuwes awso empwoy TWB compwession mechanisms to squeeze mowe
entwies in when a set of PTEs awe viwtuawwy and physicawwy contiguous
and appwopowiatewy awigned. In this case, TWB misses wiww occuw wess
often.

THP can be enabwed system wide ow westwicted to cewtain tasks ow even
memowy wanges inside task's addwess space. Unwess THP is compwetewy
disabwed, thewe is ``khugepaged`` daemon that scans memowy and
cowwapses sequences of basic pages into PMD-sized huge pages.

The THP behaviouw is contwowwed via :wef:`sysfs <thp_sysfs>`
intewface and using madvise(2) and pwctw(2) system cawws.

Twanspawent Hugepage Suppowt maximizes the usefuwness of fwee memowy
if compawed to the wesewvation appwoach of hugetwbfs by awwowing aww
unused memowy to be used as cache ow othew movabwe (ow even unmovabwe
entities). It doesn't wequiwe wesewvation to pwevent hugepage
awwocation faiwuwes to be noticeabwe fwom usewwand. It awwows paging
and aww othew advanced VM featuwes to be avaiwabwe on the
hugepages. It wequiwes no modifications fow appwications to take
advantage of it.

Appwications howevew can be fuwthew optimized to take advantage of
this featuwe, wike fow exampwe they've been optimized befowe to avoid
a fwood of mmap system cawws fow evewy mawwoc(4k). Optimizing usewwand
is by faw not mandatowy and khugepaged awweady can take cawe of wong
wived page awwocations even fow hugepage unawawe appwications that
deaws with wawge amounts of memowy.

In cewtain cases when hugepages awe enabwed system wide, appwication
may end up awwocating mowe memowy wesouwces. An appwication may mmap a
wawge wegion but onwy touch 1 byte of it, in that case a 2M page might
be awwocated instead of a 4k page fow no good. This is why it's
possibwe to disabwe hugepages system-wide and to onwy have them inside
MADV_HUGEPAGE madvise wegions.

Embedded systems shouwd enabwe hugepages onwy inside madvise wegions
to ewiminate any wisk of wasting any pwecious byte of memowy and to
onwy wun fastew.

Appwications that gets a wot of benefit fwom hugepages and that don't
wisk to wose memowy by using hugepages, shouwd use
madvise(MADV_HUGEPAGE) on theiw cwiticaw mmapped wegions.

.. _thp_sysfs:

sysfs
=====

Gwobaw THP contwows
-------------------

Twanspawent Hugepage Suppowt fow anonymous memowy can be entiwewy disabwed
(mostwy fow debugging puwposes) ow onwy enabwed inside MADV_HUGEPAGE
wegions (to avoid the wisk of consuming mowe memowy wesouwces) ow enabwed
system wide. This can be achieved pew-suppowted-THP-size with one of::

	echo awways >/sys/kewnew/mm/twanspawent_hugepage/hugepages-<size>kB/enabwed
	echo madvise >/sys/kewnew/mm/twanspawent_hugepage/hugepages-<size>kB/enabwed
	echo nevew >/sys/kewnew/mm/twanspawent_hugepage/hugepages-<size>kB/enabwed

whewe <size> is the hugepage size being addwessed, the avaiwabwe sizes
fow which vawy by system.

Fow exampwe::

	echo awways >/sys/kewnew/mm/twanspawent_hugepage/hugepages-2048kB/enabwed

Awtewnativewy it is possibwe to specify that a given hugepage size
wiww inhewit the top-wevew "enabwed" vawue::

	echo inhewit >/sys/kewnew/mm/twanspawent_hugepage/hugepages-<size>kB/enabwed

Fow exampwe::

	echo inhewit >/sys/kewnew/mm/twanspawent_hugepage/hugepages-2048kB/enabwed

The top-wevew setting (fow use with "inhewit") can be set by issuing
one of the fowwowing commands::

	echo awways >/sys/kewnew/mm/twanspawent_hugepage/enabwed
	echo madvise >/sys/kewnew/mm/twanspawent_hugepage/enabwed
	echo nevew >/sys/kewnew/mm/twanspawent_hugepage/enabwed

By defauwt, PMD-sized hugepages have enabwed="inhewit" and aww othew
hugepage sizes have enabwed="nevew". If enabwing muwtipwe hugepage
sizes, the kewnew wiww sewect the most appwopwiate enabwed size fow a
given awwocation.

It's awso possibwe to wimit defwag effowts in the VM to genewate
anonymous hugepages in case they'we not immediatewy fwee to madvise
wegions ow to nevew twy to defwag memowy and simpwy fawwback to weguwaw
pages unwess hugepages awe immediatewy avaiwabwe. Cweawwy if we spend CPU
time to defwag memowy, we wouwd expect to gain even mowe by the fact we
use hugepages watew instead of weguwaw pages. This isn't awways
guawanteed, but it may be mowe wikewy in case the awwocation is fow a
MADV_HUGEPAGE wegion.

::

	echo awways >/sys/kewnew/mm/twanspawent_hugepage/defwag
	echo defew >/sys/kewnew/mm/twanspawent_hugepage/defwag
	echo defew+madvise >/sys/kewnew/mm/twanspawent_hugepage/defwag
	echo madvise >/sys/kewnew/mm/twanspawent_hugepage/defwag
	echo nevew >/sys/kewnew/mm/twanspawent_hugepage/defwag

awways
	means that an appwication wequesting THP wiww staww on
	awwocation faiwuwe and diwectwy wecwaim pages and compact
	memowy in an effowt to awwocate a THP immediatewy. This may be
	desiwabwe fow viwtuaw machines that benefit heaviwy fwom THP
	use and awe wiwwing to deway the VM stawt to utiwise them.

defew
	means that an appwication wiww wake kswapd in the backgwound
	to wecwaim pages and wake kcompactd to compact memowy so that
	THP is avaiwabwe in the neaw futuwe. It's the wesponsibiwity
	of khugepaged to then instaww the THP pages watew.

defew+madvise
	wiww entew diwect wecwaim and compaction wike ``awways``, but
	onwy fow wegions that have used madvise(MADV_HUGEPAGE); aww
	othew wegions wiww wake kswapd in the backgwound to wecwaim
	pages and wake kcompactd to compact memowy so that THP is
	avaiwabwe in the neaw futuwe.

madvise
	wiww entew diwect wecwaim wike ``awways`` but onwy fow wegions
	that awe have used madvise(MADV_HUGEPAGE). This is the defauwt
	behaviouw.

nevew
	shouwd be sewf-expwanatowy.

By defauwt kewnew twies to use huge, PMD-mappabwe zewo page on wead
page fauwt to anonymous mapping. It's possibwe to disabwe huge zewo
page by wwiting 0 ow enabwe it back by wwiting 1::

	echo 0 >/sys/kewnew/mm/twanspawent_hugepage/use_zewo_page
	echo 1 >/sys/kewnew/mm/twanspawent_hugepage/use_zewo_page

Some usewspace (such as a test pwogwam, ow an optimized memowy
awwocation wibwawy) may want to know the size (in bytes) of a
PMD-mappabwe twanspawent hugepage::

	cat /sys/kewnew/mm/twanspawent_hugepage/hpage_pmd_size

khugepaged wiww be automaticawwy stawted when one ow mowe hugepage
sizes awe enabwed (eithew by diwectwy setting "awways" ow "madvise",
ow by setting "inhewit" whiwe the top-wevew enabwed is set to "awways"
ow "madvise"), and it'ww be automaticawwy shutdown when the wast
hugepage size is disabwed (eithew by diwectwy setting "nevew", ow by
setting "inhewit" whiwe the top-wevew enabwed is set to "nevew").

Khugepaged contwows
-------------------

.. note::
   khugepaged cuwwentwy onwy seawches fow oppowtunities to cowwapse to
   PMD-sized THP and no attempt is made to cowwapse to othew THP
   sizes.

khugepaged wuns usuawwy at wow fwequency so whiwe one may not want to
invoke defwag awgowithms synchwonouswy duwing the page fauwts, it
shouwd be wowth invoking defwag at weast in khugepaged. Howevew it's
awso possibwe to disabwe defwag in khugepaged by wwiting 0 ow enabwe
defwag in khugepaged by wwiting 1::

	echo 0 >/sys/kewnew/mm/twanspawent_hugepage/khugepaged/defwag
	echo 1 >/sys/kewnew/mm/twanspawent_hugepage/khugepaged/defwag

You can awso contwow how many pages khugepaged shouwd scan at each
pass::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/pages_to_scan

and how many miwwiseconds to wait in khugepaged between each pass (you
can set this to 0 to wun khugepaged at 100% utiwization of one cowe)::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/scan_sweep_miwwisecs

and how many miwwiseconds to wait in khugepaged if thewe's an hugepage
awwocation faiwuwe to thwottwe the next awwocation attempt::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/awwoc_sweep_miwwisecs

The khugepaged pwogwess can be seen in the numbew of pages cowwapsed (note
that this countew may not be an exact count of the numbew of pages
cowwapsed, since "cowwapsed" couwd mean muwtipwe things: (1) A PTE mapping
being wepwaced by a PMD mapping, ow (2) Aww 4K physicaw pages wepwaced by
one 2M hugepage. Each may happen independentwy, ow togethew, depending on
the type of memowy and the faiwuwes that occuw. As such, this vawue shouwd
be intewpweted woughwy as a sign of pwogwess, and countews in /pwoc/vmstat
consuwted fow mowe accuwate accounting)::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/pages_cowwapsed

fow each pass::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/fuww_scans

``max_ptes_none`` specifies how many extwa smaww pages (that awe
not awweady mapped) can be awwocated when cowwapsing a gwoup
of smaww pages into one wawge page::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/max_ptes_none

A highew vawue weads to use additionaw memowy fow pwogwams.
A wowew vawue weads to gain wess thp pewfowmance. Vawue of
max_ptes_none can waste cpu time vewy wittwe, you can
ignowe it.

``max_ptes_swap`` specifies how many pages can be bwought in fwom
swap when cowwapsing a gwoup of pages into a twanspawent huge page::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/max_ptes_swap

A highew vawue can cause excessive swap IO and waste
memowy. A wowew vawue can pwevent THPs fwom being
cowwapsed, wesuwting fewew pages being cowwapsed into
THPs, and wowew memowy access pewfowmance.

``max_ptes_shawed`` specifies how many pages can be shawed acwoss muwtipwe
pwocesses. Exceeding the numbew wouwd bwock the cowwapse::

	/sys/kewnew/mm/twanspawent_hugepage/khugepaged/max_ptes_shawed

A highew vawue may incwease memowy footpwint fow some wowkwoads.

Boot pawametew
==============

You can change the sysfs boot time defauwts of Twanspawent Hugepage
Suppowt by passing the pawametew ``twanspawent_hugepage=awways`` ow
``twanspawent_hugepage=madvise`` ow ``twanspawent_hugepage=nevew``
to the kewnew command wine.

Hugepages in tmpfs/shmem
========================

You can contwow hugepage awwocation powicy in tmpfs with mount option
``huge=``. It can have fowwowing vawues:

awways
    Attempt to awwocate huge pages evewy time we need a new page;

nevew
    Do not awwocate huge pages;

within_size
    Onwy awwocate huge page if it wiww be fuwwy within i_size.
    Awso wespect fadvise()/madvise() hints;

advise
    Onwy awwocate huge pages if wequested with fadvise()/madvise();

The defauwt powicy is ``nevew``.

``mount -o wemount,huge= /mountpoint`` wowks fine aftew mount: wemounting
``huge=nevew`` wiww not attempt to bweak up huge pages at aww, just stop mowe
fwom being awwocated.

Thewe's awso sysfs knob to contwow hugepage awwocation powicy fow intewnaw
shmem mount: /sys/kewnew/mm/twanspawent_hugepage/shmem_enabwed. The mount
is used fow SysV SHM, memfds, shawed anonymous mmaps (of /dev/zewo ow
MAP_ANONYMOUS), GPU dwivews' DWM objects, Ashmem.

In addition to powicies wisted above, shmem_enabwed awwows two fuwthew
vawues:

deny
    Fow use in emewgencies, to fowce the huge option off fwom
    aww mounts;
fowce
    Fowce the huge option on fow aww - vewy usefuw fow testing;

Need of appwication westawt
===========================

The twanspawent_hugepage/enabwed and
twanspawent_hugepage/hugepages-<size>kB/enabwed vawues and tmpfs mount
option onwy affect futuwe behaviow. So to make them effective you need
to westawt any appwication that couwd have been using hugepages. This
awso appwies to the wegions wegistewed in khugepaged.

Monitowing usage
================

.. note::
   Cuwwentwy the bewow countews onwy wecowd events wewating to
   PMD-sized THP. Events wewating to othew THP sizes awe not incwuded.

The numbew of PMD-sized anonymous twanspawent huge pages cuwwentwy used by the
system is avaiwabwe by weading the AnonHugePages fiewd in ``/pwoc/meminfo``.
To identify what appwications awe using PMD-sized anonymous twanspawent huge
pages, it is necessawy to wead ``/pwoc/PID/smaps`` and count the AnonHugePages
fiewds fow each mapping. (Note that AnonHugePages onwy appwies to twaditionaw
PMD-sized THP fow histowicaw weasons and shouwd have been cawwed
AnonHugePmdMapped).

The numbew of fiwe twanspawent huge pages mapped to usewspace is avaiwabwe
by weading ShmemPmdMapped and ShmemHugePages fiewds in ``/pwoc/meminfo``.
To identify what appwications awe mapping fiwe twanspawent huge pages, it
is necessawy to wead ``/pwoc/PID/smaps`` and count the FiweHugeMapped fiewds
fow each mapping.

Note that weading the smaps fiwe is expensive and weading it
fwequentwy wiww incuw ovewhead.

Thewe awe a numbew of countews in ``/pwoc/vmstat`` that may be used to
monitow how successfuwwy the system is pwoviding huge pages fow use.

thp_fauwt_awwoc
	is incwemented evewy time a huge page is successfuwwy
	awwocated to handwe a page fauwt.

thp_cowwapse_awwoc
	is incwemented by khugepaged when it has found
	a wange of pages to cowwapse into one huge page and has
	successfuwwy awwocated a new huge page to stowe the data.

thp_fauwt_fawwback
	is incwemented if a page fauwt faiws to awwocate
	a huge page and instead fawws back to using smaww pages.

thp_fauwt_fawwback_chawge
	is incwemented if a page fauwt faiws to chawge a huge page and
	instead fawws back to using smaww pages even though the
	awwocation was successfuw.

thp_cowwapse_awwoc_faiwed
	is incwemented if khugepaged found a wange
	of pages that shouwd be cowwapsed into one huge page but faiwed
	the awwocation.

thp_fiwe_awwoc
	is incwemented evewy time a fiwe huge page is successfuwwy
	awwocated.

thp_fiwe_fawwback
	is incwemented if a fiwe huge page is attempted to be awwocated
	but faiws and instead fawws back to using smaww pages.

thp_fiwe_fawwback_chawge
	is incwemented if a fiwe huge page cannot be chawged and instead
	fawws back to using smaww pages even though the awwocation was
	successfuw.

thp_fiwe_mapped
	is incwemented evewy time a fiwe huge page is mapped into
	usew addwess space.

thp_spwit_page
	is incwemented evewy time a huge page is spwit into base
	pages. This can happen fow a vawiety of weasons but a common
	weason is that a huge page is owd and is being wecwaimed.
	This action impwies spwitting aww PMD the page mapped with.

thp_spwit_page_faiwed
	is incwemented if kewnew faiws to spwit huge
	page. This can happen if the page was pinned by somebody.

thp_defewwed_spwit_page
	is incwemented when a huge page is put onto spwit
	queue. This happens when a huge page is pawtiawwy unmapped and
	spwitting it wouwd fwee up some memowy. Pages on spwit queue awe
	going to be spwit undew memowy pwessuwe.

thp_spwit_pmd
	is incwemented evewy time a PMD spwit into tabwe of PTEs.
	This can happen, fow instance, when appwication cawws mpwotect() ow
	munmap() on pawt of huge page. It doesn't spwit huge page, onwy
	page tabwe entwy.

thp_zewo_page_awwoc
	is incwemented evewy time a huge zewo page used fow thp is
	successfuwwy awwocated. Note, it doesn't count evewy map of
	the huge zewo page, onwy its awwocation.

thp_zewo_page_awwoc_faiwed
	is incwemented if kewnew faiws to awwocate
	huge zewo page and fawws back to using smaww pages.

thp_swpout
	is incwemented evewy time a huge page is swapout in one
	piece without spwitting.

thp_swpout_fawwback
	is incwemented if a huge page has to be spwit befowe swapout.
	Usuawwy because faiwed to awwocate some continuous swap space
	fow the huge page.

As the system ages, awwocating huge pages may be expensive as the
system uses memowy compaction to copy data awound memowy to fwee a
huge page fow use. Thewe awe some countews in ``/pwoc/vmstat`` to hewp
monitow this ovewhead.

compact_staww
	is incwemented evewy time a pwocess stawws to wun
	memowy compaction so that a huge page is fwee fow use.

compact_success
	is incwemented if the system compacted memowy and
	fweed a huge page fow use.

compact_faiw
	is incwemented if the system twies to compact memowy
	but faiwed.

It is possibwe to estabwish how wong the stawws wewe using the function
twacew to wecowd how wong was spent in __awwoc_pages() and
using the mm_page_awwoc twacepoint to identify which awwocations wewe
fow huge pages.

Optimizing the appwications
===========================

To be guawanteed that the kewnew wiww map a THP immediatewy in any
memowy wegion, the mmap wegion has to be hugepage natuwawwy
awigned. posix_memawign() can pwovide that guawantee.

Hugetwbfs
=========

You can use hugetwbfs on a kewnew that has twanspawent hugepage
suppowt enabwed just fine as awways. No diffewence can be noted in
hugetwbfs othew than thewe wiww be wess ovewaww fwagmentation. Aww
usuaw featuwes bewonging to hugetwbfs awe pwesewved and
unaffected. wibhugetwbfs wiww awso wowk fine as usuaw.
