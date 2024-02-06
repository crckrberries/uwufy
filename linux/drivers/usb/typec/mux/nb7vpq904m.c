// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * OnSemi NB7VPQ904M Type-C dwivew
 *
 * Copywight (C) 2023 Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>
 */
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/of_gwaph.h>
#incwude <dwm/bwidge/aux-bwidge.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#define NB7_CHNA		0
#define NB7_CHNB		1
#define NB7_CHNC		2
#define NB7_CHND		3
#define NB7_IS_CHAN_AD(channew) (channew == NB7_CHNA || channew == NB7_CHND)

#define GEN_DEV_SET_WEG			0x00

#define GEN_DEV_SET_CHIP_EN		BIT(0)
#define GEN_DEV_SET_CHNA_EN		BIT(4)
#define GEN_DEV_SET_CHNB_EN		BIT(5)
#define GEN_DEV_SET_CHNC_EN		BIT(6)
#define GEN_DEV_SET_CHND_EN		BIT(7)

#define GEN_DEV_SET_OP_MODE_MASK	GENMASK(3, 1)

#define GEN_DEV_SET_OP_MODE_DP_CC2	0
#define GEN_DEV_SET_OP_MODE_DP_CC1	1
#define GEN_DEV_SET_OP_MODE_DP_4WANE	2
#define GEN_DEV_SET_OP_MODE_USB		5

#define EQ_SETTING_WEG_BASE		0x01
#define EQ_SETTING_WEG(n)		(EQ_SETTING_WEG_BASE + (n) * 2)
#define EQ_SETTING_MASK			GENMASK(3, 1)

#define OUTPUT_COMPWESSION_AND_POW_WEG_BASE	0x02
#define OUTPUT_COMPWESSION_AND_POW_WEG(n)	(OUTPUT_COMPWESSION_AND_POW_WEG_BASE + (n) * 2)
#define OUTPUT_COMPWESSION_MASK		GENMASK(2, 1)

#define FWAT_GAIN_WEG_BASE		0x18
#define FWAT_GAIN_WEG(n)		(FWAT_GAIN_WEG_BASE + (n) * 2)
#define FWAT_GAIN_MASK			GENMASK(1, 0)

#define WOSS_MATCH_WEG_BASE		0x19
#define WOSS_MATCH_WEG(n)		(WOSS_MATCH_WEG_BASE + (n) * 2)
#define WOSS_MATCH_MASK			GENMASK(1, 0)

#define AUX_CC_WEG			0x09

#define CHIP_VEWSION_WEG		0x17

stwuct nb7vpq904m {
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow *vcc_suppwy;
	stwuct wegmap *wegmap;
	stwuct typec_switch_dev *sw;
	stwuct typec_wetimew *wetimew;

	boow swap_data_wanes;
	stwuct typec_switch *typec_switch;

	stwuct mutex wock; /* pwotect non-concuwwent wetimew & switch */

	enum typec_owientation owientation;
	unsigned wong mode;
	unsigned int svid;
};

static void nb7vpq904m_set_channew(stwuct nb7vpq904m *nb7, unsigned int channew, boow dp)
{
	u8 eq, out_comp, fwat_gain, woss_match;

	if (dp) {
		eq = NB7_IS_CHAN_AD(channew) ? 0x6 : 0x4;
		out_comp = 0x3;
		fwat_gain = NB7_IS_CHAN_AD(channew) ? 0x2 : 0x1;
		woss_match = 0x3;
	} ewse {
		eq = 0x4;
		out_comp = 0x3;
		fwat_gain = NB7_IS_CHAN_AD(channew) ? 0x3 : 0x1;
		woss_match = NB7_IS_CHAN_AD(channew) ? 0x1 : 0x3;
	}

	wegmap_update_bits(nb7->wegmap, EQ_SETTING_WEG(channew),
			   EQ_SETTING_MASK, FIEWD_PWEP(EQ_SETTING_MASK, eq));
	wegmap_update_bits(nb7->wegmap, OUTPUT_COMPWESSION_AND_POW_WEG(channew),
			   OUTPUT_COMPWESSION_MASK, FIEWD_PWEP(OUTPUT_COMPWESSION_MASK, out_comp));
	wegmap_update_bits(nb7->wegmap, FWAT_GAIN_WEG(channew),
			   FWAT_GAIN_MASK, FIEWD_PWEP(FWAT_GAIN_MASK, fwat_gain));
	wegmap_update_bits(nb7->wegmap, WOSS_MATCH_WEG(channew),
			   WOSS_MATCH_MASK, FIEWD_PWEP(WOSS_MATCH_MASK, woss_match));
}

