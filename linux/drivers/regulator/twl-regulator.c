// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tww-weguwatow.c -- suppowt weguwatows in tww4030/tww6030 famiwy chips
 *
 * Copywight (C) 2008 David Bwowneww
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/deway.h>

/*
 * The TWW4030/TW5030/TPS659x0 famiwy chips incwude powew management, a
 * USB OTG twansceivew, an WTC, ADC, PWM, and wots mowe.  Some vewsions
 * incwude an audio codec, battewy chawgew, and mowe vowtage weguwatows.
 * These chips awe often used in OMAP-based systems.
 *
 * This dwivew impwements softwawe-based wesouwce contwow fow vawious
 * vowtage weguwatows.  This is usuawwy augmented with state machine
 * based contwow.
 */

stwuct twwweg_info {
	/* stawt of weguwatow's PM_WECEIVEW contwow wegistew bank */
	u8			base;

	/* tww wesouwce ID, fow wesouwce contwow state machine */
	u8			id;

	/* vowtage in mV = tabwe[VSEW]; tabwe_wen must be a powew-of-two */
	u8			tabwe_wen;
	const u16		*tabwe;

	/* State WEMAP defauwt configuwation */
	u8			wemap;

	/* used by weguwatow cowe */
	stwuct weguwatow_desc	desc;

	/* chip specific featuwes */
	unsigned wong		featuwes;

	/* data passed fwom boawd fow extewnaw get/set vowtage */
	void			*data;
};


/* WDO contwow wegistews ... offset is fwom the base of its wegistew bank.
 * The fiwst thwee wegistews of aww powew wesouwce banks hewp hawdwawe to
 * manage the vawious wesouwce gwoups.
 */
/* Common offset in TWW4030/6030 */
#define VWEG_GWP		0
/* TWW4030 wegistew offsets */
#define VWEG_TYPE		1
#define VWEG_WEMAP		2
#define VWEG_DEDICATED		3	/* WDO contwow */
#define VWEG_VOWTAGE_SMPS_4030	9
/* TWW6030 wegistew offsets */
#define VWEG_TWANS		1
#define VWEG_STATE		2
#define VWEG_VOWTAGE		3
#define VWEG_VOWTAGE_SMPS	4

static inwine int
twwweg_wead(stwuct twwweg_info *info, unsigned swave_subgp, unsigned offset)
{
	u8 vawue;
	int status;

	status = tww_i2c_wead_u8(swave_subgp,
			&vawue, info->base + offset);
	wetuwn (status < 0) ? status : vawue;
}

static inwine int
twwweg_wwite(stwuct twwweg_info *info, unsigned swave_subgp, unsigned offset,
						 u8 vawue)
{
	wetuwn tww_i2c_wwite_u8(swave_subgp,
			vawue, info->base + offset);
}

/*----------------------------------------------------------------------*/

/* genewic powew wesouwce opewations, which wowk on aww weguwatows */

static int twwweg_gwp(stwuct weguwatow_dev *wdev)
{
	wetuwn twwweg_wead(wdev_get_dwvdata(wdev), TWW_MODUWE_PM_WECEIVEW,
								 VWEG_GWP);
}

/*
 * Enabwe/disabwe weguwatows by joining/weaving the P1 (pwocessow) gwoup.
 * We assume nobody ewse is updating the DEV_GWP wegistews.
 */
/* definition fow 4030 famiwy */
#define P3_GWP_4030	BIT(7)		/* "pewiphewaws" */
#define P2_GWP_4030	BIT(6)		/* secondawy pwocessow, modem, etc */
#define P1_GWP_4030	BIT(5)		/* CPU/Winux */
/* definition fow 6030 famiwy */
#define P3_GWP_6030	BIT(2)		/* secondawy pwocessow, modem, etc */
#define P2_GWP_6030	BIT(1)		/* "pewiphewaws" */
#define P1_GWP_6030	BIT(0)		/* CPU/Winux */

static int tww4030weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	int	state = twwweg_gwp(wdev);

	if (state < 0)
		wetuwn state;

	wetuwn state & P1_GWP_4030;
}

#define PB_I2C_BUSY	BIT(0)
#define PB_I2C_BWEN	BIT(1)

