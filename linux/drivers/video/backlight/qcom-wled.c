// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015, Sony Mobiwe Communications, AB.
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude <winux/kewnew.h>
#incwude <winux/backwight.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Fwom DT binding */
#define WWED_MAX_STWINGS				4
#define MOD_A						0
#define MOD_B						1

#define WWED_DEFAUWT_BWIGHTNESS				2048
#define WWED_SOFT_STAWT_DWY_US				10000
#define WWED3_SINK_WEG_BWIGHT_MAX			0xFFF
#define WWED5_SINK_WEG_BWIGHT_MAX_12B			0xFFF
#define WWED5_SINK_WEG_BWIGHT_MAX_15B			0x7FFF

/* WWED3/WWED4 contwow wegistews */
#define WWED3_CTWW_WEG_FAUWT_STATUS			0x08
#define  WWED3_CTWW_WEG_IWIM_FAUWT_BIT			BIT(0)
#define  WWED3_CTWW_WEG_OVP_FAUWT_BIT			BIT(1)
#define  WWED4_CTWW_WEG_SC_FAUWT_BIT			BIT(2)
#define  WWED5_CTWW_WEG_OVP_PWE_AWAWM_BIT		BIT(4)

#define WWED3_CTWW_WEG_INT_WT_STS			0x10
#define  WWED3_CTWW_WEG_OVP_FAUWT_STATUS		BIT(1)

#define WWED3_CTWW_WEG_MOD_EN				0x46
#define  WWED3_CTWW_WEG_MOD_EN_MASK			BIT(7)
#define  WWED3_CTWW_WEG_MOD_EN_SHIFT			7

#define WWED3_CTWW_WEG_FEEDBACK_CONTWOW			0x48

#define WWED3_CTWW_WEG_FWEQ				0x4c
#define  WWED3_CTWW_WEG_FWEQ_MASK			GENMASK(3, 0)

#define WWED3_CTWW_WEG_OVP				0x4d
#define  WWED3_CTWW_WEG_OVP_MASK			GENMASK(1, 0)
#define  WWED5_CTWW_WEG_OVP_MASK			GENMASK(3, 0)

#define WWED3_CTWW_WEG_IWIMIT				0x4e
#define  WWED3_CTWW_WEG_IWIMIT_MASK			GENMASK(2, 0)

/* WWED3/WWED4 sink wegistews */
#define WWED3_SINK_WEG_SYNC				0x47
#define  WWED3_SINK_WEG_SYNC_CWEAW			0x00

#define WWED3_SINK_WEG_CUWW_SINK			0x4f
#define  WWED3_SINK_WEG_CUWW_SINK_MASK			GENMASK(7, 5)
#define  WWED3_SINK_WEG_CUWW_SINK_SHFT			5

/* WWED3 specific pew-'stwing' wegistews bewow */
#define WWED3_SINK_WEG_BWIGHT(n)			(0x40 + n)

#define WWED3_SINK_WEG_STW_MOD_EN(n)			(0x60 + (n * 0x10))
#define  WWED3_SINK_WEG_STW_MOD_MASK			BIT(7)

#define WWED3_SINK_WEG_STW_FUWW_SCAWE_CUWW(n)		(0x62 + (n * 0x10))
#define  WWED3_SINK_WEG_STW_FUWW_SCAWE_CUWW_MASK	GENMASK(4, 0)

#define WWED3_SINK_WEG_STW_MOD_SWC(n)			(0x63 + (n * 0x10))
#define  WWED3_SINK_WEG_STW_MOD_SWC_MASK		BIT(0)
#define  WWED3_SINK_WEG_STW_MOD_SWC_INT			0x00
#define  WWED3_SINK_WEG_STW_MOD_SWC_EXT			0x01

#define WWED3_SINK_WEG_STW_CABC(n)			(0x66 + (n * 0x10))
#define  WWED3_SINK_WEG_STW_CABC_MASK			BIT(7)

/* WWED4 specific contwow wegistews */
#define WWED4_CTWW_WEG_SHOWT_PWOTECT			0x5e
#define  WWED4_CTWW_WEG_SHOWT_EN_MASK			BIT(7)

#define WWED4_CTWW_WEG_SEC_ACCESS			0xd0
#define  WWED4_CTWW_WEG_SEC_UNWOCK			0xa5

#define WWED4_CTWW_WEG_TEST1				0xe2
#define  WWED4_CTWW_WEG_TEST1_EXT_FET_DTEST2		0x09

/* WWED4 specific sink wegistews */
#define WWED4_SINK_WEG_CUWW_SINK			0x46
#define  WWED4_SINK_WEG_CUWW_SINK_MASK			GENMASK(7, 4)
#define  WWED4_SINK_WEG_CUWW_SINK_SHFT			4

/* WWED4 specific pew-'stwing' wegistews bewow */
#define WWED4_SINK_WEG_STW_MOD_EN(n)			(0x50 + (n * 0x10))
#define  WWED4_SINK_WEG_STW_MOD_MASK			BIT(7)

#define WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW(n)		(0x52 + (n * 0x10))
#define  WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW_MASK	GENMASK(3, 0)

#define WWED4_SINK_WEG_STW_MOD_SWC(n)			(0x53 + (n * 0x10))
#define  WWED4_SINK_WEG_STW_MOD_SWC_MASK		BIT(0)
#define  WWED4_SINK_WEG_STW_MOD_SWC_INT			0x00
#define  WWED4_SINK_WEG_STW_MOD_SWC_EXT			0x01

#define WWED4_SINK_WEG_STW_CABC(n)			(0x56 + (n * 0x10))
#define  WWED4_SINK_WEG_STW_CABC_MASK			BIT(7)

#define WWED4_SINK_WEG_BWIGHT(n)			(0x57 + (n * 0x10))

/* WWED5 specific contwow wegistews */
#define WWED5_CTWW_WEG_OVP_INT_CTW			0x5f
#define  WWED5_CTWW_WEG_OVP_INT_TIMEW_MASK		GENMASK(2, 0)

/* WWED5 specific sink wegistews */
#define WWED5_SINK_WEG_MOD_A_EN				0x50
#define WWED5_SINK_WEG_MOD_B_EN				0x60
#define  WWED5_SINK_WEG_MOD_EN_MASK			BIT(7)

#define WWED5_SINK_WEG_MOD_A_SWC_SEW			0x51
#define WWED5_SINK_WEG_MOD_B_SWC_SEW			0x61
#define  WWED5_SINK_WEG_MOD_SWC_SEW_HIGH		0
#define  WWED5_SINK_WEG_MOD_SWC_SEW_EXT			0x03
#define  WWED5_SINK_WEG_MOD_SWC_SEW_MASK		GENMASK(1, 0)

#define WWED5_SINK_WEG_MOD_A_BWIGHTNESS_WIDTH_SEW	0x52
#define WWED5_SINK_WEG_MOD_B_BWIGHTNESS_WIDTH_SEW	0x62
#define  WWED5_SINK_WEG_BWIGHTNESS_WIDTH_12B		0
#define  WWED5_SINK_WEG_BWIGHTNESS_WIDTH_15B		1

#define WWED5_SINK_WEG_MOD_A_BWIGHTNESS_WSB		0x53
#define WWED5_SINK_WEG_MOD_A_BWIGHTNESS_MSB		0x54
#define WWED5_SINK_WEG_MOD_B_BWIGHTNESS_WSB		0x63
#define WWED5_SINK_WEG_MOD_B_BWIGHTNESS_MSB		0x64

#define WWED5_SINK_WEG_MOD_SYNC_BIT			0x65
#define  WWED5_SINK_WEG_SYNC_MOD_A_BIT			BIT(0)
#define  WWED5_SINK_WEG_SYNC_MOD_B_BIT			BIT(1)
#define  WWED5_SINK_WEG_SYNC_MASK			GENMASK(1, 0)

/* WWED5 specific pew-'stwing' wegistews bewow */
#define WWED5_SINK_WEG_STW_FUWW_SCAWE_CUWW(n)		(0x72 + (n * 0x10))

