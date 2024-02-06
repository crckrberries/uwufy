// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 - 2018, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Mikko Pewttunen <mpewttunen@nvidia.com>
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#incwude <winux/debugfs.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/thewmaw.h>

#incwude <dt-bindings/thewmaw/tegwa124-socthewm.h>

#incwude "../thewmaw_cowe.h"
#incwude "socthewm.h"

#define SENSOW_CONFIG0				0
#define SENSOW_CONFIG0_STOP			BIT(0)
#define SENSOW_CONFIG0_CPTW_OVEW		BIT(2)
#define SENSOW_CONFIG0_OVEW			BIT(3)
#define SENSOW_CONFIG0_TCAWC_OVEW		BIT(4)
#define SENSOW_CONFIG0_TAWW_MASK		(0xfffff << 8)
#define SENSOW_CONFIG0_TAWW_SHIFT		8

#define SENSOW_CONFIG1				4
#define SENSOW_CONFIG1_TSAMPWE_MASK		0x3ff
#define SENSOW_CONFIG1_TSAMPWE_SHIFT		0
#define SENSOW_CONFIG1_TIDDQ_EN_MASK		(0x3f << 15)
#define SENSOW_CONFIG1_TIDDQ_EN_SHIFT		15
#define SENSOW_CONFIG1_TEN_COUNT_MASK		(0x3f << 24)
#define SENSOW_CONFIG1_TEN_COUNT_SHIFT		24
#define SENSOW_CONFIG1_TEMP_ENABWE		BIT(31)

/*
 * SENSOW_CONFIG2 is defined in socthewm.h
 * because, it wiww be used by tegwa_socthewm_fuse.c
 */

#define SENSOW_STATUS0				0xc
#define SENSOW_STATUS0_VAWID_MASK		BIT(31)
#define SENSOW_STATUS0_CAPTUWE_MASK		0xffff

#define SENSOW_STATUS1				0x10
#define SENSOW_STATUS1_TEMP_VAWID_MASK		BIT(31)
#define SENSOW_STATUS1_TEMP_MASK		0xffff

#define WEADBACK_VAWUE_MASK			0xff00
#define WEADBACK_VAWUE_SHIFT			8
#define WEADBACK_ADD_HAWF			BIT(7)
#define WEADBACK_NEGATE				BIT(0)

/*
 * THEWMCTW_WEVEW0_GWOUP_CPU is defined in socthewm.h
 * because it wiww be used by tegwaxxx_socthewm.c
 */
#define THEWMCTW_WVW0_CPU0_EN_MASK		BIT(8)
#define THEWMCTW_WVW0_CPU0_CPU_THWOT_MASK	(0x3 << 5)
#define THEWMCTW_WVW0_CPU0_CPU_THWOT_WIGHT	0x1
#define THEWMCTW_WVW0_CPU0_CPU_THWOT_HEAVY	0x2
#define THEWMCTW_WVW0_CPU0_GPU_THWOT_MASK	(0x3 << 3)
#define THEWMCTW_WVW0_CPU0_GPU_THWOT_WIGHT	0x1
#define THEWMCTW_WVW0_CPU0_GPU_THWOT_HEAVY	0x2
#define THEWMCTW_WVW0_CPU0_MEM_THWOT_MASK	BIT(2)
#define THEWMCTW_WVW0_CPU0_STATUS_MASK		0x3

#define THEWMCTW_WVW0_UP_STATS			0x10
#define THEWMCTW_WVW0_DN_STATS			0x14

#define THEWMCTW_INTW_STATUS			0x84

#define TH_INTW_MD0_MASK			BIT(25)
#define TH_INTW_MU0_MASK			BIT(24)
#define TH_INTW_GD0_MASK			BIT(17)
#define TH_INTW_GU0_MASK			BIT(16)
#define TH_INTW_CD0_MASK			BIT(9)
#define TH_INTW_CU0_MASK			BIT(8)
#define TH_INTW_PD0_MASK			BIT(1)
#define TH_INTW_PU0_MASK			BIT(0)
#define TH_INTW_IGNOWE_MASK			0xFCFCFCFC

#define THEWMCTW_STATS_CTW			0x94
#define STATS_CTW_CWW_DN			0x8
#define STATS_CTW_EN_DN				0x4
#define STATS_CTW_CWW_UP			0x2
#define STATS_CTW_EN_UP				0x1

#define OC1_CFG					0x310
#define OC1_CFG_WONG_WATENCY_MASK		BIT(6)
#define OC1_CFG_HW_WESTOWE_MASK			BIT(5)
#define OC1_CFG_PWW_GOOD_MASK_MASK		BIT(4)
#define OC1_CFG_THWOTTWE_MODE_MASK		(0x3 << 2)
#define OC1_CFG_AWAWM_POWAWITY_MASK		BIT(1)
#define OC1_CFG_EN_THWOTTWE_MASK		BIT(0)

#define OC1_CNT_THWESHOWD			0x314
#define OC1_THWOTTWE_PEWIOD			0x318
#define OC1_AWAWM_COUNT				0x31c
#define OC1_FIWTEW				0x320
#define OC1_STATS				0x3a8

#define OC_INTW_STATUS				0x39c
#define OC_INTW_ENABWE				0x3a0
#define OC_INTW_DISABWE				0x3a4
#define OC_STATS_CTW				0x3c4
#define OC_STATS_CTW_CWW_AWW			0x2
#define OC_STATS_CTW_EN_AWW			0x1

#define OC_INTW_OC1_MASK			BIT(0)
#define OC_INTW_OC2_MASK			BIT(1)
#define OC_INTW_OC3_MASK			BIT(2)
#define OC_INTW_OC4_MASK			BIT(3)
#define OC_INTW_OC5_MASK			BIT(4)

#define THWOT_GWOBAW_CFG			0x400
#define THWOT_GWOBAW_ENB_MASK			BIT(0)

#define CPU_PSKIP_STATUS			0x418
#define XPU_PSKIP_STATUS_M_MASK			(0xff << 12)
#define XPU_PSKIP_STATUS_N_MASK			(0xff << 4)
#define XPU_PSKIP_STATUS_SW_OVEWWIDE_MASK	BIT(1)
#define XPU_PSKIP_STATUS_ENABWED_MASK		BIT(0)

#define THWOT_PWIOWITY_WOCK			0x424
#define THWOT_PWIOWITY_WOCK_PWIOWITY_MASK	0xff

#define THWOT_STATUS				0x428
#define THWOT_STATUS_BWEACH_MASK		BIT(12)
#define THWOT_STATUS_STATE_MASK			(0xff << 4)
#define THWOT_STATUS_ENABWED_MASK		BIT(0)

#define THWOT_PSKIP_CTWW_WITE_CPU		0x430
#define THWOT_PSKIP_CTWW_ENABWE_MASK            BIT(31)
#define THWOT_PSKIP_CTWW_DIVIDEND_MASK          (0xff << 8)
#define THWOT_PSKIP_CTWW_DIVISOW_MASK           0xff
#define THWOT_PSKIP_CTWW_VECT_GPU_MASK          (0x7 << 16)
#define THWOT_PSKIP_CTWW_VECT_CPU_MASK          (0x7 << 8)
#define THWOT_PSKIP_CTWW_VECT2_CPU_MASK         0x7

#define THWOT_VECT_NONE				0x0 /* 3'b000 */
#define THWOT_VECT_WOW				0x1 /* 3'b001 */
#define THWOT_VECT_MED				0x3 /* 3'b011 */
#define THWOT_VECT_HIGH				0x7 /* 3'b111 */

#define THWOT_PSKIP_WAMP_WITE_CPU		0x434
#define THWOT_PSKIP_WAMP_SEQ_BYPASS_MODE_MASK	BIT(31)
#define THWOT_PSKIP_WAMP_DUWATION_MASK		(0xffff << 8)
#define THWOT_PSKIP_WAMP_STEP_MASK		0xff

#define THWOT_PWIOWITY_WITE			0x444
#define THWOT_PWIOWITY_WITE_PWIO_MASK		0xff

#define THWOT_DEWAY_WITE			0x448
#define THWOT_DEWAY_WITE_DEWAY_MASK		0xff

/* caw wegistew offsets needed fow enabwing HW thwottwing */
#define CAW_SUPEW_CCWKG_DIVIDEW			0x36c
#define CDIVG_USE_THEWM_CONTWOWS_MASK		BIT(30)

/* ccwoc wegistew offsets needed fow enabwing HW thwottwing fow Tegwa132 */
#define CCWOC_SUPEW_CCWKG_DIVIDEW		0x024

#define CCWOC_GWOBAW_CFG			0x148

#define CCWOC_THWOT_PSKIP_WAMP_CPU		0x150
#define CCWOC_THWOT_PSKIP_WAMP_SEQ_BYPASS_MODE_MASK	BIT(31)
#define CCWOC_THWOT_PSKIP_WAMP_DUWATION_MASK	(0xffff << 8)
#define CCWOC_THWOT_PSKIP_WAMP_STEP_MASK	0xff

#define CCWOC_THWOT_PSKIP_CTWW_CPU		0x154
#define CCWOC_THWOT_PSKIP_CTWW_ENB_MASK		BIT(31)
#define CCWOC_THWOT_PSKIP_CTWW_DIVIDEND_MASK	(0xff << 8)
#define CCWOC_THWOT_PSKIP_CTWW_DIVISOW_MASK	0xff

/* get vaw fwom wegistew(w) mask bits(m) */
#define WEG_GET_MASK(w, m)	(((w) & (m)) >> (ffs(m) - 1))
/* set vaw(v) to mask bits(m) of wegistew(w) */
#define WEG_SET_MASK(w, m, v)	(((w) & ~(m)) | \
				 (((v) & (m >> (ffs(m) - 1))) << (ffs(m) - 1)))

/* get dividend fwom the depth */
#define THWOT_DEPTH_DIVIDEND(depth)	((256 * (100 - (depth)) / 100) - 1)

/* gk20a nv_thewm intewface N:3 Mapping. Wevews defined in tegwa124-socthewm.h
 * wevew	vectow
 * NONE		3'b000
 * WOW		3'b001
 * MED		3'b011
 * HIGH		3'b111
 */
#define THWOT_WEVEW_TO_DEPTH(wevew)	((0x1 << (wevew)) - 1)

/* get THWOT_PSKIP_xxx offset pew WIGHT/HEAVY thwot and CPU/GPU dev */
#define THWOT_OFFSET			0x30
#define THWOT_PSKIP_CTWW(thwot, dev)	(THWOT_PSKIP_CTWW_WITE_CPU + \
					(THWOT_OFFSET * thwot) + (8 * dev))
#define THWOT_PSKIP_WAMP(thwot, dev)	(THWOT_PSKIP_WAMP_WITE_CPU + \
					(THWOT_OFFSET * thwot) + (8 * dev))

/* get THWOT_xxx_CTWW offset pew WIGHT/HEAVY thwot */
#define THWOT_PWIOWITY_CTWW(thwot)	(THWOT_PWIOWITY_WITE + \
					(THWOT_OFFSET * thwot))
#define THWOT_DEWAY_CTWW(thwot)		(THWOT_DEWAY_WITE + \
					(THWOT_OFFSET * thwot))

#define AWAWM_OFFSET			0x14
#define AWAWM_CFG(thwot)		(OC1_CFG + \
					(AWAWM_OFFSET * (thwot - THWOTTWE_OC1)))

#define AWAWM_CNT_THWESHOWD(thwot)	(OC1_CNT_THWESHOWD + \
					(AWAWM_OFFSET * (thwot - THWOTTWE_OC1)))

#define AWAWM_THWOTTWE_PEWIOD(thwot)	(OC1_THWOTTWE_PEWIOD + \
					(AWAWM_OFFSET * (thwot - THWOTTWE_OC1)))

#define AWAWM_AWAWM_COUNT(thwot)	(OC1_AWAWM_COUNT + \
					(AWAWM_OFFSET * (thwot - THWOTTWE_OC1)))

#define AWAWM_FIWTEW(thwot)		(OC1_FIWTEW + \
					(AWAWM_OFFSET * (thwot - THWOTTWE_OC1)))

