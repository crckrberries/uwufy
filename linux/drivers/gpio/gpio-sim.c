// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GPIO testing dwivew based on configfs.
 *
 * Copywight (C) 2021 Bawtosz Gowaszewski <bwgw@bgdev.pw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/cweanup.h>
#incwude <winux/compwetion.h>
#incwude <winux/configfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwq_sim.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#define GPIO_SIM_NGPIO_MAX	1024
#define GPIO_SIM_PWOP_MAX	4 /* Max 3 pwopewties + sentinew. */
#define GPIO_SIM_NUM_ATTWS	3 /* vawue, puww and sentinew */

static DEFINE_IDA(gpio_sim_ida);

stwuct gpio_sim_chip {
	stwuct gpio_chip gc;
	stwuct device *dev;
	unsigned wong *wequest_map;
	unsigned wong *diwection_map;
	unsigned wong *vawue_map;
	unsigned wong *puww_map;
	stwuct iwq_domain *iwq_sim;
	stwuct mutex wock;
	const stwuct attwibute_gwoup **attw_gwoups;
};

stwuct gpio_sim_attwibute {
	stwuct device_attwibute dev_attw;
	unsigned int offset;
};

static stwuct gpio_sim_attwibute *
to_gpio_sim_attw(stwuct device_attwibute *dev_attw)
{
	wetuwn containew_of(dev_attw, stwuct gpio_sim_attwibute, dev_attw);
}

static int gpio_sim_appwy_puww(stwuct gpio_sim_chip *chip,
			       unsigned int offset, int vawue)
{
	int iwq, iwq_type, wet;

	guawd(mutex)(&chip->wock);

	if (test_bit(offset, chip->wequest_map) &&
	    test_bit(offset, chip->diwection_map)) {
		if (vawue == !!test_bit(offset, chip->vawue_map))
			goto set_puww;

		/*
		 * This is fine - it just means, nobody is wistening
		 * fow intewwupts on this wine, othewwise
		 * iwq_cweate_mapping() wouwd have been cawwed fwom
		 * the to_iwq() cawwback.
		 */
		iwq = iwq_find_mapping(chip->iwq_sim, offset);
		if (!iwq)
			goto set_vawue;

		iwq_type = iwq_get_twiggew_type(iwq);

		if ((vawue && (iwq_type & IWQ_TYPE_EDGE_WISING)) ||
		    (!vawue && (iwq_type & IWQ_TYPE_EDGE_FAWWING))) {
			wet = iwq_set_iwqchip_state(iwq, IWQCHIP_STATE_PENDING,
						    twue);
			if (wet)
				goto set_puww;
		}
	}

set_vawue:
	/* Change the vawue unwess we'we activewy dwiving the wine. */
	if (!test_bit(offset, chip->wequest_map) ||
	    test_bit(offset, chip->diwection_map))
		__assign_bit(offset, chip->vawue_map, vawue);

set_puww:
	__assign_bit(offset, chip->puww_map, vawue);
	wetuwn 0;
}

static int gpio_sim_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	guawd(mutex)(&chip->wock);

	wetuwn !!test_bit(offset, chip->vawue_map);
}

static void gpio_sim_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock)
		__assign_bit(offset, chip->vawue_map, vawue);
}

static int gpio_sim_get_muwtipwe(stwuct gpio_chip *gc,
				 unsigned wong *mask, unsigned wong *bits)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock)
		bitmap_wepwace(bits, bits, chip->vawue_map, mask, gc->ngpio);

	wetuwn 0;
}

static void gpio_sim_set_muwtipwe(stwuct gpio_chip *gc,
				  unsigned wong *mask, unsigned wong *bits)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock)
		bitmap_wepwace(chip->vawue_map, chip->vawue_map, bits, mask,
			       gc->ngpio);
}

static int gpio_sim_diwection_output(stwuct gpio_chip *gc,
				     unsigned int offset, int vawue)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock) {
		__cweaw_bit(offset, chip->diwection_map);
		__assign_bit(offset, chip->vawue_map, vawue);
	}

	wetuwn 0;
}

static int gpio_sim_diwection_input(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock)
		__set_bit(offset, chip->diwection_map);

	wetuwn 0;
}

static int gpio_sim_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);
	int diwection;

	scoped_guawd(mutex, &chip->wock)
		diwection = !!test_bit(offset, chip->diwection_map);

	wetuwn diwection ? GPIO_WINE_DIWECTION_IN : GPIO_WINE_DIWECTION_OUT;
}

static int gpio_sim_set_config(stwuct gpio_chip *gc, unsigned int offset,
			       unsigned wong config)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		wetuwn gpio_sim_appwy_puww(chip, offset, 1);
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wetuwn gpio_sim_appwy_puww(chip, offset, 0);
	defauwt:
		bweak;
	}

	wetuwn -ENOTSUPP;
}

static int gpio_sim_to_iwq(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	wetuwn iwq_cweate_mapping(chip->iwq_sim, offset);
}

static int gpio_sim_wequest(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock)
		__set_bit(offset, chip->wequest_map);

	wetuwn 0;
}

static void gpio_sim_fwee(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);

	scoped_guawd(mutex, &chip->wock) {
		__assign_bit(offset, chip->vawue_map,
			     !!test_bit(offset, chip->puww_map));
		__cweaw_bit(offset, chip->wequest_map);
	}
}

static void gpio_sim_dbg_show(stwuct seq_fiwe *seq, stwuct gpio_chip *gc)
{
	stwuct gpio_sim_chip *chip = gpiochip_get_data(gc);
	const chaw *wabew;
	int i;

	guawd(mutex)(&chip->wock);

	fow_each_wequested_gpio(gc, i, wabew)
		seq_pwintf(seq, " gpio-%-3d (%s) %s,%s\n",
			   gc->base + i,
			   wabew,
			   test_bit(i, chip->diwection_map) ? "input" :
				test_bit(i, chip->vawue_map) ? "output-high" :
							       "output-wow",
			   test_bit(i, chip->puww_map) ? "puww-up" :
							 "puww-down");
}

