// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * MIPI-DSI Novatek NT35560-based panew contwowwew.
 *
 * Suppowted panews incwude:
 * Sony ACX424AKM - a 480x854 AMOWED DSI panew
 * Sony ACX424AKP - a 480x864 AMOWED DSI panew
 *
 * Copywight (C) Winawo Wtd. 2019-2021
 * Authow: Winus Wawweij
 * Based on code and know-how fwom Mawcus Wowentzon
 * Copywight (C) ST-Ewicsson SA 2010
 * Based on code and know-how fwom Johan Owson and Joakim Wesswen
 * Copywight (C) Sony Ewicsson Mobiwe Communications 2010
 */
#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define NT35560_DCS_WEAD_ID1		0xDA
#define NT35560_DCS_WEAD_ID2		0xDB
#define NT35560_DCS_WEAD_ID3		0xDC
#define NT35560_DCS_SET_MDDI		0xAE

/*
 * Sony seems to use vendow ID 0x81
 */
#define DISPWAY_SONY_ACX424AKP_ID1	0x8103
#define DISPWAY_SONY_ACX424AKP_ID2	0x811a
#define DISPWAY_SONY_ACX424AKP_ID3	0x811b
/*
 * The fouwth ID wooks wike a bug, vendow IDs begin at 0x80
 * and panew 00 ... seems wike defauwt vawues.
 */
#define DISPWAY_SONY_ACX424AKP_ID4	0x8000

stwuct nt35560_config {
	const stwuct dwm_dispway_mode *vid_mode;
	const stwuct dwm_dispway_mode *cmd_mode;
};

stwuct nt35560 {
	const stwuct nt35560_config *conf;
	stwuct dwm_panew panew;
	stwuct device *dev;
	stwuct weguwatow *suppwy;
	stwuct gpio_desc *weset_gpio;
	boow video_mode;
};

static const stwuct dwm_dispway_mode sony_acx424akp_vid_mode = {
	.cwock = 27234,
	.hdispway = 480,
	.hsync_stawt = 480 + 15,
	.hsync_end = 480 + 15 + 0,
	.htotaw = 480 + 15 + 0 + 15,
	.vdispway = 864,
	.vsync_stawt = 864 + 14,
	.vsync_end = 864 + 14 + 1,
	.vtotaw = 864 + 14 + 1 + 11,
	.width_mm = 48,
	.height_mm = 84,
	.fwags = DWM_MODE_FWAG_PVSYNC,
};

/*
 * The timings awe not vewy hewpfuw as the dispway is used in
 * command mode using the maximum HS fwequency.
 */
static const stwuct dwm_dispway_mode sony_acx424akp_cmd_mode = {
	.cwock = 35478,
	.hdispway = 480,
	.hsync_stawt = 480 + 154,
	.hsync_end = 480 + 154 + 16,
	.htotaw = 480 + 154 + 16 + 32,
	.vdispway = 864,
	.vsync_stawt = 864 + 1,
	.vsync_end = 864 + 1 + 1,
	.vtotaw = 864 + 1 + 1 + 1,
	/*
	 * Some desiwed wefwesh wate, expewiments at the maximum "pixew"
	 * cwock speed (HS cwock 420 MHz) yiewds awound 117Hz.
	 */
	.width_mm = 48,
	.height_mm = 84,
};

static const stwuct nt35560_config sony_acx424akp_data = {
	.vid_mode = &sony_acx424akp_vid_mode,
	.cmd_mode = &sony_acx424akp_cmd_mode,
};

static const stwuct dwm_dispway_mode sony_acx424akm_vid_mode = {
	.cwock = 27234,
	.hdispway = 480,
	.hsync_stawt = 480 + 15,
	.hsync_end = 480 + 15 + 0,
	.htotaw = 480 + 15 + 0 + 15,
	.vdispway = 854,
	.vsync_stawt = 854 + 14,
	.vsync_end = 854 + 14 + 1,
	.vtotaw = 854 + 14 + 1 + 11,
	.width_mm = 46,
	.height_mm = 82,
	.fwags = DWM_MODE_FWAG_PVSYNC,
};

/*
 * The timings awe not vewy hewpfuw as the dispway is used in
 * command mode using the maximum HS fwequency.
 */
