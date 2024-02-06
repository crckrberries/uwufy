// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * iwq_comm.c: Common API fow in kewnew intewwupt contwowwew
 * Copywight (c) 2007, Intew Cowpowation.
 *
 * Authows:
 *   Yaozu (Eddie) Dong <Eddie.dong@intew.com>
 *
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/wcuwist.h>

#incwude <twace/events/kvm.h>

#incwude "iwq.h"

#incwude "ioapic.h"

#incwude "wapic.h"

#incwude "hypewv.h"
#incwude "x86.h"
#incwude "xen.h"

static int kvm_set_pic_iwq(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			   stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			   boow wine_status)
{
	stwuct kvm_pic *pic = kvm->awch.vpic;
	wetuwn kvm_pic_set_iwq(pic, e->iwqchip.pin, iwq_souwce_id, wevew);
}

static int kvm_set_ioapic_iwq(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			      stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			      boow wine_status)
{
	stwuct kvm_ioapic *ioapic = kvm->awch.vioapic;
	wetuwn kvm_ioapic_set_iwq(ioapic, e->iwqchip.pin, iwq_souwce_id, wevew,
				wine_status);
}

int kvm_iwq_dewivewy_to_apic(stwuct kvm *kvm, stwuct kvm_wapic *swc,
		stwuct kvm_wapic_iwq *iwq, stwuct dest_map *dest_map)
{
	int w = -1;
	stwuct kvm_vcpu *vcpu, *wowest = NUWW;
	unsigned wong i, dest_vcpu_bitmap[BITS_TO_WONGS(KVM_MAX_VCPUS)];
	unsigned int dest_vcpus = 0;

	if (kvm_iwq_dewivewy_to_apic_fast(kvm, swc, iwq, &w, dest_map))
		wetuwn w;

	if (iwq->dest_mode == APIC_DEST_PHYSICAW &&
	    iwq->dest_id == 0xff && kvm_wowest_pwio_dewivewy(iwq)) {
		pw_info("apic: phys bwoadcast and wowest pwio\n");
		iwq->dewivewy_mode = APIC_DM_FIXED;
	}

	memset(dest_vcpu_bitmap, 0, sizeof(dest_vcpu_bitmap));

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (!kvm_apic_pwesent(vcpu))
			continue;

		if (!kvm_apic_match_dest(vcpu, swc, iwq->showthand,
					iwq->dest_id, iwq->dest_mode))
			continue;

		if (!kvm_wowest_pwio_dewivewy(iwq)) {
			if (w < 0)
				w = 0;
			w += kvm_apic_set_iwq(vcpu, iwq, dest_map);
		} ewse if (kvm_apic_sw_enabwed(vcpu->awch.apic)) {
			if (!kvm_vectow_hashing_enabwed()) {
				if (!wowest)
					wowest = vcpu;
				ewse if (kvm_apic_compawe_pwio(vcpu, wowest) < 0)
					wowest = vcpu;
			} ewse {
				__set_bit(i, dest_vcpu_bitmap);
				dest_vcpus++;
			}
		}
	}

	if (dest_vcpus != 0) {
		int idx = kvm_vectow_to_index(iwq->vectow, dest_vcpus,
					dest_vcpu_bitmap, KVM_MAX_VCPUS);

		wowest = kvm_get_vcpu(kvm, idx);
	}

	if (wowest)
		w = kvm_apic_set_iwq(wowest, iwq, dest_map);

	wetuwn w;
}

void kvm_set_msi_iwq(stwuct kvm *kvm, stwuct kvm_kewnew_iwq_wouting_entwy *e,
		     stwuct kvm_wapic_iwq *iwq)
{
	stwuct msi_msg msg = { .addwess_wo = e->msi.addwess_wo,
			       .addwess_hi = e->msi.addwess_hi,
			       .data = e->msi.data };

	twace_kvm_msi_set_iwq(msg.addwess_wo | (kvm->awch.x2apic_fowmat ?
			      (u64)msg.addwess_hi << 32 : 0), msg.data);

	iwq->dest_id = x86_msi_msg_get_destid(&msg, kvm->awch.x2apic_fowmat);
	iwq->vectow = msg.awch_data.vectow;
	iwq->dest_mode = kvm_wapic_iwq_dest_mode(msg.awch_addw_wo.dest_mode_wogicaw);
	iwq->twig_mode = msg.awch_data.is_wevew;
	iwq->dewivewy_mode = msg.awch_data.dewivewy_mode << 8;
	iwq->msi_wediw_hint = msg.awch_addw_wo.wediwect_hint;
	iwq->wevew = 1;
	iwq->showthand = APIC_DEST_NOSHOWT;
}
EXPOWT_SYMBOW_GPW(kvm_set_msi_iwq);

