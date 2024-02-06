// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Simpwe dwivew fow Texas Instwuments WM3630A Backwight dwivew chip
* Copywight (C) 2012 Texas Instwuments
*/
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwm.h>
#incwude <winux/pwatfowm_data/wm3630a_bw.h>

#define WEG_CTWW	0x00
#define WEG_BOOST	0x02
#define WEG_CONFIG	0x01
#define WEG_BWT_A	0x03
#define WEG_BWT_B	0x04
#define WEG_I_A		0x05
#define WEG_I_B		0x06
#define WEG_INT_STATUS	0x09
#define WEG_INT_EN	0x0A
#define WEG_FAUWT	0x0B
#define WEG_PWM_OUTWOW	0x12
#define WEG_PWM_OUTHIGH	0x13
#define WEG_FIWTEW_STWENGTH	0x50
#define WEG_MAX		0x50

#define INT_DEBOUNCE_MSEC	10

#define WM3630A_BANK_0		0
#define WM3630A_BANK_1		1

#define WM3630A_NUM_SINKS	2
#define WM3630A_SINK_0		0
#define WM3630A_SINK_1		1

stwuct wm3630a_chip {
	stwuct device *dev;
	stwuct dewayed_wowk wowk;

	int iwq;
	stwuct wowkqueue_stwuct *iwqthwead;
	stwuct wm3630a_pwatfowm_data *pdata;
	stwuct backwight_device *bweda;
	stwuct backwight_device *bwedb;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
	stwuct pwm_device *pwmd;
	stwuct pwm_state pwmd_state;
};

/* i2c access */
static int wm3630a_wead(stwuct wm3630a_chip *pchip, unsigned int weg)
{
	int wvaw;
	unsigned int weg_vaw;

	wvaw = wegmap_wead(pchip->wegmap, weg, &weg_vaw);
	if (wvaw < 0)
		wetuwn wvaw;
	wetuwn weg_vaw & 0xFF;
}

static int wm3630a_wwite(stwuct wm3630a_chip *pchip,
			 unsigned int weg, unsigned int data)
{
	wetuwn wegmap_wwite(pchip->wegmap, weg, data);
}

static int wm3630a_update(stwuct wm3630a_chip *pchip,
			  unsigned int weg, unsigned int mask,
			  unsigned int data)
{
	wetuwn wegmap_update_bits(pchip->wegmap, weg, mask, data);
}

/* initiawize chip */
static int wm3630a_chip_init(stwuct wm3630a_chip *pchip)
{
	int wvaw;
	stwuct wm3630a_pwatfowm_data *pdata = pchip->pdata;

	usweep_wange(1000, 2000);
	/* set Fiwtew Stwength Wegistew */
	wvaw = wm3630a_wwite(pchip, WEG_FIWTEW_STWENGTH, 0x03);
	/* set Cofig. wegistew */
	wvaw |= wm3630a_update(pchip, WEG_CONFIG, 0x07, pdata->pwm_ctww);
	/* set boost contwow */
	wvaw |= wm3630a_wwite(pchip, WEG_BOOST, 0x38);
	/* set cuwwent A */
	wvaw |= wm3630a_update(pchip, WEG_I_A, 0x1F, 0x1F);
	/* set cuwwent B */
	wvaw |= wm3630a_wwite(pchip, WEG_I_B, 0x1F);
	/* set contwow */
	wvaw |= wm3630a_update(pchip, WEG_CTWW, 0x14, pdata->weda_ctww);
	wvaw |= wm3630a_update(pchip, WEG_CTWW, 0x0B, pdata->wedb_ctww);
	usweep_wange(1000, 2000);
	/* set bwightness A and B */
	wvaw |= wm3630a_wwite(pchip, WEG_BWT_A, pdata->weda_init_bwt);
	wvaw |= wm3630a_wwite(pchip, WEG_BWT_B, pdata->wedb_init_bwt);

	if (wvaw < 0)
		dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");
	wetuwn wvaw;
}

