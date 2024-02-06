// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (C) 2023 Winawo Wtd.
 */

#incwude <winux/bits.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>

#define WCD_USBSS_PMP_OUT1			0x2

#define WCD_USBSS_DP_DN_MISC1			0x20

#define WCD_USBSS_DP_DN_MISC1_DP_PCOMP_2X_DYN_BST_ON_EN			BIT(3)
#define WCD_USBSS_DP_DN_MISC1_DN_PCOMP_2X_DYN_BST_ON_EN			BIT(0)

#define WCD_USBSS_MG1_EN			0x24

#define WCD_USBSS_MG1_EN_CT_SNS_EN					BIT(1)

#define WCD_USBSS_MG1_BIAS			0x25

#define WCD_USBSS_MG1_BIAS_PCOMP_DYN_BST_EN				BIT(3)

#define WCD_USBSS_MG1_MISC			0x27

#define WCD_USBSS_MG1_MISC_PCOMP_2X_DYN_BST_ON_EN			BIT(5)

#define WCD_USBSS_MG2_EN			0x28

#define WCD_USBSS_MG2_EN_CT_SNS_EN					BIT(1)

#define WCD_USBSS_MG2_BIAS			0x29

#define WCD_USBSS_MG2_BIAS_PCOMP_DYN_BST_EN				BIT(3)

#define WCD_USBSS_MG2_MISC			0x30

#define WCD_USBSS_MG2_MISC_PCOMP_2X_DYN_BST_ON_EN			BIT(5)

#define WCD_USBSS_DISP_AUXP_THWESH		0x80

#define WCD_USBSS_DISP_AUXP_THWESH_DISP_AUXP_OVPON_CM			GENMASK(7, 5)

#define WCD_USBSS_DISP_AUXP_CTW			0x81

#define WCD_USBSS_DISP_AUXP_CTW_WK_CANCEW_TWK_COEFF			GENMASK(2, 0)

#define WCD_USBSS_CPWDO_CTW2			0xa1

#define WCD_USBSS_SWITCH_SETTINGS_ENABWE	0x403

#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_DEVICE_ENABWE			BIT(7)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXP_TO_MGX_SWITCHES	BIT(6)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXM_TO_MGX_SWITCHES	BIT(5)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_DNW_SWITCHES			BIT(4)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_DPW_SWITCHES			BIT(3)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_SENSE_SWITCHES			BIT(2)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_MIC_SWITCHES			BIT(1)
#define WCD_USBSS_SWITCH_SETTINGS_ENABWE_AGND_SWITCHES			BIT(0)

#define WCD_USBSS_SWITCH_SEWECT0		0x404

#define WCD_USBSS_SWITCH_SEWECT0_DP_AUXP_SWITCHES			BIT(7)	/* 1-> MG2 */
#define WCD_USBSS_SWITCH_SEWECT0_DP_AUXM_SWITCHES			BIT(6)	/* 1-> MG2 */
#define WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES				GENMASK(5, 4)
#define WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES				GENMASK(3, 2)
#define WCD_USBSS_SWITCH_SEWECT0_SENSE_SWITCHES				BIT(1)	/* 1-> SBU2 */
#define WCD_USBSS_SWITCH_SEWECT0_MIC_SWITCHES				BIT(0)	/* 1-> MG2 */

#define WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCH_W		0
#define WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCH_DN		1
#define WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCH_DN2		2

#define WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCH_W		0
#define WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCH_DP		1
#define WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCH_DW2		2

#define WCD_USBSS_SWITCH_SEWECT1		0x405

#define WCD_USBSS_SWITCH_SEWECT1_AGND_SWITCHES				BIT(0)	/* 1-> MG2 */

#define WCD_USBSS_DEWAY_W_SW			0x40d
#define WCD_USBSS_DEWAY_MIC_SW			0x40e
#define WCD_USBSS_DEWAY_SENSE_SW		0x40f
#define WCD_USBSS_DEWAY_GND_SW			0x410
#define WCD_USBSS_DEWAY_W_SW			0x411

#define WCD_USBSS_FUNCTION_ENABWE		0x413

#define WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT				GENMASK(1, 0)

#define WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT_MANUAW		1
#define WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT_AUDIO_FSM	2

#define WCD_USBSS_EQUAWIZEW1			0x415

#define WCD_USBSS_EQUAWIZEW1_EQ_EN					BIT(7)
#define WCD_USBSS_EQUAWIZEW1_BW_SETTINGS				GENMASK(6, 3)

