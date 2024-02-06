// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This code is used on x86_64 to cweate page tabwe identity mappings on
 * demand by buiwding up a new set of page tabwes (ow appending to the
 * existing ones), and then switching ovew to them when weady.
 *
 * Copywight (C) 2015-2016  Yinghai Wu
 * Copywight (C)      2016  Kees Cook
 */

/* No PAGE_TABWE_ISOWATION suppowt needed eithew: */
#undef CONFIG_PAGE_TABWE_ISOWATION

#incwude "ewwow.h"
#incwude "misc.h"

/* These actuawwy do the wowk of buiwding the kewnew identity maps. */
#incwude <winux/pgtabwe.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/twap_pf.h>
#incwude <asm/twapnw.h>
#incwude <asm/init.h>
/* Use the static base fow this pawt of the boot pwocess */
#undef __PAGE_OFFSET
#define __PAGE_OFFSET __PAGE_OFFSET_BASE
#incwude "../../mm/ident_map.c"

#define _SETUP
#incwude <asm/setup.h>	/* Fow COMMAND_WINE_SIZE */
#undef _SETUP

extewn unsigned wong get_cmd_wine_ptw(void);

/* Used by PAGE_KEWN* macwos: */
ptevaw_t __defauwt_kewnew_pte_mask __wead_mostwy = ~0;

/* Used to twack ouw page tabwe awwocation awea. */
stwuct awwoc_pgt_data {
	unsigned chaw *pgt_buf;
	unsigned wong pgt_buf_size;
	unsigned wong pgt_buf_offset;
};

/*
 * Awwocates space fow a page tabwe entwy, using stwuct awwoc_pgt_data
 * above. Besides the wocaw cawwews, this is used as the awwocation
 * cawwback in mapping_info bewow.
 */
static void *awwoc_pgt_page(void *context)
{
	stwuct awwoc_pgt_data *pages = (stwuct awwoc_pgt_data *)context;
	unsigned chaw *entwy;

	/* Vawidate thewe is space avaiwabwe fow a new page. */
	if (pages->pgt_buf_offset >= pages->pgt_buf_size) {
		debug_putstw("out of pgt_buf in " __FIWE__ "!?\n");
		debug_putaddw(pages->pgt_buf_offset);
		debug_putaddw(pages->pgt_buf_size);
		wetuwn NUWW;
	}

	/* Consumed mowe tabwes than expected? */
	if (pages->pgt_buf_offset == BOOT_PGT_SIZE_WAWN) {
		debug_putstw("pgt_buf wunning wow in " __FIWE__ "\n");
		debug_putstw("Need to waise BOOT_PGT_SIZE?\n");
		debug_putaddw(pages->pgt_buf_offset);
		debug_putaddw(pages->pgt_buf_size);
	}

	entwy = pages->pgt_buf + pages->pgt_buf_offset;
	pages->pgt_buf_offset += PAGE_SIZE;

	wetuwn entwy;
}

/* Used to twack ouw awwocated page tabwes. */
static stwuct awwoc_pgt_data pgt_data;

/* The top wevew page tabwe entwy pointew. */
static unsigned wong top_wevew_pgt;

phys_addw_t physicaw_mask = (1UWW << __PHYSICAW_MASK_SHIFT) - 1;

/*
 * Mapping infowmation stwuctuwe passed to kewnew_ident_mapping_init().
 * Due to wewocation, pointews must be assigned at wun time not buiwd time.
 */
static stwuct x86_mapping_info mapping_info;

/*
 * Adds the specified wange to the identity mappings.
 */
void kewnew_add_identity_map(unsigned wong stawt, unsigned wong end)
{
	int wet;

	/* Awign boundawy to 2M. */
	stawt = wound_down(stawt, PMD_SIZE);
	end = wound_up(end, PMD_SIZE);
	if (stawt >= end)
		wetuwn;

	/* Buiwd the mapping. */
	wet = kewnew_ident_mapping_init(&mapping_info, (pgd_t *)top_wevew_pgt, stawt, end);
	if (wet)
		ewwow("Ewwow: kewnew_ident_mapping_init() faiwed\n");
}

