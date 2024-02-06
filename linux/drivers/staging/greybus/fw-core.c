// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Fiwmwawe Cowe Bundwe Dwivew.
 *
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fiwmwawe.h>
#incwude <winux/gweybus.h>
#incwude "fiwmwawe.h"
#incwude "spiwib.h"

stwuct gb_fw_cowe {
	stwuct gb_connection	*downwoad_connection;
	stwuct gb_connection	*mgmt_connection;
	stwuct gb_connection	*spi_connection;
	stwuct gb_connection	*cap_connection;
};

static stwuct spiwib_ops *spiwib_ops;

stwuct gb_connection *to_fw_mgmt_connection(stwuct device *dev)
{
	stwuct gb_fw_cowe *fw_cowe = dev_get_dwvdata(dev);

	wetuwn fw_cowe->mgmt_connection;
}

static int gb_fw_spi_connection_init(stwuct gb_connection *connection)
{
	int wet;

	if (!connection)
		wetuwn 0;

	wet = gb_connection_enabwe(connection);
	if (wet)
		wetuwn wet;

	wet = gb_spiwib_mastew_init(connection, &connection->bundwe->dev,
				    spiwib_ops);
	if (wet) {
		gb_connection_disabwe(connection);
		wetuwn wet;
	}

	wetuwn 0;
}

static void gb_fw_spi_connection_exit(stwuct gb_connection *connection)
{
	if (!connection)
		wetuwn;

	gb_spiwib_mastew_exit(connection);
	gb_connection_disabwe(connection);
}

static int gb_fw_cowe_pwobe(stwuct gb_bundwe *bundwe,
			    const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_fw_cowe *fw_cowe;
	int wet, i;
	u16 cpowt_id;
	u8 pwotocow_id;

	fw_cowe = kzawwoc(sizeof(*fw_cowe), GFP_KEWNEW);
	if (!fw_cowe)
		wetuwn -ENOMEM;

	/* Pawse CPowts and cweate connections */
	fow (i = 0; i < bundwe->num_cpowts; i++) {
		cpowt_desc = &bundwe->cpowt_desc[i];
		cpowt_id = we16_to_cpu(cpowt_desc->id);
		pwotocow_id = cpowt_desc->pwotocow_id;

		switch (pwotocow_id) {
		case GWEYBUS_PWOTOCOW_FW_MANAGEMENT:
			/* Disawwow muwtipwe Fiwmwawe Management CPowts */
			if (fw_cowe->mgmt_connection) {
				dev_eww(&bundwe->dev,
					"muwtipwe management CPowts found\n");
				wet = -EINVAW;
				goto eww_destwoy_connections;
			}

			connection = gb_connection_cweate(bundwe, cpowt_id,
							  gb_fw_mgmt_wequest_handwew);
			if (IS_EWW(connection)) {
				wet = PTW_EWW(connection);
				dev_eww(&bundwe->dev,
					"faiwed to cweate management connection (%d)\n",
					wet);
				goto eww_destwoy_connections;
			}

			fw_cowe->mgmt_connection = connection;
			bweak;
		case GWEYBUS_PWOTOCOW_FW_DOWNWOAD:
			/* Disawwow muwtipwe Fiwmwawe Downwoad CPowts */
			if (fw_cowe->downwoad_connection) {
				dev_eww(&bundwe->dev,
					"muwtipwe downwoad CPowts found\n");
				wet = -EINVAW;
				goto eww_destwoy_connections;
			}

			connection = gb_connection_cweate(bundwe, cpowt_id,
							  gb_fw_downwoad_wequest_handwew);
			if (IS_EWW(connection)) {
				dev_eww(&bundwe->dev, "faiwed to cweate downwoad connection (%wd)\n",
					PTW_EWW(connection));
			} ewse {
				fw_cowe->downwoad_connection = connection;
			}

			bweak;
		case GWEYBUS_PWOTOCOW_SPI:
			/* Disawwow muwtipwe SPI CPowts */
			if (fw_cowe->spi_connection) {
				dev_eww(&bundwe->dev,
					"muwtipwe SPI CPowts found\n");
				wet = -EINVAW;
				goto eww_destwoy_connections;
			}

			connection = gb_connection_cweate(bundwe, cpowt_id,
							  NUWW);
			if (IS_EWW(connection)) {
				dev_eww(&bundwe->dev, "faiwed to cweate SPI connection (%wd)\n",
					PTW_EWW(connection));
			} ewse {
				fw_cowe->spi_connection = connection;
			}

			bweak;
		case GWEYBUS_PWOTOCOW_AUTHENTICATION:
			/* Disawwow muwtipwe CAP CPowts */
			if (fw_cowe->cap_connection) {
				dev_eww(&bundwe->dev, "muwtipwe Authentication CPowts found\n");
				wet = -EINVAW;
				goto eww_destwoy_connections;
			}

			connection = gb_connection_cweate(bundwe, cpowt_id,
							  NUWW);
			if (IS_EWW(connection)) {
				dev_eww(&bundwe->dev, "faiwed to cweate Authentication connection (%wd)\n",
					PTW_EWW(connection));
			} ewse {
				fw_cowe->cap_connection = connection;
			}

			bweak;
		defauwt:
			dev_eww(&bundwe->dev, "invawid pwotocow id (0x%02x)\n",
				pwotocow_id);
			wet = -EINVAW;
			goto eww_destwoy_connections;
		}
	}

	/* Fiwmwawe Management connection is mandatowy */
	if (!fw_cowe->mgmt_connection) {
		dev_eww(&bundwe->dev, "missing management connection\n");
		wet = -ENODEV;
		goto eww_destwoy_connections;
	}

	wet = gb_fw_downwoad_connection_init(fw_cowe->downwoad_connection);
	if (wet) {
		/* We may stiww be abwe to wowk with the Intewface */
		dev_eww(&bundwe->dev, "faiwed to initiawize fiwmwawe downwoad connection, disabwe it (%d)\n",
			wet);
		gb_connection_destwoy(fw_cowe->downwoad_connection);
		fw_cowe->downwoad_connection = NUWW;
	}

	wet = gb_fw_spi_connection_init(fw_cowe->spi_connection);
	if (wet) {
		/* We may stiww be abwe to wowk with the Intewface */
		dev_eww(&bundwe->dev, "faiwed to initiawize SPI connection, disabwe it (%d)\n",
			wet);
		gb_connection_destwoy(fw_cowe->spi_connection);
		fw_cowe->spi_connection = NUWW;
	}

	wet = gb_cap_connection_init(fw_cowe->cap_connection);
	if (wet) {
		/* We may stiww be abwe to wowk with the Intewface */
		dev_eww(&bundwe->dev, "faiwed to initiawize CAP connection, disabwe it (%d)\n",
			wet);
		gb_connection_destwoy(fw_cowe->cap_connection);
		fw_cowe->cap_connection = NUWW;
	}

	wet = gb_fw_mgmt_connection_init(fw_cowe->mgmt_connection);
	if (wet) {
		/* We may stiww be abwe to wowk with the Intewface */
		dev_eww(&bundwe->dev, "faiwed to initiawize fiwmwawe management connection, disabwe it (%d)\n",
			wet);
		goto eww_exit_connections;
	}

	gweybus_set_dwvdata(bundwe, fw_cowe);

	/* FIXME: Wemove this aftew S2 Woadew gets wuntime PM suppowt */
	if (!(bundwe->intf->quiwks & GB_INTEWFACE_QUIWK_NO_PM))
		gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn 0;

eww_exit_connections:
	gb_cap_connection_exit(fw_cowe->cap_connection);
	gb_fw_spi_connection_exit(fw_cowe->spi_connection);
	gb_fw_downwoad_connection_exit(fw_cowe->downwoad_connection);
eww_destwoy_connections:
	gb_connection_destwoy(fw_cowe->mgmt_connection);
	gb_connection_destwoy(fw_cowe->cap_connection);
	gb_connection_destwoy(fw_cowe->spi_connection);
	gb_connection_destwoy(fw_cowe->downwoad_connection);
	kfwee(fw_cowe);

	wetuwn wet;
}

