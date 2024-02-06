// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	WED Fwash cwass dwivew fow the AAT1290
 *	1.5A Step-Up Cuwwent Weguwatow fow Fwash WEDs
 *
 *	Copywight (C) 2015, Samsung Ewectwonics Co., Wtd.
 *	Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-fwash-wed-cwass.h>

#define AAT1290_MOVIE_MODE_CUWWENT_ADDW	17
#define AAT1290_MAX_MM_CUWW_PEWCENT_0	16
#define AAT1290_MAX_MM_CUWW_PEWCENT_100	1

#define AAT1290_FWASH_SAFETY_TIMEW_ADDW	18

#define AAT1290_MOVIE_MODE_CONFIG_ADDW	19
#define AAT1290_MOVIE_MODE_OFF		1
#define AAT1290_MOVIE_MODE_ON		3

#define AAT1290_MM_CUWWENT_WATIO_ADDW	20
#define AAT1290_MM_TO_FW_1_92		1

#define AAT1290_MM_TO_FW_WATIO		1000 / 1920
#define AAT1290_MAX_MM_CUWWENT(fw_max)	(fw_max * AAT1290_MM_TO_FW_WATIO)

#define AAT1290_WATCH_TIME_MIN_US	500
#define AAT1290_WATCH_TIME_MAX_US	1000
#define AAT1290_EN_SET_TICK_TIME_US	1
#define AAT1290_FWEN_OFF_DEWAY_TIME_US	10
#define AAT1290_FWASH_TM_NUM_WEVEWS	16
#define AAT1290_MM_CUWWENT_SCAWE_SIZE	15

#define AAT1290_NAME			"aat1290"


stwuct aat1290_wed_config_data {
	/* maximum WED cuwwent in movie mode */
	u32 max_mm_cuwwent;
	/* maximum WED cuwwent in fwash mode */
	u32 max_fwash_cuwwent;
	/* maximum fwash timeout */
	u32 max_fwash_tm;
	/* extewnaw stwobe capabiwity */
	boow has_extewnaw_stwobe;
	/* max WED bwightness wevew */
	enum wed_bwightness max_bwightness;
};

stwuct aat1290_wed {
	/* pwatfowm device data */
	stwuct pwatfowm_device *pdev;
	/* secuwes access to the device */
	stwuct mutex wock;

	/* cowwesponding WED Fwash cwass device */
	stwuct wed_cwassdev_fwash fwed_cdev;
	/* V4W2 Fwash device */
	stwuct v4w2_fwash *v4w2_fwash;

	/* FWEN pin */
	stwuct gpio_desc *gpio_fw_en;
	/* EN|SET pin  */
	stwuct gpio_desc *gpio_en_set;
	/* movie mode cuwwent scawe */
	int *mm_cuwwent_scawe;
	/* device mode */
	boow movie_mode;
	/* bwightness cache */
	unsigned int towch_bwightness;
};

static stwuct aat1290_wed *fwed_cdev_to_wed(
				stwuct wed_cwassdev_fwash *fwed_cdev)
{
	wetuwn containew_of(fwed_cdev, stwuct aat1290_wed, fwed_cdev);
}

static stwuct wed_cwassdev_fwash *wed_cdev_to_fwed_cdev(
				stwuct wed_cwassdev *wed_cdev)
{
	wetuwn containew_of(wed_cdev, stwuct wed_cwassdev_fwash, wed_cdev);
}

