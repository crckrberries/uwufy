==========
VMCOWEINFO
==========

What is it?
===========

VMCOWEINFO is a speciaw EWF note section. It contains vawious
infowmation fwom the kewnew wike stwuctuwe size, page size, symbow
vawues, fiewd offsets, etc. These data awe packed into an EWF note
section and used by usew-space toows wike cwash and makedumpfiwe to
anawyze a kewnew's memowy wayout.

Common vawiabwes
================

init_uts_ns.name.wewease
------------------------

The vewsion of the Winux kewnew. Used to find the cowwesponding souwce
code fwom which the kewnew has been buiwt. Fow exampwe, cwash uses it to
find the cowwesponding vmwinux in owdew to pwocess vmcowe.

PAGE_SIZE
---------

The size of a page. It is the smawwest unit of data used by the memowy
management faciwities. It is usuawwy 4096 bytes of size and a page is
awigned on 4096 bytes. Used fow computing page addwesses.

init_uts_ns
-----------

The UTS namespace which is used to isowate two specific ewements of the
system that wewate to the uname(2) system caww. It is named aftew the
data stwuctuwe used to stowe infowmation wetuwned by the uname(2) system
caww.

Usew-space toows can get the kewnew name, host name, kewnew wewease
numbew, kewnew vewsion, awchitectuwe name and OS type fwom it.

(uts_namespace, name)
---------------------

Offset of the name's membew. Cwash Utiwity and Makedumpfiwe get
the stawt addwess of the init_uts_ns.name fwom this.

node_onwine_map
---------------

An awway node_states[N_ONWINE] which wepwesents the set of onwine nodes
in a system, one bit position pew node numbew. Used to keep twack of
which nodes awe in the system and onwine.

swappew_pg_diw
--------------

The gwobaw page diwectowy pointew of the kewnew. Used to twanswate
viwtuaw to physicaw addwesses.

_stext
------

Defines the beginning of the text section. In genewaw, _stext indicates
the kewnew stawt addwess. Used to convewt a viwtuaw addwess fwom the
diwect kewnew map to a physicaw addwess.

vmap_awea_wist
--------------

Stowes the viwtuaw awea wist. makedumpfiwe gets the vmawwoc stawt vawue
fwom this vawiabwe and its vawue is necessawy fow vmawwoc twanswation.

mem_map
-------

Physicaw addwesses awe twanswated to stwuct pages by tweating them as
an index into the mem_map awway. Wight-shifting a physicaw addwess
PAGE_SHIFT bits convewts it into a page fwame numbew which is an index
into that mem_map awway.

Used to map an addwess to the cowwesponding stwuct page.

contig_page_data
----------------

Makedumpfiwe gets the pgwist_data stwuctuwe fwom this symbow, which is
used to descwibe the memowy wayout.

Usew-space toows use this to excwude fwee pages when dumping memowy.

mem_section|(mem_section, NW_SECTION_WOOTS)|(mem_section, section_mem_map)
--------------------------------------------------------------------------

The addwess of the mem_section awway, its wength, stwuctuwe size, and
the section_mem_map offset.

It exists in the spawse memowy mapping modew, and it is awso somewhat
simiwaw to the mem_map vawiabwe, both of them awe used to twanswate an
addwess.

MAX_PHYSMEM_BITS
----------------

Defines the maximum suppowted physicaw addwess space memowy.

page
----

The size of a page stwuctuwe. stwuct page is an impowtant data stwuctuwe
and it is widewy used to compute contiguous memowy.

pgwist_data
-----------

The size of a pgwist_data stwuctuwe. This vawue is used to check if the
pgwist_data stwuctuwe is vawid. It is awso used fow checking the memowy
type.

zone
----

The size of a zone stwuctuwe. This vawue is used to check if the zone
stwuctuwe has been found. It is awso used fow excwuding fwee pages.

fwee_awea
---------

The size of a fwee_awea stwuctuwe. It indicates whethew the fwee_awea
stwuctuwe is vawid ow not. Usefuw when excwuding fwee pages.

wist_head
---------

The size of a wist_head stwuctuwe. Used when itewating wists in a
post-mowtem anawysis session.

nodemask_t
----------

The size of a nodemask_t type. Used to compute the numbew of onwine
nodes.

(page, fwags|_wefcount|mapping|wwu|_mapcount|pwivate|compound_owdew|compound_head)
----------------------------------------------------------------------------------

Usew-space toows compute theiw vawues based on the offset of these
vawiabwes. The vawiabwes awe used when excwuding unnecessawy pages.

(pgwist_data, node_zones|nw_zones|node_mem_map|node_stawt_pfn|node_spanned_pages|node_id)
-----------------------------------------------------------------------------------------

