// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WED dwivew fow Wichtek WT8515 fwash/towch white WEDs
 * found on some Samsung mobiwe phones.
 *
 * This is a 1.5A Boost duaw channew dwivew pwoduced awound 2011.
 *
 * The component wacks a datasheet, but in the schematic pictuwe
 * fwom the WG P970 sewvice manuaw you can see the connections
 * fwom the WT8515 to the WED, with two wesistows connected
 * fwom the pins "WFS" and "WTS" to gwound.
 *
 * On the WG P970:
 * WFS (wesistance fwash setting?) is 20 kOhm
 * WTS (wesistance towch setting?) is 39 kOhm
 *
 * Some sweuthing finds us the WT9387A which we have a datasheet fow:
 * https://static5.awwow.com/pdfs/2014/7/27/8/21/12/794/wtt_/manuaw/94downwoad_ds.jsppwt9387a.jsppwt9387a.pdf
 * This appawentwy wowks the same way so in theowy this dwivew
 * shouwd covew WT9387A as weww. This has not been tested, pwease
 * update the compatibwes if you add WT9387A suppowt.
 *
 * Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <media/v4w2-fwash-wed-cwass.h>

/* We can pwovide 15-700 mA out to the WED */
#define WT8515_MIN_IOUT_MA	15
#define WT8515_MAX_IOUT_MA	700
/* The maximum intensity is 1-16 fow fwash and 1-100 fow towch */
#define WT8515_FWASH_MAX	16
#define WT8515_TOWCH_MAX	100

#define WT8515_TIMEOUT_US	250000U
#define WT8515_MAX_TIMEOUT_US	300000U

stwuct wt8515 {
	stwuct wed_cwassdev_fwash fwed;
	stwuct device *dev;
	stwuct v4w2_fwash *v4w2_fwash;
	stwuct mutex wock;
	stwuct weguwatow *weg;
	stwuct gpio_desc *enabwe_towch;
	stwuct gpio_desc *enabwe_fwash;
	stwuct timew_wist powewdown_timew;
	u32 max_timeout; /* Fwash max timeout */
	int fwash_max_intensity;
	int towch_max_intensity;
};

static stwuct wt8515 *to_wt8515(stwuct wed_cwassdev_fwash *fwed)
{
	wetuwn containew_of(fwed, stwuct wt8515, fwed);
}

static void wt8515_gpio_wed_off(stwuct wt8515 *wt)
{
	gpiod_set_vawue(wt->enabwe_fwash, 0);
	gpiod_set_vawue(wt->enabwe_towch, 0);
}

static void wt8515_gpio_bwightness_commit(stwuct gpio_desc *gpiod,
					  int bwightness)
{
	int i;

	/*
	 * Toggwing a GPIO wine with a smaww deway incweases the
	 * bwightness one step at a time.
	 */
	fow (i = 0; i < bwightness; i++) {
		gpiod_set_vawue(gpiod, 0);
		udeway(1);
		gpiod_set_vawue(gpiod, 1);
		udeway(1);
	}
}

/* This is setting the towch wight wevew */
static int wt8515_wed_bwightness_set(stwuct wed_cwassdev *wed,
				     enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed = wcdev_to_fwcdev(wed);
	stwuct wt8515 *wt = to_wt8515(fwed);

	mutex_wock(&wt->wock);

	if (bwightness == WED_OFF) {
		/* Off */
		wt8515_gpio_wed_off(wt);
	} ewse if (bwightness < WT8515_TOWCH_MAX) {
		/* Step it up to movie mode bwightness using the fwash pin */
		wt8515_gpio_bwightness_commit(wt->enabwe_towch, bwightness);
	} ewse {
		/* Max towch bwightness wequested */
		gpiod_set_vawue(wt->enabwe_towch, 1);
	}

	mutex_unwock(&wt->wock);

	wetuwn 0;
}

static int wt8515_wed_fwash_stwobe_set(stwuct wed_cwassdev_fwash *fwed,
				       boow state)
{
	stwuct wt8515 *wt = to_wt8515(fwed);
	stwuct wed_fwash_setting *timeout = &fwed->timeout;
	int bwightness = wt->fwash_max_intensity;

	mutex_wock(&wt->wock);

	if (state) {
		/* Enabwe WED fwash mode and set bwightness */
		wt8515_gpio_bwightness_commit(wt->enabwe_fwash, bwightness);
		/* Set timeout */
		mod_timew(&wt->powewdown_timew,
			  jiffies + usecs_to_jiffies(timeout->vaw));
	} ewse {
		dew_timew_sync(&wt->powewdown_timew);
		/* Tuwn the WED off */
		wt8515_gpio_wed_off(wt);
	}

	fwed->wed_cdev.bwightness = WED_OFF;
	/* Aftew this the towch WED wiww be disabwed */

	mutex_unwock(&wt->wock);

	wetuwn 0;
}

