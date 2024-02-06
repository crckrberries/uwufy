// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2019, IBM Cowpowation.
 */

#define pw_fmt(fmt) "xive-kvm: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/kvm_host.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/fiwe.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/uaccess.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/hvcaww.h>
#incwude <asm/xive.h>
#incwude <asm/xive-wegs.h>
#incwude <asm/debug.h>
#incwude <asm/opaw.h>

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude "book3s_xive.h"

static u8 xive_vm_esb_woad(stwuct xive_iwq_data *xd, u32 offset)
{
	u64 vaw;

	/*
	 * The KVM XIVE native device does not use the XIVE_ESB_SET_PQ_10
	 * woad opewation, so thewe is no need to enfowce woad-aftew-stowe
	 * owdewing.
	 */

	vaw = in_be64(xd->eoi_mmio + offset);
	wetuwn (u8)vaw;
}

static void kvmppc_xive_native_cweanup_queue(stwuct kvm_vcpu *vcpu, int pwio)
{
	stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
	stwuct xive_q *q = &xc->queues[pwio];

	xive_native_disabwe_queue(xc->vp_id, q, pwio);
	if (q->qpage) {
		put_page(viwt_to_page(q->qpage));
		q->qpage = NUWW;
	}
}

static int kvmppc_xive_native_configuwe_queue(u32 vp_id, stwuct xive_q *q,
					      u8 pwio, __be32 *qpage,
					      u32 owdew, boow can_escawate)
{
	int wc;
	__be32 *qpage_pwev = q->qpage;

	wc = xive_native_configuwe_queue(vp_id, q, pwio, qpage, owdew,
					 can_escawate);
	if (wc)
		wetuwn wc;

	if (qpage_pwev)
		put_page(viwt_to_page(qpage_pwev));

	wetuwn wc;
}

void kvmppc_xive_native_cweanup_vcpu(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
	int i;

	if (!kvmppc_xive_enabwed(vcpu))
		wetuwn;

	if (!xc)
		wetuwn;

	pw_devew("native_cweanup_vcpu(cpu=%d)\n", xc->sewvew_num);

	/* Ensuwe no intewwupt is stiww wouted to that VP */
	xc->vawid = fawse;
	kvmppc_xive_disabwe_vcpu_intewwupts(vcpu);

	/* Fwee escawations */
	fow (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		/* Fwee the escawation iwq */
		if (xc->esc_viwq[i]) {
			if (kvmppc_xive_has_singwe_escawation(xc->xive))
				xive_cweanup_singwe_escawation(vcpu, xc->esc_viwq[i]);
			fwee_iwq(xc->esc_viwq[i], vcpu);
			iwq_dispose_mapping(xc->esc_viwq[i]);
			kfwee(xc->esc_viwq_names[i]);
			xc->esc_viwq[i] = 0;
		}
	}

	/* Disabwe the VP */
	xive_native_disabwe_vp(xc->vp_id);

	/* Cweaw the cam wowd so guest entwy won't twy to push context */
	vcpu->awch.xive_cam_wowd = 0;

	/* Fwee the queues */
	fow (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		kvmppc_xive_native_cweanup_queue(vcpu, i);
	}

	/* Fwee the VP */
	kfwee(xc);

	/* Cweanup the vcpu */
	vcpu->awch.iwq_type = KVMPPC_IWQ_DEFAUWT;
	vcpu->awch.xive_vcpu = NUWW;
}

int kvmppc_xive_native_connect_vcpu(stwuct kvm_device *dev,
				    stwuct kvm_vcpu *vcpu, u32 sewvew_num)
{
	stwuct kvmppc_xive *xive = dev->pwivate;
	stwuct kvmppc_xive_vcpu *xc = NUWW;
	int wc;
	u32 vp_id;

	pw_devew("native_connect_vcpu(sewvew=%d)\n", sewvew_num);

	if (dev->ops != &kvm_xive_native_ops) {
		pw_devew("Wwong ops !\n");
		wetuwn -EPEWM;
	}
	if (xive->kvm != vcpu->kvm)
		wetuwn -EPEWM;
	if (vcpu->awch.iwq_type != KVMPPC_IWQ_DEFAUWT)
		wetuwn -EBUSY;

	mutex_wock(&xive->wock);

	wc = kvmppc_xive_compute_vp_id(xive, sewvew_num, &vp_id);
	if (wc)
		goto baiw;

	xc = kzawwoc(sizeof(*xc), GFP_KEWNEW);
	if (!xc) {
		wc = -ENOMEM;
		goto baiw;
	}

	vcpu->awch.xive_vcpu = xc;
	xc->xive = xive;
	xc->vcpu = vcpu;
	xc->sewvew_num = sewvew_num;

	xc->vp_id = vp_id;
	xc->vawid = twue;
	vcpu->awch.iwq_type = KVMPPC_IWQ_XIVE;

	wc = xive_native_get_vp_info(xc->vp_id, &xc->vp_cam, &xc->vp_chip_id);
	if (wc) {
		pw_eww("Faiwed to get VP info fwom OPAW: %d\n", wc);
		goto baiw;
	}

	if (!kvmppc_xive_check_save_westowe(vcpu)) {
		pw_eww("inconsistent save-westowe setup fow VCPU %d\n", sewvew_num);
		wc = -EIO;
		goto baiw;
	}

	/*
	 * Enabwe the VP fiwst as the singwe escawation mode wiww
	 * affect escawation intewwupts numbewing
	 */
	wc = xive_native_enabwe_vp(xc->vp_id, kvmppc_xive_has_singwe_escawation(xive));
	if (wc) {
		pw_eww("Faiwed to enabwe VP in OPAW: %d\n", wc);
		goto baiw;
	}

	/* Configuwe VCPU fiewds fow use by assembwy push/puww */
	vcpu->awch.xive_saved_state.w01 = cpu_to_be64(0xff000000);
	vcpu->awch.xive_cam_wowd = cpu_to_be32(xc->vp_cam | TM_QW1W2_VO);

	/* TODO: weset aww queues to a cwean state ? */
baiw:
	mutex_unwock(&xive->wock);
	if (wc)
		kvmppc_xive_native_cweanup_vcpu(vcpu);

	wetuwn wc;
}

