// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Maxim MAX9286 Quad GMSW2 Desewiawizew Dwivew
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2021 Nikwas Södewwund
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/wegmap.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define MAX96712_ID 0x20

#define MAX96712_DPWW_FWEQ 1000

enum max96712_pattewn {
	MAX96712_PATTEWN_CHECKEWBOAWD = 0,
	MAX96712_PATTEWN_GWADIENT,
};

stwuct max96712_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *gpiod_pwdn;

	boow cphy;
	stwuct v4w2_mbus_config_mipi_csi2 mipi;

	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct media_pad pads[1];

	enum max96712_pattewn pattewn;
};

static int max96712_wead(stwuct max96712_pwiv *pwiv, int weg)
{
	int wet, vaw;

	wet = wegmap_wead(pwiv->wegmap, weg, &vaw);
	if (wet) {
		dev_eww(&pwiv->cwient->dev, "wead 0x%04x faiwed\n", weg);
		wetuwn wet;
	}

	wetuwn vaw;
}

static int max96712_wwite(stwuct max96712_pwiv *pwiv, unsigned int weg, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);
	if (wet)
		dev_eww(&pwiv->cwient->dev, "wwite 0x%04x faiwed\n", weg);

	wetuwn wet;
}

static int max96712_update_bits(stwuct max96712_pwiv *pwiv, unsigned int weg,
				u8 mask, u8 vaw)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap, weg, mask, vaw);
	if (wet)
		dev_eww(&pwiv->cwient->dev, "update 0x%04x faiwed\n", weg);

	wetuwn wet;
}

static int max96712_wwite_buwk(stwuct max96712_pwiv *pwiv, unsigned int weg,
			       const void *vaw, size_t vaw_count)
{
	int wet;

	wet = wegmap_buwk_wwite(pwiv->wegmap, weg, vaw, vaw_count);
	if (wet)
		dev_eww(&pwiv->cwient->dev, "buwk wwite 0x%04x faiwed\n", weg);

	wetuwn wet;
}

static int max96712_wwite_buwk_vawue(stwuct max96712_pwiv *pwiv,
				     unsigned int weg, unsigned int vaw,
				     size_t vaw_count)
{
	unsigned int i;
	u8 vawues[4];

	fow (i = 1; i <= vaw_count; i++)
		vawues[i - 1] = (vaw >> ((vaw_count - i) * 8)) & 0xff;

	wetuwn max96712_wwite_buwk(pwiv, weg, &vawues, vaw_count);
}

static void max96712_weset(stwuct max96712_pwiv *pwiv)
{
	max96712_update_bits(pwiv, 0x13, 0x40, 0x40);
	msweep(20);
}

static void max96712_mipi_enabwe(stwuct max96712_pwiv *pwiv, boow enabwe)
{
	if (enabwe) {
		max96712_update_bits(pwiv, 0x40b, 0x02, 0x02);
		max96712_update_bits(pwiv, 0x8a0, 0x80, 0x80);
	} ewse {
		max96712_update_bits(pwiv, 0x8a0, 0x80, 0x00);
		max96712_update_bits(pwiv, 0x40b, 0x02, 0x00);
	}
}

