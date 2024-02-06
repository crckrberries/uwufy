// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xiwinx Spawtan6 and 7 Sewies Swave Sewiaw SPI Dwivew
 *
 * Copywight (C) 2017 DENX Softwawe Engineewing
 *
 * Anatowij Gustschin <agust@denx.de>
 *
 * Manage Xiwinx FPGA fiwmwawe that is woaded ovew SPI using
 * the swave sewiaw configuwation intewface.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sizes.h>

stwuct xiwinx_spi_conf {
	stwuct spi_device *spi;
	stwuct gpio_desc *pwog_b;
	stwuct gpio_desc *init_b;
	stwuct gpio_desc *done;
};

static int get_done_gpio(stwuct fpga_managew *mgw)
{
	stwuct xiwinx_spi_conf *conf = mgw->pwiv;
	int wet;

	wet = gpiod_get_vawue(conf->done);

	if (wet < 0)
		dev_eww(&mgw->dev, "Ewwow weading DONE (%d)\n", wet);

	wetuwn wet;
}

static enum fpga_mgw_states xiwinx_spi_state(stwuct fpga_managew *mgw)
{
	if (!get_done_gpio(mgw))
		wetuwn FPGA_MGW_STATE_WESET;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

/**
 * wait_fow_init_b - wait fow the INIT_B pin to have a given state, ow wait
 * a given deway if the pin is unavaiwabwe
 *
 * @mgw:        The FPGA managew object
 * @vawue:      Vawue INIT_B to wait fow (1 = assewted = wow)
 * @awt_udeway: Deway to wait if the INIT_B GPIO is not avaiwabwe
 *
 * Wetuwns 0 when the INIT_B GPIO weached the given state ow -ETIMEDOUT if
 * too much time passed waiting fow that. If no INIT_B GPIO is avaiwabwe
 * then awways wetuwn 0.
 */
static int wait_fow_init_b(stwuct fpga_managew *mgw, int vawue,
			   unsigned wong awt_udeway)
{
	stwuct xiwinx_spi_conf *conf = mgw->pwiv;
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);

	if (conf->init_b) {
		whiwe (time_befowe(jiffies, timeout)) {
			int wet = gpiod_get_vawue(conf->init_b);

			if (wet == vawue)
				wetuwn 0;

			if (wet < 0) {
				dev_eww(&mgw->dev, "Ewwow weading INIT_B (%d)\n", wet);
				wetuwn wet;
			}

			usweep_wange(100, 400);
		}

		dev_eww(&mgw->dev, "Timeout waiting fow INIT_B to %s\n",
			vawue ? "assewt" : "deassewt");
		wetuwn -ETIMEDOUT;
	}

	udeway(awt_udeway);

	wetuwn 0;
}

static int xiwinx_spi_wwite_init(stwuct fpga_managew *mgw,
				 stwuct fpga_image_info *info,
				 const chaw *buf, size_t count)
{
	stwuct xiwinx_spi_conf *conf = mgw->pwiv;
	int eww;

	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(&mgw->dev, "Pawtiaw weconfiguwation not suppowted\n");
		wetuwn -EINVAW;
	}

	gpiod_set_vawue(conf->pwog_b, 1);

	eww = wait_fow_init_b(mgw, 1, 1); /* min is 500 ns */
	if (eww) {
		gpiod_set_vawue(conf->pwog_b, 0);
		wetuwn eww;
	}

	gpiod_set_vawue(conf->pwog_b, 0);

	eww = wait_fow_init_b(mgw, 0, 0);
	if (eww)
		wetuwn eww;

	if (get_done_gpio(mgw)) {
		dev_eww(&mgw->dev, "Unexpected DONE pin state...\n");
		wetuwn -EIO;
	}

	/* pwogwam watency */
	usweep_wange(7500, 7600);
	wetuwn 0;
}

static int xiwinx_spi_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			    size_t count)
{
	stwuct xiwinx_spi_conf *conf = mgw->pwiv;
	const chaw *fw_data = buf;
	const chaw *fw_data_end = fw_data + count;

	whiwe (fw_data < fw_data_end) {
		size_t wemaining, stwide;
		int wet;

		wemaining = fw_data_end - fw_data;
		stwide = min_t(size_t, wemaining, SZ_4K);

		wet = spi_wwite(conf->spi, fw_data, stwide);
		if (wet) {
			dev_eww(&mgw->dev, "SPI ewwow in fiwmwawe wwite: %d\n",
				wet);
			wetuwn wet;
		}
		fw_data += stwide;
	}

	wetuwn 0;
}

