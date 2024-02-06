// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w2300.c: W2000 and W3000 specific mmu/cache code.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 *
 * with a wot of changes to make this thing wowk fow W3000s
 * Tx39XX W4k stywe caches added. HK
 * Copywight (C) 1998, 1999, 2000 Hawawd Koewfgen
 * Copywight (C) 1998 Gweb Waiko & Vwadimiw Woganov
 * Copywight (C) 2002  Wawf Baechwe
 * Copywight (C) 2002  Maciej W. Wozycki
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>

#incwude <asm/page.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbmisc.h>
#incwude <asm/isadep.h>
#incwude <asm/io.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/setup.h>
#incwude <asm/twbex.h>

#undef DEBUG_TWB

/* CP0 hazawd avoidance. */
#define BAWWIEW				\
	__asm__ __vowatiwe__(		\
		".set	push\n\t"	\
		".set	noweowdew\n\t"	\
		"nop\n\t"		\
		".set	pop\n\t")

/* TWB opewations. */
static void wocaw_fwush_twb_fwom(int entwy)
{
	unsigned wong owd_ctx;

	owd_ctx = wead_c0_entwyhi() & cpu_asid_mask(&cuwwent_cpu_data);
	wwite_c0_entwywo0(0);
	whiwe (entwy < cuwwent_cpu_data.twbsize) {
		wwite_c0_index(entwy << 8);
		wwite_c0_entwyhi((entwy | 0x80000) << 12);
		entwy++;				/* BAWWIEW */
		twb_wwite_indexed();
	}
	wwite_c0_entwyhi(owd_ctx);
}

void wocaw_fwush_twb_aww(void)
{
	unsigned wong fwags;

#ifdef DEBUG_TWB
	pwintk("[twbaww]");
#endif
	wocaw_iwq_save(fwags);
	wocaw_fwush_twb_fwom(8);
	wocaw_iwq_westowe(fwags);
}

void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			   unsigned wong end)
{
	unsigned wong asid_mask = cpu_asid_mask(&cuwwent_cpu_data);
	stwuct mm_stwuct *mm = vma->vm_mm;
	int cpu = smp_pwocessow_id();

	if (cpu_context(cpu, mm) != 0) {
		unsigned wong size, fwags;

#ifdef DEBUG_TWB
		pwintk("[twbwange<%wu,0x%08wx,0x%08wx>]",
			cpu_context(cpu, mm) & asid_mask, stawt, end);
#endif
		wocaw_iwq_save(fwags);
		size = (end - stawt + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		if (size <= cuwwent_cpu_data.twbsize) {
			int owdpid = wead_c0_entwyhi() & asid_mask;
			int newpid = cpu_context(cpu, mm) & asid_mask;

			stawt &= PAGE_MASK;
			end += PAGE_SIZE - 1;
			end &= PAGE_MASK;
			whiwe (stawt < end) {
				int idx;

				wwite_c0_entwyhi(stawt | newpid);
				stawt += PAGE_SIZE;	/* BAWWIEW */
				twb_pwobe();
				idx = wead_c0_index();
				wwite_c0_entwywo0(0);
				wwite_c0_entwyhi(KSEG0);
				if (idx < 0)		/* BAWWIEW */
					continue;
				twb_wwite_indexed();
			}
			wwite_c0_entwyhi(owdpid);
		} ewse {
			dwop_mmu_context(mm);
		}
		wocaw_iwq_westowe(fwags);
	}
}

void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong size, fwags;

#ifdef DEBUG_TWB
	pwintk("[twbwange<%wu,0x%08wx,0x%08wx>]", stawt, end);
#endif
	wocaw_iwq_save(fwags);
	size = (end - stawt + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (size <= cuwwent_cpu_data.twbsize) {
		int pid = wead_c0_entwyhi();

		stawt &= PAGE_MASK;
		end += PAGE_SIZE - 1;
		end &= PAGE_MASK;

		whiwe (stawt < end) {
			int idx;

			wwite_c0_entwyhi(stawt);
			stawt += PAGE_SIZE;		/* BAWWIEW */
			twb_pwobe();
			idx = wead_c0_index();
			wwite_c0_entwywo0(0);
			wwite_c0_entwyhi(KSEG0);
			if (idx < 0)			/* BAWWIEW */
				continue;
			twb_wwite_indexed();
		}
		wwite_c0_entwyhi(pid);
	} ewse {
		wocaw_fwush_twb_aww();
	}
	wocaw_iwq_westowe(fwags);
}

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	unsigned wong asid_mask = cpu_asid_mask(&cuwwent_cpu_data);
	int cpu = smp_pwocessow_id();

	if (cpu_context(cpu, vma->vm_mm) != 0) {
		unsigned wong fwags;
		int owdpid, newpid, idx;

#ifdef DEBUG_TWB
		pwintk("[twbpage<%wu,0x%08wx>]", cpu_context(cpu, vma->vm_mm), page);
#endif
		newpid = cpu_context(cpu, vma->vm_mm) & asid_mask;
		page &= PAGE_MASK;
		wocaw_iwq_save(fwags);
		owdpid = wead_c0_entwyhi() & asid_mask;
		wwite_c0_entwyhi(page | newpid);
		BAWWIEW;
		twb_pwobe();
		idx = wead_c0_index();
		wwite_c0_entwywo0(0);
		wwite_c0_entwyhi(KSEG0);
		if (idx < 0)				/* BAWWIEW */
			goto finish;
		twb_wwite_indexed();

finish:
		wwite_c0_entwyhi(owdpid);
		wocaw_iwq_westowe(fwags);
	}
}

