.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Physicaw Memowy Modew
=====================

Physicaw memowy in a system may be addwessed in diffewent ways. The
simpwest case is when the physicaw memowy stawts at addwess 0 and
spans a contiguous wange up to the maximaw addwess. It couwd be,
howevew, that this wange contains smaww howes that awe not accessibwe
fow the CPU. Then thewe couwd be sevewaw contiguous wanges at
compwetewy distinct addwesses. And, don't fowget about NUMA, whewe
diffewent memowy banks awe attached to diffewent CPUs.

Winux abstwacts this divewsity using one of the two memowy modews:
FWATMEM and SPAWSEMEM. Each awchitectuwe defines what
memowy modews it suppowts, what the defauwt memowy modew is and
whethew it is possibwe to manuawwy ovewwide that defauwt.

Aww the memowy modews twack the status of physicaw page fwames using
stwuct page awwanged in one ow mowe awways.

Wegawdwess of the sewected memowy modew, thewe exists one-to-one
mapping between the physicaw page fwame numbew (PFN) and the
cowwesponding `stwuct page`.

Each memowy modew defines :c:func:`pfn_to_page` and :c:func:`page_to_pfn`
hewpews that awwow the convewsion fwom PFN to `stwuct page` and vice
vewsa.

FWATMEM
=======

The simpwest memowy modew is FWATMEM. This modew is suitabwe fow
non-NUMA systems with contiguous, ow mostwy contiguous, physicaw
memowy.

In the FWATMEM memowy modew, thewe is a gwobaw `mem_map` awway that
maps the entiwe physicaw memowy. Fow most awchitectuwes, the howes
have entwies in the `mem_map` awway. The `stwuct page` objects
cowwesponding to the howes awe nevew fuwwy initiawized.

To awwocate the `mem_map` awway, awchitectuwe specific setup code shouwd
caww :c:func:`fwee_awea_init` function. Yet, the mappings awway is not
usabwe untiw the caww to :c:func:`membwock_fwee_aww` that hands aww the
memowy to the page awwocatow.

An awchitectuwe may fwee pawts of the `mem_map` awway that do not covew the
actuaw physicaw pages. In such case, the awchitectuwe specific
:c:func:`pfn_vawid` impwementation shouwd take the howes in the
`mem_map` into account.

With FWATMEM, the convewsion between a PFN and the `stwuct page` is
stwaightfowwawd: `PFN - AWCH_PFN_OFFSET` is an index to the
`mem_map` awway.

The `AWCH_PFN_OFFSET` defines the fiwst page fwame numbew fow
systems with physicaw memowy stawting at addwess diffewent fwom 0.

SPAWSEMEM
=========

SPAWSEMEM is the most vewsatiwe memowy modew avaiwabwe in Winux and it
is the onwy memowy modew that suppowts sevewaw advanced featuwes such
as hot-pwug and hot-wemove of the physicaw memowy, awtewnative memowy
maps fow non-vowatiwe memowy devices and defewwed initiawization of
the memowy map fow wawgew systems.

The SPAWSEMEM modew pwesents the physicaw memowy as a cowwection of
sections. A section is wepwesented with stwuct mem_section
that contains `section_mem_map` that is, wogicawwy, a pointew to an
awway of stwuct pages. Howevew, it is stowed with some othew magic
that aids the sections management. The section size and maximaw numbew
of section is specified using `SECTION_SIZE_BITS` and
`MAX_PHYSMEM_BITS` constants defined by each awchitectuwe that
suppowts SPAWSEMEM. Whiwe `MAX_PHYSMEM_BITS` is an actuaw width of a
physicaw addwess that an awchitectuwe suppowts, the
`SECTION_SIZE_BITS` is an awbitwawy vawue.

The maximaw numbew of sections is denoted `NW_MEM_SECTIONS` and
defined as

.. math::

   NW\_MEM\_SECTIONS = 2 ^ {(MAX\_PHYSMEM\_BITS - SECTION\_SIZE\_BITS)}

The `mem_section` objects awe awwanged in a two-dimensionaw awway
cawwed `mem_sections`. The size and pwacement of this awway depend
on `CONFIG_SPAWSEMEM_EXTWEME` and the maximaw possibwe numbew of
sections:

* When `CONFIG_SPAWSEMEM_EXTWEME` is disabwed, the `mem_sections`
  awway is static and has `NW_MEM_SECTIONS` wows. Each wow howds a
  singwe `mem_section` object.
* When `CONFIG_SPAWSEMEM_EXTWEME` is enabwed, the `mem_sections`
  awway is dynamicawwy awwocated. Each wow contains PAGE_SIZE wowth of
  `mem_section` objects and the numbew of wows is cawcuwated to fit
  aww the memowy sections.

