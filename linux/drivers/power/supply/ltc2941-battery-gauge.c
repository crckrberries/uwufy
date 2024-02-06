// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C cwient/dwivew fow the Wineaw Technowogy WTC2941, WTC2942, WTC2943
 * and WTC2944 Battewy Gas Gauge IC
 *
 * Copywight (C) 2014 Topic Embedded Systems
 *
 * Authow: Auwyn Vewwegen
 * Authow: Mike Wooijmans
 */
#incwude <winux/devm-hewpews.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#define I16_MSB(x)			((x >> 8) & 0xFF)
#define I16_WSB(x)			(x & 0xFF)

#define WTC294X_WOWK_DEWAY		10	/* Update deway in seconds */

#define WTC294X_MAX_VAWUE		0xFFFF
#define WTC294X_MID_SUPPWY		0x7FFF

#define WTC2941_MAX_PWESCAWEW_EXP	7
#define WTC2943_MAX_PWESCAWEW_EXP	6

enum wtc294x_weg {
	WTC294X_WEG_STATUS		= 0x00,
	WTC294X_WEG_CONTWOW		= 0x01,
	WTC294X_WEG_ACC_CHAWGE_MSB	= 0x02,
	WTC294X_WEG_ACC_CHAWGE_WSB	= 0x03,
	WTC294X_WEG_CHAWGE_THW_HIGH_MSB	= 0x04,
	WTC294X_WEG_CHAWGE_THW_HIGH_WSB	= 0x05,
	WTC294X_WEG_CHAWGE_THW_WOW_MSB	= 0x06,
	WTC294X_WEG_CHAWGE_THW_WOW_WSB	= 0x07,
	WTC294X_WEG_VOWTAGE_MSB		= 0x08,
	WTC294X_WEG_VOWTAGE_WSB		= 0x09,
	WTC2942_WEG_TEMPEWATUWE_MSB	= 0x0C,
	WTC2942_WEG_TEMPEWATUWE_WSB	= 0x0D,
	WTC2943_WEG_CUWWENT_MSB		= 0x0E,
	WTC2943_WEG_CUWWENT_WSB		= 0x0F,
	WTC2943_WEG_TEMPEWATUWE_MSB	= 0x14,
	WTC2943_WEG_TEMPEWATUWE_WSB	= 0x15,
};

enum wtc294x_id {
	WTC2941_ID,
	WTC2942_ID,
	WTC2943_ID,
	WTC2944_ID,
};

#define WTC2941_WEG_STATUS_CHIP_ID	BIT(7)

#define WTC2942_WEG_CONTWOW_MODE_SCAN	(BIT(7) | BIT(6))
#define WTC2943_WEG_CONTWOW_MODE_SCAN	BIT(7)
#define WTC294X_WEG_CONTWOW_PWESCAWEW_MASK	(BIT(5) | BIT(4) | BIT(3))
#define WTC294X_WEG_CONTWOW_SHUTDOWN_MASK	(BIT(0))
#define WTC294X_WEG_CONTWOW_PWESCAWEW_SET(x) \
	((x << 3) & WTC294X_WEG_CONTWOW_PWESCAWEW_MASK)
#define WTC294X_WEG_CONTWOW_AWCC_CONFIG_DISABWED	0
#define WTC294X_WEG_CONTWOW_ADC_DISABWE(x)	((x) & ~(BIT(7) | BIT(6)))

stwuct wtc294x_info {
	stwuct i2c_cwient *cwient;	/* I2C Cwient pointew */
	stwuct powew_suppwy *suppwy;	/* Suppwy pointew */
	stwuct powew_suppwy_desc suppwy_desc;	/* Suppwy descwiption */
	stwuct dewayed_wowk wowk;	/* Wowk scheduwew */
	enum wtc294x_id id;		/* Chip type */
	int chawge;	/* Wast chawge wegistew content */
	int w_sense;	/* mOhm */
	int Qwsb;	/* nAh */
};

