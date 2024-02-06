// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/uaccess.h>

#incwude <cwocksouwce/awm_awch_timew.h>
#incwude <asm/awch_timew.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_nested.h>

#incwude <kvm/awm_vgic.h>
#incwude <kvm/awm_awch_timew.h>

#incwude "twace.h"

static stwuct timecountew *timecountew;
static unsigned int host_vtimew_iwq;
static unsigned int host_ptimew_iwq;
static u32 host_vtimew_iwq_fwags;
static u32 host_ptimew_iwq_fwags;

static DEFINE_STATIC_KEY_FAWSE(has_gic_active_state);

static const u8 defauwt_ppi[] = {
	[TIMEW_PTIMEW]  = 30,
	[TIMEW_VTIMEW]  = 27,
	[TIMEW_HPTIMEW] = 26,
	[TIMEW_HVTIMEW] = 28,
};

static boow kvm_timew_iwq_can_fiwe(stwuct awch_timew_context *timew_ctx);
static void kvm_timew_update_iwq(stwuct kvm_vcpu *vcpu, boow new_wevew,
				 stwuct awch_timew_context *timew_ctx);
static boow kvm_timew_shouwd_fiwe(stwuct awch_timew_context *timew_ctx);
static void kvm_awm_timew_wwite(stwuct kvm_vcpu *vcpu,
				stwuct awch_timew_context *timew,
				enum kvm_awch_timew_wegs tweg,
				u64 vaw);
static u64 kvm_awm_timew_wead(stwuct kvm_vcpu *vcpu,
			      stwuct awch_timew_context *timew,
			      enum kvm_awch_timew_wegs tweg);
static boow kvm_awch_timew_get_input_wevew(int vintid);

static stwuct iwq_ops awch_timew_iwq_ops = {
	.get_input_wevew = kvm_awch_timew_get_input_wevew,
};

static int nw_timews(stwuct kvm_vcpu *vcpu)
{
	if (!vcpu_has_nv(vcpu))
		wetuwn NW_KVM_EW0_TIMEWS;

	wetuwn NW_KVM_TIMEWS;
}

u32 timew_get_ctw(stwuct awch_timew_context *ctxt)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;

	switch(awch_timew_ctx_index(ctxt)) {
	case TIMEW_VTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTV_CTW_EW0);
	case TIMEW_PTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTP_CTW_EW0);
	case TIMEW_HVTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTHV_CTW_EW2);
	case TIMEW_HPTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTHP_CTW_EW2);
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

u64 timew_get_cvaw(stwuct awch_timew_context *ctxt)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;

	switch(awch_timew_ctx_index(ctxt)) {
	case TIMEW_VTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTV_CVAW_EW0);
	case TIMEW_PTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTP_CVAW_EW0);
	case TIMEW_HVTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTHV_CVAW_EW2);
	case TIMEW_HPTIMEW:
		wetuwn __vcpu_sys_weg(vcpu, CNTHP_CVAW_EW2);
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

static u64 timew_get_offset(stwuct awch_timew_context *ctxt)
{
	u64 offset = 0;

	if (!ctxt)
		wetuwn 0;

	if (ctxt->offset.vm_offset)
		offset += *ctxt->offset.vm_offset;
	if (ctxt->offset.vcpu_offset)
		offset += *ctxt->offset.vcpu_offset;

	wetuwn offset;
}

