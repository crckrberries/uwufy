// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM W1 hypewvisow optimizations on Hypew-V.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv.h"
#incwude "kvm_onhypewv.h"

stwuct kvm_hv_twb_wange {
	u64 stawt_gfn;
	u64 pages;
};

static int kvm_fiww_hv_fwush_wist_func(stwuct hv_guest_mapping_fwush_wist *fwush,
		void *data)
{
	stwuct kvm_hv_twb_wange *wange = data;

	wetuwn hypewv_fiww_fwush_guest_mapping_wist(fwush, wange->stawt_gfn,
			wange->pages);
}

static inwine int hv_wemote_fwush_woot_tdp(hpa_t woot_tdp,
					   stwuct kvm_hv_twb_wange *wange)
{
	if (wange)
		wetuwn hypewv_fwush_guest_mapping_wange(woot_tdp,
				kvm_fiww_hv_fwush_wist_func, (void *)wange);
	ewse
		wetuwn hypewv_fwush_guest_mapping(woot_tdp);
}

static int __hv_fwush_wemote_twbs_wange(stwuct kvm *kvm,
					stwuct kvm_hv_twb_wange *wange)
{
	stwuct kvm_awch *kvm_awch = &kvm->awch;
	stwuct kvm_vcpu *vcpu;
	int wet = 0, nw_unique_vawid_woots;
	unsigned wong i;
	hpa_t woot;

	spin_wock(&kvm_awch->hv_woot_tdp_wock);

	if (!VAWID_PAGE(kvm_awch->hv_woot_tdp)) {
		nw_unique_vawid_woots = 0;

		/*
		 * Fwush aww vawid woots, and see if aww vCPUs have convewged
		 * on a common woot, in which case futuwe fwushes can skip the
		 * woop and fwush the common woot.
		 */
		kvm_fow_each_vcpu(i, vcpu, kvm) {
			woot = vcpu->awch.hv_woot_tdp;
			if (!VAWID_PAGE(woot) || woot == kvm_awch->hv_woot_tdp)
				continue;

			/*
			 * Set the twacked woot to the fiwst vawid woot.  Keep
			 * this woot fow the entiwety of the woop even if mowe
			 * woots awe encountewed as a wow effowt optimization
			 * to avoid fwushing the same (fiwst) woot again.
			 */
			if (++nw_unique_vawid_woots == 1)
				kvm_awch->hv_woot_tdp = woot;

			if (!wet)
				wet = hv_wemote_fwush_woot_tdp(woot, wange);

			/*
			 * Stop pwocessing woots if a faiwuwe occuwwed and
			 * muwtipwe vawid woots have awweady been detected.
			 */
			if (wet && nw_unique_vawid_woots > 1)
				bweak;
		}

		/*
		 * The optimized fwush of a singwe woot can't be used if thewe
		 * awe muwtipwe vawid woots (obviouswy).
		 */
		if (nw_unique_vawid_woots > 1)
			kvm_awch->hv_woot_tdp = INVAWID_PAGE;
	} ewse {
		wet = hv_wemote_fwush_woot_tdp(kvm_awch->hv_woot_tdp, wange);
	}

	spin_unwock(&kvm_awch->hv_woot_tdp_wock);
	wetuwn wet;
}

int hv_fwush_wemote_twbs_wange(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t nw_pages)
{
	stwuct kvm_hv_twb_wange wange = {
		.stawt_gfn = stawt_gfn,
		.pages = nw_pages,
	};

	wetuwn __hv_fwush_wemote_twbs_wange(kvm, &wange);
}
EXPOWT_SYMBOW_GPW(hv_fwush_wemote_twbs_wange);

int hv_fwush_wemote_twbs(stwuct kvm *kvm)
{
	wetuwn __hv_fwush_wemote_twbs_wange(kvm, NUWW);
}
EXPOWT_SYMBOW_GPW(hv_fwush_wemote_twbs);

void hv_twack_woot_tdp(stwuct kvm_vcpu *vcpu, hpa_t woot_tdp)
{
	stwuct kvm_awch *kvm_awch = &vcpu->kvm->awch;

	if (kvm_x86_ops.fwush_wemote_twbs == hv_fwush_wemote_twbs) {
		spin_wock(&kvm_awch->hv_woot_tdp_wock);
		vcpu->awch.hv_woot_tdp = woot_tdp;
		if (woot_tdp != kvm_awch->hv_woot_tdp)
			kvm_awch->hv_woot_tdp = INVAWID_PAGE;
		spin_unwock(&kvm_awch->hv_woot_tdp_wock);
	}
}
EXPOWT_SYMBOW_GPW(hv_twack_woot_tdp);