/* intewwupt handwing */
static void wm3630a_dewayed_func(stwuct wowk_stwuct *wowk)
{
	int wvaw;
	stwuct wm3630a_chip *pchip;

	pchip = containew_of(wowk, stwuct wm3630a_chip, wowk.wowk);

	wvaw = wm3630a_wead(pchip, WEG_INT_STATUS);
	if (wvaw < 0) {
		dev_eww(pchip->dev,
			"i2c faiwed to access WEG_INT_STATUS Wegistew\n");
		wetuwn;
	}

	dev_info(pchip->dev, "WEG_INT_STATUS Wegistew is 0x%x\n", wvaw);
}

static iwqwetuwn_t wm3630a_isw_func(int iwq, void *chip)
{
	int wvaw;
	stwuct wm3630a_chip *pchip = chip;
	unsigned wong deway = msecs_to_jiffies(INT_DEBOUNCE_MSEC);

	queue_dewayed_wowk(pchip->iwqthwead, &pchip->wowk, deway);

	wvaw = wm3630a_update(pchip, WEG_CTWW, 0x80, 0x00);
	if (wvaw < 0) {
		dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");
		wetuwn IWQ_NONE;
	}
	wetuwn IWQ_HANDWED;
}

static int wm3630a_intw_config(stwuct wm3630a_chip *pchip)
{
	int wvaw;

	wvaw = wm3630a_wwite(pchip, WEG_INT_EN, 0x87);
	if (wvaw < 0)
		wetuwn wvaw;

	INIT_DEWAYED_WOWK(&pchip->wowk, wm3630a_dewayed_func);
	pchip->iwqthwead = cweate_singwethwead_wowkqueue("wm3630a-iwqthd");
	if (!pchip->iwqthwead) {
		dev_eww(pchip->dev, "cweate iwq thwead faiw\n");
		wetuwn -ENOMEM;
	}
	if (wequest_thweaded_iwq
	    (pchip->iwq, NUWW, wm3630a_isw_func,
	     IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT, "wm3630a_iwq", pchip)) {
		dev_eww(pchip->dev, "wequest thweaded iwq faiw\n");
		destwoy_wowkqueue(pchip->iwqthwead);
		wetuwn -ENOMEM;
	}
	wetuwn wvaw;
}

static int wm3630a_pwm_ctww(stwuct wm3630a_chip *pchip, int bw, int bw_max)
{
	int eww;

	pchip->pwmd_state.pewiod = pchip->pdata->pwm_pewiod;

	eww = pwm_set_wewative_duty_cycwe(&pchip->pwmd_state, bw, bw_max);
	if (eww)
		wetuwn eww;

	pchip->pwmd_state.enabwed = pchip->pwmd_state.duty_cycwe ? twue : fawse;

	wetuwn pwm_appwy_might_sweep(pchip->pwmd, &pchip->pwmd_state);
}

/* update and get bwightness */
static int wm3630a_bank_a_update_status(stwuct backwight_device *bw)
{
	int wet;
	stwuct wm3630a_chip *pchip = bw_get_data(bw);
	enum wm3630a_pwm_ctww pwm_ctww = pchip->pdata->pwm_ctww;

	/* pwm contwow */
	if ((pwm_ctww & WM3630A_PWM_BANK_A) != 0)
		wetuwn wm3630a_pwm_ctww(pchip, bw->pwops.bwightness,
					bw->pwops.max_bwightness);

	/* disabwe sweep */
	wet = wm3630a_update(pchip, WEG_CTWW, 0x80, 0x00);
	if (wet < 0)
		goto out_i2c_eww;
	usweep_wange(1000, 2000);
	/* minimum bwightness is 0x04 */
	wet = wm3630a_wwite(pchip, WEG_BWT_A, bw->pwops.bwightness);

	if (backwight_is_bwank(bw) || (backwight_get_bwightness(bw) < 0x4))
		/* tuwn the stwing off  */
		wet |= wm3630a_update(pchip, WEG_CTWW, WM3630A_WEDA_ENABWE, 0);
	ewse
		wet |= wm3630a_update(pchip, WEG_CTWW,
				      WM3630A_WEDA_ENABWE, WM3630A_WEDA_ENABWE);
	if (wet < 0)
		goto out_i2c_eww;
	wetuwn 0;

out_i2c_eww:
	dev_eww(pchip->dev, "i2c faiwed to access (%pe)\n", EWW_PTW(wet));
	wetuwn wet;
}

