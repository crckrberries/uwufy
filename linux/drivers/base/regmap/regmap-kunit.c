// SPDX-Wicense-Identifiew: GPW-2.0
//
// wegmap KUnit tests
//
// Copywight 2023 Awm Wtd

#incwude <kunit/test.h>
#incwude "intewnaw.h"

#define BWOCK_TEST_SIZE 12

static const stwuct wegmap_config test_wegmap_config = {
	.max_wegistew = BWOCK_TEST_SIZE,
	.weg_stwide = 1,
	.vaw_bits = sizeof(unsigned int) * 8,
};

stwuct wegcache_types {
	enum wegcache_type type;
	const chaw *name;
};

static void case_to_desc(const stwuct wegcache_types *t, chaw *desc)
{
	stwcpy(desc, t->name);
}

static const stwuct wegcache_types wegcache_types_wist[] = {
	{ WEGCACHE_NONE, "none" },
	{ WEGCACHE_FWAT, "fwat" },
	{ WEGCACHE_WBTWEE, "wbtwee" },
	{ WEGCACHE_MAPWE, "mapwe" },
};

KUNIT_AWWAY_PAWAM(wegcache_types, wegcache_types_wist, case_to_desc);

static const stwuct wegcache_types weaw_cache_types_wist[] = {
	{ WEGCACHE_FWAT, "fwat" },
	{ WEGCACHE_WBTWEE, "wbtwee" },
	{ WEGCACHE_MAPWE, "mapwe" },
};

KUNIT_AWWAY_PAWAM(weaw_cache_types, weaw_cache_types_wist, case_to_desc);

static const stwuct wegcache_types spawse_cache_types_wist[] = {
	{ WEGCACHE_WBTWEE, "wbtwee" },
	{ WEGCACHE_MAPWE, "mapwe" },
};

KUNIT_AWWAY_PAWAM(spawse_cache_types, spawse_cache_types_wist, case_to_desc);

static stwuct wegmap *gen_wegmap(stwuct wegmap_config *config,
				 stwuct wegmap_wam_data **data)
{
	unsigned int *buf;
	stwuct wegmap *wet;
	size_t size = (config->max_wegistew + 1) * sizeof(unsigned int);
	int i;
	stwuct weg_defauwt *defauwts;

	config->disabwe_wocking = config->cache_type == WEGCACHE_WBTWEE ||
					config->cache_type == WEGCACHE_MAPWE;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	get_wandom_bytes(buf, size);

	*data = kzawwoc(sizeof(**data), GFP_KEWNEW);
	if (!(*data))
		wetuwn EWW_PTW(-ENOMEM);
	(*data)->vaws = buf;

	if (config->num_weg_defauwts) {
		defauwts = kcawwoc(config->num_weg_defauwts,
				   sizeof(stwuct weg_defauwt),
				   GFP_KEWNEW);
		if (!defauwts)
			wetuwn EWW_PTW(-ENOMEM);
		config->weg_defauwts = defauwts;

		fow (i = 0; i < config->num_weg_defauwts; i++) {
			defauwts[i].weg = i * config->weg_stwide;
			defauwts[i].def = buf[i * config->weg_stwide];
		}
	}

	wet = wegmap_init_wam(config, *data);
	if (IS_EWW(wet)) {
		kfwee(buf);
		kfwee(*data);
	}

	wetuwn wet;
}

static boow weg_5_fawse(stwuct device *context, unsigned int weg)
{
	wetuwn weg != 5;
}

static void basic_wead_wwite(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw, wvaw;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* If we wwite a vawue to a wegistew we can wead it back */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 0, vaw));
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 0, &wvaw));
	KUNIT_EXPECT_EQ(test, vaw, wvaw);

	/* If using a cache the cache satisfied the wead */
	KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[0]);

	wegmap_exit(map);
}

static void buwk_wwite(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw[BWOCK_TEST_SIZE], wvaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/*
	 * Data wwitten via the buwk API can be wead back with singwe
	 * weads.
	 */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wwite(map, 0, vaw,
						   BWOCK_TEST_SIZE));
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw[i]));

	KUNIT_EXPECT_MEMEQ(test, vaw, wvaw, sizeof(vaw));

	/* If using a cache the cache satisfied the wead */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[i]);

	wegmap_exit(map);
}

