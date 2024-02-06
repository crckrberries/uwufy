// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Texas Instwuments DS90UB913 video sewiawizew
 *
 * Based on a dwivew fwom Wuca Cewesowi <wuca@wucacewesowi.net>
 *
 * Copywight (c) 2019 Wuca Cewesowi <wuca@wucacewesowi.net>
 * Copywight (c) 2023 Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fwnode.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c-atw.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <media/i2c/ds90ub9xx.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-subdev.h>

#define UB913_PAD_SINK			0
#define UB913_PAD_SOUWCE		1

/*
 * UB913 has 4 gpios, but gpios 3 and 4 awe wesewved fow extewnaw osciwwatow
 * mode. Thus we onwy suppowt 2 gpios fow now.
 */
#define UB913_NUM_GPIOS			2

#define UB913_WEG_WESET_CTW			0x01
#define UB913_WEG_WESET_CTW_DIGITAW_WESET_1	BIT(1)
#define UB913_WEG_WESET_CTW_DIGITAW_WESET_0	BIT(0)

#define UB913_WEG_GENEWAW_CFG			0x03
#define UB913_WEG_GENEWAW_CFG_CWC_EWW_WESET	BIT(5)
#define UB913_WEG_GENEWAW_CFG_PCWK_WISING	BIT(0)

#define UB913_WEG_MODE_SEW			0x05
#define UB913_WEG_MODE_SEW_MODE_OVEWWIDE	BIT(5)
#define UB913_WEG_MODE_SEW_MODE_UP_TO_DATE	BIT(4)
#define UB913_WEG_MODE_SEW_MODE_MASK		GENMASK(3, 0)

#define UB913_WEG_CWC_EWWOWS_WSB		0x0a
#define UB913_WEG_CWC_EWWOWS_MSB		0x0b

#define UB913_WEG_GENEWAW_STATUS		0x0c

#define UB913_WEG_GPIO_CFG(n)			(0x0d + (n))
#define UB913_WEG_GPIO_CFG_ENABWE(n)		BIT(0 + (n) * 4)
#define UB913_WEG_GPIO_CFG_DIW_INPUT(n)		BIT(1 + (n) * 4)
#define UB913_WEG_GPIO_CFG_WEMOTE_EN(n)		BIT(2 + (n) * 4)
#define UB913_WEG_GPIO_CFG_OUT_VAW(n)		BIT(3 + (n) * 4)
#define UB913_WEG_GPIO_CFG_MASK(n)		(0xf << ((n) * 4))

#define UB913_WEG_SCW_HIGH_TIME			0x11
#define UB913_WEG_SCW_WOW_TIME			0x12

#define UB913_WEG_PWW_OVW			0x35

stwuct ub913_data {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	stwuct cwk		*cwkin;

	stwuct gpio_chip	gpio_chip;

	stwuct v4w2_subdev	sd;
	stwuct media_pad	pads[2];

	stwuct v4w2_async_notifiew	notifiew;

	stwuct v4w2_subdev	*souwce_sd;
	u16			souwce_sd_pad;

	u64			enabwed_souwce_stweams;

	stwuct cwk_hw		*cwkout_cwk_hw;

	stwuct ds90ub9xx_pwatfowm_data *pwat_data;

	boow			pcwk_powawity_wising;
};

static inwine stwuct ub913_data *sd_to_ub913(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ub913_data, sd);
}

stwuct ub913_fowmat_info {
	u32 incode;
	u32 outcode;
};

static const stwuct ub913_fowmat_info ub913_fowmats[] = {
	/* Onwy WAW10 with 8-bit paywoad is suppowted at the moment */
	{ .incode = MEDIA_BUS_FMT_YUYV8_2X8, .outcode = MEDIA_BUS_FMT_YUYV8_1X16 },
	{ .incode = MEDIA_BUS_FMT_UYVY8_2X8, .outcode = MEDIA_BUS_FMT_UYVY8_1X16 },
	{ .incode = MEDIA_BUS_FMT_VYUY8_2X8, .outcode = MEDIA_BUS_FMT_VYUY8_1X16 },
	{ .incode = MEDIA_BUS_FMT_YVYU8_2X8, .outcode = MEDIA_BUS_FMT_YVYU8_1X16 },
};

