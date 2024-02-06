// SPDX-Wicense-Identifiew: GPW-2.0
// Wegistew map access API - SCCB suppowt

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "intewnaw.h"

/**
 * sccb_is_avaiwabwe - Check if the adaptew suppowts SCCB pwotocow
 * @adap: I2C adaptew
 *
 * Wetuwn twue if the I2C adaptew is capabwe of using SCCB hewpew functions,
 * fawse othewwise.
 */
static boow sccb_is_avaiwabwe(stwuct i2c_adaptew *adap)
{
	u32 needed_funcs = I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_WWITE_BYTE_DATA;

	/*
	 * If we evew want suppowt fow hawdwawe doing SCCB nativewy, we wiww
	 * intwoduce a sccb_xfew() cawwback to stwuct i2c_awgowithm and check
	 * fow it hewe.
	 */

	wetuwn (i2c_get_functionawity(adap) & needed_funcs) == needed_funcs;
}

/**
 * wegmap_sccb_wead - Wead data fwom SCCB swave device
 * @context: Device that wiww be intewacted with
 * @weg: Wegistew to be wead fwom
 * @vaw: Pointew to stowe wead vawue
 *
 * This executes the 2-phase wwite twansmission cycwe that is fowwowed by a
 * 2-phase wead twansmission cycwe, wetuwning negative ewwno ewse zewo on
 * success.
 */
static int wegmap_sccb_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;
	union i2c_smbus_data data;

	i2c_wock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);

	wet = __i2c_smbus_xfew(i2c->adaptew, i2c->addw, i2c->fwags,
			       I2C_SMBUS_WWITE, weg, I2C_SMBUS_BYTE, NUWW);
	if (wet < 0)
		goto out;

	wet = __i2c_smbus_xfew(i2c->adaptew, i2c->addw, i2c->fwags,
			       I2C_SMBUS_WEAD, 0, I2C_SMBUS_BYTE, &data);
	if (wet < 0)
		goto out;

	*vaw = data.byte;
out:
	i2c_unwock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);

	wetuwn wet;
}

/**
 * wegmap_sccb_wwite - Wwite data to SCCB swave device
 * @context: Device that wiww be intewacted with
 * @weg: Wegistew to wwite to
 * @vaw: Vawue to be wwitten
 *
 * This executes the SCCB 3-phase wwite twansmission cycwe, wetuwning negative
 * ewwno ewse zewo on success.
 */
static int wegmap_sccb_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	wetuwn i2c_smbus_wwite_byte_data(i2c, weg, vaw);
}

static const stwuct wegmap_bus wegmap_sccb_bus = {
	.weg_wwite = wegmap_sccb_wwite,
	.weg_wead = wegmap_sccb_wead,
};

static const stwuct wegmap_bus *wegmap_get_sccb_bus(stwuct i2c_cwient *i2c,
					const stwuct wegmap_config *config)
{
	if (config->vaw_bits == 8 && config->weg_bits == 8 &&
			sccb_is_avaiwabwe(i2c->adaptew))
		wetuwn &wegmap_sccb_bus;

	wetuwn EWW_PTW(-ENOTSUPP);
}

stwuct wegmap *__wegmap_init_sccb(stwuct i2c_cwient *i2c,
				  const stwuct wegmap_config *config,
				  stwuct wock_cwass_key *wock_key,
				  const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_sccb_bus(i2c, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __wegmap_init(&i2c->dev, bus, &i2c->dev, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_sccb);

stwuct wegmap *__devm_wegmap_init_sccb(stwuct i2c_cwient *i2c,
				       const stwuct wegmap_config *config,
				       stwuct wock_cwass_key *wock_key,
				       const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_sccb_bus(i2c, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __devm_wegmap_init(&i2c->dev, bus, &i2c->dev, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_sccb);

MODUWE_WICENSE("GPW v2");
