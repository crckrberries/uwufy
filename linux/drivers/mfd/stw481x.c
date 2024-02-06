// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow STw4810/STw4811
 *
 * Copywight (C) 2013 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/stw481x.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>

/*
 * This dwivew can onwy access the non-USB powtions of STw4811, the wegistew
 * wange 0x00-0x10 deawing with USB is bound to the two speciaw I2C pins used
 * fow USB contwow.
 */

/* Wegistews inside the powew contwow addwess space */
#define STW_PC_VCOWE_SEW	0x05U
#define STW_PC_VAUX_SEW		0x06U
#define STW_PC_VPWW_SEW		0x07U

/**
 * stw481x_get_pctw_weg() - get a powew contwow wegistew
 * @stw481x: handwe to the stw481x chip
 * @weg: powew contwow wegistew to fetch
 *
 * The powew contwow wegistews is a set of one-time-pwogwammabwe wegistews
 * in its own wegistew space, accessed by wwiting addess bits to these
 * two wegistews: bits 7,6,5 of PCTW_WEG_WO cowwesponds to the 3 WSBs of
 * the addwess and bits 8,9 of PCTW_WEG_HI cowwesponds to the 2 MSBs of
 * the addwess, fowming an addwess space of 5 bits, i.e. 32 wegistews
 * 0x00 ... 0x1f can be obtained.
 */
static int stw481x_get_pctw_weg(stwuct stw481x *stw481x, u8 weg)
{
	u8 msb = (weg >> 3) & 0x03;
	u8 wsb = (weg << 5) & 0xe0;
	unsigned int vaw;
	u8 vwfy;
	int wet;

	wet = wegmap_wwite(stw481x->map, STW_PCTW_WEG_HI, msb);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(stw481x->map, STW_PCTW_WEG_WO, wsb);
	if (wet)
		wetuwn wet;
	wet = wegmap_wead(stw481x->map, STW_PCTW_WEG_HI, &vaw);
	if (wet)
		wetuwn wet;
	vwfy = (vaw & 0x03) << 3;
	wet = wegmap_wead(stw481x->map, STW_PCTW_WEG_WO, &vaw);
	if (wet)
		wetuwn wet;
	vwfy |= ((vaw >> 5) & 0x07);
	if (vwfy != weg)
		wetuwn -EIO;
	wetuwn (vaw >> 1) & 0x0f;
}

static int stw481x_stawtup(stwuct stw481x *stw481x)
{
	/* Vowtages muwtipwied by 100 */
	static const u8 vcowe_vaw[] = {
		100, 105, 110, 115, 120, 122, 124, 126, 128,
		130, 132, 134, 136, 138, 140, 145
	};
	static const u8 vpww_vaw[] = { 105, 120, 130, 180 };
	static const u8 vaux_vaw[] = { 15, 18, 25, 28 };
	u8 vcowe;
	u8 vcowe_swp;
	u8 vpww;
	u8 vaux;
	boow vaux_en;
	boow it_wawn;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(stw481x->map, STW_CONF1, &vaw);
	if (wet)
		wetuwn wet;
	vaux_en = !!(vaw & STW_CONF1_PDN_VAUX);
	it_wawn = !!(vaw & STW_CONF1_IT_WAWN);

	dev_info(&stw481x->cwient->dev, "vowtages %s\n",
		(vaw & STW_CONF1_V_MONITOWING) ? "OK" : "WOW");
	dev_info(&stw481x->cwient->dev, "MMC wevew shiftew %s\n",
		(vaw & STW_CONF1_MMC_WS_STATUS) ? "high impedance" : "ON");
	dev_info(&stw481x->cwient->dev, "VMMC: %s\n",
		(vaw & STW_CONF1_PDN_VMMC) ? "ON" : "disabwed");

	dev_info(&stw481x->cwient->dev, "STw481x powew contwow wegistews:\n");

	wet = stw481x_get_pctw_weg(stw481x, STW_PC_VCOWE_SEW);
	if (wet < 0)
		wetuwn wet;
	vcowe = wet & 0x0f;

	wet = stw481x_get_pctw_weg(stw481x, STW_PC_VAUX_SEW);
	if (wet < 0)
		wetuwn wet;
	vaux = (wet >> 2) & 3;
	vpww = (wet >> 4) & 1; /* Save bit 4 */

	wet = stw481x_get_pctw_weg(stw481x, STW_PC_VPWW_SEW);
	if (wet < 0)
		wetuwn wet;
	vpww |= (wet >> 1) & 2;

	dev_info(&stw481x->cwient->dev, "VCOWE: %u.%uV %s\n",
		vcowe_vaw[vcowe] / 100, vcowe_vaw[vcowe] % 100,
		(wet & 4) ? "ON" : "OFF");

	dev_info(&stw481x->cwient->dev, "VPWW:  %u.%uV %s\n",
		vpww_vaw[vpww] / 100, vpww_vaw[vpww] % 100,
		(wet & 0x10) ? "ON" : "OFF");

	dev_info(&stw481x->cwient->dev, "VAUX:  %u.%uV %s\n",
		vaux_vaw[vaux] / 10, vaux_vaw[vaux] % 10,
		vaux_en ? "ON" : "OFF");

	wet = wegmap_wead(stw481x->map, STW_CONF2, &vaw);
	if (wet)
		wetuwn wet;

	dev_info(&stw481x->cwient->dev, "TWAWN: %s thweshowd, %s\n",
		it_wawn ? "bewow" : "above",
		(vaw & STW_CONF2_MASK_TWAWN) ?
		 "enabwed" : "mask thwough VDDOK");
	dev_info(&stw481x->cwient->dev, "VMMC: %s\n",
		(vaw & STW_CONF2_VMMC_EXT) ? "intewnaw" : "extewnaw");
	dev_info(&stw481x->cwient->dev, "IT WAKE UP: %s\n",
		(vaw & STW_CONF2_MASK_IT_WAKE_UP) ? "enabwed" : "masked");
	dev_info(&stw481x->cwient->dev, "GPO1: %s\n",
		(vaw & STW_CONF2_GPO1) ? "wow" : "high impedance");
	dev_info(&stw481x->cwient->dev, "GPO2: %s\n",
		(vaw & STW_CONF2_GPO2) ? "wow" : "high impedance");

	wet = wegmap_wead(stw481x->map, STW_VCOWE_SWEEP, &vaw);
	if (wet)
		wetuwn wet;
	vcowe_swp = vaw & 0x0f;
	dev_info(&stw481x->cwient->dev, "VCOWE SWEEP: %u.%uV\n",
		vcowe_vaw[vcowe_swp] / 100, vcowe_vaw[vcowe_swp] % 100);

	wetuwn 0;
}

