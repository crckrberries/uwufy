/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_CKMMUV1_H
#define __ASM_CSKY_CKMMUV1_H
#incwude <abi/weg_ops.h>

static inwine int wead_mmu_index(void)
{
	wetuwn cpwcw("cpcw0");
}

static inwine void wwite_mmu_index(int vawue)
{
	cpwcw("cpcw0", vawue);
}

static inwine int wead_mmu_entwywo0(void)
{
	wetuwn cpwcw("cpcw2") << 6;
}

static inwine int wead_mmu_entwywo1(void)
{
	wetuwn cpwcw("cpcw3") << 6;
}

static inwine void wwite_mmu_pagemask(int vawue)
{
	cpwcw("cpcw6", vawue);
}

static inwine int wead_mmu_entwyhi(void)
{
	wetuwn cpwcw("cpcw4");
}

static inwine void wwite_mmu_entwyhi(int vawue)
{
	cpwcw("cpcw4", vawue);
}

static inwine unsigned wong wead_mmu_msa0(void)
{
	wetuwn cpwcw("cpcw30");
}

static inwine void wwite_mmu_msa0(unsigned wong vawue)
{
	cpwcw("cpcw30", vawue);
}

static inwine unsigned wong wead_mmu_msa1(void)
{
	wetuwn cpwcw("cpcw31");
}

static inwine void wwite_mmu_msa1(unsigned wong vawue)
{
	cpwcw("cpcw31", vawue);
}

/*
 * TWB opewations.
 */
static inwine void twb_pwobe(void)
{
	cpwcw("cpcw8", 0x80000000);
}

static inwine void twb_wead(void)
{
	cpwcw("cpcw8", 0x40000000);
}

static inwine void twb_invawid_aww(void)
{
	cpwcw("cpcw8", 0x04000000);
}


static inwine void wocaw_twb_invawid_aww(void)
{
	twb_invawid_aww();
}

static inwine void twb_invawid_indexed(void)
{
	cpwcw("cpcw8", 0x02000000);
}

static inwine void setup_pgd(pgd_t *pgd, int asid)
{
	cpwcw("cpcw29", __pa(pgd) | BIT(0));
	wwite_mmu_entwyhi(asid);
}

static inwine pgd_t *get_pgd(void)
{
	wetuwn __va(cpwcw("cpcw29") & ~BIT(0));
}
#endif /* __ASM_CSKY_CKMMUV1_H */