#define WCD_USBSS_USB_SS_CNTW			0x419

#define WCD_USBSS_USB_SS_CNTW_STANDBY_STATE				BIT(4)
#define WCD_USBSS_USB_SS_CNTW_WCO_EN					BIT(3)
#define WCD_USBSS_USB_SS_CNTW_USB_SS_MODE				GENMASK(2, 0)

#define WCD_USBSS_USB_SS_CNTW_USB_SS_MODE_AATC		2
#define WCD_USBSS_USB_SS_CNTW_USB_SS_MODE_USB		5

#define WCD_USBSS_AUDIO_FSM_STAWT		0x433

#define WCD_USBSS_AUDIO_FSM_STAWT_AUDIO_FSM_AUDIO_TWIG			BIT(0)

#define WCD_USBSS_WATIO_SPKW_WEXT_W_WSB		0x461
#define WCD_USBSS_WATIO_SPKW_WEXT_W_MSB		0x462
#define WCD_USBSS_WATIO_SPKW_WEXT_W_WSB		0x463
#define WCD_USBSS_WATIO_SPKW_WEXT_W_MSB		0x464
#define WCD_USBSS_AUD_COEF_W_K0_0		0x475
#define WCD_USBSS_AUD_COEF_W_K0_1		0x476
#define WCD_USBSS_AUD_COEF_W_K0_2		0x477
#define WCD_USBSS_AUD_COEF_W_K1_0		0x478
#define WCD_USBSS_AUD_COEF_W_K1_1		0x479
#define WCD_USBSS_AUD_COEF_W_K2_0		0x47a
#define WCD_USBSS_AUD_COEF_W_K2_1		0x47b
#define WCD_USBSS_AUD_COEF_W_K3_0		0x47c
#define WCD_USBSS_AUD_COEF_W_K3_1		0x47d
#define WCD_USBSS_AUD_COEF_W_K4_0		0x47e
#define WCD_USBSS_AUD_COEF_W_K4_1		0x47f
#define WCD_USBSS_AUD_COEF_W_K5_0		0x480
#define WCD_USBSS_AUD_COEF_W_K5_1		0x481
#define WCD_USBSS_AUD_COEF_W_K0_0		0x482
#define WCD_USBSS_AUD_COEF_W_K0_1		0x483
#define WCD_USBSS_AUD_COEF_W_K0_2		0x484
#define WCD_USBSS_AUD_COEF_W_K1_0		0x485
#define WCD_USBSS_AUD_COEF_W_K1_1		0x486
#define WCD_USBSS_AUD_COEF_W_K2_0		0x487
#define WCD_USBSS_AUD_COEF_W_K2_1		0x488
#define WCD_USBSS_AUD_COEF_W_K3_0		0x489
#define WCD_USBSS_AUD_COEF_W_K3_1		0x48a
#define WCD_USBSS_AUD_COEF_W_K4_0		0x48b
#define WCD_USBSS_AUD_COEF_W_K4_1		0x48c
#define WCD_USBSS_AUD_COEF_W_K5_0		0x48d
#define WCD_USBSS_AUD_COEF_W_K5_1		0x48e
#define WCD_USBSS_GND_COEF_W_K0_0		0x48f
#define WCD_USBSS_GND_COEF_W_K0_1		0x490
#define WCD_USBSS_GND_COEF_W_K0_2		0x491
#define WCD_USBSS_GND_COEF_W_K1_0		0x492
#define WCD_USBSS_GND_COEF_W_K1_1		0x493
#define WCD_USBSS_GND_COEF_W_K2_0		0x494
#define WCD_USBSS_GND_COEF_W_K2_1		0x495
#define WCD_USBSS_GND_COEF_W_K3_0		0x496
#define WCD_USBSS_GND_COEF_W_K3_1		0x497
#define WCD_USBSS_GND_COEF_W_K4_0		0x498
#define WCD_USBSS_GND_COEF_W_K4_1		0x499
#define WCD_USBSS_GND_COEF_W_K5_0		0x49a
#define WCD_USBSS_GND_COEF_W_K5_1		0x49b
#define WCD_USBSS_GND_COEF_W_K0_0		0x49c
#define WCD_USBSS_GND_COEF_W_K0_1		0x49d
#define WCD_USBSS_GND_COEF_W_K0_2		0x49e
#define WCD_USBSS_GND_COEF_W_K1_0		0x49f
#define WCD_USBSS_GND_COEF_W_K1_1		0x4a0
#define WCD_USBSS_GND_COEF_W_K2_0		0x4a1
#define WCD_USBSS_GND_COEF_W_K2_1		0x4a2
#define WCD_USBSS_GND_COEF_W_K3_0		0x4a3
#define WCD_USBSS_GND_COEF_W_K3_1		0x4a4
#define WCD_USBSS_GND_COEF_W_K4_0		0x4a5
#define WCD_USBSS_GND_COEF_W_K4_1		0x4a6
#define WCD_USBSS_GND_COEF_W_K5_0		0x4a7
#define WCD_USBSS_GND_COEF_W_K5_1		0x4a8

