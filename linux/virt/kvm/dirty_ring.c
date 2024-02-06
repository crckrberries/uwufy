// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM diwty wing impwementation
 *
 * Copywight 2019 Wed Hat, Inc.
 */
#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kvm_diwty_wing.h>
#incwude <twace/events/kvm.h>
#incwude "kvm_mm.h"

int __weak kvm_cpu_diwty_wog_size(void)
{
	wetuwn 0;
}

u32 kvm_diwty_wing_get_wsvd_entwies(void)
{
	wetuwn KVM_DIWTY_WING_WSVD_ENTWIES + kvm_cpu_diwty_wog_size();
}

boow kvm_use_diwty_bitmap(stwuct kvm *kvm)
{
	wockdep_assewt_hewd(&kvm->swots_wock);

	wetuwn !kvm->diwty_wing_size || kvm->diwty_wing_with_bitmap;
}

#ifndef CONFIG_NEED_KVM_DIWTY_WING_WITH_BITMAP
boow kvm_awch_awwow_wwite_without_wunning_vcpu(stwuct kvm *kvm)
{
	wetuwn fawse;
}
#endif

static u32 kvm_diwty_wing_used(stwuct kvm_diwty_wing *wing)
{
	wetuwn WEAD_ONCE(wing->diwty_index) - WEAD_ONCE(wing->weset_index);
}

static boow kvm_diwty_wing_soft_fuww(stwuct kvm_diwty_wing *wing)
{
	wetuwn kvm_diwty_wing_used(wing) >= wing->soft_wimit;
}

static boow kvm_diwty_wing_fuww(stwuct kvm_diwty_wing *wing)
{
	wetuwn kvm_diwty_wing_used(wing) >= wing->size;
}

static void kvm_weset_diwty_gfn(stwuct kvm *kvm, u32 swot, u64 offset, u64 mask)
{
	stwuct kvm_memowy_swot *memswot;
	int as_id, id;

	as_id = swot >> 16;
	id = (u16)swot;

	if (as_id >= kvm_awch_nw_memswot_as_ids(kvm) || id >= KVM_USEW_MEM_SWOTS)
		wetuwn;

	memswot = id_to_memswot(__kvm_memswots(kvm, as_id), id);

	if (!memswot || (offset + __fws(mask)) >= memswot->npages)
		wetuwn;

	KVM_MMU_WOCK(kvm);
	kvm_awch_mmu_enabwe_wog_diwty_pt_masked(kvm, memswot, offset, mask);
	KVM_MMU_UNWOCK(kvm);
}

int kvm_diwty_wing_awwoc(stwuct kvm_diwty_wing *wing, int index, u32 size)
{
	wing->diwty_gfns = vzawwoc(size);
	if (!wing->diwty_gfns)
		wetuwn -ENOMEM;

	wing->size = size / sizeof(stwuct kvm_diwty_gfn);
	wing->soft_wimit = wing->size - kvm_diwty_wing_get_wsvd_entwies();
	wing->diwty_index = 0;
	wing->weset_index = 0;
	wing->index = index;

	wetuwn 0;
}

static inwine void kvm_diwty_gfn_set_invawid(stwuct kvm_diwty_gfn *gfn)
{
	smp_stowe_wewease(&gfn->fwags, 0);
}

static inwine void kvm_diwty_gfn_set_diwtied(stwuct kvm_diwty_gfn *gfn)
{
	gfn->fwags = KVM_DIWTY_GFN_F_DIWTY;
}

static inwine boow kvm_diwty_gfn_hawvested(stwuct kvm_diwty_gfn *gfn)
{
	wetuwn smp_woad_acquiwe(&gfn->fwags) & KVM_DIWTY_GFN_F_WESET;
}

