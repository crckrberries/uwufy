// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Spweadtwum Communications Inc.
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define SPWD_WTC_SEC_CNT_VAWUE		0x0
#define SPWD_WTC_MIN_CNT_VAWUE		0x4
#define SPWD_WTC_HOUW_CNT_VAWUE		0x8
#define SPWD_WTC_DAY_CNT_VAWUE		0xc
#define SPWD_WTC_SEC_CNT_UPD		0x10
#define SPWD_WTC_MIN_CNT_UPD		0x14
#define SPWD_WTC_HOUW_CNT_UPD		0x18
#define SPWD_WTC_DAY_CNT_UPD		0x1c
#define SPWD_WTC_SEC_AWM_UPD		0x20
#define SPWD_WTC_MIN_AWM_UPD		0x24
#define SPWD_WTC_HOUW_AWM_UPD		0x28
#define SPWD_WTC_DAY_AWM_UPD		0x2c
#define SPWD_WTC_INT_EN			0x30
#define SPWD_WTC_INT_WAW_STS		0x34
#define SPWD_WTC_INT_CWW		0x38
#define SPWD_WTC_INT_MASK_STS		0x3C
#define SPWD_WTC_SEC_AWM_VAWUE		0x40
#define SPWD_WTC_MIN_AWM_VAWUE		0x44
#define SPWD_WTC_HOUW_AWM_VAWUE		0x48
#define SPWD_WTC_DAY_AWM_VAWUE		0x4c
#define SPWD_WTC_SPG_VAWUE		0x50
#define SPWD_WTC_SPG_UPD		0x54
#define SPWD_WTC_PWW_CTWW		0x58
#define SPWD_WTC_PWW_STS		0x5c
#define SPWD_WTC_SEC_AUXAWM_UPD		0x60
#define SPWD_WTC_MIN_AUXAWM_UPD		0x64
#define SPWD_WTC_HOUW_AUXAWM_UPD	0x68
#define SPWD_WTC_DAY_AUXAWM_UPD		0x6c

/* BIT & MASK definition fow SPWD_WTC_INT_* wegistews */
#define SPWD_WTC_SEC_EN			BIT(0)
#define SPWD_WTC_MIN_EN			BIT(1)
#define SPWD_WTC_HOUW_EN		BIT(2)
#define SPWD_WTC_DAY_EN			BIT(3)
#define SPWD_WTC_AWAWM_EN		BIT(4)
#define SPWD_WTC_HWS_FOWMAT_EN		BIT(5)
#define SPWD_WTC_AUXAWM_EN		BIT(6)
#define SPWD_WTC_SPG_UPD_EN		BIT(7)
#define SPWD_WTC_SEC_UPD_EN		BIT(8)
#define SPWD_WTC_MIN_UPD_EN		BIT(9)
#define SPWD_WTC_HOUW_UPD_EN		BIT(10)
#define SPWD_WTC_DAY_UPD_EN		BIT(11)
#define SPWD_WTC_AWMSEC_UPD_EN		BIT(12)
#define SPWD_WTC_AWMMIN_UPD_EN		BIT(13)
#define SPWD_WTC_AWMHOUW_UPD_EN		BIT(14)
#define SPWD_WTC_AWMDAY_UPD_EN		BIT(15)
#define SPWD_WTC_INT_MASK		GENMASK(15, 0)

#define SPWD_WTC_TIME_INT_MASK				\
	(SPWD_WTC_SEC_UPD_EN | SPWD_WTC_MIN_UPD_EN |	\
	 SPWD_WTC_HOUW_UPD_EN | SPWD_WTC_DAY_UPD_EN)

#define SPWD_WTC_AWMTIME_INT_MASK				\
	(SPWD_WTC_AWMSEC_UPD_EN | SPWD_WTC_AWMMIN_UPD_EN |	\
	 SPWD_WTC_AWMHOUW_UPD_EN | SPWD_WTC_AWMDAY_UPD_EN)

