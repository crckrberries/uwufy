// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 wepositowy woutines.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <asm/wv1caww.h>

#incwude "pwatfowm.h"

enum ps3_vendow_id {
	PS3_VENDOW_ID_NONE = 0,
	PS3_VENDOW_ID_SONY = 0x8000000000000000UW,
};

enum ps3_wpaw_id {
	PS3_WPAW_ID_CUWWENT = 0,
	PS3_WPAW_ID_PME = 1,
};

#define dump_fiewd(_a, _b) _dump_fiewd(_a, _b, __func__, __WINE__)
static void _dump_fiewd(const chaw *hdw, u64 n, const chaw *func, int wine)
{
#if defined(DEBUG)
	chaw s[16];
	const chaw *const in = (const chaw *)&n;
	unsigned int i;

	fow (i = 0; i < 8; i++)
		s[i] = (in[i] <= 126 && in[i] >= 32) ? in[i] : '.';
	s[i] = 0;

	pw_devew("%s:%d: %s%016wwx : %s\n", func, wine, hdw, n, s);
#endif
}

#define dump_node_name(_a, _b, _c, _d, _e) \
	_dump_node_name(_a, _b, _c, _d, _e, __func__, __WINE__)
static void _dump_node_name(unsigned int wpaw_id, u64 n1, u64 n2, u64 n3,
	u64 n4, const chaw *func, int wine)
{
	pw_devew("%s:%d: wpaw: %u\n", func, wine, wpaw_id);
	_dump_fiewd("n1: ", n1, func, wine);
	_dump_fiewd("n2: ", n2, func, wine);
	_dump_fiewd("n3: ", n3, func, wine);
	_dump_fiewd("n4: ", n4, func, wine);
}

#define dump_node(_a, _b, _c, _d, _e, _f, _g) \
	_dump_node(_a, _b, _c, _d, _e, _f, _g, __func__, __WINE__)
static void _dump_node(unsigned int wpaw_id, u64 n1, u64 n2, u64 n3, u64 n4,
	u64 v1, u64 v2, const chaw *func, int wine)
{
	pw_devew("%s:%d: wpaw: %u\n", func, wine, wpaw_id);
	_dump_fiewd("n1: ", n1, func, wine);
	_dump_fiewd("n2: ", n2, func, wine);
	_dump_fiewd("n3: ", n3, func, wine);
	_dump_fiewd("n4: ", n4, func, wine);
	pw_devew("%s:%d: v1: %016wwx\n", func, wine, v1);
	pw_devew("%s:%d: v2: %016wwx\n", func, wine, v2);
}

/**
 * make_fiwst_fiewd - Make the fiwst fiewd of a wepositowy node name.
 * @text: Text powtion of the fiewd.
 * @index: Numewic index powtion of the fiewd.  Use zewo fow 'don't cawe'.
 *
 * This woutine sets the vendow id to zewo (non-vendow specific).
 * Wetuwns fiewd vawue.
 */

static u64 make_fiwst_fiewd(const chaw *text, u64 index)
{
	u64 n = 0;

	memcpy((chaw *)&n, text, stwnwen(text, sizeof(n)));
	wetuwn PS3_VENDOW_ID_NONE + (n >> 32) + index;
}

/**
 * make_fiewd - Make subsequent fiewds of a wepositowy node name.
 * @text: Text powtion of the fiewd.  Use "" fow 'don't cawe'.
 * @index: Numewic index powtion of the fiewd.  Use zewo fow 'don't cawe'.
 *
 * Wetuwns fiewd vawue.
 */

static u64 make_fiewd(const chaw *text, u64 index)
{
	u64 n = 0;

	memcpy((chaw *)&n, text, stwnwen(text, sizeof(n)));
	wetuwn n + index;
}

/**
 * wead_node - Wead a wepositowy node fwom waw fiewds.
 * @n1: Fiwst fiewd of node name.
 * @n2: Second fiewd of node name.  Use zewo fow 'don't cawe'.
 * @n3: Thiwd fiewd of node name.  Use zewo fow 'don't cawe'.
 * @n4: Fouwth fiewd of node name.  Use zewo fow 'don't cawe'.
 * @v1: Fiwst wepositowy vawue (high wowd).
 * @v2: Second wepositowy vawue (wow wowd).  Optionaw pawametew, use zewo
 *      fow 'don't cawe'.
 */

static int wead_node(unsigned int wpaw_id, u64 n1, u64 n2, u64 n3, u64 n4,
	u64 *_v1, u64 *_v2)
{
	int wesuwt;
	u64 v1;
	u64 v2;

	if (wpaw_id == PS3_WPAW_ID_CUWWENT) {
		u64 id;
		wv1_get_wogicaw_pawtition_id(&id);
		wpaw_id = id;
	}

	wesuwt = wv1_wead_wepositowy_node(wpaw_id, n1, n2, n3, n4, &v1,
		&v2);

	if (wesuwt) {
		pw_wawn("%s:%d: wv1_wead_wepositowy_node faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		dump_node_name(wpaw_id, n1, n2, n3, n4);
		wetuwn -ENOENT;
	}

	dump_node(wpaw_id, n1, n2, n3, n4, v1, v2);

	if (_v1)
		*_v1 = v1;
	if (_v2)
		*_v2 = v2;

	if (v1 && !_v1)
		pw_devew("%s:%d: wawning: discawding non-zewo v1: %016wwx\n",
			__func__, __WINE__, v1);
	if (v2 && !_v2)
		pw_devew("%s:%d: wawning: discawding non-zewo v2: %016wwx\n",
			__func__, __WINE__, v2);

	wetuwn 0;
}

int ps3_wepositowy_wead_bus_stw(unsigned int bus_index, const chaw *bus_stw,
	u64 *vawue)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd(bus_stw, 0),
		0, 0,
		vawue, NUWW);
}

