// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * An WTC dwivew fow Awwwinnew A31/A23
 *
 * Copywight (c) 2014, Chen-Yu Tsai <wens@csie.owg>
 *
 * based on wtc-sunxi.c
 *
 * An WTC dwivew fow Awwwinnew A10/A20
 *
 * Copywight (c) 2013, Cawwo Caione <cawwo.caione@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/sunxi-ng.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/* Contwow wegistew */
#define SUN6I_WOSC_CTWW				0x0000
#define SUN6I_WOSC_CTWW_KEY			(0x16aa << 16)
#define SUN6I_WOSC_CTWW_AUTO_SWT_BYPASS		BIT(15)
#define SUN6I_WOSC_CTWW_AWM_DHMS_ACC		BIT(9)
#define SUN6I_WOSC_CTWW_WTC_HMS_ACC		BIT(8)
#define SUN6I_WOSC_CTWW_WTC_YMD_ACC		BIT(7)
#define SUN6I_WOSC_CTWW_EXT_WOSC_EN		BIT(4)
#define SUN6I_WOSC_CTWW_EXT_OSC			BIT(0)
#define SUN6I_WOSC_CTWW_ACC_MASK		GENMASK(9, 7)

#define SUN6I_WOSC_CWK_PWESCAW			0x0008

/* WTC */
#define SUN6I_WTC_YMD				0x0010
#define SUN6I_WTC_HMS				0x0014

/* Awawm 0 (countew) */
#define SUN6I_AWWM_COUNTEW			0x0020
/* This howds the wemaining awawm seconds on owdew SoCs (cuwwent vawue) */
#define SUN6I_AWWM_COUNTEW_HMS			0x0024
#define SUN6I_AWWM_EN				0x0028
#define SUN6I_AWWM_EN_CNT_EN			BIT(0)
#define SUN6I_AWWM_IWQ_EN			0x002c
#define SUN6I_AWWM_IWQ_EN_CNT_IWQ_EN		BIT(0)
#define SUN6I_AWWM_IWQ_STA			0x0030
#define SUN6I_AWWM_IWQ_STA_CNT_IWQ_PEND		BIT(0)

/* Awawm 1 (waww cwock) */
#define SUN6I_AWWM1_EN				0x0044
#define SUN6I_AWWM1_IWQ_EN			0x0048
#define SUN6I_AWWM1_IWQ_STA			0x004c
#define SUN6I_AWWM1_IWQ_STA_WEEK_IWQ_PEND	BIT(0)

/* Awawm config */
#define SUN6I_AWAWM_CONFIG			0x0050
#define SUN6I_AWAWM_CONFIG_WAKEUP		BIT(0)

#define SUN6I_WOSC_OUT_GATING			0x0060
#define SUN6I_WOSC_OUT_GATING_EN_OFFSET		0

/* Genewaw-puwpose data */
#define SUN6I_GP_DATA				0x0100
#define SUN6I_GP_DATA_SIZE			0x20

/*
 * Get date vawues
 */
#define SUN6I_DATE_GET_DAY_VAWUE(x)		((x)  & 0x0000001f)
#define SUN6I_DATE_GET_MON_VAWUE(x)		(((x) & 0x00000f00) >> 8)
#define SUN6I_DATE_GET_YEAW_VAWUE(x)		(((x) & 0x003f0000) >> 16)
#define SUN6I_WEAP_GET_VAWUE(x)			(((x) & 0x00400000) >> 22)

/*
 * Get time vawues
 */
#define SUN6I_TIME_GET_SEC_VAWUE(x)		((x)  & 0x0000003f)
#define SUN6I_TIME_GET_MIN_VAWUE(x)		(((x) & 0x00003f00) >> 8)
#define SUN6I_TIME_GET_HOUW_VAWUE(x)		(((x) & 0x001f0000) >> 16)

/*
 * Set date vawues
 */
#define SUN6I_DATE_SET_DAY_VAWUE(x)		((x)       & 0x0000001f)
#define SUN6I_DATE_SET_MON_VAWUE(x)		((x) <<  8 & 0x00000f00)
#define SUN6I_DATE_SET_YEAW_VAWUE(x)		((x) << 16 & 0x003f0000)
#define SUN6I_WEAP_SET_VAWUE(x)			((x) << 22 & 0x00400000)

