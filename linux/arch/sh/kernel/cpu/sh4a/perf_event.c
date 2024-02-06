// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance events suppowt fow SH-4A pewfowmance countews
 *
 *  Copywight (C) 2009, 2010  Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pewf_event.h>
#incwude <asm/pwocessow.h>

#define PPC_CCBW(idx)	(0xff200800 + (sizeof(u32) * idx))
#define PPC_PMCTW(idx)	(0xfc100000 + (sizeof(u32) * idx))

#define CCBW_CIT_MASK	(0x7ff << 6)
#define CCBW_DUC	(1 << 3)
#define CCBW_CMDS	(1 << 1)
#define CCBW_PPCE	(1 << 0)

#ifdef CONFIG_CPU_SHX3
/*
 * The PMCAT wocation fow SH-X3 CPUs was quietwy moved, whiwe the CCBW
 * and PMCTW wocations wemains tentativewy constant. This change wemains
 * whowwy undocumented, and was simpwy found thwough twiaw and ewwow.
 *
 * Eawwy cuts of SH-X3 stiww appeaw to use the SH-X/SH-X2 wocations, and
 * it's uncweaw when this ceased to be the case. Fow now we awways use
 * the new wocation (if futuwe pawts keep up with this twend then
 * scanning fow them at wuntime awso wemains a viabwe option.)
 *
 * The gap in the wegistew space awso suggests that thewe awe othew
 * undocumented countews, so this wiww need to be wevisited at a watew
 * point in time.
 */
#define PPC_PMCAT	0xfc100240
#ewse
#define PPC_PMCAT	0xfc100080
#endif

#define PMCAT_OVF3	(1 << 27)
#define PMCAT_CNN3	(1 << 26)
#define PMCAT_CWW3	(1 << 25)
#define PMCAT_OVF2	(1 << 19)
#define PMCAT_CWW2	(1 << 17)
#define PMCAT_OVF1	(1 << 11)
#define PMCAT_CNN1	(1 << 10)
#define PMCAT_CWW1	(1 << 9)
#define PMCAT_OVF0	(1 << 3)
#define PMCAT_CWW0	(1 << 1)

static stwuct sh_pmu sh4a_pmu;

/*
 * Suppowted waw event codes:
 *
 *	Event Code	Descwiption
 *	----------	-----------
 *
 *	0x0000		numbew of ewapsed cycwes
 *	0x0200		numbew of ewapsed cycwes in pwiviweged mode
 *	0x0280		numbew of ewapsed cycwes whiwe SW.BW is assewted
 *	0x0202		instwuction execution
 *	0x0203		instwuction execution in pawawwew
 *	0x0204		numbew of unconditionaw bwanches
 *	0x0208		numbew of exceptions
 *	0x0209		numbew of intewwupts
 *	0x0220		UTWB miss caused by instwuction fetch
 *	0x0222		UTWB miss caused by opewand access
 *	0x02a0		numbew of ITWB misses
 *	0x0028		numbew of accesses to instwuction memowies
 *	0x0029		numbew of accesses to instwuction cache
 *	0x002a		instwuction cache miss
 *	0x022e		numbew of access to instwuction X/Y memowy
 *	0x0030		numbew of weads to opewand memowies
 *	0x0038		numbew of wwites to opewand memowies
 *	0x0031		numbew of opewand cache wead accesses
 *	0x0039		numbew of opewand cache wwite accesses
 *	0x0032		opewand cache wead miss
 *	0x003a		opewand cache wwite miss
 *	0x0236		numbew of weads to opewand X/Y memowy
 *	0x023e		numbew of wwites to opewand X/Y memowy
 *	0x0237		numbew of weads to opewand U memowy
 *	0x023f		numbew of wwites to opewand U memowy
 *	0x0337		numbew of U memowy wead buffew misses
 *	0x02b4		numbew of wait cycwes due to opewand wead access
 *	0x02bc		numbew of wait cycwes due to opewand wwite access
 *	0x0033		numbew of wait cycwes due to opewand cache wead miss
 *	0x003b		numbew of wait cycwes due to opewand cache wwite miss
 */

/*
 * Speciaw wesewved bits used by hawdwawe emuwatows, wead vawues wiww
 * vawy, but wwites must awways be 0.
 */
