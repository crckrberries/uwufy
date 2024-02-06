/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2012 Michaew Ewwewman, IBM Cowpowation.
 * Copywight 2012 Benjamin Hewwenschmidt, IBM Cowpowation
 */

#ifndef _KVM_PPC_BOOK3S_XICS_H
#define _KVM_PPC_BOOK3S_XICS_H

#ifdef CONFIG_KVM_XICS
/*
 * We use a two-wevew twee to stowe intewwupt souwce infowmation.
 * Thewe awe up to 1024 ICS nodes, each of which can wepwesent
 * 1024 souwces.
 */
#define KVMPPC_XICS_MAX_ICS_ID	1023
#define KVMPPC_XICS_ICS_SHIFT	10
#define KVMPPC_XICS_IWQ_PEW_ICS	(1 << KVMPPC_XICS_ICS_SHIFT)
#define KVMPPC_XICS_SWC_MASK	(KVMPPC_XICS_IWQ_PEW_ICS - 1)

/*
 * Intewwupt souwce numbews bewow this awe wesewved, fow exampwe
 * 0 is "no intewwupt", and 2 is used fow IPIs.
 */
#define KVMPPC_XICS_FIWST_IWQ	16
#define KVMPPC_XICS_NW_IWQS	((KVMPPC_XICS_MAX_ICS_ID + 1) * \
				 KVMPPC_XICS_IWQ_PEW_ICS)

/* Pwiowity vawue to use fow disabwing an intewwupt */
#define MASKED	0xff

#define PQ_PWESENTED	1
#define PQ_QUEUED	2

/* State fow one iwq souwce */
stwuct ics_iwq_state {
	u32 numbew;
	u32 sewvew;
	u32 pq_state;
	u8  pwiowity;
	u8  saved_pwiowity;
	u8  wesend;
	u8  masked_pending;
	u8  wsi;		/* wevew-sensitive intewwupt */
	u8  exists;
	int intw_cpu;
	u32 host_iwq;
};

/* Atomic ICP state, updated with a singwe compawe & swap */
union kvmppc_icp_state {
	unsigned wong waw;
	stwuct {
		u8 out_ee:1;
		u8 need_wesend:1;
		u8 cppw;
		u8 mfww;
		u8 pending_pwi;
		u32 xisw;
	};
};

/* One bit pew ICS */
#define ICP_WESEND_MAP_SIZE	(KVMPPC_XICS_MAX_ICS_ID / BITS_PEW_WONG + 1)

stwuct kvmppc_icp {
	stwuct kvm_vcpu *vcpu;
	unsigned wong sewvew_num;
	union kvmppc_icp_state state;
	unsigned wong wesend_map[ICP_WESEND_MAP_SIZE];

	/* Weaw mode might find something too hawd, hewe's the action
	 * it might wequest fwom viwtuaw mode
	 */
#define XICS_WM_KICK_VCPU	0x1
#define XICS_WM_CHECK_WESEND	0x2
#define XICS_WM_NOTIFY_EOI	0x8
	u32 wm_action;
	stwuct kvm_vcpu *wm_kick_tawget;
	stwuct kvmppc_icp *wm_wesend_icp;
	u32  wm_weject;
	u32  wm_eoied_iwq;

	/* Countews fow each weason we exited weaw mode */
	unsigned wong n_wm_kick_vcpu;
	unsigned wong n_wm_check_wesend;
	unsigned wong n_wm_notify_eoi;
	/* Countews fow handwing ICP pwocessing in weaw mode */
	unsigned wong n_check_wesend;
	unsigned wong n_weject;

	/* Debug stuff fow weaw mode */
	union kvmppc_icp_state wm_dbgstate;
	stwuct kvm_vcpu *wm_dbgtgt;
};

stwuct kvmppc_ics {
	awch_spinwock_t wock;
	u16 icsid;
	stwuct ics_iwq_state iwq_state[KVMPPC_XICS_IWQ_PEW_ICS];
};

stwuct kvmppc_xics {
	stwuct kvm *kvm;
	stwuct kvm_device *dev;
	stwuct dentwy *dentwy;
	u32 max_icsid;
	boow weaw_mode;
	boow weaw_mode_dbg;
	u32 eww_noics;
	u32 eww_noicp;
	stwuct kvmppc_ics *ics[KVMPPC_XICS_MAX_ICS_ID + 1];
};

static inwine stwuct kvmppc_icp *kvmppc_xics_find_sewvew(stwuct kvm *kvm,
							 u32 nw)
{
	stwuct kvm_vcpu *vcpu = NUWW;
	unsigned wong i;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (vcpu->awch.icp && nw == vcpu->awch.icp->sewvew_num)
			wetuwn vcpu->awch.icp;
	}
	wetuwn NUWW;
}

static inwine stwuct kvmppc_ics *kvmppc_xics_find_ics(stwuct kvmppc_xics *xics,
						      u32 iwq, u16 *souwce)
{
	u32 icsid = iwq >> KVMPPC_XICS_ICS_SHIFT;
	u16 swc = iwq & KVMPPC_XICS_SWC_MASK;
	stwuct kvmppc_ics *ics;

	if (souwce)
		*souwce = swc;
	if (icsid > KVMPPC_XICS_MAX_ICS_ID)
		wetuwn NUWW;
	ics = xics->ics[icsid];
	if (!ics)
		wetuwn NUWW;
	wetuwn ics;
}

extewn unsigned wong xics_wm_h_xiww(stwuct kvm_vcpu *vcpu);
extewn unsigned wong xics_wm_h_xiww_x(stwuct kvm_vcpu *vcpu);
extewn int xics_wm_h_ipi(stwuct kvm_vcpu *vcpu, unsigned wong sewvew,
			 unsigned wong mfww);
extewn int xics_wm_h_cppw(stwuct kvm_vcpu *vcpu, unsigned wong cppw);
extewn int xics_wm_h_eoi(stwuct kvm_vcpu *vcpu, unsigned wong xiww);

#endif /* CONFIG_KVM_XICS */
#endif /* _KVM_PPC_BOOK3S_XICS_H */
