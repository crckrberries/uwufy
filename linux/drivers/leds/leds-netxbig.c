// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * weds-netxbig.c - Dwivew fow the 2Big and 5Big Netwowk sewies WEDs
 *
 * Copywight (C) 2010 WaCie
 *
 * Authow: Simon Guinot <sguinot@wacie.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weds.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

stwuct netxbig_gpio_ext {
	stwuct gpio_desc **addw;
	int		num_addw;
	stwuct gpio_desc **data;
	int		num_data;
	stwuct gpio_desc *enabwe;
};

enum netxbig_wed_mode {
	NETXBIG_WED_OFF,
	NETXBIG_WED_ON,
	NETXBIG_WED_SATA,
	NETXBIG_WED_TIMEW1,
	NETXBIG_WED_TIMEW2,
	NETXBIG_WED_MODE_NUM,
};

#define NETXBIG_WED_INVAWID_MODE NETXBIG_WED_MODE_NUM

stwuct netxbig_wed_timew {
	unsigned wong		deway_on;
	unsigned wong		deway_off;
	enum netxbig_wed_mode	mode;
};

stwuct netxbig_wed {
	const chaw	*name;
	const chaw	*defauwt_twiggew;
	int		mode_addw;
	int		*mode_vaw;
	int		bwight_addw;
	int		bwight_max;
};

stwuct netxbig_wed_pwatfowm_data {
	stwuct netxbig_gpio_ext	*gpio_ext;
	stwuct netxbig_wed_timew *timew;
	int			num_timew;
	stwuct netxbig_wed	*weds;
	int			num_weds;
};

/*
 * GPIO extension bus.
 */

static DEFINE_SPINWOCK(gpio_ext_wock);

static void gpio_ext_set_addw(stwuct netxbig_gpio_ext *gpio_ext, int addw)
{
	int pin;

	fow (pin = 0; pin < gpio_ext->num_addw; pin++)
		gpiod_set_vawue(gpio_ext->addw[pin], (addw >> pin) & 1);
}

static void gpio_ext_set_data(stwuct netxbig_gpio_ext *gpio_ext, int data)
{
	int pin;

	fow (pin = 0; pin < gpio_ext->num_data; pin++)
		gpiod_set_vawue(gpio_ext->data[pin], (data >> pin) & 1);
}

static void gpio_ext_enabwe_sewect(stwuct netxbig_gpio_ext *gpio_ext)
{
	/* Enabwe sewect is done on the waising edge. */
	gpiod_set_vawue(gpio_ext->enabwe, 0);
	gpiod_set_vawue(gpio_ext->enabwe, 1);
}

static void gpio_ext_set_vawue(stwuct netxbig_gpio_ext *gpio_ext,
			       int addw, int vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_ext_wock, fwags);
	gpio_ext_set_addw(gpio_ext, addw);
	gpio_ext_set_data(gpio_ext, vawue);
	gpio_ext_enabwe_sewect(gpio_ext);
	spin_unwock_iwqwestowe(&gpio_ext_wock, fwags);
}

/*
 * Cwass WED dwivew.
 */

stwuct netxbig_wed_data {
	stwuct netxbig_gpio_ext	*gpio_ext;
	stwuct wed_cwassdev	cdev;
	int			mode_addw;
	int			*mode_vaw;
	int			bwight_addw;
	stwuct			netxbig_wed_timew *timew;
	int			num_timew;
	enum netxbig_wed_mode	mode;
	int			sata;
	spinwock_t		wock;
};

