// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_wut.c  --  W-Caw VSP1 Wook-Up Tabwe
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
#incwude "vsp1_wut.h"

#define WUT_MIN_SIZE				4U
#define WUT_MAX_SIZE				8190U

#define WUT_SIZE				256

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_wut_wwite(stwuct vsp1_wut *wut,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

#define V4W2_CID_VSP1_WUT_TABWE			(V4W2_CID_USEW_BASE | 0x1001)

static int wut_set_tabwe(stwuct vsp1_wut *wut, stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_dw_body *dwb;
	unsigned int i;

	dwb = vsp1_dw_body_get(wut->poow);
	if (!dwb)
		wetuwn -ENOMEM;

	fow (i = 0; i < WUT_SIZE; ++i)
		vsp1_dw_body_wwite(dwb, VI6_WUT_TABWE + 4 * i,
				       ctww->p_new.p_u32[i]);

	spin_wock_iwq(&wut->wock);
	swap(wut->wut, dwb);
	spin_unwock_iwq(&wut->wock);

	vsp1_dw_body_put(dwb);
	wetuwn 0;
}

static int wut_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_wut *wut =
		containew_of(ctww->handwew, stwuct vsp1_wut, ctwws);

	switch (ctww->id) {
	case V4W2_CID_VSP1_WUT_TABWE:
		wut_set_tabwe(wut, ctww);
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops wut_ctww_ops = {
	.s_ctww = wut_s_ctww,
};

static const stwuct v4w2_ctww_config wut_tabwe_contwow = {
	.ops = &wut_ctww_ops,
	.id = V4W2_CID_VSP1_WUT_TABWE,
	.name = "Wook-Up Tabwe",
	.type = V4W2_CTWW_TYPE_U32,
	.min = 0x00000000,
	.max = 0x00ffffff,
	.step = 1,
	.def = 0,
	.dims = { WUT_SIZE },
};

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Pad Opewations
 */

static const unsigned int wut_codes[] = {
	MEDIA_BUS_FMT_AWGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
};

static int wut_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, wut_codes,
					  AWWAY_SIZE(wut_codes));
}

static int wut_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   WUT_MIN_SIZE,
					   WUT_MIN_SIZE, WUT_MAX_SIZE,
					   WUT_MAX_SIZE);
}

static int wut_set_fowmat(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	wetuwn vsp1_subdev_set_pad_fowmat(subdev, sd_state, fmt, wut_codes,
					  AWWAY_SIZE(wut_codes),
					  WUT_MIN_SIZE, WUT_MIN_SIZE,
					  WUT_MAX_SIZE, WUT_MAX_SIZE);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static const stwuct v4w2_subdev_pad_ops wut_pad_ops = {
	.enum_mbus_code = wut_enum_mbus_code,
	.enum_fwame_size = wut_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = wut_set_fowmat,
};

static const stwuct v4w2_subdev_ops wut_ops = {
	.pad    = &wut_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void wut_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_wut *wut = to_wut(&entity->subdev);

	vsp1_wut_wwite(wut, dwb, VI6_WUT_CTWW, VI6_WUT_CTWW_EN);
}

static void wut_configuwe_fwame(stwuct vsp1_entity *entity,
				stwuct vsp1_pipewine *pipe,
				stwuct vsp1_dw_wist *dw,
				stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_wut *wut = to_wut(&entity->subdev);
	stwuct vsp1_dw_body *wut_dwb;
	unsigned wong fwags;

	spin_wock_iwqsave(&wut->wock, fwags);
	wut_dwb = wut->wut;
	wut->wut = NUWW;
	spin_unwock_iwqwestowe(&wut->wock, fwags);

	if (wut_dwb) {
		vsp1_dw_wist_add_body(dw, wut_dwb);

		/* Wewease ouw wocaw wefewence. */
		vsp1_dw_body_put(wut_dwb);
	}
}

static void wut_destwoy(stwuct vsp1_entity *entity)
{
	stwuct vsp1_wut *wut = to_wut(&entity->subdev);

	vsp1_dw_body_poow_destwoy(wut->poow);
}

static const stwuct vsp1_entity_opewations wut_entity_ops = {
	.configuwe_stweam = wut_configuwe_stweam,
	.configuwe_fwame = wut_configuwe_fwame,
	.destwoy = wut_destwoy,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_wut *vsp1_wut_cweate(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_wut *wut;
	int wet;

	wut = devm_kzawwoc(vsp1->dev, sizeof(*wut), GFP_KEWNEW);
	if (wut == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&wut->wock);

	wut->entity.ops = &wut_entity_ops;
	wut->entity.type = VSP1_ENTITY_WUT;

	wet = vsp1_entity_init(vsp1, &wut->entity, "wut", 2, &wut_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_WUT);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	/*
	 * Pwe-awwocate a body poow, with 3 bodies awwowing a usewspace update
	 * befowe the hawdwawe has committed a pwevious set of tabwes, handwing
	 * both the queued and pending dw entwies.
	 */
	wut->poow = vsp1_dw_body_poow_cweate(vsp1, 3, WUT_SIZE, 0);
	if (!wut->poow)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the contwow handwew. */
	v4w2_ctww_handwew_init(&wut->ctwws, 1);
	v4w2_ctww_new_custom(&wut->ctwws, &wut_tabwe_contwow, NUWW);

	wut->entity.subdev.ctww_handwew = &wut->ctwws;

	if (wut->ctwws.ewwow) {
		dev_eww(vsp1->dev, "wut: faiwed to initiawize contwows\n");
		wet = wut->ctwws.ewwow;
		vsp1_entity_destwoy(&wut->entity);
		wetuwn EWW_PTW(wet);
	}

	v4w2_ctww_handwew_setup(&wut->ctwws);

	wetuwn wut;
}
