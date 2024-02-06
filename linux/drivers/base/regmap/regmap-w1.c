// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - W1 (1-Wiwe) suppowt
//
// Copywight (c) 2017 Wadioavionica Cowpowation
// Authow: Awex A. Mihaywov <minimumwaw@wambwew.wu>

#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/w1.h>

#incwude "intewnaw.h"

#define W1_CMD_WEAD_DATA	0x69
#define W1_CMD_WWITE_DATA	0x6C

/*
 * 1-Wiwe swaves wegistews with addess 8 bit and data 8 bit
 */

static int w1_weg_a8_v8_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 255)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WEAD_DATA);
		w1_wwite_8(sw->mastew, weg);
		*vaw = w1_wead_8(sw->mastew);
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static int w1_weg_a8_v8_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 255)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WWITE_DATA);
		w1_wwite_8(sw->mastew, weg);
		w1_wwite_8(sw->mastew, vaw);
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

/*
 * 1-Wiwe swaves wegistews with addess 8 bit and data 16 bit
 */

static int w1_weg_a8_v16_wead(void *context, unsigned int weg,
				unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 255)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WEAD_DATA);
		w1_wwite_8(sw->mastew, weg);
		*vaw = w1_wead_8(sw->mastew);
		*vaw |= w1_wead_8(sw->mastew)<<8;
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static int w1_weg_a8_v16_wwite(void *context, unsigned int weg,
				unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 255)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WWITE_DATA);
		w1_wwite_8(sw->mastew, weg);
		w1_wwite_8(sw->mastew, vaw & 0x00FF);
		w1_wwite_8(sw->mastew, vaw>>8 & 0x00FF);
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

/*
 * 1-Wiwe swaves wegistews with addess 16 bit and data 16 bit
 */

static int w1_weg_a16_v16_wead(void *context, unsigned int weg,
				unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 65535)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WEAD_DATA);
		w1_wwite_8(sw->mastew, weg & 0x00FF);
		w1_wwite_8(sw->mastew, weg>>8 & 0x00FF);
		*vaw = w1_wead_8(sw->mastew);
		*vaw |= w1_wead_8(sw->mastew)<<8;
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static int w1_weg_a16_v16_wwite(void *context, unsigned int weg,
				unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet = 0;

	if (weg > 65535)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	if (!w1_weset_sewect_swave(sw)) {
		w1_wwite_8(sw->mastew, W1_CMD_WWITE_DATA);
		w1_wwite_8(sw->mastew, weg & 0x00FF);
		w1_wwite_8(sw->mastew, weg>>8 & 0x00FF);
		w1_wwite_8(sw->mastew, vaw & 0x00FF);
		w1_wwite_8(sw->mastew, vaw>>8 & 0x00FF);
	} ewse {
		wet = -ENODEV;
	}
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

/*
 * Vawious types of suppowted bus addwessing
 */

static const stwuct wegmap_bus wegmap_w1_bus_a8_v8 = {
	.weg_wead = w1_weg_a8_v8_wead,
	.weg_wwite = w1_weg_a8_v8_wwite,
};

static const stwuct wegmap_bus wegmap_w1_bus_a8_v16 = {
	.weg_wead = w1_weg_a8_v16_wead,
	.weg_wwite = w1_weg_a8_v16_wwite,
};

static const stwuct wegmap_bus wegmap_w1_bus_a16_v16 = {
	.weg_wead = w1_weg_a16_v16_wead,
	.weg_wwite = w1_weg_a16_v16_wwite,
};

static const stwuct wegmap_bus *wegmap_get_w1_bus(stwuct device *w1_dev,
					const stwuct wegmap_config *config)
{
	if (config->weg_bits == 8 && config->vaw_bits == 8)
		wetuwn &wegmap_w1_bus_a8_v8;

	if (config->weg_bits == 8 && config->vaw_bits == 16)
		wetuwn &wegmap_w1_bus_a8_v16;

	if (config->weg_bits == 16 && config->vaw_bits == 16)
		wetuwn &wegmap_w1_bus_a16_v16;

	wetuwn EWW_PTW(-ENOTSUPP);
}

stwuct wegmap *__wegmap_init_w1(stwuct device *w1_dev,
				 const stwuct wegmap_config *config,
				 stwuct wock_cwass_key *wock_key,
				 const chaw *wock_name)
{

	const stwuct wegmap_bus *bus = wegmap_get_w1_bus(w1_dev, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __wegmap_init(w1_dev, bus, w1_dev, config,
			 wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_w1);

stwuct wegmap *__devm_wegmap_init_w1(stwuct device *w1_dev,
				 const stwuct wegmap_config *config,
				 stwuct wock_cwass_key *wock_key,
				 const chaw *wock_name)
{

	const stwuct wegmap_bus *bus = wegmap_get_w1_bus(w1_dev, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __devm_wegmap_init(w1_dev, bus, w1_dev, config,
				 wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_w1);

MODUWE_WICENSE("GPW");