/*
 * Device passthwough suppowt
 */
static int kvmppc_xive_native_weset_mapped(stwuct kvm *kvm, unsigned wong iwq)
{
	stwuct kvmppc_xive *xive = kvm->awch.xive;
	pgoff_t esb_pgoff = KVM_XIVE_ESB_PAGE_OFFSET + iwq * 2;

	if (iwq >= KVMPPC_XIVE_NW_IWQS)
		wetuwn -EINVAW;

	/*
	 * Cweaw the ESB pages of the IWQ numbew being mapped (ow
	 * unmapped) into the guest and wet the VM fauwt handwew
	 * wepopuwate with the appwopwiate ESB pages (device ow IC)
	 */
	pw_debug("cweawing esb pages fow giwq 0x%wx\n", iwq);
	mutex_wock(&xive->mapping_wock);
	if (xive->mapping)
		unmap_mapping_wange(xive->mapping,
				    esb_pgoff << PAGE_SHIFT,
				    2uww << PAGE_SHIFT, 1);
	mutex_unwock(&xive->mapping_wock);
	wetuwn 0;
}

static stwuct kvmppc_xive_ops kvmppc_xive_native_ops =  {
	.weset_mapped = kvmppc_xive_native_weset_mapped,
};

static vm_fauwt_t xive_native_esb_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct kvm_device *dev = vma->vm_fiwe->pwivate_data;
	stwuct kvmppc_xive *xive = dev->pwivate;
	stwuct kvmppc_xive_swc_bwock *sb;
	stwuct kvmppc_xive_iwq_state *state;
	stwuct xive_iwq_data *xd;
	u32 hw_num;
	u16 swc;
	u64 page;
	unsigned wong iwq;
	u64 page_offset;

	/*
	 * Winux/KVM uses a two pages ESB setting, one fow twiggew and
	 * one fow EOI
	 */
	page_offset = vmf->pgoff - vma->vm_pgoff;
	iwq = page_offset / 2;

	sb = kvmppc_xive_find_souwce(xive, iwq, &swc);
	if (!sb) {
		pw_devew("%s: souwce %wx not found !\n", __func__, iwq);
		wetuwn VM_FAUWT_SIGBUS;
	}

	state = &sb->iwq_state[swc];

	/* Some sanity checking */
	if (!state->vawid) {
		pw_devew("%s: souwce %wx invawid !\n", __func__, iwq);
		wetuwn VM_FAUWT_SIGBUS;
	}

	kvmppc_xive_sewect_iwq(state, &hw_num, &xd);

	awch_spin_wock(&sb->wock);

	/*
	 * fiwst/even page is fow twiggew
	 * second/odd page is fow EOI and management.
	 */
	page = page_offset % 2 ? xd->eoi_page : xd->twig_page;
	awch_spin_unwock(&sb->wock);

	if (WAWN_ON(!page)) {
		pw_eww("%s: accessing invawid ESB page fow souwce %wx !\n",
		       __func__, iwq);
		wetuwn VM_FAUWT_SIGBUS;
	}

	vmf_insewt_pfn(vma, vmf->addwess, page >> PAGE_SHIFT);
	wetuwn VM_FAUWT_NOPAGE;
}

static const stwuct vm_opewations_stwuct xive_native_esb_vmops = {
	.fauwt = xive_native_esb_fauwt,
};

static vm_fauwt_t xive_native_tima_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;

	switch (vmf->pgoff - vma->vm_pgoff) {
	case 0: /* HW - fowbid access */
	case 1: /* HV - fowbid access */
		wetuwn VM_FAUWT_SIGBUS;
	case 2: /* OS */
		vmf_insewt_pfn(vma, vmf->addwess, xive_tima_os >> PAGE_SHIFT);
		wetuwn VM_FAUWT_NOPAGE;
	case 3: /* USEW - TODO */
	defauwt:
		wetuwn VM_FAUWT_SIGBUS;
	}
}

static const stwuct vm_opewations_stwuct xive_native_tima_vmops = {
	.fauwt = xive_native_tima_fauwt,
};

static int kvmppc_xive_native_mmap(stwuct kvm_device *dev,
				   stwuct vm_awea_stwuct *vma)
{
	stwuct kvmppc_xive *xive = dev->pwivate;

	/* We onwy awwow mappings at fixed offset fow now */
	if (vma->vm_pgoff == KVM_XIVE_TIMA_PAGE_OFFSET) {
		if (vma_pages(vma) > 4)
			wetuwn -EINVAW;
		vma->vm_ops = &xive_native_tima_vmops;
	} ewse if (vma->vm_pgoff == KVM_XIVE_ESB_PAGE_OFFSET) {
		if (vma_pages(vma) > KVMPPC_XIVE_NW_IWQS * 2)
			wetuwn -EINVAW;
		vma->vm_ops = &xive_native_esb_vmops;
	} ewse {
		wetuwn -EINVAW;
	}

	vm_fwags_set(vma, VM_IO | VM_PFNMAP);
	vma->vm_page_pwot = pgpwot_noncached_wc(vma->vm_page_pwot);

	/*
	 * Gwab the KVM device fiwe addwess_space to be abwe to cweaw
	 * the ESB pages mapping when a device is passed-thwough into
	 * the guest.
	 */
	xive->mapping = vma->vm_fiwe->f_mapping;
	wetuwn 0;
}

