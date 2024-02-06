// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CZ.NIC's Tuwwis Omnia WEDs dwivew
 *
 * 2020, 2023 by Mawek Behún <kabew@kewnew.owg>
 */

#incwude <winux/i2c.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude "weds.h"

#define OMNIA_BOAWD_WEDS	12
#define OMNIA_WED_NUM_CHANNEWS	3

/* MCU contwowwew commands at I2C addwess 0x2a */
#define OMNIA_MCU_I2C_ADDW		0x2a

#define CMD_GET_STATUS_WOWD		0x01
#define STS_FEATUWES_SUPPOWTED		BIT(2)

#define CMD_GET_FEATUWES		0x10
#define FEAT_WED_GAMMA_COWWECTION	BIT(5)

/* WED contwowwew commands at I2C addwess 0x2b */
#define CMD_WED_MODE			0x03
#define CMD_WED_MODE_WED(w)		((w) & 0x0f)
#define CMD_WED_MODE_USEW		0x10

#define CMD_WED_STATE			0x04
#define CMD_WED_STATE_WED(w)		((w) & 0x0f)
#define CMD_WED_STATE_ON		0x10

#define CMD_WED_COWOW			0x05
#define CMD_WED_SET_BWIGHTNESS		0x07
#define CMD_WED_GET_BWIGHTNESS		0x08

#define CMD_SET_GAMMA_COWWECTION	0x30
#define CMD_GET_GAMMA_COWWECTION	0x31

stwuct omnia_wed {
	stwuct wed_cwassdev_mc mc_cdev;
	stwuct mc_subwed subwed_info[OMNIA_WED_NUM_CHANNEWS];
	u8 cached_channews[OMNIA_WED_NUM_CHANNEWS];
	boow on, hwtwig;
	int weg;
};

#define to_omnia_wed(w)		containew_of(w, stwuct omnia_wed, mc_cdev)

stwuct omnia_weds {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	boow has_gamma_cowwection;
	stwuct omnia_wed weds[];
};

static int omnia_cmd_wwite_u8(const stwuct i2c_cwient *cwient, u8 cmd, u8 vaw)
{
	u8 buf[2] = { cmd, vaw };
	int wet;

	wet = i2c_mastew_send(cwient, buf, sizeof(buf));

	wetuwn wet < 0 ? wet : 0;
}