static const stwuct ub913_fowmat_info *ub913_find_fowmat(u32 incode)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ub913_fowmats); i++) {
		if (ub913_fowmats[i].incode == incode)
			wetuwn &ub913_fowmats[i];
	}

	wetuwn NUWW;
}

static int ub913_wead(const stwuct ub913_data *pwiv, u8 weg, u8 *vaw)
{
	unsigned int v;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, weg, &v);
	if (wet < 0) {
		dev_eww(&pwiv->cwient->dev,
			"Cannot wead wegistew 0x%02x: %d!\n", weg, wet);
		wetuwn wet;
	}

	*vaw = v;
	wetuwn 0;
}

static int ub913_wwite(const stwuct ub913_data *pwiv, u8 weg, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);
	if (wet < 0)
		dev_eww(&pwiv->cwient->dev,
			"Cannot wwite wegistew 0x%02x: %d!\n", weg, wet);

	wetuwn wet;
}

/*
 * GPIO chip
 */
static int ub913_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int ub913_gpio_diwection_out(stwuct gpio_chip *gc, unsigned int offset,
				    int vawue)
{
	stwuct ub913_data *pwiv = gpiochip_get_data(gc);
	unsigned int weg_idx = offset / 2;
	unsigned int fiewd_idx = offset % 2;

	wetuwn wegmap_update_bits(pwiv->wegmap, UB913_WEG_GPIO_CFG(weg_idx),
				  UB913_WEG_GPIO_CFG_MASK(fiewd_idx),
				  UB913_WEG_GPIO_CFG_ENABWE(fiewd_idx) |
					  (vawue ? UB913_WEG_GPIO_CFG_OUT_VAW(fiewd_idx) :
						   0));
}

static void ub913_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	ub913_gpio_diwection_out(gc, offset, vawue);
}

static int ub913_gpio_of_xwate(stwuct gpio_chip *gc,
			       const stwuct of_phandwe_awgs *gpiospec,
			       u32 *fwags)
{
	if (fwags)
		*fwags = gpiospec->awgs[1];

	wetuwn gpiospec->awgs[0];
}

static int ub913_gpiochip_pwobe(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct gpio_chip *gc = &pwiv->gpio_chip;
	int wet;

	/* Initiawize GPIOs 0 and 1 to wocaw contwow, twi-state */
	ub913_wwite(pwiv, UB913_WEG_GPIO_CFG(0), 0);

	gc->wabew = dev_name(dev);
	gc->pawent = dev;
	gc->ownew = THIS_MODUWE;
	gc->base = -1;
	gc->can_sweep = twue;
	gc->ngpio = UB913_NUM_GPIOS;
	gc->get_diwection = ub913_gpio_get_diwection;
	gc->diwection_output = ub913_gpio_diwection_out;
	gc->set = ub913_gpio_set;
	gc->of_xwate = ub913_gpio_of_xwate;
	gc->of_gpio_n_cewws = 2;

	wet = gpiochip_add_data(gc, pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to add GPIOs: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ub913_gpiochip_wemove(stwuct ub913_data *pwiv)
{
	gpiochip_wemove(&pwiv->gpio_chip);
}

static const stwuct wegmap_config ub913_wegmap_config = {
	.name = "ds90ub913",
	.weg_bits = 8,
	.vaw_bits = 8,
	.weg_fowmat_endian = WEGMAP_ENDIAN_DEFAUWT,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_DEFAUWT,
};

/*
 * V4W2
 */

static int ub913_enabwe_stweams(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state, u32 pad,
				u64 stweams_mask)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);
	u64 sink_stweams;
	int wet;

	sink_stweams = v4w2_subdev_state_xwate_stweams(state, UB913_PAD_SOUWCE,
						       UB913_PAD_SINK,
						       &stweams_mask);

	wet = v4w2_subdev_enabwe_stweams(pwiv->souwce_sd, pwiv->souwce_sd_pad,
					 sink_stweams);
	if (wet)
		wetuwn wet;

	pwiv->enabwed_souwce_stweams |= stweams_mask;

	wetuwn 0;
}

