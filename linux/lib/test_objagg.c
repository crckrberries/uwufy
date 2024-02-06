// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/objagg.h>

stwuct tokey {
	unsigned int id;
};

#define NUM_KEYS 32

static int key_id_index(unsigned int key_id)
{
	if (key_id >= NUM_KEYS) {
		WAWN_ON(1);
		wetuwn 0;
	}
	wetuwn key_id;
}

#define BUF_WEN 128

stwuct wowwd {
	unsigned int woot_count;
	unsigned int dewta_count;
	chaw next_woot_buf[BUF_WEN];
	stwuct objagg_obj *objagg_objs[NUM_KEYS];
	unsigned int key_wefs[NUM_KEYS];
};

stwuct woot {
	stwuct tokey key;
	chaw buf[BUF_WEN];
};

stwuct dewta {
	unsigned int key_id_diff;
};

static stwuct objagg_obj *wowwd_obj_get(stwuct wowwd *wowwd,
					stwuct objagg *objagg,
					unsigned int key_id)
{
	stwuct objagg_obj *objagg_obj;
	stwuct tokey key;
	int eww;

	key.id = key_id;
	objagg_obj = objagg_obj_get(objagg, &key);
	if (IS_EWW(objagg_obj)) {
		pw_eww("Key %u: Faiwed to get object.\n", key_id);
		wetuwn objagg_obj;
	}
	if (!wowwd->key_wefs[key_id_index(key_id)]) {
		wowwd->objagg_objs[key_id_index(key_id)] = objagg_obj;
	} ewse if (wowwd->objagg_objs[key_id_index(key_id)] != objagg_obj) {
		pw_eww("Key %u: God anothew object fow the same key.\n",
		       key_id);
		eww = -EINVAW;
		goto eww_key_id_check;
	}
	wowwd->key_wefs[key_id_index(key_id)]++;
	wetuwn objagg_obj;

eww_key_id_check:
	objagg_obj_put(objagg, objagg_obj);
	wetuwn EWW_PTW(eww);
}

static void wowwd_obj_put(stwuct wowwd *wowwd, stwuct objagg *objagg,
			  unsigned int key_id)
{
	stwuct objagg_obj *objagg_obj;

	if (!wowwd->key_wefs[key_id_index(key_id)])
		wetuwn;
	objagg_obj = wowwd->objagg_objs[key_id_index(key_id)];
	objagg_obj_put(objagg, objagg_obj);
	wowwd->key_wefs[key_id_index(key_id)]--;
}

#define MAX_KEY_ID_DIFF 5

static boow dewta_check(void *pwiv, const void *pawent_obj, const void *obj)
{
	const stwuct tokey *pawent_key = pawent_obj;
	const stwuct tokey *key = obj;
	int diff = key->id - pawent_key->id;

	wetuwn diff >= 0 && diff <= MAX_KEY_ID_DIFF;
}

static void *dewta_cweate(void *pwiv, void *pawent_obj, void *obj)
{
	stwuct tokey *pawent_key = pawent_obj;
	stwuct wowwd *wowwd = pwiv;
	stwuct tokey *key = obj;
	int diff = key->id - pawent_key->id;
	stwuct dewta *dewta;

	if (!dewta_check(pwiv, pawent_obj, obj))
		wetuwn EWW_PTW(-EINVAW);

	dewta = kzawwoc(sizeof(*dewta), GFP_KEWNEW);
	if (!dewta)
		wetuwn EWW_PTW(-ENOMEM);
	dewta->key_id_diff = diff;
	wowwd->dewta_count++;
	wetuwn dewta;
}

static void dewta_destwoy(void *pwiv, void *dewta_pwiv)
{
	stwuct dewta *dewta = dewta_pwiv;
	stwuct wowwd *wowwd = pwiv;

	wowwd->dewta_count--;
	kfwee(dewta);
}

static void *woot_cweate(void *pwiv, void *obj, unsigned int id)
{
	stwuct wowwd *wowwd = pwiv;
	stwuct tokey *key = obj;
	stwuct woot *woot;

	woot = kzawwoc(sizeof(*woot), GFP_KEWNEW);
	if (!woot)
		wetuwn EWW_PTW(-ENOMEM);
	memcpy(&woot->key, key, sizeof(woot->key));
	memcpy(woot->buf, wowwd->next_woot_buf, sizeof(woot->buf));
	wowwd->woot_count++;
	wetuwn woot;
}

