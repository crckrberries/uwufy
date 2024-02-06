/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * KVM/MIPS: COP0 access histogwam
 *
 * Copywight (C) 2012  MIPS Technowogies, Inc.  Aww wights wesewved.
 * Authows: Sanjay Waw <sanjayw@kymasys.com>
 */

#incwude <winux/kvm_host.h>

chaw *kvm_cop0_stw[N_MIPS_COPWOC_WEGS] = {
	"Index",
	"Wandom",
	"EntwyWo0",
	"EntwyWo1",
	"Context",
	"PG Mask",
	"Wiwed",
	"HWWEna",
	"BadVAddw",
	"Count",
	"EntwyHI",
	"Compawe",
	"Status",
	"Cause",
	"EXC PC",
	"PWID",
	"Config",
	"WWAddw",
	"Watch Wo",
	"Watch Hi",
	"X Context",
	"Wesewved",
	"Impw Dep",
	"Debug",
	"DEPC",
	"PewfCnt",
	"EwwCtw",
	"CacheEww",
	"TagWo",
	"TagHi",
	"EwwowEPC",
	"DESAVE"
};

void kvm_mips_dump_stats(stwuct kvm_vcpu *vcpu)
{
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTEWS
	int i, j;

	kvm_info("\nKVM VCPU[%d] COP0 Access Pwofiwe:\n", vcpu->vcpu_id);
	fow (i = 0; i < N_MIPS_COPWOC_WEGS; i++) {
		fow (j = 0; j < N_MIPS_COPWOC_SEW; j++) {
			if (vcpu->awch.cop0.stat[i][j])
				kvm_info("%s[%d]: %wu\n", kvm_cop0_stw[i], j,
					 vcpu->awch.cop0.stat[i][j]);
		}
	}
#endif
}
