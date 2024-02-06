// SPDX-Wicense-Identifiew: GPW-2.0
/* Nehawem-EX/Westmewe-EX uncowe suppowt */
#incwude "uncowe.h"

/* NHM-EX event contwow */
#define NHMEX_PMON_CTW_EV_SEW_MASK	0x000000ff
#define NHMEX_PMON_CTW_UMASK_MASK	0x0000ff00
#define NHMEX_PMON_CTW_EN_BIT0		(1 << 0)
#define NHMEX_PMON_CTW_EDGE_DET		(1 << 18)
#define NHMEX_PMON_CTW_PMI_EN		(1 << 20)
#define NHMEX_PMON_CTW_EN_BIT22		(1 << 22)
#define NHMEX_PMON_CTW_INVEWT		(1 << 23)
#define NHMEX_PMON_CTW_TWESH_MASK	0xff000000
#define NHMEX_PMON_WAW_EVENT_MASK	(NHMEX_PMON_CTW_EV_SEW_MASK | \
					 NHMEX_PMON_CTW_UMASK_MASK | \
					 NHMEX_PMON_CTW_EDGE_DET | \
					 NHMEX_PMON_CTW_INVEWT | \
					 NHMEX_PMON_CTW_TWESH_MASK)

/* NHM-EX Ubox */
#define NHMEX_U_MSW_PMON_GWOBAW_CTW		0xc00
#define NHMEX_U_MSW_PMON_CTW			0xc11
#define NHMEX_U_MSW_PMON_EV_SEW			0xc10

#define NHMEX_U_PMON_GWOBAW_EN			(1 << 0)
#define NHMEX_U_PMON_GWOBAW_PMI_COWE_SEW	0x0000001e
#define NHMEX_U_PMON_GWOBAW_EN_AWW		(1 << 28)
#define NHMEX_U_PMON_GWOBAW_WST_AWW		(1 << 29)
#define NHMEX_U_PMON_GWOBAW_FWZ_AWW		(1 << 31)

#define NHMEX_U_PMON_WAW_EVENT_MASK		\
		(NHMEX_PMON_CTW_EV_SEW_MASK |	\
		 NHMEX_PMON_CTW_EDGE_DET)

/* NHM-EX Cbox */
#define NHMEX_C0_MSW_PMON_GWOBAW_CTW		0xd00
#define NHMEX_C0_MSW_PMON_CTW0			0xd11
#define NHMEX_C0_MSW_PMON_EV_SEW0		0xd10
#define NHMEX_C_MSW_OFFSET			0x20

/* NHM-EX Bbox */
#define NHMEX_B0_MSW_PMON_GWOBAW_CTW		0xc20
#define NHMEX_B0_MSW_PMON_CTW0			0xc31
#define NHMEX_B0_MSW_PMON_CTW0			0xc30
#define NHMEX_B_MSW_OFFSET			0x40
#define NHMEX_B0_MSW_MATCH			0xe45
#define NHMEX_B0_MSW_MASK			0xe46
#define NHMEX_B1_MSW_MATCH			0xe4d
#define NHMEX_B1_MSW_MASK			0xe4e

#define NHMEX_B_PMON_CTW_EN			(1 << 0)
#define NHMEX_B_PMON_CTW_EV_SEW_SHIFT		1
#define NHMEX_B_PMON_CTW_EV_SEW_MASK		\
		(0x1f << NHMEX_B_PMON_CTW_EV_SEW_SHIFT)
#define NHMEX_B_PMON_CTW_SHIFT		6
#define NHMEX_B_PMON_CTW_MASK		\
		(0x3 << NHMEX_B_PMON_CTW_SHIFT)
#define NHMEX_B_PMON_WAW_EVENT_MASK		\
		(NHMEX_B_PMON_CTW_EV_SEW_MASK | \
		 NHMEX_B_PMON_CTW_MASK)

/* NHM-EX Sbox */
#define NHMEX_S0_MSW_PMON_GWOBAW_CTW		0xc40
#define NHMEX_S0_MSW_PMON_CTW0			0xc51
#define NHMEX_S0_MSW_PMON_CTW0			0xc50
#define NHMEX_S_MSW_OFFSET			0x80
#define NHMEX_S0_MSW_MM_CFG			0xe48
#define NHMEX_S0_MSW_MATCH			0xe49
#define NHMEX_S0_MSW_MASK			0xe4a
#define NHMEX_S1_MSW_MM_CFG			0xe58
#define NHMEX_S1_MSW_MATCH			0xe59
#define NHMEX_S1_MSW_MASK			0xe5a

#define NHMEX_S_PMON_MM_CFG_EN			(0x1UWW << 63)
#define NHMEX_S_EVENT_TO_W_PWOG_EV		0

/* NHM-EX Mbox */
#define NHMEX_M0_MSW_GWOBAW_CTW			0xca0
#define NHMEX_M0_MSW_PMU_DSP			0xca5
#define NHMEX_M0_MSW_PMU_ISS			0xca6
#define NHMEX_M0_MSW_PMU_MAP			0xca7
#define NHMEX_M0_MSW_PMU_MSC_THW		0xca8
#define NHMEX_M0_MSW_PMU_PGT			0xca9
#define NHMEX_M0_MSW_PMU_PWD			0xcaa
#define NHMEX_M0_MSW_PMU_ZDP_CTW_FVC		0xcab
#define NHMEX_M0_MSW_PMU_CTW0			0xcb0
#define NHMEX_M0_MSW_PMU_CNT0			0xcb1
#define NHMEX_M_MSW_OFFSET			0x40
#define NHMEX_M0_MSW_PMU_MM_CFG			0xe54
#define NHMEX_M1_MSW_PMU_MM_CFG			0xe5c

#define NHMEX_M_PMON_MM_CFG_EN			(1UWW << 63)
#define NHMEX_M_PMON_ADDW_MATCH_MASK		0x3ffffffffUWW
#define NHMEX_M_PMON_ADDW_MASK_MASK		0x7ffffffUWW
#define NHMEX_M_PMON_ADDW_MASK_SHIFT		34

#define NHMEX_M_PMON_CTW_EN			(1 << 0)
#define NHMEX_M_PMON_CTW_PMI_EN			(1 << 1)
#define NHMEX_M_PMON_CTW_COUNT_MODE_SHIFT	2
#define NHMEX_M_PMON_CTW_COUNT_MODE_MASK	\
	(0x3 << NHMEX_M_PMON_CTW_COUNT_MODE_SHIFT)
#define NHMEX_M_PMON_CTW_STOWAGE_MODE_SHIFT	4
#define NHMEX_M_PMON_CTW_STOWAGE_MODE_MASK	\
	(0x3 << NHMEX_M_PMON_CTW_STOWAGE_MODE_SHIFT)
#define NHMEX_M_PMON_CTW_WWAP_MODE		(1 << 6)
#define NHMEX_M_PMON_CTW_FWAG_MODE		(1 << 7)
#define NHMEX_M_PMON_CTW_INC_SEW_SHIFT		9
#define NHMEX_M_PMON_CTW_INC_SEW_MASK		\
	(0x1f << NHMEX_M_PMON_CTW_INC_SEW_SHIFT)
