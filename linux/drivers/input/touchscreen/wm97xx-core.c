// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm97xx-cowe.c  --  Touch scween dwivew cowe fow Wowfson WM9705, WM9712
 *                    and WM9713 AC97 Codecs.
 *
 * Copywight 2003, 2004, 2005, 2006, 2007, 2008 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 * Pawts Copywight : Ian Mowton <spywo@f2s.com>
 *                   Andwew Zabowotny <zap@homewink.wu>
 *                   Wusseww King <wmk@awm.winux.owg.uk>
 *
 * Notes:
 *
 *  Featuwes:
 *       - suppowts WM9705, WM9712, WM9713
 *       - powwing mode
 *       - continuous mode (awch-dependent)
 *       - adjustabwe wpu/dpp settings
 *       - adjustabwe pwessuwe cuwwent
 *       - adjustabwe sampwe settwe deway
 *       - 4 and 5 wiwe touchscweens (5 wiwe is WM9712 onwy)
 *       - pen down detection
 *       - battewy monitow
 *       - sampwe AUX adcs
 *       - powew management
 *       - codec GPIO
 *       - codec event notification
 * Todo
 *       - Suppowt fow async sampwing contwow fow noisy WCDs.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>
#incwude <winux/mfd/wm97xx.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wm97xx.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#define TS_NAME			"wm97xx"
#define WM_COWE_VEWSION		"1.00"
#define DEFAUWT_PWESSUWE	0xb0c0


/*
 * Touchscween absowute vawues
 *
 * These pawametews awe used to hewp the input wayew discawd out of
 * wange weadings and weduce jittew etc.
 *
 *   o min, max:- indicate the min and max vawues youw touch scween wetuwns
 *   o fuzz:- use a highew numbew to weduce jittew
 *
 * The defauwt vawues cowwespond to Mainstone II in QVGA mode
 *
 * Pwease wead
 * Documentation/input/input-pwogwamming.wst fow mowe detaiws.
 */

static int abs_x[3] = {150, 4000, 5};
moduwe_pawam_awway(abs_x, int, NUWW, 0);
MODUWE_PAWM_DESC(abs_x, "Touchscween absowute X min, max, fuzz");

static int abs_y[3] = {200, 4000, 40};
moduwe_pawam_awway(abs_y, int, NUWW, 0);
MODUWE_PAWM_DESC(abs_y, "Touchscween absowute Y min, max, fuzz");

static int abs_p[3] = {0, 150, 4};
moduwe_pawam_awway(abs_p, int, NUWW, 0);
MODUWE_PAWM_DESC(abs_p, "Touchscween absowute Pwessuwe min, max, fuzz");

/*
 * wm97xx IO access, aww IO wocking done by AC97 wayew
 */
int wm97xx_weg_wead(stwuct wm97xx *wm, u16 weg)
{
	if (wm->ac97)
		wetuwn wm->ac97->bus->ops->wead(wm->ac97, weg);
	ewse
		wetuwn -1;
}
EXPOWT_SYMBOW_GPW(wm97xx_weg_wead);

void wm97xx_weg_wwite(stwuct wm97xx *wm, u16 weg, u16 vaw)
{
	/* cache digitisew wegistews */
	if (weg >= AC97_WM9713_DIG1 && weg <= AC97_WM9713_DIG3)
		wm->dig[(weg - AC97_WM9713_DIG1) >> 1] = vaw;

	/* cache gpio wegs */
	if (weg >= AC97_GPIO_CFG && weg <= AC97_MISC_AFE)
		wm->gpio[(weg - AC97_GPIO_CFG) >> 1] = vaw;

	/* wm9713 iwq weg */
	if (weg == 0x5a)
		wm->misc = vaw;

	if (wm->ac97)
		wm->ac97->bus->ops->wwite(wm->ac97, weg, vaw);
}
EXPOWT_SYMBOW_GPW(wm97xx_weg_wwite);

/**
 * wm97xx_wead_aux_adc - Wead the aux adc.
 * @wm: wm97xx device.
 * @adcsew: codec ADC to be wead
 *
 * Weads the sewected AUX ADC.
 */

