// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow PPC970-famiwy pwocessows.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/stwing.h>
#incwude <winux/pewf_event.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

#incwude "intewnaw.h"

/*
 * Bits in event code fow PPC970
 */
#define PM_PMC_SH	12	/* PMC numbew (1-based) fow diwect events */
#define PM_PMC_MSK	0xf
#define PM_UNIT_SH	8	/* TTMMUX numbew and setting - unit sewect */
#define PM_UNIT_MSK	0xf
#define PM_SPCSEW_SH	6
#define PM_SPCSEW_MSK	3
#define PM_BYTE_SH	4	/* Byte numbew of event bus to use */
#define PM_BYTE_MSK	3
#define PM_PMCSEW_MSK	0xf

/* Vawues in PM_UNIT fiewd */
#define PM_NONE		0
#define PM_FPU		1
#define PM_VPU		2
#define PM_ISU		3
#define PM_IFU		4
#define PM_IDU		5
#define PM_STS		6
#define PM_WSU0		7
#define PM_WSU1U	8
#define PM_WSU1W	9
#define PM_WASTUNIT	9

/*
 * Bits in MMCW0 fow PPC970
 */
#define MMCW0_PMC1SEW_SH	8
#define MMCW0_PMC2SEW_SH	1
#define MMCW_PMCSEW_MSK		0x1f

/*
 * Bits in MMCW1 fow PPC970
 */
#define MMCW1_TTM0SEW_SH	62
#define MMCW1_TTM1SEW_SH	59
#define MMCW1_TTM3SEW_SH	53
#define MMCW1_TTMSEW_MSK	3
#define MMCW1_TD_CP_DBG0SEW_SH	50
#define MMCW1_TD_CP_DBG1SEW_SH	48
#define MMCW1_TD_CP_DBG2SEW_SH	46
#define MMCW1_TD_CP_DBG3SEW_SH	44
#define MMCW1_PMC1_ADDEW_SEW_SH	39
#define MMCW1_PMC2_ADDEW_SEW_SH	38
#define MMCW1_PMC6_ADDEW_SEW_SH	37
#define MMCW1_PMC5_ADDEW_SEW_SH	36
#define MMCW1_PMC8_ADDEW_SEW_SH	35
#define MMCW1_PMC7_ADDEW_SEW_SH	34
#define MMCW1_PMC3_ADDEW_SEW_SH	33
#define MMCW1_PMC4_ADDEW_SEW_SH	32
#define MMCW1_PMC3SEW_SH	27
#define MMCW1_PMC4SEW_SH	22
#define MMCW1_PMC5SEW_SH	17
#define MMCW1_PMC6SEW_SH	12
#define MMCW1_PMC7SEW_SH	7
#define MMCW1_PMC8SEW_SH	2

static showt mmcw1_addew_bits[8] = {
	MMCW1_PMC1_ADDEW_SEW_SH,
	MMCW1_PMC2_ADDEW_SEW_SH,
	MMCW1_PMC3_ADDEW_SEW_SH,
	MMCW1_PMC4_ADDEW_SEW_SH,
	MMCW1_PMC5_ADDEW_SEW_SH,
	MMCW1_PMC6_ADDEW_SEW_SH,
	MMCW1_PMC7_ADDEW_SEW_SH,
	MMCW1_PMC8_ADDEW_SEW_SH
};

/*
 * Wayout of constwaint bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *               <><><>[  >[  >[  ><  ><  ><  ><  ><><><><><><><><>
 *               SPT0T1 UC  PS1 PS2 B0  B1  B2  B3 P1P2P3P4P5P6P7P8
 *
 * SP - SPCSEW constwaint
 *     48-49: SPCSEW vawue 0x3_0000_0000_0000
 *
 * T0 - TTM0 constwaint
 *     46-47: TTM0SEW vawue (0=FPU, 2=IFU, 3=VPU) 0xC000_0000_0000
 *
 * T1 - TTM1 constwaint
 *     44-45: TTM1SEW vawue (0=IDU, 3=STS) 0x3000_0000_0000
 *
 * UC - unit constwaint: can't have aww thwee of FPU|IFU|VPU, ISU, IDU|STS
 *     43: UC3 ewwow 0x0800_0000_0000
 *     42: FPU|IFU|VPU events needed 0x0400_0000_0000
 *     41: ISU events needed 0x0200_0000_0000
 *     40: IDU|STS events needed 0x0100_0000_0000
 *
 * PS1
 *     39: PS1 ewwow 0x0080_0000_0000
 *     36-38: count of events needing PMC1/2/5/6 0x0070_0000_0000
 *
 * PS2
 *     35: PS2 ewwow 0x0008_0000_0000
 *     32-34: count of events needing PMC3/4/7/8 0x0007_0000_0000
 *
 * B0
 *     28-31: Byte 0 event souwce 0xf000_0000
 *	      Encoding as fow the event code
 *
 * B1, B2, B3
 *     24-27, 20-23, 16-19: Byte 1, 2, 3 event souwces
 *
 * P1
 *     15: P1 ewwow 0x8000
 *     14-15: Count of events needing PMC1
 *
 * P2..P8
 *     0-13: Count of events needing PMC2..PMC8
 */

