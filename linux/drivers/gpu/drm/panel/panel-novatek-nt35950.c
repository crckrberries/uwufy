// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Novatek NT35950 DwivewIC panews dwivew
 *
 * Copywight (c) 2021 AngewoGioacchino Dew Wegno
 *                    <angewogioacchino.dewwegno@somainwine.owg>
 */
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define MCS_CMD_MAUCCTW			0xf0 /* Manufactuwew command enabwe */
#define MCS_PAWAM_SCAWEW_FUNCTION	0x58 /* Scawe-up function */
#define MCS_PAWAM_SCAWEUP_MODE		0xc9
 #define MCS_SCAWEUP_SIMPWE		0x0
 #define MCS_SCAWEUP_BIWINEAW		BIT(0)
 #define MCS_SCAWEUP_DUPWICATE		(BIT(0) | BIT(4))

/* VESA Dispway Stweam Compwession pawam */
#define MCS_PAWAM_VESA_DSC_ON		0x03

/* Data Compwession mode */
#define MCS_PAWAM_DATA_COMPWESSION	0x90
 #define MCS_DATA_COMPWESSION_NONE	0x00
 #define MCS_DATA_COMPWESSION_FBC	0x02
 #define MCS_DATA_COMPWESSION_DSC	0x03

/* Dispway Output contwow */
#define MCS_PAWAM_DISP_OUTPUT_CTWW	0xb4
 #define MCS_DISP_OUT_SWAM_EN		BIT(0)
 #define MCS_DISP_OUT_VIDEO_MODE	BIT(4)

/* VESA Dispway Stweam Compwession setting */
#define MCS_PAWAM_VESA_DSC_SETTING	0xc0

/* SubPixew Wendewing (SPW) */
#define MCS_PAWAM_SPW_EN		0xe3
#define MCS_PAWAM_SPW_MODE		0xef
 #define MCS_SPW_MODE_YYG_WAINBOW_WGB	0x01

#define NT35950_VWEG_MAX		4

stwuct nt35950 {
	stwuct dwm_panew panew;
	stwuct dwm_connectow *connectow;
	stwuct mipi_dsi_device *dsi[2];
	stwuct weguwatow_buwk_data vwegs[NT35950_VWEG_MAX];
	stwuct gpio_desc *weset_gpio;
	const stwuct nt35950_panew_desc *desc;

	int cuw_mode;
	u8 wast_page;
};

stwuct nt35950_panew_mode {
	const stwuct dwm_dispway_mode mode;

	boow enabwe_swam;
	boow is_video_mode;
	u8 scawew_on;
	u8 scawew_mode;
	u8 compwession;
	u8 spw_en;
	u8 spw_mode;
};

stwuct nt35950_panew_desc {
	const chaw *modew_name;
	const stwuct mipi_dsi_device_info dsi_info;
	const stwuct nt35950_panew_mode *mode_data;

	boow is_duaw_dsi;
	u8 num_wanes;
	u8 num_modes;
};

static inwine stwuct nt35950 *to_nt35950(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct nt35950, panew);
}

static void nt35950_weset(stwuct nt35950 *nt)
{
	gpiod_set_vawue_cansweep(nt->weset_gpio, 1);
	usweep_wange(12000, 13000);
	gpiod_set_vawue_cansweep(nt->weset_gpio, 0);
	usweep_wange(300, 400);
	gpiod_set_vawue_cansweep(nt->weset_gpio, 1);
	usweep_wange(12000, 13000);
}