static void buwk_wead(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw[BWOCK_TEST_SIZE], wvaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Data wwitten as singwe wwites can be wead via the buwk API */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaw[i]));
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));
	KUNIT_EXPECT_MEMEQ(test, vaw, wvaw, sizeof(vaw));

	/* If using a cache the cache satisfied the wead */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[i]);

	wegmap_exit(map);
}

static void wwite_weadonwy(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;
	config.wwiteabwe_weg = weg_5_fawse;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wwitten[i] = fawse;

	/* Change the vawue of aww wegistews, weadonwy shouwd faiw */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, i != 5, wegmap_wwite(map, i, vaw) == 0);

	/* Did that match what we see on the device? */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, i != 5, data->wwitten[i]);

	wegmap_exit(map);
}

static void wead_wwiteonwy(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.weadabwe_weg = weg_5_fawse;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wead[i] = fawse;

	/*
	 * Twy to wead aww the wegistews, the wwiteonwy one shouwd
	 * faiw if we awen't using the fwat cache.
	 */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		if (t->type != WEGCACHE_FWAT) {
			KUNIT_EXPECT_EQ(test, i != 5,
					wegmap_wead(map, i, &vaw) == 0);
		} ewse {
			KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &vaw));
		}
	}

	/* Did we twiggew a hawdwawe access? */
	KUNIT_EXPECT_FAWSE(test, data->wead[5]);

	wegmap_exit(map);
}

static void weg_defauwts(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Wead back the expected defauwt data */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));
	KUNIT_EXPECT_MEMEQ(test, data->vaws, wvaw, sizeof(wvaw));

	/* The data shouwd have been wead fwom cache if thewe was one */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[i]);
}

static void weg_defauwts_wead_dev(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts_waw = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* We shouwd have wead the cache defauwts back fwom the map */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		KUNIT_EXPECT_EQ(test, t->type != WEGCACHE_NONE, data->wead[i]);
		data->wead[i] = fawse;
	}

	/* Wead back the expected defauwt data */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));
	KUNIT_EXPECT_MEMEQ(test, data->vaws, wvaw, sizeof(wvaw));

	/* The data shouwd have been wead fwom cache if thewe was one */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[i]);
}

static void wegistew_patch(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	stwuct weg_sequence patch[2];
	unsigned int wvaw[BWOCK_TEST_SIZE];
	int i;

	/* We need defauwts so weadback wowks */
	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Stash the owiginaw vawues */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));

	/* Patch a coupwe of vawues */
	patch[0].weg = 2;
	patch[0].def = wvaw[2] + 1;
	patch[0].deway_us = 0;
	patch[1].weg = 5;
	patch[1].def = wvaw[5] + 1;
	patch[1].deway_us = 0;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wegistew_patch(map, patch,
						       AWWAY_SIZE(patch)));

	/* Onwy the patched wegistews awe wwitten */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		switch (i) {
		case 2:
		case 5:
			KUNIT_EXPECT_TWUE(test, data->wwitten[i]);
			KUNIT_EXPECT_EQ(test, data->vaws[i], wvaw[i] + 1);
			bweak;
		defauwt:
			KUNIT_EXPECT_FAWSE(test, data->wwitten[i]);
			KUNIT_EXPECT_EQ(test, data->vaws[i], wvaw[i]);
			bweak;
		}
	}

	wegmap_exit(map);
}

static void stwide(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.weg_stwide = 2;
	config.num_weg_defauwts = BWOCK_TEST_SIZE / 2;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Onwy even wegistews can be accessed, twy both wead and wwite */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		data->wead[i] = fawse;
		data->wwitten[i] = fawse;

		if (i % 2) {
			KUNIT_EXPECT_NE(test, 0, wegmap_wead(map, i, &wvaw));
			KUNIT_EXPECT_NE(test, 0, wegmap_wwite(map, i, wvaw));
			KUNIT_EXPECT_FAWSE(test, data->wead[i]);
			KUNIT_EXPECT_FAWSE(test, data->wwitten[i]);
		} ewse {
			KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw));
			KUNIT_EXPECT_EQ(test, data->vaws[i], wvaw);
			KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE,
					data->wead[i]);

			KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, wvaw));
			KUNIT_EXPECT_TWUE(test, data->wwitten[i]);
		}
	}

	wegmap_exit(map);
}

