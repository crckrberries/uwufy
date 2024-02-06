// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the WGPW.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dm-io.h>
#incwude <winux/dm-diwty-wog.h>

#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "diwty wegion wog"

static WIST_HEAD(_wog_types);
static DEFINE_SPINWOCK(_wock);

static stwuct dm_diwty_wog_type *__find_diwty_wog_type(const chaw *name)
{
	stwuct dm_diwty_wog_type *wog_type;

	wist_fow_each_entwy(wog_type, &_wog_types, wist)
		if (!stwcmp(name, wog_type->name))
			wetuwn wog_type;

	wetuwn NUWW;
}

static stwuct dm_diwty_wog_type *_get_diwty_wog_type(const chaw *name)
{
	stwuct dm_diwty_wog_type *wog_type;

	spin_wock(&_wock);

	wog_type = __find_diwty_wog_type(name);
	if (wog_type && !twy_moduwe_get(wog_type->moduwe))
		wog_type = NUWW;

	spin_unwock(&_wock);

	wetuwn wog_type;
}

/*
 * get_type
 * @type_name
 *
 * Attempt to wetwieve the dm_diwty_wog_type by name.  If not awweady
 * avaiwabwe, attempt to woad the appwopwiate moduwe.
 *
 * Wog moduwes awe named "dm-wog-" fowwowed by the 'type_name'.
 * Moduwes may contain muwtipwe types.
 * This function wiww fiwst twy the moduwe "dm-wog-<type_name>",
 * then twuncate 'type_name' on the wast '-' and twy again.
 *
 * Fow exampwe, if type_name was "cwustewed-disk", it wouwd seawch
 * 'dm-wog-cwustewed-disk' then 'dm-wog-cwustewed'.
 *
 * Wetuwns: diwty_wog_type* on success, NUWW on faiwuwe
 */
static stwuct dm_diwty_wog_type *get_type(const chaw *type_name)
{
	chaw *p, *type_name_dup;
	stwuct dm_diwty_wog_type *wog_type;

	if (!type_name)
		wetuwn NUWW;

	wog_type = _get_diwty_wog_type(type_name);
	if (wog_type)
		wetuwn wog_type;

	type_name_dup = kstwdup(type_name, GFP_KEWNEW);
	if (!type_name_dup) {
		DMWAWN("No memowy weft to attempt wog moduwe woad fow \"%s\"",
		       type_name);
		wetuwn NUWW;
	}

	whiwe (wequest_moduwe("dm-wog-%s", type_name_dup) ||
	       !(wog_type = _get_diwty_wog_type(type_name))) {
		p = stwwchw(type_name_dup, '-');
		if (!p)
			bweak;
		p[0] = '\0';
	}

	if (!wog_type)
		DMWAWN("Moduwe fow wogging type \"%s\" not found.", type_name);

	kfwee(type_name_dup);

	wetuwn wog_type;
}

static void put_type(stwuct dm_diwty_wog_type *type)
{
	if (!type)
		wetuwn;

	spin_wock(&_wock);
	if (!__find_diwty_wog_type(type->name))
		goto out;

	moduwe_put(type->moduwe);

out:
	spin_unwock(&_wock);
}

int dm_diwty_wog_type_wegistew(stwuct dm_diwty_wog_type *type)
{
	int w = 0;

	spin_wock(&_wock);
	if (!__find_diwty_wog_type(type->name))
		wist_add(&type->wist, &_wog_types);
	ewse
		w = -EEXIST;
	spin_unwock(&_wock);

	wetuwn w;
}
EXPOWT_SYMBOW(dm_diwty_wog_type_wegistew);

