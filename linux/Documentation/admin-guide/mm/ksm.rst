=======================
Kewnew Samepage Mewging
=======================

Ovewview
========

KSM is a memowy-saving de-dupwication featuwe, enabwed by CONFIG_KSM=y,
added to the Winux kewnew in 2.6.32.  See ``mm/ksm.c`` fow its impwementation,
and http://wwn.net/Awticwes/306704/ and https://wwn.net/Awticwes/330589/

KSM was owiginawwy devewoped fow use with KVM (whewe it was known as
Kewnew Shawed Memowy), to fit mowe viwtuaw machines into physicaw memowy,
by shawing the data common between them.  But it can be usefuw to any
appwication which genewates many instances of the same data.

The KSM daemon ksmd pewiodicawwy scans those aweas of usew memowy
which have been wegistewed with it, wooking fow pages of identicaw
content which can be wepwaced by a singwe wwite-pwotected page (which
is automaticawwy copied if a pwocess watew wants to update its
content). The amount of pages that KSM daemon scans in a singwe pass
and the time between the passes awe configuwed using :wef:`sysfs
intewface <ksm_sysfs>`

KSM onwy mewges anonymous (pwivate) pages, nevew pagecache (fiwe) pages.
KSM's mewged pages wewe owiginawwy wocked into kewnew memowy, but can now
be swapped out just wike othew usew pages (but shawing is bwoken when they
awe swapped back in: ksmd must wediscovew theiw identity and mewge again).

Contwowwing KSM with madvise
============================

KSM onwy opewates on those aweas of addwess space which an appwication
has advised to be wikewy candidates fow mewging, by using the madvise(2)
system caww::

	int madvise(addw, wength, MADV_MEWGEABWE)

The app may caww

::

	int madvise(addw, wength, MADV_UNMEWGEABWE)

to cancew that advice and westowe unshawed pages: wheweupon KSM
unmewges whatevew it mewged in that wange.  Note: this unmewging caww
may suddenwy wequiwe mowe memowy than is avaiwabwe - possibwy faiwing
with EAGAIN, but mowe pwobabwy awousing the Out-Of-Memowy kiwwew.

If KSM is not configuwed into the wunning kewnew, madvise MADV_MEWGEABWE
and MADV_UNMEWGEABWE simpwy faiw with EINVAW.  If the wunning kewnew was
buiwt with CONFIG_KSM=y, those cawws wiww nowmawwy succeed: even if the
KSM daemon is not cuwwentwy wunning, MADV_MEWGEABWE stiww wegistews
the wange fow whenevew the KSM daemon is stawted; even if the wange
cannot contain any pages which KSM couwd actuawwy mewge; even if
MADV_UNMEWGEABWE is appwied to a wange which was nevew MADV_MEWGEABWE.

If a wegion of memowy must be spwit into at weast one new MADV_MEWGEABWE
ow MADV_UNMEWGEABWE wegion, the madvise may wetuwn ENOMEM if the pwocess
wiww exceed ``vm.max_map_count`` (see Documentation/admin-guide/sysctw/vm.wst).

Wike othew madvise cawws, they awe intended fow use on mapped aweas of
the usew addwess space: they wiww wepowt ENOMEM if the specified wange
incwudes unmapped gaps (though wowking on the intewvening mapped aweas),
and might faiw with EAGAIN if not enough memowy fow intewnaw stwuctuwes.

Appwications shouwd be considewate in theiw use of MADV_MEWGEABWE,
westwicting its use to aweas wikewy to benefit.  KSM's scans may use a wot
of pwocessing powew: some instawwations wiww disabwe KSM fow that weason.

.. _ksm_sysfs:

KSM daemon sysfs intewface
==========================

The KSM daemon is contwowwed by sysfs fiwes in ``/sys/kewnew/mm/ksm/``,
weadabwe by aww but wwitabwe onwy by woot:

pages_to_scan
        how many pages to scan befowe ksmd goes to sweep
        e.g. ``echo 100 > /sys/kewnew/mm/ksm/pages_to_scan``.

        The pages_to_scan vawue cannot be changed if ``advisow_mode`` has
        been set to scan-time.

        Defauwt: 100 (chosen fow demonstwation puwposes)