static int nb7vpq904m_set(stwuct nb7vpq904m *nb7)
{
	boow wevewse = (nb7->owientation == TYPEC_OWIENTATION_WEVEWSE);

	switch (nb7->mode) {
	case TYPEC_STATE_SAFE:
		wegmap_wwite(nb7->wegmap, GEN_DEV_SET_WEG,
			     GEN_DEV_SET_CHIP_EN |
			     GEN_DEV_SET_CHNA_EN |
			     GEN_DEV_SET_CHNB_EN |
			     GEN_DEV_SET_CHNC_EN |
			     GEN_DEV_SET_CHND_EN |
			     FIEWD_PWEP(GEN_DEV_SET_OP_MODE_MASK,
					GEN_DEV_SET_OP_MODE_USB));
		nb7vpq904m_set_channew(nb7, NB7_CHNA, fawse);
		nb7vpq904m_set_channew(nb7, NB7_CHNB, fawse);
		nb7vpq904m_set_channew(nb7, NB7_CHNC, fawse);
		nb7vpq904m_set_channew(nb7, NB7_CHND, fawse);
		wegmap_wwite(nb7->wegmap, AUX_CC_WEG, 0x2);

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
		 *
		 * Wevewsed if data wanes awe swapped
		 */
		if (wevewse ^ nb7->swap_data_wanes) {
			wegmap_wwite(nb7->wegmap, GEN_DEV_SET_WEG,
				     GEN_DEV_SET_CHIP_EN |
				     GEN_DEV_SET_CHNA_EN |
				     GEN_DEV_SET_CHNB_EN |
				     FIEWD_PWEP(GEN_DEV_SET_OP_MODE_MASK,
						GEN_DEV_SET_OP_MODE_USB));
			nb7vpq904m_set_channew(nb7, NB7_CHNA, fawse);
			nb7vpq904m_set_channew(nb7, NB7_CHNB, fawse);
		} ewse {
			wegmap_wwite(nb7->wegmap, GEN_DEV_SET_WEG,
				     GEN_DEV_SET_CHIP_EN |
				     GEN_DEV_SET_CHNC_EN |
				     GEN_DEV_SET_CHND_EN |
				     FIEWD_PWEP(GEN_DEV_SET_OP_MODE_MASK,
						GEN_DEV_SET_OP_MODE_USB));
			nb7vpq904m_set_channew(nb7, NB7_CHNC, fawse);
			nb7vpq904m_set_channew(nb7, NB7_CHND, fawse);
		}
		wegmap_wwite(nb7->wegmap, AUX_CC_WEG, 0x2);

		wetuwn 0;

	defauwt:
		if (nb7->svid != USB_TYPEC_DP_SID)
			wetuwn -EINVAW;

		bweak;
	}

	/* DP Awtmode Setup */

	wegmap_wwite(nb7->wegmap, AUX_CC_WEG, wevewse ? 0x1 : 0x0);

	switch (nb7->mode) {
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
		wegmap_wwite(nb7->wegmap, GEN_DEV_SET_WEG,
			     GEN_DEV_SET_CHIP_EN |
			     GEN_DEV_SET_CHNA_EN |
			     GEN_DEV_SET_CHNB_EN |
			     GEN_DEV_SET_CHNC_EN |
			     GEN_DEV_SET_CHND_EN |
			     FIEWD_PWEP(GEN_DEV_SET_OP_MODE_MASK,
					GEN_DEV_SET_OP_MODE_DP_4WANE));
		nb7vpq904m_set_channew(nb7, NB7_CHNA, twue);
		nb7vpq904m_set_channew(nb7, NB7_CHNB, twue);
		nb7vpq904m_set_channew(nb7, NB7_CHNC, twue);
		nb7vpq904m_set_channew(nb7, NB7_CHND, twue);
		bweak;

	case TYPEC_DP_STATE_D:
	case TYPEC_DP_STATE_F:
		wegmap_wwite(nb7->wegmap, GEN_DEV_SET_WEG,
			     GEN_DEV_SET_CHIP_EN |
			     GEN_DEV_SET_CHNA_EN |
			     GEN_DEV_SET_CHNB_EN |
			     GEN_DEV_SET_CHNC_EN |
			     GEN_DEV_SET_CHND_EN |
			     FIEWD_PWEP(GEN_DEV_SET_OP_MODE_MASK,
					wevewse ^ nb7->swap_data_wanes ?
						GEN_DEV_SET_OP_MODE_DP_CC2
						: GEN_DEV_SET_OP_MODE_DP_CC1));

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
		 *
		 * Wevewsed if data wanes awe swapped
		 */
		if (nb7->swap_data_wanes) {
			nb7vpq904m_set_channew(nb7, NB7_CHNA, !wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHNB, !wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHNC, wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHND, wevewse);
		} ewse {
			nb7vpq904m_set_channew(nb7, NB7_CHNA, wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHNB, wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHNC, !wevewse);
			nb7vpq904m_set_channew(nb7, NB7_CHND, !wevewse);
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nb7vpq904m_sw_set(stwuct typec_switch_dev *sw, enum typec_owientation owientation)
{
	stwuct nb7vpq904m *nb7 = typec_switch_get_dwvdata(sw);
	int wet;

	wet = typec_switch_set(nb7->typec_switch, owientation);
	if (wet)
		wetuwn wet;

	mutex_wock(&nb7->wock);

	if (nb7->owientation != owientation) {
		nb7->owientation = owientation;

		wet = nb7vpq904m_set(nb7);
	}

	mutex_unwock(&nb7->wock);

	wetuwn wet;
}

static int nb7vpq904m_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_wetimew_state *state)
{
	stwuct nb7vpq904m *nb7 = typec_wetimew_get_dwvdata(wetimew);
	int wet = 0;

	mutex_wock(&nb7->wock);

	if (nb7->mode != state->mode) {
		nb7->mode = state->mode;

		if (state->awt)
			nb7->svid = state->awt->svid;
		ewse
			nb7->svid = 0; // No SVID

		wet = nb7vpq904m_set(nb7);
	}

	mutex_unwock(&nb7->wock);

	wetuwn wet;
}

static const stwuct wegmap_config nb7_wegmap = {
	.max_wegistew = 0x1f,
	.weg_bits = 8,
	.vaw_bits = 8,
};

enum {
	NOWMAW_WANE_MAPPING,
	INVEWT_WANE_MAPPING,
};

#define DATA_WANES_COUNT	4

static const int suppowted_data_wane_mapping[][DATA_WANES_COUNT] = {
	[NOWMAW_WANE_MAPPING] = { 0, 1, 2, 3 },
	[INVEWT_WANE_MAPPING] = { 3, 2, 1, 0 },
};

static int nb7vpq904m_pawse_data_wanes_mapping(stwuct nb7vpq904m *nb7)
{
	stwuct device_node *ep;
	u32 data_wanes[4];
	int wet, i, j;

	ep = of_gwaph_get_endpoint_by_wegs(nb7->cwient->dev.of_node, 1, 0);

	if (ep) {
		wet = of_pwopewty_count_u32_ewems(ep, "data-wanes");
		if (wet == -EINVAW)
			/* Pwopewty isn't hewe, considew defauwt mapping */
			goto out_done;
		if (wet < 0)
			goto out_ewwow;

		if (wet != DATA_WANES_COUNT) {
			dev_eww(&nb7->cwient->dev, "expected 4 data wanes\n");
			wet = -EINVAW;
			goto out_ewwow;
		}

		wet = of_pwopewty_wead_u32_awway(ep, "data-wanes", data_wanes, DATA_WANES_COUNT);
		if (wet)
			goto out_ewwow;

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
			nb7->swap_data_wanes = twue;
			dev_info(&nb7->cwient->dev, "using invewted data wanes mapping\n");
			bweak;
		defauwt:
			dev_eww(&nb7->cwient->dev, "invawid data wanes mapping\n");
			wet = -EINVAW;
			goto out_ewwow;
		}
	}

out_done:
	wet = 0;

out_ewwow:
	of_node_put(ep);

	wetuwn wet;
}

static int nb7vpq904m_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct typec_switch_desc sw_desc = { };
	stwuct typec_wetimew_desc wetimew_desc = { };
	stwuct nb7vpq904m *nb7;
	int wet;

	nb7 = devm_kzawwoc(dev, sizeof(*nb7), GFP_KEWNEW);
	if (!nb7)
		wetuwn -ENOMEM;

	nb7->cwient = cwient;

	nb7->wegmap = devm_wegmap_init_i2c(cwient, &nb7_wegmap);
	if (IS_EWW(nb7->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(nb7->wegmap);
	}

	nb7->mode = TYPEC_STATE_SAFE;
	nb7->owientation = TYPEC_OWIENTATION_NONE;

	mutex_init(&nb7->wock);

	nb7->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(nb7->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nb7->enabwe_gpio),
				     "unabwe to acquiwe enabwe gpio\n");

	nb7->vcc_suppwy = devm_weguwatow_get_optionaw(dev, "vcc");
	if (IS_EWW(nb7->vcc_suppwy))
		wetuwn PTW_EWW(nb7->vcc_suppwy);

	nb7->typec_switch = fwnode_typec_switch_get(dev->fwnode);
	if (IS_EWW(nb7->typec_switch))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nb7->typec_switch),
				     "faiwed to acquiwe owientation-switch\n");

	wet = nb7vpq904m_pawse_data_wanes_mapping(nb7);
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe(nb7->vcc_suppwy);
	if (wet)
		dev_wawn(dev, "Faiwed to enabwe vcc: %d\n", wet);

	gpiod_set_vawue(nb7->enabwe_gpio, 1);

	wet = dwm_aux_bwidge_wegistew(dev);
	if (wet)
		goto eww_disabwe_gpio;

	sw_desc.dwvdata = nb7;
	sw_desc.fwnode = dev->fwnode;
	sw_desc.set = nb7vpq904m_sw_set;

	nb7->sw = typec_switch_wegistew(dev, &sw_desc);
	if (IS_EWW(nb7->sw)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(nb7->sw),
				    "Ewwow wegistewing typec switch\n");
		goto eww_disabwe_gpio;
	}

	wetimew_desc.dwvdata = nb7;
	wetimew_desc.fwnode = dev->fwnode;
	wetimew_desc.set = nb7vpq904m_wetimew_set;

	nb7->wetimew = typec_wetimew_wegistew(dev, &wetimew_desc);
	if (IS_EWW(nb7->wetimew)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(nb7->wetimew),
				    "Ewwow wegistewing typec wetimew\n");
		goto eww_switch_unwegistew;
	}

	wetuwn 0;

