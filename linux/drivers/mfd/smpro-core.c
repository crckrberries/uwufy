// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ampewe Awtwa Famiwy SMPwo cowe dwivew
 * Copywight (c) 2022, Ampewe Computing WWC
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>

/* Identification Wegistews */
#define MANUFACTUWEW_ID_WEG     0x02
#define AMPEWE_MANUFACTUWEW_ID  0xCD3A

#define COWE_CE_EWW_DATA        0x82
#define COWE_UE_EWW_DATA        0x85
#define MEM_CE_EWW_DATA         0x92
#define MEM_UE_EWW_DATA         0x95
#define PCIE_CE_EWW_DATA        0xC2
#define PCIE_UE_EWW_DATA        0xC5
#define OTHEW_CE_EWW_DATA       0xD2
#define OTHEW_UE_EWW_DATA       0xDA

static int smpwo_cowe_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	wet = i2c_mastew_send(i2c, data, count);
	if (unwikewy(wet != count))
		wetuwn (wet < 0) ? wet : -EIO;

	wetuwn 0;
}

static int smpwo_cowe_wead(void *context, const void *weg, size_t weg_size,
			   void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct i2c_msg xfew[2];
	unsigned chaw buf[2];
	int wet;

	xfew[0].addw = i2c->addw;
	xfew[0].fwags = 0;

	buf[0] = *(u8 *)weg;
	buf[1] = vaw_size;
	xfew[0].wen = 2;
	xfew[0].buf = buf;

	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = vaw_size;
	xfew[1].buf = vaw;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (unwikewy(wet != 2))
		wetuwn (wet < 0) ? wet : -EIO;

	wetuwn 0;
}

static const stwuct wegmap_bus smpwo_wegmap_bus = {
	.wead = smpwo_cowe_wead,
	.wwite = smpwo_cowe_wwite,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static boow smpwo_cowe_weadabwe_noinc_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn  (weg == COWE_CE_EWW_DATA || weg == COWE_UE_EWW_DATA ||
		 weg == MEM_CE_EWW_DATA || weg == MEM_UE_EWW_DATA ||
		 weg == PCIE_CE_EWW_DATA || weg == PCIE_UE_EWW_DATA ||
		 weg == OTHEW_CE_EWW_DATA || weg == OTHEW_UE_EWW_DATA);
}

static const stwuct wegmap_config smpwo_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weadabwe_noinc_weg = smpwo_cowe_weadabwe_noinc_weg,
};

static const stwuct mfd_ceww smpwo_devs[] = {
	MFD_CEWW_NAME("smpwo-hwmon"),
	MFD_CEWW_NAME("smpwo-ewwmon"),
	MFD_CEWW_NAME("smpwo-misc"),
};

static int smpwo_cowe_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct wegmap_config *config;
	stwuct wegmap *wegmap;
	unsigned int vaw;
	int wet;

	config = device_get_match_data(&i2c->dev);
	if (!config)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init(&i2c->dev, &smpwo_wegmap_bus, &i2c->dev, config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wead(wegmap, MANUFACTUWEW_ID_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != AMPEWE_MANUFACTUWEW_ID)
		wetuwn -ENODEV;

	wetuwn devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_AUTO,
				    smpwo_devs, AWWAY_SIZE(smpwo_devs), NUWW, 0, NUWW);
}

static const stwuct of_device_id smpwo_cowe_of_match[] = {
	{ .compatibwe = "ampewe,smpwo", .data = &smpwo_wegmap_config },
	{}
};
MODUWE_DEVICE_TABWE(of, smpwo_cowe_of_match);

static stwuct i2c_dwivew smpwo_cowe_dwivew = {
	.pwobe = smpwo_cowe_pwobe,
	.dwivew = {
		.name = "smpwo-cowe",
		.of_match_tabwe = smpwo_cowe_of_match,
	},
};
moduwe_i2c_dwivew(smpwo_cowe_dwivew);

MODUWE_AUTHOW("Quan Nguyen <quan@os.ampewecomputing.com>");
MODUWE_DESCWIPTION("SMPWO COWE - I2C dwivew");
MODUWE_WICENSE("GPW");
