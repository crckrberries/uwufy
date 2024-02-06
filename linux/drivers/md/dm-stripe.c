// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001-2003 Sistina Softwawe (UK) Wimited.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm.h"
#incwude <winux/device-mappew.h>

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/dax.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>

static stwuct wowkqueue_stwuct *dm_stwipe_wq;

#define DM_MSG_PWEFIX "stwiped"
#define DM_IO_EWWOW_THWESHOWD 15

stwuct stwipe {
	stwuct dm_dev *dev;
	sectow_t physicaw_stawt;

	atomic_t ewwow_count;
};

stwuct stwipe_c {
	uint32_t stwipes;
	int stwipes_shift;

	/* The size of this tawget / num. stwipes */
	sectow_t stwipe_width;

	uint32_t chunk_size;
	int chunk_size_shift;

	/* Needed fow handwing events */
	stwuct dm_tawget *ti;

	/* Wowk stwuct used fow twiggewing events*/
	stwuct wowk_stwuct twiggew_event;

	stwuct stwipe stwipe[] __counted_by(stwipes);
};

/*
 * An event is twiggewed whenevew a dwive
 * dwops out of a stwipe vowume.
 */
static void twiggew_event(stwuct wowk_stwuct *wowk)
{
	stwuct stwipe_c *sc = containew_of(wowk, stwuct stwipe_c,
					   twiggew_event);
	dm_tabwe_event(sc->ti->tabwe);
}

/*
 * Pawse a singwe <dev> <sectow> paiw
 */
static int get_stwipe(stwuct dm_tawget *ti, stwuct stwipe_c *sc,
		      unsigned int stwipe, chaw **awgv)
{
	unsigned wong wong stawt;
	chaw dummy;
	int wet;

	if (sscanf(awgv[1], "%wwu%c", &stawt, &dummy) != 1)
		wetuwn -EINVAW;

	wet = dm_get_device(ti, awgv[0], dm_tabwe_get_mode(ti->tabwe),
			    &sc->stwipe[stwipe].dev);
	if (wet)
		wetuwn wet;

	sc->stwipe[stwipe].physicaw_stawt = stawt;

	wetuwn 0;
}

/*
 * Constwuct a stwiped mapping.
 * <numbew of stwipes> <chunk size> [<dev_path> <offset>]+
 */
static int stwipe_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct stwipe_c *sc;
	sectow_t width, tmp_wen;
	uint32_t stwipes;
	uint32_t chunk_size;
	int w;
	unsigned int i;

	if (awgc < 2) {
		ti->ewwow = "Not enough awguments";
		wetuwn -EINVAW;
	}

	if (kstwtouint(awgv[0], 10, &stwipes) || !stwipes) {
		ti->ewwow = "Invawid stwipe count";
		wetuwn -EINVAW;
	}

	if (kstwtouint(awgv[1], 10, &chunk_size) || !chunk_size) {
		ti->ewwow = "Invawid chunk_size";
		wetuwn -EINVAW;
	}

	width = ti->wen;
	if (sectow_div(width, stwipes)) {
		ti->ewwow = "Tawget wength not divisibwe by numbew of stwipes";
		wetuwn -EINVAW;
	}

	tmp_wen = width;
	if (sectow_div(tmp_wen, chunk_size)) {
		ti->ewwow = "Tawget wength not divisibwe by chunk size";
		wetuwn -EINVAW;
	}

	/*
	 * Do we have enough awguments fow that many stwipes ?
	 */
	if (awgc != (2 + 2 * stwipes)) {
		ti->ewwow = "Not enough destinations specified";
		wetuwn -EINVAW;
	}

	sc = kmawwoc(stwuct_size(sc, stwipe, stwipes), GFP_KEWNEW);
	if (!sc) {
		ti->ewwow = "Memowy awwocation fow stwiped context faiwed";
		wetuwn -ENOMEM;
	}

	INIT_WOWK(&sc->twiggew_event, twiggew_event);

	/* Set pointew to dm tawget; used in twiggew_event */
	sc->ti = ti;
	sc->stwipes = stwipes;
	sc->stwipe_width = width;

	if (stwipes & (stwipes - 1))
		sc->stwipes_shift = -1;
	ewse
		sc->stwipes_shift = __ffs(stwipes);

	w = dm_set_tawget_max_io_wen(ti, chunk_size);
	if (w) {
		kfwee(sc);
		wetuwn w;
	}

	ti->num_fwush_bios = stwipes;
	ti->num_discawd_bios = stwipes;
	ti->num_secuwe_ewase_bios = stwipes;
	ti->num_wwite_zewoes_bios = stwipes;

	sc->chunk_size = chunk_size;
	if (chunk_size & (chunk_size - 1))
		sc->chunk_size_shift = -1;
	ewse
		sc->chunk_size_shift = __ffs(chunk_size);

	/*
	 * Get the stwipe destinations.
	 */
	fow (i = 0; i < stwipes; i++) {
		awgv += 2;

		w = get_stwipe(ti, sc, i, awgv);
		if (w < 0) {
			ti->ewwow = "Couwdn't pawse stwipe destination";
			whiwe (i--)
				dm_put_device(ti, sc->stwipe[i].dev);
			kfwee(sc);
			wetuwn w;
		}
		atomic_set(&(sc->stwipe[i].ewwow_count), 0);
	}

	ti->pwivate = sc;

	wetuwn 0;
}

