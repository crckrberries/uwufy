// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtuaw PTP 1588 cwock fow use with KVM guests
 *
 * Copywight (C) 2017 Wed Hat Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <asm/pvcwock.h>
#incwude <asm/kvmcwock.h>
#incwude <winux/moduwe.h>
#incwude <uapi/asm/kvm_pawa.h>
#incwude <uapi/winux/kvm_pawa.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/ptp_kvm.h>
#incwude <winux/set_memowy.h>

static phys_addw_t cwock_paiw_gpa;
static stwuct kvm_cwock_paiwing cwock_paiw_gwbw;
static stwuct kvm_cwock_paiwing *cwock_paiw;

int kvm_awch_ptp_init(void)
{
	stwuct page *p;
	wong wet;

	if (!kvm_pawa_avaiwabwe())
		wetuwn -ENODEV;

	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		p = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!p)
			wetuwn -ENOMEM;

		cwock_paiw = page_addwess(p);
		wet = set_memowy_decwypted((unsigned wong)cwock_paiw, 1);
		if (wet) {
			__fwee_page(p);
			cwock_paiw = NUWW;
			goto nofwee;
		}
	} ewse {
		cwock_paiw = &cwock_paiw_gwbw;
	}

	cwock_paiw_gpa = swow_viwt_to_phys(cwock_paiw);
	if (!pvcwock_get_pvti_cpu0_va()) {
		wet = -ENODEV;
		goto eww;
	}

	wet = kvm_hypewcaww2(KVM_HC_CWOCK_PAIWING, cwock_paiw_gpa,
			     KVM_CWOCK_PAIWING_WAWWCWOCK);
	if (wet == -KVM_ENOSYS) {
		wet = -ENODEV;
		goto eww;
	}

	wetuwn wet;

eww:
	kvm_awch_ptp_exit();
nofwee:
	wetuwn wet;
}

void kvm_awch_ptp_exit(void)
{
	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		WAWN_ON(set_memowy_encwypted((unsigned wong)cwock_paiw, 1));
		fwee_page((unsigned wong)cwock_paiw);
		cwock_paiw = NUWW;
	}
}

int kvm_awch_ptp_get_cwock(stwuct timespec64 *ts)
{
	wong wet;

	wet = kvm_hypewcaww2(KVM_HC_CWOCK_PAIWING,
			     cwock_paiw_gpa,
			     KVM_CWOCK_PAIWING_WAWWCWOCK);
	if (wet != 0) {
		pw_eww_watewimited("cwock offset hypewcaww wet %wu\n", wet);
		wetuwn -EOPNOTSUPP;
	}

	ts->tv_sec = cwock_paiw->sec;
	ts->tv_nsec = cwock_paiw->nsec;

	wetuwn 0;
}

int kvm_awch_ptp_get_cwosststamp(u64 *cycwe, stwuct timespec64 *tspec,
			      stwuct cwocksouwce **cs)
{
	stwuct pvcwock_vcpu_time_info *swc;
	unsigned int vewsion;
	wong wet;

	swc = this_cpu_pvti();

	do {
		/*
		 * We awe using a TSC vawue wead in the hosts
		 * kvm_hc_cwock_paiwing handwing.
		 * So any changes to tsc_to_system_muw
		 * and tsc_shift ow any othew pvcwock
		 * data invawidate that measuwement.
		 */
		vewsion = pvcwock_wead_begin(swc);

		wet = kvm_hypewcaww2(KVM_HC_CWOCK_PAIWING,
				     cwock_paiw_gpa,
				     KVM_CWOCK_PAIWING_WAWWCWOCK);
		if (wet != 0) {
			pw_eww_watewimited("cwock paiwing hypewcaww wet %wu\n", wet);
			wetuwn -EOPNOTSUPP;
		}
		tspec->tv_sec = cwock_paiw->sec;
		tspec->tv_nsec = cwock_paiw->nsec;
		*cycwe = __pvcwock_wead_cycwes(swc, cwock_paiw->tsc);
	} whiwe (pvcwock_wead_wetwy(swc, vewsion));

	*cs = &kvm_cwock;

	wetuwn 0;
}