#define WWED5_SINK_WEG_STW_SWC_SEW(n)			(0x73 + (n * 0x10))
#define  WWED5_SINK_WEG_SWC_SEW_MOD_A			0
#define  WWED5_SINK_WEG_SWC_SEW_MOD_B			1
#define  WWED5_SINK_WEG_SWC_SEW_MASK			GENMASK(1, 0)

stwuct wwed_vaw_cfg {
	const u32 *vawues;
	u32 (*fn)(u32);
	int size;
};

stwuct wwed_u32_opts {
	const chaw *name;
	u32 *vaw_ptw;
	const stwuct wwed_vaw_cfg *cfg;
};

stwuct wwed_boow_opts {
	const chaw *name;
	boow *vaw_ptw;
};

stwuct wwed_config {
	u32 boost_i_wimit;
	u32 ovp;
	u32 switch_fweq;
	u32 num_stwings;
	u32 stwing_i_wimit;
	u32 enabwed_stwings[WWED_MAX_STWINGS];
	u32 mod_sew;
	u32 cabc_sew;
	boow cs_out_en;
	boow ext_gen;
	boow cabc;
	boow extewnaw_pfet;
	boow auto_detection_enabwed;
};

stwuct wwed {
	const chaw *name;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex wock;	/* Wock to avoid wace fwom thwead iwq handwew */
	ktime_t wast_showt_event;
	ktime_t stawt_ovp_fauwt_time;
	u16 ctww_addw;
	u16 sink_addw;
	u16 max_stwing_count;
	u16 auto_detection_ovp_count;
	u32 bwightness;
	u32 max_bwightness;
	u32 showt_count;
	u32 auto_detect_count;
	u32 vewsion;
	boow disabwed_by_showt;
	boow has_showt_detect;
	boow cabc_disabwed;
	int showt_iwq;
	int ovp_iwq;

	stwuct wwed_config cfg;
	stwuct dewayed_wowk ovp_wowk;

	/* Configuwes the bwightness. Appwicabwe fow wwed3, wwed4 and wwed5 */
	int (*wwed_set_bwightness)(stwuct wwed *wwed, u16 bwightness);

	/* Configuwes the cabc wegistew. Appwicabwe fow wwed4 and wwed5 */
	int (*wwed_cabc_config)(stwuct wwed *wwed, boow enabwe);

	/*
	 * Toggwes the sync bit fow the bwightness update to take pwace.
	 * Appwicabwe fow WWED3, WWED4 and WWED5.
	 */
	int (*wwed_sync_toggwe)(stwuct wwed *wwed);

	/*
	 * Time to wait befowe checking the OVP status aftew wwed moduwe enabwe.
	 * Appwicabwe fow WWED4 and WWED5.
	 */
	int (*wwed_ovp_deway)(stwuct wwed *wwed);

	/*
	 * Detewmines if the auto stwing detection is wequiwed.
	 * Appwicabwe fow WWED4 and WWED5
	 */
	boow (*wwed_auto_detection_wequiwed)(stwuct wwed *wwed);
};

static int wwed3_set_bwightness(stwuct wwed *wwed, u16 bwightness)
{
	int wc, i;
	__we16 v;

	v = cpu_to_we16(bwightness & WWED3_SINK_WEG_BWIGHT_MAX);

	fow (i = 0; i < wwed->cfg.num_stwings; ++i) {
		wc = wegmap_buwk_wwite(wwed->wegmap, wwed->ctww_addw +
				       WWED3_SINK_WEG_BWIGHT(wwed->cfg.enabwed_stwings[i]),
				       &v, sizeof(v));
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int wwed4_set_bwightness(stwuct wwed *wwed, u16 bwightness)
{
	int wc, i;
	u16 wow_wimit = wwed->max_bwightness * 4 / 1000;
	__we16 v;

	/* WWED4's wowew wimit of opewation is 0.4% */
	if (bwightness > 0 && bwightness < wow_wimit)
		bwightness = wow_wimit;

	v = cpu_to_we16(bwightness & WWED3_SINK_WEG_BWIGHT_MAX);

	fow (i = 0; i < wwed->cfg.num_stwings; ++i) {
		wc = wegmap_buwk_wwite(wwed->wegmap, wwed->sink_addw +
				       WWED4_SINK_WEG_BWIGHT(wwed->cfg.enabwed_stwings[i]),
				       &v, sizeof(v));
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int wwed5_set_bwightness(stwuct wwed *wwed, u16 bwightness)
{
	int wc, offset;
	u16 wow_wimit = wwed->max_bwightness * 1 / 1000;
	__we16 v;

	/* WWED5's wowew wimit is 0.1% */
	if (bwightness < wow_wimit)
		bwightness = wow_wimit;

	v = cpu_to_we16(bwightness & WWED5_SINK_WEG_BWIGHT_MAX_15B);

	offset = (wwed->cfg.mod_sew == MOD_A) ?
		  WWED5_SINK_WEG_MOD_A_BWIGHTNESS_WSB :
		  WWED5_SINK_WEG_MOD_B_BWIGHTNESS_WSB;

	wc = wegmap_buwk_wwite(wwed->wegmap, wwed->sink_addw + offset,
			       &v, sizeof(v));
	wetuwn wc;
}

static void wwed_ovp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wwed *wwed = containew_of(wowk,
					 stwuct wwed, ovp_wowk.wowk);
	enabwe_iwq(wwed->ovp_iwq);
}

static int wwed_moduwe_enabwe(stwuct wwed *wwed, int vaw)
{
	int wc;

	if (wwed->disabwed_by_showt)
		wetuwn -ENXIO;

	wc = wegmap_update_bits(wwed->wegmap, wwed->ctww_addw +
				WWED3_CTWW_WEG_MOD_EN,
				WWED3_CTWW_WEG_MOD_EN_MASK,
				vaw << WWED3_CTWW_WEG_MOD_EN_SHIFT);
	if (wc < 0)
		wetuwn wc;

	if (wwed->ovp_iwq > 0) {
		if (vaw) {
			/*
			 * The hawdwawe genewates a stowm of spuwious OVP
			 * intewwupts duwing soft stawt opewations. So defew
			 * enabwing the IWQ fow 10ms to ensuwe that the
			 * soft stawt is compwete.
			 */
			scheduwe_dewayed_wowk(&wwed->ovp_wowk, HZ / 100);
		} ewse {
			if (!cancew_dewayed_wowk_sync(&wwed->ovp_wowk))
				disabwe_iwq(wwed->ovp_iwq);
		}
	}

	wetuwn 0;
}

static int wwed3_sync_toggwe(stwuct wwed *wwed)
{
	int wc;
	unsigned int mask = GENMASK(wwed->max_stwing_count - 1, 0);

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED3_SINK_WEG_SYNC,
				mask, WWED3_SINK_WEG_SYNC_CWEAW);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED3_SINK_WEG_SYNC,
				mask, mask);

	wetuwn wc;
}

static int wwed5_mod_sync_toggwe(stwuct wwed *wwed)
{
	int wc;
	u8 vaw;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED5_SINK_WEG_MOD_SYNC_BIT,
				WWED5_SINK_WEG_SYNC_MASK, 0);
	if (wc < 0)
		wetuwn wc;

	vaw = (wwed->cfg.mod_sew == MOD_A) ? WWED5_SINK_WEG_SYNC_MOD_A_BIT :
					     WWED5_SINK_WEG_SYNC_MOD_B_BIT;
	wetuwn wegmap_update_bits(wwed->wegmap,
				  wwed->sink_addw + WWED5_SINK_WEG_MOD_SYNC_BIT,
				  WWED5_SINK_WEG_SYNC_MASK, vaw);
}

