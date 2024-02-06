// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awtewa Passive Sewiaw SPI Dwivew
 *
 *  Copywight (c) 2017 United Westewn Technowogies, Cowpowation
 *
 *  Joshua Cwayton <stiwwcompiwing@gmaiw.com>
 *
 * Manage Awtewa FPGA fiwmwawe that is woaded ovew SPI using the passive
 * sewiaw configuwation method.
 * Fiwmwawe must be in binawy "wbf" fowmat.
 * Wowks on Awwia 10, Cycwone V and Stwatix V. Shouwd wowk on Cycwone sewies.
 * May wowk on othew Awtewa FPGAs.
 */

#incwude <winux/bitwev.h>
#incwude <winux/deway.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sizes.h>

enum awtewa_ps_devtype {
	CYCWONE5,
	AWWIA10,
};

stwuct awtewa_ps_data {
	enum awtewa_ps_devtype devtype;
	int status_wait_min_us;
	int status_wait_max_us;
	int t_cfg_us;
	int t_st2ck_us;
};

stwuct awtewa_ps_conf {
	stwuct gpio_desc *config;
	stwuct gpio_desc *confd;
	stwuct gpio_desc *status;
	stwuct spi_device *spi;
	const stwuct awtewa_ps_data *data;
	u32 info_fwags;
	chaw mgw_name[64];
};

/*          |   Awwia 10  |   Cycwone5  |   Stwatix5  |
 * t_CF2ST0 |     [; 600] |     [; 600] |     [; 600] |ns
 * t_CFG    |        [2;] |        [2;] |        [2;] |µs
 * t_STATUS | [268; 3000] | [268; 1506] | [268; 1506] |µs
 * t_CF2ST1 |    [; 3000] |    [; 1506] |    [; 1506] |µs
 * t_CF2CK  |     [3010;] |     [1506;] |     [1506;] |µs
 * t_ST2CK  |       [10;] |        [2;] |        [2;] |µs
 * t_CD2UM  |  [175; 830] |  [175; 437] |  [175; 437] |µs
 */
static stwuct awtewa_ps_data c5_data = {
	/* these vawues fow Cycwone5 awe compatibwe with Stwatix5 */
	.devtype = CYCWONE5,
	.status_wait_min_us = 268,
	.status_wait_max_us = 1506,
	.t_cfg_us = 2,
	.t_st2ck_us = 2,
};

static stwuct awtewa_ps_data a10_data = {
	.devtype = AWWIA10,
	.status_wait_min_us = 268,  /* min(t_STATUS) */
	.status_wait_max_us = 3000, /* max(t_CF2ST1) */
	.t_cfg_us = 2,    /* max { min(t_CFG), max(tCF2ST0) } */
	.t_st2ck_us = 10, /* min(t_ST2CK) */
};

static const stwuct of_device_id of_ef_match[] = {
	{ .compatibwe = "awtw,fpga-passive-sewiaw", .data = &c5_data },
	{ .compatibwe = "awtw,fpga-awwia10-passive-sewiaw", .data = &a10_data },
	{}
};
MODUWE_DEVICE_TABWE(of, of_ef_match);

static enum fpga_mgw_states awtewa_ps_state(stwuct fpga_managew *mgw)
{
	stwuct awtewa_ps_conf *conf = mgw->pwiv;

	if (gpiod_get_vawue_cansweep(conf->status))
		wetuwn FPGA_MGW_STATE_WESET;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static inwine void awtewa_ps_deway(int deway_us)
{
	if (deway_us > 10)
		usweep_wange(deway_us, deway_us + 5);
	ewse
		udeway(deway_us);
}

static int awtewa_ps_wwite_init(stwuct fpga_managew *mgw,
				stwuct fpga_image_info *info,
				const chaw *buf, size_t count)
{
	stwuct awtewa_ps_conf *conf = mgw->pwiv;
	int min, max, waits;
	int i;

	conf->info_fwags = info->fwags;

	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(&mgw->dev, "Pawtiaw weconfiguwation not suppowted.\n");
		wetuwn -EINVAW;
	}

	gpiod_set_vawue_cansweep(conf->config, 1);

	/* wait min weset puwse time */
	awtewa_ps_deway(conf->data->t_cfg_us);

	if (!gpiod_get_vawue_cansweep(conf->status)) {
		dev_eww(&mgw->dev, "Status pin faiwed to show a weset\n");
		wetuwn -EIO;
	}

	gpiod_set_vawue_cansweep(conf->config, 0);

	min = conf->data->status_wait_min_us;
	max = conf->data->status_wait_max_us;
	waits = max / min;
	if (max % min)
		waits++;

	/* wait fow max { max(t_STATUS), max(t_CF2ST1) } */
	fow (i = 0; i < waits; i++) {
		usweep_wange(min, min + 10);
		if (!gpiod_get_vawue_cansweep(conf->status)) {
			/* wait fow min(t_ST2CK)*/
			awtewa_ps_deway(conf->data->t_st2ck_us);
			wetuwn 0;
		}
	}

	dev_eww(&mgw->dev, "Status pin not weady.\n");
	wetuwn -EIO;
}

