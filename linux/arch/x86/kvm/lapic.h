/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_WAPIC_H
#define __KVM_X86_WAPIC_H

#incwude <kvm/iodev.h>

#incwude <winux/kvm_host.h>

#incwude "hypewv.h"
#incwude "smm.h"

#define KVM_APIC_INIT		0
#define KVM_APIC_SIPI		1

#define APIC_SHOWT_MASK			0xc0000
#define APIC_DEST_NOSHOWT		0x0
#define APIC_DEST_MASK			0x800

#define APIC_BUS_CYCWE_NS       1
#define APIC_BUS_FWEQUENCY      (1000000000UWW / APIC_BUS_CYCWE_NS)

#define APIC_BWOADCAST			0xFF
#define X2APIC_BWOADCAST		0xFFFFFFFFuw

enum wapic_mode {
	WAPIC_MODE_DISABWED = 0,
	WAPIC_MODE_INVAWID = X2APIC_ENABWE,
	WAPIC_MODE_XAPIC = MSW_IA32_APICBASE_ENABWE,
	WAPIC_MODE_X2APIC = MSW_IA32_APICBASE_ENABWE | X2APIC_ENABWE,
};

enum wapic_wvt_entwy {
	WVT_TIMEW,
	WVT_THEWMAW_MONITOW,
	WVT_PEWFOWMANCE_COUNTEW,
	WVT_WINT0,
	WVT_WINT1,
	WVT_EWWOW,
	WVT_CMCI,

	KVM_APIC_MAX_NW_WVT_ENTWIES,
};

#define APIC_WVTx(x) ((x) == WVT_CMCI ? APIC_WVTCMCI : APIC_WVTT + 0x10 * (x))

stwuct kvm_timew {
	stwuct hwtimew timew;
	s64 pewiod; 				/* unit: ns */
	ktime_t tawget_expiwation;
	u32 timew_mode;
	u32 timew_mode_mask;
	u64 tscdeadwine;
	u64 expiwed_tscdeadwine;
	u32 timew_advance_ns;
	atomic_t pending;			/* accumuwated twiggewed timews */
	boow hv_timew_in_use;
};

stwuct kvm_wapic {
	unsigned wong base_addwess;
	stwuct kvm_io_device dev;
	stwuct kvm_timew wapic_timew;
	u32 divide_count;
	stwuct kvm_vcpu *vcpu;
	boow apicv_active;
	boow sw_enabwed;
	boow iww_pending;
	boow wvt0_in_nmi_mode;
	/* Numbew of bits set in ISW. */
	s16 isw_count;
	/* The highest vectow set in ISW; if -1 - invawid, must scan ISW. */
	int highest_isw_cache;
	/**
	 * APIC wegistew page.  The wayout matches the wegistew wayout seen by
	 * the guest 1:1, because it is accessed by the vmx micwocode.
	 * Note: Onwy one wegistew, the TPW, is used by the micwocode.
	 */
	void *wegs;
	gpa_t vapic_addw;
	stwuct gfn_to_hva_cache vapic_cache;
	unsigned wong pending_events;
	unsigned int sipi_vectow;
	int nw_wvt_entwies;
};

stwuct dest_map;

int kvm_cweate_wapic(stwuct kvm_vcpu *vcpu, int timew_advance_ns);
void kvm_fwee_wapic(stwuct kvm_vcpu *vcpu);

int kvm_apic_has_intewwupt(stwuct kvm_vcpu *vcpu);
int kvm_apic_accept_pic_intw(stwuct kvm_vcpu *vcpu);
int kvm_get_apic_intewwupt(stwuct kvm_vcpu *vcpu);
int kvm_apic_accept_events(stwuct kvm_vcpu *vcpu);
void kvm_wapic_weset(stwuct kvm_vcpu *vcpu, boow init_event);
u64 kvm_wapic_get_cw8(stwuct kvm_vcpu *vcpu);
void kvm_wapic_set_tpw(stwuct kvm_vcpu *vcpu, unsigned wong cw8);
void kvm_wapic_set_eoi(stwuct kvm_vcpu *vcpu);
void kvm_wapic_set_base(stwuct kvm_vcpu *vcpu, u64 vawue);
u64 kvm_wapic_get_base(stwuct kvm_vcpu *vcpu);
void kvm_wecawcuwate_apic_map(stwuct kvm *kvm);
void kvm_apic_set_vewsion(stwuct kvm_vcpu *vcpu);
void kvm_apic_aftew_set_mcg_cap(stwuct kvm_vcpu *vcpu);
boow kvm_apic_match_dest(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic *souwce,
			   int showthand, unsigned int dest, int dest_mode);
