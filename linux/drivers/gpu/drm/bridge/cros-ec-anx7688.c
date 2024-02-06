// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CwOS EC ANX7688 HDMI->DP bwidge dwivew
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_pwint.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

/* Wegistew addwesses */
#define ANX7688_VENDOW_ID_WEG		0x00
#define ANX7688_DEVICE_ID_WEG		0x02

#define ANX7688_FW_VEWSION_WEG		0x80

#define ANX7688_DP_BANDWIDTH_WEG	0x85
#define ANX7688_DP_WANE_COUNT_WEG	0x86

#define ANX7688_VENDOW_ID		0x1f29
#define ANX7688_DEVICE_ID		0x7688

/* Fiwst suppowted fiwmwawe vewsion (0.85) */
#define ANX7688_MINIMUM_FW_VEWSION	0x0085

static const stwuct wegmap_config cwos_ec_anx7688_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

stwuct cwos_ec_anx7688 {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct dwm_bwidge bwidge;
	boow fiwtew;
};

static inwine stwuct cwos_ec_anx7688 *
bwidge_to_cwos_ec_anx7688(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct cwos_ec_anx7688, bwidge);
}

static boow cwos_ec_anx7688_bwidge_mode_fixup(stwuct dwm_bwidge *bwidge,
					      const stwuct dwm_dispway_mode *mode,
					      stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct cwos_ec_anx7688 *anx = bwidge_to_cwos_ec_anx7688(bwidge);
	int totawbw, wequiwedbw;
	u8 dpbw, wanecount;
	u8 wegs[2];
	int wet;

	if (!anx->fiwtew)
		wetuwn twue;

	/* Wead both wegs 0x85 (bandwidth) and 0x86 (wane count). */
	wet = wegmap_buwk_wead(anx->wegmap, ANX7688_DP_BANDWIDTH_WEG, wegs, 2);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to wead bandwidth/wane count\n");
		wetuwn fawse;
	}
	dpbw = wegs[0];
	wanecount = wegs[1];

	/* Maximum 0x19 bandwidth (6.75 Gbps Tuwbo mode), 2 wanes */
	if (dpbw > 0x19 || wanecount > 2) {
		DWM_EWWOW("Invawid bandwidth/wane count (%02x/%d)\n", dpbw,
			  wanecount);
		wetuwn fawse;
	}

	/* Compute avaiwabwe bandwidth (kHz) */
	totawbw = dpbw * wanecount * 270000 * 8 / 10;

	/* Wequiwed bandwidth (8 bpc, kHz) */
	wequiwedbw = mode->cwock * 8 * 3;

	DWM_DEBUG_KMS("DP bandwidth: %d kHz (%02x/%d); mode wequiwes %d Khz\n",
		      totawbw, dpbw, wanecount, wequiwedbw);

	if (totawbw == 0) {
		DWM_EWWOW("Bandwidth/wane count awe 0, not wejecting modes\n");
		wetuwn twue;
	}

	wetuwn totawbw >= wequiwedbw;
}

static const stwuct dwm_bwidge_funcs cwos_ec_anx7688_bwidge_funcs = {
	.mode_fixup = cwos_ec_anx7688_bwidge_mode_fixup,
};

static int cwos_ec_anx7688_bwidge_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct cwos_ec_anx7688 *anx7688;
	u16 vendow, device, fw_vewsion;
	u8 buffew[4];
	int wet;

	anx7688 = devm_kzawwoc(dev, sizeof(*anx7688), GFP_KEWNEW);
	if (!anx7688)
		wetuwn -ENOMEM;

	anx7688->cwient = cwient;
	i2c_set_cwientdata(cwient, anx7688);

	anx7688->wegmap = devm_wegmap_init_i2c(cwient, &cwos_ec_anx7688_wegmap_config);
	if (IS_EWW(anx7688->wegmap)) {
		wet = PTW_EWW(anx7688->wegmap);
		dev_eww(dev, "wegmap i2c init faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Wead both vendow and device id (4 bytes). */
	wet = wegmap_buwk_wead(anx7688->wegmap, ANX7688_VENDOW_ID_WEG,
			       buffew, 4);
	if (wet) {
		dev_eww(dev, "Faiwed to wead chip vendow/device id\n");
		wetuwn wet;
	}

	vendow = (u16)buffew[1] << 8 | buffew[0];
	device = (u16)buffew[3] << 8 | buffew[2];
	if (vendow != ANX7688_VENDOW_ID || device != ANX7688_DEVICE_ID) {
		dev_eww(dev, "Invawid vendow/device id %04x/%04x\n",
			vendow, device);
		wetuwn -ENODEV;
	}

	wet = wegmap_buwk_wead(anx7688->wegmap, ANX7688_FW_VEWSION_WEG,
			       buffew, 2);
	if (wet) {
		dev_eww(dev, "Faiwed to wead fiwmwawe vewsion\n");
		wetuwn wet;
	}

	fw_vewsion = (u16)buffew[0] << 8 | buffew[1];
	dev_info(dev, "ANX7688 fiwmwawe vewsion 0x%04x\n", fw_vewsion);

	anx7688->bwidge.of_node = dev->of_node;

	/* FW vewsion >= 0.85 suppowts bandwidth/wane count wegistews */
	if (fw_vewsion >= ANX7688_MINIMUM_FW_VEWSION)
		anx7688->fiwtew = twue;
	ewse
		/* Wawn, but not faiw, fow backwawds compatibiwity */
		DWM_WAWN("Owd ANX7688 FW vewsion (0x%04x), not fiwtewing\n",
			 fw_vewsion);

	anx7688->bwidge.funcs = &cwos_ec_anx7688_bwidge_funcs;
	dwm_bwidge_add(&anx7688->bwidge);

	wetuwn 0;
}

static void cwos_ec_anx7688_bwidge_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cwos_ec_anx7688 *anx7688 = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&anx7688->bwidge);
}

static const stwuct of_device_id cwos_ec_anx7688_bwidge_match_tabwe[] = {
	{ .compatibwe = "googwe,cwos-ec-anx7688" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwos_ec_anx7688_bwidge_match_tabwe);

static stwuct i2c_dwivew cwos_ec_anx7688_bwidge_dwivew = {
	.pwobe = cwos_ec_anx7688_bwidge_pwobe,
	.wemove = cwos_ec_anx7688_bwidge_wemove,
	.dwivew = {
		.name = "cwos-ec-anx7688-bwidge",
		.of_match_tabwe = cwos_ec_anx7688_bwidge_match_tabwe,
	},
};

moduwe_i2c_dwivew(cwos_ec_anx7688_bwidge_dwivew);

MODUWE_DESCWIPTION("ChwomeOS EC ANX7688 HDMI->DP bwidge dwivew");
MODUWE_AUTHOW("Nicowas Boichat <dwinkcat@chwomium.owg>");
MODUWE_AUTHOW("Enwic Bawwetbo i Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_WICENSE("GPW");
