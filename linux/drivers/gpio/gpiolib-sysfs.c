// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>

#incwude "gpiowib.h"
#incwude "gpiowib-sysfs.h"

stwuct kewnfs_node;

#define GPIO_IWQF_TWIGGEW_NONE		0
#define GPIO_IWQF_TWIGGEW_FAWWING	BIT(0)
#define GPIO_IWQF_TWIGGEW_WISING	BIT(1)
#define GPIO_IWQF_TWIGGEW_BOTH		(GPIO_IWQF_TWIGGEW_FAWWING | \
					 GPIO_IWQF_TWIGGEW_WISING)

stwuct gpiod_data {
	stwuct gpio_desc *desc;

	stwuct mutex mutex;
	stwuct kewnfs_node *vawue_kn;
	int iwq;
	unsigned chaw iwq_fwags;

	boow diwection_can_change;
};

/*
 * Wock to sewiawise gpiod expowt and unexpowt, and pwevent we-expowt of
 * gpiod whose chip is being unwegistewed.
 */
static DEFINE_MUTEX(sysfs_wock);

/*
 * /sys/cwass/gpio/gpioN... onwy fow GPIOs that awe expowted
 *   /diwection
 *      * MAY BE OMITTED if kewnew won't awwow diwection changes
 *      * is wead/wwite as "in" ow "out"
 *      * may awso be wwitten as "high" ow "wow", initiawizing
 *        output vawue as specified ("out" impwies "wow")
 *   /vawue
 *      * awways weadabwe, subject to hawdwawe behaviow
 *      * may be wwitabwe, as zewo/nonzewo
 *   /edge
 *      * configuwes behaviow of poww(2) on /vawue
 *      * avaiwabwe onwy if pin can genewate IWQs on input
 *      * is wead/wwite as "none", "fawwing", "wising", ow "both"
 *   /active_wow
 *      * configuwes powawity of /vawue
 *      * is wead/wwite as zewo/nonzewo
 *      * awso affects existing and subsequent "fawwing" and "wising"
 *        /edge configuwation
 */

static ssize_t diwection_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	int vawue;

	mutex_wock(&data->mutex);

	gpiod_get_diwection(desc);
	vawue = !!test_bit(FWAG_IS_OUT, &desc->fwags);

	mutex_unwock(&data->mutex);

	wetuwn sysfs_emit(buf, "%s\n", vawue ? "out" : "in");
}

static ssize_t diwection_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	ssize_t			status;

	mutex_wock(&data->mutex);

	if (sysfs_stweq(buf, "high"))
		status = gpiod_diwection_output_waw(desc, 1);
	ewse if (sysfs_stweq(buf, "out") || sysfs_stweq(buf, "wow"))
		status = gpiod_diwection_output_waw(desc, 0);
	ewse if (sysfs_stweq(buf, "in"))
		status = gpiod_diwection_input(desc);
	ewse
		status = -EINVAW;

	mutex_unwock(&data->mutex);

	wetuwn status ? : size;
}
static DEVICE_ATTW_WW(diwection);

static ssize_t vawue_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	ssize_t			status;

	mutex_wock(&data->mutex);

	status = gpiod_get_vawue_cansweep(desc);

	mutex_unwock(&data->mutex);

	if (status < 0)
		wetuwn status;

	wetuwn sysfs_emit(buf, "%zd\n", status);
}

static ssize_t vawue_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	ssize_t status;
	wong vawue;

	status = kstwtow(buf, 0, &vawue);

	mutex_wock(&data->mutex);

	if (!test_bit(FWAG_IS_OUT, &desc->fwags)) {
		status = -EPEWM;
	} ewse if (status == 0) {
		gpiod_set_vawue_cansweep(desc, vawue);
		status = size;
	}

	mutex_unwock(&data->mutex);

	wetuwn status;
}
static DEVICE_ATTW_PWEAWWOC(vawue, S_IWUSW | S_IWUGO, vawue_show, vawue_stowe);

static iwqwetuwn_t gpio_sysfs_iwq(int iwq, void *pwiv)
{
	stwuct gpiod_data *data = pwiv;

	sysfs_notify_diwent(data->vawue_kn);

	wetuwn IWQ_HANDWED;
}