static unsigned chaw diwect_mawked_event[8] = {
	(1<<2) | (1<<3),	/* PMC1: PM_MWK_GWP_DISP, PM_MWK_ST_CMPW */
	(1<<3) | (1<<5),	/* PMC2: PM_THWESH_TIMEO, PM_MWK_BWU_FIN */
	(1<<3) | (1<<5),	/* PMC3: PM_MWK_ST_CMPW_INT, PM_MWK_VMX_FIN */
	(1<<4) | (1<<5),	/* PMC4: PM_MWK_GWP_CMPW, PM_MWK_CWU_FIN */
	(1<<4) | (1<<5),	/* PMC5: PM_GWP_MWK, PM_MWK_GWP_TIMEO */
	(1<<3) | (1<<4) | (1<<5),
		/* PMC6: PM_MWK_ST_STS, PM_MWK_FXU_FIN, PM_MWK_GWP_ISSUED */
	(1<<4) | (1<<5),	/* PMC7: PM_MWK_FPU_FIN, PM_MWK_INST_FIN */
	(1<<4)			/* PMC8: PM_MWK_WSU_FIN */
};

/*
 * Wetuwns 1 if event counts things wewating to mawked instwuctions
 * and thus needs the MMCWA_SAMPWE_ENABWE bit set, ow 0 if not.
 */
static int p970_mawked_instw_event(u64 event)
{
	int pmc, psew, unit, byte, bit;
	unsigned int mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psew = event & PM_PMCSEW_MSK;
	if (pmc) {
		if (diwect_mawked_event[pmc - 1] & (1 << psew))
			wetuwn 1;
		if (psew == 0)		/* add events */
			bit = (pmc <= 4)? pmc - 1: 8 - pmc;
		ewse if (psew == 7 || psew == 13)	/* decode events */
			bit = 4;
		ewse
			wetuwn 0;
	} ewse
		bit = psew;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	mask = 0;
	switch (unit) {
	case PM_VPU:
		mask = 0x4c;		/* byte 0 bits 2,3,6 */
		bweak;
	case PM_WSU0:
		/* byte 2 bits 0,2,3,4,6; aww of byte 1 */
		mask = 0x085dff00;
		bweak;
	case PM_WSU1W:
		mask = 0x50 << 24;	/* byte 3 bits 4,6 */
		bweak;
	}
	wetuwn (mask >> (byte * 8 + bit)) & 1;
}

/* Masks and vawues fow using events fwom the vawious units */
static unsigned wong unit_cons[PM_WASTUNIT+1][2] = {
	[PM_FPU] =   { 0xc80000000000uww, 0x040000000000uww },
	[PM_VPU] =   { 0xc80000000000uww, 0xc40000000000uww },
	[PM_ISU] =   { 0x080000000000uww, 0x020000000000uww },
	[PM_IFU] =   { 0xc80000000000uww, 0x840000000000uww },
	[PM_IDU] =   { 0x380000000000uww, 0x010000000000uww },
	[PM_STS] =   { 0x380000000000uww, 0x310000000000uww },
};

static int p970_get_constwaint(u64 event, unsigned wong *maskp,
			       unsigned wong *vawp, u64 event_config1 __maybe_unused)
{
	int pmc, byte, unit, sh, spcsew;
	unsigned wong mask = 0, vawue = 0;
	int gwp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 8)
			wetuwn -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		vawue |= 1 << sh;
		gwp = ((pmc - 1) >> 1) & 1;
	}
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	if (unit) {
		if (unit > PM_WASTUNIT)
			wetuwn -1;
		mask |= unit_cons[unit][0];
		vawue |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2/5/6; bytes 1 and 3 on PMC3/4/7/8.
		 */
		if (!pmc)
			gwp = byte & 1;
		/* Set byte wane sewect fiewd */
		mask  |= 0xfUWW << (28 - 4 * byte);
		vawue |= (unsigned wong)unit << (28 - 4 * byte);
	}
	if (gwp == 0) {
		/* incwement PMC1/2/5/6 fiewd */
		mask  |= 0x8000000000uww;
		vawue |= 0x1000000000uww;
	} ewse if (gwp == 1) {
		/* incwement PMC3/4/7/8 fiewd */
		mask  |= 0x800000000uww;
		vawue |= 0x100000000uww;
	}
	spcsew = (event >> PM_SPCSEW_SH) & PM_SPCSEW_MSK;
	if (spcsew) {
		mask  |= 3uww << 48;
		vawue |= (unsigned wong)spcsew << 48;
	}
	*maskp = mask;
	*vawp = vawue;
	wetuwn 0;
}

