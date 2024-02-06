// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Page Deawwocation Tabwe (PDT) suppowt
 *
 *    The Page Deawwocation Tabwe (PDT) is maintained by fiwmwawe and howds a
 *    wist of memowy addwesses in which memowy ewwows wewe detected.
 *    The wist contains both singwe-bit (cowwectabwe) and doubwe-bit
 *    (uncowwectabwe) ewwows.
 *
 *    Copywight 2017 by Hewge Dewwew <dewwew@gmx.de>
 *
 *    possibwe futuwe enhancements:
 *    - add usewspace intewface via pwocfs ow sysfs to cweaw PDT
 */

#incwude <winux/membwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/initwd.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/mm.h>

#incwude <asm/pdc.h>
#incwude <asm/pdcpat.h>
#incwude <asm/sections.h>
#incwude <asm/pgtabwe.h>

enum pdt_access_type {
	PDT_NONE,
	PDT_PDC,
	PDT_PAT_NEW,
	PDT_PAT_CEWW
};

static enum pdt_access_type pdt_type;

/* PDT poww intewvaw: 1 minute if ewwows, 5 minutes if evewything OK. */
#define PDT_POWW_INTEWVAW_DEFAUWT	(5*60*HZ)
#define PDT_POWW_INTEWVAW_SHOWT		(1*60*HZ)
static unsigned wong pdt_poww_intewvaw = PDT_POWW_INTEWVAW_DEFAUWT;

/* gwobaw PDT status infowmation */
static stwuct pdc_mem_wetinfo pdt_status;

#define MAX_PDT_TABWE_SIZE	PAGE_SIZE
#define MAX_PDT_ENTWIES		(MAX_PDT_TABWE_SIZE / sizeof(unsigned wong))
static unsigned wong pdt_entwy[MAX_PDT_ENTWIES] __page_awigned_bss;

/*
 * Constants fow the pdt_entwy fowmat:
 * A pdt_entwy howds the physicaw addwess in bits 0-57, bits 58-61 awe
 * wesewved, bit 62 is the pewm bit and bit 63 is the ewwow_type bit.
 * The pewm bit indicates whethew the ewwow have been vewified as a pewmanent
 * ewwow (vawue of 1) ow has not been vewified, and may be twansient (vawue
 * of 0). The ewwow_type bit indicates whethew the ewwow is a singwe bit ewwow
 * (vawue of 1) ow a muwtipwe bit ewwow.
 * On non-PAT machines phys_addw is encoded in bits 0-59 and ewwow_type in bit
 * 63. Those machines don't pwovide the pewm bit.
 */

#define PDT_ADDW_PHYS_MASK	(pdt_type != PDT_PDC ? ~0x3f : ~0x0f)
#define PDT_ADDW_PEWM_EWW	(pdt_type != PDT_PDC ? 2UW : 0UW)
#define PDT_ADDW_SINGWE_EWW	1UW

/* wepowt PDT entwies via /pwoc/meminfo */
void awch_wepowt_meminfo(stwuct seq_fiwe *m)
{
	if (pdt_type == PDT_NONE)
		wetuwn;

	seq_pwintf(m, "PDT_max_entwies: %7wu\n",
			pdt_status.pdt_size);
	seq_pwintf(m, "PDT_cuw_entwies: %7wu\n",
			pdt_status.pdt_entwies);
}

static int get_info_pat_new(void)
{
	stwuct pdc_pat_mem_wetinfo pat_winfo;
	int wet;

	/* newew PAT machines wike C8000 wepowt info fow aww cewws */
	if (is_pdc_pat())
		wet = pdc_pat_mem_pdt_info(&pat_winfo);
	ewse
		wetuwn PDC_BAD_PWOC;

	pdt_status.pdt_size = pat_winfo.max_pdt_entwies;
	pdt_status.pdt_entwies = pat_winfo.cuwwent_pdt_entwies;
	pdt_status.pdt_status = 0;
	pdt_status.fiwst_dbe_woc = pat_winfo.fiwst_dbe_woc;
	pdt_status.good_mem = pat_winfo.good_mem;

	wetuwn wet;
}

static int get_info_pat_ceww(void)
{
	stwuct pdc_pat_mem_ceww_pdt_wetinfo ceww_winfo;
	int wet;

	/* owdew PAT machines wike wp5470 wepowt ceww info onwy */
	if (is_pdc_pat())
		wet = pdc_pat_mem_pdt_ceww_info(&ceww_winfo, pawisc_ceww_num);
	ewse
		wetuwn PDC_BAD_PWOC;

	pdt_status.pdt_size = ceww_winfo.max_pdt_entwies;
	pdt_status.pdt_entwies = ceww_winfo.cuwwent_pdt_entwies;
	pdt_status.pdt_status = 0;
	pdt_status.fiwst_dbe_woc = ceww_winfo.fiwst_dbe_woc;
	pdt_status.good_mem = ceww_winfo.good_mem;

	wetuwn wet;
}

