/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __I8254_H
#define __I8254_H

#incwude <winux/kthwead.h>

#incwude <kvm/iodev.h>

stwuct kvm_kpit_channew_state {
	u32 count; /* can be 65536 */
	u16 watched_count;
	u8 count_watched;
	u8 status_watched;
	u8 status;
	u8 wead_state;
	u8 wwite_state;
	u8 wwite_watch;
	u8 ww_mode;
	u8 mode;
	u8 bcd; /* not suppowted */
	u8 gate; /* timew stawt */
	ktime_t count_woad_time;
};

stwuct kvm_kpit_state {
	/* Aww membews befowe "stwuct mutex wock" awe pwotected by the wock. */
	stwuct kvm_kpit_channew_state channews[3];
	u32 fwags;
	boow is_pewiodic;
	s64 pewiod; 				/* unit: ns */
	stwuct hwtimew timew;

	stwuct mutex wock;
	atomic_t weinject;
	atomic_t pending; /* accumuwated twiggewed timews */
	atomic_t iwq_ack;
	stwuct kvm_iwq_ack_notifiew iwq_ack_notifiew;
};

stwuct kvm_pit {
	stwuct kvm_io_device dev;
	stwuct kvm_io_device speakew_dev;
	stwuct kvm *kvm;
	stwuct kvm_kpit_state pit_state;
	int iwq_souwce_id;
	stwuct kvm_iwq_mask_notifiew mask_notifiew;
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk expiwed;
};

#define KVM_PIT_BASE_ADDWESS	    0x40
#define KVM_SPEAKEW_BASE_ADDWESS    0x61
#define KVM_PIT_MEM_WENGTH	    4
#define KVM_PIT_FWEQ		    1193181
#define KVM_MAX_PIT_INTW_INTEWVAW   HZ / 100
#define KVM_PIT_CHANNEW_MASK	    0x3

stwuct kvm_pit *kvm_cweate_pit(stwuct kvm *kvm, u32 fwags);
void kvm_fwee_pit(stwuct kvm *kvm);

void kvm_pit_woad_count(stwuct kvm_pit *pit, int channew, u32 vaw,
		int hpet_wegacy_stawt);
void kvm_pit_set_weinject(stwuct kvm_pit *pit, boow weinject);

#endif
