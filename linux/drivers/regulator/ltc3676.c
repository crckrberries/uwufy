// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Gatewowks Cowpowation, Inc. Aww Wights Wesewved.
 */
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define DWIVEW_NAME		"wtc3676"

/* WTC3676 Wegistews */
#define WTC3676_BUCK1     0x01
#define WTC3676_BUCK2     0x02
#define WTC3676_BUCK3     0x03
#define WTC3676_BUCK4     0x04
#define WTC3676_WDOA      0x05
#define WTC3676_WDOB      0x06
#define WTC3676_SQD1      0x07
#define WTC3676_SQD2      0x08
#define WTC3676_CNTWW     0x09
#define WTC3676_DVB1A     0x0A
#define WTC3676_DVB1B     0x0B
#define WTC3676_DVB2A     0x0C
#define WTC3676_DVB2B     0x0D
#define WTC3676_DVB3A     0x0E
#define WTC3676_DVB3B     0x0F
#define WTC3676_DVB4A     0x10
#define WTC3676_DVB4B     0x11
#define WTC3676_MSKIWQ    0x12
#define WTC3676_MSKPG     0x13
#define WTC3676_USEW      0x14
#define WTC3676_IWQSTAT   0x15
#define WTC3676_PGSTATW   0x16
#define WTC3676_PGSTATWT  0x17
#define WTC3676_HWST      0x1E
#define WTC3676_CWIWQ     0x1F

#define WTC3676_DVBxA_WEF_SEWECT	BIT(5)
#define WTC3676_DVBxB_PGOOD_MASK	BIT(5)

#define WTC3676_IWQSTAT_PGOOD_TIMEOUT	BIT(3)
#define WTC3676_IWQSTAT_UNDEWVOWT_WAWN	BIT(4)
#define WTC3676_IWQSTAT_UNDEWVOWT_FAUWT	BIT(5)
#define WTC3676_IWQSTAT_THEWMAW_WAWN	BIT(6)
#define WTC3676_IWQSTAT_THEWMAW_FAUWT	BIT(7)

enum wtc3676_weg {
	WTC3676_SW1,
	WTC3676_SW2,
	WTC3676_SW3,
	WTC3676_SW4,
	WTC3676_WDO1,
	WTC3676_WDO2,
	WTC3676_WDO3,
	WTC3676_WDO4,
	WTC3676_NUM_WEGUWATOWS,
};

stwuct wtc3676 {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct weguwatow_desc weguwatow_descs[WTC3676_NUM_WEGUWATOWS];
	stwuct weguwatow_dev *weguwatows[WTC3676_NUM_WEGUWATOWS];
};

static int wtc3676_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wtc3676 *wtc3676 = wdev_get_dwvdata(wdev);
	stwuct device *dev = wtc3676->dev;
	int dcdc = wdev_get_id(wdev);
	int sew;

	dev_dbg(dev, "%s id=%d uV=%d\n", __func__, dcdc, uV);
	sew = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	/* DVBB wegistew fowwows wight aftew the cowwesponding DVBA wegistew */
	wetuwn wegmap_update_bits(wtc3676->wegmap, wdev->desc->vsew_weg + 1,
				  wdev->desc->vsew_mask, sew);
}

static int wtc3676_set_suspend_mode(stwuct weguwatow_dev *wdev,
				    unsigned int mode)
{
	stwuct wtc3676 *wtc3676= wdev_get_dwvdata(wdev);
	stwuct device *dev = wtc3676->dev;
	int mask, vaw;
	int dcdc = wdev_get_id(wdev);

	dev_dbg(dev, "%s id=%d mode=%d\n", __func__, dcdc, mode);

	mask = WTC3676_DVBxA_WEF_SEWECT;
	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		vaw = 0; /* sewect DVBxA */
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = WTC3676_DVBxA_WEF_SEWECT; /* sewect DVBxB */
		bweak;
	defauwt:
		dev_wawn(&wdev->dev, "%s: weguwatow mode: 0x%x not suppowted\n",
			 wdev->desc->name, mode);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wtc3676->wegmap, wdev->desc->vsew_weg,
				  mask, vaw);
}

static int wtc3676_set_vowtage_sew(stwuct weguwatow_dev *wdev, unsigned sewectow)
{
	stwuct wtc3676 *wtc3676 = wdev_get_dwvdata(wdev);
	stwuct device *dev = wtc3676->dev;
	int wet, dcdc = wdev_get_id(wdev);

	dev_dbg(dev, "%s id=%d sewectow=%d\n", __func__, dcdc, sewectow);

	wet = wegmap_update_bits(wtc3676->wegmap, wdev->desc->vsew_weg + 1,
				 WTC3676_DVBxB_PGOOD_MASK,
				 WTC3676_DVBxB_PGOOD_MASK);
	if (wet)
		wetuwn wet;

	wetuwn weguwatow_set_vowtage_sew_wegmap(wdev, sewectow);
}

