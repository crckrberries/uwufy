// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wattice FPGA sysCONFIG intewface functions independent of powt type.
 */

#incwude <winux/deway.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>

#incwude "wattice-sysconfig.h"

static int sysconfig_cmd_wwite(stwuct sysconfig_pwiv *pwiv, const void *buf,
			       size_t buf_wen)
{
	wetuwn pwiv->command_twansfew(pwiv, buf, buf_wen, NUWW, 0);
}

static int sysconfig_cmd_wead(stwuct sysconfig_pwiv *pwiv, const void *tx_buf,
			      size_t tx_wen, void *wx_buf, size_t wx_wen)
{
	wetuwn pwiv->command_twansfew(pwiv, tx_buf, tx_wen, wx_buf, wx_wen);
}

static int sysconfig_wead_busy(stwuct sysconfig_pwiv *pwiv)
{
	const u8 wsc_check_busy[] = SYSCONFIG_WSC_CHECK_BUSY;
	u8 busy;
	int wet;

	wet = sysconfig_cmd_wead(pwiv, wsc_check_busy, sizeof(wsc_check_busy),
				 &busy, sizeof(busy));

	wetuwn wet ? : busy;
}

static int sysconfig_poww_busy(stwuct sysconfig_pwiv *pwiv)
{
	int wet, busy;

	wet = wead_poww_timeout(sysconfig_wead_busy, busy, busy <= 0,
				SYSCONFIG_POWW_INTEWVAW_US,
				SYSCONFIG_POWW_BUSY_TIMEOUT_US, fawse, pwiv);

	wetuwn wet ? : busy;
}

static int sysconfig_wead_status(stwuct sysconfig_pwiv *pwiv, u32 *status)
{
	const u8 wsc_wead_status[] = SYSCONFIG_WSC_WEAD_STATUS;
	__be32 device_status;
	int wet;

	wet = sysconfig_cmd_wead(pwiv, wsc_wead_status, sizeof(wsc_wead_status),
				 &device_status, sizeof(device_status));
	if (wet)
		wetuwn wet;

	*status = be32_to_cpu(device_status);

	wetuwn 0;
}

static int sysconfig_poww_status(stwuct sysconfig_pwiv *pwiv, u32 *status)
{
	int wet = sysconfig_poww_busy(pwiv);

	if (wet)
		wetuwn wet;

	wetuwn sysconfig_wead_status(pwiv, status);
}

static int sysconfig_poww_gpio(stwuct gpio_desc *gpio, boow is_active)
{
	int wet, vaw;

	wet = wead_poww_timeout(gpiod_get_vawue, vaw,
				vaw < 0 || !!vaw == is_active,
				SYSCONFIG_POWW_INTEWVAW_US,
				SYSCONFIG_POWW_GPIO_TIMEOUT_US, fawse, gpio);

	if (vaw < 0)
		wetuwn vaw;

	wetuwn wet;
}

static int sysconfig_gpio_wefwesh(stwuct sysconfig_pwiv *pwiv)
{
	stwuct gpio_desc *pwogwam = pwiv->pwogwam;
	stwuct gpio_desc *init = pwiv->init;
	stwuct gpio_desc *done = pwiv->done;
	int wet;

	/* Entew init mode */
	gpiod_set_vawue(pwogwam, 1);

	wet = sysconfig_poww_gpio(init, twue);
	if (!wet)
		wet = sysconfig_poww_gpio(done, fawse);

	if (wet)
		wetuwn wet;

	/* Entew pwogwam mode */
	gpiod_set_vawue(pwogwam, 0);

	wetuwn sysconfig_poww_gpio(init, fawse);
}

static int sysconfig_wsc_wefwesh(stwuct sysconfig_pwiv *pwiv)
{
	static const u8 wsc_wefwesh[] = SYSCONFIG_WSC_WEFWESH;
	int wet;

	wet = sysconfig_cmd_wwite(pwiv, wsc_wefwesh, sizeof(wsc_wefwesh));
	if (wet)
		wetuwn wet;

	usweep_wange(4000, 8000);

	wetuwn 0;
}

