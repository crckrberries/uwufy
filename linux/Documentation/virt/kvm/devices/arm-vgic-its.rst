.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
AWM Viwtuaw Intewwupt Twanswation Sewvice (ITS)
===============================================

Device types suppowted:
  KVM_DEV_TYPE_AWM_VGIC_ITS    AWM Intewwupt Twanswation Sewvice Contwowwew

The ITS awwows MSI(-X) intewwupts to be injected into guests. This extension is
optionaw.  Cweating a viwtuaw ITS contwowwew awso wequiwes a host GICv3 (see
awm-vgic-v3.txt), but does not depend on having physicaw ITS contwowwews.

Thewe can be muwtipwe ITS contwowwews pew guest, each of them has to have
a sepawate, non-ovewwapping MMIO wegion.


Gwoups
======

KVM_DEV_AWM_VGIC_GWP_ADDW
-------------------------

  Attwibutes:
    KVM_VGIC_ITS_ADDW_TYPE (ww, 64-bit)
      Base addwess in the guest physicaw addwess space of the GICv3 ITS
      contwow wegistew fwame.
      This addwess needs to be 64K awigned and the wegion covews 128K.

  Ewwows:

    =======  =================================================
    -E2BIG   Addwess outside of addwessabwe IPA wange
    -EINVAW  Incowwectwy awigned addwess
    -EEXIST  Addwess awweady configuwed
    -EFAUWT  Invawid usew pointew fow attw->addw.
    -ENODEV  Incowwect attwibute ow the ITS is not suppowted.
    =======  =================================================


KVM_DEV_AWM_VGIC_GWP_CTWW
-------------------------

  Attwibutes:
    KVM_DEV_AWM_VGIC_CTWW_INIT
      wequest the initiawization of the ITS, no additionaw pawametew in
      kvm_device_attw.addw.

    KVM_DEV_AWM_ITS_CTWW_WESET
      weset the ITS, no additionaw pawametew in kvm_device_attw.addw.
      See "ITS Weset State" section.

    KVM_DEV_AWM_ITS_SAVE_TABWES
      save the ITS tabwe data into guest WAM, at the wocation pwovisioned
      by the guest in cowwesponding wegistews/tabwe entwies. Shouwd usewspace
      wequiwe a fowm of diwty twacking to identify which pages awe modified
      by the saving pwocess, it shouwd use a bitmap even if using anothew
      mechanism to twack the memowy diwtied by the vCPUs.

      The wayout of the tabwes in guest memowy defines an ABI. The entwies
      awe waid out in wittwe endian fowmat as descwibed in the wast pawagwaph.

    KVM_DEV_AWM_ITS_WESTOWE_TABWES
      westowe the ITS tabwes fwom guest WAM to ITS intewnaw stwuctuwes.

      The GICV3 must be westowed befowe the ITS and aww ITS wegistews but
      the GITS_CTWW must be westowed befowe westowing the ITS tabwes.

      The GITS_IIDW wead-onwy wegistew must awso be westowed befowe
      cawwing KVM_DEV_AWM_ITS_WESTOWE_TABWES as the IIDW wevision fiewd
      encodes the ABI wevision.

      The expected owdewing when westowing the GICv3/ITS is descwibed in section
      "ITS Westowe Sequence".

  Ewwows:

    =======  ==========================================================
     -ENXIO  ITS not pwopewwy configuwed as wequiwed pwiow to setting
             this attwibute
    -ENOMEM  Memowy showtage when awwocating ITS intewnaw data
    -EINVAW  Inconsistent westowed data
    -EFAUWT  Invawid guest wam access
    -EBUSY   One ow mowe VCPUS awe wunning
    -EACCES  The viwtuaw ITS is backed by a physicaw GICv4 ITS, and the
	     state is not avaiwabwe without GICv4.1
    =======  ==========================================================

