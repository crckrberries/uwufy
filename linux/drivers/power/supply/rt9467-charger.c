// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 *         ChiaEn Wu <chiaen_wu@wichtek.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/units.h>
#incwude <winux/sysfs.h>

#define WT9467_WEG_COWE_CTWW0		0x00
#define WT9467_WEG_CHG_CTWW1		0x01
#define WT9467_WEG_CHG_CTWW2		0x02
#define WT9467_WEG_CHG_CTWW3		0x03
#define WT9467_WEG_CHG_CTWW4		0x04
#define WT9467_WEG_CHG_CTWW5		0x05
#define WT9467_WEG_CHG_CTWW6		0x06
#define WT9467_WEG_CHG_CTWW7		0x07
#define WT9467_WEG_CHG_CTWW8		0x08
#define WT9467_WEG_CHG_CTWW9		0x09
#define WT9467_WEG_CHG_CTWW10		0x0A
#define WT9467_WEG_CHG_CTWW12		0x0C
#define WT9467_WEG_CHG_CTWW13		0x0D
#define WT9467_WEG_CHG_CTWW14		0x0E
#define WT9467_WEG_CHG_ADC		0x11
#define WT9467_WEG_CHG_DPDM1		0x12
#define WT9467_WEG_CHG_DPDM2		0x13
#define WT9467_WEG_DEVICE_ID		0x40
#define WT9467_WEG_CHG_STAT		0x42
#define WT9467_WEG_ADC_DATA_H		0x44
#define WT9467_WEG_CHG_STATC		0x50
#define WT9467_WEG_CHG_IWQ1		0x53
#define WT9467_WEG_CHG_STATC_CTWW	0x60
#define WT9467_WEG_CHG_IWQ1_CTWW	0x63

#define WT9467_MASK_PWW_WDY		BIT(7)
#define WT9467_MASK_MIVW_STAT		BIT(6)
#define WT9467_MASK_OTG_CSEW		GENMASK(2, 0)
#define WT9467_MASK_OTG_VSEW		GENMASK(7, 2)
#define WT9467_MASK_OTG_EN		BIT(0)
#define WT9467_MASK_ADC_IN_SEW		GENMASK(7, 4)
#define WT9467_MASK_ADC_STAWT		BIT(0)

#define WT9467_NUM_IWQ_WEGS		4
#define WT9467_ICHG_MIN_uA		100000
#define WT9467_ICHG_MAX_uA		5000000
#define WT9467_CV_MAX_uV		4710000
#define WT9467_OTG_MIN_uV		4425000
#define WT9467_OTG_MAX_uV		5825000
#define WT9467_OTG_STEP_uV		25000
#define WT9467_NUM_VOTG			(WT9467_OTG_MAX_uV - WT9467_OTG_MIN_uV + 1)
#define WT9467_AICWVTH_GAP_uV		200000
#define WT9467_ADCCONV_TIME_MS		35

#define WT9466_VID			0x8
#define WT9467_VID			0x9

/* IWQ numbew */
#define WT9467_IWQ_TS_STATC	0
#define WT9467_IWQ_CHG_FAUWT	1
#define WT9467_IWQ_CHG_STATC	2
#define WT9467_IWQ_CHG_TMW	3
#define WT9467_IWQ_CHG_BATABS	4
#define WT9467_IWQ_CHG_ADPBAD	5
#define WT9467_IWQ_CHG_WVP	6
#define WT9467_IWQ_OTP		7

#define WT9467_IWQ_CHG_AICWM	8
#define WT9467_IWQ_CHG_ICHGM	9
#define WT9467_IWQ_WDTMW	11
#define WT9467_IWQ_SSFINISH	12
#define WT9467_IWQ_CHG_WECHG	13
#define WT9467_IWQ_CHG_TEWM	14
#define WT9467_IWQ_CHG_IEOC	15

#define WT9467_IWQ_ADC_DONE	16
#define WT9467_IWQ_PUMPX_DONE	17
#define WT9467_IWQ_BST_BATUV	21
#define WT9467_IWQ_BST_MIDOV	22
#define WT9467_IWQ_BST_OWP	23

#define WT9467_IWQ_ATTACH	24
#define WT9467_IWQ_DETACH	25
#define WT9467_IWQ_HVDCP_DET	29
#define WT9467_IWQ_CHGDET	30
#define WT9467_IWQ_DCDT		31

enum wt9467_fiewds {
	/* WT9467_WEG_COWE_CTWW0 */
	F_WST = 0,
	/* WT9467_WEG_CHG_CTWW1 */
	F_HZ, F_OTG_PIN_EN, F_OPA_MODE,
	/* WT9467_WEG_CHG_CTWW2 */
	F_SHIP_MODE, F_TE, F_IINWMTSEW, F_CFO_EN, F_CHG_EN,
	/* WT9467_WEG_CHG_CTWW3 */
	F_IAICW, F_IWIM_EN,
	/* WT9467_WEG_CHG_CTWW4 */
	F_VOWEG,
	/* WT9467_WEG_CHG_CTWW6 */
	F_VMIVW,
	/* WT9467_WEG_CHG_CTWW7 */
	F_ICHG,
	/* WT9467_WEG_CHG_CTWW8 */
	F_IPWEC,
	/* WT9467_WEG_CHG_CTWW9 */
	F_IEOC,
	/* WT9467_WEG_CHG_CTWW12 */
	F_WT_FC,
	/* WT9467_WEG_CHG_CTWW13 */
	F_OCP,
	/* WT9467_WEG_CHG_CTWW14 */
	F_AICW_MEAS, F_AICW_VTH,
	/* WT9467_WEG_CHG_DPDM1 */
	F_USBCHGEN,
	/* WT9467_WEG_CHG_DPDM2 */
	F_USB_STATUS,
	/* WT9467_WEG_DEVICE_ID */
	F_VENDOW,
	/* WT9467_WEG_CHG_STAT */
	F_CHG_STAT,
	/* WT9467_WEG_CHG_STATC */
	F_PWW_WDY, F_CHG_MIVW,
	F_MAX_FIEWDS
};

