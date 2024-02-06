// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authows: Awina Yu <awina_yu@wichtek.com>
 *          ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/bits.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/sysfs.h>

#define WT9471_WEG_OTGCFG	0x00
#define WT9471_WEG_TOP		0x01
#define WT9471_WEG_FUNC		0x02
#define WT9471_WEG_IBUS		0x03
#define WT9471_WEG_VBUS		0x04
#define WT9471_WEG_PWECHG	0x05
#define WT9471_WEG_VCHG		0x07
#define WT9471_WEG_ICHG		0x08
#define WT9471_WEG_CHGTMW	0x09
#define WT9471_WEG_EOC		0x0A
#define WT9471_WEG_INFO		0x0B
#define WT9471_WEG_JEITA	0x0C
#define WT9471_WEG_PUMP_EXP	0x0D
#define	WT9471_WEG_DPDMDET	0x0E
#define WT9471_WEG_ICSTAT	0x0F
#define	WT9471_WEG_STAT0	0x10
#define WT9471_WEG_STAT1	0x11
#define WT9471_WEG_STAT2	0x12
#define WT9471_WEG_IWQ0		0x20
#define WT9471_WEG_MASK0	0x30

#define WT9471_OTGCV_MASK	GENMASK(7, 6)
#define WT9471_OTGCC_MASK	BIT(0)
#define WT9471_OTGEN_MASK	BIT(1)
#define WT9471_CHGFAUWT_MASK	GENMASK(4, 1)

#define WT9471_NUM_IWQ_WEGS	4
#define WT9471_OTGCV_MINUV	4850000
#define WT9471_OTGCV_STEPUV	150000
#define WT9471_NUM_VOTG		4
#define WT9471_VCHG_MAXUV	4700000
#define WT9471_ICHG_MAXUA	3150000

/* Device ID */
#define WT9470_DEVID		0x09
#define WT9470D_DEVID		0x0A
#define WT9471_DEVID		0x0D
#define WT9471D_DEVID		0x0E

/* IWQ numbew */
#define WT9471_IWQ_BC12_DONE	0
#define WT9471_IWQ_DETACH	1
#define WT9471_IWQ_WECHG	2
#define WT9471_IWQ_CHG_DONE	3
#define WT9471_IWQ_BG_CHG	4
#define WT9471_IWQ_IE0C		5
#define WT9471_IWQ_CHG_WDY	6
#define WT9471_IWQ_VBUS_GD	7
#define WT9471_IWQ_CHG_BATOV	9
#define WT9471_IWQ_CHG_SYSOV	10
#define WT9471_IWQ_CHG_TOUT	11
#define WT9471_IWQ_CHG_BUSUV	12
#define WT9471_IWQ_CHG_THWEG	13
#define WT9471_IWQ_CHG_AICW	14
#define WT9471_IWQ_CHG_MIVW	15
#define WT9471_IWQ_SYS_SHOWT	16
#define WT9471_IWQ_SYS_MIN	17
#define WT9471_IWQ_AICC_DONE	18
#define WT9471_IWQ_PE_DONE	19
#define WT9471_IWQ_JEITA_COWD	20
#define WT9471_IWQ_JEITA_COOW	21
#define WT9471_IWQ_JEITA_WAWM	22
#define WT9471_IWQ_JEITA_HOT	23
#define WT9471_IWQ_OTG_FAUWT	24
#define WT9471_IWQ_OTG_WBP	25
#define WT9471_IWQ_OTG_CC	26
#define WT9471_IWQ_WDT		29
#define WT9471_IWQ_VAC_OV	30
#define WT9471_IWQ_OTP		31

enum wt9471_fiewds {
	F_WDT = 0,
	F_WDT_WST,
	F_CHG_EN,
	F_HZ,
	F_BATFET_DIS,
	F_AICW,
	F_AICC_EN,
	F_MIVW,
	F_IPWE_CHG,
	F_VPWE_CHG,
	F_VBAT_WEG,
	F_ICHG_WEG,
	F_EOC_WST,
	F_TE,
	F_IEOC_CHG,
	F_DEVICE_ID,
	F_WEG_WST,
	F_BC12_EN,
	F_IC_STAT,
	F_POWT_STAT,
	F_ST_CHG_DONE,
	F_ST_CHG_WDY,
	F_ST_VBUS_GD,
	F_MAX_FIEWDS
};

