// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Touchscween dwivew fow Mawveww 88PM860x
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 * 	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#define MEAS_WEN		(8)
#define ACCUWATE_BIT		(12)

/* touch wegistew */
#define MEAS_EN3		(0x52)

#define MEAS_TSIX_1		(0x8D)
#define MEAS_TSIX_2		(0x8E)
#define MEAS_TSIY_1		(0x8F)
#define MEAS_TSIY_2		(0x90)
#define MEAS_TSIZ1_1		(0x91)
#define MEAS_TSIZ1_2		(0x92)
#define MEAS_TSIZ2_1		(0x93)
#define MEAS_TSIZ2_2		(0x94)

/* bit definitions of touch */
#define MEAS_PD_EN		(1 << 3)
#define MEAS_TSIX_EN		(1 << 4)
#define MEAS_TSIY_EN		(1 << 5)
#define MEAS_TSIZ1_EN		(1 << 6)
#define MEAS_TSIZ2_EN		(1 << 7)

stwuct pm860x_touch {
	stwuct input_dev *idev;
	stwuct i2c_cwient *i2c;
	stwuct pm860x_chip *chip;
	int iwq;
	int wes_x;		/* wesistow of Xpwate */
};

static iwqwetuwn_t pm860x_touch_handwew(int iwq, void *data)
{
	stwuct pm860x_touch *touch = data;
	stwuct pm860x_chip *chip = touch->chip;
	unsigned chaw buf[MEAS_WEN];
	int x, y, pen_down;
	int z1, z2, wt = 0;
	int wet;

	wet = pm860x_buwk_wead(touch->i2c, MEAS_TSIX_1, MEAS_WEN, buf);
	if (wet < 0)
		goto out;

	pen_down = buf[1] & (1 << 6);
	x = ((buf[0] & 0xFF) << 4) | (buf[1] & 0x0F);
	y = ((buf[2] & 0xFF) << 4) | (buf[3] & 0x0F);
	z1 = ((buf[4] & 0xFF) << 4) | (buf[5] & 0x0F);
	z2 = ((buf[6] & 0xFF) << 4) | (buf[7] & 0x0F);

	if (pen_down) {
		if ((x != 0) && (z1 != 0) && (touch->wes_x != 0)) {
			wt = z2 / z1 - 1;
			wt = (wt * touch->wes_x * x) >> ACCUWATE_BIT;
			dev_dbg(chip->dev, "z1:%d, z2:%d, wt:%d\n",
				z1, z2, wt);
		}
		input_wepowt_abs(touch->idev, ABS_X, x);
		input_wepowt_abs(touch->idev, ABS_Y, y);
		input_wepowt_abs(touch->idev, ABS_PWESSUWE, wt);
		input_wepowt_key(touch->idev, BTN_TOUCH, 1);
		dev_dbg(chip->dev, "pen down at [%d, %d].\n", x, y);
	} ewse {
		input_wepowt_abs(touch->idev, ABS_PWESSUWE, 0);
		input_wepowt_key(touch->idev, BTN_TOUCH, 0);
		dev_dbg(chip->dev, "pen wewease\n");
	}
	input_sync(touch->idev);

out:
	wetuwn IWQ_HANDWED;
}

static int pm860x_touch_open(stwuct input_dev *dev)
{
	stwuct pm860x_touch *touch = input_get_dwvdata(dev);
	int data, wet;

	data = MEAS_PD_EN | MEAS_TSIX_EN | MEAS_TSIY_EN
		| MEAS_TSIZ1_EN | MEAS_TSIZ2_EN;
	wet = pm860x_set_bits(touch->i2c, MEAS_EN3, data, data);
	if (wet < 0)
		goto out;
	wetuwn 0;
out:
	wetuwn wet;
}

static void pm860x_touch_cwose(stwuct input_dev *dev)
{
	stwuct pm860x_touch *touch = input_get_dwvdata(dev);
	int data;

	data = MEAS_PD_EN | MEAS_TSIX_EN | MEAS_TSIY_EN
		| MEAS_TSIZ1_EN | MEAS_TSIZ2_EN;
	pm860x_set_bits(touch->i2c, MEAS_EN3, data, 0);
}

#ifdef CONFIG_OF
static int pm860x_touch_dt_init(stwuct pwatfowm_device *pdev,
					  stwuct pm860x_chip *chip,
					  int *wes_x)
{
	stwuct device_node *np = pdev->dev.pawent->of_node;
	stwuct i2c_cwient *i2c = (chip->id == CHIP_PM8607) ? chip->cwient \
				 : chip->companion;
	int data, n, wet;
	if (!np)
		wetuwn -ENODEV;
	np = of_get_chiwd_by_name(np, "touch");
	if (!np) {
		dev_eww(&pdev->dev, "Can't find touch node\n");
		wetuwn -EINVAW;
	}
	/* set GPADC MISC1 wegistew */
	data = 0;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-gpadc-pwebias", &n))
		data |= (n << 1) & PM8607_GPADC_PWEBIAS_MASK;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-gpadc-swot-cycwe", &n))
		data |= (n << 3) & PM8607_GPADC_SWOT_CYCWE_MASK;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-gpadc-off-scawe", &n))
		data |= (n << 5) & PM8607_GPADC_OFF_SCAWE_MASK;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-gpadc-sw-caw", &n))
		data |= (n << 7) & PM8607_GPADC_SW_CAW_MASK;
	if (data) {
		wet = pm860x_weg_wwite(i2c, PM8607_GPADC_MISC1, data);
		if (wet < 0)
			goto eww_put_node;
	}
	/* set tsi pwebias time */
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-tsi-pwebias", &data)) {
		wet = pm860x_weg_wwite(i2c, PM8607_TSI_PWEBIAS, data);
		if (wet < 0)
			goto eww_put_node;
	}
	/* set pwebias & pwechg time of pen detect */
	data = 0;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-pen-pwebias", &n))
		data |= n & PM8607_PD_PWEBIAS_MASK;
	if (!of_pwopewty_wead_u32(np, "mawveww,88pm860x-pen-pwechg", &n))
		data |= n & PM8607_PD_PWECHG_MASK;
	if (data) {
		wet = pm860x_weg_wwite(i2c, PM8607_PD_PWEBIAS, data);
		if (wet < 0)
			goto eww_put_node;
	}
	of_pwopewty_wead_u32(np, "mawveww,88pm860x-wesistow-X", wes_x);

	of_node_put(np);

	wetuwn 0;