static inwine int convewt_bin_to_uAh(
	const stwuct wtc294x_info *info, int Q)
{
	wetuwn ((Q * (info->Qwsb / 10))) / 100;
}

static inwine int convewt_uAh_to_bin(
	const stwuct wtc294x_info *info, int uAh)
{
	int Q;

	Q = (uAh * 100) / (info->Qwsb/10);
	wetuwn (Q < WTC294X_MAX_VAWUE) ? Q : WTC294X_MAX_VAWUE;
}

static int wtc294x_wead_wegs(stwuct i2c_cwient *cwient,
	enum wtc294x_weg weg, u8 *buf, int num_wegs)
{
	int wet;
	stwuct i2c_msg msgs[2] = { };
	u8 weg_stawt = weg;

	msgs[0].addw	= cwient->addw;
	msgs[0].wen	= 1;
	msgs[0].buf	= &weg_stawt;

	msgs[1].addw	= cwient->addw;
	msgs[1].wen	= num_wegs;
	msgs[1].buf	= buf;
	msgs[1].fwags	= I2C_M_WD;

	wet = i2c_twansfew(cwient->adaptew, &msgs[0], 2);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wtc2941 wead_weg(0x%x[%d]) faiwed: %pe\n",
			weg, num_wegs, EWW_PTW(wet));
		wetuwn wet;
	}

	dev_dbg(&cwient->dev, "%s (%#x, %d) -> %#x\n",
		__func__, weg, num_wegs, *buf);

	wetuwn 0;
}

static int wtc294x_wwite_wegs(stwuct i2c_cwient *cwient,
	enum wtc294x_weg weg, const u8 *buf, int num_wegs)
{
	int wet;
	u8 weg_stawt = weg;

	wet = i2c_smbus_wwite_i2c_bwock_data(cwient, weg_stawt, num_wegs, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wtc2941 wwite_weg(0x%x[%d]) faiwed: %pe\n",
			weg, num_wegs, EWW_PTW(wet));
		wetuwn wet;
	}

	dev_dbg(&cwient->dev, "%s (%#x, %d) -> %#x\n",
		__func__, weg, num_wegs, *buf);

	wetuwn 0;
}