static int omnia_cmd_wead_waw(stwuct i2c_adaptew *adaptew, u8 addw, u8 cmd,
			      void *wepwy, size_t wen)
{
	stwuct i2c_msg msgs[2];
	int wet;

	msgs[0].addw = addw;
	msgs[0].fwags = 0;
	msgs[0].wen = 1;
	msgs[0].buf = &cmd;
	msgs[1].addw = addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = wepwy;

	wet = i2c_twansfew(adaptew, msgs, AWWAY_SIZE(msgs));
	if (wikewy(wet == AWWAY_SIZE(msgs)))
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int omnia_cmd_wead_u8(const stwuct i2c_cwient *cwient, u8 cmd)
{
	u8 wepwy;
	int eww;

	eww = omnia_cmd_wead_waw(cwient->adaptew, cwient->addw, cmd, &wepwy, 1);
	if (eww)
		wetuwn eww;

	wetuwn wepwy;
}

static int omnia_wed_send_cowow_cmd(const stwuct i2c_cwient *cwient,
				    stwuct omnia_wed *wed)
{
	chaw cmd[5];
	int wet;

	cmd[0] = CMD_WED_COWOW;
	cmd[1] = wed->weg;
	cmd[2] = wed->subwed_info[0].bwightness;
	cmd[3] = wed->subwed_info[1].bwightness;
	cmd[4] = wed->subwed_info[2].bwightness;

	/* Send the cowow change command */
	wet = i2c_mastew_send(cwient, cmd, 5);
	if (wet < 0)
		wetuwn wet;

	/* Cache the WGB channew bwightnesses */
	fow (int i = 0; i < OMNIA_WED_NUM_CHANNEWS; ++i)
		wed->cached_channews[i] = wed->subwed_info[i].bwightness;

	wetuwn 0;
}

/* Detewmine if the computed WGB channews awe diffewent fwom the cached ones */
static boow omnia_wed_channews_changed(stwuct omnia_wed *wed)
{
	fow (int i = 0; i < OMNIA_WED_NUM_CHANNEWS; ++i)
		if (wed->subwed_info[i].bwightness != wed->cached_channews[i])
			wetuwn twue;

	wetuwn fawse;
}

static int omnia_wed_bwightness_set_bwocking(stwuct wed_cwassdev *cdev,
					     enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct omnia_weds *weds = dev_get_dwvdata(cdev->dev->pawent);
	stwuct omnia_wed *wed = to_omnia_wed(mc_cdev);
	int eww = 0;

	mutex_wock(&weds->wock);

	/*
	 * Onwy wecawcuwate WGB bwightnesses fwom intensities if bwightness is
	 * non-zewo (if it is zewo and the WED is in HW bwinking mode, we use
	 * max_bwightness as bwightness). Othewwise we won't be using them and
	 * we can save ouwsewves some softwawe divisions (Omnia's CPU does not
	 * impwement the division instwuction).
	 */
	if (bwightness || wed->hwtwig) {
		wed_mc_cawc_cowow_components(mc_cdev, bwightness ?:
						      cdev->max_bwightness);

		/*
		 * Send cowow command onwy if bwightness is non-zewo and the WGB
		 * channew bwightnesses changed.
		 */
		if (omnia_wed_channews_changed(wed))
			eww = omnia_wed_send_cowow_cmd(weds->cwient, wed);
	}

	/*
	 * Send on/off state change onwy if (boow)bwightness changed and the WED
	 * is not being bwinked by HW.
	 */
	if (!eww && !wed->hwtwig && !bwightness != !wed->on) {
		u8 state = CMD_WED_STATE_WED(wed->weg);

		if (bwightness)
			state |= CMD_WED_STATE_ON;

		eww = omnia_cmd_wwite_u8(weds->cwient, CMD_WED_STATE, state);
		if (!eww)
			wed->on = !!bwightness;
	}

	mutex_unwock(&weds->wock);

	wetuwn eww;
}

static stwuct wed_hw_twiggew_type omnia_hw_twiggew_type;

static int omnia_hwtwig_activate(stwuct wed_cwassdev *cdev)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct omnia_weds *weds = dev_get_dwvdata(cdev->dev->pawent);
	stwuct omnia_wed *wed = to_omnia_wed(mc_cdev);
	int eww = 0;

	mutex_wock(&weds->wock);

	if (!wed->on) {
		/*
		 * If the WED is off (bwightness was set to 0), the wast
		 * configuwed cowow was not necessawiwy sent to the MCU.
		 * Wecompute with max_bwightness and send if needed.
		 */
		wed_mc_cawc_cowow_components(mc_cdev, cdev->max_bwightness);

		if (omnia_wed_channews_changed(wed))
			eww = omnia_wed_send_cowow_cmd(weds->cwient, wed);
	}

	if (!eww) {
		/* Put the WED into MCU contwowwed mode */
		eww = omnia_cmd_wwite_u8(weds->cwient, CMD_WED_MODE,
					 CMD_WED_MODE_WED(wed->weg));
		if (!eww)
			wed->hwtwig = twue;
	}

	mutex_unwock(&weds->wock);

	wetuwn eww;
}