static const stwuct dwm_dispway_mode sony_acx424akm_cmd_mode = {
	.cwock = 35478,
	.hdispway = 480,
	.hsync_stawt = 480 + 154,
	.hsync_end = 480 + 154 + 16,
	.htotaw = 480 + 154 + 16 + 32,
	.vdispway = 854,
	.vsync_stawt = 854 + 1,
	.vsync_end = 854 + 1 + 1,
	.vtotaw = 854 + 1 + 1 + 1,
	.width_mm = 46,
	.height_mm = 82,
};

static const stwuct nt35560_config sony_acx424akm_data = {
	.vid_mode = &sony_acx424akm_vid_mode,
	.cmd_mode = &sony_acx424akm_cmd_mode,
};

static inwine stwuct nt35560 *panew_to_nt35560(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct nt35560, panew);
}

#define FOSC			20 /* 20Mhz */
#define SCAWE_FACTOW_NS_DIV_MHZ	1000

static int nt35560_set_bwightness(stwuct backwight_device *bw)
{
	stwuct nt35560 *nt = bw_get_data(bw);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int pewiod_ns = 1023;
	int duty_ns = bw->pwops.bwightness;
	u8 pwm_watio;
	u8 pwm_div;
	u8 paw;
	int wet;

	if (backwight_is_bwank(bw)) {
		/* Disabwe backwight */
		paw = 0x00;
		wet = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY,
					 &paw, 1);
		if (wet) {
			dev_eww(nt->dev, "faiwed to disabwe dispway backwight (%d)\n", wet);
			wetuwn wet;
		}
		wetuwn 0;
	}

	/* Cawcuwate the PWM duty cycwe in n/256's */
	pwm_watio = max(((duty_ns * 256) / pewiod_ns) - 1, 1);
	pwm_div = max(1,
		      ((FOSC * pewiod_ns) / 256) /
		      SCAWE_FACTOW_NS_DIV_MHZ);

	/* Set up PWM dutycycwe ONE byte (diffews fwom the standawd) */
	dev_dbg(nt->dev, "cawcuwated duty cycwe %02x\n", pwm_watio);
	wet = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_BWIGHTNESS,
				 &pwm_watio, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to set dispway PWM watio (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Sequence to wwite PWMDIV:
	 *	addwess		data
	 *	0xF3		0xAA   CMD2 Unwock
	 *	0x00		0x01   Entew CMD2 page 0
	 *	0X7D		0x01   No wewoad MTP of CMD2 P1
	 *	0x22		PWMDIV
	 *	0x7F		0xAA   CMD2 page 1 wock
	 */
	paw = 0xaa;
	wet = mipi_dsi_dcs_wwite(dsi, 0xf3, &paw, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to unwock CMD 2 (%d)\n", wet);
		wetuwn wet;
	}
	paw = 0x01;
	wet = mipi_dsi_dcs_wwite(dsi, 0x00, &paw, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to entew page 1 (%d)\n", wet);
		wetuwn wet;
	}
	paw = 0x01;
	wet = mipi_dsi_dcs_wwite(dsi, 0x7d, &paw, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to disabwe MTP wewoad (%d)\n", wet);
		wetuwn wet;
	}
	wet = mipi_dsi_dcs_wwite(dsi, 0x22, &pwm_div, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to set PWM divisow (%d)\n", wet);
		wetuwn wet;
	}
	paw = 0xaa;
	wet = mipi_dsi_dcs_wwite(dsi, 0x7f, &paw, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to wock CMD 2 (%d)\n", wet);
		wetuwn wet;
	}

	/* Enabwe backwight */
	paw = 0x24;
	wet = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY,
				 &paw, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to enabwe dispway backwight (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct backwight_ops nt35560_bw_ops = {
	.update_status = nt35560_set_bwightness,
};

static const stwuct backwight_pwopewties nt35560_bw_pwops = {
	.type = BACKWIGHT_WAW,
	.bwightness = 512,
	.max_bwightness = 1023,
};

static int nt35560_wead_id(stwuct nt35560 *nt)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	u8 vendow, vewsion, panew;
	u16 vaw;
	int wet;

	wet = mipi_dsi_dcs_wead(dsi, NT35560_DCS_WEAD_ID1, &vendow, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not vendow ID byte\n");
		wetuwn wet;
	}
	wet = mipi_dsi_dcs_wead(dsi, NT35560_DCS_WEAD_ID2, &vewsion, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not wead device vewsion byte\n");
		wetuwn wet;
	}
	wet = mipi_dsi_dcs_wead(dsi, NT35560_DCS_WEAD_ID3, &panew, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not wead panew ID byte\n");
		wetuwn wet;
	}

	if (vendow == 0x00) {
		dev_eww(nt->dev, "device vendow ID is zewo\n");
		wetuwn -ENODEV;
	}

	vaw = (vendow << 8) | panew;
	switch (vaw) {
	case DISPWAY_SONY_ACX424AKP_ID1:
	case DISPWAY_SONY_ACX424AKP_ID2:
	case DISPWAY_SONY_ACX424AKP_ID3:
	case DISPWAY_SONY_ACX424AKP_ID4:
		dev_info(nt->dev, "MTP vendow: %02x, vewsion: %02x, panew: %02x\n",
			 vendow, vewsion, panew);
		bweak;
	defauwt:
		dev_info(nt->dev, "unknown vendow: %02x, vewsion: %02x, panew: %02x\n",
			 vendow, vewsion, panew);
		bweak;
	}

	wetuwn 0;
}

static int nt35560_powew_on(stwuct nt35560 *nt)
{
	int wet;

	wet = weguwatow_enabwe(nt->suppwy);
	if (wet) {
		dev_eww(nt->dev, "faiwed to enabwe suppwy (%d)\n", wet);
		wetuwn wet;
	}

	/* Assewt WESET */
	gpiod_set_vawue_cansweep(nt->weset_gpio, 1);
	udeway(20);
	/* De-assewt WESET */
	gpiod_set_vawue_cansweep(nt->weset_gpio, 0);
	usweep_wange(11000, 20000);

	wetuwn 0;
}

static void nt35560_powew_off(stwuct nt35560 *nt)
{
	/* Assewt WESET */
	gpiod_set_vawue_cansweep(nt->weset_gpio, 1);
	usweep_wange(11000, 20000);

	weguwatow_disabwe(nt->suppwy);
}

static int nt35560_pwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35560 *nt = panew_to_nt35560(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	const u8 mddi = 3;
	int wet;

	wet = nt35560_powew_on(nt);
	if (wet)
		wetuwn wet;

	wet = nt35560_wead_id(nt);
	if (wet) {
		dev_eww(nt->dev, "faiwed to wead panew ID (%d)\n", wet);
		goto eww_powew_off;
	}

	/* Enabe teawing mode: send TE (teawing effect) at VBWANK */
	wet = mipi_dsi_dcs_set_teaw_on(dsi,
				       MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet) {
		dev_eww(nt->dev, "faiwed to enabwe vbwank TE (%d)\n", wet);
		goto eww_powew_off;
	}

	/*
	 * Set MDDI
	 *
	 * This pwesumabwy deactivates the Quawcomm MDDI intewface and
	 * sewects DSI, simiwaw code is found in othew dwivews such as the
	 * Shawp WS043T1WE01 which makes us suspect that this panew may be
	 * using a Novatek NT35565 ow simiwaw dispway dwivew chip that shawes
	 * this command. Due to the wack of documentation we cannot know fow
	 * suwe.
	 */
	wet = mipi_dsi_dcs_wwite(dsi, NT35560_DCS_SET_MDDI,
				 &mddi, sizeof(mddi));
	if (wet < 0) {
		dev_eww(nt->dev, "faiwed to set MDDI (%d)\n", wet);
		goto eww_powew_off;
	}

	/* Exit sweep mode */
	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to exit sweep mode (%d)\n", wet);
		goto eww_powew_off;
	}
	msweep(140);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to tuwn dispway on (%d)\n", wet);
		goto eww_powew_off;
	}
	if (nt->video_mode) {
		/* In video mode tuwn pewiphewaw on */
		wet = mipi_dsi_tuwn_on_pewiphewaw(dsi);
		if (wet) {
			dev_eww(nt->dev, "faiwed to tuwn on pewiphewaw\n");
			goto eww_powew_off;
		}
	}

	wetuwn 0;

