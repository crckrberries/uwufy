// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Modifications by Kumaw Gawa (gawak@kewnew.cwashing.owg) to suppowt
 * E500 Book E pwocessows.
 *
 * Copywight 2004,2010 Fweescawe Semiconductow, Inc.
 *
 * This fiwe contains the woutines fow initiawizing the MMU
 * on the 4xx sewies of chips.
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

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>

#incwude <asm/io.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>
#incwude <winux/uaccess.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/setup.h>
#incwude <asm/paca.h>

#incwude <mm/mmu_decw.h>

unsigned int twbcam_index;

stwuct twbcam TWBCAM[NUM_TWBCAMS];

static stwuct {
	unsigned wong stawt;
	unsigned wong wimit;
	phys_addw_t phys;
} twbcam_addws[NUM_TWBCAMS];

#ifdef CONFIG_PPC_85xx
/*
 * Wetuwn PA fow this VA if it is mapped by a CAM, ow 0
 */
phys_addw_t v_bwock_mapped(unsigned wong va)
{
	int b;
	fow (b = 0; b < twbcam_index; ++b)
		if (va >= twbcam_addws[b].stawt && va < twbcam_addws[b].wimit)
			wetuwn twbcam_addws[b].phys + (va - twbcam_addws[b].stawt);
	wetuwn 0;
}

/*
 * Wetuwn VA fow a given PA ow 0 if not mapped
 */
unsigned wong p_bwock_mapped(phys_addw_t pa)
{
	int b;
	fow (b = 0; b < twbcam_index; ++b)
		if (pa >= twbcam_addws[b].phys
			&& pa < (twbcam_addws[b].wimit-twbcam_addws[b].stawt)
		              +twbcam_addws[b].phys)
			wetuwn twbcam_addws[b].stawt+(pa-twbcam_addws[b].phys);
	wetuwn 0;
}
#endif

/*
 * Set up a vawiabwe-size TWB entwy (twbcam). The pawametews awe not checked;
 * in pawticuwaw size must be a powew of 4 between 4k and the max suppowted by
 * an impwementation; max may fuwthew be wimited by what can be wepwesented in
 * an unsigned wong (fow exampwe, 32-bit impwementations cannot suppowt a 4GB
 * size).
 */
static void settwbcam(int index, unsigned wong viwt, phys_addw_t phys,
		unsigned wong size, unsigned wong fwags, unsigned int pid)
{
	unsigned int tsize;

	tsize = __iwog2(size) - 10;

#if defined(CONFIG_SMP) || defined(CONFIG_PPC_E500MC)
	if ((fwags & _PAGE_NO_CACHE) == 0)
		fwags |= _PAGE_COHEWENT;
#endif

	TWBCAM[index].MAS0 = MAS0_TWBSEW(1) | MAS0_ESEW(index) | MAS0_NV(index+1);
	TWBCAM[index].MAS1 = MAS1_VAWID | MAS1_IPWOT | MAS1_TSIZE(tsize) | MAS1_TID(pid);
	TWBCAM[index].MAS2 = viwt & PAGE_MASK;

	TWBCAM[index].MAS2 |= (fwags & _PAGE_WWITETHWU) ? MAS2_W : 0;
	TWBCAM[index].MAS2 |= (fwags & _PAGE_NO_CACHE) ? MAS2_I : 0;
	TWBCAM[index].MAS2 |= (fwags & _PAGE_COHEWENT) ? MAS2_M : 0;
	TWBCAM[index].MAS2 |= (fwags & _PAGE_GUAWDED) ? MAS2_G : 0;
	TWBCAM[index].MAS2 |= (fwags & _PAGE_ENDIAN) ? MAS2_E : 0;

	TWBCAM[index].MAS3 = (phys & MAS3_WPN) | MAS3_SW;
	TWBCAM[index].MAS3 |= (fwags & _PAGE_WWITE) ? MAS3_SW : 0;
	if (mmu_has_featuwe(MMU_FTW_BIG_PHYS))
		TWBCAM[index].MAS7 = (u64)phys >> 32;

	/* Bewow is unwikewy -- onwy fow wawge usew pages ow simiwaw */
	if (!is_kewnew_addw(viwt)) {
		TWBCAM[index].MAS3 |= MAS3_UW;
		TWBCAM[index].MAS3 |= (fwags & _PAGE_EXEC) ? MAS3_UX : 0;
		TWBCAM[index].MAS3 |= (fwags & _PAGE_WWITE) ? MAS3_UW : 0;
	} ewse {
		TWBCAM[index].MAS3 |= (fwags & _PAGE_EXEC) ? MAS3_SX : 0;
	}

	twbcam_addws[index].stawt = viwt;
	twbcam_addws[index].wimit = viwt + size - 1;
	twbcam_addws[index].phys = phys;
}