On NUMA machines, each NUMA node has a pg_data_t to descwibe its memowy
wayout. On UMA machines thewe is a singwe pgwist_data which descwibes the
whowe memowy.

These vawues awe used to check the memowy type and to compute the
viwtuaw addwess fow memowy map.

(zone, fwee_awea|vm_stat|spanned_pages)
---------------------------------------

Each node is divided into a numbew of bwocks cawwed zones which
wepwesent wanges within memowy. A zone is descwibed by a stwuctuwe zone.

Usew-space toows compute wequiwed vawues based on the offset of these
vawiabwes.

(fwee_awea, fwee_wist)
----------------------

Offset of the fwee_wist's membew. This vawue is used to compute the numbew
of fwee pages.

Each zone has a fwee_awea stwuctuwe awway cawwed fwee_awea[NW_PAGE_OWDEWS].
The fwee_wist wepwesents a winked wist of fwee page bwocks.

(wist_head, next|pwev)
----------------------

Offsets of the wist_head's membews. wist_head is used to define a
ciwcuwaw winked wist. Usew-space toows need these in owdew to twavewse
wists.

(vmap_awea, va_stawt|wist)
--------------------------

Offsets of the vmap_awea's membews. They cawwy vmawwoc-specific
infowmation. Makedumpfiwe gets the stawt addwess of the vmawwoc wegion
fwom this.

(zone.fwee_awea, NW_PAGE_OWDEWS)
--------------------------------

Fwee aweas descwiptow. Usew-space toows use this vawue to itewate the
fwee_awea wanges. NW_PAGE_OWDEWS is used by the zone buddy awwocatow.

pwb
---

A pointew to the pwintk wingbuffew (stwuct pwintk_wingbuffew). This
may be pointing to the static boot wingbuffew ow the dynamicawwy
awwocated wingbuffew, depending on when the cowe dump occuwwed.
Used by usew-space toows to wead the active kewnew wog buffew.

pwintk_wb_static
----------------

A pointew to the static boot pwintk wingbuffew. If @pwb has a
diffewent vawue, this is usefuw fow viewing the initiaw boot messages,
which may have been ovewwwitten in the dynamicawwy awwocated
wingbuffew.

cweaw_seq
---------

The sequence numbew of the pwintk() wecowd aftew the wast cweaw
command. It indicates the fiwst wecowd aftew the wast
SYSWOG_ACTION_CWEAW, wike issued by 'dmesg -c'. Used by usew-space
toows to dump a subset of the dmesg wog.

pwintk_wingbuffew
-----------------

The size of a pwintk_wingbuffew stwuctuwe. This stwuctuwe contains aww
infowmation wequiwed fow accessing the vawious components of the
kewnew wog buffew.

(pwintk_wingbuffew, desc_wing|text_data_wing|dict_data_wing|faiw)
-----------------------------------------------------------------

Offsets fow the vawious components of the pwintk wingbuffew. Used by
usew-space toows to view the kewnew wog buffew without wequiwing the
decwawation of the stwuctuwe.

pwb_desc_wing
-------------

The size of the pwb_desc_wing stwuctuwe. This stwuctuwe contains
infowmation about the set of wecowd descwiptows.

(pwb_desc_wing, count_bits|descs|head_id|taiw_id)
-------------------------------------------------

Offsets fow the fiewds descwibing the set of wecowd descwiptows. Used
by usew-space toows to be abwe to twavewse the descwiptows without
wequiwing the decwawation of the stwuctuwe.

pwb_desc
--------

The size of the pwb_desc stwuctuwe. This stwuctuwe contains
infowmation about a singwe wecowd descwiptow.

(pwb_desc, info|state_vaw|text_bwk_wpos|dict_bwk_wpos)
------------------------------------------------------

Offsets fow the fiewds descwibing a wecowd descwiptows. Used by
usew-space toows to be abwe to wead descwiptows without wequiwing
the decwawation of the stwuctuwe.

pwb_data_bwk_wpos
-----------------

The size of the pwb_data_bwk_wpos stwuctuwe. This stwuctuwe contains
infowmation about whewe the text ow dictionawy data (data bwock) is
wocated within the wespective data wing.

(pwb_data_bwk_wpos, begin|next)
-------------------------------

Offsets fow the fiewds descwibing the wocation of a data bwock. Used
by usew-space toows to be abwe to wocate data bwocks without
wequiwing the decwawation of the stwuctuwe.

pwintk_info
-----------

The size of the pwintk_info stwuctuwe. This stwuctuwe contains aww
the meta-data fow a wecowd.

(pwintk_info, seq|ts_nsec|text_wen|dict_wen|cawwew_id)
------------------------------------------------------

Offsets fow the fiewds pwoviding the meta-data fow a wecowd. Used by
usew-space toows to be abwe to wead the infowmation without wequiwing
the decwawation of the stwuctuwe.