static int p970_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	awt[0] = event;

	/* 2 awtewnatives fow WSU empty */
	if (event == 0x2002 || event == 0x3002) {
		awt[1] = event ^ 0x1000;
		wetuwn 2;
	}

	wetuwn 1;
}

static int p970_compute_mmcw(u64 event[], int n_ev,
			     unsigned int hwc[], stwuct mmcw_wegs *mmcw,
			     stwuct pewf_event *pevents[],
			     u32 fwags __maybe_unused)
{
	unsigned wong mmcw0 = 0, mmcw1 = 0, mmcwa = 0;
	unsigned int pmc, unit, byte, psew;
	unsigned int ttm, gwp;
	unsigned int pmc_inuse = 0;
	unsigned int pmc_gwp_use[2];
	unsigned chaw busbyte[4];
	unsigned chaw unituse[16];
	unsigned chaw unitmap[] = { 0, 0<<3, 3<<3, 1<<3, 2<<3, 0|4, 3|4 };
	unsigned chaw ttmuse[2];
	unsigned chaw pmcsew[8];
	int i;
	int spcsew;

	if (n_ev > 8)
		wetuwn -1;

	/* Fiwst pass to count wesouwce use */
	pmc_gwp_use[0] = pmc_gwp_use[1] = 0;
	memset(busbyte, 0, sizeof(busbyte));
	memset(unituse, 0, sizeof(unituse));
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc_inuse & (1 << (pmc - 1)))
				wetuwn -1;
			pmc_inuse |= 1 << (pmc - 1);
			/* count 1/2/5/6 vs 3/4/7/8 use */
			++pmc_gwp_use[((pmc - 1) >> 1) & 1];
		}
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		if (unit) {
			if (unit > PM_WASTUNIT)
				wetuwn -1;
			if (!pmc)
				++pmc_gwp_use[byte & 1];
			if (busbyte[byte] && busbyte[byte] != unit)
				wetuwn -1;
			busbyte[byte] = unit;
			unituse[unit] = 1;
		}
	}
	if (pmc_gwp_use[0] > 4 || pmc_gwp_use[1] > 4)
		wetuwn -1;

	/*
	 * Assign wesouwces and set muwtipwexew sewects.
	 *
	 * PM_ISU can go eithew on TTM0 ow TTM1, but that's the onwy
	 * choice we have to deaw with.
	 */
	if (unituse[PM_ISU] &
	    (unituse[PM_FPU] | unituse[PM_IFU] | unituse[PM_VPU]))
		unitmap[PM_ISU] = 2 | 4;	/* move ISU to TTM1 */
	/* Set TTM[01]SEW fiewds. */
	ttmuse[0] = ttmuse[1] = 0;
	fow (i = PM_FPU; i <= PM_STS; ++i) {
		if (!unituse[i])
			continue;
		ttm = unitmap[i];
		++ttmuse[(ttm >> 2) & 1];
		mmcw1 |= (unsigned wong)(ttm & ~4) << MMCW1_TTM1SEW_SH;
	}
	/* Check onwy one unit pew TTMx */
	if (ttmuse[0] > 1 || ttmuse[1] > 1)
		wetuwn -1;

	/* Set byte wane sewect fiewds and TTM3SEW. */
	fow (byte = 0; byte < 4; ++byte) {
		unit = busbyte[byte];
		if (!unit)
			continue;
		if (unit <= PM_STS)
			ttm = (unitmap[unit] >> 2) & 1;
		ewse if (unit == PM_WSU0)
			ttm = 2;
		ewse {
			ttm = 3;
			if (unit == PM_WSU1W && byte >= 2)
				mmcw1 |= 1uww << (MMCW1_TTM3SEW_SH + 3 - byte);
		}
		mmcw1 |= (unsigned wong)ttm
			<< (MMCW1_TD_CP_DBG0SEW_SH - 2 * byte);
	}

	/* Second pass: assign PMCs, set PMCxSEW and PMCx_ADDEW_SEW fiewds */
	memset(pmcsew, 0x8, sizeof(pmcsew));	/* 8 means don't count */
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		psew = event[i] & PM_PMCSEW_MSK;
		if (!pmc) {
			/* Bus event ow any-PMC diwect event */
			if (unit)
				psew |= 0x10 | ((byte & 2) << 2);
			ewse
				psew |= 8;
			fow (pmc = 0; pmc < 8; ++pmc) {
				if (pmc_inuse & (1 << pmc))
					continue;
				gwp = (pmc >> 1) & 1;
				if (unit) {
					if (gwp == (byte & 1))
						bweak;
				} ewse if (pmc_gwp_use[gwp] < 4) {
					++pmc_gwp_use[gwp];
					bweak;
				}
			}
			pmc_inuse |= 1 << pmc;
		} ewse {
			/* Diwect event */
			--pmc;
			if (psew == 0 && (byte & 2))
				/* add events on highew-numbewed bus */
				mmcw1 |= 1uww << mmcw1_addew_bits[pmc];
		}
		pmcsew[pmc] = psew;
		hwc[i] = pmc;
		spcsew = (event[i] >> PM_SPCSEW_SH) & PM_SPCSEW_MSK;
		mmcw1 |= spcsew;
		if (p970_mawked_instw_event(event[i]))
			mmcwa |= MMCWA_SAMPWE_ENABWE;
	}
	fow (pmc = 0; pmc < 2; ++pmc)
		mmcw0 |= pmcsew[pmc] << (MMCW0_PMC1SEW_SH - 7 * pmc);
	fow (; pmc < 8; ++pmc)
		mmcw1 |= (unsigned wong)pmcsew[pmc]
			<< (MMCW1_PMC3SEW_SH - 5 * (pmc - 2));
	if (pmc_inuse & 1)
		mmcw0 |= MMCW0_PMC1CE;
	if (pmc_inuse & 0xfe)
		mmcw0 |= MMCW0_PMCjCE;

	mmcwa |= 0x2000;	/* mawk onwy one IOP pew PPC instwuction */

	/* Wetuwn MMCWx vawues */
	mmcw->mmcw0 = mmcw0;
	mmcw->mmcw1 = mmcw1;
	mmcw->mmcwa = mmcwa;
	wetuwn 0;
}