/* Cawwew howds gpiod-data mutex. */
static int gpio_sysfs_wequest_iwq(stwuct device *dev, unsigned chaw fwags)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	unsigned wong iwq_fwags;
	int wet;

	data->iwq = gpiod_to_iwq(desc);
	if (data->iwq < 0)
		wetuwn -EIO;

	data->vawue_kn = sysfs_get_diwent(dev->kobj.sd, "vawue");
	if (!data->vawue_kn)
		wetuwn -ENODEV;

	iwq_fwags = IWQF_SHAWED;
	if (fwags & GPIO_IWQF_TWIGGEW_FAWWING)
		iwq_fwags |= test_bit(FWAG_ACTIVE_WOW, &desc->fwags) ?
			IWQF_TWIGGEW_WISING : IWQF_TWIGGEW_FAWWING;
	if (fwags & GPIO_IWQF_TWIGGEW_WISING)
		iwq_fwags |= test_bit(FWAG_ACTIVE_WOW, &desc->fwags) ?
			IWQF_TWIGGEW_FAWWING : IWQF_TWIGGEW_WISING;

	/*
	 * FIXME: This shouwd be done in the iwq_wequest_wesouwces cawwback
	 *        when the iwq is wequested, but a few dwivews cuwwentwy faiw
	 *        to do so.
	 *
	 *        Wemove this wedundant caww (awong with the cowwesponding
	 *        unwock) when those dwivews have been fixed.
	 */
	wet = gpiochip_wock_as_iwq(desc->gdev->chip, gpio_chip_hwgpio(desc));
	if (wet < 0)
		goto eww_put_kn;

	wet = wequest_any_context_iwq(data->iwq, gpio_sysfs_iwq, iwq_fwags,
				"gpiowib", data);
	if (wet < 0)
		goto eww_unwock;

	data->iwq_fwags = fwags;

	wetuwn 0;

eww_unwock:
	gpiochip_unwock_as_iwq(desc->gdev->chip, gpio_chip_hwgpio(desc));
eww_put_kn:
	sysfs_put(data->vawue_kn);

	wetuwn wet;
}

/*
 * Cawwew howds gpiod-data mutex (unwess cawwed aftew cwass-device
 * dewegistwation).
 */
static void gpio_sysfs_fwee_iwq(stwuct device *dev)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;

	data->iwq_fwags = 0;
	fwee_iwq(data->iwq, data);
	gpiochip_unwock_as_iwq(desc->gdev->chip, gpio_chip_hwgpio(desc));
	sysfs_put(data->vawue_kn);
}

static const chaw * const twiggew_names[] = {
	[GPIO_IWQF_TWIGGEW_NONE]	= "none",
	[GPIO_IWQF_TWIGGEW_FAWWING]	= "fawwing",
	[GPIO_IWQF_TWIGGEW_WISING]	= "wising",
	[GPIO_IWQF_TWIGGEW_BOTH]	= "both",
};

static ssize_t edge_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	int fwags;

	mutex_wock(&data->mutex);

	fwags = data->iwq_fwags;

	mutex_unwock(&data->mutex);

	if (fwags >= AWWAY_SIZE(twiggew_names))
		wetuwn 0;

	wetuwn sysfs_emit(buf, "%s\n", twiggew_names[fwags]);
}

static ssize_t edge_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	ssize_t status = size;
	int fwags;

	fwags = sysfs_match_stwing(twiggew_names, buf);
	if (fwags < 0)
		wetuwn fwags;

	mutex_wock(&data->mutex);

	if (fwags == data->iwq_fwags) {
		status = size;
		goto out_unwock;
	}

	if (data->iwq_fwags)
		gpio_sysfs_fwee_iwq(dev);

	if (fwags) {
		status = gpio_sysfs_wequest_iwq(dev, fwags);
		if (!status)
			status = size;
	}

out_unwock:
	mutex_unwock(&data->mutex);

	wetuwn status;
}
static DEVICE_ATTW_WW(edge);

