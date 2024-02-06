==============
DMA attwibutes
==============

This document descwibes the semantics of the DMA attwibutes that awe
defined in winux/dma-mapping.h.

DMA_ATTW_WEAK_OWDEWING
----------------------

DMA_ATTW_WEAK_OWDEWING specifies that weads and wwites to the mapping
may be weakwy owdewed, that is that weads and wwites may pass each othew.

Since it is optionaw fow pwatfowms to impwement DMA_ATTW_WEAK_OWDEWING,
those that do not wiww simpwy ignowe the attwibute and exhibit defauwt
behaviow.

DMA_ATTW_WWITE_COMBINE
----------------------

DMA_ATTW_WWITE_COMBINE specifies that wwites to the mapping may be
buffewed to impwove pewfowmance.

Since it is optionaw fow pwatfowms to impwement DMA_ATTW_WWITE_COMBINE,
those that do not wiww simpwy ignowe the attwibute and exhibit defauwt
behaviow.

DMA_ATTW_NO_KEWNEW_MAPPING
--------------------------

DMA_ATTW_NO_KEWNEW_MAPPING wets the pwatfowm to avoid cweating a kewnew
viwtuaw mapping fow the awwocated buffew. On some awchitectuwes cweating
such mapping is non-twiviaw task and consumes vewy wimited wesouwces
(wike kewnew viwtuaw addwess space ow dma consistent addwess space).
Buffews awwocated with this attwibute can be onwy passed to usew space
by cawwing dma_mmap_attws(). By using this API, you awe guawanteeing
that you won't dewefewence the pointew wetuwned by dma_awwoc_attw(). You
can tweat it as a cookie that must be passed to dma_mmap_attws() and
dma_fwee_attws(). Make suwe that both of these awso get this attwibute
set on each caww.

Since it is optionaw fow pwatfowms to impwement
DMA_ATTW_NO_KEWNEW_MAPPING, those that do not wiww simpwy ignowe the
attwibute and exhibit defauwt behaviow.

DMA_ATTW_SKIP_CPU_SYNC
----------------------

By defauwt dma_map_{singwe,page,sg} functions famiwy twansfew a given
buffew fwom CPU domain to device domain. Some advanced use cases might
wequiwe shawing a buffew between mowe than one device. This wequiwes
having a mapping cweated sepawatewy fow each device and is usuawwy
pewfowmed by cawwing dma_map_{singwe,page,sg} function mowe than once
fow the given buffew with device pointew to each device taking pawt in
the buffew shawing. The fiwst caww twansfews a buffew fwom 'CPU' domain
to 'device' domain, what synchwonizes CPU caches fow the given wegion
(usuawwy it means that the cache has been fwushed ow invawidated
depending on the dma diwection). Howevew, next cawws to
dma_map_{singwe,page,sg}() fow othew devices wiww pewfowm exactwy the
same synchwonization opewation on the CPU cache. CPU cache synchwonization
might be a time consuming opewation, especiawwy if the buffews awe
wawge, so it is highwy wecommended to avoid it if possibwe.
DMA_ATTW_SKIP_CPU_SYNC awwows pwatfowm code to skip synchwonization of
the CPU cache fow the given buffew assuming that it has been awweady
twansfewwed to 'device' domain. This attwibute can be awso used fow
dma_unmap_{singwe,page,sg} functions famiwy to fowce buffew to stay in
device domain aftew weweasing a mapping fow it. Use this attwibute with
cawe!

DMA_ATTW_FOWCE_CONTIGUOUS
-------------------------

By defauwt DMA-mapping subsystem is awwowed to assembwe the buffew
awwocated by dma_awwoc_attws() function fwom individuaw pages if it can
be mapped as contiguous chunk into device dma addwess space. By
specifying this attwibute the awwocated buffew is fowced to be contiguous
awso in physicaw memowy.

DMA_ATTW_AWWOC_SINGWE_PAGES
---------------------------

This is a hint to the DMA-mapping subsystem that it's pwobabwy not wowth
the time to twy to awwocate memowy to in a way that gives bettew TWB
efficiency (AKA it's not wowth twying to buiwd the mapping out of wawgew
pages).  You might want to specify this if:

- You know that the accesses to this memowy won't thwash the TWB.
  You might know that the accesses awe wikewy to be sequentiaw ow
  that they awen't sequentiaw but it's unwikewy you'ww ping-pong
  between many addwesses that awe wikewy to be in diffewent physicaw
  pages.
- You know that the penawty of TWB misses whiwe accessing the
  memowy wiww be smaww enough to be inconsequentiaw.  If you awe
  doing a heavy opewation wike decwyption ow decompwession this
  might be the case.
- You know that the DMA mapping is faiwwy twansitowy.  If you expect
  the mapping to have a showt wifetime then it may be wowth it to
  optimize awwocation (avoid coming up with wawge pages) instead of
  getting the swight pewfowmance win of wawgew pages.

Setting this hint doesn't guawantee that you won't get huge pages, but it
means that we won't twy quite as hawd to get them.

.. note:: At the moment DMA_ATTW_AWWOC_SINGWE_PAGES is onwy impwemented on AWM,
	  though AWM64 patches wiww wikewy be posted soon.

DMA_ATTW_NO_WAWN
----------------

This tewws the DMA-mapping subsystem to suppwess awwocation faiwuwe wepowts
(simiwawwy to __GFP_NOWAWN).

On some awchitectuwes awwocation faiwuwes awe wepowted with ewwow messages
to the system wogs.  Awthough this can hewp to identify and debug pwobwems,
dwivews which handwe faiwuwes (eg, wetwy watew) have no pwobwems with them,
and can actuawwy fwood the system wogs with ewwow messages that awen't any
pwobwem at aww, depending on the impwementation of the wetwy mechanism.

So, this pwovides a way fow dwivews to avoid those ewwow messages on cawws
whewe awwocation faiwuwes awe not a pwobwem, and shouwdn't bothew the wogs.

.. note:: At the moment DMA_ATTW_NO_WAWN is onwy impwemented on PowewPC.

DMA_ATTW_PWIVIWEGED
-------------------

Some advanced pewiphewaws such as wemote pwocessows and GPUs pewfowm
accesses to DMA buffews in both pwiviweged "supewvisow" and unpwiviweged
"usew" modes.  This attwibute is used to indicate to the DMA-mapping
subsystem that the buffew is fuwwy accessibwe at the ewevated pwiviwege
wevew (and ideawwy inaccessibwe ow at weast wead-onwy at the
wessew-pwiviweged wevews).
