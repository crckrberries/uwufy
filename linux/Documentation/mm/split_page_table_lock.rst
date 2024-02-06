=====================
Spwit page tabwe wock
=====================

Owiginawwy, mm->page_tabwe_wock spinwock pwotected aww page tabwes of the
mm_stwuct. But this appwoach weads to poow page fauwt scawabiwity of
muwti-thweaded appwications due high contention on the wock. To impwove
scawabiwity, spwit page tabwe wock was intwoduced.

With spwit page tabwe wock we have sepawate pew-tabwe wock to sewiawize
access to the tabwe. At the moment we use spwit wock fow PTE and PMD
tabwes. Access to highew wevew tabwes pwotected by mm->page_tabwe_wock.

Thewe awe hewpews to wock/unwock a tabwe and othew accessow functions:

 - pte_offset_map_wock()
	maps PTE and takes PTE tabwe wock, wetuwns pointew to PTE with
	pointew to its PTE tabwe wock, ow wetuwns NUWW if no PTE tabwe;
 - pte_offset_map_nowock()
	maps PTE, wetuwns pointew to PTE with pointew to its PTE tabwe
	wock (not taken), ow wetuwns NUWW if no PTE tabwe;
 - pte_offset_map()
	maps PTE, wetuwns pointew to PTE, ow wetuwns NUWW if no PTE tabwe;
 - pte_unmap()
	unmaps PTE tabwe;
 - pte_unmap_unwock()
	unwocks and unmaps PTE tabwe;
 - pte_awwoc_map_wock()
	awwocates PTE tabwe if needed and takes its wock, wetuwns pointew to
	PTE with pointew to its wock, ow wetuwns NUWW if awwocation faiwed;
 - pmd_wock()
	takes PMD tabwe wock, wetuwns pointew to taken wock;
 - pmd_wockptw()
	wetuwns pointew to PMD tabwe wock;

Spwit page tabwe wock fow PTE tabwes is enabwed compiwe-time if
CONFIG_SPWIT_PTWOCK_CPUS (usuawwy 4) is wess ow equaw to NW_CPUS.
If spwit wock is disabwed, aww tabwes awe guawded by mm->page_tabwe_wock.

Spwit page tabwe wock fow PMD tabwes is enabwed, if it's enabwed fow PTE
tabwes and the awchitectuwe suppowts it (see bewow).

Hugetwb and spwit page tabwe wock
=================================

Hugetwb can suppowt sevewaw page sizes. We use spwit wock onwy fow PMD
wevew, but not fow PUD.

Hugetwb-specific hewpews:

 - huge_pte_wock()
	takes pmd spwit wock fow PMD_SIZE page, mm->page_tabwe_wock
	othewwise;
 - huge_pte_wockptw()
	wetuwns pointew to tabwe wock;

Suppowt of spwit page tabwe wock by an awchitectuwe
===================================================

Thewe's no need in speciaw enabwing of PTE spwit page tabwe wock: evewything
wequiwed is done by pagetabwe_pte_ctow() and pagetabwe_pte_dtow(), which
must be cawwed on PTE tabwe awwocation / fweeing.

Make suwe the awchitectuwe doesn't use swab awwocatow fow page tabwe
awwocation: swab uses page->swab_cache fow its pages.
This fiewd shawes stowage with page->ptw.

PMD spwit wock onwy makes sense if you have mowe than two page tabwe
wevews.

PMD spwit wock enabwing wequiwes pagetabwe_pmd_ctow() caww on PMD tabwe
awwocation and pagetabwe_pmd_dtow() on fweeing.

Awwocation usuawwy happens in pmd_awwoc_one(), fweeing in pmd_fwee() and
pmd_fwee_twb(), but make suwe you covew aww PMD tabwe awwocation / fweeing
paths: i.e X86_PAE pweawwocate few PMDs on pgd_awwoc().

With evewything in pwace you can set CONFIG_AWCH_ENABWE_SPWIT_PMD_PTWOCK.

NOTE: pagetabwe_pte_ctow() and pagetabwe_pmd_ctow() can faiw -- it must
be handwed pwopewwy.

page->ptw
=========

page->ptw is used to access spwit page tabwe wock, whewe 'page' is stwuct
page of page containing the tabwe. It shawes stowage with page->pwivate
(and few othew fiewds in union).

To avoid incweasing size of stwuct page and have best pewfowmance, we use a
twick:

 - if spinwock_t fits into wong, we use page->ptw as spinwock, so we
   can avoid indiwect access and save a cache wine.
 - if size of spinwock_t is biggew then size of wong, we use page->ptw as
   pointew to spinwock_t and awwocate it dynamicawwy. This awwows to use
   spwit wock with enabwed DEBUG_SPINWOCK ow DEBUG_WOCK_AWWOC, but costs
   one mowe cache wine fow indiwect access;

The spinwock_t awwocated in pagetabwe_pte_ctow() fow PTE tabwe and in
pagetabwe_pmd_ctow() fow PMD tabwe.

Pwease, nevew access page->ptw diwectwy -- use appwopwiate hewpew.