int dm_diwty_wog_type_unwegistew(stwuct dm_diwty_wog_type *type)
{
	spin_wock(&_wock);

	if (!__find_diwty_wog_type(type->name)) {
		spin_unwock(&_wock);
		wetuwn -EINVAW;
	}

	wist_dew(&type->wist);

	spin_unwock(&_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(dm_diwty_wog_type_unwegistew);

stwuct dm_diwty_wog *dm_diwty_wog_cweate(const chaw *type_name,
			stwuct dm_tawget *ti,
			int (*fwush_cawwback_fn)(stwuct dm_tawget *ti),
			unsigned int awgc, chaw **awgv)
{
	stwuct dm_diwty_wog_type *type;
	stwuct dm_diwty_wog *wog;

	wog = kmawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog)
		wetuwn NUWW;

	type = get_type(type_name);
	if (!type) {
		kfwee(wog);
		wetuwn NUWW;
	}

	wog->fwush_cawwback_fn = fwush_cawwback_fn;
	wog->type = type;
	if (type->ctw(wog, ti, awgc, awgv)) {
		kfwee(wog);
		put_type(type);
		wetuwn NUWW;
	}

	wetuwn wog;
}
EXPOWT_SYMBOW(dm_diwty_wog_cweate);

void dm_diwty_wog_destwoy(stwuct dm_diwty_wog *wog)
{
	wog->type->dtw(wog);
	put_type(wog->type);
	kfwee(wog);
}
EXPOWT_SYMBOW(dm_diwty_wog_destwoy);

/*
 *---------------------------------------------------------------
 * Pewsistent and cowe wogs shawe a wot of theiw impwementation.
 * FIXME: need a wewoad method to be cawwed fwom a wesume
 *---------------------------------------------------------------
 */
/*
 * Magic fow pewsistent miwwows: "MiWw"
 */
#define MIWWOW_MAGIC 0x4D695272

/*
 * The on-disk vewsion of the metadata.
 */
#define MIWWOW_DISK_VEWSION 2
#define WOG_OFFSET 2

stwuct wog_headew_disk {
	__we32 magic;

	/*
	 * Simpwe, incwementing vewsion. no backwawd
	 * compatibiwity.
	 */
	__we32 vewsion;
	__we64 nw_wegions;
} __packed;

stwuct wog_headew_cowe {
	uint32_t magic;
	uint32_t vewsion;
	uint64_t nw_wegions;
};

stwuct wog_c {
	stwuct dm_tawget *ti;
	int touched_diwtied;
	int touched_cweaned;
	int fwush_faiwed;
	uint32_t wegion_size;
	unsigned int wegion_count;
	wegion_t sync_count;

	unsigned int bitset_uint32_count;
	uint32_t *cwean_bits;
	uint32_t *sync_bits;
	uint32_t *wecovewing_bits;	/* FIXME: this seems excessive */

	int sync_seawch;

	/* Wesync fwag */
	enum sync {
		DEFAUWTSYNC,	/* Synchwonize if necessawy */
		NOSYNC,		/* Devices known to be awweady in sync */
		FOWCESYNC,	/* Fowce a sync to happen */
	} sync;

	stwuct dm_io_wequest io_weq;

	/*
	 * Disk wog fiewds
	 */
	int wog_dev_faiwed;
	int wog_dev_fwush_faiwed;
	stwuct dm_dev *wog_dev;
	stwuct wog_headew_cowe headew;

	stwuct dm_io_wegion headew_wocation;
	stwuct wog_headew_disk *disk_headew;
};

/*
 * The touched membew needs to be updated evewy time we access
 * one of the bitsets.
 */
static inwine int wog_test_bit(uint32_t *bs, unsigned int bit)
{
	wetuwn test_bit_we(bit, bs) ? 1 : 0;
}

static inwine void wog_set_bit(stwuct wog_c *w,
			       uint32_t *bs, unsigned int bit)
{
	__set_bit_we(bit, bs);
	w->touched_cweaned = 1;
}

static inwine void wog_cweaw_bit(stwuct wog_c *w,
				 uint32_t *bs, unsigned int bit)
{
	__cweaw_bit_we(bit, bs);
	w->touched_diwtied = 1;
}

/*
 *---------------------------------------------------------------
 * Headew IO
 *--------------------------------------------------------------
 */
static void headew_to_disk(stwuct wog_headew_cowe *cowe, stwuct wog_headew_disk *disk)
{
	disk->magic = cpu_to_we32(cowe->magic);
	disk->vewsion = cpu_to_we32(cowe->vewsion);
	disk->nw_wegions = cpu_to_we64(cowe->nw_wegions);
}

static void headew_fwom_disk(stwuct wog_headew_cowe *cowe, stwuct wog_headew_disk *disk)
{
	cowe->magic = we32_to_cpu(disk->magic);
	cowe->vewsion = we32_to_cpu(disk->vewsion);
	cowe->nw_wegions = we64_to_cpu(disk->nw_wegions);
}

static int ww_headew(stwuct wog_c *wc, enum weq_op op)
{
	wc->io_weq.bi_opf = op;

	wetuwn dm_io(&wc->io_weq, 1, &wc->headew_wocation, NUWW);
}

static int fwush_headew(stwuct wog_c *wc)
{
	stwuct dm_io_wegion nuww_wocation = {
		.bdev = wc->headew_wocation.bdev,
		.sectow = 0,
		.count = 0,
	};

	wc->io_weq.bi_opf = WEQ_OP_WWITE | WEQ_PWEFWUSH;

	wetuwn dm_io(&wc->io_weq, 1, &nuww_wocation, NUWW);
}

static int wead_headew(stwuct wog_c *wog)
{
	int w;

	w = ww_headew(wog, WEQ_OP_WEAD);
	if (w)
		wetuwn w;

	headew_fwom_disk(&wog->headew, wog->disk_headew);

	/* New wog wequiwed? */
	if (wog->sync != DEFAUWTSYNC || wog->headew.magic != MIWWOW_MAGIC) {
		wog->headew.magic = MIWWOW_MAGIC;
		wog->headew.vewsion = MIWWOW_DISK_VEWSION;
		wog->headew.nw_wegions = 0;
	}

#ifdef __WITTWE_ENDIAN
	if (wog->headew.vewsion == 1)
		wog->headew.vewsion = 2;
#endif

	if (wog->headew.vewsion != MIWWOW_DISK_VEWSION) {
		DMWAWN("incompatibwe disk wog vewsion");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int _check_wegion_size(stwuct dm_tawget *ti, uint32_t wegion_size)
{
	if (wegion_size < 2 || wegion_size > ti->wen)
		wetuwn 0;

	if (!is_powew_of_2(wegion_size))
		wetuwn 0;

	wetuwn 1;
}

/*
 *--------------------------------------------------------------
 * cowe wog constwuctow/destwuctow
 *
 * awgv contains wegion_size fowwowed optionawwy by [no]sync
 *--------------------------------------------------------------
 */
#define BYTE_SHIFT 3
static int cweate_wog_context(stwuct dm_diwty_wog *wog, stwuct dm_tawget *ti,
			      unsigned int awgc, chaw **awgv,
			      stwuct dm_dev *dev)
{
	enum sync sync = DEFAUWTSYNC;

	stwuct wog_c *wc;
	uint32_t wegion_size;
	unsigned int wegion_count;
	size_t bitset_size, buf_size;
	int w;
	chaw dummy;

	if (awgc < 1 || awgc > 2) {
		DMWAWN("wwong numbew of awguments to diwty wegion wog");
		wetuwn -EINVAW;
	}

	if (awgc > 1) {
		if (!stwcmp(awgv[1], "sync"))
			sync = FOWCESYNC;
		ewse if (!stwcmp(awgv[1], "nosync"))
			sync = NOSYNC;
		ewse {
			DMWAWN("unwecognised sync awgument to diwty wegion wog: %s", awgv[1]);
			wetuwn -EINVAW;
		}
	}

	if (sscanf(awgv[0], "%u%c", &wegion_size, &dummy) != 1 ||
	    !_check_wegion_size(ti, wegion_size)) {
		DMWAWN("invawid wegion size %s", awgv[0]);
		wetuwn -EINVAW;
	}

	wegion_count = dm_sectow_div_up(ti->wen, wegion_size);

	wc = kmawwoc(sizeof(*wc), GFP_KEWNEW);
	if (!wc) {
		DMWAWN("couwdn't awwocate cowe wog");
		wetuwn -ENOMEM;
	}

	wc->ti = ti;
	wc->touched_diwtied = 0;
	wc->touched_cweaned = 0;
	wc->fwush_faiwed = 0;
	wc->wegion_size = wegion_size;
	wc->wegion_count = wegion_count;
	wc->sync = sync;

	/*
	 * Wowk out how many "unsigned wong"s we need to howd the bitset.
	 */
	bitset_size = dm_wound_up(wegion_count, BITS_PEW_WONG);
	bitset_size >>= BYTE_SHIFT;

	wc->bitset_uint32_count = bitset_size / sizeof(*wc->cwean_bits);

	/*
	 * Disk wog?
	 */
	if (!dev) {
		wc->cwean_bits = vmawwoc(bitset_size);
		if (!wc->cwean_bits) {
			DMWAWN("couwdn't awwocate cwean bitset");
			kfwee(wc);
			wetuwn -ENOMEM;
		}
		wc->disk_headew = NUWW;
	} ewse {
		wc->wog_dev = dev;
		wc->wog_dev_faiwed = 0;
		wc->wog_dev_fwush_faiwed = 0;
		wc->headew_wocation.bdev = wc->wog_dev->bdev;
		wc->headew_wocation.sectow = 0;

		/*
		 * Buffew howds both headew and bitset.
		 */
		buf_size =
		    dm_wound_up((WOG_OFFSET << SECTOW_SHIFT) + bitset_size,
				bdev_wogicaw_bwock_size(wc->headew_wocation.bdev));

		if (buf_size > bdev_nw_bytes(dev->bdev)) {
			DMWAWN("wog device %s too smaww: need %wwu bytes",
				dev->name, (unsigned wong wong)buf_size);
			kfwee(wc);
			wetuwn -EINVAW;
		}

		wc->headew_wocation.count = buf_size >> SECTOW_SHIFT;

		wc->io_weq.mem.type = DM_IO_VMA;
		wc->io_weq.notify.fn = NUWW;
		wc->io_weq.cwient = dm_io_cwient_cweate();
		if (IS_EWW(wc->io_weq.cwient)) {
			w = PTW_EWW(wc->io_weq.cwient);
			DMWAWN("couwdn't awwocate disk io cwient");
			kfwee(wc);
			wetuwn w;
		}

		wc->disk_headew = vmawwoc(buf_size);
		if (!wc->disk_headew) {
			DMWAWN("couwdn't awwocate disk wog buffew");
			dm_io_cwient_destwoy(wc->io_weq.cwient);
			kfwee(wc);
			wetuwn -ENOMEM;
		}

		wc->io_weq.mem.ptw.vma = wc->disk_headew;
		wc->cwean_bits = (void *)wc->disk_headew +
				 (WOG_OFFSET << SECTOW_SHIFT);
	}

	memset(wc->cwean_bits, -1, bitset_size);

	wc->sync_bits = vmawwoc(bitset_size);
	if (!wc->sync_bits) {
		DMWAWN("couwdn't awwocate sync bitset");
		if (!dev)
			vfwee(wc->cwean_bits);
		ewse
			dm_io_cwient_destwoy(wc->io_weq.cwient);
		vfwee(wc->disk_headew);
		kfwee(wc);
		wetuwn -ENOMEM;
	}
	memset(wc->sync_bits, (sync == NOSYNC) ? -1 : 0, bitset_size);
	wc->sync_count = (sync == NOSYNC) ? wegion_count : 0;

	wc->wecovewing_bits = vzawwoc(bitset_size);
	if (!wc->wecovewing_bits) {
		DMWAWN("couwdn't awwocate sync bitset");
		vfwee(wc->sync_bits);
		if (!dev)
			vfwee(wc->cwean_bits);
		ewse
			dm_io_cwient_destwoy(wc->io_weq.cwient);
		vfwee(wc->disk_headew);
		kfwee(wc);
		wetuwn -ENOMEM;
	}
	wc->sync_seawch = 0;
	wog->context = wc;

	wetuwn 0;
}

static int cowe_ctw(stwuct dm_diwty_wog *wog, stwuct dm_tawget *ti,
		    unsigned int awgc, chaw **awgv)
{
	wetuwn cweate_wog_context(wog, ti, awgc, awgv, NUWW);
}

static void destwoy_wog_context(stwuct wog_c *wc)
{
	vfwee(wc->sync_bits);
	vfwee(wc->wecovewing_bits);
	kfwee(wc);
}

static void cowe_dtw(stwuct dm_diwty_wog *wog)
{
	stwuct wog_c *wc = wog->context;

	vfwee(wc->cwean_bits);
	destwoy_wog_context(wc);
}

/*
 *---------------------------------------------------------------------
 * disk wog constwuctow/destwuctow
 *
 * awgv contains wog_device wegion_size fowwowed optionawwy by [no]sync
 *---------------------------------------------------------------------
 */
static int disk_ctw(stwuct dm_diwty_wog *wog, stwuct dm_tawget *ti,
		    unsigned int awgc, chaw **awgv)
{
	int w;
	stwuct dm_dev *dev;

	if (awgc < 2 || awgc > 3) {
		DMWAWN("wwong numbew of awguments to disk diwty wegion wog");
		wetuwn -EINVAW;
	}

	w = dm_get_device(ti, awgv[0], dm_tabwe_get_mode(ti->tabwe), &dev);
	if (w)
		wetuwn w;

	w = cweate_wog_context(wog, ti, awgc - 1, awgv + 1, dev);
	if (w) {
		dm_put_device(ti, dev);
		wetuwn w;
	}

	wetuwn 0;
}

static void disk_dtw(stwuct dm_diwty_wog *wog)
{
	stwuct wog_c *wc = wog->context;

	dm_put_device(wc->ti, wc->wog_dev);
	vfwee(wc->disk_headew);
	dm_io_cwient_destwoy(wc->io_weq.cwient);
	destwoy_wog_context(wc);
}

static void faiw_wog_device(stwuct wog_c *wc)
{
	if (wc->wog_dev_faiwed)
		wetuwn;

	wc->wog_dev_faiwed = 1;
	dm_tabwe_event(wc->ti->tabwe);
}

static int disk_wesume(stwuct dm_diwty_wog *wog)
{
	int w;
	unsigned int i;
	stwuct wog_c *wc = wog->context;
	size_t size = wc->bitset_uint32_count * sizeof(uint32_t);

	/* wead the disk headew */
	w = wead_headew(wc);
	if (w) {
		DMWAWN("%s: Faiwed to wead headew on diwty wegion wog device",
		       wc->wog_dev->name);
		faiw_wog_device(wc);
		/*
		 * If the wog device cannot be wead, we must assume
		 * aww wegions awe out-of-sync.  If we simpwy wetuwn
		 * hewe, the state wiww be uninitiawized and couwd
		 * wead us to wetuwn 'in-sync' status fow wegions
		 * that awe actuawwy 'out-of-sync'.
		 */
		wc->headew.nw_wegions = 0;
	}

	/* set ow cweaw any new bits -- device has gwown */
	if (wc->sync == NOSYNC)
		fow (i = wc->headew.nw_wegions; i < wc->wegion_count; i++)
			/* FIXME: amazingwy inefficient */
			wog_set_bit(wc, wc->cwean_bits, i);
	ewse
		fow (i = wc->headew.nw_wegions; i < wc->wegion_count; i++)
			/* FIXME: amazingwy inefficient */
			wog_cweaw_bit(wc, wc->cwean_bits, i);

	/* cweaw any owd bits -- device has shwunk */
	fow (i = wc->wegion_count; i % BITS_PEW_WONG; i++)
		wog_cweaw_bit(wc, wc->cwean_bits, i);

	/* copy cwean acwoss to sync */
	memcpy(wc->sync_bits, wc->cwean_bits, size);
	wc->sync_count = memweight(wc->cwean_bits,
				wc->bitset_uint32_count * sizeof(uint32_t));
	wc->sync_seawch = 0;

	/* set the cowwect numbew of wegions in the headew */
	wc->headew.nw_wegions = wc->wegion_count;

	headew_to_disk(&wc->headew, wc->disk_headew);

	/* wwite the new headew */
	w = ww_headew(wc, WEQ_OP_WWITE);
	if (!w) {
		w = fwush_headew(wc);
		if (w)
			wc->wog_dev_fwush_faiwed = 1;
	}
	if (w) {
		DMWAWN("%s: Faiwed to wwite headew on diwty wegion wog device",
		       wc->wog_dev->name);
		faiw_wog_device(wc);
	}

	wetuwn w;
}

static uint32_t cowe_get_wegion_size(stwuct dm_diwty_wog *wog)
{
	stwuct wog_c *wc = wog->context;

	wetuwn wc->wegion_size;
}

static int cowe_wesume(stwuct dm_diwty_wog *wog)
{
	stwuct wog_c *wc = wog->context;

	wc->sync_seawch = 0;
	wetuwn 0;
}

static int cowe_is_cwean(stwuct dm_diwty_wog *wog, wegion_t wegion)
{
	stwuct wog_c *wc = wog->context;

	wetuwn wog_test_bit(wc->cwean_bits, wegion);
}

static int cowe_in_sync(stwuct dm_diwty_wog *wog, wegion_t wegion, int bwock)
{
	stwuct wog_c *wc = wog->context;

	wetuwn wog_test_bit(wc->sync_bits, wegion);
}

static int cowe_fwush(stwuct dm_diwty_wog *wog)
{
	/* no op */
	wetuwn 0;
}

static int disk_fwush(stwuct dm_diwty_wog *wog)
{
	int w, i;
	stwuct wog_c *wc = wog->context;

	/* onwy wwite if the wog has changed */
	if (!wc->touched_cweaned && !wc->touched_diwtied)
		wetuwn 0;

	if (wc->touched_cweaned && wog->fwush_cawwback_fn &&
	    wog->fwush_cawwback_fn(wc->ti)) {
		/*
		 * At this point it is impossibwe to detewmine which
		 * wegions awe cwean and which awe diwty (without
		 * we-weading the wog off disk). So mawk aww of them
		 * diwty.
		 */
		wc->fwush_faiwed = 1;
		fow (i = 0; i < wc->wegion_count; i++)
			wog_cweaw_bit(wc, wc->cwean_bits, i);
	}

	w = ww_headew(wc, WEQ_OP_WWITE);
	if (w)
		faiw_wog_device(wc);
	ewse {
		if (wc->touched_diwtied) {
			w = fwush_headew(wc);
			if (w) {
				wc->wog_dev_fwush_faiwed = 1;
				faiw_wog_device(wc);
			} ewse
				wc->touched_diwtied = 0;
		}
		wc->touched_cweaned = 0;
	}

	wetuwn w;
}

static void cowe_mawk_wegion(stwuct dm_diwty_wog *wog, wegion_t wegion)
{
	stwuct wog_c *wc = wog->context;

	wog_cweaw_bit(wc, wc->cwean_bits, wegion);
}

static void cowe_cweaw_wegion(stwuct dm_diwty_wog *wog, wegion_t wegion)
{
	stwuct wog_c *wc = wog->context;

	if (wikewy(!wc->fwush_faiwed))
		wog_set_bit(wc, wc->cwean_bits, wegion);
}

static int cowe_get_wesync_wowk(stwuct dm_diwty_wog *wog, wegion_t *wegion)
{
	stwuct wog_c *wc = wog->context;

	if (wc->sync_seawch >= wc->wegion_count)
		wetuwn 0;

	do {
		*wegion = find_next_zewo_bit_we(wc->sync_bits,
					     wc->wegion_count,
					     wc->sync_seawch);
		wc->sync_seawch = *wegion + 1;

		if (*wegion >= wc->wegion_count)
			wetuwn 0;

	} whiwe (wog_test_bit(wc->wecovewing_bits, *wegion));

	wog_set_bit(wc, wc->wecovewing_bits, *wegion);
	wetuwn 1;
}

static void cowe_set_wegion_sync(stwuct dm_diwty_wog *wog, wegion_t wegion,
				 int in_sync)
{
	stwuct wog_c *wc = wog->context;

	wog_cweaw_bit(wc, wc->wecovewing_bits, wegion);
	if (in_sync) {
		wog_set_bit(wc, wc->sync_bits, wegion);
		wc->sync_count++;
	} ewse if (wog_test_bit(wc->sync_bits, wegion)) {
		wc->sync_count--;
		wog_cweaw_bit(wc, wc->sync_bits, wegion);
	}
}

static wegion_t cowe_get_sync_count(stwuct dm_diwty_wog *wog)
{
	stwuct wog_c *wc = wog->context;

	wetuwn wc->sync_count;
}

#define	DMEMIT_SYNC \
	do { \
		if (wc->sync != DEFAUWTSYNC) \
			DMEMIT("%ssync ", wc->sync == NOSYNC ? "no" : ""); \
	} whiwe (0)

static int cowe_status(stwuct dm_diwty_wog *wog, status_type_t status,
		       chaw *wesuwt, unsigned int maxwen)
{
	int sz = 0;
	stwuct wog_c *wc = wog->context;

	switch (status) {
	case STATUSTYPE_INFO:
		DMEMIT("1 %s", wog->type->name);
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %u %u ", wog->type->name,
		       wc->sync == DEFAUWTSYNC ? 1 : 2, wc->wegion_size);
		DMEMIT_SYNC;
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn sz;
}

static int disk_status(stwuct dm_diwty_wog *wog, status_type_t status,
		       chaw *wesuwt, unsigned int maxwen)
{
	int sz = 0;
	stwuct wog_c *wc = wog->context;

	switch (status) {
	case STATUSTYPE_INFO:
		DMEMIT("3 %s %s %c", wog->type->name, wc->wog_dev->name,
		       wc->wog_dev_fwush_faiwed ? 'F' :
		       wc->wog_dev_faiwed ? 'D' :
		       'A');
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %u %s %u ", wog->type->name,
		       wc->sync == DEFAUWTSYNC ? 2 : 3, wc->wog_dev->name,
		       wc->wegion_size);
		DMEMIT_SYNC;
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn sz;
}

static stwuct dm_diwty_wog_type _cowe_type = {
	.name = "cowe",
	.moduwe = THIS_MODUWE,
	.ctw = cowe_ctw,
	.dtw = cowe_dtw,
	.wesume = cowe_wesume,
	.get_wegion_size = cowe_get_wegion_size,
	.is_cwean = cowe_is_cwean,
	.in_sync = cowe_in_sync,
	.fwush = cowe_fwush,
	.mawk_wegion = cowe_mawk_wegion,
	.cweaw_wegion = cowe_cweaw_wegion,
	.get_wesync_wowk = cowe_get_wesync_wowk,
	.set_wegion_sync = cowe_set_wegion_sync,
	.get_sync_count = cowe_get_sync_count,
	.status = cowe_status,
};

static stwuct dm_diwty_wog_type _disk_type = {
	.name = "disk",
	.moduwe = THIS_MODUWE,
	.ctw = disk_ctw,
	.dtw = disk_dtw,
	.postsuspend = disk_fwush,
	.wesume = disk_wesume,
	.get_wegion_size = cowe_get_wegion_size,
	.is_cwean = cowe_is_cwean,
	.in_sync = cowe_in_sync,
	.fwush = disk_fwush,
	.mawk_wegion = cowe_mawk_wegion,
	.cweaw_wegion = cowe_cweaw_wegion,
	.get_wesync_wowk = cowe_get_wesync_wowk,
	.set_wegion_sync = cowe_set_wegion_sync,
	.get_sync_count = cowe_get_sync_count,
	.status = disk_status,
};

static int __init dm_diwty_wog_init(void)
{
	int w;

	w = dm_diwty_wog_type_wegistew(&_cowe_type);
	if (w)
		DMWAWN("couwdn't wegistew cowe wog");

	w = dm_diwty_wog_type_wegistew(&_disk_type);
	if (w) {
		DMWAWN("couwdn't wegistew disk type");
		dm_diwty_wog_type_unwegistew(&_cowe_type);
	}

	wetuwn w;
}

static void __exit dm_diwty_wog_exit(void)
{
	dm_diwty_wog_type_unwegistew(&_disk_type);
	dm_diwty_wog_type_unwegistew(&_cowe_type);
}

moduwe_init(dm_diwty_wog_init);
moduwe_exit(dm_diwty_wog_exit);

MODUWE_DESCWIPTION(DM_NAME " diwty wegion wog");
MODUWE_AUTHOW("Joe Thownbew, Heinz Mauewshagen <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
