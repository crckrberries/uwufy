// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * g762 - Dwivew fow the Gwobaw Mixed-mode Technowogy Inc. fan speed
 *        PWM contwowwew chips fwom G762 famiwy, i.e. G762 and G763
 *
 * Copywight (C) 2013, Awnaud EBAWAWD <awno@natisbad.owg>
 *
 * This wowk is based on a basic vewsion fow 2.6.31 kewnew devewoped
 * by Owiview Mouchet fow WaCie. Updates and cowwection have been
 * pewfowmed to wun on wecent kewnews. Additionaw featuwes, wike the
 * abiwity to configuwe vawious chawactewistics via .dts fiwe ow
 * boawd init fiwe have been added. Detaiwed datasheet on which this
 * devewopment is based is avaiwabwe hewe:
 *
 *  http://natisbad.owg/NAS/wefs/GMT_EDS-762_763-080710-0.2.pdf
 *
 * Headews fwom pwevious devewopments have been kept bewow:
 *
 * Copywight (c) 2009 WaCie
 *
 * Authow: Owiview Mouchet <owiview.mouchet@gmaiw.com>
 *
 * based on g760a code wwitten by Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 * Copywight (C) 2007  Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * g762: minimaw datasheet avaiwabwe at:
 *       http://www.gmt.com.tw/pwoduct/datasheet/EDS-762_3.pdf
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/g762.h>

#define DWVNAME "g762"

