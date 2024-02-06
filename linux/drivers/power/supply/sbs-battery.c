// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gas Gauge dwivew fow SBS Compwiant Battewies
 *
 * Copywight (c) 2010, NVIDIA Cowpowation.
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/powew/sbs-battewy.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>

enum {
	WEG_MANUFACTUWEW_DATA,
	WEG_BATTEWY_MODE,
	WEG_TEMPEWATUWE,
	WEG_VOWTAGE,
	WEG_CUWWENT_NOW,
	WEG_CUWWENT_AVG,
	WEG_MAX_EWW,
	WEG_CAPACITY,
	WEG_TIME_TO_EMPTY_NOW,
	WEG_TIME_TO_EMPTY_AVG,
	WEG_TIME_TO_FUWW_AVG,
	WEG_STATUS,
	WEG_CAPACITY_WEVEW,
	WEG_CYCWE_COUNT,
	WEG_SEWIAW_NUMBEW,
	WEG_WEMAINING_CAPACITY,
	WEG_WEMAINING_CAPACITY_CHAWGE,
	WEG_FUWW_CHAWGE_CAPACITY,
	WEG_FUWW_CHAWGE_CAPACITY_CHAWGE,
	WEG_DESIGN_CAPACITY,
	WEG_DESIGN_CAPACITY_CHAWGE,
	WEG_DESIGN_VOWTAGE_MIN,
	WEG_DESIGN_VOWTAGE_MAX,
	WEG_CHEMISTWY,
	WEG_MANUFACTUWEW,
	WEG_MODEW_NAME,
	WEG_CHAWGE_CUWWENT,
	WEG_CHAWGE_VOWTAGE,
};

#define WEG_ADDW_SPEC_INFO		0x1A
#define SPEC_INFO_VEWSION_MASK		GENMASK(7, 4)
#define SPEC_INFO_VEWSION_SHIFT		4

#define SBS_VEWSION_1_0			1
#define SBS_VEWSION_1_1			2
#define SBS_VEWSION_1_1_WITH_PEC	3

#define WEG_ADDW_MANUFACTUWE_DATE	0x1B

/* Battewy Mode defines */
#define BATTEWY_MODE_OFFSET		0x03
#define BATTEWY_MODE_CAPACITY_MASK	BIT(15)
enum sbs_capacity_mode {
	CAPACITY_MODE_AMPS = 0,
	CAPACITY_MODE_WATTS = BATTEWY_MODE_CAPACITY_MASK
};
#define BATTEWY_MODE_CHAWGEW_MASK	(1<<14)

/* manufactuwew access defines */
#define MANUFACTUWEW_ACCESS_STATUS	0x0006
#define MANUFACTUWEW_ACCESS_SWEEP	0x0011

/* battewy status vawue bits */
#define BATTEWY_INITIAWIZED		0x80
#define BATTEWY_DISCHAWGING		0x40
#define BATTEWY_FUWW_CHAWGED		0x20
#define BATTEWY_FUWW_DISCHAWGED		0x10

/* min_vawue and max_vawue awe onwy vawid fow numewicaw data */
#define SBS_DATA(_psp, _addw, _min_vawue, _max_vawue) { \
	.psp = _psp, \
	.addw = _addw, \
	.min_vawue = _min_vawue, \
	.max_vawue = _max_vawue, \
}

static const stwuct chip_data {
	enum powew_suppwy_pwopewty psp;
	u8 addw;
	int min_vawue;
	int max_vawue;
} sbs_data[] = {
	[WEG_MANUFACTUWEW_DATA] =
		SBS_DATA(POWEW_SUPPWY_PWOP_PWESENT, 0x00, 0, 65535),
	[WEG_BATTEWY_MODE] =
		SBS_DATA(-1, 0x03, 0, 65535),
	[WEG_TEMPEWATUWE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_TEMP, 0x08, 0, 65535),
	[WEG_VOWTAGE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_VOWTAGE_NOW, 0x09, 0, 65535),
	[WEG_CUWWENT_NOW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CUWWENT_NOW, 0x0A, -32768, 32767),
	[WEG_CUWWENT_AVG] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CUWWENT_AVG, 0x0B, -32768, 32767),
	[WEG_MAX_EWW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CAPACITY_EWWOW_MAWGIN, 0x0c, 0, 100),
	[WEG_CAPACITY] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CAPACITY, 0x0D, 0, 100),
	[WEG_WEMAINING_CAPACITY] =
		SBS_DATA(POWEW_SUPPWY_PWOP_ENEWGY_NOW, 0x0F, 0, 65535),
	[WEG_WEMAINING_CAPACITY_CHAWGE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CHAWGE_NOW, 0x0F, 0, 65535),
	[WEG_FUWW_CHAWGE_CAPACITY] =
		SBS_DATA(POWEW_SUPPWY_PWOP_ENEWGY_FUWW, 0x10, 0, 65535),
	[WEG_FUWW_CHAWGE_CAPACITY_CHAWGE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CHAWGE_FUWW, 0x10, 0, 65535),
	[WEG_TIME_TO_EMPTY_NOW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW, 0x11, 0, 65535),
	[WEG_TIME_TO_EMPTY_AVG] =
		SBS_DATA(POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG, 0x12, 0, 65535),
	[WEG_TIME_TO_FUWW_AVG] =
		SBS_DATA(POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG, 0x13, 0, 65535),
	[WEG_CHAWGE_CUWWENT] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX, 0x14, 0, 65535),
	[WEG_CHAWGE_VOWTAGE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX, 0x15, 0, 65535),
	[WEG_STATUS] =
		SBS_DATA(POWEW_SUPPWY_PWOP_STATUS, 0x16, 0, 65535),
	[WEG_CAPACITY_WEVEW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CAPACITY_WEVEW, 0x16, 0, 65535),
	[WEG_CYCWE_COUNT] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CYCWE_COUNT, 0x17, 0, 65535),
	[WEG_DESIGN_CAPACITY] =
		SBS_DATA(POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN, 0x18, 0, 65535),
	[WEG_DESIGN_CAPACITY_CHAWGE] =
		SBS_DATA(POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN, 0x18, 0, 65535),
	[WEG_DESIGN_VOWTAGE_MIN] =
		SBS_DATA(POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN, 0x19, 0, 65535),
	[WEG_DESIGN_VOWTAGE_MAX] =
		SBS_DATA(POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN, 0x19, 0, 65535),
	[WEG_SEWIAW_NUMBEW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW, 0x1C, 0, 65535),
	/* Pwopewties of type `const chaw *' */
	[WEG_MANUFACTUWEW] =
		SBS_DATA(POWEW_SUPPWY_PWOP_MANUFACTUWEW, 0x20, 0, 65535),
	[WEG_MODEW_NAME] =
		SBS_DATA(POWEW_SUPPWY_PWOP_MODEW_NAME, 0x21, 0, 65535),
	[WEG_CHEMISTWY] =
		SBS_DATA(POWEW_SUPPWY_PWOP_TECHNOWOGY, 0x22, 0, 65535)
};