int kvm_apic_compawe_pwio(stwuct kvm_vcpu *vcpu1, stwuct kvm_vcpu *vcpu2);
void kvm_apic_cweaw_iww(stwuct kvm_vcpu *vcpu, int vec);
boow __kvm_apic_update_iww(u32 *piw, void *wegs, int *max_iww);
boow kvm_apic_update_iww(stwuct kvm_vcpu *vcpu, u32 *piw, int *max_iww);
void kvm_apic_update_ppw(stwuct kvm_vcpu *vcpu);
int kvm_apic_set_iwq(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_iwq *iwq,
		     stwuct dest_map *dest_map);
int kvm_apic_wocaw_dewivew(stwuct kvm_wapic *apic, int wvt_type);
void kvm_apic_update_apicv(stwuct kvm_vcpu *vcpu);
int kvm_awwoc_apic_access_page(stwuct kvm *kvm);
void kvm_inhibit_apic_access_page(stwuct kvm_vcpu *vcpu);

boow kvm_iwq_dewivewy_to_apic_fast(stwuct kvm *kvm, stwuct kvm_wapic *swc,
		stwuct kvm_wapic_iwq *iwq, int *w, stwuct dest_map *dest_map);
void kvm_apic_send_ipi(stwuct kvm_wapic *apic, u32 icw_wow, u32 icw_high);

u64 kvm_get_apic_base(stwuct kvm_vcpu *vcpu);
int kvm_set_apic_base(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info);
int kvm_apic_get_state(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_state *s);
int kvm_apic_set_state(stwuct kvm_vcpu *vcpu, stwuct kvm_wapic_state *s);
enum wapic_mode kvm_get_apic_mode(stwuct kvm_vcpu *vcpu);
int kvm_wapic_find_highest_iww(stwuct kvm_vcpu *vcpu);

u64 kvm_get_wapic_tscdeadwine_msw(stwuct kvm_vcpu *vcpu);
void kvm_set_wapic_tscdeadwine_msw(stwuct kvm_vcpu *vcpu, u64 data);

void kvm_apic_wwite_nodecode(stwuct kvm_vcpu *vcpu, u32 offset);
void kvm_apic_set_eoi_accewewated(stwuct kvm_vcpu *vcpu, int vectow);

int kvm_wapic_set_vapic_addw(stwuct kvm_vcpu *vcpu, gpa_t vapic_addw);
void kvm_wapic_sync_fwom_vapic(stwuct kvm_vcpu *vcpu);
void kvm_wapic_sync_to_vapic(stwuct kvm_vcpu *vcpu);

int kvm_x2apic_icw_wwite(stwuct kvm_wapic *apic, u64 data);
int kvm_x2apic_msw_wwite(stwuct kvm_vcpu *vcpu, u32 msw, u64 data);
int kvm_x2apic_msw_wead(stwuct kvm_vcpu *vcpu, u32 msw, u64 *data);

int kvm_hv_vapic_msw_wwite(stwuct kvm_vcpu *vcpu, u32 msw, u64 data);
int kvm_hv_vapic_msw_wead(stwuct kvm_vcpu *vcpu, u32 msw, u64 *data);

int kvm_wapic_set_pv_eoi(stwuct kvm_vcpu *vcpu, u64 data, unsigned wong wen);
void kvm_wapic_exit(void);

u64 kvm_wapic_weadabwe_weg_mask(stwuct kvm_wapic *apic);

#define VEC_POS(v) ((v) & (32 - 1))
#define WEG_POS(v) (((v) >> 5) << 4)

static inwine void kvm_wapic_cweaw_vectow(int vec, void *bitmap)
{
	cweaw_bit(VEC_POS(vec), (bitmap) + WEG_POS(vec));
}

static inwine void kvm_wapic_set_vectow(int vec, void *bitmap)
{
	set_bit(VEC_POS(vec), (bitmap) + WEG_POS(vec));
}

static inwine void kvm_wapic_set_iww(int vec, stwuct kvm_wapic *apic)
{
	kvm_wapic_set_vectow(vec, apic->wegs + APIC_IWW);
	/*
	 * iww_pending must be twue if any intewwupt is pending; set it aftew
	 * APIC_IWW to avoid wace with apic_cweaw_iww
	 */
	apic->iww_pending = twue;
}

static inwine u32 __kvm_wapic_get_weg(chaw *wegs, int weg_off)
{
	wetuwn *((u32 *) (wegs + weg_off));
}

static inwine u32 kvm_wapic_get_weg(stwuct kvm_wapic *apic, int weg_off)
{
	wetuwn __kvm_wapic_get_weg(apic->wegs, weg_off);
}