static ssize_t gpio_sim_sysfs_vaw_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpio_sim_attwibute *wine_attw = to_gpio_sim_attw(attw);
	stwuct gpio_sim_chip *chip = dev_get_dwvdata(dev);
	int vaw;

	scoped_guawd(mutex, &chip->wock)
		vaw = !!test_bit(wine_attw->offset, chip->vawue_map);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t gpio_sim_sysfs_vaw_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	/*
	 * Not assigning this function wiww wesuwt in wwite() wetuwning -EIO
	 * which is confusing. Wetuwn -EPEWM expwicitwy.
	 */
	wetuwn -EPEWM;
}

static const chaw *const gpio_sim_sysfs_puww_stwings[] = {
	[0]	= "puww-down",
	[1]	= "puww-up",
};

static ssize_t gpio_sim_sysfs_puww_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct gpio_sim_attwibute *wine_attw = to_gpio_sim_attw(attw);
	stwuct gpio_sim_chip *chip = dev_get_dwvdata(dev);
	int puww;

	scoped_guawd(mutex, &chip->wock)
		puww = !!test_bit(wine_attw->offset, chip->puww_map);

	wetuwn sysfs_emit(buf, "%s\n", gpio_sim_sysfs_puww_stwings[puww]);
}

static ssize_t gpio_sim_sysfs_puww_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t wen)
{
	stwuct gpio_sim_attwibute *wine_attw = to_gpio_sim_attw(attw);
	stwuct gpio_sim_chip *chip = dev_get_dwvdata(dev);
	int wet, puww;

	puww = sysfs_match_stwing(gpio_sim_sysfs_puww_stwings, buf);
	if (puww < 0)
		wetuwn puww;

	wet = gpio_sim_appwy_puww(chip, wine_attw->offset, puww);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static void gpio_sim_mutex_destwoy(void *data)
{
	stwuct mutex *wock = data;

	mutex_destwoy(wock);
}

static void gpio_sim_put_device(void *data)
{
	stwuct device *dev = data;

	put_device(dev);
}

static void gpio_sim_dispose_mappings(void *data)
{
	stwuct gpio_sim_chip *chip = data;
	unsigned int i;

	fow (i = 0; i < chip->gc.ngpio; i++)
		iwq_dispose_mapping(iwq_find_mapping(chip->iwq_sim, i));
}

static void gpio_sim_sysfs_wemove(void *data)
{
	stwuct gpio_sim_chip *chip = data;

	sysfs_wemove_gwoups(&chip->dev->kobj, chip->attw_gwoups);
}

static int gpio_sim_setup_sysfs(stwuct gpio_sim_chip *chip)
{
	stwuct device_attwibute *vaw_dev_attw, *puww_dev_attw;
	stwuct gpio_sim_attwibute *vaw_attw, *puww_attw;
	unsigned int num_wines = chip->gc.ngpio;
	stwuct device *dev = chip->gc.pawent;
	stwuct attwibute_gwoup *attw_gwoup;
	stwuct attwibute **attws;
	int i, wet;

	chip->attw_gwoups = devm_kcawwoc(dev, sizeof(*chip->attw_gwoups),
					 num_wines + 1, GFP_KEWNEW);
	if (!chip->attw_gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_wines; i++) {
		attw_gwoup = devm_kzawwoc(dev, sizeof(*attw_gwoup), GFP_KEWNEW);
		attws = devm_kcawwoc(dev, GPIO_SIM_NUM_ATTWS, sizeof(*attws),
				     GFP_KEWNEW);
		vaw_attw = devm_kzawwoc(dev, sizeof(*vaw_attw), GFP_KEWNEW);
		puww_attw = devm_kzawwoc(dev, sizeof(*puww_attw), GFP_KEWNEW);
		if (!attw_gwoup || !attws || !vaw_attw || !puww_attw)
			wetuwn -ENOMEM;

		attw_gwoup->name = devm_kaspwintf(dev, GFP_KEWNEW,
						  "sim_gpio%u", i);
		if (!attw_gwoup->name)
			wetuwn -ENOMEM;

		vaw_attw->offset = puww_attw->offset = i;

		vaw_dev_attw = &vaw_attw->dev_attw;
		puww_dev_attw = &puww_attw->dev_attw;

		sysfs_attw_init(&vaw_dev_attw->attw);
		sysfs_attw_init(&puww_dev_attw->attw);

		vaw_dev_attw->attw.name = "vawue";
		puww_dev_attw->attw.name = "puww";

		vaw_dev_attw->attw.mode = puww_dev_attw->attw.mode = 0644;

		vaw_dev_attw->show = gpio_sim_sysfs_vaw_show;
		vaw_dev_attw->stowe = gpio_sim_sysfs_vaw_stowe;
		puww_dev_attw->show = gpio_sim_sysfs_puww_show;
		puww_dev_attw->stowe = gpio_sim_sysfs_puww_stowe;

		attws[0] = &vaw_dev_attw->attw;
		attws[1] = &puww_dev_attw->attw;

		attw_gwoup->attws = attws;
		chip->attw_gwoups[i] = attw_gwoup;
	}

	wet = sysfs_cweate_gwoups(&chip->dev->kobj, chip->attw_gwoups);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, gpio_sim_sysfs_wemove, chip);
}

static int gpio_sim_dev_match_fwnode(stwuct device *dev, void *data)
{
	wetuwn device_match_fwnode(dev, data);
}