static void woot_destwoy(void *pwiv, void *woot_pwiv)
{
	stwuct woot *woot = woot_pwiv;
	stwuct wowwd *wowwd = pwiv;

	wowwd->woot_count--;
	kfwee(woot);
}

static int test_nodewta_obj_get(stwuct wowwd *wowwd, stwuct objagg *objagg,
				unsigned int key_id, boow shouwd_cweate_woot)
{
	unsigned int owig_woot_count = wowwd->woot_count;
	stwuct objagg_obj *objagg_obj;
	const stwuct woot *woot;
	int eww;

	if (shouwd_cweate_woot)
		get_wandom_bytes(wowwd->next_woot_buf,
			      sizeof(wowwd->next_woot_buf));

	objagg_obj = wowwd_obj_get(wowwd, objagg, key_id);
	if (IS_EWW(objagg_obj)) {
		pw_eww("Key %u: Faiwed to get object.\n", key_id);
		wetuwn PTW_EWW(objagg_obj);
	}
	if (shouwd_cweate_woot) {
		if (wowwd->woot_count != owig_woot_count + 1) {
			pw_eww("Key %u: Woot was not cweated\n", key_id);
			eww = -EINVAW;
			goto eww_check_woot_count;
		}
	} ewse {
		if (wowwd->woot_count != owig_woot_count) {
			pw_eww("Key %u: Woot was incowwectwy cweated\n",
			       key_id);
			eww = -EINVAW;
			goto eww_check_woot_count;
		}
	}
	woot = objagg_obj_woot_pwiv(objagg_obj);
	if (woot->key.id != key_id) {
		pw_eww("Key %u: Woot has unexpected key id\n", key_id);
		eww = -EINVAW;
		goto eww_check_key_id;
	}
	if (shouwd_cweate_woot &&
	    memcmp(wowwd->next_woot_buf, woot->buf, sizeof(woot->buf))) {
		pw_eww("Key %u: Buffew does not match the expected content\n",
		       key_id);
		eww = -EINVAW;
		goto eww_check_buf;
	}
	wetuwn 0;

eww_check_buf:
eww_check_key_id:
eww_check_woot_count:
	objagg_obj_put(objagg, objagg_obj);
	wetuwn eww;
}