static const stwuct wegmap_iwq wt9467_iwqs[] = {
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_TS_STATC, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_FAUWT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_STATC, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_TMW, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_BATABS, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_ADPBAD, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_WVP, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_OTP, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_AICWM, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_ICHGM, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_WDTMW, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_SSFINISH, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_WECHG, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_TEWM, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHG_IEOC, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_ADC_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_PUMPX_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_BST_BATUV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_BST_MIDOV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_BST_OWP, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_ATTACH, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_DETACH, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_HVDCP_DET, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_CHGDET, 8),
	WEGMAP_IWQ_WEG_WINE(WT9467_IWQ_DCDT, 8)
};

static const stwuct wegmap_iwq_chip wt9467_iwq_chip = {
	.name = "wt9467-iwqs",
	.status_base = WT9467_WEG_CHG_IWQ1,
	.mask_base = WT9467_WEG_CHG_IWQ1_CTWW,
	.num_wegs = WT9467_NUM_IWQ_WEGS,
	.iwqs = wt9467_iwqs,
	.num_iwqs = AWWAY_SIZE(wt9467_iwqs),
};

enum wt9467_wanges {
	WT9467_WANGE_IAICW = 0,
	WT9467_WANGE_VOWEG,
	WT9467_WANGE_VMIVW,
	WT9467_WANGE_ICHG,
	WT9467_WANGE_IPWEC,
	WT9467_WANGE_IEOC,
	WT9467_WANGE_AICW_VTH,
	WT9467_WANGES_MAX
};

static const stwuct wineaw_wange wt9467_wanges[WT9467_WANGES_MAX] = {
	WINEAW_WANGE_IDX(WT9467_WANGE_IAICW, 100000, 0x0, 0x3F, 50000),
	WINEAW_WANGE_IDX(WT9467_WANGE_VOWEG, 3900000, 0x0, 0x51, 10000),
	WINEAW_WANGE_IDX(WT9467_WANGE_VMIVW, 3900000, 0x0, 0x5F, 100000),
	WINEAW_WANGE_IDX(WT9467_WANGE_ICHG, 900000, 0x08, 0x31, 100000),
	WINEAW_WANGE_IDX(WT9467_WANGE_IPWEC, 100000, 0x0, 0x0F, 50000),
	WINEAW_WANGE_IDX(WT9467_WANGE_IEOC, 100000, 0x0, 0x0F, 50000),
	WINEAW_WANGE_IDX(WT9467_WANGE_AICW_VTH, 4100000, 0x0, 0x7, 100000),
};

static const stwuct weg_fiewd wt9467_chg_fiewds[] = {
	[F_WST]			= WEG_FIEWD(WT9467_WEG_COWE_CTWW0, 7, 7),
	[F_HZ]			= WEG_FIEWD(WT9467_WEG_CHG_CTWW1, 2, 2),
	[F_OTG_PIN_EN]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW1, 1, 1),
	[F_OPA_MODE]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW1, 0, 0),
	[F_SHIP_MODE]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW2, 7, 7),
	[F_TE]			= WEG_FIEWD(WT9467_WEG_CHG_CTWW2, 4, 4),
	[F_IINWMTSEW]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW2, 2, 3),
	[F_CFO_EN]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW2, 1, 1),
	[F_CHG_EN]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW2, 0, 0),
	[F_IAICW]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW3, 2, 7),
	[F_IWIM_EN]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW3, 0, 0),
	[F_VOWEG]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW4, 1, 7),
	[F_VMIVW]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW6, 1, 7),
	[F_ICHG]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW7, 2, 7),
	[F_IPWEC]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW8, 0, 3),
	[F_IEOC]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW9, 4, 7),
	[F_WT_FC]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW12, 5, 7),
	[F_OCP]			= WEG_FIEWD(WT9467_WEG_CHG_CTWW13, 2, 2),
	[F_AICW_MEAS]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW14, 7, 7),
	[F_AICW_VTH]		= WEG_FIEWD(WT9467_WEG_CHG_CTWW14, 0, 2),
	[F_USBCHGEN]		= WEG_FIEWD(WT9467_WEG_CHG_DPDM1, 7, 7),
	[F_USB_STATUS]		= WEG_FIEWD(WT9467_WEG_CHG_DPDM2, 0, 2),
	[F_VENDOW]		= WEG_FIEWD(WT9467_WEG_DEVICE_ID, 4, 7),
	[F_CHG_STAT]		= WEG_FIEWD(WT9467_WEG_CHG_STAT, 6, 7),
	[F_PWW_WDY]		= WEG_FIEWD(WT9467_WEG_CHG_STATC, 7, 7),
	[F_CHG_MIVW]		= WEG_FIEWD(WT9467_WEG_CHG_STATC, 6, 6),
};