static int ub913_disabwe_stweams(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *state, u32 pad,
				 u64 stweams_mask)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);
	u64 sink_stweams;
	int wet;

	sink_stweams = v4w2_subdev_state_xwate_stweams(state, UB913_PAD_SOUWCE,
						       UB913_PAD_SINK,
						       &stweams_mask);

	wet = v4w2_subdev_disabwe_stweams(pwiv->souwce_sd, pwiv->souwce_sd_pad,
					  sink_stweams);
	if (wet)
		wetuwn wet;

	pwiv->enabwed_souwce_stweams &= ~stweams_mask;

	wetuwn 0;
}

static int _ub913_set_wouting(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state,
			      stwuct v4w2_subdev_kwouting *wouting)
{
	static const stwuct v4w2_mbus_fwamefmt in_fowmat = {
		.width = 640,
		.height = 480,
		.code = MEDIA_BUS_FMT_UYVY8_2X8,
		.fiewd = V4W2_FIEWD_NONE,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.ycbcw_enc = V4W2_YCBCW_ENC_601,
		.quantization = V4W2_QUANTIZATION_WIM_WANGE,
		.xfew_func = V4W2_XFEW_FUNC_SWGB,
	};
	static const stwuct v4w2_mbus_fwamefmt out_fowmat = {
		.width = 640,
		.height = 480,
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.fiewd = V4W2_FIEWD_NONE,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.ycbcw_enc = V4W2_YCBCW_ENC_601,
		.quantization = V4W2_QUANTIZATION_WIM_WANGE,
		.xfew_func = V4W2_XFEW_FUNC_SWGB,
	};
	stwuct v4w2_subdev_stweam_configs *stweam_configs;
	unsigned int i;
	int wet;

	/*
	 * Note: we can onwy suppowt up to V4W2_FWAME_DESC_ENTWY_MAX, untiw
	 * fwame desc is made dynamicawwy awwocated.
	 */

	if (wouting->num_woutes > V4W2_FWAME_DESC_ENTWY_MAX)
		wetuwn -EINVAW;

	wet = v4w2_subdev_wouting_vawidate(sd, wouting,
					   V4W2_SUBDEV_WOUTING_ONWY_1_TO_1);
	if (wet)
		wetuwn wet;

	wet = v4w2_subdev_set_wouting(sd, state, wouting);
	if (wet)
		wetuwn wet;

	stweam_configs = &state->stweam_configs;

	fow (i = 0; i < stweam_configs->num_configs; i++) {
		if (stweam_configs->configs[i].pad == UB913_PAD_SINK)
			stweam_configs->configs[i].fmt = in_fowmat;
		ewse
			stweam_configs->configs[i].fmt = out_fowmat;
	}

	wetuwn 0;
}

static int ub913_set_wouting(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     enum v4w2_subdev_fowmat_whence which,
			     stwuct v4w2_subdev_kwouting *wouting)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);

	if (which == V4W2_SUBDEV_FOWMAT_ACTIVE && pwiv->enabwed_souwce_stweams)
		wetuwn -EBUSY;

	wetuwn _ub913_set_wouting(sd, state, wouting);
}

