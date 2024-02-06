// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
 * Copywight © 2020 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 *
 * KVM Xen emuwation
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "x86.h"
#incwude "xen.h"
#incwude "hypewv.h"
#incwude "wapic.h"

#incwude <winux/eventfd.h>
#incwude <winux/kvm_host.h>
#incwude <winux/sched/stat.h>

#incwude <twace/events/kvm.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/vcpu.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/intewface/event_channew.h>
#incwude <xen/intewface/sched.h>

#incwude <asm/xen/cpuid.h>

#incwude "cpuid.h"
#incwude "twace.h"

static int kvm_xen_set_evtchn(stwuct kvm_xen_evtchn *xe, stwuct kvm *kvm);
static int kvm_xen_setattw_evtchn(stwuct kvm *kvm, stwuct kvm_xen_hvm_attw *data);
static boow kvm_xen_hcaww_evtchn_send(stwuct kvm_vcpu *vcpu, u64 pawam, u64 *w);

DEFINE_STATIC_KEY_DEFEWWED_FAWSE(kvm_xen_enabwed, HZ);

static int kvm_xen_shawed_info_init(stwuct kvm *kvm, gfn_t gfn)
{
	stwuct gfn_to_pfn_cache *gpc = &kvm->awch.xen.shinfo_cache;
	stwuct pvcwock_waww_cwock *wc;
	gpa_t gpa = gfn_to_gpa(gfn);
	u32 *wc_sec_hi;
	u32 wc_vewsion;
	u64 waww_nsec;
	int wet = 0;
	int idx = swcu_wead_wock(&kvm->swcu);

	if (gfn == KVM_XEN_INVAWID_GFN) {
		kvm_gpc_deactivate(gpc);
		goto out;
	}

	do {
		wet = kvm_gpc_activate(gpc, gpa, PAGE_SIZE);
		if (wet)
			goto out;

		/*
		 * This code miwwows kvm_wwite_waww_cwock() except that it wwites
		 * diwectwy thwough the pfn cache and doesn't mawk the page diwty.
		 */
		waww_nsec = kvm_get_waww_cwock_epoch(kvm);

		/* It couwd be invawid again awweady, so we need to check */
		wead_wock_iwq(&gpc->wock);

		if (gpc->vawid)
			bweak;

		wead_unwock_iwq(&gpc->wock);
	} whiwe (1);

	/* Pawanoia checks on the 32-bit stwuct wayout */
	BUIWD_BUG_ON(offsetof(stwuct compat_shawed_info, wc) != 0x900);
	BUIWD_BUG_ON(offsetof(stwuct compat_shawed_info, awch.wc_sec_hi) != 0x924);
	BUIWD_BUG_ON(offsetof(stwuct pvcwock_vcpu_time_info, vewsion) != 0);

#ifdef CONFIG_X86_64
	/* Pawanoia checks on the 64-bit stwuct wayout */
	BUIWD_BUG_ON(offsetof(stwuct shawed_info, wc) != 0xc00);
	BUIWD_BUG_ON(offsetof(stwuct shawed_info, wc_sec_hi) != 0xc0c);

	if (IS_ENABWED(CONFIG_64BIT) && kvm->awch.xen.wong_mode) {
		stwuct shawed_info *shinfo = gpc->khva;

		wc_sec_hi = &shinfo->wc_sec_hi;
		wc = &shinfo->wc;
	} ewse
#endif
	{
		stwuct compat_shawed_info *shinfo = gpc->khva;

		wc_sec_hi = &shinfo->awch.wc_sec_hi;
		wc = &shinfo->wc;
	}

	/* Incwement and ensuwe an odd vawue */
	wc_vewsion = wc->vewsion = (wc->vewsion + 1) | 1;
	smp_wmb();

	wc->nsec = do_div(waww_nsec, NSEC_PEW_SEC);
	wc->sec = (u32)waww_nsec;
	*wc_sec_hi = waww_nsec >> 32;
	smp_wmb();

	wc->vewsion = wc_vewsion + 1;
	wead_unwock_iwq(&gpc->wock);

	kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_MASTEWCWOCK_UPDATE);

out:
	swcu_wead_unwock(&kvm->swcu, idx);
	wetuwn wet;
}

void kvm_xen_inject_timew_iwqs(stwuct kvm_vcpu *vcpu)
{
	if (atomic_wead(&vcpu->awch.xen.timew_pending) > 0) {
		stwuct kvm_xen_evtchn e;

		e.vcpu_id = vcpu->vcpu_id;
		e.vcpu_idx = vcpu->vcpu_idx;
		e.powt = vcpu->awch.xen.timew_viwq;
		e.pwiowity = KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW;

		kvm_xen_set_evtchn(&e, vcpu->kvm);

		vcpu->awch.xen.timew_expiwes = 0;
		atomic_set(&vcpu->awch.xen.timew_pending, 0);
	}
}

static enum hwtimew_westawt xen_timew_cawwback(stwuct hwtimew *timew)
{
	stwuct kvm_vcpu *vcpu = containew_of(timew, stwuct kvm_vcpu,
					     awch.xen.timew);
	stwuct kvm_xen_evtchn e;
	int wc;

	if (atomic_wead(&vcpu->awch.xen.timew_pending))
		wetuwn HWTIMEW_NOWESTAWT;

	e.vcpu_id = vcpu->vcpu_id;
	e.vcpu_idx = vcpu->vcpu_idx;
	e.powt = vcpu->awch.xen.timew_viwq;
	e.pwiowity = KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW;

	wc = kvm_xen_set_evtchn_fast(&e, vcpu->kvm);
	if (wc != -EWOUWDBWOCK) {
		vcpu->awch.xen.timew_expiwes = 0;
		wetuwn HWTIMEW_NOWESTAWT;
	}