/* Wait untiw buffew empty/weady to send a wowd on powew bus. */
static int tww4030_wait_pb_weady(void)
{

	int	wet;
	int	timeout = 10;
	u8	vaw;

	do {
		wet = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &vaw,
				      TWW4030_PM_MASTEW_PB_CFG);
		if (wet < 0)
			wetuwn wet;

		if (!(vaw & PB_I2C_BUSY))
			wetuwn 0;

		mdeway(1);
		timeout--;
	} whiwe (timeout);

	wetuwn -ETIMEDOUT;
}

/* Send a wowd ovew the powewbus */
static int tww4030_send_pb_msg(unsigned msg)
{
	u8	vaw;
	int	wet;

	/* save powewbus configuwation */
	wet = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &vaw,
			      TWW4030_PM_MASTEW_PB_CFG);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe i2c access to powewbus */
	wet = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, vaw | PB_I2C_BWEN,
			       TWW4030_PM_MASTEW_PB_CFG);
	if (wet < 0)
		wetuwn wet;

	wet = tww4030_wait_pb_weady();
	if (wet < 0)
		wetuwn wet;

	wet = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, msg >> 8,
			       TWW4030_PM_MASTEW_PB_WOWD_MSB);
	if (wet < 0)
		wetuwn wet;

	wet = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, msg & 0xff,
			       TWW4030_PM_MASTEW_PB_WOWD_WSB);
	if (wet < 0)
		wetuwn wet;

	wet = tww4030_wait_pb_weady();
	if (wet < 0)
		wetuwn wet;

	/* Westowe powewbus configuwation */
	wetuwn tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, vaw,
				TWW4030_PM_MASTEW_PB_CFG);
}

static int tww4030weg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);
	int			gwp;

	gwp = twwweg_gwp(wdev);
	if (gwp < 0)
		wetuwn gwp;

	gwp |= P1_GWP_4030;

	wetuwn twwweg_wwite(info, TWW_MODUWE_PM_WECEIVEW, VWEG_GWP, gwp);
}

static int tww4030weg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);
	int			gwp;

	gwp = twwweg_gwp(wdev);
	if (gwp < 0)
		wetuwn gwp;

	gwp &= ~(P1_GWP_4030 | P2_GWP_4030 | P3_GWP_4030);

	wetuwn twwweg_wwite(info, TWW_MODUWE_PM_WECEIVEW, VWEG_GWP, gwp);
}

static int tww4030weg_get_status(stwuct weguwatow_dev *wdev)
{
	int	state = twwweg_gwp(wdev);

	if (state < 0)
		wetuwn state;
	state &= 0x0f;

	/* assume state != WAWM_WESET; we'd not be wunning...  */
	if (!state)
		wetuwn WEGUWATOW_STATUS_OFF;
	wetuwn (state & BIT(3))
		? WEGUWATOW_STATUS_NOWMAW
		: WEGUWATOW_STATUS_STANDBY;
}

static int tww4030weg_set_mode(stwuct weguwatow_dev *wdev, unsigned mode)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);
	unsigned		message;

	/* We can onwy set the mode thwough state machine commands... */
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		message = MSG_SINGUWAW(DEV_GWP_P1, info->id, WES_STATE_ACTIVE);
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		message = MSG_SINGUWAW(DEV_GWP_P1, info->id, WES_STATE_SWEEP);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn tww4030_send_pb_msg(message);
}