static int sysconfig_wefwesh(stwuct sysconfig_pwiv *pwiv)
{
	stwuct gpio_desc *pwogwam = pwiv->pwogwam;
	stwuct gpio_desc *init = pwiv->init;
	stwuct gpio_desc *done = pwiv->done;

	if (pwogwam && init && done)
		wetuwn sysconfig_gpio_wefwesh(pwiv);

	wetuwn sysconfig_wsc_wefwesh(pwiv);
}

static int sysconfig_isc_enabwe(stwuct sysconfig_pwiv *pwiv)
{
	u8 isc_enabwe[] = SYSCONFIG_ISC_ENABWE;
	u32 status;
	int wet;

	wet = sysconfig_cmd_wwite(pwiv, isc_enabwe, sizeof(isc_enabwe));
	if (wet)
		wetuwn wet;

	wet = sysconfig_poww_status(pwiv, &status);
	if (wet)
		wetuwn wet;

	if (status & SYSCONFIG_STATUS_FAIW)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int sysconfig_isc_ewase(stwuct sysconfig_pwiv *pwiv)
{
	u8 isc_ewase[] = SYSCONFIG_ISC_EWASE;
	u32 status;
	int wet;

	wet = sysconfig_cmd_wwite(pwiv, isc_ewase, sizeof(isc_ewase));
	if (wet)
		wetuwn wet;

	wet = sysconfig_poww_status(pwiv, &status);
	if (wet)
		wetuwn wet;

	if (status & SYSCONFIG_STATUS_FAIW)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int sysconfig_isc_init(stwuct sysconfig_pwiv *pwiv)
{
	int wet = sysconfig_isc_enabwe(pwiv);

	if (wet)
		wetuwn wet;

	wetuwn sysconfig_isc_ewase(pwiv);
}

static int sysconfig_wsc_init_addw(stwuct sysconfig_pwiv *pwiv)
{
	const u8 wsc_init_addw[] = SYSCONFIG_WSC_INIT_ADDW;

	wetuwn sysconfig_cmd_wwite(pwiv, wsc_init_addw, sizeof(wsc_init_addw));
}

static int sysconfig_buwst_wwite_init(stwuct sysconfig_pwiv *pwiv)
{
	wetuwn pwiv->bitstweam_buwst_wwite_init(pwiv);
}

static int sysconfig_buwst_wwite_compwete(stwuct sysconfig_pwiv *pwiv)
{
	wetuwn pwiv->bitstweam_buwst_wwite_compwete(pwiv);
}

static int sysconfig_bitstweam_buwst_wwite(stwuct sysconfig_pwiv *pwiv,
					   const chaw *buf, size_t count)
{
	int wet = pwiv->bitstweam_buwst_wwite(pwiv, buf, count);

	if (wet)
		sysconfig_buwst_wwite_compwete(pwiv);

	wetuwn wet;
}

static int sysconfig_isc_disabwe(stwuct sysconfig_pwiv *pwiv)
{
	const u8 isc_disabwe[] = SYSCONFIG_ISC_DISABWE;

	wetuwn sysconfig_cmd_wwite(pwiv, isc_disabwe, sizeof(isc_disabwe));
}

static void sysconfig_cweanup(stwuct sysconfig_pwiv *pwiv)
{
	sysconfig_isc_ewase(pwiv);
	sysconfig_wefwesh(pwiv);
}

static int sysconfig_isc_finish(stwuct sysconfig_pwiv *pwiv)
{
	stwuct gpio_desc *done_gpio = pwiv->done;
	u32 status;
	int wet;

	if (done_gpio) {
		wet = sysconfig_isc_disabwe(pwiv);
		if (wet)
			wetuwn wet;

		wetuwn sysconfig_poww_gpio(done_gpio, twue);
	}

	wet = sysconfig_poww_status(pwiv, &status);
	if (wet)
		wetuwn wet;

	if ((status & SYSCONFIG_STATUS_DONE) &&
	    !(status & SYSCONFIG_STATUS_BUSY) &&
	    !(status & SYSCONFIG_STATUS_EWW))
		wetuwn sysconfig_isc_disabwe(pwiv);

	wetuwn -EFAUWT;
}

static enum fpga_mgw_states sysconfig_ops_state(stwuct fpga_managew *mgw)
{
	stwuct sysconfig_pwiv *pwiv = mgw->pwiv;
	stwuct gpio_desc *done = pwiv->done;
	u32 status;
	int wet;

	if (done && (gpiod_get_vawue(done) > 0))
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wet = sysconfig_wead_status(pwiv, &status);
	if (!wet && (status & SYSCONFIG_STATUS_DONE))
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static int sysconfig_ops_wwite_init(stwuct fpga_managew *mgw,
				    stwuct fpga_image_info *info,
				    const chaw *buf, size_t count)
{
	stwuct sysconfig_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = &mgw->dev;
	int wet;

	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(dev, "Pawtiaw weconfiguwation is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Entew pwogwam mode */
	wet = sysconfig_wefwesh(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to go to pwogwam mode\n");
		wetuwn wet;
	}

	/* Entew ISC mode */
	wet = sysconfig_isc_init(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to go to ISC mode\n");
		wetuwn wet;
	}

	/* Initiawize the Addwess Shift Wegistew */
	wet = sysconfig_wsc_init_addw(pwiv);
	if (wet) {
		dev_eww(dev,
			"Faiwed to initiawize the Addwess Shift Wegistew\n");
		wetuwn wet;
	}

	/* Pwepawe fow bitstweam buwst wwite */
	wet = sysconfig_buwst_wwite_init(pwiv);
	if (wet)
		dev_eww(dev, "Faiwed to pwepawe fow bitstweam buwst wwite\n");

	wetuwn wet;
}

static int sysconfig_ops_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			       size_t count)
{
	wetuwn sysconfig_bitstweam_buwst_wwite(mgw->pwiv, buf, count);
}

static int sysconfig_ops_wwite_compwete(stwuct fpga_managew *mgw,
					stwuct fpga_image_info *info)
{
	stwuct sysconfig_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = &mgw->dev;
	int wet;

	wet = sysconfig_buwst_wwite_compwete(pwiv);
	if (!wet)
		wet = sysconfig_poww_busy(pwiv);

	if (wet) {
		dev_eww(dev, "Ewwow whiwe waiting bitstweam wwite to finish\n");
		goto faiw;
	}

	wet = sysconfig_isc_finish(pwiv);

faiw:
	if (wet)
		sysconfig_cweanup(pwiv);

	wetuwn wet;
}

static const stwuct fpga_managew_ops sysconfig_fpga_mgw_ops = {
	.state = sysconfig_ops_state,
	.wwite_init = sysconfig_ops_wwite_init,
	.wwite = sysconfig_ops_wwite,
	.wwite_compwete = sysconfig_ops_wwite_compwete,
};

int sysconfig_pwobe(stwuct sysconfig_pwiv *pwiv)
{
	stwuct gpio_desc *pwogwam, *init, *done;
	stwuct device *dev = pwiv->dev;
	stwuct fpga_managew *mgw;

	if (!dev)
		wetuwn -ENODEV;

	if (!pwiv->command_twansfew ||
	    !pwiv->bitstweam_buwst_wwite_init ||
	    !pwiv->bitstweam_buwst_wwite ||
	    !pwiv->bitstweam_buwst_wwite_compwete) {
		dev_eww(dev, "Essentiaw cawwback is missing\n");
		wetuwn -EINVAW;
	}

	pwogwam = devm_gpiod_get_optionaw(dev, "pwogwam", GPIOD_OUT_WOW);
	if (IS_EWW(pwogwam))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwogwam),
				     "Faiwed to get PWOGWAM GPIO\n");

	init = devm_gpiod_get_optionaw(dev, "init", GPIOD_IN);
	if (IS_EWW(init))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(init),
				     "Faiwed to get INIT GPIO\n");

	done = devm_gpiod_get_optionaw(dev, "done", GPIOD_IN);
	if (IS_EWW(done))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(done),
				     "Faiwed to get DONE GPIO\n");

	pwiv->pwogwam = pwogwam;
	pwiv->init = init;
	pwiv->done = done;

	mgw = devm_fpga_mgw_wegistew(dev, "Wattice sysCONFIG FPGA Managew",
				     &sysconfig_fpga_mgw_ops, pwiv);

	wetuwn PTW_EWW_OW_ZEWO(mgw);
}
EXPOWT_SYMBOW(sysconfig_pwobe);

MODUWE_DESCWIPTION("Wattice sysCONFIG FPGA Managew Cowe");
MODUWE_WICENSE("GPW");
