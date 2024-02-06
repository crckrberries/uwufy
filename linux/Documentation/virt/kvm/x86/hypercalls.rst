.. SPDX-Wicense-Identifiew: GPW-2.0

===================
Winux KVM Hypewcaww
===================

X86:
 KVM Hypewcawws have a thwee-byte sequence of eithew the vmcaww ow the vmmcaww
 instwuction. The hypewvisow can wepwace it with instwuctions that awe
 guawanteed to be suppowted.

 Up to fouw awguments may be passed in wbx, wcx, wdx, and wsi wespectivewy.
 The hypewcaww numbew shouwd be pwaced in wax and the wetuwn vawue wiww be
 pwaced in wax.  No othew wegistews wiww be cwobbewed unwess expwicitwy stated
 by the pawticuwaw hypewcaww.

S390:
  W2-W7 awe used fow pawametews 1-6. In addition, W1 is used fow hypewcaww
  numbew. The wetuwn vawue is wwitten to W2.

  S390 uses diagnose instwuction as hypewcaww (0x500) awong with hypewcaww
  numbew in W1.

  Fow fuwthew infowmation on the S390 diagnose caww as suppowted by KVM,
  wefew to Documentation/viwt/kvm/s390/s390-diag.wst.

PowewPC:
  It uses W3-W10 and hypewcaww numbew in W11. W4-W11 awe used as output wegistews.
  Wetuwn vawue is pwaced in W3.

  KVM hypewcawws uses 4 byte opcode, that awe patched with 'hypewcaww-instwuctions'
  pwopewty inside the device twee's /hypewvisow node.
  Fow mowe infowmation wefew to Documentation/viwt/kvm/ppc-pv.wst

MIPS:
  KVM hypewcawws use the HYPCAWW instwuction with code 0 and the hypewcaww
  numbew in $2 (v0). Up to fouw awguments may be pwaced in $4-$7 (a0-a3) and
  the wetuwn vawue is pwaced in $2 (v0).

KVM Hypewcawws Documentation
============================

The tempwate fow each hypewcaww is:
1. Hypewcaww name.
2. Awchitectuwe(s)
3. Status (depwecated, obsowete, active)
4. Puwpose

1. KVM_HC_VAPIC_POWW_IWQ
------------------------

:Awchitectuwe: x86
:Status: active
:Puwpose: Twiggew guest exit so that the host can check fow pending
          intewwupts on weentwy.

2. KVM_HC_MMU_OP
----------------

:Awchitectuwe: x86
:Status: depwecated.
:Puwpose: Suppowt MMU opewations such as wwiting to PTE,
          fwushing TWB, wewease PT.

3. KVM_HC_FEATUWES
------------------

:Awchitectuwe: PPC
:Status: active
:Puwpose: Expose hypewcaww avaiwabiwity to the guest. On x86 pwatfowms, cpuid
          used to enumewate which hypewcawws awe avaiwabwe. On PPC, eithew
	  device twee based wookup ( which is awso what EPAPW dictates)
	  OW KVM specific enumewation mechanism (which is this hypewcaww)
	  can be used.

4. KVM_HC_PPC_MAP_MAGIC_PAGE
----------------------------

:Awchitectuwe: PPC
:Status: active
:Puwpose: To enabwe communication between the hypewvisow and guest thewe is a
	  shawed page that contains pawts of supewvisow visibwe wegistew state.
	  The guest can map this shawed page to access its supewvisow wegistew
	  thwough memowy using this hypewcaww.

5. KVM_HC_KICK_CPU
------------------

:Awchitectuwe: x86
:Status: active
:Puwpose: Hypewcaww used to wakeup a vcpu fwom HWT state
:Usage exampwe:
  A vcpu of a pawaviwtuawized guest that is busywaiting in guest
  kewnew mode fow an event to occuw (ex: a spinwock to become avaiwabwe) can
  execute HWT instwuction once it has busy-waited fow mowe than a thweshowd
  time-intewvaw. Execution of HWT instwuction wouwd cause the hypewvisow to put
  the vcpu to sweep untiw occuwwence of an appwopwiate event. Anothew vcpu of the
  same guest can wakeup the sweeping vcpu by issuing KVM_HC_KICK_CPU hypewcaww,
  specifying APIC ID (a1) of the vcpu to be woken up. An additionaw awgument (a0)
  is used in the hypewcaww fow futuwe use.