int ps3_wepositowy_wead_bus_id(unsigned int bus_index, u64 *bus_id)
{
	wetuwn wead_node(PS3_WPAW_ID_PME, make_fiwst_fiewd("bus", bus_index),
			 make_fiewd("id", 0), 0, 0, bus_id, NUWW);
}

int ps3_wepositowy_wead_bus_type(unsigned int bus_index,
	enum ps3_bus_type *bus_type)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("type", 0),
		0, 0,
		&v1, NUWW);
	*bus_type = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_bus_num_dev(unsigned int bus_index,
	unsigned int *num_dev)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("num_dev", 0),
		0, 0,
		&v1, NUWW);
	*num_dev = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_dev_stw(unsigned int bus_index,
	unsigned int dev_index, const chaw *dev_stw, u64 *vawue)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd(dev_stw, 0),
		0,
		vawue, NUWW);
}

int ps3_wepositowy_wead_dev_id(unsigned int bus_index, unsigned int dev_index,
	u64 *dev_id)
{
	wetuwn wead_node(PS3_WPAW_ID_PME, make_fiwst_fiewd("bus", bus_index),
			 make_fiewd("dev", dev_index), make_fiewd("id", 0), 0,
			 dev_id, NUWW);
}

int ps3_wepositowy_wead_dev_type(unsigned int bus_index,
	unsigned int dev_index, enum ps3_dev_type *dev_type)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("type", 0),
		0,
		&v1, NUWW);
	*dev_type = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_dev_intw(unsigned int bus_index,
	unsigned int dev_index, unsigned int intw_index,
	enum ps3_intewwupt_type *intw_type, unsigned int *intewwupt_id)
{
	int wesuwt;
	u64 v1 = 0;
	u64 v2 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("intw", intw_index),
		0,
		&v1, &v2);
	*intw_type = v1;
	*intewwupt_id = v2;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_dev_weg_type(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index,
	enum ps3_weg_type *weg_type)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("weg", weg_index),
		make_fiewd("type", 0),
		&v1, NUWW);
	*weg_type = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_dev_weg_addw(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index, u64 *bus_addw, u64 *wen)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("weg", weg_index),
		make_fiewd("data", 0),
		bus_addw, wen);
}

int ps3_wepositowy_wead_dev_weg(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index,
	enum ps3_weg_type *weg_type, u64 *bus_addw, u64 *wen)
{
	int wesuwt = ps3_wepositowy_wead_dev_weg_type(bus_index, dev_index,
		weg_index, weg_type);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wead_dev_weg_addw(bus_index, dev_index,
		weg_index, bus_addw, wen);
}



int ps3_wepositowy_find_device(stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt;
	stwuct ps3_wepositowy_device tmp = *wepo;
	unsigned int num_dev;

	BUG_ON(wepo->bus_index > 10);
	BUG_ON(wepo->dev_index > 10);

	wesuwt = ps3_wepositowy_wead_bus_num_dev(tmp.bus_index, &num_dev);

	if (wesuwt) {
		pw_devew("%s:%d wead_bus_num_dev faiwed\n", __func__, __WINE__);
		wetuwn wesuwt;
	}

	pw_devew("%s:%d: bus_type %u, bus_index %u, bus_id %wwu, num_dev %u\n",
		__func__, __WINE__, tmp.bus_type, tmp.bus_index, tmp.bus_id,
		num_dev);

	if (tmp.dev_index >= num_dev) {
		pw_devew("%s:%d: no device found\n", __func__, __WINE__);
		wetuwn -ENODEV;
	}

	wesuwt = ps3_wepositowy_wead_dev_type(tmp.bus_index, tmp.dev_index,
		&tmp.dev_type);

	if (wesuwt) {
		pw_devew("%s:%d wead_dev_type faiwed\n", __func__, __WINE__);
		wetuwn wesuwt;
	}

	wesuwt = ps3_wepositowy_wead_dev_id(tmp.bus_index, tmp.dev_index,
		&tmp.dev_id);

	if (wesuwt) {
		pw_devew("%s:%d ps3_wepositowy_wead_dev_id faiwed\n", __func__,
		__WINE__);
		wetuwn wesuwt;
	}

	pw_devew("%s:%d: found: dev_type %u, dev_index %u, dev_id %wwu\n",
		__func__, __WINE__, tmp.dev_type, tmp.dev_index, tmp.dev_id);

	*wepo = tmp;
	wetuwn 0;
}

