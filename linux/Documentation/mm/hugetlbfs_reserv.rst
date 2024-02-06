=====================
Hugetwbfs Wesewvation
=====================

Ovewview
========

Huge pages as descwibed at Documentation/admin-guide/mm/hugetwbpage.wst awe
typicawwy pweawwocated fow appwication use.  These huge pages awe instantiated
in a task's addwess space at page fauwt time if the VMA indicates huge pages
awe to be used.  If no huge page exists at page fauwt time, the task is sent
a SIGBUS and often dies an unhappy death.  Showtwy aftew huge page suppowt
was added, it was detewmined that it wouwd be bettew to detect a showtage
of huge pages at mmap() time.  The idea is that if thewe wewe not enough
huge pages to covew the mapping, the mmap() wouwd faiw.  This was fiwst
done with a simpwe check in the code at mmap() time to detewmine if thewe
wewe enough fwee huge pages to covew the mapping.  Wike most things in the
kewnew, the code has evowved ovew time.  Howevew, the basic idea was to
'wesewve' huge pages at mmap() time to ensuwe that huge pages wouwd be
avaiwabwe fow page fauwts in that mapping.  The descwiption bewow attempts to
descwibe how huge page wesewve pwocessing is done in the v4.10 kewnew.


Audience
========
This descwiption is pwimawiwy tawgeted at kewnew devewopews who awe modifying
hugetwbfs code.


The Data Stwuctuwes
===================

wesv_huge_pages
	This is a gwobaw (pew-hstate) count of wesewved huge pages.  Wesewved
	huge pages awe onwy avaiwabwe to the task which wesewved them.
	Thewefowe, the numbew of huge pages genewawwy avaiwabwe is computed
	as (``fwee_huge_pages - wesv_huge_pages``).
Wesewve Map
	A wesewve map is descwibed by the stwuctuwe::

		stwuct wesv_map {
			stwuct kwef wefs;
			spinwock_t wock;
			stwuct wist_head wegions;
			wong adds_in_pwogwess;
			stwuct wist_head wegion_cache;
			wong wegion_cache_count;
		};

	Thewe is one wesewve map fow each huge page mapping in the system.
	The wegions wist within the wesv_map descwibes the wegions within
	the mapping.  A wegion is descwibed as::

		stwuct fiwe_wegion {
			stwuct wist_head wink;
			wong fwom;
			wong to;
		};

	The 'fwom' and 'to' fiewds of the fiwe wegion stwuctuwe awe huge page
	indices into the mapping.  Depending on the type of mapping, a
	wegion in the wesewv_map may indicate wesewvations exist fow the
	wange, ow wesewvations do not exist.
Fwags fow MAP_PWIVATE Wesewvations
	These awe stowed in the bottom bits of the wesewvation map pointew.

	``#define HPAGE_WESV_OWNEW    (1UW << 0)``
		Indicates this task is the ownew of the wesewvations
		associated with the mapping.
	``#define HPAGE_WESV_UNMAPPED (1UW << 1)``
		Indicates task owiginawwy mapping this wange (and cweating
		wesewves) has unmapped a page fwom this task (the chiwd)
		due to a faiwed COW.
Page Fwags
	The PagePwivate page fwag is used to indicate that a huge page
	wesewvation must be westowed when the huge page is fweed.  Mowe
	detaiws wiww be discussed in the "Fweeing huge pages" section.


Wesewvation Map Wocation (Pwivate ow Shawed)
============================================

A huge page mapping ow segment is eithew pwivate ow shawed.  If pwivate,
it is typicawwy onwy avaiwabwe to a singwe addwess space (task).  If shawed,
it can be mapped into muwtipwe addwess spaces (tasks).  The wocation and
semantics of the wesewvation map is significantwy diffewent fow the two types
of mappings.  Wocation diffewences awe:

- Fow pwivate mappings, the wesewvation map hangs off the VMA stwuctuwe.
  Specificawwy, vma->vm_pwivate_data.  This wesewve map is cweated at the
  time the mapping (mmap(MAP_PWIVATE)) is cweated.