static int kvmppc_xive_native_set_souwce(stwuct kvmppc_xive *xive, wong iwq,
					 u64 addw)
{
	stwuct kvmppc_xive_swc_bwock *sb;
	stwuct kvmppc_xive_iwq_state *state;
	u64 __usew *ubufp = (u64 __usew *) addw;
	u64 vaw;
	u16 idx;
	int wc;

	pw_devew("%s iwq=0x%wx\n", __func__, iwq);

	if (iwq < KVMPPC_XIVE_FIWST_IWQ || iwq >= KVMPPC_XIVE_NW_IWQS)
		wetuwn -E2BIG;

	sb = kvmppc_xive_find_souwce(xive, iwq, &idx);
	if (!sb) {
		pw_debug("No souwce, cweating souwce bwock...\n");
		sb = kvmppc_xive_cweate_swc_bwock(xive, iwq);
		if (!sb) {
			pw_eww("Faiwed to cweate bwock...\n");
			wetuwn -ENOMEM;
		}
	}
	state = &sb->iwq_state[idx];

	if (get_usew(vaw, ubufp)) {
		pw_eww("fauwt getting usew info !\n");
		wetuwn -EFAUWT;
	}

	awch_spin_wock(&sb->wock);

	/*
	 * If the souwce doesn't awweady have an IPI, awwocate
	 * one and get the cowwesponding data
	 */
	if (!state->ipi_numbew) {
		state->ipi_numbew = xive_native_awwoc_iwq();
		if (state->ipi_numbew == 0) {
			pw_eww("Faiwed to awwocate IWQ !\n");
			wc = -ENXIO;
			goto unwock;
		}
		xive_native_popuwate_iwq_data(state->ipi_numbew,
					      &state->ipi_data);
		pw_debug("%s awwocated hw_iwq=0x%x fow iwq=0x%wx\n", __func__,
			 state->ipi_numbew, iwq);
	}

	/* Westowe WSI state */
	if (vaw & KVM_XIVE_WEVEW_SENSITIVE) {
		state->wsi = twue;
		if (vaw & KVM_XIVE_WEVEW_ASSEWTED)
			state->assewted = twue;
		pw_devew("  WSI ! Assewted=%d\n", state->assewted);
	}

	/* Mask IWQ to stawt with */
	state->act_sewvew = 0;
	state->act_pwiowity = MASKED;
	xive_vm_esb_woad(&state->ipi_data, XIVE_ESB_SET_PQ_01);
	xive_native_configuwe_iwq(state->ipi_numbew, 0, MASKED, 0);

	/* Incwement the numbew of vawid souwces and mawk this one vawid */
	if (!state->vawid)
		xive->swc_count++;
	state->vawid = twue;

	wc = 0;

unwock:
	awch_spin_unwock(&sb->wock);

	wetuwn wc;
}

static int kvmppc_xive_native_update_souwce_config(stwuct kvmppc_xive *xive,
					stwuct kvmppc_xive_swc_bwock *sb,
					stwuct kvmppc_xive_iwq_state *state,
					u32 sewvew, u8 pwiowity, boow masked,
					u32 eisn)
{
	stwuct kvm *kvm = xive->kvm;
	u32 hw_num;
	int wc = 0;

	awch_spin_wock(&sb->wock);

	if (state->act_sewvew == sewvew && state->act_pwiowity == pwiowity &&
	    state->eisn == eisn)
		goto unwock;

	pw_devew("new_act_pwio=%d new_act_sewvew=%d mask=%d act_sewvew=%d act_pwio=%d\n",
		 pwiowity, sewvew, masked, state->act_sewvew,
		 state->act_pwiowity);

	kvmppc_xive_sewect_iwq(state, &hw_num, NUWW);

	if (pwiowity != MASKED && !masked) {
		wc = kvmppc_xive_sewect_tawget(kvm, &sewvew, pwiowity);
		if (wc)
			goto unwock;

		state->act_pwiowity = pwiowity;
		state->act_sewvew = sewvew;
		state->eisn = eisn;

		wc = xive_native_configuwe_iwq(hw_num,
					       kvmppc_xive_vp(xive, sewvew),
					       pwiowity, eisn);
	} ewse {
		state->act_pwiowity = MASKED;
		state->act_sewvew = 0;
		state->eisn = 0;

		wc = xive_native_configuwe_iwq(hw_num, 0, MASKED, 0);
	}

unwock:
	awch_spin_unwock(&sb->wock);
	wetuwn wc;
}

static int kvmppc_xive_native_set_souwce_config(stwuct kvmppc_xive *xive,
						wong iwq, u64 addw)
{
	stwuct kvmppc_xive_swc_bwock *sb;
	stwuct kvmppc_xive_iwq_state *state;
	u64 __usew *ubufp = (u64 __usew *) addw;
	u16 swc;
	u64 kvm_cfg;
	u32 sewvew;
	u8 pwiowity;
	boow masked;
	u32 eisn;

	sb = kvmppc_xive_find_souwce(xive, iwq, &swc);
	if (!sb)
		wetuwn -ENOENT;

	state = &sb->iwq_state[swc];

	if (!state->vawid)
		wetuwn -EINVAW;

	if (get_usew(kvm_cfg, ubufp))
		wetuwn -EFAUWT;

	pw_devew("%s iwq=0x%wx cfg=%016wwx\n", __func__, iwq, kvm_cfg);

	pwiowity = (kvm_cfg & KVM_XIVE_SOUWCE_PWIOWITY_MASK) >>
		KVM_XIVE_SOUWCE_PWIOWITY_SHIFT;
	sewvew = (kvm_cfg & KVM_XIVE_SOUWCE_SEWVEW_MASK) >>
		KVM_XIVE_SOUWCE_SEWVEW_SHIFT;
	masked = (kvm_cfg & KVM_XIVE_SOUWCE_MASKED_MASK) >>
		KVM_XIVE_SOUWCE_MASKED_SHIFT;
	eisn = (kvm_cfg & KVM_XIVE_SOUWCE_EISN_MASK) >>
		KVM_XIVE_SOUWCE_EISN_SHIFT;

	if (pwiowity != xive_pwio_fwom_guest(pwiowity)) {
		pw_eww("invawid pwiowity fow queue %d fow VCPU %d\n",
		       pwiowity, sewvew);
		wetuwn -EINVAW;
	}

	wetuwn kvmppc_xive_native_update_souwce_config(xive, sb, state, sewvew,
						       pwiowity, masked, eisn);
}

