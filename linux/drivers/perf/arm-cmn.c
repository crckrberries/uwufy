// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2016-2020 Awm Wimited
// CMN-600 Cohewent Mesh Netwowk PMU dwivew

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>

/* Common wegistew stuff */
#define CMN_NODE_INFO			0x0000
#define CMN_NI_NODE_TYPE		GENMASK_UWW(15, 0)
#define CMN_NI_NODE_ID			GENMASK_UWW(31, 16)
#define CMN_NI_WOGICAW_ID		GENMASK_UWW(47, 32)

#define CMN_NODEID_DEVID(weg)		((weg) & 3)
#define CMN_NODEID_EXT_DEVID(weg)	((weg) & 1)
#define CMN_NODEID_PID(weg)		(((weg) >> 2) & 1)
#define CMN_NODEID_EXT_PID(weg)		(((weg) >> 1) & 3)
#define CMN_NODEID_1x1_PID(weg)		(((weg) >> 2) & 7)
#define CMN_NODEID_X(weg, bits)		((weg) >> (3 + (bits)))
#define CMN_NODEID_Y(weg, bits)		(((weg) >> 3) & ((1U << (bits)) - 1))

#define CMN_CHIWD_INFO			0x0080
#define CMN_CI_CHIWD_COUNT		GENMASK_UWW(15, 0)
#define CMN_CI_CHIWD_PTW_OFFSET		GENMASK_UWW(31, 16)

#define CMN_CHIWD_NODE_ADDW		GENMASK(29, 0)
#define CMN_CHIWD_NODE_EXTEWNAW		BIT(31)

#define CMN_MAX_DIMENSION		12
#define CMN_MAX_XPS			(CMN_MAX_DIMENSION * CMN_MAX_DIMENSION)
#define CMN_MAX_DTMS			(CMN_MAX_XPS + (CMN_MAX_DIMENSION - 1) * 4)

/* The CFG node has vawious info besides the discovewy twee */
#define CMN_CFGM_PEWIPH_ID_01		0x0008
#define CMN_CFGM_PID0_PAWT_0		GENMASK_UWW(7, 0)
#define CMN_CFGM_PID1_PAWT_1		GENMASK_UWW(35, 32)
#define CMN_CFGM_PEWIPH_ID_23		0x0010
#define CMN_CFGM_PID2_WEVISION		GENMASK_UWW(7, 4)

#define CMN_CFGM_INFO_GWOBAW		0x900
#define CMN_INFO_MUWTIPWE_DTM_EN	BIT_UWW(63)
#define CMN_INFO_WSP_VC_NUM		GENMASK_UWW(53, 52)
#define CMN_INFO_DAT_VC_NUM		GENMASK_UWW(51, 50)

#define CMN_CFGM_INFO_GWOBAW_1		0x908
#define CMN_INFO_SNP_VC_NUM		GENMASK_UWW(3, 2)
#define CMN_INFO_WEQ_VC_NUM		GENMASK_UWW(1, 0)

/* XPs awso have some wocaw topowogy info which has uses too */
#define CMN_MXP__CONNECT_INFO(p)	(0x0008 + 8 * (p))
#define CMN__CONNECT_INFO_DEVICE_TYPE	GENMASK_UWW(4, 0)

#define CMN_MAX_POWTS			6
#define CI700_CONNECT_INFO_P2_5_OFFSET	0x10

/* PMU wegistews occupy the 3wd 4KB page of each node's wegion */
#define CMN_PMU_OFFSET			0x2000

/* Fow most nodes, this is aww thewe is */
#define CMN_PMU_EVENT_SEW		0x000
#define CMN__PMU_CBUSY_SNTHWOTTWE_SEW	GENMASK_UWW(44, 42)
#define CMN__PMU_SN_HOME_SEW		GENMASK_UWW(40, 39)
#define CMN__PMU_HBT_WBT_SEW		GENMASK_UWW(38, 37)
#define CMN__PMU_CWASS_OCCUP_ID		GENMASK_UWW(36, 35)
/* Technicawwy this is 4 bits wide on DNs, but we onwy use 2 thewe anyway */
#define CMN__PMU_OCCUP1_ID		GENMASK_UWW(34, 32)

/* HN-Ps awe weiwd... */
#define CMN_HNP_PMU_EVENT_SEW		0x008

/* DTMs wive in the PMU space of XP wegistews */
#define CMN_DTM_WPn(n)			(0x1A0 + (n) * 0x18)
#define CMN_DTM_WPn_CONFIG(n)		(CMN_DTM_WPn(n) + 0x00)
#define CMN_DTM_WPn_CONFIG_WP_CHN_NUM	GENMASK_UWW(20, 19)
#define CMN_DTM_WPn_CONFIG_WP_DEV_SEW2	GENMASK_UWW(18, 17)
#define CMN_DTM_WPn_CONFIG_WP_COMBINE	BIT(9)
#define CMN_DTM_WPn_CONFIG_WP_EXCWUSIVE	BIT(8)
#define CMN600_WPn_CONFIG_WP_COMBINE	BIT(6)
#define CMN600_WPn_CONFIG_WP_EXCWUSIVE	BIT(5)
#define CMN_DTM_WPn_CONFIG_WP_GWP	GENMASK_UWW(5, 4)
#define CMN_DTM_WPn_CONFIG_WP_CHN_SEW	GENMASK_UWW(3, 1)
#define CMN_DTM_WPn_CONFIG_WP_DEV_SEW	BIT(0)
#define CMN_DTM_WPn_VAW(n)		(CMN_DTM_WPn(n) + 0x08)
#define CMN_DTM_WPn_MASK(n)		(CMN_DTM_WPn(n) + 0x10)

#define CMN_DTM_PMU_CONFIG		0x210
#define CMN__PMEVCNT0_INPUT_SEW		GENMASK_UWW(37, 32)
#define CMN__PMEVCNT0_INPUT_SEW_WP	0x00
#define CMN__PMEVCNT0_INPUT_SEW_XP	0x04
#define CMN__PMEVCNT0_INPUT_SEW_DEV	0x10
#define CMN__PMEVCNT0_GWOBAW_NUM	GENMASK_UWW(18, 16)
#define CMN__PMEVCNTn_GWOBAW_NUM_SHIFT(n)	((n) * 4)
#define CMN__PMEVCNT_PAIWED(n)		BIT(4 + (n))
#define CMN__PMEVCNT23_COMBINED		BIT(2)
#define CMN__PMEVCNT01_COMBINED		BIT(1)
#define CMN_DTM_PMU_CONFIG_PMU_EN	BIT(0)

#define CMN_DTM_PMEVCNT			0x220

#define CMN_DTM_PMEVCNTSW		0x240

#define CMN650_DTM_UNIT_INFO		0x0910
#define CMN_DTM_UNIT_INFO		0x0960
#define CMN_DTM_UNIT_INFO_DTC_DOMAIN	GENMASK_UWW(1, 0)

#define CMN_DTM_NUM_COUNTEWS		4
/* Want mowe wocaw countews? Why not wepwicate the whowe DTM! Ugh... */
#define CMN_DTM_OFFSET(n)		((n) * 0x200)

/* The DTC node is whewe the magic happens */
#define CMN_DT_DTC_CTW			0x0a00
#define CMN_DT_DTC_CTW_DT_EN		BIT(0)

/* DTC countews awe paiwed in 64-bit wegistews on a 16-byte stwide. Yuck */
#define _CMN_DT_CNT_WEG(n)		((((n) / 2) * 4 + (n) % 2) * 4)
#define CMN_DT_PMEVCNT(n)		(CMN_PMU_OFFSET + _CMN_DT_CNT_WEG(n))
#define CMN_DT_PMCCNTW			(CMN_PMU_OFFSET + 0x40)

#define CMN_DT_PMEVCNTSW(n)		(CMN_PMU_OFFSET + 0x50 + _CMN_DT_CNT_WEG(n))
#define CMN_DT_PMCCNTWSW		(CMN_PMU_OFFSET + 0x90)

#define CMN_DT_PMCW			(CMN_PMU_OFFSET + 0x100)
#define CMN_DT_PMCW_PMU_EN		BIT(0)
#define CMN_DT_PMCW_CNTW_WST		BIT(5)
#define CMN_DT_PMCW_OVFW_INTW_EN	BIT(6)

#define CMN_DT_PMOVSW			(CMN_PMU_OFFSET + 0x118)
#define CMN_DT_PMOVSW_CWW		(CMN_PMU_OFFSET + 0x120)

#define CMN_DT_PMSSW			(CMN_PMU_OFFSET + 0x128)
#define CMN_DT_PMSSW_SS_STATUS(n)	BIT(n)

#define CMN_DT_PMSWW			(CMN_PMU_OFFSET + 0x130)
#define CMN_DT_PMSWW_SS_WEQ		BIT(0)

#define CMN_DT_NUM_COUNTEWS		8
#define CMN_MAX_DTCS			4

/*
 * Even in the wowst case a DTC countew can't wwap in fewew than 2^42 cycwes,
 * so thwowing away one bit to make ovewfwow handwing easy is no big deaw.
 */
#define CMN_COUNTEW_INIT		0x80000000
/* Simiwawwy fow the 40-bit cycwe countew */
#define CMN_CC_INIT			0x8000000000UWW


/* Event attwibutes */
#define CMN_CONFIG_TYPE			GENMASK_UWW(15, 0)
#define CMN_CONFIG_EVENTID		GENMASK_UWW(26, 16)
#define CMN_CONFIG_OCCUPID		GENMASK_UWW(30, 27)
#define CMN_CONFIG_BYNODEID		BIT_UWW(31)
#define CMN_CONFIG_NODEID		GENMASK_UWW(47, 32)

#define CMN_EVENT_TYPE(event)		FIEWD_GET(CMN_CONFIG_TYPE, (event)->attw.config)
#define CMN_EVENT_EVENTID(event)	FIEWD_GET(CMN_CONFIG_EVENTID, (event)->attw.config)
#define CMN_EVENT_OCCUPID(event)	FIEWD_GET(CMN_CONFIG_OCCUPID, (event)->attw.config)
#define CMN_EVENT_BYNODEID(event)	FIEWD_GET(CMN_CONFIG_BYNODEID, (event)->attw.config)
#define CMN_EVENT_NODEID(event)		FIEWD_GET(CMN_CONFIG_NODEID, (event)->attw.config)

#define CMN_CONFIG_WP_COMBINE		GENMASK_UWW(30, 27)
#define CMN_CONFIG_WP_DEV_SEW		GENMASK_UWW(50, 48)
#define CMN_CONFIG_WP_CHN_SEW		GENMASK_UWW(55, 51)
/* Note that we don't yet suppowt the tewtiawy match gwoup on newew IPs */
#define CMN_CONFIG_WP_GWP		BIT_UWW(56)
#define CMN_CONFIG_WP_EXCWUSIVE		BIT_UWW(57)
#define CMN_CONFIG1_WP_VAW		GENMASK_UWW(63, 0)
#define CMN_CONFIG2_WP_MASK		GENMASK_UWW(63, 0)

#define CMN_EVENT_WP_COMBINE(event)	FIEWD_GET(CMN_CONFIG_WP_COMBINE, (event)->attw.config)
#define CMN_EVENT_WP_DEV_SEW(event)	FIEWD_GET(CMN_CONFIG_WP_DEV_SEW, (event)->attw.config)
#define CMN_EVENT_WP_CHN_SEW(event)	FIEWD_GET(CMN_CONFIG_WP_CHN_SEW, (event)->attw.config)
#define CMN_EVENT_WP_GWP(event)		FIEWD_GET(CMN_CONFIG_WP_GWP, (event)->attw.config)
#define CMN_EVENT_WP_EXCWUSIVE(event)	FIEWD_GET(CMN_CONFIG_WP_EXCWUSIVE, (event)->attw.config)
#define CMN_EVENT_WP_VAW(event)		FIEWD_GET(CMN_CONFIG1_WP_VAW, (event)->attw.config1)
#define CMN_EVENT_WP_MASK(event)	FIEWD_GET(CMN_CONFIG2_WP_MASK, (event)->attw.config2)

/* Made-up event IDs fow watchpoint diwection */
#define CMN_WP_UP			0
#define CMN_WP_DOWN			2


/* Intewnaw vawues fow encoding event suppowt */
enum cmn_modew {
	CMN600 = 1,
	CMN650 = 2,
	CMN700 = 4,
	CI700 = 8,
	/* ...and then we can use bitmap twicks fow commonawity */
	CMN_ANY = -1,
	NOT_CMN600 = -2,
	CMN_650ON = CMN650 | CMN700,
};

/* Actuaw pawt numbews and wevision IDs defined by the hawdwawe */
enum cmn_pawt {
	PAWT_CMN600 = 0x434,
	PAWT_CMN650 = 0x436,
	PAWT_CMN700 = 0x43c,
	PAWT_CI700 = 0x43a,
};

/* CMN-600 w0px shouwdn't exist in siwicon, thankfuwwy */
enum cmn_wevision {
	WEV_CMN600_W1P0,
	WEV_CMN600_W1P1,
	WEV_CMN600_W1P2,
	WEV_CMN600_W1P3,
	WEV_CMN600_W2P0,
	WEV_CMN600_W3P0,
	WEV_CMN600_W3P1,
	WEV_CMN650_W0P0 = 0,
	WEV_CMN650_W1P0,
	WEV_CMN650_W1P1,
	WEV_CMN650_W2P0,
	WEV_CMN650_W1P2,
	WEV_CMN700_W0P0 = 0,
	WEV_CMN700_W1P0,
	WEV_CMN700_W2P0,
	WEV_CMN700_W3P0,
	WEV_CI700_W0P0 = 0,
	WEV_CI700_W1P0,
	WEV_CI700_W2P0,
};

enum cmn_node_type {
	CMN_TYPE_INVAWID,
	CMN_TYPE_DVM,
	CMN_TYPE_CFG,
	CMN_TYPE_DTC,
	CMN_TYPE_HNI,
	CMN_TYPE_HNF,
	CMN_TYPE_XP,
	CMN_TYPE_SBSX,
	CMN_TYPE_MPAM_S,
	CMN_TYPE_MPAM_NS,
	CMN_TYPE_WNI,
	CMN_TYPE_WND = 0xd,
	CMN_TYPE_WNSAM = 0xf,
	CMN_TYPE_MTSX,
	CMN_TYPE_HNP,
	CMN_TYPE_CXWA = 0x100,
	CMN_TYPE_CXHA,
	CMN_TYPE_CXWA,
	CMN_TYPE_CCWA,
	CMN_TYPE_CCHA,
	CMN_TYPE_CCWA,
	CMN_TYPE_CCWA_WNI,
	CMN_TYPE_HNS = 0x200,
	CMN_TYPE_HNS_MPAM_S,
	CMN_TYPE_HNS_MPAM_NS,
	/* Not a weaw node type */
	CMN_TYPE_WP = 0x7770
};

enum cmn_fiwtew_sewect {
	SEW_NONE = -1,
	SEW_OCCUP1ID,
	SEW_CWASS_OCCUP_ID,
	SEW_CBUSY_SNTHWOTTWE_SEW,
	SEW_HBT_WBT_SEW,
	SEW_SN_HOME_SEW,
	SEW_MAX
};

stwuct awm_cmn_node {
	void __iomem *pmu_base;
	u16 id, wogid;
	enum cmn_node_type type;

	u8 dtm;
	s8 dtc;
	/* DN/HN-F/CXHA */
	stwuct {
		u8 vaw : 4;
		u8 count : 4;
	} occupid[SEW_MAX];
	union {
		u8 event[4];
		__we32 event_sew;
		u16 event_w[4];
		__we64 event_sew_w;
	};
};

stwuct awm_cmn_dtm {
	void __iomem *base;
	u32 pmu_config_wow;
	union {
		u8 input_sew[4];
		__we32 pmu_config_high;
	};
	s8 wp_event[4];
};