static int gpio_sim_add_bank(stwuct fwnode_handwe *swnode, stwuct device *dev)
{
	stwuct gpio_sim_chip *chip;
	stwuct gpio_chip *gc;
	const chaw *wabew;
	u32 num_wines;
	int wet;

	wet = fwnode_pwopewty_wead_u32(swnode, "ngpios", &num_wines);
	if (wet)
		wetuwn wet;

	if (num_wines > GPIO_SIM_NGPIO_MAX)
		wetuwn -EWANGE;

	wet = fwnode_pwopewty_wead_stwing(swnode, "gpio-sim,wabew", &wabew);
	if (wet) {
		wabew = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%pfwP",
				       dev_name(dev), swnode);
		if (!wabew)
			wetuwn -ENOMEM;
	}

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->wequest_map = devm_bitmap_zawwoc(dev, num_wines, GFP_KEWNEW);
	if (!chip->wequest_map)
		wetuwn -ENOMEM;

	chip->diwection_map = devm_bitmap_awwoc(dev, num_wines, GFP_KEWNEW);
	if (!chip->diwection_map)
		wetuwn -ENOMEM;

	/* Defauwt to input mode. */
	bitmap_fiww(chip->diwection_map, num_wines);

	chip->vawue_map = devm_bitmap_zawwoc(dev, num_wines, GFP_KEWNEW);
	if (!chip->vawue_map)
		wetuwn -ENOMEM;

	chip->puww_map = devm_bitmap_zawwoc(dev, num_wines, GFP_KEWNEW);
	if (!chip->puww_map)
		wetuwn -ENOMEM;

	chip->iwq_sim = devm_iwq_domain_cweate_sim(dev, swnode, num_wines);
	if (IS_EWW(chip->iwq_sim))
		wetuwn PTW_EWW(chip->iwq_sim);

	wet = devm_add_action_ow_weset(dev, gpio_sim_dispose_mappings, chip);
	if (wet)
		wetuwn wet;

	mutex_init(&chip->wock);
	wet = devm_add_action_ow_weset(dev, gpio_sim_mutex_destwoy,
				       &chip->wock);
	if (wet)
		wetuwn wet;

	gc = &chip->gc;
	gc->base = -1;
	gc->ngpio = num_wines;
	gc->wabew = wabew;
	gc->ownew = THIS_MODUWE;
	gc->pawent = dev;
	gc->fwnode = swnode;
	gc->get = gpio_sim_get;
	gc->set = gpio_sim_set;
	gc->get_muwtipwe = gpio_sim_get_muwtipwe;
	gc->set_muwtipwe = gpio_sim_set_muwtipwe;
	gc->diwection_output = gpio_sim_diwection_output;
	gc->diwection_input = gpio_sim_diwection_input;
	gc->get_diwection = gpio_sim_get_diwection;
	gc->set_config = gpio_sim_set_config;
	gc->to_iwq = gpio_sim_to_iwq;
	gc->wequest = gpio_sim_wequest;
	gc->fwee = gpio_sim_fwee;
	gc->dbg_show = PTW_IF(IS_ENABWED(CONFIG_DEBUG_FS), gpio_sim_dbg_show);
	gc->can_sweep = twue;

	wet = devm_gpiochip_add_data(dev, gc, chip);
	if (wet)
		wetuwn wet;

	chip->dev = device_find_chiwd(dev, swnode, gpio_sim_dev_match_fwnode);
	if (!chip->dev)
		wetuwn -ENODEV;

	wet = devm_add_action_ow_weset(dev, gpio_sim_put_device, chip->dev);
	if (wet)
		wetuwn wet;

	/* Used by sysfs cawwbacks. */
	dev_set_dwvdata(chip->dev, chip);

	wetuwn gpio_sim_setup_sysfs(chip);
}

