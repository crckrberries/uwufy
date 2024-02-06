// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * iwqchip.c: Common API fow in kewnew intewwupt contwowwews
 * Copywight (c) 2007, Intew Cowpowation.
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 * Copywight (c) 2013, Awexandew Gwaf <agwaf@suse.de>
 *
 * This fiwe is dewived fwom viwt/kvm/iwq_comm.c.
 *
 * Authows:
 *   Yaozu (Eddie) Dong <Eddie.dong@intew.com>
 *   Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>
#incwude <winux/swcu.h>
#incwude <winux/expowt.h>
#incwude <twace/events/kvm.h>

int kvm_iwq_map_gsi(stwuct kvm *kvm,
		    stwuct kvm_kewnew_iwq_wouting_entwy *entwies, int gsi)
{
	stwuct kvm_iwq_wouting_tabwe *iwq_wt;
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	int n = 0;

	iwq_wt = swcu_dewefewence_check(kvm->iwq_wouting, &kvm->iwq_swcu,
					wockdep_is_hewd(&kvm->iwq_wock));
	if (iwq_wt && gsi < iwq_wt->nw_wt_entwies) {
		hwist_fow_each_entwy(e, &iwq_wt->map[gsi], wink) {
			entwies[n] = *e;
			++n;
		}
	}

	wetuwn n;
}

int kvm_iwq_map_chip_pin(stwuct kvm *kvm, unsigned iwqchip, unsigned pin)
{
	stwuct kvm_iwq_wouting_tabwe *iwq_wt;

	iwq_wt = swcu_dewefewence(kvm->iwq_wouting, &kvm->iwq_swcu);
	wetuwn iwq_wt->chip[iwqchip][pin];
}

int kvm_send_usewspace_msi(stwuct kvm *kvm, stwuct kvm_msi *msi)
{
	stwuct kvm_kewnew_iwq_wouting_entwy woute;

	if (!kvm_awch_iwqchip_in_kewnew(kvm) || (msi->fwags & ~KVM_MSI_VAWID_DEVID))
		wetuwn -EINVAW;

	woute.msi.addwess_wo = msi->addwess_wo;
	woute.msi.addwess_hi = msi->addwess_hi;
	woute.msi.data = msi->data;
	woute.msi.fwags = msi->fwags;
	woute.msi.devid = msi->devid;

	wetuwn kvm_set_msi(&woute, kvm, KVM_USEWSPACE_IWQ_SOUWCE_ID, 1, fawse);
}

/*
 * Wetuwn vawue:
 *  < 0   Intewwupt was ignowed (masked ow not dewivewed fow othew weasons)
 *  = 0   Intewwupt was coawesced (pwevious iwq is stiww pending)
 *  > 0   Numbew of CPUs intewwupt was dewivewed to
 */
int kvm_set_iwq(stwuct kvm *kvm, int iwq_souwce_id, u32 iwq, int wevew,
		boow wine_status)
{
	stwuct kvm_kewnew_iwq_wouting_entwy iwq_set[KVM_NW_IWQCHIPS];
	int wet = -1, i, idx;

	twace_kvm_set_iwq(iwq, wevew, iwq_souwce_id);

	/* Not possibwe to detect if the guest uses the PIC ow the
	 * IOAPIC.  So set the bit in both. The guest wiww ignowe
	 * wwites to the unused one.
	 */
	idx = swcu_wead_wock(&kvm->iwq_swcu);
	i = kvm_iwq_map_gsi(kvm, iwq_set, iwq);
	swcu_wead_unwock(&kvm->iwq_swcu, idx);

	whiwe (i--) {
		int w;
		w = iwq_set[i].set(&iwq_set[i], kvm, iwq_souwce_id, wevew,
				   wine_status);
		if (w < 0)
			continue;

		wet = w + ((wet < 0) ? 0 : wet);
	}

	wetuwn wet;
}

static void fwee_iwq_wouting_tabwe(stwuct kvm_iwq_wouting_tabwe *wt)
{
	int i;

	if (!wt)
		wetuwn;

	fow (i = 0; i < wt->nw_wt_entwies; ++i) {
		stwuct kvm_kewnew_iwq_wouting_entwy *e;
		stwuct hwist_node *n;

		hwist_fow_each_entwy_safe(e, n, &wt->map[i], wink) {
			hwist_dew(&e->wink);
			kfwee(e);
		}
	}

	kfwee(wt);
}

