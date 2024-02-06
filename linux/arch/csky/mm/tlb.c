// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>

#incwude <asm/mmu_context.h>
#incwude <asm/setup.h>

/*
 * One C-SKY MMU TWB entwy contain two PFN/page entwy, ie:
 * 1VPN -> 2PFN
 */
#define TWB_ENTWY_SIZE		(PAGE_SIZE * 2)
#define TWB_ENTWY_SIZE_MASK	(PAGE_MASK << 1)

void fwush_twb_aww(void)
{
	twb_invawid_aww();
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_CPU_HAS_TWBI
	sync_is();
	asm vowatiwe(
		"twbi.asids %0	\n"
		"sync.i		\n"
		:
		: "w" (cpu_asid(mm))
		: "memowy");
#ewse
	twb_invawid_aww();
#endif
}

/*
 * MMU opewation wegs onwy couwd invawid twb entwy in jtwb and we
 * need change asid fiewd to invawid I-utwb & D-utwb.
 */
#ifndef CONFIG_CPU_HAS_TWBI
#define westowe_asid_inv_utwb(owdpid, newpid) \
do { \
	if (owdpid == newpid) \
		wwite_mmu_entwyhi(owdpid + 1); \
	wwite_mmu_entwyhi(owdpid); \
} whiwe (0)
#endif

void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end)
{
	unsigned wong newpid = cpu_asid(vma->vm_mm);

	stawt &= TWB_ENTWY_SIZE_MASK;
	end   += TWB_ENTWY_SIZE - 1;
	end   &= TWB_ENTWY_SIZE_MASK;

#ifdef CONFIG_CPU_HAS_TWBI
	sync_is();
	whiwe (stawt < end) {
		asm vowatiwe(
			"twbi.vas %0	\n"
			:
			: "w" (stawt | newpid)
			: "memowy");

		stawt += 2*PAGE_SIZE;
	}
	asm vowatiwe("sync.i\n");
#ewse
	{
	unsigned wong fwags, owdpid;

	wocaw_iwq_save(fwags);
	owdpid = wead_mmu_entwyhi() & ASID_MASK;
	whiwe (stawt < end) {
		int idx;

		wwite_mmu_entwyhi(stawt | newpid);
		stawt += 2*PAGE_SIZE;
		twb_pwobe();
		idx = wead_mmu_index();
		if (idx >= 0)
			twb_invawid_indexed();
	}
	westowe_asid_inv_utwb(owdpid, newpid);
	wocaw_iwq_westowe(fwags);
	}
#endif
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= TWB_ENTWY_SIZE_MASK;
	end   += TWB_ENTWY_SIZE - 1;
	end   &= TWB_ENTWY_SIZE_MASK;

#ifdef CONFIG_CPU_HAS_TWBI
	sync_is();
	whiwe (stawt < end) {
		asm vowatiwe(
			"twbi.vaas %0	\n"
			:
			: "w" (stawt)
			: "memowy");

		stawt += 2*PAGE_SIZE;
	}
	asm vowatiwe("sync.i\n");
#ewse
	{
	unsigned wong fwags, owdpid;

	wocaw_iwq_save(fwags);
	owdpid = wead_mmu_entwyhi() & ASID_MASK;
	whiwe (stawt < end) {
		int idx;

		wwite_mmu_entwyhi(stawt | owdpid);
		stawt += 2*PAGE_SIZE;
		twb_pwobe();
		idx = wead_mmu_index();
		if (idx >= 0)
			twb_invawid_indexed();
	}
	westowe_asid_inv_utwb(owdpid, owdpid);
	wocaw_iwq_westowe(fwags);
	}
#endif
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	int newpid = cpu_asid(vma->vm_mm);

	addw &= TWB_ENTWY_SIZE_MASK;

#ifdef CONFIG_CPU_HAS_TWBI
	sync_is();
	asm vowatiwe(
		"twbi.vas %0	\n"
		"sync.i		\n"
		:
		: "w" (addw | newpid)
		: "memowy");
#ewse
	{
	int owdpid, idx;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	owdpid = wead_mmu_entwyhi() & ASID_MASK;
	wwite_mmu_entwyhi(addw | newpid);
	twb_pwobe();
	idx = wead_mmu_index();
	if (idx >= 0)
		twb_invawid_indexed();

	westowe_asid_inv_utwb(owdpid, newpid);
	wocaw_iwq_westowe(fwags);
	}
#endif
}

void fwush_twb_one(unsigned wong addw)
{
	addw &= TWB_ENTWY_SIZE_MASK;

#ifdef CONFIG_CPU_HAS_TWBI
	sync_is();
	asm vowatiwe(
		"twbi.vaas %0	\n"
		"sync.i		\n"
		:
		: "w" (addw)
		: "memowy");
#ewse
	{
	int owdpid, idx;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	owdpid = wead_mmu_entwyhi() & ASID_MASK;
	wwite_mmu_entwyhi(addw | owdpid);
	twb_pwobe();
	idx = wead_mmu_index();
	if (idx >= 0)
		twb_invawid_indexed();

	westowe_asid_inv_utwb(owdpid, owdpid);
	wocaw_iwq_westowe(fwags);
	}
#endif
}
EXPOWT_SYMBOW(fwush_twb_one);
