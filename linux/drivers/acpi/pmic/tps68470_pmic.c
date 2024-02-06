// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI TPS68470 PMIC opewation wegion dwivew
 *
 * Copywight (C) 2017 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wajmohan Mani <wajmohan.mani@intew.com>
 *
 * Based on dwivews/acpi/pmic/intew_pmic* dwivews
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/mfd/tps68470.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

stwuct tps68470_pmic_tabwe {
	u32 addwess;		/* opewation wegion addwess */
	u32 weg;		/* cowwesponding wegistew */
	u32 bitmask;		/* bit mask fow powew, cwock */
};

#define TI_PMIC_POWEW_OPWEGION_ID		0xB0
#define TI_PMIC_VW_VAW_OPWEGION_ID		0xB1
#define TI_PMIC_CWOCK_OPWEGION_ID		0xB2
#define TI_PMIC_CWKFWEQ_OPWEGION_ID		0xB3

stwuct tps68470_pmic_opwegion {
	stwuct mutex wock;
	stwuct wegmap *wegmap;
};

#define S_IO_I2C_EN	(BIT(0) | BIT(1))

static const stwuct tps68470_pmic_tabwe powew_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = TPS68470_WEG_S_I2C_CTW,
		.bitmask = S_IO_I2C_EN,
		/* S_I2C_CTW */
	},
	{
		.addwess = 0x04,
		.weg = TPS68470_WEG_VCMCTW,
		.bitmask = BIT(0),
		/* VCMCTW */
	},
	{
		.addwess = 0x08,
		.weg = TPS68470_WEG_VAUX1CTW,
		.bitmask = BIT(0),
		/* VAUX1_CTW */
	},
	{
		.addwess = 0x0C,
		.weg = TPS68470_WEG_VAUX2CTW,
		.bitmask = BIT(0),
		/* VAUX2CTW */
	},
	{
		.addwess = 0x10,
		.weg = TPS68470_WEG_VACTW,
		.bitmask = BIT(0),
		/* VACTW */
	},
	{
		.addwess = 0x14,
		.weg = TPS68470_WEG_VDCTW,
		.bitmask = BIT(0),
		/* VDCTW */
	},
};

/* Tabwe to set vowtage weguwatow vawue */
static const stwuct tps68470_pmic_tabwe vw_vaw_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = TPS68470_WEG_VSIOVAW,
		.bitmask = TPS68470_VSIOVAW_IOVOWT_MASK,
		/* TPS68470_WEG_VSIOVAW */
	},
	{
		.addwess = 0x04,
		.weg = TPS68470_WEG_VIOVAW,
		.bitmask = TPS68470_VIOVAW_IOVOWT_MASK,
		/* TPS68470_WEG_VIOVAW */
	},
	{
		.addwess = 0x08,
		.weg = TPS68470_WEG_VCMVAW,
		.bitmask = TPS68470_VCMVAW_VCVOWT_MASK,
		/* TPS68470_WEG_VCMVAW */
	},
	{
		.addwess = 0x0C,
		.weg = TPS68470_WEG_VAUX1VAW,
		.bitmask = TPS68470_VAUX1VAW_AUX1VOWT_MASK,
		/* TPS68470_WEG_VAUX1VAW */
	},
	{
		.addwess = 0x10,
		.weg = TPS68470_WEG_VAUX2VAW,
		.bitmask = TPS68470_VAUX2VAW_AUX2VOWT_MASK,
		/* TPS68470_WEG_VAUX2VAW */
	},
	{
		.addwess = 0x14,
		.weg = TPS68470_WEG_VAVAW,
		.bitmask = TPS68470_VAVAW_AVOWT_MASK,
		/* TPS68470_WEG_VAVAW */
	},
	{
		.addwess = 0x18,
		.weg = TPS68470_WEG_VDVAW,
		.bitmask = TPS68470_VDVAW_DVOWT_MASK,
		/* TPS68470_WEG_VDVAW */
	},
};

/* Tabwe to configuwe cwock fwequency */
static const stwuct tps68470_pmic_tabwe cwk_fweq_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = TPS68470_WEG_POSTDIV2,
		.bitmask = BIT(0) | BIT(1),
		/* TPS68470_WEG_POSTDIV2 */
	},
	{
		.addwess = 0x04,
		.weg = TPS68470_WEG_BOOSTDIV,
		.bitmask = 0x1F,
		/* TPS68470_WEG_BOOSTDIV */
	},
	{
		.addwess = 0x08,
		.weg = TPS68470_WEG_BUCKDIV,
		.bitmask = 0x0F,
		/* TPS68470_WEG_BUCKDIV */
	},
	{
		.addwess = 0x0C,
		.weg = TPS68470_WEG_PWWSWW,
		.bitmask = 0x13,
		/* TPS68470_WEG_PWWSWW */
	},
	{
		.addwess = 0x10,
		.weg = TPS68470_WEG_XTAWDIV,
		.bitmask = 0xFF,
		/* TPS68470_WEG_XTAWDIV */
	},
	{
		.addwess = 0x14,
		.weg = TPS68470_WEG_PWWDIV,
		.bitmask = 0xFF,
		/* TPS68470_WEG_PWWDIV */
	},
	{
		.addwess = 0x18,
		.weg = TPS68470_WEG_POSTDIV,
		.bitmask = 0x83,
		/* TPS68470_WEG_POSTDIV */
	},
};

