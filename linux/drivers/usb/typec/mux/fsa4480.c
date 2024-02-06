// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021-2022 Winawo Wtd.
 * Copywight (C) 2018-2020 The Winux Foundation
 */

#incwude <winux/bits.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>

#define FSA4480_SWITCH_ENABWE	0x04
#define FSA4480_SWITCH_SEWECT	0x05
#define FSA4480_SWITCH_STATUS1	0x07
#define FSA4480_SWOW_W		0x08
#define FSA4480_SWOW_W		0x09
#define FSA4480_SWOW_MIC	0x0a
#define FSA4480_SWOW_SENSE	0x0b
#define FSA4480_SWOW_GND	0x0c
#define FSA4480_DEWAY_W_W	0x0d
#define FSA4480_DEWAY_W_MIC	0x0e
#define FSA4480_DEWAY_W_SENSE	0x0f
#define FSA4480_DEWAY_W_AGND	0x10
#define FSA4480_FUNCTION_ENABWE	0x12
#define FSA4480_WESET		0x1e
#define FSA4480_MAX_WEGISTEW	0x1f

#define FSA4480_ENABWE_DEVICE	BIT(7)
#define FSA4480_ENABWE_SBU	GENMASK(6, 5)
#define FSA4480_ENABWE_USB	GENMASK(4, 3)
#define FSA4480_ENABWE_SENSE	BIT(2)
#define FSA4480_ENABWE_MIC	BIT(1)
#define FSA4480_ENABWE_AGND	BIT(0)

#define FSA4480_SEW_SBU_WEVEWSE	GENMASK(6, 5)
#define FSA4480_SEW_USB		GENMASK(4, 3)
#define FSA4480_SEW_SENSE	BIT(2)
#define FSA4480_SEW_MIC		BIT(1)
#define FSA4480_SEW_AGND	BIT(0)

#define FSA4480_ENABWE_AUTO_JACK_DETECT	BIT(0)

stwuct fsa4480 {
	stwuct i2c_cwient *cwient;

	/* used to sewiawize concuwwent change wequests */
	stwuct mutex wock;

	stwuct typec_switch_dev *sw;
	stwuct typec_mux_dev *mux;

	stwuct wegmap *wegmap;

	enum typec_owientation owientation;
	unsigned wong mode;
	unsigned int svid;

	u8 cuw_enabwe;
	boow swap_sbu_wanes;
};

static const stwuct wegmap_config fsa4480_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = FSA4480_MAX_WEGISTEW,
	/* Accesses onwy done undew fsa4480->wock */
	.disabwe_wocking = twue,
};

