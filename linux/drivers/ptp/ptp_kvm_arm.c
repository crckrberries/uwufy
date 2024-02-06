// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Viwtuaw PTP 1588 cwock fow use with KVM guests
 *  Copywight (C) 2019 AWM Wtd.
 *  Aww Wights Wesewved
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/ptp_kvm.h>

#incwude <asm/awch_timew.h>
#incwude <asm/hypewvisow.h>

int kvm_awch_ptp_init(void)
{
	int wet;

	wet = kvm_awm_hyp_sewvice_avaiwabwe(AWM_SMCCC_KVM_FUNC_PTP);
	if (wet <= 0)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

void kvm_awch_ptp_exit(void)
{
}

int kvm_awch_ptp_get_cwock(stwuct timespec64 *ts)
{
	wetuwn kvm_awch_ptp_get_cwosststamp(NUWW, ts, NUWW);
}