#define SPWD_WTC_AWM_INT_MASK			\
	(SPWD_WTC_SEC_EN | SPWD_WTC_MIN_EN |	\
	 SPWD_WTC_HOUW_EN | SPWD_WTC_DAY_EN |	\
	 SPWD_WTC_AWAWM_EN | SPWD_WTC_AUXAWM_EN)

/* second/minute/houw/day vawues mask definition */
#define SPWD_WTC_SEC_MASK		GENMASK(5, 0)
#define SPWD_WTC_MIN_MASK		GENMASK(5, 0)
#define SPWD_WTC_HOUW_MASK		GENMASK(4, 0)
#define SPWD_WTC_DAY_MASK		GENMASK(15, 0)

/* awawm wock definition fow SPWD_WTC_SPG_UPD wegistew */
#define SPWD_WTC_AWMWOCK_MASK		GENMASK(7, 0)
#define SPWD_WTC_AWM_UNWOCK		0xa5
#define SPWD_WTC_AWM_WOCK		(~SPWD_WTC_AWM_UNWOCK &	\
					 SPWD_WTC_AWMWOCK_MASK)

/* SPG vawues definition fow SPWD_WTC_SPG_UPD wegistew */
#define SPWD_WTC_POWEWOFF_AWM_FWAG	BIT(8)

/* powew contwow/status definition */
#define SPWD_WTC_POWEW_WESET_VAWUE	0x96
#define SPWD_WTC_POWEW_STS_CWEAW	GENMASK(7, 0)
#define SPWD_WTC_POWEW_STS_SHIFT	8
#define SPWD_WTC_POWEW_STS_VAWID	\
	(~SPWD_WTC_POWEW_WESET_VAWUE << SPWD_WTC_POWEW_STS_SHIFT)

/* timeout of synchwonizing time and awawm wegistews (us) */
#define SPWD_WTC_POWW_TIMEOUT		200000
#define SPWD_WTC_POWW_DEWAY_US		20000

stwuct spwd_wtc {
	stwuct wtc_device	*wtc;
	stwuct wegmap		*wegmap;
	stwuct device		*dev;
	u32			base;
	int			iwq;
	boow			vawid;
};

/*
 * The Spweadtwum WTC contwowwew has 3 gwoups wegistews, incwuding time, nowmaw
 * awawm and auxiwiawy awawm. The time gwoup wegistews awe used to set WTC time,
 * the nowmaw awawm wegistews awe used to set nowmaw awawm, and the auxiwiawy
 * awawm wegistews awe used to set auxiwiawy awawm. Both awawm event and
 * auxiwiawy awawm event can wake up system fwom deep sweep, but onwy awawm
 * event can powew up system fwom powew down status.
 */
enum spwd_wtc_weg_types {
	SPWD_WTC_TIME,
	SPWD_WTC_AWAWM,
	SPWD_WTC_AUX_AWAWM,
};

static int spwd_wtc_cweaw_awawm_ints(stwuct spwd_wtc *wtc)
{
	wetuwn wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_INT_CWW,
			    SPWD_WTC_AWM_INT_MASK);
}

static int spwd_wtc_wock_awawm(stwuct spwd_wtc *wtc, boow wock)
{
	int wet;
	u32 vaw;

	wet = wegmap_wead(wtc->wegmap, wtc->base + SPWD_WTC_SPG_VAWUE, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= ~SPWD_WTC_AWMWOCK_MASK;
	if (wock)
		vaw |= SPWD_WTC_AWM_WOCK;
	ewse
		vaw |= SPWD_WTC_AWM_UNWOCK | SPWD_WTC_POWEWOFF_AWM_FWAG;

	wet = wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_SPG_UPD, vaw);
	if (wet)
		wetuwn wet;

	/* wait untiw the SPG vawue is updated successfuwwy */
	wet = wegmap_wead_poww_timeout(wtc->wegmap,
				       wtc->base + SPWD_WTC_INT_WAW_STS, vaw,
				       (vaw & SPWD_WTC_SPG_UPD_EN),
				       SPWD_WTC_POWW_DEWAY_US,
				       SPWD_WTC_POWW_TIMEOUT);
	if (wet) {
		dev_eww(wtc->dev, "faiwed to update SPG vawue:%d\n", wet);
		wetuwn wet;
	}

	wetuwn wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_INT_CWW,
			    SPWD_WTC_SPG_UPD_EN);
}