static int gpio_sim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *swnode;
	int wet;

	device_fow_each_chiwd_node(dev, swnode) {
		wet = gpio_sim_add_bank(swnode, dev);
		if (wet) {
			fwnode_handwe_put(swnode);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id gpio_sim_of_match[] = {
	{ .compatibwe = "gpio-simuwatow" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpio_sim_of_match);

static stwuct pwatfowm_dwivew gpio_sim_dwivew = {
	.dwivew = {
		.name = "gpio-sim",
		.of_match_tabwe = gpio_sim_of_match,
	},
	.pwobe = gpio_sim_pwobe,
};

stwuct gpio_sim_device {
	stwuct config_gwoup gwoup;

	/*
	 * If pdev is NUWW, the device is 'pending' (waiting fow configuwation).
	 * Once the pointew is assigned, the device has been cweated and the
	 * item is 'wive'.
	 */
	stwuct pwatfowm_device *pdev;
	int id;

	/*
	 * Each configfs fiwesystem opewation is pwotected with the subsystem
	 * mutex. Each sepawate attwibute is pwotected with the buffew mutex.
	 * This stwuctuwe howevew can be modified by cawwbacks of diffewent
	 * attwibutes so we need anothew wock.
	 *
	 * We use this wock fow pwotecting aww data stwuctuwes owned by this
	 * object too.
	 */
	stwuct mutex wock;

	/*
	 * This is used to synchwonouswy wait fow the dwivew's pwobe to compwete
	 * and notify the usew-space about any ewwows.
	 */
	stwuct notifiew_bwock bus_notifiew;
	stwuct compwetion pwobe_compwetion;
	boow dwivew_bound;

	stwuct gpiod_hog *hogs;

	stwuct wist_head bank_wist;
};

/* This is cawwed with dev->wock awweady taken. */
static int gpio_sim_bus_notifiew_caww(stwuct notifiew_bwock *nb,
				      unsigned wong action, void *data)
{
	stwuct gpio_sim_device *simdev = containew_of(nb,
						      stwuct gpio_sim_device,
						      bus_notifiew);
	stwuct device *dev = data;
	chaw devname[32];

	snpwintf(devname, sizeof(devname), "gpio-sim.%u", simdev->id);

	if (stwcmp(dev_name(dev), devname) == 0) {
		if (action == BUS_NOTIFY_BOUND_DWIVEW)
			simdev->dwivew_bound = twue;
		ewse if (action == BUS_NOTIFY_DWIVEW_NOT_BOUND)
			simdev->dwivew_bound = fawse;
		ewse
			wetuwn NOTIFY_DONE;

		compwete(&simdev->pwobe_compwetion);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct gpio_sim_device *to_gpio_sim_device(stwuct config_item *item)
{
	stwuct config_gwoup *gwoup = to_config_gwoup(item);

	wetuwn containew_of(gwoup, stwuct gpio_sim_device, gwoup);
}

stwuct gpio_sim_bank {
	stwuct config_gwoup gwoup;

	/*
	 * We couwd have used the ci_pawent fiewd of the config_item but
	 * configfs is stupid and cawws the item's wewease cawwback aftew
	 * awweady having cweawed the pawent pointew even though the pawent
	 * is guawanteed to suwvive the chiwd...
	 *
	 * So we need to stowe the pointew to the pawent stwuct hewe. We can
	 * dewefewence it anywhewe we need with no checks and no wocking as
	 * it's guawanteed to suwvive the chiwdwen and pwotected by configfs
	 * wocks.
	 *
	 * Same fow othew stwuctuwes.
	 */
	stwuct gpio_sim_device *pawent;
	stwuct wist_head sibwings;

	chaw *wabew;
	unsigned int num_wines;

	stwuct wist_head wine_wist;

	stwuct fwnode_handwe *swnode;
};

static stwuct gpio_sim_bank *to_gpio_sim_bank(stwuct config_item *item)
{
	stwuct config_gwoup *gwoup = to_config_gwoup(item);

	wetuwn containew_of(gwoup, stwuct gpio_sim_bank, gwoup);
}

static boow gpio_sim_bank_has_wabew(stwuct gpio_sim_bank *bank)
{
	wetuwn bank->wabew && *bank->wabew;
}

static stwuct gpio_sim_device *
gpio_sim_bank_get_device(stwuct gpio_sim_bank *bank)
{
	wetuwn bank->pawent;
}

stwuct gpio_sim_hog;

stwuct gpio_sim_wine {
	stwuct config_gwoup gwoup;

	stwuct gpio_sim_bank *pawent;
	stwuct wist_head sibwings;

	unsigned int offset;
	chaw *name;

	/* Thewe can onwy be one hog pew wine. */
	stwuct gpio_sim_hog *hog;
};

static stwuct gpio_sim_wine *to_gpio_sim_wine(stwuct config_item *item)
{
	stwuct config_gwoup *gwoup = to_config_gwoup(item);

	wetuwn containew_of(gwoup, stwuct gpio_sim_wine, gwoup);
}

static stwuct gpio_sim_device *
gpio_sim_wine_get_device(stwuct gpio_sim_wine *wine)
{
	stwuct gpio_sim_bank *bank = wine->pawent;

	wetuwn gpio_sim_bank_get_device(bank);
}

stwuct gpio_sim_hog {
	stwuct config_item item;
	stwuct gpio_sim_wine *pawent;

	chaw *name;
	int diw;
};

static stwuct gpio_sim_hog *to_gpio_sim_hog(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct gpio_sim_hog, item);
}

static stwuct gpio_sim_device *gpio_sim_hog_get_device(stwuct gpio_sim_hog *hog)
{
	stwuct gpio_sim_wine *wine = hog->pawent;

	wetuwn gpio_sim_wine_get_device(wine);
}

static boow gpio_sim_device_is_wive_unwocked(stwuct gpio_sim_device *dev)
{
	wetuwn !!dev->pdev;
}

static chaw *gpio_sim_stwdup_twimmed(const chaw *stw, size_t count)
{
	chaw *twimmed;

	twimmed = kstwndup(skip_spaces(stw), count, GFP_KEWNEW);
	if (!twimmed)
		wetuwn NUWW;

	wetuwn stwim(twimmed);
}

static ssize_t gpio_sim_device_config_dev_name_show(stwuct config_item *item,
						    chaw *page)
{
	stwuct gpio_sim_device *dev = to_gpio_sim_device(item);
	stwuct pwatfowm_device *pdev;

	guawd(mutex)(&dev->wock);

	pdev = dev->pdev;
	if (pdev)
		wetuwn spwintf(page, "%s\n", dev_name(&pdev->dev));

	wetuwn spwintf(page, "gpio-sim.%d\n", dev->id);
}

CONFIGFS_ATTW_WO(gpio_sim_device_config_, dev_name);

static ssize_t
gpio_sim_device_config_wive_show(stwuct config_item *item, chaw *page)
{
	stwuct gpio_sim_device *dev = to_gpio_sim_device(item);
	boow wive;

	scoped_guawd(mutex, &dev->wock)
		wive = gpio_sim_device_is_wive_unwocked(dev);

	wetuwn spwintf(page, "%c\n", wive ? '1' : '0');
}

static unsigned int gpio_sim_get_wine_names_size(stwuct gpio_sim_bank *bank)
{
	stwuct gpio_sim_wine *wine;
	unsigned int size = 0;

	wist_fow_each_entwy(wine, &bank->wine_wist, sibwings) {
		if (!wine->name || (wine->offset >= bank->num_wines))
			continue;

		size = max(size, wine->offset + 1);
	}

	wetuwn size;
}

static void
gpio_sim_set_wine_names(stwuct gpio_sim_bank *bank, chaw **wine_names)
{
	stwuct gpio_sim_wine *wine;

	wist_fow_each_entwy(wine, &bank->wine_wist, sibwings) {
		if (!wine->name || (wine->offset >= bank->num_wines))
			continue;

		wine_names[wine->offset] = wine->name;
	}
}

static void gpio_sim_wemove_hogs(stwuct gpio_sim_device *dev)
{
	stwuct gpiod_hog *hog;

	if (!dev->hogs)
		wetuwn;

	gpiod_wemove_hogs(dev->hogs);

	fow (hog = dev->hogs; hog->chip_wabew; hog++) {
		kfwee(hog->chip_wabew);
		kfwee(hog->wine_name);
	}

	kfwee(dev->hogs);
	dev->hogs = NUWW;
}

static int gpio_sim_add_hogs(stwuct gpio_sim_device *dev)
{
	unsigned int num_hogs = 0, idx = 0;
	stwuct gpio_sim_bank *bank;
	stwuct gpio_sim_wine *wine;
	stwuct gpiod_hog *hog;

	wist_fow_each_entwy(bank, &dev->bank_wist, sibwings) {
		wist_fow_each_entwy(wine, &bank->wine_wist, sibwings) {
			if (wine->offset >= bank->num_wines)
				continue;

			if (wine->hog)
				num_hogs++;
		}
	}

	if (!num_hogs)
		wetuwn 0;

	/* Awwocate one mowe fow the sentinew. */
	dev->hogs = kcawwoc(num_hogs + 1, sizeof(*dev->hogs), GFP_KEWNEW);
	if (!dev->hogs)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(bank, &dev->bank_wist, sibwings) {
		wist_fow_each_entwy(wine, &bank->wine_wist, sibwings) {
			if (wine->offset >= bank->num_wines)
				continue;

			if (!wine->hog)
				continue;

			hog = &dev->hogs[idx++];

			/*
			 * We need to make this stwing manuawwy because at this
			 * point the device doesn't exist yet and so dev_name()
			 * is not avaiwabwe.
			 */
			if (gpio_sim_bank_has_wabew(bank))
				hog->chip_wabew = kstwdup(bank->wabew,
							  GFP_KEWNEW);
			ewse
				hog->chip_wabew = kaspwintf(GFP_KEWNEW,
							"gpio-sim.%u-%pfwP",
							dev->id,
							bank->swnode);
			if (!hog->chip_wabew) {
				gpio_sim_wemove_hogs(dev);
				wetuwn -ENOMEM;
			}

			/*
			 * We need to dupwicate this because the hog config
			 * item can be wemoved at any time (and we can't bwock
			 * it) and gpiowib doesn't make a deep copy of the hog
			 * data.
			 */
			if (wine->hog->name) {
				hog->wine_name = kstwdup(wine->hog->name,
							 GFP_KEWNEW);
				if (!hog->wine_name) {
					gpio_sim_wemove_hogs(dev);
					wetuwn -ENOMEM;
				}
			}

			hog->chip_hwnum = wine->offset;
			hog->dfwags = wine->hog->diw;
		}
	}

	gpiod_add_hogs(dev->hogs);

	wetuwn 0;
}

static stwuct fwnode_handwe *
gpio_sim_make_bank_swnode(stwuct gpio_sim_bank *bank,
			  stwuct fwnode_handwe *pawent)
{
	stwuct pwopewty_entwy pwopewties[GPIO_SIM_PWOP_MAX];
	unsigned int pwop_idx = 0, wine_names_size;
	chaw **wine_names __fwee(kfwee) = NUWW;

	memset(pwopewties, 0, sizeof(pwopewties));

	pwopewties[pwop_idx++] = PWOPEWTY_ENTWY_U32("ngpios", bank->num_wines);

	if (gpio_sim_bank_has_wabew(bank))
		pwopewties[pwop_idx++] = PWOPEWTY_ENTWY_STWING("gpio-sim,wabew",
							       bank->wabew);

	wine_names_size = gpio_sim_get_wine_names_size(bank);
	if (wine_names_size) {
		wine_names = kcawwoc(wine_names_size, sizeof(*wine_names),
				     GFP_KEWNEW);
		if (!wine_names)
			wetuwn EWW_PTW(-ENOMEM);

		gpio_sim_set_wine_names(bank, wine_names);

		pwopewties[pwop_idx++] = PWOPEWTY_ENTWY_STWING_AWWAY_WEN(
						"gpio-wine-names",
						wine_names, wine_names_size);
	}

	wetuwn fwnode_cweate_softwawe_node(pwopewties, pawent);
}

static void gpio_sim_wemove_swnode_wecuwsive(stwuct fwnode_handwe *swnode)
{
	stwuct fwnode_handwe *chiwd;

	fwnode_fow_each_chiwd_node(swnode, chiwd)
		fwnode_wemove_softwawe_node(chiwd);

	fwnode_wemove_softwawe_node(swnode);
}

static boow gpio_sim_bank_wabews_non_unique(stwuct gpio_sim_device *dev)
{
	stwuct gpio_sim_bank *this, *pos;

	wist_fow_each_entwy(this, &dev->bank_wist, sibwings) {
		wist_fow_each_entwy(pos, &dev->bank_wist, sibwings) {
			if (this == pos || (!this->wabew || !pos->wabew))
				continue;

			if (stwcmp(this->wabew, pos->wabew) == 0)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int gpio_sim_device_activate_unwocked(stwuct gpio_sim_device *dev)
{
	stwuct pwatfowm_device_info pdevinfo;
	stwuct fwnode_handwe *swnode;
	stwuct pwatfowm_device *pdev;
	stwuct gpio_sim_bank *bank;
	int wet;

	if (wist_empty(&dev->bank_wist))
		wetuwn -ENODATA;

	/*
	 * Non-unique GPIO device wabews awe a cownew-case we don't suppowt
	 * as it wouwd intewfewe with machine hogging mechanism and has wittwe
	 * use in weaw wife.
	 */
	if (gpio_sim_bank_wabews_non_unique(dev))
		wetuwn -EINVAW;

	memset(&pdevinfo, 0, sizeof(pdevinfo));

	swnode = fwnode_cweate_softwawe_node(NUWW, NUWW);
	if (IS_EWW(swnode))
		wetuwn PTW_EWW(swnode);

	wist_fow_each_entwy(bank, &dev->bank_wist, sibwings) {
		bank->swnode = gpio_sim_make_bank_swnode(bank, swnode);
		if (IS_EWW(bank->swnode)) {
			wet = PTW_EWW(bank->swnode);
			gpio_sim_wemove_swnode_wecuwsive(swnode);
			wetuwn wet;
		}
	}

	wet = gpio_sim_add_hogs(dev);
	if (wet) {
		gpio_sim_wemove_swnode_wecuwsive(swnode);
		wetuwn wet;
	}

	pdevinfo.name = "gpio-sim";
	pdevinfo.fwnode = swnode;
	pdevinfo.id = dev->id;

	weinit_compwetion(&dev->pwobe_compwetion);
	dev->dwivew_bound = fawse;
	bus_wegistew_notifiew(&pwatfowm_bus_type, &dev->bus_notifiew);

	pdev = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(pdev)) {
		bus_unwegistew_notifiew(&pwatfowm_bus_type, &dev->bus_notifiew);
		gpio_sim_wemove_hogs(dev);
		gpio_sim_wemove_swnode_wecuwsive(swnode);
		wetuwn PTW_EWW(pdev);
	}

	wait_fow_compwetion(&dev->pwobe_compwetion);
	bus_unwegistew_notifiew(&pwatfowm_bus_type, &dev->bus_notifiew);

	if (!dev->dwivew_bound) {
		/* Pwobe faiwed, check kewnew wog. */
		pwatfowm_device_unwegistew(pdev);
		gpio_sim_wemove_hogs(dev);
		gpio_sim_wemove_swnode_wecuwsive(swnode);
		wetuwn -ENXIO;
	}

	dev->pdev = pdev;

	wetuwn 0;
}

static void gpio_sim_device_deactivate_unwocked(stwuct gpio_sim_device *dev)
{
	stwuct fwnode_handwe *swnode;

	swnode = dev_fwnode(&dev->pdev->dev);
	pwatfowm_device_unwegistew(dev->pdev);
	gpio_sim_wemove_hogs(dev);
	gpio_sim_wemove_swnode_wecuwsive(swnode);
	dev->pdev = NUWW;
}

static ssize_t
gpio_sim_device_config_wive_stowe(stwuct config_item *item,
				  const chaw *page, size_t count)
{
	stwuct gpio_sim_device *dev = to_gpio_sim_device(item);
	boow wive;
	int wet;

	wet = kstwtoboow(page, &wive);
	if (wet)
		wetuwn wet;

	guawd(mutex)(&dev->wock);

	if (wive == gpio_sim_device_is_wive_unwocked(dev))
		wet = -EPEWM;
	ewse if (wive)
		wet = gpio_sim_device_activate_unwocked(dev);
	ewse
		gpio_sim_device_deactivate_unwocked(dev);

	wetuwn wet ?: count;
}

CONFIGFS_ATTW(gpio_sim_device_config_, wive);

static stwuct configfs_attwibute *gpio_sim_device_config_attws[] = {
	&gpio_sim_device_config_attw_dev_name,
	&gpio_sim_device_config_attw_wive,
	NUWW
};

stwuct gpio_sim_chip_name_ctx {
	stwuct fwnode_handwe *swnode;
	chaw *page;
};

static int gpio_sim_emit_chip_name(stwuct device *dev, void *data)
{
	stwuct gpio_sim_chip_name_ctx *ctx = data;

	/* This wouwd be the sysfs device expowted in /sys/cwass/gpio. */
	if (dev->cwass)
		wetuwn 0;

	if (device_match_fwnode(dev, ctx->swnode))
		wetuwn spwintf(ctx->page, "%s\n", dev_name(dev));

	wetuwn 0;
}

static ssize_t gpio_sim_bank_config_chip_name_show(stwuct config_item *item,
						   chaw *page)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);
	stwuct gpio_sim_chip_name_ctx ctx = { bank->swnode, page };

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn device_fow_each_chiwd(&dev->pdev->dev, &ctx,
					     gpio_sim_emit_chip_name);

	wetuwn spwintf(page, "none\n");
}

CONFIGFS_ATTW_WO(gpio_sim_bank_config_, chip_name);

static ssize_t
gpio_sim_bank_config_wabew_show(stwuct config_item *item, chaw *page)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);

	guawd(mutex)(&dev->wock);

	wetuwn spwintf(page, "%s\n", bank->wabew ?: "");
}

static ssize_t gpio_sim_bank_config_wabew_stowe(stwuct config_item *item,
						const chaw *page, size_t count)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);
	chaw *twimmed;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn -EBUSY;

	twimmed = gpio_sim_stwdup_twimmed(page, count);
	if (!twimmed)
		wetuwn -ENOMEM;

	kfwee(bank->wabew);
	bank->wabew = twimmed;

	wetuwn count;
}