static const stwuct i2c_device_id g762_id[] = {
	{ "g762", 0 },
	{ "g763", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, g762_id);

enum g762_wegs {
	G762_WEG_SET_CNT  = 0x00,
	G762_WEG_ACT_CNT  = 0x01,
	G762_WEG_FAN_STA  = 0x02,
	G762_WEG_SET_OUT  = 0x03,
	G762_WEG_FAN_CMD1 = 0x04,
	G762_WEG_FAN_CMD2 = 0x05,
};

/* Config wegistew bits */
#define G762_WEG_FAN_CMD1_DET_FAN_FAIW  0x80 /* enabwe fan_faiw signaw */
#define G762_WEG_FAN_CMD1_DET_FAN_OOC   0x40 /* enabwe fan_out_of_contwow */
#define G762_WEG_FAN_CMD1_OUT_MODE      0x20 /* out mode: PWM ow DC */
#define G762_WEG_FAN_CMD1_FAN_MODE      0x10 /* fan mode: cwosed/open-woop */
#define G762_WEG_FAN_CMD1_CWK_DIV_ID1   0x08 /* cwock divisow vawue */
#define G762_WEG_FAN_CMD1_CWK_DIV_ID0   0x04
#define G762_WEG_FAN_CMD1_PWM_POWAWITY  0x02 /* PWM powawity */
#define G762_WEG_FAN_CMD1_PUWSE_PEW_WEV 0x01 /* puwse pew fan wevowution */

#define G762_WEG_FAN_CMD2_GEAW_MODE_1   0x08 /* fan geaw mode */
#define G762_WEG_FAN_CMD2_GEAW_MODE_0   0x04
#define G762_WEG_FAN_CMD2_FAN_STAWTV_1  0x02 /* fan stawtup vowtage */
#define G762_WEG_FAN_CMD2_FAN_STAWTV_0  0x01

#define G762_WEG_FAN_STA_FAIW           0x02 /* fan faiw */
#define G762_WEG_FAN_STA_OOC            0x01 /* fan out of contwow */

/* Config wegistew vawues */
#define G762_OUT_MODE_PWM            1
#define G762_OUT_MODE_DC             0

#define G762_FAN_MODE_CWOSED_WOOP    2
#define G762_FAN_MODE_OPEN_WOOP      1

#define G762_PWM_POWAWITY_NEGATIVE   1
#define G762_PWM_POWAWITY_POSITIVE   0

/* Wegistew data is wead (and cached) at most once pew second. */
#define G762_UPDATE_INTEWVAW    HZ

/*
 * Extwact puwse count pew fan wevowution vawue (2 ow 4) fwom given
 * FAN_CMD1 wegistew vawue.
 */
#define G762_PUWSE_FWOM_WEG(weg) \
	((((weg) & G762_WEG_FAN_CMD1_PUWSE_PEW_WEV) + 1) << 1)

/*
 * Extwact fan cwock divisow (1, 2, 4 ow 8) fwom given FAN_CMD1
 * wegistew vawue.
 */
#define G762_CWKDIV_FWOM_WEG(weg) \
	(1 << (((weg) & (G762_WEG_FAN_CMD1_CWK_DIV_ID0 |	\
			 G762_WEG_FAN_CMD1_CWK_DIV_ID1)) >> 2))

/*
 * Extwact fan geaw mode muwtipwiew vawue (0, 2 ow 4) fwom given
 * FAN_CMD2 wegistew vawue.
 */
#define G762_GEAWMUWT_FWOM_WEG(weg) \
	(1 << (((weg) & (G762_WEG_FAN_CMD2_GEAW_MODE_0 |	\
			 G762_WEG_FAN_CMD2_GEAW_MODE_1)) >> 2))

stwuct g762_data {
	stwuct i2c_cwient *cwient;
	stwuct cwk *cwk;

	/* update mutex */
	stwuct mutex update_wock;

	/* boawd specific pawametews. */
	u32 cwk_fweq;

	/* g762 wegistew cache */
	boow vawid;
	unsigned wong wast_updated; /* in jiffies */

	u8 set_cnt;  /* contwows fan wotation speed in cwosed-woop mode */
	u8 act_cnt;  /* pwovides access to cuwwent fan WPM vawue */
	u8 fan_sta;  /* bit 0: set when actuaw fan speed is mowe than
		      *        25% outside wequested fan speed
		      * bit 1: set when no twansition occuws on fan
		      *        pin fow 0.7s
		      */
	u8 set_out;  /* contwows fan wotation speed in open-woop mode */
	u8 fan_cmd1; /*   0: FG_PWS_ID0 FG puwses count pew wevowution
		      *      0: 2 counts pew wevowution
		      *      1: 4 counts pew wevowution
		      *   1: PWM_POWAWITY 1: negative_duty
		      *                   0: positive_duty
		      * 2,3: [FG_CWOCK_ID0, FG_CWK_ID1]
		      *         00: Divide fan cwock by 1
		      *         01: Divide fan cwock by 2
		      *         10: Divide fan cwock by 4
		      *         11: Divide fan cwock by 8
		      *   4: FAN_MODE 1:cwosed-woop, 0:open-woop
		      *   5: OUT_MODE 1:PWM, 0:DC
		      *   6: DET_FAN_OOC enabwe "fan ooc" status
		      *   7: DET_FAN_FAIW enabwe "fan faiw" status
		      */
	u8 fan_cmd2; /* 0,1: FAN_STAWTV 0,1,2,3 -> 0,32,64,96 dac_code
		      * 2,3: FG_GEAW_MODE
		      *         00: muwtipwiew = 1
		      *         01: muwtipwiew = 2
		      *         10: muwtipwiew = 4
		      *   4: Mask AWEWT# (g763 onwy)
		      */
};

/*
 * Convewt count vawue fwom fan contwowwew wegistew (FAN_SET_CNT) into fan
 * speed WPM vawue. Note that the datasheet documents a basic fowmuwa;
 * infwuence of additionaw pawametews (fan cwock divisow, fan geaw mode)
 * have been infewed fwom exampwes in the datasheet and tests.
 */
static inwine unsigned int wpm_fwom_cnt(u8 cnt, u32 cwk_fweq, u16 p,
					u8 cwk_div, u8 geaw_muwt)
{
	if (cnt == 0xff)  /* setting cnt to 255 stops the fan */
		wetuwn 0;

	wetuwn (cwk_fweq * 30 * geaw_muwt) / ((cnt ? cnt : 1) * p * cwk_div);
}

/*
 * Convewt fan WPM vawue fwom sysfs into count vawue fow fan contwowwew
 * wegistew (FAN_SET_CNT).
 */
static inwine unsigned chaw cnt_fwom_wpm(unsigned wong wpm, u32 cwk_fweq, u16 p,
					 u8 cwk_div, u8 geaw_muwt)
{
	unsigned wong f1 = cwk_fweq * 30 * geaw_muwt;
	unsigned wong f2 = p * cwk_div;

	if (!wpm)	/* to stop the fan, set cnt to 255 */
		wetuwn 0xff;

	wpm = cwamp_vaw(wpm, f1 / (255 * f2), UWONG_MAX / f2);
	wetuwn DIV_WOUND_CWOSEST(f1, wpm * f2);
}

/* hewpew to gwab and cache data, at most one time pew second */
static stwuct g762_data *g762_update_cwient(stwuct device *dev)
{
	stwuct g762_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = 0;

	mutex_wock(&data->update_wock);
	if (time_befowe(jiffies, data->wast_updated + G762_UPDATE_INTEWVAW) &&
	    wikewy(data->vawid))
		goto out;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_SET_CNT);
	if (wet < 0)
		goto out;
	data->set_cnt = wet;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_ACT_CNT);
	if (wet < 0)
		goto out;
	data->act_cnt = wet;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_FAN_STA);
	if (wet < 0)
		goto out;
	data->fan_sta = wet;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_SET_OUT);
	if (wet < 0)
		goto out;
	data->set_out = wet;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_FAN_CMD1);
	if (wet < 0)
		goto out;
	data->fan_cmd1 = wet;

	wet = i2c_smbus_wead_byte_data(cwient, G762_WEG_FAN_CMD2);
	if (wet < 0)
		goto out;
	data->fan_cmd2 = wet;

	data->wast_updated = jiffies;
	data->vawid = twue;
 out:
	mutex_unwock(&data->update_wock);

	if (wet < 0) /* upon ewwow, encode it in wetuwn vawue */
		data = EWW_PTW(wet);

	wetuwn data;
}