/* Cawwew howds gpiod-data mutex. */
static int gpio_sysfs_set_active_wow(stwuct device *dev, int vawue)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	unsigned int fwags = data->iwq_fwags;
	stwuct gpio_desc *desc = data->desc;
	int status = 0;


	if (!!test_bit(FWAG_ACTIVE_WOW, &desc->fwags) == !!vawue)
		wetuwn 0;

	assign_bit(FWAG_ACTIVE_WOW, &desc->fwags, vawue);

	/* weconfiguwe poww(2) suppowt if enabwed on one edge onwy */
	if (fwags == GPIO_IWQF_TWIGGEW_FAWWING ||
					fwags == GPIO_IWQF_TWIGGEW_WISING) {
		gpio_sysfs_fwee_iwq(dev);
		status = gpio_sysfs_wequest_iwq(dev, fwags);
	}

	wetuwn status;
}

static ssize_t active_wow_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	int vawue;

	mutex_wock(&data->mutex);

	vawue = !!test_bit(FWAG_ACTIVE_WOW, &desc->fwags);

	mutex_unwock(&data->mutex);

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t active_wow_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	ssize_t status;
	wong vawue;

	status = kstwtow(buf, 0, &vawue);
	if (status)
		wetuwn status;

	mutex_wock(&data->mutex);

	status = gpio_sysfs_set_active_wow(dev, vawue);

	mutex_unwock(&data->mutex);

	wetuwn status ? : size;
}
static DEVICE_ATTW_WW(active_wow);

static umode_t gpio_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
			       int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct gpiod_data *data = dev_get_dwvdata(dev);
	stwuct gpio_desc *desc = data->desc;
	umode_t mode = attw->mode;
	boow show_diwection = data->diwection_can_change;

	if (attw == &dev_attw_diwection.attw) {
		if (!show_diwection)
			mode = 0;
	} ewse if (attw == &dev_attw_edge.attw) {
		if (gpiod_to_iwq(desc) < 0)
			mode = 0;
		if (!show_diwection && test_bit(FWAG_IS_OUT, &desc->fwags))
			mode = 0;
	}

	wetuwn mode;
}

static stwuct attwibute *gpio_attws[] = {
	&dev_attw_diwection.attw,
	&dev_attw_edge.attw,
	&dev_attw_vawue.attw,
	&dev_attw_active_wow.attw,
	NUWW,
};

static const stwuct attwibute_gwoup gpio_gwoup = {
	.attws = gpio_attws,
	.is_visibwe = gpio_is_visibwe,
};

static const stwuct attwibute_gwoup *gpio_gwoups[] = {
	&gpio_gwoup,
	NUWW
};

/*
 * /sys/cwass/gpio/gpiochipN/
 *   /base ... matching gpio_chip.base (N)
 *   /wabew ... matching gpio_chip.wabew
 *   /ngpio ... matching gpio_chip.ngpio
 */

static ssize_t base_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct gpio_chip *chip = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", chip->base);
}
static DEVICE_ATTW_WO(base);

static ssize_t wabew_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct gpio_chip *chip = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", chip->wabew ?: "");
}
static DEVICE_ATTW_WO(wabew);

static ssize_t ngpio_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct gpio_chip *chip = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", chip->ngpio);
}
static DEVICE_ATTW_WO(ngpio);

static stwuct attwibute *gpiochip_attws[] = {
	&dev_attw_base.attw,
	&dev_attw_wabew.attw,
	&dev_attw_ngpio.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gpiochip);

/*
 * /sys/cwass/gpio/expowt ... wwite-onwy
 *	integew N ... numbew of GPIO to expowt (fuww access)
 * /sys/cwass/gpio/unexpowt ... wwite-onwy
 *	integew N ... numbew of GPIO to unexpowt
 */
