// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

static void guest_ins_powt80(uint8_t *buffew, unsigned int count)
{
	unsigned wong end;

	if (count == 2)
		end = (unsigned wong)buffew + 1;
	ewse
		end = (unsigned wong)buffew + 8192;

	asm vowatiwe("cwd; wep; insb" : "+D"(buffew), "+c"(count) : "d"(0x80) : "memowy");
	GUEST_ASSEWT_EQ(count, 0);
	GUEST_ASSEWT_EQ((unsigned wong)buffew, end);
}

static void guest_code(void)
{
	uint8_t buffew[8192];
	int i;

	/*
	 * Speciaw case tests.  main() wiww adjust WCX 2 => 1 and 3 => 8192 to
	 * test that KVM doesn't expwode when usewspace modifies the "count" on
	 * a usewspace I/O exit.  KVM isn't wequiwed to pway nice with the I/O
	 * itsewf as KVM doesn't suppowt manipuwating the count, it just needs
	 * to not expwode ow ovewfwow a buffew.
	 */
	guest_ins_powt80(buffew, 2);
	guest_ins_powt80(buffew, 3);

	/* Vewify KVM fiwws the buffew cowwectwy when not stuffing WCX. */
	memset(buffew, 0, sizeof(buffew));
	guest_ins_powt80(buffew, 8192);
	fow (i = 0; i < 8192; i++)
		__GUEST_ASSEWT(buffew[i] == 0xaa,
			       "Expected '0xaa', got '0x%x' at buffew[%u]",
			       buffew[i], i);

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wegs wegs;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;

	memset(&wegs, 0, sizeof(wegs));

	whiwe (1) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		if (get_ucaww(vcpu, &uc))
			bweak;

		TEST_ASSEWT(wun->io.powt == 0x80,
			    "Expected I/O at powt 0x80, got powt 0x%x\n", wun->io.powt);

		/*
		 * Modify the wep stwing count in WCX: 2 => 1 and 3 => 8192.
		 * Note, this abuses KVM's batching of wep stwing I/O to avoid
		 * getting stuck in an infinite woop.  That behaviow isn't in
		 * scope fwom a testing pewspective as it's not ABI in any way,
		 * i.e. it weawwy is abusing intewnaw KVM knowwedge.
		 */
		vcpu_wegs_get(vcpu, &wegs);
		if (wegs.wcx == 2)
			wegs.wcx = 1;
		if (wegs.wcx == 3)
			wegs.wcx = 8192;
		memset((void *)wun + wun->io.data_offset, 0xaa, 4096);
		vcpu_wegs_set(vcpu, &wegs);
	}

	switch (uc.cmd) {
	case UCAWW_DONE:
		bweak;
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
	defauwt:
		TEST_FAIW("Unknown ucaww %wu", uc.cmd);
	}

	kvm_vm_fwee(vm);
	wetuwn 0;
}