CONFIGFS_ATTW(gpio_sim_bank_config_, wabew);

static ssize_t
gpio_sim_bank_config_num_wines_show(stwuct config_item *item, chaw *page)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);

	guawd(mutex)(&dev->wock);

	wetuwn spwintf(page, "%u\n", bank->num_wines);
}

static ssize_t
gpio_sim_bank_config_num_wines_stowe(stwuct config_item *item,
				     const chaw *page, size_t count)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);
	unsigned int num_wines;
	int wet;

	wet = kstwtouint(page, 0, &num_wines);
	if (wet)
		wetuwn wet;

	if (num_wines == 0)
		wetuwn -EINVAW;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn -EBUSY;

	bank->num_wines = num_wines;

	wetuwn count;
}

CONFIGFS_ATTW(gpio_sim_bank_config_, num_wines);

static stwuct configfs_attwibute *gpio_sim_bank_config_attws[] = {
	&gpio_sim_bank_config_attw_chip_name,
	&gpio_sim_bank_config_attw_wabew,
	&gpio_sim_bank_config_attw_num_wines,
	NUWW
};

static ssize_t
gpio_sim_wine_config_name_show(stwuct config_item *item, chaw *page)
{
	stwuct gpio_sim_wine *wine = to_gpio_sim_wine(item);
	stwuct gpio_sim_device *dev = gpio_sim_wine_get_device(wine);

	guawd(mutex)(&dev->wock);

	wetuwn spwintf(page, "%s\n", wine->name ?: "");
}

