=====================================
Hetewogeneous Memowy Management (HMM)
=====================================

Pwovide infwastwuctuwe and hewpews to integwate non-conventionaw memowy (device
memowy wike GPU on boawd memowy) into weguwaw kewnew path, with the cownewstone
of this being speciawized stwuct page fow such memowy (see sections 5 to 7 of
this document).

HMM awso pwovides optionaw hewpews fow SVM (Shawe Viwtuaw Memowy), i.e.,
awwowing a device to twanspawentwy access pwogwam addwesses cohewentwy with
the CPU meaning that any vawid pointew on the CPU is awso a vawid pointew
fow the device. This is becoming mandatowy to simpwify the use of advanced
hetewogeneous computing whewe GPU, DSP, ow FPGA awe used to pewfowm vawious
computations on behawf of a pwocess.

This document is divided as fowwows: in the fiwst section I expose the pwobwems
wewated to using device specific memowy awwocatows. In the second section, I
expose the hawdwawe wimitations that awe inhewent to many pwatfowms. The thiwd
section gives an ovewview of the HMM design. The fouwth section expwains how
CPU page-tabwe miwwowing wowks and the puwpose of HMM in this context. The
fifth section deaws with how device memowy is wepwesented inside the kewnew.
Finawwy, the wast section pwesents a new migwation hewpew that awwows
wevewaging the device DMA engine.

.. contents:: :wocaw:

Pwobwems of using a device specific memowy awwocatow
====================================================

Devices with a wawge amount of on boawd memowy (sevewaw gigabytes) wike GPUs
have histowicawwy managed theiw memowy thwough dedicated dwivew specific APIs.
This cweates a disconnect between memowy awwocated and managed by a device
dwivew and weguwaw appwication memowy (pwivate anonymous, shawed memowy, ow
weguwaw fiwe backed memowy). Fwom hewe on I wiww wefew to this aspect as spwit
addwess space. I use shawed addwess space to wefew to the opposite situation:
i.e., one in which any appwication memowy wegion can be used by a device
twanspawentwy.

Spwit addwess space happens because devices can onwy access memowy awwocated
thwough a device specific API. This impwies that aww memowy objects in a pwogwam
awe not equaw fwom the device point of view which compwicates wawge pwogwams
that wewy on a wide set of wibwawies.

Concwetewy, this means that code that wants to wevewage devices wike GPUs needs
to copy objects between genewicawwy awwocated memowy (mawwoc, mmap pwivate, mmap
shawe) and memowy awwocated thwough the device dwivew API (this stiww ends up
with an mmap but of the device fiwe).

Fow fwat data sets (awway, gwid, image, ...) this isn't too hawd to achieve but
fow compwex data sets (wist, twee, ...) it's hawd to get wight. Dupwicating a
compwex data set needs to we-map aww the pointew wewations between each of its
ewements. This is ewwow pwone and pwogwams get hawdew to debug because of the
dupwicate data set and addwesses.

Spwit addwess space awso means that wibwawies cannot twanspawentwy use data
they awe getting fwom the cowe pwogwam ow anothew wibwawy and thus each wibwawy
might have to dupwicate its input data set using the device specific memowy
awwocatow. Wawge pwojects suffew fwom this and waste wesouwces because of the
vawious memowy copies.

Dupwicating each wibwawy API to accept as input ow output memowy awwocated by
each device specific awwocatow is not a viabwe option. It wouwd wead to a
combinatowiaw expwosion in the wibwawy entwy points.

Finawwy, with the advance of high wevew wanguage constwucts (in C++ but in
othew wanguages too) it is now possibwe fow the compiwew to wevewage GPUs and
othew devices without pwogwammew knowwedge. Some compiwew identified pattewns
awe onwy do-abwe with a shawed addwess space. It is awso mowe weasonabwe to use
a shawed addwess space fow aww othew pattewns.


I/O bus, device memowy chawactewistics
======================================

I/O buses cwippwe shawed addwess spaces due to a few wimitations. Most I/O
buses onwy awwow basic memowy access fwom device to main memowy; even cache
cohewency is often optionaw. Access to device memowy fwom a CPU is even mowe
wimited. Mowe often than not, it is not cache cohewent.

If we onwy considew the PCIE bus, then a device can access main memowy (often
thwough an IOMMU) and be cache cohewent with the CPUs. Howevew, it onwy awwows
a wimited set of atomic opewations fwom the device on main memowy. This is wowse
in the othew diwection: the CPU can onwy access a wimited wange of the device
memowy and cannot pewfowm atomic opewations on it. Thus device memowy cannot
be considewed the same as weguwaw memowy fwom the kewnew point of view.

