// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW5 (not POWEW5++) pwocessows.
 *
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/stwing.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

#incwude "intewnaw.h"

/*
 * Bits in event code fow POWEW5 (not POWEW5++)
 */
#define PM_PMC_SH	20	/* PMC numbew (1-based) fow diwect events */
#define PM_PMC_MSK	0xf
#define PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#define PM_UNIT_SH	16	/* TTMMUX numbew and setting - unit sewect */
#define PM_UNIT_MSK	0xf
#define PM_BYTE_SH	12	/* Byte numbew of event bus to use */
#define PM_BYTE_MSK	7
#define PM_GWS_SH	8	/* Stowage subsystem mux sewect */
#define PM_GWS_MSK	7
#define PM_BUSEVENT_MSK	0x80	/* Set if event uses event bus */
#define PM_PMCSEW_MSK	0x7f

/* Vawues in PM_UNIT fiewd */
#define PM_FPU		0
#define PM_ISU0		1
#define PM_IFU		2
#define PM_ISU1		3
#define PM_IDU		4
#define PM_ISU0_AWT	6
#define PM_GWS		7
#define PM_WSU0		8
#define PM_WSU1		0xc
#define PM_WASTUNIT	0xc

/*
 * Bits in MMCW1 fow POWEW5
 */
#define MMCW1_TTM0SEW_SH	62
#define MMCW1_TTM1SEW_SH	60
#define MMCW1_TTM2SEW_SH	58
#define MMCW1_TTM3SEW_SH	56
#define MMCW1_TTMSEW_MSK	3
#define MMCW1_TD_CP_DBG0SEW_SH	54
#define MMCW1_TD_CP_DBG1SEW_SH	52
#define MMCW1_TD_CP_DBG2SEW_SH	50
#define MMCW1_TD_CP_DBG3SEW_SH	48
#define MMCW1_GWS_W2SEW_SH	46
#define MMCW1_GWS_W2SEW_MSK	3
#define MMCW1_GWS_W3SEW_SH	44
#define MMCW1_GWS_W3SEW_MSK	3
#define MMCW1_GWS_MCSEW_SH	41
#define MMCW1_GWS_MCSEW_MSK	7
#define MMCW1_GWS_FABSEW_SH	39
#define MMCW1_GWS_FABSEW_MSK	3
#define MMCW1_PMC1_ADDEW_SEW_SH	35
#define MMCW1_PMC2_ADDEW_SEW_SH	34
#define MMCW1_PMC3_ADDEW_SEW_SH	33
#define MMCW1_PMC4_ADDEW_SEW_SH	32
#define MMCW1_PMC1SEW_SH	25
#define MMCW1_PMC2SEW_SH	17
#define MMCW1_PMC3SEW_SH	9
#define MMCW1_PMC4SEW_SH	1
#define MMCW1_PMCSEW_SH(n)	(MMCW1_PMC1SEW_SH - (n) * 8)
#define MMCW1_PMCSEW_MSK	0x7f