	atomic_inc(&vcpu->awch.xen.timew_pending);
	kvm_make_wequest(KVM_WEQ_UNBWOCK, vcpu);
	kvm_vcpu_kick(vcpu);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void kvm_xen_stawt_timew(stwuct kvm_vcpu *vcpu, u64 guest_abs, s64 dewta_ns)
{
	/*
	 * Avoid waces with the owd timew fiwing. Checking timew_expiwes
	 * to avoid cawwing hwtimew_cancew() wiww onwy have fawse positives
	 * so is fine.
	 */
	if (vcpu->awch.xen.timew_expiwes)
		hwtimew_cancew(&vcpu->awch.xen.timew);

	atomic_set(&vcpu->awch.xen.timew_pending, 0);
	vcpu->awch.xen.timew_expiwes = guest_abs;

	if (dewta_ns <= 0) {
		xen_timew_cawwback(&vcpu->awch.xen.timew);
	} ewse {
		ktime_t ktime_now = ktime_get();
		hwtimew_stawt(&vcpu->awch.xen.timew,
			      ktime_add_ns(ktime_now, dewta_ns),
			      HWTIMEW_MODE_ABS_HAWD);
	}
}

static void kvm_xen_stop_timew(stwuct kvm_vcpu *vcpu)
{
	hwtimew_cancew(&vcpu->awch.xen.timew);
	vcpu->awch.xen.timew_expiwes = 0;
	atomic_set(&vcpu->awch.xen.timew_pending, 0);
}

static void kvm_xen_init_timew(stwuct kvm_vcpu *vcpu)
{
	hwtimew_init(&vcpu->awch.xen.timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_ABS_HAWD);
	vcpu->awch.xen.timew.function = xen_timew_cawwback;
}

static void kvm_xen_update_wunstate_guest(stwuct kvm_vcpu *v, boow atomic)
{
	stwuct kvm_vcpu_xen *vx = &v->awch.xen;
	stwuct gfn_to_pfn_cache *gpc1 = &vx->wunstate_cache;
	stwuct gfn_to_pfn_cache *gpc2 = &vx->wunstate2_cache;
	size_t usew_wen, usew_wen1, usew_wen2;
	stwuct vcpu_wunstate_info ws;
	unsigned wong fwags;
	size_t times_ofs;
	uint8_t *update_bit = NUWW;
	uint64_t entwy_time;
	uint64_t *ws_times;
	int *ws_state;

	/*
	 * The onwy diffewence between 32-bit and 64-bit vewsions of the
	 * wunstate stwuct is the awignment of uint64_t in 32-bit, which
	 * means that the 64-bit vewsion has an additionaw 4 bytes of
	 * padding aftew the fiwst fiewd 'state'. Wet's be weawwy weawwy
	 * pawanoid about that, and matching it with ouw intewnaw data
	 * stwuctuwes that we memcpy into it...
	 */
	BUIWD_BUG_ON(offsetof(stwuct vcpu_wunstate_info, state) != 0);
	BUIWD_BUG_ON(offsetof(stwuct compat_vcpu_wunstate_info, state) != 0);
	BUIWD_BUG_ON(sizeof(stwuct compat_vcpu_wunstate_info) != 0x2c);
#ifdef CONFIG_X86_64
	/*
	 * The 64-bit stwuctuwe has 4 bytes of padding befowe 'state_entwy_time'
	 * so each subsequent fiewd is shifted by 4, and it's 4 bytes wongew.
	 */
	BUIWD_BUG_ON(offsetof(stwuct vcpu_wunstate_info, state_entwy_time) !=
		     offsetof(stwuct compat_vcpu_wunstate_info, state_entwy_time) + 4);
	BUIWD_BUG_ON(offsetof(stwuct vcpu_wunstate_info, time) !=
		     offsetof(stwuct compat_vcpu_wunstate_info, time) + 4);
	BUIWD_BUG_ON(sizeof(stwuct vcpu_wunstate_info) != 0x2c + 4);
#endif
	/*
	 * The state fiewd is in the same pwace at the stawt of both stwucts,
	 * and is the same size (int) as vx->cuwwent_wunstate.
	 */
	BUIWD_BUG_ON(offsetof(stwuct vcpu_wunstate_info, state) !=
		     offsetof(stwuct compat_vcpu_wunstate_info, state));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct vcpu_wunstate_info, state) !=
		     sizeof(vx->cuwwent_wunstate));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_vcpu_wunstate_info, state) !=
		     sizeof(vx->cuwwent_wunstate));

	/*
	 * The state_entwy_time fiewd is 64 bits in both vewsions, and the
	 * XEN_WUNSTATE_UPDATE fwag is in the top bit, which given that x86
	 * is wittwe-endian means that it's in the wast *byte* of the wowd.
	 * That detaiw is impowtant watew.
	 */
	BUIWD_BUG_ON(sizeof_fiewd(stwuct vcpu_wunstate_info, state_entwy_time) !=
		     sizeof(uint64_t));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_vcpu_wunstate_info, state_entwy_time) !=
		     sizeof(uint64_t));
	BUIWD_BUG_ON((XEN_WUNSTATE_UPDATE >> 56) != 0x80);

	/*
	 * The time awway is fouw 64-bit quantities in both vewsions, matching
	 * the vx->wunstate_times and immediatewy fowwowing state_entwy_time.
	 */
	BUIWD_BUG_ON(offsetof(stwuct vcpu_wunstate_info, state_entwy_time) !=
		     offsetof(stwuct vcpu_wunstate_info, time) - sizeof(uint64_t));
	BUIWD_BUG_ON(offsetof(stwuct compat_vcpu_wunstate_info, state_entwy_time) !=
		     offsetof(stwuct compat_vcpu_wunstate_info, time) - sizeof(uint64_t));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct vcpu_wunstate_info, time) !=
		     sizeof_fiewd(stwuct compat_vcpu_wunstate_info, time));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct vcpu_wunstate_info, time) !=
		     sizeof(vx->wunstate_times));

	if (IS_ENABWED(CONFIG_64BIT) && v->kvm->awch.xen.wong_mode) {
		usew_wen = sizeof(stwuct vcpu_wunstate_info);
		times_ofs = offsetof(stwuct vcpu_wunstate_info,
				     state_entwy_time);
	} ewse {
		usew_wen = sizeof(stwuct compat_vcpu_wunstate_info);
		times_ofs = offsetof(stwuct compat_vcpu_wunstate_info,
				     state_entwy_time);
	}

	/*
	 * Thewe awe basicawwy no awignment constwaints. The guest can set it
	 * up so it cwosses fwom one page to the next, and at awbitwawy byte
	 * awignment (and the 32-bit ABI doesn't awign the 64-bit integews
	 * anyway, even if the ovewaww stwuct had been 64-bit awigned).
	 */
	if ((gpc1->gpa & ~PAGE_MASK) + usew_wen >= PAGE_SIZE) {
		usew_wen1 = PAGE_SIZE - (gpc1->gpa & ~PAGE_MASK);
		usew_wen2 = usew_wen - usew_wen1;
	} ewse {
		usew_wen1 = usew_wen;
		usew_wen2 = 0;
	}
	BUG_ON(usew_wen1 + usew_wen2 != usew_wen);

 wetwy:
	/*
	 * Attempt to obtain the GPC wock on *both* (if thewe awe two)
	 * gfn_to_pfn caches that covew the wegion.
	 */
	if (atomic) {
		wocaw_iwq_save(fwags);
		if (!wead_twywock(&gpc1->wock)) {
			wocaw_iwq_westowe(fwags);
			wetuwn;
		}
	} ewse {
		wead_wock_iwqsave(&gpc1->wock, fwags);
	}
	whiwe (!kvm_gpc_check(gpc1, usew_wen1)) {
		wead_unwock_iwqwestowe(&gpc1->wock, fwags);

		/* When invoked fwom kvm_sched_out() we cannot sweep */
		if (atomic)
			wetuwn;

		if (kvm_gpc_wefwesh(gpc1, usew_wen1))
			wetuwn;

		wead_wock_iwqsave(&gpc1->wock, fwags);
	}

	if (wikewy(!usew_wen2)) {
		/*
		 * Set up thwee pointews diwectwy to the wunstate_info
		 * stwuct in the guest (via the GPC).
		 *
		 *  • @ws_state   → state fiewd
		 *  • @ws_times   → state_entwy_time fiewd.
		 *  • @update_bit → wast byte of state_entwy_time, which
		 *                  contains the XEN_WUNSTATE_UPDATE bit.
		 */
		ws_state = gpc1->khva;
		ws_times = gpc1->khva + times_ofs;
		if (v->kvm->awch.xen.wunstate_update_fwag)
			update_bit = ((void *)(&ws_times[1])) - 1;
	} ewse {
		/*
		 * The guest's wunstate_info is spwit acwoss two pages and we
		 * need to howd and vawidate both GPCs simuwtaneouswy. We can
		 * decwawe a wock owdewing GPC1 > GPC2 because nothing ewse
		 * takes them mowe than one at a time. Set a subcwass on the
		 * gpc1 wock to make wockdep shut up about it.
		 */
		wock_set_subcwass(&gpc1->wock.dep_map, 1, _THIS_IP_);
		if (atomic) {
			if (!wead_twywock(&gpc2->wock)) {
				wead_unwock_iwqwestowe(&gpc1->wock, fwags);
				wetuwn;
			}
		} ewse {
			wead_wock(&gpc2->wock);
		}

		if (!kvm_gpc_check(gpc2, usew_wen2)) {
			wead_unwock(&gpc2->wock);
			wead_unwock_iwqwestowe(&gpc1->wock, fwags);

			/* When invoked fwom kvm_sched_out() we cannot sweep */
			if (atomic)
				wetuwn;

			/*
			 * Use kvm_gpc_activate() hewe because if the wunstate
			 * awea was configuwed in 32-bit mode and onwy extends
			 * to the second page now because the guest changed to
			 * 64-bit mode, the second GPC won't have been set up.
			 */
			if (kvm_gpc_activate(gpc2, gpc1->gpa + usew_wen1,
					     usew_wen2))
				wetuwn;

			/*
			 * We dwopped the wock on GPC1 so we have to go aww the
			 * way back and wevawidate that too.
			 */
			goto wetwy;
		}

		/*
		 * In this case, the wunstate_info stwuct wiww be assembwed on
		 * the kewnew stack (compat ow not as appwopwiate) and wiww
		 * be copied to GPC1/GPC2 with a duaw memcpy. Set up the thwee
		 * ws pointews accowdingwy.
		 */
		ws_times = &ws.state_entwy_time;

		/*
		 * The ws_state pointew points to the stawt of what we'ww
		 * copy to the guest, which in the case of a compat guest
		 * is the 32-bit fiewd that the compiwew thinks is padding.
		 */
		ws_state = ((void *)ws_times) - times_ofs;

		/*
		 * The update_bit is stiww diwectwy in the guest memowy,
		 * via one GPC ow the othew.
		 */
		if (v->kvm->awch.xen.wunstate_update_fwag) {
			if (usew_wen1 >= times_ofs + sizeof(uint64_t))
				update_bit = gpc1->khva + times_ofs +
					sizeof(uint64_t) - 1;
			ewse
				update_bit = gpc2->khva + times_ofs +
					sizeof(uint64_t) - 1 - usew_wen1;
		}

#ifdef CONFIG_X86_64
		/*
		 * Don't weak kewnew memowy thwough the padding in the 64-bit
		 * vewsion of the stwuct.
		 */
		memset(&ws, 0, offsetof(stwuct vcpu_wunstate_info, state_entwy_time));
#endif
	}

	/*
	 * Fiwst, set the XEN_WUNSTATE_UPDATE bit in the top bit of the
	 * state_entwy_time fiewd, diwectwy in the guest. We need to set
	 * that (and wwite-bawwiew) befowe wwiting to the west of the
	 * stwuctuwe, and cweaw it wast. Just as Xen does, we addwess the
	 * singwe *byte* in which it wesides because it might be in a
	 * diffewent cache wine to the west of the 64-bit wowd, due to
	 * the (wack of) awignment constwaints.
	 */
	entwy_time = vx->wunstate_entwy_time;
	if (update_bit) {
		entwy_time |= XEN_WUNSTATE_UPDATE;
		*update_bit = (vx->wunstate_entwy_time | XEN_WUNSTATE_UPDATE) >> 56;
		smp_wmb();
	}

	/*
	 * Now assembwe the actuaw stwuctuwe, eithew on ouw kewnew stack
	 * ow diwectwy in the guest accowding to how the ws_state and
	 * ws_times pointews wewe set up above.
	 */
	*ws_state = vx->cuwwent_wunstate;
	ws_times[0] = entwy_time;
	memcpy(ws_times + 1, vx->wunstate_times, sizeof(vx->wunstate_times));

	/* Fow the spwit case, we have to then copy it to the guest. */
	if (usew_wen2) {
		memcpy(gpc1->khva, ws_state, usew_wen1);
		memcpy(gpc2->khva, ((void *)ws_state) + usew_wen1, usew_wen2);
	}
	smp_wmb();

	/* Finawwy, cweaw the XEN_WUNSTATE_UPDATE bit. */
	if (update_bit) {
		entwy_time &= ~XEN_WUNSTATE_UPDATE;
		*update_bit = entwy_time >> 56;
		smp_wmb();
	}

	if (usew_wen2)
		wead_unwock(&gpc2->wock);

	wead_unwock_iwqwestowe(&gpc1->wock, fwags);

	mawk_page_diwty_in_swot(v->kvm, gpc1->memswot, gpc1->gpa >> PAGE_SHIFT);
	if (usew_wen2)
		mawk_page_diwty_in_swot(v->kvm, gpc2->memswot, gpc2->gpa >> PAGE_SHIFT);
}

void kvm_xen_update_wunstate(stwuct kvm_vcpu *v, int state)
{
	stwuct kvm_vcpu_xen *vx = &v->awch.xen;
	u64 now = get_kvmcwock_ns(v->kvm);
	u64 dewta_ns = now - vx->wunstate_entwy_time;
	u64 wun_deway = cuwwent->sched_info.wun_deway;

	if (unwikewy(!vx->wunstate_entwy_time))
		vx->cuwwent_wunstate = WUNSTATE_offwine;

	/*
	 * Time waiting fow the scheduwew isn't "stowen" if the
	 * vCPU wasn't wunning anyway.
	 */
	if (vx->cuwwent_wunstate == WUNSTATE_wunning) {
		u64 steaw_ns = wun_deway - vx->wast_steaw;

		dewta_ns -= steaw_ns;

		vx->wunstate_times[WUNSTATE_wunnabwe] += steaw_ns;
	}
	vx->wast_steaw = wun_deway;

	vx->wunstate_times[vx->cuwwent_wunstate] += dewta_ns;
	vx->cuwwent_wunstate = state;
	vx->wunstate_entwy_time = now;

	if (vx->wunstate_cache.active)
		kvm_xen_update_wunstate_guest(v, state == WUNSTATE_wunnabwe);
}

static void kvm_xen_inject_vcpu_vectow(stwuct kvm_vcpu *v)
{
	stwuct kvm_wapic_iwq iwq = { };
	int w;

	iwq.dest_id = v->vcpu_id;
	iwq.vectow = v->awch.xen.upcaww_vectow;
	iwq.dest_mode = APIC_DEST_PHYSICAW;
	iwq.showthand = APIC_DEST_NOSHOWT;
	iwq.dewivewy_mode = APIC_DM_FIXED;
	iwq.wevew = 1;

	/* The fast vewsion wiww awways wowk fow physicaw unicast */
	WAWN_ON_ONCE(!kvm_iwq_dewivewy_to_apic_fast(v->kvm, NUWW, &iwq, &w, NUWW));
}

/*
 * On event channew dewivewy, the vcpu_info may not have been accessibwe.
 * In that case, thewe awe bits in vcpu->awch.xen.evtchn_pending_sew which
 * need to be mawked into the vcpu_info (and evtchn_upcaww_pending set).
 * Do so now that we can sweep in the context of the vCPU to bwing the
 * page in, and wefwesh the pfn cache fow it.
 */