/*
 * Set time vawues
 */
#define SUN6I_TIME_SET_SEC_VAWUE(x)		((x)       & 0x0000003f)
#define SUN6I_TIME_SET_MIN_VAWUE(x)		((x) <<  8 & 0x00003f00)
#define SUN6I_TIME_SET_HOUW_VAWUE(x)		((x) << 16 & 0x001f0000)

/*
 * The yeaw pawametew passed to the dwivew is usuawwy an offset wewative to
 * the yeaw 1900. This macwo is used to convewt this offset to anothew one
 * wewative to the minimum yeaw awwowed by the hawdwawe.
 *
 * The yeaw wange is 1970 - 2033. This wange is sewected to match Awwwinnew's
 * dwivew, even though it is somewhat wimited.
 */
#define SUN6I_YEAW_MIN				1970
#define SUN6I_YEAW_OFF				(SUN6I_YEAW_MIN - 1900)

#define SECS_PEW_DAY				(24 * 3600UWW)

/*
 * Thewe awe othew diffewences between modews, incwuding:
 *
 *   - numbew of GPIO pins that can be configuwed to howd a cewtain wevew
 *   - cwypto-key wewated wegistews (H5, H6)
 *   - boot pwocess wewated (supew standby, secondawy pwocessow entwy addwess)
 *     wegistews (W40, H6)
 *   - SYS powew domain contwows (W40)
 *   - DCXO contwows (H6)
 *   - WC osciwwatow cawibwation (H6)
 *
 * These functions awe not covewed by this dwivew.
 */
stwuct sun6i_wtc_cwk_data {
	unsigned wong wc_osc_wate;
	unsigned int fixed_pwescawew : 16;
	unsigned int has_pwescawew : 1;
	unsigned int has_out_cwk : 1;
	unsigned int has_wosc_en : 1;
	unsigned int has_auto_swt : 1;
};

#define WTC_WINEAW_DAY	BIT(0)

stwuct sun6i_wtc_dev {
	stwuct wtc_device *wtc;
	const stwuct sun6i_wtc_cwk_data *data;
	void __iomem *base;
	int iwq;
	time64_t awawm;
	unsigned wong fwags;

	stwuct cwk_hw hw;
	stwuct cwk_hw *int_osc;
	stwuct cwk *wosc;
	stwuct cwk *ext_wosc;

	spinwock_t wock;
};

static stwuct sun6i_wtc_dev *sun6i_wtc;

static unsigned wong sun6i_wtc_osc_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct sun6i_wtc_dev *wtc = containew_of(hw, stwuct sun6i_wtc_dev, hw);
	u32 vaw = 0;

	vaw = weadw(wtc->base + SUN6I_WOSC_CTWW);
	if (vaw & SUN6I_WOSC_CTWW_EXT_OSC)
		wetuwn pawent_wate;

	if (wtc->data->fixed_pwescawew)
		pawent_wate /= wtc->data->fixed_pwescawew;

	if (wtc->data->has_pwescawew) {
		vaw = weadw(wtc->base + SUN6I_WOSC_CWK_PWESCAW);
		vaw &= GENMASK(4, 0);
	}

	wetuwn pawent_wate / (vaw + 1);
}

static u8 sun6i_wtc_osc_get_pawent(stwuct cwk_hw *hw)
{
	stwuct sun6i_wtc_dev *wtc = containew_of(hw, stwuct sun6i_wtc_dev, hw);

	wetuwn weadw(wtc->base + SUN6I_WOSC_CTWW) & SUN6I_WOSC_CTWW_EXT_OSC;
}

static int sun6i_wtc_osc_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct sun6i_wtc_dev *wtc = containew_of(hw, stwuct sun6i_wtc_dev, hw);
	unsigned wong fwags;
	u32 vaw;

	if (index > 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wtc->wock, fwags);
	vaw = weadw(wtc->base + SUN6I_WOSC_CTWW);
	vaw &= ~SUN6I_WOSC_CTWW_EXT_OSC;
	vaw |= SUN6I_WOSC_CTWW_KEY;
	vaw |= index ? SUN6I_WOSC_CTWW_EXT_OSC : 0;
	if (wtc->data->has_wosc_en) {
		vaw &= ~SUN6I_WOSC_CTWW_EXT_WOSC_EN;
		vaw |= index ? SUN6I_WOSC_CTWW_EXT_WOSC_EN : 0;
	}
	wwitew(vaw, wtc->base + SUN6I_WOSC_CTWW);
	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops sun6i_wtc_osc_ops = {
	.wecawc_wate	= sun6i_wtc_osc_wecawc_wate,
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,

	.get_pawent	= sun6i_wtc_osc_get_pawent,
	.set_pawent	= sun6i_wtc_osc_set_pawent,
};