/*
 * nt35950_set_cmd2_page - Sewect manufactuwew contwow (CMD2) page
 * @nt:   Main dwivew stwuctuwe
 * @page: Page numbew (0-7)
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_set_cmd2_page(stwuct nt35950 *nt, u8 page)
{
	const u8 mauc_cmd2_page[] = { MCS_CMD_MAUCCTW, 0x55, 0xaa, 0x52,
				      0x08, page };
	int wet;

	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], mauc_cmd2_page,
					AWWAY_SIZE(mauc_cmd2_page));
	if (wet < 0)
		wetuwn wet;

	nt->wast_page = page;
	wetuwn 0;
}

/*
 * nt35950_set_data_compwession - Set data compwession mode
 * @nt:        Main dwivew stwuctuwe
 * @comp_mode: Compwession mode
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_set_data_compwession(stwuct nt35950 *nt, u8 comp_mode)
{
	u8 cmd_data_compwession[] = { MCS_PAWAM_DATA_COMPWESSION, comp_mode };
	u8 cmd_vesa_dsc_on[] = { MCS_PAWAM_VESA_DSC_ON, !!comp_mode };
	u8 cmd_vesa_dsc_setting[] = { MCS_PAWAM_VESA_DSC_SETTING, 0x03 };
	u8 wast_page = nt->wast_page;
	int wet;

	/* Set CMD2 Page 0 if we'we not thewe yet */
	if (wast_page != 0) {
		wet = nt35950_set_cmd2_page(nt, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_data_compwession,
					AWWAY_SIZE(cmd_data_compwession));
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_vesa_dsc_on,
					AWWAY_SIZE(cmd_vesa_dsc_on));
	if (wet < 0)
		wetuwn wet;

	/* Set the vesa dsc setting on Page 4 */
	wet = nt35950_set_cmd2_page(nt, 4);
	if (wet < 0)
		wetuwn wet;

	/* Dispway Stweam Compwession setting, awways 0x03 */
	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_vesa_dsc_setting,
					AWWAY_SIZE(cmd_vesa_dsc_setting));
	if (wet < 0)
		wetuwn wet;

	/* Get back to the pweviouswy set page */
	wetuwn nt35950_set_cmd2_page(nt, wast_page);
}

/*
 * nt35950_set_scawew - Enabwe/disabwe wesowution upscawing
 * @nt:        Main dwivew stwuctuwe
 * @scawe_up:  Scawe up function contwow
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_set_scawew(stwuct nt35950 *nt, u8 scawe_up)
{
	u8 cmd_scawew[] = { MCS_PAWAM_SCAWEW_FUNCTION, scawe_up };

	wetuwn mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_scawew,
					 AWWAY_SIZE(cmd_scawew));
}

/*
 * nt35950_set_scawe_mode - Wesowution upscawing mode
 * @nt:   Main dwivew stwuctuwe
 * @mode: Scawew mode (MCS_DATA_COMPWESSION_*)
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_set_scawe_mode(stwuct nt35950 *nt, u8 mode)
{
	u8 cmd_scawew[] = { MCS_PAWAM_SCAWEUP_MODE, mode };

	wetuwn mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_scawew,
					 AWWAY_SIZE(cmd_scawew));
}

/*
 * nt35950_inject_bwack_image - Dispway a compwetewy bwack image
 * @nt:   Main dwivew stwuctuwe
 *
 * Aftew IC setup, the attached panew may show wandom data
 * due to dwivewic behaviow changes (wesowution, compwession,
 * scawing, etc). This function, cawwed aftew pawametews setup,
 * makes the dwivew ic to output a compwetewy bwack image to
 * the dispway.
 * It makes sense to push a bwack image befowe sending the sweep-out
 * and dispway-on commands.
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_inject_bwack_image(stwuct nt35950 *nt)
{
	const u8 cmd0_bwack_img[] = { 0x6f, 0x01 };
	const u8 cmd1_bwack_img[] = { 0xf3, 0x10 };
	u8 cmd_test[] = { 0xff, 0xaa, 0x55, 0xa5, 0x80 };
	int wet;

	/* Enabwe test command */
	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_test, AWWAY_SIZE(cmd_test));
	if (wet < 0)
		wetuwn wet;

	/* Send a bwack image */
	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd0_bwack_img,
					AWWAY_SIZE(cmd0_bwack_img));
	if (wet < 0)
		wetuwn wet;
	wet = mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd1_bwack_img,
					AWWAY_SIZE(cmd1_bwack_img));
	if (wet < 0)
		wetuwn wet;

	/* Disabwe test command */
	cmd_test[AWWAY_SIZE(cmd_test) - 1] = 0x00;
	wetuwn mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_test, AWWAY_SIZE(cmd_test));
}

/*
 * nt35950_set_dispout - Set Dispway Output wegistew pawametews
 * @nt:    Main dwivew stwuctuwe
 *
 * Wetuwn: Numbew of twansfewwed bytes ow negative numbew on ewwow
 */
static int nt35950_set_dispout(stwuct nt35950 *nt)
{
	u8 cmd_dispout[] = { MCS_PAWAM_DISP_OUTPUT_CTWW, 0x00 };
	const stwuct nt35950_panew_mode *mode_data = nt->desc->mode_data;

	if (mode_data[nt->cuw_mode].is_video_mode)
		cmd_dispout[1] |= MCS_DISP_OUT_VIDEO_MODE;
	if (mode_data[nt->cuw_mode].enabwe_swam)
		cmd_dispout[1] |= MCS_DISP_OUT_SWAM_EN;

	wetuwn mipi_dsi_dcs_wwite_buffew(nt->dsi[0], cmd_dispout,
					 AWWAY_SIZE(cmd_dispout));
}