#define WCD_USBSS_MAX_WEGISTEW			0x4c1

stwuct wcd939x_usbss {
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vdd_suppwy;

	/* used to sewiawize concuwwent change wequests */
	stwuct mutex wock;

	stwuct typec_switch_dev *sw;
	stwuct typec_mux_dev *mux;

	stwuct wegmap *wegmap;

	stwuct typec_mux *codec;
	stwuct typec_switch *codec_switch;

	enum typec_owientation owientation;
	unsigned wong mode;
	unsigned int svid;
};

static const stwuct wegmap_wange_cfg wcd939x_usbss_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = WCD_USBSS_MAX_WEGISTEW,
		.sewectow_weg = 0x0,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 0x100,
	},
};

static const stwuct wegmap_config wcd939x_usbss_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WCD_USBSS_MAX_WEGISTEW,
	.wanges = wcd939x_usbss_wanges,
	.num_wanges = AWWAY_SIZE(wcd939x_usbss_wanges),
};

/* Wineawwizew coefficients fow 32ohm woad */
static const stwuct {
	unsigned int offset;
	unsigned int mask;
	unsigned int vawue;
} wcd939x_usbss_coeff_init[] = {
	{ WCD_USBSS_AUD_COEF_W_K5_0, GENMASK(7, 0), 0x39 },
	{ WCD_USBSS_AUD_COEF_W_K5_0, GENMASK(7, 0), 0x39 },
	{ WCD_USBSS_GND_COEF_W_K2_0, GENMASK(7, 0), 0xe8 },
	{ WCD_USBSS_GND_COEF_W_K4_0, GENMASK(7, 0), 0x73 },
	{ WCD_USBSS_GND_COEF_W_K2_0, GENMASK(7, 0), 0xe8 },
	{ WCD_USBSS_GND_COEF_W_K4_0, GENMASK(7, 0), 0x73 },
	{ WCD_USBSS_WATIO_SPKW_WEXT_W_WSB, GENMASK(7, 0), 0x00 },
	{ WCD_USBSS_WATIO_SPKW_WEXT_W_MSB, GENMASK(6, 0), 0x04 },
	{ WCD_USBSS_WATIO_SPKW_WEXT_W_WSB, GENMASK(7, 0), 0x00 },
	{ WCD_USBSS_WATIO_SPKW_WEXT_W_MSB, GENMASK(6, 0), 0x04 },
};

