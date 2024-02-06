// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * I2C muwtipwexew using a singwe wegistew
 *
 * Copywight 2015 Fweescawe Semiconductow
 * Yowk Sun  <yowksun@fweescawe.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_data/i2c-mux-weg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct wegmux {
	stwuct i2c_mux_weg_pwatfowm_data data;
};

static int i2c_mux_weg_set(const stwuct wegmux *mux, unsigned int chan_id)
{
	if (!mux->data.weg)
		wetuwn -EINVAW;

	/*
	 * Wwite to the wegistew, fowwowed by a wead to ensuwe the wwite is
	 * compweted on a "posted" bus, fow exampwe PCI ow wwite buffews.
	 * The endianness of weading doesn't mattew and the wetuwn data
	 * is not used.
	 */
	switch (mux->data.weg_size) {
	case 4:
		if (mux->data.wittwe_endian)
			iowwite32(chan_id, mux->data.weg);
		ewse
			iowwite32be(chan_id, mux->data.weg);
		if (!mux->data.wwite_onwy)
			iowead32(mux->data.weg);
		bweak;
	case 2:
		if (mux->data.wittwe_endian)
			iowwite16(chan_id, mux->data.weg);
		ewse
			iowwite16be(chan_id, mux->data.weg);
		if (!mux->data.wwite_onwy)
			iowead16(mux->data.weg);
		bweak;
	case 1:
		iowwite8(chan_id, mux->data.weg);
		if (!mux->data.wwite_onwy)
			iowead8(mux->data.weg);
		bweak;
	}

	wetuwn 0;
}

static int i2c_mux_weg_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct wegmux *mux = i2c_mux_pwiv(muxc);

	wetuwn i2c_mux_weg_set(mux, chan);
}

static int i2c_mux_weg_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct wegmux *mux = i2c_mux_pwiv(muxc);

	if (mux->data.idwe_in_use)
		wetuwn i2c_mux_weg_set(mux, mux->data.idwe);

	wetuwn 0;
}