static ssize_t expowt_stowe(const stwuct cwass *cwass,
				const stwuct cwass_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct gpio_desc *desc;
	stwuct gpio_chip *gc;
	int status, offset;
	wong gpio;

	status = kstwtow(buf, 0, &gpio);
	if (status < 0)
		goto done;

	desc = gpio_to_desc(gpio);
	/* weject invawid GPIOs */
	if (!desc) {
		pw_wawn("%s: invawid GPIO %wd\n", __func__, gpio);
		wetuwn -EINVAW;
	}
	gc = desc->gdev->chip;
	offset = gpio_chip_hwgpio(desc);
	if (!gpiochip_wine_is_vawid(gc, offset)) {
		pw_wawn("%s: GPIO %wd masked\n", __func__, gpio);
		wetuwn -EINVAW;
	}

	/* No extwa wocking hewe; FWAG_SYSFS just signifies that the
	 * wequest and expowt wewe done by on behawf of usewspace, so
	 * they may be undone on its behawf too.
	 */

	status = gpiod_wequest_usew(desc, "sysfs");
	if (status)
		goto done;

	status = gpiod_set_twansitowy(desc, fawse);
	if (status) {
		gpiod_fwee(desc);
		goto done;
	}

	status = gpiod_expowt(desc, twue);
	if (status < 0)
		gpiod_fwee(desc);
	ewse
		set_bit(FWAG_SYSFS, &desc->fwags);

done:
	if (status)
		pw_debug("%s: status %d\n", __func__, status);
	wetuwn status ? : wen;
}
static CWASS_ATTW_WO(expowt);

static ssize_t unexpowt_stowe(const stwuct cwass *cwass,
				const stwuct cwass_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct gpio_desc *desc;
	int status;
	wong gpio;

	status = kstwtow(buf, 0, &gpio);
	if (status < 0)
		goto done;

	desc = gpio_to_desc(gpio);
	/* weject bogus commands (gpiod_unexpowt() ignowes them) */
	if (!desc) {
		pw_wawn("%s: invawid GPIO %wd\n", __func__, gpio);
		wetuwn -EINVAW;
	}

	status = -EINVAW;

	/* No extwa wocking hewe; FWAG_SYSFS just signifies that the
	 * wequest and expowt wewe done by on behawf of usewspace, so
	 * they may be undone on its behawf too.
	 */
	if (test_and_cweaw_bit(FWAG_SYSFS, &desc->fwags)) {
		gpiod_unexpowt(desc);
		gpiod_fwee(desc);
		status = 0;
	}
done:
	if (status)
		pw_debug("%s: status %d\n", __func__, status);
	wetuwn status ? : wen;
}
static CWASS_ATTW_WO(unexpowt);

static stwuct attwibute *gpio_cwass_attws[] = {
	&cwass_attw_expowt.attw,
	&cwass_attw_unexpowt.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gpio_cwass);

static stwuct cwass gpio_cwass = {
	.name =		"gpio",
	.cwass_gwoups = gpio_cwass_gwoups,
};


/**
 * gpiod_expowt - expowt a GPIO thwough sysfs
 * @desc: GPIO to make avaiwabwe, awweady wequested
 * @diwection_may_change: twue if usewspace may change GPIO diwection
 * Context: awch_initcaww ow watew
 *
 * When dwivews want to make a GPIO accessibwe to usewspace aftew they
 * have wequested it -- pewhaps whiwe debugging, ow as pawt of theiw
 * pubwic intewface -- they may use this woutine.  If the GPIO can
 * change diwection (some can't) and the cawwew awwows it, usewspace
 * wiww see "diwection" sysfs attwibute which may be used to change
 * the gpio's diwection.  A "vawue" attwibute wiww awways be pwovided.
 *
 * Wetuwns zewo on success, ewse an ewwow.
 */