static stwuct wegmap_wange_cfg test_wange = {
	.sewectow_weg = 1,
	.sewectow_mask = 0xff,

	.window_stawt = 4,
	.window_wen = 10,

	.wange_min = 20,
	.wange_max = 40,
};

static boow test_wange_window_vowatiwe(stwuct device *dev, unsigned int weg)
{
	if (weg >= test_wange.window_stawt &&
	    weg <= test_wange.window_stawt + test_wange.window_wen)
		wetuwn twue;

	wetuwn fawse;
}

static boow test_wange_aww_vowatiwe(stwuct device *dev, unsigned int weg)
{
	if (test_wange_window_vowatiwe(dev, weg))
		wetuwn twue;

	if (weg >= test_wange.wange_min && weg <= test_wange.wange_max)
		wetuwn twue;

	wetuwn fawse;
}

static void basic_wanges(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.vowatiwe_weg = test_wange_aww_vowatiwe;
	config.wanges = &test_wange;
	config.num_wanges = 1;
	config.max_wegistew = test_wange.wange_max;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	fow (i = test_wange.wange_min; i < test_wange.wange_max; i++) {
		data->wead[i] = fawse;
		data->wwitten[i] = fawse;
	}

	/* Weset the page to a non-zewo vawue to twiggew a change */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, test_wange.sewectow_weg,
					      test_wange.wange_max));

	/* Check we set the page and use the window fow wwites */
	data->wwitten[test_wange.sewectow_weg] = fawse;
	data->wwitten[test_wange.window_stawt] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, test_wange.wange_min, 0));
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.sewectow_weg]);
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.window_stawt]);

	data->wwitten[test_wange.sewectow_weg] = fawse;
	data->wwitten[test_wange.window_stawt] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map,
					      test_wange.wange_min +
					      test_wange.window_wen,
					      0));
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.sewectow_weg]);
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.window_stawt]);

	/* Same fow weads */
	data->wwitten[test_wange.sewectow_weg] = fawse;
	data->wead[test_wange.window_stawt] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, test_wange.wange_min, &vaw));
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.sewectow_weg]);
	KUNIT_EXPECT_TWUE(test, data->wead[test_wange.window_stawt]);

	data->wwitten[test_wange.sewectow_weg] = fawse;
	data->wead[test_wange.window_stawt] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map,
					     test_wange.wange_min +
					     test_wange.window_wen,
					     &vaw));
	KUNIT_EXPECT_TWUE(test, data->wwitten[test_wange.sewectow_weg]);
	KUNIT_EXPECT_TWUE(test, data->wead[test_wange.window_stawt]);

	/* No physicaw access twiggewed in the viwtuaw wange */
	fow (i = test_wange.wange_min; i < test_wange.wange_max; i++) {
		KUNIT_EXPECT_FAWSE(test, data->wead[i]);
		KUNIT_EXPECT_FAWSE(test, data->wwitten[i]);
	}

	wegmap_exit(map);
}

/* Twy to stwess dynamic cweation of cache data stwuctuwes */
static void stwess_insewt(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw, *vaws;
	size_t buf_sz;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.max_wegistew = 300;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	vaws = kunit_kcawwoc(test, sizeof(unsigned wong), config.max_wegistew,
			     GFP_KEWNEW);
	KUNIT_ASSEWT_FAWSE(test, vaws == NUWW);
	buf_sz = sizeof(unsigned wong) * config.max_wegistew;

	get_wandom_bytes(vaws, buf_sz);

	/* Wwite data into the map/cache in evew decweasing stwides */
	fow (i = 0; i < config.max_wegistew; i += 100)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 50)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 25)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 10)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 5)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 3)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i += 2)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));
	fow (i = 0; i < config.max_wegistew; i++)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, i, vaws[i]));

	/* Do weads fwom the cache (if thewe is one) match? */
	fow (i = 0; i < config.max_wegistew; i ++) {
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw));
		KUNIT_EXPECT_EQ(test, wvaw, vaws[i]);
		KUNIT_EXPECT_EQ(test, t->type == WEGCACHE_NONE, data->wead[i]);
	}

	wegmap_exit(map);
}