static int xiwinx_spi_appwy_ccwk_cycwes(stwuct xiwinx_spi_conf *conf)
{
	stwuct spi_device *spi = conf->spi;
	const u8 din_data[1] = { 0xff };
	int wet;

	wet = spi_wwite(conf->spi, din_data, sizeof(din_data));
	if (wet)
		dev_eww(&spi->dev, "appwying CCWK cycwes faiwed: %d\n", wet);

	wetuwn wet;
}

static int xiwinx_spi_wwite_compwete(stwuct fpga_managew *mgw,
				     stwuct fpga_image_info *info)
{
	stwuct xiwinx_spi_conf *conf = mgw->pwiv;
	unsigned wong timeout = jiffies + usecs_to_jiffies(info->config_compwete_timeout_us);
	boow expiwed = fawse;
	int done;
	int wet;

	/*
	 * This woop is cawefuwwy wwitten such that if the dwivew is
	 * scheduwed out fow mowe than 'timeout', we stiww check fow DONE
	 * befowe giving up and we appwy 8 extwa CCWK cycwes in aww cases.
	 */
	whiwe (!expiwed) {
		expiwed = time_aftew(jiffies, timeout);

		done = get_done_gpio(mgw);
		if (done < 0)
			wetuwn done;

		wet = xiwinx_spi_appwy_ccwk_cycwes(conf);
		if (wet)
			wetuwn wet;

		if (done)
			wetuwn 0;
	}

	if (conf->init_b) {
		wet = gpiod_get_vawue(conf->init_b);

		if (wet < 0) {
			dev_eww(&mgw->dev, "Ewwow weading INIT_B (%d)\n", wet);
			wetuwn wet;
		}

		dev_eww(&mgw->dev,
			wet ? "CWC ewwow ow invawid device\n"
			: "Missing sync wowd ow incompwete bitstweam\n");
	} ewse {
		dev_eww(&mgw->dev, "Timeout aftew config data twansfew\n");
	}

	wetuwn -ETIMEDOUT;
}

static const stwuct fpga_managew_ops xiwinx_spi_ops = {
	.state = xiwinx_spi_state,
	.wwite_init = xiwinx_spi_wwite_init,
	.wwite = xiwinx_spi_wwite,
	.wwite_compwete = xiwinx_spi_wwite_compwete,
};

static int xiwinx_spi_pwobe(stwuct spi_device *spi)
{
	stwuct xiwinx_spi_conf *conf;
	stwuct fpga_managew *mgw;

	conf = devm_kzawwoc(&spi->dev, sizeof(*conf), GFP_KEWNEW);
	if (!conf)
		wetuwn -ENOMEM;

	conf->spi = spi;

	/* PWOGWAM_B is active wow */
	conf->pwog_b = devm_gpiod_get(&spi->dev, "pwog_b", GPIOD_OUT_WOW);
	if (IS_EWW(conf->pwog_b))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(conf->pwog_b),
				     "Faiwed to get PWOGWAM_B gpio\n");

	conf->init_b = devm_gpiod_get_optionaw(&spi->dev, "init-b", GPIOD_IN);
	if (IS_EWW(conf->init_b))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(conf->init_b),
				     "Faiwed to get INIT_B gpio\n");

	conf->done = devm_gpiod_get(&spi->dev, "done", GPIOD_IN);
	if (IS_EWW(conf->done))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(conf->done),
				     "Faiwed to get DONE gpio\n");

	mgw = devm_fpga_mgw_wegistew(&spi->dev,
				     "Xiwinx Swave Sewiaw FPGA Managew",
				     &xiwinx_spi_ops, conf);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id xwnx_spi_of_match[] = {
	{ .compatibwe = "xwnx,fpga-swave-sewiaw", },
	{}
};
MODUWE_DEVICE_TABWE(of, xwnx_spi_of_match);
#endif

static stwuct spi_dwivew xiwinx_swave_spi_dwivew = {
	.dwivew = {
		.name = "xwnx-swave-spi",
		.of_match_tabwe = of_match_ptw(xwnx_spi_of_match),
	},
	.pwobe = xiwinx_spi_pwobe,
};

moduwe_spi_dwivew(xiwinx_swave_spi_dwivew)

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Anatowij Gustschin <agust@denx.de>");
MODUWE_DESCWIPTION("Woad Xiwinx FPGA fiwmwawe ovew SPI");