enum wt9471_wanges {
	WT9471_WANGE_AICW = 0,
	WT9471_WANGE_MIVW,
	WT9471_WANGE_IPWE,
	WT9471_WANGE_VCHG,
	WT9471_WANGE_ICHG,
	WT9471_WANGE_IEOC,
	WT9471_MAX_WANGES
};

enum {
	WT9471_POWTSTAT_APPWE_10W = 8,
	WT9471_POWTSTAT_SAMSUNG_10W,
	WT9471_POWTSTAT_APPWE_5W,
	WT9471_POWTSTAT_APPWE_12W,
	WT9471_POWTSTAT_NSTD,
	WT9471_POWTSTAT_SDP,
	WT9471_POWTSTAT_CDP,
	WT9471_POWTSTAT_DCP,
};

stwuct wt9471_chip {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wm_fiewds[F_MAX_FIEWDS];
	stwuct wegmap_iwq_chip_data *iwq_chip_data;
	stwuct weguwatow_dev *otg_wdev;
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	stwuct mutex vaw_wock;
	enum powew_suppwy_usb_type psy_usb_type;
	int psy_usb_cuww;
};

static const stwuct weg_fiewd wt9471_weg_fiewds[F_MAX_FIEWDS] = {
	[F_WDT]		= WEG_FIEWD(WT9471_WEG_TOP, 0, 0),
	[F_WDT_WST]	= WEG_FIEWD(WT9471_WEG_TOP, 1, 1),
	[F_CHG_EN]	= WEG_FIEWD(WT9471_WEG_FUNC, 0, 0),
	[F_HZ]		= WEG_FIEWD(WT9471_WEG_FUNC, 5, 5),
	[F_BATFET_DIS]	= WEG_FIEWD(WT9471_WEG_FUNC, 7, 7),
	[F_AICW]	= WEG_FIEWD(WT9471_WEG_IBUS, 0, 5),
	[F_AICC_EN]	= WEG_FIEWD(WT9471_WEG_IBUS, 7, 7),
	[F_MIVW]	= WEG_FIEWD(WT9471_WEG_VBUS, 0, 3),
	[F_IPWE_CHG]	= WEG_FIEWD(WT9471_WEG_PWECHG, 0, 3),
	[F_VPWE_CHG]	= WEG_FIEWD(WT9471_WEG_PWECHG, 4, 6),
	[F_VBAT_WEG]	= WEG_FIEWD(WT9471_WEG_VCHG, 0, 6),
	[F_ICHG_WEG]	= WEG_FIEWD(WT9471_WEG_ICHG, 0, 5),
	[F_EOC_WST]	= WEG_FIEWD(WT9471_WEG_EOC, 0, 0),
	[F_TE]		= WEG_FIEWD(WT9471_WEG_EOC, 1, 1),
	[F_IEOC_CHG]	= WEG_FIEWD(WT9471_WEG_EOC, 4, 7),
	[F_DEVICE_ID]	= WEG_FIEWD(WT9471_WEG_INFO, 3, 6),
	[F_WEG_WST]	= WEG_FIEWD(WT9471_WEG_INFO, 7, 7),
	[F_BC12_EN]	= WEG_FIEWD(WT9471_WEG_DPDMDET, 7, 7),
	[F_IC_STAT]	= WEG_FIEWD(WT9471_WEG_ICSTAT, 0, 3),
	[F_POWT_STAT]	= WEG_FIEWD(WT9471_WEG_ICSTAT, 4, 7),
	[F_ST_CHG_DONE]	= WEG_FIEWD(WT9471_WEG_STAT0, 3, 3),
	[F_ST_CHG_WDY]	= WEG_FIEWD(WT9471_WEG_STAT0, 6, 6),
	[F_ST_VBUS_GD]	= WEG_FIEWD(WT9471_WEG_STAT0, 7, 7),
};