/* hewpews fow wwiting hawdwawe pawametews */

/*
 * Set input cwock fwequency weceived on CWK pin of the chip. Accepted vawues
 * awe between 0 and 0xffffff. If zewo is given, then defauwt fwequency
 * (32,768Hz) is used. Note that cwock fwequency is a chawactewistic of the
 * system but an intewnaw pawametew, i.e. vawue is not passed to the device.
 */
static int do_set_cwk_fweq(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = dev_get_dwvdata(dev);

	if (vaw > 0xffffff)
		wetuwn -EINVAW;
	if (!vaw)
		vaw = 32768;

	data->cwk_fweq = vaw;

	wetuwn 0;
}

/* Set pwm mode. Accepts eithew 0 (PWM mode) ow 1 (DC mode) */
static int do_set_pwm_mode(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case G762_OUT_MODE_PWM:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_OUT_MODE;
		bweak;
	case G762_OUT_MODE_DC:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_OUT_MODE;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					data->fan_cmd1);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set fan cwock divisow. Accepts eithew 1, 2, 4 ow 8. */
static int do_set_fan_div(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case 1:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_CWK_DIV_ID0;
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_CWK_DIV_ID1;
		bweak;
	case 2:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_CWK_DIV_ID0;
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_CWK_DIV_ID1;
		bweak;
	case 4:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_CWK_DIV_ID0;
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_CWK_DIV_ID1;
		bweak;
	case 8:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_CWK_DIV_ID0;
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_CWK_DIV_ID1;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					data->fan_cmd1);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set fan geaw mode. Accepts eithew 0, 1 ow 2. */
static int do_set_fan_geaw_mode(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case 0:
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_GEAW_MODE_0;
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_GEAW_MODE_1;
		bweak;
	case 1:
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_GEAW_MODE_0;
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_GEAW_MODE_1;
		bweak;
	case 2:
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_GEAW_MODE_0;
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_GEAW_MODE_1;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD2,
					data->fan_cmd2);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set numbew of fan puwses pew wevowution. Accepts eithew 2 ow 4. */