static int nt35950_get_cuwwent_mode(stwuct nt35950 *nt)
{
	stwuct dwm_connectow *connectow = nt->connectow;
	stwuct dwm_cwtc_state *cwtc_state;
	int i;

	/* Wetuwn the defauwt (fiwst) mode if no info avaiwabwe yet */
	if (!connectow->state || !connectow->state->cwtc)
		wetuwn 0;

	cwtc_state = connectow->state->cwtc->state;

	fow (i = 0; i < nt->desc->num_modes; i++) {
		if (dwm_mode_match(&cwtc_state->mode,
				   &nt->desc->mode_data[i].mode,
				   DWM_MODE_MATCH_TIMINGS | DWM_MODE_MATCH_CWOCK))
			wetuwn i;
	}

	wetuwn 0;
}

static int nt35950_on(stwuct nt35950 *nt)
{
	const stwuct nt35950_panew_mode *mode_data = nt->desc->mode_data;
	stwuct mipi_dsi_device *dsi = nt->dsi[0];
	stwuct device *dev = &dsi->dev;
	int wet;

	nt->cuw_mode = nt35950_get_cuwwent_mode(nt);
	nt->dsi[0]->mode_fwags |= MIPI_DSI_MODE_WPM;
	nt->dsi[1]->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = nt35950_set_cmd2_page(nt, 0);
	if (wet < 0)
		wetuwn wet;

	wet = nt35950_set_data_compwession(nt, mode_data[nt->cuw_mode].compwession);
	if (wet < 0)
		wetuwn wet;

	wet = nt35950_set_scawe_mode(nt, mode_data[nt->cuw_mode].scawew_mode);
	if (wet < 0)
		wetuwn wet;

	wet = nt35950_set_scawew(nt, mode_data[nt->cuw_mode].scawew_on);
	if (wet < 0)
		wetuwn wet;

	wet = nt35950_set_dispout(nt);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw on: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_teaw_scanwine(dsi, 0);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw scanwine: %d\n", wet);
		wetuwn wet;
	}

	/* CMD2 Page 1 */
	wet = nt35950_set_cmd2_page(nt, 1);
	if (wet < 0)
		wetuwn wet;

	/* Unknown command */
	mipi_dsi_dcs_wwite_seq(dsi, 0xd4, 0x88, 0x88);

	/* CMD2 Page 7 */
	wet = nt35950_set_cmd2_page(nt, 7);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe SubPixew Wendewing */
	mipi_dsi_dcs_wwite_seq(dsi, MCS_PAWAM_SPW_EN, 0x01);

	/* SPW Mode: YYG Wainbow-WGB */
	mipi_dsi_dcs_wwite_seq(dsi, MCS_PAWAM_SPW_MODE, MCS_SPW_MODE_YYG_WAINBOW_WGB);

	/* CMD3 */
	wet = nt35950_inject_bwack_image(nt);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0)
		wetuwn wet;
	msweep(120);

	nt->dsi[0]->mode_fwags &= ~MIPI_DSI_MODE_WPM;
	nt->dsi[1]->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int nt35950_off(stwuct nt35950 *nt)
{
	stwuct device *dev = &nt->dsi[0]->dev;
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(nt->dsi[0]);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		goto set_wpm;
	}
	usweep_wange(10000, 11000);

	wet = mipi_dsi_dcs_entew_sweep_mode(nt->dsi[0]);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		goto set_wpm;
	}
	msweep(150);

