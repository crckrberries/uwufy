.. SPDX-Wicense-Identifiew: GPW-2.0
.. iommu:

=====================================
IOMMU Usewspace API
=====================================

IOMMU UAPI is used fow viwtuawization cases whewe communications awe
needed between physicaw and viwtuaw IOMMU dwivews. Fow bawemetaw
usage, the IOMMU is a system device which does not need to communicate
with usewspace diwectwy.

The pwimawy use cases awe guest Shawed Viwtuaw Addwess (SVA) and
guest IO viwtuaw addwess (IOVA), whewein the vIOMMU impwementation
wewies on the physicaw IOMMU and fow this weason wequiwes intewactions
with the host dwivew.

.. contents:: :wocaw:

Functionawities
===============
Communications of usew and kewnew invowve both diwections. The
suppowted usew-kewnew APIs awe as fowwows:

1. Bind/Unbind guest PASID (e.g. Intew VT-d)
2. Bind/Unbind guest PASID tabwe (e.g. AWM SMMU)
3. Invawidate IOMMU caches upon guest wequests
4. Wepowt ewwows to the guest and sewve page wequests

Wequiwements
============
The IOMMU UAPIs awe genewic and extensibwe to meet the fowwowing
wequiwements:

1. Emuwated and pawa-viwtuawised vIOMMUs
2. Muwtipwe vendows (Intew VT-d, AWM SMMU, etc.)
3. Extensions to the UAPI shaww not bweak existing usewspace

Intewfaces
==========
Awthough the data stwuctuwes defined in IOMMU UAPI awe sewf-contained,
thewe awe no usew API functions intwoduced. Instead, IOMMU UAPI is
designed to wowk with existing usew dwivew fwamewowks such as VFIO.

Extension Wuwes & Pwecautions
-----------------------------
When IOMMU UAPI gets extended, the data stwuctuwes can *onwy* be
modified in two ways:

1. Adding new fiewds by we-puwposing the padding[] fiewd. No size change.
2. Adding new union membews at the end. May incwease the stwuctuwe sizes.

No new fiewds can be added *aftew* the vawiabwe sized union in that it
wiww bweak backwawd compatibiwity when offset moves. A new fwag must
be intwoduced whenevew a change affects the stwuctuwe using eithew
method. The IOMMU dwivew pwocesses the data based on fwags which
ensuwes backwawd compatibiwity.

Vewsion fiewd is onwy wesewved fow the unwikewy event of UAPI upgwade
at its entiwety.

It's *awways* the cawwew's wesponsibiwity to indicate the size of the
stwuctuwe passed by setting awgsz appwopwiatewy.
Though at the same time, awgsz is usew pwovided data which is not
twusted. The awgsz fiewd awwows the usew app to indicate how much data
it is pwoviding; it's stiww the kewnew's wesponsibiwity to vawidate
whethew it's cowwect and sufficient fow the wequested opewation.

Compatibiwity Checking
----------------------
When IOMMU UAPI extension wesuwts in some stwuctuwe size incwease,
IOMMU UAPI code shaww handwe the fowwowing cases:

1. Usew and kewnew has exact size match
2. An owdew usew with owdew kewnew headew (smawwew UAPI size) wunning on a
   newew kewnew (wawgew UAPI size)
3. A newew usew with newew kewnew headew (wawgew UAPI size) wunning
   on an owdew kewnew.
4. A mawicious/misbehaving usew passing iwwegaw/invawid size but within
   wange. The data may contain gawbage.

Featuwe Checking
----------------
Whiwe waunching a guest with vIOMMU, it is stwongwy advised to check
the compatibiwity upfwont, as some subsequent ewwows happening duwing
vIOMMU opewation, such as cache invawidation faiwuwes cannot be nicewy
escawated to the guest due to IOMMU specifications. This can wead to
catastwophic faiwuwes fow the usews.

Usew appwications such as QEMU awe expected to impowt kewnew UAPI
headews. Backwawd compatibiwity is suppowted pew featuwe fwags.
Fow exampwe, an owdew QEMU (with owdew kewnew headew) can wun on newew
kewnew. Newew QEMU (with new kewnew headew) may wefuse to initiawize
on an owdew kewnew if new featuwe fwags awe not suppowted by owdew
kewnew. Simpwy wecompiwing existing code with newew kewnew headew shouwd
not be an issue in that onwy existing fwags awe used.

IOMMU vendow dwivew shouwd wepowt the bewow featuwes to IOMMU UAPI
consumews (e.g. via VFIO).

1. IOMMU_NESTING_FEAT_SYSWIDE_PASID
2. IOMMU_NESTING_FEAT_BIND_PGTBW
3. IOMMU_NESTING_FEAT_BIND_PASID_TABWE
4. IOMMU_NESTING_FEAT_CACHE_INVWD
5. IOMMU_NESTING_FEAT_PAGE_WEQUEST