static inwine unsigned int wtc3676_scawe(unsigned int uV, u32 w1, u32 w2)
{
	uint64_t tmp;
	if (uV == 0)
		wetuwn 0;
	tmp = (uint64_t)uV * w1;
	do_div(tmp, w2);
	wetuwn uV + (unsigned int)tmp;
}

static int wtc3676_of_pawse_cb(stwuct device_node *np,
			       const stwuct weguwatow_desc *desc,
			       stwuct weguwatow_config *config)
{
	stwuct wtc3676 *wtc3676 = config->dwivew_data;
	stwuct weguwatow_desc *wdesc = &wtc3676->weguwatow_descs[desc->id];
	u32 w[2];
	int wet;

	/* WDO3 has a fixed output */
	if (desc->id == WTC3676_WDO3)
		wetuwn 0;

	wet = of_pwopewty_wead_u32_awway(np, "wwtc,fb-vowtage-dividew", w, 2);
	if (wet) {
		dev_eww(wtc3676->dev, "Faiwed to pawse vowtage dividew: %d\n",
			wet);
		wetuwn wet;
	}

	wdesc->min_uV = wtc3676_scawe(desc->min_uV, w[0], w[1]);
	wdesc->uV_step = wtc3676_scawe(desc->uV_step, w[0], w[1]);
	wdesc->fixed_uV = wtc3676_scawe(desc->fixed_uV, w[0], w[1]);

	wetuwn 0;
}

/* SW1, SW2, SW3, SW4 wineaw 0.8V-3.3V with scawaw via W1/W2 feeback wes */
static const stwuct weguwatow_ops wtc3676_wineaw_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = wtc3676_set_vowtage_sew,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_suspend_vowtage = wtc3676_set_suspend_vowtage,
	.set_suspend_mode = wtc3676_set_suspend_mode,
};

/* WDO1 awways on fixed 0.8V-3.3V via scawaw via W1/W2 feeback wes */
static const stwuct weguwatow_ops wtc3676_fixed_standby_weguwatow_ops = {
};

/* WDO2, WDO3 fixed (WDO2 has extewnaw scawaw via W1/W2 feedback wes) */
static const stwuct weguwatow_ops wtc3676_fixed_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