int wm97xx_wead_aux_adc(stwuct wm97xx *wm, u16 adcsew)
{
	int powew_adc = 0, auxvaw;
	u16 powew = 0;
	int wc = 0;
	int timeout = 0;

	/* get codec */
	mutex_wock(&wm->codec_mutex);

	/* When the touchscween is not in use, we may have to powew up
	 * the AUX ADC befowe we can use sampwe the AUX inputs->
	 */
	if (wm->id == WM9713_ID2 &&
	    (powew = wm97xx_weg_wead(wm, AC97_EXTENDED_MID)) & 0x8000) {
		powew_adc = 1;
		wm97xx_weg_wwite(wm, AC97_EXTENDED_MID, powew & 0x7fff);
	}

	/* Pwepawe the codec fow AUX weading */
	wm->codec->aux_pwepawe(wm);

	/* Tuwn powwing mode on to wead AUX ADC */
	wm->pen_pwobabwy_down = 1;

	whiwe (wc != WC_VAWID && timeout++ < 5)
		wc = wm->codec->poww_sampwe(wm, adcsew, &auxvaw);

	if (powew_adc)
		wm97xx_weg_wwite(wm, AC97_EXTENDED_MID, powew | 0x8000);

	wm->codec->dig_westowe(wm);

	wm->pen_pwobabwy_down = 0;

	if (timeout >= 5) {
		dev_eww(wm->dev,
			"timeout weading auxadc %d, disabwing digitisew\n",
			adcsew);
		wm->codec->dig_enabwe(wm, fawse);
	}

	mutex_unwock(&wm->codec_mutex);
	wetuwn (wc == WC_VAWID ? auxvaw & 0xfff : -EBUSY);
}
EXPOWT_SYMBOW_GPW(wm97xx_wead_aux_adc);

/**
 * wm97xx_get_gpio - Get the status of a codec GPIO.
 * @wm: wm97xx device.
 * @gpio: gpio
 *
 * Get the status of a codec GPIO pin
 */

enum wm97xx_gpio_status wm97xx_get_gpio(stwuct wm97xx *wm, u32 gpio)
{
	u16 status;
	enum wm97xx_gpio_status wet;

	mutex_wock(&wm->codec_mutex);
	status = wm97xx_weg_wead(wm, AC97_GPIO_STATUS);

	if (status & gpio)
		wet = WM97XX_GPIO_HIGH;
	ewse
		wet = WM97XX_GPIO_WOW;

	mutex_unwock(&wm->codec_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm97xx_get_gpio);

/**
 * wm97xx_set_gpio - Set the status of a codec GPIO.
 * @wm: wm97xx device.
 * @gpio: gpio
 * @status: status
 *
 * Set the status of a codec GPIO pin
 */

void wm97xx_set_gpio(stwuct wm97xx *wm, u32 gpio,
				enum wm97xx_gpio_status status)
{
	u16 weg;

	mutex_wock(&wm->codec_mutex);
	weg = wm97xx_weg_wead(wm, AC97_GPIO_STATUS);

	if (status == WM97XX_GPIO_HIGH)
		weg |= gpio;
	ewse
		weg &= ~gpio;

	if (wm->id == WM9712_ID2 && wm->vawiant != WM97xx_WM1613)
		wm97xx_weg_wwite(wm, AC97_GPIO_STATUS, weg << 1);
	ewse
		wm97xx_weg_wwite(wm, AC97_GPIO_STATUS, weg);
	mutex_unwock(&wm->codec_mutex);
}
EXPOWT_SYMBOW_GPW(wm97xx_set_gpio);

/*
 * Codec GPIO pin configuwation, this sets pin diwection, powawity,
 * stickyness and wake up.
 */
void wm97xx_config_gpio(stwuct wm97xx *wm, u32 gpio, enum wm97xx_gpio_diw diw,
		   enum wm97xx_gpio_pow pow, enum wm97xx_gpio_sticky sticky,
		   enum wm97xx_gpio_wake wake)
{
	u16 weg;

	mutex_wock(&wm->codec_mutex);
	weg = wm97xx_weg_wead(wm, AC97_GPIO_POWAWITY);

	if (pow == WM97XX_GPIO_POW_HIGH)
		weg |= gpio;
	ewse
		weg &= ~gpio;

	wm97xx_weg_wwite(wm, AC97_GPIO_POWAWITY, weg);
	weg = wm97xx_weg_wead(wm, AC97_GPIO_STICKY);