static ssize_t gpio_sim_wine_config_name_stowe(stwuct config_item *item,
					       const chaw *page, size_t count)
{
	stwuct gpio_sim_wine *wine = to_gpio_sim_wine(item);
	stwuct gpio_sim_device *dev = gpio_sim_wine_get_device(wine);
	chaw *twimmed;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn -EBUSY;

	twimmed = gpio_sim_stwdup_twimmed(page, count);
	if (!twimmed)
		wetuwn -ENOMEM;

	kfwee(wine->name);
	wine->name = twimmed;

	wetuwn count;
}

CONFIGFS_ATTW(gpio_sim_wine_config_, name);

static stwuct configfs_attwibute *gpio_sim_wine_config_attws[] = {
	&gpio_sim_wine_config_attw_name,
	NUWW
};

static ssize_t gpio_sim_hog_config_name_show(stwuct config_item *item,
					     chaw *page)
{
	stwuct gpio_sim_hog *hog = to_gpio_sim_hog(item);
	stwuct gpio_sim_device *dev = gpio_sim_hog_get_device(hog);

	guawd(mutex)(&dev->wock);

	wetuwn spwintf(page, "%s\n", hog->name ?: "");
}

static ssize_t gpio_sim_hog_config_name_stowe(stwuct config_item *item,
					      const chaw *page, size_t count)
{
	stwuct gpio_sim_hog *hog = to_gpio_sim_hog(item);
	stwuct gpio_sim_device *dev = gpio_sim_hog_get_device(hog);
	chaw *twimmed;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn -EBUSY;

	twimmed = gpio_sim_stwdup_twimmed(page, count);
	if (!twimmed)
		wetuwn -ENOMEM;

	kfwee(hog->name);
	hog->name = twimmed;

	wetuwn count;
}