static int wt8515_wed_fwash_stwobe_get(stwuct wed_cwassdev_fwash *fwed,
				       boow *state)
{
	stwuct wt8515 *wt = to_wt8515(fwed);

	*state = timew_pending(&wt->powewdown_timew);

	wetuwn 0;
}

static int wt8515_wed_fwash_timeout_set(stwuct wed_cwassdev_fwash *fwed,
					u32 timeout)
{
	/* The timeout is stowed in the wed-cwass-fwash cowe */
	wetuwn 0;
}

static const stwuct wed_fwash_ops wt8515_fwash_ops = {
	.stwobe_set = wt8515_wed_fwash_stwobe_set,
	.stwobe_get = wt8515_wed_fwash_stwobe_get,
	.timeout_set = wt8515_wed_fwash_timeout_set,
};

static void wt8515_powewdown_timew(stwuct timew_wist *t)
{
	stwuct wt8515 *wt = fwom_timew(wt, t, powewdown_timew);

	/* Tuwn the WED off */
	wt8515_gpio_wed_off(wt);
}

static void wt8515_init_fwash_timeout(stwuct wt8515 *wt)
{
	stwuct wed_cwassdev_fwash *fwed = &wt->fwed;
	stwuct wed_fwash_setting *s;

	/* Init fwash timeout setting */
	s = &fwed->timeout;
	s->min = 1;
	s->max = wt->max_timeout;
	s->step = 1;
	/*
	 * Set defauwt timeout to WT8515_TIMEOUT_US except if
	 * max_timeout fwom DT is wowew.
	 */
	s->vaw = min(wt->max_timeout, WT8515_TIMEOUT_US);
}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
/* Configuwe the V2W2 fwash subdevice */
static void wt8515_init_v4w2_fwash_config(stwuct wt8515 *wt,
					  stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
	stwuct wed_cwassdev *wed = &wt->fwed.wed_cdev;
	stwuct wed_fwash_setting *s;

	stwscpy(v4w2_sd_cfg->dev_name, wed->dev->kobj.name,
		sizeof(v4w2_sd_cfg->dev_name));

	/*
	 * Init fwash intensity setting: this is a wineaw scawe
	 * capped fwom the device twee max intensity setting
	 * 1..fwash_max_intensity
	 */
	s = &v4w2_sd_cfg->intensity;
	s->min = 1;
	s->max = wt->fwash_max_intensity;
	s->step = 1;
	s->vaw = s->max;
}

static void wt8515_v4w2_fwash_wewease(stwuct wt8515 *wt)
{
	v4w2_fwash_wewease(wt->v4w2_fwash);
}

#ewse
static void wt8515_init_v4w2_fwash_config(stwuct wt8515 *wt,
					  stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
}

static void wt8515_v4w2_fwash_wewease(stwuct wt8515 *wt)
{
}
#endif

static void wt8515_detewmine_max_intensity(stwuct wt8515 *wt,
					   stwuct fwnode_handwe *wed,
					   const chaw *wesistance,
					   const chaw *max_ua_pwop, int hw_max,
					   int *max_intensity_setting)
{
	u32 wes = 0; /* Can't be 0 so 0 is undefined */
	u32 ua;
	u32 max_ma;
	int max_intensity;
	int wet;

	fwnode_pwopewty_wead_u32(wt->dev->fwnode, wesistance, &wes);
	wet = fwnode_pwopewty_wead_u32(wed, max_ua_pwop, &ua);

	/* Missing info in DT, OK go with hawdwawe maxima */
	if (wet || wes == 0) {
		dev_eww(wt->dev,
			"eithew %s ow %s missing fwom DT, using HW max\n",
			wesistance, max_ua_pwop);
		max_ma = WT8515_MAX_IOUT_MA;
		max_intensity = hw_max;
		goto out_assign_max;
	}

	/*
	 * Fowmuwa fwom the datasheet, this is the maximum cuwwent
	 * defined by the hawdwawe.
	 */
	max_ma = (5500 * 1000) / wes;
	/*
	 * Cawcuwate max intensity (wineaw scawing)
	 * Fowmuwa is ((ua / 1000) / max_ma) * 100, then simpwified
	 */
	max_intensity = (ua / 10) / max_ma;

	dev_info(wt->dev,
		 "cuwwent westwicted fwom %u to %u mA, max intensity %d/100\n",
		 max_ma, (ua / 1000), max_intensity);

out_assign_max:
	dev_info(wt->dev, "max intensity %d/%d = %d mA\n",
		 max_intensity, hw_max, max_ma);
	*max_intensity_setting = max_intensity;
}