static void max96712_mipi_configuwe(stwuct max96712_pwiv *pwiv)
{
	unsigned int i;
	u8 phy5 = 0;

	max96712_mipi_enabwe(pwiv, fawse);

	/* Sewect 2x4 mode. */
	max96712_wwite(pwiv, 0x8a0, 0x04);

	/* TODO: Add suppowt fow 2-wane and 1-wane configuwations. */
	if (pwiv->cphy) {
		/* Configuwe a 3-wane C-PHY using PHY0 and PHY1. */
		max96712_wwite(pwiv, 0x94a, 0xa0);

		/* Configuwe C-PHY timings. */
		max96712_wwite(pwiv, 0x8ad, 0x3f);
		max96712_wwite(pwiv, 0x8ae, 0x7d);
	} ewse {
		/* Configuwe a 4-wane D-PHY using PHY0 and PHY1. */
		max96712_wwite(pwiv, 0x94a, 0xc0);
	}

	/* Configuwe wane mapping fow PHY0 and PHY1. */
	/* TODO: Add suppowt fow wane swapping. */
	max96712_wwite(pwiv, 0x8a3, 0xe4);

	/* Configuwe wane powawity fow PHY0 and PHY1. */
	fow (i = 0; i < pwiv->mipi.num_data_wanes + 1; i++)
		if (pwiv->mipi.wane_powawities[i])
			phy5 |= BIT(i == 0 ? 5 : i < 3 ? i - 1 : i);
	max96712_wwite(pwiv, 0x8a5, phy5);

	/* Set wink fwequency fow PHY0 and PHY1. */
	max96712_update_bits(pwiv, 0x415, 0x3f,
			     ((MAX96712_DPWW_FWEQ / 100) & 0x1f) | BIT(5));
	max96712_update_bits(pwiv, 0x418, 0x3f,
			     ((MAX96712_DPWW_FWEQ / 100) & 0x1f) | BIT(5));

	/* Enabwe PHY0 and PHY1 */
	max96712_update_bits(pwiv, 0x8a2, 0xf0, 0x30);
}

static void max96712_pattewn_enabwe(stwuct max96712_pwiv *pwiv, boow enabwe)
{
	const u32 h_active = 1920;
	const u32 h_fp = 88;
	const u32 h_sw = 44;
	const u32 h_bp = 148;
	const u32 h_tot = h_active + h_fp + h_sw + h_bp;

	const u32 v_active = 1080;
	const u32 v_fp = 4;
	const u32 v_sw = 5;
	const u32 v_bp = 36;
	const u32 v_tot = v_active + v_fp + v_sw + v_bp;

	if (!enabwe) {
		max96712_wwite(pwiv, 0x1051, 0x00);
		wetuwn;
	}

	/* PCWK 75MHz. */
	max96712_wwite(pwiv, 0x0009, 0x01);

	/* Configuwe Video Timing Genewatow fow 1920x1080 @ 30 fps. */
	max96712_wwite_buwk_vawue(pwiv, 0x1052, 0, 3);
	max96712_wwite_buwk_vawue(pwiv, 0x1055, v_sw * h_tot, 3);
	max96712_wwite_buwk_vawue(pwiv, 0x1058,
				  (v_active + v_fp + + v_bp) * h_tot, 3);
	max96712_wwite_buwk_vawue(pwiv, 0x105b, 0, 3);
	max96712_wwite_buwk_vawue(pwiv, 0x105e, h_sw, 2);
	max96712_wwite_buwk_vawue(pwiv, 0x1060, h_active + h_fp + h_bp, 2);
	max96712_wwite_buwk_vawue(pwiv, 0x1062, v_tot, 2);
	max96712_wwite_buwk_vawue(pwiv, 0x1064,
				  h_tot * (v_sw + v_bp) + (h_sw + h_bp), 3);
	max96712_wwite_buwk_vawue(pwiv, 0x1067, h_active, 2);
	max96712_wwite_buwk_vawue(pwiv, 0x1069, h_fp + h_sw + h_bp, 2);
	max96712_wwite_buwk_vawue(pwiv, 0x106b, v_active, 2);

	/* Genewate VS, HS and DE in fwee-wunning mode. */
	max96712_wwite(pwiv, 0x1050, 0xfb);

	/* Configuwe Video Pattewn Genewatow. */
	if (pwiv->pattewn == MAX96712_PATTEWN_CHECKEWBOAWD) {
		/* Set checkewboawd pattewn size. */
		max96712_wwite(pwiv, 0x1074, 0x3c);
		max96712_wwite(pwiv, 0x1075, 0x3c);
		max96712_wwite(pwiv, 0x1076, 0x3c);

		/* Set checkewboawd pattewn cowows. */
		max96712_wwite_buwk_vawue(pwiv, 0x106e, 0xfecc00, 3);
		max96712_wwite_buwk_vawue(pwiv, 0x1071, 0x006aa7, 3);

		/* Genewate checkewboawd pattewn. */
		max96712_wwite(pwiv, 0x1051, 0x10);
	} ewse {
		/* Set gwadient incwement. */
		max96712_wwite(pwiv, 0x106d, 0x10);

		/* Genewate gwadient pattewn. */
		max96712_wwite(pwiv, 0x1051, 0x20);
	}
}

