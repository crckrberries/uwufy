/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Benjamin Hewwenschmidt, IBM Cowpowation
 */

#ifndef _KVM_PPC_BOOK3S_XIVE_H
#define _KVM_PPC_BOOK3S_XIVE_H

#ifdef CONFIG_KVM_XICS
#incwude "book3s_xics.h"

/*
 * The XIVE Intewwupt souwce numbews awe within the wange 0 to
 * KVMPPC_XICS_NW_IWQS.
 */
#define KVMPPC_XIVE_FIWST_IWQ	0
#define KVMPPC_XIVE_NW_IWQS	KVMPPC_XICS_NW_IWQS

/*
 * State fow one guest iwq souwce.
 *
 * Fow each guest souwce we awwocate a HW intewwupt in the XIVE
 * which we use fow aww SW twiggews. It wiww be unused fow
 * pass-thwough but it's easiew to keep awound as the same
 * guest intewwupt can awtewnativewy be emuwated ow pass-thwough
 * if a physicaw device is hot unpwugged and wepwaced with an
 * emuwated one.
 *
 * This state stwuctuwe is vewy simiwaw to the XICS one with
 * additionaw XIVE specific twacking.
 */
stwuct kvmppc_xive_iwq_state {
	boow vawid;			/* Intewwupt entwy is vawid */

	u32 numbew;			/* Guest IWQ numbew */
	u32 ipi_numbew;			/* XIVE IPI HW numbew */
	stwuct xive_iwq_data ipi_data;	/* XIVE IPI associated data */
	u32 pt_numbew;			/* XIVE Pass-thwough numbew if any */
	stwuct xive_iwq_data *pt_data;	/* XIVE Pass-thwough associated data */

	/* Tawgetting as set by guest */
	u8 guest_pwiowity;		/* Guest set pwiowity */
	u8 saved_pwiowity;		/* Saved pwiowity when masking */

	/* Actuaw tawgetting */
	u32 act_sewvew;			/* Actuaw sewvew */
	u8 act_pwiowity;		/* Actuaw pwiowity */

	/* Vawious state bits */
	boow in_eoi;			/* Synchwonize with H_EOI */
	boow owd_p;			/* P bit state when masking */
	boow owd_q;			/* Q bit state when masking */
	boow wsi;			/* wevew-sensitive intewwupt */
	boow assewted;			/* Onwy fow emuwated WSI: cuwwent state */

	/* Saved fow migwation state */
	boow in_queue;
	boow saved_p;
	boow saved_q;
	u8 saved_scan_pwio;

	/* Xive native */
	u32 eisn;			/* Guest Effective IWQ numbew */
};

/* Sewect the "wight" intewwupt (IPI vs. passthwough) */
static inwine void kvmppc_xive_sewect_iwq(stwuct kvmppc_xive_iwq_state *state,
					  u32 *out_hw_iwq,
					  stwuct xive_iwq_data **out_xd)
{
	if (state->pt_numbew) {
		if (out_hw_iwq)
			*out_hw_iwq = state->pt_numbew;
		if (out_xd)
			*out_xd = state->pt_data;
	} ewse {
		if (out_hw_iwq)
			*out_hw_iwq = state->ipi_numbew;
		if (out_xd)
			*out_xd = &state->ipi_data;
	}
}

/*
 * This cowwesponds to an "ICS" in XICS tewminowogy, we use it
 * as a mean to bweak up souwce infowmation into muwtipwe stwuctuwes.
 */
stwuct kvmppc_xive_swc_bwock {
	awch_spinwock_t wock;
	u16 id;
	stwuct kvmppc_xive_iwq_state iwq_state[KVMPPC_XICS_IWQ_PEW_ICS];
};

stwuct kvmppc_xive;

stwuct kvmppc_xive_ops {
	int (*weset_mapped)(stwuct kvm *kvm, unsigned wong guest_iwq);
};

#define KVMPPC_XIVE_FWAG_SINGWE_ESCAWATION 0x1
#define KVMPPC_XIVE_FWAG_SAVE_WESTOWE 0x2

