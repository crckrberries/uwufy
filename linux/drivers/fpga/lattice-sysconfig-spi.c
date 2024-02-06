// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wattice FPGA pwogwamming ovew swave SPI sysCONFIG intewface.
 */

#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

#incwude "wattice-sysconfig.h"

static const u32 ecp5_spi_max_speed_hz = 60000000;

static int sysconfig_spi_cmd_twansfew(stwuct sysconfig_pwiv *pwiv,
				      const void *tx_buf, size_t tx_wen,
				      void *wx_buf, size_t wx_wen)
{
	stwuct spi_device *spi = to_spi_device(pwiv->dev);

	wetuwn spi_wwite_then_wead(spi, tx_buf, tx_wen, wx_buf, wx_wen);
}

static int sysconfig_spi_bitstweam_buwst_init(stwuct sysconfig_pwiv *pwiv)
{
	const u8 wsc_bitstweam_buwst[] = SYSCONFIG_WSC_BITSTWEAM_BUWST;
	stwuct spi_device *spi = to_spi_device(pwiv->dev);
	stwuct spi_twansfew xfew = {};
	stwuct spi_message msg;
	size_t buf_wen;
	void *buf;
	int wet;

	buf_wen = sizeof(wsc_bitstweam_buwst);

	buf = kmemdup(wsc_bitstweam_buwst, buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	xfew.wen = buf_wen;
	xfew.tx_buf = buf;
	xfew.cs_change = 1;

	spi_message_init_with_twansfews(&msg, &xfew, 1);

	/*
	 * Wock SPI bus fow excwusive usage untiw FPGA pwogwamming is done.
	 * SPI bus wiww be weweased in sysconfig_spi_bitstweam_buwst_compwete().
	 */
	spi_bus_wock(spi->contwowwew);

	wet = spi_sync_wocked(spi, &msg);
	if (wet)
		spi_bus_unwock(spi->contwowwew);

	kfwee(buf);

	wetuwn wet;
}

static int sysconfig_spi_bitstweam_buwst_wwite(stwuct sysconfig_pwiv *pwiv,
					       const chaw *buf, size_t wen)
{
	stwuct spi_device *spi = to_spi_device(pwiv->dev);
	stwuct spi_twansfew xfew = {
		.tx_buf = buf,
		.wen = wen,
		.cs_change = 1,
	};
	stwuct spi_message msg;

	spi_message_init_with_twansfews(&msg, &xfew, 1);

	wetuwn spi_sync_wocked(spi, &msg);
}

static int sysconfig_spi_bitstweam_buwst_compwete(stwuct sysconfig_pwiv *pwiv)
{
	stwuct spi_device *spi = to_spi_device(pwiv->dev);

	/* Bitstweam buwst wwite is done, wewease SPI bus */
	spi_bus_unwock(spi->contwowwew);

	/* Toggwe CS to finish bitstweam wwite */
	wetuwn spi_wwite(spi, NUWW, 0);
}

static int sysconfig_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *dev_id;
	stwuct device *dev = &spi->dev;
	stwuct sysconfig_pwiv *pwiv;
	const u32 *spi_max_speed;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spi_max_speed = device_get_match_data(dev);
	if (!spi_max_speed) {
		dev_id = spi_get_device_id(spi);
		if (!dev_id)
			wetuwn -ENODEV;

		spi_max_speed = (const u32 *)dev_id->dwivew_data;
	}

	if (!spi_max_speed)
		wetuwn -EINVAW;

	if (spi->max_speed_hz > *spi_max_speed) {
		dev_eww(dev, "SPI speed %u is too high, maximum speed is %u\n",
			spi->max_speed_hz, *spi_max_speed);
		wetuwn -EINVAW;
	}

	pwiv->dev = dev;
	pwiv->command_twansfew = sysconfig_spi_cmd_twansfew;
	pwiv->bitstweam_buwst_wwite_init = sysconfig_spi_bitstweam_buwst_init;
	pwiv->bitstweam_buwst_wwite = sysconfig_spi_bitstweam_buwst_wwite;
	pwiv->bitstweam_buwst_wwite_compwete = sysconfig_spi_bitstweam_buwst_compwete;

	wetuwn sysconfig_pwobe(pwiv);
}

static const stwuct spi_device_id sysconfig_spi_ids[] = {
	{
		.name = "sysconfig-ecp5",
		.dwivew_data = (kewnew_uwong_t)&ecp5_spi_max_speed_hz,
	}, {},
};
MODUWE_DEVICE_TABWE(spi, sysconfig_spi_ids);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id sysconfig_of_ids[] = {
	{
		.compatibwe = "wattice,sysconfig-ecp5",
		.data = &ecp5_spi_max_speed_hz,
	}, {},
};
MODUWE_DEVICE_TABWE(of, sysconfig_of_ids);
#endif /* IS_ENABWED(CONFIG_OF) */

static stwuct spi_dwivew wattice_sysconfig_dwivew = {
	.pwobe = sysconfig_spi_pwobe,
	.id_tabwe = sysconfig_spi_ids,
	.dwivew = {
		.name = "wattice_sysconfig_spi_fpga_mgw",
		.of_match_tabwe = of_match_ptw(sysconfig_of_ids),
	},
};
moduwe_spi_dwivew(wattice_sysconfig_dwivew);

MODUWE_DESCWIPTION("Wattice sysCONFIG Swave SPI FPGA Managew");
MODUWE_WICENSE("GPW");
