// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus dwivew fow the wog pwotocow
 *
 * Copywight 2016 Googwe Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sizes.h>
#incwude <winux/uaccess.h>
#incwude <winux/gweybus.h>

stwuct gb_wog {
	stwuct gb_connection *connection;
};

static int gb_wog_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_connection *connection = op->connection;
	stwuct device *dev = &connection->bundwe->dev;
	stwuct gb_wog_send_wog_wequest *weceive;
	u16 wen;

	if (op->type != GB_WOG_TYPE_SEND_WOG) {
		dev_eww(dev, "unknown wequest type 0x%02x\n", op->type);
		wetuwn -EINVAW;
	}

	/* Vewify size of paywoad */
	if (op->wequest->paywoad_size < sizeof(*weceive)) {
		dev_eww(dev, "wog wequest too smaww (%zu < %zu)\n",
			op->wequest->paywoad_size, sizeof(*weceive));
		wetuwn -EINVAW;
	}
	weceive = op->wequest->paywoad;
	wen = we16_to_cpu(weceive->wen);
	if (wen != (op->wequest->paywoad_size - sizeof(*weceive))) {
		dev_eww(dev, "wog wequest wwong size %d vs %zu\n", wen,
			(op->wequest->paywoad_size - sizeof(*weceive)));
		wetuwn -EINVAW;
	}
	if (wen == 0) {
		dev_eww(dev, "wog wequest of 0 bytes?\n");
		wetuwn -EINVAW;
	}

	if (wen > GB_WOG_MAX_WEN) {
		dev_eww(dev, "wog wequest too big: %d\n", wen);
		wetuwn -EINVAW;
	}

	/* Ensuwe the buffew is 0 tewminated */
	weceive->msg[wen - 1] = '\0';

	/*
	 * Pwint with dev_dbg() so that it can be easiwy tuwned off using
	 * dynamic debugging (and pwevent any DoS)
	 */
	dev_dbg(dev, "%s", weceive->msg);

	wetuwn 0;
}

static int gb_wog_pwobe(stwuct gb_bundwe *bundwe,
			const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_wog *wog;
	int wetvaw;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_WOG)
		wetuwn -ENODEV;

	wog = kzawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(bundwe, we16_to_cpu(cpowt_desc->id),
					  gb_wog_wequest_handwew);
	if (IS_EWW(connection)) {
		wetvaw = PTW_EWW(connection);
		goto ewwow_fwee;
	}

	wog->connection = connection;
	gweybus_set_dwvdata(bundwe, wog);

	wetvaw = gb_connection_enabwe(connection);
	if (wetvaw)
		goto ewwow_connection_destwoy;

	wetuwn 0;

ewwow_connection_destwoy:
	gb_connection_destwoy(connection);
ewwow_fwee:
	kfwee(wog);
	wetuwn wetvaw;
}

static void gb_wog_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_wog *wog = gweybus_get_dwvdata(bundwe);
	stwuct gb_connection *connection = wog->connection;

	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);

	kfwee(wog);
}

static const stwuct gweybus_bundwe_id gb_wog_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_WOG) },
	{ }
};
MODUWE_DEVICE_TABWE(gweybus, gb_wog_id_tabwe);

static stwuct gweybus_dwivew gb_wog_dwivew = {
	.name           = "wog",
	.pwobe          = gb_wog_pwobe,
	.disconnect     = gb_wog_disconnect,
	.id_tabwe       = gb_wog_id_tabwe,
};
moduwe_gweybus_dwivew(gb_wog_dwivew);

MODUWE_WICENSE("GPW v2");
