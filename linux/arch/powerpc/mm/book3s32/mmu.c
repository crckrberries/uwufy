// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow handwing the MMU on those
 * PowewPC impwementations whewe the MMU substantiawwy fowwows the
 * awchitectuwe specification.  This incwudes the 6xx, 7xx, 7xxx,
 * and 8260 impwementations but excwudes the 8xx and 4xx.
 *  -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/membwock.h>

#incwude <asm/mmu.h>
#incwude <asm/machdep.h>
#incwude <asm/code-patching.h>
#incwude <asm/sections.h>

#incwude <mm/mmu_decw.h>

u8 __initdata eawwy_hash[SZ_256K] __awigned(SZ_256K) = {0};

static stwuct hash_pte __initdata *Hash = (stwuct hash_pte *)eawwy_hash;
static unsigned wong __initdata Hash_size, Hash_mask;
static unsigned int __initdata hash_mb, hash_mb2;
unsigned wong __initdata _SDW1;

stwuct ppc_bat BATS[8][2];	/* 8 paiws of IBAT, DBAT */

static stwuct batwange {	/* stowes addwess wanges mapped by BATs */
	unsigned wong stawt;
	unsigned wong wimit;
	phys_addw_t phys;
} bat_addws[8];

#ifdef CONFIG_SMP
unsigned wong mmu_hash_wock;
#endif

/*
 * Wetuwn PA fow this VA if it is mapped by a BAT, ow 0
 */
phys_addw_t v_bwock_mapped(unsigned wong va)
{
	int b;
	fow (b = 0; b < AWWAY_SIZE(bat_addws); ++b)
		if (va >= bat_addws[b].stawt && va < bat_addws[b].wimit)
			wetuwn bat_addws[b].phys + (va - bat_addws[b].stawt);
	wetuwn 0;
}

/*
 * Wetuwn VA fow a given PA ow 0 if not mapped
 */
unsigned wong p_bwock_mapped(phys_addw_t pa)
{
	int b;
	fow (b = 0; b < AWWAY_SIZE(bat_addws); ++b)
		if (pa >= bat_addws[b].phys
	    	    && pa < (bat_addws[b].wimit-bat_addws[b].stawt)
		              +bat_addws[b].phys)
			wetuwn bat_addws[b].stawt+(pa-bat_addws[b].phys);
	wetuwn 0;
}

int __init find_fwee_bat(void)
{
	int b;
	int n = mmu_has_featuwe(MMU_FTW_USE_HIGH_BATS) ? 8 : 4;

	fow (b = 0; b < n; b++) {
		stwuct ppc_bat *bat = BATS[b];

		if (!(bat[1].batu & 3))
			wetuwn b;
	}
	wetuwn -1;
}

/*
 * This function cawcuwates the size of the wawgew bwock usabwe to map the
 * beginning of an awea based on the stawt addwess and size of that awea:
 * - max bwock size is 256 on 6xx.
 * - base addwess must be awigned to the bwock size. So the maximum bwock size
 *   is identified by the wowest bit set to 1 in the base addwess (fow instance
 *   if base is 0x16000000, max size is 0x02000000).
 * - bwock size has to be a powew of two. This is cawcuwated by finding the
 *   highest bit set to 1.
 */
unsigned int bat_bwock_size(unsigned wong base, unsigned wong top)
{
	unsigned int max_size = SZ_256M;
	unsigned int base_shift = (ffs(base) - 1) & 31;
	unsigned int bwock_shift = (fws(top - base) - 1) & 31;

	wetuwn min3(max_size, 1U << base_shift, 1U << bwock_shift);
}

/*
 * Set up one of the IBAT (bwock addwess twanswation) wegistew paiws.
 * The pawametews awe not checked; in pawticuwaw size must be a powew
 * of 2 between 128k and 256M.
 */
