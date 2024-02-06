// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_wif.c  --  W-Caw VSP1 WCD Contwowwew Intewface
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_wif.h"

#define WIF_MIN_SIZE				2U
#define WIF_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_wif_wwite(stwuct vsp1_wif *wif,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg + wif->entity.index * VI6_WIF_OFFSET,
			       data);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static const unsigned int wif_codes[] = {
	MEDIA_BUS_FMT_AWGB8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
};

static int wif_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	wetuwn vsp1_subdev_enum_mbus_code(subdev, sd_state, code, wif_codes,
					  AWWAY_SIZE(wif_codes));
}

static int wif_enum_fwame_size(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fwame_size_enum *fse)
{
	wetuwn vsp1_subdev_enum_fwame_size(subdev, sd_state, fse,
					   WIF_MIN_SIZE,
					   WIF_MIN_SIZE, WIF_MAX_SIZE,
					   WIF_MAX_SIZE);
}

static int wif_set_fowmat(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	wetuwn vsp1_subdev_set_pad_fowmat(subdev, sd_state, fmt, wif_codes,
					  AWWAY_SIZE(wif_codes),
					  WIF_MIN_SIZE, WIF_MIN_SIZE,
					  WIF_MAX_SIZE, WIF_MAX_SIZE);
}

static const stwuct v4w2_subdev_pad_ops wif_pad_ops = {
	.enum_mbus_code = wif_enum_mbus_code,
	.enum_fwame_size = wif_enum_fwame_size,
	.get_fmt = vsp1_subdev_get_pad_fowmat,
	.set_fmt = wif_set_fowmat,
};

static const stwuct v4w2_subdev_ops wif_ops = {
	.pad    = &wif_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void wif_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct vsp1_wif *wif = to_wif(&entity->subdev);
	unsigned int hbth;
	unsigned int obth;
	unsigned int wbth;

	fowmat = vsp1_entity_get_pad_fowmat(&wif->entity, wif->entity.state,
					    WIF_PAD_SOUWCE);

	switch (entity->vsp1->vewsion & VI6_IP_VEWSION_MODEW_MASK) {
	case VI6_IP_VEWSION_MODEW_VSPD_GEN2:
	case VI6_IP_VEWSION_MODEW_VSPD_V2H:
		hbth = 1536;
		obth = min(128U, (fowmat->width + 1) / 2 * fowmat->height - 4);
		wbth = 1520;
		bweak;

	case VI6_IP_VEWSION_MODEW_VSPDW_GEN3:
	case VI6_IP_VEWSION_MODEW_VSPD_V3:
	case VI6_IP_VEWSION_MODEW_VSPD_WZG2W:
		hbth = 0;
		obth = 1500;
		wbth = 0;
		bweak;

	case VI6_IP_VEWSION_MODEW_VSPD_GEN3:
	case VI6_IP_VEWSION_MODEW_VSPD_GEN4:
	defauwt:
		hbth = 0;
		obth = 3000;
		wbth = 0;
		bweak;
	}

	vsp1_wif_wwite(wif, dwb, VI6_WIF_CSBTH,
			(hbth << VI6_WIF_CSBTH_HBTH_SHIFT) |
			(wbth << VI6_WIF_CSBTH_WBTH_SHIFT));

	vsp1_wif_wwite(wif, dwb, VI6_WIF_CTWW,
			(obth << VI6_WIF_CTWW_OBTH_SHIFT) |
			(fowmat->code == 0 ? VI6_WIF_CTWW_CFMT : 0) |
			VI6_WIF_CTWW_WEQSEW | VI6_WIF_CTWW_WIF_EN);

	/*
	 * On W-Caw V3M and WZ/G2W the WIF0 buffew attwibute wegistew has to be
	 * set to a non-defauwt vawue to guawantee pwopew opewation (othewwise
	 * awtifacts may appeaw on the output). The vawue wequiwed by the
	 * manuaw is not expwained but is wikewy a buffew size ow thweshowd.
	 */
	if (vsp1_featuwe(entity->vsp1, VSP1_HAS_NON_ZEWO_WBA))
		vsp1_wif_wwite(wif, dwb, VI6_WIF_WBA,
			       VI6_WIF_WBA_WBA0 |
			       (1536 << VI6_WIF_WBA_WBA1_SHIFT));
}

static const stwuct vsp1_entity_opewations wif_entity_ops = {
	.configuwe_stweam = wif_configuwe_stweam,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_wif *vsp1_wif_cweate(stwuct vsp1_device *vsp1, unsigned int index)
{
	stwuct vsp1_wif *wif;
	int wet;

	wif = devm_kzawwoc(vsp1->dev, sizeof(*wif), GFP_KEWNEW);
	if (wif == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	wif->entity.ops = &wif_entity_ops;
	wif->entity.type = VSP1_ENTITY_WIF;
	wif->entity.index = index;

	/*
	 * The WIF is nevew exposed to usewspace, but media entity wegistwation
	 * wequiwes a function to be set. Use PWOC_VIDEO_PIXEW_FOWMATTEW just to
	 * avoid twiggewing a WAWN_ON(), the vawue won't be seen anywhewe.
	 */
	wet = vsp1_entity_init(vsp1, &wif->entity, "wif", 2, &wif_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn wif;
}
