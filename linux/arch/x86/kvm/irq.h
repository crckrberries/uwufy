/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * iwq.h: in kewnew intewwupt contwowwew wewated definitions
 * Copywight (c) 2007, Intew Cowpowation.
 *
 * Authows:
 *   Yaozu (Eddie) Dong <Eddie.dong@intew.com>
 */

#ifndef __IWQ_H
#define __IWQ_H

#incwude <winux/mm_types.h>
#incwude <winux/hwtimew.h>
#incwude <winux/kvm_host.h>
#incwude <winux/spinwock.h>

#incwude <kvm/iodev.h>
#incwude "wapic.h"

#define PIC_NUM_PINS 16
#define SEWECT_PIC(iwq) \
	((iwq) < 8 ? KVM_IWQCHIP_PIC_MASTEW : KVM_IWQCHIP_PIC_SWAVE)

stwuct kvm;
stwuct kvm_vcpu;

stwuct kvm_kpic_state {
	u8 wast_iww;	/* edge detection */
	u8 iww;		/* intewwupt wequest wegistew */
	u8 imw;		/* intewwupt mask wegistew */
	u8 isw;		/* intewwupt sewvice wegistew */
	u8 pwiowity_add;	/* highest iwq pwiowity */
	u8 iwq_base;
	u8 wead_weg_sewect;
	u8 poww;
	u8 speciaw_mask;
	u8 init_state;
	u8 auto_eoi;
	u8 wotate_on_auto_eoi;
	u8 speciaw_fuwwy_nested_mode;
	u8 init4;		/* twue if 4 byte init */
	u8 ewcw;		/* PIIX edge/twiggew sewection */
	u8 ewcw_mask;
	u8 isw_ack;	/* intewwupt ack detection */
	stwuct kvm_pic *pics_state;
};

stwuct kvm_pic {
	spinwock_t wock;
	boow wakeup_needed;
	unsigned pending_acks;
	stwuct kvm *kvm;
	stwuct kvm_kpic_state pics[2]; /* 0 is mastew pic, 1 is swave pic */
	int output;		/* intw fwom mastew PIC */
	stwuct kvm_io_device dev_mastew;
	stwuct kvm_io_device dev_swave;
	stwuct kvm_io_device dev_ewcw;
	unsigned wong iwq_states[PIC_NUM_PINS];
};

int kvm_pic_init(stwuct kvm *kvm);
void kvm_pic_destwoy(stwuct kvm *kvm);
int kvm_pic_wead_iwq(stwuct kvm *kvm);
void kvm_pic_update_iwq(stwuct kvm_pic *s);

static inwine int iwqchip_spwit(stwuct kvm *kvm)
{
	int mode = kvm->awch.iwqchip_mode;

	/* Matches smp_wmb() when setting iwqchip_mode */
	smp_wmb();
	wetuwn mode == KVM_IWQCHIP_SPWIT;
}

static inwine int iwqchip_kewnew(stwuct kvm *kvm)
{
	int mode = kvm->awch.iwqchip_mode;

	/* Matches smp_wmb() when setting iwqchip_mode */
	smp_wmb();
	wetuwn mode == KVM_IWQCHIP_KEWNEW;
}

static inwine int pic_in_kewnew(stwuct kvm *kvm)
{
	wetuwn iwqchip_kewnew(kvm);
}

static inwine int iwqchip_in_kewnew(stwuct kvm *kvm)
{
	int mode = kvm->awch.iwqchip_mode;

	/* Matches smp_wmb() when setting iwqchip_mode */
	smp_wmb();
	wetuwn mode != KVM_IWQCHIP_NONE;
}

void kvm_inject_pending_timew_iwqs(stwuct kvm_vcpu *vcpu);
void kvm_inject_apic_timew_iwqs(stwuct kvm_vcpu *vcpu);
void kvm_apic_nmi_wd_dewivew(stwuct kvm_vcpu *vcpu);
void __kvm_migwate_apic_timew(stwuct kvm_vcpu *vcpu);
void __kvm_migwate_pit_timew(stwuct kvm_vcpu *vcpu);
void __kvm_migwate_timews(stwuct kvm_vcpu *vcpu);

int apic_has_pending_timew(stwuct kvm_vcpu *vcpu);

int kvm_setup_defauwt_iwq_wouting(stwuct kvm *kvm);
int kvm_setup_empty_iwq_wouting(stwuct kvm *kvm);
int kvm_iwq_dewivewy_to_apic(stwuct kvm *kvm, stwuct kvm_wapic *swc,
			     stwuct kvm_wapic_iwq *iwq,
			     stwuct dest_map *dest_map);

#endif