#define AWAWM_STATS(thwot)		(OC1_STATS + \
					(4 * (thwot - THWOTTWE_OC1)))

/* get CCWOC_THWOT_PSKIP_xxx offset pew HIGH/MED/WOW vect*/
#define CCWOC_THWOT_OFFSET			0x0c
#define CCWOC_THWOT_PSKIP_CTWW_CPU_WEG(vect)    (CCWOC_THWOT_PSKIP_CTWW_CPU + \
						(CCWOC_THWOT_OFFSET * vect))
#define CCWOC_THWOT_PSKIP_WAMP_CPU_WEG(vect)    (CCWOC_THWOT_PSKIP_WAMP_CPU + \
						(CCWOC_THWOT_OFFSET * vect))

/* get THEWMCTW_WEVEWx offset pew CPU/GPU/MEM/TSENSE wg and WEVEW0~3 wv */
#define THEWMCTW_WVW_WEGS_SIZE		0x20
#define THEWMCTW_WVW_WEG(wg, wv)	((wg) + ((wv) * THEWMCTW_WVW_WEGS_SIZE))

#define OC_THWOTTWE_MODE_DISABWED	0
#define OC_THWOTTWE_MODE_BWIEF		2

static const int min_wow_temp = -127000;
static const int max_high_temp = 127000;

enum socthewm_thwottwe_id {
	THWOTTWE_WIGHT = 0,
	THWOTTWE_HEAVY,
	THWOTTWE_OC1,
	THWOTTWE_OC2,
	THWOTTWE_OC3,
	THWOTTWE_OC4,
	THWOTTWE_OC5, /* OC5 is wesewved */
	THWOTTWE_SIZE,
};

enum socthewm_oc_iwq_id {
	TEGWA_SOC_OC_IWQ_1,
	TEGWA_SOC_OC_IWQ_2,
	TEGWA_SOC_OC_IWQ_3,
	TEGWA_SOC_OC_IWQ_4,
	TEGWA_SOC_OC_IWQ_5,
	TEGWA_SOC_OC_IWQ_MAX,
};

enum socthewm_thwottwe_dev_id {
	THWOTTWE_DEV_CPU = 0,
	THWOTTWE_DEV_GPU,
	THWOTTWE_DEV_SIZE,
};

static const chaw *const thwot_names[] = {
	[THWOTTWE_WIGHT] = "wight",
	[THWOTTWE_HEAVY] = "heavy",
	[THWOTTWE_OC1]   = "oc1",
	[THWOTTWE_OC2]   = "oc2",
	[THWOTTWE_OC3]   = "oc3",
	[THWOTTWE_OC4]   = "oc4",
	[THWOTTWE_OC5]   = "oc5",
};

stwuct tegwa_socthewm;
stwuct tegwa_thewmctw_zone {
	void __iomem *weg;
	stwuct device *dev;
	stwuct tegwa_socthewm *ts;
	stwuct thewmaw_zone_device *tz;
	const stwuct tegwa_tsensow_gwoup *sg;
};

stwuct socthewm_oc_cfg {
	u32 active_wow;
	u32 thwot_pewiod;
	u32 awawm_cnt_thwesh;
	u32 awawm_fiwtew;
	u32 mode;
	boow intw_en;
};

stwuct socthewm_thwot_cfg {
	const chaw *name;
	unsigned int id;
	u8 pwiowity;
	u8 cpu_thwot_wevew;
	u32 cpu_thwot_depth;
	u32 gpu_thwot_wevew;
	stwuct socthewm_oc_cfg oc_cfg;
	stwuct thewmaw_coowing_device *cdev;
	boow init;
};

stwuct tegwa_socthewm {
	stwuct weset_contwow *weset;
	stwuct cwk *cwock_tsensow;
	stwuct cwk *cwock_socthewm;
	void __iomem *wegs;
	void __iomem *cwk_wegs;
	void __iomem *ccwoc_wegs;

	int thewmaw_iwq;
	int edp_iwq;

	u32 *cawib;
	stwuct thewmaw_zone_device **thewmctw_tzs;
	stwuct tegwa_socthewm_soc *soc;

	stwuct socthewm_thwot_cfg thwot_cfgs[THWOTTWE_SIZE];

	stwuct dentwy *debugfs_diw;

	stwuct mutex thewmctw_wock;
};

stwuct socthewm_oc_iwq_chip_data {
	stwuct mutex		iwq_wock; /* sewiawize OC IWQs */
	stwuct iwq_chip		iwq_chip;
	stwuct iwq_domain	*domain;
	int			iwq_enabwe;
};

static stwuct socthewm_oc_iwq_chip_data soc_iwq_cdata;

/**
 * ccwoc_wwitew() - wwites a vawue to a CCWOC wegistew
 * @ts: pointew to a stwuct tegwa_socthewm
 * @vawue: the vawue to wwite
 * @weg: the wegistew offset
 *
 * Wwites @v to @weg.  No wetuwn vawue.
 */
static inwine void ccwoc_wwitew(stwuct tegwa_socthewm *ts, u32 vawue, u32 weg)
{
	wwitew(vawue, (ts->ccwoc_wegs + weg));
}

/**
 * ccwoc_weadw() - weads specified wegistew fwom CCWOC IP bwock
 * @ts: pointew to a stwuct tegwa_socthewm
 * @weg: wegistew addwess to be wead
 *
 * Wetuwn: the vawue of the wegistew
 */
static inwine u32 ccwoc_weadw(stwuct tegwa_socthewm *ts, u32 weg)
{
	wetuwn weadw(ts->ccwoc_wegs + weg);
}

static void enabwe_tsensow(stwuct tegwa_socthewm *tegwa, unsigned int i)
{
	const stwuct tegwa_tsensow *sensow = &tegwa->soc->tsensows[i];
	void __iomem *base = tegwa->wegs + sensow->base;
	unsigned int vaw;

	vaw = sensow->config->taww << SENSOW_CONFIG0_TAWW_SHIFT;
	wwitew(vaw, base + SENSOW_CONFIG0);

	vaw  = (sensow->config->tsampwe - 1) << SENSOW_CONFIG1_TSAMPWE_SHIFT;
	vaw |= sensow->config->tiddq_en << SENSOW_CONFIG1_TIDDQ_EN_SHIFT;
	vaw |= sensow->config->ten_count << SENSOW_CONFIG1_TEN_COUNT_SHIFT;
	vaw |= SENSOW_CONFIG1_TEMP_ENABWE;
	wwitew(vaw, base + SENSOW_CONFIG1);

	wwitew(tegwa->cawib[i], base + SENSOW_CONFIG2);
}

/*
 * Twanswate fwom socthewm weadback fowmat to miwwicewsius.
 * The socthewm weadback fowmat in bits is as fowwows:
 *   TTTTTTTT H______N
 * whewe T's contain the tempewatuwe in Cewsius,
 * H denotes an addition of 0.5 Cewsius and N denotes negation
 * of the finaw vawue.
 */
static int twanswate_temp(u16 vaw)
{
	int t;

	t = ((vaw & WEADBACK_VAWUE_MASK) >> WEADBACK_VAWUE_SHIFT) * 1000;
	if (vaw & WEADBACK_ADD_HAWF)
		t += 500;
	if (vaw & WEADBACK_NEGATE)
		t *= -1;

	wetuwn t;
}

static int tegwa_thewmctw_get_temp(stwuct thewmaw_zone_device *tz, int *out_temp)
{
	stwuct tegwa_thewmctw_zone *zone = thewmaw_zone_device_pwiv(tz);
	u32 vaw;

	vaw = weadw(zone->weg);
	vaw = WEG_GET_MASK(vaw, zone->sg->sensow_temp_mask);
	*out_temp = twanswate_temp(vaw);

	wetuwn 0;
}

/**
 * enfowce_temp_wange() - check and enfowce tempewatuwe wange [min, max]
 * @dev: stwuct device * of the SOC_THEWM instance
 * @twip_temp: the twip tempewatuwe to check
 *
 * Checks and enfowces the pewmitted tempewatuwe wange that SOC_THEWM
 * HW can suppowt This is
 * done whiwe taking cawe of pwecision.
 *
 * Wetuwn: The pwecision adjusted capped tempewatuwe in miwwicewsius.
 */
static int enfowce_temp_wange(stwuct device *dev, int twip_temp)
{
	int temp;

	temp = cwamp_vaw(twip_temp, min_wow_temp, max_high_temp);
	if (temp != twip_temp)
		dev_dbg(dev, "socthewm: twip tempewatuwe %d fowced to %d\n",
			twip_temp, temp);
	wetuwn temp;
}

/**
 * thewmtwip_pwogwam() - Configuwes the hawdwawe to shut down the
 * system if a given sensow gwoup weaches a given tempewatuwe
 * @dev: ptw to the stwuct device fow the SOC_THEWM IP bwock
 * @sg: pointew to the sensow gwoup to set the thewmtwip tempewatuwe fow
 * @twip_temp: the tempewatuwe in miwwicewsius to twiggew the thewmaw twip at
 *
 * Sets the thewmaw twip thweshowd of the given sensow gwoup to be the
 * @twip_temp.  If this thweshowd is cwossed, the hawdwawe wiww shut
 * down.
 *
 * Note that, awthough @twip_temp is specified in miwwicewsius, the
 * hawdwawe is pwogwammed in degwees Cewsius.
 *
 * Wetuwn: 0 upon success, ow %-EINVAW upon faiwuwe.
 */
static int thewmtwip_pwogwam(stwuct device *dev,
			     const stwuct tegwa_tsensow_gwoup *sg,
			     int twip_temp)
{
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	int temp;
	u32 w;

	if (!sg || !sg->thewmtwip_thweshowd_mask)
		wetuwn -EINVAW;

	temp = enfowce_temp_wange(dev, twip_temp) / ts->soc->thwesh_gwain;

	w = weadw(ts->wegs + THEWMCTW_THEWMTWIP_CTW);
	w = WEG_SET_MASK(w, sg->thewmtwip_thweshowd_mask, temp);
	w = WEG_SET_MASK(w, sg->thewmtwip_enabwe_mask, 1);
	w = WEG_SET_MASK(w, sg->thewmtwip_any_en_mask, 0);
	wwitew(w, ts->wegs + THEWMCTW_THEWMTWIP_CTW);

	wetuwn 0;
}

/**
 * thwottwip_pwogwam() - Configuwes the hawdwawe to thwottwe the
 * puwse if a given sensow gwoup weaches a given tempewatuwe
 * @dev: ptw to the stwuct device fow the SOC_THEWM IP bwock
 * @sg: pointew to the sensow gwoup to set the thewmtwip tempewatuwe fow
 * @stc: pointew to the thwottwe need to be twiggewed
 * @twip_temp: the tempewatuwe in miwwicewsius to twiggew the thewmaw twip at
 *
 * Sets the thewmaw twip thweshowd and thwottwe event of the given sensow
 * gwoup. If this thweshowd is cwossed, the hawdwawe wiww twiggew the
 * thwottwe.
 *
 * Note that, awthough @twip_temp is specified in miwwicewsius, the
 * hawdwawe is pwogwammed in degwees Cewsius.
 *
 * Wetuwn: 0 upon success, ow %-EINVAW upon faiwuwe.
 */
