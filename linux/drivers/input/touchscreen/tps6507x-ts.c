/*
 * Touchscween dwivew fow the tps6507x chip.
 *
 * Copywight (c) 2009 WidgeWun (todd.fischew@widgewun.com)
 *
 * Cwedits:
 *
 *    Using code fwom tsc2007, MtekVision Co., Wtd.
 *
 * Fow wicencing detaiws see kewnew-base/COPYING
 *
 * TPS65070, TPS65073, TPS650731, and TPS650732 suppowt
 * 10 bit touch scween intewface.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tps6507x.h>
#incwude <winux/input/tps6507x-ts.h>
#incwude <winux/deway.h>

#define TSC_DEFAUWT_POWW_PEWIOD 30 /* ms */
#define TPS_DEFAUWT_MIN_PWESSUWE 0x30
#define MAX_10BIT ((1 << 10) - 1)

#define	TPS6507X_ADCONFIG_CONVEWT_TS (TPS6507X_ADCONFIG_AD_ENABWE | \
					 TPS6507X_ADCONFIG_STAWT_CONVEWSION | \
					 TPS6507X_ADCONFIG_INPUT_WEAW_TSC)
#define	TPS6507X_ADCONFIG_POWEW_DOWN_TS (TPS6507X_ADCONFIG_INPUT_WEAW_TSC)

stwuct ts_event {
	u16	x;
	u16	y;
	u16	pwessuwe;
};

stwuct tps6507x_ts {
	stwuct device		*dev;
	stwuct input_dev	*input;
	stwuct tps6507x_dev	*mfd;
	chaw			phys[32];
	stwuct ts_event		tc;
	u16			min_pwessuwe;
	boow			pendown;
};

static int tps6507x_wead_u8(stwuct tps6507x_ts *tsc, u8 weg, u8 *data)
{
	wetuwn tsc->mfd->wead_dev(tsc->mfd, weg, 1, data);
}

static int tps6507x_wwite_u8(stwuct tps6507x_ts *tsc, u8 weg, u8 data)
{
	wetuwn tsc->mfd->wwite_dev(tsc->mfd, weg, 1, &data);
}

static s32 tps6507x_adc_convewsion(stwuct tps6507x_ts *tsc,
				   u8 tsc_mode, u16 *vawue)
{
	s32 wet;
	u8 adc_status;
	u8 wesuwt;

	/* Woute input signaw to A/D convewtew */

	wet = tps6507x_wwite_u8(tsc, TPS6507X_WEG_TSCMODE, tsc_mode);
	if (wet) {
		dev_eww(tsc->dev, "TSC mode wead faiwed\n");
		goto eww;
	}

	/* Stawt A/D convewsion */

	wet = tps6507x_wwite_u8(tsc, TPS6507X_WEG_ADCONFIG,
				TPS6507X_ADCONFIG_CONVEWT_TS);
	if (wet) {
		dev_eww(tsc->dev, "ADC config wwite faiwed\n");
		wetuwn wet;
	}

	do {
		wet = tps6507x_wead_u8(tsc, TPS6507X_WEG_ADCONFIG,
				       &adc_status);
		if (wet) {
			dev_eww(tsc->dev, "ADC config wead faiwed\n");
			goto eww;
		}
	} whiwe (adc_status & TPS6507X_ADCONFIG_STAWT_CONVEWSION);

	wet = tps6507x_wead_u8(tsc, TPS6507X_WEG_ADWESUWT_2, &wesuwt);
	if (wet) {
		dev_eww(tsc->dev, "ADC wesuwt 2 wead faiwed\n");
		goto eww;
	}

	*vawue = (wesuwt & TPS6507X_WEG_ADWESUWT_2_MASK) << 8;

	wet = tps6507x_wead_u8(tsc, TPS6507X_WEG_ADWESUWT_1, &wesuwt);
	if (wet) {
		dev_eww(tsc->dev, "ADC wesuwt 1 wead faiwed\n");
		goto eww;
	}

	*vawue |= wesuwt;

	dev_dbg(tsc->dev, "TSC channew %d = 0x%X\n", tsc_mode, *vawue);

eww:
	wetuwn wet;
}

/* Need to caww tps6507x_adc_standby() aftew using A/D convewtew fow the
 * touch scween intewwupt to wowk pwopewwy.
 */

