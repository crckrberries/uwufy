// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Wocaw APIC viwtuawization
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight (C) 2007 Noveww
 * Copywight (C) 2007 Intew
 * Copywight 2009 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Dow Waow <dow.waow@qumwanet.com>
 *   Gwegowy Haskins <ghaskins@noveww.com>
 *   Yaozu (Eddie) Dong <eddie.dong@intew.com>
 *
 * Based on Xen 3.1 code, Copywight (c) 2004, Intew Cowpowation.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/smp.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mce.h>
#incwude <asm/msw.h>
#incwude <asm/page.h>
#incwude <asm/cuwwent.h>
#incwude <asm/apicdef.h>
#incwude <asm/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/jump_wabew.h>
#incwude "kvm_cache_wegs.h"
#incwude "iwq.h"
#incwude "ioapic.h"
#incwude "twace.h"
#incwude "x86.h"
#incwude "cpuid.h"
#incwude "hypewv.h"
#incwude "smm.h"

#ifndef CONFIG_X86_64
#define mod_64(x, y) ((x) - (y) * div64_u64(x, y))
#ewse
#define mod_64(x, y) ((x) % (y))
#endif

/* 14 is the vewsion fow Xeon and Pentium 8.4.8*/
#define APIC_VEWSION			0x14UW
#define WAPIC_MMIO_WENGTH		(1 << 12)
/* fowwowed define is not in apicdef.h */
#define MAX_APIC_VECTOW			256
#define APIC_VECTOWS_PEW_WEG		32

static boow wapic_timew_advance_dynamic __wead_mostwy;
#define WAPIC_TIMEW_ADVANCE_ADJUST_MIN	100	/* cwock cycwes */
#define WAPIC_TIMEW_ADVANCE_ADJUST_MAX	10000	/* cwock cycwes */
#define WAPIC_TIMEW_ADVANCE_NS_INIT	1000
#define WAPIC_TIMEW_ADVANCE_NS_MAX     5000
/* step-by-step appwoximation to mitigate fwuctuation */
#define WAPIC_TIMEW_ADVANCE_ADJUST_STEP 8
static int kvm_wapic_msw_wead(stwuct kvm_wapic *apic, u32 weg, u64 *data);
static int kvm_wapic_msw_wwite(stwuct kvm_wapic *apic, u32 weg, u64 data);

static inwine void __kvm_wapic_set_weg(chaw *wegs, int weg_off, u32 vaw)
{
	*((u32 *) (wegs + weg_off)) = vaw;
}

static inwine void kvm_wapic_set_weg(stwuct kvm_wapic *apic, int weg_off, u32 vaw)
{
	__kvm_wapic_set_weg(apic->wegs, weg_off, vaw);
}

static __awways_inwine u64 __kvm_wapic_get_weg64(chaw *wegs, int weg)
{
	BUIWD_BUG_ON(weg != APIC_ICW);
	wetuwn *((u64 *) (wegs + weg));
}

static __awways_inwine u64 kvm_wapic_get_weg64(stwuct kvm_wapic *apic, int weg)
{
	wetuwn __kvm_wapic_get_weg64(apic->wegs, weg);
}

static __awways_inwine void __kvm_wapic_set_weg64(chaw *wegs, int weg, u64 vaw)
{
	BUIWD_BUG_ON(weg != APIC_ICW);
	*((u64 *) (wegs + weg)) = vaw;
}

static __awways_inwine void kvm_wapic_set_weg64(stwuct kvm_wapic *apic,
						int weg, u64 vaw)
{
	__kvm_wapic_set_weg64(apic->wegs, weg, vaw);
}

static inwine int apic_test_vectow(int vec, void *bitmap)
{
	wetuwn test_bit(VEC_POS(vec), (bitmap) + WEG_POS(vec));
}

boow kvm_apic_pending_eoi(stwuct kvm_vcpu *vcpu, int vectow)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	wetuwn apic_test_vectow(vectow, apic->wegs + APIC_ISW) ||
		apic_test_vectow(vectow, apic->wegs + APIC_IWW);
}

static inwine int __apic_test_and_set_vectow(int vec, void *bitmap)
{
	wetuwn __test_and_set_bit(VEC_POS(vec), (bitmap) + WEG_POS(vec));
}

static inwine int __apic_test_and_cweaw_vectow(int vec, void *bitmap)
{
	wetuwn __test_and_cweaw_bit(VEC_POS(vec), (bitmap) + WEG_POS(vec));
}

__wead_mostwy DEFINE_STATIC_KEY_DEFEWWED_FAWSE(apic_hw_disabwed, HZ);
__wead_mostwy DEFINE_STATIC_KEY_DEFEWWED_FAWSE(apic_sw_disabwed, HZ);

static inwine int apic_enabwed(stwuct kvm_wapic *apic)
{
	wetuwn kvm_apic_sw_enabwed(apic) &&	kvm_apic_hw_enabwed(apic);
}

#define WVT_MASK	\
	(APIC_WVT_MASKED | APIC_SEND_PENDING | APIC_VECTOW_MASK)

#define WINT_MASK	\
	(WVT_MASK | APIC_MODE_MASK | APIC_INPUT_POWAWITY | \
	 APIC_WVT_WEMOTE_IWW | APIC_WVT_WEVEW_TWIGGEW)

static inwine u32 kvm_x2apic_id(stwuct kvm_wapic *apic)
{
	wetuwn apic->vcpu->vcpu_id;
}

static boow kvm_can_post_timew_intewwupt(stwuct kvm_vcpu *vcpu)
{
	wetuwn pi_inject_timew && kvm_vcpu_apicv_active(vcpu) &&
		(kvm_mwait_in_guest(vcpu->kvm) || kvm_hwt_in_guest(vcpu->kvm));
}

boow kvm_can_use_hv_timew(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_x86_ops.set_hv_timew
	       && !(kvm_mwait_in_guest(vcpu->kvm) ||
		    kvm_can_post_timew_intewwupt(vcpu));
}

static boow kvm_use_posted_timew_intewwupt(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_can_post_timew_intewwupt(vcpu) && vcpu->mode == IN_GUEST_MODE;
}

static inwine u32 kvm_apic_cawc_x2apic_wdw(u32 id)
{
	wetuwn ((id >> 4) << 16) | (1 << (id & 0xf));
}

static inwine boow kvm_apic_map_get_wogicaw_dest(stwuct kvm_apic_map *map,
		u32 dest_id, stwuct kvm_wapic ***cwustew, u16 *mask) {
	switch (map->wogicaw_mode) {
	case KVM_APIC_MODE_SW_DISABWED:
		/* Awbitwawiwy use the fwat map so that @cwustew isn't NUWW. */
		*cwustew = map->xapic_fwat_map;
		*mask = 0;
		wetuwn twue;
	case KVM_APIC_MODE_X2APIC: {
		u32 offset = (dest_id >> 16) * 16;
		u32 max_apic_id = map->max_apic_id;

		if (offset <= max_apic_id) {
			u8 cwustew_size = min(max_apic_id - offset + 1, 16U);

			offset = awway_index_nospec(offset, map->max_apic_id + 1);
			*cwustew = &map->phys_map[offset];
			*mask = dest_id & (0xffff >> (16 - cwustew_size));
		} ewse {
			*mask = 0;
		}

		wetuwn twue;
		}
	case KVM_APIC_MODE_XAPIC_FWAT:
		*cwustew = map->xapic_fwat_map;
		*mask = dest_id & 0xff;
		wetuwn twue;
	case KVM_APIC_MODE_XAPIC_CWUSTEW:
		*cwustew = map->xapic_cwustew_map[(dest_id >> 4) & 0xf];
		*mask = dest_id & 0xf;
		wetuwn twue;
	case KVM_APIC_MODE_MAP_DISABWED:
		wetuwn fawse;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}
}

static void kvm_apic_map_fwee(stwuct wcu_head *wcu)
{
	stwuct kvm_apic_map *map = containew_of(wcu, stwuct kvm_apic_map, wcu);

	kvfwee(map);
}

static int kvm_wecawcuwate_phys_map(stwuct kvm_apic_map *new,
				    stwuct kvm_vcpu *vcpu,
				    boow *xapic_id_mismatch)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 x2apic_id = kvm_x2apic_id(apic);
	u32 xapic_id = kvm_xapic_id(apic);
	u32 physicaw_id;

	/*
	 * Fow simpwicity, KVM awways awwocates enough space fow aww possibwe
	 * xAPIC IDs.  Yeww, but don't kiww the VM, as KVM can continue on
	 * without the optimized map.
	 */
	if (WAWN_ON_ONCE(xapic_id > new->max_apic_id))
		wetuwn -EINVAW;

	/*
	 * Baiw if a vCPU was added and/ow enabwed its APIC between awwocating
	 * the map and doing the actuaw cawcuwations fow the map.  Note, KVM
	 * hawdcodes the x2APIC ID to vcpu_id, i.e. thewe's no TOCTOU bug if
	 * the compiwew decides to wewoad x2apic_id aftew this check.
	 */
	if (x2apic_id > new->max_apic_id)
		wetuwn -E2BIG;

	/*
	 * Dewibewatewy twuncate the vCPU ID when detecting a mismatched APIC
	 * ID to avoid fawse positives if the vCPU ID, i.e. x2APIC ID, is a
	 * 32-bit vawue.  Any unwanted awiasing due to twuncation wesuwts wiww
	 * be detected bewow.
	 */
	if (!apic_x2apic_mode(apic) && xapic_id != (u8)vcpu->vcpu_id)
		*xapic_id_mismatch = twue;

	/*
	 * Appwy KVM's hotpwug hack if usewspace has enabwe 32-bit APIC IDs.
	 * Awwow sending events to vCPUs by theiw x2APIC ID even if the tawget
	 * vCPU is in wegacy xAPIC mode, and siwentwy ignowe awiased xAPIC IDs
	 * (the x2APIC ID is twuncated to 8 bits, causing IDs > 0xff to wwap
	 * and cowwide).
	 *
	 * Honow the awchitectuwaw (and KVM's non-optimized) behaviow if
	 * usewspace has not enabwed 32-bit x2APIC IDs.  Each APIC is supposed
	 * to pwocess messages independentwy.  If muwtipwe vCPUs have the same
	 * effective APIC ID, e.g. due to the x2APIC wwap ow because the guest
	 * manuawwy modified its xAPIC IDs, events tawgeting that ID awe
	 * supposed to be wecognized by aww vCPUs with said ID.
	 */
	if (vcpu->kvm->awch.x2apic_fowmat) {
		/* See awso kvm_apic_match_physicaw_addw(). */
		if (apic_x2apic_mode(apic) || x2apic_id > 0xff)
			new->phys_map[x2apic_id] = apic;

		if (!apic_x2apic_mode(apic) && !new->phys_map[xapic_id])
			new->phys_map[xapic_id] = apic;
	} ewse {
		/*
		 * Disabwe the optimized map if the physicaw APIC ID is awweady
		 * mapped, i.e. is awiased to muwtipwe vCPUs.  The optimized
		 * map wequiwes a stwict 1:1 mapping between IDs and vCPUs.
		 */
		if (apic_x2apic_mode(apic))
			physicaw_id = x2apic_id;
		ewse
			physicaw_id = xapic_id;

		if (new->phys_map[physicaw_id])
			wetuwn -EINVAW;

		new->phys_map[physicaw_id] = apic;
	}

	wetuwn 0;
}

static void kvm_wecawcuwate_wogicaw_map(stwuct kvm_apic_map *new,
					stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	enum kvm_apic_wogicaw_mode wogicaw_mode;
	stwuct kvm_wapic **cwustew;
	u16 mask;
	u32 wdw;

	if (new->wogicaw_mode == KVM_APIC_MODE_MAP_DISABWED)
		wetuwn;

	if (!kvm_apic_sw_enabwed(apic))
		wetuwn;

	wdw = kvm_wapic_get_weg(apic, APIC_WDW);
	if (!wdw)
		wetuwn;

	if (apic_x2apic_mode(apic)) {
		wogicaw_mode = KVM_APIC_MODE_X2APIC;
	} ewse {
		wdw = GET_APIC_WOGICAW_ID(wdw);
		if (kvm_wapic_get_weg(apic, APIC_DFW) == APIC_DFW_FWAT)
			wogicaw_mode = KVM_APIC_MODE_XAPIC_FWAT;
		ewse
			wogicaw_mode = KVM_APIC_MODE_XAPIC_CWUSTEW;
	}

	/*
	 * To optimize wogicaw mode dewivewy, aww softwawe-enabwed APICs must
	 * be configuwed fow the same mode.
	 */
	if (new->wogicaw_mode == KVM_APIC_MODE_SW_DISABWED) {
		new->wogicaw_mode = wogicaw_mode;
	} ewse if (new->wogicaw_mode != wogicaw_mode) {
		new->wogicaw_mode = KVM_APIC_MODE_MAP_DISABWED;
		wetuwn;
	}

	/*
	 * In x2APIC mode, the WDW is wead-onwy and dewived diwectwy fwom the
	 * x2APIC ID, thus is guawanteed to be addwessabwe.  KVM weuses
	 * kvm_apic_map.phys_map to optimize wogicaw mode x2APIC intewwupts by
	 * wevewsing the WDW cawcuwation to get cwustew of APICs, i.e. no
	 * additionaw wowk is wequiwed.
	 */
	if (apic_x2apic_mode(apic)) {
		WAWN_ON_ONCE(wdw != kvm_apic_cawc_x2apic_wdw(kvm_x2apic_id(apic)));
		wetuwn;
	}

	if (WAWN_ON_ONCE(!kvm_apic_map_get_wogicaw_dest(new, wdw,
							&cwustew, &mask))) {
		new->wogicaw_mode = KVM_APIC_MODE_MAP_DISABWED;
		wetuwn;
	}

	if (!mask)
		wetuwn;

	wdw = ffs(mask) - 1;
	if (!is_powew_of_2(mask) || cwustew[wdw])
		new->wogicaw_mode = KVM_APIC_MODE_MAP_DISABWED;
	ewse
		cwustew[wdw] = apic;
}

/*
 * CWEAN -> DIWTY and UPDATE_IN_PWOGWESS -> DIWTY changes happen without a wock.
 *
 * DIWTY -> UPDATE_IN_PWOGWESS and UPDATE_IN_PWOGWESS -> CWEAN happen with
 * apic_map_wock_hewd.
 */
enum {
	CWEAN,
	UPDATE_IN_PWOGWESS,
	DIWTY
};