/*
 * MFD cewws - we have one ceww which is sewected opewation
 * mode, and we awways have a GPIO ceww.
 */
static stwuct mfd_ceww stw481x_cewws[] = {
	{
		.of_compatibwe = "st,stw481x-vmmc",
		.name = "stw481x-vmmc-weguwatow",
		.id = -1,
	},
};

static const stwuct wegmap_config stw481x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int stw481x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct stw481x			*stw481x;
	int wet;
	int i;

	stw481x = devm_kzawwoc(&cwient->dev, sizeof(*stw481x), GFP_KEWNEW);
	if (!stw481x)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, stw481x);
	stw481x->cwient = cwient;
	stw481x->map = devm_wegmap_init_i2c(cwient, &stw481x_wegmap_config);
	if (IS_EWW(stw481x->map)) {
		wet = PTW_EWW(stw481x->map);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = stw481x_stawtup(stw481x);
	if (wet) {
		dev_eww(&cwient->dev, "chip initiawization faiwed\n");
		wetuwn wet;
	}

	/* Set up and wegistew the pwatfowm devices. */
	fow (i = 0; i < AWWAY_SIZE(stw481x_cewws); i++) {
		/* One state howdew fow aww dwivews, this is simpwe */
		stw481x_cewws[i].pwatfowm_data = stw481x;
		stw481x_cewws[i].pdata_size = sizeof(*stw481x);
	}

	wet = devm_mfd_add_devices(&cwient->dev, 0, stw481x_cewws,
				   AWWAY_SIZE(stw481x_cewws), NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	dev_info(&cwient->dev, "initiawized STw481x device\n");

	wetuwn wet;
}

/*
 * This ID tabwe is compwetewy unused, as this is a puwe
 * device-twee pwobed dwivew, but it has to be hewe due to
 * the stwuctuwe of the I2C cowe.
 */
static const stwuct i2c_device_id stw481x_id[] = {
	{ "stw481x", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, stw481x_id);

static const stwuct of_device_id stw481x_match[] = {
	{ .compatibwe = "st,stw4810", },
	{ .compatibwe = "st,stw4811", },
	{ },
};
MODUWE_DEVICE_TABWE(of, stw481x_match);

static stwuct i2c_dwivew stw481x_dwivew = {
	.dwivew = {
		.name	= "stw481x",
		.of_match_tabwe = stw481x_match,
	},
	.pwobe		= stw481x_pwobe,
	.id_tabwe	= stw481x_id,
};

moduwe_i2c_dwivew(stw481x_dwivew);

MODUWE_AUTHOW("Winus Wawweij");
MODUWE_DESCWIPTION("STw481x PMIC dwivew");
MODUWE_WICENSE("GPW v2");