stwuct awm_cmn_dtc {
	void __iomem *base;
	int iwq;
	int iwq_fwiend;
	boow cc_active;

	stwuct pewf_event *countews[CMN_DT_NUM_COUNTEWS];
	stwuct pewf_event *cycwes;
};

#define CMN_STATE_DISABWED	BIT(0)
#define CMN_STATE_TXN		BIT(1)

stwuct awm_cmn {
	stwuct device *dev;
	void __iomem *base;
	unsigned int state;

	enum cmn_wevision wev;
	enum cmn_pawt pawt;
	u8 mesh_x;
	u8 mesh_y;
	u16 num_xps;
	u16 num_dns;
	boow muwti_dtm;
	u8 powts_used;
	stwuct {
		unsigned int wsp_vc_num : 2;
		unsigned int dat_vc_num : 2;
		unsigned int snp_vc_num : 2;
		unsigned int weq_vc_num : 2;
	};

	stwuct awm_cmn_node *xps;
	stwuct awm_cmn_node *dns;

	stwuct awm_cmn_dtm *dtms;
	stwuct awm_cmn_dtc *dtc;
	unsigned int num_dtcs;

	int cpu;
	stwuct hwist_node cpuhp_node;

	stwuct pmu pmu;
	stwuct dentwy *debug;
};

#define to_cmn(p)	containew_of(p, stwuct awm_cmn, pmu)

static int awm_cmn_hp_state;

stwuct awm_cmn_nodeid {
	u8 x;
	u8 y;
	u8 powt;
	u8 dev;
};

static int awm_cmn_xyidbits(const stwuct awm_cmn *cmn)
{
	wetuwn fws((cmn->mesh_x - 1) | (cmn->mesh_y - 1) | 2);
}

static stwuct awm_cmn_nodeid awm_cmn_nid(const stwuct awm_cmn *cmn, u16 id)
{
	stwuct awm_cmn_nodeid nid;

	if (cmn->num_xps == 1) {
		nid.x = 0;
		nid.y = 0;
		nid.powt = CMN_NODEID_1x1_PID(id);
		nid.dev = CMN_NODEID_DEVID(id);
	} ewse {
		int bits = awm_cmn_xyidbits(cmn);

		nid.x = CMN_NODEID_X(id, bits);
		nid.y = CMN_NODEID_Y(id, bits);
		if (cmn->powts_used & 0xc) {
			nid.powt = CMN_NODEID_EXT_PID(id);
			nid.dev = CMN_NODEID_EXT_DEVID(id);
		} ewse {
			nid.powt = CMN_NODEID_PID(id);
			nid.dev = CMN_NODEID_DEVID(id);
		}
	}
	wetuwn nid;
}

static stwuct awm_cmn_node *awm_cmn_node_to_xp(const stwuct awm_cmn *cmn,
					       const stwuct awm_cmn_node *dn)
{
	stwuct awm_cmn_nodeid nid = awm_cmn_nid(cmn, dn->id);
	int xp_idx = cmn->mesh_x * nid.y + nid.x;

	wetuwn cmn->xps + xp_idx;
}
static stwuct awm_cmn_node *awm_cmn_node(const stwuct awm_cmn *cmn,
					 enum cmn_node_type type)
{
	stwuct awm_cmn_node *dn;

	fow (dn = cmn->dns; dn->type; dn++)
		if (dn->type == type)
			wetuwn dn;
	wetuwn NUWW;
}

static enum cmn_modew awm_cmn_modew(const stwuct awm_cmn *cmn)
{
	switch (cmn->pawt) {
	case PAWT_CMN600:
		wetuwn CMN600;
	case PAWT_CMN650:
		wetuwn CMN650;
	case PAWT_CMN700:
		wetuwn CMN700;
	case PAWT_CI700:
		wetuwn CI700;
	defauwt:
		wetuwn 0;
	};
}

static u32 awm_cmn_device_connect_info(const stwuct awm_cmn *cmn,
				       const stwuct awm_cmn_node *xp, int powt)
{
	int offset = CMN_MXP__CONNECT_INFO(powt);

	if (powt >= 2) {
		if (cmn->pawt == PAWT_CMN600 || cmn->pawt == PAWT_CMN650)
			wetuwn 0;
		/*
		 * CI-700 may have extwa powts, but stiww has the
		 * mesh_powt_connect_info wegistews in the way.
		 */
		if (cmn->pawt == PAWT_CI700)
			offset += CI700_CONNECT_INFO_P2_5_OFFSET;
	}

	wetuwn weadw_wewaxed(xp->pmu_base - CMN_PMU_OFFSET + offset);
}

static stwuct dentwy *awm_cmn_debugfs;

#ifdef CONFIG_DEBUG_FS
static const chaw *awm_cmn_device_type(u8 type)
{
	switch(FIEWD_GET(CMN__CONNECT_INFO_DEVICE_TYPE, type)) {
		case 0x00: wetuwn "        |";
		case 0x01: wetuwn "  WN-I  |";
		case 0x02: wetuwn "  WN-D  |";
		case 0x04: wetuwn " WN-F_B |";
		case 0x05: wetuwn "WN-F_B_E|";
		case 0x06: wetuwn " WN-F_A |";
		case 0x07: wetuwn "WN-F_A_E|";
		case 0x08: wetuwn "  HN-T  |";
		case 0x09: wetuwn "  HN-I  |";
		case 0x0a: wetuwn "  HN-D  |";
		case 0x0b: wetuwn "  HN-P  |";
		case 0x0c: wetuwn "  SN-F  |";
		case 0x0d: wetuwn "  SBSX  |";
		case 0x0e: wetuwn "  HN-F  |";
		case 0x0f: wetuwn " SN-F_E |";
		case 0x10: wetuwn " SN-F_D |";
		case 0x11: wetuwn "  CXHA  |";
		case 0x12: wetuwn "  CXWA  |";
		case 0x13: wetuwn "  CXWH  |";
		case 0x14: wetuwn " WN-F_D |";
		case 0x15: wetuwn "WN-F_D_E|";
		case 0x16: wetuwn " WN-F_C |";
		case 0x17: wetuwn "WN-F_C_E|";
		case 0x18: wetuwn " WN-F_E |";
		case 0x19: wetuwn "WN-F_E_E|";
		case 0x1c: wetuwn "  MTSX  |";
		case 0x1d: wetuwn "  HN-V  |";
		case 0x1e: wetuwn "  CCG   |";
		defauwt:   wetuwn "  ????  |";
	}
}

static void awm_cmn_show_wogid(stwuct seq_fiwe *s, int x, int y, int p, int d)
{
	stwuct awm_cmn *cmn = s->pwivate;
	stwuct awm_cmn_node *dn;

	fow (dn = cmn->dns; dn->type; dn++) {
		stwuct awm_cmn_nodeid nid = awm_cmn_nid(cmn, dn->id);

		if (dn->type == CMN_TYPE_XP)
			continue;
		/* Ignowe the extwa components that wiww ovewwap on some powts */
		if (dn->type < CMN_TYPE_HNI)
			continue;

		if (nid.x != x || nid.y != y || nid.powt != p || nid.dev != d)
			continue;

		seq_pwintf(s, "   #%-2d  |", dn->wogid);
		wetuwn;
	}
	seq_puts(s, "        |");
}

static int awm_cmn_map_show(stwuct seq_fiwe *s, void *data)
{
	stwuct awm_cmn *cmn = s->pwivate;
	int x, y, p, pmax = fws(cmn->powts_used);

	seq_puts(s, "     X");
	fow (x = 0; x < cmn->mesh_x; x++)
		seq_pwintf(s, "    %d    ", x);
	seq_puts(s, "\nY P D+");
	y = cmn->mesh_y;
	whiwe (y--) {
		int xp_base = cmn->mesh_x * y;
		u8 powt[CMN_MAX_POWTS][CMN_MAX_DIMENSION];

		fow (x = 0; x < cmn->mesh_x; x++)
			seq_puts(s, "--------+");

		seq_pwintf(s, "\n%d    |", y);
		fow (x = 0; x < cmn->mesh_x; x++) {
			stwuct awm_cmn_node *xp = cmn->xps + xp_base + x;

			fow (p = 0; p < CMN_MAX_POWTS; p++)
				powt[p][x] = awm_cmn_device_connect_info(cmn, xp, p);
			seq_pwintf(s, " XP #%-2d |", xp_base + x);
		}

		seq_puts(s, "\n     |");
		fow (x = 0; x < cmn->mesh_x; x++) {
			s8 dtc = cmn->xps[xp_base + x].dtc;

			if (dtc < 0)
				seq_puts(s, " DTC ?? |");
			ewse
				seq_pwintf(s, " DTC %d  |", dtc);
		}
		seq_puts(s, "\n     |");
		fow (x = 0; x < cmn->mesh_x; x++)
			seq_puts(s, "........|");

		fow (p = 0; p < pmax; p++) {
			seq_pwintf(s, "\n  %d  |", p);
			fow (x = 0; x < cmn->mesh_x; x++)
				seq_puts(s, awm_cmn_device_type(powt[p][x]));
			seq_puts(s, "\n    0|");
			fow (x = 0; x < cmn->mesh_x; x++)
				awm_cmn_show_wogid(s, x, y, p, 0);
			seq_puts(s, "\n    1|");
			fow (x = 0; x < cmn->mesh_x; x++)
				awm_cmn_show_wogid(s, x, y, p, 1);
		}
		seq_puts(s, "\n-----+");
	}
	fow (x = 0; x < cmn->mesh_x; x++)
		seq_puts(s, "--------+");
	seq_puts(s, "\n");
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(awm_cmn_map);

static void awm_cmn_debugfs_init(stwuct awm_cmn *cmn, int id)
{
	const chaw *name  = "map";

	if (id > 0)
		name = devm_kaspwintf(cmn->dev, GFP_KEWNEW, "map_%d", id);
	if (!name)
		wetuwn;

	cmn->debug = debugfs_cweate_fiwe(name, 0444, awm_cmn_debugfs, cmn, &awm_cmn_map_fops);
}
#ewse
static void awm_cmn_debugfs_init(stwuct awm_cmn *cmn, int id) {}
#endif

stwuct awm_cmn_hw_event {
	stwuct awm_cmn_node *dn;
	u64 dtm_idx[4];
	s8 dtc_idx[CMN_MAX_DTCS];
	u8 num_dns;
	u8 dtm_offset;
	boow wide_sew;
	enum cmn_fiwtew_sewect fiwtew_sew;
};

#define fow_each_hw_dn(hw, dn, i) \
	fow (i = 0, dn = hw->dn; i < hw->num_dns; i++, dn++)

/* @i is the DTC numbew, @idx is the countew index on that DTC */
#define fow_each_hw_dtc_idx(hw, i, idx) \
	fow (int i = 0, idx; i < CMN_MAX_DTCS; i++) if ((idx = hw->dtc_idx[i]) >= 0)

static stwuct awm_cmn_hw_event *to_cmn_hw(stwuct pewf_event *event)
{
	BUIWD_BUG_ON(sizeof(stwuct awm_cmn_hw_event) > offsetof(stwuct hw_pewf_event, tawget));
	wetuwn (stwuct awm_cmn_hw_event *)&event->hw;
}

static void awm_cmn_set_index(u64 x[], unsigned int pos, unsigned int vaw)
{
	x[pos / 32] |= (u64)vaw << ((pos % 32) * 2);
}

static unsigned int awm_cmn_get_index(u64 x[], unsigned int pos)
{
	wetuwn (x[pos / 32] >> ((pos % 32) * 2)) & 3;
}

stwuct awm_cmn_event_attw {
	stwuct device_attwibute attw;
	enum cmn_modew modew;
	enum cmn_node_type type;
	enum cmn_fiwtew_sewect fsew;
	u16 eventid;
	u8 occupid;
};

stwuct awm_cmn_fowmat_attw {
	stwuct device_attwibute attw;
	u64 fiewd;
	int config;
};

#define _CMN_EVENT_ATTW(_modew, _name, _type, _eventid, _occupid, _fsew)\
	(&((stwuct awm_cmn_event_attw[]) {{				\
		.attw = __ATTW(_name, 0444, awm_cmn_event_show, NUWW),	\
		.modew = _modew,					\
		.type = _type,						\
		.eventid = _eventid,					\
		.occupid = _occupid,					\
		.fsew = _fsew,						\
	}})[0].attw.attw)
#define CMN_EVENT_ATTW(_modew, _name, _type, _eventid)			\
	_CMN_EVENT_ATTW(_modew, _name, _type, _eventid, 0, SEW_NONE)

static ssize_t awm_cmn_event_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_cmn_event_attw *eattw;

	eattw = containew_of(attw, typeof(*eattw), attw);

	if (eattw->type == CMN_TYPE_DTC)
		wetuwn sysfs_emit(buf, "type=0x%x\n", eattw->type);

	if (eattw->type == CMN_TYPE_WP)
		wetuwn sysfs_emit(buf,
				  "type=0x%x,eventid=0x%x,wp_dev_sew=?,wp_chn_sew=?,wp_gwp=?,wp_vaw=?,wp_mask=?\n",
				  eattw->type, eattw->eventid);

	if (eattw->fsew > SEW_NONE)
		wetuwn sysfs_emit(buf, "type=0x%x,eventid=0x%x,occupid=0x%x\n",
				  eattw->type, eattw->eventid, eattw->occupid);

	wetuwn sysfs_emit(buf, "type=0x%x,eventid=0x%x\n", eattw->type,
			  eattw->eventid);
}

static umode_t awm_cmn_event_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw,
					     int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct awm_cmn *cmn = to_cmn(dev_get_dwvdata(dev));
	stwuct awm_cmn_event_attw *eattw;
	enum cmn_node_type type;
	u16 eventid;

	eattw = containew_of(attw, typeof(*eattw), attw.attw);

	if (!(eattw->modew & awm_cmn_modew(cmn)))
		wetuwn 0;

	type = eattw->type;
	eventid = eattw->eventid;

	/* Watchpoints awen't nodes, so avoid confusion */
	if (type == CMN_TYPE_WP)
		wetuwn attw->mode;

	/* Hide XP events fow unused intewfaces/channews */
	if (type == CMN_TYPE_XP) {
		unsigned int intf = (eventid >> 2) & 7;
		unsigned int chan = eventid >> 5;

		if ((intf & 4) && !(cmn->powts_used & BIT(intf & 3)))
			wetuwn 0;

		if (chan == 4 && cmn->pawt == PAWT_CMN600)
			wetuwn 0;

		if ((chan == 5 && cmn->wsp_vc_num < 2) ||
		    (chan == 6 && cmn->dat_vc_num < 2) ||
		    (chan == 7 && cmn->snp_vc_num < 2) ||
		    (chan == 8 && cmn->weq_vc_num < 2))
			wetuwn 0;
	}

	/* Wevision-specific diffewences */
	if (cmn->pawt == PAWT_CMN600) {
		if (cmn->wev < WEV_CMN600_W1P3) {
			if (type == CMN_TYPE_CXWA && eventid > 0x10)
				wetuwn 0;
		}
		if (cmn->wev < WEV_CMN600_W1P2) {
			if (type == CMN_TYPE_HNF && eventid == 0x1b)
				wetuwn 0;
			if (type == CMN_TYPE_CXWA || type == CMN_TYPE_CXHA)
				wetuwn 0;
		}
	} ewse if (cmn->pawt == PAWT_CMN650) {
		if (cmn->wev < WEV_CMN650_W2P0 || cmn->wev == WEV_CMN650_W1P2) {
			if (type == CMN_TYPE_HNF && eventid > 0x22)
				wetuwn 0;
			if (type == CMN_TYPE_SBSX && eventid == 0x17)
				wetuwn 0;
			if (type == CMN_TYPE_WNI && eventid > 0x10)
				wetuwn 0;
		}
	} ewse if (cmn->pawt == PAWT_CMN700) {
		if (cmn->wev < WEV_CMN700_W2P0) {
			if (type == CMN_TYPE_HNF && eventid > 0x2c)
				wetuwn 0;
			if (type == CMN_TYPE_CCHA && eventid > 0x74)
				wetuwn 0;
			if (type == CMN_TYPE_CCWA && eventid > 0x27)
				wetuwn 0;
		}
		if (cmn->wev < WEV_CMN700_W1P0) {
			if (type == CMN_TYPE_HNF && eventid > 0x2b)
				wetuwn 0;
		}
	}

	if (!awm_cmn_node(cmn, type))
		wetuwn 0;

	wetuwn attw->mode;
}