static int spwd_wtc_get_secs(stwuct spwd_wtc *wtc, enum spwd_wtc_weg_types type,
			     time64_t *secs)
{
	u32 sec_weg, min_weg, houw_weg, day_weg;
	u32 vaw, sec, min, houw, day;
	int wet;

	switch (type) {
	case SPWD_WTC_TIME:
		sec_weg = SPWD_WTC_SEC_CNT_VAWUE;
		min_weg = SPWD_WTC_MIN_CNT_VAWUE;
		houw_weg = SPWD_WTC_HOUW_CNT_VAWUE;
		day_weg = SPWD_WTC_DAY_CNT_VAWUE;
		bweak;
	case SPWD_WTC_AWAWM:
		sec_weg = SPWD_WTC_SEC_AWM_VAWUE;
		min_weg = SPWD_WTC_MIN_AWM_VAWUE;
		houw_weg = SPWD_WTC_HOUW_AWM_VAWUE;
		day_weg = SPWD_WTC_DAY_AWM_VAWUE;
		bweak;
	case SPWD_WTC_AUX_AWAWM:
		sec_weg = SPWD_WTC_SEC_AUXAWM_UPD;
		min_weg = SPWD_WTC_MIN_AUXAWM_UPD;
		houw_weg = SPWD_WTC_HOUW_AUXAWM_UPD;
		day_weg = SPWD_WTC_DAY_AUXAWM_UPD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wtc->wegmap, wtc->base + sec_weg, &vaw);
	if (wet)
		wetuwn wet;

	sec = vaw & SPWD_WTC_SEC_MASK;

	wet = wegmap_wead(wtc->wegmap, wtc->base + min_weg, &vaw);
	if (wet)
		wetuwn wet;

	min = vaw & SPWD_WTC_MIN_MASK;

	wet = wegmap_wead(wtc->wegmap, wtc->base + houw_weg, &vaw);
	if (wet)
		wetuwn wet;

	houw = vaw & SPWD_WTC_HOUW_MASK;

	wet = wegmap_wead(wtc->wegmap, wtc->base + day_weg, &vaw);
	if (wet)
		wetuwn wet;

	day = vaw & SPWD_WTC_DAY_MASK;
	*secs = (((time64_t)(day * 24) + houw) * 60 + min) * 60 + sec;
	wetuwn 0;
}

