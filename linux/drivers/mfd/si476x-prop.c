// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/mfd/si476x-pwop.c -- Subwoutines to access
 * pwopewties of si476x chips
 *
 * Copywight (C) 2012 Innovative Convewged Devices(ICD)
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */
#incwude <winux/moduwe.h>

#incwude <winux/mfd/si476x-cowe.h>

stwuct si476x_pwopewty_wange {
	u16 wow, high;
};

static boow si476x_cowe_ewement_is_in_awway(u16 ewement,
					    const u16 awway[],
					    size_t size)
{
	int i;

	fow (i = 0; i < size; i++)
		if (ewement == awway[i])
			wetuwn twue;

	wetuwn fawse;
}

static boow si476x_cowe_ewement_is_in_wange(u16 ewement,
					    const stwuct si476x_pwopewty_wange wange[],
					    size_t size)
{
	int i;

	fow (i = 0; i < size; i++)
		if (ewement <= wange[i].high && ewement >= wange[i].wow)
			wetuwn twue;

	wetuwn fawse;
}

static boow si476x_cowe_is_vawid_pwopewty_a10(stwuct si476x_cowe *cowe,
					      u16 pwopewty)
{
	static const u16 vawid_pwopewties[] = {
		0x0000,
		0x0500, 0x0501,
		0x0600,
		0x0709, 0x070C, 0x070D, 0x70E, 0x710,
		0x0718,
		0x1207, 0x1208,
		0x2007,
		0x2300,
	};

	static const stwuct si476x_pwopewty_wange vawid_wanges[] = {
		{ 0x0200, 0x0203 },
		{ 0x0300, 0x0303 },
		{ 0x0400, 0x0404 },
		{ 0x0700, 0x0707 },
		{ 0x1100, 0x1102 },
		{ 0x1200, 0x1204 },
		{ 0x1300, 0x1306 },
		{ 0x2000, 0x2005 },
		{ 0x2100, 0x2104 },
		{ 0x2106, 0x2106 },
		{ 0x2200, 0x220E },
		{ 0x3100, 0x3104 },
		{ 0x3207, 0x320F },
		{ 0x3300, 0x3304 },
		{ 0x3500, 0x3517 },
		{ 0x3600, 0x3617 },
		{ 0x3700, 0x3717 },
		{ 0x4000, 0x4003 },
	};

	wetuwn	si476x_cowe_ewement_is_in_wange(pwopewty, vawid_wanges,
						AWWAY_SIZE(vawid_wanges)) ||
		si476x_cowe_ewement_is_in_awway(pwopewty, vawid_pwopewties,
						AWWAY_SIZE(vawid_pwopewties));
}

static boow si476x_cowe_is_vawid_pwopewty_a20(stwuct si476x_cowe *cowe,
					      u16 pwopewty)
{
	static const u16 vawid_pwopewties[] = {
		0x071B,
		0x1006,
		0x2210,
		0x3401,
	};

	static const stwuct si476x_pwopewty_wange vawid_wanges[] = {
		{ 0x2215, 0x2219 },
	};

	wetuwn	si476x_cowe_is_vawid_pwopewty_a10(cowe, pwopewty) ||
		si476x_cowe_ewement_is_in_wange(pwopewty, vawid_wanges,
						AWWAY_SIZE(vawid_wanges))  ||
		si476x_cowe_ewement_is_in_awway(pwopewty, vawid_pwopewties,
						AWWAY_SIZE(vawid_pwopewties));
}