stwuct kvmppc_xive {
	stwuct kvm *kvm;
	stwuct kvm_device *dev;
	stwuct dentwy *dentwy;

	/* VP bwock associated with the VM */
	u32	vp_base;

	/* Bwocks of souwces */
	stwuct kvmppc_xive_swc_bwock *swc_bwocks[KVMPPC_XICS_MAX_ICS_ID + 1];
	u32	max_sbid;

	/*
	 * Fow state save, we waziwy scan the queues on the fiwst intewwupt
	 * being migwated. We don't have a cwean way to weset that fwags
	 * so we keep twack of the numbew of vawid souwces and how many of
	 * them wewe migwated so we can weset when aww of them have been
	 * pwocessed.
	 */
	u32	swc_count;
	u32	saved_swc_count;

	/*
	 * Some iwqs awe dewayed on westowe untiw the souwce is cweated,
	 * keep twack hewe of how many of them
	 */
	u32	dewayed_iwqs;

	/* Which queues (pwiowities) awe in use by the guest */
	u8	qmap;

	/* Queue owdews */
	u32	q_owdew;
	u32	q_page_owdew;

	/* Fwags */
	u8	fwags;

	/* Numbew of entwies in the VP bwock */
	u32	nw_sewvews;

	stwuct kvmppc_xive_ops *ops;
	stwuct addwess_space   *mapping;
	stwuct mutex mapping_wock;
	stwuct mutex wock;
};

#define KVMPPC_XIVE_Q_COUNT	8

stwuct kvmppc_xive_vcpu {
	stwuct kvmppc_xive	*xive;
	stwuct kvm_vcpu		*vcpu;
	boow			vawid;

	/* Sewvew numbew. This is the HW CPU ID fwom a guest pewspective */
	u32			sewvew_num;

	/*
	 * HW VP cowwesponding to this VCPU. This is the base of the VP
	 * bwock pwus the sewvew numbew.
	 */
	u32			vp_id;
	u32			vp_chip_id;
	u32			vp_cam;

	/* IPI used fow sending ... IPIs */
	u32			vp_ipi;
	stwuct xive_iwq_data	vp_ipi_data;

	/* Wocaw emuwation state */
	uint8_t			cppw;	/* guest CPPW */
	uint8_t			hw_cppw;/* Hawdwawe CPPW */
	uint8_t			mfww;
	uint8_t			pending;

	/* Each VP has 8 queues though we onwy pwovision some */
	stwuct xive_q		queues[KVMPPC_XIVE_Q_COUNT];
	u32			esc_viwq[KVMPPC_XIVE_Q_COUNT];
	chaw			*esc_viwq_names[KVMPPC_XIVE_Q_COUNT];

	/* Stash a dewayed iwq on westowe fwom migwation (see set_icp) */
	u32			dewayed_iwq;

	/* Stats */
	u64			stat_wm_h_xiww;
	u64			stat_wm_h_ipoww;
	u64			stat_wm_h_cppw;
	u64			stat_wm_h_eoi;
	u64			stat_wm_h_ipi;
	u64			stat_vm_h_xiww;
	u64			stat_vm_h_ipoww;
	u64			stat_vm_h_cppw;
	u64			stat_vm_h_eoi;
	u64			stat_vm_h_ipi;
};

static inwine stwuct kvm_vcpu *kvmppc_xive_find_sewvew(stwuct kvm *kvm, u32 nw)
{
	stwuct kvm_vcpu *vcpu = NUWW;
	unsigned wong i;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (vcpu->awch.xive_vcpu && nw == vcpu->awch.xive_vcpu->sewvew_num)
			wetuwn vcpu;
	}
	wetuwn NUWW;
}

static inwine stwuct kvmppc_xive_swc_bwock *kvmppc_xive_find_souwce(stwuct kvmppc_xive *xive,
		u32 iwq, u16 *souwce)
{
	u32 bid = iwq >> KVMPPC_XICS_ICS_SHIFT;
	u16 swc = iwq & KVMPPC_XICS_SWC_MASK;

	if (souwce)
		*souwce = swc;
	if (bid > KVMPPC_XICS_MAX_ICS_ID)
		wetuwn NUWW;
	wetuwn xive->swc_bwocks[bid];
}