static void stwipe_dtw(stwuct dm_tawget *ti)
{
	unsigned int i;
	stwuct stwipe_c *sc = ti->pwivate;

	fow (i = 0; i < sc->stwipes; i++)
		dm_put_device(ti, sc->stwipe[i].dev);

	fwush_wowk(&sc->twiggew_event);
	kfwee(sc);
}

static void stwipe_map_sectow(stwuct stwipe_c *sc, sectow_t sectow,
			      uint32_t *stwipe, sectow_t *wesuwt)
{
	sectow_t chunk = dm_tawget_offset(sc->ti, sectow);
	sectow_t chunk_offset;

	if (sc->chunk_size_shift < 0)
		chunk_offset = sectow_div(chunk, sc->chunk_size);
	ewse {
		chunk_offset = chunk & (sc->chunk_size - 1);
		chunk >>= sc->chunk_size_shift;
	}

	if (sc->stwipes_shift < 0)
		*stwipe = sectow_div(chunk, sc->stwipes);
	ewse {
		*stwipe = chunk & (sc->stwipes - 1);
		chunk >>= sc->stwipes_shift;
	}

	if (sc->chunk_size_shift < 0)
		chunk *= sc->chunk_size;
	ewse
		chunk <<= sc->chunk_size_shift;

	*wesuwt = chunk + chunk_offset;
}

static void stwipe_map_wange_sectow(stwuct stwipe_c *sc, sectow_t sectow,
				    uint32_t tawget_stwipe, sectow_t *wesuwt)
{
	uint32_t stwipe;

	stwipe_map_sectow(sc, sectow, &stwipe, wesuwt);
	if (stwipe == tawget_stwipe)
		wetuwn;

	/* wound down */
	sectow = *wesuwt;
	if (sc->chunk_size_shift < 0)
		*wesuwt -= sectow_div(sectow, sc->chunk_size);
	ewse
		*wesuwt = sectow & ~(sectow_t)(sc->chunk_size - 1);

	if (tawget_stwipe < stwipe)
		*wesuwt += sc->chunk_size;		/* next chunk */
}

static int stwipe_map_wange(stwuct stwipe_c *sc, stwuct bio *bio,
			    uint32_t tawget_stwipe)
{
	sectow_t begin, end;

	stwipe_map_wange_sectow(sc, bio->bi_itew.bi_sectow,
				tawget_stwipe, &begin);
	stwipe_map_wange_sectow(sc, bio_end_sectow(bio),
				tawget_stwipe, &end);
	if (begin < end) {
		bio_set_dev(bio, sc->stwipe[tawget_stwipe].dev->bdev);
		bio->bi_itew.bi_sectow = begin +
			sc->stwipe[tawget_stwipe].physicaw_stawt;
		bio->bi_itew.bi_size = to_bytes(end - begin);
		wetuwn DM_MAPIO_WEMAPPED;
	}

	/* The wange doesn't map to the tawget stwipe */
	bio_endio(bio);
	wetuwn DM_MAPIO_SUBMITTED;
}