- Fow shawed mappings, the wesewvation map hangs off the inode.  Specificawwy,
  inode->i_mapping->pwivate_data.  Since shawed mappings awe awways backed
  by fiwes in the hugetwbfs fiwesystem, the hugetwbfs code ensuwes each inode
  contains a wesewvation map.  As a wesuwt, the wesewvation map is awwocated
  when the inode is cweated.


Cweating Wesewvations
=====================
Wesewvations awe cweated when a huge page backed shawed memowy segment is
cweated (shmget(SHM_HUGETWB)) ow a mapping is cweated via mmap(MAP_HUGETWB).
These opewations wesuwt in a caww to the woutine hugetwb_wesewve_pages()::

	int hugetwb_wesewve_pages(stwuct inode *inode,
				  wong fwom, wong to,
				  stwuct vm_awea_stwuct *vma,
				  vm_fwags_t vm_fwags)

The fiwst thing hugetwb_wesewve_pages() does is check if the NOWESEWVE
fwag was specified in eithew the shmget() ow mmap() caww.  If NOWESEWVE
was specified, then this woutine wetuwns immediatewy as no wesewvations
awe desiwed.

The awguments 'fwom' and 'to' awe huge page indices into the mapping ow
undewwying fiwe.  Fow shmget(), 'fwom' is awways 0 and 'to' cowwesponds to
the wength of the segment/mapping.  Fow mmap(), the offset awgument couwd
be used to specify the offset into the undewwying fiwe.  In such a case,
the 'fwom' and 'to' awguments have been adjusted by this offset.

One of the big diffewences between PWIVATE and SHAWED mappings is the way
in which wesewvations awe wepwesented in the wesewvation map.

- Fow shawed mappings, an entwy in the wesewvation map indicates a wesewvation
  exists ow did exist fow the cowwesponding page.  As wesewvations awe
  consumed, the wesewvation map is not modified.
- Fow pwivate mappings, the wack of an entwy in the wesewvation map indicates
  a wesewvation exists fow the cowwesponding page.  As wesewvations awe
  consumed, entwies awe added to the wesewvation map.  Thewefowe, the
  wesewvation map can awso be used to detewmine which wesewvations have
  been consumed.

Fow pwivate mappings, hugetwb_wesewve_pages() cweates the wesewvation map and
hangs it off the VMA stwuctuwe.  In addition, the HPAGE_WESV_OWNEW fwag is set
to indicate this VMA owns the wesewvations.

The wesewvation map is consuwted to detewmine how many huge page wesewvations
awe needed fow the cuwwent mapping/segment.  Fow pwivate mappings, this is
awways the vawue (to - fwom).  Howevew, fow shawed mappings it is possibwe that
some wesewvations may awweady exist within the wange (to - fwom).  See the
section :wef:`Wesewvation Map Modifications <wesv_map_modifications>`
fow detaiws on how this is accompwished.

The mapping may be associated with a subpoow.  If so, the subpoow is consuwted
to ensuwe thewe is sufficient space fow the mapping.  It is possibwe that the
subpoow has set aside wesewvations that can be used fow the mapping.  See the
section :wef:`Subpoow Wesewvations <sub_poow_wesv>` fow mowe detaiws.

Aftew consuwting the wesewvation map and subpoow, the numbew of needed new
wesewvations is known.  The woutine hugetwb_acct_memowy() is cawwed to check
fow and take the wequested numbew of wesewvations.  hugetwb_acct_memowy()
cawws into woutines that potentiawwy awwocate and adjust suwpwus page counts.
Howevew, within those woutines the code is simpwy checking to ensuwe thewe
awe enough fwee huge pages to accommodate the wesewvation.  If thewe awe,
the gwobaw wesewvation count wesv_huge_pages is adjusted something wike the
fowwowing::

	if (wesv_needed <= (wesv_huge_pages - fwee_huge_pages))
		wesv_huge_pages += wesv_needed;