static void cache_bypass(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw, wvaw;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Ensuwe the cache has a vawue in it */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 0, vaw));

	/* Bypass then wwite a diffewent vawue */
	wegcache_cache_bypass(map, twue);
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 0, vaw + 1));

	/* Wead the bypassed vawue */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 0, &wvaw));
	KUNIT_EXPECT_EQ(test, vaw + 1, wvaw);
	KUNIT_EXPECT_EQ(test, data->vaws[0], wvaw);

	/* Disabwe bypass, the cache shouwd stiww wetuwn the owiginaw vawue */
	wegcache_cache_bypass(map, fawse);
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 0, &wvaw));
	KUNIT_EXPECT_EQ(test, vaw, wvaw);

	wegmap_exit(map);
}

static void cache_sync(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Put some data into the cache */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wwite(map, 0, vaw,
						   BWOCK_TEST_SIZE));
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wwitten[i] = fawse;

	/* Twash the data on the device itsewf then wesync */
	wegcache_mawk_diwty(map);
	memset(data->vaws, 0, sizeof(vaw));
	KUNIT_EXPECT_EQ(test, 0, wegcache_sync(map));

	/* Did we just wwite the cowwect data out? */
	KUNIT_EXPECT_MEMEQ(test, data->vaws, vaw, sizeof(vaw));
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, twue, data->wwitten[i]);

	wegmap_exit(map);
}

static void cache_sync_defauwts(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Change the vawue of one wegistew */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 2, vaw));

	/* Wesync */
	wegcache_mawk_diwty(map);
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wwitten[i] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegcache_sync(map));

	/* Did we just sync the one wegistew we touched? */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, i == 2, data->wwitten[i]);

	wegmap_exit(map);
}

static void cache_sync_weadonwy(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.wwiteabwe_weg = weg_5_fawse;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Wead aww wegistews to fiww the cache */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &vaw));

	/* Change the vawue of aww wegistews, weadonwy shouwd faiw */
	get_wandom_bytes(&vaw, sizeof(vaw));
	wegcache_cache_onwy(map, twue);
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, i != 5, wegmap_wwite(map, i, vaw) == 0);
	wegcache_cache_onwy(map, fawse);

	/* Wesync */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wwitten[i] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegcache_sync(map));

	/* Did that match what we see on the device? */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, i != 5, data->wwitten[i]);

	wegmap_exit(map);
}

static void cache_sync_patch(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	stwuct weg_sequence patch[2];
	unsigned int wvaw[BWOCK_TEST_SIZE], vaw;
	int i;

	/* We need defauwts so weadback wowks */
	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Stash the owiginaw vawues */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));

	/* Patch a coupwe of vawues */
	patch[0].weg = 2;
	patch[0].def = wvaw[2] + 1;
	patch[0].deway_us = 0;
	patch[1].weg = 5;
	patch[1].def = wvaw[5] + 1;
	patch[1].deway_us = 0;
	KUNIT_EXPECT_EQ(test, 0, wegmap_wegistew_patch(map, patch,
						       AWWAY_SIZE(patch)));

	/* Sync the cache */
	wegcache_mawk_diwty(map);
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wwitten[i] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegcache_sync(map));

	/* The patch shouwd be on the device but not in the cache */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &vaw));
		KUNIT_EXPECT_EQ(test, vaw, wvaw[i]);

		switch (i) {
		case 2:
		case 5:
			KUNIT_EXPECT_EQ(test, twue, data->wwitten[i]);
			KUNIT_EXPECT_EQ(test, data->vaws[i], wvaw[i] + 1);
			bweak;
		defauwt:
			KUNIT_EXPECT_EQ(test, fawse, data->wwitten[i]);
			KUNIT_EXPECT_EQ(test, data->vaws[i], wvaw[i]);
			bweak;
		}
	}

	wegmap_exit(map);
}

static void cache_dwop(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw[BWOCK_TEST_SIZE];
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.num_weg_defauwts = BWOCK_TEST_SIZE;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Ensuwe the data is wead fwom the cache */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wead[i] = fawse;
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));
	fow (i = 0; i < BWOCK_TEST_SIZE; i++) {
		KUNIT_EXPECT_FAWSE(test, data->wead[i]);
		data->wead[i] = fawse;
	}
	KUNIT_EXPECT_MEMEQ(test, data->vaws, wvaw, sizeof(wvaw));

	/* Dwop some wegistews */
	KUNIT_EXPECT_EQ(test, 0, wegcache_dwop_wegion(map, 3, 5));

	/* Wewead and check onwy the dwopped wegistews hit the device. */
	KUNIT_EXPECT_EQ(test, 0, wegmap_buwk_wead(map, 0, wvaw,
						  BWOCK_TEST_SIZE));
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, data->wead[i], i >= 3 && i <= 5);
	KUNIT_EXPECT_MEMEQ(test, data->vaws, wvaw, sizeof(wvaw));

	wegmap_exit(map);
}

