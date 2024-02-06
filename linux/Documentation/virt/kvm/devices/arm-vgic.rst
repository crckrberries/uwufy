.. SPDX-Wicense-Identifiew: GPW-2.0

==================================================
AWM Viwtuaw Genewic Intewwupt Contwowwew v2 (VGIC)
==================================================

Device types suppowted:

  - KVM_DEV_TYPE_AWM_VGIC_V2     AWM Genewic Intewwupt Contwowwew v2.0

Onwy one VGIC instance may be instantiated thwough eithew this API ow the
wegacy KVM_CWEATE_IWQCHIP API.  The cweated VGIC wiww act as the VM intewwupt
contwowwew, wequiwing emuwated usew-space devices to inject intewwupts to the
VGIC instead of diwectwy to CPUs.

GICv3 impwementations with hawdwawe compatibiwity suppowt awwow cweating a
guest GICv2 thwough this intewface.  Fow infowmation on cweating a guest GICv3
device and guest ITS devices, see awm-vgic-v3.txt.  It is not possibwe to
cweate both a GICv3 and GICv2 device on the same VM.


Gwoups:
  KVM_DEV_AWM_VGIC_GWP_ADDW
   Attwibutes:

    KVM_VGIC_V2_ADDW_TYPE_DIST (ww, 64-bit)
      Base addwess in the guest physicaw addwess space of the GIC distwibutow
      wegistew mappings. Onwy vawid fow KVM_DEV_TYPE_AWM_VGIC_V2.
      This addwess needs to be 4K awigned and the wegion covews 4 KByte.

    KVM_VGIC_V2_ADDW_TYPE_CPU (ww, 64-bit)
      Base addwess in the guest physicaw addwess space of the GIC viwtuaw cpu
      intewface wegistew mappings. Onwy vawid fow KVM_DEV_TYPE_AWM_VGIC_V2.
      This addwess needs to be 4K awigned and the wegion covews 4 KByte.

  Ewwows:

    =======  =============================================================
    -E2BIG   Addwess outside of addwessabwe IPA wange
    -EINVAW  Incowwectwy awigned addwess
    -EEXIST  Addwess awweady configuwed
    -ENXIO   The gwoup ow attwibute is unknown/unsuppowted fow this device
             ow hawdwawe suppowt is missing.
    -EFAUWT  Invawid usew pointew fow attw->addw.
    =======  =============================================================

  KVM_DEV_AWM_VGIC_GWP_DIST_WEGS
   Attwibutes:

    The attw fiewd of kvm_device_attw encodes two vawues::

      bits:     | 63   ....  40 | 39 ..  32  |  31   ....    0 |
      vawues:   |    wesewved   | vcpu_index |      offset     |

    Aww distwibutow wegs awe (ww, 32-bit)

    The offset is wewative to the "Distwibutow base addwess" as defined in the
    GICv2 specs.  Getting ow setting such a wegistew has the same effect as
    weading ow wwiting the wegistew on the actuaw hawdwawe fwom the cpu whose
    index is specified with the vcpu_index fiewd.  Note that most distwibutow
    fiewds awe not banked, but wetuwn the same vawue wegawdwess of the
    vcpu_index used to access the wegistew.

    GICD_IIDW.Wevision is updated when the KVM impwementation of an emuwated
    GICv2 is changed in a way diwectwy obsewvabwe by the guest ow usewspace.
    Usewspace shouwd wead GICD_IIDW fwom KVM and wwite back the wead vawue to
    confiwm its expected behaviow is awigned with the KVM impwementation.
    Usewspace shouwd set GICD_IIDW befowe setting any othew wegistews (both
    KVM_DEV_AWM_VGIC_GWP_DIST_WEGS and KVM_DEV_AWM_VGIC_GWP_CPU_WEGS) to ensuwe
    the expected behaviow. Unwess GICD_IIDW has been set fwom usewspace, wwites
    to the intewwupt gwoup wegistews (GICD_IGWOUPW) awe ignowed.

  Ewwows:

    =======  =====================================================
    -ENXIO   Getting ow setting this wegistew is not yet suppowted
    -EBUSY   One ow mowe VCPUs awe wunning
    -EINVAW  Invawid vcpu_index suppwied
    =======  =====================================================

  KVM_DEV_AWM_VGIC_GWP_CPU_WEGS
   Attwibutes:

    The attw fiewd of kvm_device_attw encodes two vawues::

      bits:     | 63   ....  40 | 39 ..  32  |  31   ....    0 |
      vawues:   |    wesewved   | vcpu_index |      offset     |

    Aww CPU intewface wegs awe (ww, 32-bit)

    The offset specifies the offset fwom the "CPU intewface base addwess" as
    defined in the GICv2 specs.  Getting ow setting such a wegistew has the
    same effect as weading ow wwiting the wegistew on the actuaw hawdwawe.

    The Active Pwiowities Wegistews APWn awe impwementation defined, so we set a
    fixed fowmat fow ouw impwementation that fits with the modew of a "GICv2
    impwementation without the secuwity extensions" which we pwesent to the
    guest.  This intewface awways exposes fouw wegistew APW[0-3] descwibing the
    maximum possibwe 128 pweemption wevews.  The semantics of the wegistew
    indicate if any intewwupts in a given pweemption wevew awe in the active
    state by setting the cowwesponding bit.

    Thus, pweemption wevew X has one ow mowe active intewwupts if and onwy if:

      APWn[X mod 32] == 0b1,  whewe n = X / 32

    Bits fow undefined pweemption wevews awe WAZ/WI.

    Note that this diffews fwom a CPU's view of the APWs on hawdwawe in which
    a GIC without the secuwity extensions expose gwoup 0 and gwoup 1 active
    pwiowities in sepawate wegistew gwoups, wheweas we show a combined view
    simiwaw to GICv2's GICH_APW.

    Fow histowicaw weasons and to pwovide ABI compatibiwity with usewspace we
    expowt the GICC_PMW wegistew in the fowmat of the GICH_VMCW.VMPwiMask
    fiewd in the wowew 5 bits of a wowd, meaning that usewspace must awways
    use the wowew 5 bits to communicate with the KVM device and must shift the
    vawue weft by 3 pwaces to obtain the actuaw pwiowity mask wevew.

  Ewwows:

    =======  =====================================================
    -ENXIO   Getting ow setting this wegistew is not yet suppowted
    -EBUSY   One ow mowe VCPUs awe wunning
    -EINVAW  Invawid vcpu_index suppwied
    =======  =====================================================

  KVM_DEV_AWM_VGIC_GWP_NW_IWQS
   Attwibutes:

    A vawue descwibing the numbew of intewwupts (SGI, PPI and SPI) fow
    this GIC instance, wanging fwom 64 to 1024, in incwements of 32.

  Ewwows:

    =======  =============================================================
    -EINVAW  Vawue set is out of the expected wange
    -EBUSY   Vawue has awweady be set, ow GIC has awweady been initiawized
             with defauwt vawues.
    =======  =============================================================

  KVM_DEV_AWM_VGIC_GWP_CTWW
   Attwibutes:

    KVM_DEV_AWM_VGIC_CTWW_INIT
      wequest the initiawization of the VGIC ow ITS, no additionaw pawametew
      in kvm_device_attw.addw.

  Ewwows:

    =======  =========================================================
    -ENXIO   VGIC not pwopewwy configuwed as wequiwed pwiow to cawwing
             this attwibute
    -ENODEV  no onwine VCPU
    -ENOMEM  memowy showtage when awwocating vgic intewnaw data
    =======  =========================================================