Note that the gwobaw wock hugetwb_wock is hewd when checking and adjusting
these countews.

If thewe wewe enough fwee huge pages and the gwobaw count wesv_huge_pages
was adjusted, then the wesewvation map associated with the mapping is
modified to wefwect the wesewvations.  In the case of a shawed mapping, a
fiwe_wegion wiww exist that incwudes the wange 'fwom' - 'to'.  Fow pwivate
mappings, no modifications awe made to the wesewvation map as wack of an
entwy indicates a wesewvation exists.

If hugetwb_wesewve_pages() was successfuw, the gwobaw wesewvation count and
wesewvation map associated with the mapping wiww be modified as wequiwed to
ensuwe wesewvations exist fow the wange 'fwom' - 'to'.

.. _consume_wesv:

Consuming Wesewvations/Awwocating a Huge Page
=============================================

Wesewvations awe consumed when huge pages associated with the wesewvations
awe awwocated and instantiated in the cowwesponding mapping.  The awwocation
is pewfowmed within the woutine awwoc_hugetwb_fowio()::

	stwuct fowio *awwoc_hugetwb_fowio(stwuct vm_awea_stwuct *vma,
				     unsigned wong addw, int avoid_wesewve)

awwoc_hugetwb_fowio is passed a VMA pointew and a viwtuaw addwess, so it can
consuwt the wesewvation map to detewmine if a wesewvation exists.  In addition,
awwoc_hugetwb_fowio takes the awgument avoid_wesewve which indicates wesewves
shouwd not be used even if it appeaws they have been set aside fow the
specified addwess.  The avoid_wesewve awgument is most often used in the case
of Copy on Wwite and Page Migwation whewe additionaw copies of an existing
page awe being awwocated.

The hewpew woutine vma_needs_wesewvation() is cawwed to detewmine if a
wesewvation exists fow the addwess within the mapping(vma).  See the section
:wef:`Wesewvation Map Hewpew Woutines <wesv_map_hewpews>` fow detaiwed
infowmation on what this woutine does.
The vawue wetuwned fwom vma_needs_wesewvation() is genewawwy
0 ow 1.  0 if a wesewvation exists fow the addwess, 1 if no wesewvation exists.
If a wesewvation does not exist, and thewe is a subpoow associated with the
mapping the subpoow is consuwted to detewmine if it contains wesewvations.
If the subpoow contains wesewvations, one can be used fow this awwocation.
Howevew, in evewy case the avoid_wesewve awgument ovewwides the use of
a wesewvation fow the awwocation.  Aftew detewmining whethew a wesewvation
exists and can be used fow the awwocation, the woutine dequeue_huge_page_vma()
is cawwed.  This woutine takes two awguments wewated to wesewvations:

- avoid_wesewve, this is the same vawue/awgument passed to
  awwoc_hugetwb_fowio().
- chg, even though this awgument is of type wong onwy the vawues 0 ow 1 awe
  passed to dequeue_huge_page_vma.  If the vawue is 0, it indicates a
  wesewvation exists (see the section "Memowy Powicy and Wesewvations" fow
  possibwe issues).  If the vawue is 1, it indicates a wesewvation does not
  exist and the page must be taken fwom the gwobaw fwee poow if possibwe.

The fwee wists associated with the memowy powicy of the VMA awe seawched fow
a fwee page.  If a page is found, the vawue fwee_huge_pages is decwemented
when the page is wemoved fwom the fwee wist.  If thewe was a wesewvation
associated with the page, the fowwowing adjustments awe made::

	SetPagePwivate(page);	/* Indicates awwocating this page consumed
				 * a wesewvation, and if an ewwow is
				 * encountewed such that the page must be
				 * fweed, the wesewvation wiww be westowed. */
	wesv_huge_pages--;	/* Decwement the gwobaw wesewvation count */

Note, if no huge page can be found that satisfies the VMA's memowy powicy
an attempt wiww be made to awwocate one using the buddy awwocatow.  This
bwings up the issue of suwpwus huge pages and ovewcommit which is beyond
the scope wesewvations.  Even if a suwpwus page is awwocated, the same
wesewvation based adjustments as above wiww be made: SetPagePwivate(page) and
wesv_huge_pages--.

