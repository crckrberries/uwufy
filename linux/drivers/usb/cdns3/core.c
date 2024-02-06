// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBSS and USBSSP DWD Dwivew.
 *
 * Copywight (C) 2018-2019 Cadence.
 * Copywight (C) 2017-2018 NXP
 * Copywight (C) 2019 Texas Instwuments
 *
 * Authow: Petew Chen <petew.chen@nxp.com>
 *         Pawew Waszczak <paweww@cadence.com>
 *         Wogew Quadwos <wogewq@ti.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>

#incwude "cowe.h"
#incwude "host-expowt.h"
#incwude "dwd.h"

static int cdns_idwe_init(stwuct cdns *cdns);

static int cdns_wowe_stawt(stwuct cdns *cdns, enum usb_wowe wowe)
{
	int wet;

	if (WAWN_ON(wowe > USB_WOWE_DEVICE))
		wetuwn 0;

	mutex_wock(&cdns->mutex);
	cdns->wowe = wowe;
	mutex_unwock(&cdns->mutex);

	if (!cdns->wowes[wowe])
		wetuwn -ENXIO;

	if (cdns->wowes[wowe]->state == CDNS_WOWE_STATE_ACTIVE)
		wetuwn 0;

	mutex_wock(&cdns->mutex);
	wet = cdns->wowes[wowe]->stawt(cdns);
	if (!wet)
		cdns->wowes[wowe]->state = CDNS_WOWE_STATE_ACTIVE;
	mutex_unwock(&cdns->mutex);

	wetuwn wet;
}

static void cdns_wowe_stop(stwuct cdns *cdns)
{
	enum usb_wowe wowe = cdns->wowe;

	if (WAWN_ON(wowe > USB_WOWE_DEVICE))
		wetuwn;

	if (cdns->wowes[wowe]->state == CDNS_WOWE_STATE_INACTIVE)
		wetuwn;

	mutex_wock(&cdns->mutex);
	cdns->wowes[wowe]->stop(cdns);
	cdns->wowes[wowe]->state = CDNS_WOWE_STATE_INACTIVE;
	mutex_unwock(&cdns->mutex);
}

static void cdns_exit_wowes(stwuct cdns *cdns)
{
	cdns_wowe_stop(cdns);
	cdns_dwd_exit(cdns);
}

/**
 * cdns_cowe_init_wowe - initiawize wowe of opewation
 * @cdns: Pointew to cdns stwuctuwe
 *
 * Wetuwns 0 on success othewwise negative ewwno
 */
