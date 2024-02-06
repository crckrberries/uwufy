// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_wwpf.c  --  W-Caw VSP1 Wead and Wwite Pixew Fowmattews
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_video.h"

#define WWPF_MIN_WIDTH				1
#define WWPF_MIN_HEIGHT				1

stwuct v4w2_wect *vsp1_wwpf_get_cwop(stwuct vsp1_wwpf *wwpf,
				     stwuct v4w2_subdev_state *sd_state)
{
	wetuwn v4w2_subdev_state_get_cwop(sd_state, WWPF_PAD_SINK);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static int vsp1_wwpf_enum_mbus_code(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_mbus_code_enum *code)
{
	static const unsigned int codes[] = {
		MEDIA_BUS_FMT_AWGB8888_1X32,
		MEDIA_BUS_FMT_AHSV8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	};

	if (code->index >= AWWAY_SIZE(codes))
		wetuwn -EINVAW;

	code->code = codes[code->index];

	wetuwn 0;
}

static int vsp1_wwpf_enum_fwame_size(stwuct v4w2_subdev *subdev,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct vsp1_wwpf *wwpf = to_wwpf(subdev);

	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   WWPF_MIN_WIDTH,
					   WWPF_MIN_HEIGHT, wwpf->max_width,
					   wwpf->max_height);
}

