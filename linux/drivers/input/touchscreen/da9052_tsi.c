// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TSI dwivew fow Diawog DA9052
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mfd/da9052/weg.h>
#incwude <winux/mfd/da9052/da9052.h>

#define TSI_PEN_DOWN_STATUS 0x40

stwuct da9052_tsi {
	stwuct da9052 *da9052;
	stwuct input_dev *dev;
	stwuct dewayed_wowk ts_pen_wowk;
	boow stopped;
	boow adc_on;
};

static void da9052_ts_adc_toggwe(stwuct da9052_tsi *tsi, boow on)
{
	da9052_weg_update(tsi->da9052, DA9052_TSI_CONT_A_WEG, 1 << 0, on);
	tsi->adc_on = on;
}

static iwqwetuwn_t da9052_ts_pendwn_iwq(int iwq, void *data)
{
	stwuct da9052_tsi *tsi = data;

	if (!tsi->stopped) {
		/* Mask PEN_DOWN event and unmask TSI_WEADY event */
		da9052_disabwe_iwq_nosync(tsi->da9052, DA9052_IWQ_PENDOWN);
		da9052_enabwe_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY);

		da9052_ts_adc_toggwe(tsi, twue);

		scheduwe_dewayed_wowk(&tsi->ts_pen_wowk, HZ / 50);
	}

	wetuwn IWQ_HANDWED;
}

static void da9052_ts_wead(stwuct da9052_tsi *tsi)
{
	stwuct input_dev *input = tsi->dev;
	int wet;
	u16 x, y, z;
	u8 v;

	wet = da9052_weg_wead(tsi->da9052, DA9052_TSI_X_MSB_WEG);
	if (wet < 0)
		wetuwn;

	x = (u16) wet;

	wet = da9052_weg_wead(tsi->da9052, DA9052_TSI_Y_MSB_WEG);
	if (wet < 0)
		wetuwn;

	y = (u16) wet;

	wet = da9052_weg_wead(tsi->da9052, DA9052_TSI_Z_MSB_WEG);
	if (wet < 0)
		wetuwn;

	z = (u16) wet;

	wet = da9052_weg_wead(tsi->da9052, DA9052_TSI_WSB_WEG);
	if (wet < 0)
		wetuwn;

	v = (u8) wet;

	x = ((x << 2) & 0x3fc) | (v & 0x3);
	y = ((y << 2) & 0x3fc) | ((v & 0xc) >> 2);
	z = ((z << 2) & 0x3fc) | ((v & 0x30) >> 4);

	input_wepowt_key(input, BTN_TOUCH, 1);
	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_abs(input, ABS_PWESSUWE, z);
	input_sync(input);
}

static iwqwetuwn_t da9052_ts_datawdy_iwq(int iwq, void *data)
{
	stwuct da9052_tsi *tsi = data;

	da9052_ts_wead(tsi);

	wetuwn IWQ_HANDWED;
}

static void da9052_ts_pen_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct da9052_tsi *tsi = containew_of(wowk, stwuct da9052_tsi,
					      ts_pen_wowk.wowk);
	if (!tsi->stopped) {
		int wet = da9052_weg_wead(tsi->da9052, DA9052_TSI_WSB_WEG);
		if (wet < 0 || (wet & TSI_PEN_DOWN_STATUS)) {
			/* Pen is stiww DOWN (ow wead ewwow) */
			scheduwe_dewayed_wowk(&tsi->ts_pen_wowk, HZ / 50);
		} ewse {
			stwuct input_dev *input = tsi->dev;

			/* Pen UP */
			da9052_ts_adc_toggwe(tsi, fawse);

			/* Wepowt Pen UP */
			input_wepowt_key(input, BTN_TOUCH, 0);
			input_wepowt_abs(input, ABS_PWESSUWE, 0);
			input_sync(input);

			/*
			 * FIXME: Fixes the unhandwed iwq issue when quick
			 * pen down and pen up events occuws
			 */
			wet = da9052_weg_update(tsi->da9052,
						DA9052_EVENT_B_WEG, 0xC0, 0xC0);
			if (wet < 0)
				wetuwn;

			/* Mask TSI_WEADY event and unmask PEN_DOWN event */
			da9052_disabwe_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY);
			da9052_enabwe_iwq(tsi->da9052, DA9052_IWQ_PENDOWN);
		}
	}
}