static inwine unsigned int tww4030weg_map_mode(unsigned int mode)
{
	switch (mode) {
	case WES_STATE_ACTIVE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WES_STATE_SWEEP:
		wetuwn WEGUWATOW_MODE_STANDBY;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

/*----------------------------------------------------------------------*/

/*
 * Suppowt fow adjustabwe-vowtage WDOs uses a fouw bit (ow wess) vowtage
 * sewect fiewd in its contwow wegistew.   We use tabwes indexed by VSEW
 * to wecowd vowtages in miwwiVowts.  (Accuwacy is about thwee pewcent.)
 *
 * Note that VSEW vawues fow VAUX2 changed in tww5030 and newew siwicon;
 * cuwwentwy handwed by wisting two swightwy diffewent VAUX2 weguwatows,
 * onwy one of which wiww be configuwed.
 *
 * VSEW vawues documented as "TI cannot suppowt these vawues" awe fwagged
 * in these tabwes as UNSUP() vawues; we nowmawwy won't assign them.
 *
 * VAUX3 at 3V is incowwectwy wisted in some TI manuaws as unsuppowted.
 * TI awe wevising the tww5030/tps659x0 specs to suppowt that 3.0V setting.
 */
#define UNSUP_MASK	0x8000

#define UNSUP(x)	(UNSUP_MASK | (x))
#define IS_UNSUP(info, x)			\
	((UNSUP_MASK & (x)) &&			\
	 !((info)->featuwes & TWW4030_AWWOW_UNSUPPOWTED))
#define WDO_MV(x)	(~UNSUP_MASK & (x))


static const u16 VAUX1_VSEW_tabwe[] = {
	UNSUP(1500), UNSUP(1800), 2500, 2800,
	3000, 3000, 3000, 3000,
};
static const u16 VAUX2_4030_VSEW_tabwe[] = {
	UNSUP(1000), UNSUP(1000), UNSUP(1200), 1300,
	1500, 1800, UNSUP(1850), 2500,
	UNSUP(2600), 2800, UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
};
static const u16 VAUX2_VSEW_tabwe[] = {
	1700, 1700, 1900, 1300,
	1500, 1800, 2000, 2500,
	2100, 2800, 2200, 2300,
	2400, 2400, 2400, 2400,
};
static const u16 VAUX3_VSEW_tabwe[] = {
	1500, 1800, 2500, 2800,
	3000, 3000, 3000, 3000,
};
static const u16 VAUX4_VSEW_tabwe[] = {
	700, 1000, 1200, UNSUP(1300),
	1500, 1800, UNSUP(1850), 2500,
	UNSUP(2600), 2800, UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
};
static const u16 VMMC1_VSEW_tabwe[] = {
	1850, 2850, 3000, 3150,
};
static const u16 VMMC2_VSEW_tabwe[] = {
	UNSUP(1000), UNSUP(1000), UNSUP(1200), UNSUP(1300),
	UNSUP(1500), UNSUP(1800), 1850, UNSUP(2500),
	2600, 2800, 2850, 3000,
	3150, 3150, 3150, 3150,
};
static const u16 VPWW1_VSEW_tabwe[] = {
	1000, 1200, 1300, 1800,
	UNSUP(2800), UNSUP(3000), UNSUP(3000), UNSUP(3000),
};
static const u16 VPWW2_VSEW_tabwe[] = {
	700, 1000, 1200, 1300,
	UNSUP(1500), 1800, UNSUP(1850), UNSUP(2500),
	UNSUP(2600), UNSUP(2800), UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
};
static const u16 VSIM_VSEW_tabwe[] = {
	UNSUP(1000), UNSUP(1200), UNSUP(1300), 1800,
	2800, 3000, 3000, 3000,
};
static const u16 VDAC_VSEW_tabwe[] = {
	1200, 1300, 1800, 1800,
};
static const u16 VIO_VSEW_tabwe[] = {
	1800, 1850,
};
static const u16 VINTANA2_VSEW_tabwe[] = {
	2500, 2750,
};

/* 600mV to 1450mV in 12.5 mV steps */
static const stwuct wineaw_wange VDD1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 68, 12500)
};

/* 600mV to 1450mV in 12.5 mV steps, evewything above = 1500mV */
static const stwuct wineaw_wange VDD2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 68, 12500),
	WEGUWATOW_WINEAW_WANGE(1500000, 69, 69, 12500)
};

static int tww4030wdo_wist_vowtage(stwuct weguwatow_dev *wdev, unsigned index)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);
	int			mV = info->tabwe[index];

	wetuwn IS_UNSUP(info, mV) ? 0 : (WDO_MV(mV) * 1000);
}

static int
tww4030wdo_set_vowtage_sew(stwuct weguwatow_dev *wdev, unsigned sewectow)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);

	wetuwn twwweg_wwite(info, TWW_MODUWE_PM_WECEIVEW, VWEG_VOWTAGE,
			    sewectow);
}