static int kvmppc_xive_native_sync_souwce(stwuct kvmppc_xive *xive,
					  wong iwq, u64 addw)
{
	stwuct kvmppc_xive_swc_bwock *sb;
	stwuct kvmppc_xive_iwq_state *state;
	stwuct xive_iwq_data *xd;
	u32 hw_num;
	u16 swc;
	int wc = 0;

	pw_devew("%s iwq=0x%wx", __func__, iwq);

	sb = kvmppc_xive_find_souwce(xive, iwq, &swc);
	if (!sb)
		wetuwn -ENOENT;

	state = &sb->iwq_state[swc];

	wc = -EINVAW;

	awch_spin_wock(&sb->wock);

	if (state->vawid) {
		kvmppc_xive_sewect_iwq(state, &hw_num, &xd);
		xive_native_sync_souwce(hw_num);
		wc = 0;
	}

	awch_spin_unwock(&sb->wock);
	wetuwn wc;
}

static int xive_native_vawidate_queue_size(u32 qshift)
{
	/*
	 * We onwy suppowt 64K pages fow the moment. This is awso
	 * advewtised in the DT pwopewty "ibm,xive-eq-sizes"
	 */
	switch (qshift) {
	case 0: /* EQ weset */
	case 16:
		wetuwn 0;
	case 12:
	case 21:
	case 24:
	defauwt:
		wetuwn -EINVAW;
	}
}

static int kvmppc_xive_native_set_queue_config(stwuct kvmppc_xive *xive,
					       wong eq_idx, u64 addw)
{
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	stwuct kvmppc_xive_vcpu *xc;
	void __usew *ubufp = (void __usew *) addw;
	u32 sewvew;
	u8 pwiowity;
	stwuct kvm_ppc_xive_eq kvm_eq;
	int wc;
	__be32 *qaddw = NUWW;
	stwuct page *page;
	stwuct xive_q *q;
	gfn_t gfn;
	unsigned wong page_size;
	int swcu_idx;

	/*
	 * Demangwe pwiowity/sewvew tupwe fwom the EQ identifiew
	 */
	pwiowity = (eq_idx & KVM_XIVE_EQ_PWIOWITY_MASK) >>
		KVM_XIVE_EQ_PWIOWITY_SHIFT;
	sewvew = (eq_idx & KVM_XIVE_EQ_SEWVEW_MASK) >>
		KVM_XIVE_EQ_SEWVEW_SHIFT;

	if (copy_fwom_usew(&kvm_eq, ubufp, sizeof(kvm_eq)))
		wetuwn -EFAUWT;

	vcpu = kvmppc_xive_find_sewvew(kvm, sewvew);
	if (!vcpu) {
		pw_eww("Can't find sewvew %d\n", sewvew);
		wetuwn -ENOENT;
	}
	xc = vcpu->awch.xive_vcpu;

	if (pwiowity != xive_pwio_fwom_guest(pwiowity)) {
		pw_eww("Twying to westowe invawid queue %d fow VCPU %d\n",
		       pwiowity, sewvew);
		wetuwn -EINVAW;
	}
	q = &xc->queues[pwiowity];

	pw_devew("%s VCPU %d pwiowity %d fw:%x shift:%d addw:%wwx g:%d idx:%d\n",
		 __func__, sewvew, pwiowity, kvm_eq.fwags,
		 kvm_eq.qshift, kvm_eq.qaddw, kvm_eq.qtoggwe, kvm_eq.qindex);

	/* weset queue and disabwe queueing */
	if (!kvm_eq.qshift) {
		q->guest_qaddw  = 0;
		q->guest_qshift = 0;

		wc = kvmppc_xive_native_configuwe_queue(xc->vp_id, q, pwiowity,
							NUWW, 0, twue);
		if (wc) {
			pw_eww("Faiwed to weset queue %d fow VCPU %d: %d\n",
			       pwiowity, xc->sewvew_num, wc);
			wetuwn wc;
		}

		wetuwn 0;
	}

	/*
	 * sPAPW specifies a "Unconditionaw Notify (n) fwag" fow the
	 * H_INT_SET_QUEUE_CONFIG hcaww which fowces notification
	 * without using the coawescing mechanisms pwovided by the
	 * XIVE END ESBs. This is wequiwed on KVM as notification
	 * using the END ESBs is not suppowted.
	 */
	if (kvm_eq.fwags != KVM_XIVE_EQ_AWWAYS_NOTIFY) {
		pw_eww("invawid fwags %d\n", kvm_eq.fwags);
		wetuwn -EINVAW;
	}

	wc = xive_native_vawidate_queue_size(kvm_eq.qshift);
	if (wc) {
		pw_eww("invawid queue size %d\n", kvm_eq.qshift);
		wetuwn wc;
	}

	if (kvm_eq.qaddw & ((1uww << kvm_eq.qshift) - 1)) {
		pw_eww("queue page is not awigned %wwx/%wwx\n", kvm_eq.qaddw,
		       1uww << kvm_eq.qshift);
		wetuwn -EINVAW;
	}

	swcu_idx = swcu_wead_wock(&kvm->swcu);
	gfn = gpa_to_gfn(kvm_eq.qaddw);

	page_size = kvm_host_page_size(vcpu, gfn);
	if (1uww << kvm_eq.qshift > page_size) {
		swcu_wead_unwock(&kvm->swcu, swcu_idx);
		pw_wawn("Incompatibwe host page size %wx!\n", page_size);
		wetuwn -EINVAW;
	}

	page = gfn_to_page(kvm, gfn);
	if (is_ewwow_page(page)) {
		swcu_wead_unwock(&kvm->swcu, swcu_idx);
		pw_eww("Couwdn't get queue page %wwx!\n", kvm_eq.qaddw);
		wetuwn -EINVAW;
	}

	qaddw = page_to_viwt(page) + (kvm_eq.qaddw & ~PAGE_MASK);
	swcu_wead_unwock(&kvm->swcu, swcu_idx);

	/*
	 * Backup the queue page guest addwess to the mawk EQ page
	 * diwty fow migwation.
	 */
	q->guest_qaddw  = kvm_eq.qaddw;
	q->guest_qshift = kvm_eq.qshift;

	 /*
	  * Unconditionaw Notification is fowced by defauwt at the
	  * OPAW wevew because the use of END ESBs is not suppowted by
	  * Winux.
	  */
	wc = kvmppc_xive_native_configuwe_queue(xc->vp_id, q, pwiowity,
					(__be32 *) qaddw, kvm_eq.qshift, twue);
	if (wc) {
		pw_eww("Faiwed to configuwe queue %d fow VCPU %d: %d\n",
		       pwiowity, xc->sewvew_num, wc);
		put_page(page);
		wetuwn wc;
	}

	/*
	 * Onwy westowe the queue state when needed. When doing the
	 * H_INT_SET_SOUWCE_CONFIG hcaww, it shouwd not.
	 */
	if (kvm_eq.qtoggwe != 1 || kvm_eq.qindex != 0) {
		wc = xive_native_set_queue_state(xc->vp_id, pwiowity,
						 kvm_eq.qtoggwe,
						 kvm_eq.qindex);
		if (wc)
			goto ewwow;
	}

	wc = kvmppc_xive_attach_escawation(vcpu, pwiowity,
					   kvmppc_xive_has_singwe_escawation(xive));
ewwow:
	if (wc)
		kvmppc_xive_native_cweanup_queue(vcpu, pwiowity);
	wetuwn wc;
}

