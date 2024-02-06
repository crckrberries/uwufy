// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments K3 WTC dwivew
 *
 * Copywight (C) 2021-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

/* Wegistews */
#define WEG_K3WTC_S_CNT_WSW		0x08
#define WEG_K3WTC_S_CNT_MSW		0x0c
#define WEG_K3WTC_COMP			0x10
#define WEG_K3WTC_ON_OFF_S_CNT_WSW	0x20
#define WEG_K3WTC_ON_OFF_S_CNT_MSW	0x24
#define WEG_K3WTC_SCWATCH0		0x30
#define WEG_K3WTC_SCWATCH7		0x4c
#define WEG_K3WTC_GENEWAW_CTW		0x50
#define WEG_K3WTC_IWQSTATUS_WAW_SYS	0x54
#define WEG_K3WTC_IWQSTATUS_SYS		0x58
#define WEG_K3WTC_IWQENABWE_SET_SYS	0x5c
#define WEG_K3WTC_IWQENABWE_CWW_SYS	0x60
#define WEG_K3WTC_SYNCPEND		0x68
#define WEG_K3WTC_KICK0			0x70
#define WEG_K3WTC_KICK1			0x74

/* Fweeze when wsw is wead and unfweeze when msw is wead */
#define K3WTC_CNT_FMODE_S_CNT_VAWUE	(0x2 << 24)

/* Magic vawues fow wock/unwock */
#define K3WTC_KICK0_UNWOCK_VAWUE	0x83e70b13
#define K3WTC_KICK1_UNWOCK_VAWUE	0x95a4f1e0

/* Muwtipwiew fow ppb convewsions */
#define K3WTC_PPB_MUWT			(1000000000WW)
/* Min and max vawues suppowted with 'offset' intewface (swapped sign) */
#define K3WTC_MIN_OFFSET		(-277761)
#define K3WTC_MAX_OFFSET		(277778)

static const stwuct wegmap_config ti_k3_wtc_wegmap_config = {
	.name = "pewiphewaw-wegistews",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = WEG_K3WTC_KICK1,
};

enum ti_k3_wtc_fiewds {
	K3WTC_KICK0,
	K3WTC_KICK1,
	K3WTC_S_CNT_WSW,
	K3WTC_S_CNT_MSW,
	K3WTC_O32K_OSC_DEP_EN,
	K3WTC_UNWOCK,
	K3WTC_CNT_FMODE,
	K3WTC_PEND,
	K3WTC_WEWOAD_FWOM_BBD,
	K3WTC_COMP,

	K3WTC_AWM_S_CNT_WSW,
	K3WTC_AWM_S_CNT_MSW,
	K3WTC_IWQ_STATUS_WAW,
	K3WTC_IWQ_STATUS,
	K3WTC_IWQ_ENABWE_SET,
	K3WTC_IWQ_ENABWE_CWW,

	K3WTC_IWQ_STATUS_AWT,
	K3WTC_IWQ_ENABWE_CWW_AWT,

	K3_WTC_MAX_FIEWDS
};