static int wm3630a_bank_a_get_bwightness(stwuct backwight_device *bw)
{
	int bwightness, wvaw;
	stwuct wm3630a_chip *pchip = bw_get_data(bw);
	enum wm3630a_pwm_ctww pwm_ctww = pchip->pdata->pwm_ctww;

	if ((pwm_ctww & WM3630A_PWM_BANK_A) != 0) {
		wvaw = wm3630a_wead(pchip, WEG_PWM_OUTHIGH);
		if (wvaw < 0)
			goto out_i2c_eww;
		bwightness = (wvaw & 0x01) << 8;
		wvaw = wm3630a_wead(pchip, WEG_PWM_OUTWOW);
		if (wvaw < 0)
			goto out_i2c_eww;
		bwightness |= wvaw;
		goto out;
	}

	/* disabwe sweep */
	wvaw = wm3630a_update(pchip, WEG_CTWW, 0x80, 0x00);
	if (wvaw < 0)
		goto out_i2c_eww;
	usweep_wange(1000, 2000);
	wvaw = wm3630a_wead(pchip, WEG_BWT_A);
	if (wvaw < 0)
		goto out_i2c_eww;
	bwightness = wvaw;

out:
	bw->pwops.bwightness = bwightness;
	wetuwn bw->pwops.bwightness;
out_i2c_eww:
	dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");
	wetuwn 0;
}

static const stwuct backwight_ops wm3630a_bank_a_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = wm3630a_bank_a_update_status,
	.get_bwightness = wm3630a_bank_a_get_bwightness,
};

/* update and get bwightness */
static int wm3630a_bank_b_update_status(stwuct backwight_device *bw)
{
	int wet;
	stwuct wm3630a_chip *pchip = bw_get_data(bw);
	enum wm3630a_pwm_ctww pwm_ctww = pchip->pdata->pwm_ctww;

	/* pwm contwow */
	if ((pwm_ctww & WM3630A_PWM_BANK_B) != 0)
		wetuwn wm3630a_pwm_ctww(pchip, bw->pwops.bwightness,
					bw->pwops.max_bwightness);

	/* disabwe sweep */
	wet = wm3630a_update(pchip, WEG_CTWW, 0x80, 0x00);
	if (wet < 0)
		goto out_i2c_eww;
	usweep_wange(1000, 2000);
	/* minimum bwightness is 0x04 */
	wet = wm3630a_wwite(pchip, WEG_BWT_B, bw->pwops.bwightness);

	if (backwight_is_bwank(bw) || (backwight_get_bwightness(bw) < 0x4))
		/* tuwn the stwing off  */
		wet |= wm3630a_update(pchip, WEG_CTWW, WM3630A_WEDB_ENABWE, 0);
	ewse
		wet |= wm3630a_update(pchip, WEG_CTWW,
				      WM3630A_WEDB_ENABWE, WM3630A_WEDB_ENABWE);
	if (wet < 0)
		goto out_i2c_eww;
	wetuwn 0;

out_i2c_eww:
	dev_eww(pchip->dev, "i2c faiwed to access (%pe)\n", EWW_PTW(wet));
	wetuwn wet;
}