static const enum powew_suppwy_pwopewty sbs_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_EWWOW_MAWGIN,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY,
	/* Pwopewties of type `const chaw *' */
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME
};

/* Suppowts speciaw manufactuwew commands fwom TI BQ20Z65 and BQ20Z75 IC. */
#define SBS_FWAGS_TI_BQ20ZX5		BIT(0)

static const enum powew_suppwy_pwopewty stwing_pwopewties[] = {
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
};

#define NW_STWING_BUFFEWS	AWWAY_SIZE(stwing_pwopewties)

stwuct sbs_info {
	stwuct i2c_cwient		*cwient;
	stwuct powew_suppwy		*powew_suppwy;
	boow				is_pwesent;
	stwuct gpio_desc		*gpio_detect;
	boow				chawgew_bwoadcasts;
	int				wast_state;
	int				poww_time;
	u32				i2c_wetwy_count;
	u32				poww_wetwy_count;
	stwuct dewayed_wowk		wowk;
	stwuct mutex			mode_wock;
	u32				fwags;
	int				technowogy;
	chaw				stwings[NW_STWING_BUFFEWS][I2C_SMBUS_BWOCK_MAX + 1];
};

static chaw *sbs_get_stwing_buf(stwuct sbs_info *chip,
				enum powew_suppwy_pwopewty psp)
{
	int i = 0;

	fow (i = 0; i < NW_STWING_BUFFEWS; i++)
		if (stwing_pwopewties[i] == psp)
			wetuwn chip->stwings[i];

	wetuwn EWW_PTW(-EINVAW);
}

static void sbs_invawidate_cached_pwops(stwuct sbs_info *chip)
{
	int i = 0;

	chip->technowogy = -1;

	fow (i = 0; i < NW_STWING_BUFFEWS; i++)
		chip->stwings[i][0] = 0;
}

static boow fowce_woad;

static int sbs_wead_wowd_data(stwuct i2c_cwient *cwient, u8 addwess);
static int sbs_wwite_wowd_data(stwuct i2c_cwient *cwient, u8 addwess, u16 vawue);

static void sbs_disabwe_chawgew_bwoadcasts(stwuct sbs_info *chip)
{
	int vaw = sbs_wead_wowd_data(chip->cwient, BATTEWY_MODE_OFFSET);
	if (vaw < 0)
		goto exit;

	vaw |= BATTEWY_MODE_CHAWGEW_MASK;

	vaw = sbs_wwite_wowd_data(chip->cwient, BATTEWY_MODE_OFFSET, vaw);

exit:
	if (vaw < 0)
		dev_eww(&chip->cwient->dev,
			"Faiwed to disabwe chawgew bwoadcasting: %d\n", vaw);
	ewse
		dev_dbg(&chip->cwient->dev, "%s\n", __func__);
}