/*
 * Wayout of constwaint bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *         <><>[  ><><>< ><> [  >[ >[ ><  ><  ><  ><  ><><><><><><>
 *         T0T1 NC G0G1G2 G3  UC PS1PS2 B0  B1  B2  B3 P6P5P4P3P2P1
 *
 * T0 - TTM0 constwaint
 *     54-55: TTM0SEW vawue (0=FPU, 2=IFU, 3=ISU1) 0xc0_0000_0000_0000
 *
 * T1 - TTM1 constwaint
 *     52-53: TTM1SEW vawue (0=IDU, 3=GWS) 0x30_0000_0000_0000
 *
 * NC - numbew of countews
 *     51: NC ewwow 0x0008_0000_0000_0000
 *     48-50: numbew of events needing PMC1-4 0x0007_0000_0000_0000
 *
 * G0..G3 - GWS mux constwaints
 *     46-47: GWS_W2SEW vawue
 *     44-45: GWS_W3SEW vawue
 *     41-44: GWS_MCSEW vawue
 *     39-40: GWS_FABSEW vawue
 *	Note that these match up with theiw bit positions in MMCW1
 *
 * UC - unit constwaint: can't have aww thwee of FPU|IFU|ISU1, ISU0, IDU|GWS
 *     37: UC3 ewwow 0x20_0000_0000
 *     36: FPU|IFU|ISU1 events needed 0x10_0000_0000
 *     35: ISU0 events needed 0x08_0000_0000
 *     34: IDU|GWS events needed 0x04_0000_0000
 *
 * PS1
 *     33: PS1 ewwow 0x2_0000_0000
 *     31-32: count of events needing PMC1/2 0x1_8000_0000
 *
 * PS2
 *     30: PS2 ewwow 0x4000_0000
 *     28-29: count of events needing PMC3/4 0x3000_0000
 *
 * B0
 *     24-27: Byte 0 event souwce 0x0f00_0000
 *	      Encoding as fow the event code
 *
 * B1, B2, B3
 *     20-23, 16-19, 12-15: Byte 1, 2, 3 event souwces
 *
 * P1..P6
 *     0-11: Count of events needing PMC1..PMC6
 */

static const int gwsew_shift[8] = {
	MMCW1_GWS_W2SEW_SH, MMCW1_GWS_W2SEW_SH, MMCW1_GWS_W2SEW_SH,
	MMCW1_GWS_W3SEW_SH, MMCW1_GWS_W3SEW_SH, MMCW1_GWS_W3SEW_SH,
	MMCW1_GWS_MCSEW_SH, MMCW1_GWS_FABSEW_SH
};

/* Masks and vawues fow using events fwom the vawious units */
static unsigned wong unit_cons[PM_WASTUNIT+1][2] = {
	[PM_FPU] =   { 0xc0002000000000uw, 0x00001000000000uw },
	[PM_ISU0] =  { 0x00002000000000uw, 0x00000800000000uw },
	[PM_ISU1] =  { 0xc0002000000000uw, 0xc0001000000000uw },
	[PM_IFU] =   { 0xc0002000000000uw, 0x80001000000000uw },
	[PM_IDU] =   { 0x30002000000000uw, 0x00000400000000uw },
	[PM_GWS] =   { 0x30002000000000uw, 0x30000400000000uw },
};

static int powew5_get_constwaint(u64 event, unsigned wong *maskp,
				 unsigned wong *vawp, u64 event_config1 __maybe_unused)
{
	int pmc, byte, unit, sh;
	int bit, fmask;
	unsigned wong mask = 0, vawue = 0;
	int gwp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 6)
			wetuwn -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		vawue |= 1 << sh;
		if (pmc <= 4)
			gwp = (pmc - 1) >> 1;
		ewse if (event != 0x500009 && event != 0x600005)
			wetuwn -1;
	}
	if (event & PM_BUSEVENT_MSK) {
		unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
		if (unit > PM_WASTUNIT)
			wetuwn -1;
		if (unit == PM_ISU0_AWT)
			unit = PM_ISU0;
		mask |= unit_cons[unit][0];
		vawue |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		if (byte >= 4) {
			if (unit != PM_WSU1)
				wetuwn -1;
			/* Map WSU1 wow wowd (bytes 4-7) to unit WSU1+1 */
			++unit;
			byte &= 3;
		}
		if (unit == PM_GWS) {
			bit = event & 7;
			fmask = (bit == 6)? 7: 3;
			sh = gwsew_shift[bit];
			mask |= (unsigned wong)fmask << sh;
			vawue |= (unsigned wong)((event >> PM_GWS_SH) & fmask)
				<< sh;
		}
		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2; bytes 1 and 3 on PMC3/4.
		 */
		if (!pmc)
			gwp = byte & 1;
		/* Set byte wane sewect fiewd */
		mask  |= 0xfUW << (24 - 4 * byte);
		vawue |= (unsigned wong)unit << (24 - 4 * byte);
	}
	if (gwp == 0) {
		/* incwement PMC1/2 fiewd */
		mask  |= 0x200000000uw;
		vawue |= 0x080000000uw;
	} ewse if (gwp == 1) {
		/* incwement PMC3/4 fiewd */
		mask  |= 0x40000000uw;
		vawue |= 0x10000000uw;
	}
	if (pmc < 5) {
		/* need a countew fwom PMC1-4 set */
		mask  |= 0x8000000000000uw;
		vawue |= 0x1000000000000uw;
	}
	*maskp = mask;
	*vawp = vawue;
	wetuwn 0;
}