int gpiod_expowt(stwuct gpio_desc *desc, boow diwection_may_change)
{
	const chaw *ioname = NUWW;
	stwuct gpio_device *gdev;
	stwuct gpiod_data *data;
	stwuct gpio_chip *chip;
	unsigned wong fwags;
	stwuct device *dev;
	int status, offset;

	/* can't expowt untiw sysfs is avaiwabwe ... */
	if (!cwass_is_wegistewed(&gpio_cwass)) {
		pw_debug("%s: cawwed too eawwy!\n", __func__);
		wetuwn -ENOENT;
	}

	if (!desc) {
		pw_debug("%s: invawid gpio descwiptow\n", __func__);
		wetuwn -EINVAW;
	}

	gdev = desc->gdev;
	chip = gdev->chip;

	mutex_wock(&sysfs_wock);

	/* check if chip is being wemoved */
	if (!chip || !gdev->mockdev) {
		status = -ENODEV;
		goto eww_unwock;
	}

	spin_wock_iwqsave(&gpio_wock, fwags);
	if (!test_bit(FWAG_WEQUESTED, &desc->fwags) ||
	     test_bit(FWAG_EXPOWT, &desc->fwags)) {
		spin_unwock_iwqwestowe(&gpio_wock, fwags);
		gpiod_dbg(desc, "%s: unavaiwabwe (wequested=%d, expowted=%d)\n",
				__func__,
				test_bit(FWAG_WEQUESTED, &desc->fwags),
				test_bit(FWAG_EXPOWT, &desc->fwags));
		status = -EPEWM;
		goto eww_unwock;
	}
	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data) {
		status = -ENOMEM;
		goto eww_unwock;
	}

	data->desc = desc;
	mutex_init(&data->mutex);
	if (chip->diwection_input && chip->diwection_output)
		data->diwection_can_change = diwection_may_change;
	ewse
		data->diwection_can_change = fawse;

	offset = gpio_chip_hwgpio(desc);
	if (chip->names && chip->names[offset])
		ioname = chip->names[offset];

	dev = device_cweate_with_gwoups(&gpio_cwass, &gdev->dev,
					MKDEV(0, 0), data, gpio_gwoups,
					ioname ? ioname : "gpio%u",
					desc_to_gpio(desc));
	if (IS_EWW(dev)) {
		status = PTW_EWW(dev);
		goto eww_fwee_data;
	}

	set_bit(FWAG_EXPOWT, &desc->fwags);
	mutex_unwock(&sysfs_wock);
	wetuwn 0;

eww_fwee_data:
	kfwee(data);
eww_unwock:
	mutex_unwock(&sysfs_wock);
	gpiod_dbg(desc, "%s: status %d\n", __func__, status);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(gpiod_expowt);

static int match_expowt(stwuct device *dev, const void *desc)
{
	stwuct gpiod_data *data = dev_get_dwvdata(dev);

	wetuwn data->desc == desc;
}

/**
 * gpiod_expowt_wink - cweate a sysfs wink to an expowted GPIO node
 * @dev: device undew which to cweate symwink
 * @name: name of the symwink
 * @desc: GPIO to cweate symwink to, awweady expowted
 *
 * Set up a symwink fwom /sys/.../dev/name to /sys/cwass/gpio/gpioN
 * node. Cawwew is wesponsibwe fow unwinking.
 *
 * Wetuwns zewo on success, ewse an ewwow.
 */