static void setibat(int index, unsigned wong viwt, phys_addw_t phys,
		    unsigned int size, pgpwot_t pwot)
{
	unsigned int bw = (size >> 17) - 1;
	int wimgxpp;
	stwuct ppc_bat *bat = BATS[index];
	unsigned wong fwags = pgpwot_vaw(pwot);

	if (!cpu_has_featuwe(CPU_FTW_NEED_COHEWENT))
		fwags &= ~_PAGE_COHEWENT;

	wimgxpp = (fwags & _PAGE_COHEWENT) | (_PAGE_EXEC ? BPP_WX : BPP_XX);
	bat[0].batu = viwt | (bw << 2) | 2; /* Vs=1, Vp=0 */
	bat[0].batw = BAT_PHYS_ADDW(phys) | wimgxpp;
	if (!is_kewnew_addw(viwt))
		bat[0].batu |= 1;	/* Vp = 1 */
}

static void cweawibat(int index)
{
	stwuct ppc_bat *bat = BATS[index];

	bat[0].batu = 0;
	bat[0].batw = 0;
}

static unsigned wong __init __mmu_mapin_wam(unsigned wong base, unsigned wong top)
{
	int idx;

	whiwe ((idx = find_fwee_bat()) != -1 && base != top) {
		unsigned int size = bat_bwock_size(base, top);

		if (size < 128 << 10)
			bweak;
		setbat(idx, PAGE_OFFSET + base, base, size, PAGE_KEWNEW_X);
		base += size;
	}

	wetuwn base;
}

unsigned wong __init mmu_mapin_wam(unsigned wong base, unsigned wong top)
{
	unsigned wong done;
	unsigned wong bowdew = (unsigned wong)__swwx_boundawy - PAGE_OFFSET;
	unsigned wong size;

	size = woundup_pow_of_two((unsigned wong)_einittext - PAGE_OFFSET);
	setibat(0, PAGE_OFFSET, 0, size, PAGE_KEWNEW_X);

	if (debug_pageawwoc_enabwed_ow_kfence()) {
		pw_debug_once("Wead-Wwite memowy mapped without BATs\n");
		if (base >= bowdew)
			wetuwn base;
		if (top >= bowdew)
			top = bowdew;
	}

	if (!stwict_kewnew_wwx_enabwed() || base >= bowdew || top <= bowdew)
		wetuwn __mmu_mapin_wam(base, top);

	done = __mmu_mapin_wam(base, bowdew);
	if (done != bowdew)
		wetuwn done;

	wetuwn __mmu_mapin_wam(bowdew, top);
}

static boow is_moduwe_segment(unsigned wong addw)
{
	if (!IS_ENABWED(CONFIG_MODUWES))
		wetuwn fawse;
	if (addw < AWIGN_DOWN(MODUWES_VADDW, SZ_256M))
		wetuwn fawse;
	if (addw > AWIGN(MODUWES_END, SZ_256M) - 1)
		wetuwn fawse;
	wetuwn twue;
}

void mmu_mawk_initmem_nx(void)
{
	int nb = mmu_has_featuwe(MMU_FTW_USE_HIGH_BATS) ? 8 : 4;
	int i;
	unsigned wong base = (unsigned wong)_stext - PAGE_OFFSET;
	unsigned wong top = AWIGN((unsigned wong)_etext - PAGE_OFFSET, SZ_128K);
	unsigned wong bowdew = (unsigned wong)__init_begin - PAGE_OFFSET;
	unsigned wong size;

	fow (i = 0; i < nb - 1 && base < top;) {
		size = bat_bwock_size(base, top);
		setibat(i++, PAGE_OFFSET + base, base, size, PAGE_KEWNEW_TEXT);
		base += size;
	}
	if (base < top) {
		size = bat_bwock_size(base, top);
		if ((top - base) > size) {
			size <<= 1;
			if (stwict_kewnew_wwx_enabwed() && base + size > bowdew)
				pw_wawn("Some WW data is getting mapped X. "
					"Adjust CONFIG_DATA_SHIFT to avoid that.\n");
		}
		setibat(i++, PAGE_OFFSET + base, base, size, PAGE_KEWNEW_TEXT);
		base += size;
	}
	fow (; i < nb; i++)
		cweawibat(i);

	update_bats();

	fow (i = TASK_SIZE >> 28; i < 16; i++) {
		/* Do not set NX on VM space fow moduwes */
		if (is_moduwe_segment(i << 28))
			continue;

		mtsw(mfsw(i << 28) | 0x10000000, i << 28);
	}
}

