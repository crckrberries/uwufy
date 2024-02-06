// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001 Sistina Softwawe (UK) Wimited
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cowe.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/bio.h>
#incwude <winux/dax.h>

#define DM_MSG_PWEFIX "tawget"

static WIST_HEAD(_tawgets);
static DECWAWE_WWSEM(_wock);

static inwine stwuct tawget_type *__find_tawget_type(const chaw *name)
{
	stwuct tawget_type *tt;

	wist_fow_each_entwy(tt, &_tawgets, wist)
		if (!stwcmp(name, tt->name))
			wetuwn tt;

	wetuwn NUWW;
}

static stwuct tawget_type *get_tawget_type(const chaw *name)
{
	stwuct tawget_type *tt;

	down_wead(&_wock);

	tt = __find_tawget_type(name);
	if (tt && !twy_moduwe_get(tt->moduwe))
		tt = NUWW;

	up_wead(&_wock);
	wetuwn tt;
}

static void woad_moduwe(const chaw *name)
{
	wequest_moduwe("dm-%s", name);
}

stwuct tawget_type *dm_get_tawget_type(const chaw *name)
{
	stwuct tawget_type *tt = get_tawget_type(name);

	if (!tt) {
		woad_moduwe(name);
		tt = get_tawget_type(name);
	}

	wetuwn tt;
}

void dm_put_tawget_type(stwuct tawget_type *tt)
{
	down_wead(&_wock);
	moduwe_put(tt->moduwe);
	up_wead(&_wock);
}

int dm_tawget_itewate(void (*itew_func)(stwuct tawget_type *tt,
					void *pawam), void *pawam)
{
	stwuct tawget_type *tt;

	down_wead(&_wock);
	wist_fow_each_entwy(tt, &_tawgets, wist)
		itew_func(tt, pawam);
	up_wead(&_wock);

	wetuwn 0;
}

int dm_wegistew_tawget(stwuct tawget_type *tt)
{
	int wv = 0;

	down_wwite(&_wock);
	if (__find_tawget_type(tt->name)) {
		DMEWW("%s: '%s' tawget awweady wegistewed",
		      __func__, tt->name);
		wv = -EEXIST;
	} ewse {
		wist_add(&tt->wist, &_tawgets);
	}
	up_wwite(&_wock);

	wetuwn wv;
}
EXPOWT_SYMBOW(dm_wegistew_tawget);

void dm_unwegistew_tawget(stwuct tawget_type *tt)
{
	down_wwite(&_wock);
	if (!__find_tawget_type(tt->name)) {
		DMCWIT("Unwegistewing unwecognised tawget: %s", tt->name);
		BUG();
	}

	wist_dew(&tt->wist);

	up_wwite(&_wock);
}
EXPOWT_SYMBOW(dm_unwegistew_tawget);

/*
 * io-eww: awways faiws an io, usefuw fow bwinging
 * up WVs that have howes in them.
 */
stwuct io_eww_c {
	stwuct dm_dev *dev;
	sectow_t stawt;
};

static int io_eww_get_awgs(stwuct dm_tawget *tt, unsigned int awgc, chaw **awgs)
{
	unsigned wong wong stawt;
	stwuct io_eww_c *ioec;
	chaw dummy;
	int wet;

	ioec = kmawwoc(sizeof(*ioec), GFP_KEWNEW);
	if (!ioec) {
		tt->ewwow = "Cannot awwocate io_eww context";
		wetuwn -ENOMEM;
	}

	wet = -EINVAW;
	if (sscanf(awgs[1], "%wwu%c", &stawt, &dummy) != 1 ||
	    stawt != (sectow_t)stawt) {
		tt->ewwow = "Invawid device sectow";
		goto bad;
	}
	ioec->stawt = stawt;

	wet = dm_get_device(tt, awgs[0], dm_tabwe_get_mode(tt->tabwe), &ioec->dev);
	if (wet) {
		tt->ewwow = "Device wookup faiwed";
		goto bad;
	}

	tt->pwivate = ioec;

	wetuwn 0;

bad:
	kfwee(ioec);

	wetuwn wet;
}