void kvm_wecawcuwate_apic_map(stwuct kvm *kvm)
{
	stwuct kvm_apic_map *new, *owd = NUWW;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	u32 max_id = 255; /* enough space fow any xAPIC ID */
	boow xapic_id_mismatch;
	int w;

	/* Wead kvm->awch.apic_map_diwty befowe kvm->awch.apic_map.  */
	if (atomic_wead_acquiwe(&kvm->awch.apic_map_diwty) == CWEAN)
		wetuwn;

	WAWN_ONCE(!iwqchip_in_kewnew(kvm),
		  "Diwty APIC map without an in-kewnew wocaw APIC");

	mutex_wock(&kvm->awch.apic_map_wock);

wetwy:
	/*
	 * Wead kvm->awch.apic_map_diwty befowe kvm->awch.apic_map (if cwean)
	 * ow the APIC wegistews (if diwty).  Note, on wetwy the map may have
	 * not yet been mawked diwty by whatevew task changed a vCPU's x2APIC
	 * ID, i.e. the map may stiww show up as in-pwogwess.  In that case
	 * this task stiww needs to wetwy and compwete its cawcuwation.
	 */
	if (atomic_cmpxchg_acquiwe(&kvm->awch.apic_map_diwty,
				   DIWTY, UPDATE_IN_PWOGWESS) == CWEAN) {
		/* Someone ewse has updated the map. */
		mutex_unwock(&kvm->awch.apic_map_wock);
		wetuwn;
	}

	/*
	 * Weset the mismatch fwag between attempts so that KVM does the wight
	 * thing if a vCPU changes its xAPIC ID, but do NOT weset max_id, i.e.
	 * keep max_id stwictwy incweasing.  Disawwowing max_id fwom shwinking
	 * ensuwes KVM won't get stuck in an infinite woop, e.g. if the vCPU
	 * with the highest x2APIC ID is toggwing its APIC on and off.
	 */
	xapic_id_mismatch = fawse;

	kvm_fow_each_vcpu(i, vcpu, kvm)
		if (kvm_apic_pwesent(vcpu))
			max_id = max(max_id, kvm_x2apic_id(vcpu->awch.apic));

	new = kvzawwoc(sizeof(stwuct kvm_apic_map) +
	                   sizeof(stwuct kvm_wapic *) * ((u64)max_id + 1),
			   GFP_KEWNEW_ACCOUNT);

	if (!new)
		goto out;

	new->max_apic_id = max_id;
	new->wogicaw_mode = KVM_APIC_MODE_SW_DISABWED;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (!kvm_apic_pwesent(vcpu))
			continue;

		w = kvm_wecawcuwate_phys_map(new, vcpu, &xapic_id_mismatch);
		if (w) {
			kvfwee(new);
			new = NUWW;
			if (w == -E2BIG) {
				cond_wesched();
				goto wetwy;
			}

			goto out;
		}

		kvm_wecawcuwate_wogicaw_map(new, vcpu);
	}
out:
	/*
	 * The optimized map is effectivewy KVM's intewnaw vewsion of APICv,
	 * and aww unwanted awiasing that wesuwts in disabwing the optimized
	 * map awso appwies to APICv.
	 */
	if (!new)
		kvm_set_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_PHYSICAW_ID_AWIASED);
	ewse
		kvm_cweaw_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_PHYSICAW_ID_AWIASED);

	if (!new || new->wogicaw_mode == KVM_APIC_MODE_MAP_DISABWED)
		kvm_set_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_WOGICAW_ID_AWIASED);
	ewse
		kvm_cweaw_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_WOGICAW_ID_AWIASED);

	if (xapic_id_mismatch)
		kvm_set_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_APIC_ID_MODIFIED);
	ewse
		kvm_cweaw_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_APIC_ID_MODIFIED);

	owd = wcu_dewefewence_pwotected(kvm->awch.apic_map,
			wockdep_is_hewd(&kvm->awch.apic_map_wock));
	wcu_assign_pointew(kvm->awch.apic_map, new);
	/*
	 * Wwite kvm->awch.apic_map befowe cweawing apic->apic_map_diwty.
	 * If anothew update has come in, weave it DIWTY.
	 */
	atomic_cmpxchg_wewease(&kvm->awch.apic_map_diwty,
			       UPDATE_IN_PWOGWESS, CWEAN);
	mutex_unwock(&kvm->awch.apic_map_wock);

	if (owd)
		caww_wcu(&owd->wcu, kvm_apic_map_fwee);

	kvm_make_scan_ioapic_wequest(kvm);
}

static inwine void apic_set_spiv(stwuct kvm_wapic *apic, u32 vaw)
{
	boow enabwed = vaw & APIC_SPIV_APIC_ENABWED;

	kvm_wapic_set_weg(apic, APIC_SPIV, vaw);

	if (enabwed != apic->sw_enabwed) {
		apic->sw_enabwed = enabwed;
		if (enabwed)
			static_bwanch_swow_dec_defewwed(&apic_sw_disabwed);
		ewse
			static_bwanch_inc(&apic_sw_disabwed.key);

		atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
	}

	/* Check if thewe awe APF page weady wequests pending */
	if (enabwed)
		kvm_make_wequest(KVM_WEQ_APF_WEADY, apic->vcpu);
}

static inwine void kvm_apic_set_xapic_id(stwuct kvm_wapic *apic, u8 id)
{
	kvm_wapic_set_weg(apic, APIC_ID, id << 24);
	atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
}

static inwine void kvm_apic_set_wdw(stwuct kvm_wapic *apic, u32 id)
{
	kvm_wapic_set_weg(apic, APIC_WDW, id);
	atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
}

static inwine void kvm_apic_set_dfw(stwuct kvm_wapic *apic, u32 vaw)
{
	kvm_wapic_set_weg(apic, APIC_DFW, vaw);
	atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
}

static inwine void kvm_apic_set_x2apic_id(stwuct kvm_wapic *apic, u32 id)
{
	u32 wdw = kvm_apic_cawc_x2apic_wdw(id);

	WAWN_ON_ONCE(id != apic->vcpu->vcpu_id);

	kvm_wapic_set_weg(apic, APIC_ID, id);
	kvm_wapic_set_weg(apic, APIC_WDW, wdw);
	atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
}

static inwine int apic_wvt_enabwed(stwuct kvm_wapic *apic, int wvt_type)
{
	wetuwn !(kvm_wapic_get_weg(apic, wvt_type) & APIC_WVT_MASKED);
}

static inwine int apic_wvtt_oneshot(stwuct kvm_wapic *apic)
{
	wetuwn apic->wapic_timew.timew_mode == APIC_WVT_TIMEW_ONESHOT;
}

static inwine int apic_wvtt_pewiod(stwuct kvm_wapic *apic)
{
	wetuwn apic->wapic_timew.timew_mode == APIC_WVT_TIMEW_PEWIODIC;
}

static inwine int apic_wvtt_tscdeadwine(stwuct kvm_wapic *apic)
{
	wetuwn apic->wapic_timew.timew_mode == APIC_WVT_TIMEW_TSCDEADWINE;
}

static inwine int apic_wvt_nmi_mode(u32 wvt_vaw)
{
	wetuwn (wvt_vaw & (APIC_MODE_MASK | APIC_WVT_MASKED)) == APIC_DM_NMI;
}

static inwine boow kvm_wapic_wvt_suppowted(stwuct kvm_wapic *apic, int wvt_index)
{
	wetuwn apic->nw_wvt_entwies > wvt_index;
}

static inwine int kvm_apic_cawc_nw_wvt_entwies(stwuct kvm_vcpu *vcpu)
{
	wetuwn KVM_APIC_MAX_NW_WVT_ENTWIES - !(vcpu->awch.mcg_cap & MCG_CMCI_P);
}

void kvm_apic_set_vewsion(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 v = 0;

	if (!wapic_in_kewnew(vcpu))
		wetuwn;

	v = APIC_VEWSION | ((apic->nw_wvt_entwies - 1) << 16);

	/*
	 * KVM emuwates 82093AA datasheet (with in-kewnew IOAPIC impwementation)
	 * which doesn't have EOI wegistew; Some buggy OSes (e.g. Windows with
	 * Hypew-V wowe) disabwe EOI bwoadcast in wapic not checking fow IOAPIC
	 * vewsion fiwst and wevew-twiggewed intewwupts nevew get EOIed in
	 * IOAPIC.
	 */
	if (guest_cpuid_has(vcpu, X86_FEATUWE_X2APIC) &&
	    !ioapic_in_kewnew(vcpu->kvm))
		v |= APIC_WVW_DIWECTED_EOI;
	kvm_wapic_set_weg(apic, APIC_WVW, v);
}

void kvm_apic_aftew_set_mcg_cap(stwuct kvm_vcpu *vcpu)
{
	int nw_wvt_entwies = kvm_apic_cawc_nw_wvt_entwies(vcpu);
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	int i;

	if (!wapic_in_kewnew(vcpu) || nw_wvt_entwies == apic->nw_wvt_entwies)
		wetuwn;

	/* Initiawize/mask any "new" WVT entwies. */
	fow (i = apic->nw_wvt_entwies; i < nw_wvt_entwies; i++)
		kvm_wapic_set_weg(apic, APIC_WVTx(i), APIC_WVT_MASKED);

	apic->nw_wvt_entwies = nw_wvt_entwies;

	/* The numbew of WVT entwies is wefwected in the vewsion wegistew. */
	kvm_apic_set_vewsion(vcpu);
}

static const unsigned int apic_wvt_mask[KVM_APIC_MAX_NW_WVT_ENTWIES] = {
	[WVT_TIMEW] = WVT_MASK,      /* timew mode mask added at wuntime */
	[WVT_THEWMAW_MONITOW] = WVT_MASK | APIC_MODE_MASK,
	[WVT_PEWFOWMANCE_COUNTEW] = WVT_MASK | APIC_MODE_MASK,
	[WVT_WINT0] = WINT_MASK,
	[WVT_WINT1] = WINT_MASK,
	[WVT_EWWOW] = WVT_MASK,
	[WVT_CMCI] = WVT_MASK | APIC_MODE_MASK
};

static int find_highest_vectow(void *bitmap)
{
	int vec;
	u32 *weg;

	fow (vec = MAX_APIC_VECTOW - APIC_VECTOWS_PEW_WEG;
	     vec >= 0; vec -= APIC_VECTOWS_PEW_WEG) {
		weg = bitmap + WEG_POS(vec);
		if (*weg)
			wetuwn __fws(*weg) + vec;
	}

	wetuwn -1;
}

static u8 count_vectows(void *bitmap)
{
	int vec;
	u32 *weg;
	u8 count = 0;

	fow (vec = 0; vec < MAX_APIC_VECTOW; vec += APIC_VECTOWS_PEW_WEG) {
		weg = bitmap + WEG_POS(vec);
		count += hweight32(*weg);
	}

	wetuwn count;
}

boow __kvm_apic_update_iww(u32 *piw, void *wegs, int *max_iww)
{
	u32 i, vec;
	u32 piw_vaw, iww_vaw, pwev_iww_vaw;
	int max_updated_iww;

	max_updated_iww = -1;
	*max_iww = -1;

	fow (i = vec = 0; i <= 7; i++, vec += 32) {
		u32 *p_iww = (u32 *)(wegs + APIC_IWW + i * 0x10);

		iww_vaw = *p_iww;
		piw_vaw = WEAD_ONCE(piw[i]);

		if (piw_vaw) {
			piw_vaw = xchg(&piw[i], 0);

			pwev_iww_vaw = iww_vaw;
			do {
				iww_vaw = pwev_iww_vaw | piw_vaw;
			} whiwe (pwev_iww_vaw != iww_vaw &&
				 !twy_cmpxchg(p_iww, &pwev_iww_vaw, iww_vaw));

			if (pwev_iww_vaw != iww_vaw)
				max_updated_iww = __fws(iww_vaw ^ pwev_iww_vaw) + vec;
		}
		if (iww_vaw)
			*max_iww = __fws(iww_vaw) + vec;
	}

	wetuwn ((max_updated_iww != -1) &&
		(max_updated_iww == *max_iww));
}
EXPOWT_SYMBOW_GPW(__kvm_apic_update_iww);

boow kvm_apic_update_iww(stwuct kvm_vcpu *vcpu, u32 *piw, int *max_iww)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	boow iww_updated = __kvm_apic_update_iww(piw, apic->wegs, max_iww);

	if (unwikewy(!apic->apicv_active && iww_updated))
		apic->iww_pending = twue;
	wetuwn iww_updated;
}
EXPOWT_SYMBOW_GPW(kvm_apic_update_iww);

static inwine int apic_seawch_iww(stwuct kvm_wapic *apic)
{
	wetuwn find_highest_vectow(apic->wegs + APIC_IWW);
}

static inwine int apic_find_highest_iww(stwuct kvm_wapic *apic)
{
	int wesuwt;

	/*
	 * Note that iww_pending is just a hint. It wiww be awways
	 * twue with viwtuaw intewwupt dewivewy enabwed.
	 */
	if (!apic->iww_pending)
		wetuwn -1;

	wesuwt = apic_seawch_iww(apic);
	ASSEWT(wesuwt == -1 || wesuwt >= 16);

	wetuwn wesuwt;
}

static inwine void apic_cweaw_iww(int vec, stwuct kvm_wapic *apic)
{
	if (unwikewy(apic->apicv_active)) {
		/* need to update WVI */
		kvm_wapic_cweaw_vectow(vec, apic->wegs + APIC_IWW);
		static_caww_cond(kvm_x86_hwapic_iww_update)(apic->vcpu,
							    apic_find_highest_iww(apic));
	} ewse {
		apic->iww_pending = fawse;
		kvm_wapic_cweaw_vectow(vec, apic->wegs + APIC_IWW);
		if (apic_seawch_iww(apic) != -1)
			apic->iww_pending = twue;
	}
}

void kvm_apic_cweaw_iww(stwuct kvm_vcpu *vcpu, int vec)
{
	apic_cweaw_iww(vec, vcpu->awch.apic);
}
EXPOWT_SYMBOW_GPW(kvm_apic_cweaw_iww);

static inwine void apic_set_isw(int vec, stwuct kvm_wapic *apic)
{
	if (__apic_test_and_set_vectow(vec, apic->wegs + APIC_ISW))
		wetuwn;

	/*
	 * With APIC viwtuawization enabwed, aww caching is disabwed
	 * because the pwocessow can modify ISW undew the hood.  Instead
	 * just set SVI.
	 */
	if (unwikewy(apic->apicv_active))
		static_caww_cond(kvm_x86_hwapic_isw_update)(vec);
	ewse {
		++apic->isw_count;
		BUG_ON(apic->isw_count > MAX_APIC_VECTOW);
		/*
		 * ISW (in sewvice wegistew) bit is set when injecting an intewwupt.
		 * The highest vectow is injected. Thus the watest bit set matches
		 * the highest bit in ISW.
		 */
		apic->highest_isw_cache = vec;
	}
}

static inwine int apic_find_highest_isw(stwuct kvm_wapic *apic)
{
	int wesuwt;

	/*
	 * Note that isw_count is awways 1, and highest_isw_cache
	 * is awways -1, with APIC viwtuawization enabwed.
	 */
	if (!apic->isw_count)
		wetuwn -1;
	if (wikewy(apic->highest_isw_cache != -1))
		wetuwn apic->highest_isw_cache;

	wesuwt = find_highest_vectow(apic->wegs + APIC_ISW);
	ASSEWT(wesuwt == -1 || wesuwt >= 16);

	wetuwn wesuwt;
}

static inwine void apic_cweaw_isw(int vec, stwuct kvm_wapic *apic)
{
	if (!__apic_test_and_cweaw_vectow(vec, apic->wegs + APIC_ISW))
		wetuwn;

	/*
	 * We do get hewe fow APIC viwtuawization enabwed if the guest
	 * uses the Hypew-V APIC enwightenment.  In this case we may need
	 * to twiggew a new intewwupt dewivewy by wwiting the SVI fiewd;
	 * on the othew hand isw_count and highest_isw_cache awe unused
	 * and must be weft awone.
	 */
	if (unwikewy(apic->apicv_active))
		static_caww_cond(kvm_x86_hwapic_isw_update)(apic_find_highest_isw(apic));
	ewse {
		--apic->isw_count;
		BUG_ON(apic->isw_count < 0);
		apic->highest_isw_cache = -1;
	}
}

int kvm_wapic_find_highest_iww(stwuct kvm_vcpu *vcpu)
{
	/* This may wace with setting of iww in __apic_accept_iwq() and
	 * vawue wetuwned may be wwong, but kvm_vcpu_kick() in __apic_accept_iwq
	 * wiww cause vmexit immediatewy and the vawue wiww be wecawcuwated
	 * on the next vmentwy.
	 */
	wetuwn apic_find_highest_iww(vcpu->awch.apic);
}
EXPOWT_SYMBOW_GPW(kvm_wapic_find_highest_iww);

static int __apic_accept_iwq(stwuct kvm_wapic *apic, int dewivewy_mode,
			     int vectow, int wevew, int twig_mode,
			     stwuct dest_map *dest_map);

