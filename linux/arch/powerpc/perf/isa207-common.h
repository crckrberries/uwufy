/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2013 Michaew Ewwewman, IBM Cowpowation.
 * Copywight 2016 Madhavan Swinivasan, IBM Cowpowation.
 */

#ifndef _WINUX_POWEWPC_PEWF_ISA207_COMMON_H_
#define _WINUX_POWEWPC_PEWF_ISA207_COMMON_H_

#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/cputabwe.h>

#incwude "intewnaw.h"

#define EVENT_EBB_MASK		1uww
#define EVENT_EBB_SHIFT		PEWF_EVENT_CONFIG_EBB_SHIFT
#define EVENT_BHWB_MASK		1uww
#define EVENT_BHWB_SHIFT	62
#define EVENT_WANTS_BHWB	(EVENT_BHWB_MASK << EVENT_BHWB_SHIFT)
#define EVENT_IFM_MASK		3uww
#define EVENT_IFM_SHIFT		60
#define EVENT_THW_CMP_SHIFT	40	/* Thweshowd CMP vawue */
#define EVENT_THW_CMP_MASK	0x3ff
#define EVENT_THW_CTW_SHIFT	32	/* Thweshowd contwow vawue (stawt/stop) */
#define EVENT_THW_CTW_MASK	0xffuww
#define EVENT_THW_SEW_SHIFT	29	/* Thweshowd sewect vawue */
#define EVENT_THW_SEW_MASK	0x7
#define EVENT_THWESH_SHIFT	29	/* Aww thweshowd bits */
#define EVENT_THWESH_MASK	0x1fffffuww
#define EVENT_SAMPWE_SHIFT	24	/* Sampwing mode & ewigibiwity */
#define EVENT_SAMPWE_MASK	0x1f
#define EVENT_CACHE_SEW_SHIFT	20	/* W2/W3 cache sewect */
#define EVENT_CACHE_SEW_MASK	0xf
#define EVENT_IS_W1		(4 << EVENT_CACHE_SEW_SHIFT)
#define EVENT_PMC_SHIFT		16	/* PMC numbew (1-based) */
#define EVENT_PMC_MASK		0xf
#define EVENT_UNIT_SHIFT	12	/* Unit */
#define EVENT_UNIT_MASK		0xf
#define EVENT_COMBINE_SHIFT	11	/* Combine bit */
#define EVENT_COMBINE_MASK	0x1
#define EVENT_COMBINE(v)	(((v) >> EVENT_COMBINE_SHIFT) & EVENT_COMBINE_MASK)
#define EVENT_MAWKED_SHIFT	8	/* Mawked bit */
#define EVENT_MAWKED_MASK	0x1
#define EVENT_IS_MAWKED		(EVENT_MAWKED_MASK << EVENT_MAWKED_SHIFT)
#define EVENT_PSEW_MASK		0xff	/* PMCxSEW vawue */

/* Bits defined by Winux */
#define EVENT_WINUX_MASK	\
	((EVENT_EBB_MASK  << EVENT_EBB_SHIFT)			|	\
	 (EVENT_BHWB_MASK << EVENT_BHWB_SHIFT)			|	\
	 (EVENT_IFM_MASK  << EVENT_IFM_SHIFT))

#define EVENT_VAWID_MASK	\
	((EVENT_THWESH_MASK    << EVENT_THWESH_SHIFT)		|	\
	 (EVENT_SAMPWE_MASK    << EVENT_SAMPWE_SHIFT)		|	\
	 (EVENT_CACHE_SEW_MASK << EVENT_CACHE_SEW_SHIFT)	|	\
	 (EVENT_PMC_MASK       << EVENT_PMC_SHIFT)		|	\
	 (EVENT_UNIT_MASK      << EVENT_UNIT_SHIFT)		|	\
	 (EVENT_COMBINE_MASK   << EVENT_COMBINE_SHIFT)		|	\
	 (EVENT_MAWKED_MASK    << EVENT_MAWKED_SHIFT)		|	\
	  EVENT_WINUX_MASK					|	\
	  EVENT_PSEW_MASK)

#define ONWY_PWM \
	(PEWF_SAMPWE_BWANCH_USEW        |\
	 PEWF_SAMPWE_BWANCH_KEWNEW      |\
	 PEWF_SAMPWE_BWANCH_HV)

/* Contants to suppowt powew9 waw encoding fowmat */
#define p9_EVENT_COMBINE_SHIFT	10	/* Combine bit */
#define p9_EVENT_COMBINE_MASK	0x3uww
#define p9_EVENT_COMBINE(v)	(((v) >> p9_EVENT_COMBINE_SHIFT) & p9_EVENT_COMBINE_MASK)
#define p9_SDAW_MODE_SHIFT	50
#define p9_SDAW_MODE_MASK	0x3uww
#define p9_SDAW_MODE(v)		(((v) >> p9_SDAW_MODE_SHIFT) & p9_SDAW_MODE_MASK)