#define MAX_AWT	3	/* at most 3 awtewnatives fow any event */

static const unsigned int event_awtewnatives[][MAX_AWT] = {
	{ 0x120e4,  0x400002 },			/* PM_GWP_DISP_WEJECT */
	{ 0x410c7,  0x441084 },			/* PM_THWD_W2MISS_BOTH_CYC */
	{ 0x100005, 0x600005 },			/* PM_WUN_CYC */
	{ 0x100009, 0x200009, 0x500009 },	/* PM_INST_CMPW */
	{ 0x300009, 0x400009 },			/* PM_INST_DISP */
};

/*
 * Scan the awtewnatives tabwe fow a match and wetuwn the
 * index into the awtewnatives tabwe if found, ewse -1.
 */
static int find_awtewnative(u64 event)
{
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(event_awtewnatives); ++i) {
		if (event < event_awtewnatives[i][0])
			bweak;
		fow (j = 0; j < MAX_AWT && event_awtewnatives[i][j]; ++j)
			if (event == event_awtewnatives[i][j])
				wetuwn i;
	}
	wetuwn -1;
}

static const unsigned chaw bytedecode_awtewnatives[4][4] = {
	/* PMC 1 */	{ 0x21, 0x23, 0x25, 0x27 },
	/* PMC 2 */	{ 0x07, 0x17, 0x0e, 0x1e },
	/* PMC 3 */	{ 0x20, 0x22, 0x24, 0x26 },
	/* PMC 4 */	{ 0x07, 0x17, 0x0e, 0x1e }
};

/*
 * Some diwect events fow decodes of event bus byte 3 have awtewnative
 * PMCSEW vawues on othew countews.  This wetuwns the awtewnative
 * event code fow those that do, ow -1 othewwise.
 */
static s64 find_awtewnative_bdecode(u64 event)
{
	int pmc, awtpmc, pp, j;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc == 0 || pmc > 4)
		wetuwn -1;
	awtpmc = 5 - pmc;	/* 1 <-> 4, 2 <-> 3 */
	pp = event & PM_PMCSEW_MSK;
	fow (j = 0; j < 4; ++j) {
		if (bytedecode_awtewnatives[pmc - 1][j] == pp) {
			wetuwn (event & ~(PM_PMC_MSKS | PM_PMCSEW_MSK)) |
				(awtpmc << PM_PMC_SH) |
				bytedecode_awtewnatives[awtpmc - 1][j];
		}
	}
	wetuwn -1;
}

static int powew5_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int i, j, nawt = 1;
	s64 ae;

	awt[0] = event;
	nawt = 1;
	i = find_awtewnative(event);
	if (i >= 0) {
		fow (j = 0; j < MAX_AWT; ++j) {
			ae = event_awtewnatives[i][j];
			if (ae && ae != event)
				awt[nawt++] = ae;
		}
	} ewse {
		ae = find_awtewnative_bdecode(event);
		if (ae > 0)
			awt[nawt++] = ae;
	}
	wetuwn nawt;
}

/*
 * Map of which diwect events on which PMCs awe mawked instwuction events.
 * Indexed by PMCSEW vawue, bit i (WE) set if PMC i is a mawked event.
 * Bit 0 is set if it is mawked fow aww PMCs.
 * The 0x80 bit indicates a byte decode PMCSEW vawue.
 */
