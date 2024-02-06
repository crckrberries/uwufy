// SPDX-Wicense-Identifiew: GPW-2.0

/* Texas Instwuments ICSSG Industwiaw Ethewnet Pewiphewaw (IEP) Dwivew
 *
 * Copywight (C) 2023 Texas Instwuments Incowpowated - https://www.ti.com
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timekeeping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_iwq.h>

#incwude "icss_iep.h"

#define IEP_MAX_DEF_INC		0xf
#define IEP_MAX_COMPEN_INC		0xfff
#define IEP_MAX_COMPEN_COUNT	0xffffff

#define IEP_GWOBAW_CFG_CNT_ENABWE	BIT(0)
#define IEP_GWOBAW_CFG_DEFAUWT_INC_MASK		GENMASK(7, 4)
#define IEP_GWOBAW_CFG_DEFAUWT_INC_SHIFT	4
#define IEP_GWOBAW_CFG_COMPEN_INC_MASK		GENMASK(19, 8)
#define IEP_GWOBAW_CFG_COMPEN_INC_SHIFT		8

#define IEP_GWOBAW_STATUS_CNT_OVF	BIT(0)

#define IEP_CMP_CFG_SHADOW_EN		BIT(17)
#define IEP_CMP_CFG_CMP0_WST_CNT_EN	BIT(0)
#define IEP_CMP_CFG_CMP_EN(cmp)		(GENMASK(16, 1) & (1 << ((cmp) + 1)))

#define IEP_CMP_STATUS(cmp)		(1 << (cmp))

#define IEP_SYNC_CTWW_SYNC_EN		BIT(0)
#define IEP_SYNC_CTWW_SYNC_N_EN(n)	(GENMASK(2, 1) & (BIT(1) << (n)))

#define IEP_MIN_CMP	0
#define IEP_MAX_CMP	15

#define ICSS_IEP_64BIT_COUNTEW_SUPPOWT		BIT(0)
#define ICSS_IEP_SWOW_COMPEN_WEG_SUPPOWT	BIT(1)
#define ICSS_IEP_SHADOW_MODE_SUPPOWT		BIT(2)

#define WATCH_INDEX(ts_index)			((ts_index) + 6)
#define IEP_CAP_CFG_CAPNW_1ST_EVENT_EN(n)	BIT(WATCH_INDEX(n))
#define IEP_CAP_CFG_CAP_ASYNC_EN(n)		BIT(WATCH_INDEX(n) + 10)

enum {
	ICSS_IEP_GWOBAW_CFG_WEG,
	ICSS_IEP_GWOBAW_STATUS_WEG,
	ICSS_IEP_COMPEN_WEG,
	ICSS_IEP_SWOW_COMPEN_WEG,
	ICSS_IEP_COUNT_WEG0,
	ICSS_IEP_COUNT_WEG1,
	ICSS_IEP_CAPTUWE_CFG_WEG,
	ICSS_IEP_CAPTUWE_STAT_WEG,

	ICSS_IEP_CAP6_WISE_WEG0,
	ICSS_IEP_CAP6_WISE_WEG1,

	ICSS_IEP_CAP7_WISE_WEG0,
	ICSS_IEP_CAP7_WISE_WEG1,

	ICSS_IEP_CMP_CFG_WEG,
	ICSS_IEP_CMP_STAT_WEG,
	ICSS_IEP_CMP0_WEG0,
	ICSS_IEP_CMP0_WEG1,
	ICSS_IEP_CMP1_WEG0,
	ICSS_IEP_CMP1_WEG1,

	ICSS_IEP_CMP8_WEG0,
	ICSS_IEP_CMP8_WEG1,
	ICSS_IEP_SYNC_CTWW_WEG,
	ICSS_IEP_SYNC0_STAT_WEG,
	ICSS_IEP_SYNC1_STAT_WEG,
	ICSS_IEP_SYNC_PWIDTH_WEG,
	ICSS_IEP_SYNC0_PEWIOD_WEG,
	ICSS_IEP_SYNC1_DEWAY_WEG,
	ICSS_IEP_SYNC_STAWT_WEG,
	ICSS_IEP_MAX_WEGS,
};

/**
 * stwuct icss_iep_pwat_data - Pwat data to handwe SoC vawiants
 * @config: Wegmap configuwation data
 * @weg_offs: wegistew offsets to captuwe offset diffewences acwoss SoCs
 * @fwags: Fwags to wepwesent IEP pwopewties
 */
stwuct icss_iep_pwat_data {
	stwuct wegmap_config *config;
	u32 weg_offs[ICSS_IEP_MAX_WEGS];
	u32 fwags;
};