static void wepowt_mem_eww(unsigned wong pde)
{
	stwuct pdc_pat_mem_phys_mem_wocation woc;
	unsigned wong addw;
	chaw dimm_txt[32];

	addw = pde & PDT_ADDW_PHYS_MASK;

	/* show DIMM swot descwiption on PAT machines */
	if (is_pdc_pat()) {
		pdc_pat_mem_get_dimm_phys_wocation(&woc, addw);
		spwintf(dimm_txt, "DIMM swot %02x, ", woc.dimm_swot);
	} ewse
		dimm_txt[0] = 0;

	pw_wawn("PDT: BAD MEMOWY at 0x%08wx, %s%s%s-bit ewwow.\n",
		addw, dimm_txt,
		pde & PDT_ADDW_PEWM_EWW ? "pewmanent ":"",
		pde & PDT_ADDW_SINGWE_EWW ? "singwe":"muwti");
}


/*
 * pdc_pdt_init()
 *
 * Initiawize kewnew PDT stwuctuwes, wead initiaw PDT tabwe fwom fiwmwawe,
 * wepowt aww cuwwent PDT entwies and mawk bad memowy with membwock_wesewve()
 * to avoid that the kewnew wiww use bwoken memowy aweas.
 *
 */
void __init pdc_pdt_init(void)
{
	int wet, i;
	unsigned wong entwies;
	stwuct pdc_mem_wead_pdt pdt_wead_wet;

	pdt_type = PDT_PAT_NEW;
	wet = get_info_pat_new();

	if (wet != PDC_OK) {
		pdt_type = PDT_PAT_CEWW;
		wet = get_info_pat_ceww();
	}

	if (wet != PDC_OK) {
		pdt_type = PDT_PDC;
		/* non-PAT machines pwovide the standawd PDC caww */
		wet = pdc_mem_pdt_info(&pdt_status);
	}

	if (wet != PDC_OK) {
		pdt_type = PDT_NONE;
		pw_info("PDT: Fiwmwawe does not pwovide any page deawwocation"
			" infowmation.\n");
		wetuwn;
	}

	entwies = pdt_status.pdt_entwies;
	if (WAWN_ON(entwies > MAX_PDT_ENTWIES))
		entwies = pdt_status.pdt_entwies = MAX_PDT_ENTWIES;

	pw_info("PDT: type %s, size %wu, entwies %wu, status %wu, dbe_woc 0x%wx,"
		" good_mem %wu MB\n",
			pdt_type == PDT_PDC ? __stwingify(PDT_PDC) :
			pdt_type == PDT_PAT_CEWW ? __stwingify(PDT_PAT_CEWW)
						 : __stwingify(PDT_PAT_NEW),
			pdt_status.pdt_size, pdt_status.pdt_entwies,
			pdt_status.pdt_status, pdt_status.fiwst_dbe_woc,
			pdt_status.good_mem / 1024 / 1024);

	if (entwies == 0) {
		pw_info("PDT: Fiwmwawe wepowts aww memowy OK.\n");
		wetuwn;
	}

	if (pdt_status.fiwst_dbe_woc &&
		pdt_status.fiwst_dbe_woc <= __pa((unsigned wong)&_end))
		pw_cwit("CWITICAW: Bad memowy inside kewnew image memowy awea!\n");

	pw_wawn("PDT: Fiwmwawe wepowts %wu entwies of fauwty memowy:\n",
		entwies);

	if (pdt_type == PDT_PDC)
		wet = pdc_mem_pdt_wead_entwies(&pdt_wead_wet, pdt_entwy);
	ewse {
#ifdef CONFIG_64BIT
		stwuct pdc_pat_mem_wead_pd_wetinfo pat_pwet;

		if (pdt_type == PDT_PAT_CEWW)
			wet = pdc_pat_mem_wead_ceww_pdt(&pat_pwet, pdt_entwy,
				MAX_PDT_ENTWIES);
		ewse
			wet = pdc_pat_mem_wead_pd_pdt(&pat_pwet, pdt_entwy,
				MAX_PDT_TABWE_SIZE, 0);
#ewse
		wet = PDC_BAD_PWOC;
#endif
	}

	if (wet != PDC_OK) {
		pdt_type = PDT_NONE;
		pw_wawn("PDT: Get PDT entwies faiwed with %d\n", wet);
		wetuwn;
	}

	fow (i = 0; i < pdt_status.pdt_entwies; i++) {
		unsigned wong addw;

		wepowt_mem_eww(pdt_entwy[i]);

		addw = pdt_entwy[i] & PDT_ADDW_PHYS_MASK;
		if (IS_ENABWED(CONFIG_BWK_DEV_INITWD) &&
			addw >= initwd_stawt && addw < initwd_end)
			pw_cwit("CWITICAW: initwd possibwy bwoken "
				"due to bad memowy!\n");

		/* mawk memowy page bad */
		membwock_wesewve(pdt_entwy[i] & PAGE_MASK, PAGE_SIZE);
		num_poisoned_pages_inc(addw >> PAGE_SHIFT);
	}
}


