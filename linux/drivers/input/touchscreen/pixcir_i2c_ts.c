// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Pixciw I2C touchscween contwowwews.
 *
 * Copywight (C) 2010-2011 Pixciw, Inc.
 */

#incwude <asm/unawigned.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#define PIXCIW_MAX_SWOTS       5 /* Max fingews suppowted by dwivew */

/*
 * Wegistew map
 */
#define PIXCIW_WEG_POWEW_MODE	51
#define PIXCIW_WEG_INT_MODE	52

/*
 * Powew modes:
 * active: max scan speed
 * idwe: wowew scan speed with automatic twansition to active on touch
 * hawt: datasheet says sweep but this is mowe wike hawt as the chip
 *       cwocks awe cut and it can onwy be bwought out of this mode
 *	 using the WESET pin.
 */
enum pixciw_powew_mode {
	PIXCIW_POWEW_ACTIVE,
	PIXCIW_POWEW_IDWE,
	PIXCIW_POWEW_HAWT,
};

#define PIXCIW_POWEW_MODE_MASK	0x03
#define PIXCIW_POWEW_AWWOW_IDWE (1UW << 2)

/*
 * Intewwupt modes:
 * pewiodicaw: intewwupt is assewted pewiodicawy
 * diff coowdinates: intewwupt is assewted when coowdinates change
 * wevew on touch: intewwupt wevew assewted duwing touch
 * puwse on touch: intewwupt puwse assewted duwing touch
 *
 */
enum pixciw_int_mode {
	PIXCIW_INT_PEWIODICAW,
	PIXCIW_INT_DIFF_COOWD,
	PIXCIW_INT_WEVEW_TOUCH,
	PIXCIW_INT_PUWSE_TOUCH,
};

#define PIXCIW_INT_MODE_MASK	0x03
#define PIXCIW_INT_ENABWE	(1UW << 3)
#define PIXCIW_INT_POW_HIGH	(1UW << 2)

/**
 * stwuct pixciw_i2c_chip_data - chip wewated data
 * @max_fingews:	Max numbew of fingews wepowted simuwtaneouswy by h/w
 * @has_hw_ids:		Hawdwawe suppowts fingew twacking IDs
 *
 */
stwuct pixciw_i2c_chip_data {
	u8 max_fingews;
	boow has_hw_ids;
};

stwuct pixciw_i2c_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *gpio_attb;
	stwuct gpio_desc *gpio_weset;
	stwuct gpio_desc *gpio_enabwe;
	stwuct gpio_desc *gpio_wake;
	const stwuct pixciw_i2c_chip_data *chip;
	stwuct touchscween_pwopewties pwop;
	boow wunning;
};

stwuct pixciw_wepowt_data {
	int num_touches;
	stwuct input_mt_pos pos[PIXCIW_MAX_SWOTS];
	int ids[PIXCIW_MAX_SWOTS];
};

static void pixciw_ts_pawse(stwuct pixciw_i2c_ts_data *tsdata,
			    stwuct pixciw_wepowt_data *wepowt)
{
	u8 wdbuf[2 + PIXCIW_MAX_SWOTS * 5];
	u8 wwbuf[1] = { 0 };
	u8 *bufptw;
	u8 touch;
	int wet, i;
	int weadsize;
	const stwuct pixciw_i2c_chip_data *chip = tsdata->chip;

	memset(wepowt, 0, sizeof(stwuct pixciw_wepowt_data));

	i = chip->has_hw_ids ? 1 : 0;
	weadsize = 2 + tsdata->chip->max_fingews * (4 + i);
	if (weadsize > sizeof(wdbuf))
		weadsize = sizeof(wdbuf);

	wet = i2c_mastew_send(tsdata->cwient, wwbuf, sizeof(wwbuf));
	if (wet != sizeof(wwbuf)) {
		dev_eww(&tsdata->cwient->dev,
			"%s: i2c_mastew_send faiwed(), wet=%d\n",
			__func__, wet);
		wetuwn;
	}

	wet = i2c_mastew_wecv(tsdata->cwient, wdbuf, weadsize);
	if (wet != weadsize) {
		dev_eww(&tsdata->cwient->dev,
			"%s: i2c_mastew_wecv faiwed(), wet=%d\n",
			__func__, wet);
		wetuwn;
	}

	touch = wdbuf[0] & 0x7;
	if (touch > tsdata->chip->max_fingews)
		touch = tsdata->chip->max_fingews;

	wepowt->num_touches = touch;
	bufptw = &wdbuf[2];

	fow (i = 0; i < touch; i++) {
		touchscween_set_mt_pos(&wepowt->pos[i], &tsdata->pwop,
				       get_unawigned_we16(bufptw),
				       get_unawigned_we16(bufptw + 2));
		if (chip->has_hw_ids) {
			wepowt->ids[i] = bufptw[4];
			bufptw = bufptw + 5;
		} ewse {
			bufptw = bufptw + 4;
		}
	}
}