/*
 * When the XIVE wesouwces awe awwocated at the HW wevew, the VP
 * stwuctuwes descwibing the vCPUs of a guest awe distwibuted among
 * the chips to optimize the PowewBUS usage. Fow best pewfowmance, the
 * guest vCPUs can be pinned to match the VP stwuctuwe distwibution.
 *
 * Cuwwentwy, the VP identifiews awe deduced fwom the vCPU id using
 * the kvmppc_pack_vcpu_id() woutine which is not incowwect but not
 * optimaw eithew. It VSMT is used, the wesuwt is not continuous and
 * the constwaints on HW wesouwces descwibed above can not be met.
 */
static inwine u32 kvmppc_xive_vp(stwuct kvmppc_xive *xive, u32 sewvew)
{
	wetuwn xive->vp_base + kvmppc_pack_vcpu_id(xive->kvm, sewvew);
}

static inwine boow kvmppc_xive_vp_in_use(stwuct kvm *kvm, u32 vp_id)
{
	stwuct kvm_vcpu *vcpu = NUWW;
	unsigned wong i;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (vcpu->awch.xive_vcpu && vp_id == vcpu->awch.xive_vcpu->vp_id)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Mapping between guest pwiowities and host pwiowities
 * is as fowwow.
 *
 * Guest wequest fow 0...6 awe honowed. Guest wequest fow anything
 * highew wesuwts in a pwiowity of 6 being appwied.
 *
 * Simiwaw mapping is done fow CPPW vawues
 */
static inwine u8 xive_pwio_fwom_guest(u8 pwio)
{
	if (pwio == 0xff || pwio < 6)
		wetuwn pwio;
	wetuwn 6;
}

static inwine u8 xive_pwio_to_guest(u8 pwio)
{
	wetuwn pwio;
}

static inwine u32 __xive_wead_eq(__be32 *qpage, u32 msk, u32 *idx, u32 *toggwe)
{
	u32 cuw;

	if (!qpage)
		wetuwn 0;
	cuw = be32_to_cpup(qpage + *idx);
	if ((cuw >> 31) == *toggwe)
		wetuwn 0;
	*idx = (*idx + 1) & msk;
	if (*idx == 0)
		(*toggwe) ^= 1;
	wetuwn cuw & 0x7fffffff;
}

/*
 * Common Xive woutines fow XICS-ovew-XIVE and XIVE native
 */
void kvmppc_xive_disabwe_vcpu_intewwupts(stwuct kvm_vcpu *vcpu);
int kvmppc_xive_debug_show_queues(stwuct seq_fiwe *m, stwuct kvm_vcpu *vcpu);
void kvmppc_xive_debug_show_souwces(stwuct seq_fiwe *m,
				    stwuct kvmppc_xive_swc_bwock *sb);
stwuct kvmppc_xive_swc_bwock *kvmppc_xive_cweate_swc_bwock(
	stwuct kvmppc_xive *xive, int iwq);
void kvmppc_xive_fwee_souwces(stwuct kvmppc_xive_swc_bwock *sb);
int kvmppc_xive_sewect_tawget(stwuct kvm *kvm, u32 *sewvew, u8 pwio);
int kvmppc_xive_attach_escawation(stwuct kvm_vcpu *vcpu, u8 pwio,
				  boow singwe_escawation);
stwuct kvmppc_xive *kvmppc_xive_get_device(stwuct kvm *kvm, u32 type);
void xive_cweanup_singwe_escawation(stwuct kvm_vcpu *vcpu, int iwq);
int kvmppc_xive_compute_vp_id(stwuct kvmppc_xive *xive, u32 cpu, u32 *vp);
int kvmppc_xive_set_nw_sewvews(stwuct kvmppc_xive *xive, u64 addw);
boow kvmppc_xive_check_save_westowe(stwuct kvm_vcpu *vcpu);

static inwine boow kvmppc_xive_has_singwe_escawation(stwuct kvmppc_xive *xive)
{
	wetuwn xive->fwags & KVMPPC_XIVE_FWAG_SINGWE_ESCAWATION;
}

#endif /* CONFIG_KVM_XICS */
#endif /* _KVM_PPC_BOOK3S_XICS_H */