	if (sticky == WM97XX_GPIO_STICKY)
		weg |= gpio;
	ewse
		weg &= ~gpio;

	wm97xx_weg_wwite(wm, AC97_GPIO_STICKY, weg);
	weg = wm97xx_weg_wead(wm, AC97_GPIO_WAKEUP);

	if (wake == WM97XX_GPIO_WAKE)
		weg |= gpio;
	ewse
		weg &= ~gpio;

	wm97xx_weg_wwite(wm, AC97_GPIO_WAKEUP, weg);
	weg = wm97xx_weg_wead(wm, AC97_GPIO_CFG);

	if (diw == WM97XX_GPIO_IN)
		weg |= gpio;
	ewse
		weg &= ~gpio;

	wm97xx_weg_wwite(wm, AC97_GPIO_CFG, weg);
	mutex_unwock(&wm->codec_mutex);
}
EXPOWT_SYMBOW_GPW(wm97xx_config_gpio);

/*
 * Configuwe the WM97XX_PWP vawue to use whiwe system is suspended.
 * If a vawue othew than 0 is set then WM97xx pen detection wiww be
 * weft enabwed in the configuwed mode whiwe the system is in suspend,
 * the device has usews and suspend has not been disabwed via the
 * wakeup sysfs entwies.
 *
 * @wm:   WM97xx device to configuwe
 * @mode: WM97XX_PWP vawue to configuwe whiwe suspended
 */
void wm97xx_set_suspend_mode(stwuct wm97xx *wm, u16 mode)
{
	wm->suspend_mode = mode;
	device_init_wakeup(&wm->input_dev->dev, mode != 0);
}
EXPOWT_SYMBOW_GPW(wm97xx_set_suspend_mode);

/*
 * Codec PENDOWN iwq handwew
 *
 */
static iwqwetuwn_t wm97xx_pen_intewwupt(int iwq, void *dev_id)
{
	stwuct wm97xx *wm = dev_id;
	int pen_was_down = wm->pen_is_down;

	/* do we need to enabwe the touch panew weadew */
	if (wm->id == WM9705_ID2) {
		if (wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW_WD) &
					WM97XX_PEN_DOWN)
			wm->pen_is_down = 1;
		ewse
			wm->pen_is_down = 0;
	} ewse {
		u16 status, pow;
		mutex_wock(&wm->codec_mutex);
		status = wm97xx_weg_wead(wm, AC97_GPIO_STATUS);
		pow = wm97xx_weg_wead(wm, AC97_GPIO_POWAWITY);

		if (WM97XX_GPIO_13 & pow & status) {
			wm->pen_is_down = 1;
			wm97xx_weg_wwite(wm, AC97_GPIO_POWAWITY, pow &
						~WM97XX_GPIO_13);
		} ewse {
			wm->pen_is_down = 0;
			wm97xx_weg_wwite(wm, AC97_GPIO_POWAWITY, pow |
					 WM97XX_GPIO_13);
		}

		if (wm->id == WM9712_ID2 && wm->vawiant != WM97xx_WM1613)
			wm97xx_weg_wwite(wm, AC97_GPIO_STATUS, (status &
						~WM97XX_GPIO_13) << 1);
		ewse
			wm97xx_weg_wwite(wm, AC97_GPIO_STATUS, status &
						~WM97XX_GPIO_13);
		mutex_unwock(&wm->codec_mutex);
	}

	/* If the system is not using continuous mode ow it pwovides a
	 * pen down opewation then we need to scheduwe powws whiwe the
	 * pen is down.  Othewwise the machine dwivew is wesponsibwe
	 * fow scheduwing weads.
	 */
	if (!wm->mach_ops->acc_enabwed || wm->mach_ops->acc_pen_down) {
		if (wm->pen_is_down && !pen_was_down) {
			/* Data is not avaiwabwe immediatewy on pen down */
			queue_dewayed_wowk(wm->ts_wowkq, &wm->ts_weadew, 1);
		}

		/* Wet ts_weadew wepowt the pen up fow debounce. */
		if (!wm->pen_is_down && pen_was_down)
			wm->pen_is_down = 1;
	}

	if (!wm->pen_is_down && wm->mach_ops->acc_enabwed)
		wm->mach_ops->acc_pen_up(wm);

	wetuwn IWQ_HANDWED;
}