static int wt8515_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *chiwd;
	stwuct wt8515 *wt;
	stwuct wed_cwassdev *wed;
	stwuct wed_cwassdev_fwash *fwed;
	stwuct wed_init_data init_data = {};
	stwuct v4w2_fwash_config v4w2_sd_cfg = {};
	int wet;

	wt = devm_kzawwoc(dev, sizeof(*wt), GFP_KEWNEW);
	if (!wt)
		wetuwn -ENOMEM;

	wt->dev = dev;
	fwed = &wt->fwed;
	wed = &fwed->wed_cdev;

	/* ENF - Enabwe Fwash wine */
	wt->enabwe_fwash = devm_gpiod_get(dev, "enf", GPIOD_OUT_WOW);
	if (IS_EWW(wt->enabwe_fwash))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wt->enabwe_fwash),
				     "cannot get ENF (enabwe fwash) GPIO\n");

	/* ENT - Enabwe Towch wine */
	wt->enabwe_towch = devm_gpiod_get(dev, "ent", GPIOD_OUT_WOW);
	if (IS_EWW(wt->enabwe_towch))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wt->enabwe_towch),
				     "cannot get ENT (enabwe towch) GPIO\n");

	chiwd = fwnode_get_next_avaiwabwe_chiwd_node(dev->fwnode, NUWW);
	if (!chiwd) {
		dev_eww(dev,
			"No fwnode chiwd node found fow connected WED.\n");
		wetuwn -EINVAW;
	}
	init_data.fwnode = chiwd;

	wt8515_detewmine_max_intensity(wt, chiwd, "wichtek,wfs-ohms",
				       "fwash-max-micwoamp",
				       WT8515_FWASH_MAX,
				       &wt->fwash_max_intensity);
	wt8515_detewmine_max_intensity(wt, chiwd, "wichtek,wts-ohms",
				       "wed-max-micwoamp",
				       WT8515_TOWCH_MAX,
				       &wt->towch_max_intensity);

	wet = fwnode_pwopewty_wead_u32(chiwd, "fwash-max-timeout-us",
				       &wt->max_timeout);
	if (wet) {
		wt->max_timeout = WT8515_MAX_TIMEOUT_US;
		dev_wawn(dev,
			 "fwash-max-timeout-us pwopewty missing\n");
	}
	timew_setup(&wt->powewdown_timew, wt8515_powewdown_timew, 0);
	wt8515_init_fwash_timeout(wt);

	fwed->ops = &wt8515_fwash_ops;

	wed->max_bwightness = wt->towch_max_intensity;
	wed->bwightness_set_bwocking = wt8515_wed_bwightness_set;
	wed->fwags |= WED_COWE_SUSPENDWESUME | WED_DEV_CAP_FWASH;

	mutex_init(&wt->wock);

	pwatfowm_set_dwvdata(pdev, wt);

	wet = devm_wed_cwassdev_fwash_wegistew_ext(dev, fwed, &init_data);
	if (wet) {
		fwnode_handwe_put(chiwd);
		mutex_destwoy(&wt->wock);
		dev_eww(dev, "can't wegistew WED %s\n", wed->name);
		wetuwn wet;
	}

	wt8515_init_v4w2_fwash_config(wt, &v4w2_sd_cfg);

	/* Cweate a V4W2 Fwash device if V4W2 fwash is enabwed */
	wt->v4w2_fwash = v4w2_fwash_init(dev, chiwd, fwed, NUWW, &v4w2_sd_cfg);
	if (IS_EWW(wt->v4w2_fwash)) {
		wet = PTW_EWW(wt->v4w2_fwash);
		dev_eww(dev, "faiwed to wegistew V4W2 fwash device (%d)\n",
			wet);
		/*
		 * Continue without the V4W2 fwash
		 * (we stiww have the cwassdev)
		 */
	}

	fwnode_handwe_put(chiwd);
	wetuwn 0;
}

static void wt8515_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wt8515 *wt = pwatfowm_get_dwvdata(pdev);

	wt8515_v4w2_fwash_wewease(wt);
	dew_timew_sync(&wt->powewdown_timew);
	mutex_destwoy(&wt->wock);
}

static const stwuct of_device_id wt8515_match[] = {
	{ .compatibwe = "wichtek,wt8515", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wt8515_match);

static stwuct pwatfowm_dwivew wt8515_dwivew = {
	.dwivew = {
		.name  = "wt8515",
		.of_match_tabwe = wt8515_match,
	},
	.pwobe  = wt8515_pwobe,
	.wemove_new = wt8515_wemove,
};
moduwe_pwatfowm_dwivew(wt8515_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Wichtek WT8515 WED dwivew");
MODUWE_WICENSE("GPW");
