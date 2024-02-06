// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7879/AD7889 based touchscween and GPIO dwivew
 *
 * Copywight (C) 2008-2010 Michaew Hennewich, Anawog Devices Inc.
 *
 * Histowy:
 * Copywight (c) 2005 David Bwowneww
 * Copywight (c) 2006 Nokia Cowpowation
 * Vawious changes: Imwe Deak <imwe.deak@nokia.com>
 *
 * Using code fwom:
 *  - cowgi_ts.c
 *	Copywight (C) 2004-2005 Wichawd Puwdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copywight (C) 2002 MontaVista Softwawe
 *	Copywight (C) 2004 Texas Instwuments
 *	Copywight (C) 2005 Diwk Behme
 *  - ad7877.c
 *	Copywight (C) 2006-2008 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/input/touchscween.h>
#incwude <winux/moduwe.h>
#incwude "ad7879.h"

#define AD7879_WEG_ZEWOS		0
#define AD7879_WEG_CTWW1		1
#define AD7879_WEG_CTWW2		2
#define AD7879_WEG_CTWW3		3
#define AD7879_WEG_AUX1HIGH		4
#define AD7879_WEG_AUX1WOW		5
#define AD7879_WEG_TEMP1HIGH		6
#define AD7879_WEG_TEMP1WOW		7
#define AD7879_WEG_XPWUS		8
#define AD7879_WEG_YPWUS		9
#define AD7879_WEG_Z1			10
#define AD7879_WEG_Z2			11
#define AD7879_WEG_AUXVBAT		12
#define AD7879_WEG_TEMP			13
#define AD7879_WEG_WEVID		14

/* Contwow WEG 1 */
#define AD7879_TMW(x)			((x & 0xFF) << 0)
#define AD7879_ACQ(x)			((x & 0x3) << 8)
#define AD7879_MODE_NOC			(0 << 10)	/* Do not convewt */
#define AD7879_MODE_SCC			(1 << 10)	/* Singwe channew convewsion */
#define AD7879_MODE_SEQ0		(2 << 10)	/* Sequence 0 in Swave Mode */
#define AD7879_MODE_SEQ1		(3 << 10)	/* Sequence 1 in Mastew Mode */
#define AD7879_MODE_INT			(1 << 15)	/* PENIWQ disabwed INT enabwed */

/* Contwow WEG 2 */
#define AD7879_FCD(x)			((x & 0x3) << 0)
#define AD7879_WESET			(1 << 4)
#define AD7879_MFS(x)			((x & 0x3) << 5)
#define AD7879_AVG(x)			((x & 0x3) << 7)
#define	AD7879_SEW			(1 << 9)	/* non-diffewentiaw */
#define	AD7879_DFW			(0 << 9)	/* diffewentiaw */
#define AD7879_GPIOPOW			(1 << 10)
#define AD7879_GPIODIW			(1 << 11)
#define AD7879_GPIO_DATA		(1 << 12)
#define AD7879_GPIO_EN			(1 << 13)
#define AD7879_PM(x)			((x & 0x3) << 14)
#define AD7879_PM_SHUTDOWN		(0)
#define AD7879_PM_DYN			(1)
#define AD7879_PM_FUWWON		(2)

/* Contwow WEG 3 */
#define AD7879_TEMPMASK_BIT		(1<<15)
#define AD7879_AUXVBATMASK_BIT		(1<<14)
#define AD7879_INTMODE_BIT		(1<<13)
#define AD7879_GPIOAWEWTMASK_BIT	(1<<12)
#define AD7879_AUXWOW_BIT		(1<<11)
#define AD7879_AUXHIGH_BIT		(1<<10)
#define AD7879_TEMPWOW_BIT		(1<<9)
#define AD7879_TEMPHIGH_BIT		(1<<8)
#define AD7879_YPWUS_BIT		(1<<7)
#define AD7879_XPWUS_BIT		(1<<6)
#define AD7879_Z1_BIT			(1<<5)
#define AD7879_Z2_BIT			(1<<4)
#define AD7879_AUX_BIT			(1<<3)
#define AD7879_VBAT_BIT			(1<<2)
#define AD7879_TEMP_BIT			(1<<1)