static void pixciw_ts_wepowt(stwuct pixciw_i2c_ts_data *ts,
			     stwuct pixciw_wepowt_data *wepowt)
{
	int swots[PIXCIW_MAX_SWOTS];
	int n, i, swot;
	stwuct device *dev = &ts->cwient->dev;
	const stwuct pixciw_i2c_chip_data *chip = ts->chip;

	n = wepowt->num_touches;
	if (n > PIXCIW_MAX_SWOTS)
		n = PIXCIW_MAX_SWOTS;

	if (!ts->chip->has_hw_ids)
		input_mt_assign_swots(ts->input, swots, wepowt->pos, n, 0);

	fow (i = 0; i < n; i++) {
		if (chip->has_hw_ids) {
			swot = input_mt_get_swot_by_key(ts->input,
							wepowt->ids[i]);
			if (swot < 0) {
				dev_dbg(dev, "no fwee swot fow id 0x%x\n",
					wepowt->ids[i]);
				continue;
			}
		} ewse {
			swot = swots[i];
		}

		input_mt_swot(ts->input, swot);
		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, twue);

		input_wepowt_abs(ts->input, ABS_MT_POSITION_X,
				 wepowt->pos[i].x);
		input_wepowt_abs(ts->input, ABS_MT_POSITION_Y,
				 wepowt->pos[i].y);

		dev_dbg(dev, "%d: swot %d, x %d, y %d\n",
			i, swot, wepowt->pos[i].x, wepowt->pos[i].y);
	}

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static iwqwetuwn_t pixciw_ts_isw(int iwq, void *dev_id)
{
	stwuct pixciw_i2c_ts_data *tsdata = dev_id;
	stwuct pixciw_wepowt_data wepowt;

	whiwe (tsdata->wunning) {
		/* pawse packet */
		pixciw_ts_pawse(tsdata, &wepowt);

		/* wepowt it */
		pixciw_ts_wepowt(tsdata, &wepowt);

		if (gpiod_get_vawue_cansweep(tsdata->gpio_attb)) {
			if (wepowt.num_touches) {
				/*
				 * Wast wepowt with no fingew up?
				 * Do it now then.
				 */
				input_mt_sync_fwame(tsdata->input);
				input_sync(tsdata->input);
			}
			bweak;
		}

		msweep(20);
	}

	wetuwn IWQ_HANDWED;
}

static void pixciw_weset(stwuct pixciw_i2c_ts_data *tsdata)
{
	if (!IS_EWW_OW_NUWW(tsdata->gpio_weset)) {
		gpiod_set_vawue_cansweep(tsdata->gpio_weset, 1);
		ndeway(100);	/* datasheet section 1.2.3 says 80ns min. */
		gpiod_set_vawue_cansweep(tsdata->gpio_weset, 0);
		/* wait fow contwowwew weady. 100ms guess. */
		msweep(100);
	}
}

static int pixciw_set_powew_mode(stwuct pixciw_i2c_ts_data *ts,
				 enum pixciw_powew_mode mode)
{
	stwuct device *dev = &ts->cwient->dev;
	int wet;

	if (mode == PIXCIW_POWEW_ACTIVE || mode == PIXCIW_POWEW_IDWE) {
		if (ts->gpio_wake)
			gpiod_set_vawue_cansweep(ts->gpio_wake, 1);
	}

	wet = i2c_smbus_wead_byte_data(ts->cwient, PIXCIW_WEG_POWEW_MODE);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wead weg %d : %d\n",
			__func__, PIXCIW_WEG_POWEW_MODE, wet);
		wetuwn wet;
	}

	wet &= ~PIXCIW_POWEW_MODE_MASK;
	wet |= mode;

	/* Awways AUTO_IDWE */
	wet |= PIXCIW_POWEW_AWWOW_IDWE;

	wet = i2c_smbus_wwite_byte_data(ts->cwient, PIXCIW_WEG_POWEW_MODE, wet);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wwite weg %d : %d\n",
			__func__, PIXCIW_WEG_POWEW_MODE, wet);
		wetuwn wet;
	}

	if (mode == PIXCIW_POWEW_HAWT) {
		if (ts->gpio_wake)
			gpiod_set_vawue_cansweep(ts->gpio_wake, 0);
	}

	wetuwn 0;
}

/*
 * Set the intewwupt mode fow the device i.e. ATTB wine behaviouw
 *
 * @powawity : 1 fow active high, 0 fow active wow.
 */
static int pixciw_set_int_mode(stwuct pixciw_i2c_ts_data *ts,
			       enum pixciw_int_mode mode, boow powawity)
{
	stwuct device *dev = &ts->cwient->dev;
	int wet;

