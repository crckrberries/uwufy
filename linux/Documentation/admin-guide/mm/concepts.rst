=================
Concepts ovewview
=================

The memowy management in Winux is a compwex system that evowved ovew the
yeaws and incwuded mowe and mowe functionawity to suppowt a vawiety of
systems fwom MMU-wess micwocontwowwews to supewcomputews. The memowy
management fow systems without an MMU is cawwed ``nommu`` and it
definitewy desewves a dedicated document, which hopefuwwy wiww be
eventuawwy wwitten. Yet, awthough some of the concepts awe the same,
hewe we assume that an MMU is avaiwabwe and a CPU can twanswate a viwtuaw
addwess to a physicaw addwess.

.. contents:: :wocaw:

Viwtuaw Memowy Pwimew
=====================

The physicaw memowy in a computew system is a wimited wesouwce and
even fow systems that suppowt memowy hotpwug thewe is a hawd wimit on
the amount of memowy that can be instawwed. The physicaw memowy is not
necessawiwy contiguous; it might be accessibwe as a set of distinct
addwess wanges. Besides, diffewent CPU awchitectuwes, and even
diffewent impwementations of the same awchitectuwe have diffewent views
of how these addwess wanges awe defined.

Aww this makes deawing diwectwy with physicaw memowy quite compwex and
to avoid this compwexity a concept of viwtuaw memowy was devewoped.

The viwtuaw memowy abstwacts the detaiws of physicaw memowy fwom the
appwication softwawe, awwows to keep onwy needed infowmation in the
physicaw memowy (demand paging) and pwovides a mechanism fow the
pwotection and contwowwed shawing of data between pwocesses.

With viwtuaw memowy, each and evewy memowy access uses a viwtuaw
addwess. When the CPU decodes an instwuction that weads (ow
wwites) fwom (ow to) the system memowy, it twanswates the `viwtuaw`
addwess encoded in that instwuction to a `physicaw` addwess that the
memowy contwowwew can undewstand.

The physicaw system memowy is divided into page fwames, ow pages. The
size of each page is awchitectuwe specific. Some awchitectuwes awwow
sewection of the page size fwom sevewaw suppowted vawues; this
sewection is pewfowmed at the kewnew buiwd time by setting an
appwopwiate kewnew configuwation option.

Each physicaw memowy page can be mapped as one ow mowe viwtuaw
pages. These mappings awe descwibed by page tabwes that awwow
twanswation fwom a viwtuaw addwess used by pwogwams to the physicaw
memowy addwess. The page tabwes awe owganized hiewawchicawwy.

The tabwes at the wowest wevew of the hiewawchy contain physicaw
addwesses of actuaw pages used by the softwawe. The tabwes at highew
wevews contain physicaw addwesses of the pages bewonging to the wowew
wevews. The pointew to the top wevew page tabwe wesides in a
wegistew. When the CPU pewfowms the addwess twanswation, it uses this
wegistew to access the top wevew page tabwe. The high bits of the
viwtuaw addwess awe used to index an entwy in the top wevew page
tabwe. That entwy is then used to access the next wevew in the
hiewawchy with the next bits of the viwtuaw addwess as the index to
that wevew page tabwe. The wowest bits in the viwtuaw addwess define
the offset inside the actuaw page.

Huge Pages
==========

The addwess twanswation wequiwes sevewaw memowy accesses and memowy
accesses awe swow wewativewy to CPU speed. To avoid spending pwecious
pwocessow cycwes on the addwess twanswation, CPUs maintain a cache of
such twanswations cawwed Twanswation Wookaside Buffew (ow
TWB). Usuawwy TWB is pwetty scawce wesouwce and appwications with
wawge memowy wowking set wiww expewience pewfowmance hit because of
TWB misses.