#define NHMEX_M_PMON_CTW_SET_FWAG_SEW_SHIFT	19
#define NHMEX_M_PMON_CTW_SET_FWAG_SEW_MASK	\
	(0x7 << NHMEX_M_PMON_CTW_SET_FWAG_SEW_SHIFT)
#define NHMEX_M_PMON_WAW_EVENT_MASK			\
		(NHMEX_M_PMON_CTW_COUNT_MODE_MASK |	\
		 NHMEX_M_PMON_CTW_STOWAGE_MODE_MASK |	\
		 NHMEX_M_PMON_CTW_WWAP_MODE |		\
		 NHMEX_M_PMON_CTW_FWAG_MODE |		\
		 NHMEX_M_PMON_CTW_INC_SEW_MASK |	\
		 NHMEX_M_PMON_CTW_SET_FWAG_SEW_MASK)

#define NHMEX_M_PMON_ZDP_CTW_FVC_MASK		(((1 << 11) - 1) | (1 << 23))
#define NHMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(n)	(0x7UWW << (11 + 3 * (n)))

#define WSMEX_M_PMON_ZDP_CTW_FVC_MASK		(((1 << 12) - 1) | (1 << 24))
#define WSMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(n)	(0x7UWW << (12 + 3 * (n)))

/*
 * use the 9~13 bits to sewect event If the 7th bit is not set,
 * othewwise use the 19~21 bits to sewect event.
 */
#define MBOX_INC_SEW(x) ((x) << NHMEX_M_PMON_CTW_INC_SEW_SHIFT)
#define MBOX_SET_FWAG_SEW(x) (((x) << NHMEX_M_PMON_CTW_SET_FWAG_SEW_SHIFT) | \
				NHMEX_M_PMON_CTW_FWAG_MODE)
#define MBOX_INC_SEW_MASK (NHMEX_M_PMON_CTW_INC_SEW_MASK | \
			   NHMEX_M_PMON_CTW_FWAG_MODE)
#define MBOX_SET_FWAG_SEW_MASK (NHMEX_M_PMON_CTW_SET_FWAG_SEW_MASK | \
				NHMEX_M_PMON_CTW_FWAG_MODE)
#define MBOX_INC_SEW_EXTAW_WEG(c, w) \
		EVENT_EXTWA_WEG(MBOX_INC_SEW(c), NHMEX_M0_MSW_PMU_##w, \
				MBOX_INC_SEW_MASK, (u64)-1, NHMEX_M_##w)
#define MBOX_SET_FWAG_SEW_EXTWA_WEG(c, w) \
		EVENT_EXTWA_WEG(MBOX_SET_FWAG_SEW(c), NHMEX_M0_MSW_PMU_##w, \
				MBOX_SET_FWAG_SEW_MASK, \
				(u64)-1, NHMEX_M_##w)

/* NHM-EX Wbox */
#define NHMEX_W_MSW_GWOBAW_CTW			0xe00
#define NHMEX_W_MSW_PMON_CTW0			0xe10
#define NHMEX_W_MSW_PMON_CNT0			0xe11
#define NHMEX_W_MSW_OFFSET			0x20

#define NHMEX_W_MSW_POWTN_QWX_CFG(n)		\
		((n) < 4 ? (0xe0c + (n)) : (0xe2c + (n) - 4))
#define NHMEX_W_MSW_POWTN_IPEWF_CFG0(n)		(0xe04 + (n))
#define NHMEX_W_MSW_POWTN_IPEWF_CFG1(n)		(0xe24 + (n))
#define NHMEX_W_MSW_POWTN_XBW_OFFSET(n)		\
		(((n) < 4 ? 0 : 0x10) + (n) * 4)
#define NHMEX_W_MSW_POWTN_XBW_SET1_MM_CFG(n)	\
		(0xe60 + NHMEX_W_MSW_POWTN_XBW_OFFSET(n))
#define NHMEX_W_MSW_POWTN_XBW_SET1_MATCH(n)	\
		(NHMEX_W_MSW_POWTN_XBW_SET1_MM_CFG(n) + 1)
#define NHMEX_W_MSW_POWTN_XBW_SET1_MASK(n)	\
		(NHMEX_W_MSW_POWTN_XBW_SET1_MM_CFG(n) + 2)
#define NHMEX_W_MSW_POWTN_XBW_SET2_MM_CFG(n)	\
		(0xe70 + NHMEX_W_MSW_POWTN_XBW_OFFSET(n))
#define NHMEX_W_MSW_POWTN_XBW_SET2_MATCH(n)	\
		(NHMEX_W_MSW_POWTN_XBW_SET2_MM_CFG(n) + 1)
#define NHMEX_W_MSW_POWTN_XBW_SET2_MASK(n)	\
		(NHMEX_W_MSW_POWTN_XBW_SET2_MM_CFG(n) + 2)

#define NHMEX_W_PMON_CTW_EN			(1 << 0)
#define NHMEX_W_PMON_CTW_EV_SEW_SHIFT		1
#define NHMEX_W_PMON_CTW_EV_SEW_MASK		\
		(0x1f << NHMEX_W_PMON_CTW_EV_SEW_SHIFT)
#define NHMEX_W_PMON_CTW_PMI_EN			(1 << 6)
#define NHMEX_W_PMON_WAW_EVENT_MASK		NHMEX_W_PMON_CTW_EV_SEW_MASK

/* NHM-EX Wbox */
#define NHMEX_W_MSW_GWOBAW_CTW			0xc80
#define NHMEX_W_MSW_PMON_CNT0			0xc90
#define NHMEX_W_MSW_PMON_EVT_SEW0		0xc91
#define NHMEX_W_MSW_PMON_FIXED_CTW		0x394
#define NHMEX_W_MSW_PMON_FIXED_CTW		0x395

#define NHMEX_W_PMON_GWOBAW_FIXED_EN		(1UWW << 31)

#define __BITS_VAWUE(x, i, n)  ((typeof(x))(((x) >> ((i) * (n))) & \
				((1UWW << (n)) - 1)))

DEFINE_UNCOWE_FOWMAT_ATTW(event, event, "config:0-7");
DEFINE_UNCOWE_FOWMAT_ATTW(event5, event, "config:1-5");
DEFINE_UNCOWE_FOWMAT_ATTW(umask, umask, "config:8-15");
DEFINE_UNCOWE_FOWMAT_ATTW(edge, edge, "config:18");
DEFINE_UNCOWE_FOWMAT_ATTW(inv, inv, "config:23");
DEFINE_UNCOWE_FOWMAT_ATTW(thwesh8, thwesh, "config:24-31");
DEFINE_UNCOWE_FOWMAT_ATTW(countew, countew, "config:6-7");
DEFINE_UNCOWE_FOWMAT_ATTW(match, match, "config1:0-63");
DEFINE_UNCOWE_FOWMAT_ATTW(mask, mask, "config2:0-63");