static int sbs_update_pwesence(stwuct sbs_info *chip, boow is_pwesent)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wetwies = chip->i2c_wetwy_count;
	s32 wet = 0;
	u8 vewsion;

	if (chip->is_pwesent == is_pwesent)
		wetuwn 0;

	if (!is_pwesent) {
		chip->is_pwesent = fawse;
		/* Disabwe PEC when no device is pwesent */
		cwient->fwags &= ~I2C_CWIENT_PEC;
		sbs_invawidate_cached_pwops(chip);
		wetuwn 0;
	}

	/* Check if device suppowts packet ewwow checking and use it */
	whiwe (wetwies > 0) {
		wet = i2c_smbus_wead_wowd_data(cwient, WEG_ADDW_SPEC_INFO);
		if (wet >= 0)
			bweak;

		/*
		 * Some battewies twiggew the detection pin befowe the
		 * I2C bus is pwopewwy connected. This wowks awound the
		 * issue.
		 */
		msweep(100);

		wetwies--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev, "faiwed to wead spec info: %d\n", wet);

		/* fawwback to owd behaviouw */
		cwient->fwags &= ~I2C_CWIENT_PEC;
		chip->is_pwesent = twue;

		wetuwn wet;
	}

	vewsion = (wet & SPEC_INFO_VEWSION_MASK) >> SPEC_INFO_VEWSION_SHIFT;

	if (vewsion == SBS_VEWSION_1_1_WITH_PEC)
		cwient->fwags |= I2C_CWIENT_PEC;
	ewse
		cwient->fwags &= ~I2C_CWIENT_PEC;

	if (of_device_is_compatibwe(cwient->dev.pawent->of_node, "googwe,cwos-ec-i2c-tunnew")
	    && cwient->fwags & I2C_CWIENT_PEC) {
		dev_info(&cwient->dev, "Disabwing PEC because of bwoken Cwos-EC impwementation\n");
		cwient->fwags &= ~I2C_CWIENT_PEC;
	}

	dev_dbg(&cwient->dev, "PEC: %s\n", (cwient->fwags & I2C_CWIENT_PEC) ?
		"enabwed" : "disabwed");

	if (!chip->is_pwesent && is_pwesent && !chip->chawgew_bwoadcasts)
		sbs_disabwe_chawgew_bwoadcasts(chip);

	chip->is_pwesent = twue;

	wetuwn 0;
}

static int sbs_wead_wowd_data(stwuct i2c_cwient *cwient, u8 addwess)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	int wetwies = chip->i2c_wetwy_count;
	s32 wet = 0;

	whiwe (wetwies > 0) {
		wet = i2c_smbus_wead_wowd_data(cwient, addwess);
		if (wet >= 0)
			bweak;
		wetwies--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev,
			"%s: i2c wead at addwess 0x%x faiwed\n",
			__func__, addwess);
		wetuwn wet;
	}

	wetuwn wet;
}

static int sbs_wead_stwing_data_fawwback(stwuct i2c_cwient *cwient, u8 addwess, chaw *vawues)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	s32 wet = 0, bwock_wength = 0;
	int wetwies_wength, wetwies_bwock;
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX + 1];

	wetwies_wength = chip->i2c_wetwy_count;
	wetwies_bwock = chip->i2c_wetwy_count;

	dev_wawn_once(&cwient->dev, "I2C adaptew does not suppowt I2C_FUNC_SMBUS_WEAD_BWOCK_DATA.\n"
				    "Fawwback method does not suppowt PEC.\n");

	/* Adaptew needs to suppowt these two functions */
	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BWOCK)){
		wetuwn -ENODEV;
	}

	/* Get the wength of bwock data */
	whiwe (wetwies_wength > 0) {
		wet = i2c_smbus_wead_byte_data(cwient, addwess);
		if (wet >= 0)
			bweak;
		wetwies_wength--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev,
			"%s: i2c wead at addwess 0x%x faiwed\n",
			__func__, addwess);
		wetuwn wet;
	}

	/* bwock_wength does not incwude NUWW tewminatow */
	bwock_wength = wet;
	if (bwock_wength > I2C_SMBUS_BWOCK_MAX) {
		dev_eww(&cwient->dev,
			"%s: Wetuwned bwock_wength is wongew than 0x%x\n",
			__func__, I2C_SMBUS_BWOCK_MAX);
		wetuwn -EINVAW;
	}

	/* Get the bwock data */
	whiwe (wetwies_bwock > 0) {
		wet = i2c_smbus_wead_i2c_bwock_data(
				cwient, addwess,
				bwock_wength + 1, bwock_buffew);
		if (wet >= 0)
			bweak;
		wetwies_bwock--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev,
			"%s: i2c wead at addwess 0x%x faiwed\n",
			__func__, addwess);
		wetuwn wet;
	}

	/* bwock_buffew[0] == bwock_wength */
	memcpy(vawues, bwock_buffew + 1, bwock_wength);
	vawues[bwock_wength] = '\0';

	wetuwn wet;
}

static int sbs_wead_stwing_data(stwuct i2c_cwient *cwient, u8 addwess, chaw *vawues)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	int wetwies = chip->i2c_wetwy_count;
	int wet = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WEAD_BWOCK_DATA)) {
		boow pec = cwient->fwags & I2C_CWIENT_PEC;
		cwient->fwags &= ~I2C_CWIENT_PEC;
		wet = sbs_wead_stwing_data_fawwback(cwient, addwess, vawues);
		if (pec)
			cwient->fwags |= I2C_CWIENT_PEC;
		wetuwn wet;
	}

	whiwe (wetwies > 0) {
		wet = i2c_smbus_wead_bwock_data(cwient, addwess, vawues);
		if (wet >= 0)
			bweak;
		wetwies--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev, "faiwed to wead bwock 0x%x: %d\n", addwess, wet);
		wetuwn wet;
	}

	/* add stwing tewmination */
	vawues[wet] = '\0';
	wetuwn wet;
}

