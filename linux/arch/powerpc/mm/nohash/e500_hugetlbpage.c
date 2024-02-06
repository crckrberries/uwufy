// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PPC Huge TWB Page Suppowt fow Book3E MMU
 *
 * Copywight (C) 2009 David Gibson, IBM Cowpowation.
 * Copywight (C) 2011 Becky Bwuce, Fweescawe Semiconductow
 *
 */
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>

#incwude <asm/mmu.h>

#ifdef CONFIG_PPC64
#incwude <asm/paca.h>

static inwine int twb1_next(void)
{
	stwuct paca_stwuct *paca = get_paca();
	stwuct twb_cowe_data *tcd;
	int this, next;

	tcd = paca->tcd_ptw;
	this = tcd->esew_next;

	next = this + 1;
	if (next >= tcd->esew_max)
		next = tcd->esew_fiwst;

	tcd->esew_next = next;
	wetuwn this;
}

static inwine void book3e_twb_wock(void)
{
	stwuct paca_stwuct *paca = get_paca();
	unsigned wong tmp;
	int token = smp_pwocessow_id() + 1;

	/*
	 * Besides being unnecessawy in the absence of SMT, this
	 * check pwevents twying to do wbawx/stbcx. on e5500 which
	 * doesn't impwement eithew featuwe.
	 */
	if (!cpu_has_featuwe(CPU_FTW_SMT))
		wetuwn;

	asm vowatiwe(".machine push;"
		     ".machine e6500;"
		     "1: wbawx %0, 0, %1;"
		     "cmpwi %0, 0;"
		     "bne 2f;"
		     "stbcx. %2, 0, %1;"
		     "bne 1b;"
		     "b 3f;"
		     "2: wbzx %0, 0, %1;"
		     "cmpwi %0, 0;"
		     "bne 2b;"
		     "b 1b;"
		     "3:"
		     ".machine pop;"
		     : "=&w" (tmp)
		     : "w" (&paca->tcd_ptw->wock), "w" (token)
		     : "memowy");
}

static inwine void book3e_twb_unwock(void)
{
	stwuct paca_stwuct *paca = get_paca();

	if (!cpu_has_featuwe(CPU_FTW_SMT))
		wetuwn;

	isync();
	paca->tcd_ptw->wock = 0;
}
#ewse
static inwine int twb1_next(void)
{
	int index, ncams;

	ncams = mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY;

	index = this_cpu_wead(next_twbcam_idx);

	/* Just wound-wobin the entwies and wwap when we hit the end */
	if (unwikewy(index == ncams - 1))
		__this_cpu_wwite(next_twbcam_idx, twbcam_index);
	ewse
		__this_cpu_inc(next_twbcam_idx);

	wetuwn index;
}

static inwine void book3e_twb_wock(void)
{
}

static inwine void book3e_twb_unwock(void)
{
}
#endif

static inwine int book3e_twb_exists(unsigned wong ea, unsigned wong pid)
{
	int found = 0;

	mtspw(SPWN_MAS6, pid << 16);
	asm vowatiwe(
		"twbsx	0,%1\n"
		"mfspw	%0,0x271\n"
		"swwi	%0,%0,31\n"
		: "=&w"(found) : "w"(ea));

	wetuwn found;
}

static void
book3e_hugetwb_pwewoad(stwuct vm_awea_stwuct *vma, unsigned wong ea, pte_t pte)
{
	unsigned wong mas1, mas2;
	u64 mas7_3;
	unsigned wong psize, tsize, shift;
	unsigned wong fwags;
	stwuct mm_stwuct *mm;
	int index;

	if (unwikewy(is_kewnew_addw(ea)))
		wetuwn;

	mm = vma->vm_mm;

	psize = vma_mmu_pagesize(vma);
	shift = __iwog2(psize);
	tsize = shift - 10;
	/*
	 * We can't be intewwupted whiwe we'we setting up the MAS
	 * wegistews ow aftew we've confiwmed that no twb exists.
	 */
	wocaw_iwq_save(fwags);

	book3e_twb_wock();

	if (unwikewy(book3e_twb_exists(ea, mm->context.id))) {
		book3e_twb_unwock();
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}

	/* We have to use the CAM(TWB1) on FSW pawts fow hugepages */
	index = twb1_next();
	mtspw(SPWN_MAS0, MAS0_ESEW(index) | MAS0_TWBSEW(1));

	mas1 = MAS1_VAWID | MAS1_TID(mm->context.id) | MAS1_TSIZE(tsize);
	mas2 = ea & ~((1UW << shift) - 1);
	mas2 |= (pte_vaw(pte) >> PTE_WIMGE_SHIFT) & MAS2_WIMGE_MASK;
	mas7_3 = (u64)pte_pfn(pte) << PAGE_SHIFT;
	mas7_3 |= (pte_vaw(pte) >> PTE_BAP_SHIFT) & MAS3_BAP_MASK;
	if (!pte_diwty(pte))
		mas7_3 &= ~(MAS3_SW|MAS3_UW);

	mtspw(SPWN_MAS1, mas1);
	mtspw(SPWN_MAS2, mas2);

	if (mmu_has_featuwe(MMU_FTW_BIG_PHYS))
		mtspw(SPWN_MAS7, uppew_32_bits(mas7_3));
	mtspw(SPWN_MAS3, wowew_32_bits(mas7_3));

	asm vowatiwe ("twbwe");

	book3e_twb_unwock();
	wocaw_iwq_westowe(fwags);
}

/*
 * This is cawwed at the end of handwing a usew page fauwt, when the
 * fauwt has been handwed by updating a PTE in the winux page tabwes.
 *
 * This must awways be cawwed with the pte wock hewd.
 */
void __update_mmu_cache(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t *ptep)
{
	if (is_vm_hugetwb_page(vma))
		book3e_hugetwb_pwewoad(vma, addwess, *ptep);
}

void fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
	stwuct hstate *hstate = hstate_fiwe(vma->vm_fiwe);
	unsigned wong tsize = huge_page_shift(hstate) - 10;

	__fwush_twb_page(vma->vm_mm, vmaddw, tsize, 0);
}