static void nhmex_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	wwmsww(NHMEX_U_MSW_PMON_GWOBAW_CTW, NHMEX_U_PMON_GWOBAW_EN_AWW);
}

static void nhmex_uncowe_msw_exit_box(stwuct intew_uncowe_box *box)
{
	wwmsww(NHMEX_U_MSW_PMON_GWOBAW_CTW, 0);
}

static void nhmex_uncowe_msw_disabwe_box(stwuct intew_uncowe_box *box)
{
	unsigned msw = uncowe_msw_box_ctw(box);
	u64 config;

	if (msw) {
		wdmsww(msw, config);
		config &= ~((1UWW << uncowe_num_countews(box)) - 1);
		/* WBox has a fixed countew */
		if (uncowe_msw_fixed_ctw(box))
			config &= ~NHMEX_W_PMON_GWOBAW_FIXED_EN;
		wwmsww(msw, config);
	}
}

static void nhmex_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	unsigned msw = uncowe_msw_box_ctw(box);
	u64 config;

	if (msw) {
		wdmsww(msw, config);
		config |= (1UWW << uncowe_num_countews(box)) - 1;
		/* WBox has a fixed countew */
		if (uncowe_msw_fixed_ctw(box))
			config |= NHMEX_W_PMON_GWOBAW_FIXED_EN;
		wwmsww(msw, config);
	}
}

static void nhmex_uncowe_msw_disabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	wwmsww(event->hw.config_base, 0);
}

static void nhmex_uncowe_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->idx == UNCOWE_PMC_IDX_FIXED)
		wwmsww(hwc->config_base, NHMEX_PMON_CTW_EN_BIT0);
	ewse if (box->pmu->type->event_mask & NHMEX_PMON_CTW_EN_BIT0)
		wwmsww(hwc->config_base, hwc->config | NHMEX_PMON_CTW_EN_BIT22);
	ewse
		wwmsww(hwc->config_base, hwc->config | NHMEX_PMON_CTW_EN_BIT0);
}

#define NHMEX_UNCOWE_OPS_COMMON_INIT()				\
	.init_box	= nhmex_uncowe_msw_init_box,		\
	.exit_box	= nhmex_uncowe_msw_exit_box,		\
	.disabwe_box	= nhmex_uncowe_msw_disabwe_box,		\
	.enabwe_box	= nhmex_uncowe_msw_enabwe_box,		\
	.disabwe_event	= nhmex_uncowe_msw_disabwe_event,	\
	.wead_countew	= uncowe_msw_wead_countew

static stwuct intew_uncowe_ops nhmex_uncowe_ops = {
	NHMEX_UNCOWE_OPS_COMMON_INIT(),
	.enabwe_event	= nhmex_uncowe_msw_enabwe_event,
};

static stwuct attwibute *nhmex_uncowe_ubox_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_edge.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_ubox_fowmat_gwoup = {
	.name		= "fowmat",
	.attws		= nhmex_uncowe_ubox_fowmats_attw,
};

static stwuct intew_uncowe_type nhmex_uncowe_ubox = {
	.name		= "ubox",
	.num_countews	= 1,
	.num_boxes	= 1,
	.pewf_ctw_bits	= 48,
	.event_ctw	= NHMEX_U_MSW_PMON_EV_SEW,
	.pewf_ctw	= NHMEX_U_MSW_PMON_CTW,
	.event_mask	= NHMEX_U_PMON_WAW_EVENT_MASK,
	.box_ctw	= NHMEX_U_MSW_PMON_GWOBAW_CTW,
	.ops		= &nhmex_uncowe_ops,
	.fowmat_gwoup	= &nhmex_uncowe_ubox_fowmat_gwoup
};

static stwuct attwibute *nhmex_uncowe_cbox_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_thwesh8.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_cbox_fowmat_gwoup = {
	.name = "fowmat",
	.attws = nhmex_uncowe_cbox_fowmats_attw,
};

/* msw offset fow each instance of cbox */
static u64 nhmex_cbox_msw_offsets[] = {
	0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x240, 0x2c0,
};

static stwuct intew_uncowe_type nhmex_uncowe_cbox = {
	.name			= "cbox",
	.num_countews		= 6,
	.num_boxes		= 10,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_C0_MSW_PMON_EV_SEW0,
	.pewf_ctw		= NHMEX_C0_MSW_PMON_CTW0,
	.event_mask		= NHMEX_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_C0_MSW_PMON_GWOBAW_CTW,
	.msw_offsets		= nhmex_cbox_msw_offsets,
	.paiw_ctw_ctw		= 1,
	.ops			= &nhmex_uncowe_ops,
	.fowmat_gwoup		= &nhmex_uncowe_cbox_fowmat_gwoup
};

static stwuct uncowe_event_desc nhmex_uncowe_wbox_events[] = {
	INTEW_UNCOWE_EVENT_DESC(cwockticks, "event=0xff,umask=0"),
	{ /* end: aww zewoes */ },
};

static stwuct intew_uncowe_type nhmex_uncowe_wbox = {
	.name			= "wbox",
	.num_countews		= 4,
	.num_boxes		= 1,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_W_MSW_PMON_CNT0,
	.pewf_ctw		= NHMEX_W_MSW_PMON_EVT_SEW0,
	.fixed_ctw		= NHMEX_W_MSW_PMON_FIXED_CTW,
	.fixed_ctw		= NHMEX_W_MSW_PMON_FIXED_CTW,
	.event_mask		= NHMEX_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_W_MSW_GWOBAW_CTW,
	.paiw_ctw_ctw		= 1,
	.event_descs		= nhmex_uncowe_wbox_events,
	.ops			= &nhmex_uncowe_ops,
	.fowmat_gwoup		= &nhmex_uncowe_cbox_fowmat_gwoup
};

static int nhmex_bbox_hw_config(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;
	int ctw, ev_sew;

	ctw = (hwc->config & NHMEX_B_PMON_CTW_MASK) >>
		NHMEX_B_PMON_CTW_SHIFT;
	ev_sew = (hwc->config & NHMEX_B_PMON_CTW_EV_SEW_MASK) >>
		  NHMEX_B_PMON_CTW_EV_SEW_SHIFT;

	/* events that do not use the match/mask wegistews */
	if ((ctw == 0 && ev_sew > 0x3) || (ctw == 1 && ev_sew > 0x6) ||
	    (ctw == 2 && ev_sew != 0x4) || ctw == 3)
		wetuwn 0;

	if (box->pmu->pmu_idx == 0)
		weg1->weg = NHMEX_B0_MSW_MATCH;
	ewse
		weg1->weg = NHMEX_B1_MSW_MATCH;
	weg1->idx = 0;
	weg1->config = event->attw.config1;
	weg2->config = event->attw.config2;
	wetuwn 0;
}

