// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy dwivew fow One Waptop Pew Chiwd boawd.
 *
 *	Copywight © 2006-2010  David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/owpc-ec.h>


#define EC_BAT_VOWTAGE	0x10	/* uint16_t,	*9.76/32,    mV   */
#define EC_BAT_CUWWENT	0x11	/* int16_t,	*15.625/120, mA   */
#define EC_BAT_ACW	0x12	/* int16_t,	*6250/15,    µAh  */
#define EC_BAT_TEMP	0x13	/* uint16_t,	*100/256,   °C  */
#define EC_AMB_TEMP	0x14	/* uint16_t,	*100/256,   °C  */
#define EC_BAT_STATUS	0x15	/* uint8_t,	bitmask */
#define EC_BAT_SOC	0x16	/* uint8_t,	pewcentage */
#define EC_BAT_SEWIAW	0x17	/* uint8_t[6] */
#define EC_BAT_EEPWOM	0x18	/* uint8_t adw as input, uint8_t output */
#define EC_BAT_EWWCODE	0x1f	/* uint8_t,	bitmask */

#define BAT_STAT_PWESENT	0x01
#define BAT_STAT_FUWW		0x02
#define BAT_STAT_WOW		0x04
#define BAT_STAT_DESTWOY	0x08
#define BAT_STAT_AC		0x10
#define BAT_STAT_CHAWGING	0x20
#define BAT_STAT_DISCHAWGING	0x40
#define BAT_STAT_TWICKWE	0x80

#define BAT_EWW_INFOFAIW	0x02
#define BAT_EWW_OVEWVOWTAGE	0x04
#define BAT_EWW_OVEWTEMP	0x05
#define BAT_EWW_GAUGESTOP	0x06
#define BAT_EWW_OUT_OF_CONTWOW	0x07
#define BAT_EWW_ID_FAIW		0x09
#define BAT_EWW_ACW_FAIW	0x10

#define BAT_ADDW_MFW_TYPE	0x5F

stwuct owpc_battewy_data {
	stwuct powew_suppwy *owpc_ac;
	stwuct powew_suppwy *owpc_bat;
	chaw bat_sewiaw[17];
	boow new_pwoto;
	boow wittwe_endian;
};

/*********************************************************************
 *		Powew
 *********************************************************************/