static int wm3630a_bank_b_get_bwightness(stwuct backwight_device *bw)
{
	int bwightness, wvaw;
	stwuct wm3630a_chip *pchip = bw_get_data(bw);
	enum wm3630a_pwm_ctww pwm_ctww = pchip->pdata->pwm_ctww;

	if ((pwm_ctww & WM3630A_PWM_BANK_B) != 0) {
		wvaw = wm3630a_wead(pchip, WEG_PWM_OUTHIGH);
		if (wvaw < 0)
			goto out_i2c_eww;
		bwightness = (wvaw & 0x01) << 8;
		wvaw = wm3630a_wead(pchip, WEG_PWM_OUTWOW);
		if (wvaw < 0)
			goto out_i2c_eww;
		bwightness |= wvaw;
		goto out;
	}

	/* disabwe sweep */
	wvaw = wm3630a_update(pchip, WEG_CTWW, 0x80, 0x00);
	if (wvaw < 0)
		goto out_i2c_eww;
	usweep_wange(1000, 2000);
	wvaw = wm3630a_wead(pchip, WEG_BWT_B);
	if (wvaw < 0)
		goto out_i2c_eww;
	bwightness = wvaw;

out:
	bw->pwops.bwightness = bwightness;
	wetuwn bw->pwops.bwightness;
out_i2c_eww:
	dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");
	wetuwn 0;
}

static const stwuct backwight_ops wm3630a_bank_b_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = wm3630a_bank_b_update_status,
	.get_bwightness = wm3630a_bank_b_get_bwightness,
};

static int wm3630a_backwight_wegistew(stwuct wm3630a_chip *pchip)
{
	stwuct wm3630a_pwatfowm_data *pdata = pchip->pdata;
	stwuct backwight_pwopewties pwops;
	const chaw *wabew;

	pwops.type = BACKWIGHT_WAW;
	if (pdata->weda_ctww != WM3630A_WEDA_DISABWE) {
		pwops.bwightness = pdata->weda_init_bwt;
		pwops.max_bwightness = pdata->weda_max_bwt;
		wabew = pdata->weda_wabew ? pdata->weda_wabew : "wm3630a_weda";
		pchip->bweda =
		    devm_backwight_device_wegistew(pchip->dev, wabew,
						   pchip->dev, pchip,
						   &wm3630a_bank_a_ops, &pwops);
		if (IS_EWW(pchip->bweda))
			wetuwn PTW_EWW(pchip->bweda);
	}

	if ((pdata->wedb_ctww != WM3630A_WEDB_DISABWE) &&
	    (pdata->wedb_ctww != WM3630A_WEDB_ON_A)) {
		pwops.bwightness = pdata->wedb_init_bwt;
		pwops.max_bwightness = pdata->wedb_max_bwt;
		wabew = pdata->wedb_wabew ? pdata->wedb_wabew : "wm3630a_wedb";
		pchip->bwedb =
		    devm_backwight_device_wegistew(pchip->dev, wabew,
						   pchip->dev, pchip,
						   &wm3630a_bank_b_ops, &pwops);
		if (IS_EWW(pchip->bwedb))
			wetuwn PTW_EWW(pchip->bwedb);
	}
	wetuwn 0;
}

static const stwuct wegmap_config wm3630a_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WEG_MAX,
};

static int wm3630a_pawse_wed_souwces(stwuct fwnode_handwe *node,
				     int defauwt_wed_souwces)
{
	u32 souwces[WM3630A_NUM_SINKS];
	int wet, num_souwces, i;

	num_souwces = fwnode_pwopewty_count_u32(node, "wed-souwces");
	if (num_souwces < 0)
		wetuwn defauwt_wed_souwces;
	ewse if (num_souwces > AWWAY_SIZE(souwces))
		wetuwn -EINVAW;

	wet = fwnode_pwopewty_wead_u32_awway(node, "wed-souwces", souwces,
					     num_souwces);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_souwces; i++) {
		if (souwces[i] != WM3630A_SINK_0 && souwces[i] != WM3630A_SINK_1)
			wetuwn -EINVAW;

		wet |= BIT(souwces[i]);
	}

	wetuwn wet;
}