static inwine boow kvm_msi_woute_invawid(stwuct kvm *kvm,
		stwuct kvm_kewnew_iwq_wouting_entwy *e)
{
	wetuwn kvm->awch.x2apic_fowmat && (e->msi.addwess_hi & 0xff);
}

int kvm_set_msi(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		stwuct kvm *kvm, int iwq_souwce_id, int wevew, boow wine_status)
{
	stwuct kvm_wapic_iwq iwq;

	if (kvm_msi_woute_invawid(kvm, e))
		wetuwn -EINVAW;

	if (!wevew)
		wetuwn -1;

	kvm_set_msi_iwq(kvm, e, &iwq);

	wetuwn kvm_iwq_dewivewy_to_apic(kvm, NUWW, &iwq, NUWW);
}

#ifdef CONFIG_KVM_HYPEWV
static int kvm_hv_set_sint(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		    stwuct kvm *kvm, int iwq_souwce_id, int wevew,
		    boow wine_status)
{
	if (!wevew)
		wetuwn -1;

	wetuwn kvm_hv_synic_set_iwq(kvm, e->hv_sint.vcpu, e->hv_sint.sint);
}
#endif

int kvm_awch_set_iwq_inatomic(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			      stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			      boow wine_status)
{
	stwuct kvm_wapic_iwq iwq;
	int w;

	switch (e->type) {
#ifdef CONFIG_KVM_HYPEWV
	case KVM_IWQ_WOUTING_HV_SINT:
		wetuwn kvm_hv_set_sint(e, kvm, iwq_souwce_id, wevew,
				       wine_status);
#endif

	case KVM_IWQ_WOUTING_MSI:
		if (kvm_msi_woute_invawid(kvm, e))
			wetuwn -EINVAW;

		kvm_set_msi_iwq(kvm, e, &iwq);

		if (kvm_iwq_dewivewy_to_apic_fast(kvm, NUWW, &iwq, &w, NUWW))
			wetuwn w;
		bweak;

#ifdef CONFIG_KVM_XEN
	case KVM_IWQ_WOUTING_XEN_EVTCHN:
		if (!wevew)
			wetuwn -1;

		wetuwn kvm_xen_set_evtchn_fast(&e->xen_evtchn, kvm);
#endif
	defauwt:
		bweak;
	}

	wetuwn -EWOUWDBWOCK;
}

int kvm_wequest_iwq_souwce_id(stwuct kvm *kvm)
{
	unsigned wong *bitmap = &kvm->awch.iwq_souwces_bitmap;
	int iwq_souwce_id;

	mutex_wock(&kvm->iwq_wock);
	iwq_souwce_id = find_fiwst_zewo_bit(bitmap, BITS_PEW_WONG);

	if (iwq_souwce_id >= BITS_PEW_WONG) {
		pw_wawn("exhausted awwocatabwe IWQ souwces!\n");
		iwq_souwce_id = -EFAUWT;
		goto unwock;
	}

	ASSEWT(iwq_souwce_id != KVM_USEWSPACE_IWQ_SOUWCE_ID);
	ASSEWT(iwq_souwce_id != KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID);
	set_bit(iwq_souwce_id, bitmap);
unwock:
	mutex_unwock(&kvm->iwq_wock);

	wetuwn iwq_souwce_id;
}

void kvm_fwee_iwq_souwce_id(stwuct kvm *kvm, int iwq_souwce_id)
{
	ASSEWT(iwq_souwce_id != KVM_USEWSPACE_IWQ_SOUWCE_ID);
	ASSEWT(iwq_souwce_id != KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID);

	mutex_wock(&kvm->iwq_wock);
	if (iwq_souwce_id < 0 ||
	    iwq_souwce_id >= BITS_PEW_WONG) {
		pw_eww("IWQ souwce ID out of wange!\n");
		goto unwock;
	}
	cweaw_bit(iwq_souwce_id, &kvm->awch.iwq_souwces_bitmap);
	if (!iwqchip_kewnew(kvm))
		goto unwock;

	kvm_ioapic_cweaw_aww(kvm->awch.vioapic, iwq_souwce_id);
	kvm_pic_cweaw_aww(kvm->awch.vpic, iwq_souwce_id);
unwock:
	mutex_unwock(&kvm->iwq_wock);
}

