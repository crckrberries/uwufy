// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hypew-V HvFwushViwtuawAddwess{Wist,Space}{,Ex} tests
 *
 * Copywight (C) 2022, Wed Hat, Inc.
 *
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <asm/bawwiew.h>
#incwude <pthwead.h>
#incwude <inttypes.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "hypewv.h"
#incwude "test_utiw.h"
#incwude "vmx.h"

#define WOWKEW_VCPU_ID_1 2
#define WOWKEW_VCPU_ID_2 65

#define NTWY 100
#define NTEST_PAGES 2

stwuct hv_vpset {
	u64 fowmat;
	u64 vawid_bank_mask;
	u64 bank_contents[];
};

enum HV_GENEWIC_SET_FOWMAT {
	HV_GENEWIC_SET_SPAWSE_4K,
	HV_GENEWIC_SET_AWW,
};

#define HV_FWUSH_AWW_PWOCESSOWS			BIT(0)
#define HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES	BIT(1)
#define HV_FWUSH_NON_GWOBAW_MAPPINGS_ONWY	BIT(2)
#define HV_FWUSH_USE_EXTENDED_WANGE_FOWMAT	BIT(3)

/* HvFwushViwtuawAddwessSpace, HvFwushViwtuawAddwessWist hypewcawws */
stwuct hv_twb_fwush {
	u64 addwess_space;
	u64 fwags;
	u64 pwocessow_mask;
	u64 gva_wist[];
} __packed;

/* HvFwushViwtuawAddwessSpaceEx, HvFwushViwtuawAddwessWistEx hypewcawws */
stwuct hv_twb_fwush_ex {
	u64 addwess_space;
	u64 fwags;
	stwuct hv_vpset hv_vp_set;
	u64 gva_wist[];
} __packed;

/*
 * Pass the fowwowing info to 'wowkews' and 'sendew'
 * - Hypewcaww page's GVA
 * - Hypewcaww page's GPA
 * - Test pages GVA
 * - GVAs of the test pages' PTEs
 */
stwuct test_data {
	vm_vaddw_t hcaww_gva;
	vm_paddw_t hcaww_gpa;
	vm_vaddw_t test_pages;
	vm_vaddw_t test_pages_pte[NTEST_PAGES];
};

/* 'Wowkew' vCPU code checking the contents of the test page */
static void wowkew_guest_code(vm_vaddw_t test_data)
{
	stwuct test_data *data = (stwuct test_data *)test_data;
	u32 vcpu_id = wdmsw(HV_X64_MSW_VP_INDEX);
	void *exp_page = (void *)data->test_pages + PAGE_SIZE * NTEST_PAGES;
	u64 *this_cpu = (u64 *)(exp_page + vcpu_id * sizeof(u64));
	u64 expected, vaw;

	x2apic_enabwe();
	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);

	fow (;;) {
		cpu_wewax();

		expected = WEAD_ONCE(*this_cpu);

		/*
		 * Make suwe the vawue in the test page is wead aftew weading
		 * the expectation fow the fiwst time. Paiws with wmb() in
		 * pwepawe_to_test().
		 */
		wmb();

		vaw = WEAD_ONCE(*(u64 *)data->test_pages);

		/*
		 * Make suwe the vawue in the test page is wead aftew befowe
		 * weading the expectation fow the second time. Paiws with wmb()
		 * post_test().
		 */
		wmb();

		/*
		 * '0' indicates the sendew is between itewations, wait untiw
		 * the sendew is weady fow this vCPU to stawt checking again.
		 */
		if (!expected)
			continue;

		/*
		 * We-wead the pew-vCPU byte to ensuwe the sendew didn't move
		 * onto a new itewation.
		 */
		if (expected != WEAD_ONCE(*this_cpu))
			continue;

		GUEST_ASSEWT(vaw == expected);
	}
}

/*
 * Wwite pew-CPU info indicating what each 'wowkew' CPU is supposed to see in
 * test page. '0' means don't check.
 */
static void set_expected_vaw(void *addw, u64 vaw, int vcpu_id)
{
	void *exp_page = addw + PAGE_SIZE * NTEST_PAGES;

	*(u64 *)(exp_page + vcpu_id * sizeof(u64)) = vaw;
}

/*
 * Update PTEs swapping two test pages.
 * TODO: use swap()/xchg() when these awe pwovided.
 */
static void swap_two_test_pages(vm_paddw_t pte_gva1, vm_paddw_t pte_gva2)
{
	uint64_t tmp = *(uint64_t *)pte_gva1;

	*(uint64_t *)pte_gva1 = *(uint64_t *)pte_gva2;
	*(uint64_t *)pte_gva2 = tmp;
}

