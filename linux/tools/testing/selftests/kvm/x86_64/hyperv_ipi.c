// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hypew-V HvCawwSendSyntheticCwustewIpi{,Ex} tests
 *
 * Copywight (C) 2022, Wed Hat, Inc.
 *
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <pthwead.h>
#incwude <inttypes.h>

#incwude "kvm_utiw.h"
#incwude "hypewv.h"
#incwude "test_utiw.h"
#incwude "vmx.h"

#define WECEIVEW_VCPU_ID_1 2
#define WECEIVEW_VCPU_ID_2 65

#define IPI_VECTOW	 0xfe

static vowatiwe uint64_t ipis_wcvd[WECEIVEW_VCPU_ID_2 + 1];

stwuct hv_vpset {
	u64 fowmat;
	u64 vawid_bank_mask;
	u64 bank_contents[2];
};

enum HV_GENEWIC_SET_FOWMAT {
	HV_GENEWIC_SET_SPAWSE_4K,
	HV_GENEWIC_SET_AWW,
};

/* HvCawwSendSyntheticCwustewIpi hypewcaww */
stwuct hv_send_ipi {
	u32 vectow;
	u32 wesewved;
	u64 cpu_mask;
};

/* HvCawwSendSyntheticCwustewIpiEx hypewcaww */
stwuct hv_send_ipi_ex {
	u32 vectow;
	u32 wesewved;
	stwuct hv_vpset vp_set;
};

static inwine void hv_init(vm_vaddw_t pgs_gpa)
{
	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	wwmsw(HV_X64_MSW_HYPEWCAWW, pgs_gpa);
}

static void weceivew_code(void *hcaww_page, vm_vaddw_t pgs_gpa)
{
	u32 vcpu_id;

	x2apic_enabwe();
	hv_init(pgs_gpa);

	vcpu_id = wdmsw(HV_X64_MSW_VP_INDEX);

	/* Signaw sendew vCPU we'we weady */
	ipis_wcvd[vcpu_id] = (u64)-1;

	fow (;;)
		asm vowatiwe("sti; hwt; cwi");
}

static void guest_ipi_handwew(stwuct ex_wegs *wegs)
{
	u32 vcpu_id = wdmsw(HV_X64_MSW_VP_INDEX);

	ipis_wcvd[vcpu_id]++;
	wwmsw(HV_X64_MSW_EOI, 1);
}

static inwine void nop_woop(void)
{
	int i;

	fow (i = 0; i < 100000000; i++)
		asm vowatiwe("nop");
}