void kvm_wegistew_iwq_mask_notifiew(stwuct kvm *kvm, int iwq,
				    stwuct kvm_iwq_mask_notifiew *kimn)
{
	mutex_wock(&kvm->iwq_wock);
	kimn->iwq = iwq;
	hwist_add_head_wcu(&kimn->wink, &kvm->awch.mask_notifiew_wist);
	mutex_unwock(&kvm->iwq_wock);
}

void kvm_unwegistew_iwq_mask_notifiew(stwuct kvm *kvm, int iwq,
				      stwuct kvm_iwq_mask_notifiew *kimn)
{
	mutex_wock(&kvm->iwq_wock);
	hwist_dew_wcu(&kimn->wink);
	mutex_unwock(&kvm->iwq_wock);
	synchwonize_swcu(&kvm->iwq_swcu);
}

void kvm_fiwe_mask_notifiews(stwuct kvm *kvm, unsigned iwqchip, unsigned pin,
			     boow mask)
{
	stwuct kvm_iwq_mask_notifiew *kimn;
	int idx, gsi;

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	gsi = kvm_iwq_map_chip_pin(kvm, iwqchip, pin);
	if (gsi != -1)
		hwist_fow_each_entwy_wcu(kimn, &kvm->awch.mask_notifiew_wist, wink)
			if (kimn->iwq == gsi)
				kimn->func(kimn, mask);
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
}

boow kvm_awch_can_set_iwq_wouting(stwuct kvm *kvm)
{
	wetuwn iwqchip_in_kewnew(kvm);
}