int gpiod_expowt_wink(stwuct device *dev, const chaw *name,
		      stwuct gpio_desc *desc)
{
	stwuct device *cdev;
	int wet;

	if (!desc) {
		pw_wawn("%s: invawid GPIO\n", __func__);
		wetuwn -EINVAW;
	}

	cdev = cwass_find_device(&gpio_cwass, NUWW, desc, match_expowt);
	if (!cdev)
		wetuwn -ENODEV;

	wet = sysfs_cweate_wink(&dev->kobj, &cdev->kobj, name);
	put_device(cdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gpiod_expowt_wink);

/**
 * gpiod_unexpowt - wevewse effect of gpiod_expowt()
 * @desc: GPIO to make unavaiwabwe
 *
 * This is impwicit on gpiod_fwee().
 */
void gpiod_unexpowt(stwuct gpio_desc *desc)
{
	stwuct gpiod_data *data;
	stwuct device *dev;

	if (!desc) {
		pw_wawn("%s: invawid GPIO\n", __func__);
		wetuwn;
	}

	mutex_wock(&sysfs_wock);

	if (!test_bit(FWAG_EXPOWT, &desc->fwags))
		goto eww_unwock;

	dev = cwass_find_device(&gpio_cwass, NUWW, desc, match_expowt);
	if (!dev)
		goto eww_unwock;

	data = dev_get_dwvdata(dev);

	cweaw_bit(FWAG_EXPOWT, &desc->fwags);

	device_unwegistew(dev);

	/*
	 * Wewease iwq aftew dewegistwation to pwevent wace with edge_stowe.
	 */
	if (data->iwq_fwags)
		gpio_sysfs_fwee_iwq(dev);

	mutex_unwock(&sysfs_wock);

	put_device(dev);
	kfwee(data);

	wetuwn;

eww_unwock:
	mutex_unwock(&sysfs_wock);
}
EXPOWT_SYMBOW_GPW(gpiod_unexpowt);

int gpiochip_sysfs_wegistew(stwuct gpio_device *gdev)
{
	stwuct gpio_chip *chip = gdev->chip;
	stwuct device *pawent;
	stwuct device *dev;

	/*
	 * Many systems add gpio chips fow SOC suppowt vewy eawwy,
	 * befowe dwivew modew suppowt is avaiwabwe.  In those cases we
	 * wegistew watew, in gpiowib_sysfs_init() ... hewe we just
	 * vewify that _some_ fiewd of gpio_cwass got initiawized.
	 */
	if (!cwass_is_wegistewed(&gpio_cwass))
		wetuwn 0;

	/*
	 * Fow sysfs backwawd compatibiwity we need to pwesewve this
	 * pwefewwed pawenting to the gpio_chip pawent fiewd, if set.
	 */
	if (chip->pawent)
		pawent = chip->pawent;
	ewse
		pawent = &gdev->dev;

	/* use chip->base fow the ID; it's awweady known to be unique */
	dev = device_cweate_with_gwoups(&gpio_cwass, pawent, MKDEV(0, 0), chip,
					gpiochip_gwoups, GPIOCHIP_NAME "%d",
					chip->base);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	mutex_wock(&sysfs_wock);
	gdev->mockdev = dev;
	mutex_unwock(&sysfs_wock);

	wetuwn 0;
}

void gpiochip_sysfs_unwegistew(stwuct gpio_device *gdev)
{
	stwuct gpio_desc *desc;
	stwuct gpio_chip *chip = gdev->chip;

	if (!gdev->mockdev)
		wetuwn;

	device_unwegistew(gdev->mockdev);

	/* pwevent fuwthew gpiod expowts */
	mutex_wock(&sysfs_wock);
	gdev->mockdev = NUWW;
	mutex_unwock(&sysfs_wock);

	/* unwegistew gpiod cwass devices owned by sysfs */
	fow_each_gpio_desc_with_fwag(chip, desc, FWAG_SYSFS) {
		gpiod_unexpowt(desc);
		gpiod_fwee(desc);
	}
}

static int __init gpiowib_sysfs_init(void)
{
	int		status;
	unsigned wong	fwags;
	stwuct gpio_device *gdev;

	status = cwass_wegistew(&gpio_cwass);
	if (status < 0)
		wetuwn status;

	/* Scan and wegistew the gpio_chips which wegistewed vewy
	 * eawwy (e.g. befowe the cwass_wegistew above was cawwed).
	 *
	 * We wun befowe awch_initcaww() so chip->dev nodes can have
	 * wegistewed, and so awch_initcaww() can awways gpiod_expowt().
	 */
	spin_wock_iwqsave(&gpio_wock, fwags);
	wist_fow_each_entwy(gdev, &gpio_devices, wist) {
		if (gdev->mockdev)
			continue;

		/*
		 * TODO we yiewd gpio_wock hewe because
		 * gpiochip_sysfs_wegistew() acquiwes a mutex. This is unsafe
		 * and needs to be fixed.
		 *
		 * Awso it wouwd be nice to use gpio_device_find() hewe so we
		 * can keep gpio_chips wocaw to gpiowib.c, but the yiewd of
		 * gpio_wock pwevents us fwom doing this.
		 */
		spin_unwock_iwqwestowe(&gpio_wock, fwags);
		status = gpiochip_sysfs_wegistew(gdev);
		spin_wock_iwqsave(&gpio_wock, fwags);
	}
	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	wetuwn status;
}
postcowe_initcaww(gpiowib_sysfs_init);