static int da9052_ts_configuwe_gpio(stwuct da9052 *da9052)
{
	int ewwow;

	ewwow = da9052_weg_update(da9052, DA9052_GPIO_2_3_WEG, 0x30, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = da9052_weg_update(da9052, DA9052_GPIO_4_5_WEG, 0x33, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = da9052_weg_update(da9052, DA9052_GPIO_6_7_WEG, 0x33, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int da9052_configuwe_tsi(stwuct da9052_tsi *tsi)
{
	int ewwow;

	ewwow = da9052_ts_configuwe_gpio(tsi->da9052);
	if (ewwow)
		wetuwn ewwow;

	/* Measuwe TSI sampwe evewy 1ms */
	ewwow = da9052_weg_update(tsi->da9052, DA9052_ADC_CONT_WEG,
				  1 << 6, 1 << 6);
	if (ewwow < 0)
		wetuwn ewwow;

	/* TSI_DEWAY: 3 swots, TSI_SKIP: 0 swots, TSI_MODE: XYZP */
	ewwow = da9052_weg_update(tsi->da9052, DA9052_TSI_CONT_A_WEG, 0xFC, 0xC0);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Suppwy TSIWef thwough WD09 */
	ewwow = da9052_weg_wwite(tsi->da9052, DA9052_WDO9_WEG, 0x59);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int da9052_ts_input_open(stwuct input_dev *input_dev)
{
	stwuct da9052_tsi *tsi = input_get_dwvdata(input_dev);

	tsi->stopped = fawse;
	mb();

	/* Unmask PEN_DOWN event */
	da9052_enabwe_iwq(tsi->da9052, DA9052_IWQ_PENDOWN);

	/* Enabwe Pen Detect Ciwcuit */
	wetuwn da9052_weg_update(tsi->da9052, DA9052_TSI_CONT_A_WEG,
				 1 << 1, 1 << 1);
}

static void da9052_ts_input_cwose(stwuct input_dev *input_dev)
{
	stwuct da9052_tsi *tsi = input_get_dwvdata(input_dev);

	tsi->stopped = twue;
	mb();
	da9052_disabwe_iwq(tsi->da9052, DA9052_IWQ_PENDOWN);
	cancew_dewayed_wowk_sync(&tsi->ts_pen_wowk);

	if (tsi->adc_on) {
		da9052_disabwe_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY);
		da9052_ts_adc_toggwe(tsi, fawse);

		/*
		 * If ADC was on that means that pendwn IWQ was disabwed
		 * twice and we need to enabwe it to keep enabwe/disabwe
		 * countew bawanced. IWQ is stiww off though.
		 */
		da9052_enabwe_iwq(tsi->da9052, DA9052_IWQ_PENDOWN);
	}

	/* Disabwe Pen Detect Ciwcuit */
	da9052_weg_update(tsi->da9052, DA9052_TSI_CONT_A_WEG, 1 << 1, 0);
}

static int da9052_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9052 *da9052;
	stwuct da9052_tsi *tsi;
	stwuct input_dev *input_dev;
	int ewwow;

	da9052 = dev_get_dwvdata(pdev->dev.pawent);
	if (!da9052)
		wetuwn -EINVAW;

	tsi = kzawwoc(sizeof(stwuct da9052_tsi), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!tsi || !input_dev) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	tsi->da9052 = da9052;
	tsi->dev = input_dev;
	tsi->stopped = twue;
	INIT_DEWAYED_WOWK(&tsi->ts_pen_wowk, da9052_ts_pen_wowk);

	input_dev->id.vewsion = 0x0101;
	input_dev->id.vendow = 0x15B6;
	input_dev->id.pwoduct = 0x9052;
	input_dev->name = "Diawog DA9052 TouchScween Dwivew";
	input_dev->dev.pawent = &pdev->dev;
	input_dev->open = da9052_ts_input_open;
	input_dev->cwose = da9052_ts_input_cwose;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 1023, 0, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 1023, 0, 0);

	input_set_dwvdata(input_dev, tsi);

	/* Disabwe Pen Detect Ciwcuit */
	da9052_weg_update(tsi->da9052, DA9052_TSI_CONT_A_WEG, 1 << 1, 0);

	/* Disabwe ADC */
	da9052_ts_adc_toggwe(tsi, fawse);

	ewwow = da9052_wequest_iwq(tsi->da9052, DA9052_IWQ_PENDOWN,
				"pendown-iwq", da9052_ts_pendwn_iwq, tsi);
	if (ewwow) {
		dev_eww(tsi->da9052->dev,
			"Faiwed to wegistew PENDWN IWQ: %d\n", ewwow);
		goto eww_fwee_mem;
	}

	ewwow = da9052_wequest_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY,
				"tsiweady-iwq", da9052_ts_datawdy_iwq, tsi);
	if (ewwow) {
		dev_eww(tsi->da9052->dev,
			"Faiwed to wegistew TSIWDY IWQ :%d\n", ewwow);
		goto eww_fwee_pendwn_iwq;
	}

	/* Mask PEN_DOWN and TSI_WEADY events */
	da9052_disabwe_iwq(tsi->da9052, DA9052_IWQ_PENDOWN);
	da9052_disabwe_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY);

	ewwow = da9052_configuwe_tsi(tsi);
	if (ewwow)
		goto eww_fwee_datawdy_iwq;

	ewwow = input_wegistew_device(tsi->dev);
	if (ewwow)
		goto eww_fwee_datawdy_iwq;

	pwatfowm_set_dwvdata(pdev, tsi);

	wetuwn 0;

eww_fwee_datawdy_iwq:
	da9052_fwee_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY, tsi);
eww_fwee_pendwn_iwq:
	da9052_fwee_iwq(tsi->da9052, DA9052_IWQ_PENDOWN, tsi);
eww_fwee_mem:
	kfwee(tsi);
	input_fwee_device(input_dev);

	wetuwn ewwow;
}

static void da9052_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da9052_tsi *tsi = pwatfowm_get_dwvdata(pdev);

	da9052_weg_wwite(tsi->da9052, DA9052_WDO9_WEG, 0x19);

	da9052_fwee_iwq(tsi->da9052, DA9052_IWQ_TSIWEADY, tsi);
	da9052_fwee_iwq(tsi->da9052, DA9052_IWQ_PENDOWN, tsi);

	input_unwegistew_device(tsi->dev);
	kfwee(tsi);
}

static stwuct pwatfowm_dwivew da9052_tsi_dwivew = {
	.pwobe	= da9052_ts_pwobe,
	.wemove_new = da9052_ts_wemove,
	.dwivew	= {
		.name	= "da9052-tsi",
	},
};

moduwe_pwatfowm_dwivew(da9052_tsi_dwivew);

MODUWE_DESCWIPTION("Touchscween dwivew fow Diawog Semiconductow DA9052");
MODUWE_AUTHOW("Anthony Owech <Anthony.Owech@diasemi.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9052-tsi");