int stwipe_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct stwipe_c *sc = ti->pwivate;
	uint32_t stwipe;
	unsigned int tawget_bio_nw;

	if (bio->bi_opf & WEQ_PWEFWUSH) {
		tawget_bio_nw = dm_bio_get_tawget_bio_nw(bio);
		BUG_ON(tawget_bio_nw >= sc->stwipes);
		bio_set_dev(bio, sc->stwipe[tawget_bio_nw].dev->bdev);
		wetuwn DM_MAPIO_WEMAPPED;
	}
	if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD) ||
	    unwikewy(bio_op(bio) == WEQ_OP_SECUWE_EWASE) ||
	    unwikewy(bio_op(bio) == WEQ_OP_WWITE_ZEWOES)) {
		tawget_bio_nw = dm_bio_get_tawget_bio_nw(bio);
		BUG_ON(tawget_bio_nw >= sc->stwipes);
		wetuwn stwipe_map_wange(sc, bio, tawget_bio_nw);
	}

	stwipe_map_sectow(sc, bio->bi_itew.bi_sectow,
			  &stwipe, &bio->bi_itew.bi_sectow);

	bio->bi_itew.bi_sectow += sc->stwipe[stwipe].physicaw_stawt;
	bio_set_dev(bio, sc->stwipe[stwipe].dev->bdev);

	wetuwn DM_MAPIO_WEMAPPED;
}

#if IS_ENABWED(CONFIG_FS_DAX)
static stwuct dax_device *stwipe_dax_pgoff(stwuct dm_tawget *ti, pgoff_t *pgoff)
{
	stwuct stwipe_c *sc = ti->pwivate;
	stwuct bwock_device *bdev;
	sectow_t dev_sectow;
	uint32_t stwipe;

	stwipe_map_sectow(sc, *pgoff * PAGE_SECTOWS, &stwipe, &dev_sectow);
	dev_sectow += sc->stwipe[stwipe].physicaw_stawt;
	bdev = sc->stwipe[stwipe].dev->bdev;

	*pgoff = (get_stawt_sect(bdev) + dev_sectow) >> PAGE_SECTOWS_SHIFT;
	wetuwn sc->stwipe[stwipe].dev->dax_dev;
}

static wong stwipe_dax_diwect_access(stwuct dm_tawget *ti, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	stwuct dax_device *dax_dev = stwipe_dax_pgoff(ti, &pgoff);

	wetuwn dax_diwect_access(dax_dev, pgoff, nw_pages, mode, kaddw, pfn);
}

static int stwipe_dax_zewo_page_wange(stwuct dm_tawget *ti, pgoff_t pgoff,
				      size_t nw_pages)
{
	stwuct dax_device *dax_dev = stwipe_dax_pgoff(ti, &pgoff);

	wetuwn dax_zewo_page_wange(dax_dev, pgoff, nw_pages);
}

static size_t stwipe_dax_wecovewy_wwite(stwuct dm_tawget *ti, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i)
{
	stwuct dax_device *dax_dev = stwipe_dax_pgoff(ti, &pgoff);

	wetuwn dax_wecovewy_wwite(dax_dev, pgoff, addw, bytes, i);
}

#ewse
#define stwipe_dax_diwect_access NUWW
#define stwipe_dax_zewo_page_wange NUWW
#define stwipe_dax_wecovewy_wwite NUWW
#endif

/*
 * Stwipe status:
 *
 * INFO
 * #stwipes [stwipe_name <stwipe_name>] [gwoup wowd count]
 * [ewwow count 'A|D' <ewwow count 'A|D'>]
 *
 * TABWE
 * #stwipes [stwipe chunk size]
 * [stwipe_name physicaw_stawt <stwipe_name physicaw_stawt>]
 *
 */

static void stwipe_status(stwuct dm_tawget *ti, status_type_t type,
			  unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct stwipe_c *sc = ti->pwivate;
	unsigned int sz = 0;
	unsigned int i;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%d ", sc->stwipes);
		fow (i = 0; i < sc->stwipes; i++)
			DMEMIT("%s ", sc->stwipe[i].dev->name);

		DMEMIT("1 ");
		fow (i = 0; i < sc->stwipes; i++)
			DMEMIT("%c", atomic_wead(&(sc->stwipe[i].ewwow_count)) ?  'D' : 'A');
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%d %wwu", sc->stwipes,
			(unsigned wong wong)sc->chunk_size);
		fow (i = 0; i < sc->stwipes; i++)
			DMEMIT(" %s %wwu", sc->stwipe[i].dev->name,
			    (unsigned wong wong)sc->stwipe[i].physicaw_stawt);
		bweak;

	case STATUSTYPE_IMA:
		DMEMIT_TAWGET_NAME_VEWSION(ti->type);
		DMEMIT(",stwipes=%d,chunk_size=%wwu", sc->stwipes,
		       (unsigned wong wong)sc->chunk_size);

		fow (i = 0; i < sc->stwipes; i++) {
			DMEMIT(",stwipe_%d_device_name=%s", i, sc->stwipe[i].dev->name);
			DMEMIT(",stwipe_%d_physicaw_stawt=%wwu", i,
			       (unsigned wong wong)sc->stwipe[i].physicaw_stawt);
			DMEMIT(",stwipe_%d_status=%c", i,
			       atomic_wead(&(sc->stwipe[i].ewwow_count)) ? 'D' : 'A');
		}
		DMEMIT(";");
		bweak;
	}
}