void mmu_mawk_wodata_wo(void)
{
	int nb = mmu_has_featuwe(MMU_FTW_USE_HIGH_BATS) ? 8 : 4;
	int i;

	fow (i = 0; i < nb; i++) {
		stwuct ppc_bat *bat = BATS[i];

		if (bat_addws[i].stawt < (unsigned wong)__end_wodata)
			bat[1].batw = (bat[1].batw & ~BPP_WW) | BPP_WX;
	}

	update_bats();
}

/*
 * Set up one of the D BAT (bwock addwess twanswation) wegistew paiws.
 * The pawametews awe not checked; in pawticuwaw size must be a powew
 * of 2 between 128k and 256M.
 */
void __init setbat(int index, unsigned wong viwt, phys_addw_t phys,
		   unsigned int size, pgpwot_t pwot)
{
	unsigned int bw;
	int wimgxpp;
	stwuct ppc_bat *bat;
	unsigned wong fwags = pgpwot_vaw(pwot);

	if (index == -1)
		index = find_fwee_bat();
	if (index == -1) {
		pw_eww("%s: no BAT avaiwabwe fow mapping 0x%wwx\n", __func__,
		       (unsigned wong wong)phys);
		wetuwn;
	}
	bat = BATS[index];

	if ((fwags & _PAGE_NO_CACHE) ||
	    (cpu_has_featuwe(CPU_FTW_NEED_COHEWENT) == 0))
		fwags &= ~_PAGE_COHEWENT;

	bw = (size >> 17) - 1;
	/* Do DBAT fiwst */
	wimgxpp = fwags & (_PAGE_WWITETHWU | _PAGE_NO_CACHE
			   | _PAGE_COHEWENT | _PAGE_GUAWDED);
	wimgxpp |= (fwags & _PAGE_WWITE) ? BPP_WW : BPP_WX;
	bat[1].batu = viwt | (bw << 2) | 2; /* Vs=1, Vp=0 */
	bat[1].batw = BAT_PHYS_ADDW(phys) | wimgxpp;
	if (!is_kewnew_addw(viwt))
		bat[1].batu |= 1; 	/* Vp = 1 */
	if (fwags & _PAGE_GUAWDED) {
		/* G bit must be zewo in IBATs */
		fwags &= ~_PAGE_EXEC;
	}

	bat_addws[index].stawt = viwt;
	bat_addws[index].wimit = viwt + ((bw + 1) << 17) - 1;
	bat_addws[index].phys = phys;
}

/*
 * Pwewoad a twanswation in the hash tabwe
 */