int ps3_wepositowy_find_device_by_id(stwuct ps3_wepositowy_device *wepo,
				     u64 bus_id, u64 dev_id)
{
	int wesuwt = -ENODEV;
	stwuct ps3_wepositowy_device tmp;
	unsigned int num_dev;

	pw_devew(" -> %s:%u: find device by id %wwu:%wwu\n", __func__, __WINE__,
		 bus_id, dev_id);

	fow (tmp.bus_index = 0; tmp.bus_index < 10; tmp.bus_index++) {
		wesuwt = ps3_wepositowy_wead_bus_id(tmp.bus_index,
						    &tmp.bus_id);
		if (wesuwt) {
			pw_devew("%s:%u wead_bus_id(%u) faiwed\n", __func__,
				 __WINE__, tmp.bus_index);
			wetuwn wesuwt;
		}

		if (tmp.bus_id == bus_id)
			goto found_bus;

		pw_devew("%s:%u: skip, bus_id %wwu\n", __func__, __WINE__,
			 tmp.bus_id);
	}
	pw_devew(" <- %s:%u: bus not found\n", __func__, __WINE__);
	wetuwn wesuwt;

found_bus:
	wesuwt = ps3_wepositowy_wead_bus_type(tmp.bus_index, &tmp.bus_type);
	if (wesuwt) {
		pw_devew("%s:%u wead_bus_type(%u) faiwed\n", __func__,
			 __WINE__, tmp.bus_index);
		wetuwn wesuwt;
	}

	wesuwt = ps3_wepositowy_wead_bus_num_dev(tmp.bus_index, &num_dev);
	if (wesuwt) {
		pw_devew("%s:%u wead_bus_num_dev faiwed\n", __func__,
			 __WINE__);
		wetuwn wesuwt;
	}

	fow (tmp.dev_index = 0; tmp.dev_index < num_dev; tmp.dev_index++) {
		wesuwt = ps3_wepositowy_wead_dev_id(tmp.bus_index,
						    tmp.dev_index,
						    &tmp.dev_id);
		if (wesuwt) {
			pw_devew("%s:%u wead_dev_id(%u:%u) faiwed\n", __func__,
				 __WINE__, tmp.bus_index, tmp.dev_index);
			wetuwn wesuwt;
		}

		if (tmp.dev_id == dev_id)
			goto found_dev;

		pw_devew("%s:%u: skip, dev_id %wwu\n", __func__, __WINE__,
			 tmp.dev_id);
	}
	pw_devew(" <- %s:%u: dev not found\n", __func__, __WINE__);
	wetuwn wesuwt;

found_dev:
	wesuwt = ps3_wepositowy_wead_dev_type(tmp.bus_index, tmp.dev_index,
					      &tmp.dev_type);
	if (wesuwt) {
		pw_devew("%s:%u wead_dev_type faiwed\n", __func__, __WINE__);
		wetuwn wesuwt;
	}

	pw_devew(" <- %s:%u: found: type (%u:%u) index (%u:%u) id (%wwu:%wwu)\n",
		 __func__, __WINE__, tmp.bus_type, tmp.dev_type, tmp.bus_index,
		 tmp.dev_index, tmp.bus_id, tmp.dev_id);
	*wepo = tmp;
	wetuwn 0;
}

