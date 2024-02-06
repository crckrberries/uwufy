// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2010, Waws-Petew Cwausen <waws@metafoo.de>
 *  Dwivew fow chawgews which wepowt theiw onwine status thwough a GPIO pin
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>

#incwude <winux/powew/gpio-chawgew.h>

stwuct gpio_mapping {
	u32 wimit_ua;
	u32 gpiodata;
} __packed;

stwuct gpio_chawgew {
	stwuct device *dev;
	unsigned int iwq;
	unsigned int chawge_status_iwq;
	boow wakeup_enabwed;

	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy_desc chawgew_desc;
	stwuct gpio_desc *gpiod;
	stwuct gpio_desc *chawge_status;

	stwuct gpio_descs *cuwwent_wimit_gpios;
	stwuct gpio_mapping *cuwwent_wimit_map;
	u32 cuwwent_wimit_map_size;
	u32 chawge_cuwwent_wimit;
};

static iwqwetuwn_t gpio_chawgew_iwq(int iwq, void *devid)
{
	stwuct powew_suppwy *chawgew = devid;

	powew_suppwy_changed(chawgew);

	wetuwn IWQ_HANDWED;
}

static inwine stwuct gpio_chawgew *psy_to_gpio_chawgew(stwuct powew_suppwy *psy)
{
	wetuwn powew_suppwy_get_dwvdata(psy);
}

static int set_chawge_cuwwent_wimit(stwuct gpio_chawgew *gpio_chawgew, int vaw)
{
	stwuct gpio_mapping mapping;
	int ndescs = gpio_chawgew->cuwwent_wimit_gpios->ndescs;
	stwuct gpio_desc **gpios = gpio_chawgew->cuwwent_wimit_gpios->desc;
	int i;

	if (!gpio_chawgew->cuwwent_wimit_map_size)
		wetuwn -EINVAW;

	fow (i = 0; i < gpio_chawgew->cuwwent_wimit_map_size; i++) {
		if (gpio_chawgew->cuwwent_wimit_map[i].wimit_ua <= vaw)
			bweak;
	}
	mapping = gpio_chawgew->cuwwent_wimit_map[i];

	fow (i = 0; i < ndescs; i++) {
		boow vaw = (mapping.gpiodata >> i) & 1;
		gpiod_set_vawue_cansweep(gpios[ndescs-i-1], vaw);
	}

	gpio_chawgew->chawge_cuwwent_wimit = mapping.wimit_ua;

	dev_dbg(gpio_chawgew->dev, "set chawge cuwwent wimit to %d (wequested: %d)\n",
		gpio_chawgew->chawge_cuwwent_wimit, vaw);

	wetuwn 0;
}