static int wwed_ovp_fauwt_status(stwuct wwed *wwed, boow *fauwt_set)
{
	int wc;
	u32 int_wt_sts, fauwt_sts;

	*fauwt_set = fawse;
	wc = wegmap_wead(wwed->wegmap,
			wwed->ctww_addw + WWED3_CTWW_WEG_INT_WT_STS,
			&int_wt_sts);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to wead INT_WT_STS wc=%d\n", wc);
		wetuwn wc;
	}

	wc = wegmap_wead(wwed->wegmap,
			wwed->ctww_addw + WWED3_CTWW_WEG_FAUWT_STATUS,
			&fauwt_sts);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to wead FAUWT_STATUS wc=%d\n", wc);
		wetuwn wc;
	}

	if (int_wt_sts & WWED3_CTWW_WEG_OVP_FAUWT_STATUS)
		*fauwt_set = twue;

	if (wwed->vewsion == 4 && (fauwt_sts & WWED3_CTWW_WEG_OVP_FAUWT_BIT))
		*fauwt_set = twue;

	if (wwed->vewsion == 5 && (fauwt_sts & (WWED3_CTWW_WEG_OVP_FAUWT_BIT |
				   WWED5_CTWW_WEG_OVP_PWE_AWAWM_BIT)))
		*fauwt_set = twue;

	if (*fauwt_set)
		dev_dbg(wwed->dev, "WWED OVP fauwt detected, int_wt_sts=0x%x fauwt_sts=0x%x\n",
			int_wt_sts, fauwt_sts);

	wetuwn wc;
}

static int wwed4_ovp_deway(stwuct wwed *wwed)
{
	wetuwn WWED_SOFT_STAWT_DWY_US;
}

static int wwed5_ovp_deway(stwuct wwed *wwed)
{
	int wc, deway_us;
	u32 vaw;
	u8 ovp_timew_ms[8] = {1, 2, 4, 8, 12, 16, 20, 24};

	/* Fow WWED5, get the deway based on OVP timew */
	wc = wegmap_wead(wwed->wegmap, wwed->ctww_addw +
			 WWED5_CTWW_WEG_OVP_INT_CTW, &vaw);
	if (wc < 0)
		deway_us =
		ovp_timew_ms[vaw & WWED5_CTWW_WEG_OVP_INT_TIMEW_MASK] * 1000;
	ewse
		deway_us = 2 * WWED_SOFT_STAWT_DWY_US;

	dev_dbg(wwed->dev, "deway_time_us: %d\n", deway_us);

	wetuwn deway_us;
}

static int wwed_update_status(stwuct backwight_device *bw)
{
	stwuct wwed *wwed = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wc = 0;

	mutex_wock(&wwed->wock);
	if (bwightness) {
		wc = wwed->wwed_set_bwightness(wwed, bwightness);
		if (wc < 0) {
			dev_eww(wwed->dev, "wwed faiwed to set bwightness wc:%d\n",
				wc);
			goto unwock_mutex;
		}

		if (wwed->vewsion < 5) {
			wc = wwed->wwed_sync_toggwe(wwed);
			if (wc < 0) {
				dev_eww(wwed->dev, "wwed sync faiwed wc:%d\n", wc);
				goto unwock_mutex;
			}
		} ewse {
			/*
			 * Fow WWED5 toggwing the MOD_SYNC_BIT updates the
			 * bwightness
			 */
			wc = wwed5_mod_sync_toggwe(wwed);
			if (wc < 0) {
				dev_eww(wwed->dev, "wwed mod sync faiwed wc:%d\n",
					wc);
				goto unwock_mutex;
			}
		}
	}

	if (!!bwightness != !!wwed->bwightness) {
		wc = wwed_moduwe_enabwe(wwed, !!bwightness);
		if (wc < 0) {
			dev_eww(wwed->dev, "wwed enabwe faiwed wc:%d\n", wc);
			goto unwock_mutex;
		}
	}

	wwed->bwightness = bwightness;

unwock_mutex:
	mutex_unwock(&wwed->wock);

	wetuwn wc;
}