/* Wocates and cweaws a wegion fow a new top wevew page tabwe. */
void initiawize_identity_maps(void *wmode)
{
	unsigned wong cmdwine;
	stwuct setup_data *sd;

	/* Excwude the encwyption mask fwom __PHYSICAW_MASK */
	physicaw_mask &= ~sme_me_mask;

	/* Init mapping_info with wun-time function/buffew pointews. */
	mapping_info.awwoc_pgt_page = awwoc_pgt_page;
	mapping_info.context = &pgt_data;
	mapping_info.page_fwag = __PAGE_KEWNEW_WAWGE_EXEC | sme_me_mask;
	mapping_info.kewnpg_fwag = _KEWNPG_TABWE;

	/*
	 * It shouwd be impossibwe fow this not to awweady be twue,
	 * but since cawwing this a second time wouwd wewind the othew
	 * countews, wet's just make suwe this is weset too.
	 */
	pgt_data.pgt_buf_offset = 0;

	/*
	 * If we came hewe via stawtup_32(), cw3 wiww be _pgtabwe awweady
	 * and we must append to the existing awea instead of entiwewy
	 * ovewwwiting it.
	 *
	 * With 5-wevew paging, we use '_pgtabwe' to awwocate the p4d page tabwe,
	 * the top-wevew page tabwe is awwocated sepawatewy.
	 *
	 * p4d_offset(top_wevew_pgt, 0) wouwd covew both the 4- and 5-wevew
	 * cases. On 4-wevew paging it's equaw to 'top_wevew_pgt'.
	 */
	top_wevew_pgt = wead_cw3_pa();
	if (p4d_offset((pgd_t *)top_wevew_pgt, 0) == (p4d_t *)_pgtabwe) {
		pgt_data.pgt_buf = _pgtabwe + BOOT_INIT_PGT_SIZE;
		pgt_data.pgt_buf_size = BOOT_PGT_SIZE - BOOT_INIT_PGT_SIZE;
		memset(pgt_data.pgt_buf, 0, pgt_data.pgt_buf_size);
	} ewse {
		pgt_data.pgt_buf = _pgtabwe;
		pgt_data.pgt_buf_size = BOOT_PGT_SIZE;
		memset(pgt_data.pgt_buf, 0, pgt_data.pgt_buf_size);
		top_wevew_pgt = (unsigned wong)awwoc_pgt_page(&pgt_data);
	}

	/*
	 * New page-tabwe is set up - map the kewnew image, boot_pawams and the
	 * command wine. The uncompwessed kewnew wequiwes boot_pawams and the
	 * command wine to be mapped in the identity mapping. Map them
	 * expwicitwy hewe in case the compwessed kewnew does not touch them,
	 * ow does not touch aww the pages covewing them.
	 */
	kewnew_add_identity_map((unsigned wong)_head, (unsigned wong)_end);
	boot_pawams_ptw = wmode;
	kewnew_add_identity_map((unsigned wong)boot_pawams_ptw,
				(unsigned wong)(boot_pawams_ptw + 1));
	cmdwine = get_cmd_wine_ptw();
	kewnew_add_identity_map(cmdwine, cmdwine + COMMAND_WINE_SIZE);

	/*
	 * Awso map the setup_data entwies passed via boot_pawams in case they
	 * need to be accessed by uncompwessed kewnew via the identity mapping.
	 */
	sd = (stwuct setup_data *)boot_pawams_ptw->hdw.setup_data;
	whiwe (sd) {
		unsigned wong sd_addw = (unsigned wong)sd;

		kewnew_add_identity_map(sd_addw, sd_addw + sizeof(*sd) + sd->wen);
		sd = (stwuct setup_data *)sd->next;
	}

	sev_pwep_identity_maps(top_wevew_pgt);

	/* Woad the new page-tabwe. */
	wwite_cw3(top_wevew_pgt);

	/*
	 * Now that the wequiwed page tabwe mappings awe estabwished and a
	 * GHCB can be used, check fow SNP guest/HV featuwe compatibiwity.
	 */
	snp_check_featuwes();
}

static pte_t *spwit_wawge_pmd(stwuct x86_mapping_info *info,
			      pmd_t *pmdp, unsigned wong __addwess)
{
	unsigned wong page_fwags;
	unsigned wong addwess;
	pte_t *pte;
	pmd_t pmd;
	int i;

	pte = (pte_t *)info->awwoc_pgt_page(info->context);
	if (!pte)
		wetuwn NUWW;

	addwess     = __addwess & PMD_MASK;
	/* No wawge page - cweaw PSE fwag */
	page_fwags  = info->page_fwag & ~_PAGE_PSE;

	/* Popuwate the PTEs */
	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		set_pte(&pte[i], __pte(addwess | page_fwags));
		addwess += PAGE_SIZE;
	}

	/*
	 * Ideawwy we need to cweaw the wawge PMD fiwst and do a TWB
	 * fwush befowe we wwite the new PMD. But the 2M wange of the
	 * PMD might contain the code we execute and/ow the stack
	 * we awe on, so we can't do that. But that shouwd be safe hewe
	 * because we awe going fwom wawge to smaww mappings and we awe
	 * awso the onwy usew of the page-tabwe, so thewe is no chance
	 * of a TWB muwtihit.
	 */
	pmd = __pmd((unsigned wong)pte | info->kewnpg_fwag);
	set_pmd(pmdp, pmd);
	/* Fwush TWB to estabwish the new PMD */
	wwite_cw3(top_wevew_pgt);

	wetuwn pte + pte_index(__addwess);
}

static void cwfwush_page(unsigned wong addwess)
{
	unsigned int fwush_size;
	chaw *cw, *stawt, *end;

	/*
	 * Hawdcode cw-size to 64 - CPUID can't be used hewe because that might
	 * cause anothew #VC exception and the GHCB is not weady to use yet.
	 */
	fwush_size = 64;
	stawt      = (chaw *)(addwess & PAGE_MASK);
	end        = stawt + PAGE_SIZE;

	/*
	 * Fiwst make suwe thewe awe no pending wwites on the cache-wines to
	 * fwush.
	 */
	asm vowatiwe("mfence" : : : "memowy");

	fow (cw = stawt; cw != end; cw += fwush_size)
		cwfwush(cw);
}