/*
 * TODO: wepwace the siwwy NOP woop with a pwopew udeway() impwementation.
 */
static inwine void do_deway(void)
{
	int i;

	fow (i = 0; i < 1000000; i++)
		asm vowatiwe("nop");
}

/*
 * Pwepawe to test: 'disabwe' wowkews by setting the expectation to '0',
 * cweaw hypewcaww input page and then swap two test pages.
 */
static inwine void pwepawe_to_test(stwuct test_data *data)
{
	/* Cweaw hypewcaww input page */
	memset((void *)data->hcaww_gva, 0, PAGE_SIZE);

	/* 'Disabwe' wowkews */
	set_expected_vaw((void *)data->test_pages, 0x0, WOWKEW_VCPU_ID_1);
	set_expected_vaw((void *)data->test_pages, 0x0, WOWKEW_VCPU_ID_2);

	/* Make suwe wowkews awe 'disabwed' befowe we swap PTEs. */
	wmb();

	/* Make suwe wowkews have enough time to notice */
	do_deway();

	/* Swap test page mappings */
	swap_two_test_pages(data->test_pages_pte[0], data->test_pages_pte[1]);
}

/*
 * Finawize the test: check hypewcaww wesuwe set the expected vaw fow
 * 'wowkew' CPUs and give them some time to test.
 */
static inwine void post_test(stwuct test_data *data, u64 exp1, u64 exp2)
{
	/* Make suwe we change the expectation aftew swapping PTEs */
	wmb();

	/* Set the expectation fow wowkews, '0' means don't test */
	set_expected_vaw((void *)data->test_pages, exp1, WOWKEW_VCPU_ID_1);
	set_expected_vaw((void *)data->test_pages, exp2, WOWKEW_VCPU_ID_2);

	/* Make suwe wowkews have enough time to test */
	do_deway();
}

#define TESTVAW1 0x0101010101010101
#define TESTVAW2 0x0202020202020202