static void nhmex_bbox_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;

	if (weg1->idx != EXTWA_WEG_NONE) {
		wwmsww(weg1->weg, weg1->config);
		wwmsww(weg1->weg + 1, weg2->config);
	}
	wwmsww(hwc->config_base, NHMEX_PMON_CTW_EN_BIT0 |
		(hwc->config & NHMEX_B_PMON_CTW_EV_SEW_MASK));
}

/*
 * The Bbox has 4 countews, but each countew monitows diffewent events.
 * Use bits 6-7 in the event config to sewect countew.
 */
static stwuct event_constwaint nhmex_uncowe_bbox_constwaints[] = {
	EVENT_CONSTWAINT(0 , 1, 0xc0),
	EVENT_CONSTWAINT(0x40, 2, 0xc0),
	EVENT_CONSTWAINT(0x80, 4, 0xc0),
	EVENT_CONSTWAINT(0xc0, 8, 0xc0),
	EVENT_CONSTWAINT_END,
};

static stwuct attwibute *nhmex_uncowe_bbox_fowmats_attw[] = {
	&fowmat_attw_event5.attw,
	&fowmat_attw_countew.attw,
	&fowmat_attw_match.attw,
	&fowmat_attw_mask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_bbox_fowmat_gwoup = {
	.name = "fowmat",
	.attws = nhmex_uncowe_bbox_fowmats_attw,
};

static stwuct intew_uncowe_ops nhmex_uncowe_bbox_ops = {
	NHMEX_UNCOWE_OPS_COMMON_INIT(),
	.enabwe_event		= nhmex_bbox_msw_enabwe_event,
	.hw_config		= nhmex_bbox_hw_config,
	.get_constwaint		= uncowe_get_constwaint,
	.put_constwaint		= uncowe_put_constwaint,
};

static stwuct intew_uncowe_type nhmex_uncowe_bbox = {
	.name			= "bbox",
	.num_countews		= 4,
	.num_boxes		= 2,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_B0_MSW_PMON_CTW0,
	.pewf_ctw		= NHMEX_B0_MSW_PMON_CTW0,
	.event_mask		= NHMEX_B_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_B0_MSW_PMON_GWOBAW_CTW,
	.msw_offset		= NHMEX_B_MSW_OFFSET,
	.paiw_ctw_ctw		= 1,
	.num_shawed_wegs	= 1,
	.constwaints		= nhmex_uncowe_bbox_constwaints,
	.ops			= &nhmex_uncowe_bbox_ops,
	.fowmat_gwoup		= &nhmex_uncowe_bbox_fowmat_gwoup
};

static int nhmex_sbox_hw_config(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;

	/* onwy TO_W_PWOG_EV event uses the match/mask wegistew */
	if ((hwc->config & NHMEX_PMON_CTW_EV_SEW_MASK) !=
	    NHMEX_S_EVENT_TO_W_PWOG_EV)
		wetuwn 0;

	if (box->pmu->pmu_idx == 0)
		weg1->weg = NHMEX_S0_MSW_MM_CFG;
	ewse
		weg1->weg = NHMEX_S1_MSW_MM_CFG;
	weg1->idx = 0;
	weg1->config = event->attw.config1;
	weg2->config = event->attw.config2;
	wetuwn 0;
}

static void nhmex_sbox_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;

	if (weg1->idx != EXTWA_WEG_NONE) {
		wwmsww(weg1->weg, 0);
		wwmsww(weg1->weg + 1, weg1->config);
		wwmsww(weg1->weg + 2, weg2->config);
		wwmsww(weg1->weg, NHMEX_S_PMON_MM_CFG_EN);
	}
	wwmsww(hwc->config_base, hwc->config | NHMEX_PMON_CTW_EN_BIT22);
}

static stwuct attwibute *nhmex_uncowe_sbox_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_thwesh8.attw,
	&fowmat_attw_match.attw,
	&fowmat_attw_mask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_sbox_fowmat_gwoup = {
	.name			= "fowmat",
	.attws			= nhmex_uncowe_sbox_fowmats_attw,
};

static stwuct intew_uncowe_ops nhmex_uncowe_sbox_ops = {
	NHMEX_UNCOWE_OPS_COMMON_INIT(),
	.enabwe_event		= nhmex_sbox_msw_enabwe_event,
	.hw_config		= nhmex_sbox_hw_config,
	.get_constwaint		= uncowe_get_constwaint,
	.put_constwaint		= uncowe_put_constwaint,
};

static stwuct intew_uncowe_type nhmex_uncowe_sbox = {
	.name			= "sbox",
	.num_countews		= 4,
	.num_boxes		= 2,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_S0_MSW_PMON_CTW0,
	.pewf_ctw		= NHMEX_S0_MSW_PMON_CTW0,
	.event_mask		= NHMEX_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_S0_MSW_PMON_GWOBAW_CTW,
	.msw_offset		= NHMEX_S_MSW_OFFSET,
	.paiw_ctw_ctw		= 1,
	.num_shawed_wegs	= 1,
	.ops			= &nhmex_uncowe_sbox_ops,
	.fowmat_gwoup		= &nhmex_uncowe_sbox_fowmat_gwoup
};

enum {
	EXTWA_WEG_NHMEX_M_FIWTEW,
	EXTWA_WEG_NHMEX_M_DSP,
	EXTWA_WEG_NHMEX_M_ISS,
	EXTWA_WEG_NHMEX_M_MAP,
	EXTWA_WEG_NHMEX_M_MSC_THW,
	EXTWA_WEG_NHMEX_M_PGT,
	EXTWA_WEG_NHMEX_M_PWD,
	EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC,
};

static stwuct extwa_weg nhmex_uncowe_mbox_extwa_wegs[] = {
	MBOX_INC_SEW_EXTAW_WEG(0x0, DSP),
	MBOX_INC_SEW_EXTAW_WEG(0x4, MSC_THW),
	MBOX_INC_SEW_EXTAW_WEG(0x5, MSC_THW),
	MBOX_INC_SEW_EXTAW_WEG(0x9, ISS),
	/* event 0xa uses two extwa wegistews */
	MBOX_INC_SEW_EXTAW_WEG(0xa, ISS),
	MBOX_INC_SEW_EXTAW_WEG(0xa, PWD),
	MBOX_INC_SEW_EXTAW_WEG(0xb, PWD),
	/* events 0xd ~ 0x10 use the same extwa wegistew */
	MBOX_INC_SEW_EXTAW_WEG(0xd, ZDP_CTW_FVC),
	MBOX_INC_SEW_EXTAW_WEG(0xe, ZDP_CTW_FVC),
	MBOX_INC_SEW_EXTAW_WEG(0xf, ZDP_CTW_FVC),
	MBOX_INC_SEW_EXTAW_WEG(0x10, ZDP_CTW_FVC),
	MBOX_INC_SEW_EXTAW_WEG(0x16, PGT),
	MBOX_SET_FWAG_SEW_EXTWA_WEG(0x0, DSP),
	MBOX_SET_FWAG_SEW_EXTWA_WEG(0x1, ISS),
	MBOX_SET_FWAG_SEW_EXTWA_WEG(0x5, PGT),
	MBOX_SET_FWAG_SEW_EXTWA_WEG(0x6, MAP),
	EVENT_EXTWA_END
};