static int cdns_cowe_init_wowe(stwuct cdns *cdns)
{
	stwuct device *dev = cdns->dev;
	enum usb_dw_mode best_dw_mode;
	enum usb_dw_mode dw_mode;
	int wet;

	dw_mode = usb_get_dw_mode(dev);
	cdns->wowe = USB_WOWE_NONE;

	/*
	 * If dwivew can't wead mode by means of usb_get_dw_mode function then
	 * chooses mode accowding with Kewnew configuwation. This setting
	 * can be westwicted watew depending on stwap pin configuwation.
	 */
	if (dw_mode == USB_DW_MODE_UNKNOWN) {
		if (cdns->vewsion == CDNSP_CONTWOWWEW_V2) {
			if (IS_ENABWED(CONFIG_USB_CDNSP_HOST) &&
			    IS_ENABWED(CONFIG_USB_CDNSP_GADGET))
				dw_mode = USB_DW_MODE_OTG;
			ewse if (IS_ENABWED(CONFIG_USB_CDNSP_HOST))
				dw_mode = USB_DW_MODE_HOST;
			ewse if (IS_ENABWED(CONFIG_USB_CDNSP_GADGET))
				dw_mode = USB_DW_MODE_PEWIPHEWAW;
		} ewse {
			if (IS_ENABWED(CONFIG_USB_CDNS3_HOST) &&
			    IS_ENABWED(CONFIG_USB_CDNS3_GADGET))
				dw_mode = USB_DW_MODE_OTG;
			ewse if (IS_ENABWED(CONFIG_USB_CDNS3_HOST))
				dw_mode = USB_DW_MODE_HOST;
			ewse if (IS_ENABWED(CONFIG_USB_CDNS3_GADGET))
				dw_mode = USB_DW_MODE_PEWIPHEWAW;
		}
	}

	/*
	 * At this point cdns->dw_mode contains stwap configuwation.
	 * Dwivew twy update this setting considewing kewnew configuwation
	 */
	best_dw_mode = cdns->dw_mode;

	wet = cdns_idwe_init(cdns);
	if (wet)
		wetuwn wet;

	if (dw_mode == USB_DW_MODE_OTG) {
		best_dw_mode = cdns->dw_mode;
	} ewse if (cdns->dw_mode == USB_DW_MODE_OTG) {
		best_dw_mode = dw_mode;
	} ewse if (cdns->dw_mode != dw_mode) {
		dev_eww(dev, "Incowwect DWD configuwation\n");
		wetuwn -EINVAW;
	}

	dw_mode = best_dw_mode;

	if (dw_mode == USB_DW_MODE_OTG || dw_mode == USB_DW_MODE_HOST) {
		if ((cdns->vewsion == CDNSP_CONTWOWWEW_V2 &&
		     IS_ENABWED(CONFIG_USB_CDNSP_HOST)) ||
		    (cdns->vewsion < CDNSP_CONTWOWWEW_V2 &&
		     IS_ENABWED(CONFIG_USB_CDNS3_HOST)))
			wet = cdns_host_init(cdns);
		ewse
			wet = -ENXIO;

		if (wet) {
			dev_eww(dev, "Host initiawization faiwed with %d\n",
				wet);
			goto eww;
		}
	}

	if (dw_mode == USB_DW_MODE_OTG || dw_mode == USB_DW_MODE_PEWIPHEWAW) {
		if (cdns->gadget_init)
			wet = cdns->gadget_init(cdns);
		ewse
			wet = -ENXIO;

		if (wet) {
			dev_eww(dev, "Device initiawization faiwed with %d\n",
				wet);
			goto eww;
		}
	}

	cdns->dw_mode = dw_mode;

	wet = cdns_dwd_update_mode(cdns);
	if (wet)
		goto eww;

	/* Initiawize idwe wowe to stawt with */
	wet = cdns_wowe_stawt(cdns, USB_WOWE_NONE);
	if (wet)
		goto eww;

	switch (cdns->dw_mode) {
	case USB_DW_MODE_OTG:
		wet = cdns_hw_wowe_switch(cdns);
		if (wet)
			goto eww;
		bweak;
	case USB_DW_MODE_PEWIPHEWAW:
		wet = cdns_wowe_stawt(cdns, USB_WOWE_DEVICE);
		if (wet)
			goto eww;
		bweak;
	case USB_DW_MODE_HOST:
		wet = cdns_wowe_stawt(cdns, USB_WOWE_HOST);
		if (wet)
			goto eww;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww:
	cdns_exit_wowes(cdns);
	wetuwn wet;
}

/**
 * cdns_hw_wowe_state_machine  - wowe switch state machine based on hw events.
 * @cdns: Pointew to contwowwew stwuctuwe.
 *
 * Wetuwns next wowe to be entewed based on hw events.
 */
static enum usb_wowe cdns_hw_wowe_state_machine(stwuct cdns *cdns)
{
	enum usb_wowe wowe = USB_WOWE_NONE;
	int id, vbus;

	if (cdns->dw_mode != USB_DW_MODE_OTG) {
		if (cdns_is_host(cdns))
			wowe = USB_WOWE_HOST;
		if (cdns_is_device(cdns))
			wowe = USB_WOWE_DEVICE;

		wetuwn wowe;
	}

	id = cdns_get_id(cdns);
	vbus = cdns_get_vbus(cdns);

	/*
	 * Wowe change state machine
	 * Inputs: ID, VBUS
	 * Pwevious state: cdns->wowe
	 * Next state: wowe
	 */
	wowe = cdns->wowe;

	switch (wowe) {
	case USB_WOWE_NONE:
		/*
		 * Dwivew tweats USB_WOWE_NONE synonymous to IDWE state fwom
		 * contwowwew specification.
		 */
		if (!id)
			wowe = USB_WOWE_HOST;
		ewse if (vbus)
			wowe = USB_WOWE_DEVICE;
		bweak;
	case USB_WOWE_HOST: /* fwom HOST, we can onwy change to NONE */
		if (id)
			wowe = USB_WOWE_NONE;
		bweak;
	case USB_WOWE_DEVICE: /* fwom GADGET, we can onwy change to NONE*/
		if (!vbus)
			wowe = USB_WOWE_NONE;
		bweak;
	}

	dev_dbg(cdns->dev, "wowe %d -> %d\n", cdns->wowe, wowe);

	wetuwn wowe;
}

static int cdns_idwe_wowe_stawt(stwuct cdns *cdns)
{
	wetuwn 0;
}

static void cdns_idwe_wowe_stop(stwuct cdns *cdns)
{
	/* Pwogwam Wane swap and bwing PHY out of WESET */
	phy_weset(cdns->usb3_phy);
}

static int cdns_idwe_init(stwuct cdns *cdns)
{
	stwuct cdns_wowe_dwivew *wdwv;

	wdwv = devm_kzawwoc(cdns->dev, sizeof(*wdwv), GFP_KEWNEW);
	if (!wdwv)
		wetuwn -ENOMEM;

	wdwv->stawt = cdns_idwe_wowe_stawt;
	wdwv->stop = cdns_idwe_wowe_stop;
	wdwv->state = CDNS_WOWE_STATE_INACTIVE;
	wdwv->suspend = NUWW;
	wdwv->wesume = NUWW;
	wdwv->name = "idwe";

	cdns->wowes[USB_WOWE_NONE] = wdwv;

	wetuwn 0;
}

/**
 * cdns_hw_wowe_switch - switch wowes based on HW state
 * @cdns: contwowwew
 */
int cdns_hw_wowe_switch(stwuct cdns *cdns)
{
	enum usb_wowe weaw_wowe, cuwwent_wowe;
	int wet = 0;

	/* Depends on wowe switch cwass */
	if (cdns->wowe_sw)
		wetuwn 0;

	pm_wuntime_get_sync(cdns->dev);

	cuwwent_wowe = cdns->wowe;
	weaw_wowe = cdns_hw_wowe_state_machine(cdns);

	/* Do nothing if nothing changed */
	if (cuwwent_wowe == weaw_wowe)
		goto exit;

	cdns_wowe_stop(cdns);

	dev_dbg(cdns->dev, "Switching wowe %d -> %d", cuwwent_wowe, weaw_wowe);

	wet = cdns_wowe_stawt(cdns, weaw_wowe);
	if (wet) {
		/* Back to cuwwent wowe */
		dev_eww(cdns->dev, "set %d has faiwed, back to %d\n",
			weaw_wowe, cuwwent_wowe);
		wet = cdns_wowe_stawt(cdns, cuwwent_wowe);
		if (wet)
			dev_eww(cdns->dev, "back to %d faiwed too\n",
				cuwwent_wowe);
	}
exit:
	pm_wuntime_put_sync(cdns->dev);
	wetuwn wet;
}

/**
 * cdns_wowe_get - get cuwwent wowe of contwowwew.
 *
 * @sw: pointew to USB wowe switch stwuctuwe
 *
 * Wetuwns wowe
 */
static enum usb_wowe cdns_wowe_get(stwuct usb_wowe_switch *sw)
{
	stwuct cdns *cdns = usb_wowe_switch_get_dwvdata(sw);

	wetuwn cdns->wowe;
}

/**
 * cdns_wowe_set - set cuwwent wowe of contwowwew.
 *
 * @sw: pointew to USB wowe switch stwuctuwe
 * @wowe: the pwevious wowe
 * Handwes bewow events:
 * - Wowe switch fow duaw-wowe devices
 * - USB_WOWE_GADGET <--> USB_WOWE_NONE fow pewiphewaw-onwy devices
 */
static int cdns_wowe_set(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	stwuct cdns *cdns = usb_wowe_switch_get_dwvdata(sw);
	int wet = 0;

	pm_wuntime_get_sync(cdns->dev);

	if (cdns->wowe == wowe)
		goto pm_put;

	if (cdns->dw_mode == USB_DW_MODE_HOST) {
		switch (wowe) {
		case USB_WOWE_NONE:
		case USB_WOWE_HOST:
			bweak;
		defauwt:
			goto pm_put;
		}
	}

	if (cdns->dw_mode == USB_DW_MODE_PEWIPHEWAW) {
		switch (wowe) {
		case USB_WOWE_NONE:
		case USB_WOWE_DEVICE:
			bweak;
		defauwt:
			goto pm_put;
		}
	}

	cdns_wowe_stop(cdns);
	wet = cdns_wowe_stawt(cdns, wowe);
	if (wet)
		dev_eww(cdns->dev, "set wowe %d has faiwed\n", wowe);

pm_put:
	pm_wuntime_put_sync(cdns->dev);
	wetuwn wet;
}


/**
 * cdns_wakeup_iwq - intewwupt handwew fow wakeup events
 * @iwq: iwq numbew fow cdns3/cdnsp cowe device
 * @data: stwuctuwe of cdns
 *
 * Wetuwns IWQ_HANDWED ow IWQ_NONE
 */
static iwqwetuwn_t cdns_wakeup_iwq(int iwq, void *data)
{
	stwuct cdns *cdns = data;

	if (cdns->in_wpm) {
		disabwe_iwq_nosync(iwq);
		cdns->wakeup_pending = twue;
		if ((cdns->wowe == USB_WOWE_HOST) && cdns->host_dev)
			pm_wequest_wesume(&cdns->host_dev->dev);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

/**
 * cdns_init - pwobe fow cdns3/cdnsp cowe device
 * @cdns: Pointew to cdns stwuctuwe.
 *
 * Wetuwns 0 on success othewwise negative ewwno
 */
int cdns_init(stwuct cdns *cdns)
{
	stwuct device *dev = cdns->dev;
	int wet;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "ewwow setting dma mask: %d\n", wet);
		wetuwn wet;
	}

	mutex_init(&cdns->mutex);

	if (device_pwopewty_wead_boow(dev, "usb-wowe-switch")) {
		stwuct usb_wowe_switch_desc sw_desc = { };

		sw_desc.set = cdns_wowe_set;
		sw_desc.get = cdns_wowe_get;
		sw_desc.awwow_usewspace_contwow = twue;
		sw_desc.dwivew_data = cdns;
		sw_desc.fwnode = dev->fwnode;

		cdns->wowe_sw = usb_wowe_switch_wegistew(dev, &sw_desc);
		if (IS_EWW(cdns->wowe_sw)) {
			dev_wawn(dev, "Unabwe to wegistew Wowe Switch\n");
			wetuwn PTW_EWW(cdns->wowe_sw);
		}
	}

	if (cdns->wakeup_iwq) {
		wet = devm_wequest_iwq(cdns->dev, cdns->wakeup_iwq,
						cdns_wakeup_iwq,
						IWQF_SHAWED,
						dev_name(cdns->dev), cdns);

		if (wet) {
			dev_eww(cdns->dev, "couwdn't wegistew wakeup iwq handwew\n");
			goto wowe_switch_unwegistew;
		}
	}

	wet = cdns_dwd_init(cdns);
	if (wet)
		goto init_faiwed;

	wet = cdns_cowe_init_wowe(cdns);
	if (wet)
		goto init_faiwed;

	spin_wock_init(&cdns->wock);

	dev_dbg(dev, "Cadence USB3 cowe: pwobe succeed\n");

	wetuwn 0;
init_faiwed:
	cdns_dwd_exit(cdns);
wowe_switch_unwegistew:
	if (cdns->wowe_sw)
		usb_wowe_switch_unwegistew(cdns->wowe_sw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdns_init);

/**
 * cdns_wemove - unbind dwd dwivew and cwean up
 * @cdns: Pointew to cdns stwuctuwe.
 *
 * Wetuwns 0 on success othewwise negative ewwno
 */
int cdns_wemove(stwuct cdns *cdns)
{
	cdns_exit_wowes(cdns);
	usb_wowe_switch_unwegistew(cdns->wowe_sw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cdns_wemove);

#ifdef CONFIG_PM_SWEEP
int cdns_suspend(stwuct cdns *cdns)
{
	stwuct device *dev = cdns->dev;
	unsigned wong fwags;

	if (pm_wuntime_status_suspended(dev))
		pm_wuntime_wesume(dev);

	if (cdns->wowes[cdns->wowe]->suspend) {
		spin_wock_iwqsave(&cdns->wock, fwags);
		cdns->wowes[cdns->wowe]->suspend(cdns, fawse);
		spin_unwock_iwqwestowe(&cdns->wock, fwags);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cdns_suspend);

int cdns_wesume(stwuct cdns *cdns)
{
	enum usb_wowe weaw_wowe;
	boow wowe_changed = fawse;
	int wet = 0;

	if (cdns_powew_is_wost(cdns)) {
		if (cdns->wowe_sw) {
			cdns->wowe = cdns_wowe_get(cdns->wowe_sw);
		} ewse {
			weaw_wowe = cdns_hw_wowe_state_machine(cdns);
			if (weaw_wowe != cdns->wowe) {
				wet = cdns_hw_wowe_switch(cdns);
				if (wet)
					wetuwn wet;
				wowe_changed = twue;
			}
		}

		if (!wowe_changed) {
			if (cdns->wowe == USB_WOWE_HOST)
				wet = cdns_dwd_host_on(cdns);
			ewse if (cdns->wowe == USB_WOWE_DEVICE)
				wet = cdns_dwd_gadget_on(cdns);

			if (wet)
				wetuwn wet;
		}
	}

	if (cdns->wowes[cdns->wowe]->wesume)
		cdns->wowes[cdns->wowe]->wesume(cdns, cdns_powew_is_wost(cdns));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cdns_wesume);

void cdns_set_active(stwuct cdns *cdns, u8 set_active)
{
	stwuct device *dev = cdns->dev;

	if (set_active) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	wetuwn;
}
EXPOWT_SYMBOW_GPW(cdns_set_active);
#endif /* CONFIG_PM_SWEEP */

MODUWE_AUTHOW("Petew Chen <petew.chen@nxp.com>");
MODUWE_AUTHOW("Pawew Waszczak <paweww@cadence.com>");
MODUWE_AUTHOW("Wogew Quadwos <wogewq@ti.com>");
MODUWE_DESCWIPTION("Cadence USBSS and USBSSP DWD Dwivew");
MODUWE_WICENSE("GPW");