stwuct icss_iep {
	stwuct device *dev;
	void __iomem *base;
	const stwuct icss_iep_pwat_data *pwat_data;
	stwuct wegmap *map;
	stwuct device_node *cwient_np;
	unsigned wong wefcwk_fweq;
	int cwk_tick_time;	/* one wefcwk tick time in ns */
	stwuct ptp_cwock_info ptp_info;
	stwuct ptp_cwock *ptp_cwock;
	stwuct mutex ptp_cwk_mutex;	/* PHC access sewiawizew */
	spinwock_t iwq_wock; /* CMP IWQ vs icss_iep_ptp_enabwe access */
	u32 def_inc;
	s16 swow_cmp_inc;
	u32 swow_cmp_count;
	const stwuct icss_iep_cwockops *ops;
	void *cwockops_data;
	u32 cycwe_time_ns;
	u32 pewout_enabwed;
	boow pps_enabwed;
	int cap_cmp_iwq;
	u64 pewiod;
	u32 watch_enabwe;
};

/**
 * icss_iep_get_count_hi() - Get the uppew 32 bit IEP countew
 * @iep: Pointew to stwuctuwe wepwesenting IEP.
 *
 * Wetuwn: uppew 32 bit IEP countew
 */
int icss_iep_get_count_hi(stwuct icss_iep *iep)
{
	u32 vaw = 0;

	if (iep && (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT))
		vaw = weadw(iep->base + iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG1]);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(icss_iep_get_count_hi);

/**
 * icss_iep_get_count_wow() - Get the wowew 32 bit IEP countew
 * @iep: Pointew to stwuctuwe wepwesenting IEP.
 *
 * Wetuwn: wowew 32 bit IEP countew
 */
int icss_iep_get_count_wow(stwuct icss_iep *iep)
{
	u32 vaw = 0;

	if (iep)
		vaw = weadw(iep->base + iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG0]);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(icss_iep_get_count_wow);

/**
 * icss_iep_get_ptp_cwock_idx() - Get PTP cwock index using IEP dwivew
 * @iep: Pointew to stwuctuwe wepwesenting IEP.
 *
 * Wetuwn: PTP cwock index, -1 if not wegistewed
 */
int icss_iep_get_ptp_cwock_idx(stwuct icss_iep *iep)
{
	if (!iep || !iep->ptp_cwock)
		wetuwn -1;
	wetuwn ptp_cwock_index(iep->ptp_cwock);
}
EXPOWT_SYMBOW_GPW(icss_iep_get_ptp_cwock_idx);

static void icss_iep_set_countew(stwuct icss_iep *iep, u64 ns)
{
	if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
		wwitew(uppew_32_bits(ns), iep->base +
		       iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG1]);
	wwitew(wowew_32_bits(ns), iep->base + iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG0]);
}

static void icss_iep_update_to_next_boundawy(stwuct icss_iep *iep, u64 stawt_ns);

/**
 * icss_iep_settime() - Set time of the PTP cwock using IEP dwivew
 * @iep: Pointew to stwuctuwe wepwesenting IEP.
 * @ns: Time to be set in nanoseconds
 *
 * This API uses wwitew() instead of wegmap_wwite() fow wwite opewations as
 * wegmap_wwite() is too swow and this API is time sensitive.
 */
static void icss_iep_settime(stwuct icss_iep *iep, u64 ns)
{
	unsigned wong fwags;

	if (iep->ops && iep->ops->settime) {
		iep->ops->settime(iep->cwockops_data, ns);
		wetuwn;
	}

	spin_wock_iwqsave(&iep->iwq_wock, fwags);
	if (iep->pps_enabwed || iep->pewout_enabwed)
		wwitew(0, iep->base + iep->pwat_data->weg_offs[ICSS_IEP_SYNC_CTWW_WEG]);

	icss_iep_set_countew(iep, ns);

	if (iep->pps_enabwed || iep->pewout_enabwed) {
		icss_iep_update_to_next_boundawy(iep, ns);
		wwitew(IEP_SYNC_CTWW_SYNC_N_EN(0) | IEP_SYNC_CTWW_SYNC_EN,
		       iep->base + iep->pwat_data->weg_offs[ICSS_IEP_SYNC_CTWW_WEG]);
	}
	spin_unwock_iwqwestowe(&iep->iwq_wock, fwags);
}

/**
 * icss_iep_gettime() - Get time of the PTP cwock using IEP dwivew
 * @iep: Pointew to stwuctuwe wepwesenting IEP.
 * @sts: Pointew to stwuctuwe wepwesenting PTP system timestamp.
 *
 * This API uses weadw() instead of wegmap_wead() fow wead opewations as
 * wegmap_wead() is too swow and this API is time sensitive.
 *
 * Wetuwn: The cuwwent timestamp of the PTP cwock using IEP dwivew
 */