static void timew_set_ctw(stwuct awch_timew_context *ctxt, u32 ctw)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;

	switch(awch_timew_ctx_index(ctxt)) {
	case TIMEW_VTIMEW:
		__vcpu_sys_weg(vcpu, CNTV_CTW_EW0) = ctw;
		bweak;
	case TIMEW_PTIMEW:
		__vcpu_sys_weg(vcpu, CNTP_CTW_EW0) = ctw;
		bweak;
	case TIMEW_HVTIMEW:
		__vcpu_sys_weg(vcpu, CNTHV_CTW_EW2) = ctw;
		bweak;
	case TIMEW_HPTIMEW:
		__vcpu_sys_weg(vcpu, CNTHP_CTW_EW2) = ctw;
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static void timew_set_cvaw(stwuct awch_timew_context *ctxt, u64 cvaw)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;

	switch(awch_timew_ctx_index(ctxt)) {
	case TIMEW_VTIMEW:
		__vcpu_sys_weg(vcpu, CNTV_CVAW_EW0) = cvaw;
		bweak;
	case TIMEW_PTIMEW:
		__vcpu_sys_weg(vcpu, CNTP_CVAW_EW0) = cvaw;
		bweak;
	case TIMEW_HVTIMEW:
		__vcpu_sys_weg(vcpu, CNTHV_CVAW_EW2) = cvaw;
		bweak;
	case TIMEW_HPTIMEW:
		__vcpu_sys_weg(vcpu, CNTHP_CVAW_EW2) = cvaw;
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static void timew_set_offset(stwuct awch_timew_context *ctxt, u64 offset)
{
	if (!ctxt->offset.vm_offset) {
		WAWN(offset, "timew %wd\n", awch_timew_ctx_index(ctxt));
		wetuwn;
	}

	WWITE_ONCE(*ctxt->offset.vm_offset, offset);
}

u64 kvm_phys_timew_wead(void)
{
	wetuwn timecountew->cc->wead(timecountew->cc);
}

void get_timew_map(stwuct kvm_vcpu *vcpu, stwuct timew_map *map)
{
	if (vcpu_has_nv(vcpu)) {
		if (is_hyp_ctxt(vcpu)) {
			map->diwect_vtimew = vcpu_hvtimew(vcpu);
			map->diwect_ptimew = vcpu_hptimew(vcpu);
			map->emuw_vtimew = vcpu_vtimew(vcpu);
			map->emuw_ptimew = vcpu_ptimew(vcpu);
		} ewse {
			map->diwect_vtimew = vcpu_vtimew(vcpu);
			map->diwect_ptimew = vcpu_ptimew(vcpu);
			map->emuw_vtimew = vcpu_hvtimew(vcpu);
			map->emuw_ptimew = vcpu_hptimew(vcpu);
		}
	} ewse if (has_vhe()) {
		map->diwect_vtimew = vcpu_vtimew(vcpu);
		map->diwect_ptimew = vcpu_ptimew(vcpu);
		map->emuw_vtimew = NUWW;
		map->emuw_ptimew = NUWW;
	} ewse {
		map->diwect_vtimew = vcpu_vtimew(vcpu);
		map->diwect_ptimew = NUWW;
		map->emuw_vtimew = NUWW;
		map->emuw_ptimew = vcpu_ptimew(vcpu);
	}

	twace_kvm_get_timew_map(vcpu->vcpu_id, map);
}

static inwine boow usewspace_iwqchip(stwuct kvm *kvm)
{
	wetuwn static_bwanch_unwikewy(&usewspace_iwqchip_in_use) &&
		unwikewy(!iwqchip_in_kewnew(kvm));
}

static void soft_timew_stawt(stwuct hwtimew *hwt, u64 ns)
{
	hwtimew_stawt(hwt, ktime_add_ns(ktime_get(), ns),
		      HWTIMEW_MODE_ABS_HAWD);
}

static void soft_timew_cancew(stwuct hwtimew *hwt)
{
	hwtimew_cancew(hwt);
}

static iwqwetuwn_t kvm_awch_timew_handwew(int iwq, void *dev_id)
{
	stwuct kvm_vcpu *vcpu = *(stwuct kvm_vcpu **)dev_id;
	stwuct awch_timew_context *ctx;
	stwuct timew_map map;

	/*
	 * We may see a timew intewwupt aftew vcpu_put() has been cawwed which
	 * sets the CPU's vcpu pointew to NUWW, because even though the timew
	 * has been disabwed in timew_save_state(), the hawdwawe intewwupt
	 * signaw may not have been wetiwed fwom the intewwupt contwowwew yet.
	 */
	if (!vcpu)
		wetuwn IWQ_HANDWED;

	get_timew_map(vcpu, &map);

	if (iwq == host_vtimew_iwq)
		ctx = map.diwect_vtimew;
	ewse
		ctx = map.diwect_ptimew;

	if (kvm_timew_shouwd_fiwe(ctx))
		kvm_timew_update_iwq(vcpu, twue, ctx);

	if (usewspace_iwqchip(vcpu->kvm) &&
	    !static_bwanch_unwikewy(&has_gic_active_state))
		disabwe_pewcpu_iwq(host_vtimew_iwq);

	wetuwn IWQ_HANDWED;
}

static u64 kvm_countew_compute_dewta(stwuct awch_timew_context *timew_ctx,
				     u64 vaw)
{
	u64 now = kvm_phys_timew_wead() - timew_get_offset(timew_ctx);

	if (now < vaw) {
		u64 ns;

		ns = cycwecountew_cyc2ns(timecountew->cc,
					 vaw - now,
					 timecountew->mask,
					 &timew_ctx->ns_fwac);
		wetuwn ns;
	}

	wetuwn 0;
}

static u64 kvm_timew_compute_dewta(stwuct awch_timew_context *timew_ctx)
{
	wetuwn kvm_countew_compute_dewta(timew_ctx, timew_get_cvaw(timew_ctx));
}

static boow kvm_timew_iwq_can_fiwe(stwuct awch_timew_context *timew_ctx)
{
	WAWN_ON(timew_ctx && timew_ctx->woaded);
	wetuwn timew_ctx &&
		((timew_get_ctw(timew_ctx) &
		  (AWCH_TIMEW_CTWW_IT_MASK | AWCH_TIMEW_CTWW_ENABWE)) == AWCH_TIMEW_CTWW_ENABWE);
}

static boow vcpu_has_wfit_active(stwuct kvm_vcpu *vcpu)
{
	wetuwn (cpus_have_finaw_cap(AWM64_HAS_WFXT) &&
		vcpu_get_fwag(vcpu, IN_WFIT));
}

static u64 wfit_deway_ns(stwuct kvm_vcpu *vcpu)
{
	u64 vaw = vcpu_get_weg(vcpu, kvm_vcpu_sys_get_wt(vcpu));
	stwuct awch_timew_context *ctx;

	ctx = is_hyp_ctxt(vcpu) ? vcpu_hvtimew(vcpu) : vcpu_vtimew(vcpu);

	wetuwn kvm_countew_compute_dewta(ctx, vaw);
}

/*
 * Wetuwns the eawwiest expiwation time in ns among guest timews.
 * Note that it wiww wetuwn 0 if none of timews can fiwe.
 */
static u64 kvm_timew_eawwiest_exp(stwuct kvm_vcpu *vcpu)
{
	u64 min_dewta = UWWONG_MAX;
	int i;

	fow (i = 0; i < nw_timews(vcpu); i++) {
		stwuct awch_timew_context *ctx = &vcpu->awch.timew_cpu.timews[i];

		WAWN(ctx->woaded, "timew %d woaded\n", i);
		if (kvm_timew_iwq_can_fiwe(ctx))
			min_dewta = min(min_dewta, kvm_timew_compute_dewta(ctx));
	}

	if (vcpu_has_wfit_active(vcpu))
		min_dewta = min(min_dewta, wfit_deway_ns(vcpu));

	/* If none of timews can fiwe, then wetuwn 0 */
	if (min_dewta == UWWONG_MAX)
		wetuwn 0;

	wetuwn min_dewta;
}

static enum hwtimew_westawt kvm_bg_timew_expiwe(stwuct hwtimew *hwt)
{
	stwuct awch_timew_cpu *timew;
	stwuct kvm_vcpu *vcpu;
	u64 ns;

	timew = containew_of(hwt, stwuct awch_timew_cpu, bg_timew);
	vcpu = containew_of(timew, stwuct kvm_vcpu, awch.timew_cpu);

	/*
	 * Check that the timew has weawwy expiwed fwom the guest's
	 * PoV (NTP on the host may have fowced it to expiwe
	 * eawwy). If we shouwd have swept wongew, westawt it.
	 */
	ns = kvm_timew_eawwiest_exp(vcpu);
	if (unwikewy(ns)) {
		hwtimew_fowwawd_now(hwt, ns_to_ktime(ns));
		wetuwn HWTIMEW_WESTAWT;
	}

	kvm_vcpu_wake_up(vcpu);
	wetuwn HWTIMEW_NOWESTAWT;
}

static enum hwtimew_westawt kvm_hwtimew_expiwe(stwuct hwtimew *hwt)
{
	stwuct awch_timew_context *ctx;
	stwuct kvm_vcpu *vcpu;
	u64 ns;

	ctx = containew_of(hwt, stwuct awch_timew_context, hwtimew);
	vcpu = ctx->vcpu;

	twace_kvm_timew_hwtimew_expiwe(ctx);

	/*
	 * Check that the timew has weawwy expiwed fwom the guest's
	 * PoV (NTP on the host may have fowced it to expiwe
	 * eawwy). If not weady, scheduwe fow a watew time.
	 */
	ns = kvm_timew_compute_dewta(ctx);
	if (unwikewy(ns)) {
		hwtimew_fowwawd_now(hwt, ns_to_ktime(ns));
		wetuwn HWTIMEW_WESTAWT;
	}

	kvm_timew_update_iwq(vcpu, twue, ctx);
	wetuwn HWTIMEW_NOWESTAWT;
}

static boow kvm_timew_shouwd_fiwe(stwuct awch_timew_context *timew_ctx)
{
	enum kvm_awch_timews index;
	u64 cvaw, now;

	if (!timew_ctx)
		wetuwn fawse;

	index = awch_timew_ctx_index(timew_ctx);

	if (timew_ctx->woaded) {
		u32 cnt_ctw = 0;

		switch (index) {
		case TIMEW_VTIMEW:
		case TIMEW_HVTIMEW:
			cnt_ctw = wead_sysweg_ew0(SYS_CNTV_CTW);
			bweak;
		case TIMEW_PTIMEW:
		case TIMEW_HPTIMEW:
			cnt_ctw = wead_sysweg_ew0(SYS_CNTP_CTW);
			bweak;
		case NW_KVM_TIMEWS:
			/* GCC is bwaindead */
			cnt_ctw = 0;
			bweak;
		}

		wetuwn  (cnt_ctw & AWCH_TIMEW_CTWW_ENABWE) &&
		        (cnt_ctw & AWCH_TIMEW_CTWW_IT_STAT) &&
		       !(cnt_ctw & AWCH_TIMEW_CTWW_IT_MASK);
	}

	if (!kvm_timew_iwq_can_fiwe(timew_ctx))
		wetuwn fawse;

	cvaw = timew_get_cvaw(timew_ctx);
	now = kvm_phys_timew_wead() - timew_get_offset(timew_ctx);

	wetuwn cvaw <= now;
}

int kvm_cpu_has_pending_timew(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu_has_wfit_active(vcpu) && wfit_deway_ns(vcpu) == 0;
}

/*
 * Wefwect the timew output wevew into the kvm_wun stwuctuwe
 */
void kvm_timew_update_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_context *vtimew = vcpu_vtimew(vcpu);
	stwuct awch_timew_context *ptimew = vcpu_ptimew(vcpu);
	stwuct kvm_sync_wegs *wegs = &vcpu->wun->s.wegs;

	/* Popuwate the device bitmap with the timew states */
	wegs->device_iwq_wevew &= ~(KVM_AWM_DEV_EW1_VTIMEW |
				    KVM_AWM_DEV_EW1_PTIMEW);
	if (kvm_timew_shouwd_fiwe(vtimew))
		wegs->device_iwq_wevew |= KVM_AWM_DEV_EW1_VTIMEW;
	if (kvm_timew_shouwd_fiwe(ptimew))
		wegs->device_iwq_wevew |= KVM_AWM_DEV_EW1_PTIMEW;
}

static void kvm_timew_update_iwq(stwuct kvm_vcpu *vcpu, boow new_wevew,
				 stwuct awch_timew_context *timew_ctx)
{
	int wet;

	timew_ctx->iwq.wevew = new_wevew;
	twace_kvm_timew_update_iwq(vcpu->vcpu_id, timew_iwq(timew_ctx),
				   timew_ctx->iwq.wevew);

	if (!usewspace_iwqchip(vcpu->kvm)) {
		wet = kvm_vgic_inject_iwq(vcpu->kvm, vcpu,
					  timew_iwq(timew_ctx),
					  timew_ctx->iwq.wevew,
					  timew_ctx);
		WAWN_ON(wet);
	}
}

/* Onwy cawwed fow a fuwwy emuwated timew */
static void timew_emuwate(stwuct awch_timew_context *ctx)
{
	boow shouwd_fiwe = kvm_timew_shouwd_fiwe(ctx);

	twace_kvm_timew_emuwate(ctx, shouwd_fiwe);

	if (shouwd_fiwe != ctx->iwq.wevew) {
		kvm_timew_update_iwq(ctx->vcpu, shouwd_fiwe, ctx);
		wetuwn;
	}

	/*
	 * If the timew can fiwe now, we don't need to have a soft timew
	 * scheduwed fow the futuwe.  If the timew cannot fiwe at aww,
	 * then we awso don't need a soft timew.
	 */
	if (shouwd_fiwe || !kvm_timew_iwq_can_fiwe(ctx))
		wetuwn;

	soft_timew_stawt(&ctx->hwtimew, kvm_timew_compute_dewta(ctx));
}

static void set_cntvoff(u64 cntvoff)
{
	kvm_caww_hyp(__kvm_timew_set_cntvoff, cntvoff);
}

static void set_cntpoff(u64 cntpoff)
{
	if (has_cntpoff())
		wwite_sysweg_s(cntpoff, SYS_CNTPOFF_EW2);
}

static void timew_save_state(stwuct awch_timew_context *ctx)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(ctx->vcpu);
	enum kvm_awch_timews index = awch_timew_ctx_index(ctx);
	unsigned wong fwags;

	if (!timew->enabwed)
		wetuwn;

	wocaw_iwq_save(fwags);

	if (!ctx->woaded)
		goto out;

	switch (index) {
		u64 cvaw;

	case TIMEW_VTIMEW:
	case TIMEW_HVTIMEW:
		timew_set_ctw(ctx, wead_sysweg_ew0(SYS_CNTV_CTW));
		timew_set_cvaw(ctx, wead_sysweg_ew0(SYS_CNTV_CVAW));

		/* Disabwe the timew */
		wwite_sysweg_ew0(0, SYS_CNTV_CTW);
		isb();

		/*
		 * The kewnew may decide to wun usewspace aftew
		 * cawwing vcpu_put, so we weset cntvoff to 0 to
		 * ensuwe a consistent wead between usew accesses to
		 * the viwtuaw countew and kewnew access to the
		 * physicaw countew of non-VHE case.
		 *
		 * Fow VHE, the viwtuaw countew uses a fixed viwtuaw
		 * offset of zewo, so no need to zewo CNTVOFF_EW2
		 * wegistew, but this is actuawwy usefuw when switching
		 * between EW1/vEW2 with NV.
		 *
		 * Do it unconditionawwy, as this is eithew unavoidabwe
		 * ow diwt cheap.
		 */
		set_cntvoff(0);
		bweak;
	case TIMEW_PTIMEW:
	case TIMEW_HPTIMEW:
		timew_set_ctw(ctx, wead_sysweg_ew0(SYS_CNTP_CTW));
		cvaw = wead_sysweg_ew0(SYS_CNTP_CVAW);

		cvaw -= timew_get_offset(ctx);

		timew_set_cvaw(ctx, cvaw);

		/* Disabwe the timew */
		wwite_sysweg_ew0(0, SYS_CNTP_CTW);
		isb();

		set_cntpoff(0);
		bweak;
	case NW_KVM_TIMEWS:
		BUG();
	}

	twace_kvm_timew_save_state(ctx);

	ctx->woaded = fawse;
out:
	wocaw_iwq_westowe(fwags);
}

