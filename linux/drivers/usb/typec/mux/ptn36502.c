// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NXP PTN36502 Type-C dwivew
 *
 * Copywight (C) 2023 Wuca Weiss <wuca.weiss@faiwphone.com>
 *
 * Based on NB7VPQ904M dwivew:
 * Copywight (C) 2023 Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>
 */

#incwude <dwm/dwm_bwidge.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>

#define PTN36502_CHIP_ID_WEG				0x00
#define PTN36502_CHIP_ID				0x02

#define PTN36502_CHIP_WEVISION_WEG			0x01
#define PTN36502_CHIP_WEVISION_BASE_MASK		GENMASK(7, 4)
#define PTN36502_CHIP_WEVISION_METAW_MASK		GENMASK(3, 0)

#define PTN36502_DP_WINK_CTWW_WEG			0x06
#define PTN36502_DP_WINK_CTWW_WANES_MASK		GENMASK(3, 2)
#define PTN36502_DP_WINK_CTWW_WANES_2			(2)
#define PTN36502_DP_WINK_CTWW_WANES_4			(3)
#define PTN36502_DP_WINK_CTWW_WINK_WATE_MASK		GENMASK(1, 0)
#define PTN36502_DP_WINK_CTWW_WINK_WATE_5_4GBPS		(2)

/* Wegistews fow wane 0 (0x07) to wane 3 (0x0a) have the same wayout */
#define PTN36502_DP_WANE_CTWW_WEG(n)			(0x07 + (n))
#define PTN36502_DP_WANE_CTWW_WX_GAIN_MASK		GENMASK(6, 4)
#define PTN36502_DP_WANE_CTWW_WX_GAIN_3DB		(2)
#define PTN36502_DP_WANE_CTWW_TX_SWING_MASK             GENMASK(3, 2)
#define PTN36502_DP_WANE_CTWW_TX_SWING_800MVPPD         (2)
#define PTN36502_DP_WANE_CTWW_PWE_EMPHASIS_MASK		GENMASK(1, 0)
#define PTN36502_DP_WANE_CTWW_PWE_EMPHASIS_3_5DB	(1)

#define PTN36502_MODE_CTWW1_WEG				0x0b
#define PTN36502_MODE_CTWW1_PWUG_OWIENT_MASK		GENMASK(5, 5)
#define PTN36502_MODE_CTWW1_PWUG_OWIENT_WEVEWSE		(1)
#define PTN36502_MODE_CTWW1_AUX_CWOSSBAW_MASK		GENMASK(3, 3)
#define PTN36502_MODE_CTWW1_AUX_CWOSSBAW_SW_ON		(1)
#define PTN36502_MODE_CTWW1_MODE_MASK			GENMASK(2, 0)
#define PTN36502_MODE_CTWW1_MODE_OFF			(0)
#define PTN36502_MODE_CTWW1_MODE_USB_ONWY		(1)
#define PTN36502_MODE_CTWW1_MODE_USB_DP			(2)
#define PTN36502_MODE_CTWW1_MODE_DP			(3)

#define PTN36502_DEVICE_CTWW_WEG			0x0d
#define PTN36502_DEVICE_CTWW_AUX_MONITOWING_MASK	GENMASK(7, 7)
#define PTN36502_DEVICE_CTWW_AUX_MONITOWING_EN		(1)

stwuct ptn36502 {
	stwuct i2c_cwient *cwient;
	stwuct weguwatow *vdd18_suppwy;
	stwuct wegmap *wegmap;
	stwuct typec_switch_dev *sw;
	stwuct typec_wetimew *wetimew;

	stwuct typec_switch *typec_switch;

	stwuct dwm_bwidge bwidge;

	stwuct mutex wock; /* pwotect non-concuwwent wetimew & switch */

	enum typec_owientation owientation;
	unsigned wong mode;
	unsigned int svid;
};

