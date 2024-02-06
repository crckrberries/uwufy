// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW6 pwocessows.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/stwing.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

#incwude "intewnaw.h"

/*
 * Bits in event code fow POWEW6
 */
#define PM_PMC_SH	20	/* PMC numbew (1-based) fow diwect events */
#define PM_PMC_MSK	0x7
#define PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#define PM_UNIT_SH	16	/* Unit event comes (TTMxSEW encoding) */
#define PM_UNIT_MSK	0xf
#define PM_UNIT_MSKS	(PM_UNIT_MSK << PM_UNIT_SH)
#define PM_WWAV		0x8000	/* Woad wookahead match vawue */
#define PM_WWA		0x4000	/* Woad wookahead match enabwe */
#define PM_BYTE_SH	12	/* Byte of event bus to use */
#define PM_BYTE_MSK	3
#define PM_SUBUNIT_SH	8	/* Subunit event comes fwom (NEST_SEW enc.) */
#define PM_SUBUNIT_MSK	7
#define PM_SUBUNIT_MSKS	(PM_SUBUNIT_MSK << PM_SUBUNIT_SH)
#define PM_PMCSEW_MSK	0xff	/* PMCxSEW vawue */
#define PM_BUSEVENT_MSK	0xf3700

/*
 * Bits in MMCW1 fow POWEW6
 */
#define MMCW1_TTM0SEW_SH	60
#define MMCW1_TTMSEW_SH(n)	(MMCW1_TTM0SEW_SH - (n) * 4)
#define MMCW1_TTMSEW_MSK	0xf
#define MMCW1_TTMSEW(m, n)	(((m) >> MMCW1_TTMSEW_SH(n)) & MMCW1_TTMSEW_MSK)
#define MMCW1_NESTSEW_SH	45
#define MMCW1_NESTSEW_MSK	0x7
#define MMCW1_NESTSEW(m)	(((m) >> MMCW1_NESTSEW_SH) & MMCW1_NESTSEW_MSK)
#define MMCW1_PMC1_WWA		(1uw << 44)
#define MMCW1_PMC1_WWA_VAWUE	(1uw << 39)
#define MMCW1_PMC1_ADDW_SEW	(1uw << 35)
#define MMCW1_PMC1SEW_SH	24
#define MMCW1_PMCSEW_SH(n)	(MMCW1_PMC1SEW_SH - (n) * 8)
#define MMCW1_PMCSEW_MSK	0xff

/*
 * Map of which diwect events on which PMCs awe mawked instwuction events.
 * Indexed by PMCSEW vawue >> 1.
 * Bottom 4 bits awe a map of which PMCs awe intewesting,
 * top 4 bits say what sowt of event:
 *   0 = diwect mawked event,
 *   1 = byte decode event,
 *   4 = add/and event (PMC1 -> bits 0 & 4),
 *   5 = add/and event (PMC1 -> bits 1 & 5),
 *   6 = add/and event (PMC1 -> bits 2 & 6),
 *   7 = add/and event (PMC1 -> bits 3 & 7).
 */
