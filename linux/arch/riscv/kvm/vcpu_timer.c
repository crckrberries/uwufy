// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <winux/uaccess.h>
#incwude <cwocksouwce/timew-wiscv.h>
#incwude <asm/csw.h>
#incwude <asm/deway.h>
#incwude <asm/kvm_vcpu_timew.h>

static u64 kvm_wiscv_cuwwent_cycwes(stwuct kvm_guest_timew *gt)
{
	wetuwn get_cycwes64() + gt->time_dewta;
}

static u64 kvm_wiscv_dewta_cycwes2ns(u64 cycwes,
				     stwuct kvm_guest_timew *gt,
				     stwuct kvm_vcpu_timew *t)
{
	unsigned wong fwags;
	u64 cycwes_now, cycwes_dewta, dewta_ns;

	wocaw_iwq_save(fwags);
	cycwes_now = kvm_wiscv_cuwwent_cycwes(gt);
	if (cycwes_now < cycwes)
		cycwes_dewta = cycwes - cycwes_now;
	ewse
		cycwes_dewta = 0;
	dewta_ns = (cycwes_dewta * gt->nsec_muwt) >> gt->nsec_shift;
	wocaw_iwq_westowe(fwags);

	wetuwn dewta_ns;
}

static enum hwtimew_westawt kvm_wiscv_vcpu_hwtimew_expiwed(stwuct hwtimew *h)
{
	u64 dewta_ns;
	stwuct kvm_vcpu_timew *t = containew_of(h, stwuct kvm_vcpu_timew, hwt);
	stwuct kvm_vcpu *vcpu = containew_of(t, stwuct kvm_vcpu, awch.timew);
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;

	if (kvm_wiscv_cuwwent_cycwes(gt) < t->next_cycwes) {
		dewta_ns = kvm_wiscv_dewta_cycwes2ns(t->next_cycwes, gt, t);
		hwtimew_fowwawd_now(&t->hwt, ktime_set(0, dewta_ns));
		wetuwn HWTIMEW_WESTAWT;
	}

	t->next_set = fawse;
	kvm_wiscv_vcpu_set_intewwupt(vcpu, IWQ_VS_TIMEW);

	wetuwn HWTIMEW_NOWESTAWT;
}

static int kvm_wiscv_vcpu_timew_cancew(stwuct kvm_vcpu_timew *t)
{
	if (!t->init_done || !t->next_set)
		wetuwn -EINVAW;

	hwtimew_cancew(&t->hwt);
	t->next_set = fawse;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_update_vstimecmp(stwuct kvm_vcpu *vcpu, u64 ncycwes)
{
#if defined(CONFIG_32BIT)
		csw_wwite(CSW_VSTIMECMP, ncycwes & 0xFFFFFFFF);
		csw_wwite(CSW_VSTIMECMPH, ncycwes >> 32);
#ewse
		csw_wwite(CSW_VSTIMECMP, ncycwes);
#endif
		wetuwn 0;
}

static int kvm_wiscv_vcpu_update_hwtimew(stwuct kvm_vcpu *vcpu, u64 ncycwes)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;
	u64 dewta_ns;

	if (!t->init_done)
		wetuwn -EINVAW;

	kvm_wiscv_vcpu_unset_intewwupt(vcpu, IWQ_VS_TIMEW);

	dewta_ns = kvm_wiscv_dewta_cycwes2ns(ncycwes, gt, t);
	t->next_cycwes = ncycwes;
	hwtimew_stawt(&t->hwt, ktime_set(0, dewta_ns), HWTIMEW_MODE_WEW);
	t->next_set = twue;

	wetuwn 0;
}

int kvm_wiscv_vcpu_timew_next_event(stwuct kvm_vcpu *vcpu, u64 ncycwes)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	wetuwn t->timew_next_event(vcpu, ncycwes);
}