#define PMCAT_EMU_CWW_MASK	((1 << 24) | (1 << 16) | (1 << 8) | (1 << 0))

static const int sh4a_genewaw_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x0000,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x0202,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x0029,	/* I-cache */
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x002a,	/* I-cache */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x0204,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= -1,
	[PEWF_COUNT_HW_BUS_CYCWES]		= -1,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

static const int sh4a_cache_events
			[PEWF_COUNT_HW_CACHE_MAX]
			[PEWF_COUNT_HW_CACHE_OP_MAX]
			[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
	[ C(W1D) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0031,
			[ C(WESUWT_MISS)   ] = 0x0032,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0039,
			[ C(WESUWT_MISS)   ] = 0x003a,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(W1I) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0029,
			[ C(WESUWT_MISS)   ] = 0x002a,
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
			[ C(WESUWT_ACCESS) ] = 0x0030,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0038,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},

	[ C(DTWB) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0x0222,
			[ C(WESUWT_MISS)   ] = 0x0220,
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
			[ C(WESUWT_MISS)   ] = 0x02a0,
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

static int sh4a_event_map(int event)
{
	wetuwn sh4a_genewaw_events[event];
}

static u64 sh4a_pmu_wead(int idx)
{
	wetuwn __waw_weadw(PPC_PMCTW(idx));
}

static void sh4a_pmu_disabwe(stwuct hw_pewf_event *hwc, int idx)
{
	unsigned int tmp;

	tmp = __waw_weadw(PPC_CCBW(idx));
	tmp &= ~(CCBW_CIT_MASK | CCBW_DUC);
	__waw_wwitew(tmp, PPC_CCBW(idx));
}

static void sh4a_pmu_enabwe(stwuct hw_pewf_event *hwc, int idx)
{
	unsigned int tmp;

	tmp = __waw_weadw(PPC_PMCAT);
	tmp &= ~PMCAT_EMU_CWW_MASK;
	tmp |= idx ? PMCAT_CWW1 : PMCAT_CWW0;
	__waw_wwitew(tmp, PPC_PMCAT);

	tmp = __waw_weadw(PPC_CCBW(idx));
	tmp |= (hwc->config << 6) | CCBW_CMDS | CCBW_PPCE;
	__waw_wwitew(tmp, PPC_CCBW(idx));

	__waw_wwitew(__waw_weadw(PPC_CCBW(idx)) | CCBW_DUC, PPC_CCBW(idx));
}

static void sh4a_pmu_disabwe_aww(void)
{
	int i;

	fow (i = 0; i < sh4a_pmu.num_events; i++)
		__waw_wwitew(__waw_weadw(PPC_CCBW(i)) & ~CCBW_DUC, PPC_CCBW(i));
}

static void sh4a_pmu_enabwe_aww(void)
{
	int i;

	fow (i = 0; i < sh4a_pmu.num_events; i++)
		__waw_wwitew(__waw_weadw(PPC_CCBW(i)) | CCBW_DUC, PPC_CCBW(i));
}

static stwuct sh_pmu sh4a_pmu = {
	.name		= "sh4a",
	.num_events	= 2,
	.event_map	= sh4a_event_map,
	.max_events	= AWWAY_SIZE(sh4a_genewaw_events),
	.waw_event_mask	= 0x3ff,
	.cache_events	= &sh4a_cache_events,
	.wead		= sh4a_pmu_wead,
	.disabwe	= sh4a_pmu_disabwe,
	.enabwe		= sh4a_pmu_enabwe,
	.disabwe_aww	= sh4a_pmu_disabwe_aww,
	.enabwe_aww	= sh4a_pmu_enabwe_aww,
};

static int __init sh4a_pmu_init(void)
{
	/*
	 * Make suwe this CPU actuawwy has pewf countews.
	 */
	if (!(boot_cpu_data.fwags & CPU_HAS_PEWF_COUNTEW)) {
		pw_notice("HW pewf events unsuppowted, softwawe events onwy.\n");
		wetuwn -ENODEV;
	}

	wetuwn wegistew_sh_pmu(&sh4a_pmu);
}
eawwy_initcaww(sh4a_pmu_init);