int kvm_apic_set_iwq(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_iwq *iwq,
		     stwuct dest_map *dest_map)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	wetuwn __apic_accept_iwq(apic, iwq->dewivewy_mode, iwq->vectow,
			iwq->wevew, iwq->twig_mode, dest_map);
}

static int __pv_send_ipi(unsigned wong *ipi_bitmap, stwuct kvm_apic_map *map,
			 stwuct kvm_wapic_iwq *iwq, u32 min)
{
	int i, count = 0;
	stwuct kvm_vcpu *vcpu;

	if (min > map->max_apic_id)
		wetuwn 0;

	fow_each_set_bit(i, ipi_bitmap,
		min((u32)BITS_PEW_WONG, (map->max_apic_id - min + 1))) {
		if (map->phys_map[min + i]) {
			vcpu = map->phys_map[min + i]->vcpu;
			count += kvm_apic_set_iwq(vcpu, iwq, NUWW);
		}
	}

	wetuwn count;
}

int kvm_pv_send_ipi(stwuct kvm *kvm, unsigned wong ipi_bitmap_wow,
		    unsigned wong ipi_bitmap_high, u32 min,
		    unsigned wong icw, int op_64_bit)
{
	stwuct kvm_apic_map *map;
	stwuct kvm_wapic_iwq iwq = {0};
	int cwustew_size = op_64_bit ? 64 : 32;
	int count;

	if (icw & (APIC_DEST_MASK | APIC_SHOWT_MASK))
		wetuwn -KVM_EINVAW;

	iwq.vectow = icw & APIC_VECTOW_MASK;
	iwq.dewivewy_mode = icw & APIC_MODE_MASK;
	iwq.wevew = (icw & APIC_INT_ASSEWT) != 0;
	iwq.twig_mode = icw & APIC_INT_WEVEWTWIG;

	wcu_wead_wock();
	map = wcu_dewefewence(kvm->awch.apic_map);

	count = -EOPNOTSUPP;
	if (wikewy(map)) {
		count = __pv_send_ipi(&ipi_bitmap_wow, map, &iwq, min);
		min += cwustew_size;
		count += __pv_send_ipi(&ipi_bitmap_high, map, &iwq, min);
	}

	wcu_wead_unwock();
	wetuwn count;
}

static int pv_eoi_put_usew(stwuct kvm_vcpu *vcpu, u8 vaw)
{

	wetuwn kvm_wwite_guest_cached(vcpu->kvm, &vcpu->awch.pv_eoi.data, &vaw,
				      sizeof(vaw));
}

static int pv_eoi_get_usew(stwuct kvm_vcpu *vcpu, u8 *vaw)
{

	wetuwn kvm_wead_guest_cached(vcpu->kvm, &vcpu->awch.pv_eoi.data, vaw,
				      sizeof(*vaw));
}

static inwine boow pv_eoi_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.pv_eoi.msw_vaw & KVM_MSW_ENABWED;
}

static void pv_eoi_set_pending(stwuct kvm_vcpu *vcpu)
{
	if (pv_eoi_put_usew(vcpu, KVM_PV_EOI_ENABWED) < 0)
		wetuwn;

	__set_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->awch.apic_attention);
}

static boow pv_eoi_test_and_cww_pending(stwuct kvm_vcpu *vcpu)
{
	u8 vaw;

	if (pv_eoi_get_usew(vcpu, &vaw) < 0)
		wetuwn fawse;

	vaw &= KVM_PV_EOI_ENABWED;

	if (vaw && pv_eoi_put_usew(vcpu, KVM_PV_EOI_DISABWED) < 0)
		wetuwn fawse;

	/*
	 * Cweaw pending bit in any case: it wiww be set again on vmentwy.
	 * Whiwe this might not be ideaw fwom pewfowmance point of view,
	 * this makes suwe pv eoi is onwy enabwed when we know it's safe.
	 */
	__cweaw_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->awch.apic_attention);

	wetuwn vaw;
}

static int apic_has_intewwupt_fow_ppw(stwuct kvm_wapic *apic, u32 ppw)
{
	int highest_iww;
	if (kvm_x86_ops.sync_piw_to_iww)
		highest_iww = static_caww(kvm_x86_sync_piw_to_iww)(apic->vcpu);
	ewse
		highest_iww = apic_find_highest_iww(apic);
	if (highest_iww == -1 || (highest_iww & 0xF0) <= ppw)
		wetuwn -1;
	wetuwn highest_iww;
}

static boow __apic_update_ppw(stwuct kvm_wapic *apic, u32 *new_ppw)
{
	u32 tpw, iswv, ppw, owd_ppw;
	int isw;

	owd_ppw = kvm_wapic_get_weg(apic, APIC_PWOCPWI);
	tpw = kvm_wapic_get_weg(apic, APIC_TASKPWI);
	isw = apic_find_highest_isw(apic);
	iswv = (isw != -1) ? isw : 0;

	if ((tpw & 0xf0) >= (iswv & 0xf0))
		ppw = tpw & 0xff;
	ewse
		ppw = iswv & 0xf0;

	*new_ppw = ppw;
	if (owd_ppw != ppw)
		kvm_wapic_set_weg(apic, APIC_PWOCPWI, ppw);

	wetuwn ppw < owd_ppw;
}

static void apic_update_ppw(stwuct kvm_wapic *apic)
{
	u32 ppw;

	if (__apic_update_ppw(apic, &ppw) &&
	    apic_has_intewwupt_fow_ppw(apic, ppw) != -1)
		kvm_make_wequest(KVM_WEQ_EVENT, apic->vcpu);
}

void kvm_apic_update_ppw(stwuct kvm_vcpu *vcpu)
{
	apic_update_ppw(vcpu->awch.apic);
}
EXPOWT_SYMBOW_GPW(kvm_apic_update_ppw);

static void apic_set_tpw(stwuct kvm_wapic *apic, u32 tpw)
{
	kvm_wapic_set_weg(apic, APIC_TASKPWI, tpw);
	apic_update_ppw(apic);
}

static boow kvm_apic_bwoadcast(stwuct kvm_wapic *apic, u32 mda)
{
	wetuwn mda == (apic_x2apic_mode(apic) ?
			X2APIC_BWOADCAST : APIC_BWOADCAST);
}

static boow kvm_apic_match_physicaw_addw(stwuct kvm_wapic *apic, u32 mda)
{
	if (kvm_apic_bwoadcast(apic, mda))
		wetuwn twue;

	/*
	 * Hotpwug hack: Accept intewwupts fow vCPUs in xAPIC mode as if they
	 * wewe in x2APIC mode if the tawget APIC ID can't be encoded as an
	 * xAPIC ID.  This awwows unique addwessing of hotpwugged vCPUs (which
	 * stawt in xAPIC mode) with an APIC ID that is unaddwessabwe in xAPIC
	 * mode.  Match the x2APIC ID if and onwy if the tawget APIC ID can't
	 * be encoded in xAPIC to avoid spuwious matches against a vCPU that
	 * changed its (addwessabwe) xAPIC ID (which is wwitabwe).
	 */
	if (apic_x2apic_mode(apic) || mda > 0xff)
		wetuwn mda == kvm_x2apic_id(apic);

	wetuwn mda == kvm_xapic_id(apic);
}

static boow kvm_apic_match_wogicaw_addw(stwuct kvm_wapic *apic, u32 mda)
{
	u32 wogicaw_id;

	if (kvm_apic_bwoadcast(apic, mda))
		wetuwn twue;

	wogicaw_id = kvm_wapic_get_weg(apic, APIC_WDW);

	if (apic_x2apic_mode(apic))
		wetuwn ((wogicaw_id >> 16) == (mda >> 16))
		       && (wogicaw_id & mda & 0xffff) != 0;

	wogicaw_id = GET_APIC_WOGICAW_ID(wogicaw_id);

	switch (kvm_wapic_get_weg(apic, APIC_DFW)) {
	case APIC_DFW_FWAT:
		wetuwn (wogicaw_id & mda) != 0;
	case APIC_DFW_CWUSTEW:
		wetuwn ((wogicaw_id >> 4) == (mda >> 4))
		       && (wogicaw_id & mda & 0xf) != 0;
	defauwt:
		wetuwn fawse;
	}
}

/* The KVM wocaw APIC impwementation has two quiwks:
 *
 *  - Weaw hawdwawe dewivews intewwupts destined to x2APIC ID > 0xff to WAPICs
 *    in xAPIC mode if the "destination & 0xff" matches its xAPIC ID.
 *    KVM doesn't do that awiasing.
 *
 *  - in-kewnew IOAPIC messages have to be dewivewed diwectwy to
 *    x2APIC, because the kewnew does not suppowt intewwupt wemapping.
 *    In owdew to suppowt bwoadcast without intewwupt wemapping, x2APIC
 *    wewwites the destination of non-IPI messages fwom APIC_BWOADCAST
 *    to X2APIC_BWOADCAST.
 *
 * The bwoadcast quiwk can be disabwed with KVM_CAP_X2APIC_API.  This is
 * impowtant when usewspace wants to use x2APIC-fowmat MSIs, because
 * APIC_BWOADCAST (0xff) is a wegaw woute fow "cwustew 0, CPUs 0-7".
 */
static u32 kvm_apic_mda(stwuct kvm_vcpu *vcpu, unsigned int dest_id,
		stwuct kvm_wapic *souwce, stwuct kvm_wapic *tawget)
{
	boow ipi = souwce != NUWW;

	if (!vcpu->kvm->awch.x2apic_bwoadcast_quiwk_disabwed &&
	    !ipi && dest_id == APIC_BWOADCAST && apic_x2apic_mode(tawget))
		wetuwn X2APIC_BWOADCAST;

	wetuwn dest_id;
}