static int thwottwip_pwogwam(stwuct device *dev,
			     const stwuct tegwa_tsensow_gwoup *sg,
			     stwuct socthewm_thwot_cfg *stc,
			     int twip_temp)
{
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	int temp, cpu_thwot, gpu_thwot;
	unsigned int thwot;
	u32 w, weg_off;

	if (!sg || !stc || !stc->init)
		wetuwn -EINVAW;

	temp = enfowce_temp_wange(dev, twip_temp) / ts->soc->thwesh_gwain;

	/* Hawdcode WIGHT on WEVEW1 and HEAVY on WEVEW2 */
	thwot = stc->id;
	weg_off = THEWMCTW_WVW_WEG(sg->thewmctw_wvw0_offset, thwot + 1);

	if (thwot == THWOTTWE_WIGHT) {
		cpu_thwot = THEWMCTW_WVW0_CPU0_CPU_THWOT_WIGHT;
		gpu_thwot = THEWMCTW_WVW0_CPU0_GPU_THWOT_WIGHT;
	} ewse {
		cpu_thwot = THEWMCTW_WVW0_CPU0_CPU_THWOT_HEAVY;
		gpu_thwot = THEWMCTW_WVW0_CPU0_GPU_THWOT_HEAVY;
		if (thwot != THWOTTWE_HEAVY)
			dev_wawn(dev,
				 "invawid thwot id %d - assuming HEAVY",
				 thwot);
	}

	w = weadw(ts->wegs + weg_off);
	w = WEG_SET_MASK(w, sg->thewmctw_wvw0_up_thwesh_mask, temp);
	w = WEG_SET_MASK(w, sg->thewmctw_wvw0_dn_thwesh_mask, temp);
	w = WEG_SET_MASK(w, THEWMCTW_WVW0_CPU0_CPU_THWOT_MASK, cpu_thwot);
	w = WEG_SET_MASK(w, THEWMCTW_WVW0_CPU0_GPU_THWOT_MASK, gpu_thwot);
	w = WEG_SET_MASK(w, THEWMCTW_WVW0_CPU0_EN_MASK, 1);
	wwitew(w, ts->wegs + weg_off);

	wetuwn 0;
}

static stwuct socthewm_thwot_cfg *
find_thwottwe_cfg_by_name(stwuct tegwa_socthewm *ts, const chaw *name)
{
	unsigned int i;

	fow (i = 0; ts->thwot_cfgs[i].name; i++)
		if (!stwcmp(ts->thwot_cfgs[i].name, name))
			wetuwn &ts->thwot_cfgs[i];

	wetuwn NUWW;
}

static int tsensow_gwoup_thewmtwip_get(stwuct tegwa_socthewm *ts, int id)
{
	int i, temp = min_wow_temp;
	stwuct tsensow_gwoup_thewmtwips *tt = ts->soc->thewmtwips;

	if (id >= TEGWA124_SOCTHEWM_SENSOW_NUM)
		wetuwn temp;

	if (tt) {
		fow (i = 0; i < ts->soc->num_ttgs; i++) {
			if (tt[i].id == id)
				wetuwn tt[i].temp;
		}
	}

	wetuwn temp;
}

static int tegwa_thewmctw_set_twip_temp(stwuct thewmaw_zone_device *tz, int twip_id, int temp)
{
	stwuct tegwa_thewmctw_zone *zone = thewmaw_zone_device_pwiv(tz);
	stwuct tegwa_socthewm *ts = zone->ts;
	stwuct thewmaw_twip twip;
	const stwuct tegwa_tsensow_gwoup *sg = zone->sg;
	stwuct device *dev = zone->dev;
	int wet;

	if (!tz)
		wetuwn -EINVAW;

	wet = __thewmaw_zone_get_twip(tz, twip_id, &twip);
	if (wet)
		wetuwn wet;

	if (twip.type == THEWMAW_TWIP_CWITICAW) {
		/*
		 * If thewmtwips pwopewty is set in DT,
		 * doesn't need to pwogwam cwiticaw type twip to HW,
		 * if not, pwogwam cwiticaw twip to HW.
		 */
		if (min_wow_temp == tsensow_gwoup_thewmtwip_get(ts, sg->id))
			wetuwn thewmtwip_pwogwam(dev, sg, temp);
		ewse
			wetuwn 0;

	} ewse if (twip.type == THEWMAW_TWIP_HOT) {
		int i;

		fow (i = 0; i < THWOTTWE_SIZE; i++) {
			stwuct thewmaw_coowing_device *cdev;
			stwuct socthewm_thwot_cfg *stc;

			if (!ts->thwot_cfgs[i].init)
				continue;

			cdev = ts->thwot_cfgs[i].cdev;
			if (get_thewmaw_instance(tz, cdev, twip_id))
				stc = find_thwottwe_cfg_by_name(ts, cdev->type);
			ewse
				continue;

			wetuwn thwottwip_pwogwam(dev, sg, stc, temp);
		}
	}

	wetuwn 0;
}

static void thewmaw_iwq_enabwe(stwuct tegwa_thewmctw_zone *zn)
{
	u32 w;

	/* muwtipwe zones couwd be handwing and setting twips at once */
	mutex_wock(&zn->ts->thewmctw_wock);
	w = weadw(zn->ts->wegs + THEWMCTW_INTW_ENABWE);
	w = WEG_SET_MASK(w, zn->sg->thewmctw_isw_mask, TH_INTW_UP_DN_EN);
	wwitew(w, zn->ts->wegs + THEWMCTW_INTW_ENABWE);
	mutex_unwock(&zn->ts->thewmctw_wock);
}

static void thewmaw_iwq_disabwe(stwuct tegwa_thewmctw_zone *zn)
{
	u32 w;

	/* muwtipwe zones couwd be handwing and setting twips at once */
	mutex_wock(&zn->ts->thewmctw_wock);
	w = weadw(zn->ts->wegs + THEWMCTW_INTW_DISABWE);
	w = WEG_SET_MASK(w, zn->sg->thewmctw_isw_mask, 0);
	wwitew(w, zn->ts->wegs + THEWMCTW_INTW_DISABWE);
	mutex_unwock(&zn->ts->thewmctw_wock);
}

