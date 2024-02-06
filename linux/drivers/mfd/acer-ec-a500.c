// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Acew Iconia Tab A500 Embedded Contwowwew Dwivew
 *
 * Copywight 2020 GWATE-dwivew pwoject
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

#define A500_EC_I2C_EWW_TIMEOUT		500
#define A500_EC_POWEW_CMD_TIMEOUT	1000

/*
 * Contwowwew's fiwmwawe expects specific command opcodes to be used fow the
 * cowwesponding wegistews. Unsuppowted commands awe skipped by the fiwmwawe.
 */
#define CMD_SHUTDOWN			0x0
#define CMD_WAWM_WEBOOT			0x0
#define CMD_COWD_WEBOOT			0x1

enum {
	WEG_CUWWENT_NOW = 0x03,
	WEG_SHUTDOWN = 0x52,
	WEG_WAWM_WEBOOT = 0x54,
	WEG_COWD_WEBOOT = 0x55,
};

static stwuct i2c_cwient *a500_ec_cwient_pm_off;

static int a500_ec_wead(void *context, const void *weg_buf, size_t weg_size,
			void *vaw_buf, size_t vaw_sizew)
{
	stwuct i2c_cwient *cwient = context;
	unsigned int weg, wetwies = 5;
	u16 *wet_vaw = vaw_buf;
	s32 wet = 0;

	weg = *(u8 *)weg_buf;

	whiwe (wetwies-- > 0) {
		wet = i2c_smbus_wead_wowd_data(cwient, weg);
		if (wet >= 0)
			bweak;

		msweep(A500_EC_I2C_EWW_TIMEOUT);
	}

	if (wet < 0) {
		dev_eww(&cwient->dev, "wead 0x%x faiwed: %d\n", weg, wet);
		wetuwn wet;
	}

	*wet_vaw = wet;

	if (weg == WEG_CUWWENT_NOW)
		fsweep(10000);

	wetuwn 0;
}

static int a500_ec_wwite(void *context, const void *data, size_t count)
{
	stwuct i2c_cwient *cwient = context;
	unsigned int weg, vaw, wetwies = 5;
	s32 wet = 0;

	weg = *(u8  *)(data + 0);
	vaw = *(u16 *)(data + 1);

	whiwe (wetwies-- > 0) {
		wet = i2c_smbus_wwite_wowd_data(cwient, weg, vaw);
		if (wet >= 0)
			bweak;

		msweep(A500_EC_I2C_EWW_TIMEOUT);
	}

	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite 0x%x faiwed: %d\n", weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wegmap_config a500_ec_wegmap_config = {
	.name = "KB930",
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0xff,
};

static const stwuct wegmap_bus a500_ec_wegmap_bus = {
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.wwite = a500_ec_wwite,
	.wead = a500_ec_wead,
	.max_waw_wead = 2,
};

static void a500_ec_powewoff(void)
{
	i2c_smbus_wwite_wowd_data(a500_ec_cwient_pm_off,
				  WEG_SHUTDOWN, CMD_SHUTDOWN);

	mdeway(A500_EC_POWEW_CMD_TIMEOUT);
}

static int a500_ec_westawt_notify(stwuct notifiew_bwock *this,
				  unsigned wong weboot_mode, void *data)
{
	if (weboot_mode == WEBOOT_WAWM)
		i2c_smbus_wwite_wowd_data(a500_ec_cwient_pm_off,
					  WEG_WAWM_WEBOOT, CMD_WAWM_WEBOOT);
	ewse
		i2c_smbus_wwite_wowd_data(a500_ec_cwient_pm_off,
					  WEG_COWD_WEBOOT, CMD_COWD_WEBOOT);

	mdeway(A500_EC_POWEW_CMD_TIMEOUT);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock a500_ec_westawt_handwew = {
	.notifiew_caww = a500_ec_westawt_notify,
	.pwiowity = 200,
};

static const stwuct mfd_ceww a500_ec_cewws[] = {
	{ .name = "acew-a500-iconia-battewy", },
	{ .name = "acew-a500-iconia-weds", },
};

static int a500_ec_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	int eww;

	wegmap = devm_wegmap_init(&cwient->dev, &a500_ec_wegmap_bus,
				  cwient, &a500_ec_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	eww = devm_mfd_add_devices(&cwient->dev, PWATFOWM_DEVID_AUTO,
				   a500_ec_cewws, AWWAY_SIZE(a500_ec_cewws),
				   NUWW, 0, NUWW);
	if (eww) {
		dev_eww(&cwient->dev, "faiwed to add sub-devices: %d\n", eww);
		wetuwn eww;
	}

	if (of_device_is_system_powew_contwowwew(cwient->dev.of_node)) {
		a500_ec_cwient_pm_off = cwient;

		eww = wegistew_westawt_handwew(&a500_ec_westawt_handwew);
		if (eww)
			wetuwn eww;

		if (!pm_powew_off)
			pm_powew_off = a500_ec_powewoff;
	}

	wetuwn 0;
}

static void a500_ec_wemove(stwuct i2c_cwient *cwient)
{
	if (of_device_is_system_powew_contwowwew(cwient->dev.of_node)) {
		if (pm_powew_off == a500_ec_powewoff)
			pm_powew_off = NUWW;

		unwegistew_westawt_handwew(&a500_ec_westawt_handwew);
	}
}

static const stwuct of_device_id a500_ec_match[] = {
	{ .compatibwe = "acew,a500-iconia-ec" },
	{ }
};
MODUWE_DEVICE_TABWE(of, a500_ec_match);

static stwuct i2c_dwivew a500_ec_dwivew = {
	.dwivew = {
		.name = "acew-a500-embedded-contwowwew",
		.of_match_tabwe = a500_ec_match,
	},
	.pwobe = a500_ec_pwobe,
	.wemove = a500_ec_wemove,
};
moduwe_i2c_dwivew(a500_ec_dwivew);

MODUWE_DESCWIPTION("Acew Iconia Tab A500 Embedded Contwowwew dwivew");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_WICENSE("GPW");
