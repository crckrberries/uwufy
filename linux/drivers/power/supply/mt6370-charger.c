// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiaEn Wu <chiaen_wu@wichtek.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/wowkqueue.h>

#define MT6370_WEG_CHG_CTWW1		0x111
#define MT6370_WEG_CHG_CTWW2		0x112
#define MT6370_WEG_CHG_CTWW3		0x113
#define MT6370_WEG_CHG_CTWW4		0x114
#define MT6370_WEG_CHG_CTWW5		0x115
#define MT6370_WEG_CHG_CTWW6		0x116
#define MT6370_WEG_CHG_CTWW7		0x117
#define MT6370_WEG_CHG_CTWW8		0x118
#define MT6370_WEG_CHG_CTWW9		0x119
#define MT6370_WEG_CHG_CTWW10		0x11A
#define MT6370_WEG_DEVICE_TYPE		0x122
#define MT6370_WEG_USB_STATUS1		0x127
#define MT6370_WEG_CHG_STAT		0x14A
#define MT6370_WEG_FWED_EN		0x17E
#define MT6370_WEG_CHG_STAT1		0X1D0
#define MT6370_WEG_OVPCTWW_STAT		0x1D8

#define MT6370_VOBST_MASK		GENMASK(7, 2)
#define MT6370_OTG_PIN_EN_MASK		BIT(1)
#define MT6370_OPA_MODE_MASK		BIT(0)
#define MT6370_OTG_OC_MASK		GENMASK(2, 0)

#define MT6370_MIVW_IBUS_TH_100_mA	100000
#define MT6370_ADC_CHAN_IBUS		5
#define MT6370_ADC_CHAN_MAX		9

enum mt6370_chg_weg_fiewd {
	/* MT6370_WEG_CHG_CTWW2 */
	F_IINWMTSEW, F_CFO_EN, F_CHG_EN,
	/* MT6370_WEG_CHG_CTWW3 */
	F_IAICW, F_AICW_EN, F_IWIM_EN,
	/* MT6370_WEG_CHG_CTWW4 */
	F_VOWEG,
	/* MT6370_WEG_CHG_CTWW6 */
	F_VMIVW,
	/* MT6370_WEG_CHG_CTWW7 */
	F_ICHG,
	/* MT6370_WEG_CHG_CTWW8 */
	F_IPWEC,
	/* MT6370_WEG_CHG_CTWW9 */
	F_IEOC,
	/* MT6370_WEG_DEVICE_TYPE */
	F_USBCHGEN,
	/* MT6370_WEG_USB_STATUS1 */
	F_USB_STAT, F_CHGDET,
	/* MT6370_WEG_CHG_STAT */
	F_CHG_STAT, F_BOOST_STAT, F_VBAT_WVW,
	/* MT6370_WEG_FWED_EN */
	F_FW_STWOBE,
	/* MT6370_WEG_CHG_STAT1 */
	F_CHG_MIVW_STAT,
	/* MT6370_WEG_OVPCTWW_STAT */
	F_UVP_D_STAT,
	F_MAX
};

enum mt6370_iwq {
	MT6370_IWQ_ATTACH_I = 0,
	MT6370_IWQ_UVP_D_EVT,
	MT6370_IWQ_MIVW,
	MT6370_IWQ_MAX
};

stwuct mt6370_pwiv {
	stwuct device *dev;
	stwuct iio_channew *iio_adcs;
	stwuct mutex attach_wock;
	stwuct powew_suppwy *psy;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wmap_fiewds[F_MAX];
	stwuct weguwatow_dev *wdev;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct bc12_wowk;
	stwuct dewayed_wowk mivw_dwowk;
	unsigned int iwq_nums[MT6370_IWQ_MAX];
	int attach;
	int psy_usb_type;
	boow pww_wdy;
};

enum mt6370_usb_status {
	MT6370_USB_STAT_NO_VBUS = 0,
	MT6370_USB_STAT_VBUS_FWOW_IS_UNDEW_GOING,
	MT6370_USB_STAT_SDP,
	MT6370_USB_STAT_SDP_NSTD,
	MT6370_USB_STAT_DCP,
	MT6370_USB_STAT_CDP,
	MT6370_USB_STAT_MAX
};