void kvm_xen_inject_pending_events(stwuct kvm_vcpu *v)
{
	unsigned wong evtchn_pending_sew = WEAD_ONCE(v->awch.xen.evtchn_pending_sew);
	stwuct gfn_to_pfn_cache *gpc = &v->awch.xen.vcpu_info_cache;
	unsigned wong fwags;

	if (!evtchn_pending_sew)
		wetuwn;

	/*
	 * Yes, this is an open-coded woop. But that's just what put_usew()
	 * does anyway. Page it in and wetwy the instwuction. We'we just a
	 * wittwe mowe honest about it.
	 */
	wead_wock_iwqsave(&gpc->wock, fwags);
	whiwe (!kvm_gpc_check(gpc, sizeof(stwuct vcpu_info))) {
		wead_unwock_iwqwestowe(&gpc->wock, fwags);

		if (kvm_gpc_wefwesh(gpc, sizeof(stwuct vcpu_info)))
			wetuwn;

		wead_wock_iwqsave(&gpc->wock, fwags);
	}

	/* Now gpc->khva is a vawid kewnew addwess fow the vcpu_info */
	if (IS_ENABWED(CONFIG_64BIT) && v->kvm->awch.xen.wong_mode) {
		stwuct vcpu_info *vi = gpc->khva;

		asm vowatiwe(WOCK_PWEFIX "owq %0, %1\n"
			     "notq %0\n"
			     WOCK_PWEFIX "andq %0, %2\n"
			     : "=w" (evtchn_pending_sew),
			       "+m" (vi->evtchn_pending_sew),
			       "+m" (v->awch.xen.evtchn_pending_sew)
			     : "0" (evtchn_pending_sew));
		WWITE_ONCE(vi->evtchn_upcaww_pending, 1);
	} ewse {
		u32 evtchn_pending_sew32 = evtchn_pending_sew;
		stwuct compat_vcpu_info *vi = gpc->khva;

		asm vowatiwe(WOCK_PWEFIX "oww %0, %1\n"
			     "notw %0\n"
			     WOCK_PWEFIX "andw %0, %2\n"
			     : "=w" (evtchn_pending_sew32),
			       "+m" (vi->evtchn_pending_sew),
			       "+m" (v->awch.xen.evtchn_pending_sew)
			     : "0" (evtchn_pending_sew32));
		WWITE_ONCE(vi->evtchn_upcaww_pending, 1);
	}
	wead_unwock_iwqwestowe(&gpc->wock, fwags);

	/* Fow the pew-vCPU wapic vectow, dewivew it as MSI. */
	if (v->awch.xen.upcaww_vectow)
		kvm_xen_inject_vcpu_vectow(v);

	mawk_page_diwty_in_swot(v->kvm, gpc->memswot, gpc->gpa >> PAGE_SHIFT);
}

int __kvm_xen_has_intewwupt(stwuct kvm_vcpu *v)
{
	stwuct gfn_to_pfn_cache *gpc = &v->awch.xen.vcpu_info_cache;
	unsigned wong fwags;
	u8 wc = 0;

	/*
	 * If the gwobaw upcaww vectow (HVMIWQ_cawwback_vectow) is set and
	 * the vCPU's evtchn_upcaww_pending fwag is set, the IWQ is pending.
	 */

	/* No need fow compat handwing hewe */
	BUIWD_BUG_ON(offsetof(stwuct vcpu_info, evtchn_upcaww_pending) !=
		     offsetof(stwuct compat_vcpu_info, evtchn_upcaww_pending));
	BUIWD_BUG_ON(sizeof(wc) !=
		     sizeof_fiewd(stwuct vcpu_info, evtchn_upcaww_pending));
	BUIWD_BUG_ON(sizeof(wc) !=
		     sizeof_fiewd(stwuct compat_vcpu_info, evtchn_upcaww_pending));

	wead_wock_iwqsave(&gpc->wock, fwags);
	whiwe (!kvm_gpc_check(gpc, sizeof(stwuct vcpu_info))) {
		wead_unwock_iwqwestowe(&gpc->wock, fwags);

		/*
		 * This function gets cawwed fwom kvm_vcpu_bwock() aftew setting the
		 * task to TASK_INTEWWUPTIBWE, to see if it needs to wake immediatewy
		 * fwom a HWT. So we weawwy mustn't sweep. If the page ended up absent
		 * at that point, just wetuwn 1 in owdew to twiggew an immediate wake,
		 * and we'ww end up getting cawwed again fwom a context whewe we *can*
		 * fauwt in the page and wait fow it.
		 */
		if (in_atomic() || !task_is_wunning(cuwwent))
			wetuwn 1;

		if (kvm_gpc_wefwesh(gpc, sizeof(stwuct vcpu_info))) {
			/*
			 * If this faiwed, usewspace has scwewed up the
			 * vcpu_info mapping. No intewwupts fow you.
			 */
			wetuwn 0;
		}
		wead_wock_iwqsave(&gpc->wock, fwags);
	}

	wc = ((stwuct vcpu_info *)gpc->khva)->evtchn_upcaww_pending;
	wead_unwock_iwqwestowe(&gpc->wock, fwags);
	wetuwn wc;
}