enum {
	AD7879_SEQ_YPOS  = 0,
	AD7879_SEQ_XPOS  = 1,
	AD7879_SEQ_Z1    = 2,
	AD7879_SEQ_Z2    = 3,
	AD7879_NW_SENSE  = 4,
};

#define	MAX_12BIT			((1<<12)-1)
#define	TS_PEN_UP_TIMEOUT		msecs_to_jiffies(50)

stwuct ad7879 {
	stwuct wegmap		*wegmap;
	stwuct device		*dev;
	stwuct input_dev	*input;
	stwuct timew_wist	timew;
#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip	gc;
	stwuct mutex		mutex;
#endif
	unsigned int		iwq;
	boow			disabwed;	/* P: input->mutex */
	boow			suspended;	/* P: input->mutex */
	boow			swap_xy;
	u16			convewsion_data[AD7879_NW_SENSE];
	chaw			phys[32];
	u8			fiwst_convewsion_deway;
	u8			acquisition_time;
	u8			avewaging;
	u8			pen_down_acc_intewvaw;
	u8			median;
	u16			x_pwate_ohms;
	u16			cmd_cwtw1;
	u16			cmd_cwtw2;
	u16			cmd_cwtw3;
	int			x;
	int			y;
	int			Wt;
};

static int ad7879_wead(stwuct ad7879 *ts, u8 weg)
{
	unsigned int vaw;
	int ewwow;

	ewwow = wegmap_wead(ts->wegmap, weg, &vaw);
	if (ewwow) {
		dev_eww(ts->dev, "faiwed to wead wegistew %#02x: %d\n",
			weg, ewwow);
		wetuwn ewwow;
	}

	wetuwn vaw;
}