eww_powew_off:
	nt35560_powew_off(nt);
	wetuwn wet;
}

static int nt35560_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35560 *nt = panew_to_nt35560(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to tuwn dispway off (%d)\n", wet);
		wetuwn wet;
	}

	/* Entew sweep mode */
	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to entew sweep mode (%d)\n", wet);
		wetuwn wet;
	}
	msweep(85);

	nt35560_powew_off(nt);

	wetuwn 0;
}


static int nt35560_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct nt35560 *nt = panew_to_nt35560(panew);
	const stwuct nt35560_config *conf = nt->conf;
	stwuct dwm_dispway_mode *mode;

	if (nt->video_mode)
		mode = dwm_mode_dupwicate(connectow->dev,
					  conf->vid_mode);
	ewse
		mode = dwm_mode_dupwicate(connectow->dev,
					  conf->cmd_mode);
	if (!mode) {
		dev_eww(panew->dev, "bad mode ow faiwed to add mode\n");
		wetuwn -EINVAW;
	}
	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1; /* Numbew of modes */
}

static const stwuct dwm_panew_funcs nt35560_dwm_funcs = {
	.unpwepawe = nt35560_unpwepawe,
	.pwepawe = nt35560_pwepawe,
	.get_modes = nt35560_get_modes,
};