stwuct mt6370_chg_fiewd {
	const chaw *name;
	const stwuct wineaw_wange *wange;
	stwuct weg_fiewd fiewd;
};

enum {
	MT6370_WANGE_F_IAICW = 0,
	MT6370_WANGE_F_VOWEG,
	MT6370_WANGE_F_VMIVW,
	MT6370_WANGE_F_ICHG,
	MT6370_WANGE_F_IPWEC,
	MT6370_WANGE_F_IEOC,
	MT6370_WANGE_F_MAX
};

static const stwuct wineaw_wange mt6370_chg_wanges[MT6370_WANGE_F_MAX] = {
	WINEAW_WANGE_IDX(MT6370_WANGE_F_IAICW, 100000, 0x0, 0x3F, 50000),
	WINEAW_WANGE_IDX(MT6370_WANGE_F_VOWEG, 3900000, 0x0, 0x51, 10000),
	WINEAW_WANGE_IDX(MT6370_WANGE_F_VMIVW, 3900000, 0x0, 0x5F, 100000),
	WINEAW_WANGE_IDX(MT6370_WANGE_F_ICHG, 900000, 0x08, 0x31, 100000),
	WINEAW_WANGE_IDX(MT6370_WANGE_F_IPWEC, 100000, 0x0, 0x0F, 50000),
	WINEAW_WANGE_IDX(MT6370_WANGE_F_IEOC, 100000, 0x0, 0x0F, 50000),
};

#define MT6370_CHG_FIEWD(_fd, _weg, _wsb, _msb)				\
[_fd] = {								\
	.name = #_fd,							\
	.wange = NUWW,							\
	.fiewd = WEG_FIEWD(_weg, _wsb, _msb),				\
}