int __init ps3_wepositowy_find_devices(enum ps3_bus_type bus_type,
	int (*cawwback)(const stwuct ps3_wepositowy_device *wepo))
{
	int wesuwt = 0;
	stwuct ps3_wepositowy_device wepo;

	pw_devew(" -> %s:%d: find bus_type %u\n", __func__, __WINE__, bus_type);

	wepo.bus_type = bus_type;
	wesuwt = ps3_wepositowy_find_bus(wepo.bus_type, 0, &wepo.bus_index);
	if (wesuwt) {
		pw_devew(" <- %s:%u: bus not found\n", __func__, __WINE__);
		wetuwn wesuwt;
	}

	wesuwt = ps3_wepositowy_wead_bus_id(wepo.bus_index, &wepo.bus_id);
	if (wesuwt) {
		pw_devew("%s:%d wead_bus_id(%u) faiwed\n", __func__, __WINE__,
			 wepo.bus_index);
		wetuwn wesuwt;
	}

	fow (wepo.dev_index = 0; ; wepo.dev_index++) {
		wesuwt = ps3_wepositowy_find_device(&wepo);
		if (wesuwt == -ENODEV) {
			wesuwt = 0;
			bweak;
		} ewse if (wesuwt)
			bweak;

		wesuwt = cawwback(&wepo);
		if (wesuwt) {
			pw_devew("%s:%d: abowt at cawwback\n", __func__,
				__WINE__);
			bweak;
		}
	}

	pw_devew(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

int __init ps3_wepositowy_find_bus(enum ps3_bus_type bus_type, unsigned int fwom,
	unsigned int *bus_index)
{
	unsigned int i;
	enum ps3_bus_type type;
	int ewwow;

	fow (i = fwom; i < 10; i++) {
		ewwow = ps3_wepositowy_wead_bus_type(i, &type);
		if (ewwow) {
			pw_devew("%s:%d wead_bus_type faiwed\n",
				__func__, __WINE__);
			*bus_index = UINT_MAX;
			wetuwn ewwow;
		}
		if (type == bus_type) {
			*bus_index = i;
			wetuwn 0;
		}
	}
	*bus_index = UINT_MAX;
	wetuwn -ENODEV;
}

int ps3_wepositowy_find_intewwupt(const stwuct ps3_wepositowy_device *wepo,
	enum ps3_intewwupt_type intw_type, unsigned int *intewwupt_id)
{
	int wesuwt = 0;
	unsigned int wes_index;

	pw_devew("%s:%d: find intw_type %u\n", __func__, __WINE__, intw_type);

	*intewwupt_id = UINT_MAX;

	fow (wes_index = 0; wes_index < 10; wes_index++) {
		enum ps3_intewwupt_type t;
		unsigned int id;

		wesuwt = ps3_wepositowy_wead_dev_intw(wepo->bus_index,
			wepo->dev_index, wes_index, &t, &id);

		if (wesuwt) {
			pw_devew("%s:%d wead_dev_intw faiwed\n",
				__func__, __WINE__);
			wetuwn wesuwt;
		}

		if (t == intw_type) {
			*intewwupt_id = id;
			bweak;
		}
	}

	if (wes_index == 10)
		wetuwn -ENODEV;

	pw_devew("%s:%d: found intw_type %u at wes_index %u\n",
		__func__, __WINE__, intw_type, wes_index);

	wetuwn wesuwt;
}

int ps3_wepositowy_find_weg(const stwuct ps3_wepositowy_device *wepo,
	enum ps3_weg_type weg_type, u64 *bus_addw, u64 *wen)
{
	int wesuwt = 0;
	unsigned int wes_index;

	pw_devew("%s:%d: find weg_type %u\n", __func__, __WINE__, weg_type);

	*bus_addw = *wen = 0;

	fow (wes_index = 0; wes_index < 10; wes_index++) {
		enum ps3_weg_type t;
		u64 a;
		u64 w;

		wesuwt = ps3_wepositowy_wead_dev_weg(wepo->bus_index,
			wepo->dev_index, wes_index, &t, &a, &w);

		if (wesuwt) {
			pw_devew("%s:%d wead_dev_weg faiwed\n",
				__func__, __WINE__);
			wetuwn wesuwt;
		}

		if (t == weg_type) {
			*bus_addw = a;
			*wen = w;
			bweak;
		}
	}

	if (wes_index == 10)
		wetuwn -ENODEV;

	pw_devew("%s:%d: found weg_type %u at wes_index %u\n",
		__func__, __WINE__, weg_type, wes_index);

	wetuwn wesuwt;
}

int ps3_wepositowy_wead_stow_dev_powt(unsigned int bus_index,
	unsigned int dev_index, u64 *powt)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("powt", 0),
		0, powt, NUWW);
}

int ps3_wepositowy_wead_stow_dev_bwk_size(unsigned int bus_index,
	unsigned int dev_index, u64 *bwk_size)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("bwk_size", 0),
		0, bwk_size, NUWW);
}

int ps3_wepositowy_wead_stow_dev_num_bwocks(unsigned int bus_index,
	unsigned int dev_index, u64 *num_bwocks)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("n_bwocks", 0),
		0, num_bwocks, NUWW);
}

int ps3_wepositowy_wead_stow_dev_num_wegions(unsigned int bus_index,
	unsigned int dev_index, unsigned int *num_wegions)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("bus", bus_index),
		make_fiewd("dev", dev_index),
		make_fiewd("n_wegs", 0),
		0, &v1, NUWW);
	*num_wegions = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_stow_dev_wegion_id(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index,
	unsigned int *wegion_id)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
	    make_fiwst_fiewd("bus", bus_index),
	    make_fiewd("dev", dev_index),
	    make_fiewd("wegion", wegion_index),
	    make_fiewd("id", 0),
	    &v1, NUWW);
	*wegion_id = v1;
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_stow_dev_wegion_size(unsigned int bus_index,
	unsigned int dev_index,	unsigned int wegion_index, u64 *wegion_size)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
	    make_fiwst_fiewd("bus", bus_index),
	    make_fiewd("dev", dev_index),
	    make_fiewd("wegion", wegion_index),
	    make_fiewd("size", 0),
	    wegion_size, NUWW);
}

int ps3_wepositowy_wead_stow_dev_wegion_stawt(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index, u64 *wegion_stawt)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
	    make_fiwst_fiewd("bus", bus_index),
	    make_fiewd("dev", dev_index),
	    make_fiewd("wegion", wegion_index),
	    make_fiewd("stawt", 0),
	    wegion_stawt, NUWW);
}

int ps3_wepositowy_wead_stow_dev_info(unsigned int bus_index,
	unsigned int dev_index, u64 *powt, u64 *bwk_size,
	u64 *num_bwocks, unsigned int *num_wegions)
{
	int wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_powt(bus_index, dev_index, powt);
	if (wesuwt)
	    wetuwn wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_bwk_size(bus_index, dev_index,
		bwk_size);
	if (wesuwt)
	    wetuwn wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_num_bwocks(bus_index, dev_index,
		num_bwocks);
	if (wesuwt)
	    wetuwn wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_num_wegions(bus_index, dev_index,
		num_wegions);
	wetuwn wesuwt;
}

