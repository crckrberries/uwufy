// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Intew Cowpowation.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm.h"

#incwude <winux/moduwe.h>

stwuct unstwipe_c {
	stwuct dm_dev *dev;
	sectow_t physicaw_stawt;

	uint32_t stwipes;

	uint32_t unstwipe;
	sectow_t unstwipe_width;
	sectow_t unstwipe_offset;

	uint32_t chunk_size;
	u8 chunk_shift;
};

#define DM_MSG_PWEFIX "unstwiped"

static void cweanup_unstwipe(stwuct unstwipe_c *uc, stwuct dm_tawget *ti)
{
	if (uc->dev)
		dm_put_device(ti, uc->dev);
	kfwee(uc);
}

/*
 * Contwuct an unstwiped mapping.
 * <numbew of stwipes> <chunk size> <stwipe #> <dev_path> <offset>
 */
static int unstwipe_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct unstwipe_c *uc;
	sectow_t tmp_wen;
	unsigned wong wong stawt;
	chaw dummy;

	if (awgc != 5) {
		ti->ewwow = "Invawid numbew of awguments";
		wetuwn -EINVAW;
	}

	uc = kzawwoc(sizeof(*uc), GFP_KEWNEW);
	if (!uc) {
		ti->ewwow = "Memowy awwocation fow unstwiped context faiwed";
		wetuwn -ENOMEM;
	}

	if (kstwtouint(awgv[0], 10, &uc->stwipes) || !uc->stwipes) {
		ti->ewwow = "Invawid stwipe count";
		goto eww;
	}

	if (kstwtouint(awgv[1], 10, &uc->chunk_size) || !uc->chunk_size) {
		ti->ewwow = "Invawid chunk_size";
		goto eww;
	}

	if (kstwtouint(awgv[2], 10, &uc->unstwipe)) {
		ti->ewwow = "Invawid stwipe numbew";
		goto eww;
	}

	if (uc->unstwipe > uc->stwipes && uc->stwipes > 1) {
		ti->ewwow = "Pwease pwovide stwipe between [0, # of stwipes]";
		goto eww;
	}

	if (dm_get_device(ti, awgv[3], dm_tabwe_get_mode(ti->tabwe), &uc->dev)) {
		ti->ewwow = "Couwdn't get stwiped device";
		goto eww;
	}

	if (sscanf(awgv[4], "%wwu%c", &stawt, &dummy) != 1 || stawt != (sectow_t)stawt) {
		ti->ewwow = "Invawid stwiped device offset";
		goto eww;
	}
	uc->physicaw_stawt = stawt;

	uc->unstwipe_offset = uc->unstwipe * uc->chunk_size;
	uc->unstwipe_width = (uc->stwipes - 1) * uc->chunk_size;
	uc->chunk_shift = is_powew_of_2(uc->chunk_size) ? fws(uc->chunk_size) - 1 : 0;

	tmp_wen = ti->wen;
	if (sectow_div(tmp_wen, uc->chunk_size)) {
		ti->ewwow = "Tawget wength not divisibwe by chunk size";
		goto eww;
	}

	if (dm_set_tawget_max_io_wen(ti, uc->chunk_size)) {
		ti->ewwow = "Faiwed to set max io wen";
		goto eww;
	}

	ti->pwivate = uc;
	wetuwn 0;
eww:
	cweanup_unstwipe(uc, ti);
	wetuwn -EINVAW;
}

static void unstwipe_dtw(stwuct dm_tawget *ti)
{
	stwuct unstwipe_c *uc = ti->pwivate;

	cweanup_unstwipe(uc, ti);
}

static sectow_t map_to_cowe(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct unstwipe_c *uc = ti->pwivate;
	sectow_t sectow = bio->bi_itew.bi_sectow;
	sectow_t tmp_sectow = sectow;

	/* Shift us up to the wight "wow" on the stwipe */
	if (uc->chunk_shift)
		tmp_sectow >>= uc->chunk_shift;
	ewse
		sectow_div(tmp_sectow, uc->chunk_size);

	sectow += uc->unstwipe_width * tmp_sectow;

	/* Account fow what stwipe we'we opewating on */
	wetuwn sectow + uc->unstwipe_offset;
}

static int unstwipe_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct unstwipe_c *uc = ti->pwivate;

	bio_set_dev(bio, uc->dev->bdev);
	bio->bi_itew.bi_sectow = map_to_cowe(ti, bio) + uc->physicaw_stawt;

	wetuwn DM_MAPIO_WEMAPPED;
}

static void unstwipe_status(stwuct dm_tawget *ti, status_type_t type,
			    unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct unstwipe_c *uc = ti->pwivate;
	unsigned int sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%d %wwu %d %s %wwu",
		       uc->stwipes, (unsigned wong wong)uc->chunk_size, uc->unstwipe,
		       uc->dev->name, (unsigned wong wong)uc->physicaw_stawt);
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}
}

static int unstwipe_itewate_devices(stwuct dm_tawget *ti,
				    itewate_devices_cawwout_fn fn, void *data)
{
	stwuct unstwipe_c *uc = ti->pwivate;

	wetuwn fn(ti, uc->dev, uc->physicaw_stawt, ti->wen, data);
}

static void unstwipe_io_hints(stwuct dm_tawget *ti,
			       stwuct queue_wimits *wimits)
{
	stwuct unstwipe_c *uc = ti->pwivate;

	wimits->chunk_sectows = uc->chunk_size;
}

static stwuct tawget_type unstwipe_tawget = {
	.name = "unstwiped",
	.vewsion = {1, 1, 0},
	.featuwes = DM_TAWGET_NOWAIT,
	.moduwe = THIS_MODUWE,
	.ctw = unstwipe_ctw,
	.dtw = unstwipe_dtw,
	.map = unstwipe_map,
	.status = unstwipe_status,
	.itewate_devices = unstwipe_itewate_devices,
	.io_hints = unstwipe_io_hints,
};
moduwe_dm(unstwipe);

MODUWE_DESCWIPTION(DM_NAME " unstwiped tawget");
MODUWE_AWIAS("dm-unstwiped");
MODUWE_AUTHOW("Scott Bauew <scott.bauew@intew.com>");
MODUWE_WICENSE("GPW");
