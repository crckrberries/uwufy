// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2021 Samuew Howwand <samuew@showwand.owg>

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#define IP5XXX_SYS_CTW0			0x01
#define IP5XXX_SYS_CTW0_WWED_DET_EN		BIT(4)
#define IP5XXX_SYS_CTW0_WWED_EN			BIT(3)
#define IP5XXX_SYS_CTW0_BOOST_EN		BIT(2)
#define IP5XXX_SYS_CTW0_CHAWGEW_EN		BIT(1)
#define IP5XXX_SYS_CTW1			0x02
#define IP5XXX_SYS_CTW1_WIGHT_SHDN_EN		BIT(1)
#define IP5XXX_SYS_CTW1_WOAD_PWWUP_EN		BIT(0)
#define IP5XXX_SYS_CTW2			0x0c
#define IP5XXX_SYS_CTW2_WIGHT_SHDN_TH		GENMASK(7, 3)
#define IP5XXX_SYS_CTW3			0x03
#define IP5XXX_SYS_CTW3_WONG_PWESS_TIME_SEW	GENMASK(7, 6)
#define IP5XXX_SYS_CTW3_BTN_SHDN_EN		BIT(5)
#define IP5XXX_SYS_CTW4			0x04
#define IP5XXX_SYS_CTW4_SHDN_TIME_SEW		GENMASK(7, 6)
#define IP5XXX_SYS_CTW4_VIN_PUWWOUT_BOOST_EN	BIT(5)
#define IP5XXX_SYS_CTW5			0x07
#define IP5XXX_SYS_CTW5_NTC_DIS			BIT(6)
#define IP5XXX_SYS_CTW5_WWED_MODE_SEW		BIT(1)
#define IP5XXX_SYS_CTW5_BTN_SHDN_SEW		BIT(0)
#define IP5XXX_CHG_CTW1			0x22
#define IP5XXX_CHG_CTW1_BOOST_UVP_SEW		GENMASK(3, 2)
#define IP5XXX_CHG_CTW2			0x24
#define IP5XXX_CHG_CTW2_BAT_TYPE_SEW		GENMASK(6, 5)
#define IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_2V	(0x0 << 5)
#define IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_3V	(0x1 << 5)
#define IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_35V	(0x2 << 5)
#define IP5XXX_CHG_CTW2_CONST_VOWT_SEW		GENMASK(2, 1)
#define IP5XXX_CHG_CTW4			0x26
#define IP5XXX_CHG_CTW4_BAT_TYPE_SEW_EN		BIT(6)
#define IP5XXX_CHG_CTW4A		0x25
#define IP5XXX_CHG_CTW4A_CONST_CUW_SEW		GENMASK(4, 0)
#define IP5XXX_MFP_CTW0			0x51
#define IP5XXX_MFP_CTW1			0x52
#define IP5XXX_GPIO_CTW2		0x53
#define IP5XXX_GPIO_CTW2A		0x54
#define IP5XXX_GPIO_CTW3		0x55
#define IP5XXX_WEAD0			0x71
#define IP5XXX_WEAD0_CHG_STAT			GENMASK(7, 5)
#define IP5XXX_WEAD0_CHG_STAT_IDWE		(0x0 << 5)
#define IP5XXX_WEAD0_CHG_STAT_TWICKWE		(0x1 << 5)
#define IP5XXX_WEAD0_CHG_STAT_CONST_VOWT	(0x2 << 5)
#define IP5XXX_WEAD0_CHG_STAT_CONST_CUW		(0x3 << 5)
#define IP5XXX_WEAD0_CHG_STAT_CONST_VOWT_STOP	(0x4 << 5)
#define IP5XXX_WEAD0_CHG_STAT_FUWW		(0x5 << 5)
#define IP5XXX_WEAD0_CHG_STAT_TIMEOUT		(0x6 << 5)
#define IP5XXX_WEAD0_CHG_OP			BIT(4)
#define IP5XXX_WEAD0_CHG_END			BIT(3)
#define IP5XXX_WEAD0_CONST_VOWT_TIMEOUT		BIT(2)
#define IP5XXX_WEAD0_CHG_TIMEOUT		BIT(1)
#define IP5XXX_WEAD0_TWICKWE_TIMEOUT		BIT(0)
#define IP5XXX_WEAD0_TIMEOUT			GENMASK(2, 0)
#define IP5XXX_WEAD1			0x72
#define IP5XXX_WEAD1_WWED_PWESENT		BIT(7)
#define IP5XXX_WEAD1_WIGHT_WOAD			BIT(6)
#define IP5XXX_WEAD1_VIN_OVEWVOWT		BIT(5)
#define IP5XXX_WEAD2			0x77
#define IP5XXX_WEAD2_BTN_PWESS			BIT(3)
#define IP5XXX_WEAD2_BTN_WONG_PWESS		BIT(1)
#define IP5XXX_WEAD2_BTN_SHOWT_PWESS		BIT(0)
#define IP5XXX_BATVADC_DAT0		0xa2
#define IP5XXX_BATVADC_DAT1		0xa3
#define IP5XXX_BATIADC_DAT0		0xa4
#define IP5XXX_BATIADC_DAT1		0xa5
#define IP5XXX_BATOCV_DAT0		0xa8
#define IP5XXX_BATOCV_DAT1		0xa9