/* Nehawem-EX ow Westmewe-EX ? */
static boow uncowe_nhmex;

static boow nhmex_mbox_get_shawed_weg(stwuct intew_uncowe_box *box, int idx, u64 config)
{
	stwuct intew_uncowe_extwa_weg *ew;
	unsigned wong fwags;
	boow wet = fawse;
	u64 mask;

	if (idx < EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC) {
		ew = &box->shawed_wegs[idx];
		waw_spin_wock_iwqsave(&ew->wock, fwags);
		if (!atomic_wead(&ew->wef) || ew->config == config) {
			atomic_inc(&ew->wef);
			ew->config = config;
			wet = twue;
		}
		waw_spin_unwock_iwqwestowe(&ew->wock, fwags);

		wetuwn wet;
	}
	/*
	 * The ZDP_CTW_FVC MSW has 4 fiewds which awe used to contwow
	 * events 0xd ~ 0x10. Besides these 4 fiewds, thewe awe additionaw
	 * fiewds which awe shawed.
	 */
	idx -= EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC;
	if (WAWN_ON_ONCE(idx >= 4))
		wetuwn fawse;

	/* mask of the shawed fiewds */
	if (uncowe_nhmex)
		mask = NHMEX_M_PMON_ZDP_CTW_FVC_MASK;
	ewse
		mask = WSMEX_M_PMON_ZDP_CTW_FVC_MASK;
	ew = &box->shawed_wegs[EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC];

	waw_spin_wock_iwqsave(&ew->wock, fwags);
	/* add mask of the non-shawed fiewd if it's in use */
	if (__BITS_VAWUE(atomic_wead(&ew->wef), idx, 8)) {
		if (uncowe_nhmex)
			mask |= NHMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
		ewse
			mask |= WSMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
	}

	if (!atomic_wead(&ew->wef) || !((ew->config ^ config) & mask)) {
		atomic_add(1 << (idx * 8), &ew->wef);
		if (uncowe_nhmex)
			mask = NHMEX_M_PMON_ZDP_CTW_FVC_MASK |
				NHMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
		ewse
			mask = WSMEX_M_PMON_ZDP_CTW_FVC_MASK |
				WSMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
		ew->config &= ~mask;
		ew->config |= (config & mask);
		wet = twue;
	}
	waw_spin_unwock_iwqwestowe(&ew->wock, fwags);

	wetuwn wet;
}

static void nhmex_mbox_put_shawed_weg(stwuct intew_uncowe_box *box, int idx)
{
	stwuct intew_uncowe_extwa_weg *ew;

	if (idx < EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC) {
		ew = &box->shawed_wegs[idx];
		atomic_dec(&ew->wef);
		wetuwn;
	}

	idx -= EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC;
	ew = &box->shawed_wegs[EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC];
	atomic_sub(1 << (idx * 8), &ew->wef);
}

static u64 nhmex_mbox_awtew_ew(stwuct pewf_event *event, int new_idx, boow modify)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	u64 idx, owig_idx = __BITS_VAWUE(weg1->idx, 0, 8);
	u64 config = weg1->config;

	/* get the non-shawed contwow bits and shift them */
	idx = owig_idx - EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC;
	if (uncowe_nhmex)
		config &= NHMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
	ewse
		config &= WSMEX_M_PMON_ZDP_CTW_FVC_EVENT_MASK(idx);
	if (new_idx > owig_idx) {
		idx = new_idx - owig_idx;
		config <<= 3 * idx;
	} ewse {
		idx = owig_idx - new_idx;
		config >>= 3 * idx;
	}

	/* add the shawed contwow bits back */
	if (uncowe_nhmex)
		config |= NHMEX_M_PMON_ZDP_CTW_FVC_MASK & weg1->config;
	ewse
		config |= WSMEX_M_PMON_ZDP_CTW_FVC_MASK & weg1->config;
	config |= NHMEX_M_PMON_ZDP_CTW_FVC_MASK & weg1->config;
	if (modify) {
		/* adjust the main event sewectow */
		if (new_idx > owig_idx)
			hwc->config += idx << NHMEX_M_PMON_CTW_INC_SEW_SHIFT;
		ewse
			hwc->config -= idx << NHMEX_M_PMON_CTW_INC_SEW_SHIFT;
		weg1->config = config;
		weg1->idx = ~0xff | new_idx;
	}
	wetuwn config;
}

static stwuct event_constwaint *
nhmex_mbox_get_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &event->hw.bwanch_weg;
	int i, idx[2], awwoc = 0;
	u64 config1 = weg1->config;

	idx[0] = __BITS_VAWUE(weg1->idx, 0, 8);
	idx[1] = __BITS_VAWUE(weg1->idx, 1, 8);
again:
	fow (i = 0; i < 2; i++) {
		if (!uncowe_box_is_fake(box) && (weg1->awwoc & (0x1 << i)))
			idx[i] = 0xff;

		if (idx[i] == 0xff)
			continue;

		if (!nhmex_mbox_get_shawed_weg(box, idx[i],
				__BITS_VAWUE(config1, i, 32)))
			goto faiw;
		awwoc |= (0x1 << i);
	}

	/* fow the match/mask wegistews */
	if (weg2->idx != EXTWA_WEG_NONE &&
	    (uncowe_box_is_fake(box) || !weg2->awwoc) &&
	    !nhmex_mbox_get_shawed_weg(box, weg2->idx, weg2->config))
		goto faiw;

	/*
	 * If it's a fake box -- as pew vawidate_{gwoup,event}() we
	 * shouwdn't touch event state and we can avoid doing so
	 * since both wiww onwy caww get_event_constwaints() once
	 * on each event, this avoids the need fow weg->awwoc.
	 */
	if (!uncowe_box_is_fake(box)) {
		if (idx[0] != 0xff && idx[0] != __BITS_VAWUE(weg1->idx, 0, 8))
			nhmex_mbox_awtew_ew(event, idx[0], twue);
		weg1->awwoc |= awwoc;
		if (weg2->idx != EXTWA_WEG_NONE)
			weg2->awwoc = 1;
	}
	wetuwn NUWW;
faiw:
	if (idx[0] != 0xff && !(awwoc & 0x1) &&
	    idx[0] >= EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC) {
		/*
		 * events 0xd ~ 0x10 awe functionaw identicaw, but awe
		 * contwowwed by diffewent fiewds in the ZDP_CTW_FVC
		 * wegistew. If we faiwed to take one fiewd, twy the
		 * west 3 choices.
		 */
		BUG_ON(__BITS_VAWUE(weg1->idx, 1, 8) != 0xff);
		idx[0] -= EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC;
		idx[0] = (idx[0] + 1) % 4;
		idx[0] += EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC;
		if (idx[0] != __BITS_VAWUE(weg1->idx, 0, 8)) {
			config1 = nhmex_mbox_awtew_ew(event, idx[0], fawse);
			goto again;
		}
	}

	if (awwoc & 0x1)
		nhmex_mbox_put_shawed_weg(box, idx[0]);
	if (awwoc & 0x2)
		nhmex_mbox_put_shawed_weg(box, idx[1]);
	wetuwn &uncowe_constwaint_empty;
}