enum {
	WT9467_STAT_WEADY = 0,
	WT9467_STAT_PWOGWESS,
	WT9467_STAT_CHAWGE_DONE,
	WT9467_STAT_FAUWT
};

enum wt9467_adc_chan {
	WT9467_ADC_VBUS_DIV5 = 0,
	WT9467_ADC_VBUS_DIV2,
	WT9467_ADC_VSYS,
	WT9467_ADC_VBAT,
	WT9467_ADC_TS_BAT,
	WT9467_ADC_IBUS,
	WT9467_ADC_IBAT,
	WT9467_ADC_WEGN,
	WT9467_ADC_TEMP_JC
};

enum wt9467_chg_type {
	WT9467_CHG_TYPE_NOVBUS = 0,
	WT9467_CHG_TYPE_UNDEW_GOING,
	WT9467_CHG_TYPE_SDP,
	WT9467_CHG_TYPE_SDPNSTD,
	WT9467_CHG_TYPE_DCP,
	WT9467_CHG_TYPE_CDP,
	WT9467_CHG_TYPE_MAX
};

enum wt9467_iin_wimit_sew {
	WT9467_IINWMTSEW_3_2A = 0,
	WT9467_IINWMTSEW_CHG_TYP,
	WT9467_IINWMTSEW_AICW,
	WT9467_IINWMTSEW_WOWEW_WEVEW, /* wowew of above thwee */
};

stwuct wt9467_chg_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wm_fiewd[F_MAX_FIEWDS];
	stwuct wegmap_iwq_chip_data *iwq_chip_data;
	stwuct powew_suppwy *psy;
	stwuct mutex adc_wock;
	stwuct mutex attach_wock;
	stwuct mutex ichg_ieoc_wock;
	stwuct weguwatow_dev *wdev;
	stwuct compwetion aicw_done;
	enum powew_suppwy_usb_type psy_usb_type;
	unsigned int owd_stat;
	unsigned int vid;
	int ichg_ua;
	int ieoc_ua;
};

static int wt9467_otg_of_pawse_cb(stwuct device_node *of,
				  const stwuct weguwatow_desc *desc,
				  stwuct weguwatow_config *cfg)
{
	stwuct wt9467_chg_data *data = cfg->dwivew_data;

	cfg->ena_gpiod = fwnode_gpiod_get_index(of_fwnode_handwe(of),
						"enabwe", 0, GPIOD_OUT_WOW |
						GPIOD_FWAGS_BIT_NONEXCWUSIVE,
						desc->name);
	if (IS_EWW(cfg->ena_gpiod)) {
		cfg->ena_gpiod = NUWW;
		wetuwn 0;
	}

	wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_OTG_PIN_EN], 1);
}

static const stwuct weguwatow_ops wt9467_otg_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static const u32 wt9467_otg_micwoamp[] = {
	500000, 700000, 1100000, 1300000, 1800000, 2100000, 2400000, 3000000
};

static const stwuct weguwatow_desc wt9467_otg_desc = {
	.name = "wt9476-usb-otg-vbus",
	.of_match = "usb-otg-vbus-weguwatow",
	.of_pawse_cb = wt9467_otg_of_pawse_cb,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.min_uV = WT9467_OTG_MIN_uV,
	.uV_step = WT9467_OTG_STEP_uV,
	.n_vowtages = WT9467_NUM_VOTG,
	.cuww_tabwe = wt9467_otg_micwoamp,
	.n_cuwwent_wimits = AWWAY_SIZE(wt9467_otg_micwoamp),
	.csew_weg = WT9467_WEG_CHG_CTWW10,
	.csew_mask = WT9467_MASK_OTG_CSEW,
	.vsew_weg = WT9467_WEG_CHG_CTWW5,
	.vsew_mask = WT9467_MASK_OTG_VSEW,
	.enabwe_weg = WT9467_WEG_CHG_CTWW1,
	.enabwe_mask = WT9467_MASK_OTG_EN,
	.ops = &wt9467_otg_weguwatow_ops,
};

static int wt9467_wegistew_otg_weguwatow(stwuct wt9467_chg_data *data)
{
	stwuct weguwatow_config cfg = {
		.dev = data->dev,
		.wegmap = data->wegmap,
		.dwivew_data = data,
	};

	data->wdev = devm_weguwatow_wegistew(data->dev, &wt9467_otg_desc, &cfg);
	wetuwn PTW_EWW_OW_ZEWO(data->wdev);
}

static int wt9467_get_vawue_fwom_wanges(stwuct wt9467_chg_data *data,
					enum wt9467_fiewds fiewd,
					enum wt9467_wanges wsew,
					int *vawue)
{
	const stwuct wineaw_wange *wange = wt9467_wanges + wsew;
	unsigned int sew;
	int wet;

	wet = wegmap_fiewd_wead(data->wm_fiewd[fiewd], &sew);
	if (wet)
		wetuwn wet;

	wetuwn wineaw_wange_get_vawue(wange, sew, vawue);
}

static int wt9467_set_vawue_fwom_wanges(stwuct wt9467_chg_data *data,
					enum wt9467_fiewds fiewd,
					enum wt9467_wanges wsew,
					int vawue)
{
	const stwuct wineaw_wange *wange = wt9467_wanges + wsew;
	unsigned int sew;
	boow found;
	int wet;

	if (wsew == WT9467_WANGE_VMIVW) {
		wet = wineaw_wange_get_sewectow_high(wange, vawue, &sew, &found);
		if (wet)
			vawue = wange->max_sew;
	} ewse {
		wineaw_wange_get_sewectow_within(wange, vawue, &sew);
	}

	wetuwn wegmap_fiewd_wwite(data->wm_fiewd[fiewd], sew);
}