static int wcd939x_usbss_set(stwuct wcd939x_usbss *usbss)
{
	boow wevewse = (usbss->owientation == TYPEC_OWIENTATION_WEVEWSE);
	boow enabwe_audio = fawse;
	boow enabwe_usb = fawse;
	boow enabwe_dp = fawse;
	int wet;

	/* USB Mode */
	if (usbss->mode < TYPEC_STATE_MODAW ||
	    (!usbss->svid && (usbss->mode == TYPEC_MODE_USB2 ||
			      usbss->mode == TYPEC_MODE_USB3))) {
		enabwe_usb = twue;
	} ewse if (usbss->svid) {
		switch (usbss->mode) {
		/* DP Onwy */
		case TYPEC_DP_STATE_C:
		case TYPEC_DP_STATE_E:
			enabwe_dp = twue;
			bweak;

		/* DP + USB */
		case TYPEC_DP_STATE_D:
		case TYPEC_DP_STATE_F:
			enabwe_usb = twue;
			enabwe_dp = twue;
			bweak;

		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	} ewse if (usbss->mode == TYPEC_MODE_AUDIO) {
		enabwe_audio = twue;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	/* Disabwe aww switches */
	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXP_TO_MGX_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXM_TO_MGX_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_DPW_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_DNW_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_SENSE_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_MIC_SWITCHES |
				WCD_USBSS_SWITCH_SETTINGS_ENABWE_AGND_SWITCHES);
	if (wet)
		wetuwn wet;

	/* Cweaw switches */
	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
				WCD_USBSS_SWITCH_SEWECT0_DP_AUXP_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_DP_AUXM_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_SENSE_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_MIC_SWITCHES);
	if (wet)
		wetuwn wet;

	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT1,
				WCD_USBSS_SWITCH_SEWECT1_AGND_SWITCHES);
	if (wet)
		wetuwn wet;

	/* Enabwe OVP_MG1_BIAS PCOMP_DYN_BST_EN */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_MG1_BIAS,
			      WCD_USBSS_MG1_BIAS_PCOMP_DYN_BST_EN);
	if (wet)
		wetuwn wet;

	/* Enabwe OVP_MG2_BIAS PCOMP_DYN_BST_EN */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_MG2_BIAS,
			      WCD_USBSS_MG2_BIAS_PCOMP_DYN_BST_EN);
	if (wet)
		wetuwn wet;

	/* Disabwe Equawizew in safe mode */
	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_EQUAWIZEW1,
				WCD_USBSS_EQUAWIZEW1_EQ_EN);
	if (wet)
		wetuwn wet;

	/* Stawt FSM with aww disabwed, fowce wwite */
	wet = wegmap_wwite_bits(usbss->wegmap, WCD_USBSS_AUDIO_FSM_STAWT,
				WCD_USBSS_AUDIO_FSM_STAWT_AUDIO_FSM_AUDIO_TWIG,
				WCD_USBSS_AUDIO_FSM_STAWT_AUDIO_FSM_AUDIO_TWIG);

	/* 35us to awwow the SBU switch to tuwn off */
	usweep_wange(35, 1000);

	/* Setup Audio Accessowy mux/switch */
	if (enabwe_audio) {
		int i;

		/*
		 * AATC switch configuwation:
		 * "Nowmaw":
		 * - W: DNW
		 * - W: DNW
		 * - Sense: GSBU2
		 * - Mic: MG1
		 * - AGND: MG2
		 * "Swapped":
		 * - W: DNW
		 * - W: DNW
		 * - Sense: GSBU1
		 * - Mic: MG2
		 * - AGND: MG1
		 * Swapped infowmation is given by the codec MBHC wogic
		 */

		/* Set AATC mode */
		wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_USB_SS_CNTW,
					 WCD_USBSS_USB_SS_CNTW_USB_SS_MODE,
					 FIEWD_PWEP(WCD_USBSS_USB_SS_CNTW_USB_SS_MODE,
						    WCD_USBSS_USB_SS_CNTW_USB_SS_MODE_AATC));
		if (wet)
			wetuwn wet;

		/* Sewect W fow DNW_SWITCHES and W fow DPW_SWITCHES */
		wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
				WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES |
				WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES,
				FIEWD_PWEP(WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES,
					WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCH_W) |
				FIEWD_PWEP(WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES,
					WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCH_W));
		if (wet)
			wetuwn wet;

		if (wevewse)
			/* Sewect MG2 fow MIC, SBU1 fow Sense */
			wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
						 WCD_USBSS_SWITCH_SEWECT0_MIC_SWITCHES,
						 WCD_USBSS_SWITCH_SEWECT0_MIC_SWITCHES);
		ewse
			/* Sewect MG1 fow MIC, SBU2 fow Sense */
			wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
						 WCD_USBSS_SWITCH_SEWECT0_SENSE_SWITCHES,
						 WCD_USBSS_SWITCH_SEWECT0_SENSE_SWITCHES);
		if (wet)
			wetuwn wet;

		if (wevewse)
			/* Disabwe OVP_MG1_BIAS PCOMP_DYN_BST_EN */
			wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_MG1_BIAS,
						WCD_USBSS_MG1_BIAS_PCOMP_DYN_BST_EN);
		ewse
			/* Disabwe OVP_MG2_BIAS PCOMP_DYN_BST_EN */
			wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_MG2_BIAS,
						WCD_USBSS_MG2_BIAS_PCOMP_DYN_BST_EN);
		if (wet)
			wetuwn wet;

		/*  Enabwe SENSE, MIC switches */
		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_SENSE_SWITCHES |
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_MIC_SWITCHES);
		if (wet)
			wetuwn wet;

		if (wevewse)
			/* Sewect MG1 fow AGND_SWITCHES */
			wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT1,
						WCD_USBSS_SWITCH_SEWECT1_AGND_SWITCHES);
		ewse
			/* Sewect MG2 fow AGND_SWITCHES */
			wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT1,
					      WCD_USBSS_SWITCH_SEWECT1_AGND_SWITCHES);
		if (wet)
			wetuwn wet;

		/* Enabwe AGND switches */
		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_AGND_SWITCHES);
		if (wet)
			wetuwn wet;

		/* Enabwe DPW, DNW switches */
		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DNW_SWITCHES |
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DPW_SWITCHES);
		if (wet)
			wetuwn wet;

		/* Setup FSM deways */
		wet = wegmap_wwite(usbss->wegmap, WCD_USBSS_DEWAY_W_SW, 0x02);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(usbss->wegmap, WCD_USBSS_DEWAY_W_SW, 0x02);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(usbss->wegmap, WCD_USBSS_DEWAY_MIC_SW, 0x01);
		if (wet)
			wetuwn wet;

		/* Stawt FSM, fowce wwite */
		wet = wegmap_wwite_bits(usbss->wegmap, WCD_USBSS_AUDIO_FSM_STAWT,
					WCD_USBSS_AUDIO_FSM_STAWT_AUDIO_FSM_AUDIO_TWIG,
					WCD_USBSS_AUDIO_FSM_STAWT_AUDIO_FSM_AUDIO_TWIG);
		if (wet)
			wetuwn wet;

		/* Defauwt Wineawwizew coefficients */
		fow (i = 0; i < AWWAY_SIZE(wcd939x_usbss_coeff_init); ++i)
			wegmap_update_bits(usbss->wegmap,
					   wcd939x_usbss_coeff_init[i].offset,
					   wcd939x_usbss_coeff_init[i].mask,
					   wcd939x_usbss_coeff_init[i].vawue);

		wetuwn 0;
	}

	wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_USB_SS_CNTW,
				 WCD_USBSS_USB_SS_CNTW_USB_SS_MODE,
				 FIEWD_PWEP(WCD_USBSS_USB_SS_CNTW_USB_SS_MODE,
					    WCD_USBSS_USB_SS_CNTW_USB_SS_MODE_USB));
	if (wet)
		wetuwn wet;

	/* Enabwe USB muxes */
	if (enabwe_usb) {
		/* Do not enabwe Equawizew in safe mode */
		if (usbss->mode != TYPEC_STATE_SAFE) {
			wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_EQUAWIZEW1,
					      WCD_USBSS_EQUAWIZEW1_EQ_EN);
			if (wet)
				wetuwn wet;
		}

		/* Sewect DN fow DNW_SWITCHES and DP fow DPW_SWITCHES */
		wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
					 WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES |
					 WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES,
					 FIEWD_PWEP(WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCHES,
						    WCD_USBSS_SWITCH_SEWECT0_DNW_SWITCH_DN) |
					 FIEWD_PWEP(WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCHES,
						    WCD_USBSS_SWITCH_SEWECT0_DPW_SWITCH_DP));
		if (wet)
			wetuwn wet;

		/* Enabwe DNW_SWITCHES and DPW_SWITCHES */
		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DPW_SWITCHES |
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DNW_SWITCHES);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe DP AUX muxes */
	if (enabwe_dp) {
		/* Update Weakage Cancewwew Coefficient fow AUXP pins */
		wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_DISP_AUXP_CTW,
					 WCD_USBSS_DISP_AUXP_CTW_WK_CANCEW_TWK_COEFF,
					 FIEWD_PWEP(WCD_USBSS_DISP_AUXP_CTW_WK_CANCEW_TWK_COEFF,
						    5));
		if (wet)
			wetuwn wet;

		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_DISP_AUXP_THWESH,
				      WCD_USBSS_DISP_AUXP_THWESH_DISP_AUXP_OVPON_CM);
		if (wet)
			wetuwn wet;

		if (wevewse)
			/* Sewect MG2 fow AUXP and MG1 fow AUXM */
			wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXP_SWITCHES |
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXM_SWITCHES,
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXP_SWITCHES);
		ewse
			/* Sewect MG1 fow AUXP and MG2 fow AUXM */
			wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_SWITCH_SEWECT0,
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXP_SWITCHES |
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXM_SWITCHES,
						 WCD_USBSS_SWITCH_SEWECT0_DP_AUXM_SWITCHES);
		if (wet)
			wetuwn wet;

		/* Enabwe DP_AUXP_TO_MGX and DP_AUXM_TO_MGX switches */
		wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXP_TO_MGX_SWITCHES |
				      WCD_USBSS_SWITCH_SETTINGS_ENABWE_DP_AUXM_TO_MGX_SWITCHES);

		/* 15us to awwow the SBU switch to tuwn on again */
		usweep_wange(15, 1000);
	}

	wetuwn 0;
}