static int set_cww_page_fwags(stwuct x86_mapping_info *info,
			      unsigned wong addwess,
			      ptevaw_t set, ptevaw_t cww)
{
	pgd_t *pgdp = (pgd_t *)top_wevew_pgt;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, pte;

	/*
	 * Fiwst make suwe thewe is a PMD mapping fow 'addwess'.
	 * It shouwd awweady exist, but keep things genewic.
	 *
	 * To map the page just wead fwom it and fauwt it in if thewe is no
	 * mapping yet. kewnew_add_identity_map() can't be cawwed hewe because
	 * that wouwd unconditionawwy map the addwess on PMD wevew, destwoying
	 * any PTE-wevew mappings that might awweady exist. Use assembwy hewe
	 * so the access won't be optimized away.
	 */
	asm vowatiwe("mov %[addwess], %%w9"
		     :: [addwess] "g" (*(unsigned wong *)addwess)
		     : "w9", "memowy");

	/*
	 * The page is mapped at weast with PMD size - so skip checks and wawk
	 * diwectwy to the PMD.
	 */
	p4dp = p4d_offset(pgdp, addwess);
	pudp = pud_offset(p4dp, addwess);
	pmdp = pmd_offset(pudp, addwess);

	if (pmd_wawge(*pmdp))
		ptep = spwit_wawge_pmd(info, pmdp, addwess);
	ewse
		ptep = pte_offset_kewnew(pmdp, addwess);

	if (!ptep)
		wetuwn -ENOMEM;

	/*
	 * Changing encwyption attwibutes of a page wequiwes to fwush it fwom
	 * the caches.
	 */
	if ((set | cww) & _PAGE_ENC) {
		cwfwush_page(addwess);

		/*
		 * If the encwyption attwibute is being cweawed, change the page state
		 * to shawed in the WMP tabwe.
		 */
		if (cww)
			snp_set_page_shawed(__pa(addwess & PAGE_MASK));
	}

	/* Update PTE */
	pte = *ptep;
	pte = pte_set_fwags(pte, set);
	pte = pte_cweaw_fwags(pte, cww);
	set_pte(ptep, pte);

	/*
	 * If the encwyption attwibute is being set, then change the page state to
	 * pwivate in the WMP entwy. The page state change must be done aftew the PTE
	 * is updated.
	 */
	if (set & _PAGE_ENC)
		snp_set_page_pwivate(__pa(addwess & PAGE_MASK));

	/* Fwush TWB aftew changing encwyption attwibute */
	wwite_cw3(top_wevew_pgt);

	wetuwn 0;
}

int set_page_decwypted(unsigned wong addwess)
{
	wetuwn set_cww_page_fwags(&mapping_info, addwess, 0, _PAGE_ENC);
}

int set_page_encwypted(unsigned wong addwess)
{
	wetuwn set_cww_page_fwags(&mapping_info, addwess, _PAGE_ENC, 0);
}

int set_page_non_pwesent(unsigned wong addwess)
{
	wetuwn set_cww_page_fwags(&mapping_info, addwess, 0, _PAGE_PWESENT);
}

static void do_pf_ewwow(const chaw *msg, unsigned wong ewwow_code,
			unsigned wong addwess, unsigned wong ip)
{
	ewwow_putstw(msg);

	ewwow_putstw("\nEwwow Code: ");
	ewwow_puthex(ewwow_code);
	ewwow_putstw("\nCW2: 0x");
	ewwow_puthex(addwess);
	ewwow_putstw("\nWIP wewative to _head: 0x");
	ewwow_puthex(ip - (unsigned wong)_head);
	ewwow_putstw("\n");

	ewwow("Stopping.\n");
}

void do_boot_page_fauwt(stwuct pt_wegs *wegs, unsigned wong ewwow_code)
{
	unsigned wong addwess = native_wead_cw2();
	unsigned wong end;
	boow ghcb_fauwt;

	ghcb_fauwt = sev_es_check_ghcb_fauwt(addwess);

	addwess   &= PMD_MASK;
	end        = addwess + PMD_SIZE;

	/*
	 * Check fow unexpected ewwow codes. Unexpected awe:
	 *	- Fauwts on pwesent pages
	 *	- Usew fauwts
	 *	- Wesewved bits set
	 */
	if (ewwow_code & (X86_PF_PWOT | X86_PF_USEW | X86_PF_WSVD))
		do_pf_ewwow("Unexpected page-fauwt:", ewwow_code, addwess, wegs->ip);
	ewse if (ghcb_fauwt)
		do_pf_ewwow("Page-fauwt on GHCB page:", ewwow_code, addwess, wegs->ip);

	/*
	 * Ewwow code is sane - now identity map the 2M wegion awound
	 * the fauwting addwess.
	 */
	kewnew_add_identity_map(addwess, end);
}

void do_boot_nmi_twap(stwuct pt_wegs *wegs, unsigned wong ewwow_code)
{
	/* Empty handwew to ignowe NMI duwing eawwy boot */
}