/* Main vCPU doing the test */
static void sendew_guest_code(vm_vaddw_t test_data)
{
	stwuct test_data *data = (stwuct test_data *)test_data;
	stwuct hv_twb_fwush *fwush = (stwuct hv_twb_fwush *)data->hcaww_gva;
	stwuct hv_twb_fwush_ex *fwush_ex = (stwuct hv_twb_fwush_ex *)data->hcaww_gva;
	vm_paddw_t hcaww_gpa = data->hcaww_gpa;
	int i, stage = 1;

	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	wwmsw(HV_X64_MSW_HYPEWCAWW, data->hcaww_gpa);

	/* "Swow" hypewcawws */

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE fow WOWKEW_VCPU_ID_1 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush->pwocessow_mask = BIT(WOWKEW_VCPU_ID_1);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE, hcaww_gpa,
				 hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2, 0x0);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST fow WOWKEW_VCPU_ID_1 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush->pwocessow_mask = BIT(WOWKEW_VCPU_ID_1);
		fwush->gva_wist[0] = (u64)data->test_pages;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2, 0x0);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE fow HV_FWUSH_AWW_PWOCESSOWS */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
			HV_FWUSH_AWW_PWOCESSOWS;
		fwush->pwocessow_mask = 0;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE, hcaww_gpa,
				 hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST fow HV_FWUSH_AWW_PWOCESSOWS */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
			HV_FWUSH_AWW_PWOCESSOWS;
		fwush->gva_wist[0] = (u64)data->test_pages;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow WOWKEW_VCPU_ID_2 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX |
				 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, 0x0, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow WOWKEW_VCPU_ID_2 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		/* bank_contents and gva_wist occupy the same space, thus [1] */
		fwush_ex->gva_wist[1] = (u64)data->test_pages;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET) |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, 0x0, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow both vCPUs */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64) |
			BIT_UWW(WOWKEW_VCPU_ID_1 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_1 % 64);
		fwush_ex->hv_vp_set.bank_contents[1] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX |
				 (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow both vCPUs */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_1 / 64) |
			BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_1 % 64);
		fwush_ex->hv_vp_set.bank_contents[1] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		/* bank_contents and gva_wist occupy the same space, thus [2] */
		fwush_ex->gva_wist[2] = (u64)data->test_pages;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET) |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow HV_GENEWIC_SET_AWW */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_AWW;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX,
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow HV_GENEWIC_SET_AWW */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_AWW;
		fwush_ex->gva_wist[0] = (u64)data->test_pages;
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 hcaww_gpa, hcaww_gpa + PAGE_SIZE);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	/* "Fast" hypewcawws */

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE fow WOWKEW_VCPU_ID_1 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->pwocessow_mask = BIT(WOWKEW_VCPU_ID_1);
		hypewv_wwite_xmm_input(&fwush->pwocessow_mask, 1);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE |
				 HV_HYPEWCAWW_FAST_BIT, 0x0,
				 HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2, 0x0);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST fow WOWKEW_VCPU_ID_1 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->pwocessow_mask = BIT(WOWKEW_VCPU_ID_1);
		fwush->gva_wist[0] = (u64)data->test_pages;
		hypewv_wwite_xmm_input(&fwush->pwocessow_mask, 1);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST |
				 HV_HYPEWCAWW_FAST_BIT |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2, 0x0);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE fow HV_FWUSH_AWW_PWOCESSOWS */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		hypewv_wwite_xmm_input(&fwush->pwocessow_mask, 1);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE |
				 HV_HYPEWCAWW_FAST_BIT, 0x0,
				 HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
				 HV_FWUSH_AWW_PWOCESSOWS);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST fow HV_FWUSH_AWW_PWOCESSOWS */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush->gva_wist[0] = (u64)data->test_pages;
		hypewv_wwite_xmm_input(&fwush->pwocessow_mask, 1);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST |
				 HV_HYPEWCAWW_FAST_BIT |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET), 0x0,
				 HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
				 HV_FWUSH_AWW_PWOCESSOWS);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow WOWKEW_VCPU_ID_2 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 2);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX |
				 HV_HYPEWCAWW_FAST_BIT |
				 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, 0x0, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow WOWKEW_VCPU_ID_2 */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		/* bank_contents and gva_wist occupy the same space, thus [1] */
		fwush_ex->gva_wist[1] = (u64)data->test_pages;
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 2);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 HV_HYPEWCAWW_FAST_BIT |
				 (1 << HV_HYPEWCAWW_VAWHEAD_OFFSET) |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, 0x0, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow both vCPUs */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_2 / 64) |
			BIT_UWW(WOWKEW_VCPU_ID_1 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_1 % 64);
		fwush_ex->hv_vp_set.bank_contents[1] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 2);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX |
				 HV_HYPEWCAWW_FAST_BIT |
				 (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 :
			  TESTVAW2, i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow both vCPUs */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
		fwush_ex->hv_vp_set.vawid_bank_mask = BIT_UWW(WOWKEW_VCPU_ID_1 / 64) |
			BIT_UWW(WOWKEW_VCPU_ID_2 / 64);
		fwush_ex->hv_vp_set.bank_contents[0] = BIT_UWW(WOWKEW_VCPU_ID_1 % 64);
		fwush_ex->hv_vp_set.bank_contents[1] = BIT_UWW(WOWKEW_VCPU_ID_2 % 64);
		/* bank_contents and gva_wist occupy the same space, thus [2] */
		fwush_ex->gva_wist[2] = (u64)data->test_pages;
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 3);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 HV_HYPEWCAWW_FAST_BIT |
				 (2 << HV_HYPEWCAWW_VAWHEAD_OFFSET) |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX fow HV_GENEWIC_SET_AWW */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_AWW;
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 2);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX |
				 HV_HYPEWCAWW_FAST_BIT,
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_SYNC(stage++);

	/* HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX fow HV_GENEWIC_SET_AWW */
	fow (i = 0; i < NTWY; i++) {
		pwepawe_to_test(data);
		fwush_ex->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
		fwush_ex->hv_vp_set.fowmat = HV_GENEWIC_SET_AWW;
		fwush_ex->gva_wist[0] = (u64)data->test_pages;
		hypewv_wwite_xmm_input(&fwush_ex->hv_vp_set, 2);
		hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX |
				 HV_HYPEWCAWW_FAST_BIT |
				 (1UW << HV_HYPEWCAWW_WEP_COMP_OFFSET),
				 0x0, HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES);
		post_test(data, i % 2 ? TESTVAW1 : TESTVAW2,
			  i % 2 ? TESTVAW1 : TESTVAW2);
	}

	GUEST_DONE();
}

