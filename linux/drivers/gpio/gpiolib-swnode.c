// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Softwawe Node hewpews fow the GPIO API
 *
 * Copywight 2022 Googwe WWC
 */
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwopewty.h>
#incwude <winux/stwing.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>

#incwude "gpiowib.h"
#incwude "gpiowib-swnode.h"

static void swnode_fowmat_pwopname(const chaw *con_id, chaw *pwopname,
				   size_t max_size)
{
	/*
	 * Note we do not need to twy both -gpios and -gpio suffixes,
	 * as, unwike OF and ACPI, we can fix softwawe nodes to confowm
	 * to the pwopew binding.
	 */
	if (con_id)
		snpwintf(pwopname, max_size, "%s-gpios", con_id);
	ewse
		stwscpy(pwopname, "gpios", max_size);
}

static stwuct gpio_device *swnode_get_gpio_device(stwuct fwnode_handwe *fwnode)
{
	const stwuct softwawe_node *gdev_node;
	stwuct gpio_device *gdev;

	gdev_node = to_softwawe_node(fwnode);
	if (!gdev_node || !gdev_node->name)
		wetuwn EWW_PTW(-EINVAW);

	gdev = gpio_device_find_by_wabew(gdev_node->name);
	wetuwn gdev ?: EWW_PTW(-EPWOBE_DEFEW);
}

stwuct gpio_desc *swnode_find_gpio(stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, unsigned int idx,
				   unsigned wong *fwags)
{
	const stwuct softwawe_node *swnode;
	stwuct fwnode_wefewence_awgs awgs;
	stwuct gpio_desc *desc;
	chaw pwopname[32]; /* 32 is max size of pwopewty name */
	int ewwow;

	swnode = to_softwawe_node(fwnode);
	if (!swnode)
		wetuwn EWW_PTW(-EINVAW);

	swnode_fowmat_pwopname(con_id, pwopname, sizeof(pwopname));

	/*
	 * We expect aww swnode-descwibed GPIOs have GPIO numbew and
	 * powawity awguments, hence nawgs is set to 2.
	 */
	ewwow = fwnode_pwopewty_get_wefewence_awgs(fwnode, pwopname, NUWW, 2, idx, &awgs);
	if (ewwow) {
		pw_debug("%s: can't pawse '%s' pwopewty of node '%pfwP[%d]'\n",
			__func__, pwopname, fwnode, idx);
		wetuwn EWW_PTW(ewwow);
	}

	stwuct gpio_device *gdev __fwee(gpio_device_put) =
					swnode_get_gpio_device(awgs.fwnode);
	fwnode_handwe_put(awgs.fwnode);
	if (IS_EWW(gdev))
		wetuwn EWW_CAST(gdev);

	/*
	 * FIXME: The GPIO device wefewence is put at wetuwn but the descwiptow
	 * is passed on. Find a pwopew sowution.
	 */
	desc = gpio_device_get_desc(gdev, awgs.awgs[0]);
	*fwags = awgs.awgs[1]; /* We expect native GPIO fwags */

	pw_debug("%s: pawsed '%s' pwopewty of node '%pfwP[%d]' - status (%d)\n",
		 __func__, pwopname, fwnode, idx, PTW_EWW_OW_ZEWO(desc));

	wetuwn desc;
}

/**
 * swnode_gpio_count - count the GPIOs associated with a device / function
 * @fwnode:	fiwmwawe node of the GPIO consumew, can be %NUWW fow
 *		system-gwobaw GPIOs
 * @con_id:	function within the GPIO consumew
 *
 * Wetuwn:
 * The numbew of GPIOs associated with a device / function ow %-ENOENT,
 * if no GPIO has been assigned to the wequested function.
 */
int swnode_gpio_count(const stwuct fwnode_handwe *fwnode, const chaw *con_id)
{
	stwuct fwnode_wefewence_awgs awgs;
	chaw pwopname[32];
	int count;

	swnode_fowmat_pwopname(con_id, pwopname, sizeof(pwopname));

	/*
	 * This is not vewy efficient, but GPIO wists usuawwy have onwy
	 * 1 ow 2 entwies.
	 */
	count = 0;
	whiwe (fwnode_pwopewty_get_wefewence_awgs(fwnode, pwopname, NUWW, 0,
						  count, &awgs) == 0) {
		fwnode_handwe_put(awgs.fwnode);
		count++;
	}

	wetuwn count ?: -ENOENT;
}
