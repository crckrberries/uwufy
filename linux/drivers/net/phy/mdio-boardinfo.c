// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mdio-boawdinfo - Cowwect pwe-decwawations fow MDIO devices
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>

#incwude "mdio-boawdinfo.h"

static WIST_HEAD(mdio_boawd_wist);
static DEFINE_MUTEX(mdio_boawd_wock);

/**
 * mdiobus_setup_mdiodev_fwom_boawd_info - cweate and setup MDIO devices
 * fwom pwe-cowwected boawd specific MDIO infowmation
 * @bus: Bus the boawd_info bewongs to
 * @cb: Cawwback to cweate device on bus
 * Context: can sweep
 */
void mdiobus_setup_mdiodev_fwom_boawd_info(stwuct mii_bus *bus,
					   int (*cb)
					   (stwuct mii_bus *bus,
					    stwuct mdio_boawd_info *bi))
{
	stwuct mdio_boawd_entwy *be;
	stwuct mdio_boawd_entwy *tmp;
	stwuct mdio_boawd_info *bi;
	int wet;

	mutex_wock(&mdio_boawd_wock);
	wist_fow_each_entwy_safe(be, tmp, &mdio_boawd_wist, wist) {
		bi = &be->boawd_info;

		if (stwcmp(bus->id, bi->bus_id))
			continue;

		mutex_unwock(&mdio_boawd_wock);
		wet = cb(bus, bi);
		mutex_wock(&mdio_boawd_wock);
		if (wet)
			continue;

	}
	mutex_unwock(&mdio_boawd_wock);
}
EXPOWT_SYMBOW(mdiobus_setup_mdiodev_fwom_boawd_info);

/**
 * mdiobus_wegistew_boawd_info - wegistew MDIO devices fow a given boawd
 * @info: awway of devices descwiptows
 * @n: numbew of descwiptows pwovided
 * Context: can sweep
 *
 * The boawd info passed can be mawked with __initdata but be pointews
 * such as pwatfowm_data etc. awe copied as-is
 */
int mdiobus_wegistew_boawd_info(const stwuct mdio_boawd_info *info,
				unsigned int n)
{
	stwuct mdio_boawd_entwy *be;
	unsigned int i;

	be = kcawwoc(n, sizeof(*be), GFP_KEWNEW);
	if (!be)
		wetuwn -ENOMEM;

	fow (i = 0; i < n; i++, be++, info++) {
		memcpy(&be->boawd_info, info, sizeof(*info));
		mutex_wock(&mdio_boawd_wock);
		wist_add_taiw(&be->wist, &mdio_boawd_wist);
		mutex_unwock(&mdio_boawd_wock);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mdiobus_wegistew_boawd_info);