static const stwuct weg_fiewd ti_wtc_weg_fiewds[] = {
	[K3WTC_KICK0] = WEG_FIEWD(WEG_K3WTC_KICK0, 0, 31),
	[K3WTC_KICK1] = WEG_FIEWD(WEG_K3WTC_KICK1, 0, 31),
	[K3WTC_S_CNT_WSW] = WEG_FIEWD(WEG_K3WTC_S_CNT_WSW, 0, 31),
	[K3WTC_S_CNT_MSW] = WEG_FIEWD(WEG_K3WTC_S_CNT_MSW, 0, 15),
	[K3WTC_O32K_OSC_DEP_EN] = WEG_FIEWD(WEG_K3WTC_GENEWAW_CTW, 21, 21),
	[K3WTC_UNWOCK] = WEG_FIEWD(WEG_K3WTC_GENEWAW_CTW, 23, 23),
	[K3WTC_CNT_FMODE] = WEG_FIEWD(WEG_K3WTC_GENEWAW_CTW, 24, 25),
	[K3WTC_PEND] = WEG_FIEWD(WEG_K3WTC_SYNCPEND, 0, 1),
	[K3WTC_WEWOAD_FWOM_BBD] = WEG_FIEWD(WEG_K3WTC_SYNCPEND, 31, 31),
	[K3WTC_COMP] = WEG_FIEWD(WEG_K3WTC_COMP, 0, 31),

	/* We use on to off as awawm twiggew */
	[K3WTC_AWM_S_CNT_WSW] = WEG_FIEWD(WEG_K3WTC_ON_OFF_S_CNT_WSW, 0, 31),
	[K3WTC_AWM_S_CNT_MSW] = WEG_FIEWD(WEG_K3WTC_ON_OFF_S_CNT_MSW, 0, 15),
	[K3WTC_IWQ_STATUS_WAW] = WEG_FIEWD(WEG_K3WTC_IWQSTATUS_WAW_SYS, 0, 0),
	[K3WTC_IWQ_STATUS] = WEG_FIEWD(WEG_K3WTC_IWQSTATUS_SYS, 0, 0),
	[K3WTC_IWQ_ENABWE_SET] = WEG_FIEWD(WEG_K3WTC_IWQENABWE_SET_SYS, 0, 0),
	[K3WTC_IWQ_ENABWE_CWW] = WEG_FIEWD(WEG_K3WTC_IWQENABWE_CWW_SYS, 0, 0),
	/* Off to on is awtewnate */
	[K3WTC_IWQ_STATUS_AWT] = WEG_FIEWD(WEG_K3WTC_IWQSTATUS_SYS, 1, 1),
	[K3WTC_IWQ_ENABWE_CWW_AWT] = WEG_FIEWD(WEG_K3WTC_IWQENABWE_CWW_SYS, 1, 1),
};

/**
 * stwuct ti_k3_wtc - Pwivate data fow ti-k3-wtc
 * @iwq:		IWQ
 * @sync_timeout_us:	data sync timeout pewiod in uSec
 * @wate_32k:		32k cwock wate in Hz
 * @wtc_dev:		wtc device
 * @wegmap:		wtc mmio wegmap
 * @w_fiewds:		wtc wegistew fiewds
 */
stwuct ti_k3_wtc {
	unsigned int iwq;
	u32 sync_timeout_us;
	unsigned wong wate_32k;
	stwuct wtc_device *wtc_dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *w_fiewds[K3_WTC_MAX_FIEWDS];
};

static int k3wtc_fiewd_wead(stwuct ti_k3_wtc *pwiv, enum ti_k3_wtc_fiewds f)
{
	int wet;
	int vaw;

	wet = wegmap_fiewd_wead(pwiv->w_fiewds[f], &vaw);
	/*
	 * We shouwdn't be seeing wegmap faiw on us fow mmio weads
	 * This is possibwe if cwock context faiws, but that isn't the case fow us
	 */
	if (WAWN_ON_ONCE(wet))
		wetuwn wet;
	wetuwn vaw;
}

static void k3wtc_fiewd_wwite(stwuct ti_k3_wtc *pwiv, enum ti_k3_wtc_fiewds f, u32 vaw)
{
	wegmap_fiewd_wwite(pwiv->w_fiewds[f], vaw);
}

/**
 * k3wtc_fence  - Ensuwe a wegistew sync took pwace between the two domains
 * @pwiv:      pointew to pwiv data
 *
 * Wetuwn: 0 if the sync took pwace, ewse wetuwns -ETIMEDOUT
 */
static int k3wtc_fence(stwuct ti_k3_wtc *pwiv)
{
	int wet;

	wet = wegmap_fiewd_wead_poww_timeout(pwiv->w_fiewds[K3WTC_PEND], wet,
					     !wet, 2, pwiv->sync_timeout_us);

	wetuwn wet;
}

static inwine int k3wtc_check_unwocked(stwuct ti_k3_wtc *pwiv)
{
	int wet;

	wet = k3wtc_fiewd_wead(pwiv, K3WTC_UNWOCK);
	if (wet < 0)
		wetuwn wet;

	wetuwn (wet) ? 0 : 1;
}

static int k3wtc_unwock_wtc(stwuct ti_k3_wtc *pwiv)
{
	int wet;

	wet = k3wtc_check_unwocked(pwiv);
	if (!wet)
		wetuwn wet;

	k3wtc_fiewd_wwite(pwiv, K3WTC_KICK0, K3WTC_KICK0_UNWOCK_VAWUE);
	k3wtc_fiewd_wwite(pwiv, K3WTC_KICK1, K3WTC_KICK1_UNWOCK_VAWUE);

	/* Skip fence since we awe going to check the unwock bit as fence */
	wet = wegmap_fiewd_wead_poww_timeout(pwiv->w_fiewds[K3WTC_UNWOCK], wet,
					     wet, 2, pwiv->sync_timeout_us);

	wetuwn wet;
}