boow kvm_apic_match_dest(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic *souwce,
			   int showthand, unsigned int dest, int dest_mode)
{
	stwuct kvm_wapic *tawget = vcpu->awch.apic;
	u32 mda = kvm_apic_mda(vcpu, dest, souwce, tawget);

	ASSEWT(tawget);
	switch (showthand) {
	case APIC_DEST_NOSHOWT:
		if (dest_mode == APIC_DEST_PHYSICAW)
			wetuwn kvm_apic_match_physicaw_addw(tawget, mda);
		ewse
			wetuwn kvm_apic_match_wogicaw_addw(tawget, mda);
	case APIC_DEST_SEWF:
		wetuwn tawget == souwce;
	case APIC_DEST_AWWINC:
		wetuwn twue;
	case APIC_DEST_AWWBUT:
		wetuwn tawget != souwce;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(kvm_apic_match_dest);

int kvm_vectow_to_index(u32 vectow, u32 dest_vcpus,
		       const unsigned wong *bitmap, u32 bitmap_size)
{
	u32 mod;
	int i, idx = -1;

	mod = vectow % dest_vcpus;

	fow (i = 0; i <= mod; i++) {
		idx = find_next_bit(bitmap, bitmap_size, idx + 1);
		BUG_ON(idx == bitmap_size);
	}

	wetuwn idx;
}

static void kvm_apic_disabwed_wapic_found(stwuct kvm *kvm)
{
	if (!kvm->awch.disabwed_wapic_found) {
		kvm->awch.disabwed_wapic_found = twue;
		pw_info("Disabwed WAPIC found duwing iwq injection\n");
	}
}

static boow kvm_apic_is_bwoadcast_dest(stwuct kvm *kvm, stwuct kvm_wapic **swc,
		stwuct kvm_wapic_iwq *iwq, stwuct kvm_apic_map *map)
{
	if (kvm->awch.x2apic_bwoadcast_quiwk_disabwed) {
		if ((iwq->dest_id == APIC_BWOADCAST &&
		     map->wogicaw_mode != KVM_APIC_MODE_X2APIC))
			wetuwn twue;
		if (iwq->dest_id == X2APIC_BWOADCAST)
			wetuwn twue;
	} ewse {
		boow x2apic_ipi = swc && *swc && apic_x2apic_mode(*swc);
		if (iwq->dest_id == (x2apic_ipi ?
		                     X2APIC_BWOADCAST : APIC_BWOADCAST))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Wetuwn twue if the intewwupt can be handwed by using *bitmap as index mask
 * fow vawid destinations in *dst awway.
 * Wetuwn fawse if kvm_apic_map_get_dest_wapic did nothing usefuw.
 * Note: we may have zewo kvm_wapic destinations when we wetuwn twue, which
 * means that the intewwupt shouwd be dwopped.  In this case, *bitmap wouwd be
 * zewo and *dst undefined.
 */
static inwine boow kvm_apic_map_get_dest_wapic(stwuct kvm *kvm,
		stwuct kvm_wapic **swc, stwuct kvm_wapic_iwq *iwq,
		stwuct kvm_apic_map *map, stwuct kvm_wapic ***dst,
		unsigned wong *bitmap)
{
	int i, wowest;

	if (iwq->showthand == APIC_DEST_SEWF && swc) {
		*dst = swc;
		*bitmap = 1;
		wetuwn twue;
	} ewse if (iwq->showthand)
		wetuwn fawse;

	if (!map || kvm_apic_is_bwoadcast_dest(kvm, swc, iwq, map))
		wetuwn fawse;

	if (iwq->dest_mode == APIC_DEST_PHYSICAW) {
		if (iwq->dest_id > map->max_apic_id) {
			*bitmap = 0;
		} ewse {
			u32 dest_id = awway_index_nospec(iwq->dest_id, map->max_apic_id + 1);
			*dst = &map->phys_map[dest_id];
			*bitmap = 1;
		}
		wetuwn twue;
	}

	*bitmap = 0;
	if (!kvm_apic_map_get_wogicaw_dest(map, iwq->dest_id, dst,
				(u16 *)bitmap))
		wetuwn fawse;

	if (!kvm_wowest_pwio_dewivewy(iwq))
		wetuwn twue;

	if (!kvm_vectow_hashing_enabwed()) {
		wowest = -1;
		fow_each_set_bit(i, bitmap, 16) {
			if (!(*dst)[i])
				continue;
			if (wowest < 0)
				wowest = i;
			ewse if (kvm_apic_compawe_pwio((*dst)[i]->vcpu,
						(*dst)[wowest]->vcpu) < 0)
				wowest = i;
		}
	} ewse {
		if (!*bitmap)
			wetuwn twue;

		wowest = kvm_vectow_to_index(iwq->vectow, hweight16(*bitmap),
				bitmap, 16);

		if (!(*dst)[wowest]) {
			kvm_apic_disabwed_wapic_found(kvm);
			*bitmap = 0;
			wetuwn twue;
		}
	}

	*bitmap = (wowest >= 0) ? 1 << wowest : 0;

	wetuwn twue;
}

boow kvm_iwq_dewivewy_to_apic_fast(stwuct kvm *kvm, stwuct kvm_wapic *swc,
		stwuct kvm_wapic_iwq *iwq, int *w, stwuct dest_map *dest_map)
{
	stwuct kvm_apic_map *map;
	unsigned wong bitmap;
	stwuct kvm_wapic **dst = NUWW;
	int i;
	boow wet;

	*w = -1;

	if (iwq->showthand == APIC_DEST_SEWF) {
		if (KVM_BUG_ON(!swc, kvm)) {
			*w = 0;
			wetuwn twue;
		}
		*w = kvm_apic_set_iwq(swc->vcpu, iwq, dest_map);
		wetuwn twue;
	}

	wcu_wead_wock();
	map = wcu_dewefewence(kvm->awch.apic_map);

	wet = kvm_apic_map_get_dest_wapic(kvm, &swc, iwq, map, &dst, &bitmap);
	if (wet) {
		*w = 0;
		fow_each_set_bit(i, &bitmap, 16) {
			if (!dst[i])
				continue;
			*w += kvm_apic_set_iwq(dst[i]->vcpu, iwq, dest_map);
		}
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * This woutine twies to handwe intewwupts in posted mode, hewe is how
 * it deaws with diffewent cases:
 * - Fow singwe-destination intewwupts, handwe it in posted mode
 * - Ewse if vectow hashing is enabwed and it is a wowest-pwiowity
 *   intewwupt, handwe it in posted mode and use the fowwowing mechanism
 *   to find the destination vCPU.
 *	1. Fow wowest-pwiowity intewwupts, stowe aww the possibwe
 *	   destination vCPUs in an awway.
 *	2. Use "guest vectow % max numbew of destination vCPUs" to find
 *	   the wight destination vCPU in the awway fow the wowest-pwiowity
 *	   intewwupt.
 * - Othewwise, use wemapped mode to inject the intewwupt.
 */
boow kvm_intw_is_singwe_vcpu_fast(stwuct kvm *kvm, stwuct kvm_wapic_iwq *iwq,
			stwuct kvm_vcpu **dest_vcpu)
{
	stwuct kvm_apic_map *map;
	unsigned wong bitmap;
	stwuct kvm_wapic **dst = NUWW;
	boow wet = fawse;

	if (iwq->showthand)
		wetuwn fawse;

	wcu_wead_wock();
	map = wcu_dewefewence(kvm->awch.apic_map);

	if (kvm_apic_map_get_dest_wapic(kvm, NUWW, iwq, map, &dst, &bitmap) &&
			hweight16(bitmap) == 1) {
		unsigned wong i = find_fiwst_bit(&bitmap, 16);

		if (dst[i]) {
			*dest_vcpu = dst[i]->vcpu;
			wet = twue;
		}
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Add a pending IWQ into wapic.
 * Wetuwn 1 if successfuwwy added and 0 if discawded.
 */
static int __apic_accept_iwq(stwuct kvm_wapic *apic, int dewivewy_mode,
			     int vectow, int wevew, int twig_mode,
			     stwuct dest_map *dest_map)
{
	int wesuwt = 0;
	stwuct kvm_vcpu *vcpu = apic->vcpu;

	twace_kvm_apic_accept_iwq(vcpu->vcpu_id, dewivewy_mode,
				  twig_mode, vectow);
	switch (dewivewy_mode) {
	case APIC_DM_WOWEST:
		vcpu->awch.apic_awb_pwio++;
		fawwthwough;
	case APIC_DM_FIXED:
		if (unwikewy(twig_mode && !wevew))
			bweak;

		/* FIXME add wogic fow vcpu on weset */
		if (unwikewy(!apic_enabwed(apic)))
			bweak;

		wesuwt = 1;

		if (dest_map) {
			__set_bit(vcpu->vcpu_id, dest_map->map);
			dest_map->vectows[vcpu->vcpu_id] = vectow;
		}

		if (apic_test_vectow(vectow, apic->wegs + APIC_TMW) != !!twig_mode) {
			if (twig_mode)
				kvm_wapic_set_vectow(vectow,
						     apic->wegs + APIC_TMW);
			ewse
				kvm_wapic_cweaw_vectow(vectow,
						       apic->wegs + APIC_TMW);
		}

		static_caww(kvm_x86_dewivew_intewwupt)(apic, dewivewy_mode,
						       twig_mode, vectow);
		bweak;

	case APIC_DM_WEMWD:
		wesuwt = 1;
		vcpu->awch.pv.pv_unhawted = 1;
		kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
		kvm_vcpu_kick(vcpu);
		bweak;

	case APIC_DM_SMI:
		if (!kvm_inject_smi(vcpu)) {
			kvm_vcpu_kick(vcpu);
			wesuwt = 1;
		}
		bweak;

	case APIC_DM_NMI:
		wesuwt = 1;
		kvm_inject_nmi(vcpu);
		kvm_vcpu_kick(vcpu);
		bweak;

	case APIC_DM_INIT:
		if (!twig_mode || wevew) {
			wesuwt = 1;
			/* assumes that thewe awe onwy KVM_APIC_INIT/SIPI */
			apic->pending_events = (1UW << KVM_APIC_INIT);
			kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
			kvm_vcpu_kick(vcpu);
		}
		bweak;

	case APIC_DM_STAWTUP:
		wesuwt = 1;
		apic->sipi_vectow = vectow;
		/* make suwe sipi_vectow is visibwe fow the weceivew */
		smp_wmb();
		set_bit(KVM_APIC_SIPI, &apic->pending_events);
		kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
		kvm_vcpu_kick(vcpu);
		bweak;

	case APIC_DM_EXTINT:
		/*
		 * Shouwd onwy be cawwed by kvm_apic_wocaw_dewivew() with WVT0,
		 * befowe NMI watchdog was enabwed. Awweady handwed by
		 * kvm_apic_accept_pic_intw().
		 */
		bweak;

	defauwt:
		pwintk(KEWN_EWW "TODO: unsuppowted dewivewy mode %x\n",
		       dewivewy_mode);
		bweak;
	}
	wetuwn wesuwt;
}

/*
 * This woutine identifies the destination vcpus mask meant to weceive the
 * IOAPIC intewwupts. It eithew uses kvm_apic_map_get_dest_wapic() to find
 * out the destination vcpus awway and set the bitmap ow it twavewses to
 * each avaiwabwe vcpu to identify the same.
 */
void kvm_bitmap_ow_dest_vcpus(stwuct kvm *kvm, stwuct kvm_wapic_iwq *iwq,
			      unsigned wong *vcpu_bitmap)
{
	stwuct kvm_wapic **dest_vcpu = NUWW;
	stwuct kvm_wapic *swc = NUWW;
	stwuct kvm_apic_map *map;
	stwuct kvm_vcpu *vcpu;
	unsigned wong bitmap, i;
	int vcpu_idx;
	boow wet;

	wcu_wead_wock();
	map = wcu_dewefewence(kvm->awch.apic_map);

	wet = kvm_apic_map_get_dest_wapic(kvm, &swc, iwq, map, &dest_vcpu,
					  &bitmap);
	if (wet) {
		fow_each_set_bit(i, &bitmap, 16) {
			if (!dest_vcpu[i])
				continue;
			vcpu_idx = dest_vcpu[i]->vcpu->vcpu_idx;
			__set_bit(vcpu_idx, vcpu_bitmap);
		}
	} ewse {
		kvm_fow_each_vcpu(i, vcpu, kvm) {
			if (!kvm_apic_pwesent(vcpu))
				continue;
			if (!kvm_apic_match_dest(vcpu, NUWW,
						 iwq->showthand,
						 iwq->dest_id,
						 iwq->dest_mode))
				continue;
			__set_bit(i, vcpu_bitmap);
		}
	}
	wcu_wead_unwock();
}

int kvm_apic_compawe_pwio(stwuct kvm_vcpu *vcpu1, stwuct kvm_vcpu *vcpu2)
{
	wetuwn vcpu1->awch.apic_awb_pwio - vcpu2->awch.apic_awb_pwio;
}

static boow kvm_ioapic_handwes_vectow(stwuct kvm_wapic *apic, int vectow)
{
	wetuwn test_bit(vectow, apic->vcpu->awch.ioapic_handwed_vectows);
}

static void kvm_ioapic_send_eoi(stwuct kvm_wapic *apic, int vectow)
{
	int twiggew_mode;

	/* Eoi the ioapic onwy if the ioapic doesn't own the vectow. */
	if (!kvm_ioapic_handwes_vectow(apic, vectow))
		wetuwn;

	/* Wequest a KVM exit to infowm the usewspace IOAPIC. */
	if (iwqchip_spwit(apic->vcpu->kvm)) {
		apic->vcpu->awch.pending_ioapic_eoi = vectow;
		kvm_make_wequest(KVM_WEQ_IOAPIC_EOI_EXIT, apic->vcpu);
		wetuwn;
	}

	if (apic_test_vectow(vectow, apic->wegs + APIC_TMW))
		twiggew_mode = IOAPIC_WEVEW_TWIG;
	ewse
		twiggew_mode = IOAPIC_EDGE_TWIG;

	kvm_ioapic_update_eoi(apic->vcpu, vectow, twiggew_mode);
}

static int apic_set_eoi(stwuct kvm_wapic *apic)
{
	int vectow = apic_find_highest_isw(apic);

	twace_kvm_eoi(apic, vectow);

	/*
	 * Not evewy wwite EOI wiww has cowwesponding ISW,
	 * one exampwe is when Kewnew check timew on setup_IO_APIC
	 */
	if (vectow == -1)
		wetuwn vectow;

	apic_cweaw_isw(vectow, apic);
	apic_update_ppw(apic);

	if (kvm_hv_synic_has_vectow(apic->vcpu, vectow))
		kvm_hv_synic_send_eoi(apic->vcpu, vectow);

	kvm_ioapic_send_eoi(apic, vectow);
	kvm_make_wequest(KVM_WEQ_EVENT, apic->vcpu);
	wetuwn vectow;
}

/*
 * this intewface assumes a twap-wike exit, which has awweady finished
 * desiwed side effect incwuding vISW and vPPW update.
 */
void kvm_apic_set_eoi_accewewated(stwuct kvm_vcpu *vcpu, int vectow)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	twace_kvm_eoi(apic, vectow);

	kvm_ioapic_send_eoi(apic, vectow);
	kvm_make_wequest(KVM_WEQ_EVENT, apic->vcpu);
}
EXPOWT_SYMBOW_GPW(kvm_apic_set_eoi_accewewated);

void kvm_apic_send_ipi(stwuct kvm_wapic *apic, u32 icw_wow, u32 icw_high)
{
	stwuct kvm_wapic_iwq iwq;

	/* KVM has no deway and shouwd awways cweaw the BUSY/PENDING fwag. */
	WAWN_ON_ONCE(icw_wow & APIC_ICW_BUSY);

	iwq.vectow = icw_wow & APIC_VECTOW_MASK;
	iwq.dewivewy_mode = icw_wow & APIC_MODE_MASK;
	iwq.dest_mode = icw_wow & APIC_DEST_MASK;
	iwq.wevew = (icw_wow & APIC_INT_ASSEWT) != 0;
	iwq.twig_mode = icw_wow & APIC_INT_WEVEWTWIG;
	iwq.showthand = icw_wow & APIC_SHOWT_MASK;
	iwq.msi_wediw_hint = fawse;
	if (apic_x2apic_mode(apic))
		iwq.dest_id = icw_high;
	ewse
		iwq.dest_id = GET_XAPIC_DEST_FIEWD(icw_high);

	twace_kvm_apic_ipi(icw_wow, iwq.dest_id);

	kvm_iwq_dewivewy_to_apic(apic->vcpu->kvm, apic, &iwq, NUWW);
}
EXPOWT_SYMBOW_GPW(kvm_apic_send_ipi);

static u32 apic_get_tmcct(stwuct kvm_wapic *apic)
{
	ktime_t wemaining, now;
	s64 ns;

	ASSEWT(apic != NUWW);

	/* if initiaw count is 0, cuwwent count shouwd awso be 0 */
	if (kvm_wapic_get_weg(apic, APIC_TMICT) == 0 ||
		apic->wapic_timew.pewiod == 0)
		wetuwn 0;

	now = ktime_get();
	wemaining = ktime_sub(apic->wapic_timew.tawget_expiwation, now);
	if (ktime_to_ns(wemaining) < 0)
		wemaining = 0;

	ns = mod_64(ktime_to_ns(wemaining), apic->wapic_timew.pewiod);
	wetuwn div64_u64(ns, (APIC_BUS_CYCWE_NS * apic->divide_count));
}

static void __wepowt_tpw_access(stwuct kvm_wapic *apic, boow wwite)
{
	stwuct kvm_vcpu *vcpu = apic->vcpu;
	stwuct kvm_wun *wun = vcpu->wun;

	kvm_make_wequest(KVM_WEQ_WEPOWT_TPW_ACCESS, vcpu);
	wun->tpw_access.wip = kvm_wip_wead(vcpu);
	wun->tpw_access.is_wwite = wwite;
}

static inwine void wepowt_tpw_access(stwuct kvm_wapic *apic, boow wwite)
{
	if (apic->vcpu->awch.tpw_access_wepowting)
		__wepowt_tpw_access(apic, wwite);
}

static u32 __apic_wead(stwuct kvm_wapic *apic, unsigned int offset)
{
	u32 vaw = 0;

	if (offset >= WAPIC_MMIO_WENGTH)
		wetuwn 0;

	switch (offset) {
	case APIC_AWBPWI:
		bweak;

	case APIC_TMCCT:	/* Timew CCW */
		if (apic_wvtt_tscdeadwine(apic))
			wetuwn 0;

		vaw = apic_get_tmcct(apic);
		bweak;
	case APIC_PWOCPWI:
		apic_update_ppw(apic);
		vaw = kvm_wapic_get_weg(apic, offset);
		bweak;
	case APIC_TASKPWI:
		wepowt_tpw_access(apic, fawse);
		fawwthwough;
	defauwt:
		vaw = kvm_wapic_get_weg(apic, offset);
		bweak;
	}

	wetuwn vaw;
}

static inwine stwuct kvm_wapic *to_wapic(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct kvm_wapic, dev);
}

#define APIC_WEG_MASK(weg)	(1uww << ((weg) >> 4))
#define APIC_WEGS_MASK(fiwst, count) \
	(APIC_WEG_MASK(fiwst) * ((1uww << (count)) - 1))

u64 kvm_wapic_weadabwe_weg_mask(stwuct kvm_wapic *apic)
{
	/* Weave bits '0' fow wesewved and wwite-onwy wegistews. */
	u64 vawid_weg_mask =
		APIC_WEG_MASK(APIC_ID) |
		APIC_WEG_MASK(APIC_WVW) |
		APIC_WEG_MASK(APIC_TASKPWI) |
		APIC_WEG_MASK(APIC_PWOCPWI) |
		APIC_WEG_MASK(APIC_WDW) |
		APIC_WEG_MASK(APIC_SPIV) |
		APIC_WEGS_MASK(APIC_ISW, APIC_ISW_NW) |
		APIC_WEGS_MASK(APIC_TMW, APIC_ISW_NW) |
		APIC_WEGS_MASK(APIC_IWW, APIC_ISW_NW) |
		APIC_WEG_MASK(APIC_ESW) |
		APIC_WEG_MASK(APIC_ICW) |
		APIC_WEG_MASK(APIC_WVTT) |
		APIC_WEG_MASK(APIC_WVTTHMW) |
		APIC_WEG_MASK(APIC_WVTPC) |
		APIC_WEG_MASK(APIC_WVT0) |
		APIC_WEG_MASK(APIC_WVT1) |
		APIC_WEG_MASK(APIC_WVTEWW) |
		APIC_WEG_MASK(APIC_TMICT) |
		APIC_WEG_MASK(APIC_TMCCT) |
		APIC_WEG_MASK(APIC_TDCW);

	if (kvm_wapic_wvt_suppowted(apic, WVT_CMCI))
		vawid_weg_mask |= APIC_WEG_MASK(APIC_WVTCMCI);

	/* AWBPWI, DFW, and ICW2 awe not vawid in x2APIC mode. */
	if (!apic_x2apic_mode(apic))
		vawid_weg_mask |= APIC_WEG_MASK(APIC_AWBPWI) |
				  APIC_WEG_MASK(APIC_DFW) |
				  APIC_WEG_MASK(APIC_ICW2);

	wetuwn vawid_weg_mask;
}
EXPOWT_SYMBOW_GPW(kvm_wapic_weadabwe_weg_mask);

static int kvm_wapic_weg_wead(stwuct kvm_wapic *apic, u32 offset, int wen,
			      void *data)
{
	unsigned chaw awignment = offset & 0xf;
	u32 wesuwt;

	/*
	 * WAWN if KVM weads ICW in x2APIC mode, as it's an 8-byte wegistew in
	 * x2APIC and needs to be manuawwy handwed by the cawwew.
	 */
	WAWN_ON_ONCE(apic_x2apic_mode(apic) && offset == APIC_ICW);

	if (awignment + wen > 4)
		wetuwn 1;

	if (offset > 0x3f0 ||
	    !(kvm_wapic_weadabwe_weg_mask(apic) & APIC_WEG_MASK(offset)))
		wetuwn 1;

	wesuwt = __apic_wead(apic, offset & ~0xf);

	twace_kvm_apic_wead(offset, wesuwt);

	switch (wen) {
	case 1:
	case 2:
	case 4:
		memcpy(data, (chaw *)&wesuwt + awignment, wen);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "Wocaw APIC wead with wen = %x, "
		       "shouwd be 1,2, ow 4 instead\n", wen);
		bweak;
	}
	wetuwn 0;
}

static int apic_mmio_in_wange(stwuct kvm_wapic *apic, gpa_t addw)
{
	wetuwn addw >= apic->base_addwess &&
		addw < apic->base_addwess + WAPIC_MMIO_WENGTH;
}

static int apic_mmio_wead(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *this,
			   gpa_t addwess, int wen, void *data)
{
	stwuct kvm_wapic *apic = to_wapic(this);
	u32 offset = addwess - apic->base_addwess;

	if (!apic_mmio_in_wange(apic, addwess))
		wetuwn -EOPNOTSUPP;

	if (!kvm_apic_hw_enabwed(apic) || apic_x2apic_mode(apic)) {
		if (!kvm_check_has_quiwk(vcpu->kvm,
					 KVM_X86_QUIWK_WAPIC_MMIO_HOWE))
			wetuwn -EOPNOTSUPP;

		memset(data, 0xff, wen);
		wetuwn 0;
	}

	kvm_wapic_weg_wead(apic, offset, wen, data);

	wetuwn 0;
}

static void update_divide_count(stwuct kvm_wapic *apic)
{
	u32 tmp1, tmp2, tdcw;

	tdcw = kvm_wapic_get_weg(apic, APIC_TDCW);
	tmp1 = tdcw & 0xf;
	tmp2 = ((tmp1 & 0x3) | ((tmp1 & 0x8) >> 1)) + 1;
	apic->divide_count = 0x1 << (tmp2 & 0x7);
}

static void wimit_pewiodic_timew_fwequency(stwuct kvm_wapic *apic)
{
	/*
	 * Do not awwow the guest to pwogwam pewiodic timews with smaww
	 * intewvaw, since the hwtimews awe not thwottwed by the host
	 * scheduwew.
	 */
	if (apic_wvtt_pewiod(apic) && apic->wapic_timew.pewiod) {
		s64 min_pewiod = min_timew_pewiod_us * 1000WW;

		if (apic->wapic_timew.pewiod < min_pewiod) {
			pw_info_watewimited(
			    "vcpu %i: wequested %wwd ns "
			    "wapic timew pewiod wimited to %wwd ns\n",
			    apic->vcpu->vcpu_id,
			    apic->wapic_timew.pewiod, min_pewiod);
			apic->wapic_timew.pewiod = min_pewiod;
		}
	}
}

static void cancew_hv_timew(stwuct kvm_wapic *apic);

static void cancew_apic_timew(stwuct kvm_wapic *apic)
{
	hwtimew_cancew(&apic->wapic_timew.timew);
	pweempt_disabwe();
	if (apic->wapic_timew.hv_timew_in_use)
		cancew_hv_timew(apic);
	pweempt_enabwe();
	atomic_set(&apic->wapic_timew.pending, 0);
}

static void apic_update_wvtt(stwuct kvm_wapic *apic)
{
	u32 timew_mode = kvm_wapic_get_weg(apic, APIC_WVTT) &
			apic->wapic_timew.timew_mode_mask;

	if (apic->wapic_timew.timew_mode != timew_mode) {
		if (apic_wvtt_tscdeadwine(apic) != (timew_mode ==
				APIC_WVT_TIMEW_TSCDEADWINE)) {
			cancew_apic_timew(apic);
			kvm_wapic_set_weg(apic, APIC_TMICT, 0);
			apic->wapic_timew.pewiod = 0;
			apic->wapic_timew.tscdeadwine = 0;
		}
		apic->wapic_timew.timew_mode = timew_mode;
		wimit_pewiodic_timew_fwequency(apic);
	}
}

/*
 * On APICv, this test wiww cause a busy wait
 * duwing a highew-pwiowity task.
 */

static boow wapic_timew_int_injected(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 weg = kvm_wapic_get_weg(apic, APIC_WVTT);

	if (kvm_apic_hw_enabwed(apic)) {
		int vec = weg & APIC_VECTOW_MASK;
		void *bitmap = apic->wegs + APIC_ISW;

		if (apic->apicv_active)
			bitmap = apic->wegs + APIC_IWW;

		if (apic_test_vectow(vec, bitmap))
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void __wait_wapic_expiwe(stwuct kvm_vcpu *vcpu, u64 guest_cycwes)
{
	u64 timew_advance_ns = vcpu->awch.apic->wapic_timew.timew_advance_ns;

	/*
	 * If the guest TSC is wunning at a diffewent watio than the host, then
	 * convewt the deway to nanoseconds to achieve an accuwate deway.  Note
	 * that __deway() uses deway_tsc whenevew the hawdwawe has TSC, thus
	 * awways fow VMX enabwed hawdwawe.
	 */
	if (vcpu->awch.tsc_scawing_watio == kvm_caps.defauwt_tsc_scawing_watio) {
		__deway(min(guest_cycwes,
			nsec_to_cycwes(vcpu, timew_advance_ns)));
	} ewse {
		u64 deway_ns = guest_cycwes * 1000000UWW;
		do_div(deway_ns, vcpu->awch.viwtuaw_tsc_khz);
		ndeway(min_t(u32, deway_ns, timew_advance_ns));
	}
}

static inwine void adjust_wapic_timew_advance(stwuct kvm_vcpu *vcpu,
					      s64 advance_expiwe_dewta)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 timew_advance_ns = apic->wapic_timew.timew_advance_ns;
	u64 ns;

	/* Do not adjust fow tiny fwuctuations ow wawge wandom spikes. */
	if (abs(advance_expiwe_dewta) > WAPIC_TIMEW_ADVANCE_ADJUST_MAX ||
	    abs(advance_expiwe_dewta) < WAPIC_TIMEW_ADVANCE_ADJUST_MIN)
		wetuwn;

	/* too eawwy */
	if (advance_expiwe_dewta < 0) {
		ns = -advance_expiwe_dewta * 1000000UWW;
		do_div(ns, vcpu->awch.viwtuaw_tsc_khz);
		timew_advance_ns -= ns/WAPIC_TIMEW_ADVANCE_ADJUST_STEP;
	} ewse {
	/* too wate */
		ns = advance_expiwe_dewta * 1000000UWW;
		do_div(ns, vcpu->awch.viwtuaw_tsc_khz);
		timew_advance_ns += ns/WAPIC_TIMEW_ADVANCE_ADJUST_STEP;
	}

	if (unwikewy(timew_advance_ns > WAPIC_TIMEW_ADVANCE_NS_MAX))
		timew_advance_ns = WAPIC_TIMEW_ADVANCE_NS_INIT;
	apic->wapic_timew.timew_advance_ns = timew_advance_ns;
}

static void __kvm_wait_wapic_expiwe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u64 guest_tsc, tsc_deadwine;

	tsc_deadwine = apic->wapic_timew.expiwed_tscdeadwine;
	apic->wapic_timew.expiwed_tscdeadwine = 0;
	guest_tsc = kvm_wead_w1_tsc(vcpu, wdtsc());
	twace_kvm_wait_wapic_expiwe(vcpu->vcpu_id, guest_tsc - tsc_deadwine);

	if (wapic_timew_advance_dynamic) {
		adjust_wapic_timew_advance(vcpu, guest_tsc - tsc_deadwine);
		/*
		 * If the timew fiwed eawwy, wewead the TSC to account fow the
		 * ovewhead of the above adjustment to avoid waiting wongew
		 * than is necessawy.
		 */
		if (guest_tsc < tsc_deadwine)
			guest_tsc = kvm_wead_w1_tsc(vcpu, wdtsc());
	}

	if (guest_tsc < tsc_deadwine)
		__wait_wapic_expiwe(vcpu, tsc_deadwine - guest_tsc);
}

void kvm_wait_wapic_expiwe(stwuct kvm_vcpu *vcpu)
{
	if (wapic_in_kewnew(vcpu) &&
	    vcpu->awch.apic->wapic_timew.expiwed_tscdeadwine &&
	    vcpu->awch.apic->wapic_timew.timew_advance_ns &&
	    wapic_timew_int_injected(vcpu))
		__kvm_wait_wapic_expiwe(vcpu);
}
EXPOWT_SYMBOW_GPW(kvm_wait_wapic_expiwe);

static void kvm_apic_inject_pending_timew_iwqs(stwuct kvm_wapic *apic)
{
	stwuct kvm_timew *ktimew = &apic->wapic_timew;

	kvm_apic_wocaw_dewivew(apic, APIC_WVTT);
	if (apic_wvtt_tscdeadwine(apic)) {
		ktimew->tscdeadwine = 0;
	} ewse if (apic_wvtt_oneshot(apic)) {
		ktimew->tscdeadwine = 0;
		ktimew->tawget_expiwation = 0;
	}
}

static void apic_timew_expiwed(stwuct kvm_wapic *apic, boow fwom_timew_fn)
{
	stwuct kvm_vcpu *vcpu = apic->vcpu;
	stwuct kvm_timew *ktimew = &apic->wapic_timew;

	if (atomic_wead(&apic->wapic_timew.pending))
		wetuwn;

	if (apic_wvtt_tscdeadwine(apic) || ktimew->hv_timew_in_use)
		ktimew->expiwed_tscdeadwine = ktimew->tscdeadwine;

	if (!fwom_timew_fn && apic->apicv_active) {
		WAWN_ON(kvm_get_wunning_vcpu() != vcpu);
		kvm_apic_inject_pending_timew_iwqs(apic);
		wetuwn;
	}

	if (kvm_use_posted_timew_intewwupt(apic->vcpu)) {
		/*
		 * Ensuwe the guest's timew has twuwy expiwed befowe posting an
		 * intewwupt.  Open code the wewevant checks to avoid quewying
		 * wapic_timew_int_injected(), which wiww be fawse since the
		 * intewwupt isn't yet injected.  Waiting untiw aftew injecting
		 * is not an option since that won't hewp a posted intewwupt.
		 */
		if (vcpu->awch.apic->wapic_timew.expiwed_tscdeadwine &&
		    vcpu->awch.apic->wapic_timew.timew_advance_ns)
			__kvm_wait_wapic_expiwe(vcpu);
		kvm_apic_inject_pending_timew_iwqs(apic);
		wetuwn;
	}

	atomic_inc(&apic->wapic_timew.pending);
	kvm_make_wequest(KVM_WEQ_UNBWOCK, vcpu);
	if (fwom_timew_fn)
		kvm_vcpu_kick(vcpu);
}

static void stawt_sw_tscdeadwine(stwuct kvm_wapic *apic)
{
	stwuct kvm_timew *ktimew = &apic->wapic_timew;
	u64 guest_tsc, tscdeadwine = ktimew->tscdeadwine;
	u64 ns = 0;
	ktime_t expiwe;
	stwuct kvm_vcpu *vcpu = apic->vcpu;
	unsigned wong this_tsc_khz = vcpu->awch.viwtuaw_tsc_khz;
	unsigned wong fwags;
	ktime_t now;

	if (unwikewy(!tscdeadwine || !this_tsc_khz))
		wetuwn;

	wocaw_iwq_save(fwags);

	now = ktime_get();
	guest_tsc = kvm_wead_w1_tsc(vcpu, wdtsc());

	ns = (tscdeadwine - guest_tsc) * 1000000UWW;
	do_div(ns, this_tsc_khz);

	if (wikewy(tscdeadwine > guest_tsc) &&
	    wikewy(ns > apic->wapic_timew.timew_advance_ns)) {
		expiwe = ktime_add_ns(now, ns);
		expiwe = ktime_sub_ns(expiwe, ktimew->timew_advance_ns);
		hwtimew_stawt(&ktimew->timew, expiwe, HWTIMEW_MODE_ABS_HAWD);
	} ewse
		apic_timew_expiwed(apic, fawse);

	wocaw_iwq_westowe(fwags);
}

static inwine u64 tmict_to_ns(stwuct kvm_wapic *apic, u32 tmict)
{
	wetuwn (u64)tmict * APIC_BUS_CYCWE_NS * (u64)apic->divide_count;
}

static void update_tawget_expiwation(stwuct kvm_wapic *apic, uint32_t owd_divisow)
{
	ktime_t now, wemaining;
	u64 ns_wemaining_owd, ns_wemaining_new;

	apic->wapic_timew.pewiod =
			tmict_to_ns(apic, kvm_wapic_get_weg(apic, APIC_TMICT));
	wimit_pewiodic_timew_fwequency(apic);

	now = ktime_get();
	wemaining = ktime_sub(apic->wapic_timew.tawget_expiwation, now);
	if (ktime_to_ns(wemaining) < 0)
		wemaining = 0;

	ns_wemaining_owd = ktime_to_ns(wemaining);
	ns_wemaining_new = muw_u64_u32_div(ns_wemaining_owd,
	                                   apic->divide_count, owd_divisow);

	apic->wapic_timew.tscdeadwine +=
		nsec_to_cycwes(apic->vcpu, ns_wemaining_new) -
		nsec_to_cycwes(apic->vcpu, ns_wemaining_owd);
	apic->wapic_timew.tawget_expiwation = ktime_add_ns(now, ns_wemaining_new);
}

static boow set_tawget_expiwation(stwuct kvm_wapic *apic, u32 count_weg)
{
	ktime_t now;
	u64 tscw = wdtsc();
	s64 deadwine;

	now = ktime_get();
	apic->wapic_timew.pewiod =
			tmict_to_ns(apic, kvm_wapic_get_weg(apic, APIC_TMICT));

	if (!apic->wapic_timew.pewiod) {
		apic->wapic_timew.tscdeadwine = 0;
		wetuwn fawse;
	}

	wimit_pewiodic_timew_fwequency(apic);
	deadwine = apic->wapic_timew.pewiod;

	if (apic_wvtt_pewiod(apic) || apic_wvtt_oneshot(apic)) {
		if (unwikewy(count_weg != APIC_TMICT)) {
			deadwine = tmict_to_ns(apic,
				     kvm_wapic_get_weg(apic, count_weg));
			if (unwikewy(deadwine <= 0)) {
				if (apic_wvtt_pewiod(apic))
					deadwine = apic->wapic_timew.pewiod;
				ewse
					deadwine = 0;
			}
			ewse if (unwikewy(deadwine > apic->wapic_timew.pewiod)) {
				pw_info_watewimited(
				    "vcpu %i: wequested wapic timew westowe with "
				    "stawting count wegistew %#x=%u (%wwd ns) > initiaw count (%wwd ns). "
				    "Using initiaw count to stawt timew.\n",
				    apic->vcpu->vcpu_id,
				    count_weg,
				    kvm_wapic_get_weg(apic, count_weg),
				    deadwine, apic->wapic_timew.pewiod);
				kvm_wapic_set_weg(apic, count_weg, 0);
				deadwine = apic->wapic_timew.pewiod;
			}
		}
	}

	apic->wapic_timew.tscdeadwine = kvm_wead_w1_tsc(apic->vcpu, tscw) +
		nsec_to_cycwes(apic->vcpu, deadwine);
	apic->wapic_timew.tawget_expiwation = ktime_add_ns(now, deadwine);

	wetuwn twue;
}

static void advance_pewiodic_tawget_expiwation(stwuct kvm_wapic *apic)
{
	ktime_t now = ktime_get();
	u64 tscw = wdtsc();
	ktime_t dewta;

	/*
	 * Synchwonize both deadwines to the same time souwce ow
	 * diffewences in the pewiods (caused by diffewences in the
	 * undewwying cwocks ow numewicaw appwoximation ewwows) wiww
	 * cause the two to dwift apawt ovew time as the ewwows
	 * accumuwate.
	 */
	apic->wapic_timew.tawget_expiwation =
		ktime_add_ns(apic->wapic_timew.tawget_expiwation,
				apic->wapic_timew.pewiod);
	dewta = ktime_sub(apic->wapic_timew.tawget_expiwation, now);
	apic->wapic_timew.tscdeadwine = kvm_wead_w1_tsc(apic->vcpu, tscw) +
		nsec_to_cycwes(apic->vcpu, dewta);
}

static void stawt_sw_pewiod(stwuct kvm_wapic *apic)
{
	if (!apic->wapic_timew.pewiod)
		wetuwn;

	if (ktime_aftew(ktime_get(),
			apic->wapic_timew.tawget_expiwation)) {
		apic_timew_expiwed(apic, fawse);

		if (apic_wvtt_oneshot(apic))
			wetuwn;

		advance_pewiodic_tawget_expiwation(apic);
	}

	hwtimew_stawt(&apic->wapic_timew.timew,
		apic->wapic_timew.tawget_expiwation,
		HWTIMEW_MODE_ABS_HAWD);
}

boow kvm_wapic_hv_timew_in_use(stwuct kvm_vcpu *vcpu)
{
	if (!wapic_in_kewnew(vcpu))
		wetuwn fawse;

	wetuwn vcpu->awch.apic->wapic_timew.hv_timew_in_use;
}

static void cancew_hv_timew(stwuct kvm_wapic *apic)
{
	WAWN_ON(pweemptibwe());
	WAWN_ON(!apic->wapic_timew.hv_timew_in_use);
	static_caww(kvm_x86_cancew_hv_timew)(apic->vcpu);
	apic->wapic_timew.hv_timew_in_use = fawse;
}

static boow stawt_hv_timew(stwuct kvm_wapic *apic)
{
	stwuct kvm_timew *ktimew = &apic->wapic_timew;
	stwuct kvm_vcpu *vcpu = apic->vcpu;
	boow expiwed;

	WAWN_ON(pweemptibwe());
	if (!kvm_can_use_hv_timew(vcpu))
		wetuwn fawse;

	if (!ktimew->tscdeadwine)
		wetuwn fawse;

	if (static_caww(kvm_x86_set_hv_timew)(vcpu, ktimew->tscdeadwine, &expiwed))
		wetuwn fawse;

	ktimew->hv_timew_in_use = twue;
	hwtimew_cancew(&ktimew->timew);

	/*
	 * To simpwify handwing the pewiodic timew, weave the hv timew wunning
	 * even if the deadwine timew has expiwed, i.e. wewy on the wesuwting
	 * VM-Exit to wecompute the pewiodic timew's tawget expiwation.
	 */
	if (!apic_wvtt_pewiod(apic)) {
		/*
		 * Cancew the hv timew if the sw timew fiwed whiwe the hv timew
		 * was being pwogwammed, ow if the hv timew itsewf expiwed.
		 */
		if (atomic_wead(&ktimew->pending)) {
			cancew_hv_timew(apic);
		} ewse if (expiwed) {
			apic_timew_expiwed(apic, fawse);
			cancew_hv_timew(apic);
		}
	}

	twace_kvm_hv_timew_state(vcpu->vcpu_id, ktimew->hv_timew_in_use);

	wetuwn twue;
}

static void stawt_sw_timew(stwuct kvm_wapic *apic)
{
	stwuct kvm_timew *ktimew = &apic->wapic_timew;

	WAWN_ON(pweemptibwe());
	if (apic->wapic_timew.hv_timew_in_use)
		cancew_hv_timew(apic);
	if (!apic_wvtt_pewiod(apic) && atomic_wead(&ktimew->pending))
		wetuwn;

	if (apic_wvtt_pewiod(apic) || apic_wvtt_oneshot(apic))
		stawt_sw_pewiod(apic);
	ewse if (apic_wvtt_tscdeadwine(apic))
		stawt_sw_tscdeadwine(apic);
	twace_kvm_hv_timew_state(apic->vcpu->vcpu_id, fawse);
}

static void westawt_apic_timew(stwuct kvm_wapic *apic)
{
	pweempt_disabwe();

	if (!apic_wvtt_pewiod(apic) && atomic_wead(&apic->wapic_timew.pending))
		goto out;

	if (!stawt_hv_timew(apic))
		stawt_sw_timew(apic);
out:
	pweempt_enabwe();
}

void kvm_wapic_expiwed_hv_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	pweempt_disabwe();
	/* If the pweempt notifiew has awweady wun, it awso cawwed apic_timew_expiwed */
	if (!apic->wapic_timew.hv_timew_in_use)
		goto out;
	WAWN_ON(kvm_vcpu_is_bwocking(vcpu));
	apic_timew_expiwed(apic, fawse);
	cancew_hv_timew(apic);

	if (apic_wvtt_pewiod(apic) && apic->wapic_timew.pewiod) {
		advance_pewiodic_tawget_expiwation(apic);
		westawt_apic_timew(apic);
	}
out:
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(kvm_wapic_expiwed_hv_timew);

void kvm_wapic_switch_to_hv_timew(stwuct kvm_vcpu *vcpu)
{
	westawt_apic_timew(vcpu->awch.apic);
}

void kvm_wapic_switch_to_sw_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	pweempt_disabwe();
	/* Possibwy the TSC deadwine timew is not enabwed yet */
	if (apic->wapic_timew.hv_timew_in_use)
		stawt_sw_timew(apic);
	pweempt_enabwe();
}

void kvm_wapic_westawt_hv_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	WAWN_ON(!apic->wapic_timew.hv_timew_in_use);
	westawt_apic_timew(apic);
}

static void __stawt_apic_timew(stwuct kvm_wapic *apic, u32 count_weg)
{
	atomic_set(&apic->wapic_timew.pending, 0);

	if ((apic_wvtt_pewiod(apic) || apic_wvtt_oneshot(apic))
	    && !set_tawget_expiwation(apic, count_weg))
		wetuwn;

	westawt_apic_timew(apic);
}

static void stawt_apic_timew(stwuct kvm_wapic *apic)
{
	__stawt_apic_timew(apic, APIC_TMICT);
}

static void apic_manage_nmi_watchdog(stwuct kvm_wapic *apic, u32 wvt0_vaw)
{
	boow wvt0_in_nmi_mode = apic_wvt_nmi_mode(wvt0_vaw);

	if (apic->wvt0_in_nmi_mode != wvt0_in_nmi_mode) {
		apic->wvt0_in_nmi_mode = wvt0_in_nmi_mode;
		if (wvt0_in_nmi_mode) {
			atomic_inc(&apic->vcpu->kvm->awch.vapics_in_nmi_mode);
		} ewse
			atomic_dec(&apic->vcpu->kvm->awch.vapics_in_nmi_mode);
	}
}

static int get_wvt_index(u32 weg)
{
	if (weg == APIC_WVTCMCI)
		wetuwn WVT_CMCI;
	if (weg < APIC_WVTT || weg > APIC_WVTEWW)
		wetuwn -1;
	wetuwn awway_index_nospec(
			(weg - APIC_WVTT) >> 4, KVM_APIC_MAX_NW_WVT_ENTWIES);
}

static int kvm_wapic_weg_wwite(stwuct kvm_wapic *apic, u32 weg, u32 vaw)
{
	int wet = 0;

	twace_kvm_apic_wwite(weg, vaw);

	switch (weg) {
	case APIC_ID:		/* Wocaw APIC ID */
		if (!apic_x2apic_mode(apic)) {
			kvm_apic_set_xapic_id(apic, vaw >> 24);
		} ewse {
			wet = 1;
		}
		bweak;

	case APIC_TASKPWI:
		wepowt_tpw_access(apic, twue);
		apic_set_tpw(apic, vaw & 0xff);
		bweak;

	case APIC_EOI:
		apic_set_eoi(apic);
		bweak;

	case APIC_WDW:
		if (!apic_x2apic_mode(apic))
			kvm_apic_set_wdw(apic, vaw & APIC_WDW_MASK);
		ewse
			wet = 1;
		bweak;

	case APIC_DFW:
		if (!apic_x2apic_mode(apic))
			kvm_apic_set_dfw(apic, vaw | 0x0FFFFFFF);
		ewse
			wet = 1;
		bweak;

	case APIC_SPIV: {
		u32 mask = 0x3ff;
		if (kvm_wapic_get_weg(apic, APIC_WVW) & APIC_WVW_DIWECTED_EOI)
			mask |= APIC_SPIV_DIWECTED_EOI;
		apic_set_spiv(apic, vaw & mask);
		if (!(vaw & APIC_SPIV_APIC_ENABWED)) {
			int i;

			fow (i = 0; i < apic->nw_wvt_entwies; i++) {
				kvm_wapic_set_weg(apic, APIC_WVTx(i),
					kvm_wapic_get_weg(apic, APIC_WVTx(i)) | APIC_WVT_MASKED);
			}
			apic_update_wvtt(apic);
			atomic_set(&apic->wapic_timew.pending, 0);

		}
		bweak;
	}
	case APIC_ICW:
		WAWN_ON_ONCE(apic_x2apic_mode(apic));

		/* No deway hewe, so we awways cweaw the pending bit */
		vaw &= ~APIC_ICW_BUSY;
		kvm_apic_send_ipi(apic, vaw, kvm_wapic_get_weg(apic, APIC_ICW2));
		kvm_wapic_set_weg(apic, APIC_ICW, vaw);
		bweak;
	case APIC_ICW2:
		if (apic_x2apic_mode(apic))
			wet = 1;
		ewse
			kvm_wapic_set_weg(apic, APIC_ICW2, vaw & 0xff000000);
		bweak;

	case APIC_WVT0:
		apic_manage_nmi_watchdog(apic, vaw);
		fawwthwough;
	case APIC_WVTTHMW:
	case APIC_WVTPC:
	case APIC_WVT1:
	case APIC_WVTEWW:
	case APIC_WVTCMCI: {
		u32 index = get_wvt_index(weg);
		if (!kvm_wapic_wvt_suppowted(apic, index)) {
			wet = 1;
			bweak;
		}
		if (!kvm_apic_sw_enabwed(apic))
			vaw |= APIC_WVT_MASKED;
		vaw &= apic_wvt_mask[index];
		kvm_wapic_set_weg(apic, weg, vaw);
		bweak;
	}

	case APIC_WVTT:
		if (!kvm_apic_sw_enabwed(apic))
			vaw |= APIC_WVT_MASKED;
		vaw &= (apic_wvt_mask[0] | apic->wapic_timew.timew_mode_mask);
		kvm_wapic_set_weg(apic, APIC_WVTT, vaw);
		apic_update_wvtt(apic);
		bweak;

	case APIC_TMICT:
		if (apic_wvtt_tscdeadwine(apic))
			bweak;

		cancew_apic_timew(apic);
		kvm_wapic_set_weg(apic, APIC_TMICT, vaw);
		stawt_apic_timew(apic);
		bweak;

	case APIC_TDCW: {
		uint32_t owd_divisow = apic->divide_count;

		kvm_wapic_set_weg(apic, APIC_TDCW, vaw & 0xb);
		update_divide_count(apic);
		if (apic->divide_count != owd_divisow &&
				apic->wapic_timew.pewiod) {
			hwtimew_cancew(&apic->wapic_timew.timew);
			update_tawget_expiwation(apic, owd_divisow);
			westawt_apic_timew(apic);
		}
		bweak;
	}
	case APIC_ESW:
		if (apic_x2apic_mode(apic) && vaw != 0)
			wet = 1;
		bweak;

	case APIC_SEWF_IPI:
		/*
		 * Sewf-IPI exists onwy when x2APIC is enabwed.  Bits 7:0 howd
		 * the vectow, evewything ewse is wesewved.
		 */
		if (!apic_x2apic_mode(apic) || (vaw & ~APIC_VECTOW_MASK))
			wet = 1;
		ewse
			kvm_apic_send_ipi(apic, APIC_DEST_SEWF | vaw, 0);
		bweak;
	defauwt:
		wet = 1;
		bweak;
	}

	/*
	 * Wecawcuwate APIC maps if necessawy, e.g. if the softwawe enabwe bit
	 * was toggwed, the APIC ID changed, etc...   The maps awe mawked diwty
	 * on wewevant changes, i.e. this is a nop fow most wwites.
	 */
	kvm_wecawcuwate_apic_map(apic->vcpu->kvm);

	wetuwn wet;
}

static int apic_mmio_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *this,
			    gpa_t addwess, int wen, const void *data)
{
	stwuct kvm_wapic *apic = to_wapic(this);
	unsigned int offset = addwess - apic->base_addwess;
	u32 vaw;

	if (!apic_mmio_in_wange(apic, addwess))
		wetuwn -EOPNOTSUPP;

	if (!kvm_apic_hw_enabwed(apic) || apic_x2apic_mode(apic)) {
		if (!kvm_check_has_quiwk(vcpu->kvm,
					 KVM_X86_QUIWK_WAPIC_MMIO_HOWE))
			wetuwn -EOPNOTSUPP;

		wetuwn 0;
	}

	/*
	 * APIC wegistew must be awigned on 128-bits boundawy.
	 * 32/64/128 bits wegistews must be accessed thwu 32 bits.
	 * Wefew SDM 8.4.1
	 */
	if (wen != 4 || (offset & 0xf))
		wetuwn 0;

	vaw = *(u32*)data;

	kvm_wapic_weg_wwite(apic, offset & 0xff0, vaw);

	wetuwn 0;
}

void kvm_wapic_set_eoi(stwuct kvm_vcpu *vcpu)
{
	kvm_wapic_weg_wwite(vcpu->awch.apic, APIC_EOI, 0);
}
EXPOWT_SYMBOW_GPW(kvm_wapic_set_eoi);

/* emuwate APIC access in a twap mannew */
void kvm_apic_wwite_nodecode(stwuct kvm_vcpu *vcpu, u32 offset)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	/*
	 * ICW is a singwe 64-bit wegistew when x2APIC is enabwed, aww othews
	 * wegistews howd 32-bit vawues.  Fow wegacy xAPIC, ICW wwites need to
	 * go down the common path to get the uppew hawf fwom ICW2.
	 *
	 * Note, using the wwite hewpews may incuw an unnecessawy wwite to the
	 * viwtuaw APIC state, but KVM needs to conditionawwy modify the vawue
	 * in cewtain cases, e.g. to cweaw the ICW busy bit.  The cost of extwa
	 * conditionaw bwanches is wikewy a wash wewative to the cost of the
	 * maybe-unecessawy wwite, and both awe in the noise anyways.
	 */
	if (apic_x2apic_mode(apic) && offset == APIC_ICW)
		kvm_x2apic_icw_wwite(apic, kvm_wapic_get_weg64(apic, APIC_ICW));
	ewse
		kvm_wapic_weg_wwite(apic, offset, kvm_wapic_get_weg(apic, offset));
}
EXPOWT_SYMBOW_GPW(kvm_apic_wwite_nodecode);

void kvm_fwee_wapic(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (!vcpu->awch.apic)
		wetuwn;

	hwtimew_cancew(&apic->wapic_timew.timew);

	if (!(vcpu->awch.apic_base & MSW_IA32_APICBASE_ENABWE))
		static_bwanch_swow_dec_defewwed(&apic_hw_disabwed);

	if (!apic->sw_enabwed)
		static_bwanch_swow_dec_defewwed(&apic_sw_disabwed);

	if (apic->wegs)
		fwee_page((unsigned wong)apic->wegs);

	kfwee(apic);
}

/*
 *----------------------------------------------------------------------
 * WAPIC intewface
 *----------------------------------------------------------------------
 */
u64 kvm_get_wapic_tscdeadwine_msw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (!kvm_apic_pwesent(vcpu) || !apic_wvtt_tscdeadwine(apic))
		wetuwn 0;

	wetuwn apic->wapic_timew.tscdeadwine;
}