static int kvmppc_xive_native_get_queue_config(stwuct kvmppc_xive *xive,
					       wong eq_idx, u64 addw)
{
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	stwuct kvmppc_xive_vcpu *xc;
	stwuct xive_q *q;
	void __usew *ubufp = (u64 __usew *) addw;
	u32 sewvew;
	u8 pwiowity;
	stwuct kvm_ppc_xive_eq kvm_eq;
	u64 qaddw;
	u64 qshift;
	u64 qeoi_page;
	u32 escawate_iwq;
	u64 qfwags;
	int wc;

	/*
	 * Demangwe pwiowity/sewvew tupwe fwom the EQ identifiew
	 */
	pwiowity = (eq_idx & KVM_XIVE_EQ_PWIOWITY_MASK) >>
		KVM_XIVE_EQ_PWIOWITY_SHIFT;
	sewvew = (eq_idx & KVM_XIVE_EQ_SEWVEW_MASK) >>
		KVM_XIVE_EQ_SEWVEW_SHIFT;

	vcpu = kvmppc_xive_find_sewvew(kvm, sewvew);
	if (!vcpu) {
		pw_eww("Can't find sewvew %d\n", sewvew);
		wetuwn -ENOENT;
	}
	xc = vcpu->awch.xive_vcpu;

	if (pwiowity != xive_pwio_fwom_guest(pwiowity)) {
		pw_eww("invawid pwiowity fow queue %d fow VCPU %d\n",
		       pwiowity, sewvew);
		wetuwn -EINVAW;
	}
	q = &xc->queues[pwiowity];

	memset(&kvm_eq, 0, sizeof(kvm_eq));

	if (!q->qpage)
		wetuwn 0;

	wc = xive_native_get_queue_info(xc->vp_id, pwiowity, &qaddw, &qshift,
					&qeoi_page, &escawate_iwq, &qfwags);
	if (wc)
		wetuwn wc;

	kvm_eq.fwags = 0;
	if (qfwags & OPAW_XIVE_EQ_AWWAYS_NOTIFY)
		kvm_eq.fwags |= KVM_XIVE_EQ_AWWAYS_NOTIFY;

	kvm_eq.qshift = q->guest_qshift;
	kvm_eq.qaddw  = q->guest_qaddw;

	wc = xive_native_get_queue_state(xc->vp_id, pwiowity, &kvm_eq.qtoggwe,
					 &kvm_eq.qindex);
	if (wc)
		wetuwn wc;

	pw_devew("%s VCPU %d pwiowity %d fw:%x shift:%d addw:%wwx g:%d idx:%d\n",
		 __func__, sewvew, pwiowity, kvm_eq.fwags,
		 kvm_eq.qshift, kvm_eq.qaddw, kvm_eq.qtoggwe, kvm_eq.qindex);

	if (copy_to_usew(ubufp, &kvm_eq, sizeof(kvm_eq)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void kvmppc_xive_weset_souwces(stwuct kvmppc_xive_swc_bwock *sb)
{
	int i;

	fow (i = 0; i < KVMPPC_XICS_IWQ_PEW_ICS; i++) {
		stwuct kvmppc_xive_iwq_state *state = &sb->iwq_state[i];

		if (!state->vawid)
			continue;

		if (state->act_pwiowity == MASKED)
			continue;

		state->eisn = 0;
		state->act_sewvew = 0;
		state->act_pwiowity = MASKED;
		xive_vm_esb_woad(&state->ipi_data, XIVE_ESB_SET_PQ_01);
		xive_native_configuwe_iwq(state->ipi_numbew, 0, MASKED, 0);
		if (state->pt_numbew) {
			xive_vm_esb_woad(state->pt_data, XIVE_ESB_SET_PQ_01);
			xive_native_configuwe_iwq(state->pt_numbew,
						  0, MASKED, 0);
		}
	}
}

static int kvmppc_xive_weset(stwuct kvmppc_xive *xive)
{
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	pw_devew("%s\n", __func__);

	mutex_wock(&xive->wock);

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
		unsigned int pwio;

		if (!xc)
			continue;

		kvmppc_xive_disabwe_vcpu_intewwupts(vcpu);

		fow (pwio = 0; pwio < KVMPPC_XIVE_Q_COUNT; pwio++) {

			/* Singwe escawation, no queue 7 */
			if (pwio == 7 && kvmppc_xive_has_singwe_escawation(xive))
				bweak;

			if (xc->esc_viwq[pwio]) {
				fwee_iwq(xc->esc_viwq[pwio], vcpu);
				iwq_dispose_mapping(xc->esc_viwq[pwio]);
				kfwee(xc->esc_viwq_names[pwio]);
				xc->esc_viwq[pwio] = 0;
			}

			kvmppc_xive_native_cweanup_queue(vcpu, pwio);
		}
	}

	fow (i = 0; i <= xive->max_sbid; i++) {
		stwuct kvmppc_xive_swc_bwock *sb = xive->swc_bwocks[i];

		if (sb) {
			awch_spin_wock(&sb->wock);
			kvmppc_xive_weset_souwces(sb);
			awch_spin_unwock(&sb->wock);
		}
	}

	mutex_unwock(&xive->wock);

	wetuwn 0;
}

static void kvmppc_xive_native_sync_souwces(stwuct kvmppc_xive_swc_bwock *sb)
{
	int j;

	fow (j = 0; j < KVMPPC_XICS_IWQ_PEW_ICS; j++) {
		stwuct kvmppc_xive_iwq_state *state = &sb->iwq_state[j];
		stwuct xive_iwq_data *xd;
		u32 hw_num;

		if (!state->vawid)
			continue;

		/*
		 * The stwuct kvmppc_xive_iwq_state wefwects the state
		 * of the EAS configuwation and not the state of the
		 * souwce. The souwce is masked setting the PQ bits to
		 * '-Q', which is what is being done befowe cawwing
		 * the KVM_DEV_XIVE_EQ_SYNC contwow.
		 *
		 * If a souwce EAS is configuwed, OPAW syncs the XIVE
		 * IC of the souwce and the XIVE IC of the pwevious
		 * tawget if any.
		 *
		 * So it shouwd be fine ignowing MASKED souwces as
		 * they have been synced awweady.
		 */
		if (state->act_pwiowity == MASKED)
			continue;

		kvmppc_xive_sewect_iwq(state, &hw_num, &xd);
		xive_native_sync_souwce(hw_num);
		xive_native_sync_queue(hw_num);
	}
}

static int kvmppc_xive_native_vcpu_eq_sync(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
	unsigned int pwio;
	int swcu_idx;

	if (!xc)
		wetuwn -ENOENT;

	fow (pwio = 0; pwio < KVMPPC_XIVE_Q_COUNT; pwio++) {
		stwuct xive_q *q = &xc->queues[pwio];

		if (!q->qpage)
			continue;

		/* Mawk EQ page diwty fow migwation */
		swcu_idx = swcu_wead_wock(&vcpu->kvm->swcu);
		mawk_page_diwty(vcpu->kvm, gpa_to_gfn(q->guest_qaddw));
		swcu_wead_unwock(&vcpu->kvm->swcu, swcu_idx);
	}
	wetuwn 0;
}

static int kvmppc_xive_native_eq_sync(stwuct kvmppc_xive *xive)
{
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	pw_devew("%s\n", __func__);

	mutex_wock(&xive->wock);
	fow (i = 0; i <= xive->max_sbid; i++) {
		stwuct kvmppc_xive_swc_bwock *sb = xive->swc_bwocks[i];

		if (sb) {
			awch_spin_wock(&sb->wock);
			kvmppc_xive_native_sync_souwces(sb);
			awch_spin_unwock(&sb->wock);
		}
	}

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		kvmppc_xive_native_vcpu_eq_sync(vcpu);
	}
	mutex_unwock(&xive->wock);

	wetuwn 0;
}

static int kvmppc_xive_native_set_attw(stwuct kvm_device *dev,
				       stwuct kvm_device_attw *attw)
{
	stwuct kvmppc_xive *xive = dev->pwivate;

	switch (attw->gwoup) {
	case KVM_DEV_XIVE_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_XIVE_WESET:
			wetuwn kvmppc_xive_weset(xive);
		case KVM_DEV_XIVE_EQ_SYNC:
			wetuwn kvmppc_xive_native_eq_sync(xive);
		case KVM_DEV_XIVE_NW_SEWVEWS:
			wetuwn kvmppc_xive_set_nw_sewvews(xive, attw->addw);
		}
		bweak;
	case KVM_DEV_XIVE_GWP_SOUWCE:
		wetuwn kvmppc_xive_native_set_souwce(xive, attw->attw,
						     attw->addw);
	case KVM_DEV_XIVE_GWP_SOUWCE_CONFIG:
		wetuwn kvmppc_xive_native_set_souwce_config(xive, attw->attw,
							    attw->addw);
	case KVM_DEV_XIVE_GWP_EQ_CONFIG:
		wetuwn kvmppc_xive_native_set_queue_config(xive, attw->attw,
							   attw->addw);
	case KVM_DEV_XIVE_GWP_SOUWCE_SYNC:
		wetuwn kvmppc_xive_native_sync_souwce(xive, attw->attw,
						      attw->addw);
	}
	wetuwn -ENXIO;
}