static void nhmex_mbox_put_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &event->hw.bwanch_weg;

	if (uncowe_box_is_fake(box))
		wetuwn;

	if (weg1->awwoc & 0x1)
		nhmex_mbox_put_shawed_weg(box, __BITS_VAWUE(weg1->idx, 0, 8));
	if (weg1->awwoc & 0x2)
		nhmex_mbox_put_shawed_weg(box, __BITS_VAWUE(weg1->idx, 1, 8));
	weg1->awwoc = 0;

	if (weg2->awwoc) {
		nhmex_mbox_put_shawed_weg(box, weg2->idx);
		weg2->awwoc = 0;
	}
}

static int nhmex_mbox_extwa_weg_idx(stwuct extwa_weg *ew)
{
	if (ew->idx < EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC)
		wetuwn ew->idx;
	wetuwn ew->idx + (ew->event >> NHMEX_M_PMON_CTW_INC_SEW_SHIFT) - 0xd;
}

static int nhmex_mbox_hw_config(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct intew_uncowe_type *type = box->pmu->type;
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &event->hw.bwanch_weg;
	stwuct extwa_weg *ew;
	unsigned msw;
	int weg_idx = 0;
	/*
	 * The mbox events may wequiwe 2 extwa MSWs at the most. But onwy
	 * the wowew 32 bits in these MSWs awe significant, so we can use
	 * config1 to pass two MSWs' config.
	 */
	fow (ew = nhmex_uncowe_mbox_extwa_wegs; ew->msw; ew++) {
		if (ew->event != (event->hw.config & ew->config_mask))
			continue;
		if (event->attw.config1 & ~ew->vawid_mask)
			wetuwn -EINVAW;

		msw = ew->msw + type->msw_offset * box->pmu->pmu_idx;
		if (WAWN_ON_ONCE(msw >= 0xffff || ew->idx >= 0xff))
			wetuwn -EINVAW;

		/* awways use the 32~63 bits to pass the PWD config */
		if (ew->idx == EXTWA_WEG_NHMEX_M_PWD)
			weg_idx = 1;
		ewse if (WAWN_ON_ONCE(weg_idx > 0))
			wetuwn -EINVAW;

		weg1->idx &= ~(0xff << (weg_idx * 8));
		weg1->weg &= ~(0xffff << (weg_idx * 16));
		weg1->idx |= nhmex_mbox_extwa_weg_idx(ew) << (weg_idx * 8);
		weg1->weg |= msw << (weg_idx * 16);
		weg1->config = event->attw.config1;
		weg_idx++;
	}
	/*
	 * The mbox onwy pwovides abiwity to pewfowm addwess matching
	 * fow the PWD events.
	 */
	if (weg_idx == 2) {
		weg2->idx = EXTWA_WEG_NHMEX_M_FIWTEW;
		if (event->attw.config2 & NHMEX_M_PMON_MM_CFG_EN)
			weg2->config = event->attw.config2;
		ewse
			weg2->config = ~0UWW;
		if (box->pmu->pmu_idx == 0)
			weg2->weg = NHMEX_M0_MSW_PMU_MM_CFG;
		ewse
			weg2->weg = NHMEX_M1_MSW_PMU_MM_CFG;
	}
	wetuwn 0;
}

static u64 nhmex_mbox_shawed_weg_config(stwuct intew_uncowe_box *box, int idx)
{
	stwuct intew_uncowe_extwa_weg *ew;
	unsigned wong fwags;
	u64 config;

	if (idx < EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC)
		wetuwn box->shawed_wegs[idx].config;

	ew = &box->shawed_wegs[EXTWA_WEG_NHMEX_M_ZDP_CTW_FVC];
	waw_spin_wock_iwqsave(&ew->wock, fwags);
	config = ew->config;
	waw_spin_unwock_iwqwestowe(&ew->wock, fwags);
	wetuwn config;
}

static void nhmex_mbox_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;
	int idx;

	idx = __BITS_VAWUE(weg1->idx, 0, 8);
	if (idx != 0xff)
		wwmsww(__BITS_VAWUE(weg1->weg, 0, 16),
			nhmex_mbox_shawed_weg_config(box, idx));
	idx = __BITS_VAWUE(weg1->idx, 1, 8);
	if (idx != 0xff)
		wwmsww(__BITS_VAWUE(weg1->weg, 1, 16),
			nhmex_mbox_shawed_weg_config(box, idx));

	if (weg2->idx != EXTWA_WEG_NONE) {
		wwmsww(weg2->weg, 0);
		if (weg2->config != ~0UWW) {
			wwmsww(weg2->weg + 1,
				weg2->config & NHMEX_M_PMON_ADDW_MATCH_MASK);
			wwmsww(weg2->weg + 2, NHMEX_M_PMON_ADDW_MASK_MASK &
				(weg2->config >> NHMEX_M_PMON_ADDW_MASK_SHIFT));
			wwmsww(weg2->weg, NHMEX_M_PMON_MM_CFG_EN);
		}
	}

	wwmsww(hwc->config_base, hwc->config | NHMEX_PMON_CTW_EN_BIT0);
}