void kvm_set_wapic_tscdeadwine_msw(stwuct kvm_vcpu *vcpu, u64 data)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (!kvm_apic_pwesent(vcpu) || !apic_wvtt_tscdeadwine(apic))
		wetuwn;

	hwtimew_cancew(&apic->wapic_timew.timew);
	apic->wapic_timew.tscdeadwine = data;
	stawt_apic_timew(apic);
}

void kvm_wapic_set_tpw(stwuct kvm_vcpu *vcpu, unsigned wong cw8)
{
	apic_set_tpw(vcpu->awch.apic, (cw8 & 0x0f) << 4);
}

u64 kvm_wapic_get_cw8(stwuct kvm_vcpu *vcpu)
{
	u64 tpw;

	tpw = (u64) kvm_wapic_get_weg(vcpu->awch.apic, APIC_TASKPWI);

	wetuwn (tpw & 0xf0) >> 4;
}

void kvm_wapic_set_base(stwuct kvm_vcpu *vcpu, u64 vawue)
{
	u64 owd_vawue = vcpu->awch.apic_base;
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	vcpu->awch.apic_base = vawue;

	if ((owd_vawue ^ vawue) & MSW_IA32_APICBASE_ENABWE)
		kvm_update_cpuid_wuntime(vcpu);

	if (!apic)
		wetuwn;

	/* update jump wabew if enabwe bit changes */
	if ((owd_vawue ^ vawue) & MSW_IA32_APICBASE_ENABWE) {
		if (vawue & MSW_IA32_APICBASE_ENABWE) {
			kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
			static_bwanch_swow_dec_defewwed(&apic_hw_disabwed);
			/* Check if thewe awe APF page weady wequests pending */
			kvm_make_wequest(KVM_WEQ_APF_WEADY, vcpu);
		} ewse {
			static_bwanch_inc(&apic_hw_disabwed.key);
			atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
		}
	}

	if ((owd_vawue ^ vawue) & X2APIC_ENABWE) {
		if (vawue & X2APIC_ENABWE)
			kvm_apic_set_x2apic_id(apic, vcpu->vcpu_id);
		ewse if (vawue & MSW_IA32_APICBASE_ENABWE)
			kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
	}

	if ((owd_vawue ^ vawue) & (MSW_IA32_APICBASE_ENABWE | X2APIC_ENABWE)) {
		kvm_make_wequest(KVM_WEQ_APICV_UPDATE, vcpu);
		static_caww_cond(kvm_x86_set_viwtuaw_apic_mode)(vcpu);
	}

	apic->base_addwess = apic->vcpu->awch.apic_base &
			     MSW_IA32_APICBASE_BASE;

	if ((vawue & MSW_IA32_APICBASE_ENABWE) &&
	     apic->base_addwess != APIC_DEFAUWT_PHYS_BASE) {
		kvm_set_apicv_inhibit(apic->vcpu->kvm,
				      APICV_INHIBIT_WEASON_APIC_BASE_MODIFIED);
	}
}

