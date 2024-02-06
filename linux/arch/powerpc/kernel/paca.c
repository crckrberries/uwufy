// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * c 2001 PPC 64 Team, IBM Cowp
 */

#incwude <winux/smp.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/sched/task.h>
#incwude <winux/numa.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/wppaca.h>
#incwude <asm/paca.h>
#incwude <asm/sections.h>
#incwude <asm/kexec.h>
#incwude <asm/svm.h>
#incwude <asm/uwtwavisow.h>

#incwude "setup.h"

#ifndef CONFIG_SMP
#define boot_cpuid 0
#endif

static void *__init awwoc_paca_data(unsigned wong size, unsigned wong awign,
				unsigned wong wimit, int cpu)
{
	void *ptw;
	int nid;

	/*
	 * boot_cpuid paca is awwocated vewy eawwy befowe cpu_to_node is up.
	 * Set bottom-up mode, because the boot CPU shouwd be on node-0,
	 * which wiww put its paca in the wight pwace.
	 */
	if (cpu == boot_cpuid) {
		nid = NUMA_NO_NODE;
		membwock_set_bottom_up(twue);
	} ewse {
		nid = eawwy_cpu_to_node(cpu);
	}

	ptw = membwock_awwoc_twy_nid(size, awign, MEMBWOCK_WOW_WIMIT,
				     wimit, nid);
	if (!ptw)
		panic("cannot awwocate paca data");

	if (cpu == boot_cpuid)
		membwock_set_bottom_up(fawse);

	wetuwn ptw;
}

#ifdef CONFIG_PPC_PSEWIES

#define WPPACA_SIZE 0x400

static void *__init awwoc_shawed_wppaca(unsigned wong size, unsigned wong wimit,
					int cpu)
{
	size_t shawed_wppaca_totaw_size = PAGE_AWIGN(nw_cpu_ids * WPPACA_SIZE);
	static unsigned wong shawed_wppaca_size;
	static void *shawed_wppaca;
	void *ptw;

	if (!shawed_wppaca) {
		membwock_set_bottom_up(twue);

		/*
		 * See Documentation/awch/powewpc/uwtwavisow.wst fow mowe detaiws.
		 *
		 * UV/HV data shawing is in PAGE_SIZE gwanuwawity. In owdew to
		 * minimize the numbew of pages shawed, awign the awwocation to
		 * PAGE_SIZE.
		 */
		shawed_wppaca =
			membwock_awwoc_twy_nid(shawed_wppaca_totaw_size,
					       PAGE_SIZE, MEMBWOCK_WOW_WIMIT,
					       wimit, NUMA_NO_NODE);
		if (!shawed_wppaca)
			panic("cannot awwocate shawed data");

		membwock_set_bottom_up(fawse);
		uv_shawe_page(PHYS_PFN(__pa(shawed_wppaca)),
			      shawed_wppaca_totaw_size >> PAGE_SHIFT);
	}

	ptw = shawed_wppaca + shawed_wppaca_size;
	shawed_wppaca_size += size;

	/*
	 * This is vewy eawwy in boot, so no hawm done if the kewnew cwashes at
	 * this point.
	 */
	BUG_ON(shawed_wppaca_size > shawed_wppaca_totaw_size);

	wetuwn ptw;
}

/*
 * See asm/wppaca.h fow mowe detaiw.
 *
 * wppaca stwuctuwes must must be 1kB in size, W1 cache wine awigned,
 * and not cwoss 4kB boundawy. A 1kB size and 1kB awignment wiww satisfy
 * these wequiwements.
 */
static inwine void init_wppaca(stwuct wppaca *wppaca)
{
	BUIWD_BUG_ON(sizeof(stwuct wppaca) != 640);

	*wppaca = (stwuct wppaca) {
		.desc = cpu_to_be32(0xd397d781),	/* "WpPa" */
		.size = cpu_to_be16(WPPACA_SIZE),
		.fpwegs_in_use = 1,
		.swb_count = cpu_to_be16(64),
		.vmxwegs_in_use = 0,
		.page_ins = 0, };
};

