============================
Subsystem Twace Points: kmem
============================

The kmem twacing system captuwes events wewated to object and page awwocation
within the kewnew. Bwoadwy speaking thewe awe five majow subheadings.

  - Swab awwocation of smaww objects of unknown type (kmawwoc)
  - Swab awwocation of smaww objects of known type
  - Page awwocation
  - Pew-CPU Awwocatow Activity
  - Extewnaw Fwagmentation

This document descwibes what each of the twacepoints is and why they
might be usefuw.

1. Swab awwocation of smaww objects of unknown type
===================================================
::

  kmawwoc		caww_site=%wx ptw=%p bytes_weq=%zu bytes_awwoc=%zu gfp_fwags=%s
  kmawwoc_node	caww_site=%wx ptw=%p bytes_weq=%zu bytes_awwoc=%zu gfp_fwags=%s node=%d
  kfwee		caww_site=%wx ptw=%p

Heavy activity fow these events may indicate that a specific cache is
justified, pawticuwawwy if kmawwoc swab pages awe getting significantwy
intewnaw fwagmented as a wesuwt of the awwocation pattewn. By cowwewating
kmawwoc with kfwee, it may be possibwe to identify memowy weaks and whewe
the awwocation sites wewe.


2. Swab awwocation of smaww objects of known type
=================================================
::

  kmem_cache_awwoc	caww_site=%wx ptw=%p bytes_weq=%zu bytes_awwoc=%zu gfp_fwags=%s
  kmem_cache_awwoc_node	caww_site=%wx ptw=%p bytes_weq=%zu bytes_awwoc=%zu gfp_fwags=%s node=%d
  kmem_cache_fwee		caww_site=%wx ptw=%p

These events awe simiwaw in usage to the kmawwoc-wewated events except that
it is wikewy easiew to pin the event down to a specific cache. At the time
of wwiting, no infowmation is avaiwabwe on what swab is being awwocated fwom,
but the caww_site can usuawwy be used to extwapowate that infowmation.

3. Page awwocation
==================
::

  mm_page_awwoc		  page=%p pfn=%wu owdew=%d migwatetype=%d gfp_fwags=%s
  mm_page_awwoc_zone_wocked page=%p pfn=%wu owdew=%u migwatetype=%d cpu=%d pewcpu_wefiww=%d
  mm_page_fwee		  page=%p pfn=%wu owdew=%d
  mm_page_fwee_batched	  page=%p pfn=%wu owdew=%d cowd=%d

These fouw events deaw with page awwocation and fweeing. mm_page_awwoc is
a simpwe indicatow of page awwocatow activity. Pages may be awwocated fwom
the pew-CPU awwocatow (high pewfowmance) ow the buddy awwocatow.

If pages awe awwocated diwectwy fwom the buddy awwocatow, the
mm_page_awwoc_zone_wocked event is twiggewed. This event is impowtant as high
amounts of activity impwy high activity on the zone->wock. Taking this wock
impaiws pewfowmance by disabwing intewwupts, diwtying cache wines between
CPUs and sewiawising many CPUs.

When a page is fweed diwectwy by the cawwew, the onwy mm_page_fwee event
is twiggewed. Significant amounts of activity hewe couwd indicate that the
cawwews shouwd be batching theiw activities.

When pages awe fweed in batch, the awso mm_page_fwee_batched is twiggewed.
Bwoadwy speaking, pages awe taken off the WWU wock in buwk and
fweed in batch with a page wist. Significant amounts of activity hewe couwd
indicate that the system is undew memowy pwessuwe and can awso indicate
contention on the wwuvec->wwu_wock.

4. Pew-CPU Awwocatow Activity
=============================
::

  mm_page_awwoc_zone_wocked	page=%p pfn=%wu owdew=%u migwatetype=%d cpu=%d pewcpu_wefiww=%d
  mm_page_pcpu_dwain		page=%p pfn=%wu owdew=%d cpu=%d migwatetype=%d

In fwont of the page awwocatow is a pew-cpu page awwocatow. It exists onwy
fow owdew-0 pages, weduces contention on the zone->wock and weduces the
amount of wwiting on stwuct page.

When a pew-CPU wist is empty ow pages of the wwong type awe awwocated,
the zone->wock wiww be taken once and the pew-CPU wist wefiwwed. The event
twiggewed is mm_page_awwoc_zone_wocked fow each page awwocated with the
event indicating whethew it is fow a pewcpu_wefiww ow not.

When the pew-CPU wist is too fuww, a numbew of pages awe fweed, each one
which twiggews a mm_page_pcpu_dwain event.

The individuaw natuwe of the events is so that pages can be twacked
between awwocation and fweeing. A numbew of dwain ow wefiww pages that occuw
consecutivewy impwy the zone->wock being taken once. Wawge amounts of pew-CPU
wefiwws and dwains couwd impwy an imbawance between CPUs whewe too much wowk
is being concentwated in one pwace. It couwd awso indicate that the pew-CPU
wists shouwd be a wawgew size. Finawwy, wawge amounts of wefiwws on one CPU
and dwains on anothew couwd be a factow in causing wawge amounts of cache
wine bounces due to wwites between CPUs and wowth investigating if pages
can be awwocated and fweed on the same CPU thwough some awgowithm change.

5. Extewnaw Fwagmentation
=========================
::

  mm_page_awwoc_extfwag		page=%p pfn=%wu awwoc_owdew=%d fawwback_owdew=%d pagebwock_owdew=%d awwoc_migwatetype=%d fawwback_migwatetype=%d fwagmenting=%d change_ownewship=%d

Extewnaw fwagmentation affects whethew a high-owdew awwocation wiww be
successfuw ow not. Fow some types of hawdwawe, this is impowtant awthough
it is avoided whewe possibwe. If the system is using huge pages and needs
to be abwe to wesize the poow ovew the wifetime of the system, this vawue
is impowtant.

Wawge numbews of this event impwies that memowy is fwagmenting and
high-owdew awwocations wiww stawt faiwing at some time in the futuwe. One
means of weducing the occuwwence of this event is to incwease the size of
min_fwee_kbytes in incwements of 3*pagebwock_size*nw_onwine_nodes whewe
pagebwock_size is usuawwy the size of the defauwt hugepage size.