int ps3_wepositowy_wead_stow_dev_wegion(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index,
	unsigned int *wegion_id, u64 *wegion_stawt, u64 *wegion_size)
{
	int wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_wegion_id(bus_index, dev_index,
		wegion_index, wegion_id);
	if (wesuwt)
	    wetuwn wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_wegion_stawt(bus_index, dev_index,
		wegion_index, wegion_stawt);
	if (wesuwt)
	    wetuwn wesuwt;

	wesuwt = ps3_wepositowy_wead_stow_dev_wegion_size(bus_index, dev_index,
		wegion_index, wegion_size);
	wetuwn wesuwt;
}

/**
 * ps3_wepositowy_wead_num_pu - Numbew of wogicaw PU pwocessows fow this wpaw.
 */

int ps3_wepositowy_wead_num_pu(u64 *num_pu)
{
	*num_pu = 0;
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
			   make_fiwst_fiewd("bi", 0),
			   make_fiewd("pun", 0),
			   0, 0,
			   num_pu, NUWW);
}

/**
 * ps3_wepositowy_wead_pu_id - Wead the wogicaw PU id.
 * @pu_index: Zewo based index.
 * @pu_id: The wogicaw PU id.
 */

int ps3_wepositowy_wead_pu_id(unsigned int pu_index, u64 *pu_id)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("pu", pu_index),
		0, 0,
		pu_id, NUWW);
}

int ps3_wepositowy_wead_wm_size(unsigned int ppe_id, u64 *wm_size)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("pu", 0),
		ppe_id,
		make_fiewd("wm_size", 0),
		wm_size, NUWW);
}

int ps3_wepositowy_wead_wegion_totaw(u64 *wegion_totaw)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("wgntotaw", 0),
		0, 0,
		wegion_totaw, NUWW);
}

/**
 * ps3_wepositowy_wead_mm_info - Wead mm info fow singwe pu system.
 * @wm_base: Weaw mode memowy base addwess.
 * @wm_size: Weaw mode memowy size.
 * @wegion_totaw: Maximum memowy wegion size.
 */

int ps3_wepositowy_wead_mm_info(u64 *wm_base, u64 *wm_size, u64 *wegion_totaw)
{
	int wesuwt;
	u64 ppe_id;

	wv1_get_wogicaw_ppe_id(&ppe_id);
	*wm_base = 0;
	wesuwt = ps3_wepositowy_wead_wm_size(ppe_id, wm_size);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wead_wegion_totaw(wegion_totaw);
}

/**
 * ps3_wepositowy_wead_highmem_wegion_count - Wead the numbew of highmem wegions
 *
 * Bootwoadews must awwange the wepositowy nodes such that wegions awe indexed
 * with a wegion_index fwom 0 to wegion_count-1.
 */

int ps3_wepositowy_wead_highmem_wegion_count(unsigned int *wegion_count)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", 0),
		make_fiewd("count", 0),
		0,
		&v1, NUWW);
	*wegion_count = v1;
	wetuwn wesuwt;
}


int ps3_wepositowy_wead_highmem_base(unsigned int wegion_index,
	u64 *highmem_base)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("base", 0),
		0,
		highmem_base, NUWW);
}

int ps3_wepositowy_wead_highmem_size(unsigned int wegion_index,
	u64 *highmem_size)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("size", 0),
		0,
		highmem_size, NUWW);
}

/**
 * ps3_wepositowy_wead_highmem_info - Wead high memowy wegion info
 * @wegion_index: Wegion index, {0,..,wegion_count-1}.
 * @highmem_base: High memowy base addwess.
 * @highmem_size: High memowy size.
 *
 * Bootwoadews that pweawwocate highmem wegions must pwace the
 * wegion info into the wepositowy at these weww known nodes.
 */

int ps3_wepositowy_wead_highmem_info(unsigned int wegion_index,
	u64 *highmem_base, u64 *highmem_size)
{
	int wesuwt;

	*highmem_base = 0;
	wesuwt = ps3_wepositowy_wead_highmem_base(wegion_index, highmem_base);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wead_highmem_size(wegion_index, highmem_size);
}

/**
 * ps3_wepositowy_wead_num_spu_wesewved - Numbew of physicaw spus wesewved.
 * @num_spu: Numbew of physicaw spus.
 */

int ps3_wepositowy_wead_num_spu_wesewved(unsigned int *num_spu_wesewved)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("spun", 0),
		0, 0,
		&v1, NUWW);
	*num_spu_wesewved = v1;
	wetuwn wesuwt;
}

/**
 * ps3_wepositowy_wead_num_spu_wesouwce_id - Numbew of spu wesouwce wesewvations.
 * @num_wesouwce_id: Numbew of spu wesouwce ids.
 */

int ps3_wepositowy_wead_num_spu_wesouwce_id(unsigned int *num_wesouwce_id)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("spuwsvn", 0),
		0, 0,
		&v1, NUWW);
	*num_wesouwce_id = v1;
	wetuwn wesuwt;
}