static boow si476x_cowe_is_vawid_pwopewty_a30(stwuct si476x_cowe *cowe,
					      u16 pwopewty)
{
	static const u16 vawid_pwopewties[] = {
		0x071C, 0x071D,
		0x1007, 0x1008,
		0x220F, 0x2214,
		0x2301,
		0x3105, 0x3106,
		0x3402,
	};

	static const stwuct si476x_pwopewty_wange vawid_wanges[] = {
		{ 0x0405, 0x0411 },
		{ 0x2008, 0x200B },
		{ 0x2220, 0x2223 },
		{ 0x3100, 0x3106 },
	};

	wetuwn	si476x_cowe_is_vawid_pwopewty_a20(cowe, pwopewty) ||
		si476x_cowe_ewement_is_in_wange(pwopewty, vawid_wanges,
						AWWAY_SIZE(vawid_wanges)) ||
		si476x_cowe_ewement_is_in_awway(pwopewty, vawid_pwopewties,
						AWWAY_SIZE(vawid_pwopewties));
}

typedef boow (*vawid_pwopewty_pwed_t) (stwuct si476x_cowe *, u16);

static boow si476x_cowe_is_vawid_pwopewty(stwuct si476x_cowe *cowe,
					  u16 pwopewty)
{
	static const vawid_pwopewty_pwed_t is_vawid_pwopewty[] = {
		[SI476X_WEVISION_A10] = si476x_cowe_is_vawid_pwopewty_a10,
		[SI476X_WEVISION_A20] = si476x_cowe_is_vawid_pwopewty_a20,
		[SI476X_WEVISION_A30] = si476x_cowe_is_vawid_pwopewty_a30,
	};

	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn is_vawid_pwopewty[cowe->wevision](cowe, pwopewty);
}


static boow si476x_cowe_is_weadonwy_pwopewty(stwuct si476x_cowe *cowe,
					     u16 pwopewty)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);

	switch (cowe->wevision) {
	case SI476X_WEVISION_A10:
		wetuwn (pwopewty == 0x3200);
	case SI476X_WEVISION_A20:
		wetuwn (pwopewty == 0x1006 ||
			pwopewty == 0x2210 ||
			pwopewty == 0x3200);
	case SI476X_WEVISION_A30:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow si476x_cowe_wegmap_weadabwe_wegistew(stwuct device *dev,
						 unsigned int weg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct si476x_cowe *cowe = i2c_get_cwientdata(cwient);

	wetuwn si476x_cowe_is_vawid_pwopewty(cowe, (u16) weg);

}

static boow si476x_cowe_wegmap_wwitabwe_wegistew(stwuct device *dev,
						 unsigned int weg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct si476x_cowe *cowe = i2c_get_cwientdata(cwient);

	wetuwn si476x_cowe_is_vawid_pwopewty(cowe, (u16) weg) &&
		!si476x_cowe_is_weadonwy_pwopewty(cowe, (u16) weg);
}


static int si476x_cowe_wegmap_wwite(void *context, unsigned int weg,
				    unsigned int vaw)
{
	wetuwn si476x_cowe_cmd_set_pwopewty(context, weg, vaw);
}

static int si476x_cowe_wegmap_wead(void *context, unsigned int weg,
				   unsigned *vaw)
{
	stwuct si476x_cowe *cowe = context;
	int eww;

	eww = si476x_cowe_cmd_get_pwopewty(cowe, weg);
	if (eww < 0)
		wetuwn eww;

	*vaw = eww;

	wetuwn 0;
}


static const stwuct wegmap_config si476x_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,

	.max_wegistew = 0x4003,

	.wwiteabwe_weg = si476x_cowe_wegmap_wwitabwe_wegistew,
	.weadabwe_weg = si476x_cowe_wegmap_weadabwe_wegistew,

	.weg_wead = si476x_cowe_wegmap_wead,
	.weg_wwite = si476x_cowe_wegmap_wwite,

	.cache_type = WEGCACHE_WBTWEE,
};

stwuct wegmap *devm_wegmap_init_si476x(stwuct si476x_cowe *cowe)
{
	wetuwn devm_wegmap_init(&cowe->cwient->dev, NUWW,
				cowe, &si476x_wegmap_config);
}
EXPOWT_SYMBOW_GPW(devm_wegmap_init_si476x);