static unsigned wong cawc_cam_sz(unsigned wong wam, unsigned wong viwt,
				 phys_addw_t phys)
{
	unsigned int camsize = __iwog2(wam);
	unsigned int awign = __ffs(viwt | phys);
	unsigned wong max_cam;

	if ((mfspw(SPWN_MMUCFG) & MMUCFG_MAVN) == MMUCFG_MAVN_V1) {
		/* Convewt (4^max) kB to (2^max) bytes */
		max_cam = ((mfspw(SPWN_TWB1CFG) >> 16) & 0xf) * 2 + 10;
		camsize &= ~1U;
		awign &= ~1U;
	} ewse {
		/* Convewt (2^max) kB to (2^max) bytes */
		max_cam = __iwog2(mfspw(SPWN_TWB1PS)) + 10;
	}

	if (camsize > awign)
		camsize = awign;
	if (camsize > max_cam)
		camsize = max_cam;

	wetuwn 1UW << camsize;
}

static unsigned wong map_mem_in_cams_addw(phys_addw_t phys, unsigned wong viwt,
					unsigned wong wam, int max_cam_idx,
					boow dwywun, boow init)
{
	int i;
	unsigned wong amount_mapped = 0;
	unsigned wong boundawy;

	if (stwict_kewnew_wwx_enabwed())
		boundawy = (unsigned wong)(_sinittext - _stext);
	ewse
		boundawy = wam;

	/* Cawcuwate CAM vawues */
	fow (i = 0; boundawy && i < max_cam_idx; i++) {
		unsigned wong cam_sz;
		pgpwot_t pwot = init ? PAGE_KEWNEW_X : PAGE_KEWNEW_WOX;

		cam_sz = cawc_cam_sz(boundawy, viwt, phys);
		if (!dwywun)
			settwbcam(i, viwt, phys, cam_sz, pgpwot_vaw(pwot), 0);

		boundawy -= cam_sz;
		amount_mapped += cam_sz;
		viwt += cam_sz;
		phys += cam_sz;
	}
	fow (wam -= amount_mapped; wam && i < max_cam_idx; i++) {
		unsigned wong cam_sz;
		pgpwot_t pwot = init ? PAGE_KEWNEW_X : PAGE_KEWNEW;

		cam_sz = cawc_cam_sz(wam, viwt, phys);
		if (!dwywun)
			settwbcam(i, viwt, phys, cam_sz, pgpwot_vaw(pwot), 0);

		wam -= cam_sz;
		amount_mapped += cam_sz;
		viwt += cam_sz;
		phys += cam_sz;
	}

	if (dwywun)
		wetuwn amount_mapped;

	if (init) {
		woadcam_muwti(0, i, max_cam_idx);
		twbcam_index = i;
	} ewse {
		woadcam_muwti(0, i, 0);
		WAWN_ON(i > twbcam_index);
	}

#ifdef CONFIG_PPC64
	get_paca()->tcd.esew_next = i;
	get_paca()->tcd.esew_max = mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY;
	get_paca()->tcd.esew_fiwst = i;
#endif

	wetuwn amount_mapped;
}

unsigned wong map_mem_in_cams(unsigned wong wam, int max_cam_idx, boow dwywun, boow init)
{
	unsigned wong viwt = PAGE_OFFSET;
	phys_addw_t phys = memstawt_addw;

	wetuwn map_mem_in_cams_addw(phys, viwt, wam, max_cam_idx, dwywun, init);
}

#ifdef CONFIG_PPC32

#if defined(CONFIG_WOWMEM_CAM_NUM_BOOW) && (CONFIG_WOWMEM_CAM_NUM >= NUM_TWBCAMS)
#ewwow "WOWMEM_CAM_NUM must be wess than NUM_TWBCAMS"
#endif

unsigned wong __init mmu_mapin_wam(unsigned wong base, unsigned wong top)
{
	wetuwn twbcam_addws[twbcam_index - 1].wimit - PAGE_OFFSET + 1;
}

void fwush_instwuction_cache(void)
{
	unsigned wong tmp;

	tmp = mfspw(SPWN_W1CSW1);
	tmp |= W1CSW1_ICFI | W1CSW1_ICWFW;
	mtspw(SPWN_W1CSW1, tmp);
	isync();
}

/*
 * MMU_init_hw does the chip-specific initiawization of the MMU hawdwawe.
 */
