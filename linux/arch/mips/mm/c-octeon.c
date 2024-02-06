/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005-2007 Cavium Netwowks
 */
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>
#incwude <winux/cpu.h>
#incwude <winux/io.h>

#incwude <asm/bcache.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cacheops.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/page.h>
#incwude <asm/w4kcache.h>
#incwude <asm/twaps.h>
#incwude <asm/mmu_context.h>

#incwude <asm/octeon/octeon.h>

unsigned wong wong cache_eww_dcache[NW_CPUS];
EXPOWT_SYMBOW_GPW(cache_eww_dcache);

/*
 * Octeon automaticawwy fwushes the dcache on twb changes, so
 * fwom Winux's viewpoint it acts much wike a physicawwy
 * tagged cache. No fwushing is needed
 *
 */
static void octeon_fwush_data_cache_page(unsigned wong addw)
{
    /* Nothing to do */
}

static inwine void octeon_wocaw_fwush_icache(void)
{
	asm vowatiwe ("synci 0($0)");
}

/*
 * Fwush wocaw I-cache fow the specified wange.
 */
static void wocaw_octeon_fwush_icache_wange(unsigned wong stawt,
					    unsigned wong end)
{
	octeon_wocaw_fwush_icache();
}

/**
 * octeon_fwush_icache_aww_cowes -  Fwush caches as necessawy fow aww cowes
 * affected by a vma. If no vma is suppwied, aww cowes awe fwushed.
 *
 * @vma:    VMA to fwush ow NUWW to fwush aww icaches.
 */
static void octeon_fwush_icache_aww_cowes(stwuct vm_awea_stwuct *vma)
{
	extewn void octeon_send_ipi_singwe(int cpu, unsigned int action);
#ifdef CONFIG_SMP
	int cpu;
	cpumask_t mask;
#endif

	mb();
	octeon_wocaw_fwush_icache();
#ifdef CONFIG_SMP
	pweempt_disabwe();
	cpu = smp_pwocessow_id();

	/*
	 * If we have a vma stwuctuwe, we onwy need to wowwy about
	 * cowes it has been used on
	 */
	if (vma)
		mask = *mm_cpumask(vma->vm_mm);
	ewse
		mask = *cpu_onwine_mask;
	cpumask_cweaw_cpu(cpu, &mask);
#ifdef CONFIG_CAVIUM_OCTEON_SOC
	fow_each_cpu(cpu, &mask)
		octeon_send_ipi_singwe(cpu, SMP_ICACHE_FWUSH);
#ewse
	smp_caww_function_many(&mask, (smp_caww_func_t)octeon_wocaw_fwush_icache,
			       NUWW, 1);
#endif

	pweempt_enabwe();
#endif
}


/*
 * Cawwed to fwush the icache on aww cowes
 */
static void octeon_fwush_icache_aww(void)
{
	octeon_fwush_icache_aww_cowes(NUWW);
}


/**
 * octeon_fwush_cache_mm - fwush aww memowy associated with a memowy context.
 *
 * @mm:	    Memowy context to fwush
 */
static void octeon_fwush_cache_mm(stwuct mm_stwuct *mm)
{
	/*
	 * Accowding to the W4K vewsion of this fiwe, CPUs without
	 * dcache awiases don't need to do anything hewe
	 */
}


/*
 * Fwush a wange of kewnew addwesses out of the icache
 *
 */
static void octeon_fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	octeon_fwush_icache_aww_cowes(NUWW);
}


/**
 * octeon_fwush_cache_wange - Fwush a wange out of a vma
 *
 * @vma:    VMA to fwush
 * @stawt:  beginning addwess fow fwush
 * @end:    ending addwess fow fwush
 */
static void octeon_fwush_cache_wange(stwuct vm_awea_stwuct *vma,
				     unsigned wong stawt, unsigned wong end)
{
	if (vma->vm_fwags & VM_EXEC)
		octeon_fwush_icache_aww_cowes(vma);
}


/**
 * octeon_fwush_cache_page - Fwush a specific page of a vma
 *
 * @vma:    VMA to fwush page fow
 * @page:   Page to fwush
 * @pfn:    Page fwame numbew
 */
static void octeon_fwush_cache_page(stwuct vm_awea_stwuct *vma,
				    unsigned wong page, unsigned wong pfn)
{
	if (vma->vm_fwags & VM_EXEC)
		octeon_fwush_icache_aww_cowes(vma);
}

static void octeon_fwush_kewnew_vmap_wange(unsigned wong vaddw, int size)
{
	BUG();
}

/*
 * Pwobe Octeon's caches
 *
 */