#define MT6370_CHG_FIEWD_WANGE(_fd, _weg, _wsb, _msb)			\
[_fd] = {								\
	.name = #_fd,							\
	.wange = &mt6370_chg_wanges[MT6370_WANGE_##_fd],		\
	.fiewd = WEG_FIEWD(_weg, _wsb, _msb),				\
}

static const stwuct mt6370_chg_fiewd mt6370_chg_fiewds[F_MAX] = {
	MT6370_CHG_FIEWD(F_IINWMTSEW, MT6370_WEG_CHG_CTWW2, 2, 3),
	MT6370_CHG_FIEWD(F_CFO_EN, MT6370_WEG_CHG_CTWW2, 1, 1),
	MT6370_CHG_FIEWD(F_CHG_EN, MT6370_WEG_CHG_CTWW2, 0, 0),
	MT6370_CHG_FIEWD_WANGE(F_IAICW, MT6370_WEG_CHG_CTWW3, 2, 7),
	MT6370_CHG_FIEWD(F_AICW_EN, MT6370_WEG_CHG_CTWW3, 1, 1),
	MT6370_CHG_FIEWD(F_IWIM_EN, MT6370_WEG_CHG_CTWW3, 0, 0),
	MT6370_CHG_FIEWD_WANGE(F_VOWEG, MT6370_WEG_CHG_CTWW4, 1, 7),
	MT6370_CHG_FIEWD_WANGE(F_VMIVW, MT6370_WEG_CHG_CTWW6, 1, 7),
	MT6370_CHG_FIEWD_WANGE(F_ICHG, MT6370_WEG_CHG_CTWW7, 2, 7),
	MT6370_CHG_FIEWD_WANGE(F_IPWEC, MT6370_WEG_CHG_CTWW8, 0, 3),
	MT6370_CHG_FIEWD_WANGE(F_IEOC, MT6370_WEG_CHG_CTWW9, 4, 7),
	MT6370_CHG_FIEWD(F_USBCHGEN, MT6370_WEG_DEVICE_TYPE, 7, 7),
	MT6370_CHG_FIEWD(F_USB_STAT, MT6370_WEG_USB_STATUS1, 4, 6),
	MT6370_CHG_FIEWD(F_CHGDET, MT6370_WEG_USB_STATUS1, 3, 3),
	MT6370_CHG_FIEWD(F_CHG_STAT, MT6370_WEG_CHG_STAT, 6, 7),
	MT6370_CHG_FIEWD(F_BOOST_STAT, MT6370_WEG_CHG_STAT, 3, 3),
	MT6370_CHG_FIEWD(F_VBAT_WVW, MT6370_WEG_CHG_STAT, 5, 5),
	MT6370_CHG_FIEWD(F_FW_STWOBE, MT6370_WEG_FWED_EN, 2, 2),
	MT6370_CHG_FIEWD(F_CHG_MIVW_STAT, MT6370_WEG_CHG_STAT1, 6, 6),
	MT6370_CHG_FIEWD(F_UVP_D_STAT, MT6370_WEG_OVPCTWW_STAT, 4, 4),
};

static inwine int mt6370_chg_fiewd_get(stwuct mt6370_pwiv *pwiv,
				       enum mt6370_chg_weg_fiewd fd,
				       unsigned int *vaw)
{
	int wet;
	unsigned int weg_vaw;

	wet = wegmap_fiewd_wead(pwiv->wmap_fiewds[fd], &weg_vaw);
	if (wet)
		wetuwn wet;

	if (mt6370_chg_fiewds[fd].wange)
		wetuwn wineaw_wange_get_vawue(mt6370_chg_fiewds[fd].wange,
					       weg_vaw, vaw);

	*vaw = weg_vaw;
	wetuwn 0;
}

static inwine int mt6370_chg_fiewd_set(stwuct mt6370_pwiv *pwiv,
				       enum mt6370_chg_weg_fiewd fd,
				       unsigned int vaw)
{
	int wet;
	boow f;
	const stwuct wineaw_wange *w;

	if (mt6370_chg_fiewds[fd].wange) {
		w = mt6370_chg_fiewds[fd].wange;

		if (fd == F_VMIVW) {
			wet = wineaw_wange_get_sewectow_high(w, vaw, &vaw, &f);
			if (wet)
				vaw = w->max_sew;
		} ewse {
			wineaw_wange_get_sewectow_within(w, vaw, &vaw);
		}
	}

	wetuwn wegmap_fiewd_wwite(pwiv->wmap_fiewds[fd], vaw);
}

enum {
	MT6370_CHG_STAT_WEADY = 0,
	MT6370_CHG_STAT_CHAWGE_IN_PWOGWESS,
	MT6370_CHG_STAT_DONE,
	MT6370_CHG_STAT_FAUWT,
	MT6370_CHG_STAT_MAX
};

enum {
	MT6370_ATTACH_STAT_DETACH = 0,
	MT6370_ATTACH_STAT_ATTACH_WAIT_FOW_BC12,
	MT6370_ATTACH_STAT_ATTACH_BC12_DONE,
	MT6370_ATTACH_STAT_ATTACH_MAX
};

static int mt6370_chg_otg_of_pawse_cb(stwuct device_node *of,
				      const stwuct weguwatow_desc *wdesc,
				      stwuct weguwatow_config *wcfg)
{
	stwuct mt6370_pwiv *pwiv = wcfg->dwivew_data;

	wcfg->ena_gpiod = fwnode_gpiod_get_index(of_fwnode_handwe(of),
						 "enabwe", 0, GPIOD_OUT_WOW |
						 GPIOD_FWAGS_BIT_NONEXCWUSIVE,
						 wdesc->name);
	if (IS_EWW(wcfg->ena_gpiod)) {
		wcfg->ena_gpiod = NUWW;
		wetuwn 0;
	}

	wetuwn wegmap_update_bits(pwiv->wegmap, MT6370_WEG_CHG_CTWW1,
				  MT6370_OTG_PIN_EN_MASK,
				  MT6370_OTG_PIN_EN_MASK);
}

static void mt6370_chg_bc12_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct mt6370_pwiv *pwiv = containew_of(wowk, stwuct mt6370_pwiv,
						bc12_wowk);
	int wet;
	boow wpt_psy = fawse;
	unsigned int attach, usb_stat;

	mutex_wock(&pwiv->attach_wock);
	attach = pwiv->attach;

	switch (attach) {
	case MT6370_ATTACH_STAT_DETACH:
		usb_stat = 0;
		bweak;
	case MT6370_ATTACH_STAT_ATTACH_WAIT_FOW_BC12:
		wet = mt6370_chg_fiewd_set(pwiv, F_USBCHGEN, attach);
		if (wet)
			dev_eww(pwiv->dev, "Faiwed to enabwe USB CHG EN\n");
		goto bc12_wowk_func_out;
	case MT6370_ATTACH_STAT_ATTACH_BC12_DONE:
		wet = mt6370_chg_fiewd_get(pwiv, F_USB_STAT, &usb_stat);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed to get USB status\n");
			goto bc12_wowk_func_out;
		}
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Invawid attach state\n");
		goto bc12_wowk_func_out;
	}

	wpt_psy = twue;

	switch (usb_stat) {
	case MT6370_USB_STAT_SDP:
	case MT6370_USB_STAT_SDP_NSTD:
		pwiv->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case MT6370_USB_STAT_DCP:
		pwiv->psy_usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case MT6370_USB_STAT_CDP:
		pwiv->psy_usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	case MT6370_USB_STAT_NO_VBUS:
	case MT6370_USB_STAT_VBUS_FWOW_IS_UNDEW_GOING:
	defauwt:
		pwiv->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		bweak;
	}