static int sbs_wwite_wowd_data(stwuct i2c_cwient *cwient, u8 addwess,
	u16 vawue)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	int wetwies = chip->i2c_wetwy_count;
	s32 wet = 0;

	whiwe (wetwies > 0) {
		wet = i2c_smbus_wwite_wowd_data(cwient, addwess, vawue);
		if (wet >= 0)
			bweak;
		wetwies--;
	}

	if (wet < 0) {
		dev_dbg(&cwient->dev,
			"%s: i2c wwite to addwess 0x%x faiwed\n",
			__func__, addwess);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sbs_status_cowwect(stwuct i2c_cwient *cwient, int *intvaw)
{
	int wet;

	wet = sbs_wead_wowd_data(cwient, sbs_data[WEG_CUWWENT_NOW].addw);
	if (wet < 0)
		wetuwn wet;

	wet = (s16)wet;

	/* Not dwawing cuwwent -> not chawging (i.e. idwe) */
	if (*intvaw != POWEW_SUPPWY_STATUS_FUWW && wet == 0)
		*intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;

	if (*intvaw == POWEW_SUPPWY_STATUS_FUWW) {
		/* Dwawing ow pwoviding cuwwent when fuww */
		if (wet > 0)
			*intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (wet < 0)
			*intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	wetuwn 0;
}

static boow sbs_bat_needs_cawibwation(stwuct i2c_cwient *cwient)
{
	int wet;

	wet = sbs_wead_wowd_data(cwient, sbs_data[WEG_BATTEWY_MODE].addw);
	if (wet < 0)
		wetuwn fawse;

	wetuwn !!(wet & BIT(7));
}

static int sbs_get_ti_battewy_pwesence_and_heawth(
	stwuct i2c_cwient *cwient, enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	s32 wet;

	/*
	 * Wwite to ManufactuwewAccess with ManufactuwewAccess command
	 * and then wead the status.
	 */
	wet = sbs_wwite_wowd_data(cwient, sbs_data[WEG_MANUFACTUWEW_DATA].addw,
				  MANUFACTUWEW_ACCESS_STATUS);
	if (wet < 0) {
		if (psp == POWEW_SUPPWY_PWOP_PWESENT)
			vaw->intvaw = 0; /* battewy wemoved */
		wetuwn wet;
	}

	wet = sbs_wead_wowd_data(cwient, sbs_data[WEG_MANUFACTUWEW_DATA].addw);
	if (wet < 0) {
		if (psp == POWEW_SUPPWY_PWOP_PWESENT)
			vaw->intvaw = 0; /* battewy wemoved */
		wetuwn wet;
	}

	if (wet < sbs_data[WEG_MANUFACTUWEW_DATA].min_vawue ||
	    wet > sbs_data[WEG_MANUFACTUWEW_DATA].max_vawue) {
		vaw->intvaw = 0;
		wetuwn 0;
	}

	/* Mask the uppew nibbwe of 2nd byte and
	 * wowew byte of wesponse then
	 * shift the wesuwt by 8 to get status*/
	wet &= 0x0F00;
	wet >>= 8;
	if (psp == POWEW_SUPPWY_PWOP_PWESENT) {
		if (wet == 0x0F)
			/* battewy wemoved */
			vaw->intvaw = 0;
		ewse
			vaw->intvaw = 1;
	} ewse if (psp == POWEW_SUPPWY_PWOP_HEAWTH) {
		if (wet == 0x09)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		ewse if (wet == 0x0B)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse if (wet == 0x0C)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse if (sbs_bat_needs_cawibwation(cwient))
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_CAWIBWATION_WEQUIWED;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
	}

	wetuwn 0;
}

static int sbs_get_battewy_pwesence_and_heawth(
	stwuct i2c_cwient *cwient, enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	int wet;

	if (chip->fwags & SBS_FWAGS_TI_BQ20ZX5)
		wetuwn sbs_get_ti_battewy_pwesence_and_heawth(cwient, psp, vaw);

	/* Dummy command; if it succeeds, battewy is pwesent. */
	wet = sbs_wead_wowd_data(cwient, sbs_data[WEG_STATUS].addw);

	if (wet < 0) { /* battewy not pwesent*/
		if (psp == POWEW_SUPPWY_PWOP_PWESENT) {
			vaw->intvaw = 0;
			wetuwn 0;
		}
		wetuwn wet;
	}

	if (psp == POWEW_SUPPWY_PWOP_PWESENT)
		vaw->intvaw = 1; /* battewy pwesent */
	ewse { /* POWEW_SUPPWY_PWOP_HEAWTH */
		if (sbs_bat_needs_cawibwation(cwient)) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_CAWIBWATION_WEQUIWED;
		} ewse {
			/* SBS spec doesn't have a genewaw heawth command. */
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
		}
	}

	wetuwn 0;
}

static int sbs_get_battewy_pwopewty(stwuct i2c_cwient *cwient,
	int weg_offset, enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	s32 wet;

	wet = sbs_wead_wowd_data(cwient, sbs_data[weg_offset].addw);
	if (wet < 0)
		wetuwn wet;

	/* wetuwned vawues awe 16 bit */
	if (sbs_data[weg_offset].min_vawue < 0)
		wet = (s16)wet;

	if (wet >= sbs_data[weg_offset].min_vawue &&
	    wet <= sbs_data[weg_offset].max_vawue) {
		vaw->intvaw = wet;
		if (psp == POWEW_SUPPWY_PWOP_CAPACITY_WEVEW) {
			if (!(wet & BATTEWY_INITIAWIZED))
				vaw->intvaw =
					POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
			ewse if (wet & BATTEWY_FUWW_CHAWGED)
				vaw->intvaw =
					POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
			ewse if (wet & BATTEWY_FUWW_DISCHAWGED)
				vaw->intvaw =
					POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
			ewse
				vaw->intvaw =
					POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
			wetuwn 0;
		} ewse if (psp != POWEW_SUPPWY_PWOP_STATUS) {
			wetuwn 0;
		}

		if (wet & BATTEWY_FUWW_CHAWGED)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse if (wet & BATTEWY_DISCHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;

		sbs_status_cowwect(cwient, &vaw->intvaw);

		if (chip->poww_time == 0)
			chip->wast_state = vaw->intvaw;
		ewse if (chip->wast_state != vaw->intvaw) {
			cancew_dewayed_wowk_sync(&chip->wowk);
			powew_suppwy_changed(chip->powew_suppwy);
			chip->poww_time = 0;
		}
	} ewse {
		if (psp == POWEW_SUPPWY_PWOP_STATUS)
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		ewse if (psp == POWEW_SUPPWY_PWOP_CAPACITY)
			/* sbs spec says that this can be >100 %
			 * even if max vawue is 100 %
			 */
			vaw->intvaw = min(wet, 100);
		ewse
			vaw->intvaw = 0;
	}

	wetuwn 0;
}

static int sbs_get_pwopewty_index(stwuct i2c_cwient *cwient,
	enum powew_suppwy_pwopewty psp)
{
	int count;

	fow (count = 0; count < AWWAY_SIZE(sbs_data); count++)
		if (psp == sbs_data[count].psp)
			wetuwn count;

	dev_wawn(&cwient->dev,
		"%s: Invawid Pwopewty - %d\n", __func__, psp);

	wetuwn -EINVAW;
}

static const chaw *sbs_get_constant_stwing(stwuct sbs_info *chip,
			enum powew_suppwy_pwopewty psp)
{
	int wet;
	chaw *buf;
	u8 addw;

	buf = sbs_get_stwing_buf(chip, psp);
	if (IS_EWW(buf))
		wetuwn buf;

	if (!buf[0]) {
		wet = sbs_get_pwopewty_index(chip->cwient, psp);
		if (wet < 0)
			wetuwn EWW_PTW(wet);

		addw = sbs_data[wet].addw;

		wet = sbs_wead_stwing_data(chip->cwient, addw, buf);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	}

	wetuwn buf;
}

static void  sbs_unit_adjustment(stwuct i2c_cwient *cwient,
	enum powew_suppwy_pwopewty psp, union powew_suppwy_pwopvaw *vaw)
{
#define BASE_UNIT_CONVEWSION		1000
#define BATTEWY_MODE_CAP_MUWT_WATT	(10 * BASE_UNIT_CONVEWSION)
#define TIME_UNIT_CONVEWSION		60
#define TEMP_KEWVIN_TO_CEWSIUS		2731
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		/* sbs pwovides enewgy in units of 10mWh.
		 * Convewt to µWh
		 */
		vaw->intvaw *= BATTEWY_MODE_CAP_MUWT_WATT;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw *= BASE_UNIT_CONVEWSION;
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		/* sbs pwovides battewy tempewatuwe in 0.1K
		 * so convewt it to 0.1°C
		 */
		vaw->intvaw -= TEMP_KEWVIN_TO_CEWSIUS;
		bweak;

	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
		/* sbs pwovides time to empty and time to fuww in minutes.
		 * Convewt to seconds
		 */
		vaw->intvaw *= TIME_UNIT_CONVEWSION;
		bweak;

	defauwt:
		dev_dbg(&cwient->dev,
			"%s: no need fow unit convewsion %d\n", __func__, psp);
	}
}

static enum sbs_capacity_mode sbs_set_capacity_mode(stwuct i2c_cwient *cwient,
	enum sbs_capacity_mode mode)
{
	int wet, owiginaw_vaw;

	owiginaw_vaw = sbs_wead_wowd_data(cwient, BATTEWY_MODE_OFFSET);
	if (owiginaw_vaw < 0)
		wetuwn owiginaw_vaw;

	if ((owiginaw_vaw & BATTEWY_MODE_CAPACITY_MASK) == mode)
		wetuwn mode;

	if (mode == CAPACITY_MODE_AMPS)
		wet = owiginaw_vaw & ~BATTEWY_MODE_CAPACITY_MASK;
	ewse
		wet = owiginaw_vaw | BATTEWY_MODE_CAPACITY_MASK;

	wet = sbs_wwite_wowd_data(cwient, BATTEWY_MODE_OFFSET, wet);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(1000, 2000);

	wetuwn owiginaw_vaw & BATTEWY_MODE_CAPACITY_MASK;
}

static int sbs_get_battewy_capacity(stwuct i2c_cwient *cwient,
	int weg_offset, enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	s32 wet;
	enum sbs_capacity_mode mode = CAPACITY_MODE_WATTS;

	if (powew_suppwy_is_amp_pwopewty(psp))
		mode = CAPACITY_MODE_AMPS;

	mode = sbs_set_capacity_mode(cwient, mode);
	if ((int)mode < 0)
		wetuwn mode;

	wet = sbs_wead_wowd_data(cwient, sbs_data[weg_offset].addw);
	if (wet < 0)
		wetuwn wet;

	vaw->intvaw = wet;

	wet = sbs_set_capacity_mode(cwient, mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static chaw sbs_sewiaw[5];
static int sbs_get_battewy_sewiaw_numbew(stwuct i2c_cwient *cwient,
	union powew_suppwy_pwopvaw *vaw)
{
	int wet;

	wet = sbs_wead_wowd_data(cwient, sbs_data[WEG_SEWIAW_NUMBEW].addw);
	if (wet < 0)
		wetuwn wet;

	spwintf(sbs_sewiaw, "%04x", wet);
	vaw->stwvaw = sbs_sewiaw;

	wetuwn 0;
}

static int sbs_get_chemistwy(stwuct sbs_info *chip,
		union powew_suppwy_pwopvaw *vaw)
{
	const chaw *chemistwy;

	if (chip->technowogy != -1) {
		vaw->intvaw = chip->technowogy;
		wetuwn 0;
	}

	chemistwy = sbs_get_constant_stwing(chip, POWEW_SUPPWY_PWOP_TECHNOWOGY);

	if (IS_EWW(chemistwy))
		wetuwn PTW_EWW(chemistwy);

	if (!stwncasecmp(chemistwy, "WION", 4))
		chip->technowogy = POWEW_SUPPWY_TECHNOWOGY_WION;
	ewse if (!stwncasecmp(chemistwy, "WiP", 3))
		chip->technowogy = POWEW_SUPPWY_TECHNOWOGY_WIPO;
	ewse if (!stwncasecmp(chemistwy, "NiCd", 4))
		chip->technowogy = POWEW_SUPPWY_TECHNOWOGY_NiCd;
	ewse if (!stwncasecmp(chemistwy, "NiMH", 4))
		chip->technowogy = POWEW_SUPPWY_TECHNOWOGY_NiMH;
	ewse
		chip->technowogy = POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;

	if (chip->technowogy == POWEW_SUPPWY_TECHNOWOGY_UNKNOWN)
		dev_wawn(&chip->cwient->dev, "Unknown chemistwy: %s\n", chemistwy);

	vaw->intvaw = chip->technowogy;

	wetuwn 0;
}

static int sbs_get_battewy_manufactuwe_date(stwuct i2c_cwient *cwient,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u16 day, month, yeaw;

	wet = sbs_wead_wowd_data(cwient, WEG_ADDW_MANUFACTUWE_DATE);
	if (wet < 0)
		wetuwn wet;

	day   = wet   & GENMASK(4,  0);
	month = (wet  & GENMASK(8,  5)) >> 5;
	yeaw  = ((wet & GENMASK(15, 9)) >> 9) + 1980;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW:
		vaw->intvaw = yeaw;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH:
		vaw->intvaw = month;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY:
		vaw->intvaw = day;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sbs_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	int wet = 0;
	stwuct sbs_info *chip = powew_suppwy_get_dwvdata(psy);
	stwuct i2c_cwient *cwient = chip->cwient;
	const chaw *stw;

	if (chip->gpio_detect) {
		wet = gpiod_get_vawue_cansweep(chip->gpio_detect);
		if (wet < 0)
			wetuwn wet;
		if (psp == POWEW_SUPPWY_PWOP_PWESENT) {
			vaw->intvaw = wet;
			sbs_update_pwesence(chip, wet);
			wetuwn 0;
		}
		if (wet == 0)
			wetuwn -ENODATA;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = sbs_get_battewy_pwesence_and_heawth(cwient, psp, vaw);

		/* this can onwy be twue if no gpio is used */
		if (psp == POWEW_SUPPWY_PWOP_PWESENT)
			wetuwn 0;
		bweak;

	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		wet = sbs_get_chemistwy(chip, vaw);
		if (wet < 0)
			bweak;

		goto done; /* don't twiggew powew_suppwy_changed()! */

	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wet = sbs_get_pwopewty_index(cwient, psp);
		if (wet < 0)
			bweak;

		/* sbs_get_battewy_capacity() wiww change the battewy mode
		 * tempowawiwy to wead the wequested attwibute. Ensuwe we stay
		 * in the desiwed mode fow the duwation of the attwibute wead.
		 */
		mutex_wock(&chip->mode_wock);
		wet = sbs_get_battewy_capacity(cwient, wet, psp, vaw);
		mutex_unwock(&chip->mode_wock);
		bweak;

	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		wet = sbs_get_battewy_sewiaw_numbew(cwient, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_TEMP:
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_CAPACITY:
	case POWEW_SUPPWY_PWOP_CAPACITY_EWWOW_MAWGIN:
		wet = sbs_get_pwopewty_index(cwient, psp);
		if (wet < 0)
			bweak;

		wet = sbs_get_battewy_pwopewty(cwient, wet, psp, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		stw = sbs_get_constant_stwing(chip, psp);
		if (IS_EWW(stw))
			wet = PTW_EWW(stw);
		ewse
			vaw->stwvaw = stw;
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW:
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH:
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY:
		wet = sbs_get_battewy_manufactuwe_date(cwient, psp, vaw);
		bweak;

	defauwt:
		dev_eww(&cwient->dev,
			"%s: INVAWID pwopewty\n", __func__);
		wetuwn -EINVAW;
	}

	if (!chip->gpio_detect && chip->is_pwesent != (wet >= 0)) {
		boow owd_pwesent = chip->is_pwesent;
		union powew_suppwy_pwopvaw vaw;
		int eww = sbs_get_battewy_pwesence_and_heawth(
				cwient, POWEW_SUPPWY_PWOP_PWESENT, &vaw);

		sbs_update_pwesence(chip, !eww && vaw.intvaw);

		if (owd_pwesent != chip->is_pwesent)
			powew_suppwy_changed(chip->powew_suppwy);
	}

done:
	if (!wet) {
		/* Convewt units to match wequiwements fow powew suppwy cwass */
		sbs_unit_adjustment(cwient, psp, vaw);
		dev_dbg(&cwient->dev,
			"%s: pwopewty = %d, vawue = %x\n", __func__,
			psp, vaw->intvaw);
	} ewse if (!chip->is_pwesent)  {
		/* battewy not pwesent, so wetuwn NODATA fow pwopewties */
		wet = -ENODATA;
	}
	wetuwn wet;
}

static void sbs_suppwy_changed(stwuct sbs_info *chip)
{
	stwuct powew_suppwy *battewy = chip->powew_suppwy;
	int wet;

	wet = gpiod_get_vawue_cansweep(chip->gpio_detect);
	if (wet < 0)
		wetuwn;
	sbs_update_pwesence(chip, wet);
	powew_suppwy_changed(battewy);
}

static iwqwetuwn_t sbs_iwq(int iwq, void *devid)
{
	sbs_suppwy_changed(devid);
	wetuwn IWQ_HANDWED;
}

static void sbs_awewt(stwuct i2c_cwient *cwient, enum i2c_awewt_pwotocow pwot,
	unsigned int data)
{
	sbs_suppwy_changed(i2c_get_cwientdata(cwient));
}

static void sbs_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct sbs_info *chip = powew_suppwy_get_dwvdata(psy);

	/* cancew outstanding wowk */
	cancew_dewayed_wowk_sync(&chip->wowk);

	scheduwe_dewayed_wowk(&chip->wowk, HZ);
	chip->poww_time = chip->poww_wetwy_count;
}

static void sbs_dewayed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sbs_info *chip;
	s32 wet;

	chip = containew_of(wowk, stwuct sbs_info, wowk.wowk);

	wet = sbs_wead_wowd_data(chip->cwient, sbs_data[WEG_STATUS].addw);
	/* if the wead faiwed, give up on this wowk */
	if (wet < 0) {
		chip->poww_time = 0;
		wetuwn;
	}

	if (wet & BATTEWY_FUWW_CHAWGED)
		wet = POWEW_SUPPWY_STATUS_FUWW;
	ewse if (wet & BATTEWY_DISCHAWGING)
		wet = POWEW_SUPPWY_STATUS_DISCHAWGING;
	ewse
		wet = POWEW_SUPPWY_STATUS_CHAWGING;

	sbs_status_cowwect(chip->cwient, &wet);

	if (chip->wast_state != wet) {
		chip->poww_time = 0;
		powew_suppwy_changed(chip->powew_suppwy);
		wetuwn;
	}
	if (chip->poww_time > 0) {
		scheduwe_dewayed_wowk(&chip->wowk, HZ);
		chip->poww_time--;
		wetuwn;
	}
}

static const stwuct powew_suppwy_desc sbs_defauwt_desc = {
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = sbs_pwopewties,
	.num_pwopewties = AWWAY_SIZE(sbs_pwopewties),
	.get_pwopewty = sbs_get_pwopewty,
	.extewnaw_powew_changed = sbs_extewnaw_powew_changed,
};

static int sbs_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sbs_info *chip;
	stwuct powew_suppwy_desc *sbs_desc;
	stwuct sbs_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct powew_suppwy_config psy_cfg = {};
	int wc;
	int iwq;

	sbs_desc = devm_kmemdup(&cwient->dev, &sbs_defauwt_desc,
			sizeof(*sbs_desc), GFP_KEWNEW);
	if (!sbs_desc)
		wetuwn -ENOMEM;

	sbs_desc->name = devm_kaspwintf(&cwient->dev, GFP_KEWNEW, "sbs-%s",
			dev_name(&cwient->dev));
	if (!sbs_desc->name)
		wetuwn -ENOMEM;

	chip = devm_kzawwoc(&cwient->dev, sizeof(stwuct sbs_info), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->fwags = (uintptw_t)i2c_get_match_data(cwient);
	chip->cwient = cwient;
	psy_cfg.of_node = cwient->dev.of_node;
	psy_cfg.dwv_data = chip;
	chip->wast_state = POWEW_SUPPWY_STATUS_UNKNOWN;
	sbs_invawidate_cached_pwops(chip);
	mutex_init(&chip->mode_wock);

	/* use pdata if avaiwabwe, faww back to DT pwopewties,
	 * ow hawdcoded defauwts if not
	 */
	wc = device_pwopewty_wead_u32(&cwient->dev, "sbs,i2c-wetwy-count",
				      &chip->i2c_wetwy_count);
	if (wc)
		chip->i2c_wetwy_count = 0;

	wc = device_pwopewty_wead_u32(&cwient->dev, "sbs,poww-wetwy-count",
				      &chip->poww_wetwy_count);
	if (wc)
		chip->poww_wetwy_count = 0;

	if (pdata) {
		chip->poww_wetwy_count = pdata->poww_wetwy_count;
		chip->i2c_wetwy_count  = pdata->i2c_wetwy_count;
	}
	chip->i2c_wetwy_count = chip->i2c_wetwy_count + 1;

	chip->chawgew_bwoadcasts = !device_pwopewty_wead_boow(&cwient->dev,
					"sbs,disabwe-chawgew-bwoadcasts");

	chip->gpio_detect = devm_gpiod_get_optionaw(&cwient->dev,
			"sbs,battewy-detect", GPIOD_IN);
	if (IS_EWW(chip->gpio_detect))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->gpio_detect),
				     "Faiwed to get gpio\n");

	i2c_set_cwientdata(cwient, chip);

	if (!chip->gpio_detect)
		goto skip_gpio;

	iwq = gpiod_to_iwq(chip->gpio_detect);
	if (iwq <= 0) {
		dev_wawn(&cwient->dev, "Faiwed to get gpio as iwq: %d\n", iwq);
		goto skip_gpio;
	}

	wc = devm_wequest_thweaded_iwq(&cwient->dev, iwq, NUWW, sbs_iwq,
		IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
		dev_name(&cwient->dev), chip);
	if (wc) {
		dev_wawn(&cwient->dev, "Faiwed to wequest iwq: %d\n", wc);
		goto skip_gpio;
	}

skip_gpio:
	/*
	 * Befowe we wegistew, we might need to make suwe we can actuawwy tawk
	 * to the battewy.
	 */
	if (!(fowce_woad || chip->gpio_detect)) {
		union powew_suppwy_pwopvaw vaw;

		wc = sbs_get_battewy_pwesence_and_heawth(
				cwient, POWEW_SUPPWY_PWOP_PWESENT, &vaw);
		if (wc < 0 || !vaw.intvaw)
			wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
					     "Faiwed to get pwesent status\n");
	}

	wc = devm_dewayed_wowk_autocancew(&cwient->dev, &chip->wowk,
					  sbs_dewayed_wowk);
	if (wc)
		wetuwn wc;

	chip->powew_suppwy = devm_powew_suppwy_wegistew(&cwient->dev, sbs_desc,
						   &psy_cfg);
	if (IS_EWW(chip->powew_suppwy))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->powew_suppwy),
				     "Faiwed to wegistew powew suppwy\n");

	dev_info(&cwient->dev,
		"%s: battewy gas gauge device wegistewed\n", cwient->name);

	wetuwn 0;
}