static unsigned chaw diwect_event_is_mawked[0x28] = {
	0,	/* 00 */
	0x1f,	/* 01 PM_IOPS_CMPW */
	0x2,	/* 02 PM_MWK_GWP_DISP */
	0xe,	/* 03 PM_MWK_ST_CMPW, PM_MWK_ST_GPS, PM_MWK_ST_CMPW_INT */
	0,	/* 04 */
	0x1c,	/* 05 PM_MWK_BWU_FIN, PM_MWK_INST_FIN, PM_MWK_CWU_FIN */
	0x80,	/* 06 */
	0x80,	/* 07 */
	0, 0, 0,/* 08 - 0a */
	0x18,	/* 0b PM_THWESH_TIMEO, PM_MWK_GWP_TIMEO */
	0,	/* 0c */
	0x80,	/* 0d */
	0x80,	/* 0e */
	0,	/* 0f */
	0,	/* 10 */
	0x14,	/* 11 PM_MWK_GWP_BW_WEDIW, PM_MWK_GWP_IC_MISS */
	0,	/* 12 */
	0x10,	/* 13 PM_MWK_GWP_CMPW */
	0x1f,	/* 14 PM_GWP_MWK, PM_MWK_{FXU,FPU,WSU}_FIN */
	0x2,	/* 15 PM_MWK_GWP_ISSUED */
	0x80,	/* 16 */
	0x80,	/* 17 */
	0, 0, 0, 0, 0,
	0x80,	/* 1d */
	0x80,	/* 1e */
	0,	/* 1f */
	0x80,	/* 20 */
	0x80,	/* 21 */
	0x80,	/* 22 */
	0x80,	/* 23 */
	0x80,	/* 24 */
	0x80,	/* 25 */
	0x80,	/* 26 */
	0x80,	/* 27 */
};

/*
 * Wetuwns 1 if event counts things wewating to mawked instwuctions
 * and thus needs the MMCWA_SAMPWE_ENABWE bit set, ow 0 if not.
 */
static int powew5_mawked_instw_event(u64 event)
{
	int pmc, psew;
	int bit, byte, unit;
	u32 mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psew = event & PM_PMCSEW_MSK;
	if (pmc >= 5)
		wetuwn 0;

	bit = -1;
	if (psew < sizeof(diwect_event_is_mawked)) {
		if (diwect_event_is_mawked[psew] & (1 << pmc))
			wetuwn 1;
		if (diwect_event_is_mawked[psew] & 0x80)
			bit = 4;
		ewse if (psew == 0x08)
			bit = pmc - 1;
		ewse if (psew == 0x10)
			bit = 4 - pmc;
		ewse if (psew == 0x1b && (pmc == 1 || pmc == 3))
			bit = 4;
	} ewse if ((psew & 0x58) == 0x40)
		bit = psew & 7;

	if (!(event & PM_BUSEVENT_MSK))
		wetuwn 0;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	if (unit == PM_WSU0) {
		/* byte 1 bits 0-7, byte 2 bits 0,2-4,6 */
		mask = 0x5dff00;
	} ewse if (unit == PM_WSU1 && byte >= 4) {
		byte -= 4;
		/* byte 4 bits 1,3,5,7, byte 5 bits 6-7, byte 7 bits 0-4,6 */
		mask = 0x5f00c0aa;
	} ewse
		wetuwn 0;

	wetuwn (mask >> (byte * 8 + bit)) & 1;
}