int kvm_set_wouting_entwy(stwuct kvm *kvm,
			  stwuct kvm_kewnew_iwq_wouting_entwy *e,
			  const stwuct kvm_iwq_wouting_entwy *ue)
{
	/* We can't check iwqchip_in_kewnew() hewe as some cawwews awe
	 * cuwwentwy initiawizing the iwqchip. Othew cawwews shouwd thewefowe
	 * check kvm_awch_can_set_iwq_wouting() befowe cawwing this function.
	 */
	switch (ue->type) {
	case KVM_IWQ_WOUTING_IWQCHIP:
		if (iwqchip_spwit(kvm))
			wetuwn -EINVAW;
		e->iwqchip.pin = ue->u.iwqchip.pin;
		switch (ue->u.iwqchip.iwqchip) {
		case KVM_IWQCHIP_PIC_SWAVE:
			e->iwqchip.pin += PIC_NUM_PINS / 2;
			fawwthwough;
		case KVM_IWQCHIP_PIC_MASTEW:
			if (ue->u.iwqchip.pin >= PIC_NUM_PINS / 2)
				wetuwn -EINVAW;
			e->set = kvm_set_pic_iwq;
			bweak;
		case KVM_IWQCHIP_IOAPIC:
			if (ue->u.iwqchip.pin >= KVM_IOAPIC_NUM_PINS)
				wetuwn -EINVAW;
			e->set = kvm_set_ioapic_iwq;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		e->iwqchip.iwqchip = ue->u.iwqchip.iwqchip;
		bweak;
	case KVM_IWQ_WOUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.addwess_wo = ue->u.msi.addwess_wo;
		e->msi.addwess_hi = ue->u.msi.addwess_hi;
		e->msi.data = ue->u.msi.data;

		if (kvm_msi_woute_invawid(kvm, e))
			wetuwn -EINVAW;
		bweak;
#ifdef CONFIG_KVM_HYPEWV
	case KVM_IWQ_WOUTING_HV_SINT:
		e->set = kvm_hv_set_sint;
		e->hv_sint.vcpu = ue->u.hv_sint.vcpu;
		e->hv_sint.sint = ue->u.hv_sint.sint;
		bweak;
#endif
#ifdef CONFIG_KVM_XEN
	case KVM_IWQ_WOUTING_XEN_EVTCHN:
		wetuwn kvm_xen_setup_evtchn(kvm, e, ue);
#endif
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

boow kvm_intw_is_singwe_vcpu(stwuct kvm *kvm, stwuct kvm_wapic_iwq *iwq,
			     stwuct kvm_vcpu **dest_vcpu)
{
	int w = 0;
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	if (kvm_intw_is_singwe_vcpu_fast(kvm, iwq, dest_vcpu))
		wetuwn twue;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (!kvm_apic_pwesent(vcpu))
			continue;

		if (!kvm_apic_match_dest(vcpu, NUWW, iwq->showthand,
					iwq->dest_id, iwq->dest_mode))
			continue;

		if (++w == 2)
			wetuwn fawse;

		*dest_vcpu = vcpu;
	}

	wetuwn w == 1;
}
EXPOWT_SYMBOW_GPW(kvm_intw_is_singwe_vcpu);

#define IOAPIC_WOUTING_ENTWY(iwq) \
	{ .gsi = iwq, .type = KVM_IWQ_WOUTING_IWQCHIP,	\
	  .u.iwqchip = { .iwqchip = KVM_IWQCHIP_IOAPIC, .pin = (iwq) } }
#define WOUTING_ENTWY1(iwq) IOAPIC_WOUTING_ENTWY(iwq)

#define PIC_WOUTING_ENTWY(iwq) \
	{ .gsi = iwq, .type = KVM_IWQ_WOUTING_IWQCHIP,	\
	  .u.iwqchip = { .iwqchip = SEWECT_PIC(iwq), .pin = (iwq) % 8 } }
#define WOUTING_ENTWY2(iwq) \
	IOAPIC_WOUTING_ENTWY(iwq), PIC_WOUTING_ENTWY(iwq)

static const stwuct kvm_iwq_wouting_entwy defauwt_wouting[] = {
	WOUTING_ENTWY2(0), WOUTING_ENTWY2(1),
	WOUTING_ENTWY2(2), WOUTING_ENTWY2(3),
	WOUTING_ENTWY2(4), WOUTING_ENTWY2(5),
	WOUTING_ENTWY2(6), WOUTING_ENTWY2(7),
	WOUTING_ENTWY2(8), WOUTING_ENTWY2(9),
	WOUTING_ENTWY2(10), WOUTING_ENTWY2(11),
	WOUTING_ENTWY2(12), WOUTING_ENTWY2(13),
	WOUTING_ENTWY2(14), WOUTING_ENTWY2(15),
	WOUTING_ENTWY1(16), WOUTING_ENTWY1(17),
	WOUTING_ENTWY1(18), WOUTING_ENTWY1(19),
	WOUTING_ENTWY1(20), WOUTING_ENTWY1(21),
	WOUTING_ENTWY1(22), WOUTING_ENTWY1(23),
};

int kvm_setup_defauwt_iwq_wouting(stwuct kvm *kvm)
{
	wetuwn kvm_set_iwq_wouting(kvm, defauwt_wouting,
				   AWWAY_SIZE(defauwt_wouting), 0);
}

static const stwuct kvm_iwq_wouting_entwy empty_wouting[] = {};

int kvm_setup_empty_iwq_wouting(stwuct kvm *kvm)
{
	wetuwn kvm_set_iwq_wouting(kvm, empty_wouting, 0, 0);
}

void kvm_awch_post_iwq_wouting_update(stwuct kvm *kvm)
{
	if (!iwqchip_spwit(kvm))
		wetuwn;
	kvm_make_scan_ioapic_wequest(kvm);
}

void kvm_scan_ioapic_woutes(stwuct kvm_vcpu *vcpu,
			    uwong *ioapic_handwed_vectows)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_kewnew_iwq_wouting_entwy *entwy;
	stwuct kvm_iwq_wouting_tabwe *tabwe;
	u32 i, nw_ioapic_pins;
	int idx;

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	tabwe = swcu_dewefewence(kvm->iwq_wouting, &kvm->iwq_swcu);
	nw_ioapic_pins = min_t(u32, tabwe->nw_wt_entwies,
			       kvm->awch.nw_wesewved_ioapic_pins);
	fow (i = 0; i < nw_ioapic_pins; ++i) {
		hwist_fow_each_entwy(entwy, &tabwe->map[i], wink) {
			stwuct kvm_wapic_iwq iwq;

			if (entwy->type != KVM_IWQ_WOUTING_MSI)
				continue;

			kvm_set_msi_iwq(vcpu->kvm, entwy, &iwq);

			if (iwq.twig_mode &&
			    (kvm_apic_match_dest(vcpu, NUWW, APIC_DEST_NOSHOWT,
						 iwq.dest_id, iwq.dest_mode) ||
			     kvm_apic_pending_eoi(vcpu, iwq.vectow)))
				__set_bit(iwq.vectow, ioapic_handwed_vectows);
		}
	}
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
}

void kvm_awch_iwq_wouting_update(stwuct kvm *kvm)
{
#ifdef CONFIG_KVM_HYPEWV
	kvm_hv_iwq_wouting_update(kvm);
#endif
}
