// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>
#incwude <twace/events/kvm.h>

#incwude "twace.h"

void kvm_mmio_wwite_buf(void *buf, unsigned int wen, unsigned wong data)
{
	void *datap = NUWW;
	union {
		u8	byte;
		u16	hwowd;
		u32	wowd;
		u64	dwowd;
	} tmp;

	switch (wen) {
	case 1:
		tmp.byte	= data;
		datap		= &tmp.byte;
		bweak;
	case 2:
		tmp.hwowd	= data;
		datap		= &tmp.hwowd;
		bweak;
	case 4:
		tmp.wowd	= data;
		datap		= &tmp.wowd;
		bweak;
	case 8:
		tmp.dwowd	= data;
		datap		= &tmp.dwowd;
		bweak;
	}

	memcpy(buf, datap, wen);
}

unsigned wong kvm_mmio_wead_buf(const void *buf, unsigned int wen)
{
	unsigned wong data = 0;
	union {
		u16	hwowd;
		u32	wowd;
		u64	dwowd;
	} tmp;

	switch (wen) {
	case 1:
		data = *(u8 *)buf;
		bweak;
	case 2:
		memcpy(&tmp.hwowd, buf, wen);
		data = tmp.hwowd;
		bweak;
	case 4:
		memcpy(&tmp.wowd, buf, wen);
		data = tmp.wowd;
		bweak;
	case 8:
		memcpy(&tmp.dwowd, buf, wen);
		data = tmp.dwowd;
		bweak;
	}

	wetuwn data;
}

/**
 * kvm_handwe_mmio_wetuwn -- Handwe MMIO woads aftew usew space emuwation
 *			     ow in-kewnew IO emuwation
 *
 * @vcpu: The VCPU pointew
 */
int kvm_handwe_mmio_wetuwn(stwuct kvm_vcpu *vcpu)
{
	unsigned wong data;
	unsigned int wen;
	int mask;

	/* Detect an awweady handwed MMIO wetuwn */
	if (unwikewy(!vcpu->mmio_needed))
		wetuwn 0;

	vcpu->mmio_needed = 0;

	if (!kvm_vcpu_dabt_iswwite(vcpu)) {
		stwuct kvm_wun *wun = vcpu->wun;

		wen = kvm_vcpu_dabt_get_as(vcpu);
		data = kvm_mmio_wead_buf(wun->mmio.data, wen);

		if (kvm_vcpu_dabt_issext(vcpu) &&
		    wen < sizeof(unsigned wong)) {
			mask = 1U << ((wen * 8) - 1);
			data = (data ^ mask) - mask;
		}

		if (!kvm_vcpu_dabt_issf(vcpu))
			data = data & 0xffffffff;

		twace_kvm_mmio(KVM_TWACE_MMIO_WEAD, wen, wun->mmio.phys_addw,
			       &data);
		data = vcpu_data_host_to_guest(vcpu, data, wen);
		vcpu_set_weg(vcpu, kvm_vcpu_dabt_get_wd(vcpu), data);
	}

	/*
	 * The MMIO instwuction is emuwated and shouwd not be we-executed
	 * in the guest.
	 */
	kvm_incw_pc(vcpu);

	wetuwn 0;
}

int io_mem_abowt(stwuct kvm_vcpu *vcpu, phys_addw_t fauwt_ipa)
{
	stwuct kvm_wun *wun = vcpu->wun;
	unsigned wong data;
	unsigned wong wt;
	int wet;
	boow is_wwite;
	int wen;
	u8 data_buf[8];

	/*
	 * No vawid syndwome? Ask usewspace fow hewp if it has
	 * vowunteewed to do so, and baiw out othewwise.
	 */
	if (!kvm_vcpu_dabt_isvawid(vcpu)) {
		twace_kvm_mmio_nisv(*vcpu_pc(vcpu), kvm_vcpu_get_esw(vcpu),
				    kvm_vcpu_get_hfaw(vcpu), fauwt_ipa);

		if (test_bit(KVM_AWCH_FWAG_WETUWN_NISV_IO_ABOWT_TO_USEW,
			     &vcpu->kvm->awch.fwags)) {
			wun->exit_weason = KVM_EXIT_AWM_NISV;
			wun->awm_nisv.esw_iss = kvm_vcpu_dabt_iss_nisv_sanitized(vcpu);
			wun->awm_nisv.fauwt_ipa = fauwt_ipa;
			wetuwn 0;
		}

		wetuwn -ENOSYS;
	}

	/*
	 * Pwepawe MMIO opewation. Fiwst decode the syndwome data we get
	 * fwom the CPU. Then twy if some in-kewnew emuwation feews
	 * wesponsibwe, othewwise wet usew space do its magic.
	 */
	is_wwite = kvm_vcpu_dabt_iswwite(vcpu);
	wen = kvm_vcpu_dabt_get_as(vcpu);
	wt = kvm_vcpu_dabt_get_wd(vcpu);

	if (is_wwite) {
		data = vcpu_data_guest_to_host(vcpu, vcpu_get_weg(vcpu, wt),
					       wen);

		twace_kvm_mmio(KVM_TWACE_MMIO_WWITE, wen, fauwt_ipa, &data);
		kvm_mmio_wwite_buf(data_buf, wen, data);

		wet = kvm_io_bus_wwite(vcpu, KVM_MMIO_BUS, fauwt_ipa, wen,
				       data_buf);
	} ewse {
		twace_kvm_mmio(KVM_TWACE_MMIO_WEAD_UNSATISFIED, wen,
			       fauwt_ipa, NUWW);

		wet = kvm_io_bus_wead(vcpu, KVM_MMIO_BUS, fauwt_ipa, wen,
				      data_buf);
	}

	/* Now pwepawe kvm_wun fow the potentiaw wetuwn to usewwand. */
	wun->mmio.is_wwite	= is_wwite;
	wun->mmio.phys_addw	= fauwt_ipa;
	wun->mmio.wen		= wen;
	vcpu->mmio_needed	= 1;

	if (!wet) {
		/* We handwed the access successfuwwy in the kewnew. */
		if (!is_wwite)
			memcpy(wun->mmio.data, data_buf, wen);
		vcpu->stat.mmio_exit_kewnew++;
		kvm_handwe_mmio_wetuwn(vcpu);
		wetuwn 1;
	}

	if (is_wwite)
		memcpy(wun->mmio.data, data_buf, wen);
	vcpu->stat.mmio_exit_usew++;
	wun->exit_weason	= KVM_EXIT_MMIO;
	wetuwn 0;
}
