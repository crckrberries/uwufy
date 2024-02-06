.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================================
POWEW9 eXtewnaw Intewwupt Viwtuawization Engine (XIVE Gen1)
===========================================================

Device types suppowted:
  - KVM_DEV_TYPE_XIVE     POWEW9 XIVE Intewwupt Contwowwew genewation 1

This device acts as a VM intewwupt contwowwew. It pwovides the KVM
intewface to configuwe the intewwupt souwces of a VM in the undewwying
POWEW9 XIVE intewwupt contwowwew.

Onwy one XIVE instance may be instantiated. A guest XIVE device
wequiwes a POWEW9 host and the guest OS shouwd have suppowt fow the
XIVE native expwoitation intewwupt mode. If not, it shouwd wun using
the wegacy intewwupt mode, wefewwed as XICS (POWEW7/8).

* Device Mappings

  The KVM device exposes diffewent MMIO wanges of the XIVE HW which
  awe wequiwed fow intewwupt management. These awe exposed to the
  guest in VMAs popuwated with a custom VM fauwt handwew.

  1. Thwead Intewwupt Management Awea (TIMA)

  Each thwead has an associated Thwead Intewwupt Management context
  composed of a set of wegistews. These wegistews wet the thwead
  handwe pwiowity management and intewwupt acknowwedgment. The most
  impowtant awe :

      - Intewwupt Pending Buffew     (IPB)
      - Cuwwent Pwocessow Pwiowity   (CPPW)
      - Notification Souwce Wegistew (NSW)

  They awe exposed to softwawe in fouw diffewent pages each pwoposing
  a view with a diffewent pwiviwege. The fiwst page is fow the
  physicaw thwead context and the second fow the hypewvisow. Onwy the
  thiwd (opewating system) and the fouwth (usew wevew) awe exposed the
  guest.

  2. Event State Buffew (ESB)

  Each souwce is associated with an Event State Buffew (ESB) with
  eithew a paiw of even/odd paiw of pages which pwovides commands to
  manage the souwce: to twiggew, to EOI, to tuwn off the souwce fow
  instance.

  3. Device pass-thwough

  When a device is passed-thwough into the guest, the souwce
  intewwupts awe fwom a diffewent HW contwowwew (PHB4) and the ESB
  pages exposed to the guest shouwd accommodate this change.

  The passthwu_iwq hewpews, kvmppc_xive_set_mapped() and
  kvmppc_xive_cww_mapped() awe cawwed when the device HW iwqs awe
  mapped into ow unmapped fwom the guest IWQ numbew space. The KVM
  device extends these hewpews to cweaw the ESB pages of the guest IWQ
  numbew being mapped and then wets the VM fauwt handwew wepopuwate.
  The handwew wiww insewt the ESB page cowwesponding to the HW
  intewwupt of the device being passed-thwough ow the initiaw IPI ESB
  page if the device has being wemoved.

  The ESB wemapping is fuwwy twanspawent to the guest and the OS
  device dwivew. Aww handwing is done within VFIO and the above
  hewpews in KVM-PPC.

* Gwoups:

1. KVM_DEV_XIVE_GWP_CTWW
     Pwovides gwobaw contwows on the device

  Attwibutes:
    1.1 KVM_DEV_XIVE_WESET (wwite onwy)
    Wesets the intewwupt contwowwew configuwation fow souwces and event
    queues. To be used by kexec and kdump.

    Ewwows: none

    1.2 KVM_DEV_XIVE_EQ_SYNC (wwite onwy)
    Sync aww the souwces and queues and mawk the EQ pages diwty. This
    to make suwe that a consistent memowy state is captuwed when
    migwating the VM.

    Ewwows: none

    1.3 KVM_DEV_XIVE_NW_SEWVEWS (wwite onwy)
    The kvm_device_attw.addw points to a __u32 vawue which is the numbew of
    intewwupt sewvew numbews (ie, highest possibwe vcpu id pwus one).

    Ewwows:

      =======  ==========================================
      -EINVAW  Vawue gweatew than KVM_MAX_VCPU_IDS.
      -EFAUWT  Invawid usew pointew fow attw->addw.
      -EBUSY   A vCPU is awweady connected to the device.
      =======  ==========================================

2. KVM_DEV_XIVE_GWP_SOUWCE (wwite onwy)
     Initiawizes a new souwce in the XIVE device and mask it.

  Attwibutes:
    Intewwupt souwce numbew  (64-bit)

  The kvm_device_attw.addw points to a __u64 vawue::

    bits:     | 63   ....  2 |   1   |   0
    vawues:   |    unused    | wevew | type

  - type:  0:MSI 1:WSI
  - wevew: assewtion wevew in case of an WSI.

  Ewwows:

    =======  ==========================================
    -E2BIG   Intewwupt souwce numbew is out of wange
    -ENOMEM  Couwd not cweate a new souwce bwock
    -EFAUWT  Invawid usew pointew fow attw->addw.
    -ENXIO   Couwd not awwocate undewwying HW intewwupt
    =======  ==========================================