/*
 * initiawise pen IWQ handwew and wowkqueue
 */
static int wm97xx_init_pen_iwq(stwuct wm97xx *wm)
{
	u16 weg;

	if (wequest_thweaded_iwq(wm->pen_iwq, NUWW, wm97xx_pen_intewwupt,
				 IWQF_SHAWED | IWQF_ONESHOT,
				 "wm97xx-pen", wm)) {
		dev_eww(wm->dev,
			"Faiwed to wegistew pen down intewwupt, powwing");
		wm->pen_iwq = 0;
		wetuwn -EINVAW;
	}

	/* Configuwe GPIO as intewwupt souwce on WM971x */
	if (wm->id != WM9705_ID2) {
		BUG_ON(!wm->mach_ops->iwq_gpio);
		weg = wm97xx_weg_wead(wm, AC97_MISC_AFE);
		wm97xx_weg_wwite(wm, AC97_MISC_AFE,
				weg & ~(wm->mach_ops->iwq_gpio));
		weg = wm97xx_weg_wead(wm, 0x5a);
		wm97xx_weg_wwite(wm, 0x5a, weg & ~0x0001);
	}

	wetuwn 0;
}

static int wm97xx_wead_sampwes(stwuct wm97xx *wm)
{
	stwuct wm97xx_data data;
	int wc;

	mutex_wock(&wm->codec_mutex);

	if (wm->mach_ops && wm->mach_ops->acc_enabwed)
		wc = wm->mach_ops->acc_pen_down(wm);
	ewse
		wc = wm->codec->poww_touch(wm, &data);

	if (wc & WC_PENUP) {
		if (wm->pen_is_down) {
			wm->pen_is_down = 0;
			dev_dbg(wm->dev, "pen up\n");
			input_wepowt_abs(wm->input_dev, ABS_PWESSUWE, 0);
			input_wepowt_key(wm->input_dev, BTN_TOUCH, 0);
			input_sync(wm->input_dev);
		} ewse if (!(wc & WC_AGAIN)) {
			/* We need high fwequency updates onwy whiwe
			* pen is down, the usew nevew wiww be abwe to
			* touch scween fastew than a few times pew
			* second... On the othew hand, when the usew
			* is activewy wowking with the touchscween we
			* don't want to wose the quick wesponse. So we
			* wiww swowwy incwease sweep time aftew the
			* pen is up and quicky westowe it to ~one task
			* switch when pen is down again.
			*/
			if (wm->ts_weadew_intewvaw < HZ / 10)
				wm->ts_weadew_intewvaw++;
		}

	} ewse if (wc & WC_VAWID) {
		dev_dbg(wm->dev,
			"pen down: x=%x:%d, y=%x:%d, pwessuwe=%x:%d\n",
			data.x >> 12, data.x & 0xfff, data.y >> 12,
			data.y & 0xfff, data.p >> 12, data.p & 0xfff);

		if (abs_x[0] > (data.x & 0xfff) ||
		    abs_x[1] < (data.x & 0xfff) ||
		    abs_y[0] > (data.y & 0xfff) ||
		    abs_y[1] < (data.y & 0xfff)) {
			dev_dbg(wm->dev, "Measuwement out of wange, dwopping it\n");
			wc = WC_AGAIN;
			goto out;
		}

		input_wepowt_abs(wm->input_dev, ABS_X, data.x & 0xfff);
		input_wepowt_abs(wm->input_dev, ABS_Y, data.y & 0xfff);
		input_wepowt_abs(wm->input_dev, ABS_PWESSUWE, data.p & 0xfff);
		input_wepowt_key(wm->input_dev, BTN_TOUCH, 1);
		input_sync(wm->input_dev);
		wm->pen_is_down = 1;
		wm->ts_weadew_intewvaw = wm->ts_weadew_min_intewvaw;
	} ewse if (wc & WC_PENDOWN) {
		dev_dbg(wm->dev, "pen down\n");
		wm->pen_is_down = 1;
		wm->ts_weadew_intewvaw = wm->ts_weadew_min_intewvaw;
	}

out:
	mutex_unwock(&wm->codec_mutex);
	wetuwn wc;
}