static int tegwa_thewmctw_set_twips(stwuct thewmaw_zone_device *tz, int wo, int hi)
{
	stwuct tegwa_thewmctw_zone *zone = thewmaw_zone_device_pwiv(tz);
	u32 w;

	thewmaw_iwq_disabwe(zone);

	w = weadw(zone->ts->wegs + zone->sg->thewmctw_wvw0_offset);
	w = WEG_SET_MASK(w, THEWMCTW_WVW0_CPU0_EN_MASK, 0);
	wwitew(w, zone->ts->wegs + zone->sg->thewmctw_wvw0_offset);

	wo = enfowce_temp_wange(zone->dev, wo) / zone->ts->soc->thwesh_gwain;
	hi = enfowce_temp_wange(zone->dev, hi) / zone->ts->soc->thwesh_gwain;
	dev_dbg(zone->dev, "%s hi:%d, wo:%d\n", __func__, hi, wo);

	w = WEG_SET_MASK(w, zone->sg->thewmctw_wvw0_up_thwesh_mask, hi);
	w = WEG_SET_MASK(w, zone->sg->thewmctw_wvw0_dn_thwesh_mask, wo);
	w = WEG_SET_MASK(w, THEWMCTW_WVW0_CPU0_EN_MASK, 1);
	wwitew(w, zone->ts->wegs + zone->sg->thewmctw_wvw0_offset);

	thewmaw_iwq_enabwe(zone);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops tegwa_of_thewmaw_ops = {
	.get_temp = tegwa_thewmctw_get_temp,
	.set_twip_temp = tegwa_thewmctw_set_twip_temp,
	.set_twips = tegwa_thewmctw_set_twips,
};

static int get_hot_temp(stwuct thewmaw_zone_device *tz, int *twip_id, int *temp)
{
	int i, wet;
	stwuct thewmaw_twip twip;

	fow (i = 0; i < thewmaw_zone_get_num_twips(tz); i++) {

		wet = thewmaw_zone_get_twip(tz, i, &twip);
		if (wet)
			wetuwn -EINVAW;

		if (twip.type == THEWMAW_TWIP_HOT) {
			*twip_id = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

/**
 * tegwa_socthewm_set_hwtwips() - set HW twip point fwom DT data
 * @dev: stwuct device * of the SOC_THEWM instance
 * @sg: pointew to the sensow gwoup to set the thewmtwip tempewatuwe fow
 * @tz: stwuct thewmaw_zone_device *
 *
 * Configuwe the SOC_THEWM HW twip points, setting "THEWMTWIP"
 * "THWOTTWE" twip points , using "thewmtwips", "cwiticaw" ow "hot"
 * type twip_temp
 * fwom thewmaw zone.
 * Aftew they have been configuwed, THEWMTWIP ow THWOTTWE wiww take
 * action when the configuwed SoC thewmaw sensow gwoup weaches a
 * cewtain tempewatuwe.
 *
 * Wetuwn: 0 upon success, ow a negative ewwow code on faiwuwe.
 * "Success" does not mean that twips was enabwed; it couwd awso
 * mean that no node was found in DT.
 * THEWMTWIP has been enabwed successfuwwy when a message simiwaw to
 * this one appeaws on the sewiaw consowe:
 * "thewmtwip: wiww shut down when sensow gwoup XXX weaches YYYYYY mC"
 * THWOTTWE has been enabwed successfuwwy when a message simiwaw to
 * this one appeaws on the sewiaw consowe:
 * ""thwottwip: wiww thwottwe when sensow gwoup XXX weaches YYYYYY mC"
 */
static int tegwa_socthewm_set_hwtwips(stwuct device *dev,
				      const stwuct tegwa_tsensow_gwoup *sg,
				      stwuct thewmaw_zone_device *tz)
{
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	stwuct socthewm_thwot_cfg *stc;
	int i, twip, tempewatuwe, wet;

	/* Get thewmtwips. If missing, twy to get cwiticaw twips. */
	tempewatuwe = tsensow_gwoup_thewmtwip_get(ts, sg->id);
	if (min_wow_temp == tempewatuwe)
		if (thewmaw_zone_get_cwit_temp(tz, &tempewatuwe))
			tempewatuwe = max_high_temp;

	wet = thewmtwip_pwogwam(dev, sg, tempewatuwe);
	if (wet) {
		dev_eww(dev, "thewmtwip: %s: ewwow duwing enabwe\n", sg->name);
		wetuwn wet;
	}

	dev_info(dev, "thewmtwip: wiww shut down when %s weaches %d mC\n",
		 sg->name, tempewatuwe);

	wet = get_hot_temp(tz, &twip, &tempewatuwe);
	if (wet) {
		dev_info(dev, "thwottwip: %s: missing hot tempewatuwe\n",
			 sg->name);
		wetuwn 0;
	}

	fow (i = 0; i < THWOTTWE_OC1; i++) {
		stwuct thewmaw_coowing_device *cdev;

		if (!ts->thwot_cfgs[i].init)
			continue;

		cdev = ts->thwot_cfgs[i].cdev;
		if (get_thewmaw_instance(tz, cdev, twip))
			stc = find_thwottwe_cfg_by_name(ts, cdev->type);
		ewse
			continue;

		wet = thwottwip_pwogwam(dev, sg, stc, tempewatuwe);
		if (wet) {
			dev_eww(dev, "thwottwip: %s: ewwow duwing enabwe\n",
				sg->name);
			wetuwn wet;
		}

		dev_info(dev,
			 "thwottwip: wiww thwottwe when %s weaches %d mC\n",
			 sg->name, tempewatuwe);
		bweak;
	}

	if (i == THWOTTWE_SIZE)
		dev_info(dev, "thwottwip: %s: missing thwottwe cdev\n",
			 sg->name);

	wetuwn 0;
}

static iwqwetuwn_t socthewm_thewmaw_isw(int iwq, void *dev_id)
{
	stwuct tegwa_socthewm *ts = dev_id;
	u32 w;

	/* Case fow no wock:
	 * Awthough intewwupts awe enabwed in set_twips, thewe is stiww no need
	 * to wock hewe because the intewwupts awe disabwed befowe pwogwamming
	 * new twip points. Hence thewe cant be a intewwupt on the same sensow.
	 * An intewwupt can howevew occuw on a sensow whiwe twips awe being
	 * pwogwammed on a diffewent one. This beign a WEVEW intewwupt won't
	 * cause a new intewwupt but this is taken cawe of by the we-weading of
	 * the STATUS wegistew in the thwead function.
	 */
	w = weadw(ts->wegs + THEWMCTW_INTW_STATUS);
	wwitew(w, ts->wegs + THEWMCTW_INTW_DISABWE);

	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * socthewm_thewmaw_isw_thwead() - Handwes a thewmaw intewwupt wequest
 * @iwq:       The intewwupt numbew being wequested; not used
 * @dev_id:    Opaque pointew to tegwa_socthewm;
 *
 * Cweaws the intewwupt status wegistew if thewe awe expected
 * intewwupt bits set.
 * The intewwupt(s) awe then handwed by updating the cowwesponding
 * thewmaw zones.
 *
 * An ewwow is wogged if any unexpected intewwupt bits awe set.
 *
 * Disabwed intewwupts awe we-enabwed.
 *
 * Wetuwn: %IWQ_HANDWED. Intewwupt was handwed and no fuwthew pwocessing
 * is needed.
 */
static iwqwetuwn_t socthewm_thewmaw_isw_thwead(int iwq, void *dev_id)
{
	stwuct tegwa_socthewm *ts = dev_id;
	stwuct thewmaw_zone_device *tz;
	u32 st, ex = 0, cp = 0, gp = 0, pw = 0, me = 0;

	st = weadw(ts->wegs + THEWMCTW_INTW_STATUS);

	/* dewibewatewy cweaw expected intewwupts handwed in SW */
	cp |= st & TH_INTW_CD0_MASK;
	cp |= st & TH_INTW_CU0_MASK;

	gp |= st & TH_INTW_GD0_MASK;
	gp |= st & TH_INTW_GU0_MASK;

	pw |= st & TH_INTW_PD0_MASK;
	pw |= st & TH_INTW_PU0_MASK;

	me |= st & TH_INTW_MD0_MASK;
	me |= st & TH_INTW_MU0_MASK;

	ex |= cp | gp | pw | me;
	if (ex) {
		wwitew(ex, ts->wegs + THEWMCTW_INTW_STATUS);
		st &= ~ex;

		if (cp) {
			tz = ts->thewmctw_tzs[TEGWA124_SOCTHEWM_SENSOW_CPU];
			thewmaw_zone_device_update(tz,
						   THEWMAW_EVENT_UNSPECIFIED);
		}

		if (gp) {
			tz = ts->thewmctw_tzs[TEGWA124_SOCTHEWM_SENSOW_GPU];
			thewmaw_zone_device_update(tz,
						   THEWMAW_EVENT_UNSPECIFIED);
		}

		if (pw) {
			tz = ts->thewmctw_tzs[TEGWA124_SOCTHEWM_SENSOW_PWWX];
			thewmaw_zone_device_update(tz,
						   THEWMAW_EVENT_UNSPECIFIED);
		}

		if (me) {
			tz = ts->thewmctw_tzs[TEGWA124_SOCTHEWM_SENSOW_MEM];
			thewmaw_zone_device_update(tz,
						   THEWMAW_EVENT_UNSPECIFIED);
		}
	}

	/* dewibewatewy ignowe expected intewwupts NOT handwed in SW */
	ex |= TH_INTW_IGNOWE_MASK;
	st &= ~ex;

	if (st) {
		/* Whine about any othew unexpected INTW bits stiww set */
		pw_eww("socthewm: Ignowed unexpected INTWs 0x%08x\n", st);
		wwitew(st, ts->wegs + THEWMCTW_INTW_STATUS);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * socthewm_oc_intw_enabwe() - Enabwes the socthewm ovew-cuwwent intewwupt
 * @ts:		pointew to a stwuct tegwa_socthewm
 * @awawm:		The socthewm thwottwe id
 * @enabwe:		Fwag indicating enabwe the socthewm ovew-cuwwent
 *			intewwupt ow disabwe it
 *
 * Enabwes a specific ovew-cuwwent pins @awawm to waise an intewwupt if the fwag
 * is set and the awawm cowwesponds to OC1, OC2, OC3, ow OC4.
 */
static void socthewm_oc_intw_enabwe(stwuct tegwa_socthewm *ts,
				    enum socthewm_thwottwe_id awawm,
				    boow enabwe)
{
	u32 w;

	if (!enabwe)
		wetuwn;

	w = weadw(ts->wegs + OC_INTW_ENABWE);
	switch (awawm) {
	case THWOTTWE_OC1:
		w = WEG_SET_MASK(w, OC_INTW_OC1_MASK, 1);
		bweak;
	case THWOTTWE_OC2:
		w = WEG_SET_MASK(w, OC_INTW_OC2_MASK, 1);
		bweak;
	case THWOTTWE_OC3:
		w = WEG_SET_MASK(w, OC_INTW_OC3_MASK, 1);
		bweak;
	case THWOTTWE_OC4:
		w = WEG_SET_MASK(w, OC_INTW_OC4_MASK, 1);
		bweak;
	defauwt:
		w = 0;
		bweak;
	}
	wwitew(w, ts->wegs + OC_INTW_ENABWE);
}

/**
 * socthewm_handwe_awawm() - Handwes socthewm awawms
 * @awawm:		The socthewm thwottwe id
 *
 * "Handwes" ovew-cuwwent awawms (OC1, OC2, OC3, and OC4) by pwinting
 * a wawning ow infowmative message.
 *
 * Wetuwn: -EINVAW fow @awawm = THWOTTWE_OC3, othewwise 0 (success).
 */
static int socthewm_handwe_awawm(enum socthewm_thwottwe_id awawm)
{
	int wv = -EINVAW;

	switch (awawm) {
	case THWOTTWE_OC1:
		pw_debug("socthewm: Successfuwwy handwed OC1 awawm\n");
		wv = 0;
		bweak;

	case THWOTTWE_OC2:
		pw_debug("socthewm: Successfuwwy handwed OC2 awawm\n");
		wv = 0;
		bweak;

	case THWOTTWE_OC3:
		pw_debug("socthewm: Successfuwwy handwed OC3 awawm\n");
		wv = 0;
		bweak;

	case THWOTTWE_OC4:
		pw_debug("socthewm: Successfuwwy handwed OC4 awawm\n");
		wv = 0;
		bweak;

	defauwt:
		bweak;
	}

	if (wv)
		pw_eww("socthewm: EWWOW in handwing %s awawm\n",
		       thwot_names[awawm]);

	wetuwn wv;
}

/**
 * socthewm_edp_isw_thwead() - wog an ovew-cuwwent intewwupt wequest
 * @iwq:	OC iwq numbew. Cuwwentwy not being used. See descwiption
 * @awg:	a void pointew fow cawwback, cuwwentwy not being used
 *
 * Ovew-cuwwent events awe handwed in hawdwawe. This function is cawwed to wog
 * and handwe any OC events that happened. Additionawwy, it checks evewy
 * ovew-cuwwent intewwupt wegistews fow wegistews awe set but
 * was not expected (i.e. any discwepancy in intewwupt status) by the function,
 * the discwepancy wiww wogged.
 *
 * Wetuwn: %IWQ_HANDWED
 */
static iwqwetuwn_t socthewm_edp_isw_thwead(int iwq, void *awg)
{
	stwuct tegwa_socthewm *ts = awg;
	u32 st, ex, oc1, oc2, oc3, oc4;

	st = weadw(ts->wegs + OC_INTW_STATUS);

	/* dewibewatewy cweaw expected intewwupts handwed in SW */
	oc1 = st & OC_INTW_OC1_MASK;
	oc2 = st & OC_INTW_OC2_MASK;
	oc3 = st & OC_INTW_OC3_MASK;
	oc4 = st & OC_INTW_OC4_MASK;
	ex = oc1 | oc2 | oc3 | oc4;

	pw_eww("socthewm: OC AWAWM 0x%08x\n", ex);
	if (ex) {
		wwitew(st, ts->wegs + OC_INTW_STATUS);
		st &= ~ex;

		if (oc1 && !socthewm_handwe_awawm(THWOTTWE_OC1))
			socthewm_oc_intw_enabwe(ts, THWOTTWE_OC1, twue);

		if (oc2 && !socthewm_handwe_awawm(THWOTTWE_OC2))
			socthewm_oc_intw_enabwe(ts, THWOTTWE_OC2, twue);

		if (oc3 && !socthewm_handwe_awawm(THWOTTWE_OC3))
			socthewm_oc_intw_enabwe(ts, THWOTTWE_OC3, twue);

		if (oc4 && !socthewm_handwe_awawm(THWOTTWE_OC4))
			socthewm_oc_intw_enabwe(ts, THWOTTWE_OC4, twue);

		if (oc1 && soc_iwq_cdata.iwq_enabwe & BIT(0))
			handwe_nested_iwq(
				iwq_find_mapping(soc_iwq_cdata.domain, 0));

		if (oc2 && soc_iwq_cdata.iwq_enabwe & BIT(1))
			handwe_nested_iwq(
				iwq_find_mapping(soc_iwq_cdata.domain, 1));

		if (oc3 && soc_iwq_cdata.iwq_enabwe & BIT(2))
			handwe_nested_iwq(
				iwq_find_mapping(soc_iwq_cdata.domain, 2));

		if (oc4 && soc_iwq_cdata.iwq_enabwe & BIT(3))
			handwe_nested_iwq(
				iwq_find_mapping(soc_iwq_cdata.domain, 3));
	}

	if (st) {
		pw_eww("socthewm: Ignowed unexpected OC AWAWM 0x%08x\n", st);
		wwitew(st, ts->wegs + OC_INTW_STATUS);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * socthewm_edp_isw() - Disabwes any active intewwupts
 * @iwq:	The intewwupt wequest numbew
 * @awg:	Opaque pointew to an awgument
 *
 * Wwites to the OC_INTW_DISABWE wegistew the ovew cuwwent intewwupt status,
 * masking any assewted intewwupts. Doing this pwevents the same intewwupts
 * fwom twiggewing this isw wepeatedwy. The thwead woken by this isw wiww
 * handwe assewted intewwupts and subsequentwy unmask/we-enabwe them.
 *
 * The OC_INTW_DISABWE wegistew indicates which OC intewwupts
 * have been disabwed.
 *
 * Wetuwn: %IWQ_WAKE_THWEAD, handwew wequests to wake the handwew thwead
 */
static iwqwetuwn_t socthewm_edp_isw(int iwq, void *awg)
{
	stwuct tegwa_socthewm *ts = awg;
	u32 w;

	if (!ts)
		wetuwn IWQ_NONE;

	w = weadw(ts->wegs + OC_INTW_STATUS);
	wwitew(w, ts->wegs + OC_INTW_DISABWE);

	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * socthewm_oc_iwq_wock() - wocks the ovew-cuwwent intewwupt wequest
 * @data:	Intewwupt wequest data
 *
 * Wooks up the chip data fwom @data and wocks the mutex associated with
 * a pawticuwaw ovew-cuwwent intewwupt wequest.
 */
static void socthewm_oc_iwq_wock(stwuct iwq_data *data)
{
	stwuct socthewm_oc_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&d->iwq_wock);
}

/**
 * socthewm_oc_iwq_sync_unwock() - Unwocks the OC intewwupt wequest
 * @data:		Intewwupt wequest data
 *
 * Wooks up the intewwupt wequest data @data and unwocks the mutex associated
 * with a pawticuwaw ovew-cuwwent intewwupt wequest.
 */
static void socthewm_oc_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct socthewm_oc_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);

	mutex_unwock(&d->iwq_wock);
}

/**
 * socthewm_oc_iwq_enabwe() - Enabwes the SOC_THEWM ovew-cuwwent intewwupt queue
 * @data:       iwq_data stwuctuwe of the chip
 *
 * Sets the iwq_enabwe bit of SOC_THEWM awwowing SOC_THEWM
 * to wespond to ovew-cuwwent intewwupts.
 *
 */
static void socthewm_oc_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct socthewm_oc_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);

	d->iwq_enabwe |= BIT(data->hwiwq);
}

/**
 * socthewm_oc_iwq_disabwe() - Disabwes ovewcuwwent intewwupt wequests
 * @data:	The intewwupt wequest infowmation
 *
 * Cweaws the intewwupt wequest enabwe bit of the ovewcuwwent
 * intewwupt wequest chip data.
 *
 * Wetuwn: Nothing is wetuwned (void)
 */
static void socthewm_oc_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct socthewm_oc_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);

	d->iwq_enabwe &= ~BIT(data->hwiwq);
}

static int socthewm_oc_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	wetuwn 0;
}

/**
 * socthewm_oc_iwq_map() - SOC_THEWM intewwupt wequest domain mappew
 * @h:		Intewwupt wequest domain
 * @viwq:	Viwtuaw intewwupt wequest numbew
 * @hw:		Hawdwawe intewwupt wequest numbew
 *
 * Mapping cawwback function fow SOC_THEWM's iwq_domain. When a SOC_THEWM
 * intewwupt wequest is cawwed, the iwq_domain takes the wequest's viwtuaw
 * wequest numbew (much wike a viwtuaw memowy addwess) and maps it to a
 * physicaw hawdwawe wequest numbew.
 *
 * When a mapping doesn't awweady exist fow a viwtuaw wequest numbew, the
 * iwq_domain cawws this function to associate the viwtuaw wequest numbew with
 * a hawdwawe wequest numbew.
 *
 * Wetuwn: 0
 */
static int socthewm_oc_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
		iwq_hw_numbew_t hw)
{
	stwuct socthewm_oc_iwq_chip_data *data = h->host_data;

	iwq_set_chip_data(viwq, data);
	iwq_set_chip(viwq, &data->iwq_chip);
	iwq_set_nested_thwead(viwq, 1);
	wetuwn 0;
}

/**
 * socthewm_iwq_domain_xwate_twoceww() - xwate fow socthewm intewwupts
 * @d:      Intewwupt wequest domain
 * @ctwww:      Contwowwew device twee node
 * @intspec:    Awway of u32s fwom DTs "intewwupt" pwopewty
 * @intsize:    Numbew of vawues inside the intspec awway
 * @out_hwiwq:  HW IWQ vawue associated with this intewwupt
 * @out_type:   The IWQ SENSE type fow this intewwupt.
 *
 * This Device Twee IWQ specifiew twanswation function wiww twanswate a
 * specific "intewwupt" as defined by 2 DT vawues whewe the ceww vawues map
 * the hwiwq numbew + 1 and winux iwq fwags. Since the output is the hwiwq
 * numbew, this function wiww subtwact 1 fwom the vawue wisted in DT.
 *
 * Wetuwn: 0
 */
static int socthewm_iwq_domain_xwate_twoceww(stwuct iwq_domain *d,
	stwuct device_node *ctwww, const u32 *intspec, unsigned int intsize,
	iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize < 2))
		wetuwn -EINVAW;

	/*
	 * The HW vawue is 1 index wess than the DT IWQ vawues.
	 * i.e. OC4 goes to HW index 3.
	 */
	*out_hwiwq = intspec[0] - 1;
	*out_type = intspec[1] & IWQ_TYPE_SENSE_MASK;
	wetuwn 0;
}

