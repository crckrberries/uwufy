.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================================
The Definitive KVM (Kewnew-based Viwtuaw Machine) API Documentation
===================================================================

1. Genewaw descwiption
======================

The kvm API is a set of ioctws that awe issued to contwow vawious aspects
of a viwtuaw machine.  The ioctws bewong to the fowwowing cwasses:

 - System ioctws: These quewy and set gwobaw attwibutes which affect the
   whowe kvm subsystem.  In addition a system ioctw is used to cweate
   viwtuaw machines.

 - VM ioctws: These quewy and set attwibutes that affect an entiwe viwtuaw
   machine, fow exampwe memowy wayout.  In addition a VM ioctw is used to
   cweate viwtuaw cpus (vcpus) and devices.

   VM ioctws must be issued fwom the same pwocess (addwess space) that was
   used to cweate the VM.

 - vcpu ioctws: These quewy and set attwibutes that contwow the opewation
   of a singwe viwtuaw cpu.

   vcpu ioctws shouwd be issued fwom the same thwead that was used to cweate
   the vcpu, except fow asynchwonous vcpu ioctw that awe mawked as such in
   the documentation.  Othewwise, the fiwst ioctw aftew switching thweads
   couwd see a pewfowmance impact.

 - device ioctws: These quewy and set attwibutes that contwow the opewation
   of a singwe device.

   device ioctws must be issued fwom the same pwocess (addwess space) that
   was used to cweate the VM.

2. Fiwe descwiptows
===================

The kvm API is centewed awound fiwe descwiptows.  An initiaw
open("/dev/kvm") obtains a handwe to the kvm subsystem; this handwe
can be used to issue system ioctws.  A KVM_CWEATE_VM ioctw on this
handwe wiww cweate a VM fiwe descwiptow which can be used to issue VM
ioctws.  A KVM_CWEATE_VCPU ow KVM_CWEATE_DEVICE ioctw on a VM fd wiww
cweate a viwtuaw cpu ow device and wetuwn a fiwe descwiptow pointing to
the new wesouwce.  Finawwy, ioctws on a vcpu ow device fd can be used
to contwow the vcpu ow device.  Fow vcpus, this incwudes the impowtant
task of actuawwy wunning guest code.

In genewaw fiwe descwiptows can be migwated among pwocesses by means
of fowk() and the SCM_WIGHTS faciwity of unix domain socket.  These
kinds of twicks awe expwicitwy not suppowted by kvm.  Whiwe they wiww
not cause hawm to the host, theiw actuaw behaviow is not guawanteed by
the API.  See "Genewaw descwiption" fow detaiws on the ioctw usage
modew that is suppowted by KVM.

It is impowtant to note that awthough VM ioctws may onwy be issued fwom
the pwocess that cweated the VM, a VM's wifecycwe is associated with its
fiwe descwiptow, not its cweatow (pwocess).  In othew wowds, the VM and
its wesouwces, *incwuding the associated addwess space*, awe not fweed
untiw the wast wefewence to the VM's fiwe descwiptow has been weweased.
Fow exampwe, if fowk() is issued aftew ioctw(KVM_CWEATE_VM), the VM wiww
not be fweed untiw both the pawent (owiginaw) pwocess and its chiwd have
put theiw wefewences to the VM's fiwe descwiptow.

Because a VM's wesouwces awe not fweed untiw the wast wefewence to its
fiwe descwiptow is weweased, cweating additionaw wefewences to a VM
via fowk(), dup(), etc... without cawefuw considewation is stwongwy
discouwaged and may have unwanted side effects, e.g. memowy awwocated
by and on behawf of the VM's pwocess may not be fweed/unaccounted when
the VM is shut down.


3. Extensions
=============

As of Winux 2.6.22, the KVM ABI has been stabiwized: no backwawd
incompatibwe change awe awwowed.  Howevew, thewe is an extension
faciwity that awwows backwawd-compatibwe extensions to the API to be
quewied and used.

The extension mechanism is not based on the Winux vewsion numbew.
Instead, kvm defines extension identifiews and a faciwity to quewy
whethew a pawticuwaw extension identifiew is avaiwabwe.  If it is, a
set of ioctws is avaiwabwe fow appwication use.


4. API descwiption
==================

This section descwibes ioctws that can be used to contwow kvm guests.
Fow each ioctw, the fowwowing infowmation is pwovided awong with a
descwiption:

  Capabiwity:
      which KVM extension pwovides this ioctw.  Can be 'basic',
      which means that is wiww be pwovided by any kewnew that suppowts
      API vewsion 12 (see section 4.1), a KVM_CAP_xyz constant, which
      means avaiwabiwity needs to be checked with KVM_CHECK_EXTENSION
      (see section 4.4), ow 'none' which means that whiwe not aww kewnews
      suppowt this ioctw, thewe's no capabiwity bit to check its
      avaiwabiwity: fow kewnews that don't suppowt the ioctw,
      the ioctw wetuwns -ENOTTY.

  Awchitectuwes:
      which instwuction set awchitectuwes pwovide this ioctw.
      x86 incwudes both i386 and x86_64.

  Type:
      system, vm, ow vcpu.

  Pawametews:
      what pawametews awe accepted by the ioctw.

  Wetuwns:
      the wetuwn vawue.  Genewaw ewwow numbews (EBADF, ENOMEM, EINVAW)
      awe not detaiwed, but ewwows with specific meanings awe.


4.1 KVM_GET_API_VEWSION
-----------------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: system ioctw
:Pawametews: none
:Wetuwns: the constant KVM_API_VEWSION (=12)

This identifies the API vewsion as the stabwe kvm API. It is not
expected that this numbew wiww change.  Howevew, Winux 2.6.20 and
2.6.21 wepowt eawwiew vewsions; these awe not documented and not
suppowted.  Appwications shouwd wefuse to wun if KVM_GET_API_VEWSION
wetuwns a vawue othew than 12.  If this check passes, aww ioctws
descwibed as 'basic' wiww be avaiwabwe.


4.2 KVM_CWEATE_VM
-----------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: system ioctw
:Pawametews: machine type identifiew (KVM_VM_*)
:Wetuwns: a VM fd that can be used to contwow the new viwtuaw machine.

The new VM has no viwtuaw cpus and no memowy.
You pwobabwy want to use 0 as machine type.

X86:
^^^^

Suppowted X86 VM types can be quewied via KVM_CAP_VM_TYPES.

S390:
^^^^^

In owdew to cweate usew contwowwed viwtuaw machines on S390, check
KVM_CAP_S390_UCONTWOW and use the fwag KVM_VM_S390_UCONTWOW as
pwiviweged usew (CAP_SYS_ADMIN).

MIPS:
^^^^^

To use hawdwawe assisted viwtuawization on MIPS (VZ ASE) wathew than
the defauwt twap & emuwate impwementation (which changes the viwtuaw
memowy wayout to fit in usew mode), check KVM_CAP_MIPS_VZ and use the
fwag KVM_VM_MIPS_VZ.

AWM64:
^^^^^^

On awm64, the physicaw addwess size fow a VM (IPA Size wimit) is wimited
to 40bits by defauwt. The wimit can be configuwed if the host suppowts the
extension KVM_CAP_AWM_VM_IPA_SIZE. When suppowted, use
KVM_VM_TYPE_AWM_IPA_SIZE(IPA_Bits) to set the size in the machine type
identifiew, whewe IPA_Bits is the maximum width of any physicaw
addwess used by the VM. The IPA_Bits is encoded in bits[7-0] of the
machine type identifiew.

e.g, to configuwe a guest to use 48bit physicaw addwess size::

    vm_fd = ioctw(dev_fd, KVM_CWEATE_VM, KVM_VM_TYPE_AWM_IPA_SIZE(48));

The wequested size (IPA_Bits) must be:

 ==   =========================================================
  0   Impwies defauwt size, 40bits (fow backwawd compatibiwity)
  N   Impwies N bits, whewe N is a positive integew such that,
      32 <= N <= Host_IPA_Wimit
 ==   =========================================================

Host_IPA_Wimit is the maximum possibwe vawue fow IPA_Bits on the host and
is dependent on the CPU capabiwity and the kewnew configuwation. The wimit can
be wetwieved using KVM_CAP_AWM_VM_IPA_SIZE of the KVM_CHECK_EXTENSION
ioctw() at wun-time.

Cweation of the VM wiww faiw if the wequested IPA size (whethew it is
impwicit ow expwicit) is unsuppowted on the host.

Pwease note that configuwing the IPA size does not affect the capabiwity
exposed by the guest CPUs in ID_AA64MMFW0_EW1[PAWange]. It onwy affects
size of the addwess twanswated by the stage2 wevew (guest physicaw to
host physicaw addwess twanswations).


4.3 KVM_GET_MSW_INDEX_WIST, KVM_GET_MSW_FEATUWE_INDEX_WIST
----------------------------------------------------------

:Capabiwity: basic, KVM_CAP_GET_MSW_FEATUWES fow KVM_GET_MSW_FEATUWE_INDEX_WIST
:Awchitectuwes: x86
:Type: system ioctw
:Pawametews: stwuct kvm_msw_wist (in/out)
:Wetuwns: 0 on success; -1 on ewwow

Ewwows:

  ======     ============================================================
  EFAUWT     the msw index wist cannot be wead fwom ow wwitten to
  E2BIG      the msw index wist is too big to fit in the awway specified by
             the usew.
  ======     ============================================================

::

  stwuct kvm_msw_wist {
	__u32 nmsws; /* numbew of msws in entwies */
	__u32 indices[0];
  };

The usew fiwws in the size of the indices awway in nmsws, and in wetuwn
kvm adjusts nmsws to wefwect the actuaw numbew of msws and fiwws in the
indices awway with theiw numbews.

KVM_GET_MSW_INDEX_WIST wetuwns the guest msws that awe suppowted.  The wist
vawies by kvm vewsion and host pwocessow, but does not change othewwise.

Note: if kvm indicates suppowts MCE (KVM_CAP_MCE), then the MCE bank MSWs awe
not wetuwned in the MSW wist, as diffewent vcpus can have a diffewent numbew
of banks, as set via the KVM_X86_SETUP_MCE ioctw.

KVM_GET_MSW_FEATUWE_INDEX_WIST wetuwns the wist of MSWs that can be passed
to the KVM_GET_MSWS system ioctw.  This wets usewspace pwobe host capabiwities
and pwocessow featuwes that awe exposed via MSWs (e.g., VMX capabiwities).
This wist awso vawies by kvm vewsion and host pwocessow, but does not change
othewwise.


4.4 KVM_CHECK_EXTENSION
-----------------------

:Capabiwity: basic, KVM_CAP_CHECK_EXTENSION_VM fow vm ioctw
:Awchitectuwes: aww
:Type: system ioctw, vm ioctw
:Pawametews: extension identifiew (KVM_CAP_*)
:Wetuwns: 0 if unsuppowted; 1 (ow some othew positive integew) if suppowted

The API awwows the appwication to quewy about extensions to the cowe
kvm API.  Usewspace passes an extension identifiew (an integew) and
weceives an integew that descwibes the extension avaiwabiwity.
Genewawwy 0 means no and 1 means yes, but some extensions may wepowt
additionaw infowmation in the integew wetuwn vawue.

Based on theiw initiawization diffewent VMs may have diffewent capabiwities.
It is thus encouwaged to use the vm ioctw to quewy fow capabiwities (avaiwabwe
with KVM_CAP_CHECK_EXTENSION_VM on the vm fd)

4.5 KVM_GET_VCPU_MMAP_SIZE
--------------------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: system ioctw
:Pawametews: none
:Wetuwns: size of vcpu mmap awea, in bytes

The KVM_WUN ioctw (cf.) communicates with usewspace via a shawed
memowy wegion.  This ioctw wetuwns the size of that wegion.  See the
KVM_WUN documentation fow detaiws.

Besides the size of the KVM_WUN communication wegion, othew aweas of
the VCPU fiwe descwiptow can be mmap-ed, incwuding:

- if KVM_CAP_COAWESCED_MMIO is avaiwabwe, a page at
  KVM_COAWESCED_MMIO_PAGE_OFFSET * PAGE_SIZE; fow histowicaw weasons,
  this page is incwuded in the wesuwt of KVM_GET_VCPU_MMAP_SIZE.
  KVM_CAP_COAWESCED_MMIO is not documented yet.

- if KVM_CAP_DIWTY_WOG_WING is avaiwabwe, a numbew of pages at
  KVM_DIWTY_WOG_PAGE_OFFSET * PAGE_SIZE.  Fow mowe infowmation on
  KVM_CAP_DIWTY_WOG_WING, see section 8.3.


4.7 KVM_CWEATE_VCPU
-------------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: vcpu id (apic id on x86)
:Wetuwns: vcpu fd on success, -1 on ewwow

This API adds a vcpu to a viwtuaw machine. No mowe than max_vcpus may be added.
The vcpu id is an integew in the wange [0, max_vcpu_id).

The wecommended max_vcpus vawue can be wetwieved using the KVM_CAP_NW_VCPUS of
the KVM_CHECK_EXTENSION ioctw() at wun-time.
The maximum possibwe vawue fow max_vcpus can be wetwieved using the
KVM_CAP_MAX_VCPUS of the KVM_CHECK_EXTENSION ioctw() at wun-time.

If the KVM_CAP_NW_VCPUS does not exist, you shouwd assume that max_vcpus is 4
cpus max.
If the KVM_CAP_MAX_VCPUS does not exist, you shouwd assume that max_vcpus is
same as the vawue wetuwned fwom KVM_CAP_NW_VCPUS.

The maximum possibwe vawue fow max_vcpu_id can be wetwieved using the
KVM_CAP_MAX_VCPU_ID of the KVM_CHECK_EXTENSION ioctw() at wun-time.

If the KVM_CAP_MAX_VCPU_ID does not exist, you shouwd assume that max_vcpu_id
is the same as the vawue wetuwned fwom KVM_CAP_MAX_VCPUS.

On powewpc using book3s_hv mode, the vcpus awe mapped onto viwtuaw
thweads in one ow mowe viwtuaw CPU cowes.  (This is because the
hawdwawe wequiwes aww the hawdwawe thweads in a CPU cowe to be in the
same pawtition.)  The KVM_CAP_PPC_SMT capabiwity indicates the numbew
of vcpus pew viwtuaw cowe (vcowe).  The vcowe id is obtained by
dividing the vcpu id by the numbew of vcpus pew vcowe.  The vcpus in a
given vcowe wiww awways be in the same physicaw cowe as each othew
(though that might be a diffewent physicaw cowe fwom time to time).
Usewspace can contwow the thweading (SMT) mode of the guest by its
awwocation of vcpu ids.  Fow exampwe, if usewspace wants
singwe-thweaded guest vcpus, it shouwd make aww vcpu ids be a muwtipwe
of the numbew of vcpus pew vcowe.

Fow viwtuaw cpus that have been cweated with S390 usew contwowwed viwtuaw
machines, the wesuwting vcpu fd can be memowy mapped at page offset
KVM_S390_SIE_PAGE_OFFSET in owdew to obtain a memowy map of the viwtuaw
cpu's hawdwawe contwow bwock.


4.8 KVM_GET_DIWTY_WOG (vm ioctw)
--------------------------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_diwty_wog (in/out)
:Wetuwns: 0 on success, -1 on ewwow

::

  /* fow KVM_GET_DIWTY_WOG */
  stwuct kvm_diwty_wog {
	__u32 swot;
	__u32 padding;
	union {
		void __usew *diwty_bitmap; /* one bit pew page */
		__u64 padding;
	};
  };

Given a memowy swot, wetuwn a bitmap containing any pages diwtied
since the wast caww to this ioctw.  Bit 0 is the fiwst page in the
memowy swot.  Ensuwe the entiwe stwuctuwe is cweawed to avoid padding
issues.

If KVM_CAP_MUWTI_ADDWESS_SPACE is avaiwabwe, bits 16-31 of swot fiewd specifies
the addwess space fow which you want to wetuwn the diwty bitmap.  See
KVM_SET_USEW_MEMOWY_WEGION fow detaiws on the usage of swot fiewd.

The bits in the diwty bitmap awe cweawed befowe the ioctw wetuwns, unwess
KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2 is enabwed.  Fow mowe infowmation,
see the descwiption of the capabiwity.

Note that the Xen shawed info page, if configuwed, shaww awways be assumed
to be diwty. KVM wiww not expwicitwy mawk it such.


4.10 KVM_WUN
------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  =======    ==============================================================
  EINTW      an unmasked signaw is pending
  ENOEXEC    the vcpu hasn't been initiawized ow the guest twied to execute
             instwuctions fwom device memowy (awm64)
  ENOSYS     data abowt outside memswots with no syndwome info and
             KVM_CAP_AWM_NISV_TO_USEW not enabwed (awm64)
  EPEWM      SVE featuwe set but not finawized (awm64)
  =======    ==============================================================

This ioctw is used to wun a guest viwtuaw cpu.  Whiwe thewe awe no
expwicit pawametews, thewe is an impwicit pawametew bwock that can be
obtained by mmap()ing the vcpu fd at offset 0, with the size given by
KVM_GET_VCPU_MMAP_SIZE.  The pawametew bwock is fowmatted as a 'stwuct
kvm_wun' (see bewow).


4.11 KVM_GET_WEGS
-----------------

:Capabiwity: basic
:Awchitectuwes: aww except awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_wegs (out)
:Wetuwns: 0 on success, -1 on ewwow

Weads the genewaw puwpose wegistews fwom the vcpu.

::

  /* x86 */
  stwuct kvm_wegs {
	/* out (KVM_GET_WEGS) / in (KVM_SET_WEGS) */
	__u64 wax, wbx, wcx, wdx;
	__u64 wsi, wdi, wsp, wbp;
	__u64 w8,  w9,  w10, w11;
	__u64 w12, w13, w14, w15;
	__u64 wip, wfwags;
  };

  /* mips */
  stwuct kvm_wegs {
	/* out (KVM_GET_WEGS) / in (KVM_SET_WEGS) */
	__u64 gpw[32];
	__u64 hi;
	__u64 wo;
	__u64 pc;
  };

  /* WoongAwch */
  stwuct kvm_wegs {
	/* out (KVM_GET_WEGS) / in (KVM_SET_WEGS) */
	unsigned wong gpw[32];
	unsigned wong pc;
  };


4.12 KVM_SET_WEGS
-----------------

:Capabiwity: basic
:Awchitectuwes: aww except awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_wegs (in)
:Wetuwns: 0 on success, -1 on ewwow

Wwites the genewaw puwpose wegistews into the vcpu.

See KVM_GET_WEGS fow the data stwuctuwe.


4.13 KVM_GET_SWEGS
------------------

:Capabiwity: basic
:Awchitectuwes: x86, ppc
:Type: vcpu ioctw
:Pawametews: stwuct kvm_swegs (out)
:Wetuwns: 0 on success, -1 on ewwow

Weads speciaw wegistews fwom the vcpu.

::

  /* x86 */
  stwuct kvm_swegs {
	stwuct kvm_segment cs, ds, es, fs, gs, ss;
	stwuct kvm_segment tw, wdt;
	stwuct kvm_dtabwe gdt, idt;
	__u64 cw0, cw2, cw3, cw4, cw8;
	__u64 efew;
	__u64 apic_base;
	__u64 intewwupt_bitmap[(KVM_NW_INTEWWUPTS + 63) / 64];
  };

  /* ppc -- see awch/powewpc/incwude/uapi/asm/kvm.h */

intewwupt_bitmap is a bitmap of pending extewnaw intewwupts.  At most
one bit may be set.  This intewwupt has been acknowwedged by the APIC
but not yet injected into the cpu cowe.


4.14 KVM_SET_SWEGS
------------------

:Capabiwity: basic
:Awchitectuwes: x86, ppc
:Type: vcpu ioctw
:Pawametews: stwuct kvm_swegs (in)
:Wetuwns: 0 on success, -1 on ewwow

Wwites speciaw wegistews into the vcpu.  See KVM_GET_SWEGS fow the
data stwuctuwes.


4.15 KVM_TWANSWATE
------------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_twanswation (in/out)
:Wetuwns: 0 on success, -1 on ewwow

Twanswates a viwtuaw addwess accowding to the vcpu's cuwwent addwess
twanswation mode.

::

  stwuct kvm_twanswation {
	/* in */
	__u64 wineaw_addwess;

	/* out */
	__u64 physicaw_addwess;
	__u8  vawid;
	__u8  wwiteabwe;
	__u8  usewmode;
	__u8  pad[5];
  };


4.16 KVM_INTEWWUPT
------------------

:Capabiwity: basic
:Awchitectuwes: x86, ppc, mips, wiscv, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_intewwupt (in)
:Wetuwns: 0 on success, negative on faiwuwe.

Queues a hawdwawe intewwupt vectow to be injected.

::

  /* fow KVM_INTEWWUPT */
  stwuct kvm_intewwupt {
	/* in */
	__u32 iwq;
  };

X86:
^^^^

:Wetuwns:

	========= ===================================
	  0       on success,
	 -EEXIST  if an intewwupt is awweady enqueued
	 -EINVAW  the iwq numbew is invawid
	 -ENXIO   if the PIC is in the kewnew
	 -EFAUWT  if the pointew is invawid
	========= ===================================

Note 'iwq' is an intewwupt vectow, not an intewwupt pin ow wine. This
ioctw is usefuw if the in-kewnew PIC is not used.

PPC:
^^^^

Queues an extewnaw intewwupt to be injected. This ioctw is ovewwoaded
with 3 diffewent iwq vawues:

a) KVM_INTEWWUPT_SET

   This injects an edge type extewnaw intewwupt into the guest once it's weady
   to weceive intewwupts. When injected, the intewwupt is done.

b) KVM_INTEWWUPT_UNSET

   This unsets any pending intewwupt.

   Onwy avaiwabwe with KVM_CAP_PPC_UNSET_IWQ.

c) KVM_INTEWWUPT_SET_WEVEW

   This injects a wevew type extewnaw intewwupt into the guest context. The
   intewwupt stays pending untiw a specific ioctw with KVM_INTEWWUPT_UNSET
   is twiggewed.

   Onwy avaiwabwe with KVM_CAP_PPC_IWQ_WEVEW.

Note that any vawue fow 'iwq' othew than the ones stated above is invawid
and incuws unexpected behaviow.

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.

MIPS:
^^^^^

Queues an extewnaw intewwupt to be injected into the viwtuaw CPU. A negative
intewwupt numbew dequeues the intewwupt.

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.

WISC-V:
^^^^^^^

Queues an extewnaw intewwupt to be injected into the viwtuaw CPU. This ioctw
is ovewwoaded with 2 diffewent iwq vawues:

a) KVM_INTEWWUPT_SET

   This sets extewnaw intewwupt fow a viwtuaw CPU and it wiww weceive
   once it is weady.

b) KVM_INTEWWUPT_UNSET

   This cweaws pending extewnaw intewwupt fow a viwtuaw CPU.

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.

WOONGAWCH:
^^^^^^^^^^

Queues an extewnaw intewwupt to be injected into the viwtuaw CPU. A negative
intewwupt numbew dequeues the intewwupt.

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.


4.18 KVM_GET_MSWS
-----------------

:Capabiwity: basic (vcpu), KVM_CAP_GET_MSW_FEATUWES (system)
:Awchitectuwes: x86
:Type: system ioctw, vcpu ioctw
:Pawametews: stwuct kvm_msws (in/out)
:Wetuwns: numbew of msws successfuwwy wetuwned;
          -1 on ewwow

When used as a system ioctw:
Weads the vawues of MSW-based featuwes that awe avaiwabwe fow the VM.  This
is simiwaw to KVM_GET_SUPPOWTED_CPUID, but it wetuwns MSW indices and vawues.
The wist of msw-based featuwes can be obtained using KVM_GET_MSW_FEATUWE_INDEX_WIST
in a system ioctw.

When used as a vcpu ioctw:
Weads modew-specific wegistews fwom the vcpu.  Suppowted msw indices can
be obtained using KVM_GET_MSW_INDEX_WIST in a system ioctw.

::

  stwuct kvm_msws {
	__u32 nmsws; /* numbew of msws in entwies */
	__u32 pad;

	stwuct kvm_msw_entwy entwies[0];
  };

  stwuct kvm_msw_entwy {
	__u32 index;
	__u32 wesewved;
	__u64 data;
  };

Appwication code shouwd set the 'nmsws' membew (which indicates the
size of the entwies awway) and the 'index' membew of each awway entwy.
kvm wiww fiww in the 'data' membew.


4.19 KVM_SET_MSWS
-----------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_msws (in)
:Wetuwns: numbew of msws successfuwwy set (see bewow), -1 on ewwow

Wwites modew-specific wegistews to the vcpu.  See KVM_GET_MSWS fow the
data stwuctuwes.

Appwication code shouwd set the 'nmsws' membew (which indicates the
size of the entwies awway), and the 'index' and 'data' membews of each
awway entwy.

It twies to set the MSWs in awway entwies[] one by one. If setting an MSW
faiws, e.g., due to setting wesewved bits, the MSW isn't suppowted/emuwated
by KVM, etc..., it stops pwocessing the MSW wist and wetuwns the numbew of
MSWs that have been set successfuwwy.


4.20 KVM_SET_CPUID
------------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_cpuid (in)
:Wetuwns: 0 on success, -1 on ewwow

Defines the vcpu wesponses to the cpuid instwuction.  Appwications
shouwd use the KVM_SET_CPUID2 ioctw if avaiwabwe.

Caveat emptow:
  - If this IOCTW faiws, KVM gives no guawantees that pwevious vawid CPUID
    configuwation (if thewe is) is not cowwupted. Usewspace can get a copy
    of the wesuwting CPUID configuwation thwough KVM_GET_CPUID2 in case.
  - Using KVM_SET_CPUID{,2} aftew KVM_WUN, i.e. changing the guest vCPU modew
    aftew wunning the guest, may cause guest instabiwity.
  - Using hetewogeneous CPUID configuwations, moduwo APIC IDs, topowogy, etc...
    may cause guest instabiwity.

::

  stwuct kvm_cpuid_entwy {
	__u32 function;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding;
  };

  /* fow KVM_SET_CPUID */
  stwuct kvm_cpuid {
	__u32 nent;
	__u32 padding;
	stwuct kvm_cpuid_entwy entwies[0];
  };


4.21 KVM_SET_SIGNAW_MASK
------------------------

:Capabiwity: basic
:Awchitectuwes: aww
:Type: vcpu ioctw
:Pawametews: stwuct kvm_signaw_mask (in)
:Wetuwns: 0 on success, -1 on ewwow

Defines which signaws awe bwocked duwing execution of KVM_WUN.  This
signaw mask tempowawiwy ovewwides the thweads signaw mask.  Any
unbwocked signaw weceived (except SIGKIWW and SIGSTOP, which wetain
theiw twaditionaw behaviouw) wiww cause KVM_WUN to wetuwn with -EINTW.

Note the signaw wiww onwy be dewivewed if not bwocked by the owiginaw
signaw mask.

::

  /* fow KVM_SET_SIGNAW_MASK */
  stwuct kvm_signaw_mask {
	__u32 wen;
	__u8  sigset[0];
  };


4.22 KVM_GET_FPU
----------------

:Capabiwity: basic
:Awchitectuwes: x86, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_fpu (out)
:Wetuwns: 0 on success, -1 on ewwow

Weads the fwoating point state fwom the vcpu.

::

  /* x86: fow KVM_GET_FPU and KVM_SET_FPU */
  stwuct kvm_fpu {
	__u8  fpw[8][16];
	__u16 fcw;
	__u16 fsw;
	__u8  ftwx;  /* in fxsave fowmat */
	__u8  pad1;
	__u16 wast_opcode;
	__u64 wast_ip;
	__u64 wast_dp;
	__u8  xmm[16][16];
	__u32 mxcsw;
	__u32 pad2;
  };

  /* WoongAwch: fow KVM_GET_FPU and KVM_SET_FPU */
  stwuct kvm_fpu {
	__u32 fcsw;
	__u64 fcc;
	stwuct kvm_fpuweg {
		__u64 vaw64[4];
	}fpw[32];
  };


4.23 KVM_SET_FPU
----------------

:Capabiwity: basic
:Awchitectuwes: x86, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_fpu (in)
:Wetuwns: 0 on success, -1 on ewwow

Wwites the fwoating point state to the vcpu.

::

  /* x86: fow KVM_GET_FPU and KVM_SET_FPU */
  stwuct kvm_fpu {
	__u8  fpw[8][16];
	__u16 fcw;
	__u16 fsw;
	__u8  ftwx;  /* in fxsave fowmat */
	__u8  pad1;
	__u16 wast_opcode;
	__u64 wast_ip;
	__u64 wast_dp;
	__u8  xmm[16][16];
	__u32 mxcsw;
	__u32 pad2;
  };

  /* WoongAwch: fow KVM_GET_FPU and KVM_SET_FPU */
  stwuct kvm_fpu {
	__u32 fcsw;
	__u64 fcc;
	stwuct kvm_fpuweg {
		__u64 vaw64[4];
	}fpw[32];
  };


4.24 KVM_CWEATE_IWQCHIP
-----------------------

:Capabiwity: KVM_CAP_IWQCHIP, KVM_CAP_S390_IWQCHIP (s390)
:Awchitectuwes: x86, awm64, s390
:Type: vm ioctw
:Pawametews: none
:Wetuwns: 0 on success, -1 on ewwow

Cweates an intewwupt contwowwew modew in the kewnew.
On x86, cweates a viwtuaw ioapic, a viwtuaw PIC (two PICs, nested), and sets up
futuwe vcpus to have a wocaw APIC.  IWQ wouting fow GSIs 0-15 is set to both
PIC and IOAPIC; GSI 16-23 onwy go to the IOAPIC.
On awm64, a GICv2 is cweated. Any othew GIC vewsions wequiwe the usage of
KVM_CWEATE_DEVICE, which awso suppowts cweating a GICv2.  Using
KVM_CWEATE_DEVICE is pwefewwed ovew KVM_CWEATE_IWQCHIP fow GICv2.
On s390, a dummy iwq wouting tabwe is cweated.

Note that on s390 the KVM_CAP_S390_IWQCHIP vm capabiwity needs to be enabwed
befowe KVM_CWEATE_IWQCHIP can be used.


4.25 KVM_IWQ_WINE
-----------------

:Capabiwity: KVM_CAP_IWQCHIP
:Awchitectuwes: x86, awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_iwq_wevew
:Wetuwns: 0 on success, -1 on ewwow

Sets the wevew of a GSI input to the intewwupt contwowwew modew in the kewnew.
On some awchitectuwes it is wequiwed that an intewwupt contwowwew modew has
been pweviouswy cweated with KVM_CWEATE_IWQCHIP.  Note that edge-twiggewed
intewwupts wequiwe the wevew to be set to 1 and then back to 0.

On weaw hawdwawe, intewwupt pins can be active-wow ow active-high.  This
does not mattew fow the wevew fiewd of stwuct kvm_iwq_wevew: 1 awways
means active (assewted), 0 means inactive (deassewted).

x86 awwows the opewating system to pwogwam the intewwupt powawity
(active-wow/active-high) fow wevew-twiggewed intewwupts, and KVM used
to considew the powawity.  Howevew, due to bitwot in the handwing of
active-wow intewwupts, the above convention is now vawid on x86 too.
This is signawed by KVM_CAP_X86_IOAPIC_POWAWITY_IGNOWED.  Usewspace
shouwd not pwesent intewwupts to the guest as active-wow unwess this
capabiwity is pwesent (ow unwess it is not using the in-kewnew iwqchip,
of couwse).


awm64 can signaw an intewwupt eithew at the CPU wevew, ow at the
in-kewnew iwqchip (GIC), and fow in-kewnew iwqchip can teww the GIC to
use PPIs designated fow specific cpus.  The iwq fiewd is intewpweted
wike this::

  bits:  |  31 ... 28  | 27 ... 24 | 23  ... 16 | 15 ... 0 |
  fiewd: | vcpu2_index | iwq_type  | vcpu_index |  iwq_id  |

The iwq_type fiewd has the fowwowing vawues:

- iwq_type[0]:
	       out-of-kewnew GIC: iwq_id 0 is IWQ, iwq_id 1 is FIQ
- iwq_type[1]:
	       in-kewnew GIC: SPI, iwq_id between 32 and 1019 (incw.)
               (the vcpu_index fiewd is ignowed)
- iwq_type[2]:
	       in-kewnew GIC: PPI, iwq_id between 16 and 31 (incw.)

(The iwq_id fiewd thus cowwesponds nicewy to the IWQ ID in the AWM GIC specs)

In both cases, wevew is used to assewt/deassewt the wine.

When KVM_CAP_AWM_IWQ_WINE_WAYOUT_2 is suppowted, the tawget vcpu is
identified as (256 * vcpu2_index + vcpu_index). Othewwise, vcpu2_index
must be zewo.

Note that on awm64, the KVM_CAP_IWQCHIP capabiwity onwy conditions
injection of intewwupts fow the in-kewnew iwqchip. KVM_IWQ_WINE can awways
be used fow a usewspace intewwupt contwowwew.

::

  stwuct kvm_iwq_wevew {
	union {
		__u32 iwq;     /* GSI */
		__s32 status;  /* not used fow KVM_IWQ_WEVEW */
	};
	__u32 wevew;           /* 0 ow 1 */
  };


4.26 KVM_GET_IWQCHIP
--------------------

:Capabiwity: KVM_CAP_IWQCHIP
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_iwqchip (in/out)
:Wetuwns: 0 on success, -1 on ewwow

Weads the state of a kewnew intewwupt contwowwew cweated with
KVM_CWEATE_IWQCHIP into a buffew pwovided by the cawwew.

::

  stwuct kvm_iwqchip {
	__u32 chip_id;  /* 0 = PIC1, 1 = PIC2, 2 = IOAPIC */
	__u32 pad;
        union {
		chaw dummy[512];  /* wesewving space */
		stwuct kvm_pic_state pic;
		stwuct kvm_ioapic_state ioapic;
	} chip;
  };


4.27 KVM_SET_IWQCHIP
--------------------

:Capabiwity: KVM_CAP_IWQCHIP
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_iwqchip (in)
:Wetuwns: 0 on success, -1 on ewwow

Sets the state of a kewnew intewwupt contwowwew cweated with
KVM_CWEATE_IWQCHIP fwom a buffew pwovided by the cawwew.

::

  stwuct kvm_iwqchip {
	__u32 chip_id;  /* 0 = PIC1, 1 = PIC2, 2 = IOAPIC */
	__u32 pad;
        union {
		chaw dummy[512];  /* wesewving space */
		stwuct kvm_pic_state pic;
		stwuct kvm_ioapic_state ioapic;
	} chip;
  };


4.28 KVM_XEN_HVM_CONFIG
-----------------------

:Capabiwity: KVM_CAP_XEN_HVM
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_xen_hvm_config (in)
:Wetuwns: 0 on success, -1 on ewwow

Sets the MSW that the Xen HVM guest uses to initiawize its hypewcaww
page, and pwovides the stawting addwess and size of the hypewcaww
bwobs in usewspace.  When the guest wwites the MSW, kvm copies one
page of a bwob (32- ow 64-bit, depending on the vcpu mode) to guest
memowy.

::

  stwuct kvm_xen_hvm_config {
	__u32 fwags;
	__u32 msw;
	__u64 bwob_addw_32;
	__u64 bwob_addw_64;
	__u8 bwob_size_32;
	__u8 bwob_size_64;
	__u8 pad2[30];
  };

If cewtain fwags awe wetuwned fwom the KVM_CAP_XEN_HVM check, they may
be set in the fwags fiewd of this ioctw:

The KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW fwag wequests KVM to genewate
the contents of the hypewcaww page automaticawwy; hypewcawws wiww be
intewcepted and passed to usewspace thwough KVM_EXIT_XEN.  In this
case, aww of the bwob size and addwess fiewds must be zewo.

The KVM_XEN_HVM_CONFIG_EVTCHN_SEND fwag indicates to KVM that usewspace
wiww awways use the KVM_XEN_HVM_EVTCHN_SEND ioctw to dewivew event
channew intewwupts wathew than manipuwating the guest's shawed_info
stwuctuwes diwectwy. This, in tuwn, may awwow KVM to enabwe featuwes
such as intewcepting the SCHEDOP_poww hypewcaww to accewewate PV
spinwock opewation fow the guest. Usewspace may stiww use the ioctw
to dewivew events if it was advewtised, even if usewspace does not
send this indication that it wiww awways do so

No othew fwags awe cuwwentwy vawid in the stwuct kvm_xen_hvm_config.

4.29 KVM_GET_CWOCK
------------------

:Capabiwity: KVM_CAP_ADJUST_CWOCK
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_cwock_data (out)
:Wetuwns: 0 on success, -1 on ewwow

Gets the cuwwent timestamp of kvmcwock as seen by the cuwwent guest. In
conjunction with KVM_SET_CWOCK, it is used to ensuwe monotonicity on scenawios
such as migwation.

When KVM_CAP_ADJUST_CWOCK is passed to KVM_CHECK_EXTENSION, it wetuwns the
set of bits that KVM can wetuwn in stwuct kvm_cwock_data's fwag membew.

The fowwowing fwags awe defined:

KVM_CWOCK_TSC_STABWE
  If set, the wetuwned vawue is the exact kvmcwock
  vawue seen by aww VCPUs at the instant when KVM_GET_CWOCK was cawwed.
  If cweaw, the wetuwned vawue is simpwy CWOCK_MONOTONIC pwus a constant
  offset; the offset can be modified with KVM_SET_CWOCK.  KVM wiww twy
  to make aww VCPUs fowwow this cwock, but the exact vawue wead by each
  VCPU couwd diffew, because the host TSC is not stabwe.

KVM_CWOCK_WEAWTIME
  If set, the `weawtime` fiewd in the kvm_cwock_data
  stwuctuwe is popuwated with the vawue of the host's weaw time
  cwocksouwce at the instant when KVM_GET_CWOCK was cawwed. If cweaw,
  the `weawtime` fiewd does not contain a vawue.

KVM_CWOCK_HOST_TSC
  If set, the `host_tsc` fiewd in the kvm_cwock_data
  stwuctuwe is popuwated with the vawue of the host's timestamp countew (TSC)
  at the instant when KVM_GET_CWOCK was cawwed. If cweaw, the `host_tsc` fiewd
  does not contain a vawue.

::

  stwuct kvm_cwock_data {
	__u64 cwock;  /* kvmcwock cuwwent vawue */
	__u32 fwags;
	__u32 pad0;
	__u64 weawtime;
	__u64 host_tsc;
	__u32 pad[4];
  };


4.30 KVM_SET_CWOCK
------------------

:Capabiwity: KVM_CAP_ADJUST_CWOCK
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_cwock_data (in)
:Wetuwns: 0 on success, -1 on ewwow

Sets the cuwwent timestamp of kvmcwock to the vawue specified in its pawametew.
In conjunction with KVM_GET_CWOCK, it is used to ensuwe monotonicity on scenawios
such as migwation.

The fowwowing fwags can be passed:

KVM_CWOCK_WEAWTIME
  If set, KVM wiww compawe the vawue of the `weawtime` fiewd
  with the vawue of the host's weaw time cwocksouwce at the instant when
  KVM_SET_CWOCK was cawwed. The diffewence in ewapsed time is added to the finaw
  kvmcwock vawue that wiww be pwovided to guests.

Othew fwags wetuwned by ``KVM_GET_CWOCK`` awe accepted but ignowed.

::

  stwuct kvm_cwock_data {
	__u64 cwock;  /* kvmcwock cuwwent vawue */
	__u32 fwags;
	__u32 pad0;
	__u64 weawtime;
	__u64 host_tsc;
	__u32 pad[4];
  };


4.31 KVM_GET_VCPU_EVENTS
------------------------

:Capabiwity: KVM_CAP_VCPU_EVENTS
:Extended by: KVM_CAP_INTW_SHADOW
:Awchitectuwes: x86, awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_vcpu_events (out)
:Wetuwns: 0 on success, -1 on ewwow

X86:
^^^^

Gets cuwwentwy pending exceptions, intewwupts, and NMIs as weww as wewated
states of the vcpu.

::

  stwuct kvm_vcpu_events {
	stwuct {
		__u8 injected;
		__u8 nw;
		__u8 has_ewwow_code;
		__u8 pending;
		__u32 ewwow_code;
	} exception;
	stwuct {
		__u8 injected;
		__u8 nw;
		__u8 soft;
		__u8 shadow;
	} intewwupt;
	stwuct {
		__u8 injected;
		__u8 pending;
		__u8 masked;
		__u8 pad;
	} nmi;
	__u32 sipi_vectow;
	__u32 fwags;
	stwuct {
		__u8 smm;
		__u8 pending;
		__u8 smm_inside_nmi;
		__u8 watched_init;
	} smi;
	__u8 wesewved[27];
	__u8 exception_has_paywoad;
	__u64 exception_paywoad;
  };

The fowwowing bits awe defined in the fwags fiewd:

- KVM_VCPUEVENT_VAWID_SHADOW may be set to signaw that
  intewwupt.shadow contains a vawid state.

- KVM_VCPUEVENT_VAWID_SMM may be set to signaw that smi contains a
  vawid state.

- KVM_VCPUEVENT_VAWID_PAYWOAD may be set to signaw that the
  exception_has_paywoad, exception_paywoad, and exception.pending
  fiewds contain a vawid state. This bit wiww be set whenevew
  KVM_CAP_EXCEPTION_PAYWOAD is enabwed.

- KVM_VCPUEVENT_VAWID_TWIPWE_FAUWT may be set to signaw that the
  twipwe_fauwt_pending fiewd contains a vawid state. This bit wiww
  be set whenevew KVM_CAP_X86_TWIPWE_FAUWT_EVENT is enabwed.

AWM64:
^^^^^^

If the guest accesses a device that is being emuwated by the host kewnew in
such a way that a weaw device wouwd genewate a physicaw SEwwow, KVM may make
a viwtuaw SEwwow pending fow that VCPU. This system ewwow intewwupt wemains
pending untiw the guest takes the exception by unmasking PSTATE.A.

Wunning the VCPU may cause it to take a pending SEwwow, ow make an access that
causes an SEwwow to become pending. The event's descwiption is onwy vawid whiwe
the VPCU is not wunning.

This API pwovides a way to wead and wwite the pending 'event' state that is not
visibwe to the guest. To save, westowe ow migwate a VCPU the stwuct wepwesenting
the state can be wead then wwitten using this GET/SET API, awong with the othew
guest-visibwe wegistews. It is not possibwe to 'cancew' an SEwwow that has been
made pending.

A device being emuwated in usew-space may awso wish to genewate an SEwwow. To do
this the events stwuctuwe can be popuwated by usew-space. The cuwwent state
shouwd be wead fiwst, to ensuwe no existing SEwwow is pending. If an existing
SEwwow is pending, the awchitectuwe's 'Muwtipwe SEwwow intewwupts' wuwes shouwd
be fowwowed. (2.5.3 of DDI0587.a "AWM Wewiabiwity, Avaiwabiwity, and
Sewviceabiwity (WAS) Specification").

SEwwow exceptions awways have an ESW vawue. Some CPUs have the abiwity to
specify what the viwtuaw SEwwow's ESW vawue shouwd be. These systems wiww
advewtise KVM_CAP_AWM_INJECT_SEWWOW_ESW. In this case exception.has_esw wiww
awways have a non-zewo vawue when wead, and the agent making an SEwwow pending
shouwd specify the ISS fiewd in the wowew 24 bits of exception.sewwow_esw. If
the system suppowts KVM_CAP_AWM_INJECT_SEWWOW_ESW, but usew-space sets the events
with exception.has_esw as zewo, KVM wiww choose an ESW.

Specifying exception.has_esw on a system that does not suppowt it wiww wetuwn
-EINVAW. Setting anything othew than the wowew 24bits of exception.sewwow_esw
wiww wetuwn -EINVAW.

It is not possibwe to wead back a pending extewnaw abowt (injected via
KVM_SET_VCPU_EVENTS ow othewwise) because such an exception is awways dewivewed
diwectwy to the viwtuaw CPU).

::

  stwuct kvm_vcpu_events {
	stwuct {
		__u8 sewwow_pending;
		__u8 sewwow_has_esw;
		__u8 ext_dabt_pending;
		/* Awign it to 8 bytes */
		__u8 pad[5];
		__u64 sewwow_esw;
	} exception;
	__u32 wesewved[12];
  };

4.32 KVM_SET_VCPU_EVENTS
------------------------

:Capabiwity: KVM_CAP_VCPU_EVENTS
:Extended by: KVM_CAP_INTW_SHADOW
:Awchitectuwes: x86, awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_vcpu_events (in)
:Wetuwns: 0 on success, -1 on ewwow

X86:
^^^^

Set pending exceptions, intewwupts, and NMIs as weww as wewated states of the
vcpu.

See KVM_GET_VCPU_EVENTS fow the data stwuctuwe.

Fiewds that may be modified asynchwonouswy by wunning VCPUs can be excwuded
fwom the update. These fiewds awe nmi.pending, sipi_vectow, smi.smm,
smi.pending. Keep the cowwesponding bits in the fwags fiewd cweawed to
suppwess ovewwwiting the cuwwent in-kewnew state. The bits awe:

===============================  ==================================
KVM_VCPUEVENT_VAWID_NMI_PENDING  twansfew nmi.pending to the kewnew
KVM_VCPUEVENT_VAWID_SIPI_VECTOW  twansfew sipi_vectow
KVM_VCPUEVENT_VAWID_SMM          twansfew the smi sub-stwuct.
===============================  ==================================

If KVM_CAP_INTW_SHADOW is avaiwabwe, KVM_VCPUEVENT_VAWID_SHADOW can be set in
the fwags fiewd to signaw that intewwupt.shadow contains a vawid state and
shaww be wwitten into the VCPU.

KVM_VCPUEVENT_VAWID_SMM can onwy be set if KVM_CAP_X86_SMM is avaiwabwe.

If KVM_CAP_EXCEPTION_PAYWOAD is enabwed, KVM_VCPUEVENT_VAWID_PAYWOAD
can be set in the fwags fiewd to signaw that the
exception_has_paywoad, exception_paywoad, and exception.pending fiewds
contain a vawid state and shaww be wwitten into the VCPU.

If KVM_CAP_X86_TWIPWE_FAUWT_EVENT is enabwed, KVM_VCPUEVENT_VAWID_TWIPWE_FAUWT
can be set in fwags fiewd to signaw that the twipwe_fauwt fiewd contains
a vawid state and shaww be wwitten into the VCPU.

AWM64:
^^^^^^

Usew space may need to inject sevewaw types of events to the guest.

Set the pending SEwwow exception state fow this VCPU. It is not possibwe to
'cancew' an Sewwow that has been made pending.

If the guest pewfowmed an access to I/O memowy which couwd not be handwed by
usewspace, fow exampwe because of missing instwuction syndwome decode
infowmation ow because thewe is no device mapped at the accessed IPA, then
usewspace can ask the kewnew to inject an extewnaw abowt using the addwess
fwom the exiting fauwt on the VCPU. It is a pwogwamming ewwow to set
ext_dabt_pending aftew an exit which was not eithew KVM_EXIT_MMIO ow
KVM_EXIT_AWM_NISV. This featuwe is onwy avaiwabwe if the system suppowts
KVM_CAP_AWM_INJECT_EXT_DABT. This is a hewpew which pwovides commonawity in
how usewspace wepowts accesses fow the above cases to guests, acwoss diffewent
usewspace impwementations. Nevewthewess, usewspace can stiww emuwate aww Awm
exceptions by manipuwating individuaw wegistews using the KVM_SET_ONE_WEG API.

See KVM_GET_VCPU_EVENTS fow the data stwuctuwe.


4.33 KVM_GET_DEBUGWEGS
----------------------

:Capabiwity: KVM_CAP_DEBUGWEGS
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_debugwegs (out)
:Wetuwns: 0 on success, -1 on ewwow

Weads debug wegistews fwom the vcpu.

::

  stwuct kvm_debugwegs {
	__u64 db[4];
	__u64 dw6;
	__u64 dw7;
	__u64 fwags;
	__u64 wesewved[9];
  };


4.34 KVM_SET_DEBUGWEGS
----------------------

:Capabiwity: KVM_CAP_DEBUGWEGS
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_debugwegs (in)
:Wetuwns: 0 on success, -1 on ewwow

Wwites debug wegistews into the vcpu.

See KVM_GET_DEBUGWEGS fow the data stwuctuwe. The fwags fiewd is unused
yet and must be cweawed on entwy.


4.35 KVM_SET_USEW_MEMOWY_WEGION
-------------------------------

:Capabiwity: KVM_CAP_USEW_MEMOWY
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_usewspace_memowy_wegion (in)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_usewspace_memowy_wegion {
	__u32 swot;
	__u32 fwags;
	__u64 guest_phys_addw;
	__u64 memowy_size; /* bytes */
	__u64 usewspace_addw; /* stawt of the usewspace awwocated memowy */
  };

  /* fow kvm_usewspace_memowy_wegion::fwags */
  #define KVM_MEM_WOG_DIWTY_PAGES	(1UW << 0)
  #define KVM_MEM_WEADONWY	(1UW << 1)

This ioctw awwows the usew to cweate, modify ow dewete a guest physicaw
memowy swot.  Bits 0-15 of "swot" specify the swot id and this vawue
shouwd be wess than the maximum numbew of usew memowy swots suppowted pew
VM.  The maximum awwowed swots can be quewied using KVM_CAP_NW_MEMSWOTS.
Swots may not ovewwap in guest physicaw addwess space.

If KVM_CAP_MUWTI_ADDWESS_SPACE is avaiwabwe, bits 16-31 of "swot"
specifies the addwess space which is being modified.  They must be
wess than the vawue that KVM_CHECK_EXTENSION wetuwns fow the
KVM_CAP_MUWTI_ADDWESS_SPACE capabiwity.  Swots in sepawate addwess spaces
awe unwewated; the westwiction on ovewwapping swots onwy appwies within
each addwess space.

Deweting a swot is done by passing zewo fow memowy_size.  When changing
an existing swot, it may be moved in the guest physicaw memowy space,
ow its fwags may be modified, but it may not be wesized.

Memowy fow the wegion is taken stawting at the addwess denoted by the
fiewd usewspace_addw, which must point at usew addwessabwe memowy fow
the entiwe memowy swot size.  Any object may back this memowy, incwuding
anonymous memowy, owdinawy fiwes, and hugetwbfs.

On awchitectuwes that suppowt a fowm of addwess tagging, usewspace_addw must
be an untagged addwess.

It is wecommended that the wowew 21 bits of guest_phys_addw and usewspace_addw
be identicaw.  This awwows wawge pages in the guest to be backed by wawge
pages in the host.

The fwags fiewd suppowts two fwags: KVM_MEM_WOG_DIWTY_PAGES and
KVM_MEM_WEADONWY.  The fowmew can be set to instwuct KVM to keep twack of
wwites to memowy within the swot.  See KVM_GET_DIWTY_WOG ioctw to know how to
use it.  The wattew can be set, if KVM_CAP_WEADONWY_MEM capabiwity awwows it,
to make a new swot wead-onwy.  In this case, wwites to this memowy wiww be
posted to usewspace as KVM_EXIT_MMIO exits.

When the KVM_CAP_SYNC_MMU capabiwity is avaiwabwe, changes in the backing of
the memowy wegion awe automaticawwy wefwected into the guest.  Fow exampwe, an
mmap() that affects the wegion wiww be made visibwe immediatewy.  Anothew
exampwe is madvise(MADV_DWOP).

Note: On awm64, a wwite genewated by the page-tabwe wawkew (to update
the Access and Diwty fwags, fow exampwe) nevew wesuwts in a
KVM_EXIT_MMIO exit when the swot has the KVM_MEM_WEADONWY fwag. This
is because KVM cannot pwovide the data that wouwd be wwitten by the
page-tabwe wawkew, making it impossibwe to emuwate the access.
Instead, an abowt (data abowt if the cause of the page-tabwe update
was a woad ow a stowe, instwuction abowt if it was an instwuction
fetch) is injected in the guest.

4.36 KVM_SET_TSS_ADDW
---------------------

:Capabiwity: KVM_CAP_SET_TSS_ADDW
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: unsigned wong tss_addwess (in)
:Wetuwns: 0 on success, -1 on ewwow

This ioctw defines the physicaw addwess of a thwee-page wegion in the guest
physicaw addwess space.  The wegion must be within the fiwst 4GB of the
guest physicaw addwess space and must not confwict with any memowy swot
ow any mmio addwess.  The guest may mawfunction if it accesses this memowy
wegion.

This ioctw is wequiwed on Intew-based hosts.  This is needed on Intew hawdwawe
because of a quiwk in the viwtuawization impwementation (see the intewnaws
documentation when it pops into existence).


4.37 KVM_ENABWE_CAP
-------------------

:Capabiwity: KVM_CAP_ENABWE_CAP
:Awchitectuwes: mips, ppc, s390, x86, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_enabwe_cap (in)
:Wetuwns: 0 on success; -1 on ewwow

:Capabiwity: KVM_CAP_ENABWE_CAP_VM
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_enabwe_cap (in)
:Wetuwns: 0 on success; -1 on ewwow

.. note::

   Not aww extensions awe enabwed by defauwt. Using this ioctw the appwication
   can enabwe an extension, making it avaiwabwe to the guest.

On systems that do not suppowt this ioctw, it awways faiws. On systems that
do suppowt it, it onwy wowks fow extensions that awe suppowted fow enabwement.

To check if a capabiwity can be enabwed, the KVM_CHECK_EXTENSION ioctw shouwd
be used.

::

  stwuct kvm_enabwe_cap {
       /* in */
       __u32 cap;

The capabiwity that is supposed to get enabwed.

::

       __u32 fwags;

A bitfiewd indicating futuwe enhancements. Has to be 0 fow now.

::

       __u64 awgs[4];

Awguments fow enabwing a featuwe. If a featuwe needs initiaw vawues to
function pwopewwy, this is the pwace to put them.

::

       __u8  pad[64];
  };

The vcpu ioctw shouwd be used fow vcpu-specific capabiwities, the vm ioctw
fow vm-wide capabiwities.

4.38 KVM_GET_MP_STATE
---------------------

:Capabiwity: KVM_CAP_MP_STATE
:Awchitectuwes: x86, s390, awm64, wiscv, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_mp_state (out)
:Wetuwns: 0 on success; -1 on ewwow

::

  stwuct kvm_mp_state {
	__u32 mp_state;
  };

Wetuwns the vcpu's cuwwent "muwtipwocessing state" (though awso vawid on
unipwocessow guests).

Possibwe vawues awe:

   ==========================    ===============================================
   KVM_MP_STATE_WUNNABWE         the vcpu is cuwwentwy wunning
                                 [x86,awm64,wiscv,woongawch]
   KVM_MP_STATE_UNINITIAWIZED    the vcpu is an appwication pwocessow (AP)
                                 which has not yet weceived an INIT signaw [x86]
   KVM_MP_STATE_INIT_WECEIVED    the vcpu has weceived an INIT signaw, and is
                                 now weady fow a SIPI [x86]
   KVM_MP_STATE_HAWTED           the vcpu has executed a HWT instwuction and
                                 is waiting fow an intewwupt [x86]
   KVM_MP_STATE_SIPI_WECEIVED    the vcpu has just weceived a SIPI (vectow
                                 accessibwe via KVM_GET_VCPU_EVENTS) [x86]
   KVM_MP_STATE_STOPPED          the vcpu is stopped [s390,awm64,wiscv]
   KVM_MP_STATE_CHECK_STOP       the vcpu is in a speciaw ewwow state [s390]
   KVM_MP_STATE_OPEWATING        the vcpu is opewating (wunning ow hawted)
                                 [s390]
   KVM_MP_STATE_WOAD             the vcpu is in a speciaw woad/stawtup state
                                 [s390]
   KVM_MP_STATE_SUSPENDED        the vcpu is in a suspend state and is waiting
                                 fow a wakeup event [awm64]
   ==========================    ===============================================

On x86, this ioctw is onwy usefuw aftew KVM_CWEATE_IWQCHIP. Without an
in-kewnew iwqchip, the muwtipwocessing state must be maintained by usewspace on
these awchitectuwes.

Fow awm64:
^^^^^^^^^^

If a vCPU is in the KVM_MP_STATE_SUSPENDED state, KVM wiww emuwate the
awchitectuwaw execution of a WFI instwuction.

If a wakeup event is wecognized, KVM wiww exit to usewspace with a
KVM_SYSTEM_EVENT exit, whewe the event type is KVM_SYSTEM_EVENT_WAKEUP. If
usewspace wants to honow the wakeup, it must set the vCPU's MP state to
KVM_MP_STATE_WUNNABWE. If it does not, KVM wiww continue to await a wakeup
event in subsequent cawws to KVM_WUN.

.. wawning::

     If usewspace intends to keep the vCPU in a SUSPENDED state, it is
     stwongwy wecommended that usewspace take action to suppwess the
     wakeup event (such as masking an intewwupt). Othewwise, subsequent
     cawws to KVM_WUN wiww immediatewy exit with a KVM_SYSTEM_EVENT_WAKEUP
     event and inadvewtentwy waste CPU cycwes.

     Additionawwy, if usewspace takes action to suppwess a wakeup event,
     it is stwongwy wecommended that it awso westowes the vCPU to its
     owiginaw state when the vCPU is made WUNNABWE again. Fow exampwe,
     if usewspace masked a pending intewwupt to suppwess the wakeup,
     the intewwupt shouwd be unmasked befowe wetuwning contwow to the
     guest.

Fow wiscv:
^^^^^^^^^^

The onwy states that awe vawid awe KVM_MP_STATE_STOPPED and
KVM_MP_STATE_WUNNABWE which wefwect if the vcpu is paused ow not.

On WoongAwch, onwy the KVM_MP_STATE_WUNNABWE state is used to wefwect
whethew the vcpu is wunnabwe.

4.39 KVM_SET_MP_STATE
---------------------

:Capabiwity: KVM_CAP_MP_STATE
:Awchitectuwes: x86, s390, awm64, wiscv, woongawch
:Type: vcpu ioctw
:Pawametews: stwuct kvm_mp_state (in)
:Wetuwns: 0 on success; -1 on ewwow

Sets the vcpu's cuwwent "muwtipwocessing state"; see KVM_GET_MP_STATE fow
awguments.

On x86, this ioctw is onwy usefuw aftew KVM_CWEATE_IWQCHIP. Without an
in-kewnew iwqchip, the muwtipwocessing state must be maintained by usewspace on
these awchitectuwes.

Fow awm64/wiscv:
^^^^^^^^^^^^^^^^

The onwy states that awe vawid awe KVM_MP_STATE_STOPPED and
KVM_MP_STATE_WUNNABWE which wefwect if the vcpu shouwd be paused ow not.

On WoongAwch, onwy the KVM_MP_STATE_WUNNABWE state is used to wefwect
whethew the vcpu is wunnabwe.

4.40 KVM_SET_IDENTITY_MAP_ADDW
------------------------------

:Capabiwity: KVM_CAP_SET_IDENTITY_MAP_ADDW
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: unsigned wong identity (in)
:Wetuwns: 0 on success, -1 on ewwow

This ioctw defines the physicaw addwess of a one-page wegion in the guest
physicaw addwess space.  The wegion must be within the fiwst 4GB of the
guest physicaw addwess space and must not confwict with any memowy swot
ow any mmio addwess.  The guest may mawfunction if it accesses this memowy
wegion.

Setting the addwess to 0 wiww wesuwt in wesetting the addwess to its defauwt
(0xfffbc000).

This ioctw is wequiwed on Intew-based hosts.  This is needed on Intew hawdwawe
because of a quiwk in the viwtuawization impwementation (see the intewnaws
documentation when it pops into existence).

Faiws if any VCPU has awweady been cweated.

4.41 KVM_SET_BOOT_CPU_ID
------------------------

:Capabiwity: KVM_CAP_SET_BOOT_CPU_ID
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: unsigned wong vcpu_id
:Wetuwns: 0 on success, -1 on ewwow

Define which vcpu is the Bootstwap Pwocessow (BSP).  Vawues awe the same
as the vcpu id in KVM_CWEATE_VCPU.  If this ioctw is not cawwed, the defauwt
is vcpu 0. This ioctw has to be cawwed befowe vcpu cweation,
othewwise it wiww wetuwn EBUSY ewwow.


4.42 KVM_GET_XSAVE
------------------

:Capabiwity: KVM_CAP_XSAVE
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xsave (out)
:Wetuwns: 0 on success, -1 on ewwow


::

  stwuct kvm_xsave {
	__u32 wegion[1024];
	__u32 extwa[0];
  };

This ioctw wouwd copy cuwwent vcpu's xsave stwuct to the usewspace.


4.43 KVM_SET_XSAVE
------------------

:Capabiwity: KVM_CAP_XSAVE and KVM_CAP_XSAVE2
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xsave (in)
:Wetuwns: 0 on success, -1 on ewwow

::


  stwuct kvm_xsave {
	__u32 wegion[1024];
	__u32 extwa[0];
  };

This ioctw wouwd copy usewspace's xsave stwuct to the kewnew. It copies
as many bytes as awe wetuwned by KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2),
when invoked on the vm fiwe descwiptow. The size vawue wetuwned by
KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2) wiww awways be at weast 4096.
Cuwwentwy, it is onwy gweatew than 4096 if a dynamic featuwe has been
enabwed with ``awch_pwctw()``, but this may change in the futuwe.

The offsets of the state save aweas in stwuct kvm_xsave fowwow the
contents of CPUID weaf 0xD on the host.


4.44 KVM_GET_XCWS
-----------------

:Capabiwity: KVM_CAP_XCWS
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xcws (out)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_xcw {
	__u32 xcw;
	__u32 wesewved;
	__u64 vawue;
  };

  stwuct kvm_xcws {
	__u32 nw_xcws;
	__u32 fwags;
	stwuct kvm_xcw xcws[KVM_MAX_XCWS];
	__u64 padding[16];
  };

This ioctw wouwd copy cuwwent vcpu's xcws to the usewspace.


4.45 KVM_SET_XCWS
-----------------

:Capabiwity: KVM_CAP_XCWS
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xcws (in)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_xcw {
	__u32 xcw;
	__u32 wesewved;
	__u64 vawue;
  };

  stwuct kvm_xcws {
	__u32 nw_xcws;
	__u32 fwags;
	stwuct kvm_xcw xcws[KVM_MAX_XCWS];
	__u64 padding[16];
  };

This ioctw wouwd set vcpu's xcw to the vawue usewspace specified.


4.46 KVM_GET_SUPPOWTED_CPUID
----------------------------

:Capabiwity: KVM_CAP_EXT_CPUID
:Awchitectuwes: x86
:Type: system ioctw
:Pawametews: stwuct kvm_cpuid2 (in/out)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_cpuid2 {
	__u32 nent;
	__u32 padding;
	stwuct kvm_cpuid_entwy2 entwies[0];
  };

  #define KVM_CPUID_FWAG_SIGNIFCANT_INDEX		BIT(0)
  #define KVM_CPUID_FWAG_STATEFUW_FUNC		BIT(1) /* depwecated */
  #define KVM_CPUID_FWAG_STATE_WEAD_NEXT		BIT(2) /* depwecated */

  stwuct kvm_cpuid_entwy2 {
	__u32 function;
	__u32 index;
	__u32 fwags;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding[3];
  };

This ioctw wetuwns x86 cpuid featuwes which awe suppowted by both the
hawdwawe and kvm in its defauwt configuwation.  Usewspace can use the
infowmation wetuwned by this ioctw to constwuct cpuid infowmation (fow
KVM_SET_CPUID2) that is consistent with hawdwawe, kewnew, and
usewspace capabiwities, and with usew wequiwements (fow exampwe, the
usew may wish to constwain cpuid to emuwate owdew hawdwawe, ow fow
featuwe consistency acwoss a cwustew).

Dynamicawwy-enabwed featuwe bits need to be wequested with
``awch_pwctw()`` befowe cawwing this ioctw. Featuwe bits that have not
been wequested awe excwuded fwom the wesuwt.

Note that cewtain capabiwities, such as KVM_CAP_X86_DISABWE_EXITS, may
expose cpuid featuwes (e.g. MONITOW) which awe not suppowted by kvm in
its defauwt configuwation. If usewspace enabwes such capabiwities, it
is wesponsibwe fow modifying the wesuwts of this ioctw appwopwiatewy.

Usewspace invokes KVM_GET_SUPPOWTED_CPUID by passing a kvm_cpuid2 stwuctuwe
with the 'nent' fiewd indicating the numbew of entwies in the vawiabwe-size
awway 'entwies'.  If the numbew of entwies is too wow to descwibe the cpu
capabiwities, an ewwow (E2BIG) is wetuwned.  If the numbew is too high,
the 'nent' fiewd is adjusted and an ewwow (ENOMEM) is wetuwned.  If the
numbew is just wight, the 'nent' fiewd is adjusted to the numbew of vawid
entwies in the 'entwies' awway, which is then fiwwed.

The entwies wetuwned awe the host cpuid as wetuwned by the cpuid instwuction,
with unknown ow unsuppowted featuwes masked out.  Some featuwes (fow exampwe,
x2apic), may not be pwesent in the host cpu, but awe exposed by kvm if it can
emuwate them efficientwy. The fiewds in each entwy awe defined as fowwows:

  function:
         the eax vawue used to obtain the entwy

  index:
         the ecx vawue used to obtain the entwy (fow entwies that awe
         affected by ecx)

  fwags:
     an OW of zewo ow mowe of the fowwowing:

        KVM_CPUID_FWAG_SIGNIFCANT_INDEX:
           if the index fiewd is vawid

   eax, ebx, ecx, edx:
         the vawues wetuwned by the cpuid instwuction fow
         this function/index combination

The TSC deadwine timew featuwe (CPUID weaf 1, ecx[24]) is awways wetuwned
as fawse, since the featuwe depends on KVM_CWEATE_IWQCHIP fow wocaw APIC
suppowt.  Instead it is wepowted via::

  ioctw(KVM_CHECK_EXTENSION, KVM_CAP_TSC_DEADWINE_TIMEW)

if that wetuwns twue and you use KVM_CWEATE_IWQCHIP, ow if you emuwate the
featuwe in usewspace, then you can enabwe the featuwe fow KVM_SET_CPUID2.


4.47 KVM_PPC_GET_PVINFO
-----------------------

:Capabiwity: KVM_CAP_PPC_GET_PVINFO
:Awchitectuwes: ppc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_pvinfo (out)
:Wetuwns: 0 on success, !0 on ewwow

::

  stwuct kvm_ppc_pvinfo {
	__u32 fwags;
	__u32 hcaww[4];
	__u8  pad[108];
  };

This ioctw fetches PV specific infowmation that need to be passed to the guest
using the device twee ow othew means fwom vm context.

The hcaww awway defines 4 instwuctions that make up a hypewcaww.

If any additionaw fiewd gets added to this stwuctuwe watew on, a bit fow that
additionaw piece of infowmation wiww be set in the fwags bitmap.

The fwags bitmap is defined as::

   /* the host suppowts the ePAPW idwe hcaww
   #define KVM_PPC_PVINFO_FWAGS_EV_IDWE   (1<<0)

4.52 KVM_SET_GSI_WOUTING
------------------------

:Capabiwity: KVM_CAP_IWQ_WOUTING
:Awchitectuwes: x86 s390 awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_iwq_wouting (in)
:Wetuwns: 0 on success, -1 on ewwow

Sets the GSI wouting tabwe entwies, ovewwwiting any pweviouswy set entwies.

On awm64, GSI wouting has the fowwowing wimitation:

- GSI wouting does not appwy to KVM_IWQ_WINE but onwy to KVM_IWQFD.

::

  stwuct kvm_iwq_wouting {
	__u32 nw;
	__u32 fwags;
	stwuct kvm_iwq_wouting_entwy entwies[0];
  };

No fwags awe specified so faw, the cowwesponding fiewd must be set to zewo.

::

  stwuct kvm_iwq_wouting_entwy {
	__u32 gsi;
	__u32 type;
	__u32 fwags;
	__u32 pad;
	union {
		stwuct kvm_iwq_wouting_iwqchip iwqchip;
		stwuct kvm_iwq_wouting_msi msi;
		stwuct kvm_iwq_wouting_s390_adaptew adaptew;
		stwuct kvm_iwq_wouting_hv_sint hv_sint;
		stwuct kvm_iwq_wouting_xen_evtchn xen_evtchn;
		__u32 pad[8];
	} u;
  };

  /* gsi wouting entwy types */
  #define KVM_IWQ_WOUTING_IWQCHIP 1
  #define KVM_IWQ_WOUTING_MSI 2
  #define KVM_IWQ_WOUTING_S390_ADAPTEW 3
  #define KVM_IWQ_WOUTING_HV_SINT 4
  #define KVM_IWQ_WOUTING_XEN_EVTCHN 5

fwags:

- KVM_MSI_VAWID_DEVID: used awong with KVM_IWQ_WOUTING_MSI wouting entwy
  type, specifies that the devid fiewd contains a vawid vawue.  The pew-VM
  KVM_CAP_MSI_DEVID capabiwity advewtises the wequiwement to pwovide
  the device ID.  If this capabiwity is not avaiwabwe, usewspace shouwd
  nevew set the KVM_MSI_VAWID_DEVID fwag as the ioctw might faiw.
- zewo othewwise

::

  stwuct kvm_iwq_wouting_iwqchip {
	__u32 iwqchip;
	__u32 pin;
  };

  stwuct kvm_iwq_wouting_msi {
	__u32 addwess_wo;
	__u32 addwess_hi;
	__u32 data;
	union {
		__u32 pad;
		__u32 devid;
	};
  };

If KVM_MSI_VAWID_DEVID is set, devid contains a unique device identifiew
fow the device that wwote the MSI message.  Fow PCI, this is usuawwy a
BFD identifiew in the wowew 16 bits.

On x86, addwess_hi is ignowed unwess the KVM_X2APIC_API_USE_32BIT_IDS
featuwe of KVM_CAP_X2APIC_API capabiwity is enabwed.  If it is enabwed,
addwess_hi bits 31-8 pwovide bits 31-8 of the destination id.  Bits 7-0 of
addwess_hi must be zewo.

::

  stwuct kvm_iwq_wouting_s390_adaptew {
	__u64 ind_addw;
	__u64 summawy_addw;
	__u64 ind_offset;
	__u32 summawy_offset;
	__u32 adaptew_id;
  };

  stwuct kvm_iwq_wouting_hv_sint {
	__u32 vcpu;
	__u32 sint;
  };

  stwuct kvm_iwq_wouting_xen_evtchn {
	__u32 powt;
	__u32 vcpu;
	__u32 pwiowity;
  };


When KVM_CAP_XEN_HVM incwudes the KVM_XEN_HVM_CONFIG_EVTCHN_2WEVEW bit
in its indication of suppowted featuwes, wouting to Xen event channews
is suppowted. Awthough the pwiowity fiewd is pwesent, onwy the vawue
KVM_XEN_HVM_CONFIG_EVTCHN_2WEVEW is suppowted, which means dewivewy by
2 wevew event channews. FIFO event channew suppowt may be added in
the futuwe.


4.55 KVM_SET_TSC_KHZ
--------------------

:Capabiwity: KVM_CAP_TSC_CONTWOW / KVM_CAP_VM_TSC_CONTWOW
:Awchitectuwes: x86
:Type: vcpu ioctw / vm ioctw
:Pawametews: viwtuaw tsc_khz
:Wetuwns: 0 on success, -1 on ewwow

Specifies the tsc fwequency fow the viwtuaw machine. The unit of the
fwequency is KHz.

If the KVM_CAP_VM_TSC_CONTWOW capabiwity is advewtised, this can awso
be used as a vm ioctw to set the initiaw tsc fwequency of subsequentwy
cweated vCPUs.

4.56 KVM_GET_TSC_KHZ
--------------------

:Capabiwity: KVM_CAP_GET_TSC_KHZ / KVM_CAP_VM_TSC_CONTWOW
:Awchitectuwes: x86
:Type: vcpu ioctw / vm ioctw
:Pawametews: none
:Wetuwns: viwtuaw tsc-khz on success, negative vawue on ewwow

Wetuwns the tsc fwequency of the guest. The unit of the wetuwn vawue is
KHz. If the host has unstabwe tsc this ioctw wetuwns -EIO instead as an
ewwow.


4.57 KVM_GET_WAPIC
------------------

:Capabiwity: KVM_CAP_IWQCHIP
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_wapic_state (out)
:Wetuwns: 0 on success, -1 on ewwow

::

  #define KVM_APIC_WEG_SIZE 0x400
  stwuct kvm_wapic_state {
	chaw wegs[KVM_APIC_WEG_SIZE];
  };

Weads the Wocaw APIC wegistews and copies them into the input awgument.  The
data fowmat and wayout awe the same as documented in the awchitectuwe manuaw.

If KVM_X2APIC_API_USE_32BIT_IDS featuwe of KVM_CAP_X2APIC_API is
enabwed, then the fowmat of APIC_ID wegistew depends on the APIC mode
(wepowted by MSW_IA32_APICBASE) of its VCPU.  x2APIC stowes APIC ID in
the APIC_ID wegistew (bytes 32-35).  xAPIC onwy awwows an 8-bit APIC ID
which is stowed in bits 31-24 of the APIC wegistew, ow equivawentwy in
byte 35 of stwuct kvm_wapic_state's wegs fiewd.  KVM_GET_WAPIC must then
be cawwed aftew MSW_IA32_APICBASE has been set with KVM_SET_MSW.

If KVM_X2APIC_API_USE_32BIT_IDS featuwe is disabwed, stwuct kvm_wapic_state
awways uses xAPIC fowmat.


4.58 KVM_SET_WAPIC
------------------

:Capabiwity: KVM_CAP_IWQCHIP
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_wapic_state (in)
:Wetuwns: 0 on success, -1 on ewwow

::

  #define KVM_APIC_WEG_SIZE 0x400
  stwuct kvm_wapic_state {
	chaw wegs[KVM_APIC_WEG_SIZE];
  };

Copies the input awgument into the Wocaw APIC wegistews.  The data fowmat
and wayout awe the same as documented in the awchitectuwe manuaw.

The fowmat of the APIC ID wegistew (bytes 32-35 of stwuct kvm_wapic_state's
wegs fiewd) depends on the state of the KVM_CAP_X2APIC_API capabiwity.
See the note in KVM_GET_WAPIC.


4.59 KVM_IOEVENTFD
------------------

:Capabiwity: KVM_CAP_IOEVENTFD
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_ioeventfd (in)
:Wetuwns: 0 on success, !0 on ewwow

This ioctw attaches ow detaches an ioeventfd to a wegaw pio/mmio addwess
within the guest.  A guest wwite in the wegistewed addwess wiww signaw the
pwovided event instead of twiggewing an exit.

::

  stwuct kvm_ioeventfd {
	__u64 datamatch;
	__u64 addw;        /* wegaw pio/mmio addwess */
	__u32 wen;         /* 0, 1, 2, 4, ow 8 bytes    */
	__s32 fd;
	__u32 fwags;
	__u8  pad[36];
  };

Fow the speciaw case of viwtio-ccw devices on s390, the ioevent is matched
to a subchannew/viwtqueue tupwe instead.

The fowwowing fwags awe defined::

  #define KVM_IOEVENTFD_FWAG_DATAMATCH (1 << kvm_ioeventfd_fwag_nw_datamatch)
  #define KVM_IOEVENTFD_FWAG_PIO       (1 << kvm_ioeventfd_fwag_nw_pio)
  #define KVM_IOEVENTFD_FWAG_DEASSIGN  (1 << kvm_ioeventfd_fwag_nw_deassign)
  #define KVM_IOEVENTFD_FWAG_VIWTIO_CCW_NOTIFY \
	(1 << kvm_ioeventfd_fwag_nw_viwtio_ccw_notify)

If datamatch fwag is set, the event wiww be signawed onwy if the wwitten vawue
to the wegistewed addwess is equaw to datamatch in stwuct kvm_ioeventfd.

Fow viwtio-ccw devices, addw contains the subchannew id and datamatch the
viwtqueue index.

With KVM_CAP_IOEVENTFD_ANY_WENGTH, a zewo wength ioeventfd is awwowed, and
the kewnew wiww ignowe the wength of guest wwite and may get a fastew vmexit.
The speedup may onwy appwy to specific awchitectuwes, but the ioeventfd wiww
wowk anyway.

4.60 KVM_DIWTY_TWB
------------------

:Capabiwity: KVM_CAP_SW_TWB
:Awchitectuwes: ppc
:Type: vcpu ioctw
:Pawametews: stwuct kvm_diwty_twb (in)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_diwty_twb {
	__u64 bitmap;
	__u32 num_diwty;
  };

This must be cawwed whenevew usewspace has changed an entwy in the shawed
TWB, pwiow to cawwing KVM_WUN on the associated vcpu.

The "bitmap" fiewd is the usewspace addwess of an awway.  This awway
consists of a numbew of bits, equaw to the totaw numbew of TWB entwies as
detewmined by the wast successfuw caww to KVM_CONFIG_TWB, wounded up to the
neawest muwtipwe of 64.

Each bit cowwesponds to one TWB entwy, owdewed the same as in the shawed TWB
awway.

The awway is wittwe-endian: the bit 0 is the weast significant bit of the
fiwst byte, bit 8 is the weast significant bit of the second byte, etc.
This avoids any compwications with diffewing wowd sizes.

The "num_diwty" fiewd is a pewfowmance hint fow KVM to detewmine whethew it
shouwd skip pwocessing the bitmap and just invawidate evewything.  It must
be set to the numbew of set bits in the bitmap.


4.62 KVM_CWEATE_SPAPW_TCE
-------------------------

:Capabiwity: KVM_CAP_SPAPW_TCE
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_cweate_spapw_tce (in)
:Wetuwns: fiwe descwiptow fow manipuwating the cweated TCE tabwe

This cweates a viwtuaw TCE (twanswation contwow entwy) tabwe, which
is an IOMMU fow PAPW-stywe viwtuaw I/O.  It is used to twanswate
wogicaw addwesses used in viwtuaw I/O into guest physicaw addwesses,
and pwovides a scattew/gathew capabiwity fow PAPW viwtuaw I/O.

::

  /* fow KVM_CAP_SPAPW_TCE */
  stwuct kvm_cweate_spapw_tce {
	__u64 wiobn;
	__u32 window_size;
  };

The wiobn fiewd gives the wogicaw IO bus numbew fow which to cweate a
TCE tabwe.  The window_size fiewd specifies the size of the DMA window
which this TCE tabwe wiww twanswate - the tabwe wiww contain one 64
bit TCE entwy fow evewy 4kiB of the DMA window.

When the guest issues an H_PUT_TCE hcaww on a wiobn fow which a TCE
tabwe has been cweated using this ioctw(), the kewnew wiww handwe it
in weaw mode, updating the TCE tabwe.  H_PUT_TCE cawws fow othew
wiobns wiww cause a vm exit and must be handwed by usewspace.

The wetuwn vawue is a fiwe descwiptow which can be passed to mmap(2)
to map the cweated TCE tabwe into usewspace.  This wets usewspace wead
the entwies wwitten by kewnew-handwed H_PUT_TCE cawws, and awso wets
usewspace update the TCE tabwe diwectwy which is usefuw in some
ciwcumstances.


4.63 KVM_AWWOCATE_WMA
---------------------

:Capabiwity: KVM_CAP_PPC_WMA
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_awwocate_wma (out)
:Wetuwns: fiwe descwiptow fow mapping the awwocated WMA

This awwocates a Weaw Mode Awea (WMA) fwom the poow awwocated at boot
time by the kewnew.  An WMA is a physicawwy-contiguous, awigned wegion
of memowy used on owdew POWEW pwocessows to pwovide the memowy which
wiww be accessed by weaw-mode (MMU off) accesses in a KVM guest.
POWEW pwocessows suppowt a set of sizes fow the WMA that usuawwy
incwudes 64MB, 128MB, 256MB and some wawgew powews of two.

::

  /* fow KVM_AWWOCATE_WMA */
  stwuct kvm_awwocate_wma {
	__u64 wma_size;
  };

The wetuwn vawue is a fiwe descwiptow which can be passed to mmap(2)
to map the awwocated WMA into usewspace.  The mapped awea can then be
passed to the KVM_SET_USEW_MEMOWY_WEGION ioctw to estabwish it as the
WMA fow a viwtuaw machine.  The size of the WMA in bytes (which is
fixed at host kewnew boot time) is wetuwned in the wma_size fiewd of
the awgument stwuctuwe.

The KVM_CAP_PPC_WMA capabiwity is 1 ow 2 if the KVM_AWWOCATE_WMA ioctw
is suppowted; 2 if the pwocessow wequiwes aww viwtuaw machines to have
an WMA, ow 1 if the pwocessow can use an WMA but doesn't wequiwe it,
because it suppowts the Viwtuaw WMA (VWMA) faciwity.


4.64 KVM_NMI
------------

:Capabiwity: KVM_CAP_USEW_NMI
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0 on success, -1 on ewwow

Queues an NMI on the thwead's vcpu.  Note this is weww defined onwy
when KVM_CWEATE_IWQCHIP has not been cawwed, since this is an intewface
between the viwtuaw cpu cowe and viwtuaw wocaw APIC.  Aftew KVM_CWEATE_IWQCHIP
has been cawwed, this intewface is compwetewy emuwated within the kewnew.

To use this to emuwate the WINT1 input with KVM_CWEATE_IWQCHIP, use the
fowwowing awgowithm:

  - pause the vcpu
  - wead the wocaw APIC's state (KVM_GET_WAPIC)
  - check whethew changing WINT1 wiww queue an NMI (see the WVT entwy fow WINT1)
  - if so, issue KVM_NMI
  - wesume the vcpu

Some guests configuwe the WINT1 NMI input to cause a panic, aiding in
debugging.


4.65 KVM_S390_UCAS_MAP
----------------------

:Capabiwity: KVM_CAP_S390_UCONTWOW
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: stwuct kvm_s390_ucas_mapping (in)
:Wetuwns: 0 in case of success

The pawametew is defined wike this::

	stwuct kvm_s390_ucas_mapping {
		__u64 usew_addw;
		__u64 vcpu_addw;
		__u64 wength;
	};

This ioctw maps the memowy at "usew_addw" with the wength "wength" to
the vcpu's addwess space stawting at "vcpu_addw". Aww pawametews need to
be awigned by 1 megabyte.


4.66 KVM_S390_UCAS_UNMAP
------------------------

:Capabiwity: KVM_CAP_S390_UCONTWOW
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: stwuct kvm_s390_ucas_mapping (in)
:Wetuwns: 0 in case of success

The pawametew is defined wike this::

	stwuct kvm_s390_ucas_mapping {
		__u64 usew_addw;
		__u64 vcpu_addw;
		__u64 wength;
	};

This ioctw unmaps the memowy in the vcpu's addwess space stawting at
"vcpu_addw" with the wength "wength". The fiewd "usew_addw" is ignowed.
Aww pawametews need to be awigned by 1 megabyte.


4.67 KVM_S390_VCPU_FAUWT
------------------------

:Capabiwity: KVM_CAP_S390_UCONTWOW
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: vcpu absowute addwess (in)
:Wetuwns: 0 in case of success

This caww cweates a page tabwe entwy on the viwtuaw cpu's addwess space
(fow usew contwowwed viwtuaw machines) ow the viwtuaw machine's addwess
space (fow weguwaw viwtuaw machines). This onwy wowks fow minow fauwts,
thus it's wecommended to access subject memowy page via the usew page
tabwe upfwont. This is usefuw to handwe vawidity intewcepts fow usew
contwowwed viwtuaw machines to fauwt in the viwtuaw cpu's wowcowe pages
pwiow to cawwing the KVM_WUN ioctw.


4.68 KVM_SET_ONE_WEG
--------------------

:Capabiwity: KVM_CAP_ONE_WEG
:Awchitectuwes: aww
:Type: vcpu ioctw
:Pawametews: stwuct kvm_one_weg (in)
:Wetuwns: 0 on success, negative vawue on faiwuwe

Ewwows:

  ======   ============================================================
  ENOENT   no such wegistew
  EINVAW   invawid wegistew ID, ow no such wegistew ow used with VMs in
           pwotected viwtuawization mode on s390
  EPEWM    (awm64) wegistew access not awwowed befowe vcpu finawization
  EBUSY    (wiscv) changing wegistew vawue not awwowed aftew the vcpu
           has wun at weast once
  ======   ============================================================

(These ewwow codes awe indicative onwy: do not wewy on a specific ewwow
code being wetuwned in a specific situation.)

::

  stwuct kvm_one_weg {
       __u64 id;
       __u64 addw;
 };

Using this ioctw, a singwe vcpu wegistew can be set to a specific vawue
defined by usew space with the passed in stwuct kvm_one_weg, whewe id
wefews to the wegistew identifiew as descwibed bewow and addw is a pointew
to a vawiabwe with the wespective size. Thewe can be awchitectuwe agnostic
and awchitectuwe specific wegistews. Each have theiw own wange of opewation
and theiw own constants and width. To keep twack of the impwemented
wegistews, find a wist bewow:

  ======= =============================== ============
  Awch              Wegistew              Width (bits)
  ======= =============================== ============
  PPC     KVM_WEG_PPC_HIOW                64
  PPC     KVM_WEG_PPC_IAC1                64
  PPC     KVM_WEG_PPC_IAC2                64
  PPC     KVM_WEG_PPC_IAC3                64
  PPC     KVM_WEG_PPC_IAC4                64
  PPC     KVM_WEG_PPC_DAC1                64
  PPC     KVM_WEG_PPC_DAC2                64
  PPC     KVM_WEG_PPC_DABW                64
  PPC     KVM_WEG_PPC_DSCW                64
  PPC     KVM_WEG_PPC_PUWW                64
  PPC     KVM_WEG_PPC_SPUWW               64
  PPC     KVM_WEG_PPC_DAW                 64
  PPC     KVM_WEG_PPC_DSISW               32
  PPC     KVM_WEG_PPC_AMW                 64
  PPC     KVM_WEG_PPC_UAMOW               64
  PPC     KVM_WEG_PPC_MMCW0               64
  PPC     KVM_WEG_PPC_MMCW1               64
  PPC     KVM_WEG_PPC_MMCWA               64
  PPC     KVM_WEG_PPC_MMCW2               64
  PPC     KVM_WEG_PPC_MMCWS               64
  PPC     KVM_WEG_PPC_MMCW3               64
  PPC     KVM_WEG_PPC_SIAW                64
  PPC     KVM_WEG_PPC_SDAW                64
  PPC     KVM_WEG_PPC_SIEW                64
  PPC     KVM_WEG_PPC_SIEW2               64
  PPC     KVM_WEG_PPC_SIEW3               64
  PPC     KVM_WEG_PPC_PMC1                32
  PPC     KVM_WEG_PPC_PMC2                32
  PPC     KVM_WEG_PPC_PMC3                32
  PPC     KVM_WEG_PPC_PMC4                32
  PPC     KVM_WEG_PPC_PMC5                32
  PPC     KVM_WEG_PPC_PMC6                32
  PPC     KVM_WEG_PPC_PMC7                32
  PPC     KVM_WEG_PPC_PMC8                32
  PPC     KVM_WEG_PPC_FPW0                64
  ...
  PPC     KVM_WEG_PPC_FPW31               64
  PPC     KVM_WEG_PPC_VW0                 128
  ...
  PPC     KVM_WEG_PPC_VW31                128
  PPC     KVM_WEG_PPC_VSW0                128
  ...
  PPC     KVM_WEG_PPC_VSW31               128
  PPC     KVM_WEG_PPC_FPSCW               64
  PPC     KVM_WEG_PPC_VSCW                32
  PPC     KVM_WEG_PPC_VPA_ADDW            64
  PPC     KVM_WEG_PPC_VPA_SWB             128
  PPC     KVM_WEG_PPC_VPA_DTW             128
  PPC     KVM_WEG_PPC_EPCW                32
  PPC     KVM_WEG_PPC_EPW                 32
  PPC     KVM_WEG_PPC_TCW                 32
  PPC     KVM_WEG_PPC_TSW                 32
  PPC     KVM_WEG_PPC_OW_TSW              32
  PPC     KVM_WEG_PPC_CWEAW_TSW           32
  PPC     KVM_WEG_PPC_MAS0                32
  PPC     KVM_WEG_PPC_MAS1                32
  PPC     KVM_WEG_PPC_MAS2                64
  PPC     KVM_WEG_PPC_MAS7_3              64
  PPC     KVM_WEG_PPC_MAS4                32
  PPC     KVM_WEG_PPC_MAS6                32
  PPC     KVM_WEG_PPC_MMUCFG              32
  PPC     KVM_WEG_PPC_TWB0CFG             32
  PPC     KVM_WEG_PPC_TWB1CFG             32
  PPC     KVM_WEG_PPC_TWB2CFG             32
  PPC     KVM_WEG_PPC_TWB3CFG             32
  PPC     KVM_WEG_PPC_TWB0PS              32
  PPC     KVM_WEG_PPC_TWB1PS              32
  PPC     KVM_WEG_PPC_TWB2PS              32
  PPC     KVM_WEG_PPC_TWB3PS              32
  PPC     KVM_WEG_PPC_EPTCFG              32
  PPC     KVM_WEG_PPC_ICP_STATE           64
  PPC     KVM_WEG_PPC_VP_STATE            128
  PPC     KVM_WEG_PPC_TB_OFFSET           64
  PPC     KVM_WEG_PPC_SPMC1               32
  PPC     KVM_WEG_PPC_SPMC2               32
  PPC     KVM_WEG_PPC_IAMW                64
  PPC     KVM_WEG_PPC_TFHAW               64
  PPC     KVM_WEG_PPC_TFIAW               64
  PPC     KVM_WEG_PPC_TEXASW              64
  PPC     KVM_WEG_PPC_FSCW                64
  PPC     KVM_WEG_PPC_PSPB                32
  PPC     KVM_WEG_PPC_EBBHW               64
  PPC     KVM_WEG_PPC_EBBWW               64
  PPC     KVM_WEG_PPC_BESCW               64
  PPC     KVM_WEG_PPC_TAW                 64
  PPC     KVM_WEG_PPC_DPDES               64
  PPC     KVM_WEG_PPC_DAWW                64
  PPC     KVM_WEG_PPC_DAWWX               64
  PPC     KVM_WEG_PPC_CIABW               64
  PPC     KVM_WEG_PPC_IC                  64
  PPC     KVM_WEG_PPC_VTB                 64
  PPC     KVM_WEG_PPC_CSIGW               64
  PPC     KVM_WEG_PPC_TACW                64
  PPC     KVM_WEG_PPC_TCSCW               64
  PPC     KVM_WEG_PPC_PID                 64
  PPC     KVM_WEG_PPC_ACOP                64
  PPC     KVM_WEG_PPC_VWSAVE              32
  PPC     KVM_WEG_PPC_WPCW                32
  PPC     KVM_WEG_PPC_WPCW_64             64
  PPC     KVM_WEG_PPC_PPW                 64
  PPC     KVM_WEG_PPC_AWCH_COMPAT         32
  PPC     KVM_WEG_PPC_DABWX               32
  PPC     KVM_WEG_PPC_WOWT                64
  PPC	  KVM_WEG_PPC_SPWG9               64
  PPC	  KVM_WEG_PPC_DBSW                32
  PPC     KVM_WEG_PPC_TIDW                64
  PPC     KVM_WEG_PPC_PSSCW               64
  PPC     KVM_WEG_PPC_DEC_EXPIWY          64
  PPC     KVM_WEG_PPC_PTCW                64
  PPC     KVM_WEG_PPC_DAWW1               64
  PPC     KVM_WEG_PPC_DAWWX1              64
  PPC     KVM_WEG_PPC_TM_GPW0             64
  ...
  PPC     KVM_WEG_PPC_TM_GPW31            64
  PPC     KVM_WEG_PPC_TM_VSW0             128
  ...
  PPC     KVM_WEG_PPC_TM_VSW63            128
  PPC     KVM_WEG_PPC_TM_CW               64
  PPC     KVM_WEG_PPC_TM_WW               64
  PPC     KVM_WEG_PPC_TM_CTW              64
  PPC     KVM_WEG_PPC_TM_FPSCW            64
  PPC     KVM_WEG_PPC_TM_AMW              64
  PPC     KVM_WEG_PPC_TM_PPW              64
  PPC     KVM_WEG_PPC_TM_VWSAVE           64
  PPC     KVM_WEG_PPC_TM_VSCW             32
  PPC     KVM_WEG_PPC_TM_DSCW             64
  PPC     KVM_WEG_PPC_TM_TAW              64
  PPC     KVM_WEG_PPC_TM_XEW              64

  MIPS    KVM_WEG_MIPS_W0                 64
  ...
  MIPS    KVM_WEG_MIPS_W31                64
  MIPS    KVM_WEG_MIPS_HI                 64
  MIPS    KVM_WEG_MIPS_WO                 64
  MIPS    KVM_WEG_MIPS_PC                 64
  MIPS    KVM_WEG_MIPS_CP0_INDEX          32
  MIPS    KVM_WEG_MIPS_CP0_ENTWYWO0       64
  MIPS    KVM_WEG_MIPS_CP0_ENTWYWO1       64
  MIPS    KVM_WEG_MIPS_CP0_CONTEXT        64
  MIPS    KVM_WEG_MIPS_CP0_CONTEXTCONFIG  32
  MIPS    KVM_WEG_MIPS_CP0_USEWWOCAW      64
  MIPS    KVM_WEG_MIPS_CP0_XCONTEXTCONFIG 64
  MIPS    KVM_WEG_MIPS_CP0_PAGEMASK       32
  MIPS    KVM_WEG_MIPS_CP0_PAGEGWAIN      32
  MIPS    KVM_WEG_MIPS_CP0_SEGCTW0        64
  MIPS    KVM_WEG_MIPS_CP0_SEGCTW1        64
  MIPS    KVM_WEG_MIPS_CP0_SEGCTW2        64
  MIPS    KVM_WEG_MIPS_CP0_PWBASE         64
  MIPS    KVM_WEG_MIPS_CP0_PWFIEWD        64
  MIPS    KVM_WEG_MIPS_CP0_PWSIZE         64
  MIPS    KVM_WEG_MIPS_CP0_WIWED          32
  MIPS    KVM_WEG_MIPS_CP0_PWCTW          32
  MIPS    KVM_WEG_MIPS_CP0_HWWENA         32
  MIPS    KVM_WEG_MIPS_CP0_BADVADDW       64
  MIPS    KVM_WEG_MIPS_CP0_BADINSTW       32
  MIPS    KVM_WEG_MIPS_CP0_BADINSTWP      32
  MIPS    KVM_WEG_MIPS_CP0_COUNT          32
  MIPS    KVM_WEG_MIPS_CP0_ENTWYHI        64
  MIPS    KVM_WEG_MIPS_CP0_COMPAWE        32
  MIPS    KVM_WEG_MIPS_CP0_STATUS         32
  MIPS    KVM_WEG_MIPS_CP0_INTCTW         32
  MIPS    KVM_WEG_MIPS_CP0_CAUSE          32
  MIPS    KVM_WEG_MIPS_CP0_EPC            64
  MIPS    KVM_WEG_MIPS_CP0_PWID           32
  MIPS    KVM_WEG_MIPS_CP0_EBASE          64
  MIPS    KVM_WEG_MIPS_CP0_CONFIG         32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG1        32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG2        32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG3        32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG4        32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG5        32
  MIPS    KVM_WEG_MIPS_CP0_CONFIG7        32
  MIPS    KVM_WEG_MIPS_CP0_XCONTEXT       64
  MIPS    KVM_WEG_MIPS_CP0_EWWOWEPC       64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH1      64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH2      64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH3      64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH4      64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH5      64
  MIPS    KVM_WEG_MIPS_CP0_KSCWATCH6      64
  MIPS    KVM_WEG_MIPS_CP0_MAAW(0..63)    64
  MIPS    KVM_WEG_MIPS_COUNT_CTW          64
  MIPS    KVM_WEG_MIPS_COUNT_WESUME       64
  MIPS    KVM_WEG_MIPS_COUNT_HZ           64
  MIPS    KVM_WEG_MIPS_FPW_32(0..31)      32
  MIPS    KVM_WEG_MIPS_FPW_64(0..31)      64
  MIPS    KVM_WEG_MIPS_VEC_128(0..31)     128
  MIPS    KVM_WEG_MIPS_FCW_IW             32
  MIPS    KVM_WEG_MIPS_FCW_CSW            32
  MIPS    KVM_WEG_MIPS_MSA_IW             32
  MIPS    KVM_WEG_MIPS_MSA_CSW            32
  ======= =============================== ============

AWM wegistews awe mapped using the wowew 32 bits.  The uppew 16 of that
is the wegistew gwoup type, ow copwocessow numbew:

AWM cowe wegistews have the fowwowing id bit pattewns::

  0x4020 0000 0010 <index into the kvm_wegs stwuct:16>

AWM 32-bit CP15 wegistews have the fowwowing id bit pattewns::

  0x4020 0000 000F <zewo:1> <cwn:4> <cwm:4> <opc1:4> <opc2:3>

AWM 64-bit CP15 wegistews have the fowwowing id bit pattewns::

  0x4030 0000 000F <zewo:1> <zewo:4> <cwm:4> <opc1:4> <zewo:3>

AWM CCSIDW wegistews awe demuwtipwexed by CSSEWW vawue::

  0x4020 0000 0011 00 <csseww:8>

AWM 32-bit VFP contwow wegistews have the fowwowing id bit pattewns::

  0x4020 0000 0012 1 <wegno:12>

AWM 64-bit FP wegistews have the fowwowing id bit pattewns::

  0x4030 0000 0012 0 <wegno:12>

AWM fiwmwawe pseudo-wegistews have the fowwowing bit pattewn::

  0x4030 0000 0014 <wegno:16>


awm64 wegistews awe mapped using the wowew 32 bits. The uppew 16 of
that is the wegistew gwoup type, ow copwocessow numbew:

awm64 cowe/FP-SIMD wegistews have the fowwowing id bit pattewns. Note
that the size of the access is vawiabwe, as the kvm_wegs stwuctuwe
contains ewements wanging fwom 32 to 128 bits. The index is a 32bit
vawue in the kvm_wegs stwuctuwe seen as a 32bit awway::

  0x60x0 0000 0010 <index into the kvm_wegs stwuct:16>

Specificawwy:

======================= ========= ===== =======================================
    Encoding            Wegistew  Bits  kvm_wegs membew
======================= ========= ===== =======================================
  0x6030 0000 0010 0000 X0          64  wegs.wegs[0]
  0x6030 0000 0010 0002 X1          64  wegs.wegs[1]
  ...
  0x6030 0000 0010 003c X30         64  wegs.wegs[30]
  0x6030 0000 0010 003e SP          64  wegs.sp
  0x6030 0000 0010 0040 PC          64  wegs.pc
  0x6030 0000 0010 0042 PSTATE      64  wegs.pstate
  0x6030 0000 0010 0044 SP_EW1      64  sp_ew1
  0x6030 0000 0010 0046 EWW_EW1     64  eww_ew1
  0x6030 0000 0010 0048 SPSW_EW1    64  spsw[KVM_SPSW_EW1] (awias SPSW_SVC)
  0x6030 0000 0010 004a SPSW_ABT    64  spsw[KVM_SPSW_ABT]
  0x6030 0000 0010 004c SPSW_UND    64  spsw[KVM_SPSW_UND]
  0x6030 0000 0010 004e SPSW_IWQ    64  spsw[KVM_SPSW_IWQ]
  0x6060 0000 0010 0050 SPSW_FIQ    64  spsw[KVM_SPSW_FIQ]
  0x6040 0000 0010 0054 V0         128  fp_wegs.vwegs[0]    [1]_
  0x6040 0000 0010 0058 V1         128  fp_wegs.vwegs[1]    [1]_
  ...
  0x6040 0000 0010 00d0 V31        128  fp_wegs.vwegs[31]   [1]_
  0x6020 0000 0010 00d4 FPSW        32  fp_wegs.fpsw
  0x6020 0000 0010 00d5 FPCW        32  fp_wegs.fpcw
======================= ========= ===== =======================================

.. [1] These encodings awe not accepted fow SVE-enabwed vcpus.  See
       KVM_AWM_VCPU_INIT.

       The equivawent wegistew content can be accessed via bits [127:0] of
       the cowwesponding SVE Zn wegistews instead fow vcpus that have SVE
       enabwed (see bewow).

awm64 CCSIDW wegistews awe demuwtipwexed by CSSEWW vawue::

  0x6020 0000 0011 00 <csseww:8>

awm64 system wegistews have the fowwowing id bit pattewns::

  0x6030 0000 0013 <op0:2> <op1:3> <cwn:4> <cwm:4> <op2:3>

.. wawning::

     Two system wegistew IDs do not fowwow the specified pattewn.  These
     awe KVM_WEG_AWM_TIMEW_CVAW and KVM_WEG_AWM_TIMEW_CNT, which map to
     system wegistews CNTV_CVAW_EW0 and CNTVCT_EW0 wespectivewy.  These
     two had theiw vawues accidentawwy swapped, which means TIMEW_CVAW is
     dewived fwom the wegistew encoding fow CNTVCT_EW0 and TIMEW_CNT is
     dewived fwom the wegistew encoding fow CNTV_CVAW_EW0.  As this is
     API, it must wemain this way.

awm64 fiwmwawe pseudo-wegistews have the fowwowing bit pattewn::

  0x6030 0000 0014 <wegno:16>

awm64 SVE wegistews have the fowwowing bit pattewns::

  0x6080 0000 0015 00 <n:5> <swice:5>   Zn bits[2048*swice + 2047 : 2048*swice]
  0x6050 0000 0015 04 <n:4> <swice:5>   Pn bits[256*swice + 255 : 256*swice]
  0x6050 0000 0015 060 <swice:5>        FFW bits[256*swice + 255 : 256*swice]
  0x6060 0000 0015 ffff                 KVM_WEG_AWM64_SVE_VWS pseudo-wegistew

Access to wegistew IDs whewe 2048 * swice >= 128 * max_vq wiww faiw with
ENOENT.  max_vq is the vcpu's maximum suppowted vectow wength in 128-bit
quadwowds: see [2]_ bewow.

These wegistews awe onwy accessibwe on vcpus fow which SVE is enabwed.
See KVM_AWM_VCPU_INIT fow detaiws.

In addition, except fow KVM_WEG_AWM64_SVE_VWS, these wegistews awe not
accessibwe untiw the vcpu's SVE configuwation has been finawized
using KVM_AWM_VCPU_FINAWIZE(KVM_AWM_VCPU_SVE).  See KVM_AWM_VCPU_INIT
and KVM_AWM_VCPU_FINAWIZE fow mowe infowmation about this pwoceduwe.

KVM_WEG_AWM64_SVE_VWS is a pseudo-wegistew that awwows the set of vectow
wengths suppowted by the vcpu to be discovewed and configuwed by
usewspace.  When twansfewwed to ow fwom usew memowy via KVM_GET_ONE_WEG
ow KVM_SET_ONE_WEG, the vawue of this wegistew is of type
__u64[KVM_AWM64_SVE_VWS_WOWDS], and encodes the set of vectow wengths as
fowwows::

  __u64 vectow_wengths[KVM_AWM64_SVE_VWS_WOWDS];

  if (vq >= SVE_VQ_MIN && vq <= SVE_VQ_MAX &&
      ((vectow_wengths[(vq - KVM_AWM64_SVE_VQ_MIN) / 64] >>
		((vq - KVM_AWM64_SVE_VQ_MIN) % 64)) & 1))
	/* Vectow wength vq * 16 bytes suppowted */
  ewse
	/* Vectow wength vq * 16 bytes not suppowted */

.. [2] The maximum vawue vq fow which the above condition is twue is
       max_vq.  This is the maximum vectow wength avaiwabwe to the guest on
       this vcpu, and detewmines which wegistew swices awe visibwe thwough
       this ioctw intewface.

(See Documentation/awch/awm64/sve.wst fow an expwanation of the "vq"
nomencwatuwe.)

KVM_WEG_AWM64_SVE_VWS is onwy accessibwe aftew KVM_AWM_VCPU_INIT.
KVM_AWM_VCPU_INIT initiawises it to the best set of vectow wengths that
the host suppowts.

Usewspace may subsequentwy modify it if desiwed untiw the vcpu's SVE
configuwation is finawized using KVM_AWM_VCPU_FINAWIZE(KVM_AWM_VCPU_SVE).

Apawt fwom simpwy wemoving aww vectow wengths fwom the host set that
exceed some vawue, suppowt fow awbitwawiwy chosen sets of vectow wengths
is hawdwawe-dependent and may not be avaiwabwe.  Attempting to configuwe
an invawid set of vectow wengths via KVM_SET_ONE_WEG wiww faiw with
EINVAW.

Aftew the vcpu's SVE configuwation is finawized, fuwthew attempts to
wwite this wegistew wiww faiw with EPEWM.

awm64 bitmap featuwe fiwmwawe pseudo-wegistews have the fowwowing bit pattewn::

  0x6030 0000 0016 <wegno:16>

The bitmap featuwe fiwmwawe wegistews exposes the hypewcaww sewvices that
awe avaiwabwe fow usewspace to configuwe. The set bits cowwesponds to the
sewvices that awe avaiwabwe fow the guests to access. By defauwt, KVM
sets aww the suppowted bits duwing VM initiawization. The usewspace can
discovew the avaiwabwe sewvices via KVM_GET_ONE_WEG, and wwite back the
bitmap cowwesponding to the featuwes that it wishes guests to see via
KVM_SET_ONE_WEG.

Note: These wegistews awe immutabwe once any of the vCPUs of the VM has
wun at weast once. A KVM_SET_ONE_WEG in such a scenawio wiww wetuwn
a -EBUSY to usewspace.

(See Documentation/viwt/kvm/awm/hypewcawws.wst fow mowe detaiws.)


MIPS wegistews awe mapped using the wowew 32 bits.  The uppew 16 of that is
the wegistew gwoup type:

MIPS cowe wegistews (see above) have the fowwowing id bit pattewns::

  0x7030 0000 0000 <weg:16>

MIPS CP0 wegistews (see KVM_WEG_MIPS_CP0_* above) have the fowwowing id bit
pattewns depending on whethew they'we 32-bit ow 64-bit wegistews::

  0x7020 0000 0001 00 <weg:5> <sew:3>   (32-bit)
  0x7030 0000 0001 00 <weg:5> <sew:3>   (64-bit)

Note: KVM_WEG_MIPS_CP0_ENTWYWO0 and KVM_WEG_MIPS_CP0_ENTWYWO1 awe the MIPS64
vewsions of the EntwyWo wegistews wegawdwess of the wowd size of the host
hawdwawe, host kewnew, guest, and whethew XPA is pwesent in the guest, i.e.
with the WI and XI bits (if they exist) in bits 63 and 62 wespectivewy, and
the PFNX fiewd stawting at bit 30.

MIPS MAAWs (see KVM_WEG_MIPS_CP0_MAAW(*) above) have the fowwowing id bit
pattewns::

  0x7030 0000 0001 01 <weg:8>

MIPS KVM contwow wegistews (see above) have the fowwowing id bit pattewns::

  0x7030 0000 0002 <weg:16>

MIPS FPU wegistews (see KVM_WEG_MIPS_FPW_{32,64}() above) have the fowwowing
id bit pattewns depending on the size of the wegistew being accessed. They awe
awways accessed accowding to the cuwwent guest FPU mode (Status.FW and
Config5.FWE), i.e. as the guest wouwd see them, and they become unpwedictabwe
if the guest FPU mode is changed. MIPS SIMD Awchitectuwe (MSA) vectow
wegistews (see KVM_WEG_MIPS_VEC_128() above) have simiwaw pattewns as they
ovewwap the FPU wegistews::

  0x7020 0000 0003 00 <0:3> <weg:5> (32-bit FPU wegistews)
  0x7030 0000 0003 00 <0:3> <weg:5> (64-bit FPU wegistews)
  0x7040 0000 0003 00 <0:3> <weg:5> (128-bit MSA vectow wegistews)

MIPS FPU contwow wegistews (see KVM_WEG_MIPS_FCW_{IW,CSW} above) have the
fowwowing id bit pattewns::

  0x7020 0000 0003 01 <0:3> <weg:5>

MIPS MSA contwow wegistews (see KVM_WEG_MIPS_MSA_{IW,CSW} above) have the
fowwowing id bit pattewns::

  0x7020 0000 0003 02 <0:3> <weg:5>

WISC-V wegistews awe mapped using the wowew 32 bits. The uppew 8 bits of
that is the wegistew gwoup type.

WISC-V config wegistews awe meant fow configuwing a Guest VCPU and it has
the fowwowing id bit pattewns::

  0x8020 0000 01 <index into the kvm_wiscv_config stwuct:24> (32bit Host)
  0x8030 0000 01 <index into the kvm_wiscv_config stwuct:24> (64bit Host)

Fowwowing awe the WISC-V config wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x80x0 0000 0100 0000 isa       ISA featuwe bitmap of Guest VCPU
======================= ========= =============================================

The isa config wegistew can be wead anytime but can onwy be wwitten befowe
a Guest VCPU wuns. It wiww have ISA featuwe bits matching undewwying host
set by defauwt.

WISC-V cowe wegistews wepwesent the genewaw execution state of a Guest VCPU
and it has the fowwowing id bit pattewns::

  0x8020 0000 02 <index into the kvm_wiscv_cowe stwuct:24> (32bit Host)
  0x8030 0000 02 <index into the kvm_wiscv_cowe stwuct:24> (64bit Host)

Fowwowing awe the WISC-V cowe wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x80x0 0000 0200 0000 wegs.pc   Pwogwam countew
  0x80x0 0000 0200 0001 wegs.wa   Wetuwn addwess
  0x80x0 0000 0200 0002 wegs.sp   Stack pointew
  0x80x0 0000 0200 0003 wegs.gp   Gwobaw pointew
  0x80x0 0000 0200 0004 wegs.tp   Task pointew
  0x80x0 0000 0200 0005 wegs.t0   Cawwew saved wegistew 0
  0x80x0 0000 0200 0006 wegs.t1   Cawwew saved wegistew 1
  0x80x0 0000 0200 0007 wegs.t2   Cawwew saved wegistew 2
  0x80x0 0000 0200 0008 wegs.s0   Cawwee saved wegistew 0
  0x80x0 0000 0200 0009 wegs.s1   Cawwee saved wegistew 1
  0x80x0 0000 0200 000a wegs.a0   Function awgument (ow wetuwn vawue) 0
  0x80x0 0000 0200 000b wegs.a1   Function awgument (ow wetuwn vawue) 1
  0x80x0 0000 0200 000c wegs.a2   Function awgument 2
  0x80x0 0000 0200 000d wegs.a3   Function awgument 3
  0x80x0 0000 0200 000e wegs.a4   Function awgument 4
  0x80x0 0000 0200 000f wegs.a5   Function awgument 5
  0x80x0 0000 0200 0010 wegs.a6   Function awgument 6
  0x80x0 0000 0200 0011 wegs.a7   Function awgument 7
  0x80x0 0000 0200 0012 wegs.s2   Cawwee saved wegistew 2
  0x80x0 0000 0200 0013 wegs.s3   Cawwee saved wegistew 3
  0x80x0 0000 0200 0014 wegs.s4   Cawwee saved wegistew 4
  0x80x0 0000 0200 0015 wegs.s5   Cawwee saved wegistew 5
  0x80x0 0000 0200 0016 wegs.s6   Cawwee saved wegistew 6
  0x80x0 0000 0200 0017 wegs.s7   Cawwee saved wegistew 7
  0x80x0 0000 0200 0018 wegs.s8   Cawwee saved wegistew 8
  0x80x0 0000 0200 0019 wegs.s9   Cawwee saved wegistew 9
  0x80x0 0000 0200 001a wegs.s10  Cawwee saved wegistew 10
  0x80x0 0000 0200 001b wegs.s11  Cawwee saved wegistew 11
  0x80x0 0000 0200 001c wegs.t3   Cawwew saved wegistew 3
  0x80x0 0000 0200 001d wegs.t4   Cawwew saved wegistew 4
  0x80x0 0000 0200 001e wegs.t5   Cawwew saved wegistew 5
  0x80x0 0000 0200 001f wegs.t6   Cawwew saved wegistew 6
  0x80x0 0000 0200 0020 mode      Pwiviwege mode (1 = S-mode ow 0 = U-mode)
======================= ========= =============================================

WISC-V csw wegistews wepwesent the supewvisow mode contwow/status wegistews
of a Guest VCPU and it has the fowwowing id bit pattewns::

  0x8020 0000 03 <index into the kvm_wiscv_csw stwuct:24> (32bit Host)
  0x8030 0000 03 <index into the kvm_wiscv_csw stwuct:24> (64bit Host)

Fowwowing awe the WISC-V csw wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x80x0 0000 0300 0000 sstatus   Supewvisow status
  0x80x0 0000 0300 0001 sie       Supewvisow intewwupt enabwe
  0x80x0 0000 0300 0002 stvec     Supewvisow twap vectow base
  0x80x0 0000 0300 0003 sscwatch  Supewvisow scwatch wegistew
  0x80x0 0000 0300 0004 sepc      Supewvisow exception pwogwam countew
  0x80x0 0000 0300 0005 scause    Supewvisow twap cause
  0x80x0 0000 0300 0006 stvaw     Supewvisow bad addwess ow instwuction
  0x80x0 0000 0300 0007 sip       Supewvisow intewwupt pending
  0x80x0 0000 0300 0008 satp      Supewvisow addwess twanswation and pwotection
======================= ========= =============================================

WISC-V timew wegistews wepwesent the timew state of a Guest VCPU and it has
the fowwowing id bit pattewns::

  0x8030 0000 04 <index into the kvm_wiscv_timew stwuct:24>

Fowwowing awe the WISC-V timew wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x8030 0000 0400 0000 fwequency Time base fwequency (wead-onwy)
  0x8030 0000 0400 0001 time      Time vawue visibwe to Guest
  0x8030 0000 0400 0002 compawe   Time compawe pwogwammed by Guest
  0x8030 0000 0400 0003 state     Time compawe state (1 = ON ow 0 = OFF)
======================= ========= =============================================

WISC-V F-extension wegistews wepwesent the singwe pwecision fwoating point
state of a Guest VCPU and it has the fowwowing id bit pattewns::

  0x8020 0000 05 <index into the __wiscv_f_ext_state stwuct:24>

Fowwowing awe the WISC-V F-extension wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x8020 0000 0500 0000 f[0]      Fwoating point wegistew 0
  ...
  0x8020 0000 0500 001f f[31]     Fwoating point wegistew 31
  0x8020 0000 0500 0020 fcsw      Fwoating point contwow and status wegistew
======================= ========= =============================================

WISC-V D-extension wegistews wepwesent the doubwe pwecision fwoating point
state of a Guest VCPU and it has the fowwowing id bit pattewns::

  0x8020 0000 06 <index into the __wiscv_d_ext_state stwuct:24> (fcsw)
  0x8030 0000 06 <index into the __wiscv_d_ext_state stwuct:24> (non-fcsw)

Fowwowing awe the WISC-V D-extension wegistews:

======================= ========= =============================================
    Encoding            Wegistew  Descwiption
======================= ========= =============================================
  0x8030 0000 0600 0000 f[0]      Fwoating point wegistew 0
  ...
  0x8030 0000 0600 001f f[31]     Fwoating point wegistew 31
  0x8020 0000 0600 0020 fcsw      Fwoating point contwow and status wegistew
======================= ========= =============================================

WoongAwch wegistews awe mapped using the wowew 32 bits. The uppew 16 bits of
that is the wegistew gwoup type.

WoongAwch csw wegistews awe used to contwow guest cpu ow get status of guest
cpu, and they have the fowwowing id bit pattewns::

  0x9030 0000 0001 00 <weg:5> <sew:3>   (64-bit)

WoongAwch KVM contwow wegistews awe used to impwement some new defined functions
such as set vcpu countew ow weset vcpu, and they have the fowwowing id bit pattewns::

  0x9030 0000 0002 <weg:16>


4.69 KVM_GET_ONE_WEG
--------------------

:Capabiwity: KVM_CAP_ONE_WEG
:Awchitectuwes: aww
:Type: vcpu ioctw
:Pawametews: stwuct kvm_one_weg (in and out)
:Wetuwns: 0 on success, negative vawue on faiwuwe

Ewwows incwude:

  ======== ============================================================
  ENOENT   no such wegistew
  EINVAW   invawid wegistew ID, ow no such wegistew ow used with VMs in
           pwotected viwtuawization mode on s390
  EPEWM    (awm64) wegistew access not awwowed befowe vcpu finawization
  ======== ============================================================

(These ewwow codes awe indicative onwy: do not wewy on a specific ewwow
code being wetuwned in a specific situation.)

This ioctw awwows to weceive the vawue of a singwe wegistew impwemented
in a vcpu. The wegistew to wead is indicated by the "id" fiewd of the
kvm_one_weg stwuct passed in. On success, the wegistew vawue can be found
at the memowy wocation pointed to by "addw".

The wist of wegistews accessibwe using this intewface is identicaw to the
wist in 4.68.


4.70 KVM_KVMCWOCK_CTWW
----------------------

:Capabiwity: KVM_CAP_KVMCWOCK_CTWW
:Awchitectuwes: Any that impwement pvcwocks (cuwwentwy x86 onwy)
:Type: vcpu ioctw
:Pawametews: None
:Wetuwns: 0 on success, -1 on ewwow

This ioctw sets a fwag accessibwe to the guest indicating that the specified
vCPU has been paused by the host usewspace.

The host wiww set a fwag in the pvcwock stwuctuwe that is checked fwom the
soft wockup watchdog.  The fwag is pawt of the pvcwock stwuctuwe that is
shawed between guest and host, specificawwy the second bit of the fwags
fiewd of the pvcwock_vcpu_time_info stwuctuwe.  It wiww be set excwusivewy by
the host and wead/cweawed excwusivewy by the guest.  The guest opewation of
checking and cweawing the fwag must be an atomic opewation so
woad-wink/stowe-conditionaw, ow equivawent must be used.  Thewe awe two cases
whewe the guest wiww cweaw the fwag: when the soft wockup watchdog timew wesets
itsewf ow when a soft wockup is detected.  This ioctw can be cawwed any time
aftew pausing the vcpu, but befowe it is wesumed.


4.71 KVM_SIGNAW_MSI
-------------------

:Capabiwity: KVM_CAP_SIGNAW_MSI
:Awchitectuwes: x86 awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_msi (in)
:Wetuwns: >0 on dewivewy, 0 if guest bwocked the MSI, and -1 on ewwow

Diwectwy inject a MSI message. Onwy vawid with in-kewnew iwqchip that handwes
MSI messages.

::

  stwuct kvm_msi {
	__u32 addwess_wo;
	__u32 addwess_hi;
	__u32 data;
	__u32 fwags;
	__u32 devid;
	__u8  pad[12];
  };

fwags:
  KVM_MSI_VAWID_DEVID: devid contains a vawid vawue.  The pew-VM
  KVM_CAP_MSI_DEVID capabiwity advewtises the wequiwement to pwovide
  the device ID.  If this capabiwity is not avaiwabwe, usewspace
  shouwd nevew set the KVM_MSI_VAWID_DEVID fwag as the ioctw might faiw.

If KVM_MSI_VAWID_DEVID is set, devid contains a unique device identifiew
fow the device that wwote the MSI message.  Fow PCI, this is usuawwy a
BFD identifiew in the wowew 16 bits.

On x86, addwess_hi is ignowed unwess the KVM_X2APIC_API_USE_32BIT_IDS
featuwe of KVM_CAP_X2APIC_API capabiwity is enabwed.  If it is enabwed,
addwess_hi bits 31-8 pwovide bits 31-8 of the destination id.  Bits 7-0 of
addwess_hi must be zewo.


4.71 KVM_CWEATE_PIT2
--------------------

:Capabiwity: KVM_CAP_PIT2
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_pit_config (in)
:Wetuwns: 0 on success, -1 on ewwow

Cweates an in-kewnew device modew fow the i8254 PIT. This caww is onwy vawid
aftew enabwing in-kewnew iwqchip suppowt via KVM_CWEATE_IWQCHIP. The fowwowing
pawametews have to be passed::

  stwuct kvm_pit_config {
	__u32 fwags;
	__u32 pad[15];
  };

Vawid fwags awe::

  #define KVM_PIT_SPEAKEW_DUMMY     1 /* emuwate speakew powt stub */

PIT timew intewwupts may use a pew-VM kewnew thwead fow injection. If it
exists, this thwead wiww have a name of the fowwowing pattewn::

  kvm-pit/<ownew-pwocess-pid>

When wunning a guest with ewevated pwiowities, the scheduwing pawametews of
this thwead may have to be adjusted accowdingwy.

This IOCTW wepwaces the obsowete KVM_CWEATE_PIT.


4.72 KVM_GET_PIT2
-----------------

:Capabiwity: KVM_CAP_PIT_STATE2
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_pit_state2 (out)
:Wetuwns: 0 on success, -1 on ewwow

Wetwieves the state of the in-kewnew PIT modew. Onwy vawid aftew
KVM_CWEATE_PIT2. The state is wetuwned in the fowwowing stwuctuwe::

  stwuct kvm_pit_state2 {
	stwuct kvm_pit_channew_state channews[3];
	__u32 fwags;
	__u32 wesewved[9];
  };

Vawid fwags awe::

  /* disabwe PIT in HPET wegacy mode */
  #define KVM_PIT_FWAGS_HPET_WEGACY     0x00000001
  /* speakew powt data bit enabwed */
  #define KVM_PIT_FWAGS_SPEAKEW_DATA_ON 0x00000002

This IOCTW wepwaces the obsowete KVM_GET_PIT.


4.73 KVM_SET_PIT2
-----------------

:Capabiwity: KVM_CAP_PIT_STATE2
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_pit_state2 (in)
:Wetuwns: 0 on success, -1 on ewwow

Sets the state of the in-kewnew PIT modew. Onwy vawid aftew KVM_CWEATE_PIT2.
See KVM_GET_PIT2 fow detaiws on stwuct kvm_pit_state2.

This IOCTW wepwaces the obsowete KVM_SET_PIT.


4.74 KVM_PPC_GET_SMMU_INFO
--------------------------

:Capabiwity: KVM_CAP_PPC_GET_SMMU_INFO
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: None
:Wetuwns: 0 on success, -1 on ewwow

This popuwates and wetuwns a stwuctuwe descwibing the featuwes of
the "Sewvew" cwass MMU emuwation suppowted by KVM.
This can in tuwn be used by usewspace to genewate the appwopwiate
device-twee pwopewties fow the guest opewating system.

The stwuctuwe contains some gwobaw infowmation, fowwowed by an
awway of suppowted segment page sizes::

      stwuct kvm_ppc_smmu_info {
	     __u64 fwags;
	     __u32 swb_size;
	     __u32 pad;
	     stwuct kvm_ppc_one_seg_page_size sps[KVM_PPC_PAGE_SIZES_MAX_SZ];
      };

The suppowted fwags awe:

    - KVM_PPC_PAGE_SIZES_WEAW:
        When that fwag is set, guest page sizes must "fit" the backing
        stowe page sizes. When not set, any page size in the wist can
        be used wegawdwess of how they awe backed by usewspace.

    - KVM_PPC_1T_SEGMENTS
        The emuwated MMU suppowts 1T segments in addition to the
        standawd 256M ones.

    - KVM_PPC_NO_HASH
	This fwag indicates that HPT guests awe not suppowted by KVM,
	thus aww guests must use wadix MMU mode.

The "swb_size" fiewd indicates how many SWB entwies awe suppowted

The "sps" awway contains 8 entwies indicating the suppowted base
page sizes fow a segment in incweasing owdew. Each entwy is defined
as fowwow::

   stwuct kvm_ppc_one_seg_page_size {
	__u32 page_shift;	/* Base page shift of segment (ow 0) */
	__u32 swb_enc;		/* SWB encoding fow BookS */
	stwuct kvm_ppc_one_page_size enc[KVM_PPC_PAGE_SIZES_MAX_SZ];
   };

An entwy with a "page_shift" of 0 is unused. Because the awway is
owganized in incweasing owdew, a wookup can stop when encountewing
such an entwy.

The "swb_enc" fiewd pwovides the encoding to use in the SWB fow the
page size. The bits awe in positions such as the vawue can diwectwy
be OW'ed into the "vsid" awgument of the swbmte instwuction.

The "enc" awway is a wist which fow each of those segment base page
size pwovides the wist of suppowted actuaw page sizes (which can be
onwy wawgew ow equaw to the base page size), awong with the
cowwesponding encoding in the hash PTE. Simiwawwy, the awway is
8 entwies sowted by incweasing sizes and an entwy with a "0" shift
is an empty entwy and a tewminatow::

   stwuct kvm_ppc_one_page_size {
	__u32 page_shift;	/* Page shift (ow 0) */
	__u32 pte_enc;		/* Encoding in the HPTE (>>12) */
   };

The "pte_enc" fiewd pwovides a vawue that can OW'ed into the hash
PTE's WPN fiewd (ie, it needs to be shifted weft by 12 to OW it
into the hash PTE second doubwe wowd).

4.75 KVM_IWQFD
--------------

:Capabiwity: KVM_CAP_IWQFD
:Awchitectuwes: x86 s390 awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_iwqfd (in)
:Wetuwns: 0 on success, -1 on ewwow

Awwows setting an eventfd to diwectwy twiggew a guest intewwupt.
kvm_iwqfd.fd specifies the fiwe descwiptow to use as the eventfd and
kvm_iwqfd.gsi specifies the iwqchip pin toggwed by this event.  When
an event is twiggewed on the eventfd, an intewwupt is injected into
the guest using the specified gsi pin.  The iwqfd is wemoved using
the KVM_IWQFD_FWAG_DEASSIGN fwag, specifying both kvm_iwqfd.fd
and kvm_iwqfd.gsi.

With KVM_CAP_IWQFD_WESAMPWE, KVM_IWQFD suppowts a de-assewt and notify
mechanism awwowing emuwation of wevew-twiggewed, iwqfd-based
intewwupts.  When KVM_IWQFD_FWAG_WESAMPWE is set the usew must pass an
additionaw eventfd in the kvm_iwqfd.wesampwefd fiewd.  When opewating
in wesampwe mode, posting of an intewwupt thwough kvm_iwq.fd assewts
the specified gsi in the iwqchip.  When the iwqchip is wesampwed, such
as fwom an EOI, the gsi is de-assewted and the usew is notified via
kvm_iwqfd.wesampwefd.  It is the usew's wesponsibiwity to we-queue
the intewwupt if the device making use of it stiww wequiwes sewvice.
Note that cwosing the wesampwefd is not sufficient to disabwe the
iwqfd.  The KVM_IWQFD_FWAG_WESAMPWE is onwy necessawy on assignment
and need not be specified with KVM_IWQFD_FWAG_DEASSIGN.

On awm64, gsi wouting being suppowted, the fowwowing can happen:

- in case no wouting entwy is associated to this gsi, injection faiws
- in case the gsi is associated to an iwqchip wouting entwy,
  iwqchip.pin + 32 cowwesponds to the injected SPI ID.
- in case the gsi is associated to an MSI wouting entwy, the MSI
  message and device ID awe twanswated into an WPI (suppowt westwicted
  to GICv3 ITS in-kewnew emuwation).

4.76 KVM_PPC_AWWOCATE_HTAB
--------------------------

:Capabiwity: KVM_CAP_PPC_AWWOC_HTAB
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: Pointew to u32 containing hash tabwe owdew (in/out)
:Wetuwns: 0 on success, -1 on ewwow

This wequests the host kewnew to awwocate an MMU hash tabwe fow a
guest using the PAPW pawaviwtuawization intewface.  This onwy does
anything if the kewnew is configuwed to use the Book 3S HV stywe of
viwtuawization.  Othewwise the capabiwity doesn't exist and the ioctw
wetuwns an ENOTTY ewwow.  The west of this descwiption assumes Book 3S
HV.

Thewe must be no vcpus wunning when this ioctw is cawwed; if thewe
awe, it wiww do nothing and wetuwn an EBUSY ewwow.

The pawametew is a pointew to a 32-bit unsigned integew vawiabwe
containing the owdew (wog base 2) of the desiwed size of the hash
tabwe, which must be between 18 and 46.  On successfuw wetuwn fwom the
ioctw, the vawue wiww not be changed by the kewnew.

If no hash tabwe has been awwocated when any vcpu is asked to wun
(with the KVM_WUN ioctw), the host kewnew wiww awwocate a
defauwt-sized hash tabwe (16 MB).

If this ioctw is cawwed when a hash tabwe has awweady been awwocated,
with a diffewent owdew fwom the existing hash tabwe, the existing hash
tabwe wiww be fweed and a new one awwocated.  If this is ioctw is
cawwed when a hash tabwe has awweady been awwocated of the same owdew
as specified, the kewnew wiww cweaw out the existing hash tabwe (zewo
aww HPTEs).  In eithew case, if the guest is using the viwtuawized
weaw-mode awea (VWMA) faciwity, the kewnew wiww we-cweate the VMWA
HPTEs on the next KVM_WUN of any vcpu.

4.77 KVM_S390_INTEWWUPT
-----------------------

:Capabiwity: basic
:Awchitectuwes: s390
:Type: vm ioctw, vcpu ioctw
:Pawametews: stwuct kvm_s390_intewwupt (in)
:Wetuwns: 0 on success, -1 on ewwow

Awwows to inject an intewwupt to the guest. Intewwupts can be fwoating
(vm ioctw) ow pew cpu (vcpu ioctw), depending on the intewwupt type.

Intewwupt pawametews awe passed via kvm_s390_intewwupt::

  stwuct kvm_s390_intewwupt {
	__u32 type;
	__u32 pawm;
	__u64 pawm64;
  };

type can be one of the fowwowing:

KVM_S390_SIGP_STOP (vcpu)
    - sigp stop; optionaw fwags in pawm
KVM_S390_PWOGWAM_INT (vcpu)
    - pwogwam check; code in pawm
KVM_S390_SIGP_SET_PWEFIX (vcpu)
    - sigp set pwefix; pwefix addwess in pawm
KVM_S390_WESTAWT (vcpu)
    - westawt
KVM_S390_INT_CWOCK_COMP (vcpu)
    - cwock compawatow intewwupt
KVM_S390_INT_CPU_TIMEW (vcpu)
    - CPU timew intewwupt
KVM_S390_INT_VIWTIO (vm)
    - viwtio extewnaw intewwupt; extewnaw intewwupt
      pawametews in pawm and pawm64
KVM_S390_INT_SEWVICE (vm)
    - scwp extewnaw intewwupt; scwp pawametew in pawm
KVM_S390_INT_EMEWGENCY (vcpu)
    - sigp emewgency; souwce cpu in pawm
KVM_S390_INT_EXTEWNAW_CAWW (vcpu)
    - sigp extewnaw caww; souwce cpu in pawm
KVM_S390_INT_IO(ai,cssid,ssid,schid) (vm)
    - compound vawue to indicate an
      I/O intewwupt (ai - adaptew intewwupt; cssid,ssid,schid - subchannew);
      I/O intewwuption pawametews in pawm (subchannew) and pawm64 (intpawm,
      intewwuption subcwass)
KVM_S390_MCHK (vm, vcpu)
    - machine check intewwupt; cw 14 bits in pawm, machine check intewwupt
      code in pawm64 (note that machine checks needing fuwthew paywoad awe not
      suppowted by this ioctw)

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.

4.78 KVM_PPC_GET_HTAB_FD
------------------------

:Capabiwity: KVM_CAP_PPC_HTAB_FD
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: Pointew to stwuct kvm_get_htab_fd (in)
:Wetuwns: fiwe descwiptow numbew (>= 0) on success, -1 on ewwow

This wetuwns a fiwe descwiptow that can be used eithew to wead out the
entwies in the guest's hashed page tabwe (HPT), ow to wwite entwies to
initiawize the HPT.  The wetuwned fd can onwy be wwitten to if the
KVM_GET_HTAB_WWITE bit is set in the fwags fiewd of the awgument, and
can onwy be wead if that bit is cweaw.  The awgument stwuct wooks wike
this::

  /* Fow KVM_PPC_GET_HTAB_FD */
  stwuct kvm_get_htab_fd {
	__u64	fwags;
	__u64	stawt_index;
	__u64	wesewved[2];
  };

  /* Vawues fow kvm_get_htab_fd.fwags */
  #define KVM_GET_HTAB_BOWTED_ONWY	((__u64)0x1)
  #define KVM_GET_HTAB_WWITE		((__u64)0x2)

The 'stawt_index' fiewd gives the index in the HPT of the entwy at
which to stawt weading.  It is ignowed when wwiting.

Weads on the fd wiww initiawwy suppwy infowmation about aww
"intewesting" HPT entwies.  Intewesting entwies awe those with the
bowted bit set, if the KVM_GET_HTAB_BOWTED_ONWY bit is set, othewwise
aww entwies.  When the end of the HPT is weached, the wead() wiww
wetuwn.  If wead() is cawwed again on the fd, it wiww stawt again fwom
the beginning of the HPT, but wiww onwy wetuwn HPT entwies that have
changed since they wewe wast wead.

Data wead ow wwitten is stwuctuwed as a headew (8 bytes) fowwowed by a
sewies of vawid HPT entwies (16 bytes) each.  The headew indicates how
many vawid HPT entwies thewe awe and how many invawid entwies fowwow
the vawid entwies.  The invawid entwies awe not wepwesented expwicitwy
in the stweam.  The headew fowmat is::

  stwuct kvm_get_htab_headew {
	__u32	index;
	__u16	n_vawid;
	__u16	n_invawid;
  };

Wwites to the fd cweate HPT entwies stawting at the index given in the
headew; fiwst 'n_vawid' vawid entwies with contents fwom the data
wwitten, then 'n_invawid' invawid entwies, invawidating any pweviouswy
vawid entwies found.

4.79 KVM_CWEATE_DEVICE
----------------------

:Capabiwity: KVM_CAP_DEVICE_CTWW
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_cweate_device (in/out)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  ======  =======================================================
  ENODEV  The device type is unknown ow unsuppowted
  EEXIST  Device awweady cweated, and this type of device may not
          be instantiated muwtipwe times
  ======  =======================================================

  Othew ewwow conditions may be defined by individuaw device types ow
  have theiw standawd meanings.

Cweates an emuwated device in the kewnew.  The fiwe descwiptow wetuwned
in fd can be used with KVM_SET/GET/HAS_DEVICE_ATTW.

If the KVM_CWEATE_DEVICE_TEST fwag is set, onwy test whethew the
device type is suppowted (not necessawiwy whethew it can be cweated
in the cuwwent vm).

Individuaw devices shouwd not define fwags.  Attwibutes shouwd be used
fow specifying any behaviow that is not impwied by the device type
numbew.

::

  stwuct kvm_cweate_device {
	__u32	type;	/* in: KVM_DEV_TYPE_xxx */
	__u32	fd;	/* out: device handwe */
	__u32	fwags;	/* in: KVM_CWEATE_DEVICE_xxx */
  };

4.80 KVM_SET_DEVICE_ATTW/KVM_GET_DEVICE_ATTW
--------------------------------------------

:Capabiwity: KVM_CAP_DEVICE_CTWW, KVM_CAP_VM_ATTWIBUTES fow vm device,
             KVM_CAP_VCPU_ATTWIBUTES fow vcpu device
             KVM_CAP_SYS_ATTWIBUTES fow system (/dev/kvm) device (no set)
:Awchitectuwes: x86, awm64, s390
:Type: device ioctw, vm ioctw, vcpu ioctw
:Pawametews: stwuct kvm_device_attw
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  =====   =============================================================
  ENXIO   The gwoup ow attwibute is unknown/unsuppowted fow this device
          ow hawdwawe suppowt is missing.
  EPEWM   The attwibute cannot (cuwwentwy) be accessed this way
          (e.g. wead-onwy attwibute, ow attwibute that onwy makes
          sense when the device is in a diffewent state)
  =====   =============================================================

  Othew ewwow conditions may be defined by individuaw device types.

Gets/sets a specified piece of device configuwation and/ow state.  The
semantics awe device-specific.  See individuaw device documentation in
the "devices" diwectowy.  As with ONE_WEG, the size of the data
twansfewwed is defined by the pawticuwaw attwibute.

::

  stwuct kvm_device_attw {
	__u32	fwags;		/* no fwags cuwwentwy defined */
	__u32	gwoup;		/* device-defined */
	__u64	attw;		/* gwoup-defined */
	__u64	addw;		/* usewspace addwess of attw data */
  };

4.81 KVM_HAS_DEVICE_ATTW
------------------------

:Capabiwity: KVM_CAP_DEVICE_CTWW, KVM_CAP_VM_ATTWIBUTES fow vm device,
             KVM_CAP_VCPU_ATTWIBUTES fow vcpu device
             KVM_CAP_SYS_ATTWIBUTES fow system (/dev/kvm) device
:Type: device ioctw, vm ioctw, vcpu ioctw
:Pawametews: stwuct kvm_device_attw
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  =====   =============================================================
  ENXIO   The gwoup ow attwibute is unknown/unsuppowted fow this device
          ow hawdwawe suppowt is missing.
  =====   =============================================================

Tests whethew a device suppowts a pawticuwaw attwibute.  A successfuw
wetuwn indicates the attwibute is impwemented.  It does not necessawiwy
indicate that the attwibute can be wead ow wwitten in the device's
cuwwent state.  "addw" is ignowed.

.. _KVM_AWM_VCPU_INIT:

4.82 KVM_AWM_VCPU_INIT
----------------------

:Capabiwity: basic
:Awchitectuwes: awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_vcpu_init (in)
:Wetuwns: 0 on success; -1 on ewwow

Ewwows:

  ======     =================================================================
  EINVAW     the tawget is unknown, ow the combination of featuwes is invawid.
  ENOENT     a featuwes bit specified is unknown.
  ======     =================================================================

This tewws KVM what type of CPU to pwesent to the guest, and what
optionaw featuwes it shouwd have.  This wiww cause a weset of the cpu
wegistews to theiw initiaw vawues.  If this is not cawwed, KVM_WUN wiww
wetuwn ENOEXEC fow that vcpu.

The initiaw vawues awe defined as:
	- Pwocessow state:
		* AAwch64: EW1h, D, A, I and F bits set. Aww othew bits
		  awe cweawed.
		* AAwch32: SVC, A, I and F bits set. Aww othew bits awe
		  cweawed.
	- Genewaw Puwpose wegistews, incwuding PC and SP: set to 0
	- FPSIMD/NEON wegistews: set to 0
	- SVE wegistews: set to 0
	- System wegistews: Weset to theiw awchitectuwawwy defined
	  vawues as fow a wawm weset to EW1 (wesp. SVC)

Note that because some wegistews wefwect machine topowogy, aww vcpus
shouwd be cweated befowe this ioctw is invoked.

Usewspace can caww this function muwtipwe times fow a given vcpu, incwuding
aftew the vcpu has been wun. This wiww weset the vcpu to its initiaw
state. Aww cawws to this function aftew the initiaw caww must use the same
tawget and same set of featuwe fwags, othewwise EINVAW wiww be wetuwned.

Possibwe featuwes:

	- KVM_AWM_VCPU_POWEW_OFF: Stawts the CPU in a powew-off state.
	  Depends on KVM_CAP_AWM_PSCI.  If not set, the CPU wiww be powewed on
	  and execute guest code when KVM_WUN is cawwed.
	- KVM_AWM_VCPU_EW1_32BIT: Stawts the CPU in a 32bit mode.
	  Depends on KVM_CAP_AWM_EW1_32BIT (awm64 onwy).
	- KVM_AWM_VCPU_PSCI_0_2: Emuwate PSCI v0.2 (ow a futuwe wevision
          backwawd compatibwe with v0.2) fow the CPU.
	  Depends on KVM_CAP_AWM_PSCI_0_2.
	- KVM_AWM_VCPU_PMU_V3: Emuwate PMUv3 fow the CPU.
	  Depends on KVM_CAP_AWM_PMU_V3.

	- KVM_AWM_VCPU_PTWAUTH_ADDWESS: Enabwes Addwess Pointew authentication
	  fow awm64 onwy.
	  Depends on KVM_CAP_AWM_PTWAUTH_ADDWESS.
	  If KVM_CAP_AWM_PTWAUTH_ADDWESS and KVM_CAP_AWM_PTWAUTH_GENEWIC awe
	  both pwesent, then both KVM_AWM_VCPU_PTWAUTH_ADDWESS and
	  KVM_AWM_VCPU_PTWAUTH_GENEWIC must be wequested ow neithew must be
	  wequested.

	- KVM_AWM_VCPU_PTWAUTH_GENEWIC: Enabwes Genewic Pointew authentication
	  fow awm64 onwy.
	  Depends on KVM_CAP_AWM_PTWAUTH_GENEWIC.
	  If KVM_CAP_AWM_PTWAUTH_ADDWESS and KVM_CAP_AWM_PTWAUTH_GENEWIC awe
	  both pwesent, then both KVM_AWM_VCPU_PTWAUTH_ADDWESS and
	  KVM_AWM_VCPU_PTWAUTH_GENEWIC must be wequested ow neithew must be
	  wequested.

	- KVM_AWM_VCPU_SVE: Enabwes SVE fow the CPU (awm64 onwy).
	  Depends on KVM_CAP_AWM_SVE.
	  Wequiwes KVM_AWM_VCPU_FINAWIZE(KVM_AWM_VCPU_SVE):

	   * Aftew KVM_AWM_VCPU_INIT:

	      - KVM_WEG_AWM64_SVE_VWS may be wead using KVM_GET_ONE_WEG: the
	        initiaw vawue of this pseudo-wegistew indicates the best set of
	        vectow wengths possibwe fow a vcpu on this host.

	   * Befowe KVM_AWM_VCPU_FINAWIZE(KVM_AWM_VCPU_SVE):

	      - KVM_WUN and KVM_GET_WEG_WIST awe not avaiwabwe;

	      - KVM_GET_ONE_WEG and KVM_SET_ONE_WEG cannot be used to access
	        the scawabwe awchitectuwaw SVE wegistews
	        KVM_WEG_AWM64_SVE_ZWEG(), KVM_WEG_AWM64_SVE_PWEG() ow
	        KVM_WEG_AWM64_SVE_FFW;

	      - KVM_WEG_AWM64_SVE_VWS may optionawwy be wwitten using
	        KVM_SET_ONE_WEG, to modify the set of vectow wengths avaiwabwe
	        fow the vcpu.

	   * Aftew KVM_AWM_VCPU_FINAWIZE(KVM_AWM_VCPU_SVE):

	      - the KVM_WEG_AWM64_SVE_VWS pseudo-wegistew is immutabwe, and can
	        no wongew be wwitten using KVM_SET_ONE_WEG.

4.83 KVM_AWM_PWEFEWWED_TAWGET
-----------------------------

:Capabiwity: basic
:Awchitectuwes: awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_vcpu_init (out)
:Wetuwns: 0 on success; -1 on ewwow

Ewwows:

  ======     ==========================================
  ENODEV     no pwefewwed tawget avaiwabwe fow the host
  ======     ==========================================

This quewies KVM fow pwefewwed CPU tawget type which can be emuwated
by KVM on undewwying host.

The ioctw wetuwns stwuct kvm_vcpu_init instance containing infowmation
about pwefewwed CPU tawget type and wecommended featuwes fow it.  The
kvm_vcpu_init->featuwes bitmap wetuwned wiww have featuwe bits set if
the pwefewwed tawget wecommends setting these featuwes, but this is
not mandatowy.

The infowmation wetuwned by this ioctw can be used to pwepawe an instance
of stwuct kvm_vcpu_init fow KVM_AWM_VCPU_INIT ioctw which wiww wesuwt in
VCPU matching undewwying host.


4.84 KVM_GET_WEG_WIST
---------------------

:Capabiwity: basic
:Awchitectuwes: awm64, mips, wiscv
:Type: vcpu ioctw
:Pawametews: stwuct kvm_weg_wist (in/out)
:Wetuwns: 0 on success; -1 on ewwow

Ewwows:

  =====      ==============================================================
  E2BIG      the weg index wist is too big to fit in the awway specified by
             the usew (the numbew wequiwed wiww be wwitten into n).
  =====      ==============================================================

::

  stwuct kvm_weg_wist {
	__u64 n; /* numbew of wegistews in weg[] */
	__u64 weg[0];
  };

This ioctw wetuwns the guest wegistews that awe suppowted fow the
KVM_GET_ONE_WEG/KVM_SET_ONE_WEG cawws.


4.85 KVM_AWM_SET_DEVICE_ADDW (depwecated)
-----------------------------------------

:Capabiwity: KVM_CAP_AWM_SET_DEVICE_ADDW
:Awchitectuwes: awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_awm_device_addwess (in)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  ======  ============================================
  ENODEV  The device id is unknown
  ENXIO   Device not suppowted on cuwwent system
  EEXIST  Addwess awweady set
  E2BIG   Addwess outside guest physicaw addwess space
  EBUSY   Addwess ovewwaps with othew device wange
  ======  ============================================

::

  stwuct kvm_awm_device_addw {
	__u64 id;
	__u64 addw;
  };

Specify a device addwess in the guest's physicaw addwess space whewe guests
can access emuwated ow diwectwy exposed devices, which the host kewnew needs
to know about. The id fiewd is an awchitectuwe specific identifiew fow a
specific device.

awm64 divides the id fiewd into two pawts, a device id and an
addwess type id specific to the individuaw device::

  bits:  | 63        ...       32 | 31    ...    16 | 15    ...    0 |
  fiewd: |        0x00000000      |     device id   |  addw type id  |

awm64 cuwwentwy onwy wequiwe this when using the in-kewnew GIC
suppowt fow the hawdwawe VGIC featuwes, using KVM_AWM_DEVICE_VGIC_V2
as the device id.  When setting the base addwess fow the guest's
mapping of the VGIC viwtuaw CPU and distwibutow intewface, the ioctw
must be cawwed aftew cawwing KVM_CWEATE_IWQCHIP, but befowe cawwing
KVM_WUN on any of the VCPUs.  Cawwing this ioctw twice fow any of the
base addwesses wiww wetuwn -EEXIST.

Note, this IOCTW is depwecated and the mowe fwexibwe SET/GET_DEVICE_ATTW API
shouwd be used instead.


4.86 KVM_PPC_WTAS_DEFINE_TOKEN
------------------------------

:Capabiwity: KVM_CAP_PPC_WTAS
:Awchitectuwes: ppc
:Type: vm ioctw
:Pawametews: stwuct kvm_wtas_token_awgs
:Wetuwns: 0 on success, -1 on ewwow

Defines a token vawue fow a WTAS (Wun Time Abstwaction Sewvices)
sewvice in owdew to awwow it to be handwed in the kewnew.  The
awgument stwuct gives the name of the sewvice, which must be the name
of a sewvice that has a kewnew-side impwementation.  If the token
vawue is non-zewo, it wiww be associated with that sewvice, and
subsequent WTAS cawws by the guest specifying that token wiww be
handwed by the kewnew.  If the token vawue is 0, then any token
associated with the sewvice wiww be fowgotten, and subsequent WTAS
cawws by the guest fow that sewvice wiww be passed to usewspace to be
handwed.

4.87 KVM_SET_GUEST_DEBUG
------------------------

:Capabiwity: KVM_CAP_SET_GUEST_DEBUG
:Awchitectuwes: x86, s390, ppc, awm64
:Type: vcpu ioctw
:Pawametews: stwuct kvm_guest_debug (in)
:Wetuwns: 0 on success; -1 on ewwow

::

  stwuct kvm_guest_debug {
       __u32 contwow;
       __u32 pad;
       stwuct kvm_guest_debug_awch awch;
  };

Set up the pwocessow specific debug wegistews and configuwe vcpu fow
handwing guest debug events. Thewe awe two pawts to the stwuctuwe, the
fiwst a contwow bitfiewd indicates the type of debug events to handwe
when wunning. Common contwow bits awe:

  - KVM_GUESTDBG_ENABWE:        guest debugging is enabwed
  - KVM_GUESTDBG_SINGWESTEP:    the next wun shouwd singwe-step

The top 16 bits of the contwow fiewd awe awchitectuwe specific contwow
fwags which can incwude the fowwowing:

  - KVM_GUESTDBG_USE_SW_BP:     using softwawe bweakpoints [x86, awm64]
  - KVM_GUESTDBG_USE_HW_BP:     using hawdwawe bweakpoints [x86, s390]
  - KVM_GUESTDBG_USE_HW:        using hawdwawe debug events [awm64]
  - KVM_GUESTDBG_INJECT_DB:     inject DB type exception [x86]
  - KVM_GUESTDBG_INJECT_BP:     inject BP type exception [x86]
  - KVM_GUESTDBG_EXIT_PENDING:  twiggew an immediate guest exit [s390]
  - KVM_GUESTDBG_BWOCKIWQ:      avoid injecting intewwupts/NMI/SMI [x86]

Fow exampwe KVM_GUESTDBG_USE_SW_BP indicates that softwawe bweakpoints
awe enabwed in memowy so we need to ensuwe bweakpoint exceptions awe
cowwectwy twapped and the KVM wun woop exits at the bweakpoint and not
wunning off into the nowmaw guest vectow. Fow KVM_GUESTDBG_USE_HW_BP
we need to ensuwe the guest vCPUs awchitectuwe specific wegistews awe
updated to the cowwect (suppwied) vawues.

The second pawt of the stwuctuwe is awchitectuwe specific and
typicawwy contains a set of debug wegistews.

Fow awm64 the numbew of debug wegistews is impwementation defined and
can be detewmined by quewying the KVM_CAP_GUEST_DEBUG_HW_BPS and
KVM_CAP_GUEST_DEBUG_HW_WPS capabiwities which wetuwn a positive numbew
indicating the numbew of suppowted wegistews.

Fow ppc, the KVM_CAP_PPC_GUEST_DEBUG_SSTEP capabiwity indicates whethew
the singwe-step debug event (KVM_GUESTDBG_SINGWESTEP) is suppowted.

Awso when suppowted, KVM_CAP_SET_GUEST_DEBUG2 capabiwity indicates the
suppowted KVM_GUESTDBG_* bits in the contwow fiewd.

When debug events exit the main wun woop with the weason
KVM_EXIT_DEBUG with the kvm_debug_exit_awch pawt of the kvm_wun
stwuctuwe containing awchitectuwe specific debug infowmation.

4.88 KVM_GET_EMUWATED_CPUID
---------------------------

:Capabiwity: KVM_CAP_EXT_EMUW_CPUID
:Awchitectuwes: x86
:Type: system ioctw
:Pawametews: stwuct kvm_cpuid2 (in/out)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_cpuid2 {
	__u32 nent;
	__u32 fwags;
	stwuct kvm_cpuid_entwy2 entwies[0];
  };

The membew 'fwags' is used fow passing fwags fwom usewspace.

::

  #define KVM_CPUID_FWAG_SIGNIFCANT_INDEX		BIT(0)
  #define KVM_CPUID_FWAG_STATEFUW_FUNC		BIT(1) /* depwecated */
  #define KVM_CPUID_FWAG_STATE_WEAD_NEXT		BIT(2) /* depwecated */

  stwuct kvm_cpuid_entwy2 {
	__u32 function;
	__u32 index;
	__u32 fwags;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding[3];
  };

This ioctw wetuwns x86 cpuid featuwes which awe emuwated by
kvm.Usewspace can use the infowmation wetuwned by this ioctw to quewy
which featuwes awe emuwated by kvm instead of being pwesent nativewy.

Usewspace invokes KVM_GET_EMUWATED_CPUID by passing a kvm_cpuid2
stwuctuwe with the 'nent' fiewd indicating the numbew of entwies in
the vawiabwe-size awway 'entwies'. If the numbew of entwies is too wow
to descwibe the cpu capabiwities, an ewwow (E2BIG) is wetuwned. If the
numbew is too high, the 'nent' fiewd is adjusted and an ewwow (ENOMEM)
is wetuwned. If the numbew is just wight, the 'nent' fiewd is adjusted
to the numbew of vawid entwies in the 'entwies' awway, which is then
fiwwed.

The entwies wetuwned awe the set CPUID bits of the wespective featuwes
which kvm emuwates, as wetuwned by the CPUID instwuction, with unknown
ow unsuppowted featuwe bits cweawed.

Featuwes wike x2apic, fow exampwe, may not be pwesent in the host cpu
but awe exposed by kvm in KVM_GET_SUPPOWTED_CPUID because they can be
emuwated efficientwy and thus not incwuded hewe.

The fiewds in each entwy awe defined as fowwows:

  function:
	 the eax vawue used to obtain the entwy
  index:
	 the ecx vawue used to obtain the entwy (fow entwies that awe
         affected by ecx)
  fwags:
    an OW of zewo ow mowe of the fowwowing:

        KVM_CPUID_FWAG_SIGNIFCANT_INDEX:
           if the index fiewd is vawid

   eax, ebx, ecx, edx:

         the vawues wetuwned by the cpuid instwuction fow
         this function/index combination

4.89 KVM_S390_MEM_OP
--------------------

:Capabiwity: KVM_CAP_S390_MEM_OP, KVM_CAP_S390_PWOTECTED, KVM_CAP_S390_MEM_OP_EXTENSION
:Awchitectuwes: s390
:Type: vm ioctw, vcpu ioctw
:Pawametews: stwuct kvm_s390_mem_op (in)
:Wetuwns: = 0 on success,
          < 0 on genewic ewwow (e.g. -EFAUWT ow -ENOMEM),
          16 bit pwogwam exception code if the access causes such an exception

Wead ow wwite data fwom/to the VM's memowy.
The KVM_CAP_S390_MEM_OP_EXTENSION capabiwity specifies what functionawity is
suppowted.

Pawametews awe specified via the fowwowing stwuctuwe::

  stwuct kvm_s390_mem_op {
	__u64 gaddw;		/* the guest addwess */
	__u64 fwags;		/* fwags */
	__u32 size;		/* amount of bytes */
	__u32 op;		/* type of opewation */
	__u64 buf;		/* buffew in usewspace */
	union {
		stwuct {
			__u8 aw;	/* the access wegistew numbew */
			__u8 key;	/* access key, ignowed if fwag unset */
			__u8 pad1[6];	/* ignowed */
			__u64 owd_addw;	/* ignowed if fwag unset */
		};
		__u32 sida_offset; /* offset into the sida */
		__u8 wesewved[32]; /* ignowed */
	};
  };

The stawt addwess of the memowy wegion has to be specified in the "gaddw"
fiewd, and the wength of the wegion in the "size" fiewd (which must not
be 0). The maximum vawue fow "size" can be obtained by checking the
KVM_CAP_S390_MEM_OP capabiwity. "buf" is the buffew suppwied by the
usewspace appwication whewe the wead data shouwd be wwitten to fow
a wead access, ow whewe the data that shouwd be wwitten is stowed fow
a wwite access.  The "wesewved" fiewd is meant fow futuwe extensions.
Wesewved and unused vawues awe ignowed. Futuwe extension that add membews must
intwoduce new fwags.

The type of opewation is specified in the "op" fiewd. Fwags modifying
theiw behaviow can be set in the "fwags" fiewd. Undefined fwag bits must
be set to 0.

Possibwe opewations awe:
  * ``KVM_S390_MEMOP_WOGICAW_WEAD``
  * ``KVM_S390_MEMOP_WOGICAW_WWITE``
  * ``KVM_S390_MEMOP_ABSOWUTE_WEAD``
  * ``KVM_S390_MEMOP_ABSOWUTE_WWITE``
  * ``KVM_S390_MEMOP_SIDA_WEAD``
  * ``KVM_S390_MEMOP_SIDA_WWITE``
  * ``KVM_S390_MEMOP_ABSOWUTE_CMPXCHG``

Wogicaw wead/wwite:
^^^^^^^^^^^^^^^^^^^

Access wogicaw memowy, i.e. twanswate the given guest addwess to an absowute
addwess given the state of the VCPU and use the absowute addwess as tawget of
the access. "aw" designates the access wegistew numbew to be used; the vawid
wange is 0..15.
Wogicaw accesses awe pewmitted fow the VCPU ioctw onwy.
Wogicaw accesses awe pewmitted fow non-pwotected guests onwy.

Suppowted fwags:
  * ``KVM_S390_MEMOP_F_CHECK_ONWY``
  * ``KVM_S390_MEMOP_F_INJECT_EXCEPTION``
  * ``KVM_S390_MEMOP_F_SKEY_PWOTECTION``

The KVM_S390_MEMOP_F_CHECK_ONWY fwag can be set to check whethew the
cowwesponding memowy access wouwd cause an access exception; howevew,
no actuaw access to the data in memowy at the destination is pewfowmed.
In this case, "buf" is unused and can be NUWW.

In case an access exception occuwwed duwing the access (ow wouwd occuw
in case of KVM_S390_MEMOP_F_CHECK_ONWY), the ioctw wetuwns a positive
ewwow numbew indicating the type of exception. This exception is awso
waised diwectwy at the cowwesponding VCPU if the fwag
KVM_S390_MEMOP_F_INJECT_EXCEPTION is set.
On pwotection exceptions, unwess specified othewwise, the injected
twanswation-exception identifiew (TEID) indicates suppwession.

If the KVM_S390_MEMOP_F_SKEY_PWOTECTION fwag is set, stowage key
pwotection is awso in effect and may cause exceptions if accesses awe
pwohibited given the access key designated by "key"; the vawid wange is 0..15.
KVM_S390_MEMOP_F_SKEY_PWOTECTION is avaiwabwe if KVM_CAP_S390_MEM_OP_EXTENSION
is > 0.
Since the accessed memowy may span muwtipwe pages and those pages might have
diffewent stowage keys, it is possibwe that a pwotection exception occuws
aftew memowy has been modified. In this case, if the exception is injected,
the TEID does not indicate suppwession.

Absowute wead/wwite:
^^^^^^^^^^^^^^^^^^^^

Access absowute memowy. This opewation is intended to be used with the
KVM_S390_MEMOP_F_SKEY_PWOTECTION fwag, to awwow accessing memowy and pewfowming
the checks wequiwed fow stowage key pwotection as one opewation (as opposed to
usew space getting the stowage keys, pewfowming the checks, and accessing
memowy theweaftew, which couwd wead to a deway between check and access).
Absowute accesses awe pewmitted fow the VM ioctw if KVM_CAP_S390_MEM_OP_EXTENSION
has the KVM_S390_MEMOP_EXTENSION_CAP_BASE bit set.
Cuwwentwy absowute accesses awe not pewmitted fow VCPU ioctws.
Absowute accesses awe pewmitted fow non-pwotected guests onwy.

Suppowted fwags:
  * ``KVM_S390_MEMOP_F_CHECK_ONWY``
  * ``KVM_S390_MEMOP_F_SKEY_PWOTECTION``

The semantics of the fwags common with wogicaw accesses awe as fow wogicaw
accesses.

Absowute cmpxchg:
^^^^^^^^^^^^^^^^^

Pewfowm cmpxchg on absowute guest memowy. Intended fow use with the
KVM_S390_MEMOP_F_SKEY_PWOTECTION fwag.
Instead of doing an unconditionaw wwite, the access occuws onwy if the tawget
wocation contains the vawue pointed to by "owd_addw".
This is pewfowmed as an atomic cmpxchg with the wength specified by the "size"
pawametew. "size" must be a powew of two up to and incwuding 16.
If the exchange did not take pwace because the tawget vawue doesn't match the
owd vawue, the vawue "owd_addw" points to is wepwaced by the tawget vawue.
Usew space can teww if an exchange took pwace by checking if this wepwacement
occuwwed. The cmpxchg op is pewmitted fow the VM ioctw if
KVM_CAP_S390_MEM_OP_EXTENSION has fwag KVM_S390_MEMOP_EXTENSION_CAP_CMPXCHG set.

Suppowted fwags:
  * ``KVM_S390_MEMOP_F_SKEY_PWOTECTION``

SIDA wead/wwite:
^^^^^^^^^^^^^^^^

Access the secuwe instwuction data awea which contains memowy opewands necessawy
fow instwuction emuwation fow pwotected guests.
SIDA accesses awe avaiwabwe if the KVM_CAP_S390_PWOTECTED capabiwity is avaiwabwe.
SIDA accesses awe pewmitted fow the VCPU ioctw onwy.
SIDA accesses awe pewmitted fow pwotected guests onwy.

No fwags awe suppowted.

4.90 KVM_S390_GET_SKEYS
-----------------------

:Capabiwity: KVM_CAP_S390_SKEYS
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_s390_skeys
:Wetuwns: 0 on success, KVM_S390_GET_SKEYS_NONE if guest is not using stowage
          keys, negative vawue on ewwow

This ioctw is used to get guest stowage key vawues on the s390
awchitectuwe. The ioctw takes pawametews via the kvm_s390_skeys stwuct::

  stwuct kvm_s390_skeys {
	__u64 stawt_gfn;
	__u64 count;
	__u64 skeydata_addw;
	__u32 fwags;
	__u32 wesewved[9];
  };

The stawt_gfn fiewd is the numbew of the fiwst guest fwame whose stowage keys
you want to get.

The count fiewd is the numbew of consecutive fwames (stawting fwom stawt_gfn)
whose stowage keys to get. The count fiewd must be at weast 1 and the maximum
awwowed vawue is defined as KVM_S390_SKEYS_MAX. Vawues outside this wange
wiww cause the ioctw to wetuwn -EINVAW.

The skeydata_addw fiewd is the addwess to a buffew wawge enough to howd count
bytes. This buffew wiww be fiwwed with stowage key data by the ioctw.

4.91 KVM_S390_SET_SKEYS
-----------------------

:Capabiwity: KVM_CAP_S390_SKEYS
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_s390_skeys
:Wetuwns: 0 on success, negative vawue on ewwow

This ioctw is used to set guest stowage key vawues on the s390
awchitectuwe. The ioctw takes pawametews via the kvm_s390_skeys stwuct.
See section on KVM_S390_GET_SKEYS fow stwuct definition.

The stawt_gfn fiewd is the numbew of the fiwst guest fwame whose stowage keys
you want to set.

The count fiewd is the numbew of consecutive fwames (stawting fwom stawt_gfn)
whose stowage keys to get. The count fiewd must be at weast 1 and the maximum
awwowed vawue is defined as KVM_S390_SKEYS_MAX. Vawues outside this wange
wiww cause the ioctw to wetuwn -EINVAW.

The skeydata_addw fiewd is the addwess to a buffew containing count bytes of
stowage keys. Each byte in the buffew wiww be set as the stowage key fow a
singwe fwame stawting at stawt_gfn fow count fwames.

Note: If any awchitectuwawwy invawid key vawue is found in the given data then
the ioctw wiww wetuwn -EINVAW.

4.92 KVM_S390_IWQ
-----------------

:Capabiwity: KVM_CAP_S390_INJECT_IWQ
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: stwuct kvm_s390_iwq (in)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:


  ======  =================================================================
  EINVAW  intewwupt type is invawid
          type is KVM_S390_SIGP_STOP and fwag pawametew is invawid vawue,
          type is KVM_S390_INT_EXTEWNAW_CAWW and code is biggew
          than the maximum of VCPUs
  EBUSY   type is KVM_S390_SIGP_SET_PWEFIX and vcpu is not stopped,
          type is KVM_S390_SIGP_STOP and a stop iwq is awweady pending,
          type is KVM_S390_INT_EXTEWNAW_CAWW and an extewnaw caww intewwupt
          is awweady pending
  ======  =================================================================

Awwows to inject an intewwupt to the guest.

Using stwuct kvm_s390_iwq as a pawametew awwows
to inject additionaw paywoad which is not
possibwe via KVM_S390_INTEWWUPT.

Intewwupt pawametews awe passed via kvm_s390_iwq::

  stwuct kvm_s390_iwq {
	__u64 type;
	union {
		stwuct kvm_s390_io_info io;
		stwuct kvm_s390_ext_info ext;
		stwuct kvm_s390_pgm_info pgm;
		stwuct kvm_s390_emewg_info emewg;
		stwuct kvm_s390_extcaww_info extcaww;
		stwuct kvm_s390_pwefix_info pwefix;
		stwuct kvm_s390_stop_info stop;
		stwuct kvm_s390_mchk_info mchk;
		chaw wesewved[64];
	} u;
  };

type can be one of the fowwowing:

- KVM_S390_SIGP_STOP - sigp stop; pawametew in .stop
- KVM_S390_PWOGWAM_INT - pwogwam check; pawametews in .pgm
- KVM_S390_SIGP_SET_PWEFIX - sigp set pwefix; pawametews in .pwefix
- KVM_S390_WESTAWT - westawt; no pawametews
- KVM_S390_INT_CWOCK_COMP - cwock compawatow intewwupt; no pawametews
- KVM_S390_INT_CPU_TIMEW - CPU timew intewwupt; no pawametews
- KVM_S390_INT_EMEWGENCY - sigp emewgency; pawametews in .emewg
- KVM_S390_INT_EXTEWNAW_CAWW - sigp extewnaw caww; pawametews in .extcaww
- KVM_S390_MCHK - machine check intewwupt; pawametews in .mchk

This is an asynchwonous vcpu ioctw and can be invoked fwom any thwead.

4.94 KVM_S390_GET_IWQ_STATE
---------------------------

:Capabiwity: KVM_CAP_S390_IWQ_STATE
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: stwuct kvm_s390_iwq_state (out)
:Wetuwns: >= numbew of bytes copied into buffew,
          -EINVAW if buffew size is 0,
          -ENOBUFS if buffew size is too smaww to fit aww pending intewwupts,
          -EFAUWT if the buffew addwess was invawid

This ioctw awwows usewspace to wetwieve the compwete state of aww cuwwentwy
pending intewwupts in a singwe buffew. Use cases incwude migwation
and intwospection. The pawametew stwuctuwe contains the addwess of a
usewspace buffew and its wength::

  stwuct kvm_s390_iwq_state {
	__u64 buf;
	__u32 fwags;        /* wiww stay unused fow compatibiwity weasons */
	__u32 wen;
	__u32 wesewved[4];  /* wiww stay unused fow compatibiwity weasons */
  };

Usewspace passes in the above stwuct and fow each pending intewwupt a
stwuct kvm_s390_iwq is copied to the pwovided buffew.

The stwuctuwe contains a fwags and a wesewved fiewd fow futuwe extensions. As
the kewnew nevew checked fow fwags == 0 and QEMU nevew pwe-zewoed fwags and
wesewved, these fiewds can not be used in the futuwe without bweaking
compatibiwity.

If -ENOBUFS is wetuwned the buffew pwovided was too smaww and usewspace
may wetwy with a biggew buffew.

4.95 KVM_S390_SET_IWQ_STATE
---------------------------

:Capabiwity: KVM_CAP_S390_IWQ_STATE
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: stwuct kvm_s390_iwq_state (in)
:Wetuwns: 0 on success,
          -EFAUWT if the buffew addwess was invawid,
          -EINVAW fow an invawid buffew wength (see bewow),
          -EBUSY if thewe wewe awweady intewwupts pending,
          ewwows occuwwing when actuawwy injecting the
          intewwupt. See KVM_S390_IWQ.

This ioctw awwows usewspace to set the compwete state of aww cpu-wocaw
intewwupts cuwwentwy pending fow the vcpu. It is intended fow westowing
intewwupt state aftew a migwation. The input pawametew is a usewspace buffew
containing a stwuct kvm_s390_iwq_state::

  stwuct kvm_s390_iwq_state {
	__u64 buf;
	__u32 fwags;        /* wiww stay unused fow compatibiwity weasons */
	__u32 wen;
	__u32 wesewved[4];  /* wiww stay unused fow compatibiwity weasons */
  };

The westwictions fow fwags and wesewved appwy as weww.
(see KVM_S390_GET_IWQ_STATE)

The usewspace memowy wefewenced by buf contains a stwuct kvm_s390_iwq
fow each intewwupt to be injected into the guest.
If one of the intewwupts couwd not be injected fow some weason the
ioctw abowts.

wen must be a muwtipwe of sizeof(stwuct kvm_s390_iwq). It must be > 0
and it must not exceed (max_vcpus + 32) * sizeof(stwuct kvm_s390_iwq),
which is the maximum numbew of possibwy pending cpu-wocaw intewwupts.

4.96 KVM_SMI
------------

:Capabiwity: KVM_CAP_X86_SMM
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0 on success, -1 on ewwow

Queues an SMI on the thwead's vcpu.

4.97 KVM_X86_SET_MSW_FIWTEW
----------------------------

:Capabiwity: KVM_CAP_X86_MSW_FIWTEW
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_msw_fiwtew
:Wetuwns: 0 on success, < 0 on ewwow

::

  stwuct kvm_msw_fiwtew_wange {
  #define KVM_MSW_FIWTEW_WEAD  (1 << 0)
  #define KVM_MSW_FIWTEW_WWITE (1 << 1)
	__u32 fwags;
	__u32 nmsws; /* numbew of msws in bitmap */
	__u32 base;  /* MSW index the bitmap stawts at */
	__u8 *bitmap; /* a 1 bit awwows the opewations in fwags, 0 denies */
  };

  #define KVM_MSW_FIWTEW_MAX_WANGES 16
  stwuct kvm_msw_fiwtew {
  #define KVM_MSW_FIWTEW_DEFAUWT_AWWOW (0 << 0)
  #define KVM_MSW_FIWTEW_DEFAUWT_DENY  (1 << 0)
	__u32 fwags;
	stwuct kvm_msw_fiwtew_wange wanges[KVM_MSW_FIWTEW_MAX_WANGES];
  };

fwags vawues fow ``stwuct kvm_msw_fiwtew_wange``:

``KVM_MSW_FIWTEW_WEAD``

  Fiwtew wead accesses to MSWs using the given bitmap. A 0 in the bitmap
  indicates that wead accesses shouwd be denied, whiwe a 1 indicates that
  a wead fow a pawticuwaw MSW shouwd be awwowed wegawdwess of the defauwt
  fiwtew action.

``KVM_MSW_FIWTEW_WWITE``

  Fiwtew wwite accesses to MSWs using the given bitmap. A 0 in the bitmap
  indicates that wwite accesses shouwd be denied, whiwe a 1 indicates that
  a wwite fow a pawticuwaw MSW shouwd be awwowed wegawdwess of the defauwt
  fiwtew action.

fwags vawues fow ``stwuct kvm_msw_fiwtew``:

``KVM_MSW_FIWTEW_DEFAUWT_AWWOW``

  If no fiwtew wange matches an MSW index that is getting accessed, KVM wiww
  awwow accesses to aww MSWs by defauwt.

``KVM_MSW_FIWTEW_DEFAUWT_DENY``

  If no fiwtew wange matches an MSW index that is getting accessed, KVM wiww
  deny accesses to aww MSWs by defauwt.

This ioctw awwows usewspace to define up to 16 bitmaps of MSW wanges to deny
guest MSW accesses that wouwd nowmawwy be awwowed by KVM.  If an MSW is not
covewed by a specific wange, the "defauwt" fiwtewing behaviow appwies.  Each
bitmap wange covews MSWs fwom [base .. base+nmsws).

If an MSW access is denied by usewspace, the wesuwting KVM behaviow depends on
whethew ow not KVM_CAP_X86_USEW_SPACE_MSW's KVM_MSW_EXIT_WEASON_FIWTEW is
enabwed.  If KVM_MSW_EXIT_WEASON_FIWTEW is enabwed, KVM wiww exit to usewspace
on denied accesses, i.e. usewspace effectivewy intewcepts the MSW access.  If
KVM_MSW_EXIT_WEASON_FIWTEW is not enabwed, KVM wiww inject a #GP into the guest
on denied accesses.

If an MSW access is awwowed by usewspace, KVM wiww emuwate and/ow viwtuawize
the access in accowdance with the vCPU modew.  Note, KVM may stiww uwtimatewy
inject a #GP if an access is awwowed by usewspace, e.g. if KVM doesn't suppowt
the MSW, ow to fowwow awchitectuwaw behaviow fow the MSW.

By defauwt, KVM opewates in KVM_MSW_FIWTEW_DEFAUWT_AWWOW mode with no MSW wange
fiwtews.

Cawwing this ioctw with an empty set of wanges (aww nmsws == 0) disabwes MSW
fiwtewing. In that mode, ``KVM_MSW_FIWTEW_DEFAUWT_DENY`` is invawid and causes
an ewwow.

.. wawning::
   MSW accesses as pawt of nested VM-Entew/VM-Exit awe not fiwtewed.
   This incwudes both wwites to individuaw VMCS fiewds and weads/wwites
   thwough the MSW wists pointed to by the VMCS.

   x2APIC MSW accesses cannot be fiwtewed (KVM siwentwy ignowes fiwtews that
   covew any x2APIC MSWs).

Note, invoking this ioctw whiwe a vCPU is wunning is inhewentwy wacy.  Howevew,
KVM does guawantee that vCPUs wiww see eithew the pwevious fiwtew ow the new
fiwtew, e.g. MSWs with identicaw settings in both the owd and new fiwtew wiww
have detewministic behaviow.

Simiwawwy, if usewspace wishes to intewcept on denied accesses,
KVM_MSW_EXIT_WEASON_FIWTEW must be enabwed befowe activating any fiwtews, and
weft enabwed untiw aftew aww fiwtews awe deactivated.  Faiwuwe to do so may
wesuwt in KVM injecting a #GP instead of exiting to usewspace.

4.98 KVM_CWEATE_SPAPW_TCE_64
----------------------------

:Capabiwity: KVM_CAP_SPAPW_TCE_64
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_cweate_spapw_tce_64 (in)
:Wetuwns: fiwe descwiptow fow manipuwating the cweated TCE tabwe

This is an extension fow KVM_CAP_SPAPW_TCE which onwy suppowts 32bit
windows, descwibed in 4.62 KVM_CWEATE_SPAPW_TCE

This capabiwity uses extended stwuct in ioctw intewface::

  /* fow KVM_CAP_SPAPW_TCE_64 */
  stwuct kvm_cweate_spapw_tce_64 {
	__u64 wiobn;
	__u32 page_shift;
	__u32 fwags;
	__u64 offset;	/* in pages */
	__u64 size; 	/* in pages */
  };

The aim of extension is to suppowt an additionaw biggew DMA window with
a vawiabwe page size.
KVM_CWEATE_SPAPW_TCE_64 weceives a 64bit window size, an IOMMU page shift and
a bus offset of the cowwesponding DMA window, @size and @offset awe numbews
of IOMMU pages.

@fwags awe not used at the moment.

The west of functionawity is identicaw to KVM_CWEATE_SPAPW_TCE.

4.99 KVM_WEINJECT_CONTWOW
-------------------------

:Capabiwity: KVM_CAP_WEINJECT_CONTWOW
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_weinject_contwow (in)
:Wetuwns: 0 on success,
         -EFAUWT if stwuct kvm_weinject_contwow cannot be wead,
         -ENXIO if KVM_CWEATE_PIT ow KVM_CWEATE_PIT2 didn't succeed eawwiew.

i8254 (PIT) has two modes, weinject and !weinject.  The defauwt is weinject,
whewe KVM queues ewapsed i8254 ticks and monitows compwetion of intewwupt fwom
vectow(s) that i8254 injects.  Weinject mode dequeues a tick and injects its
intewwupt whenevew thewe isn't a pending intewwupt fwom i8254.
!weinject mode injects an intewwupt as soon as a tick awwives.

::

  stwuct kvm_weinject_contwow {
	__u8 pit_weinject;
	__u8 wesewved[31];
  };

pit_weinject = 0 (!weinject mode) is wecommended, unwess wunning an owd
opewating system that uses the PIT fow timing (e.g. Winux 2.4.x).

4.100 KVM_PPC_CONFIGUWE_V3_MMU
------------------------------

:Capabiwity: KVM_CAP_PPC_WADIX_MMU ow KVM_CAP_PPC_HASH_MMU_V3
:Awchitectuwes: ppc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_mmuv3_cfg (in)
:Wetuwns: 0 on success,
         -EFAUWT if stwuct kvm_ppc_mmuv3_cfg cannot be wead,
         -EINVAW if the configuwation is invawid

This ioctw contwows whethew the guest wiww use wadix ow HPT (hashed
page tabwe) twanswation, and sets the pointew to the pwocess tabwe fow
the guest.

::

  stwuct kvm_ppc_mmuv3_cfg {
	__u64	fwags;
	__u64	pwocess_tabwe;
  };

Thewe awe two bits that can be set in fwags; KVM_PPC_MMUV3_WADIX and
KVM_PPC_MMUV3_GTSE.  KVM_PPC_MMUV3_WADIX, if set, configuwes the guest
to use wadix twee twanswation, and if cweaw, to use HPT twanswation.
KVM_PPC_MMUV3_GTSE, if set and if KVM pewmits it, configuwes the guest
to be abwe to use the gwobaw TWB and SWB invawidation instwuctions;
if cweaw, the guest may not use these instwuctions.

The pwocess_tabwe fiewd specifies the addwess and size of the guest
pwocess tabwe, which is in the guest's space.  This fiewd is fowmatted
as the second doubwewowd of the pawtition tabwe entwy, as defined in
the Powew ISA V3.00, Book III section 5.7.6.1.

4.101 KVM_PPC_GET_WMMU_INFO
---------------------------

:Capabiwity: KVM_CAP_PPC_WADIX_MMU
:Awchitectuwes: ppc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_wmmu_info (out)
:Wetuwns: 0 on success,
	 -EFAUWT if stwuct kvm_ppc_wmmu_info cannot be wwitten,
	 -EINVAW if no usefuw infowmation can be wetuwned

This ioctw wetuwns a stwuctuwe containing two things: (a) a wist
containing suppowted wadix twee geometwies, and (b) a wist that maps
page sizes to put in the "AP" (actuaw page size) fiewd fow the twbie
(TWB invawidate entwy) instwuction.

::

  stwuct kvm_ppc_wmmu_info {
	stwuct kvm_ppc_wadix_geom {
		__u8	page_shift;
		__u8	wevew_bits[4];
		__u8	pad[3];
	}	geometwies[8];
	__u32	ap_encodings[8];
  };

The geometwies[] fiewd gives up to 8 suppowted geometwies fow the
wadix page tabwe, in tewms of the wog base 2 of the smawwest page
size, and the numbew of bits indexed at each wevew of the twee, fwom
the PTE wevew up to the PGD wevew in that owdew.  Any unused entwies
wiww have 0 in the page_shift fiewd.

The ap_encodings gives the suppowted page sizes and theiw AP fiewd
encodings, encoded with the AP vawue in the top 3 bits and the wog
base 2 of the page size in the bottom 6 bits.

4.102 KVM_PPC_WESIZE_HPT_PWEPAWE
--------------------------------

:Capabiwity: KVM_CAP_SPAPW_WESIZE_HPT
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_wesize_hpt (in)
:Wetuwns: 0 on successfuw compwetion,
	 >0 if a new HPT is being pwepawed, the vawue is an estimated
         numbew of miwwiseconds untiw pwepawation is compwete,
         -EFAUWT if stwuct kvm_weinject_contwow cannot be wead,
	 -EINVAW if the suppwied shift ow fwags awe invawid,
	 -ENOMEM if unabwe to awwocate the new HPT,

Used to impwement the PAPW extension fow wuntime wesizing of a guest's
Hashed Page Tabwe (HPT).  Specificawwy this stawts, stops ow monitows
the pwepawation of a new potentiaw HPT fow the guest, essentiawwy
impwementing the H_WESIZE_HPT_PWEPAWE hypewcaww.

::

  stwuct kvm_ppc_wesize_hpt {
	__u64 fwags;
	__u32 shift;
	__u32 pad;
  };

If cawwed with shift > 0 when thewe is no pending HPT fow the guest,
this begins pwepawation of a new pending HPT of size 2^(shift) bytes.
It then wetuwns a positive integew with the estimated numbew of
miwwiseconds untiw pwepawation is compwete.

If cawwed when thewe is a pending HPT whose size does not match that
wequested in the pawametews, discawds the existing pending HPT and
cweates a new one as above.

If cawwed when thewe is a pending HPT of the size wequested, wiww:

  * If pwepawation of the pending HPT is awweady compwete, wetuwn 0
  * If pwepawation of the pending HPT has faiwed, wetuwn an ewwow
    code, then discawd the pending HPT.
  * If pwepawation of the pending HPT is stiww in pwogwess, wetuwn an
    estimated numbew of miwwiseconds untiw pwepawation is compwete.

If cawwed with shift == 0, discawds any cuwwentwy pending HPT and
wetuwns 0 (i.e. cancews any in-pwogwess pwepawation).

fwags is wesewved fow futuwe expansion, cuwwentwy setting any bits in
fwags wiww wesuwt in an -EINVAW.

Nowmawwy this wiww be cawwed wepeatedwy with the same pawametews untiw
it wetuwns <= 0.  The fiwst caww wiww initiate pwepawation, subsequent
ones wiww monitow pwepawation untiw it compwetes ow faiws.

4.103 KVM_PPC_WESIZE_HPT_COMMIT
-------------------------------

:Capabiwity: KVM_CAP_SPAPW_WESIZE_HPT
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_wesize_hpt (in)
:Wetuwns: 0 on successfuw compwetion,
         -EFAUWT if stwuct kvm_weinject_contwow cannot be wead,
	 -EINVAW if the suppwied shift ow fwags awe invawid,
	 -ENXIO is thewe is no pending HPT, ow the pending HPT doesn't
         have the wequested size,
	 -EBUSY if the pending HPT is not fuwwy pwepawed,
	 -ENOSPC if thewe was a hash cowwision when moving existing
         HPT entwies to the new HPT,
	 -EIO on othew ewwow conditions

Used to impwement the PAPW extension fow wuntime wesizing of a guest's
Hashed Page Tabwe (HPT).  Specificawwy this wequests that the guest be
twansfewwed to wowking with the new HPT, essentiawwy impwementing the
H_WESIZE_HPT_COMMIT hypewcaww.

::

  stwuct kvm_ppc_wesize_hpt {
	__u64 fwags;
	__u32 shift;
	__u32 pad;
  };

This shouwd onwy be cawwed aftew KVM_PPC_WESIZE_HPT_PWEPAWE has
wetuwned 0 with the same pawametews.  In othew cases
KVM_PPC_WESIZE_HPT_COMMIT wiww wetuwn an ewwow (usuawwy -ENXIO ow
-EBUSY, though othews may be possibwe if the pwepawation was stawted,
but faiwed).

This wiww have undefined effects on the guest if it has not awweady
pwaced itsewf in a quiescent state whewe no vcpu wiww make MMU enabwed
memowy accesses.

On successfuw compwetion, the pending HPT wiww become the guest's active
HPT and the pwevious HPT wiww be discawded.

On faiwuwe, the guest wiww stiww be opewating on its pwevious HPT.

4.104 KVM_X86_GET_MCE_CAP_SUPPOWTED
-----------------------------------

:Capabiwity: KVM_CAP_MCE
:Awchitectuwes: x86
:Type: system ioctw
:Pawametews: u64 mce_cap (out)
:Wetuwns: 0 on success, -1 on ewwow

Wetuwns suppowted MCE capabiwities. The u64 mce_cap pawametew
has the same fowmat as the MSW_IA32_MCG_CAP wegistew. Suppowted
capabiwities wiww have the cowwesponding bits set.

4.105 KVM_X86_SETUP_MCE
-----------------------

:Capabiwity: KVM_CAP_MCE
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: u64 mcg_cap (in)
:Wetuwns: 0 on success,
         -EFAUWT if u64 mcg_cap cannot be wead,
         -EINVAW if the wequested numbew of banks is invawid,
         -EINVAW if wequested MCE capabiwity is not suppowted.

Initiawizes MCE suppowt fow use. The u64 mcg_cap pawametew
has the same fowmat as the MSW_IA32_MCG_CAP wegistew and
specifies which capabiwities shouwd be enabwed. The maximum
suppowted numbew of ewwow-wepowting banks can be wetwieved when
checking fow KVM_CAP_MCE. The suppowted capabiwities can be
wetwieved with KVM_X86_GET_MCE_CAP_SUPPOWTED.

4.106 KVM_X86_SET_MCE
---------------------

:Capabiwity: KVM_CAP_MCE
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_x86_mce (in)
:Wetuwns: 0 on success,
         -EFAUWT if stwuct kvm_x86_mce cannot be wead,
         -EINVAW if the bank numbew is invawid,
         -EINVAW if VAW bit is not set in status fiewd.

Inject a machine check ewwow (MCE) into the guest. The input
pawametew is::

  stwuct kvm_x86_mce {
	__u64 status;
	__u64 addw;
	__u64 misc;
	__u64 mcg_status;
	__u8 bank;
	__u8 pad1[7];
	__u64 pad2[3];
  };

If the MCE being wepowted is an uncowwected ewwow, KVM wiww
inject it as an MCE exception into the guest. If the guest
MCG_STATUS wegistew wepowts that an MCE is in pwogwess, KVM
causes an KVM_EXIT_SHUTDOWN vmexit.

Othewwise, if the MCE is a cowwected ewwow, KVM wiww just
stowe it in the cowwesponding bank (pwovided this bank is
not howding a pweviouswy wepowted uncowwected ewwow).

4.107 KVM_S390_GET_CMMA_BITS
----------------------------

:Capabiwity: KVM_CAP_S390_CMMA_MIGWATION
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_s390_cmma_wog (in, out)
:Wetuwns: 0 on success, a negative vawue on ewwow

Ewwows:

  ======     =============================================================
  ENOMEM     not enough memowy can be awwocated to compwete the task
  ENXIO      if CMMA is not enabwed
  EINVAW     if KVM_S390_CMMA_PEEK is not set but migwation mode was not enabwed
  EINVAW     if KVM_S390_CMMA_PEEK is not set but diwty twacking has been
             disabwed (and thus migwation mode was automaticawwy disabwed)
  EFAUWT     if the usewspace addwess is invawid ow if no page tabwe is
             pwesent fow the addwesses (e.g. when using hugepages).
  ======     =============================================================

This ioctw is used to get the vawues of the CMMA bits on the s390
awchitectuwe. It is meant to be used in two scenawios:

- Duwing wive migwation to save the CMMA vawues. Wive migwation needs
  to be enabwed via the KVM_WEQ_STAWT_MIGWATION VM pwopewty.
- To non-destwuctivewy peek at the CMMA vawues, with the fwag
  KVM_S390_CMMA_PEEK set.

The ioctw takes pawametews via the kvm_s390_cmma_wog stwuct. The desiwed
vawues awe wwitten to a buffew whose wocation is indicated via the "vawues"
membew in the kvm_s390_cmma_wog stwuct.  The vawues in the input stwuct awe
awso updated as needed.

Each CMMA vawue takes up one byte.

::

  stwuct kvm_s390_cmma_wog {
	__u64 stawt_gfn;
	__u32 count;
	__u32 fwags;
	union {
		__u64 wemaining;
		__u64 mask;
	};
	__u64 vawues;
  };

stawt_gfn is the numbew of the fiwst guest fwame whose CMMA vawues awe
to be wetwieved,

count is the wength of the buffew in bytes,

vawues points to the buffew whewe the wesuwt wiww be wwitten to.

If count is gweatew than KVM_S390_SKEYS_MAX, then it is considewed to be
KVM_S390_SKEYS_MAX. KVM_S390_SKEYS_MAX is we-used fow consistency with
othew ioctws.

The wesuwt is wwitten in the buffew pointed to by the fiewd vawues, and
the vawues of the input pawametew awe updated as fowwows.

Depending on the fwags, diffewent actions awe pewfowmed. The onwy
suppowted fwag so faw is KVM_S390_CMMA_PEEK.

The defauwt behaviouw if KVM_S390_CMMA_PEEK is not set is:
stawt_gfn wiww indicate the fiwst page fwame whose CMMA bits wewe diwty.
It is not necessawiwy the same as the one passed as input, as cwean pages
awe skipped.

count wiww indicate the numbew of bytes actuawwy wwitten in the buffew.
It can (and vewy often wiww) be smawwew than the input vawue, since the
buffew is onwy fiwwed untiw 16 bytes of cwean vawues awe found (which
awe then not copied in the buffew). Since a CMMA migwation bwock needs
the base addwess and the wength, fow a totaw of 16 bytes, we wiww send
back some cwean data if thewe is some diwty data aftewwawds, as wong as
the size of the cwean data does not exceed the size of the headew. This
awwows to minimize the amount of data to be saved ow twansfewwed ovew
the netwowk at the expense of mowe woundtwips to usewspace. The next
invocation of the ioctw wiww skip ovew aww the cwean vawues, saving
potentiawwy mowe than just the 16 bytes we found.

If KVM_S390_CMMA_PEEK is set:
the existing stowage attwibutes awe wead even when not in migwation
mode, and no othew action is pewfowmed;

the output stawt_gfn wiww be equaw to the input stawt_gfn,

the output count wiww be equaw to the input count, except if the end of
memowy has been weached.

In both cases:
the fiewd "wemaining" wiww indicate the totaw numbew of diwty CMMA vawues
stiww wemaining, ow 0 if KVM_S390_CMMA_PEEK is set and migwation mode is
not enabwed.

mask is unused.

vawues points to the usewspace buffew whewe the wesuwt wiww be stowed.

4.108 KVM_S390_SET_CMMA_BITS
----------------------------

:Capabiwity: KVM_CAP_S390_CMMA_MIGWATION
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_s390_cmma_wog (in)
:Wetuwns: 0 on success, a negative vawue on ewwow

This ioctw is used to set the vawues of the CMMA bits on the s390
awchitectuwe. It is meant to be used duwing wive migwation to westowe
the CMMA vawues, but thewe awe no westwictions on its use.
The ioctw takes pawametews via the kvm_s390_cmma_vawues stwuct.
Each CMMA vawue takes up one byte.

::

  stwuct kvm_s390_cmma_wog {
	__u64 stawt_gfn;
	__u32 count;
	__u32 fwags;
	union {
		__u64 wemaining;
		__u64 mask;
 	};
	__u64 vawues;
  };

stawt_gfn indicates the stawting guest fwame numbew,

count indicates how many vawues awe to be considewed in the buffew,

fwags is not used and must be 0.

mask indicates which PGSTE bits awe to be considewed.

wemaining is not used.

vawues points to the buffew in usewspace whewe to stowe the vawues.

This ioctw can faiw with -ENOMEM if not enough memowy can be awwocated to
compwete the task, with -ENXIO if CMMA is not enabwed, with -EINVAW if
the count fiewd is too wawge (e.g. mowe than KVM_S390_CMMA_SIZE_MAX) ow
if the fwags fiewd was not 0, with -EFAUWT if the usewspace addwess is
invawid, if invawid pages awe wwitten to (e.g. aftew the end of memowy)
ow if no page tabwe is pwesent fow the addwesses (e.g. when using
hugepages).

4.109 KVM_PPC_GET_CPU_CHAW
--------------------------

:Capabiwity: KVM_CAP_PPC_GET_CPU_CHAW
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: stwuct kvm_ppc_cpu_chaw (out)
:Wetuwns: 0 on successfuw compwetion,
	 -EFAUWT if stwuct kvm_ppc_cpu_chaw cannot be wwitten

This ioctw gives usewspace infowmation about cewtain chawactewistics
of the CPU wewating to specuwative execution of instwuctions and
possibwe infowmation weakage wesuwting fwom specuwative execution (see
CVE-2017-5715, CVE-2017-5753 and CVE-2017-5754).  The infowmation is
wetuwned in stwuct kvm_ppc_cpu_chaw, which wooks wike this::

  stwuct kvm_ppc_cpu_chaw {
	__u64	chawactew;		/* chawactewistics of the CPU */
	__u64	behaviouw;		/* wecommended softwawe behaviouw */
	__u64	chawactew_mask;		/* vawid bits in chawactew */
	__u64	behaviouw_mask;		/* vawid bits in behaviouw */
  };

Fow extensibiwity, the chawactew_mask and behaviouw_mask fiewds
indicate which bits of chawactew and behaviouw have been fiwwed in by
the kewnew.  If the set of defined bits is extended in futuwe then
usewspace wiww be abwe to teww whethew it is wunning on a kewnew that
knows about the new bits.

The chawactew fiewd descwibes attwibutes of the CPU which can hewp
with pweventing inadvewtent infowmation discwosuwe - specificawwy,
whethew thewe is an instwuction to fwash-invawidate the W1 data cache
(owi 30,30,0 ow mtspw SPWN_TWIG2,wN), whethew the W1 data cache is set
to a mode whewe entwies can onwy be used by the thwead that cweated
them, whethew the bcctw[w] instwuction pwevents specuwation, and
whethew a specuwation bawwiew instwuction (owi 31,31,0) is pwovided.

The behaviouw fiewd descwibes actions that softwawe shouwd take to
pwevent inadvewtent infowmation discwosuwe, and thus descwibes which
vuwnewabiwities the hawdwawe is subject to; specificawwy whethew the
W1 data cache shouwd be fwushed when wetuwning to usew mode fwom the
kewnew, and whethew a specuwation bawwiew shouwd be pwaced between an
awway bounds check and the awway access.

These fiewds use the same bit definitions as the new
H_GET_CPU_CHAWACTEWISTICS hypewcaww.

4.110 KVM_MEMOWY_ENCWYPT_OP
---------------------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: vm
:Pawametews: an opaque pwatfowm specific stwuctuwe (in/out)
:Wetuwns: 0 on success; -1 on ewwow

If the pwatfowm suppowts cweating encwypted VMs then this ioctw can be used
fow issuing pwatfowm-specific memowy encwyption commands to manage those
encwypted VMs.

Cuwwentwy, this ioctw is used fow issuing Secuwe Encwypted Viwtuawization
(SEV) commands on AMD Pwocessows. The SEV commands awe defined in
Documentation/viwt/kvm/x86/amd-memowy-encwyption.wst.

4.111 KVM_MEMOWY_ENCWYPT_WEG_WEGION
-----------------------------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: system
:Pawametews: stwuct kvm_enc_wegion (in)
:Wetuwns: 0 on success; -1 on ewwow

This ioctw can be used to wegistew a guest memowy wegion which may
contain encwypted data (e.g. guest WAM, SMWAM etc).

It is used in the SEV-enabwed guest. When encwyption is enabwed, a guest
memowy wegion may contain encwypted data. The SEV memowy encwyption
engine uses a tweak such that two identicaw pwaintext pages, each at
diffewent wocations wiww have diffewing ciphewtexts. So swapping ow
moving ciphewtext of those pages wiww not wesuwt in pwaintext being
swapped. So wewocating (ow migwating) physicaw backing pages fow the SEV
guest wiww wequiwe some additionaw steps.

Note: The cuwwent SEV key management spec does not pwovide commands to
swap ow migwate (move) ciphewtext pages. Hence, fow now we pin the guest
memowy wegion wegistewed with the ioctw.

4.112 KVM_MEMOWY_ENCWYPT_UNWEG_WEGION
-------------------------------------

:Capabiwity: basic
:Awchitectuwes: x86
:Type: system
:Pawametews: stwuct kvm_enc_wegion (in)
:Wetuwns: 0 on success; -1 on ewwow

This ioctw can be used to unwegistew the guest memowy wegion wegistewed
with KVM_MEMOWY_ENCWYPT_WEG_WEGION ioctw above.

4.113 KVM_HYPEWV_EVENTFD
------------------------

:Capabiwity: KVM_CAP_HYPEWV_EVENTFD
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_hypewv_eventfd (in)

This ioctw (un)wegistews an eventfd to weceive notifications fwom the guest on
the specified Hypew-V connection id thwough the SIGNAW_EVENT hypewcaww, without
causing a usew exit.  SIGNAW_EVENT hypewcaww with non-zewo event fwag numbew
(bits 24-31) stiww twiggews a KVM_EXIT_HYPEWV_HCAWW usew exit.

::

  stwuct kvm_hypewv_eventfd {
	__u32 conn_id;
	__s32 fd;
	__u32 fwags;
	__u32 padding[3];
  };

The conn_id fiewd shouwd fit within 24 bits::

  #define KVM_HYPEWV_CONN_ID_MASK		0x00ffffff

The acceptabwe vawues fow the fwags fiewd awe::

  #define KVM_HYPEWV_EVENTFD_DEASSIGN	(1 << 0)

:Wetuwns: 0 on success,
 	  -EINVAW if conn_id ow fwags is outside the awwowed wange,
	  -ENOENT on deassign if the conn_id isn't wegistewed,
	  -EEXIST on assign if the conn_id is awweady wegistewed

4.114 KVM_GET_NESTED_STATE
--------------------------

:Capabiwity: KVM_CAP_NESTED_STATE
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_nested_state (in/out)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  =====      =============================================================
  E2BIG      the totaw state size exceeds the vawue of 'size' specified by
             the usew; the size wequiwed wiww be wwitten into size.
  =====      =============================================================

::

  stwuct kvm_nested_state {
	__u16 fwags;
	__u16 fowmat;
	__u32 size;

	union {
		stwuct kvm_vmx_nested_state_hdw vmx;
		stwuct kvm_svm_nested_state_hdw svm;

		/* Pad the headew to 128 bytes.  */
		__u8 pad[120];
	} hdw;

	union {
		stwuct kvm_vmx_nested_state_data vmx[0];
		stwuct kvm_svm_nested_state_data svm[0];
	} data;
  };

  #define KVM_STATE_NESTED_GUEST_MODE		0x00000001
  #define KVM_STATE_NESTED_WUN_PENDING		0x00000002
  #define KVM_STATE_NESTED_EVMCS		0x00000004

  #define KVM_STATE_NESTED_FOWMAT_VMX		0
  #define KVM_STATE_NESTED_FOWMAT_SVM		1

  #define KVM_STATE_NESTED_VMX_VMCS_SIZE	0x1000

  #define KVM_STATE_NESTED_VMX_SMM_GUEST_MODE	0x00000001
  #define KVM_STATE_NESTED_VMX_SMM_VMXON	0x00000002

  #define KVM_STATE_VMX_PWEEMPTION_TIMEW_DEADWINE 0x00000001

  stwuct kvm_vmx_nested_state_hdw {
	__u64 vmxon_pa;
	__u64 vmcs12_pa;

	stwuct {
		__u16 fwags;
	} smm;

	__u32 fwags;
	__u64 pweemption_timew_deadwine;
  };

  stwuct kvm_vmx_nested_state_data {
	__u8 vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
	__u8 shadow_vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
  };

This ioctw copies the vcpu's nested viwtuawization state fwom the kewnew to
usewspace.

The maximum size of the state can be wetwieved by passing KVM_CAP_NESTED_STATE
to the KVM_CHECK_EXTENSION ioctw().

4.115 KVM_SET_NESTED_STATE
--------------------------

:Capabiwity: KVM_CAP_NESTED_STATE
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_nested_state (in)
:Wetuwns: 0 on success, -1 on ewwow

This copies the vcpu's kvm_nested_state stwuct fwom usewspace to the kewnew.
Fow the definition of stwuct kvm_nested_state, see KVM_GET_NESTED_STATE.

4.116 KVM_(UN)WEGISTEW_COAWESCED_MMIO
-------------------------------------

:Capabiwity: KVM_CAP_COAWESCED_MMIO (fow coawesced mmio)
	     KVM_CAP_COAWESCED_PIO (fow coawesced pio)
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_coawesced_mmio_zone
:Wetuwns: 0 on success, < 0 on ewwow

Coawesced I/O is a pewfowmance optimization that defews hawdwawe
wegistew wwite emuwation so that usewspace exits awe avoided.  It is
typicawwy used to weduce the ovewhead of emuwating fwequentwy accessed
hawdwawe wegistews.

When a hawdwawe wegistew is configuwed fow coawesced I/O, wwite accesses
do not exit to usewspace and theiw vawue is wecowded in a wing buffew
that is shawed between kewnew and usewspace.

Coawesced I/O is used if one ow mowe wwite accesses to a hawdwawe
wegistew can be defewwed untiw a wead ow a wwite to anothew hawdwawe
wegistew on the same device.  This wast access wiww cause a vmexit and
usewspace wiww pwocess accesses fwom the wing buffew befowe emuwating
it. That wiww avoid exiting to usewspace on wepeated wwites.

Coawesced pio is based on coawesced mmio. Thewe is wittwe diffewence
between coawesced mmio and pio except that coawesced pio wecowds accesses
to I/O powts.

4.117 KVM_CWEAW_DIWTY_WOG (vm ioctw)
------------------------------------

:Capabiwity: KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2
:Awchitectuwes: x86, awm64, mips
:Type: vm ioctw
:Pawametews: stwuct kvm_cweaw_diwty_wog (in)
:Wetuwns: 0 on success, -1 on ewwow

::

  /* fow KVM_CWEAW_DIWTY_WOG */
  stwuct kvm_cweaw_diwty_wog {
	__u32 swot;
	__u32 num_pages;
	__u64 fiwst_page;
	union {
		void __usew *diwty_bitmap; /* one bit pew page */
		__u64 padding;
	};
  };

The ioctw cweaws the diwty status of pages in a memowy swot, accowding to
the bitmap that is passed in stwuct kvm_cweaw_diwty_wog's diwty_bitmap
fiewd.  Bit 0 of the bitmap cowwesponds to page "fiwst_page" in the
memowy swot, and num_pages is the size in bits of the input bitmap.
fiwst_page must be a muwtipwe of 64; num_pages must awso be a muwtipwe of
64 unwess fiwst_page + num_pages is the size of the memowy swot.  Fow each
bit that is set in the input bitmap, the cowwesponding page is mawked "cwean"
in KVM's diwty bitmap, and diwty twacking is we-enabwed fow that page
(fow exampwe via wwite-pwotection, ow by cweawing the diwty bit in
a page tabwe entwy).

If KVM_CAP_MUWTI_ADDWESS_SPACE is avaiwabwe, bits 16-31 of swot fiewd specifies
the addwess space fow which you want to cweaw the diwty status.  See
KVM_SET_USEW_MEMOWY_WEGION fow detaiws on the usage of swot fiewd.

This ioctw is mostwy usefuw when KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2
is enabwed; fow mowe infowmation, see the descwiption of the capabiwity.
Howevew, it can awways be used as wong as KVM_CHECK_EXTENSION confiwms
that KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2 is pwesent.

4.118 KVM_GET_SUPPOWTED_HV_CPUID
--------------------------------

:Capabiwity: KVM_CAP_HYPEWV_CPUID (vcpu), KVM_CAP_SYS_HYPEWV_CPUID (system)
:Awchitectuwes: x86
:Type: system ioctw, vcpu ioctw
:Pawametews: stwuct kvm_cpuid2 (in/out)
:Wetuwns: 0 on success, -1 on ewwow

::

  stwuct kvm_cpuid2 {
	__u32 nent;
	__u32 padding;
	stwuct kvm_cpuid_entwy2 entwies[0];
  };

  stwuct kvm_cpuid_entwy2 {
	__u32 function;
	__u32 index;
	__u32 fwags;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding[3];
  };

This ioctw wetuwns x86 cpuid featuwes weaves wewated to Hypew-V emuwation in
KVM.  Usewspace can use the infowmation wetuwned by this ioctw to constwuct
cpuid infowmation pwesented to guests consuming Hypew-V enwightenments (e.g.
Windows ow Hypew-V guests).

CPUID featuwe weaves wetuwned by this ioctw awe defined by Hypew-V Top Wevew
Functionaw Specification (TWFS). These weaves can't be obtained with
KVM_GET_SUPPOWTED_CPUID ioctw because some of them intewsect with KVM featuwe
weaves (0x40000000, 0x40000001).

Cuwwentwy, the fowwowing wist of CPUID weaves awe wetuwned:

 - HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS
 - HYPEWV_CPUID_INTEWFACE
 - HYPEWV_CPUID_VEWSION
 - HYPEWV_CPUID_FEATUWES
 - HYPEWV_CPUID_ENWIGHTMENT_INFO
 - HYPEWV_CPUID_IMPWEMENT_WIMITS
 - HYPEWV_CPUID_NESTED_FEATUWES
 - HYPEWV_CPUID_SYNDBG_VENDOW_AND_MAX_FUNCTIONS
 - HYPEWV_CPUID_SYNDBG_INTEWFACE
 - HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES

Usewspace invokes KVM_GET_SUPPOWTED_HV_CPUID by passing a kvm_cpuid2 stwuctuwe
with the 'nent' fiewd indicating the numbew of entwies in the vawiabwe-size
awway 'entwies'.  If the numbew of entwies is too wow to descwibe aww Hypew-V
featuwe weaves, an ewwow (E2BIG) is wetuwned. If the numbew is mowe ow equaw
to the numbew of Hypew-V featuwe weaves, the 'nent' fiewd is adjusted to the
numbew of vawid entwies in the 'entwies' awway, which is then fiwwed.

'index' and 'fwags' fiewds in 'stwuct kvm_cpuid_entwy2' awe cuwwentwy wesewved,
usewspace shouwd not expect to get any pawticuwaw vawue thewe.

Note, vcpu vewsion of KVM_GET_SUPPOWTED_HV_CPUID is cuwwentwy depwecated. Unwike
system ioctw which exposes aww suppowted featuwe bits unconditionawwy, vcpu
vewsion has the fowwowing quiwks:

- HYPEWV_CPUID_NESTED_FEATUWES weaf and HV_X64_ENWIGHTENED_VMCS_WECOMMENDED
  featuwe bit awe onwy exposed when Enwightened VMCS was pweviouswy enabwed
  on the cowwesponding vCPU (KVM_CAP_HYPEWV_ENWIGHTENED_VMCS).
- HV_STIMEW_DIWECT_MODE_AVAIWABWE bit is onwy exposed with in-kewnew WAPIC.
  (pwesumes KVM_CWEATE_IWQCHIP has awweady been cawwed).

4.119 KVM_AWM_VCPU_FINAWIZE
---------------------------

:Awchitectuwes: awm64
:Type: vcpu ioctw
:Pawametews: int featuwe (in)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  ======     ==============================================================
  EPEWM      featuwe not enabwed, needs configuwation, ow awweady finawized
  EINVAW     featuwe unknown ow not pwesent
  ======     ==============================================================

Wecognised vawues fow featuwe:

  =====      ===========================================
  awm64      KVM_AWM_VCPU_SVE (wequiwes KVM_CAP_AWM_SVE)
  =====      ===========================================

Finawizes the configuwation of the specified vcpu featuwe.

The vcpu must awweady have been initiawised, enabwing the affected featuwe, by
means of a successfuw KVM_AWM_VCPU_INIT caww with the appwopwiate fwag set in
featuwes[].

Fow affected vcpu featuwes, this is a mandatowy step that must be pewfowmed
befowe the vcpu is fuwwy usabwe.

Between KVM_AWM_VCPU_INIT and KVM_AWM_VCPU_FINAWIZE, the featuwe may be
configuwed by use of ioctws such as KVM_SET_ONE_WEG.  The exact configuwation
that shouwd be pewfowmed and how to do it awe featuwe-dependent.

Othew cawws that depend on a pawticuwaw featuwe being finawized, such as
KVM_WUN, KVM_GET_WEG_WIST, KVM_GET_ONE_WEG and KVM_SET_ONE_WEG, wiww faiw with
-EPEWM unwess the featuwe has awweady been finawized by means of a
KVM_AWM_VCPU_FINAWIZE caww.

See KVM_AWM_VCPU_INIT fow detaiws of vcpu featuwes that wequiwe finawization
using this ioctw.

4.120 KVM_SET_PMU_EVENT_FIWTEW
------------------------------

:Capabiwity: KVM_CAP_PMU_EVENT_FIWTEW
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_pmu_event_fiwtew (in)
:Wetuwns: 0 on success, -1 on ewwow

Ewwows:

  ======     ============================================================
  EFAUWT     awgs[0] cannot be accessed
  EINVAW     awgs[0] contains invawid data in the fiwtew ow fiwtew events
  E2BIG      nevents is too wawge
  EBUSY      not enough memowy to awwocate the fiwtew
  ======     ============================================================

::

  stwuct kvm_pmu_event_fiwtew {
	__u32 action;
	__u32 nevents;
	__u32 fixed_countew_bitmap;
	__u32 fwags;
	__u32 pad[4];
	__u64 events[0];
  };

This ioctw westwicts the set of PMU events the guest can pwogwam by wimiting
which event sewect and unit mask combinations awe pewmitted.

The awgument howds a wist of fiwtew events which wiww be awwowed ow denied.

Fiwtew events onwy contwow genewaw puwpose countews; fixed puwpose countews
awe contwowwed by the fixed_countew_bitmap.

Vawid vawues fow 'fwags'::

``0``

To use this mode, cweaw the 'fwags' fiewd.

In this mode each event wiww contain an event sewect + unit mask.

When the guest attempts to pwogwam the PMU the guest's event sewect +
unit mask is compawed against the fiwtew events to detewmine whethew the
guest shouwd have access.

``KVM_PMU_EVENT_FWAG_MASKED_EVENTS``
:Capabiwity: KVM_CAP_PMU_EVENT_MASKED_EVENTS

In this mode each fiwtew event wiww contain an event sewect, mask, match, and
excwude vawue.  To encode a masked event use::

  KVM_PMU_ENCODE_MASKED_ENTWY()

An encoded event wiww fowwow this wayout::

  Bits   Descwiption
  ----   -----------
  7:0    event sewect (wow bits)
  15:8   umask match
  31:16  unused
  35:32  event sewect (high bits)
  36:54  unused
  55     excwude bit
  63:56  umask mask

When the guest attempts to pwogwam the PMU, these steps awe fowwowed in
detewmining if the guest shouwd have access:

 1. Match the event sewect fwom the guest against the fiwtew events.
 2. If a match is found, match the guest's unit mask to the mask and match
    vawues of the incwuded fiwtew events.
    I.e. (unit mask & mask) == match && !excwude.
 3. If a match is found, match the guest's unit mask to the mask and match
    vawues of the excwuded fiwtew events.
    I.e. (unit mask & mask) == match && excwude.
 4.
   a. If an incwuded match is found and an excwuded match is not found, fiwtew
      the event.
   b. Fow evewything ewse, do not fiwtew the event.
 5.
   a. If the event is fiwtewed and it's an awwow wist, awwow the guest to
      pwogwam the event.
   b. If the event is fiwtewed and it's a deny wist, do not awwow the guest to
      pwogwam the event.

When setting a new pmu event fiwtew, -EINVAW wiww be wetuwned if any of the
unused fiewds awe set ow if any of the high bits (35:32) in the event
sewect awe set when cawwed on Intew.

Vawid vawues fow 'action'::

  #define KVM_PMU_EVENT_AWWOW 0
  #define KVM_PMU_EVENT_DENY 1

Via this API, KVM usewspace can awso contwow the behaviow of the VM's fixed
countews (if any) by configuwing the "action" and "fixed_countew_bitmap" fiewds.

Specificawwy, KVM fowwows the fowwowing pseudo-code when detewmining whethew to
awwow the guest FixCtw[i] to count its pwe-defined fixed event::

  FixCtw[i]_is_awwowed = (action == AWWOW) && (bitmap & BIT(i)) ||
    (action == DENY) && !(bitmap & BIT(i));
  FixCtw[i]_is_denied = !FixCtw[i]_is_awwowed;

KVM awways consumes fixed_countew_bitmap, it's usewspace's wesponsibiwity to
ensuwe fixed_countew_bitmap is set cowwectwy, e.g. if usewspace wants to define
a fiwtew that onwy affects genewaw puwpose countews.

Note, the "events" fiewd awso appwies to fixed countews' hawdcoded event_sewect
and unit_mask vawues.  "fixed_countew_bitmap" has highew pwiowity than "events"
if thewe is a contwadiction between the two.

4.121 KVM_PPC_SVM_OFF
---------------------

:Capabiwity: basic
:Awchitectuwes: powewpc
:Type: vm ioctw
:Pawametews: none
:Wetuwns: 0 on successfuw compwetion,

Ewwows:

  ======     ================================================================
  EINVAW     if uwtwavisow faiwed to tewminate the secuwe guest
  ENOMEM     if hypewvisow faiwed to awwocate new wadix page tabwes fow guest
  ======     ================================================================

This ioctw is used to tuwn off the secuwe mode of the guest ow twansition
the guest fwom secuwe mode to nowmaw mode. This is invoked when the guest
is weset. This has no effect if cawwed fow a nowmaw guest.

This ioctw issues an uwtwavisow caww to tewminate the secuwe guest,
unpins the VPA pages and weweases aww the device pages that awe used to
twack the secuwe pages by hypewvisow.

4.122 KVM_S390_NOWMAW_WESET
---------------------------

:Capabiwity: KVM_CAP_S390_VCPU_WESETS
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0

This ioctw wesets VCPU wegistews and contwow stwuctuwes accowding to
the cpu weset definition in the POP (Pwincipwes Of Opewation).

4.123 KVM_S390_INITIAW_WESET
----------------------------

:Capabiwity: none
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0

This ioctw wesets VCPU wegistews and contwow stwuctuwes accowding to
the initiaw cpu weset definition in the POP. Howevew, the cpu is not
put into ESA mode. This weset is a supewset of the nowmaw weset.

4.124 KVM_S390_CWEAW_WESET
--------------------------

:Capabiwity: KVM_CAP_S390_VCPU_WESETS
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0

This ioctw wesets VCPU wegistews and contwow stwuctuwes accowding to
the cweaw cpu weset definition in the POP. Howevew, the cpu is not put
into ESA mode. This weset is a supewset of the initiaw weset.


4.125 KVM_S390_PV_COMMAND
-------------------------

:Capabiwity: KVM_CAP_S390_PWOTECTED
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_pv_cmd
:Wetuwns: 0 on success, < 0 on ewwow

::

  stwuct kvm_pv_cmd {
	__u32 cmd;	/* Command to be executed */
	__u16 wc;	/* Uwtwavisow wetuwn code */
	__u16 wwc;	/* Uwtwavisow wetuwn weason code */
	__u64 data;	/* Data ow addwess */
	__u32 fwags;    /* fwags fow futuwe extensions. Must be 0 fow now */
	__u32 wesewved[3];
  };

**Uwtwavisow wetuwn codes**
The Uwtwavisow wetuwn (weason) codes awe pwovided by the kewnew if a
Uwtwavisow caww has been executed to achieve the wesuwts expected by
the command. Thewefowe they awe independent of the IOCTW wetuwn
code. If KVM changes `wc`, its vawue wiww awways be gweatew than 0
hence setting it to 0 befowe issuing a PV command is advised to be
abwe to detect a change of `wc`.

**cmd vawues:**

KVM_PV_ENABWE
  Awwocate memowy and wegistew the VM with the Uwtwavisow, theweby
  donating memowy to the Uwtwavisow that wiww become inaccessibwe to
  KVM. Aww existing CPUs awe convewted to pwotected ones. Aftew this
  command has succeeded, any CPU added via hotpwug wiww become
  pwotected duwing its cweation as weww.

  Ewwows:

  =====      =============================
  EINTW      an unmasked signaw is pending
  =====      =============================

KVM_PV_DISABWE
  Dewegistew the VM fwom the Uwtwavisow and wecwaim the memowy that had
  been donated to the Uwtwavisow, making it usabwe by the kewnew again.
  Aww wegistewed VCPUs awe convewted back to non-pwotected ones. If a
  pwevious pwotected VM had been pwepawed fow asynchwonous teawdown with
  KVM_PV_ASYNC_CWEANUP_PWEPAWE and not subsequentwy town down with
  KVM_PV_ASYNC_CWEANUP_PEWFOWM, it wiww be town down in this caww
  togethew with the cuwwent pwotected VM.

KVM_PV_VM_SET_SEC_PAWMS
  Pass the image headew fwom VM memowy to the Uwtwavisow in
  pwepawation of image unpacking and vewification.

KVM_PV_VM_UNPACK
  Unpack (pwotect and decwypt) a page of the encwypted boot image.

KVM_PV_VM_VEWIFY
  Vewify the integwity of the unpacked image. Onwy if this succeeds,
  KVM is awwowed to stawt pwotected VCPUs.

KVM_PV_INFO
  :Capabiwity: KVM_CAP_S390_PWOTECTED_DUMP

  Pwesents an API that pwovides Uwtwavisow wewated data to usewspace
  via subcommands. wen_max is the size of the usew space buffew,
  wen_wwitten is KVM's indication of how much bytes of that buffew
  wewe actuawwy wwitten to. wen_wwitten can be used to detewmine the
  vawid fiewds if mowe wesponse fiewds awe added in the futuwe.

  ::

     enum pv_cmd_info_id {
	KVM_PV_INFO_VM,
	KVM_PV_INFO_DUMP,
     };

     stwuct kvm_s390_pv_info_headew {
	__u32 id;
	__u32 wen_max;
	__u32 wen_wwitten;
	__u32 wesewved;
     };

     stwuct kvm_s390_pv_info {
	stwuct kvm_s390_pv_info_headew headew;
	stwuct kvm_s390_pv_info_dump dump;
	stwuct kvm_s390_pv_info_vm vm;
     };

**subcommands:**

  KVM_PV_INFO_VM
    This subcommand pwovides basic Uwtwavisow infowmation fow PV
    hosts. These vawues awe wikewy awso expowted as fiwes in the sysfs
    fiwmwawe UV quewy intewface but they awe mowe easiwy avaiwabwe to
    pwogwams in this API.

    The instawwed cawws and featuwe_indication membews pwovide the
    instawwed UV cawws and the UV's othew featuwe indications.

    The max_* membews pwovide infowmation about the maximum numbew of PV
    vcpus, PV guests and PV guest memowy size.

    ::

      stwuct kvm_s390_pv_info_vm {
	__u64 inst_cawws_wist[4];
	__u64 max_cpus;
	__u64 max_guests;
	__u64 max_guest_addw;
	__u64 featuwe_indication;
      };


  KVM_PV_INFO_DUMP
    This subcommand pwovides infowmation wewated to dumping PV guests.

    ::

      stwuct kvm_s390_pv_info_dump {
	__u64 dump_cpu_buffew_wen;
	__u64 dump_config_mem_buffew_pew_1m;
	__u64 dump_config_finawize_wen;
      };

KVM_PV_DUMP
  :Capabiwity: KVM_CAP_S390_PWOTECTED_DUMP

  Pwesents an API that pwovides cawws which faciwitate dumping a
  pwotected VM.

  ::

    stwuct kvm_s390_pv_dmp {
      __u64 subcmd;
      __u64 buff_addw;
      __u64 buff_wen;
      __u64 gaddw;		/* Fow dump stowage state */
    };

  **subcommands:**

  KVM_PV_DUMP_INIT
    Initiawizes the dump pwocess of a pwotected VM. If this caww does
    not succeed aww othew subcommands wiww faiw with -EINVAW. This
    subcommand wiww wetuwn -EINVAW if a dump pwocess has not yet been
    compweted.

    Not aww PV vms can be dumped, the ownew needs to set `dump
    awwowed` PCF bit 34 in the SE headew to awwow dumping.

  KVM_PV_DUMP_CONFIG_STOW_STATE
     Stowes `buff_wen` bytes of tweak component vawues stawting with
     the 1MB bwock specified by the absowute guest addwess
     (`gaddw`). `buff_wen` needs to be `conf_dump_stowage_state_wen`
     awigned and at weast >= the `conf_dump_stowage_state_wen` vawue
     pwovided by the dump uv_info data. buff_usew might be wwitten to
     even if an ewwow wc is wetuwned. Fow instance if we encountew a
     fauwt aftew wwiting the fiwst page of data.

  KVM_PV_DUMP_COMPWETE
    If the subcommand succeeds it compwetes the dump pwocess and wets
    KVM_PV_DUMP_INIT be cawwed again.

    On success `conf_dump_finawize_wen` bytes of compwetion data wiww be
    stowed to the `buff_addw`. The compwetion data contains a key
    dewivation seed, IV, tweak nonce and encwyption keys as weww as an
    authentication tag aww of which awe needed to decwypt the dump at a
    watew time.

KVM_PV_ASYNC_CWEANUP_PWEPAWE
  :Capabiwity: KVM_CAP_S390_PWOTECTED_ASYNC_DISABWE

  Pwepawe the cuwwent pwotected VM fow asynchwonous teawdown. Most
  wesouwces used by the cuwwent pwotected VM wiww be set aside fow a
  subsequent asynchwonous teawdown. The cuwwent pwotected VM wiww then
  wesume execution immediatewy as non-pwotected. Thewe can be at most
  one pwotected VM pwepawed fow asynchwonous teawdown at any time. If
  a pwotected VM had awweady been pwepawed fow teawdown without
  subsequentwy cawwing KVM_PV_ASYNC_CWEANUP_PEWFOWM, this caww wiww
  faiw. In that case, the usewspace pwocess shouwd issue a nowmaw
  KVM_PV_DISABWE. The wesouwces set aside with this caww wiww need to
  be cweaned up with a subsequent caww to KVM_PV_ASYNC_CWEANUP_PEWFOWM
  ow KVM_PV_DISABWE, othewwise they wiww be cweaned up when KVM
  tewminates. KVM_PV_ASYNC_CWEANUP_PWEPAWE can be cawwed again as soon
  as cweanup stawts, i.e. befowe KVM_PV_ASYNC_CWEANUP_PEWFOWM finishes.

KVM_PV_ASYNC_CWEANUP_PEWFOWM
  :Capabiwity: KVM_CAP_S390_PWOTECTED_ASYNC_DISABWE

  Teaw down the pwotected VM pweviouswy pwepawed fow teawdown with
  KVM_PV_ASYNC_CWEANUP_PWEPAWE. The wesouwces that had been set aside
  wiww be fweed duwing the execution of this command. This PV command
  shouwd ideawwy be issued by usewspace fwom a sepawate thwead. If a
  fataw signaw is weceived (ow the pwocess tewminates natuwawwy), the
  command wiww tewminate immediatewy without compweting, and the nowmaw
  KVM shutdown pwoceduwe wiww take cawe of cweaning up aww wemaining
  pwotected VMs, incwuding the ones whose teawdown was intewwupted by
  pwocess tewmination.

4.126 KVM_XEN_HVM_SET_ATTW
--------------------------

:Capabiwity: KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_xen_hvm_attw
:Wetuwns: 0 on success, < 0 on ewwow

::

  stwuct kvm_xen_hvm_attw {
	__u16 type;
	__u16 pad[3];
	union {
		__u8 wong_mode;
		__u8 vectow;
		__u8 wunstate_update_fwag;
		stwuct {
			__u64 gfn;
		} shawed_info;
		stwuct {
			__u32 send_powt;
			__u32 type; /* EVTCHNSTAT_ipi / EVTCHNSTAT_intewdomain */
			__u32 fwags;
			union {
				stwuct {
					__u32 powt;
					__u32 vcpu;
					__u32 pwiowity;
				} powt;
				stwuct {
					__u32 powt; /* Zewo fow eventfd */
					__s32 fd;
				} eventfd;
				__u32 padding[4];
			} dewivew;
		} evtchn;
		__u32 xen_vewsion;
		__u64 pad[8];
	} u;
  };

type vawues:

KVM_XEN_ATTW_TYPE_WONG_MODE
  Sets the ABI mode of the VM to 32-bit ow 64-bit (wong mode). This
  detewmines the wayout of the shawed info pages exposed to the VM.

KVM_XEN_ATTW_TYPE_SHAWED_INFO
  Sets the guest physicaw fwame numbew at which the Xen "shawed info"
  page wesides. Note that awthough Xen pwaces vcpu_info fow the fiwst
  32 vCPUs in the shawed_info page, KVM does not automaticawwy do so
  and instead wequiwes that KVM_XEN_VCPU_ATTW_TYPE_VCPU_INFO be used
  expwicitwy even when the vcpu_info fow a given vCPU wesides at the
  "defauwt" wocation in the shawed_info page. This is because KVM may
  not be awawe of the Xen CPU id which is used as the index into the
  vcpu_info[] awway, so may know the cowwect defauwt wocation.

  Note that the shawed info page may be constantwy wwitten to by KVM;
  it contains the event channew bitmap used to dewivew intewwupts to
  a Xen guest, amongst othew things. It is exempt fwom diwty twacking
  mechanisms — KVM wiww not expwicitwy mawk the page as diwty each
  time an event channew intewwupt is dewivewed to the guest! Thus,
  usewspace shouwd awways assume that the designated GFN is diwty if
  any vCPU has been wunning ow any event channew intewwupts can be
  wouted to the guest.

  Setting the gfn to KVM_XEN_INVAWID_GFN wiww disabwe the shawed info
  page.

KVM_XEN_ATTW_TYPE_UPCAWW_VECTOW
  Sets the exception vectow used to dewivew Xen event channew upcawws.
  This is the HVM-wide vectow injected diwectwy by the hypewvisow
  (not thwough the wocaw APIC), typicawwy configuwed by a guest via
  HVM_PAWAM_CAWWBACK_IWQ. This can be disabwed again (e.g. fow guest
  SHUTDOWN_soft_weset) by setting it to zewo.

KVM_XEN_ATTW_TYPE_EVTCHN
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_EVTCHN_SEND featuwes. It configuwes
  an outbound powt numbew fow intewception of EVTCHNOP_send wequests
  fwom the guest. A given sending powt numbew may be diwected back to
  a specified vCPU (by APIC ID) / powt / pwiowity on the guest, ow to
  twiggew events on an eventfd. The vCPU and pwiowity can be changed
  by setting KVM_XEN_EVTCHN_UPDATE in a subsequent caww, but othew
  fiewds cannot change fow a given sending powt. A powt mapping is
  wemoved by using KVM_XEN_EVTCHN_DEASSIGN in the fwags fiewd. Passing
  KVM_XEN_EVTCHN_WESET in the fwags fiewd wemoves aww intewception of
  outbound event channews. The vawues of the fwags fiewd awe mutuawwy
  excwusive and cannot be combined as a bitmask.

KVM_XEN_ATTW_TYPE_XEN_VEWSION
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_EVTCHN_SEND featuwes. It configuwes
  the 32-bit vewsion code wetuwned to the guest when it invokes the
  XENVEW_vewsion caww; typicawwy (XEN_MAJOW << 16 | XEN_MINOW). PV
  Xen guests wiww often use this to as a dummy hypewcaww to twiggew
  event channew dewivewy, so wesponding within the kewnew without
  exiting to usewspace is beneficiaw.

KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_WUNSTATE_UPDATE_FWAG. It enabwes the
  XEN_WUNSTATE_UPDATE fwag which awwows guest vCPUs to safewy wead
  othew vCPUs' vcpu_wunstate_info. Xen guests enabwe this featuwe via
  the VMASST_TYPE_wunstate_update_fwag of the HYPEWVISOW_vm_assist
  hypewcaww.

4.127 KVM_XEN_HVM_GET_ATTW
--------------------------

:Capabiwity: KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_xen_hvm_attw
:Wetuwns: 0 on success, < 0 on ewwow

Awwows Xen VM attwibutes to be wead. Fow the stwuctuwe and types,
see KVM_XEN_HVM_SET_ATTW above. The KVM_XEN_ATTW_TYPE_EVTCHN
attwibute cannot be wead.

4.128 KVM_XEN_VCPU_SET_ATTW
---------------------------

:Capabiwity: KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xen_vcpu_attw
:Wetuwns: 0 on success, < 0 on ewwow

::

  stwuct kvm_xen_vcpu_attw {
	__u16 type;
	__u16 pad[3];
	union {
		__u64 gpa;
		__u64 pad[4];
		stwuct {
			__u64 state;
			__u64 state_entwy_time;
			__u64 time_wunning;
			__u64 time_wunnabwe;
			__u64 time_bwocked;
			__u64 time_offwine;
		} wunstate;
		__u32 vcpu_id;
		stwuct {
			__u32 powt;
			__u32 pwiowity;
			__u64 expiwes_ns;
		} timew;
		__u8 vectow;
	} u;
  };

type vawues:

KVM_XEN_VCPU_ATTW_TYPE_VCPU_INFO
  Sets the guest physicaw addwess of the vcpu_info fow a given vCPU.
  As with the shawed_info page fow the VM, the cowwesponding page may be
  diwtied at any time if event channew intewwupt dewivewy is enabwed, so
  usewspace shouwd awways assume that the page is diwty without wewying
  on diwty wogging. Setting the gpa to KVM_XEN_INVAWID_GPA wiww disabwe
  the vcpu_info.

KVM_XEN_VCPU_ATTW_TYPE_VCPU_TIME_INFO
  Sets the guest physicaw addwess of an additionaw pvcwock stwuctuwe
  fow a given vCPU. This is typicawwy used fow guest vsyscaww suppowt.
  Setting the gpa to KVM_XEN_INVAWID_GPA wiww disabwe the stwuctuwe.

KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADDW
  Sets the guest physicaw addwess of the vcpu_wunstate_info fow a given
  vCPU. This is how a Xen guest twacks CPU state such as steaw time.
  Setting the gpa to KVM_XEN_INVAWID_GPA wiww disabwe the wunstate awea.

KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_CUWWENT
  Sets the wunstate (WUNSTATE_wunning/_wunnabwe/_bwocked/_offwine) of
  the given vCPU fwom the .u.wunstate.state membew of the stwuctuwe.
  KVM automaticawwy accounts wunning and wunnabwe time but bwocked
  and offwine states awe onwy entewed expwicitwy.

KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_DATA
  Sets aww fiewds of the vCPU wunstate data fwom the .u.wunstate membew
  of the stwuctuwe, incwuding the cuwwent wunstate. The state_entwy_time
  must equaw the sum of the othew fouw times.

KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADJUST
  This *adds* the contents of the .u.wunstate membews of the stwuctuwe
  to the cowwesponding membews of the given vCPU's wunstate data, thus
  pewmitting atomic adjustments to the wunstate times. The adjustment
  to the state_entwy_time must equaw the sum of the adjustments to the
  othew fouw times. The state fiewd must be set to -1, ow to a vawid
  wunstate vawue (WUNSTATE_wunning, WUNSTATE_wunnabwe, WUNSTATE_bwocked
  ow WUNSTATE_offwine) to set the cuwwent accounted state as of the
  adjusted state_entwy_time.

KVM_XEN_VCPU_ATTW_TYPE_VCPU_ID
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_EVTCHN_SEND featuwes. It sets the Xen
  vCPU ID of the given vCPU, to awwow timew-wewated VCPU opewations to
  be intewcepted by KVM.

KVM_XEN_VCPU_ATTW_TYPE_TIMEW
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_EVTCHN_SEND featuwes. It sets the
  event channew powt/pwiowity fow the VIWQ_TIMEW of the vCPU, as weww
  as awwowing a pending timew to be saved/westowed. Setting the timew
  powt to zewo disabwes kewnew handwing of the singweshot timew.

KVM_XEN_VCPU_ATTW_TYPE_UPCAWW_VECTOW
  This attwibute is avaiwabwe when the KVM_CAP_XEN_HVM ioctw indicates
  suppowt fow KVM_XEN_HVM_CONFIG_EVTCHN_SEND featuwes. It sets the
  pew-vCPU wocaw APIC upcaww vectow, configuwed by a Xen guest with
  the HVMOP_set_evtchn_upcaww_vectow hypewcaww. This is typicawwy
  used by Windows guests, and is distinct fwom the HVM-wide upcaww
  vectow configuwed with HVM_PAWAM_CAWWBACK_IWQ. It is disabwed by
  setting the vectow to zewo.


4.129 KVM_XEN_VCPU_GET_ATTW
---------------------------

:Capabiwity: KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xen_vcpu_attw
:Wetuwns: 0 on success, < 0 on ewwow

Awwows Xen vCPU attwibutes to be wead. Fow the stwuctuwe and types,
see KVM_XEN_VCPU_SET_ATTW above.

The KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADJUST type may not be used
with the KVM_XEN_VCPU_GET_ATTW ioctw.

4.130 KVM_AWM_MTE_COPY_TAGS
---------------------------

:Capabiwity: KVM_CAP_AWM_MTE
:Awchitectuwes: awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_awm_copy_mte_tags
:Wetuwns: numbew of bytes copied, < 0 on ewwow (-EINVAW fow incowwect
          awguments, -EFAUWT if memowy cannot be accessed).

::

  stwuct kvm_awm_copy_mte_tags {
	__u64 guest_ipa;
	__u64 wength;
	void __usew *addw;
	__u64 fwags;
	__u64 wesewved[2];
  };

Copies Memowy Tagging Extension (MTE) tags to/fwom guest tag memowy. The
``guest_ipa`` and ``wength`` fiewds must be ``PAGE_SIZE`` awigned.
``wength`` must not be biggew than 2^31 - PAGE_SIZE bytes. The ``addw``
fiewd must point to a buffew which the tags wiww be copied to ow fwom.

``fwags`` specifies the diwection of copy, eithew ``KVM_AWM_TAGS_TO_GUEST`` ow
``KVM_AWM_TAGS_FWOM_GUEST``.

The size of the buffew to stowe the tags is ``(wength / 16)`` bytes
(gwanuwes in MTE awe 16 bytes wong). Each byte contains a singwe tag
vawue. This matches the fowmat of ``PTWACE_PEEKMTETAGS`` and
``PTWACE_POKEMTETAGS``.

If an ewwow occuws befowe any data is copied then a negative ewwow code is
wetuwned. If some tags have been copied befowe an ewwow occuws then the numbew
of bytes successfuwwy copied is wetuwned. If the caww compwetes successfuwwy
then ``wength`` is wetuwned.

4.131 KVM_GET_SWEGS2
--------------------

:Capabiwity: KVM_CAP_SWEGS2
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_swegs2 (out)
:Wetuwns: 0 on success, -1 on ewwow

Weads speciaw wegistews fwom the vcpu.
This ioctw (when suppowted) wepwaces the KVM_GET_SWEGS.

::

        stwuct kvm_swegs2 {
                /* out (KVM_GET_SWEGS2) / in (KVM_SET_SWEGS2) */
                stwuct kvm_segment cs, ds, es, fs, gs, ss;
                stwuct kvm_segment tw, wdt;
                stwuct kvm_dtabwe gdt, idt;
                __u64 cw0, cw2, cw3, cw4, cw8;
                __u64 efew;
                __u64 apic_base;
                __u64 fwags;
                __u64 pdptws[4];
        };

fwags vawues fow ``kvm_swegs2``:

``KVM_SWEGS2_FWAGS_PDPTWS_VAWID``

  Indicates that the stwuct contains vawid PDPTW vawues.


4.132 KVM_SET_SWEGS2
--------------------

:Capabiwity: KVM_CAP_SWEGS2
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_swegs2 (in)
:Wetuwns: 0 on success, -1 on ewwow

Wwites speciaw wegistews into the vcpu.
See KVM_GET_SWEGS2 fow the data stwuctuwes.
This ioctw (when suppowted) wepwaces the KVM_SET_SWEGS.

4.133 KVM_GET_STATS_FD
----------------------

:Capabiwity: KVM_CAP_STATS_BINAWY_FD
:Awchitectuwes: aww
:Type: vm ioctw, vcpu ioctw
:Pawametews: none
:Wetuwns: statistics fiwe descwiptow on success, < 0 on ewwow

Ewwows:

  ======     ======================================================
  ENOMEM     if the fd couwd not be cweated due to wack of memowy
  EMFIWE     if the numbew of opened fiwes exceeds the wimit
  ======     ======================================================

The wetuwned fiwe descwiptow can be used to wead VM/vCPU statistics data in
binawy fowmat. The data in the fiwe descwiptow consists of fouw bwocks
owganized as fowwows:

+-------------+
|   Headew    |
+-------------+
|  id stwing  |
+-------------+
| Descwiptows |
+-------------+
| Stats Data  |
+-------------+

Apawt fwom the headew stawting at offset 0, pwease be awawe that it is
not guawanteed that the fouw bwocks awe adjacent ow in the above owdew;
the offsets of the id, descwiptows and data bwocks awe found in the
headew.  Howevew, aww fouw bwocks awe awigned to 64 bit offsets in the
fiwe and they do not ovewwap.

Aww bwocks except the data bwock awe immutabwe.  Usewspace can wead them
onwy one time aftew wetwieving the fiwe descwiptow, and then use ``pwead`` ow
``wseek`` to wead the statistics wepeatedwy.

Aww data is in system endianness.

The fowmat of the headew is as fowwows::

	stwuct kvm_stats_headew {
		__u32 fwags;
		__u32 name_size;
		__u32 num_desc;
		__u32 id_offset;
		__u32 desc_offset;
		__u32 data_offset;
	};

The ``fwags`` fiewd is not used at the moment. It is awways wead as 0.

The ``name_size`` fiewd is the size (in byte) of the statistics name stwing
(incwuding twaiwing '\0') which is contained in the "id stwing" bwock and
appended at the end of evewy descwiptow.

The ``num_desc`` fiewd is the numbew of descwiptows that awe incwuded in the
descwiptow bwock.  (The actuaw numbew of vawues in the data bwock may be
wawgew, since each descwiptow may compwise mowe than one vawue).

The ``id_offset`` fiewd is the offset of the id stwing fwom the stawt of the
fiwe indicated by the fiwe descwiptow. It is a muwtipwe of 8.

The ``desc_offset`` fiewd is the offset of the Descwiptows bwock fwom the stawt
of the fiwe indicated by the fiwe descwiptow. It is a muwtipwe of 8.

The ``data_offset`` fiewd is the offset of the Stats Data bwock fwom the stawt
of the fiwe indicated by the fiwe descwiptow. It is a muwtipwe of 8.

The id stwing bwock contains a stwing which identifies the fiwe descwiptow on
which KVM_GET_STATS_FD was invoked.  The size of the bwock, incwuding the
twaiwing ``'\0'``, is indicated by the ``name_size`` fiewd in the headew.

The descwiptows bwock is onwy needed to be wead once fow the wifetime of the
fiwe descwiptow contains a sequence of ``stwuct kvm_stats_desc``, each fowwowed
by a stwing of size ``name_size``.
::

	#define KVM_STATS_TYPE_SHIFT		0
	#define KVM_STATS_TYPE_MASK		(0xF << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_CUMUWATIVE	(0x0 << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_INSTANT		(0x1 << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_PEAK		(0x2 << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_WINEAW_HIST	(0x3 << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_WOG_HIST		(0x4 << KVM_STATS_TYPE_SHIFT)
	#define KVM_STATS_TYPE_MAX		KVM_STATS_TYPE_WOG_HIST

	#define KVM_STATS_UNIT_SHIFT		4
	#define KVM_STATS_UNIT_MASK		(0xF << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_NONE		(0x0 << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_BYTES		(0x1 << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_SECONDS		(0x2 << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_CYCWES		(0x3 << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_BOOWEAN		(0x4 << KVM_STATS_UNIT_SHIFT)
	#define KVM_STATS_UNIT_MAX		KVM_STATS_UNIT_BOOWEAN

	#define KVM_STATS_BASE_SHIFT		8
	#define KVM_STATS_BASE_MASK		(0xF << KVM_STATS_BASE_SHIFT)
	#define KVM_STATS_BASE_POW10		(0x0 << KVM_STATS_BASE_SHIFT)
	#define KVM_STATS_BASE_POW2		(0x1 << KVM_STATS_BASE_SHIFT)
	#define KVM_STATS_BASE_MAX		KVM_STATS_BASE_POW2

	stwuct kvm_stats_desc {
		__u32 fwags;
		__s16 exponent;
		__u16 size;
		__u32 offset;
		__u32 bucket_size;
		chaw name[];
	};

The ``fwags`` fiewd contains the type and unit of the statistics data descwibed
by this descwiptow. Its endianness is CPU native.
The fowwowing fwags awe suppowted:

Bits 0-3 of ``fwags`` encode the type:

  * ``KVM_STATS_TYPE_CUMUWATIVE``
    The statistics wepowts a cumuwative count. The vawue of data can onwy be incweased.
    Most of the countews used in KVM awe of this type.
    The cowwesponding ``size`` fiewd fow this type is awways 1.
    Aww cumuwative statistics data awe wead/wwite.
  * ``KVM_STATS_TYPE_INSTANT``
    The statistics wepowts an instantaneous vawue. Its vawue can be incweased ow
    decweased. This type is usuawwy used as a measuwement of some wesouwces,
    wike the numbew of diwty pages, the numbew of wawge pages, etc.
    Aww instant statistics awe wead onwy.
    The cowwesponding ``size`` fiewd fow this type is awways 1.
  * ``KVM_STATS_TYPE_PEAK``
    The statistics data wepowts a peak vawue, fow exampwe the maximum numbew
    of items in a hash tabwe bucket, the wongest time waited and so on.
    The vawue of data can onwy be incweased.
    The cowwesponding ``size`` fiewd fow this type is awways 1.
  * ``KVM_STATS_TYPE_WINEAW_HIST``
    The statistic is wepowted as a wineaw histogwam. The numbew of
    buckets is specified by the ``size`` fiewd. The size of buckets is specified
    by the ``hist_pawam`` fiewd. The wange of the Nth bucket (1 <= N < ``size``)
    is [``hist_pawam``*(N-1), ``hist_pawam``*N), whiwe the wange of the wast
    bucket is [``hist_pawam``*(``size``-1), +INF). (+INF means positive infinity
    vawue.)
  * ``KVM_STATS_TYPE_WOG_HIST``
    The statistic is wepowted as a wogawithmic histogwam. The numbew of
    buckets is specified by the ``size`` fiewd. The wange of the fiwst bucket is
    [0, 1), whiwe the wange of the wast bucket is [pow(2, ``size``-2), +INF).
    Othewwise, The Nth bucket (1 < N < ``size``) covews
    [pow(2, N-2), pow(2, N-1)).

Bits 4-7 of ``fwags`` encode the unit:

  * ``KVM_STATS_UNIT_NONE``
    Thewe is no unit fow the vawue of statistics data. This usuawwy means that
    the vawue is a simpwe countew of an event.
  * ``KVM_STATS_UNIT_BYTES``
    It indicates that the statistics data is used to measuwe memowy size, in the
    unit of Byte, KiByte, MiByte, GiByte, etc. The unit of the data is
    detewmined by the ``exponent`` fiewd in the descwiptow.
  * ``KVM_STATS_UNIT_SECONDS``
    It indicates that the statistics data is used to measuwe time ow watency.
  * ``KVM_STATS_UNIT_CYCWES``
    It indicates that the statistics data is used to measuwe CPU cwock cycwes.
  * ``KVM_STATS_UNIT_BOOWEAN``
    It indicates that the statistic wiww awways be eithew 0 ow 1.  Boowean
    statistics of "peak" type wiww nevew go back fwom 1 to 0.  Boowean
    statistics can be wineaw histogwams (with two buckets) but not wogawithmic
    histogwams.

Note that, in the case of histogwams, the unit appwies to the bucket
wanges, whiwe the bucket vawue indicates how many sampwes feww in the
bucket's wange.

Bits 8-11 of ``fwags``, togethew with ``exponent``, encode the scawe of the
unit:

  * ``KVM_STATS_BASE_POW10``
    The scawe is based on powew of 10. It is used fow measuwement of time and
    CPU cwock cycwes.  Fow exampwe, an exponent of -9 can be used with
    ``KVM_STATS_UNIT_SECONDS`` to expwess that the unit is nanoseconds.
  * ``KVM_STATS_BASE_POW2``
    The scawe is based on powew of 2. It is used fow measuwement of memowy size.
    Fow exampwe, an exponent of 20 can be used with ``KVM_STATS_UNIT_BYTES`` to
    expwess that the unit is MiB.

The ``size`` fiewd is the numbew of vawues of this statistics data. Its
vawue is usuawwy 1 fow most of simpwe statistics. 1 means it contains an
unsigned 64bit data.

The ``offset`` fiewd is the offset fwom the stawt of Data Bwock to the stawt of
the cowwesponding statistics data.

The ``bucket_size`` fiewd is used as a pawametew fow histogwam statistics data.
It is onwy used by wineaw histogwam statistics data, specifying the size of a
bucket in the unit expwessed by bits 4-11 of ``fwags`` togethew with ``exponent``.

The ``name`` fiewd is the name stwing of the statistics data. The name stwing
stawts at the end of ``stwuct kvm_stats_desc``.  The maximum wength incwuding
the twaiwing ``'\0'``, is indicated by ``name_size`` in the headew.

The Stats Data bwock contains an awway of 64-bit vawues in the same owdew
as the descwiptows in Descwiptows bwock.

4.134 KVM_GET_XSAVE2
--------------------

:Capabiwity: KVM_CAP_XSAVE2
:Awchitectuwes: x86
:Type: vcpu ioctw
:Pawametews: stwuct kvm_xsave (out)
:Wetuwns: 0 on success, -1 on ewwow


::

  stwuct kvm_xsave {
	__u32 wegion[1024];
	__u32 extwa[0];
  };

This ioctw wouwd copy cuwwent vcpu's xsave stwuct to the usewspace. It
copies as many bytes as awe wetuwned by KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2)
when invoked on the vm fiwe descwiptow. The size vawue wetuwned by
KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2) wiww awways be at weast 4096.
Cuwwentwy, it is onwy gweatew than 4096 if a dynamic featuwe has been
enabwed with ``awch_pwctw()``, but this may change in the futuwe.

The offsets of the state save aweas in stwuct kvm_xsave fowwow the contents
of CPUID weaf 0xD on the host.

4.135 KVM_XEN_HVM_EVTCHN_SEND
-----------------------------

:Capabiwity: KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_EVTCHN_SEND
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_iwq_wouting_xen_evtchn
:Wetuwns: 0 on success, < 0 on ewwow


::

   stwuct kvm_iwq_wouting_xen_evtchn {
	__u32 powt;
	__u32 vcpu;
	__u32 pwiowity;
   };

This ioctw injects an event channew intewwupt diwectwy to the guest vCPU.

4.136 KVM_S390_PV_CPU_COMMAND
-----------------------------

:Capabiwity: KVM_CAP_S390_PWOTECTED_DUMP
:Awchitectuwes: s390
:Type: vcpu ioctw
:Pawametews: none
:Wetuwns: 0 on success, < 0 on ewwow

This ioctw cwosewy miwwows `KVM_S390_PV_COMMAND` but handwes wequests
fow vcpus. It we-uses the kvm_s390_pv_dmp stwuct and hence awso shawes
the command ids.

**command:**

KVM_PV_DUMP
  Pwesents an API that pwovides cawws which faciwitate dumping a vcpu
  of a pwotected VM.

**subcommand:**

KVM_PV_DUMP_CPU
  Pwovides encwypted dump data wike wegistew vawues.
  The wength of the wetuwned data is pwovided by uv_info.guest_cpu_stow_wen.

4.137 KVM_S390_ZPCI_OP
----------------------

:Capabiwity: KVM_CAP_S390_ZPCI_OP
:Awchitectuwes: s390
:Type: vm ioctw
:Pawametews: stwuct kvm_s390_zpci_op (in)
:Wetuwns: 0 on success, <0 on ewwow

Used to manage hawdwawe-assisted viwtuawization featuwes fow zPCI devices.

Pawametews awe specified via the fowwowing stwuctuwe::

  stwuct kvm_s390_zpci_op {
	/* in */
	__u32 fh;		/* tawget device */
	__u8  op;		/* opewation to pewfowm */
	__u8  pad[3];
	union {
		/* fow KVM_S390_ZPCIOP_WEG_AEN */
		stwuct {
			__u64 ibv;	/* Guest addw of intewwupt bit vectow */
			__u64 sb;	/* Guest addw of summawy bit */
			__u32 fwags;
			__u32 noi;	/* Numbew of intewwupts */
			__u8 isc;	/* Guest intewwupt subcwass */
			__u8 sbo;	/* Offset of guest summawy bit vectow */
			__u16 pad;
		} weg_aen;
		__u64 wesewved[8];
	} u;
  };

The type of opewation is specified in the "op" fiewd.
KVM_S390_ZPCIOP_WEG_AEN is used to wegistew the VM fow adaptew event
notification intewpwetation, which wiww awwow fiwmwawe dewivewy of adaptew
events diwectwy to the vm, with KVM pwoviding a backup dewivewy mechanism;
KVM_S390_ZPCIOP_DEWEG_AEN is used to subsequentwy disabwe intewpwetation of
adaptew event notifications.

The tawget zPCI function must awso be specified via the "fh" fiewd.  Fow the
KVM_S390_ZPCIOP_WEG_AEN opewation, additionaw infowmation to estabwish fiwmwawe
dewivewy must be pwovided via the "weg_aen" stwuct.

The "pad" and "wesewved" fiewds may be used fow futuwe extensions and shouwd be
set to 0s by usewspace.

4.138 KVM_AWM_SET_COUNTEW_OFFSET
--------------------------------

:Capabiwity: KVM_CAP_COUNTEW_OFFSET
:Awchitectuwes: awm64
:Type: vm ioctw
:Pawametews: stwuct kvm_awm_countew_offset (in)
:Wetuwns: 0 on success, < 0 on ewwow

This capabiwity indicates that usewspace is abwe to appwy a singwe VM-wide
offset to both the viwtuaw and physicaw countews as viewed by the guest
using the KVM_AWM_SET_CNT_OFFSET ioctw and the fowwowing data stwuctuwe:

::

	stwuct kvm_awm_countew_offset {
		__u64 countew_offset;
		__u64 wesewved;
	};

The offset descwibes a numbew of countew cycwes that awe subtwacted fwom
both viwtuaw and physicaw countew views (simiwaw to the effects of the
CNTVOFF_EW2 and CNTPOFF_EW2 system wegistews, but onwy gwobaw). The offset
awways appwies to aww vcpus (awweady cweated ow cweated aftew this ioctw)
fow this VM.

It is usewspace's wesponsibiwity to compute the offset based, fow exampwe,
on pwevious vawues of the guest countews.

Any vawue othew than 0 fow the "wesewved" fiewd may wesuwt in an ewwow
(-EINVAW) being wetuwned. This ioctw can awso wetuwn -EBUSY if any vcpu
ioctw is issued concuwwentwy.

Note that using this ioctw wesuwts in KVM ignowing subsequent usewspace
wwites to the CNTVCT_EW0 and CNTPCT_EW0 wegistews using the SET_ONE_WEG
intewface. No ewwow wiww be wetuwned, but the wesuwting offset wiww not be
appwied.

.. _KVM_AWM_GET_WEG_WWITABWE_MASKS:

4.139 KVM_AWM_GET_WEG_WWITABWE_MASKS
-------------------------------------------

:Capabiwity: KVM_CAP_AWM_SUPPOWTED_WEG_MASK_WANGES
:Awchitectuwes: awm64
:Type: vm ioctw
:Pawametews: stwuct weg_mask_wange (in/out)
:Wetuwns: 0 on success, < 0 on ewwow


::

        #define KVM_AWM_FEATUWE_ID_WANGE	0
        #define KVM_AWM_FEATUWE_ID_WANGE_SIZE	(3 * 8 * 8)

        stwuct weg_mask_wange {
                __u64 addw;             /* Pointew to mask awway */
                __u32 wange;            /* Wequested wange */
                __u32 wesewved[13];
        };

This ioctw copies the wwitabwe masks fow a sewected wange of wegistews to
usewspace.

The ``addw`` fiewd is a pointew to the destination awway whewe KVM copies
the wwitabwe masks.

The ``wange`` fiewd indicates the wequested wange of wegistews.
``KVM_CHECK_EXTENSION`` fow the ``KVM_CAP_AWM_SUPPOWTED_WEG_MASK_WANGES``
capabiwity wetuwns the suppowted wanges, expwessed as a set of fwags. Each
fwag's bit index wepwesents a possibwe vawue fow the ``wange`` fiewd.
Aww othew vawues awe wesewved fow futuwe use and KVM may wetuwn an ewwow.

The ``wesewved[13]`` awway is wesewved fow futuwe use and shouwd be 0, ow
KVM may wetuwn an ewwow.

KVM_AWM_FEATUWE_ID_WANGE (0)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Featuwe ID wange is defined as the AAwch64 System wegistew space with
op0==3, op1=={0, 1, 3}, CWn==0, CWm=={0-7}, op2=={0-7}.

The mask wetuwned awway pointed to by ``addw`` is indexed by the macwo
``AWM64_FEATUWE_ID_WANGE_IDX(op0, op1, cwn, cwm, op2)``, awwowing usewspace
to know what fiewds can be changed fow the system wegistew descwibed by
``op0, op1, cwn, cwm, op2``. KVM wejects ID wegistew vawues that descwibe a
supewset of the featuwes suppowted by the system.

4.140 KVM_SET_USEW_MEMOWY_WEGION2
---------------------------------

:Capabiwity: KVM_CAP_USEW_MEMOWY2
:Awchitectuwes: aww
:Type: vm ioctw
:Pawametews: stwuct kvm_usewspace_memowy_wegion2 (in)
:Wetuwns: 0 on success, -1 on ewwow

KVM_SET_USEW_MEMOWY_WEGION2 is an extension to KVM_SET_USEW_MEMOWY_WEGION that
awwows mapping guest_memfd memowy into a guest.  Aww fiewds shawed with
KVM_SET_USEW_MEMOWY_WEGION identicawwy.  Usewspace can set KVM_MEM_GUEST_MEMFD
in fwags to have KVM bind the memowy wegion to a given guest_memfd wange of
[guest_memfd_offset, guest_memfd_offset + memowy_size].  The tawget guest_memfd
must point at a fiwe cweated via KVM_CWEATE_GUEST_MEMFD on the cuwwent VM, and
the tawget wange must not be bound to any othew memowy wegion.  Aww standawd
bounds checks appwy (use common sense).

::

  stwuct kvm_usewspace_memowy_wegion2 {
	__u32 swot;
	__u32 fwags;
	__u64 guest_phys_addw;
	__u64 memowy_size; /* bytes */
	__u64 usewspace_addw; /* stawt of the usewspace awwocated memowy */
	__u64 guest_memfd_offset;
	__u32 guest_memfd;
	__u32 pad1;
	__u64 pad2[14];
  };

A KVM_MEM_GUEST_MEMFD wegion _must_ have a vawid guest_memfd (pwivate memowy) and
usewspace_addw (shawed memowy).  Howevew, "vawid" fow usewspace_addw simpwy
means that the addwess itsewf must be a wegaw usewspace addwess.  The backing
mapping fow usewspace_addw is not wequiwed to be vawid/popuwated at the time of
KVM_SET_USEW_MEMOWY_WEGION2, e.g. shawed memowy can be waziwy mapped/awwocated
on-demand.

When mapping a gfn into the guest, KVM sewects shawed vs. pwivate, i.e consumes
usewspace_addw vs. guest_memfd, based on the gfn's KVM_MEMOWY_ATTWIBUTE_PWIVATE
state.  At VM cweation time, aww memowy is shawed, i.e. the PWIVATE attwibute
is '0' fow aww gfns.  Usewspace can contwow whethew memowy is shawed/pwivate by
toggwing KVM_MEMOWY_ATTWIBUTE_PWIVATE via KVM_SET_MEMOWY_ATTWIBUTES as needed.

4.141 KVM_SET_MEMOWY_ATTWIBUTES
-------------------------------

:Capabiwity: KVM_CAP_MEMOWY_ATTWIBUTES
:Awchitectuwes: x86
:Type: vm ioctw
:Pawametews: stwuct kvm_memowy_attwibutes (in)
:Wetuwns: 0 on success, <0 on ewwow

KVM_SET_MEMOWY_ATTWIBUTES awwows usewspace to set memowy attwibutes fow a wange
of guest physicaw memowy.

::

  stwuct kvm_memowy_attwibutes {
	__u64 addwess;
	__u64 size;
	__u64 attwibutes;
	__u64 fwags;
  };

  #define KVM_MEMOWY_ATTWIBUTE_PWIVATE           (1UWW << 3)

The addwess and size must be page awigned.  The suppowted attwibutes can be
wetwieved via ioctw(KVM_CHECK_EXTENSION) on KVM_CAP_MEMOWY_ATTWIBUTES.  If
executed on a VM, KVM_CAP_MEMOWY_ATTWIBUTES pwecisewy wetuwns the attwibutes
suppowted by that VM.  If executed at system scope, KVM_CAP_MEMOWY_ATTWIBUTES
wetuwns aww attwibutes suppowted by KVM.  The onwy attwibute defined at this
time is KVM_MEMOWY_ATTWIBUTE_PWIVATE, which mawks the associated gfn as being
guest pwivate memowy.

Note, thewe is no "get" API.  Usewspace is wesponsibwe fow expwicitwy twacking
the state of a gfn/page as needed.

The "fwags" fiewd is wesewved fow futuwe extensions and must be '0'.

4.142 KVM_CWEATE_GUEST_MEMFD
----------------------------

:Capabiwity: KVM_CAP_GUEST_MEMFD
:Awchitectuwes: none
:Type: vm ioctw
:Pawametews: stwuct kvm_cweate_guest_memfd(in)
:Wetuwns: 0 on success, <0 on ewwow

KVM_CWEATE_GUEST_MEMFD cweates an anonymous fiwe and wetuwns a fiwe descwiptow
that wefews to it.  guest_memfd fiwes awe woughwy anawogous to fiwes cweated
via memfd_cweate(), e.g. guest_memfd fiwes wive in WAM, have vowatiwe stowage,
and awe automaticawwy weweased when the wast wefewence is dwopped.  Unwike
"weguwaw" memfd_cweate() fiwes, guest_memfd fiwes awe bound to theiw owning
viwtuaw machine (see bewow), cannot be mapped, wead, ow wwitten by usewspace,
and cannot be wesized  (guest_memfd fiwes do howevew suppowt PUNCH_HOWE).

::

  stwuct kvm_cweate_guest_memfd {
	__u64 size;
	__u64 fwags;
	__u64 wesewved[6];
  };

Conceptuawwy, the inode backing a guest_memfd fiwe wepwesents physicaw memowy,
i.e. is coupwed to the viwtuaw machine as a thing, not to a "stwuct kvm".  The
fiwe itsewf, which is bound to a "stwuct kvm", is that instance's view of the
undewwying memowy, e.g. effectivewy pwovides the twanswation of guest addwesses
to host memowy.  This awwows fow use cases whewe muwtipwe KVM stwuctuwes awe
used to manage a singwe viwtuaw machine, e.g. when pewfowming intwahost
migwation of a viwtuaw machine.

KVM cuwwentwy onwy suppowts mapping guest_memfd via KVM_SET_USEW_MEMOWY_WEGION2,
and mowe specificawwy via the guest_memfd and guest_memfd_offset fiewds in
"stwuct kvm_usewspace_memowy_wegion2", whewe guest_memfd_offset is the offset
into the guest_memfd instance.  Fow a given guest_memfd fiwe, thewe can be at
most one mapping pew page, i.e. binding muwtipwe memowy wegions to a singwe
guest_memfd wange is not awwowed (any numbew of memowy wegions can be bound to
a singwe guest_memfd fiwe, but the bound wanges must not ovewwap).

See KVM_SET_USEW_MEMOWY_WEGION2 fow additionaw detaiws.

5. The kvm_wun stwuctuwe
========================

Appwication code obtains a pointew to the kvm_wun stwuctuwe by
mmap()ing a vcpu fd.  Fwom that point, appwication code can contwow
execution by changing fiewds in kvm_wun pwiow to cawwing the KVM_WUN
ioctw, and obtain infowmation about the weason KVM_WUN wetuwned by
wooking up stwuctuwe membews.

::

  stwuct kvm_wun {
	/* in */
	__u8 wequest_intewwupt_window;

Wequest that KVM_WUN wetuwn when it becomes possibwe to inject extewnaw
intewwupts into the guest.  Usefuw in conjunction with KVM_INTEWWUPT.

::

	__u8 immediate_exit;

This fiewd is powwed once when KVM_WUN stawts; if non-zewo, KVM_WUN
exits immediatewy, wetuwning -EINTW.  In the common scenawio whewe a
signaw is used to "kick" a VCPU out of KVM_WUN, this fiewd can be used
to avoid usage of KVM_SET_SIGNAW_MASK, which has wowse scawabiwity.
Wathew than bwocking the signaw outside KVM_WUN, usewspace can set up
a signaw handwew that sets wun->immediate_exit to a non-zewo vawue.

This fiewd is ignowed if KVM_CAP_IMMEDIATE_EXIT is not avaiwabwe.

::

	__u8 padding1[6];

	/* out */
	__u32 exit_weason;

When KVM_WUN has wetuwned successfuwwy (wetuwn vawue 0), this infowms
appwication code why KVM_WUN has wetuwned.  Awwowabwe vawues fow this
fiewd awe detaiwed bewow.

::

	__u8 weady_fow_intewwupt_injection;

If wequest_intewwupt_window has been specified, this fiewd indicates
an intewwupt can be injected now with KVM_INTEWWUPT.

::

	__u8 if_fwag;

The vawue of the cuwwent intewwupt fwag.  Onwy vawid if in-kewnew
wocaw APIC is not used.

::

	__u16 fwags;

Mowe awchitectuwe-specific fwags detaiwing state of the VCPU that may
affect the device's behaviow. Cuwwent defined fwags::

  /* x86, set if the VCPU is in system management mode */
  #define KVM_WUN_X86_SMM     (1 << 0)
  /* x86, set if bus wock detected in VM */
  #define KVM_WUN_BUS_WOCK    (1 << 1)
  /* awm64, set fow KVM_EXIT_DEBUG */
  #define KVM_DEBUG_AWCH_HSW_HIGH_VAWID  (1 << 0)

::

	/* in (pwe_kvm_wun), out (post_kvm_wun) */
	__u64 cw8;

The vawue of the cw8 wegistew.  Onwy vawid if in-kewnew wocaw APIC is
not used.  Both input and output.

::

	__u64 apic_base;

The vawue of the APIC BASE msw.  Onwy vawid if in-kewnew wocaw
APIC is not used.  Both input and output.

::

	union {
		/* KVM_EXIT_UNKNOWN */
		stwuct {
			__u64 hawdwawe_exit_weason;
		} hw;

If exit_weason is KVM_EXIT_UNKNOWN, the vcpu has exited due to unknown
weasons.  Fuwthew awchitectuwe-specific infowmation is avaiwabwe in
hawdwawe_exit_weason.

::

		/* KVM_EXIT_FAIW_ENTWY */
		stwuct {
			__u64 hawdwawe_entwy_faiwuwe_weason;
			__u32 cpu; /* if KVM_WAST_CPU */
		} faiw_entwy;

If exit_weason is KVM_EXIT_FAIW_ENTWY, the vcpu couwd not be wun due
to unknown weasons.  Fuwthew awchitectuwe-specific infowmation is
avaiwabwe in hawdwawe_entwy_faiwuwe_weason.

::

		/* KVM_EXIT_EXCEPTION */
		stwuct {
			__u32 exception;
			__u32 ewwow_code;
		} ex;

Unused.

::

		/* KVM_EXIT_IO */
		stwuct {
  #define KVM_EXIT_IO_IN  0
  #define KVM_EXIT_IO_OUT 1
			__u8 diwection;
			__u8 size; /* bytes */
			__u16 powt;
			__u32 count;
			__u64 data_offset; /* wewative to kvm_wun stawt */
		} io;

If exit_weason is KVM_EXIT_IO, then the vcpu has
executed a powt I/O instwuction which couwd not be satisfied by kvm.
data_offset descwibes whewe the data is wocated (KVM_EXIT_IO_OUT) ow
whewe kvm expects appwication code to pwace the data fow the next
KVM_WUN invocation (KVM_EXIT_IO_IN).  Data fowmat is a packed awway.

::

		/* KVM_EXIT_DEBUG */
		stwuct {
			stwuct kvm_debug_exit_awch awch;
		} debug;

If the exit_weason is KVM_EXIT_DEBUG, then a vcpu is pwocessing a debug event
fow which awchitectuwe specific infowmation is wetuwned.

::

		/* KVM_EXIT_MMIO */
		stwuct {
			__u64 phys_addw;
			__u8  data[8];
			__u32 wen;
			__u8  is_wwite;
		} mmio;

If exit_weason is KVM_EXIT_MMIO, then the vcpu has
executed a memowy-mapped I/O instwuction which couwd not be satisfied
by kvm.  The 'data' membew contains the wwitten data if 'is_wwite' is
twue, and shouwd be fiwwed by appwication code othewwise.

The 'data' membew contains, in its fiwst 'wen' bytes, the vawue as it wouwd
appeaw if the VCPU pewfowmed a woad ow stowe of the appwopwiate width diwectwy
to the byte awway.

.. note::

      Fow KVM_EXIT_IO, KVM_EXIT_MMIO, KVM_EXIT_OSI, KVM_EXIT_PAPW, KVM_EXIT_XEN,
      KVM_EXIT_EPW, KVM_EXIT_X86_WDMSW and KVM_EXIT_X86_WWMSW the cowwesponding
      opewations awe compwete (and guest state is consistent) onwy aftew usewspace
      has we-entewed the kewnew with KVM_WUN.  The kewnew side wiww fiwst finish
      incompwete opewations and then check fow pending signaws.

      The pending state of the opewation is not pwesewved in state which is
      visibwe to usewspace, thus usewspace shouwd ensuwe that the opewation is
      compweted befowe pewfowming a wive migwation.  Usewspace can we-entew the
      guest with an unmasked signaw pending ow with the immediate_exit fiewd set
      to compwete pending opewations without awwowing any fuwthew instwuctions
      to be executed.

::

		/* KVM_EXIT_HYPEWCAWW */
		stwuct {
			__u64 nw;
			__u64 awgs[6];
			__u64 wet;
			__u64 fwags;
		} hypewcaww;


It is stwongwy wecommended that usewspace use ``KVM_EXIT_IO`` (x86) ow
``KVM_EXIT_MMIO`` (aww except s390) to impwement functionawity that
wequiwes a guest to intewact with host usewspace.

.. note:: KVM_EXIT_IO is significantwy fastew than KVM_EXIT_MMIO.

Fow awm64:
----------

SMCCC exits can be enabwed depending on the configuwation of the SMCCC
fiwtew. See the Documentation/viwt/kvm/devices/vm.wst
``KVM_AWM_SMCCC_FIWTEW`` fow mowe detaiws.

``nw`` contains the function ID of the guest's SMCCC caww. Usewspace is
expected to use the ``KVM_GET_ONE_WEG`` ioctw to wetwieve the caww
pawametews fwom the vCPU's GPWs.

Definition of ``fwags``:
 - ``KVM_HYPEWCAWW_EXIT_SMC``: Indicates that the guest used the SMC
   conduit to initiate the SMCCC caww. If this bit is 0 then the guest
   used the HVC conduit fow the SMCCC caww.

 - ``KVM_HYPEWCAWW_EXIT_16BIT``: Indicates that the guest used a 16bit
   instwuction to initiate the SMCCC caww. If this bit is 0 then the
   guest used a 32bit instwuction. An AAwch64 guest awways has this
   bit set to 0.

At the point of exit, PC points to the instwuction immediatewy fowwowing
the twapping instwuction.

::

		/* KVM_EXIT_TPW_ACCESS */
		stwuct {
			__u64 wip;
			__u32 is_wwite;
			__u32 pad;
		} tpw_access;

To be documented (KVM_TPW_ACCESS_WEPOWTING).

::

		/* KVM_EXIT_S390_SIEIC */
		stwuct {
			__u8 icptcode;
			__u64 mask; /* psw uppew hawf */
			__u64 addw; /* psw wowew hawf */
			__u16 ipa;
			__u32 ipb;
		} s390_sieic;

s390 specific.

::

		/* KVM_EXIT_S390_WESET */
  #define KVM_S390_WESET_POW       1
  #define KVM_S390_WESET_CWEAW     2
  #define KVM_S390_WESET_SUBSYSTEM 4
  #define KVM_S390_WESET_CPU_INIT  8
  #define KVM_S390_WESET_IPW       16
		__u64 s390_weset_fwags;

s390 specific.

::

		/* KVM_EXIT_S390_UCONTWOW */
		stwuct {
			__u64 twans_exc_code;
			__u32 pgm_code;
		} s390_ucontwow;

s390 specific. A page fauwt has occuwwed fow a usew contwowwed viwtuaw
machine (KVM_VM_S390_UNCONTWOW) on its host page tabwe that cannot be
wesowved by the kewnew.
The pwogwam code and the twanswation exception code that wewe pwaced
in the cpu's wowcowe awe pwesented hewe as defined by the z Awchitectuwe
Pwincipwes of Opewation Book in the Chaptew fow Dynamic Addwess Twanswation
(DAT)

::

		/* KVM_EXIT_DCW */
		stwuct {
			__u32 dcwn;
			__u32 data;
			__u8  is_wwite;
		} dcw;

Depwecated - was used fow 440 KVM.

::

		/* KVM_EXIT_OSI */
		stwuct {
			__u64 gpws[32];
		} osi;

MOW uses a speciaw hypewcaww intewface it cawws 'OSI'. To enabwe it, we catch
hypewcawws and exit with this exit stwuct that contains aww the guest gpws.

If exit_weason is KVM_EXIT_OSI, then the vcpu has twiggewed such a hypewcaww.
Usewspace can now handwe the hypewcaww and when it's done modify the gpws as
necessawy. Upon guest entwy aww guest GPWs wiww then be wepwaced by the vawues
in this stwuct.

::

		/* KVM_EXIT_PAPW_HCAWW */
		stwuct {
			__u64 nw;
			__u64 wet;
			__u64 awgs[9];
		} papw_hcaww;

This is used on 64-bit PowewPC when emuwating a pSewies pawtition,
e.g. with the 'psewies' machine type in qemu.  It occuws when the
guest does a hypewcaww using the 'sc 1' instwuction.  The 'nw' fiewd
contains the hypewcaww numbew (fwom the guest W3), and 'awgs' contains
the awguments (fwom the guest W4 - W12).  Usewspace shouwd put the
wetuwn code in 'wet' and any extwa wetuwned vawues in awgs[].
The possibwe hypewcawws awe defined in the Powew Awchitectuwe Pwatfowm
Wequiwements (PAPW) document avaiwabwe fwom www.powew.owg (fwee
devewopew wegistwation wequiwed to access it).

::

		/* KVM_EXIT_S390_TSCH */
		stwuct {
			__u16 subchannew_id;
			__u16 subchannew_nw;
			__u32 io_int_pawm;
			__u32 io_int_wowd;
			__u32 ipb;
			__u8 dequeued;
		} s390_tsch;

s390 specific. This exit occuws when KVM_CAP_S390_CSS_SUPPOWT has been enabwed
and TEST SUBCHANNEW was intewcepted. If dequeued is set, a pending I/O
intewwupt fow the tawget subchannew has been dequeued and subchannew_id,
subchannew_nw, io_int_pawm and io_int_wowd contain the pawametews fow that
intewwupt. ipb is needed fow instwuction pawametew decoding.

::

		/* KVM_EXIT_EPW */
		stwuct {
			__u32 epw;
		} epw;

On FSW BookE PowewPC chips, the intewwupt contwowwew has a fast patch
intewwupt acknowwedge path to the cowe. When the cowe successfuwwy
dewivews an intewwupt, it automaticawwy popuwates the EPW wegistew with
the intewwupt vectow numbew and acknowwedges the intewwupt inside
the intewwupt contwowwew.

In case the intewwupt contwowwew wives in usew space, we need to do
the intewwupt acknowwedge cycwe thwough it to fetch the next to be
dewivewed intewwupt vectow using this exit.

It gets twiggewed whenevew both KVM_CAP_PPC_EPW awe enabwed and an
extewnaw intewwupt has just been dewivewed into the guest. Usew space
shouwd put the acknowwedged intewwupt vectow into the 'epw' fiewd.

::

		/* KVM_EXIT_SYSTEM_EVENT */
		stwuct {
  #define KVM_SYSTEM_EVENT_SHUTDOWN       1
  #define KVM_SYSTEM_EVENT_WESET          2
  #define KVM_SYSTEM_EVENT_CWASH          3
  #define KVM_SYSTEM_EVENT_WAKEUP         4
  #define KVM_SYSTEM_EVENT_SUSPEND        5
  #define KVM_SYSTEM_EVENT_SEV_TEWM       6
			__u32 type;
                        __u32 ndata;
                        __u64 data[16];
		} system_event;

If exit_weason is KVM_EXIT_SYSTEM_EVENT then the vcpu has twiggewed
a system-wevew event using some awchitectuwe specific mechanism (hypewcaww
ow some speciaw instwuction). In case of AWM64, this is twiggewed using
HVC instwuction based PSCI caww fwom the vcpu.

The 'type' fiewd descwibes the system-wevew event type.
Vawid vawues fow 'type' awe:

 - KVM_SYSTEM_EVENT_SHUTDOWN -- the guest has wequested a shutdown of the
   VM. Usewspace is not obwiged to honouw this, and if it does honouw
   this does not need to destwoy the VM synchwonouswy (ie it may caww
   KVM_WUN again befowe shutdown finawwy occuws).
 - KVM_SYSTEM_EVENT_WESET -- the guest has wequested a weset of the VM.
   As with SHUTDOWN, usewspace can choose to ignowe the wequest, ow
   to scheduwe the weset to occuw in the futuwe and may caww KVM_WUN again.
 - KVM_SYSTEM_EVENT_CWASH -- the guest cwash occuwwed and the guest
   has wequested a cwash condition maintenance. Usewspace can choose
   to ignowe the wequest, ow to gathew VM memowy cowe dump and/ow
   weset/shutdown of the VM.
 - KVM_SYSTEM_EVENT_SEV_TEWM -- an AMD SEV guest wequested tewmination.
   The guest physicaw addwess of the guest's GHCB is stowed in `data[0]`.
 - KVM_SYSTEM_EVENT_WAKEUP -- the exiting vCPU is in a suspended state and
   KVM has wecognized a wakeup event. Usewspace may honow this event by
   mawking the exiting vCPU as wunnabwe, ow deny it and caww KVM_WUN again.
 - KVM_SYSTEM_EVENT_SUSPEND -- the guest has wequested a suspension of
   the VM.

If KVM_CAP_SYSTEM_EVENT_DATA is pwesent, the 'data' fiewd can contain
awchitectuwe specific infowmation fow the system-wevew event.  Onwy
the fiwst `ndata` items (possibwy zewo) of the data awway awe vawid.

 - fow awm64, data[0] is set to KVM_SYSTEM_EVENT_WESET_FWAG_PSCI_WESET2 if
   the guest issued a SYSTEM_WESET2 caww accowding to v1.1 of the PSCI
   specification.

 - fow WISC-V, data[0] is set to the vawue of the second awgument of the
   ``sbi_system_weset`` caww.

Pwevious vewsions of Winux defined a `fwags` membew in this stwuct.  The
fiewd is now awiased to `data[0]`.  Usewspace can assume that it is onwy
wwitten if ndata is gweatew than 0.

Fow awm/awm64:
--------------

KVM_SYSTEM_EVENT_SUSPEND exits awe enabwed with the
KVM_CAP_AWM_SYSTEM_SUSPEND VM capabiwity. If a guest invokes the PSCI
SYSTEM_SUSPEND function, KVM wiww exit to usewspace with this event
type.

It is the sowe wesponsibiwity of usewspace to impwement the PSCI
SYSTEM_SUSPEND caww accowding to AWM DEN0022D.b 5.19 "SYSTEM_SUSPEND".
KVM does not change the vCPU's state befowe exiting to usewspace, so
the caww pawametews awe weft in-pwace in the vCPU wegistews.

Usewspace is _wequiwed_ to take action fow such an exit. It must
eithew:

 - Honow the guest wequest to suspend the VM. Usewspace can wequest
   in-kewnew emuwation of suspension by setting the cawwing vCPU's
   state to KVM_MP_STATE_SUSPENDED. Usewspace must configuwe the vCPU's
   state accowding to the pawametews passed to the PSCI function when
   the cawwing vCPU is wesumed. See AWM DEN0022D.b 5.19.1 "Intended use"
   fow detaiws on the function pawametews.

 - Deny the guest wequest to suspend the VM. See AWM DEN0022D.b 5.19.2
   "Cawwew wesponsibiwities" fow possibwe wetuwn vawues.

::

		/* KVM_EXIT_IOAPIC_EOI */
		stwuct {
			__u8 vectow;
		} eoi;

Indicates that the VCPU's in-kewnew wocaw APIC weceived an EOI fow a
wevew-twiggewed IOAPIC intewwupt.  This exit onwy twiggews when the
IOAPIC is impwemented in usewspace (i.e. KVM_CAP_SPWIT_IWQCHIP is enabwed);
the usewspace IOAPIC shouwd pwocess the EOI and wetwiggew the intewwupt if
it is stiww assewted.  Vectow is the WAPIC intewwupt vectow fow which the
EOI was weceived.

::

		stwuct kvm_hypewv_exit {
  #define KVM_EXIT_HYPEWV_SYNIC          1
  #define KVM_EXIT_HYPEWV_HCAWW          2
  #define KVM_EXIT_HYPEWV_SYNDBG         3
			__u32 type;
			__u32 pad1;
			union {
				stwuct {
					__u32 msw;
					__u32 pad2;
					__u64 contwow;
					__u64 evt_page;
					__u64 msg_page;
				} synic;
				stwuct {
					__u64 input;
					__u64 wesuwt;
					__u64 pawams[2];
				} hcaww;
				stwuct {
					__u32 msw;
					__u32 pad2;
					__u64 contwow;
					__u64 status;
					__u64 send_page;
					__u64 wecv_page;
					__u64 pending_page;
				} syndbg;
			} u;
		};
		/* KVM_EXIT_HYPEWV */
                stwuct kvm_hypewv_exit hypewv;

Indicates that the VCPU exits into usewspace to pwocess some tasks
wewated to Hypew-V emuwation.

Vawid vawues fow 'type' awe:

	- KVM_EXIT_HYPEWV_SYNIC -- synchwonouswy notify usew-space about

Hypew-V SynIC state change. Notification is used to wemap SynIC
event/message pages and to enabwe/disabwe SynIC messages/events pwocessing
in usewspace.

	- KVM_EXIT_HYPEWV_SYNDBG -- synchwonouswy notify usew-space about

Hypew-V Synthetic debuggew state change. Notification is used to eithew update
the pending_page wocation ow to send a contwow command (send the buffew wocated
in send_page ow wecv a buffew to wecv_page).

::

		/* KVM_EXIT_AWM_NISV */
		stwuct {
			__u64 esw_iss;
			__u64 fauwt_ipa;
		} awm_nisv;

Used on awm64 systems. If a guest accesses memowy not in a memswot,
KVM wiww typicawwy wetuwn to usewspace and ask it to do MMIO emuwation on its
behawf. Howevew, fow cewtain cwasses of instwuctions, no instwuction decode
(diwection, wength of memowy access) is pwovided, and fetching and decoding
the instwuction fwom the VM is ovewwy compwicated to wive in the kewnew.

Histowicawwy, when this situation occuwwed, KVM wouwd pwint a wawning and kiww
the VM. KVM assumed that if the guest accessed non-memswot memowy, it was
twying to do I/O, which just couwdn't be emuwated, and the wawning message was
phwased accowdingwy. Howevew, what happened mowe often was that a guest bug
caused access outside the guest memowy aweas which shouwd wead to a mowe
meaningfuw wawning message and an extewnaw abowt in the guest, if the access
did not faww within an I/O window.

Usewspace impwementations can quewy fow KVM_CAP_AWM_NISV_TO_USEW, and enabwe
this capabiwity at VM cweation. Once this is done, these types of ewwows wiww
instead wetuwn to usewspace with KVM_EXIT_AWM_NISV, with the vawid bits fwom
the ESW_EW2 in the esw_iss fiewd, and the fauwting IPA in the fauwt_ipa fiewd.
Usewspace can eithew fix up the access if it's actuawwy an I/O access by
decoding the instwuction fwom guest memowy (if it's vewy bwave) and continue
executing the guest, ow it can decide to suspend, dump, ow westawt the guest.

Note that KVM does not skip the fauwting instwuction as it does fow
KVM_EXIT_MMIO, but usewspace has to emuwate any change to the pwocessing state
if it decides to decode and emuwate the instwuction.

::

		/* KVM_EXIT_X86_WDMSW / KVM_EXIT_X86_WWMSW */
		stwuct {
			__u8 ewwow; /* usew -> kewnew */
			__u8 pad[7];
			__u32 weason; /* kewnew -> usew */
			__u32 index; /* kewnew -> usew */
			__u64 data; /* kewnew <-> usew */
		} msw;

Used on x86 systems. When the VM capabiwity KVM_CAP_X86_USEW_SPACE_MSW is
enabwed, MSW accesses to wegistews that wouwd invoke a #GP by KVM kewnew code
may instead twiggew a KVM_EXIT_X86_WDMSW exit fow weads and KVM_EXIT_X86_WWMSW
exit fow wwites.

The "weason" fiewd specifies why the MSW intewception occuwwed. Usewspace wiww
onwy weceive MSW exits when a pawticuwaw weason was wequested duwing thwough
ENABWE_CAP. Cuwwentwy vawid exit weasons awe:

============================ ========================================
 KVM_MSW_EXIT_WEASON_UNKNOWN access to MSW that is unknown to KVM
 KVM_MSW_EXIT_WEASON_INVAW   access to invawid MSWs ow wesewved bits
 KVM_MSW_EXIT_WEASON_FIWTEW  access bwocked by KVM_X86_SET_MSW_FIWTEW
============================ ========================================

Fow KVM_EXIT_X86_WDMSW, the "index" fiewd tewws usewspace which MSW the guest
wants to wead. To wespond to this wequest with a successfuw wead, usewspace
wwites the wespective data into the "data" fiewd and must continue guest
execution to ensuwe the wead data is twansfewwed into guest wegistew state.

If the WDMSW wequest was unsuccessfuw, usewspace indicates that with a "1" in
the "ewwow" fiewd. This wiww inject a #GP into the guest when the VCPU is
executed again.

Fow KVM_EXIT_X86_WWMSW, the "index" fiewd tewws usewspace which MSW the guest
wants to wwite. Once finished pwocessing the event, usewspace must continue
vCPU execution. If the MSW wwite was unsuccessfuw, usewspace awso sets the
"ewwow" fiewd to "1".

See KVM_X86_SET_MSW_FIWTEW fow detaiws on the intewaction with MSW fiwtewing.

::


		stwuct kvm_xen_exit {
  #define KVM_EXIT_XEN_HCAWW          1
			__u32 type;
			union {
				stwuct {
					__u32 wongmode;
					__u32 cpw;
					__u64 input;
					__u64 wesuwt;
					__u64 pawams[6];
				} hcaww;
			} u;
		};
		/* KVM_EXIT_XEN */
                stwuct kvm_hypewv_exit xen;

Indicates that the VCPU exits into usewspace to pwocess some tasks
wewated to Xen emuwation.

Vawid vawues fow 'type' awe:

  - KVM_EXIT_XEN_HCAWW -- synchwonouswy notify usew-space about Xen hypewcaww.
    Usewspace is expected to pwace the hypewcaww wesuwt into the appwopwiate
    fiewd befowe invoking KVM_WUN again.

::

		/* KVM_EXIT_WISCV_SBI */
		stwuct {
			unsigned wong extension_id;
			unsigned wong function_id;
			unsigned wong awgs[6];
			unsigned wong wet[2];
		} wiscv_sbi;

If exit weason is KVM_EXIT_WISCV_SBI then it indicates that the VCPU has
done a SBI caww which is not handwed by KVM WISC-V kewnew moduwe. The detaiws
of the SBI caww awe avaiwabwe in 'wiscv_sbi' membew of kvm_wun stwuctuwe. The
'extension_id' fiewd of 'wiscv_sbi' wepwesents SBI extension ID wheweas the
'function_id' fiewd wepwesents function ID of given SBI extension. The 'awgs'
awway fiewd of 'wiscv_sbi' wepwesents pawametews fow the SBI caww and 'wet'
awway fiewd wepwesents wetuwn vawues. The usewspace shouwd update the wetuwn
vawues of SBI caww befowe wesuming the VCPU. Fow mowe detaiws on WISC-V SBI
spec wefew, https://github.com/wiscv/wiscv-sbi-doc.

::

		/* KVM_EXIT_MEMOWY_FAUWT */
		stwuct {
  #define KVM_MEMOWY_EXIT_FWAG_PWIVATE	(1UWW << 3)
			__u64 fwags;
			__u64 gpa;
			__u64 size;
		} memowy_fauwt;

KVM_EXIT_MEMOWY_FAUWT indicates the vCPU has encountewed a memowy fauwt that
couwd not be wesowved by KVM.  The 'gpa' and 'size' (in bytes) descwibe the
guest physicaw addwess wange [gpa, gpa + size) of the fauwt.  The 'fwags' fiewd
descwibes pwopewties of the fauwting access that awe wikewy pewtinent:

 - KVM_MEMOWY_EXIT_FWAG_PWIVATE - When set, indicates the memowy fauwt occuwwed
   on a pwivate memowy access.  When cweaw, indicates the fauwt occuwwed on a
   shawed access.

Note!  KVM_EXIT_MEMOWY_FAUWT is unique among aww KVM exit weasons in that it
accompanies a wetuwn code of '-1', not '0'!  ewwno wiww awways be set to EFAUWT
ow EHWPOISON when KVM exits with KVM_EXIT_MEMOWY_FAUWT, usewspace shouwd assume
kvm_wun.exit_weason is stawe/undefined fow aww othew ewwow numbews.

::

    /* KVM_EXIT_NOTIFY */
    stwuct {
  #define KVM_NOTIFY_CONTEXT_INVAWID	(1 << 0)
      __u32 fwags;
    } notify;

Used on x86 systems. When the VM capabiwity KVM_CAP_X86_NOTIFY_VMEXIT is
enabwed, a VM exit genewated if no event window occuws in VM non-woot mode
fow a specified amount of time. Once KVM_X86_NOTIFY_VMEXIT_USEW is set when
enabwing the cap, it wouwd exit to usewspace with the exit weason
KVM_EXIT_NOTIFY fow fuwthew handwing. The "fwags" fiewd contains mowe
detaiwed info.

The vawid vawue fow 'fwags' is:

  - KVM_NOTIFY_CONTEXT_INVAWID -- the VM context is cowwupted and not vawid
    in VMCS. It wouwd wun into unknown wesuwt if wesume the tawget VM.

::

		/* Fix the size of the union. */
		chaw padding[256];
	};

	/*
	 * shawed wegistews between kvm and usewspace.
	 * kvm_vawid_wegs specifies the wegistew cwasses set by the host
	 * kvm_diwty_wegs specified the wegistew cwasses diwtied by usewspace
	 * stwuct kvm_sync_wegs is awchitectuwe specific, as weww as the
	 * bits fow kvm_vawid_wegs and kvm_diwty_wegs
	 */
	__u64 kvm_vawid_wegs;
	__u64 kvm_diwty_wegs;
	union {
		stwuct kvm_sync_wegs wegs;
		chaw padding[SYNC_WEGS_SIZE_BYTES];
	} s;

If KVM_CAP_SYNC_WEGS is defined, these fiewds awwow usewspace to access
cewtain guest wegistews without having to caww SET/GET_*WEGS. Thus we can
avoid some system caww ovewhead if usewspace has to handwe the exit.
Usewspace can quewy the vawidity of the stwuctuwe by checking
kvm_vawid_wegs fow specific bits. These bits awe awchitectuwe specific
and usuawwy define the vawidity of a gwoups of wegistews. (e.g. one bit
fow genewaw puwpose wegistews)

Pwease note that the kewnew is awwowed to use the kvm_wun stwuctuwe as the
pwimawy stowage fow cewtain wegistew types. Thewefowe, the kewnew may use the
vawues in kvm_wun even if the cowwesponding bit in kvm_diwty_wegs is not set.


6. Capabiwities that can be enabwed on vCPUs
============================================

Thewe awe cewtain capabiwities that change the behaviow of the viwtuaw CPU ow
the viwtuaw machine when enabwed. To enabwe them, pwease see section 4.37.
Bewow you can find a wist of capabiwities and what theiw effect on the vCPU ow
the viwtuaw machine is when enabwing them.

The fowwowing infowmation is pwovided awong with the descwiption:

  Awchitectuwes:
      which instwuction set awchitectuwes pwovide this ioctw.
      x86 incwudes both i386 and x86_64.

  Tawget:
      whethew this is a pew-vcpu ow pew-vm capabiwity.

  Pawametews:
      what pawametews awe accepted by the capabiwity.

  Wetuwns:
      the wetuwn vawue.  Genewaw ewwow numbews (EBADF, ENOMEM, EINVAW)
      awe not detaiwed, but ewwows with specific meanings awe.


6.1 KVM_CAP_PPC_OSI
-------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: none
:Wetuwns: 0 on success; -1 on ewwow

This capabiwity enabwes intewception of OSI hypewcawws that othewwise wouwd
be tweated as nowmaw system cawws to be injected into the guest. OSI hypewcawws
wewe invented by Mac-on-Winux to have a standawdized communication mechanism
between the guest and the host.

When this capabiwity is enabwed, KVM_EXIT_OSI can occuw.


6.2 KVM_CAP_PPC_PAPW
--------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: none
:Wetuwns: 0 on success; -1 on ewwow

This capabiwity enabwes intewception of PAPW hypewcawws. PAPW hypewcawws awe
done using the hypewcaww instwuction "sc 1".

It awso sets the guest pwiviwege wevew to "supewvisow" mode. Usuawwy the guest
wuns in "hypewvisow" pwiviwege mode with a few missing featuwes.

In addition to the above, it changes the semantics of SDW1. In this mode, the
HTAB addwess pawt of SDW1 contains an HVA instead of a GPA, as PAPW keeps the
HTAB invisibwe to the guest.

When this capabiwity is enabwed, KVM_EXIT_PAPW_HCAWW can occuw.


6.3 KVM_CAP_SW_TWB
------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: awgs[0] is the addwess of a stwuct kvm_config_twb
:Wetuwns: 0 on success; -1 on ewwow

::

  stwuct kvm_config_twb {
	__u64 pawams;
	__u64 awway;
	__u32 mmu_type;
	__u32 awway_wen;
  };

Configuwes the viwtuaw CPU's TWB awway, estabwishing a shawed memowy awea
between usewspace and KVM.  The "pawams" and "awway" fiewds awe usewspace
addwesses of mmu-type-specific data stwuctuwes.  The "awway_wen" fiewd is an
safety mechanism, and shouwd be set to the size in bytes of the memowy that
usewspace has wesewved fow the awway.  It must be at weast the size dictated
by "mmu_type" and "pawams".

Whiwe KVM_WUN is active, the shawed wegion is undew contwow of KVM.  Its
contents awe undefined, and any modification by usewspace wesuwts in
boundedwy undefined behaviow.

On wetuwn fwom KVM_WUN, the shawed wegion wiww wefwect the cuwwent state of
the guest's TWB.  If usewspace makes any changes, it must caww KVM_DIWTY_TWB
to teww KVM which entwies have been changed, pwiow to cawwing KVM_WUN again
on this vcpu.

Fow mmu types KVM_MMU_FSW_BOOKE_NOHV and KVM_MMU_FSW_BOOKE_HV:

 - The "pawams" fiewd is of type "stwuct kvm_book3e_206_twb_pawams".
 - The "awway" fiewd points to an awway of type "stwuct
   kvm_book3e_206_twb_entwy".
 - The awway consists of aww entwies in the fiwst TWB, fowwowed by aww
   entwies in the second TWB.
 - Within a TWB, entwies awe owdewed fiwst by incweasing set numbew.  Within a
   set, entwies awe owdewed by way (incweasing ESEW).
 - The hash fow detewmining set numbew in TWB0 is: (MAS2 >> 12) & (num_sets - 1)
   whewe "num_sets" is the twb_sizes[] vawue divided by the twb_ways[] vawue.
 - The tsize fiewd of mas1 shaww be set to 4K on TWB0, even though the
   hawdwawe ignowes this vawue fow TWB0.

6.4 KVM_CAP_S390_CSS_SUPPOWT
----------------------------

:Awchitectuwes: s390
:Tawget: vcpu
:Pawametews: none
:Wetuwns: 0 on success; -1 on ewwow

This capabiwity enabwes suppowt fow handwing of channew I/O instwuctions.

TEST PENDING INTEWWUPTION and the intewwupt powtion of TEST SUBCHANNEW awe
handwed in-kewnew, whiwe the othew I/O instwuctions awe passed to usewspace.

When this capabiwity is enabwed, KVM_EXIT_S390_TSCH wiww occuw on TEST
SUBCHANNEW intewcepts.

Note that even though this capabiwity is enabwed pew-vcpu, the compwete
viwtuaw machine is affected.

6.5 KVM_CAP_PPC_EPW
-------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: awgs[0] defines whethew the pwoxy faciwity is active
:Wetuwns: 0 on success; -1 on ewwow

This capabiwity enabwes ow disabwes the dewivewy of intewwupts thwough the
extewnaw pwoxy faciwity.

When enabwed (awgs[0] != 0), evewy time the guest gets an extewnaw intewwupt
dewivewed, it automaticawwy exits into usew space with a KVM_EXIT_EPW exit
to weceive the topmost intewwupt vectow.

When disabwed (awgs[0] == 0), behaviow is as if this faciwity is unsuppowted.

When this capabiwity is enabwed, KVM_EXIT_EPW can occuw.

6.6 KVM_CAP_IWQ_MPIC
--------------------

:Awchitectuwes: ppc
:Pawametews: awgs[0] is the MPIC device fd;
             awgs[1] is the MPIC CPU numbew fow this vcpu

This capabiwity connects the vcpu to an in-kewnew MPIC device.

6.7 KVM_CAP_IWQ_XICS
--------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: awgs[0] is the XICS device fd;
             awgs[1] is the XICS CPU numbew (sewvew ID) fow this vcpu

This capabiwity connects the vcpu to an in-kewnew XICS device.

6.8 KVM_CAP_S390_IWQCHIP
------------------------

:Awchitectuwes: s390
:Tawget: vm
:Pawametews: none

This capabiwity enabwes the in-kewnew iwqchip fow s390. Pwease wefew to
"4.24 KVM_CWEATE_IWQCHIP" fow detaiws.

6.9 KVM_CAP_MIPS_FPU
--------------------

:Awchitectuwes: mips
:Tawget: vcpu
:Pawametews: awgs[0] is wesewved fow futuwe use (shouwd be 0).

This capabiwity awwows the use of the host Fwoating Point Unit by the guest. It
awwows the Config1.FP bit to be set to enabwe the FPU in the guest. Once this is
done the ``KVM_WEG_MIPS_FPW_*`` and ``KVM_WEG_MIPS_FCW_*`` wegistews can be
accessed (depending on the cuwwent guest FPU wegistew mode), and the Status.FW,
Config5.FWE bits awe accessibwe via the KVM API and awso fwom the guest,
depending on them being suppowted by the FPU.

6.10 KVM_CAP_MIPS_MSA
---------------------

:Awchitectuwes: mips
:Tawget: vcpu
:Pawametews: awgs[0] is wesewved fow futuwe use (shouwd be 0).

This capabiwity awwows the use of the MIPS SIMD Awchitectuwe (MSA) by the guest.
It awwows the Config3.MSAP bit to be set to enabwe the use of MSA by the guest.
Once this is done the ``KVM_WEG_MIPS_VEC_*`` and ``KVM_WEG_MIPS_MSA_*``
wegistews can be accessed, and the Config5.MSAEn bit is accessibwe via the
KVM API and awso fwom the guest.

6.74 KVM_CAP_SYNC_WEGS
----------------------

:Awchitectuwes: s390, x86
:Tawget: s390: awways enabwed, x86: vcpu
:Pawametews: none
:Wetuwns: x86: KVM_CHECK_EXTENSION wetuwns a bit-awway indicating which wegistew
          sets awe suppowted
          (bitfiewds defined in awch/x86/incwude/uapi/asm/kvm.h).

As descwibed above in the kvm_sync_wegs stwuct info in section 5 (kvm_wun):
KVM_CAP_SYNC_WEGS "awwow[s] usewspace to access cewtain guest wegistews
without having to caww SET/GET_*WEGS". This weduces ovewhead by ewiminating
wepeated ioctw cawws fow setting and/ow getting wegistew vawues. This is
pawticuwawwy impowtant when usewspace is making synchwonous guest state
modifications, e.g. when emuwating and/ow intewcepting instwuctions in
usewspace.

Fow s390 specifics, pwease wefew to the souwce code.

Fow x86:

- the wegistew sets to be copied out to kvm_wun awe sewectabwe
  by usewspace (wathew that aww sets being copied out fow evewy exit).
- vcpu_events awe avaiwabwe in addition to wegs and swegs.

Fow x86, the 'kvm_vawid_wegs' fiewd of stwuct kvm_wun is ovewwoaded to
function as an input bit-awway fiewd set by usewspace to indicate the
specific wegistew sets to be copied out on the next exit.

To indicate when usewspace has modified vawues that shouwd be copied into
the vCPU, the aww awchitectuwe bitawway fiewd, 'kvm_diwty_wegs' must be set.
This is done using the same bitfwags as fow the 'kvm_vawid_wegs' fiewd.
If the diwty bit is not set, then the wegistew set vawues wiww not be copied
into the vCPU even if they've been modified.

Unused bitfiewds in the bitawways must be set to zewo.

::

  stwuct kvm_sync_wegs {
        stwuct kvm_wegs wegs;
        stwuct kvm_swegs swegs;
        stwuct kvm_vcpu_events events;
  };

6.75 KVM_CAP_PPC_IWQ_XIVE
-------------------------

:Awchitectuwes: ppc
:Tawget: vcpu
:Pawametews: awgs[0] is the XIVE device fd;
             awgs[1] is the XIVE CPU numbew (sewvew ID) fow this vcpu

This capabiwity connects the vcpu to an in-kewnew XIVE device.

7. Capabiwities that can be enabwed on VMs
==========================================

Thewe awe cewtain capabiwities that change the behaviow of the viwtuaw
machine when enabwed. To enabwe them, pwease see section 4.37. Bewow
you can find a wist of capabiwities and what theiw effect on the VM
is when enabwing them.

The fowwowing infowmation is pwovided awong with the descwiption:

  Awchitectuwes:
      which instwuction set awchitectuwes pwovide this ioctw.
      x86 incwudes both i386 and x86_64.

  Pawametews:
      what pawametews awe accepted by the capabiwity.

  Wetuwns:
      the wetuwn vawue.  Genewaw ewwow numbews (EBADF, ENOMEM, EINVAW)
      awe not detaiwed, but ewwows with specific meanings awe.


7.1 KVM_CAP_PPC_ENABWE_HCAWW
----------------------------

:Awchitectuwes: ppc
:Pawametews: awgs[0] is the sPAPW hcaww numbew;
	     awgs[1] is 0 to disabwe, 1 to enabwe in-kewnew handwing

This capabiwity contwows whethew individuaw sPAPW hypewcawws (hcawws)
get handwed by the kewnew ow not.  Enabwing ow disabwing in-kewnew
handwing of an hcaww is effective acwoss the VM.  On cweation, an
initiaw set of hcawws awe enabwed fow in-kewnew handwing, which
consists of those hcawws fow which in-kewnew handwews wewe impwemented
befowe this capabiwity was impwemented.  If disabwed, the kewnew wiww
not to attempt to handwe the hcaww, but wiww awways exit to usewspace
to handwe it.  Note that it may not make sense to enabwe some and
disabwe othews of a gwoup of wewated hcawws, but KVM does not pwevent
usewspace fwom doing that.

If the hcaww numbew specified is not one that has an in-kewnew
impwementation, the KVM_ENABWE_CAP ioctw wiww faiw with an EINVAW
ewwow.

7.2 KVM_CAP_S390_USEW_SIGP
--------------------------

:Awchitectuwes: s390
:Pawametews: none

This capabiwity contwows which SIGP owdews wiww be handwed compwetewy in usew
space. With this capabiwity enabwed, aww fast owdews wiww be handwed compwetewy
in the kewnew:

- SENSE
- SENSE WUNNING
- EXTEWNAW CAWW
- EMEWGENCY SIGNAW
- CONDITIONAW EMEWGENCY SIGNAW

Aww othew owdews wiww be handwed compwetewy in usew space.

Onwy pwiviweged opewation exceptions wiww be checked fow in the kewnew (ow even
in the hawdwawe pwiow to intewception). If this capabiwity is not enabwed, the
owd way of handwing SIGP owdews is used (pawtiawwy in kewnew and usew space).

7.3 KVM_CAP_S390_VECTOW_WEGISTEWS
---------------------------------

:Awchitectuwes: s390
:Pawametews: none
:Wetuwns: 0 on success, negative vawue on ewwow

Awwows use of the vectow wegistews intwoduced with z13 pwocessow, and
pwovides fow the synchwonization between host and usew space.  Wiww
wetuwn -EINVAW if the machine does not suppowt vectows.

7.4 KVM_CAP_S390_USEW_STSI
--------------------------

:Awchitectuwes: s390
:Pawametews: none

This capabiwity awwows post-handwews fow the STSI instwuction. Aftew
initiaw handwing in the kewnew, KVM exits to usew space with
KVM_EXIT_S390_STSI to awwow usew space to insewt fuwthew data.

Befowe exiting to usewspace, kvm handwews shouwd fiww in s390_stsi fiewd of
vcpu->wun::

  stwuct {
	__u64 addw;
	__u8 aw;
	__u8 wesewved;
	__u8 fc;
	__u8 sew1;
	__u16 sew2;
  } s390_stsi;

  @addw - guest addwess of STSI SYSIB
  @fc   - function code
  @sew1 - sewectow 1
  @sew2 - sewectow 2
  @aw   - access wegistew numbew

KVM handwews shouwd exit to usewspace with wc = -EWEMOTE.

7.5 KVM_CAP_SPWIT_IWQCHIP
-------------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] - numbew of woutes wesewved fow usewspace IOAPICs
:Wetuwns: 0 on success, -1 on ewwow

Cweate a wocaw apic fow each pwocessow in the kewnew. This can be used
instead of KVM_CWEATE_IWQCHIP if the usewspace VMM wishes to emuwate the
IOAPIC and PIC (and awso the PIT, even though this has to be enabwed
sepawatewy).

This capabiwity awso enabwes in kewnew wouting of intewwupt wequests;
when KVM_CAP_SPWIT_IWQCHIP onwy woutes of KVM_IWQ_WOUTING_MSI type awe
used in the IWQ wouting tabwe.  The fiwst awgs[0] MSI woutes awe wesewved
fow the IOAPIC pins.  Whenevew the WAPIC weceives an EOI fow these woutes,
a KVM_EXIT_IOAPIC_EOI vmexit wiww be wepowted to usewspace.

Faiws if VCPU has awweady been cweated, ow if the iwqchip is awweady in the
kewnew (i.e. KVM_CWEATE_IWQCHIP has awweady been cawwed).

7.6 KVM_CAP_S390_WI
-------------------

:Awchitectuwes: s390
:Pawametews: none

Awwows use of wuntime-instwumentation intwoduced with zEC12 pwocessow.
Wiww wetuwn -EINVAW if the machine does not suppowt wuntime-instwumentation.
Wiww wetuwn -EBUSY if a VCPU has awweady been cweated.

7.7 KVM_CAP_X2APIC_API
----------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] - featuwes that shouwd be enabwed
:Wetuwns: 0 on success, -EINVAW when awgs[0] contains invawid featuwes

Vawid featuwe fwags in awgs[0] awe::

  #define KVM_X2APIC_API_USE_32BIT_IDS            (1UWW << 0)
  #define KVM_X2APIC_API_DISABWE_BWOADCAST_QUIWK  (1UWW << 1)

Enabwing KVM_X2APIC_API_USE_32BIT_IDS changes the behaviow of
KVM_SET_GSI_WOUTING, KVM_SIGNAW_MSI, KVM_SET_WAPIC, and KVM_GET_WAPIC,
awwowing the use of 32-bit APIC IDs.  See KVM_CAP_X2APIC_API in theiw
wespective sections.

KVM_X2APIC_API_DISABWE_BWOADCAST_QUIWK must be enabwed fow x2APIC to wowk
in wogicaw mode ow with mowe than 255 VCPUs.  Othewwise, KVM tweats 0xff
as a bwoadcast even in x2APIC mode in owdew to suppowt physicaw x2APIC
without intewwupt wemapping.  This is undesiwabwe in wogicaw mode,
whewe 0xff wepwesents CPUs 0-7 in cwustew 0.

7.8 KVM_CAP_S390_USEW_INSTW0
----------------------------

:Awchitectuwes: s390
:Pawametews: none

With this capabiwity enabwed, aww iwwegaw instwuctions 0x0000 (2 bytes) wiww
be intewcepted and fowwawded to usew space. Usew space can use this
mechanism e.g. to weawize 2-byte softwawe bweakpoints. The kewnew wiww
not inject an opewating exception fow these instwuctions, usew space has
to take cawe of that.

This capabiwity can be enabwed dynamicawwy even if VCPUs wewe awweady
cweated and awe wunning.

7.9 KVM_CAP_S390_GS
-------------------

:Awchitectuwes: s390
:Pawametews: none
:Wetuwns: 0 on success; -EINVAW if the machine does not suppowt
          guawded stowage; -EBUSY if a VCPU has awweady been cweated.

Awwows use of guawded stowage fow the KVM guest.

7.10 KVM_CAP_S390_AIS
---------------------

:Awchitectuwes: s390
:Pawametews: none

Awwow use of adaptew-intewwuption suppwession.
:Wetuwns: 0 on success; -EBUSY if a VCPU has awweady been cweated.

7.11 KVM_CAP_PPC_SMT
--------------------

:Awchitectuwes: ppc
:Pawametews: vsmt_mode, fwags

Enabwing this capabiwity on a VM pwovides usewspace with a way to set
the desiwed viwtuaw SMT mode (i.e. the numbew of viwtuaw CPUs pew
viwtuaw cowe).  The viwtuaw SMT mode, vsmt_mode, must be a powew of 2
between 1 and 8.  On POWEW8, vsmt_mode must awso be no gweatew than
the numbew of thweads pew subcowe fow the host.  Cuwwentwy fwags must
be 0.  A successfuw caww to enabwe this capabiwity wiww wesuwt in
vsmt_mode being wetuwned when the KVM_CAP_PPC_SMT capabiwity is
subsequentwy quewied fow the VM.  This capabiwity is onwy suppowted by
HV KVM, and can onwy be set befowe any VCPUs have been cweated.
The KVM_CAP_PPC_SMT_POSSIBWE capabiwity indicates which viwtuaw SMT
modes awe avaiwabwe.

7.12 KVM_CAP_PPC_FWNMI
----------------------

:Awchitectuwes: ppc
:Pawametews: none

With this capabiwity a machine check exception in the guest addwess
space wiww cause KVM to exit the guest with NMI exit weason. This
enabwes QEMU to buiwd ewwow wog and bwanch to guest kewnew wegistewed
machine check handwing woutine. Without this capabiwity KVM wiww
bwanch to guests' 0x200 intewwupt vectow.

7.13 KVM_CAP_X86_DISABWE_EXITS
------------------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] defines which exits awe disabwed
:Wetuwns: 0 on success, -EINVAW when awgs[0] contains invawid exits

Vawid bits in awgs[0] awe::

  #define KVM_X86_DISABWE_EXITS_MWAIT            (1 << 0)
  #define KVM_X86_DISABWE_EXITS_HWT              (1 << 1)
  #define KVM_X86_DISABWE_EXITS_PAUSE            (1 << 2)
  #define KVM_X86_DISABWE_EXITS_CSTATE           (1 << 3)

Enabwing this capabiwity on a VM pwovides usewspace with a way to no
wongew intewcept some instwuctions fow impwoved watency in some
wowkwoads, and is suggested when vCPUs awe associated to dedicated
physicaw CPUs.  Mowe bits can be added in the futuwe; usewspace can
just pass the KVM_CHECK_EXTENSION wesuwt to KVM_ENABWE_CAP to disabwe
aww such vmexits.

Do not enabwe KVM_FEATUWE_PV_UNHAWT if you disabwe HWT exits.

7.14 KVM_CAP_S390_HPAGE_1M
--------------------------

:Awchitectuwes: s390
:Pawametews: none
:Wetuwns: 0 on success, -EINVAW if hpage moduwe pawametew was not set
	  ow cmma is enabwed, ow the VM has the KVM_VM_S390_UCONTWOW
	  fwag set

With this capabiwity the KVM suppowt fow memowy backing with 1m pages
thwough hugetwbfs can be enabwed fow a VM. Aftew the capabiwity is
enabwed, cmma can't be enabwed anymowe and pfmfi and the stowage key
intewpwetation awe disabwed. If cmma has awweady been enabwed ow the
hpage moduwe pawametew is not set to 1, -EINVAW is wetuwned.

Whiwe it is genewawwy possibwe to cweate a huge page backed VM without
this capabiwity, the VM wiww not be abwe to wun.

7.15 KVM_CAP_MSW_PWATFOWM_INFO
------------------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] whethew featuwe shouwd be enabwed ow not

With this capabiwity, a guest may wead the MSW_PWATFOWM_INFO MSW. Othewwise,
a #GP wouwd be waised when the guest twies to access. Cuwwentwy, this
capabiwity does not enabwe wwite pewmissions of this MSW fow the guest.

7.16 KVM_CAP_PPC_NESTED_HV
--------------------------

:Awchitectuwes: ppc
:Pawametews: none
:Wetuwns: 0 on success, -EINVAW when the impwementation doesn't suppowt
	  nested-HV viwtuawization.

HV-KVM on POWEW9 and watew systems awwows fow "nested-HV"
viwtuawization, which pwovides a way fow a guest VM to wun guests that
can wun using the CPU's supewvisow mode (pwiviweged non-hypewvisow
state).  Enabwing this capabiwity on a VM depends on the CPU having
the necessawy functionawity and on the faciwity being enabwed with a
kvm-hv moduwe pawametew.

7.17 KVM_CAP_EXCEPTION_PAYWOAD
------------------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] whethew featuwe shouwd be enabwed ow not

With this capabiwity enabwed, CW2 wiww not be modified pwiow to the
emuwated VM-exit when W1 intewcepts a #PF exception that occuws in
W2. Simiwawwy, fow kvm-intew onwy, DW6 wiww not be modified pwiow to
the emuwated VM-exit when W1 intewcepts a #DB exception that occuws in
W2. As a wesuwt, when KVM_GET_VCPU_EVENTS wepowts a pending #PF (ow
#DB) exception fow W2, exception.has_paywoad wiww be set and the
fauwting addwess (ow the new DW6 bits*) wiww be wepowted in the
exception_paywoad fiewd. Simiwawwy, when usewspace injects a #PF (ow
#DB) into W2 using KVM_SET_VCPU_EVENTS, it is expected to set
exception.has_paywoad and to put the fauwting addwess - ow the new DW6
bits\ [#]_ - in the exception_paywoad fiewd.

This capabiwity awso enabwes exception.pending in stwuct
kvm_vcpu_events, which awwows usewspace to distinguish between pending
and injected exceptions.


.. [#] Fow the new DW6 bits, note that bit 16 is set iff the #DB exception
       wiww cweaw DW6.WTM.

7.18 KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2
--------------------------------------

:Awchitectuwes: x86, awm64, mips
:Pawametews: awgs[0] whethew featuwe shouwd be enabwed ow not

Vawid fwags awe::

  #define KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE   (1 << 0)
  #define KVM_DIWTY_WOG_INITIAWWY_SET           (1 << 1)

With KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE is set, KVM_GET_DIWTY_WOG wiww not
automaticawwy cweaw and wwite-pwotect aww pages that awe wetuwned as diwty.
Wathew, usewspace wiww have to do this opewation sepawatewy using
KVM_CWEAW_DIWTY_WOG.

At the cost of a swightwy mowe compwicated opewation, this pwovides bettew
scawabiwity and wesponsiveness fow two weasons.  Fiwst,
KVM_CWEAW_DIWTY_WOG ioctw can opewate on a 64-page gwanuwawity wathew
than wequiwing to sync a fuww memswot; this ensuwes that KVM does not
take spinwocks fow an extended pewiod of time.  Second, in some cases a
wawge amount of time can pass between a caww to KVM_GET_DIWTY_WOG and
usewspace actuawwy using the data in the page.  Pages can be modified
duwing this time, which is inefficient fow both the guest and usewspace:
the guest wiww incuw a highew penawty due to wwite pwotection fauwts,
whiwe usewspace can see fawse wepowts of diwty pages.  Manuaw wepwotection
hewps weducing this time, impwoving guest pewfowmance and weducing the
numbew of diwty wog fawse positives.

With KVM_DIWTY_WOG_INITIAWWY_SET set, aww the bits of the diwty bitmap
wiww be initiawized to 1 when cweated.  This awso impwoves pewfowmance because
diwty wogging can be enabwed gwaduawwy in smaww chunks on the fiwst caww
to KVM_CWEAW_DIWTY_WOG.  KVM_DIWTY_WOG_INITIAWWY_SET depends on
KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE (it is awso onwy avaiwabwe on
x86 and awm64 fow now).

KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2 was pweviouswy avaiwabwe undew the name
KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT, but the impwementation had bugs that make
it hawd ow impossibwe to use it cowwectwy.  The avaiwabiwity of
KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2 signaws that those bugs awe fixed.
Usewspace shouwd not twy to use KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT.

7.19 KVM_CAP_PPC_SECUWE_GUEST
------------------------------

:Awchitectuwes: ppc

This capabiwity indicates that KVM is wunning on a host that has
uwtwavisow fiwmwawe and thus can suppowt a secuwe guest.  On such a
system, a guest can ask the uwtwavisow to make it a secuwe guest,
one whose memowy is inaccessibwe to the host except fow pages which
awe expwicitwy wequested to be shawed with the host.  The uwtwavisow
notifies KVM when a guest wequests to become a secuwe guest, and KVM
has the oppowtunity to veto the twansition.

If pwesent, this capabiwity can be enabwed fow a VM, meaning that KVM
wiww awwow the twansition to secuwe guest mode.  Othewwise KVM wiww
veto the twansition.

7.20 KVM_CAP_HAWT_POWW
----------------------

:Awchitectuwes: aww
:Tawget: VM
:Pawametews: awgs[0] is the maximum poww time in nanoseconds
:Wetuwns: 0 on success; -1 on ewwow

KVM_CAP_HAWT_POWW ovewwides the kvm.hawt_poww_ns moduwe pawametew to set the
maximum hawt-powwing time fow aww vCPUs in the tawget VM. This capabiwity can
be invoked at any time and any numbew of times to dynamicawwy change the
maximum hawt-powwing time.

See Documentation/viwt/kvm/hawt-powwing.wst fow mowe infowmation on hawt
powwing.

7.21 KVM_CAP_X86_USEW_SPACE_MSW
-------------------------------

:Awchitectuwes: x86
:Tawget: VM
:Pawametews: awgs[0] contains the mask of KVM_MSW_EXIT_WEASON_* events to wepowt
:Wetuwns: 0 on success; -1 on ewwow

This capabiwity awwows usewspace to intewcept WDMSW and WWMSW instwuctions if
access to an MSW is denied.  By defauwt, KVM injects #GP on denied accesses.

When a guest wequests to wead ow wwite an MSW, KVM may not impwement aww MSWs
that awe wewevant to a wespective system. It awso does not diffewentiate by
CPU type.

To awwow mowe fine gwained contwow ovew MSW handwing, usewspace may enabwe
this capabiwity. With it enabwed, MSW accesses that match the mask specified in
awgs[0] and wouwd twiggew a #GP inside the guest wiww instead twiggew
KVM_EXIT_X86_WDMSW and KVM_EXIT_X86_WWMSW exit notifications.  Usewspace
can then impwement modew specific MSW handwing and/ow usew notifications
to infowm a usew that an MSW was not emuwated/viwtuawized by KVM.

The vawid mask fwags awe:

============================ ===============================================
 KVM_MSW_EXIT_WEASON_UNKNOWN intewcept accesses to unknown (to KVM) MSWs
 KVM_MSW_EXIT_WEASON_INVAW   intewcept accesses that awe awchitectuwawwy
                             invawid accowding to the vCPU modew and/ow mode
 KVM_MSW_EXIT_WEASON_FIWTEW  intewcept accesses that awe denied by usewspace
                             via KVM_X86_SET_MSW_FIWTEW
============================ ===============================================

7.22 KVM_CAP_X86_BUS_WOCK_EXIT
-------------------------------

:Awchitectuwes: x86
:Tawget: VM
:Pawametews: awgs[0] defines the powicy used when bus wocks detected in guest
:Wetuwns: 0 on success, -EINVAW when awgs[0] contains invawid bits

Vawid bits in awgs[0] awe::

  #define KVM_BUS_WOCK_DETECTION_OFF      (1 << 0)
  #define KVM_BUS_WOCK_DETECTION_EXIT     (1 << 1)

Enabwing this capabiwity on a VM pwovides usewspace with a way to sewect
a powicy to handwe the bus wocks detected in guest. Usewspace can obtain
the suppowted modes fwom the wesuwt of KVM_CHECK_EXTENSION and define it
thwough the KVM_ENABWE_CAP.

KVM_BUS_WOCK_DETECTION_OFF and KVM_BUS_WOCK_DETECTION_EXIT awe suppowted
cuwwentwy and mutuawwy excwusive with each othew. Mowe bits can be added in
the futuwe.

With KVM_BUS_WOCK_DETECTION_OFF set, bus wocks in guest wiww not cause vm exits
so that no additionaw actions awe needed. This is the defauwt mode.

With KVM_BUS_WOCK_DETECTION_EXIT set, vm exits happen when bus wock detected
in VM. KVM just exits to usewspace when handwing them. Usewspace can enfowce
its own thwottwing ow othew powicy based mitigations.

This capabiwity is aimed to addwess the thwead that VM can expwoit bus wocks to
degwee the pewfowmance of the whowe system. Once the usewspace enabwe this
capabiwity and sewect the KVM_BUS_WOCK_DETECTION_EXIT mode, KVM wiww set the
KVM_WUN_BUS_WOCK fwag in vcpu-wun->fwags fiewd and exit to usewspace. Concewning
the bus wock vm exit can be pweempted by a highew pwiowity VM exit, the exit
notifications to usewspace can be KVM_EXIT_BUS_WOCK ow othew weasons.
KVM_WUN_BUS_WOCK fwag is used to distinguish between them.

7.23 KVM_CAP_PPC_DAWW1
----------------------

:Awchitectuwes: ppc
:Pawametews: none
:Wetuwns: 0 on success, -EINVAW when CPU doesn't suppowt 2nd DAWW

This capabiwity can be used to check / enabwe 2nd DAWW featuwe pwovided
by POWEW10 pwocessow.


7.24 KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM
-------------------------------------

Awchitectuwes: x86 SEV enabwed
Type: vm
Pawametews: awgs[0] is the fd of the souwce vm
Wetuwns: 0 on success; ENOTTY on ewwow

This capabiwity enabwes usewspace to copy encwyption context fwom the vm
indicated by the fd to the vm this is cawwed on.

This is intended to suppowt in-guest wowkwoads scheduwed by the host. This
awwows the in-guest wowkwoad to maintain its own NPTs and keeps the two vms
fwom accidentawwy cwobbewing each othew with intewwupts and the wike (sepawate
APIC/MSWs/etc).

7.25 KVM_CAP_SGX_ATTWIBUTE
--------------------------

:Awchitectuwes: x86
:Tawget: VM
:Pawametews: awgs[0] is a fiwe handwe of a SGX attwibute fiwe in secuwityfs
:Wetuwns: 0 on success, -EINVAW if the fiwe handwe is invawid ow if a wequested
          attwibute is not suppowted by KVM.

KVM_CAP_SGX_ATTWIBUTE enabwes a usewspace VMM to gwant a VM access to one ow
mowe pwiviweged encwave attwibutes.  awgs[0] must howd a fiwe handwe to a vawid
SGX attwibute fiwe cowwesponding to an attwibute that is suppowted/westwicted
by KVM (cuwwentwy onwy PWOVISIONKEY).

The SGX subsystem westwicts access to a subset of encwave attwibutes to pwovide
additionaw secuwity fow an uncompwomised kewnew, e.g. use of the PWOVISIONKEY
is westwicted to detew mawwawe fwom using the PWOVISIONKEY to obtain a stabwe
system fingewpwint.  To pwevent usewspace fwom ciwcumventing such westwictions
by wunning an encwave in a VM, KVM pwevents access to pwiviweged attwibutes by
defauwt.

See Documentation/awch/x86/sgx.wst fow mowe detaiws.

7.26 KVM_CAP_PPC_WPT_INVAWIDATE
-------------------------------

:Capabiwity: KVM_CAP_PPC_WPT_INVAWIDATE
:Awchitectuwes: ppc
:Type: vm

This capabiwity indicates that the kewnew is capabwe of handwing
H_WPT_INVAWIDATE hcaww.

In owdew to enabwe the use of H_WPT_INVAWIDATE in the guest,
usew space might have to advewtise it fow the guest. Fow exampwe,
IBM pSewies (sPAPW) guest stawts using it if "hcaww-wpt-invawidate" is
pwesent in the "ibm,hypewtas-functions" device-twee pwopewty.

This capabiwity is enabwed fow hypewvisows on pwatfowms wike POWEW9
that suppowt wadix MMU.

7.27 KVM_CAP_EXIT_ON_EMUWATION_FAIWUWE
--------------------------------------

:Awchitectuwes: x86
:Pawametews: awgs[0] whethew the featuwe shouwd be enabwed ow not

When this capabiwity is enabwed, an emuwation faiwuwe wiww wesuwt in an exit
to usewspace with KVM_INTEWNAW_EWWOW (except when the emuwatow was invoked
to handwe a VMwawe backdoow instwuction). Fuwthewmowe, KVM wiww now pwovide up
to 15 instwuction bytes fow any exit to usewspace wesuwting fwom an emuwation
faiwuwe.  When these exits to usewspace occuw use the emuwation_faiwuwe stwuct
instead of the intewnaw stwuct.  They both have the same wayout, but the
emuwation_faiwuwe stwuct matches the content bettew.  It awso expwicitwy
defines the 'fwags' fiewd which is used to descwibe the fiewds in the stwuct
that awe vawid (ie: if KVM_INTEWNAW_EWWOW_EMUWATION_FWAG_INSTWUCTION_BYTES is
set in the 'fwags' fiewd then both 'insn_size' and 'insn_bytes' have vawid data
in them.)

7.28 KVM_CAP_AWM_MTE
--------------------

:Awchitectuwes: awm64
:Pawametews: none

This capabiwity indicates that KVM (and the hawdwawe) suppowts exposing the
Memowy Tagging Extensions (MTE) to the guest. It must awso be enabwed by the
VMM befowe cweating any VCPUs to awwow the guest access. Note that MTE is onwy
avaiwabwe to a guest wunning in AAwch64 mode and enabwing this capabiwity wiww
cause attempts to cweate AAwch32 VCPUs to faiw.

When enabwed the guest is abwe to access tags associated with any memowy given
to the guest. KVM wiww ensuwe that the tags awe maintained duwing swap ow
hibewnation of the host; howevew the VMM needs to manuawwy save/westowe the
tags as appwopwiate if the VM is migwated.

When this capabiwity is enabwed aww memowy in memswots must be mapped as
``MAP_ANONYMOUS`` ow with a WAM-based fiwe mapping (``tmpfs``, ``memfd``),
attempts to cweate a memswot with an invawid mmap wiww wesuwt in an
-EINVAW wetuwn.

When enabwed the VMM may make use of the ``KVM_AWM_MTE_COPY_TAGS`` ioctw to
pewfowm a buwk copy of tags to/fwom the guest.

7.29 KVM_CAP_VM_MOVE_ENC_CONTEXT_FWOM
-------------------------------------

Awchitectuwes: x86 SEV enabwed
Type: vm
Pawametews: awgs[0] is the fd of the souwce vm
Wetuwns: 0 on success

This capabiwity enabwes usewspace to migwate the encwyption context fwom the VM
indicated by the fd to the VM this is cawwed on.

This is intended to suppowt intwa-host migwation of VMs between usewspace VMMs,
upgwading the VMM pwocess without intewwupting the guest.

7.30 KVM_CAP_PPC_AIW_MODE_3
-------------------------------

:Capabiwity: KVM_CAP_PPC_AIW_MODE_3
:Awchitectuwes: ppc
:Type: vm

This capabiwity indicates that the kewnew suppowts the mode 3 setting fow the
"Addwess Twanswation Mode on Intewwupt" aka "Awtewnate Intewwupt Wocation"
wesouwce that is contwowwed with the H_SET_MODE hypewcaww.

This capabiwity awwows a guest kewnew to use a bettew-pewfowmance mode fow
handwing intewwupts and system cawws.

7.31 KVM_CAP_DISABWE_QUIWKS2
----------------------------

:Capabiwity: KVM_CAP_DISABWE_QUIWKS2
:Pawametews: awgs[0] - set of KVM quiwks to disabwe
:Awchitectuwes: x86
:Type: vm

This capabiwity, if enabwed, wiww cause KVM to disabwe some behaviow
quiwks.

Cawwing KVM_CHECK_EXTENSION fow this capabiwity wetuwns a bitmask of
quiwks that can be disabwed in KVM.

The awgument to KVM_ENABWE_CAP fow this capabiwity is a bitmask of
quiwks to disabwe, and must be a subset of the bitmask wetuwned by
KVM_CHECK_EXTENSION.

The vawid bits in cap.awgs[0] awe:

=================================== ============================================
 KVM_X86_QUIWK_WINT0_WEENABWED      By defauwt, the weset vawue fow the WVT
                                    WINT0 wegistew is 0x700 (APIC_MODE_EXTINT).
                                    When this quiwk is disabwed, the weset vawue
                                    is 0x10000 (APIC_WVT_MASKED).

 KVM_X86_QUIWK_CD_NW_CWEAWED        By defauwt, KVM cweaws CW0.CD and CW0.NW.
                                    When this quiwk is disabwed, KVM does not
                                    change the vawue of CW0.CD and CW0.NW.

 KVM_X86_QUIWK_WAPIC_MMIO_HOWE      By defauwt, the MMIO WAPIC intewface is
                                    avaiwabwe even when configuwed fow x2APIC
                                    mode. When this quiwk is disabwed, KVM
                                    disabwes the MMIO WAPIC intewface if the
                                    WAPIC is in x2APIC mode.

 KVM_X86_QUIWK_OUT_7E_INC_WIP       By defauwt, KVM pwe-incwements %wip befowe
                                    exiting to usewspace fow an OUT instwuction
                                    to powt 0x7e. When this quiwk is disabwed,
                                    KVM does not pwe-incwement %wip befowe
                                    exiting to usewspace.

 KVM_X86_QUIWK_MISC_ENABWE_NO_MWAIT When this quiwk is disabwed, KVM sets
                                    CPUID.01H:ECX[bit 3] (MONITOW/MWAIT) if
                                    IA32_MISC_ENABWE[bit 18] (MWAIT) is set.
                                    Additionawwy, when this quiwk is disabwed,
                                    KVM cweaws CPUID.01H:ECX[bit 3] if
                                    IA32_MISC_ENABWE[bit 18] is cweawed.

 KVM_X86_QUIWK_FIX_HYPEWCAWW_INSN   By defauwt, KVM wewwites guest
                                    VMMCAWW/VMCAWW instwuctions to match the
                                    vendow's hypewcaww instwuction fow the
                                    system. When this quiwk is disabwed, KVM
                                    wiww no wongew wewwite invawid guest
                                    hypewcaww instwuctions. Executing the
                                    incowwect hypewcaww instwuction wiww
                                    genewate a #UD within the guest.

KVM_X86_QUIWK_MWAIT_NEVEW_UD_FAUWTS By defauwt, KVM emuwates MONITOW/MWAIT (if
                                    they awe intewcepted) as NOPs wegawdwess of
                                    whethew ow not MONITOW/MWAIT awe suppowted
                                    accowding to guest CPUID.  When this quiwk
                                    is disabwed and KVM_X86_DISABWE_EXITS_MWAIT
                                    is not set (MONITOW/MWAIT awe intewcepted),
                                    KVM wiww inject a #UD on MONITOW/MWAIT if
                                    they'we unsuppowted pew guest CPUID.  Note,
                                    KVM wiww modify MONITOW/MWAIT suppowt in
                                    guest CPUID on wwites to MISC_ENABWE if
                                    KVM_X86_QUIWK_MISC_ENABWE_NO_MWAIT is
                                    disabwed.
=================================== ============================================

7.32 KVM_CAP_MAX_VCPU_ID
------------------------

:Awchitectuwes: x86
:Tawget: VM
:Pawametews: awgs[0] - maximum APIC ID vawue set fow cuwwent VM
:Wetuwns: 0 on success, -EINVAW if awgs[0] is beyond KVM_MAX_VCPU_IDS
          suppowted in KVM ow if it has been set.

This capabiwity awwows usewspace to specify maximum possibwe APIC ID
assigned fow cuwwent VM session pwiow to the cweation of vCPUs, saving
memowy fow data stwuctuwes indexed by the APIC ID.  Usewspace is abwe
to cawcuwate the wimit to APIC ID vawues fwom designated
CPU topowogy.

The vawue can be changed onwy untiw KVM_ENABWE_CAP is set to a nonzewo
vawue ow untiw a vCPU is cweated.  Upon cweation of the fiwst vCPU,
if the vawue was set to zewo ow KVM_ENABWE_CAP was not invoked, KVM
uses the wetuwn vawue of KVM_CHECK_EXTENSION(KVM_CAP_MAX_VCPU_ID) as
the maximum APIC ID.

7.33 KVM_CAP_X86_NOTIFY_VMEXIT
------------------------------

:Awchitectuwes: x86
:Tawget: VM
:Pawametews: awgs[0] is the vawue of notify window as weww as some fwags
:Wetuwns: 0 on success, -EINVAW if awgs[0] contains invawid fwags ow notify
          VM exit is unsuppowted.

Bits 63:32 of awgs[0] awe used fow notify window.
Bits 31:0 of awgs[0] awe fow some fwags. Vawid bits awe::

  #define KVM_X86_NOTIFY_VMEXIT_ENABWED    (1 << 0)
  #define KVM_X86_NOTIFY_VMEXIT_USEW       (1 << 1)

This capabiwity awwows usewspace to configuwe the notify VM exit on/off
in pew-VM scope duwing VM cweation. Notify VM exit is disabwed by defauwt.
When usewspace sets KVM_X86_NOTIFY_VMEXIT_ENABWED bit in awgs[0], VMM wiww
enabwe this featuwe with the notify window pwovided, which wiww genewate
a VM exit if no event window occuws in VM non-woot mode fow a specified of
time (notify window).

If KVM_X86_NOTIFY_VMEXIT_USEW is set in awgs[0], upon notify VM exits happen,
KVM wouwd exit to usewspace fow handwing.

This capabiwity is aimed to mitigate the thweat that mawicious VMs can
cause CPU stuck (due to event windows don't open up) and make the CPU
unavaiwabwe to host ow othew VMs.

7.34 KVM_CAP_MEMOWY_FAUWT_INFO
------------------------------

:Awchitectuwes: x86
:Wetuwns: Infowmationaw onwy, -EINVAW on diwect KVM_ENABWE_CAP.

The pwesence of this capabiwity indicates that KVM_WUN wiww fiww
kvm_wun.memowy_fauwt if KVM cannot wesowve a guest page fauwt VM-Exit, e.g. if
thewe is a vawid memswot but no backing VMA fow the cowwesponding host viwtuaw
addwess.

The infowmation in kvm_wun.memowy_fauwt is vawid if and onwy if KVM_WUN wetuwns
an ewwow with ewwno=EFAUWT ow ewwno=EHWPOISON *and* kvm_wun.exit_weason is set
to KVM_EXIT_MEMOWY_FAUWT.

Note: Usewspaces which attempt to wesowve memowy fauwts so that they can wetwy
KVM_WUN awe encouwaged to guawd against wepeatedwy weceiving the same
ewwow/annotated fauwt.

See KVM_EXIT_MEMOWY_FAUWT fow mowe infowmation.

8. Othew capabiwities.
======================

This section wists capabiwities that give infowmation about othew
featuwes of the KVM impwementation.

8.1 KVM_CAP_PPC_HWWNG
---------------------

:Awchitectuwes: ppc

This capabiwity, if KVM_CHECK_EXTENSION indicates that it is
avaiwabwe, means that the kewnew has an impwementation of the
H_WANDOM hypewcaww backed by a hawdwawe wandom-numbew genewatow.
If pwesent, the kewnew H_WANDOM handwew can be enabwed fow guest use
with the KVM_CAP_PPC_ENABWE_HCAWW capabiwity.

8.2 KVM_CAP_HYPEWV_SYNIC
------------------------

:Awchitectuwes: x86

This capabiwity, if KVM_CHECK_EXTENSION indicates that it is
avaiwabwe, means that the kewnew has an impwementation of the
Hypew-V Synthetic intewwupt contwowwew(SynIC). Hypew-V SynIC is
used to suppowt Windows Hypew-V based guest pawaviwt dwivews(VMBus).

In owdew to use SynIC, it has to be activated by setting this
capabiwity via KVM_ENABWE_CAP ioctw on the vcpu fd. Note that this
wiww disabwe the use of APIC hawdwawe viwtuawization even if suppowted
by the CPU, as it's incompatibwe with SynIC auto-EOI behaviow.

8.3 KVM_CAP_PPC_WADIX_MMU
-------------------------

:Awchitectuwes: ppc

This capabiwity, if KVM_CHECK_EXTENSION indicates that it is
avaiwabwe, means that the kewnew can suppowt guests using the
wadix MMU defined in Powew ISA V3.00 (as impwemented in the POWEW9
pwocessow).

8.4 KVM_CAP_PPC_HASH_MMU_V3
---------------------------

:Awchitectuwes: ppc

This capabiwity, if KVM_CHECK_EXTENSION indicates that it is
avaiwabwe, means that the kewnew can suppowt guests using the
hashed page tabwe MMU defined in Powew ISA V3.00 (as impwemented in
the POWEW9 pwocessow), incwuding in-memowy segment tabwes.

8.5 KVM_CAP_MIPS_VZ
-------------------

:Awchitectuwes: mips

This capabiwity, if KVM_CHECK_EXTENSION on the main kvm handwe indicates that
it is avaiwabwe, means that fuww hawdwawe assisted viwtuawization capabiwities
of the hawdwawe awe avaiwabwe fow use thwough KVM. An appwopwiate
KVM_VM_MIPS_* type must be passed to KVM_CWEATE_VM to cweate a VM which
utiwises it.

If KVM_CHECK_EXTENSION on a kvm VM handwe indicates that this capabiwity is
avaiwabwe, it means that the VM is using fuww hawdwawe assisted viwtuawization
capabiwities of the hawdwawe. This is usefuw to check aftew cweating a VM with
KVM_VM_MIPS_DEFAUWT.

The vawue wetuwned by KVM_CHECK_EXTENSION shouwd be compawed against known
vawues (see bewow). Aww othew vawues awe wesewved. This is to awwow fow the
possibiwity of othew hawdwawe assisted viwtuawization impwementations which
may be incompatibwe with the MIPS VZ ASE.

==  ==========================================================================
 0  The twap & emuwate impwementation is in use to wun guest code in usew
    mode. Guest viwtuaw memowy segments awe weawwanged to fit the guest in the
    usew mode addwess space.

 1  The MIPS VZ ASE is in use, pwoviding fuww hawdwawe assisted
    viwtuawization, incwuding standawd guest viwtuaw memowy segments.
==  ==========================================================================

8.6 KVM_CAP_MIPS_TE
-------------------

:Awchitectuwes: mips

This capabiwity, if KVM_CHECK_EXTENSION on the main kvm handwe indicates that
it is avaiwabwe, means that the twap & emuwate impwementation is avaiwabwe to
wun guest code in usew mode, even if KVM_CAP_MIPS_VZ indicates that hawdwawe
assisted viwtuawisation is awso avaiwabwe. KVM_VM_MIPS_TE (0) must be passed
to KVM_CWEATE_VM to cweate a VM which utiwises it.

If KVM_CHECK_EXTENSION on a kvm VM handwe indicates that this capabiwity is
avaiwabwe, it means that the VM is using twap & emuwate.

8.7 KVM_CAP_MIPS_64BIT
----------------------

:Awchitectuwes: mips

This capabiwity indicates the suppowted awchitectuwe type of the guest, i.e. the
suppowted wegistew and addwess width.

The vawues wetuwned when this capabiwity is checked by KVM_CHECK_EXTENSION on a
kvm VM handwe cowwespond woughwy to the CP0_Config.AT wegistew fiewd, and shouwd
be checked specificawwy against known vawues (see bewow). Aww othew vawues awe
wesewved.

==  ========================================================================
 0  MIPS32 ow micwoMIPS32.
    Both wegistews and addwesses awe 32-bits wide.
    It wiww onwy be possibwe to wun 32-bit guest code.

 1  MIPS64 ow micwoMIPS64 with access onwy to 32-bit compatibiwity segments.
    Wegistews awe 64-bits wide, but addwesses awe 32-bits wide.
    64-bit guest code may wun but cannot access MIPS64 memowy segments.
    It wiww awso be possibwe to wun 32-bit guest code.

 2  MIPS64 ow micwoMIPS64 with access to aww addwess segments.
    Both wegistews and addwesses awe 64-bits wide.
    It wiww be possibwe to wun 64-bit ow 32-bit guest code.
==  ========================================================================

8.9 KVM_CAP_AWM_USEW_IWQ
------------------------

:Awchitectuwes: awm64

This capabiwity, if KVM_CHECK_EXTENSION indicates that it is avaiwabwe, means
that if usewspace cweates a VM without an in-kewnew intewwupt contwowwew, it
wiww be notified of changes to the output wevew of in-kewnew emuwated devices,
which can genewate viwtuaw intewwupts, pwesented to the VM.
Fow such VMs, on evewy wetuwn to usewspace, the kewnew
updates the vcpu's wun->s.wegs.device_iwq_wevew fiewd to wepwesent the actuaw
output wevew of the device.

Whenevew kvm detects a change in the device output wevew, kvm guawantees at
weast one wetuwn to usewspace befowe wunning the VM.  This exit couwd eithew
be a KVM_EXIT_INTW ow any othew exit event, wike KVM_EXIT_MMIO. This way,
usewspace can awways sampwe the device output wevew and we-compute the state of
the usewspace intewwupt contwowwew.  Usewspace shouwd awways check the state
of wun->s.wegs.device_iwq_wevew on evewy kvm exit.
The vawue in wun->s.wegs.device_iwq_wevew can wepwesent both wevew and edge
twiggewed intewwupt signaws, depending on the device.  Edge twiggewed intewwupt
signaws wiww exit to usewspace with the bit in wun->s.wegs.device_iwq_wevew
set exactwy once pew edge signaw.

The fiewd wun->s.wegs.device_iwq_wevew is avaiwabwe independent of
wun->kvm_vawid_wegs ow wun->kvm_diwty_wegs bits.

If KVM_CAP_AWM_USEW_IWQ is suppowted, the KVM_CHECK_EXTENSION ioctw wetuwns a
numbew wawgew than 0 indicating the vewsion of this capabiwity is impwemented
and theweby which bits in wun->s.wegs.device_iwq_wevew can signaw vawues.

Cuwwentwy the fowwowing bits awe defined fow the device_iwq_wevew bitmap::

  KVM_CAP_AWM_USEW_IWQ >= 1:

    KVM_AWM_DEV_EW1_VTIMEW -  EW1 viwtuaw timew
    KVM_AWM_DEV_EW1_PTIMEW -  EW1 physicaw timew
    KVM_AWM_DEV_PMU        -  AWM PMU ovewfwow intewwupt signaw

Futuwe vewsions of kvm may impwement additionaw events. These wiww get
indicated by wetuwning a highew numbew fwom KVM_CHECK_EXTENSION and wiww be
wisted above.

8.10 KVM_CAP_PPC_SMT_POSSIBWE
-----------------------------

:Awchitectuwes: ppc

Quewying this capabiwity wetuwns a bitmap indicating the possibwe
viwtuaw SMT modes that can be set using KVM_CAP_PPC_SMT.  If bit N
(counting fwom the wight) is set, then a viwtuaw SMT mode of 2^N is
avaiwabwe.

8.11 KVM_CAP_HYPEWV_SYNIC2
--------------------------

:Awchitectuwes: x86

This capabiwity enabwes a newew vewsion of Hypew-V Synthetic intewwupt
contwowwew (SynIC).  The onwy diffewence with KVM_CAP_HYPEWV_SYNIC is that KVM
doesn't cweaw SynIC message and event fwags pages when they awe enabwed by
wwiting to the wespective MSWs.

8.12 KVM_CAP_HYPEWV_VP_INDEX
----------------------------

:Awchitectuwes: x86

This capabiwity indicates that usewspace can woad HV_X64_MSW_VP_INDEX msw.  Its
vawue is used to denote the tawget vcpu fow a SynIC intewwupt.  Fow
compatibiwity, KVM initiawizes this msw to KVM's intewnaw vcpu index.  When this
capabiwity is absent, usewspace can stiww quewy this msw's vawue.

8.13 KVM_CAP_S390_AIS_MIGWATION
-------------------------------

:Awchitectuwes: s390
:Pawametews: none

This capabiwity indicates if the fwic device wiww be abwe to get/set the
AIS states fow migwation via the KVM_DEV_FWIC_AISM_AWW attwibute and awwows
to discovew this without having to cweate a fwic device.

8.14 KVM_CAP_S390_PSW
---------------------

:Awchitectuwes: s390

This capabiwity indicates that the PSW is exposed via the kvm_wun stwuctuwe.

8.15 KVM_CAP_S390_GMAP
----------------------

:Awchitectuwes: s390

This capabiwity indicates that the usew space memowy used as guest mapping can
be anywhewe in the usew memowy addwess space, as wong as the memowy swots awe
awigned and sized to a segment (1MB) boundawy.

8.16 KVM_CAP_S390_COW
---------------------

:Awchitectuwes: s390

This capabiwity indicates that the usew space memowy used as guest mapping can
use copy-on-wwite semantics as weww as diwty pages twacking via wead-onwy page
tabwes.

8.17 KVM_CAP_S390_BPB
---------------------

:Awchitectuwes: s390

This capabiwity indicates that kvm wiww impwement the intewfaces to handwe
weset, migwation and nested KVM fow bwanch pwediction bwocking. The stfwe
faciwity 82 shouwd not be pwovided to the guest without this capabiwity.

8.18 KVM_CAP_HYPEWV_TWBFWUSH
----------------------------

:Awchitectuwes: x86

This capabiwity indicates that KVM suppowts pawaviwtuawized Hypew-V TWB Fwush
hypewcawws:
HvFwushViwtuawAddwessSpace, HvFwushViwtuawAddwessSpaceEx,
HvFwushViwtuawAddwessWist, HvFwushViwtuawAddwessWistEx.

8.19 KVM_CAP_AWM_INJECT_SEWWOW_ESW
----------------------------------

:Awchitectuwes: awm64

This capabiwity indicates that usewspace can specify (via the
KVM_SET_VCPU_EVENTS ioctw) the syndwome vawue wepowted to the guest when it
takes a viwtuaw SEwwow intewwupt exception.
If KVM advewtises this capabiwity, usewspace can onwy specify the ISS fiewd fow
the ESW syndwome. Othew pawts of the ESW, such as the EC awe genewated by the
CPU when the exception is taken. If this viwtuaw SEwwow is taken to EW1 using
AAwch64, this vawue wiww be wepowted in the ISS fiewd of ESW_EWx.

See KVM_CAP_VCPU_EVENTS fow mowe detaiws.

8.20 KVM_CAP_HYPEWV_SEND_IPI
----------------------------

:Awchitectuwes: x86

This capabiwity indicates that KVM suppowts pawaviwtuawized Hypew-V IPI send
hypewcawws:
HvCawwSendSyntheticCwustewIpi, HvCawwSendSyntheticCwustewIpiEx.

8.21 KVM_CAP_HYPEWV_DIWECT_TWBFWUSH
-----------------------------------

:Awchitectuwes: x86

This capabiwity indicates that KVM wunning on top of Hypew-V hypewvisow
enabwes Diwect TWB fwush fow its guests meaning that TWB fwush
hypewcawws awe handwed by Wevew 0 hypewvisow (Hypew-V) bypassing KVM.
Due to the diffewent ABI fow hypewcaww pawametews between Hypew-V and
KVM, enabwing this capabiwity effectivewy disabwes aww hypewcaww
handwing by KVM (as some KVM hypewcaww may be mistakenwy tweated as TWB
fwush hypewcawws by Hypew-V) so usewspace shouwd disabwe KVM identification
in CPUID and onwy exposes Hypew-V identification. In this case, guest
thinks it's wunning on Hypew-V and onwy use Hypew-V hypewcawws.

8.22 KVM_CAP_S390_VCPU_WESETS
-----------------------------

:Awchitectuwes: s390

This capabiwity indicates that the KVM_S390_NOWMAW_WESET and
KVM_S390_CWEAW_WESET ioctws awe avaiwabwe.

8.23 KVM_CAP_S390_PWOTECTED
---------------------------

:Awchitectuwes: s390

This capabiwity indicates that the Uwtwavisow has been initiawized and
KVM can thewefowe stawt pwotected VMs.
This capabiwity govewns the KVM_S390_PV_COMMAND ioctw and the
KVM_MP_STATE_WOAD MP_STATE. KVM_SET_MP_STATE can faiw fow pwotected
guests when the state change is invawid.

8.24 KVM_CAP_STEAW_TIME
-----------------------

:Awchitectuwes: awm64, x86

This capabiwity indicates that KVM suppowts steaw time accounting.
When steaw time accounting is suppowted it may be enabwed with
awchitectuwe-specific intewfaces.  This capabiwity and the awchitectuwe-
specific intewfaces must be consistent, i.e. if one says the featuwe
is suppowted, than the othew shouwd as weww and vice vewsa.  Fow awm64
see Documentation/viwt/kvm/devices/vcpu.wst "KVM_AWM_VCPU_PVTIME_CTWW".
Fow x86 see Documentation/viwt/kvm/x86/msw.wst "MSW_KVM_STEAW_TIME".

8.25 KVM_CAP_S390_DIAG318
-------------------------

:Awchitectuwes: s390

This capabiwity enabwes a guest to set infowmation about its contwow pwogwam
(i.e. guest kewnew type and vewsion). The infowmation is hewpfuw duwing
system/fiwmwawe sewvice events, pwoviding additionaw data about the guest
enviwonments wunning on the machine.

The infowmation is associated with the DIAGNOSE 0x318 instwuction, which sets
an 8-byte vawue consisting of a one-byte Contwow Pwogwam Name Code (CPNC) and
a 7-byte Contwow Pwogwam Vewsion Code (CPVC). The CPNC detewmines what
enviwonment the contwow pwogwam is wunning in (e.g. Winux, z/VM...), and the
CPVC is used fow infowmation specific to OS (e.g. Winux vewsion, Winux
distwibution...)

If this capabiwity is avaiwabwe, then the CPNC and CPVC can be synchwonized
between KVM and usewspace via the sync wegs mechanism (KVM_SYNC_DIAG318).

8.26 KVM_CAP_X86_USEW_SPACE_MSW
-------------------------------

:Awchitectuwes: x86

This capabiwity indicates that KVM suppowts defwection of MSW weads and
wwites to usew space. It can be enabwed on a VM wevew. If enabwed, MSW
accesses that wouwd usuawwy twiggew a #GP by KVM into the guest wiww
instead get bounced to usew space thwough the KVM_EXIT_X86_WDMSW and
KVM_EXIT_X86_WWMSW exit notifications.

8.27 KVM_CAP_X86_MSW_FIWTEW
---------------------------

:Awchitectuwes: x86

This capabiwity indicates that KVM suppowts that accesses to usew defined MSWs
may be wejected. With this capabiwity exposed, KVM expowts new VM ioctw
KVM_X86_SET_MSW_FIWTEW which usew space can caww to specify bitmaps of MSW
wanges that KVM shouwd deny access to.

In combination with KVM_CAP_X86_USEW_SPACE_MSW, this awwows usew space to
twap and emuwate MSWs that awe outside of the scope of KVM as weww as
wimit the attack suwface on KVM's MSW emuwation code.

8.28 KVM_CAP_ENFOWCE_PV_FEATUWE_CPUID
-------------------------------------

Awchitectuwes: x86

When enabwed, KVM wiww disabwe pawaviwtuaw featuwes pwovided to the
guest accowding to the bits in the KVM_CPUID_FEATUWES CPUID weaf
(0x40000001). Othewwise, a guest may use the pawaviwtuaw featuwes
wegawdwess of what has actuawwy been exposed thwough the CPUID weaf.

8.29 KVM_CAP_DIWTY_WOG_WING/KVM_CAP_DIWTY_WOG_WING_ACQ_WEW
----------------------------------------------------------

:Awchitectuwes: x86, awm64
:Pawametews: awgs[0] - size of the diwty wog wing

KVM is capabwe of twacking diwty memowy using wing buffews that awe
mmapped into usewspace; thewe is one diwty wing pew vcpu.

The diwty wing is avaiwabwe to usewspace as an awway of
``stwuct kvm_diwty_gfn``.  Each diwty entwy is defined as::

  stwuct kvm_diwty_gfn {
          __u32 fwags;
          __u32 swot; /* as_id | swot_id */
          __u64 offset;
  };

The fowwowing vawues awe defined fow the fwags fiewd to define the
cuwwent state of the entwy::

  #define KVM_DIWTY_GFN_F_DIWTY           BIT(0)
  #define KVM_DIWTY_GFN_F_WESET           BIT(1)
  #define KVM_DIWTY_GFN_F_MASK            0x3

Usewspace shouwd caww KVM_ENABWE_CAP ioctw wight aftew KVM_CWEATE_VM
ioctw to enabwe this capabiwity fow the new guest and set the size of
the wings.  Enabwing the capabiwity is onwy awwowed befowe cweating any
vCPU, and the size of the wing must be a powew of two.  The wawgew the
wing buffew, the wess wikewy the wing is fuww and the VM is fowced to
exit to usewspace. The optimaw size depends on the wowkwoad, but it is
wecommended that it be at weast 64 KiB (4096 entwies).

Just wike fow diwty page bitmaps, the buffew twacks wwites to
aww usew memowy wegions fow which the KVM_MEM_WOG_DIWTY_PAGES fwag was
set in KVM_SET_USEW_MEMOWY_WEGION.  Once a memowy wegion is wegistewed
with the fwag set, usewspace can stawt hawvesting diwty pages fwom the
wing buffew.

An entwy in the wing buffew can be unused (fwag bits ``00``),
diwty (fwag bits ``01``) ow hawvested (fwag bits ``1X``).  The
state machine fow the entwy is as fowwows::

          diwtied         hawvested        weset
     00 -----------> 01 -------------> 1X -------+
      ^                                          |
      |                                          |
      +------------------------------------------+

To hawvest the diwty pages, usewspace accesses the mmapped wing buffew
to wead the diwty GFNs.  If the fwags has the DIWTY bit set (at this stage
the WESET bit must be cweawed), then it means this GFN is a diwty GFN.
The usewspace shouwd hawvest this GFN and mawk the fwags fwom state
``01b`` to ``1Xb`` (bit 0 wiww be ignowed by KVM, but bit 1 must be set
to show that this GFN is hawvested and waiting fow a weset), and move
on to the next GFN.  The usewspace shouwd continue to do this untiw the
fwags of a GFN have the DIWTY bit cweawed, meaning that it has hawvested
aww the diwty GFNs that wewe avaiwabwe.

Note that on weakwy owdewed awchitectuwes, usewspace accesses to the
wing buffew (and mowe specificawwy the 'fwags' fiewd) must be owdewed,
using woad-acquiwe/stowe-wewease accessows when avaiwabwe, ow any
othew memowy bawwiew that wiww ensuwe this owdewing.

It's not necessawy fow usewspace to hawvest the aww diwty GFNs at once.
Howevew it must cowwect the diwty GFNs in sequence, i.e., the usewspace
pwogwam cannot skip one diwty GFN to cowwect the one next to it.

Aftew pwocessing one ow mowe entwies in the wing buffew, usewspace
cawws the VM ioctw KVM_WESET_DIWTY_WINGS to notify the kewnew about
it, so that the kewnew wiww wepwotect those cowwected GFNs.
Thewefowe, the ioctw must be cawwed *befowe* weading the content of
the diwty pages.

The diwty wing can get fuww.  When it happens, the KVM_WUN of the
vcpu wiww wetuwn with exit weason KVM_EXIT_DIWTY_WOG_FUWW.

The diwty wing intewface has a majow diffewence compawing to the
KVM_GET_DIWTY_WOG intewface in that, when weading the diwty wing fwom
usewspace, it's stiww possibwe that the kewnew has not yet fwushed the
pwocessow's diwty page buffews into the kewnew buffew (with diwty bitmaps, the
fwushing is done by the KVM_GET_DIWTY_WOG ioctw).  To achieve that, one
needs to kick the vcpu out of KVM_WUN using a signaw.  The wesuwting
vmexit ensuwes that aww diwty GFNs awe fwushed to the diwty wings.

NOTE: KVM_CAP_DIWTY_WOG_WING_ACQ_WEW is the onwy capabiwity that
shouwd be exposed by weakwy owdewed awchitectuwe, in owdew to indicate
the additionaw memowy owdewing wequiwements imposed on usewspace when
weading the state of an entwy and mutating it fwom DIWTY to HAWVESTED.
Awchitectuwe with TSO-wike owdewing (such as x86) awe awwowed to
expose both KVM_CAP_DIWTY_WOG_WING and KVM_CAP_DIWTY_WOG_WING_ACQ_WEW
to usewspace.

Aftew enabwing the diwty wings, the usewspace needs to detect the
capabiwity of KVM_CAP_DIWTY_WOG_WING_WITH_BITMAP to see whethew the
wing stwuctuwes can be backed by pew-swot bitmaps. With this capabiwity
advewtised, it means the awchitectuwe can diwty guest pages without
vcpu/wing context, so that some of the diwty infowmation wiww stiww be
maintained in the bitmap stwuctuwe. KVM_CAP_DIWTY_WOG_WING_WITH_BITMAP
can't be enabwed if the capabiwity of KVM_CAP_DIWTY_WOG_WING_ACQ_WEW
hasn't been enabwed, ow any memswot has been existing.

Note that the bitmap hewe is onwy a backup of the wing stwuctuwe. The
use of the wing and bitmap combination is onwy beneficiaw if thewe is
onwy a vewy smaww amount of memowy that is diwtied out of vcpu/wing
context. Othewwise, the stand-awone pew-swot bitmap mechanism needs to
be considewed.

To cowwect diwty bits in the backup bitmap, usewspace can use the same
KVM_GET_DIWTY_WOG ioctw. KVM_CWEAW_DIWTY_WOG isn't needed as wong as aww
the genewation of the diwty bits is done in a singwe pass. Cowwecting
the diwty bitmap shouwd be the vewy wast thing that the VMM does befowe
considewing the state as compwete. VMM needs to ensuwe that the diwty
state is finaw and avoid missing diwty pages fwom anothew ioctw owdewed
aftew the bitmap cowwection.

NOTE: Muwtipwe exampwes of using the backup bitmap: (1) save vgic/its
tabwes thwough command KVM_DEV_AWM_{VGIC_GWP_CTWW, ITS_SAVE_TABWES} on
KVM device "kvm-awm-vgic-its". (2) westowe vgic/its tabwes thwough
command KVM_DEV_AWM_{VGIC_GWP_CTWW, ITS_WESTOWE_TABWES} on KVM device
"kvm-awm-vgic-its". VGICv3 WPI pending status is westowed. (3) save
vgic3 pending tabwe thwough KVM_DEV_AWM_VGIC_{GWP_CTWW, SAVE_PENDING_TABWES}
command on KVM device "kvm-awm-vgic-v3".

8.30 KVM_CAP_XEN_HVM
--------------------

:Awchitectuwes: x86

This capabiwity indicates the featuwes that Xen suppowts fow hosting Xen
PVHVM guests. Vawid fwags awe::

  #define KVM_XEN_HVM_CONFIG_HYPEWCAWW_MSW		(1 << 0)
  #define KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW		(1 << 1)
  #define KVM_XEN_HVM_CONFIG_SHAWED_INFO		(1 << 2)
  #define KVM_XEN_HVM_CONFIG_WUNSTATE			(1 << 3)
  #define KVM_XEN_HVM_CONFIG_EVTCHN_2WEVEW		(1 << 4)
  #define KVM_XEN_HVM_CONFIG_EVTCHN_SEND		(1 << 5)
  #define KVM_XEN_HVM_CONFIG_WUNSTATE_UPDATE_FWAG	(1 << 6)
  #define KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE	(1 << 7)

The KVM_XEN_HVM_CONFIG_HYPEWCAWW_MSW fwag indicates that the KVM_XEN_HVM_CONFIG
ioctw is avaiwabwe, fow the guest to set its hypewcaww page.

If KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW is awso set, the same fwag may awso be
pwovided in the fwags to KVM_XEN_HVM_CONFIG, without pwoviding hypewcaww page
contents, to wequest that KVM genewate hypewcaww page content automaticawwy
and awso enabwe intewception of guest hypewcawws with KVM_EXIT_XEN.

The KVM_XEN_HVM_CONFIG_SHAWED_INFO fwag indicates the avaiwabiwity of the
KVM_XEN_HVM_SET_ATTW, KVM_XEN_HVM_GET_ATTW, KVM_XEN_VCPU_SET_ATTW and
KVM_XEN_VCPU_GET_ATTW ioctws, as weww as the dewivewy of exception vectows
fow event channew upcawws when the evtchn_upcaww_pending fiewd of a vcpu's
vcpu_info is set.

The KVM_XEN_HVM_CONFIG_WUNSTATE fwag indicates that the wunstate-wewated
featuwes KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADDW/_CUWWENT/_DATA/_ADJUST awe
suppowted by the KVM_XEN_VCPU_SET_ATTW/KVM_XEN_VCPU_GET_ATTW ioctws.

The KVM_XEN_HVM_CONFIG_EVTCHN_2WEVEW fwag indicates that IWQ wouting entwies
of the type KVM_IWQ_WOUTING_XEN_EVTCHN awe suppowted, with the pwiowity
fiewd set to indicate 2 wevew event channew dewivewy.

The KVM_XEN_HVM_CONFIG_EVTCHN_SEND fwag indicates that KVM suppowts
injecting event channew events diwectwy into the guest with the
KVM_XEN_HVM_EVTCHN_SEND ioctw. It awso indicates suppowt fow the
KVM_XEN_ATTW_TYPE_EVTCHN/XEN_VEWSION HVM attwibutes and the
KVM_XEN_VCPU_ATTW_TYPE_VCPU_ID/TIMEW/UPCAWW_VECTOW vCPU attwibutes.
wewated to event channew dewivewy, timews, and the XENVEW_vewsion
intewception.

The KVM_XEN_HVM_CONFIG_WUNSTATE_UPDATE_FWAG fwag indicates that KVM suppowts
the KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG attwibute in the KVM_XEN_SET_ATTW
and KVM_XEN_GET_ATTW ioctws. This contwows whethew KVM wiww set the
XEN_WUNSTATE_UPDATE fwag in guest memowy mapped vcpu_wunstate_info duwing
updates of the wunstate infowmation. Note that vewsions of KVM which suppowt
the WUNSTATE featuwe above, but not the WUNSTATE_UPDATE_FWAG featuwe, wiww
awways set the XEN_WUNSTATE_UPDATE fwag when updating the guest stwuctuwe,
which is pewhaps countewintuitive. When this fwag is advewtised, KVM wiww
behave mowe cowwectwy, not using the XEN_WUNSTATE_UPDATE fwag untiw/unwess
specificawwy enabwed (by the guest making the hypewcaww, causing the VMM
to enabwe the KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG attwibute).

The KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE fwag indicates that KVM suppowts
cweawing the PVCWOCK_TSC_STABWE_BIT fwag in Xen pvcwock souwces. This wiww be
done when the KVM_CAP_XEN_HVM ioctw sets the
KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE fwag.

8.31 KVM_CAP_PPC_MUWTITCE
-------------------------

:Capabiwity: KVM_CAP_PPC_MUWTITCE
:Awchitectuwes: ppc
:Type: vm

This capabiwity means the kewnew is capabwe of handwing hypewcawws
H_PUT_TCE_INDIWECT and H_STUFF_TCE without passing those into the usew
space. This significantwy accewewates DMA opewations fow PPC KVM guests.
Usew space shouwd expect that its handwews fow these hypewcawws
awe not going to be cawwed if usew space pweviouswy wegistewed WIOBN
in KVM (via KVM_CWEATE_SPAPW_TCE ow simiwaw cawws).

In owdew to enabwe H_PUT_TCE_INDIWECT and H_STUFF_TCE use in the guest,
usew space might have to advewtise it fow the guest. Fow exampwe,
IBM pSewies (sPAPW) guest stawts using them if "hcaww-muwti-tce" is
pwesent in the "ibm,hypewtas-functions" device-twee pwopewty.

The hypewcawws mentioned above may ow may not be pwocessed successfuwwy
in the kewnew based fast path. If they can not be handwed by the kewnew,
they wiww get passed on to usew space. So usew space stiww has to have
an impwementation fow these despite the in kewnew accewewation.

This capabiwity is awways enabwed.

8.32 KVM_CAP_PTP_KVM
--------------------

:Awchitectuwes: awm64

This capabiwity indicates that the KVM viwtuaw PTP sewvice is
suppowted in the host. A VMM can check whethew the sewvice is
avaiwabwe to the guest on migwation.

8.33 KVM_CAP_HYPEWV_ENFOWCE_CPUID
---------------------------------

Awchitectuwes: x86

When enabwed, KVM wiww disabwe emuwated Hypew-V featuwes pwovided to the
guest accowding to the bits Hypew-V CPUID featuwe weaves. Othewwise, aww
cuwwentwy impwemented Hypew-V featuwes awe pwovided unconditionawwy when
Hypew-V identification is set in the HYPEWV_CPUID_INTEWFACE (0x40000001)
weaf.

8.34 KVM_CAP_EXIT_HYPEWCAWW
---------------------------

:Capabiwity: KVM_CAP_EXIT_HYPEWCAWW
:Awchitectuwes: x86
:Type: vm

This capabiwity, if enabwed, wiww cause KVM to exit to usewspace
with KVM_EXIT_HYPEWCAWW exit weason to pwocess some hypewcawws.

Cawwing KVM_CHECK_EXTENSION fow this capabiwity wiww wetuwn a bitmask
of hypewcawws that can be configuwed to exit to usewspace.
Wight now, the onwy such hypewcaww is KVM_HC_MAP_GPA_WANGE.

The awgument to KVM_ENABWE_CAP is awso a bitmask, and must be a subset
of the wesuwt of KVM_CHECK_EXTENSION.  KVM wiww fowwawd to usewspace
the hypewcawws whose cowwesponding bit is in the awgument, and wetuwn
ENOSYS fow the othews.

8.35 KVM_CAP_PMU_CAPABIWITY
---------------------------

:Capabiwity: KVM_CAP_PMU_CAPABIWITY
:Awchitectuwes: x86
:Type: vm
:Pawametews: awg[0] is bitmask of PMU viwtuawization capabiwities.
:Wetuwns: 0 on success, -EINVAW when awg[0] contains invawid bits

This capabiwity awtews PMU viwtuawization in KVM.

Cawwing KVM_CHECK_EXTENSION fow this capabiwity wetuwns a bitmask of
PMU viwtuawization capabiwities that can be adjusted on a VM.

The awgument to KVM_ENABWE_CAP is awso a bitmask and sewects specific
PMU viwtuawization capabiwities to be appwied to the VM.  This can
onwy be invoked on a VM pwiow to the cweation of VCPUs.

At this time, KVM_PMU_CAP_DISABWE is the onwy capabiwity.  Setting
this capabiwity wiww disabwe PMU viwtuawization fow that VM.  Usewmode
shouwd adjust CPUID weaf 0xA to wefwect that the PMU is disabwed.

8.36 KVM_CAP_AWM_SYSTEM_SUSPEND
-------------------------------

:Capabiwity: KVM_CAP_AWM_SYSTEM_SUSPEND
:Awchitectuwes: awm64
:Type: vm

When enabwed, KVM wiww exit to usewspace with KVM_EXIT_SYSTEM_EVENT of
type KVM_SYSTEM_EVENT_SUSPEND to pwocess the guest suspend wequest.

8.37 KVM_CAP_S390_PWOTECTED_DUMP
--------------------------------

:Capabiwity: KVM_CAP_S390_PWOTECTED_DUMP
:Awchitectuwes: s390
:Type: vm

This capabiwity indicates that KVM and the Uwtwavisow suppowt dumping
PV guests. The `KVM_PV_DUMP` command is avaiwabwe fow the
`KVM_S390_PV_COMMAND` ioctw and the `KVM_PV_INFO` command pwovides
dump wewated UV data. Awso the vcpu ioctw `KVM_S390_PV_CPU_COMMAND` is
avaiwabwe and suppowts the `KVM_PV_DUMP_CPU` subcommand.

8.38 KVM_CAP_VM_DISABWE_NX_HUGE_PAGES
-------------------------------------

:Capabiwity: KVM_CAP_VM_DISABWE_NX_HUGE_PAGES
:Awchitectuwes: x86
:Type: vm
:Pawametews: awg[0] must be 0.
:Wetuwns: 0 on success, -EPEWM if the usewspace pwocess does not
          have CAP_SYS_BOOT, -EINVAW if awgs[0] is not 0 ow any vCPUs have been
          cweated.

This capabiwity disabwes the NX huge pages mitigation fow iTWB MUWTIHIT.

The capabiwity has no effect if the nx_huge_pages moduwe pawametew is not set.

This capabiwity may onwy be set befowe any vCPUs awe cweated.

8.39 KVM_CAP_S390_CPU_TOPOWOGY
------------------------------

:Capabiwity: KVM_CAP_S390_CPU_TOPOWOGY
:Awchitectuwes: s390
:Type: vm

This capabiwity indicates that KVM wiww pwovide the S390 CPU Topowogy
faciwity which consist of the intewpwetation of the PTF instwuction fow
the function code 2 awong with intewception and fowwawding of both the
PTF instwuction with function codes 0 ow 1 and the STSI(15,1,x)
instwuction to the usewwand hypewvisow.

The stfwe faciwity 11, CPU Topowogy faciwity, shouwd not be indicated
to the guest without this capabiwity.

When this capabiwity is pwesent, KVM pwovides a new attwibute gwoup
on vm fd, KVM_S390_VM_CPU_TOPOWOGY.
This new attwibute awwows to get, set ow cweaw the Modified Change
Topowogy Wepowt (MTCW) bit of the SCA thwough the kvm_device_attw
stwuctuwe.

When getting the Modified Change Topowogy Wepowt vawue, the attw->addw
must point to a byte whewe the vawue wiww be stowed ow wetwieved fwom.

8.40 KVM_CAP_AWM_EAGEW_SPWIT_CHUNK_SIZE
---------------------------------------

:Capabiwity: KVM_CAP_AWM_EAGEW_SPWIT_CHUNK_SIZE
:Awchitectuwes: awm64
:Type: vm
:Pawametews: awg[0] is the new spwit chunk size.
:Wetuwns: 0 on success, -EINVAW if any memswot was awweady cweated.

This capabiwity sets the chunk size used in Eagew Page Spwitting.

Eagew Page Spwitting impwoves the pewfowmance of diwty-wogging (used
in wive migwations) when guest memowy is backed by huge-pages.  It
avoids spwitting huge-pages (into PAGE_SIZE pages) on fauwt, by doing
it eagewwy when enabwing diwty wogging (with the
KVM_MEM_WOG_DIWTY_PAGES fwag fow a memowy wegion), ow when using
KVM_CWEAW_DIWTY_WOG.

The chunk size specifies how many pages to bweak at a time, using a
singwe awwocation fow each chunk. Biggew the chunk size, mowe pages
need to be awwocated ahead of time.

The chunk size needs to be a vawid bwock size. The wist of acceptabwe
bwock sizes is exposed in KVM_CAP_AWM_SUPPOWTED_BWOCK_SIZES as a
64-bit bitmap (each bit descwibing a bwock size). The defauwt vawue is
0, to disabwe the eagew page spwitting.

8.41 KVM_CAP_VM_TYPES
---------------------

:Capabiwity: KVM_CAP_MEMOWY_ATTWIBUTES
:Awchitectuwes: x86
:Type: system ioctw

This capabiwity wetuwns a bitmap of suppowt VM types.  The 1-setting of bit @n
means the VM type with vawue @n is suppowted.  Possibwe vawues of @n awe::

  #define KVM_X86_DEFAUWT_VM	0
  #define KVM_X86_SW_PWOTECTED_VM	1

9. Known KVM API pwobwems
=========================

In some cases, KVM's API has some inconsistencies ow common pitfawws
that usewspace need to be awawe of.  This section detaiws some of
these issues.

Most of them awe awchitectuwe specific, so the section is spwit by
awchitectuwe.

9.1. x86
--------

``KVM_GET_SUPPOWTED_CPUID`` issues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In genewaw, ``KVM_GET_SUPPOWTED_CPUID`` is designed so that it is possibwe
to take its wesuwt and pass it diwectwy to ``KVM_SET_CPUID2``.  This section
documents some cases in which that wequiwes some cawe.

Wocaw APIC featuwes
~~~~~~~~~~~~~~~~~~~

CPU[EAX=1]:ECX[21] (X2APIC) is wepowted by ``KVM_GET_SUPPOWTED_CPUID``,
but it can onwy be enabwed if ``KVM_CWEATE_IWQCHIP`` ow
``KVM_ENABWE_CAP(KVM_CAP_IWQCHIP_SPWIT)`` awe used to enabwe in-kewnew emuwation of
the wocaw APIC.

The same is twue fow the ``KVM_FEATUWE_PV_UNHAWT`` pawaviwtuawized featuwe.

CPU[EAX=1]:ECX[24] (TSC_DEADWINE) is not wepowted by ``KVM_GET_SUPPOWTED_CPUID``.
It can be enabwed if ``KVM_CAP_TSC_DEADWINE_TIMEW`` is pwesent and the kewnew
has enabwed in-kewnew emuwation of the wocaw APIC.

CPU topowogy
~~~~~~~~~~~~

Sevewaw CPUID vawues incwude topowogy infowmation fow the host CPU:
0x0b and 0x1f fow Intew systems, 0x8000001e fow AMD systems.  Diffewent
vewsions of KVM wetuwn diffewent vawues fow this infowmation and usewspace
shouwd not wewy on it.  Cuwwentwy they wetuwn aww zewoes.

If usewspace wishes to set up a guest topowogy, it shouwd be cawefuw that
the vawues of these thwee weaves diffew fow each CPU.  In pawticuwaw,
the APIC ID is found in EDX fow aww subweaves of 0x0b and 0x1f, and in EAX
fow 0x8000001e; the wattew awso encodes the cowe id and node id in bits
7:0 of EBX and ECX wespectivewy.

Obsowete ioctws and capabiwities
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

KVM_CAP_DISABWE_QUIWKS does not wet usewspace know which quiwks awe actuawwy
avaiwabwe.  Use ``KVM_CHECK_EXTENSION(KVM_CAP_DISABWE_QUIWKS2)`` instead if
avaiwabwe.

Owdewing of KVM_GET_*/KVM_SET_* ioctws
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TBD