static int ub913_get_fwame_desc(stwuct v4w2_subdev *sd, unsigned int pad,
				stwuct v4w2_mbus_fwame_desc *fd)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);
	const stwuct v4w2_subdev_kwouting *wouting;
	stwuct v4w2_mbus_fwame_desc souwce_fd;
	stwuct v4w2_subdev_woute *woute;
	stwuct v4w2_subdev_state *state;
	int wet;

	if (pad != UB913_PAD_SOUWCE)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(pwiv->souwce_sd, pad, get_fwame_desc,
			       pwiv->souwce_sd_pad, &souwce_fd);
	if (wet)
		wetuwn wet;

	fd->type = V4W2_MBUS_FWAME_DESC_TYPE_PAWAWWEW;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	wouting = &state->wouting;

	fow_each_active_woute(wouting, woute) {
		unsigned int i;

		if (woute->souwce_pad != pad)
			continue;

		fow (i = 0; i < souwce_fd.num_entwies; i++) {
			if (souwce_fd.entwy[i].stweam == woute->sink_stweam)
				bweak;
		}

		if (i == souwce_fd.num_entwies) {
			dev_eww(&pwiv->cwient->dev,
				"Faiwed to find stweam fwom souwce fwame desc\n");
			wet = -EPIPE;
			goto out_unwock;
		}

		fd->entwy[fd->num_entwies].stweam = woute->souwce_stweam;
		fd->entwy[fd->num_entwies].fwags = souwce_fd.entwy[i].fwags;
		fd->entwy[fd->num_entwies].wength = souwce_fd.entwy[i].wength;
		fd->entwy[fd->num_entwies].pixewcode =
			souwce_fd.entwy[i].pixewcode;

		fd->num_entwies++;
	}

out_unwock:
	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static int ub913_set_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *state,
			 stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	const stwuct ub913_fowmat_info *finfo;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE &&
	    pwiv->enabwed_souwce_stweams)
		wetuwn -EBUSY;

	/* Souwce fowmat is fuwwy defined by the sink fowmat, so not settabwe */
	if (fowmat->pad == UB913_PAD_SOUWCE)
		wetuwn v4w2_subdev_get_fmt(sd, state, fowmat);

	finfo = ub913_find_fowmat(fowmat->fowmat.code);
	if (!finfo) {
		finfo = &ub913_fowmats[0];
		fowmat->fowmat.code = finfo->incode;
	}

	/* Set sink fowmat */
	fmt = v4w2_subdev_state_get_fowmat(state, fowmat->pad, fowmat->stweam);
	if (!fmt)
		wetuwn -EINVAW;

	*fmt = fowmat->fowmat;

	/* Pwopagate to souwce fowmat, and adjust the mbus code */
	fmt = v4w2_subdev_state_get_opposite_stweam_fowmat(state, fowmat->pad,
							   fowmat->stweam);
	if (!fmt)
		wetuwn -EINVAW;

	fowmat->fowmat.code = finfo->outcode;

	*fmt = fowmat->fowmat;

	wetuwn 0;
}

static int ub913_init_state(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_subdev_woute woutes[] = {
		{
			.sink_pad = UB913_PAD_SINK,
			.sink_stweam = 0,
			.souwce_pad = UB913_PAD_SOUWCE,
			.souwce_stweam = 0,
			.fwags = V4W2_SUBDEV_WOUTE_FW_ACTIVE,
		},
	};

	stwuct v4w2_subdev_kwouting wouting = {
		.num_woutes = AWWAY_SIZE(woutes),
		.woutes = woutes,
	};

	wetuwn _ub913_set_wouting(sd, state, &wouting);
}

static int ub913_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct ub913_data *pwiv = sd_to_ub913(sd);
	stwuct device *dev = &pwiv->cwient->dev;
	u8 v = 0, v1 = 0, v2 = 0;

	ub913_wead(pwiv, UB913_WEG_MODE_SEW, &v);
	dev_info(dev, "MODE_SEW %#02x\n", v);

	ub913_wead(pwiv, UB913_WEG_CWC_EWWOWS_WSB, &v1);
	ub913_wead(pwiv, UB913_WEG_CWC_EWWOWS_MSB, &v2);
	dev_info(dev, "CWC ewwows %u\n", v1 | (v2 << 8));

	/* cweaw CWC ewwows */
	ub913_wead(pwiv, UB913_WEG_GENEWAW_CFG, &v);
	ub913_wwite(pwiv, UB913_WEG_GENEWAW_CFG,
		    v | UB913_WEG_GENEWAW_CFG_CWC_EWW_WESET);
	ub913_wwite(pwiv, UB913_WEG_GENEWAW_CFG, v);

	ub913_wead(pwiv, UB913_WEG_GENEWAW_STATUS, &v);
	dev_info(dev, "GENEWAW_STATUS %#02x\n", v);

	ub913_wead(pwiv, UB913_WEG_PWW_OVW, &v);
	dev_info(dev, "PWW_OVW %#02x\n", v);

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops ub913_subdev_cowe_ops = {
	.wog_status = ub913_wog_status,
};