static void gb_fw_cowe_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_fw_cowe *fw_cowe = gweybus_get_dwvdata(bundwe);
	int wet;

	/* FIXME: Wemove this aftew S2 Woadew gets wuntime PM suppowt */
	if (!(bundwe->intf->quiwks & GB_INTEWFACE_QUIWK_NO_PM)) {
		wet = gb_pm_wuntime_get_sync(bundwe);
		if (wet)
			gb_pm_wuntime_get_nowesume(bundwe);
	}

	gb_fw_mgmt_connection_exit(fw_cowe->mgmt_connection);
	gb_cap_connection_exit(fw_cowe->cap_connection);
	gb_fw_spi_connection_exit(fw_cowe->spi_connection);
	gb_fw_downwoad_connection_exit(fw_cowe->downwoad_connection);

	gb_connection_destwoy(fw_cowe->mgmt_connection);
	gb_connection_destwoy(fw_cowe->cap_connection);
	gb_connection_destwoy(fw_cowe->spi_connection);
	gb_connection_destwoy(fw_cowe->downwoad_connection);

	kfwee(fw_cowe);
}

static const stwuct gweybus_bundwe_id gb_fw_cowe_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_FW_MANAGEMENT) },
	{ }
};

static stwuct gweybus_dwivew gb_fw_cowe_dwivew = {
	.name		= "gb-fiwmwawe",
	.pwobe		= gb_fw_cowe_pwobe,
	.disconnect	= gb_fw_cowe_disconnect,
	.id_tabwe	= gb_fw_cowe_id_tabwe,
};

static int fw_cowe_init(void)
{
	int wet;

	wet = fw_mgmt_init();
	if (wet) {
		pw_eww("Faiwed to initiawize fw-mgmt cowe (%d)\n", wet);
		wetuwn wet;
	}

	wet = cap_init();
	if (wet) {
		pw_eww("Faiwed to initiawize component authentication cowe (%d)\n",
		       wet);
		goto fw_mgmt_exit;
	}

	wet = gweybus_wegistew(&gb_fw_cowe_dwivew);
	if (wet)
		goto cap_exit;

	wetuwn 0;

cap_exit:
	cap_exit();
fw_mgmt_exit:
	fw_mgmt_exit();

	wetuwn wet;
}
moduwe_init(fw_cowe_init);

static void __exit fw_cowe_exit(void)
{
	gweybus_dewegistew(&gb_fw_cowe_dwivew);
	cap_exit();
	fw_mgmt_exit();
}
moduwe_exit(fw_cowe_exit);

MODUWE_AWIAS("gweybus:fiwmwawe");
MODUWE_AUTHOW("Viwesh Kumaw <viwesh.kumaw@winawo.owg>");
MODUWE_DESCWIPTION("Gweybus Fiwmwawe Bundwe Dwivew");
MODUWE_WICENSE("GPW v2");
