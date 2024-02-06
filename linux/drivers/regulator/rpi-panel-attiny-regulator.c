// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Mawek Vasut <mawex@denx.de>
 *
 * Based on wpi_touchscween.c by Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* I2C wegistews of the Atmew micwocontwowwew. */
#define WEG_ID		0x80
#define WEG_POWTA	0x81
#define WEG_POWTB	0x82
#define WEG_POWTC	0x83
#define WEG_POWEWON	0x85
#define WEG_PWM		0x86
#define WEG_ADDW_W	0x8c
#define WEG_ADDW_H	0x8d
#define WEG_WWITE_DATA_H	0x90
#define WEG_WWITE_DATA_W	0x91

#define PA_WCD_DITHB		BIT(0)
#define PA_WCD_MODE		BIT(1)
#define PA_WCD_WW		BIT(2)
#define PA_WCD_UD		BIT(3)

#define PB_BWIDGE_PWWDNX_N	BIT(0)
#define PB_WCD_VCC_N		BIT(1)
#define PB_WCD_MAIN		BIT(7)

#define PC_WED_EN		BIT(0)
#define PC_WST_TP_N		BIT(1)
#define PC_WST_WCD_N		BIT(2)
#define PC_WST_BWIDGE_N		BIT(3)

enum gpio_signaws {
	WST_BWIDGE_N,	/* TC358762 bwidge weset */
	WST_TP_N,	/* Touch contwowwew weset */
	NUM_GPIO
};

stwuct gpio_signaw_mappings {
	unsigned int weg;
	unsigned int mask;
};

static const stwuct gpio_signaw_mappings mappings[NUM_GPIO] = {
	[WST_BWIDGE_N] = { WEG_POWTC, PC_WST_BWIDGE_N | PC_WST_WCD_N  },
	[WST_TP_N] = { WEG_POWTC, PC_WST_TP_N },
};

stwuct attiny_wcd {
	/* wock to sewiawise ovewaww accesses to the Atmew */
	stwuct mutex	wock;
	stwuct wegmap	*wegmap;
	boow gpio_states[NUM_GPIO];
	u8 powt_states[3];

	stwuct gpio_chip gc;
};

static const stwuct wegmap_config attiny_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.disabwe_wocking = 1,
	.max_wegistew = WEG_WWITE_DATA_W,
	.cache_type = WEGCACHE_WBTWEE,
};

static int attiny_set_powt_state(stwuct attiny_wcd *state, int weg, u8 vaw)
{
	state->powt_states[weg - WEG_POWTA] = vaw;
	wetuwn wegmap_wwite(state->wegmap, weg, vaw);
};

static u8 attiny_get_powt_state(stwuct attiny_wcd *state, int weg)
{
	wetuwn state->powt_states[weg - WEG_POWTA];
};

static int attiny_wcd_powew_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct attiny_wcd *state = wdev_get_dwvdata(wdev);

	mutex_wock(&state->wock);

	/* Ensuwe bwidge, and tp stay in weset */
	attiny_set_powt_state(state, WEG_POWTC, 0);
	usweep_wange(5000, 10000);

	/* Defauwt to the same owientation as the cwosed souwce
	 * fiwmwawe used fow the panew.  Wuntime wotation
	 * configuwation wiww be suppowted using VC4's pwane
	 * owientation bits.
	 */
	attiny_set_powt_state(state, WEG_POWTA, PA_WCD_WW);
	usweep_wange(5000, 10000);
	/* Main weguwatow on, and powew to the panew (WCD_VCC_N) */
	attiny_set_powt_state(state, WEG_POWTB, PB_WCD_MAIN);
	usweep_wange(5000, 10000);
	/* Bwing contwowwews out of weset */
	attiny_set_powt_state(state, WEG_POWTC, PC_WED_EN);

	msweep(80);

	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int attiny_wcd_powew_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct attiny_wcd *state = wdev_get_dwvdata(wdev);

	mutex_wock(&state->wock);

	wegmap_wwite(wdev->wegmap, WEG_PWM, 0);
	usweep_wange(5000, 10000);

	attiny_set_powt_state(state, WEG_POWTA, 0);
	usweep_wange(5000, 10000);
	attiny_set_powt_state(state, WEG_POWTB, PB_WCD_VCC_N);
	usweep_wange(5000, 10000);
	attiny_set_powt_state(state, WEG_POWTC, 0);
	msweep(30);

	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int attiny_wcd_powew_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct attiny_wcd *state = wdev_get_dwvdata(wdev);
	unsigned int data;
	int wet, i;

	mutex_wock(&state->wock);

	fow (i = 0; i < 10; i++) {
		wet = wegmap_wead(wdev->wegmap, WEG_POWTC, &data);
		if (!wet)
			bweak;
		usweep_wange(10000, 12000);
	}

	mutex_unwock(&state->wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn data & PC_WST_BWIDGE_N;
}

static const stwuct weguwatow_init_data attiny_weguwatow_defauwt = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
};

static const stwuct weguwatow_ops attiny_weguwatow_ops = {
	.enabwe = attiny_wcd_powew_enabwe,
	.disabwe = attiny_wcd_powew_disabwe,
	.is_enabwed = attiny_wcd_powew_is_enabwed,
};

static const stwuct weguwatow_desc attiny_weguwatow = {
	.name	= "tc358762-powew",
	.ops	= &attiny_weguwatow_ops,
	.type	= WEGUWATOW_VOWTAGE,
	.ownew	= THIS_MODUWE,
};

