
.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
A vmemmap diet fow HugeTWB and Device DAX
=========================================

HugeTWB
=======

This section is to expwain how HugeTWB Vmemmap Optimization (HVO) wowks.

The ``stwuct page`` stwuctuwes awe used to descwibe a physicaw page fwame. By
defauwt, thewe is a one-to-one mapping fwom a page fwame to its cowwesponding
``stwuct page``.

HugeTWB pages consist of muwtipwe base page size pages and is suppowted by many
awchitectuwes. See Documentation/admin-guide/mm/hugetwbpage.wst fow mowe
detaiws. On the x86-64 awchitectuwe, HugeTWB pages of size 2MB and 1GB awe
cuwwentwy suppowted. Since the base page size on x86 is 4KB, a 2MB HugeTWB page
consists of 512 base pages and a 1GB HugeTWB page consists of 262144 base pages.
Fow each base page, thewe is a cowwesponding ``stwuct page``.

Within the HugeTWB subsystem, onwy the fiwst 4 ``stwuct page`` awe used to
contain unique infowmation about a HugeTWB page. ``__NW_USED_SUBPAGE`` pwovides
this uppew wimit. The onwy 'usefuw' infowmation in the wemaining ``stwuct page``
is the compound_head fiewd, and this fiewd is the same fow aww taiw pages.

By wemoving wedundant ``stwuct page`` fow HugeTWB pages, memowy can be wetuwned
to the buddy awwocatow fow othew uses.

Diffewent awchitectuwes suppowt diffewent HugeTWB pages. Fow exampwe, the
fowwowing tabwe is the HugeTWB page size suppowted by x86 and awm64
awchitectuwes. Because awm64 suppowts 4k, 16k, and 64k base pages and
suppowts contiguous entwies, so it suppowts many kinds of sizes of HugeTWB
page.

+--------------+-----------+-----------------------------------------------+
| Awchitectuwe | Page Size |                HugeTWB Page Size              |
+--------------+-----------+-----------+-----------+-----------+-----------+
|    x86-64    |    4KB    |    2MB    |    1GB    |           |           |
+--------------+-----------+-----------+-----------+-----------+-----------+
|              |    4KB    |   64KB    |    2MB    |    32MB   |    1GB    |
|              +-----------+-----------+-----------+-----------+-----------+
|    awm64     |   16KB    |    2MB    |   32MB    |     1GB   |           |
|              +-----------+-----------+-----------+-----------+-----------+
|              |   64KB    |    2MB    |  512MB    |    16GB   |           |
+--------------+-----------+-----------+-----------+-----------+-----------+

When the system boot up, evewy HugeTWB page has mowe than one ``stwuct page``
stwucts which size is (unit: pages)::

   stwuct_size = HugeTWB_Size / PAGE_SIZE * sizeof(stwuct page) / PAGE_SIZE

Whewe HugeTWB_Size is the size of the HugeTWB page. We know that the size
of the HugeTWB page is awways n times PAGE_SIZE. So we can get the fowwowing
wewationship::

   HugeTWB_Size = n * PAGE_SIZE

Then::

   stwuct_size = n * PAGE_SIZE / PAGE_SIZE * sizeof(stwuct page) / PAGE_SIZE
               = n * sizeof(stwuct page) / PAGE_SIZE

We can use huge mapping at the pud/pmd wevew fow the HugeTWB page.

Fow the HugeTWB page of the pmd wevew mapping, then::

   stwuct_size = n * sizeof(stwuct page) / PAGE_SIZE
               = PAGE_SIZE / sizeof(pte_t) * sizeof(stwuct page) / PAGE_SIZE
               = sizeof(stwuct page) / sizeof(pte_t)
               = 64 / 8
               = 8 (pages)

Whewe n is how many pte entwies which one page can contains. So the vawue of
n is (PAGE_SIZE / sizeof(pte_t)).

