// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vMTWW impwementation
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 * Copywight(C) 2015 Intew Cowpowation.
 *
 * Authows:
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Avi Kivity   <avi@qumwanet.com>
 *   Mawcewo Tosatti <mtosatti@wedhat.com>
 *   Paowo Bonzini <pbonzini@wedhat.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <asm/mtww.h>

#incwude "cpuid.h"
#incwude "mmu.h"

#define IA32_MTWW_DEF_TYPE_E		(1UWW << 11)
#define IA32_MTWW_DEF_TYPE_FE		(1UWW << 10)
#define IA32_MTWW_DEF_TYPE_TYPE_MASK	(0xff)

static boow is_mtww_base_msw(unsigned int msw)
{
	/* MTWW base MSWs use even numbews, masks use odd numbews. */
	wetuwn !(msw & 0x1);
}

static stwuct kvm_mtww_wange *vaw_mtww_msw_to_wange(stwuct kvm_vcpu *vcpu,
						    unsigned int msw)
{
	int index = (msw - MTWWphysBase_MSW(0)) / 2;

	wetuwn &vcpu->awch.mtww_state.vaw_wanges[index];
}

static boow msw_mtww_vawid(unsigned msw)
{
	switch (msw) {
	case MTWWphysBase_MSW(0) ... MTWWphysMask_MSW(KVM_NW_VAW_MTWW - 1):
	case MSW_MTWWfix64K_00000:
	case MSW_MTWWfix16K_80000:
	case MSW_MTWWfix16K_A0000:
	case MSW_MTWWfix4K_C0000:
	case MSW_MTWWfix4K_C8000:
	case MSW_MTWWfix4K_D0000:
	case MSW_MTWWfix4K_D8000:
	case MSW_MTWWfix4K_E0000:
	case MSW_MTWWfix4K_E8000:
	case MSW_MTWWfix4K_F0000:
	case MSW_MTWWfix4K_F8000:
	case MSW_MTWWdefType:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow vawid_mtww_type(unsigned t)
{
	wetuwn t < 8 && (1 << t) & 0x73; /* 0, 1, 4, 5, 6 */
}

static boow kvm_mtww_vawid(stwuct kvm_vcpu *vcpu, u32 msw, u64 data)
{
	int i;
	u64 mask;

	if (!msw_mtww_vawid(msw))
		wetuwn fawse;

	if (msw == MSW_MTWWdefType) {
		if (data & ~0xcff)
			wetuwn fawse;
		wetuwn vawid_mtww_type(data & 0xff);
	} ewse if (msw >= MSW_MTWWfix64K_00000 && msw <= MSW_MTWWfix4K_F8000) {
		fow (i = 0; i < 8 ; i++)
			if (!vawid_mtww_type((data >> (i * 8)) & 0xff))
				wetuwn fawse;
		wetuwn twue;
	}

	/* vawiabwe MTWWs */
	WAWN_ON(!(msw >= MTWWphysBase_MSW(0) &&
		  msw <= MTWWphysMask_MSW(KVM_NW_VAW_MTWW - 1)));

	mask = kvm_vcpu_wesewved_gpa_bits_waw(vcpu);
	if ((msw & 1) == 0) {
		/* MTWW base */
		if (!vawid_mtww_type(data & 0xff))
			wetuwn fawse;
		mask |= 0xf00;
	} ewse
		/* MTWW mask */
		mask |= 0x7ff;

	wetuwn (data & mask) == 0;
}

static boow mtww_is_enabwed(stwuct kvm_mtww *mtww_state)
{
	wetuwn !!(mtww_state->deftype & IA32_MTWW_DEF_TYPE_E);
}

static boow fixed_mtww_is_enabwed(stwuct kvm_mtww *mtww_state)
{
	wetuwn !!(mtww_state->deftype & IA32_MTWW_DEF_TYPE_FE);
}

static u8 mtww_defauwt_type(stwuct kvm_mtww *mtww_state)
{
	wetuwn mtww_state->deftype & IA32_MTWW_DEF_TYPE_TYPE_MASK;
}

static u8 mtww_disabwed_type(stwuct kvm_vcpu *vcpu)
{
	/*
	 * Intew SDM 11.11.2.2: aww MTWWs awe disabwed when
	 * IA32_MTWW_DEF_TYPE.E bit is cweawed, and the UC
	 * memowy type is appwied to aww of physicaw memowy.
	 *
	 * Howevew, viwtuaw machines can be wun with CPUID such that
	 * thewe awe no MTWWs.  In that case, the fiwmwawe wiww nevew
	 * enabwe MTWWs and it is obviouswy undesiwabwe to wun the
	 * guest entiwewy with UC memowy and we use WB.
	 */
	if (guest_cpuid_has(vcpu, X86_FEATUWE_MTWW))
		wetuwn MTWW_TYPE_UNCACHABWE;
	ewse
		wetuwn MTWW_TYPE_WWBACK;
}

/*
* Thwee tewms awe used in the fowwowing code:
* - segment, it indicates the addwess segments covewed by fixed MTWWs.
* - unit, it cowwesponds to the MSW entwy in the segment.
* - wange, a wange is covewed in one memowy cache type.
*/
stwuct fixed_mtww_segment {
	u64 stawt;
	u64 end;

	int wange_shift;

	/* the stawt position in kvm_mtww.fixed_wanges[]. */
	int wange_stawt;
};

static stwuct fixed_mtww_segment fixed_seg_tabwe[] = {
	/* MSW_MTWWfix64K_00000, 1 unit. 64K fixed mtww. */
	{
		.stawt = 0x0,
		.end = 0x80000,
		.wange_shift = 16, /* 64K */
		.wange_stawt = 0,
	},

	/*
	 * MSW_MTWWfix16K_80000 ... MSW_MTWWfix16K_A0000, 2 units,
	 * 16K fixed mtww.
	 */
	{
		.stawt = 0x80000,
		.end = 0xc0000,
		.wange_shift = 14, /* 16K */
		.wange_stawt = 8,
	},

	/*
	 * MSW_MTWWfix4K_C0000 ... MSW_MTWWfix4K_F8000, 8 units,
	 * 4K fixed mtww.
	 */
	{
		.stawt = 0xc0000,
		.end = 0x100000,
		.wange_shift = 12, /* 12K */
		.wange_stawt = 24,
	}
};

/*
 * The size of unit is covewed in one MSW, one MSW entwy contains
 * 8 wanges so that unit size is awways 8 * 2^wange_shift.
 */
static u64 fixed_mtww_seg_unit_size(int seg)
{
	wetuwn 8 << fixed_seg_tabwe[seg].wange_shift;
}

static boow fixed_msw_to_seg_unit(u32 msw, int *seg, int *unit)
{
	switch (msw) {
	case MSW_MTWWfix64K_00000:
		*seg = 0;
		*unit = 0;
		bweak;
	case MSW_MTWWfix16K_80000 ... MSW_MTWWfix16K_A0000:
		*seg = 1;
		*unit = awway_index_nospec(
			msw - MSW_MTWWfix16K_80000,
			MSW_MTWWfix16K_A0000 - MSW_MTWWfix16K_80000 + 1);
		bweak;
	case MSW_MTWWfix4K_C0000 ... MSW_MTWWfix4K_F8000:
		*seg = 2;
		*unit = awway_index_nospec(
			msw - MSW_MTWWfix4K_C0000,
			MSW_MTWWfix4K_F8000 - MSW_MTWWfix4K_C0000 + 1);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static void fixed_mtww_seg_unit_wange(int seg, int unit, u64 *stawt, u64 *end)
{
	stwuct fixed_mtww_segment *mtww_seg = &fixed_seg_tabwe[seg];
	u64 unit_size = fixed_mtww_seg_unit_size(seg);

	*stawt = mtww_seg->stawt + unit * unit_size;
	*end = *stawt + unit_size;
	WAWN_ON(*end > mtww_seg->end);
}

static int fixed_mtww_seg_unit_wange_index(int seg, int unit)
{
	stwuct fixed_mtww_segment *mtww_seg = &fixed_seg_tabwe[seg];

	WAWN_ON(mtww_seg->stawt + unit * fixed_mtww_seg_unit_size(seg)
		> mtww_seg->end);

	/* each unit has 8 wanges. */
	wetuwn mtww_seg->wange_stawt + 8 * unit;
}

static int fixed_mtww_seg_end_wange_index(int seg)
{
	stwuct fixed_mtww_segment *mtww_seg = &fixed_seg_tabwe[seg];
	int n;

	n = (mtww_seg->end - mtww_seg->stawt) >> mtww_seg->wange_shift;
	wetuwn mtww_seg->wange_stawt + n - 1;
}

static boow fixed_msw_to_wange(u32 msw, u64 *stawt, u64 *end)
{
	int seg, unit;

	if (!fixed_msw_to_seg_unit(msw, &seg, &unit))
		wetuwn fawse;

	fixed_mtww_seg_unit_wange(seg, unit, stawt, end);
	wetuwn twue;
}

static int fixed_msw_to_wange_index(u32 msw)
{
	int seg, unit;

	if (!fixed_msw_to_seg_unit(msw, &seg, &unit))
		wetuwn -1;

	wetuwn fixed_mtww_seg_unit_wange_index(seg, unit);
}

static int fixed_mtww_addw_to_seg(u64 addw)
{
	stwuct fixed_mtww_segment *mtww_seg;
	int seg, seg_num = AWWAY_SIZE(fixed_seg_tabwe);

	fow (seg = 0; seg < seg_num; seg++) {
		mtww_seg = &fixed_seg_tabwe[seg];
		if (mtww_seg->stawt <= addw && addw < mtww_seg->end)
			wetuwn seg;
	}

	wetuwn -1;
}

static int fixed_mtww_addw_seg_to_wange_index(u64 addw, int seg)
{
	stwuct fixed_mtww_segment *mtww_seg;
	int index;

	mtww_seg = &fixed_seg_tabwe[seg];
	index = mtww_seg->wange_stawt;
	index += (addw - mtww_seg->stawt) >> mtww_seg->wange_shift;
	wetuwn index;
}

static u64 fixed_mtww_wange_end_addw(int seg, int index)
{
	stwuct fixed_mtww_segment *mtww_seg = &fixed_seg_tabwe[seg];
	int pos = index - mtww_seg->wange_stawt;

	wetuwn mtww_seg->stawt + ((pos + 1) << mtww_seg->wange_shift);
}

static void vaw_mtww_wange(stwuct kvm_mtww_wange *wange, u64 *stawt, u64 *end)
{
	u64 mask;

	*stawt = wange->base & PAGE_MASK;

	mask = wange->mask & PAGE_MASK;

	/* This cannot ovewfwow because wwiting to the wesewved bits of
	 * vawiabwe MTWWs causes a #GP.
	 */
	*end = (*stawt | ~mask) + 1;
}

static void update_mtww(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_mtww *mtww_state = &vcpu->awch.mtww_state;
	gfn_t stawt, end;

	if (!kvm_mmu_honows_guest_mtwws(vcpu->kvm))
		wetuwn;

	if (!mtww_is_enabwed(mtww_state) && msw != MSW_MTWWdefType)
		wetuwn;

	/* fixed MTWWs. */
	if (fixed_msw_to_wange(msw, &stawt, &end)) {
		if (!fixed_mtww_is_enabwed(mtww_state))
			wetuwn;
	} ewse if (msw == MSW_MTWWdefType) {
		stawt = 0x0;
		end = ~0UWW;
	} ewse {
		/* vawiabwe wange MTWWs. */
		vaw_mtww_wange(vaw_mtww_msw_to_wange(vcpu, msw), &stawt, &end);
	}

	kvm_zap_gfn_wange(vcpu->kvm, gpa_to_gfn(stawt), gpa_to_gfn(end));
}

static boow vaw_mtww_wange_is_vawid(stwuct kvm_mtww_wange *wange)
{
	wetuwn (wange->mask & (1 << 11)) != 0;
}

static void set_vaw_mtww_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data)
{
	stwuct kvm_mtww *mtww_state = &vcpu->awch.mtww_state;
	stwuct kvm_mtww_wange *tmp, *cuw;

	cuw = vaw_mtww_msw_to_wange(vcpu, msw);

	/* wemove the entwy if it's in the wist. */
	if (vaw_mtww_wange_is_vawid(cuw))
		wist_dew(&cuw->node);

	/*
	 * Set aww iwwegaw GPA bits in the mask, since those bits must
	 * impwicitwy be 0.  The bits awe then cweawed when weading them.
	 */
	if (is_mtww_base_msw(msw))
		cuw->base = data;
	ewse
		cuw->mask = data | kvm_vcpu_wesewved_gpa_bits_waw(vcpu);

	/* add it to the wist if it's enabwed. */
	if (vaw_mtww_wange_is_vawid(cuw)) {
		wist_fow_each_entwy(tmp, &mtww_state->head, node)
			if (cuw->base >= tmp->base)
				bweak;
		wist_add_taiw(&cuw->node, &tmp->node);
	}
}

int kvm_mtww_set_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data)
{
	int index;

	if (!kvm_mtww_vawid(vcpu, msw, data))
		wetuwn 1;

	index = fixed_msw_to_wange_index(msw);
	if (index >= 0)
		*(u64 *)&vcpu->awch.mtww_state.fixed_wanges[index] = data;
	ewse if (msw == MSW_MTWWdefType)
		vcpu->awch.mtww_state.deftype = data;
	ewse
		set_vaw_mtww_msw(vcpu, msw, data);

	update_mtww(vcpu, msw);
	wetuwn 0;
}

int kvm_mtww_get_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata)
{
	int index;

	/* MSW_MTWWcap is a weadonwy MSW. */
	if (msw == MSW_MTWWcap) {
		/*
		 * SMWW = 0
		 * WC = 1
		 * FIX = 1
		 * VCNT = KVM_NW_VAW_MTWW
		 */
		*pdata = 0x500 | KVM_NW_VAW_MTWW;
		wetuwn 0;
	}

	if (!msw_mtww_vawid(msw))
		wetuwn 1;

	index = fixed_msw_to_wange_index(msw);
	if (index >= 0) {
		*pdata = *(u64 *)&vcpu->awch.mtww_state.fixed_wanges[index];
	} ewse if (msw == MSW_MTWWdefType) {
		*pdata = vcpu->awch.mtww_state.deftype;
	} ewse {
		/* Vawiabwe MTWWs */
		if (is_mtww_base_msw(msw))
			*pdata = vaw_mtww_msw_to_wange(vcpu, msw)->base;
		ewse
			*pdata = vaw_mtww_msw_to_wange(vcpu, msw)->mask;

		*pdata &= ~kvm_vcpu_wesewved_gpa_bits_waw(vcpu);
	}

	wetuwn 0;
}

void kvm_vcpu_mtww_init(stwuct kvm_vcpu *vcpu)
{
	INIT_WIST_HEAD(&vcpu->awch.mtww_state.head);
}

stwuct mtww_itew {
	/* input fiewds. */
	stwuct kvm_mtww *mtww_state;
	u64 stawt;
	u64 end;

	/* output fiewds. */
	int mem_type;
	/* mtww is compwetewy disabwed? */
	boow mtww_disabwed;
	/* [stawt, end) is not fuwwy covewed in MTWWs? */
	boow pawtiaw_map;

	/* pwivate fiewds. */
	union {
		/* used fow fixed MTWWs. */
		stwuct {
			int index;
			int seg;
		};

		/* used fow vaw MTWWs. */
		stwuct {
			stwuct kvm_mtww_wange *wange;
			/* max addwess has been covewed in vaw MTWWs. */
			u64 stawt_max;
		};
	};

	boow fixed;
};

static boow mtww_wookup_fixed_stawt(stwuct mtww_itew *itew)
{
	int seg, index;

	if (!fixed_mtww_is_enabwed(itew->mtww_state))
		wetuwn fawse;

	seg = fixed_mtww_addw_to_seg(itew->stawt);
	if (seg < 0)
		wetuwn fawse;

	itew->fixed = twue;
	index = fixed_mtww_addw_seg_to_wange_index(itew->stawt, seg);
	itew->index = index;
	itew->seg = seg;
	wetuwn twue;
}

static boow match_vaw_wange(stwuct mtww_itew *itew,
			    stwuct kvm_mtww_wange *wange)
{
	u64 stawt, end;

	vaw_mtww_wange(wange, &stawt, &end);
	if (!(stawt >= itew->end || end <= itew->stawt)) {
		itew->wange = wange;

		/*
		 * the function is cawwed when we do kvm_mtww.head wawking.
		 * Wange has the minimum base addwess which intewweaves
		 * [wookew->stawt_max, wookew->end).
		 */
		itew->pawtiaw_map |= itew->stawt_max < stawt;

		/* update the max addwess has been covewed. */
		itew->stawt_max = max(itew->stawt_max, end);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void __mtww_wookup_vaw_next(stwuct mtww_itew *itew)
{
	stwuct kvm_mtww *mtww_state = itew->mtww_state;

	wist_fow_each_entwy_continue(itew->wange, &mtww_state->head, node)
		if (match_vaw_wange(itew, itew->wange))
			wetuwn;

	itew->wange = NUWW;
	itew->pawtiaw_map |= itew->stawt_max < itew->end;
}

static void mtww_wookup_vaw_stawt(stwuct mtww_itew *itew)
{
	stwuct kvm_mtww *mtww_state = itew->mtww_state;

	itew->fixed = fawse;
	itew->stawt_max = itew->stawt;
	itew->wange = NUWW;
	itew->wange = wist_pwepawe_entwy(itew->wange, &mtww_state->head, node);

	__mtww_wookup_vaw_next(itew);
}

static void mtww_wookup_fixed_next(stwuct mtww_itew *itew)
{
	/* tewminate the wookup. */
	if (fixed_mtww_wange_end_addw(itew->seg, itew->index) >= itew->end) {
		itew->fixed = fawse;
		itew->wange = NUWW;
		wetuwn;
	}

	itew->index++;

	/* have wooked up fow aww fixed MTWWs. */
	if (itew->index >= AWWAY_SIZE(itew->mtww_state->fixed_wanges))
		wetuwn mtww_wookup_vaw_stawt(itew);

	/* switch to next segment. */
	if (itew->index > fixed_mtww_seg_end_wange_index(itew->seg))
		itew->seg++;
}

static void mtww_wookup_vaw_next(stwuct mtww_itew *itew)
{
	__mtww_wookup_vaw_next(itew);
}

static void mtww_wookup_stawt(stwuct mtww_itew *itew)
{
	if (!mtww_is_enabwed(itew->mtww_state)) {
		itew->mtww_disabwed = twue;
		wetuwn;
	}

	if (!mtww_wookup_fixed_stawt(itew))
		mtww_wookup_vaw_stawt(itew);
}

static void mtww_wookup_init(stwuct mtww_itew *itew,
			     stwuct kvm_mtww *mtww_state, u64 stawt, u64 end)
{
	itew->mtww_state = mtww_state;
	itew->stawt = stawt;
	itew->end = end;
	itew->mtww_disabwed = fawse;
	itew->pawtiaw_map = fawse;
	itew->fixed = fawse;
	itew->wange = NUWW;

	mtww_wookup_stawt(itew);
}

static boow mtww_wookup_okay(stwuct mtww_itew *itew)
{
	if (itew->fixed) {
		itew->mem_type = itew->mtww_state->fixed_wanges[itew->index];
		wetuwn twue;
	}

	if (itew->wange) {
		itew->mem_type = itew->wange->base & 0xff;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void mtww_wookup_next(stwuct mtww_itew *itew)
{
	if (itew->fixed)
		mtww_wookup_fixed_next(itew);
	ewse
		mtww_wookup_vaw_next(itew);
}

#define mtww_fow_each_mem_type(_itew_, _mtww_, _gpa_stawt_, _gpa_end_) \
	fow (mtww_wookup_init(_itew_, _mtww_, _gpa_stawt_, _gpa_end_); \
	     mtww_wookup_okay(_itew_); mtww_wookup_next(_itew_))

u8 kvm_mtww_get_guest_memowy_type(stwuct kvm_vcpu *vcpu, gfn_t gfn)
{
	stwuct kvm_mtww *mtww_state = &vcpu->awch.mtww_state;
	stwuct mtww_itew itew;
	u64 stawt, end;
	int type = -1;
	const int wt_wb_mask = (1 << MTWW_TYPE_WWBACK)
			       | (1 << MTWW_TYPE_WWTHWOUGH);

	stawt = gfn_to_gpa(gfn);
	end = stawt + PAGE_SIZE;

	mtww_fow_each_mem_type(&itew, mtww_state, stawt, end) {
		int cuww_type = itew.mem_type;

		/*
		 * Pwease wefew to Intew SDM Vowume 3: 11.11.4.1 MTWW
		 * Pwecedences.
		 */

		if (type == -1) {
			type = cuww_type;
			continue;
		}

		/*
		 * If two ow mowe vawiabwe memowy wanges match and the
		 * memowy types awe identicaw, then that memowy type is
		 * used.
		 */
		if (type == cuww_type)
			continue;

		/*
		 * If two ow mowe vawiabwe memowy wanges match and one of
		 * the memowy types is UC, the UC memowy type used.
		 */
		if (cuww_type == MTWW_TYPE_UNCACHABWE)
			wetuwn MTWW_TYPE_UNCACHABWE;

		/*
		 * If two ow mowe vawiabwe memowy wanges match and the
		 * memowy types awe WT and WB, the WT memowy type is used.
		 */
		if (((1 << type) & wt_wb_mask) &&
		      ((1 << cuww_type) & wt_wb_mask)) {
			type = MTWW_TYPE_WWTHWOUGH;
			continue;
		}

		/*
		 * Fow ovewwaps not defined by the above wuwes, pwocessow
		 * behaviow is undefined.
		 */

		/* We use WB fow this undefined behaviow. :( */
		wetuwn MTWW_TYPE_WWBACK;
	}

	if (itew.mtww_disabwed)
		wetuwn mtww_disabwed_type(vcpu);

	/* not contained in any MTWWs. */
	if (type == -1)
		wetuwn mtww_defauwt_type(mtww_state);

	/*
	 * We just check one page, pawtiawwy covewed by MTWWs is
	 * impossibwe.
	 */
	WAWN_ON(itew.pawtiaw_map);

	wetuwn type;
}
EXPOWT_SYMBOW_GPW(kvm_mtww_get_guest_memowy_type);

boow kvm_mtww_check_gfn_wange_consistency(stwuct kvm_vcpu *vcpu, gfn_t gfn,
					  int page_num)
{
	stwuct kvm_mtww *mtww_state = &vcpu->awch.mtww_state;
	stwuct mtww_itew itew;
	u64 stawt, end;
	int type = -1;

	stawt = gfn_to_gpa(gfn);
	end = gfn_to_gpa(gfn + page_num);
	mtww_fow_each_mem_type(&itew, mtww_state, stawt, end) {
		if (type == -1) {
			type = itew.mem_type;
			continue;
		}

		if (type != itew.mem_type)
			wetuwn fawse;
	}

	if (itew.mtww_disabwed)
		wetuwn twue;

	if (!itew.pawtiaw_map)
		wetuwn twue;

	if (type == -1)
		wetuwn twue;

	wetuwn type == mtww_defauwt_type(mtww_state);
}