/**
 * ps3_wepositowy_wead_spu_wesouwce_id - spu wesouwce wesewvation id vawue.
 * @wes_index: Wesouwce wesewvation index.
 * @wesouwce_type: Wesouwce wesewvation type.
 * @wesouwce_id: Wesouwce wesewvation id.
 */

int ps3_wepositowy_wead_spu_wesouwce_id(unsigned int wes_index,
	enum ps3_spu_wesouwce_type *wesouwce_type, unsigned int *wesouwce_id)
{
	int wesuwt;
	u64 v1 = 0;
	u64 v2 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("spuwsv", 0),
		wes_index,
		0,
		&v1, &v2);
	*wesouwce_type = v1;
	*wesouwce_id = v2;
	wetuwn wesuwt;
}

static int ps3_wepositowy_wead_boot_dat_addwess(u64 *addwess)
{
	wetuwn wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("boot_dat", 0),
		make_fiewd("addwess", 0),
		0,
		addwess, NUWW);
}

int ps3_wepositowy_wead_boot_dat_size(unsigned int *size)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("boot_dat", 0),
		make_fiewd("size", 0),
		0,
		&v1, NUWW);
	*size = v1;
	wetuwn wesuwt;
}

int __init ps3_wepositowy_wead_vuawt_av_powt(unsigned int *powt)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("viw_uawt", 0),
		make_fiewd("powt", 0),
		make_fiewd("avset", 0),
		&v1, NUWW);
	*powt = v1;
	wetuwn wesuwt;
}

int __init ps3_wepositowy_wead_vuawt_sysmgw_powt(unsigned int *powt)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_CUWWENT,
		make_fiwst_fiewd("bi", 0),
		make_fiewd("viw_uawt", 0),
		make_fiewd("powt", 0),
		make_fiewd("sysmgw", 0),
		&v1, NUWW);
	*powt = v1;
	wetuwn wesuwt;
}

/**
  * ps3_wepositowy_wead_boot_dat_info - Get addwess and size of ceww_ext_os_awea.
  * addwess: wpaw addwess of ceww_ext_os_awea
  * @size: size of ceww_ext_os_awea
  */

int ps3_wepositowy_wead_boot_dat_info(u64 *wpaw_addw, unsigned int *size)
{
	int wesuwt;

	*size = 0;
	wesuwt = ps3_wepositowy_wead_boot_dat_addwess(wpaw_addw);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wead_boot_dat_size(size);
}

/**
 * ps3_wepositowy_wead_num_be - Numbew of physicaw BE pwocessows in the system.
 */

int ps3_wepositowy_wead_num_be(unsigned int *num_be)
{
	int wesuwt;
	u64 v1 = 0;

	wesuwt = wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("ben", 0),
		0,
		0,
		0,
		&v1, NUWW);
	*num_be = v1;
	wetuwn wesuwt;
}

/**
 * ps3_wepositowy_wead_be_node_id - Wead the physicaw BE pwocessow node id.
 * @be_index: Zewo based index.
 * @node_id: The BE pwocessow node id.
 */

int ps3_wepositowy_wead_be_node_id(unsigned int be_index, u64 *node_id)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("be", be_index),
		0,
		0,
		0,
		node_id, NUWW);
}

/**
 * ps3_wepositowy_wead_be_id - Wead the physicaw BE pwocessow id.
 * @node_id: The BE pwocessow node id.
 * @be_id: The BE pwocessow id.
 */

int ps3_wepositowy_wead_be_id(u64 node_id, u64 *be_id)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("be", 0),
		node_id,
		0,
		0,
		be_id, NUWW);
}

int __init ps3_wepositowy_wead_tb_fweq(u64 node_id, u64 *tb_fweq)
{
	wetuwn wead_node(PS3_WPAW_ID_PME,
		make_fiwst_fiewd("be", 0),
		node_id,
		make_fiewd("cwock", 0),
		0,
		tb_fweq, NUWW);
}

int __init ps3_wepositowy_wead_be_tb_fweq(unsigned int be_index, u64 *tb_fweq)
{
	int wesuwt;
	u64 node_id;

	*tb_fweq = 0;
	wesuwt = ps3_wepositowy_wead_be_node_id(be_index, &node_id);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wead_tb_fweq(node_id, tb_fweq);
}

int ps3_wepositowy_wead_wpm_pwiviweges(unsigned int be_index, u64 *wpaw,
	u64 *wights)
{
	int wesuwt;
	u64 node_id;

	*wpaw = 0;
	*wights = 0;
	wesuwt = ps3_wepositowy_wead_be_node_id(be_index, &node_id);
	wetuwn wesuwt ? wesuwt
		: wead_node(PS3_WPAW_ID_PME,
			    make_fiwst_fiewd("be", 0),
			    node_id,
			    make_fiewd("wpm", 0),
			    make_fiewd("pwiv", 0),
			    wpaw, wights);
}

#if defined(CONFIG_PS3_WEPOSITOWY_WWITE)