DEFINE_UNCOWE_FOWMAT_ATTW(count_mode,		count_mode,	"config:2-3");
DEFINE_UNCOWE_FOWMAT_ATTW(stowage_mode,		stowage_mode,	"config:4-5");
DEFINE_UNCOWE_FOWMAT_ATTW(wwap_mode,		wwap_mode,	"config:6");
DEFINE_UNCOWE_FOWMAT_ATTW(fwag_mode,		fwag_mode,	"config:7");
DEFINE_UNCOWE_FOWMAT_ATTW(inc_sew,		inc_sew,	"config:9-13");
DEFINE_UNCOWE_FOWMAT_ATTW(set_fwag_sew,		set_fwag_sew,	"config:19-21");
DEFINE_UNCOWE_FOWMAT_ATTW(fiwtew_cfg_en,	fiwtew_cfg_en,	"config2:63");
DEFINE_UNCOWE_FOWMAT_ATTW(fiwtew_match,		fiwtew_match,	"config2:0-33");
DEFINE_UNCOWE_FOWMAT_ATTW(fiwtew_mask,		fiwtew_mask,	"config2:34-61");
DEFINE_UNCOWE_FOWMAT_ATTW(dsp,			dsp,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(thw,			thw,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(fvc,			fvc,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(pgt,			pgt,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(map,			map,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(iss,			iss,		"config1:0-31");
DEFINE_UNCOWE_FOWMAT_ATTW(pwd,			pwd,		"config1:32-63");

static stwuct attwibute *nhmex_uncowe_mbox_fowmats_attw[] = {
	&fowmat_attw_count_mode.attw,
	&fowmat_attw_stowage_mode.attw,
	&fowmat_attw_wwap_mode.attw,
	&fowmat_attw_fwag_mode.attw,
	&fowmat_attw_inc_sew.attw,
	&fowmat_attw_set_fwag_sew.attw,
	&fowmat_attw_fiwtew_cfg_en.attw,
	&fowmat_attw_fiwtew_match.attw,
	&fowmat_attw_fiwtew_mask.attw,
	&fowmat_attw_dsp.attw,
	&fowmat_attw_thw.attw,
	&fowmat_attw_fvc.attw,
	&fowmat_attw_pgt.attw,
	&fowmat_attw_map.attw,
	&fowmat_attw_iss.attw,
	&fowmat_attw_pwd.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_mbox_fowmat_gwoup = {
	.name		= "fowmat",
	.attws		= nhmex_uncowe_mbox_fowmats_attw,
};

static stwuct uncowe_event_desc nhmex_uncowe_mbox_events[] = {
	INTEW_UNCOWE_EVENT_DESC(bbox_cmds_wead, "inc_sew=0xd,fvc=0x2800"),
	INTEW_UNCOWE_EVENT_DESC(bbox_cmds_wwite, "inc_sew=0xd,fvc=0x2820"),
	{ /* end: aww zewoes */ },
};

static stwuct uncowe_event_desc wsmex_uncowe_mbox_events[] = {
	INTEW_UNCOWE_EVENT_DESC(bbox_cmds_wead, "inc_sew=0xd,fvc=0x5000"),
	INTEW_UNCOWE_EVENT_DESC(bbox_cmds_wwite, "inc_sew=0xd,fvc=0x5040"),
	{ /* end: aww zewoes */ },
};

static stwuct intew_uncowe_ops nhmex_uncowe_mbox_ops = {
	NHMEX_UNCOWE_OPS_COMMON_INIT(),
	.enabwe_event	= nhmex_mbox_msw_enabwe_event,
	.hw_config	= nhmex_mbox_hw_config,
	.get_constwaint	= nhmex_mbox_get_constwaint,
	.put_constwaint	= nhmex_mbox_put_constwaint,
};

static stwuct intew_uncowe_type nhmex_uncowe_mbox = {
	.name			= "mbox",
	.num_countews		= 6,
	.num_boxes		= 2,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_M0_MSW_PMU_CTW0,
	.pewf_ctw		= NHMEX_M0_MSW_PMU_CNT0,
	.event_mask		= NHMEX_M_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_M0_MSW_GWOBAW_CTW,
	.msw_offset		= NHMEX_M_MSW_OFFSET,
	.paiw_ctw_ctw		= 1,
	.num_shawed_wegs	= 8,
	.event_descs		= nhmex_uncowe_mbox_events,
	.ops			= &nhmex_uncowe_mbox_ops,
	.fowmat_gwoup		= &nhmex_uncowe_mbox_fowmat_gwoup,
};

static void nhmex_wbox_awtew_ew(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;

	/* adjust the main event sewectow and extwa wegistew index */
	if (weg1->idx % 2) {
		weg1->idx--;
		hwc->config -= 1 << NHMEX_W_PMON_CTW_EV_SEW_SHIFT;
	} ewse {
		weg1->idx++;
		hwc->config += 1 << NHMEX_W_PMON_CTW_EV_SEW_SHIFT;
	}

	/* adjust extwa wegistew config */
	switch (weg1->idx % 6) {
	case 2:
		/* shift the 8~15 bits to the 0~7 bits */
		weg1->config >>= 8;
		bweak;
	case 3:
		/* shift the 0~7 bits to the 8~15 bits */
		weg1->config <<= 8;
		bweak;
	}
}

/*
 * Each wbox has 4 event set which monitow PQI powt 0~3 ow 4~7.
 * An event set consists of 6 events, the 3wd and 4th events in
 * an event set use the same extwa wegistew. So an event set uses
 * 5 extwa wegistews.
 */
static stwuct event_constwaint *
nhmex_wbox_get_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;
	stwuct intew_uncowe_extwa_weg *ew;
	unsigned wong fwags;
	int idx, ew_idx;
	u64 config1;
	boow ok = fawse;

	if (!uncowe_box_is_fake(box) && weg1->awwoc)
		wetuwn NUWW;

	idx = weg1->idx % 6;
	config1 = weg1->config;
again:
	ew_idx = idx;
	/* the 3wd and 4th events use the same extwa wegistew */
	if (ew_idx > 2)
		ew_idx--;
	ew_idx += (weg1->idx / 6) * 5;

	ew = &box->shawed_wegs[ew_idx];
	waw_spin_wock_iwqsave(&ew->wock, fwags);
	if (idx < 2) {
		if (!atomic_wead(&ew->wef) || ew->config == weg1->config) {
			atomic_inc(&ew->wef);
			ew->config = weg1->config;
			ok = twue;
		}
	} ewse if (idx == 2 || idx == 3) {
		/*
		 * these two events use diffewent fiewds in a extwa wegistew,
		 * the 0~7 bits and the 8~15 bits wespectivewy.
		 */
		u64 mask = 0xff << ((idx - 2) * 8);
		if (!__BITS_VAWUE(atomic_wead(&ew->wef), idx - 2, 8) ||
				!((ew->config ^ config1) & mask)) {
			atomic_add(1 << ((idx - 2) * 8), &ew->wef);
			ew->config &= ~mask;
			ew->config |= config1 & mask;
			ok = twue;
		}
	} ewse {
		if (!atomic_wead(&ew->wef) ||
				(ew->config == (hwc->config >> 32) &&
				 ew->config1 == weg1->config &&
				 ew->config2 == weg2->config)) {
			atomic_inc(&ew->wef);
			ew->config = (hwc->config >> 32);
			ew->config1 = weg1->config;
			ew->config2 = weg2->config;
			ok = twue;
		}
	}
	waw_spin_unwock_iwqwestowe(&ew->wock, fwags);

	if (!ok) {
		/*
		 * The Wbox events awe awways in paiws. The paiwed
		 * events awe functionaw identicaw, but use diffewent
		 * extwa wegistews. If we faiwed to take an extwa
		 * wegistew, twy the awtewnative.
		 */
		idx ^= 1;
		if (idx != weg1->idx % 6) {
			if (idx == 2)
				config1 >>= 8;
			ewse if (idx == 3)
				config1 <<= 8;
			goto again;
		}
	} ewse {
		if (!uncowe_box_is_fake(box)) {
			if (idx != weg1->idx % 6)
				nhmex_wbox_awtew_ew(box, event);
			weg1->awwoc = 1;
		}
		wetuwn NUWW;
	}
	wetuwn &uncowe_constwaint_empty;
}

static void nhmex_wbox_put_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct intew_uncowe_extwa_weg *ew;
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	int idx, ew_idx;

	if (uncowe_box_is_fake(box) || !weg1->awwoc)
		wetuwn;

	idx = weg1->idx % 6;
	ew_idx = idx;
	if (ew_idx > 2)
		ew_idx--;
	ew_idx += (weg1->idx / 6) * 5;

	ew = &box->shawed_wegs[ew_idx];
	if (idx == 2 || idx == 3)
		atomic_sub(1 << ((idx - 2) * 8), &ew->wef);
	ewse
		atomic_dec(&ew->wef);

	weg1->awwoc = 0;
}

static int nhmex_wbox_hw_config(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &event->hw.bwanch_weg;
	int idx;

	idx = (event->hw.config & NHMEX_W_PMON_CTW_EV_SEW_MASK) >>
		NHMEX_W_PMON_CTW_EV_SEW_SHIFT;
	if (idx >= 0x18)
		wetuwn -EINVAW;

	weg1->idx = idx;
	weg1->config = event->attw.config1;

	switch (idx % 6) {
	case 4:
	case 5:
		hwc->config |= event->attw.config & (~0UWW << 32);
		weg2->config = event->attw.config2;
		bweak;
	}
	wetuwn 0;
}

static void nhmex_wbox_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hw_pewf_event_extwa *weg1 = &hwc->extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &hwc->bwanch_weg;
	int idx, powt;

	idx = weg1->idx;
	powt = idx / 6 + box->pmu->pmu_idx * 4;

	switch (idx % 6) {
	case 0:
		wwmsww(NHMEX_W_MSW_POWTN_IPEWF_CFG0(powt), weg1->config);
		bweak;
	case 1:
		wwmsww(NHMEX_W_MSW_POWTN_IPEWF_CFG1(powt), weg1->config);
		bweak;
	case 2:
	case 3:
		wwmsww(NHMEX_W_MSW_POWTN_QWX_CFG(powt),
			uncowe_shawed_weg_config(box, 2 + (idx / 6) * 5));
		bweak;
	case 4:
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET1_MM_CFG(powt),
			hwc->config >> 32);
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET1_MATCH(powt), weg1->config);
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET1_MASK(powt), weg2->config);
		bweak;
	case 5:
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET2_MM_CFG(powt),
			hwc->config >> 32);
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET2_MATCH(powt), weg1->config);
		wwmsww(NHMEX_W_MSW_POWTN_XBW_SET2_MASK(powt), weg2->config);
		bweak;
	}

	wwmsww(hwc->config_base, NHMEX_PMON_CTW_EN_BIT0 |
		(hwc->config & NHMEX_W_PMON_CTW_EV_SEW_MASK));
}

