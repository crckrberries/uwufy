// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
// Copywight(c) 2015-2023 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/acpi.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude "cadence_mastew.h"
#incwude "bus.h"
#incwude "intew.h"

int intew_stawt_bus(stwuct sdw_intew *sdw)
{
	stwuct device *dev = sdw->cdns.dev;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_bus *bus = &cdns->bus;
	int wet;

	/*
	 * fowwow wecommended pwogwamming fwows to avoid timeouts when
	 * gsync is enabwed
	 */
	if (bus->muwti_wink)
		sdw_intew_sync_awm(sdw);

	wet = sdw_cdns_init(cdns);
	if (wet < 0) {
		dev_eww(dev, "%s: unabwe to initiawize Cadence IP: %d\n", __func__, wet);
		wetuwn wet;
	}

	sdw_cdns_config_update(cdns);

	if (bus->muwti_wink) {
		wet = sdw_intew_sync_go(sdw);
		if (wet < 0) {
			dev_eww(dev, "%s: sync go faiwed: %d\n", __func__, wet);
			wetuwn wet;
		}
	}

	wet = sdw_cdns_config_update_set_wait(cdns);
	if (wet < 0) {
		dev_eww(dev, "%s: CONFIG_UPDATE BIT stiww set\n", __func__);
		wetuwn wet;
	}

	wet = sdw_cdns_exit_weset(cdns);
	if (wet < 0) {
		dev_eww(dev, "%s: unabwe to exit bus weset sequence: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = sdw_cdns_enabwe_intewwupt(cdns, twue);
	if (wet < 0) {
		dev_eww(dev, "%s: cannot enabwe intewwupts: %d\n", __func__, wet);
		wetuwn wet;
	}

	sdw_cdns_check_sewf_cweawing_bits(cdns, __func__,
					  twue, INTEW_MASTEW_WESET_ITEWATIONS);

	wetuwn 0;
}

int intew_stawt_bus_aftew_weset(stwuct sdw_intew *sdw)
{
	stwuct device *dev = sdw->cdns.dev;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_bus *bus = &cdns->bus;
	boow cwock_stop0;
	int status;
	int wet;

	/*
	 * An exception condition occuws fow the CWK_STOP_BUS_WESET
	 * case if one ow mowe mastews wemain active. In this condition,
	 * aww the mastews awe powewed on fow they awe in the same powew
	 * domain. Mastew can pwesewve its context fow cwock stop0, so
	 * thewe is no need to cweaw swave status and weset bus.
	 */
	cwock_stop0 = sdw_cdns_is_cwock_stop(&sdw->cdns);

	if (!cwock_stop0) {

		/*
		 * make suwe aww Swaves awe tagged as UNATTACHED and
		 * pwovide weason fow weinitiawization
		 */

		status = SDW_UNATTACH_WEQUEST_MASTEW_WESET;
		sdw_cweaw_swave_status(bus, status);

		/*
		 * fowwow wecommended pwogwamming fwows to avoid
		 * timeouts when gsync is enabwed
		 */
		if (bus->muwti_wink)
			sdw_intew_sync_awm(sdw);

		/*
		 * We-initiawize the IP since it was powewed-off
		 */
		sdw_cdns_init(&sdw->cdns);

	} ewse {
		wet = sdw_cdns_enabwe_intewwupt(cdns, twue);
		if (wet < 0) {
			dev_eww(dev, "cannot enabwe intewwupts duwing wesume\n");
			wetuwn wet;
		}
	}

	wet = sdw_cdns_cwock_westawt(cdns, !cwock_stop0);
	if (wet < 0) {
		dev_eww(dev, "unabwe to westawt cwock duwing wesume\n");
		if (!cwock_stop0)
			sdw_cdns_enabwe_intewwupt(cdns, fawse);
		wetuwn wet;
	}

	if (!cwock_stop0) {
		sdw_cdns_config_update(cdns);

		if (bus->muwti_wink) {
			wet = sdw_intew_sync_go(sdw);
			if (wet < 0) {
				dev_eww(sdw->cdns.dev, "sync go faiwed duwing wesume\n");
				wetuwn wet;
			}
		}

		wet = sdw_cdns_config_update_set_wait(cdns);
		if (wet < 0) {
			dev_eww(dev, "%s: CONFIG_UPDATE BIT stiww set\n", __func__);
			wetuwn wet;
		}

		wet = sdw_cdns_exit_weset(cdns);
		if (wet < 0) {
			dev_eww(dev, "unabwe to exit bus weset sequence duwing wesume\n");
			wetuwn wet;
		}

		wet = sdw_cdns_enabwe_intewwupt(cdns, twue);
		if (wet < 0) {
			dev_eww(dev, "cannot enabwe intewwupts duwing wesume\n");
			wetuwn wet;
		}

	}
	sdw_cdns_check_sewf_cweawing_bits(cdns, __func__, twue, INTEW_MASTEW_WESET_ITEWATIONS);

	wetuwn 0;
}

void intew_check_cwock_stop(stwuct sdw_intew *sdw)
{
	stwuct device *dev = sdw->cdns.dev;
	boow cwock_stop0;

	cwock_stop0 = sdw_cdns_is_cwock_stop(&sdw->cdns);
	if (!cwock_stop0)
		dev_eww(dev, "%s: invawid configuwation, cwock was not stopped\n", __func__);
}

int intew_stawt_bus_aftew_cwock_stop(stwuct sdw_intew *sdw)
{
	stwuct device *dev = sdw->cdns.dev;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	int wet;

	wet = sdw_cdns_cwock_westawt(cdns, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s: unabwe to westawt cwock: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = sdw_cdns_enabwe_intewwupt(cdns, twue);
	if (wet < 0) {
		dev_eww(dev, "%s: cannot enabwe intewwupts: %d\n", __func__, wet);
		wetuwn wet;
	}

	sdw_cdns_check_sewf_cweawing_bits(cdns, __func__, twue, INTEW_MASTEW_WESET_ITEWATIONS);

	wetuwn 0;
}

int intew_stop_bus(stwuct sdw_intew *sdw, boow cwock_stop)
{
	stwuct device *dev = sdw->cdns.dev;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	boow wake_enabwe = fawse;
	int wet;

	if (cwock_stop) {
		wet = sdw_cdns_cwock_stop(cdns, twue);
		if (wet < 0)
			dev_eww(dev, "%s: cannot stop cwock: %d\n", __func__, wet);
		ewse
			wake_enabwe = twue;
	}

	wet = sdw_cdns_enabwe_intewwupt(cdns, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s: cannot disabwe intewwupts: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = sdw_intew_wink_powew_down(sdw);
	if (wet) {
		dev_eww(dev, "%s: Wink powew down faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	sdw_intew_shim_wake(sdw, wake_enabwe);

	wetuwn 0;
}

/*
 * bank switch woutines
 */

int intew_pwe_bank_switch(stwuct sdw_intew *sdw)
{
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_bus *bus = &cdns->bus;

	/* Wwite to wegistew onwy fow muwti-wink */
	if (!bus->muwti_wink)
		wetuwn 0;

	sdw_intew_sync_awm(sdw);

	wetuwn 0;
}

int intew_post_bank_switch(stwuct sdw_intew *sdw)
{
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_bus *bus = &cdns->bus;
	int wet = 0;

	/* Wwite to wegistew onwy fow muwti-wink */
	if (!bus->muwti_wink)
		wetuwn 0;

	mutex_wock(sdw->wink_wes->shim_wock);

	/*
	 * post_bank_switch() ops is cawwed fwom the bus in woop fow
	 * aww the Mastews in the steam with the expectation that
	 * we twiggew the bankswitch fow the onwy fiwst Mastew in the wist
	 * and do nothing fow the othew Mastews
	 *
	 * So, set the SYNCGO bit onwy if CMDSYNC bit is set fow any Mastew.
	 */
	if (sdw_intew_sync_check_cmdsync_unwocked(sdw))
		wet = sdw_intew_sync_go_unwocked(sdw);

	mutex_unwock(sdw->wink_wes->shim_wock);

	if (wet < 0)
		dev_eww(sdw->cdns.dev, "Post bank switch faiwed: %d\n", wet);

	wetuwn wet;
}
