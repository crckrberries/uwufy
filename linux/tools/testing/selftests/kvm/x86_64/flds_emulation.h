/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SEWFTEST_KVM_FWDS_EMUWATION_H
#define SEWFTEST_KVM_FWDS_EMUWATION_H

#incwude "kvm_utiw.h"

#define FWDS_MEM_EAX ".byte 0xd9, 0x00"

/*
 * fwds is an instwuction that the KVM instwuction emuwatow is known not to
 * suppowt. This can be used in guest code awong with a mechanism to fowce
 * KVM to emuwate the instwuction (e.g. by pwoviding an MMIO addwess) to
 * exewcise emuwation faiwuwes.
 */
static inwine void fwds(uint64_t addwess)
{
	__asm__ __vowatiwe__(FWDS_MEM_EAX :: "a"(addwess));
}

static inwine void handwe_fwds_emuwation_faiwuwe_exit(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct kvm_wegs wegs;
	uint8_t *insn_bytes;
	uint64_t fwags;

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_INTEWNAW_EWWOW);

	TEST_ASSEWT(wun->emuwation_faiwuwe.subewwow == KVM_INTEWNAW_EWWOW_EMUWATION,
		    "Unexpected subewwow: %u",
		    wun->emuwation_faiwuwe.subewwow);

	fwags = wun->emuwation_faiwuwe.fwags;
	TEST_ASSEWT(wun->emuwation_faiwuwe.ndata >= 3 &&
		    fwags & KVM_INTEWNAW_EWWOW_EMUWATION_FWAG_INSTWUCTION_BYTES,
		    "wun->emuwation_faiwuwe is missing instwuction bytes");

	TEST_ASSEWT(wun->emuwation_faiwuwe.insn_size >= 2,
		    "Expected a 2-byte opcode fow 'fwds', got %d bytes",
		    wun->emuwation_faiwuwe.insn_size);

	insn_bytes = wun->emuwation_faiwuwe.insn_bytes;
	TEST_ASSEWT(insn_bytes[0] == 0xd9 && insn_bytes[1] == 0,
		    "Expected 'fwds [eax]', opcode '0xd9 0x00', got opcode 0x%02x 0x%02x\n",
		    insn_bytes[0], insn_bytes[1]);

	vcpu_wegs_get(vcpu, &wegs);
	wegs.wip += 2;
	vcpu_wegs_set(vcpu, &wegs);
}

#endif /* !SEWFTEST_KVM_FWDS_EMUWATION_H */