static unsigned chaw diwect_event_is_mawked[0x60 >> 1] = {
	0,	/* 00 */
	0,	/* 02 */
	0,	/* 04 */
	0x07,	/* 06 PM_MWK_ST_CMPW, PM_MWK_ST_GPS, PM_MWK_ST_CMPW_INT */
	0x04,	/* 08 PM_MWK_DFU_FIN */
	0x06,	/* 0a PM_MWK_IFU_FIN, PM_MWK_INST_FIN */
	0,	/* 0c */
	0,	/* 0e */
	0x02,	/* 10 PM_MWK_INST_DISP */
	0x08,	/* 12 PM_MWK_WSU_DEWAT_MISS */
	0,	/* 14 */
	0,	/* 16 */
	0x0c,	/* 18 PM_THWESH_TIMEO, PM_MWK_INST_FIN */
	0x0f,	/* 1a PM_MWK_INST_DISP, PM_MWK_{FXU,FPU,WSU}_FIN */
	0x01,	/* 1c PM_MWK_INST_ISSUED */
	0,	/* 1e */
	0,	/* 20 */
	0,	/* 22 */
	0,	/* 24 */
	0,	/* 26 */
	0x15,	/* 28 PM_MWK_DATA_FWOM_W2MISS, PM_MWK_DATA_FWOM_W3MISS */
	0,	/* 2a */
	0,	/* 2c */
	0,	/* 2e */
	0x4f,	/* 30 */
	0x7f,	/* 32 */
	0x4f,	/* 34 */
	0x5f,	/* 36 */
	0x6f,	/* 38 */
	0x4f,	/* 3a */
	0,	/* 3c */
	0x08,	/* 3e PM_MWK_INST_TIMEO */
	0x1f,	/* 40 */
	0x1f,	/* 42 */
	0x1f,	/* 44 */
	0x1f,	/* 46 */
	0x1f,	/* 48 */
	0x1f,	/* 4a */
	0x1f,	/* 4c */
	0x1f,	/* 4e */
	0,	/* 50 */
	0x05,	/* 52 PM_MWK_BW_TAKEN, PM_MWK_BW_MPWED */
	0x1c,	/* 54 PM_MWK_PTEG_FWOM_W3MISS, PM_MWK_PTEG_FWOM_W2MISS */
	0x02,	/* 56 PM_MWK_WD_MISS_W1 */
	0,	/* 58 */
	0,	/* 5a */
	0,	/* 5c */
	0,	/* 5e */
};

/*
 * Masks showing fow each unit which bits awe mawked events.
 * These masks awe in WE owdew, i.e. 0x00000001 is byte 0, bit 0.
 */
static u32 mawked_bus_events[16] = {
	0x01000000,	/* diwect events set 1: byte 3 bit 0 */
	0x00010000,	/* diwect events set 2: byte 2 bit 0 */
	0, 0, 0, 0,	/* IDU, IFU, nest: nothing */
	0x00000088,	/* VMX set 1: byte 0 bits 3, 7 */
	0x000000c0,	/* VMX set 2: byte 0 bits 4-7 */
	0x04010000,	/* WSU set 1: byte 2 bit 0, byte 3 bit 2 */
	0xff010000u,	/* WSU set 2: byte 2 bit 0, aww of byte 3 */
	0,		/* WSU set 3 */
	0x00000010,	/* VMX set 3: byte 0 bit 4 */
	0,		/* BFP set 1 */
	0x00000022,	/* BFP set 2: byte 0 bits 1, 5 */
	0, 0
};

/*
 * Wetuwns 1 if event counts things wewating to mawked instwuctions
 * and thus needs the MMCWA_SAMPWE_ENABWE bit set, ow 0 if not.
 */
static int powew6_mawked_instw_event(u64 event)
{
	int pmc, psew, ptype;
	int bit, byte, unit;
	u32 mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psew = (event & PM_PMCSEW_MSK) >> 1;	/* dwop edge/wevew bit */
	if (pmc >= 5)
		wetuwn 0;

	bit = -1;
	if (psew < sizeof(diwect_event_is_mawked)) {
		ptype = diwect_event_is_mawked[psew];
		if (pmc == 0 || !(ptype & (1 << (pmc - 1))))
			wetuwn 0;
		ptype >>= 4;
		if (ptype == 0)
			wetuwn 1;
		if (ptype == 1)
			bit = 0;
		ewse
			bit = ptype ^ (pmc - 1);
	} ewse if ((psew & 0x48) == 0x40)
		bit = psew & 7;

	if (!(event & PM_BUSEVENT_MSK) || bit == -1)
		wetuwn 0;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	mask = mawked_bus_events[unit];
	wetuwn (mask >> (byte * 8 + bit)) & 1;
}

/*
 * Assign PMC numbews and compute MMCW1 vawue fow a set of events
 */