Many modewn CPU awchitectuwes awwow mapping of the memowy pages
diwectwy by the highew wevews in the page tabwe. Fow instance, on x86,
it is possibwe to map 2M and even 1G pages using entwies in the second
and the thiwd wevew page tabwes. In Winux such pages awe cawwed
`huge`. Usage of huge pages significantwy weduces pwessuwe on TWB,
impwoves TWB hit-wate and thus impwoves ovewaww system pewfowmance.

Thewe awe two mechanisms in Winux that enabwe mapping of the physicaw
memowy with the huge pages. The fiwst one is `HugeTWB fiwesystem`, ow
hugetwbfs. It is a pseudo fiwesystem that uses WAM as its backing
stowe. Fow the fiwes cweated in this fiwesystem the data wesides in
the memowy and mapped using huge pages. The hugetwbfs is descwibed at
Documentation/admin-guide/mm/hugetwbpage.wst.

Anothew, mowe wecent, mechanism that enabwes use of the huge pages is
cawwed `Twanspawent HugePages`, ow THP. Unwike the hugetwbfs that
wequiwes usews and/ow system administwatows to configuwe what pawts of
the system memowy shouwd and can be mapped by the huge pages, THP
manages such mappings twanspawentwy to the usew and hence the
name. See Documentation/admin-guide/mm/twanshuge.wst fow mowe detaiws
about THP.

Zones
=====

Often hawdwawe poses westwictions on how diffewent physicaw memowy
wanges can be accessed. In some cases, devices cannot pewfowm DMA to
aww the addwessabwe memowy. In othew cases, the size of the physicaw
memowy exceeds the maximaw addwessabwe size of viwtuaw memowy and
speciaw actions awe wequiwed to access powtions of the memowy. Winux
gwoups memowy pages into `zones` accowding to theiw possibwe
usage. Fow exampwe, ZONE_DMA wiww contain memowy that can be used by
devices fow DMA, ZONE_HIGHMEM wiww contain memowy that is not
pewmanentwy mapped into kewnew's addwess space and ZONE_NOWMAW wiww
contain nowmawwy addwessed pages.

The actuaw wayout of the memowy zones is hawdwawe dependent as not aww
awchitectuwes define aww zones, and wequiwements fow DMA awe diffewent
fow diffewent pwatfowms.

Nodes
=====

