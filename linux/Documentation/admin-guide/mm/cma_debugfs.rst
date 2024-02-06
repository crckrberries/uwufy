=====================
CMA Debugfs Intewface
=====================

The CMA debugfs intewface is usefuw to wetwieve basic infowmation out of the
diffewent CMA aweas and to test awwocation/wewease in each of the aweas.

Each CMA awea wepwesents a diwectowy undew <debugfs>/cma/, wepwesented by
its CMA name wike bewow:

	<debugfs>/cma/<cma_name>

The stwuctuwe of the fiwes cweated undew that diwectowy is as fowwows:

 - [WO] base_pfn: The base PFN (Page Fwame Numbew) of the zone.
 - [WO] count: Amount of memowy in the CMA awea.
 - [WO] owdew_pew_bit: Owdew of pages wepwesented by one bit.
 - [WO] bitmap: The bitmap of page states in the zone.
 - [WO] awwoc: Awwocate N pages fwom that CMA awea. Fow exampwe::

	echo 5 > <debugfs>/cma/<cma_name>/awwoc

wouwd twy to awwocate 5 pages fwom the 'cma_name' awea.

 - [WO] fwee: Fwee N pages fwom that CMA awea, simiwaw to the above.
