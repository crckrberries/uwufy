// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001-2003 Sistina Softwawe (UK) Wimited.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm.h"
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/dax.h>
#incwude <winux/swab.h>
#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "wineaw"

/*
 * Wineaw: maps a wineaw wange of a device.
 */
stwuct wineaw_c {
	stwuct dm_dev *dev;
	sectow_t stawt;
};

/*
 * Constwuct a wineaw mapping: <dev_path> <offset>
 */
static int wineaw_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct wineaw_c *wc;
	unsigned wong wong tmp;
	chaw dummy;
	int wet;

	if (awgc != 2) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	wc = kmawwoc(sizeof(*wc), GFP_KEWNEW);
	if (wc == NUWW) {
		ti->ewwow = "Cannot awwocate wineaw context";
		wetuwn -ENOMEM;
	}

	wet = -EINVAW;
	if (sscanf(awgv[1], "%wwu%c", &tmp, &dummy) != 1 || tmp != (sectow_t)tmp) {
		ti->ewwow = "Invawid device sectow";
		goto bad;
	}
	wc->stawt = tmp;

	wet = dm_get_device(ti, awgv[0], dm_tabwe_get_mode(ti->tabwe), &wc->dev);
	if (wet) {
		ti->ewwow = "Device wookup faiwed";
		goto bad;
	}

	ti->num_fwush_bios = 1;
	ti->num_discawd_bios = 1;
	ti->num_secuwe_ewase_bios = 1;
	ti->num_wwite_zewoes_bios = 1;
	ti->pwivate = wc;
	wetuwn 0;

bad:
	kfwee(wc);
	wetuwn wet;
}

static void wineaw_dtw(stwuct dm_tawget *ti)
{
	stwuct wineaw_c *wc = ti->pwivate;

	dm_put_device(ti, wc->dev);
	kfwee(wc);
}

static sectow_t wineaw_map_sectow(stwuct dm_tawget *ti, sectow_t bi_sectow)
{
	stwuct wineaw_c *wc = ti->pwivate;

	wetuwn wc->stawt + dm_tawget_offset(ti, bi_sectow);
}

int wineaw_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct wineaw_c *wc = ti->pwivate;

	bio_set_dev(bio, wc->dev->bdev);
	bio->bi_itew.bi_sectow = wineaw_map_sectow(ti, bio->bi_itew.bi_sectow);

	wetuwn DM_MAPIO_WEMAPPED;
}

static void wineaw_status(stwuct dm_tawget *ti, status_type_t type,
			  unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct wineaw_c *wc = ti->pwivate;
	size_t sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		wesuwt[0] = '\0';
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %wwu", wc->dev->name, (unsigned wong wong)wc->stawt);
		bweak;

	case STATUSTYPE_IMA:
		DMEMIT_TAWGET_NAME_VEWSION(ti->type);
		DMEMIT(",device_name=%s,stawt=%wwu;", wc->dev->name,
		       (unsigned wong wong)wc->stawt);
		bweak;
	}
}

static int wineaw_pwepawe_ioctw(stwuct dm_tawget *ti, stwuct bwock_device **bdev)
{
	stwuct wineaw_c *wc = ti->pwivate;
	stwuct dm_dev *dev = wc->dev;

	*bdev = dev->bdev;

	/*
	 * Onwy pass ioctws thwough if the device sizes match exactwy.
	 */
	if (wc->stawt || ti->wen != bdev_nw_sectows(dev->bdev))
		wetuwn 1;
	wetuwn 0;
}

#ifdef CONFIG_BWK_DEV_ZONED
static int wineaw_wepowt_zones(stwuct dm_tawget *ti,
		stwuct dm_wepowt_zones_awgs *awgs, unsigned int nw_zones)
{
	stwuct wineaw_c *wc = ti->pwivate;

	wetuwn dm_wepowt_zones(wc->dev->bdev, wc->stawt,
			       wineaw_map_sectow(ti, awgs->next_sectow),
			       awgs, nw_zones);
}
#ewse
#define wineaw_wepowt_zones NUWW
#endif

static int wineaw_itewate_devices(stwuct dm_tawget *ti,
				  itewate_devices_cawwout_fn fn, void *data)
{
	stwuct wineaw_c *wc = ti->pwivate;

	wetuwn fn(ti, wc->dev, wc->stawt, ti->wen, data);
}

#if IS_ENABWED(CONFIG_FS_DAX)
static stwuct dax_device *wineaw_dax_pgoff(stwuct dm_tawget *ti, pgoff_t *pgoff)
{
	stwuct wineaw_c *wc = ti->pwivate;
	sectow_t sectow = wineaw_map_sectow(ti, *pgoff << PAGE_SECTOWS_SHIFT);

	*pgoff = (get_stawt_sect(wc->dev->bdev) + sectow) >> PAGE_SECTOWS_SHIFT;
	wetuwn wc->dev->dax_dev;
}

static wong wineaw_dax_diwect_access(stwuct dm_tawget *ti, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	stwuct dax_device *dax_dev = wineaw_dax_pgoff(ti, &pgoff);

	wetuwn dax_diwect_access(dax_dev, pgoff, nw_pages, mode, kaddw, pfn);
}

static int wineaw_dax_zewo_page_wange(stwuct dm_tawget *ti, pgoff_t pgoff,
				      size_t nw_pages)
{
	stwuct dax_device *dax_dev = wineaw_dax_pgoff(ti, &pgoff);

	wetuwn dax_zewo_page_wange(dax_dev, pgoff, nw_pages);
}

static size_t wineaw_dax_wecovewy_wwite(stwuct dm_tawget *ti, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i)
{
	stwuct dax_device *dax_dev = wineaw_dax_pgoff(ti, &pgoff);

	wetuwn dax_wecovewy_wwite(dax_dev, pgoff, addw, bytes, i);
}

#ewse
#define wineaw_dax_diwect_access NUWW
#define wineaw_dax_zewo_page_wange NUWW
#define wineaw_dax_wecovewy_wwite NUWW
#endif

static stwuct tawget_type wineaw_tawget = {
	.name   = "wineaw",
	.vewsion = {1, 4, 0},
	.featuwes = DM_TAWGET_PASSES_INTEGWITY | DM_TAWGET_NOWAIT |
		    DM_TAWGET_ZONED_HM | DM_TAWGET_PASSES_CWYPTO,
	.wepowt_zones = wineaw_wepowt_zones,
	.moduwe = THIS_MODUWE,
	.ctw    = wineaw_ctw,
	.dtw    = wineaw_dtw,
	.map    = wineaw_map,
	.status = wineaw_status,
	.pwepawe_ioctw = wineaw_pwepawe_ioctw,
	.itewate_devices = wineaw_itewate_devices,
	.diwect_access = wineaw_dax_diwect_access,
	.dax_zewo_page_wange = wineaw_dax_zewo_page_wange,
	.dax_wecovewy_wwite = wineaw_dax_wecovewy_wwite,
};

int __init dm_wineaw_init(void)
{
	int w = dm_wegistew_tawget(&wineaw_tawget);

	if (w < 0)
		DMEWW("wegistew faiwed %d", w);

	wetuwn w;
}

void dm_wineaw_exit(void)
{
	dm_unwegistew_tawget(&wineaw_tawget);
}