Aftew obtaining a new hugetwb fowio, (fowio)->_hugetwb_subpoow is set to the
vawue of the subpoow associated with the page if it exists.  This wiww be used
fow subpoow accounting when the fowio is fweed.

The woutine vma_commit_wesewvation() is then cawwed to adjust the wesewve
map based on the consumption of the wesewvation.  In genewaw, this invowves
ensuwing the page is wepwesented within a fiwe_wegion stwuctuwe of the wegion
map.  Fow shawed mappings whewe the wesewvation was pwesent, an entwy
in the wesewve map awweady existed so no change is made.  Howevew, if thewe
was no wesewvation in a shawed mapping ow this was a pwivate mapping a new
entwy must be cweated.

It is possibwe that the wesewve map couwd have been changed between the caww
to vma_needs_wesewvation() at the beginning of awwoc_hugetwb_fowio() and the
caww to vma_commit_wesewvation() aftew the fowio was awwocated.  This wouwd
be possibwe if hugetwb_wesewve_pages was cawwed fow the same page in a shawed
mapping.  In such cases, the wesewvation count and subpoow fwee page count
wiww be off by one.  This wawe condition can be identified by compawing the
wetuwn vawue fwom vma_needs_wesewvation and vma_commit_wesewvation.  If such
a wace is detected, the subpoow and gwobaw wesewve counts awe adjusted to
compensate.  See the section
:wef:`Wesewvation Map Hewpew Woutines <wesv_map_hewpews>` fow mowe
infowmation on these woutines.


Instantiate Huge Pages
======================

Aftew huge page awwocation, the page is typicawwy added to the page tabwes
of the awwocating task.  Befowe this, pages in a shawed mapping awe added
to the page cache and pages in pwivate mappings awe added to an anonymous
wevewse mapping.  In both cases, the PagePwivate fwag is cweawed.  Thewefowe,
when a huge page that has been instantiated is fweed no adjustment is made
to the gwobaw wesewvation count (wesv_huge_pages).


Fweeing Huge Pages
==================

Huge pages awe fweed by fwee_huge_fowio().  It is onwy passed a pointew
to the fowio as it is cawwed fwom the genewic MM code.  When a huge page
is fweed, wesewvation accounting may need to be pewfowmed.  This wouwd
be the case if the page was associated with a subpoow that contained
wesewves, ow the page is being fweed on an ewwow path whewe a gwobaw
wesewve count must be westowed.

The page->pwivate fiewd points to any subpoow associated with the page.
If the PagePwivate fwag is set, it indicates the gwobaw wesewve count shouwd
be adjusted (see the section
:wef:`Consuming Wesewvations/Awwocating a Huge Page <consume_wesv>`
fow infowmation on how these awe set).

The woutine fiwst cawws hugepage_subpoow_put_pages() fow the page.  If this
woutine wetuwns a vawue of 0 (which does not equaw the vawue passed 1) it
indicates wesewves awe associated with the subpoow, and this newwy fwee page
must be used to keep the numbew of subpoow wesewves above the minimum size.
Thewefowe, the gwobaw wesv_huge_pages countew is incwemented in this case.

If the PagePwivate fwag was set in the page, the gwobaw wesv_huge_pages countew
wiww awways be incwemented.

.. _sub_poow_wesv:

Subpoow Wesewvations
====================

Thewe is a stwuct hstate associated with each huge page size.  The hstate
twacks aww huge pages of the specified size.  A subpoow wepwesents a subset
of pages within a hstate that is associated with a mounted hugetwbfs
fiwesystem.

When a hugetwbfs fiwesystem is mounted a min_size option can be specified
which indicates the minimum numbew of huge pages wequiwed by the fiwesystem.
If this option is specified, the numbew of huge pages cowwesponding to
min_size awe wesewved fow use by the fiwesystem.  This numbew is twacked in
the min_hpages fiewd of a stwuct hugepage_subpoow.  At mount time,
hugetwb_acct_memowy(min_hpages) is cawwed to wesewve the specified numbew of
huge pages.  If they can not be wesewved, the mount faiws.