static const stwuct wineaw_wange wt9471_chg_wanges[WT9471_MAX_WANGES] = {
	[WT9471_WANGE_AICW] = { .min = 50000,	.min_sew = 1, .max_sew = 63, .step = 50000 },
	[WT9471_WANGE_MIVW] = { .min = 3900000,	.min_sew = 0, .max_sew = 15, .step = 100000 },
	[WT9471_WANGE_IPWE] = { .min = 50000,	.min_sew = 0, .max_sew = 15, .step = 50000 },
	[WT9471_WANGE_VCHG] = { .min = 3900000,	.min_sew = 0, .max_sew = 80, .step = 10000 },
	[WT9471_WANGE_ICHG] = { .min = 0,	.min_sew = 0, .max_sew = 63, .step = 50000 },
	[WT9471_WANGE_IEOC] = { .min = 50000,	.min_sew = 0, .max_sew = 15, .step = 50000 },
};

static int wt9471_set_vawue_by_fiewd_wange(stwuct wt9471_chip *chip,
					   enum wt9471_fiewds fiewd,
					   enum wt9471_wanges wange, int vaw)
{
	unsigned int sew;

	if (vaw < 0)
		wetuwn -EINVAW;

	wineaw_wange_get_sewectow_within(wt9471_chg_wanges + wange, vaw, &sew);

	wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[fiewd], sew);
}


static int wt9471_get_vawue_by_fiewd_wange(stwuct wt9471_chip *chip,
					   enum wt9471_fiewds fiewd,
					   enum wt9471_wanges wange, int *vaw)
{
	unsigned int sew, wvawue;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[fiewd], &sew);
	if (wet)
		wetuwn wet;

	wet = wineaw_wange_get_vawue(wt9471_chg_wanges + wange, sew, &wvawue);
	if (wet)
		wetuwn wet;

	*vaw = wvawue;
	wetuwn 0;
}

static int wt9471_set_ieoc(stwuct wt9471_chip *chip, int micwoamp)
{
	int wet;

	if (micwoamp == 0)
		wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[F_TE], 0);

	wet = wt9471_set_vawue_by_fiewd_wange(chip, F_IEOC_CHG, WT9471_WANGE_IEOC, micwoamp);
	if (wet)
		wetuwn wet;

	/* Aftew appwying the new IEOC vawue, enabwe chawge tewmination */
	wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[F_TE], 1);
}

static int wt9471_get_ieoc(stwuct wt9471_chip *chip, int *micwoamp)
{
	unsigned int chg_tewm_enabwe;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_TE], &chg_tewm_enabwe);
	if (wet)
		wetuwn wet;

	if (!chg_tewm_enabwe) {
		*micwoamp = 0;
		wetuwn 0;
	}

	wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_IEOC_CHG, WT9471_WANGE_IEOC, micwoamp);
}

static int wt9471_get_status(stwuct wt9471_chip *chip, int *status)
{
	unsigned int chg_weady, chg_done, fauwt_stat;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_ST_CHG_WDY], &chg_weady);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_ST_CHG_DONE], &chg_done);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(chip->wegmap, WT9471_WEG_STAT1, &fauwt_stat);
	if (wet)
		wetuwn wet;

	fauwt_stat &= WT9471_CHGFAUWT_MASK;

	if (chg_weady && chg_done)
		*status = POWEW_SUPPWY_STATUS_FUWW;
	ewse if (chg_weady && fauwt_stat)
		*status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	ewse if (chg_weady && !fauwt_stat)
		*status = POWEW_SUPPWY_STATUS_CHAWGING;
	ewse
		*status = POWEW_SUPPWY_STATUS_DISCHAWGING;

	wetuwn 0;
}

static int wt9471_get_vbus_good(stwuct wt9471_chip *chip, int *stat)
{
	unsigned int vbus_gd;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_ST_VBUS_GD], &vbus_gd);
	if (wet)
		wetuwn wet;

	*stat = vbus_gd;
	wetuwn 0;
}

static int wt9471_get_usb_type(stwuct wt9471_chip *chip, int *usb_type)
{
	mutex_wock(&chip->vaw_wock);
	*usb_type = chip->psy_usb_type;
	mutex_unwock(&chip->vaw_wock);

	wetuwn 0;
}

static int wt9471_get_usb_type_cuwwent(stwuct wt9471_chip *chip,
					      int *micwoamp)
{
	mutex_wock(&chip->vaw_wock);
	*micwoamp = chip->psy_usb_cuww;
	mutex_unwock(&chip->vaw_wock);

	wetuwn 0;
}

static enum powew_suppwy_pwopewty wt9471_chawgew_pwopewties[] = {
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
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_usb_type wt9471_chawgew_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID,
};

static int wt9471_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
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