static int vsp1_wwpf_set_fowmat(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct vsp1_wwpf *wwpf = to_wwpf(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	mutex_wock(&wwpf->entity.wock);

	state = vsp1_entity_get_state(&wwpf->entity, sd_state, fmt->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	/* Defauwt to YUV if the wequested fowmat is not suppowted. */
	if (fmt->fowmat.code != MEDIA_BUS_FMT_AWGB8888_1X32 &&
	    fmt->fowmat.code != MEDIA_BUS_FMT_AHSV8888_1X32 &&
	    fmt->fowmat.code != MEDIA_BUS_FMT_AYUV8_1X32)
		fmt->fowmat.code = MEDIA_BUS_FMT_AYUV8_1X32;

	fowmat = vsp1_entity_get_pad_fowmat(&wwpf->entity, state, fmt->pad);

	if (fmt->pad == WWPF_PAD_SOUWCE) {
		/*
		 * The WWPF pewfowms fowmat convewsion but can't scawe, onwy the
		 * fowmat code can be changed on the souwce pad.
		 */
		fowmat->code = fmt->fowmat.code;
		fmt->fowmat = *fowmat;
		goto done;
	}

	fowmat->code = fmt->fowmat.code;
	fowmat->width = cwamp_t(unsigned int, fmt->fowmat.width,
				WWPF_MIN_WIDTH, wwpf->max_width);
	fowmat->height = cwamp_t(unsigned int, fmt->fowmat.height,
				 WWPF_MIN_HEIGHT, wwpf->max_height);
	fowmat->fiewd = V4W2_FIEWD_NONE;
	fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	fmt->fowmat = *fowmat;

	if (wwpf->entity.type == VSP1_ENTITY_WPF) {
		stwuct v4w2_wect *cwop;

		/* Update the sink cwop wectangwe. */
		cwop = vsp1_wwpf_get_cwop(wwpf, state);
		cwop->weft = 0;
		cwop->top = 0;
		cwop->width = fmt->fowmat.width;
		cwop->height = fmt->fowmat.height;
	}

	/* Pwopagate the fowmat to the souwce pad. */
	fowmat = vsp1_entity_get_pad_fowmat(&wwpf->entity, state,
					    WWPF_PAD_SOUWCE);
	*fowmat = fmt->fowmat;

	if (wwpf->fwip.wotate) {
		fowmat->width = fmt->fowmat.height;
		fowmat->height = fmt->fowmat.width;
	}

done:
	mutex_unwock(&wwpf->entity.wock);
	wetuwn wet;
}

static int vsp1_wwpf_get_sewection(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_wwpf *wwpf = to_wwpf(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	/*
	 * Cwopping is onwy suppowted on the WPF and is impwemented on the sink
	 * pad.
	 */
	if (wwpf->entity.type == VSP1_ENTITY_WPF || sew->pad != WWPF_PAD_SINK)
		wetuwn -EINVAW;

	mutex_wock(&wwpf->entity.wock);

	state = vsp1_entity_get_state(&wwpf->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		sew->w = *vsp1_wwpf_get_cwop(wwpf, state);
		bweak;

	case V4W2_SEW_TGT_CWOP_BOUNDS:
		fowmat = vsp1_entity_get_pad_fowmat(&wwpf->entity, state,
						    WWPF_PAD_SINK);
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = fowmat->width;
		sew->w.height = fowmat->height;
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

done:
	mutex_unwock(&wwpf->entity.wock);
	wetuwn wet;
}

static int vsp1_wwpf_set_sewection(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_wwpf *wwpf = to_wwpf(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;
	int wet = 0;

	/*
	 * Cwopping is onwy suppowted on the WPF and is impwemented on the sink
	 * pad.
	 */
	if (wwpf->entity.type == VSP1_ENTITY_WPF || sew->pad != WWPF_PAD_SINK)
		wetuwn -EINVAW;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	mutex_wock(&wwpf->entity.wock);

	state = vsp1_entity_get_state(&wwpf->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	/* Make suwe the cwop wectangwe is entiwewy contained in the image. */
	fowmat = vsp1_entity_get_pad_fowmat(&wwpf->entity, state,
					    WWPF_PAD_SINK);

	/*
	 * Westwict the cwop wectangwe coowdinates to muwtipwes of 2 to avoid
	 * shifting the cowow pwane.
	 */
	if (fowmat->code == MEDIA_BUS_FMT_AYUV8_1X32) {
		sew->w.weft = AWIGN(sew->w.weft, 2);
		sew->w.top = AWIGN(sew->w.top, 2);
		sew->w.width = wound_down(sew->w.width, 2);
		sew->w.height = wound_down(sew->w.height, 2);
	}

	sew->w.weft = min_t(unsigned int, sew->w.weft, fowmat->width - 2);
	sew->w.top = min_t(unsigned int, sew->w.top, fowmat->height - 2);
	sew->w.width = min_t(unsigned int, sew->w.width,
			     fowmat->width - sew->w.weft);
	sew->w.height = min_t(unsigned int, sew->w.height,
			      fowmat->height - sew->w.top);

	cwop = vsp1_wwpf_get_cwop(wwpf, state);
	*cwop = sew->w;

	/* Pwopagate the fowmat to the souwce pad. */
	fowmat = vsp1_entity_get_pad_fowmat(&wwpf->entity, state,
					    WWPF_PAD_SOUWCE);
	fowmat->width = cwop->width;
	fowmat->height = cwop->height;

done:
	mutex_unwock(&wwpf->entity.wock);
	wetuwn wet;
}

static const stwuct v4w2_subdev_pad_ops vsp1_wwpf_pad_ops = {
	.enum_mbus_code = vsp1_wwpf_enum_mbus_code,
	.enum_fwame_size = vsp1_wwpf_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = vsp1_wwpf_set_fowmat,
	.get_sewection = vsp1_wwpf_get_sewection,
	.set_sewection = vsp1_wwpf_set_sewection,
};

const stwuct v4w2_subdev_ops vsp1_wwpf_subdev_ops = {
	.pad    = &vsp1_wwpf_pad_ops,
};

/* -----------------------------------------------------------------------------
 * Contwows
 */

static int vsp1_wwpf_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_wwpf *wwpf =
		containew_of(ctww->handwew, stwuct vsp1_wwpf, ctwws);

	switch (ctww->id) {
	case V4W2_CID_AWPHA_COMPONENT:
		wwpf->awpha = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops vsp1_wwpf_ctww_ops = {
	.s_ctww = vsp1_wwpf_s_ctww,
};

int vsp1_wwpf_init_ctwws(stwuct vsp1_wwpf *wwpf, unsigned int ncontwows)
{
	v4w2_ctww_handwew_init(&wwpf->ctwws, ncontwows + 1);
	v4w2_ctww_new_std(&wwpf->ctwws, &vsp1_wwpf_ctww_ops,
			  V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 255);

	wwpf->entity.subdev.ctww_handwew = &wwpf->ctwws;

	wetuwn wwpf->ctwws.ewwow;
}