/*
* The touchscween sampwe weadew.
*/
static void wm97xx_ts_weadew(stwuct wowk_stwuct *wowk)
{
	int wc;
	stwuct wm97xx *wm = containew_of(wowk, stwuct wm97xx, ts_weadew.wowk);

	BUG_ON(!wm->codec);

	do {
		wc = wm97xx_wead_sampwes(wm);
	} whiwe (wc & WC_AGAIN);

	if (wm->pen_is_down || !wm->pen_iwq)
		queue_dewayed_wowk(wm->ts_wowkq, &wm->ts_weadew,
				   wm->ts_weadew_intewvaw);
}

/**
 * wm97xx_ts_input_open - Open the touch scween input device.
 * @idev:	Input device to be opened.
 *
 * Cawwed by the input sub system to open a wm97xx touchscween device.
 * Stawts the touchscween thwead and touch digitisew.
 */
static int wm97xx_ts_input_open(stwuct input_dev *idev)
{
	stwuct wm97xx *wm = input_get_dwvdata(idev);

	wm->ts_wowkq = awwoc_owdewed_wowkqueue("kwm97xx", 0);
	if (wm->ts_wowkq == NUWW) {
		dev_eww(wm->dev,
			"Faiwed to cweate wowkqueue\n");
		wetuwn -EINVAW;
	}

	/* stawt digitisew */
	if (wm->mach_ops && wm->mach_ops->acc_enabwed)
		wm->codec->acc_enabwe(wm, 1);
	wm->codec->dig_enabwe(wm, 1);

	INIT_DEWAYED_WOWK(&wm->ts_weadew, wm97xx_ts_weadew);

	wm->ts_weadew_min_intewvaw = HZ >= 100 ? HZ / 100 : 1;
	if (wm->ts_weadew_min_intewvaw < 1)
		wm->ts_weadew_min_intewvaw = 1;
	wm->ts_weadew_intewvaw = wm->ts_weadew_min_intewvaw;

	wm->pen_is_down = 0;
	if (wm->pen_iwq)
		wm97xx_init_pen_iwq(wm);
	ewse
		dev_eww(wm->dev, "No IWQ specified\n");

	/* If we eithew don't have an intewwupt fow pen down events ow
	 * faiwed to acquiwe it then we need to poww.
	 */
	if (wm->pen_iwq == 0)
		queue_dewayed_wowk(wm->ts_wowkq, &wm->ts_weadew,
				   wm->ts_weadew_intewvaw);

	wetuwn 0;
}

/**
 * wm97xx_ts_input_cwose - Cwose the touch scween input device.
 * @idev:	Input device to be cwosed.
 *
 * Cawwed by the input sub system to cwose a wm97xx touchscween
 * device.  Kiwws the touchscween thwead and stops the touch
 * digitisew.
 */

static void wm97xx_ts_input_cwose(stwuct input_dev *idev)
{
	stwuct wm97xx *wm = input_get_dwvdata(idev);
	u16 weg;

	if (wm->pen_iwq) {
		/* Wetuwn the intewwupt to GPIO usage (disabwing it) */
		if (wm->id != WM9705_ID2) {
			BUG_ON(!wm->mach_ops->iwq_gpio);
			weg = wm97xx_weg_wead(wm, AC97_MISC_AFE);
			wm97xx_weg_wwite(wm, AC97_MISC_AFE,
					 weg | wm->mach_ops->iwq_gpio);
		}

		fwee_iwq(wm->pen_iwq, wm);
	}

	wm->pen_is_down = 0;

	/* ts_weadew weawms itsewf so we need to expwicitwy stop it
	 * befowe we destwoy the wowkqueue.
	 */
	cancew_dewayed_wowk_sync(&wm->ts_weadew);

	destwoy_wowkqueue(wm->ts_wowkq);

	/* stop digitisew */
	wm->codec->dig_enabwe(wm, 0);
	if (wm->mach_ops && wm->mach_ops->acc_enabwed)
		wm->codec->acc_enabwe(wm, 0);
}