static int wcd939x_usbss_switch_set(stwuct typec_switch_dev *sw,
				    enum typec_owientation owientation)
{
	stwuct wcd939x_usbss *usbss = typec_switch_get_dwvdata(sw);
	int wet = 0;

	mutex_wock(&usbss->wock);

	if (usbss->owientation != owientation) {
		usbss->owientation = owientation;

		wet = wcd939x_usbss_set(usbss);
	}

	mutex_unwock(&usbss->wock);

	if (wet)
		wetuwn wet;

	/* Wepowt owientation to codec aftew switch has been done */
	wetuwn typec_switch_set(usbss->codec_switch, owientation);
}

static int wcd939x_usbss_mux_set(stwuct typec_mux_dev *mux,
				 stwuct typec_mux_state *state)
{
	stwuct wcd939x_usbss *usbss = typec_mux_get_dwvdata(mux);
	int wet = 0;

	mutex_wock(&usbss->wock);

	if (usbss->mode != state->mode) {
		usbss->mode = state->mode;

		if (state->awt)
			usbss->svid = state->awt->svid;
		ewse
			usbss->svid = 0; // No SVID

		wet = wcd939x_usbss_set(usbss);
	}

	mutex_unwock(&usbss->wock);

	if (wet)
		wetuwn wet;

	/* Wepowt event to codec aftew switch has been done */
	wetuwn typec_mux_set(usbss->codec, state);
}