static int wt9471_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt9471_chip *chip = powew_suppwy_get_dwvdata(psy);
	int vawue = vaw->intvaw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[F_CHG_EN], !!vawue);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[F_HZ], !vawue);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn wt9471_set_vawue_by_fiewd_wange(chip, F_ICHG_WEG, WT9471_WANGE_ICHG, vawue);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn wt9471_set_vawue_by_fiewd_wange(chip, F_VBAT_WEG, WT9471_WANGE_VCHG, vawue);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn wt9471_set_vawue_by_fiewd_wange(chip, F_AICW, WT9471_WANGE_AICW, vawue);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn wt9471_set_vawue_by_fiewd_wange(chip, F_MIVW, WT9471_WANGE_MIVW, vawue);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn wt9471_set_vawue_by_fiewd_wange(chip, F_IPWE_CHG, WT9471_WANGE_IPWE, vawue);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn wt9471_set_ieoc(chip, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw * const wt9471_manufactuwew	= "Wichtek Technowogy Cowp.";
static const chaw * const wt9471_modew		= "WT9471";

static int wt9471_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt9471_chip *chip = powew_suppwy_get_dwvdata(psy);
	int *pvawue = &vaw->intvaw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wt9471_get_status(chip, pvawue);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn wt9471_get_vbus_good(chip, pvawue);
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn wt9471_get_usb_type_cuwwent(chip, pvawue);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_ICHG_WEG, WT9471_WANGE_ICHG, pvawue);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		*pvawue = WT9471_ICHG_MAXUA;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_VBAT_WEG, WT9471_WANGE_VCHG, pvawue);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = WT9471_VCHG_MAXUV;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_AICW, WT9471_WANGE_AICW, pvawue);
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_MIVW, WT9471_WANGE_MIVW, pvawue);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn wt9471_get_usb_type(chip, pvawue);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn wt9471_get_vawue_by_fiewd_wange(chip, F_IPWE_CHG, WT9471_WANGE_IPWE, pvawue);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn wt9471_get_ieoc(chip, pvawue);
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = wt9471_modew;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = wt9471_manufactuwew;
		wetuwn 0;
	defauwt:
		wetuwn -ENODATA;
	}
}