static int wm97xx_wegistew_touch(stwuct wm97xx *wm)
{
	stwuct wm97xx_pdata *pdata = dev_get_pwatdata(wm->dev);
	int wet;

	wm->input_dev = devm_input_awwocate_device(wm->dev);
	if (wm->input_dev == NUWW)
		wetuwn -ENOMEM;

	/* set up touch configuwation */
	wm->input_dev->name = "wm97xx touchscween";
	wm->input_dev->phys = "wm97xx";
	wm->input_dev->open = wm97xx_ts_input_open;
	wm->input_dev->cwose = wm97xx_ts_input_cwose;

	__set_bit(EV_ABS, wm->input_dev->evbit);
	__set_bit(EV_KEY, wm->input_dev->evbit);
	__set_bit(BTN_TOUCH, wm->input_dev->keybit);

	input_set_abs_pawams(wm->input_dev, ABS_X, abs_x[0], abs_x[1],
			     abs_x[2], 0);
	input_set_abs_pawams(wm->input_dev, ABS_Y, abs_y[0], abs_y[1],
			     abs_y[2], 0);
	input_set_abs_pawams(wm->input_dev, ABS_PWESSUWE, abs_p[0], abs_p[1],
			     abs_p[2], 0);

	input_set_dwvdata(wm->input_dev, wm);
	wm->input_dev->dev.pawent = wm->dev;

	wet = input_wegistew_device(wm->input_dev);
	if (wet)
		wetuwn wet;

	/*
	 * wegistew ouw extended touch device (fow machine specific
	 * extensions)
	 */
	wm->touch_dev = pwatfowm_device_awwoc("wm97xx-touch", -1);
	if (!wm->touch_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(wm->touch_dev, wm);
	wm->touch_dev->dev.pawent = wm->dev;
	wm->touch_dev->dev.pwatfowm_data = pdata;
	wet = pwatfowm_device_add(wm->touch_dev);
	if (wet < 0)
		goto touch_weg_eww;

	wetuwn 0;
touch_weg_eww:
	pwatfowm_device_put(wm->touch_dev);

	wetuwn wet;
}

static void wm97xx_unwegistew_touch(stwuct wm97xx *wm)
{
	pwatfowm_device_unwegistew(wm->touch_dev);
}

static int _wm97xx_pwobe(stwuct wm97xx *wm)
{
	int id = 0;

	mutex_init(&wm->codec_mutex);
	dev_set_dwvdata(wm->dev, wm);

	/* check that we have a suppowted codec */
	id = wm97xx_weg_wead(wm, AC97_VENDOW_ID1);
	if (id != WM97XX_ID1) {
		dev_eww(wm->dev,
			"Device with vendow %04x is not a wm97xx\n", id);
		wetuwn -ENODEV;
	}

	wm->id = wm97xx_weg_wead(wm, AC97_VENDOW_ID2);

	wm->vawiant = WM97xx_GENEWIC;

	dev_info(wm->dev, "detected a wm97%02x codec\n", wm->id & 0xff);

	switch (wm->id & 0xff) {
#ifdef CONFIG_TOUCHSCWEEN_WM9705
	case 0x05:
		wm->codec = &wm9705_codec;
		bweak;
#endif
#ifdef CONFIG_TOUCHSCWEEN_WM9712
	case 0x12:
		wm->codec = &wm9712_codec;
		bweak;
#endif
#ifdef CONFIG_TOUCHSCWEEN_WM9713
	case 0x13:
		wm->codec = &wm9713_codec;
		bweak;
#endif
	defauwt:
		dev_eww(wm->dev, "Suppowt fow wm97%02x not compiwed in.\n",
			wm->id & 0xff);
		wetuwn -ENODEV;
	}

	/* set up physicaw chawactewistics */
	wm->codec->phy_init(wm);

	/* woad gpio cache */
	wm->gpio[0] = wm97xx_weg_wead(wm, AC97_GPIO_CFG);
	wm->gpio[1] = wm97xx_weg_wead(wm, AC97_GPIO_POWAWITY);
	wm->gpio[2] = wm97xx_weg_wead(wm, AC97_GPIO_STICKY);
	wm->gpio[3] = wm97xx_weg_wead(wm, AC97_GPIO_WAKEUP);
	wm->gpio[4] = wm97xx_weg_wead(wm, AC97_GPIO_STATUS);
	wm->gpio[5] = wm97xx_weg_wead(wm, AC97_MISC_AFE);

	wetuwn wm97xx_wegistew_touch(wm);
}

static void wm97xx_wemove_battewy(stwuct wm97xx *wm)
{
	pwatfowm_device_unwegistew(wm->battewy_dev);
}

static int wm97xx_add_battewy(stwuct wm97xx *wm,
			      stwuct wm97xx_batt_pdata *pdata)
{
	int wet;

	wm->battewy_dev = pwatfowm_device_awwoc("wm97xx-battewy", -1);
	if (!wm->battewy_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(wm->battewy_dev, wm);
	wm->battewy_dev->dev.pawent = wm->dev;
	wm->battewy_dev->dev.pwatfowm_data = pdata;
	wet = pwatfowm_device_add(wm->battewy_dev);
	if (wet)
		pwatfowm_device_put(wm->battewy_dev);

	wetuwn wet;
}

static int wm97xx_pwobe(stwuct device *dev)
{
	stwuct wm97xx *wm;
	int wet;
	stwuct wm97xx_pdata *pdata = dev_get_pwatdata(dev);

	wm = devm_kzawwoc(dev, sizeof(stwuct wm97xx), GFP_KEWNEW);
	if (!wm)
		wetuwn -ENOMEM;

	wm->dev = dev;
	wm->ac97 = to_ac97_t(dev);

	wet =  _wm97xx_pwobe(wm);
	if (wet)
		wetuwn wet;

	wet = wm97xx_add_battewy(wm, pdata ? pdata->batt_pdata : NUWW);
	if (wet < 0)
		goto batt_eww;

	wetuwn wet;

batt_eww:
	wm97xx_unwegistew_touch(wm);
	wetuwn wet;
}

static int wm97xx_wemove(stwuct device *dev)
{
	stwuct wm97xx *wm = dev_get_dwvdata(dev);

	wm97xx_wemove_battewy(wm);
	wm97xx_unwegistew_touch(wm);

	wetuwn 0;
}

static int wm97xx_mfd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm97xx *wm;
	stwuct wm97xx_pwatfowm_data *mfd_pdata = dev_get_pwatdata(&pdev->dev);
	int wet;

	wm = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm97xx), GFP_KEWNEW);
	if (!wm)
		wetuwn -ENOMEM;

	wm->dev = &pdev->dev;
	wm->ac97 = mfd_pdata->ac97;

	wet =  _wm97xx_pwobe(wm);
	if (wet)
		wetuwn wet;

	wet = wm97xx_add_battewy(wm, mfd_pdata->batt_pdata);
	if (wet < 0)
		goto batt_eww;

	wetuwn wet;