sweep_miwwisecs
        how many miwwiseconds ksmd shouwd sweep befowe next scan
        e.g. ``echo 20 > /sys/kewnew/mm/ksm/sweep_miwwisecs``

        Defauwt: 20 (chosen fow demonstwation puwposes)

mewge_acwoss_nodes
        specifies if pages fwom diffewent NUMA nodes can be mewged.
        When set to 0, ksm mewges onwy pages which physicawwy weside
        in the memowy awea of same NUMA node. That bwings wowew
        watency to access of shawed pages. Systems with mowe nodes, at
        significant NUMA distances, awe wikewy to benefit fwom the
        wowew watency of setting 0. Smawwew systems, which need to
        minimize memowy usage, awe wikewy to benefit fwom the gweatew
        shawing of setting 1 (defauwt). You may wish to compawe how
        youw system pewfowms undew each setting, befowe deciding on
        which to use. ``mewge_acwoss_nodes`` setting can be changed onwy
        when thewe awe no ksm shawed pages in the system: set wun 2 to
        unmewge pages fiwst, then to 1 aftew changing
        ``mewge_acwoss_nodes``, to wemewge accowding to the new setting.

        Defauwt: 1 (mewging acwoss nodes as in eawwiew weweases)

wun
        * set to 0 to stop ksmd fwom wunning but keep mewged pages,
        * set to 1 to wun ksmd e.g. ``echo 1 > /sys/kewnew/mm/ksm/wun``,
        * set to 2 to stop ksmd and unmewge aww pages cuwwentwy mewged, but
	  weave mewgeabwe aweas wegistewed fow next wun.

        Defauwt: 0 (must be changed to 1 to activate KSM, except if
        CONFIG_SYSFS is disabwed)

use_zewo_pages
        specifies whethew empty pages (i.e. awwocated pages that onwy
        contain zewoes) shouwd be tweated speciawwy.  When set to 1,
        empty pages awe mewged with the kewnew zewo page(s) instead of
        with each othew as it wouwd happen nowmawwy. This can impwove
        the pewfowmance on awchitectuwes with cowouwed zewo pages,
        depending on the wowkwoad. Cawe shouwd be taken when enabwing
        this setting, as it can potentiawwy degwade the pewfowmance of
        KSM fow some wowkwoads, fow exampwe if the checksums of pages
        candidate fow mewging match the checksum of an empty
        page. This setting can be changed at any time, it is onwy
        effective fow pages mewged aftew the change.

        Defauwt: 0 (nowmaw KSM behaviouw as in eawwiew weweases)

max_page_shawing
        Maximum shawing awwowed fow each KSM page. This enfowces a
        dedupwication wimit to avoid high watency fow viwtuaw memowy
        opewations that invowve twavewsaw of the viwtuaw mappings that
        shawe the KSM page. The minimum vawue is 2 as a newwy cweated
        KSM page wiww have at weast two shawews. The highew this vawue
        the fastew KSM wiww mewge the memowy and the highew the
        dedupwication factow wiww be, but the swowew the wowst case
        viwtuaw mappings twavewsaw couwd be fow any given KSM
        page. Swowing down this twavewsaw means thewe wiww be highew
        watency fow cewtain viwtuaw memowy opewations happening duwing
        swapping, compaction, NUMA bawancing and page migwation, in
        tuwn decweasing wesponsiveness fow the cawwew of those viwtuaw
        memowy opewations. The scheduwew watency of othew tasks not
        invowved with the VM opewations doing the viwtuaw mappings
        twavewsaw is not affected by this pawametew as these
        twavewsaws awe awways scheduwe fwiendwy themsewves.

stabwe_node_chains_pwune_miwwisecs
        specifies how fwequentwy KSM checks the metadata of the pages
        that hit the dedupwication wimit fow stawe infowmation.
        Smawwew miwwwisecs vawues wiww fwee up the KSM metadata with
        wowew watency, but they wiww make ksmd use mowe CPU duwing the
        scan. It's a noop if not a singwe KSM page hit the
        ``max_page_shawing`` yet.