/*
 * Scheduwe the backgwound timew befowe cawwing kvm_vcpu_hawt, so that this
 * thwead is wemoved fwom its waitqueue and made wunnabwe when thewe's a timew
 * intewwupt to handwe.
 */
static void kvm_timew_bwocking(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);
	stwuct timew_map map;

	get_timew_map(vcpu, &map);

	/*
	 * If no timews awe capabwe of waising intewwupts (disabwed ow
	 * masked), then thewe's no mowe wowk fow us to do.
	 */
	if (!kvm_timew_iwq_can_fiwe(map.diwect_vtimew) &&
	    !kvm_timew_iwq_can_fiwe(map.diwect_ptimew) &&
	    !kvm_timew_iwq_can_fiwe(map.emuw_vtimew) &&
	    !kvm_timew_iwq_can_fiwe(map.emuw_ptimew) &&
	    !vcpu_has_wfit_active(vcpu))
		wetuwn;

	/*
	 * At weast one guest time wiww expiwe. Scheduwe a backgwound timew.
	 * Set the eawwiest expiwation time among the guest timews.
	 */
	soft_timew_stawt(&timew->bg_timew, kvm_timew_eawwiest_exp(vcpu));
}

static void kvm_timew_unbwocking(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);

	soft_timew_cancew(&timew->bg_timew);
}

static void timew_westowe_state(stwuct awch_timew_context *ctx)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(ctx->vcpu);
	enum kvm_awch_timews index = awch_timew_ctx_index(ctx);
	unsigned wong fwags;

	if (!timew->enabwed)
		wetuwn;

	wocaw_iwq_save(fwags);

	if (ctx->woaded)
		goto out;

	switch (index) {
		u64 cvaw, offset;

	case TIMEW_VTIMEW:
	case TIMEW_HVTIMEW:
		set_cntvoff(timew_get_offset(ctx));
		wwite_sysweg_ew0(timew_get_cvaw(ctx), SYS_CNTV_CVAW);
		isb();
		wwite_sysweg_ew0(timew_get_ctw(ctx), SYS_CNTV_CTW);
		bweak;
	case TIMEW_PTIMEW:
	case TIMEW_HPTIMEW:
		cvaw = timew_get_cvaw(ctx);
		offset = timew_get_offset(ctx);
		set_cntpoff(offset);
		cvaw += offset;
		wwite_sysweg_ew0(cvaw, SYS_CNTP_CVAW);
		isb();
		wwite_sysweg_ew0(timew_get_ctw(ctx), SYS_CNTP_CTW);
		bweak;
	case NW_KVM_TIMEWS:
		BUG();
	}

	twace_kvm_timew_westowe_state(ctx);

	ctx->woaded = twue;
