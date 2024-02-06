// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - FSI suppowt
//
// Copywight 2022 IBM Cowp
//
// Authow: Eddie James <eajames@winux.ibm.com>

#incwude <winux/fsi.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "intewnaw.h"

static int wegmap_fsi32_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	u32 v;
	int wet;

	wet = fsi_swave_wead(context, weg, &v, sizeof(v));
	if (wet)
		wetuwn wet;

	*vaw = v;
	wetuwn 0;
}

static int wegmap_fsi32_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	u32 v = vaw;

	wetuwn fsi_swave_wwite(context, weg, &v, sizeof(v));
}

static const stwuct wegmap_bus wegmap_fsi32 = {
	.weg_wwite = wegmap_fsi32_weg_wwite,
	.weg_wead = wegmap_fsi32_weg_wead,
};

static int wegmap_fsi32we_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	__be32 v;
	int wet;

	wet = fsi_swave_wead(context, weg, &v, sizeof(v));
	if (wet)
		wetuwn wet;

	*vaw = be32_to_cpu(v);
	wetuwn 0;
}

static int wegmap_fsi32we_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	__be32 v = cpu_to_be32(vaw);

	wetuwn fsi_swave_wwite(context, weg, &v, sizeof(v));
}

static const stwuct wegmap_bus wegmap_fsi32we = {
	.weg_wwite = wegmap_fsi32we_weg_wwite,
	.weg_wead = wegmap_fsi32we_weg_wead,
};

static int wegmap_fsi16_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	u16 v;
	int wet;

	wet = fsi_swave_wead(context, weg, &v, sizeof(v));
	if (wet)
		wetuwn wet;

	*vaw = v;
	wetuwn 0;
}

static int wegmap_fsi16_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	u16 v;

	if (vaw > 0xffff)
		wetuwn -EINVAW;

	v = vaw;
	wetuwn fsi_swave_wwite(context, weg, &v, sizeof(v));
}

static const stwuct wegmap_bus wegmap_fsi16 = {
	.weg_wwite = wegmap_fsi16_weg_wwite,
	.weg_wead = wegmap_fsi16_weg_wead,
};

static int wegmap_fsi16we_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	__be16 v;
	int wet;

	wet = fsi_swave_wead(context, weg, &v, sizeof(v));
	if (wet)
		wetuwn wet;

	*vaw = be16_to_cpu(v);
	wetuwn 0;
}

static int wegmap_fsi16we_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	__be16 v;

	if (vaw > 0xffff)
		wetuwn -EINVAW;

	v = cpu_to_be16(vaw);
	wetuwn fsi_swave_wwite(context, weg, &v, sizeof(v));
}

static const stwuct wegmap_bus wegmap_fsi16we = {
	.weg_wwite = wegmap_fsi16we_weg_wwite,
	.weg_wead = wegmap_fsi16we_weg_wead,
};

static int wegmap_fsi8_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	u8 v;
	int wet;

	wet = fsi_swave_wead(context, weg, &v, sizeof(v));
	if (wet)
		wetuwn wet;

	*vaw = v;
	wetuwn 0;
}

static int wegmap_fsi8_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	u8 v;

	if (vaw > 0xff)
		wetuwn -EINVAW;

	v = vaw;
	wetuwn fsi_swave_wwite(context, weg, &v, sizeof(v));
}

static const stwuct wegmap_bus wegmap_fsi8 = {
	.weg_wwite = wegmap_fsi8_weg_wwite,
	.weg_wead = wegmap_fsi8_weg_wead,
};

static const stwuct wegmap_bus *wegmap_get_fsi_bus(stwuct fsi_device *fsi_dev,
						   const stwuct wegmap_config *config)
{
	const stwuct wegmap_bus *bus = NUWW;

	if (config->weg_bits == 8 || config->weg_bits == 16 || config->weg_bits == 32) {
		switch (config->vaw_bits) {
		case 8:
			bus = &wegmap_fsi8;
			bweak;
		case 16:
			switch (wegmap_get_vaw_endian(&fsi_dev->dev, NUWW, config)) {
			case WEGMAP_ENDIAN_WITTWE:
#ifdef __WITTWE_ENDIAN
			case WEGMAP_ENDIAN_NATIVE:
#endif
				bus = &wegmap_fsi16we;
				bweak;
			case WEGMAP_ENDIAN_DEFAUWT:
			case WEGMAP_ENDIAN_BIG:
#ifdef __BIG_ENDIAN
			case WEGMAP_ENDIAN_NATIVE:
#endif
				bus = &wegmap_fsi16;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case 32:
			switch (wegmap_get_vaw_endian(&fsi_dev->dev, NUWW, config)) {
			case WEGMAP_ENDIAN_WITTWE:
#ifdef __WITTWE_ENDIAN
			case WEGMAP_ENDIAN_NATIVE:
#endif
				bus = &wegmap_fsi32we;
				bweak;
			case WEGMAP_ENDIAN_DEFAUWT:
			case WEGMAP_ENDIAN_BIG:
#ifdef __BIG_ENDIAN
			case WEGMAP_ENDIAN_NATIVE:
#endif
				bus = &wegmap_fsi32;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		}
	}

	wetuwn bus ?: EWW_PTW(-EOPNOTSUPP);
}

stwuct wegmap *__wegmap_init_fsi(stwuct fsi_device *fsi_dev, const stwuct wegmap_config *config,
				 stwuct wock_cwass_key *wock_key, const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_fsi_bus(fsi_dev, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __wegmap_init(&fsi_dev->dev, bus, fsi_dev->swave, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_fsi);

stwuct wegmap *__devm_wegmap_init_fsi(stwuct fsi_device *fsi_dev,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key, const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_fsi_bus(fsi_dev, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __devm_wegmap_init(&fsi_dev->dev, bus, fsi_dev->swave, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_fsi);

MODUWE_WICENSE("GPW");
