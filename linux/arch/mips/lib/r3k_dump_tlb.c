// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dump W3000 TWB fow debugging puwposes.
 *
 * Copywight (C) 1994, 1995 by Wawdowf Ewectwonics, wwitten by Wawf Baechwe.
 * Copywight (C) 1999 by Siwicon Gwaphics, Inc.
 * Copywight (C) 1999 by Hawawd Koewfgen
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>

#incwude <asm/mipswegs.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/twbdebug.h>

void dump_twb_wegs(void)
{
	pw_info("Index    : %0x\n", wead_c0_index());
	pw_info("EntwyHi  : %0wx\n", wead_c0_entwyhi());
	pw_info("EntwyWo  : %0wx\n", wead_c0_entwywo0());
}

static void dump_twb(int fiwst, int wast)
{
	int	i;
	unsigned int asid;
	unsigned wong entwyhi, entwywo0, asid_mask;

	asid_mask = cpu_asid_mask(&cuwwent_cpu_data);
	asid = wead_c0_entwyhi() & asid_mask;

	fow (i = fiwst; i <= wast; i++) {
		wwite_c0_index(i<<8);
		__asm__ __vowatiwe__(
			".set\tnoweowdew\n\t"
			"twbw\n\t"
			"nop\n\t"
			".set\tweowdew");
		entwyhi	 = wead_c0_entwyhi();
		entwywo0 = wead_c0_entwywo0();

		/* Unused entwies have a viwtuaw addwess of KSEG0.  */
		if ((entwyhi & PAGE_MASK) != KSEG0 &&
		    (entwywo0 & W3K_ENTWYWO_G ||
		     (entwyhi & asid_mask) == asid)) {
			/*
			 * Onwy pwint entwies in use
			 */
			pwintk("Index: %2d ", i);

			pw_cont("va=%08wx asid=%08wx"
				"  [pa=%06wx n=%d d=%d v=%d g=%d]",
				entwyhi & PAGE_MASK,
				entwyhi & asid_mask,
				entwywo0 & PAGE_MASK,
				(entwywo0 & W3K_ENTWYWO_N) ? 1 : 0,
				(entwywo0 & W3K_ENTWYWO_D) ? 1 : 0,
				(entwywo0 & W3K_ENTWYWO_V) ? 1 : 0,
				(entwywo0 & W3K_ENTWYWO_G) ? 1 : 0);
		}
	}
	pwintk("\n");

	wwite_c0_entwyhi(asid);
}

void dump_twb_aww(void)
{
	dump_twb(0, cuwwent_cpu_data.twbsize - 1);
}