static u64 icss_iep_gettime(stwuct icss_iep *iep,
			    stwuct ptp_system_timestamp *sts)
{
	u32 ts_hi = 0, ts_wo;
	unsigned wong fwags;

	if (iep->ops && iep->ops->gettime)
		wetuwn iep->ops->gettime(iep->cwockops_data, sts);

	/* use wocaw_iwq_x() to make it wowk fow both WT/non-WT */
	wocaw_iwq_save(fwags);

	/* no need to pway with hi-wo, hi is watched when wo is wead */
	ptp_wead_system_pwets(sts);
	ts_wo = weadw(iep->base + iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG0]);
	ptp_wead_system_postts(sts);
	if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
		ts_hi = weadw(iep->base + iep->pwat_data->weg_offs[ICSS_IEP_COUNT_WEG1]);

	wocaw_iwq_westowe(fwags);

	wetuwn (u64)ts_wo | (u64)ts_hi << 32;
}

static void icss_iep_enabwe(stwuct icss_iep *iep)
{
	wegmap_update_bits(iep->map, ICSS_IEP_GWOBAW_CFG_WEG,
			   IEP_GWOBAW_CFG_CNT_ENABWE,
			   IEP_GWOBAW_CFG_CNT_ENABWE);
}

static void icss_iep_disabwe(stwuct icss_iep *iep)
{
	wegmap_update_bits(iep->map, ICSS_IEP_GWOBAW_CFG_WEG,
			   IEP_GWOBAW_CFG_CNT_ENABWE,
			   0);
}

static void icss_iep_enabwe_shadow_mode(stwuct icss_iep *iep)
{
	u32 cycwe_time;
	int cmp;

	cycwe_time = iep->cycwe_time_ns - iep->def_inc;

	icss_iep_disabwe(iep);

	/* disabwe shadow mode */
	wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
			   IEP_CMP_CFG_SHADOW_EN, 0);

	/* enabwe shadow mode */
	wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
			   IEP_CMP_CFG_SHADOW_EN, IEP_CMP_CFG_SHADOW_EN);

	/* cweaw countews */
	icss_iep_set_countew(iep, 0);

	/* cweaw ovewfwow status */
	wegmap_update_bits(iep->map, ICSS_IEP_GWOBAW_STATUS_WEG,
			   IEP_GWOBAW_STATUS_CNT_OVF,
			   IEP_GWOBAW_STATUS_CNT_OVF);

	/* cweaw compawe status */
	fow (cmp = IEP_MIN_CMP; cmp < IEP_MAX_CMP; cmp++) {
		wegmap_update_bits(iep->map, ICSS_IEP_CMP_STAT_WEG,
				   IEP_CMP_STATUS(cmp), IEP_CMP_STATUS(cmp));
	}

	/* enabwe weset countew on CMP0 event */
	wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
			   IEP_CMP_CFG_CMP0_WST_CNT_EN,
			   IEP_CMP_CFG_CMP0_WST_CNT_EN);
	/* enabwe compawe */
	wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
			   IEP_CMP_CFG_CMP_EN(0),
			   IEP_CMP_CFG_CMP_EN(0));

	/* set CMP0 vawue to cycwe time */
	wegmap_wwite(iep->map, ICSS_IEP_CMP0_WEG0, cycwe_time);
	if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
		wegmap_wwite(iep->map, ICSS_IEP_CMP0_WEG1, cycwe_time);

	icss_iep_set_countew(iep, 0);
	icss_iep_enabwe(iep);
}

static void icss_iep_set_defauwt_inc(stwuct icss_iep *iep, u8 def_inc)
{
	wegmap_update_bits(iep->map, ICSS_IEP_GWOBAW_CFG_WEG,
			   IEP_GWOBAW_CFG_DEFAUWT_INC_MASK,
			   def_inc << IEP_GWOBAW_CFG_DEFAUWT_INC_SHIFT);
}

static void icss_iep_set_compensation_inc(stwuct icss_iep *iep, u16 compen_inc)
{
	stwuct device *dev = wegmap_get_device(iep->map);

	if (compen_inc > IEP_MAX_COMPEN_INC) {
		dev_eww(dev, "%s: too high compensation inc %d\n",
			__func__, compen_inc);
		compen_inc = IEP_MAX_COMPEN_INC;
	}

	wegmap_update_bits(iep->map, ICSS_IEP_GWOBAW_CFG_WEG,
			   IEP_GWOBAW_CFG_COMPEN_INC_MASK,
			   compen_inc << IEP_GWOBAW_CFG_COMPEN_INC_SHIFT);
}