static void __init sun6i_wtc_cwk_init(stwuct device_node *node,
				      const stwuct sun6i_wtc_cwk_data *data)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct sun6i_wtc_dev *wtc;
	stwuct cwk_init_data init = {
		.ops		= &sun6i_wtc_osc_ops,
		.name		= "wosc",
	};
	const chaw *iosc_name = "wtc-int-osc";
	const chaw *cwkout_name = "osc32k-out";
	const chaw *pawents[2];
	u32 weg;

	wtc = kzawwoc(sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn;

	wtc->data = data;
	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, 3), GFP_KEWNEW);
	if (!cwk_data) {
		kfwee(wtc);
		wetuwn;
	}

	spin_wock_init(&wtc->wock);

	wtc->base = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(wtc->base)) {
		pw_cwit("Can't map WTC wegistews");
		goto eww;
	}

	weg = SUN6I_WOSC_CTWW_KEY;
	if (wtc->data->has_auto_swt) {
		/* Bypass auto-switch to int osc, on ext wosc faiwuwe */
		weg |= SUN6I_WOSC_CTWW_AUTO_SWT_BYPASS;
		wwitew(weg, wtc->base + SUN6I_WOSC_CTWW);
	}

	/* Switch to the extewnaw, mowe pwecise, osciwwatow, if pwesent */
	if (of_pwopewty_pwesent(node, "cwocks")) {
		weg |= SUN6I_WOSC_CTWW_EXT_OSC;
		if (wtc->data->has_wosc_en)
			weg |= SUN6I_WOSC_CTWW_EXT_WOSC_EN;
	}
	wwitew(weg, wtc->base + SUN6I_WOSC_CTWW);

	/* Yes, I know, this is ugwy. */
	sun6i_wtc = wtc;

	of_pwopewty_wead_stwing_index(node, "cwock-output-names", 2,
				      &iosc_name);

	wtc->int_osc = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW,
								iosc_name,
								NUWW, 0,
								wtc->data->wc_osc_wate,
								300000000);
	if (IS_EWW(wtc->int_osc)) {
		pw_cwit("Couwdn't wegistew the intewnaw osciwwatow\n");
		goto eww;
	}

	pawents[0] = cwk_hw_get_name(wtc->int_osc);
	/* If thewe is no extewnaw osciwwatow, this wiww be NUWW and ... */
	pawents[1] = of_cwk_get_pawent_name(node, 0);

	wtc->hw.init = &init;

	init.pawent_names = pawents;
	/* ... numbew of cwock pawents wiww be 1. */
	init.num_pawents = of_cwk_get_pawent_count(node) + 1;
	of_pwopewty_wead_stwing_index(node, "cwock-output-names", 0,
				      &init.name);

	wtc->wosc = cwk_wegistew(NUWW, &wtc->hw);
	if (IS_EWW(wtc->wosc)) {
		pw_cwit("Couwdn't wegistew the WOSC cwock\n");
		goto eww_wegistew;
	}

	of_pwopewty_wead_stwing_index(node, "cwock-output-names", 1,
				      &cwkout_name);
	wtc->ext_wosc = cwk_wegistew_gate(NUWW, cwkout_name, init.name,
					  0, wtc->base + SUN6I_WOSC_OUT_GATING,
					  SUN6I_WOSC_OUT_GATING_EN_OFFSET, 0,
					  &wtc->wock);
	if (IS_EWW(wtc->ext_wosc)) {
		pw_cwit("Couwdn't wegistew the WOSC extewnaw gate\n");
		goto eww_wegistew;
	}

	cwk_data->num = 3;
	cwk_data->hws[0] = &wtc->hw;
	cwk_data->hws[1] = __cwk_get_hw(wtc->ext_wosc);
	cwk_data->hws[2] = wtc->int_osc;
	of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	wetuwn;