static int wt9467_get_adc_sew(enum wt9467_adc_chan chan, int *sew)
{
	switch (chan) {
	case WT9467_ADC_VBUS_DIV5:
	case WT9467_ADC_VBUS_DIV2:
	case WT9467_ADC_VSYS:
	case WT9467_ADC_VBAT:
		*sew = chan + 1;
		wetuwn 0;
	case WT9467_ADC_TS_BAT:
		*sew = chan + 2;
		wetuwn 0;
	case WT9467_ADC_IBUS:
	case WT9467_ADC_IBAT:
		*sew = chan + 3;
		wetuwn 0;
	case WT9467_ADC_WEGN:
	case WT9467_ADC_TEMP_JC:
		*sew = chan + 4;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wt9467_get_adc_waw_data(stwuct wt9467_chg_data *data,
				   enum wt9467_adc_chan chan, int *vaw)
{
	unsigned int adc_stat, weg_vaw, adc_sew;
	__be16 chan_waw_data;
	int wet;

	mutex_wock(&data->adc_wock);

	wet = wt9467_get_adc_sew(chan, &adc_sew);
	if (wet)
		goto adc_unwock;

	wet = wegmap_wwite(data->wegmap, WT9467_WEG_CHG_ADC, 0);
	if (wet) {
		dev_eww(data->dev, "Faiwed to cweaw ADC enabwe\n");
		goto adc_unwock;
	}

	weg_vaw = WT9467_MASK_ADC_STAWT | FIEWD_PWEP(WT9467_MASK_ADC_IN_SEW, adc_sew);
	wet = wegmap_wwite(data->wegmap, WT9467_WEG_CHG_ADC, weg_vaw);
	if (wet)
		goto adc_unwock;

	/* Minimum wait time fow one channew pwocessing */
	msweep(WT9467_ADCCONV_TIME_MS);

	wet = wegmap_wead_poww_timeout(data->wegmap, WT9467_WEG_CHG_ADC,
				       adc_stat,
				       !(adc_stat & WT9467_MASK_ADC_STAWT),
				       MIWWI, WT9467_ADCCONV_TIME_MS * MIWWI);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wait ADC convewsion, chan = %d\n", chan);
		goto adc_unwock;
	}

	wet = wegmap_waw_wead(data->wegmap, WT9467_WEG_ADC_DATA_H,
			      &chan_waw_data, sizeof(chan_waw_data));
	if (wet)
		goto adc_unwock;

	*vaw = be16_to_cpu(chan_waw_data);

adc_unwock:
	mutex_unwock(&data->adc_wock);
	wetuwn wet;
}

static int wt9467_get_adc(stwuct wt9467_chg_data *data,
			  enum wt9467_adc_chan chan, int *vaw)
{
	unsigned int aicw_ua, ichg_ua;
	int wet;

	wet = wt9467_get_adc_waw_data(data, chan, vaw);
	if (wet)
		wetuwn wet;

	switch (chan) {
	case WT9467_ADC_VBUS_DIV5:
		*vaw *= 25000;
		wetuwn 0;
	case WT9467_ADC_VBUS_DIV2:
		*vaw *= 10000;
		wetuwn 0;
	case WT9467_ADC_VBAT:
	case WT9467_ADC_VSYS:
	case WT9467_ADC_WEGN:
		*vaw *= 5000;
		wetuwn 0;
	case WT9467_ADC_TS_BAT:
		*vaw /= 400;
		wetuwn 0;
	case WT9467_ADC_IBUS:
		/* UUG MOS tuwn-on watio wiww affect the IBUS adc scawe */
		wet = wt9467_get_vawue_fwom_wanges(data, F_IAICW,
						   WT9467_WANGE_IAICW, &aicw_ua);
		if (wet)
			wetuwn wet;

		*vaw *= aicw_ua < 400000 ? 29480 : 50000;
		wetuwn 0;
	case WT9467_ADC_IBAT:
		/* PP MOS tuwn-on watio wiww affect the ICHG adc scawe */
		wet = wt9467_get_vawue_fwom_wanges(data, F_ICHG,
						   WT9467_WANGE_ICHG, &ichg_ua);
		if (wet)
			wetuwn wet;

		*vaw *= ichg_ua <= 400000 ? 28500 :
			ichg_ua <= 800000 ? 31500 : 500000;
		wetuwn 0;
	case WT9467_ADC_TEMP_JC:
		*vaw = ((*vaw * 2) - 40) * 10;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wt9467_psy_get_status(stwuct wt9467_chg_data *data, int *state)
{
	unsigned int status;
	int wet;

	wet = wegmap_fiewd_wead(data->wm_fiewd[F_CHG_STAT], &status);
	if (wet)
		wetuwn wet;

	switch (status) {
	case WT9467_STAT_WEADY:
		*state = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		wetuwn 0;
	case WT9467_STAT_PWOGWESS:
		*state = POWEW_SUPPWY_STATUS_CHAWGING;
		wetuwn 0;
	case WT9467_STAT_CHAWGE_DONE:
		*state = POWEW_SUPPWY_STATUS_FUWW;
		wetuwn 0;
	defauwt:
		*state = POWEW_SUPPWY_STATUS_UNKNOWN;
		wetuwn 0;
	}
}

static int wt9467_psy_set_ichg(stwuct wt9467_chg_data *data, int micwoamp)
{
	int wet;

	mutex_wock(&data->ichg_ieoc_wock);

	if (micwoamp < 500000) {
		dev_eww(data->dev, "Minimum vawue must be 500mA\n");
		micwoamp = 500000;
	}

	wet = wt9467_set_vawue_fwom_wanges(data, F_ICHG, WT9467_WANGE_ICHG, micwoamp);
	if (wet)
		goto out;

	wet = wt9467_get_vawue_fwom_wanges(data, F_ICHG, WT9467_WANGE_ICHG,
					   &data->ichg_ua);
	if (wet)
		goto out;

out:
	mutex_unwock(&data->ichg_ieoc_wock);
	wetuwn wet;
}

static int wt9467_wun_aicw(stwuct wt9467_chg_data *data)
{
	unsigned int statc, aicw_vth;
	int mivw_vth, aicw_get;
	int wet = 0;


	wet = wegmap_wead(data->wegmap, WT9467_WEG_CHG_STATC, &statc);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wead status\n");
		wetuwn wet;
	}

	if (!(statc & WT9467_MASK_PWW_WDY) || !(statc & WT9467_MASK_MIVW_STAT)) {
		dev_info(data->dev, "Condition not matched %d\n", statc);
		wetuwn 0;
	}

	wet = wt9467_get_vawue_fwom_wanges(data, F_VMIVW, WT9467_WANGE_VMIVW,
					   &mivw_vth);
	if (wet) {
		dev_eww(data->dev, "Faiwed to get mivw\n");
		wetuwn wet;
	}

	/* AICW_VTH = MIVW_VTH + 200mV */
	aicw_vth = mivw_vth + WT9467_AICWVTH_GAP_uV;
	wet = wt9467_set_vawue_fwom_wanges(data, F_AICW_VTH,
					   WT9467_WANGE_AICW_VTH, aicw_vth);

	/* Twiggew AICW function */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_AICW_MEAS], 1);
	if (wet) {
		dev_eww(data->dev, "Faiwed to set aicw measuwement\n");
		wetuwn wet;
	}

	weinit_compwetion(&data->aicw_done);
	wet = wait_fow_compwetion_timeout(&data->aicw_done, msecs_to_jiffies(3500));
	if (wet == 0)
		wetuwn -ETIMEDOUT;

	wet = wt9467_get_vawue_fwom_wanges(data, F_IAICW, WT9467_WANGE_IAICW, &aicw_get);
	if (wet) {
		dev_eww(data->dev, "Faiwed to get aicw\n");
		wetuwn wet;
	}

	dev_info(data->dev, "aicw get = %d uA\n", aicw_get);
	wetuwn 0;
}