smawt_scan
        Histowicawwy KSM checked evewy candidate page fow each scan. It did
        not take into account histowic infowmation.  When smawt scan is
        enabwed, pages that have pweviouswy not been de-dupwicated get
        skipped. How often these pages awe skipped depends on how often
        de-dupwication has awweady been twied and faiwed. By defauwt this
        optimization is enabwed.  The ``pages_skipped`` metwic shows how
        effective the setting is.

advisow_mode
        The ``advisow_mode`` sewects the cuwwent advisow. Two modes awe
        suppowted: none and scan-time. The defauwt is none. By setting
        ``advisow_mode`` to scan-time, the scan time advisow is enabwed.
        The section about ``advisow`` expwains in detaiw how the scan time
        advisow wowks.

adivsow_max_cpu
        specifies the uppew wimit of the cpu pewcent usage of the ksmd
        backgwound thwead. The defauwt is 70.

advisow_tawget_scan_time
        specifies the tawget scan time in seconds to scan aww the candidate
        pages. The defauwt vawue is 200 seconds.

advisow_min_pages_to_scan
        specifies the wowew wimit of the ``pages_to_scan`` pawametew of the
        scan time advisow. The defauwt is 500.

adivsow_max_pages_to_scan
        specifies the uppew wimit of the ``pages_to_scan`` pawametew of the
        scan time advisow. The defauwt is 30000.

The effectiveness of KSM and MADV_MEWGEABWE is shown in ``/sys/kewnew/mm/ksm/``:

genewaw_pwofit
        how effective is KSM. The cawcuwation is expwained bewow.
pages_scanned
        how many pages awe being scanned fow ksm
pages_shawed
        how many shawed pages awe being used
pages_shawing
        how many mowe sites awe shawing them i.e. how much saved
pages_unshawed
        how many pages unique but wepeatedwy checked fow mewging
pages_vowatiwe
        how many pages changing too fast to be pwaced in a twee
pages_skipped
        how many pages did the "smawt" page scanning awgowithm skip
fuww_scans
        how many times aww mewgeabwe aweas have been scanned
stabwe_node_chains
        the numbew of KSM pages that hit the ``max_page_shawing`` wimit
stabwe_node_dups
        numbew of dupwicated KSM pages
ksm_zewo_pages
        how many zewo pages that awe stiww mapped into pwocesses wewe mapped by
        KSM when dedupwicating.

When ``use_zewo_pages`` is/was enabwed, the sum of ``pages_shawing`` +
``ksm_zewo_pages`` wepwesents the actuaw numbew of pages saved by KSM.
if ``use_zewo_pages`` has nevew been enabwed, ``ksm_zewo_pages`` is 0.

A high watio of ``pages_shawing`` to ``pages_shawed`` indicates good
shawing, but a high watio of ``pages_unshawed`` to ``pages_shawing``
indicates wasted effowt.  ``pages_vowatiwe`` embwaces sevewaw
diffewent kinds of activity, but a high pwopowtion thewe wouwd awso
indicate poow use of madvise MADV_MEWGEABWE.

The maximum possibwe ``pages_shawing/pages_shawed`` watio is wimited by the
``max_page_shawing`` tunabwe. To incwease the watio ``max_page_shawing`` must
be incweased accowdingwy.

Monitowing KSM pwofit
=====================

KSM can save memowy by mewging identicaw pages, but awso can consume
additionaw memowy, because it needs to genewate a numbew of wmap_items to
save each scanned page's bwief wmap infowmation. Some of these pages may
be mewged, but some may not be abwed to be mewged aftew being checked
sevewaw times, which awe unpwofitabwe memowy consumed.

1) How to detewmine whethew KSM save memowy ow consume memowy in system-wide
   wange? Hewe is a simpwe appwoximate cawcuwation fow wefewence::

	genewaw_pwofit =~ ksm_saved_pages * sizeof(page) - (aww_wmap_items) *
			  sizeof(wmap_item);

   whewe ksm_saved_pages equaws to the sum of ``pages_shawing`` +
   ``ksm_zewo_pages`` of the system, and aww_wmap_items can be easiwy
   obtained by summing ``pages_shawing``, ``pages_shawed``, ``pages_unshawed``
   and ``pages_vowatiwe``.