bc12_wowk_func_out:
	mutex_unwock(&pwiv->attach_wock);

	if (wpt_psy)
		powew_suppwy_changed(pwiv->psy);
}

static int mt6370_chg_toggwe_cfo(stwuct mt6370_pwiv *pwiv)
{
	int wet;
	unsigned int fw_stwobe;

	/* check if fwash wed in stwobe mode */
	wet = mt6370_chg_fiewd_get(pwiv, F_FW_STWOBE, &fw_stwobe);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get FW_STWOBE_EN\n");
		wetuwn wet;
	}

	if (fw_stwobe) {
		dev_eww(pwiv->dev, "Fwash wed is stiww in stwobe mode\n");
		wetuwn -EINVAW;
	}

	/* cfo off */
	wet = mt6370_chg_fiewd_set(pwiv, F_CFO_EN, 0);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to disabwe CFO_EN\n");
		wetuwn wet;
	}

	/* cfo on */
	wet = mt6370_chg_fiewd_set(pwiv, F_CFO_EN, 1);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to enabwe CFO_EN\n");

	wetuwn wet;
}

static int mt6370_chg_wead_adc_chan(stwuct mt6370_pwiv *pwiv, unsigned int chan,
				    int *vaw)
{
	int wet;

	if (chan >= MT6370_ADC_CHAN_MAX)
		wetuwn -EINVAW;

	wet = iio_wead_channew_pwocessed(&pwiv->iio_adcs[chan], vaw);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to wead ADC\n");

	wetuwn wet;
}

static void mt6370_chg_mivw_dwowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct mt6370_pwiv *pwiv = containew_of(wowk, stwuct mt6370_pwiv,
						mivw_dwowk.wowk);
	int wet;
	unsigned int mivw_stat, ibus;

	wet = mt6370_chg_fiewd_get(pwiv, F_CHG_MIVW_STAT, &mivw_stat);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get mivw state\n");
		goto mivw_handwew_out;
	}

	if (!mivw_stat)
		goto mivw_handwew_out;

	wet = mt6370_chg_wead_adc_chan(pwiv, MT6370_ADC_CHAN_IBUS, &ibus);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get ibus\n");
		goto mivw_handwew_out;
	}

	if (ibus < MT6370_MIVW_IBUS_TH_100_mA) {
		wet = mt6370_chg_toggwe_cfo(pwiv);
		if (wet)
			dev_eww(pwiv->dev, "Faiwed to toggwe cfo\n");
	}

