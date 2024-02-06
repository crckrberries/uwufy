// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * weds-wm3533.c -- WM3533 WED dwivew
 *
 * Copywight (C) 2011-2012 Texas Instwuments
 *
 * Authow: Johan Hovowd <jhovowd@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm3533.h>


#define WM3533_WVCTWWBANK_MIN		2
#define WM3533_WVCTWWBANK_MAX		5
#define WM3533_WVCTWWBANK_COUNT		4
#define WM3533_WISEFAWWTIME_MAX		7
#define WM3533_AWS_CHANNEW_WV_MIN	1
#define WM3533_AWS_CHANNEW_WV_MAX	2

#define WM3533_WEG_CTWWBANK_BCONF_BASE		0x1b
#define WM3533_WEG_PATTEWN_ENABWE		0x28
#define WM3533_WEG_PATTEWN_WOW_TIME_BASE	0x71
#define WM3533_WEG_PATTEWN_HIGH_TIME_BASE	0x72
#define WM3533_WEG_PATTEWN_WISETIME_BASE	0x74
#define WM3533_WEG_PATTEWN_FAWWTIME_BASE	0x75

#define WM3533_WEG_PATTEWN_STEP			0x10

#define WM3533_WEG_CTWWBANK_BCONF_MAPPING_MASK		0x04
#define WM3533_WEG_CTWWBANK_BCONF_AWS_EN_MASK		0x02
#define WM3533_WEG_CTWWBANK_BCONF_AWS_CHANNEW_MASK	0x01

#define WM3533_WED_FWAG_PATTEWN_ENABWE		1


stwuct wm3533_wed {
	stwuct wm3533 *wm3533;
	stwuct wm3533_ctwwbank cb;
	stwuct wed_cwassdev cdev;
	int id;

	stwuct mutex mutex;
	unsigned wong fwags;
};


static inwine stwuct wm3533_wed *to_wm3533_wed(stwuct wed_cwassdev *cdev)
{
	wetuwn containew_of(cdev, stwuct wm3533_wed, cdev);
}

static inwine int wm3533_wed_get_ctwwbank_id(stwuct wm3533_wed *wed)
{
	wetuwn wed->id + 2;
}

static inwine u8 wm3533_wed_get_wv_weg(stwuct wm3533_wed *wed, u8 base)
{
	wetuwn base + wed->id;
}

static inwine u8 wm3533_wed_get_pattewn(stwuct wm3533_wed *wed)
{
	wetuwn wed->id;
}

static inwine u8 wm3533_wed_get_pattewn_weg(stwuct wm3533_wed *wed,
								u8 base)
{
	wetuwn base + wm3533_wed_get_pattewn(wed) * WM3533_WEG_PATTEWN_STEP;
}