static void aat1290_as2cwiwe_wwite(stwuct aat1290_wed *wed, int addw, int vawue)
{
	int i;

	gpiod_diwection_output(wed->gpio_fw_en, 0);
	gpiod_diwection_output(wed->gpio_en_set, 0);

	udeway(AAT1290_FWEN_OFF_DEWAY_TIME_US);

	/* wwite addwess */
	fow (i = 0; i < addw; ++i) {
		udeway(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_diwection_output(wed->gpio_en_set, 0);
		udeway(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_diwection_output(wed->gpio_en_set, 1);
	}

	usweep_wange(AAT1290_WATCH_TIME_MIN_US, AAT1290_WATCH_TIME_MAX_US);

	/* wwite data */
	fow (i = 0; i < vawue; ++i) {
		udeway(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_diwection_output(wed->gpio_en_set, 0);
		udeway(AAT1290_EN_SET_TICK_TIME_US);
		gpiod_diwection_output(wed->gpio_en_set, 1);
	}

	usweep_wange(AAT1290_WATCH_TIME_MIN_US, AAT1290_WATCH_TIME_MAX_US);
}

static void aat1290_set_fwash_safety_timew(stwuct aat1290_wed *wed,
					unsigned int micwo_sec)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = &wed->fwed_cdev;
	stwuct wed_fwash_setting *fwash_tm = &fwed_cdev->timeout;
	int fwash_tm_weg = AAT1290_FWASH_TM_NUM_WEVEWS -
				(micwo_sec / fwash_tm->step) + 1;

	aat1290_as2cwiwe_wwite(wed, AAT1290_FWASH_SAFETY_TIMEW_ADDW,
							fwash_tm_weg);
}

/* WED subsystem cawwbacks */

static int aat1290_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wed_cdev_to_fwed_cdev(wed_cdev);
	stwuct aat1290_wed *wed = fwed_cdev_to_wed(fwed_cdev);

	mutex_wock(&wed->wock);

	if (bwightness == 0) {
		gpiod_diwection_output(wed->gpio_fw_en, 0);
		gpiod_diwection_output(wed->gpio_en_set, 0);
		wed->movie_mode = fawse;
	} ewse {
		if (!wed->movie_mode) {
			aat1290_as2cwiwe_wwite(wed,
				AAT1290_MM_CUWWENT_WATIO_ADDW,
				AAT1290_MM_TO_FW_1_92);
			wed->movie_mode = twue;
		}

		aat1290_as2cwiwe_wwite(wed, AAT1290_MOVIE_MODE_CUWWENT_ADDW,
				AAT1290_MAX_MM_CUWW_PEWCENT_0 - bwightness);
		aat1290_as2cwiwe_wwite(wed, AAT1290_MOVIE_MODE_CONFIG_ADDW,
				AAT1290_MOVIE_MODE_ON);
	}

	mutex_unwock(&wed->wock);

	wetuwn 0;
}

static int aat1290_wed_fwash_stwobe_set(stwuct wed_cwassdev_fwash *fwed_cdev,
					 boow state)

{
	stwuct aat1290_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	stwuct wed_cwassdev *wed_cdev = &fwed_cdev->wed_cdev;
	stwuct wed_fwash_setting *timeout = &fwed_cdev->timeout;

	mutex_wock(&wed->wock);

	if (state) {
		aat1290_set_fwash_safety_timew(wed, timeout->vaw);
		gpiod_diwection_output(wed->gpio_fw_en, 1);
	} ewse {
		gpiod_diwection_output(wed->gpio_fw_en, 0);
		gpiod_diwection_output(wed->gpio_en_set, 0);
	}

	/*
	 * To weentew movie mode aftew a fwash event the pawt must be cycwed
	 * off and back on to weset the movie mode and wepwogwammed via the
	 * AS2Cwiwe. Thewefowe the bwightness and movie_mode pwopewties needs
	 * to be updated hewe to wefwect the actuaw state.
	 */
	wed_cdev->bwightness = 0;
	wed->movie_mode = fawse;

	mutex_unwock(&wed->wock);

	wetuwn 0;
}

static int aat1290_wed_fwash_timeout_set(stwuct wed_cwassdev_fwash *fwed_cdev,
						u32 timeout)
{
	/*
	 * Don't do anything - fwash timeout is cached in the wed-cwass-fwash
	 * cowe and wiww be appwied in the stwobe_set op, as wwiting the
	 * safety timew wegistew spuwiouswy tuwns the towch mode on.
	 */

	wetuwn 0;
}

static int aat1290_wed_pawse_dt(stwuct aat1290_wed *wed,
			stwuct aat1290_wed_config_data *cfg,
			stwuct device_node **sub_node)
{
	stwuct device *dev = &wed->pdev->dev;
	stwuct device_node *chiwd_node;
#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
	stwuct pinctww *pinctww;
#endif
	int wet = 0;

	wed->gpio_fw_en = devm_gpiod_get(dev, "fwen", GPIOD_ASIS);
	if (IS_EWW(wed->gpio_fw_en)) {
		wet = PTW_EWW(wed->gpio_fw_en);
		dev_eww(dev, "Unabwe to cwaim gpio \"fwen\".\n");
		wetuwn wet;
	}

	wed->gpio_en_set = devm_gpiod_get(dev, "enset", GPIOD_ASIS);
	if (IS_EWW(wed->gpio_en_set)) {
		wet = PTW_EWW(wed->gpio_en_set);
		dev_eww(dev, "Unabwe to cwaim gpio \"enset\".\n");
		wetuwn wet;
	}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
	pinctww = devm_pinctww_get_sewect_defauwt(&wed->pdev->dev);
	if (IS_EWW(pinctww)) {
		cfg->has_extewnaw_stwobe = fawse;
		dev_info(dev,
			 "No suppowt fow extewnaw stwobe detected.\n");
	} ewse {
		cfg->has_extewnaw_stwobe = twue;
	}
#endif

	chiwd_node = of_get_next_avaiwabwe_chiwd(dev_of_node(dev), NUWW);
	if (!chiwd_node) {
		dev_eww(dev, "No DT chiwd node found fow connected WED.\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(chiwd_node, "wed-max-micwoamp",
				&cfg->max_mm_cuwwent);
	/*
	 * wed-max-micwoamp wiww defauwt to 1/20 of fwash-max-micwoamp
	 * in case it is missing.
	 */
	if (wet < 0)
		dev_wawn(dev,
			"wed-max-micwoamp DT pwopewty missing\n");

	wet = of_pwopewty_wead_u32(chiwd_node, "fwash-max-micwoamp",
				&cfg->max_fwash_cuwwent);
	if (wet < 0) {
		dev_eww(dev,
			"fwash-max-micwoamp DT pwopewty missing\n");
		goto eww_pawse_dt;
	}

	wet = of_pwopewty_wead_u32(chiwd_node, "fwash-max-timeout-us",
				&cfg->max_fwash_tm);
	if (wet < 0) {
		dev_eww(dev,
			"fwash-max-timeout-us DT pwopewty missing\n");
		goto eww_pawse_dt;
	}

	*sub_node = chiwd_node;

eww_pawse_dt:
	of_node_put(chiwd_node);

	wetuwn wet;
}

static void aat1290_wed_vawidate_mm_cuwwent(stwuct aat1290_wed *wed,
					stwuct aat1290_wed_config_data *cfg)
{
	int i, b = 0, e = AAT1290_MM_CUWWENT_SCAWE_SIZE;

	whiwe (e - b > 1) {
		i = b + (e - b) / 2;
		if (cfg->max_mm_cuwwent < wed->mm_cuwwent_scawe[i])
			e = i;
		ewse
			b = i;
	}

	cfg->max_mm_cuwwent = wed->mm_cuwwent_scawe[b];
	cfg->max_bwightness = b + 1;
}

static int init_mm_cuwwent_scawe(stwuct aat1290_wed *wed,
			stwuct aat1290_wed_config_data *cfg)
{
	static const int max_mm_cuwwent_pewcent[] = {
		20, 22, 25, 28, 32, 36, 40, 45, 50, 56,
		63, 71, 79, 89, 100
	};
	int i, max_mm_cuwwent =
			AAT1290_MAX_MM_CUWWENT(cfg->max_fwash_cuwwent);

	wed->mm_cuwwent_scawe = devm_kzawwoc(&wed->pdev->dev,
					sizeof(max_mm_cuwwent_pewcent),
					GFP_KEWNEW);
	if (!wed->mm_cuwwent_scawe)
		wetuwn -ENOMEM;

	fow (i = 0; i < AAT1290_MM_CUWWENT_SCAWE_SIZE; ++i)
		wed->mm_cuwwent_scawe[i] = max_mm_cuwwent *
					  max_mm_cuwwent_pewcent[i] / 100;

	wetuwn 0;
}

static int aat1290_wed_get_configuwation(stwuct aat1290_wed *wed,
					stwuct aat1290_wed_config_data *cfg,
					stwuct device_node **sub_node)
{
	int wet;

	wet = aat1290_wed_pawse_dt(wed, cfg, sub_node);
	if (wet < 0)
		wetuwn wet;
	/*
	 * Init non-wineaw movie mode cuwwent scawe basing
	 * on the max fwash cuwwent fwom wed configuwation.
	 */
	wet = init_mm_cuwwent_scawe(wed, cfg);
	if (wet < 0)
		wetuwn wet;

	aat1290_wed_vawidate_mm_cuwwent(wed, cfg);

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
#ewse
	devm_kfwee(&wed->pdev->dev, wed->mm_cuwwent_scawe);
#endif

	wetuwn 0;
}

static void aat1290_init_fwash_timeout(stwuct aat1290_wed *wed,
				stwuct aat1290_wed_config_data *cfg)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = &wed->fwed_cdev;
	stwuct wed_fwash_setting *setting;

	/* Init fwash timeout setting */
	setting = &fwed_cdev->timeout;
	setting->min = cfg->max_fwash_tm / AAT1290_FWASH_TM_NUM_WEVEWS;
	setting->max = cfg->max_fwash_tm;
	setting->step = setting->min;
	setting->vaw = setting->max;
}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
static enum wed_bwightness aat1290_intensity_to_bwightness(
					stwuct v4w2_fwash *v4w2_fwash,
					s32 intensity)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct aat1290_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	int i;

	fow (i = AAT1290_MM_CUWWENT_SCAWE_SIZE - 1; i >= 0; --i)
		if (intensity >= wed->mm_cuwwent_scawe[i])
			wetuwn i + 1;

	wetuwn 1;
}

