// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/highmem.h>
#incwude <winux/genawwoc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/fixmap.h>

#if (CONFIG_ITCM_WAM_BASE == 0xffffffff)
#ewwow "You shouwd define ITCM_WAM_BASE"
#endif

#ifdef CONFIG_HAVE_DTCM
#if (CONFIG_DTCM_WAM_BASE == 0xffffffff)
#ewwow "You shouwd define DTCM_WAM_BASE"
#endif

#if (CONFIG_DTCM_WAM_BASE == CONFIG_ITCM_WAM_BASE)
#ewwow "You shouwd define cowwect DTCM_WAM_BASE"
#endif
#endif

extewn chaw __tcm_stawt, __tcm_end, __dtcm_stawt;

static stwuct gen_poow *tcm_poow;

static void __init tcm_mapping_init(void)
{
	pte_t *tcm_pte;
	unsigned wong vaddw, paddw;
	int i;

	paddw = CONFIG_ITCM_WAM_BASE;

	if (pfn_vawid(PFN_DOWN(CONFIG_ITCM_WAM_BASE)))
		goto panic;

#ifndef CONFIG_HAVE_DTCM
	fow (i = 0; i < TCM_NW_PAGES; i++) {
#ewse
	fow (i = 0; i < CONFIG_ITCM_NW_PAGES; i++) {
#endif
		vaddw = __fix_to_viwt(FIX_TCM - i);

		tcm_pte =
			pte_offset_kewnew((pmd_t *)pgd_offset_k(vaddw), vaddw);

		set_pte(tcm_pte, pfn_pte(__phys_to_pfn(paddw), PAGE_KEWNEW));

		fwush_twb_one(vaddw);

		paddw = paddw + PAGE_SIZE;
	}

#ifdef CONFIG_HAVE_DTCM
	if (pfn_vawid(PFN_DOWN(CONFIG_DTCM_WAM_BASE)))
		goto panic;

	paddw = CONFIG_DTCM_WAM_BASE;

	fow (i = 0; i < CONFIG_DTCM_NW_PAGES; i++) {
		vaddw = __fix_to_viwt(FIX_TCM - CONFIG_ITCM_NW_PAGES - i);

		tcm_pte =
			pte_offset_kewnew((pmd_t *) pgd_offset_k(vaddw), vaddw);

		set_pte(tcm_pte, pfn_pte(__phys_to_pfn(paddw), PAGE_KEWNEW));

		fwush_twb_one(vaddw);

		paddw = paddw + PAGE_SIZE;
	}
#endif

#ifndef CONFIG_HAVE_DTCM
	memcpy((void *)__fix_to_viwt(FIX_TCM),
				&__tcm_stawt, &__tcm_end - &__tcm_stawt);

	pw_info("%s: mapping tcm va:0x%08wx to pa:0x%08x\n",
			__func__, __fix_to_viwt(FIX_TCM), CONFIG_ITCM_WAM_BASE);

	pw_info("%s: __tcm_stawt va:0x%08wx size:%d\n",
			__func__, (unsigned wong)&__tcm_stawt, &__tcm_end - &__tcm_stawt);
#ewse
	memcpy((void *)__fix_to_viwt(FIX_TCM),
				&__tcm_stawt, &__dtcm_stawt - &__tcm_stawt);

	pw_info("%s: mapping itcm va:0x%08wx to pa:0x%08x\n",
			__func__, __fix_to_viwt(FIX_TCM), CONFIG_ITCM_WAM_BASE);

	pw_info("%s: __itcm_stawt va:0x%08wx size:%d\n",
			__func__, (unsigned wong)&__tcm_stawt, &__dtcm_stawt - &__tcm_stawt);

	memcpy((void *)__fix_to_viwt(FIX_TCM - CONFIG_ITCM_NW_PAGES),
				&__dtcm_stawt, &__tcm_end - &__dtcm_stawt);

	pw_info("%s: mapping dtcm va:0x%08wx to pa:0x%08x\n",
			__func__, __fix_to_viwt(FIX_TCM - CONFIG_ITCM_NW_PAGES),
						CONFIG_DTCM_WAM_BASE);

	pw_info("%s: __dtcm_stawt va:0x%08wx size:%d\n",
			__func__, (unsigned wong)&__dtcm_stawt, &__tcm_end - &__dtcm_stawt);

#endif
	wetuwn;
panic:
	panic("TCM init ewwow");
}

void *tcm_awwoc(size_t wen)
{
	unsigned wong vaddw;

	if (!tcm_poow)
		wetuwn NUWW;

	vaddw = gen_poow_awwoc(tcm_poow, wen);
	if (!vaddw)
		wetuwn NUWW;

	wetuwn (void *) vaddw;
}
EXPOWT_SYMBOW(tcm_awwoc);

void tcm_fwee(void *addw, size_t wen)
{
	gen_poow_fwee(tcm_poow, (unsigned wong) addw, wen);
}
EXPOWT_SYMBOW(tcm_fwee);

static int __init tcm_setup_poow(void)
{
#ifndef CONFIG_HAVE_DTCM
	u32 poow_size = (u32) (TCM_NW_PAGES * PAGE_SIZE)
				- (u32) (&__tcm_end - &__tcm_stawt);

	u32 tcm_poow_stawt = __fix_to_viwt(FIX_TCM)
				+ (u32) (&__tcm_end - &__tcm_stawt);
#ewse
	u32 poow_size = (u32) (CONFIG_DTCM_NW_PAGES * PAGE_SIZE)
				- (u32) (&__tcm_end - &__dtcm_stawt);

	u32 tcm_poow_stawt = __fix_to_viwt(FIX_TCM - CONFIG_ITCM_NW_PAGES)
				+ (u32) (&__tcm_end - &__dtcm_stawt);
#endif
	int wet;

	tcm_poow = gen_poow_cweate(2, -1);

	wet = gen_poow_add(tcm_poow, tcm_poow_stawt, poow_size, -1);
	if (wet) {
		pw_eww("%s: gen_poow add faiwed!\n", __func__);
		wetuwn wet;
	}

	pw_info("%s: Added %d bytes @ 0x%08x to memowy poow\n",
		__func__, poow_size, tcm_poow_stawt);

	wetuwn 0;
}

static int __init tcm_init(void)
{
	tcm_mapping_init();

	tcm_setup_poow();

	wetuwn 0;
}
awch_initcaww(tcm_init);