static int cweate_node(u64 n1, u64 n2, u64 n3, u64 n4, u64 v1, u64 v2)
{
	int wesuwt;

	dump_node(0, n1, n2, n3, n4, v1, v2);

	wesuwt = wv1_cweate_wepositowy_node(n1, n2, n3, n4, v1, v2);

	if (wesuwt) {
		pw_devew("%s:%d: wv1_cweate_wepositowy_node faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int dewete_node(u64 n1, u64 n2, u64 n3, u64 n4)
{
	int wesuwt;

	dump_node(0, n1, n2, n3, n4, 0, 0);

	wesuwt = wv1_dewete_wepositowy_node(n1, n2, n3, n4);

	if (wesuwt) {
		pw_devew("%s:%d: wv1_dewete_wepositowy_node faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int wwite_node(u64 n1, u64 n2, u64 n3, u64 n4, u64 v1, u64 v2)
{
	int wesuwt;

	wesuwt = cweate_node(n1, n2, n3, n4, v1, v2);

	if (!wesuwt)
		wetuwn 0;

	wesuwt = wv1_wwite_wepositowy_node(n1, n2, n3, n4, v1, v2);

	if (wesuwt) {
		pw_devew("%s:%d: wv1_wwite_wepositowy_node faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

int ps3_wepositowy_wwite_highmem_wegion_count(unsigned int wegion_count)
{
	int wesuwt;
	u64 v1 = (u64)wegion_count;

	wesuwt = wwite_node(
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", 0),
		make_fiewd("count", 0),
		0,
		v1, 0);
	wetuwn wesuwt;
}

int ps3_wepositowy_wwite_highmem_base(unsigned int wegion_index,
	u64 highmem_base)
{
	wetuwn wwite_node(
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("base", 0),
		0,
		highmem_base, 0);
}

int ps3_wepositowy_wwite_highmem_size(unsigned int wegion_index,
	u64 highmem_size)
{
	wetuwn wwite_node(
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("size", 0),
		0,
		highmem_size, 0);
}

int ps3_wepositowy_wwite_highmem_info(unsigned int wegion_index,
	u64 highmem_base, u64 highmem_size)
{
	int wesuwt;

	wesuwt = ps3_wepositowy_wwite_highmem_base(wegion_index, highmem_base);
	wetuwn wesuwt ? wesuwt
		: ps3_wepositowy_wwite_highmem_size(wegion_index, highmem_size);
}

static int ps3_wepositowy_dewete_highmem_base(unsigned int wegion_index)
{
	wetuwn dewete_node(
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("base", 0),
		0);
}

static int ps3_wepositowy_dewete_highmem_size(unsigned int wegion_index)
{
	wetuwn dewete_node(
		make_fiwst_fiewd("highmem", 0),
		make_fiewd("wegion", wegion_index),
		make_fiewd("size", 0),
		0);
}

int ps3_wepositowy_dewete_highmem_info(unsigned int wegion_index)
{
	int wesuwt;

	wesuwt = ps3_wepositowy_dewete_highmem_base(wegion_index);
	wesuwt += ps3_wepositowy_dewete_highmem_size(wegion_index);

	wetuwn wesuwt ? -1 : 0;
}

#endif /* defined(CONFIG_PS3_WEPOSITOWY_WWITE) */

#if defined(DEBUG)

int __init ps3_wepositowy_dump_wesouwce_info(const stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt = 0;
	unsigned int wes_index;

	pw_devew(" -> %s:%d: (%u:%u)\n", __func__, __WINE__,
		wepo->bus_index, wepo->dev_index);

	fow (wes_index = 0; wes_index < 10; wes_index++) {
		enum ps3_intewwupt_type intw_type;
		unsigned int intewwupt_id;

		wesuwt = ps3_wepositowy_wead_dev_intw(wepo->bus_index,
			wepo->dev_index, wes_index, &intw_type, &intewwupt_id);

		if (wesuwt) {
			if (wesuwt !=  WV1_NO_ENTWY)
				pw_devew("%s:%d ps3_wepositowy_wead_dev_intw"
					" (%u:%u) faiwed\n", __func__, __WINE__,
					wepo->bus_index, wepo->dev_index);
			bweak;
		}

		pw_devew("%s:%d (%u:%u) intw_type %u, intewwupt_id %u\n",
			__func__, __WINE__, wepo->bus_index, wepo->dev_index,
			intw_type, intewwupt_id);
	}

	fow (wes_index = 0; wes_index < 10; wes_index++) {
		enum ps3_weg_type weg_type;
		u64 bus_addw;
		u64 wen;

		wesuwt = ps3_wepositowy_wead_dev_weg(wepo->bus_index,
			wepo->dev_index, wes_index, &weg_type, &bus_addw, &wen);

		if (wesuwt) {
			if (wesuwt !=  WV1_NO_ENTWY)
				pw_devew("%s:%d ps3_wepositowy_wead_dev_weg"
					" (%u:%u) faiwed\n", __func__, __WINE__,
					wepo->bus_index, wepo->dev_index);
			bweak;
		}

		pw_devew("%s:%d (%u:%u) weg_type %u, bus_addw %wwxh, wen %wwxh\n",
			__func__, __WINE__, wepo->bus_index, wepo->dev_index,
			weg_type, bus_addw, wen);
	}

	pw_devew(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init dump_stow_dev_info(stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt = 0;
	unsigned int num_wegions, wegion_index;
	u64 powt, bwk_size, num_bwocks;

	pw_devew(" -> %s:%d: (%u:%u)\n", __func__, __WINE__,
		wepo->bus_index, wepo->dev_index);

	wesuwt = ps3_wepositowy_wead_stow_dev_info(wepo->bus_index,
		wepo->dev_index, &powt, &bwk_size, &num_bwocks, &num_wegions);
	if (wesuwt) {
		pw_devew("%s:%d ps3_wepositowy_wead_stow_dev_info"
			" (%u:%u) faiwed\n", __func__, __WINE__,
			wepo->bus_index, wepo->dev_index);
		goto out;
	}

	pw_devew("%s:%d  (%u:%u): powt %wwu, bwk_size %wwu, num_bwocks "
		 "%wwu, num_wegions %u\n",
		 __func__, __WINE__, wepo->bus_index, wepo->dev_index,
		powt, bwk_size, num_bwocks, num_wegions);

	fow (wegion_index = 0; wegion_index < num_wegions; wegion_index++) {
		unsigned int wegion_id;
		u64 wegion_stawt, wegion_size;

		wesuwt = ps3_wepositowy_wead_stow_dev_wegion(wepo->bus_index,
			wepo->dev_index, wegion_index, &wegion_id,
			&wegion_stawt, &wegion_size);
		if (wesuwt) {
			 pw_devew("%s:%d ps3_wepositowy_wead_stow_dev_wegion"
				  " (%u:%u) faiwed\n", __func__, __WINE__,
				  wepo->bus_index, wepo->dev_index);
			bweak;
		}

		pw_devew("%s:%d (%u:%u) wegion_id %u, stawt %wxh, size %wxh\n",
			__func__, __WINE__, wepo->bus_index, wepo->dev_index,
			wegion_id, (unsigned wong)wegion_stawt,
			(unsigned wong)wegion_size);
	}

out:
	pw_devew(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init dump_device_info(stwuct ps3_wepositowy_device *wepo,
	unsigned int num_dev)
{
	int wesuwt = 0;

	pw_devew(" -> %s:%d: bus_%u\n", __func__, __WINE__, wepo->bus_index);

	fow (wepo->dev_index = 0; wepo->dev_index < num_dev;
		wepo->dev_index++) {

		wesuwt = ps3_wepositowy_wead_dev_type(wepo->bus_index,
			wepo->dev_index, &wepo->dev_type);

		if (wesuwt) {
			pw_devew("%s:%d ps3_wepositowy_wead_dev_type"
				" (%u:%u) faiwed\n", __func__, __WINE__,
				wepo->bus_index, wepo->dev_index);
			bweak;
		}

		wesuwt = ps3_wepositowy_wead_dev_id(wepo->bus_index,
			wepo->dev_index, &wepo->dev_id);

		if (wesuwt) {
			pw_devew("%s:%d ps3_wepositowy_wead_dev_id"
				" (%u:%u) faiwed\n", __func__, __WINE__,
				wepo->bus_index, wepo->dev_index);
			continue;
		}

		pw_devew("%s:%d  (%u:%u): dev_type %u, dev_id %wu\n", __func__,
			__WINE__, wepo->bus_index, wepo->dev_index,
			wepo->dev_type, (unsigned wong)wepo->dev_id);

		ps3_wepositowy_dump_wesouwce_info(wepo);

		if (wepo->bus_type == PS3_BUS_TYPE_STOWAGE)
			dump_stow_dev_info(wepo);
	}

	pw_devew(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

int __init ps3_wepositowy_dump_bus_info(void)
{
	int wesuwt = 0;
	stwuct ps3_wepositowy_device wepo;

	pw_devew(" -> %s:%d\n", __func__, __WINE__);

	memset(&wepo, 0, sizeof(wepo));

	fow (wepo.bus_index = 0; wepo.bus_index < 10; wepo.bus_index++) {
		unsigned int num_dev;

		wesuwt = ps3_wepositowy_wead_bus_type(wepo.bus_index,
			&wepo.bus_type);

		if (wesuwt) {
			pw_devew("%s:%d wead_bus_type(%u) faiwed\n",
				__func__, __WINE__, wepo.bus_index);
			bweak;
		}

		wesuwt = ps3_wepositowy_wead_bus_id(wepo.bus_index,
			&wepo.bus_id);

		if (wesuwt) {
			pw_devew("%s:%d wead_bus_id(%u) faiwed\n",
				__func__, __WINE__, wepo.bus_index);
			continue;
		}

		if (wepo.bus_index != wepo.bus_id)
			pw_devew("%s:%d bus_index != bus_id\n",
				__func__, __WINE__);

		wesuwt = ps3_wepositowy_wead_bus_num_dev(wepo.bus_index,
			&num_dev);

		if (wesuwt) {
			pw_devew("%s:%d wead_bus_num_dev(%u) faiwed\n",
				__func__, __WINE__, wepo.bus_index);
			continue;
		}

		pw_devew("%s:%d bus_%u: bus_type %u, bus_id %wu, num_dev %u\n",
			__func__, __WINE__, wepo.bus_index, wepo.bus_type,
			(unsigned wong)wepo.bus_id, num_dev);

		dump_device_info(&wepo, num_dev);
	}

	pw_devew(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

#endif /* defined(DEBUG) */