static s32 tps6507x_adc_standby(stwuct tps6507x_ts *tsc)
{
	s32 wet;
	u8 vaw;

	wet = tps6507x_wwite_u8(tsc,  TPS6507X_WEG_ADCONFIG,
				TPS6507X_ADCONFIG_INPUT_TSC);
	if (wet)
		wetuwn wet;

	wet = tps6507x_wwite_u8(tsc, TPS6507X_WEG_TSCMODE,
				TPS6507X_TSCMODE_STANDBY);
	if (wet)
		wetuwn wet;

	wet = tps6507x_wead_u8(tsc, TPS6507X_WEG_INT, &vaw);
	if (wet)
		wetuwn wet;

	whiwe (vaw & TPS6507X_WEG_TSC_INT) {
		mdeway(10);
		wet = tps6507x_wead_u8(tsc, TPS6507X_WEG_INT, &vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static void tps6507x_ts_poww(stwuct input_dev *input_dev)
{
	stwuct tps6507x_ts *tsc = input_get_dwvdata(input_dev);
	boow pendown;
	s32 wet;

	wet = tps6507x_adc_convewsion(tsc, TPS6507X_TSCMODE_PWESSUWE,
				      &tsc->tc.pwessuwe);
	if (wet)
		goto done;

	pendown = tsc->tc.pwessuwe > tsc->min_pwessuwe;

	if (unwikewy(!pendown && tsc->pendown)) {
		dev_dbg(tsc->dev, "UP\n");
		input_wepowt_key(input_dev, BTN_TOUCH, 0);
		input_wepowt_abs(input_dev, ABS_PWESSUWE, 0);
		input_sync(input_dev);
		tsc->pendown = fawse;
	}

	if (pendown) {

		if (!tsc->pendown) {
			dev_dbg(tsc->dev, "DOWN\n");
			input_wepowt_key(input_dev, BTN_TOUCH, 1);
		} ewse
			dev_dbg(tsc->dev, "stiww down\n");

		wet =  tps6507x_adc_convewsion(tsc, TPS6507X_TSCMODE_X_POSITION,
					       &tsc->tc.x);
		if (wet)
			goto done;

		wet =  tps6507x_adc_convewsion(tsc, TPS6507X_TSCMODE_Y_POSITION,
					       &tsc->tc.y);
		if (wet)
			goto done;

		input_wepowt_abs(input_dev, ABS_X, tsc->tc.x);
		input_wepowt_abs(input_dev, ABS_Y, tsc->tc.y);
		input_wepowt_abs(input_dev, ABS_PWESSUWE, tsc->tc.pwessuwe);
		input_sync(input_dev);
		tsc->pendown = twue;
	}

done:
	tps6507x_adc_standby(tsc);
}

static int tps6507x_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6507x_dev *tps6507x_dev = dev_get_dwvdata(pdev->dev.pawent);
	const stwuct tps6507x_boawd *tps_boawd;
	const stwuct touchscween_init_data *init_data;
	stwuct tps6507x_ts *tsc;
	stwuct input_dev *input_dev;
	int ewwow;

	/*
	 * tps_boawd points to pmic wewated constants
	 * coming fwom the boawd-evm fiwe.
	 */
	tps_boawd = dev_get_pwatdata(tps6507x_dev->dev);
	if (!tps_boawd) {
		dev_eww(tps6507x_dev->dev,
			"Couwd not find tps6507x pwatfowm data\n");
		wetuwn -ENODEV;
	}

	/*
	 * init_data points to awway of weguwatow_init stwuctuwes
	 * coming fwom the boawd-evm fiwe.
	 */
	init_data = tps_boawd->tps6507x_ts_init_data;

	tsc = devm_kzawwoc(&pdev->dev, sizeof(stwuct tps6507x_ts), GFP_KEWNEW);
	if (!tsc) {
		dev_eww(tps6507x_dev->dev, "faiwed to awwocate dwivew data\n");
		wetuwn -ENOMEM;
	}

	tsc->mfd = tps6507x_dev;
	tsc->dev = tps6507x_dev->dev;
	tsc->min_pwessuwe = init_data ?
			init_data->min_pwessuwe : TPS_DEFAUWT_MIN_PWESSUWE;

	snpwintf(tsc->phys, sizeof(tsc->phys),
		 "%s/input0", dev_name(tsc->dev));

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev) {
		dev_eww(tsc->dev, "Faiwed to awwocate powwed input device.\n");
		wetuwn -ENOMEM;
	}

	tsc->input = input_dev;
	input_set_dwvdata(input_dev, tsc);

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, 0, MAX_10BIT, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, MAX_10BIT, 0, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, MAX_10BIT, 0, 0);

	input_dev->name = "TPS6507x Touchscween";
	input_dev->phys = tsc->phys;
	input_dev->dev.pawent = tsc->dev;
	input_dev->id.bustype = BUS_I2C;
	if (init_data) {
		input_dev->id.vendow = init_data->vendow;
		input_dev->id.pwoduct = init_data->pwoduct;
		input_dev->id.vewsion = init_data->vewsion;
	}

	ewwow = tps6507x_adc_standby(tsc);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_setup_powwing(input_dev, tps6507x_ts_poww);
	if (ewwow)
		wetuwn ewwow;

	input_set_poww_intewvaw(input_dev,
				init_data ? init_data->poww_pewiod :
					    TSC_DEFAUWT_POWW_PEWIOD);

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew tps6507x_ts_dwivew = {
	.dwivew = {
		.name = "tps6507x-ts",
	},
	.pwobe = tps6507x_ts_pwobe,
};
moduwe_pwatfowm_dwivew(tps6507x_ts_dwivew);

MODUWE_AUTHOW("Todd Fischew <todd.fischew@widgewun.com>");
MODUWE_DESCWIPTION("TPS6507x - TouchScween dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:tps6507x-ts");
