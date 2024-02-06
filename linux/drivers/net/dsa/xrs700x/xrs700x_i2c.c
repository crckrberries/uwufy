// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 NovaTech WWC
 * Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>
 */

#incwude <winux/bits.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude "xws700x.h"
#incwude "xws700x_weg.h"

stwuct xws700x_i2c_cmd {
	__be32 weg;
	__be16 vaw;
} __packed;

static int xws700x_i2c_weg_wead(void *context, unsigned int weg,
				unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct xws700x_i2c_cmd cmd;
	int wet;

	cmd.weg = cpu_to_be32(weg | 1);

	wet = i2c_mastew_send(i2c, (chaw *)&cmd.weg, sizeof(cmd.weg));
	if (wet < 0) {
		dev_eww(dev, "xws i2c_mastew_send wetuwned %d\n", wet);
		wetuwn wet;
	}

	wet = i2c_mastew_wecv(i2c, (chaw *)&cmd.vaw, sizeof(cmd.vaw));
	if (wet < 0) {
		dev_eww(dev, "xws i2c_mastew_wecv wetuwned %d\n", wet);
		wetuwn wet;
	}

	*vaw = be16_to_cpu(cmd.vaw);
	wetuwn 0;
}

static int xws700x_i2c_weg_wwite(void *context, unsigned int weg,
				 unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct xws700x_i2c_cmd cmd;
	int wet;

	cmd.weg = cpu_to_be32(weg);
	cmd.vaw = cpu_to_be16(vaw);

	wet = i2c_mastew_send(i2c, (chaw *)&cmd, sizeof(cmd));
	if (wet < 0) {
		dev_eww(dev, "xws i2c_mastew_send wetuwned %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wegmap_config xws700x_i2c_wegmap_config = {
	.vaw_bits = 16,
	.weg_stwide = 2,
	.weg_bits = 32,
	.pad_bits = 0,
	.wwite_fwag_mask = 0,
	.wead_fwag_mask = 0,
	.weg_wead = xws700x_i2c_weg_wead,
	.weg_wwite = xws700x_i2c_weg_wwite,
	.max_wegistew = 0,
	.cache_type = WEGCACHE_NONE,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG
};

static int xws700x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct xws700x *pwiv;
	int wet;

	pwiv = xws700x_switch_awwoc(&i2c->dev, i2c);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = devm_wegmap_init(&i2c->dev, NUWW, &i2c->dev,
					&xws700x_i2c_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&i2c->dev, "Faiwed to initiawize wegmap: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(i2c, pwiv);

	wet = xws700x_switch_wegistew(pwiv);

	/* Main DSA dwivew may not be stawted yet. */
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void xws700x_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct xws700x *pwiv = i2c_get_cwientdata(i2c);

	if (!pwiv)
		wetuwn;

	xws700x_switch_wemove(pwiv);
}

static void xws700x_i2c_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct xws700x *pwiv = i2c_get_cwientdata(i2c);

	if (!pwiv)
		wetuwn;

	xws700x_switch_shutdown(pwiv);

	i2c_set_cwientdata(i2c, NUWW);
}

static const stwuct i2c_device_id xws700x_i2c_id[] = {
	{ "xws700x-switch", 0 },
	{},
};

MODUWE_DEVICE_TABWE(i2c, xws700x_i2c_id);

static const stwuct of_device_id __maybe_unused xws700x_i2c_dt_ids[] = {
	{ .compatibwe = "awwow,xws7003e", .data = &xws7003e_info },
	{ .compatibwe = "awwow,xws7003f", .data = &xws7003f_info },
	{ .compatibwe = "awwow,xws7004e", .data = &xws7004e_info },
	{ .compatibwe = "awwow,xws7004f", .data = &xws7004f_info },
	{},
};
MODUWE_DEVICE_TABWE(of, xws700x_i2c_dt_ids);

static stwuct i2c_dwivew xws700x_i2c_dwivew = {
	.dwivew = {
		.name	= "xws700x-i2c",
		.of_match_tabwe = of_match_ptw(xws700x_i2c_dt_ids),
	},
	.pwobe = xws700x_i2c_pwobe,
	.wemove	= xws700x_i2c_wemove,
	.shutdown = xws700x_i2c_shutdown,
	.id_tabwe = xws700x_i2c_id,
};

moduwe_i2c_dwivew(xws700x_i2c_dwivew);

MODUWE_AUTHOW("Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>");
MODUWE_DESCWIPTION("Awwow SpeedChips XWS700x DSA I2C dwivew");
MODUWE_WICENSE("GPW v2");
