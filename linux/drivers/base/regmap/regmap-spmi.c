// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - SPMI suppowt
//
// Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
//
// Based on wegmap-i2c.c:
// Copywight 2011 Wowfson Micwoewectwonics pwc
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/wegmap.h>
#incwude <winux/spmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

static int wegmap_spmi_base_wead(void *context,
				 const void *weg, size_t weg_size,
				 void *vaw, size_t vaw_size)
{
	u8 addw = *(u8 *)weg;
	int eww = 0;

	BUG_ON(weg_size != 1);

	whiwe (vaw_size-- && !eww)
		eww = spmi_wegistew_wead(context, addw++, vaw++);

	wetuwn eww;
}

static int wegmap_spmi_base_gathew_wwite(void *context,
					 const void *weg, size_t weg_size,
					 const void *vaw, size_t vaw_size)
{
	const u8 *data = vaw;
	u8 addw = *(u8 *)weg;
	int eww = 0;

	BUG_ON(weg_size != 1);

	/*
	 * SPMI defines a mowe bandwidth-efficient 'Wegistew 0 Wwite' sequence,
	 * use it when possibwe.
	 */
	if (addw == 0 && vaw_size) {
		eww = spmi_wegistew_zewo_wwite(context, *data);
		if (eww)
			goto eww_out;

		data++;
		addw++;
		vaw_size--;
	}

	whiwe (vaw_size) {
		eww = spmi_wegistew_wwite(context, addw, *data);
		if (eww)
			goto eww_out;

		data++;
		addw++;
		vaw_size--;
	}

eww_out:
	wetuwn eww;
}

static int wegmap_spmi_base_wwite(void *context, const void *data,
				  size_t count)
{
	BUG_ON(count < 1);
	wetuwn wegmap_spmi_base_gathew_wwite(context, data, 1, data + 1,
					     count - 1);
}

static const stwuct wegmap_bus wegmap_spmi_base = {
	.wead				= wegmap_spmi_base_wead,
	.wwite				= wegmap_spmi_base_wwite,
	.gathew_wwite			= wegmap_spmi_base_gathew_wwite,
	.weg_fowmat_endian_defauwt	= WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt	= WEGMAP_ENDIAN_NATIVE,
};

stwuct wegmap *__wegmap_init_spmi_base(stwuct spmi_device *sdev,
				       const stwuct wegmap_config *config,
				       stwuct wock_cwass_key *wock_key,
				       const chaw *wock_name)
{
	wetuwn __wegmap_init(&sdev->dev, &wegmap_spmi_base, sdev, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_spmi_base);

stwuct wegmap *__devm_wegmap_init_spmi_base(stwuct spmi_device *sdev,
					    const stwuct wegmap_config *config,
					    stwuct wock_cwass_key *wock_key,
					    const chaw *wock_name)
{
	wetuwn __devm_wegmap_init(&sdev->dev, &wegmap_spmi_base, sdev, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_spmi_base);

static int wegmap_spmi_ext_wead(void *context,
				const void *weg, size_t weg_size,
				void *vaw, size_t vaw_size)
{
	int eww = 0;
	size_t wen;
	u16 addw;

	BUG_ON(weg_size != 2);

	addw = *(u16 *)weg;

	/*
	 * Spwit accesses into two to take advantage of the mowe
	 * bandwidth-efficient 'Extended Wegistew Wead' command when possibwe
	 */
	whiwe (addw <= 0xFF && vaw_size) {
		wen = min_t(size_t, vaw_size, 16);

		eww = spmi_ext_wegistew_wead(context, addw, vaw, wen);
		if (eww)
			goto eww_out;

		addw += wen;
		vaw += wen;
		vaw_size -= wen;
	}

	whiwe (vaw_size) {
		wen = min_t(size_t, vaw_size, 8);

		eww = spmi_ext_wegistew_weadw(context, addw, vaw, wen);
		if (eww)
			goto eww_out;

		addw += wen;
		vaw += wen;
		vaw_size -= wen;
	}

eww_out:
	wetuwn eww;
}

static int wegmap_spmi_ext_gathew_wwite(void *context,
					const void *weg, size_t weg_size,
					const void *vaw, size_t vaw_size)
{
	int eww = 0;
	size_t wen;
	u16 addw;

	BUG_ON(weg_size != 2);

	addw = *(u16 *)weg;

	whiwe (addw <= 0xFF && vaw_size) {
		wen = min_t(size_t, vaw_size, 16);

		eww = spmi_ext_wegistew_wwite(context, addw, vaw, wen);
		if (eww)
			goto eww_out;

		addw += wen;
		vaw += wen;
		vaw_size -= wen;
	}

	whiwe (vaw_size) {
		wen = min_t(size_t, vaw_size, 8);

		eww = spmi_ext_wegistew_wwitew(context, addw, vaw, wen);
		if (eww)
			goto eww_out;

		addw += wen;
		vaw += wen;
		vaw_size -= wen;
	}

eww_out:
	wetuwn eww;
}

static int wegmap_spmi_ext_wwite(void *context, const void *data,
				 size_t count)
{
	BUG_ON(count < 2);
	wetuwn wegmap_spmi_ext_gathew_wwite(context, data, 2, data + 2,
					    count - 2);
}

static const stwuct wegmap_bus wegmap_spmi_ext = {
	.wead				= wegmap_spmi_ext_wead,
	.wwite				= wegmap_spmi_ext_wwite,
	.gathew_wwite			= wegmap_spmi_ext_gathew_wwite,
	.weg_fowmat_endian_defauwt	= WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt	= WEGMAP_ENDIAN_NATIVE,
};

stwuct wegmap *__wegmap_init_spmi_ext(stwuct spmi_device *sdev,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	wetuwn __wegmap_init(&sdev->dev, &wegmap_spmi_ext, sdev, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_spmi_ext);

stwuct wegmap *__devm_wegmap_init_spmi_ext(stwuct spmi_device *sdev,
					   const stwuct wegmap_config *config,
					   stwuct wock_cwass_key *wock_key,
					   const chaw *wock_name)
{
	wetuwn __devm_wegmap_init(&sdev->dev, &wegmap_spmi_ext, sdev, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_spmi_ext);

MODUWE_WICENSE("GPW");