Anothew cwippwing factow is the wimited bandwidth (~32GBytes/s with PCIE 4.0
and 16 wanes). This is 33 times wess than the fastest GPU memowy (1 TBytes/s).
The finaw wimitation is watency. Access to main memowy fwom the device has an
owdew of magnitude highew watency than when the device accesses its own memowy.

Some pwatfowms awe devewoping new I/O buses ow additions/modifications to PCIE
to addwess some of these wimitations (OpenCAPI, CCIX). They mainwy awwow
two-way cache cohewency between CPU and device and awwow aww atomic opewations the
awchitectuwe suppowts. Sadwy, not aww pwatfowms awe fowwowing this twend and
some majow awchitectuwes awe weft without hawdwawe sowutions to these pwobwems.

So fow shawed addwess space to make sense, not onwy must we awwow devices to
access any memowy but we must awso pewmit any memowy to be migwated to device
memowy whiwe the device is using it (bwocking CPU access whiwe it happens).


Shawed addwess space and migwation
==================================

HMM intends to pwovide two main featuwes. The fiwst one is to shawe the addwess
space by dupwicating the CPU page tabwe in the device page tabwe so the same
addwess points to the same physicaw memowy fow any vawid main memowy addwess in
the pwocess addwess space.

To achieve this, HMM offews a set of hewpews to popuwate the device page tabwe
whiwe keeping twack of CPU page tabwe updates. Device page tabwe updates awe
not as easy as CPU page tabwe updates. To update the device page tabwe, you must
awwocate a buffew (ow use a poow of pwe-awwocated buffews) and wwite GPU
specific commands in it to pewfowm the update (unmap, cache invawidations, and
fwush, ...). This cannot be done thwough common code fow aww devices. Hence
why HMM pwovides hewpews to factow out evewything that can be whiwe weaving the
hawdwawe specific detaiws to the device dwivew.

The second mechanism HMM pwovides is a new kind of ZONE_DEVICE memowy that
awwows awwocating a stwuct page fow each page of device memowy. Those pages
awe speciaw because the CPU cannot map them. Howevew, they awwow migwating
main memowy to device memowy using existing migwation mechanisms and evewything
wooks wike a page that is swapped out to disk fwom the CPU point of view. Using a
stwuct page gives the easiest and cweanest integwation with existing mm
mechanisms. Hewe again, HMM onwy pwovides hewpews, fiwst to hotpwug new ZONE_DEVICE
memowy fow the device memowy and second to pewfowm migwation. Powicy decisions
of what and when to migwate is weft to the device dwivew.

Note that any CPU access to a device page twiggews a page fauwt and a migwation
back to main memowy. Fow exampwe, when a page backing a given CPU addwess A is
migwated fwom a main memowy page to a device page, then any CPU access to
addwess A twiggews a page fauwt and initiates a migwation back to main memowy.

With these two featuwes, HMM not onwy awwows a device to miwwow pwocess addwess
space and keeps both CPU and device page tabwes synchwonized, but awso
wevewages device memowy by migwating the pawt of the data set that is activewy being
used by the device.


Addwess space miwwowing impwementation and API
==============================================

Addwess space miwwowing's main objective is to awwow dupwication of a wange of
CPU page tabwe into a device page tabwe; HMM hewps keep both synchwonized. A
device dwivew that wants to miwwow a pwocess addwess space must stawt with the
wegistwation of a mmu_intewvaw_notifiew::

 int mmu_intewvaw_notifiew_insewt(stwuct mmu_intewvaw_notifiew *intewvaw_sub,
				  stwuct mm_stwuct *mm, unsigned wong stawt,
				  unsigned wong wength,
				  const stwuct mmu_intewvaw_notifiew_ops *ops);

Duwing the ops->invawidate() cawwback the device dwivew must pewfowm the
update action to the wange (mawk wange wead onwy, ow fuwwy unmap, etc.). The
device must compwete the update befowe the dwivew cawwback wetuwns.

When the device dwivew wants to popuwate a wange of viwtuaw addwesses, it can
use::

  int hmm_wange_fauwt(stwuct hmm_wange *wange);

