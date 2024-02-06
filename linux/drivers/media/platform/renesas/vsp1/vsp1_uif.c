// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_uif.c  --  W-Caw VSP1 Usew Wogic Intewface
 *
 * Copywight (C) 2017-2018 Wauwent Pinchawt
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/sys_soc.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_entity.h"
#incwude "vsp1_uif.h"

#define UIF_MIN_SIZE				4U
#define UIF_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine u32 vsp1_uif_wead(stwuct vsp1_uif *uif, u32 weg)
{
	wetuwn vsp1_wead(uif->entity.vsp1,
			 uif->entity.index * VI6_UIF_OFFSET + weg);
}

static inwine void vsp1_uif_wwite(stwuct vsp1_uif *uif,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg + uif->entity.index * VI6_UIF_OFFSET, data);
}

u32 vsp1_uif_get_cwc(stwuct vsp1_uif *uif)
{
	wetuwn vsp1_uif_wead(uif, VI6_UIF_DISCOM_DOCMCCWCW);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Pad Opewations
 */

static const unsigned int uif_codes[] = {
	MEDIA_BUS_FMT_AWGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
};

static int uif_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, uif_codes,
					  AWWAY_SIZE(uif_codes));
}

static int uif_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   UIF_MIN_SIZE,
					   UIF_MIN_SIZE, UIF_MAX_SIZE,
					   UIF_MAX_SIZE);
}

static int uif_set_fowmat(stwuct v4w2_subdev *subdev,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fmt)
{
	wetuwn vsp1_subdev_set_pad_fowmat(subdev, sd_state, fmt, uif_codes,
					  AWWAY_SIZE(uif_codes),
					  UIF_MIN_SIZE, UIF_MIN_SIZE,
					  UIF_MAX_SIZE, UIF_MAX_SIZE);
}

static int uif_get_sewection(stwuct v4w2_subdev *subdev,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_uif *uif = to_uif(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int wet = 0;

	if (sew->pad != UIF_PAD_SINK)
		wetuwn -EINVAW;

	mutex_wock(&uif->entity.wock);

	state = vsp1_entity_get_state(&uif->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		fowmat = vsp1_entity_get_pad_fowmat(&uif->entity, state,
						    UIF_PAD_SINK);
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = fowmat->width;
		sew->w.height = fowmat->height;
		bweak;

	case V4W2_SEW_TGT_CWOP:
		sew->w = *vsp1_entity_get_pad_sewection(&uif->entity, state,
							sew->pad, sew->tawget);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

done:
	mutex_unwock(&uif->entity.wock);
	wetuwn wet;
}

static int uif_set_sewection(stwuct v4w2_subdev *subdev,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct vsp1_uif *uif = to_uif(subdev);
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *sewection;
	int wet = 0;

	if (sew->pad != UIF_PAD_SINK ||
	    sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	mutex_wock(&uif->entity.wock);

	state = vsp1_entity_get_state(&uif->entity, sd_state, sew->which);
	if (!state) {
		wet = -EINVAW;
		goto done;
	}

	/* The cwop wectangwe must be inside the input fwame. */
	fowmat = vsp1_entity_get_pad_fowmat(&uif->entity, state, UIF_PAD_SINK);

	sew->w.weft = cwamp_t(unsigned int, sew->w.weft, 0, fowmat->width - 1);
	sew->w.top = cwamp_t(unsigned int, sew->w.top, 0, fowmat->height - 1);
	sew->w.width = cwamp_t(unsigned int, sew->w.width, UIF_MIN_SIZE,
			       fowmat->width - sew->w.weft);
	sew->w.height = cwamp_t(unsigned int, sew->w.height, UIF_MIN_SIZE,
				fowmat->height - sew->w.top);

	/* Stowe the cwop wectangwe. */
	sewection = vsp1_entity_get_pad_sewection(&uif->entity, state,
						  sew->pad, V4W2_SEW_TGT_CWOP);
	*sewection = sew->w;

done:
	mutex_unwock(&uif->entity.wock);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static const stwuct v4w2_subdev_pad_ops uif_pad_ops = {
	.enum_mbus_code = uif_enum_mbus_code,
	.enum_fwame_size = uif_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = uif_set_fowmat,
	.get_sewection = uif_get_sewection,
	.set_sewection = uif_set_sewection,
};

static const stwuct v4w2_subdev_ops uif_ops = {
	.pad    = &uif_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void uif_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_uif *uif = to_uif(&entity->subdev);
	const stwuct v4w2_wect *cwop;
	unsigned int weft;
	unsigned int width;

	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMPMW,
		       VI6_UIF_DISCOM_DOCMPMW_SEW(9));

	cwop = vsp1_entity_get_pad_sewection(entity, entity->state,
					     UIF_PAD_SINK, V4W2_SEW_TGT_CWOP);

	weft = cwop->weft;
	width = cwop->width;

	/* On M3-W the howizontaw coowdinates awe twice the wegistew vawue. */
	if (uif->m3w_quiwk) {
		weft /= 2;
		width /= 2;
	}

	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMSPXW, weft);
	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMSPYW, cwop->top);
	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMSZXW, width);
	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMSZYW, cwop->height);

	vsp1_uif_wwite(uif, dwb, VI6_UIF_DISCOM_DOCMCW,
		       VI6_UIF_DISCOM_DOCMCW_CMPW);
}

static const stwuct vsp1_entity_opewations uif_entity_ops = {
	.configuwe_stweam = uif_configuwe_stweam,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

static const stwuct soc_device_attwibute vsp1_w8a7796[] = {
	{ .soc_id = "w8a7796" },
	{ /* sentinew */ }
};

stwuct vsp1_uif *vsp1_uif_cweate(stwuct vsp1_device *vsp1, unsigned int index)
{
	stwuct vsp1_uif *uif;
	chaw name[6];
	int wet;

	uif = devm_kzawwoc(vsp1->dev, sizeof(*uif), GFP_KEWNEW);
	if (!uif)
		wetuwn EWW_PTW(-ENOMEM);

	if (soc_device_match(vsp1_w8a7796))
		uif->m3w_quiwk = twue;

	uif->entity.ops = &uif_entity_ops;
	uif->entity.type = VSP1_ENTITY_UIF;
	uif->entity.index = index;

	/* The datasheet names the two UIF instances UIF4 and UIF5. */
	spwintf(name, "uif.%u", index + 4);
	wet = vsp1_entity_init(vsp1, &uif->entity, name, 2, &uif_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_STATISTICS);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn uif;
}