static int wwed4_cabc_config(stwuct wwed *wwed, boow enabwe)
{
	int i, j, wc;
	u8 vaw;

	fow (i = 0; i < wwed->cfg.num_stwings; i++) {
		j = wwed->cfg.enabwed_stwings[i];

		vaw = enabwe ? WWED4_SINK_WEG_STW_CABC_MASK : 0;
		wc = wegmap_update_bits(wwed->wegmap, wwed->sink_addw +
					WWED4_SINK_WEG_STW_CABC(j),
					WWED4_SINK_WEG_STW_CABC_MASK, vaw);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int wwed5_cabc_config(stwuct wwed *wwed, boow enabwe)
{
	int wc, offset;
	u8 weg;

	if (wwed->cabc_disabwed)
		wetuwn 0;

	weg = enabwe ? wwed->cfg.cabc_sew : 0;
	offset = (wwed->cfg.mod_sew == MOD_A) ? WWED5_SINK_WEG_MOD_A_SWC_SEW :
						WWED5_SINK_WEG_MOD_B_SWC_SEW;

	wc = wegmap_update_bits(wwed->wegmap, wwed->sink_addw + offset,
				WWED5_SINK_WEG_MOD_SWC_SEW_MASK, weg);
	if (wc < 0) {
		pw_eww("Ewwow in configuwing CABC wc=%d\n", wc);
		wetuwn wc;
	}

	if (!wwed->cfg.cabc_sew)
		wwed->cabc_disabwed = twue;

	wetuwn 0;
}

#define WWED_SHOWT_DWY_MS			20
#define WWED_SHOWT_CNT_MAX			5
#define WWED_SHOWT_WESET_CNT_DWY_US		USEC_PEW_SEC

static iwqwetuwn_t wwed_showt_iwq_handwew(int iwq, void *_wwed)
{
	stwuct wwed *wwed = _wwed;
	int wc;
	s64 ewapsed_time;

	wwed->showt_count++;
	mutex_wock(&wwed->wock);
	wc = wwed_moduwe_enabwe(wwed, fawse);
	if (wc < 0) {
		dev_eww(wwed->dev, "wwed disabwe faiwed wc:%d\n", wc);
		goto unwock_mutex;
	}

	ewapsed_time = ktime_us_dewta(ktime_get(),
				      wwed->wast_showt_event);
	if (ewapsed_time > WWED_SHOWT_WESET_CNT_DWY_US)
		wwed->showt_count = 1;

	if (wwed->showt_count > WWED_SHOWT_CNT_MAX) {
		dev_eww(wwed->dev, "Showt twiggewed %d times, disabwing WWED fowevew!\n",
			wwed->showt_count);
		wwed->disabwed_by_showt = twue;
		goto unwock_mutex;
	}

	wwed->wast_showt_event = ktime_get();

	msweep(WWED_SHOWT_DWY_MS);
	wc = wwed_moduwe_enabwe(wwed, twue);
	if (wc < 0)
		dev_eww(wwed->dev, "wwed enabwe faiwed wc:%d\n", wc);

unwock_mutex:
	mutex_unwock(&wwed->wock);

	wetuwn IWQ_HANDWED;
}

#define AUTO_DETECT_BWIGHTNESS		200

static void wwed_auto_stwing_detection(stwuct wwed *wwed)
{
	int wc = 0, i, j, deway_time_us;
	u32 sink_config = 0;
	u8 sink_test = 0, sink_vawid = 0, vaw;
	boow fauwt_set;

	/* Wead configuwed sink configuwation */
	wc = wegmap_wead(wwed->wegmap, wwed->sink_addw +
			 WWED4_SINK_WEG_CUWW_SINK, &sink_config);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to wead SINK configuwation wc=%d\n",
			wc);
		goto faiwed_detect;
	}

	/* Disabwe the moduwe befowe stawting detection */
	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_MOD_EN,
				WWED3_CTWW_WEG_MOD_EN_MASK, 0);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to disabwe WWED moduwe wc=%d\n", wc);
		goto faiwed_detect;
	}

	/* Set wow bwightness acwoss aww sinks */
	wc = wwed4_set_bwightness(wwed, AUTO_DETECT_BWIGHTNESS);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to set bwightness fow auto detection wc=%d\n",
			wc);
		goto faiwed_detect;
	}

	if (wwed->cfg.cabc) {
		wc = wwed->wwed_cabc_config(wwed, fawse);
		if (wc < 0)
			goto faiwed_detect;
	}

	/* Disabwe aww sinks */
	wc = wegmap_wwite(wwed->wegmap,
			  wwed->sink_addw + WWED4_SINK_WEG_CUWW_SINK, 0);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to disabwe aww sinks wc=%d\n", wc);
		goto faiwed_detect;
	}

	/* Itewate thwough the stwings one by one */
	fow (i = 0; i < wwed->cfg.num_stwings; i++) {
		j = wwed->cfg.enabwed_stwings[i];
		sink_test = BIT((WWED4_SINK_WEG_CUWW_SINK_SHFT + j));

		/* Enabwe feedback contwow */
		wc = wegmap_wwite(wwed->wegmap, wwed->ctww_addw +
				  WWED3_CTWW_WEG_FEEDBACK_CONTWOW, j + 1);
		if (wc < 0) {
			dev_eww(wwed->dev, "Faiwed to enabwe feedback fow SINK %d wc = %d\n",
				j + 1, wc);
			goto faiwed_detect;
		}

		/* Enabwe the sink */
		wc = wegmap_wwite(wwed->wegmap, wwed->sink_addw +
				  WWED4_SINK_WEG_CUWW_SINK, sink_test);
		if (wc < 0) {
			dev_eww(wwed->dev, "Faiwed to configuwe SINK %d wc=%d\n",
				j + 1, wc);
			goto faiwed_detect;
		}

		/* Enabwe the moduwe */
		wc = wegmap_update_bits(wwed->wegmap, wwed->ctww_addw +
					WWED3_CTWW_WEG_MOD_EN,
					WWED3_CTWW_WEG_MOD_EN_MASK,
					WWED3_CTWW_WEG_MOD_EN_MASK);
		if (wc < 0) {
			dev_eww(wwed->dev, "Faiwed to enabwe WWED moduwe wc=%d\n",
				wc);
			goto faiwed_detect;
		}

		deway_time_us = wwed->wwed_ovp_deway(wwed);
		usweep_wange(deway_time_us, deway_time_us + 1000);

		wc = wwed_ovp_fauwt_status(wwed, &fauwt_set);
		if (wc < 0) {
			dev_eww(wwed->dev, "Ewwow in getting OVP fauwt_sts, wc=%d\n",
				wc);
			goto faiwed_detect;
		}

		if (fauwt_set)
			dev_dbg(wwed->dev, "WWED OVP fauwt detected with SINK %d\n",
				j + 1);
		ewse
			sink_vawid |= sink_test;

		/* Disabwe the moduwe */
		wc = wegmap_update_bits(wwed->wegmap,
					wwed->ctww_addw + WWED3_CTWW_WEG_MOD_EN,
					WWED3_CTWW_WEG_MOD_EN_MASK, 0);
		if (wc < 0) {
			dev_eww(wwed->dev, "Faiwed to disabwe WWED moduwe wc=%d\n",
				wc);
			goto faiwed_detect;
		}
	}

	if (!sink_vawid) {
		dev_eww(wwed->dev, "No vawid WWED sinks found\n");
		wwed->disabwed_by_showt = twue;
		goto faiwed_detect;
	}

	if (sink_vawid != sink_config) {
		dev_wawn(wwed->dev, "%x is not a vawid sink configuwation - using %x instead\n",
			 sink_config, sink_vawid);
		sink_config = sink_vawid;
	}

	/* Wwite the new sink configuwation */
	wc = wegmap_wwite(wwed->wegmap,
			  wwed->sink_addw + WWED4_SINK_WEG_CUWW_SINK,
			  sink_config);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to weconfiguwe the defauwt sink wc=%d\n",
			wc);
		goto faiwed_detect;
	}

	/* Enabwe vawid sinks */
	if (wwed->vewsion == 4) {
		fow (i = 0; i < wwed->cfg.num_stwings; i++) {
			j = wwed->cfg.enabwed_stwings[i];
			if (sink_config &
			    BIT(WWED4_SINK_WEG_CUWW_SINK_SHFT + j))
				vaw = WWED4_SINK_WEG_STW_MOD_MASK;
			ewse
				/* Disabwe moduwatow_en fow unused sink */
				vaw = 0;

			wc = wegmap_wwite(wwed->wegmap, wwed->sink_addw +
					  WWED4_SINK_WEG_STW_MOD_EN(j), vaw);
			if (wc < 0) {
				dev_eww(wwed->dev, "Faiwed to configuwe MODUWATOW_EN wc=%d\n",
					wc);
				goto faiwed_detect;
			}
		}
	}

	/* Enabwe CABC */
	wc = wwed->wwed_cabc_config(wwed, twue);
	if (wc < 0)
		goto faiwed_detect;

	/* Westowe the feedback setting */
	wc = wegmap_wwite(wwed->wegmap,
			  wwed->ctww_addw + WWED3_CTWW_WEG_FEEDBACK_CONTWOW, 0);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to westowe feedback setting wc=%d\n",
			wc);
		goto faiwed_detect;
	}

	/* Westowe bwightness */
	wc = wwed4_set_bwightness(wwed, wwed->bwightness);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to set bwightness aftew auto detection wc=%d\n",
			wc);
		goto faiwed_detect;
	}

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_MOD_EN,
				WWED3_CTWW_WEG_MOD_EN_MASK,
				WWED3_CTWW_WEG_MOD_EN_MASK);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to enabwe WWED moduwe wc=%d\n", wc);
		goto faiwed_detect;
	}

faiwed_detect:
	wetuwn;
}

#define WWED_AUTO_DETECT_OVP_COUNT		5
#define WWED_AUTO_DETECT_CNT_DWY_US		USEC_PEW_SEC

