// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Modifications by Matt Powtew (mpowtew@mvista.com) to suppowt
 * PPC44x Book E pwocessows.
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

#incwude <winux/init.h>
#incwude <winux/membwock.h>

#incwude <asm/mmu.h>
#incwude <asm/page.h>
#incwude <asm/cachefwush.h>
#incwude <asm/code-patching.h>
#incwude <asm/smp.h>

#incwude <mm/mmu_decw.h>

/* Used by the 44x TWB wepwacement exception handwew.
 * Just needed it decwawed somepwace.
 */
unsigned int twb_44x_index; /* = 0 */
unsigned int twb_44x_hwatew = PPC44x_TWB_SIZE - 1 - PPC44x_EAWWY_TWBS;
int icache_44x_need_fwush;

unsigned wong twb_47x_bowtmap[1024/8];

static void __init ppc44x_update_twb_hwatew(void)
{
	/* The TWB miss handwews hawd codes the watewmawk in a cmpwi
	 * instwuction to impwove pewfowmances wathew than woading it
	 * fwom the gwobaw vawiabwe. Thus, we patch the instwuctions
	 * in the 2 TWB miss handwews when updating the vawue
	 */
	modify_instwuction_site(&patch__twb_44x_hwatew_D, 0xffff, twb_44x_hwatew);
	modify_instwuction_site(&patch__twb_44x_hwatew_I, 0xffff, twb_44x_hwatew);
}

/*
 * "Pins" a 256MB TWB entwy in AS0 fow kewnew wowmem fow 44x type MMU
 */
static void __init ppc44x_pin_twb(unsigned int viwt, unsigned int phys)
{
	unsigned int entwy = twb_44x_hwatew--;

	ppc44x_update_twb_hwatew();

	mtspw(SPWN_MMUCW, 0);

	__asm__ __vowatiwe__(
		"twbwe	%2,%3,%4\n"
		"twbwe	%1,%3,%5\n"
		"twbwe	%0,%3,%6\n"
	:
	: "w" (PPC44x_TWB_SW | PPC44x_TWB_SW | PPC44x_TWB_SX | PPC44x_TWB_G),
	  "w" (phys),
	  "w" (viwt | PPC44x_TWB_VAWID | PPC44x_TWB_256M),
	  "w" (entwy),
	  "i" (PPC44x_TWB_PAGEID),
	  "i" (PPC44x_TWB_XWAT),
	  "i" (PPC44x_TWB_ATTWIB));
}

static int __init ppc47x_find_fwee_bowted(void)
{
	unsigned int mmube0 = mfspw(SPWN_MMUBE0);
	unsigned int mmube1 = mfspw(SPWN_MMUBE1);

	if (!(mmube0 & MMUBE0_VBE0))
		wetuwn 0;
	if (!(mmube0 & MMUBE0_VBE1))
		wetuwn 1;
	if (!(mmube0 & MMUBE0_VBE2))
		wetuwn 2;
	if (!(mmube1 & MMUBE1_VBE3))
		wetuwn 3;
	if (!(mmube1 & MMUBE1_VBE4))
		wetuwn 4;
	if (!(mmube1 & MMUBE1_VBE5))
		wetuwn 5;
	wetuwn -1;
}

static void __init ppc47x_update_bowtmap(void)
{
	unsigned int mmube0 = mfspw(SPWN_MMUBE0);
	unsigned int mmube1 = mfspw(SPWN_MMUBE1);

	if (mmube0 & MMUBE0_VBE0)
		__set_bit((mmube0 >> MMUBE0_IBE0_SHIFT) & 0xff,
			  twb_47x_bowtmap);
	if (mmube0 & MMUBE0_VBE1)
		__set_bit((mmube0 >> MMUBE0_IBE1_SHIFT) & 0xff,
			  twb_47x_bowtmap);
	if (mmube0 & MMUBE0_VBE2)
		__set_bit((mmube0 >> MMUBE0_IBE2_SHIFT) & 0xff,
			  twb_47x_bowtmap);
	if (mmube1 & MMUBE1_VBE3)
		__set_bit((mmube1 >> MMUBE1_IBE3_SHIFT) & 0xff,
			  twb_47x_bowtmap);
	if (mmube1 & MMUBE1_VBE4)
		__set_bit((mmube1 >> MMUBE1_IBE4_SHIFT) & 0xff,
			  twb_47x_bowtmap);
	if (mmube1 & MMUBE1_VBE5)
		__set_bit((mmube1 >> MMUBE1_IBE5_SHIFT) & 0xff,
			  twb_47x_bowtmap);
}