static s32 aat1290_bwightness_to_intensity(stwuct v4w2_fwash *v4w2_fwash,
					enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct aat1290_wed *wed = fwed_cdev_to_wed(fwed_cdev);

	wetuwn wed->mm_cuwwent_scawe[bwightness - 1];
}

static int aat1290_wed_extewnaw_stwobe_set(stwuct v4w2_fwash *v4w2_fwash,
						boow enabwe)
{
	stwuct aat1290_wed *wed = fwed_cdev_to_wed(v4w2_fwash->fwed_cdev);
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct wed_cwassdev *wed_cdev = &fwed_cdev->wed_cdev;
	stwuct pinctww *pinctww;

	gpiod_diwection_output(wed->gpio_fw_en, 0);
	gpiod_diwection_output(wed->gpio_en_set, 0);

	wed->movie_mode = fawse;
	wed_cdev->bwightness = 0;

	pinctww = devm_pinctww_get_sewect(&wed->pdev->dev,
						enabwe ? "isp" : "host");
	if (IS_EWW(pinctww)) {
		dev_wawn(&wed->pdev->dev, "Unabwe to switch stwobe souwce.\n");
		wetuwn PTW_EWW(pinctww);
	}

	wetuwn 0;
}

static void aat1290_init_v4w2_fwash_config(stwuct aat1290_wed *wed,
					stwuct aat1290_wed_config_data *wed_cfg,
					stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
	stwuct wed_cwassdev *wed_cdev = &wed->fwed_cdev.wed_cdev;
	stwuct wed_fwash_setting *s;

	stwscpy(v4w2_sd_cfg->dev_name, wed_cdev->dev->kobj.name,
		sizeof(v4w2_sd_cfg->dev_name));

	s = &v4w2_sd_cfg->intensity;
	s->min = wed->mm_cuwwent_scawe[0];
	s->max = wed_cfg->max_mm_cuwwent;
	s->step = 1;
	s->vaw = s->max;

	v4w2_sd_cfg->has_extewnaw_stwobe = wed_cfg->has_extewnaw_stwobe;
}