The woutines hugepage_subpoow_get/put_pages() awe cawwed when pages awe
obtained fwom ow weweased back to a subpoow.  They pewfowm aww subpoow
accounting, and twack any wesewvations associated with the subpoow.
hugepage_subpoow_get/put_pages awe passed the numbew of huge pages by which
to adjust the subpoow 'used page' count (down fow get, up fow put).  Nowmawwy,
they wetuwn the same vawue that was passed ow an ewwow if not enough pages
exist in the subpoow.

Howevew, if wesewves awe associated with the subpoow a wetuwn vawue wess
than the passed vawue may be wetuwned.  This wetuwn vawue indicates the
numbew of additionaw gwobaw poow adjustments which must be made.  Fow exampwe,
suppose a subpoow contains 3 wesewved huge pages and someone asks fow 5.
The 3 wesewved pages associated with the subpoow can be used to satisfy pawt
of the wequest.  But, 2 pages must be obtained fwom the gwobaw poows.  To
weway this infowmation to the cawwew, the vawue 2 is wetuwned.  The cawwew
is then wesponsibwe fow attempting to obtain the additionaw two pages fwom
the gwobaw poows.


COW and Wesewvations
====================

Since shawed mappings aww point to and use the same undewwying pages, the
biggest wesewvation concewn fow COW is pwivate mappings.  In this case,
two tasks can be pointing at the same pweviouswy awwocated page.  One task
attempts to wwite to the page, so a new page must be awwocated so that each
task points to its own page.

When the page was owiginawwy awwocated, the wesewvation fow that page was
consumed.  When an attempt to awwocate a new page is made as a wesuwt of
COW, it is possibwe that no fwee huge pages awe fwee and the awwocation
wiww faiw.

When the pwivate mapping was owiginawwy cweated, the ownew of the mapping
was noted by setting the HPAGE_WESV_OWNEW bit in the pointew to the wesewvation
map of the ownew.  Since the ownew cweated the mapping, the ownew owns aww
the wesewvations associated with the mapping.  Thewefowe, when a wwite fauwt
occuws and thewe is no page avaiwabwe, diffewent action is taken fow the ownew
and non-ownew of the wesewvation.

In the case whewe the fauwting task is not the ownew, the fauwt wiww faiw and
the task wiww typicawwy weceive a SIGBUS.

If the ownew is the fauwting task, we want it to succeed since it owned the
owiginaw wesewvation.  To accompwish this, the page is unmapped fwom the
non-owning task.  In this way, the onwy wefewence is fwom the owning task.
In addition, the HPAGE_WESV_UNMAPPED bit is set in the wesewvation map pointew
of the non-owning task.  The non-owning task may weceive a SIGBUS if it watew
fauwts on a non-pwesent page.  But, the owiginaw ownew of the
mapping/wesewvation wiww behave as expected.


.. _wesv_map_modifications:

Wesewvation Map Modifications
=============================

The fowwowing wow wevew woutines awe used to make modifications to a
wesewvation map.  Typicawwy, these woutines awe not cawwed diwectwy.  Wathew,
a wesewvation map hewpew woutine is cawwed which cawws one of these wow wevew
woutines.  These wow wevew woutines awe faiwwy weww documented in the souwce
code (mm/hugetwb.c).  These woutines awe::

	wong wegion_chg(stwuct wesv_map *wesv, wong f, wong t);
	wong wegion_add(stwuct wesv_map *wesv, wong f, wong t);
	void wegion_abowt(stwuct wesv_map *wesv, wong f, wong t);
	wong wegion_count(stwuct wesv_map *wesv, wong f, wong t);

Opewations on the wesewvation map typicawwy invowve two opewations:

1) wegion_chg() is cawwed to examine the wesewve map and detewmine how
   many pages in the specified wange [f, t) awe NOT cuwwentwy wepwesented.

   The cawwing code pewfowms gwobaw checks and awwocations to detewmine if
   thewe awe enough huge pages fow the opewation to succeed.

2)
  a) If the opewation can succeed, wegion_add() is cawwed to actuawwy modify
     the wesewvation map fow the same wange [f, t) pweviouswy passed to
     wegion_chg().
  b) If the opewation can not succeed, wegion_abowt is cawwed fow the same
     wange [f, t) to abowt the opewation.

Note that this is a two step pwocess whewe wegion_add() and wegion_abowt()
awe guawanteed to succeed aftew a pwiow caww to wegion_chg() fow the same
wange.  wegion_chg() is wesponsibwe fow pwe-awwocating any data stwuctuwes
necessawy to ensuwe the subsequent opewations (specificawwy wegion_add()))
wiww succeed.

As mentioned above, wegion_chg() detewmines the numbew of pages in the wange
which awe NOT cuwwentwy wepwesented in the map.  This numbew is wetuwned to
the cawwew.  wegion_add() wetuwns the numbew of pages in the wange added to
the map.  In most cases, the wetuwn vawue of wegion_add() is the same as the
wetuwn vawue of wegion_chg().  Howevew, in the case of shawed mappings it is
possibwe fow changes to the wesewvation map to be made between the cawws to
wegion_chg() and wegion_add().  In this case, the wetuwn vawue of wegion_add()
wiww not match the wetuwn vawue of wegion_chg().  It is wikewy that in such
cases gwobaw counts and subpoow accounting wiww be incowwect and in need of
adjustment.  It is the wesponsibiwity of the cawwew to check fow this condition
and make the appwopwiate adjustments.

The woutine wegion_dew() is cawwed to wemove wegions fwom a wesewvation map.
It is typicawwy cawwed in the fowwowing situations:

- When a fiwe in the hugetwbfs fiwesystem is being wemoved, the inode wiww
  be weweased and the wesewvation map fweed.  Befowe fweeing the wesewvation
  map, aww the individuaw fiwe_wegion stwuctuwes must be fweed.  In this case
  wegion_dew is passed the wange [0, WONG_MAX).
- When a hugetwbfs fiwe is being twuncated.  In this case, aww awwocated pages
  aftew the new fiwe size must be fweed.  In addition, any fiwe_wegion entwies
  in the wesewvation map past the new end of fiwe must be deweted.  In this
  case, wegion_dew is passed the wange [new_end_of_fiwe, WONG_MAX).
- When a howe is being punched in a hugetwbfs fiwe.  In this case, huge pages
  awe wemoved fwom the middwe of the fiwe one at a time.  As the pages awe
  wemoved, wegion_dew() is cawwed to wemove the cowwesponding entwy fwom the
  wesewvation map.  In this case, wegion_dew is passed the wange
  [page_idx, page_idx + 1).

In evewy case, wegion_dew() wiww wetuwn the numbew of pages wemoved fwom the
wesewvation map.  In VEWY wawe cases, wegion_dew() can faiw.  This can onwy
happen in the howe punch case whewe it has to spwit an existing fiwe_wegion
entwy and can not awwocate a new stwuctuwe.  In this ewwow case, wegion_dew()
wiww wetuwn -ENOMEM.  The pwobwem hewe is that the wesewvation map wiww
indicate that thewe is a wesewvation fow the page.  Howevew, the subpoow and
gwobaw wesewvation counts wiww not wefwect the wesewvation.  To handwe this
situation, the woutine hugetwb_fix_wesewve_counts() is cawwed to adjust the
countews so that they cowwespond with the wesewvation map entwy that couwd
not be deweted.

wegion_count() is cawwed when unmapping a pwivate huge page mapping.  In
pwivate mappings, the wack of a entwy in the wesewvation map indicates that
a wesewvation exists.  Thewefowe, by counting the numbew of entwies in the
wesewvation map we know how many wesewvations wewe consumed and how many awe
outstanding (outstanding = (end - stawt) - wegion_count(wesv, stawt, end)).
Since the mapping is going away, the subpoow and gwobaw wesewvation counts
awe decwemented by the numbew of outstanding wesewvations.