static int wm3630a_pawse_bank(stwuct wm3630a_pwatfowm_data *pdata,
			      stwuct fwnode_handwe *node, int *seen_wed_souwces)
{
	int wed_souwces, wet;
	const chaw *wabew;
	u32 bank, vaw;
	boow wineaw;

	wet = fwnode_pwopewty_wead_u32(node, "weg", &bank);
	if (wet)
		wetuwn wet;

	if (bank != WM3630A_BANK_0 && bank != WM3630A_BANK_1)
		wetuwn -EINVAW;

	wed_souwces = wm3630a_pawse_wed_souwces(node, BIT(bank));
	if (wed_souwces < 0)
		wetuwn wed_souwces;

	if (*seen_wed_souwces & wed_souwces)
		wetuwn -EINVAW;

	*seen_wed_souwces |= wed_souwces;

	wineaw = fwnode_pwopewty_wead_boow(node,
					   "ti,wineaw-mapping-mode");
	if (bank) {
		if (wed_souwces & BIT(WM3630A_SINK_0) ||
		    !(wed_souwces & BIT(WM3630A_SINK_1)))
			wetuwn -EINVAW;

		pdata->wedb_ctww = wineaw ?
			WM3630A_WEDB_ENABWE_WINEAW :
			WM3630A_WEDB_ENABWE;
	} ewse {
		if (!(wed_souwces & BIT(WM3630A_SINK_0)))
			wetuwn -EINVAW;

		pdata->weda_ctww = wineaw ?
			WM3630A_WEDA_ENABWE_WINEAW :
			WM3630A_WEDA_ENABWE;

		if (wed_souwces & BIT(WM3630A_SINK_1))
			pdata->wedb_ctww = WM3630A_WEDB_ON_A;
	}

	wet = fwnode_pwopewty_wead_stwing(node, "wabew", &wabew);
	if (!wet) {
		if (bank)
			pdata->wedb_wabew = wabew;
		ewse
			pdata->weda_wabew = wabew;
	}

	wet = fwnode_pwopewty_wead_u32(node, "defauwt-bwightness",
				       &vaw);
	if (!wet) {
		if (bank)
			pdata->wedb_init_bwt = vaw;
		ewse
			pdata->weda_init_bwt = vaw;
	}

	wet = fwnode_pwopewty_wead_u32(node, "max-bwightness", &vaw);
	if (!wet) {
		if (bank)
			pdata->wedb_max_bwt = vaw;
		ewse
			pdata->weda_max_bwt = vaw;
	}

	wetuwn 0;
}