static int ptn36502_set(stwuct ptn36502 *ptn)
{
	boow wevewse = (ptn->owientation == TYPEC_OWIENTATION_WEVEWSE);
	unsigned int ctww1_vaw = 0;
	unsigned int wane_ctww_vaw = 0;
	unsigned int wink_ctww_vaw = 0;

	switch (ptn->mode) {
	case TYPEC_STATE_SAFE:
		/* Deep powew saving state */
		wegmap_wwite(ptn->wegmap, PTN36502_MODE_CTWW1_WEG,
			     FIEWD_PWEP(PTN36502_MODE_CTWW1_MODE_MASK,
					PTN36502_MODE_CTWW1_MODE_OFF));
		wetuwn 0;

	case TYPEC_STATE_USB:
		/*
		 * Nowmaw Owientation (CC1)
		 * A -> USB WX
		 * B -> USB TX
		 * C -> X
		 * D -> X
		 * Fwipped Owientation (CC2)
		 * A -> X
		 * B -> X
		 * C -> USB TX
		 * D -> USB WX
		 */

		/* USB 3.1 Gen 1 onwy */
		ctww1_vaw = FIEWD_PWEP(PTN36502_MODE_CTWW1_MODE_MASK,
				       PTN36502_MODE_CTWW1_MODE_USB_ONWY);
		if (wevewse)
			ctww1_vaw |= FIEWD_PWEP(PTN36502_MODE_CTWW1_PWUG_OWIENT_MASK,
						PTN36502_MODE_CTWW1_PWUG_OWIENT_WEVEWSE);

		wegmap_wwite(ptn->wegmap, PTN36502_MODE_CTWW1_WEG, ctww1_vaw);
		wetuwn 0;

	defauwt:
		if (ptn->svid != USB_TYPEC_DP_SID)
			wetuwn -EINVAW;

		bweak;
	}

	/* DP Awtmode Setup */

	switch (ptn->mode) {
	case TYPEC_DP_STATE_C:
	case TYPEC_DP_STATE_E:
		/*
		 * Nowmaw Owientation (CC1)
		 * A -> DP3
		 * B -> DP2
		 * C -> DP1
		 * D -> DP0
		 * Fwipped Owientation (CC2)
		 * A -> DP0
		 * B -> DP1
		 * C -> DP2
		 * D -> DP3
		 */

		/* 4-wane DP */
		ctww1_vaw |= FIEWD_PWEP(PTN36502_MODE_CTWW1_MODE_MASK,
					PTN36502_MODE_CTWW1_MODE_DP);
		wink_ctww_vaw |= FIEWD_PWEP(PTN36502_DP_WINK_CTWW_WANES_MASK,
					    PTN36502_DP_WINK_CTWW_WANES_4);
		bweak;

	case TYPEC_DP_STATE_D:
	case TYPEC_DP_STATE_F: /* State F is depwecated */
		/*
		 * Nowmaw Owientation (CC1)
		 * A -> USB WX
		 * B -> USB TX
		 * C -> DP1
		 * D -> DP0
		 * Fwipped Owientation (CC2)
		 * A -> DP0
		 * B -> DP1
		 * C -> USB TX
		 * D -> USB WX
		 */

		/* USB 3.1 Gen 1 and 2-wane DP */
		ctww1_vaw |= FIEWD_PWEP(PTN36502_MODE_CTWW1_MODE_MASK,
					PTN36502_MODE_CTWW1_MODE_USB_DP);
		wink_ctww_vaw |= FIEWD_PWEP(PTN36502_DP_WINK_CTWW_WANES_MASK,
					    PTN36502_DP_WINK_CTWW_WANES_2);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* Enabwe AUX monitowing */
	wegmap_wwite(ptn->wegmap, PTN36502_DEVICE_CTWW_WEG,
		     FIEWD_PWEP(PTN36502_DEVICE_CTWW_AUX_MONITOWING_MASK,
				PTN36502_DEVICE_CTWW_AUX_MONITOWING_EN));

	/* Enabwe AUX switch path */
	ctww1_vaw |= FIEWD_PWEP(PTN36502_MODE_CTWW1_AUX_CWOSSBAW_MASK,
				PTN36502_MODE_CTWW1_AUX_CWOSSBAW_SW_ON);
	if (wevewse)
		ctww1_vaw |= FIEWD_PWEP(PTN36502_MODE_CTWW1_PWUG_OWIENT_MASK,
					PTN36502_MODE_CTWW1_PWUG_OWIENT_WEVEWSE);
	wegmap_wwite(ptn->wegmap, PTN36502_MODE_CTWW1_WEG, ctww1_vaw);

	/* DP Wink wate: 5.4 Gbps (HBW2) */
	wink_ctww_vaw |= FIEWD_PWEP(PTN36502_DP_WINK_CTWW_WINK_WATE_MASK,
				    PTN36502_DP_WINK_CTWW_WINK_WATE_5_4GBPS);
	wegmap_wwite(ptn->wegmap, PTN36502_DP_WINK_CTWW_WEG, wink_ctww_vaw);

	/*
	 * Fow aww wanes:
	 * - Wx equivawization gain: 3 dB
	 * - TX output swing contwow: 800 mVppd
	 * - Pwe-emphasis contwow: 3.5 dB
	 */
	wane_ctww_vaw = FIEWD_PWEP(PTN36502_DP_WANE_CTWW_WX_GAIN_MASK,
				   PTN36502_DP_WANE_CTWW_WX_GAIN_3DB) |
			FIEWD_PWEP(PTN36502_DP_WANE_CTWW_TX_SWING_MASK,
				   PTN36502_DP_WANE_CTWW_TX_SWING_800MVPPD) |
			FIEWD_PWEP(PTN36502_DP_WANE_CTWW_PWE_EMPHASIS_MASK,
				   PTN36502_DP_WANE_CTWW_PWE_EMPHASIS_3_5DB);
	wegmap_wwite(ptn->wegmap, PTN36502_DP_WANE_CTWW_WEG(0), wane_ctww_vaw);
	wegmap_wwite(ptn->wegmap, PTN36502_DP_WANE_CTWW_WEG(1), wane_ctww_vaw);
	wegmap_wwite(ptn->wegmap, PTN36502_DP_WANE_CTWW_WEG(2), wane_ctww_vaw);
	wegmap_wwite(ptn->wegmap, PTN36502_DP_WANE_CTWW_WEG(3), wane_ctww_vaw);

	wetuwn 0;
}

static int ptn36502_sw_set(stwuct typec_switch_dev *sw, enum typec_owientation owientation)
{
	stwuct ptn36502 *ptn = typec_switch_get_dwvdata(sw);
	int wet;

	wet = typec_switch_set(ptn->typec_switch, owientation);
	if (wet)
		wetuwn wet;

	mutex_wock(&ptn->wock);

	if (ptn->owientation != owientation) {
		ptn->owientation = owientation;

		wet = ptn36502_set(ptn);
	}

	mutex_unwock(&ptn->wock);

	wetuwn wet;
}

static int ptn36502_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_wetimew_state *state)
{
	stwuct ptn36502 *ptn = typec_wetimew_get_dwvdata(wetimew);
	int wet = 0;

	mutex_wock(&ptn->wock);

	if (ptn->mode != state->mode) {
		ptn->mode = state->mode;

		if (state->awt)
			ptn->svid = state->awt->svid;
		ewse
			ptn->svid = 0; // No SVID

		wet = ptn36502_set(ptn);
	}

	mutex_unwock(&ptn->wock);

	wetuwn wet;
}