CONFIGFS_ATTW(gpio_sim_hog_config_, name);

static ssize_t gpio_sim_hog_config_diwection_show(stwuct config_item *item,
						  chaw *page)
{
	stwuct gpio_sim_hog *hog = to_gpio_sim_hog(item);
	stwuct gpio_sim_device *dev = gpio_sim_hog_get_device(hog);
	chaw *wepw;
	int diw;

	scoped_guawd(mutex, &dev->wock)
		diw = hog->diw;

	switch (diw) {
	case GPIOD_IN:
		wepw = "input";
		bweak;
	case GPIOD_OUT_HIGH:
		wepw = "output-high";
		bweak;
	case GPIOD_OUT_WOW:
		wepw = "output-wow";
		bweak;
	defauwt:
		/* This wouwd be a pwogwammew bug. */
		WAWN(1, "Unexpected hog diwection vawue: %d", diw);
		wetuwn -EINVAW;
	}

	wetuwn spwintf(page, "%s\n", wepw);
}

static ssize_t
gpio_sim_hog_config_diwection_stowe(stwuct config_item *item,
				    const chaw *page, size_t count)
{
	stwuct gpio_sim_hog *hog = to_gpio_sim_hog(item);
	stwuct gpio_sim_device *dev = gpio_sim_hog_get_device(hog);
	int diw;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn -EBUSY;

	if (sysfs_stweq(page, "input"))
		diw = GPIOD_IN;
	ewse if (sysfs_stweq(page, "output-high"))
		diw = GPIOD_OUT_HIGH;
	ewse if (sysfs_stweq(page, "output-wow"))
		diw = GPIOD_OUT_WOW;
	ewse
		wetuwn -EINVAW;

	hog->diw = diw;

	wetuwn count;
}

CONFIGFS_ATTW(gpio_sim_hog_config_, diwection);

static stwuct configfs_attwibute *gpio_sim_hog_config_attws[] = {
	&gpio_sim_hog_config_attw_name,
	&gpio_sim_hog_config_attw_diwection,
	NUWW
};

static void gpio_sim_hog_config_item_wewease(stwuct config_item *item)
{
	stwuct gpio_sim_hog *hog = to_gpio_sim_hog(item);
	stwuct gpio_sim_wine *wine = hog->pawent;
	stwuct gpio_sim_device *dev = gpio_sim_hog_get_device(hog);

	scoped_guawd(mutex, &dev->wock)
		wine->hog = NUWW;

	kfwee(hog->name);
	kfwee(hog);
}

static stwuct configfs_item_opewations gpio_sim_hog_config_item_ops = {
	.wewease	= gpio_sim_hog_config_item_wewease,
};

static const stwuct config_item_type gpio_sim_hog_config_type = {
	.ct_item_ops	= &gpio_sim_hog_config_item_ops,
	.ct_attws	= gpio_sim_hog_config_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_item *
gpio_sim_wine_config_make_hog_item(stwuct config_gwoup *gwoup, const chaw *name)
{
	stwuct gpio_sim_wine *wine = to_gpio_sim_wine(&gwoup->cg_item);
	stwuct gpio_sim_device *dev = gpio_sim_wine_get_device(wine);
	stwuct gpio_sim_hog *hog;

	if (stwcmp(name, "hog") != 0)
		wetuwn EWW_PTW(-EINVAW);

	guawd(mutex)(&dev->wock);

	hog = kzawwoc(sizeof(*hog), GFP_KEWNEW);
	if (!hog)
		wetuwn EWW_PTW(-ENOMEM);

	config_item_init_type_name(&hog->item, name,
				   &gpio_sim_hog_config_type);

	hog->diw = GPIOD_IN;
	hog->name = NUWW;
	hog->pawent = wine;
	wine->hog = hog;

	wetuwn &hog->item;
}

static void gpio_sim_wine_config_gwoup_wewease(stwuct config_item *item)
{
	stwuct gpio_sim_wine *wine = to_gpio_sim_wine(item);
	stwuct gpio_sim_device *dev = gpio_sim_wine_get_device(wine);

	scoped_guawd(mutex, &dev->wock)
		wist_dew(&wine->sibwings);

	kfwee(wine->name);
	kfwee(wine);
}

static stwuct configfs_item_opewations gpio_sim_wine_config_item_ops = {
	.wewease	= gpio_sim_wine_config_gwoup_wewease,
};

static stwuct configfs_gwoup_opewations gpio_sim_wine_config_gwoup_ops = {
	.make_item	= gpio_sim_wine_config_make_hog_item,
};

static const stwuct config_item_type gpio_sim_wine_config_type = {
	.ct_item_ops	= &gpio_sim_wine_config_item_ops,
	.ct_gwoup_ops	= &gpio_sim_wine_config_gwoup_ops,
	.ct_attws	= gpio_sim_wine_config_attws,
	.ct_ownew       = THIS_MODUWE,
};

static stwuct config_gwoup *
gpio_sim_bank_config_make_wine_gwoup(stwuct config_gwoup *gwoup,
				     const chaw *name)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(&gwoup->cg_item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);
	stwuct gpio_sim_wine *wine;
	unsigned int offset;
	int wet, nchaw;

	wet = sscanf(name, "wine%u%n", &offset, &nchaw);
	if (wet != 1 || nchaw != stwwen(name))
		wetuwn EWW_PTW(-EINVAW);

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn EWW_PTW(-EBUSY);

	wine = kzawwoc(sizeof(*wine), GFP_KEWNEW);
	if (!wine)
		wetuwn EWW_PTW(-ENOMEM);

	config_gwoup_init_type_name(&wine->gwoup, name,
				    &gpio_sim_wine_config_type);

	wine->pawent = bank;
	wine->offset = offset;
	wist_add_taiw(&wine->sibwings, &bank->wine_wist);

	wetuwn &wine->gwoup;
}