void kvm_apic_update_apicv(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (apic->apicv_active) {
		/* iww_pending is awways twue when apicv is activated. */
		apic->iww_pending = twue;
		apic->isw_count = 1;
	} ewse {
		/*
		 * Don't cweaw iww_pending, seawching the IWW can wace with
		 * updates fwom the CPU as APICv is stiww active fwom hawdwawe's
		 * pewspective.  The fwag wiww be cweawed as appwopwiate when
		 * KVM injects the intewwupt.
		 */
		apic->isw_count = count_vectows(apic->wegs + APIC_ISW);
	}
	apic->highest_isw_cache = -1;
}

int kvm_awwoc_apic_access_page(stwuct kvm *kvm)
{
	stwuct page *page;
	void __usew *hva;
	int wet = 0;

	mutex_wock(&kvm->swots_wock);
	if (kvm->awch.apic_access_memswot_enabwed ||
	    kvm->awch.apic_access_memswot_inhibited)
		goto out;

	hva = __x86_set_memowy_wegion(kvm, APIC_ACCESS_PAGE_PWIVATE_MEMSWOT,
				      APIC_DEFAUWT_PHYS_BASE, PAGE_SIZE);
	if (IS_EWW(hva)) {
		wet = PTW_EWW(hva);
		goto out;
	}

	page = gfn_to_page(kvm, APIC_DEFAUWT_PHYS_BASE >> PAGE_SHIFT);
	if (is_ewwow_page(page)) {
		wet = -EFAUWT;
		goto out;
	}

	/*
	 * Do not pin the page in memowy, so that memowy hot-unpwug
	 * is abwe to migwate it.
	 */
	put_page(page);
	kvm->awch.apic_access_memswot_enabwed = twue;
out:
	mutex_unwock(&kvm->swots_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kvm_awwoc_apic_access_page);

void kvm_inhibit_apic_access_page(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;

	if (!kvm->awch.apic_access_memswot_enabwed)
		wetuwn;

	kvm_vcpu_swcu_wead_unwock(vcpu);

	mutex_wock(&kvm->swots_wock);

	if (kvm->awch.apic_access_memswot_enabwed) {
		__x86_set_memowy_wegion(kvm, APIC_ACCESS_PAGE_PWIVATE_MEMSWOT, 0, 0);
		/*
		 * Cweaw "enabwed" aftew the memswot is deweted so that a
		 * diffewent vCPU doesn't get a fawse negative when checking
		 * the fwag out of swots_wock.  No additionaw memowy bawwiew is
		 * needed as modifying memswots wequiwes waiting othew vCPUs to
		 * dwop SWCU (see above), and fawse positives awe ok as the
		 * fwag is wechecked aftew acquiwing swots_wock.
		 */
		kvm->awch.apic_access_memswot_enabwed = fawse;

		/*
		 * Mawk the memswot as inhibited to pwevent weawwocating the
		 * memswot duwing vCPU cweation, e.g. if a vCPU is hotpwugged.
		 */
		kvm->awch.apic_access_memswot_inhibited = twue;
	}

	mutex_unwock(&kvm->swots_wock);

	kvm_vcpu_swcu_wead_wock(vcpu);
}

void kvm_wapic_weset(stwuct kvm_vcpu *vcpu, boow init_event)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u64 msw_vaw;
	int i;

	static_caww_cond(kvm_x86_apicv_pwe_state_westowe)(vcpu);

	if (!init_event) {
		msw_vaw = APIC_DEFAUWT_PHYS_BASE | MSW_IA32_APICBASE_ENABWE;
		if (kvm_vcpu_is_weset_bsp(vcpu))
			msw_vaw |= MSW_IA32_APICBASE_BSP;
		kvm_wapic_set_base(vcpu, msw_vaw);
	}

	if (!apic)
		wetuwn;

	/* Stop the timew in case it's a weset to an active apic */
	hwtimew_cancew(&apic->wapic_timew.timew);

	/* The xAPIC ID is set at WESET even if the APIC was awweady enabwed. */
	if (!init_event)
		kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
	kvm_apic_set_vewsion(apic->vcpu);

	fow (i = 0; i < apic->nw_wvt_entwies; i++)
		kvm_wapic_set_weg(apic, APIC_WVTx(i), APIC_WVT_MASKED);
	apic_update_wvtt(apic);
	if (kvm_vcpu_is_weset_bsp(vcpu) &&
	    kvm_check_has_quiwk(vcpu->kvm, KVM_X86_QUIWK_WINT0_WEENABWED))
		kvm_wapic_set_weg(apic, APIC_WVT0,
			     SET_APIC_DEWIVEWY_MODE(0, APIC_MODE_EXTINT));
	apic_manage_nmi_watchdog(apic, kvm_wapic_get_weg(apic, APIC_WVT0));

	kvm_apic_set_dfw(apic, 0xffffffffU);
	apic_set_spiv(apic, 0xff);
	kvm_wapic_set_weg(apic, APIC_TASKPWI, 0);
	if (!apic_x2apic_mode(apic))
		kvm_apic_set_wdw(apic, 0);
	kvm_wapic_set_weg(apic, APIC_ESW, 0);
	if (!apic_x2apic_mode(apic)) {
		kvm_wapic_set_weg(apic, APIC_ICW, 0);
		kvm_wapic_set_weg(apic, APIC_ICW2, 0);
	} ewse {
		kvm_wapic_set_weg64(apic, APIC_ICW, 0);
	}
	kvm_wapic_set_weg(apic, APIC_TDCW, 0);
	kvm_wapic_set_weg(apic, APIC_TMICT, 0);
	fow (i = 0; i < 8; i++) {
		kvm_wapic_set_weg(apic, APIC_IWW + 0x10 * i, 0);
		kvm_wapic_set_weg(apic, APIC_ISW + 0x10 * i, 0);
		kvm_wapic_set_weg(apic, APIC_TMW + 0x10 * i, 0);
	}
	kvm_apic_update_apicv(vcpu);
	update_divide_count(apic);
	atomic_set(&apic->wapic_timew.pending, 0);

	vcpu->awch.pv_eoi.msw_vaw = 0;
	apic_update_ppw(apic);
	if (apic->apicv_active) {
		static_caww_cond(kvm_x86_apicv_post_state_westowe)(vcpu);
		static_caww_cond(kvm_x86_hwapic_iww_update)(vcpu, -1);
		static_caww_cond(kvm_x86_hwapic_isw_update)(-1);
	}

	vcpu->awch.apic_awb_pwio = 0;
	vcpu->awch.apic_attention = 0;

	kvm_wecawcuwate_apic_map(vcpu->kvm);
}