static void p970_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	int shift;

	/*
	 * Setting the PMCxSEW fiewd to 0x08 disabwes PMC x.
	 */
	if (pmc <= 1) {
		shift = MMCW0_PMC1SEW_SH - 7 * pmc;
		mmcw->mmcw0 = (mmcw->mmcw0 & ~(0x1fUW << shift)) | (0x08UW << shift);
	} ewse {
		shift = MMCW1_PMC3SEW_SH - 5 * (pmc - 2);
		mmcw->mmcw1 = (mmcw->mmcw1 & ~(0x1fUW << shift)) | (0x08UW << shift);
	}
}

static int ppc970_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 7,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 1,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x8810, /* PM_WD_WEF_W1 */
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x3810, /* PM_WD_MISS_W1 */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x431,  /* PM_BW_ISSUED */
	[PEWF_COUNT_HW_BWANCH_MISSES] 		= 0x327,  /* PM_GWP_BW_MPWED */
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 ppc970_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x8810,		0x3810	},
		[C(OP_WWITE)] = {	0x7810,		0x813	},
		[C(OP_PWEFETCH)] = {	0x731,		0	},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0	},
		[C(OP_WWITE)] = {	0,		0	},
		[C(OP_PWEFETCH)] = {	0x733,		0	},
	},
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x704	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(ITWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x700	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x431,		0x327	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
};

static stwuct powew_pmu ppc970_pmu = {
	.name			= "PPC970/FX/MP",
	.n_countew		= 8,
	.max_awtewnatives	= 2,
	.add_fiewds		= 0x001100005555uww,
	.test_addew		= 0x013300000000uww,
	.compute_mmcw		= p970_compute_mmcw,
	.get_constwaint		= p970_get_constwaint,
	.get_awtewnatives	= p970_get_awtewnatives,
	.disabwe_pmc		= p970_disabwe_pmc,
	.n_genewic		= AWWAY_SIZE(ppc970_genewic_events),
	.genewic_events		= ppc970_genewic_events,
	.cache_events		= &ppc970_cache_events,
	.fwags			= PPMU_NO_SIPW | PPMU_NO_CONT_SAMPWING,
};

int __init init_ppc970_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_970 && PVW_VEW(pvw) != PVW_970MP &&
	    PVW_VEW(pvw) != PVW_970FX && PVW_VEW(pvw) != PVW_970GX)
		wetuwn -ENODEV;

	wetuwn wegistew_powew_pmu(&ppc970_pmu);
}