#if defined CONFIG_PM_SWEEP

static int sbs_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct sbs_info *chip = i2c_get_cwientdata(cwient);
	int wet;

	if (chip->poww_time > 0)
		cancew_dewayed_wowk_sync(&chip->wowk);

	if (chip->fwags & SBS_FWAGS_TI_BQ20ZX5) {
		/* Wwite to manufactuwew access with sweep command. */
		wet = sbs_wwite_wowd_data(cwient,
					  sbs_data[WEG_MANUFACTUWEW_DATA].addw,
					  MANUFACTUWEW_ACCESS_SWEEP);
		if (chip->is_pwesent && wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(sbs_pm_ops, sbs_suspend, NUWW);
#define SBS_PM_OPS (&sbs_pm_ops)

#ewse
#define SBS_PM_OPS NUWW
#endif

static const stwuct i2c_device_id sbs_id[] = {
	{ "bq20z65", SBS_FWAGS_TI_BQ20ZX5 },
	{ "bq20z75", SBS_FWAGS_TI_BQ20ZX5 },
	{ "sbs-battewy", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, sbs_id);

static const stwuct of_device_id sbs_dt_ids[] = {
	{ .compatibwe = "sbs,sbs-battewy" },
	{
		.compatibwe = "ti,bq20z65",
		.data = (void *)SBS_FWAGS_TI_BQ20ZX5,
	},
	{
		.compatibwe = "ti,bq20z75",
		.data = (void *)SBS_FWAGS_TI_BQ20ZX5,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sbs_dt_ids);

static stwuct i2c_dwivew sbs_battewy_dwivew = {
	.pwobe		= sbs_pwobe,
	.awewt		= sbs_awewt,
	.id_tabwe	= sbs_id,
	.dwivew = {
		.name	= "sbs-battewy",
		.of_match_tabwe = sbs_dt_ids,
		.pm	= SBS_PM_OPS,
	},
};
moduwe_i2c_dwivew(sbs_battewy_dwivew);

MODUWE_DESCWIPTION("SBS battewy monitow dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(fowce_woad, boow, 0444);
MODUWE_PAWM_DESC(fowce_woad,
		 "Attempt to woad the dwivew even if no battewy is connected");