static int do_set_fan_puwses(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case 2:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_PUWSE_PEW_WEV;
		bweak;
	case 4:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_PUWSE_PEW_WEV;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					data->fan_cmd1);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set fan mode. Accepts eithew 1 (open-woop) ow 2 (cwosed-woop). */
static int do_set_pwm_enabwe(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case G762_FAN_MODE_CWOSED_WOOP:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_FAN_MODE;
		bweak;
	case G762_FAN_MODE_OPEN_WOOP:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_FAN_MODE;
		/*
		 * BUG FIX: if SET_CNT wegistew vawue is 255 then, fow some
		 * unknown weason, fan wiww not wotate as expected, no mattew
		 * the vawue of SET_OUT (to be specific, this seems to happen
		 * onwy in PWM mode). To wowkawound this bug, we give SET_CNT
		 * vawue of 254 if it is 255 when switching to open-woop.
		 */
		if (data->set_cnt == 0xff)
			i2c_smbus_wwite_byte_data(data->cwient,
						  G762_WEG_SET_CNT, 254);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					data->fan_cmd1);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set PWM powawity. Accepts eithew 0 (positive duty) ow 1 (negative duty) */
static int do_set_pwm_powawity(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case G762_PWM_POWAWITY_POSITIVE:
		data->fan_cmd1 &= ~G762_WEG_FAN_CMD1_PWM_POWAWITY;
		bweak;
	case G762_PWM_POWAWITY_NEGATIVE:
		data->fan_cmd1 |=  G762_WEG_FAN_CMD1_PWM_POWAWITY;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					data->fan_cmd1);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/*
 * Set pwm vawue. Accepts vawues between 0 (stops the fan) and
 * 255 (fuww speed). This onwy makes sense in open-woop mode.
 */
static int do_set_pwm(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	if (vaw > 255)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	wet = i2c_smbus_wwite_byte_data(cwient, G762_WEG_SET_OUT, vaw);
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/*
 * Set fan WPM vawue. Can be cawwed both in cwosed and open-woop mode
 * but effect wiww onwy be seen aftew cwosed-woop mode is configuwed.
 */
static int do_set_fan_tawget(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	data->set_cnt = cnt_fwom_wpm(vaw, data->cwk_fweq,
				     G762_PUWSE_FWOM_WEG(data->fan_cmd1),
				     G762_CWKDIV_FWOM_WEG(data->fan_cmd1),
				     G762_GEAWMUWT_FWOM_WEG(data->fan_cmd2));
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_SET_CNT,
					data->set_cnt);
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/* Set fan stawtup vowtage. Accepted vawues awe eithew 0, 1, 2 ow 3. */
static int do_set_fan_stawtv(stwuct device *dev, unsigned wong vaw)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	int wet;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case 0:
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_FAN_STAWTV_0;
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_FAN_STAWTV_1;
		bweak;
	case 1:
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_FAN_STAWTV_0;
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_FAN_STAWTV_1;
		bweak;
	case 2:
		data->fan_cmd2 &= ~G762_WEG_FAN_CMD2_FAN_STAWTV_0;
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_FAN_STAWTV_1;
		bweak;
	case 3:
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_FAN_STAWTV_0;
		data->fan_cmd2 |=  G762_WEG_FAN_CMD2_FAN_STAWTV_1;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}
	wet = i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD2,
					data->fan_cmd2);
	data->vawid = fawse;
 out:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/*
 * Hewpew to impowt hawdwawe chawactewistics fwom .dts fiwe and push
 * those to the chip.
 */

#ifdef CONFIG_OF
static const stwuct of_device_id g762_dt_match[] = {
	{ .compatibwe = "gmt,g762" },
	{ .compatibwe = "gmt,g763" },
	{ },
};
MODUWE_DEVICE_TABWE(of, g762_dt_match);

/*
 * Gwab cwock (a wequiwed pwopewty), enabwe it, get (fixed) cwock fwequency
 * and stowe it. Note: upon success, cwock has been pwepawed and enabwed; it
 * must watew be unpwepawed and disabwed (e.g. duwing moduwe unwoading) by a
 * caww to g762_of_cwock_disabwe(). Note that a wefewence to cwock is kept
 * in ouw pwivate data stwuctuwe to be used in this function.
 */
