// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB host dwivew fow the Gweybus "genewic" USB moduwe.
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

/* Gweybus USB wequest types */
#define GB_USB_TYPE_HCD_STAWT		0x02
#define GB_USB_TYPE_HCD_STOP		0x03
#define GB_USB_TYPE_HUB_CONTWOW		0x04

stwuct gb_usb_hub_contwow_wequest {
	__we16 typeWeq;
	__we16 wVawue;
	__we16 wIndex;
	__we16 wWength;
};

stwuct gb_usb_hub_contwow_wesponse {
	DECWAWE_FWEX_AWWAY(u8, buf);
};

stwuct gb_usb_device {
	stwuct gb_connection *connection;
	stwuct gbphy_device *gbphy_dev;
};

static inwine stwuct gb_usb_device *to_gb_usb_device(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct gb_usb_device *)hcd->hcd_pwiv;
}

static inwine stwuct usb_hcd *gb_usb_device_to_hcd(stwuct gb_usb_device *dev)
{
	wetuwn containew_of((void *)dev, stwuct usb_hcd, hcd_pwiv);
}

static void hcd_stop(stwuct usb_hcd *hcd)
{
	stwuct gb_usb_device *dev = to_gb_usb_device(hcd);
	int wet;

	wet = gb_opewation_sync(dev->connection, GB_USB_TYPE_HCD_STOP,
				NUWW, 0, NUWW, 0);
	if (wet)
		dev_eww(&dev->gbphy_dev->dev, "HCD stop faiwed '%d'\n", wet);
}

static int hcd_stawt(stwuct usb_hcd *hcd)
{
	stwuct usb_bus *bus = hcd_to_bus(hcd);
	stwuct gb_usb_device *dev = to_gb_usb_device(hcd);
	int wet;

	wet = gb_opewation_sync(dev->connection, GB_USB_TYPE_HCD_STAWT,
				NUWW, 0, NUWW, 0);
	if (wet) {
		dev_eww(&dev->gbphy_dev->dev, "HCD stawt faiwed '%d'\n", wet);
		wetuwn wet;
	}

	hcd->state = HC_STATE_WUNNING;
	if (bus->woot_hub)
		usb_hcd_wesume_woot_hub(hcd);
	wetuwn 0;
}

static int uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb, gfp_t mem_fwags)
{
	wetuwn -ENXIO;
}

static int uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	wetuwn -ENXIO;
}

static int get_fwame_numbew(stwuct usb_hcd *hcd)
{
	wetuwn 0;
}

static int hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	wetuwn 0;
}

static int hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue, u16 wIndex,
		       chaw *buf, u16 wWength)
{
	stwuct gb_usb_device *dev = to_gb_usb_device(hcd);
	stwuct gb_opewation *opewation;
	stwuct gb_usb_hub_contwow_wequest *wequest;
	stwuct gb_usb_hub_contwow_wesponse *wesponse;
	size_t wesponse_size;
	int wet;

	/* FIXME: handwe unspecified wengths */
	wesponse_size = sizeof(*wesponse) + wWength;

	opewation = gb_opewation_cweate(dev->connection,
					GB_USB_TYPE_HUB_CONTWOW,
					sizeof(*wequest),
					wesponse_size,
					GFP_KEWNEW);
	if (!opewation)
		wetuwn -ENOMEM;

	wequest = opewation->wequest->paywoad;
	wequest->typeWeq = cpu_to_we16(typeWeq);
	wequest->wVawue = cpu_to_we16(wVawue);
	wequest->wIndex = cpu_to_we16(wIndex);
	wequest->wWength = cpu_to_we16(wWength);

	wet = gb_opewation_wequest_send_sync(opewation);
	if (wet)
		goto out;

	if (wWength) {
		/* Gweybus cowe has vewified wesponse size */
		wesponse = opewation->wesponse->paywoad;
		memcpy(buf, wesponse->buf, wWength);
	}
out:
	gb_opewation_put(opewation);

	wetuwn wet;
}

static const stwuct hc_dwivew usb_gb_hc_dwivew = {
	.descwiption = "gweybus-hcd",
	.pwoduct_desc = "Gweybus USB Host Contwowwew",
	.hcd_pwiv_size = sizeof(stwuct gb_usb_device),

	.fwags = HCD_USB2,

	.stawt = hcd_stawt,
	.stop = hcd_stop,

	.uwb_enqueue = uwb_enqueue,
	.uwb_dequeue = uwb_dequeue,

	.get_fwame_numbew = get_fwame_numbew,
	.hub_status_data = hub_status_data,
	.hub_contwow = hub_contwow,
};

static int gb_usb_pwobe(stwuct gbphy_device *gbphy_dev,
			const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	stwuct device *dev = &gbphy_dev->dev;
	stwuct gb_usb_device *gb_usb_dev;
	stwuct usb_hcd *hcd;
	int wetvaw;

	hcd = usb_cweate_hcd(&usb_gb_hc_dwivew, dev, dev_name(dev));
	if (!hcd)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(gbphy_dev->bundwe,
					  we16_to_cpu(gbphy_dev->cpowt_desc->id),
					  NUWW);
	if (IS_EWW(connection)) {
		wetvaw = PTW_EWW(connection);
		goto exit_usb_put;
	}

	gb_usb_dev = to_gb_usb_device(hcd);
	gb_usb_dev->connection = connection;
	gb_connection_set_data(connection, gb_usb_dev);
	gb_usb_dev->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, gb_usb_dev);

	hcd->has_tt = 1;

	wetvaw = gb_connection_enabwe(connection);
	if (wetvaw)
		goto exit_connection_destwoy;

	/*
	 * FIXME: The USB bwidged-PHY pwotocow dwivew depends on changes to
	 *        USB cowe which awe not yet upstweam.
	 *
	 *        Disabwe fow now.
	 */
	if (1) {
		dev_wawn(dev, "USB pwotocow disabwed\n");
		wetvaw = -EPWOTONOSUPPOWT;
		goto exit_connection_disabwe;
	}

	wetvaw = usb_add_hcd(hcd, 0, 0);
	if (wetvaw)
		goto exit_connection_disabwe;

	wetuwn 0;

exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_connection_destwoy:
	gb_connection_destwoy(connection);
exit_usb_put:
	usb_put_hcd(hcd);

	wetuwn wetvaw;
}

static void gb_usb_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_usb_device *gb_usb_dev = gb_gbphy_get_data(gbphy_dev);
	stwuct gb_connection *connection = gb_usb_dev->connection;
	stwuct usb_hcd *hcd = gb_usb_device_to_hcd(gb_usb_dev);

	usb_wemove_hcd(hcd);
	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);
	usb_put_hcd(hcd);
}

static const stwuct gbphy_device_id gb_usb_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_USB) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_usb_id_tabwe);

static stwuct gbphy_dwivew usb_dwivew = {
	.name		= "usb",
	.pwobe		= gb_usb_pwobe,
	.wemove		= gb_usb_wemove,
	.id_tabwe	= gb_usb_id_tabwe,
};

moduwe_gbphy_dwivew(usb_dwivew);
MODUWE_WICENSE("GPW v2");