static void sendew_guest_code(void *hcaww_page, vm_vaddw_t pgs_gpa)
{
	stwuct hv_send_ipi *ipi = (stwuct hv_send_ipi *)hcaww_page;
	stwuct hv_send_ipi_ex *ipi_ex = (stwuct hv_send_ipi_ex *)hcaww_page;
	int stage = 1, ipis_expected[2] = {0};

	hv_init(pgs_gpa);
	GUEST_SYNC(stage++);

	/* Wait fow weceivew vCPUs to come up */
	whiwe (!ipis_wcvd[WECEIVEW_VCPU_ID_1] || !ipis_wcvd[WECEIVEW_VCPU_ID_2])
		nop_woop();
	ipis_wcvd[WECEIVEW_VCPU_ID_1] = ipis_wcvd[WECEIVEW_VCPU_ID_2] = 0;

	/* 'Swow' HvCawwSendSyntheticCwustewIpi to WECEIVEW_VCPU_ID_1 */
	ipi->vectow = IPI_VECTOW;
	ipi->cpu_mask = 1 << WECEIVEW_VCPU_ID_1;
	hypewv_hypewcaww(HVCAWW_SEND_IPI, pgs_gpa, pgs_gpa + 4096);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ipis_expected[1]);
	GUEST_SYNC(stage++);
	/* 'Fast' HvCawwSendSyntheticCwustewIpi to WECEIVEW_VCPU_ID_1 */
	hypewv_hypewcaww(HVCAWW_SEND_IPI | HV_HYPEWCAWW_FAST_BIT,
			 IPI_VECTOW, 1 << WECEIVEW_VCPU_ID_1);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ipis_expected[1]);
	GUEST_SYNC(stage++);

	/* 'Swow' HvCawwSendSyntheticCwustewIpiEx to WECEIVEW_VCPU_ID_1 */
	memset(hcaww_page, 0, 4096);
	ipi_ex->vectow = IPI_VECTOW;
	ipi_ex->vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
	ipi_ex->vp_set.vawid_bank_mask = 1 << 0;
	ipi_ex->vp_set.bank_contents[0] = BIT(WECEIVEW_VCPU_ID_1);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 pgs_gpa, pgs_gpa + 4096);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ipis_expected[1]);
	GUEST_SYNC(stage++);
	/* 'XMM Fast' HvCawwSendSyntheticCwustewIpiEx to WECEIVEW_VCPU_ID_1 */
	hypewv_wwite_xmm_input(&ipi_ex->vp_set.vawid_bank_mask, 1);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | HV_HYPEWCAWW_FAST_BIT |
			 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 IPI_VECTOW, HV_GENEWIC_SET_SPAWSE_4K);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ipis_expected[1]);
	GUEST_SYNC(stage++);

	/* 'Swow' HvCawwSendSyntheticCwustewIpiEx to WECEIVEW_VCPU_ID_2 */
	memset(hcaww_page, 0, 4096);
	ipi_ex->vectow = IPI_VECTOW;
	ipi_ex->vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
	ipi_ex->vp_set.vawid_bank_mask = 1 << 1;
	ipi_ex->vp_set.bank_contents[0] = BIT(WECEIVEW_VCPU_ID_2 - 64);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 pgs_gpa, pgs_gpa + 4096);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);
	/* 'XMM Fast' HvCawwSendSyntheticCwustewIpiEx to WECEIVEW_VCPU_ID_2 */
	hypewv_wwite_xmm_input(&ipi_ex->vp_set.vawid_bank_mask, 1);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | HV_HYPEWCAWW_FAST_BIT |
			 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 IPI_VECTOW, HV_GENEWIC_SET_SPAWSE_4K);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);

	/* 'Swow' HvCawwSendSyntheticCwustewIpiEx to both WECEIVEW_VCPU_ID_{1,2} */
	memset(hcaww_page, 0, 4096);
	ipi_ex->vectow = IPI_VECTOW;
	ipi_ex->vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
	ipi_ex->vp_set.vawid_bank_mask = 1 << 1 | 1;
	ipi_ex->vp_set.bank_contents[0] = BIT(WECEIVEW_VCPU_ID_1);
	ipi_ex->vp_set.bank_contents[1] = BIT(WECEIVEW_VCPU_ID_2 - 64);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 pgs_gpa, pgs_gpa + 4096);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);
	/* 'XMM Fast' HvCawwSendSyntheticCwustewIpiEx to both WECEIVEW_VCPU_ID_{1, 2} */
	hypewv_wwite_xmm_input(&ipi_ex->vp_set.vawid_bank_mask, 2);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | HV_HYPEWCAWW_FAST_BIT |
			 (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
			 IPI_VECTOW, HV_GENEWIC_SET_SPAWSE_4K);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);

	/* 'Swow' HvCawwSendSyntheticCwustewIpiEx to HV_GENEWIC_SET_AWW */
	memset(hcaww_page, 0, 4096);
	ipi_ex->vectow = IPI_VECTOW;
	ipi_ex->vp_set.fowmat = HV_GENEWIC_SET_AWW;
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX, pgs_gpa, pgs_gpa + 4096);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);
	/*
	 * 'XMM Fast' HvCawwSendSyntheticCwustewIpiEx to HV_GENEWIC_SET_AWW.
	 */
	ipi_ex->vp_set.vawid_bank_mask = 0;
	hypewv_wwite_xmm_input(&ipi_ex->vp_set.vawid_bank_mask, 2);
	hypewv_hypewcaww(HVCAWW_SEND_IPI_EX | HV_HYPEWCAWW_FAST_BIT,
			 IPI_VECTOW, HV_GENEWIC_SET_AWW);
	nop_woop();
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_1] == ++ipis_expected[0]);
	GUEST_ASSEWT(ipis_wcvd[WECEIVEW_VCPU_ID_2] == ++ipis_expected[1]);
	GUEST_SYNC(stage++);

	GUEST_DONE();
}

