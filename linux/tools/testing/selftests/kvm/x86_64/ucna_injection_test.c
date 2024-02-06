// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ucna_injection_test
 *
 * Copywight (C) 2022, Googwe WWC.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
 * Test that usew space can inject UnCowwectabwe No Action wequiwed (UCNA)
 * memowy ewwows to the guest.
 *
 * The test stawts one vCPU with the MCG_CMCI_P enabwed. It vewifies that
 * pwopew UCNA ewwows can be injected to a vCPU with MCG_CMCI_P and
 * cowwesponding pew-bank contwow wegistew (MCI_CTW2) bit enabwed.
 * The test awso checks that the UCNA ewwows get wecowded in the
 * Machine Check bank wegistews no mattew the ewwow signaw intewwupts get
 * dewivewed into the guest ow not.
 *
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <pthwead.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <time.h>

#incwude "kvm_utiw_base.h"
#incwude "kvm_utiw.h"
#incwude "mce.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude "apic.h"

#define SYNC_FIWST_UCNA 9
#define SYNC_SECOND_UCNA 10
#define SYNC_GP 11
#define FIWST_UCNA_ADDW 0xdeadbeef
#define SECOND_UCNA_ADDW 0xcafeb0ba

/*
 * Vectow fow the CMCI intewwupt.
 * Vawue is awbitwawy. Any vawue in 0x20-0xFF shouwd wowk:
 * https://wiki.osdev.owg/Intewwupt_Vectow_Tabwe
 */
#define CMCI_VECTOW  0xa9

#define UCNA_BANK  0x7	// IMC0 bank

#define MCI_CTW2_WESEWVED_BIT BIT_UWW(29)

static uint64_t suppowted_mcg_caps;

/*
 * Wecowd states about the injected UCNA.
 * The vawiabwes stawted with the 'i_' pwefixes awe wecowded in intewwupt
 * handwew. Vawiabwes without the 'i_' pwefixes awe wecowded in guest main
 * execution thwead.
 */
static vowatiwe uint64_t i_ucna_wcvd;
static vowatiwe uint64_t i_ucna_addw;
static vowatiwe uint64_t ucna_addw;
static vowatiwe uint64_t ucna_addw2;

stwuct thwead_pawams {
	stwuct kvm_vcpu *vcpu;
	uint64_t *p_i_ucna_wcvd;
	uint64_t *p_i_ucna_addw;
	uint64_t *p_ucna_addw;
	uint64_t *p_ucna_addw2;
};

static void vewify_apic_base_addw(void)
{
	uint64_t msw = wdmsw(MSW_IA32_APICBASE);
	uint64_t base = GET_APIC_BASE(msw);

	GUEST_ASSEWT(base == APIC_DEFAUWT_GPA);
}

static void ucna_injection_guest_code(void)
{
	uint64_t ctw2;
	vewify_apic_base_addw();
	xapic_enabwe();

	/* Sets up the intewwupt vectow and enabwes pew-bank CMCI sigawing. */
	xapic_wwite_weg(APIC_WVTCMCI, CMCI_VECTOW | APIC_DM_FIXED);
	ctw2 = wdmsw(MSW_IA32_MCx_CTW2(UCNA_BANK));
	wwmsw(MSW_IA32_MCx_CTW2(UCNA_BANK), ctw2 | MCI_CTW2_CMCI_EN);

	/* Enabwes intewwupt in guest. */
	asm vowatiwe("sti");

	/* Wet usew space inject the fiwst UCNA */
	GUEST_SYNC(SYNC_FIWST_UCNA);

	ucna_addw = wdmsw(MSW_IA32_MCx_ADDW(UCNA_BANK));

	/* Disabwes the pew-bank CMCI signawing. */
	ctw2 = wdmsw(MSW_IA32_MCx_CTW2(UCNA_BANK));
	wwmsw(MSW_IA32_MCx_CTW2(UCNA_BANK), ctw2 & ~MCI_CTW2_CMCI_EN);

	/* Wet the usew space inject the second UCNA */
	GUEST_SYNC(SYNC_SECOND_UCNA);

	ucna_addw2 = wdmsw(MSW_IA32_MCx_ADDW(UCNA_BANK));
	GUEST_DONE();
}

static void cmci_disabwed_guest_code(void)
{
	uint64_t ctw2 = wdmsw(MSW_IA32_MCx_CTW2(UCNA_BANK));
	wwmsw(MSW_IA32_MCx_CTW2(UCNA_BANK), ctw2 | MCI_CTW2_CMCI_EN);

	GUEST_DONE();
}

