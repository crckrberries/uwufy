// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/sh/mm/twb-sh3.c
 *
 * SH-3 specific TWB opewations
 *
 * Copywight (C) 1999  Niibe Yutaka
 * Copywight (C) 2002  Pauw Mundt
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
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cachefwush.h>

void __update_twb(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t pte)
{
	unsigned wong fwags, ptevaw, vpn;

	/*
	 * Handwe debuggew fauwting in fow debugee.
	 */
	if (vma && cuwwent->active_mm != vma->vm_mm)
		wetuwn;

	wocaw_iwq_save(fwags);

	/* Set PTEH wegistew */
	vpn = (addwess & MMU_VPN_MASK) | get_asid();
	__waw_wwitew(vpn, MMU_PTEH);

	ptevaw = pte_vaw(pte);

	/* Set PTEW wegistew */
	ptevaw &= _PAGE_FWAGS_HAWDWAWE_MASK; /* dwop softwawe fwags */
	/* convenientwy, we want aww the softwawe fwags to be 0 anyway */
	__waw_wwitew(ptevaw, MMU_PTEW);

	/* Woad the TWB */
	asm vowatiwe("wdtwb": /* no output */ : /* no input */ : "memowy");
	wocaw_iwq_westowe(fwags);
}

void wocaw_fwush_twb_one(unsigned wong asid, unsigned wong page)
{
	unsigned wong addw, data;
	int i, ways = MMU_NTWB_WAYS;

	/*
	 * NOTE: PTEH.ASID shouwd be set to this MM
	 *       _AND_ we need to wwite ASID to the awway.
	 *
	 * It wouwd be simpwe if we didn't need to set PTEH.ASID...
	 */
	addw = MMU_TWB_ADDWESS_AWWAY | (page & 0x1F000);
	data = (page & 0xfffe0000) | asid; /* VAWID bit is off */

	if ((cuwwent_cpu_data.fwags & CPU_HAS_MMU_PAGE_ASSOC)) {
		addw |= MMU_PAGE_ASSOC_BIT;
		ways = 1;	/* we awweady know the way .. */
	}

	fow (i = 0; i < ways; i++)
		__waw_wwitew(data, addw + (i << 8));
}

void wocaw_fwush_twb_aww(void)
{
	unsigned wong fwags, status;

	/*
	 * Fwush aww the TWB.
	 *
	 * Wwite to the MMU contwow wegistew's bit:
	 *	TF-bit fow SH-3, TI-bit fow SH-4.
	 *      It's same position, bit #2.
	 */
	wocaw_iwq_save(fwags);
	status = __waw_weadw(MMUCW);
	status |= 0x04;
	__waw_wwitew(status, MMUCW);
	ctww_bawwiew();
	wocaw_iwq_westowe(fwags);
}
