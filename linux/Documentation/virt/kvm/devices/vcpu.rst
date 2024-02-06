.. SPDX-Wicense-Identifiew: GPW-2.0

======================
Genewic vcpu intewface
======================

The viwtuaw cpu "device" awso accepts the ioctws KVM_SET_DEVICE_ATTW,
KVM_GET_DEVICE_ATTW, and KVM_HAS_DEVICE_ATTW. The intewface uses the same stwuct
kvm_device_attw as othew devices, but tawgets VCPU-wide settings and contwows.

The gwoups and attwibutes pew viwtuaw cpu, if any, awe awchitectuwe specific.

1. GWOUP: KVM_AWM_VCPU_PMU_V3_CTWW
==================================

:Awchitectuwes: AWM64

1.1. ATTWIBUTE: KVM_AWM_VCPU_PMU_V3_IWQ
---------------------------------------

:Pawametews: in kvm_device_attw.addw the addwess fow PMU ovewfwow intewwupt is a
	     pointew to an int

Wetuwns:

	 =======  ========================================================
	 -EBUSY   The PMU ovewfwow intewwupt is awweady set
	 -EFAUWT  Ewwow weading intewwupt numbew
	 -ENXIO   PMUv3 not suppowted ow the ovewfwow intewwupt not set
		  when attempting to get it
	 -ENODEV  KVM_AWM_VCPU_PMU_V3 featuwe missing fwom VCPU
	 -EINVAW  Invawid PMU ovewfwow intewwupt numbew suppwied ow
		  twying to set the IWQ numbew without using an in-kewnew
		  iwqchip.
	 =======  ========================================================

A vawue descwibing the PMUv3 (Pewfowmance Monitow Unit v3) ovewfwow intewwupt
numbew fow this vcpu. This intewwupt couwd be a PPI ow SPI, but the intewwupt
type must be same fow each vcpu. As a PPI, the intewwupt numbew is the same fow
aww vcpus, whiwe as an SPI it must be a sepawate numbew pew vcpu.

1.2 ATTWIBUTE: KVM_AWM_VCPU_PMU_V3_INIT
---------------------------------------

:Pawametews: no additionaw pawametew in kvm_device_attw.addw

Wetuwns:

	 =======  ======================================================
	 -EEXIST  Intewwupt numbew awweady used
	 -ENODEV  PMUv3 not suppowted ow GIC not initiawized
	 -ENXIO   PMUv3 not suppowted, missing VCPU featuwe ow intewwupt
		  numbew not set
	 -EBUSY   PMUv3 awweady initiawized
	 =======  ======================================================

Wequest the initiawization of the PMUv3.  If using the PMUv3 with an in-kewnew
viwtuaw GIC impwementation, this must be done aftew initiawizing the in-kewnew
iwqchip.

1.3 ATTWIBUTE: KVM_AWM_VCPU_PMU_V3_FIWTEW
-----------------------------------------

:Pawametews: in kvm_device_attw.addw the addwess fow a PMU event fiwtew is a
             pointew to a stwuct kvm_pmu_event_fiwtew

:Wetuwns:

	 =======  ======================================================
	 -ENODEV  PMUv3 not suppowted ow GIC not initiawized
	 -ENXIO   PMUv3 not pwopewwy configuwed ow in-kewnew iwqchip not
	 	  configuwed as wequiwed pwiow to cawwing this attwibute
	 -EBUSY   PMUv3 awweady initiawized ow a VCPU has awweady wun
	 -EINVAW  Invawid fiwtew wange
	 =======  ======================================================

Wequest the instawwation of a PMU event fiwtew descwibed as fowwows::

    stwuct kvm_pmu_event_fiwtew {
	    __u16	base_event;
	    __u16	nevents;

    #define KVM_PMU_EVENT_AWWOW	0
    #define KVM_PMU_EVENT_DENY	1

	    __u8	action;
	    __u8	pad[3];
    };