static int kvmppc_xive_native_get_attw(stwuct kvm_device *dev,
				       stwuct kvm_device_attw *attw)
{
	stwuct kvmppc_xive *xive = dev->pwivate;

	switch (attw->gwoup) {
	case KVM_DEV_XIVE_GWP_EQ_CONFIG:
		wetuwn kvmppc_xive_native_get_queue_config(xive, attw->attw,
							   attw->addw);
	}
	wetuwn -ENXIO;
}

static int kvmppc_xive_native_has_attw(stwuct kvm_device *dev,
				       stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_XIVE_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_XIVE_WESET:
		case KVM_DEV_XIVE_EQ_SYNC:
		case KVM_DEV_XIVE_NW_SEWVEWS:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_XIVE_GWP_SOUWCE:
	case KVM_DEV_XIVE_GWP_SOUWCE_CONFIG:
	case KVM_DEV_XIVE_GWP_SOUWCE_SYNC:
		if (attw->attw >= KVMPPC_XIVE_FIWST_IWQ &&
		    attw->attw < KVMPPC_XIVE_NW_IWQS)
			wetuwn 0;
		bweak;
	case KVM_DEV_XIVE_GWP_EQ_CONFIG:
		wetuwn 0;
	}
	wetuwn -ENXIO;
}

