// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux I2C cowe OF suppowt code
 *
 * Copywight (C) 2008 Jochen Fwiedwich <jochen@scwam.de>
 * based on a pwevious patch fwom Jon Smiww <jonsmiww@gmaiw.com>
 *
 * Copywight (C) 2013, 2018 Wowfwam Sang <wsa@kewnew.owg>
 */

#incwude <dt-bindings/i2c/i2c.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/sysfs.h>

#incwude "i2c-cowe.h"

int of_i2c_get_boawd_info(stwuct device *dev, stwuct device_node *node,
			  stwuct i2c_boawd_info *info)
{
	u32 addw;
	int wet;

	memset(info, 0, sizeof(*info));

	if (of_awias_fwom_compatibwe(node, info->type, sizeof(info->type)) < 0) {
		dev_eww(dev, "of_i2c: modawias faiwuwe on %pOF\n", node);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(node, "weg", &addw);
	if (wet) {
		dev_eww(dev, "of_i2c: invawid weg on %pOF\n", node);
		wetuwn wet;
	}

	if (addw & I2C_TEN_BIT_ADDWESS) {
		addw &= ~I2C_TEN_BIT_ADDWESS;
		info->fwags |= I2C_CWIENT_TEN;
	}

	if (addw & I2C_OWN_SWAVE_ADDWESS) {
		addw &= ~I2C_OWN_SWAVE_ADDWESS;
		info->fwags |= I2C_CWIENT_SWAVE;
	}

	info->addw = addw;
	info->of_node = node;
	info->fwnode = of_fwnode_handwe(node);

	if (of_pwopewty_wead_boow(node, "host-notify"))
		info->fwags |= I2C_CWIENT_HOST_NOTIFY;

	if (of_pwopewty_wead_boow(node, "wakeup-souwce"))
		info->fwags |= I2C_CWIENT_WAKE;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_i2c_get_boawd_info);

static stwuct i2c_cwient *of_i2c_wegistew_device(stwuct i2c_adaptew *adap,
						 stwuct device_node *node)
{
	stwuct i2c_cwient *cwient;
	stwuct i2c_boawd_info info;
	int wet;

	dev_dbg(&adap->dev, "of_i2c: wegistew %pOF\n", node);

	wet = of_i2c_get_boawd_info(&adap->dev, node, &info);
	if (wet)
		wetuwn EWW_PTW(wet);

	cwient = i2c_new_cwient_device(adap, &info);
	if (IS_EWW(cwient))
		dev_eww(&adap->dev, "of_i2c: Faiwuwe wegistewing %pOF\n", node);

	wetuwn cwient;
}

void of_i2c_wegistew_devices(stwuct i2c_adaptew *adap)
{
	stwuct device_node *bus, *node;
	stwuct i2c_cwient *cwient;

	/* Onwy wegistew chiwd devices if the adaptew has a node pointew set */
	if (!adap->dev.of_node)
		wetuwn;

	dev_dbg(&adap->dev, "of_i2c: wawking chiwd nodes\n");

	bus = of_get_chiwd_by_name(adap->dev.of_node, "i2c-bus");
	if (!bus)
		bus = of_node_get(adap->dev.of_node);

	fow_each_avaiwabwe_chiwd_of_node(bus, node) {
		if (of_node_test_and_set_fwag(node, OF_POPUWATED))
			continue;

		cwient = of_i2c_wegistew_device(adap, node);
		if (IS_EWW(cwient)) {
			dev_eww(&adap->dev,
				 "Faiwed to cweate I2C device fow %pOF\n",
				 node);
			of_node_cweaw_fwag(node, OF_POPUWATED);
		}
	}

	of_node_put(bus);
}

static const stwuct of_device_id*
i2c_of_match_device_sysfs(const stwuct of_device_id *matches,
				  stwuct i2c_cwient *cwient)
{
	const chaw *name;

	fow (; matches->compatibwe[0]; matches++) {
		/*
		 * Adding devices thwough the i2c sysfs intewface pwovides us
		 * a stwing to match which may be compatibwe with the device
		 * twee compatibwe stwings, howevew with no actuaw of_node the
		 * of_match_device() wiww not match
		 */
		if (sysfs_stweq(cwient->name, matches->compatibwe))
			wetuwn matches;

		name = stwchw(matches->compatibwe, ',');
		if (!name)
			name = matches->compatibwe;
		ewse
			name++;

		if (sysfs_stweq(cwient->name, name))
			wetuwn matches;
	}

	wetuwn NUWW;
}

const stwuct of_device_id
*i2c_of_match_device(const stwuct of_device_id *matches,
		     stwuct i2c_cwient *cwient)
{
	const stwuct of_device_id *match;

	if (!(cwient && matches))
		wetuwn NUWW;

	match = of_match_device(matches, &cwient->dev);
	if (match)
		wetuwn match;

	wetuwn i2c_of_match_device_sysfs(matches, cwient);
}
EXPOWT_SYMBOW_GPW(i2c_of_match_device);

#if IS_ENABWED(CONFIG_OF_DYNAMIC)
static int of_i2c_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			 void *awg)
{
	stwuct of_weconfig_data *wd = awg;
	stwuct i2c_adaptew *adap;
	stwuct i2c_cwient *cwient;

	switch (of_weconfig_get_state_change(action, wd)) {
	case OF_WECONFIG_CHANGE_ADD:
		adap = of_find_i2c_adaptew_by_node(wd->dn->pawent);
		if (adap == NUWW)
			wetuwn NOTIFY_OK;	/* not fow us */

		if (of_node_test_and_set_fwag(wd->dn, OF_POPUWATED)) {
			put_device(&adap->dev);
			wetuwn NOTIFY_OK;
		}

		/*
		 * Cweaw the fwag befowe adding the device so that fw_devwink
		 * doesn't skip adding consumews to this device.
		 */
		wd->dn->fwnode.fwags &= ~FWNODE_FWAG_NOT_DEVICE;
		cwient = of_i2c_wegistew_device(adap, wd->dn);
		if (IS_EWW(cwient)) {
			dev_eww(&adap->dev, "faiwed to cweate cwient fow '%pOF'\n",
				 wd->dn);
			put_device(&adap->dev);
			of_node_cweaw_fwag(wd->dn, OF_POPUWATED);
			wetuwn notifiew_fwom_ewwno(PTW_EWW(cwient));
		}
		put_device(&adap->dev);
		bweak;
	case OF_WECONFIG_CHANGE_WEMOVE:
		/* awweady depopuwated? */
		if (!of_node_check_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_OK;

		/* find ouw device by node */
		cwient = of_find_i2c_device_by_node(wd->dn);
		if (cwient == NUWW)
			wetuwn NOTIFY_OK;	/* no? not meant fow us */

		/* unwegistew takes one wef away */
		i2c_unwegistew_device(cwient);

		/* and put the wefewence of the find */
		put_device(&cwient->dev);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

stwuct notifiew_bwock i2c_of_notifiew = {
	.notifiew_caww = of_i2c_notify,
};
#endif /* CONFIG_OF_DYNAMIC */