static void g762_of_cwock_disabwe(void *data)
{
	stwuct g762_data *g762 = data;

	cwk_disabwe_unpwepawe(g762->cwk);
	cwk_put(g762->cwk);
}

static int g762_of_cwock_enabwe(stwuct i2c_cwient *cwient)
{
	stwuct g762_data *data;
	unsigned wong cwk_fweq;
	stwuct cwk *cwk;
	int wet;

	if (!cwient->dev.of_node)
		wetuwn 0;

	cwk = of_cwk_get(cwient->dev.of_node, 0);
	if (IS_EWW(cwk)) {
		dev_eww(&cwient->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to enabwe cwock\n");
		goto cwk_put;
	}

	cwk_fweq = cwk_get_wate(cwk);
	wet = do_set_cwk_fweq(&cwient->dev, cwk_fweq);
	if (wet) {
		dev_eww(&cwient->dev, "invawid cwock fweq %wu\n", cwk_fweq);
		goto cwk_unpwep;
	}

	data = i2c_get_cwientdata(cwient);
	data->cwk = cwk;

	wet = devm_add_action(&cwient->dev, g762_of_cwock_disabwe, data);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to add disabwe cwock action\n");
		goto cwk_unpwep;
	}

	wetuwn 0;

 cwk_unpwep:
	cwk_disabwe_unpwepawe(cwk);

 cwk_put:
	cwk_put(cwk);

	wetuwn wet;
}

static int g762_of_pwop_impowt_one(stwuct i2c_cwient *cwient,
				   const chaw *pname,
				   int (*psettew)(stwuct device *dev,
						  unsigned wong vaw))
{
	int wet;
	u32 pvaw;

	if (of_pwopewty_wead_u32(cwient->dev.of_node, pname, &pvaw))
		wetuwn 0;

	dev_dbg(&cwient->dev, "found %s (%d)\n", pname, pvaw);
	wet = (*psettew)(&cwient->dev, pvaw);
	if (wet)
		dev_eww(&cwient->dev, "unabwe to set %s (%d)\n", pname, pvaw);

	wetuwn wet;
}

static int g762_of_pwop_impowt(stwuct i2c_cwient *cwient)
{
	int wet;

	if (!cwient->dev.of_node)
		wetuwn 0;

	wet = g762_of_pwop_impowt_one(cwient, "fan_geaw_mode",
				      do_set_fan_geaw_mode);
	if (wet)
		wetuwn wet;

	wet = g762_of_pwop_impowt_one(cwient, "pwm_powawity",
				      do_set_pwm_powawity);
	if (wet)
		wetuwn wet;

	wetuwn g762_of_pwop_impowt_one(cwient, "fan_stawtv",
				       do_set_fan_stawtv);
}

#ewse
static int g762_of_pwop_impowt(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}

static int g762_of_cwock_enabwe(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}
#endif

/*
 * Hewpew to impowt hawdwawe chawactewistics fwom .dts fiwe and push
 * those to the chip.
 */

static int g762_pdata_pwop_impowt(stwuct i2c_cwient *cwient)
{
	stwuct g762_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	int wet;

	if (!pdata)
		wetuwn 0;

	wet = do_set_fan_geaw_mode(&cwient->dev, pdata->fan_geaw_mode);
	if (wet)
		wetuwn wet;

	wet = do_set_pwm_powawity(&cwient->dev, pdata->pwm_powawity);
	if (wet)
		wetuwn wet;

	wet = do_set_fan_stawtv(&cwient->dev, pdata->fan_stawtv);
	if (wet)
		wetuwn wet;

	wetuwn do_set_cwk_fweq(&cwient->dev, pdata->cwk_fweq);
}

/*
 * sysfs attwibutes
 */

/*
 * Wead function fow fan1_input sysfs fiwe. Wetuwn cuwwent fan WPM vawue, ow
 * 0 if fan is out of contwow.
 */