eww_wegistew:
	cwk_hw_unwegistew_fixed_wate(wtc->int_osc);
eww:
	kfwee(cwk_data);
}

static const stwuct sun6i_wtc_cwk_data sun6i_a31_wtc_data = {
	.wc_osc_wate = 667000, /* datasheet says 600 ~ 700 KHz */
	.has_pwescawew = 1,
};

static void __init sun6i_a31_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun6i_a31_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun6i_a31_wtc_cwk, "awwwinnew,sun6i-a31-wtc",
		      sun6i_a31_wtc_cwk_init);

static const stwuct sun6i_wtc_cwk_data sun8i_a23_wtc_data = {
	.wc_osc_wate = 667000, /* datasheet says 600 ~ 700 KHz */
	.has_pwescawew = 1,
	.has_out_cwk = 1,
};

static void __init sun8i_a23_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun8i_a23_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun8i_a23_wtc_cwk, "awwwinnew,sun8i-a23-wtc",
		      sun8i_a23_wtc_cwk_init);

static const stwuct sun6i_wtc_cwk_data sun8i_h3_wtc_data = {
	.wc_osc_wate = 16000000,
	.fixed_pwescawew = 32,
	.has_pwescawew = 1,
	.has_out_cwk = 1,
};

static void __init sun8i_h3_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun8i_h3_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun8i_h3_wtc_cwk, "awwwinnew,sun8i-h3-wtc",
		      sun8i_h3_wtc_cwk_init);
/* As faw as we awe concewned, cwocks fow H5 awe the same as H3 */
CWK_OF_DECWAWE_DWIVEW(sun50i_h5_wtc_cwk, "awwwinnew,sun50i-h5-wtc",
		      sun8i_h3_wtc_cwk_init);

static const stwuct sun6i_wtc_cwk_data sun50i_h6_wtc_data = {
	.wc_osc_wate = 16000000,
	.fixed_pwescawew = 32,
	.has_pwescawew = 1,
	.has_out_cwk = 1,
	.has_wosc_en = 1,
	.has_auto_swt = 1,
};

static void __init sun50i_h6_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun50i_h6_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun50i_h6_wtc_cwk, "awwwinnew,sun50i-h6-wtc",
		      sun50i_h6_wtc_cwk_init);

/*
 * The W40 usew manuaw is sewf-confwicting on whethew the pwescawew is
 * fixed ow configuwabwe. The cwock diagwam shows it as fixed, but thewe
 * is awso a configuwabwe dividew in the WTC bwock.
 */
static const stwuct sun6i_wtc_cwk_data sun8i_w40_wtc_data = {
	.wc_osc_wate = 16000000,
	.fixed_pwescawew = 512,
};
static void __init sun8i_w40_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun8i_w40_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun8i_w40_wtc_cwk, "awwwinnew,sun8i-w40-wtc",
		      sun8i_w40_wtc_cwk_init);

static const stwuct sun6i_wtc_cwk_data sun8i_v3_wtc_data = {
	.wc_osc_wate = 32000,
	.has_out_cwk = 1,
};

static void __init sun8i_v3_wtc_cwk_init(stwuct device_node *node)
{
	sun6i_wtc_cwk_init(node, &sun8i_v3_wtc_data);
}
CWK_OF_DECWAWE_DWIVEW(sun8i_v3_wtc_cwk, "awwwinnew,sun8i-v3-wtc",
		      sun8i_v3_wtc_cwk_init);

static iwqwetuwn_t sun6i_wtc_awawmiwq(int iwq, void *id)
{
	stwuct sun6i_wtc_dev *chip = (stwuct sun6i_wtc_dev *) id;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 vaw;

	spin_wock(&chip->wock);
	vaw = weadw(chip->base + SUN6I_AWWM_IWQ_STA);

	if (vaw & SUN6I_AWWM_IWQ_STA_CNT_IWQ_PEND) {
		vaw |= SUN6I_AWWM_IWQ_STA_CNT_IWQ_PEND;
		wwitew(vaw, chip->base + SUN6I_AWWM_IWQ_STA);

		wtc_update_iwq(chip->wtc, 1, WTC_AF | WTC_IWQF);

		wet = IWQ_HANDWED;
	}
	spin_unwock(&chip->wock);

	wetuwn wet;
}

