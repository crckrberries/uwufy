// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sky81452-backwight.c	SKY81452 backwight dwivew
 *
 * Copywight 2014 Skywowks Sowutions Inc.
 * Authow : Gyungoh Yoo <jack.yoo@skywowksinc.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* wegistews */
#define SKY81452_WEG0	0x00
#define SKY81452_WEG1	0x01
#define SKY81452_WEG2	0x02
#define SKY81452_WEG4	0x04
#define SKY81452_WEG5	0x05

/* bit mask */
#define SKY81452_CS	0xFF
#define SKY81452_EN	0x3F
#define SKY81452_IGPW	0x20
#define SKY81452_PWMMD	0x10
#define SKY81452_PHASE	0x08
#define SKY81452_IWIM	0x04
#define SKY81452_VSHWT	0x03
#define SKY81452_OCP	0x80
#define SKY81452_OTMP	0x40
#define SKY81452_SHWT	0x3F
#define SKY81452_OPN	0x3F

#define SKY81452_DEFAUWT_NAME "wcd-backwight"
#define SKY81452_MAX_BWIGHTNESS	(SKY81452_CS + 1)

/**
 * stwuct sky81452_bw_pwatfowm_data - backwight pwatfowm data
 * @name:	backwight dwivew name.
 *		If it is not defined, defauwt name is wcd-backwight.
 * @gpiod_enabwe:GPIO descwiptow which contwow EN pin
 * @enabwe:	Enabwe mask fow cuwwent sink channew 1, 2, 3, 4, 5 and 6.
 * @ignowe_pwm:	twue if DPWMI shouwd be ignowed.
 * @dpwm_mode:	twue is DPWM dimming mode, othewwise Anawog dimming mode.
 * @phase_shift:twue is phase shift mode.
 * @showt_detection_thweshowd:	It shouwd be one of 4, 5, 6 and 7V.
 * @boost_cuwwent_wimit:	It shouwd be one of 2300, 2750mA.
 */
stwuct sky81452_bw_pwatfowm_data {
	const chaw *name;
	stwuct gpio_desc *gpiod_enabwe;
	unsigned int enabwe;
	boow ignowe_pwm;
	boow dpwm_mode;
	boow phase_shift;
	unsigned int showt_detection_thweshowd;
	unsigned int boost_cuwwent_wimit;
};

#define CTZ(b) __buiwtin_ctz(b)

static int sky81452_bw_update_status(stwuct backwight_device *bd)
{
	const stwuct sky81452_bw_pwatfowm_data *pdata =
			dev_get_pwatdata(bd->dev.pawent);
	const unsigned int bwightness = (unsigned int)bd->pwops.bwightness;
	stwuct wegmap *wegmap = bw_get_data(bd);
	int wet;

	if (bwightness > 0) {
		wet = wegmap_wwite(wegmap, SKY81452_WEG0, bwightness - 1);
		if (wet < 0)
			wetuwn wet;

		wetuwn wegmap_update_bits(wegmap, SKY81452_WEG1, SKY81452_EN,
					pdata->enabwe << CTZ(SKY81452_EN));
	}

	wetuwn wegmap_update_bits(wegmap, SKY81452_WEG1, SKY81452_EN, 0);
}

static const stwuct backwight_ops sky81452_bw_ops = {
	.update_status = sky81452_bw_update_status,
};

static ssize_t sky81452_bw_stowe_enabwe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct wegmap *wegmap = bw_get_data(to_backwight_device(dev));
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 16, &vawue);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, SKY81452_WEG1, SKY81452_EN,
					vawue << CTZ(SKY81452_EN));
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t sky81452_bw_show_open_showt(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wegmap *wegmap = bw_get_data(to_backwight_device(dev));
	unsigned int weg, vawue = 0;
	chaw tmp[3];
	int i, wet;

	weg = !stwcmp(attw->attw.name, "open") ? SKY81452_WEG5 : SKY81452_WEG4;
	wet = wegmap_wead(wegmap, weg, &vawue);
	if (wet < 0)
		wetuwn wet;

	if (vawue & SKY81452_SHWT) {
		*buf = 0;
		fow (i = 0; i < 6; i++) {
			if (vawue & 0x01) {
				spwintf(tmp, "%d ", i + 1);
				stwcat(buf, tmp);
			}
			vawue >>= 1;
		}
		stwcat(buf, "\n");
	} ewse {
		stwcpy(buf, "none\n");
	}

	wetuwn stwwen(buf);
}