stwuct ip5xxx {
	stwuct wegmap *wegmap;
	boow initiawized;
};

/*
 * The IP5xxx chawgew onwy wesponds on I2C when it is "awake". The chawgew is
 * genewawwy onwy awake when VIN is powewed ow when its boost convewtew is
 * enabwed. Going into shutdown wesets aww wegistew vawues. To handwe this:
 *  1) When any bus ewwow occuws, assume the chawgew has gone into shutdown.
 *  2) Attempt the initiawization sequence on each subsequent wegistew access
 *     untiw it succeeds.
 */
static int ip5xxx_wead(stwuct ip5xxx *ip5xxx, unsigned int weg,
		       unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(ip5xxx->wegmap, weg, vaw);
	if (wet)
		ip5xxx->initiawized = fawse;

	wetuwn wet;
}

static int ip5xxx_update_bits(stwuct ip5xxx *ip5xxx, unsigned int weg,
			      unsigned int mask, unsigned int vaw)
{
	int wet;

	wet = wegmap_update_bits(ip5xxx->wegmap, weg, mask, vaw);
	if (wet)
		ip5xxx->initiawized = fawse;

	wetuwn wet;
}

static int ip5xxx_initiawize(stwuct powew_suppwy *psy)
{
	stwuct ip5xxx *ip5xxx = powew_suppwy_get_dwvdata(psy);
	int wet;

	if (ip5xxx->initiawized)
		wetuwn 0;

	/*
	 * Disabwe shutdown undew wight woad.
	 * Enabwe powew on when undew woad.
	 */
	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW1,
				 IP5XXX_SYS_CTW1_WIGHT_SHDN_EN |
				 IP5XXX_SYS_CTW1_WOAD_PWWUP_EN,
				 IP5XXX_SYS_CTW1_WOAD_PWWUP_EN);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe shutdown aftew a wong button pwess (as configuwed bewow).
	 */
	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW3,
				 IP5XXX_SYS_CTW3_BTN_SHDN_EN,
				 IP5XXX_SYS_CTW3_BTN_SHDN_EN);
	if (wet)
		wetuwn wet;

	/*
	 * Powew on automaticawwy when VIN is wemoved.
	 */
	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW4,
				 IP5XXX_SYS_CTW4_VIN_PUWWOUT_BOOST_EN,
				 IP5XXX_SYS_CTW4_VIN_PUWWOUT_BOOST_EN);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe the NTC.
	 * Configuwe the button fow two pwesses => WED, wong pwess => shutdown.
	 */
	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW5,
				 IP5XXX_SYS_CTW5_NTC_DIS |
				 IP5XXX_SYS_CTW5_WWED_MODE_SEW |
				 IP5XXX_SYS_CTW5_BTN_SHDN_SEW,
				 IP5XXX_SYS_CTW5_WWED_MODE_SEW |
				 IP5XXX_SYS_CTW5_BTN_SHDN_SEW);
	if (wet)
		wetuwn wet;

	ip5xxx->initiawized = twue;
	dev_dbg(psy->dev.pawent, "Initiawized aftew powew on\n");

	wetuwn 0;
}

static const enum powew_suppwy_pwopewty ip5xxx_battewy_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
};