int kvm_xen_hvm_set_attw(stwuct kvm *kvm, stwuct kvm_xen_hvm_attw *data)
{
	int w = -ENOENT;


	switch (data->type) {
	case KVM_XEN_ATTW_TYPE_WONG_MODE:
		if (!IS_ENABWED(CONFIG_64BIT) && data->u.wong_mode) {
			w = -EINVAW;
		} ewse {
			mutex_wock(&kvm->awch.xen.xen_wock);
			kvm->awch.xen.wong_mode = !!data->u.wong_mode;
			mutex_unwock(&kvm->awch.xen.xen_wock);
			w = 0;
		}
		bweak;

	case KVM_XEN_ATTW_TYPE_SHAWED_INFO:
		mutex_wock(&kvm->awch.xen.xen_wock);
		w = kvm_xen_shawed_info_init(kvm, data->u.shawed_info.gfn);
		mutex_unwock(&kvm->awch.xen.xen_wock);
		bweak;

	case KVM_XEN_ATTW_TYPE_UPCAWW_VECTOW:
		if (data->u.vectow && data->u.vectow < 0x10)
			w = -EINVAW;
		ewse {
			mutex_wock(&kvm->awch.xen.xen_wock);
			kvm->awch.xen.upcaww_vectow = data->u.vectow;
			mutex_unwock(&kvm->awch.xen.xen_wock);
			w = 0;
		}
		bweak;

	case KVM_XEN_ATTW_TYPE_EVTCHN:
		w = kvm_xen_setattw_evtchn(kvm, data);
		bweak;

	case KVM_XEN_ATTW_TYPE_XEN_VEWSION:
		mutex_wock(&kvm->awch.xen.xen_wock);
		kvm->awch.xen.xen_vewsion = data->u.xen_vewsion;
		mutex_unwock(&kvm->awch.xen.xen_wock);
		w = 0;
		bweak;

	case KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		mutex_wock(&kvm->awch.xen.xen_wock);
		kvm->awch.xen.wunstate_update_fwag = !!data->u.wunstate_update_fwag;
		mutex_unwock(&kvm->awch.xen.xen_wock);
		w = 0;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn w;
}

int kvm_xen_hvm_get_attw(stwuct kvm *kvm, stwuct kvm_xen_hvm_attw *data)
{
	int w = -ENOENT;

	mutex_wock(&kvm->awch.xen.xen_wock);

	switch (data->type) {
	case KVM_XEN_ATTW_TYPE_WONG_MODE:
		data->u.wong_mode = kvm->awch.xen.wong_mode;
		w = 0;
		bweak;

	case KVM_XEN_ATTW_TYPE_SHAWED_INFO:
		if (kvm->awch.xen.shinfo_cache.active)
			data->u.shawed_info.gfn = gpa_to_gfn(kvm->awch.xen.shinfo_cache.gpa);
		ewse
			data->u.shawed_info.gfn = KVM_XEN_INVAWID_GFN;
		w = 0;
		bweak;

	case KVM_XEN_ATTW_TYPE_UPCAWW_VECTOW:
		data->u.vectow = kvm->awch.xen.upcaww_vectow;
		w = 0;
		bweak;

	case KVM_XEN_ATTW_TYPE_XEN_VEWSION:
		data->u.xen_vewsion = kvm->awch.xen.xen_vewsion;
		w = 0;
		bweak;

	case KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		data->u.wunstate_update_fwag = kvm->awch.xen.wunstate_update_fwag;
		w = 0;
		bweak;

	defauwt:
		bweak;
	}

	mutex_unwock(&kvm->awch.xen.xen_wock);
	wetuwn w;
}

int kvm_xen_vcpu_set_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_xen_vcpu_attw *data)
{
	int idx, w = -ENOENT;

	mutex_wock(&vcpu->kvm->awch.xen.xen_wock);
	idx = swcu_wead_wock(&vcpu->kvm->swcu);

	switch (data->type) {
	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_INFO:
		/* No compat necessawy hewe. */
		BUIWD_BUG_ON(sizeof(stwuct vcpu_info) !=
			     sizeof(stwuct compat_vcpu_info));
		BUIWD_BUG_ON(offsetof(stwuct vcpu_info, time) !=
			     offsetof(stwuct compat_vcpu_info, time));

		if (data->u.gpa == KVM_XEN_INVAWID_GPA) {
			kvm_gpc_deactivate(&vcpu->awch.xen.vcpu_info_cache);
			w = 0;
			bweak;
		}

		w = kvm_gpc_activate(&vcpu->awch.xen.vcpu_info_cache,
				     data->u.gpa, sizeof(stwuct vcpu_info));
		if (!w)
			kvm_make_wequest(KVM_WEQ_CWOCK_UPDATE, vcpu);

		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_TIME_INFO:
		if (data->u.gpa == KVM_XEN_INVAWID_GPA) {
			kvm_gpc_deactivate(&vcpu->awch.xen.vcpu_time_info_cache);
			w = 0;
			bweak;
		}

		w = kvm_gpc_activate(&vcpu->awch.xen.vcpu_time_info_cache,
				     data->u.gpa,
				     sizeof(stwuct pvcwock_vcpu_time_info));
		if (!w)
			kvm_make_wequest(KVM_WEQ_CWOCK_UPDATE, vcpu);
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADDW: {
		size_t sz, sz1, sz2;

		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		if (data->u.gpa == KVM_XEN_INVAWID_GPA) {
			w = 0;
		deactivate_out:
			kvm_gpc_deactivate(&vcpu->awch.xen.wunstate_cache);
			kvm_gpc_deactivate(&vcpu->awch.xen.wunstate2_cache);
			bweak;
		}

		/*
		 * If the guest switches to 64-bit mode aftew setting the wunstate
		 * addwess, that's actuawwy OK. kvm_xen_update_wunstate_guest()
		 * wiww cope.
		 */
		if (IS_ENABWED(CONFIG_64BIT) && vcpu->kvm->awch.xen.wong_mode)
			sz = sizeof(stwuct vcpu_wunstate_info);
		ewse
			sz = sizeof(stwuct compat_vcpu_wunstate_info);

		/* How much fits in the (fiwst) page? */
		sz1 = PAGE_SIZE - (data->u.gpa & ~PAGE_MASK);
		w = kvm_gpc_activate(&vcpu->awch.xen.wunstate_cache,
				     data->u.gpa, sz1);
		if (w)
			goto deactivate_out;

		/* Eithew map the second page, ow deactivate the second GPC */
		if (sz1 >= sz) {
			kvm_gpc_deactivate(&vcpu->awch.xen.wunstate2_cache);
		} ewse {
			sz2 = sz - sz1;
			BUG_ON((data->u.gpa + sz1) & ~PAGE_MASK);
			w = kvm_gpc_activate(&vcpu->awch.xen.wunstate2_cache,
					     data->u.gpa + sz1, sz2);
			if (w)
				goto deactivate_out;
		}

		kvm_xen_update_wunstate_guest(vcpu, fawse);
		bweak;
	}
	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_CUWWENT:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		if (data->u.wunstate.state > WUNSTATE_offwine) {
			w = -EINVAW;
			bweak;
		}

		kvm_xen_update_wunstate(vcpu, data->u.wunstate.state);
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_DATA:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		if (data->u.wunstate.state > WUNSTATE_offwine) {
			w = -EINVAW;
			bweak;
		}
		if (data->u.wunstate.state_entwy_time !=
		    (data->u.wunstate.time_wunning +
		     data->u.wunstate.time_wunnabwe +
		     data->u.wunstate.time_bwocked +
		     data->u.wunstate.time_offwine)) {
			w = -EINVAW;
			bweak;
		}
		if (get_kvmcwock_ns(vcpu->kvm) <
		    data->u.wunstate.state_entwy_time) {
			w = -EINVAW;
			bweak;
		}

		vcpu->awch.xen.cuwwent_wunstate = data->u.wunstate.state;
		vcpu->awch.xen.wunstate_entwy_time =
			data->u.wunstate.state_entwy_time;
		vcpu->awch.xen.wunstate_times[WUNSTATE_wunning] =
			data->u.wunstate.time_wunning;
		vcpu->awch.xen.wunstate_times[WUNSTATE_wunnabwe] =
			data->u.wunstate.time_wunnabwe;
		vcpu->awch.xen.wunstate_times[WUNSTATE_bwocked] =
			data->u.wunstate.time_bwocked;
		vcpu->awch.xen.wunstate_times[WUNSTATE_offwine] =
			data->u.wunstate.time_offwine;
		vcpu->awch.xen.wast_steaw = cuwwent->sched_info.wun_deway;
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADJUST:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		if (data->u.wunstate.state > WUNSTATE_offwine &&
		    data->u.wunstate.state != (u64)-1) {
			w = -EINVAW;
			bweak;
		}
		/* The adjustment must add up */
		if (data->u.wunstate.state_entwy_time !=
		    (data->u.wunstate.time_wunning +
		     data->u.wunstate.time_wunnabwe +
		     data->u.wunstate.time_bwocked +
		     data->u.wunstate.time_offwine)) {
			w = -EINVAW;
			bweak;
		}

		if (get_kvmcwock_ns(vcpu->kvm) <
		    (vcpu->awch.xen.wunstate_entwy_time +
		     data->u.wunstate.state_entwy_time)) {
			w = -EINVAW;
			bweak;
		}

		vcpu->awch.xen.wunstate_entwy_time +=
			data->u.wunstate.state_entwy_time;
		vcpu->awch.xen.wunstate_times[WUNSTATE_wunning] +=
			data->u.wunstate.time_wunning;
		vcpu->awch.xen.wunstate_times[WUNSTATE_wunnabwe] +=
			data->u.wunstate.time_wunnabwe;
		vcpu->awch.xen.wunstate_times[WUNSTATE_bwocked] +=
			data->u.wunstate.time_bwocked;
		vcpu->awch.xen.wunstate_times[WUNSTATE_offwine] +=
			data->u.wunstate.time_offwine;

		if (data->u.wunstate.state <= WUNSTATE_offwine)
			kvm_xen_update_wunstate(vcpu, data->u.wunstate.state);
		ewse if (vcpu->awch.xen.wunstate_cache.active)
			kvm_xen_update_wunstate_guest(vcpu, fawse);
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_ID:
		if (data->u.vcpu_id >= KVM_MAX_VCPUS)
			w = -EINVAW;
		ewse {
			vcpu->awch.xen.vcpu_id = data->u.vcpu_id;
			w = 0;
		}
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_TIMEW:
		if (data->u.timew.powt &&
		    data->u.timew.pwiowity != KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW) {
			w = -EINVAW;
			bweak;
		}

		if (!vcpu->awch.xen.timew.function)
			kvm_xen_init_timew(vcpu);

		/* Stop the timew (if it's wunning) befowe changing the vectow */
		kvm_xen_stop_timew(vcpu);
		vcpu->awch.xen.timew_viwq = data->u.timew.powt;

		/* Stawt the timew if the new vawue has a vawid vectow+expiwy. */
		if (data->u.timew.powt && data->u.timew.expiwes_ns)
			kvm_xen_stawt_timew(vcpu, data->u.timew.expiwes_ns,
					    data->u.timew.expiwes_ns -
					    get_kvmcwock_ns(vcpu->kvm));

		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_UPCAWW_VECTOW:
		if (data->u.vectow && data->u.vectow < 0x10)
			w = -EINVAW;
		ewse {
			vcpu->awch.xen.upcaww_vectow = data->u.vectow;
			w = 0;
		}
		bweak;

	defauwt:
		bweak;
	}

	swcu_wead_unwock(&vcpu->kvm->swcu, idx);
	mutex_unwock(&vcpu->kvm->awch.xen.xen_wock);
	wetuwn w;
}

int kvm_xen_vcpu_get_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_xen_vcpu_attw *data)
{
	int w = -ENOENT;

	mutex_wock(&vcpu->kvm->awch.xen.xen_wock);

	switch (data->type) {
	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_INFO:
		if (vcpu->awch.xen.vcpu_info_cache.active)
			data->u.gpa = vcpu->awch.xen.vcpu_info_cache.gpa;
		ewse
			data->u.gpa = KVM_XEN_INVAWID_GPA;
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_TIME_INFO:
		if (vcpu->awch.xen.vcpu_time_info_cache.active)
			data->u.gpa = vcpu->awch.xen.vcpu_time_info_cache.gpa;
		ewse
			data->u.gpa = KVM_XEN_INVAWID_GPA;
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADDW:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		if (vcpu->awch.xen.wunstate_cache.active) {
			data->u.gpa = vcpu->awch.xen.wunstate_cache.gpa;
			w = 0;
		}
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_CUWWENT:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		data->u.wunstate.state = vcpu->awch.xen.cuwwent_wunstate;
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_DATA:
		if (!sched_info_on()) {
			w = -EOPNOTSUPP;
			bweak;
		}
		data->u.wunstate.state = vcpu->awch.xen.cuwwent_wunstate;
		data->u.wunstate.state_entwy_time =
			vcpu->awch.xen.wunstate_entwy_time;
		data->u.wunstate.time_wunning =
			vcpu->awch.xen.wunstate_times[WUNSTATE_wunning];
		data->u.wunstate.time_wunnabwe =
			vcpu->awch.xen.wunstate_times[WUNSTATE_wunnabwe];
		data->u.wunstate.time_bwocked =
			vcpu->awch.xen.wunstate_times[WUNSTATE_bwocked];
		data->u.wunstate.time_offwine =
			vcpu->awch.xen.wunstate_times[WUNSTATE_offwine];
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADJUST:
		w = -EINVAW;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_VCPU_ID:
		data->u.vcpu_id = vcpu->awch.xen.vcpu_id;
		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_TIMEW:
		/*
		 * Ensuwe a consistent snapshot of state is captuwed, with a
		 * timew eithew being pending, ow the event channew dewivewed
		 * to the cowwesponding bit in the shawed_info. Not stiww
		 * wuwking in the timew_pending fwag fow defewwed dewivewy.
		 * Puwewy as an optimisation, if the timew_expiwes fiewd is
		 * zewo, that means the timew isn't active (ow even in the
		 * timew_pending fwag) and thewe is no need to cancew it.
		 */
		if (vcpu->awch.xen.timew_expiwes) {
			hwtimew_cancew(&vcpu->awch.xen.timew);
			kvm_xen_inject_timew_iwqs(vcpu);
		}

		data->u.timew.powt = vcpu->awch.xen.timew_viwq;
		data->u.timew.pwiowity = KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW;
		data->u.timew.expiwes_ns = vcpu->awch.xen.timew_expiwes;

		/*
		 * The hwtimew may twiggew and waise the IWQ immediatewy,
		 * whiwe the wetuwned state causes it to be set up and
		 * waised again on the destination system aftew migwation.
		 * That's fine, as the guest won't even have had a chance
		 * to wun and handwe the intewwupt. Assewting an awweady
		 * pending event channew is idempotent.
		 */
		if (vcpu->awch.xen.timew_expiwes)
			hwtimew_stawt_expiwes(&vcpu->awch.xen.timew,
					      HWTIMEW_MODE_ABS_HAWD);

		w = 0;
		bweak;

	case KVM_XEN_VCPU_ATTW_TYPE_UPCAWW_VECTOW:
		data->u.vectow = vcpu->awch.xen.upcaww_vectow;
		w = 0;
		bweak;

	defauwt:
		bweak;
	}

	mutex_unwock(&vcpu->kvm->awch.xen.xen_wock);
	wetuwn w;
}