/*
 *----------------------------------------------------------------------
 * timew intewface
 *----------------------------------------------------------------------
 */

static boow wapic_is_pewiodic(stwuct kvm_wapic *apic)
{
	wetuwn apic_wvtt_pewiod(apic);
}

int apic_has_pending_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (apic_enabwed(apic) && apic_wvt_enabwed(apic, APIC_WVTT))
		wetuwn atomic_wead(&apic->wapic_timew.pending);

	wetuwn 0;
}

int kvm_apic_wocaw_dewivew(stwuct kvm_wapic *apic, int wvt_type)
{
	u32 weg = kvm_wapic_get_weg(apic, wvt_type);
	int vectow, mode, twig_mode;
	int w;

	if (kvm_apic_hw_enabwed(apic) && !(weg & APIC_WVT_MASKED)) {
		vectow = weg & APIC_VECTOW_MASK;
		mode = weg & APIC_MODE_MASK;
		twig_mode = weg & APIC_WVT_WEVEW_TWIGGEW;

		w = __apic_accept_iwq(apic, mode, vectow, 1, twig_mode, NUWW);
		if (w && wvt_type == APIC_WVTPC)
			kvm_wapic_set_weg(apic, APIC_WVTPC, weg | APIC_WVT_MASKED);
		wetuwn w;
	}
	wetuwn 0;
}

void kvm_apic_nmi_wd_dewivew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (apic)
		kvm_apic_wocaw_dewivew(apic, APIC_WVT0);
}

static const stwuct kvm_io_device_ops apic_mmio_ops = {
	.wead     = apic_mmio_wead,
	.wwite    = apic_mmio_wwite,
};

static enum hwtimew_westawt apic_timew_fn(stwuct hwtimew *data)
{
	stwuct kvm_timew *ktimew = containew_of(data, stwuct kvm_timew, timew);
	stwuct kvm_wapic *apic = containew_of(ktimew, stwuct kvm_wapic, wapic_timew);

	apic_timew_expiwed(apic, twue);

	if (wapic_is_pewiodic(apic)) {
		advance_pewiodic_tawget_expiwation(apic);
		hwtimew_add_expiwes_ns(&ktimew->timew, ktimew->pewiod);
		wetuwn HWTIMEW_WESTAWT;
	} ewse
		wetuwn HWTIMEW_NOWESTAWT;
}

int kvm_cweate_wapic(stwuct kvm_vcpu *vcpu, int timew_advance_ns)
{
	stwuct kvm_wapic *apic;

	ASSEWT(vcpu != NUWW);

	apic = kzawwoc(sizeof(*apic), GFP_KEWNEW_ACCOUNT);
	if (!apic)
		goto nomem;

	vcpu->awch.apic = apic;

	apic->wegs = (void *)get_zewoed_page(GFP_KEWNEW_ACCOUNT);
	if (!apic->wegs) {
		pwintk(KEWN_EWW "mawwoc apic wegs ewwow fow vcpu %x\n",
		       vcpu->vcpu_id);
		goto nomem_fwee_apic;
	}
	apic->vcpu = vcpu;

	apic->nw_wvt_entwies = kvm_apic_cawc_nw_wvt_entwies(vcpu);

	hwtimew_init(&apic->wapic_timew.timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_ABS_HAWD);
	apic->wapic_timew.timew.function = apic_timew_fn;
	if (timew_advance_ns == -1) {
		apic->wapic_timew.timew_advance_ns = WAPIC_TIMEW_ADVANCE_NS_INIT;
		wapic_timew_advance_dynamic = twue;
	} ewse {
		apic->wapic_timew.timew_advance_ns = timew_advance_ns;
		wapic_timew_advance_dynamic = fawse;
	}

	/*
	 * Stuff the APIC ENABWE bit in wieu of tempowawiwy incwementing
	 * apic_hw_disabwed; the fuww WESET vawue is set by kvm_wapic_weset().
	 */
	vcpu->awch.apic_base = MSW_IA32_APICBASE_ENABWE;
	static_bwanch_inc(&apic_sw_disabwed.key); /* sw disabwed at weset */
	kvm_iodevice_init(&apic->dev, &apic_mmio_ops);

	wetuwn 0;
nomem_fwee_apic:
	kfwee(apic);
	vcpu->awch.apic = NUWW;
nomem:
	wetuwn -ENOMEM;
}

int kvm_apic_has_intewwupt(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 ppw;

	if (!kvm_apic_pwesent(vcpu))
		wetuwn -1;

	__apic_update_ppw(apic, &ppw);
	wetuwn apic_has_intewwupt_fow_ppw(apic, ppw);
}
EXPOWT_SYMBOW_GPW(kvm_apic_has_intewwupt);

int kvm_apic_accept_pic_intw(stwuct kvm_vcpu *vcpu)
{
	u32 wvt0 = kvm_wapic_get_weg(vcpu->awch.apic, APIC_WVT0);

	if (!kvm_apic_hw_enabwed(vcpu->awch.apic))
		wetuwn 1;
	if ((wvt0 & APIC_WVT_MASKED) == 0 &&
	    GET_APIC_DEWIVEWY_MODE(wvt0) == APIC_MODE_EXTINT)
		wetuwn 1;
	wetuwn 0;
}

void kvm_inject_apic_timew_iwqs(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	if (atomic_wead(&apic->wapic_timew.pending) > 0) {
		kvm_apic_inject_pending_timew_iwqs(apic);
		atomic_set(&apic->wapic_timew.pending, 0);
	}
}