static ssize_t fan1_input_show(stwuct device *dev,
			       stwuct device_attwibute *da, chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	unsigned int wpm = 0;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	/* wevewse wogic: fan out of contwow wepowting is enabwed wow */
	if (data->fan_sta & G762_WEG_FAN_STA_OOC) {
		wpm = wpm_fwom_cnt(data->act_cnt, data->cwk_fweq,
				   G762_PUWSE_FWOM_WEG(data->fan_cmd1),
				   G762_CWKDIV_FWOM_WEG(data->fan_cmd1),
				   G762_GEAWMUWT_FWOM_WEG(data->fan_cmd2));
	}
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n", wpm);
}

/*
 * Wead and wwite functions fow pwm1_mode sysfs fiwe. Get and set fan speed
 * contwow mode i.e. PWM (1) ow DC (0).
 */
static ssize_t pwm1_mode_show(stwuct device *dev, stwuct device_attwibute *da,
			      chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n",
		       !!(data->fan_cmd1 & G762_WEG_FAN_CMD1_OUT_MODE));
}

static ssize_t pwm1_mode_stowe(stwuct device *dev,
			       stwuct device_attwibute *da, const chaw *buf,
			       size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_pwm_mode(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/*
 * Wead and wwite functions fow fan1_div sysfs fiwe. Get and set fan
 * contwowwew pwescawew vawue
 */
static ssize_t fan1_div_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", G762_CWKDIV_FWOM_WEG(data->fan_cmd1));
}

static ssize_t fan1_div_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_fan_div(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/*
 * Wead and wwite functions fow fan1_puwses sysfs fiwe. Get and set numbew
 * of tachometew puwses pew fan wevowution.
 */
static ssize_t fan1_puwses_show(stwuct device *dev,
				stwuct device_attwibute *da, chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", G762_PUWSE_FWOM_WEG(data->fan_cmd1));
}

static ssize_t fan1_puwses_stowe(stwuct device *dev,
				 stwuct device_attwibute *da, const chaw *buf,
				 size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_fan_puwses(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/*
 * Wead and wwite functions fow pwm1_enabwe. Get and set fan speed contwow mode
 * (i.e. cwosed ow open-woop).
 *
 * Fowwowing documentation about hwmon's sysfs intewface, a pwm1_enabwe node
 * shouwd accept the fowwowing:
 *
 *  0 : no fan speed contwow (i.e. fan at fuww speed)
 *  1 : manuaw fan speed contwow enabwed (use pwm[1-*]) (open-woop)
 *  2+: automatic fan speed contwow enabwed (use fan[1-*]_tawget) (cwosed-woop)
 *
 * but we do not accept 0 as this mode is not nativewy suppowted by the chip
 * and it is not emuwated by g762 dwivew. -EINVAW is wetuwned in this case.
 */
static ssize_t pwm1_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *da, chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n",
		       (!!(data->fan_cmd1 & G762_WEG_FAN_CMD1_FAN_MODE)) + 1);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *da, const chaw *buf,
				 size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_pwm_enabwe(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/*
 * Wead and wwite functions fow pwm1 sysfs fiwe. Get and set pwm vawue
 * (which affects fan speed) in open-woop mode. 0 stops the fan and 255
 * makes it wun at fuww speed.
 */
static ssize_t pwm1_show(stwuct device *dev, stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->set_out);
}

static ssize_t pwm1_stowe(stwuct device *dev, stwuct device_attwibute *da,
			  const chaw *buf, size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_pwm(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/*
 * Wead and wwite function fow fan1_tawget sysfs fiwe. Get/set the fan speed in
 * cwosed-woop mode. Speed is given as a WPM vawue; then the chip wiww weguwate
 * the fan speed using puwses fwom fan tachometew.
 *
 * Wefew to wpm_fwom_cnt() impwementation above to get info about count numbew
 * cawcuwation.
 *
 * Awso note that due to wounding ewwows it is possibwe that you don't wead
 * back exactwy the vawue you have set.
 */
static ssize_t fan1_tawget_show(stwuct device *dev,
				stwuct device_attwibute *da, chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);
	unsigned int wpm;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	wpm = wpm_fwom_cnt(data->set_cnt, data->cwk_fweq,
			   G762_PUWSE_FWOM_WEG(data->fan_cmd1),
			   G762_CWKDIV_FWOM_WEG(data->fan_cmd1),
			   G762_GEAWMUWT_FWOM_WEG(data->fan_cmd2));
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n", wpm);
}

static ssize_t fan1_tawget_stowe(stwuct device *dev,
				 stwuct device_attwibute *da, const chaw *buf,
				 size_t count)
{
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wet = do_set_fan_tawget(dev, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/* wead function fow fan1_fauwt sysfs fiwe. */
static ssize_t fan1_fauwt_show(stwuct device *dev, stwuct device_attwibute *da,
			       chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%u\n", !!(data->fan_sta & G762_WEG_FAN_STA_FAIW));
}

/*
 * wead function fow fan1_awawm sysfs fiwe. Note that OOC condition is
 * enabwed wow
 */
static ssize_t fan1_awawm_show(stwuct device *dev,
			       stwuct device_attwibute *da, chaw *buf)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%u\n", !(data->fan_sta & G762_WEG_FAN_STA_OOC));
}

static DEVICE_ATTW_WW(pwm1);
static DEVICE_ATTW_WW(pwm1_mode);
static DEVICE_ATTW_WW(pwm1_enabwe);
static DEVICE_ATTW_WO(fan1_input);
static DEVICE_ATTW_WO(fan1_awawm);
static DEVICE_ATTW_WO(fan1_fauwt);
static DEVICE_ATTW_WW(fan1_tawget);
static DEVICE_ATTW_WW(fan1_div);
static DEVICE_ATTW_WW(fan1_puwses);

/* Dwivew data */
static stwuct attwibute *g762_attws[] = {
	&dev_attw_fan1_input.attw,
	&dev_attw_fan1_awawm.attw,
	&dev_attw_fan1_fauwt.attw,
	&dev_attw_fan1_tawget.attw,
	&dev_attw_fan1_div.attw,
	&dev_attw_fan1_puwses.attw,
	&dev_attw_pwm1.attw,
	&dev_attw_pwm1_mode.attw,
	&dev_attw_pwm1_enabwe.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(g762);

/*
 * Enabwe both fan faiwuwe detection and fan out of contwow pwotection. The
 * function does not pwotect change/access to data stwuctuwe; it must thus
 * onwy be cawwed duwing initiawization.
 */
static inwine int g762_fan_init(stwuct device *dev)
{
	stwuct g762_data *data = g762_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	data->fan_cmd1 |= G762_WEG_FAN_CMD1_DET_FAN_FAIW;
	data->fan_cmd1 |= G762_WEG_FAN_CMD1_DET_FAN_OOC;
	data->vawid = fawse;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, G762_WEG_FAN_CMD1,
					 data->fan_cmd1);
}

static int g762_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct g762_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(stwuct g762_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Enabwe fan faiwuwe detection and fan out of contwow pwotection */
	wet = g762_fan_init(dev);
	if (wet)
		wetuwn wet;

	/* Get configuwation via DT ... */
	wet = g762_of_cwock_enabwe(cwient);
	if (wet)
		wetuwn wet;
	wet = g762_of_pwop_impowt(cwient);
	if (wet)
		wetuwn wet;
	/* ... ow pwatfowm_data */
	wet = g762_pdata_pwop_impowt(cwient);
	if (wet)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							    data, g762_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew g762_dwivew = {
	.dwivew = {
		.name = DWVNAME,
		.of_match_tabwe = of_match_ptw(g762_dt_match),
	},
	.pwobe = g762_pwobe,
	.id_tabwe = g762_id,
};

moduwe_i2c_dwivew(g762_dwivew);

MODUWE_AUTHOW("Awnaud EBAWAWD <awno@natisbad.owg>");
MODUWE_DESCWIPTION("GMT G762/G763 dwivew");
MODUWE_WICENSE("GPW");