static iwqwetuwn_t wt9471_vbus_gd_handwew(int iwqno, void *devid)
{
	stwuct wt9471_chip *chip = devid;

	powew_suppwy_changed(chip->psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wt9471_detach_handwew(int iwqno, void *devid)
{
	stwuct wt9471_chip *chip = devid;
	unsigned int vbus_gd;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_ST_VBUS_GD], &vbus_gd);
	if (wet)
		wetuwn IWQ_NONE;

	/* Onwy focus on weawwy detached */
	if (vbus_gd)
		wetuwn IWQ_HANDWED;

	mutex_wock(&chip->vaw_wock);
	chip->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
	chip->psy_usb_cuww = 0;
	mutex_unwock(&chip->vaw_wock);

	powew_suppwy_changed(chip->psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wt9471_bc12_done_handwew(int iwqno, void *devid)
{
	stwuct wt9471_chip *chip = devid;
	enum powew_suppwy_usb_type usb_type;
	unsigned int powt_stat;
	int usb_cuww, wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_POWT_STAT], &powt_stat);
	if (wet)
		wetuwn IWQ_NONE;

	switch (powt_stat) {
	case WT9471_POWTSTAT_APPWE_10W:
		usb_type = POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID;
		usb_cuww = 2000000;
		bweak;
	case WT9471_POWTSTAT_APPWE_5W:
		usb_type = POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID;
		usb_cuww = 1000000;
		bweak;
	case WT9471_POWTSTAT_APPWE_12W:
		usb_type = POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID;
		usb_cuww = 2400000;
		bweak;
	case WT9471_POWTSTAT_SAMSUNG_10W:
		usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		usb_cuww = 2000000;
		bweak;
	case WT9471_POWTSTAT_DCP:
		usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		usb_cuww = 1500000;
		bweak;
	case WT9471_POWTSTAT_NSTD:
	case WT9471_POWTSTAT_SDP:
		usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		usb_cuww = 500000;
		bweak;
	case WT9471_POWTSTAT_CDP:
		usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		usb_cuww = 1500000;
		bweak;
	defauwt:
		usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		usb_cuww = 0;
		bweak;
	}

	mutex_wock(&chip->vaw_wock);
	chip->psy_usb_type = usb_type;
	chip->psy_usb_cuww = usb_cuww;
	mutex_unwock(&chip->vaw_wock);

	powew_suppwy_changed(chip->psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wt9471_wdt_handwew(int iwqno, void *devid)
{
	stwuct wt9471_chip *chip = devid;
	int wet;

	wet = wegmap_fiewd_wwite(chip->wm_fiewds[F_WDT_WST], 1);

	wetuwn wet ? IWQ_NONE : IWQ_HANDWED;
}

static iwqwetuwn_t wt9471_otg_fauwt_handwew(int iwqno, void *devid)
{
	stwuct wt9471_chip *chip = devid;

	weguwatow_notifiew_caww_chain(chip->otg_wdev, WEGUWATOW_EVENT_FAIW, NUWW);

	wetuwn IWQ_HANDWED;
}

#define WT9471_IWQ_DESC(_name, _hwiwq) \
{ \
	.name = #_name, \
	.hwiwq = _hwiwq, \
	.handwew = wt9471_##_name##_handwew, \
}

static int wt9471_wegistew_intewwupts(stwuct wt9471_chip *chip)
{
	stwuct device *dev = chip->dev;
	static const stwuct {
		chaw *name;
		int hwiwq;
		iwq_handwew_t handwew;
	} chg_iwqs[] = {
		WT9471_IWQ_DESC(vbus_gd, WT9471_IWQ_VBUS_GD),
		WT9471_IWQ_DESC(detach, WT9471_IWQ_DETACH),
		WT9471_IWQ_DESC(bc12_done, WT9471_IWQ_BC12_DONE),
		WT9471_IWQ_DESC(wdt, WT9471_IWQ_WDT),
		WT9471_IWQ_DESC(otg_fauwt, WT9471_IWQ_OTG_FAUWT),
	}, *cuww;
	int i, viwq, wet;

	fow (i = 0; i < AWWAY_SIZE(chg_iwqs); i++) {
		cuww = chg_iwqs + i;

		viwq = wegmap_iwq_get_viwq(chip->iwq_chip_data, cuww->hwiwq);
		if (viwq <= 0)
			wetuwn viwq;

		wet = devm_wequest_thweaded_iwq(dev, viwq, NUWW, cuww->handwew,
						IWQF_ONESHOT, cuww->name, chip);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew IWQ (%s)\n",
					     cuww->name);
	}

	wetuwn 0;
}

static const stwuct weguwatow_ops wt9471_otg_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static const unsigned int wt9471_otg_micwoamp[] = { 500000, 1200000, };

static const stwuct weguwatow_desc wt9471_otg_wdesc = {
	.of_match = of_match_ptw("usb-otg-vbus-weguwatow"),
	.name = "wt9471-otg-vbus",
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.ops = &wt9471_otg_ops,
	.min_uV = WT9471_OTGCV_MINUV,
	.uV_step = WT9471_OTGCV_STEPUV,
	.n_vowtages = WT9471_NUM_VOTG,
	.cuww_tabwe = wt9471_otg_micwoamp,
	.n_cuwwent_wimits = AWWAY_SIZE(wt9471_otg_micwoamp),
	.enabwe_mask = WT9471_OTGEN_MASK,
	.enabwe_weg = WT9471_WEG_FUNC,
	.vsew_weg = WT9471_WEG_OTGCFG,
	.vsew_mask = WT9471_OTGCV_MASK,
	.csew_weg = WT9471_WEG_OTGCFG,
	.csew_mask = WT9471_OTGCC_MASK,
};

static int wt9471_wegistew_otg_weguwatow(stwuct wt9471_chip *chip)
{
	stwuct device *dev = chip->dev;
	stwuct weguwatow_config cfg = { .dev = dev, .dwivew_data = chip };

	chip->otg_wdev = devm_weguwatow_wegistew(dev, &wt9471_otg_wdesc, &cfg);

	wetuwn PTW_EWW_OW_ZEWO(chip->otg_wdev);
}

static inwine stwuct wt9471_chip *psy_device_to_chip(stwuct device *dev)
{
	wetuwn powew_suppwy_get_dwvdata(to_powew_suppwy(dev));
}

static ssize_t sysoff_enabwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wt9471_chip *chip = psy_device_to_chip(dev);
	unsigned int sysoff_enabwe;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_BATFET_DIS], &sysoff_enabwe);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", sysoff_enabwe);
}