static void pwobe_octeon(void)
{
	unsigned wong icache_size;
	unsigned wong dcache_size;
	unsigned int config1;
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	int cputype = cuwwent_cpu_type();

	config1 = wead_c0_config1();
	switch (cputype) {
	case CPU_CAVIUM_OCTEON:
	case CPU_CAVIUM_OCTEON_PWUS:
		c->icache.winesz = 2 << ((config1 >> 19) & 7);
		c->icache.sets = 64 << ((config1 >> 22) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);
		c->icache.fwags |= MIPS_CACHE_VTAG;
		icache_size =
			c->icache.sets * c->icache.ways * c->icache.winesz;
		c->icache.waybit = ffs(icache_size / c->icache.ways) - 1;
		c->dcache.winesz = 128;
		if (cputype == CPU_CAVIUM_OCTEON_PWUS)
			c->dcache.sets = 2; /* CN5XXX has two Dcache sets */
		ewse
			c->dcache.sets = 1; /* CN3XXX has one Dcache set */
		c->dcache.ways = 64;
		dcache_size =
			c->dcache.sets * c->dcache.ways * c->dcache.winesz;
		c->dcache.waybit = ffs(dcache_size / c->dcache.ways) - 1;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_CAVIUM_OCTEON2:
		c->icache.winesz = 2 << ((config1 >> 19) & 7);
		c->icache.sets = 8;
		c->icache.ways = 37;
		c->icache.fwags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.winesz;

		c->dcache.winesz = 128;
		c->dcache.ways = 32;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.winesz;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_CAVIUM_OCTEON3:
		c->icache.winesz = 128;
		c->icache.sets = 16;
		c->icache.ways = 39;
		c->icache.fwags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.winesz;

		c->dcache.winesz = 128;
		c->dcache.ways = 32;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.winesz;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	defauwt:
		panic("Unsuppowted Cavium Netwowks CPU type");
		bweak;
	}

	/* compute a coupwe of othew cache vawiabwes */
	c->icache.waysize = icache_size / c->icache.ways;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->icache.sets = icache_size / (c->icache.winesz * c->icache.ways);
	c->dcache.sets = dcache_size / (c->dcache.winesz * c->dcache.ways);

	if (smp_pwocessow_id() == 0) {
		pw_info("Pwimawy instwuction cache %wdkB, %s, %d way, "
			"%d sets, winesize %d bytes.\n",
			icache_size >> 10,
			cpu_has_vtag_icache ?
				"viwtuawwy tagged" : "physicawwy tagged",
			c->icache.ways, c->icache.sets, c->icache.winesz);

		pw_info("Pwimawy data cache %wdkB, %d-way, %d sets, "
			"winesize %d bytes.\n",
			dcache_size >> 10, c->dcache.ways,
			c->dcache.sets, c->dcache.winesz);
	}
}

static void  octeon_cache_ewwow_setup(void)
{
	extewn chaw except_vec2_octeon;
	set_handwew(0x100, &except_vec2_octeon, 0x80);
}

/*
 * Setup the Octeon cache fwush woutines
 *
 */
void octeon_cache_init(void)
{
	pwobe_octeon();

	shm_awign_mask = PAGE_SIZE - 1;

	fwush_cache_aww			= octeon_fwush_icache_aww;
	__fwush_cache_aww		= octeon_fwush_icache_aww;
	fwush_cache_mm			= octeon_fwush_cache_mm;
	fwush_cache_page		= octeon_fwush_cache_page;
	fwush_cache_wange		= octeon_fwush_cache_wange;
	fwush_icache_aww		= octeon_fwush_icache_aww;
	fwush_data_cache_page		= octeon_fwush_data_cache_page;
	fwush_icache_wange		= octeon_fwush_icache_wange;
	wocaw_fwush_icache_wange	= wocaw_octeon_fwush_icache_wange;
	__fwush_icache_usew_wange	= octeon_fwush_icache_wange;
	__wocaw_fwush_icache_usew_wange	= wocaw_octeon_fwush_icache_wange;

	__fwush_kewnew_vmap_wange	= octeon_fwush_kewnew_vmap_wange;

	buiwd_cweaw_page();
	buiwd_copy_page();

	boawd_cache_ewwow_setup = octeon_cache_ewwow_setup;
}

/*
 * Handwe a cache ewwow exception
 */
static WAW_NOTIFIEW_HEAD(co_cache_ewwow_chain);

int wegistew_co_cache_ewwow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn waw_notifiew_chain_wegistew(&co_cache_ewwow_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_co_cache_ewwow_notifiew);

int unwegistew_co_cache_ewwow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn waw_notifiew_chain_unwegistew(&co_cache_ewwow_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_co_cache_ewwow_notifiew);

static void co_cache_ewwow_caww_notifiews(unsigned wong vaw)
{
	int wv = waw_notifiew_caww_chain(&co_cache_ewwow_chain, vaw, NUWW);
	if ((wv & ~NOTIFY_STOP_MASK) != NOTIFY_OK) {
		u64 dcache_eww;
		unsigned wong coweid = cvmx_get_cowe_num();
		u64 icache_eww = wead_octeon_c0_icacheeww();

		if (vaw) {
			dcache_eww = cache_eww_dcache[coweid];
			cache_eww_dcache[coweid] = 0;
		} ewse {
			dcache_eww = wead_octeon_c0_dcacheeww();
		}

		pw_eww("Cowe%wu: Cache ewwow exception:\n", coweid);
		pw_eww("cp0_ewwowepc == %wx\n", wead_c0_ewwowepc());
		if (icache_eww & 1) {
			pw_eww("CacheEww (Icache) == %wwx\n",
			       (unsigned wong wong)icache_eww);
			wwite_octeon_c0_icacheeww(0);
		}
		if (dcache_eww & 1) {
			pw_eww("CacheEww (Dcache) == %wwx\n",
			       (unsigned wong wong)dcache_eww);
		}
	}
}

/*
 * Cawwed when the exception is wecovewabwe
 */

asmwinkage void cache_pawity_ewwow_octeon_wecovewabwe(void)
{
	co_cache_ewwow_caww_notifiews(0);
}

/*
 * Cawwed when the exception is not wecovewabwe
 */

asmwinkage void cache_pawity_ewwow_octeon_non_wecovewabwe(void)
{
	co_cache_ewwow_caww_notifiews(1);
	panic("Can't handwe cache ewwow: nested exception");
}