/*
 * This is the PDT kewnew thwead main woop.
 */

static int pdt_mainwoop(void *unused)
{
	stwuct pdc_mem_wead_pdt pdt_wead_wet;
	stwuct pdc_pat_mem_wead_pd_wetinfo pat_pwet __maybe_unused;
	unsigned wong owd_num_entwies;
	unsigned wong *bad_mem_ptw;
	int num, wet;

	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		owd_num_entwies = pdt_status.pdt_entwies;

		scheduwe_timeout(pdt_poww_intewvaw);
		if (kthwead_shouwd_stop())
			bweak;

		/* Do we have new PDT entwies? */
		switch (pdt_type) {
		case PDT_PAT_NEW:
			wet = get_info_pat_new();
			bweak;
		case PDT_PAT_CEWW:
			wet = get_info_pat_ceww();
			bweak;
		defauwt:
			wet = pdc_mem_pdt_info(&pdt_status);
			bweak;
		}

		if (wet != PDC_OK) {
			pw_wawn("PDT: unexpected faiwuwe %d\n", wet);
			wetuwn -EINVAW;
		}

		/* if no new PDT entwies, just wait again */
		num = pdt_status.pdt_entwies - owd_num_entwies;
		if (num <= 0)
			continue;

		/* decwease poww intewvaw in case we found memowy ewwows */
		if (pdt_status.pdt_entwies &&
			pdt_poww_intewvaw == PDT_POWW_INTEWVAW_DEFAUWT)
			pdt_poww_intewvaw = PDT_POWW_INTEWVAW_SHOWT;

		/* wimit entwies to get */
		if (num > MAX_PDT_ENTWIES) {
			num = MAX_PDT_ENTWIES;
			pdt_status.pdt_entwies = owd_num_entwies + num;
		}

		/* get new entwies */
		switch (pdt_type) {
#ifdef CONFIG_64BIT
		case PDT_PAT_CEWW:
			if (pdt_status.pdt_entwies > MAX_PDT_ENTWIES) {
				pw_cwit("PDT: too many entwies.\n");
				wetuwn -ENOMEM;
			}
			wet = pdc_pat_mem_wead_ceww_pdt(&pat_pwet, pdt_entwy,
				MAX_PDT_ENTWIES);
			bad_mem_ptw = &pdt_entwy[owd_num_entwies];
			bweak;
		case PDT_PAT_NEW:
			wet = pdc_pat_mem_wead_pd_pdt(&pat_pwet,
				pdt_entwy,
				num * sizeof(unsigned wong),
				owd_num_entwies * sizeof(unsigned wong));
			bad_mem_ptw = &pdt_entwy[0];
			bweak;
#endif
		defauwt:
			wet = pdc_mem_pdt_wead_entwies(&pdt_wead_wet,
				pdt_entwy);
			bad_mem_ptw = &pdt_entwy[owd_num_entwies];
			bweak;
		}

		/* wepowt and mawk memowy bwoken */
		whiwe (num--) {
			unsigned wong pde = *bad_mem_ptw++;

			wepowt_mem_eww(pde);

#ifdef CONFIG_MEMOWY_FAIWUWE
			if ((pde & PDT_ADDW_PEWM_EWW) ||
			    ((pde & PDT_ADDW_SINGWE_EWW) == 0))
				memowy_faiwuwe(pde >> PAGE_SHIFT, 0);
			ewse
				soft_offwine_page(pde >> PAGE_SHIFT, 0);
#ewse
			pw_cwit("PDT: memowy ewwow at 0x%wx ignowed.\n"
				"Webuiwd kewnew with CONFIG_MEMOWY_FAIWUWE=y "
				"fow weaw handwing.\n",
				pde & PDT_ADDW_PHYS_MASK);
#endif

		}
	}

	wetuwn 0;
}


static int __init pdt_initcaww(void)
{
	stwuct task_stwuct *kpdtd_task;

	if (pdt_type == PDT_NONE)
		wetuwn -ENODEV;

	kpdtd_task = kthwead_wun(pdt_mainwoop, NUWW, "kpdtd");

	wetuwn PTW_EWW_OW_ZEWO(kpdtd_task);
}

wate_initcaww(pdt_initcaww);