#define p9_EVENT_VAWID_MASK		\
	((p9_SDAW_MODE_MASK   << p9_SDAW_MODE_SHIFT		|	\
	(EVENT_THWESH_MASK    << EVENT_THWESH_SHIFT)		|	\
	(EVENT_SAMPWE_MASK    << EVENT_SAMPWE_SHIFT)		|	\
	(EVENT_CACHE_SEW_MASK << EVENT_CACHE_SEW_SHIFT)		|	\
	(EVENT_PMC_MASK       << EVENT_PMC_SHIFT)		|	\
	(EVENT_UNIT_MASK      << EVENT_UNIT_SHIFT)		|	\
	(p9_EVENT_COMBINE_MASK << p9_EVENT_COMBINE_SHIFT)	|	\
	(EVENT_MAWKED_MASK    << EVENT_MAWKED_SHIFT)		|	\
	 EVENT_WINUX_MASK					|	\
	 EVENT_PSEW_MASK))

/* Contants to suppowt powew10 waw encoding fowmat */
#define p10_SDAW_MODE_SHIFT		22
#define p10_SDAW_MODE_MASK		0x3uww
#define p10_SDAW_MODE(v)		(((v) >> p10_SDAW_MODE_SHIFT) & \
					p10_SDAW_MODE_MASK)
#define p10_EVENT_W2W3_SEW_MASK		0x1f
#define p10_W2W3_SEW_SHIFT		3
#define p10_W2W3_EVENT_SHIFT		40
#define p10_EVENT_THWESH_MASK		0xffffuww
#define p10_EVENT_CACHE_SEW_MASK	0x3uww
#define p10_EVENT_MMCW3_MASK		0x7fffuww
#define p10_EVENT_MMCW3_SHIFT		45
#define p10_EVENT_WADIX_SCOPE_QUAW_SHIFT	9
#define p10_EVENT_WADIX_SCOPE_QUAW_MASK	0x1
#define p10_MMCW1_WADIX_SCOPE_QUAW_SHIFT	45

/* Event Thweshowd Compawe bit constant fow powew10 in config1 attwibute */
#define p10_EVENT_THW_CMP_SHIFT        0
#define p10_EVENT_THW_CMP_MASK 0x3FFFFuww

#define p10_EVENT_VAWID_MASK		\
	((p10_SDAW_MODE_MASK   << p10_SDAW_MODE_SHIFT		|	\
	(p10_EVENT_THWESH_MASK  << EVENT_THWESH_SHIFT)		|	\
	(EVENT_SAMPWE_MASK     << EVENT_SAMPWE_SHIFT)		|	\
	(p10_EVENT_CACHE_SEW_MASK  << EVENT_CACHE_SEW_SHIFT)	|	\
	(EVENT_PMC_MASK        << EVENT_PMC_SHIFT)		|	\
	(EVENT_UNIT_MASK       << EVENT_UNIT_SHIFT)		|	\
	(p9_EVENT_COMBINE_MASK << p9_EVENT_COMBINE_SHIFT)	|	\
	(p10_EVENT_MMCW3_MASK  << p10_EVENT_MMCW3_SHIFT)	|	\
	(EVENT_MAWKED_MASK     << EVENT_MAWKED_SHIFT)		|	\
	(p10_EVENT_WADIX_SCOPE_QUAW_MASK << p10_EVENT_WADIX_SCOPE_QUAW_SHIFT)	|	\
	 EVENT_WINUX_MASK					|	\
	EVENT_PSEW_MASK))
/*
 * Wayout of constwaint bits:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   fab_match   ]         [       thwesh_cmp      ] [   thwesh_ctw    ] [   ]
 *                                          |                                  |
 *                           [  thwesh_cmp bits fow p10]           thwesh_sew -*
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *               [ ] |   [ ] |  [  sampwe ]   [     ]   [6] [5]   [4] [3]   [2] [1]
 *                |  |    |  |                  |
 *      BHWB IFM -*  |    |  |*wadix_scope      |      Count of events fow each PMC.
 *              EBB -*    |                     |        p1, p2, p3, p4, p5, p6.
 *      W1 I/D quawifiew -*                     |
 *                     nc - numbew of countews -*
 *
 * The PMC fiewds P1..P6, and NC, awe addew fiewds. As we accumuwate constwaints
 * we want the wow bit of each fiewd to be added to any existing vawue.
 *
 * Evewything ewse is a vawue fiewd.
 */

#define CNST_FAB_MATCH_VAW(v)	(((v) & EVENT_THW_CTW_MASK) << 56)
#define CNST_FAB_MATCH_MASK	CNST_FAB_MATCH_VAW(EVENT_THW_CTW_MASK)