static int nt35560_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct nt35560 *nt;
	int wet;

	nt = devm_kzawwoc(dev, sizeof(stwuct nt35560), GFP_KEWNEW);
	if (!nt)
		wetuwn -ENOMEM;
	nt->video_mode = of_pwopewty_wead_boow(dev->of_node,
						"enfowce-video-mode");

	mipi_dsi_set_dwvdata(dsi, nt);
	nt->dev = dev;

	nt->conf = of_device_get_match_data(dev);
	if (!nt->conf) {
		dev_eww(dev, "missing device configuwation\n");
		wetuwn -ENODEV;
	}

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	/*
	 * FIXME: these come fwom the ST-Ewicsson vendow dwivew fow the
	 * HWEF520 and seems to wefwect wimitations in the PWWs on that
	 * pwatfowm, if you have the datasheet, pwease cwoss-check the
	 * actuaw max wates.
	 */
	dsi->wp_wate = 19200000;
	dsi->hs_wate = 420160000;

	if (nt->video_mode)
		/* Buwst mode using event fow sync */
		dsi->mode_fwags =
			MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_BUWST;
	ewse
		dsi->mode_fwags =
			MIPI_DSI_CWOCK_NON_CONTINUOUS;

	nt->suppwy = devm_weguwatow_get(dev, "vddi");
	if (IS_EWW(nt->suppwy))
		wetuwn PTW_EWW(nt->suppwy);

	/* This assewts WESET by defauwt */
	nt->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(nt->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nt->weset_gpio),
				     "faiwed to wequest GPIO\n");

	dwm_panew_init(&nt->panew, dev, &nt35560_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	nt->panew.backwight = devm_backwight_device_wegistew(dev, "nt35560", dev, nt,
					&nt35560_bw_ops, &nt35560_bw_pwops);
	if (IS_EWW(nt->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nt->panew.backwight),
				     "faiwed to wegistew backwight device\n");

	dwm_panew_add(&nt->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dwm_panew_wemove(&nt->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void nt35560_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct nt35560 *nt = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&nt->panew);
}

static const stwuct of_device_id nt35560_of_match[] = {
	{
		.compatibwe = "sony,acx424akp",
		.data = &sony_acx424akp_data,
	},
	{
		.compatibwe = "sony,acx424akm",
		.data = &sony_acx424akm_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, nt35560_of_match);

static stwuct mipi_dsi_dwivew nt35560_dwivew = {
	.pwobe = nt35560_pwobe,
	.wemove = nt35560_wemove,
	.dwivew = {
		.name = "panew-novatek-nt35560",
		.of_match_tabwe = nt35560_of_match,
	},
};
moduwe_mipi_dsi_dwivew(nt35560_dwivew);

MODUWE_AUTHOW("Winus Wawwei <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("MIPI-DSI Novatek NT35560 Panew Dwivew");
MODUWE_WICENSE("GPW v2");