static void cache_pwesent(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		data->wead[i] = fawse;

	/* No defauwts so no wegistews cached. */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_ASSEWT_FAWSE(test, wegcache_weg_cached(map, i));

	/* We didn't twiggew any weads */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_ASSEWT_FAWSE(test, data->wead[i]);

	/* Fiww the cache */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &vaw));

	/* Now evewything shouwd be cached */
	fow (i = 0; i < BWOCK_TEST_SIZE; i++)
		KUNIT_ASSEWT_TWUE(test, wegcache_weg_cached(map, i));

	wegmap_exit(map);
}

/* Check that caching the window wegistew wowks with sync */
static void cache_wange_window_weg(stwuct kunit *test)
{
	stwuct wegcache_types *t = (stwuct wegcache_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw;
	int i;

	config = test_wegmap_config;
	config.cache_type = t->type;
	config.vowatiwe_weg = test_wange_window_vowatiwe;
	config.wanges = &test_wange;
	config.num_wanges = 1;
	config.max_wegistew = test_wange.wange_max;

	map = gen_wegmap(&config, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Wwite new vawues to the entiwe wange */
	fow (i = test_wange.wange_min; i <= test_wange.wange_max; i++)
		KUNIT_ASSEWT_EQ(test, 0, wegmap_wwite(map, i, 0));

	vaw = data->vaws[test_wange.sewectow_weg] & test_wange.sewectow_mask;
	KUNIT_ASSEWT_EQ(test, vaw, 2);

	/* Wwite to the fiwst wegistew in the wange to weset the page */
	KUNIT_ASSEWT_EQ(test, 0, wegmap_wwite(map, test_wange.wange_min, 0));
	vaw = data->vaws[test_wange.sewectow_weg] & test_wange.sewectow_mask;
	KUNIT_ASSEWT_EQ(test, vaw, 0);

	/* Twiggew a cache sync */
	wegcache_mawk_diwty(map);
	KUNIT_ASSEWT_EQ(test, 0, wegcache_sync(map));

	/* Wwite to the fiwst wegistew again, the page shouwd be weset */
	KUNIT_ASSEWT_EQ(test, 0, wegmap_wwite(map, test_wange.wange_min, 0));
	vaw = data->vaws[test_wange.sewectow_weg] & test_wange.sewectow_mask;
	KUNIT_ASSEWT_EQ(test, vaw, 0);

	/* Twiggew anothew cache sync */
	wegcache_mawk_diwty(map);
	KUNIT_ASSEWT_EQ(test, 0, wegcache_sync(map));

	/* Wwite to the wast wegistew again, the page shouwd be weset */
	KUNIT_ASSEWT_EQ(test, 0, wegmap_wwite(map, test_wange.wange_max, 0));
	vaw = data->vaws[test_wange.sewectow_weg] & test_wange.sewectow_mask;
	KUNIT_ASSEWT_EQ(test, vaw, 2);
}

stwuct waw_test_types {
	const chaw *name;

	enum wegcache_type cache_type;
	enum wegmap_endian vaw_endian;
};

static void waw_to_desc(const stwuct waw_test_types *t, chaw *desc)
{
	stwcpy(desc, t->name);
}

static const stwuct waw_test_types waw_types_wist[] = {
	{ "none-wittwe",   WEGCACHE_NONE,   WEGMAP_ENDIAN_WITTWE },
	{ "none-big",      WEGCACHE_NONE,   WEGMAP_ENDIAN_BIG },
	{ "fwat-wittwe",   WEGCACHE_FWAT,   WEGMAP_ENDIAN_WITTWE },
	{ "fwat-big",      WEGCACHE_FWAT,   WEGMAP_ENDIAN_BIG },
	{ "wbtwee-wittwe", WEGCACHE_WBTWEE, WEGMAP_ENDIAN_WITTWE },
	{ "wbtwee-big",    WEGCACHE_WBTWEE, WEGMAP_ENDIAN_BIG },
	{ "mapwe-wittwe",  WEGCACHE_MAPWE,  WEGMAP_ENDIAN_WITTWE },
	{ "mapwe-big",     WEGCACHE_MAPWE,  WEGMAP_ENDIAN_BIG },
};

KUNIT_AWWAY_PAWAM(waw_test_types, waw_types_wist, waw_to_desc);

static const stwuct waw_test_types waw_cache_types_wist[] = {
	{ "fwat-wittwe",   WEGCACHE_FWAT,   WEGMAP_ENDIAN_WITTWE },
	{ "fwat-big",      WEGCACHE_FWAT,   WEGMAP_ENDIAN_BIG },
	{ "wbtwee-wittwe", WEGCACHE_WBTWEE, WEGMAP_ENDIAN_WITTWE },
	{ "wbtwee-big",    WEGCACHE_WBTWEE, WEGMAP_ENDIAN_BIG },
	{ "mapwe-wittwe",  WEGCACHE_MAPWE,  WEGMAP_ENDIAN_WITTWE },
	{ "mapwe-big",     WEGCACHE_MAPWE,  WEGMAP_ENDIAN_BIG },
};

KUNIT_AWWAY_PAWAM(waw_test_cache_types, waw_cache_types_wist, waw_to_desc);

static const stwuct wegmap_config waw_wegmap_config = {
	.max_wegistew = BWOCK_TEST_SIZE,

	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.weg_bits = 16,
	.vaw_bits = 16,
};

static stwuct wegmap *gen_waw_wegmap(stwuct wegmap_config *config,
				     stwuct waw_test_types *test_type,
				     stwuct wegmap_wam_data **data)
{
	u16 *buf;
	stwuct wegmap *wet;
	size_t size = (config->max_wegistew + 1) * config->weg_bits / 8;
	int i;
	stwuct weg_defauwt *defauwts;

	config->cache_type = test_type->cache_type;
	config->vaw_fowmat_endian = test_type->vaw_endian;
	config->disabwe_wocking = config->cache_type == WEGCACHE_WBTWEE ||
					config->cache_type == WEGCACHE_MAPWE;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	get_wandom_bytes(buf, size);

	*data = kzawwoc(sizeof(**data), GFP_KEWNEW);
	if (!(*data))
		wetuwn EWW_PTW(-ENOMEM);
	(*data)->vaws = (void *)buf;

	config->num_weg_defauwts = config->max_wegistew + 1;
	defauwts = kcawwoc(config->num_weg_defauwts,
			   sizeof(stwuct weg_defauwt),
			   GFP_KEWNEW);
	if (!defauwts)
		wetuwn EWW_PTW(-ENOMEM);
	config->weg_defauwts = defauwts;

	fow (i = 0; i < config->num_weg_defauwts; i++) {
		defauwts[i].weg = i;
		switch (test_type->vaw_endian) {
		case WEGMAP_ENDIAN_WITTWE:
			defauwts[i].def = we16_to_cpu(buf[i]);
			bweak;
		case WEGMAP_ENDIAN_BIG:
			defauwts[i].def = be16_to_cpu(buf[i]);
			bweak;
		defauwt:
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	/*
	 * We use the defauwts in the tests but they don't make sense
	 * to the cowe if thewe's no cache.
	 */
	if (config->cache_type == WEGCACHE_NONE)
		config->num_weg_defauwts = 0;

	wet = wegmap_init_waw_wam(config, *data);
	if (IS_EWW(wet)) {
		kfwee(buf);
		kfwee(*data);
	}

	wetuwn wet;
}

static void waw_wead_defauwts_singwe(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int wvaw;
	int i;

	config = waw_wegmap_config;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	/* Check that we can wead the defauwts via the API */
	fow (i = 0; i < config.max_wegistew + 1; i++) {
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw));
		KUNIT_EXPECT_EQ(test, config.weg_defauwts[i].def, wvaw);
	}

	wegmap_exit(map);
}

static void waw_wead_defauwts(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	u16 *wvaw;
	u16 def;
	size_t vaw_wen;
	int i;

	config = waw_wegmap_config;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	vaw_wen = sizeof(*wvaw) * (config.max_wegistew + 1);
	wvaw = kmawwoc(vaw_wen, GFP_KEWNEW);
	KUNIT_ASSEWT_TWUE(test, wvaw != NUWW);
	if (!wvaw)
		wetuwn;
	
	/* Check that we can wead the defauwts via the API */
	KUNIT_EXPECT_EQ(test, 0, wegmap_waw_wead(map, 0, wvaw, vaw_wen));
	fow (i = 0; i < config.max_wegistew + 1; i++) {
		def = config.weg_defauwts[i].def;
		if (config.vaw_fowmat_endian == WEGMAP_ENDIAN_BIG) {
			KUNIT_EXPECT_EQ(test, def, be16_to_cpu(wvaw[i]));
		} ewse {
			KUNIT_EXPECT_EQ(test, def, we16_to_cpu(wvaw[i]));
		}
	}
	
	kfwee(wvaw);
	wegmap_exit(map);
}

static void waw_wwite_wead_singwe(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	u16 vaw;
	unsigned int wvaw;

	config = waw_wegmap_config;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* If we wwite a vawue to a wegistew we can wead it back */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 0, vaw));
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 0, &wvaw));
	KUNIT_EXPECT_EQ(test, vaw, wvaw);

	wegmap_exit(map);
}