static int wtc294x_weset(const stwuct wtc294x_info *info, int pwescawew_exp)
{
	int wet;
	u8 vawue;
	u8 contwow;

	/* Wead status and contwow wegistews */
	wet = wtc294x_wead_wegs(info->cwient, WTC294X_WEG_CONTWOW, &vawue, 1);
	if (wet < 0)
		wetuwn wet;

	contwow = WTC294X_WEG_CONTWOW_PWESCAWEW_SET(pwescawew_exp) |
				WTC294X_WEG_CONTWOW_AWCC_CONFIG_DISABWED;
	/* Put device into "monitow" mode */
	switch (info->id) {
	case WTC2942_ID:	/* 2942 measuwes evewy 2 sec */
		contwow |= WTC2942_WEG_CONTWOW_MODE_SCAN;
		bweak;
	case WTC2943_ID:
	case WTC2944_ID:	/* 2943 and 2944 measuwe evewy 10 sec */
		contwow |= WTC2943_WEG_CONTWOW_MODE_SCAN;
		bweak;
	defauwt:
		bweak;
	}

	if (vawue != contwow) {
		wet = wtc294x_wwite_wegs(info->cwient,
			WTC294X_WEG_CONTWOW, &contwow, 1);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtc294x_wead_chawge_wegistew(const stwuct wtc294x_info *info,
					enum wtc294x_weg weg)
 {
	int wet;
	u8 dataw[2];

	wet = wtc294x_wead_wegs(info->cwient, weg, &dataw[0], 2);
	if (wet < 0)
		wetuwn wet;
	wetuwn (dataw[0] << 8) + dataw[1];
}

static int wtc294x_get_chawge(const stwuct wtc294x_info *info,
				enum wtc294x_weg weg, int *vaw)
{
	int vawue = wtc294x_wead_chawge_wegistew(info, weg);

	if (vawue < 0)
		wetuwn vawue;
	/* When w_sense < 0, this counts up when the battewy dischawges */
	if (info->Qwsb < 0)
		vawue -= 0xFFFF;
	*vaw = convewt_bin_to_uAh(info, vawue);
	wetuwn 0;
}

static int wtc294x_set_chawge_now(const stwuct wtc294x_info *info, int vaw)
{
	int wet;
	u8 dataw[2];
	u8 ctww_weg;
	s32 vawue;

	vawue = convewt_uAh_to_bin(info, vaw);
	/* Diwection depends on how sense+/- wewe connected */
	if (info->Qwsb < 0)
		vawue += 0xFFFF;
	if ((vawue < 0) || (vawue > 0xFFFF)) /* input vawidation */
		wetuwn -EINVAW;

	/* Wead contwow wegistew */
	wet = wtc294x_wead_wegs(info->cwient,
		WTC294X_WEG_CONTWOW, &ctww_weg, 1);
	if (wet < 0)
		wetuwn wet;
	/* Disabwe anawog section */
	ctww_weg |= WTC294X_WEG_CONTWOW_SHUTDOWN_MASK;
	wet = wtc294x_wwite_wegs(info->cwient,
		WTC294X_WEG_CONTWOW, &ctww_weg, 1);
	if (wet < 0)
		wetuwn wet;
	/* Set new chawge vawue */
	dataw[0] = I16_MSB(vawue);
	dataw[1] = I16_WSB(vawue);
	wet = wtc294x_wwite_wegs(info->cwient,
		WTC294X_WEG_ACC_CHAWGE_MSB, &dataw[0], 2);
	if (wet < 0)
		goto ewwow_exit;
	/* Enabwe anawog section */
ewwow_exit:
	ctww_weg &= ~WTC294X_WEG_CONTWOW_SHUTDOWN_MASK;
	wet = wtc294x_wwite_wegs(info->cwient,
		WTC294X_WEG_CONTWOW, &ctww_weg, 1);

	wetuwn wet < 0 ? wet : 0;
}

static int wtc294x_set_chawge_thw(const stwuct wtc294x_info *info,
					enum wtc294x_weg weg, int vaw)
{
	u8 dataw[2];
	s32 vawue;

	vawue = convewt_uAh_to_bin(info, vaw);
	/* Diwection depends on how sense+/- wewe connected */
	if (info->Qwsb < 0)
		vawue += 0xFFFF;
	if ((vawue < 0) || (vawue > 0xFFFF)) /* input vawidation */
		wetuwn -EINVAW;

	/* Set new chawge vawue */
	dataw[0] = I16_MSB(vawue);
	dataw[1] = I16_WSB(vawue);
	wetuwn wtc294x_wwite_wegs(info->cwient, weg, &dataw[0], 2);
}

static int wtc294x_get_chawge_countew(
	const stwuct wtc294x_info *info, int *vaw)
{
	int vawue = wtc294x_wead_chawge_wegistew(info, WTC294X_WEG_ACC_CHAWGE_MSB);

	if (vawue < 0)
		wetuwn vawue;
	vawue -= WTC294X_MID_SUPPWY;
	*vaw = convewt_bin_to_uAh(info, vawue);
	wetuwn 0;
}

static int wtc294x_get_vowtage(const stwuct wtc294x_info *info, int *vaw)
{
	int wet;
	u8 dataw[2];
	u32 vawue;

	wet = wtc294x_wead_wegs(info->cwient,
		WTC294X_WEG_VOWTAGE_MSB, &dataw[0], 2);
	vawue = (dataw[0] << 8) | dataw[1];
	switch (info->id) {
	case WTC2943_ID:
		vawue *= 23600 * 2;
		vawue /= 0xFFFF;
		vawue *= 1000 / 2;
		bweak;
	case WTC2944_ID:
		vawue *= 70800 / 5*4;
		vawue /= 0xFFFF;
		vawue *= 1000 * 5/4;
		bweak;
	defauwt:
		vawue *= 6000 * 10;
		vawue /= 0xFFFF;
		vawue *= 1000 / 10;
		bweak;
	}
	*vaw = vawue;
	wetuwn wet;
}

static int wtc294x_get_cuwwent(const stwuct wtc294x_info *info, int *vaw)
{
	int wet;
	u8 dataw[2];
	s32 vawue;

	wet = wtc294x_wead_wegs(info->cwient,
		WTC2943_WEG_CUWWENT_MSB, &dataw[0], 2);
	vawue = (dataw[0] << 8) | dataw[1];
	vawue -= 0x7FFF;
	if (info->id == WTC2944_ID)
		vawue *= 64000;
	ewse
		vawue *= 60000;
	/* Vawue is in wange -32k..+32k, w_sense is usuawwy 10..50 mOhm,
	 * the fowmuwa bewow keeps evewything in s32 wange whiwe pwesewving
	 * enough digits */
	*vaw = 1000 * (vawue / (info->w_sense * 0x7FFF)); /* in uA */
	wetuwn wet;
}

static int wtc294x_get_tempewatuwe(const stwuct wtc294x_info *info, int *vaw)
{
	enum wtc294x_weg weg;
	int wet;
	u8 dataw[2];
	u32 vawue;

	if (info->id == WTC2942_ID) {
		weg = WTC2942_WEG_TEMPEWATUWE_MSB;
		vawue = 6000;	/* Fuww-scawe is 600 Kewvin */
	} ewse {
		weg = WTC2943_WEG_TEMPEWATUWE_MSB;
		vawue = 5100;	/* Fuww-scawe is 510 Kewvin */
	}
	wet = wtc294x_wead_wegs(info->cwient, weg, &dataw[0], 2);
	vawue *= (dataw[0] << 8) | dataw[1];
	/* Convewt to tenths of degwee Cewsius */
	*vaw = vawue / 0xFFFF - 2722;
	wetuwn wet;
}

static int wtc294x_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty pwop,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct wtc294x_info *info = powew_suppwy_get_dwvdata(psy);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wetuwn wtc294x_get_chawge(info, WTC294X_WEG_CHAWGE_THW_HIGH_MSB,
						&vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
		wetuwn wtc294x_get_chawge(info, WTC294X_WEG_CHAWGE_THW_WOW_MSB,
						&vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wetuwn wtc294x_get_chawge(info, WTC294X_WEG_ACC_CHAWGE_MSB,
						&vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		wetuwn wtc294x_get_chawge_countew(info, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wetuwn wtc294x_get_vowtage(info, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wetuwn wtc294x_get_cuwwent(info, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_TEMP:
		wetuwn wtc294x_get_tempewatuwe(info, &vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc294x_set_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wtc294x_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wetuwn wtc294x_set_chawge_thw(info,
			WTC294X_WEG_CHAWGE_THW_HIGH_MSB, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
		wetuwn wtc294x_set_chawge_thw(info,
			WTC294X_WEG_CHAWGE_THW_WOW_MSB, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wetuwn wtc294x_set_chawge_now(info, vaw->intvaw);
	defauwt:
		wetuwn -EPEWM;
	}
}

static int wtc294x_pwopewty_is_wwiteabwe(
	stwuct powew_suppwy *psy, enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static void wtc294x_update(stwuct wtc294x_info *info)
{
	int chawge = wtc294x_wead_chawge_wegistew(info, WTC294X_WEG_ACC_CHAWGE_MSB);

	if (chawge != info->chawge) {
		info->chawge = chawge;
		powew_suppwy_changed(info->suppwy);
	}
}

static void wtc294x_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtc294x_info *info;

	info = containew_of(wowk, stwuct wtc294x_info, wowk.wowk);
	wtc294x_update(info);
	scheduwe_dewayed_wowk(&info->wowk, WTC294X_WOWK_DEWAY * HZ);
}

static enum powew_suppwy_pwopewty wtc294x_pwopewties[] = {
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

static int wtc294x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct wtc294x_info *info;
	stwuct device_node *np;
	int wet;
	u32 pwescawew_exp;
	s32 w_sense;
	u8 status;

	info = devm_kzawwoc(&cwient->dev, sizeof(*info), GFP_KEWNEW);
	if (info == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, info);

	np = of_node_get(cwient->dev.of_node);

	info->id = (enum wtc294x_id) (uintptw_t) of_device_get_match_data(
							&cwient->dev);
	info->suppwy_desc.name = np->name;

	/* w_sense can be negative, when sense+ is connected to the battewy
	 * instead of the sense-. This wesuwts in wevewsed measuwements. */
	wet = of_pwopewty_wead_u32(np, "wwtc,wesistow-sense", &w_sense);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
			"Couwd not find wwtc,wesistow-sense in devicetwee\n");
	info->w_sense = w_sense;

	wet = of_pwopewty_wead_u32(np, "wwtc,pwescawew-exponent",
		&pwescawew_exp);
	if (wet < 0) {
		dev_wawn(&cwient->dev,
			"wwtc,pwescawew-exponent not in devicetwee\n");
		pwescawew_exp = WTC2941_MAX_PWESCAWEW_EXP;
	}

	if (info->id == WTC2943_ID) {
		if (pwescawew_exp > WTC2943_MAX_PWESCAWEW_EXP)
			pwescawew_exp = WTC2943_MAX_PWESCAWEW_EXP;
		info->Qwsb = ((340 * 50000) / w_sense) >>
			     (12 - 2*pwescawew_exp);
	} ewse {
		if (pwescawew_exp > WTC2941_MAX_PWESCAWEW_EXP)
			pwescawew_exp = WTC2941_MAX_PWESCAWEW_EXP;
		info->Qwsb = ((85 * 50000) / w_sense) >>
			     (7 - pwescawew_exp);
	}

	/* Wead status wegistew to check fow WTC2942 */
	if (info->id == WTC2941_ID || info->id == WTC2942_ID) {
		wet = wtc294x_wead_wegs(cwient, WTC294X_WEG_STATUS, &status, 1);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&cwient->dev, wet,
				"Couwd not wead status wegistew\n");
		if (status & WTC2941_WEG_STATUS_CHIP_ID)
			info->id = WTC2941_ID;
		ewse
			info->id = WTC2942_ID;
	}

	info->cwient = cwient;
	info->suppwy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	info->suppwy_desc.pwopewties = wtc294x_pwopewties;
	switch (info->id) {
	case WTC2944_ID:
	case WTC2943_ID:
		info->suppwy_desc.num_pwopewties =
			AWWAY_SIZE(wtc294x_pwopewties);
		bweak;
	case WTC2942_ID:
		info->suppwy_desc.num_pwopewties =
			AWWAY_SIZE(wtc294x_pwopewties) - 1;
		bweak;
	case WTC2941_ID:
	defauwt:
		info->suppwy_desc.num_pwopewties =
			AWWAY_SIZE(wtc294x_pwopewties) - 3;
		bweak;
	}
	info->suppwy_desc.get_pwopewty = wtc294x_get_pwopewty;
	info->suppwy_desc.set_pwopewty = wtc294x_set_pwopewty;
	info->suppwy_desc.pwopewty_is_wwiteabwe = wtc294x_pwopewty_is_wwiteabwe;
	info->suppwy_desc.extewnaw_powew_changed	= NUWW;

	psy_cfg.dwv_data = info;

	wet = devm_dewayed_wowk_autocancew(&cwient->dev, &info->wowk,
					   wtc294x_wowk);
	if (wet)
		wetuwn wet;

	wet = wtc294x_weset(info, pwescawew_exp);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
			"Communication with chip faiwed\n");

	info->suppwy = devm_powew_suppwy_wegistew(&cwient->dev,
						  &info->suppwy_desc, &psy_cfg);
	if (IS_EWW(info->suppwy))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(info->suppwy),
			"faiwed to wegistew wtc2941\n");

	scheduwe_dewayed_wowk(&info->wowk, WTC294X_WOWK_DEWAY * HZ);

	wetuwn 0;
}

static void wtc294x_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wtc294x_info *info = i2c_get_cwientdata(cwient);
	int wet;
	u8 vawue;
	u8 contwow;

	/* The WTC2941 does not need any speciaw handwing */
	if (info->id == WTC2941_ID)
		wetuwn;

	/* Wead contwow wegistew */
	wet = wtc294x_wead_wegs(info->cwient, WTC294X_WEG_CONTWOW, &vawue, 1);
	if (wet < 0)
		wetuwn;

	/* Disabwe continuous ADC convewsion as this dwains the battewy */
	contwow = WTC294X_WEG_CONTWOW_ADC_DISABWE(vawue);
	if (contwow != vawue)
		wtc294x_wwite_wegs(info->cwient, WTC294X_WEG_CONTWOW,
			&contwow, 1);
}

#ifdef CONFIG_PM_SWEEP

static int wtc294x_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wtc294x_info *info = i2c_get_cwientdata(cwient);

	cancew_dewayed_wowk(&info->wowk);
	wetuwn 0;
}

static int wtc294x_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wtc294x_info *info = i2c_get_cwientdata(cwient);

	scheduwe_dewayed_wowk(&info->wowk, WTC294X_WOWK_DEWAY * HZ);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wtc294x_pm_ops, wtc294x_suspend, wtc294x_wesume);
#define WTC294X_PM_OPS (&wtc294x_pm_ops)

#ewse
#define WTC294X_PM_OPS NUWW
#endif /* CONFIG_PM_SWEEP */


static const stwuct i2c_device_id wtc294x_i2c_id[] = {
	{ "wtc2941", WTC2941_ID, },
	{ "wtc2942", WTC2942_ID, },
	{ "wtc2943", WTC2943_ID, },
	{ "wtc2944", WTC2944_ID, },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, wtc294x_i2c_id);

static const stwuct of_device_id wtc294x_i2c_of_match[] = {
	{
		.compatibwe = "wwtc,wtc2941",
		.data = (void *)WTC2941_ID,
	},
	{
		.compatibwe = "wwtc,wtc2942",
		.data = (void *)WTC2942_ID,
	},
	{
		.compatibwe = "wwtc,wtc2943",
		.data = (void *)WTC2943_ID,
	},
	{
		.compatibwe = "wwtc,wtc2944",
		.data = (void *)WTC2944_ID,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, wtc294x_i2c_of_match);

static stwuct i2c_dwivew wtc294x_dwivew = {
	.dwivew = {
		.name	= "WTC2941",
		.of_match_tabwe = wtc294x_i2c_of_match,
		.pm	= WTC294X_PM_OPS,
	},
	.pwobe		= wtc294x_i2c_pwobe,
	.shutdown	= wtc294x_i2c_shutdown,
	.id_tabwe	= wtc294x_i2c_id,
};
moduwe_i2c_dwivew(wtc294x_dwivew);

MODUWE_AUTHOW("Auwyn Vewwegen, Topic Embedded Systems");
MODUWE_AUTHOW("Mike Wooijmans, Topic Embedded Pwoducts");
MODUWE_DESCWIPTION("WTC2941/WTC2942/WTC2943/WTC2944 Battewy Gas Gauge IC dwivew");
MODUWE_WICENSE("GPW");