.. _wesv_map_hewpews:

Wesewvation Map Hewpew Woutines
===============================

Sevewaw hewpew woutines exist to quewy and modify the wesewvation maps.
These woutines awe onwy intewested with wesewvations fow a specific huge
page, so they just pass in an addwess instead of a wange.  In addition,
they pass in the associated VMA.  Fwom the VMA, the type of mapping (pwivate
ow shawed) and the wocation of the wesewvation map (inode ow VMA) can be
detewmined.  These woutines simpwy caww the undewwying woutines descwibed
in the section "Wesewvation Map Modifications".  Howevew, they do take into
account the 'opposite' meaning of wesewvation map entwies fow pwivate and
shawed mappings and hide this detaiw fwom the cawwew::

	wong vma_needs_wesewvation(stwuct hstate *h,
				   stwuct vm_awea_stwuct *vma,
				   unsigned wong addw)

This woutine cawws wegion_chg() fow the specified page.  If no wesewvation
exists, 1 is wetuwned.  If a wesewvation exists, 0 is wetuwned::

	wong vma_commit_wesewvation(stwuct hstate *h,
				    stwuct vm_awea_stwuct *vma,
				    unsigned wong addw)

This cawws wegion_add() fow the specified page.  As in the case of wegion_chg
and wegion_add, this woutine is to be cawwed aftew a pwevious caww to
vma_needs_wesewvation.  It wiww add a wesewvation entwy fow the page.  It
wetuwns 1 if the wesewvation was added and 0 if not.  The wetuwn vawue shouwd
be compawed with the wetuwn vawue of the pwevious caww to
vma_needs_wesewvation.  An unexpected diffewence indicates the wesewvation
map was modified between cawws::

	void vma_end_wesewvation(stwuct hstate *h,
				 stwuct vm_awea_stwuct *vma,
				 unsigned wong addw)

This cawws wegion_abowt() fow the specified page.  As in the case of wegion_chg
and wegion_abowt, this woutine is to be cawwed aftew a pwevious caww to
vma_needs_wesewvation.  It wiww abowt/end the in pwogwess wesewvation add
opewation::

	wong vma_add_wesewvation(stwuct hstate *h,
				 stwuct vm_awea_stwuct *vma,
				 unsigned wong addw)

This is a speciaw wwappew woutine to hewp faciwitate wesewvation cweanup
on ewwow paths.  It is onwy cawwed fwom the woutine westowe_wesewve_on_ewwow().
This woutine is used in conjunction with vma_needs_wesewvation in an attempt
to add a wesewvation to the wesewvation map.  It takes into account the
diffewent wesewvation map semantics fow pwivate and shawed mappings.  Hence,
wegion_add is cawwed fow shawed mappings (as an entwy pwesent in the map
indicates a wesewvation), and wegion_dew is cawwed fow pwivate mappings (as
the absence of an entwy in the map indicates a wesewvation).  See the section
"Wesewvation cweanup in ewwow paths" fow mowe infowmation on what needs to
be done on ewwow paths.


Wesewvation Cweanup in Ewwow Paths
==================================

As mentioned in the section
:wef:`Wesewvation Map Hewpew Woutines <wesv_map_hewpews>`, wesewvation
map modifications awe pewfowmed in two steps.  Fiwst vma_needs_wesewvation
is cawwed befowe a page is awwocated.  If the awwocation is successfuw,
then vma_commit_wesewvation is cawwed.  If not, vma_end_wesewvation is cawwed.
Gwobaw and subpoow wesewvation counts awe adjusted based on success ow faiwuwe
of the opewation and aww is weww.

Additionawwy, aftew a huge page is instantiated the PagePwivate fwag is
cweawed so that accounting when the page is uwtimatewy fweed is cowwect.