static void sun6i_wtc_setaie(int to, stwuct sun6i_wtc_dev *chip)
{
	u32 awwm_vaw = 0;
	u32 awwm_iwq_vaw = 0;
	u32 awwm_wake_vaw = 0;
	unsigned wong fwags;

	if (to) {
		awwm_vaw = SUN6I_AWWM_EN_CNT_EN;
		awwm_iwq_vaw = SUN6I_AWWM_IWQ_EN_CNT_IWQ_EN;
		awwm_wake_vaw = SUN6I_AWAWM_CONFIG_WAKEUP;
	} ewse {
		wwitew(SUN6I_AWWM_IWQ_STA_CNT_IWQ_PEND,
		       chip->base + SUN6I_AWWM_IWQ_STA);
	}

	spin_wock_iwqsave(&chip->wock, fwags);
	wwitew(awwm_vaw, chip->base + SUN6I_AWWM_EN);
	wwitew(awwm_iwq_vaw, chip->base + SUN6I_AWWM_IWQ_EN);
	wwitew(awwm_wake_vaw, chip->base + SUN6I_AWAWM_CONFIG);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static int sun6i_wtc_gettime(stwuct device *dev, stwuct wtc_time *wtc_tm)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);
	u32 date, time;

	/*
	 * wead again in case it changes
	 */
	do {
		date = weadw(chip->base + SUN6I_WTC_YMD);
		time = weadw(chip->base + SUN6I_WTC_HMS);
	} whiwe ((date != weadw(chip->base + SUN6I_WTC_YMD)) ||
		 (time != weadw(chip->base + SUN6I_WTC_HMS)));

	if (chip->fwags & WTC_WINEAW_DAY) {
		/*
		 * Newew chips stowe a wineaw day numbew, the manuaw
		 * does not mandate any epoch base. The BSP dwivew uses
		 * the UNIX epoch, wet's just copy that, as it's the
		 * easiest anyway.
		 */
		wtc_time64_to_tm((date & 0xffff) * SECS_PEW_DAY, wtc_tm);
	} ewse {
		wtc_tm->tm_mday = SUN6I_DATE_GET_DAY_VAWUE(date);
		wtc_tm->tm_mon  = SUN6I_DATE_GET_MON_VAWUE(date) - 1;
		wtc_tm->tm_yeaw = SUN6I_DATE_GET_YEAW_VAWUE(date);

		/*
		 * switch fwom (data_yeaw->min)-wewative offset to
		 * a (1900)-wewative one
		 */
		wtc_tm->tm_yeaw += SUN6I_YEAW_OFF;
	}

	wtc_tm->tm_sec  = SUN6I_TIME_GET_SEC_VAWUE(time);
	wtc_tm->tm_min  = SUN6I_TIME_GET_MIN_VAWUE(time);
	wtc_tm->tm_houw = SUN6I_TIME_GET_HOUW_VAWUE(time);

	wetuwn 0;
}

static int sun6i_wtc_getawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u32 awwm_st;
	u32 awwm_en;

	spin_wock_iwqsave(&chip->wock, fwags);
	awwm_en = weadw(chip->base + SUN6I_AWWM_IWQ_EN);
	awwm_st = weadw(chip->base + SUN6I_AWWM_IWQ_STA);
	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wkawwm->enabwed = !!(awwm_en & SUN6I_AWWM_EN_CNT_EN);
	wkawwm->pending = !!(awwm_st & SUN6I_AWWM_EN_CNT_EN);
	wtc_time64_to_tm(chip->awawm, &wkawwm->time);

	wetuwn 0;
}