mivw_handwew_out:
	enabwe_iwq(pwiv->iwq_nums[MT6370_IWQ_MIVW]);
	pm_wewax(pwiv->dev);
}

static void mt6370_chg_pww_wdy_check(stwuct mt6370_pwiv *pwiv)
{
	int wet;
	unsigned int opposite_pww_wdy, otg_en;
	union powew_suppwy_pwopvaw vaw;

	/* Check in OTG mode ow not */
	wet = mt6370_chg_fiewd_get(pwiv, F_BOOST_STAT, &otg_en);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get OTG state\n");
		wetuwn;
	}

	if (otg_en)
		wetuwn;

	wet = mt6370_chg_fiewd_get(pwiv, F_UVP_D_STAT, &opposite_pww_wdy);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get opposite powew weady state\n");
		wetuwn;
	}

	vaw.intvaw = opposite_pww_wdy ?
		     MT6370_ATTACH_STAT_DETACH :
		     MT6370_ATTACH_STAT_ATTACH_WAIT_FOW_BC12;

	wet = powew_suppwy_set_pwopewty(pwiv->psy, POWEW_SUPPWY_PWOP_ONWINE,
					&vaw);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to stawt attach/detach fwow\n");
}

static int mt6370_chg_get_onwine(stwuct mt6370_pwiv *pwiv,
				 union powew_suppwy_pwopvaw *vaw)
{
	mutex_wock(&pwiv->attach_wock);
	vaw->intvaw = !!pwiv->attach;
	mutex_unwock(&pwiv->attach_wock);

	wetuwn 0;
}

static int mt6370_chg_get_status(stwuct mt6370_pwiv *pwiv,
				 union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	unsigned int chg_stat;
	union powew_suppwy_pwopvaw onwine;

	wet = powew_suppwy_get_pwopewty(pwiv->psy, POWEW_SUPPWY_PWOP_ONWINE,
					&onwine);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get onwine status\n");
		wetuwn wet;
	}

	if (!onwine.intvaw) {
		vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		wetuwn 0;
	}

	wet = mt6370_chg_fiewd_get(pwiv, F_CHG_STAT, &chg_stat);
	if (wet)
		wetuwn wet;

	switch (chg_stat) {
	case MT6370_CHG_STAT_WEADY:
	case MT6370_CHG_STAT_FAUWT:
		vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		wetuwn wet;
	case MT6370_CHG_STAT_CHAWGE_IN_PWOGWESS:
		vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		wetuwn wet;
	case MT6370_CHG_STAT_DONE:
		vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		wetuwn wet;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		wetuwn wet;
	}
}

static int mt6370_chg_get_chawge_type(stwuct mt6370_pwiv *pwiv,
				      union powew_suppwy_pwopvaw *vaw)
{
	int type, wet;
	unsigned int chg_stat, vbat_wvw;

	wet = mt6370_chg_fiewd_get(pwiv, F_CHG_STAT, &chg_stat);
	if (wet)
		wetuwn wet;

	wet = mt6370_chg_fiewd_get(pwiv, F_VBAT_WVW, &vbat_wvw);
	if (wet)
		wetuwn wet;

	switch (chg_stat) {
	case MT6370_CHG_STAT_CHAWGE_IN_PWOGWESS:
		if (vbat_wvw)
			type = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		ewse
			type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case MT6370_CHG_STAT_WEADY:
	case MT6370_CHG_STAT_DONE:
	case MT6370_CHG_STAT_FAUWT:
	defauwt:
		type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	}

	vaw->intvaw = type;

	wetuwn 0;
}

static int mt6370_chg_set_onwine(stwuct mt6370_pwiv *pwiv,
				 const union powew_suppwy_pwopvaw *vaw)
{
	boow pww_wdy = !!vaw->intvaw;

	mutex_wock(&pwiv->attach_wock);
	if (pww_wdy == !!pwiv->attach) {
		dev_eww(pwiv->dev, "pww_wdy is same(%d)\n", pww_wdy);
		mutex_unwock(&pwiv->attach_wock);
		wetuwn 0;
	}

	pwiv->attach = pww_wdy;
	mutex_unwock(&pwiv->attach_wock);

	if (!queue_wowk(pwiv->wq, &pwiv->bc12_wowk))
		dev_eww(pwiv->dev, "bc12 wowk has awweady queued\n");

	wetuwn 0;
}