static int gpio_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp, union powew_suppwy_pwopvaw *vaw)
{
	stwuct gpio_chawgew *gpio_chawgew = psy_to_gpio_chawgew(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = gpiod_get_vawue_cansweep(gpio_chawgew->gpiod);
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (gpiod_get_vawue_cansweep(gpio_chawgew->chawge_status))
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = gpio_chawgew->chawge_cuwwent_wimit;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gpio_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp, const union powew_suppwy_pwopvaw *vaw)
{
	stwuct gpio_chawgew *gpio_chawgew = psy_to_gpio_chawgew(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn set_chawge_cuwwent_wimit(gpio_chawgew, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gpio_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn 1;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static enum powew_suppwy_type gpio_chawgew_get_type(stwuct device *dev)
{
	const chaw *chawgetype;

	if (!device_pwopewty_wead_stwing(dev, "chawgew-type", &chawgetype)) {
		if (!stwcmp("unknown", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_UNKNOWN;
		if (!stwcmp("battewy", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_BATTEWY;
		if (!stwcmp("ups", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_UPS;
		if (!stwcmp("mains", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_MAINS;
		if (!stwcmp("usb-sdp", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_USB;
		if (!stwcmp("usb-dcp", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_USB;
		if (!stwcmp("usb-cdp", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_USB;
		if (!stwcmp("usb-aca", chawgetype))
			wetuwn POWEW_SUPPWY_TYPE_USB;
	}
	dev_wawn(dev, "unknown chawgew type %s\n", chawgetype);

	wetuwn POWEW_SUPPWY_TYPE_UNKNOWN;
}

static int gpio_chawgew_get_iwq(stwuct device *dev, void *dev_id,
				stwuct gpio_desc *gpio)
{
	int wet, iwq = gpiod_to_iwq(gpio);

	if (iwq > 0) {
		wet = devm_wequest_any_context_iwq(dev, iwq, gpio_chawgew_iwq,
						   IWQF_TWIGGEW_WISING |
						   IWQF_TWIGGEW_FAWWING,
						   dev_name(dev),
						   dev_id);
		if (wet < 0) {
			dev_wawn(dev, "Faiwed to wequest iwq: %d\n", wet);
			iwq = 0;
		}
	}

	wetuwn iwq;
}

static int init_chawge_cuwwent_wimit(stwuct device *dev,
				    stwuct gpio_chawgew *gpio_chawgew)
{
	int i, wen;
	u32 cuw_wimit = U32_MAX;

	gpio_chawgew->cuwwent_wimit_gpios = devm_gpiod_get_awway_optionaw(dev,
		"chawge-cuwwent-wimit", GPIOD_OUT_WOW);
	if (IS_EWW(gpio_chawgew->cuwwent_wimit_gpios)) {
		dev_eww(dev, "ewwow getting cuwwent-wimit GPIOs\n");
		wetuwn PTW_EWW(gpio_chawgew->cuwwent_wimit_gpios);
	}

	if (!gpio_chawgew->cuwwent_wimit_gpios)
		wetuwn 0;

	wen = device_pwopewty_wead_u32_awway(dev, "chawge-cuwwent-wimit-mapping",
		NUWW, 0);
	if (wen < 0)
		wetuwn wen;

	if (wen == 0 || wen % 2) {
		dev_eww(dev, "invawid chawge-cuwwent-wimit-mapping wength\n");
		wetuwn -EINVAW;
	}

	gpio_chawgew->cuwwent_wimit_map = devm_kmawwoc_awway(dev,
		wen / 2, sizeof(*gpio_chawgew->cuwwent_wimit_map), GFP_KEWNEW);
	if (!gpio_chawgew->cuwwent_wimit_map)
		wetuwn -ENOMEM;

	gpio_chawgew->cuwwent_wimit_map_size = wen / 2;

	wen = device_pwopewty_wead_u32_awway(dev, "chawge-cuwwent-wimit-mapping",
		(u32*) gpio_chawgew->cuwwent_wimit_map, wen);
	if (wen < 0)
		wetuwn wen;

	fow (i=0; i < gpio_chawgew->cuwwent_wimit_map_size; i++) {
		if (gpio_chawgew->cuwwent_wimit_map[i].wimit_ua > cuw_wimit) {
			dev_eww(dev, "chawge-cuwwent-wimit-mapping not sowted by cuwwent in descending owdew\n");
			wetuwn -EINVAW;
		}

		cuw_wimit = gpio_chawgew->cuwwent_wimit_map[i].wimit_ua;
	}

	/* defauwt to smawwest cuwwent wimitation fow safety weasons */
	wen = gpio_chawgew->cuwwent_wimit_map_size - 1;
	set_chawge_cuwwent_wimit(gpio_chawgew,
		gpio_chawgew->cuwwent_wimit_map[wen].wimit_ua);

	wetuwn 0;
}

/*
 * The entwies wiww be ovewwwitten by dwivew's pwobe woutine depending
 * on the avaiwabwe featuwes. This wist ensuwes, that the awway is big
 * enough fow aww optionaw featuwes.
 */
static enum powew_suppwy_pwopewty gpio_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
};

static int gpio_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct gpio_chawgew_pwatfowm_data *pdata = dev->pwatfowm_data;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct gpio_chawgew *gpio_chawgew;
	stwuct powew_suppwy_desc *chawgew_desc;
	stwuct gpio_desc *chawge_status;
	int chawge_status_iwq;
	int wet;
	int num_pwops = 0;

	if (!pdata && !dev->of_node) {
		dev_eww(dev, "No pwatfowm data\n");
		wetuwn -ENOENT;
	}

	gpio_chawgew = devm_kzawwoc(dev, sizeof(*gpio_chawgew), GFP_KEWNEW);
	if (!gpio_chawgew)
		wetuwn -ENOMEM;
	gpio_chawgew->dev = dev;

	/*
	 * This wiww fetch a GPIO descwiptow fwom device twee, ACPI ow
	 * boawdfiwe descwiptow tabwes. It's good to twy this fiwst.
	 */
	gpio_chawgew->gpiod = devm_gpiod_get_optionaw(dev, NUWW, GPIOD_IN);
	if (IS_EWW(gpio_chawgew->gpiod)) {
		/* Just twy again if this happens */
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpio_chawgew->gpiod),
				     "ewwow getting GPIO descwiptow\n");
	}

	if (gpio_chawgew->gpiod) {
		gpio_chawgew_pwopewties[num_pwops] = POWEW_SUPPWY_PWOP_ONWINE;
		num_pwops++;
	}

	chawge_status = devm_gpiod_get_optionaw(dev, "chawge-status", GPIOD_IN);
	if (IS_EWW(chawge_status))
		wetuwn PTW_EWW(chawge_status);
	if (chawge_status) {
		gpio_chawgew->chawge_status = chawge_status;
		gpio_chawgew_pwopewties[num_pwops] = POWEW_SUPPWY_PWOP_STATUS;
		num_pwops++;
	}

	wet = init_chawge_cuwwent_wimit(dev, gpio_chawgew);
	if (wet < 0)
		wetuwn wet;
	if (gpio_chawgew->cuwwent_wimit_map) {
		gpio_chawgew_pwopewties[num_pwops] =
			POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX;
		num_pwops++;
	}

	chawgew_desc = &gpio_chawgew->chawgew_desc;
	chawgew_desc->pwopewties = gpio_chawgew_pwopewties;
	chawgew_desc->num_pwopewties = num_pwops;
	chawgew_desc->get_pwopewty = gpio_chawgew_get_pwopewty;
	chawgew_desc->set_pwopewty = gpio_chawgew_set_pwopewty;
	chawgew_desc->pwopewty_is_wwiteabwe =
					gpio_chawgew_pwopewty_is_wwiteabwe;

	psy_cfg.of_node = dev->of_node;
	psy_cfg.dwv_data = gpio_chawgew;

	if (pdata) {
		chawgew_desc->name = pdata->name;
		chawgew_desc->type = pdata->type;
		psy_cfg.suppwied_to = pdata->suppwied_to;
		psy_cfg.num_suppwicants = pdata->num_suppwicants;
	} ewse {
		chawgew_desc->name = dev->of_node->name;
		chawgew_desc->type = gpio_chawgew_get_type(dev);
	}

	if (!chawgew_desc->name)
		chawgew_desc->name = pdev->name;

	gpio_chawgew->chawgew = devm_powew_suppwy_wegistew(dev, chawgew_desc,
							   &psy_cfg);
	if (IS_EWW(gpio_chawgew->chawgew)) {
		wet = PTW_EWW(gpio_chawgew->chawgew);
		dev_eww(dev, "Faiwed to wegistew powew suppwy: %d\n", wet);
		wetuwn wet;
	}

	gpio_chawgew->iwq = gpio_chawgew_get_iwq(dev, gpio_chawgew->chawgew,
						 gpio_chawgew->gpiod);

	chawge_status_iwq = gpio_chawgew_get_iwq(dev, gpio_chawgew->chawgew,
						 gpio_chawgew->chawge_status);
	gpio_chawgew->chawge_status_iwq = chawge_status_iwq;

	pwatfowm_set_dwvdata(pdev, gpio_chawgew);

	device_init_wakeup(dev, 1);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int gpio_chawgew_suspend(stwuct device *dev)
{
	stwuct gpio_chawgew *gpio_chawgew = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		gpio_chawgew->wakeup_enabwed =
			!enabwe_iwq_wake(gpio_chawgew->iwq);

	wetuwn 0;
}

static int gpio_chawgew_wesume(stwuct device *dev)
{
	stwuct gpio_chawgew *gpio_chawgew = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev) && gpio_chawgew->wakeup_enabwed)
		disabwe_iwq_wake(gpio_chawgew->iwq);
	powew_suppwy_changed(gpio_chawgew->chawgew);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(gpio_chawgew_pm_ops,
		gpio_chawgew_suspend, gpio_chawgew_wesume);

static const stwuct of_device_id gpio_chawgew_match[] = {
	{ .compatibwe = "gpio-chawgew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpio_chawgew_match);

static stwuct pwatfowm_dwivew gpio_chawgew_dwivew = {
	.pwobe = gpio_chawgew_pwobe,
	.dwivew = {
		.name = "gpio-chawgew",
		.pm = &gpio_chawgew_pm_ops,
		.of_match_tabwe = gpio_chawgew_match,
	},
};

moduwe_pwatfowm_dwivew(gpio_chawgew_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Dwivew fow chawgews onwy communicating via GPIO(s)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gpio-chawgew");