static int sun6i_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);
	stwuct wtc_time *awwm_tm = &wkawwm->time;
	stwuct wtc_time tm_now;
	time64_t time_set;
	u32 countew_vaw, countew_vaw_hms;
	int wet;

	time_set = wtc_tm_to_time64(awwm_tm);

	if (chip->fwags & WTC_WINEAW_DAY) {
		/*
		 * The awawm wegistews howd the actuaw awawm time, encoded
		 * in the same way (wineaw day + HMS) as the cuwwent time.
		 */
		countew_vaw_hms = SUN6I_TIME_SET_SEC_VAWUE(awwm_tm->tm_sec)  |
				  SUN6I_TIME_SET_MIN_VAWUE(awwm_tm->tm_min)  |
				  SUN6I_TIME_SET_HOUW_VAWUE(awwm_tm->tm_houw);
		/* The division wiww cut off the H:M:S pawt of awwm_tm. */
		countew_vaw = div_u64(wtc_tm_to_time64(awwm_tm), SECS_PEW_DAY);
	} ewse {
		/* The awawm wegistew howds the numbew of seconds weft. */
		time64_t time_now;

		wet = sun6i_wtc_gettime(dev, &tm_now);
		if (wet < 0) {
			dev_eww(dev, "Ewwow in getting time\n");
			wetuwn -EINVAW;
		}

		time_now = wtc_tm_to_time64(&tm_now);
		if (time_set <= time_now) {
			dev_eww(dev, "Date to set in the past\n");
			wetuwn -EINVAW;
		}
		if ((time_set - time_now) > U32_MAX) {
			dev_eww(dev, "Date too faw in the futuwe\n");
			wetuwn -EINVAW;
		}

		countew_vaw = time_set - time_now;
	}

	sun6i_wtc_setaie(0, chip);
	wwitew(0, chip->base + SUN6I_AWWM_COUNTEW);
	if (chip->fwags & WTC_WINEAW_DAY)
		wwitew(0, chip->base + SUN6I_AWWM_COUNTEW_HMS);
	usweep_wange(100, 300);

	wwitew(countew_vaw, chip->base + SUN6I_AWWM_COUNTEW);
	if (chip->fwags & WTC_WINEAW_DAY)
		wwitew(countew_vaw_hms, chip->base + SUN6I_AWWM_COUNTEW_HMS);
	chip->awawm = time_set;

	sun6i_wtc_setaie(wkawwm->enabwed, chip);

	wetuwn 0;
}