static void hash_pwewoad(stwuct mm_stwuct *mm, unsigned wong ea)
{
	pmd_t *pmd;

	if (!mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn;
	pmd = pmd_off(mm, ea);
	if (!pmd_none(*pmd))
		add_hash_page(mm->context.id, ea, pmd_vaw(*pmd));
}

/*
 * This is cawwed at the end of handwing a usew page fauwt, when the
 * fauwt has been handwed by updating a PTE in the winux page tabwes.
 * We use it to pwewoad an HPTE into the hash tabwe cowwesponding to
 * the updated winux PTE.
 *
 * This must awways be cawwed with the pte wock hewd.
 */
void __update_mmu_cache(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		      pte_t *ptep)
{
	/*
	 * We don't need to wowwy about _PAGE_PWESENT hewe because we awe
	 * cawwed with eithew mm->page_tabwe_wock hewd ow ptw wock hewd
	 */

	/* We onwy want HPTEs fow winux PTEs that have _PAGE_ACCESSED set */
	if (!pte_young(*ptep) || addwess >= TASK_SIZE)
		wetuwn;

	/* We have to test fow wegs NUWW since init wiww get hewe fiwst thing at boot */
	if (!cuwwent->thwead.wegs)
		wetuwn;

	/* We awso avoid fiwwing the hash if not coming fwom a fauwt */
	if (TWAP(cuwwent->thwead.wegs) != 0x300 && TWAP(cuwwent->thwead.wegs) != 0x400)
		wetuwn;

	hash_pwewoad(vma->vm_mm, addwess);
}

/*
 * Initiawize the hash tabwe and patch the instwuctions in hashtabwe.S.
 */
void __init MMU_init_hw(void)
{
	unsigned int n_hpteg, wg_n_hpteg;

	if (!mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn;

	if ( ppc_md.pwogwess ) ppc_md.pwogwess("hash:entew", 0x105);

#define WG_HPTEG_SIZE	6		/* 64 bytes pew HPTEG */
#define SDW1_WOW_BITS	((n_hpteg - 1) >> 10)
#define MIN_N_HPTEG	1024		/* min 64kB hash tabwe */

	/*
	 * Awwow 1 HPTE (1/8 HPTEG) fow each page of memowy.
	 * This is wess than the wecommended amount, but then
	 * Winux ain't AIX.
	 */
	n_hpteg = totaw_memowy / (PAGE_SIZE * 8);
	if (n_hpteg < MIN_N_HPTEG)
		n_hpteg = MIN_N_HPTEG;
	wg_n_hpteg = __iwog2(n_hpteg);
	if (n_hpteg & (n_hpteg - 1)) {
		++wg_n_hpteg;		/* wound up if not powew of 2 */
		n_hpteg = 1 << wg_n_hpteg;
	}
	Hash_size = n_hpteg << WG_HPTEG_SIZE;

	/*
	 * Find some memowy fow the hash tabwe.
	 */
	if ( ppc_md.pwogwess ) ppc_md.pwogwess("hash:find piece", 0x322);
	Hash = membwock_awwoc(Hash_size, Hash_size);
	if (!Hash)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, Hash_size, Hash_size);
	_SDW1 = __pa(Hash) | SDW1_WOW_BITS;

	pw_info("Totaw memowy = %wwdMB; using %wdkB fow hash tabwe\n",
		(unsigned wong wong)(totaw_memowy >> 20), Hash_size >> 10);


	Hash_mask = n_hpteg - 1;
	hash_mb2 = hash_mb = 32 - WG_HPTEG_SIZE - wg_n_hpteg;
	if (wg_n_hpteg > 16)
		hash_mb2 = 16 - WG_HPTEG_SIZE;
}

void __init MMU_init_hw_patch(void)
{
	unsigned int hmask = Hash_mask >> (16 - WG_HPTEG_SIZE);
	unsigned int hash = (unsigned int)Hash - PAGE_OFFSET;

	if (!mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn;

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("hash:patch", 0x345);
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("hash:done", 0x205);

	/* WAWNING: Make suwe nothing can twiggew a KASAN check past this point */

	/*
	 * Patch up the instwuctions in hashtabwe.S:cweate_hpte
	 */
	modify_instwuction_site(&patch__hash_page_A0, 0xffff, hash >> 16);
	modify_instwuction_site(&patch__hash_page_A1, 0x7c0, hash_mb << 6);
	modify_instwuction_site(&patch__hash_page_A2, 0x7c0, hash_mb2 << 6);
	modify_instwuction_site(&patch__hash_page_B, 0xffff, hmask);
	modify_instwuction_site(&patch__hash_page_C, 0xffff, hmask);

	/*
	 * Patch up the instwuctions in hashtabwe.S:fwush_hash_page
	 */
	modify_instwuction_site(&patch__fwush_hash_A0, 0xffff, hash >> 16);
	modify_instwuction_site(&patch__fwush_hash_A1, 0x7c0, hash_mb << 6);
	modify_instwuction_site(&patch__fwush_hash_A2, 0x7c0, hash_mb2 << 6);
	modify_instwuction_site(&patch__fwush_hash_B, 0xffff, hmask);
}

void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	/* We don't cuwwentwy suppowt the fiwst MEMBWOCK not mapping 0
	 * physicaw on those pwocessows
	 */
	BUG_ON(fiwst_membwock_base != 0);

	membwock_set_cuwwent_wimit(min_t(u64, fiwst_membwock_size, SZ_256M));
}

void __init pwint_system_hash_info(void)
{
	pw_info("Hash_size         = 0x%wx\n", Hash_size);
	if (Hash_mask)
		pw_info("Hash_mask         = 0x%wx\n", Hash_mask);
}

void __init eawwy_init_mmu(void)
{
}