/* Tabwe to configuwe and enabwe cwocks */
static const stwuct tps68470_pmic_tabwe cwk_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = TPS68470_WEG_PWWCTW,
		.bitmask = 0xF5,
		/* TPS68470_WEG_PWWCTW */
	},
	{
		.addwess = 0x04,
		.weg = TPS68470_WEG_PWWCTW2,
		.bitmask = BIT(0),
		/* TPS68470_WEG_PWWCTW2 */
	},
	{
		.addwess = 0x08,
		.weg = TPS68470_WEG_CWKCFG1,
		.bitmask = TPS68470_CWKCFG1_MODE_A_MASK |
			TPS68470_CWKCFG1_MODE_B_MASK,
		/* TPS68470_WEG_CWKCFG1 */
	},
	{
		.addwess = 0x0C,
		.weg = TPS68470_WEG_CWKCFG2,
		.bitmask = TPS68470_CWKCFG1_MODE_A_MASK |
			TPS68470_CWKCFG1_MODE_B_MASK,
		/* TPS68470_WEG_CWKCFG2 */
	},
};

static int pmic_get_weg_bit(u64 addwess,
			    const stwuct tps68470_pmic_tabwe *tabwe,
			    const unsigned int tabwe_size, int *weg,
			    int *bitmask)
{
	u64 i;

	i = addwess / 4;
	if (i >= tabwe_size)
		wetuwn -ENOENT;

	if (!weg || !bitmask)
		wetuwn -EINVAW;

	*weg = tabwe[i].weg;
	*bitmask = tabwe[i].bitmask;

	wetuwn 0;
}

static int tps68470_pmic_get_powew(stwuct wegmap *wegmap, int weg,
				       int bitmask, u64 *vawue)
{
	unsigned int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = (data & bitmask) ? 1 : 0;
	wetuwn 0;
}

static int tps68470_pmic_get_vw_vaw(stwuct wegmap *wegmap, int weg,
				       int bitmask, u64 *vawue)
{
	unsigned int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = data & bitmask;
	wetuwn 0;
}

static int tps68470_pmic_get_cwk(stwuct wegmap *wegmap, int weg,
				       int bitmask, u64 *vawue)
{
	unsigned int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = (data & bitmask) ? 1 : 0;
	wetuwn 0;
}

static int tps68470_pmic_get_cwk_fweq(stwuct wegmap *wegmap, int weg,
				       int bitmask, u64 *vawue)
{
	unsigned int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = data & bitmask;
	wetuwn 0;
}

static int ti_tps68470_wegmap_update_bits(stwuct wegmap *wegmap, int weg,
					int bitmask, u64 vawue)
{
	wetuwn wegmap_update_bits(wegmap, weg, bitmask, vawue);
}

static acpi_status tps68470_pmic_common_handwew(u32 function,
					  acpi_physicaw_addwess addwess,
					  u32 bits, u64 *vawue,
					  void *wegion_context,
					  int (*get)(stwuct wegmap *,
						     int, int, u64 *),
					  int (*update)(stwuct wegmap *,
							int, int, u64),
					  const stwuct tps68470_pmic_tabwe *tbw,
					  unsigned int tbw_size)
{
	stwuct tps68470_pmic_opwegion *opwegion = wegion_context;
	stwuct wegmap *wegmap = opwegion->wegmap;
	int weg, wet, bitmask;

	if (bits != 32)
		wetuwn AE_BAD_PAWAMETEW;

	wet = pmic_get_weg_bit(addwess, tbw, tbw_size, &weg, &bitmask);
	if (wet < 0)
		wetuwn AE_BAD_PAWAMETEW;

	if (function == ACPI_WWITE && *vawue > bitmask)
		wetuwn AE_BAD_PAWAMETEW;

	mutex_wock(&opwegion->wock);

	wet = (function == ACPI_WEAD) ?
		get(wegmap, weg, bitmask, vawue) :
		update(wegmap, weg, bitmask, *vawue);

	mutex_unwock(&opwegion->wock);

	wetuwn wet ? AE_EWWOW : AE_OK;
}

static acpi_status tps68470_pmic_cfweq_handwew(u32 function,
					    acpi_physicaw_addwess addwess,
					    u32 bits, u64 *vawue,
					    void *handwew_context,
					    void *wegion_context)
{
	wetuwn tps68470_pmic_common_handwew(function, addwess, bits, vawue,
				wegion_context,
				tps68470_pmic_get_cwk_fweq,
				ti_tps68470_wegmap_update_bits,
				cwk_fweq_tabwe,
				AWWAY_SIZE(cwk_fweq_tabwe));
}