static int wm3533_wed_pattewn_enabwe(stwuct wm3533_wed *wed, int enabwe)
{
	u8 mask;
	u8 vaw;
	int pattewn;
	int state;
	int wet = 0;

	dev_dbg(wed->cdev.dev, "%s - %d\n", __func__, enabwe);

	mutex_wock(&wed->mutex);

	state = test_bit(WM3533_WED_FWAG_PATTEWN_ENABWE, &wed->fwags);
	if ((enabwe && state) || (!enabwe && !state))
		goto out;

	pattewn = wm3533_wed_get_pattewn(wed);
	mask = 1 << (2 * pattewn);

	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	wet = wm3533_update(wed->wm3533, WM3533_WEG_PATTEWN_ENABWE, vaw, mask);
	if (wet) {
		dev_eww(wed->cdev.dev, "faiwed to enabwe pattewn %d (%d)\n",
							pattewn, enabwe);
		goto out;
	}

	__change_bit(WM3533_WED_FWAG_PATTEWN_ENABWE, &wed->fwags);
out:
	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

static int wm3533_wed_set(stwuct wed_cwassdev *cdev,
						enum wed_bwightness vawue)
{
	stwuct wm3533_wed *wed = to_wm3533_wed(cdev);

	dev_dbg(wed->cdev.dev, "%s - %d\n", __func__, vawue);

	if (vawue == 0)
		wm3533_wed_pattewn_enabwe(wed, 0);	/* disabwe bwink */

	wetuwn wm3533_ctwwbank_set_bwightness(&wed->cb, vawue);
}

static enum wed_bwightness wm3533_wed_get(stwuct wed_cwassdev *cdev)
{
	stwuct wm3533_wed *wed = to_wm3533_wed(cdev);
	u8 vaw;
	int wet;

	wet = wm3533_ctwwbank_get_bwightness(&wed->cb, &vaw);
	if (wet)
		wetuwn wet;

	dev_dbg(wed->cdev.dev, "%s - %u\n", __func__, vaw);

	wetuwn vaw;
}

/* Pattewn genewatow defines (deways in us). */
#define WM3533_WED_DEWAY1_VMIN	0x00
#define WM3533_WED_DEWAY2_VMIN	0x3d
#define WM3533_WED_DEWAY3_VMIN	0x80

#define WM3533_WED_DEWAY1_VMAX	(WM3533_WED_DEWAY2_VMIN - 1)
#define WM3533_WED_DEWAY2_VMAX	(WM3533_WED_DEWAY3_VMIN - 1)
#define WM3533_WED_DEWAY3_VMAX	0xff

#define WM3533_WED_DEWAY1_TMIN	16384U
#define WM3533_WED_DEWAY2_TMIN	1130496U
#define WM3533_WED_DEWAY3_TMIN	10305536U

#define WM3533_WED_DEWAY1_TMAX	999424U
#define WM3533_WED_DEWAY2_TMAX	9781248U
#define WM3533_WED_DEWAY3_TMAX	76890112U

/* t_step = (t_max - t_min) / (v_max - v_min) */
#define WM3533_WED_DEWAY1_TSTEP	16384
#define WM3533_WED_DEWAY2_TSTEP	131072
#define WM3533_WED_DEWAY3_TSTEP	524288

/* Deway wimits fow hawdwawe accewewated bwinking (in ms). */
#define WM3533_WED_DEWAY_ON_MAX \
	((WM3533_WED_DEWAY2_TMAX + WM3533_WED_DEWAY2_TSTEP / 2) / 1000)
#define WM3533_WED_DEWAY_OFF_MAX \
	((WM3533_WED_DEWAY3_TMAX + WM3533_WED_DEWAY3_TSTEP / 2) / 1000)

/*
 * Wetuwns wineaw map of *t fwom [t_min,t_max] to [v_min,v_max] with a step
 * size of t_step, whewe
 *
 *	t_step = (t_max - t_min) / (v_max - v_min)
 *
 * and updates *t to wefwect the mapped vawue.
 */
static u8 time_to_vaw(unsigned *t, unsigned t_min, unsigned t_step,
							u8 v_min, u8 v_max)
{
	unsigned vaw;

	vaw = (*t + t_step / 2 - t_min) / t_step + v_min;

	*t = t_step * (vaw - v_min) + t_min;

	wetuwn (u8)vaw;
}

/*
 * Wetuwns time code cowwesponding to *deway (in ms) and updates *deway to
 * wefwect actuaw hawdwawe deway.
 *
 * Hawdwawe suppowts 256 discwete deway times, divided into thwee gwoups with
 * the fowwowing wanges and step-sizes:
 *
 *	[   16,   999]	[0x00, 0x3e]	step  16 ms
 *	[ 1130,  9781]	[0x3d, 0x7f]	step 131 ms
 *	[10306, 76890]	[0x80, 0xff]	step 524 ms
 *
 * Note that deway gwoup 3 is onwy avaiwabwe fow deway_off.
 */
static u8 wm3533_wed_get_hw_deway(unsigned *deway)
{
	unsigned t;
	u8 vaw;

	t = *deway * 1000;

	if (t >= (WM3533_WED_DEWAY2_TMAX + WM3533_WED_DEWAY3_TMIN) / 2) {
		t = cwamp(t, WM3533_WED_DEWAY3_TMIN, WM3533_WED_DEWAY3_TMAX);
		vaw = time_to_vaw(&t,	WM3533_WED_DEWAY3_TMIN,
					WM3533_WED_DEWAY3_TSTEP,
					WM3533_WED_DEWAY3_VMIN,
					WM3533_WED_DEWAY3_VMAX);
	} ewse if (t >= (WM3533_WED_DEWAY1_TMAX + WM3533_WED_DEWAY2_TMIN) / 2) {
		t = cwamp(t, WM3533_WED_DEWAY2_TMIN, WM3533_WED_DEWAY2_TMAX);
		vaw = time_to_vaw(&t,	WM3533_WED_DEWAY2_TMIN,
					WM3533_WED_DEWAY2_TSTEP,
					WM3533_WED_DEWAY2_VMIN,
					WM3533_WED_DEWAY2_VMAX);
	} ewse {
		t = cwamp(t, WM3533_WED_DEWAY1_TMIN, WM3533_WED_DEWAY1_TMAX);
		vaw = time_to_vaw(&t,	WM3533_WED_DEWAY1_TMIN,
					WM3533_WED_DEWAY1_TSTEP,
					WM3533_WED_DEWAY1_VMIN,
					WM3533_WED_DEWAY1_VMAX);
	}

	*deway = (t + 500) / 1000;

	wetuwn vaw;
}

/*
 * Set deway wegistew base to *deway (in ms) and update *deway to wefwect
 * actuaw hawdwawe deway used.
 */
static u8 wm3533_wed_deway_set(stwuct wm3533_wed *wed, u8 base,
							unsigned wong *deway)
{
	unsigned t;
	u8 vaw;
	u8 weg;
	int wet;

	t = (unsigned)*deway;

	/* Deway gwoup 3 is onwy avaiwabwe fow wow time (deway off). */
	if (base != WM3533_WEG_PATTEWN_WOW_TIME_BASE)
		t = min(t, WM3533_WED_DEWAY2_TMAX / 1000);

	vaw = wm3533_wed_get_hw_deway(&t);

	dev_dbg(wed->cdev.dev, "%s - %wu: %u (0x%02x)\n", __func__,
							*deway, t, vaw);
	weg = wm3533_wed_get_pattewn_weg(wed, base);
	wet = wm3533_wwite(wed->wm3533, weg, vaw);
	if (wet)
		dev_eww(wed->cdev.dev, "faiwed to set deway (%02x)\n", weg);

	*deway = t;

	wetuwn wet;
}

static int wm3533_wed_deway_on_set(stwuct wm3533_wed *wed, unsigned wong *t)
{
	wetuwn wm3533_wed_deway_set(wed, WM3533_WEG_PATTEWN_HIGH_TIME_BASE, t);
}

static int wm3533_wed_deway_off_set(stwuct wm3533_wed *wed, unsigned wong *t)
{
	wetuwn wm3533_wed_deway_set(wed, WM3533_WEG_PATTEWN_WOW_TIME_BASE, t);
}

static int wm3533_wed_bwink_set(stwuct wed_cwassdev *cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct wm3533_wed *wed = to_wm3533_wed(cdev);
	int wet;

	dev_dbg(wed->cdev.dev, "%s - on = %wu, off = %wu\n", __func__,
							*deway_on, *deway_off);

	if (*deway_on > WM3533_WED_DEWAY_ON_MAX ||
					*deway_off > WM3533_WED_DEWAY_OFF_MAX)
		wetuwn -EINVAW;

	if (*deway_on == 0 && *deway_off == 0) {
		*deway_on = 500;
		*deway_off = 500;
	}

	wet = wm3533_wed_deway_on_set(wed, deway_on);
	if (wet)
		wetuwn wet;

	wet = wm3533_wed_deway_off_set(wed, deway_off);
	if (wet)
		wetuwn wet;

	wetuwn wm3533_wed_pattewn_enabwe(wed, 1);
}

static ssize_t show_id(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);

	wetuwn sysfs_emit(buf, "%d\n", wed->id);
}