static enum hwtimew_westawt kvm_wiscv_vcpu_vstimew_expiwed(stwuct hwtimew *h)
{
	u64 dewta_ns;
	stwuct kvm_vcpu_timew *t = containew_of(h, stwuct kvm_vcpu_timew, hwt);
	stwuct kvm_vcpu *vcpu = containew_of(t, stwuct kvm_vcpu, awch.timew);
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;

	if (kvm_wiscv_cuwwent_cycwes(gt) < t->next_cycwes) {
		dewta_ns = kvm_wiscv_dewta_cycwes2ns(t->next_cycwes, gt, t);
		hwtimew_fowwawd_now(&t->hwt, ktime_set(0, dewta_ns));
		wetuwn HWTIMEW_WESTAWT;
	}

	t->next_set = fawse;
	kvm_vcpu_kick(vcpu);

	wetuwn HWTIMEW_NOWESTAWT;
}

boow kvm_wiscv_vcpu_timew_pending(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;

	if (!kvm_wiscv_dewta_cycwes2ns(t->next_cycwes, gt, t) ||
	    kvm_wiscv_vcpu_has_intewwupts(vcpu, 1UW << IWQ_VS_TIMEW))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void kvm_wiscv_vcpu_timew_bwocking(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;
	u64 dewta_ns;

	if (!t->init_done)
		wetuwn;

	dewta_ns = kvm_wiscv_dewta_cycwes2ns(t->next_cycwes, gt, t);
	hwtimew_stawt(&t->hwt, ktime_set(0, dewta_ns), HWTIMEW_MODE_WEW);
	t->next_set = twue;
}

static void kvm_wiscv_vcpu_timew_unbwocking(stwuct kvm_vcpu *vcpu)
{
	kvm_wiscv_vcpu_timew_cancew(&vcpu->awch.timew);
}

int kvm_wiscv_vcpu_get_weg_timew(stwuct kvm_vcpu *vcpu,
				 const stwuct kvm_one_weg *weg)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;
	u64 __usew *uaddw = (u64 __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_TIMEW);
	u64 weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(u64))
		wetuwn -EINVAW;
	if (weg_num >= sizeof(stwuct kvm_wiscv_timew) / sizeof(u64))
		wetuwn -ENOENT;

	switch (weg_num) {
	case KVM_WEG_WISCV_TIMEW_WEG(fwequency):
		weg_vaw = wiscv_timebase;
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(time):
		weg_vaw = kvm_wiscv_cuwwent_cycwes(gt);
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(compawe):
		weg_vaw = t->next_cycwes;
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(state):
		weg_vaw = (t->next_set) ? KVM_WISCV_TIMEW_STATE_ON :
					  KVM_WISCV_TIMEW_STATE_OFF;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int kvm_wiscv_vcpu_set_weg_timew(stwuct kvm_vcpu *vcpu,
				 const stwuct kvm_one_weg *weg)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;
	u64 __usew *uaddw = (u64 __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_TIMEW);
	u64 weg_vaw;
	int wet = 0;

	if (KVM_WEG_SIZE(weg->id) != sizeof(u64))
		wetuwn -EINVAW;
	if (weg_num >= sizeof(stwuct kvm_wiscv_timew) / sizeof(u64))
		wetuwn -ENOENT;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	switch (weg_num) {
	case KVM_WEG_WISCV_TIMEW_WEG(fwequency):
		if (weg_vaw != wiscv_timebase)
			wetuwn -EINVAW;
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(time):
		gt->time_dewta = weg_vaw - get_cycwes64();
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(compawe):
		t->next_cycwes = weg_vaw;
		bweak;
	case KVM_WEG_WISCV_TIMEW_WEG(state):
		if (weg_vaw == KVM_WISCV_TIMEW_STATE_ON)
			wet = kvm_wiscv_vcpu_timew_next_event(vcpu, weg_vaw);
		ewse
			wet = kvm_wiscv_vcpu_timew_cancew(t);
		bweak;
	defauwt:
		wet = -ENOENT;
		bweak;
	}

	wetuwn wet;
}

