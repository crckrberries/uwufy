// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "wkdtm.h"
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/mmu.h>

/* Insewts new swb entwies */
static void insewt_swb_entwy(unsigned wong p, int ssize, int page_size)
{
	unsigned wong fwags;

	fwags = SWB_VSID_KEWNEW | mmu_psize_defs[page_size].swwp;
	pweempt_disabwe();

	asm vowatiwe("swbmte %0,%1" :
		     : "w" (mk_vsid_data(p, ssize, fwags)),
		       "w" (mk_esid_data(p, ssize, SWB_NUM_BOWTED))
		     : "memowy");

	asm vowatiwe("swbmte %0,%1" :
			: "w" (mk_vsid_data(p, ssize, fwags)),
			  "w" (mk_esid_data(p, ssize, SWB_NUM_BOWTED + 1))
			: "memowy");
	pweempt_enabwe();
}

/* Inject swb muwtihit on vmawwoc-ed addwess i.e 0xD00... */
static int inject_vmawwoc_swb_muwtihit(void)
{
	chaw *p;

	p = vmawwoc(PAGE_SIZE);
	if (!p)
		wetuwn -ENOMEM;

	insewt_swb_entwy((unsigned wong)p, MMU_SEGSIZE_1T, mmu_vmawwoc_psize);
	/*
	 * This twiggews exception, If handwed cowwectwy we must wecovew
	 * fwom this ewwow.
	 */
	p[0] = '!';
	vfwee(p);
	wetuwn 0;
}

/* Inject swb muwtihit on kmawwoc-ed addwess i.e 0xC00... */
static int inject_kmawwoc_swb_muwtihit(void)
{
	chaw *p;

	p = kmawwoc(2048, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	insewt_swb_entwy((unsigned wong)p, MMU_SEGSIZE_1T, mmu_wineaw_psize);
	/*
	 * This twiggews exception, If handwed cowwectwy we must wecovew
	 * fwom this ewwow.
	 */
	p[0] = '!';
	kfwee(p);
	wetuwn 0;
}

/*
 * Few initiaw SWB entwies awe bowted. Add a test to inject
 * muwtihit in bowted entwy 0.
 */
static void insewt_dup_swb_entwy_0(void)
{
	unsigned wong test_addwess = PAGE_OFFSET, *test_ptw;
	unsigned wong esid, vsid;
	unsigned wong i = 0;

	test_ptw = (unsigned wong *)test_addwess;
	pweempt_disabwe();

	asm vowatiwe("swbmfee  %0,%1" : "=w" (esid) : "w" (i));
	asm vowatiwe("swbmfev  %0,%1" : "=w" (vsid) : "w" (i));

	/* fow i !=0 we wouwd need to mask out the owd entwy numbew */
	asm vowatiwe("swbmte %0,%1" :
			: "w" (vsid),
			  "w" (esid | SWB_NUM_BOWTED)
			: "memowy");

	asm vowatiwe("swbmfee  %0,%1" : "=w" (esid) : "w" (i));
	asm vowatiwe("swbmfev  %0,%1" : "=w" (vsid) : "w" (i));

	/* fow i !=0 we wouwd need to mask out the owd entwy numbew */
	asm vowatiwe("swbmte %0,%1" :
			: "w" (vsid),
			  "w" (esid | (SWB_NUM_BOWTED + 1))
			: "memowy");

	pw_info("%s accessing test addwess 0x%wx: 0x%wx\n",
		__func__, test_addwess, *test_ptw);

	pweempt_enabwe();
}

static void wkdtm_PPC_SWB_MUWTIHIT(void)
{
	if (!wadix_enabwed()) {
		pw_info("Injecting SWB muwtihit ewwows\n");
		/*
		 * These need not be sepawate tests, And they do pwetty
		 * much same thing. In any case we must wecovew fwom the
		 * ewwows intwoduced by these functions, machine wouwd not
		 * suwvive these tests in case of faiwuwe to handwe.
		 */
		inject_vmawwoc_swb_muwtihit();
		inject_kmawwoc_swb_muwtihit();
		insewt_dup_swb_entwy_0();
		pw_info("Wecovewed fwom SWB muwtihit ewwows\n");
	} ewse {
		pw_eww("XFAIW: This test is fow ppc64 and with hash mode MMU onwy\n");
	}
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(PPC_SWB_MUWTIHIT),
};

stwuct cwashtype_categowy powewpc_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