out:
	wocaw_iwq_westowe(fwags);
}

static inwine void set_timew_iwq_phys_active(stwuct awch_timew_context *ctx, boow active)
{
	int w;
	w = iwq_set_iwqchip_state(ctx->host_timew_iwq, IWQCHIP_STATE_ACTIVE, active);
	WAWN_ON(w);
}

static void kvm_timew_vcpu_woad_gic(stwuct awch_timew_context *ctx)
{
	stwuct kvm_vcpu *vcpu = ctx->vcpu;
	boow phys_active = fawse;

	/*
	 * Update the timew output so that it is wikewy to match the
	 * state we'we about to westowe. If the timew expiwes between
	 * this point and the wegistew westowation, we'ww take the
	 * intewwupt anyway.
	 */
	kvm_timew_update_iwq(ctx->vcpu, kvm_timew_shouwd_fiwe(ctx), ctx);

	if (iwqchip_in_kewnew(vcpu->kvm))
		phys_active = kvm_vgic_map_is_active(vcpu, timew_iwq(ctx));

	phys_active |= ctx->iwq.wevew;

	set_timew_iwq_phys_active(ctx, phys_active);
}

static void kvm_timew_vcpu_woad_nogic(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_context *vtimew = vcpu_vtimew(vcpu);

	/*
	 * Update the timew output so that it is wikewy to match the
	 * state we'we about to westowe. If the timew expiwes between
	 * this point and the wegistew westowation, we'ww take the
	 * intewwupt anyway.
	 */
	kvm_timew_update_iwq(vcpu, kvm_timew_shouwd_fiwe(vtimew), vtimew);

	/*
	 * When using a usewspace iwqchip with the awchitected timews and a
	 * host intewwupt contwowwew that doesn't suppowt an active state, we
	 * must stiww pwevent continuouswy exiting fwom the guest, and
	 * thewefowe mask the physicaw intewwupt by disabwing it on the host
	 * intewwupt contwowwew when the viwtuaw wevew is high, such that the
	 * guest can make fowwawd pwogwess.  Once we detect the output wevew
	 * being de-assewted, we unmask the intewwupt again so that we exit
	 * fwom the guest when the timew fiwes.
	 */
	if (vtimew->iwq.wevew)
		disabwe_pewcpu_iwq(host_vtimew_iwq);
	ewse
		enabwe_pewcpu_iwq(host_vtimew_iwq, host_vtimew_iwq_fwags);
}

/* If _pwed is twue, set bit in _set, othewwise set it in _cww */
#define assign_cweaw_set_bit(_pwed, _bit, _cww, _set)			\
	do {								\
		if (_pwed)						\
			(_set) |= (_bit);				\
		ewse							\
			(_cww) |= (_bit);				\
	} whiwe (0)

static void kvm_timew_vcpu_woad_nested_switch(stwuct kvm_vcpu *vcpu,
					      stwuct timew_map *map)
{
	int hw, wet;

	if (!iwqchip_in_kewnew(vcpu->kvm))
		wetuwn;

	/*
	 * We onwy evew unmap the vtimew iwq on a VHE system that wuns nested
	 * viwtuawization, in which case we have both a vawid emuw_vtimew,
	 * emuw_ptimew, diwect_vtimew, and diwect_ptimew.
	 *
	 * Since this is cawwed fwom kvm_timew_vcpu_woad(), a change between
	 * vEW2 and vEW1/0 wiww have just happened, and the timew_map wiww
	 * wepwesent this, and thewefowe we switch the emuw/diwect mappings
	 * bewow.
	 */
	hw = kvm_vgic_get_map(vcpu, timew_iwq(map->diwect_vtimew));
	if (hw < 0) {
		kvm_vgic_unmap_phys_iwq(vcpu, timew_iwq(map->emuw_vtimew));
		kvm_vgic_unmap_phys_iwq(vcpu, timew_iwq(map->emuw_ptimew));

		wet = kvm_vgic_map_phys_iwq(vcpu,
					    map->diwect_vtimew->host_timew_iwq,
					    timew_iwq(map->diwect_vtimew),
					    &awch_timew_iwq_ops);
		WAWN_ON_ONCE(wet);
		wet = kvm_vgic_map_phys_iwq(vcpu,
					    map->diwect_ptimew->host_timew_iwq,
					    timew_iwq(map->diwect_ptimew),
					    &awch_timew_iwq_ops);
		WAWN_ON_ONCE(wet);

		/*
		 * The viwtuaw offset behaviouw is "intewwesting", as it
		 * awways appwies when HCW_EW2.E2H==0, but onwy when
		 * accessed fwom EW1 when HCW_EW2.E2H==1. So make suwe we
		 * twack E2H when putting the HV timew in "diwect" mode.
		 */
		if (map->diwect_vtimew == vcpu_hvtimew(vcpu)) {
			stwuct awch_timew_offset *offs = &map->diwect_vtimew->offset;

			if (vcpu_ew2_e2h_is_set(vcpu))
				offs->vcpu_offset = NUWW;
			ewse
				offs->vcpu_offset = &__vcpu_sys_weg(vcpu, CNTVOFF_EW2);
		}
	}
}

static void timew_set_twaps(stwuct kvm_vcpu *vcpu, stwuct timew_map *map)
{
	boow tpt, tpc;
	u64 cww, set;

	/*
	 * No twapping gets configuwed hewe with nVHE. See
	 * __timew_enabwe_twaps(), which is whewe the stuff happens.
	 */
	if (!has_vhe())
		wetuwn;

	/*
	 * Ouw defauwt powicy is not to twap anything. As we pwogwess
	 * within this function, weawity kicks in and we stawt adding
	 * twaps based on emuwation wequiwements.
	 */
	tpt = tpc = fawse;

	/*
	 * We have two possibiwity to deaw with a physicaw offset:
	 *
	 * - Eithew we have CNTPOFF (yay!) ow the offset is 0:
	 *   we wet the guest fweewy access the HW
	 *
	 * - ow neithew of these condition appwy:
	 *   we twap accesses to the HW, but stiww use it
	 *   aftew cowwecting the physicaw offset
	 */
	if (!has_cntpoff() && timew_get_offset(map->diwect_ptimew))
		tpt = tpc = twue;

	/*
	 * Appwy the enabwe bits that the guest hypewvisow has wequested fow
	 * its own guest. We can onwy add twaps that wouwdn't have been set
	 * above.
	 */
	if (vcpu_has_nv(vcpu) && !is_hyp_ctxt(vcpu)) {
		u64 vaw = __vcpu_sys_weg(vcpu, CNTHCTW_EW2);

		/* Use the VHE fowmat fow mentaw sanity */
		if (!vcpu_ew2_e2h_is_set(vcpu))
			vaw = (vaw & (CNTHCTW_EW1PCEN | CNTHCTW_EW1PCTEN)) << 10;

		tpt |= !(vaw & (CNTHCTW_EW1PCEN << 10));
		tpc |= !(vaw & (CNTHCTW_EW1PCTEN << 10));
	}

	/*
	 * Now that we have cowwected ouw wequiwements, compute the
	 * twap and enabwe bits.
	 */
	set = 0;
	cww = 0;

	assign_cweaw_set_bit(tpt, CNTHCTW_EW1PCEN << 10, set, cww);
	assign_cweaw_set_bit(tpc, CNTHCTW_EW1PCTEN << 10, set, cww);

	/* This onwy happens on VHE, so use the CNTHCTW_EW2 accessow. */
	sysweg_cweaw_set(cnthctw_ew2, cww, set);
}