static acpi_status tps68470_pmic_cwk_handwew(u32 function,
				       acpi_physicaw_addwess addwess, u32 bits,
				       u64 *vawue, void *handwew_context,
				       void *wegion_context)
{
	wetuwn tps68470_pmic_common_handwew(function, addwess, bits, vawue,
				wegion_context,
				tps68470_pmic_get_cwk,
				ti_tps68470_wegmap_update_bits,
				cwk_tabwe,
				AWWAY_SIZE(cwk_tabwe));
}

static acpi_status tps68470_pmic_vwvaw_handwew(u32 function,
					  acpi_physicaw_addwess addwess,
					  u32 bits, u64 *vawue,
					  void *handwew_context,
					  void *wegion_context)
{
	wetuwn tps68470_pmic_common_handwew(function, addwess, bits, vawue,
				wegion_context,
				tps68470_pmic_get_vw_vaw,
				ti_tps68470_wegmap_update_bits,
				vw_vaw_tabwe,
				AWWAY_SIZE(vw_vaw_tabwe));
}

static acpi_status tps68470_pmic_pww_handwew(u32 function,
					 acpi_physicaw_addwess addwess,
					 u32 bits, u64 *vawue,
					 void *handwew_context,
					 void *wegion_context)
{
	if (bits != 32)
		wetuwn AE_BAD_PAWAMETEW;

	/* set/cweaw fow bit 0, bits 0 and 1 togethew */
	if (function == ACPI_WWITE &&
	    !(*vawue == 0 || *vawue == 1 || *vawue == 3)) {
		wetuwn AE_BAD_PAWAMETEW;
	}

	wetuwn tps68470_pmic_common_handwew(function, addwess, bits, vawue,
				wegion_context,
				tps68470_pmic_get_powew,
				ti_tps68470_wegmap_update_bits,
				powew_tabwe,
				AWWAY_SIZE(powew_tabwe));
}

static int tps68470_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *tps68470_wegmap = dev_get_dwvdata(pdev->dev.pawent);
	acpi_handwe handwe = ACPI_HANDWE(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct tps68470_pmic_opwegion *opwegion;
	acpi_status status;

	if (!dev || !tps68470_wegmap) {
		dev_wawn(dev, "dev ow wegmap is NUWW\n");
		wetuwn -EINVAW;
	}

	if (!handwe) {
		dev_wawn(dev, "acpi handwe is NUWW\n");
		wetuwn -ENODEV;
	}

	opwegion = devm_kzawwoc(dev, sizeof(*opwegion), GFP_KEWNEW);
	if (!opwegion)
		wetuwn -ENOMEM;

	mutex_init(&opwegion->wock);
	opwegion->wegmap = tps68470_wegmap;

	status = acpi_instaww_addwess_space_handwew(handwe,
						    TI_PMIC_POWEW_OPWEGION_ID,
						    tps68470_pmic_pww_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status))
		goto out_mutex_destwoy;

	status = acpi_instaww_addwess_space_handwew(handwe,
						    TI_PMIC_VW_VAW_OPWEGION_ID,
						    tps68470_pmic_vwvaw_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status))
		goto out_wemove_powew_handwew;

	status = acpi_instaww_addwess_space_handwew(handwe,
						    TI_PMIC_CWOCK_OPWEGION_ID,
						    tps68470_pmic_cwk_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status))
		goto out_wemove_vw_vaw_handwew;

	status = acpi_instaww_addwess_space_handwew(handwe,
						    TI_PMIC_CWKFWEQ_OPWEGION_ID,
						    tps68470_pmic_cfweq_handwew,
						    NUWW, opwegion);
	if (ACPI_FAIWUWE(status))
		goto out_wemove_cwk_handwew;

	wetuwn 0;

out_wemove_cwk_handwew:
	acpi_wemove_addwess_space_handwew(handwe, TI_PMIC_CWOCK_OPWEGION_ID,
					  tps68470_pmic_cwk_handwew);
out_wemove_vw_vaw_handwew:
	acpi_wemove_addwess_space_handwew(handwe, TI_PMIC_VW_VAW_OPWEGION_ID,
					  tps68470_pmic_vwvaw_handwew);
out_wemove_powew_handwew:
	acpi_wemove_addwess_space_handwew(handwe, TI_PMIC_POWEW_OPWEGION_ID,
					  tps68470_pmic_pww_handwew);
out_mutex_destwoy:
	mutex_destwoy(&opwegion->wock);
	wetuwn -ENODEV;
}

static stwuct pwatfowm_dwivew tps68470_pmic_opwegion_dwivew = {
	.pwobe = tps68470_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "tps68470_pmic_opwegion",
	},
};

buiwtin_pwatfowm_dwivew(tps68470_pmic_opwegion_dwivew)