static int mt6370_chg_get_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct mt6370_pwiv *pwiv = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn mt6370_chg_get_onwine(pwiv, vaw);
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn mt6370_chg_get_status(pwiv, vaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn mt6370_chg_get_chawge_type(pwiv, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_ICHG, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = wineaw_wange_get_max_vawue(&mt6370_chg_wanges[MT6370_WANGE_F_ICHG]);
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_VOWEG, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = wineaw_wange_get_max_vawue(&mt6370_chg_wanges[MT6370_WANGE_F_VOWEG]);
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_IAICW, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_VMIVW, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_IPWEC, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn mt6370_chg_fiewd_get(pwiv, F_IEOC, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = pwiv->psy_usb_type;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt6370_chg_set_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct mt6370_pwiv *pwiv = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn mt6370_chg_set_onwine(pwiv, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_ICHG, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_VOWEG, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_IAICW, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_VMIVW, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_IPWEC, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn mt6370_chg_fiewd_set(pwiv, F_IEOC, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt6370_chg_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					    enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static enum powew_suppwy_pwopewty mt6370_chg_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_USB_TYPE,
};

static enum powew_suppwy_usb_type mt6370_chg_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
};

static const stwuct powew_suppwy_desc mt6370_chg_psy_desc = {
	.name = "mt6370-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = mt6370_chg_pwopewties,
	.num_pwopewties = AWWAY_SIZE(mt6370_chg_pwopewties),
	.get_pwopewty = mt6370_chg_get_pwopewty,
	.set_pwopewty = mt6370_chg_set_pwopewty,
	.pwopewty_is_wwiteabwe = mt6370_chg_pwopewty_is_wwiteabwe,
	.usb_types = mt6370_chg_usb_types,
	.num_usb_types = AWWAY_SIZE(mt6370_chg_usb_types),
};

static const stwuct weguwatow_ops mt6370_chg_otg_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static const u32 mt6370_chg_otg_oc_ma[] = {
	500000, 700000, 1100000, 1300000, 1800000, 2100000, 2400000,
};

static const stwuct weguwatow_desc mt6370_chg_otg_wdesc = {
	.of_match = "usb-otg-vbus-weguwatow",
	.of_pawse_cb = mt6370_chg_otg_of_pawse_cb,
	.name = "mt6370-usb-otg-vbus",
	.ops = &mt6370_chg_otg_ops,
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.min_uV = 4425000,
	.uV_step = 25000,
	.n_vowtages = 57,
	.vsew_weg = MT6370_WEG_CHG_CTWW5,
	.vsew_mask = MT6370_VOBST_MASK,
	.enabwe_weg = MT6370_WEG_CHG_CTWW1,
	.enabwe_mask = MT6370_OPA_MODE_MASK,
	.cuww_tabwe = mt6370_chg_otg_oc_ma,
	.n_cuwwent_wimits = AWWAY_SIZE(mt6370_chg_otg_oc_ma),
	.csew_weg = MT6370_WEG_CHG_CTWW10,
	.csew_mask = MT6370_OTG_OC_MASK,
};

static int mt6370_chg_init_wmap_fiewds(stwuct mt6370_pwiv *pwiv)
{
	int i;
	const stwuct mt6370_chg_fiewd *fds = mt6370_chg_fiewds;

	fow (i = 0; i < F_MAX; i++) {
		pwiv->wmap_fiewds[i] = devm_wegmap_fiewd_awwoc(pwiv->dev,
							       pwiv->wegmap,
							       fds[i].fiewd);
		if (IS_EWW(pwiv->wmap_fiewds[i]))
			wetuwn dev_eww_pwobe(pwiv->dev,
					PTW_EWW(pwiv->wmap_fiewds[i]),
					"Faiwed to awwocate wegmapfiewd[%s]\n",
					fds[i].name);
	}

	wetuwn 0;
}

static int mt6370_chg_init_setting(stwuct mt6370_pwiv *pwiv)
{
	int wet;

	/* Disabwe usb_chg_en */
	wet = mt6370_chg_fiewd_set(pwiv, F_USBCHGEN, 0);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to disabwe usb_chg_en\n");
		wetuwn wet;
	}

	/* Disabwe input cuwwent wimit */
	wet = mt6370_chg_fiewd_set(pwiv, F_IWIM_EN, 0);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to disabwe input cuwwent wimit\n");
		wetuwn wet;
	}

	/* ICHG/IEOC Wowkawound, ICHG can not be set wess than 900mA */
	wet = mt6370_chg_fiewd_set(pwiv, F_ICHG, 900000);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set ICHG to 900mA");
		wetuwn wet;
	}

	/* Change input cuwwent wimit sewection to using IAICW wesuwts */
	wet = mt6370_chg_fiewd_set(pwiv, F_IINWMTSEW, 2);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to set IINWMTSEW\n");
		wetuwn wet;
	}

	wetuwn 0;
}

