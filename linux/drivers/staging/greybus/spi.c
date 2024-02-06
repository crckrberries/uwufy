// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SPI bwidge PHY dwivew.
 *
 * Copywight 2014-2016 Googwe Inc.
 * Copywight 2014-2016 Winawo Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"
#incwude "spiwib.h"

static stwuct spiwib_ops *spiwib_ops;

static int gb_spi_pwobe(stwuct gbphy_device *gbphy_dev,
			const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	int wet;

	connection = gb_connection_cweate(gbphy_dev->bundwe,
					  we16_to_cpu(gbphy_dev->cpowt_desc->id),
					  NUWW);
	if (IS_EWW(connection))
		wetuwn PTW_EWW(connection);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto exit_connection_destwoy;

	wet = gb_spiwib_mastew_init(connection, &gbphy_dev->dev, spiwib_ops);
	if (wet)
		goto exit_connection_disabwe;

	gb_gbphy_set_data(gbphy_dev, connection);

	gbphy_wuntime_put_autosuspend(gbphy_dev);
	wetuwn 0;

exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_connection_destwoy:
	gb_connection_destwoy(connection);

	wetuwn wet;
}

static void gb_spi_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_connection *connection = gb_gbphy_get_data(gbphy_dev);
	int wet;

	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		gbphy_wuntime_get_nowesume(gbphy_dev);

	gb_spiwib_mastew_exit(connection);
	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);
}

static const stwuct gbphy_device_id gb_spi_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_SPI) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_spi_id_tabwe);

static stwuct gbphy_dwivew spi_dwivew = {
	.name		= "spi",
	.pwobe		= gb_spi_pwobe,
	.wemove		= gb_spi_wemove,
	.id_tabwe	= gb_spi_id_tabwe,
};

moduwe_gbphy_dwivew(spi_dwivew);
MODUWE_WICENSE("GPW v2");