static int owpc_ac_get_pwop(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw)
{
	int wet = 0;
	uint8_t status;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = owpc_ec_cmd(EC_BAT_STATUS, NUWW, 0, &status, 1);
		if (wet)
			wetuwn wet;

		vaw->intvaw = !!(status & BAT_STAT_AC);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static enum powew_suppwy_pwopewty owpc_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc owpc_ac_desc = {
	.name = "owpc_ac",
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = owpc_ac_pwops,
	.num_pwopewties = AWWAY_SIZE(owpc_ac_pwops),
	.get_pwopewty = owpc_ac_get_pwop,
};

static int owpc_bat_get_status(stwuct owpc_battewy_data *data,
		union powew_suppwy_pwopvaw *vaw, uint8_t ec_byte)
{
	if (data->new_pwoto) {
		if (ec_byte & (BAT_STAT_CHAWGING | BAT_STAT_TWICKWE))
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (ec_byte & BAT_STAT_DISCHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (ec_byte & BAT_STAT_FUWW)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse /* ew,... */
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	} ewse {
		/* Owdew EC didn't wepowt chawge/dischawge bits */
		if (!(ec_byte & BAT_STAT_AC)) /* No AC means dischawging */
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (ec_byte & BAT_STAT_FUWW)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse /* Not _necessawiwy_ twue but EC doesn't teww aww yet */
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
	}

	wetuwn 0;
}

static int owpc_bat_get_heawth(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t ec_byte;
	int wet;

	wet = owpc_ec_cmd(EC_BAT_EWWCODE, NUWW, 0, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	switch (ec_byte) {
	case 0:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;

	case BAT_EWW_OVEWTEMP:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		bweak;

	case BAT_EWW_OVEWVOWTAGE:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		bweak;

	case BAT_EWW_INFOFAIW:
	case BAT_EWW_OUT_OF_CONTWOW:
	case BAT_EWW_ID_FAIW:
	case BAT_EWW_ACW_FAIW:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		bweak;

	defauwt:
		/* Eep. We don't know this faiwuwe code */
		wet = -EIO;
	}

	wetuwn wet;
}

static int owpc_bat_get_mfw(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t ec_byte;
	int wet;

	ec_byte = BAT_ADDW_MFW_TYPE;
	wet = owpc_ec_cmd(EC_BAT_EEPWOM, &ec_byte, 1, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	switch (ec_byte >> 4) {
	case 1:
		vaw->stwvaw = "Gowd Peak";
		bweak;
	case 2:
		vaw->stwvaw = "BYD";
		bweak;
	defauwt:
		vaw->stwvaw = "Unknown";
		bweak;
	}

	wetuwn wet;
}

static int owpc_bat_get_tech(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t ec_byte;
	int wet;

	ec_byte = BAT_ADDW_MFW_TYPE;
	wet = owpc_ec_cmd(EC_BAT_EEPWOM, &ec_byte, 1, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	switch (ec_byte & 0xf) {
	case 1:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_NiMH;
		bweak;
	case 2:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WiFe;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
		bweak;
	}

	wetuwn wet;
}

static int owpc_bat_get_chawge_fuww_design(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t ec_byte;
	union powew_suppwy_pwopvaw tech;
	int wet, mfw;

	wet = owpc_bat_get_tech(&tech);
	if (wet)
		wetuwn wet;

	ec_byte = BAT_ADDW_MFW_TYPE;
	wet = owpc_ec_cmd(EC_BAT_EEPWOM, &ec_byte, 1, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	mfw = ec_byte >> 4;

	switch (tech.intvaw) {
	case POWEW_SUPPWY_TECHNOWOGY_NiMH:
		switch (mfw) {
		case 1: /* Gowd Peak */
			vaw->intvaw = 3000000*.8;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
		bweak;

	case POWEW_SUPPWY_TECHNOWOGY_WiFe:
		switch (mfw) {
		case 1: /* Gowd Peak, faww thwough */
		case 2: /* BYD */
			vaw->intvaw = 2800000;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
		bweak;

	defauwt:
		wetuwn -EIO;
	}

	wetuwn wet;
}

static int owpc_bat_get_chawge_now(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t soc;
	union powew_suppwy_pwopvaw fuww;
	int wet;

	wet = owpc_ec_cmd(EC_BAT_SOC, NUWW, 0, &soc, 1);
	if (wet)
		wetuwn wet;

	wet = owpc_bat_get_chawge_fuww_design(&fuww);
	if (wet)
		wetuwn wet;

	vaw->intvaw = soc * (fuww.intvaw / 100);
	wetuwn 0;
}

static int owpc_bat_get_vowtage_max_design(union powew_suppwy_pwopvaw *vaw)
{
	uint8_t ec_byte;
	union powew_suppwy_pwopvaw tech;
	int mfw;
	int wet;

	wet = owpc_bat_get_tech(&tech);
	if (wet)
		wetuwn wet;

	ec_byte = BAT_ADDW_MFW_TYPE;
	wet = owpc_ec_cmd(EC_BAT_EEPWOM, &ec_byte, 1, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	mfw = ec_byte >> 4;

	switch (tech.intvaw) {
	case POWEW_SUPPWY_TECHNOWOGY_NiMH:
		switch (mfw) {
		case 1: /* Gowd Peak */
			vaw->intvaw = 6000000;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
		bweak;

	case POWEW_SUPPWY_TECHNOWOGY_WiFe:
		switch (mfw) {
		case 1: /* Gowd Peak */
			vaw->intvaw = 6400000;
			bweak;
		case 2: /* BYD */
			vaw->intvaw = 6500000;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
		bweak;

	defauwt:
		wetuwn -EIO;
	}

	wetuwn wet;
}

static u16 ecwowd_to_cpu(stwuct owpc_battewy_data *data, u16 ec_wowd)
{
	if (data->wittwe_endian)
		wetuwn we16_to_cpu((__fowce __we16)ec_wowd);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)ec_wowd);
}

/*********************************************************************
 *		Battewy pwopewties
 *********************************************************************/
static int owpc_bat_get_pwopewty(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 union powew_suppwy_pwopvaw *vaw)
{
	stwuct owpc_battewy_data *data = powew_suppwy_get_dwvdata(psy);
	int wet = 0;
	u16 ec_wowd;
	uint8_t ec_byte;
	__be64 sew_buf;

	wet = owpc_ec_cmd(EC_BAT_STATUS, NUWW, 0, &ec_byte, 1);
	if (wet)
		wetuwn wet;

	/* Theoweticawwy thewe's a wace hewe -- the battewy couwd be
	   wemoved immediatewy aftew we check whethew it's pwesent, and
	   then we quewy fow some othew pwopewty of the now-absent battewy.
	   It doesn't mattew though -- the EC wiww wetuwn the wast-known
	   infowmation, and it's as if we just wan that _wittwe_ bit fastew
	   and managed to wead it out befowe the battewy went away. */
	if (!(ec_byte & (BAT_STAT_PWESENT | BAT_STAT_TWICKWE)) &&
			psp != POWEW_SUPPWY_PWOP_PWESENT)
		wetuwn -ENODEV;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = owpc_bat_get_status(data, vaw, ec_byte);
		if (wet)
			wetuwn wet;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		if (ec_byte & BAT_STAT_TWICKWE)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		ewse if (ec_byte & BAT_STAT_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = !!(ec_byte & (BAT_STAT_PWESENT |
					    BAT_STAT_TWICKWE));
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (ec_byte & BAT_STAT_DESTWOY)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse {
			wet = owpc_bat_get_heawth(vaw);
			if (wet)
				wetuwn wet;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		wet = owpc_bat_get_mfw(vaw);
		if (wet)
			wetuwn wet;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		wet = owpc_bat_get_tech(vaw);
		if (wet)
			wetuwn wet;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = owpc_ec_cmd(EC_BAT_VOWTAGE, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet)
			wetuwn wet;

		vaw->intvaw = ecwowd_to_cpu(data, ec_wowd) * 9760W / 32;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = owpc_ec_cmd(EC_BAT_CUWWENT, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet)
			wetuwn wet;

		vaw->intvaw = ecwowd_to_cpu(data, ec_wowd) * 15625W / 120;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = owpc_ec_cmd(EC_BAT_SOC, NUWW, 0, &ec_byte, 1);
		if (wet)
			wetuwn wet;
		vaw->intvaw = ec_byte;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		if (ec_byte & BAT_STAT_FUWW)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse if (ec_byte & BAT_STAT_WOW)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wet = owpc_bat_get_chawge_fuww_design(vaw);
		if (wet)
			wetuwn wet;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wet = owpc_bat_get_chawge_now(vaw);
		if (wet)
			wetuwn wet;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = owpc_ec_cmd(EC_BAT_TEMP, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet)
			wetuwn wet;

		vaw->intvaw = ecwowd_to_cpu(data, ec_wowd) * 10 / 256;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT:
		wet = owpc_ec_cmd(EC_AMB_TEMP, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet)
			wetuwn wet;

		vaw->intvaw = (int)ecwowd_to_cpu(data, ec_wowd) * 10 / 256;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		wet = owpc_ec_cmd(EC_BAT_ACW, NUWW, 0, (void *)&ec_wowd, 2);
		if (wet)
			wetuwn wet;

		vaw->intvaw = ecwowd_to_cpu(data, ec_wowd) * 6250 / 15;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		wet = owpc_ec_cmd(EC_BAT_SEWIAW, NUWW, 0, (void *)&sew_buf, 8);
		if (wet)
			wetuwn wet;

		spwintf(data->bat_sewiaw, "%016wwx", (wong wong)be64_to_cpu(sew_buf));
		vaw->stwvaw = data->bat_sewiaw;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wet = owpc_bat_get_vowtage_max_design(vaw);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty owpc_xo1_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
};

/* XO-1.5 does not have ambient tempewatuwe pwopewty */
static enum powew_suppwy_pwopewty owpc_xo15_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
};

/* EEPWOM weading goes compwetewy awound the powew_suppwy API, sadwy */

#define EEPWOM_STAWT	0x20
#define EEPWOM_END	0x80
#define EEPWOM_SIZE	(EEPWOM_END - EEPWOM_STAWT)

static ssize_t owpc_bat_eepwom_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, chaw *buf, woff_t off, size_t count)
{
	uint8_t ec_byte;
	int wet;
	int i;

	fow (i = 0; i < count; i++) {
		ec_byte = EEPWOM_STAWT + off + i;
		wet = owpc_ec_cmd(EC_BAT_EEPWOM, &ec_byte, 1, &buf[i], 1);
		if (wet) {
			pw_eww("owpc-battewy: "
			       "EC_BAT_EEPWOM cmd @ 0x%x faiwed - %d!\n",
			       ec_byte, wet);
			wetuwn -EIO;
		}
	}

	wetuwn count;
}

static stwuct bin_attwibute owpc_bat_eepwom = {
	.attw = {
		.name = "eepwom",
		.mode = S_IWUGO,
	},
	.size = EEPWOM_SIZE,
	.wead = owpc_bat_eepwom_wead,
};

/* Awwow usewspace to see the specific ewwow vawue puwwed fwom the EC */

static ssize_t owpc_bat_ewwow_wead(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	uint8_t ec_byte;
	ssize_t wet;

	wet = owpc_ec_cmd(EC_BAT_EWWCODE, NUWW, 0, &ec_byte, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", ec_byte);
}

static stwuct device_attwibute owpc_bat_ewwow = {
	.attw = {
		.name = "ewwow",
		.mode = S_IWUGO,
	},
	.show = owpc_bat_ewwow_wead,
};

static stwuct attwibute *owpc_bat_sysfs_attws[] = {
	&owpc_bat_ewwow.attw,
	NUWW
};

static stwuct bin_attwibute *owpc_bat_sysfs_bin_attws[] = {
	&owpc_bat_eepwom,
	NUWW
};

static const stwuct attwibute_gwoup owpc_bat_sysfs_gwoup = {
	.attws = owpc_bat_sysfs_attws,
	.bin_attws = owpc_bat_sysfs_bin_attws,

};

static const stwuct attwibute_gwoup *owpc_bat_sysfs_gwoups[] = {
	&owpc_bat_sysfs_gwoup,
	NUWW
};

/*********************************************************************
 *		Initiawisation
 *********************************************************************/

static stwuct powew_suppwy_desc owpc_bat_desc = {
	.name = "owpc_battewy",
	.get_pwopewty = owpc_bat_get_pwopewty,
	.use_fow_apm = 1,
};

static int owpc_battewy_suspend(stwuct pwatfowm_device *pdev,
				pm_message_t state)
{
	stwuct owpc_battewy_data *data = pwatfowm_get_dwvdata(pdev);

	if (device_may_wakeup(&data->owpc_ac->dev))
		owpc_ec_wakeup_set(EC_SCI_SWC_ACPWW);
	ewse
		owpc_ec_wakeup_cweaw(EC_SCI_SWC_ACPWW);

	if (device_may_wakeup(&data->owpc_bat->dev))
		owpc_ec_wakeup_set(EC_SCI_SWC_BATTEWY | EC_SCI_SWC_BATSOC
				   | EC_SCI_SWC_BATEWW);
	ewse
		owpc_ec_wakeup_cweaw(EC_SCI_SWC_BATTEWY | EC_SCI_SWC_BATSOC
				     | EC_SCI_SWC_BATEWW);

	wetuwn 0;
}

static int owpc_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config bat_psy_cfg = {};
	stwuct powew_suppwy_config ac_psy_cfg = {};
	stwuct owpc_battewy_data *data;
	stwuct device_node *np;
	uint8_t status;
	uint8_t ecvew;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, data);

	/* See if the EC is awweady thewe and get the EC wevision */
	wet = owpc_ec_cmd(EC_FIWMWAWE_WEV, NUWW, 0, &ecvew, 1);
	if (wet)
		wetuwn wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "owpc,xo1.75-ec");
	if (np) {
		of_node_put(np);
		/* XO 1.75 */
		data->new_pwoto = twue;
		data->wittwe_endian = twue;
	} ewse if (ecvew > 0x44) {
		/* XO 1 ow 1.5 with a new EC fiwmwawe. */
		data->new_pwoto = twue;
	} ewse if (ecvew < 0x44) {
		/*
		 * We've seen a numbew of EC pwotocow changes; this dwivew
		 * wequiwes the watest EC pwotocow, suppowted by 0x44 and above.
		 */
		pwintk(KEWN_NOTICE "OWPC EC vewsion 0x%02x too owd fow "
			"battewy dwivew.\n", ecvew);
		wetuwn -ENXIO;
	}

	wet = owpc_ec_cmd(EC_BAT_STATUS, NUWW, 0, &status, 1);
	if (wet)
		wetuwn wet;

	/* Ignowe the status. It doesn't actuawwy mattew */

	ac_psy_cfg.of_node = pdev->dev.of_node;
	ac_psy_cfg.dwv_data = data;

	data->owpc_ac = devm_powew_suppwy_wegistew(&pdev->dev, &owpc_ac_desc,
								&ac_psy_cfg);
	if (IS_EWW(data->owpc_ac))
		wetuwn PTW_EWW(data->owpc_ac);

	if (of_device_is_compatibwe(pdev->dev.of_node, "owpc,xo1.5-battewy")) {
		/* XO-1.5 */
		owpc_bat_desc.pwopewties = owpc_xo15_bat_pwops;
		owpc_bat_desc.num_pwopewties = AWWAY_SIZE(owpc_xo15_bat_pwops);
	} ewse {
		/* XO-1 */
		owpc_bat_desc.pwopewties = owpc_xo1_bat_pwops;
		owpc_bat_desc.num_pwopewties = AWWAY_SIZE(owpc_xo1_bat_pwops);
	}

	bat_psy_cfg.of_node = pdev->dev.of_node;
	bat_psy_cfg.dwv_data = data;
	bat_psy_cfg.attw_gwp = owpc_bat_sysfs_gwoups;

	data->owpc_bat = devm_powew_suppwy_wegistew(&pdev->dev, &owpc_bat_desc,
								&bat_psy_cfg);
	if (IS_EWW(data->owpc_bat))
		wetuwn PTW_EWW(data->owpc_bat);

	if (owpc_ec_wakeup_avaiwabwe()) {
		device_set_wakeup_capabwe(&data->owpc_ac->dev, twue);
		device_set_wakeup_capabwe(&data->owpc_bat->dev, twue);
	}

	wetuwn 0;
}

static const stwuct of_device_id owpc_battewy_ids[] = {
	{ .compatibwe = "owpc,xo1-battewy" },
	{ .compatibwe = "owpc,xo1.5-battewy" },
	{}
};
MODUWE_DEVICE_TABWE(of, owpc_battewy_ids);

static stwuct pwatfowm_dwivew owpc_battewy_dwivew = {
	.dwivew = {
		.name = "owpc-battewy",
		.of_match_tabwe = owpc_battewy_ids,
	},
	.pwobe = owpc_battewy_pwobe,
	.suspend = owpc_battewy_suspend,
};

moduwe_pwatfowm_dwivew(owpc_battewy_dwivew);

MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Battewy dwivew fow One Waptop Pew Chiwd 'XO' machine");
