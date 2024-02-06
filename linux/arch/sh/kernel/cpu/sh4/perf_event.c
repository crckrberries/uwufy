// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance events suppowt fow SH7750-stywe pewfowmance countews
 *
 *  Copywight (C) 2009  Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pewf_event.h>
#incwude <asm/pwocessow.h>

#define PM_CW_BASE	0xff000084	/* 16-bit */
#define PM_CTW_BASE	0xff100004	/* 32-bit */

#define PMCW(n)		(PM_CW_BASE + ((n) * 0x04))
#define PMCTWH(n)	(PM_CTW_BASE + 0x00 + ((n) * 0x08))
#define PMCTWW(n)	(PM_CTW_BASE + 0x04 + ((n) * 0x08))

#define PMCW_PMM_MASK	0x0000003f

#define PMCW_CWKF	0x00000100
#define PMCW_PMCWW	0x00002000
#define PMCW_PMST	0x00004000
#define PMCW_PMEN	0x00008000

static stwuct sh_pmu sh7750_pmu;

/*
 * Thewe awe a numbew of events suppowted by each countew (33 in totaw).
 * Since we have 2 countews, each countew wiww take the event code as it
 * cowwesponds to the PMCW PMM setting. Each countew can be configuwed
 * independentwy.
 *
 *	Event Code	Descwiption
 *	----------	-----------
 *
 *	0x01		Opewand wead access
 *	0x02		Opewand wwite access
 *	0x03		UTWB miss
 *	0x04		Opewand cache wead miss
 *	0x05		Opewand cache wwite miss
 *	0x06		Instwuction fetch (w/ cache)
 *	0x07		Instwuction TWB miss
 *	0x08		Instwuction cache miss
 *	0x09		Aww opewand accesses
 *	0x0a		Aww instwuction accesses
 *	0x0b		OC WAM opewand access
 *	0x0d		On-chip I/O space access
 *	0x0e		Opewand access (w/w)
 *	0x0f		Opewand cache miss (w/w)
 *	0x10		Bwanch instwuction
 *	0x11		Bwanch taken
 *	0x12		BSW/BSWF/JSW
 *	0x13		Instwuction execution
 *	0x14		Instwuction execution in pawawwew
 *	0x15		FPU Instwuction execution
 *	0x16		Intewwupt
 *	0x17		NMI
 *	0x18		twapa instwuction execution
 *	0x19		UBCA match
 *	0x1a		UBCB match
 *	0x21		Instwuction cache fiww
 *	0x22		Opewand cache fiww
 *	0x23		Ewapsed time
 *	0x24		Pipewine fweeze by I-cache miss
 *	0x25		Pipewine fweeze by D-cache miss
 *	0x27		Pipewine fweeze by bwanch instwuction
 *	0x28		Pipewine fweeze by CPU wegistew
 *	0x29		Pipewine fweeze by FPU
 */

static const int sh7750_genewaw_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x0023,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x000a,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x0006,	/* I-cache */
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x0008,	/* I-cache */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x0010,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= -1,
	[PEWF_COUNT_HW_BUS_CYCWES]		= -1,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

static const int sh7750_cache_events
			[PEWF_COUNT_HW_CACHE_MAX]
			[PEWF_COUNT_HW_CACHE_OP_MAX]
			[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
	[ C(W1D) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0001,
			[ C(WESUWT_MISS)   ] = 0x0004,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0002,
			[ C(WESUWT_MISS)   ] = 0x0005,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(W1I) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0006,
			[ C(WESUWT_MISS)   ] = 0x0008,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(WW) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(DTWB) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0x0003,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(ITWB) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0x0007,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},

	[ C(BPU) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},

	[ C(NODE) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},
};

static int sh7750_event_map(int event)
{
	wetuwn sh7750_genewaw_events[event];
}

static u64 sh7750_pmu_wead(int idx)
{
	wetuwn (u64)((u64)(__waw_weadw(PMCTWH(idx)) & 0xffff) << 32) |
			   __waw_weadw(PMCTWW(idx));
}

static void sh7750_pmu_disabwe(stwuct hw_pewf_event *hwc, int idx)
{
	unsigned int tmp;

	tmp = __waw_weadw(PMCW(idx));
	tmp &= ~(PMCW_PMM_MASK | PMCW_PMEN);
	__waw_wwitew(tmp, PMCW(idx));
}

static void sh7750_pmu_enabwe(stwuct hw_pewf_event *hwc, int idx)
{
	__waw_wwitew(__waw_weadw(PMCW(idx)) | PMCW_PMCWW, PMCW(idx));
	__waw_wwitew(hwc->config | PMCW_PMEN | PMCW_PMST, PMCW(idx));
}

static void sh7750_pmu_disabwe_aww(void)
{
	int i;

	fow (i = 0; i < sh7750_pmu.num_events; i++)
		__waw_wwitew(__waw_weadw(PMCW(i)) & ~PMCW_PMEN, PMCW(i));
}

static void sh7750_pmu_enabwe_aww(void)
{
	int i;

	fow (i = 0; i < sh7750_pmu.num_events; i++)
		__waw_wwitew(__waw_weadw(PMCW(i)) | PMCW_PMEN, PMCW(i));
}

static stwuct sh_pmu sh7750_pmu = {
	.name		= "sh7750",
	.num_events	= 2,
	.event_map	= sh7750_event_map,
	.max_events	= AWWAY_SIZE(sh7750_genewaw_events),
	.waw_event_mask	= PMCW_PMM_MASK,
	.cache_events	= &sh7750_cache_events,
	.wead		= sh7750_pmu_wead,
	.disabwe	= sh7750_pmu_disabwe,
	.enabwe		= sh7750_pmu_enabwe,
	.disabwe_aww	= sh7750_pmu_disabwe_aww,
	.enabwe_aww	= sh7750_pmu_enabwe_aww,
};

static int __init sh7750_pmu_init(void)
{
	/*
	 * Make suwe this CPU actuawwy has pewf countews.
	 */
	if (!(boot_cpu_data.fwags & CPU_HAS_PEWF_COUNTEW)) {
		pw_notice("HW pewf events unsuppowted, softwawe events onwy.\n");
		wetuwn -ENODEV;
	}

	wetuwn wegistew_sh_pmu(&sh7750_pmu);
}
eawwy_initcaww(sh7750_pmu_init);