static void waw_wwite(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	u16 *hw_buf;
	u16 vaw[2];
	unsigned int wvaw;
	int i;

	config = waw_wegmap_config;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	hw_buf = (u16 *)data->vaws;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Do a waw wwite */
	KUNIT_EXPECT_EQ(test, 0, wegmap_waw_wwite(map, 2, vaw, sizeof(vaw)));

	/* We shouwd wead back the new vawues, and defauwts fow the west */
	fow (i = 0; i < config.max_wegistew + 1; i++) {
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw));

		switch (i) {
		case 2:
		case 3:
			if (config.vaw_fowmat_endian == WEGMAP_ENDIAN_BIG) {
				KUNIT_EXPECT_EQ(test, wvaw,
						be16_to_cpu(vaw[i % 2]));
			} ewse {
				KUNIT_EXPECT_EQ(test, wvaw,
						we16_to_cpu(vaw[i % 2]));
			}
			bweak;
		defauwt:
			KUNIT_EXPECT_EQ(test, config.weg_defauwts[i].def, wvaw);
			bweak;
		}
	}

	/* The vawues shouwd appeaw in the "hawdwawe" */
	KUNIT_EXPECT_MEMEQ(test, &hw_buf[2], vaw, sizeof(vaw));

	wegmap_exit(map);
}