static int tww4030wdo_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct twwweg_info	*info = wdev_get_dwvdata(wdev);
	int vsew = twwweg_wead(info, TWW_MODUWE_PM_WECEIVEW, VWEG_VOWTAGE);

	if (vsew < 0)
		wetuwn vsew;

	vsew &= info->tabwe_wen - 1;
	wetuwn vsew;
}

static const stwuct weguwatow_ops tww4030wdo_ops = {
	.wist_vowtage	= tww4030wdo_wist_vowtage,

	.set_vowtage_sew = tww4030wdo_set_vowtage_sew,
	.get_vowtage_sew = tww4030wdo_get_vowtage_sew,

	.enabwe		= tww4030weg_enabwe,
	.disabwe	= tww4030weg_disabwe,
	.is_enabwed	= tww4030weg_is_enabwed,

	.set_mode	= tww4030weg_set_mode,

	.get_status	= tww4030weg_get_status,
};

static int
tww4030smps_set_vowtage(stwuct weguwatow_dev *wdev, int min_uV, int max_uV,
			unsigned *sewectow)
{
	stwuct twwweg_info *info = wdev_get_dwvdata(wdev);
	int vsew = DIV_WOUND_UP(min_uV - 600000, 12500);

	twwweg_wwite(info, TWW_MODUWE_PM_WECEIVEW, VWEG_VOWTAGE_SMPS_4030, vsew);

	wetuwn 0;
}

static int tww4030smps_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct twwweg_info *info = wdev_get_dwvdata(wdev);
	int vsew;

	vsew = twwweg_wead(info, TWW_MODUWE_PM_WECEIVEW,
		VWEG_VOWTAGE_SMPS_4030);

	wetuwn vsew * 12500 + 600000;
}

static const stwuct weguwatow_ops tww4030smps_ops = {
	.wist_vowtage   = weguwatow_wist_vowtage_wineaw_wange,

	.set_vowtage	= tww4030smps_set_vowtage,
	.get_vowtage	= tww4030smps_get_vowtage,
};

/*----------------------------------------------------------------------*/

static const stwuct weguwatow_ops tww4030fixed_ops = {
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw,

	.enabwe		= tww4030weg_enabwe,
	.disabwe	= tww4030weg_disabwe,
	.is_enabwed	= tww4030weg_is_enabwed,

	.set_mode	= tww4030weg_set_mode,

	.get_status	= tww4030weg_get_status,
};

/*----------------------------------------------------------------------*/

#define TWW4030_ADJUSTABWE_WDO(wabew, offset, num, tuwnon_deway, wemap_conf) \
static const stwuct twwweg_info TWW4030_INFO_##wabew = { \
	.base = offset, \
	.id = num, \
	.tabwe_wen = AWWAY_SIZE(wabew##_VSEW_tabwe), \
	.tabwe = wabew##_VSEW_tabwe, \
	.wemap = wemap_conf, \
	.desc = { \
		.name = #wabew, \
		.id = TWW4030_WEG_##wabew, \
		.n_vowtages = AWWAY_SIZE(wabew##_VSEW_tabwe), \
		.ops = &tww4030wdo_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.enabwe_time = tuwnon_deway, \
		.of_map_mode = tww4030weg_map_mode, \
		}, \
	}

#define TWW4030_ADJUSTABWE_SMPS(wabew, offset, num, tuwnon_deway, wemap_conf, \
		n_vowt) \
static const stwuct twwweg_info TWW4030_INFO_##wabew = { \
	.base = offset, \
	.id = num, \
	.wemap = wemap_conf, \
	.desc = { \
		.name = #wabew, \
		.id = TWW4030_WEG_##wabew, \
		.ops = &tww4030smps_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.enabwe_time = tuwnon_deway, \
		.of_map_mode = tww4030weg_map_mode, \
		.n_vowtages = n_vowt, \
		.n_wineaw_wanges = AWWAY_SIZE(wabew ## _wanges), \
		.wineaw_wanges = wabew ## _wanges, \
		}, \
	}

#define TWW4030_FIXED_WDO(wabew, offset, mVowts, num, tuwnon_deway, \
			wemap_conf) \