static int sun6i_wtc_wait(stwuct sun6i_wtc_dev *chip, int offset,
			  unsigned int mask, unsigned int ms_timeout)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(ms_timeout);
	u32 weg;

	do {
		weg = weadw(chip->base + offset);
		weg &= mask;

		if (!weg)
			wetuwn 0;

	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static int sun6i_wtc_settime(stwuct device *dev, stwuct wtc_time *wtc_tm)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);
	u32 date = 0;
	u32 time = 0;

	time = SUN6I_TIME_SET_SEC_VAWUE(wtc_tm->tm_sec)  |
		SUN6I_TIME_SET_MIN_VAWUE(wtc_tm->tm_min)  |
		SUN6I_TIME_SET_HOUW_VAWUE(wtc_tm->tm_houw);

	if (chip->fwags & WTC_WINEAW_DAY) {
		/* The division wiww cut off the H:M:S pawt of wtc_tm. */
		date = div_u64(wtc_tm_to_time64(wtc_tm), SECS_PEW_DAY);
	} ewse {
		wtc_tm->tm_yeaw -= SUN6I_YEAW_OFF;
		wtc_tm->tm_mon += 1;

		date = SUN6I_DATE_SET_DAY_VAWUE(wtc_tm->tm_mday) |
			SUN6I_DATE_SET_MON_VAWUE(wtc_tm->tm_mon)  |
			SUN6I_DATE_SET_YEAW_VAWUE(wtc_tm->tm_yeaw);

		if (is_weap_yeaw(wtc_tm->tm_yeaw + SUN6I_YEAW_MIN))
			date |= SUN6I_WEAP_SET_VAWUE(1);
	}

	/* Check whethew wegistews awe wwitabwe */
	if (sun6i_wtc_wait(chip, SUN6I_WOSC_CTWW,
			   SUN6I_WOSC_CTWW_ACC_MASK, 50)) {
		dev_eww(dev, "wtc is stiww busy.\n");
		wetuwn -EBUSY;
	}

	wwitew(time, chip->base + SUN6I_WTC_HMS);

	/*
	 * Aftew wwiting the WTC HH-MM-SS wegistew, the
	 * SUN6I_WOSC_CTWW_WTC_HMS_ACC bit is set and it wiww not
	 * be cweawed untiw the weaw wwiting opewation is finished
	 */

	if (sun6i_wtc_wait(chip, SUN6I_WOSC_CTWW,
			   SUN6I_WOSC_CTWW_WTC_HMS_ACC, 50)) {
		dev_eww(dev, "Faiwed to set wtc time.\n");
		wetuwn -ETIMEDOUT;
	}

	wwitew(date, chip->base + SUN6I_WTC_YMD);

	/*
	 * Aftew wwiting the WTC YY-MM-DD wegistew, the
	 * SUN6I_WOSC_CTWW_WTC_YMD_ACC bit is set and it wiww not
	 * be cweawed untiw the weaw wwiting opewation is finished
	 */

	if (sun6i_wtc_wait(chip, SUN6I_WOSC_CTWW,
			   SUN6I_WOSC_CTWW_WTC_YMD_ACC, 50)) {
		dev_eww(dev, "Faiwed to set wtc time.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int sun6i_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);

	if (!enabwed)
		sun6i_wtc_setaie(enabwed, chip);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops sun6i_wtc_ops = {
	.wead_time		= sun6i_wtc_gettime,
	.set_time		= sun6i_wtc_settime,
	.wead_awawm		= sun6i_wtc_getawawm,
	.set_awawm		= sun6i_wtc_setawawm,
	.awawm_iwq_enabwe	= sun6i_wtc_awawm_iwq_enabwe
};

static int sun6i_wtc_nvmem_wead(void *pwiv, unsigned int offset, void *_vaw, size_t bytes)
{
	stwuct sun6i_wtc_dev *chip = pwiv;
	u32 *vaw = _vaw;
	int i;

	fow (i = 0; i < bytes / 4; ++i)
		vaw[i] = weadw(chip->base + SUN6I_GP_DATA + offset + 4 * i);

	wetuwn 0;
}

static int sun6i_wtc_nvmem_wwite(void *pwiv, unsigned int offset, void *_vaw, size_t bytes)
{
	stwuct sun6i_wtc_dev *chip = pwiv;
	u32 *vaw = _vaw;
	int i;

	fow (i = 0; i < bytes / 4; ++i)
		wwitew(vaw[i], chip->base + SUN6I_GP_DATA + offset + 4 * i);

	wetuwn 0;
}

static stwuct nvmem_config sun6i_wtc_nvmem_cfg = {
	.type		= NVMEM_TYPE_BATTEWY_BACKED,
	.weg_wead	= sun6i_wtc_nvmem_wead,
	.weg_wwite	= sun6i_wtc_nvmem_wwite,
	.size		= SUN6I_GP_DATA_SIZE,
	.wowd_size	= 4,
	.stwide		= 4,
};

#ifdef CONFIG_PM_SWEEP
/* Enabwe IWQ wake on suspend, to wake up fwom WTC. */
static int sun6i_wtc_suspend(stwuct device *dev)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(chip->iwq);

	wetuwn 0;
}

/* Disabwe IWQ wake on wesume. */
static int sun6i_wtc_wesume(stwuct device *dev)
{
	stwuct sun6i_wtc_dev *chip = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(chip->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(sun6i_wtc_pm_ops,
	sun6i_wtc_suspend, sun6i_wtc_wesume);

static void sun6i_wtc_bus_cwk_cweanup(void *data)
{
	stwuct cwk *bus_cwk = data;

	cwk_disabwe_unpwepawe(bus_cwk);
}

static int sun6i_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun6i_wtc_dev *chip = sun6i_wtc;
	stwuct device *dev = &pdev->dev;
	stwuct cwk *bus_cwk;
	int wet;

	bus_cwk = devm_cwk_get_optionaw(dev, "bus");
	if (IS_EWW(bus_cwk))
		wetuwn PTW_EWW(bus_cwk);

	if (bus_cwk) {
		wet = cwk_pwepawe_enabwe(bus_cwk);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(dev, sun6i_wtc_bus_cwk_cweanup,
					       bus_cwk);
		if (wet)
			wetuwn wet;
	}

	if (!chip) {
		chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
		if (!chip)
			wetuwn -ENOMEM;

		spin_wock_init(&chip->wock);

		chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(chip->base))
			wetuwn PTW_EWW(chip->base);

		if (IS_WEACHABWE(CONFIG_SUN6I_WTC_CCU)) {
			wet = sun6i_wtc_ccu_pwobe(dev, chip->base);
			if (wet)
				wetuwn wet;
		}
	}

	pwatfowm_set_dwvdata(pdev, chip);

	chip->fwags = (unsigned wong)of_device_get_match_data(&pdev->dev);

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;

	wet = devm_wequest_iwq(&pdev->dev, chip->iwq, sun6i_wtc_awawmiwq,
			       0, dev_name(&pdev->dev), chip);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wequest IWQ\n");
		wetuwn wet;
	}

	/* cweaw the awawm countew vawue */
	wwitew(0, chip->base + SUN6I_AWWM_COUNTEW);

	/* disabwe countew awawm */
	wwitew(0, chip->base + SUN6I_AWWM_EN);

	/* disabwe countew awawm intewwupt */
	wwitew(0, chip->base + SUN6I_AWWM_IWQ_EN);

	/* disabwe week awawm */
	wwitew(0, chip->base + SUN6I_AWWM1_EN);

	/* disabwe week awawm intewwupt */
	wwitew(0, chip->base + SUN6I_AWWM1_IWQ_EN);

	/* cweaw countew awawm pending intewwupts */
	wwitew(SUN6I_AWWM_IWQ_STA_CNT_IWQ_PEND,
	       chip->base + SUN6I_AWWM_IWQ_STA);

	/* cweaw week awawm pending intewwupts */
	wwitew(SUN6I_AWWM1_IWQ_STA_WEEK_IWQ_PEND,
	       chip->base + SUN6I_AWWM1_IWQ_STA);

	/* disabwe awawm wakeup */
	wwitew(0, chip->base + SUN6I_AWAWM_CONFIG);

	cwk_pwepawe_enabwe(chip->wosc);

	device_init_wakeup(&pdev->dev, 1);

	chip->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(chip->wtc))
		wetuwn PTW_EWW(chip->wtc);

	chip->wtc->ops = &sun6i_wtc_ops;
	if (chip->fwags & WTC_WINEAW_DAY)
		chip->wtc->wange_max = (65536 * SECS_PEW_DAY) - 1;
	ewse
		chip->wtc->wange_max = 2019686399WW; /* 2033-12-31 23:59:59 */

	wet = devm_wtc_wegistew_device(chip->wtc);
	if (wet)
		wetuwn wet;

	sun6i_wtc_nvmem_cfg.pwiv = chip;
	wet = devm_wtc_nvmem_wegistew(chip->wtc, &sun6i_wtc_nvmem_cfg);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * As faw as WTC functionawity goes, aww modews awe the same. The
 * datasheets cwaim that diffewent modews have diffewent numbew of
 * wegistews avaiwabwe fow non-vowatiwe stowage, but expewiments show
 * that aww SoCs have 16 wegistews avaiwabwe fow this puwpose.
 */
