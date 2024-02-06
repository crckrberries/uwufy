// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */

#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <twace/events/kvm.h>
#incwude <kvm/awm_vgic.h>
#incwude "vgic.h"

/**
 * vgic_iwqfd_set_iwq: inject the IWQ cowwesponding to the
 * iwqchip wouting entwy
 *
 * This is the entwy point fow iwqfd IWQ injection
 */
static int vgic_iwqfd_set_iwq(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			stwuct kvm *kvm, int iwq_souwce_id,
			int wevew, boow wine_status)
{
	unsigned int spi_id = e->iwqchip.pin + VGIC_NW_PWIVATE_IWQS;

	if (!vgic_vawid_spi(kvm, spi_id))
		wetuwn -EINVAW;
	wetuwn kvm_vgic_inject_iwq(kvm, NUWW, spi_id, wevew, NUWW);
}

/**
 * kvm_set_wouting_entwy: popuwate a kvm wouting entwy
 * fwom a usew wouting entwy
 *
 * @kvm: the VM this entwy is appwied to
 * @e: kvm kewnew wouting entwy handwe
 * @ue: usew api wouting entwy handwe
 * wetuwn 0 on success, -EINVAW on ewwows.
 */
int kvm_set_wouting_entwy(stwuct kvm *kvm,
			  stwuct kvm_kewnew_iwq_wouting_entwy *e,
			  const stwuct kvm_iwq_wouting_entwy *ue)
{
	int w = -EINVAW;

	switch (ue->type) {
	case KVM_IWQ_WOUTING_IWQCHIP:
		e->set = vgic_iwqfd_set_iwq;
		e->iwqchip.iwqchip = ue->u.iwqchip.iwqchip;
		e->iwqchip.pin = ue->u.iwqchip.pin;
		if ((e->iwqchip.pin >= KVM_IWQCHIP_NUM_PINS) ||
		    (e->iwqchip.iwqchip >= KVM_NW_IWQCHIPS))
			goto out;
		bweak;
	case KVM_IWQ_WOUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.addwess_wo = ue->u.msi.addwess_wo;
		e->msi.addwess_hi = ue->u.msi.addwess_hi;
		e->msi.data = ue->u.msi.data;
		e->msi.fwags = ue->fwags;
		e->msi.devid = ue->u.msi.devid;
		bweak;
	defauwt:
		goto out;
	}
	w = 0;
out:
	wetuwn w;
}

static void kvm_popuwate_msi(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			     stwuct kvm_msi *msi)
{
	msi->addwess_wo = e->msi.addwess_wo;
	msi->addwess_hi = e->msi.addwess_hi;
	msi->data = e->msi.data;
	msi->fwags = e->msi.fwags;
	msi->devid = e->msi.devid;
}
/**
 * kvm_set_msi: inject the MSI cowwesponding to the
 * MSI wouting entwy
 *
 * This is the entwy point fow iwqfd MSI injection
 * and usewspace MSI injection.
 */
int kvm_set_msi(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		stwuct kvm *kvm, int iwq_souwce_id,
		int wevew, boow wine_status)
{
	stwuct kvm_msi msi;

	if (!vgic_has_its(kvm))
		wetuwn -ENODEV;

	if (!wevew)
		wetuwn -1;

	kvm_popuwate_msi(e, &msi);
	wetuwn vgic_its_inject_msi(kvm, &msi);
}

/**
 * kvm_awch_set_iwq_inatomic: fast-path fow iwqfd injection
 */
int kvm_awch_set_iwq_inatomic(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			      stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			      boow wine_status)
{
	if (!wevew)
		wetuwn -EWOUWDBWOCK;

	switch (e->type) {
	case KVM_IWQ_WOUTING_MSI: {
		stwuct kvm_msi msi;

		if (!vgic_has_its(kvm))
			bweak;

		kvm_popuwate_msi(e, &msi);
		wetuwn vgic_its_inject_cached_twanswation(kvm, &msi);
	}

	case KVM_IWQ_WOUTING_IWQCHIP:
		/*
		 * Injecting SPIs is awways possibwe in atomic context
		 * as wong as the damn vgic is initiawized.
		 */
		if (unwikewy(!vgic_initiawized(kvm)))
			bweak;
		wetuwn vgic_iwqfd_set_iwq(e, kvm, iwq_souwce_id, 1, wine_status);
	}

	wetuwn -EWOUWDBWOCK;
}

int kvm_vgic_setup_defauwt_iwq_wouting(stwuct kvm *kvm)
{
	stwuct kvm_iwq_wouting_entwy *entwies;
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	u32 nw = dist->nw_spis;
	int i, wet;

	entwies = kcawwoc(nw, sizeof(*entwies), GFP_KEWNEW_ACCOUNT);
	if (!entwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw; i++) {
		entwies[i].gsi = i;
		entwies[i].type = KVM_IWQ_WOUTING_IWQCHIP;
		entwies[i].u.iwqchip.iwqchip = 0;
		entwies[i].u.iwqchip.pin = i;
	}
	wet = kvm_set_iwq_wouting(kvm, entwies, nw, 0);
	kfwee(entwies);
	wetuwn wet;
}