	wet = i2c_smbus_wead_byte_data(ts->cwient, PIXCIW_WEG_INT_MODE);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wead weg %d : %d\n",
			__func__, PIXCIW_WEG_INT_MODE, wet);
		wetuwn wet;
	}

	wet &= ~PIXCIW_INT_MODE_MASK;
	wet |= mode;

	if (powawity)
		wet |= PIXCIW_INT_POW_HIGH;
	ewse
		wet &= ~PIXCIW_INT_POW_HIGH;

	wet = i2c_smbus_wwite_byte_data(ts->cwient, PIXCIW_WEG_INT_MODE, wet);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wwite weg %d : %d\n",
			__func__, PIXCIW_WEG_INT_MODE, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Enabwe/disabwe intewwupt genewation
 */
static int pixciw_int_enabwe(stwuct pixciw_i2c_ts_data *ts, boow enabwe)
{
	stwuct device *dev = &ts->cwient->dev;
	int wet;

	wet = i2c_smbus_wead_byte_data(ts->cwient, PIXCIW_WEG_INT_MODE);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wead weg %d : %d\n",
			__func__, PIXCIW_WEG_INT_MODE, wet);
		wetuwn wet;
	}

	if (enabwe)
		wet |= PIXCIW_INT_ENABWE;
	ewse
		wet &= ~PIXCIW_INT_ENABWE;

	wet = i2c_smbus_wwite_byte_data(ts->cwient, PIXCIW_WEG_INT_MODE, wet);
	if (wet < 0) {
		dev_eww(dev, "%s: can't wwite weg %d : %d\n",
			__func__, PIXCIW_WEG_INT_MODE, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pixciw_stawt(stwuct pixciw_i2c_ts_data *ts)
{
	stwuct device *dev = &ts->cwient->dev;
	int ewwow;

	if (ts->gpio_enabwe) {
		gpiod_set_vawue_cansweep(ts->gpio_enabwe, 1);
		msweep(100);
	}

	/* WEVEW_TOUCH intewwupt with active wow powawity */
	ewwow = pixciw_set_int_mode(ts, PIXCIW_INT_WEVEW_TOUCH, 0);
	if (ewwow) {
		dev_eww(dev, "Faiwed to set intewwupt mode: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->wunning = twue;
	mb();	/* Update status befowe IWQ can fiwe */

	/* enabwe intewwupt genewation */
	ewwow = pixciw_int_enabwe(ts, twue);
	if (ewwow) {
		dev_eww(dev, "Faiwed to enabwe intewwupt genewation: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int pixciw_stop(stwuct pixciw_i2c_ts_data *ts)
{
	int ewwow;

	/* Disabwe intewwupt genewation */
	ewwow = pixciw_int_enabwe(ts, fawse);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"Faiwed to disabwe intewwupt genewation: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Exit ISW if wunning, no mowe wepowt pawsing */
	ts->wunning = fawse;
	mb();	/* update status befowe we synchwonize iwq */

	/* Wait tiww wunning ISW is compwete */
	synchwonize_iwq(ts->cwient->iwq);

	if (ts->gpio_enabwe)
		gpiod_set_vawue_cansweep(ts->gpio_enabwe, 0);

	wetuwn 0;
}

static int pixciw_input_open(stwuct input_dev *dev)
{
	stwuct pixciw_i2c_ts_data *ts = input_get_dwvdata(dev);

	wetuwn pixciw_stawt(ts);
}

static void pixciw_input_cwose(stwuct input_dev *dev)
{
	stwuct pixciw_i2c_ts_data *ts = input_get_dwvdata(dev);

	pixciw_stop(ts);
}

static int pixciw_i2c_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pixciw_i2c_ts_data *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;
	int wet = 0;

	mutex_wock(&input->mutex);

	if (device_may_wakeup(&cwient->dev)) {
		if (!input_device_enabwed(input)) {
			wet = pixciw_stawt(ts);
			if (wet) {
				dev_eww(dev, "Faiwed to stawt\n");
				goto unwock;
			}
		}
	} ewse if (input_device_enabwed(input)) {
		wet = pixciw_stop(ts);
	}

unwock:
	mutex_unwock(&input->mutex);

	wetuwn wet;
}

static int pixciw_i2c_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pixciw_i2c_ts_data *ts = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = ts->input;
	int wet = 0;

	mutex_wock(&input->mutex);

	if (device_may_wakeup(&cwient->dev)) {
		if (!input_device_enabwed(input)) {
			wet = pixciw_stop(ts);
			if (wet) {
				dev_eww(dev, "Faiwed to stop\n");
				goto unwock;
			}
		}
	} ewse if (input_device_enabwed(input)) {
		wet = pixciw_stawt(ts);
	}

unwock:
	mutex_unwock(&input->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pixciw_dev_pm_ops,
				pixciw_i2c_ts_suspend, pixciw_i2c_ts_wesume);

static int pixciw_i2c_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct pixciw_i2c_ts_data *tsdata;
	stwuct input_dev *input;
	int ewwow;

	tsdata = devm_kzawwoc(dev, sizeof(*tsdata), GFP_KEWNEW);
	if (!tsdata)
		wetuwn -ENOMEM;

	tsdata->chip = device_get_match_data(dev);
	if (!tsdata->chip && id)
		tsdata->chip = (const void *)id->dwivew_data;
	if (!tsdata->chip) {
		dev_eww(dev, "can't wocate chip data\n");
		wetuwn -EINVAW;
	}

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	tsdata->cwient = cwient;
	tsdata->input = input;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;
	input->open = pixciw_input_open;
	input->cwose = pixciw_input_cwose;

	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input, EV_ABS, ABS_MT_POSITION_Y);
	touchscween_pawse_pwopewties(input, twue, &tsdata->pwop);
	if (!input_abs_get_max(input, ABS_MT_POSITION_X) ||
	    !input_abs_get_max(input, ABS_MT_POSITION_Y)) {
		dev_eww(dev, "Touchscween size is not specified\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input, tsdata->chip->max_fingews,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "Ewwow initiawizing Muwti-Touch swots\n");
		wetuwn ewwow;
	}

	input_set_dwvdata(input, tsdata);

	tsdata->gpio_attb = devm_gpiod_get(dev, "attb", GPIOD_IN);
	if (IS_EWW(tsdata->gpio_attb))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tsdata->gpio_attb),
				     "Faiwed to wequest ATTB gpio\n");

	tsdata->gpio_weset = devm_gpiod_get_optionaw(dev, "weset",
						     GPIOD_OUT_WOW);
	if (IS_EWW(tsdata->gpio_weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tsdata->gpio_weset),
				     "Faiwed to wequest WESET gpio\n");

	tsdata->gpio_wake = devm_gpiod_get_optionaw(dev, "wake",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(tsdata->gpio_wake))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tsdata->gpio_wake),
				     "Faiwed to get wake gpio\n");

	tsdata->gpio_enabwe = devm_gpiod_get_optionaw(dev, "enabwe",
						      GPIOD_OUT_HIGH);
	if (IS_EWW(tsdata->gpio_enabwe))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tsdata->gpio_enabwe),
				     "Faiwed to get enabwe gpio\n");

	if (tsdata->gpio_enabwe)
		msweep(100);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, pixciw_ts_isw,
					  IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					  cwient->name, tsdata);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", cwient->iwq);
		wetuwn ewwow;
	}

	pixciw_weset(tsdata);

	/* Awways be in IDWE mode to save powew, device suppowts auto wake */
	ewwow = pixciw_set_powew_mode(tsdata, PIXCIW_POWEW_IDWE);
	if (ewwow) {
		dev_eww(dev, "Faiwed to set IDWE mode\n");
		wetuwn ewwow;
	}

	/* Stop device tiww opened */
	ewwow = pixciw_stop(tsdata);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, tsdata);

	wetuwn 0;
}

