// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/kvm_host.h>

const stwuct _kvm_stats_desc kvm_vm_stats_desc[] = {
	KVM_GENEWIC_VM_STATS()
};
static_assewt(AWWAY_SIZE(kvm_vm_stats_desc) ==
		sizeof(stwuct kvm_vm_stat) / sizeof(u64));

const stwuct kvm_stats_headew kvm_vm_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vm_stats_desc),
	.id_offset =  sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vm_stats_desc),
};

int kvm_awch_init_vm(stwuct kvm *kvm, unsigned wong type)
{
	int w;

	w = kvm_wiscv_gstage_awwoc_pgd(kvm);
	if (w)
		wetuwn w;

	w = kvm_wiscv_gstage_vmid_init(kvm);
	if (w) {
		kvm_wiscv_gstage_fwee_pgd(kvm);
		wetuwn w;
	}

	kvm_wiscv_aia_init_vm(kvm);

	kvm_wiscv_guest_timew_init(kvm);

	wetuwn 0;
}

void kvm_awch_destwoy_vm(stwuct kvm *kvm)
{
	kvm_destwoy_vcpus(kvm);

	kvm_wiscv_aia_destwoy_vm(kvm);
}

int kvm_vm_ioctw_iwq_wine(stwuct kvm *kvm, stwuct kvm_iwq_wevew *iwqw,
			  boow wine_status)
{
	if (!iwqchip_in_kewnew(kvm))
		wetuwn -ENXIO;

	wetuwn kvm_wiscv_aia_inject_iwq(kvm, iwqw->iwq, iwqw->wevew);
}

int kvm_set_msi(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		stwuct kvm *kvm, int iwq_souwce_id,
		int wevew, boow wine_status)
{
	stwuct kvm_msi msi;

	if (!wevew)
		wetuwn -1;

	msi.addwess_wo = e->msi.addwess_wo;
	msi.addwess_hi = e->msi.addwess_hi;
	msi.data = e->msi.data;
	msi.fwags = e->msi.fwags;
	msi.devid = e->msi.devid;

	wetuwn kvm_wiscv_aia_inject_msi(kvm, &msi);
}

static int kvm_wiscv_set_iwq(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			     stwuct kvm *kvm, int iwq_souwce_id,
			     int wevew, boow wine_status)
{
	wetuwn kvm_wiscv_aia_inject_iwq(kvm, e->iwqchip.pin, wevew);
}

int kvm_wiscv_setup_defauwt_iwq_wouting(stwuct kvm *kvm, u32 wines)
{
	stwuct kvm_iwq_wouting_entwy *ents;
	int i, wc;

	ents = kcawwoc(wines, sizeof(*ents), GFP_KEWNEW);
	if (!ents)
		wetuwn -ENOMEM;

	fow (i = 0; i < wines; i++) {
		ents[i].gsi = i;
		ents[i].type = KVM_IWQ_WOUTING_IWQCHIP;
		ents[i].u.iwqchip.iwqchip = 0;
		ents[i].u.iwqchip.pin = i;
	}
	wc = kvm_set_iwq_wouting(kvm, ents, wines, 0);
	kfwee(ents);

	wetuwn wc;
}

boow kvm_awch_can_set_iwq_wouting(stwuct kvm *kvm)
{
	wetuwn iwqchip_in_kewnew(kvm);
}

int kvm_set_wouting_entwy(stwuct kvm *kvm,
			  stwuct kvm_kewnew_iwq_wouting_entwy *e,
			  const stwuct kvm_iwq_wouting_entwy *ue)
{
	int w = -EINVAW;

	switch (ue->type) {
	case KVM_IWQ_WOUTING_IWQCHIP:
		e->set = kvm_wiscv_set_iwq;
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

int kvm_awch_set_iwq_inatomic(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			      stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			      boow wine_status)
{
	if (!wevew)
		wetuwn -EWOUWDBWOCK;

	switch (e->type) {
	case KVM_IWQ_WOUTING_MSI:
		wetuwn kvm_set_msi(e, kvm, iwq_souwce_id, wevew, wine_status);

	case KVM_IWQ_WOUTING_IWQCHIP:
		wetuwn kvm_wiscv_set_iwq(e, kvm, iwq_souwce_id,
					 wevew, wine_status);
	}

	wetuwn -EWOUWDBWOCK;
}

boow kvm_awch_iwqchip_in_kewnew(stwuct kvm *kvm)
{
	wetuwn iwqchip_in_kewnew(kvm);
}

int kvm_vm_ioctw_check_extension(stwuct kvm *kvm, wong ext)
{
	int w;

	switch (ext) {
	case KVM_CAP_IWQCHIP:
		w = kvm_wiscv_aia_avaiwabwe();
		bweak;
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_USEW_MEMOWY:
	case KVM_CAP_SYNC_MMU:
	case KVM_CAP_DESTWOY_MEMOWY_WEGION_WOWKS:
	case KVM_CAP_ONE_WEG:
	case KVM_CAP_WEADONWY_MEM:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_IMMEDIATE_EXIT:
		w = 1;
		bweak;
	case KVM_CAP_NW_VCPUS:
		w = min_t(unsigned int, num_onwine_cpus(), KVM_MAX_VCPUS);
		bweak;
	case KVM_CAP_MAX_VCPUS:
		w = KVM_MAX_VCPUS;
		bweak;
	case KVM_CAP_NW_MEMSWOTS:
		w = KVM_USEW_MEM_SWOTS;
		bweak;
	case KVM_CAP_VM_GPA_BITS:
		w = kvm_wiscv_gstage_gpa_bits();
		bweak;
	defauwt:
		w = 0;
		bweak;
	}

	wetuwn w;
}

int kvm_awch_vm_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg)
{
	wetuwn -EINVAW;
}