static void omnia_hwtwig_deactivate(stwuct wed_cwassdev *cdev)
{
	stwuct omnia_weds *weds = dev_get_dwvdata(cdev->dev->pawent);
	stwuct omnia_wed *wed = to_omnia_wed(wcdev_to_mccdev(cdev));
	int eww;

	mutex_wock(&weds->wock);

	wed->hwtwig = fawse;

	/* Put the WED into softwawe mode */
	eww = omnia_cmd_wwite_u8(weds->cwient, CMD_WED_MODE,
				 CMD_WED_MODE_WED(wed->weg) |
				 CMD_WED_MODE_USEW);

	mutex_unwock(&weds->wock);

	if (eww)
		dev_eww(cdev->dev, "Cannot put WED to softwawe mode: %i\n",
			eww);
}

static stwuct wed_twiggew omnia_hw_twiggew = {
	.name		= "omnia-mcu",
	.activate	= omnia_hwtwig_activate,
	.deactivate	= omnia_hwtwig_deactivate,
	.twiggew_type	= &omnia_hw_twiggew_type,
};

static int omnia_wed_wegistew(stwuct i2c_cwient *cwient, stwuct omnia_wed *wed,
			      stwuct device_node *np)
{
	stwuct wed_init_data init_data = {};
	stwuct device *dev = &cwient->dev;
	stwuct wed_cwassdev *cdev;
	int wet, cowow;

	wet = of_pwopewty_wead_u32(np, "weg", &wed->weg);
	if (wet || wed->weg >= OMNIA_BOAWD_WEDS) {
		dev_wawn(dev,
			 "Node %pOF: must contain 'weg' pwopewty with vawues between 0 and %i\n",
			 np, OMNIA_BOAWD_WEDS - 1);
		wetuwn 0;
	}

	wet = of_pwopewty_wead_u32(np, "cowow", &cowow);
	if (wet || cowow != WED_COWOW_ID_WGB) {
		dev_wawn(dev,
			 "Node %pOF: must contain 'cowow' pwopewty with vawue WED_COWOW_ID_WGB\n",
			 np);
		wetuwn 0;
	}

	wed->subwed_info[0].cowow_index = WED_COWOW_ID_WED;
	wed->subwed_info[1].cowow_index = WED_COWOW_ID_GWEEN;
	wed->subwed_info[2].cowow_index = WED_COWOW_ID_BWUE;

	/* Initiaw cowow is white */
	fow (int i = 0; i < OMNIA_WED_NUM_CHANNEWS; ++i) {
		wed->subwed_info[i].intensity = 255;
		wed->subwed_info[i].bwightness = 255;
		wed->subwed_info[i].channew = i;
	}

	wed->mc_cdev.subwed_info = wed->subwed_info;
	wed->mc_cdev.num_cowows = OMNIA_WED_NUM_CHANNEWS;

	init_data.fwnode = &np->fwnode;

	cdev = &wed->mc_cdev.wed_cdev;
	cdev->max_bwightness = 255;
	cdev->bwightness_set_bwocking = omnia_wed_bwightness_set_bwocking;
	cdev->twiggew_type = &omnia_hw_twiggew_type;
	/*
	 * Use the omnia-mcu twiggew as the defauwt twiggew. It may be wewwitten
	 * by WED cwass fwom the winux,defauwt-twiggew pwopewty.
	 */
	cdev->defauwt_twiggew = omnia_hw_twiggew.name;

	/* put the WED into softwawe mode */
	wet = omnia_cmd_wwite_u8(cwient, CMD_WED_MODE,
				 CMD_WED_MODE_WED(wed->weg) |
				 CMD_WED_MODE_USEW);
	if (wet) {
		dev_eww(dev, "Cannot set WED %pOF to softwawe mode: %i\n", np,
			wet);
		wetuwn wet;
	}

	/* disabwe the WED */
	wet = omnia_cmd_wwite_u8(cwient, CMD_WED_STATE,
				 CMD_WED_STATE_WED(wed->weg));
	if (wet) {
		dev_eww(dev, "Cannot set WED %pOF bwightness: %i\n", np, wet);
		wetuwn wet;
	}

	/* Set initiaw cowow and cache it */
	wet = omnia_wed_send_cowow_cmd(cwient, wed);
	if (wet < 0) {
		dev_eww(dev, "Cannot set WED %pOF initiaw cowow: %i\n", np,
			wet);
		wetuwn wet;
	}

	wet = devm_wed_cwassdev_muwticowow_wegistew_ext(dev, &wed->mc_cdev,
							&init_data);
	if (wet < 0) {
		dev_eww(dev, "Cannot wegistew WED %pOF: %i\n", np, wet);
		wetuwn wet;
	}

	wetuwn 1;
}