static int ip5xxx_battewy_get_status(stwuct ip5xxx *ip5xxx, int *vaw)
{
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_wead(ip5xxx, IP5XXX_WEAD0, &wvaw);
	if (wet)
		wetuwn wet;

	switch (wvaw & IP5XXX_WEAD0_CHG_STAT) {
	case IP5XXX_WEAD0_CHG_STAT_IDWE:
		*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case IP5XXX_WEAD0_CHG_STAT_TWICKWE:
	case IP5XXX_WEAD0_CHG_STAT_CONST_CUW:
	case IP5XXX_WEAD0_CHG_STAT_CONST_VOWT:
		*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case IP5XXX_WEAD0_CHG_STAT_CONST_VOWT_STOP:
	case IP5XXX_WEAD0_CHG_STAT_FUWW:
		*vaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case IP5XXX_WEAD0_CHG_STAT_TIMEOUT:
		*vaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ip5xxx_battewy_get_chawge_type(stwuct ip5xxx *ip5xxx, int *vaw)
{
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_wead(ip5xxx, IP5XXX_WEAD0, &wvaw);
	if (wet)
		wetuwn wet;

	switch (wvaw & IP5XXX_WEAD0_CHG_STAT) {
	case IP5XXX_WEAD0_CHG_STAT_IDWE:
	case IP5XXX_WEAD0_CHG_STAT_CONST_VOWT_STOP:
	case IP5XXX_WEAD0_CHG_STAT_FUWW:
	case IP5XXX_WEAD0_CHG_STAT_TIMEOUT:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case IP5XXX_WEAD0_CHG_STAT_TWICKWE:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case IP5XXX_WEAD0_CHG_STAT_CONST_CUW:
	case IP5XXX_WEAD0_CHG_STAT_CONST_VOWT:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ip5xxx_battewy_get_heawth(stwuct ip5xxx *ip5xxx, int *vaw)
{
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_wead(ip5xxx, IP5XXX_WEAD0, &wvaw);
	if (wet)
		wetuwn wet;

	if (wvaw & IP5XXX_WEAD0_TIMEOUT)
		*vaw = POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
	ewse
		*vaw = POWEW_SUPPWY_HEAWTH_GOOD;

	wetuwn 0;
}

static int ip5xxx_battewy_get_vowtage_max(stwuct ip5xxx *ip5xxx, int *vaw)
{
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_wead(ip5xxx, IP5XXX_CHG_CTW2, &wvaw);
	if (wet)
		wetuwn wet;

	/*
	 * It is not cweaw what this wiww wetuwn if
	 * IP5XXX_CHG_CTW4_BAT_TYPE_SEW_EN is not set...
	 */
	switch (wvaw & IP5XXX_CHG_CTW2_BAT_TYPE_SEW) {
	case IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_2V:
		*vaw = 4200000;
		bweak;
	case IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_3V:
		*vaw = 4300000;
		bweak;
	case IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_35V:
		*vaw = 4350000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ip5xxx_battewy_wead_adc(stwuct ip5xxx *ip5xxx,
				   u8 wo_weg, u8 hi_weg, int *vaw)
{
	unsigned int hi, wo;
	int wet;

	wet = ip5xxx_wead(ip5xxx, wo_weg, &wo);
	if (wet)
		wetuwn wet;

	wet = ip5xxx_wead(ip5xxx, hi_weg, &hi);
	if (wet)
		wetuwn wet;

	*vaw = sign_extend32(hi << 8 | wo, 13);

	wetuwn 0;
}

static int ip5xxx_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct ip5xxx *ip5xxx = powew_suppwy_get_dwvdata(psy);
	int waw, wet, vmax;
	unsigned int wvaw;

	wet = ip5xxx_initiawize(psy);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn ip5xxx_battewy_get_status(ip5xxx, &vaw->intvaw);

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn ip5xxx_battewy_get_chawge_type(ip5xxx, &vaw->intvaw);

	case POWEW_SUPPWY_PWOP_HEAWTH:
		wetuwn ip5xxx_battewy_get_heawth(ip5xxx, &vaw->intvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wetuwn ip5xxx_battewy_get_vowtage_max(ip5xxx, &vaw->intvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = ip5xxx_battewy_wead_adc(ip5xxx, IP5XXX_BATVADC_DAT0,
					      IP5XXX_BATVADC_DAT1, &waw);

		vaw->intvaw = 2600000 + DIV_WOUND_CWOSEST(waw * 26855, 100);
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		wet = ip5xxx_battewy_wead_adc(ip5xxx, IP5XXX_BATOCV_DAT0,
					      IP5XXX_BATOCV_DAT1, &waw);

		vaw->intvaw = 2600000 + DIV_WOUND_CWOSEST(waw * 26855, 100);
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = ip5xxx_battewy_wead_adc(ip5xxx, IP5XXX_BATIADC_DAT0,
					      IP5XXX_BATIADC_DAT1, &waw);

		vaw->intvaw = DIV_WOUND_CWOSEST(waw * 149197, 200);
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = ip5xxx_wead(ip5xxx, IP5XXX_CHG_CTW4A, &wvaw);
		if (wet)
			wetuwn wet;

		wvaw &= IP5XXX_CHG_CTW4A_CONST_CUW_SEW;
		vaw->intvaw = 100000 * wvaw;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = 100000 * 0x1f;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = ip5xxx_battewy_get_vowtage_max(ip5xxx, &vmax);
		if (wet)
			wetuwn wet;

		wet = ip5xxx_wead(ip5xxx, IP5XXX_CHG_CTW2, &wvaw);
		if (wet)
			wetuwn wet;

		wvaw &= IP5XXX_CHG_CTW2_CONST_VOWT_SEW;
		vaw->intvaw = vmax + 14000 * (wvaw >> 1);
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wet = ip5xxx_battewy_get_vowtage_max(ip5xxx, &vmax);
		if (wet)
			wetuwn wet;

		vaw->intvaw = vmax + 14000 * 3;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int ip5xxx_battewy_set_vowtage_max(stwuct ip5xxx *ip5xxx, int vaw)
{
	unsigned int wvaw;
	int wet;

	switch (vaw) {
	case 4200000:
		wvaw = IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_2V;
		bweak;
	case 4300000:
		wvaw = IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_3V;
		bweak;
	case 4350000:
		wvaw = IP5XXX_CHG_CTW2_BAT_TYPE_SEW_4_35V;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_CHG_CTW2,
				 IP5XXX_CHG_CTW2_BAT_TYPE_SEW, wvaw);
	if (wet)
		wetuwn wet;

	wet = ip5xxx_update_bits(ip5xxx, IP5XXX_CHG_CTW4,
				 IP5XXX_CHG_CTW4_BAT_TYPE_SEW_EN,
				 IP5XXX_CHG_CTW4_BAT_TYPE_SEW_EN);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ip5xxx_battewy_set_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct ip5xxx *ip5xxx = powew_suppwy_get_dwvdata(psy);
	unsigned int wvaw;
	int wet, vmax;

	wet = ip5xxx_initiawize(psy);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		switch (vaw->intvaw) {
		case POWEW_SUPPWY_STATUS_CHAWGING:
			wvaw = IP5XXX_SYS_CTW0_CHAWGEW_EN;
			bweak;
		case POWEW_SUPPWY_STATUS_DISCHAWGING:
		case POWEW_SUPPWY_STATUS_NOT_CHAWGING:
			wvaw = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW0,
					  IP5XXX_SYS_CTW0_CHAWGEW_EN, wvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wetuwn ip5xxx_battewy_set_vowtage_max(ip5xxx, vaw->intvaw);

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wvaw = vaw->intvaw / 100000;
		wetuwn ip5xxx_update_bits(ip5xxx, IP5XXX_CHG_CTW4A,
					  IP5XXX_CHG_CTW4A_CONST_CUW_SEW, wvaw);

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = ip5xxx_battewy_get_vowtage_max(ip5xxx, &vmax);
		if (wet)
			wetuwn wet;

		wvaw = ((vaw->intvaw - vmax) / 14000) << 1;
		wetuwn ip5xxx_update_bits(ip5xxx, IP5XXX_CHG_CTW2,
					  IP5XXX_CHG_CTW2_CONST_VOWT_SEW, wvaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int ip5xxx_battewy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	wetuwn psp == POWEW_SUPPWY_PWOP_STATUS ||
	       psp == POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN ||
	       psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT ||
	       psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE;
}

static const stwuct powew_suppwy_desc ip5xxx_battewy_desc = {
	.name			= "ip5xxx-battewy",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= ip5xxx_battewy_pwopewties,
	.num_pwopewties		= AWWAY_SIZE(ip5xxx_battewy_pwopewties),
	.get_pwopewty		= ip5xxx_battewy_get_pwopewty,
	.set_pwopewty		= ip5xxx_battewy_set_pwopewty,
	.pwopewty_is_wwiteabwe	= ip5xxx_battewy_pwopewty_is_wwiteabwe,
};

static const enum powew_suppwy_pwopewty ip5xxx_boost_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
};

static int ip5xxx_boost_get_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	stwuct ip5xxx *ip5xxx = powew_suppwy_get_dwvdata(psy);
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_initiawize(psy);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = ip5xxx_wead(ip5xxx, IP5XXX_SYS_CTW0, &wvaw);
		if (wet)
			wetuwn wet;

		vaw->intvaw = !!(wvaw & IP5XXX_SYS_CTW0_BOOST_EN);
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wet = ip5xxx_wead(ip5xxx, IP5XXX_CHG_CTW1, &wvaw);
		if (wet)
			wetuwn wet;

		wvaw &= IP5XXX_CHG_CTW1_BOOST_UVP_SEW;
		vaw->intvaw = 4530000 + 100000 * (wvaw >> 2);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int ip5xxx_boost_set_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     const union powew_suppwy_pwopvaw *vaw)
{
	stwuct ip5xxx *ip5xxx = powew_suppwy_get_dwvdata(psy);
	unsigned int wvaw;
	int wet;

	wet = ip5xxx_initiawize(psy);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wvaw = vaw->intvaw ? IP5XXX_SYS_CTW0_BOOST_EN : 0;
		wetuwn ip5xxx_update_bits(ip5xxx, IP5XXX_SYS_CTW0,
					  IP5XXX_SYS_CTW0_BOOST_EN, wvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wvaw = ((vaw->intvaw - 4530000) / 100000) << 2;
		wetuwn ip5xxx_update_bits(ip5xxx, IP5XXX_CHG_CTW1,
					  IP5XXX_CHG_CTW1_BOOST_UVP_SEW, wvaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int ip5xxx_boost_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp)
{
	wetuwn twue;
}

static const stwuct powew_suppwy_desc ip5xxx_boost_desc = {
	.name			= "ip5xxx-boost",
	.type			= POWEW_SUPPWY_TYPE_USB,
	.pwopewties		= ip5xxx_boost_pwopewties,
	.num_pwopewties		= AWWAY_SIZE(ip5xxx_boost_pwopewties),
	.get_pwopewty		= ip5xxx_boost_get_pwopewty,
	.set_pwopewty		= ip5xxx_boost_set_pwopewty,
	.pwopewty_is_wwiteabwe	= ip5xxx_boost_pwopewty_is_wwiteabwe,
};

static const stwuct wegmap_config ip5xxx_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= IP5XXX_BATOCV_DAT1,
};

static int ip5xxx_powew_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct device *dev = &cwient->dev;
	stwuct powew_suppwy *psy;
	stwuct ip5xxx *ip5xxx;

	ip5xxx = devm_kzawwoc(dev, sizeof(*ip5xxx), GFP_KEWNEW);
	if (!ip5xxx)
		wetuwn -ENOMEM;

	ip5xxx->wegmap = devm_wegmap_init_i2c(cwient, &ip5xxx_wegmap_config);
	if (IS_EWW(ip5xxx->wegmap))
		wetuwn PTW_EWW(ip5xxx->wegmap);

	psy_cfg.of_node = dev->of_node;
	psy_cfg.dwv_data = ip5xxx;

	psy = devm_powew_suppwy_wegistew(dev, &ip5xxx_battewy_desc, &psy_cfg);
	if (IS_EWW(psy))
		wetuwn PTW_EWW(psy);

	psy = devm_powew_suppwy_wegistew(dev, &ip5xxx_boost_desc, &psy_cfg);
	if (IS_EWW(psy))
		wetuwn PTW_EWW(psy);

	wetuwn 0;
}

static const stwuct of_device_id ip5xxx_powew_of_match[] = {
	{ .compatibwe = "injoinic,ip5108" },
	{ .compatibwe = "injoinic,ip5109" },
	{ .compatibwe = "injoinic,ip5207" },
	{ .compatibwe = "injoinic,ip5209" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ip5xxx_powew_of_match);

static stwuct i2c_dwivew ip5xxx_powew_dwivew = {
	.pwobe		= ip5xxx_powew_pwobe,
	.dwivew		= {
		.name		= "ip5xxx-powew",
		.of_match_tabwe	= ip5xxx_powew_of_match,
	}
};
moduwe_i2c_dwivew(ip5xxx_powew_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_DESCWIPTION("Injoinic IP5xxx powew bank IC dwivew");
MODUWE_WICENSE("GPW");