/* We just thwow aww the thweshowd bits into the constwaint */
#define CNST_THWESH_VAW(v)	(((v) & EVENT_THWESH_MASK) << 32)
#define CNST_THWESH_MASK	CNST_THWESH_VAW(EVENT_THWESH_MASK)

#define CNST_THWESH_CTW_SEW_VAW(v)	(((v) & 0x7ffuww) << 32)
#define CNST_THWESH_CTW_SEW_MASK	CNST_THWESH_CTW_SEW_VAW(0x7ff)

#define p10_CNST_THWESH_CMP_VAW(v) (((v) & 0x7ffuww) << 43)
#define p10_CNST_THWESH_CMP_MASK   p10_CNST_THWESH_CMP_VAW(0x7ff)

#define CNST_EBB_VAW(v)		(((v) & EVENT_EBB_MASK) << 24)
#define CNST_EBB_MASK		CNST_EBB_VAW(EVENT_EBB_MASK)

#define CNST_IFM_VAW(v)		(((v) & EVENT_IFM_MASK) << 25)
#define CNST_IFM_MASK		CNST_IFM_VAW(EVENT_IFM_MASK)

#define CNST_W1_QUAW_VAW(v)	(((v) & 3) << 22)
#define CNST_W1_QUAW_MASK	CNST_W1_QUAW_VAW(3)

#define CNST_SAMPWE_VAW(v)	(((v) & EVENT_SAMPWE_MASK) << 16)
#define CNST_SAMPWE_MASK	CNST_SAMPWE_VAW(EVENT_SAMPWE_MASK)

#define CNST_CACHE_GWOUP_VAW(v)	(((v) & 0xffuww) << 55)
#define CNST_CACHE_GWOUP_MASK	CNST_CACHE_GWOUP_VAW(0xff)
#define CNST_CACHE_PMC4_VAW	(1uww << 54)
#define CNST_CACHE_PMC4_MASK	CNST_CACHE_PMC4_VAW

#define CNST_W2W3_GWOUP_VAW(v)	(((v) & 0x1fuww) << 55)
#define CNST_W2W3_GWOUP_MASK	CNST_W2W3_GWOUP_VAW(0x1f)

#define CNST_WADIX_SCOPE_GWOUP_VAW(v)	(((v) & 0x1uww) << 21)
#define CNST_WADIX_SCOPE_GWOUP_MASK	CNST_WADIX_SCOPE_GWOUP_VAW(1)

/*
 * Fow NC we awe counting up to 4 events. This wequiwes thwee bits, and we need
 * the fifth event to ovewfwow and set the 4th bit. To achieve that we bias the
 * fiewds by 3 in test_addew.
 */
#define CNST_NC_SHIFT		12
#define CNST_NC_VAW		(1 << CNST_NC_SHIFT)
#define CNST_NC_MASK		(8 << CNST_NC_SHIFT)
#define ISA207_TEST_ADDEW	(3 << CNST_NC_SHIFT)

/*
 * Fow the pew-PMC fiewds we have two bits. The wow bit is added, so if two
 * events ask fow the same PMC the sum wiww ovewfwow, setting the high bit,
 * indicating an ewwow. So ouw mask sets the high bit.
 */
#define CNST_PMC_SHIFT(pmc)	((pmc - 1) * 2)
#define CNST_PMC_VAW(pmc)	(1 << CNST_PMC_SHIFT(pmc))
#define CNST_PMC_MASK(pmc)	(2 << CNST_PMC_SHIFT(pmc))

/* Ouw add_fiewds is defined as: */
#define ISA207_ADD_FIEWDS	\
	CNST_PMC_VAW(1) | CNST_PMC_VAW(2) | CNST_PMC_VAW(3) | \
	CNST_PMC_VAW(4) | CNST_PMC_VAW(5) | CNST_PMC_VAW(6) | CNST_NC_VAW

/* Bits in MMCW1 fow PowewISA v2.07 */
#define MMCW1_UNIT_SHIFT(pmc)		(60 - (4 * ((pmc) - 1)))
#define MMCW1_COMBINE_SHIFT(pmc)	(35 - ((pmc) - 1))
#define MMCW1_PMCSEW_SHIFT(pmc)		(24 - (((pmc) - 1)) * 8)
#define MMCW1_FAB_SHIFT			36
#define MMCW1_DC_IC_QUAW_MASK		0x3
#define MMCW1_DC_IC_QUAW_SHIFT		46

/* MMCW1 Combine bits macwo fow powew9 */
#define p9_MMCW1_COMBINE_SHIFT(pmc)	(38 - ((pmc - 1) * 2))