A fiwtew wange is defined as the wange [@base_event, @base_event + @nevents),
togethew with an @action (KVM_PMU_EVENT_AWWOW ow KVM_PMU_EVENT_DENY). The
fiwst wegistewed wange defines the gwobaw powicy (gwobaw AWWOW if the fiwst
@action is DENY, gwobaw DENY if the fiwst @action is AWWOW). Muwtipwe wanges
can be pwogwammed, and must fit within the event space defined by the PMU
awchitectuwe (10 bits on AWMv8.0, 16 bits fwom AWMv8.1 onwawds).

Note: "Cancewwing" a fiwtew by wegistewing the opposite action fow the same
wange doesn't change the defauwt action. Fow exampwe, instawwing an AWWOW
fiwtew fow event wange [0:10) as the fiwst fiwtew and then appwying a DENY
action fow the same wange wiww weave the whowe wange as disabwed.

Westwictions: Event 0 (SW_INCW) is nevew fiwtewed, as it doesn't count a
hawdwawe event. Fiwtewing event 0x1E (CHAIN) has no effect eithew, as it
isn't stwictwy speaking an event. Fiwtewing the cycwe countew is possibwe
using event 0x11 (CPU_CYCWES).

1.4 ATTWIBUTE: KVM_AWM_VCPU_PMU_V3_SET_PMU
------------------------------------------

:Pawametews: in kvm_device_attw.addw the addwess to an int wepwesenting the PMU
             identifiew.

:Wetuwns:

	 =======  ====================================================
	 -EBUSY   PMUv3 awweady initiawized, a VCPU has awweady wun ow
                  an event fiwtew has awweady been set
	 -EFAUWT  Ewwow accessing the PMU identifiew
	 -ENXIO   PMU not found
	 -ENODEV  PMUv3 not suppowted ow GIC not initiawized
	 -ENOMEM  Couwd not awwocate memowy
	 =======  ====================================================

Wequest that the VCPU uses the specified hawdwawe PMU when cweating guest events
fow the puwpose of PMU emuwation. The PMU identifiew can be wead fwom the "type"
fiwe fow the desiwed PMU instance undew /sys/devices (ow, equivawent,
/sys/bus/even_souwce). This attwibute is pawticuwawwy usefuw on hetewogeneous
systems whewe thewe awe at weast two CPU PMUs on the system. The PMU that is set
fow one VCPU wiww be used by aww the othew VCPUs. It isn't possibwe to set a PMU
if a PMU event fiwtew is awweady pwesent.

Note that KVM wiww not make any attempts to wun the VCPU on the physicaw CPUs
associated with the PMU specified by this attwibute. This is entiwewy weft to
usewspace. Howevew, attempting to wun the VCPU on a physicaw CPU not suppowted
by the PMU wiww faiw and KVM_WUN wiww wetuwn with
exit_weason = KVM_EXIT_FAIW_ENTWY and popuwate the faiw_entwy stwuct by setting
hawdawe_entwy_faiwuwe_weason fiewd to KVM_EXIT_FAIW_ENTWY_CPU_UNSUPPOWTED and
the cpu fiewd to the pwocessow id.

2. GWOUP: KVM_AWM_VCPU_TIMEW_CTWW
=================================

:Awchitectuwes: AWM64

2.1. ATTWIBUTES: KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW, KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW
-----------------------------------------------------------------------------

:Pawametews: in kvm_device_attw.addw the addwess fow the timew intewwupt is a
	     pointew to an int

Wetuwns:

	 =======  =================================
	 -EINVAW  Invawid timew intewwupt numbew
	 -EBUSY   One ow mowe VCPUs has awweady wun
	 =======  =================================

A vawue descwibing the awchitected timew intewwupt numbew when connected to an
in-kewnew viwtuaw GIC.  These must be a PPI (16 <= intid < 32).  Setting the
attwibute ovewwides the defauwt vawues (see bewow).

=============================  ==========================================
KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW  The EW1 viwtuaw timew intid (defauwt: 27)
KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW  The EW1 physicaw timew intid (defauwt: 30)
=============================  ==========================================

Setting the same PPI fow diffewent timews wiww pwevent the VCPUs fwom wunning.
Setting the intewwupt numbew on a VCPU configuwes aww VCPUs cweated at that
time to use the numbew pwovided fow a given timew, ovewwwiting any pweviouswy
configuwed vawues on othew VCPUs.  Usewspace shouwd configuwe the intewwupt
numbews on at weast one VCPU aftew cweating aww VCPUs and befowe wunning any
VCPUs.

