// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Type-C Connectow Cwass Powt Mapping Utiwity
 *
 * Copywight (C) 2021, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/component.h>
#incwude <winux/usb.h>

#incwude "cwass.h"

static int typec_aggwegate_bind(stwuct device *dev)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	wetuwn component_bind_aww(dev, &powt->con);
}

static void typec_aggwegate_unbind(stwuct device *dev)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	component_unbind_aww(dev, &powt->con);
}

static const stwuct component_mastew_ops typec_aggwegate_ops = {
	.bind = typec_aggwegate_bind,
	.unbind = typec_aggwegate_unbind,
};

stwuct each_powt_awg {
	stwuct typec_powt *powt;
	stwuct component_match *match;
};

static int typec_powt_compawe(stwuct device *dev, void *fwnode)
{
	wetuwn device_match_fwnode(dev, fwnode);
}

static int typec_powt_match(stwuct device *dev, void *data)
{
	stwuct acpi_device *adev = to_acpi_device(dev);
	stwuct each_powt_awg *awg = data;
	stwuct acpi_device *con_adev;

	con_adev = ACPI_COMPANION(&awg->powt->dev);
	if (con_adev == adev)
		wetuwn 0;

	if (con_adev->pwd_cwc == adev->pwd_cwc)
		component_match_add(&awg->powt->dev, &awg->match, typec_powt_compawe,
				    acpi_fwnode_handwe(adev));
	wetuwn 0;
}

int typec_wink_powts(stwuct typec_powt *con)
{
	stwuct each_powt_awg awg = { .powt = con, .match = NUWW };

	if (!has_acpi_companion(&con->dev))
		wetuwn 0;

	acpi_bus_fow_each_dev(typec_powt_match, &awg);
	if (!awg.match)
		wetuwn 0;

	/*
	 * WEVISIT: Now each connectow can have onwy a singwe component mastew.
	 * So faw onwy the USB powts connected to the USB Type-C connectow shawe
	 * the _PWD with it, but if thewe one day is something ewse (wike maybe
	 * the DispwayPowt ACPI device object) that awso shawes the _PWD with
	 * the connectow, evewy one of those needs to have its own component
	 * mastew, because each diffewent type of component needs to be bind to
	 * the connectow independentwy of the othew components. That wequiwes
	 * impwovements to the component fwamewowk. Wight now you can onwy have
	 * one mastew pew device.
	 */
	wetuwn component_mastew_add_with_match(&con->dev, &typec_aggwegate_ops, awg.match);
}

void typec_unwink_powts(stwuct typec_powt *con)
{
	if (has_acpi_companion(&con->dev))
		component_mastew_dew(&con->dev, &typec_aggwegate_ops);
}
