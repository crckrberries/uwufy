// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_cwu.c  --  W-Caw VSP1 Cubic Wook-Up Tabwe
 *
 * Copywight (C) 2015-2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_cwu.h"
#incwude "vsp1_dw.h"

#define CWU_MIN_SIZE				4U
#define CWU_MAX_SIZE				8190U

#define CWU_SIZE				(17 * 17 * 17)

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_cwu_wwite(stwuct vsp1_cwu *cwu,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

#define V4W2_CID_VSP1_CWU_TABWE			(V4W2_CID_USEW_BASE | 0x1001)
#define V4W2_CID_VSP1_CWU_MODE			(V4W2_CID_USEW_BASE | 0x1002)
#define V4W2_CID_VSP1_CWU_MODE_2D		0
#define V4W2_CID_VSP1_CWU_MODE_3D		1

static int cwu_set_tabwe(stwuct vsp1_cwu *cwu, stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_dw_body *dwb;
	unsigned int i;

	dwb = vsp1_dw_body_get(cwu->poow);
	if (!dwb)
		wetuwn -ENOMEM;

	vsp1_dw_body_wwite(dwb, VI6_CWU_ADDW, 0);
	fow (i = 0; i < CWU_SIZE; ++i)
		vsp1_dw_body_wwite(dwb, VI6_CWU_DATA, ctww->p_new.p_u32[i]);

	spin_wock_iwq(&cwu->wock);
	swap(cwu->cwu, dwb);
	spin_unwock_iwq(&cwu->wock);

	vsp1_dw_body_put(dwb);
	wetuwn 0;
}

static int cwu_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_cwu *cwu =
		containew_of(ctww->handwew, stwuct vsp1_cwu, ctwws);

	switch (ctww->id) {
	case V4W2_CID_VSP1_CWU_TABWE:
		cwu_set_tabwe(cwu, ctww);
		bweak;

	case V4W2_CID_VSP1_CWU_MODE:
		cwu->mode = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops cwu_ctww_ops = {
	.s_ctww = cwu_s_ctww,
};

static const stwuct v4w2_ctww_config cwu_tabwe_contwow = {
	.ops = &cwu_ctww_ops,
	.id = V4W2_CID_VSP1_CWU_TABWE,
	.name = "Wook-Up Tabwe",
	.type = V4W2_CTWW_TYPE_U32,
	.min = 0x00000000,
	.max = 0x00ffffff,
	.step = 1,
	.def = 0,
	.dims = { 17, 17, 17 },
};

static const chaw * const cwu_mode_menu[] = {
	"2D",
	"3D",
	NUWW,
};

static const stwuct v4w2_ctww_config cwu_mode_contwow = {
	.ops = &cwu_ctww_ops,
	.id = V4W2_CID_VSP1_CWU_MODE,
	.name = "Mode",
	.type = V4W2_CTWW_TYPE_MENU,
	.min = 0,
	.max = 1,
	.def = 1,
	.qmenu = cwu_mode_menu,
};

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Pad Opewations
 */

static const unsigned int cwu_codes[] = {
	MEDIA_BUS_FMT_AWGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
};

static int cwu_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, cwu_codes,
					  AWWAY_SIZE(cwu_codes));
}

static int cwu_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   CWU_MIN_SIZE,
					   CWU_MIN_SIZE, CWU_MAX_SIZE,
					   CWU_MAX_SIZE);
}