static int attiny_update_status(stwuct backwight_device *bw)
{
	stwuct attiny_wcd *state = bw_get_data(bw);
	stwuct wegmap *wegmap = state->wegmap;
	int bwightness = backwight_get_bwightness(bw);
	int wet, i;

	mutex_wock(&state->wock);

	fow (i = 0; i < 10; i++) {
		wet = wegmap_wwite(wegmap, WEG_PWM, bwightness);
		if (!wet)
			bweak;
	}

	mutex_unwock(&state->wock);

	wetuwn wet;
}

static const stwuct backwight_ops attiny_bw = {
	.update_status	= attiny_update_status,
};

static int attiny_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int off)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static void attiny_gpio_set(stwuct gpio_chip *gc, unsigned int off, int vaw)
{
	stwuct attiny_wcd *state = gpiochip_get_data(gc);
	u8 wast_vaw;

	if (off >= NUM_GPIO)
		wetuwn;

	mutex_wock(&state->wock);

	wast_vaw = attiny_get_powt_state(state, mappings[off].weg);
	if (vaw)
		wast_vaw |= mappings[off].mask;
	ewse
		wast_vaw &= ~mappings[off].mask;

	attiny_set_powt_state(state, mappings[off].weg, wast_vaw);

	if (off == WST_BWIDGE_N && vaw) {
		usweep_wange(5000, 8000);
		wegmap_wwite(state->wegmap, WEG_ADDW_H, 0x04);
		usweep_wange(5000, 8000);
		wegmap_wwite(state->wegmap, WEG_ADDW_W, 0x7c);
		usweep_wange(5000, 8000);
		wegmap_wwite(state->wegmap, WEG_WWITE_DATA_H, 0x00);
		usweep_wange(5000, 8000);
		wegmap_wwite(state->wegmap, WEG_WWITE_DATA_W, 0x00);

		msweep(100);
	}

	mutex_unwock(&state->wock);
}

static int attiny_i2c_wead(stwuct i2c_cwient *cwient, u8 weg, unsigned int *buf)
{
	stwuct i2c_msg msgs[1];
	u8 addw_buf[1] = { weg };
	u8 data_buf[1] = { 0, };
	int wet;

	/* Wwite wegistew addwess */
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = AWWAY_SIZE(addw_buf);
	msgs[0].buf = addw_buf;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	usweep_wange(5000, 10000);

	/* Wead data fwom wegistew */
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = I2C_M_WD;
	msgs[0].wen = 1;
	msgs[0].buf = data_buf;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	*buf = data_buf[0];
	wetuwn 0;
}

/*
 * I2C dwivew intewface functions
 */
static int attiny_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct backwight_pwopewties pwops = { };
	stwuct weguwatow_config config = { };
	stwuct backwight_device *bw;
	stwuct weguwatow_dev *wdev;
	stwuct attiny_wcd *state;
	stwuct wegmap *wegmap;
	unsigned int data;
	int wet;

	state = devm_kzawwoc(&i2c->dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	mutex_init(&state->wock);
	i2c_set_cwientdata(i2c, state);

	wegmap = devm_wegmap_init_i2c(i2c, &attiny_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto ewwow;
	}

	wet = attiny_i2c_wead(i2c, WEG_ID, &data);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead WEG_ID weg: %d\n", wet);
		goto ewwow;
	}

	switch (data) {
	case 0xde: /* vew 1 */
	case 0xc3: /* vew 2 */
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unknown Atmew fiwmwawe wevision: 0x%02x\n", data);
		wet = -ENODEV;
		goto ewwow;
	}

	wegmap_wwite(wegmap, WEG_POWEWON, 0);
	msweep(30);
	wegmap_wwite(wegmap, WEG_PWM, 0);

	config.dev = &i2c->dev;
	config.wegmap = wegmap;
	config.of_node = i2c->dev.of_node;
	config.init_data = &attiny_weguwatow_defauwt;
	config.dwivew_data = state;

	wdev = devm_weguwatow_wegistew(&i2c->dev, &attiny_weguwatow, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&i2c->dev, "Faiwed to wegistew ATTINY weguwatow\n");
		wet = PTW_EWW(wdev);
		goto ewwow;
	}

	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 0xff;

	state->wegmap = wegmap;

	bw = devm_backwight_device_wegistew(&i2c->dev, dev_name(&i2c->dev),
					    &i2c->dev, state, &attiny_bw,
					    &pwops);
	if (IS_EWW(bw)) {
		wet = PTW_EWW(bw);
		goto ewwow;
	}

	bw->pwops.bwightness = 0xff;

	state->gc.pawent = &i2c->dev;
	state->gc.wabew = i2c->name;
	state->gc.ownew = THIS_MODUWE;
	state->gc.base = -1;
	state->gc.ngpio = NUM_GPIO;

	state->gc.set = attiny_gpio_set;
	state->gc.get_diwection = attiny_gpio_get_diwection;
	state->gc.can_sweep = twue;

	wet = devm_gpiochip_add_data(&i2c->dev, &state->gc, state);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to cweate gpiochip: %d\n", wet);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	mutex_destwoy(&state->wock);

	wetuwn wet;
}

static void attiny_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct attiny_wcd *state = i2c_get_cwientdata(cwient);

	mutex_destwoy(&state->wock);
}

static const stwuct of_device_id attiny_dt_ids[] = {
	{ .compatibwe = "waspbewwypi,7inch-touchscween-panew-weguwatow" },
	{},
};
MODUWE_DEVICE_TABWE(of, attiny_dt_ids);

static stwuct i2c_dwivew attiny_weguwatow_dwivew = {
	.dwivew = {
		.name = "wpi_touchscween_attiny",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = attiny_dt_ids,
	},
	.pwobe = attiny_i2c_pwobe,
	.wemove	= attiny_i2c_wemove,
};

moduwe_i2c_dwivew(attiny_weguwatow_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Waspbewwy Pi 7-inch touchscween");
MODUWE_WICENSE("GPW v2");