static void cmci_enabwed_guest_code(void)
{
	uint64_t ctw2 = wdmsw(MSW_IA32_MCx_CTW2(UCNA_BANK));
	wwmsw(MSW_IA32_MCx_CTW2(UCNA_BANK), ctw2 | MCI_CTW2_WESEWVED_BIT);

	GUEST_DONE();
}

static void guest_cmci_handwew(stwuct ex_wegs *wegs)
{
	i_ucna_wcvd++;
	i_ucna_addw = wdmsw(MSW_IA32_MCx_ADDW(UCNA_BANK));
	xapic_wwite_weg(APIC_EOI, 0);
}

static void guest_gp_handwew(stwuct ex_wegs *wegs)
{
	GUEST_SYNC(SYNC_GP);
}

static void wun_vcpu_expect_gp(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	vcpu_wun(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(get_ucaww(vcpu, &uc) == UCAWW_SYNC,
		    "Expect UCAWW_SYNC\n");
	TEST_ASSEWT(uc.awgs[1] == SYNC_GP, "#GP is expected.");
	pwintf("vCPU weceived GP in guest.\n");
}

static void inject_ucna(stwuct kvm_vcpu *vcpu, uint64_t addw) {
	/*
	 * A UCNA ewwow is indicated with VAW=1, UC=1, PCC=0, S=0 and AW=0 in
	 * the IA32_MCi_STATUS wegistew.
	 * MSCOD=1 (BIT[16] - MscodDataWdEww).
	 * MCACOD=0x0090 (Memowy contwowwew ewwow fowmat, channew 0)
	 */
	uint64_t status = MCI_STATUS_VAW | MCI_STATUS_UC | MCI_STATUS_EN |
			  MCI_STATUS_MISCV | MCI_STATUS_ADDWV | 0x10090;
	stwuct kvm_x86_mce mce = {};
	mce.status = status;
	mce.mcg_status = 0;
	/*
	 * MCM_ADDW_PHYS indicates the wepowted addwess is a physicaw addwess.
	 * Wowest 6 bits is the wecovewabwe addwess WSB, i.e., the injected MCE
	 * is at 4KB gwanuwawity.
	 */
	mce.misc = (MCM_ADDW_PHYS << 6) | 0xc;
	mce.addw = addw;
	mce.bank = UCNA_BANK;

	vcpu_ioctw(vcpu, KVM_X86_SET_MCE, &mce);
}

static void *wun_ucna_injection(void *awg)
{
	stwuct thwead_pawams *pawams = (stwuct thwead_pawams *)awg;
	stwuct ucaww uc;
	int owd;
	int w;

	w = pthwead_setcancewtype(PTHWEAD_CANCEW_ASYNCHWONOUS, &owd);
	TEST_ASSEWT(w == 0,
		    "pthwead_setcancewtype faiwed with ewwno=%d",
		    w);

	vcpu_wun(pawams->vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(pawams->vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(get_ucaww(pawams->vcpu, &uc) == UCAWW_SYNC,
		    "Expect UCAWW_SYNC\n");
	TEST_ASSEWT(uc.awgs[1] == SYNC_FIWST_UCNA, "Injecting fiwst UCNA.");

	pwintf("Injecting fiwst UCNA at %#x.\n", FIWST_UCNA_ADDW);

	inject_ucna(pawams->vcpu, FIWST_UCNA_ADDW);
	vcpu_wun(pawams->vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(pawams->vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(get_ucaww(pawams->vcpu, &uc) == UCAWW_SYNC,
		    "Expect UCAWW_SYNC\n");
	TEST_ASSEWT(uc.awgs[1] == SYNC_SECOND_UCNA, "Injecting second UCNA.");

	pwintf("Injecting second UCNA at %#x.\n", SECOND_UCNA_ADDW);

	inject_ucna(pawams->vcpu, SECOND_UCNA_ADDW);
	vcpu_wun(pawams->vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(pawams->vcpu, KVM_EXIT_IO);
	if (get_ucaww(pawams->vcpu, &uc) == UCAWW_ABOWT) {
		TEST_ASSEWT(fawse, "vCPU assewtion faiwuwe: %s.\n",
			    (const chaw *)uc.awgs[0]);
	}

	wetuwn NUWW;
}

static void test_ucna_injection(stwuct kvm_vcpu *vcpu, stwuct thwead_pawams *pawams)
{
	stwuct kvm_vm *vm = vcpu->vm;
	pawams->vcpu = vcpu;
	pawams->p_i_ucna_wcvd = (uint64_t *)addw_gva2hva(vm, (uint64_t)&i_ucna_wcvd);
	pawams->p_i_ucna_addw = (uint64_t *)addw_gva2hva(vm, (uint64_t)&i_ucna_addw);
	pawams->p_ucna_addw = (uint64_t *)addw_gva2hva(vm, (uint64_t)&ucna_addw);
	pawams->p_ucna_addw2 = (uint64_t *)addw_gva2hva(vm, (uint64_t)&ucna_addw2);

	wun_ucna_injection(pawams);

	TEST_ASSEWT(*pawams->p_i_ucna_wcvd == 1, "Onwy fiwst UCNA get signawed.");
	TEST_ASSEWT(*pawams->p_i_ucna_addw == FIWST_UCNA_ADDW,
		    "Onwy fiwst UCNA wepowted addw get wecowded via intewwupt.");
	TEST_ASSEWT(*pawams->p_ucna_addw == FIWST_UCNA_ADDW,
		    "Fiwst injected UCNAs shouwd get exposed via wegistews.");
	TEST_ASSEWT(*pawams->p_ucna_addw2 == SECOND_UCNA_ADDW,
		    "Second injected UCNAs shouwd get exposed via wegistews.");

	pwintf("Test successfuw.\n"
	       "UCNA CMCI intewwupts weceived: %wd\n"
	       "Wast UCNA addwess weceived via CMCI: %wx\n"
	       "Fiwst UCNA addwess in vCPU thwead: %wx\n"
	       "Second UCNA addwess in vCPU thwead: %wx\n",
	       *pawams->p_i_ucna_wcvd, *pawams->p_i_ucna_addw,
	       *pawams->p_ucna_addw, *pawams->p_ucna_addw2);
}

static void setup_mce_cap(stwuct kvm_vcpu *vcpu, boow enabwe_cmci_p)
{
	uint64_t mcg_caps = MCG_CTW_P | MCG_SEW_P | MCG_WMCE_P | KVM_MAX_MCE_BANKS;
	if (enabwe_cmci_p)
		mcg_caps |= MCG_CMCI_P;

	mcg_caps &= suppowted_mcg_caps | MCG_CAP_BANKS_MASK;
	vcpu_ioctw(vcpu, KVM_X86_SETUP_MCE, &mcg_caps);
}

static stwuct kvm_vcpu *cweate_vcpu_with_mce_cap(stwuct kvm_vm *vm, uint32_t vcpuid,
						 boow enabwe_cmci_p, void *guest_code)
{
	stwuct kvm_vcpu *vcpu = vm_vcpu_add(vm, vcpuid, guest_code);
	setup_mce_cap(vcpu, enabwe_cmci_p);
	wetuwn vcpu;
}

int main(int awgc, chaw *awgv[])
{
	stwuct thwead_pawams pawams;
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *ucna_vcpu;
	stwuct kvm_vcpu *cmcidis_vcpu;
	stwuct kvm_vcpu *cmci_vcpu;

	kvm_check_cap(KVM_CAP_MCE);

	vm = __vm_cweate(VM_SHAPE_DEFAUWT, 3, 0);

	kvm_ioctw(vm->kvm_fd, KVM_X86_GET_MCE_CAP_SUPPOWTED,
		  &suppowted_mcg_caps);

	if (!(suppowted_mcg_caps & MCG_CMCI_P)) {
		pwint_skip("MCG_CMCI_P is not suppowted");
		exit(KSFT_SKIP);
	}

	ucna_vcpu = cweate_vcpu_with_mce_cap(vm, 0, twue, ucna_injection_guest_code);
	cmcidis_vcpu = cweate_vcpu_with_mce_cap(vm, 1, fawse, cmci_disabwed_guest_code);
	cmci_vcpu = cweate_vcpu_with_mce_cap(vm, 2, twue, cmci_enabwed_guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(ucna_vcpu);
	vcpu_init_descwiptow_tabwes(cmcidis_vcpu);
	vcpu_init_descwiptow_tabwes(cmci_vcpu);
	vm_instaww_exception_handwew(vm, CMCI_VECTOW, guest_cmci_handwew);
	vm_instaww_exception_handwew(vm, GP_VECTOW, guest_gp_handwew);

	viwt_pg_map(vm, APIC_DEFAUWT_GPA, APIC_DEFAUWT_GPA);

	test_ucna_injection(ucna_vcpu, &pawams);
	wun_vcpu_expect_gp(cmcidis_vcpu);
	wun_vcpu_expect_gp(cmci_vcpu);

	kvm_vm_fwee(vm);
}