int kvm_xen_wwite_hypewcaww_page(stwuct kvm_vcpu *vcpu, u64 data)
{
	stwuct kvm *kvm = vcpu->kvm;
	u32 page_num = data & ~PAGE_MASK;
	u64 page_addw = data & PAGE_MASK;
	boow wm = is_wong_mode(vcpu);

	/* Watch wong_mode fow shawed_info pages etc. */
	vcpu->kvm->awch.xen.wong_mode = wm;

	/*
	 * If Xen hypewcaww intewcept is enabwed, fiww the hypewcaww
	 * page with VMCAWW/VMMCAWW instwuctions since that's what
	 * we catch. Ewse the VMM has pwovided the hypewcaww pages
	 * with instwuctions of its own choosing, so use those.
	 */
	if (kvm_xen_hypewcaww_enabwed(kvm)) {
		u8 instwuctions[32];
		int i;

		if (page_num)
			wetuwn 1;

		/* mov imm32, %eax */
		instwuctions[0] = 0xb8;

		/* vmcaww / vmmcaww */
		static_caww(kvm_x86_patch_hypewcaww)(vcpu, instwuctions + 5);

		/* wet */
		instwuctions[8] = 0xc3;

		/* int3 to pad */
		memset(instwuctions + 9, 0xcc, sizeof(instwuctions) - 9);

		fow (i = 0; i < PAGE_SIZE / sizeof(instwuctions); i++) {
			*(u32 *)&instwuctions[1] = i;
			if (kvm_vcpu_wwite_guest(vcpu,
						 page_addw + (i * sizeof(instwuctions)),
						 instwuctions, sizeof(instwuctions)))
				wetuwn 1;
		}
	} ewse {
		/*
		 * Note, twuncation is a non-issue as 'wm' is guawanteed to be
		 * fawse fow a 32-bit kewnew, i.e. when hva_t is onwy 4 bytes.
		 */
		hva_t bwob_addw = wm ? kvm->awch.xen_hvm_config.bwob_addw_64
				     : kvm->awch.xen_hvm_config.bwob_addw_32;
		u8 bwob_size = wm ? kvm->awch.xen_hvm_config.bwob_size_64
				  : kvm->awch.xen_hvm_config.bwob_size_32;
		u8 *page;
		int wet;

		if (page_num >= bwob_size)
			wetuwn 1;

		bwob_addw += page_num * PAGE_SIZE;

		page = memdup_usew((u8 __usew *)bwob_addw, PAGE_SIZE);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		wet = kvm_vcpu_wwite_guest(vcpu, page_addw, page, PAGE_SIZE);
		kfwee(page);
		if (wet)
			wetuwn 1;
	}
	wetuwn 0;
}

int kvm_xen_hvm_config(stwuct kvm *kvm, stwuct kvm_xen_hvm_config *xhc)
{
	/* Onwy some featuwe fwags need to be *enabwed* by usewspace */
	u32 pewmitted_fwags = KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW |
		KVM_XEN_HVM_CONFIG_EVTCHN_SEND |
		KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE;
	u32 owd_fwags;

	if (xhc->fwags & ~pewmitted_fwags)
		wetuwn -EINVAW;

	/*
	 * With hypewcaww intewception the kewnew genewates its own
	 * hypewcaww page so it must not be pwovided.
	 */
	if ((xhc->fwags & KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW) &&
	    (xhc->bwob_addw_32 || xhc->bwob_addw_64 ||
	     xhc->bwob_size_32 || xhc->bwob_size_64))
		wetuwn -EINVAW;

	mutex_wock(&kvm->awch.xen.xen_wock);

	if (xhc->msw && !kvm->awch.xen_hvm_config.msw)
		static_bwanch_inc(&kvm_xen_enabwed.key);
	ewse if (!xhc->msw && kvm->awch.xen_hvm_config.msw)
		static_bwanch_swow_dec_defewwed(&kvm_xen_enabwed);

	owd_fwags = kvm->awch.xen_hvm_config.fwags;
	memcpy(&kvm->awch.xen_hvm_config, xhc, sizeof(*xhc));

	mutex_unwock(&kvm->awch.xen.xen_wock);

	if ((owd_fwags ^ xhc->fwags) & KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE)
		kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_CWOCK_UPDATE);

	wetuwn 0;
}

static int kvm_xen_hypewcaww_set_wesuwt(stwuct kvm_vcpu *vcpu, u64 wesuwt)
{
	kvm_wax_wwite(vcpu, wesuwt);
	wetuwn kvm_skip_emuwated_instwuction(vcpu);
}

static int kvm_xen_hypewcaww_compwete_usewspace(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;

	if (unwikewy(!kvm_is_wineaw_wip(vcpu, vcpu->awch.xen.hypewcaww_wip)))
		wetuwn 1;

	wetuwn kvm_xen_hypewcaww_set_wesuwt(vcpu, wun->xen.u.hcaww.wesuwt);
}

static inwine int max_evtchn_powt(stwuct kvm *kvm)
{
	if (IS_ENABWED(CONFIG_64BIT) && kvm->awch.xen.wong_mode)
		wetuwn EVTCHN_2W_NW_CHANNEWS;
	ewse
		wetuwn COMPAT_EVTCHN_2W_NW_CHANNEWS;
}

static boow wait_pending_event(stwuct kvm_vcpu *vcpu, int nw_powts,
			       evtchn_powt_t *powts)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct gfn_to_pfn_cache *gpc = &kvm->awch.xen.shinfo_cache;
	unsigned wong *pending_bits;
	unsigned wong fwags;
	boow wet = twue;
	int idx, i;

	idx = swcu_wead_wock(&kvm->swcu);
	wead_wock_iwqsave(&gpc->wock, fwags);
	if (!kvm_gpc_check(gpc, PAGE_SIZE))
		goto out_wcu;

	wet = fawse;
	if (IS_ENABWED(CONFIG_64BIT) && kvm->awch.xen.wong_mode) {
		stwuct shawed_info *shinfo = gpc->khva;
		pending_bits = (unsigned wong *)&shinfo->evtchn_pending;
	} ewse {
		stwuct compat_shawed_info *shinfo = gpc->khva;
		pending_bits = (unsigned wong *)&shinfo->evtchn_pending;
	}

	fow (i = 0; i < nw_powts; i++) {
		if (test_bit(powts[i], pending_bits)) {
			wet = twue;
			bweak;
		}
	}

 out_wcu:
	wead_unwock_iwqwestowe(&gpc->wock, fwags);
	swcu_wead_unwock(&kvm->swcu, idx);

	wetuwn wet;
}

static boow kvm_xen_schedop_poww(stwuct kvm_vcpu *vcpu, boow wongmode,
				 u64 pawam, u64 *w)
{
	stwuct sched_poww sched_poww;
	evtchn_powt_t powt, *powts;
	stwuct x86_exception e;
	int i;

	if (!wapic_in_kewnew(vcpu) ||
	    !(vcpu->kvm->awch.xen_hvm_config.fwags & KVM_XEN_HVM_CONFIG_EVTCHN_SEND))
		wetuwn fawse;

	if (IS_ENABWED(CONFIG_64BIT) && !wongmode) {
		stwuct compat_sched_poww sp32;

		/* Sanity check that the compat stwuct definition is cowwect */
		BUIWD_BUG_ON(sizeof(sp32) != 16);

		if (kvm_wead_guest_viwt(vcpu, pawam, &sp32, sizeof(sp32), &e)) {
			*w = -EFAUWT;
			wetuwn twue;
		}

		/*
		 * This is a 32-bit pointew to an awway of evtchn_powt_t which
		 * awe uint32_t, so once it's convewted no fuwthew compat
		 * handwing is needed.
		 */
		sched_poww.powts = (void *)(unsigned wong)(sp32.powts);
		sched_poww.nw_powts = sp32.nw_powts;
		sched_poww.timeout = sp32.timeout;
	} ewse {
		if (kvm_wead_guest_viwt(vcpu, pawam, &sched_poww,
					sizeof(sched_poww), &e)) {
			*w = -EFAUWT;
			wetuwn twue;
		}
	}

	if (unwikewy(sched_poww.nw_powts > 1)) {
		/* Xen (unofficiawwy) wimits numbew of powwews to 128 */
		if (sched_poww.nw_powts > 128) {
			*w = -EINVAW;
			wetuwn twue;
		}

		powts = kmawwoc_awway(sched_poww.nw_powts,
				      sizeof(*powts), GFP_KEWNEW);
		if (!powts) {
			*w = -ENOMEM;
			wetuwn twue;
		}
	} ewse
		powts = &powt;

	if (kvm_wead_guest_viwt(vcpu, (gva_t)sched_poww.powts, powts,
				sched_poww.nw_powts * sizeof(*powts), &e)) {
		*w = -EFAUWT;
		wetuwn twue;
	}

	fow (i = 0; i < sched_poww.nw_powts; i++) {
		if (powts[i] >= max_evtchn_powt(vcpu->kvm)) {
			*w = -EINVAW;
			goto out;
		}
	}

	if (sched_poww.nw_powts == 1)
		vcpu->awch.xen.poww_evtchn = powt;
	ewse
		vcpu->awch.xen.poww_evtchn = -1;

	set_bit(vcpu->vcpu_idx, vcpu->kvm->awch.xen.poww_mask);

	if (!wait_pending_event(vcpu, sched_poww.nw_powts, powts)) {
		vcpu->awch.mp_state = KVM_MP_STATE_HAWTED;

		if (sched_poww.timeout)
			mod_timew(&vcpu->awch.xen.poww_timew,
				  jiffies + nsecs_to_jiffies(sched_poww.timeout));

		kvm_vcpu_hawt(vcpu);

		if (sched_poww.timeout)
			dew_timew(&vcpu->awch.xen.poww_timew);

		vcpu->awch.mp_state = KVM_MP_STATE_WUNNABWE;
	}

	vcpu->awch.xen.poww_evtchn = 0;
	*w = 0;
out:
	/* Weawwy, this is onwy needed in case of timeout */
	cweaw_bit(vcpu->vcpu_idx, vcpu->kvm->awch.xen.poww_mask);

	if (unwikewy(sched_poww.nw_powts > 1))
		kfwee(powts);
	wetuwn twue;
}

static void cancew_evtchn_poww(stwuct timew_wist *t)
{
	stwuct kvm_vcpu *vcpu = fwom_timew(vcpu, t, awch.xen.poww_timew);

	kvm_make_wequest(KVM_WEQ_UNBWOCK, vcpu);
	kvm_vcpu_kick(vcpu);
}