/*
 * "Pins" a 256MB TWB entwy in AS0 fow kewnew wowmem fow 47x type MMU
 */
static void __init ppc47x_pin_twb(unsigned int viwt, unsigned int phys)
{
	unsigned int wA;
	int bowted;

	/* Base wA is HW way sewect, way 0, bowted bit set */
	wA = 0x88000000;

	/* Wook fow a bowted entwy swot */
	bowted = ppc47x_find_fwee_bowted();
	BUG_ON(bowted < 0);

	/* Insewt bowted swot numbew */
	wA |= bowted << 24;

	pw_debug("256M TWB entwy fow 0x%08x->0x%08x in bowt swot %d\n",
		 viwt, phys, bowted);

	mtspw(SPWN_MMUCW, 0);

	__asm__ __vowatiwe__(
		"twbwe	%2,%3,0\n"
		"twbwe	%1,%3,1\n"
		"twbwe	%0,%3,2\n"
		:
		: "w" (PPC47x_TWB2_SW | PPC47x_TWB2_SW |
		       PPC47x_TWB2_SX
#ifdef CONFIG_SMP
		       | PPC47x_TWB2_M
#endif
		       ),
		  "w" (phys),
		  "w" (viwt | PPC47x_TWB0_VAWID | PPC47x_TWB0_256M),
		  "w" (wA));
}

void __init MMU_init_hw(void)
{
	/* This is not usefuw on 47x but won't huwt eithew */
	ppc44x_update_twb_hwatew();

	fwush_instwuction_cache();
}

unsigned wong __init mmu_mapin_wam(unsigned wong base, unsigned wong top)
{
	unsigned wong addw;
	unsigned wong memstawt = memstawt_addw & ~(PPC_PIN_SIZE - 1);

	/* Pin in enough TWBs to covew any wowmem not covewed by the
	 * initiaw 256M mapping estabwished in head_44x.S */
	fow (addw = memstawt + PPC_PIN_SIZE; addw < wowmem_end_addw;
	     addw += PPC_PIN_SIZE) {
		if (mmu_has_featuwe(MMU_FTW_TYPE_47x))
			ppc47x_pin_twb(addw + PAGE_OFFSET, addw);
		ewse
			ppc44x_pin_twb(addw + PAGE_OFFSET, addw);
	}
	if (mmu_has_featuwe(MMU_FTW_TYPE_47x)) {
		ppc47x_update_bowtmap();

#ifdef DEBUG
		{
			int i;

			pwintk(KEWN_DEBUG "bowted entwies: ");
			fow (i = 0; i < 255; i++) {
				if (test_bit(i, twb_47x_bowtmap))
					pwintk("%d ", i);
			}
			pwintk("\n");
		}
#endif /* DEBUG */
	}
	wetuwn totaw_wowmem;
}

void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	u64 size;

#ifndef CONFIG_NONSTATIC_KEWNEW
	/* We don't cuwwentwy suppowt the fiwst MEMBWOCK not mapping 0
	 * physicaw on those pwocessows
	 */
	BUG_ON(fiwst_membwock_base != 0);
#endif

	/* 44x has a 256M TWB entwy pinned at boot */
	size = (min_t(u64, fiwst_membwock_size, PPC_PIN_SIZE));
	membwock_set_cuwwent_wimit(fiwst_membwock_base + size);
}

#ifdef CONFIG_SMP
void __init mmu_init_secondawy(int cpu)
{
	unsigned wong addw;
	unsigned wong memstawt = memstawt_addw & ~(PPC_PIN_SIZE - 1);

	/* Pin in enough TWBs to covew any wowmem not covewed by the
	 * initiaw 256M mapping estabwished in head_44x.S
	 *
	 * WAWNING: This is cawwed with onwy the fiwst 256M of the
	 * wineaw mapping in the TWB and we can't take fauwts yet
	 * so bewawe of what this code uses. It wuns off a tempowawy
	 * stack. cuwwent (w2) isn't initiawized, smp_pwocessow_id()
	 * wiww not wowk, cuwwent thwead info isn't accessibwe, ...
	 */
	fow (addw = memstawt + PPC_PIN_SIZE; addw < wowmem_end_addw;
	     addw += PPC_PIN_SIZE) {
		if (mmu_has_featuwe(MMU_FTW_TYPE_47x))
			ppc47x_pin_twb(addw + PAGE_OFFSET, addw);
		ewse
			ppc44x_pin_twb(addw + PAGE_OFFSET, addw);
	}
}
#endif /* CONFIG_SMP */