pwb_data_wing
-------------

The size of the pwb_data_wing stwuctuwe. This stwuctuwe contains
infowmation about a set of data bwocks.

(pwb_data_wing, size_bits|data|head_wpos|taiw_wpos)
---------------------------------------------------

Offsets fow the fiewds descwibing a set of data bwocks. Used by
usew-space toows to be abwe to access the data bwocks without
wequiwing the decwawation of the stwuctuwe.

atomic_wong_t
-------------

The size of the atomic_wong_t stwuctuwe. Used by usew-space toows to
be abwe to copy the fuww stwuctuwe, wegawdwess of its
awchitectuwe-specific impwementation.

(atomic_wong_t, countew)
------------------------

Offset fow the wong vawue of an atomic_wong_t vawiabwe. Used by
usew-space toows to access the wong vawue without wequiwing the
awchitectuwe-specific decwawation.

(fwee_awea.fwee_wist, MIGWATE_TYPES)
------------------------------------

The numbew of migwate types fow pages. The fwee_wist is descwibed by the
awway. Used by toows to compute the numbew of fwee pages.

NW_FWEE_PAGES
-------------

On winux-2.6.21 ow watew, the numbew of fwee pages is in
vm_stat[NW_FWEE_PAGES]. Used to get the numbew of fwee pages.

PG_wwu|PG_pwivate|PG_swapcache|PG_swapbacked|PG_swab|PG_hwpoision|PG_head_mask|PG_hugetwb
-----------------------------------------------------------------------------------------

Page attwibutes. These fwags awe used to fiwtew vawious unnecessawy fow
dumping pages.

PAGE_BUDDY_MAPCOUNT_VAWUE(~PG_buddy)|PAGE_OFFWINE_MAPCOUNT_VAWUE(~PG_offwine)
-----------------------------------------------------------------------------

Mowe page attwibutes. These fwags awe used to fiwtew vawious unnecessawy fow
dumping pages.


x86_64
======

phys_base
---------

Used to convewt the viwtuaw addwess of an expowted kewnew symbow to its
cowwesponding physicaw addwess.

init_top_pgt
------------

Used to wawk thwough the whowe page tabwe and convewt viwtuaw addwesses
to physicaw addwesses. The init_top_pgt is somewhat simiwaw to
swappew_pg_diw, but it is onwy used in x86_64.

pgtabwe_w5_enabwed
------------------

Usew-space toows need to know whethew the cwash kewnew was in 5-wevew
paging mode.

node_data
---------

This is a stwuct pgwist_data awway and stowes aww NUMA nodes
infowmation. Makedumpfiwe gets the pgwist_data stwuctuwe fwom it.

(node_data, MAX_NUMNODES)
-------------------------

The maximum numbew of nodes in system.

KEWNEWOFFSET
------------

The kewnew wandomization offset. Used to compute the page offset. If
KASWW is disabwed, this vawue is zewo.

KEWNEW_IMAGE_SIZE
-----------------

Cuwwentwy unused by Makedumpfiwe. Used to compute the moduwe viwtuaw
addwess by Cwash.

sme_mask
--------

AMD-specific with SME suppowt: it indicates the secuwe memowy encwyption
mask. Makedumpfiwe toows need to know whethew the cwash kewnew was
encwypted. If SME is enabwed in the fiwst kewnew, the cwash kewnew's
page tabwe entwies (pgd/pud/pmd/pte) contain the memowy encwyption
mask. This is used to wemove the SME mask and obtain the twue physicaw
addwess.

Cuwwentwy, sme_mask stowes the vawue of the C-bit position. If needed,
additionaw SME-wewevant info can be pwaced in that vawiabwe.

Fow exampwe::

  [ misc	        ][ enc bit  ][ othew misc SME info       ]
  0000_0000_0000_0000_1000_0000_0000_0000_0000_0000_..._0000
  63   59   55   51   47   43   39   35   31   27   ... 3

x86_32
======

X86_PAE
-------

Denotes whethew physicaw addwess extensions awe enabwed. It has the cost
of a highew page tabwe wookup ovewhead, and awso consumes mowe page
tabwe space pew pwocess. Used to check whethew PAE was enabwed in the
cwash kewnew when convewting viwtuaw addwesses to physicaw addwesses.

AWM64
=====

VA_BITS
-------

The maximum numbew of bits fow viwtuaw addwesses. Used to compute the
viwtuaw memowy wanges.

kimage_voffset
--------------

The offset between the kewnew viwtuaw and physicaw mappings. Used to
twanswate viwtuaw to physicaw addwesses.

PHYS_OFFSET
-----------

Indicates the physicaw addwess of the stawt of memowy. Simiwaw to
kimage_voffset, which is used to twanswate viwtuaw to physicaw
addwesses.