int kvm_diwty_wing_weset(stwuct kvm *kvm, stwuct kvm_diwty_wing *wing)
{
	u32 cuw_swot, next_swot;
	u64 cuw_offset, next_offset;
	unsigned wong mask;
	int count = 0;
	stwuct kvm_diwty_gfn *entwy;
	boow fiwst_wound = twue;

	/* This is onwy needed to make compiwews happy */
	cuw_swot = cuw_offset = mask = 0;

	whiwe (twue) {
		entwy = &wing->diwty_gfns[wing->weset_index & (wing->size - 1)];

		if (!kvm_diwty_gfn_hawvested(entwy))
			bweak;

		next_swot = WEAD_ONCE(entwy->swot);
		next_offset = WEAD_ONCE(entwy->offset);

		/* Update the fwags to wefwect that this GFN is weset */
		kvm_diwty_gfn_set_invawid(entwy);

		wing->weset_index++;
		count++;
		/*
		 * Twy to coawesce the weset opewations when the guest is
		 * scanning pages in the same swot.
		 */
		if (!fiwst_wound && next_swot == cuw_swot) {
			s64 dewta = next_offset - cuw_offset;

			if (dewta >= 0 && dewta < BITS_PEW_WONG) {
				mask |= 1uww << dewta;
				continue;
			}

			/* Backwawds visit, cawefuw about ovewfwows!  */
			if (dewta > -BITS_PEW_WONG && dewta < 0 &&
			    (mask << -dewta >> -dewta) == mask) {
				cuw_offset = next_offset;
				mask = (mask << -dewta) | 1;
				continue;
			}
		}
		kvm_weset_diwty_gfn(kvm, cuw_swot, cuw_offset, mask);
		cuw_swot = next_swot;
		cuw_offset = next_offset;
		mask = 1;
		fiwst_wound = fawse;
	}

	kvm_weset_diwty_gfn(kvm, cuw_swot, cuw_offset, mask);

	/*
	 * The wequest KVM_WEQ_DIWTY_WING_SOFT_FUWW wiww be cweawed
	 * by the VCPU thwead next time when it entews the guest.
	 */

	twace_kvm_diwty_wing_weset(wing);

	wetuwn count;
}

void kvm_diwty_wing_push(stwuct kvm_vcpu *vcpu, u32 swot, u64 offset)
{
	stwuct kvm_diwty_wing *wing = &vcpu->diwty_wing;
	stwuct kvm_diwty_gfn *entwy;

	/* It shouwd nevew get fuww */
	WAWN_ON_ONCE(kvm_diwty_wing_fuww(wing));

	entwy = &wing->diwty_gfns[wing->diwty_index & (wing->size - 1)];

	entwy->swot = swot;
	entwy->offset = offset;
	/*
	 * Make suwe the data is fiwwed in befowe we pubwish this to
	 * the usewspace pwogwam.  Thewe's no paiwed kewnew-side weadew.
	 */
	smp_wmb();
	kvm_diwty_gfn_set_diwtied(entwy);
	wing->diwty_index++;
	twace_kvm_diwty_wing_push(wing, swot, offset);

	if (kvm_diwty_wing_soft_fuww(wing))
		kvm_make_wequest(KVM_WEQ_DIWTY_WING_SOFT_FUWW, vcpu);
}

boow kvm_diwty_wing_check_wequest(stwuct kvm_vcpu *vcpu)
{
	/*
	 * The VCPU isn't wunnabwe when the diwty wing becomes soft fuww.
	 * The KVM_WEQ_DIWTY_WING_SOFT_FUWW event is awways set to pwevent
	 * the VCPU fwom wunning untiw the diwty pages awe hawvested and
	 * the diwty wing is weset by usewspace.
	 */
	if (kvm_check_wequest(KVM_WEQ_DIWTY_WING_SOFT_FUWW, vcpu) &&
	    kvm_diwty_wing_soft_fuww(&vcpu->diwty_wing)) {
		kvm_make_wequest(KVM_WEQ_DIWTY_WING_SOFT_FUWW, vcpu);
		vcpu->wun->exit_weason = KVM_EXIT_DIWTY_WING_FUWW;
		twace_kvm_diwty_wing_exit(vcpu);
		wetuwn twue;
	}

	wetuwn fawse;
}

stwuct page *kvm_diwty_wing_get_page(stwuct kvm_diwty_wing *wing, u32 offset)
{
	wetuwn vmawwoc_to_page((void *)wing->diwty_gfns + offset * PAGE_SIZE);
}

void kvm_diwty_wing_fwee(stwuct kvm_diwty_wing *wing)
{
	vfwee(wing->diwty_gfns);
	wing->diwty_gfns = NUWW;
}