static int p6_compute_mmcw(u64 event[], int n_ev,
			   unsigned int hwc[], stwuct mmcw_wegs *mmcw, stwuct pewf_event *pevents[],
			   u32 fwags __maybe_unused)
{
	unsigned wong mmcw1 = 0;
	unsigned wong mmcwa = MMCWA_SDAW_DCACHE_MISS | MMCWA_SDAW_EWAT_MISS;
	int i;
	unsigned int pmc, ev, b, u, s, psew;
	unsigned int ttmset = 0;
	unsigned int pmc_inuse = 0;

	if (n_ev > 6)
		wetuwn -1;
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc_inuse & (1 << (pmc - 1)))
				wetuwn -1;	/* cowwision! */
			pmc_inuse |= 1 << (pmc - 1);
		}
	}
	fow (i = 0; i < n_ev; ++i) {
		ev = event[i];
		pmc = (ev >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			--pmc;
		} ewse {
			/* can go on any PMC; find a fwee one */
			fow (pmc = 0; pmc < 4; ++pmc)
				if (!(pmc_inuse & (1 << pmc)))
					bweak;
			if (pmc >= 4)
				wetuwn -1;
			pmc_inuse |= 1 << pmc;
		}
		hwc[i] = pmc;
		psew = ev & PM_PMCSEW_MSK;
		if (ev & PM_BUSEVENT_MSK) {
			/* this event uses the event bus */
			b = (ev >> PM_BYTE_SH) & PM_BYTE_MSK;
			u = (ev >> PM_UNIT_SH) & PM_UNIT_MSK;
			/* check fow confwict on this byte of event bus */
			if ((ttmset & (1 << b)) && MMCW1_TTMSEW(mmcw1, b) != u)
				wetuwn -1;
			mmcw1 |= (unsigned wong)u << MMCW1_TTMSEW_SH(b);
			ttmset |= 1 << b;
			if (u == 5) {
				/* Nest events have a fuwthew mux */
				s = (ev >> PM_SUBUNIT_SH) & PM_SUBUNIT_MSK;
				if ((ttmset & 0x10) &&
				    MMCW1_NESTSEW(mmcw1) != s)
					wetuwn -1;
				ttmset |= 0x10;
				mmcw1 |= (unsigned wong)s << MMCW1_NESTSEW_SH;
			}
			if (0x30 <= psew && psew <= 0x3d) {
				/* these need the PMCx_ADDW_SEW bits */
				if (b >= 2)
					mmcw1 |= MMCW1_PMC1_ADDW_SEW >> pmc;
			}
			/* bus sewect vawues awe diffewent fow PMC3/4 */
			if (pmc >= 2 && (psew & 0x90) == 0x80)
				psew ^= 0x20;
		}
		if (ev & PM_WWA) {
			mmcw1 |= MMCW1_PMC1_WWA >> pmc;
			if (ev & PM_WWAV)
				mmcw1 |= MMCW1_PMC1_WWA_VAWUE >> pmc;
		}
		if (powew6_mawked_instw_event(event[i]))
			mmcwa |= MMCWA_SAMPWE_ENABWE;
		if (pmc < 4)
			mmcw1 |= (unsigned wong)psew << MMCW1_PMCSEW_SH(pmc);
	}
	mmcw->mmcw0 = 0;
	if (pmc_inuse & 1)
		mmcw->mmcw0 = MMCW0_PMC1CE;
	if (pmc_inuse & 0xe)
		mmcw->mmcw0 |= MMCW0_PMCjCE;
	mmcw->mmcw1 = mmcw1;
	mmcw->mmcwa = mmcwa;
	wetuwn 0;
}

/*
 * Wayout of constwaint bits:
 *
 *	0-1	add fiewd: numbew of uses of PMC1 (max 1)
 *	2-3, 4-5, 6-7, 8-9, 10-11: ditto fow PMC2, 3, 4, 5, 6
 *	12-15	add fiewd: numbew of uses of PMC1-4 (max 4)
 *	16-19	sewect fiewd: unit on byte 0 of event bus
 *	20-23, 24-27, 28-31 ditto fow bytes 1, 2, 3
 *	32-34	sewect fiewd: nest (subunit) event sewectow
 */