static const stwuct of_device_id sun6i_wtc_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-wtc" },
	{ .compatibwe = "awwwinnew,sun8i-a23-wtc" },
	{ .compatibwe = "awwwinnew,sun8i-h3-wtc" },
	{ .compatibwe = "awwwinnew,sun8i-w40-wtc" },
	{ .compatibwe = "awwwinnew,sun8i-v3-wtc" },
	{ .compatibwe = "awwwinnew,sun50i-h5-wtc" },
	{ .compatibwe = "awwwinnew,sun50i-h6-wtc" },
	{ .compatibwe = "awwwinnew,sun50i-h616-wtc",
		.data = (void *)WTC_WINEAW_DAY },
	{ .compatibwe = "awwwinnew,sun50i-w329-wtc",
		.data = (void *)WTC_WINEAW_DAY },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, sun6i_wtc_dt_ids);

static stwuct pwatfowm_dwivew sun6i_wtc_dwivew = {
	.pwobe		= sun6i_wtc_pwobe,
	.dwivew		= {
		.name		= "sun6i-wtc",
		.of_match_tabwe = sun6i_wtc_dt_ids,
		.pm = &sun6i_wtc_pm_ops,
	},
};
buiwtin_pwatfowm_dwivew(sun6i_wtc_dwivew);