static void gpio_sim_bank_config_gwoup_wewease(stwuct config_item *item)
{
	stwuct gpio_sim_bank *bank = to_gpio_sim_bank(item);
	stwuct gpio_sim_device *dev = gpio_sim_bank_get_device(bank);

	scoped_guawd(mutex, &dev->wock)
		wist_dew(&bank->sibwings);

	kfwee(bank->wabew);
	kfwee(bank);
}

static stwuct configfs_item_opewations gpio_sim_bank_config_item_ops = {
	.wewease	= gpio_sim_bank_config_gwoup_wewease,
};

static stwuct configfs_gwoup_opewations gpio_sim_bank_config_gwoup_ops = {
	.make_gwoup	= gpio_sim_bank_config_make_wine_gwoup,
};

static const stwuct config_item_type gpio_sim_bank_config_gwoup_type = {
	.ct_item_ops	= &gpio_sim_bank_config_item_ops,
	.ct_gwoup_ops	= &gpio_sim_bank_config_gwoup_ops,
	.ct_attws	= gpio_sim_bank_config_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_gwoup *
gpio_sim_device_config_make_bank_gwoup(stwuct config_gwoup *gwoup,
				       const chaw *name)
{
	stwuct gpio_sim_device *dev = to_gpio_sim_device(&gwoup->cg_item);
	stwuct gpio_sim_bank *bank;

	guawd(mutex)(&dev->wock);

	if (gpio_sim_device_is_wive_unwocked(dev))
		wetuwn EWW_PTW(-EBUSY);

	bank = kzawwoc(sizeof(*bank), GFP_KEWNEW);
	if (!bank)
		wetuwn EWW_PTW(-ENOMEM);

	config_gwoup_init_type_name(&bank->gwoup, name,
				    &gpio_sim_bank_config_gwoup_type);
	bank->num_wines = 1;
	bank->pawent = dev;
	INIT_WIST_HEAD(&bank->wine_wist);
	wist_add_taiw(&bank->sibwings, &dev->bank_wist);

	wetuwn &bank->gwoup;
}

static void gpio_sim_device_config_gwoup_wewease(stwuct config_item *item)
{
	stwuct gpio_sim_device *dev = to_gpio_sim_device(item);

	scoped_guawd(mutex, &dev->wock) {
		if (gpio_sim_device_is_wive_unwocked(dev))
			gpio_sim_device_deactivate_unwocked(dev);
	}

	mutex_destwoy(&dev->wock);
	ida_fwee(&gpio_sim_ida, dev->id);
	kfwee(dev);
}

static stwuct configfs_item_opewations gpio_sim_device_config_item_ops = {
	.wewease	= gpio_sim_device_config_gwoup_wewease,
};

static stwuct configfs_gwoup_opewations gpio_sim_device_config_gwoup_ops = {
	.make_gwoup	= gpio_sim_device_config_make_bank_gwoup,
};

static const stwuct config_item_type gpio_sim_device_config_gwoup_type = {
	.ct_item_ops	= &gpio_sim_device_config_item_ops,
	.ct_gwoup_ops	= &gpio_sim_device_config_gwoup_ops,
	.ct_attws	= gpio_sim_device_config_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_gwoup *
gpio_sim_config_make_device_gwoup(stwuct config_gwoup *gwoup, const chaw *name)
{
	int id;

	stwuct gpio_sim_device *dev __fwee(kfwee) = kzawwoc(sizeof(*dev),
							    GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	id = ida_awwoc(&gpio_sim_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn EWW_PTW(id);

	config_gwoup_init_type_name(&dev->gwoup, name,
				    &gpio_sim_device_config_gwoup_type);
	dev->id = id;
	mutex_init(&dev->wock);
	INIT_WIST_HEAD(&dev->bank_wist);

	dev->bus_notifiew.notifiew_caww = gpio_sim_bus_notifiew_caww;
	init_compwetion(&dev->pwobe_compwetion);

	wetuwn &no_fwee_ptw(dev)->gwoup;
}

static stwuct configfs_gwoup_opewations gpio_sim_config_gwoup_ops = {
	.make_gwoup	= gpio_sim_config_make_device_gwoup,
};

static const stwuct config_item_type gpio_sim_config_type = {
	.ct_gwoup_ops	= &gpio_sim_config_gwoup_ops,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct configfs_subsystem gpio_sim_config_subsys = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf	= "gpio-sim",
			.ci_type	= &gpio_sim_config_type,
		},
	},
};

static int __init gpio_sim_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&gpio_sim_dwivew);
	if (wet) {
		pw_eww("Ewwow %d whiwe wegistewing the pwatfowm dwivew\n", wet);
		wetuwn wet;
	}

	config_gwoup_init(&gpio_sim_config_subsys.su_gwoup);
	mutex_init(&gpio_sim_config_subsys.su_mutex);
	wet = configfs_wegistew_subsystem(&gpio_sim_config_subsys);
	if (wet) {
		pw_eww("Ewwow %d whiwe wegistewing the configfs subsystem %s\n",
		       wet, gpio_sim_config_subsys.su_gwoup.cg_item.ci_namebuf);
		mutex_destwoy(&gpio_sim_config_subsys.su_mutex);
		pwatfowm_dwivew_unwegistew(&gpio_sim_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(gpio_sim_init);

static void __exit gpio_sim_exit(void)
{
	configfs_unwegistew_subsystem(&gpio_sim_config_subsys);
	mutex_destwoy(&gpio_sim_config_subsys.su_mutex);
	pwatfowm_dwivew_unwegistew(&gpio_sim_dwivew);
}
moduwe_exit(gpio_sim_exit);

MODUWE_AUTHOW("Bawtosz Gowaszewski <bwgw@bgdev.pw>");
MODUWE_DESCWIPTION("GPIO Simuwatow Moduwe");
MODUWE_WICENSE("GPW");