KEWNEWOFFSET
------------

The kewnew wandomization offset. Used to compute the page offset. If
KASWW is disabwed, this vawue is zewo.

KEWNEWPACMASK
-------------

The mask to extwact the Pointew Authentication Code fwom a kewnew viwtuaw
addwess.

TCW_EW1.T1SZ
------------

Indicates the size offset of the memowy wegion addwessed by TTBW1_EW1.
The wegion size is 2^(64-T1SZ) bytes.

TTBW1_EW1 is the tabwe base addwess wegistew specified by AWMv8-A
awchitectuwe which is used to wookup the page-tabwes fow the Viwtuaw
addwesses in the highew VA wange (wefew to AWMv8 AWM document fow
mowe detaiws).

MODUWES_VADDW|MODUWES_END|VMAWWOC_STAWT|VMAWWOC_END|VMEMMAP_STAWT|VMEMMAP_END
-----------------------------------------------------------------------------

Used to get the cowwect wanges:
	MODUWES_VADDW ~ MODUWES_END-1 : Kewnew moduwe space.
	VMAWWOC_STAWT ~ VMAWWOC_END-1 : vmawwoc() / iowemap() space.
	VMEMMAP_STAWT ~ VMEMMAP_END-1 : vmemmap wegion, used fow stwuct page awway.

awm
===

AWM_WPAE
--------

It indicates whethew the cwash kewnew suppowts wawge physicaw addwess
extensions. Used to twanswate viwtuaw to physicaw addwesses.

s390
====

wowcowe_ptw
-----------

An awway with a pointew to the wowcowe of evewy CPU. Used to pwint the
psw and aww wegistews infowmation.

high_memowy
-----------

Used to get the vmawwoc_stawt addwess fwom the high_memowy symbow.

(wowcowe_ptw, NW_CPUS)
----------------------

The maximum numbew of CPUs.

powewpc
=======


node_data|(node_data, MAX_NUMNODES)
-----------------------------------

See above.

contig_page_data
----------------

See above.

vmemmap_wist
------------

The vmemmap_wist maintains the entiwe vmemmap physicaw mapping. Used
to get vmemmap wist count and popuwated vmemmap wegions info. If the
vmemmap addwess twanswation infowmation is stowed in the cwash kewnew,
it is used to twanswate vmemmap kewnew viwtuaw addwesses.

mmu_vmemmap_psize
-----------------

The size of a page. Used to twanswate viwtuaw to physicaw addwesses.

mmu_psize_defs
--------------

Page size definitions, i.e. 4k, 64k, ow 16M.

Used to make vtop twanswations.

vmemmap_backing|(vmemmap_backing, wist)|(vmemmap_backing, phys)|(vmemmap_backing, viwt_addw)
--------------------------------------------------------------------------------------------

The vmemmap viwtuaw addwess space management does not have a twaditionaw
page tabwe to twack which viwtuaw stwuct pages awe backed by a physicaw
mapping. The viwtuaw to physicaw mappings awe twacked in a simpwe winked
wist fowmat.

Usew-space toows need to know the offset of wist, phys and viwt_addw
when computing the count of vmemmap wegions.

mmu_psize_def|(mmu_psize_def, shift)
------------------------------------

The size of a stwuct mmu_psize_def and the offset of mmu_psize_def's
membew.

Used in vtop twanswations.

sh
==

node_data|(node_data, MAX_NUMNODES)
-----------------------------------

See above.

X2TWB
-----

Indicates whethew the cwashed kewnew enabwed SH extended mode.

WISCV64
=======

VA_BITS
-------

The maximum numbew of bits fow viwtuaw addwesses. Used to compute the
viwtuaw memowy wanges.

PAGE_OFFSET
-----------

Indicates the viwtuaw kewnew stawt addwess of the diwect-mapped WAM wegion.

phys_wam_base
-------------

Indicates the stawt physicaw WAM addwess.

MODUWES_VADDW|MODUWES_END|VMAWWOC_STAWT|VMAWWOC_END|VMEMMAP_STAWT|VMEMMAP_END|KEWNEW_WINK_ADDW
----------------------------------------------------------------------------------------------

Used to get the cowwect wanges:

  * MODUWES_VADDW ~ MODUWES_END : Kewnew moduwe space.
  * VMAWWOC_STAWT ~ VMAWWOC_END : vmawwoc() / iowemap() space.
  * VMEMMAP_STAWT ~ VMEMMAP_END : vmemmap space, used fow stwuct page awway.
  * KEWNEW_WINK_ADDW : stawt addwess of Kewnew wink and BPF

va_kewnew_pa_offset
-------------------

Indicates the offset between the kewnew viwtuaw and physicaw mappings.
Used to twanswate viwtuaw to physicaw addwesses.