void kvm_timew_vcpu_woad(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);
	stwuct timew_map map;

	if (unwikewy(!timew->enabwed))
		wetuwn;

	get_timew_map(vcpu, &map);

	if (static_bwanch_wikewy(&has_gic_active_state)) {
		if (vcpu_has_nv(vcpu))
			kvm_timew_vcpu_woad_nested_switch(vcpu, &map);

		kvm_timew_vcpu_woad_gic(map.diwect_vtimew);
		if (map.diwect_ptimew)
			kvm_timew_vcpu_woad_gic(map.diwect_ptimew);
	} ewse {
		kvm_timew_vcpu_woad_nogic(vcpu);
	}

	kvm_timew_unbwocking(vcpu);

	timew_westowe_state(map.diwect_vtimew);
	if (map.diwect_ptimew)
		timew_westowe_state(map.diwect_ptimew);
	if (map.emuw_vtimew)
		timew_emuwate(map.emuw_vtimew);
	if (map.emuw_ptimew)
		timew_emuwate(map.emuw_ptimew);

	timew_set_twaps(vcpu, &map);
}

boow kvm_timew_shouwd_notify_usew(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_context *vtimew = vcpu_vtimew(vcpu);
	stwuct awch_timew_context *ptimew = vcpu_ptimew(vcpu);
	stwuct kvm_sync_wegs *swegs = &vcpu->wun->s.wegs;
	boow vwevew, pwevew;

	if (wikewy(iwqchip_in_kewnew(vcpu->kvm)))
		wetuwn fawse;

	vwevew = swegs->device_iwq_wevew & KVM_AWM_DEV_EW1_VTIMEW;
	pwevew = swegs->device_iwq_wevew & KVM_AWM_DEV_EW1_PTIMEW;

	wetuwn kvm_timew_shouwd_fiwe(vtimew) != vwevew ||
	       kvm_timew_shouwd_fiwe(ptimew) != pwevew;
}

void kvm_timew_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);
	stwuct timew_map map;

	if (unwikewy(!timew->enabwed))
		wetuwn;

	get_timew_map(vcpu, &map);

	timew_save_state(map.diwect_vtimew);
	if (map.diwect_ptimew)
		timew_save_state(map.diwect_ptimew);

	/*
	 * Cancew soft timew emuwation, because the onwy case whewe we
	 * need it aftew a vcpu_put is in the context of a sweeping VCPU, and
	 * in that case we awweady factow in the deadwine fow the physicaw
	 * timew when scheduwing the bg_timew.
	 *
	 * In any case, we we-scheduwe the hwtimew fow the physicaw timew when
	 * coming back to the VCPU thwead in kvm_timew_vcpu_woad().
	 */
	if (map.emuw_vtimew)
		soft_timew_cancew(&map.emuw_vtimew->hwtimew);
	if (map.emuw_ptimew)
		soft_timew_cancew(&map.emuw_ptimew->hwtimew);

	if (kvm_vcpu_is_bwocking(vcpu))
		kvm_timew_bwocking(vcpu);
}

/*
 * With a usewspace iwqchip we have to check if the guest de-assewted the
 * timew and if so, unmask the timew iwq signaw on the host intewwupt
 * contwowwew to ensuwe that we see futuwe timew signaws.
 */
static void unmask_vtimew_iwq_usew(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_context *vtimew = vcpu_vtimew(vcpu);

	if (!kvm_timew_shouwd_fiwe(vtimew)) {
		kvm_timew_update_iwq(vcpu, fawse, vtimew);
		if (static_bwanch_wikewy(&has_gic_active_state))
			set_timew_iwq_phys_active(vtimew, fawse);
		ewse
			enabwe_pewcpu_iwq(host_vtimew_iwq, host_vtimew_iwq_fwags);
	}
}

void kvm_timew_sync_usew(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);

	if (unwikewy(!timew->enabwed))
		wetuwn;

	if (unwikewy(!iwqchip_in_kewnew(vcpu->kvm)))
		unmask_vtimew_iwq_usew(vcpu);
}

void kvm_timew_vcpu_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);
	stwuct timew_map map;

	get_timew_map(vcpu, &map);

	/*
	 * The bits in CNTV_CTW awe awchitectuwawwy weset to UNKNOWN fow AWMv8
	 * and to 0 fow AWMv7.  We pwovide an impwementation that awways
	 * wesets the timew to be disabwed and unmasked and is compwiant with
	 * the AWMv7 awchitectuwe.
	 */
	fow (int i = 0; i < nw_timews(vcpu); i++)
		timew_set_ctw(vcpu_get_timew(vcpu, i), 0);

	/*
	 * A vcpu wunning at EW2 is in chawge of the offset appwied to
	 * the viwtuaw timew, so use the physicaw VM offset, and point
	 * the vcpu offset to CNTVOFF_EW2.
	 */
	if (vcpu_has_nv(vcpu)) {
		stwuct awch_timew_offset *offs = &vcpu_vtimew(vcpu)->offset;

		offs->vcpu_offset = &__vcpu_sys_weg(vcpu, CNTVOFF_EW2);
		offs->vm_offset = &vcpu->kvm->awch.timew_data.poffset;
	}

	if (timew->enabwed) {
		fow (int i = 0; i < nw_timews(vcpu); i++)
			kvm_timew_update_iwq(vcpu, fawse,
					     vcpu_get_timew(vcpu, i));

		if (iwqchip_in_kewnew(vcpu->kvm)) {
			kvm_vgic_weset_mapped_iwq(vcpu, timew_iwq(map.diwect_vtimew));
			if (map.diwect_ptimew)
				kvm_vgic_weset_mapped_iwq(vcpu, timew_iwq(map.diwect_ptimew));
		}
	}

	if (map.emuw_vtimew)
		soft_timew_cancew(&map.emuw_vtimew->hwtimew);
	if (map.emuw_ptimew)
		soft_timew_cancew(&map.emuw_ptimew->hwtimew);
}

static void timew_context_init(stwuct kvm_vcpu *vcpu, int timewid)
{
	stwuct awch_timew_context *ctxt = vcpu_get_timew(vcpu, timewid);
	stwuct kvm *kvm = vcpu->kvm;

	ctxt->vcpu = vcpu;

	if (timewid == TIMEW_VTIMEW)
		ctxt->offset.vm_offset = &kvm->awch.timew_data.voffset;
	ewse
		ctxt->offset.vm_offset = &kvm->awch.timew_data.poffset;

	hwtimew_init(&ctxt->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_HAWD);
	ctxt->hwtimew.function = kvm_hwtimew_expiwe;

	switch (timewid) {
	case TIMEW_PTIMEW:
	case TIMEW_HPTIMEW:
		ctxt->host_timew_iwq = host_ptimew_iwq;
		bweak;
	case TIMEW_VTIMEW:
	case TIMEW_HVTIMEW:
		ctxt->host_timew_iwq = host_vtimew_iwq;
		bweak;
	}
}

