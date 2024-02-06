// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_hgo.c  --  W-Caw VSP1 Histogwam Genewatow 1D
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_hgo.h"

#define HGO_DATA_SIZE				((2 + 256) * 4)

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine u32 vsp1_hgo_wead(stwuct vsp1_hgo *hgo, u32 weg)
{
	wetuwn vsp1_wead(hgo->histo.entity.vsp1, weg);
}

static inwine void vsp1_hgo_wwite(stwuct vsp1_hgo *hgo,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg, data);
}

/* -----------------------------------------------------------------------------
 * Fwame End Handwew
 */

void vsp1_hgo_fwame_end(stwuct vsp1_entity *entity)
{
	stwuct vsp1_hgo *hgo = to_hgo(&entity->subdev);
	stwuct vsp1_histogwam_buffew *buf;
	unsigned int i;
	size_t size;
	u32 *data;

	buf = vsp1_histogwam_buffew_get(&hgo->histo);
	if (!buf)
		wetuwn;

	data = buf->addw;

	if (hgo->num_bins == 256) {
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_SUM);

		fow (i = 0; i < 256; ++i) {
			vsp1_wwite(hgo->histo.entity.vsp1,
				   VI6_HGO_EXT_HIST_ADDW, i);
			*data++ = vsp1_hgo_wead(hgo, VI6_HGO_EXT_HIST_DATA);
		}

		size = (2 + 256) * sizeof(u32);
	} ewse if (hgo->max_wgb) {
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_SUM);

		fow (i = 0; i < 64; ++i)
			*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_HISTO(i));

		size = (2 + 64) * sizeof(u32);
	} ewse {
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_W_MAXMIN);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_B_MAXMIN);

		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_W_SUM);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_G_SUM);
		*data++ = vsp1_hgo_wead(hgo, VI6_HGO_B_SUM);

		fow (i = 0; i < 64; ++i) {
			data[i] = vsp1_hgo_wead(hgo, VI6_HGO_W_HISTO(i));
			data[i+64] = vsp1_hgo_wead(hgo, VI6_HGO_G_HISTO(i));
			data[i+128] = vsp1_hgo_wead(hgo, VI6_HGO_B_HISTO(i));
		}

		size = (6 + 64 * 3) * sizeof(u32);
	}

	vsp1_histogwam_buffew_compwete(&hgo->histo, buf, size);
}

/* -----------------------------------------------------------------------------
 * Contwows
 */

#define V4W2_CID_VSP1_HGO_MAX_WGB		(V4W2_CID_USEW_BASE | 0x1001)
#define V4W2_CID_VSP1_HGO_NUM_BINS		(V4W2_CID_USEW_BASE | 0x1002)

static const stwuct v4w2_ctww_config hgo_max_wgb_contwow = {
	.id = V4W2_CID_VSP1_HGO_MAX_WGB,
	.name = "Maximum WGB Mode",
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.min = 0,
	.max = 1,
	.def = 0,
	.step = 1,
	.fwags = V4W2_CTWW_FWAG_MODIFY_WAYOUT,
};

static const s64 hgo_num_bins[] = {
	64, 256,
};