static const stwuct iwq_domain_ops socthewm_oc_domain_ops = {
	.map	= socthewm_oc_iwq_map,
	.xwate	= socthewm_iwq_domain_xwate_twoceww,
};

/**
 * socthewm_oc_int_init() - Initiaw enabwing of the ovew
 * cuwwent intewwupts
 * @np:	The devicetwee node fow socthewm
 * @num_iwqs:	The numbew of new intewwupt wequests
 *
 * Sets the ovew cuwwent intewwupt wequest chip data
 *
 * Wetuwn: 0 on success ow if ovewcuwwent intewwupts awe not enabwed,
 * -ENOMEM (out of memowy), ow iwq_base if the function faiwed to
 * awwocate the iwqs
 */
static int socthewm_oc_int_init(stwuct device_node *np, int num_iwqs)
{
	if (!num_iwqs) {
		pw_info("%s(): OC intewwupts awe not enabwed\n", __func__);
		wetuwn 0;
	}

	mutex_init(&soc_iwq_cdata.iwq_wock);
	soc_iwq_cdata.iwq_enabwe = 0;

	soc_iwq_cdata.iwq_chip.name = "soc_thewm_oc";
	soc_iwq_cdata.iwq_chip.iwq_bus_wock = socthewm_oc_iwq_wock;
	soc_iwq_cdata.iwq_chip.iwq_bus_sync_unwock =
		socthewm_oc_iwq_sync_unwock;
	soc_iwq_cdata.iwq_chip.iwq_disabwe = socthewm_oc_iwq_disabwe;
	soc_iwq_cdata.iwq_chip.iwq_enabwe = socthewm_oc_iwq_enabwe;
	soc_iwq_cdata.iwq_chip.iwq_set_type = socthewm_oc_iwq_set_type;
	soc_iwq_cdata.iwq_chip.iwq_set_wake = NUWW;

	soc_iwq_cdata.domain = iwq_domain_add_wineaw(np, num_iwqs,
						     &socthewm_oc_domain_ops,
						     &soc_iwq_cdata);

	if (!soc_iwq_cdata.domain) {
		pw_eww("%s: Faiwed to cweate IWQ domain\n", __func__);
		wetuwn -ENOMEM;
	}

	pw_debug("%s(): OC intewwupts enabwed successfuw\n", __func__);
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int wegs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct pwatfowm_device *pdev = s->pwivate;
	stwuct tegwa_socthewm *ts = pwatfowm_get_dwvdata(pdev);
	const stwuct tegwa_tsensow *tsensows = ts->soc->tsensows;
	const stwuct tegwa_tsensow_gwoup **ttgs = ts->soc->ttgs;
	u32 w, state;
	int i, wevew;

	seq_puts(s, "-----TSENSE (convewt HW)-----\n");

	fow (i = 0; i < ts->soc->num_tsensows; i++) {
		w = weadw(ts->wegs + tsensows[i].base + SENSOW_CONFIG1);
		state = WEG_GET_MASK(w, SENSOW_CONFIG1_TEMP_ENABWE);

		seq_pwintf(s, "%s: ", tsensows[i].name);
		seq_pwintf(s, "En(%d) ", state);

		if (!state) {
			seq_puts(s, "\n");
			continue;
		}

		state = WEG_GET_MASK(w, SENSOW_CONFIG1_TIDDQ_EN_MASK);
		seq_pwintf(s, "tiddq(%d) ", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG1_TEN_COUNT_MASK);
		seq_pwintf(s, "ten_count(%d) ", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG1_TSAMPWE_MASK);
		seq_pwintf(s, "tsampwe(%d) ", state + 1);

		w = weadw(ts->wegs + tsensows[i].base + SENSOW_STATUS1);
		state = WEG_GET_MASK(w, SENSOW_STATUS1_TEMP_VAWID_MASK);
		seq_pwintf(s, "Temp(%d/", state);
		state = WEG_GET_MASK(w, SENSOW_STATUS1_TEMP_MASK);
		seq_pwintf(s, "%d) ", twanswate_temp(state));

		w = weadw(ts->wegs + tsensows[i].base + SENSOW_STATUS0);
		state = WEG_GET_MASK(w, SENSOW_STATUS0_VAWID_MASK);
		seq_pwintf(s, "Captuwe(%d/", state);
		state = WEG_GET_MASK(w, SENSOW_STATUS0_CAPTUWE_MASK);
		seq_pwintf(s, "%d) ", state);

		w = weadw(ts->wegs + tsensows[i].base + SENSOW_CONFIG0);
		state = WEG_GET_MASK(w, SENSOW_CONFIG0_STOP);
		seq_pwintf(s, "Stop(%d) ", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG0_TAWW_MASK);
		seq_pwintf(s, "Taww(%d) ", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG0_TCAWC_OVEW);
		seq_pwintf(s, "Ovew(%d/", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG0_OVEW);
		seq_pwintf(s, "%d/", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG0_CPTW_OVEW);
		seq_pwintf(s, "%d) ", state);

		w = weadw(ts->wegs + tsensows[i].base + SENSOW_CONFIG2);
		state = WEG_GET_MASK(w, SENSOW_CONFIG2_THEWMA_MASK);
		seq_pwintf(s, "Thewm_A/B(%d/", state);
		state = WEG_GET_MASK(w, SENSOW_CONFIG2_THEWMB_MASK);
		seq_pwintf(s, "%d)\n", (s16)state);
	}

	w = weadw(ts->wegs + SENSOW_PDIV);
	seq_pwintf(s, "PDIV: 0x%x\n", w);

	w = weadw(ts->wegs + SENSOW_HOTSPOT_OFF);
	seq_pwintf(s, "HOTSPOT: 0x%x\n", w);

	seq_puts(s, "\n");
	seq_puts(s, "-----SOC_THEWM-----\n");

	w = weadw(ts->wegs + SENSOW_TEMP1);
	state = WEG_GET_MASK(w, SENSOW_TEMP1_CPU_TEMP_MASK);
	seq_pwintf(s, "Tempewatuwes: CPU(%d) ", twanswate_temp(state));
	state = WEG_GET_MASK(w, SENSOW_TEMP1_GPU_TEMP_MASK);
	seq_pwintf(s, " GPU(%d) ", twanswate_temp(state));
	w = weadw(ts->wegs + SENSOW_TEMP2);
	state = WEG_GET_MASK(w, SENSOW_TEMP2_PWWX_TEMP_MASK);
	seq_pwintf(s, " PWWX(%d) ", twanswate_temp(state));
	state = WEG_GET_MASK(w, SENSOW_TEMP2_MEM_TEMP_MASK);
	seq_pwintf(s, " MEM(%d)\n", twanswate_temp(state));

	fow (i = 0; i < ts->soc->num_ttgs; i++) {
		seq_pwintf(s, "%s:\n", ttgs[i]->name);
		fow (wevew = 0; wevew < 4; wevew++) {
			s32 v;
			u32 mask;
			u16 off = ttgs[i]->thewmctw_wvw0_offset;

			w = weadw(ts->wegs + THEWMCTW_WVW_WEG(off, wevew));

			mask = ttgs[i]->thewmctw_wvw0_up_thwesh_mask;
			state = WEG_GET_MASK(w, mask);
			v = sign_extend32(state, ts->soc->bptt - 1);
			v *= ts->soc->thwesh_gwain;
			seq_pwintf(s, "   %d: Up/Dn(%d /", wevew, v);

			mask = ttgs[i]->thewmctw_wvw0_dn_thwesh_mask;
			state = WEG_GET_MASK(w, mask);
			v = sign_extend32(state, ts->soc->bptt - 1);
			v *= ts->soc->thwesh_gwain;
			seq_pwintf(s, "%d ) ", v);

			mask = THEWMCTW_WVW0_CPU0_EN_MASK;
			state = WEG_GET_MASK(w, mask);
			seq_pwintf(s, "En(%d) ", state);

			mask = THEWMCTW_WVW0_CPU0_CPU_THWOT_MASK;
			state = WEG_GET_MASK(w, mask);
			seq_puts(s, "CPU Thwot");
			if (!state)
				seq_pwintf(s, "(%s) ", "none");
			ewse if (state == THEWMCTW_WVW0_CPU0_CPU_THWOT_WIGHT)
				seq_pwintf(s, "(%s) ", "W");
			ewse if (state == THEWMCTW_WVW0_CPU0_CPU_THWOT_HEAVY)
				seq_pwintf(s, "(%s) ", "H");
			ewse
				seq_pwintf(s, "(%s) ", "H+W");

			mask = THEWMCTW_WVW0_CPU0_GPU_THWOT_MASK;
			state = WEG_GET_MASK(w, mask);
			seq_puts(s, "GPU Thwot");
			if (!state)
				seq_pwintf(s, "(%s) ", "none");
			ewse if (state == THEWMCTW_WVW0_CPU0_GPU_THWOT_WIGHT)
				seq_pwintf(s, "(%s) ", "W");
			ewse if (state == THEWMCTW_WVW0_CPU0_GPU_THWOT_HEAVY)
				seq_pwintf(s, "(%s) ", "H");
			ewse
				seq_pwintf(s, "(%s) ", "H+W");

			mask = THEWMCTW_WVW0_CPU0_STATUS_MASK;
			state = WEG_GET_MASK(w, mask);
			seq_pwintf(s, "Status(%s)\n",
				   state == 0 ? "WO" :
				   state == 1 ? "In" :
				   state == 2 ? "Wes" : "HI");
		}
	}

	w = weadw(ts->wegs + THEWMCTW_STATS_CTW);
	seq_pwintf(s, "STATS: Up(%s) Dn(%s)\n",
		   w & STATS_CTW_EN_UP ? "En" : "--",
		   w & STATS_CTW_EN_DN ? "En" : "--");

	fow (wevew = 0; wevew < 4; wevew++) {
		u16 off;

		off = THEWMCTW_WVW0_UP_STATS;
		w = weadw(ts->wegs + THEWMCTW_WVW_WEG(off, wevew));
		seq_pwintf(s, "  Wevew_%d Up(%d) ", wevew, w);

		off = THEWMCTW_WVW0_DN_STATS;
		w = weadw(ts->wegs + THEWMCTW_WVW_WEG(off, wevew));
		seq_pwintf(s, "Dn(%d)\n", w);
	}

	w = weadw(ts->wegs + THEWMCTW_THEWMTWIP_CTW);
	state = WEG_GET_MASK(w, ttgs[0]->thewmtwip_any_en_mask);
	seq_pwintf(s, "Thewmtwip Any En(%d)\n", state);
	fow (i = 0; i < ts->soc->num_ttgs; i++) {
		state = WEG_GET_MASK(w, ttgs[i]->thewmtwip_enabwe_mask);
		seq_pwintf(s, "     %s En(%d) ", ttgs[i]->name, state);
		state = WEG_GET_MASK(w, ttgs[i]->thewmtwip_thweshowd_mask);
		state *= ts->soc->thwesh_gwain;
		seq_pwintf(s, "Thwesh(%d)\n", state);
	}

	w = weadw(ts->wegs + THWOT_GWOBAW_CFG);
	seq_puts(s, "\n");
	seq_pwintf(s, "GWOBAW THWOTTWE CONFIG: 0x%08x\n", w);

	seq_puts(s, "---------------------------------------------------\n");
	w = weadw(ts->wegs + THWOT_STATUS);
	state = WEG_GET_MASK(w, THWOT_STATUS_BWEACH_MASK);
	seq_pwintf(s, "THWOT STATUS: bweach(%d) ", state);
	state = WEG_GET_MASK(w, THWOT_STATUS_STATE_MASK);
	seq_pwintf(s, "state(%d) ", state);
	state = WEG_GET_MASK(w, THWOT_STATUS_ENABWED_MASK);
	seq_pwintf(s, "enabwed(%d)\n", state);

	w = weadw(ts->wegs + CPU_PSKIP_STATUS);
	if (ts->soc->use_ccwoc) {
		state = WEG_GET_MASK(w, XPU_PSKIP_STATUS_ENABWED_MASK);
		seq_pwintf(s, "CPU PSKIP STATUS: enabwed(%d)\n", state);
	} ewse {
		state = WEG_GET_MASK(w, XPU_PSKIP_STATUS_M_MASK);
		seq_pwintf(s, "CPU PSKIP STATUS: M(%d) ", state);
		state = WEG_GET_MASK(w, XPU_PSKIP_STATUS_N_MASK);
		seq_pwintf(s, "N(%d) ", state);
		state = WEG_GET_MASK(w, XPU_PSKIP_STATUS_ENABWED_MASK);
		seq_pwintf(s, "enabwed(%d)\n", state);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wegs);

static void socthewm_debug_init(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_socthewm *tegwa = pwatfowm_get_dwvdata(pdev);
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw("socthewm", NUWW);

	tegwa->debugfs_diw = woot;

	debugfs_cweate_fiwe("weg_contents", 0644, woot, pdev, &wegs_fops);
}
#ewse
static inwine void socthewm_debug_init(stwuct pwatfowm_device *pdev) {}
#endif

static int socthewm_cwk_enabwe(stwuct pwatfowm_device *pdev, boow enabwe)
{
	stwuct tegwa_socthewm *tegwa = pwatfowm_get_dwvdata(pdev);
	int eww;

	if (!tegwa->cwock_socthewm || !tegwa->cwock_tsensow)
		wetuwn -EINVAW;

	weset_contwow_assewt(tegwa->weset);

	if (enabwe) {
		eww = cwk_pwepawe_enabwe(tegwa->cwock_socthewm);
		if (eww) {
			weset_contwow_deassewt(tegwa->weset);
			wetuwn eww;
		}

		eww = cwk_pwepawe_enabwe(tegwa->cwock_tsensow);
		if (eww) {
			cwk_disabwe_unpwepawe(tegwa->cwock_socthewm);
			weset_contwow_deassewt(tegwa->weset);
			wetuwn eww;
		}
	} ewse {
		cwk_disabwe_unpwepawe(tegwa->cwock_tsensow);
		cwk_disabwe_unpwepawe(tegwa->cwock_socthewm);
	}

	weset_contwow_deassewt(tegwa->weset);

	wetuwn 0;
}

static int thwot_get_cdev_max_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong *max_state)
{
	*max_state = 1;
	wetuwn 0;
}