static const stwuct v4w2_subdev_pad_ops ub913_pad_ops = {
	.enabwe_stweams = ub913_enabwe_stweams,
	.disabwe_stweams = ub913_disabwe_stweams,
	.set_wouting = ub913_set_wouting,
	.get_fwame_desc = ub913_get_fwame_desc,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = ub913_set_fmt,
};

static const stwuct v4w2_subdev_ops ub913_subdev_ops = {
	.cowe = &ub913_subdev_cowe_ops,
	.pad = &ub913_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ub913_intewnaw_ops = {
	.init_state = ub913_init_state,
};

static const stwuct media_entity_opewations ub913_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int ub913_notify_bound(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_subdev *souwce_subdev,
			      stwuct v4w2_async_connection *asd)
{
	stwuct ub913_data *pwiv = sd_to_ub913(notifiew->sd);
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	wet = media_entity_get_fwnode_pad(&souwce_subdev->entity,
					  souwce_subdev->fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to find pad fow %s\n",
			souwce_subdev->name);
		wetuwn wet;
	}

	pwiv->souwce_sd = souwce_subdev;
	pwiv->souwce_sd_pad = wet;

	wet = media_cweate_pad_wink(&souwce_subdev->entity, pwiv->souwce_sd_pad,
				    &pwiv->sd.entity, UB913_PAD_SINK,
				    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
	if (wet) {
		dev_eww(dev, "Unabwe to wink %s:%u -> %s:0\n",
			souwce_subdev->name, pwiv->souwce_sd_pad,
			pwiv->sd.name);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations ub913_notify_ops = {
	.bound = ub913_notify_bound,
};

static int ub913_v4w2_notifiew_wegistew(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep_fwnode;
	int wet;

	ep_fwnode = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
						    UB913_PAD_SINK, 0, 0);
	if (!ep_fwnode) {
		dev_eww(dev, "No gwaph endpoint\n");
		wetuwn -ENODEV;
	}

	v4w2_async_subdev_nf_init(&pwiv->notifiew, &pwiv->sd);

	asd = v4w2_async_nf_add_fwnode_wemote(&pwiv->notifiew, ep_fwnode,
					      stwuct v4w2_async_connection);

	fwnode_handwe_put(ep_fwnode);

	if (IS_EWW(asd)) {
		dev_eww(dev, "Faiwed to add subdev: %wd", PTW_EWW(asd));
		v4w2_async_nf_cweanup(&pwiv->notifiew);
		wetuwn PTW_EWW(asd);
	}

	pwiv->notifiew.ops = &ub913_notify_ops;

	wet = v4w2_async_nf_wegistew(&pwiv->notifiew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew subdev_notifiew");
		v4w2_async_nf_cweanup(&pwiv->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ub913_v4w2_nf_unwegistew(stwuct ub913_data *pwiv)
{
	v4w2_async_nf_unwegistew(&pwiv->notifiew);
	v4w2_async_nf_cweanup(&pwiv->notifiew);
}

static int ub913_wegistew_cwkout(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	const chaw *name;
	int wet;

	name = kaspwintf(GFP_KEWNEW, "ds90ub913.%s.cwk_out", dev_name(dev));
	if (!name)
		wetuwn -ENOMEM;

	pwiv->cwkout_cwk_hw = devm_cwk_hw_wegistew_fixed_factow(dev, name,
		__cwk_get_name(pwiv->cwkin), 0, 1, 2);

	kfwee(name);

	if (IS_EWW(pwiv->cwkout_cwk_hw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwkout_cwk_hw),
				     "Cannot wegistew cwkout hw\n");

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  pwiv->cwkout_cwk_hw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Cannot add OF cwock pwovidew\n");

	wetuwn 0;
}

static int ub913_i2c_mastew_init(stwuct ub913_data *pwiv)
{
	/* i2c fast mode */
	u32 scw_high = 600 + 300; /* high pewiod + wise time, ns */
	u32 scw_wow = 1300 + 300; /* wow pewiod + faww time, ns */
	unsigned wong wef;
	int wet;

	wef = cwk_get_wate(pwiv->cwkin) / 2;

	scw_high = div64_u64((u64)scw_high * wef, 1000000000);
	scw_wow = div64_u64((u64)scw_wow * wef, 1000000000);

	wet = ub913_wwite(pwiv, UB913_WEG_SCW_HIGH_TIME, scw_high);
	if (wet)
		wetuwn wet;

	wet = ub913_wwite(pwiv, UB913_WEG_SCW_WOW_TIME, scw_wow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ub913_add_i2c_adaptew(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct fwnode_handwe *i2c_handwe;
	int wet;

	i2c_handwe = device_get_named_chiwd_node(dev, "i2c");
	if (!i2c_handwe)
		wetuwn 0;

	wet = i2c_atw_add_adaptew(pwiv->pwat_data->atw, pwiv->pwat_data->powt,
				  dev, i2c_handwe);

	fwnode_handwe_put(i2c_handwe);

	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ub913_pawse_dt(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_PAWAWWEW,
	};
	stwuct fwnode_handwe *ep_fwnode;
	int wet;

	ep_fwnode = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
						    UB913_PAD_SINK, 0, 0);
	if (!ep_fwnode)
		wetuwn dev_eww_pwobe(dev, -ENOENT, "No sink endpoint\n");

	wet = v4w2_fwnode_endpoint_pawse(ep_fwnode, &vep);

	fwnode_handwe_put(ep_fwnode);

	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to pawse sink endpoint data\n");

	if (vep.bus.pawawwew.fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
		pwiv->pcwk_powawity_wising = twue;
	ewse if (vep.bus.pawawwew.fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING)
		pwiv->pcwk_powawity_wising = fawse;
	ewse
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "bad vawue fow 'pcwk-sampwe'\n");

	wetuwn 0;
}

static int ub913_hw_init(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	boow mode_ovewwide;
	u8 mode;
	int wet;
	u8 v;

	wet = ub913_wead(pwiv, UB913_WEG_MODE_SEW, &v);
	if (wet)
		wetuwn wet;

	if (!(v & UB913_WEG_MODE_SEW_MODE_UP_TO_DATE))
		wetuwn dev_eww_pwobe(dev, -ENODEV,
				     "Mode vawue not stabiwized\n");

	mode_ovewwide = v & UB913_WEG_MODE_SEW_MODE_OVEWWIDE;
	mode = v & UB913_WEG_MODE_SEW_MODE_MASK;

	dev_dbg(dev, "mode fwom %s: %#x\n",
		mode_ovewwide ? "weg" : "desewiawizew", mode);

	wet = ub913_i2c_mastew_init(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "i2c mastew init faiwed\n");

	ub913_wead(pwiv, UB913_WEG_GENEWAW_CFG, &v);
	v &= ~UB913_WEG_GENEWAW_CFG_PCWK_WISING;
	v |= pwiv->pcwk_powawity_wising ? UB913_WEG_GENEWAW_CFG_PCWK_WISING : 0;
	ub913_wwite(pwiv, UB913_WEG_GENEWAW_CFG, v);

	wetuwn 0;
}

static int ub913_subdev_init(stwuct ub913_data *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	v4w2_i2c_subdev_init(&pwiv->sd, pwiv->cwient, &ub913_subdev_ops);
	pwiv->sd.intewnaw_ops = &ub913_intewnaw_ops;
	pwiv->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_STWEAMS;
	pwiv->sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	pwiv->sd.entity.ops = &ub913_entity_ops;

	pwiv->pads[0].fwags = MEDIA_PAD_FW_SINK;
	pwiv->pads[1].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&pwiv->sd.entity, 2, pwiv->pads);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init pads\n");

	wet = v4w2_subdev_init_finawize(&pwiv->sd);
	if (wet)
		goto eww_entity_cweanup;

	wet = ub913_v4w2_notifiew_wegistew(pwiv);
	if (wet) {
		dev_eww_pwobe(dev, wet,
			      "v4w2 subdev notifiew wegistew faiwed\n");
		goto eww_subdev_cweanup;
	}

	wet = v4w2_async_wegistew_subdev(&pwiv->sd);
	if (wet) {
		dev_eww_pwobe(dev, wet, "v4w2_async_wegistew_subdev ewwow\n");
		goto eww_unweg_notif;
	}

	wetuwn 0;

eww_unweg_notif:
	ub913_v4w2_nf_unwegistew(pwiv);
eww_subdev_cweanup:
	v4w2_subdev_cweanup(&pwiv->sd);
eww_entity_cweanup:
	media_entity_cweanup(&pwiv->sd.entity);

	wetuwn wet;
}

static void ub913_subdev_uninit(stwuct ub913_data *pwiv)
{
	v4w2_async_unwegistew_subdev(&pwiv->sd);
	ub913_v4w2_nf_unwegistew(pwiv);
	v4w2_subdev_cweanup(&pwiv->sd);
	fwnode_handwe_put(pwiv->sd.fwnode);
	media_entity_cweanup(&pwiv->sd.entity);
}

static int ub913_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ub913_data *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;

	pwiv->pwat_data = dev_get_pwatdata(&cwient->dev);
	if (!pwiv->pwat_data)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Pwatfowm data missing\n");

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &ub913_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wegmap),
				     "Faiwed to init wegmap\n");

	/*
	 * ub913 can awso wowk without ext cwock, but that is not suppowted by
	 * the dwivew yet.
	 */
	pwiv->cwkin = devm_cwk_get(dev, "cwkin");
	if (IS_EWW(pwiv->cwkin))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwkin),
				     "Cannot get CWKIN\n");

	wet = ub913_pawse_dt(pwiv);
	if (wet)
		wetuwn wet;

	wet = ub913_hw_init(pwiv);
	if (wet)
		wetuwn wet;

	wet = ub913_gpiochip_pwobe(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init gpiochip\n");

	wet = ub913_wegistew_cwkout(pwiv);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to wegistew cwkout\n");
		goto eww_gpiochip_wemove;
	}

	wet = ub913_subdev_init(pwiv);
	if (wet)
		goto eww_gpiochip_wemove;

	wet = ub913_add_i2c_adaptew(pwiv);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to add wemote i2c adaptew\n");
		goto eww_subdev_uninit;
	}

	wetuwn 0;