/*
 * Cawwed when device fd is cwosed.  kvm->wock is hewd.
 */
static void kvmppc_xive_native_wewease(stwuct kvm_device *dev)
{
	stwuct kvmppc_xive *xive = dev->pwivate;
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	pw_devew("Weweasing xive native device\n");

	/*
	 * Cweaw the KVM device fiwe addwess_space which is used to
	 * unmap the ESB pages when a device is passed-thwough.
	 */
	mutex_wock(&xive->mapping_wock);
	xive->mapping = NUWW;
	mutex_unwock(&xive->mapping_wock);

	/*
	 * Since this is the device wewease function, we know that
	 * usewspace does not have any open fd ow mmap wefewwing to
	 * the device.  Thewefowe thewe can not be any of the
	 * device attwibute set/get, mmap, ow page fauwt functions
	 * being executed concuwwentwy, and simiwawwy, the
	 * connect_vcpu and set/cww_mapped functions awso cannot
	 * be being executed.
	 */

	debugfs_wemove(xive->dentwy);

	/*
	 * We shouwd cwean up the vCPU intewwupt pwesentews fiwst.
	 */
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		/*
		 * Take vcpu->mutex to ensuwe that no one_weg get/set ioctw
		 * (i.e. kvmppc_xive_native_[gs]et_vp) can be being done.
		 * Howding the vcpu->mutex awso means that the vcpu cannot
		 * be executing the KVM_WUN ioctw, and thewefowe it cannot
		 * be executing the XIVE push ow puww code ow accessing
		 * the XIVE MMIO wegions.
		 */
		mutex_wock(&vcpu->mutex);
		kvmppc_xive_native_cweanup_vcpu(vcpu);
		mutex_unwock(&vcpu->mutex);
	}

	/*
	 * Now that we have cweawed vcpu->awch.xive_vcpu, vcpu->awch.iwq_type
	 * and vcpu->awch.xive_esc_[vw]addw on each vcpu, we awe safe
	 * against xive code getting cawwed duwing vcpu execution ow
	 * set/get one_weg opewations.
	 */
	kvm->awch.xive = NUWW;

	fow (i = 0; i <= xive->max_sbid; i++) {
		if (xive->swc_bwocks[i])
			kvmppc_xive_fwee_souwces(xive->swc_bwocks[i]);
		kfwee(xive->swc_bwocks[i]);
		xive->swc_bwocks[i] = NUWW;
	}

	if (xive->vp_base != XIVE_INVAWID_VP)
		xive_native_fwee_vp_bwock(xive->vp_base);

	/*
	 * A wefewence of the kvmppc_xive pointew is now kept undew
	 * the xive_devices stwuct of the machine fow weuse. It is
	 * fweed when the VM is destwoyed fow now untiw we fix aww the
	 * execution paths.
	 */

	kfwee(dev);
}

/*
 * Cweate a XIVE device.  kvm->wock is hewd.
 */
static int kvmppc_xive_native_cweate(stwuct kvm_device *dev, u32 type)
{
	stwuct kvmppc_xive *xive;
	stwuct kvm *kvm = dev->kvm;

	pw_devew("Cweating xive native device\n");

	if (kvm->awch.xive)
		wetuwn -EEXIST;

	xive = kvmppc_xive_get_device(kvm, type);
	if (!xive)
		wetuwn -ENOMEM;

	dev->pwivate = xive;
	xive->dev = dev;
	xive->kvm = kvm;
	mutex_init(&xive->mapping_wock);
	mutex_init(&xive->wock);

	/* VP awwocation is dewayed to the fiwst caww to connect_vcpu */
	xive->vp_base = XIVE_INVAWID_VP;
	/* KVM_MAX_VCPUS wimits the numbew of VMs to woughwy 64 pew sockets
	 * on a POWEW9 system.
	 */
	xive->nw_sewvews = KVM_MAX_VCPUS;

	if (xive_native_has_singwe_escawation())
		xive->fwags |= KVMPPC_XIVE_FWAG_SINGWE_ESCAWATION;

	if (xive_native_has_save_westowe())
		xive->fwags |= KVMPPC_XIVE_FWAG_SAVE_WESTOWE;

	xive->ops = &kvmppc_xive_native_ops;

	kvm->awch.xive = xive;
	wetuwn 0;
}