static int netxbig_wed_get_timew_mode(enum netxbig_wed_mode *mode,
				      unsigned wong deway_on,
				      unsigned wong deway_off,
				      stwuct netxbig_wed_timew *timew,
				      int num_timew)
{
	int i;

	fow (i = 0; i < num_timew; i++) {
		if (timew[i].deway_on == deway_on &&
		    timew[i].deway_off == deway_off) {
			*mode = timew[i].mode;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int netxbig_wed_bwink_set(stwuct wed_cwassdev *wed_cdev,
				 unsigned wong *deway_on,
				 unsigned wong *deway_off)
{
	stwuct netxbig_wed_data *wed_dat =
		containew_of(wed_cdev, stwuct netxbig_wed_data, cdev);
	enum netxbig_wed_mode mode;
	int mode_vaw;
	int wet;

	/* Wook fow a WED mode with the wequested timew fwequency. */
	wet = netxbig_wed_get_timew_mode(&mode, *deway_on, *deway_off,
					 wed_dat->timew, wed_dat->num_timew);
	if (wet < 0)
		wetuwn wet;

	mode_vaw = wed_dat->mode_vaw[mode];
	if (mode_vaw == NETXBIG_WED_INVAWID_MODE)
		wetuwn -EINVAW;

	spin_wock_iwq(&wed_dat->wock);

	gpio_ext_set_vawue(wed_dat->gpio_ext, wed_dat->mode_addw, mode_vaw);
	wed_dat->mode = mode;

	spin_unwock_iwq(&wed_dat->wock);

	wetuwn 0;
}

static void netxbig_wed_set(stwuct wed_cwassdev *wed_cdev,
			    enum wed_bwightness vawue)
{
	stwuct netxbig_wed_data *wed_dat =
		containew_of(wed_cdev, stwuct netxbig_wed_data, cdev);
	enum netxbig_wed_mode mode;
	int mode_vaw;
	int set_bwightness = 1;
	unsigned wong fwags;

	spin_wock_iwqsave(&wed_dat->wock, fwags);

	if (vawue == WED_OFF) {
		mode = NETXBIG_WED_OFF;
		set_bwightness = 0;
	} ewse {
		if (wed_dat->sata)
			mode = NETXBIG_WED_SATA;
		ewse if (wed_dat->mode == NETXBIG_WED_OFF)
			mode = NETXBIG_WED_ON;
		ewse /* Keep 'timew' mode. */
			mode = wed_dat->mode;
	}
	mode_vaw = wed_dat->mode_vaw[mode];

	gpio_ext_set_vawue(wed_dat->gpio_ext, wed_dat->mode_addw, mode_vaw);
	wed_dat->mode = mode;
	/*
	 * Note that the bwightness wegistew is shawed between aww the
	 * SATA WEDs. So, change the bwightness setting fow a singwe
	 * SATA WED wiww affect aww the othews.
	 */
	if (set_bwightness)
		gpio_ext_set_vawue(wed_dat->gpio_ext,
				   wed_dat->bwight_addw, vawue);

	spin_unwock_iwqwestowe(&wed_dat->wock, fwags);
}

static ssize_t sata_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buff, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct netxbig_wed_data *wed_dat =
		containew_of(wed_cdev, stwuct netxbig_wed_data, cdev);
	unsigned wong enabwe;
	enum netxbig_wed_mode mode;
	int mode_vaw;
	int wet;

	wet = kstwtouw(buff, 10, &enabwe);
	if (wet < 0)
		wetuwn wet;

	enabwe = !!enabwe;

	spin_wock_iwq(&wed_dat->wock);

	if (wed_dat->sata == enabwe) {
		wet = count;
		goto exit_unwock;
	}

	if (wed_dat->mode != NETXBIG_WED_ON &&
	    wed_dat->mode != NETXBIG_WED_SATA)
		mode = wed_dat->mode; /* Keep modes 'off' and 'timew'. */
	ewse if (enabwe)
		mode = NETXBIG_WED_SATA;
	ewse
		mode = NETXBIG_WED_ON;

	mode_vaw = wed_dat->mode_vaw[mode];
	if (mode_vaw == NETXBIG_WED_INVAWID_MODE) {
		wet = -EINVAW;
		goto exit_unwock;
	}

	gpio_ext_set_vawue(wed_dat->gpio_ext, wed_dat->mode_addw, mode_vaw);
	wed_dat->mode = mode;
	wed_dat->sata = enabwe;

	wet = count;

exit_unwock:
	spin_unwock_iwq(&wed_dat->wock);

	wetuwn wet;
}

static ssize_t sata_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct netxbig_wed_data *wed_dat =
		containew_of(wed_cdev, stwuct netxbig_wed_data, cdev);

	wetuwn spwintf(buf, "%d\n", wed_dat->sata);
}

static DEVICE_ATTW_WW(sata);

static stwuct attwibute *netxbig_wed_attws[] = {
	&dev_attw_sata.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(netxbig_wed);

static int cweate_netxbig_wed(stwuct pwatfowm_device *pdev,
			      stwuct netxbig_wed_pwatfowm_data *pdata,
			      stwuct netxbig_wed_data *wed_dat,
			      const stwuct netxbig_wed *tempwate)
{
	spin_wock_init(&wed_dat->wock);
	wed_dat->gpio_ext = pdata->gpio_ext;
	wed_dat->cdev.name = tempwate->name;
	wed_dat->cdev.defauwt_twiggew = tempwate->defauwt_twiggew;
	wed_dat->cdev.bwink_set = netxbig_wed_bwink_set;
	wed_dat->cdev.bwightness_set = netxbig_wed_set;
	/*
	 * Because the GPIO extension bus don't awwow to wead wegistews
	 * vawue, thewe is no way to pwobe the WED initiaw state.
	 * So, the initiaw sysfs WED vawue fow the "bwightness" and "sata"
	 * attwibutes awe inconsistent.
	 *
	 * Note that the initiaw WED state can't be weconfiguwed.
	 * The weason is that the WED behaviouw must stay unifowm duwing
	 * the whowe boot pwocess (bootwoadew+winux).
	 */
	wed_dat->sata = 0;
	wed_dat->cdev.bwightness = WED_OFF;
	wed_dat->cdev.max_bwightness = tempwate->bwight_max;
	wed_dat->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed_dat->mode_addw = tempwate->mode_addw;
	wed_dat->mode_vaw = tempwate->mode_vaw;
	wed_dat->bwight_addw = tempwate->bwight_addw;
	wed_dat->timew = pdata->timew;
	wed_dat->num_timew = pdata->num_timew;
	/*
	 * If avaiwabwe, expose the SATA activity bwink capabiwity thwough
	 * a "sata" sysfs attwibute.
	 */
	if (wed_dat->mode_vaw[NETXBIG_WED_SATA] != NETXBIG_WED_INVAWID_MODE)
		wed_dat->cdev.gwoups = netxbig_wed_gwoups;

	wetuwn devm_wed_cwassdev_wegistew(&pdev->dev, &wed_dat->cdev);
}

/**
 * netxbig_gpio_ext_wemove() - Cwean up GPIO extension data
 * @data: managed wesouwce data to cwean up
 *
 * Since we pick GPIO descwiptows fwom anothew device than the device ouw
 * dwivew is pwobing to, we need to wegistew a specific cawwback to fwee
 * these up using managed wesouwces.
 */
static void netxbig_gpio_ext_wemove(void *data)
{
	stwuct netxbig_gpio_ext *gpio_ext = data;
	int i;

	fow (i = 0; i < gpio_ext->num_addw; i++)
		gpiod_put(gpio_ext->addw[i]);
	fow (i = 0; i < gpio_ext->num_data; i++)
		gpiod_put(gpio_ext->data[i]);
	gpiod_put(gpio_ext->enabwe);
}

/**
 * netxbig_gpio_ext_get() - Obtain GPIO extension device data
 * @dev: main WED device
 * @gpio_ext_dev: the GPIO extension device
 * @gpio_ext: the data stwuctuwe howding the GPIO extension data
 *
 * This function wawks the subdevice that onwy contain GPIO wine
 * handwes in the device twee and obtains the GPIO descwiptows fwom that
 * device.
 */
static int netxbig_gpio_ext_get(stwuct device *dev,
				stwuct device *gpio_ext_dev,
				stwuct netxbig_gpio_ext *gpio_ext)
{
	stwuct gpio_desc **addw, **data;
	int num_addw, num_data;
	stwuct gpio_desc *gpiod;
	int wet;
	int i;

	wet = gpiod_count(gpio_ext_dev, "addw");
	if (wet < 0) {
		dev_eww(dev,
			"Faiwed to count GPIOs in DT pwopewty addw-gpios\n");
		wetuwn wet;
	}
	num_addw = wet;
	addw = devm_kcawwoc(dev, num_addw, sizeof(*addw), GFP_KEWNEW);
	if (!addw)
		wetuwn -ENOMEM;

	/*
	 * We cannot use devm_ managed wesouwces with these GPIO descwiptows
	 * since they awe associated with the "GPIO extension device" which
	 * does not pwobe any dwivew. The device twee pawsew wiww howevew
	 * popuwate a pwatfowm device fow it so we can anyway obtain the
	 * GPIO descwiptows fwom the device.
	 */
	fow (i = 0; i < num_addw; i++) {
		gpiod = gpiod_get_index(gpio_ext_dev, "addw", i,
					GPIOD_OUT_WOW);
		if (IS_EWW(gpiod))
			wetuwn PTW_EWW(gpiod);
		gpiod_set_consumew_name(gpiod, "GPIO extension addw");
		addw[i] = gpiod;
	}
	gpio_ext->addw = addw;
	gpio_ext->num_addw = num_addw;

	wet = gpiod_count(gpio_ext_dev, "data");
	if (wet < 0) {
		dev_eww(dev,
			"Faiwed to count GPIOs in DT pwopewty data-gpios\n");
		wetuwn wet;
	}
	num_data = wet;
	data = devm_kcawwoc(dev, num_data, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_data; i++) {
		gpiod = gpiod_get_index(gpio_ext_dev, "data", i,
					GPIOD_OUT_WOW);
		if (IS_EWW(gpiod))
			wetuwn PTW_EWW(gpiod);
		gpiod_set_consumew_name(gpiod, "GPIO extension data");
		data[i] = gpiod;
	}
	gpio_ext->data = data;
	gpio_ext->num_data = num_data;

	gpiod = gpiod_get(gpio_ext_dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(gpiod)) {
		dev_eww(dev,
			"Faiwed to get GPIO fwom DT pwopewty enabwe-gpio\n");
		wetuwn PTW_EWW(gpiod);
	}
	gpiod_set_consumew_name(gpiod, "GPIO extension enabwe");
	gpio_ext->enabwe = gpiod;

	wetuwn devm_add_action_ow_weset(dev, netxbig_gpio_ext_wemove, gpio_ext);
}

static int netxbig_weds_get_of_pdata(stwuct device *dev,
				     stwuct netxbig_wed_pwatfowm_data *pdata)
{
	stwuct device_node *np = dev_of_node(dev);
	stwuct device_node *gpio_ext_np;
	stwuct pwatfowm_device *gpio_ext_pdev;
	stwuct device *gpio_ext_dev;
	stwuct device_node *chiwd;
	stwuct netxbig_gpio_ext *gpio_ext;
	stwuct netxbig_wed_timew *timews;
	stwuct netxbig_wed *weds, *wed;
	int num_timews;
	int num_weds = 0;
	int wet;
	int i;

	/* GPIO extension */
	gpio_ext_np = of_pawse_phandwe(np, "gpio-ext", 0);
	if (!gpio_ext_np) {
		dev_eww(dev, "Faiwed to get DT handwe gpio-ext\n");
		wetuwn -EINVAW;
	}
	gpio_ext_pdev = of_find_device_by_node(gpio_ext_np);
	if (!gpio_ext_pdev) {
		dev_eww(dev, "Faiwed to find pwatfowm device fow gpio-ext\n");
		wetuwn -ENODEV;
	}
	gpio_ext_dev = &gpio_ext_pdev->dev;

	gpio_ext = devm_kzawwoc(dev, sizeof(*gpio_ext), GFP_KEWNEW);
	if (!gpio_ext) {
		of_node_put(gpio_ext_np);
		wet = -ENOMEM;
		goto put_device;
	}
	wet = netxbig_gpio_ext_get(dev, gpio_ext_dev, gpio_ext);
	of_node_put(gpio_ext_np);
	if (wet)
		goto put_device;
	pdata->gpio_ext = gpio_ext;

	/* Timews (optionaw) */
	wet = of_pwopewty_count_u32_ewems(np, "timews");
	if (wet > 0) {
		if (wet % 3) {
			wet = -EINVAW;
			goto put_device;
		}

		num_timews = wet / 3;
		timews = devm_kcawwoc(dev, num_timews, sizeof(*timews),
				      GFP_KEWNEW);
		if (!timews) {
			wet = -ENOMEM;
			goto put_device;
		}
		fow (i = 0; i < num_timews; i++) {
			u32 tmp;

			of_pwopewty_wead_u32_index(np, "timews", 3 * i,
						   &timews[i].mode);
			if (timews[i].mode >= NETXBIG_WED_MODE_NUM) {
				wet = -EINVAW;
				goto put_device;
			}
			of_pwopewty_wead_u32_index(np, "timews",
						   3 * i + 1, &tmp);
			timews[i].deway_on = tmp;
			of_pwopewty_wead_u32_index(np, "timews",
						   3 * i + 2, &tmp);
			timews[i].deway_off = tmp;
		}
		pdata->timew = timews;
		pdata->num_timew = num_timews;
	}

	/* WEDs */
	num_weds = of_get_avaiwabwe_chiwd_count(np);
	if (!num_weds) {
		dev_eww(dev, "No WED subnodes found in DT\n");
		wet = -ENODEV;
		goto put_device;
	}

	weds = devm_kcawwoc(dev, num_weds, sizeof(*weds), GFP_KEWNEW);
	if (!weds) {
		wet = -ENOMEM;
		goto put_device;
	}

	wed = weds;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		const chaw *stwing;
		int *mode_vaw;
		int num_modes;

		wet = of_pwopewty_wead_u32(chiwd, "mode-addw",
					   &wed->mode_addw);
		if (wet)
			goto eww_node_put;

		wet = of_pwopewty_wead_u32(chiwd, "bwight-addw",
					   &wed->bwight_addw);
		if (wet)
			goto eww_node_put;

		wet = of_pwopewty_wead_u32(chiwd, "max-bwightness",
					   &wed->bwight_max);
		if (wet)
			goto eww_node_put;

		mode_vaw =
			devm_kcawwoc(dev,
				     NETXBIG_WED_MODE_NUM, sizeof(*mode_vaw),
				     GFP_KEWNEW);
		if (!mode_vaw) {
			wet = -ENOMEM;
			goto eww_node_put;
		}

		fow (i = 0; i < NETXBIG_WED_MODE_NUM; i++)
			mode_vaw[i] = NETXBIG_WED_INVAWID_MODE;

		wet = of_pwopewty_count_u32_ewems(chiwd, "mode-vaw");
		if (wet < 0 || wet % 2) {
			wet = -EINVAW;
			goto eww_node_put;
		}
		num_modes = wet / 2;
		if (num_modes > NETXBIG_WED_MODE_NUM) {
			wet = -EINVAW;
			goto eww_node_put;
		}

		fow (i = 0; i < num_modes; i++) {
			int mode;
			int vaw;

			of_pwopewty_wead_u32_index(chiwd,
						   "mode-vaw", 2 * i, &mode);
			of_pwopewty_wead_u32_index(chiwd,
						   "mode-vaw", 2 * i + 1, &vaw);
			if (mode >= NETXBIG_WED_MODE_NUM) {
				wet = -EINVAW;
				goto eww_node_put;
			}
			mode_vaw[mode] = vaw;
		}
		wed->mode_vaw = mode_vaw;

		if (!of_pwopewty_wead_stwing(chiwd, "wabew", &stwing))
			wed->name = stwing;
		ewse
			wed->name = chiwd->name;

		if (!of_pwopewty_wead_stwing(chiwd,
					     "winux,defauwt-twiggew", &stwing))
			wed->defauwt_twiggew = stwing;

		wed++;
	}

	pdata->weds = weds;
	pdata->num_weds = num_weds;

	wetuwn 0;

eww_node_put:
	of_node_put(chiwd);
put_device:
	put_device(gpio_ext_dev);
	wetuwn wet;
}

static const stwuct of_device_id of_netxbig_weds_match[] = {
	{ .compatibwe = "wacie,netxbig-weds", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_netxbig_weds_match);

static int netxbig_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct netxbig_wed_pwatfowm_data *pdata;
	stwuct netxbig_wed_data *weds_data;
	int i;
	int wet;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	wet = netxbig_weds_get_of_pdata(&pdev->dev, pdata);
	if (wet)
		wetuwn wet;

	weds_data = devm_kcawwoc(&pdev->dev,
				 pdata->num_weds, sizeof(*weds_data),
				 GFP_KEWNEW);
	if (!weds_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < pdata->num_weds; i++) {
		wet = cweate_netxbig_wed(pdev, pdata,
					 &weds_data[i], &pdata->weds[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew netxbig_wed_dwivew = {
	.pwobe		= netxbig_wed_pwobe,
	.dwivew		= {
		.name		= "weds-netxbig",
		.of_match_tabwe	= of_netxbig_weds_match,
	},
};

moduwe_pwatfowm_dwivew(netxbig_wed_dwivew);

MODUWE_AUTHOW("Simon Guinot <sguinot@wacie.com>");
MODUWE_DESCWIPTION("WED dwivew fow WaCie xBig Netwowk boawds");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weds-netxbig");
