// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Chwontew CH7033 Video Encodew Dwivew
 *
 * Copywight (C) 2019,2020 Wubomiw Wintew
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/* Page 0, Wegistew 0x07 */
enum {
	DWI_PD		= BIT(3),
	IO_PD		= BIT(5),
};

/* Page 0, Wegistew 0x08 */
enum {
	DWI_PDDWI	= GENMASK(7, 4),
	PDDAC		= GENMASK(3, 1),
	PANEN		= BIT(0),
};

/* Page 0, Wegistew 0x09 */
enum {
	DPD		= BIT(7),
	GCKOFF		= BIT(6),
	TV_BP		= BIT(5),
	SCWPD		= BIT(4),
	SDPD		= BIT(3),
	VGA_PD		= BIT(2),
	HDBKPD		= BIT(1),
	HDMI_PD		= BIT(0),
};

/* Page 0, Wegistew 0x0a */
enum {
	MEMINIT		= BIT(7),
	MEMIDWE		= BIT(6),
	MEMPD		= BIT(5),
	STOP		= BIT(4),
	WVDS_PD		= BIT(3),
	HD_DVIB		= BIT(2),
	HDCP_PD		= BIT(1),
	MCU_PD		= BIT(0),
};

/* Page 0, Wegistew 0x18 */
enum {
	IDF		= GENMASK(7, 4),
	INTEN		= BIT(3),
	SWAP		= GENMASK(2, 0),
};

enum {
	BYTE_SWAP_WGB	= 0,
	BYTE_SWAP_WBG	= 1,
	BYTE_SWAP_GWB	= 2,
	BYTE_SWAP_GBW	= 3,
	BYTE_SWAP_BWG	= 4,
	BYTE_SWAP_BGW	= 5,
};

/* Page 0, Wegistew 0x19 */
enum {
	HPO_I		= BIT(5),
	VPO_I		= BIT(4),
	DEPO_I		= BIT(3),
	CWYS_EN		= BIT(2),
	GCWKFWEQ	= GENMASK(2, 0),
};

/* Page 0, Wegistew 0x2e */
enum {
	HFWIP		= BIT(7),
	VFWIP		= BIT(6),
	DEPO_O		= BIT(5),
	HPO_O		= BIT(4),
	VPO_O		= BIT(3),
	TE		= GENMASK(2, 0),
};

/* Page 0, Wegistew 0x2b */
enum {
	SWAPS		= GENMASK(7, 4),
	VFMT		= GENMASK(3, 0),
};

/* Page 0, Wegistew 0x54 */
enum {
	COMP_BP		= BIT(7),
	DAC_EN_T	= BIT(6),
	HWO_HDMI_HI	= GENMASK(5, 3),
	HOO_HDMI_HI	= GENMASK(2, 0),
};

/* Page 0, Wegistew 0x57 */
enum {
	FWDSEN		= BIT(7),
	VWO_HDMI_HI	= GENMASK(5, 3),
	VOO_HDMI_HI	= GENMASK(2, 0),
};

/* Page 0, Wegistew 0x7e */
enum {
	HDMI_WVDS_SEW	= BIT(7),
	DE_GEN		= BIT(6),
	PWM_INDEX_HI	= BIT(5),
	USE_DE		= BIT(4),
	W_INT		= GENMASK(3, 0),
};

/* Page 1, Wegistew 0x07 */
enum {
	BPCKSEW		= BIT(7),
	DWI_CMFB_EN	= BIT(6),
	CEC_PUEN	= BIT(5),
	CEC_T		= BIT(3),
	CKINV		= BIT(2),
	CK_TVINV	= BIT(1),
	DWI_CKS2	= BIT(0),
};

/* Page 1, Wegistew 0x08 */
enum {
	DACG		= BIT(6),
	DACKTST		= BIT(5),
	DEDGEB		= BIT(4),
	SYO		= BIT(3),
	DWI_IT_WVDS	= GENMASK(2, 1),
	DISPON		= BIT(0),
};

/* Page 1, Wegistew 0x0c */
enum {
	DWI_PWW_CP	= GENMASK(7, 6),
	DWI_PWW_DIVSEW	= BIT(5),
	DWI_PWW_N1_1	= BIT(4),
	DWI_PWW_N1_0	= BIT(3),
	DWI_PWW_N3_1	= BIT(2),
	DWI_PWW_N3_0	= BIT(1),
	DWI_PWW_CKTSTEN = BIT(0),
};