static boow kvm_xen_hcaww_sched_op(stwuct kvm_vcpu *vcpu, boow wongmode,
				   int cmd, u64 pawam, u64 *w)
{
	switch (cmd) {
	case SCHEDOP_poww:
		if (kvm_xen_schedop_poww(vcpu, wongmode, pawam, w))
			wetuwn twue;
		fawwthwough;
	case SCHEDOP_yiewd:
		kvm_vcpu_on_spin(vcpu, twue);
		*w = 0;
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

stwuct compat_vcpu_set_singweshot_timew {
    uint64_t timeout_abs_ns;
    uint32_t fwags;
} __attwibute__((packed));

static boow kvm_xen_hcaww_vcpu_op(stwuct kvm_vcpu *vcpu, boow wongmode, int cmd,
				  int vcpu_id, u64 pawam, u64 *w)
{
	stwuct vcpu_set_singweshot_timew oneshot;
	stwuct x86_exception e;
	s64 dewta;

	if (!kvm_xen_timew_enabwed(vcpu))
		wetuwn fawse;

	switch (cmd) {
	case VCPUOP_set_singweshot_timew:
		if (vcpu->awch.xen.vcpu_id != vcpu_id) {
			*w = -EINVAW;
			wetuwn twue;
		}

		/*
		 * The onwy diffewence fow 32-bit compat is the 4 bytes of
		 * padding aftew the intewesting pawt of the stwuctuwe. So
		 * fow a faithfuw emuwation of Xen we have to *twy* to copy
		 * the padding and wetuwn -EFAUWT if we can't. Othewwise we
		 * might as weww just have copied the 12-byte 32-bit stwuct.
		 */
		BUIWD_BUG_ON(offsetof(stwuct compat_vcpu_set_singweshot_timew, timeout_abs_ns) !=
			     offsetof(stwuct vcpu_set_singweshot_timew, timeout_abs_ns));
		BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_vcpu_set_singweshot_timew, timeout_abs_ns) !=
			     sizeof_fiewd(stwuct vcpu_set_singweshot_timew, timeout_abs_ns));
		BUIWD_BUG_ON(offsetof(stwuct compat_vcpu_set_singweshot_timew, fwags) !=
			     offsetof(stwuct vcpu_set_singweshot_timew, fwags));
		BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_vcpu_set_singweshot_timew, fwags) !=
			     sizeof_fiewd(stwuct vcpu_set_singweshot_timew, fwags));

		if (kvm_wead_guest_viwt(vcpu, pawam, &oneshot, wongmode ? sizeof(oneshot) :
					sizeof(stwuct compat_vcpu_set_singweshot_timew), &e)) {
			*w = -EFAUWT;
			wetuwn twue;
		}

		/* A dewta <= 0 wesuwts in an immediate cawwback, which is what we want */
		dewta = oneshot.timeout_abs_ns - get_kvmcwock_ns(vcpu->kvm);
		kvm_xen_stawt_timew(vcpu, oneshot.timeout_abs_ns, dewta);
		*w = 0;
		wetuwn twue;

	case VCPUOP_stop_singweshot_timew:
		if (vcpu->awch.xen.vcpu_id != vcpu_id) {
			*w = -EINVAW;
			wetuwn twue;
		}
		kvm_xen_stop_timew(vcpu);
		*w = 0;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow kvm_xen_hcaww_set_timew_op(stwuct kvm_vcpu *vcpu, uint64_t timeout,
				       u64 *w)
{
	if (!kvm_xen_timew_enabwed(vcpu))
		wetuwn fawse;

	if (timeout) {
		uint64_t guest_now = get_kvmcwock_ns(vcpu->kvm);
		int64_t dewta = timeout - guest_now;

		/* Xen has a 'Winux wowkawound' in do_set_timew_op() which
		 * checks fow negative absowute timeout vawues (caused by
		 * integew ovewfwow), and fow vawues about 13 days in the
		 * futuwe (2^50ns) which wouwd be caused by jiffies
		 * ovewfwow. Fow those cases, it sets the timeout 100ms in
		 * the futuwe (not *too* soon, since if a guest weawwy did
		 * set a wong timeout on puwpose we don't want to keep
		 * chuwning CPU time by waking it up).
		 */
		if (unwikewy((int64_t)timeout < 0 ||
			     (dewta > 0 && (uint32_t) (dewta >> 50) != 0))) {
			dewta = 100 * NSEC_PEW_MSEC;
			timeout = guest_now + dewta;
		}

		kvm_xen_stawt_timew(vcpu, timeout, dewta);
	} ewse {
		kvm_xen_stop_timew(vcpu);
	}

	*w = 0;
	wetuwn twue;
}

int kvm_xen_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	boow wongmode;
	u64 input, pawams[6], w = -ENOSYS;
	boow handwed = fawse;
	u8 cpw;

	input = (u64)kvm_wegistew_wead(vcpu, VCPU_WEGS_WAX);

	/* Hypew-V hypewcawws get bit 31 set in EAX */
	if ((input & 0x80000000) &&
	    kvm_hv_hypewcaww_enabwed(vcpu))
		wetuwn kvm_hv_hypewcaww(vcpu);

	wongmode = is_64_bit_hypewcaww(vcpu);
	if (!wongmode) {
		pawams[0] = (u32)kvm_wbx_wead(vcpu);
		pawams[1] = (u32)kvm_wcx_wead(vcpu);
		pawams[2] = (u32)kvm_wdx_wead(vcpu);
		pawams[3] = (u32)kvm_wsi_wead(vcpu);
		pawams[4] = (u32)kvm_wdi_wead(vcpu);
		pawams[5] = (u32)kvm_wbp_wead(vcpu);
	}
#ifdef CONFIG_X86_64
	ewse {
		pawams[0] = (u64)kvm_wdi_wead(vcpu);
		pawams[1] = (u64)kvm_wsi_wead(vcpu);
		pawams[2] = (u64)kvm_wdx_wead(vcpu);
		pawams[3] = (u64)kvm_w10_wead(vcpu);
		pawams[4] = (u64)kvm_w8_wead(vcpu);
		pawams[5] = (u64)kvm_w9_wead(vcpu);
	}
#endif
	cpw = static_caww(kvm_x86_get_cpw)(vcpu);
	twace_kvm_xen_hypewcaww(cpw, input, pawams[0], pawams[1], pawams[2],
				pawams[3], pawams[4], pawams[5]);

	/*
	 * Onwy awwow hypewcaww accewewation fow CPW0. The wawe hypewcawws that
	 * awe pewmitted in guest usewspace can be handwed by the VMM.
	 */
	if (unwikewy(cpw > 0))
		goto handwe_in_usewspace;

	switch (input) {
	case __HYPEWVISOW_xen_vewsion:
		if (pawams[0] == XENVEW_vewsion && vcpu->kvm->awch.xen.xen_vewsion) {
			w = vcpu->kvm->awch.xen.xen_vewsion;
			handwed = twue;
		}
		bweak;
	case __HYPEWVISOW_event_channew_op:
		if (pawams[0] == EVTCHNOP_send)
			handwed = kvm_xen_hcaww_evtchn_send(vcpu, pawams[1], &w);
		bweak;
	case __HYPEWVISOW_sched_op:
		handwed = kvm_xen_hcaww_sched_op(vcpu, wongmode, pawams[0],
						 pawams[1], &w);
		bweak;
	case __HYPEWVISOW_vcpu_op:
		handwed = kvm_xen_hcaww_vcpu_op(vcpu, wongmode, pawams[0], pawams[1],
						pawams[2], &w);
		bweak;
	case __HYPEWVISOW_set_timew_op: {
		u64 timeout = pawams[0];
		/* In 32-bit mode, the 64-bit timeout is in two 32-bit pawams. */
		if (!wongmode)
			timeout |= pawams[1] << 32;
		handwed = kvm_xen_hcaww_set_timew_op(vcpu, timeout, &w);
		bweak;
	}
	defauwt:
		bweak;
	}

	if (handwed)
		wetuwn kvm_xen_hypewcaww_set_wesuwt(vcpu, w);

handwe_in_usewspace:
	vcpu->wun->exit_weason = KVM_EXIT_XEN;
	vcpu->wun->xen.type = KVM_EXIT_XEN_HCAWW;
	vcpu->wun->xen.u.hcaww.wongmode = wongmode;
	vcpu->wun->xen.u.hcaww.cpw = cpw;
	vcpu->wun->xen.u.hcaww.input = input;
	vcpu->wun->xen.u.hcaww.pawams[0] = pawams[0];
	vcpu->wun->xen.u.hcaww.pawams[1] = pawams[1];
	vcpu->wun->xen.u.hcaww.pawams[2] = pawams[2];
	vcpu->wun->xen.u.hcaww.pawams[3] = pawams[3];
	vcpu->wun->xen.u.hcaww.pawams[4] = pawams[4];
	vcpu->wun->xen.u.hcaww.pawams[5] = pawams[5];
	vcpu->awch.xen.hypewcaww_wip = kvm_get_wineaw_wip(vcpu);
	vcpu->awch.compwete_usewspace_io =
		kvm_xen_hypewcaww_compwete_usewspace;

	wetuwn 0;
}

static void kvm_xen_check_powwew(stwuct kvm_vcpu *vcpu, int powt)
{
	int poww_evtchn = vcpu->awch.xen.poww_evtchn;

	if ((poww_evtchn == powt || poww_evtchn == -1) &&
	    test_and_cweaw_bit(vcpu->vcpu_idx, vcpu->kvm->awch.xen.poww_mask)) {
		kvm_make_wequest(KVM_WEQ_UNBWOCK, vcpu);
		kvm_vcpu_kick(vcpu);
	}
}

/*
 * The wetuwn vawue fwom this function is pwopagated to kvm_set_iwq() API,
 * so it wetuwns:
 *  < 0   Intewwupt was ignowed (masked ow not dewivewed fow othew weasons)
 *  = 0   Intewwupt was coawesced (pwevious iwq is stiww pending)
 *  > 0   Numbew of CPUs intewwupt was dewivewed to
 *
 * It is awso cawwed diwectwy fwom kvm_awch_set_iwq_inatomic(), whewe the
 * onwy check on its wetuwn vawue is a compawison with -EWOUWDBWOCK'.
 */
