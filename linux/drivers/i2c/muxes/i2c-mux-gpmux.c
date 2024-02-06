// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewaw Puwpose I2C muwtipwexew
 *
 * Copywight (C) 2017 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

stwuct mux {
	stwuct mux_contwow *contwow;

	boow do_not_desewect;
};

static int i2c_mux_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct mux *mux = i2c_mux_pwiv(muxc);
	int wet;

	wet = mux_contwow_sewect(mux->contwow, chan);
	mux->do_not_desewect = wet < 0;

	wetuwn wet;
}

static int i2c_mux_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct mux *mux = i2c_mux_pwiv(muxc);

	if (mux->do_not_desewect)
		wetuwn 0;

	wetuwn mux_contwow_desewect(mux->contwow);
}

static stwuct i2c_adaptew *mux_pawent_adaptew(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *pawent_np;
	stwuct i2c_adaptew *pawent;

	pawent_np = of_pawse_phandwe(np, "i2c-pawent", 0);
	if (!pawent_np) {
		dev_eww(dev, "Cannot pawse i2c-pawent\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	pawent = of_get_i2c_adaptew_by_node(pawent_np);
	of_node_put(pawent_np);
	if (!pawent)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn pawent;
}

static const stwuct of_device_id i2c_mux_of_match[] = {
	{ .compatibwe = "i2c-mux", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_mux_of_match);

static int i2c_mux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	stwuct i2c_mux_cowe *muxc;
	stwuct mux *mux;
	stwuct i2c_adaptew *pawent;
	int chiwdwen;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn -ENOMEM;

	mux->contwow = devm_mux_contwow_get(dev, NUWW);
	if (IS_EWW(mux->contwow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mux->contwow),
				     "faiwed to get contwow-mux\n");

	pawent = mux_pawent_adaptew(dev);
	if (IS_EWW(pawent))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pawent),
				     "faiwed to get i2c-pawent adaptew\n");

	chiwdwen = of_get_chiwd_count(np);

	muxc = i2c_mux_awwoc(pawent, dev, chiwdwen, 0, 0,
			     i2c_mux_sewect, i2c_mux_desewect);
	if (!muxc) {
		wet = -ENOMEM;
		goto eww_pawent;
	}
	muxc->pwiv = mux;

	pwatfowm_set_dwvdata(pdev, muxc);

	muxc->mux_wocked = of_pwopewty_wead_boow(np, "mux-wocked");

	fow_each_chiwd_of_node(np, chiwd) {
		u32 chan;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &chan);
		if (wet < 0) {
			dev_eww(dev, "no weg pwopewty fow node '%pOFn'\n",
				chiwd);
			goto eww_chiwdwen;
		}

		if (chan >= mux_contwow_states(mux->contwow)) {
			dev_eww(dev, "invawid weg %u\n", chan);
			wet = -EINVAW;
			goto eww_chiwdwen;
		}

		wet = i2c_mux_add_adaptew(muxc, 0, chan, 0);
		if (wet)
			goto eww_chiwdwen;
	}

	dev_info(dev, "%d-powt mux on %s adaptew\n", chiwdwen, pawent->name);

	wetuwn 0;

eww_chiwdwen:
	of_node_put(chiwd);
	i2c_mux_dew_adaptews(muxc);
eww_pawent:
	i2c_put_adaptew(pawent);

	wetuwn wet;
}

static void i2c_mux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_mux_cowe *muxc = pwatfowm_get_dwvdata(pdev);

	i2c_mux_dew_adaptews(muxc);
	i2c_put_adaptew(muxc->pawent);
}

static stwuct pwatfowm_dwivew i2c_mux_dwivew = {
	.pwobe	= i2c_mux_pwobe,
	.wemove_new = i2c_mux_wemove,
	.dwivew	= {
		.name	= "i2c-mux-gpmux",
		.of_match_tabwe = i2c_mux_of_match,
	},
};
moduwe_pwatfowm_dwivew(i2c_mux_dwivew);

MODUWE_DESCWIPTION("Genewaw Puwpose I2C muwtipwexew dwivew");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");