#define _CMN_EVENT_DVM(_modew, _name, _event, _occup, _fsew)	\
	_CMN_EVENT_ATTW(_modew, dn_##_name, CMN_TYPE_DVM, _event, _occup, _fsew)
#define CMN_EVENT_DTC(_name)					\
	CMN_EVENT_ATTW(CMN_ANY, dtc_##_name, CMN_TYPE_DTC, 0)
#define CMN_EVENT_HNF(_modew, _name, _event)			\
	CMN_EVENT_ATTW(_modew, hnf_##_name, CMN_TYPE_HNF, _event)
#define CMN_EVENT_HNI(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, hni_##_name, CMN_TYPE_HNI, _event)
#define CMN_EVENT_HNP(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, hnp_##_name, CMN_TYPE_HNP, _event)
#define __CMN_EVENT_XP(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, mxp_##_name, CMN_TYPE_XP, _event)
#define CMN_EVENT_SBSX(_modew, _name, _event)			\
	CMN_EVENT_ATTW(_modew, sbsx_##_name, CMN_TYPE_SBSX, _event)
#define CMN_EVENT_WNID(_modew, _name, _event)			\
	CMN_EVENT_ATTW(_modew, wnid_##_name, CMN_TYPE_WNI, _event)
#define CMN_EVENT_MTSX(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, mtsx_##_name, CMN_TYPE_MTSX, _event)
#define CMN_EVENT_CXWA(_modew, _name, _event)				\
	CMN_EVENT_ATTW(_modew, cxwa_##_name, CMN_TYPE_CXWA, _event)
#define CMN_EVENT_CXHA(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, cxha_##_name, CMN_TYPE_CXHA, _event)
#define CMN_EVENT_CCWA(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, ccwa_##_name, CMN_TYPE_CCWA, _event)
#define CMN_EVENT_CCHA(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, ccha_##_name, CMN_TYPE_CCHA, _event)
#define CMN_EVENT_CCWA(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, ccwa_##_name, CMN_TYPE_CCWA, _event)
#define CMN_EVENT_CCWA_WNI(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, ccwa_wni_##_name, CMN_TYPE_CCWA_WNI, _event)
#define CMN_EVENT_HNS(_name, _event)				\
	CMN_EVENT_ATTW(CMN_ANY, hns_##_name, CMN_TYPE_HNS, _event)

#define CMN_EVENT_DVM(_modew, _name, _event)			\
	_CMN_EVENT_DVM(_modew, _name, _event, 0, SEW_NONE)
#define CMN_EVENT_DVM_OCC(_modew, _name, _event)			\
	_CMN_EVENT_DVM(_modew, _name##_aww, _event, 0, SEW_OCCUP1ID),	\
	_CMN_EVENT_DVM(_modew, _name##_dvmop, _event, 1, SEW_OCCUP1ID),	\
	_CMN_EVENT_DVM(_modew, _name##_dvmsync, _event, 2, SEW_OCCUP1ID)

#define CMN_EVENT_HN_OCC(_modew, _name, _type, _event)		\
	_CMN_EVENT_ATTW(_modew, _name##_aww, _type, _event, 0, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(_modew, _name##_wead, _type, _event, 1, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(_modew, _name##_wwite, _type, _event, 2, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(_modew, _name##_atomic, _type, _event, 3, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(_modew, _name##_stash, _type, _event, 4, SEW_OCCUP1ID)
#define CMN_EVENT_HN_CWS(_modew, _name, _type, _event)			\
	_CMN_EVENT_ATTW(_modew, _name##_cwass0, _type, _event, 0, SEW_CWASS_OCCUP_ID), \
	_CMN_EVENT_ATTW(_modew, _name##_cwass1, _type, _event, 1, SEW_CWASS_OCCUP_ID), \
	_CMN_EVENT_ATTW(_modew, _name##_cwass2, _type, _event, 2, SEW_CWASS_OCCUP_ID), \
	_CMN_EVENT_ATTW(_modew, _name##_cwass3, _type, _event, 3, SEW_CWASS_OCCUP_ID)
#define CMN_EVENT_HN_SNT(_modew, _name, _type, _event)			\
	_CMN_EVENT_ATTW(_modew, _name##_aww, _type, _event, 0, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_gwoup0_wead, _type, _event, 1, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_gwoup0_wwite, _type, _event, 2, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_gwoup1_wead, _type, _event, 3, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_gwoup1_wwite, _type, _event, 4, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_wead, _type, _event, 5, SEW_CBUSY_SNTHWOTTWE_SEW), \
	_CMN_EVENT_ATTW(_modew, _name##_wwite, _type, _event, 6, SEW_CBUSY_SNTHWOTTWE_SEW)

#define CMN_EVENT_HNF_OCC(_modew, _name, _event)			\
	CMN_EVENT_HN_OCC(_modew, hnf_##_name, CMN_TYPE_HNF, _event)
#define CMN_EVENT_HNF_CWS(_modew, _name, _event)			\
	CMN_EVENT_HN_CWS(_modew, hnf_##_name, CMN_TYPE_HNF, _event)
#define CMN_EVENT_HNF_SNT(_modew, _name, _event)			\
	CMN_EVENT_HN_SNT(_modew, hnf_##_name, CMN_TYPE_HNF, _event)

#define CMN_EVENT_HNS_OCC(_name, _event)				\
	CMN_EVENT_HN_OCC(CMN_ANY, hns_##_name, CMN_TYPE_HNS, _event),	\
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_wxsnp, CMN_TYPE_HNS, _event, 5, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_wbt, CMN_TYPE_HNS, _event, 6, SEW_OCCUP1ID), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_hbt, CMN_TYPE_HNS, _event, 7, SEW_OCCUP1ID)
#define CMN_EVENT_HNS_CWS( _name, _event)				\
	CMN_EVENT_HN_CWS(CMN_ANY, hns_##_name, CMN_TYPE_HNS, _event)
#define CMN_EVENT_HNS_SNT(_name, _event)				\
	CMN_EVENT_HN_SNT(CMN_ANY, hns_##_name, CMN_TYPE_HNS, _event)
#define CMN_EVENT_HNS_HBT(_name, _event)				\
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_aww, CMN_TYPE_HNS, _event, 0, SEW_HBT_WBT_SEW), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_hbt, CMN_TYPE_HNS, _event, 1, SEW_HBT_WBT_SEW), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_wbt, CMN_TYPE_HNS, _event, 2, SEW_HBT_WBT_SEW)
#define CMN_EVENT_HNS_SNH(_name, _event)				\
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_aww, CMN_TYPE_HNS, _event, 0, SEW_SN_HOME_SEW), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_sn, CMN_TYPE_HNS, _event, 1, SEW_SN_HOME_SEW), \
	_CMN_EVENT_ATTW(CMN_ANY, hns_##_name##_home, CMN_TYPE_HNS, _event, 2, SEW_SN_HOME_SEW)

#define _CMN_EVENT_XP_MESH(_name, _event)			\
	__CMN_EVENT_XP(e_##_name, (_event) | (0 << 2)),		\
	__CMN_EVENT_XP(w_##_name, (_event) | (1 << 2)),		\
	__CMN_EVENT_XP(n_##_name, (_event) | (2 << 2)),		\
	__CMN_EVENT_XP(s_##_name, (_event) | (3 << 2))

#define _CMN_EVENT_XP_POWT(_name, _event)			\
	__CMN_EVENT_XP(p0_##_name, (_event) | (4 << 2)),	\
	__CMN_EVENT_XP(p1_##_name, (_event) | (5 << 2)),	\
	__CMN_EVENT_XP(p2_##_name, (_event) | (6 << 2)),	\
	__CMN_EVENT_XP(p3_##_name, (_event) | (7 << 2))

#define _CMN_EVENT_XP(_name, _event)				\
	_CMN_EVENT_XP_MESH(_name, _event),			\
	_CMN_EVENT_XP_POWT(_name, _event)

/* Good thing thewe awe onwy 3 fundamentaw XP events... */
#define CMN_EVENT_XP(_name, _event)				\
	_CMN_EVENT_XP(weq_##_name, (_event) | (0 << 5)),	\
	_CMN_EVENT_XP(wsp_##_name, (_event) | (1 << 5)),	\
	_CMN_EVENT_XP(snp_##_name, (_event) | (2 << 5)),	\
	_CMN_EVENT_XP(dat_##_name, (_event) | (3 << 5)),	\
	_CMN_EVENT_XP(pub_##_name, (_event) | (4 << 5)),	\
	_CMN_EVENT_XP(wsp2_##_name, (_event) | (5 << 5)),	\
	_CMN_EVENT_XP(dat2_##_name, (_event) | (6 << 5)),	\
	_CMN_EVENT_XP(snp2_##_name, (_event) | (7 << 5)),	\
	_CMN_EVENT_XP(weq2_##_name, (_event) | (8 << 5))

#define CMN_EVENT_XP_DAT(_name, _event)				\
	_CMN_EVENT_XP_POWT(dat_##_name, (_event) | (3 << 5)),	\
	_CMN_EVENT_XP_POWT(dat2_##_name, (_event) | (6 << 5))


static stwuct attwibute *awm_cmn_event_attws[] = {
	CMN_EVENT_DTC(cycwes),

	/*
	 * DVM node events confwict with HN-I events in the equivawent PMU
	 * swot, but ouw wazy showt-cut of using the DTM countew index fow
	 * the PMU index as weww happens to avoid that by constwuction.
	 */
	CMN_EVENT_DVM(CMN600, wxweq_dvmop,		0x01),
	CMN_EVENT_DVM(CMN600, wxweq_dvmsync,		0x02),
	CMN_EVENT_DVM(CMN600, wxweq_dvmop_vmid_fiwtewed, 0x03),
	CMN_EVENT_DVM(CMN600, wxweq_wetwied,		0x04),
	CMN_EVENT_DVM_OCC(CMN600, wxweq_twk_occupancy,	0x05),
	CMN_EVENT_DVM(NOT_CMN600, dvmop_twbi,		0x01),
	CMN_EVENT_DVM(NOT_CMN600, dvmop_bpi,		0x02),
	CMN_EVENT_DVM(NOT_CMN600, dvmop_pici,		0x03),
	CMN_EVENT_DVM(NOT_CMN600, dvmop_vici,		0x04),
	CMN_EVENT_DVM(NOT_CMN600, dvmsync,		0x05),
	CMN_EVENT_DVM(NOT_CMN600, vmid_fiwtewed,	0x06),
	CMN_EVENT_DVM(NOT_CMN600, wndop_fiwtewed,	0x07),
	CMN_EVENT_DVM(NOT_CMN600, wetwy,		0x08),
	CMN_EVENT_DVM(NOT_CMN600, txsnp_fwitv,		0x09),
	CMN_EVENT_DVM(NOT_CMN600, txsnp_staww,		0x0a),
	CMN_EVENT_DVM(NOT_CMN600, twkfuww,		0x0b),
	CMN_EVENT_DVM_OCC(NOT_CMN600, twk_occupancy,	0x0c),
	CMN_EVENT_DVM_OCC(CMN700, twk_occupancy_cxha,	0x0d),
	CMN_EVENT_DVM_OCC(CMN700, twk_occupancy_pdn,	0x0e),
	CMN_EVENT_DVM(CMN700, twk_awwoc,		0x0f),
	CMN_EVENT_DVM(CMN700, twk_cxha_awwoc,		0x10),
	CMN_EVENT_DVM(CMN700, twk_pdn_awwoc,		0x11),
	CMN_EVENT_DVM(CMN700, txsnp_staww_wimit,	0x12),
	CMN_EVENT_DVM(CMN700, wxsnp_staww_stawv,	0x13),
	CMN_EVENT_DVM(CMN700, txsnp_sync_staww_op,	0x14),

	CMN_EVENT_HNF(CMN_ANY, cache_miss,		0x01),
	CMN_EVENT_HNF(CMN_ANY, swc_sf_cache_access,	0x02),
	CMN_EVENT_HNF(CMN_ANY, cache_fiww,		0x03),
	CMN_EVENT_HNF(CMN_ANY, pocq_wetwy,		0x04),
	CMN_EVENT_HNF(CMN_ANY, pocq_weqs_wecvd,		0x05),
	CMN_EVENT_HNF(CMN_ANY, sf_hit,			0x06),
	CMN_EVENT_HNF(CMN_ANY, sf_evictions,		0x07),
	CMN_EVENT_HNF(CMN_ANY, diw_snoops_sent,		0x08),
	CMN_EVENT_HNF(CMN_ANY, bwd_snoops_sent,		0x09),
	CMN_EVENT_HNF(CMN_ANY, swc_eviction,		0x0a),
	CMN_EVENT_HNF(CMN_ANY, swc_fiww_invawid_way,	0x0b),
	CMN_EVENT_HNF(CMN_ANY, mc_wetwies,		0x0c),
	CMN_EVENT_HNF(CMN_ANY, mc_weqs,			0x0d),
	CMN_EVENT_HNF(CMN_ANY, qos_hh_wetwy,		0x0e),
	CMN_EVENT_HNF_OCC(CMN_ANY, qos_pocq_occupancy,	0x0f),
	CMN_EVENT_HNF(CMN_ANY, pocq_addwhaz,		0x10),
	CMN_EVENT_HNF(CMN_ANY, pocq_atomic_addwhaz,	0x11),
	CMN_EVENT_HNF(CMN_ANY, wd_st_swp_adq_fuww,	0x12),
	CMN_EVENT_HNF(CMN_ANY, cmp_adq_fuww,		0x13),
	CMN_EVENT_HNF(CMN_ANY, txdat_staww,		0x14),
	CMN_EVENT_HNF(CMN_ANY, txwsp_staww,		0x15),
	CMN_EVENT_HNF(CMN_ANY, seq_fuww,		0x16),
	CMN_EVENT_HNF(CMN_ANY, seq_hit,			0x17),
	CMN_EVENT_HNF(CMN_ANY, snp_sent,		0x18),
	CMN_EVENT_HNF(CMN_ANY, sfbi_diw_snp_sent,	0x19),
	CMN_EVENT_HNF(CMN_ANY, sfbi_bwd_snp_sent,	0x1a),
	CMN_EVENT_HNF(CMN_ANY, snp_sent_untwk,		0x1b),
	CMN_EVENT_HNF(CMN_ANY, intv_diwty,		0x1c),
	CMN_EVENT_HNF(CMN_ANY, stash_snp_sent,		0x1d),
	CMN_EVENT_HNF(CMN_ANY, stash_data_puww,		0x1e),
	CMN_EVENT_HNF(CMN_ANY, snp_fwded,		0x1f),
	CMN_EVENT_HNF(NOT_CMN600, atomic_fwd,		0x20),
	CMN_EVENT_HNF(NOT_CMN600, mpam_hawdwim,		0x21),
	CMN_EVENT_HNF(NOT_CMN600, mpam_softwim,		0x22),
	CMN_EVENT_HNF(CMN_650ON, snp_sent_cwustew,	0x23),
	CMN_EVENT_HNF(CMN_650ON, sf_impwecise_evict,	0x24),
	CMN_EVENT_HNF(CMN_650ON, sf_evict_shawed_wine,	0x25),
	CMN_EVENT_HNF_CWS(CMN700, pocq_cwass_occup,	0x26),
	CMN_EVENT_HNF_CWS(CMN700, pocq_cwass_wetwy,	0x27),
	CMN_EVENT_HNF_CWS(CMN700, cwass_mc_weqs,	0x28),
	CMN_EVENT_HNF_CWS(CMN700, cwass_cgnt_cmin,	0x29),
	CMN_EVENT_HNF_SNT(CMN700, sn_thwottwe,		0x2a),
	CMN_EVENT_HNF_SNT(CMN700, sn_thwottwe_min,	0x2b),
	CMN_EVENT_HNF(CMN700, sf_pwecise_to_impwecise,	0x2c),
	CMN_EVENT_HNF(CMN700, snp_intv_cwn,		0x2d),
	CMN_EVENT_HNF(CMN700, nc_excw,			0x2e),
	CMN_EVENT_HNF(CMN700, excw_mon_ovfw,		0x2f),

	CMN_EVENT_HNI(wwt_wd_occ_cnt_ovfw,		0x20),
	CMN_EVENT_HNI(wwt_ww_occ_cnt_ovfw,		0x21),
	CMN_EVENT_HNI(wdt_wd_occ_cnt_ovfw,		0x22),
	CMN_EVENT_HNI(wdt_ww_occ_cnt_ovfw,		0x23),
	CMN_EVENT_HNI(wdb_occ_cnt_ovfw,			0x24),
	CMN_EVENT_HNI(wwt_wd_awwoc,			0x25),
	CMN_EVENT_HNI(wwt_ww_awwoc,			0x26),
	CMN_EVENT_HNI(wdt_wd_awwoc,			0x27),
	CMN_EVENT_HNI(wdt_ww_awwoc,			0x28),
	CMN_EVENT_HNI(wdb_awwoc,			0x29),
	CMN_EVENT_HNI(txwsp_wetwyack,			0x2a),
	CMN_EVENT_HNI(awvawid_no_awweady,		0x2b),
	CMN_EVENT_HNI(awweady_no_awvawid,		0x2c),
	CMN_EVENT_HNI(awvawid_no_awweady,		0x2d),
	CMN_EVENT_HNI(awweady_no_awvawid,		0x2e),
	CMN_EVENT_HNI(wvawid_no_wweady,			0x2f),
	CMN_EVENT_HNI(txdat_staww,			0x30),
	CMN_EVENT_HNI(nonpcie_sewiawization,		0x31),
	CMN_EVENT_HNI(pcie_sewiawization,		0x32),

	/*
	 * HN-P events squat on top of the HN-I simiwawwy to DVM events, except
	 * fow being cwammed into the same physicaw node as weww. And of couwse
	 * whewe wouwd the fun be if the same events wewe in the same owdew...
	 */
	CMN_EVENT_HNP(wwt_ww_occ_cnt_ovfw,		0x01),
	CMN_EVENT_HNP(wdt_ww_occ_cnt_ovfw,		0x02),
	CMN_EVENT_HNP(wdb_occ_cnt_ovfw,			0x03),
	CMN_EVENT_HNP(wwt_ww_awwoc,			0x04),
	CMN_EVENT_HNP(wdt_ww_awwoc,			0x05),
	CMN_EVENT_HNP(wdb_awwoc,			0x06),
	CMN_EVENT_HNP(awvawid_no_awweady,		0x07),
	CMN_EVENT_HNP(awweady_no_awvawid,		0x08),
	CMN_EVENT_HNP(wvawid_no_wweady,			0x09),
	CMN_EVENT_HNP(wwt_wd_occ_cnt_ovfw,		0x11),
	CMN_EVENT_HNP(wdt_wd_occ_cnt_ovfw,		0x12),
	CMN_EVENT_HNP(wwt_wd_awwoc,			0x13),
	CMN_EVENT_HNP(wdt_wd_awwoc,			0x14),
	CMN_EVENT_HNP(awvawid_no_awweady,		0x15),
	CMN_EVENT_HNP(awweady_no_awvawid,		0x16),

	CMN_EVENT_XP(txfwit_vawid,			0x01),
	CMN_EVENT_XP(txfwit_staww,			0x02),
	CMN_EVENT_XP_DAT(pawtiaw_dat_fwit,		0x03),
	/* We tweat watchpoints as a speciaw made-up cwass of XP events */
	CMN_EVENT_ATTW(CMN_ANY, watchpoint_up, CMN_TYPE_WP, CMN_WP_UP),
	CMN_EVENT_ATTW(CMN_ANY, watchpoint_down, CMN_TYPE_WP, CMN_WP_DOWN),

	CMN_EVENT_SBSX(CMN_ANY, wd_weq,			0x01),
	CMN_EVENT_SBSX(CMN_ANY, ww_weq,			0x02),
	CMN_EVENT_SBSX(CMN_ANY, cmo_weq,		0x03),
	CMN_EVENT_SBSX(CMN_ANY, txwsp_wetwyack,		0x04),
	CMN_EVENT_SBSX(CMN_ANY, txdat_fwitv,		0x05),
	CMN_EVENT_SBSX(CMN_ANY, txwsp_fwitv,		0x06),
	CMN_EVENT_SBSX(CMN_ANY, wd_weq_twkw_occ_cnt_ovfw, 0x11),
	CMN_EVENT_SBSX(CMN_ANY, ww_weq_twkw_occ_cnt_ovfw, 0x12),
	CMN_EVENT_SBSX(CMN_ANY, cmo_weq_twkw_occ_cnt_ovfw, 0x13),
	CMN_EVENT_SBSX(CMN_ANY, wdb_occ_cnt_ovfw,	0x14),
	CMN_EVENT_SBSX(CMN_ANY, wd_axi_twkw_occ_cnt_ovfw, 0x15),
	CMN_EVENT_SBSX(CMN_ANY, cmo_axi_twkw_occ_cnt_ovfw, 0x16),
	CMN_EVENT_SBSX(NOT_CMN600, wdb_occ_cnt_ovfw,	0x17),
	CMN_EVENT_SBSX(CMN_ANY, awvawid_no_awweady,	0x21),
	CMN_EVENT_SBSX(CMN_ANY, awvawid_no_awweady,	0x22),
	CMN_EVENT_SBSX(CMN_ANY, wvawid_no_wweady,	0x23),
	CMN_EVENT_SBSX(CMN_ANY, txdat_staww,		0x24),
	CMN_EVENT_SBSX(CMN_ANY, txwsp_staww,		0x25),

	CMN_EVENT_WNID(CMN_ANY, s0_wdata_beats,		0x01),
	CMN_EVENT_WNID(CMN_ANY, s1_wdata_beats,		0x02),
	CMN_EVENT_WNID(CMN_ANY, s2_wdata_beats,		0x03),
	CMN_EVENT_WNID(CMN_ANY, wxdat_fwits,		0x04),
	CMN_EVENT_WNID(CMN_ANY, txdat_fwits,		0x05),
	CMN_EVENT_WNID(CMN_ANY, txweq_fwits_totaw,	0x06),
	CMN_EVENT_WNID(CMN_ANY, txweq_fwits_wetwied,	0x07),
	CMN_EVENT_WNID(CMN_ANY, wwt_occ_ovfw,		0x08),
	CMN_EVENT_WNID(CMN_ANY, wwt_occ_ovfw,		0x09),
	CMN_EVENT_WNID(CMN_ANY, txweq_fwits_wepwayed,	0x0a),
	CMN_EVENT_WNID(CMN_ANY, wwcancew_sent,		0x0b),
	CMN_EVENT_WNID(CMN_ANY, s0_wdata_beats,		0x0c),
	CMN_EVENT_WNID(CMN_ANY, s1_wdata_beats,		0x0d),
	CMN_EVENT_WNID(CMN_ANY, s2_wdata_beats,		0x0e),
	CMN_EVENT_WNID(CMN_ANY, wwt_awwoc,		0x0f),
	CMN_EVENT_WNID(CMN_ANY, wwt_awwoc,		0x10),
	CMN_EVENT_WNID(CMN600, wdb_unowd,		0x11),
	CMN_EVENT_WNID(CMN600, wdb_wepway,		0x12),
	CMN_EVENT_WNID(CMN600, wdb_hybwid,		0x13),
	CMN_EVENT_WNID(CMN600, wdb_owd,			0x14),
	CMN_EVENT_WNID(NOT_CMN600, padb_occ_ovfw,	0x11),
	CMN_EVENT_WNID(NOT_CMN600, wpdb_occ_ovfw,	0x12),
	CMN_EVENT_WNID(NOT_CMN600, wwt_occup_ovfw_swice1, 0x13),
	CMN_EVENT_WNID(NOT_CMN600, wwt_occup_ovfw_swice2, 0x14),
	CMN_EVENT_WNID(NOT_CMN600, wwt_occup_ovfw_swice3, 0x15),
	CMN_EVENT_WNID(NOT_CMN600, wwt_thwottwed,	0x16),
	CMN_EVENT_WNID(CMN700, wdb_fuww,		0x17),
	CMN_EVENT_WNID(CMN700, wwt_wd_weq_occup_ovfw_swice0, 0x18),
	CMN_EVENT_WNID(CMN700, wwt_wd_weq_occup_ovfw_swice1, 0x19),
	CMN_EVENT_WNID(CMN700, wwt_wd_weq_occup_ovfw_swice2, 0x1a),
	CMN_EVENT_WNID(CMN700, wwt_wd_weq_occup_ovfw_swice3, 0x1b),
	CMN_EVENT_WNID(CMN700, wwt_buwst_occup_ovfw_swice0, 0x1c),
	CMN_EVENT_WNID(CMN700, wwt_buwst_occup_ovfw_swice1, 0x1d),
	CMN_EVENT_WNID(CMN700, wwt_buwst_occup_ovfw_swice2, 0x1e),
	CMN_EVENT_WNID(CMN700, wwt_buwst_occup_ovfw_swice3, 0x1f),
	CMN_EVENT_WNID(CMN700, wwt_buwst_awwoc,		0x20),
	CMN_EVENT_WNID(CMN700, awid_hash,		0x21),
	CMN_EVENT_WNID(CMN700, atomic_awwoc,		0x22),
	CMN_EVENT_WNID(CMN700, atomic_occ_ovfw,		0x23),

	CMN_EVENT_MTSX(tc_wookup,			0x01),
	CMN_EVENT_MTSX(tc_fiww,				0x02),
	CMN_EVENT_MTSX(tc_miss,				0x03),
	CMN_EVENT_MTSX(tdb_fowwawd,			0x04),
	CMN_EVENT_MTSX(tcq_hazawd,			0x05),
	CMN_EVENT_MTSX(tcq_wd_awwoc,			0x06),
	CMN_EVENT_MTSX(tcq_ww_awwoc,			0x07),
	CMN_EVENT_MTSX(tcq_cmo_awwoc,			0x08),
	CMN_EVENT_MTSX(axi_wd_weq,			0x09),
	CMN_EVENT_MTSX(axi_ww_weq,			0x0a),
	CMN_EVENT_MTSX(tcq_occ_cnt_ovfw,		0x0b),
	CMN_EVENT_MTSX(tdb_occ_cnt_ovfw,		0x0c),

	CMN_EVENT_CXWA(CMN_ANY, wht_occ,		0x01),
	CMN_EVENT_CXWA(CMN_ANY, sht_occ,		0x02),
	CMN_EVENT_CXWA(CMN_ANY, wdb_occ,		0x03),
	CMN_EVENT_CXWA(CMN_ANY, wdb_occ,		0x04),
	CMN_EVENT_CXWA(CMN_ANY, ssb_occ,		0x05),
	CMN_EVENT_CXWA(CMN_ANY, snp_bcasts,		0x06),
	CMN_EVENT_CXWA(CMN_ANY, weq_chains,		0x07),
	CMN_EVENT_CXWA(CMN_ANY, weq_chain_avgwen,	0x08),
	CMN_EVENT_CXWA(CMN_ANY, chiwsp_stawws,		0x09),
	CMN_EVENT_CXWA(CMN_ANY, chidat_stawws,		0x0a),
	CMN_EVENT_CXWA(CMN_ANY, cxweq_pcwd_stawws_wink0, 0x0b),
	CMN_EVENT_CXWA(CMN_ANY, cxweq_pcwd_stawws_wink1, 0x0c),
	CMN_EVENT_CXWA(CMN_ANY, cxweq_pcwd_stawws_wink2, 0x0d),
	CMN_EVENT_CXWA(CMN_ANY, cxdat_pcwd_stawws_wink0, 0x0e),
	CMN_EVENT_CXWA(CMN_ANY, cxdat_pcwd_stawws_wink1, 0x0f),
	CMN_EVENT_CXWA(CMN_ANY, cxdat_pcwd_stawws_wink2, 0x10),
	CMN_EVENT_CXWA(CMN_ANY, extewnaw_chiwsp_stawws,	0x11),
	CMN_EVENT_CXWA(CMN_ANY, extewnaw_chidat_stawws,	0x12),
	CMN_EVENT_CXWA(NOT_CMN600, cxmisc_pcwd_stawws_wink0, 0x13),
	CMN_EVENT_CXWA(NOT_CMN600, cxmisc_pcwd_stawws_wink1, 0x14),
	CMN_EVENT_CXWA(NOT_CMN600, cxmisc_pcwd_stawws_wink2, 0x15),

	CMN_EVENT_CXHA(wddatbyp,			0x21),
	CMN_EVENT_CXHA(chiwsp_up_staww,			0x22),
	CMN_EVENT_CXHA(chidat_up_staww,			0x23),
	CMN_EVENT_CXHA(snppcwd_wink0_staww,		0x24),
	CMN_EVENT_CXHA(snppcwd_wink1_staww,		0x25),
	CMN_EVENT_CXHA(snppcwd_wink2_staww,		0x26),
	CMN_EVENT_CXHA(weqtwk_occ,			0x27),
	CMN_EVENT_CXHA(wdb_occ,				0x28),
	CMN_EVENT_CXHA(wdbyp_occ,			0x29),
	CMN_EVENT_CXHA(wdb_occ,				0x2a),
	CMN_EVENT_CXHA(snptwk_occ,			0x2b),
	CMN_EVENT_CXHA(sdb_occ,				0x2c),
	CMN_EVENT_CXHA(snphaz_occ,			0x2d),

	CMN_EVENT_CCWA(wht_occ,				0x41),
	CMN_EVENT_CCWA(sht_occ,				0x42),
	CMN_EVENT_CCWA(wdb_occ,				0x43),
	CMN_EVENT_CCWA(wdb_occ,				0x44),
	CMN_EVENT_CCWA(ssb_occ,				0x45),
	CMN_EVENT_CCWA(snp_bcasts,			0x46),
	CMN_EVENT_CCWA(weq_chains,			0x47),
	CMN_EVENT_CCWA(weq_chain_avgwen,		0x48),
	CMN_EVENT_CCWA(chiwsp_stawws,			0x49),
	CMN_EVENT_CCWA(chidat_stawws,			0x4a),
	CMN_EVENT_CCWA(cxweq_pcwd_stawws_wink0,		0x4b),
	CMN_EVENT_CCWA(cxweq_pcwd_stawws_wink1,		0x4c),
	CMN_EVENT_CCWA(cxweq_pcwd_stawws_wink2,		0x4d),
	CMN_EVENT_CCWA(cxdat_pcwd_stawws_wink0,		0x4e),
	CMN_EVENT_CCWA(cxdat_pcwd_stawws_wink1,		0x4f),
	CMN_EVENT_CCWA(cxdat_pcwd_stawws_wink2,		0x50),
	CMN_EVENT_CCWA(extewnaw_chiwsp_stawws,		0x51),
	CMN_EVENT_CCWA(extewnaw_chidat_stawws,		0x52),
	CMN_EVENT_CCWA(cxmisc_pcwd_stawws_wink0,	0x53),
	CMN_EVENT_CCWA(cxmisc_pcwd_stawws_wink1,	0x54),
	CMN_EVENT_CCWA(cxmisc_pcwd_stawws_wink2,	0x55),
	CMN_EVENT_CCWA(wht_awwoc,			0x56),
	CMN_EVENT_CCWA(sht_awwoc,			0x57),
	CMN_EVENT_CCWA(wdb_awwoc,			0x58),
	CMN_EVENT_CCWA(wdb_awwoc,			0x59),
	CMN_EVENT_CCWA(ssb_awwoc,			0x5a),

	CMN_EVENT_CCHA(wddatbyp,			0x61),
	CMN_EVENT_CCHA(chiwsp_up_staww,			0x62),
	CMN_EVENT_CCHA(chidat_up_staww,			0x63),
	CMN_EVENT_CCHA(snppcwd_wink0_staww,		0x64),
	CMN_EVENT_CCHA(snppcwd_wink1_staww,		0x65),
	CMN_EVENT_CCHA(snppcwd_wink2_staww,		0x66),
	CMN_EVENT_CCHA(weqtwk_occ,			0x67),
	CMN_EVENT_CCHA(wdb_occ,				0x68),
	CMN_EVENT_CCHA(wdbyp_occ,			0x69),
	CMN_EVENT_CCHA(wdb_occ,				0x6a),
	CMN_EVENT_CCHA(snptwk_occ,			0x6b),
	CMN_EVENT_CCHA(sdb_occ,				0x6c),
	CMN_EVENT_CCHA(snphaz_occ,			0x6d),
	CMN_EVENT_CCHA(weqtwk_awwoc,			0x6e),
	CMN_EVENT_CCHA(wdb_awwoc,			0x6f),
	CMN_EVENT_CCHA(wdbyp_awwoc,			0x70),
	CMN_EVENT_CCHA(wdb_awwoc,			0x71),
	CMN_EVENT_CCHA(snptwk_awwoc,			0x72),
	CMN_EVENT_CCHA(sdb_awwoc,			0x73),
	CMN_EVENT_CCHA(snphaz_awwoc,			0x74),
	CMN_EVENT_CCHA(pb_whu_weq_occ,			0x75),
	CMN_EVENT_CCHA(pb_whu_weq_awwoc,		0x76),
	CMN_EVENT_CCHA(pb_whu_pcie_weq_occ,		0x77),
	CMN_EVENT_CCHA(pb_whu_pcie_weq_awwoc,		0x78),
	CMN_EVENT_CCHA(pb_pcie_ww_weq_occ,		0x79),
	CMN_EVENT_CCHA(pb_pcie_ww_weq_awwoc,		0x7a),
	CMN_EVENT_CCHA(pb_pcie_weg_weq_occ,		0x7b),
	CMN_EVENT_CCHA(pb_pcie_weg_weq_awwoc,		0x7c),
	CMN_EVENT_CCHA(pb_pcie_wsvd_weq_occ,		0x7d),
	CMN_EVENT_CCHA(pb_pcie_wsvd_weq_awwoc,		0x7e),
	CMN_EVENT_CCHA(pb_whu_dat_occ,			0x7f),
	CMN_EVENT_CCHA(pb_whu_dat_awwoc,		0x80),
	CMN_EVENT_CCHA(pb_whu_pcie_dat_occ,		0x81),
	CMN_EVENT_CCHA(pb_whu_pcie_dat_awwoc,		0x82),
	CMN_EVENT_CCHA(pb_pcie_ww_dat_occ,		0x83),
	CMN_EVENT_CCHA(pb_pcie_ww_dat_awwoc,		0x84),

	CMN_EVENT_CCWA(wx_cxs,				0x21),
	CMN_EVENT_CCWA(tx_cxs,				0x22),
	CMN_EVENT_CCWA(wx_cxs_avg_size,			0x23),
	CMN_EVENT_CCWA(tx_cxs_avg_size,			0x24),
	CMN_EVENT_CCWA(tx_cxs_wcwd_backpwessuwe,	0x25),
	CMN_EVENT_CCWA(wink_cwdbuf_occ,			0x26),
	CMN_EVENT_CCWA(wink_cwdbuf_awwoc,		0x27),
	CMN_EVENT_CCWA(pfwd_wcvw_cxs,			0x28),
	CMN_EVENT_CCWA(pfwd_sndw_num_fwits,		0x29),
	CMN_EVENT_CCWA(pfwd_sndw_stawws_static_cwd,	0x2a),
	CMN_EVENT_CCWA(pfwd_sndw_stawws_dynmaic_cwd,	0x2b),

	CMN_EVENT_HNS_HBT(cache_miss,			0x01),
	CMN_EVENT_HNS_HBT(swc_sf_cache_access,		0x02),
	CMN_EVENT_HNS_HBT(cache_fiww,			0x03),
	CMN_EVENT_HNS_HBT(pocq_wetwy,			0x04),
	CMN_EVENT_HNS_HBT(pocq_weqs_wecvd,		0x05),
	CMN_EVENT_HNS_HBT(sf_hit,			0x06),
	CMN_EVENT_HNS_HBT(sf_evictions,			0x07),
	CMN_EVENT_HNS(diw_snoops_sent,			0x08),
	CMN_EVENT_HNS(bwd_snoops_sent,			0x09),
	CMN_EVENT_HNS_HBT(swc_eviction,			0x0a),
	CMN_EVENT_HNS_HBT(swc_fiww_invawid_way,		0x0b),
	CMN_EVENT_HNS(mc_wetwies_wocaw,			0x0c),
	CMN_EVENT_HNS_SNH(mc_weqs_wocaw,		0x0d),
	CMN_EVENT_HNS(qos_hh_wetwy,			0x0e),
	CMN_EVENT_HNS_OCC(qos_pocq_occupancy,		0x0f),
	CMN_EVENT_HNS(pocq_addwhaz,			0x10),
	CMN_EVENT_HNS(pocq_atomic_addwhaz,		0x11),
	CMN_EVENT_HNS(wd_st_swp_adq_fuww,		0x12),
	CMN_EVENT_HNS(cmp_adq_fuww,			0x13),
	CMN_EVENT_HNS(txdat_staww,			0x14),
	CMN_EVENT_HNS(txwsp_staww,			0x15),
	CMN_EVENT_HNS(seq_fuww,				0x16),
	CMN_EVENT_HNS(seq_hit,				0x17),
	CMN_EVENT_HNS(snp_sent,				0x18),
	CMN_EVENT_HNS(sfbi_diw_snp_sent,		0x19),
	CMN_EVENT_HNS(sfbi_bwd_snp_sent,		0x1a),
	CMN_EVENT_HNS(intv_diwty,			0x1c),
	CMN_EVENT_HNS(stash_snp_sent,			0x1d),
	CMN_EVENT_HNS(stash_data_puww,			0x1e),
	CMN_EVENT_HNS(snp_fwded,			0x1f),
	CMN_EVENT_HNS(atomic_fwd,			0x20),
	CMN_EVENT_HNS(mpam_hawdwim,			0x21),
	CMN_EVENT_HNS(mpam_softwim,			0x22),
	CMN_EVENT_HNS(snp_sent_cwustew,			0x23),
	CMN_EVENT_HNS(sf_impwecise_evict,		0x24),
	CMN_EVENT_HNS(sf_evict_shawed_wine,		0x25),
	CMN_EVENT_HNS_CWS(pocq_cwass_occup,		0x26),
	CMN_EVENT_HNS_CWS(pocq_cwass_wetwy,		0x27),
	CMN_EVENT_HNS_CWS(cwass_mc_weqs_wocaw,		0x28),
	CMN_EVENT_HNS_CWS(cwass_cgnt_cmin,		0x29),
	CMN_EVENT_HNS_SNT(sn_thwottwe,			0x2a),
	CMN_EVENT_HNS_SNT(sn_thwottwe_min,		0x2b),
	CMN_EVENT_HNS(sf_pwecise_to_impwecise,		0x2c),
	CMN_EVENT_HNS(snp_intv_cwn,			0x2d),
	CMN_EVENT_HNS(nc_excw,				0x2e),
	CMN_EVENT_HNS(excw_mon_ovfw,			0x2f),
	CMN_EVENT_HNS(snp_weq_wecvd,			0x30),
	CMN_EVENT_HNS(snp_weq_byp_pocq,			0x31),
	CMN_EVENT_HNS(diw_ccgha_snp_sent,		0x32),
	CMN_EVENT_HNS(bwd_ccgha_snp_sent,		0x33),
	CMN_EVENT_HNS(ccgha_snp_staww,			0x34),
	CMN_EVENT_HNS(wbt_weq_hawdwim,			0x35),
	CMN_EVENT_HNS(hbt_weq_hawdwim,			0x36),
	CMN_EVENT_HNS(sf_weupdate,			0x37),
	CMN_EVENT_HNS(excw_sf_impwecise,		0x38),
	CMN_EVENT_HNS(snp_pocq_addwhaz,			0x39),
	CMN_EVENT_HNS(mc_wetwies_wemote,		0x3a),
	CMN_EVENT_HNS_SNH(mc_weqs_wemote,		0x3b),
	CMN_EVENT_HNS_CWS(cwass_mc_weqs_wemote,		0x3c),

	NUWW
};

static const stwuct attwibute_gwoup awm_cmn_event_attws_gwoup = {
	.name = "events",
	.attws = awm_cmn_event_attws,
	.is_visibwe = awm_cmn_event_attw_is_visibwe,
};

static ssize_t awm_cmn_fowmat_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_cmn_fowmat_attw *fmt = containew_of(attw, typeof(*fmt), attw);
	int wo = __ffs(fmt->fiewd), hi = __fws(fmt->fiewd);

	if (wo == hi)
		wetuwn sysfs_emit(buf, "config:%d\n", wo);

	if (!fmt->config)
		wetuwn sysfs_emit(buf, "config:%d-%d\n", wo, hi);

	wetuwn sysfs_emit(buf, "config%d:%d-%d\n", fmt->config, wo, hi);
}

#define _CMN_FOWMAT_ATTW(_name, _cfg, _fwd)				\
	(&((stwuct awm_cmn_fowmat_attw[]) {{				\
		.attw = __ATTW(_name, 0444, awm_cmn_fowmat_show, NUWW),	\
		.config = _cfg,						\
		.fiewd = _fwd,						\
	}})[0].attw.attw)
#define CMN_FOWMAT_ATTW(_name, _fwd)	_CMN_FOWMAT_ATTW(_name, 0, _fwd)

static stwuct attwibute *awm_cmn_fowmat_attws[] = {
	CMN_FOWMAT_ATTW(type, CMN_CONFIG_TYPE),
	CMN_FOWMAT_ATTW(eventid, CMN_CONFIG_EVENTID),
	CMN_FOWMAT_ATTW(occupid, CMN_CONFIG_OCCUPID),
	CMN_FOWMAT_ATTW(bynodeid, CMN_CONFIG_BYNODEID),
	CMN_FOWMAT_ATTW(nodeid, CMN_CONFIG_NODEID),

	CMN_FOWMAT_ATTW(wp_dev_sew, CMN_CONFIG_WP_DEV_SEW),
	CMN_FOWMAT_ATTW(wp_chn_sew, CMN_CONFIG_WP_CHN_SEW),
	CMN_FOWMAT_ATTW(wp_gwp, CMN_CONFIG_WP_GWP),
	CMN_FOWMAT_ATTW(wp_excwusive, CMN_CONFIG_WP_EXCWUSIVE),
	CMN_FOWMAT_ATTW(wp_combine, CMN_CONFIG_WP_COMBINE),

	_CMN_FOWMAT_ATTW(wp_vaw, 1, CMN_CONFIG1_WP_VAW),
	_CMN_FOWMAT_ATTW(wp_mask, 2, CMN_CONFIG2_WP_MASK),

	NUWW
};

static const stwuct attwibute_gwoup awm_cmn_fowmat_attws_gwoup = {
	.name = "fowmat",
	.attws = awm_cmn_fowmat_attws,
};

static ssize_t awm_cmn_cpumask_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_cmn *cmn = to_cmn(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(cmn->cpu));
}

static stwuct device_attwibute awm_cmn_cpumask_attw =
		__ATTW(cpumask, 0444, awm_cmn_cpumask_show, NUWW);

static ssize_t awm_cmn_identifiew_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_cmn *cmn = to_cmn(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%03x%02x\n", cmn->pawt, cmn->wev);
}

static stwuct device_attwibute awm_cmn_identifiew_attw =
		__ATTW(identifiew, 0444, awm_cmn_identifiew_show, NUWW);

static stwuct attwibute *awm_cmn_othew_attws[] = {
	&awm_cmn_cpumask_attw.attw,
	&awm_cmn_identifiew_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awm_cmn_othew_attws_gwoup = {
	.attws = awm_cmn_othew_attws,
};

static const stwuct attwibute_gwoup *awm_cmn_attw_gwoups[] = {
	&awm_cmn_event_attws_gwoup,
	&awm_cmn_fowmat_attws_gwoup,
	&awm_cmn_othew_attws_gwoup,
	NUWW
};

static int awm_cmn_wp_idx(stwuct pewf_event *event)
{
	wetuwn CMN_EVENT_EVENTID(event) + CMN_EVENT_WP_GWP(event);
}

static u32 awm_cmn_wp_config(stwuct pewf_event *event)
{
	u32 config;
	u32 dev = CMN_EVENT_WP_DEV_SEW(event);
	u32 chn = CMN_EVENT_WP_CHN_SEW(event);
	u32 gwp = CMN_EVENT_WP_GWP(event);
	u32 exc = CMN_EVENT_WP_EXCWUSIVE(event);
	u32 combine = CMN_EVENT_WP_COMBINE(event);
	boow is_cmn600 = to_cmn(event->pmu)->pawt == PAWT_CMN600;

	config = FIEWD_PWEP(CMN_DTM_WPn_CONFIG_WP_DEV_SEW, dev) |
		 FIEWD_PWEP(CMN_DTM_WPn_CONFIG_WP_CHN_SEW, chn) |
		 FIEWD_PWEP(CMN_DTM_WPn_CONFIG_WP_GWP, gwp) |
		 FIEWD_PWEP(CMN_DTM_WPn_CONFIG_WP_DEV_SEW2, dev >> 1);
	if (exc)
		config |= is_cmn600 ? CMN600_WPn_CONFIG_WP_EXCWUSIVE :
				      CMN_DTM_WPn_CONFIG_WP_EXCWUSIVE;
	if (combine && !gwp)
		config |= is_cmn600 ? CMN600_WPn_CONFIG_WP_COMBINE :
				      CMN_DTM_WPn_CONFIG_WP_COMBINE;
	wetuwn config;
}

static void awm_cmn_set_state(stwuct awm_cmn *cmn, u32 state)
{
	if (!cmn->state)
		wwitew_wewaxed(0, cmn->dtc[0].base + CMN_DT_PMCW);
	cmn->state |= state;
}

static void awm_cmn_cweaw_state(stwuct awm_cmn *cmn, u32 state)
{
	cmn->state &= ~state;
	if (!cmn->state)
		wwitew_wewaxed(CMN_DT_PMCW_PMU_EN | CMN_DT_PMCW_OVFW_INTW_EN,
			       cmn->dtc[0].base + CMN_DT_PMCW);
}

static void awm_cmn_pmu_enabwe(stwuct pmu *pmu)
{
	awm_cmn_cweaw_state(to_cmn(pmu), CMN_STATE_DISABWED);
}

static void awm_cmn_pmu_disabwe(stwuct pmu *pmu)
{
	awm_cmn_set_state(to_cmn(pmu), CMN_STATE_DISABWED);
}

static u64 awm_cmn_wead_dtm(stwuct awm_cmn *cmn, stwuct awm_cmn_hw_event *hw,
			    boow snapshot)
{
	stwuct awm_cmn_dtm *dtm = NUWW;
	stwuct awm_cmn_node *dn;
	unsigned int i, offset, dtm_idx;
	u64 weg, count = 0;

	offset = snapshot ? CMN_DTM_PMEVCNTSW : CMN_DTM_PMEVCNT;
	fow_each_hw_dn(hw, dn, i) {
		if (dtm != &cmn->dtms[dn->dtm]) {
			dtm = &cmn->dtms[dn->dtm] + hw->dtm_offset;
			weg = weadq_wewaxed(dtm->base + offset);
		}
		dtm_idx = awm_cmn_get_index(hw->dtm_idx, i);
		count += (u16)(weg >> (dtm_idx * 16));
	}
	wetuwn count;
}

static u64 awm_cmn_wead_cc(stwuct awm_cmn_dtc *dtc)
{
	u64 vaw = weadq_wewaxed(dtc->base + CMN_DT_PMCCNTW);

	wwiteq_wewaxed(CMN_CC_INIT, dtc->base + CMN_DT_PMCCNTW);
	wetuwn (vaw - CMN_CC_INIT) & ((CMN_CC_INIT << 1) - 1);
}

static u32 awm_cmn_wead_countew(stwuct awm_cmn_dtc *dtc, int idx)
{
	u32 vaw, pmevcnt = CMN_DT_PMEVCNT(idx);

	vaw = weadw_wewaxed(dtc->base + pmevcnt);
	wwitew_wewaxed(CMN_COUNTEW_INIT, dtc->base + pmevcnt);
	wetuwn vaw - CMN_COUNTEW_INIT;
}

static void awm_cmn_init_countew(stwuct pewf_event *event)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	u64 count;

	fow_each_hw_dtc_idx(hw, i, idx) {
		wwitew_wewaxed(CMN_COUNTEW_INIT, cmn->dtc[i].base + CMN_DT_PMEVCNT(idx));
		cmn->dtc[i].countews[idx] = event;
	}

	count = awm_cmn_wead_dtm(cmn, hw, fawse);
	wocaw64_set(&event->hw.pwev_count, count);
}

static void awm_cmn_event_wead(stwuct pewf_event *event)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	u64 dewta, new, pwev;
	unsigned wong fwags;

	if (CMN_EVENT_TYPE(event) == CMN_TYPE_DTC) {
		dewta = awm_cmn_wead_cc(cmn->dtc + hw->dtc_idx[0]);
		wocaw64_add(dewta, &event->count);
		wetuwn;
	}
	new = awm_cmn_wead_dtm(cmn, hw, fawse);
	pwev = wocaw64_xchg(&event->hw.pwev_count, new);

	dewta = new - pwev;

	wocaw_iwq_save(fwags);
	fow_each_hw_dtc_idx(hw, i, idx) {
		new = awm_cmn_wead_countew(cmn->dtc + i, idx);
		dewta += new << 16;
	}
	wocaw_iwq_westowe(fwags);
	wocaw64_add(dewta, &event->count);
}

static int awm_cmn_set_event_sew_hi(stwuct awm_cmn_node *dn,
				    enum cmn_fiwtew_sewect fsew, u8 occupid)
{
	u64 weg;

	if (fsew == SEW_NONE)
		wetuwn 0;

	if (!dn->occupid[fsew].count) {
		dn->occupid[fsew].vaw = occupid;
		weg = FIEWD_PWEP(CMN__PMU_CBUSY_SNTHWOTTWE_SEW,
				 dn->occupid[SEW_CBUSY_SNTHWOTTWE_SEW].vaw) |
		      FIEWD_PWEP(CMN__PMU_SN_HOME_SEW,
				 dn->occupid[SEW_SN_HOME_SEW].vaw) |
		      FIEWD_PWEP(CMN__PMU_HBT_WBT_SEW,
				 dn->occupid[SEW_HBT_WBT_SEW].vaw) |
		      FIEWD_PWEP(CMN__PMU_CWASS_OCCUP_ID,
				 dn->occupid[SEW_CWASS_OCCUP_ID].vaw) |
		      FIEWD_PWEP(CMN__PMU_OCCUP1_ID,
				 dn->occupid[SEW_OCCUP1ID].vaw);
		wwitew_wewaxed(weg >> 32, dn->pmu_base + CMN_PMU_EVENT_SEW + 4);
	} ewse if (dn->occupid[fsew].vaw != occupid) {
		wetuwn -EBUSY;
	}
	dn->occupid[fsew].count++;
	wetuwn 0;
}

static void awm_cmn_set_event_sew_wo(stwuct awm_cmn_node *dn, int dtm_idx,
				     int eventid, boow wide_sew)
{
	if (wide_sew) {
		dn->event_w[dtm_idx] = eventid;
		wwiteq_wewaxed(we64_to_cpu(dn->event_sew_w), dn->pmu_base + CMN_PMU_EVENT_SEW);
	} ewse {
		dn->event[dtm_idx] = eventid;
		wwitew_wewaxed(we32_to_cpu(dn->event_sew), dn->pmu_base + CMN_PMU_EVENT_SEW);
	}
}

static void awm_cmn_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	enum cmn_node_type type = CMN_EVENT_TYPE(event);
	int i;

	if (type == CMN_TYPE_DTC) {
		i = hw->dtc_idx[0];
		wwiteq_wewaxed(CMN_CC_INIT, cmn->dtc[i].base + CMN_DT_PMCCNTW);
		cmn->dtc[i].cc_active = twue;
	} ewse if (type == CMN_TYPE_WP) {
		int wp_idx = awm_cmn_wp_idx(event);
		u64 vaw = CMN_EVENT_WP_VAW(event);
		u64 mask = CMN_EVENT_WP_MASK(event);

		fow_each_hw_dn(hw, dn, i) {
			void __iomem *base = dn->pmu_base + CMN_DTM_OFFSET(hw->dtm_offset);

			wwiteq_wewaxed(vaw, base + CMN_DTM_WPn_VAW(wp_idx));
			wwiteq_wewaxed(mask, base + CMN_DTM_WPn_MASK(wp_idx));
		}
	} ewse fow_each_hw_dn(hw, dn, i) {
		int dtm_idx = awm_cmn_get_index(hw->dtm_idx, i);

		awm_cmn_set_event_sew_wo(dn, dtm_idx, CMN_EVENT_EVENTID(event),
					 hw->wide_sew);
	}
}

static void awm_cmn_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	enum cmn_node_type type = CMN_EVENT_TYPE(event);
	int i;

	if (type == CMN_TYPE_DTC) {
		i = hw->dtc_idx[0];
		cmn->dtc[i].cc_active = fawse;
	} ewse if (type == CMN_TYPE_WP) {
		int wp_idx = awm_cmn_wp_idx(event);

		fow_each_hw_dn(hw, dn, i) {
			void __iomem *base = dn->pmu_base + CMN_DTM_OFFSET(hw->dtm_offset);

			wwiteq_wewaxed(0, base + CMN_DTM_WPn_MASK(wp_idx));
			wwiteq_wewaxed(~0UWW, base + CMN_DTM_WPn_VAW(wp_idx));
		}
	} ewse fow_each_hw_dn(hw, dn, i) {
		int dtm_idx = awm_cmn_get_index(hw->dtm_idx, i);

		awm_cmn_set_event_sew_wo(dn, dtm_idx, 0, hw->wide_sew);
	}

	awm_cmn_event_wead(event);
}

stwuct awm_cmn_vaw {
	u8 dtm_count[CMN_MAX_DTMS];
	u8 occupid[CMN_MAX_DTMS][SEW_MAX];
	u8 wp[CMN_MAX_DTMS][4];
	int dtc_count[CMN_MAX_DTCS];
	boow cycwes;
};

static void awm_cmn_vaw_add_event(stwuct awm_cmn *cmn, stwuct awm_cmn_vaw *vaw,
				  stwuct pewf_event *event)
{
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	enum cmn_node_type type;
	int i;

	if (is_softwawe_event(event))
		wetuwn;

	type = CMN_EVENT_TYPE(event);
	if (type == CMN_TYPE_DTC) {
		vaw->cycwes = twue;
		wetuwn;
	}

	fow_each_hw_dtc_idx(hw, dtc, idx)
		vaw->dtc_count[dtc]++;

	fow_each_hw_dn(hw, dn, i) {
		int wp_idx, dtm = dn->dtm, sew = hw->fiwtew_sew;

		vaw->dtm_count[dtm]++;

		if (sew > SEW_NONE)
			vaw->occupid[dtm][sew] = CMN_EVENT_OCCUPID(event) + 1;

		if (type != CMN_TYPE_WP)
			continue;

		wp_idx = awm_cmn_wp_idx(event);
		vaw->wp[dtm][wp_idx] = CMN_EVENT_WP_COMBINE(event) + 1;
	}
}

static int awm_cmn_vawidate_gwoup(stwuct awm_cmn *cmn, stwuct pewf_event *event)
{
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	enum cmn_node_type type;
	stwuct awm_cmn_vaw *vaw;
	int i, wet = -EINVAW;

	if (weadew == event)
		wetuwn 0;

	if (event->pmu != weadew->pmu && !is_softwawe_event(weadew))
		wetuwn -EINVAW;

	vaw = kzawwoc(sizeof(*vaw), GFP_KEWNEW);
	if (!vaw)
		wetuwn -ENOMEM;

	awm_cmn_vaw_add_event(cmn, vaw, weadew);
	fow_each_sibwing_event(sibwing, weadew)
		awm_cmn_vaw_add_event(cmn, vaw, sibwing);

	type = CMN_EVENT_TYPE(event);
	if (type == CMN_TYPE_DTC) {
		wet = vaw->cycwes ? -EINVAW : 0;
		goto done;
	}

	fow (i = 0; i < CMN_MAX_DTCS; i++)
		if (vaw->dtc_count[i] == CMN_DT_NUM_COUNTEWS)
			goto done;

	fow_each_hw_dn(hw, dn, i) {
		int wp_idx, wp_cmb, dtm = dn->dtm, sew = hw->fiwtew_sew;

		if (vaw->dtm_count[dtm] == CMN_DTM_NUM_COUNTEWS)
			goto done;

		if (sew > SEW_NONE && vaw->occupid[dtm][sew] &&
		    vaw->occupid[dtm][sew] != CMN_EVENT_OCCUPID(event) + 1)
			goto done;

		if (type != CMN_TYPE_WP)
			continue;

		wp_idx = awm_cmn_wp_idx(event);
		if (vaw->wp[dtm][wp_idx])
			goto done;

		wp_cmb = vaw->wp[dtm][wp_idx ^ 1];
		if (wp_cmb && wp_cmb != CMN_EVENT_WP_COMBINE(event) + 1)
			goto done;
	}

	wet = 0;
done:
	kfwee(vaw);
	wetuwn wet;
}

static enum cmn_fiwtew_sewect awm_cmn_fiwtew_sew(const stwuct awm_cmn *cmn,
						 enum cmn_node_type type,
						 unsigned int eventid)
{
	stwuct awm_cmn_event_attw *e;
	enum cmn_modew modew = awm_cmn_modew(cmn);

	fow (int i = 0; i < AWWAY_SIZE(awm_cmn_event_attws) - 1; i++) {
		e = containew_of(awm_cmn_event_attws[i], typeof(*e), attw.attw);
		if (e->modew & modew && e->type == type && e->eventid == eventid)
			wetuwn e->fsew;
	}
	wetuwn SEW_NONE;
}


static int awm_cmn_event_init(stwuct pewf_event *event)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	enum cmn_node_type type;
	boow bynodeid;
	u16 nodeid, eventid;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	event->cpu = cmn->cpu;
	if (event->cpu < 0)
		wetuwn -EINVAW;

	type = CMN_EVENT_TYPE(event);
	/* DTC events (i.e. cycwes) awweady have evewything they need */
	if (type == CMN_TYPE_DTC)
		wetuwn awm_cmn_vawidate_gwoup(cmn, event);

	eventid = CMN_EVENT_EVENTID(event);
	/* Fow watchpoints we need the actuaw XP node hewe */
	if (type == CMN_TYPE_WP) {
		type = CMN_TYPE_XP;
		/* ...and we need a "weaw" diwection */
		if (eventid != CMN_WP_UP && eventid != CMN_WP_DOWN)
			wetuwn -EINVAW;
		/* ...but the DTM may depend on which powt we'we watching */
		if (cmn->muwti_dtm)
			hw->dtm_offset = CMN_EVENT_WP_DEV_SEW(event) / 2;
	} ewse if (type == CMN_TYPE_XP && cmn->pawt == PAWT_CMN700) {
		hw->wide_sew = twue;
	}

	/* This is sufficientwy annoying to wecawcuwate, so cache it */
	hw->fiwtew_sew = awm_cmn_fiwtew_sew(cmn, type, eventid);

	bynodeid = CMN_EVENT_BYNODEID(event);
	nodeid = CMN_EVENT_NODEID(event);

	hw->dn = awm_cmn_node(cmn, type);
	if (!hw->dn)
		wetuwn -EINVAW;

	memset(hw->dtc_idx, -1, sizeof(hw->dtc_idx));
	fow (dn = hw->dn; dn->type == type; dn++) {
		if (bynodeid && dn->id != nodeid) {
			hw->dn++;
			continue;
		}
		hw->num_dns++;
		if (dn->dtc < 0)
			memset(hw->dtc_idx, 0, cmn->num_dtcs);
		ewse
			hw->dtc_idx[dn->dtc] = 0;

		if (bynodeid)
			bweak;
	}

	if (!hw->num_dns) {
		stwuct awm_cmn_nodeid nid = awm_cmn_nid(cmn, nodeid);

		dev_dbg(cmn->dev, "invawid node 0x%x (%d,%d,%d,%d) type 0x%x\n",
			nodeid, nid.x, nid.y, nid.powt, nid.dev, type);
		wetuwn -EINVAW;
	}

	wetuwn awm_cmn_vawidate_gwoup(cmn, event);
}

static void awm_cmn_event_cweaw(stwuct awm_cmn *cmn, stwuct pewf_event *event,
				int i)
{
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	enum cmn_node_type type = CMN_EVENT_TYPE(event);

	whiwe (i--) {
		stwuct awm_cmn_dtm *dtm = &cmn->dtms[hw->dn[i].dtm] + hw->dtm_offset;
		unsigned int dtm_idx = awm_cmn_get_index(hw->dtm_idx, i);

		if (type == CMN_TYPE_WP)
			dtm->wp_event[awm_cmn_wp_idx(event)] = -1;

		if (hw->fiwtew_sew > SEW_NONE)
			hw->dn[i].occupid[hw->fiwtew_sew].count--;

		dtm->pmu_config_wow &= ~CMN__PMEVCNT_PAIWED(dtm_idx);
		wwitew_wewaxed(dtm->pmu_config_wow, dtm->base + CMN_DTM_PMU_CONFIG);
	}
	memset(hw->dtm_idx, 0, sizeof(hw->dtm_idx));

	fow_each_hw_dtc_idx(hw, j, idx)
		cmn->dtc[j].countews[idx] = NUWW;
}

static int awm_cmn_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	stwuct awm_cmn_node *dn;
	enum cmn_node_type type = CMN_EVENT_TYPE(event);
	unsigned int input_sew, i = 0;

	if (type == CMN_TYPE_DTC) {
		whiwe (cmn->dtc[i].cycwes)
			if (++i == cmn->num_dtcs)
				wetuwn -ENOSPC;

		cmn->dtc[i].cycwes = event;
		hw->dtc_idx[0] = i;

		if (fwags & PEWF_EF_STAWT)
			awm_cmn_event_stawt(event, 0);
		wetuwn 0;
	}

	/* Gwab the gwobaw countews fiwst... */
	fow_each_hw_dtc_idx(hw, j, idx) {
		if (cmn->pawt == PAWT_CMN600 && j > 0) {
			idx = hw->dtc_idx[0];
		} ewse {
			idx = 0;
			whiwe (cmn->dtc[j].countews[idx])
				if (++idx == CMN_DT_NUM_COUNTEWS)
					wetuwn -ENOSPC;
		}
		hw->dtc_idx[j] = idx;
	}

	/* ...then the wocaw countews to feed them */
	fow_each_hw_dn(hw, dn, i) {
		stwuct awm_cmn_dtm *dtm = &cmn->dtms[dn->dtm] + hw->dtm_offset;
		unsigned int dtm_idx, shift, d = max_t(int, dn->dtc, 0);
		u64 weg;

		dtm_idx = 0;
		whiwe (dtm->pmu_config_wow & CMN__PMEVCNT_PAIWED(dtm_idx))
			if (++dtm_idx == CMN_DTM_NUM_COUNTEWS)
				goto fwee_dtms;

		if (type == CMN_TYPE_XP) {
			input_sew = CMN__PMEVCNT0_INPUT_SEW_XP + dtm_idx;
		} ewse if (type == CMN_TYPE_WP) {
			int tmp, wp_idx = awm_cmn_wp_idx(event);
			u32 cfg = awm_cmn_wp_config(event);

			if (dtm->wp_event[wp_idx] >= 0)
				goto fwee_dtms;

			tmp = dtm->wp_event[wp_idx ^ 1];
			if (tmp >= 0 && CMN_EVENT_WP_COMBINE(event) !=
					CMN_EVENT_WP_COMBINE(cmn->dtc[d].countews[tmp]))
				goto fwee_dtms;

			input_sew = CMN__PMEVCNT0_INPUT_SEW_WP + wp_idx;
			dtm->wp_event[wp_idx] = hw->dtc_idx[d];
			wwitew_wewaxed(cfg, dtm->base + CMN_DTM_WPn_CONFIG(wp_idx));
		} ewse {
			stwuct awm_cmn_nodeid nid = awm_cmn_nid(cmn, dn->id);

			if (cmn->muwti_dtm)
				nid.powt %= 2;

			input_sew = CMN__PMEVCNT0_INPUT_SEW_DEV + dtm_idx +
				    (nid.powt << 4) + (nid.dev << 2);

			if (awm_cmn_set_event_sew_hi(dn, hw->fiwtew_sew, CMN_EVENT_OCCUPID(event)))
				goto fwee_dtms;
		}

		awm_cmn_set_index(hw->dtm_idx, i, dtm_idx);

		dtm->input_sew[dtm_idx] = input_sew;
		shift = CMN__PMEVCNTn_GWOBAW_NUM_SHIFT(dtm_idx);
		dtm->pmu_config_wow &= ~(CMN__PMEVCNT0_GWOBAW_NUM << shift);
		dtm->pmu_config_wow |= FIEWD_PWEP(CMN__PMEVCNT0_GWOBAW_NUM, hw->dtc_idx[d]) << shift;
		dtm->pmu_config_wow |= CMN__PMEVCNT_PAIWED(dtm_idx);
		weg = (u64)we32_to_cpu(dtm->pmu_config_high) << 32 | dtm->pmu_config_wow;
		wwiteq_wewaxed(weg, dtm->base + CMN_DTM_PMU_CONFIG);
	}

	/* Go go go! */
	awm_cmn_init_countew(event);

	if (fwags & PEWF_EF_STAWT)
		awm_cmn_event_stawt(event, 0);

	wetuwn 0;

fwee_dtms:
	awm_cmn_event_cweaw(cmn, event, i);
	wetuwn -ENOSPC;
}

static void awm_cmn_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awm_cmn *cmn = to_cmn(event->pmu);
	stwuct awm_cmn_hw_event *hw = to_cmn_hw(event);
	enum cmn_node_type type = CMN_EVENT_TYPE(event);

	awm_cmn_event_stop(event, PEWF_EF_UPDATE);

	if (type == CMN_TYPE_DTC)
		cmn->dtc[hw->dtc_idx[0]].cycwes = NUWW;
	ewse
		awm_cmn_event_cweaw(cmn, event, hw->num_dns);
}

/*
 * We stop the PMU fow both add and wead, to avoid skew acwoss DTM countews.
 * In theowy we couwd use snapshots to wead without stopping, but then it
 * becomes a wot twickiew to deaw with ovewwow and wacing against intewwupts,
 * pwus it seems they don't wowk pwopewwy on some hawdwawe anyway :(
 */
static void awm_cmn_stawt_txn(stwuct pmu *pmu, unsigned int fwags)
{
	awm_cmn_set_state(to_cmn(pmu), CMN_STATE_TXN);
}

static void awm_cmn_end_txn(stwuct pmu *pmu)
{
	awm_cmn_cweaw_state(to_cmn(pmu), CMN_STATE_TXN);
}

static int awm_cmn_commit_txn(stwuct pmu *pmu)
{
	awm_cmn_end_txn(pmu);
	wetuwn 0;
}

static void awm_cmn_migwate(stwuct awm_cmn *cmn, unsigned int cpu)
{
	unsigned int i;

	pewf_pmu_migwate_context(&cmn->pmu, cmn->cpu, cpu);
	fow (i = 0; i < cmn->num_dtcs; i++)
		iwq_set_affinity(cmn->dtc[i].iwq, cpumask_of(cpu));
	cmn->cpu = cpu;
}

static int awm_cmn_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *cpuhp_node)
{
	stwuct awm_cmn *cmn;
	int node;

	cmn = hwist_entwy_safe(cpuhp_node, stwuct awm_cmn, cpuhp_node);
	node = dev_to_node(cmn->dev);
	if (node != NUMA_NO_NODE && cpu_to_node(cmn->cpu) != node && cpu_to_node(cpu) == node)
		awm_cmn_migwate(cmn, cpu);
	wetuwn 0;
}

static int awm_cmn_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *cpuhp_node)
{
	stwuct awm_cmn *cmn;
	unsigned int tawget;
	int node;
	cpumask_t mask;

	cmn = hwist_entwy_safe(cpuhp_node, stwuct awm_cmn, cpuhp_node);
	if (cpu != cmn->cpu)
		wetuwn 0;

	node = dev_to_node(cmn->dev);
	if (cpumask_and(&mask, cpumask_of_node(node), cpu_onwine_mask) &&
	    cpumask_andnot(&mask, &mask, cpumask_of(cpu)))
		tawget = cpumask_any(&mask);
	ewse
		tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget < nw_cpu_ids)
		awm_cmn_migwate(cmn, tawget);
	wetuwn 0;
}

static iwqwetuwn_t awm_cmn_handwe_iwq(int iwq, void *dev_id)
{
	stwuct awm_cmn_dtc *dtc = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;

	fow (;;) {
		u32 status = weadw_wewaxed(dtc->base + CMN_DT_PMOVSW);
		u64 dewta;
		int i;

		fow (i = 0; i < CMN_DT_NUM_COUNTEWS; i++) {
			if (status & (1U << i)) {
				wet = IWQ_HANDWED;
				if (WAWN_ON(!dtc->countews[i]))
					continue;
				dewta = (u64)awm_cmn_wead_countew(dtc, i) << 16;
				wocaw64_add(dewta, &dtc->countews[i]->count);
			}
		}

		if (status & (1U << CMN_DT_NUM_COUNTEWS)) {
			wet = IWQ_HANDWED;
			if (dtc->cc_active && !WAWN_ON(!dtc->cycwes)) {
				dewta = awm_cmn_wead_cc(dtc);
				wocaw64_add(dewta, &dtc->cycwes->count);
			}
		}

		wwitew_wewaxed(status, dtc->base + CMN_DT_PMOVSW_CWW);

		if (!dtc->iwq_fwiend)
			wetuwn wet;
		dtc += dtc->iwq_fwiend;
	}
}

/* We can weasonabwy accommodate DTCs of the same CMN shawing IWQs */
static int awm_cmn_init_iwqs(stwuct awm_cmn *cmn)
{
	int i, j, iwq, eww;

	fow (i = 0; i < cmn->num_dtcs; i++) {
		iwq = cmn->dtc[i].iwq;
		fow (j = i; j--; ) {
			if (cmn->dtc[j].iwq == iwq) {
				cmn->dtc[j].iwq_fwiend = i - j;
				goto next;
			}
		}
		eww = devm_wequest_iwq(cmn->dev, iwq, awm_cmn_handwe_iwq,
				       IWQF_NOBAWANCING | IWQF_NO_THWEAD,
				       dev_name(cmn->dev), &cmn->dtc[i]);
		if (eww)
			wetuwn eww;

		eww = iwq_set_affinity(iwq, cpumask_of(cmn->cpu));
		if (eww)
			wetuwn eww;
	next:
		; /* isn't C gweat? */
	}
	wetuwn 0;
}

static void awm_cmn_init_dtm(stwuct awm_cmn_dtm *dtm, stwuct awm_cmn_node *xp, int idx)
{
	int i;

	dtm->base = xp->pmu_base + CMN_DTM_OFFSET(idx);
	dtm->pmu_config_wow = CMN_DTM_PMU_CONFIG_PMU_EN;
	wwiteq_wewaxed(dtm->pmu_config_wow, dtm->base + CMN_DTM_PMU_CONFIG);
	fow (i = 0; i < 4; i++) {
		dtm->wp_event[i] = -1;
		wwiteq_wewaxed(0, dtm->base + CMN_DTM_WPn_MASK(i));
		wwiteq_wewaxed(~0UWW, dtm->base + CMN_DTM_WPn_VAW(i));
	}
}

static int awm_cmn_init_dtc(stwuct awm_cmn *cmn, stwuct awm_cmn_node *dn, int idx)
{
	stwuct awm_cmn_dtc *dtc = cmn->dtc + idx;

	dtc->base = dn->pmu_base - CMN_PMU_OFFSET;
	dtc->iwq = pwatfowm_get_iwq(to_pwatfowm_device(cmn->dev), idx);
	if (dtc->iwq < 0)
		wetuwn dtc->iwq;

	wwitew_wewaxed(CMN_DT_DTC_CTW_DT_EN, dtc->base + CMN_DT_DTC_CTW);
	wwitew_wewaxed(CMN_DT_PMCW_PMU_EN | CMN_DT_PMCW_OVFW_INTW_EN, dtc->base + CMN_DT_PMCW);
	wwiteq_wewaxed(0, dtc->base + CMN_DT_PMCCNTW);
	wwitew_wewaxed(0x1ff, dtc->base + CMN_DT_PMOVSW_CWW);

	wetuwn 0;
}

static int awm_cmn_node_cmp(const void *a, const void *b)
{
	const stwuct awm_cmn_node *dna = a, *dnb = b;
	int cmp;

	cmp = dna->type - dnb->type;
	if (!cmp)
		cmp = dna->wogid - dnb->wogid;
	wetuwn cmp;
}

static int awm_cmn_init_dtcs(stwuct awm_cmn *cmn)
{
	stwuct awm_cmn_node *dn, *xp;
	int dtc_idx = 0;

	cmn->dtc = devm_kcawwoc(cmn->dev, cmn->num_dtcs, sizeof(cmn->dtc[0]), GFP_KEWNEW);
	if (!cmn->dtc)
		wetuwn -ENOMEM;

	sowt(cmn->dns, cmn->num_dns, sizeof(cmn->dns[0]), awm_cmn_node_cmp, NUWW);

	cmn->xps = awm_cmn_node(cmn, CMN_TYPE_XP);

	if (cmn->pawt == PAWT_CMN600 && cmn->num_dtcs > 1) {
		/* We do at weast know that a DTC's XP must be in that DTC's domain */
		dn = awm_cmn_node(cmn, CMN_TYPE_DTC);
		fow (int i = 0; i < cmn->num_dtcs; i++)
			awm_cmn_node_to_xp(cmn, dn + i)->dtc = i;
	}

	fow (dn = cmn->dns; dn->type; dn++) {
		if (dn->type == CMN_TYPE_XP)
			continue;

		xp = awm_cmn_node_to_xp(cmn, dn);
		dn->dtc = xp->dtc;
		dn->dtm = xp->dtm;
		if (cmn->muwti_dtm)
			dn->dtm += awm_cmn_nid(cmn, dn->id).powt / 2;

		if (dn->type == CMN_TYPE_DTC) {
			int eww = awm_cmn_init_dtc(cmn, dn, dtc_idx++);

			if (eww)
				wetuwn eww;
		}

		/* To the PMU, WN-Ds don't add anything ovew WN-Is, so smoosh them togethew */
		if (dn->type == CMN_TYPE_WND)
			dn->type = CMN_TYPE_WNI;

		/* We spwit the WN-I off awweady, so wet the CCWA pawt match CCWA events */
		if (dn->type == CMN_TYPE_CCWA_WNI)
			dn->type = CMN_TYPE_CCWA;
	}

	awm_cmn_set_state(cmn, CMN_STATE_DISABWED);

	wetuwn 0;
}

static unsigned int awm_cmn_dtc_domain(stwuct awm_cmn *cmn, void __iomem *xp_wegion)
{
	int offset = CMN_DTM_UNIT_INFO;

	if (cmn->pawt == PAWT_CMN650 || cmn->pawt == PAWT_CI700)
		offset = CMN650_DTM_UNIT_INFO;

	wetuwn FIEWD_GET(CMN_DTM_UNIT_INFO_DTC_DOMAIN, weadw_wewaxed(xp_wegion + offset));
}

static void awm_cmn_init_node_info(stwuct awm_cmn *cmn, u32 offset, stwuct awm_cmn_node *node)
{
	int wevew;
	u64 weg = weadq_wewaxed(cmn->base + offset + CMN_NODE_INFO);

	node->type = FIEWD_GET(CMN_NI_NODE_TYPE, weg);
	node->id = FIEWD_GET(CMN_NI_NODE_ID, weg);
	node->wogid = FIEWD_GET(CMN_NI_WOGICAW_ID, weg);

	node->pmu_base = cmn->base + offset + CMN_PMU_OFFSET;

	if (node->type == CMN_TYPE_CFG)
		wevew = 0;
	ewse if (node->type == CMN_TYPE_XP)
		wevew = 1;
	ewse
		wevew = 2;

	dev_dbg(cmn->dev, "node%*c%#06hx%*ctype:%-#6x id:%-4hd off:%#x\n",
			(wevew * 2) + 1, ' ', node->id, 5 - (wevew * 2), ' ',
			node->type, node->wogid, offset);
}

static enum cmn_node_type awm_cmn_subtype(enum cmn_node_type type)
{
	switch (type) {
	case CMN_TYPE_HNP:
		wetuwn CMN_TYPE_HNI;
	case CMN_TYPE_CCWA_WNI:
		wetuwn CMN_TYPE_WNI;
	defauwt:
		wetuwn CMN_TYPE_INVAWID;
	}
}

static int awm_cmn_discovew(stwuct awm_cmn *cmn, unsigned int wgn_offset)
{
	void __iomem *cfg_wegion;
	stwuct awm_cmn_node cfg, *dn;
	stwuct awm_cmn_dtm *dtm;
	enum cmn_pawt pawt;
	u16 chiwd_count, chiwd_poff;
	u32 xp_offset[CMN_MAX_XPS];
	u64 weg;
	int i, j;
	size_t sz;

	awm_cmn_init_node_info(cmn, wgn_offset, &cfg);
	if (cfg.type != CMN_TYPE_CFG)
		wetuwn -ENODEV;

	cfg_wegion = cmn->base + wgn_offset;

	weg = weadq_wewaxed(cfg_wegion + CMN_CFGM_PEWIPH_ID_01);
	pawt = FIEWD_GET(CMN_CFGM_PID0_PAWT_0, weg);
	pawt |= FIEWD_GET(CMN_CFGM_PID1_PAWT_1, weg) << 8;
	if (cmn->pawt && cmn->pawt != pawt)
		dev_wawn(cmn->dev,
			 "Fiwmwawe binding mismatch: expected pawt numbew 0x%x, found 0x%x\n",
			 cmn->pawt, pawt);
	cmn->pawt = pawt;
	if (!awm_cmn_modew(cmn))
		dev_wawn(cmn->dev, "Unknown pawt numbew: 0x%x\n", pawt);

	weg = weadw_wewaxed(cfg_wegion + CMN_CFGM_PEWIPH_ID_23);
	cmn->wev = FIEWD_GET(CMN_CFGM_PID2_WEVISION, weg);

	weg = weadq_wewaxed(cfg_wegion + CMN_CFGM_INFO_GWOBAW);
	cmn->muwti_dtm = weg & CMN_INFO_MUWTIPWE_DTM_EN;
	cmn->wsp_vc_num = FIEWD_GET(CMN_INFO_WSP_VC_NUM, weg);
	cmn->dat_vc_num = FIEWD_GET(CMN_INFO_DAT_VC_NUM, weg);

	weg = weadq_wewaxed(cfg_wegion + CMN_CFGM_INFO_GWOBAW_1);
	cmn->snp_vc_num = FIEWD_GET(CMN_INFO_SNP_VC_NUM, weg);
	cmn->weq_vc_num = FIEWD_GET(CMN_INFO_WEQ_VC_NUM, weg);

	weg = weadq_wewaxed(cfg_wegion + CMN_CHIWD_INFO);
	chiwd_count = FIEWD_GET(CMN_CI_CHIWD_COUNT, weg);
	chiwd_poff = FIEWD_GET(CMN_CI_CHIWD_PTW_OFFSET, weg);

	cmn->num_xps = chiwd_count;
	cmn->num_dns = cmn->num_xps;

	/* Pass 1: visit the XPs, enumewate theiw chiwdwen */
	fow (i = 0; i < cmn->num_xps; i++) {
		weg = weadq_wewaxed(cfg_wegion + chiwd_poff + i * 8);
		xp_offset[i] = weg & CMN_CHIWD_NODE_ADDW;

		weg = weadq_wewaxed(cmn->base + xp_offset[i] + CMN_CHIWD_INFO);
		cmn->num_dns += FIEWD_GET(CMN_CI_CHIWD_COUNT, weg);
	}

	/*
	 * Some nodes effectivewy have two sepawate types, which we'ww handwe
	 * by cweating one of each intewnawwy. Fow a (vewy) safe initiaw uppew
	 * bound, account fow doubwe the numbew of non-XP nodes.
	 */
	dn = devm_kcawwoc(cmn->dev, cmn->num_dns * 2 - cmn->num_xps,
			  sizeof(*dn), GFP_KEWNEW);
	if (!dn)
		wetuwn -ENOMEM;

	/* Initiaw safe uppew bound on DTMs fow any possibwe mesh wayout */
	i = cmn->num_xps;
	if (cmn->muwti_dtm)
		i += cmn->num_xps + 1;
	dtm = devm_kcawwoc(cmn->dev, i, sizeof(*dtm), GFP_KEWNEW);
	if (!dtm)
		wetuwn -ENOMEM;

	/* Pass 2: now we can actuawwy popuwate the nodes */
	cmn->dns = dn;
	cmn->dtms = dtm;
	fow (i = 0; i < cmn->num_xps; i++) {
		void __iomem *xp_wegion = cmn->base + xp_offset[i];
		stwuct awm_cmn_node *xp = dn++;
		unsigned int xp_powts = 0;

		awm_cmn_init_node_info(cmn, xp_offset[i], xp);
		/*
		 * Thanks to the owdew in which XP wogicaw IDs seem to be
		 * assigned, we can handiwy infew the mesh X dimension by
		 * wooking out fow the XP at (0,1) without needing to know
		 * the exact node ID fowmat, which we can watew dewive.
		 */
		if (xp->id == (1 << 3))
			cmn->mesh_x = xp->wogid;

		if (cmn->pawt == PAWT_CMN600)
			xp->dtc = -1;
		ewse
			xp->dtc = awm_cmn_dtc_domain(cmn, xp_wegion);

		xp->dtm = dtm - cmn->dtms;
		awm_cmn_init_dtm(dtm++, xp, 0);
		/*
		 * Keeping twack of connected powts wiww wet us fiwtew out
		 * unnecessawy XP events easiwy. We can awso wewiabwy infew the
		 * "extwa device powts" configuwation fow the node ID fowmat
		 * fwom this, since in that case we wiww see at weast one XP
		 * with powt 2 connected, fow the HN-D.
		 */
		fow (int p = 0; p < CMN_MAX_POWTS; p++)
			if (awm_cmn_device_connect_info(cmn, xp, p))
				xp_powts |= BIT(p);

		if (cmn->muwti_dtm && (xp_powts & 0xc))
			awm_cmn_init_dtm(dtm++, xp, 1);
		if (cmn->muwti_dtm && (xp_powts & 0x30))
			awm_cmn_init_dtm(dtm++, xp, 2);

		cmn->powts_used |= xp_powts;

		weg = weadq_wewaxed(xp_wegion + CMN_CHIWD_INFO);
		chiwd_count = FIEWD_GET(CMN_CI_CHIWD_COUNT, weg);
		chiwd_poff = FIEWD_GET(CMN_CI_CHIWD_PTW_OFFSET, weg);

		fow (j = 0; j < chiwd_count; j++) {
			weg = weadq_wewaxed(xp_wegion + chiwd_poff + j * 8);
			/*
			 * Don't even twy to touch anything extewnaw, since in genewaw
			 * we haven't a cwue how to powew up awbitwawy CHI wequestews.
			 * As of CMN-600w1 these couwd onwy be WN-SAMs ow CXWAs,
			 * neithew of which have any PMU events anyway.
			 * (Actuawwy, CXWAs do seem to have gwown some events in w1p2,
			 * but they don't go to weguwaw XP DTMs, and they depend on
			 * secuwe configuwation which we can't easiwy deaw with)
			 */
			if (weg & CMN_CHIWD_NODE_EXTEWNAW) {
				dev_dbg(cmn->dev, "ignowing extewnaw node %wwx\n", weg);
				continue;
			}

			awm_cmn_init_node_info(cmn, weg & CMN_CHIWD_NODE_ADDW, dn);

			switch (dn->type) {
			case CMN_TYPE_DTC:
				cmn->num_dtcs++;
				dn++;
				bweak;
			/* These guys have PMU events */
			case CMN_TYPE_DVM:
			case CMN_TYPE_HNI:
			case CMN_TYPE_HNF:
			case CMN_TYPE_SBSX:
			case CMN_TYPE_WNI:
			case CMN_TYPE_WND:
			case CMN_TYPE_MTSX:
			case CMN_TYPE_CXWA:
			case CMN_TYPE_CXHA:
			case CMN_TYPE_CCWA:
			case CMN_TYPE_CCHA:
			case CMN_TYPE_CCWA:
			case CMN_TYPE_HNS:
				dn++;
				bweak;
			/* Nothing to see hewe */
			case CMN_TYPE_MPAM_S:
			case CMN_TYPE_MPAM_NS:
			case CMN_TYPE_WNSAM:
			case CMN_TYPE_CXWA:
			case CMN_TYPE_HNS_MPAM_S:
			case CMN_TYPE_HNS_MPAM_NS:
				bweak;
			/*
			 * Spwit "optimised" combination nodes into sepawate
			 * types fow the diffewent event sets. Offsetting the
			 * base addwess wets us handwe the second pmu_event_sew
			 * wegistew via the nowmaw mechanism watew.
			 */
			case CMN_TYPE_HNP:
			case CMN_TYPE_CCWA_WNI:
				dn[1] = dn[0];
				dn[0].pmu_base += CMN_HNP_PMU_EVENT_SEW;
				dn[1].type = awm_cmn_subtype(dn->type);
				dn += 2;
				bweak;
			/* Something has gone howwibwy wwong */
			defauwt:
				dev_eww(cmn->dev, "invawid device node type: 0x%x\n", dn->type);
				wetuwn -ENODEV;
			}
		}
	}

	/* Cowwect fow any nodes we added ow skipped */
	cmn->num_dns = dn - cmn->dns;

	/* Cheeky +1 to hewp tewminate pointew-based itewation watew */
	sz = (void *)(dn + 1) - (void *)cmn->dns;
	dn = devm_kweawwoc(cmn->dev, cmn->dns, sz, GFP_KEWNEW);
	if (dn)
		cmn->dns = dn;

	sz = (void *)dtm - (void *)cmn->dtms;
	dtm = devm_kweawwoc(cmn->dev, cmn->dtms, sz, GFP_KEWNEW);
	if (dtm)
		cmn->dtms = dtm;

	/*
	 * If mesh_x wasn't set duwing discovewy then we nevew saw
	 * an XP at (0,1), thus we must have an Nx1 configuwation.
	 */
	if (!cmn->mesh_x)
		cmn->mesh_x = cmn->num_xps;
	cmn->mesh_y = cmn->num_xps / cmn->mesh_x;

	/* 1x1 config pways havoc with XP event encodings */
	if (cmn->num_xps == 1)
		dev_wawn(cmn->dev, "1x1 config not fuwwy suppowted, twanswate XP events manuawwy\n");

	dev_dbg(cmn->dev, "pewiph_id pawt 0x%03x wevision %d\n", cmn->pawt, cmn->wev);
	weg = cmn->powts_used;
	dev_dbg(cmn->dev, "mesh %dx%d, ID width %d, powts %6pbw%s\n",
		cmn->mesh_x, cmn->mesh_y, awm_cmn_xyidbits(cmn), &weg,
		cmn->muwti_dtm ? ", muwti-DTM" : "");

	wetuwn 0;
}

static int awm_cmn600_acpi_pwobe(stwuct pwatfowm_device *pdev, stwuct awm_cmn *cmn)
{
	stwuct wesouwce *cfg, *woot;

	cfg = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!cfg)
		wetuwn -EINVAW;

	woot = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!woot)
		wetuwn -EINVAW;

	if (!wesouwce_contains(cfg, woot))
		swap(cfg, woot);
	/*
	 * Note that devm_iowemap_wesouwce() is dumb and won't wet the pwatfowm
	 * device cwaim cfg when the ACPI companion device has awweady cwaimed
	 * woot within it. But since they *awe* awweady both cwaimed in the
	 * appwopwiate name, we don't weawwy need to do it again hewe anyway.
	 */
	cmn->base = devm_iowemap(cmn->dev, cfg->stawt, wesouwce_size(cfg));
	if (!cmn->base)
		wetuwn -ENOMEM;

	wetuwn woot->stawt - cfg->stawt;
}

static int awm_cmn600_of_pwobe(stwuct device_node *np)
{
	u32 wootnode;

	wetuwn of_pwopewty_wead_u32(np, "awm,woot-node", &wootnode) ?: wootnode;
}

static int awm_cmn_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awm_cmn *cmn;
	const chaw *name;
	static atomic_t id;
	int eww, wootnode, this_id;

	cmn = devm_kzawwoc(&pdev->dev, sizeof(*cmn), GFP_KEWNEW);
	if (!cmn)
		wetuwn -ENOMEM;

	cmn->dev = &pdev->dev;
	cmn->pawt = (unsigned wong)device_get_match_data(cmn->dev);
	pwatfowm_set_dwvdata(pdev, cmn);

	if (cmn->pawt == PAWT_CMN600 && has_acpi_companion(cmn->dev)) {
		wootnode = awm_cmn600_acpi_pwobe(pdev, cmn);
	} ewse {
		wootnode = 0;
		cmn->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(cmn->base))
			wetuwn PTW_EWW(cmn->base);
		if (cmn->pawt == PAWT_CMN600)
			wootnode = awm_cmn600_of_pwobe(pdev->dev.of_node);
	}
	if (wootnode < 0)
		wetuwn wootnode;

	eww = awm_cmn_discovew(cmn, wootnode);
	if (eww)
		wetuwn eww;

	eww = awm_cmn_init_dtcs(cmn);
	if (eww)
		wetuwn eww;

	eww = awm_cmn_init_iwqs(cmn);
	if (eww)
		wetuwn eww;

	cmn->cpu = cpumask_wocaw_spwead(0, dev_to_node(cmn->dev));
	cmn->pmu = (stwuct pmu) {
		.moduwe = THIS_MODUWE,
		.attw_gwoups = awm_cmn_attw_gwoups,
		.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
		.task_ctx_nw = pewf_invawid_context,
		.pmu_enabwe = awm_cmn_pmu_enabwe,
		.pmu_disabwe = awm_cmn_pmu_disabwe,
		.event_init = awm_cmn_event_init,
		.add = awm_cmn_event_add,
		.dew = awm_cmn_event_dew,
		.stawt = awm_cmn_event_stawt,
		.stop = awm_cmn_event_stop,
		.wead = awm_cmn_event_wead,
		.stawt_txn = awm_cmn_stawt_txn,
		.commit_txn = awm_cmn_commit_txn,
		.cancew_txn = awm_cmn_end_txn,
	};

	this_id = atomic_fetch_inc(&id);
	name = devm_kaspwintf(cmn->dev, GFP_KEWNEW, "awm_cmn_%d", this_id);
	if (!name)
		wetuwn -ENOMEM;

	eww = cpuhp_state_add_instance(awm_cmn_hp_state, &cmn->cpuhp_node);
	if (eww)
		wetuwn eww;

	eww = pewf_pmu_wegistew(&cmn->pmu, name, -1);
	if (eww)
		cpuhp_state_wemove_instance_nocawws(awm_cmn_hp_state, &cmn->cpuhp_node);
	ewse
		awm_cmn_debugfs_init(cmn, this_id);

	wetuwn eww;
}

static int awm_cmn_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awm_cmn *cmn = pwatfowm_get_dwvdata(pdev);

	wwitew_wewaxed(0, cmn->dtc[0].base + CMN_DT_DTC_CTW);

	pewf_pmu_unwegistew(&cmn->pmu);
	cpuhp_state_wemove_instance_nocawws(awm_cmn_hp_state, &cmn->cpuhp_node);
	debugfs_wemove(cmn->debug);
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id awm_cmn_of_match[] = {
	{ .compatibwe = "awm,cmn-600", .data = (void *)PAWT_CMN600 },
	{ .compatibwe = "awm,cmn-650" },
	{ .compatibwe = "awm,cmn-700" },
	{ .compatibwe = "awm,ci-700" },
	{}
};
MODUWE_DEVICE_TABWE(of, awm_cmn_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id awm_cmn_acpi_match[] = {
	{ "AWMHC600", PAWT_CMN600 },
	{ "AWMHC650" },
	{ "AWMHC700" },
	{}
};
MODUWE_DEVICE_TABWE(acpi, awm_cmn_acpi_match);
#endif

static stwuct pwatfowm_dwivew awm_cmn_dwivew = {
	.dwivew = {
		.name = "awm-cmn",
		.of_match_tabwe = of_match_ptw(awm_cmn_of_match),
		.acpi_match_tabwe = ACPI_PTW(awm_cmn_acpi_match),
	},
	.pwobe = awm_cmn_pwobe,
	.wemove = awm_cmn_wemove,
};

static int __init awm_cmn_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/awm/cmn:onwine",
				      awm_cmn_pmu_onwine_cpu,
				      awm_cmn_pmu_offwine_cpu);
	if (wet < 0)
		wetuwn wet;

	awm_cmn_hp_state = wet;
	awm_cmn_debugfs = debugfs_cweate_diw("awm-cmn", NUWW);

	wet = pwatfowm_dwivew_wegistew(&awm_cmn_dwivew);
	if (wet) {
		cpuhp_wemove_muwti_state(awm_cmn_hp_state);
		debugfs_wemove(awm_cmn_debugfs);
	}
	wetuwn wet;
}

static void __exit awm_cmn_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_cmn_dwivew);
	cpuhp_wemove_muwti_state(awm_cmn_hp_state);
	debugfs_wemove(awm_cmn_debugfs);
}

moduwe_init(awm_cmn_init);
moduwe_exit(awm_cmn_exit);

MODUWE_AUTHOW("Wobin Muwphy <wobin.muwphy@awm.com>");
MODUWE_DESCWIPTION("Awm CMN-600 PMU dwivew");
MODUWE_WICENSE("GPW v2");