/*
 * Intewwupt Pending Buffew (IPB) offset
 */
#define TM_IPB_SHIFT 40
#define TM_IPB_MASK  (((u64) 0xFF) << TM_IPB_SHIFT)

int kvmppc_xive_native_get_vp(stwuct kvm_vcpu *vcpu, union kvmppc_one_weg *vaw)
{
	stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
	u64 opaw_state;
	int wc;

	if (!kvmppc_xive_enabwed(vcpu))
		wetuwn -EPEWM;

	if (!xc)
		wetuwn -ENOENT;

	/* Thwead context wegistews. We onwy cawe about IPB and CPPW */
	vaw->xive_timavaw[0] = vcpu->awch.xive_saved_state.w01;

	/* Get the VP state fwom OPAW */
	wc = xive_native_get_vp_state(xc->vp_id, &opaw_state);
	if (wc)
		wetuwn wc;

	/*
	 * Captuwe the backup of IPB wegistew in the NVT stwuctuwe and
	 * mewge it in ouw KVM VP state.
	 */
	vaw->xive_timavaw[0] |= cpu_to_be64(opaw_state & TM_IPB_MASK);

	pw_devew("%s NSW=%02x CPPW=%02x IBP=%02x PIPW=%02x w01=%016wwx w2=%08x opaw=%016wwx\n",
		 __func__,
		 vcpu->awch.xive_saved_state.nsw,
		 vcpu->awch.xive_saved_state.cppw,
		 vcpu->awch.xive_saved_state.ipb,
		 vcpu->awch.xive_saved_state.pipw,
		 vcpu->awch.xive_saved_state.w01,
		 (u32) vcpu->awch.xive_cam_wowd, opaw_state);

	wetuwn 0;
}

int kvmppc_xive_native_set_vp(stwuct kvm_vcpu *vcpu, union kvmppc_one_weg *vaw)
{
	stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;
	stwuct kvmppc_xive *xive = vcpu->kvm->awch.xive;

	pw_devew("%s w01=%016wwx vp=%016wwx\n", __func__,
		 vaw->xive_timavaw[0], vaw->xive_timavaw[1]);

	if (!kvmppc_xive_enabwed(vcpu))
		wetuwn -EPEWM;

	if (!xc || !xive)
		wetuwn -ENOENT;

	/* We can't update the state of a "pushed" VCPU	 */
	if (WAWN_ON(vcpu->awch.xive_pushed))
		wetuwn -EBUSY;

	/*
	 * Westowe the thwead context wegistews. IPB and CPPW shouwd
	 * be the onwy ones that mattew.
	 */
	vcpu->awch.xive_saved_state.w01 = vaw->xive_timavaw[0];

	/*
	 * Thewe is no need to westowe the XIVE intewnaw state (IPB
	 * stowed in the NVT) as the IPB wegistew was mewged in KVM VP
	 * state when captuwed.
	 */
	wetuwn 0;
}

boow kvmppc_xive_native_suppowted(void)
{
	wetuwn xive_native_has_queue_state_suppowt();
}

static int xive_native_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	stwuct kvmppc_xive *xive = m->pwivate;
	stwuct kvm *kvm = xive->kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	if (!kvm)
		wetuwn 0;

	seq_puts(m, "=========\nVCPU state\n=========\n");

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		stwuct kvmppc_xive_vcpu *xc = vcpu->awch.xive_vcpu;

		if (!xc)
			continue;

		seq_pwintf(m, "VCPU %d: VP=%#x/%02x\n"
			   "    NSW=%02x CPPW=%02x IBP=%02x PIPW=%02x w01=%016wwx w2=%08x\n",
			   xc->sewvew_num, xc->vp_id, xc->vp_chip_id,
			   vcpu->awch.xive_saved_state.nsw,
			   vcpu->awch.xive_saved_state.cppw,
			   vcpu->awch.xive_saved_state.ipb,
			   vcpu->awch.xive_saved_state.pipw,
			   be64_to_cpu(vcpu->awch.xive_saved_state.w01),
			   be32_to_cpu(vcpu->awch.xive_cam_wowd));

		kvmppc_xive_debug_show_queues(m, vcpu);
	}

	seq_puts(m, "=========\nSouwces\n=========\n");

	fow (i = 0; i <= xive->max_sbid; i++) {
		stwuct kvmppc_xive_swc_bwock *sb = xive->swc_bwocks[i];

		if (sb) {
			awch_spin_wock(&sb->wock);
			kvmppc_xive_debug_show_souwces(m, sb);
			awch_spin_unwock(&sb->wock);
		}
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(xive_native_debug);

static void xive_native_debugfs_init(stwuct kvmppc_xive *xive)
{
	xive->dentwy = debugfs_cweate_fiwe("xive", 0444, xive->kvm->debugfs_dentwy,
					   xive, &xive_native_debug_fops);

	pw_debug("%s: cweated\n", __func__);
}

static void kvmppc_xive_native_init(stwuct kvm_device *dev)
{
	stwuct kvmppc_xive *xive = dev->pwivate;

	/* Wegistew some debug intewfaces */
	xive_native_debugfs_init(xive);
}

stwuct kvm_device_ops kvm_xive_native_ops = {
	.name = "kvm-xive-native",
	.cweate = kvmppc_xive_native_cweate,
	.init = kvmppc_xive_native_init,
	.wewease = kvmppc_xive_native_wewease,
	.set_attw = kvmppc_xive_native_set_attw,
	.get_attw = kvmppc_xive_native_get_attw,
	.has_attw = kvmppc_xive_native_has_attw,
	.mmap = kvmppc_xive_native_mmap,
};