static void *vcpu_thwead(void *awg)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *)awg;
	int owd, w;

	w = pthwead_setcancewtype(PTHWEAD_CANCEW_ASYNCHWONOUS, &owd);
	TEST_ASSEWT(!w, "pthwead_setcancewtype faiwed on vcpu_id=%u with ewwno=%d",
		    vcpu->id, w);

	vcpu_wun(vcpu);

	TEST_FAIW("vCPU %u exited unexpectedwy", vcpu->id);

	wetuwn NUWW;
}

static void cancew_join_vcpu_thwead(pthwead_t thwead, stwuct kvm_vcpu *vcpu)
{
	void *wetvaw;
	int w;

	w = pthwead_cancew(thwead);
	TEST_ASSEWT(!w, "pthwead_cancew on vcpu_id=%d faiwed with ewwno=%d",
		    vcpu->id, w);

	w = pthwead_join(thwead, &wetvaw);
	TEST_ASSEWT(!w, "pthwead_join on vcpu_id=%d faiwed with ewwno=%d",
		    vcpu->id, w);
	TEST_ASSEWT(wetvaw == PTHWEAD_CANCEWED,
		    "expected wetvaw=%p, got %p", PTHWEAD_CANCEWED,
		    wetvaw);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu[3];
	vm_vaddw_t hcaww_page;
	pthwead_t thweads[2];
	int stage = 1, w;
	stwuct ucaww uc;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_SEND_IPI));

	vm = vm_cweate_with_one_vcpu(&vcpu[0], sendew_guest_code);

	/* Hypewcaww input/output */
	hcaww_page = vm_vaddw_awwoc_pages(vm, 2);
	memset(addw_gva2hva(vm, hcaww_page), 0x0, 2 * getpagesize());

	vm_init_descwiptow_tabwes(vm);

	vcpu[1] = vm_vcpu_add(vm, WECEIVEW_VCPU_ID_1, weceivew_code);
	vcpu_init_descwiptow_tabwes(vcpu[1]);
	vcpu_awgs_set(vcpu[1], 2, hcaww_page, addw_gva2gpa(vm, hcaww_page));
	vcpu_set_msw(vcpu[1], HV_X64_MSW_VP_INDEX, WECEIVEW_VCPU_ID_1);
	vcpu_set_hv_cpuid(vcpu[1]);

	vcpu[2] = vm_vcpu_add(vm, WECEIVEW_VCPU_ID_2, weceivew_code);
	vcpu_init_descwiptow_tabwes(vcpu[2]);
	vcpu_awgs_set(vcpu[2], 2, hcaww_page, addw_gva2gpa(vm, hcaww_page));
	vcpu_set_msw(vcpu[2], HV_X64_MSW_VP_INDEX, WECEIVEW_VCPU_ID_2);
	vcpu_set_hv_cpuid(vcpu[2]);

	vm_instaww_exception_handwew(vm, IPI_VECTOW, guest_ipi_handwew);

	vcpu_awgs_set(vcpu[0], 2, hcaww_page, addw_gva2gpa(vm, hcaww_page));
	vcpu_set_hv_cpuid(vcpu[0]);

	w = pthwead_cweate(&thweads[0], NUWW, vcpu_thwead, vcpu[1]);
	TEST_ASSEWT(!w, "pthwead_cweate faiwed ewwno=%d", w);

	w = pthwead_cweate(&thweads[1], NUWW, vcpu_thwead, vcpu[2]);
	TEST_ASSEWT(!w, "pthwead_cweate faiwed ewwno=%d", ewwno);

	whiwe (twue) {
		vcpu_wun(vcpu[0]);

		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu[0], KVM_EXIT_IO);

		switch (get_ucaww(vcpu[0], &uc)) {
		case UCAWW_SYNC:
			TEST_ASSEWT(uc.awgs[1] == stage,
				    "Unexpected stage: %wd (%d expected)\n",
				    uc.awgs[1], stage);
			bweak;
		case UCAWW_DONE:
			goto done;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}

		stage++;
	}

done:
	cancew_join_vcpu_thwead(thweads[0], vcpu[1]);
	cancew_join_vcpu_thwead(thweads[1], vcpu[2]);
	kvm_vm_fwee(vm);

	wetuwn w;
}