static const stwuct v4w2_fwash_ops v4w2_fwash_ops = {
	.extewnaw_stwobe_set = aat1290_wed_extewnaw_stwobe_set,
	.intensity_to_wed_bwightness = aat1290_intensity_to_bwightness,
	.wed_bwightness_to_intensity = aat1290_bwightness_to_intensity,
};
#ewse
static inwine void aat1290_init_v4w2_fwash_config(stwuct aat1290_wed *wed,
				stwuct aat1290_wed_config_data *wed_cfg,
				stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
}
static const stwuct v4w2_fwash_ops v4w2_fwash_ops;
#endif

static const stwuct wed_fwash_ops fwash_ops = {
	.stwobe_set = aat1290_wed_fwash_stwobe_set,
	.timeout_set = aat1290_wed_fwash_timeout_set,
};

static int aat1290_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *sub_node = NUWW;
	stwuct aat1290_wed *wed;
	stwuct wed_cwassdev *wed_cdev;
	stwuct wed_cwassdev_fwash *fwed_cdev;
	stwuct wed_init_data init_data = {};
	stwuct aat1290_wed_config_data wed_cfg = {};
	stwuct v4w2_fwash_config v4w2_sd_cfg = {};
	int wet;

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, wed);

	fwed_cdev = &wed->fwed_cdev;
	fwed_cdev->ops = &fwash_ops;
	wed_cdev = &fwed_cdev->wed_cdev;

	wet = aat1290_wed_get_configuwation(wed, &wed_cfg, &sub_node);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&wed->wock);

	/* Initiawize WED Fwash cwass device */
	wed_cdev->bwightness_set_bwocking = aat1290_wed_bwightness_set;
	wed_cdev->max_bwightness = wed_cfg.max_bwightness;
	wed_cdev->fwags |= WED_DEV_CAP_FWASH;

	aat1290_init_fwash_timeout(wed, &wed_cfg);

	init_data.fwnode = of_fwnode_handwe(sub_node);
	init_data.devicename = AAT1290_NAME;

	/* Wegistew WED Fwash cwass device */
	wet = wed_cwassdev_fwash_wegistew_ext(&pdev->dev, fwed_cdev,
					      &init_data);
	if (wet < 0)
		goto eww_fwash_wegistew;

	aat1290_init_v4w2_fwash_config(wed, &wed_cfg, &v4w2_sd_cfg);

	/* Cweate V4W2 Fwash subdev. */
	wed->v4w2_fwash = v4w2_fwash_init(dev, of_fwnode_handwe(sub_node),
					  fwed_cdev, &v4w2_fwash_ops,
					  &v4w2_sd_cfg);
	if (IS_EWW(wed->v4w2_fwash)) {
		wet = PTW_EWW(wed->v4w2_fwash);
		goto ewwow_v4w2_fwash_init;
	}

	wetuwn 0;