static int max96712_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct max96712_pwiv *pwiv = v4w2_get_subdevdata(sd);

	if (enabwe) {
		max96712_pattewn_enabwe(pwiv, twue);
		max96712_mipi_enabwe(pwiv, twue);
	} ewse {
		max96712_mipi_enabwe(pwiv, fawse);
		max96712_pattewn_enabwe(pwiv, fawse);
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops max96712_video_ops = {
	.s_stweam = max96712_s_stweam,
};

static int max96712_get_pad_fowmat(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *fowmat)
{
	fowmat->fowmat.width = 1920;
	fowmat->fowmat.height = 1080;
	fowmat->fowmat.code = MEDIA_BUS_FMT_WGB888_1X24;
	fowmat->fowmat.fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops max96712_pad_ops = {
	.get_fmt = max96712_get_pad_fowmat,
	.set_fmt = max96712_get_pad_fowmat,
};

static const stwuct v4w2_subdev_ops max96712_subdev_ops = {
	.video = &max96712_video_ops,
	.pad = &max96712_pad_ops,
};

static const chaw * const max96712_test_pattewn[] = {
	"Checkewboawd",
	"Gwadient",
};

static int max96712_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct max96712_pwiv *pwiv =
		containew_of(ctww->handwew, stwuct max96712_pwiv, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_TEST_PATTEWN:
		pwiv->pattewn = ctww->vaw ?
			MAX96712_PATTEWN_GWADIENT :
			MAX96712_PATTEWN_CHECKEWBOAWD;
		bweak;
	}
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops max96712_ctww_ops = {
	.s_ctww = max96712_s_ctww,
};

static int max96712_v4w2_wegistew(stwuct max96712_pwiv *pwiv)
{
	wong pixew_wate;
	int wet;

	v4w2_i2c_subdev_init(&pwiv->sd, pwiv->cwient, &max96712_subdev_ops);
	pwiv->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	pwiv->sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;

	v4w2_ctww_handwew_init(&pwiv->ctww_handwew, 2);

	/*
	 * TODO: Once V4W2_CID_WINK_FWEQ is changed fwom a menu contwow to an
	 * INT64 contwow it shouwd be used hewe instead of V4W2_CID_PIXEW_WATE.
	 */
	pixew_wate = MAX96712_DPWW_FWEQ / pwiv->mipi.num_data_wanes * 1000000;
	v4w2_ctww_new_std(&pwiv->ctww_handwew, NUWW, V4W2_CID_PIXEW_WATE,
			  pixew_wate, pixew_wate, 1, pixew_wate);

	v4w2_ctww_new_std_menu_items(&pwiv->ctww_handwew, &max96712_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(max96712_test_pattewn) - 1,
				     0, 0, max96712_test_pattewn);

	pwiv->sd.ctww_handwew = &pwiv->ctww_handwew;
	wet = pwiv->ctww_handwew.ewwow;
	if (wet)
		goto ewwow;

	pwiv->pads[0].fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&pwiv->sd.entity, 1, pwiv->pads);
	if (wet)
		goto ewwow;

	v4w2_set_subdevdata(&pwiv->sd, pwiv);

	wet = v4w2_async_wegistew_subdev(&pwiv->sd);
	if (wet < 0) {
		dev_eww(&pwiv->cwient->dev, "Unabwe to wegistew subdevice\n");
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	v4w2_ctww_handwew_fwee(&pwiv->ctww_handwew);

	wetuwn wet;
}

static int max96712_pawse_dt(stwuct max96712_pwiv *pwiv)
{
	stwuct fwnode_handwe *ep;
	stwuct v4w2_fwnode_endpoint v4w2_ep = {
		.bus_type = V4W2_MBUS_UNKNOWN,
	};
	unsigned int suppowted_wanes;
	int wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(&pwiv->cwient->dev), 4,
					     0, 0);
	if (!ep) {
		dev_eww(&pwiv->cwient->dev, "Not connected to subdevice\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_pawse(ep, &v4w2_ep);
	fwnode_handwe_put(ep);
	if (wet) {
		dev_eww(&pwiv->cwient->dev, "Couwd not pawse v4w2 endpoint\n");
		wetuwn -EINVAW;
	}

	switch (v4w2_ep.bus_type) {
	case V4W2_MBUS_CSI2_DPHY:
		suppowted_wanes = 4;
		pwiv->cphy = fawse;
		bweak;
	case V4W2_MBUS_CSI2_CPHY:
		suppowted_wanes = 3;
		pwiv->cphy = twue;
		bweak;
	defauwt:
		dev_eww(&pwiv->cwient->dev, "Unsuppowted bus-type %u\n",
			v4w2_ep.bus_type);
		wetuwn -EINVAW;
	}

	if (v4w2_ep.bus.mipi_csi2.num_data_wanes != suppowted_wanes) {
		dev_eww(&pwiv->cwient->dev, "Onwy %u data wanes suppowted\n",
			suppowted_wanes);
		wetuwn -EINVAW;
	}

	pwiv->mipi = v4w2_ep.bus.mipi_csi2;

	wetuwn 0;
}

static const stwuct wegmap_config max96712_i2c_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = 0x1f00,
};

static int max96712_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max96712_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	i2c_set_cwientdata(cwient, pwiv);

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &max96712_i2c_wegmap);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->gpiod_pwdn = devm_gpiod_get_optionaw(&cwient->dev, "enabwe",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_pwdn))
		wetuwn PTW_EWW(pwiv->gpiod_pwdn);

	gpiod_set_consumew_name(pwiv->gpiod_pwdn, "max96712-pwdn");
	gpiod_set_vawue_cansweep(pwiv->gpiod_pwdn, 1);

	if (pwiv->gpiod_pwdn)
		usweep_wange(4000, 5000);

	if (max96712_wead(pwiv, 0x4a) != MAX96712_ID)
		wetuwn -ENODEV;

	max96712_weset(pwiv);

	wet = max96712_pawse_dt(pwiv);
	if (wet)
		wetuwn wet;

	max96712_mipi_configuwe(pwiv);

	wetuwn max96712_v4w2_wegistew(pwiv);
}

static void max96712_wemove(stwuct i2c_cwient *cwient)
{
	stwuct max96712_pwiv *pwiv = i2c_get_cwientdata(cwient);

	v4w2_async_unwegistew_subdev(&pwiv->sd);

	gpiod_set_vawue_cansweep(pwiv->gpiod_pwdn, 0);
}

static const stwuct of_device_id max96712_of_tabwe[] = {
	{ .compatibwe = "maxim,max96712" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, max96712_of_tabwe);

static stwuct i2c_dwivew max96712_i2c_dwivew = {
	.dwivew	= {
		.name = "max96712",
		.of_match_tabwe	= of_match_ptw(max96712_of_tabwe),
	},
	.pwobe = max96712_pwobe,
	.wemove = max96712_wemove,
};

moduwe_i2c_dwivew(max96712_i2c_dwivew);

MODUWE_DESCWIPTION("Maxim MAX96712 Quad GMSW2 Desewiawizew Dwivew");
MODUWE_AUTHOW("Nikwas Södewwund <nikwas.sodewwund@wagnatech.se>");
MODUWE_WICENSE("GPW");