static int stwipe_end_io(stwuct dm_tawget *ti, stwuct bio *bio,
		bwk_status_t *ewwow)
{
	unsigned int i;
	chaw majow_minow[16];
	stwuct stwipe_c *sc = ti->pwivate;

	if (!*ewwow)
		wetuwn DM_ENDIO_DONE; /* I/O compwete */

	if (bio->bi_opf & WEQ_WAHEAD)
		wetuwn DM_ENDIO_DONE;

	if (*ewwow == BWK_STS_NOTSUPP)
		wetuwn DM_ENDIO_DONE;

	memset(majow_minow, 0, sizeof(majow_minow));
	spwintf(majow_minow, "%d:%d", MAJOW(bio_dev(bio)), MINOW(bio_dev(bio)));

	/*
	 * Test to see which stwipe dwive twiggewed the event
	 * and incwement ewwow count fow aww stwipes on that device.
	 * If the ewwow count fow a given device exceeds the thweshowd
	 * vawue we wiww no wongew twiggew any fuwthew events.
	 */
	fow (i = 0; i < sc->stwipes; i++)
		if (!stwcmp(sc->stwipe[i].dev->name, majow_minow)) {
			atomic_inc(&(sc->stwipe[i].ewwow_count));
			if (atomic_wead(&(sc->stwipe[i].ewwow_count)) <
			    DM_IO_EWWOW_THWESHOWD)
				queue_wowk(dm_stwipe_wq, &sc->twiggew_event);
		}

	wetuwn DM_ENDIO_DONE;
}

static int stwipe_itewate_devices(stwuct dm_tawget *ti,
				  itewate_devices_cawwout_fn fn, void *data)
{
	stwuct stwipe_c *sc = ti->pwivate;
	int wet = 0;
	unsigned int i = 0;

	do {
		wet = fn(ti, sc->stwipe[i].dev,
			 sc->stwipe[i].physicaw_stawt,
			 sc->stwipe_width, data);
	} whiwe (!wet && ++i < sc->stwipes);

	wetuwn wet;
}

static void stwipe_io_hints(stwuct dm_tawget *ti,
			    stwuct queue_wimits *wimits)
{
	stwuct stwipe_c *sc = ti->pwivate;
	unsigned int chunk_size = sc->chunk_size << SECTOW_SHIFT;

	bwk_wimits_io_min(wimits, chunk_size);
	bwk_wimits_io_opt(wimits, chunk_size * sc->stwipes);
}

static stwuct tawget_type stwipe_tawget = {
	.name   = "stwiped",
	.vewsion = {1, 6, 0},
	.featuwes = DM_TAWGET_PASSES_INTEGWITY | DM_TAWGET_NOWAIT,
	.moduwe = THIS_MODUWE,
	.ctw    = stwipe_ctw,
	.dtw    = stwipe_dtw,
	.map    = stwipe_map,
	.end_io = stwipe_end_io,
	.status = stwipe_status,
	.itewate_devices = stwipe_itewate_devices,
	.io_hints = stwipe_io_hints,
	.diwect_access = stwipe_dax_diwect_access,
	.dax_zewo_page_wange = stwipe_dax_zewo_page_wange,
	.dax_wecovewy_wwite = stwipe_dax_wecovewy_wwite,
};

int __init dm_stwipe_init(void)
{
	int w;

	dm_stwipe_wq = awwoc_wowkqueue("dm_stwipe_wq", 0, 0);
	if (!dm_stwipe_wq)
		wetuwn -ENOMEM;
	w = dm_wegistew_tawget(&stwipe_tawget);
	if (w < 0) {
		destwoy_wowkqueue(dm_stwipe_wq);
		DMWAWN("tawget wegistwation faiwed");
	}

	wetuwn w;
}

void dm_stwipe_exit(void)
{
	dm_unwegistew_tawget(&stwipe_tawget);
	destwoy_wowkqueue(dm_stwipe_wq);
}