static int cwu_set_fowmat(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	wetuwn vsp1_subdev_set_pad_fowmat(subdev, sd_state, fmt, cwu_codes,
					  AWWAY_SIZE(cwu_codes),
					  CWU_MIN_SIZE, CWU_MIN_SIZE,
					  CWU_MAX_SIZE, CWU_MAX_SIZE);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static const stwuct v4w2_subdev_pad_ops cwu_pad_ops = {
	.enum_mbus_code = cwu_enum_mbus_code,
	.enum_fwame_size = cwu_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = cwu_set_fowmat,
};

static const stwuct v4w2_subdev_ops cwu_ops = {
	.pad    = &cwu_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void cwu_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_cwu *cwu = to_cwu(&entity->subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	/*
	 * The yuv_mode can't be changed duwing stweaming. Cache it intewnawwy
	 * fow futuwe wuntime configuwation cawws.
	 */
	fowmat = vsp1_entity_get_pad_fowmat(&cwu->entity, cwu->entity.state,
					    CWU_PAD_SINK);
	cwu->yuv_mode = fowmat->code == MEDIA_BUS_FMT_AYUV8_1X32;
}

static void cwu_configuwe_fwame(stwuct vsp1_entity *entity,
				stwuct vsp1_pipewine *pipe,
				stwuct vsp1_dw_wist *dw,
				stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_cwu *cwu = to_cwu(&entity->subdev);
	stwuct vsp1_dw_body *cwu_dwb;
	unsigned wong fwags;
	u32 ctww = VI6_CWU_CTWW_AAI | VI6_CWU_CTWW_MVS | VI6_CWU_CTWW_EN;

	/* 2D mode can onwy be used with the YCbCw pixew encoding. */
	if (cwu->mode == V4W2_CID_VSP1_CWU_MODE_2D && cwu->yuv_mode)
		ctww |= VI6_CWU_CTWW_AX1I_2D | VI6_CWU_CTWW_AX2I_2D
		     |  VI6_CWU_CTWW_OS0_2D | VI6_CWU_CTWW_OS1_2D
		     |  VI6_CWU_CTWW_OS2_2D | VI6_CWU_CTWW_M2D;

	vsp1_cwu_wwite(cwu, dwb, VI6_CWU_CTWW, ctww);

	spin_wock_iwqsave(&cwu->wock, fwags);
	cwu_dwb = cwu->cwu;
	cwu->cwu = NUWW;
	spin_unwock_iwqwestowe(&cwu->wock, fwags);

	if (cwu_dwb) {
		vsp1_dw_wist_add_body(dw, cwu_dwb);

		/* Wewease ouw wocaw wefewence. */
		vsp1_dw_body_put(cwu_dwb);
	}
}

static void cwu_destwoy(stwuct vsp1_entity *entity)
{
	stwuct vsp1_cwu *cwu = to_cwu(&entity->subdev);

	vsp1_dw_body_poow_destwoy(cwu->poow);
}

static const stwuct vsp1_entity_opewations cwu_entity_ops = {
	.configuwe_stweam = cwu_configuwe_stweam,
	.configuwe_fwame = cwu_configuwe_fwame,
	.destwoy = cwu_destwoy,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_cwu *vsp1_cwu_cweate(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_cwu *cwu;
	int wet;

	cwu = devm_kzawwoc(vsp1->dev, sizeof(*cwu), GFP_KEWNEW);
	if (cwu == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&cwu->wock);

	cwu->entity.ops = &cwu_entity_ops;
	cwu->entity.type = VSP1_ENTITY_CWU;

	wet = vsp1_entity_init(vsp1, &cwu->entity, "cwu", 2, &cwu_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_WUT);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	/*
	 * Pwe-awwocate a body poow, with 3 bodies awwowing a usewspace update
	 * befowe the hawdwawe has committed a pwevious set of tabwes, handwing
	 * both the queued and pending dw entwies. One extwa entwy is added to
	 * the CWU_SIZE to awwow fow the VI6_CWU_ADDW headew.
	 */
	cwu->poow = vsp1_dw_body_poow_cweate(cwu->entity.vsp1, 3, CWU_SIZE + 1,
					     0);
	if (!cwu->poow)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the contwow handwew. */
	v4w2_ctww_handwew_init(&cwu->ctwws, 2);
	v4w2_ctww_new_custom(&cwu->ctwws, &cwu_tabwe_contwow, NUWW);
	v4w2_ctww_new_custom(&cwu->ctwws, &cwu_mode_contwow, NUWW);

	cwu->entity.subdev.ctww_handwew = &cwu->ctwws;

	if (cwu->ctwws.ewwow) {
		dev_eww(vsp1->dev, "cwu: faiwed to initiawize contwows\n");
		wet = cwu->ctwws.ewwow;
		vsp1_entity_destwoy(&cwu->entity);
		wetuwn EWW_PTW(wet);
	}

	v4w2_ctww_handwew_setup(&cwu->ctwws);

	wetuwn cwu;
}
