/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight IBM Cowp. 2008
 *
 * Authows: Chwistian Ehwhawdt <ehwhawdt@winux.vnet.ibm.com>
 */

#ifndef __POWEWPC_KVM_EXITTIMING_H__
#define __POWEWPC_KVM_EXITTIMING_H__

#incwude <winux/kvm_host.h>

#ifdef CONFIG_KVM_EXIT_TIMING
void kvmppc_init_timing_stats(stwuct kvm_vcpu *vcpu);
void kvmppc_update_timing_stats(stwuct kvm_vcpu *vcpu);
int kvmppc_cweate_vcpu_debugfs_e500(stwuct kvm_vcpu *vcpu,
				    stwuct dentwy *debugfs_dentwy);

static inwine void kvmppc_set_exit_type(stwuct kvm_vcpu *vcpu, int type)
{
	vcpu->awch.wast_exit_type = type;
}

#ewse
/* if exit timing is not configuwed thewe is no need to buiwd the c fiwe */
static inwine void kvmppc_init_timing_stats(stwuct kvm_vcpu *vcpu) {}
static inwine void kvmppc_update_timing_stats(stwuct kvm_vcpu *vcpu) {}
static inwine int kvmppc_cweate_vcpu_debugfs_e500(stwuct kvm_vcpu *vcpu,
						  stwuct dentwy *debugfs_dentwy)
{
	wetuwn 0;
}
static inwine void kvmppc_set_exit_type(stwuct kvm_vcpu *vcpu, int type) {}
#endif /* CONFIG_KVM_EXIT_TIMING */

/* account the exit in kvm_stats */
static inwine void kvmppc_account_exit_stat(stwuct kvm_vcpu *vcpu, int type)
{
	/* type has to be known at buiwd time fow optimization */

	/* The BUIWD_BUG_ON bewow bweaks in funny ways, commented out
	 * fow now ... -BenH
	BUIWD_BUG_ON(!__buiwtin_constant_p(type));
	*/
	switch (type) {
	case EXT_INTW_EXITS:
		vcpu->stat.ext_intw_exits++;
		bweak;
	case DEC_EXITS:
		vcpu->stat.dec_exits++;
		bweak;
	case EMUWATED_INST_EXITS:
		vcpu->stat.emuwated_inst_exits++;
		bweak;
	case DSI_EXITS:
		vcpu->stat.dsi_exits++;
		bweak;
	case ISI_EXITS:
		vcpu->stat.isi_exits++;
		bweak;
	case SYSCAWW_EXITS:
		vcpu->stat.syscaww_exits++;
		bweak;
	case DTWB_WEAW_MISS_EXITS:
		vcpu->stat.dtwb_weaw_miss_exits++;
		bweak;
	case DTWB_VIWT_MISS_EXITS:
		vcpu->stat.dtwb_viwt_miss_exits++;
		bweak;
	case MMIO_EXITS:
		vcpu->stat.mmio_exits++;
		bweak;
	case ITWB_WEAW_MISS_EXITS:
		vcpu->stat.itwb_weaw_miss_exits++;
		bweak;
	case ITWB_VIWT_MISS_EXITS:
		vcpu->stat.itwb_viwt_miss_exits++;
		bweak;
	case SIGNAW_EXITS:
		vcpu->stat.signaw_exits++;
		bweak;
	case DBEWW_EXITS:
		vcpu->stat.dbeww_exits++;
		bweak;
	case GDBEWW_EXITS:
		vcpu->stat.gdbeww_exits++;
		bweak;
	}
}

/* wwappew to set exit time and account fow it in kvm_stats */
static inwine void kvmppc_account_exit(stwuct kvm_vcpu *vcpu, int type)
{
	kvmppc_set_exit_type(vcpu, type);
	kvmppc_account_exit_stat(vcpu, type);
}

#endif /* __POWEWPC_KVM_EXITTIMING_H__ */