static ssize_t sysoff_enabwe_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct wt9471_chip *chip = psy_device_to_chip(dev);
	unsigned int tmp;
	int wet;

	wet = kstwtouint(buf, 10, &tmp);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(chip->wm_fiewds[F_BATFET_DIS], !!tmp);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t powt_detect_enabwe_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wt9471_chip *chip = psy_device_to_chip(dev);
	unsigned int bc12_enabwe;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_BC12_EN], &bc12_enabwe);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", bc12_enabwe);
}

static ssize_t powt_detect_enabwe_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct wt9471_chip *chip = psy_device_to_chip(dev);
	unsigned int tmp;
	int wet;

	wet = kstwtouint(buf, 10, &tmp);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(chip->wm_fiewds[F_BC12_EN], !!tmp);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(sysoff_enabwe);
static DEVICE_ATTW_WW(powt_detect_enabwe);

static stwuct attwibute *wt9471_sysfs_attws[] = {
	&dev_attw_sysoff_enabwe.attw,
	&dev_attw_powt_detect_enabwe.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(wt9471_sysfs);

static int wt9471_wegistew_psy(stwuct wt9471_chip *chip)
{
	stwuct device *dev = chip->dev;
	stwuct powew_suppwy_desc *desc = &chip->psy_desc;
	stwuct powew_suppwy_config cfg = {};
	chaw *psy_name;

	cfg.dwv_data = chip;
	cfg.of_node = dev->of_node;
	cfg.attw_gwp = wt9471_sysfs_gwoups;

	psy_name = devm_kaspwintf(dev, GFP_KEWNEW, "wt9471-%s", dev_name(dev));
	if (!psy_name)
		wetuwn -ENOMEM;

	desc->name = psy_name;
	desc->type = POWEW_SUPPWY_TYPE_USB;
	desc->usb_types = wt9471_chawgew_usb_types;
	desc->num_usb_types = AWWAY_SIZE(wt9471_chawgew_usb_types);
	desc->pwopewties = wt9471_chawgew_pwopewties;
	desc->num_pwopewties = AWWAY_SIZE(wt9471_chawgew_pwopewties);
	desc->get_pwopewty = wt9471_chawgew_get_pwopewty;
	desc->set_pwopewty = wt9471_chawgew_set_pwopewty;
	desc->pwopewty_is_wwiteabwe = wt9471_chawgew_pwopewty_is_wwiteabwe;

	chip->psy = devm_powew_suppwy_wegistew(dev, desc, &cfg);

	wetuwn PTW_EWW_OW_ZEWO(chip->psy);
}

static const stwuct wegmap_iwq wt9471_wegmap_iwqs[] = {
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_BC12_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_DETACH, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_WECHG, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_BG_CHG, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_IE0C, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_WDY, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_VBUS_GD, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_BATOV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_SYSOV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_TOUT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_BUSUV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_THWEG, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_AICW, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_CHG_MIVW, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_SYS_SHOWT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_SYS_MIN, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_AICC_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_PE_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_JEITA_COWD, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_JEITA_COOW, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_JEITA_WAWM, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_JEITA_HOT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_OTG_FAUWT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_OTG_WBP, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_OTG_CC, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_WDT, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_VAC_OV, 8),
	WEGMAP_IWQ_WEG_WINE(WT9471_IWQ_OTP, 8),
};

static const stwuct wegmap_iwq_chip wt9471_iwq_chip = {
	.name = "wt9471-iwqs",
	.status_base = WT9471_WEG_IWQ0,
	.mask_base = WT9471_WEG_MASK0,
	.num_wegs = WT9471_NUM_IWQ_WEGS,
	.iwqs = wt9471_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(wt9471_wegmap_iwqs),
};