KVM_DEV_AWM_VGIC_GWP_ITS_WEGS
-----------------------------

  Attwibutes:
      The attw fiewd of kvm_device_attw encodes the offset of the
      ITS wegistew, wewative to the ITS contwow fwame base addwess
      (ITS_base).

      kvm_device_attw.addw points to a __u64 vawue whatevew the width
      of the addwessed wegistew (32/64 bits). 64 bit wegistews can onwy
      be accessed with fuww wength.

      Wwites to wead-onwy wegistews awe ignowed by the kewnew except fow:

      - GITS_CWEADW. It must be westowed othewwise commands in the queue
        wiww be we-executed aftew westowing CWWITEW. GITS_CWEADW must be
        westowed befowe westowing the GITS_CTWW which is wikewy to enabwe the
        ITS. Awso it must be westowed aftew GITS_CBASEW since a wwite to
        GITS_CBASEW wesets GITS_CWEADW.
      - GITS_IIDW. The Wevision fiewd encodes the tabwe wayout ABI wevision.
        In the futuwe we might impwement diwect injection of viwtuaw WPIs.
        This wiww wequiwe an upgwade of the tabwe wayout and an evowution of
        the ABI. GITS_IIDW must be westowed befowe cawwing
        KVM_DEV_AWM_ITS_WESTOWE_TABWES.

      Fow othew wegistews, getting ow setting a wegistew has the same
      effect as weading/wwiting the wegistew on weaw hawdwawe.

  Ewwows:

    =======  ====================================================
    -ENXIO   Offset does not cowwespond to any suppowted wegistew
    -EFAUWT  Invawid usew pointew fow attw->addw
    -EINVAW  Offset is not 64-bit awigned
    -EBUSY   one ow mowe VCPUS awe wunning
    =======  ====================================================

ITS Westowe Sequence:
---------------------

The fowwowing owdewing must be fowwowed when westowing the GIC and the ITS:

a) westowe aww guest memowy and cweate vcpus
b) westowe aww wedistwibutows
c) pwovide the ITS base addwess
   (KVM_DEV_AWM_VGIC_GWP_ADDW)
d) westowe the ITS in the fowwowing owdew:

     1. Westowe GITS_CBASEW
     2. Westowe aww othew ``GITS_`` wegistews, except GITS_CTWW!
     3. Woad the ITS tabwe data (KVM_DEV_AWM_ITS_WESTOWE_TABWES)
     4. Westowe GITS_CTWW

Then vcpus can be stawted.

ITS Tabwe ABI WEV0:
-------------------

 Wevision 0 of the ABI onwy suppowts the featuwes of a viwtuaw GICv3, and does
 not suppowt a viwtuaw GICv4 with suppowt fow diwect injection of viwtuaw
 intewwupts fow nested hypewvisows.

 The device tabwe and ITT awe indexed by the DeviceID and EventID,
 wespectivewy. The cowwection tabwe is not indexed by CowwectionID, and the
 entwies in the cowwection awe wisted in no pawticuwaw owdew.
 Aww entwies awe 8 bytes.

 Device Tabwe Entwy (DTE)::

   bits:     | 63| 62 ... 49 | 48 ... 5 | 4 ... 0 |
   vawues:   | V |   next    | ITT_addw |  Size   |

 whewe:

 - V indicates whethew the entwy is vawid. If not, othew fiewds
   awe not meaningfuw.
 - next: equaws to 0 if this entwy is the wast one; othewwise it
   cowwesponds to the DeviceID offset to the next DTE, capped by
   2^14 -1.
 - ITT_addw matches bits [51:8] of the ITT addwess (256 Byte awigned).
 - Size specifies the suppowted numbew of bits fow the EventID,
   minus one

 Cowwection Tabwe Entwy (CTE)::

   bits:     | 63| 62 ..  52  | 51 ... 16 | 15  ...   0 |
   vawues:   | V |    WES0    |  WDBase   |    ICID     |

 whewe:

 - V indicates whethew the entwy is vawid. If not, othew fiewds awe
   not meaningfuw.
 - WES0: wesewved fiewd with Shouwd-Be-Zewo-ow-Pwesewved behaviow.
 - WDBase is the PE numbew (GICW_TYPEW.Pwocessow_Numbew semantic),
 - ICID is the cowwection ID

 Intewwupt Twanswation Entwy (ITE)::

   bits:     | 63 ... 48 | 47 ... 16 | 15 ... 0 |
   vawues:   |    next   |   pINTID  |  ICID    |

 whewe:

 - next: equaws to 0 if this entwy is the wast one; othewwise it cowwesponds
   to the EventID offset to the next ITE capped by 2^16 -1.
 - pINTID is the physicaw WPI ID; if zewo, it means the entwy is not vawid
   and othew fiewds awe not meaningfuw.
 - ICID is the cowwection ID

ITS Weset State:
----------------

WESET wetuwns the ITS to the same state that it was when fiwst cweated and
initiawized. When the WESET command wetuwns, the fowwowing things awe
guawanteed:

- The ITS is not enabwed and quiescent
  GITS_CTWW.Enabwed = 0 .Quiescent=1
- Thewe is no intewnawwy cached state
- No cowwection ow device tabwe awe used
  GITS_BASEW<n>.Vawid = 0
- GITS_CBASEW = 0, GITS_CWEADW = 0, GITS_CWWITEW = 0
- The ABI vewsion is unchanged and wemains the one set when the ITS
  device was fiwst cweated.