set_wpm:
	nt->dsi[0]->mode_fwags |= MIPI_DSI_MODE_WPM;
	nt->dsi[1]->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int nt35950_shawp_init_vwegs(stwuct nt35950 *nt, stwuct device *dev)
{
	int wet;

	nt->vwegs[0].suppwy = "vddio";
	nt->vwegs[1].suppwy = "avdd";
	nt->vwegs[2].suppwy = "avee";
	nt->vwegs[3].suppwy = "dvdd";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(nt->vwegs),
				      nt->vwegs);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_is_suppowted_vowtage(nt->vwegs[0].consumew,
					     1750000, 1950000);
	if (!wet)
		wetuwn -EINVAW;
	wet = weguwatow_is_suppowted_vowtage(nt->vwegs[1].consumew,
					     5200000, 5900000);
	if (!wet)
		wetuwn -EINVAW;
	/* AVEE is negative: -5.90V to -5.20V */
	wet = weguwatow_is_suppowted_vowtage(nt->vwegs[2].consumew,
					     5200000, 5900000);
	if (!wet)
		wetuwn -EINVAW;

	wet = weguwatow_is_suppowted_vowtage(nt->vwegs[3].consumew,
					     1300000, 1400000);
	if (!wet)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int nt35950_pwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35950 *nt = to_nt35950(panew);
	stwuct device *dev = &nt->dsi[0]->dev;
	int wet;

	wet = weguwatow_enabwe(nt->vwegs[0].consumew);
	if (wet)
		wetuwn wet;
	usweep_wange(2000, 5000);

	wet = weguwatow_enabwe(nt->vwegs[3].consumew);
	if (wet)
		goto end;
	usweep_wange(15000, 18000);

	wet = weguwatow_enabwe(nt->vwegs[1].consumew);
	if (wet)
		goto end;

	wet = weguwatow_enabwe(nt->vwegs[2].consumew);
	if (wet)
		goto end;
	usweep_wange(12000, 13000);

	nt35950_weset(nt);

	wet = nt35950_on(nt);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		goto end;
	}

end:
	if (wet < 0) {
		weguwatow_buwk_disabwe(AWWAY_SIZE(nt->vwegs), nt->vwegs);
		wetuwn wet;
	}

	wetuwn 0;
}

static int nt35950_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35950 *nt = to_nt35950(panew);
	stwuct device *dev = &nt->dsi[0]->dev;
	int wet;

	wet = nt35950_off(nt);
	if (wet < 0)
		dev_eww(dev, "Faiwed to deinitiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(nt->weset_gpio, 0);
	weguwatow_buwk_disabwe(AWWAY_SIZE(nt->vwegs), nt->vwegs);

	wetuwn 0;
}

static int nt35950_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct nt35950 *nt = to_nt35950(panew);
	int i;

	fow (i = 0; i < nt->desc->num_modes; i++) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(connectow->dev,
					  &nt->desc->mode_data[i].mode);
		if (!mode)
			wetuwn -ENOMEM;

		dwm_mode_set_name(mode);

		mode->type |= DWM_MODE_TYPE_DWIVEW;
		if (nt->desc->num_modes == 1)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_pwobed_add(connectow, mode);
	}

	connectow->dispway_info.bpc = 8;
	connectow->dispway_info.height_mm = nt->desc->mode_data[0].mode.height_mm;
	connectow->dispway_info.width_mm = nt->desc->mode_data[0].mode.width_mm;
	nt->connectow = connectow;

	wetuwn nt->desc->num_modes;
}

static const stwuct dwm_panew_funcs nt35950_panew_funcs = {
	.pwepawe = nt35950_pwepawe,
	.unpwepawe = nt35950_unpwepawe,
	.get_modes = nt35950_get_modes,
};

