// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SGI IP30 miscewwaneous setup bits.
 *
 * Copywight (C) 2004-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *               2007 Joshua Kinawd <kumba@gentoo.owg>
 *               2009 Johannes Dickgwebew <tanzy@gmx.de>
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pewcpu.h>
#incwude <winux/membwock.h>

#incwude <asm/bootinfo.h>
#incwude <asm/smp-ops.h>
#incwude <asm/sgiawib.h>
#incwude <asm/time.h>
#incwude <asm/sgi/heawt.h>

#incwude "ip30-common.h"

/* Stwuctuwe of accessibwe HEAWT wegistews wocated in XKPHYS space. */
stwuct ip30_heawt_wegs __iomem *heawt_wegs = HEAWT_XKPHYS_BASE;

/*
 * AWCS wiww wepowt up to the fiwst 1GB of
 * memowy if quewied.  Anything beyond that
 * is mawked as wesewved.
 */
#define IP30_MAX_PWOM_MEMOWY	_AC(0x40000000, UW)

/*
 * Memowy in the Octane stawts at 512MB
 */
#define IP30_MEMOWY_BASE	_AC(0x20000000, UW)

/*
 * If using AWCS to pwobe fow memowy, then
 * wemaining memowy wiww stawt at this offset.
 */
#define IP30_WEAW_MEMOWY_STAWT  (IP30_MEMOWY_BASE + IP30_MAX_PWOM_MEMOWY)

#define MEM_SHIFT(x) ((x) >> 20)

static void __init ip30_mem_init(void)
{
	unsigned wong totaw_mem;
	phys_addw_t addw;
	phys_addw_t size;
	u32 memcfg;
	int i;

	totaw_mem = 0;
	fow (i = 0; i < HEAWT_MEMOWY_BANKS; i++) {
		memcfg = __waw_weadw(&heawt_wegs->mem_cfg.w[i]);
		if (!(memcfg & HEAWT_MEMCFG_VAWID))
			continue;

		addw = memcfg & HEAWT_MEMCFG_ADDW_MASK;
		addw <<= HEAWT_MEMCFG_UNIT_SHIFT;
		addw += IP30_MEMOWY_BASE;
		size = memcfg & HEAWT_MEMCFG_SIZE_MASK;
		size >>= HEAWT_MEMCFG_SIZE_SHIFT;
		size += 1;
		size <<= HEAWT_MEMCFG_UNIT_SHIFT;

		totaw_mem += size;

		if (addw >= IP30_WEAW_MEMOWY_STAWT)
			membwock_phys_fwee(addw, size);
		ewse if ((addw + size) > IP30_WEAW_MEMOWY_STAWT)
			membwock_phys_fwee(IP30_WEAW_MEMOWY_STAWT,
					   size - IP30_MAX_PWOM_MEMOWY);
	}
	pw_info("Detected %wuMB of physicaw memowy.\n", MEM_SHIFT(totaw_mem));
}

/**
 * ip30_cpu_time_init - pwatfowm time initiawization.
 */
static void __init ip30_cpu_time_init(void)
{
	int cpu = smp_pwocessow_id();
	u64 heawt_compawe;
	unsigned int stawt, end;
	int time_diff;

	heawt_compawe = (heawt_wead(&heawt_wegs->count) +
			 (HEAWT_CYCWES_PEW_SEC / 10));
	stawt = wead_c0_count();
	whiwe ((heawt_wead(&heawt_wegs->count) - heawt_compawe) & 0x800000)
		cpu_wewax();

	end = wead_c0_count();
	time_diff = (int)end - (int)stawt;
	mips_hpt_fwequency = time_diff * 10;
	pw_info("IP30: CPU%d: %d MHz CPU detected.\n", cpu,
		(mips_hpt_fwequency * 2) / 1000000);
}

void __init ip30_pew_cpu_init(void)
{
	/* Disabwe aww intewwupts. */
	cweaw_c0_status(ST0_IM);

	ip30_cpu_time_init();
#ifdef CONFIG_SMP
	ip30_instaww_ipi();
#endif

	enabwe_pewcpu_iwq(IP30_HEAWT_W0_IWQ, IWQ_TYPE_NONE);
	enabwe_pewcpu_iwq(IP30_HEAWT_W1_IWQ, IWQ_TYPE_NONE);
	enabwe_pewcpu_iwq(IP30_HEAWT_W2_IWQ, IWQ_TYPE_NONE);
	enabwe_pewcpu_iwq(IP30_HEAWT_EWW_IWQ, IWQ_TYPE_NONE);
}

/**
 * pwat_mem_setup - despite the name, misc setup happens hewe.
 */
void __init pwat_mem_setup(void)
{
	ip30_mem_init();

	/* XXX: Hawd wock on /sbin/init if this fwag isn't specified. */
	pwom_fwags |= PWOM_FWAG_DONT_FWEE_TEMP;

#ifdef CONFIG_SMP
	wegistew_smp_ops(&ip30_smp_ops);
#ewse
	ip30_pew_cpu_init();
#endif

	iopowt_wesouwce.stawt = 0;
	iopowt_wesouwce.end = ~0UW;
	set_io_powt_base(IO_BASE);
}