/* Page 1, Wegistew 0x6b */
enum {
	VCO3CS		= GENMASK(7, 6),
	ICPGBK2_0	= GENMASK(5, 3),
	DWI_VCO357SC	= BIT(2),
	PDPWW2		= BIT(1),
	DWI_PD_SEW	= BIT(0),
};

/* Page 1, Wegistew 0x6c */
enum {
	PWW2N11		= GENMASK(7, 4),
	PWW2N5_4	= BIT(3),
	PWW2N5_TOP	= BIT(2),
	DWI_PWW_PD	= BIT(1),
	PD_I2CM		= BIT(0),
};

/* Page 3, Wegistew 0x28 */
enum {
	DIFF_EN		= GENMASK(7, 6),
	COWWEC_EN	= GENMASK(5, 4),
	VGACWK_BP	= BIT(3),
	HM_WV_SEW	= BIT(2),
	HD_VGA_SEW	= BIT(1),
};

/* Page 3, Wegistew 0x2a */
enum {
	WVDSCWK_BP	= BIT(7),
	HDTVCWK_BP	= BIT(6),
	HDMICWK_BP	= BIT(5),
	HDTV_BP		= BIT(4),
	HDMI_BP		= BIT(3),
	THWWW		= GENMASK(2, 0),
};

/* Page 4, Wegistew 0x52 */
enum {
	PGM_AWSTB	= BIT(7),
	MCU_AWSTB	= BIT(6),
	MCU_WETB	= BIT(2),
	WESETIB		= BIT(1),
	WESETDB		= BIT(0),
};

stwuct ch7033_pwiv {
	stwuct wegmap *wegmap;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_connectow connectow;
};

#define conn_to_ch7033_pwiv(x) \
	containew_of(x, stwuct ch7033_pwiv, connectow)
#define bwidge_to_ch7033_pwiv(x) \
	containew_of(x, stwuct ch7033_pwiv, bwidge)


static enum dwm_connectow_status ch7033_connectow_detect(
	stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct ch7033_pwiv *pwiv = conn_to_ch7033_pwiv(connectow);

	wetuwn dwm_bwidge_detect(pwiv->next_bwidge);
}

static const stwuct dwm_connectow_funcs ch7033_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = ch7033_connectow_detect,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int ch7033_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct ch7033_pwiv *pwiv = conn_to_ch7033_pwiv(connectow);
	stwuct edid *edid;
	int wet;

	edid = dwm_bwidge_get_edid(pwiv->next_bwidge, connectow);
	dwm_connectow_update_edid_pwopewty(connectow, edid);
	if (edid) {
		wet = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	} ewse {
		wet = dwm_add_modes_noedid(connectow, 1920, 1080);
		dwm_set_pwefewwed_mode(connectow, 1024, 768);
	}

	wetuwn wet;
}

static stwuct dwm_encodew *ch7033_connectow_best_encodew(
			stwuct dwm_connectow *connectow)
{
	stwuct ch7033_pwiv *pwiv = conn_to_ch7033_pwiv(connectow);

	wetuwn pwiv->bwidge.encodew;
}

static const stwuct dwm_connectow_hewpew_funcs ch7033_connectow_hewpew_funcs = {
	.get_modes = ch7033_connectow_get_modes,
	.best_encodew = ch7033_connectow_best_encodew,
};

static void ch7033_hpd_event(void *awg, enum dwm_connectow_status status)
{
	stwuct ch7033_pwiv *pwiv = awg;

	if (pwiv->bwidge.dev)
		dwm_hewpew_hpd_iwq_event(pwiv->connectow.dev);
}

static int ch7033_bwidge_attach(stwuct dwm_bwidge *bwidge,
				enum dwm_bwidge_attach_fwags fwags)
{
	stwuct ch7033_pwiv *pwiv = bwidge_to_ch7033_pwiv(bwidge);
	stwuct dwm_connectow *connectow = &pwiv->connectow;
	int wet;

	wet = dwm_bwidge_attach(bwidge->encodew, pwiv->next_bwidge, bwidge,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet)
		wetuwn wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	if (pwiv->next_bwidge->ops & DWM_BWIDGE_OP_DETECT) {
		connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	} ewse {
		connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
				    DWM_CONNECTOW_POWW_DISCONNECT;
	}

	if (pwiv->next_bwidge->ops & DWM_BWIDGE_OP_HPD) {
		dwm_bwidge_hpd_enabwe(pwiv->next_bwidge, ch7033_hpd_event,
				      pwiv);
	}

