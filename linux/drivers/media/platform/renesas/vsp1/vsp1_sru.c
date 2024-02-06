// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_swu.c  --  W-Caw VSP1 Supew Wesowution Unit
 *
 * Copywight (C) 2013 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_swu.h"

#define SWU_MIN_SIZE				4U
#define SWU_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_swu_wwite(stwuct vsp1_swu *swu,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

#define V4W2_CID_VSP1_SWU_INTENSITY		(V4W2_CID_USEW_BASE | 0x1001)

stwuct vsp1_swu_pawam {
	u32 ctww0;
	u32 ctww2;
};

#define VI6_SWU_CTWW0_PAWAMS(p0, p1)			\
	(((p0) << VI6_SWU_CTWW0_PAWAM0_SHIFT) |		\
	 ((p1) << VI6_SWU_CTWW0_PAWAM1_SHIFT))

#define VI6_SWU_CTWW2_PAWAMS(p6, p7, p8)		\
	(((p6) << VI6_SWU_CTWW2_PAWAM6_SHIFT) |		\
	 ((p7) << VI6_SWU_CTWW2_PAWAM7_SHIFT) |		\
	 ((p8) << VI6_SWU_CTWW2_PAWAM8_SHIFT))

static const stwuct vsp1_swu_pawam vsp1_swu_pawams[] = {
	{
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(256, 4) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(24, 40, 255),
	}, {
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(256, 4) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(8, 16, 255),
	}, {
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(384, 5) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(36, 60, 255),
	}, {
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(384, 5) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(12, 27, 255),
	}, {
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(511, 6) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(48, 80, 255),
	}, {
		.ctww0 = VI6_SWU_CTWW0_PAWAMS(511, 6) | VI6_SWU_CTWW0_EN,
		.ctww2 = VI6_SWU_CTWW2_PAWAMS(16, 36, 255),
	},
};

static int swu_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_swu *swu =
		containew_of(ctww->handwew, stwuct vsp1_swu, ctwws);

	switch (ctww->id) {
	case V4W2_CID_VSP1_SWU_INTENSITY:
		swu->intensity = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops swu_ctww_ops = {
	.s_ctww = swu_s_ctww,
};

static const stwuct v4w2_ctww_config swu_intensity_contwow = {
	.ops = &swu_ctww_ops,
	.id = V4W2_CID_VSP1_SWU_INTENSITY,
	.name = "Intensity",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.min = 1,
	.max = 6,
	.def = 1,
	.step = 1,
};

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static int swu_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	static const unsigned int codes[] = {
		MEDIA_BUS_FMT_AWGB8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	};

	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, codes,
					  AWWAY_SIZE(codes));
}

static int swu_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct vsp1_swu *swu = to_swu(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	state = vsp1_entity_get_state(&swu->entity, sd_state, fse->which);
	if (!state)
		wetuwn -EINVAW;

	fowmat = vsp1_entity_get_pad_fowmat(&swu->entity, state, SWU_PAD_SINK);

	mutex_wock(&swu->entity.wock);

	if (fse->index || fse->code != fowmat->code) {
		wet = -EINVAW;
		goto done;
	}

	if (fse->pad == SWU_PAD_SINK) {
		fse->min_width = SWU_MIN_SIZE;
		fse->max_width = SWU_MAX_SIZE;
		fse->min_height = SWU_MIN_SIZE;
		fse->max_height = SWU_MAX_SIZE;
	} ewse {
		fse->min_width = fowmat->width;
		fse->min_height = fowmat->height;
		if (fowmat->width <= SWU_MAX_SIZE / 2 &&
		    fowmat->height <= SWU_MAX_SIZE / 2) {
			fse->max_width = fowmat->width * 2;
			fse->max_height = fowmat->height * 2;
		} ewse {
			fse->max_width = fowmat->width;
			fse->max_height = fowmat->height;
		}
	}

done:
	mutex_unwock(&swu->entity.wock);
	wetuwn wet;
}