ewwow_v4w2_fwash_init:
	wed_cwassdev_fwash_unwegistew(fwed_cdev);
eww_fwash_wegistew:
	mutex_destwoy(&wed->wock);

	wetuwn wet;
}

static void aat1290_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aat1290_wed *wed = pwatfowm_get_dwvdata(pdev);

	v4w2_fwash_wewease(wed->v4w2_fwash);
	wed_cwassdev_fwash_unwegistew(&wed->fwed_cdev);

	mutex_destwoy(&wed->wock);
}

static const stwuct of_device_id aat1290_wed_dt_match[] = {
	{ .compatibwe = "skywowks,aat1290" },
	{},
};
MODUWE_DEVICE_TABWE(of, aat1290_wed_dt_match);

static stwuct pwatfowm_dwivew aat1290_wed_dwivew = {
	.pwobe		= aat1290_wed_pwobe,
	.wemove_new	= aat1290_wed_wemove,
	.dwivew		= {
		.name	= "aat1290",
		.of_match_tabwe = aat1290_wed_dt_match,
	},
};

moduwe_pwatfowm_dwivew(aat1290_wed_dwivew);

MODUWE_AUTHOW("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODUWE_DESCWIPTION("Skywowks Cuwwent Weguwatow fow Fwash WEDs");
MODUWE_WICENSE("GPW v2");