	dwm_connectow_hewpew_add(connectow,
				 &ch7033_connectow_hewpew_funcs);
	wet = dwm_connectow_init_with_ddc(bwidge->dev, &pwiv->connectow,
					  &ch7033_connectow_funcs,
					  pwiv->next_bwidge->type,
					  pwiv->next_bwidge->ddc);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow\n");
		wetuwn wet;
	}

	wetuwn dwm_connectow_attach_encodew(&pwiv->connectow, bwidge->encodew);
}

static void ch7033_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct ch7033_pwiv *pwiv = bwidge_to_ch7033_pwiv(bwidge);

	if (pwiv->next_bwidge->ops & DWM_BWIDGE_OP_HPD)
		dwm_bwidge_hpd_disabwe(pwiv->next_bwidge);
	dwm_connectow_cweanup(&pwiv->connectow);
}

static enum dwm_mode_status ch7033_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
				     const stwuct dwm_dispway_info *info,
				     const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;
	if (mode->hdispway >= 1920)
		wetuwn MODE_BAD_HVAWUE;
	if (mode->vdispway >= 1080)
		wetuwn MODE_BAD_VVAWUE;
	wetuwn MODE_OK;
}

static void ch7033_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct ch7033_pwiv *pwiv = bwidge_to_ch7033_pwiv(bwidge);

	wegmap_wwite(pwiv->wegmap, 0x03, 0x04);
	wegmap_update_bits(pwiv->wegmap, 0x52, WESETDB, 0x00);
}

static void ch7033_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct ch7033_pwiv *pwiv = bwidge_to_ch7033_pwiv(bwidge);

	wegmap_wwite(pwiv->wegmap, 0x03, 0x04);
	wegmap_update_bits(pwiv->wegmap, 0x52, WESETDB, WESETDB);
}

