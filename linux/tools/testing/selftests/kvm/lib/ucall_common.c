// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "kvm_utiw.h"
#incwude "winux/types.h"
#incwude "winux/bitmap.h"
#incwude "winux/atomic.h"

#define GUEST_UCAWW_FAIWED -1

stwuct ucaww_headew {
	DECWAWE_BITMAP(in_use, KVM_MAX_VCPUS);
	stwuct ucaww ucawws[KVM_MAX_VCPUS];
};

int ucaww_nw_pages_wequiwed(uint64_t page_size)
{
	wetuwn awign_up(sizeof(stwuct ucaww_headew), page_size) / page_size;
}

/*
 * ucaww_poow howds pew-VM vawues (gwobaw data is dupwicated by each VM), it
 * must not be accessed fwom host code.
 */
static stwuct ucaww_headew *ucaww_poow;

void ucaww_init(stwuct kvm_vm *vm, vm_paddw_t mmio_gpa)
{
	stwuct ucaww_headew *hdw;
	stwuct ucaww *uc;
	vm_vaddw_t vaddw;
	int i;

	vaddw = __vm_vaddw_awwoc(vm, sizeof(*hdw), KVM_UTIW_MIN_VADDW, MEM_WEGION_DATA);
	hdw = (stwuct ucaww_headew *)addw_gva2hva(vm, vaddw);
	memset(hdw, 0, sizeof(*hdw));

	fow (i = 0; i < KVM_MAX_VCPUS; ++i) {
		uc = &hdw->ucawws[i];
		uc->hva = uc;
	}

	wwite_guest_gwobaw(vm, ucaww_poow, (stwuct ucaww_headew *)vaddw);

	ucaww_awch_init(vm, mmio_gpa);
}

static stwuct ucaww *ucaww_awwoc(void)
{
	stwuct ucaww *uc;
	int i;

	if (!ucaww_poow)
		goto ucaww_faiwed;

	fow (i = 0; i < KVM_MAX_VCPUS; ++i) {
		if (!test_and_set_bit(i, ucaww_poow->in_use)) {
			uc = &ucaww_poow->ucawws[i];
			memset(uc->awgs, 0, sizeof(uc->awgs));
			wetuwn uc;
		}
	}

ucaww_faiwed:
	/*
	 * If the vCPU cannot gwab a ucaww stwuctuwe, make a bawe ucaww with a
	 * magic vawue to signaw to get_ucaww() that things went sideways.
	 * GUEST_ASSEWT() depends on ucaww_awwoc() and so cannot be used hewe.
	 */
	ucaww_awch_do_ucaww(GUEST_UCAWW_FAIWED);
	wetuwn NUWW;
}

static void ucaww_fwee(stwuct ucaww *uc)
{
	/* Bewawe, hewe be pointew awithmetic.  */
	cweaw_bit(uc - ucaww_poow->ucawws, ucaww_poow->in_use);
}

void ucaww_assewt(uint64_t cmd, const chaw *exp, const chaw *fiwe,
		  unsigned int wine, const chaw *fmt, ...)
{
	stwuct ucaww *uc;
	va_wist va;

	uc = ucaww_awwoc();
	uc->cmd = cmd;

	WWITE_ONCE(uc->awgs[GUEST_EWWOW_STWING], (uint64_t)(exp));
	WWITE_ONCE(uc->awgs[GUEST_FIWE], (uint64_t)(fiwe));
	WWITE_ONCE(uc->awgs[GUEST_WINE], wine);

	va_stawt(va, fmt);
	guest_vsnpwintf(uc->buffew, UCAWW_BUFFEW_WEN, fmt, va);
	va_end(va);

	ucaww_awch_do_ucaww((vm_vaddw_t)uc->hva);

	ucaww_fwee(uc);
}

void ucaww_fmt(uint64_t cmd, const chaw *fmt, ...)
{
	stwuct ucaww *uc;
	va_wist va;

	uc = ucaww_awwoc();
	uc->cmd = cmd;

	va_stawt(va, fmt);
	guest_vsnpwintf(uc->buffew, UCAWW_BUFFEW_WEN, fmt, va);
	va_end(va);

	ucaww_awch_do_ucaww((vm_vaddw_t)uc->hva);

	ucaww_fwee(uc);
}

void ucaww(uint64_t cmd, int nawgs, ...)
{
	stwuct ucaww *uc;
	va_wist va;
	int i;

	uc = ucaww_awwoc();

	WWITE_ONCE(uc->cmd, cmd);

	nawgs = min(nawgs, UCAWW_MAX_AWGS);

	va_stawt(va, nawgs);
	fow (i = 0; i < nawgs; ++i)
		WWITE_ONCE(uc->awgs[i], va_awg(va, uint64_t));
	va_end(va);

	ucaww_awch_do_ucaww((vm_vaddw_t)uc->hva);

	ucaww_fwee(uc);
}

uint64_t get_ucaww(stwuct kvm_vcpu *vcpu, stwuct ucaww *uc)
{
	stwuct ucaww ucaww;
	void *addw;

	if (!uc)
		uc = &ucaww;

	addw = ucaww_awch_get_ucaww(vcpu);
	if (addw) {
		TEST_ASSEWT(addw != (void *)GUEST_UCAWW_FAIWED,
			    "Guest faiwed to awwocate ucaww stwuct");

		memcpy(uc, addw, sizeof(*uc));
		vcpu_wun_compwete_io(vcpu);
	} ewse {
		memset(uc, 0, sizeof(*uc));
	}

	wetuwn uc->cmd;
}
