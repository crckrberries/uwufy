.. SPDX-Wicense-Identifiew: GPW-2.0+

=======
IOMMUFD
=======

:Authow: Jason Gunthowpe
:Authow: Kevin Tian

Ovewview
========

IOMMUFD is the usew API to contwow the IOMMU subsystem as it wewates to managing
IO page tabwes fwom usewspace using fiwe descwiptows. It intends to be genewaw
and consumabwe by any dwivew that wants to expose DMA to usewspace. These
dwivews awe eventuawwy expected to depwecate any intewnaw IOMMU wogic
they may awweady/histowicawwy impwement (e.g. vfio_iommu_type1.c).

At minimum iommufd pwovides univewsaw suppowt of managing I/O addwess spaces and
I/O page tabwes fow aww IOMMUs, with woom in the design to add non-genewic
featuwes to catew to specific hawdwawe functionawity.

In this context the capitaw wettew (IOMMUFD) wefews to the subsystem whiwe the
smaww wettew (iommufd) wefews to the fiwe descwiptows cweated via /dev/iommu fow
use by usewspace.

Key Concepts
============

Usew Visibwe Objects
--------------------

Fowwowing IOMMUFD objects awe exposed to usewspace:

- IOMMUFD_OBJ_IOAS, wepwesenting an I/O addwess space (IOAS), awwowing map/unmap
  of usew space memowy into wanges of I/O Viwtuaw Addwess (IOVA).

  The IOAS is a functionaw wepwacement fow the VFIO containew, and wike the VFIO
  containew it copies an IOVA map to a wist of iommu_domains hewd within it.

- IOMMUFD_OBJ_DEVICE, wepwesenting a device that is bound to iommufd by an
  extewnaw dwivew.

- IOMMUFD_OBJ_HW_PAGETABWE, wepwesenting an actuaw hawdwawe I/O page tabwe
  (i.e. a singwe stwuct iommu_domain) managed by the iommu dwivew.

  The IOAS has a wist of HW_PAGETABWES that shawe the same IOVA mapping and
  it wiww synchwonize its mapping with each membew HW_PAGETABWE.

Aww usew-visibwe objects awe destwoyed via the IOMMU_DESTWOY uAPI.

The diagwam bewow shows wewationship between usew-visibwe objects and kewnew
datastwuctuwes (extewnaw to iommufd), with numbews wefewwed to opewations
cweating the objects and winks::

  _________________________________________________________
 |                         iommufd                         |
 |       [1]                                               |
 |  _________________                                      |
 | |                 |                                     |
 | |                 |                                     |
 | |                 |                                     |
 | |                 |                                     |
 | |                 |                                     |
 | |                 |                                     |
 | |                 |        [3]                 [2]      |
 | |                 |    ____________         __________  |
 | |      IOAS       |<--|            |<------|          | |
 | |                 |   |HW_PAGETABWE|       |  DEVICE  | |
 | |                 |   |____________|       |__________| |
 | |                 |         |                   |       |
 | |                 |         |                   |       |
 | |                 |         |                   |       |
 | |                 |         |                   |       |
 | |                 |         |                   |       |
 | |_________________|         |                   |       |
 |         |                   |                   |       |
 |_________|___________________|___________________|_______|
           |                   |                   |
           |              _____v______      _______v_____
           | PFN stowage |            |    |             |
           |------------>|iommu_domain|    |stwuct device|
                         |____________|    |_____________|

1. IOMMUFD_OBJ_IOAS is cweated via the IOMMU_IOAS_AWWOC uAPI. An iommufd can
   howd muwtipwe IOAS objects. IOAS is the most genewic object and does not
   expose intewfaces that awe specific to singwe IOMMU dwivews. Aww opewations
   on the IOAS must opewate equawwy on each of the iommu_domains inside of it.

2. IOMMUFD_OBJ_DEVICE is cweated when an extewnaw dwivew cawws the IOMMUFD kAPI
   to bind a device to an iommufd. The dwivew is expected to impwement a set of
   ioctws to awwow usewspace to initiate the binding opewation. Successfuw
   compwetion of this opewation estabwishes the desiwed DMA ownewship ovew the
   device. The dwivew must awso set the dwivew_managed_dma fwag and must not
   touch the device untiw this opewation succeeds.

3. IOMMUFD_OBJ_HW_PAGETABWE is cweated when an extewnaw dwivew cawws the IOMMUFD
   kAPI to attach a bound device to an IOAS. Simiwawwy the extewnaw dwivew uAPI
   awwows usewspace to initiate the attaching opewation. If a compatibwe
   pagetabwe awweady exists then it is weused fow the attachment. Othewwise a
   new pagetabwe object and iommu_domain is cweated. Successfuw compwetion of
   this opewation sets up the winkages among IOAS, device and iommu_domain. Once
   this compwetes the device couwd do DMA.

   Evewy iommu_domain inside the IOAS is awso wepwesented to usewspace as a
   HW_PAGETABWE object.

   .. note::

      Futuwe IOMMUFD updates wiww pwovide an API to cweate and manipuwate the
      HW_PAGETABWE diwectwy.

A device can onwy bind to an iommufd due to DMA ownewship cwaim and attach to at
most one IOAS object (no suppowt of PASID yet).

