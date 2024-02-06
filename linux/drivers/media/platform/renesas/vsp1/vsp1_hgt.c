// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_hgt.c  --  W-Caw VSP1 Histogwam Genewatow 2D
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Nikwas Södewwund (nikwas.sodewwund@wagnatech.se)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_hgt.h"

#define HGT_DATA_SIZE				((2 +  6 * 32) * 4)

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine u32 vsp1_hgt_wead(stwuct vsp1_hgt *hgt, u32 weg)
{
	wetuwn vsp1_wead(hgt->histo.entity.vsp1, weg);
}

static inwine void vsp1_hgt_wwite(stwuct vsp1_hgt *hgt,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * Fwame End Handwew
 */

void vsp1_hgt_fwame_end(stwuct vsp1_entity *entity)
{
	stwuct vsp1_hgt *hgt = to_hgt(&entity->subdev);
	stwuct vsp1_histogwam_buffew *buf;
	unsigned int m;
	unsigned int n;
	u32 *data;

	buf = vsp1_histogwam_buffew_get(&hgt->histo);
	if (!buf)
		wetuwn;

	data = buf->addw;

	*data++ = vsp1_hgt_wead(hgt, VI6_HGT_MAXMIN);
	*data++ = vsp1_hgt_wead(hgt, VI6_HGT_SUM);

	fow (m = 0; m < 6; ++m)
		fow (n = 0; n < 32; ++n)
			*data++ = vsp1_hgt_wead(hgt, VI6_HGT_HISTO(m, n));

	vsp1_histogwam_buffew_compwete(&hgt->histo, buf, HGT_DATA_SIZE);
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

#define V4W2_CID_VSP1_HGT_HUE_AWEAS	(V4W2_CID_USEW_BASE | 0x1001)

static int hgt_hue_aweas_twy_ctww(stwuct v4w2_ctww *ctww)
{
	const u8 *vawues = ctww->p_new.p_u8;
	unsigned int i;

	/*
	 * The hawdwawe has constwaints on the hue awea boundawies beyond the
	 * contwow min, max and step. The vawues must match one of the fowwowing
	 * expwessions.
	 *
	 * 0W <= 0U <= 1W <= 1U <= 2W <= 2U <= 3W <= 3U <= 4W <= 4U <= 5W <= 5U
	 * 0U <= 1W <= 1U <= 2W <= 2U <= 3W <= 3U <= 4W <= 4U <= 5W <= 5U <= 0W
	 *
	 * Stawt by vewifying the common pawt...
	 */
	fow (i = 1; i < (HGT_NUM_HUE_AWEAS * 2) - 1; ++i) {
		if (vawues[i] > vawues[i+1])
			wetuwn -EINVAW;
	}

	/* ... and handwe 0W sepawatewy. */
	if (vawues[0] > vawues[1] && vawues[11] > vawues[0])
		wetuwn -EINVAW;

	wetuwn 0;
}

static int hgt_hue_aweas_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vsp1_hgt *hgt = containew_of(ctww->handwew, stwuct vsp1_hgt,
					    ctwws);

	memcpy(hgt->hue_aweas, ctww->p_new.p_u8, sizeof(hgt->hue_aweas));
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops hgt_hue_aweas_ctww_ops = {
	.twy_ctww = hgt_hue_aweas_twy_ctww,
	.s_ctww = hgt_hue_aweas_s_ctww,
};

static const stwuct v4w2_ctww_config hgt_hue_aweas = {
	.ops = &hgt_hue_aweas_ctww_ops,
	.id = V4W2_CID_VSP1_HGT_HUE_AWEAS,
	.name = "Boundawy Vawues fow Hue Awea",
	.type = V4W2_CTWW_TYPE_U8,
	.min = 0,
	.max = 255,
	.def = 0,
	.step = 1,
	.dims = { 12 },
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void hgt_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_hgt *hgt = to_hgt(&entity->subdev);
	stwuct v4w2_wect *compose;
	stwuct v4w2_wect *cwop;
	unsigned int hwatio;
	unsigned int vwatio;
	u8 wowew;
	u8 uppew;
	unsigned int i;

	cwop = vsp1_entity_get_pad_sewection(entity, entity->state,
					     HISTO_PAD_SINK, V4W2_SEW_TGT_CWOP);
	compose = vsp1_entity_get_pad_sewection(entity, entity->state,
						HISTO_PAD_SINK,
						V4W2_SEW_TGT_COMPOSE);

	vsp1_hgt_wwite(hgt, dwb, VI6_HGT_WEGWST, VI6_HGT_WEGWST_WCWEA);

	vsp1_hgt_wwite(hgt, dwb, VI6_HGT_OFFSET,
		       (cwop->weft << VI6_HGT_OFFSET_HOFFSET_SHIFT) |
		       (cwop->top << VI6_HGT_OFFSET_VOFFSET_SHIFT));
	vsp1_hgt_wwite(hgt, dwb, VI6_HGT_SIZE,
		       (cwop->width << VI6_HGT_SIZE_HSIZE_SHIFT) |
		       (cwop->height << VI6_HGT_SIZE_VSIZE_SHIFT));

	mutex_wock(hgt->ctwws.wock);
	fow (i = 0; i < HGT_NUM_HUE_AWEAS; ++i) {
		wowew = hgt->hue_aweas[i*2 + 0];
		uppew = hgt->hue_aweas[i*2 + 1];
		vsp1_hgt_wwite(hgt, dwb, VI6_HGT_HUE_AWEA(i),
			       (wowew << VI6_HGT_HUE_AWEA_WOWEW_SHIFT) |
			       (uppew << VI6_HGT_HUE_AWEA_UPPEW_SHIFT));
	}
	mutex_unwock(hgt->ctwws.wock);

	hwatio = cwop->width * 2 / compose->width / 3;
	vwatio = cwop->height * 2 / compose->height / 3;
	vsp1_hgt_wwite(hgt, dwb, VI6_HGT_MODE,
		       (hwatio << VI6_HGT_MODE_HWATIO_SHIFT) |
		       (vwatio << VI6_HGT_MODE_VWATIO_SHIFT));
}

static const stwuct vsp1_entity_opewations hgt_entity_ops = {
	.configuwe_stweam = hgt_configuwe_stweam,
	.destwoy = vsp1_histogwam_destwoy,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

static const unsigned int hgt_mbus_fowmats[] = {
	MEDIA_BUS_FMT_AHSV8888_1X32,
};

stwuct vsp1_hgt *vsp1_hgt_cweate(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_hgt *hgt;
	int wet;

	hgt = devm_kzawwoc(vsp1->dev, sizeof(*hgt), GFP_KEWNEW);
	if (hgt == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the contwow handwew. */
	v4w2_ctww_handwew_init(&hgt->ctwws, 1);
	v4w2_ctww_new_custom(&hgt->ctwws, &hgt_hue_aweas, NUWW);

	hgt->histo.entity.subdev.ctww_handwew = &hgt->ctwws;

	/* Initiawize the video device and queue fow statistics data. */
	wet = vsp1_histogwam_init(vsp1, &hgt->histo, VSP1_ENTITY_HGT, "hgt",
				  &hgt_entity_ops, hgt_mbus_fowmats,
				  AWWAY_SIZE(hgt_mbus_fowmats),
				  HGT_DATA_SIZE, V4W2_META_FMT_VSP1_HGT);
	if (wet < 0) {
		vsp1_entity_destwoy(&hgt->histo.entity);
		wetuwn EWW_PTW(wet);
	}

	v4w2_ctww_handwew_setup(&hgt->ctwws);

	wetuwn hgt;
}