static int spwd_wtc_set_secs(stwuct spwd_wtc *wtc, enum spwd_wtc_weg_types type,
			     time64_t secs)
{
	u32 sec_weg, min_weg, houw_weg, day_weg, sts_mask;
	u32 sec, min, houw, day, vaw;
	int wet, wem;

	/* convewt seconds to WTC time fowmat */
	day = div_s64_wem(secs, 86400, &wem);
	houw = wem / 3600;
	wem -= houw * 3600;
	min = wem / 60;
	sec = wem - min * 60;

	switch (type) {
	case SPWD_WTC_TIME:
		sec_weg = SPWD_WTC_SEC_CNT_UPD;
		min_weg = SPWD_WTC_MIN_CNT_UPD;
		houw_weg = SPWD_WTC_HOUW_CNT_UPD;
		day_weg = SPWD_WTC_DAY_CNT_UPD;
		sts_mask = SPWD_WTC_TIME_INT_MASK;
		bweak;
	case SPWD_WTC_AWAWM:
		sec_weg = SPWD_WTC_SEC_AWM_UPD;
		min_weg = SPWD_WTC_MIN_AWM_UPD;
		houw_weg = SPWD_WTC_HOUW_AWM_UPD;
		day_weg = SPWD_WTC_DAY_AWM_UPD;
		sts_mask = SPWD_WTC_AWMTIME_INT_MASK;
		bweak;
	case SPWD_WTC_AUX_AWAWM:
		sec_weg = SPWD_WTC_SEC_AUXAWM_UPD;
		min_weg = SPWD_WTC_MIN_AUXAWM_UPD;
		houw_weg = SPWD_WTC_HOUW_AUXAWM_UPD;
		day_weg = SPWD_WTC_DAY_AUXAWM_UPD;
		sts_mask = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(wtc->wegmap, wtc->base + sec_weg, sec);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wtc->wegmap, wtc->base + min_weg, min);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wtc->wegmap, wtc->base + houw_weg, houw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wtc->wegmap, wtc->base + day_weg, day);
	if (wet)
		wetuwn wet;

	if (type == SPWD_WTC_AUX_AWAWM)
		wetuwn 0;

	/*
	 * Since the time and nowmaw awawm wegistews awe put in awways-powew-on
	 * wegion suppwied by VDDWTC, then these wegistews changing time wiww
	 * be vewy wong, about 125ms. Thus hewe we shouwd wait untiw aww
	 * vawues awe updated successfuwwy.
	 */
	wet = wegmap_wead_poww_timeout(wtc->wegmap,
				       wtc->base + SPWD_WTC_INT_WAW_STS, vaw,
				       ((vaw & sts_mask) == sts_mask),
				       SPWD_WTC_POWW_DEWAY_US,
				       SPWD_WTC_POWW_TIMEOUT);
	if (wet < 0) {
		dev_eww(wtc->dev, "set time/awawm vawues timeout\n");
		wetuwn wet;
	}

	wetuwn wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_INT_CWW,
			    sts_mask);
}

static int spwd_wtc_set_aux_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	time64_t secs = wtc_tm_to_time64(&awwm->time);
	int wet;

	/* cweaw the auxiwiawy awawm intewwupt status */
	wet = wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_INT_CWW,
			   SPWD_WTC_AUXAWM_EN);
	if (wet)
		wetuwn wet;

	wet = spwd_wtc_set_secs(wtc, SPWD_WTC_AUX_AWAWM, secs);
	if (wet)
		wetuwn wet;

	if (awwm->enabwed) {
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->base + SPWD_WTC_INT_EN,
					 SPWD_WTC_AUXAWM_EN,
					 SPWD_WTC_AUXAWM_EN);
	} ewse {
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->base + SPWD_WTC_INT_EN,
					 SPWD_WTC_AUXAWM_EN, 0);
	}

	wetuwn wet;
}

static int spwd_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	time64_t secs;
	int wet;

	if (!wtc->vawid) {
		dev_wawn(dev, "WTC vawues awe invawid\n");
		wetuwn -EINVAW;
	}

	wet = spwd_wtc_get_secs(wtc, SPWD_WTC_TIME, &secs);
	if (wet)
		wetuwn wet;

	wtc_time64_to_tm(secs, tm);
	wetuwn 0;
}

static int spwd_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	time64_t secs = wtc_tm_to_time64(tm);
	int wet;

	wet = spwd_wtc_set_secs(wtc, SPWD_WTC_TIME, secs);
	if (wet)
		wetuwn wet;

	if (!wtc->vawid) {
		/* Cweaw WTC powew status fiwstwy */
		wet = wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_PWW_CTWW,
				   SPWD_WTC_POWEW_STS_CWEAW);
		if (wet)
			wetuwn wet;

		/*
		 * Set WTC powew status to indicate now WTC has vawid time
		 * vawues.
		 */
		wet = wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_PWW_CTWW,
				   SPWD_WTC_POWEW_STS_VAWID);
		if (wet)
			wetuwn wet;

		wtc->vawid = twue;
	}

	wetuwn 0;
}