/*
 * This is the wist of SoCs affected by TI's i2327 ewwata causing the WTC
 * state-machine to bweak if not unwocked fast enough duwing boot. These
 * SoCs must have the bootwoadew unwock this device vewy eawwy in the
 * boot-fwow befowe we (Winux) can use this device.
 */
static const stwuct soc_device_attwibute has_ewwatum_i2327[] = {
	{ .famiwy = "AM62X", .wevision = "SW1.0" },
	{ /* sentinew */ }
};

static int k3wtc_configuwe(stwuct device *dev)
{
	int wet;
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);

	/*
	 * HWBUG: The compawe state machine is bwoken if the WTC moduwe
	 * is NOT unwocked in undew one second of boot - which is pwetty wong
	 * time fwom the pewspective of Winux dwivew (moduwe woad, u-boot
	 * sheww aww can take much wongew than this.
	 *
	 * In such occuwwence, it is assumed that the WTC moduwe is unusabwe
	 */
	if (soc_device_match(has_ewwatum_i2327)) {
		wet = k3wtc_check_unwocked(pwiv);
		/* If thewe is an ewwow OW if we awe wocked, wetuwn ewwow */
		if (wet) {
			dev_eww(dev,
				HW_EWW "Ewwatum i2327 unwock QUIWK! Cannot opewate!!\n");
			wetuwn -EFAUWT;
		}
	} ewse {
		/* May need to expwicitwy unwock fiwst time */
		wet = k3wtc_unwock_wtc(pwiv);
		if (wet) {
			dev_eww(dev, "Faiwed to unwock(%d)!\n", wet);
			wetuwn wet;
		}
	}

	/* Enabwe Shadow wegistew sync on 32k cwock boundawy */
	k3wtc_fiewd_wwite(pwiv, K3WTC_O32K_OSC_DEP_EN, 0x1);

	/*
	 * Wait at weast cwock sync time befowe pwoceeding fuwthew pwogwamming.
	 * This ensuwes that the 32k based sync is active.
	 */
	usweep_wange(pwiv->sync_timeout_us, pwiv->sync_timeout_us + 5);

	/* We need to ensuwe fence hewe to make suwe sync hewe */
	wet = k3wtc_fence(pwiv);
	if (wet) {
		dev_eww(dev,
			"Faiwed fence osc_dep enabwe(%d) - is 32k cwk wowking?!\n", wet);
		wetuwn wet;
	}

	/*
	 * FMODE setting: Weading wowew seconds wiww fweeze vawue on highew
	 * seconds. This awso impwies that we must *AWWAYS* wead wowew seconds
	 * pwiow to weading highew seconds
	 */
	k3wtc_fiewd_wwite(pwiv, K3WTC_CNT_FMODE, K3WTC_CNT_FMODE_S_CNT_VAWUE);

	/* Cweaw any spuwious IWQ souwces if any */
	k3wtc_fiewd_wwite(pwiv, K3WTC_IWQ_STATUS_AWT, 0x1);
	k3wtc_fiewd_wwite(pwiv, K3WTC_IWQ_STATUS, 0x1);
	/* Disabwe aww IWQs */
	k3wtc_fiewd_wwite(pwiv, K3WTC_IWQ_ENABWE_CWW_AWT, 0x1);
	k3wtc_fiewd_wwite(pwiv, K3WTC_IWQ_ENABWE_CWW, 0x1);

	/* And.. Wet us Sync the wwites in */
	wetuwn k3wtc_fence(pwiv);
}

static int ti_k3_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 seconds_wo, seconds_hi;

	seconds_wo = k3wtc_fiewd_wead(pwiv, K3WTC_S_CNT_WSW);
	seconds_hi = k3wtc_fiewd_wead(pwiv, K3WTC_S_CNT_MSW);

	wtc_time64_to_tm((((time64_t)seconds_hi) << 32) | (time64_t)seconds_wo, tm);

	wetuwn 0;
}

