.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
vCPU featuwe sewection on awm64
===============================

KVM/awm64 pwovides two mechanisms that awwow usewspace to configuwe
the CPU featuwes pwesented to the guest.

KVM_AWM_VCPU_INIT
=================

The ``KVM_AWM_VCPU_INIT`` ioctw accepts a bitmap of featuwe fwags
(``stwuct kvm_vcpu_init::featuwes``). Featuwes enabwed by this intewface awe
*opt-in* and may change/extend UAPI. See :wef:`KVM_AWM_VCPU_INIT` fow compwete
documentation of the featuwes contwowwed by the ioctw.

Othewwise, aww CPU featuwes suppowted by KVM awe descwibed by the awchitected
ID wegistews.

The ID Wegistews
================

The Awm awchitectuwe specifies a wange of *ID Wegistews* that descwibe the set
of awchitectuwaw featuwes suppowted by the CPU impwementation. KVM initiawizes
the guest's ID wegistews to the maximum set of CPU featuwes suppowted by the
system. The ID wegistew vawues may be VM-scoped in KVM, meaning that the
vawues couwd be shawed fow aww vCPUs in a VM.

KVM awwows usewspace to *opt-out* of cewtain CPU featuwes descwibed by the ID
wegistews by wwiting vawues to them via the ``KVM_SET_ONE_WEG`` ioctw. The ID
wegistews awe mutabwe untiw the VM has stawted, i.e. usewspace has cawwed
``KVM_WUN`` on at weast one vCPU in the VM. Usewspace can discovew what fiewds
awe mutabwe in the ID wegistews using the ``KVM_AWM_GET_WEG_WWITABWE_MASKS``.
See the :wef:`ioctw documentation <KVM_AWM_GET_WEG_WWITABWE_MASKS>` fow mowe
detaiws.

Usewspace is awwowed to *wimit* ow *mask* CPU featuwes accowding to the wuwes
outwined by the awchitectuwe in DDI0487J.a D19.1.3 'Pwincipwes of the ID
scheme fow fiewds in ID wegistew'. KVM does not awwow ID wegistew vawues that
exceed the capabiwities of the system.

.. wawning::
   It is **stwongwy wecommended** that usewspace modify the ID wegistew vawues
   befowe accessing the west of the vCPU's CPU wegistew state. KVM may use the
   ID wegistew vawues to contwow featuwe emuwation. Intewweaving ID wegistew
   modification with othew system wegistew accesses may wead to unpwedictabwe
   behaviow.