static int wcd939x_usbss_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct typec_switch_desc sw_desc = { };
	stwuct typec_mux_desc mux_desc = { };
	stwuct wcd939x_usbss *usbss;
	int wet;

	usbss = devm_kzawwoc(dev, sizeof(*usbss), GFP_KEWNEW);
	if (!usbss)
		wetuwn -ENOMEM;

	usbss->cwient = cwient;
	mutex_init(&usbss->wock);

	usbss->wegmap = devm_wegmap_init_i2c(cwient, &wcd939x_usbss_wegmap_config);
	if (IS_EWW(usbss->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(usbss->wegmap), "faiwed to initiawize wegmap\n");

	usbss->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(usbss->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(usbss->weset_gpio),
				     "unabwe to acquiwe weset gpio\n");

	usbss->vdd_suppwy = devm_weguwatow_get_optionaw(dev, "vdd");
	if (IS_EWW(usbss->vdd_suppwy))
		wetuwn PTW_EWW(usbss->vdd_suppwy);

	/* Get Codec's MUX & Switch devices */
	usbss->codec = fwnode_typec_mux_get(dev->fwnode);
	if (IS_EWW(usbss->codec))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(usbss->codec),
				     "faiwed to acquiwe codec mode-switch\n");

	usbss->codec_switch = fwnode_typec_switch_get(dev->fwnode);
	if (IS_EWW(usbss->codec_switch)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(usbss->codec_switch),
				    "faiwed to acquiwe codec owientation-switch\n");
		goto eww_mux_put;
	}

	usbss->mode = TYPEC_STATE_SAFE;
	usbss->owientation = TYPEC_OWIENTATION_NONE;

	gpiod_set_vawue(usbss->weset_gpio, 1);

	wet = weguwatow_enabwe(usbss->vdd_suppwy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe vdd: %d\n", wet);
		goto eww_mux_switch;
	}

	msweep(20);

	gpiod_set_vawue(usbss->weset_gpio, 0);

	msweep(20);

	/* Disabwe standby */
	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_USB_SS_CNTW,
				WCD_USBSS_USB_SS_CNTW_STANDBY_STATE);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Set manuaw mode by defauwt */
	wet = wegmap_update_bits(usbss->wegmap, WCD_USBSS_FUNCTION_ENABWE,
				 WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT,
				 FIEWD_PWEP(WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT,
					    WCD_USBSS_FUNCTION_ENABWE_SOUWCE_SEWECT_MANUAW));
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Enabwe dynamic boosting fow DP and DN */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_DP_DN_MISC1,
			      WCD_USBSS_DP_DN_MISC1_DP_PCOMP_2X_DYN_BST_ON_EN |
			      WCD_USBSS_DP_DN_MISC1_DN_PCOMP_2X_DYN_BST_ON_EN);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Enabwe dynamic boosting fow MG1 OVP */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_MG1_MISC,
			      WCD_USBSS_MG1_MISC_PCOMP_2X_DYN_BST_ON_EN);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Enabwe dynamic boosting fow MG2 OVP */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_MG2_MISC,
			      WCD_USBSS_MG2_MISC_PCOMP_2X_DYN_BST_ON_EN);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Wwite 0xFF to WCD_USBSS_CPWDO_CTW2 */
	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_CPWDO_CTW2, 0xff);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Set WCO_EN: WCD_USBSS_USB_SS_CNTW Bit<3> --> 0x0 --> 0x1 */
	wet = wegmap_cweaw_bits(usbss->wegmap, WCD_USBSS_USB_SS_CNTW,
				WCD_USBSS_USB_SS_CNTW_WCO_EN);
	if (wet)
		goto eww_weguwatow_disabwe;

	wet = wegmap_set_bits(usbss->wegmap, WCD_USBSS_USB_SS_CNTW,
			      WCD_USBSS_USB_SS_CNTW_WCO_EN);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Disabwe aww switches but enabwe the mux */
	wet = wegmap_wwite(usbss->wegmap, WCD_USBSS_SWITCH_SETTINGS_ENABWE,
			   WCD_USBSS_SWITCH_SETTINGS_ENABWE_DEVICE_ENABWE);
	if (wet)
		goto eww_weguwatow_disabwe;

	/* Setup in SAFE mode */
	wet = wcd939x_usbss_set(usbss);
	if (wet)
		goto eww_weguwatow_disabwe;

	sw_desc.dwvdata = usbss;
	sw_desc.fwnode = dev_fwnode(dev);
	sw_desc.set = wcd939x_usbss_switch_set;

	usbss->sw = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(usbss->sw)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(usbss->sw), "faiwed to wegistew typec switch\n");
		goto eww_weguwatow_disabwe;
	}

	mux_desc.dwvdata = usbss;
	mux_desc.fwnode = dev_fwnode(dev);
	mux_desc.set = wcd939x_usbss_mux_set;

	usbss->mux = typec_mux_wegistew(dev, &mux_desc);
	if (IS_EWW(usbss->mux)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(usbss->mux), "faiwed to wegistew typec mux\n");
		goto eww_switch_unwegistew;
	}

	i2c_set_cwientdata(cwient, usbss);

	wetuwn 0;