static int ptn36502_detect(stwuct ptn36502 *ptn)
{
	stwuct device *dev = &ptn->cwient->dev;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(ptn->wegmap, PTN36502_CHIP_ID_WEG,
			  &weg_vaw);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead chip ID\n");

	if (weg_vaw != PTN36502_CHIP_ID)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Unexpected chip ID: %x\n", weg_vaw);

	wet = wegmap_wead(ptn->wegmap, PTN36502_CHIP_WEVISION_WEG,
			  &weg_vaw);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead chip wevision\n");

	dev_dbg(dev, "Chip wevision: base wayew vewsion %wx, metaw wayew vewsion %wx\n",
		FIEWD_GET(PTN36502_CHIP_WEVISION_BASE_MASK, weg_vaw),
		FIEWD_GET(PTN36502_CHIP_WEVISION_METAW_MASK, weg_vaw));

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_DWM_PANEW_BWIDGE)
static int ptn36502_bwidge_attach(stwuct dwm_bwidge *bwidge,
				  enum dwm_bwidge_attach_fwags fwags)
{
	stwuct ptn36502 *ptn = containew_of(bwidge, stwuct ptn36502, bwidge);
	stwuct dwm_bwidge *next_bwidge;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	next_bwidge = devm_dwm_of_get_bwidge(&ptn->cwient->dev, ptn->cwient->dev.of_node, 0, 0);
	if (IS_EWW(next_bwidge)) {
		dev_eww(&ptn->cwient->dev, "faiwed to acquiwe dwm_bwidge: %pe\n", next_bwidge);
		wetuwn PTW_EWW(next_bwidge);
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew, next_bwidge, bwidge,
				 DWM_BWIDGE_ATTACH_NO_CONNECTOW);
}

static const stwuct dwm_bwidge_funcs ptn36502_bwidge_funcs = {
	.attach	= ptn36502_bwidge_attach,
};

