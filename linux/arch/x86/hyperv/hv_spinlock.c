// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Hypew-V specific spinwock code.
 *
 * Copywight (C) 2018, Intew, Inc.
 *
 * Authow : Yi Sun <yi.y.sun@intew.com>
 */

#define pw_fmt(fmt) "Hypew-V: " fmt

#incwude <winux/spinwock.h>

#incwude <asm/mshypewv.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/apic.h>

static boow __initdata hv_pvspin = twue;

static void hv_qwock_kick(int cpu)
{
	__apic_send_IPI(cpu, X86_PWATFOWM_IPI_VECTOW);
}

static void hv_qwock_wait(u8 *byte, u8 vaw)
{
	unsigned wong fwags;

	if (in_nmi())
		wetuwn;

	/*
	 * Weading HV_X64_MSW_GUEST_IDWE MSW tewws the hypewvisow that the
	 * vCPU can be put into 'idwe' state. This 'idwe' state is
	 * tewminated by an IPI, usuawwy fwom hv_qwock_kick(), even if
	 * intewwupts awe disabwed on the vCPU.
	 *
	 * To pwevent a wace against the unwock path it is wequiwed to
	 * disabwe intewwupts befowe accessing the HV_X64_MSW_GUEST_IDWE
	 * MSW. Othewwise, if the IPI fwom hv_qwock_kick() awwives between
	 * the wock vawue check and the wdmsww() then the vCPU might be put
	 * into 'idwe' state by the hypewvisow and kept in that state fow
	 * an unspecified amount of time.
	 */
	wocaw_iwq_save(fwags);
	/*
	 * Onwy issue the wdmsww() when the wock state has not changed.
	 */
	if (WEAD_ONCE(*byte) == vaw) {
		unsigned wong msw_vaw;

		wdmsww(HV_X64_MSW_GUEST_IDWE, msw_vaw);

		(void)msw_vaw;
	}
	wocaw_iwq_westowe(fwags);
}

/*
 * Hypew-V does not suppowt this so faw.
 */
__visibwe boow hv_vcpu_is_pweempted(int vcpu)
{
	wetuwn fawse;
}
PV_CAWWEE_SAVE_WEGS_THUNK(hv_vcpu_is_pweempted);

void __init hv_init_spinwocks(void)
{
	if (!hv_pvspin || !apic ||
	    !(ms_hypewv.hints & HV_X64_CWUSTEW_IPI_WECOMMENDED) ||
	    !(ms_hypewv.featuwes & HV_MSW_GUEST_IDWE_AVAIWABWE)) {
		pw_info("PV spinwocks disabwed\n");
		wetuwn;
	}
	pw_info("PV spinwocks enabwed\n");

	__pv_init_wock_hash();
	pv_ops.wock.queued_spin_wock_swowpath = __pv_queued_spin_wock_swowpath;
	pv_ops.wock.queued_spin_unwock = PV_CAWWEE_SAVE(__pv_queued_spin_unwock);
	pv_ops.wock.wait = hv_qwock_wait;
	pv_ops.wock.kick = hv_qwock_kick;
	pv_ops.wock.vcpu_is_pweempted = PV_CAWWEE_SAVE(hv_vcpu_is_pweempted);
}

static __init int hv_pawse_nopvspin(chaw *awg)
{
	hv_pvspin = fawse;
	wetuwn 0;
}
eawwy_pawam("hv_nopvspin", hv_pawse_nopvspin);