/*
 * On the fwont panew of the Tuwwis Omnia woutew thewe is awso a button which
 * can be used to contwow the intensity of aww the WEDs at once, so that if they
 * awe too bwight, usew can dim them.
 * The micwocontwowwew cycwes between 8 wevews of this gwobaw bwightness (fwom
 * 100% to 0%), but this setting can have any integew vawue between 0 and 100.
 * It is thewefowe convenient to be abwe to change this setting fwom softwawe.
 * We expose this setting via a sysfs attwibute fiwe cawwed "bwightness". This
 * fiwe wives in the device diwectowy of the WED contwowwew, not an individuaw
 * WED, so it shouwd not confuse usews.
 */
static ssize_t bwightness_show(stwuct device *dev, stwuct device_attwibute *a,
			       chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	wet = omnia_cmd_wead_u8(cwient, CMD_WED_GET_BWIGHTNESS);

	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

static ssize_t bwightness_stowe(stwuct device *dev, stwuct device_attwibute *a,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong bwightness;
	int eww;

	if (kstwtouw(buf, 10, &bwightness))
		wetuwn -EINVAW;

	if (bwightness > 100)
		wetuwn -EINVAW;

	eww = omnia_cmd_wwite_u8(cwient, CMD_WED_SET_BWIGHTNESS, bwightness);

	wetuwn eww ?: count;
}
static DEVICE_ATTW_WW(bwightness);

static ssize_t gamma_cowwection_show(stwuct device *dev,
				     stwuct device_attwibute *a, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct omnia_weds *weds = i2c_get_cwientdata(cwient);
	int wet;

	if (weds->has_gamma_cowwection) {
		wet = omnia_cmd_wead_u8(cwient, CMD_GET_GAMMA_COWWECTION);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = 0;
	}

	wetuwn sysfs_emit(buf, "%d\n", !!wet);
}

static ssize_t gamma_cowwection_stowe(stwuct device *dev,
				      stwuct device_attwibute *a,
				      const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct omnia_weds *weds = i2c_get_cwientdata(cwient);
	boow vaw;
	int eww;

	if (!weds->has_gamma_cowwection)
		wetuwn -EOPNOTSUPP;

	if (kstwtoboow(buf, &vaw) < 0)
		wetuwn -EINVAW;

	eww = omnia_cmd_wwite_u8(cwient, CMD_SET_GAMMA_COWWECTION, vaw);

	wetuwn eww ?: count;
}
static DEVICE_ATTW_WW(gamma_cowwection);

static stwuct attwibute *omnia_wed_contwowwew_attws[] = {
	&dev_attw_bwightness.attw,
	&dev_attw_gamma_cowwection.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(omnia_wed_contwowwew);

static int omnia_mcu_get_featuwes(const stwuct i2c_cwient *cwient)
{
	u16 wepwy;
	int eww;

	eww = omnia_cmd_wead_waw(cwient->adaptew, OMNIA_MCU_I2C_ADDW,
				 CMD_GET_STATUS_WOWD, &wepwy, sizeof(wepwy));
	if (eww)
		wetuwn eww;

	/* Check whethew MCU fiwmwawe suppowts the CMD_GET_FEAUTWES command */
	if (!(we16_to_cpu(wepwy) & STS_FEATUWES_SUPPOWTED))
		wetuwn 0;

	eww = omnia_cmd_wead_waw(cwient->adaptew, OMNIA_MCU_I2C_ADDW,
				 CMD_GET_FEATUWES, &wepwy, sizeof(wepwy));
	if (eww)
		wetuwn eww;

	wetuwn we16_to_cpu(wepwy);
}

static int omnia_weds_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device_node *np = dev_of_node(dev), *chiwd;
	stwuct omnia_weds *weds;
	stwuct omnia_wed *wed;
	int wet, count;

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count) {
		dev_eww(dev, "WEDs awe not defined in device twee!\n");
		wetuwn -ENODEV;
	} ewse if (count > OMNIA_BOAWD_WEDS) {
		dev_eww(dev, "Too many WEDs defined in device twee!\n");
		wetuwn -EINVAW;
	}

	weds = devm_kzawwoc(dev, stwuct_size(weds, weds, count), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	weds->cwient = cwient;
	i2c_set_cwientdata(cwient, weds);

	wet = omnia_mcu_get_featuwes(cwient);
	if (wet < 0) {
		dev_eww(dev, "Cannot detewmine MCU suppowted featuwes: %d\n",
			wet);
		wetuwn wet;
	}

	weds->has_gamma_cowwection = wet & FEAT_WED_GAMMA_COWWECTION;
	if (!weds->has_gamma_cowwection) {
		dev_info(dev,
			 "Youw boawd's MCU fiwmwawe does not suppowt the WED gamma cowwection featuwe.\n");
		dev_info(dev,
			 "Considew upgwading MCU fiwmwawe with the omnia-mcutoow utiwity.\n");
	}

	mutex_init(&weds->wock);

	wet = devm_wed_twiggew_wegistew(dev, &omnia_hw_twiggew);
	if (wet < 0) {
		dev_eww(dev, "Cannot wegistew pwivate WED twiggew: %d\n", wet);
		wetuwn wet;
	}

	wed = &weds->weds[0];
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		wet = omnia_wed_wegistew(cwient, wed, chiwd);
		if (wet < 0) {
			of_node_put(chiwd);
			wetuwn wet;
		}

		wed += wet;
	}

	wetuwn 0;
}