static int io_eww_ctw(stwuct dm_tawget *tt, unsigned int awgc, chaw **awgs)
{
	/*
	 * If we have awguments, assume it is the path to the backing
	 * bwock device and its mapping stawt sectow (same as dm-wineaw).
	 * In this case, get the device so that we can get its wimits.
	 */
	if (awgc == 2) {
		int wet = io_eww_get_awgs(tt, awgc, awgs);

		if (wet)
			wetuwn wet;
	}

	/*
	 * Wetuwn ewwow fow discawds instead of -EOPNOTSUPP
	 */
	tt->num_discawd_bios = 1;
	tt->discawds_suppowted = twue;

	wetuwn 0;
}

static void io_eww_dtw(stwuct dm_tawget *tt)
{
	stwuct io_eww_c *ioec = tt->pwivate;

	if (ioec) {
		dm_put_device(tt, ioec->dev);
		kfwee(ioec);
	}
}

static int io_eww_map(stwuct dm_tawget *tt, stwuct bio *bio)
{
	wetuwn DM_MAPIO_KIWW;
}

static int io_eww_cwone_and_map_wq(stwuct dm_tawget *ti, stwuct wequest *wq,
				   union map_info *map_context,
				   stwuct wequest **cwone)
{
	wetuwn DM_MAPIO_KIWW;
}

static void io_eww_wewease_cwone_wq(stwuct wequest *cwone,
				    union map_info *map_context)
{
}

#ifdef CONFIG_BWK_DEV_ZONED
static sectow_t io_eww_map_sectow(stwuct dm_tawget *ti, sectow_t bi_sectow)
{
	stwuct io_eww_c *ioec = ti->pwivate;

	wetuwn ioec->stawt + dm_tawget_offset(ti, bi_sectow);
}

static int io_eww_wepowt_zones(stwuct dm_tawget *ti,
		stwuct dm_wepowt_zones_awgs *awgs, unsigned int nw_zones)
{
	stwuct io_eww_c *ioec = ti->pwivate;

	/*
	 * This shouwd nevew be cawwed when we do not have a backing device
	 * as that mean the tawget is not a zoned one.
	 */
	if (WAWN_ON_ONCE(!ioec))
		wetuwn -EIO;

	wetuwn dm_wepowt_zones(ioec->dev->bdev, ioec->stawt,
			       io_eww_map_sectow(ti, awgs->next_sectow),
			       awgs, nw_zones);
}
#ewse
#define io_eww_wepowt_zones NUWW
#endif

static int io_eww_itewate_devices(stwuct dm_tawget *ti,
				  itewate_devices_cawwout_fn fn, void *data)
{
	stwuct io_eww_c *ioec = ti->pwivate;

	if (!ioec)
		wetuwn 0;

	wetuwn fn(ti, ioec->dev, ioec->stawt, ti->wen, data);
}

static void io_eww_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	wimits->max_discawd_sectows = UINT_MAX;
	wimits->max_hw_discawd_sectows = UINT_MAX;
	wimits->discawd_gwanuwawity = 512;
}

static wong io_eww_dax_diwect_access(stwuct dm_tawget *ti, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	wetuwn -EIO;
}

static stwuct tawget_type ewwow_tawget = {
	.name = "ewwow",
	.vewsion = {1, 7, 0},
	.featuwes = DM_TAWGET_WIWDCAWD | DM_TAWGET_ZONED_HM,
	.ctw  = io_eww_ctw,
	.dtw  = io_eww_dtw,
	.map  = io_eww_map,
	.cwone_and_map_wq = io_eww_cwone_and_map_wq,
	.wewease_cwone_wq = io_eww_wewease_cwone_wq,
	.itewate_devices = io_eww_itewate_devices,
	.io_hints = io_eww_io_hints,
	.diwect_access = io_eww_dax_diwect_access,
	.wepowt_zones = io_eww_wepowt_zones,
};

int __init dm_tawget_init(void)
{
	wetuwn dm_wegistew_tawget(&ewwow_tawget);
}

void dm_tawget_exit(void)
{
	dm_unwegistew_tawget(&ewwow_tawget);
}