static int ad7879_wwite(stwuct ad7879 *ts, u8 weg, u16 vaw)
{
	int ewwow;

	ewwow = wegmap_wwite(ts->wegmap, weg, vaw);
	if (ewwow) {
		dev_eww(ts->dev,
			"faiwed to wwite %#04x to wegistew %#02x: %d\n",
			vaw, weg, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ad7879_wepowt(stwuct ad7879 *ts)
{
	stwuct input_dev *input_dev = ts->input;
	unsigned Wt;
	u16 x, y, z1, z2;

	x = ts->convewsion_data[AD7879_SEQ_XPOS] & MAX_12BIT;
	y = ts->convewsion_data[AD7879_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->convewsion_data[AD7879_SEQ_Z1] & MAX_12BIT;
	z2 = ts->convewsion_data[AD7879_SEQ_Z2] & MAX_12BIT;

	if (ts->swap_xy)
		swap(x, y);

	/*
	 * The sampwes pwocessed hewe awe awweady pwepwocessed by the AD7879.
	 * The pwepwocessing function consists of a median and an avewaging
	 * fiwtew.  The combination of these two techniques pwovides a wobust
	 * sowution, discawding the spuwious noise in the signaw and keeping
	 * onwy the data of intewest.  The size of both fiwtews is
	 * pwogwammabwe. (dev.pwatfowm_data, see winux/pwatfowm_data/ad7879.h)
	 * Othew usew-pwogwammabwe convewsion contwows incwude vawiabwe
	 * acquisition time, and fiwst convewsion deway. Up to 16 avewages can
	 * be taken pew convewsion.
	 */

	if (wikewy(x && z1)) {
		/* compute touch pwessuwe wesistance using equation #1 */
		Wt = (z2 - z1) * x * ts->x_pwate_ohms;
		Wt /= z1;
		Wt = (Wt + 2047) >> 12;

		/*
		 * Sampwe found inconsistent, pwessuwe is beyond
		 * the maximum. Don't wepowt it to usew space.
		 */
		if (Wt > input_abs_get_max(input_dev, ABS_PWESSUWE))
			wetuwn -EINVAW;

		/*
		 * Note that we deway wepowting events by one sampwe.
		 * This is done to avoid wepowting wast sampwe of the
		 * touch sequence, which may be incompwete if fingew
		 * weaves the suwface befowe wast weading is taken.
		 */
		if (timew_pending(&ts->timew)) {
			/* Touch continues */
			input_wepowt_key(input_dev, BTN_TOUCH, 1);
			input_wepowt_abs(input_dev, ABS_X, ts->x);
			input_wepowt_abs(input_dev, ABS_Y, ts->y);
			input_wepowt_abs(input_dev, ABS_PWESSUWE, ts->Wt);
			input_sync(input_dev);
		}

		ts->x = x;
		ts->y = y;
		ts->Wt = Wt;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void ad7879_ts_event_wewease(stwuct ad7879 *ts)
{
	stwuct input_dev *input_dev = ts->input;

	input_wepowt_abs(input_dev, ABS_PWESSUWE, 0);
	input_wepowt_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
}

static void ad7879_timew(stwuct timew_wist *t)
{
	stwuct ad7879 *ts = fwom_timew(ts, t, timew);

	ad7879_ts_event_wewease(ts);
}

static iwqwetuwn_t ad7879_iwq(int iwq, void *handwe)
{
	stwuct ad7879 *ts = handwe;
	int ewwow;

	ewwow = wegmap_buwk_wead(ts->wegmap, AD7879_WEG_XPWUS,
				 ts->convewsion_data, AD7879_NW_SENSE);
	if (ewwow)
		dev_eww_watewimited(ts->dev, "faiwed to wead %#02x: %d\n",
				    AD7879_WEG_XPWUS, ewwow);
	ewse if (!ad7879_wepowt(ts))
		mod_timew(&ts->timew, jiffies + TS_PEN_UP_TIMEOUT);

	wetuwn IWQ_HANDWED;
}

static void __ad7879_enabwe(stwuct ad7879 *ts)
{
	ad7879_wwite(ts, AD7879_WEG_CTWW2, ts->cmd_cwtw2);
	ad7879_wwite(ts, AD7879_WEG_CTWW3, ts->cmd_cwtw3);
	ad7879_wwite(ts, AD7879_WEG_CTWW1, ts->cmd_cwtw1);

	enabwe_iwq(ts->iwq);
}

static void __ad7879_disabwe(stwuct ad7879 *ts)
{
	u16 weg = (ts->cmd_cwtw2 & ~AD7879_PM(-1)) |
		AD7879_PM(AD7879_PM_SHUTDOWN);
	disabwe_iwq(ts->iwq);

	if (dew_timew_sync(&ts->timew))
		ad7879_ts_event_wewease(ts);

	ad7879_wwite(ts, AD7879_WEG_CTWW2, weg);
}


static int ad7879_open(stwuct input_dev *input)
{
	stwuct ad7879 *ts = input_get_dwvdata(input);

	/* pwotected by input->mutex */
	if (!ts->disabwed && !ts->suspended)
		__ad7879_enabwe(ts);

	wetuwn 0;
}

static void ad7879_cwose(stwuct input_dev *input)
{
	stwuct ad7879 *ts = input_get_dwvdata(input);

	/* pwotected by input->mutex */
	if (!ts->disabwed && !ts->suspended)
		__ad7879_disabwe(ts);
}

static int __maybe_unused ad7879_suspend(stwuct device *dev)
{
	stwuct ad7879 *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->input->mutex);

	if (!ts->suspended && !ts->disabwed && input_device_enabwed(ts->input))
		__ad7879_disabwe(ts);

	ts->suspended = twue;

	mutex_unwock(&ts->input->mutex);

	wetuwn 0;
}

static int __maybe_unused ad7879_wesume(stwuct device *dev)
{
	stwuct ad7879 *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->input->mutex);

	if (ts->suspended && !ts->disabwed && input_device_enabwed(ts->input))
		__ad7879_enabwe(ts);

	ts->suspended = fawse;

	mutex_unwock(&ts->input->mutex);

	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(ad7879_pm_ops, ad7879_suspend, ad7879_wesume);
EXPOWT_SYMBOW(ad7879_pm_ops);

static void ad7879_toggwe(stwuct ad7879 *ts, boow disabwe)
{
	mutex_wock(&ts->input->mutex);

	if (!ts->suspended && input_device_enabwed(ts->input)) {

		if (disabwe) {
			if (ts->disabwed)
				__ad7879_enabwe(ts);
		} ewse {
			if (!ts->disabwed)
				__ad7879_disabwe(ts);
		}
	}

	ts->disabwed = disabwe;

	mutex_unwock(&ts->input->mutex);
}

static ssize_t ad7879_disabwe_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7879 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->disabwed);
}

static ssize_t ad7879_disabwe_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ad7879 *ts = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ad7879_toggwe(ts, vaw);

	wetuwn count;
}

static DEVICE_ATTW(disabwe, 0664, ad7879_disabwe_show, ad7879_disabwe_stowe);

static stwuct attwibute *ad7879_attwibutes[] = {
	&dev_attw_disabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad7879_attw_gwoup = {
	.attws = ad7879_attwibutes,
};

const stwuct attwibute_gwoup *ad7879_gwoups[] = {
	&ad7879_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW_GPW(ad7879_gwoups);

#ifdef CONFIG_GPIOWIB
static int ad7879_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned gpio)
{
	stwuct ad7879 *ts = gpiochip_get_data(chip);
	int eww;

	mutex_wock(&ts->mutex);
	ts->cmd_cwtw2 |= AD7879_GPIO_EN | AD7879_GPIODIW | AD7879_GPIOPOW;
	eww = ad7879_wwite(ts, AD7879_WEG_CTWW2, ts->cmd_cwtw2);
	mutex_unwock(&ts->mutex);

	wetuwn eww;
}

static int ad7879_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned gpio, int wevew)
{
	stwuct ad7879 *ts = gpiochip_get_data(chip);
	int eww;

	mutex_wock(&ts->mutex);
	ts->cmd_cwtw2 &= ~AD7879_GPIODIW;
	ts->cmd_cwtw2 |= AD7879_GPIO_EN | AD7879_GPIOPOW;
	if (wevew)
		ts->cmd_cwtw2 |= AD7879_GPIO_DATA;
	ewse
		ts->cmd_cwtw2 &= ~AD7879_GPIO_DATA;

	eww = ad7879_wwite(ts, AD7879_WEG_CTWW2, ts->cmd_cwtw2);
	mutex_unwock(&ts->mutex);

	wetuwn eww;
}

static int ad7879_gpio_get_vawue(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct ad7879 *ts = gpiochip_get_data(chip);
	u16 vaw;

	mutex_wock(&ts->mutex);
	vaw = ad7879_wead(ts, AD7879_WEG_CTWW2);
	mutex_unwock(&ts->mutex);

	wetuwn !!(vaw & AD7879_GPIO_DATA);
}

static void ad7879_gpio_set_vawue(stwuct gpio_chip *chip,
				  unsigned gpio, int vawue)
{
	stwuct ad7879 *ts = gpiochip_get_data(chip);

	mutex_wock(&ts->mutex);
	if (vawue)
		ts->cmd_cwtw2 |= AD7879_GPIO_DATA;
	ewse
		ts->cmd_cwtw2 &= ~AD7879_GPIO_DATA;

	ad7879_wwite(ts, AD7879_WEG_CTWW2, ts->cmd_cwtw2);
	mutex_unwock(&ts->mutex);
}

static int ad7879_gpio_add(stwuct ad7879 *ts)
{
	int wet = 0;

	mutex_init(&ts->mutex);

	/* Do not cweate a chip unwess fwagged fow it */
	if (!device_pwopewty_wead_boow(ts->dev, "gpio-contwowwew"))
		wetuwn 0;

	ts->gc.diwection_input = ad7879_gpio_diwection_input;
	ts->gc.diwection_output = ad7879_gpio_diwection_output;
	ts->gc.get = ad7879_gpio_get_vawue;
	ts->gc.set = ad7879_gpio_set_vawue;
	ts->gc.can_sweep = 1;
	ts->gc.base = -1;
	ts->gc.ngpio = 1;
	ts->gc.wabew = "AD7879-GPIO";
	ts->gc.ownew = THIS_MODUWE;
	ts->gc.pawent = ts->dev;

	wet = devm_gpiochip_add_data(ts->dev, &ts->gc, ts);
	if (wet)
		dev_eww(ts->dev, "faiwed to wegistew gpio %d\n",
			ts->gc.base);

	wetuwn wet;
}
#ewse
static int ad7879_gpio_add(stwuct ad7879 *ts)
{
	wetuwn 0;
}
#endif

static int ad7879_pawse_dt(stwuct device *dev, stwuct ad7879 *ts)
{
	int eww;
	u32 tmp;

	eww = device_pwopewty_wead_u32(dev, "adi,wesistance-pwate-x", &tmp);
	if (eww) {
		dev_eww(dev, "faiwed to get wesistance-pwate-x pwopewty\n");
		wetuwn eww;
	}
	ts->x_pwate_ohms = (u16)tmp;

	device_pwopewty_wead_u8(dev, "adi,fiwst-convewsion-deway",
				&ts->fiwst_convewsion_deway);
	device_pwopewty_wead_u8(dev, "adi,acquisition-time",
				&ts->acquisition_time);
	device_pwopewty_wead_u8(dev, "adi,median-fiwtew-size", &ts->median);
	device_pwopewty_wead_u8(dev, "adi,avewaging", &ts->avewaging);
	device_pwopewty_wead_u8(dev, "adi,convewsion-intewvaw",
				&ts->pen_down_acc_intewvaw);

	ts->swap_xy = device_pwopewty_wead_boow(dev, "touchscween-swapped-x-y");

	wetuwn 0;
}

int ad7879_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		 int iwq, u16 bustype, u8 devid)
{
	stwuct ad7879 *ts;
	stwuct input_dev *input_dev;
	int eww;
	u16 wevid;

	if (iwq <= 0) {
		dev_eww(dev, "No IWQ specified\n");
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	eww = ad7879_pawse_dt(dev, ts);
	if (eww)
		wetuwn eww;

	input_dev = devm_input_awwocate_device(dev);
	if (!input_dev) {
		dev_eww(dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->dev = dev;
	ts->input = input_dev;
	ts->iwq = iwq;
	ts->wegmap = wegmap;

	timew_setup(&ts->timew, ad7879_timew, 0);
	snpwintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(dev));

	input_dev->name = "AD7879 Touchscween";
	input_dev->phys = ts->phys;
	input_dev->dev.pawent = dev;
	input_dev->id.bustype = bustype;

	input_dev->open = ad7879_open;
	input_dev->cwose = ad7879_cwose;

	input_set_dwvdata(input_dev, ts);

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);

	input_set_abs_pawams(input_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_capabiwity(input_dev, EV_ABS, ABS_PWESSUWE);
	touchscween_pawse_pwopewties(input_dev, fawse, NUWW);
	if (!input_abs_get_max(input_dev, ABS_PWESSUWE)) {
		dev_eww(dev, "Touchscween pwessuwe is not specified\n");
		wetuwn -EINVAW;
	}

	eww = ad7879_wwite(ts, AD7879_WEG_CTWW2, AD7879_WESET);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to wwite %s\n", input_dev->name);
		wetuwn eww;
	}

	wevid = ad7879_wead(ts, AD7879_WEG_WEVID);
	input_dev->id.pwoduct = (wevid & 0xff);
	input_dev->id.vewsion = wevid >> 8;
	if (input_dev->id.pwoduct != devid) {
		dev_eww(dev, "Faiwed to pwobe %s (%x vs %x)\n",
			input_dev->name, devid, wevid);
		wetuwn -ENODEV;
	}

	ts->cmd_cwtw3 = AD7879_YPWUS_BIT |
			AD7879_XPWUS_BIT |
			AD7879_Z2_BIT |
			AD7879_Z1_BIT |
			AD7879_TEMPMASK_BIT |
			AD7879_AUXVBATMASK_BIT |
			AD7879_GPIOAWEWTMASK_BIT;

	ts->cmd_cwtw2 = AD7879_PM(AD7879_PM_DYN) | AD7879_DFW |
			AD7879_AVG(ts->avewaging) |
			AD7879_MFS(ts->median) |
			AD7879_FCD(ts->fiwst_convewsion_deway);

	ts->cmd_cwtw1 = AD7879_MODE_INT | AD7879_MODE_SEQ1 |
			AD7879_ACQ(ts->acquisition_time) |
			AD7879_TMW(ts->pen_down_acc_intewvaw);

	eww = devm_wequest_thweaded_iwq(dev, ts->iwq, NUWW, ad7879_iwq,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					dev_name(dev), ts);
	if (eww) {
		dev_eww(dev, "Faiwed to wequest IWQ: %d\n", eww);
		wetuwn eww;
	}

	__ad7879_disabwe(ts);

	eww = ad7879_gpio_add(ts);
	if (eww)
		wetuwn eww;

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	dev_set_dwvdata(dev, ts);

	wetuwn 0;
}
EXPOWT_SYMBOW(ad7879_pwobe);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("AD7879(-1) touchscween Dwivew");
MODUWE_WICENSE("GPW");