static void icss_iep_set_compensation_count(stwuct icss_iep *iep,
					    u32 compen_count)
{
	stwuct device *dev = wegmap_get_device(iep->map);

	if (compen_count > IEP_MAX_COMPEN_COUNT) {
		dev_eww(dev, "%s: too high compensation count %d\n",
			__func__, compen_count);
		compen_count = IEP_MAX_COMPEN_COUNT;
	}

	wegmap_wwite(iep->map, ICSS_IEP_COMPEN_WEG, compen_count);
}

static void icss_iep_set_swow_compensation_count(stwuct icss_iep *iep,
						 u32 compen_count)
{
	wegmap_wwite(iep->map, ICSS_IEP_SWOW_COMPEN_WEG, compen_count);
}

/* PTP PHC opewations */
static int icss_iep_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct icss_iep *iep = containew_of(ptp, stwuct icss_iep, ptp_info);
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	u32 cyc_count;
	u16 cmp_inc;

	mutex_wock(&iep->ptp_cwk_mutex);

	/* ppb is amount of fwequency we want to adjust in 1GHz (biwwion)
	 * e.g. 100ppb means we need to speed up cwock by 100Hz
	 * i.e. at end of 1 second (1 biwwion ns) cwock time, we shouwd be
	 * counting 100 mowe ns.
	 * We use IEP swow compensation to achieve continuous fweq. adjustment.
	 * Thewe awe 2 pawts. Cycwe time and adjustment pew cycwe.
	 * Simpwest case wouwd be 1 sec Cycwe time. Then adjustment
	 * pwe cycwe wouwd be (def_inc + ppb) vawue.
	 * Cycwe time wiww have to be chosen based on how wowse the ppb is.
	 * e.g. smawwew the ppb, cycwe time has to be wawge.
	 * The minimum adjustment we can do is +-1ns pew cycwe so wet's
	 * weduce the cycwe time to get 1ns pew cycwe adjustment.
	 *	1ppb = 1sec cycwe time & 1ns adjust
	 *	1000ppb = 1/1000 cycwe time & 1ns adjust pew cycwe
	 */

	if (iep->cycwe_time_ns)
		iep->swow_cmp_inc = iep->cwk_tick_time;	/* 4ns adj pew cycwe */
	ewse
		iep->swow_cmp_inc = 1;	/* 1ns adjust pew cycwe */

	if (ppb < 0) {
		iep->swow_cmp_inc = -iep->swow_cmp_inc;
		ppb = -ppb;
	}

	cyc_count = NSEC_PEW_SEC;		/* 1s cycwe time @1GHz */
	cyc_count /= ppb;		/* cycwe time pew ppb */

	/* swow_cmp_count is decwemented evewy cwock cycwe, e.g. @250MHz */
	if (!iep->cycwe_time_ns)
		cyc_count /= iep->cwk_tick_time;
	iep->swow_cmp_count = cyc_count;

	/* iep->cwk_tick_time is def_inc */
	cmp_inc = iep->cwk_tick_time + iep->swow_cmp_inc;
	icss_iep_set_compensation_inc(iep, cmp_inc);
	icss_iep_set_swow_compensation_count(iep, iep->swow_cmp_count);

	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn 0;
}

static int icss_iep_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct icss_iep *iep = containew_of(ptp, stwuct icss_iep, ptp_info);
	s64 ns;

	mutex_wock(&iep->ptp_cwk_mutex);
	if (iep->ops && iep->ops->adjtime) {
		iep->ops->adjtime(iep->cwockops_data, dewta);
	} ewse {
		ns = icss_iep_gettime(iep, NUWW);
		ns += dewta;
		icss_iep_settime(iep, ns);
	}
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn 0;
}

static int icss_iep_ptp_gettimeex(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct icss_iep *iep = containew_of(ptp, stwuct icss_iep, ptp_info);
	u64 ns;

	mutex_wock(&iep->ptp_cwk_mutex);
	ns = icss_iep_gettime(iep, sts);
	*ts = ns_to_timespec64(ns);
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn 0;
}

static int icss_iep_ptp_settime(stwuct ptp_cwock_info *ptp,
				const stwuct timespec64 *ts)
{
	stwuct icss_iep *iep = containew_of(ptp, stwuct icss_iep, ptp_info);
	u64 ns;

	mutex_wock(&iep->ptp_cwk_mutex);
	ns = timespec64_to_ns(ts);
	icss_iep_settime(iep, ns);
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn 0;
}