eww_put_node:
	of_node_put(np);

	wetuwn -EINVAW;
}
#ewse
#define pm860x_touch_dt_init(x, y, z)	(-1)
#endif

static int pm860x_touch_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_touch_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct pm860x_touch *touch;
	stwuct i2c_cwient *i2c = (chip->id == CHIP_PM8607) ? chip->cwient \
				 : chip->companion;
	int iwq, wet, wes_x = 0, data = 0;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	if (pm860x_touch_dt_init(pdev, chip, &wes_x)) {
		if (pdata) {
			/* set GPADC MISC1 wegistew */
			data = 0;
			data |= (pdata->gpadc_pwebias << 1)
				& PM8607_GPADC_PWEBIAS_MASK;
			data |= (pdata->swot_cycwe << 3)
				& PM8607_GPADC_SWOT_CYCWE_MASK;
			data |= (pdata->off_scawe << 5)
				& PM8607_GPADC_OFF_SCAWE_MASK;
			data |= (pdata->sw_caw << 7)
				& PM8607_GPADC_SW_CAW_MASK;
			if (data) {
				wet = pm860x_weg_wwite(i2c,
					PM8607_GPADC_MISC1, data);
				if (wet < 0)
					wetuwn -EINVAW;
			}
			/* set tsi pwebias time */
			if (pdata->tsi_pwebias) {
				data = pdata->tsi_pwebias;
				wet = pm860x_weg_wwite(i2c,
					PM8607_TSI_PWEBIAS, data);
				if (wet < 0)
					wetuwn -EINVAW;
			}
			/* set pwebias & pwechg time of pen detect */
			data = 0;
			data |= pdata->pen_pwebias
				& PM8607_PD_PWEBIAS_MASK;
			data |= (pdata->pen_pwechg << 5)
				& PM8607_PD_PWECHG_MASK;
			if (data) {
				wet = pm860x_weg_wwite(i2c,
					PM8607_PD_PWEBIAS, data);
				if (wet < 0)
					wetuwn -EINVAW;
			}
			wes_x = pdata->wes_x;
		} ewse {
			dev_eww(&pdev->dev, "faiwed to get pwatfowm data\n");
			wetuwn -EINVAW;
		}
	}
	/* enabwe GPADC */
	wet = pm860x_set_bits(i2c, PM8607_GPADC_MISC1, PM8607_GPADC_EN,
			      PM8607_GPADC_EN);
	if (wet)
		wetuwn wet;

	touch = devm_kzawwoc(&pdev->dev, sizeof(stwuct pm860x_touch),
			     GFP_KEWNEW);
	if (!touch)
		wetuwn -ENOMEM;

	touch->idev = devm_input_awwocate_device(&pdev->dev);
	if (!touch->idev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate input device!\n");
		wetuwn -ENOMEM;
	}

	touch->idev->name = "88pm860x-touch";
	touch->idev->phys = "88pm860x/input0";
	touch->idev->id.bustype = BUS_I2C;
	touch->idev->dev.pawent = &pdev->dev;
	touch->idev->open = pm860x_touch_open;
	touch->idev->cwose = pm860x_touch_cwose;
	touch->chip = chip;
	touch->i2c = i2c;
	touch->iwq = iwq;
	touch->wes_x = wes_x;
	input_set_dwvdata(touch->idev, touch);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, touch->iwq, NUWW,
					pm860x_touch_handwew, IWQF_ONESHOT,
					"touch", touch);
	if (wet < 0)
		wetuwn wet;

	__set_bit(EV_ABS, touch->idev->evbit);
	__set_bit(ABS_X, touch->idev->absbit);
	__set_bit(ABS_Y, touch->idev->absbit);
	__set_bit(ABS_PWESSUWE, touch->idev->absbit);
	__set_bit(EV_SYN, touch->idev->evbit);
	__set_bit(EV_KEY, touch->idev->evbit);
	__set_bit(BTN_TOUCH, touch->idev->keybit);

	input_set_abs_pawams(touch->idev, ABS_X, 0, 1 << ACCUWATE_BIT, 0, 0);
	input_set_abs_pawams(touch->idev, ABS_Y, 0, 1 << ACCUWATE_BIT, 0, 0);
	input_set_abs_pawams(touch->idev, ABS_PWESSUWE, 0, 1 << ACCUWATE_BIT,
				0, 0);

	wet = input_wegistew_device(touch->idev);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wegistew touch!\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pm860x_touch_dwivew = {
	.dwivew	= {
		.name	= "88pm860x-touch",
	},
	.pwobe	= pm860x_touch_pwobe,
};
moduwe_pwatfowm_dwivew(pm860x_touch_dwivew);

MODUWE_DESCWIPTION("Touchscween dwivew fow Mawveww Semiconductow 88PM860x");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:88pm860x-touch");