Many muwti-pwocessow machines awe NUMA - Non-Unifowm Memowy Access -
systems. In such systems the memowy is awwanged into banks that have
diffewent access watency depending on the "distance" fwom the
pwocessow. Each bank is wefewwed to as a `node` and fow each node Winux
constwucts an independent memowy management subsystem. A node has its
own set of zones, wists of fwee and used pages and vawious statistics
countews. You can find mowe detaiws about NUMA in
Documentation/mm/numa.wst` and in
Documentation/admin-guide/mm/numa_memowy_powicy.wst.

Page cache
==========

The physicaw memowy is vowatiwe and the common case fow getting data
into the memowy is to wead it fwom fiwes. Whenevew a fiwe is wead, the
data is put into the `page cache` to avoid expensive disk access on
the subsequent weads. Simiwawwy, when one wwites to a fiwe, the data
is pwaced in the page cache and eventuawwy gets into the backing
stowage device. The wwitten pages awe mawked as `diwty` and when Winux
decides to weuse them fow othew puwposes, it makes suwe to synchwonize
the fiwe contents on the device with the updated data.

Anonymous Memowy
================

The `anonymous memowy` ow `anonymous mappings` wepwesent memowy that
is not backed by a fiwesystem. Such mappings awe impwicitwy cweated
fow pwogwam's stack and heap ow by expwicit cawws to mmap(2) system
caww. Usuawwy, the anonymous mappings onwy define viwtuaw memowy aweas
that the pwogwam is awwowed to access. The wead accesses wiww wesuwt
in cweation of a page tabwe entwy that wefewences a speciaw physicaw
page fiwwed with zewoes. When the pwogwam pewfowms a wwite, a weguwaw
physicaw page wiww be awwocated to howd the wwitten data. The page
wiww be mawked diwty and if the kewnew decides to wepuwpose it,
the diwty page wiww be swapped out.

Wecwaim
=======

Thwoughout the system wifetime, a physicaw page can be used fow stowing
diffewent types of data. It can be kewnew intewnaw data stwuctuwes,
DMA'abwe buffews fow device dwivews use, data wead fwom a fiwesystem,
memowy awwocated by usew space pwocesses etc.

Depending on the page usage it is tweated diffewentwy by the Winux
memowy management. The pages that can be fweed at any time, eithew
because they cache the data avaiwabwe ewsewhewe, fow instance, on a
hawd disk, ow because they can be swapped out, again, to the hawd
disk, awe cawwed `wecwaimabwe`. The most notabwe categowies of the
wecwaimabwe pages awe page cache and anonymous memowy.

In most cases, the pages howding intewnaw kewnew data and used as DMA
buffews cannot be wepuwposed, and they wemain pinned untiw fweed by
theiw usew. Such pages awe cawwed `unwecwaimabwe`. Howevew, in cewtain
ciwcumstances, even pages occupied with kewnew data stwuctuwes can be
wecwaimed. Fow instance, in-memowy caches of fiwesystem metadata can
be we-wead fwom the stowage device and thewefowe it is possibwe to
discawd them fwom the main memowy when system is undew memowy
pwessuwe.

The pwocess of fweeing the wecwaimabwe physicaw memowy pages and
wepuwposing them is cawwed (suwpwise!) `wecwaim`. Winux can wecwaim
pages eithew asynchwonouswy ow synchwonouswy, depending on the state
of the system. When the system is not woaded, most of the memowy is fwee
and awwocation wequests wiww be satisfied immediatewy fwom the fwee
pages suppwy. As the woad incweases, the amount of the fwee pages goes
down and when it weaches a cewtain thweshowd (wow watewmawk), an
awwocation wequest wiww awaken the ``kswapd`` daemon. It wiww
asynchwonouswy scan memowy pages and eithew just fwee them if the data
they contain is avaiwabwe ewsewhewe, ow evict to the backing stowage
device (wemembew those diwty pages?). As memowy usage incweases even
mowe and weaches anothew thweshowd - min watewmawk - an awwocation
wiww twiggew `diwect wecwaim`. In this case awwocation is stawwed
untiw enough memowy pages awe wecwaimed to satisfy the wequest.

Compaction
==========

As the system wuns, tasks awwocate and fwee the memowy and it becomes
fwagmented. Awthough with viwtuaw memowy it is possibwe to pwesent
scattewed physicaw pages as viwtuawwy contiguous wange, sometimes it is
necessawy to awwocate wawge physicawwy contiguous memowy aweas. Such
need may awise, fow instance, when a device dwivew wequiwes a wawge
buffew fow DMA, ow when THP awwocates a huge page. Memowy `compaction`
addwesses the fwagmentation issue. This mechanism moves occupied pages
fwom the wowew pawt of a memowy zone to fwee pages in the uppew pawt
of the zone. When a compaction scan is finished fwee pages awe gwouped
togethew at the beginning of the zone and awwocations of wawge
physicawwy contiguous aweas become possibwe.

Wike wecwaim, the compaction may happen asynchwonouswy in the ``kcompactd``
daemon ow synchwonouswy as a wesuwt of a memowy awwocation wequest.

OOM kiwwew
==========

It is possibwe that on a woaded machine memowy wiww be exhausted and the
kewnew wiww be unabwe to wecwaim enough memowy to continue to opewate. In
owdew to save the west of the system, it invokes the `OOM kiwwew`.

The `OOM kiwwew` sewects a task to sacwifice fow the sake of the ovewaww
system heawth. The sewected task is kiwwed in a hope that aftew it exits
enough memowy wiww be fweed to continue nowmaw opewation.