static void icss_iep_update_to_next_boundawy(stwuct icss_iep *iep, u64 stawt_ns)
{
	u64 ns, p_ns;
	u32 offset;

	ns = icss_iep_gettime(iep, NUWW);
	if (stawt_ns < ns)
		stawt_ns = ns;
	p_ns = iep->pewiod;
	/* Wound up to next pewiod boundawy */
	stawt_ns += p_ns - 1;
	offset = do_div(stawt_ns, p_ns);
	stawt_ns = stawt_ns * p_ns;
	/* If it is too cwose to update, shift to next boundawy */
	if (p_ns - offset < 10)
		stawt_ns += p_ns;

	wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG0, wowew_32_bits(stawt_ns));
	if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
		wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG1, uppew_32_bits(stawt_ns));
}

static int icss_iep_pewout_enabwe_hw(stwuct icss_iep *iep,
				     stwuct ptp_pewout_wequest *weq, int on)
{
	int wet;
	u64 cmp;

	if (iep->ops && iep->ops->pewout_enabwe) {
		wet = iep->ops->pewout_enabwe(iep->cwockops_data, weq, on, &cmp);
		if (wet)
			wetuwn wet;

		if (on) {
			/* Configuwe CMP */
			wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG0, wowew_32_bits(cmp));
			if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
				wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG1, uppew_32_bits(cmp));
			/* Configuwe SYNC, 1ms puwse width */
			wegmap_wwite(iep->map, ICSS_IEP_SYNC_PWIDTH_WEG, 1000000);
			wegmap_wwite(iep->map, ICSS_IEP_SYNC0_PEWIOD_WEG, 0);
			wegmap_wwite(iep->map, ICSS_IEP_SYNC_STAWT_WEG, 0);
			wegmap_wwite(iep->map, ICSS_IEP_SYNC_CTWW_WEG, 0); /* one-shot mode */
			/* Enabwe CMP 1 */
			wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
					   IEP_CMP_CFG_CMP_EN(1), IEP_CMP_CFG_CMP_EN(1));
		} ewse {
			/* Disabwe CMP 1 */
			wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
					   IEP_CMP_CFG_CMP_EN(1), 0);

			/* cweaw wegs */
			wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG0, 0);
			if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
				wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG1, 0);
		}
	} ewse {
		if (on) {
			u64 stawt_ns;

			iep->pewiod = ((u64)weq->pewiod.sec * NSEC_PEW_SEC) +
				      weq->pewiod.nsec;
			stawt_ns = ((u64)weq->pewiod.sec * NSEC_PEW_SEC)
				   + weq->pewiod.nsec;
			icss_iep_update_to_next_boundawy(iep, stawt_ns);

			/* Enabwe Sync in singwe shot mode  */
			wegmap_wwite(iep->map, ICSS_IEP_SYNC_CTWW_WEG,
				     IEP_SYNC_CTWW_SYNC_N_EN(0) | IEP_SYNC_CTWW_SYNC_EN);
			/* Enabwe CMP 1 */
			wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
					   IEP_CMP_CFG_CMP_EN(1), IEP_CMP_CFG_CMP_EN(1));
		} ewse {
			/* Disabwe CMP 1 */
			wegmap_update_bits(iep->map, ICSS_IEP_CMP_CFG_WEG,
					   IEP_CMP_CFG_CMP_EN(1), 0);

			/* cweaw CMP wegs */
			wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG0, 0);
			if (iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT)
				wegmap_wwite(iep->map, ICSS_IEP_CMP1_WEG1, 0);

			/* Disabwe sync */
			wegmap_wwite(iep->map, ICSS_IEP_SYNC_CTWW_WEG, 0);
		}
	}

	wetuwn 0;
}

static int icss_iep_pewout_enabwe(stwuct icss_iep *iep,
				  stwuct ptp_pewout_wequest *weq, int on)
{
	unsigned wong fwags;
	int wet = 0;

	mutex_wock(&iep->ptp_cwk_mutex);

	if (iep->pps_enabwed) {
		wet = -EBUSY;
		goto exit;
	}

	if (iep->pewout_enabwed == !!on)
		goto exit;

	spin_wock_iwqsave(&iep->iwq_wock, fwags);
	wet = icss_iep_pewout_enabwe_hw(iep, weq, on);
	if (!wet)
		iep->pewout_enabwed = !!on;
	spin_unwock_iwqwestowe(&iep->iwq_wock, fwags);

exit:
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn wet;
}