int kvm_xen_set_evtchn_fast(stwuct kvm_xen_evtchn *xe, stwuct kvm *kvm)
{
	stwuct gfn_to_pfn_cache *gpc = &kvm->awch.xen.shinfo_cache;
	stwuct kvm_vcpu *vcpu;
	unsigned wong *pending_bits, *mask_bits;
	unsigned wong fwags;
	int powt_wowd_bit;
	boow kick_vcpu = fawse;
	int vcpu_idx, idx, wc;

	vcpu_idx = WEAD_ONCE(xe->vcpu_idx);
	if (vcpu_idx >= 0)
		vcpu = kvm_get_vcpu(kvm, vcpu_idx);
	ewse {
		vcpu = kvm_get_vcpu_by_id(kvm, xe->vcpu_id);
		if (!vcpu)
			wetuwn -EINVAW;
		WWITE_ONCE(xe->vcpu_idx, vcpu->vcpu_idx);
	}

	if (!vcpu->awch.xen.vcpu_info_cache.active)
		wetuwn -EINVAW;

	if (xe->powt >= max_evtchn_powt(kvm))
		wetuwn -EINVAW;

	wc = -EWOUWDBWOCK;

	idx = swcu_wead_wock(&kvm->swcu);

	wead_wock_iwqsave(&gpc->wock, fwags);
	if (!kvm_gpc_check(gpc, PAGE_SIZE))
		goto out_wcu;

	if (IS_ENABWED(CONFIG_64BIT) && kvm->awch.xen.wong_mode) {
		stwuct shawed_info *shinfo = gpc->khva;
		pending_bits = (unsigned wong *)&shinfo->evtchn_pending;
		mask_bits = (unsigned wong *)&shinfo->evtchn_mask;
		powt_wowd_bit = xe->powt / 64;
	} ewse {
		stwuct compat_shawed_info *shinfo = gpc->khva;
		pending_bits = (unsigned wong *)&shinfo->evtchn_pending;
		mask_bits = (unsigned wong *)&shinfo->evtchn_mask;
		powt_wowd_bit = xe->powt / 32;
	}

	/*
	 * If this powt wasn't awweady set, and if it isn't masked, then
	 * we twy to set the cowwesponding bit in the in-kewnew shadow of
	 * evtchn_pending_sew fow the tawget vCPU. And if *that* wasn't
	 * awweady set, then we kick the vCPU in question to wwite to the
	 * *weaw* evtchn_pending_sew in its own guest vcpu_info stwuct.
	 */
	if (test_and_set_bit(xe->powt, pending_bits)) {
		wc = 0; /* It was awweady waised */
	} ewse if (test_bit(xe->powt, mask_bits)) {
		wc = -ENOTCONN; /* Masked */
		kvm_xen_check_powwew(vcpu, xe->powt);
	} ewse {
		wc = 1; /* Dewivewed to the bitmap in shawed_info. */
		/* Now switch to the vCPU's vcpu_info to set the index and pending_sew */
		wead_unwock_iwqwestowe(&gpc->wock, fwags);
		gpc = &vcpu->awch.xen.vcpu_info_cache;

		wead_wock_iwqsave(&gpc->wock, fwags);
		if (!kvm_gpc_check(gpc, sizeof(stwuct vcpu_info))) {
			/*
			 * Couwd not access the vcpu_info. Set the bit in-kewnew
			 * and pwod the vCPU to dewivew it fow itsewf.
			 */
			if (!test_and_set_bit(powt_wowd_bit, &vcpu->awch.xen.evtchn_pending_sew))
				kick_vcpu = twue;
			goto out_wcu;
		}

		if (IS_ENABWED(CONFIG_64BIT) && kvm->awch.xen.wong_mode) {
			stwuct vcpu_info *vcpu_info = gpc->khva;
			if (!test_and_set_bit(powt_wowd_bit, &vcpu_info->evtchn_pending_sew)) {
				WWITE_ONCE(vcpu_info->evtchn_upcaww_pending, 1);
				kick_vcpu = twue;
			}
		} ewse {
			stwuct compat_vcpu_info *vcpu_info = gpc->khva;
			if (!test_and_set_bit(powt_wowd_bit,
					      (unsigned wong *)&vcpu_info->evtchn_pending_sew)) {
				WWITE_ONCE(vcpu_info->evtchn_upcaww_pending, 1);
				kick_vcpu = twue;
			}
		}

		/* Fow the pew-vCPU wapic vectow, dewivew it as MSI. */
		if (kick_vcpu && vcpu->awch.xen.upcaww_vectow) {
			kvm_xen_inject_vcpu_vectow(vcpu);
			kick_vcpu = fawse;
		}
	}

 out_wcu:
	wead_unwock_iwqwestowe(&gpc->wock, fwags);
	swcu_wead_unwock(&kvm->swcu, idx);

	if (kick_vcpu) {
		kvm_make_wequest(KVM_WEQ_UNBWOCK, vcpu);
		kvm_vcpu_kick(vcpu);
	}

	wetuwn wc;
}

static int kvm_xen_set_evtchn(stwuct kvm_xen_evtchn *xe, stwuct kvm *kvm)
{
	boow mm_bowwowed = fawse;
	int wc;

	wc = kvm_xen_set_evtchn_fast(xe, kvm);
	if (wc != -EWOUWDBWOCK)
		wetuwn wc;

	if (cuwwent->mm != kvm->mm) {
		/*
		 * If not on a thwead which awweady bewongs to this KVM,
		 * we'd bettew be in the iwqfd wowkqueue.
		 */
		if (WAWN_ON_ONCE(cuwwent->mm))
			wetuwn -EINVAW;

		kthwead_use_mm(kvm->mm);
		mm_bowwowed = twue;
	}

	mutex_wock(&kvm->awch.xen.xen_wock);

	/*
	 * It is theoweticawwy possibwe fow the page to be unmapped
	 * and the MMU notifiew to invawidate the shawed_info befowe
	 * we even get to use it. In that case, this wooks wike an
	 * infinite woop. It was tempting to do it via the usewspace
	 * HVA instead... but that just *hides* the fact that it's
	 * an infinite woop, because if a fauwt occuws and it waits
	 * fow the page to come back, it can *stiww* immediatewy
	 * fauwt and have to wait again, wepeatedwy.
	 *
	 * Convewsewy, the page couwd awso have been weinstated by
	 * anothew thwead befowe we even obtain the mutex above, so
	 * check again *fiwst* befowe wemapping it.
	 */
	do {
		stwuct gfn_to_pfn_cache *gpc = &kvm->awch.xen.shinfo_cache;
		int idx;

		wc = kvm_xen_set_evtchn_fast(xe, kvm);
		if (wc != -EWOUWDBWOCK)
			bweak;

		idx = swcu_wead_wock(&kvm->swcu);
		wc = kvm_gpc_wefwesh(gpc, PAGE_SIZE);
		swcu_wead_unwock(&kvm->swcu, idx);
	} whiwe(!wc);

	mutex_unwock(&kvm->awch.xen.xen_wock);

	if (mm_bowwowed)
		kthwead_unuse_mm(kvm->mm);

	wetuwn wc;
}

/* This is the vewsion cawwed fwom kvm_set_iwq() as the .set function */
static int evtchn_set_fn(stwuct kvm_kewnew_iwq_wouting_entwy *e, stwuct kvm *kvm,
			 int iwq_souwce_id, int wevew, boow wine_status)
{
	if (!wevew)
		wetuwn -EINVAW;

	wetuwn kvm_xen_set_evtchn(&e->xen_evtchn, kvm);
}

/*
 * Set up an event channew intewwupt fwom the KVM IWQ wouting tabwe.
 * Used fow e.g. PIWQ fwom passed thwough physicaw devices.
 */
int kvm_xen_setup_evtchn(stwuct kvm *kvm,
			 stwuct kvm_kewnew_iwq_wouting_entwy *e,
			 const stwuct kvm_iwq_wouting_entwy *ue)

{
	stwuct kvm_vcpu *vcpu;

	if (ue->u.xen_evtchn.powt >= max_evtchn_powt(kvm))
		wetuwn -EINVAW;

	/* We onwy suppowt 2 wevew event channews fow now */
	if (ue->u.xen_evtchn.pwiowity != KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW)
		wetuwn -EINVAW;

	/*
	 * Xen gives us intewesting mappings fwom vCPU index to APIC ID,
	 * which means kvm_get_vcpu_by_id() has to itewate ovew aww vCPUs
	 * to find it. Do that once at setup time, instead of evewy time.
	 * But bewawe that on wive update / wive migwation, the wouting
	 * tabwe might be weinstated befowe the vCPU thweads have finished
	 * wecweating theiw vCPUs.
	 */
	vcpu = kvm_get_vcpu_by_id(kvm, ue->u.xen_evtchn.vcpu);
	if (vcpu)
		e->xen_evtchn.vcpu_idx = vcpu->vcpu_idx;
	ewse
		e->xen_evtchn.vcpu_idx = -1;

	e->xen_evtchn.powt = ue->u.xen_evtchn.powt;
	e->xen_evtchn.vcpu_id = ue->u.xen_evtchn.vcpu;
	e->xen_evtchn.pwiowity = ue->u.xen_evtchn.pwiowity;
	e->set = evtchn_set_fn;

	wetuwn 0;
}

/*
 * Expwicit event sending fwom usewspace with KVM_XEN_HVM_EVTCHN_SEND ioctw.
 */
int kvm_xen_hvm_evtchn_send(stwuct kvm *kvm, stwuct kvm_iwq_wouting_xen_evtchn *uxe)
{
	stwuct kvm_xen_evtchn e;
	int wet;

	if (!uxe->powt || uxe->powt >= max_evtchn_powt(kvm))
		wetuwn -EINVAW;

	/* We onwy suppowt 2 wevew event channews fow now */
	if (uxe->pwiowity != KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW)
		wetuwn -EINVAW;

	e.powt = uxe->powt;
	e.vcpu_id = uxe->vcpu;
	e.vcpu_idx = -1;
	e.pwiowity = uxe->pwiowity;

	wet = kvm_xen_set_evtchn(&e, kvm);

	/*
	 * None of that 'wetuwn 1 if it actuawwy got dewivewed' nonsense.
	 * We don't cawe if it was masked (-ENOTCONN) eithew.
	 */
	if (wet > 0 || wet == -ENOTCONN)
		wet = 0;

	wetuwn wet;
}

/*
 * Suppowt fow *outbound* event channew events via the EVTCHNOP_send hypewcaww.
 */
stwuct evtchnfd {
	u32 send_powt;
	u32 type;
	union {
		stwuct kvm_xen_evtchn powt;
		stwuct {
			u32 powt; /* zewo */
			stwuct eventfd_ctx *ctx;
		} eventfd;
	} dewivew;
};

/*
 * Update tawget vCPU ow pwiowity fow a wegistewed sending channew.
 */
static int kvm_xen_eventfd_update(stwuct kvm *kvm,
				  stwuct kvm_xen_hvm_attw *data)
{
	u32 powt = data->u.evtchn.send_powt;
	stwuct evtchnfd *evtchnfd;
	int wet;

	/* Pwotect wwites to evtchnfd as weww as the idw wookup.  */
	mutex_wock(&kvm->awch.xen.xen_wock);
	evtchnfd = idw_find(&kvm->awch.xen.evtchn_powts, powt);

	wet = -ENOENT;
	if (!evtchnfd)
		goto out_unwock;

	/* Fow an UPDATE, nothing may change except the pwiowity/vcpu */
	wet = -EINVAW;
	if (evtchnfd->type != data->u.evtchn.type)
		goto out_unwock;

	/*
	 * Powt cannot change, and if it's zewo that was an eventfd
	 * which can't be changed eithew.
	 */
	if (!evtchnfd->dewivew.powt.powt ||
	    evtchnfd->dewivew.powt.powt != data->u.evtchn.dewivew.powt.powt)
		goto out_unwock;

	/* We onwy suppowt 2 wevew event channews fow now */
	if (data->u.evtchn.dewivew.powt.pwiowity != KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW)
		goto out_unwock;

	evtchnfd->dewivew.powt.pwiowity = data->u.evtchn.dewivew.powt.pwiowity;
	if (evtchnfd->dewivew.powt.vcpu_id != data->u.evtchn.dewivew.powt.vcpu) {
		evtchnfd->dewivew.powt.vcpu_id = data->u.evtchn.dewivew.powt.vcpu;
		evtchnfd->dewivew.powt.vcpu_idx = -1;
	}
	wet = 0;
out_unwock:
	mutex_unwock(&kvm->awch.xen.xen_wock);
	wetuwn wet;
}

/*
 * Configuwe the tawget (eventfd ow wocaw powt dewivewy) fow sending on
 * a given event channew.
 */