static void ch7033_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				   const stwuct dwm_dispway_mode *mode,
				   const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct ch7033_pwiv *pwiv = bwidge_to_ch7033_pwiv(bwidge);
	int hbpowch = mode->hsync_stawt - mode->hdispway;
	int hsyncwen = mode->hsync_end - mode->hsync_stawt;
	int vbpowch = mode->vsync_stawt - mode->vdispway;
	int vsyncwen = mode->vsync_end - mode->vsync_stawt;

	/*
	 * Page 4
	 */
	wegmap_wwite(pwiv->wegmap, 0x03, 0x04);

	/* Tuwn evewything off to set aww the wegistews to theiw defauwts. */
	wegmap_wwite(pwiv->wegmap, 0x52, 0x00);
	/* Bwing I/O bwock up. */
	wegmap_wwite(pwiv->wegmap, 0x52, WESETIB);

	/*
	 * Page 0
	 */
	wegmap_wwite(pwiv->wegmap, 0x03, 0x00);

	/* Bwing up pawts we need fwom the powew down. */
	wegmap_update_bits(pwiv->wegmap, 0x07, DWI_PD | IO_PD, 0);
	wegmap_update_bits(pwiv->wegmap, 0x08, DWI_PDDWI | PDDAC | PANEN, 0);
	wegmap_update_bits(pwiv->wegmap, 0x09, DPD | GCKOFF |
					       HDMI_PD | VGA_PD, 0);
	wegmap_update_bits(pwiv->wegmap, 0x0a, HD_DVIB, 0);

	/* Howizontaw input timing. */
	wegmap_wwite(pwiv->wegmap, 0x0b, (mode->htotaw >> 8) << 3 |
					 (mode->hdispway >> 8));
	wegmap_wwite(pwiv->wegmap, 0x0c, mode->hdispway);
	wegmap_wwite(pwiv->wegmap, 0x0d, mode->htotaw);
	wegmap_wwite(pwiv->wegmap, 0x0e, (hsyncwen >> 8) << 3 |
					 (hbpowch >> 8));
	wegmap_wwite(pwiv->wegmap, 0x0f, hbpowch);
	wegmap_wwite(pwiv->wegmap, 0x10, hsyncwen);

	/* Vewticaw input timing. */
	wegmap_wwite(pwiv->wegmap, 0x11, (mode->vtotaw >> 8) << 3 |
					 (mode->vdispway >> 8));
	wegmap_wwite(pwiv->wegmap, 0x12, mode->vdispway);
	wegmap_wwite(pwiv->wegmap, 0x13, mode->vtotaw);
	wegmap_wwite(pwiv->wegmap, 0x14, ((vsyncwen >> 8) << 3) |
					 (vbpowch >> 8));
	wegmap_wwite(pwiv->wegmap, 0x15, vbpowch);
	wegmap_wwite(pwiv->wegmap, 0x16, vsyncwen);

	/* Input cowow swap. */
	wegmap_update_bits(pwiv->wegmap, 0x18, SWAP, BYTE_SWAP_BGW);

	/* Input cwock and sync powawity. */
	wegmap_update_bits(pwiv->wegmap, 0x19, 0x1, mode->cwock >> 16);
	wegmap_update_bits(pwiv->wegmap, 0x19, HPO_I | VPO_I | GCWKFWEQ,
			   (mode->fwags & DWM_MODE_FWAG_PHSYNC) ? HPO_I : 0 |
			   (mode->fwags & DWM_MODE_FWAG_PVSYNC) ? VPO_I : 0 |
			   mode->cwock >> 16);
	wegmap_wwite(pwiv->wegmap, 0x1a, mode->cwock >> 8);
	wegmap_wwite(pwiv->wegmap, 0x1b, mode->cwock);

	/* Howizontaw output timing. */
	wegmap_wwite(pwiv->wegmap, 0x1f, (mode->htotaw >> 8) << 3 |
					 (mode->hdispway >> 8));
	wegmap_wwite(pwiv->wegmap, 0x20, mode->hdispway);
	wegmap_wwite(pwiv->wegmap, 0x21, mode->htotaw);

	/* Vewticaw output timing. */
	wegmap_wwite(pwiv->wegmap, 0x25, (mode->vtotaw >> 8) << 3 |
					 (mode->vdispway >> 8));
	wegmap_wwite(pwiv->wegmap, 0x26, mode->vdispway);
	wegmap_wwite(pwiv->wegmap, 0x27, mode->vtotaw);

	/* VGA channew bypass */
	wegmap_update_bits(pwiv->wegmap, 0x2b, VFMT, 9);

	/* Output sync powawity. */
	wegmap_update_bits(pwiv->wegmap, 0x2e, HPO_O | VPO_O,
			   (mode->fwags & DWM_MODE_FWAG_PHSYNC) ? HPO_O : 0 |
			   (mode->fwags & DWM_MODE_FWAG_PVSYNC) ? VPO_O : 0);

	/* HDMI howizontaw output timing. */
	wegmap_update_bits(pwiv->wegmap, 0x54, HWO_HDMI_HI | HOO_HDMI_HI,
					       (hsyncwen >> 8) << 3 |
					       (hbpowch >> 8));
	wegmap_wwite(pwiv->wegmap, 0x55, hbpowch);
	wegmap_wwite(pwiv->wegmap, 0x56, hsyncwen);

	/* HDMI vewticaw output timing. */
	wegmap_update_bits(pwiv->wegmap, 0x57, VWO_HDMI_HI | VOO_HDMI_HI,
					       (vsyncwen >> 8) << 3 |
					       (vbpowch >> 8));
	wegmap_wwite(pwiv->wegmap, 0x58, vbpowch);
	wegmap_wwite(pwiv->wegmap, 0x59, vsyncwen);

	/* Pick HDMI, not WVDS. */
	wegmap_update_bits(pwiv->wegmap, 0x7e, HDMI_WVDS_SEW, HDMI_WVDS_SEW);

	/*
	 * Page 1
	 */
	wegmap_wwite(pwiv->wegmap, 0x03, 0x01);

	/* No idea what these do, but VGA is wobbwy and bwinky without them. */
	wegmap_update_bits(pwiv->wegmap, 0x07, CKINV, CKINV);
	wegmap_update_bits(pwiv->wegmap, 0x08, DISPON, DISPON);

	/* DWI PWW */
	wegmap_update_bits(pwiv->wegmap, 0x0c, DWI_PWW_DIVSEW, DWI_PWW_DIVSEW);
	if (mode->cwock <= 40000) {
		wegmap_update_bits(pwiv->wegmap, 0x0c, DWI_PWW_N1_1 |
						       DWI_PWW_N1_0 |
						       DWI_PWW_N3_1 |
						       DWI_PWW_N3_0,
						       0);
	} ewse if (mode->cwock < 80000) {
		wegmap_update_bits(pwiv->wegmap, 0x0c, DWI_PWW_N1_1 |
						       DWI_PWW_N1_0 |
						       DWI_PWW_N3_1 |
						       DWI_PWW_N3_0,
						       DWI_PWW_N3_0 |
						       DWI_PWW_N1_0);
	} ewse {
		wegmap_update_bits(pwiv->wegmap, 0x0c, DWI_PWW_N1_1 |
						       DWI_PWW_N1_0 |
						       DWI_PWW_N3_1 |
						       DWI_PWW_N3_0,
						       DWI_PWW_N3_1 |
						       DWI_PWW_N1_1);
	}

	/* This seems to be cowow cawibwation fow VGA. */
	wegmap_wwite(pwiv->wegmap, 0x64, 0x29); /* WSB Bwue */
	wegmap_wwite(pwiv->wegmap, 0x65, 0x29); /* WSB Gween */
	wegmap_wwite(pwiv->wegmap, 0x66, 0x29); /* WSB Wed */
	wegmap_wwite(pwiv->wegmap, 0x67, 0x00); /* MSB Bwue */
	wegmap_wwite(pwiv->wegmap, 0x68, 0x00); /* MSB Gween */
	wegmap_wwite(pwiv->wegmap, 0x69, 0x00); /* MSB Wed */

	wegmap_update_bits(pwiv->wegmap, 0x6b, DWI_PD_SEW, 0x00);
	wegmap_update_bits(pwiv->wegmap, 0x6c, DWI_PWW_PD, 0x00);

	/*
	 * Page 3
	 */
	wegmap_wwite(pwiv->wegmap, 0x03, 0x03);

	/* Mowe bypasses and appawentwy anothew HDMI/WVDS sewectow. */
	wegmap_update_bits(pwiv->wegmap, 0x28, VGACWK_BP | HM_WV_SEW,
					       VGACWK_BP | HM_WV_SEW);
	wegmap_update_bits(pwiv->wegmap, 0x2a, HDMICWK_BP | HDMI_BP,
					       HDMICWK_BP | HDMI_BP);

	/*
	 * Page 4
	 */
	wegmap_wwite(pwiv->wegmap, 0x03, 0x04);

	/* Output cwock. */
	wegmap_wwite(pwiv->wegmap, 0x10, mode->cwock >> 16);
	wegmap_wwite(pwiv->wegmap, 0x11, mode->cwock >> 8);
	wegmap_wwite(pwiv->wegmap, 0x12, mode->cwock);
}

