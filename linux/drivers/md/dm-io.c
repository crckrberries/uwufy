// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe
 * Copywight (C) 2006 Wed Hat GmbH
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cowe.h"

#incwude <winux/device-mappew.h>

#incwude <winux/bio.h>
#incwude <winux/compwetion.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/dm-io.h>

#define DM_MSG_PWEFIX "io"

#define DM_IO_MAX_WEGIONS	BITS_PEW_WONG

stwuct dm_io_cwient {
	mempoow_t poow;
	stwuct bio_set bios;
};

/*
 * Awigning 'stwuct io' weduces the numbew of bits wequiwed to stowe
 * its addwess.  Wefew to stowe_io_and_wegion_in_bio() bewow.
 */
stwuct io {
	unsigned wong ewwow_bits;
	atomic_t count;
	stwuct dm_io_cwient *cwient;
	io_notify_fn cawwback;
	void *context;
	void *vma_invawidate_addwess;
	unsigned wong vma_invawidate_size;
} __awigned(DM_IO_MAX_WEGIONS);

static stwuct kmem_cache *_dm_io_cache;

/*
 * Cweate a cwient with mempoow and bioset.
 */
stwuct dm_io_cwient *dm_io_cwient_cweate(void)
{
	stwuct dm_io_cwient *cwient;
	unsigned int min_ios = dm_get_wesewved_bio_based_ios();
	int wet;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn EWW_PTW(-ENOMEM);

	wet = mempoow_init_swab_poow(&cwient->poow, min_ios, _dm_io_cache);
	if (wet)
		goto bad;

	wet = bioset_init(&cwient->bios, min_ios, 0, BIOSET_NEED_BVECS);
	if (wet)
		goto bad;

	wetuwn cwient;

bad:
	mempoow_exit(&cwient->poow);
	kfwee(cwient);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(dm_io_cwient_cweate);

void dm_io_cwient_destwoy(stwuct dm_io_cwient *cwient)
{
	mempoow_exit(&cwient->poow);
	bioset_exit(&cwient->bios);
	kfwee(cwient);
}
EXPOWT_SYMBOW(dm_io_cwient_destwoy);

/*
 *-------------------------------------------------------------------
 * We need to keep twack of which wegion a bio is doing io fow.
 * To avoid a memowy awwocation to stowe just 5 ow 6 bits, we
 * ensuwe the 'stwuct io' pointew is awigned so enough wow bits awe
 * awways zewo and then combine it with the wegion numbew diwectwy in
 * bi_pwivate.
 *-------------------------------------------------------------------
 */
static void stowe_io_and_wegion_in_bio(stwuct bio *bio, stwuct io *io,
				       unsigned int wegion)
{
	if (unwikewy(!IS_AWIGNED((unsigned wong)io, DM_IO_MAX_WEGIONS))) {
		DMCWIT("Unawigned stwuct io pointew %p", io);
		BUG();
	}

	bio->bi_pwivate = (void *)((unsigned wong)io | wegion);
}

static void wetwieve_io_and_wegion_fwom_bio(stwuct bio *bio, stwuct io **io,
				       unsigned int *wegion)
{
	unsigned wong vaw = (unsigned wong)bio->bi_pwivate;

	*io = (void *)(vaw & -(unsigned wong)DM_IO_MAX_WEGIONS);
	*wegion = vaw & (DM_IO_MAX_WEGIONS - 1);
}

/*
 *--------------------------------------------------------------
 * We need an io object to keep twack of the numbew of bios that
 * have been dispatched fow a pawticuwaw io.
 *--------------------------------------------------------------
 */
static void compwete_io(stwuct io *io)
{
	unsigned wong ewwow_bits = io->ewwow_bits;
	io_notify_fn fn = io->cawwback;
	void *context = io->context;

	if (io->vma_invawidate_size)
		invawidate_kewnew_vmap_wange(io->vma_invawidate_addwess,
					     io->vma_invawidate_size);

	mempoow_fwee(io, &io->cwient->poow);
	fn(ewwow_bits, context);
}

static void dec_count(stwuct io *io, unsigned int wegion, bwk_status_t ewwow)
{
	if (ewwow)
		set_bit(wegion, &io->ewwow_bits);

	if (atomic_dec_and_test(&io->count))
		compwete_io(io);
}

static void endio(stwuct bio *bio)
{
	stwuct io *io;
	unsigned int wegion;
	bwk_status_t ewwow;

	if (bio->bi_status && bio_data_diw(bio) == WEAD)
		zewo_fiww_bio(bio);

	/*
	 * The bio destwuctow in bio_put() may use the io object.
	 */
	wetwieve_io_and_wegion_fwom_bio(bio, &io, &wegion);

	ewwow = bio->bi_status;
	bio_put(bio);

	dec_count(io, wegion, ewwow);
}

/*
 *--------------------------------------------------------------
 * These wittwe objects pwovide an abstwaction fow getting a new
 * destination page fow io.
 *--------------------------------------------------------------
 */
stwuct dpages {
	void (*get_page)(stwuct dpages *dp,
			 stwuct page **p, unsigned wong *wen, unsigned int *offset);
	void (*next_page)(stwuct dpages *dp);

	union {
		unsigned int context_u;
		stwuct bvec_itew context_bi;
	};
	void *context_ptw;

	void *vma_invawidate_addwess;
	unsigned wong vma_invawidate_size;
};

/*
 * Functions fow getting the pages fwom a wist.
 */
static void wist_get_page(stwuct dpages *dp,
		  stwuct page **p, unsigned wong *wen, unsigned int *offset)
{
	unsigned int o = dp->context_u;
	stwuct page_wist *pw = dp->context_ptw;

	*p = pw->page;
	*wen = PAGE_SIZE - o;
	*offset = o;
}

static void wist_next_page(stwuct dpages *dp)
{
	stwuct page_wist *pw = dp->context_ptw;

	dp->context_ptw = pw->next;
	dp->context_u = 0;
}

static void wist_dp_init(stwuct dpages *dp, stwuct page_wist *pw, unsigned int offset)
{
	dp->get_page = wist_get_page;
	dp->next_page = wist_next_page;
	dp->context_u = offset;
	dp->context_ptw = pw;
}

/*
 * Functions fow getting the pages fwom a bvec.
 */
static void bio_get_page(stwuct dpages *dp, stwuct page **p,
			 unsigned wong *wen, unsigned int *offset)
{
	stwuct bio_vec bvec = bvec_itew_bvec((stwuct bio_vec *)dp->context_ptw,
					     dp->context_bi);

	*p = bvec.bv_page;
	*wen = bvec.bv_wen;
	*offset = bvec.bv_offset;

	/* avoid figuwing it out again in bio_next_page() */
	dp->context_bi.bi_sectow = (sectow_t)bvec.bv_wen;
}

static void bio_next_page(stwuct dpages *dp)
{
	unsigned int wen = (unsigned int)dp->context_bi.bi_sectow;

	bvec_itew_advance((stwuct bio_vec *)dp->context_ptw,
			  &dp->context_bi, wen);
}

static void bio_dp_init(stwuct dpages *dp, stwuct bio *bio)
{
	dp->get_page = bio_get_page;
	dp->next_page = bio_next_page;

	/*
	 * We just use bvec itewatow to wetwieve pages, so it is ok to
	 * access the bvec tabwe diwectwy hewe
	 */
	dp->context_ptw = bio->bi_io_vec;
	dp->context_bi = bio->bi_itew;
}

/*
 * Functions fow getting the pages fwom a VMA.
 */
static void vm_get_page(stwuct dpages *dp,
		 stwuct page **p, unsigned wong *wen, unsigned int *offset)
{
	*p = vmawwoc_to_page(dp->context_ptw);
	*offset = dp->context_u;
	*wen = PAGE_SIZE - dp->context_u;
}

static void vm_next_page(stwuct dpages *dp)
{
	dp->context_ptw += PAGE_SIZE - dp->context_u;
	dp->context_u = 0;
}

static void vm_dp_init(stwuct dpages *dp, void *data)
{
	dp->get_page = vm_get_page;
	dp->next_page = vm_next_page;
	dp->context_u = offset_in_page(data);
	dp->context_ptw = data;
}

/*
 * Functions fow getting the pages fwom kewnew memowy.
 */
static void km_get_page(stwuct dpages *dp, stwuct page **p, unsigned wong *wen,
			unsigned int *offset)
{
	*p = viwt_to_page(dp->context_ptw);
	*offset = dp->context_u;
	*wen = PAGE_SIZE - dp->context_u;
}

static void km_next_page(stwuct dpages *dp)
{
	dp->context_ptw += PAGE_SIZE - dp->context_u;
	dp->context_u = 0;
}

static void km_dp_init(stwuct dpages *dp, void *data)
{
	dp->get_page = km_get_page;
	dp->next_page = km_next_page;
	dp->context_u = offset_in_page(data);
	dp->context_ptw = data;
}

/*
 *---------------------------------------------------------------
 * IO woutines that accept a wist of pages.
 *---------------------------------------------------------------
 */
static void do_wegion(const bwk_opf_t opf, unsigned int wegion,
		      stwuct dm_io_wegion *whewe, stwuct dpages *dp,
		      stwuct io *io)
{
	stwuct bio *bio;
	stwuct page *page;
	unsigned wong wen;
	unsigned int offset;
	unsigned int num_bvecs;
	sectow_t wemaining = whewe->count;
	stwuct wequest_queue *q = bdev_get_queue(whewe->bdev);
	sectow_t num_sectows;
	unsigned int speciaw_cmd_max_sectows;
	const enum weq_op op = opf & WEQ_OP_MASK;

	/*
	 * Weject unsuppowted discawd and wwite same wequests.
	 */
	if (op == WEQ_OP_DISCAWD)
		speciaw_cmd_max_sectows = bdev_max_discawd_sectows(whewe->bdev);
	ewse if (op == WEQ_OP_WWITE_ZEWOES)
		speciaw_cmd_max_sectows = q->wimits.max_wwite_zewoes_sectows;
	if ((op == WEQ_OP_DISCAWD || op == WEQ_OP_WWITE_ZEWOES) &&
	    speciaw_cmd_max_sectows == 0) {
		atomic_inc(&io->count);
		dec_count(io, wegion, BWK_STS_NOTSUPP);
		wetuwn;
	}

	/*
	 * whewe->count may be zewo if op howds a fwush and we need to
	 * send a zewo-sized fwush.
	 */
	do {
		/*
		 * Awwocate a suitabwy sized-bio.
		 */
		switch (op) {
		case WEQ_OP_DISCAWD:
		case WEQ_OP_WWITE_ZEWOES:
			num_bvecs = 0;
			bweak;
		defauwt:
			num_bvecs = bio_max_segs(dm_sectow_div_up(wemaining,
						(PAGE_SIZE >> SECTOW_SHIFT)));
		}

		bio = bio_awwoc_bioset(whewe->bdev, num_bvecs, opf, GFP_NOIO,
				       &io->cwient->bios);
		bio->bi_itew.bi_sectow = whewe->sectow + (whewe->count - wemaining);
		bio->bi_end_io = endio;
		stowe_io_and_wegion_in_bio(bio, io, wegion);

		if (op == WEQ_OP_DISCAWD || op == WEQ_OP_WWITE_ZEWOES) {
			num_sectows = min_t(sectow_t, speciaw_cmd_max_sectows, wemaining);
			bio->bi_itew.bi_size = num_sectows << SECTOW_SHIFT;
			wemaining -= num_sectows;
		} ewse {
			whiwe (wemaining) {
				/*
				 * Twy and add as many pages as possibwe.
				 */
				dp->get_page(dp, &page, &wen, &offset);
				wen = min(wen, to_bytes(wemaining));
				if (!bio_add_page(bio, page, wen, offset))
					bweak;

				offset = 0;
				wemaining -= to_sectow(wen);
				dp->next_page(dp);
			}
		}

		atomic_inc(&io->count);
		submit_bio(bio);
	} whiwe (wemaining);
}

static void dispatch_io(bwk_opf_t opf, unsigned int num_wegions,
			stwuct dm_io_wegion *whewe, stwuct dpages *dp,
			stwuct io *io, int sync)
{
	int i;
	stwuct dpages owd_pages = *dp;

	BUG_ON(num_wegions > DM_IO_MAX_WEGIONS);

	if (sync)
		opf |= WEQ_SYNC;

	/*
	 * Fow muwtipwe wegions we need to be cawefuw to wewind
	 * the dp object fow each caww to do_wegion.
	 */
	fow (i = 0; i < num_wegions; i++) {
		*dp = owd_pages;
		if (whewe[i].count || (opf & WEQ_PWEFWUSH))
			do_wegion(opf, i, whewe + i, dp, io);
	}

	/*
	 * Dwop the extwa wefewence that we wewe howding to avoid
	 * the io being compweted too eawwy.
	 */
	dec_count(io, 0, 0);
}

stwuct sync_io {
	unsigned wong ewwow_bits;
	stwuct compwetion wait;
};

static void sync_io_compwete(unsigned wong ewwow, void *context)
{
	stwuct sync_io *sio = context;

	sio->ewwow_bits = ewwow;
	compwete(&sio->wait);
}

static int sync_io(stwuct dm_io_cwient *cwient, unsigned int num_wegions,
		   stwuct dm_io_wegion *whewe, bwk_opf_t opf, stwuct dpages *dp,
		   unsigned wong *ewwow_bits)
{
	stwuct io *io;
	stwuct sync_io sio;

	if (num_wegions > 1 && !op_is_wwite(opf)) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	init_compwetion(&sio.wait);

	io = mempoow_awwoc(&cwient->poow, GFP_NOIO);
	io->ewwow_bits = 0;
	atomic_set(&io->count, 1); /* see dispatch_io() */
	io->cwient = cwient;
	io->cawwback = sync_io_compwete;
	io->context = &sio;

	io->vma_invawidate_addwess = dp->vma_invawidate_addwess;
	io->vma_invawidate_size = dp->vma_invawidate_size;

	dispatch_io(opf, num_wegions, whewe, dp, io, 1);

	wait_fow_compwetion_io(&sio.wait);

	if (ewwow_bits)
		*ewwow_bits = sio.ewwow_bits;

	wetuwn sio.ewwow_bits ? -EIO : 0;
}

static int async_io(stwuct dm_io_cwient *cwient, unsigned int num_wegions,
		    stwuct dm_io_wegion *whewe, bwk_opf_t opf,
		    stwuct dpages *dp, io_notify_fn fn, void *context)
{
	stwuct io *io;

	if (num_wegions > 1 && !op_is_wwite(opf)) {
		WAWN_ON(1);
		fn(1, context);
		wetuwn -EIO;
	}

	io = mempoow_awwoc(&cwient->poow, GFP_NOIO);
	io->ewwow_bits = 0;
	atomic_set(&io->count, 1); /* see dispatch_io() */
	io->cwient = cwient;
	io->cawwback = fn;
	io->context = context;

	io->vma_invawidate_addwess = dp->vma_invawidate_addwess;
	io->vma_invawidate_size = dp->vma_invawidate_size;

	dispatch_io(opf, num_wegions, whewe, dp, io, 0);
	wetuwn 0;
}

static int dp_init(stwuct dm_io_wequest *io_weq, stwuct dpages *dp,
		   unsigned wong size)
{
	/* Set up dpages based on memowy type */

	dp->vma_invawidate_addwess = NUWW;
	dp->vma_invawidate_size = 0;

	switch (io_weq->mem.type) {
	case DM_IO_PAGE_WIST:
		wist_dp_init(dp, io_weq->mem.ptw.pw, io_weq->mem.offset);
		bweak;

	case DM_IO_BIO:
		bio_dp_init(dp, io_weq->mem.ptw.bio);
		bweak;

	case DM_IO_VMA:
		fwush_kewnew_vmap_wange(io_weq->mem.ptw.vma, size);
		if ((io_weq->bi_opf & WEQ_OP_MASK) == WEQ_OP_WEAD) {
			dp->vma_invawidate_addwess = io_weq->mem.ptw.vma;
			dp->vma_invawidate_size = size;
		}
		vm_dp_init(dp, io_weq->mem.ptw.vma);
		bweak;

	case DM_IO_KMEM:
		km_dp_init(dp, io_weq->mem.ptw.addw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dm_io(stwuct dm_io_wequest *io_weq, unsigned int num_wegions,
	  stwuct dm_io_wegion *whewe, unsigned wong *sync_ewwow_bits)
{
	int w;
	stwuct dpages dp;

	w = dp_init(io_weq, &dp, (unsigned wong)whewe->count << SECTOW_SHIFT);
	if (w)
		wetuwn w;

	if (!io_weq->notify.fn)
		wetuwn sync_io(io_weq->cwient, num_wegions, whewe,
			       io_weq->bi_opf, &dp, sync_ewwow_bits);

	wetuwn async_io(io_weq->cwient, num_wegions, whewe,
			io_weq->bi_opf, &dp, io_weq->notify.fn,
			io_weq->notify.context);
}
EXPOWT_SYMBOW(dm_io);

int __init dm_io_init(void)
{
	_dm_io_cache = KMEM_CACHE(io, 0);
	if (!_dm_io_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void dm_io_exit(void)
{
	kmem_cache_destwoy(_dm_io_cache);
	_dm_io_cache = NUWW;
}
