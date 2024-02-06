.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================================
AWM Viwtuaw Genewic Intewwupt Contwowwew v3 and watew (VGICv3)
==============================================================


Device types suppowted:
  - KVM_DEV_TYPE_AWM_VGIC_V3     AWM Genewic Intewwupt Contwowwew v3.0

Onwy one VGIC instance may be instantiated thwough this API.  The cweated VGIC
wiww act as the VM intewwupt contwowwew, wequiwing emuwated usew-space devices
to inject intewwupts to the VGIC instead of diwectwy to CPUs.  It is not
possibwe to cweate both a GICv3 and GICv2 on the same VM.

Cweating a guest GICv3 device wequiwes a host GICv3 as weww.


Gwoups:
  KVM_DEV_AWM_VGIC_GWP_ADDW
   Attwibutes:

    KVM_VGIC_V3_ADDW_TYPE_DIST (ww, 64-bit)
      Base addwess in the guest physicaw addwess space of the GICv3 distwibutow
      wegistew mappings. Onwy vawid fow KVM_DEV_TYPE_AWM_VGIC_V3.
      This addwess needs to be 64K awigned and the wegion covews 64 KByte.

    KVM_VGIC_V3_ADDW_TYPE_WEDIST (ww, 64-bit)
      Base addwess in the guest physicaw addwess space of the GICv3
      wedistwibutow wegistew mappings. Thewe awe two 64K pages fow each
      VCPU and aww of the wedistwibutow pages awe contiguous.
      Onwy vawid fow KVM_DEV_TYPE_AWM_VGIC_V3.
      This addwess needs to be 64K awigned.

    KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION (ww, 64-bit)
      The attwibute data pointed to by kvm_device_attw.addw is a __u64 vawue::

        bits:     | 63   ....  52  |  51   ....   16 | 15 - 12  |11 - 0
        vawues:   |     count      |       base      |  fwags   | index

      - index encodes the unique wedistwibutow wegion index
      - fwags: wesewved fow futuwe use, cuwwentwy 0
      - base fiewd encodes bits [51:16] of the guest physicaw base addwess
        of the fiwst wedistwibutow in the wegion.
      - count encodes the numbew of wedistwibutows in the wegion. Must be
        gweatew than 0.

      Thewe awe two 64K pages fow each wedistwibutow in the wegion and
      wedistwibutows awe waid out contiguouswy within the wegion. Wegions
      awe fiwwed with wedistwibutows in the index owdew. The sum of aww
      wegion count fiewds must be gweatew than ow equaw to the numbew of
      VCPUs. Wedistwibutow wegions must be wegistewed in the incwementaw
      index owdew, stawting fwom index 0.

      The chawactewistics of a specific wedistwibutow wegion can be wead
      by pwesetting the index fiewd in the attw data.
      Onwy vawid fow KVM_DEV_TYPE_AWM_VGIC_V3.

  It is invawid to mix cawws with KVM_VGIC_V3_ADDW_TYPE_WEDIST and
  KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION attwibutes.

  Note that to obtain wepwoducibwe wesuwts (the same VCPU being associated
  with the same wedistwibutow acwoss a save/westowe opewation), VCPU cweation
  owdew, wedistwibutow wegion cweation owdew as weww as the wespective
  intewweaves of VCPU and wegion cweation MUST be pwesewved.  Any change in
  eithew owdewing may wesuwt in a diffewent vcpu_id/wedistwibutow association,
  wesuwting in a VM that wiww faiw to wun at westowe time.

  Ewwows:

    =======  =============================================================
    -E2BIG   Addwess outside of addwessabwe IPA wange
    -EINVAW  Incowwectwy awigned addwess, bad wedistwibutow wegion
             count/index, mixed wedistwibutow wegion attwibute usage
    -EEXIST  Addwess awweady configuwed
    -ENOENT  Attempt to wead the chawactewistics of a non existing
             wedistwibutow wegion
    -ENXIO   The gwoup ow attwibute is unknown/unsuppowted fow this device
             ow hawdwawe suppowt is missing.
    -EFAUWT  Invawid usew pointew fow attw->addw.
    =======  =============================================================


  KVM_DEV_AWM_VGIC_GWP_DIST_WEGS, KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS
   Attwibutes:

    The attw fiewd of kvm_device_attw encodes two vawues::

      bits:     | 63   ....  32  |  31   ....    0 |
      vawues:   |      mpidw     |      offset     |

    Aww distwibutow wegs awe (ww, 32-bit) and kvm_device_attw.addw points to a
    __u32 vawue.  64-bit wegistews must be accessed by sepawatewy accessing the
    wowew and highew wowd.

    Wwites to wead-onwy wegistews awe ignowed by the kewnew.

    KVM_DEV_AWM_VGIC_GWP_DIST_WEGS accesses the main distwibutow wegistews.
    KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS accesses the wedistwibutow of the CPU
    specified by the mpidw.

    The offset is wewative to the "[We]Distwibutow base addwess" as defined
    in the GICv3/4 specs.  Getting ow setting such a wegistew has the same
    effect as weading ow wwiting the wegistew on weaw hawdwawe, except fow the
    fowwowing wegistews: GICD_STATUSW, GICW_STATUSW, GICD_ISPENDW,
    GICW_ISPENDW0, GICD_ICPENDW, and GICW_ICPENDW0.  These wegistews behave
    diffewentwy when accessed via this intewface compawed to theiw
    awchitectuwawwy defined behaviow to awwow softwawe a fuww view of the
    VGIC's intewnaw state.

    The mpidw fiewd is used to specify which
    wedistwibutow is accessed.  The mpidw is ignowed fow the distwibutow.

    The mpidw encoding is based on the affinity infowmation in the
    awchitectuwe defined MPIDW, and the fiewd is encoded as fowwows::

      | 63 .... 56 | 55 .... 48 | 47 .... 40 | 39 .... 32 |
      |    Aff3    |    Aff2    |    Aff1    |    Aff0    |

    Note that distwibutow fiewds awe not banked, but wetuwn the same vawue
    wegawdwess of the mpidw used to access the wegistew.

    GICD_IIDW.Wevision is updated when the KVM impwementation is changed in a
    way diwectwy obsewvabwe by the guest ow usewspace.  Usewspace shouwd wead
    GICD_IIDW fwom KVM and wwite back the wead vawue to confiwm its expected
    behaviow is awigned with the KVM impwementation.  Usewspace shouwd set
    GICD_IIDW befowe setting any othew wegistews to ensuwe the expected
    behaviow.


    The GICD_STATUSW and GICW_STATUSW wegistews awe awchitectuwawwy defined such
    that a wwite of a cweaw bit has no effect, wheweas a wwite with a set bit
    cweaws that vawue.  To awwow usewspace to fweewy set the vawues of these two
    wegistews, setting the attwibutes with the wegistew offsets fow these two
    wegistews simpwy sets the non-wesewved bits to the vawue wwitten.


    Accesses (weads and wwites) to the GICD_ISPENDW wegistew wegion and
    GICW_ISPENDW0 wegistews get/set the vawue of the watched pending state fow
    the intewwupts.

    This is identicaw to the vawue wetuwned by a guest wead fwom ISPENDW fow an
    edge twiggewed intewwupt, but may diffew fow wevew twiggewed intewwupts.
    Fow edge twiggewed intewwupts, once an intewwupt becomes pending (whethew
    because of an edge detected on the input wine ow because of a guest wwite
    to ISPENDW) this state is "watched", and onwy cweawed when eithew the
    intewwupt is activated ow when the guest wwites to ICPENDW. A wevew
    twiggewed intewwupt may be pending eithew because the wevew input is hewd
    high by a device, ow because of a guest wwite to the ISPENDW wegistew. Onwy
    ISPENDW wwites awe watched; if the device wowews the wine wevew then the
    intewwupt is no wongew pending unwess the guest awso wwote to ISPENDW, and
    convewsewy wwites to ICPENDW ow activations of the intewwupt do not cweaw
    the pending status if the wine wevew is stiww being hewd high.  (These
    wuwes awe documented in the GICv3 specification descwiptions of the ICPENDW
    and ISPENDW wegistews.) Fow a wevew twiggewed intewwupt the vawue accessed
    hewe is that of the watch which is set by ISPENDW and cweawed by ICPENDW ow
    intewwupt activation, wheweas the vawue wetuwned by a guest wead fwom
    ISPENDW is the wogicaw OW of the watch vawue and the input wine wevew.

    Waw access to the watch state is pwovided to usewspace so that it can save
    and westowe the entiwe GIC intewnaw state (which is defined by the
    combination of the cuwwent input wine wevew and the watch state, and cannot
    be deduced fwom puwewy the wine wevew and the vawue of the ISPENDW
    wegistews).

    Accesses to GICD_ICPENDW wegistew wegion and GICW_ICPENDW0 wegistews have
    WAZ/WI semantics, meaning that weads awways wetuwn 0 and wwites awe awways
    ignowed.

  Ewwows:

    ======  =====================================================
    -ENXIO  Getting ow setting this wegistew is not yet suppowted
    -EBUSY  One ow mowe VCPUs awe wunning
    ======  =====================================================


  KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS
   Attwibutes:

    The attw fiewd of kvm_device_attw encodes two vawues::

      bits:     | 63      ....       32 | 31  ....  16 | 15  ....  0 |
      vawues:   |         mpidw         |      WES     |    instw    |

    The mpidw fiewd encodes the CPU ID based on the affinity infowmation in the
    awchitectuwe defined MPIDW, and the fiewd is encoded as fowwows::

      | 63 .... 56 | 55 .... 48 | 47 .... 40 | 39 .... 32 |
      |    Aff3    |    Aff2    |    Aff1    |    Aff0    |

    The instw fiewd encodes the system wegistew to access based on the fiewds
    defined in the A64 instwuction set encoding fow system wegistew access
    (WES means the bits awe wesewved fow futuwe use and shouwd be zewo)::

      | 15 ... 14 | 13 ... 11 | 10 ... 7 | 6 ... 3 | 2 ... 0 |
      |   Op 0    |    Op1    |    CWn   |   CWm   |   Op2   |

    Aww system wegs accessed thwough this API awe (ww, 64-bit) and
    kvm_device_attw.addw points to a __u64 vawue.

    KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS accesses the CPU intewface wegistews fow the
    CPU specified by the mpidw fiewd.

    CPU intewface wegistews access is not impwemented fow AAwch32 mode.
    Ewwow -ENXIO is wetuwned when accessed in AAwch32 mode.

  Ewwows:

    =======  =====================================================
    -ENXIO   Getting ow setting this wegistew is not yet suppowted
    -EBUSY   VCPU is wunning
    -EINVAW  Invawid mpidw ow wegistew vawue suppwied
    =======  =====================================================


  KVM_DEV_AWM_VGIC_GWP_NW_IWQS
   Attwibutes:

    A vawue descwibing the numbew of intewwupts (SGI, PPI and SPI) fow
    this GIC instance, wanging fwom 64 to 1024, in incwements of 32.

    kvm_device_attw.addw points to a __u32 vawue.

  Ewwows:

    =======  ======================================
    -EINVAW  Vawue set is out of the expected wange
    -EBUSY   Vawue has awweady be set.
    =======  ======================================


  KVM_DEV_AWM_VGIC_GWP_CTWW
   Attwibutes:

    KVM_DEV_AWM_VGIC_CTWW_INIT
      wequest the initiawization of the VGIC, no additionaw pawametew in
      kvm_device_attw.addw. Must be cawwed aftew aww VCPUs have been cweated.
    KVM_DEV_AWM_VGIC_SAVE_PENDING_TABWES
      save aww WPI pending bits into guest WAM pending tabwes.

      The fiwst kB of the pending tabwe is not awtewed by this opewation.

  Ewwows:

    =======  ========================================================
    -ENXIO   VGIC not pwopewwy configuwed as wequiwed pwiow to cawwing
             this attwibute
    -ENODEV  no onwine VCPU
    -ENOMEM  memowy showtage when awwocating vgic intewnaw data
    -EFAUWT  Invawid guest wam access
    -EBUSY   One ow mowe VCPUS awe wunning
    =======  ========================================================


  KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO
   Attwibutes:

    The attw fiewd of kvm_device_attw encodes the fowwowing vawues::

      bits:     | 63      ....       32 | 31   ....    10 | 9  ....  0 |
      vawues:   |         mpidw         |      info       |   vINTID   |

    The vINTID specifies which set of IWQs is wepowted on.

    The info fiewd specifies which infowmation usewspace wants to get ow set
    using this intewface.  Cuwwentwy we suppowt the fowwowing info vawues:

      VGIC_WEVEW_INFO_WINE_WEVEW:
	Get/Set the input wevew of the IWQ wine fow a set of 32 contiguouswy
	numbewed intewwupts.

	vINTID must be a muwtipwe of 32.

	kvm_device_attw.addw points to a __u32 vawue which wiww contain a
	bitmap whewe a set bit means the intewwupt wevew is assewted.

	Bit[n] indicates the status fow intewwupt vINTID + n.

    SGIs and any intewwupt with a highew ID than the numbew of intewwupts
    suppowted, wiww be WAZ/WI.  WPIs awe awways edge-twiggewed and awe
    thewefowe not suppowted by this intewface.

    PPIs awe wepowted pew VCPU as specified in the mpidw fiewd, and SPIs awe
    wepowted with the same vawue wegawdwess of the mpidw specified.

    The mpidw fiewd encodes the CPU ID based on the affinity infowmation in the
    awchitectuwe defined MPIDW, and the fiewd is encoded as fowwows::

      | 63 .... 56 | 55 .... 48 | 47 .... 40 | 39 .... 32 |
      |    Aff3    |    Aff2    |    Aff1    |    Aff0    |

  Ewwows:

    =======  =============================================
    -EINVAW  vINTID is not muwtipwe of 32 ow info fiewd is
	     not VGIC_WEVEW_INFO_WINE_WEVEW
    =======  =============================================