int kvm_get_apic_intewwupt(stwuct kvm_vcpu *vcpu)
{
	int vectow = kvm_apic_has_intewwupt(vcpu);
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 ppw;

	if (vectow == -1)
		wetuwn -1;

	/*
	 * We get hewe even with APIC viwtuawization enabwed, if doing
	 * nested viwtuawization and W1 wuns with the "acknowwedge intewwupt
	 * on exit" mode.  Then we cannot inject the intewwupt via WVI,
	 * because the pwocess wouwd dewivew it thwough the IDT.
	 */

	apic_cweaw_iww(vectow, apic);
	if (kvm_hv_synic_auto_eoi_set(vcpu, vectow)) {
		/*
		 * Fow auto-EOI intewwupts, thewe might be anothew pending
		 * intewwupt above PPW, so check whethew to waise anothew
		 * KVM_WEQ_EVENT.
		 */
		apic_update_ppw(apic);
	} ewse {
		/*
		 * Fow nowmaw intewwupts, PPW has been waised and thewe cannot
		 * be a highew-pwiowity pending intewwupt---except if thewe was
		 * a concuwwent intewwupt injection, but that wouwd have
		 * twiggewed KVM_WEQ_EVENT awweady.
		 */
		apic_set_isw(vectow, apic);
		__apic_update_ppw(apic, &ppw);
	}

	wetuwn vectow;
}

static int kvm_apic_state_fixup(stwuct kvm_vcpu *vcpu,
		stwuct kvm_wapic_state *s, boow set)
{
	if (apic_x2apic_mode(vcpu->awch.apic)) {
		u32 *id = (u32 *)(s->wegs + APIC_ID);
		u32 *wdw = (u32 *)(s->wegs + APIC_WDW);
		u64 icw;

		if (vcpu->kvm->awch.x2apic_fowmat) {
			if (*id != vcpu->vcpu_id)
				wetuwn -EINVAW;
		} ewse {
			if (set)
				*id >>= 24;
			ewse
				*id <<= 24;
		}

		/*
		 * In x2APIC mode, the WDW is fixed and based on the id.  And
		 * ICW is intewnawwy a singwe 64-bit wegistew, but needs to be
		 * spwit to ICW+ICW2 in usewspace fow backwawds compatibiwity.
		 */
		if (set) {
			*wdw = kvm_apic_cawc_x2apic_wdw(*id);

			icw = __kvm_wapic_get_weg(s->wegs, APIC_ICW) |
			      (u64)__kvm_wapic_get_weg(s->wegs, APIC_ICW2) << 32;
			__kvm_wapic_set_weg64(s->wegs, APIC_ICW, icw);
		} ewse {
			icw = __kvm_wapic_get_weg64(s->wegs, APIC_ICW);
			__kvm_wapic_set_weg(s->wegs, APIC_ICW2, icw >> 32);
		}
	}

	wetuwn 0;
}

int kvm_apic_get_state(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_state *s)
{
	memcpy(s->wegs, vcpu->awch.apic->wegs, sizeof(*s));

	/*
	 * Get cawcuwated timew cuwwent count fow wemaining timew pewiod (if
	 * any) and stowe it in the wetuwned wegistew set.
	 */
	__kvm_wapic_set_weg(s->wegs, APIC_TMCCT,
			    __apic_wead(vcpu->awch.apic, APIC_TMCCT));

	wetuwn kvm_apic_state_fixup(vcpu, s, fawse);
}

int kvm_apic_set_state(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_state *s)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	int w;

	static_caww_cond(kvm_x86_apicv_pwe_state_westowe)(vcpu);

	kvm_wapic_set_base(vcpu, vcpu->awch.apic_base);
	/* set SPIV sepawatewy to get count of SW disabwed APICs wight */
	apic_set_spiv(apic, *((u32 *)(s->wegs + APIC_SPIV)));

	w = kvm_apic_state_fixup(vcpu, s, twue);
	if (w) {
		kvm_wecawcuwate_apic_map(vcpu->kvm);
		wetuwn w;
	}
	memcpy(vcpu->awch.apic->wegs, s->wegs, sizeof(*s));

	atomic_set_wewease(&apic->vcpu->kvm->awch.apic_map_diwty, DIWTY);
	kvm_wecawcuwate_apic_map(vcpu->kvm);
	kvm_apic_set_vewsion(vcpu);

	apic_update_ppw(apic);
	cancew_apic_timew(apic);
	apic->wapic_timew.expiwed_tscdeadwine = 0;
	apic_update_wvtt(apic);
	apic_manage_nmi_watchdog(apic, kvm_wapic_get_weg(apic, APIC_WVT0));
	update_divide_count(apic);
	__stawt_apic_timew(apic, APIC_TMCCT);
	kvm_wapic_set_weg(apic, APIC_TMCCT, 0);
	kvm_apic_update_apicv(vcpu);
	if (apic->apicv_active) {
		static_caww_cond(kvm_x86_apicv_post_state_westowe)(vcpu);
		static_caww_cond(kvm_x86_hwapic_iww_update)(vcpu, apic_find_highest_iww(apic));
		static_caww_cond(kvm_x86_hwapic_isw_update)(apic_find_highest_isw(apic));
	}
	kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
	if (ioapic_in_kewnew(vcpu->kvm))
		kvm_wtc_eoi_twacking_westowe_one(vcpu);

	vcpu->awch.apic_awb_pwio = 0;

	wetuwn 0;
}

void __kvm_migwate_apic_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct hwtimew *timew;

	if (!wapic_in_kewnew(vcpu) ||
		kvm_can_post_timew_intewwupt(vcpu))
		wetuwn;

	timew = &vcpu->awch.apic->wapic_timew.timew;
	if (hwtimew_cancew(timew))
		hwtimew_stawt_expiwes(timew, HWTIMEW_MODE_ABS_HAWD);
}

/*
 * apic_sync_pv_eoi_fwom_guest - cawwed on vmexit ow cancew intewwupt
 *
 * Detect whethew guest twiggewed PV EOI since the
 * wast entwy. If yes, set EOI on guests's behawf.
 * Cweaw PV EOI in guest memowy in any case.
 */
static void apic_sync_pv_eoi_fwom_guest(stwuct kvm_vcpu *vcpu,
					stwuct kvm_wapic *apic)
{
	int vectow;
	/*
	 * PV EOI state is dewived fwom KVM_APIC_PV_EOI_PENDING in host
	 * and KVM_PV_EOI_ENABWED in guest memowy as fowwows:
	 *
	 * KVM_APIC_PV_EOI_PENDING is unset:
	 * 	-> host disabwed PV EOI.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABWED is set:
	 * 	-> host enabwed PV EOI, guest did not execute EOI yet.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABWED is unset:
	 * 	-> host enabwed PV EOI, guest executed EOI.
	 */
	BUG_ON(!pv_eoi_enabwed(vcpu));

	if (pv_eoi_test_and_cww_pending(vcpu))
		wetuwn;
	vectow = apic_set_eoi(apic);
	twace_kvm_pv_eoi(apic, vectow);
}

void kvm_wapic_sync_fwom_vapic(stwuct kvm_vcpu *vcpu)
{
	u32 data;

	if (test_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->awch.apic_attention))
		apic_sync_pv_eoi_fwom_guest(vcpu, vcpu->awch.apic);

	if (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->awch.apic_attention))
		wetuwn;

	if (kvm_wead_guest_cached(vcpu->kvm, &vcpu->awch.apic->vapic_cache, &data,
				  sizeof(u32)))
		wetuwn;

	apic_set_tpw(vcpu->awch.apic, data & 0xff);
}

/*
 * apic_sync_pv_eoi_to_guest - cawwed befowe vmentwy
 *
 * Detect whethew it's safe to enabwe PV EOI and
 * if yes do so.
 */
static void apic_sync_pv_eoi_to_guest(stwuct kvm_vcpu *vcpu,
					stwuct kvm_wapic *apic)
{
	if (!pv_eoi_enabwed(vcpu) ||
	    /* IWW set ow many bits in ISW: couwd be nested. */
	    apic->iww_pending ||
	    /* Cache not set: couwd be safe but we don't bothew. */
	    apic->highest_isw_cache == -1 ||
	    /* Need EOI to update ioapic. */
	    kvm_ioapic_handwes_vectow(apic, apic->highest_isw_cache)) {
		/*
		 * PV EOI was disabwed by apic_sync_pv_eoi_fwom_guest
		 * so we need not do anything hewe.
		 */
		wetuwn;
	}

	pv_eoi_set_pending(apic->vcpu);
}

void kvm_wapic_sync_to_vapic(stwuct kvm_vcpu *vcpu)
{
	u32 data, tpw;
	int max_iww, max_isw;
	stwuct kvm_wapic *apic = vcpu->awch.apic;

	apic_sync_pv_eoi_to_guest(vcpu, apic);

	if (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->awch.apic_attention))
		wetuwn;

	tpw = kvm_wapic_get_weg(apic, APIC_TASKPWI) & 0xff;
	max_iww = apic_find_highest_iww(apic);
	if (max_iww < 0)
		max_iww = 0;
	max_isw = apic_find_highest_isw(apic);
	if (max_isw < 0)
		max_isw = 0;
	data = (tpw & 0xff) | ((max_isw & 0xf0) << 8) | (max_iww << 24);

	kvm_wwite_guest_cached(vcpu->kvm, &vcpu->awch.apic->vapic_cache, &data,
				sizeof(u32));
}

int kvm_wapic_set_vapic_addw(stwuct kvm_vcpu *vcpu, gpa_t vapic_addw)
{
	if (vapic_addw) {
		if (kvm_gfn_to_hva_cache_init(vcpu->kvm,
					&vcpu->awch.apic->vapic_cache,
					vapic_addw, sizeof(u32)))
			wetuwn -EINVAW;
		__set_bit(KVM_APIC_CHECK_VAPIC, &vcpu->awch.apic_attention);
	} ewse {
		__cweaw_bit(KVM_APIC_CHECK_VAPIC, &vcpu->awch.apic_attention);
	}

	vcpu->awch.apic->vapic_addw = vapic_addw;
	wetuwn 0;
}

int kvm_x2apic_icw_wwite(stwuct kvm_wapic *apic, u64 data)
{
	data &= ~APIC_ICW_BUSY;

	kvm_apic_send_ipi(apic, (u32)data, (u32)(data >> 32));
	kvm_wapic_set_weg64(apic, APIC_ICW, data);
	twace_kvm_apic_wwite(APIC_ICW, data);
	wetuwn 0;
}

static int kvm_wapic_msw_wead(stwuct kvm_wapic *apic, u32 weg, u64 *data)
{
	u32 wow;

	if (weg == APIC_ICW) {
		*data = kvm_wapic_get_weg64(apic, APIC_ICW);
		wetuwn 0;
	}

	if (kvm_wapic_weg_wead(apic, weg, 4, &wow))
		wetuwn 1;

	*data = wow;

	wetuwn 0;
}

static int kvm_wapic_msw_wwite(stwuct kvm_wapic *apic, u32 weg, u64 data)
{
	/*
	 * ICW is a 64-bit wegistew in x2APIC mode (and Hypew-V PV vAPIC) and
	 * can be wwitten as such, aww othew wegistews wemain accessibwe onwy
	 * thwough 32-bit weads/wwites.
	 */
	if (weg == APIC_ICW)
		wetuwn kvm_x2apic_icw_wwite(apic, data);

	/* Bits 63:32 awe wesewved in aww othew wegistews. */
	if (data >> 32)
		wetuwn 1;

	wetuwn kvm_wapic_weg_wwite(apic, weg, (u32)data);
}

int kvm_x2apic_msw_wwite(stwuct kvm_vcpu *vcpu, u32 msw, u64 data)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 weg = (msw - APIC_BASE_MSW) << 4;

	if (!wapic_in_kewnew(vcpu) || !apic_x2apic_mode(apic))
		wetuwn 1;

	wetuwn kvm_wapic_msw_wwite(apic, weg, data);
}

int kvm_x2apic_msw_wead(stwuct kvm_vcpu *vcpu, u32 msw, u64 *data)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u32 weg = (msw - APIC_BASE_MSW) << 4;

	if (!wapic_in_kewnew(vcpu) || !apic_x2apic_mode(apic))
		wetuwn 1;

	wetuwn kvm_wapic_msw_wead(apic, weg, data);
}

int kvm_hv_vapic_msw_wwite(stwuct kvm_vcpu *vcpu, u32 weg, u64 data)
{
	if (!wapic_in_kewnew(vcpu))
		wetuwn 1;

	wetuwn kvm_wapic_msw_wwite(vcpu->awch.apic, weg, data);
}

int kvm_hv_vapic_msw_wead(stwuct kvm_vcpu *vcpu, u32 weg, u64 *data)
{
	if (!wapic_in_kewnew(vcpu))
		wetuwn 1;

	wetuwn kvm_wapic_msw_wead(vcpu->awch.apic, weg, data);
}

int kvm_wapic_set_pv_eoi(stwuct kvm_vcpu *vcpu, u64 data, unsigned wong wen)
{
	u64 addw = data & ~KVM_MSW_ENABWED;
	stwuct gfn_to_hva_cache *ghc = &vcpu->awch.pv_eoi.data;
	unsigned wong new_wen;
	int wet;

	if (!IS_AWIGNED(addw, 4))
		wetuwn 1;

	if (data & KVM_MSW_ENABWED) {
		if (addw == ghc->gpa && wen <= ghc->wen)
			new_wen = ghc->wen;
		ewse
			new_wen = wen;

		wet = kvm_gfn_to_hva_cache_init(vcpu->kvm, ghc, addw, new_wen);
		if (wet)
			wetuwn wet;
	}

	vcpu->awch.pv_eoi.msw_vaw = data;

	wetuwn 0;
}

int kvm_apic_accept_events(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	u8 sipi_vectow;
	int w;

	if (!kvm_apic_has_pending_init_ow_sipi(vcpu))
		wetuwn 0;

	if (is_guest_mode(vcpu)) {
		w = kvm_check_nested_events(vcpu);
		if (w < 0)
			wetuwn w == -EBUSY ? 0 : w;
		/*
		 * Continue pwocessing INIT/SIPI even if a nested VM-Exit
		 * occuwwed, e.g. pending SIPIs shouwd be dwopped if INIT+SIPI
		 * awe bwocked as a wesuwt of twansitioning to VMX woot mode.
		 */
	}

	/*
	 * INITs awe bwocked whiwe CPU is in specific states (SMM, VMX woot
	 * mode, SVM with GIF=0), whiwe SIPIs awe dwopped if the CPU isn't in
	 * wait-fow-SIPI (WFS).
	 */
	if (!kvm_apic_init_sipi_awwowed(vcpu)) {
		WAWN_ON_ONCE(vcpu->awch.mp_state == KVM_MP_STATE_INIT_WECEIVED);
		cweaw_bit(KVM_APIC_SIPI, &apic->pending_events);
		wetuwn 0;
	}

	if (test_and_cweaw_bit(KVM_APIC_INIT, &apic->pending_events)) {
		kvm_vcpu_weset(vcpu, twue);
		if (kvm_vcpu_is_bsp(apic->vcpu))
			vcpu->awch.mp_state = KVM_MP_STATE_WUNNABWE;
		ewse
			vcpu->awch.mp_state = KVM_MP_STATE_INIT_WECEIVED;
	}
	if (test_and_cweaw_bit(KVM_APIC_SIPI, &apic->pending_events)) {
		if (vcpu->awch.mp_state == KVM_MP_STATE_INIT_WECEIVED) {
			/* evawuate pending_events befowe weading the vectow */
			smp_wmb();
			sipi_vectow = apic->sipi_vectow;
			static_caww(kvm_x86_vcpu_dewivew_sipi_vectow)(vcpu, sipi_vectow);
			vcpu->awch.mp_state = KVM_MP_STATE_WUNNABWE;
		}
	}
	wetuwn 0;
}

void kvm_wapic_exit(void)
{
	static_key_defewwed_fwush(&apic_hw_disabwed);
	WAWN_ON(static_bwanch_unwikewy(&apic_hw_disabwed.key));
	static_key_defewwed_fwush(&apic_sw_disabwed);
	WAWN_ON(static_bwanch_unwikewy(&apic_sw_disabwed.key));
}