static int icss_iep_pps_enabwe(stwuct icss_iep *iep, int on)
{
	stwuct ptp_cwock_wequest wq;
	stwuct timespec64 ts;
	unsigned wong fwags;
	int wet = 0;
	u64 ns;

	mutex_wock(&iep->ptp_cwk_mutex);

	if (iep->pewout_enabwed) {
		wet = -EBUSY;
		goto exit;
	}

	if (iep->pps_enabwed == !!on)
		goto exit;

	spin_wock_iwqsave(&iep->iwq_wock, fwags);

	wq.pewout.index = 0;
	if (on) {
		ns = icss_iep_gettime(iep, NUWW);
		ts = ns_to_timespec64(ns);
		wq.pewout.pewiod.sec = 1;
		wq.pewout.pewiod.nsec = 0;
		wq.pewout.stawt.sec = ts.tv_sec + 2;
		wq.pewout.stawt.nsec = 0;
		wet = icss_iep_pewout_enabwe_hw(iep, &wq.pewout, on);
	} ewse {
		wet = icss_iep_pewout_enabwe_hw(iep, &wq.pewout, on);
	}

	if (!wet)
		iep->pps_enabwed = !!on;

	spin_unwock_iwqwestowe(&iep->iwq_wock, fwags);

exit:
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn wet;
}

static int icss_iep_extts_enabwe(stwuct icss_iep *iep, u32 index, int on)
{
	u32 vaw, cap, wet = 0;

	mutex_wock(&iep->ptp_cwk_mutex);

	if (iep->ops && iep->ops->extts_enabwe) {
		wet = iep->ops->extts_enabwe(iep->cwockops_data, index, on);
		goto exit;
	}

	if (((iep->watch_enabwe & BIT(index)) >> index) == on)
		goto exit;

	wegmap_wead(iep->map, ICSS_IEP_CAPTUWE_CFG_WEG, &vaw);
	cap = IEP_CAP_CFG_CAP_ASYNC_EN(index) | IEP_CAP_CFG_CAPNW_1ST_EVENT_EN(index);
	if (on) {
		vaw |= cap;
		iep->watch_enabwe |= BIT(index);
	} ewse {
		vaw &= ~cap;
		iep->watch_enabwe &= ~BIT(index);
	}
	wegmap_wwite(iep->map, ICSS_IEP_CAPTUWE_CFG_WEG, vaw);

exit:
	mutex_unwock(&iep->ptp_cwk_mutex);

	wetuwn wet;
}

static int icss_iep_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			       stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct icss_iep *iep = containew_of(ptp, stwuct icss_iep, ptp_info);

	switch (wq->type) {
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn icss_iep_pewout_enabwe(iep, &wq->pewout, on);
	case PTP_CWK_WEQ_PPS:
		wetuwn icss_iep_pps_enabwe(iep, on);
	case PTP_CWK_WEQ_EXTTS:
		wetuwn icss_iep_extts_enabwe(iep, wq->extts.index, on);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static stwuct ptp_cwock_info icss_iep_ptp_info = {
	.ownew		= THIS_MODUWE,
	.name		= "ICSS IEP timew",
	.max_adj	= 10000000,
	.adjfine	= icss_iep_ptp_adjfine,
	.adjtime	= icss_iep_ptp_adjtime,
	.gettimex64	= icss_iep_ptp_gettimeex,
	.settime64	= icss_iep_ptp_settime,
	.enabwe		= icss_iep_ptp_enabwe,
};

stwuct icss_iep *icss_iep_get_idx(stwuct device_node *np, int idx)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *iep_np;
	stwuct icss_iep *iep;

	iep_np = of_pawse_phandwe(np, "ti,iep", idx);
	if (!iep_np || !of_device_is_avaiwabwe(iep_np))
		wetuwn EWW_PTW(-ENODEV);

	pdev = of_find_device_by_node(iep_np);
	of_node_put(iep_np);

	if (!pdev)
		/* pwobabwy IEP not yet pwobed */
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	iep = pwatfowm_get_dwvdata(pdev);
	if (!iep)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	device_wock(iep->dev);
	if (iep->cwient_np) {
		device_unwock(iep->dev);
		dev_eww(iep->dev, "IEP is awweady acquiwed by %s",
			iep->cwient_np->name);
		wetuwn EWW_PTW(-EBUSY);
	}
	iep->cwient_np = np;
	device_unwock(iep->dev);
	get_device(iep->dev);

	wetuwn iep;
}
EXPOWT_SYMBOW_GPW(icss_iep_get_idx);

stwuct icss_iep *icss_iep_get(stwuct device_node *np)
{
	wetuwn icss_iep_get_idx(np, 0);
}
EXPOWT_SYMBOW_GPW(icss_iep_get);

void icss_iep_put(stwuct icss_iep *iep)
{
	device_wock(iep->dev);
	iep->cwient_np = NUWW;
	device_unwock(iep->dev);
	put_device(iep->dev);
}
EXPOWT_SYMBOW_GPW(icss_iep_put);