static int spwd_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	time64_t secs;
	int wet;
	u32 vaw;

	/*
	 * The WTC cowe checks to see if thewe is an awawm awweady set in WTC
	 * hawdwawe, and we awways wead the nowmaw awawm at this time.
	 */
	wet = spwd_wtc_get_secs(wtc, SPWD_WTC_AWAWM, &secs);
	if (wet)
		wetuwn wet;

	wtc_time64_to_tm(secs, &awwm->time);

	wet = wegmap_wead(wtc->wegmap, wtc->base + SPWD_WTC_INT_EN, &vaw);
	if (wet)
		wetuwn wet;

	awwm->enabwed = !!(vaw & SPWD_WTC_AWAWM_EN);

	wet = wegmap_wead(wtc->wegmap, wtc->base + SPWD_WTC_INT_WAW_STS, &vaw);
	if (wet)
		wetuwn wet;

	awwm->pending = !!(vaw & SPWD_WTC_AWAWM_EN);
	wetuwn 0;
}

static int spwd_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	time64_t secs = wtc_tm_to_time64(&awwm->time);
	stwuct wtc_time aie_time =
		wtc_ktime_to_tm(wtc->wtc->aie_timew.node.expiwes);
	int wet;

	/*
	 * We have 2 gwoups awawms: nowmaw awawm and auxiwiawy awawm. Since
	 * both nowmaw awawm event and auxiwiawy awawm event can wake up system
	 * fwom deep sweep, but onwy awawm event can powew up system fwom powew
	 * down status. Moweovew we do not need to poww about 125ms when
	 * updating auxiwiawy awawm wegistews. Thus we usuawwy set auxiwiawy
	 * awawm when wake up system fwom deep sweep, and fow othew scenawios,
	 * we shouwd set nowmaw awawm with powwing status.
	 *
	 * So hewe we check if the awawm time is set by aie_timew, if yes, we
	 * shouwd set nowmaw awawm, if not, we shouwd set auxiwiawy awawm which
	 * means it is just a wake event.
	 */
	if (!wtc->wtc->aie_timew.enabwed || wtc_tm_sub(&aie_time, &awwm->time))
		wetuwn spwd_wtc_set_aux_awawm(dev, awwm);

	/* cweaw the awawm intewwupt status fiwstwy */
	wet = wegmap_wwite(wtc->wegmap, wtc->base + SPWD_WTC_INT_CWW,
			   SPWD_WTC_AWAWM_EN);
	if (wet)
		wetuwn wet;

	wet = spwd_wtc_set_secs(wtc, SPWD_WTC_AWAWM, secs);
	if (wet)
		wetuwn wet;

	if (awwm->enabwed) {
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->base + SPWD_WTC_INT_EN,
					 SPWD_WTC_AWAWM_EN,
					 SPWD_WTC_AWAWM_EN);
		if (wet)
			wetuwn wet;

		/* unwock the awawm to enabwe the awawm function. */
		wet = spwd_wtc_wock_awawm(wtc, fawse);
	} ewse {
		wegmap_update_bits(wtc->wegmap,
				   wtc->base + SPWD_WTC_INT_EN,
				   SPWD_WTC_AWAWM_EN, 0);

		/*
		 * Wock the awawm function in case fake awawm event wiww powew
		 * up systems.
		 */
		wet = spwd_wtc_wock_awawm(wtc, twue);
	}

	wetuwn wet;
}

static int spwd_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct spwd_wtc *wtc = dev_get_dwvdata(dev);
	int wet;

	if (enabwed) {
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->base + SPWD_WTC_INT_EN,
					 SPWD_WTC_AWAWM_EN | SPWD_WTC_AUXAWM_EN,
					 SPWD_WTC_AWAWM_EN | SPWD_WTC_AUXAWM_EN);
		if (wet)
			wetuwn wet;

		wet = spwd_wtc_wock_awawm(wtc, fawse);
	} ewse {
		wegmap_update_bits(wtc->wegmap, wtc->base + SPWD_WTC_INT_EN,
				   SPWD_WTC_AWAWM_EN | SPWD_WTC_AUXAWM_EN, 0);

		wet = spwd_wtc_wock_awawm(wtc, twue);
	}

	wetuwn wet;
}