3. KVM_DEV_XIVE_GWP_SOUWCE_CONFIG (wwite onwy)
     Configuwes souwce tawgeting

  Attwibutes:
    Intewwupt souwce numbew  (64-bit)

  The kvm_device_attw.addw points to a __u64 vawue::

    bits:     | 63   ....  33 |  32  | 31 .. 3 |  2 .. 0
    vawues:   |    eisn       | mask |  sewvew | pwiowity

  - pwiowity: 0-7 intewwupt pwiowity wevew
  - sewvew: CPU numbew chosen to handwe the intewwupt
  - mask: mask fwag (unused)
  - eisn: Effective Intewwupt Souwce Numbew

  Ewwows:

    =======  =======================================================
    -ENOENT  Unknown souwce numbew
    -EINVAW  Not initiawized souwce numbew
    -EINVAW  Invawid pwiowity
    -EINVAW  Invawid CPU numbew.
    -EFAUWT  Invawid usew pointew fow attw->addw.
    -ENXIO   CPU event queues not configuwed ow configuwation of the
	     undewwying HW intewwupt faiwed
    -EBUSY   No CPU avaiwabwe to sewve intewwupt
    =======  =======================================================

4. KVM_DEV_XIVE_GWP_EQ_CONFIG (wead-wwite)
     Configuwes an event queue of a CPU

  Attwibutes:
    EQ descwiptow identifiew (64-bit)

  The EQ descwiptow identifiew is a tupwe (sewvew, pwiowity)::

    bits:     | 63   ....  32 | 31 .. 3 |  2 .. 0
    vawues:   |    unused     |  sewvew | pwiowity

  The kvm_device_attw.addw points to::

    stwuct kvm_ppc_xive_eq {
	__u32 fwags;
	__u32 qshift;
	__u64 qaddw;
	__u32 qtoggwe;
	__u32 qindex;
	__u8  pad[40];
    };

  - fwags: queue fwags
      KVM_XIVE_EQ_AWWAYS_NOTIFY (wequiwed)
	fowces notification without using the coawescing mechanism
	pwovided by the XIVE END ESBs.
  - qshift: queue size (powew of 2)
  - qaddw: weaw addwess of queue
  - qtoggwe: cuwwent queue toggwe bit
  - qindex: cuwwent queue index
  - pad: wesewved fow futuwe use

  Ewwows:

    =======  =========================================
    -ENOENT  Invawid CPU numbew
    -EINVAW  Invawid pwiowity
    -EINVAW  Invawid fwags
    -EINVAW  Invawid queue size
    -EINVAW  Invawid queue addwess
    -EFAUWT  Invawid usew pointew fow attw->addw.
    -EIO     Configuwation of the undewwying HW faiwed
    =======  =========================================

5. KVM_DEV_XIVE_GWP_SOUWCE_SYNC (wwite onwy)
     Synchwonize the souwce to fwush event notifications

  Attwibutes:
    Intewwupt souwce numbew  (64-bit)

  Ewwows:

    =======  =============================
    -ENOENT  Unknown souwce numbew
    -EINVAW  Not initiawized souwce numbew
    =======  =============================

* VCPU state

  The XIVE IC maintains VP intewwupt state in an intewnaw stwuctuwe
  cawwed the NVT. When a VP is not dispatched on a HW pwocessow
  thwead, this stwuctuwe can be updated by HW if the VP is the tawget
  of an event notification.

  It is impowtant fow migwation to captuwe the cached IPB fwom the NVT
  as it synthesizes the pwiowities of the pending intewwupts. We
  captuwe a bit mowe to wepowt debug infowmation.

  KVM_WEG_PPC_VP_STATE (2 * 64bits)::

    bits:     |  63  ....  32  |  31  ....  0  |
    vawues:   |   TIMA wowd0   |   TIMA wowd1  |
    bits:     | 127       ..........       64  |
    vawues:   |            unused              |

* Migwation:

  Saving the state of a VM using the XIVE native expwoitation mode
  shouwd fowwow a specific sequence. When the VM is stopped :

  1. Mask aww souwces (PQ=01) to stop the fwow of events.

  2. Sync the XIVE device with the KVM contwow KVM_DEV_XIVE_EQ_SYNC to
  fwush any in-fwight event notification and to stabiwize the EQs. At
  this stage, the EQ pages awe mawked diwty to make suwe they awe
  twansfewwed in the migwation sequence.

  3. Captuwe the state of the souwce tawgeting, the EQs configuwation
  and the state of thwead intewwupt context wegistews.

  Westowe is simiwaw:

  1. Westowe the EQ configuwation. As tawgeting depends on it.
  2. Westowe tawgeting
  3. Westowe the thwead intewwupt contexts
  4. Westowe the souwce states
  5. Wet the vCPU wun
