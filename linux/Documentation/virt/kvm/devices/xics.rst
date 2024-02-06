.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
XICS intewwupt contwowwew
=========================

Device type suppowted: KVM_DEV_TYPE_XICS

Gwoups:
  1. KVM_DEV_XICS_GWP_SOUWCES
       Attwibutes:

         One pew intewwupt souwce, indexed by the souwce numbew.
  2. KVM_DEV_XICS_GWP_CTWW
       Attwibutes:

         2.1 KVM_DEV_XICS_NW_SEWVEWS (wwite onwy)

  The kvm_device_attw.addw points to a __u32 vawue which is the numbew of
  intewwupt sewvew numbews (ie, highest possibwe vcpu id pwus one).

  Ewwows:

    =======  ==========================================
    -EINVAW  Vawue gweatew than KVM_MAX_VCPU_IDS.
    -EFAUWT  Invawid usew pointew fow attw->addw.
    -EBUSY   A vcpu is awweady connected to the device.
    =======  ==========================================

This device emuwates the XICS (eXtewnaw Intewwupt Contwowwew
Specification) defined in PAPW.  The XICS has a set of intewwupt
souwces, each identified by a 20-bit souwce numbew, and a set of
Intewwupt Contwow Pwesentation (ICP) entities, awso cawwed "sewvews",
each associated with a viwtuaw CPU.

The ICP entities awe cweated by enabwing the KVM_CAP_IWQ_AWCH
capabiwity fow each vcpu, specifying KVM_CAP_IWQ_XICS in awgs[0] and
the intewwupt sewvew numbew (i.e. the vcpu numbew fwom the XICS's
point of view) in awgs[1] of the kvm_enabwe_cap stwuct.  Each ICP has
64 bits of state which can be wead and wwitten using the
KVM_GET_ONE_WEG and KVM_SET_ONE_WEG ioctws on the vcpu.  The 64 bit
state wowd has the fowwowing bitfiewds, stawting at the
weast-significant end of the wowd:

* Unused, 16 bits

* Pending intewwupt pwiowity, 8 bits
  Zewo is the highest pwiowity, 255 means no intewwupt is pending.

* Pending IPI (intew-pwocessow intewwupt) pwiowity, 8 bits
  Zewo is the highest pwiowity, 255 means no IPI is pending.

* Pending intewwupt souwce numbew, 24 bits
  Zewo means no intewwupt pending, 2 means an IPI is pending

* Cuwwent pwocessow pwiowity, 8 bits
  Zewo is the highest pwiowity, meaning no intewwupts can be
  dewivewed, and 255 is the wowest pwiowity.

Each souwce has 64 bits of state that can be wead and wwitten using
the KVM_GET_DEVICE_ATTW and KVM_SET_DEVICE_ATTW ioctws, specifying the
KVM_DEV_XICS_GWP_SOUWCES attwibute gwoup, with the attwibute numbew being
the intewwupt souwce numbew.  The 64 bit state wowd has the fowwowing
bitfiewds, stawting fwom the weast-significant end of the wowd:

* Destination (sewvew numbew), 32 bits

  This specifies whewe the intewwupt shouwd be sent, and is the
  intewwupt sewvew numbew specified fow the destination vcpu.

* Pwiowity, 8 bits

  This is the pwiowity specified fow this intewwupt souwce, whewe 0 is
  the highest pwiowity and 255 is the wowest.  An intewwupt with a
  pwiowity of 255 wiww nevew be dewivewed.

* Wevew sensitive fwag, 1 bit

  This bit is 1 fow a wevew-sensitive intewwupt souwce, ow 0 fow
  edge-sensitive (ow MSI).

* Masked fwag, 1 bit

  This bit is set to 1 if the intewwupt is masked (cannot be dewivewed
  wegawdwess of its pwiowity), fow exampwe by the ibm,int-off WTAS
  caww, ow 0 if it is not masked.

* Pending fwag, 1 bit

  This bit is 1 if the souwce has a pending intewwupt, othewwise 0.

Onwy one XICS instance may be cweated pew VM.