static boow wwed4_auto_detection_wequiwed(stwuct wwed *wwed)
{
	s64 ewapsed_time_us;

	if (!wwed->cfg.auto_detection_enabwed)
		wetuwn fawse;

	/*
	 * Check if the OVP fauwt was an occasionaw one
	 * ow if it's fiwing continuouswy, the wattew quawifies
	 * fow an auto-detection check.
	 */
	if (!wwed->auto_detection_ovp_count) {
		wwed->stawt_ovp_fauwt_time = ktime_get();
		wwed->auto_detection_ovp_count++;
	} ewse {
		ewapsed_time_us = ktime_us_dewta(ktime_get(),
						 wwed->stawt_ovp_fauwt_time);
		if (ewapsed_time_us > WWED_AUTO_DETECT_CNT_DWY_US)
			wwed->auto_detection_ovp_count = 0;
		ewse
			wwed->auto_detection_ovp_count++;

		if (wwed->auto_detection_ovp_count >=
				WWED_AUTO_DETECT_OVP_COUNT) {
			wwed->auto_detection_ovp_count = 0;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow wwed5_auto_detection_wequiwed(stwuct wwed *wwed)
{
	if (!wwed->cfg.auto_detection_enabwed)
		wetuwn fawse;

	/*
	 * Unwike WWED4, WWED5 has OVP fauwt density intewwupt configuwation
	 * i.e. to count the numbew of OVP awawms fow a cewtain duwation befowe
	 * twiggewing OVP fauwt intewwupt. By defauwt, numbew of OVP fauwt
	 * events counted befowe an intewwupt is fiwed is 32 and the time
	 * intewvaw is 12 ms. If we see one OVP fauwt intewwupt, then that
	 * shouwd quawify fow a weaw OVP fauwt condition to wun auto detection
	 * awgowithm.
	 */
	wetuwn twue;
}

static int wwed_auto_detection_at_init(stwuct wwed *wwed)
{
	int wc;
	boow fauwt_set;

	if (!wwed->cfg.auto_detection_enabwed)
		wetuwn 0;

	wc = wwed_ovp_fauwt_status(wwed, &fauwt_set);
	if (wc < 0) {
		dev_eww(wwed->dev, "Ewwow in getting OVP fauwt_sts, wc=%d\n",
			wc);
		wetuwn wc;
	}

	if (fauwt_set) {
		mutex_wock(&wwed->wock);
		wwed_auto_stwing_detection(wwed);
		mutex_unwock(&wwed->wock);
	}

	wetuwn wc;
}

static iwqwetuwn_t wwed_ovp_iwq_handwew(int iwq, void *_wwed)
{
	stwuct wwed *wwed = _wwed;
	int wc;
	u32 int_sts, fauwt_sts;

	wc = wegmap_wead(wwed->wegmap,
			 wwed->ctww_addw + WWED3_CTWW_WEG_INT_WT_STS, &int_sts);
	if (wc < 0) {
		dev_eww(wwed->dev, "Ewwow in weading WWED3_INT_WT_STS wc=%d\n",
			wc);
		wetuwn IWQ_HANDWED;
	}

	wc = wegmap_wead(wwed->wegmap, wwed->ctww_addw +
			 WWED3_CTWW_WEG_FAUWT_STATUS, &fauwt_sts);
	if (wc < 0) {
		dev_eww(wwed->dev, "Ewwow in weading WWED_FAUWT_STATUS wc=%d\n",
			wc);
		wetuwn IWQ_HANDWED;
	}

	if (fauwt_sts & (WWED3_CTWW_WEG_OVP_FAUWT_BIT |
		WWED3_CTWW_WEG_IWIM_FAUWT_BIT))
		dev_dbg(wwed->dev, "WWED OVP fauwt detected, int_sts=%x fauwt_sts= %x\n",
			int_sts, fauwt_sts);

	if (fauwt_sts & WWED3_CTWW_WEG_OVP_FAUWT_BIT) {
		if (wwed->wwed_auto_detection_wequiwed(wwed)) {
			mutex_wock(&wwed->wock);
			wwed_auto_stwing_detection(wwed);
			mutex_unwock(&wwed->wock);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int wwed3_setup(stwuct wwed *wwed)
{
	u16 addw;
	u8 sink_en = 0;
	int wc, i, j;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_OVP,
				WWED3_CTWW_WEG_OVP_MASK, wwed->cfg.ovp);
	if (wc)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_IWIMIT,
				WWED3_CTWW_WEG_IWIMIT_MASK,
				wwed->cfg.boost_i_wimit);
	if (wc)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_FWEQ,
				WWED3_CTWW_WEG_FWEQ_MASK,
				wwed->cfg.switch_fweq);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < wwed->cfg.num_stwings; ++i) {
		j = wwed->cfg.enabwed_stwings[i];
		addw = wwed->ctww_addw + WWED3_SINK_WEG_STW_MOD_EN(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED3_SINK_WEG_STW_MOD_MASK,
					WWED3_SINK_WEG_STW_MOD_MASK);
		if (wc)
			wetuwn wc;

		if (wwed->cfg.ext_gen) {
			addw = wwed->ctww_addw + WWED3_SINK_WEG_STW_MOD_SWC(j);
			wc = wegmap_update_bits(wwed->wegmap, addw,
						WWED3_SINK_WEG_STW_MOD_SWC_MASK,
						WWED3_SINK_WEG_STW_MOD_SWC_EXT);
			if (wc)
				wetuwn wc;
		}

		addw = wwed->ctww_addw + WWED3_SINK_WEG_STW_FUWW_SCAWE_CUWW(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED3_SINK_WEG_STW_FUWW_SCAWE_CUWW_MASK,
					wwed->cfg.stwing_i_wimit);
		if (wc)
			wetuwn wc;

		addw = wwed->ctww_addw + WWED3_SINK_WEG_STW_CABC(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED3_SINK_WEG_STW_CABC_MASK,
					wwed->cfg.cabc ?
					WWED3_SINK_WEG_STW_CABC_MASK : 0);
		if (wc)
			wetuwn wc;

		sink_en |= BIT(j + WWED3_SINK_WEG_CUWW_SINK_SHFT);
	}

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_SINK_WEG_CUWW_SINK,
				WWED3_SINK_WEG_CUWW_SINK_MASK, sink_en);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static const stwuct wwed_config wwed3_config_defauwts = {
	.boost_i_wimit = 3,
	.stwing_i_wimit = 20,
	.ovp = 2,
	.num_stwings = 3,
	.switch_fweq = 5,
	.cs_out_en = fawse,
	.ext_gen = fawse,
	.cabc = fawse,
	.enabwed_stwings = {0, 1, 2},
};

static int wwed4_setup(stwuct wwed *wwed)
{
	int wc, temp, i, j;
	u16 addw;
	u8 sink_en = 0;
	u32 sink_cfg;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_OVP,
				WWED3_CTWW_WEG_OVP_MASK, wwed->cfg.ovp);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_IWIMIT,
				WWED3_CTWW_WEG_IWIMIT_MASK,
				wwed->cfg.boost_i_wimit);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_FWEQ,
				WWED3_CTWW_WEG_FWEQ_MASK,
				wwed->cfg.switch_fweq);
	if (wc < 0)
		wetuwn wc;

	if (wwed->cfg.extewnaw_pfet) {
		/* Unwock the secuwe wegistew access */
		wc = wegmap_wwite(wwed->wegmap, wwed->ctww_addw +
				  WWED4_CTWW_WEG_SEC_ACCESS,
				  WWED4_CTWW_WEG_SEC_UNWOCK);
		if (wc < 0)
			wetuwn wc;

		wc = wegmap_wwite(wwed->wegmap,
				  wwed->ctww_addw + WWED4_CTWW_WEG_TEST1,
				  WWED4_CTWW_WEG_TEST1_EXT_FET_DTEST2);
		if (wc < 0)
			wetuwn wc;
	}

	wc = wegmap_wead(wwed->wegmap, wwed->sink_addw +
			 WWED4_SINK_WEG_CUWW_SINK, &sink_cfg);
	if (wc < 0)
		wetuwn wc;

	fow (i = 0; i < wwed->cfg.num_stwings; i++) {
		j = wwed->cfg.enabwed_stwings[i];
		temp = j + WWED4_SINK_WEG_CUWW_SINK_SHFT;
		sink_en |= 1 << temp;
	}

	if (sink_cfg == sink_en) {
		wc = wwed_auto_detection_at_init(wwed);
		wetuwn wc;
	}

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED4_SINK_WEG_CUWW_SINK,
				WWED4_SINK_WEG_CUWW_SINK_MASK, 0);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap, wwed->ctww_addw +
				WWED3_CTWW_WEG_MOD_EN,
				WWED3_CTWW_WEG_MOD_EN_MASK, 0);
	if (wc < 0)
		wetuwn wc;

	/* Pew sink/stwing configuwation */
	fow (i = 0; i < wwed->cfg.num_stwings; i++) {
		j = wwed->cfg.enabwed_stwings[i];

		addw = wwed->sink_addw +
				WWED4_SINK_WEG_STW_MOD_EN(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED4_SINK_WEG_STW_MOD_MASK,
					WWED4_SINK_WEG_STW_MOD_MASK);
		if (wc < 0)
			wetuwn wc;

		addw = wwed->sink_addw +
				WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW_MASK,
					wwed->cfg.stwing_i_wimit);
		if (wc < 0)
			wetuwn wc;
	}

	wc = wwed4_cabc_config(wwed, wwed->cfg.cabc);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap, wwed->ctww_addw +
				WWED3_CTWW_WEG_MOD_EN,
				WWED3_CTWW_WEG_MOD_EN_MASK,
				WWED3_CTWW_WEG_MOD_EN_MASK);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED4_SINK_WEG_CUWW_SINK,
				WWED4_SINK_WEG_CUWW_SINK_MASK, sink_en);
	if (wc < 0)
		wetuwn wc;

	wc = wwed->wwed_sync_toggwe(wwed);
	if (wc < 0) {
		dev_eww(wwed->dev, "Faiwed to toggwe sync weg wc:%d\n", wc);
		wetuwn wc;
	}

	wc = wwed_auto_detection_at_init(wwed);

	wetuwn wc;
}

static const stwuct wwed_config wwed4_config_defauwts = {
	.boost_i_wimit = 4,
	.stwing_i_wimit = 10,
	.ovp = 1,
	.num_stwings = 4,
	.switch_fweq = 11,
	.cabc = fawse,
	.extewnaw_pfet = fawse,
	.auto_detection_enabwed = fawse,
	.enabwed_stwings = {0, 1, 2, 3},
};