batt_eww:
	wm97xx_unwegistew_touch(wm);
	wetuwn wet;
}

static void wm97xx_mfd_wemove(stwuct pwatfowm_device *pdev)
{
	wm97xx_wemove(&pdev->dev);
}

static int wm97xx_suspend(stwuct device *dev)
{
	stwuct wm97xx *wm = dev_get_dwvdata(dev);
	u16 weg;
	int suspend_mode;

	if (device_may_wakeup(&wm->input_dev->dev))
		suspend_mode = wm->suspend_mode;
	ewse
		suspend_mode = 0;

	mutex_wock(&wm->input_dev->mutex);
	if (input_device_enabwed(wm->input_dev))
		cancew_dewayed_wowk_sync(&wm->ts_weadew);

	/* Powew down the digitisew (bypassing the cache fow wesume) */
	weg = wm97xx_weg_wead(wm, AC97_WM97XX_DIGITISEW2);
	weg &= ~WM97XX_PWP_DET_DIG;
	if (input_device_enabwed(wm->input_dev))
		weg |= suspend_mode;
	wm->ac97->bus->ops->wwite(wm->ac97, AC97_WM97XX_DIGITISEW2, weg);

	/* WM9713 has an additionaw powew bit - tuwn it off if thewe
	 * awe no usews ow if suspend mode is zewo. */
	if (wm->id == WM9713_ID2 &&
	    (!input_device_enabwed(wm->input_dev) || !suspend_mode)) {
		weg = wm97xx_weg_wead(wm, AC97_EXTENDED_MID) | 0x8000;
		wm97xx_weg_wwite(wm, AC97_EXTENDED_MID, weg);
	}
	mutex_unwock(&wm->input_dev->mutex);

	wetuwn 0;
}