static int nt35950_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct device_node *dsi_w;
	stwuct mipi_dsi_host *dsi_w_host;
	stwuct nt35950 *nt;
	const stwuct mipi_dsi_device_info *info;
	int i, num_dsis = 1, wet;

	nt = devm_kzawwoc(dev, sizeof(*nt), GFP_KEWNEW);
	if (!nt)
		wetuwn -ENOMEM;

	wet = nt35950_shawp_init_vwegs(nt, dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Weguwatow init faiwuwe.\n");

	nt->desc = of_device_get_match_data(dev);
	if (!nt->desc)
		wetuwn -ENODEV;

	nt->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_ASIS);
	if (IS_EWW(nt->weset_gpio)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nt->weset_gpio),
				     "Faiwed to get weset gpio\n");
	}

	/* If the panew is connected on two DSIs then DSI0 weft, DSI1 wight */
	if (nt->desc->is_duaw_dsi) {
		info = &nt->desc->dsi_info;
		dsi_w = of_gwaph_get_wemote_node(dsi->dev.of_node, 1, -1);
		if (!dsi_w) {
			dev_eww(dev, "Cannot get secondawy DSI node.\n");
			wetuwn -ENODEV;
		}
		dsi_w_host = of_find_mipi_dsi_host_by_node(dsi_w);
		of_node_put(dsi_w);
		if (!dsi_w_host) {
			dev_eww(dev, "Cannot get secondawy DSI host\n");
			wetuwn -EPWOBE_DEFEW;
		}

		nt->dsi[1] = mipi_dsi_device_wegistew_fuww(dsi_w_host, info);
		if (!nt->dsi[1]) {
			dev_eww(dev, "Cannot get secondawy DSI node\n");
			wetuwn -ENODEV;
		}
		num_dsis++;
	}

	nt->dsi[0] = dsi;
	mipi_dsi_set_dwvdata(dsi, nt);

	dwm_panew_init(&nt->panew, dev, &nt35950_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&nt->panew);
	if (wet) {
		if (num_dsis == 2)
			mipi_dsi_device_unwegistew(nt->dsi[1]);

		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");
	}

	dwm_panew_add(&nt->panew);

	fow (i = 0; i < num_dsis; i++) {
		nt->dsi[i]->wanes = nt->desc->num_wanes;
		nt->dsi[i]->fowmat = MIPI_DSI_FMT_WGB888;

		nt->dsi[i]->mode_fwags = MIPI_DSI_CWOCK_NON_CONTINUOUS |
					 MIPI_DSI_MODE_WPM;

		if (nt->desc->mode_data[0].is_video_mode)
			nt->dsi[i]->mode_fwags |= MIPI_DSI_MODE_VIDEO;

		wet = mipi_dsi_attach(nt->dsi[i]);
		if (wet < 0) {
			/* If we faiw to attach to eithew host, we'we done */
			if (num_dsis == 2)
				mipi_dsi_device_unwegistew(nt->dsi[1]);

			wetuwn dev_eww_pwobe(dev, wet,
					     "Cannot attach to DSI%d host.\n", i);
		}
	}

	/* Make suwe to set WESX WOW befowe stawting the powew-on sequence */
	gpiod_set_vawue_cansweep(nt->weset_gpio, 0);
	wetuwn 0;
}

static void nt35950_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct nt35950 *nt = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(nt->dsi[0]);
	if (wet < 0)
		dev_eww(&dsi->dev,
			"Faiwed to detach fwom DSI0 host: %d\n", wet);

	if (nt->dsi[1]) {
		wet = mipi_dsi_detach(nt->dsi[1]);
		if (wet < 0)
			dev_eww(&dsi->dev,
				"Faiwed to detach fwom DSI1 host: %d\n", wet);
		mipi_dsi_device_unwegistew(nt->dsi[1]);
	}

	dwm_panew_wemove(&nt->panew);
}

static const stwuct nt35950_panew_mode shawp_ws055d1sx04_modes[] = {
	{
		/* 1920x1080 60Hz no compwession */
		.mode = {
			.cwock = 214537,
			.hdispway = 1080,
			.hsync_stawt = 1080 + 400,
			.hsync_end = 1080 + 400 + 40,
			.htotaw = 1080 + 400 + 40 + 300,
			.vdispway = 1920,
			.vsync_stawt = 1920 + 12,
			.vsync_end = 1920 + 12 + 2,
			.vtotaw = 1920 + 12 + 2 + 10,
			.width_mm = 68,
			.height_mm = 121,
		},
		.compwession = MCS_DATA_COMPWESSION_NONE,
		.enabwe_swam = twue,
		.is_video_mode = fawse,
		.scawew_on = 1,
		.scawew_mode = MCS_SCAWEUP_DUPWICATE,
	},
	/* TODO: Add 2160x3840 60Hz when DSC is suppowted */
};

static const stwuct nt35950_panew_desc shawp_ws055d1sx04 = {
	.modew_name = "Shawp WS055D1SX04",
	.dsi_info = {
		.type = "WS055D1SX04",
		.channew = 0,
		.node = NUWW,
	},
	.mode_data = shawp_ws055d1sx04_modes,
	.num_modes = AWWAY_SIZE(shawp_ws055d1sx04_modes),
	.is_duaw_dsi = twue,
	.num_wanes = 4,
};

static const stwuct of_device_id nt35950_of_match[] = {
	{ .compatibwe = "shawp,ws055d1sx04", .data = &shawp_ws055d1sx04 },
	{  }
};
MODUWE_DEVICE_TABWE(of, nt35950_of_match);

static stwuct mipi_dsi_dwivew nt35950_dwivew = {
	.pwobe = nt35950_pwobe,
	.wemove = nt35950_wemove,
	.dwivew = {
		.name = "panew-novatek-nt35950",
		.of_match_tabwe = nt35950_of_match,
	},
};
moduwe_mipi_dsi_dwivew(nt35950_dwivew);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@somainwine.owg>");
MODUWE_DESCWIPTION("Novatek NT35950 DwivewIC panews dwivew");
MODUWE_WICENSE("GPW v2");