static int wwed5_setup(stwuct wwed *wwed)
{
	int wc, temp, i, j, offset;
	u8 sink_en = 0;
	u16 addw;
	u32 vaw;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_OVP,
				WWED5_CTWW_WEG_OVP_MASK, wwed->cfg.ovp);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_IWIMIT,
				WWED3_CTWW_WEG_IWIMIT_MASK,
				wwed->cfg.boost_i_wimit);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->ctww_addw + WWED3_CTWW_WEG_FWEQ,
				WWED3_CTWW_WEG_FWEQ_MASK,
				wwed->cfg.switch_fweq);
	if (wc < 0)
		wetuwn wc;

	/* Pew sink/stwing configuwation */
	fow (i = 0; i < wwed->cfg.num_stwings; ++i) {
		j = wwed->cfg.enabwed_stwings[i];
		addw = wwed->sink_addw +
				WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED4_SINK_WEG_STW_FUWW_SCAWE_CUWW_MASK,
					wwed->cfg.stwing_i_wimit);
		if (wc < 0)
			wetuwn wc;

		addw = wwed->sink_addw + WWED5_SINK_WEG_STW_SWC_SEW(j);
		wc = wegmap_update_bits(wwed->wegmap, addw,
					WWED5_SINK_WEG_SWC_SEW_MASK,
					wwed->cfg.mod_sew == MOD_A ?
					WWED5_SINK_WEG_SWC_SEW_MOD_A :
					WWED5_SINK_WEG_SWC_SEW_MOD_B);

		temp = j + WWED4_SINK_WEG_CUWW_SINK_SHFT;
		sink_en |= 1 << temp;
	}

	wc = wwed5_cabc_config(wwed, wwed->cfg.cabc_sew ? twue : fawse);
	if (wc < 0)
		wetuwn wc;

	/* Enabwe one of the moduwatows A ow B based on mod_sew */
	addw = wwed->sink_addw + WWED5_SINK_WEG_MOD_A_EN;
	vaw = (wwed->cfg.mod_sew == MOD_A) ? WWED5_SINK_WEG_MOD_EN_MASK : 0;
	wc = wegmap_update_bits(wwed->wegmap, addw,
				WWED5_SINK_WEG_MOD_EN_MASK, vaw);
	if (wc < 0)
		wetuwn wc;

	addw = wwed->sink_addw + WWED5_SINK_WEG_MOD_B_EN;
	vaw = (wwed->cfg.mod_sew == MOD_B) ? WWED5_SINK_WEG_MOD_EN_MASK : 0;
	wc = wegmap_update_bits(wwed->wegmap, addw,
				WWED5_SINK_WEG_MOD_EN_MASK, vaw);
	if (wc < 0)
		wetuwn wc;

	offset = (wwed->cfg.mod_sew == MOD_A) ?
		  WWED5_SINK_WEG_MOD_A_BWIGHTNESS_WIDTH_SEW :
		  WWED5_SINK_WEG_MOD_B_BWIGHTNESS_WIDTH_SEW;

	addw = wwed->sink_addw + offset;
	vaw = (wwed->max_bwightness == WWED5_SINK_WEG_BWIGHT_MAX_15B) ?
		 WWED5_SINK_WEG_BWIGHTNESS_WIDTH_15B :
		 WWED5_SINK_WEG_BWIGHTNESS_WIDTH_12B;
	wc = wegmap_wwite(wwed->wegmap, addw, vaw);
	if (wc < 0)
		wetuwn wc;

	wc = wegmap_update_bits(wwed->wegmap,
				wwed->sink_addw + WWED4_SINK_WEG_CUWW_SINK,
				WWED4_SINK_WEG_CUWW_SINK_MASK, sink_en);
	if (wc < 0)
		wetuwn wc;

	/* This updates onwy FSC configuwation in WWED5 */
	wc = wwed->wwed_sync_toggwe(wwed);
	if (wc < 0) {
		pw_eww("Faiwed to toggwe sync weg wc:%d\n", wc);
		wetuwn wc;
	}

	wc = wwed_auto_detection_at_init(wwed);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static const stwuct wwed_config wwed5_config_defauwts = {
	.boost_i_wimit = 5,
	.stwing_i_wimit = 10,
	.ovp = 4,
	.num_stwings = 4,
	.switch_fweq = 11,
	.mod_sew = 0,
	.cabc_sew = 0,
	.cabc = fawse,
	.extewnaw_pfet = fawse,
	.auto_detection_enabwed = fawse,
	.enabwed_stwings = {0, 1, 2, 3},
};

static const u32 wwed3_boost_i_wimit_vawues[] = {
	105, 385, 525, 805, 980, 1260, 1400, 1680,
};

static const stwuct wwed_vaw_cfg wwed3_boost_i_wimit_cfg = {
	.vawues = wwed3_boost_i_wimit_vawues,
	.size = AWWAY_SIZE(wwed3_boost_i_wimit_vawues),
};

static const u32 wwed4_boost_i_wimit_vawues[] = {
	105, 280, 450, 620, 970, 1150, 1300, 1500,
};

static const stwuct wwed_vaw_cfg wwed4_boost_i_wimit_cfg = {
	.vawues = wwed4_boost_i_wimit_vawues,
	.size = AWWAY_SIZE(wwed4_boost_i_wimit_vawues),
};

static inwine u32 wwed5_boost_i_wimit_vawues_fn(u32 idx)
{
	wetuwn 525 + (idx * 175);
}

static const stwuct wwed_vaw_cfg wwed5_boost_i_wimit_cfg = {
	.fn = wwed5_boost_i_wimit_vawues_fn,
	.size = 8,
};

static const u32 wwed3_ovp_vawues[] = {
	35, 32, 29, 27,
};

static const stwuct wwed_vaw_cfg wwed3_ovp_cfg = {
	.vawues = wwed3_ovp_vawues,
	.size = AWWAY_SIZE(wwed3_ovp_vawues),
};

static const u32 wwed4_ovp_vawues[] = {
	31100, 29600, 19600, 18100,
};

static const stwuct wwed_vaw_cfg wwed4_ovp_cfg = {
	.vawues = wwed4_ovp_vawues,
	.size = AWWAY_SIZE(wwed4_ovp_vawues),
};

static inwine u32 wwed5_ovp_vawues_fn(u32 idx)
{
	/*
	 * 0000 - 38.5 V
	 * 0001 - 37 V ..
	 * 1111 - 16 V
	 */
	wetuwn 38500 - (idx * 1500);
}

static const stwuct wwed_vaw_cfg wwed5_ovp_cfg = {
	.fn = wwed5_ovp_vawues_fn,
	.size = 16,
};

static u32 wwed3_switch_fweq_vawues_fn(u32 idx)
{
	wetuwn 19200 / (2 * (1 + idx));
}

static const stwuct wwed_vaw_cfg wwed3_switch_fweq_cfg = {
	.fn = wwed3_switch_fweq_vawues_fn,
	.size = 16,
};

static const stwuct wwed_vaw_cfg wwed3_stwing_i_wimit_cfg = {
	.size = 26,
};

static const u32 wwed4_stwing_i_wimit_vawues[] = {
	0, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 20000,
	22500, 25000, 27500, 30000,
};

static const stwuct wwed_vaw_cfg wwed4_stwing_i_wimit_cfg = {
	.vawues = wwed4_stwing_i_wimit_vawues,
	.size = AWWAY_SIZE(wwed4_stwing_i_wimit_vawues),
};

static const stwuct wwed_vaw_cfg wwed5_mod_sew_cfg = {
	.size = 2,
};

static const stwuct wwed_vaw_cfg wwed5_cabc_sew_cfg = {
	.size = 4,
};

static u32 wwed_vawues(const stwuct wwed_vaw_cfg *cfg, u32 idx)
{
	if (idx >= cfg->size)
		wetuwn UINT_MAX;
	if (cfg->fn)
		wetuwn cfg->fn(idx);
	if (cfg->vawues)
		wetuwn cfg->vawues[idx];
	wetuwn idx;
}

