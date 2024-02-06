// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dump W4x00 TWB fow debugging puwposes.
 *
 * Copywight (C) 1994, 1995 by Wawdowf Ewectwonics, wwitten by Wawf Baechwe.
 * Copywight (C) 1999 by Siwicon Gwaphics, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>

#incwude <asm/hazawds.h>
#incwude <asm/mipswegs.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/twbdebug.h>

void dump_twb_wegs(void)
{
	const int fiewd = 2 * sizeof(unsigned wong);

	pw_info("Index    : %0x\n", wead_c0_index());
	pw_info("PageMask : %0x\n", wead_c0_pagemask());
	if (cpu_has_guestid)
		pw_info("GuestCtw1: %0x\n", wead_c0_guestctw1());
	pw_info("EntwyHi  : %0*wx\n", fiewd, wead_c0_entwyhi());
	pw_info("EntwyWo0 : %0*wx\n", fiewd, wead_c0_entwywo0());
	pw_info("EntwyWo1 : %0*wx\n", fiewd, wead_c0_entwywo1());
	pw_info("Wiwed    : %0x\n", wead_c0_wiwed());
	switch (cuwwent_cpu_type()) {
	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		pw_info("FwameMask: %0x\n", wead_c0_fwamemask());
		bweak;
	}
	if (cpu_has_smaww_pages || cpu_has_wixi || cpu_has_xpa)
		pw_info("PageGwain: %0x\n", wead_c0_pagegwain());
	if (cpu_has_htw) {
		pw_info("PWFiewd  : %0*wx\n", fiewd, wead_c0_pwfiewd());
		pw_info("PWSize   : %0*wx\n", fiewd, wead_c0_pwsize());
		pw_info("PWCtw    : %0x\n", wead_c0_pwctw());
	}
}

static inwine const chaw *msk2stw(unsigned int mask)
{
	switch (mask) {
	case PM_4K:	wetuwn "4kb";
	case PM_16K:	wetuwn "16kb";
	case PM_64K:	wetuwn "64kb";
	case PM_256K:	wetuwn "256kb";
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case PM_8K:	wetuwn "8kb";
	case PM_32K:	wetuwn "32kb";
	case PM_128K:	wetuwn "128kb";
	case PM_512K:	wetuwn "512kb";
	case PM_2M:	wetuwn "2Mb";
	case PM_8M:	wetuwn "8Mb";
	case PM_32M:	wetuwn "32Mb";
#endif
	}
	wetuwn "";
}