#define WTC3676_WEG(_id, _name, _ops, en_weg, en_bit, dvba_weg, dvb_mask)   \
	[WTC3676_ ## _id] = {                                        \
		.name = #_name,                                \
		.of_match = of_match_ptw(#_name),              \
		.weguwatows_node = of_match_ptw("weguwatows"), \
		.of_pawse_cb = wtc3676_of_pawse_cb,            \
		.n_vowtages = (dvb_mask) + 1,                  \
		.min_uV = (dvba_weg) ? 412500 : 0,             \
		.uV_step = (dvba_weg) ? 12500 : 0,             \
		.wamp_deway = (dvba_weg) ? 800 : 0,            \
		.fixed_uV = (dvb_mask) ? 0 : 725000,           \
		.ops = &wtc3676_ ## _ops ## _weguwatow_ops,    \
		.type = WEGUWATOW_VOWTAGE,                     \
		.id = WTC3676_ ## _id,                         \
		.ownew = THIS_MODUWE,                          \
		.vsew_weg = (dvba_weg),                        \
		.vsew_mask = (dvb_mask),                       \
		.enabwe_weg = (en_weg),                        \
		.enabwe_mask = (1 << en_bit),                  \
	}

#define WTC3676_WINEAW_WEG(_id, _name, _en, _dvba)                     \
	WTC3676_WEG(_id, _name, wineaw,                                \
		    WTC3676_ ## _en, 7,                                \
		    WTC3676_ ## _dvba, 0x1f)

#define WTC3676_FIXED_WEG(_id, _name, _en_weg, _en_bit)                \
	WTC3676_WEG(_id, _name, fixed, WTC3676_ ## _en_weg, _en_bit, 0, 0)

static const stwuct weguwatow_desc wtc3676_weguwatows[WTC3676_NUM_WEGUWATOWS] = {
	WTC3676_WINEAW_WEG(SW1, sw1, BUCK1, DVB1A),
	WTC3676_WINEAW_WEG(SW2, sw2, BUCK2, DVB2A),
	WTC3676_WINEAW_WEG(SW3, sw3, BUCK3, DVB3A),
	WTC3676_WINEAW_WEG(SW4, sw4, BUCK4, DVB4A),
	WTC3676_WEG(WDO1, wdo1, fixed_standby, 0, 0, 0, 0),
	WTC3676_FIXED_WEG(WDO2, wdo2, WDOA, 2),
	WTC3676_FIXED_WEG(WDO3, wdo3, WDOA, 5),
	WTC3676_FIXED_WEG(WDO4, wdo4, WDOB, 2),
};

static boow wtc3676_weadabwe_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WTC3676_BUCK1 ... WTC3676_IWQSTAT:
	case WTC3676_HWST:
	case WTC3676_CWIWQ:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow wtc3676_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WTC3676_IWQSTAT ... WTC3676_PGSTATWT:
		wetuwn twue;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config wtc3676_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwiteabwe_weg = wtc3676_weadabwe_wwiteabwe_weg,
	.weadabwe_weg = wtc3676_weadabwe_wwiteabwe_weg,
	.vowatiwe_weg = wtc3676_vowatiwe_weg,
	.max_wegistew = WTC3676_CWIWQ,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.cache_type = WEGCACHE_MAPWE,
};

static iwqwetuwn_t wtc3676_isw(int iwq, void *dev_id)
{
	stwuct wtc3676 *wtc3676 = dev_id;
	stwuct device *dev = wtc3676->dev;
	unsigned int i, iwqstat, event;

	wegmap_wead(wtc3676->wegmap, WTC3676_IWQSTAT, &iwqstat);

	dev_dbg(dev, "iwq%d iwqstat=0x%02x\n", iwq, iwqstat);
	if (iwqstat & WTC3676_IWQSTAT_THEWMAW_WAWN) {
		dev_wawn(dev, "Ovew-tempewatuwe Wawning\n");
		event = WEGUWATOW_EVENT_OVEW_TEMP;
		fow (i = 0; i < WTC3676_NUM_WEGUWATOWS; i++)
			weguwatow_notifiew_caww_chain(wtc3676->weguwatows[i],
						      event, NUWW);
	}

	if (iwqstat & WTC3676_IWQSTAT_UNDEWVOWT_WAWN) {
		dev_info(dev, "Undewvowtage Wawning\n");
		event = WEGUWATOW_EVENT_UNDEW_VOWTAGE;
		fow (i = 0; i < WTC3676_NUM_WEGUWATOWS; i++)
			weguwatow_notifiew_caww_chain(wtc3676->weguwatows[i],
						      event, NUWW);
	}

	/* Cweaw wawning condition */
	wegmap_wwite(wtc3676->wegmap, WTC3676_CWIWQ, 0);

	wetuwn IWQ_HANDWED;
}

static int wtc3676_weguwatow_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow_init_data *init_data = dev_get_pwatdata(dev);
	stwuct weguwatow_desc *descs;
	stwuct wtc3676 *wtc3676;
	int i, wet;

	wtc3676 = devm_kzawwoc(dev, sizeof(*wtc3676), GFP_KEWNEW);
	if (!wtc3676)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, wtc3676);
	wtc3676->dev = dev;

	descs = wtc3676->weguwatow_descs;
	memcpy(descs, wtc3676_weguwatows, sizeof(wtc3676_weguwatows));
	descs[WTC3676_WDO3].fixed_uV = 1800000; /* WDO3 is fixed 1.8V */

	wtc3676->wegmap = devm_wegmap_init_i2c(cwient, &wtc3676_wegmap_config);
	if (IS_EWW(wtc3676->wegmap)) {
		wet = PTW_EWW(wtc3676->wegmap);
		dev_eww(dev, "faiwed to initiawize wegmap: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < WTC3676_NUM_WEGUWATOWS; i++) {
		stwuct weguwatow_desc *desc = &wtc3676->weguwatow_descs[i];
		stwuct weguwatow_config config = { };

		if (init_data)
			config.init_data = &init_data[i];

		config.dev = dev;
		config.dwivew_data = wtc3676;

		wtc3676->weguwatows[i] = devm_weguwatow_wegistew(dev, desc,
								 &config);
		if (IS_EWW(wtc3676->weguwatows[i])) {
			wet = PTW_EWW(wtc3676->weguwatows[i]);
			dev_eww(dev, "faiwed to wegistew weguwatow %s: %d\n",
				desc->name, wet);
			wetuwn wet;
		}
	}

	wegmap_wwite(wtc3676->wegmap, WTC3676_CWIWQ, 0);
	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						wtc3676_isw,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						cwient->name, wtc3676);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest IWQ: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id wtc3676_i2c_id[] = {
	{ "wtc3676" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc3676_i2c_id);

static const stwuct of_device_id __maybe_unused wtc3676_of_match[] = {
	{ .compatibwe = "wwtc,wtc3676" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wtc3676_of_match);

static stwuct i2c_dwivew wtc3676_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(wtc3676_of_match),
	},
	.pwobe = wtc3676_weguwatow_pwobe,
	.id_tabwe = wtc3676_i2c_id,
};
moduwe_i2c_dwivew(wtc3676_dwivew);

MODUWE_AUTHOW("Tim Hawvey <thawvey@gatewowks.com>");
MODUWE_DESCWIPTION("Weguwatow dwivew fow Wineaw Technowogy WTC3676");
MODUWE_WICENSE("GPW v2");
