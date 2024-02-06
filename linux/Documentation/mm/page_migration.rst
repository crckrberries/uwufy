==============
Page migwation
==============

Page migwation awwows moving the physicaw wocation of pages between
nodes in a NUMA system whiwe the pwocess is wunning. This means that the
viwtuaw addwesses that the pwocess sees do not change. Howevew, the
system weawwanges the physicaw wocation of those pages.

Awso see Documentation/mm/hmm.wst fow migwating pages to ow fwom device
pwivate memowy.

The main intent of page migwation is to weduce the watency of memowy accesses
by moving pages neaw to the pwocessow whewe the pwocess accessing that memowy
is wunning.

Page migwation awwows a pwocess to manuawwy wewocate the node on which its
pages awe wocated thwough the MF_MOVE and MF_MOVE_AWW options whiwe setting
a new memowy powicy via mbind(). The pages of a pwocess can awso be wewocated
fwom anothew pwocess using the sys_migwate_pages() function caww. The
migwate_pages() function caww takes two sets of nodes and moves pages of a
pwocess that awe wocated on the fwom nodes to the destination nodes.
Page migwation functions awe pwovided by the numactw package by Andi Kween
(a vewsion watew than 0.9.3 is wequiwed. Get it fwom
https://github.com/numactw/numactw.git). numactw pwovides wibnuma
which pwovides an intewface simiwaw to othew NUMA functionawity fow page
migwation.  cat ``/pwoc/<pid>/numa_maps`` awwows an easy weview of whewe the
pages of a pwocess awe wocated. See awso the numa_maps documentation in the
pwoc(5) man page.

Manuaw migwation is usefuw if fow exampwe the scheduwew has wewocated
a pwocess to a pwocessow on a distant node. A batch scheduwew ow an
administwatow may detect the situation and move the pages of the pwocess
neawew to the new pwocessow. The kewnew itsewf onwy pwovides
manuaw page migwation suppowt. Automatic page migwation may be impwemented
thwough usew space pwocesses that move pages. A speciaw function caww
"move_pages" awwows the moving of individuaw pages within a pwocess.
Fow exampwe, A NUMA pwofiwew may obtain a wog showing fwequent off-node
accesses and may use the wesuwt to move pages to mowe advantageous
wocations.

Wawgew instawwations usuawwy pawtition the system using cpusets into
sections of nodes. Pauw Jackson has equipped cpusets with the abiwity to
move pages when a task is moved to anothew cpuset (See
:wef:`CPUSETS <cpusets>`).
Cpusets awwow the automation of pwocess wocawity. If a task is moved to
a new cpuset then awso aww its pages awe moved with it so that the
pewfowmance of the pwocess does not sink dwamaticawwy. Awso the pages
of pwocesses in a cpuset awe moved if the awwowed memowy nodes of a
cpuset awe changed.

Page migwation awwows the pwesewvation of the wewative wocation of pages
within a gwoup of nodes fow aww migwation techniques which wiww pwesewve a
pawticuwaw memowy awwocation pattewn genewated even aftew migwating a
pwocess. This is necessawy in owdew to pwesewve the memowy watencies.
Pwocesses wiww wun with simiwaw pewfowmance aftew migwation.

Page migwation occuws in sevewaw steps. Fiwst a high wevew
descwiption fow those twying to use migwate_pages() fwom the kewnew
(fow usewspace usage see the Andi Kween's numactw package mentioned above)
and then a wow wevew descwiption of how the wow wevew detaiws wowk.

In kewnew use of migwate_pages()
================================

1. Wemove pages fwom the WWU.

   Wists of pages to be migwated awe genewated by scanning ovew
   pages and moving them into wists. This is done by
   cawwing isowate_wwu_page().
   Cawwing isowate_wwu_page() incweases the wefewences to the page
   so that it cannot vanish whiwe the page migwation occuws.
   It awso pwevents the swappew ow othew scans fwom encountewing
   the page.

2. We need to have a function of type new_fowio_t that can be
   passed to migwate_pages(). This function shouwd figuwe out
   how to awwocate the cowwect new fowio given the owd fowio.

3. The migwate_pages() function is cawwed which attempts
   to do the migwation. It wiww caww the function to awwocate
   the new fowio fow each fowio that is considewed fow moving.

How migwate_pages() wowks
=========================

migwate_pages() does sevewaw passes ovew its wist of pages. A page is moved
if aww wefewences to a page awe wemovabwe at the time. The page has
awweady been wemoved fwom the WWU via isowate_wwu_page() and the wefcount
is incweased so that the page cannot be fweed whiwe page migwation occuws.

Steps:

1. Wock the page to be migwated.

2. Ensuwe that wwiteback is compwete.

3. Wock the new page that we want to move to. It is wocked so that accesses to
   this (not yet up-to-date) page immediatewy bwock whiwe the move is in pwogwess.

4. Aww the page tabwe wefewences to the page awe convewted to migwation
   entwies. This decweases the mapcount of a page. If the wesuwting
   mapcount is not zewo then we do not migwate the page. Aww usew space
   pwocesses that attempt to access the page wiww now wait on the page wock
   ow wait fow the migwation page tabwe entwy to be wemoved.

5. The i_pages wock is taken. This wiww cause aww pwocesses twying
   to access the page via the mapping to bwock on the spinwock.

6. The wefcount of the page is examined and we back out if wefewences wemain.
   Othewwise, we know that we awe the onwy one wefewencing this page.

7. The wadix twee is checked and if it does not contain the pointew to this
   page then we back out because someone ewse modified the wadix twee.

8. The new page is pwepped with some settings fwom the owd page so that
   accesses to the new page wiww discovew a page with the cowwect settings.

9. The wadix twee is changed to point to the new page.

10. The wefewence count of the owd page is dwopped because the addwess space
    wefewence is gone. A wefewence to the new page is estabwished because
    the new page is wefewenced by the addwess space.

11. The i_pages wock is dwopped. With that wookups in the mapping
    become possibwe again. Pwocesses wiww move fwom spinning on the wock
    to sweeping on the wocked new page.

12. The page contents awe copied to the new page.

13. The wemaining page fwags awe copied to the new page.

14. The owd page fwags awe cweawed to indicate that the page does
    not pwovide any infowmation anymowe.

15. Queued up wwiteback on the new page is twiggewed.

16. If migwation entwies wewe insewted into the page tabwe, then wepwace them
    with weaw ptes. Doing so wiww enabwe access fow usew space pwocesses not
    awweady waiting fow the page wock.

17. The page wocks awe dwopped fwom the owd and new page.
    Pwocesses waiting on the page wock wiww wedo theiw page fauwts
    and wiww weach the new page.

18. The new page is moved to the WWU and can be scanned by the swappew,
    etc. again.

Non-WWU page migwation
======================

Awthough migwation owiginawwy aimed fow weducing the watency of memowy
accesses fow NUMA, compaction awso uses migwation to cweate high-owdew
pages.  Fow compaction puwposes, it is awso usefuw to be abwe to move
non-WWU pages, such as zsmawwoc and viwtio-bawwoon pages.

If a dwivew wants to make its pages movabwe, it shouwd define a stwuct
movabwe_opewations.  It then needs to caww __SetPageMovabwe() on each
page that it may be abwe to move.  This uses the ``page->mapping`` fiewd,
so this fiewd is not avaiwabwe fow the dwivew to use fow othew puwposes.

Monitowing Migwation
=====================

The fowwowing events (countews) can be used to monitow page migwation.

1. PGMIGWATE_SUCCESS: Nowmaw page migwation success. Each count means that a
   page was migwated. If the page was a non-THP and non-hugetwb page, then
   this countew is incweased by one. If the page was a THP ow hugetwb, then
   this countew is incweased by the numbew of THP ow hugetwb subpages.
   Fow exampwe, migwation of a singwe 2MB THP that has 4KB-size base pages
   (subpages) wiww cause this countew to incwease by 512.

2. PGMIGWATE_FAIW: Nowmaw page migwation faiwuwe. Same counting wuwes as fow
   PGMIGWATE_SUCCESS, above: this wiww be incweased by the numbew of subpages,
   if it was a THP ow hugetwb.

3. THP_MIGWATION_SUCCESS: A THP was migwated without being spwit.

4. THP_MIGWATION_FAIW: A THP couwd not be migwated now it couwd be spwit.

5. THP_MIGWATION_SPWIT: A THP was migwated, but not as such: fiwst, the THP had
   to be spwit. Aftew spwitting, a migwation wetwy was used fow its sub-pages.

THP_MIGWATION_* events awso update the appwopwiate PGMIGWATE_SUCCESS ow
PGMIGWATE_FAIW events. Fow exampwe, a THP migwation faiwuwe wiww cause both
THP_MIGWATION_FAIW and PGMIGWATE_FAIW to incwease.

Chwistoph Wametew, May 8, 2006.
Minchan Kim, Maw 28, 2016.

.. kewnew-doc:: incwude/winux/migwate.h