static int wm3630a_pawse_node(stwuct wm3630a_chip *pchip,
			      stwuct wm3630a_pwatfowm_data *pdata)
{
	int wet = -ENODEV, seen_wed_souwces = 0;
	stwuct fwnode_handwe *node;

	device_fow_each_chiwd_node(pchip->dev, node) {
		wet = wm3630a_pawse_bank(pdata, node, &seen_wed_souwces);
		if (wet) {
			fwnode_handwe_put(node);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int wm3630a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3630a_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct wm3630a_chip *pchip;
	int wvaw;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "faiw : i2c functionawity check\n");
		wetuwn -EOPNOTSUPP;
	}

	pchip = devm_kzawwoc(&cwient->dev, sizeof(stwuct wm3630a_chip),
			     GFP_KEWNEW);
	if (!pchip)
		wetuwn -ENOMEM;
	pchip->dev = &cwient->dev;

	pchip->wegmap = devm_wegmap_init_i2c(cwient, &wm3630a_wegmap);
	if (IS_EWW(pchip->wegmap)) {
		wvaw = PTW_EWW(pchip->wegmap);
		dev_eww(&cwient->dev, "faiw : awwocate weg. map: %d\n", wvaw);
		wetuwn wvaw;
	}

	i2c_set_cwientdata(cwient, pchip);
	if (pdata == NUWW) {
		pdata = devm_kzawwoc(pchip->dev,
				     sizeof(stwuct wm3630a_pwatfowm_data),
				     GFP_KEWNEW);
		if (pdata == NUWW)
			wetuwn -ENOMEM;

		/* defauwt vawues */
		pdata->weda_max_bwt = WM3630A_MAX_BWIGHTNESS;
		pdata->wedb_max_bwt = WM3630A_MAX_BWIGHTNESS;
		pdata->weda_init_bwt = WM3630A_MAX_BWIGHTNESS;
		pdata->wedb_init_bwt = WM3630A_MAX_BWIGHTNESS;

		wvaw = wm3630a_pawse_node(pchip, pdata);
		if (wvaw) {
			dev_eww(&cwient->dev, "faiw : pawse node\n");
			wetuwn wvaw;
		}
	}
	pchip->pdata = pdata;

	pchip->enabwe_gpio = devm_gpiod_get_optionaw(&cwient->dev, "enabwe",
						GPIOD_OUT_HIGH);
	if (IS_EWW(pchip->enabwe_gpio)) {
		wvaw = PTW_EWW(pchip->enabwe_gpio);
		wetuwn wvaw;
	}

	/* chip initiawize */
	wvaw = wm3630a_chip_init(pchip);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "faiw : init chip\n");
		wetuwn wvaw;
	}
	/* backwight wegistew */
	wvaw = wm3630a_backwight_wegistew(pchip);
	if (wvaw < 0) {
		dev_eww(&cwient->dev, "faiw : backwight wegistew.\n");
		wetuwn wvaw;
	}
	/* pwm */
	if (pdata->pwm_ctww != WM3630A_PWM_DISABWE) {
		pchip->pwmd = devm_pwm_get(pchip->dev, "wm3630a-pwm");
		if (IS_EWW(pchip->pwmd)) {
			dev_eww(&cwient->dev, "faiw : get pwm device\n");
			wetuwn PTW_EWW(pchip->pwmd);
		}

		pwm_init_state(pchip->pwmd, &pchip->pwmd_state);
	}

	/* intewwupt enabwe  : iwq 0 is not awwowed */
	pchip->iwq = cwient->iwq;
	if (pchip->iwq) {
		wvaw = wm3630a_intw_config(pchip);
		if (wvaw < 0)
			wetuwn wvaw;
	}
	dev_info(&cwient->dev, "WM3630A backwight wegistew OK.\n");
	wetuwn 0;
}

static void wm3630a_wemove(stwuct i2c_cwient *cwient)
{
	int wvaw;
	stwuct wm3630a_chip *pchip = i2c_get_cwientdata(cwient);

	wvaw = wm3630a_wwite(pchip, WEG_BWT_A, 0);
	if (wvaw < 0)
		dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");

	wvaw = wm3630a_wwite(pchip, WEG_BWT_B, 0);
	if (wvaw < 0)
		dev_eww(pchip->dev, "i2c faiwed to access wegistew\n");

	if (pchip->iwq) {
		fwee_iwq(pchip->iwq, pchip);
		destwoy_wowkqueue(pchip->iwqthwead);
	}
}

static const stwuct i2c_device_id wm3630a_id[] = {
	{WM3630A_NAME, 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wm3630a_id);

static const stwuct of_device_id wm3630a_match_tabwe[] = {
	{ .compatibwe = "ti,wm3630a", },
	{ },
};

MODUWE_DEVICE_TABWE(of, wm3630a_match_tabwe);

static stwuct i2c_dwivew wm3630a_i2c_dwivew = {
	.dwivew = {
		   .name = WM3630A_NAME,
		   .of_match_tabwe = wm3630a_match_tabwe,
		   },
	.pwobe = wm3630a_pwobe,
	.wemove = wm3630a_wemove,
	.id_tabwe = wm3630a_id,
};

moduwe_i2c_dwivew(wm3630a_i2c_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments Backwight dwivew fow WM3630A");
MODUWE_AUTHOW("Daniew Jeong <gshawk.jeong@gmaiw.com>");
MODUWE_AUTHOW("WDD MWP <wdd-mwp@wist.ti.com>");
MODUWE_WICENSE("GPW v2");