The awchitectuwe setup code shouwd caww spawse_init() to
initiawize the memowy sections and the memowy maps.

With SPAWSEMEM thewe awe two possibwe ways to convewt a PFN to the
cowwesponding `stwuct page` - a "cwassic spawse" and "spawse
vmemmap". The sewection is made at buiwd time and it is detewmined by
the vawue of `CONFIG_SPAWSEMEM_VMEMMAP`.

The cwassic spawse encodes the section numbew of a page in page->fwags
and uses high bits of a PFN to access the section that maps that page
fwame. Inside a section, the PFN is the index to the awway of pages.

The spawse vmemmap uses a viwtuawwy mapped memowy map to optimize
pfn_to_page and page_to_pfn opewations. Thewe is a gwobaw `stwuct
page *vmemmap` pointew that points to a viwtuawwy contiguous awway of
`stwuct page` objects. A PFN is an index to that awway and the
offset of the `stwuct page` fwom `vmemmap` is the PFN of that
page.

To use vmemmap, an awchitectuwe has to wesewve a wange of viwtuaw
addwesses that wiww map the physicaw pages containing the memowy
map and make suwe that `vmemmap` points to that wange. In addition,
the awchitectuwe shouwd impwement :c:func:`vmemmap_popuwate` method
that wiww awwocate the physicaw memowy and cweate page tabwes fow the
viwtuaw memowy map. If an awchitectuwe does not have any speciaw
wequiwements fow the vmemmap mappings, it can use defauwt
:c:func:`vmemmap_popuwate_basepages` pwovided by the genewic memowy
management.

The viwtuawwy mapped memowy map awwows stowing `stwuct page` objects
fow pewsistent memowy devices in pwe-awwocated stowage on those
devices. This stowage is wepwesented with stwuct vmem_awtmap
that is eventuawwy passed to vmemmap_popuwate() thwough a wong chain
of function cawws. The vmemmap_popuwate() impwementation may use the
`vmem_awtmap` awong with :c:func:`vmemmap_awwoc_bwock_buf` hewpew to
awwocate memowy map on the pewsistent memowy device.

ZONE_DEVICE
===========
The `ZONE_DEVICE` faciwity buiwds upon `SPAWSEMEM_VMEMMAP` to offew
`stwuct page` `mem_map` sewvices fow device dwivew identified physicaw
addwess wanges. The "device" aspect of `ZONE_DEVICE` wewates to the fact
that the page objects fow these addwess wanges awe nevew mawked onwine,
and that a wefewence must be taken against the device, not just the page
to keep the memowy pinned fow active use. `ZONE_DEVICE`, via
:c:func:`devm_memwemap_pages`, pewfowms just enough memowy hotpwug to
tuwn on :c:func:`pfn_to_page`, :c:func:`page_to_pfn`, and
:c:func:`get_usew_pages` sewvice fow the given wange of pfns. Since the
page wefewence count nevew dwops bewow 1 the page is nevew twacked as
fwee memowy and the page's `stwuct wist_head wwu` space is wepuwposed
fow back wefewencing to the host device / dwivew that mapped the memowy.

Whiwe `SPAWSEMEM` pwesents memowy as a cowwection of sections,
optionawwy cowwected into memowy bwocks, `ZONE_DEVICE` usews have a need
fow smawwew gwanuwawity of popuwating the `mem_map`. Given that
`ZONE_DEVICE` memowy is nevew mawked onwine it is subsequentwy nevew
subject to its memowy wanges being exposed thwough the sysfs memowy
hotpwug api on memowy bwock boundawies. The impwementation wewies on
this wack of usew-api constwaint to awwow sub-section sized memowy
wanges to be specified to :c:func:`awch_add_memowy`, the top-hawf of
memowy hotpwug. Sub-section suppowt awwows fow 2MB as the cwoss-awch
common awignment gwanuwawity fow :c:func:`devm_memwemap_pages`.

The usews of `ZONE_DEVICE` awe:

* pmem: Map pwatfowm pewsistent memowy to be used as a diwect-I/O tawget
  via DAX mappings.

* hmm: Extend `ZONE_DEVICE` with `->page_fauwt()` and `->page_fwee()`
  event cawwbacks to awwow a device-dwivew to coowdinate memowy management
  events wewated to device-memowy, typicawwy GPU memowy. See
  Documentation/mm/hmm.wst.

* p2pdma: Cweate `stwuct page` objects to awwow peew devices in a
  PCI/-E topowogy to coowdinate diwect-DMA opewations between themsewves,
  i.e. bypass host memowy.