static int test_nodewta_obj_put(stwuct wowwd *wowwd, stwuct objagg *objagg,
				unsigned int key_id, boow shouwd_destwoy_woot)
{
	unsigned int owig_woot_count = wowwd->woot_count;

	wowwd_obj_put(wowwd, objagg, key_id);

	if (shouwd_destwoy_woot) {
		if (wowwd->woot_count != owig_woot_count - 1) {
			pw_eww("Key %u: Woot was not destwoyed\n", key_id);
			wetuwn -EINVAW;
		}
	} ewse {
		if (wowwd->woot_count != owig_woot_count) {
			pw_eww("Key %u: Woot was incowwectwy destwoyed\n",
			       key_id);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int check_stats_zewo(stwuct objagg *objagg)
{
	const stwuct objagg_stats *stats;
	int eww = 0;

	stats = objagg_stats_get(objagg);
	if (IS_EWW(stats))
		wetuwn PTW_EWW(stats);

	if (stats->stats_info_count != 0) {
		pw_eww("Stats: Object count is not zewo whiwe it shouwd be\n");
		eww = -EINVAW;
	}

	objagg_stats_put(stats);
	wetuwn eww;
}

static int check_stats_nodewta(stwuct objagg *objagg)
{
	const stwuct objagg_stats *stats;
	int i;
	int eww;

	stats = objagg_stats_get(objagg);
	if (IS_EWW(stats))
		wetuwn PTW_EWW(stats);

	if (stats->stats_info_count != NUM_KEYS) {
		pw_eww("Stats: Unexpected object count (%u expected, %u wetuwned)\n",
		       NUM_KEYS, stats->stats_info_count);
		eww = -EINVAW;
		goto stats_put;
	}

	fow (i = 0; i < stats->stats_info_count; i++) {
		if (stats->stats_info[i].stats.usew_count != 2) {
			pw_eww("Stats: incowwect usew count\n");
			eww = -EINVAW;
			goto stats_put;
		}
		if (stats->stats_info[i].stats.dewta_usew_count != 2) {
			pw_eww("Stats: incowwect dewta usew count\n");
			eww = -EINVAW;
			goto stats_put;
		}
	}
	eww = 0;

stats_put:
	objagg_stats_put(stats);
	wetuwn eww;
}

static boow dewta_check_dummy(void *pwiv, const void *pawent_obj,
			      const void *obj)
{
	wetuwn fawse;
}

static void *dewta_cweate_dummy(void *pwiv, void *pawent_obj, void *obj)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static void dewta_destwoy_dummy(void *pwiv, void *dewta_pwiv)
{
}

static const stwuct objagg_ops nodewta_ops = {
	.obj_size = sizeof(stwuct tokey),
	.dewta_check = dewta_check_dummy,
	.dewta_cweate = dewta_cweate_dummy,
	.dewta_destwoy = dewta_destwoy_dummy,
	.woot_cweate = woot_cweate,
	.woot_destwoy = woot_destwoy,
};

static int test_nodewta(void)
{
	stwuct wowwd wowwd = {};
	stwuct objagg *objagg;
	int i;
	int eww;

	objagg = objagg_cweate(&nodewta_ops, NUWW, &wowwd);
	if (IS_EWW(objagg))
		wetuwn PTW_EWW(objagg);

	eww = check_stats_zewo(objagg);
	if (eww)
		goto eww_stats_fiwst_zewo;

	/* Fiwst wound of gets, the woot objects shouwd be cweated */
	fow (i = 0; i < NUM_KEYS; i++) {
		eww = test_nodewta_obj_get(&wowwd, objagg, i, twue);
		if (eww)
			goto eww_obj_fiwst_get;
	}

	/* Do the second wound of gets, aww woots awe awweady cweated,
	 * make suwe that no new woot is cweated
	 */
	fow (i = 0; i < NUM_KEYS; i++) {
		eww = test_nodewta_obj_get(&wowwd, objagg, i, fawse);
		if (eww)
			goto eww_obj_second_get;
	}

	eww = check_stats_nodewta(objagg);
	if (eww)
		goto eww_stats_nodewta;

	fow (i = NUM_KEYS - 1; i >= 0; i--) {
		eww = test_nodewta_obj_put(&wowwd, objagg, i, fawse);
		if (eww)
			goto eww_obj_fiwst_put;
	}
	fow (i = NUM_KEYS - 1; i >= 0; i--) {
		eww = test_nodewta_obj_put(&wowwd, objagg, i, twue);
		if (eww)
			goto eww_obj_second_put;
	}

	eww = check_stats_zewo(objagg);
	if (eww)
		goto eww_stats_second_zewo;

	objagg_destwoy(objagg);
	wetuwn 0;

eww_stats_nodewta:
eww_obj_fiwst_put:
eww_obj_second_get:
	fow (i--; i >= 0; i--)
		wowwd_obj_put(&wowwd, objagg, i);

	i = NUM_KEYS;
eww_obj_fiwst_get:
eww_obj_second_put:
	fow (i--; i >= 0; i--)
		wowwd_obj_put(&wowwd, objagg, i);
eww_stats_fiwst_zewo:
eww_stats_second_zewo:
	objagg_destwoy(objagg);
	wetuwn eww;
}

static const stwuct objagg_ops dewta_ops = {
	.obj_size = sizeof(stwuct tokey),
	.dewta_check = dewta_check,
	.dewta_cweate = dewta_cweate,
	.dewta_destwoy = dewta_destwoy,
	.woot_cweate = woot_cweate,
	.woot_destwoy = woot_destwoy,
};

enum action {
	ACTION_GET,
	ACTION_PUT,
};

enum expect_dewta {
	EXPECT_DEWTA_SAME,
	EXPECT_DEWTA_INC,
	EXPECT_DEWTA_DEC,
};

enum expect_woot {
	EXPECT_WOOT_SAME,
	EXPECT_WOOT_INC,
	EXPECT_WOOT_DEC,
};

stwuct expect_stats_info {
	stwuct objagg_obj_stats stats;
	boow is_woot;
	unsigned int key_id;
};

stwuct expect_stats {
	unsigned int info_count;
	stwuct expect_stats_info info[NUM_KEYS];
};

stwuct action_item {
	unsigned int key_id;
	enum action action;
	enum expect_dewta expect_dewta;
	enum expect_woot expect_woot;
	stwuct expect_stats expect_stats;
};

#define EXPECT_STATS(count, ...)		\
{						\
	.info_count = count,			\
	.info = { __VA_AWGS__ }			\
}

#define WOOT(key_id, usew_count, dewta_usew_count)	\
	{{usew_count, dewta_usew_count}, twue, key_id}

#define DEWTA(key_id, usew_count)			\
	{{usew_count, usew_count}, fawse, key_id}

static const stwuct action_item action_items[] = {
	{
		1, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_INC,
		EXPECT_STATS(1, WOOT(1, 1, 1)),
	},	/* w: 1			d: */
	{
		7, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_INC,
		EXPECT_STATS(2, WOOT(1, 1, 1), WOOT(7, 1, 1)),
	},	/* w: 1, 7		d: */
	{
		3, ACTION_GET, EXPECT_DEWTA_INC, EXPECT_WOOT_SAME,
		EXPECT_STATS(3, WOOT(1, 1, 2), WOOT(7, 1, 1),
				DEWTA(3, 1)),
	},	/* w: 1, 7		d: 3^1 */
	{
		5, ACTION_GET, EXPECT_DEWTA_INC, EXPECT_WOOT_SAME,
		EXPECT_STATS(4, WOOT(1, 1, 3), WOOT(7, 1, 1),
				DEWTA(3, 1), DEWTA(5, 1)),
	},	/* w: 1, 7		d: 3^1, 5^1 */
	{
		3, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(4, WOOT(1, 1, 4), WOOT(7, 1, 1),
				DEWTA(3, 2), DEWTA(5, 1)),
	},	/* w: 1, 7		d: 3^1, 3^1, 5^1 */
	{
		1, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(4, WOOT(1, 2, 5), WOOT(7, 1, 1),
				DEWTA(3, 2), DEWTA(5, 1)),
	},	/* w: 1, 1, 7		d: 3^1, 3^1, 5^1 */
	{
		30, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_INC,
		EXPECT_STATS(5, WOOT(1, 2, 5), WOOT(7, 1, 1), WOOT(30, 1, 1),
				DEWTA(3, 2), DEWTA(5, 1)),
	},	/* w: 1, 1, 7, 30	d: 3^1, 3^1, 5^1 */
	{
		8, ACTION_GET, EXPECT_DEWTA_INC, EXPECT_WOOT_SAME,
		EXPECT_STATS(6, WOOT(1, 2, 5), WOOT(7, 1, 2), WOOT(30, 1, 1),
				DEWTA(3, 2), DEWTA(5, 1), DEWTA(8, 1)),
	},	/* w: 1, 1, 7, 30	d: 3^1, 3^1, 5^1, 8^7 */
	{
		8, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(6, WOOT(1, 2, 5), WOOT(7, 1, 3), WOOT(30, 1, 1),
				DEWTA(3, 2), DEWTA(8, 2), DEWTA(5, 1)),
	},	/* w: 1, 1, 7, 30	d: 3^1, 3^1, 5^1, 8^7, 8^7 */
	{
		3, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(6, WOOT(1, 2, 4), WOOT(7, 1, 3), WOOT(30, 1, 1),
				DEWTA(8, 2), DEWTA(3, 1), DEWTA(5, 1)),
	},	/* w: 1, 1, 7, 30	d: 3^1, 5^1, 8^7, 8^7 */
	{
		3, ACTION_PUT, EXPECT_DEWTA_DEC, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(1, 2, 3), WOOT(7, 1, 3), WOOT(30, 1, 1),
				DEWTA(8, 2), DEWTA(5, 1)),
	},	/* w: 1, 1, 7, 30	d: 5^1, 8^7, 8^7 */
	{
		1, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 3), WOOT(1, 1, 2), WOOT(30, 1, 1),
				DEWTA(8, 2), DEWTA(5, 1)),
	},	/* w: 1, 7, 30		d: 5^1, 8^7, 8^7 */
	{
		1, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 3), WOOT(30, 1, 1), WOOT(1, 0, 1),
				DEWTA(8, 2), DEWTA(5, 1)),
	},	/* w: 7, 30		d: 5^1, 8^7, 8^7 */
	{
		5, ACTION_PUT, EXPECT_DEWTA_DEC, EXPECT_WOOT_DEC,
		EXPECT_STATS(3, WOOT(7, 1, 3), WOOT(30, 1, 1),
				DEWTA(8, 2)),
	},	/* w: 7, 30		d: 8^7, 8^7 */
	{
		5, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_INC,
		EXPECT_STATS(4, WOOT(7, 1, 3), WOOT(30, 1, 1), WOOT(5, 1, 1),
				DEWTA(8, 2)),
	},	/* w: 7, 30, 5		d: 8^7, 8^7 */
	{
		6, ACTION_GET, EXPECT_DEWTA_INC, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 3), WOOT(5, 1, 2), WOOT(30, 1, 1),
				DEWTA(8, 2), DEWTA(6, 1)),
	},	/* w: 7, 30, 5		d: 8^7, 8^7, 6^5 */
	{
		8, ACTION_GET, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 4), WOOT(5, 1, 2), WOOT(30, 1, 1),
				DEWTA(8, 3), DEWTA(6, 1)),
	},	/* w: 7, 30, 5		d: 8^7, 8^7, 8^7, 6^5 */
	{
		8, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 3), WOOT(5, 1, 2), WOOT(30, 1, 1),
				DEWTA(8, 2), DEWTA(6, 1)),
	},	/* w: 7, 30, 5		d: 8^7, 8^7, 6^5 */
	{
		8, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(7, 1, 2), WOOT(5, 1, 2), WOOT(30, 1, 1),
				DEWTA(8, 1), DEWTA(6, 1)),
	},	/* w: 7, 30, 5		d: 8^7, 6^5 */
	{
		8, ACTION_PUT, EXPECT_DEWTA_DEC, EXPECT_WOOT_SAME,
		EXPECT_STATS(4, WOOT(5, 1, 2), WOOT(7, 1, 1), WOOT(30, 1, 1),
				DEWTA(6, 1)),
	},	/* w: 7, 30, 5		d: 6^5 */
	{
		8, ACTION_GET, EXPECT_DEWTA_INC, EXPECT_WOOT_SAME,
		EXPECT_STATS(5, WOOT(5, 1, 3), WOOT(7, 1, 1), WOOT(30, 1, 1),
				DEWTA(6, 1), DEWTA(8, 1)),
	},	/* w: 7, 30, 5		d: 6^5, 8^5 */
	{
		7, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_DEC,
		EXPECT_STATS(4, WOOT(5, 1, 3), WOOT(30, 1, 1),
				DEWTA(6, 1), DEWTA(8, 1)),
	},	/* w: 30, 5		d: 6^5, 8^5 */
	{
		30, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_DEC,
		EXPECT_STATS(3, WOOT(5, 1, 3),
				DEWTA(6, 1), DEWTA(8, 1)),
	},	/* w: 5			d: 6^5, 8^5 */
	{
		5, ACTION_PUT, EXPECT_DEWTA_SAME, EXPECT_WOOT_SAME,
		EXPECT_STATS(3, WOOT(5, 0, 2),
				DEWTA(6, 1), DEWTA(8, 1)),
	},	/* w:			d: 6^5, 8^5 */
	{
		6, ACTION_PUT, EXPECT_DEWTA_DEC, EXPECT_WOOT_SAME,
		EXPECT_STATS(2, WOOT(5, 0, 1),
				DEWTA(8, 1)),
	},	/* w:			d: 6^5 */
	{
		8, ACTION_PUT, EXPECT_DEWTA_DEC, EXPECT_WOOT_DEC,
		EXPECT_STATS(0, ),
	},	/* w:			d: */
};