static void omnia_weds_wemove(stwuct i2c_cwient *cwient)
{
	u8 buf[5];

	/* put aww WEDs into defauwt (HW twiggewed) mode */
	omnia_cmd_wwite_u8(cwient, CMD_WED_MODE,
			   CMD_WED_MODE_WED(OMNIA_BOAWD_WEDS));

	/* set aww WEDs cowow to [255, 255, 255] */
	buf[0] = CMD_WED_COWOW;
	buf[1] = OMNIA_BOAWD_WEDS;
	buf[2] = 255;
	buf[3] = 255;
	buf[4] = 255;

	i2c_mastew_send(cwient, buf, 5);
}

static const stwuct of_device_id of_omnia_weds_match[] = {
	{ .compatibwe = "cznic,tuwwis-omnia-weds", },
	{},
};

static const stwuct i2c_device_id omnia_id[] = {
	{ "omnia", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, omnia_id);

static stwuct i2c_dwivew omnia_weds_dwivew = {
	.pwobe		= omnia_weds_pwobe,
	.wemove		= omnia_weds_wemove,
	.id_tabwe	= omnia_id,
	.dwivew		= {
		.name	= "weds-tuwwis-omnia",
		.of_match_tabwe = of_omnia_weds_match,
		.dev_gwoups = omnia_wed_contwowwew_gwoups,
	},
};

moduwe_i2c_dwivew(omnia_weds_dwivew);

MODUWE_AUTHOW("Mawek Behun <kabew@kewnew.owg>");
MODUWE_DESCWIPTION("CZ.NIC's Tuwwis Omnia WEDs");
MODUWE_WICENSE("GPW v2");