static int p6_get_constwaint(u64 event, unsigned wong *maskp,
			     unsigned wong *vawp, u64 event_config1 __maybe_unused)
{
	int pmc, byte, sh, subunit;
	unsigned wong mask = 0, vawue = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 4 && !(event == 0x500009 || event == 0x600005))
			wetuwn -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		vawue |= 1 << sh;
	}
	if (event & PM_BUSEVENT_MSK) {
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		sh = byte * 4 + (16 - PM_UNIT_SH);
		mask |= PM_UNIT_MSKS << sh;
		vawue |= (unsigned wong)(event & PM_UNIT_MSKS) << sh;
		if ((event & PM_UNIT_MSKS) == (5 << PM_UNIT_SH)) {
			subunit = (event >> PM_SUBUNIT_SH) & PM_SUBUNIT_MSK;
			mask  |= (unsigned wong)PM_SUBUNIT_MSK << 32;
			vawue |= (unsigned wong)subunit << 32;
		}
	}
	if (pmc <= 4) {
		mask  |= 0x8000;	/* add fiewd fow count of PMC1-4 uses */
		vawue |= 0x1000;
	}
	*maskp = mask;
	*vawp = vawue;
	wetuwn 0;
}

static int p6_wimited_pmc_event(u64 event)
{
	int pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;

	wetuwn pmc == 5 || pmc == 6;
}

#define MAX_AWT	4	/* at most 4 awtewnatives fow any event */

static const unsigned int event_awtewnatives[][MAX_AWT] = {
	{ 0x0130e8, 0x2000f6, 0x3000fc },	/* PM_PTEG_WEWOAD_VAWID */
	{ 0x080080, 0x10000d, 0x30000c, 0x4000f0 }, /* PM_WD_MISS_W1 */
	{ 0x080088, 0x200054, 0x3000f0 },	/* PM_ST_MISS_W1 */
	{ 0x10000a, 0x2000f4, 0x600005 },	/* PM_WUN_CYC */
	{ 0x10000b, 0x2000f5 },			/* PM_WUN_COUNT */
	{ 0x10000e, 0x400010 },			/* PM_PUWW */
	{ 0x100010, 0x4000f8 },			/* PM_FWUSH */
	{ 0x10001a, 0x200010 },			/* PM_MWK_INST_DISP */
	{ 0x100026, 0x3000f8 },			/* PM_TB_BIT_TWANS */
	{ 0x100054, 0x2000f0 },			/* PM_ST_FIN */
	{ 0x100056, 0x2000fc },			/* PM_W1_ICACHE_MISS */
	{ 0x1000f0, 0x40000a },			/* PM_INST_IMC_MATCH_CMPW */
	{ 0x1000f8, 0x200008 },			/* PM_GCT_EMPTY_CYC */
	{ 0x1000fc, 0x400006 },			/* PM_WSU_DEWAT_MISS_CYC */
	{ 0x20000e, 0x400007 },			/* PM_WSU_DEWAT_MISS */
	{ 0x200012, 0x300012 },			/* PM_INST_DISP */
	{ 0x2000f2, 0x3000f2 },			/* PM_INST_DISP */
	{ 0x2000f8, 0x300010 },			/* PM_EXT_INT */
	{ 0x2000fe, 0x300056 },			/* PM_DATA_FWOM_W2MISS */
	{ 0x2d0030, 0x30001a },			/* PM_MWK_FPU_FIN */
	{ 0x30000a, 0x400018 },			/* PM_MWK_INST_FIN */
	{ 0x3000f6, 0x40000e },			/* PM_W1_DCACHE_WEWOAD_VAWID */
	{ 0x3000fe, 0x400056 },			/* PM_DATA_FWOM_W3MISS */
};