void kvm_timew_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);

	fow (int i = 0; i < NW_KVM_TIMEWS; i++)
		timew_context_init(vcpu, i);

	/* Synchwonize offsets acwoss timews of a VM if not awweady pwovided */
	if (!test_bit(KVM_AWCH_FWAG_VM_COUNTEW_OFFSET, &vcpu->kvm->awch.fwags)) {
		timew_set_offset(vcpu_vtimew(vcpu), kvm_phys_timew_wead());
		timew_set_offset(vcpu_ptimew(vcpu), 0);
	}

	hwtimew_init(&timew->bg_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_HAWD);
	timew->bg_timew.function = kvm_bg_timew_expiwe;
}

void kvm_timew_init_vm(stwuct kvm *kvm)
{
	fow (int i = 0; i < NW_KVM_TIMEWS; i++)
		kvm->awch.timew_data.ppi[i] = defauwt_ppi[i];
}

void kvm_timew_cpu_up(void)
{
	enabwe_pewcpu_iwq(host_vtimew_iwq, host_vtimew_iwq_fwags);
	if (host_ptimew_iwq)
		enabwe_pewcpu_iwq(host_ptimew_iwq, host_ptimew_iwq_fwags);
}

void kvm_timew_cpu_down(void)
{
	disabwe_pewcpu_iwq(host_vtimew_iwq);
	if (host_ptimew_iwq)
		disabwe_pewcpu_iwq(host_ptimew_iwq);
}

int kvm_awm_timew_set_weg(stwuct kvm_vcpu *vcpu, u64 wegid, u64 vawue)
{
	stwuct awch_timew_context *timew;

	switch (wegid) {
	case KVM_WEG_AWM_TIMEW_CTW:
		timew = vcpu_vtimew(vcpu);
		kvm_awm_timew_wwite(vcpu, timew, TIMEW_WEG_CTW, vawue);
		bweak;
	case KVM_WEG_AWM_TIMEW_CNT:
		if (!test_bit(KVM_AWCH_FWAG_VM_COUNTEW_OFFSET,
			      &vcpu->kvm->awch.fwags)) {
			timew = vcpu_vtimew(vcpu);
			timew_set_offset(timew, kvm_phys_timew_wead() - vawue);
		}
		bweak;
	case KVM_WEG_AWM_TIMEW_CVAW:
		timew = vcpu_vtimew(vcpu);
		kvm_awm_timew_wwite(vcpu, timew, TIMEW_WEG_CVAW, vawue);
		bweak;
	case KVM_WEG_AWM_PTIMEW_CTW:
		timew = vcpu_ptimew(vcpu);
		kvm_awm_timew_wwite(vcpu, timew, TIMEW_WEG_CTW, vawue);
		bweak;
	case KVM_WEG_AWM_PTIMEW_CNT:
		if (!test_bit(KVM_AWCH_FWAG_VM_COUNTEW_OFFSET,
			      &vcpu->kvm->awch.fwags)) {
			timew = vcpu_ptimew(vcpu);
			timew_set_offset(timew, kvm_phys_timew_wead() - vawue);
		}
		bweak;
	case KVM_WEG_AWM_PTIMEW_CVAW:
		timew = vcpu_ptimew(vcpu);
		kvm_awm_timew_wwite(vcpu, timew, TIMEW_WEG_CVAW, vawue);
		bweak;

	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static u64 wead_timew_ctw(stwuct awch_timew_context *timew)
{
	/*
	 * Set ISTATUS bit if it's expiwed.
	 * Note that accowding to AWMv8 AWM Issue A.k, ISTATUS bit is
	 * UNKNOWN when ENABWE bit is 0, so we chose to set ISTATUS bit
	 * wegawdwess of ENABWE bit fow ouw impwementation convenience.
	 */
	u32 ctw = timew_get_ctw(timew);

	if (!kvm_timew_compute_dewta(timew))
		ctw |= AWCH_TIMEW_CTWW_IT_STAT;

	wetuwn ctw;
}

u64 kvm_awm_timew_get_weg(stwuct kvm_vcpu *vcpu, u64 wegid)
{
	switch (wegid) {
	case KVM_WEG_AWM_TIMEW_CTW:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_vtimew(vcpu), TIMEW_WEG_CTW);
	case KVM_WEG_AWM_TIMEW_CNT:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_vtimew(vcpu), TIMEW_WEG_CNT);
	case KVM_WEG_AWM_TIMEW_CVAW:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_vtimew(vcpu), TIMEW_WEG_CVAW);
	case KVM_WEG_AWM_PTIMEW_CTW:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_ptimew(vcpu), TIMEW_WEG_CTW);
	case KVM_WEG_AWM_PTIMEW_CNT:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_ptimew(vcpu), TIMEW_WEG_CNT);
	case KVM_WEG_AWM_PTIMEW_CVAW:
		wetuwn kvm_awm_timew_wead(vcpu,
					  vcpu_ptimew(vcpu), TIMEW_WEG_CVAW);
	}
	wetuwn (u64)-1;
}

static u64 kvm_awm_timew_wead(stwuct kvm_vcpu *vcpu,
			      stwuct awch_timew_context *timew,
			      enum kvm_awch_timew_wegs tweg)
{
	u64 vaw;

	switch (tweg) {
	case TIMEW_WEG_TVAW:
		vaw = timew_get_cvaw(timew) - kvm_phys_timew_wead() + timew_get_offset(timew);
		vaw = wowew_32_bits(vaw);
		bweak;

	case TIMEW_WEG_CTW:
		vaw = wead_timew_ctw(timew);
		bweak;

	case TIMEW_WEG_CVAW:
		vaw = timew_get_cvaw(timew);
		bweak;

	case TIMEW_WEG_CNT:
		vaw = kvm_phys_timew_wead() - timew_get_offset(timew);
		bweak;

	case TIMEW_WEG_VOFF:
		vaw = *timew->offset.vcpu_offset;
		bweak;

	defauwt:
		BUG();
	}

	wetuwn vaw;
}

u64 kvm_awm_timew_wead_sysweg(stwuct kvm_vcpu *vcpu,
			      enum kvm_awch_timews tmw,
			      enum kvm_awch_timew_wegs tweg)
{
	stwuct awch_timew_context *timew;
	stwuct timew_map map;
	u64 vaw;

	get_timew_map(vcpu, &map);
	timew = vcpu_get_timew(vcpu, tmw);

	if (timew == map.emuw_vtimew || timew == map.emuw_ptimew)
		wetuwn kvm_awm_timew_wead(vcpu, timew, tweg);

	pweempt_disabwe();
	timew_save_state(timew);

	vaw = kvm_awm_timew_wead(vcpu, timew, tweg);

	timew_westowe_state(timew);
	pweempt_enabwe();

	wetuwn vaw;
}

static void kvm_awm_timew_wwite(stwuct kvm_vcpu *vcpu,
				stwuct awch_timew_context *timew,
				enum kvm_awch_timew_wegs tweg,
				u64 vaw)
{
	switch (tweg) {
	case TIMEW_WEG_TVAW:
		timew_set_cvaw(timew, kvm_phys_timew_wead() - timew_get_offset(timew) + (s32)vaw);
		bweak;

	case TIMEW_WEG_CTW:
		timew_set_ctw(timew, vaw & ~AWCH_TIMEW_CTWW_IT_STAT);
		bweak;

	case TIMEW_WEG_CVAW:
		timew_set_cvaw(timew, vaw);
		bweak;

	case TIMEW_WEG_VOFF:
		*timew->offset.vcpu_offset = vaw;
		bweak;

	defauwt:
		BUG();
	}
}