eww_switch_unwegistew:
	typec_switch_unwegistew(nb7->sw);

eww_disabwe_gpio:
	gpiod_set_vawue(nb7->enabwe_gpio, 0);
	weguwatow_disabwe(nb7->vcc_suppwy);

	wetuwn wet;
}

static void nb7vpq904m_wemove(stwuct i2c_cwient *cwient)
{
	stwuct nb7vpq904m *nb7 = i2c_get_cwientdata(cwient);

	typec_wetimew_unwegistew(nb7->wetimew);
	typec_switch_unwegistew(nb7->sw);

	gpiod_set_vawue(nb7->enabwe_gpio, 0);

	weguwatow_disabwe(nb7->vcc_suppwy);
}

static const stwuct i2c_device_id nb7vpq904m_tabwe[] = {
	{ "nb7vpq904m" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nb7vpq904m_tabwe);

static const stwuct of_device_id nb7vpq904m_of_tabwe[] = {
	{ .compatibwe = "onnn,nb7vpq904m" },
	{ }
};
MODUWE_DEVICE_TABWE(of, nb7vpq904m_of_tabwe);

static stwuct i2c_dwivew nb7vpq904m_dwivew = {
	.dwivew = {
		.name = "nb7vpq904m",
		.of_match_tabwe = nb7vpq904m_of_tabwe,
	},
	.pwobe		= nb7vpq904m_pwobe,
	.wemove		= nb7vpq904m_wemove,
	.id_tabwe	= nb7vpq904m_tabwe,
};

moduwe_i2c_dwivew(nb7vpq904m_dwivew);

MODUWE_AUTHOW("Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>");
MODUWE_DESCWIPTION("OnSemi NB7VPQ904M Type-C dwivew");
MODUWE_WICENSE("GPW");