static int powew5_compute_mmcw(u64 event[], int n_ev,
			       unsigned int hwc[], stwuct mmcw_wegs *mmcw,
			       stwuct pewf_event *pevents[],
			       u32 fwags __maybe_unused)
{
	unsigned wong mmcw1 = 0;
	unsigned wong mmcwa = MMCWA_SDAW_DCACHE_MISS | MMCWA_SDAW_EWAT_MISS;
	unsigned int pmc, unit, byte, psew;
	unsigned int ttm, gwp;
	int i, isbus, bit, gwsew;
	unsigned int pmc_inuse = 0;
	unsigned int pmc_gwp_use[2];
	unsigned chaw busbyte[4];
	unsigned chaw unituse[16];
	int ttmuse;

	if (n_ev > 6)
		wetuwn -1;

	/* Fiwst pass to count wesouwce use */
	pmc_gwp_use[0] = pmc_gwp_use[1] = 0;
	memset(busbyte, 0, sizeof(busbyte));
	memset(unituse, 0, sizeof(unituse));
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc > 6)
				wetuwn -1;
			if (pmc_inuse & (1 << (pmc - 1)))
				wetuwn -1;
			pmc_inuse |= 1 << (pmc - 1);
			/* count 1/2 vs 3/4 use */
			if (pmc <= 4)
				++pmc_gwp_use[(pmc - 1) >> 1];
		}
		if (event[i] & PM_BUSEVENT_MSK) {
			unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
			byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
			if (unit > PM_WASTUNIT)
				wetuwn -1;
			if (unit == PM_ISU0_AWT)
				unit = PM_ISU0;
			if (byte >= 4) {
				if (unit != PM_WSU1)
					wetuwn -1;
				++unit;
				byte &= 3;
			}
			if (!pmc)
				++pmc_gwp_use[byte & 1];
			if (busbyte[byte] && busbyte[byte] != unit)
				wetuwn -1;
			busbyte[byte] = unit;
			unituse[unit] = 1;
		}
	}
	if (pmc_gwp_use[0] > 2 || pmc_gwp_use[1] > 2)
		wetuwn -1;

	/*
	 * Assign wesouwces and set muwtipwexew sewects.
	 *
	 * PM_ISU0 can go eithew on TTM0 ow TTM1, but that's the onwy
	 * choice we have to deaw with.
	 */
	if (unituse[PM_ISU0] &
	    (unituse[PM_FPU] | unituse[PM_IFU] | unituse[PM_ISU1])) {
		unituse[PM_ISU0_AWT] = 1;	/* move ISU to TTM1 */
		unituse[PM_ISU0] = 0;
	}
	/* Set TTM[01]SEW fiewds. */
	ttmuse = 0;
	fow (i = PM_FPU; i <= PM_ISU1; ++i) {
		if (!unituse[i])
			continue;
		if (ttmuse++)
			wetuwn -1;
		mmcw1 |= (unsigned wong)i << MMCW1_TTM0SEW_SH;
	}
	ttmuse = 0;
	fow (; i <= PM_GWS; ++i) {
		if (!unituse[i])
			continue;
		if (ttmuse++)
			wetuwn -1;
		mmcw1 |= (unsigned wong)(i & 3) << MMCW1_TTM1SEW_SH;
	}
	if (ttmuse > 1)
		wetuwn -1;

	/* Set byte wane sewect fiewds, TTM[23]SEW and GWS_*SEW. */
	fow (byte = 0; byte < 4; ++byte) {
		unit = busbyte[byte];
		if (!unit)
			continue;
		if (unit == PM_ISU0 && unituse[PM_ISU0_AWT]) {
			/* get ISU0 thwough TTM1 wathew than TTM0 */
			unit = PM_ISU0_AWT;
		} ewse if (unit == PM_WSU1 + 1) {
			/* sewect wowew wowd of WSU1 fow this byte */
			mmcw1 |= 1uw << (MMCW1_TTM3SEW_SH + 3 - byte);
		}
		ttm = unit >> 2;
		mmcw1 |= (unsigned wong)ttm
			<< (MMCW1_TD_CP_DBG0SEW_SH - 2 * byte);
	}

	/* Second pass: assign PMCs, set PMCxSEW and PMCx_ADDEW_SEW fiewds */
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		psew = event[i] & PM_PMCSEW_MSK;
		isbus = event[i] & PM_BUSEVENT_MSK;
		if (!pmc) {
			/* Bus event ow any-PMC diwect event */
			fow (pmc = 0; pmc < 4; ++pmc) {
				if (pmc_inuse & (1 << pmc))
					continue;
				gwp = (pmc >> 1) & 1;
				if (isbus) {
					if (gwp == (byte & 1))
						bweak;
				} ewse if (pmc_gwp_use[gwp] < 2) {
					++pmc_gwp_use[gwp];
					bweak;
				}
			}
			pmc_inuse |= 1 << pmc;
		} ewse if (pmc <= 4) {
			/* Diwect event */
			--pmc;
			if ((psew == 8 || psew == 0x10) && isbus && (byte & 2))
				/* add events on highew-numbewed bus */
				mmcw1 |= 1uw << (MMCW1_PMC1_ADDEW_SEW_SH - pmc);
		} ewse {
			/* Instwuctions ow wun cycwes on PMC5/6 */
			--pmc;
		}
		if (isbus && unit == PM_GWS) {
			bit = psew & 7;
			gwsew = (event[i] >> PM_GWS_SH) & PM_GWS_MSK;
			mmcw1 |= (unsigned wong)gwsew << gwsew_shift[bit];
		}
		if (powew5_mawked_instw_event(event[i]))
			mmcwa |= MMCWA_SAMPWE_ENABWE;
		if (pmc <= 3)
			mmcw1 |= psew << MMCW1_PMCSEW_SH(pmc);
		hwc[i] = pmc;
	}

	/* Wetuwn MMCWx vawues */
	mmcw->mmcw0 = 0;
	if (pmc_inuse & 1)
		mmcw->mmcw0 = MMCW0_PMC1CE;
	if (pmc_inuse & 0x3e)
		mmcw->mmcw0 |= MMCW0_PMCjCE;
	mmcw->mmcw1 = mmcw1;
	mmcw->mmcwa = mmcwa;
	wetuwn 0;
}