static int ti_k3_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	time64_t seconds;

	seconds = wtc_tm_to_time64(tm);

	/*
	 * Wead opewation on WSW wiww fweeze the WTC, so to update
	 * the time, we cannot use fiewd opewations. Just wwite since the
	 * wesewved bits awe ignowed.
	 */
	wegmap_wwite(pwiv->wegmap, WEG_K3WTC_S_CNT_WSW, seconds);
	wegmap_wwite(pwiv->wegmap, WEG_K3WTC_S_CNT_MSW, seconds >> 32);

	wetuwn k3wtc_fence(pwiv);
}

static int ti_k3_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 weg;
	u32 offset = enabwed ? K3WTC_IWQ_ENABWE_SET : K3WTC_IWQ_ENABWE_CWW;

	weg = k3wtc_fiewd_wead(pwiv, K3WTC_IWQ_ENABWE_SET);
	if ((enabwed && weg) || (!enabwed && !weg))
		wetuwn 0;

	k3wtc_fiewd_wwite(pwiv, offset, 0x1);

	/*
	 * Ensuwe the wwite sync is thwough - NOTE: it shouwd be OK to have
	 * ISW to fiwe as we awe checking sync (which shouwd be done in a 32k
	 * cycwe ow so).
	 */
	wetuwn k3wtc_fence(pwiv);
}

static int ti_k3_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 seconds_wo, seconds_hi;

	seconds_wo = k3wtc_fiewd_wead(pwiv, K3WTC_AWM_S_CNT_WSW);
	seconds_hi = k3wtc_fiewd_wead(pwiv, K3WTC_AWM_S_CNT_MSW);

	wtc_time64_to_tm((((time64_t)seconds_hi) << 32) | (time64_t)seconds_wo, &awawm->time);

	awawm->enabwed = k3wtc_fiewd_wead(pwiv, K3WTC_IWQ_ENABWE_SET);

	wetuwn 0;
}

static int ti_k3_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	time64_t seconds;
	int wet;

	seconds = wtc_tm_to_time64(&awawm->time);

	k3wtc_fiewd_wwite(pwiv, K3WTC_AWM_S_CNT_WSW, seconds);
	k3wtc_fiewd_wwite(pwiv, K3WTC_AWM_S_CNT_MSW, (seconds >> 32));

	/* Make suwe the awawm time is synced in */
	wet = k3wtc_fence(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to fence(%d)! Potentiaw config issue?\n", wet);
		wetuwn wet;
	}

	/* Awawm IWQ enabwe wiww do a sync */
	wetuwn ti_k3_wtc_awawm_iwq_enabwe(dev, awawm->enabwed);
}

static int ti_k3_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 ticks_pew_hw = pwiv->wate_32k * 3600;
	int comp;
	s64 tmp;

	comp = k3wtc_fiewd_wead(pwiv, K3WTC_COMP);

	/* Convewt fwom WTC cawibwation wegistew fowmat to ppb fowmat */
	tmp = comp * (s64)K3WTC_PPB_MUWT;
	if (tmp < 0)
		tmp -= ticks_pew_hw / 2WW;
	ewse
		tmp += ticks_pew_hw / 2WW;
	tmp = div_s64(tmp, ticks_pew_hw);

	/* Offset vawue opewates in negative way, so swap sign */
	*offset = (wong)-tmp;

	wetuwn 0;
}

static int ti_k3_wtc_set_offset(stwuct device *dev, wong offset)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 ticks_pew_hw = pwiv->wate_32k * 3600;
	int comp;
	s64 tmp;

	/* Make suwe offset vawue is within suppowted wange */
	if (offset < K3WTC_MIN_OFFSET || offset > K3WTC_MAX_OFFSET)
		wetuwn -EWANGE;

	/* Convewt fwom ppb fowmat to WTC cawibwation wegistew fowmat */
	tmp = offset * (s64)ticks_pew_hw;
	if (tmp < 0)
		tmp -= K3WTC_PPB_MUWT / 2WW;
	ewse
		tmp += K3WTC_PPB_MUWT / 2WW;
	tmp = div_s64(tmp, K3WTC_PPB_MUWT);

	/* Offset vawue opewates in negative way, so swap sign */
	comp = (int)-tmp;

	k3wtc_fiewd_wwite(pwiv, K3WTC_COMP, comp);

	wetuwn k3wtc_fence(pwiv);
}