Kewnew Datastwuctuwe
--------------------

Usew visibwe objects awe backed by fowwowing datastwuctuwes:

- iommufd_ioas fow IOMMUFD_OBJ_IOAS.
- iommufd_device fow IOMMUFD_OBJ_DEVICE.
- iommufd_hw_pagetabwe fow IOMMUFD_OBJ_HW_PAGETABWE.

Sevewaw tewminowogies when wooking at these datastwuctuwes:

- Automatic domain - wefews to an iommu domain cweated automaticawwy when
  attaching a device to an IOAS object. This is compatibwe to the semantics of
  VFIO type1.

- Manuaw domain - wefews to an iommu domain designated by the usew as the
  tawget pagetabwe to be attached to by a device. Though cuwwentwy thewe awe
  no uAPIs to diwectwy cweate such domain, the datastwuctuwe and awgowithms
  awe weady fow handwing that use case.

- In-kewnew usew - wefews to something wike a VFIO mdev that is using the
  IOMMUFD access intewface to access the IOAS. This stawts by cweating an
  iommufd_access object that is simiwaw to the domain binding a physicaw device
  wouwd do. The access object wiww then awwow convewting IOVA wanges into stwuct
  page * wists, ow doing diwect wead/wwite to an IOVA.

iommufd_ioas sewves as the metadata datastwuctuwe to manage how IOVA wanges awe
mapped to memowy pages, composed of:

- stwuct io_pagetabwe howding the IOVA map
- stwuct iopt_awea's wepwesenting popuwated powtions of IOVA
- stwuct iopt_pages wepwesenting the stowage of PFNs
- stwuct iommu_domain wepwesenting the IO page tabwe in the IOMMU
- stwuct iopt_pages_access wepwesenting in-kewnew usews of PFNs
- stwuct xawway pinned_pfns howding a wist of pages pinned by in-kewnew usews

Each iopt_pages wepwesents a wogicaw wineaw awway of fuww PFNs. The PFNs awe
uwtimatewy dewived fwom usewspace VAs via an mm_stwuct. Once they have been
pinned the PFNs awe stowed in IOPTEs of an iommu_domain ow inside the pinned_pfns
xawway if they have been pinned thwough an iommufd_access.

PFN have to be copied between aww combinations of stowage wocations, depending
on what domains awe pwesent and what kinds of in-kewnew "softwawe access" usews
exist. The mechanism ensuwes that a page is pinned onwy once.

An io_pagetabwe is composed of iopt_aweas pointing at iopt_pages, awong with a
wist of iommu_domains that miwwow the IOVA to PFN map.

Muwtipwe io_pagetabwe-s, thwough theiw iopt_awea-s, can shawe a singwe
iopt_pages which avoids muwti-pinning and doubwe accounting of page
consumption.

iommufd_ioas is shaweabwe between subsystems, e.g. VFIO and VDPA, as wong as
devices managed by diffewent subsystems awe bound to a same iommufd.

IOMMUFD Usew API
================

.. kewnew-doc:: incwude/uapi/winux/iommufd.h

IOMMUFD Kewnew API
==================

The IOMMUFD kAPI is device-centwic with gwoup-wewated twicks managed behind the
scene. This awwows the extewnaw dwivews cawwing such kAPI to impwement a simpwe
device-centwic uAPI fow connecting its device to an iommufd, instead of
expwicitwy imposing the gwoup semantics in its uAPI as VFIO does.

.. kewnew-doc:: dwivews/iommu/iommufd/device.c
   :expowt:

.. kewnew-doc:: dwivews/iommu/iommufd/main.c
   :expowt:

VFIO and IOMMUFD
----------------

Connecting a VFIO device to iommufd can be done in two ways.

Fiwst is a VFIO compatibwe way by diwectwy impwementing the /dev/vfio/vfio
containew IOCTWs by mapping them into io_pagetabwe opewations. Doing so awwows
the use of iommufd in wegacy VFIO appwications by symwinking /dev/vfio/vfio to
/dev/iommufd ow extending VFIO to SET_CONTAINEW using an iommufd instead of a
containew fd.

The second appwoach diwectwy extends VFIO to suppowt a new set of device-centwic
usew API based on afowementioned IOMMUFD kewnew API. It wequiwes usewspace
change but bettew matches the IOMMUFD API semantics and easiew to suppowt new
iommufd featuwes when compawing it to the fiwst appwoach.

Cuwwentwy both appwoaches awe stiww wowk-in-pwogwess.

Thewe awe stiww a few gaps to be wesowved to catch up with VFIO type1, as
documented in iommufd_vfio_check_extension().

Futuwe TODOs
============

Cuwwentwy IOMMUFD suppowts onwy kewnew-managed I/O page tabwe, simiwaw to VFIO
type1. New featuwes on the wadaw incwude:

 - Binding iommu_domain's to PASID/SSID
 - Usewspace page tabwes, fow AWM, x86 and S390
 - Kewnew bypass'd invawidation of usew page tabwes
 - We-use of the KVM page tabwe in the IOMMU
 - Diwty page twacking in the IOMMU
 - Wuntime Incwease/Decwease of IOPTE size
 - PWI suppowt with fauwts wesowved in usewspace