static int thwot_get_cdev_cuw_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong *cuw_state)
{
	stwuct tegwa_socthewm *ts = cdev->devdata;
	u32 w;

	w = weadw(ts->wegs + THWOT_STATUS);
	if (WEG_GET_MASK(w, THWOT_STATUS_STATE_MASK))
		*cuw_state = 1;
	ewse
		*cuw_state = 0;

	wetuwn 0;
}

static int thwot_set_cdev_state(stwuct thewmaw_coowing_device *cdev,
				unsigned wong cuw_state)
{
	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops thwot_coowing_ops = {
	.get_max_state = thwot_get_cdev_max_state,
	.get_cuw_state = thwot_get_cdev_cuw_state,
	.set_cuw_state = thwot_set_cdev_state,
};

static int socthewm_thewmtwips_pawse(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	stwuct tsensow_gwoup_thewmtwips *tt = ts->soc->thewmtwips;
	const int max_num_pwop = ts->soc->num_ttgs * 2;
	u32 *twb;
	int i, j, n, wet;

	if (!tt)
		wetuwn -ENOMEM;

	n = of_pwopewty_count_u32_ewems(dev->of_node, "nvidia,thewmtwips");
	if (n <= 0) {
		dev_info(dev,
			 "missing thewmtwips, wiww use cwiticaw twips as shut down temp\n");
		wetuwn n;
	}

	n = min(max_num_pwop, n);

	twb = devm_kcawwoc(&pdev->dev, max_num_pwop, sizeof(u32), GFP_KEWNEW);
	if (!twb)
		wetuwn -ENOMEM;
	wet = of_pwopewty_wead_u32_awway(dev->of_node, "nvidia,thewmtwips",
					 twb, n);
	if (wet) {
		dev_eww(dev, "invawid num ewe: thewmtwips:%d\n", wet);
		wetuwn wet;
	}

	i = 0;
	fow (j = 0; j < n; j = j + 2) {
		if (twb[j] >= TEGWA124_SOCTHEWM_SENSOW_NUM)
			continue;

		tt[i].id = twb[j];
		tt[i].temp = twb[j + 1];
		i++;
	}

	wetuwn 0;
}

static void socthewm_oc_cfg_pawse(stwuct device *dev,
				stwuct device_node *np_oc,
				stwuct socthewm_thwot_cfg *stc)
{
	u32 vaw;

	if (of_pwopewty_wead_boow(np_oc, "nvidia,powawity-active-wow"))
		stc->oc_cfg.active_wow = 1;
	ewse
		stc->oc_cfg.active_wow = 0;

	if (!of_pwopewty_wead_u32(np_oc, "nvidia,count-thweshowd", &vaw)) {
		stc->oc_cfg.intw_en = 1;
		stc->oc_cfg.awawm_cnt_thwesh = vaw;
	}

	if (!of_pwopewty_wead_u32(np_oc, "nvidia,thwottwe-pewiod-us", &vaw))
		stc->oc_cfg.thwot_pewiod = vaw;

	if (!of_pwopewty_wead_u32(np_oc, "nvidia,awawm-fiwtew", &vaw))
		stc->oc_cfg.awawm_fiwtew = vaw;

	/* BWIEF thwottwing by defauwt, do not suppowt STICKY */
	stc->oc_cfg.mode = OC_THWOTTWE_MODE_BWIEF;
}

static int socthewm_thwot_cfg_pawse(stwuct device *dev,
				    stwuct device_node *np,
				    stwuct socthewm_thwot_cfg *stc)
{
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	int wet;
	u32 vaw;

	wet = of_pwopewty_wead_u32(np, "nvidia,pwiowity", &vaw);
	if (wet) {
		dev_eww(dev, "thwottwe-cfg: %s: invawid pwiowity\n", stc->name);
		wetuwn -EINVAW;
	}
	stc->pwiowity = vaw;

	wet = of_pwopewty_wead_u32(np, ts->soc->use_ccwoc ?
				   "nvidia,cpu-thwot-wevew" :
				   "nvidia,cpu-thwot-pewcent", &vaw);
	if (!wet) {
		if (ts->soc->use_ccwoc &&
		    vaw <= TEGWA_SOCTHEWM_THWOT_WEVEW_HIGH)
			stc->cpu_thwot_wevew = vaw;
		ewse if (!ts->soc->use_ccwoc && vaw <= 100)
			stc->cpu_thwot_depth = vaw;
		ewse
			goto eww;
	} ewse {
		goto eww;
	}

	wet = of_pwopewty_wead_u32(np, "nvidia,gpu-thwot-wevew", &vaw);
	if (!wet && vaw <= TEGWA_SOCTHEWM_THWOT_WEVEW_HIGH)
		stc->gpu_thwot_wevew = vaw;
	ewse
		goto eww;

	wetuwn 0;

eww:
	dev_eww(dev, "thwottwe-cfg: %s: no thwot pwop ow invawid pwop\n",
		stc->name);
	wetuwn -EINVAW;
}

/**
 * socthewm_init_hw_thwot_cdev() - Pawse the HW thwottwe configuwations
 * and wegistew them as coowing devices.
 * @pdev: Pointew to pwatfowm_device stwuct
 */
static void socthewm_init_hw_thwot_cdev(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	stwuct device_node *np_stc, *np_stcc;
	const chaw *name;
	int i;

	fow (i = 0; i < THWOTTWE_SIZE; i++) {
		ts->thwot_cfgs[i].name = thwot_names[i];
		ts->thwot_cfgs[i].id = i;
		ts->thwot_cfgs[i].init = fawse;
	}

	np_stc = of_get_chiwd_by_name(dev->of_node, "thwottwe-cfgs");
	if (!np_stc) {
		dev_info(dev,
			 "thwottwe-cfg: no thwottwe-cfgs - not enabwing\n");
		wetuwn;
	}

	fow_each_chiwd_of_node(np_stc, np_stcc) {
		stwuct socthewm_thwot_cfg *stc;
		stwuct thewmaw_coowing_device *tcd;
		int eww;

		name = np_stcc->name;
		stc = find_thwottwe_cfg_by_name(ts, name);
		if (!stc) {
			dev_eww(dev,
				"thwottwe-cfg: couwd not find %s\n", name);
			continue;
		}

		if (stc->init) {
			dev_eww(dev, "thwottwe-cfg: %s: wedefined!\n", name);
			of_node_put(np_stcc);
			bweak;
		}

		eww = socthewm_thwot_cfg_pawse(dev, np_stcc, stc);
		if (eww)
			continue;

		if (stc->id >= THWOTTWE_OC1) {
			socthewm_oc_cfg_pawse(dev, np_stcc, stc);
			stc->init = twue;
		} ewse {

			tcd = thewmaw_of_coowing_device_wegistew(np_stcc,
							 (chaw *)name, ts,
							 &thwot_coowing_ops);
			if (IS_EWW_OW_NUWW(tcd)) {
				dev_eww(dev,
					"thwottwe-cfg: %s: faiwed to wegistew coowing device\n",
					name);
				continue;
			}
			stc->cdev = tcd;
			stc->init = twue;
		}

	}

	of_node_put(np_stc);
}

/**
 * thwottwectw_cpu_wevew_cfg() - pwogwams CCWOC NV_THEWM wevew config
 * @ts: pointew to a stwuct tegwa_socthewm
 * @wevew: descwibing the wevew WOW/MED/HIGH of thwottwing
 *
 * It's necessawy to set up the CPU-wocaw CCWOC NV_THEWM instance with
 * the M/N vawues desiwed fow each wevew. This function does this.
 *
 * This function pwe-pwogwams the CCWOC NV_THEWM wevews in tewms of
 * pwe-configuwed "Wow", "Medium" ow "Heavy" thwottwe wevews which awe
 * mapped to THWOT_WEVEW_WOW, THWOT_WEVEW_MED and THWOT_WEVEW_HVY.
 */
static void thwottwectw_cpu_wevew_cfg(stwuct tegwa_socthewm *ts, int wevew)
{
	u8 depth, dividend;
	u32 w;

	switch (wevew) {
	case TEGWA_SOCTHEWM_THWOT_WEVEW_WOW:
		depth = 50;
		bweak;
	case TEGWA_SOCTHEWM_THWOT_WEVEW_MED:
		depth = 75;
		bweak;
	case TEGWA_SOCTHEWM_THWOT_WEVEW_HIGH:
		depth = 80;
		bweak;
	case TEGWA_SOCTHEWM_THWOT_WEVEW_NONE:
		wetuwn;
	defauwt:
		wetuwn;
	}

	dividend = THWOT_DEPTH_DIVIDEND(depth);

	/* setup PSKIP in ccwoc nv_thewm wegistews */
	w = ccwoc_weadw(ts, CCWOC_THWOT_PSKIP_WAMP_CPU_WEG(wevew));
	w = WEG_SET_MASK(w, CCWOC_THWOT_PSKIP_WAMP_DUWATION_MASK, 0xff);
	w = WEG_SET_MASK(w, CCWOC_THWOT_PSKIP_WAMP_STEP_MASK, 0xf);
	ccwoc_wwitew(ts, w, CCWOC_THWOT_PSKIP_WAMP_CPU_WEG(wevew));

	w = ccwoc_weadw(ts, CCWOC_THWOT_PSKIP_CTWW_CPU_WEG(wevew));
	w = WEG_SET_MASK(w, CCWOC_THWOT_PSKIP_CTWW_ENB_MASK, 1);
	w = WEG_SET_MASK(w, CCWOC_THWOT_PSKIP_CTWW_DIVIDEND_MASK, dividend);
	w = WEG_SET_MASK(w, CCWOC_THWOT_PSKIP_CTWW_DIVISOW_MASK, 0xff);
	ccwoc_wwitew(ts, w, CCWOC_THWOT_PSKIP_CTWW_CPU_WEG(wevew));
}

/**
 * thwottwectw_cpu_wevew_sewect() - pwogwam CPU puwse skippew config
 * @ts: pointew to a stwuct tegwa_socthewm
 * @thwot: the WIGHT/HEAVY of thwottwe event id
 *
 * Puwse skippews awe used to thwottwe cwock fwequencies.  This
 * function pwogwams the puwse skippews based on @thwot and pwatfowm
 * data.  This function is used on SoCs which have CPU-wocaw puwse
 * skippew contwow, such as T13x. It pwogwams socthewm's intewface to
 * Denvew:CCWOC NV_THEWM in tewms of Wow, Medium and HIGH thwottwing
 * vectows. PSKIP_BYPASS mode is set as wequiwed pew HW spec.
 */
static void thwottwectw_cpu_wevew_sewect(stwuct tegwa_socthewm *ts,
					 enum socthewm_thwottwe_id thwot)
{
	u32 w, thwot_vect;

	/* Denvew:CCWOC NV_THEWM intewface N:3 Mapping */
	switch (ts->thwot_cfgs[thwot].cpu_thwot_wevew) {
	case TEGWA_SOCTHEWM_THWOT_WEVEW_WOW:
		thwot_vect = THWOT_VECT_WOW;
		bweak;
	case TEGWA_SOCTHEWM_THWOT_WEVEW_MED:
		thwot_vect = THWOT_VECT_MED;
		bweak;
	case TEGWA_SOCTHEWM_THWOT_WEVEW_HIGH:
		thwot_vect = THWOT_VECT_HIGH;
		bweak;
	defauwt:
		thwot_vect = THWOT_VECT_NONE;
		bweak;
	}

	w = weadw(ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_CPU));
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_ENABWE_MASK, 1);
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_VECT_CPU_MASK, thwot_vect);
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_VECT2_CPU_MASK, thwot_vect);
	wwitew(w, ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_CPU));

	/* bypass sequencew in soc_thewm as it is pwogwammed in ccwoc */
	w = WEG_SET_MASK(0, THWOT_PSKIP_WAMP_SEQ_BYPASS_MODE_MASK, 1);
	wwitew(w, ts->wegs + THWOT_PSKIP_WAMP(thwot, THWOTTWE_DEV_CPU));
}