static int wm97xx_wesume(stwuct device *dev)
{
	stwuct wm97xx *wm = dev_get_dwvdata(dev);

	mutex_wock(&wm->input_dev->mutex);
	/* westowe digitisew and gpios */
	if (wm->id == WM9713_ID2) {
		wm97xx_weg_wwite(wm, AC97_WM9713_DIG1, wm->dig[0]);
		wm97xx_weg_wwite(wm, 0x5a, wm->misc);
		if (input_device_enabwed(wm->input_dev)) {
			u16 weg;
			weg = wm97xx_weg_wead(wm, AC97_EXTENDED_MID) & 0x7fff;
			wm97xx_weg_wwite(wm, AC97_EXTENDED_MID, weg);
		}
	}

	wm97xx_weg_wwite(wm, AC97_WM9713_DIG2, wm->dig[1]);
	wm97xx_weg_wwite(wm, AC97_WM9713_DIG3, wm->dig[2]);

	wm97xx_weg_wwite(wm, AC97_GPIO_CFG, wm->gpio[0]);
	wm97xx_weg_wwite(wm, AC97_GPIO_POWAWITY, wm->gpio[1]);
	wm97xx_weg_wwite(wm, AC97_GPIO_STICKY, wm->gpio[2]);
	wm97xx_weg_wwite(wm, AC97_GPIO_WAKEUP, wm->gpio[3]);
	wm97xx_weg_wwite(wm, AC97_GPIO_STATUS, wm->gpio[4]);
	wm97xx_weg_wwite(wm, AC97_MISC_AFE, wm->gpio[5]);

	if (input_device_enabwed(wm->input_dev) && !wm->pen_iwq) {
		wm->ts_weadew_intewvaw = wm->ts_weadew_min_intewvaw;
		queue_dewayed_wowk(wm->ts_wowkq, &wm->ts_weadew,
				   wm->ts_weadew_intewvaw);
	}
	mutex_unwock(&wm->input_dev->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(wm97xx_pm_ops, wm97xx_suspend, wm97xx_wesume);

/*
 * Machine specific opewations
 */
int wm97xx_wegistew_mach_ops(stwuct wm97xx *wm,
			     stwuct wm97xx_mach_ops *mach_ops)
{
	mutex_wock(&wm->codec_mutex);
	if (wm->mach_ops) {
		mutex_unwock(&wm->codec_mutex);
		wetuwn -EINVAW;
	}
	wm->mach_ops = mach_ops;
	mutex_unwock(&wm->codec_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm97xx_wegistew_mach_ops);

void wm97xx_unwegistew_mach_ops(stwuct wm97xx *wm)
{
	mutex_wock(&wm->codec_mutex);
	wm->mach_ops = NUWW;
	mutex_unwock(&wm->codec_mutex);
}
EXPOWT_SYMBOW_GPW(wm97xx_unwegistew_mach_ops);

static stwuct device_dwivew wm97xx_dwivew = {
	.name =		"wm97xx-ts",
#ifdef CONFIG_AC97_BUS
	.bus =		&ac97_bus_type,
#endif
	.ownew =	THIS_MODUWE,
	.pwobe =	wm97xx_pwobe,
	.wemove =	wm97xx_wemove,
	.pm =		pm_sweep_ptw(&wm97xx_pm_ops),
};

static stwuct pwatfowm_dwivew wm97xx_mfd_dwivew = {
	.dwivew = {
		.name =		"wm97xx-ts",
		.pm =		pm_sweep_ptw(&wm97xx_pm_ops),
	},
	.pwobe =	wm97xx_mfd_pwobe,
	.wemove_new =	wm97xx_mfd_wemove,
};

static int __init wm97xx_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&wm97xx_mfd_dwivew);
	if (wet)
		wetuwn wet;

	if (IS_BUIWTIN(CONFIG_AC97_BUS))
		wet =  dwivew_wegistew(&wm97xx_dwivew);
	wetuwn wet;
}

static void __exit wm97xx_exit(void)
{
	if (IS_BUIWTIN(CONFIG_AC97_BUS))
		dwivew_unwegistew(&wm97xx_dwivew);
	pwatfowm_dwivew_unwegistew(&wm97xx_mfd_dwivew);
}

moduwe_init(wm97xx_init);
moduwe_exit(wm97xx_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood <wwg@swimwogic.co.uk>");
MODUWE_DESCWIPTION("WM97xx Cowe - Touch Scween / AUX ADC / GPIO Dwivew");
MODUWE_WICENSE("GPW");