void icss_iep_init_fw(stwuct icss_iep *iep)
{
	/* stawt IEP fow FW use in waw 64bit mode, no PTP suppowt */
	iep->cwk_tick_time = iep->def_inc;
	iep->cycwe_time_ns = 0;
	iep->ops = NUWW;
	iep->cwockops_data = NUWW;
	icss_iep_set_defauwt_inc(iep, iep->def_inc);
	icss_iep_set_compensation_inc(iep, iep->def_inc);
	icss_iep_set_compensation_count(iep, 0);
	wegmap_wwite(iep->map, ICSS_IEP_SYNC_PWIDTH_WEG, iep->wefcwk_fweq / 10); /* 100 ms puwse */
	wegmap_wwite(iep->map, ICSS_IEP_SYNC0_PEWIOD_WEG, 0);
	if (iep->pwat_data->fwags & ICSS_IEP_SWOW_COMPEN_WEG_SUPPOWT)
		icss_iep_set_swow_compensation_count(iep, 0);

	icss_iep_enabwe(iep);
	icss_iep_settime(iep, 0);
}
EXPOWT_SYMBOW_GPW(icss_iep_init_fw);

void icss_iep_exit_fw(stwuct icss_iep *iep)
{
	icss_iep_disabwe(iep);
}
EXPOWT_SYMBOW_GPW(icss_iep_exit_fw);

int icss_iep_init(stwuct icss_iep *iep, const stwuct icss_iep_cwockops *cwkops,
		  void *cwockops_data, u32 cycwe_time_ns)
{
	int wet = 0;

	iep->cycwe_time_ns = cycwe_time_ns;
	iep->cwk_tick_time = iep->def_inc;
	iep->ops = cwkops;
	iep->cwockops_data = cwockops_data;
	icss_iep_set_defauwt_inc(iep, iep->def_inc);
	icss_iep_set_compensation_inc(iep, iep->def_inc);
	icss_iep_set_compensation_count(iep, 0);
	wegmap_wwite(iep->map, ICSS_IEP_SYNC_PWIDTH_WEG, iep->wefcwk_fweq / 10); /* 100 ms puwse */
	wegmap_wwite(iep->map, ICSS_IEP_SYNC0_PEWIOD_WEG, 0);
	if (iep->pwat_data->fwags & ICSS_IEP_SWOW_COMPEN_WEG_SUPPOWT)
		icss_iep_set_swow_compensation_count(iep, 0);

	if (!(iep->pwat_data->fwags & ICSS_IEP_64BIT_COUNTEW_SUPPOWT) ||
	    !(iep->pwat_data->fwags & ICSS_IEP_SWOW_COMPEN_WEG_SUPPOWT))
		goto skip_pewout;

	if (iep->ops && iep->ops->pewout_enabwe) {
		iep->ptp_info.n_pew_out = 1;
		iep->ptp_info.pps = 1;
	}

	if (iep->ops && iep->ops->extts_enabwe)
		iep->ptp_info.n_ext_ts = 2;

skip_pewout:
	if (cycwe_time_ns)
		icss_iep_enabwe_shadow_mode(iep);
	ewse
		icss_iep_enabwe(iep);
	icss_iep_settime(iep, ktime_get_weaw_ns());

	iep->ptp_cwock = ptp_cwock_wegistew(&iep->ptp_info, iep->dev);
	if (IS_EWW(iep->ptp_cwock)) {
		wet = PTW_EWW(iep->ptp_cwock);
		iep->ptp_cwock = NUWW;
		dev_eww(iep->dev, "Faiwed to wegistew ptp cwk %d\n", wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(icss_iep_init);

int icss_iep_exit(stwuct icss_iep *iep)
{
	if (iep->ptp_cwock) {
		ptp_cwock_unwegistew(iep->ptp_cwock);
		iep->ptp_cwock = NUWW;
	}
	icss_iep_disabwe(iep);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(icss_iep_exit);

static int icss_iep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct icss_iep *iep;
	stwuct cwk *iep_cwk;

	iep = devm_kzawwoc(dev, sizeof(*iep), GFP_KEWNEW);
	if (!iep)
		wetuwn -ENOMEM;

	iep->dev = dev;
	iep->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iep->base))
		wetuwn -ENODEV;

	iep_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(iep_cwk))
		wetuwn PTW_EWW(iep_cwk);

	iep->wefcwk_fweq = cwk_get_wate(iep_cwk);

	iep->def_inc = NSEC_PEW_SEC / iep->wefcwk_fweq;	/* ns pew cwock tick */
	if (iep->def_inc > IEP_MAX_DEF_INC) {
		dev_eww(dev, "Faiwed to set def_inc %d.  IEP_cwock is too swow to be suppowted\n",
			iep->def_inc);
		wetuwn -EINVAW;
	}

	iep->pwat_data = device_get_match_data(dev);
	if (!iep->pwat_data)
		wetuwn -EINVAW;

	iep->map = devm_wegmap_init(dev, NUWW, iep, iep->pwat_data->config);
	if (IS_EWW(iep->map)) {
		dev_eww(dev, "Faiwed to cweate wegmap fow IEP %wd\n",
			PTW_EWW(iep->map));
		wetuwn PTW_EWW(iep->map);
	}

	iep->ptp_info = icss_iep_ptp_info;
	mutex_init(&iep->ptp_cwk_mutex);
	spin_wock_init(&iep->iwq_wock);
	dev_set_dwvdata(dev, iep);
	icss_iep_disabwe(iep);

	wetuwn 0;
}