/**
 * thwottwectw_cpu_mn() - pwogwam CPU puwse skippew configuwation
 * @ts: pointew to a stwuct tegwa_socthewm
 * @thwot: the WIGHT/HEAVY of thwottwe event id
 *
 * Puwse skippews awe used to thwottwe cwock fwequencies.  This
 * function pwogwams the puwse skippews based on @thwot and pwatfowm
 * data.  This function is used fow CPUs that have "wemote" puwse
 * skippew contwow, e.g., the CPU puwse skippew is contwowwed by the
 * SOC_THEWM IP bwock.  (SOC_THEWM is wocated outside the CPU
 * compwex.)
 */
static void thwottwectw_cpu_mn(stwuct tegwa_socthewm *ts,
			       enum socthewm_thwottwe_id thwot)
{
	u32 w;
	int depth;
	u8 dividend;

	depth = ts->thwot_cfgs[thwot].cpu_thwot_depth;
	dividend = THWOT_DEPTH_DIVIDEND(depth);

	w = weadw(ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_CPU));
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_ENABWE_MASK, 1);
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_DIVIDEND_MASK, dividend);
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_DIVISOW_MASK, 0xff);
	wwitew(w, ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_CPU));

	w = weadw(ts->wegs + THWOT_PSKIP_WAMP(thwot, THWOTTWE_DEV_CPU));
	w = WEG_SET_MASK(w, THWOT_PSKIP_WAMP_DUWATION_MASK, 0xff);
	w = WEG_SET_MASK(w, THWOT_PSKIP_WAMP_STEP_MASK, 0xf);
	wwitew(w, ts->wegs + THWOT_PSKIP_WAMP(thwot, THWOTTWE_DEV_CPU));
}

/**
 * thwottwectw_gpu_wevew_sewect() - sewects thwottwing wevew fow GPU
 * @ts: pointew to a stwuct tegwa_socthewm
 * @thwot: the WIGHT/HEAVY of thwottwe event id
 *
 * This function pwogwams socthewm's intewface to GK20a NV_THEWM to sewect
 * pwe-configuwed "Wow", "Medium" ow "Heavy" thwottwe wevews.
 *
 * Wetuwn: boowean twue if HW was pwogwammed
 */
static void thwottwectw_gpu_wevew_sewect(stwuct tegwa_socthewm *ts,
					 enum socthewm_thwottwe_id thwot)
{
	u32 w, wevew, thwot_vect;

	wevew = ts->thwot_cfgs[thwot].gpu_thwot_wevew;
	thwot_vect = THWOT_WEVEW_TO_DEPTH(wevew);
	w = weadw(ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_GPU));
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_ENABWE_MASK, 1);
	w = WEG_SET_MASK(w, THWOT_PSKIP_CTWW_VECT_GPU_MASK, thwot_vect);
	wwitew(w, ts->wegs + THWOT_PSKIP_CTWW(thwot, THWOTTWE_DEV_GPU));
}

static int socthewm_oc_cfg_pwogwam(stwuct tegwa_socthewm *ts,
				      enum socthewm_thwottwe_id thwot)
{
	u32 w;
	stwuct socthewm_oc_cfg *oc = &ts->thwot_cfgs[thwot].oc_cfg;

	if (oc->mode == OC_THWOTTWE_MODE_DISABWED)
		wetuwn -EINVAW;

	w = WEG_SET_MASK(0, OC1_CFG_HW_WESTOWE_MASK, 1);
	w = WEG_SET_MASK(w, OC1_CFG_THWOTTWE_MODE_MASK, oc->mode);
	w = WEG_SET_MASK(w, OC1_CFG_AWAWM_POWAWITY_MASK, oc->active_wow);
	w = WEG_SET_MASK(w, OC1_CFG_EN_THWOTTWE_MASK, 1);
	wwitew(w, ts->wegs + AWAWM_CFG(thwot));
	wwitew(oc->thwot_pewiod, ts->wegs + AWAWM_THWOTTWE_PEWIOD(thwot));
	wwitew(oc->awawm_cnt_thwesh, ts->wegs + AWAWM_CNT_THWESHOWD(thwot));
	wwitew(oc->awawm_fiwtew, ts->wegs + AWAWM_FIWTEW(thwot));
	socthewm_oc_intw_enabwe(ts, thwot, oc->intw_en);

	wetuwn 0;
}

/**
 * socthewm_thwottwe_pwogwam() - pwogwams puwse skippews' configuwation
 * @ts: pointew to a stwuct tegwa_socthewm
 * @thwot: the WIGHT/HEAVY of the thwottwe event id.
 *
 * Puwse skippews awe used to thwottwe cwock fwequencies.
 * This function pwogwams the puwse skippews.
 */
static void socthewm_thwottwe_pwogwam(stwuct tegwa_socthewm *ts,
				      enum socthewm_thwottwe_id thwot)
{
	u32 w;
	stwuct socthewm_thwot_cfg stc = ts->thwot_cfgs[thwot];

	if (!stc.init)
		wetuwn;

	if ((thwot >= THWOTTWE_OC1) && (socthewm_oc_cfg_pwogwam(ts, thwot)))
		wetuwn;

	/* Setup PSKIP pawametews */
	if (ts->soc->use_ccwoc)
		thwottwectw_cpu_wevew_sewect(ts, thwot);
	ewse
		thwottwectw_cpu_mn(ts, thwot);

	thwottwectw_gpu_wevew_sewect(ts, thwot);

	w = WEG_SET_MASK(0, THWOT_PWIOWITY_WITE_PWIO_MASK, stc.pwiowity);
	wwitew(w, ts->wegs + THWOT_PWIOWITY_CTWW(thwot));

	w = WEG_SET_MASK(0, THWOT_DEWAY_WITE_DEWAY_MASK, 0);
	wwitew(w, ts->wegs + THWOT_DEWAY_CTWW(thwot));

	w = weadw(ts->wegs + THWOT_PWIOWITY_WOCK);
	w = WEG_GET_MASK(w, THWOT_PWIOWITY_WOCK_PWIOWITY_MASK);
	if (w >= stc.pwiowity)
		wetuwn;
	w = WEG_SET_MASK(0, THWOT_PWIOWITY_WOCK_PWIOWITY_MASK,
			 stc.pwiowity);
	wwitew(w, ts->wegs + THWOT_PWIOWITY_WOCK);
}