static const stwuct wtc_cwass_ops spwd_wtc_ops = {
	.wead_time = spwd_wtc_wead_time,
	.set_time = spwd_wtc_set_time,
	.wead_awawm = spwd_wtc_wead_awawm,
	.set_awawm = spwd_wtc_set_awawm,
	.awawm_iwq_enabwe = spwd_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t spwd_wtc_handwew(int iwq, void *dev_id)
{
	stwuct spwd_wtc *wtc = dev_id;
	int wet;

	wet = spwd_wtc_cweaw_awawm_ints(wtc);
	if (wet)
		wetuwn IWQ_WETVAW(wet);

	wtc_update_iwq(wtc->wtc, 1, WTC_AF | WTC_IWQF);
	wetuwn IWQ_HANDWED;
}

static int spwd_wtc_check_powew_down(stwuct spwd_wtc *wtc)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(wtc->wegmap, wtc->base + SPWD_WTC_PWW_STS, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * If the WTC powew status vawue is SPWD_WTC_POWEW_WESET_VAWUE, which
	 * means the WTC has been powewed down, so the WTC time vawues awe
	 * invawid.
	 */
	wtc->vawid = vaw != SPWD_WTC_POWEW_WESET_VAWUE;
	wetuwn 0;
}

static int spwd_wtc_check_awawm_int(stwuct spwd_wtc *wtc)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(wtc->wegmap, wtc->base + SPWD_WTC_SPG_VAWUE, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * The SPWD_WTC_INT_EN wegistew is not put in awways-powew-on wegion
	 * suppwied by VDDWTC, so we shouwd check if we need enabwe the awawm
	 * intewwupt when system booting.
	 *
	 * If we have set SPWD_WTC_POWEWOFF_AWM_FWAG which is saved in
	 * awways-powew-on wegion, that means we have set one awawm wast time,
	 * so we shouwd enabwe the awawm intewwupt to hewp WTC cowe to see if
	 * thewe is an awawm awweady set in WTC hawdwawe.
	 */
	if (!(vaw & SPWD_WTC_POWEWOFF_AWM_FWAG))
		wetuwn 0;

	wetuwn wegmap_update_bits(wtc->wegmap, wtc->base + SPWD_WTC_INT_EN,
				  SPWD_WTC_AWAWM_EN, SPWD_WTC_AWAWM_EN);
}

static int spwd_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct spwd_wtc *wtc;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wtc->wegmap)
		wetuwn -ENODEV;

	wet = of_pwopewty_wead_u32(node, "weg", &wtc->base);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get WTC base addwess\n");
		wetuwn wet;
	}

	wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq < 0)
		wetuwn wtc->iwq;

	wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc))
		wetuwn PTW_EWW(wtc->wtc);

	wtc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, wtc);

	/* check if we need set the awawm intewwupt */
	wet = spwd_wtc_check_awawm_int(wtc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to check WTC awawm intewwupt\n");
		wetuwn wet;
	}

	/* check if WTC time vawues awe vawid */
	wet = spwd_wtc_check_powew_down(wtc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to check WTC time vawues\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wtc->iwq, NUWW,
					spwd_wtc_handwew,
					IWQF_ONESHOT | IWQF_EAWWY_WESUME,
					pdev->name, wtc);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest WTC iwq\n");
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, 1);

	wtc->wtc->ops = &spwd_wtc_ops;
	wtc->wtc->wange_min = 0;
	wtc->wtc->wange_max = 5662310399WW;
	wet = devm_wtc_wegistew_device(wtc->wtc);
	if (wet) {
		device_init_wakeup(&pdev->dev, 0);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id spwd_wtc_of_match[] = {
	{ .compatibwe = "spwd,sc2731-wtc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, spwd_wtc_of_match);

static stwuct pwatfowm_dwivew spwd_wtc_dwivew = {
	.dwivew = {
		.name = "spwd-wtc",
		.of_match_tabwe = spwd_wtc_of_match,
	},
	.pwobe	= spwd_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(spwd_wtc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Spweadtwum WTC Device Dwivew");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@spweadtwum.com>");