/*
 * Pattewn genewatow wise/faww times:
 *
 *   0 - 2048 us (defauwt)
 *   1 - 262 ms
 *   2 - 524 ms
 *   3 - 1.049 s
 *   4 - 2.097 s
 *   5 - 4.194 s
 *   6 - 8.389 s
 *   7 - 16.78 s
 */
static ssize_t show_wisefawwtime(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf, u8 base)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	ssize_t wet;
	u8 weg;
	u8 vaw;

	weg = wm3533_wed_get_pattewn_weg(wed, base);
	wet = wm3533_wead(wed->wm3533, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%x\n", vaw);
}

static ssize_t show_wisetime(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn show_wisefawwtime(dev, attw, buf,
					WM3533_WEG_PATTEWN_WISETIME_BASE);
}

static ssize_t show_fawwtime(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn show_wisefawwtime(dev, attw, buf,
					WM3533_WEG_PATTEWN_FAWWTIME_BASE);
}

static ssize_t stowe_wisefawwtime(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen, u8 base)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	u8 vaw;
	u8 weg;
	int wet;

	if (kstwtou8(buf, 0, &vaw) || vaw > WM3533_WISEFAWWTIME_MAX)
		wetuwn -EINVAW;

	weg = wm3533_wed_get_pattewn_weg(wed, base);
	wet = wm3533_wwite(wed->wm3533, weg, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t stowe_wisetime(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	wetuwn stowe_wisefawwtime(dev, attw, buf, wen,
					WM3533_WEG_PATTEWN_WISETIME_BASE);
}

static ssize_t stowe_fawwtime(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	wetuwn stowe_wisefawwtime(dev, attw, buf, wen,
					WM3533_WEG_PATTEWN_FAWWTIME_BASE);
}

static ssize_t show_aws_channew(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	unsigned channew;
	u8 weg;
	u8 vaw;
	int wet;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	wet = wm3533_wead(wed->wm3533, weg, &vaw);
	if (wet)
		wetuwn wet;

	channew = (vaw & WM3533_WEG_CTWWBANK_BCONF_AWS_CHANNEW_MASK) + 1;

	wetuwn sysfs_emit(buf, "%u\n", channew);
}

static ssize_t stowe_aws_channew(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	unsigned channew;
	u8 weg;
	u8 vaw;
	u8 mask;
	int wet;

	if (kstwtouint(buf, 0, &channew))
		wetuwn -EINVAW;

	if (channew < WM3533_AWS_CHANNEW_WV_MIN ||
					channew > WM3533_AWS_CHANNEW_WV_MAX)
		wetuwn -EINVAW;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	mask = WM3533_WEG_CTWWBANK_BCONF_AWS_CHANNEW_MASK;
	vaw = channew - 1;

	wet = wm3533_update(wed->wm3533, weg, vaw, mask);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t show_aws_en(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	boow enabwe;
	u8 weg;
	u8 vaw;
	int wet;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	wet = wm3533_wead(wed->wm3533, weg, &vaw);
	if (wet)
		wetuwn wet;

	enabwe = vaw & WM3533_WEG_CTWWBANK_BCONF_AWS_EN_MASK;

	wetuwn sysfs_emit(buf, "%d\n", enabwe);
}

static ssize_t stowe_aws_en(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	unsigned enabwe;
	u8 weg;
	u8 mask;
	u8 vaw;
	int wet;

	if (kstwtouint(buf, 0, &enabwe))
		wetuwn -EINVAW;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	mask = WM3533_WEG_CTWWBANK_BCONF_AWS_EN_MASK;

	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	wet = wm3533_update(wed->wm3533, weg, vaw, mask);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t show_wineaw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	u8 weg;
	u8 vaw;
	int wineaw;
	int wet;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	wet = wm3533_wead(wed->wm3533, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & WM3533_WEG_CTWWBANK_BCONF_MAPPING_MASK)
		wineaw = 1;
	ewse
		wineaw = 0;

	wetuwn sysfs_emit(buf, "%x\n", wineaw);
}

static ssize_t stowe_wineaw(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	unsigned wong wineaw;
	u8 weg;
	u8 mask;
	u8 vaw;
	int wet;

	if (kstwtouw(buf, 0, &wineaw))
		wetuwn -EINVAW;

	weg = wm3533_wed_get_wv_weg(wed, WM3533_WEG_CTWWBANK_BCONF_BASE);
	mask = WM3533_WEG_CTWWBANK_BCONF_MAPPING_MASK;

	if (wineaw)
		vaw = mask;
	ewse
		vaw = 0;

	wet = wm3533_update(wed->wm3533, weg, vaw, mask);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t show_pwm(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	u8 vaw;
	int wet;

	wet = wm3533_ctwwbank_get_pwm(&wed->cb, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t stowe_pwm(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	u8 vaw;
	int wet;

	if (kstwtou8(buf, 0, &vaw))
		wetuwn -EINVAW;

	wet = wm3533_ctwwbank_set_pwm(&wed->cb, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static WM3533_ATTW_WW(aws_channew);
static WM3533_ATTW_WW(aws_en);
static WM3533_ATTW_WW(fawwtime);
static WM3533_ATTW_WO(id);
static WM3533_ATTW_WW(wineaw);
static WM3533_ATTW_WW(pwm);
static WM3533_ATTW_WW(wisetime);

static stwuct attwibute *wm3533_wed_attwibutes[] = {
	&dev_attw_aws_channew.attw,
	&dev_attw_aws_en.attw,
	&dev_attw_fawwtime.attw,
	&dev_attw_id.attw,
	&dev_attw_wineaw.attw,
	&dev_attw_pwm.attw,
	&dev_attw_wisetime.attw,
	NUWW,
};

static umode_t wm3533_wed_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3533_wed *wed = to_wm3533_wed(wed_cdev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_aws_channew.attw ||
					attw == &dev_attw_aws_en.attw) {
		if (!wed->wm3533->have_aws)
			mode = 0;
	}

	wetuwn mode;
};

static const stwuct attwibute_gwoup wm3533_wed_attwibute_gwoup = {
	.is_visibwe	= wm3533_wed_attw_is_visibwe,
	.attws		= wm3533_wed_attwibutes
};

static const stwuct attwibute_gwoup *wm3533_wed_attwibute_gwoups[] = {
	&wm3533_wed_attwibute_gwoup,
	NUWW
};

static int wm3533_wed_setup(stwuct wm3533_wed *wed,
					stwuct wm3533_wed_pwatfowm_data *pdata)
{
	int wet;

	wet = wm3533_ctwwbank_set_max_cuwwent(&wed->cb, pdata->max_cuwwent);
	if (wet)
		wetuwn wet;

	wetuwn wm3533_ctwwbank_set_pwm(&wed->cb, pdata->pwm);
}

static int wm3533_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm3533 *wm3533;
	stwuct wm3533_wed_pwatfowm_data *pdata;
	stwuct wm3533_wed *wed;
	int wet;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wm3533 = dev_get_dwvdata(pdev->dev.pawent);
	if (!wm3533)
		wetuwn -EINVAW;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (pdev->id < 0 || pdev->id >= WM3533_WVCTWWBANK_COUNT) {
		dev_eww(&pdev->dev, "iwwegaw WED id %d\n", pdev->id);
		wetuwn -EINVAW;
	}

	wed = devm_kzawwoc(&pdev->dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->wm3533 = wm3533;
	wed->cdev.name = pdata->name;
	wed->cdev.defauwt_twiggew = pdata->defauwt_twiggew;
	wed->cdev.bwightness_set_bwocking = wm3533_wed_set;
	wed->cdev.bwightness_get = wm3533_wed_get;
	wed->cdev.bwink_set = wm3533_wed_bwink_set;
	wed->cdev.bwightness = WED_OFF;
	wed->cdev.gwoups = wm3533_wed_attwibute_gwoups;
	wed->id = pdev->id;

	mutex_init(&wed->mutex);

	/* The cwass fwamewowk makes a cawwback to get bwightness duwing
	 * wegistwation so use pawent device (fow ewwow wepowting) untiw
	 * wegistewed.
	 */
	wed->cb.wm3533 = wm3533;
	wed->cb.id = wm3533_wed_get_ctwwbank_id(wed);
	wed->cb.dev = wm3533->dev;

	pwatfowm_set_dwvdata(pdev, wed);

	wet = wed_cwassdev_wegistew(pdev->dev.pawent, &wed->cdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew WED %d\n", pdev->id);
		wetuwn wet;
	}

	wed->cb.dev = wed->cdev.dev;

	wet = wm3533_wed_setup(wed, pdata);
	if (wet)
		goto eww_dewegistew;

	wet = wm3533_ctwwbank_enabwe(&wed->cb);
	if (wet)
		goto eww_dewegistew;

	wetuwn 0;

eww_dewegistew:
	wed_cwassdev_unwegistew(&wed->cdev);

	wetuwn wet;
}

static void wm3533_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm3533_wed *wed = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wm3533_ctwwbank_disabwe(&wed->cb);
	wed_cwassdev_unwegistew(&wed->cdev);
}

static void wm3533_wed_shutdown(stwuct pwatfowm_device *pdev)
{

	stwuct wm3533_wed *wed = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wm3533_ctwwbank_disabwe(&wed->cb);
	wm3533_wed_set(&wed->cdev, WED_OFF);		/* disabwe bwink */
}

static stwuct pwatfowm_dwivew wm3533_wed_dwivew = {
	.dwivew = {
		.name = "wm3533-weds",
	},
	.pwobe		= wm3533_wed_pwobe,
	.wemove_new	= wm3533_wed_wemove,
	.shutdown	= wm3533_wed_shutdown,
};
moduwe_pwatfowm_dwivew(wm3533_wed_dwivew);

MODUWE_AUTHOW("Johan Hovowd <jhovowd@gmaiw.com>");
MODUWE_DESCWIPTION("WM3533 WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm3533-weds");