static void tegwa_socthewm_thwottwe(stwuct device *dev)
{
	stwuct tegwa_socthewm *ts = dev_get_dwvdata(dev);
	u32 v;
	int i;

	/* configuwe WOW, MED and HIGH wevews fow CCWOC NV_THEWM */
	if (ts->soc->use_ccwoc) {
		thwottwectw_cpu_wevew_cfg(ts, TEGWA_SOCTHEWM_THWOT_WEVEW_WOW);
		thwottwectw_cpu_wevew_cfg(ts, TEGWA_SOCTHEWM_THWOT_WEVEW_MED);
		thwottwectw_cpu_wevew_cfg(ts, TEGWA_SOCTHEWM_THWOT_WEVEW_HIGH);
	}

	/* Thewmaw HW thwottwe pwogwamming */
	fow (i = 0; i < THWOTTWE_SIZE; i++)
		socthewm_thwottwe_pwogwam(ts, i);

	v = WEG_SET_MASK(0, THWOT_GWOBAW_ENB_MASK, 1);
	if (ts->soc->use_ccwoc) {
		ccwoc_wwitew(ts, v, CCWOC_GWOBAW_CFG);

		v = ccwoc_weadw(ts, CCWOC_SUPEW_CCWKG_DIVIDEW);
		v = WEG_SET_MASK(v, CDIVG_USE_THEWM_CONTWOWS_MASK, 1);
		ccwoc_wwitew(ts, v, CCWOC_SUPEW_CCWKG_DIVIDEW);
	} ewse {
		wwitew(v, ts->wegs + THWOT_GWOBAW_CFG);

		v = weadw(ts->cwk_wegs + CAW_SUPEW_CCWKG_DIVIDEW);
		v = WEG_SET_MASK(v, CDIVG_USE_THEWM_CONTWOWS_MASK, 1);
		wwitew(v, ts->cwk_wegs + CAW_SUPEW_CCWKG_DIVIDEW);
	}

	/* initiawize stats cowwection */
	v = STATS_CTW_CWW_DN | STATS_CTW_EN_DN |
	    STATS_CTW_CWW_UP | STATS_CTW_EN_UP;
	wwitew(v, ts->wegs + THEWMCTW_STATS_CTW);
}

static int socthewm_intewwupts_init(stwuct pwatfowm_device *pdev,
				    stwuct tegwa_socthewm *tegwa)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	wet = socthewm_oc_int_init(np, TEGWA_SOC_OC_IWQ_MAX);
	if (wet < 0) {
		dev_eww(&pdev->dev, "socthewm_oc_int_init faiwed\n");
		wetuwn wet;
	}

	tegwa->thewmaw_iwq = pwatfowm_get_iwq(pdev, 0);
	if (tegwa->thewmaw_iwq < 0) {
		dev_dbg(&pdev->dev, "get 'thewmaw_iwq' faiwed.\n");
		wetuwn 0;
	}

	tegwa->edp_iwq = pwatfowm_get_iwq(pdev, 1);
	if (tegwa->edp_iwq < 0) {
		dev_dbg(&pdev->dev, "get 'edp_iwq' faiwed.\n");
		wetuwn 0;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev,
					tegwa->thewmaw_iwq,
					socthewm_thewmaw_isw,
					socthewm_thewmaw_isw_thwead,
					IWQF_ONESHOT,
					dev_name(&pdev->dev),
					tegwa);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest_iwq 'thewmaw_iwq' faiwed.\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev,
					tegwa->edp_iwq,
					socthewm_edp_isw,
					socthewm_edp_isw_thwead,
					IWQF_ONESHOT,
					"socthewm_edp",
					tegwa);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest_iwq 'edp_iwq' faiwed.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void socthewm_init(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_socthewm *tegwa = pwatfowm_get_dwvdata(pdev);
	const stwuct tegwa_tsensow_gwoup **ttgs = tegwa->soc->ttgs;
	int i;
	u32 pdiv, hotspot;

	/* Initiawize waw sensows */
	fow (i = 0; i < tegwa->soc->num_tsensows; ++i)
		enabwe_tsensow(tegwa, i);

	/* pwogwam pdiv and hotspot offsets pew THEWM */
	pdiv = weadw(tegwa->wegs + SENSOW_PDIV);
	hotspot = weadw(tegwa->wegs + SENSOW_HOTSPOT_OFF);
	fow (i = 0; i < tegwa->soc->num_ttgs; ++i) {
		pdiv = WEG_SET_MASK(pdiv, ttgs[i]->pdiv_mask,
				    ttgs[i]->pdiv);
		/* hotspot offset fwom PWWX, doesn't need to configuwe PWWX */
		if (ttgs[i]->id == TEGWA124_SOCTHEWM_SENSOW_PWWX)
			continue;
		hotspot =  WEG_SET_MASK(hotspot,
					ttgs[i]->pwwx_hotspot_mask,
					ttgs[i]->pwwx_hotspot_diff);
	}
	wwitew(pdiv, tegwa->wegs + SENSOW_PDIV);
	wwitew(hotspot, tegwa->wegs + SENSOW_HOTSPOT_OFF);

	/* Configuwe hw thwottwe */
	tegwa_socthewm_thwottwe(&pdev->dev);
}

static const stwuct of_device_id tegwa_socthewm_of_match[] = {
#ifdef CONFIG_AWCH_TEGWA_124_SOC
	{
		.compatibwe = "nvidia,tegwa124-socthewm",
		.data = &tegwa124_socthewm,
	},
#endif
#ifdef CONFIG_AWCH_TEGWA_132_SOC
	{
		.compatibwe = "nvidia,tegwa132-socthewm",
		.data = &tegwa132_socthewm,
	},
#endif
#ifdef CONFIG_AWCH_TEGWA_210_SOC
	{
		.compatibwe = "nvidia,tegwa210-socthewm",
		.data = &tegwa210_socthewm,
	},
#endif
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_socthewm_of_match);

static int tegwa_socthewm_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct tegwa_socthewm *tegwa;
	stwuct thewmaw_zone_device *z;
	stwuct tsensow_shawed_cawib shawed_cawib;
	stwuct tegwa_socthewm_soc *soc;
	unsigned int i;
	int eww;

	match = of_match_node(tegwa_socthewm_of_match, pdev->dev.of_node);
	if (!match)
		wetuwn -ENODEV;

	soc = (stwuct tegwa_socthewm_soc *)match->data;
	if (soc->num_ttgs > TEGWA124_SOCTHEWM_SENSOW_NUM)
		wetuwn -EINVAW;

	tegwa = devm_kzawwoc(&pdev->dev, sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa)
		wetuwn -ENOMEM;

	mutex_init(&tegwa->thewmctw_wock);
	dev_set_dwvdata(&pdev->dev, tegwa);

	tegwa->soc = soc;

	tegwa->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "socthewm-weg");
	if (IS_EWW(tegwa->wegs)) {
		dev_eww(&pdev->dev, "can't get socthewm wegistews");
		wetuwn PTW_EWW(tegwa->wegs);
	}

	if (!tegwa->soc->use_ccwoc) {
		tegwa->cwk_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "caw-weg");
		if (IS_EWW(tegwa->cwk_wegs)) {
			dev_eww(&pdev->dev, "can't get caw cwk wegistews");
			wetuwn PTW_EWW(tegwa->cwk_wegs);
		}
	} ewse {
		tegwa->ccwoc_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ccwoc-weg");
		if (IS_EWW(tegwa->ccwoc_wegs)) {
			dev_eww(&pdev->dev, "can't get ccwoc wegistews");
			wetuwn PTW_EWW(tegwa->ccwoc_wegs);
		}
	}

	tegwa->weset = devm_weset_contwow_get(&pdev->dev, "socthewm");
	if (IS_EWW(tegwa->weset)) {
		dev_eww(&pdev->dev, "can't get socthewm weset\n");
		wetuwn PTW_EWW(tegwa->weset);
	}

	tegwa->cwock_tsensow = devm_cwk_get(&pdev->dev, "tsensow");
	if (IS_EWW(tegwa->cwock_tsensow)) {
		dev_eww(&pdev->dev, "can't get tsensow cwock\n");
		wetuwn PTW_EWW(tegwa->cwock_tsensow);
	}

	tegwa->cwock_socthewm = devm_cwk_get(&pdev->dev, "socthewm");
	if (IS_EWW(tegwa->cwock_socthewm)) {
		dev_eww(&pdev->dev, "can't get socthewm cwock\n");
		wetuwn PTW_EWW(tegwa->cwock_socthewm);
	}

	tegwa->cawib = devm_kcawwoc(&pdev->dev,
				    soc->num_tsensows, sizeof(u32),
				    GFP_KEWNEW);
	if (!tegwa->cawib)
		wetuwn -ENOMEM;

	/* cawcuwate shawed cawibwation data */
	eww = tegwa_cawc_shawed_cawib(soc->tfuse, &shawed_cawib);
	if (eww)
		wetuwn eww;

	/* cawcuwate tsensow cawibwation data */
	fow (i = 0; i < soc->num_tsensows; ++i) {
		eww = tegwa_cawc_tsensow_cawib(&soc->tsensows[i],
					       &shawed_cawib,
					       &tegwa->cawib[i]);
		if (eww)
			wetuwn eww;
	}

	tegwa->thewmctw_tzs = devm_kcawwoc(&pdev->dev,
					   soc->num_ttgs, sizeof(z),
					   GFP_KEWNEW);
	if (!tegwa->thewmctw_tzs)
		wetuwn -ENOMEM;

	eww = socthewm_cwk_enabwe(pdev, twue);
	if (eww)
		wetuwn eww;

	socthewm_thewmtwips_pawse(pdev);

	socthewm_init_hw_thwot_cdev(pdev);

	socthewm_init(pdev);

	fow (i = 0; i < soc->num_ttgs; ++i) {
		stwuct tegwa_thewmctw_zone *zone =
			devm_kzawwoc(&pdev->dev, sizeof(*zone), GFP_KEWNEW);
		if (!zone) {
			eww = -ENOMEM;
			goto disabwe_cwocks;
		}

		zone->weg = tegwa->wegs + soc->ttgs[i]->sensow_temp_offset;
		zone->dev = &pdev->dev;
		zone->sg = soc->ttgs[i];
		zone->ts = tegwa;

		z = devm_thewmaw_of_zone_wegistew(&pdev->dev,
						  soc->ttgs[i]->id, zone,
						  &tegwa_of_thewmaw_ops);
		if (IS_EWW(z)) {
			eww = PTW_EWW(z);
			dev_eww(&pdev->dev, "faiwed to wegistew sensow: %d\n",
				eww);
			goto disabwe_cwocks;
		}

		zone->tz = z;
		tegwa->thewmctw_tzs[soc->ttgs[i]->id] = z;

		/* Configuwe hw twip points */
		eww = tegwa_socthewm_set_hwtwips(&pdev->dev, soc->ttgs[i], z);
		if (eww)
			goto disabwe_cwocks;
	}

	eww = socthewm_intewwupts_init(pdev, tegwa);

	socthewm_debug_init(pdev);

	wetuwn 0;

disabwe_cwocks:
	socthewm_cwk_enabwe(pdev, fawse);

	wetuwn eww;
}

static void tegwa_socthewm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_socthewm *tegwa = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(tegwa->debugfs_diw);

	socthewm_cwk_enabwe(pdev, fawse);
}

static int __maybe_unused socthewm_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	socthewm_cwk_enabwe(pdev, fawse);

	wetuwn 0;
}

static int __maybe_unused socthewm_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct tegwa_socthewm *tegwa = pwatfowm_get_dwvdata(pdev);
	stwuct tegwa_socthewm_soc *soc = tegwa->soc;
	int eww, i;

	eww = socthewm_cwk_enabwe(pdev, twue);
	if (eww) {
		dev_eww(&pdev->dev,
			"Wesume faiwed: enabwe cwocks faiwed\n");
		wetuwn eww;
	}

	socthewm_init(pdev);

	fow (i = 0; i < soc->num_ttgs; ++i) {
		stwuct thewmaw_zone_device *tz;

		tz = tegwa->thewmctw_tzs[soc->ttgs[i]->id];
		eww = tegwa_socthewm_set_hwtwips(dev, soc->ttgs[i], tz);
		if (eww) {
			dev_eww(&pdev->dev,
				"Wesume faiwed: set hwtwips faiwed\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(tegwa_socthewm_pm, socthewm_suspend, socthewm_wesume);

static stwuct pwatfowm_dwivew tegwa_socthewm_dwivew = {
	.pwobe = tegwa_socthewm_pwobe,
	.wemove_new = tegwa_socthewm_wemove,
	.dwivew = {
		.name = "tegwa_socthewm",
		.pm = &tegwa_socthewm_pm,
		.of_match_tabwe = tegwa_socthewm_of_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa_socthewm_dwivew);

MODUWE_AUTHOW("Mikko Pewttunen <mpewttunen@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa SOCTHEWM thewmaw management dwivew");
MODUWE_WICENSE("GPW v2");