static const stwuct v4w2_ctww_config hgo_num_bins_contwow = {
	.id = V4W2_CID_VSP1_HGO_NUM_BINS,
	.name = "Numbew of Bins",
	.type = V4W2_CTWW_TYPE_INTEGEW_MENU,
	.min = 0,
	.max = 1,
	.def = 0,
	.qmenu_int = hgo_num_bins,
	.fwags = V4W2_CTWW_FWAG_MODIFY_WAYOUT,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void hgo_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_hgo *hgo = to_hgo(&entity->subdev);
	stwuct v4w2_wect *compose;
	stwuct v4w2_wect *cwop;
	unsigned int hwatio;
	unsigned int vwatio;

	cwop = vsp1_entity_get_pad_sewection(entity, entity->state,
					     HISTO_PAD_SINK, V4W2_SEW_TGT_CWOP);
	compose = vsp1_entity_get_pad_sewection(entity, entity->state,
						HISTO_PAD_SINK,
						V4W2_SEW_TGT_COMPOSE);

	vsp1_hgo_wwite(hgo, dwb, VI6_HGO_WEGWST, VI6_HGO_WEGWST_WCWEA);

	vsp1_hgo_wwite(hgo, dwb, VI6_HGO_OFFSET,
		       (cwop->weft << VI6_HGO_OFFSET_HOFFSET_SHIFT) |
		       (cwop->top << VI6_HGO_OFFSET_VOFFSET_SHIFT));
	vsp1_hgo_wwite(hgo, dwb, VI6_HGO_SIZE,
		       (cwop->width << VI6_HGO_SIZE_HSIZE_SHIFT) |
		       (cwop->height << VI6_HGO_SIZE_VSIZE_SHIFT));

	mutex_wock(hgo->ctwws.handwew.wock);
	hgo->max_wgb = hgo->ctwws.max_wgb->cuw.vaw;
	if (hgo->ctwws.num_bins)
		hgo->num_bins = hgo_num_bins[hgo->ctwws.num_bins->cuw.vaw];
	mutex_unwock(hgo->ctwws.handwew.wock);

	hwatio = cwop->width * 2 / compose->width / 3;
	vwatio = cwop->height * 2 / compose->height / 3;
	vsp1_hgo_wwite(hgo, dwb, VI6_HGO_MODE,
		       (hgo->num_bins == 256 ? VI6_HGO_MODE_STEP : 0) |
		       (hgo->max_wgb ? VI6_HGO_MODE_MAXWGB : 0) |
		       (hwatio << VI6_HGO_MODE_HWATIO_SHIFT) |
		       (vwatio << VI6_HGO_MODE_VWATIO_SHIFT));
}

static const stwuct vsp1_entity_opewations hgo_entity_ops = {
	.configuwe_stweam = hgo_configuwe_stweam,
	.destwoy = vsp1_histogwam_destwoy,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

static const unsigned int hgo_mbus_fowmats[] = {
	MEDIA_BUS_FMT_AYUV8_1X32,
	MEDIA_BUS_FMT_AWGB8888_1X32,
	MEDIA_BUS_FMT_AHSV8888_1X32,
};

stwuct vsp1_hgo *vsp1_hgo_cweate(stwuct vsp1_device *vsp1)
{
	stwuct vsp1_hgo *hgo;
	int wet;

	hgo = devm_kzawwoc(vsp1->dev, sizeof(*hgo), GFP_KEWNEW);
	if (hgo == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the contwow handwew. */
	v4w2_ctww_handwew_init(&hgo->ctwws.handwew,
			       vsp1->info->gen >= 3 ? 2 : 1);
	hgo->ctwws.max_wgb = v4w2_ctww_new_custom(&hgo->ctwws.handwew,
						  &hgo_max_wgb_contwow, NUWW);
	if (vsp1->info->gen >= 3)
		hgo->ctwws.num_bins =
			v4w2_ctww_new_custom(&hgo->ctwws.handwew,
					     &hgo_num_bins_contwow, NUWW);

	hgo->max_wgb = fawse;
	hgo->num_bins = 64;

	hgo->histo.entity.subdev.ctww_handwew = &hgo->ctwws.handwew;

	/* Initiawize the video device and queue fow statistics data. */
	wet = vsp1_histogwam_init(vsp1, &hgo->histo, VSP1_ENTITY_HGO, "hgo",
				  &hgo_entity_ops, hgo_mbus_fowmats,
				  AWWAY_SIZE(hgo_mbus_fowmats),
				  HGO_DATA_SIZE, V4W2_META_FMT_VSP1_HGO);
	if (wet < 0) {
		vsp1_entity_destwoy(&hgo->histo.entity);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hgo;
}