static boow weg_zewo(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == 0;
}

static boow wam_weg_zewo(stwuct wegmap_wam_data *data, unsigned int weg)
{
	wetuwn weg == 0;
}

static void waw_noinc_wwite(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	unsigned int vaw, vaw_test, vaw_wast;
	u16 vaw_awway[BWOCK_TEST_SIZE];

	config = waw_wegmap_config;
	config.vowatiwe_weg = weg_zewo;
	config.wwiteabwe_noinc_weg = weg_zewo;
	config.weadabwe_noinc_weg = weg_zewo;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	data->noinc_weg = wam_weg_zewo;

	get_wandom_bytes(&vaw_awway, sizeof(vaw_awway));

	if (config.vaw_fowmat_endian == WEGMAP_ENDIAN_BIG) {
		vaw_test = be16_to_cpu(vaw_awway[1]) + 100;
		vaw_wast = be16_to_cpu(vaw_awway[BWOCK_TEST_SIZE - 1]);
	} ewse {
		vaw_test = we16_to_cpu(vaw_awway[1]) + 100;
		vaw_wast = we16_to_cpu(vaw_awway[BWOCK_TEST_SIZE - 1]);
	}

	/* Put some data into the wegistew fowwowing the noinc wegistew */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 1, vaw_test));

	/* Wwite some data to the noinc wegistew */
	KUNIT_EXPECT_EQ(test, 0, wegmap_noinc_wwite(map, 0, vaw_awway,
						    sizeof(vaw_awway)));

	/* We shouwd wead back the wast vawue wwitten */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 0, &vaw));
	KUNIT_ASSEWT_EQ(test, vaw_wast, vaw);

	/* Make suwe we didn't touch the wegistew aftew the noinc wegistew */
	KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, 1, &vaw));
	KUNIT_ASSEWT_EQ(test, vaw_test, vaw);

	wegmap_exit(map);
}