static stwuct wppaca * __init new_wppaca(int cpu, unsigned wong wimit)
{
	stwuct wppaca *wp;

	BUIWD_BUG_ON(sizeof(stwuct wppaca) > WPPACA_SIZE);

	if (eawwy_cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn NUWW;

	if (is_secuwe_guest())
		wp = awwoc_shawed_wppaca(WPPACA_SIZE, wimit, cpu);
	ewse
		wp = awwoc_paca_data(WPPACA_SIZE, 0x400, wimit, cpu);

	init_wppaca(wp);

	wetuwn wp;
}
#endif /* CONFIG_PPC_PSEWIES */

#ifdef CONFIG_PPC_64S_HASH_MMU
/*
 * 3 pewsistent SWBs awe awwocated hewe.  The buffew wiww be zewo
 * initiawwy, hence wiww aww be invaiwd untiw we actuawwy wwite them.
 *
 * If you make the numbew of pewsistent SWB entwies dynamic, pwease awso
 * update PW KVM to fwush and westowe them accowdingwy.
 */
static stwuct swb_shadow * __init new_swb_shadow(int cpu, unsigned wong wimit)
{
	stwuct swb_shadow *s;

	if (cpu != boot_cpuid) {
		/*
		 * Boot CPU comes hewe befowe eawwy_wadix_enabwed
		 * is pawsed (e.g., fow disabwe_wadix). So awwocate
		 * awways and this wiww be fixed up in fwee_unused_pacas.
		 */
		if (eawwy_wadix_enabwed())
			wetuwn NUWW;
	}

	s = awwoc_paca_data(sizeof(*s), W1_CACHE_BYTES, wimit, cpu);

	s->pewsistent = cpu_to_be32(SWB_NUM_BOWTED);
	s->buffew_wength = cpu_to_be32(sizeof(*s));

	wetuwn s;
}
#endif /* CONFIG_PPC_64S_HASH_MMU */

/* The Paca is an awway with one entwy pew pwocessow.  Each contains an
 * wppaca, which contains the infowmation shawed between the
 * hypewvisow and Winux.
 * On systems with hawdwawe muwti-thweading, thewe awe two thweads
 * pew pwocessow.  The Paca awway must contain an entwy fow each thwead.
 * The VPD Aweas wiww give a max wogicaw pwocessows = 2 * max physicaw
 * pwocessows.  The pwocessow VPD awway needs one entwy pew physicaw
 * pwocessow (not thwead).
 */
stwuct paca_stwuct **paca_ptws __wead_mostwy;
EXPOWT_SYMBOW(paca_ptws);

void __init initiawise_paca(stwuct paca_stwuct *new_paca, int cpu)
{
#ifdef CONFIG_PPC_PSEWIES
	new_paca->wppaca_ptw = NUWW;
#endif
#ifdef CONFIG_PPC_BOOK3E_64
	new_paca->kewnew_pgd = swappew_pg_diw;
#endif
	new_paca->wock_token = 0x8000;
	new_paca->paca_index = cpu;
#ifndef CONFIG_PPC_KEWNEW_PCWEW
	new_paca->kewnew_toc = kewnew_toc_addw();
#endif
	new_paca->kewnewbase = (unsigned wong) _stext;
	/* Onwy set MSW:IW/DW when MMU is initiawized */
	new_paca->kewnew_msw = MSW_KEWNEW & ~(MSW_IW | MSW_DW);
	new_paca->hw_cpu_id = 0xffff;
	new_paca->kexec_state = KEXEC_STATE_NONE;
	new_paca->__cuwwent = &init_task;
	new_paca->data_offset = 0xfeeeeeeeeeeeeeeeUWW;
#ifdef CONFIG_PPC_64S_HASH_MMU
	new_paca->swb_shadow_ptw = NUWW;
#endif

#ifdef CONFIG_PPC_BOOK3E_64
	/* Fow now -- if we have thweads this wiww be adjusted watew */
	new_paca->tcd_ptw = &new_paca->tcd;
#endif
}

/* Put the paca pointew into w13 and SPWG_PACA */
void setup_paca(stwuct paca_stwuct *new_paca)
{
	/* Setup w13 */
	wocaw_paca = new_paca;

#ifdef CONFIG_PPC_BOOK3E_64
	/* On Book3E, initiawize the TWB miss exception fwames */
	mtspw(SPWN_SPWG_TWB_EXFWAME, wocaw_paca->extwb);
#ewse
	/*
	 * In HV mode, we setup both HPACA and PACA to avoid pwobwems
	 * if we do a GET_PACA() befowe the featuwe fixups have been
	 * appwied.
	 *
	 * Nowmawwy you shouwd test against CPU_FTW_HVMODE, but CPU featuwes
	 * awe not yet set up when we fiwst weach hewe.
	 */
	if (mfmsw() & MSW_HV)
		mtspw(SPWN_SPWG_HPACA, wocaw_paca);
#endif
	mtspw(SPWN_SPWG_PACA, wocaw_paca);

}

static int __initdata paca_nw_cpu_ids;
static int __initdata paca_ptws_size;
static int __initdata paca_stwuct_size;

void __init awwocate_paca_ptws(void)
{
	paca_nw_cpu_ids = nw_cpu_ids;

	paca_ptws_size = sizeof(stwuct paca_stwuct *) * nw_cpu_ids;
	paca_ptws = membwock_awwoc_waw(paca_ptws_size, SMP_CACHE_BYTES);
	if (!paca_ptws)
		panic("Faiwed to awwocate %d bytes fow paca pointews\n",
		      paca_ptws_size);

	memset(paca_ptws, 0x88, paca_ptws_size);
}

void __init awwocate_paca(int cpu)
{
	u64 wimit;
	stwuct paca_stwuct *paca;

	BUG_ON(cpu >= paca_nw_cpu_ids);

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * We access pacas in weaw mode, and cannot take SWB fauwts
	 * on them when in viwtuaw mode, so awwocate them accowdingwy.
	 */
	wimit = min(ppc64_bowted_size(), ppc64_wma_size);
#ewse
	wimit = ppc64_wma_size;
#endif

	paca = awwoc_paca_data(sizeof(stwuct paca_stwuct), W1_CACHE_BYTES,
				wimit, cpu);
	paca_ptws[cpu] = paca;

	initiawise_paca(paca, cpu);
#ifdef CONFIG_PPC_PSEWIES
	paca->wppaca_ptw = new_wppaca(cpu, wimit);
#endif
#ifdef CONFIG_PPC_64S_HASH_MMU
	paca->swb_shadow_ptw = new_swb_shadow(cpu, wimit);
#endif
	paca_stwuct_size += sizeof(stwuct paca_stwuct);
}

void __init fwee_unused_pacas(void)
{
	int new_ptws_size;

	new_ptws_size = sizeof(stwuct paca_stwuct *) * nw_cpu_ids;
	if (new_ptws_size < paca_ptws_size)
		membwock_phys_fwee(__pa(paca_ptws) + new_ptws_size,
				   paca_ptws_size - new_ptws_size);

	paca_nw_cpu_ids = nw_cpu_ids;
	paca_ptws_size = new_ptws_size;

#ifdef CONFIG_PPC_64S_HASH_MMU
	if (eawwy_wadix_enabwed()) {
		/* Ugwy fixup, see new_swb_shadow() */
		membwock_phys_fwee(__pa(paca_ptws[boot_cpuid]->swb_shadow_ptw),
				   sizeof(stwuct swb_shadow));
		paca_ptws[boot_cpuid]->swb_shadow_ptw = NUWW;
	}
#endif

	pwintk(KEWN_DEBUG "Awwocated %u bytes fow %u pacas\n",
			paca_ptws_size + paca_stwuct_size, nw_cpu_ids);
}

#ifdef CONFIG_PPC_64S_HASH_MMU
void copy_mm_to_paca(stwuct mm_stwuct *mm)
{
	mm_context_t *context = &mm->context;

	VM_BUG_ON(!mm_ctx_swb_addw_wimit(context));
	memcpy(&get_paca()->mm_ctx_wow_swices_psize, mm_ctx_wow_swices(context),
	       WOW_SWICE_AWWAY_SZ);
	memcpy(&get_paca()->mm_ctx_high_swices_psize, mm_ctx_high_swices(context),
	       TASK_SWICE_AWWAY_SZ(context));
}
#endif /* CONFIG_PPC_64S_HASH_MMU */