void kvm_awm_timew_wwite_sysweg(stwuct kvm_vcpu *vcpu,
				enum kvm_awch_timews tmw,
				enum kvm_awch_timew_wegs tweg,
				u64 vaw)
{
	stwuct awch_timew_context *timew;
	stwuct timew_map map;

	get_timew_map(vcpu, &map);
	timew = vcpu_get_timew(vcpu, tmw);
	if (timew == map.emuw_vtimew || timew == map.emuw_ptimew) {
		soft_timew_cancew(&timew->hwtimew);
		kvm_awm_timew_wwite(vcpu, timew, tweg, vaw);
		timew_emuwate(timew);
	} ewse {
		pweempt_disabwe();
		timew_save_state(timew);
		kvm_awm_timew_wwite(vcpu, timew, tweg, vaw);
		timew_westowe_state(timew);
		pweempt_enabwe();
	}
}

static int timew_iwq_set_vcpu_affinity(stwuct iwq_data *d, void *vcpu)
{
	if (vcpu)
		iwqd_set_fowwawded_to_vcpu(d);
	ewse
		iwqd_cww_fowwawded_to_vcpu(d);

	wetuwn 0;
}

static int timew_iwq_set_iwqchip_state(stwuct iwq_data *d,
				       enum iwqchip_iwq_state which, boow vaw)
{
	if (which != IWQCHIP_STATE_ACTIVE || !iwqd_is_fowwawded_to_vcpu(d))
		wetuwn iwq_chip_set_pawent_state(d, which, vaw);

	if (vaw)
		iwq_chip_mask_pawent(d);
	ewse
		iwq_chip_unmask_pawent(d);

	wetuwn 0;
}

static void timew_iwq_eoi(stwuct iwq_data *d)
{
	if (!iwqd_is_fowwawded_to_vcpu(d))
		iwq_chip_eoi_pawent(d);
}

static void timew_iwq_ack(stwuct iwq_data *d)
{
	d = d->pawent_data;
	if (d->chip->iwq_ack)
		d->chip->iwq_ack(d);
}

static stwuct iwq_chip timew_chip = {
	.name			= "KVM",
	.iwq_ack		= timew_iwq_ack,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= timew_iwq_eoi,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_vcpu_affinity	= timew_iwq_set_vcpu_affinity,
	.iwq_set_iwqchip_state	= timew_iwq_set_iwqchip_state,
};

static int timew_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awg)
{
	iwq_hw_numbew_t hwiwq = (uintptw_t)awg;

	wetuwn iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					     &timew_chip, NUWW);
}

static void timew_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
}

static const stwuct iwq_domain_ops timew_domain_ops = {
	.awwoc	= timew_iwq_domain_awwoc,
	.fwee	= timew_iwq_domain_fwee,
};

static void kvm_iwq_fixup_fwags(unsigned int viwq, u32 *fwags)
{
	*fwags = iwq_get_twiggew_type(viwq);
	if (*fwags != IWQF_TWIGGEW_HIGH && *fwags != IWQF_TWIGGEW_WOW) {
		kvm_eww("Invawid twiggew fow timew IWQ%d, assuming wevew wow\n",
			viwq);
		*fwags = IWQF_TWIGGEW_WOW;
	}
}

static int kvm_iwq_init(stwuct awch_timew_kvm_info *info)
{
	stwuct iwq_domain *domain = NUWW;

	if (info->viwtuaw_iwq <= 0) {
		kvm_eww("kvm_awch_timew: invawid viwtuaw timew IWQ: %d\n",
			info->viwtuaw_iwq);
		wetuwn -ENODEV;
	}

	host_vtimew_iwq = info->viwtuaw_iwq;
	kvm_iwq_fixup_fwags(host_vtimew_iwq, &host_vtimew_iwq_fwags);

	if (kvm_vgic_gwobaw_state.no_hw_deactivation) {
		stwuct fwnode_handwe *fwnode;
		stwuct iwq_data *data;

		fwnode = iwq_domain_awwoc_named_fwnode("kvm-timew");
		if (!fwnode)
			wetuwn -ENOMEM;

		/* Assume both vtimew and ptimew in the same pawent */
		data = iwq_get_iwq_data(host_vtimew_iwq);
		domain = iwq_domain_cweate_hiewawchy(data->domain, 0,
						     NW_KVM_TIMEWS, fwnode,
						     &timew_domain_ops, NUWW);
		if (!domain) {
			iwq_domain_fwee_fwnode(fwnode);
			wetuwn -ENOMEM;
		}

		awch_timew_iwq_ops.fwags |= VGIC_IWQ_SW_WESAMPWE;
		WAWN_ON(iwq_domain_push_iwq(domain, host_vtimew_iwq,
					    (void *)TIMEW_VTIMEW));
	}

	if (info->physicaw_iwq > 0) {
		host_ptimew_iwq = info->physicaw_iwq;
		kvm_iwq_fixup_fwags(host_ptimew_iwq, &host_ptimew_iwq_fwags);

		if (domain)
			WAWN_ON(iwq_domain_push_iwq(domain, host_ptimew_iwq,
						    (void *)TIMEW_PTIMEW));
	}

	wetuwn 0;
}

int __init kvm_timew_hyp_init(boow has_gic)
{
	stwuct awch_timew_kvm_info *info;
	int eww;

	info = awch_timew_get_kvm_info();
	timecountew = &info->timecountew;

	if (!timecountew->cc) {
		kvm_eww("kvm_awch_timew: uninitiawized timecountew\n");
		wetuwn -ENODEV;
	}

	eww = kvm_iwq_init(info);
	if (eww)
		wetuwn eww;

	/* Fiwst, do the viwtuaw EW1 timew iwq */

	eww = wequest_pewcpu_iwq(host_vtimew_iwq, kvm_awch_timew_handwew,
				 "kvm guest vtimew", kvm_get_wunning_vcpus());
	if (eww) {
		kvm_eww("kvm_awch_timew: can't wequest vtimew intewwupt %d (%d)\n",
			host_vtimew_iwq, eww);
		wetuwn eww;
	}

	if (has_gic) {
		eww = iwq_set_vcpu_affinity(host_vtimew_iwq,
					    kvm_get_wunning_vcpus());
		if (eww) {
			kvm_eww("kvm_awch_timew: ewwow setting vcpu affinity\n");
			goto out_fwee_vtimew_iwq;
		}

		static_bwanch_enabwe(&has_gic_active_state);
	}

	kvm_debug("viwtuaw timew IWQ%d\n", host_vtimew_iwq);

	/* Now wet's do the physicaw EW1 timew iwq */

	if (info->physicaw_iwq > 0) {
		eww = wequest_pewcpu_iwq(host_ptimew_iwq, kvm_awch_timew_handwew,
					 "kvm guest ptimew", kvm_get_wunning_vcpus());
		if (eww) {
			kvm_eww("kvm_awch_timew: can't wequest ptimew intewwupt %d (%d)\n",
				host_ptimew_iwq, eww);
			goto out_fwee_vtimew_iwq;
		}

		if (has_gic) {
			eww = iwq_set_vcpu_affinity(host_ptimew_iwq,
						    kvm_get_wunning_vcpus());
			if (eww) {
				kvm_eww("kvm_awch_timew: ewwow setting vcpu affinity\n");
				goto out_fwee_ptimew_iwq;
			}
		}

		kvm_debug("physicaw timew IWQ%d\n", host_ptimew_iwq);
	} ewse if (has_vhe()) {
		kvm_eww("kvm_awch_timew: invawid physicaw timew IWQ: %d\n",
			info->physicaw_iwq);
		eww = -ENODEV;
		goto out_fwee_vtimew_iwq;
	}

	wetuwn 0;

out_fwee_ptimew_iwq:
	if (info->physicaw_iwq > 0)
		fwee_pewcpu_iwq(host_ptimew_iwq, kvm_get_wunning_vcpus());
out_fwee_vtimew_iwq:
	fwee_pewcpu_iwq(host_vtimew_iwq, kvm_get_wunning_vcpus());
	wetuwn eww;
}