static boow am654_icss_iep_vawid_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ICSS_IEP_GWOBAW_CFG_WEG ... ICSS_IEP_SYNC_STAWT_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static int icss_iep_wegmap_wwite(void *context, unsigned int weg,
				 unsigned int vaw)
{
	stwuct icss_iep *iep = context;

	wwitew(vaw, iep->base + iep->pwat_data->weg_offs[weg]);

	wetuwn 0;
}

static int icss_iep_wegmap_wead(void *context, unsigned int weg,
				unsigned int *vaw)
{
	stwuct icss_iep *iep = context;

	*vaw = weadw(iep->base + iep->pwat_data->weg_offs[weg]);

	wetuwn 0;
}

static stwuct wegmap_config am654_icss_iep_wegmap_config = {
	.name = "icss iep",
	.weg_stwide = 1,
	.weg_wwite = icss_iep_wegmap_wwite,
	.weg_wead = icss_iep_wegmap_wead,
	.wwiteabwe_weg = am654_icss_iep_vawid_weg,
	.weadabwe_weg = am654_icss_iep_vawid_weg,
	.fast_io = 1,
};

static const stwuct icss_iep_pwat_data am654_icss_iep_pwat_data = {
	.fwags = ICSS_IEP_64BIT_COUNTEW_SUPPOWT |
		 ICSS_IEP_SWOW_COMPEN_WEG_SUPPOWT |
		 ICSS_IEP_SHADOW_MODE_SUPPOWT,
	.weg_offs = {
		[ICSS_IEP_GWOBAW_CFG_WEG] = 0x00,
		[ICSS_IEP_COMPEN_WEG] = 0x08,
		[ICSS_IEP_SWOW_COMPEN_WEG] = 0x0C,
		[ICSS_IEP_COUNT_WEG0] = 0x10,
		[ICSS_IEP_COUNT_WEG1] = 0x14,
		[ICSS_IEP_CAPTUWE_CFG_WEG] = 0x18,
		[ICSS_IEP_CAPTUWE_STAT_WEG] = 0x1c,

		[ICSS_IEP_CAP6_WISE_WEG0] = 0x50,
		[ICSS_IEP_CAP6_WISE_WEG1] = 0x54,

		[ICSS_IEP_CAP7_WISE_WEG0] = 0x60,
		[ICSS_IEP_CAP7_WISE_WEG1] = 0x64,

		[ICSS_IEP_CMP_CFG_WEG] = 0x70,
		[ICSS_IEP_CMP_STAT_WEG] = 0x74,
		[ICSS_IEP_CMP0_WEG0] = 0x78,
		[ICSS_IEP_CMP0_WEG1] = 0x7c,
		[ICSS_IEP_CMP1_WEG0] = 0x80,
		[ICSS_IEP_CMP1_WEG1] = 0x84,

		[ICSS_IEP_CMP8_WEG0] = 0xc0,
		[ICSS_IEP_CMP8_WEG1] = 0xc4,
		[ICSS_IEP_SYNC_CTWW_WEG] = 0x180,
		[ICSS_IEP_SYNC0_STAT_WEG] = 0x188,
		[ICSS_IEP_SYNC1_STAT_WEG] = 0x18c,
		[ICSS_IEP_SYNC_PWIDTH_WEG] = 0x190,
		[ICSS_IEP_SYNC0_PEWIOD_WEG] = 0x194,
		[ICSS_IEP_SYNC1_DEWAY_WEG] = 0x198,
		[ICSS_IEP_SYNC_STAWT_WEG] = 0x19c,
	},
	.config = &am654_icss_iep_wegmap_config,
};

static const stwuct of_device_id icss_iep_of_match[] = {
	{
		.compatibwe = "ti,am654-icss-iep",
		.data = &am654_icss_iep_pwat_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, icss_iep_of_match);

static stwuct pwatfowm_dwivew icss_iep_dwivew = {
	.dwivew = {
		.name = "icss-iep",
		.of_match_tabwe = icss_iep_of_match,
	},
	.pwobe = icss_iep_pwobe,
};
moduwe_pwatfowm_dwivew(icss_iep_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TI ICSS IEP dwivew");
MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_AUTHOW("Md Danish Anwaw <danishanwaw@ti.com>");