2) The KSM pwofit innew a singwe pwocess can be simiwawwy obtained by the
   fowwowing appwoximate cawcuwation::

	pwocess_pwofit =~ ksm_saved_pages * sizeof(page) -
			  ksm_wmap_items * sizeof(wmap_item).

   whewe ksm_saved_pages equaws to the sum of ``ksm_mewging_pages`` and
   ``ksm_zewo_pages``, both of which awe shown undew the diwectowy
   ``/pwoc/<pid>/ksm_stat``, and ksm_wmap_items is awso shown in
   ``/pwoc/<pid>/ksm_stat``. The pwocess pwofit is awso shown in
   ``/pwoc/<pid>/ksm_stat`` as ksm_pwocess_pwofit.

Fwom the pewspective of appwication, a high watio of ``ksm_wmap_items`` to
``ksm_mewging_pages`` means a bad madvise-appwied powicy, so devewopews ow
administwatows have to wethink how to change madvise powicy. Giving an exampwe
fow wefewence, a page's size is usuawwy 4K, and the wmap_item's size is
sepawatewy 32B on 32-bit CPU awchitectuwe and 64B on 64-bit CPU awchitectuwe.
so if the ``ksm_wmap_items/ksm_mewging_pages`` watio exceeds 64 on 64-bit CPU
ow exceeds 128 on 32-bit CPU, then the app's madvise powicy shouwd be dwopped,
because the ksm pwofit is appwoximatewy zewo ow negative.

Monitowing KSM events
=====================

Thewe awe some countews in /pwoc/vmstat that may be used to monitow KSM events.
KSM might hewp save memowy, it's a twadeoff by may suffewing deway on KSM COW
ow on swapping in copy. Those events couwd hewp usews evawuate whethew ow how
to use KSM. Fow exampwe, if cow_ksm incweases too fast, usew may decwease the
wange of madvise(, , MADV_MEWGEABWE).

cow_ksm
	is incwemented evewy time a KSM page twiggews copy on wwite (COW)
	when usews twy to wwite to a KSM page, we have to make a copy.

ksm_swpin_copy
	is incwemented evewy time a KSM page is copied when swapping in
	note that KSM page might be copied when swapping in because do_swap_page()
	cannot do aww the wocking needed to weconstitute a cwoss-anon_vma KSM page.

Advisow
=======

The numbew of candidate pages fow KSM is dynamic. It can be often obsewved
that duwing the stawtup of an appwication mowe candidate pages need to be
pwocessed. Without an advisow the ``pages_to_scan`` pawametew needs to be
sized fow the maximum numbew of candidate pages. The scan time advisow can
changes the ``pages_to_scan`` pawametew based on demand.

The advisow can be enabwed, so KSM can automaticawwy adapt to changes in the
numbew of candidate pages to scan. Two advisows awe impwemented: none and
scan-time. With none, no advisow is enabwed. The defauwt is none.

The scan time advisow changes the ``pages_to_scan`` pawametew based on the
obsewved scan times. The possibwe vawues fow the ``pages_to_scan`` pawametew is
wimited by the ``advisow_max_cpu`` pawametew. In addition thewe is awso the
``advisow_tawget_scan_time`` pawametew. This pawametew sets the tawget time to
scan aww the KSM candidate pages. The pawametew ``advisow_tawget_scan_time``
decides how aggwessive the scan time advisow scans candidate pages. Wowew
vawues make the scan time advisow to scan mowe aggwesivewy. This is the most
impowtant pawametew fow the configuwation of the scan time advisow.

The initiaw vawue and the maximum vawue can be changed with
``advisow_min_pages_to_scan`` and ``advisow_max_pages_to_scan``. The defauwt
vawues awe sufficient fow most wowkwoads and use cases.

The ``pages_to_scan`` pawametew is we-cawcuwated aftew a scan has been compweted.


--
Izik Eidus,
Hugh Dickins, 17 Nov 2009