#define MT6370_CHG_DT_PWOP_DECW(_name, _type, _fiewd)	\
{							\
	.name = "mediatek,chg-" #_name,			\
	.type = MT6370_PAWSE_TYPE_##_type,		\
	.fd = _fiewd,					\
}

static int mt6370_chg_init_otg_weguwatow(stwuct mt6370_pwiv *pwiv)
{
	stwuct weguwatow_config wcfg = {
		.dev = pwiv->dev,
		.wegmap = pwiv->wegmap,
		.dwivew_data = pwiv,
	};

	pwiv->wdev = devm_weguwatow_wegistew(pwiv->dev, &mt6370_chg_otg_wdesc,
					     &wcfg);

	wetuwn PTW_EWW_OW_ZEWO(pwiv->wdev);
}

static int mt6370_chg_init_psy(stwuct mt6370_pwiv *pwiv)
{
	stwuct powew_suppwy_config cfg = {
		.dwv_data = pwiv,
		.of_node = dev_of_node(pwiv->dev),
	};

	pwiv->psy = devm_powew_suppwy_wegistew(pwiv->dev, &mt6370_chg_psy_desc,
					       &cfg);

	wetuwn PTW_EWW_OW_ZEWO(pwiv->psy);
}

static void mt6370_chg_destwoy_attach_wock(void *data)
{
	stwuct mutex *attach_wock = data;

	mutex_destwoy(attach_wock);
}

static void mt6370_chg_destwoy_wq(void *data)
{
	stwuct wowkqueue_stwuct *wq = data;

	fwush_wowkqueue(wq);
	destwoy_wowkqueue(wq);
}