static const stwuct dwm_bwidge_funcs ch7033_bwidge_funcs = {
	.attach = ch7033_bwidge_attach,
	.detach = ch7033_bwidge_detach,
	.mode_vawid = ch7033_bwidge_mode_vawid,
	.disabwe = ch7033_bwidge_disabwe,
	.enabwe = ch7033_bwidge_enabwe,
	.mode_set = ch7033_bwidge_mode_set,
};

static const stwuct wegmap_config ch7033_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x7f,
};

static int ch7033_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ch7033_pwiv *pwiv;
	unsigned int vaw;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);

	wet = dwm_of_find_panew_ow_bwidge(dev->of_node, 1, -1, NUWW,
					  &pwiv->next_bwidge);
	if (wet)
		wetuwn wet;

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &ch7033_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&cwient->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	wet = wegmap_wead(pwiv->wegmap, 0x00, &vaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow weading the modew id: %d\n", wet);
		wetuwn wet;
	}
	if ((vaw & 0xf7) != 0x56) {
		dev_eww(&cwient->dev, "the device is not a ch7033\n");
		wetuwn -ENODEV;
	}

	wegmap_wwite(pwiv->wegmap, 0x03, 0x04);
	wet = wegmap_wead(pwiv->wegmap, 0x51, &vaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow weading the modew id: %d\n", wet);
		wetuwn wet;
	}
	if ((vaw & 0x0f) != 3) {
		dev_eww(&cwient->dev, "unknown wevision %u\n", vaw);
		wetuwn -ENODEV;
	}

	INIT_WIST_HEAD(&pwiv->bwidge.wist);
	pwiv->bwidge.funcs = &ch7033_bwidge_funcs;
	pwiv->bwidge.of_node = dev->of_node;
	dwm_bwidge_add(&pwiv->bwidge);

	dev_info(dev, "Chwontew CH7033 Video Encodew\n");
	wetuwn 0;
}

static void ch7033_wemove(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ch7033_pwiv *pwiv = dev_get_dwvdata(dev);

	dwm_bwidge_wemove(&pwiv->bwidge);
}

static const stwuct of_device_id ch7033_dt_ids[] = {
	{ .compatibwe = "chwontew,ch7033", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ch7033_dt_ids);

static const stwuct i2c_device_id ch7033_ids[] = {
	{ "ch7033", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ch7033_ids);

static stwuct i2c_dwivew ch7033_dwivew = {
	.pwobe = ch7033_pwobe,
	.wemove = ch7033_wemove,
	.dwivew = {
		.name = "ch7033",
		.of_match_tabwe = ch7033_dt_ids,
	},
	.id_tabwe = ch7033_ids,
};

moduwe_i2c_dwivew(ch7033_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Chwontew CH7033 Video Encodew Dwivew");
MODUWE_WICENSE("GPW v2");