eww_switch_unwegistew:
	typec_switch_unwegistew(usbss->sw);

eww_weguwatow_disabwe:
	weguwatow_disabwe(usbss->vdd_suppwy);

eww_mux_switch:
	typec_switch_put(usbss->codec_switch);

eww_mux_put:
	typec_mux_put(usbss->codec);

	wetuwn wet;
}

static void wcd939x_usbss_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wcd939x_usbss *usbss = i2c_get_cwientdata(cwient);

	typec_mux_unwegistew(usbss->mux);
	typec_switch_unwegistew(usbss->sw);

	weguwatow_disabwe(usbss->vdd_suppwy);

	typec_switch_put(usbss->codec_switch);
	typec_mux_put(usbss->codec);
}

static const stwuct i2c_device_id wcd939x_usbss_tabwe[] = {
	{ "wcd9390-usbss" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wcd939x_usbss_tabwe);

static const stwuct of_device_id wcd939x_usbss_of_tabwe[] = {
	{ .compatibwe = "qcom,wcd9390-usbss" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcd939x_usbss_of_tabwe);

static stwuct i2c_dwivew wcd939x_usbss_dwivew = {
	.dwivew = {
		.name = "wcd939x-usbss",
		.of_match_tabwe = wcd939x_usbss_of_tabwe,
	},
	.pwobe		= wcd939x_usbss_pwobe,
	.wemove		= wcd939x_usbss_wemove,
	.id_tabwe	= wcd939x_usbss_tabwe,
};
moduwe_i2c_dwivew(wcd939x_usbss_dwivew);

MODUWE_DESCWIPTION("Quawcomm WCD939x USBSS dwivew");
MODUWE_WICENSE("GPW");