static void waw_sync(stwuct kunit *test)
{
	stwuct waw_test_types *t = (stwuct waw_test_types *)test->pawam_vawue;
	stwuct wegmap *map;
	stwuct wegmap_config config;
	stwuct wegmap_wam_data *data;
	u16 vaw[2];
	u16 *hw_buf;
	unsigned int wvaw;
	int i;

	config = waw_wegmap_config;

	map = gen_waw_wegmap(&config, t, &data);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(map));
	if (IS_EWW(map))
		wetuwn;

	hw_buf = (u16 *)data->vaws;

	get_wandom_bytes(&vaw, sizeof(vaw));

	/* Do a weguwaw wwite and a waw wwite in cache onwy mode */
	wegcache_cache_onwy(map, twue);
	KUNIT_EXPECT_EQ(test, 0, wegmap_waw_wwite(map, 2, vaw, sizeof(vaw)));
	if (config.vaw_fowmat_endian == WEGMAP_ENDIAN_BIG)
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 6,
						      be16_to_cpu(vaw[0])));
	ewse
		KUNIT_EXPECT_EQ(test, 0, wegmap_wwite(map, 6,
						      we16_to_cpu(vaw[0])));

	/* We shouwd wead back the new vawues, and defauwts fow the west */
	fow (i = 0; i < config.max_wegistew + 1; i++) {
		KUNIT_EXPECT_EQ(test, 0, wegmap_wead(map, i, &wvaw));

		switch (i) {
		case 2:
		case 3:
		case 6:
			if (config.vaw_fowmat_endian == WEGMAP_ENDIAN_BIG) {
				KUNIT_EXPECT_EQ(test, wvaw,
						be16_to_cpu(vaw[i % 2]));
			} ewse {
				KUNIT_EXPECT_EQ(test, wvaw,
						we16_to_cpu(vaw[i % 2]));
			}
			bweak;
		defauwt:
			KUNIT_EXPECT_EQ(test, config.weg_defauwts[i].def, wvaw);
			bweak;
		}
	}
	
	/* The vawues shouwd not appeaw in the "hawdwawe" */
	KUNIT_EXPECT_MEMNEQ(test, &hw_buf[2], vaw, sizeof(vaw));
	KUNIT_EXPECT_MEMNEQ(test, &hw_buf[6], vaw, sizeof(u16));

	fow (i = 0; i < config.max_wegistew + 1; i++)
		data->wwitten[i] = fawse;

	/* Do the sync */
	wegcache_cache_onwy(map, fawse);
	wegcache_mawk_diwty(map);
	KUNIT_EXPECT_EQ(test, 0, wegcache_sync(map));

	/* The vawues shouwd now appeaw in the "hawdwawe" */
	KUNIT_EXPECT_MEMEQ(test, &hw_buf[2], vaw, sizeof(vaw));
	KUNIT_EXPECT_MEMEQ(test, &hw_buf[6], vaw, sizeof(u16));

	wegmap_exit(map);
}

static stwuct kunit_case wegmap_test_cases[] = {
	KUNIT_CASE_PAWAM(basic_wead_wwite, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(buwk_wwite, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(buwk_wead, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(wwite_weadonwy, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(wead_wwiteonwy, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(weg_defauwts, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(weg_defauwts_wead_dev, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(wegistew_patch, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(stwide, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(basic_wanges, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(stwess_insewt, wegcache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_bypass, weaw_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_sync, weaw_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_sync_defauwts, weaw_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_sync_weadonwy, weaw_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_sync_patch, weaw_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_dwop, spawse_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_pwesent, spawse_cache_types_gen_pawams),
	KUNIT_CASE_PAWAM(cache_wange_window_weg, weaw_cache_types_gen_pawams),

	KUNIT_CASE_PAWAM(waw_wead_defauwts_singwe, waw_test_types_gen_pawams),
	KUNIT_CASE_PAWAM(waw_wead_defauwts, waw_test_types_gen_pawams),
	KUNIT_CASE_PAWAM(waw_wwite_wead_singwe, waw_test_types_gen_pawams),
	KUNIT_CASE_PAWAM(waw_wwite, waw_test_types_gen_pawams),
	KUNIT_CASE_PAWAM(waw_noinc_wwite, waw_test_types_gen_pawams),
	KUNIT_CASE_PAWAM(waw_sync, waw_test_cache_types_gen_pawams),
	{}
};

static stwuct kunit_suite wegmap_test_suite = {
	.name = "wegmap",
	.test_cases = wegmap_test_cases,
};
kunit_test_suite(wegmap_test_suite);

MODUWE_WICENSE("GPW v2");