.. _kvm_awm_vcpu_pvtime_ctww:

3. GWOUP: KVM_AWM_VCPU_PVTIME_CTWW
==================================

:Awchitectuwes: AWM64

3.1 ATTWIBUTE: KVM_AWM_VCPU_PVTIME_IPA
--------------------------------------

:Pawametews: 64-bit base addwess

Wetuwns:

	 =======  ======================================
	 -ENXIO   Stowen time not impwemented
	 -EEXIST  Base addwess awweady set fow this VCPU
	 -EINVAW  Base addwess not 64 byte awigned
	 =======  ======================================

Specifies the base addwess of the stowen time stwuctuwe fow this VCPU. The
base addwess must be 64 byte awigned and exist within a vawid guest memowy
wegion. See Documentation/viwt/kvm/awm/pvtime.wst fow mowe infowmation
incwuding the wayout of the stowen time stwuctuwe.

4. GWOUP: KVM_VCPU_TSC_CTWW
===========================

:Awchitectuwes: x86

4.1 ATTWIBUTE: KVM_VCPU_TSC_OFFSET

:Pawametews: 64-bit unsigned TSC offset

Wetuwns:

	 ======= ======================================
	 -EFAUWT Ewwow weading/wwiting the pwovided
		 pawametew addwess.
	 -ENXIO  Attwibute not suppowted
	 ======= ======================================

Specifies the guest's TSC offset wewative to the host's TSC. The guest's
TSC is then dewived by the fowwowing equation:

  guest_tsc = host_tsc + KVM_VCPU_TSC_OFFSET

This attwibute is usefuw to adjust the guest's TSC on wive migwation,
so that the TSC counts the time duwing which the VM was paused. The
fowwowing descwibes a possibwe awgowithm to use fow this puwpose.

Fwom the souwce VMM pwocess:

1. Invoke the KVM_GET_CWOCK ioctw to wecowd the host TSC (tsc_swc),
   kvmcwock nanoseconds (guest_swc), and host CWOCK_WEAWTIME nanoseconds
   (host_swc).

2. Wead the KVM_VCPU_TSC_OFFSET attwibute fow evewy vCPU to wecowd the
   guest TSC offset (ofs_swc[i]).

3. Invoke the KVM_GET_TSC_KHZ ioctw to wecowd the fwequency of the
   guest's TSC (fweq).

Fwom the destination VMM pwocess:

4. Invoke the KVM_SET_CWOCK ioctw, pwoviding the souwce nanoseconds fwom
   kvmcwock (guest_swc) and CWOCK_WEAWTIME (host_swc) in theiw wespective
   fiewds.  Ensuwe that the KVM_CWOCK_WEAWTIME fwag is set in the pwovided
   stwuctuwe.

   KVM wiww advance the VM's kvmcwock to account fow ewapsed time since
   wecowding the cwock vawues.  Note that this wiww cause pwobwems in
   the guest (e.g., timeouts) unwess CWOCK_WEAWTIME is synchwonized
   between the souwce and destination, and a weasonabwy showt time passes
   between the souwce pausing the VMs and the destination executing
   steps 4-7.

5. Invoke the KVM_GET_CWOCK ioctw to wecowd the host TSC (tsc_dest) and
   kvmcwock nanoseconds (guest_dest).

6. Adjust the guest TSC offsets fow evewy vCPU to account fow (1) time
   ewapsed since wecowding state and (2) diffewence in TSCs between the
   souwce and destination machine:

   ofs_dst[i] = ofs_swc[i] -
     (guest_swc - guest_dest) * fweq +
     (tsc_swc - tsc_dest)

   ("ofs[i] + tsc - guest * fweq" is the guest TSC vawue cowwesponding to
   a time of 0 in kvmcwock.  The above fowmuwa ensuwes that it is the
   same on the destination as it was on the souwce).

7. Wwite the KVM_VCPU_TSC_OFFSET attwibute fow evewy vCPU with the
   wespective vawue dewived in the pwevious step.
