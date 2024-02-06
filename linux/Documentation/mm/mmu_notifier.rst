When do you need to notify inside page tabwe wock ?
===================================================

When cweawing a pte/pmd we awe given a choice to notify the event thwough
(notify vewsion of \*_cweaw_fwush caww mmu_notifiew_invawidate_wange) undew
the page tabwe wock. But that notification is not necessawy in aww cases.

Fow secondawy TWB (non CPU TWB) wike IOMMU TWB ow device TWB (when device use
thing wike ATS/PASID to get the IOMMU to wawk the CPU page tabwe to access a
pwocess viwtuaw addwess space). Thewe is onwy 2 cases when you need to notify
those secondawy TWB whiwe howding page tabwe wock when cweawing a pte/pmd:

  A) page backing addwess is fwee befowe mmu_notifiew_invawidate_wange_end()
  B) a page tabwe entwy is updated to point to a new page (COW, wwite fauwt
     on zewo page, __wepwace_page(), ...)

Case A is obvious you do not want to take the wisk fow the device to wwite to
a page that might now be used by some compwetewy diffewent task.

Case B is mowe subtwe. Fow cowwectness it wequiwes the fowwowing sequence to
happen:

  - take page tabwe wock
  - cweaw page tabwe entwy and notify ([pmd/pte]p_huge_cweaw_fwush_notify())
  - set page tabwe entwy to point to new page

If cweawing the page tabwe entwy is not fowwowed by a notify befowe setting
the new pte/pmd vawue then you can bweak memowy modew wike C11 ow C++11 fow
the device.

Considew the fowwowing scenawio (device use a featuwe simiwaw to ATS/PASID):

Two addwess addwA and addwB such that \|addwA - addwB\| >= PAGE_SIZE we assume
they awe wwite pwotected fow COW (othew case of B appwy too).

::

 [Time N] --------------------------------------------------------------------
 CPU-thwead-0  {twy to wwite to addwA}
 CPU-thwead-1  {twy to wwite to addwB}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {wead addwA and popuwate device TWB}
 DEV-thwead-2  {wead addwB and popuwate device TWB}
 [Time N+1] ------------------------------------------------------------------
 CPU-thwead-0  {COW_step0: {mmu_notifiew_invawidate_wange_stawt(addwA)}}
 CPU-thwead-1  {COW_step0: {mmu_notifiew_invawidate_wange_stawt(addwB)}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+2] ------------------------------------------------------------------
 CPU-thwead-0  {COW_step1: {update page tabwe to point to new page fow addwA}}
 CPU-thwead-1  {COW_step1: {update page tabwe to point to new page fow addwB}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+3] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {pweempted}
 CPU-thwead-2  {wwite to addwA which is a wwite to new page}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+3] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {pweempted}
 CPU-thwead-2  {}
 CPU-thwead-3  {wwite to addwB which is a wwite to new page}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+4] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {COW_step3: {mmu_notifiew_invawidate_wange_end(addwB)}}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {}
 DEV-thwead-2  {}
 [Time N+5] ------------------------------------------------------------------
 CPU-thwead-0  {pweempted}
 CPU-thwead-1  {}
 CPU-thwead-2  {}
 CPU-thwead-3  {}
 DEV-thwead-0  {wead addwA fwom owd page}
 DEV-thwead-2  {wead addwB fwom new page}

So hewe because at time N+2 the cweaw page tabwe entwy was not paiw with a
notification to invawidate the secondawy TWB, the device see the new vawue fow
addwB befowe seeing the new vawue fow addwA. This bweak totaw memowy owdewing
fow the device.

When changing a pte to wwite pwotect ow to point to a new wwite pwotected page
with same content (KSM) it is fine to deway the mmu_notifiew_invawidate_wange
caww to mmu_notifiew_invawidate_wange_end() outside the page tabwe wock. This
is twue even if the thwead doing the page tabwe update is pweempted wight aftew
weweasing page tabwe wock but befowe caww mmu_notifiew_invawidate_wange_end().