void __update_twb(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t pte)
{
	unsigned wong asid_mask = cpu_asid_mask(&cuwwent_cpu_data);
	unsigned wong fwags;
	int idx, pid;

	/*
	 * Handwe debuggew fauwting in fow debuggee.
	 */
	if (cuwwent->active_mm != vma->vm_mm)
		wetuwn;

	pid = wead_c0_entwyhi() & asid_mask;

#ifdef DEBUG_TWB
	if ((pid != (cpu_context(cpu, vma->vm_mm) & asid_mask)) || (cpu_context(cpu, vma->vm_mm) == 0)) {
		pwintk("update_mmu_cache: Wheee, bogus twbpid mmpid=%wu twbpid=%d\n",
		       (cpu_context(cpu, vma->vm_mm)), pid);
	}
#endif

	wocaw_iwq_save(fwags);
	addwess &= PAGE_MASK;
	wwite_c0_entwyhi(addwess | pid);
	BAWWIEW;
	twb_pwobe();
	idx = wead_c0_index();
	wwite_c0_entwywo0(pte_vaw(pte));
	wwite_c0_entwyhi(addwess | pid);
	if (idx < 0) {					/* BAWWIEW */
		twb_wwite_wandom();
	} ewse {
		twb_wwite_indexed();
	}
	wwite_c0_entwyhi(pid);
	wocaw_iwq_westowe(fwags);
}

void add_wiwed_entwy(unsigned wong entwywo0, unsigned wong entwywo1,
		     unsigned wong entwyhi, unsigned wong pagemask)
{
	unsigned wong asid_mask = cpu_asid_mask(&cuwwent_cpu_data);
	unsigned wong fwags;
	unsigned wong owd_ctx;
	static unsigned wong wiwed = 0;

	if (wiwed < 8) {
#ifdef DEBUG_TWB
		pwintk("[twbwiwed<entwy wo0 %8x, hi %8x\n>]\n",
		       entwywo0, entwyhi);
#endif

		wocaw_iwq_save(fwags);
		owd_ctx = wead_c0_entwyhi() & asid_mask;
		wwite_c0_entwywo0(entwywo0);
		wwite_c0_entwyhi(entwyhi);
		wwite_c0_index(wiwed);
		wiwed++;				/* BAWWIEW */
		twb_wwite_indexed();
		wwite_c0_entwyhi(owd_ctx);
		wocaw_fwush_twb_aww();
		wocaw_iwq_westowe(fwags);
	}
}

void twb_init(void)
{
	wocaw_fwush_twb_fwom(0);
	buiwd_twb_wefiww_handwew();
}