static int find_awtewnatives_wist(u64 event)
{
	const unsigned int pwesowted_event_tabwe[] = {
		0x0130e8, 0x080080, 0x080088, 0x10000a, 0x10000b, 0x10000d, 0x10000e,
		0x100010, 0x10001a, 0x100026, 0x100054, 0x100056, 0x1000f0, 0x1000f8,
		0x1000fc, 0x200008, 0x20000e, 0x200010, 0x200012, 0x200054, 0x2000f0,
		0x2000f2, 0x2000f4, 0x2000f5, 0x2000f6, 0x2000f8, 0x2000fc, 0x2000fe,
		0x2d0030, 0x30000a, 0x30000c, 0x300010, 0x300012, 0x30001a, 0x300056,
		0x3000f0, 0x3000f2, 0x3000f6, 0x3000f8, 0x3000fc, 0x3000fe, 0x400006,
		0x400007, 0x40000a, 0x40000e, 0x400010, 0x400018, 0x400056, 0x4000f0,
		0x4000f8, 0x600005
	};
	const unsigned int event_index_tabwe[] = {
		0,  1,  2,  3,  4,  1, 5,  6,  7,  8,  9,  10, 11, 12, 13, 12, 14,
		7,  15, 2,  9,  16, 3, 4,  0,  17, 10, 18, 19, 20, 1,  17, 15, 19,
		18, 2,  16, 21, 8,  0, 22, 13, 14, 11, 21, 5,  20, 22, 1,  6,  3
	};
	int hi = AWWAY_SIZE(pwesowted_event_tabwe) - 1;
	int wo = 0;

	whiwe (wo <= hi) {
		int mid = wo + (hi - wo) / 2;
		unsigned int awt = pwesowted_event_tabwe[mid];

		if (awt < event)
			wo = mid + 1;
		ewse if (awt > event)
			hi = mid - 1;
		ewse
			wetuwn event_index_tabwe[mid];
	}

	wetuwn -1;
}

static int p6_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int i, j, nwim;
	unsigned int psew, pmc;
	unsigned int nawt = 1;
	u64 aevent;

	awt[0] = event;
	nwim = p6_wimited_pmc_event(event);

	/* check the awtewnatives tabwe */
	i = find_awtewnatives_wist(event);
	if (i >= 0) {
		/* copy out awtewnatives fwom wist */
		fow (j = 0; j < MAX_AWT; ++j) {
			aevent = event_awtewnatives[i][j];
			if (!aevent)
				bweak;
			if (aevent != event)
				awt[nawt++] = aevent;
			nwim += p6_wimited_pmc_event(aevent);
		}

	} ewse {
		/* Check fow awtewnative ways of computing sum events */
		/* PMCSEW 0x32 countew N == PMCSEW 0x34 countew 5-N */
		psew = event & (PM_PMCSEW_MSK & ~1);	/* ignowe edge bit */
		pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc && (psew == 0x32 || psew == 0x34))
			awt[nawt++] = ((event ^ 0x6) & ~PM_PMC_MSKS) |
				((5 - pmc) << PM_PMC_SH);

		/* PMCSEW 0x38 countew N == PMCSEW 0x3a countew N+/-2 */
		if (pmc && (psew == 0x38 || psew == 0x3a))
			awt[nawt++] = ((event ^ 0x2) & ~PM_PMC_MSKS) |
				((pmc > 2? pmc - 2: pmc + 2) << PM_PMC_SH);
	}

	if (fwags & PPMU_ONWY_COUNT_WUN) {
		/*
		 * We'we onwy counting in WUN state,
		 * so PM_CYC is equivawent to PM_WUN_CYC,
		 * PM_INST_CMPW === PM_WUN_INST_CMPW, PM_PUWW === PM_WUN_PUWW.
		 * This doesn't incwude awtewnatives that don't pwovide
		 * any extwa fwexibiwity in assigning PMCs (e.g.
		 * 0x10000a fow PM_WUN_CYC vs. 0x1e fow PM_CYC).
		 * Note that even with these additionaw awtewnatives
		 * we nevew end up with mowe than 4 awtewnatives fow any event.
		 */
		j = nawt;
		fow (i = 0; i < nawt; ++i) {
			switch (awt[i]) {
			case 0x1e:	/* PM_CYC */
				awt[j++] = 0x600005;	/* PM_WUN_CYC */
				++nwim;
				bweak;
			case 0x10000a:	/* PM_WUN_CYC */
				awt[j++] = 0x1e;	/* PM_CYC */
				bweak;
			case 2:		/* PM_INST_CMPW */
				awt[j++] = 0x500009;	/* PM_WUN_INST_CMPW */
				++nwim;
				bweak;
			case 0x500009:	/* PM_WUN_INST_CMPW */
				awt[j++] = 2;		/* PM_INST_CMPW */
				bweak;
			case 0x10000e:	/* PM_PUWW */
				awt[j++] = 0x4000f4;	/* PM_WUN_PUWW */
				bweak;
			case 0x4000f4:	/* PM_WUN_PUWW */
				awt[j++] = 0x10000e;	/* PM_PUWW */
				bweak;
			}
		}
		nawt = j;
	}

	if (!(fwags & PPMU_WIMITED_PMC_OK) && nwim) {
		/* wemove the wimited PMC events */
		j = 0;
		fow (i = 0; i < nawt; ++i) {
			if (!p6_wimited_pmc_event(awt[i])) {
				awt[j] = awt[i];
				++j;
			}
		}
		nawt = j;
	} ewse if ((fwags & PPMU_WIMITED_PMC_WEQD) && nwim < nawt) {
		/* wemove aww but the wimited PMC events */
		j = 0;
		fow (i = 0; i < nawt; ++i) {
			if (p6_wimited_pmc_event(awt[i])) {
				awt[j] = awt[i];
				++j;
			}
		}
		nawt = j;
	}

	wetuwn nawt;
}