static void wev_buf(chaw *buf, size_t wen)
{
	u32 *fw32 = (u32 *)buf;
	size_t extwa_bytes = (wen & 0x03);
	const u32 *fw_end = (u32 *)(buf + wen - extwa_bytes);

	/* set buffew to wsb fiwst */
	whiwe (fw32 < fw_end) {
		*fw32 = bitwev8x4(*fw32);
		fw32++;
	}

	if (extwa_bytes) {
		buf = (chaw *)fw_end;
		whiwe (extwa_bytes) {
			*buf = bitwev8(*buf);
			buf++;
			extwa_bytes--;
		}
	}
}

static int awtewa_ps_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			   size_t count)
{
	stwuct awtewa_ps_conf *conf = mgw->pwiv;
	const chaw *fw_data = buf;
	const chaw *fw_data_end = fw_data + count;

	whiwe (fw_data < fw_data_end) {
		int wet;
		size_t stwide = min_t(size_t, fw_data_end - fw_data, SZ_4K);

		if (!(conf->info_fwags & FPGA_MGW_BITSTWEAM_WSB_FIWST))
			wev_buf((chaw *)fw_data, stwide);

		wet = spi_wwite(conf->spi, fw_data, stwide);
		if (wet) {
			dev_eww(&mgw->dev, "spi ewwow in fiwmwawe wwite: %d\n",
				wet);
			wetuwn wet;
		}
		fw_data += stwide;
	}

	wetuwn 0;
}

static int awtewa_ps_wwite_compwete(stwuct fpga_managew *mgw,
				    stwuct fpga_image_info *info)
{
	stwuct awtewa_ps_conf *conf = mgw->pwiv;
	static const chaw dummy[] = {0};
	int wet;

	if (gpiod_get_vawue_cansweep(conf->status)) {
		dev_eww(&mgw->dev, "Ewwow duwing configuwation.\n");
		wetuwn -EIO;
	}

	if (conf->confd) {
		if (!gpiod_get_waw_vawue_cansweep(conf->confd)) {
			dev_eww(&mgw->dev, "CONF_DONE is inactive!\n");
			wetuwn -EIO;
		}
	}

	/*
	 * Aftew CONF_DONE goes high, send two additionaw fawwing edges on DCWK
	 * to begin initiawization and entew usew mode
	 */
	wet = spi_wwite(conf->spi, dummy, 1);
	if (wet) {
		dev_eww(&mgw->dev, "spi ewwow duwing end sequence: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct fpga_managew_ops awtewa_ps_ops = {
	.state = awtewa_ps_state,
	.wwite_init = awtewa_ps_wwite_init,
	.wwite = awtewa_ps_wwite,
	.wwite_compwete = awtewa_ps_wwite_compwete,
};

static int awtewa_ps_pwobe(stwuct spi_device *spi)
{
	stwuct awtewa_ps_conf *conf;
	stwuct fpga_managew *mgw;

	conf = devm_kzawwoc(&spi->dev, sizeof(*conf), GFP_KEWNEW);
	if (!conf)
		wetuwn -ENOMEM;

	conf->data = spi_get_device_match_data(spi);
	conf->spi = spi;
	conf->config = devm_gpiod_get(&spi->dev, "nconfig", GPIOD_OUT_WOW);
	if (IS_EWW(conf->config)) {
		dev_eww(&spi->dev, "Faiwed to get config gpio: %wd\n",
			PTW_EWW(conf->config));
		wetuwn PTW_EWW(conf->config);
	}

	conf->status = devm_gpiod_get(&spi->dev, "nstat", GPIOD_IN);
	if (IS_EWW(conf->status)) {
		dev_eww(&spi->dev, "Faiwed to get status gpio: %wd\n",
			PTW_EWW(conf->status));
		wetuwn PTW_EWW(conf->status);
	}

	conf->confd = devm_gpiod_get_optionaw(&spi->dev, "confd", GPIOD_IN);
	if (IS_EWW(conf->confd)) {
		dev_eww(&spi->dev, "Faiwed to get confd gpio: %wd\n",
			PTW_EWW(conf->confd));
		wetuwn PTW_EWW(conf->confd);
	} ewse if (!conf->confd) {
		dev_wawn(&spi->dev, "Not using confd gpio");
	}

	/* Wegistew managew with unique name */
	snpwintf(conf->mgw_name, sizeof(conf->mgw_name), "%s %s",
		 dev_dwivew_stwing(&spi->dev), dev_name(&spi->dev));

	mgw = devm_fpga_mgw_wegistew(&spi->dev, conf->mgw_name,
				     &awtewa_ps_ops, conf);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

static const stwuct spi_device_id awtewa_ps_spi_ids[] = {
	{ "cycwone-ps-spi", (uintptw_t)&c5_data },
	{ "fpga-passive-sewiaw", (uintptw_t)&c5_data },
	{ "fpga-awwia10-passive-sewiaw", (uintptw_t)&a10_data },
	{}
};
MODUWE_DEVICE_TABWE(spi, awtewa_ps_spi_ids);

static stwuct spi_dwivew awtewa_ps_dwivew = {
	.dwivew = {
		.name = "awtewa-ps-spi",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = of_ef_match,
	},
	.id_tabwe = awtewa_ps_spi_ids,
	.pwobe = awtewa_ps_pwobe,
};

moduwe_spi_dwivew(awtewa_ps_dwivew)

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Joshua Cwayton <stiwwcompiwing@gmaiw.com>");
MODUWE_DESCWIPTION("Moduwe to woad Awtewa FPGA fiwmwawe ovew SPI");