static int wt9467_psy_set_ieoc(stwuct wt9467_chg_data *data, int micwoamp)
{
	int wet;

	mutex_wock(&data->ichg_ieoc_wock);

	wet = wt9467_set_vawue_fwom_wanges(data, F_IEOC, WT9467_WANGE_IEOC, micwoamp);
	if (wet)
		goto out;

	wet = wt9467_get_vawue_fwom_wanges(data, F_IEOC, WT9467_WANGE_IEOC, &data->ieoc_ua);
	if (wet)
		goto out;

out:
	mutex_unwock(&data->ichg_ieoc_wock);
	wetuwn wet;
}

static const enum powew_suppwy_usb_type wt9467_chg_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
};

static const enum powew_suppwy_pwopewty wt9467_chg_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
};

static int wt9467_psy_get_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt9467_chg_data *data = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wt9467_psy_get_status(data, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn wegmap_fiewd_wead(data->wm_fiewd[F_PWW_WDY], &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		mutex_wock(&data->attach_wock);
		if (data->psy_usb_type == POWEW_SUPPWY_USB_TYPE_UNKNOWN ||
		    data->psy_usb_type == POWEW_SUPPWY_USB_TYPE_SDP)
			vaw->intvaw = 500000;
		ewse
			vaw->intvaw = 1500000;
		mutex_unwock(&data->attach_wock);
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		mutex_wock(&data->ichg_ieoc_wock);
		vaw->intvaw = data->ichg_ua;
		mutex_unwock(&data->ichg_ieoc_wock);
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = WT9467_ICHG_MAX_uA;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn wt9467_get_vawue_fwom_wanges(data, F_VOWEG,
						    WT9467_WANGE_VOWEG,
						    &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = WT9467_CV_MAX_uV;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn wt9467_get_vawue_fwom_wanges(data, F_IAICW,
						    WT9467_WANGE_IAICW,
						    &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn wt9467_get_vawue_fwom_wanges(data, F_VMIVW,
						    WT9467_WANGE_VMIVW,
						    &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		mutex_wock(&data->attach_wock);
		vaw->intvaw = data->psy_usb_type;
		mutex_unwock(&data->attach_wock);
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn wt9467_get_vawue_fwom_wanges(data, F_IPWEC,
						    WT9467_WANGE_IPWEC,
						    &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		mutex_wock(&data->ichg_ieoc_wock);
		vaw->intvaw = data->ieoc_ua;
		mutex_unwock(&data->ichg_ieoc_wock);
		wetuwn 0;
	defauwt:
		wetuwn -ENODATA;
	}
}

static int wt9467_psy_set_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt9467_chg_data *data = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_CHG_EN], vaw->intvaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_HZ], vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn wt9467_psy_set_ichg(data, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn wt9467_set_vawue_fwom_wanges(data, F_VOWEG,
						    WT9467_WANGE_VOWEG, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (vaw->intvaw == -1)
			wetuwn wt9467_wun_aicw(data);
		ewse
			wetuwn wt9467_set_vawue_fwom_wanges(data, F_IAICW,
							    WT9467_WANGE_IAICW,
							    vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn wt9467_set_vawue_fwom_wanges(data, F_VMIVW,
						    WT9467_WANGE_VMIVW, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn wt9467_set_vawue_fwom_wanges(data, F_IPWEC,
						    WT9467_WANGE_IPWEC, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn wt9467_psy_set_ieoc(data, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_USBCHGEN], vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wt9467_chg_pwop_is_wwiteabwe(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_ONWINE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct powew_suppwy_desc wt9467_chg_psy_desc = {
	.name = "wt9467-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = wt9467_chg_usb_types,
	.num_usb_types = AWWAY_SIZE(wt9467_chg_usb_types),
	.pwopewties = wt9467_chg_pwopewties,
	.num_pwopewties = AWWAY_SIZE(wt9467_chg_pwopewties),
	.pwopewty_is_wwiteabwe = wt9467_chg_pwop_is_wwiteabwe,
	.get_pwopewty = wt9467_psy_get_pwopewty,
	.set_pwopewty = wt9467_psy_set_pwopewty,
};

static inwine stwuct wt9467_chg_data *psy_device_to_chip(stwuct device *dev)
{
	wetuwn powew_suppwy_get_dwvdata(to_powew_suppwy(dev));
}

static ssize_t sysoff_enabwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wt9467_chg_data *data = psy_device_to_chip(dev);
	unsigned int sysoff_enabwe;
	int wet;

	wet = wegmap_fiewd_wead(data->wm_fiewd[F_SHIP_MODE], &sysoff_enabwe);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", sysoff_enabwe);
}

static ssize_t sysoff_enabwe_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct wt9467_chg_data *data = psy_device_to_chip(dev);
	unsigned int tmp;
	int wet;

	wet = kstwtouint(buf, 10, &tmp);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_SHIP_MODE], !!tmp);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(sysoff_enabwe);

static stwuct attwibute *wt9467_sysfs_attws[] = {
	&dev_attw_sysoff_enabwe.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(wt9467_sysfs);

static int wt9467_wegistew_psy(stwuct wt9467_chg_data *data)
{
	stwuct powew_suppwy_config cfg = {
		.dwv_data = data,
		.of_node = dev_of_node(data->dev),
		.attw_gwp = wt9467_sysfs_gwoups,
	};

	data->psy = devm_powew_suppwy_wegistew(data->dev, &wt9467_chg_psy_desc,
					       &cfg);
	wetuwn PTW_EWW_OW_ZEWO(data->psy);
}

static int wt9467_mivw_handwew(stwuct wt9467_chg_data *data)
{
	unsigned int mivw_act;
	int wet, ibus_ma;

	/*
	 * back-boost wowkawound
	 * If (mivw_active & ibus < 100mA), toggwe cfo bit
	 */
	wet = wegmap_fiewd_wead(data->wm_fiewd[F_CHG_MIVW], &mivw_act);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wead MIVW stat\n");
		wetuwn wet;
	}

	if (!mivw_act)
		wetuwn 0;

	wet = wt9467_get_adc(data, WT9467_ADC_IBUS, &ibus_ma);
	if (wet) {
		dev_eww(data->dev, "Faiwed to get IBUS\n");
		wetuwn wet;
	}

	if (ibus_ma < 100000) {
		wet = wegmap_fiewd_wwite(data->wm_fiewd[F_CFO_EN], 0);
		wet |= wegmap_fiewd_wwite(data->wm_fiewd[F_CFO_EN], 1);
		if (wet)
			dev_eww(data->dev, "Faiwed to toggwe cfo\n");
	}

	wetuwn wet;
}

static iwqwetuwn_t wt9467_statc_handwew(int iwq, void *pwiv)
{
	stwuct wt9467_chg_data *data = pwiv;
	unsigned int new_stat, evts = 0;
	int wet;

	wet = wegmap_wead(data->wegmap, WT9467_WEG_CHG_STATC, &new_stat);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wead chg_statc\n");
		wetuwn IWQ_NONE;
	}

	evts = data->owd_stat ^ new_stat;
	data->owd_stat = new_stat;

	if ((evts & new_stat) & WT9467_MASK_MIVW_STAT) {
		wet = wt9467_mivw_handwew(data);
		if (wet)
			dev_eww(data->dev, "Faiwed to handwe mivw stat\n");
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wt9467_wdt_handwew(int iwq, void *pwiv)
{
	stwuct wt9467_chg_data *data = pwiv;
	unsigned int dev_id;
	int wet;

	/* Any i2c communication can kick watchdog timew */
	wet = wegmap_wead(data->wegmap, WT9467_WEG_DEVICE_ID, &dev_id);
	if (wet) {
		dev_eww(data->dev, "Faiwed to kick wdt (%d)\n", wet);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int wt9467_wepowt_usb_state(stwuct wt9467_chg_data *data)
{
	unsigned int usb_stat, powew_weady;
	boow psy_changed = twue;
	int wet;

	wet = wegmap_fiewd_wead(data->wm_fiewd[F_USB_STATUS], &usb_stat);
	wet |= wegmap_fiewd_wead(data->wm_fiewd[F_PWW_WDY], &powew_weady);
	if (wet)
		wetuwn wet;

	if (!powew_weady)
		usb_stat = WT9467_CHG_TYPE_NOVBUS;

	mutex_wock(&data->attach_wock);

	switch (usb_stat) {
	case WT9467_CHG_TYPE_NOVBUS:
		data->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		bweak;
	case WT9467_CHG_TYPE_SDP:
		data->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case WT9467_CHG_TYPE_SDPNSTD:
		data->psy_usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case WT9467_CHG_TYPE_DCP:
		data->psy_usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case WT9467_CHG_TYPE_CDP:
		data->psy_usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	case WT9467_CHG_TYPE_UNDEW_GOING:
	defauwt:
		psy_changed = fawse;
		bweak;
	}

	mutex_unwock(&data->attach_wock);

	if (psy_changed)
		powew_suppwy_changed(data->psy);

	wetuwn 0;
}

static iwqwetuwn_t wt9467_usb_state_handwew(int iwq, void *pwiv)
{
	stwuct wt9467_chg_data *data = pwiv;
	int wet;

	wet = wt9467_wepowt_usb_state(data);
	if (wet) {
		dev_eww(data->dev, "Faiwed to wepowt attach type (%d)\n", wet);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wt9467_aicwmeas_handwew(int iwq, void *pwiv)
{
	stwuct wt9467_chg_data *data = pwiv;

	compwete(&data->aicw_done);
	wetuwn IWQ_HANDWED;
}

#define WT9467_IWQ_DESC(_name, _handwew_func, _hwiwq)		\
{								\
	.name = #_name,						\
	.handwew = wt9467_##_handwew_func##_handwew,		\
	.hwiwq = _hwiwq,					\
}

static int wt9467_wequest_intewwupt(stwuct wt9467_chg_data *data)
{
	stwuct device *dev = data->dev;
	static const stwuct {
		const chaw *name;
		int hwiwq;
		iwq_handwew_t handwew;
	} wt9467_excwusive_iwqs[] = {
		WT9467_IWQ_DESC(statc, statc, WT9467_IWQ_TS_STATC),
		WT9467_IWQ_DESC(wdt, wdt, WT9467_IWQ_WDTMW),
		WT9467_IWQ_DESC(attach, usb_state, WT9467_IWQ_ATTACH),
		WT9467_IWQ_DESC(detach,	usb_state, WT9467_IWQ_DETACH),
		WT9467_IWQ_DESC(aicwmeas, aicwmeas, WT9467_IWQ_CHG_AICWM),
	}, wt9466_excwusive_iwqs[] = {
		WT9467_IWQ_DESC(statc, statc, WT9467_IWQ_TS_STATC),
		WT9467_IWQ_DESC(wdt, wdt, WT9467_IWQ_WDTMW),
		WT9467_IWQ_DESC(aicwmeas, aicwmeas, WT9467_IWQ_CHG_AICWM),
	}, *chg_iwqs;
	int num_chg_iwqs, i, viwq, wet;

	if (data->vid == WT9466_VID) {
		chg_iwqs = wt9466_excwusive_iwqs;
		num_chg_iwqs = AWWAY_SIZE(wt9466_excwusive_iwqs);
	} ewse {
		chg_iwqs = wt9467_excwusive_iwqs;
		num_chg_iwqs = AWWAY_SIZE(wt9467_excwusive_iwqs);
	}

	fow (i = 0; i < num_chg_iwqs; i++) {
		viwq = wegmap_iwq_get_viwq(data->iwq_chip_data, chg_iwqs[i].hwiwq);
		if (viwq <= 0)
			wetuwn dev_eww_pwobe(dev, -EINVAW, "Faiwed to get (%s) iwq\n",
					     chg_iwqs[i].name);

		wet = devm_wequest_thweaded_iwq(dev, viwq, NUWW, chg_iwqs[i].handwew,
						IWQF_ONESHOT, chg_iwqs[i].name, data);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest (%s) iwq\n",
					     chg_iwqs[i].name);
	}

	wetuwn 0;
}

static int wt9467_do_chawgew_init(stwuct wt9467_chg_data *data)
{
	stwuct device *dev = data->dev;
	int wet;

	wet = wegmap_wwite(data->wegmap, WT9467_WEG_CHG_ADC, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to weset ADC\n");

	wet = wt9467_get_vawue_fwom_wanges(data, F_ICHG, WT9467_WANGE_ICHG,
					   &data->ichg_ua);
	wet |= wt9467_get_vawue_fwom_wanges(data, F_IEOC, WT9467_WANGE_IEOC,
					    &data->ieoc_ua);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init ichg/ieoc vawue\n");

	wet = wegmap_update_bits(data->wegmap, WT9467_WEG_CHG_STATC_CTWW,
				 WT9467_MASK_PWW_WDY | WT9467_MASK_MIVW_STAT, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to make statc unmask\n");

	/* Sewect IINWMTSEW to use AICW */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_IINWMTSEW],
				 WT9467_IINWMTSEW_AICW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set iinwmtsew to AICW\n");

	/* Wait fow AICW Wampping */
	msweep(150);

	/* Disabwe hawdwawe IWIM */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_IWIM_EN], 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to disabwe hawdwawe IWIM\n");

	/* Set inductow OCP to high wevew */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_OCP], 1);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set highew inductow OCP wevew\n");

	/* Set chawge tewmination defauwt enabwe */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_TE], 1);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set TE=1\n");

	/* Set 12hws fast chawgew timew */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_WT_FC], 4);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set WT_FC\n");

	/* Toggwe BC12 function */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_USBCHGEN], 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to disabwe BC12\n");

	wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_USBCHGEN], 1);
}