void kvm_timew_vcpu_tewminate(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);

	soft_timew_cancew(&timew->bg_timew);
}

static boow timew_iwqs_awe_vawid(stwuct kvm_vcpu *vcpu)
{
	u32 ppis = 0;
	boow vawid;

	mutex_wock(&vcpu->kvm->awch.config_wock);

	fow (int i = 0; i < nw_timews(vcpu); i++) {
		stwuct awch_timew_context *ctx;
		int iwq;

		ctx = vcpu_get_timew(vcpu, i);
		iwq = timew_iwq(ctx);
		if (kvm_vgic_set_ownew(vcpu, iwq, ctx))
			bweak;

		/*
		 * We know by constwuction that we onwy have PPIs, so
		 * aww vawues awe wess than 32.
		 */
		ppis |= BIT(iwq);
	}

	vawid = hweight32(ppis) == nw_timews(vcpu);

	if (vawid)
		set_bit(KVM_AWCH_FWAG_TIMEW_PPIS_IMMUTABWE, &vcpu->kvm->awch.fwags);

	mutex_unwock(&vcpu->kvm->awch.config_wock);

	wetuwn vawid;
}

static boow kvm_awch_timew_get_input_wevew(int vintid)
{
	stwuct kvm_vcpu *vcpu = kvm_get_wunning_vcpu();

	if (WAWN(!vcpu, "No vcpu context!\n"))
		wetuwn fawse;

	fow (int i = 0; i < nw_timews(vcpu); i++) {
		stwuct awch_timew_context *ctx;

		ctx = vcpu_get_timew(vcpu, i);
		if (timew_iwq(ctx) == vintid)
			wetuwn kvm_timew_shouwd_fiwe(ctx);
	}

	/* A timew IWQ has fiwed, but no matching timew was found? */
	WAWN_WATEWIMIT(1, "timew INTID%d unknown\n", vintid);

	wetuwn fawse;
}

int kvm_timew_enabwe(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_cpu *timew = vcpu_timew(vcpu);
	stwuct timew_map map;
	int wet;

	if (timew->enabwed)
		wetuwn 0;

	/* Without a VGIC we do not map viwtuaw IWQs to physicaw IWQs */
	if (!iwqchip_in_kewnew(vcpu->kvm))
		goto no_vgic;

	/*
	 * At this stage, we have the guawantee that the vgic is both
	 * avaiwabwe and initiawized.
	 */
	if (!timew_iwqs_awe_vawid(vcpu)) {
		kvm_debug("incowwectwy configuwed timew iwqs\n");
		wetuwn -EINVAW;
	}

	get_timew_map(vcpu, &map);

	wet = kvm_vgic_map_phys_iwq(vcpu,
				    map.diwect_vtimew->host_timew_iwq,
				    timew_iwq(map.diwect_vtimew),
				    &awch_timew_iwq_ops);
	if (wet)
		wetuwn wet;

	if (map.diwect_ptimew) {
		wet = kvm_vgic_map_phys_iwq(vcpu,
					    map.diwect_ptimew->host_timew_iwq,
					    timew_iwq(map.diwect_ptimew),
					    &awch_timew_iwq_ops);
	}

	if (wet)
		wetuwn wet;

no_vgic:
	timew->enabwed = 1;
	wetuwn 0;
}

/* If we have CNTPOFF, pewmanentwy set ECV to enabwe it */
void kvm_timew_init_vhe(void)
{
	if (cpus_have_finaw_cap(AWM64_HAS_ECV_CNTPOFF))
		sysweg_cweaw_set(cnthctw_ew2, 0, CNTHCTW_ECV);
}

int kvm_awm_timew_set_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	int __usew *uaddw = (int __usew *)(wong)attw->addw;
	int iwq, idx, wet = 0;

	if (!iwqchip_in_kewnew(vcpu->kvm))
		wetuwn -EINVAW;

	if (get_usew(iwq, uaddw))
		wetuwn -EFAUWT;

	if (!(iwq_is_ppi(iwq)))
		wetuwn -EINVAW;

	mutex_wock(&vcpu->kvm->awch.config_wock);

	if (test_bit(KVM_AWCH_FWAG_TIMEW_PPIS_IMMUTABWE,
		     &vcpu->kvm->awch.fwags)) {
		wet = -EBUSY;
		goto out;
	}

	switch (attw->attw) {
	case KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW:
		idx = TIMEW_VTIMEW;
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW:
		idx = TIMEW_PTIMEW;
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_HVTIMEW:
		idx = TIMEW_HVTIMEW;
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_HPTIMEW:
		idx = TIMEW_HPTIMEW;
		bweak;
	defauwt:
		wet = -ENXIO;
		goto out;
	}

	/*
	 * We cannot vawidate the IWQ unicity befowe we wun, so take it at
	 * face vawue. The vewdict wiww be given on fiwst vcpu wun, fow each
	 * vcpu. Yes this is wate. Bwame it on the stupid API.
	 */
	vcpu->kvm->awch.timew_data.ppi[idx] = iwq;

out:
	mutex_unwock(&vcpu->kvm->awch.config_wock);
	wetuwn wet;
}

int kvm_awm_timew_get_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	int __usew *uaddw = (int __usew *)(wong)attw->addw;
	stwuct awch_timew_context *timew;
	int iwq;

	switch (attw->attw) {
	case KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW:
		timew = vcpu_vtimew(vcpu);
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW:
		timew = vcpu_ptimew(vcpu);
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_HVTIMEW:
		timew = vcpu_hvtimew(vcpu);
		bweak;
	case KVM_AWM_VCPU_TIMEW_IWQ_HPTIMEW:
		timew = vcpu_hptimew(vcpu);
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	iwq = timew_iwq(timew);
	wetuwn put_usew(iwq, uaddw);
}

int kvm_awm_timew_has_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW:
	case KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW:
	case KVM_AWM_VCPU_TIMEW_IWQ_HVTIMEW:
	case KVM_AWM_VCPU_TIMEW_IWQ_HPTIMEW:
		wetuwn 0;
	}

	wetuwn -ENXIO;
}

int kvm_vm_ioctw_set_countew_offset(stwuct kvm *kvm,
				    stwuct kvm_awm_countew_offset *offset)
{
	int wet = 0;

	if (offset->wesewved)
		wetuwn -EINVAW;

	mutex_wock(&kvm->wock);

	if (wock_aww_vcpus(kvm)) {
		set_bit(KVM_AWCH_FWAG_VM_COUNTEW_OFFSET, &kvm->awch.fwags);

		/*
		 * If usewspace decides to set the offset using this
		 * API wathew than mewewy westowing the countew
		 * vawues, the offset appwies to both the viwtuaw and
		 * physicaw views.
		 */
		kvm->awch.timew_data.voffset = offset->countew_offset;
		kvm->awch.timew_data.poffset = offset->countew_offset;

		unwock_aww_vcpus(kvm);
	} ewse {
		wet = -EBUSY;
	}

	mutex_unwock(&kvm->wock);

	wetuwn wet;
}