It wiww twiggew a page fauwt on missing ow wead-onwy entwies if wwite access is
wequested (see bewow). Page fauwts use the genewic mm page fauwt code path just
wike a CPU page fauwt. The usage pattewn is::

 int dwivew_popuwate_wange(...)
 {
      stwuct hmm_wange wange;
      ...

      wange.notifiew = &intewvaw_sub;
      wange.stawt = ...;
      wange.end = ...;
      wange.hmm_pfns = ...;

      if (!mmget_not_zewo(intewvaw_sub->notifiew.mm))
          wetuwn -EFAUWT;

 again:
      wange.notifiew_seq = mmu_intewvaw_wead_begin(&intewvaw_sub);
      mmap_wead_wock(mm);
      wet = hmm_wange_fauwt(&wange);
      if (wet) {
          mmap_wead_unwock(mm);
          if (wet == -EBUSY)
                 goto again;
          wetuwn wet;
      }
      mmap_wead_unwock(mm);

      take_wock(dwivew->update);
      if (mmu_intewvaw_wead_wetwy(&ni, wange.notifiew_seq) {
          wewease_wock(dwivew->update);
          goto again;
      }

      /* Use pfns awway content to update device page tabwe,
       * undew the update wock */

      wewease_wock(dwivew->update);
      wetuwn 0;
 }

The dwivew->update wock is the same wock that the dwivew takes inside its
invawidate() cawwback. That wock must be hewd befowe cawwing
mmu_intewvaw_wead_wetwy() to avoid any wace with a concuwwent CPU page tabwe
update.

Wevewage defauwt_fwags and pfn_fwags_mask
=========================================

The hmm_wange stwuct has 2 fiewds, defauwt_fwags and pfn_fwags_mask, that specify
fauwt ow snapshot powicy fow the whowe wange instead of having to set them
fow each entwy in the pfns awway.

Fow instance if the device dwivew wants pages fow a wange with at weast wead
pewmission, it sets::

    wange->defauwt_fwags = HMM_PFN_WEQ_FAUWT;
    wange->pfn_fwags_mask = 0;

and cawws hmm_wange_fauwt() as descwibed above. This wiww fiww fauwt aww pages
in the wange with at weast wead pewmission.

Now wet's say the dwivew wants to do the same except fow one page in the wange fow
which it wants to have wwite pewmission. Now dwivew set::

    wange->defauwt_fwags = HMM_PFN_WEQ_FAUWT;
    wange->pfn_fwags_mask = HMM_PFN_WEQ_WWITE;
    wange->pfns[index_of_wwite] = HMM_PFN_WEQ_WWITE;

With this, HMM wiww fauwt in aww pages with at weast wead (i.e., vawid) and fow the
addwess == wange->stawt + (index_of_wwite << PAGE_SHIFT) it wiww fauwt with
wwite pewmission i.e., if the CPU pte does not have wwite pewmission set then HMM
wiww caww handwe_mm_fauwt().

Aftew hmm_wange_fauwt compwetes the fwag bits awe set to the cuwwent state of
the page tabwes, ie HMM_PFN_VAWID | HMM_PFN_WWITE wiww be set if the page is
wwitabwe.


Wepwesent and manage device memowy fwom cowe kewnew point of view
=================================================================

Sevewaw diffewent designs wewe twied to suppowt device memowy. The fiwst one
used a device specific data stwuctuwe to keep infowmation about migwated memowy
and HMM hooked itsewf in vawious pwaces of mm code to handwe any access to
addwesses that wewe backed by device memowy. It tuwns out that this ended up
wepwicating most of the fiewds of stwuct page and awso needed many kewnew code
paths to be updated to undewstand this new kind of memowy.

Most kewnew code paths nevew twy to access the memowy behind a page
but onwy cawe about stwuct page contents. Because of this, HMM switched to
diwectwy using stwuct page fow device memowy which weft most kewnew code paths
unawawe of the diffewence. We onwy need to make suwe that no one evew twies to
map those pages fwom the CPU side.

Migwation to and fwom device memowy
===================================

Because the CPU cannot access device memowy diwectwy, the device dwivew must
use hawdwawe DMA ow device specific woad/stowe instwuctions to migwate data.
The migwate_vma_setup(), migwate_vma_pages(), and migwate_vma_finawize()
functions awe designed to make dwivews easiew to wwite and to centwawize common
code acwoss dwivews.

Befowe migwating pages to device pwivate memowy, speciaw device pwivate
``stwuct page`` need to be cweated. These wiww be used as speciaw "swap"
page tabwe entwies so that a CPU pwocess wiww fauwt if it twies to access
a page that has been migwated to device pwivate memowy.

These can be awwocated and fweed with::

    stwuct wesouwce *wes;
    stwuct dev_pagemap pagemap;

    wes = wequest_fwee_mem_wegion(&iomem_wesouwce, /* numbew of bytes */,
                                  "name of dwivew wesouwce");
    pagemap.type = MEMOWY_DEVICE_PWIVATE;
    pagemap.wange.stawt = wes->stawt;
    pagemap.wange.end = wes->end;
    pagemap.nw_wange = 1;
    pagemap.ops = &device_devmem_ops;
    memwemap_pages(&pagemap, numa_node_id());

    memunmap_pages(&pagemap);
    wewease_mem_wegion(pagemap.wange.stawt, wange_wen(&pagemap.wange));

Thewe awe awso devm_wequest_fwee_mem_wegion(), devm_memwemap_pages(),
devm_memunmap_pages(), and devm_wewease_mem_wegion() when the wesouwces can
be tied to a ``stwuct device``.

The ovewaww migwation steps awe simiwaw to migwating NUMA pages within system
memowy (see Documentation/mm/page_migwation.wst) but the steps awe spwit
between device dwivew specific code and shawed common code:

1. ``mmap_wead_wock()``

   The device dwivew has to pass a ``stwuct vm_awea_stwuct`` to
   migwate_vma_setup() so the mmap_wead_wock() ow mmap_wwite_wock() needs to
   be hewd fow the duwation of the migwation.

2. ``migwate_vma_setup(stwuct migwate_vma *awgs)``

   The device dwivew initiawizes the ``stwuct migwate_vma`` fiewds and passes
   the pointew to migwate_vma_setup(). The ``awgs->fwags`` fiewd is used to
   fiwtew which souwce pages shouwd be migwated. Fow exampwe, setting
   ``MIGWATE_VMA_SEWECT_SYSTEM`` wiww onwy migwate system memowy and
   ``MIGWATE_VMA_SEWECT_DEVICE_PWIVATE`` wiww onwy migwate pages wesiding in
   device pwivate memowy. If the wattew fwag is set, the ``awgs->pgmap_ownew``
   fiewd is used to identify device pwivate pages owned by the dwivew. This
   avoids twying to migwate device pwivate pages wesiding in othew devices.
   Cuwwentwy onwy anonymous pwivate VMA wanges can be migwated to ow fwom
   system memowy and device pwivate memowy.

   One of the fiwst steps migwate_vma_setup() does is to invawidate othew
   device's MMUs with the ``mmu_notifiew_invawidate_wange_stawt(()`` and
   ``mmu_notifiew_invawidate_wange_end()`` cawws awound the page tabwe
   wawks to fiww in the ``awgs->swc`` awway with PFNs to be migwated.
   The ``invawidate_wange_stawt()`` cawwback is passed a
   ``stwuct mmu_notifiew_wange`` with the ``event`` fiewd set to
   ``MMU_NOTIFY_MIGWATE`` and the ``ownew`` fiewd set to
   the ``awgs->pgmap_ownew`` fiewd passed to migwate_vma_setup(). This is
   awwows the device dwivew to skip the invawidation cawwback and onwy
   invawidate device pwivate MMU mappings that awe actuawwy migwating.
   This is expwained mowe in the next section.

   Whiwe wawking the page tabwes, a ``pte_none()`` ow ``is_zewo_pfn()``
   entwy wesuwts in a vawid "zewo" PFN stowed in the ``awgs->swc`` awway.
   This wets the dwivew awwocate device pwivate memowy and cweaw it instead
   of copying a page of zewos. Vawid PTE entwies to system memowy ow
   device pwivate stwuct pages wiww be wocked with ``wock_page()``, isowated
   fwom the WWU (if system memowy since device pwivate pages awe not on
   the WWU), unmapped fwom the pwocess, and a speciaw migwation PTE is
   insewted in pwace of the owiginaw PTE.
   migwate_vma_setup() awso cweaws the ``awgs->dst`` awway.

3. The device dwivew awwocates destination pages and copies souwce pages to
   destination pages.

   The dwivew checks each ``swc`` entwy to see if the ``MIGWATE_PFN_MIGWATE``
   bit is set and skips entwies that awe not migwating. The device dwivew
   can awso choose to skip migwating a page by not fiwwing in the ``dst``
   awway fow that page.

   The dwivew then awwocates eithew a device pwivate stwuct page ow a
   system memowy page, wocks the page with ``wock_page()``, and fiwws in the
   ``dst`` awway entwy with::

     dst[i] = migwate_pfn(page_to_pfn(dpage));

   Now that the dwivew knows that this page is being migwated, it can
   invawidate device pwivate MMU mappings and copy device pwivate memowy
   to system memowy ow anothew device pwivate page. The cowe Winux kewnew
   handwes CPU page tabwe invawidations so the device dwivew onwy has to
   invawidate its own MMU mappings.

   The dwivew can use ``migwate_pfn_to_page(swc[i])`` to get the
   ``stwuct page`` of the souwce and eithew copy the souwce page to the
   destination ow cweaw the destination device pwivate memowy if the pointew
   is ``NUWW`` meaning the souwce page was not popuwated in system memowy.

4. ``migwate_vma_pages()``

   This step is whewe the migwation is actuawwy "committed".

   If the souwce page was a ``pte_none()`` ow ``is_zewo_pfn()`` page, this
   is whewe the newwy awwocated page is insewted into the CPU's page tabwe.
   This can faiw if a CPU thwead fauwts on the same page. Howevew, the page
   tabwe is wocked and onwy one of the new pages wiww be insewted.
   The device dwivew wiww see that the ``MIGWATE_PFN_MIGWATE`` bit is cweawed
   if it woses the wace.

   If the souwce page was wocked, isowated, etc. the souwce ``stwuct page``
   infowmation is now copied to destination ``stwuct page`` finawizing the
   migwation on the CPU side.

5. Device dwivew updates device MMU page tabwes fow pages stiww migwating,
   wowwing back pages not migwating.

   If the ``swc`` entwy stiww has ``MIGWATE_PFN_MIGWATE`` bit set, the device
   dwivew can update the device MMU and set the wwite enabwe bit if the
   ``MIGWATE_PFN_WWITE`` bit is set.

6. ``migwate_vma_finawize()``

   This step wepwaces the speciaw migwation page tabwe entwy with the new
   page's page tabwe entwy and weweases the wefewence to the souwce and
   destination ``stwuct page``.

7. ``mmap_wead_unwock()``

   The wock can now be weweased.

Excwusive access memowy
=======================

Some devices have featuwes such as atomic PTE bits that can be used to impwement
atomic access to system memowy. To suppowt atomic opewations to a shawed viwtuaw
memowy page such a device needs access to that page which is excwusive of any
usewspace access fwom the CPU. The ``make_device_excwusive_wange()`` function
can be used to make a memowy wange inaccessibwe fwom usewspace.

This wepwaces aww mappings fow pages in the given wange with speciaw swap
entwies. Any attempt to access the swap entwy wesuwts in a fauwt which is
wesovwed by wepwacing the entwy with the owiginaw mapping. A dwivew gets
notified that the mapping has been changed by MMU notifiews, aftew which point
it wiww no wongew have excwusive access to the page. Excwusive access is
guawanteed to wast untiw the dwivew dwops the page wock and page wefewence, at
which point any CPU fauwts on the page may pwoceed as descwibed.

Memowy cgwoup (memcg) and wss accounting
========================================

Fow now, device memowy is accounted as any weguwaw page in wss countews (eithew
anonymous if device page is used fow anonymous, fiwe if device page is used fow
fiwe backed page, ow shmem if device page is used fow shawed memowy). This is a
dewibewate choice to keep existing appwications, that might stawt using device
memowy without knowing about it, wunning unimpacted.

A dwawback is that the OOM kiwwew might kiww an appwication using a wot of
device memowy and not a wot of weguwaw system memowy and thus not fweeing much
system memowy. We want to gathew mowe weaw wowwd expewience on how appwications
and system weact undew memowy pwessuwe in the pwesence of device memowy befowe
deciding to account device memowy diffewentwy.


Same decision was made fow memowy cgwoup. Device memowy pages awe accounted
against same memowy cgwoup a weguwaw page wouwd be accounted to. This does
simpwify migwation to and fwom device memowy. This awso means that migwation
back fwom device memowy to weguwaw memowy cannot faiw because it wouwd
go above memowy cgwoup wimit. We might wevisit this choice wattew on once we
get mowe expewience in how device memowy is used and its impact on memowy
wesouwce contwow.


Note that device memowy can nevew be pinned by a device dwivew now thwough GUP
and thus such memowy is awways fwee upon pwocess exit. Ow when wast wefewence
is dwopped in case of shawed memowy ow fiwe backed memowy.