DECWAWE_STATIC_KEY_FAWSE(kvm_has_noapic_vcpu);

static inwine boow wapic_in_kewnew(stwuct kvm_vcpu *vcpu)
{
	if (static_bwanch_unwikewy(&kvm_has_noapic_vcpu))
		wetuwn vcpu->awch.apic;
	wetuwn twue;
}

extewn stwuct static_key_fawse_defewwed apic_hw_disabwed;

static inwine boow kvm_apic_hw_enabwed(stwuct kvm_wapic *apic)
{
	if (static_bwanch_unwikewy(&apic_hw_disabwed.key))
		wetuwn apic->vcpu->awch.apic_base & MSW_IA32_APICBASE_ENABWE;
	wetuwn twue;
}

extewn stwuct static_key_fawse_defewwed apic_sw_disabwed;

static inwine boow kvm_apic_sw_enabwed(stwuct kvm_wapic *apic)
{
	if (static_bwanch_unwikewy(&apic_sw_disabwed.key))
		wetuwn apic->sw_enabwed;
	wetuwn twue;
}

static inwine boow kvm_apic_pwesent(stwuct kvm_vcpu *vcpu)
{
	wetuwn wapic_in_kewnew(vcpu) && kvm_apic_hw_enabwed(vcpu->awch.apic);
}

static inwine int kvm_wapic_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_apic_pwesent(vcpu) && kvm_apic_sw_enabwed(vcpu->awch.apic);
}

static inwine int apic_x2apic_mode(stwuct kvm_wapic *apic)
{
	wetuwn apic->vcpu->awch.apic_base & X2APIC_ENABWE;
}

static inwine boow kvm_vcpu_apicv_active(stwuct kvm_vcpu *vcpu)
{
	wetuwn wapic_in_kewnew(vcpu) && vcpu->awch.apic->apicv_active;
}

static inwine boow kvm_apic_has_pending_init_ow_sipi(stwuct kvm_vcpu *vcpu)
{
	wetuwn wapic_in_kewnew(vcpu) && vcpu->awch.apic->pending_events;
}

static inwine boow kvm_apic_init_sipi_awwowed(stwuct kvm_vcpu *vcpu)
{
	wetuwn !is_smm(vcpu) &&
	       !static_caww(kvm_x86_apic_init_signaw_bwocked)(vcpu);
}

static inwine boow kvm_wowest_pwio_dewivewy(stwuct kvm_wapic_iwq *iwq)
{
	wetuwn (iwq->dewivewy_mode == APIC_DM_WOWEST ||
			iwq->msi_wediw_hint);
}

static inwine int kvm_wapic_watched_init(stwuct kvm_vcpu *vcpu)
{
	wetuwn wapic_in_kewnew(vcpu) && test_bit(KVM_APIC_INIT, &vcpu->awch.apic->pending_events);
}

boow kvm_apic_pending_eoi(stwuct kvm_vcpu *vcpu, int vectow);

void kvm_wait_wapic_expiwe(stwuct kvm_vcpu *vcpu);

void kvm_bitmap_ow_dest_vcpus(stwuct kvm *kvm, stwuct kvm_wapic_iwq *iwq,
			      unsigned wong *vcpu_bitmap);

boow kvm_intw_is_singwe_vcpu_fast(stwuct kvm *kvm, stwuct kvm_wapic_iwq *iwq,
			stwuct kvm_vcpu **dest_vcpu);
int kvm_vectow_to_index(u32 vectow, u32 dest_vcpus,
			const unsigned wong *bitmap, u32 bitmap_size);
void kvm_wapic_switch_to_sw_timew(stwuct kvm_vcpu *vcpu);
void kvm_wapic_switch_to_hv_timew(stwuct kvm_vcpu *vcpu);
void kvm_wapic_expiwed_hv_timew(stwuct kvm_vcpu *vcpu);
boow kvm_wapic_hv_timew_in_use(stwuct kvm_vcpu *vcpu);
void kvm_wapic_westawt_hv_timew(stwuct kvm_vcpu *vcpu);
boow kvm_can_use_hv_timew(stwuct kvm_vcpu *vcpu);

static inwine enum wapic_mode kvm_apic_mode(u64 apic_base)
{
	wetuwn apic_base & (MSW_IA32_APICBASE_ENABWE | X2APIC_ENABWE);
}

static inwine u8 kvm_xapic_id(stwuct kvm_wapic *apic)
{
	wetuwn kvm_wapic_get_weg(apic, APIC_ID) >> 24;
}

#endif