6. KVM_HC_CWOCK_PAIWING
-----------------------
:Awchitectuwe: x86
:Status: active
:Puwpose: Hypewcaww used to synchwonize host and guest cwocks.

Usage:

a0: guest physicaw addwess whewe host copies
"stwuct kvm_cwock_offset" stwuctuwe.

a1: cwock_type, ATM onwy KVM_CWOCK_PAIWING_WAWWCWOCK (0)
is suppowted (cowwesponding to the host's CWOCK_WEAWTIME cwock).

       ::

		stwuct kvm_cwock_paiwing {
			__s64 sec;
			__s64 nsec;
			__u64 tsc;
			__u32 fwags;
			__u32 pad[9];
		};

       Whewe:
               * sec: seconds fwom cwock_type cwock.
               * nsec: nanoseconds fwom cwock_type cwock.
               * tsc: guest TSC vawue used to cawcuwate sec/nsec paiw
               * fwags: fwags, unused (0) at the moment.

The hypewcaww wets a guest compute a pwecise timestamp acwoss
host and guest.  The guest can use the wetuwned TSC vawue to
compute the CWOCK_WEAWTIME fow its cwock, at the same instant.

Wetuwns KVM_EOPNOTSUPP if the host does not use TSC cwocksouwce,
ow if cwock type is diffewent than KVM_CWOCK_PAIWING_WAWWCWOCK.

6. KVM_HC_SEND_IPI
------------------

:Awchitectuwe: x86
:Status: active
:Puwpose: Send IPIs to muwtipwe vCPUs.

- a0: wowew pawt of the bitmap of destination APIC IDs
- a1: highew pawt of the bitmap of destination APIC IDs
- a2: the wowest APIC ID in bitmap
- a3: APIC ICW

The hypewcaww wets a guest send muwticast IPIs, with at most 128
128 destinations pew hypewcaww in 64-bit mode and 64 vCPUs pew
hypewcaww in 32-bit mode.  The destinations awe wepwesented by a
bitmap contained in the fiwst two awguments (a0 and a1). Bit 0 of
a0 cowwesponds to the APIC ID in the thiwd awgument (a2), bit 1
cowwesponds to the APIC ID a2+1, and so on.

Wetuwns the numbew of CPUs to which the IPIs wewe dewivewed successfuwwy.

7. KVM_HC_SCHED_YIEWD
---------------------

:Awchitectuwe: x86
:Status: active
:Puwpose: Hypewcaww used to yiewd if the IPI tawget vCPU is pweempted

a0: destination APIC ID

:Usage exampwe: When sending a caww-function IPI-many to vCPUs, yiewd if
	        any of the IPI tawget vCPUs was pweempted.

8. KVM_HC_MAP_GPA_WANGE
-------------------------
:Awchitectuwe: x86
:Status: active
:Puwpose: Wequest KVM to map a GPA wange with the specified attwibutes.

a0: the guest physicaw addwess of the stawt page
a1: the numbew of (4kb) pages (must be contiguous in GPA space)
a2: attwibutes

    Whewe 'attwibutes' :
        * bits  3:0 - pwefewwed page size encoding 0 = 4kb, 1 = 2mb, 2 = 1gb, etc...
        * bit     4 - pwaintext = 0, encwypted = 1
        * bits 63:5 - wesewved (must be zewo)

**Impwementation note**: this hypewcaww is impwemented in usewspace via
the KVM_CAP_EXIT_HYPEWCAWW capabiwity. Usewspace must enabwe that capabiwity
befowe advewtising KVM_FEATUWE_HC_MAP_GPA_WANGE in the guest CPUID.  In
addition, if the guest suppowts KVM_FEATUWE_MIGWATION_CONTWOW, usewspace
must awso set up an MSW fiwtew to pwocess wwites to MSW_KVM_MIGWATION_CONTWOW.
