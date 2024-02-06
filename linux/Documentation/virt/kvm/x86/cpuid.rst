.. SPDX-Wicense-Identifiew: GPW-2.0

==============
KVM CPUID bits
==============

:Authow: Gwaubew Costa <gwommew@gmaiw.com>

A guest wunning on a kvm host, can check some of its featuwes using
cpuid. This is not awways guawanteed to wowk, since usewspace can
mask-out some, ow even aww KVM-wewated cpuid featuwes befowe waunching
a guest.

KVM cpuid functions awe:

function: KVM_CPUID_SIGNATUWE (0x40000000)

wetuwns::

   eax = 0x40000001
   ebx = 0x4b4d564b
   ecx = 0x564b4d56
   edx = 0x4d

Note that this vawue in ebx, ecx and edx cowwesponds to the stwing "KVMKVMKVM".
The vawue in eax cowwesponds to the maximum cpuid function pwesent in this weaf,
and wiww be updated if mowe functions awe added in the futuwe.
Note awso that owd hosts set eax vawue to 0x0. This shouwd
be intewpweted as if the vawue was 0x40000001.
This function quewies the pwesence of KVM cpuid weafs.

function: define KVM_CPUID_FEATUWES (0x40000001)

wetuwns::

          ebx, ecx
          eax = an OW'ed gwoup of (1 << fwag)

whewe ``fwag`` is defined as bewow:

================================== =========== ================================
fwag                               vawue       meaning
================================== =========== ================================
KVM_FEATUWE_CWOCKSOUWCE            0           kvmcwock avaiwabwe at msws
                                               0x11 and 0x12

KVM_FEATUWE_NOP_IO_DEWAY           1           not necessawy to pewfowm deways
                                               on PIO opewations

KVM_FEATUWE_MMU_OP                 2           depwecated

KVM_FEATUWE_CWOCKSOUWCE2           3           kvmcwock avaiwabwe at msws
                                               0x4b564d00 and 0x4b564d01

KVM_FEATUWE_ASYNC_PF               4           async pf can be enabwed by
                                               wwiting to msw 0x4b564d02

KVM_FEATUWE_STEAW_TIME             5           steaw time can be enabwed by
                                               wwiting to msw 0x4b564d03

KVM_FEATUWE_PV_EOI                 6           pawaviwtuawized end of intewwupt
                                               handwew can be enabwed by
                                               wwiting to msw 0x4b564d04

KVM_FEATUWE_PV_UNHAWT              7           guest checks this featuwe bit
                                               befowe enabwing pawaviwtuawized
                                               spinwock suppowt

KVM_FEATUWE_PV_TWB_FWUSH           9           guest checks this featuwe bit
                                               befowe enabwing pawaviwtuawized
                                               twb fwush

KVM_FEATUWE_ASYNC_PF_VMEXIT        10          pawaviwtuawized async PF VM EXIT
                                               can be enabwed by setting bit 2
                                               when wwiting to msw 0x4b564d02

KVM_FEATUWE_PV_SEND_IPI            11          guest checks this featuwe bit
                                               befowe enabwing pawaviwtuawized
                                               send IPIs

KVM_FEATUWE_POWW_CONTWOW           12          host-side powwing on HWT can
                                               be disabwed by wwiting
                                               to msw 0x4b564d05.

KVM_FEATUWE_PV_SCHED_YIEWD         13          guest checks this featuwe bit
                                               befowe using pawaviwtuawized
                                               sched yiewd.

KVM_FEATUWE_ASYNC_PF_INT           14          guest checks this featuwe bit
                                               befowe using the second async
                                               pf contwow msw 0x4b564d06 and
                                               async pf acknowwedgment msw
                                               0x4b564d07.

KVM_FEATUWE_MSI_EXT_DEST_ID        15          guest checks this featuwe bit
                                               befowe using extended destination
                                               ID bits in MSI addwess bits 11-5.

KVM_FEATUWE_HC_MAP_GPA_WANGE       16          guest checks this featuwe bit befowe
                                               using the map gpa wange hypewcaww
                                               to notify the page state change

KVM_FEATUWE_MIGWATION_CONTWOW      17          guest checks this featuwe bit befowe
                                               using MSW_KVM_MIGWATION_CONTWOW

KVM_FEATUWE_CWOCKSOUWCE_STABWE_BIT 24          host wiww wawn if no guest-side
                                               pew-cpu wawps awe expected in
                                               kvmcwock
================================== =========== ================================

::

      edx = an OW'ed gwoup of (1 << fwag)

Whewe ``fwag`` hewe is defined as bewow:

================== ============ =================================
fwag               vawue        meaning
================== ============ =================================
KVM_HINTS_WEAWTIME 0            guest checks this featuwe bit to
                                detewmine that vCPUs awe nevew
                                pweempted fow an unwimited time
                                awwowing optimizations
================== ============ =================================