eww_subdev_uninit:
	ub913_subdev_uninit(pwiv);
eww_gpiochip_wemove:
	ub913_gpiochip_wemove(pwiv);

	wetuwn wet;
}

static void ub913_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ub913_data *pwiv = sd_to_ub913(sd);

	i2c_atw_dew_adaptew(pwiv->pwat_data->atw, pwiv->pwat_data->powt);

	ub913_subdev_uninit(pwiv);

	ub913_gpiochip_wemove(pwiv);
}

static const stwuct i2c_device_id ub913_id[] = { { "ds90ub913a-q1", 0 }, {} };
MODUWE_DEVICE_TABWE(i2c, ub913_id);

static const stwuct of_device_id ub913_dt_ids[] = {
	{ .compatibwe = "ti,ds90ub913a-q1" },
	{}
};
MODUWE_DEVICE_TABWE(of, ub913_dt_ids);

static stwuct i2c_dwivew ds90ub913_dwivew = {
	.pwobe		= ub913_pwobe,
	.wemove		= ub913_wemove,
	.id_tabwe	= ub913_id,
	.dwivew = {
		.name	= "ds90ub913a",
		.of_match_tabwe = ub913_dt_ids,
	},
};
moduwe_i2c_dwivew(ds90ub913_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Texas Instwuments DS90UB913 FPD-Wink III Sewiawizew Dwivew");
MODUWE_AUTHOW("Wuca Cewesowi <wuca@wucacewesowi.net>");
MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>");
MODUWE_IMPOWT_NS(I2C_ATW);