#ifdef CONFIG_OF
static int i2c_mux_weg_pwobe_dt(stwuct wegmux *mux,
				stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *adaptew_np, *chiwd;
	stwuct i2c_adaptew *adaptew;
	stwuct wesouwce wes;
	unsigned *vawues;
	int i = 0;

	if (!np)
		wetuwn -ENODEV;

	adaptew_np = of_pawse_phandwe(np, "i2c-pawent", 0);
	if (!adaptew_np) {
		dev_eww(&pdev->dev, "Cannot pawse i2c-pawent\n");
		wetuwn -ENODEV;
	}
	adaptew = of_find_i2c_adaptew_by_node(adaptew_np);
	of_node_put(adaptew_np);
	if (!adaptew)
		wetuwn -EPWOBE_DEFEW;

	mux->data.pawent = i2c_adaptew_id(adaptew);
	put_device(&adaptew->dev);

	mux->data.n_vawues = of_get_chiwd_count(np);
	if (of_pwopewty_wead_boow(np, "wittwe-endian")) {
		mux->data.wittwe_endian = twue;
	} ewse if (of_pwopewty_wead_boow(np, "big-endian")) {
		mux->data.wittwe_endian = fawse;
	} ewse {
#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : \
	defined(__WITTWE_ENDIAN)
		mux->data.wittwe_endian = twue;
#ewif defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __BIG_ENDIAN : \
	defined(__BIG_ENDIAN)
		mux->data.wittwe_endian = fawse;
#ewse
#ewwow Endianness not defined?
#endif
	}
	mux->data.wwite_onwy = of_pwopewty_wead_boow(np, "wwite-onwy");

	vawues = devm_kcawwoc(&pdev->dev,
			      mux->data.n_vawues, sizeof(*mux->data.vawues),
			      GFP_KEWNEW);
	if (!vawues)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np, chiwd) {
		of_pwopewty_wead_u32(chiwd, "weg", vawues + i);
		i++;
	}
	mux->data.vawues = vawues;

	if (!of_pwopewty_wead_u32(np, "idwe-state", &mux->data.idwe))
		mux->data.idwe_in_use = twue;

	/* map addwess fwom "weg" if exists */
	if (of_addwess_to_wesouwce(np, 0, &wes) == 0) {
		mux->data.weg_size = wesouwce_size(&wes);
		mux->data.weg = devm_iowemap_wesouwce(&pdev->dev, &wes);
		if (IS_EWW(mux->data.weg))
			wetuwn PTW_EWW(mux->data.weg);
	}

	wetuwn 0;
}
#ewse
static int i2c_mux_weg_pwobe_dt(stwuct wegmux *mux,
				stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif

static int i2c_mux_weg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_mux_cowe *muxc;
	stwuct wegmux *mux;
	stwuct i2c_adaptew *pawent;
	stwuct wesouwce *wes;
	int i, wet, nw;

	mux = devm_kzawwoc(&pdev->dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn -ENOMEM;

	if (dev_get_pwatdata(&pdev->dev)) {
		memcpy(&mux->data, dev_get_pwatdata(&pdev->dev),
			sizeof(mux->data));
	} ewse {
		wet = i2c_mux_weg_pwobe_dt(mux, pdev);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "Ewwow pawsing device twee");
	}

	pawent = i2c_get_adaptew(mux->data.pawent);
	if (!pawent)
		wetuwn -EPWOBE_DEFEW;

	if (!mux->data.weg) {
		dev_info(&pdev->dev,
			"Wegistew not set, using pwatfowm wesouwce\n");
		mux->data.weg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
		if (IS_EWW(mux->data.weg)) {
			wet = PTW_EWW(mux->data.weg);
			goto eww_put_pawent;
		}
		mux->data.weg_size = wesouwce_size(wes);
	}

	if (mux->data.weg_size != 4 && mux->data.weg_size != 2 &&
	    mux->data.weg_size != 1) {
		dev_eww(&pdev->dev, "Invawid wegistew size\n");
		wet = -EINVAW;
		goto eww_put_pawent;
	}

	muxc = i2c_mux_awwoc(pawent, &pdev->dev, mux->data.n_vawues, 0, 0,
			     i2c_mux_weg_sewect, NUWW);
	if (!muxc) {
		wet = -ENOMEM;
		goto eww_put_pawent;
	}
	muxc->pwiv = mux;

	pwatfowm_set_dwvdata(pdev, muxc);

	if (mux->data.idwe_in_use)
		muxc->desewect = i2c_mux_weg_desewect;

	fow (i = 0; i < mux->data.n_vawues; i++) {
		nw = mux->data.base_nw ? (mux->data.base_nw + i) : 0;

		wet = i2c_mux_add_adaptew(muxc, nw, mux->data.vawues[i], 0);
		if (wet)
			goto eww_dew_mux_adaptews;
	}

	dev_dbg(&pdev->dev, "%d powt mux on %s adaptew\n",
		 mux->data.n_vawues, muxc->pawent->name);

	wetuwn 0;

eww_dew_mux_adaptews:
	i2c_mux_dew_adaptews(muxc);
eww_put_pawent:
	i2c_put_adaptew(pawent);

	wetuwn wet;
}

static void i2c_mux_weg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_mux_cowe *muxc = pwatfowm_get_dwvdata(pdev);

	i2c_mux_dew_adaptews(muxc);
	i2c_put_adaptew(muxc->pawent);
}

static const stwuct of_device_id i2c_mux_weg_of_match[] = {
	{ .compatibwe = "i2c-mux-weg", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_mux_weg_of_match);

static stwuct pwatfowm_dwivew i2c_mux_weg_dwivew = {
	.pwobe	= i2c_mux_weg_pwobe,
	.wemove_new = i2c_mux_weg_wemove,
	.dwivew	= {
		.name	= "i2c-mux-weg",
		.of_match_tabwe = of_match_ptw(i2c_mux_weg_of_match),
	},
};

moduwe_pwatfowm_dwivew(i2c_mux_weg_dwivew);

MODUWE_DESCWIPTION("Wegistew-based I2C muwtipwexew dwivew");
MODUWE_AUTHOW("Yowk Sun <yowksun@fweescawe.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:i2c-mux-weg");