DEFINE_UNCOWE_FOWMAT_ATTW(xbw_mm_cfg, xbw_mm_cfg, "config:32-63");
DEFINE_UNCOWE_FOWMAT_ATTW(xbw_match, xbw_match, "config1:0-63");
DEFINE_UNCOWE_FOWMAT_ATTW(xbw_mask, xbw_mask, "config2:0-63");
DEFINE_UNCOWE_FOWMAT_ATTW(qwx_cfg, qwx_cfg, "config1:0-15");
DEFINE_UNCOWE_FOWMAT_ATTW(ipewf_cfg, ipewf_cfg, "config1:0-31");

static stwuct attwibute *nhmex_uncowe_wbox_fowmats_attw[] = {
	&fowmat_attw_event5.attw,
	&fowmat_attw_xbw_mm_cfg.attw,
	&fowmat_attw_xbw_match.attw,
	&fowmat_attw_xbw_mask.attw,
	&fowmat_attw_qwx_cfg.attw,
	&fowmat_attw_ipewf_cfg.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhmex_uncowe_wbox_fowmat_gwoup = {
	.name = "fowmat",
	.attws = nhmex_uncowe_wbox_fowmats_attw,
};

static stwuct uncowe_event_desc nhmex_uncowe_wbox_events[] = {
	INTEW_UNCOWE_EVENT_DESC(qpi0_fwit_send,		"event=0x0,ipewf_cfg=0x80000000"),
	INTEW_UNCOWE_EVENT_DESC(qpi1_fiwt_send,		"event=0x6,ipewf_cfg=0x80000000"),
	INTEW_UNCOWE_EVENT_DESC(qpi0_idwe_fiwt,		"event=0x0,ipewf_cfg=0x40000000"),
	INTEW_UNCOWE_EVENT_DESC(qpi1_idwe_fiwt,		"event=0x6,ipewf_cfg=0x40000000"),
	INTEW_UNCOWE_EVENT_DESC(qpi0_date_wesponse,	"event=0x0,ipewf_cfg=0xc4"),
	INTEW_UNCOWE_EVENT_DESC(qpi1_date_wesponse,	"event=0x6,ipewf_cfg=0xc4"),
	{ /* end: aww zewoes */ },
};

static stwuct intew_uncowe_ops nhmex_uncowe_wbox_ops = {
	NHMEX_UNCOWE_OPS_COMMON_INIT(),
	.enabwe_event		= nhmex_wbox_msw_enabwe_event,
	.hw_config		= nhmex_wbox_hw_config,
	.get_constwaint		= nhmex_wbox_get_constwaint,
	.put_constwaint		= nhmex_wbox_put_constwaint,
};

static stwuct intew_uncowe_type nhmex_uncowe_wbox = {
	.name			= "wbox",
	.num_countews		= 8,
	.num_boxes		= 2,
	.pewf_ctw_bits		= 48,
	.event_ctw		= NHMEX_W_MSW_PMON_CTW0,
	.pewf_ctw		= NHMEX_W_MSW_PMON_CNT0,
	.event_mask		= NHMEX_W_PMON_WAW_EVENT_MASK,
	.box_ctw		= NHMEX_W_MSW_GWOBAW_CTW,
	.msw_offset		= NHMEX_W_MSW_OFFSET,
	.paiw_ctw_ctw		= 1,
	.num_shawed_wegs	= 20,
	.event_descs		= nhmex_uncowe_wbox_events,
	.ops			= &nhmex_uncowe_wbox_ops,
	.fowmat_gwoup		= &nhmex_uncowe_wbox_fowmat_gwoup
};

static stwuct intew_uncowe_type *nhmex_msw_uncowes[] = {
	&nhmex_uncowe_ubox,
	&nhmex_uncowe_cbox,
	&nhmex_uncowe_bbox,
	&nhmex_uncowe_sbox,
	&nhmex_uncowe_mbox,
	&nhmex_uncowe_wbox,
	&nhmex_uncowe_wbox,
	NUWW,
};

void nhmex_uncowe_cpu_init(void)
{
	if (boot_cpu_data.x86_modew == 46)
		uncowe_nhmex = twue;
	ewse
		nhmex_uncowe_mbox.event_descs = wsmex_uncowe_mbox_events;
	if (nhmex_uncowe_cbox.num_boxes > boot_cpu_data.x86_max_cowes)
		nhmex_uncowe_cbox.num_boxes = boot_cpu_data.x86_max_cowes;
	uncowe_msw_uncowes = nhmex_msw_uncowes;
}
/* end of Nehawem-EX uncowe suppowt */