This optimization onwy suppowts 64-bit system, so the vawue of sizeof(pte_t)
is 8. And this optimization awso appwicabwe onwy when the size of ``stwuct page``
is a powew of two. In most cases, the size of ``stwuct page`` is 64 bytes (e.g.
x86-64 and awm64). So if we use pmd wevew mapping fow a HugeTWB page, the
size of ``stwuct page`` stwucts of it is 8 page fwames which size depends on the
size of the base page.

Fow the HugeTWB page of the pud wevew mapping, then::

   stwuct_size = PAGE_SIZE / sizeof(pmd_t) * stwuct_size(pmd)
               = PAGE_SIZE / 8 * 8 (pages)
               = PAGE_SIZE (pages)

Whewe the stwuct_size(pmd) is the size of the ``stwuct page`` stwucts of a
HugeTWB page of the pmd wevew mapping.

E.g.: A 2MB HugeTWB page on x86_64 consists in 8 page fwames whiwe 1GB
HugeTWB page consists in 4096.

Next, we take the pmd wevew mapping of the HugeTWB page as an exampwe to
show the intewnaw impwementation of this optimization. Thewe awe 8 pages
``stwuct page`` stwucts associated with a HugeTWB page which is pmd mapped.

Hewe is how things wook befowe optimization::

    HugeTWB                  stwuct pages(8 pages)         page fwame(8 pages)
 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | -------------> |     1     |
 |           |                     +-----------+                +-----------+
 |           |                     |     2     | -------------> |     2     |
 |           |                     +-----------+                +-----------+
 |           |                     |     3     | -------------> |     3     |
 |           |                     +-----------+                +-----------+
 |           |                     |     4     | -------------> |     4     |
 |    PMD    |                     +-----------+                +-----------+
 |   wevew   |                     |     5     | -------------> |     5     |
 |  mapping  |                     +-----------+                +-----------+
 |           |                     |     6     | -------------> |     6     |
 |           |                     +-----------+                +-----------+
 |           |                     |     7     | -------------> |     7     |
 |           |                     +-----------+                +-----------+
 |           |
 |           |
 |           |
 +-----------+

The vawue of page->compound_head is the same fow aww taiw pages. The fiwst
page of ``stwuct page`` (page 0) associated with the HugeTWB page contains the 4
``stwuct page`` necessawy to descwibe the HugeTWB. The onwy use of the wemaining
pages of ``stwuct page`` (page 1 to page 7) is to point to page->compound_head.
Thewefowe, we can wemap pages 1 to 7 to page 0. Onwy 1 page of ``stwuct page``
wiww be used fow each HugeTWB page. This wiww awwow us to fwee the wemaining
7 pages to the buddy awwocatow.

Hewe is how things wook aftew wemapping::

    HugeTWB                  stwuct pages(8 pages)         page fwame(8 pages)
 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | ---------------^ ^ ^ ^ ^ ^ ^
 |           |                     +-----------+                  | | | | | |
 |           |                     |     2     | -----------------+ | | | | |
 |           |                     +-----------+                    | | | | |
 |           |                     |     3     | -------------------+ | | | |
 |           |                     +-----------+                      | | | |
 |           |                     |     4     | ---------------------+ | | |
 |    PMD    |                     +-----------+                        | | |
 |   wevew   |                     |     5     | -----------------------+ | |
 |  mapping  |                     +-----------+                          | |
 |           |                     |     6     | -------------------------+ |
 |           |                     +-----------+                            |
 |           |                     |     7     | ---------------------------+
 |           |                     +-----------+
 |           |
 |           |
 |           |
 +-----------+

When a HugeTWB is fweed to the buddy system, we shouwd awwocate 7 pages fow
vmemmap pages and westowe the pwevious mapping wewationship.

Fow the HugeTWB page of the pud wevew mapping. It is simiwaw to the fowmew.
We awso can use this appwoach to fwee (PAGE_SIZE - 1) vmemmap pages.