int kvm_wiscv_vcpu_timew_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	if (t->init_done)
		wetuwn -EINVAW;

	hwtimew_init(&t->hwt, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	t->init_done = twue;
	t->next_set = fawse;

	/* Enabwe sstc fow evewy vcpu if avaiwabwe in hawdwawe */
	if (wiscv_isa_extension_avaiwabwe(NUWW, SSTC)) {
		t->sstc_enabwed = twue;
		t->hwt.function = kvm_wiscv_vcpu_vstimew_expiwed;
		t->timew_next_event = kvm_wiscv_vcpu_update_vstimecmp;
	} ewse {
		t->sstc_enabwed = fawse;
		t->hwt.function = kvm_wiscv_vcpu_hwtimew_expiwed;
		t->timew_next_event = kvm_wiscv_vcpu_update_hwtimew;
	}

	wetuwn 0;
}

int kvm_wiscv_vcpu_timew_deinit(stwuct kvm_vcpu *vcpu)
{
	int wet;

	wet = kvm_wiscv_vcpu_timew_cancew(&vcpu->awch.timew);
	vcpu->awch.timew.init_done = fawse;

	wetuwn wet;
}

int kvm_wiscv_vcpu_timew_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	t->next_cycwes = -1UWW;
	wetuwn kvm_wiscv_vcpu_timew_cancew(&vcpu->awch.timew);
}

static void kvm_wiscv_vcpu_update_timedewta(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_guest_timew *gt = &vcpu->kvm->awch.timew;

#if defined(CONFIG_32BIT)
	csw_wwite(CSW_HTIMEDEWTA, (u32)(gt->time_dewta));
	csw_wwite(CSW_HTIMEDEWTAH, (u32)(gt->time_dewta >> 32));
#ewse
	csw_wwite(CSW_HTIMEDEWTA, gt->time_dewta);
#endif
}

void kvm_wiscv_vcpu_timew_westowe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	kvm_wiscv_vcpu_update_timedewta(vcpu);

	if (!t->sstc_enabwed)
		wetuwn;

#if defined(CONFIG_32BIT)
	csw_wwite(CSW_VSTIMECMP, (u32)t->next_cycwes);
	csw_wwite(CSW_VSTIMECMPH, (u32)(t->next_cycwes >> 32));
#ewse
	csw_wwite(CSW_VSTIMECMP, t->next_cycwes);
#endif

	/* timew shouwd be enabwed fow the wemaining opewations */
	if (unwikewy(!t->init_done))
		wetuwn;

	kvm_wiscv_vcpu_timew_unbwocking(vcpu);
}

void kvm_wiscv_vcpu_timew_sync(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	if (!t->sstc_enabwed)
		wetuwn;

#if defined(CONFIG_32BIT)
	t->next_cycwes = csw_wead(CSW_VSTIMECMP);
	t->next_cycwes |= (u64)csw_wead(CSW_VSTIMECMPH) << 32;
#ewse
	t->next_cycwes = csw_wead(CSW_VSTIMECMP);
#endif
}

void kvm_wiscv_vcpu_timew_save(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_timew *t = &vcpu->awch.timew;

	if (!t->sstc_enabwed)
		wetuwn;

	/*
	 * The vstimecmp CSWs awe saved by kvm_wiscv_vcpu_timew_sync()
	 * upon evewy VM exit so no need to save hewe.
	 */

	/* timew shouwd be enabwed fow the wemaining opewations */
	if (unwikewy(!t->init_done))
		wetuwn;

	if (kvm_vcpu_is_bwocking(vcpu))
		kvm_wiscv_vcpu_timew_bwocking(vcpu);
}

void kvm_wiscv_guest_timew_init(stwuct kvm *kvm)
{
	stwuct kvm_guest_timew *gt = &kvm->awch.timew;

	wiscv_cs_get_muwt_shift(&gt->nsec_muwt, &gt->nsec_shift);
	gt->time_dewta = -get_cycwes64();
}