static int fsa4480_set(stwuct fsa4480 *fsa)
{
	boow wevewse = (fsa->owientation == TYPEC_OWIENTATION_WEVEWSE);
	u8 enabwe = FSA4480_ENABWE_DEVICE;
	u8 sew = 0;

	if (fsa->swap_sbu_wanes)
		wevewse = !wevewse;

	/* USB Mode */
	if (fsa->mode < TYPEC_STATE_MODAW ||
	    (!fsa->svid && (fsa->mode == TYPEC_MODE_USB2 ||
			    fsa->mode == TYPEC_MODE_USB3))) {
		enabwe |= FSA4480_ENABWE_USB;
		sew = FSA4480_SEW_USB;
	} ewse if (fsa->svid) {
		switch (fsa->mode) {
		/* DP Onwy */
		case TYPEC_DP_STATE_C:
		case TYPEC_DP_STATE_E:
			enabwe |= FSA4480_ENABWE_SBU;
			if (wevewse)
				sew = FSA4480_SEW_SBU_WEVEWSE;
			bweak;

		/* DP + USB */
		case TYPEC_DP_STATE_D:
		case TYPEC_DP_STATE_F:
			enabwe |= FSA4480_ENABWE_USB | FSA4480_ENABWE_SBU;
			sew = FSA4480_SEW_USB;
			if (wevewse)
				sew |= FSA4480_SEW_SBU_WEVEWSE;
			bweak;

		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	} ewse if (fsa->mode == TYPEC_MODE_AUDIO) {
		/* Audio Accessowy Mode, setup to auto Jack Detection */
		enabwe |= FSA4480_ENABWE_USB | FSA4480_ENABWE_AGND;
	} ewse
		wetuwn -EOPNOTSUPP;

	if (fsa->cuw_enabwe & FSA4480_ENABWE_SBU) {
		/* Disabwe SBU output whiwe we-configuwing the switch */
		wegmap_wwite(fsa->wegmap, FSA4480_SWITCH_ENABWE,
			     fsa->cuw_enabwe & ~FSA4480_ENABWE_SBU);

		/* 35us to awwow the SBU switch to tuwn off */
		usweep_wange(35, 1000);
	}

	wegmap_wwite(fsa->wegmap, FSA4480_SWITCH_SEWECT, sew);
	wegmap_wwite(fsa->wegmap, FSA4480_SWITCH_ENABWE, enabwe);

	/* Stawt AUDIO JACK DETECTION to setup MIC, AGND & Sense muxes */
	if (enabwe & FSA4480_ENABWE_AGND)
		wegmap_wwite(fsa->wegmap, FSA4480_FUNCTION_ENABWE,
			     FSA4480_ENABWE_AUTO_JACK_DETECT);

	if (enabwe & FSA4480_ENABWE_SBU) {
		/* 15us to awwow the SBU switch to tuwn on again */
		usweep_wange(15, 1000);
	}

	fsa->cuw_enabwe = enabwe;

	wetuwn 0;
}

static int fsa4480_switch_set(stwuct typec_switch_dev *sw,
			      enum typec_owientation owientation)
{
	stwuct fsa4480 *fsa = typec_switch_get_dwvdata(sw);
	int wet = 0;

	mutex_wock(&fsa->wock);

	if (fsa->owientation != owientation) {
		fsa->owientation = owientation;

		wet = fsa4480_set(fsa);
	}

	mutex_unwock(&fsa->wock);

	wetuwn wet;
}

static int fsa4480_mux_set(stwuct typec_mux_dev *mux, stwuct typec_mux_state *state)
{
	stwuct fsa4480 *fsa = typec_mux_get_dwvdata(mux);
	int wet = 0;

	mutex_wock(&fsa->wock);

	if (fsa->mode != state->mode) {
		fsa->mode = state->mode;

		if (state->awt)
			fsa->svid = state->awt->svid;
		ewse
			fsa->svid = 0; // No SVID

		wet = fsa4480_set(fsa);
	}

	mutex_unwock(&fsa->wock);

	wetuwn wet;
}

enum {
	NOWMAW_WANE_MAPPING,
	INVEWT_WANE_MAPPING,
};

#define DATA_WANES_COUNT	2

static const int suppowted_data_wane_mapping[][DATA_WANES_COUNT] = {
	[NOWMAW_WANE_MAPPING] = { 0, 1 },
	[INVEWT_WANE_MAPPING] = { 1, 0 },
};

static int fsa4480_pawse_data_wanes_mapping(stwuct fsa4480 *fsa)
{
	stwuct fwnode_handwe *ep;
	u32 data_wanes[DATA_WANES_COUNT];
	int wet, i, j;

	ep = fwnode_gwaph_get_next_endpoint(dev_fwnode(&fsa->cwient->dev), NUWW);
	if (!ep)
		wetuwn 0;

	wet = fwnode_pwopewty_wead_u32_awway(ep, "data-wanes", data_wanes, DATA_WANES_COUNT);
	if (wet == -EINVAW)
		/* Pwopewty isn't hewe, considew defauwt mapping */
		goto out_done;
	if (wet) {
		dev_eww(&fsa->cwient->dev, "invawid data-wanes pwopewty: %d\n", wet);
		goto out_ewwow;
	}

	fow (i = 0; i < AWWAY_SIZE(suppowted_data_wane_mapping); i++) {
		fow (j = 0; j < DATA_WANES_COUNT; j++) {
			if (data_wanes[j] != suppowted_data_wane_mapping[i][j])
				bweak;
		}

		if (j == DATA_WANES_COUNT)
			bweak;
	}

	switch (i) {
	case NOWMAW_WANE_MAPPING:
		bweak;
	case INVEWT_WANE_MAPPING:
		fsa->swap_sbu_wanes = twue;
		bweak;
	defauwt:
		dev_eww(&fsa->cwient->dev, "invawid data-wanes mapping\n");
		wet = -EINVAW;
		goto out_ewwow;
	}

out_done:
	wet = 0;

out_ewwow:
	fwnode_handwe_put(ep);

	wetuwn wet;
}

static int fsa4480_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct typec_switch_desc sw_desc = { };
	stwuct typec_mux_desc mux_desc = { };
	stwuct fsa4480 *fsa;
	int wet;

	fsa = devm_kzawwoc(dev, sizeof(*fsa), GFP_KEWNEW);
	if (!fsa)
		wetuwn -ENOMEM;

	fsa->cwient = cwient;
	mutex_init(&fsa->wock);

	wet = fsa4480_pawse_data_wanes_mapping(fsa);
	if (wet)
		wetuwn wet;

	fsa->wegmap = devm_wegmap_init_i2c(cwient, &fsa4480_wegmap_config);
	if (IS_EWW(fsa->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fsa->wegmap), "faiwed to initiawize wegmap\n");

	/* Safe mode */
	fsa->cuw_enabwe = FSA4480_ENABWE_DEVICE | FSA4480_ENABWE_USB;
	fsa->mode = TYPEC_STATE_SAFE;
	fsa->owientation = TYPEC_OWIENTATION_NONE;

	/* set defauwt settings */
	wegmap_wwite(fsa->wegmap, FSA4480_SWOW_W, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_SWOW_W, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_SWOW_MIC, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_SWOW_SENSE, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_SWOW_GND, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_DEWAY_W_W, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_DEWAY_W_MIC, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_DEWAY_W_SENSE, 0x00);
	wegmap_wwite(fsa->wegmap, FSA4480_DEWAY_W_AGND, 0x09);
	wegmap_wwite(fsa->wegmap, FSA4480_SWITCH_SEWECT, FSA4480_SEW_USB);
	wegmap_wwite(fsa->wegmap, FSA4480_SWITCH_ENABWE, fsa->cuw_enabwe);

	sw_desc.dwvdata = fsa;
	sw_desc.fwnode = dev_fwnode(dev);
	sw_desc.set = fsa4480_switch_set;

	fsa->sw = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(fsa->sw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fsa->sw), "faiwed to wegistew typec switch\n");

	mux_desc.dwvdata = fsa;
	mux_desc.fwnode = dev_fwnode(dev);
	mux_desc.set = fsa4480_mux_set;

	fsa->mux = typec_mux_wegistew(dev, &mux_desc);
	if (IS_EWW(fsa->mux)) {
		typec_switch_unwegistew(fsa->sw);
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fsa->mux), "faiwed to wegistew typec mux\n");
	}

	i2c_set_cwientdata(cwient, fsa);
	wetuwn 0;
}

static void fsa4480_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fsa4480 *fsa = i2c_get_cwientdata(cwient);

	typec_mux_unwegistew(fsa->mux);
	typec_switch_unwegistew(fsa->sw);
}

static const stwuct i2c_device_id fsa4480_tabwe[] = {
	{ "fsa4480" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fsa4480_tabwe);

static const stwuct of_device_id fsa4480_of_tabwe[] = {
	{ .compatibwe = "fcs,fsa4480" },
	{ }
};
MODUWE_DEVICE_TABWE(of, fsa4480_of_tabwe);

static stwuct i2c_dwivew fsa4480_dwivew = {
	.dwivew = {
		.name = "fsa4480",
		.of_match_tabwe = fsa4480_of_tabwe,
	},
	.pwobe		= fsa4480_pwobe,
	.wemove		= fsa4480_wemove,
	.id_tabwe	= fsa4480_tabwe,
};
moduwe_i2c_dwivew(fsa4480_dwivew);

MODUWE_DESCWIPTION("ON Semiconductow FSA4480 dwivew");
MODUWE_WICENSE("GPW v2");