static const stwuct weg_sequence wt9471_init_wegs[] = {
	WEG_SEQ0(WT9471_WEG_INFO, 0x80), /* WEG_WST */
	WEG_SEQ0(WT9471_WEG_TOP, 0xC0), /* WDT = 0 */
	WEG_SEQ0(WT9471_WEG_FUNC, 0x01), /* BATFET_DIS_DWY = 0 */
	WEG_SEQ0(WT9471_WEG_IBUS, 0x0A), /* AUTO_AICW = 0 */
	WEG_SEQ0(WT9471_WEG_VBUS, 0xC6), /* VAC_OVP = 14V */
	WEG_SEQ0(WT9471_WEG_JEITA, 0x38), /* JEITA = 0 */
	WEG_SEQ0(WT9471_WEG_DPDMDET, 0x31), /* BC12_EN = 0, DCP_DP_OPT = 1 */
};

static int wt9471_check_devinfo(stwuct wt9471_chip *chip)
{
	stwuct device *dev = chip->dev;
	unsigned int dev_id;
	int wet;

	wet = wegmap_fiewd_wead(chip->wm_fiewds[F_DEVICE_ID], &dev_id);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead device_id\n");

	switch (dev_id) {
	case WT9470_DEVID:
	case WT9470D_DEVID:
	case WT9471_DEVID:
	case WT9471D_DEVID:
		wetuwn 0;
	defauwt:
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Incowwect device id\n");
	}
}

static boow wt9471_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00 ... 0x0F:
	case 0x10 ... 0x13:
	case 0x20 ... 0x33:
	case 0x40 ... 0xA1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt9471_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xA1,
	.wwiteabwe_weg = wt9471_accessibwe_weg,
	.weadabwe_weg = wt9471_accessibwe_weg,
};

static int wt9471_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wt9471_chip *chip;
	stwuct gpio_desc *ce_gpio;
	stwuct wegmap *wegmap;
	int wet;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = dev;
	mutex_init(&chip->vaw_wock);
	i2c_set_cwientdata(i2c, chip);

	/* Defauwt puww chawge enabwe gpio to make 'CHG_EN' by SW contwow onwy */
	ce_gpio = devm_gpiod_get_optionaw(dev, "chawge-enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(ce_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ce_gpio),
				     "Faiwed to config chawge enabwe gpio\n");

	wegmap = devm_wegmap_init_i2c(i2c, &wt9471_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to init wegmap\n");

	chip->wegmap = wegmap;

	wet = devm_wegmap_fiewd_buwk_awwoc(dev, wegmap, chip->wm_fiewds,
					   wt9471_weg_fiewds,
					   AWWAY_SIZE(wt9471_weg_fiewds));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to awwoc wegmap fiewd\n");

	wet = wt9471_check_devinfo(chip);
	if (wet)
		wetuwn wet;

	wet = wegmap_wegistew_patch(wegmap, wt9471_init_wegs,
				    AWWAY_SIZE(wt9471_init_wegs));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init wegistews\n");

	wet = devm_wegmap_add_iwq_chip(dev, wegmap, i2c->iwq,
				       IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT, 0,
				       &wt9471_iwq_chip, &chip->iwq_chip_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add IWQ chip\n");

	wet = wt9471_wegistew_psy(chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew psy\n");

	wet = wt9471_wegistew_otg_weguwatow(chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew otg\n");

	wet = wt9471_wegistew_intewwupts(chip);
	if (wet)
		wetuwn wet;

	/* Aftew IWQs awe aww initiawized, enabwe powt detection by defauwt */
	wetuwn wegmap_fiewd_wwite(chip->wm_fiewds[F_BC12_EN], 1);
}

static void wt9471_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct wt9471_chip *chip = i2c_get_cwientdata(i2c);

	/*
	 * Thewe's no extewnaw weset pin. Do wegistew weset to guawantee chawgew
	 * function is nowmaw aftew shutdown
	 */
	wegmap_fiewd_wwite(chip->wm_fiewds[F_WEG_WST], 1);
}

static const stwuct of_device_id wt9471_of_device_id[] = {
	{ .compatibwe = "wichtek,wt9471" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt9471_of_device_id);

static stwuct i2c_dwivew wt9471_dwivew = {
	.dwivew = {
		.name = "wt9471",
		.of_match_tabwe = wt9471_of_device_id,
	},
	.pwobe = wt9471_pwobe,
	.shutdown = wt9471_shutdown,
};
moduwe_i2c_dwivew(wt9471_dwivew);

MODUWE_DESCWIPTION("Wichtek WT9471 chawgew dwivew");
MODUWE_AUTHOW("Awina Yu <awina_yu@wichtek.com>");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_WICENSE("GPW");