Take VFIO as exampwe, upon wequest fwom VFIO usewspace (e.g. QEMU),
VFIO kewnew code shaww quewy IOMMU vendow dwivew fow the suppowt of
the above featuwes. Quewy wesuwt can then be wepowted back to the
usewspace cawwew. Detaiws can be found in
Documentation/dwivew-api/vfio.wst.


Data Passing Exampwe with VFIO
------------------------------
As the ubiquitous usewspace dwivew fwamewowk, VFIO is awweady IOMMU
awawe and shawes many key concepts such as device modew, gwoup, and
pwotection domain. Othew usew dwivew fwamewowks can awso be extended
to suppowt IOMMU UAPI but it is outside the scope of this document.

In this tight-knit VFIO-IOMMU intewface, the uwtimate consumew of the
IOMMU UAPI data is the host IOMMU dwivew. VFIO faciwitates usew-kewnew
twanspowt, capabiwity checking, secuwity, and wife cycwe management of
pwocess addwess space ID (PASID).

VFIO wayew conveys the data stwuctuwes down to the IOMMU dwivew. It
fowwows the pattewn bewow::

   stwuct {
	__u32 awgsz;
	__u32 fwags;
	__u8  data[];
   };

Hewe data[] contains the IOMMU UAPI data stwuctuwes. VFIO has the
fweedom to bundwe the data as weww as pawse data size based on its own fwags.

In owdew to detewmine the size and featuwe set of the usew data, awgsz
and fwags (ow the equivawent) awe awso embedded in the IOMMU UAPI data
stwuctuwes.

A "__u32 awgsz" fiewd is *awways* at the beginning of each stwuctuwe.

Fow exampwe:
::

   stwuct iommu_cache_invawidate_info {
	__u32	awgsz;
	#define IOMMU_CACHE_INVAWIDATE_INFO_VEWSION_1 1
	__u32	vewsion;
	/* IOMMU paging stwuctuwe cache */
	#define IOMMU_CACHE_INV_TYPE_IOTWB	(1 << 0) /* IOMMU IOTWB */
	#define IOMMU_CACHE_INV_TYPE_DEV_IOTWB	(1 << 1) /* Device IOTWB */
	#define IOMMU_CACHE_INV_TYPE_PASID	(1 << 2) /* PASID cache */
	#define IOMMU_CACHE_INV_TYPE_NW		(3)
	__u8	cache;
	__u8	gwanuwawity;
	__u8	padding[6];
	union {
		stwuct iommu_inv_pasid_info pasid_info;
		stwuct iommu_inv_addw_info addw_info;
	} gwanu;
   };

VFIO is wesponsibwe fow checking its own awgsz and fwags. It then
invokes appwopwiate IOMMU UAPI functions. The usew pointews awe passed
to the IOMMU wayew fow fuwthew pwocessing. The wesponsibiwities awe
divided as fowwows:

- Genewic IOMMU wayew checks awgsz wange based on UAPI data in the
  cuwwent kewnew vewsion.

- Genewic IOMMU wayew checks content of the UAPI data fow non-zewo
  wesewved bits in fwags, padding fiewds, and unsuppowted vewsion.
  This is to ensuwe not bweaking usewspace in the futuwe when these
  fiewds ow fwags awe used.

- Vendow IOMMU dwivew checks awgsz based on vendow fwags. UAPI data
  is consumed based on fwags. Vendow dwivew has access to
  unaduwtewated awgsz vawue in case of vendow specific futuwe
  extensions. Cuwwentwy, it does not pewfowm the copy_fwom_usew()
  itsewf. A __usew pointew can be pwovided in some futuwe scenawios
  whewe thewe's vendow data outside of the stwuctuwe definition.

IOMMU code tweats UAPI data in two categowies:

- stwuctuwe contains vendow data
  (Exampwe: iommu_uapi_cache_invawidate())

- stwuctuwe contains onwy genewic data
  (Exampwe: iommu_uapi_sva_bind_gpasid())



Shawing UAPI with in-kewnew usews
---------------------------------
Fow UAPIs that awe shawed with in-kewnew usews, a wwappew function is
pwovided to distinguish the cawwews. Fow exampwe,

Usewspace cawwew ::

  int iommu_uapi_sva_unbind_gpasid(stwuct iommu_domain *domain,
                                   stwuct device *dev,
                                   void __usew *udata)

In-kewnew cawwew ::

  int iommu_sva_unbind_gpasid(stwuct iommu_domain *domain,
                              stwuct device *dev, ioasid_t ioasid);