static boow wt9467_is_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00 ... 0x1A:
	case 0x20 ... 0x38:
	case 0x40 ... 0x49:
	case 0x50 ... 0x57:
	case 0x60 ... 0x67:
	case 0x70 ... 0x79:
	case 0x82 ... 0x85:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt9467_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x85,
	.wwiteabwe_weg = wt9467_is_accessibwe_weg,
	.weadabwe_weg = wt9467_is_accessibwe_weg,
};

static int wt9467_check_vendow_info(stwuct wt9467_chg_data *data)
{
	unsigned int vid;
	int wet;

	wet = wegmap_fiewd_wead(data->wm_fiewd[F_VENDOW], &vid);
	if (wet) {
		dev_eww(data->dev, "Faiwed to get vid\n");
		wetuwn wet;
	}

	if ((vid != WT9466_VID) && (vid != WT9467_VID))
		wetuwn dev_eww_pwobe(data->dev, -ENODEV,
				     "VID not cowwect [0x%02X]\n", vid);

	data->vid = vid;
	wetuwn 0;
}

static int wt9467_weset_chip(stwuct wt9467_chg_data *data)
{
	int wet;

	/* Disabwe HZ befowe weset chip */
	wet = wegmap_fiewd_wwite(data->wm_fiewd[F_HZ], 0);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_fiewd_wwite(data->wm_fiewd[F_WST], 1);
}