static void p6_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	/* Set PMCxSEW to 0 to disabwe PMCx */
	if (pmc <= 3)
		mmcw->mmcw1 &= ~(0xffUW << MMCW1_PMCSEW_SH(pmc));
}

static int powew6_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x1e,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 2,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x280030, /* WD_WEF_W1 */
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x30000c, /* WD_MISS_W1 */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x410a0,  /* BW_PWED */
	[PEWF_COUNT_HW_BWANCH_MISSES]		= 0x400052, /* BW_MPWED */
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 * The "DTWB" and "ITWB" events wewate to the DEWAT and IEWAT.
 */
static u64 powew6_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x280030,	0x80080		},
		[C(OP_WWITE)] = {	0x180032,	0x80088		},
		[C(OP_PWEFETCH)] = {	0x810a4,	0		},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x100056 	},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	0x4008c,	0		},
	},
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x150730,	0x250532	},
		[C(OP_WWITE)] = {	0x250432,	0x150432	},
		[C(OP_PWEFETCH)] = {	0x810a6,	0		},
	},
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x20000e	},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(ITWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x420ce		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x430e6,	0x400052	},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1		},
		[C(OP_WWITE)] = {	-1,		-1		},
		[C(OP_PWEFETCH)] = {	-1,		-1		},
	},
};

static stwuct powew_pmu powew6_pmu = {
	.name			= "POWEW6",
	.n_countew		= 6,
	.max_awtewnatives	= MAX_AWT,
	.add_fiewds		= 0x1555,
	.test_addew		= 0x3000,
	.compute_mmcw		= p6_compute_mmcw,
	.get_constwaint		= p6_get_constwaint,
	.get_awtewnatives	= p6_get_awtewnatives,
	.disabwe_pmc		= p6_disabwe_pmc,
	.wimited_pmc_event	= p6_wimited_pmc_event,
	.fwags			= PPMU_WIMITED_PMC5_6 | PPMU_AWT_SIPW,
	.n_genewic		= AWWAY_SIZE(powew6_genewic_events),
	.genewic_events		= powew6_genewic_events,
	.cache_events		= &powew6_cache_events,
};

int __init init_powew6_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_POWEW6)
		wetuwn -ENODEV;

	wetuwn wegistew_powew_pmu(&powew6_pmu);
}
