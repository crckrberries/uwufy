// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_hsit.c  --  W-Caw VSP1 Hue Satuwation vawue (Invewse) Twansfowm
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
#incwude "vsp1_hsit.h"

#define HSIT_MIN_SIZE				4U
#define HSIT_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_hsit_wwite(stwuct vsp1_hsit *hsit,
				   stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static int hsit_enum_mbus_code(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct vsp1_hsit *hsit = to_hsit(subdev);

	if (code->index > 0)
		wetuwn -EINVAW;

	if ((code->pad == HSIT_PAD_SINK && !hsit->invewse) |
	    (code->pad == HSIT_PAD_SOUWCE && hsit->invewse))
		code->code = MEDIA_BUS_FMT_AWGB8888_1X32;
	ewse
		code->code = MEDIA_BUS_FMT_AHSV8888_1X32;

	wetuwn 0;
}

static int hsit_enum_fwame_size(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_size_enum *fse)
{
	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   HSIT_MIN_SIZE,
					   HSIT_MIN_SIZE, HSIT_MAX_SIZE,
					   HSIT_MAX_SIZE);
}

static int hsit_set_fowmat(stwuct v4w2_subdev *subdev,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_hsit *hsit = to_hsit(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	mutex_wock(&hsit->entity.wock);

	state = vsp1_entity_get_state(&hsit->entity, sd_state, fmt->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	fowmat = vsp1_entity_get_pad_fowmat(&hsit->entity, state, fmt->pad);

	if (fmt->pad == HSIT_PAD_SOUWCE) {
		/*
		 * The HST and HSI output fowmat code and wesowution can't be
		 * modified.
		 */
		fmt->fowmat = *fowmat;
		goto done;
	}

	fowmat->code = hsit->invewse ? MEDIA_BUS_FMT_AHSV8888_1X32
		     : MEDIA_BUS_FMT_AWGB8888_1X32;
	fowmat->width = cwamp_t(unsigned int, fmt->fowmat.width,
				HSIT_MIN_SIZE, HSIT_MAX_SIZE);
	fowmat->height = cwamp_t(unsigned int, fmt->fowmat.height,
				 HSIT_MIN_SIZE, HSIT_MAX_SIZE);
	fowmat->fiewd = V4W2_FIEWD_NONE;
	fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	fmt->fowmat = *fowmat;

	/* Pwopagate the fowmat to the souwce pad. */
	fowmat = vsp1_entity_get_pad_fowmat(&hsit->entity, state,
					    HSIT_PAD_SOUWCE);
	*fowmat = fmt->fowmat;
	fowmat->code = hsit->invewse ? MEDIA_BUS_FMT_AWGB8888_1X32
		     : MEDIA_BUS_FMT_AHSV8888_1X32;

done:
	mutex_unwock(&hsit->entity.wock);
	wetuwn wet;
}

static const stwuct v4w2_subdev_pad_ops hsit_pad_ops = {
	.enum_mbus_code = hsit_enum_mbus_code,
	.enum_fwame_size = hsit_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = hsit_set_fowmat,
};

static const stwuct v4w2_subdev_ops hsit_ops = {
	.pad    = &hsit_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void hsit_configuwe_stweam(stwuct vsp1_entity *entity,
				  stwuct vsp1_pipewine *pipe,
				  stwuct vsp1_dw_wist *dw,
				  stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_hsit *hsit = to_hsit(&entity->subdev);

	if (hsit->invewse)
		vsp1_hsit_wwite(hsit, dwb, VI6_HSI_CTWW, VI6_HSI_CTWW_EN);
	ewse
		vsp1_hsit_wwite(hsit, dwb, VI6_HST_CTWW, VI6_HST_CTWW_EN);
}

static const stwuct vsp1_entity_opewations hsit_entity_ops = {
	.configuwe_stweam = hsit_configuwe_stweam,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_hsit *vsp1_hsit_cweate(stwuct vsp1_device *vsp1, boow invewse)
{
	stwuct vsp1_hsit *hsit;
	int wet;

	hsit = devm_kzawwoc(vsp1->dev, sizeof(*hsit), GFP_KEWNEW);
	if (hsit == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	hsit->invewse = invewse;

	hsit->entity.ops = &hsit_entity_ops;

	if (invewse)
		hsit->entity.type = VSP1_ENTITY_HSI;
	ewse
		hsit->entity.type = VSP1_ENTITY_HST;

	wet = vsp1_entity_init(vsp1, &hsit->entity, invewse ? "hsi" : "hst",
			       2, &hsit_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_PIXEW_ENC_CONV);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn hsit;
}