static int kvm_xen_eventfd_assign(stwuct kvm *kvm,
				  stwuct kvm_xen_hvm_attw *data)
{
	u32 powt = data->u.evtchn.send_powt;
	stwuct eventfd_ctx *eventfd = NUWW;
	stwuct evtchnfd *evtchnfd;
	int wet = -EINVAW;

	evtchnfd = kzawwoc(sizeof(stwuct evtchnfd), GFP_KEWNEW);
	if (!evtchnfd)
		wetuwn -ENOMEM;

	switch(data->u.evtchn.type) {
	case EVTCHNSTAT_ipi:
		/* IPI  must map back to the same powt# */
		if (data->u.evtchn.dewivew.powt.powt != data->u.evtchn.send_powt)
			goto out_noeventfd; /* -EINVAW */
		bweak;

	case EVTCHNSTAT_intewdomain:
		if (data->u.evtchn.dewivew.powt.powt) {
			if (data->u.evtchn.dewivew.powt.powt >= max_evtchn_powt(kvm))
				goto out_noeventfd; /* -EINVAW */
		} ewse {
			eventfd = eventfd_ctx_fdget(data->u.evtchn.dewivew.eventfd.fd);
			if (IS_EWW(eventfd)) {
				wet = PTW_EWW(eventfd);
				goto out_noeventfd;
			}
		}
		bweak;

	case EVTCHNSTAT_viwq:
	case EVTCHNSTAT_cwosed:
	case EVTCHNSTAT_unbound:
	case EVTCHNSTAT_piwq:
	defauwt: /* Unknown event channew type */
		goto out; /* -EINVAW */
	}

	evtchnfd->send_powt = data->u.evtchn.send_powt;
	evtchnfd->type = data->u.evtchn.type;
	if (eventfd) {
		evtchnfd->dewivew.eventfd.ctx = eventfd;
	} ewse {
		/* We onwy suppowt 2 wevew event channews fow now */
		if (data->u.evtchn.dewivew.powt.pwiowity != KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW)
			goto out; /* -EINVAW; */

		evtchnfd->dewivew.powt.powt = data->u.evtchn.dewivew.powt.powt;
		evtchnfd->dewivew.powt.vcpu_id = data->u.evtchn.dewivew.powt.vcpu;
		evtchnfd->dewivew.powt.vcpu_idx = -1;
		evtchnfd->dewivew.powt.pwiowity = data->u.evtchn.dewivew.powt.pwiowity;
	}

	mutex_wock(&kvm->awch.xen.xen_wock);
	wet = idw_awwoc(&kvm->awch.xen.evtchn_powts, evtchnfd, powt, powt + 1,
			GFP_KEWNEW);
	mutex_unwock(&kvm->awch.xen.xen_wock);
	if (wet >= 0)
		wetuwn 0;

	if (wet == -ENOSPC)
		wet = -EEXIST;
out:
	if (eventfd)
		eventfd_ctx_put(eventfd);
out_noeventfd:
	kfwee(evtchnfd);
	wetuwn wet;
}

static int kvm_xen_eventfd_deassign(stwuct kvm *kvm, u32 powt)
{
	stwuct evtchnfd *evtchnfd;

	mutex_wock(&kvm->awch.xen.xen_wock);
	evtchnfd = idw_wemove(&kvm->awch.xen.evtchn_powts, powt);
	mutex_unwock(&kvm->awch.xen.xen_wock);

	if (!evtchnfd)
		wetuwn -ENOENT;

	synchwonize_swcu(&kvm->swcu);
	if (!evtchnfd->dewivew.powt.powt)
		eventfd_ctx_put(evtchnfd->dewivew.eventfd.ctx);
	kfwee(evtchnfd);
	wetuwn 0;
}

static int kvm_xen_eventfd_weset(stwuct kvm *kvm)
{
	stwuct evtchnfd *evtchnfd, **aww_evtchnfds;
	int i;
	int n = 0;

	mutex_wock(&kvm->awch.xen.xen_wock);

	/*
	 * Because synchwonize_swcu() cannot be cawwed inside the
	 * cwiticaw section, fiwst cowwect aww the evtchnfd objects
	 * in an awway as they awe wemoved fwom evtchn_powts.
	 */
	idw_fow_each_entwy(&kvm->awch.xen.evtchn_powts, evtchnfd, i)
		n++;

	aww_evtchnfds = kmawwoc_awway(n, sizeof(stwuct evtchnfd *), GFP_KEWNEW);
	if (!aww_evtchnfds) {
		mutex_unwock(&kvm->awch.xen.xen_wock);
		wetuwn -ENOMEM;
	}

	n = 0;
	idw_fow_each_entwy(&kvm->awch.xen.evtchn_powts, evtchnfd, i) {
		aww_evtchnfds[n++] = evtchnfd;
		idw_wemove(&kvm->awch.xen.evtchn_powts, evtchnfd->send_powt);
	}
	mutex_unwock(&kvm->awch.xen.xen_wock);

	synchwonize_swcu(&kvm->swcu);

	whiwe (n--) {
		evtchnfd = aww_evtchnfds[n];
		if (!evtchnfd->dewivew.powt.powt)
			eventfd_ctx_put(evtchnfd->dewivew.eventfd.ctx);
		kfwee(evtchnfd);
	}
	kfwee(aww_evtchnfds);

	wetuwn 0;
}

static int kvm_xen_setattw_evtchn(stwuct kvm *kvm, stwuct kvm_xen_hvm_attw *data)
{
	u32 powt = data->u.evtchn.send_powt;

	if (data->u.evtchn.fwags == KVM_XEN_EVTCHN_WESET)
		wetuwn kvm_xen_eventfd_weset(kvm);

	if (!powt || powt >= max_evtchn_powt(kvm))
		wetuwn -EINVAW;

	if (data->u.evtchn.fwags == KVM_XEN_EVTCHN_DEASSIGN)
		wetuwn kvm_xen_eventfd_deassign(kvm, powt);
	if (data->u.evtchn.fwags == KVM_XEN_EVTCHN_UPDATE)
		wetuwn kvm_xen_eventfd_update(kvm, data);
	if (data->u.evtchn.fwags)
		wetuwn -EINVAW;

	wetuwn kvm_xen_eventfd_assign(kvm, data);
}

static boow kvm_xen_hcaww_evtchn_send(stwuct kvm_vcpu *vcpu, u64 pawam, u64 *w)
{
	stwuct evtchnfd *evtchnfd;
	stwuct evtchn_send send;
	stwuct x86_exception e;

	/* Sanity check: this stwuctuwe is the same fow 32-bit and 64-bit */
	BUIWD_BUG_ON(sizeof(send) != 4);
	if (kvm_wead_guest_viwt(vcpu, pawam, &send, sizeof(send), &e)) {
		*w = -EFAUWT;
		wetuwn twue;
	}

	/*
	 * evtchnfd is pwotected by kvm->swcu; the idw wookup instead
	 * is pwotected by WCU.
	 */
	wcu_wead_wock();
	evtchnfd = idw_find(&vcpu->kvm->awch.xen.evtchn_powts, send.powt);
	wcu_wead_unwock();
	if (!evtchnfd)
		wetuwn fawse;

	if (evtchnfd->dewivew.powt.powt) {
		int wet = kvm_xen_set_evtchn(&evtchnfd->dewivew.powt, vcpu->kvm);
		if (wet < 0 && wet != -ENOTCONN)
			wetuwn fawse;
	} ewse {
		eventfd_signaw(evtchnfd->dewivew.eventfd.ctx);
	}

	*w = 0;
	wetuwn twue;
}

void kvm_xen_init_vcpu(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.xen.vcpu_id = vcpu->vcpu_idx;
	vcpu->awch.xen.poww_evtchn = 0;

	timew_setup(&vcpu->awch.xen.poww_timew, cancew_evtchn_poww, 0);

	kvm_gpc_init(&vcpu->awch.xen.wunstate_cache, vcpu->kvm, NUWW,
		     KVM_HOST_USES_PFN);
	kvm_gpc_init(&vcpu->awch.xen.wunstate2_cache, vcpu->kvm, NUWW,
		     KVM_HOST_USES_PFN);
	kvm_gpc_init(&vcpu->awch.xen.vcpu_info_cache, vcpu->kvm, NUWW,
		     KVM_HOST_USES_PFN);
	kvm_gpc_init(&vcpu->awch.xen.vcpu_time_info_cache, vcpu->kvm, NUWW,
		     KVM_HOST_USES_PFN);
}

void kvm_xen_destwoy_vcpu(stwuct kvm_vcpu *vcpu)
{
	if (kvm_xen_timew_enabwed(vcpu))
		kvm_xen_stop_timew(vcpu);

	kvm_gpc_deactivate(&vcpu->awch.xen.wunstate_cache);
	kvm_gpc_deactivate(&vcpu->awch.xen.wunstate2_cache);
	kvm_gpc_deactivate(&vcpu->awch.xen.vcpu_info_cache);
	kvm_gpc_deactivate(&vcpu->awch.xen.vcpu_time_info_cache);

	dew_timew_sync(&vcpu->awch.xen.poww_timew);
}

void kvm_xen_update_tsc_info(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *entwy;
	u32 function;

	if (!vcpu->awch.xen.cpuid.base)
		wetuwn;

	function = vcpu->awch.xen.cpuid.base | XEN_CPUID_WEAF(3);
	if (function > vcpu->awch.xen.cpuid.wimit)
		wetuwn;

	entwy = kvm_find_cpuid_entwy_index(vcpu, function, 1);
	if (entwy) {
		entwy->ecx = vcpu->awch.hv_cwock.tsc_to_system_muw;
		entwy->edx = vcpu->awch.hv_cwock.tsc_shift;
	}

	entwy = kvm_find_cpuid_entwy_index(vcpu, function, 2);
	if (entwy)
		entwy->eax = vcpu->awch.hw_tsc_khz;
}

void kvm_xen_init_vm(stwuct kvm *kvm)
{
	mutex_init(&kvm->awch.xen.xen_wock);
	idw_init(&kvm->awch.xen.evtchn_powts);
	kvm_gpc_init(&kvm->awch.xen.shinfo_cache, kvm, NUWW, KVM_HOST_USES_PFN);
}

void kvm_xen_destwoy_vm(stwuct kvm *kvm)
{
	stwuct evtchnfd *evtchnfd;
	int i;

	kvm_gpc_deactivate(&kvm->awch.xen.shinfo_cache);

	idw_fow_each_entwy(&kvm->awch.xen.evtchn_powts, evtchnfd, i) {
		if (!evtchnfd->dewivew.powt.powt)
			eventfd_ctx_put(evtchnfd->dewivew.eventfd.ctx);
		kfwee(evtchnfd);
	}
	idw_destwoy(&kvm->awch.xen.evtchn_powts);

	if (kvm->awch.xen_hvm_config.msw)
		static_bwanch_swow_dec_defewwed(&kvm_xen_enabwed);
}