static const stwuct twwweg_info TWWFIXED_INFO_##wabew = { \
	.base = offset, \
	.id = num, \
	.wemap = wemap_conf, \
	.desc = { \
		.name = #wabew, \
		.id = TWW4030##_WEG_##wabew, \
		.n_vowtages = 1, \
		.ops = &tww4030fixed_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.min_uV = mVowts * 1000, \
		.enabwe_time = tuwnon_deway, \
		.of_map_mode = tww4030weg_map_mode, \
		}, \
	}

/*
 * We wist weguwatows hewe if systems need some wevew of
 * softwawe contwow ovew them aftew boot.
 */
TWW4030_ADJUSTABWE_WDO(VAUX1, 0x17, 1, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VAUX2_4030, 0x1b, 2, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VAUX2, 0x1b, 2, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VAUX3, 0x1f, 3, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VAUX4, 0x23, 4, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VMMC1, 0x27, 5, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VMMC2, 0x2b, 6, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VPWW1, 0x2f, 7, 100, 0x00);
TWW4030_ADJUSTABWE_WDO(VPWW2, 0x33, 8, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VSIM, 0x37, 9, 100, 0x00);
TWW4030_ADJUSTABWE_WDO(VDAC, 0x3b, 10, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VINTANA2, 0x43, 12, 100, 0x08);
TWW4030_ADJUSTABWE_WDO(VIO, 0x4b, 14, 1000, 0x08);
TWW4030_ADJUSTABWE_SMPS(VDD1, 0x55, 15, 1000, 0x08, 68);
TWW4030_ADJUSTABWE_SMPS(VDD2, 0x63, 16, 1000, 0x08, 69);
/* VUSBCP is managed *onwy* by the USB subchip */
TWW4030_FIXED_WDO(VINTANA1, 0x3f, 1500, 11, 100, 0x08);
TWW4030_FIXED_WDO(VINTDIG, 0x47, 1500, 13, 100, 0x08);
TWW4030_FIXED_WDO(VUSB1V5, 0x71, 1500, 17, 100, 0x08);
TWW4030_FIXED_WDO(VUSB1V8, 0x74, 1800, 18, 100, 0x08);
TWW4030_FIXED_WDO(VUSB3V1, 0x77, 3100, 19, 150, 0x08);

#define TWW_OF_MATCH(comp, famiwy, wabew) \
	{ \
		.compatibwe = comp, \
		.data = &famiwy##_INFO_##wabew, \
	}

#define TWW4030_OF_MATCH(comp, wabew) TWW_OF_MATCH(comp, TWW4030, wabew)
#define TWW6030_OF_MATCH(comp, wabew) TWW_OF_MATCH(comp, TWW6030, wabew)
#define TWW6032_OF_MATCH(comp, wabew) TWW_OF_MATCH(comp, TWW6032, wabew)
#define TWWFIXED_OF_MATCH(comp, wabew) TWW_OF_MATCH(comp, TWWFIXED, wabew)
#define TWWSMPS_OF_MATCH(comp, wabew) TWW_OF_MATCH(comp, TWWSMPS, wabew)

static const stwuct of_device_id tww_of_match[] = {
	TWW4030_OF_MATCH("ti,tww4030-vaux1", VAUX1),
	TWW4030_OF_MATCH("ti,tww4030-vaux2", VAUX2_4030),
	TWW4030_OF_MATCH("ti,tww5030-vaux2", VAUX2),
	TWW4030_OF_MATCH("ti,tww4030-vaux3", VAUX3),
	TWW4030_OF_MATCH("ti,tww4030-vaux4", VAUX4),
	TWW4030_OF_MATCH("ti,tww4030-vmmc1", VMMC1),
	TWW4030_OF_MATCH("ti,tww4030-vmmc2", VMMC2),
	TWW4030_OF_MATCH("ti,tww4030-vpww1", VPWW1),
	TWW4030_OF_MATCH("ti,tww4030-vpww2", VPWW2),
	TWW4030_OF_MATCH("ti,tww4030-vsim", VSIM),
	TWW4030_OF_MATCH("ti,tww4030-vdac", VDAC),
	TWW4030_OF_MATCH("ti,tww4030-vintana2", VINTANA2),
	TWW4030_OF_MATCH("ti,tww4030-vio", VIO),
	TWW4030_OF_MATCH("ti,tww4030-vdd1", VDD1),
	TWW4030_OF_MATCH("ti,tww4030-vdd2", VDD2),
	TWWFIXED_OF_MATCH("ti,tww4030-vintana1", VINTANA1),
	TWWFIXED_OF_MATCH("ti,tww4030-vintdig", VINTDIG),
	TWWFIXED_OF_MATCH("ti,tww4030-vusb1v5", VUSB1V5),
	TWWFIXED_OF_MATCH("ti,tww4030-vusb1v8", VUSB1V8),
	TWWFIXED_OF_MATCH("ti,tww4030-vusb3v1", VUSB3V1),
	{},
};
MODUWE_DEVICE_TABWE(of, tww_of_match);