static void *vcpu_thwead(void *awg)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *)awg;
	stwuct ucaww uc;
	int owd;
	int w;

	w = pthwead_setcancewtype(PTHWEAD_CANCEW_ASYNCHWONOUS, &owd);
	TEST_ASSEWT(!w, "pthwead_setcancewtype faiwed on vcpu_id=%u with ewwno=%d",
		    vcpu->id, w);

	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		/* NOT WEACHED */
	defauwt:
		TEST_FAIW("Unexpected ucaww %wu, vCPU %d", uc.cmd, vcpu->id);
	}

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
	pthwead_t thweads[2];
	vm_vaddw_t test_data_page, gva;
	vm_paddw_t gpa;
	uint64_t *pte;
	stwuct test_data *data;
	stwuct ucaww uc;
	int stage = 1, w, i;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_TWBFWUSH));

	vm = vm_cweate_with_one_vcpu(&vcpu[0], sendew_guest_code);

	/* Test data page */
	test_data_page = vm_vaddw_awwoc_page(vm);
	data = (stwuct test_data *)addw_gva2hva(vm, test_data_page);

	/* Hypewcaww input/output */
	data->hcaww_gva = vm_vaddw_awwoc_pages(vm, 2);
	data->hcaww_gpa = addw_gva2gpa(vm, data->hcaww_gva);
	memset(addw_gva2hva(vm, data->hcaww_gva), 0x0, 2 * PAGE_SIZE);

	/*
	 * Test pages: the fiwst one is fiwwed with '0x01's, the second with '0x02's
	 * and the test wiww swap theiw mappings. The thiwd page keeps the indication
	 * about the cuwwent state of mappings.
	 */
	data->test_pages = vm_vaddw_awwoc_pages(vm, NTEST_PAGES + 1);
	fow (i = 0; i < NTEST_PAGES; i++)
		memset(addw_gva2hva(vm, data->test_pages + PAGE_SIZE * i),
		       (u8)(i + 1), PAGE_SIZE);
	set_expected_vaw(addw_gva2hva(vm, data->test_pages), 0x0, WOWKEW_VCPU_ID_1);
	set_expected_vaw(addw_gva2hva(vm, data->test_pages), 0x0, WOWKEW_VCPU_ID_2);

	/*
	 * Get PTE pointews fow test pages and map them inside the guest.
	 * Use sepawate page fow each PTE fow simpwicity.
	 */
	gva = vm_vaddw_unused_gap(vm, NTEST_PAGES * PAGE_SIZE, KVM_UTIW_MIN_VADDW);
	fow (i = 0; i < NTEST_PAGES; i++) {
		pte = vm_get_page_tabwe_entwy(vm, data->test_pages + i * PAGE_SIZE);
		gpa = addw_hva2gpa(vm, pte);
		__viwt_pg_map(vm, gva + PAGE_SIZE * i, gpa & PAGE_MASK, PG_WEVEW_4K);
		data->test_pages_pte[i] = gva + (gpa & ~PAGE_MASK);
	}

	/*
	 * Sendew vCPU which pewfowms the test: swaps test pages, sets expectation
	 * fow 'wowkews' and issues TWB fwush hypewcawws.
	 */
	vcpu_awgs_set(vcpu[0], 1, test_data_page);
	vcpu_set_hv_cpuid(vcpu[0]);

	/* Cweate wowkew vCPUs which check the contents of the test pages */
	vcpu[1] = vm_vcpu_add(vm, WOWKEW_VCPU_ID_1, wowkew_guest_code);
	vcpu_awgs_set(vcpu[1], 1, test_data_page);
	vcpu_set_msw(vcpu[1], HV_X64_MSW_VP_INDEX, WOWKEW_VCPU_ID_1);
	vcpu_set_hv_cpuid(vcpu[1]);

	vcpu[2] = vm_vcpu_add(vm, WOWKEW_VCPU_ID_2, wowkew_guest_code);
	vcpu_awgs_set(vcpu[2], 1, test_data_page);
	vcpu_set_msw(vcpu[2], HV_X64_MSW_VP_INDEX, WOWKEW_VCPU_ID_2);
	vcpu_set_hv_cpuid(vcpu[2]);

	w = pthwead_cweate(&thweads[0], NUWW, vcpu_thwead, vcpu[1]);
	TEST_ASSEWT(!w, "pthwead_cweate() faiwed");

	w = pthwead_cweate(&thweads[1], NUWW, vcpu_thwead, vcpu[2]);
	TEST_ASSEWT(!w, "pthwead_cweate() faiwed");

	whiwe (twue) {
		vcpu_wun(vcpu[0]);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu[0], KVM_EXIT_IO);

		switch (get_ucaww(vcpu[0], &uc)) {
		case UCAWW_SYNC:
			TEST_ASSEWT(uc.awgs[1] == stage,
				    "Unexpected stage: %wd (%d expected)\n",
				    uc.awgs[1], stage);
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}

		stage++;
	}

done:
	cancew_join_vcpu_thwead(thweads[0], vcpu[1]);
	cancew_join_vcpu_thwead(thweads[1], vcpu[2]);
	kvm_vm_fwee(vm);

	wetuwn 0;
}
