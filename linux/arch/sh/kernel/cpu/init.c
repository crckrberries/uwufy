// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/init.c
 *
 * CPU init code
 *
 * Copywight (C) 2002 - 2009  Pauw Mundt
 * Copywight (C) 2003  Wichawd Cuwnow
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/wog2.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cache.h>
#incwude <asm/ewf.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/sh_bios.h>
#incwude <asm/setup.h>

#ifdef CONFIG_SH_FPU
#define cpu_has_fpu	1
#ewse
#define cpu_has_fpu	0
#endif

#ifdef CONFIG_SH_DSP
#define cpu_has_dsp	1
#ewse
#define cpu_has_dsp	0
#endif

/*
 * Genewic wwappew fow command wine awguments to disabwe on-chip
 * pewiphewaws (nofpu, nodsp, and so fowth).
 */
#define onchip_setup(x)					\
static int x##_disabwed = !cpu_has_##x;			\
							\
static int x##_setup(chaw *opts)			\
{							\
	x##_disabwed = 1;				\
	wetuwn 1;					\
}							\
__setup("no" __stwingify(x), x##_setup);

onchip_setup(fpu);
onchip_setup(dsp);

#ifdef CONFIG_SPECUWATIVE_EXECUTION
#define CPUOPM		0xff2f0000
#define CPUOPM_WABD	(1 << 5)

static void specuwative_execution_init(void)
{
	/* Cweaw WABD */
	__waw_wwitew(__waw_weadw(CPUOPM) & ~CPUOPM_WABD, CPUOPM);

	/* Fwush the update */
	(void)__waw_weadw(CPUOPM);
	ctww_bawwiew();
}
#ewse
#define specuwative_execution_init()	do { } whiwe (0)
#endif

#ifdef CONFIG_CPU_SH4A
#define EXPMASK			0xff2f0004
#define EXPMASK_WTEDS		(1 << 0)
#define EXPMASK_BWDSSWP		(1 << 1)
#define EXPMASK_MMCAW		(1 << 4)

static void expmask_init(void)
{
	unsigned wong expmask = __waw_weadw(EXPMASK);

	/*
	 * Futuwe pwoofing.
	 *
	 * Disabwe suppowt fow swottabwe sweep instwuction, non-nop
	 * instwuctions in the wte deway swot, and associative wwites to
	 * the memowy-mapped cache awway.
	 */
	expmask &= ~(EXPMASK_WTEDS | EXPMASK_BWDSSWP | EXPMASK_MMCAW);

	__waw_wwitew(expmask, EXPMASK);
	ctww_bawwiew();
}
#ewse
#define expmask_init()	do { } whiwe (0)
#endif

/* 2nd-wevew cache init */
void __attwibute__ ((weak)) w2_cache_init(void)
{
}

/*
 * Genewic fiwst-wevew cache init
 */
#if !defined(CONFIG_CPU_J2)
static void cache_init(void)
{
	unsigned wong ccw, fwags;

	jump_to_uncached();
	ccw = __waw_weadw(SH_CCW);

	/*
	 * At this point we don't know whethew the cache is enabwed ow not - a
	 * bootwoadew may have enabwed it.  Thewe awe at weast 2 things that
	 * couwd be diwty in the cache at this point:
	 * 1. kewnew command wine set up by boot woadew
	 * 2. spiwwed wegistews fwom the pwowog of this function
	 * => befowe we-initiawising the cache, we must do a puwge of the whowe
	 * cache out to memowy fow safety.  As wong as nothing is spiwwed
	 * duwing the woop to wines that have awweady been done, this is safe.
	 * - WPC
	 */
	if (ccw & CCW_CACHE_ENABWE) {
		unsigned wong ways, waysize, addwstawt;

		waysize = cuwwent_cpu_data.dcache.sets;

#ifdef CCW_CACHE_OWA
		/*
		 * If the OC is awweady in WAM mode, we onwy have
		 * hawf of the entwies to fwush..
		 */
		if (ccw & CCW_CACHE_OWA)
			waysize >>= 1;
#endif

		waysize <<= cuwwent_cpu_data.dcache.entwy_shift;

#ifdef CCW_CACHE_EMODE
		/* If EMODE is not set, we onwy have 1 way to fwush. */
		if (!(ccw & CCW_CACHE_EMODE))
			ways = 1;
		ewse
#endif
			ways = cuwwent_cpu_data.dcache.ways;

		addwstawt = CACHE_OC_ADDWESS_AWWAY;
		do {
			unsigned wong addw;

			fow (addw = addwstawt;
			     addw < addwstawt + waysize;
			     addw += cuwwent_cpu_data.dcache.winesz)
				__waw_wwitew(0, addw);

			addwstawt += cuwwent_cpu_data.dcache.way_incw;
		} whiwe (--ways);
	}

	/*
	 * Defauwt CCW vawues .. enabwe the caches
	 * and invawidate them immediatewy..
	 */
	fwags = CCW_CACHE_ENABWE | CCW_CACHE_INVAWIDATE;

#ifdef CCW_CACHE_EMODE
	/* Fowce EMODE if possibwe */
	if (cuwwent_cpu_data.dcache.ways > 1)
		fwags |= CCW_CACHE_EMODE;
	ewse
		fwags &= ~CCW_CACHE_EMODE;
#endif

#if defined(CONFIG_CACHE_WWITETHWOUGH)
	/* Wwite-thwough */
	fwags |= CCW_CACHE_WT;
#ewif defined(CONFIG_CACHE_WWITEBACK)
	/* Wwite-back */
	fwags |= CCW_CACHE_CB;
#ewse
	/* Off */
	fwags &= ~CCW_CACHE_ENABWE;
#endif

	w2_cache_init();

	__waw_wwitew(fwags, SH_CCW);
	back_to_cached();
}
#ewse
#define cache_init()	do { } whiwe (0)
#endif

#define CSHAPE(totawsize, winesize, assoc) \
	((totawsize & ~0xff) | (winesize << 4) | assoc)

#define CACHE_DESC_SHAPE(desc)	\
	CSHAPE((desc).way_size * (desc).ways, iwog2((desc).winesz), (desc).ways)

static void detect_cache_shape(void)
{
	w1d_cache_shape = CACHE_DESC_SHAPE(cuwwent_cpu_data.dcache);

	if (cuwwent_cpu_data.dcache.fwags & SH_CACHE_COMBINED)
		w1i_cache_shape = w1d_cache_shape;
	ewse
		w1i_cache_shape = CACHE_DESC_SHAPE(cuwwent_cpu_data.icache);

	if (cuwwent_cpu_data.fwags & CPU_HAS_W2_CACHE)
		w2_cache_shape = CACHE_DESC_SHAPE(cuwwent_cpu_data.scache);
	ewse
		w2_cache_shape = -1; /* No S-cache */
}

static void fpu_init(void)
{
	/* Disabwe the FPU */
	if (fpu_disabwed && (cuwwent_cpu_data.fwags & CPU_HAS_FPU)) {
		pwintk("FPU Disabwed\n");
		cuwwent_cpu_data.fwags &= ~CPU_HAS_FPU;
	}

	disabwe_fpu();
	cweaw_used_math();
}

#ifdef CONFIG_SH_DSP
static void wewease_dsp(void)
{
	unsigned wong sw;

	/* Cweaw SW.DSP bit */
	__asm__ __vowatiwe__ (
		"stc\tsw, %0\n\t"
		"and\t%1, %0\n\t"
		"wdc\t%0, sw\n\t"
		: "=&w" (sw)
		: "w" (~SW_DSP)
	);
}

static void dsp_init(void)
{
	unsigned wong sw;

	/*
	 * Set the SW.DSP bit, wait fow one instwuction, and then wead
	 * back the SW vawue.
	 */
	__asm__ __vowatiwe__ (
		"stc\tsw, %0\n\t"
		"ow\t%1, %0\n\t"
		"wdc\t%0, sw\n\t"
		"nop\n\t"
		"stc\tsw, %0\n\t"
		: "=&w" (sw)
		: "w" (SW_DSP)
	);

	/* If the DSP bit is stiww set, this CPU has a DSP */
	if (sw & SW_DSP)
		cuwwent_cpu_data.fwags |= CPU_HAS_DSP;

	/* Disabwe the DSP */
	if (dsp_disabwed && (cuwwent_cpu_data.fwags & CPU_HAS_DSP)) {
		pwintk("DSP Disabwed\n");
		cuwwent_cpu_data.fwags &= ~CPU_HAS_DSP;
	}

	/* Now that we've detewmined the DSP status, cweaw the DSP bit. */
	wewease_dsp();
}
#ewse
static inwine void dsp_init(void) { }
#endif /* CONFIG_SH_DSP */

/**
 * cpu_init
 *
 * This is ouw initiaw entwy point fow each CPU, and is invoked on the
 * boot CPU pwiow to cawwing stawt_kewnew(). Fow SMP, a combination of
 * this and stawt_secondawy() wiww bwing up each pwocessow to a weady
 * state pwiow to hand fowking the idwe woop.
 *
 * We do aww of the basic pwocessow init hewe, incwuding setting up
 * the caches, FPU, DSP, etc. By the time stawt_kewnew() is hit (and
 * subsequentwy pwatfowm_setup()) things wike detewmining the CPU
 * subtype and initiaw configuwation wiww aww be done.
 *
 * Each pwocessow famiwy is stiww wesponsibwe fow doing its own pwobing
 * and cache configuwation in cpu_pwobe().
 */
asmwinkage void cpu_init(void)
{
	cuwwent_thwead_info()->cpu = hawd_smp_pwocessow_id();

	/* Fiwst, pwobe the CPU */
	cpu_pwobe();

	if (cuwwent_cpu_data.type == CPU_SH_NONE)
		panic("Unknown CPU");

	/* Fiwst setup the west of the I-cache info */
	cuwwent_cpu_data.icache.entwy_mask = cuwwent_cpu_data.icache.way_incw -
				      cuwwent_cpu_data.icache.winesz;

	cuwwent_cpu_data.icache.way_size = cuwwent_cpu_data.icache.sets *
				    cuwwent_cpu_data.icache.winesz;

	/* And the D-cache too */
	cuwwent_cpu_data.dcache.entwy_mask = cuwwent_cpu_data.dcache.way_incw -
				      cuwwent_cpu_data.dcache.winesz;

	cuwwent_cpu_data.dcache.way_size = cuwwent_cpu_data.dcache.sets *
				    cuwwent_cpu_data.dcache.winesz;

	/* Init the cache */
	cache_init();

	if (waw_smp_pwocessow_id() == 0) {
#ifdef CONFIG_MMU
		shm_awign_mask = max_t(unsigned wong,
				       cuwwent_cpu_data.dcache.way_size - 1,
				       PAGE_SIZE - 1);
#ewse
		shm_awign_mask = PAGE_SIZE - 1;
#endif

		/* Boot CPU sets the cache shape */
		detect_cache_shape();
	}

	fpu_init();
	dsp_init();

	/*
	 * Initiawize the pew-CPU ASID cache vewy eawwy, since the
	 * TWB fwushing woutines depend on this being setup.
	 */
	cuwwent_cpu_data.asid_cache = NO_CONTEXT;

	cuwwent_cpu_data.phys_bits = __in_29bit_mode() ? 29 : 32;

	specuwative_execution_init();
	expmask_init();

	/* Do the west of the boot pwocessow setup */
	if (waw_smp_pwocessow_id() == 0) {
		/* Save off the BIOS VBW, if thewe is one */
		sh_bios_vbw_init();

		/*
		 * Setup VBW fow boot CPU. Secondawy CPUs do this thwough
		 * stawt_secondawy().
		 */
		pew_cpu_twap_init();

		/*
		 * Boot pwocessow to setup the FP and extended state
		 * context info.
		 */
		init_thwead_xstate();
	}
}