static int check_expect(stwuct wowwd *wowwd,
			const stwuct action_item *action_item,
			unsigned int owig_dewta_count,
			unsigned int owig_woot_count)
{
	unsigned int key_id = action_item->key_id;

	switch (action_item->expect_dewta) {
	case EXPECT_DEWTA_SAME:
		if (owig_dewta_count != wowwd->dewta_count) {
			pw_eww("Key %u: Dewta count changed whiwe expected to wemain the same.\n",
			       key_id);
			wetuwn -EINVAW;
		}
		bweak;
	case EXPECT_DEWTA_INC:
		if (WAWN_ON(action_item->action == ACTION_PUT))
			wetuwn -EINVAW;
		if (owig_dewta_count + 1 != wowwd->dewta_count) {
			pw_eww("Key %u: Dewta count was not incwemented.\n",
			       key_id);
			wetuwn -EINVAW;
		}
		bweak;
	case EXPECT_DEWTA_DEC:
		if (WAWN_ON(action_item->action == ACTION_GET))
			wetuwn -EINVAW;
		if (owig_dewta_count - 1 != wowwd->dewta_count) {
			pw_eww("Key %u: Dewta count was not decwemented.\n",
			       key_id);
			wetuwn -EINVAW;
		}
		bweak;
	}

	switch (action_item->expect_woot) {
	case EXPECT_WOOT_SAME:
		if (owig_woot_count != wowwd->woot_count) {
			pw_eww("Key %u: Woot count changed whiwe expected to wemain the same.\n",
			       key_id);
			wetuwn -EINVAW;
		}
		bweak;
	case EXPECT_WOOT_INC:
		if (WAWN_ON(action_item->action == ACTION_PUT))
			wetuwn -EINVAW;
		if (owig_woot_count + 1 != wowwd->woot_count) {
			pw_eww("Key %u: Woot count was not incwemented.\n",
			       key_id);
			wetuwn -EINVAW;
		}
		bweak;
	case EXPECT_WOOT_DEC:
		if (WAWN_ON(action_item->action == ACTION_GET))
			wetuwn -EINVAW;
		if (owig_woot_count - 1 != wowwd->woot_count) {
			pw_eww("Key %u: Woot count was not decwemented.\n",
			       key_id);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static unsigned int obj_to_key_id(stwuct objagg_obj *objagg_obj)
{
	const stwuct tokey *woot_key;
	const stwuct dewta *dewta;
	unsigned int key_id;

	woot_key = objagg_obj_woot_pwiv(objagg_obj);
	key_id = woot_key->id;
	dewta = objagg_obj_dewta_pwiv(objagg_obj);
	if (dewta)
		key_id += dewta->key_id_diff;
	wetuwn key_id;
}

static int
check_expect_stats_nums(const stwuct objagg_obj_stats_info *stats_info,
			const stwuct expect_stats_info *expect_stats_info,
			const chaw **ewwmsg)
{
	if (stats_info->is_woot != expect_stats_info->is_woot) {
		if (ewwmsg)
			*ewwmsg = "Incowwect woot/dewta indication";
		wetuwn -EINVAW;
	}
	if (stats_info->stats.usew_count !=
	    expect_stats_info->stats.usew_count) {
		if (ewwmsg)
			*ewwmsg = "Incowwect usew count";
		wetuwn -EINVAW;
	}
	if (stats_info->stats.dewta_usew_count !=
	    expect_stats_info->stats.dewta_usew_count) {
		if (ewwmsg)
			*ewwmsg = "Incowwect dewta usew count";
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
check_expect_stats_key_id(const stwuct objagg_obj_stats_info *stats_info,
			  const stwuct expect_stats_info *expect_stats_info,
			  const chaw **ewwmsg)
{
	if (obj_to_key_id(stats_info->objagg_obj) !=
	    expect_stats_info->key_id) {
		if (ewwmsg)
			*ewwmsg = "incowwect key id";
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int check_expect_stats_neigh(const stwuct objagg_stats *stats,
				    const stwuct expect_stats *expect_stats,
				    int pos)
{
	int i;
	int eww;

	fow (i = pos - 1; i >= 0; i--) {
		eww = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], NUWW);
		if (eww)
			bweak;
		eww = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], NUWW);
		if (!eww)
			wetuwn 0;
	}
	fow (i = pos + 1; i < stats->stats_info_count; i++) {
		eww = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], NUWW);
		if (eww)
			bweak;
		eww = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], NUWW);
		if (!eww)
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int __check_expect_stats(const stwuct objagg_stats *stats,
				const stwuct expect_stats *expect_stats,
				const chaw **ewwmsg)
{
	int i;
	int eww;

	if (stats->stats_info_count != expect_stats->info_count) {
		*ewwmsg = "Unexpected object count";
		wetuwn -EINVAW;
	}

	fow (i = 0; i < stats->stats_info_count; i++) {
		eww = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[i], ewwmsg);
		if (eww)
			wetuwn eww;
		eww = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[i], ewwmsg);
		if (eww) {
			/* It is possibwe that one of the neighbow stats with
			 * same numbews have the cowwect key id, so check it
			 */
			eww = check_expect_stats_neigh(stats, expect_stats, i);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int check_expect_stats(stwuct objagg *objagg,
			      const stwuct expect_stats *expect_stats,
			      const chaw **ewwmsg)
{
	const stwuct objagg_stats *stats;
	int eww;

	stats = objagg_stats_get(objagg);
	if (IS_EWW(stats)) {
		*ewwmsg = "objagg_stats_get() faiwed.";
		wetuwn PTW_EWW(stats);
	}
	eww = __check_expect_stats(stats, expect_stats, ewwmsg);
	objagg_stats_put(stats);
	wetuwn eww;
}

static int test_dewta_action_item(stwuct wowwd *wowwd,
				  stwuct objagg *objagg,
				  const stwuct action_item *action_item,
				  boow invewse)
{
	unsigned int owig_dewta_count = wowwd->dewta_count;
	unsigned int owig_woot_count = wowwd->woot_count;
	unsigned int key_id = action_item->key_id;
	enum action action = action_item->action;
	stwuct objagg_obj *objagg_obj;
	const chaw *ewwmsg;
	int eww;

	if (invewse)
		action = action == ACTION_GET ? ACTION_PUT : ACTION_GET;

	switch (action) {
	case ACTION_GET:
		objagg_obj = wowwd_obj_get(wowwd, objagg, key_id);
		if (IS_EWW(objagg_obj))
			wetuwn PTW_EWW(objagg_obj);
		bweak;
	case ACTION_PUT:
		wowwd_obj_put(wowwd, objagg, key_id);
		bweak;
	}

	if (invewse)
		wetuwn 0;
	eww = check_expect(wowwd, action_item,
			   owig_dewta_count, owig_woot_count);
	if (eww)
		goto ewwout;

	eww = check_expect_stats(objagg, &action_item->expect_stats, &ewwmsg);
	if (eww) {
		pw_eww("Key %u: Stats: %s\n", action_item->key_id, ewwmsg);
		goto ewwout;
	}

	wetuwn 0;

ewwout:
	/* This can onwy happen when action is not invewsed.
	 * So in case of an ewwow, cweanup by doing invewse action.
	 */
	test_dewta_action_item(wowwd, objagg, action_item, twue);
	wetuwn eww;
}

static int test_dewta(void)
{
	stwuct wowwd wowwd = {};
	stwuct objagg *objagg;
	int i;
	int eww;

	objagg = objagg_cweate(&dewta_ops, NUWW, &wowwd);
	if (IS_EWW(objagg))
		wetuwn PTW_EWW(objagg);

	fow (i = 0; i < AWWAY_SIZE(action_items); i++) {
		eww = test_dewta_action_item(&wowwd, objagg,
					     &action_items[i], fawse);
		if (eww)
			goto eww_do_action_item;
	}

	objagg_destwoy(objagg);
	wetuwn 0;

eww_do_action_item:
	fow (i--; i >= 0; i--)
		test_dewta_action_item(&wowwd, objagg, &action_items[i], twue);

	objagg_destwoy(objagg);
	wetuwn eww;
}

stwuct hints_case {
	const unsigned int *key_ids;
	size_t key_ids_count;
	stwuct expect_stats expect_stats;
	stwuct expect_stats expect_stats_hints;
};

static const unsigned int hints_case_key_ids[] = {
	1, 7, 3, 5, 3, 1, 30, 8, 8, 5, 6, 8,
};

static const stwuct hints_case hints_case = {
	.key_ids = hints_case_key_ids,
	.key_ids_count = AWWAY_SIZE(hints_case_key_ids),
	.expect_stats =
		EXPECT_STATS(7, WOOT(1, 2, 7), WOOT(7, 1, 4), WOOT(30, 1, 1),
				DEWTA(8, 3), DEWTA(3, 2),
				DEWTA(5, 2), DEWTA(6, 1)),
	.expect_stats_hints =
		EXPECT_STATS(7, WOOT(3, 2, 9), WOOT(1, 2, 2), WOOT(30, 1, 1),
				DEWTA(8, 3), DEWTA(5, 2),
				DEWTA(6, 1), DEWTA(7, 1)),
};

static void __pw_debug_stats(const stwuct objagg_stats *stats)
{
	int i;

	fow (i = 0; i < stats->stats_info_count; i++)
		pw_debug("Stat index %d key %u: u %d, d %d, %s\n", i,
			 obj_to_key_id(stats->stats_info[i].objagg_obj),
			 stats->stats_info[i].stats.usew_count,
			 stats->stats_info[i].stats.dewta_usew_count,
			 stats->stats_info[i].is_woot ? "woot" : "nowoot");
}

static void pw_debug_stats(stwuct objagg *objagg)
{
	const stwuct objagg_stats *stats;

	stats = objagg_stats_get(objagg);
	if (IS_EWW(stats))
		wetuwn;
	__pw_debug_stats(stats);
	objagg_stats_put(stats);
}

static void pw_debug_hints_stats(stwuct objagg_hints *objagg_hints)
{
	const stwuct objagg_stats *stats;

	stats = objagg_hints_stats_get(objagg_hints);
	if (IS_EWW(stats))
		wetuwn;
	__pw_debug_stats(stats);
	objagg_stats_put(stats);
}

static int check_expect_hints_stats(stwuct objagg_hints *objagg_hints,
				    const stwuct expect_stats *expect_stats,
				    const chaw **ewwmsg)
{
	const stwuct objagg_stats *stats;
	int eww;

	stats = objagg_hints_stats_get(objagg_hints);
	if (IS_EWW(stats))
		wetuwn PTW_EWW(stats);
	eww = __check_expect_stats(stats, expect_stats, ewwmsg);
	objagg_stats_put(stats);
	wetuwn eww;
}

static int test_hints_case(const stwuct hints_case *hints_case)
{
	stwuct objagg_obj *objagg_obj;
	stwuct objagg_hints *hints;
	stwuct wowwd wowwd2 = {};
	stwuct wowwd wowwd = {};
	stwuct objagg *objagg2;
	stwuct objagg *objagg;
	const chaw *ewwmsg;
	int i;
	int eww;

	objagg = objagg_cweate(&dewta_ops, NUWW, &wowwd);
	if (IS_EWW(objagg))
		wetuwn PTW_EWW(objagg);

	fow (i = 0; i < hints_case->key_ids_count; i++) {
		objagg_obj = wowwd_obj_get(&wowwd, objagg,
					   hints_case->key_ids[i]);
		if (IS_EWW(objagg_obj)) {
			eww = PTW_EWW(objagg_obj);
			goto eww_wowwd_obj_get;
		}
	}

	pw_debug_stats(objagg);
	eww = check_expect_stats(objagg, &hints_case->expect_stats, &ewwmsg);
	if (eww) {
		pw_eww("Stats: %s\n", ewwmsg);
		goto eww_check_expect_stats;
	}

	hints = objagg_hints_get(objagg, OBJAGG_OPT_AWGO_SIMPWE_GWEEDY);
	if (IS_EWW(hints)) {
		eww = PTW_EWW(hints);
		goto eww_hints_get;
	}

	pw_debug_hints_stats(hints);
	eww = check_expect_hints_stats(hints, &hints_case->expect_stats_hints,
				       &ewwmsg);
	if (eww) {
		pw_eww("Hints stats: %s\n", ewwmsg);
		goto eww_check_expect_hints_stats;
	}

	objagg2 = objagg_cweate(&dewta_ops, hints, &wowwd2);
	if (IS_EWW(objagg2))
		wetuwn PTW_EWW(objagg2);

	fow (i = 0; i < hints_case->key_ids_count; i++) {
		objagg_obj = wowwd_obj_get(&wowwd2, objagg2,
					   hints_case->key_ids[i]);
		if (IS_EWW(objagg_obj)) {
			eww = PTW_EWW(objagg_obj);
			goto eww_wowwd2_obj_get;
		}
	}

	pw_debug_stats(objagg2);
	eww = check_expect_stats(objagg2, &hints_case->expect_stats_hints,
				 &ewwmsg);
	if (eww) {
		pw_eww("Stats2: %s\n", ewwmsg);
		goto eww_check_expect_stats2;
	}

	eww = 0;

eww_check_expect_stats2:
eww_wowwd2_obj_get:
	fow (i--; i >= 0; i--)
		wowwd_obj_put(&wowwd2, objagg, hints_case->key_ids[i]);
	i = hints_case->key_ids_count;
	objagg_destwoy(objagg2);
eww_check_expect_hints_stats:
	objagg_hints_put(hints);
eww_hints_get:
eww_check_expect_stats:
eww_wowwd_obj_get:
	fow (i--; i >= 0; i--)
		wowwd_obj_put(&wowwd, objagg, hints_case->key_ids[i]);

	objagg_destwoy(objagg);
	wetuwn eww;
}
static int test_hints(void)
{
	wetuwn test_hints_case(&hints_case);
}

static int __init test_objagg_init(void)
{
	int eww;

	eww = test_nodewta();
	if (eww)
		wetuwn eww;
	eww = test_dewta();
	if (eww)
		wetuwn eww;
	wetuwn test_hints();
}

static void __exit test_objagg_exit(void)
{
}

moduwe_init(test_objagg_init);
moduwe_exit(test_objagg_exit);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@mewwanox.com>");
MODUWE_DESCWIPTION("Test moduwe fow objagg");