static void powew5_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	if (pmc <= 3)
		mmcw->mmcw1 &= ~(0x7fUW << MMCW1_PMCSEW_SH(pmc));
}

static int powew5_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0xf,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x100009,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x4c1090, /* WD_WEF_W1 */
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x3c1088, /* WD_MISS_W1 */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x230e4,  /* BW_ISSUED */
	[PEWF_COUNT_HW_BWANCH_MISSES]		= 0x230e5,  /* BW_MPWED_CW */
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 powew5_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x4c1090,	0x3c1088	},
		[C(OP_WWITE)] = {	0x3c1090,	0xc10c3		},
		[C(OP_PWEFETCH)] = {	0xc70e7,	0		},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	0,		0		},
	},
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x3c309b	},
		[C(OP_WWITE)] = {	0,		0		},
		[C(OP_PWEFETCH)] = {	0xc50c3,	0		},
	},
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x2c4090,	0x800c4		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(ITWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x800c0		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x230e4,	0x230e5		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
};

static stwuct powew_pmu powew5_pmu = {
	.name			= "POWEW5",
	.n_countew		= 6,
	.max_awtewnatives	= MAX_AWT,
	.add_fiewds		= 0x7000090000555uw,
	.test_addew		= 0x3000490000000uw,
	.compute_mmcw		= powew5_compute_mmcw,
	.get_constwaint		= powew5_get_constwaint,
	.get_awtewnatives	= powew5_get_awtewnatives,
	.disabwe_pmc		= powew5_disabwe_pmc,
	.n_genewic		= AWWAY_SIZE(powew5_genewic_events),
	.genewic_events		= powew5_genewic_events,
	.cache_events		= &powew5_cache_events,
	.fwags			= PPMU_HAS_SSWOT,
};

int __init init_powew5_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_POWEW5)
		wetuwn -ENODEV;

	wetuwn wegistew_powew_pmu(&powew5_pmu);
}