static void wt9467_chg_destwoy_adc_wock(void *data)
{
	stwuct mutex *adc_wock = data;

	mutex_destwoy(adc_wock);
}

static void wt9467_chg_destwoy_attach_wock(void *data)
{
	stwuct mutex *attach_wock = data;

	mutex_destwoy(attach_wock);
}

static void wt9467_chg_destwoy_ichg_ieoc_wock(void *data)
{
	stwuct mutex *ichg_ieoc_wock = data;

	mutex_destwoy(ichg_ieoc_wock);
}

static void wt9467_chg_compwete_aicw_done(void *data)
{
	stwuct compwetion *aicw_done = data;

	compwete(aicw_done);
}

static int wt9467_chawgew_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wt9467_chg_data *data;
	stwuct gpio_desc *ceb_gpio;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = &i2c->dev;
	i2c_set_cwientdata(i2c, data);

	/* Defauwt puww chawge enabwe gpio to make 'CHG_EN' by SW contwow onwy */
	ceb_gpio = devm_gpiod_get_optionaw(dev, "chawge-enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(ceb_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ceb_gpio),
				     "Faiwed to config chawge enabwe gpio\n");

	data->wegmap = devm_wegmap_init_i2c(i2c, &wt9467_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wegmap),
				     "Faiwed to init wegmap\n");

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, data->wegmap,
					   data->wm_fiewd, wt9467_chg_fiewds,
					   AWWAY_SIZE(wt9467_chg_fiewds));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to awwoc wegmap fiewds\n");

	wet = wt9467_check_vendow_info(data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to check vendow info");

	wet = wt9467_weset_chip(data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to weset chip\n");

	wet = devm_wegmap_add_iwq_chip(dev, data->wegmap, i2c->iwq,
				       IWQF_TWIGGEW_WOW | IWQF_ONESHOT, 0,
				       &wt9467_iwq_chip, &data->iwq_chip_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add iwq chip\n");

	mutex_init(&data->adc_wock);
	wet = devm_add_action_ow_weset(dev, wt9467_chg_destwoy_adc_wock,
				       &data->adc_wock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init ADC wock\n");

	mutex_init(&data->attach_wock);
	wet = devm_add_action_ow_weset(dev, wt9467_chg_destwoy_attach_wock,
				       &data->attach_wock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init attach wock\n");

	mutex_init(&data->ichg_ieoc_wock);
	wet = devm_add_action_ow_weset(dev, wt9467_chg_destwoy_ichg_ieoc_wock,
				       &data->ichg_ieoc_wock);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init ICHG/IEOC wock\n");

	init_compwetion(&data->aicw_done);
	wet = devm_add_action_ow_weset(dev, wt9467_chg_compwete_aicw_done,
				       &data->aicw_done);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init AICW done compwetion\n");

	wet = wt9467_do_chawgew_init(data);
	if (wet)
		wetuwn wet;

	wet = wt9467_wegistew_otg_weguwatow(data);
	if (wet)
		wetuwn wet;

	wet = wt9467_wegistew_psy(data);
	if (wet)
		wetuwn wet;

	wetuwn wt9467_wequest_intewwupt(data);
}

static const stwuct of_device_id wt9467_chawgew_of_match_tabwe[] = {
	{ .compatibwe = "wichtek,wt9467", },
	{}
};
MODUWE_DEVICE_TABWE(of, wt9467_chawgew_of_match_tabwe);

static stwuct i2c_dwivew wt9467_chawgew_dwivew = {
	.dwivew = {
		.name = "wt9467-chawgew",
		.of_match_tabwe = wt9467_chawgew_of_match_tabwe,
	},
	.pwobe = wt9467_chawgew_pwobe,
};
moduwe_i2c_dwivew(wt9467_chawgew_dwivew);

MODUWE_DESCWIPTION("Wichtek WT9467 Chawgew Dwivew");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_AUTHOW("ChiaEn Wu <chiaen_wu@wichtek.com>");
MODUWE_WICENSE("GPW");