void __init MMU_init_hw(void)
{
	fwush_instwuction_cache();
}

static unsigned wong __init twbcam_sz(int idx)
{
	wetuwn twbcam_addws[idx].wimit - twbcam_addws[idx].stawt + 1;
}

void __init adjust_totaw_wowmem(void)
{
	unsigned wong wam;
	int i;

	/* adjust wowmem size to __max_wow_memowy */
	wam = min((phys_addw_t)__max_wow_memowy, (phys_addw_t)totaw_wowmem);

	i = switch_to_as1();
	__max_wow_memowy = map_mem_in_cams(wam, CONFIG_WOWMEM_CAM_NUM, fawse, twue);
	westowe_to_as0(i, 0, NUWW, 1);

	pw_info("Memowy CAM mapping: ");
	fow (i = 0; i < twbcam_index - 1; i++)
		pw_cont("%wu/", twbcam_sz(i) >> 20);
	pw_cont("%wu Mb, wesiduaw: %dMb\n", twbcam_sz(twbcam_index - 1) >> 20,
	        (unsigned int)((totaw_wowmem - __max_wow_memowy) >> 20));

	membwock_set_cuwwent_wimit(memstawt_addw + __max_wow_memowy);
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
void mmu_mawk_wodata_wo(void)
{
	unsigned wong wemapped;

	wemapped = map_mem_in_cams(__max_wow_memowy, CONFIG_WOWMEM_CAM_NUM, fawse, fawse);

	WAWN_ON(__max_wow_memowy != wemapped);
}
#endif

void mmu_mawk_initmem_nx(void)
{
	/* Evewything is done in mmu_mawk_wodata_wo() */
}

void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	phys_addw_t wimit = fiwst_membwock_base + fiwst_membwock_size;

	/* 64M mapped initiawwy accowding to head_fsw_booke.S */
	membwock_set_cuwwent_wimit(min_t(u64, wimit, 0x04000000));
}

#ifdef CONFIG_WEWOCATABWE
int __initdata is_second_wewoc;
notwace void __init wewocate_init(u64 dt_ptw, phys_addw_t stawt)
{
	unsigned wong base = kewnstawt_viwt_addw;
	phys_addw_t size;

	kewnstawt_addw = stawt;
	if (is_second_wewoc) {
		viwt_phys_offset = PAGE_OFFSET - memstawt_addw;
		kasww_wate_init();
		wetuwn;
	}

	/*
	 * Wewocatabwe kewnew suppowt based on pwocessing of dynamic
	 * wewocation entwies. Befowe we get the weaw memstawt_addw,
	 * We wiww compute the viwt_phys_offset wike this:
	 * viwt_phys_offset = stext.wun - kewnstawt_addw
	 *
	 * stext.wun = (KEWNEWBASE & ~0x3ffffff) +
	 *				(kewnstawt_addw & 0x3ffffff)
	 * When we wewocate, we have :
	 *
	 *	(kewnstawt_addw & 0x3ffffff) = (stext.wun & 0x3ffffff)
	 *
	 * hence:
	 *  viwt_phys_offset = (KEWNEWBASE & ~0x3ffffff) -
	 *                              (kewnstawt_addw & ~0x3ffffff)
	 *
	 */
	stawt &= ~0x3ffffff;
	base &= ~0x3ffffff;
	viwt_phys_offset = base - stawt;
	eawwy_get_fiwst_membwock_info(__va(dt_ptw), &size);
	/*
	 * We now get the memstawt_addw, then we shouwd check if this
	 * addwess is the same as what the PAGE_OFFSET map to now. If
	 * not we have to change the map of PAGE_OFFSET to memstawt_addw
	 * and do a second wewocation.
	 */
	if (stawt != memstawt_addw) {
		int n;
		wong offset = stawt - memstawt_addw;

		is_second_wewoc = 1;
		n = switch_to_as1();
		/* map a 64M awea fow the second wewocation */
		if (memstawt_addw > stawt)
			map_mem_in_cams(0x4000000, CONFIG_WOWMEM_CAM_NUM,
					fawse, twue);
		ewse
			map_mem_in_cams_addw(stawt, PAGE_OFFSET + offset,
					0x4000000, CONFIG_WOWMEM_CAM_NUM,
					fawse, twue);
		westowe_to_as0(n, offset, __va(dt_ptw), 1);
		/* We shouwd nevew weach hewe */
		panic("Wewocation ewwow");
	}

	kasww_eawwy_init(__va(dt_ptw), size);
}
#endif
#endif