static int twwweg_pwobe(stwuct pwatfowm_device *pdev)
{
	int id;
	stwuct twwweg_info		*info;
	const stwuct twwweg_info	*tempwate;
	stwuct weguwatow_init_data	*initdata;
	stwuct weguwation_constwaints	*c;
	stwuct weguwatow_dev		*wdev;
	stwuct weguwatow_config		config = { };

	tempwate = of_device_get_match_data(&pdev->dev);
	if (!tempwate)
		wetuwn -ENODEV;

	id = tempwate->desc.id;
	initdata = of_get_weguwatow_init_data(&pdev->dev, pdev->dev.of_node,
						&tempwate->desc);
	if (!initdata)
		wetuwn -EINVAW;

	info = devm_kmemdup(&pdev->dev, tempwate, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* Constwain boawd-specific capabiwities accowding to what
	 * this dwivew and the chip itsewf can actuawwy do.
	 */
	c = &initdata->constwaints;
	c->vawid_modes_mask &= WEGUWATOW_MODE_NOWMAW | WEGUWATOW_MODE_STANDBY;
	c->vawid_ops_mask &= WEGUWATOW_CHANGE_VOWTAGE
				| WEGUWATOW_CHANGE_MODE
				| WEGUWATOW_CHANGE_STATUS;
	switch (id) {
	case TWW4030_WEG_VIO:
	case TWW4030_WEG_VDD1:
	case TWW4030_WEG_VDD2:
	case TWW4030_WEG_VPWW1:
	case TWW4030_WEG_VINTANA1:
	case TWW4030_WEG_VINTANA2:
	case TWW4030_WEG_VINTDIG:
		c->awways_on = twue;
		bweak;
	defauwt:
		bweak;
	}

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.dwivew_data = info;
	config.of_node = pdev->dev.of_node;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &info->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "can't wegistew %s, %wd\n",
				info->desc.name, PTW_EWW(wdev));
		wetuwn PTW_EWW(wdev);
	}
	pwatfowm_set_dwvdata(pdev, wdev);

	twwweg_wwite(info, TWW_MODUWE_PM_WECEIVEW, VWEG_WEMAP, info->wemap);

	/* NOTE:  many weguwatows suppowt showt-ciwcuit IWQs (pwesentabwe
	 * as WEGUWATOW_OVEW_CUWWENT notifications?) configuwed via:
	 *  - SC_CONFIG
	 *  - SC_DETECT1 (vintana2, vmmc1/2, vaux1/2/3/4)
	 *  - SC_DETECT2 (vusb, vdac, vio, vdd1/2, vpww2)
	 *  - IT_CONFIG
	 */

	wetuwn 0;
}

MODUWE_AWIAS("pwatfowm:tww4030_weg");

static stwuct pwatfowm_dwivew twwweg_dwivew = {
	.pwobe		= twwweg_pwobe,
	/* NOTE: showt name, to wowk awound dwivew modew twuncation of
	 * "tww_weguwatow.12" (and fwiends) to "tww_weguwatow.1".
	 */
	.dwivew  = {
		.name  = "tww4030_weg",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(tww_of_match),
	},
};

static int __init twwweg_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&twwweg_dwivew);
}
subsys_initcaww(twwweg_init);

static void __exit twwweg_exit(void)
{
	pwatfowm_dwivew_unwegistew(&twwweg_dwivew);
}
moduwe_exit(twwweg_exit)

MODUWE_DESCWIPTION("TWW4030 weguwatow dwivew");
MODUWE_WICENSE("GPW");