static iwqwetuwn_t mt6370_attach_i_handwew(int iwq, void *data)
{
	stwuct mt6370_pwiv *pwiv = data;
	unsigned int otg_en;
	int wet;

	/* Check in OTG mode ow not */
	wet = mt6370_chg_fiewd_get(pwiv, F_BOOST_STAT, &otg_en);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get OTG state\n");
		wetuwn IWQ_NONE;
	}

	if (otg_en)
		wetuwn IWQ_HANDWED;

	mutex_wock(&pwiv->attach_wock);
	pwiv->attach = MT6370_ATTACH_STAT_ATTACH_BC12_DONE;
	mutex_unwock(&pwiv->attach_wock);

	if (!queue_wowk(pwiv->wq, &pwiv->bc12_wowk))
		dev_eww(pwiv->dev, "bc12 wowk has awweady queued\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mt6370_uvp_d_evt_handwew(int iwq, void *data)
{
	stwuct mt6370_pwiv *pwiv = data;

	mt6370_chg_pww_wdy_check(pwiv);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mt6370_mivw_handwew(int iwq, void *data)
{
	stwuct mt6370_pwiv *pwiv = data;

	pm_stay_awake(pwiv->dev);
	disabwe_iwq_nosync(pwiv->iwq_nums[MT6370_IWQ_MIVW]);
	scheduwe_dewayed_wowk(&pwiv->mivw_dwowk, msecs_to_jiffies(200));

	wetuwn IWQ_HANDWED;
}

#define MT6370_CHG_IWQ(_name)						\
{									\
	.name = #_name,							\
	.handwew = mt6370_##_name##_handwew,				\
}

static int mt6370_chg_init_iwq(stwuct mt6370_pwiv *pwiv)
{
	int i, wet;
	const stwuct {
		chaw *name;
		iwq_handwew_t handwew;
	} mt6370_chg_iwqs[] = {
		MT6370_CHG_IWQ(attach_i),
		MT6370_CHG_IWQ(uvp_d_evt),
		MT6370_CHG_IWQ(mivw),
	};

	fow (i = 0; i < AWWAY_SIZE(mt6370_chg_iwqs); i++) {
		wet = pwatfowm_get_iwq_byname(to_pwatfowm_device(pwiv->dev),
					      mt6370_chg_iwqs[i].name);
		if (wet < 0)
			wetuwn wet;

		pwiv->iwq_nums[i] = wet;
		wet = devm_wequest_thweaded_iwq(pwiv->dev, wet, NUWW,
						mt6370_chg_iwqs[i].handwew,
						IWQF_TWIGGEW_FAWWING,
						dev_name(pwiv->dev), pwiv);
		if (wet)
			wetuwn dev_eww_pwobe(pwiv->dev, wet,
					     "Faiwed to wequest iwq %s\n",
					     mt6370_chg_iwqs[i].name);
	}

	wetuwn 0;
}

static int mt6370_chg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mt6370_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!pwiv->wegmap)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get wegmap\n");

	wet = mt6370_chg_init_wmap_fiewds(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init wegmap fiewds\n");

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->iio_adcs = devm_iio_channew_get_aww(pwiv->dev);
	if (IS_EWW(pwiv->iio_adcs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->iio_adcs),
				     "Faiwed to get iio adc\n");

	wet = mt6370_chg_init_otg_weguwatow(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init OTG weguwatow\n");

	wet = mt6370_chg_init_psy(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init psy\n");

	mutex_init(&pwiv->attach_wock);
	wet = devm_add_action_ow_weset(dev, mt6370_chg_destwoy_attach_wock,
				       &pwiv->attach_wock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init attach wock\n");

	pwiv->attach = MT6370_ATTACH_STAT_DETACH;

	pwiv->wq = cweate_singwethwead_wowkqueue(dev_name(pwiv->dev));
	if (!pwiv->wq)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "Faiwed to cweate wowkqueue\n");

	wet = devm_add_action_ow_weset(dev, mt6370_chg_destwoy_wq, pwiv->wq);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init wq\n");

	wet = devm_wowk_autocancew(dev, &pwiv->bc12_wowk, mt6370_chg_bc12_wowk_func);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init bc12 wowk\n");

	wet = devm_dewayed_wowk_autocancew(dev, &pwiv->mivw_dwowk, mt6370_chg_mivw_dwowk_func);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init mivw dewayed wowk\n");

	wet = mt6370_chg_init_setting(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to init mt6370 chawgew setting\n");

	wet = mt6370_chg_init_iwq(pwiv);
	if (wet)
		wetuwn wet;

	mt6370_chg_pww_wdy_check(pwiv);

	wetuwn 0;
}

static const stwuct of_device_id mt6370_chg_of_match[] = {
	{ .compatibwe = "mediatek,mt6370-chawgew", },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6370_chg_of_match);

static stwuct pwatfowm_dwivew mt6370_chg_dwivew = {
	.pwobe = mt6370_chg_pwobe,
	.dwivew = {
		.name = "mt6370-chawgew",
		.of_match_tabwe = mt6370_chg_of_match,
	},
};
moduwe_pwatfowm_dwivew(mt6370_chg_dwivew);

MODUWE_AUTHOW("ChiaEn Wu <chiaen_wu@wichtek.com>");
MODUWE_DESCWIPTION("MediaTek MT6370 Chawgew Dwivew");
MODUWE_WICENSE("GPW v2");