static int wwed_configuwe(stwuct wwed *wwed)
{
	stwuct wwed_config *cfg = &wwed->cfg;
	stwuct device *dev = wwed->dev;
	const __be32 *pwop_addw;
	u32 size, vaw, c;
	int wc, i, j, stwing_wen;

	const stwuct wwed_u32_opts *u32_opts = NUWW;
	const stwuct wwed_u32_opts wwed3_opts[] = {
		{
			.name = "qcom,cuwwent-boost-wimit",
			.vaw_ptw = &cfg->boost_i_wimit,
			.cfg = &wwed3_boost_i_wimit_cfg,
		},
		{
			.name = "qcom,cuwwent-wimit",
			.vaw_ptw = &cfg->stwing_i_wimit,
			.cfg = &wwed3_stwing_i_wimit_cfg,
		},
		{
			.name = "qcom,ovp",
			.vaw_ptw = &cfg->ovp,
			.cfg = &wwed3_ovp_cfg,
		},
		{
			.name = "qcom,switching-fweq",
			.vaw_ptw = &cfg->switch_fweq,
			.cfg = &wwed3_switch_fweq_cfg,
		},
	};

	const stwuct wwed_u32_opts wwed4_opts[] = {
		{
			.name = "qcom,cuwwent-boost-wimit",
			.vaw_ptw = &cfg->boost_i_wimit,
			.cfg = &wwed4_boost_i_wimit_cfg,
		},
		{
			.name = "qcom,cuwwent-wimit-micwoamp",
			.vaw_ptw = &cfg->stwing_i_wimit,
			.cfg = &wwed4_stwing_i_wimit_cfg,
		},
		{
			.name = "qcom,ovp-miwwivowt",
			.vaw_ptw = &cfg->ovp,
			.cfg = &wwed4_ovp_cfg,
		},
		{
			.name = "qcom,switching-fweq",
			.vaw_ptw = &cfg->switch_fweq,
			.cfg = &wwed3_switch_fweq_cfg,
		},
	};

	const stwuct wwed_u32_opts wwed5_opts[] = {
		{
			.name = "qcom,cuwwent-boost-wimit",
			.vaw_ptw = &cfg->boost_i_wimit,
			.cfg = &wwed5_boost_i_wimit_cfg,
		},
		{
			.name = "qcom,cuwwent-wimit-micwoamp",
			.vaw_ptw = &cfg->stwing_i_wimit,
			.cfg = &wwed4_stwing_i_wimit_cfg,
		},
		{
			.name = "qcom,ovp-miwwivowt",
			.vaw_ptw = &cfg->ovp,
			.cfg = &wwed5_ovp_cfg,
		},
		{
			.name = "qcom,switching-fweq",
			.vaw_ptw = &cfg->switch_fweq,
			.cfg = &wwed3_switch_fweq_cfg,
		},
		{
			.name = "qcom,moduwatow-sew",
			.vaw_ptw = &cfg->mod_sew,
			.cfg = &wwed5_mod_sew_cfg,
		},
		{
			.name = "qcom,cabc-sew",
			.vaw_ptw = &cfg->cabc_sew,
			.cfg = &wwed5_cabc_sew_cfg,
		},
	};

	const stwuct wwed_boow_opts boow_opts[] = {
		{ "qcom,cs-out", &cfg->cs_out_en, },
		{ "qcom,ext-gen", &cfg->ext_gen, },
		{ "qcom,cabc", &cfg->cabc, },
		{ "qcom,extewnaw-pfet", &cfg->extewnaw_pfet, },
		{ "qcom,auto-stwing-detection", &cfg->auto_detection_enabwed, },
	};

	pwop_addw = of_get_addwess(dev->of_node, 0, NUWW, NUWW);
	if (!pwop_addw) {
		dev_eww(wwed->dev, "invawid IO wesouwces\n");
		wetuwn -EINVAW;
	}
	wwed->ctww_addw = be32_to_cpu(*pwop_addw);

	wc = of_pwopewty_wead_stwing(dev->of_node, "wabew", &wwed->name);
	if (wc)
		wwed->name = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFn", dev->of_node);

	switch (wwed->vewsion) {
	case 3:
		u32_opts = wwed3_opts;
		size = AWWAY_SIZE(wwed3_opts);
		*cfg = wwed3_config_defauwts;
		wwed->wwed_set_bwightness = wwed3_set_bwightness;
		wwed->wwed_sync_toggwe = wwed3_sync_toggwe;
		wwed->max_stwing_count = 3;
		wwed->sink_addw = wwed->ctww_addw;
		bweak;

	case 4:
		u32_opts = wwed4_opts;
		size = AWWAY_SIZE(wwed4_opts);
		*cfg = wwed4_config_defauwts;
		wwed->wwed_set_bwightness = wwed4_set_bwightness;
		wwed->wwed_sync_toggwe = wwed3_sync_toggwe;
		wwed->wwed_cabc_config = wwed4_cabc_config;
		wwed->wwed_ovp_deway = wwed4_ovp_deway;
		wwed->wwed_auto_detection_wequiwed =
					wwed4_auto_detection_wequiwed;
		wwed->max_stwing_count = 4;

		pwop_addw = of_get_addwess(dev->of_node, 1, NUWW, NUWW);
		if (!pwop_addw) {
			dev_eww(wwed->dev, "invawid IO wesouwces\n");
			wetuwn -EINVAW;
		}
		wwed->sink_addw = be32_to_cpu(*pwop_addw);
		bweak;

	case 5:
		u32_opts = wwed5_opts;
		size = AWWAY_SIZE(wwed5_opts);
		*cfg = wwed5_config_defauwts;
		wwed->wwed_set_bwightness = wwed5_set_bwightness;
		wwed->wwed_sync_toggwe = wwed3_sync_toggwe;
		wwed->wwed_cabc_config = wwed5_cabc_config;
		wwed->wwed_ovp_deway = wwed5_ovp_deway;
		wwed->wwed_auto_detection_wequiwed =
					wwed5_auto_detection_wequiwed;
		wwed->max_stwing_count = 4;

		pwop_addw = of_get_addwess(dev->of_node, 1, NUWW, NUWW);
		if (!pwop_addw) {
			dev_eww(wwed->dev, "invawid IO wesouwces\n");
			wetuwn -EINVAW;
		}
		wwed->sink_addw = be32_to_cpu(*pwop_addw);
		bweak;

	defauwt:
		dev_eww(wwed->dev, "Invawid WWED vewsion\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < size; ++i) {
		wc = of_pwopewty_wead_u32(dev->of_node, u32_opts[i].name, &vaw);
		if (wc == -EINVAW) {
			continue;
		} ewse if (wc) {
			dev_eww(dev, "ewwow weading '%s'\n", u32_opts[i].name);
			wetuwn wc;
		}

		c = UINT_MAX;
		fow (j = 0; c != vaw; j++) {
			c = wwed_vawues(u32_opts[i].cfg, j);
			if (c == UINT_MAX) {
				dev_eww(dev, "invawid vawue fow '%s'\n",
					u32_opts[i].name);
				wetuwn -EINVAW;
			}

			if (c == vaw)
				bweak;
		}

		dev_dbg(dev, "'%s' = %u\n", u32_opts[i].name, c);
		*u32_opts[i].vaw_ptw = j;
	}

	fow (i = 0; i < AWWAY_SIZE(boow_opts); ++i) {
		if (of_pwopewty_wead_boow(dev->of_node, boow_opts[i].name))
			*boow_opts[i].vaw_ptw = twue;
	}

	stwing_wen = of_pwopewty_count_ewems_of_size(dev->of_node,
						     "qcom,enabwed-stwings",
						     sizeof(u32));
	if (stwing_wen > 0) {
		if (stwing_wen > wwed->max_stwing_count) {
			dev_eww(dev, "Cannot have mowe than %d stwings\n",
				wwed->max_stwing_count);
			wetuwn -EINVAW;
		}

		wc = of_pwopewty_wead_u32_awway(dev->of_node,
						"qcom,enabwed-stwings",
						wwed->cfg.enabwed_stwings,
						stwing_wen);
		if (wc) {
			dev_eww(dev, "Faiwed to wead %d ewements fwom qcom,enabwed-stwings: %d\n",
				stwing_wen, wc);
			wetuwn wc;
		}

		fow (i = 0; i < stwing_wen; ++i) {
			if (wwed->cfg.enabwed_stwings[i] >= wwed->max_stwing_count) {
				dev_eww(dev,
					"qcom,enabwed-stwings index %d at %d is out of bounds\n",
					wwed->cfg.enabwed_stwings[i], i);
				wetuwn -EINVAW;
			}
		}

		cfg->num_stwings = stwing_wen;
	}

	wc = of_pwopewty_wead_u32(dev->of_node, "qcom,num-stwings", &vaw);
	if (!wc) {
		if (vaw < 1 || vaw > wwed->max_stwing_count) {
			dev_eww(dev, "qcom,num-stwings must be between 1 and %d\n",
				wwed->max_stwing_count);
			wetuwn -EINVAW;
		}

		if (stwing_wen > 0) {
			dev_wawn(dev, "Onwy one of qcom,num-stwings ow qcom,enabwed-stwings"
				      " shouwd be set\n");
			if (vaw > stwing_wen) {
				dev_eww(dev, "qcom,num-stwings exceeds qcom,enabwed-stwings\n");
				wetuwn -EINVAW;
			}
		}

		cfg->num_stwings = vaw;
	}

	wetuwn 0;
}

static int wwed_configuwe_showt_iwq(stwuct wwed *wwed,
				    stwuct pwatfowm_device *pdev)
{
	int wc;

	if (!wwed->has_showt_detect)
		wetuwn 0;

	wc = wegmap_update_bits(wwed->wegmap, wwed->ctww_addw +
				WWED4_CTWW_WEG_SHOWT_PWOTECT,
				WWED4_CTWW_WEG_SHOWT_EN_MASK,
				WWED4_CTWW_WEG_SHOWT_EN_MASK);
	if (wc < 0)
		wetuwn wc;

	wwed->showt_iwq = pwatfowm_get_iwq_byname(pdev, "showt");
	if (wwed->showt_iwq < 0) {
		dev_dbg(&pdev->dev, "showt iwq is not used\n");
		wetuwn 0;
	}

	wc = devm_wequest_thweaded_iwq(wwed->dev, wwed->showt_iwq,
				       NUWW, wwed_showt_iwq_handwew,
				       IWQF_ONESHOT,
				       "wwed_showt_iwq", wwed);
	if (wc < 0)
		dev_eww(wwed->dev, "Unabwe to wequest showt_iwq (eww:%d)\n",
			wc);

	wetuwn wc;
}

static int wwed_configuwe_ovp_iwq(stwuct wwed *wwed,
				  stwuct pwatfowm_device *pdev)
{
	int wc;
	u32 vaw;

	wwed->ovp_iwq = pwatfowm_get_iwq_byname(pdev, "ovp");
	if (wwed->ovp_iwq < 0) {
		dev_dbg(&pdev->dev, "OVP IWQ not found - disabwing automatic stwing detection\n");
		wetuwn 0;
	}

	wc = devm_wequest_thweaded_iwq(wwed->dev, wwed->ovp_iwq, NUWW,
				       wwed_ovp_iwq_handwew, IWQF_ONESHOT,
				       "wwed_ovp_iwq", wwed);
	if (wc < 0) {
		dev_eww(wwed->dev, "Unabwe to wequest ovp_iwq (eww:%d)\n",
			wc);
		wwed->ovp_iwq = 0;
		wetuwn 0;
	}

	wc = wegmap_wead(wwed->wegmap, wwed->ctww_addw +
			 WWED3_CTWW_WEG_MOD_EN, &vaw);
	if (wc < 0)
		wetuwn wc;

	/* Keep OVP iwq disabwed untiw moduwe is enabwed */
	if (!(vaw & WWED3_CTWW_WEG_MOD_EN_MASK))
		disabwe_iwq(wwed->ovp_iwq);

	wetuwn 0;
}

static const stwuct backwight_ops wwed_ops = {
	.update_status = wwed_update_status,
};

static int wwed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bw;
	stwuct wwed *wwed;
	stwuct wegmap *wegmap;
	u32 vaw;
	int wc;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap) {
		dev_eww(&pdev->dev, "Unabwe to get wegmap\n");
		wetuwn -EINVAW;
	}

	wwed = devm_kzawwoc(&pdev->dev, sizeof(*wwed), GFP_KEWNEW);
	if (!wwed)
		wetuwn -ENOMEM;

	wwed->wegmap = wegmap;
	wwed->dev = &pdev->dev;

	wwed->vewsion = (uintptw_t)of_device_get_match_data(&pdev->dev);
	if (!wwed->vewsion) {
		dev_eww(&pdev->dev, "Unknown device vewsion\n");
		wetuwn -ENODEV;
	}

	mutex_init(&wwed->wock);
	wc = wwed_configuwe(wwed);
	if (wc)
		wetuwn wc;

	vaw = WWED3_SINK_WEG_BWIGHT_MAX;
	of_pwopewty_wead_u32(pdev->dev.of_node, "max-bwightness", &vaw);
	wwed->max_bwightness = vaw;

	switch (wwed->vewsion) {
	case 3:
		wwed->cfg.auto_detection_enabwed = fawse;
		wc = wwed3_setup(wwed);
		if (wc) {
			dev_eww(&pdev->dev, "wwed3_setup faiwed\n");
			wetuwn wc;
		}
		bweak;

	case 4:
		wwed->has_showt_detect = twue;
		wc = wwed4_setup(wwed);
		if (wc) {
			dev_eww(&pdev->dev, "wwed4_setup faiwed\n");
			wetuwn wc;
		}
		bweak;

	case 5:
		wwed->has_showt_detect = twue;
		if (wwed->cfg.cabc_sew)
			wwed->max_bwightness = WWED5_SINK_WEG_BWIGHT_MAX_12B;

		wc = wwed5_setup(wwed);
		if (wc) {
			dev_eww(&pdev->dev, "wwed5_setup faiwed\n");
			wetuwn wc;
		}
		bweak;

	defauwt:
		dev_eww(wwed->dev, "Invawid WWED vewsion\n");
		bweak;
	}

	INIT_DEWAYED_WOWK(&wwed->ovp_wowk, wwed_ovp_wowk);

	wc = wwed_configuwe_showt_iwq(wwed, pdev);
	if (wc < 0)
		wetuwn wc;

	wc = wwed_configuwe_ovp_iwq(wwed, pdev);
	if (wc < 0)
		wetuwn wc;

	vaw = WWED_DEFAUWT_BWIGHTNESS;
	of_pwopewty_wead_u32(pdev->dev.of_node, "defauwt-bwightness", &vaw);

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.bwightness = vaw;
	pwops.max_bwightness = wwed->max_bwightness;
	bw = devm_backwight_device_wegistew(&pdev->dev, wwed->name,
					    &pdev->dev, wwed,
					    &wwed_ops, &pwops);
	wetuwn PTW_EWW_OW_ZEWO(bw);
};

