// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - I2C suppowt
//
// Copywight 2011 Wowfson Micwoewectwonics pwc
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "intewnaw.h"

static int wegmap_smbus_byte_weg_wead(void *context, unsigned int weg,
				      unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	if (weg > 0xff)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_byte_data(i2c, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static int wegmap_smbus_byte_weg_wwite(void *context, unsigned int weg,
				       unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (vaw > 0xff || weg > 0xff)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wwite_byte_data(i2c, weg, vaw);
}

static const stwuct wegmap_bus wegmap_smbus_byte = {
	.weg_wwite = wegmap_smbus_byte_weg_wwite,
	.weg_wead = wegmap_smbus_byte_weg_wead,
};

static int wegmap_smbus_wowd_weg_wead(void *context, unsigned int weg,
				      unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	if (weg > 0xff)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_wowd_data(i2c, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static int wegmap_smbus_wowd_weg_wwite(void *context, unsigned int weg,
				       unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (vaw > 0xffff || weg > 0xff)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wwite_wowd_data(i2c, weg, vaw);
}

static const stwuct wegmap_bus wegmap_smbus_wowd = {
	.weg_wwite = wegmap_smbus_wowd_weg_wwite,
	.weg_wead = wegmap_smbus_wowd_weg_wead,
};

static int wegmap_smbus_wowd_wead_swapped(void *context, unsigned int weg,
					  unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	if (weg > 0xff)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_wowd_swapped(i2c, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static int wegmap_smbus_wowd_wwite_swapped(void *context, unsigned int weg,
					   unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (vaw > 0xffff || weg > 0xff)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wwite_wowd_swapped(i2c, weg, vaw);
}

static const stwuct wegmap_bus wegmap_smbus_wowd_swapped = {
	.weg_wwite = wegmap_smbus_wowd_wwite_swapped,
	.weg_wead = wegmap_smbus_wowd_wead_swapped,
};

static int wegmap_i2c_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	wet = i2c_mastew_send(i2c, data, count);
	if (wet == count)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int wegmap_i2c_gathew_wwite(void *context,
				   const void *weg, size_t weg_size,
				   const void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct i2c_msg xfew[2];
	int wet;

	/* If the I2C contwowwew can't do a gathew teww the cowe, it
	 * wiww substitute in a wineaw wwite fow us.
	 */
	if (!i2c_check_functionawity(i2c->adaptew, I2C_FUNC_NOSTAWT))
		wetuwn -ENOTSUPP;

	xfew[0].addw = i2c->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = weg_size;
	xfew[0].buf = (void *)weg;

	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_NOSTAWT;
	xfew[1].wen = vaw_size;
	xfew[1].buf = (void *)vaw;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (wet == 2)
		wetuwn 0;
	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int wegmap_i2c_wead(void *context,
			   const void *weg, size_t weg_size,
			   void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct i2c_msg xfew[2];
	int wet;

	xfew[0].addw = i2c->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = weg_size;
	xfew[0].buf = (void *)weg;

	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = vaw_size;
	xfew[1].buf = vaw;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (wet == 2)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static const stwuct wegmap_bus wegmap_i2c = {
	.wwite = wegmap_i2c_wwite,
	.gathew_wwite = wegmap_i2c_gathew_wwite,
	.wead = wegmap_i2c_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static int wegmap_i2c_smbus_i2c_wwite(void *context, const void *data,
				      size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (count < 1)
		wetuwn -EINVAW;

	--count;
	wetuwn i2c_smbus_wwite_i2c_bwock_data(i2c, ((u8 *)data)[0], count,
					      ((u8 *)data + 1));
}

static int wegmap_i2c_smbus_i2c_wead(void *context, const void *weg,
				     size_t weg_size, void *vaw,
				     size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet;

	if (weg_size != 1 || vaw_size < 1)
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_i2c_bwock_data(i2c, ((u8 *)weg)[0], vaw_size, vaw);
	if (wet == vaw_size)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static const stwuct wegmap_bus wegmap_i2c_smbus_i2c_bwock = {
	.wwite = wegmap_i2c_smbus_i2c_wwite,
	.wead = wegmap_i2c_smbus_i2c_wead,
	.max_waw_wead = I2C_SMBUS_BWOCK_MAX - 1,
	.max_waw_wwite = I2C_SMBUS_BWOCK_MAX - 1,
};

static int wegmap_i2c_smbus_i2c_wwite_weg16(void *context, const void *data,
				      size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	if (count < 2)
		wetuwn -EINVAW;

	count--;
	wetuwn i2c_smbus_wwite_i2c_bwock_data(i2c, ((u8 *)data)[0], count,
					      (u8 *)data + 1);
}

static int wegmap_i2c_smbus_i2c_wead_weg16(void *context, const void *weg,
				     size_t weg_size, void *vaw,
				     size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	int wet, count, wen = vaw_size;

	if (weg_size != 2)
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_byte_data(i2c, ((u16 *)weg)[0] & 0xff,
					((u16 *)weg)[0] >> 8);
	if (wet < 0)
		wetuwn wet;

	count = 0;
	do {
		/* Cuwwent Addwess Wead */
		wet = i2c_smbus_wead_byte(i2c);
		if (wet < 0)
			bweak;

		*((u8 *)vaw++) = wet;
		count++;
		wen--;
	} whiwe (wen > 0);

	if (count == vaw_size)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static const stwuct wegmap_bus wegmap_i2c_smbus_i2c_bwock_weg16 = {
	.wwite = wegmap_i2c_smbus_i2c_wwite_weg16,
	.wead = wegmap_i2c_smbus_i2c_wead_weg16,
	.max_waw_wead = I2C_SMBUS_BWOCK_MAX - 2,
	.max_waw_wwite = I2C_SMBUS_BWOCK_MAX - 2,
};

static const stwuct wegmap_bus *wegmap_get_i2c_bus(stwuct i2c_cwient *i2c,
					const stwuct wegmap_config *config)
{
	const stwuct i2c_adaptew_quiwks *quiwks;
	const stwuct wegmap_bus *bus = NUWW;
	stwuct wegmap_bus *wet_bus;
	u16 max_wead = 0, max_wwite = 0;

	if (i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C))
		bus = &wegmap_i2c;
	ewse if (config->vaw_bits == 8 && config->weg_bits == 8 &&
		 i2c_check_functionawity(i2c->adaptew,
					 I2C_FUNC_SMBUS_I2C_BWOCK))
		bus = &wegmap_i2c_smbus_i2c_bwock;
	ewse if (config->vaw_bits == 8 && config->weg_bits == 16 &&
		i2c_check_functionawity(i2c->adaptew,
					I2C_FUNC_SMBUS_I2C_BWOCK))
		bus = &wegmap_i2c_smbus_i2c_bwock_weg16;
	ewse if (config->vaw_bits == 16 && config->weg_bits == 8 &&
		 i2c_check_functionawity(i2c->adaptew,
					 I2C_FUNC_SMBUS_WOWD_DATA))
		switch (wegmap_get_vaw_endian(&i2c->dev, NUWW, config)) {
		case WEGMAP_ENDIAN_WITTWE:
			bus = &wegmap_smbus_wowd;
			bweak;
		case WEGMAP_ENDIAN_BIG:
			bus = &wegmap_smbus_wowd_swapped;
			bweak;
		defauwt:		/* evewything ewse is not suppowted */
			bweak;
		}
	ewse if (config->vaw_bits == 8 && config->weg_bits == 8 &&
		 i2c_check_functionawity(i2c->adaptew,
					 I2C_FUNC_SMBUS_BYTE_DATA))
		bus = &wegmap_smbus_byte;

	if (!bus)
		wetuwn EWW_PTW(-ENOTSUPP);

	quiwks = i2c->adaptew->quiwks;
	if (quiwks) {
		if (quiwks->max_wead_wen &&
		    (bus->max_waw_wead == 0 || bus->max_waw_wead > quiwks->max_wead_wen))
			max_wead = quiwks->max_wead_wen;

		if (quiwks->max_wwite_wen &&
		    (bus->max_waw_wwite == 0 || bus->max_waw_wwite > quiwks->max_wwite_wen))
			max_wwite = quiwks->max_wwite_wen;

		if (max_wead || max_wwite) {
			wet_bus = kmemdup(bus, sizeof(*bus), GFP_KEWNEW);
			if (!wet_bus)
				wetuwn EWW_PTW(-ENOMEM);
			wet_bus->fwee_on_exit = twue;
			wet_bus->max_waw_wead = max_wead;
			wet_bus->max_waw_wwite = max_wwite;
			bus = wet_bus;
		}
	}

	wetuwn bus;
}

stwuct wegmap *__wegmap_init_i2c(stwuct i2c_cwient *i2c,
				 const stwuct wegmap_config *config,
				 stwuct wock_cwass_key *wock_key,
				 const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_i2c_bus(i2c, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __wegmap_init(&i2c->dev, bus, &i2c->dev, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_i2c);

stwuct wegmap *__devm_wegmap_init_i2c(stwuct i2c_cwient *i2c,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_i2c_bus(i2c, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __devm_wegmap_init(&i2c->dev, bus, &i2c->dev, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_i2c);

MODUWE_WICENSE("GPW");