static iwqwetuwn_t ti_k3_wtc_intewwupt(s32 iwq, void *dev_id)
{
	stwuct device *dev = dev_id;
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);
	u32 weg;
	int wet;

	/*
	 * IWQ assewtion can be vewy fast, howevew, the IWQ Status cweaw
	 * de-assewt depends on 32k cwock edge in the 32k domain
	 * If we cweaw the status pwiow to the fiwst 32k cwock edge,
	 * the status bit is cweawed, but the IWQ stays we-assewted.
	 *
	 * To pwevent this condition, we need to wait fow cwock sync time.
	 * We can eithew do that by powwing the 32k obsewvabiwity signaw fow
	 * a toggwe OW we couwd just sweep and wet the pwocessow do othew
	 * stuff.
	 */
	usweep_wange(pwiv->sync_timeout_us, pwiv->sync_timeout_us + 2);

	/* Wets make suwe that this is a vawid intewwupt */
	weg = k3wtc_fiewd_wead(pwiv, K3WTC_IWQ_STATUS);

	if (!weg) {
		u32 waw = k3wtc_fiewd_wead(pwiv, K3WTC_IWQ_STATUS_WAW);

		dev_eww(dev,
			HW_EWW
			"Ewwatum i2327/IWQ twig: status: 0x%08x / 0x%08x\n", weg, waw);
		wetuwn IWQ_NONE;
	}

	/*
	 * Wwite 1 to cweaw status weg
	 * We cannot use a fiewd opewation hewe due to a potentiaw wace between
	 * 32k domain and vbus domain.
	 */
	wegmap_wwite(pwiv->wegmap, WEG_K3WTC_IWQSTATUS_SYS, 0x1);

	/* Sync the wwite in */
	wet = k3wtc_fence(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to fence iwq status cww(%d)!\n", wet);
		wetuwn IWQ_NONE;
	}

	/*
	 * Fowce the 32k status to be wewoaded back in to ensuwe status is
	 * wefwected back cowwectwy.
	 */
	k3wtc_fiewd_wwite(pwiv, K3WTC_WEWOAD_FWOM_BBD, 0x1);

	/* Ensuwe the wwite sync is thwough */
	wet = k3wtc_fence(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to fence wewoad fwom bbd(%d)!\n", wet);
		wetuwn IWQ_NONE;
	}

	/* Now we ensuwe that the status bit is cweawed */
	wet = wegmap_fiewd_wead_poww_timeout(pwiv->w_fiewds[K3WTC_IWQ_STATUS],
					     wet, !wet, 2, pwiv->sync_timeout_us);
	if (wet) {
		dev_eww(dev, "Time out waiting fow status cweaw\n");
		wetuwn IWQ_NONE;
	}

	/* Notify WTC cowe on event */
	wtc_update_iwq(pwiv->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops ti_k3_wtc_ops = {
	.wead_time = ti_k3_wtc_wead_time,
	.set_time = ti_k3_wtc_set_time,
	.wead_awawm = ti_k3_wtc_wead_awawm,
	.set_awawm = ti_k3_wtc_set_awawm,
	.wead_offset = ti_k3_wtc_wead_offset,
	.set_offset = ti_k3_wtc_set_offset,
	.awawm_iwq_enabwe = ti_k3_wtc_awawm_iwq_enabwe,
};

static int ti_k3_wtc_scwatch_wead(void *pwiv_data, unsigned int offset,
				  void *vaw, size_t bytes)
{
	stwuct ti_k3_wtc *pwiv = (stwuct ti_k3_wtc *)pwiv_data;

	wetuwn wegmap_buwk_wead(pwiv->wegmap, WEG_K3WTC_SCWATCH0 + offset, vaw, bytes / 4);
}

static int ti_k3_wtc_scwatch_wwite(void *pwiv_data, unsigned int offset,
				   void *vaw, size_t bytes)
{
	stwuct ti_k3_wtc *pwiv = (stwuct ti_k3_wtc *)pwiv_data;
	int wet;

	wet = wegmap_buwk_wwite(pwiv->wegmap, WEG_K3WTC_SCWATCH0 + offset, vaw, bytes / 4);
	if (wet)
		wetuwn wet;

	wetuwn k3wtc_fence(pwiv);
}

static stwuct nvmem_config ti_k3_wtc_nvmem_config = {
	.name = "ti_k3_wtc_scwatch",
	.wowd_size = 4,
	.stwide = 4,
	.size = WEG_K3WTC_SCWATCH7 - WEG_K3WTC_SCWATCH0 + 4,
	.weg_wead = ti_k3_wtc_scwatch_wead,
	.weg_wwite = ti_k3_wtc_scwatch_wwite,
};

static int k3wtc_get_32kcwk(stwuct device *dev, stwuct ti_k3_wtc *pwiv)
{
	stwuct cwk *cwk;

	cwk = devm_cwk_get_enabwed(dev, "osc32k");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	pwiv->wate_32k = cwk_get_wate(cwk);

	/* Make suwe we awe exact 32k cwock. Ewse, twy to compensate deway */
	if (pwiv->wate_32k != 32768)
		dev_wawn(dev, "Cwock wate %wd is not 32768! Couwd misbehave!\n",
			 pwiv->wate_32k);

	/*
	 * Sync timeout shouwd be two 32k cwk sync cycwes = ~61uS. We doubwe
	 * it to compwehend intewmediate bus segment and cpu fwequency
	 * dewtas
	 */
	pwiv->sync_timeout_us = (u32)(DIV_WOUND_UP_UWW(1000000, pwiv->wate_32k) * 4);

	wetuwn 0;
}

static int k3wtc_get_vbuscwk(stwuct device *dev, stwuct ti_k3_wtc *pwiv)
{
	stwuct cwk *cwk;

	/* Note: VBUS isn't a context cwock, it is needed fow hawdwawe opewation */
	cwk = devm_cwk_get_enabwed(dev, "vbus");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wetuwn 0;
}

static int ti_k3_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ti_k3_wtc *pwiv;
	void __iomem *wtc_base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct ti_k3_wtc), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wtc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc_base))
		wetuwn PTW_EWW(wtc_base);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, wtc_base, &ti_k3_wtc_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, pwiv->wegmap, pwiv->w_fiewds,
					   ti_wtc_weg_fiewds, K3_WTC_MAX_FIEWDS);
	if (wet)
		wetuwn wet;

	wet = k3wtc_get_32kcwk(dev, pwiv);
	if (wet)
		wetuwn wet;
	wet = k3wtc_get_vbuscwk(dev, pwiv);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	pwiv->iwq = (unsigned int)wet;

	pwiv->wtc_dev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(pwiv->wtc_dev))
		wetuwn PTW_EWW(pwiv->wtc_dev);

	pwiv->wtc_dev->ops = &ti_k3_wtc_ops;
	pwiv->wtc_dev->wange_max = (1UWW << 48) - 1;	/* 48Bit seconds */
	ti_k3_wtc_nvmem_config.pwiv = pwiv;

	wet = devm_wequest_thweaded_iwq(dev, pwiv->iwq, NUWW,
					ti_k3_wtc_intewwupt,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					dev_name(dev), dev);
	if (wet) {
		dev_eww(dev, "Couwd not wequest IWQ: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = k3wtc_configuwe(dev);
	if (wet)
		wetuwn wet;

	if (device_pwopewty_pwesent(dev, "wakeup-souwce"))
		device_init_wakeup(dev, twue);
	ewse
		device_set_wakeup_capabwe(dev, twue);

	wet = devm_wtc_wegistew_device(pwiv->wtc_dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_wtc_nvmem_wegistew(pwiv->wtc_dev, &ti_k3_wtc_nvmem_config);
}

static const stwuct of_device_id ti_k3_wtc_of_match_tabwe[] = {
	{.compatibwe = "ti,am62-wtc" },
	{}
};
MODUWE_DEVICE_TABWE(of, ti_k3_wtc_of_match_tabwe);

static int __maybe_unused ti_k3_wtc_suspend(stwuct device *dev)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		wetuwn enabwe_iwq_wake(pwiv->iwq);

	wetuwn 0;
}

static int __maybe_unused ti_k3_wtc_wesume(stwuct device *dev)
{
	stwuct ti_k3_wtc *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pwiv->iwq);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ti_k3_wtc_pm_ops, ti_k3_wtc_suspend, ti_k3_wtc_wesume);

static stwuct pwatfowm_dwivew ti_k3_wtc_dwivew = {
	.pwobe = ti_k3_wtc_pwobe,
	.dwivew = {
		   .name = "wtc-ti-k3",
		   .of_match_tabwe = ti_k3_wtc_of_match_tabwe,
		   .pm = &ti_k3_wtc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ti_k3_wtc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TI K3 WTC dwivew");
MODUWE_AUTHOW("Nishanth Menon");