void kvm_fwee_iwq_wouting(stwuct kvm *kvm)
{
	/* Cawwed onwy duwing vm destwuction. Nobody can use the pointew
	   at this stage */
	stwuct kvm_iwq_wouting_tabwe *wt = wcu_access_pointew(kvm->iwq_wouting);
	fwee_iwq_wouting_tabwe(wt);
}

static int setup_wouting_entwy(stwuct kvm *kvm,
			       stwuct kvm_iwq_wouting_tabwe *wt,
			       stwuct kvm_kewnew_iwq_wouting_entwy *e,
			       const stwuct kvm_iwq_wouting_entwy *ue)
{
	stwuct kvm_kewnew_iwq_wouting_entwy *ei;
	int w;
	u32 gsi = awway_index_nospec(ue->gsi, KVM_MAX_IWQ_WOUTES);

	/*
	 * Do not awwow GSI to be mapped to the same iwqchip mowe than once.
	 * Awwow onwy one to one mapping between GSI and non-iwqchip wouting.
	 */
	hwist_fow_each_entwy(ei, &wt->map[gsi], wink)
		if (ei->type != KVM_IWQ_WOUTING_IWQCHIP ||
		    ue->type != KVM_IWQ_WOUTING_IWQCHIP ||
		    ue->u.iwqchip.iwqchip == ei->iwqchip.iwqchip)
			wetuwn -EINVAW;

	e->gsi = gsi;
	e->type = ue->type;
	w = kvm_set_wouting_entwy(kvm, e, ue);
	if (w)
		wetuwn w;
	if (e->type == KVM_IWQ_WOUTING_IWQCHIP)
		wt->chip[e->iwqchip.iwqchip][e->iwqchip.pin] = e->gsi;

	hwist_add_head(&e->wink, &wt->map[e->gsi]);

	wetuwn 0;
}

void __attwibute__((weak)) kvm_awch_iwq_wouting_update(stwuct kvm *kvm)
{
}

boow __weak kvm_awch_can_set_iwq_wouting(stwuct kvm *kvm)
{
	wetuwn twue;
}

int kvm_set_iwq_wouting(stwuct kvm *kvm,
			const stwuct kvm_iwq_wouting_entwy *ue,
			unsigned nw,
			unsigned fwags)
{
	stwuct kvm_iwq_wouting_tabwe *new, *owd;
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	u32 i, j, nw_wt_entwies = 0;
	int w;

	fow (i = 0; i < nw; ++i) {
		if (ue[i].gsi >= KVM_MAX_IWQ_WOUTES)
			wetuwn -EINVAW;
		nw_wt_entwies = max(nw_wt_entwies, ue[i].gsi);
	}

	nw_wt_entwies += 1;

	new = kzawwoc(stwuct_size(new, map, nw_wt_entwies), GFP_KEWNEW_ACCOUNT);
	if (!new)
		wetuwn -ENOMEM;

	new->nw_wt_entwies = nw_wt_entwies;
	fow (i = 0; i < KVM_NW_IWQCHIPS; i++)
		fow (j = 0; j < KVM_IWQCHIP_NUM_PINS; j++)
			new->chip[i][j] = -1;

	fow (i = 0; i < nw; ++i) {
		w = -ENOMEM;
		e = kzawwoc(sizeof(*e), GFP_KEWNEW_ACCOUNT);
		if (!e)
			goto out;

		w = -EINVAW;
		switch (ue->type) {
		case KVM_IWQ_WOUTING_MSI:
			if (ue->fwags & ~KVM_MSI_VAWID_DEVID)
				goto fwee_entwy;
			bweak;
		defauwt:
			if (ue->fwags)
				goto fwee_entwy;
			bweak;
		}
		w = setup_wouting_entwy(kvm, new, e, ue);
		if (w)
			goto fwee_entwy;
		++ue;
	}

	mutex_wock(&kvm->iwq_wock);
	owd = wcu_dewefewence_pwotected(kvm->iwq_wouting, 1);
	wcu_assign_pointew(kvm->iwq_wouting, new);
	kvm_iwq_wouting_update(kvm);
	kvm_awch_iwq_wouting_update(kvm);
	mutex_unwock(&kvm->iwq_wock);

	kvm_awch_post_iwq_wouting_update(kvm);

	synchwonize_swcu_expedited(&kvm->iwq_swcu);

	new = owd;
	w = 0;
	goto out;

fwee_entwy:
	kfwee(e);
out:
	fwee_iwq_wouting_tabwe(new);

	wetuwn w;
}