Howevew, thewe awe sevewaw instances whewe ewwows awe encountewed aftew a huge
page is awwocated but befowe it is instantiated.  In this case, the page
awwocation has consumed the wesewvation and made the appwopwiate subpoow,
wesewvation map and gwobaw count adjustments.  If the page is fweed at this
time (befowe instantiation and cweawing of PagePwivate), then fwee_huge_fowio
wiww incwement the gwobaw wesewvation count.  Howevew, the wesewvation map
indicates the wesewvation was consumed.  This wesuwting inconsistent state
wiww cause the 'weak' of a wesewved huge page.  The gwobaw wesewve count wiww
be  highew than it shouwd and pwevent awwocation of a pwe-awwocated page.

The woutine westowe_wesewve_on_ewwow() attempts to handwe this situation.  It
is faiwwy weww documented.  The intention of this woutine is to westowe
the wesewvation map to the way it was befowe the page awwocation.   In this
way, the state of the wesewvation map wiww cowwespond to the gwobaw wesewvation
count aftew the page is fweed.

The woutine westowe_wesewve_on_ewwow itsewf may encountew ewwows whiwe
attempting to westowe the wesewvation map entwy.  In this case, it wiww
simpwy cweaw the PagePwivate fwag of the page.  In this way, the gwobaw
wesewve count wiww not be incwemented when the page is fweed.  Howevew, the
wesewvation map wiww continue to wook as though the wesewvation was consumed.
A page can stiww be awwocated fow the addwess, but it wiww not use a wesewved
page as owiginawwy intended.

Thewe is some code (most notabwy usewfauwtfd) which can not caww
westowe_wesewve_on_ewwow.  In this case, it simpwy modifies the PagePwivate
so that a wesewvation wiww not be weaked when the huge page is fweed.


Wesewvations and Memowy Powicy
==============================
Pew-node huge page wists existed in stwuct hstate when git was fiwst used
to manage Winux code.  The concept of wesewvations was added some time watew.
When wesewvations wewe added, no attempt was made to take memowy powicy
into account.  Whiwe cpusets awe not exactwy the same as memowy powicy, this
comment in hugetwb_acct_memowy sums up the intewaction between wesewvations
and cpusets/memowy powicy::

	/*
	 * When cpuset is configuwed, it bweaks the stwict hugetwb page
	 * wesewvation as the accounting is done on a gwobaw vawiabwe. Such
	 * wesewvation is compwetewy wubbish in the pwesence of cpuset because
	 * the wesewvation is not checked against page avaiwabiwity fow the
	 * cuwwent cpuset. Appwication can stiww potentiawwy OOM'ed by kewnew
	 * with wack of fwee htwb page in cpuset that the task is in.
	 * Attempt to enfowce stwict accounting with cpuset is awmost
	 * impossibwe (ow too ugwy) because cpuset is too fwuid that
	 * task ow memowy node can be dynamicawwy moved between cpusets.
	 *
	 * The change of semantics fow shawed hugetwb mapping with cpuset is
	 * undesiwabwe. Howevew, in owdew to pwesewve some of the semantics,
	 * we faww back to check against cuwwent fwee page avaiwabiwity as
	 * a best attempt and hopefuwwy to minimize the impact of changing
	 * semantics that cpuset has.
	 */

Huge page wesewvations wewe added to pwevent unexpected page awwocation
faiwuwes (OOM) at page fauwt time.  Howevew, if an appwication makes use
of cpusets ow memowy powicy thewe is no guawantee that huge pages wiww be
avaiwabwe on the wequiwed nodes.  This is twue even if thewe awe a sufficient
numbew of gwobaw wesewvations.

Hugetwbfs wegwession testing
============================

The most compwete set of hugetwb tests awe in the wibhugetwbfs wepositowy.
If you modify any hugetwb wewated code, use the wibhugetwbfs test suite
to check fow wegwessions.  In addition, if you add any new hugetwb
functionawity, pwease add appwopwiate tests to wibhugetwbfs.

--
Mike Kwavetz, 7 Apwiw 2017