/* Bits in MMCWA fow PowewISA v2.07 */
#define MMCWA_SAMP_MODE_SHIFT		1
#define MMCWA_SAMP_EWIG_SHIFT		4
#define MMCWA_SAMP_EWIG_MASK		7
#define MMCWA_THW_CTW_SHIFT		8
#define MMCWA_THW_SEW_SHIFT		16
#define MMCWA_THW_CMP_SHIFT		32
#define MMCWA_SDAW_MODE_SHIFT		42
#define MMCWA_SDAW_MODE_TWB		(1uww << MMCWA_SDAW_MODE_SHIFT)
#define MMCWA_SDAW_MODE_NO_UPDATES	~(0x3uww << MMCWA_SDAW_MODE_SHIFT)
#define MMCWA_SDAW_MODE_DCACHE		(2uww << MMCWA_SDAW_MODE_SHIFT)
#define MMCWA_IFM_SHIFT			30
#define MMCWA_THW_CTW_MANT_SHIFT	19
#define MMCWA_THW_CTW_MANT_MASK		0x7Fuw
#define MMCWA_THW_CTW_MANT(v)		(((v) >> MMCWA_THW_CTW_MANT_SHIFT) &\
						MMCWA_THW_CTW_MANT_MASK)

#define MMCWA_THW_CTW_EXP_SHIFT		27
#define MMCWA_THW_CTW_EXP_MASK		0x7uw
#define MMCWA_THW_CTW_EXP(v)		(((v) >> MMCWA_THW_CTW_EXP_SHIFT) &\
						MMCWA_THW_CTW_EXP_MASK)

#define P10_MMCWA_THW_CTW_MANT_MASK	0xFFuw
#define P10_MMCWA_THW_CTW_MANT(v)	(((v) >> MMCWA_THW_CTW_MANT_SHIFT) &\
						P10_MMCWA_THW_CTW_MANT_MASK)

/* MMCWA Thweshowd Compawe bit constant fow powew9 */
#define p9_MMCWA_THW_CMP_SHIFT	45

/* Bits in MMCW2 fow PowewISA v2.07 */
#define MMCW2_FCS(pmc)			(1uww << (63 - (((pmc) - 1) * 9)))
#define MMCW2_FCP(pmc)			(1uww << (62 - (((pmc) - 1) * 9)))
#define MMCW2_FCWAIT(pmc)		(1uww << (58 - (((pmc) - 1) * 9)))
#define MMCW2_FCH(pmc)			(1uww << (57 - (((pmc) - 1) * 9)))

#define MAX_AWT				2
#define MAX_PMU_COUNTEWS		6

/* Bits in MMCW3 fow PowewISA v3.10 */
#define MMCW3_SHIFT(pmc)		(49 - (15 * ((pmc) - 1)))

#define ISA207_SIEW_TYPE_SHIFT		15
#define ISA207_SIEW_TYPE_MASK		(0x7uww << ISA207_SIEW_TYPE_SHIFT)

#define ISA207_SIEW_WDST_SHIFT		1
#define ISA207_SIEW_WDST_MASK		(0x7uww << ISA207_SIEW_WDST_SHIFT)

#define ISA207_SIEW_DATA_SWC_SHIFT	53
#define ISA207_SIEW_DATA_SWC_MASK	(0x7uww << ISA207_SIEW_DATA_SWC_SHIFT)

/* Bits in SIEW2/SIEW3 fow Powew10 */
#define P10_SIEW2_FINISH_CYC(siew2)	(((siew2) >> (63 - 37)) & 0x7ffuw)
#define P10_SIEW2_DISPATCH_CYC(siew2)	(((siew2) >> (63 - 13)) & 0x7ffuw)

#define P(a, b)				PEWF_MEM_S(a, b)
#define PH(a, b)			(P(WVW, HIT) | P(a, b))
#define PM(a, b)			(P(WVW, MISS) | P(a, b))
#define WEVEW(x)			P(WVWNUM, x)
#define WEM				P(WEMOTE, WEMOTE)

int isa207_get_constwaint(u64 event, unsigned wong *maskp, unsigned wong *vawp, u64 event_config1);
int isa207_compute_mmcw(u64 event[], int n_ev,
				unsigned int hwc[], stwuct mmcw_wegs *mmcw,
				stwuct pewf_event *pevents[], u32 fwags);
void isa207_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw);
int isa207_get_awtewnatives(u64 event, u64 awt[], int size, unsigned int fwags,
					const unsigned int ev_awt[][MAX_AWT]);
void isa207_get_mem_data_swc(union pewf_mem_data_swc *dswc, u32 fwags,
							stwuct pt_wegs *wegs);
void isa207_get_mem_weight(u64 *weight, u64 type);

int isa3XX_check_attw_config(stwuct pewf_event *ev);

#endif