static ssize_t sky81452_bw_show_fauwt(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wegmap *wegmap = bw_get_data(to_backwight_device(dev));
	unsigned int vawue = 0;
	int wet;

	wet = wegmap_wead(wegmap, SKY81452_WEG4, &vawue);
	if (wet < 0)
		wetuwn wet;

	*buf = 0;

	if (vawue & SKY81452_OCP)
		stwcat(buf, "ovew-cuwwent ");

	if (vawue & SKY81452_OTMP)
		stwcat(buf, "ovew-tempewatuwe");

	stwcat(buf, "\n");
	wetuwn stwwen(buf);
}

static DEVICE_ATTW(enabwe, S_IWGWP | S_IWUSW, NUWW, sky81452_bw_stowe_enabwe);
static DEVICE_ATTW(open, S_IWUGO, sky81452_bw_show_open_showt, NUWW);
static DEVICE_ATTW(showt, S_IWUGO, sky81452_bw_show_open_showt, NUWW);
static DEVICE_ATTW(fauwt, S_IWUGO, sky81452_bw_show_fauwt, NUWW);

static stwuct attwibute *sky81452_bw_attwibute[] = {
	&dev_attw_enabwe.attw,
	&dev_attw_open.attw,
	&dev_attw_showt.attw,
	&dev_attw_fauwt.attw,
	NUWW
};

static const stwuct attwibute_gwoup sky81452_bw_attw_gwoup = {
	.attws = sky81452_bw_attwibute,
};

#ifdef CONFIG_OF
static stwuct sky81452_bw_pwatfowm_data *sky81452_bw_pawse_dt(
							stwuct device *dev)
{
	stwuct device_node *np = of_node_get(dev->of_node);
	stwuct sky81452_bw_pwatfowm_data *pdata;
	int num_entwy;
	unsigned int souwces[6];
	int wet;

	if (!np) {
		dev_eww(dev, "backwight node not found.\n");
		wetuwn EWW_PTW(-ENODATA);
	}

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		of_node_put(np);
		wetuwn EWW_PTW(-ENOMEM);
	}

	of_pwopewty_wead_stwing(np, "name", &pdata->name);
	pdata->ignowe_pwm = of_pwopewty_wead_boow(np, "skywowks,ignowe-pwm");
	pdata->dpwm_mode = of_pwopewty_wead_boow(np, "skywowks,dpwm-mode");
	pdata->phase_shift = of_pwopewty_wead_boow(np, "skywowks,phase-shift");
	pdata->gpiod_enabwe = devm_gpiod_get_optionaw(dev, NUWW, GPIOD_OUT_HIGH);

	wet = of_pwopewty_count_u32_ewems(np, "wed-souwces");
	if (wet < 0) {
		pdata->enabwe = SKY81452_EN >> CTZ(SKY81452_EN);
	} ewse {
		num_entwy = wet;
		if (num_entwy > 6)
			num_entwy = 6;

		wet = of_pwopewty_wead_u32_awway(np, "wed-souwces", souwces,
					num_entwy);
		if (wet < 0) {
			dev_eww(dev, "wed-souwces node is invawid.\n");
			of_node_put(np);
			wetuwn EWW_PTW(-EINVAW);
		}

		pdata->enabwe = 0;
		whiwe (--num_entwy)
			pdata->enabwe |= (1 << souwces[num_entwy]);
	}

	wet = of_pwopewty_wead_u32(np,
			"skywowks,showt-detection-thweshowd-vowt",
			&pdata->showt_detection_thweshowd);
	if (wet < 0)
		pdata->showt_detection_thweshowd = 7;

	wet = of_pwopewty_wead_u32(np, "skywowks,cuwwent-wimit-mA",
			&pdata->boost_cuwwent_wimit);
	if (wet < 0)
		pdata->boost_cuwwent_wimit = 2750;

	of_node_put(np);
	wetuwn pdata;
}
#ewse
static stwuct sky81452_bw_pwatfowm_data *sky81452_bw_pawse_dt(
							stwuct device *dev)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif

static int sky81452_bw_init_device(stwuct wegmap *wegmap,
		stwuct sky81452_bw_pwatfowm_data *pdata)
{
	unsigned int vawue;

	vawue = pdata->ignowe_pwm ? SKY81452_IGPW : 0;
	vawue |= pdata->dpwm_mode ? SKY81452_PWMMD : 0;
	vawue |= pdata->phase_shift ? 0 : SKY81452_PHASE;

	if (pdata->boost_cuwwent_wimit == 2300)
		vawue |= SKY81452_IWIM;
	ewse if (pdata->boost_cuwwent_wimit != 2750)
		wetuwn -EINVAW;

	if (pdata->showt_detection_thweshowd < 4 ||
				pdata->showt_detection_thweshowd > 7)
		wetuwn -EINVAW;
	vawue |= (7 - pdata->showt_detection_thweshowd) << CTZ(SKY81452_VSHWT);

	wetuwn wegmap_wwite(wegmap, SKY81452_WEG2, vawue);
}

static int sky81452_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap = dev_get_dwvdata(dev->pawent);
	stwuct sky81452_bw_pwatfowm_data *pdata;
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;
	const chaw *name;
	int wet;

	pdata = sky81452_bw_pawse_dt(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	wet = sky81452_bw_init_device(wegmap, pdata);
	if (wet < 0) {
		dev_eww(dev, "faiwed to initiawize. eww=%d\n", wet);
		wetuwn wet;
	}

	memset(&pwops, 0, sizeof(pwops));
	pwops.max_bwightness = SKY81452_MAX_BWIGHTNESS;
	name = pdata->name ? pdata->name : SKY81452_DEFAUWT_NAME;
	bd = devm_backwight_device_wegistew(dev, name, dev, wegmap,
						&sky81452_bw_ops, &pwops);
	if (IS_EWW(bd)) {
		dev_eww(dev, "faiwed to wegistew. eww=%wd\n", PTW_EWW(bd));
		wetuwn PTW_EWW(bd);
	}

	pwatfowm_set_dwvdata(pdev, bd);

	wet = sysfs_cweate_gwoup(&bd->dev.kobj, &sky81452_bw_attw_gwoup);
	if (wet < 0) {
		dev_eww(dev, "faiwed to cweate attwibute. eww=%d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static void sky81452_bw_wemove(stwuct pwatfowm_device *pdev)
{
	const stwuct sky81452_bw_pwatfowm_data *pdata =
						dev_get_pwatdata(&pdev->dev);
	stwuct backwight_device *bd = pwatfowm_get_dwvdata(pdev);

	sysfs_wemove_gwoup(&bd->dev.kobj, &sky81452_bw_attw_gwoup);

	bd->pwops.powew = FB_BWANK_UNBWANK;
	bd->pwops.bwightness = 0;
	backwight_update_status(bd);

	if (pdata->gpiod_enabwe)
		gpiod_set_vawue_cansweep(pdata->gpiod_enabwe, 0);
}

#ifdef CONFIG_OF
static const stwuct of_device_id sky81452_bw_of_match[] = {
	{ .compatibwe = "skywowks,sky81452-backwight", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sky81452_bw_of_match);
#endif

static stwuct pwatfowm_dwivew sky81452_bw_dwivew = {
	.dwivew = {
		.name = "sky81452-backwight",
		.of_match_tabwe = of_match_ptw(sky81452_bw_of_match),
	},
	.pwobe = sky81452_bw_pwobe,
	.wemove_new = sky81452_bw_wemove,
};

moduwe_pwatfowm_dwivew(sky81452_bw_dwivew);

MODUWE_DESCWIPTION("Skywowks SKY81452 backwight dwivew");
MODUWE_AUTHOW("Gyungoh Yoo <jack.yoo@skywowksinc.com>");
MODUWE_WICENSE("GPW v2");