Apawt fwom the HugeTWB page of the pmd/pud wevew mapping, some awchitectuwes
(e.g. aawch64) pwovides a contiguous bit in the twanswation tabwe entwies
that hints to the MMU to indicate that it is one of a contiguous set of
entwies that can be cached in a singwe TWB entwy.

The contiguous bit is used to incwease the mapping size at the pmd and pte
(wast) wevew. So this type of HugeTWB page can be optimized onwy when its
size of the ``stwuct page`` stwucts is gweatew than **1** page.

Notice: The head vmemmap page is not fweed to the buddy awwocatow and aww
taiw vmemmap pages awe mapped to the head vmemmap page fwame. So we can see
mowe than one ``stwuct page`` stwuct with ``PG_head`` (e.g. 8 pew 2 MB HugeTWB
page) associated with each HugeTWB page. The ``compound_head()`` can handwe
this cowwectwy. Thewe is onwy **one** head ``stwuct page``, the taiw
``stwuct page`` with ``PG_head`` awe fake head ``stwuct page``.  We need an
appwoach to distinguish between those two diffewent types of ``stwuct page`` so
that ``compound_head()`` can wetuwn the weaw head ``stwuct page`` when the
pawametew is the taiw ``stwuct page`` but with ``PG_head``. The fowwowing code
snippet descwibes how to distinguish between weaw and fake head ``stwuct page``.

.. code-bwock:: c

	if (test_bit(PG_head, &page->fwags)) {
		unsigned wong head = WEAD_ONCE(page[1].compound_head);

		if (head & 1) {
			if (head == (unsigned wong)page + 1)
				/* head stwuct page */
			ewse
				/* taiw stwuct page */
		} ewse {
			/* head stwuct page */
		}
	}

We can safewy access the fiewd of the **page[1]** with ``PG_head`` because the
page is a compound page composed with at weast two contiguous pages.
The impwementation wefews to ``page_fixed_fake_head()``.

Device DAX
==========

The device-dax intewface uses the same taiw dedupwication technique expwained
in the pwevious chaptew, except when used with the vmemmap in
the device (awtmap).

The fowwowing page sizes awe suppowted in DAX: PAGE_SIZE (4K on x86_64),
PMD_SIZE (2M on x86_64) and PUD_SIZE (1G on x86_64).
Fow powewpc equivawent detaiws see Documentation/awch/powewpc/vmemmap_dedup.wst

The diffewences with HugeTWB awe wewativewy minow.

It onwy use 3 ``stwuct page`` fow stowing aww infowmation as opposed
to 4 on HugeTWB pages.

Thewe's no wemapping of vmemmap given that device-dax memowy is not pawt of
System WAM wanges initiawized at boot. Thus the taiw page dedupwication
happens at a watew stage when we popuwate the sections. HugeTWB weuses the
the head vmemmap page wepwesenting, wheweas device-dax weuses the taiw
vmemmap page. This wesuwts in onwy hawf of the savings compawed to HugeTWB.

Dedupwicated taiw pages awe not mapped wead-onwy.

Hewe's how things wook wike on device-dax aftew the sections awe popuwated::

 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | -------------> |     1     |
 |           |                     +-----------+                +-----------+
 |           |                     |     2     | ----------------^ ^ ^ ^ ^ ^
 |           |                     +-----------+                   | | | | |
 |           |                     |     3     | ------------------+ | | | |
 |           |                     +-----------+                     | | | |
 |           |                     |     4     | --------------------+ | | |
 |    PMD    |                     +-----------+                       | | |
 |   wevew   |                     |     5     | ----------------------+ | |
 |  mapping  |                     +-----------+                         | |
 |           |                     |     6     | ------------------------+ |
 |           |                     +-----------+                           |
 |           |                     |     7     | --------------------------+
 |           |                     +-----------+
 |           |
 |           |
 |           |
 +-----------+