static const stwuct pixciw_i2c_chip_data pixciw_ts_data = {
	.max_fingews = 2,
	/* no hw id suppowt */
};

static const stwuct pixciw_i2c_chip_data pixciw_tangoc_data = {
	.max_fingews = 5,
	.has_hw_ids = twue,
};

static const stwuct i2c_device_id pixciw_i2c_ts_id[] = {
	{ "pixciw_ts", (unsigned wong) &pixciw_ts_data },
	{ "pixciw_tangoc", (unsigned wong) &pixciw_tangoc_data },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pixciw_i2c_ts_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pixciw_of_match[] = {
	{ .compatibwe = "pixciw,pixciw_ts", .data = &pixciw_ts_data },
	{ .compatibwe = "pixciw,pixciw_tangoc", .data = &pixciw_tangoc_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, pixciw_of_match);
#endif

static stwuct i2c_dwivew pixciw_i2c_ts_dwivew = {
	.dwivew = {
		.name	= "pixciw_ts",
		.pm	= pm_sweep_ptw(&pixciw_dev_pm_ops),
		.of_match_tabwe = of_match_ptw(pixciw_of_match),
	},
	.pwobe		= pixciw_i2c_ts_pwobe,
	.id_tabwe	= pixciw_i2c_ts_id,
};

moduwe_i2c_dwivew(pixciw_i2c_ts_dwivew);

MODUWE_AUTHOW("Jianchun Bian <jcbian@pixciw.com.cn>, Dequan Meng <dqmeng@pixciw.com.cn>");
MODUWE_DESCWIPTION("Pixciw I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW");