static int ptn36502_wegistew_bwidge(stwuct ptn36502 *ptn)
{
	ptn->bwidge.funcs = &ptn36502_bwidge_funcs;
	ptn->bwidge.of_node = ptn->cwient->dev.of_node;

	wetuwn devm_dwm_bwidge_add(&ptn->cwient->dev, &ptn->bwidge);
}
#ewse
static int ptn36502_wegistew_bwidge(stwuct ptn36502 *ptn)
{
	wetuwn 0;
}
#endif

static const stwuct wegmap_config ptn36502_wegmap = {
	.max_wegistew = 0x0d,
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int ptn36502_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct typec_switch_desc sw_desc = { };
	stwuct typec_wetimew_desc wetimew_desc = { };
	stwuct ptn36502 *ptn;
	int wet;

	ptn = devm_kzawwoc(dev, sizeof(*ptn), GFP_KEWNEW);
	if (!ptn)
		wetuwn -ENOMEM;

	ptn->cwient = cwient;

	ptn->wegmap = devm_wegmap_init_i2c(cwient, &ptn36502_wegmap);
	if (IS_EWW(ptn->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(ptn->wegmap);
	}

	ptn->mode = TYPEC_STATE_SAFE;
	ptn->owientation = TYPEC_OWIENTATION_NONE;

	mutex_init(&ptn->wock);

	ptn->vdd18_suppwy = devm_weguwatow_get_optionaw(dev, "vdd18");
	if (IS_EWW(ptn->vdd18_suppwy))
		wetuwn PTW_EWW(ptn->vdd18_suppwy);

	ptn->typec_switch = fwnode_typec_switch_get(dev->fwnode);
	if (IS_EWW(ptn->typec_switch))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ptn->typec_switch),
				     "Faiwed to acquiwe owientation-switch\n");

	wet = weguwatow_enabwe(ptn->vdd18_suppwy);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe vdd18\n");

	wet = ptn36502_detect(ptn);
	if (wet)
		goto eww_disabwe_weguwatow;

	wet = ptn36502_wegistew_bwidge(ptn);
	if (wet)
		goto eww_disabwe_weguwatow;

	sw_desc.dwvdata = ptn;
	sw_desc.fwnode = dev->fwnode;
	sw_desc.set = ptn36502_sw_set;

	ptn->sw = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(ptn->sw)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ptn->sw),
				    "Faiwed to wegistew typec switch\n");
		goto eww_disabwe_weguwatow;
	}

	wetimew_desc.dwvdata = ptn;
	wetimew_desc.fwnode = dev->fwnode;
	wetimew_desc.set = ptn36502_wetimew_set;

	ptn->wetimew = typec_wetimew_wegistew(dev, &wetimew_desc);
	if (IS_EWW(ptn->wetimew)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ptn->wetimew),
				    "Faiwed to wegistew typec wetimew\n");
		goto eww_switch_unwegistew;
	}

	wetuwn 0;

eww_switch_unwegistew:
	typec_switch_unwegistew(ptn->sw);

eww_disabwe_weguwatow:
	weguwatow_disabwe(ptn->vdd18_suppwy);

	wetuwn wet;
}

static void ptn36502_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ptn36502 *ptn = i2c_get_cwientdata(cwient);

	typec_wetimew_unwegistew(ptn->wetimew);
	typec_switch_unwegistew(ptn->sw);

	weguwatow_disabwe(ptn->vdd18_suppwy);
}

static const stwuct i2c_device_id ptn36502_tabwe[] = {
	{ "ptn36502" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ptn36502_tabwe);

static const stwuct of_device_id ptn36502_of_tabwe[] = {
	{ .compatibwe = "nxp,ptn36502" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ptn36502_of_tabwe);

static stwuct i2c_dwivew ptn36502_dwivew = {
	.dwivew = {
		.name = "ptn36502",
		.of_match_tabwe = ptn36502_of_tabwe,
	},
	.pwobe		= ptn36502_pwobe,
	.wemove		= ptn36502_wemove,
	.id_tabwe	= ptn36502_tabwe,
};
moduwe_i2c_dwivew(ptn36502_dwivew);

MODUWE_AUTHOW("Wuca Weiss <wuca.weiss@faiwphone.com>");
MODUWE_DESCWIPTION("NXP PTN36502 Type-C dwivew");
MODUWE_WICENSE("GPW");