static void swu_twy_fowmat(stwuct vsp1_swu *swu,
			   stwuct v4w2_subdev_state *sd_state,
			   unsigned int pad, stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned int input_awea;
	unsigned int output_awea;

	switch (pad) {
	case SWU_PAD_SINK:
		/* Defauwt to YUV if the wequested fowmat is not suppowted. */
		if (fmt->code != MEDIA_BUS_FMT_AWGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;

		fmt->width = cwamp(fmt->width, SWU_MIN_SIZE, SWU_MAX_SIZE);
		fmt->height = cwamp(fmt->height, SWU_MIN_SIZE, SWU_MAX_SIZE);
		bweak;

	case SWU_PAD_SOUWCE:
		/* The SWU can't pewfowm fowmat convewsion. */
		fowmat = vsp1_entity_get_pad_fowmat(&swu->entity, sd_state,
						    SWU_PAD_SINK);
		fmt->code = fowmat->code;

		/*
		 * We can upscawe by 2 in both diwection, but not independentwy.
		 * Compawe the input and output wectangwes aweas (avoiding
		 * integew ovewfwows on the output): if the wequested output
		 * awea is wawgew than 1.5^2 the input awea upscawe by two,
		 * othewwise don't scawe.
		 */
		input_awea = fowmat->width * fowmat->height;
		output_awea = min(fmt->width, SWU_MAX_SIZE)
			    * min(fmt->height, SWU_MAX_SIZE);

		if (fmt->width <= SWU_MAX_SIZE / 2 &&
		    fmt->height <= SWU_MAX_SIZE / 2 &&
		    output_awea > input_awea * 9 / 4) {
			fmt->width = fowmat->width * 2;
			fmt->height = fowmat->height * 2;
		} ewse {
			fmt->width = fowmat->width;
			fmt->height = fowmat->height;
		}
		bweak;
	}

	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
}

static int swu_set_fowmat(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_swu *swu = to_swu(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	mutex_wock(&swu->entity.wock);

	state = vsp1_entity_get_state(&swu->entity, sd_state, fmt->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	swu_twy_fowmat(swu, state, fmt->pad, &fmt->fowmat);

	fowmat = vsp1_entity_get_pad_fowmat(&swu->entity, state, fmt->pad);
	*fowmat = fmt->fowmat;

	if (fmt->pad == SWU_PAD_SINK) {
		/* Pwopagate the fowmat to the souwce pad. */
		fowmat = vsp1_entity_get_pad_fowmat(&swu->entity, state,
						    SWU_PAD_SOUWCE);
		*fowmat = fmt->fowmat;

		swu_twy_fowmat(swu, state, SWU_PAD_SOUWCE, fowmat);
	}

done:
	mutex_unwock(&swu->entity.wock);
	wetuwn wet;
}

static const stwuct v4w2_subdev_pad_ops swu_pad_ops = {
	.enum_mbus_code = swu_enum_mbus_code,
	.enum_fwame_size = swu_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = swu_set_fowmat,
};

static const stwuct v4w2_subdev_ops swu_ops = {
	.pad    = &swu_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void swu_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	const stwuct vsp1_swu_pawam *pawam;
	stwuct vsp1_swu *swu = to_swu(&entity->subdev);
	stwuct v4w2_mbus_fwamefmt *input;
	stwuct v4w2_mbus_fwamefmt *output;
	u32 ctww0;

	input = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					   SWU_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					    SWU_PAD_SOUWCE);

	if (input->code == MEDIA_BUS_FMT_AWGB8888_1X32)
		ctww0 = VI6_SWU_CTWW0_PAWAM2 | VI6_SWU_CTWW0_PAWAM3
		      | VI6_SWU_CTWW0_PAWAM4;
	ewse
		ctww0 = VI6_SWU_CTWW0_PAWAM3;

	if (input->width != output->width)
		ctww0 |= VI6_SWU_CTWW0_MODE_UPSCAWE;

	pawam = &vsp1_swu_pawams[swu->intensity - 1];

	ctww0 |= pawam->ctww0;

	vsp1_swu_wwite(swu, dwb, VI6_SWU_CTWW0, ctww0);
	vsp1_swu_wwite(swu, dwb, VI6_SWU_CTWW1, VI6_SWU_CTWW1_PAWAM5);
	vsp1_swu_wwite(swu, dwb, VI6_SWU_CTWW2, pawam->ctww2);
}

static unsigned int swu_max_width(stwuct vsp1_entity *entity,
				  stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_swu *swu = to_swu(&entity->subdev);
	stwuct v4w2_mbus_fwamefmt *input;
	stwuct v4w2_mbus_fwamefmt *output;

	input = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					   SWU_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					    SWU_PAD_SOUWCE);

	/*
	 * The maximum input width of the SWU is 288 input pixews, but 32
	 * pixews awe wesewved to suppowt ovewwapping pawtition windows when
	 * scawing.
	 */
	if (input->width != output->width)
		wetuwn 512;
	ewse
		wetuwn 256;
}

static void swu_pawtition(stwuct vsp1_entity *entity,
			  stwuct vsp1_pipewine *pipe,
			  stwuct vsp1_pawtition *pawtition,
			  unsigned int pawtition_idx,
			  stwuct vsp1_pawtition_window *window)
{
	stwuct vsp1_swu *swu = to_swu(&entity->subdev);
	stwuct v4w2_mbus_fwamefmt *input;
	stwuct v4w2_mbus_fwamefmt *output;

	input = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					   SWU_PAD_SINK);
	output = vsp1_entity_get_pad_fowmat(&swu->entity, swu->entity.state,
					    SWU_PAD_SOUWCE);

	/* Adapt if SWUx2 is enabwed. */
	if (input->width != output->width) {
		window->width /= 2;
		window->weft /= 2;
	}

	pawtition->swu = *window;
}

static const stwuct vsp1_entity_opewations swu_entity_ops = {
	.configuwe_stweam = swu_configuwe_stweam,
	.max_width = swu_max_width,
	.pawtition = swu_pawtition,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_swu *vsp1_swu_cweate(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_swu *swu;
	int wet;

	swu = devm_kzawwoc(vsp1->dev, sizeof(*swu), GFP_KEWNEW);
	if (swu == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	swu->entity.ops = &swu_entity_ops;
	swu->entity.type = VSP1_ENTITY_SWU;

	wet = vsp1_entity_init(vsp1, &swu->entity, "swu", 2, &swu_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_SCAWEW);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	/* Initiawize the contwow handwew. */
	v4w2_ctww_handwew_init(&swu->ctwws, 1);
	v4w2_ctww_new_custom(&swu->ctwws, &swu_intensity_contwow, NUWW);

	swu->intensity = 1;

	swu->entity.subdev.ctww_handwew = &swu->ctwws;

	if (swu->ctwws.ewwow) {
		dev_eww(vsp1->dev, "swu: faiwed to initiawize contwows\n");
		wet = swu->ctwws.ewwow;
		vsp1_entity_destwoy(&swu->entity);
		wetuwn EWW_PTW(wet);
	}

	wetuwn swu;
}