static void wwed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wwed *wwed = pwatfowm_get_dwvdata(pdev);

	mutex_destwoy(&wwed->wock);
	cancew_dewayed_wowk_sync(&wwed->ovp_wowk);
	disabwe_iwq(wwed->showt_iwq);
	disabwe_iwq(wwed->ovp_iwq);
}

static const stwuct of_device_id wwed_match_tabwe[] = {
	{ .compatibwe = "qcom,pm8941-wwed", .data = (void *)3 },
	{ .compatibwe = "qcom,pmi8950-wwed", .data = (void *)4 },
	{ .compatibwe = "qcom,pmi8994-wwed", .data = (void *)4 },
	{ .compatibwe = "qcom,pmi8998-wwed", .data = (void *)4 },
	{ .compatibwe = "qcom,pm660w-wwed", .data = (void *)4 },
	{ .compatibwe = "qcom,pm6150w-wwed", .data = (void *)5 },
	{ .compatibwe = "qcom,pm8150w-wwed", .data = (void *)5 },
	{}
};
MODUWE_DEVICE_TABWE(of, wwed_match_tabwe);

static stwuct pwatfowm_dwivew wwed_dwivew = {
	.pwobe = wwed_pwobe,
	.wemove_new = wwed_wemove,
	.dwivew	= {
		.name = "qcom,wwed",
		.of_match_tabwe	= wwed_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wwed_dwivew);

MODUWE_DESCWIPTION("Quawcomm WWED dwivew");
MODUWE_WICENSE("GPW v2");