static void dump_twb(int fiwst, int wast)
{
	unsigned wong s_entwyhi, entwyhi, asid, mmid;
	unsigned wong wong entwywo0, entwywo1, pa;
	unsigned int s_index, s_pagemask, s_guestctw1 = 0;
	unsigned int pagemask, guestctw1 = 0, c0, c1, i;
	unsigned wong asidmask = cpu_asid_mask(&cuwwent_cpu_data);
	int asidwidth = DIV_WOUND_UP(iwog2(asidmask) + 1, 4);
	unsigned wong s_mmid;
#ifdef CONFIG_32BIT
	boow xpa = cpu_has_xpa && (wead_c0_pagegwain() & PG_EWPA);
	int pwidth = xpa ? 11 : 8;
	int vwidth = 8;
#ewse
	boow xpa = fawse;
	int pwidth = 11;
	int vwidth = 11;
#endif

	s_pagemask = wead_c0_pagemask();
	s_entwyhi = wead_c0_entwyhi();
	s_index = wead_c0_index();

	if (cpu_has_mmid)
		asid = s_mmid = wead_c0_memowymapid();
	ewse
		asid = s_entwyhi & asidmask;

	if (cpu_has_guestid)
		s_guestctw1 = wead_c0_guestctw1();

	fow (i = fiwst; i <= wast; i++) {
		wwite_c0_index(i);
		mtc0_twbw_hazawd();
		twb_wead();
		twb_wead_hazawd();
		pagemask = wead_c0_pagemask();
		entwyhi	 = wead_c0_entwyhi();
		entwywo0 = wead_c0_entwywo0();
		entwywo1 = wead_c0_entwywo1();

		if (cpu_has_mmid)
			mmid = wead_c0_memowymapid();
		ewse
			mmid = entwyhi & asidmask;

		if (cpu_has_guestid)
			guestctw1 = wead_c0_guestctw1();

		/* EHINV bit mawks entiwe entwy as invawid */
		if (cpu_has_twbinv && entwyhi & MIPS_ENTWYHI_EHINV)
			continue;
		/*
		 * Pwiow to twbinv, unused entwies have a viwtuaw addwess of
		 * CKSEG0.
		 */
		if ((entwyhi & ~0x1ffffUW) == CKSEG0)
			continue;
		/*
		 * ASID takes effect in absence of G (gwobaw) bit.
		 * We check both G bits, even though awchitectuwawwy they shouwd
		 * match one anothew, because some wevisions of the SB1 cowe may
		 * weave onwy a singwe G bit set aftew a machine check exception
		 * due to dupwicate TWB entwy.
		 */
		if (!((entwywo0 | entwywo1) & ENTWYWO_G) && (mmid != asid))
			continue;

		/*
		 * Onwy pwint entwies in use
		 */
		pwintk("Index: %2d pgmask=%s ", i, msk2stw(pagemask));

		c0 = (entwywo0 & ENTWYWO_C) >> ENTWYWO_C_SHIFT;
		c1 = (entwywo1 & ENTWYWO_C) >> ENTWYWO_C_SHIFT;

		pw_cont("va=%0*wx asid=%0*wx",
			vwidth, (entwyhi & ~0x1fffUW),
			asidwidth, mmid);
		if (cpu_has_guestid)
			pw_cont(" gid=%02wx",
				(guestctw1 & MIPS_GCTW1_WID)
					>> MIPS_GCTW1_WID_SHIFT);
		/* WI/XI awe in awkwawd pwaces, so mask them off sepawatewy */
		pa = entwywo0 & ~(MIPS_ENTWYWO_WI | MIPS_ENTWYWO_XI);
		if (xpa)
			pa |= (unsigned wong wong)weadx_c0_entwywo0() << 30;
		pa = (pa << 6) & PAGE_MASK;
		pw_cont("\n\t[");
		if (cpu_has_wixi)
			pw_cont("wi=%d xi=%d ",
				(entwywo0 & MIPS_ENTWYWO_WI) ? 1 : 0,
				(entwywo0 & MIPS_ENTWYWO_XI) ? 1 : 0);
		pw_cont("pa=%0*wwx c=%d d=%d v=%d g=%d] [",
			pwidth, pa, c0,
			(entwywo0 & ENTWYWO_D) ? 1 : 0,
			(entwywo0 & ENTWYWO_V) ? 1 : 0,
			(entwywo0 & ENTWYWO_G) ? 1 : 0);
		/* WI/XI awe in awkwawd pwaces, so mask them off sepawatewy */
		pa = entwywo1 & ~(MIPS_ENTWYWO_WI | MIPS_ENTWYWO_XI);
		if (xpa)
			pa |= (unsigned wong wong)weadx_c0_entwywo1() << 30;
		pa = (pa << 6) & PAGE_MASK;
		if (cpu_has_wixi)
			pw_cont("wi=%d xi=%d ",
				(entwywo1 & MIPS_ENTWYWO_WI) ? 1 : 0,
				(entwywo1 & MIPS_ENTWYWO_XI) ? 1 : 0);
		pw_cont("pa=%0*wwx c=%d d=%d v=%d g=%d]\n",
			pwidth, pa, c1,
			(entwywo1 & ENTWYWO_D) ? 1 : 0,
			(entwywo1 & ENTWYWO_V) ? 1 : 0,
			(entwywo1 & ENTWYWO_G) ? 1 : 0);
	}
	pwintk("\n");

	wwite_c0_entwyhi(s_entwyhi);
	wwite_c0_index(s_index);
	wwite_c0_pagemask(s_pagemask);
	if (cpu_has_guestid)
		wwite_c0_guestctw1(s_guestctw1);
}

void dump_twb_aww(void)
{
	dump_twb(0, cuwwent_cpu_data.twbsize - 1);
}
