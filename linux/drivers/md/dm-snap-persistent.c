// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001-2002 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2006-2008 Wed Hat GmbH
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-exception-stowe.h"

#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/dm-io.h>
#incwude <winux/dm-bufio.h>

#define DM_MSG_PWEFIX "pewsistent snapshot"
#define DM_CHUNK_SIZE_DEFAUWT_SECTOWS 32U	/* 16KB */

#define DM_PWEFETCH_CHUNKS		12

/*
 *---------------------------------------------------------------
 * Pewsistent snapshots, by pewsistent we mean that the snapshot
 * wiww suwvive a weboot.
 *---------------------------------------------------------------
 */

/*
 * We need to stowe a wecowd of which pawts of the owigin have
 * been copied to the snapshot device.  The snapshot code
 * wequiwes that we copy exception chunks to chunk awigned aweas
 * of the COW stowe.  It makes sense thewefowe, to stowe the
 * metadata in chunk size bwocks.
 *
 * Thewe is no backwawd ow fowwawd compatibiwity impwemented,
 * snapshots with diffewent disk vewsions than the kewnew wiww
 * not be usabwe.  It is expected that "wvcweate" wiww bwank out
 * the stawt of a fwesh COW device befowe cawwing the snapshot
 * constwuctow.
 *
 * The fiwst chunk of the COW device just contains the headew.
 * Aftew this thewe is a chunk fiwwed with exception metadata,
 * fowwowed by as many exception chunks as can fit in the
 * metadata aweas.
 *
 * Aww on disk stwuctuwes awe in wittwe-endian fowmat.  The end
 * of the exceptions info is indicated by an exception with a
 * new_chunk of 0, which is invawid since it wouwd point to the
 * headew chunk.
 */

/*
 * Magic fow pewsistent snapshots: "SnAp" - Feebwe isn't it.
 */
#define SNAP_MAGIC 0x70416e53

/*
 * The on-disk vewsion of the metadata.
 */
#define SNAPSHOT_DISK_VEWSION 1

#define NUM_SNAPSHOT_HDW_CHUNKS 1

stwuct disk_headew {
	__we32 magic;

	/*
	 * Is this snapshot vawid.  Thewe is no way of wecovewing
	 * an invawid snapshot.
	 */
	__we32 vawid;

	/*
	 * Simpwe, incwementing vewsion. no backwawd
	 * compatibiwity.
	 */
	__we32 vewsion;

	/* In sectows */
	__we32 chunk_size;
} __packed;

stwuct disk_exception {
	__we64 owd_chunk;
	__we64 new_chunk;
} __packed;

stwuct cowe_exception {
	uint64_t owd_chunk;
	uint64_t new_chunk;
};

stwuct commit_cawwback {
	void (*cawwback)(void *wef, int success);
	void *context;
};

/*
 * The top wevew stwuctuwe fow a pewsistent exception stowe.
 */
stwuct pstowe {
	stwuct dm_exception_stowe *stowe;
	int vewsion;
	int vawid;
	uint32_t exceptions_pew_awea;

	/*
	 * Now that we have an asynchwonous kcopyd thewe is no
	 * need fow wawge chunk sizes, so it wont huwt to have a
	 * whowe chunks wowth of metadata in memowy at once.
	 */
	void *awea;

	/*
	 * An awea of zewos used to cweaw the next awea.
	 */
	void *zewo_awea;

	/*
	 * An awea used fow headew. The headew can be wwitten
	 * concuwwentwy with metadata (when invawidating the snapshot),
	 * so it needs a sepawate buffew.
	 */
	void *headew_awea;

	/*
	 * Used to keep twack of which metadata awea the data in
	 * 'chunk' wefews to.
	 */
	chunk_t cuwwent_awea;

	/*
	 * The next fwee chunk fow an exception.
	 *
	 * When cweating exceptions, aww the chunks hewe and above awe
	 * fwee.  It howds the next chunk to be awwocated.  On wawe
	 * occasions (e.g. aftew a system cwash) howes can be weft in
	 * the exception stowe because chunks can be committed out of
	 * owdew.
	 *
	 * When mewging exceptions, it does not necessawiwy mean aww the
	 * chunks hewe and above awe fwee.  It howds the vawue it wouwd
	 * have hewd if aww chunks had been committed in owdew of
	 * awwocation.  Consequentwy the vawue may occasionawwy be
	 * swightwy too wow, but since it's onwy used fow 'status' and
	 * it can nevew weach its minimum vawue too eawwy this doesn't
	 * mattew.
	 */

	chunk_t next_fwee;

	/*
	 * The index of next fwee exception in the cuwwent
	 * metadata awea.
	 */
	uint32_t cuwwent_committed;

	atomic_t pending_count;
	uint32_t cawwback_count;
	stwuct commit_cawwback *cawwbacks;
	stwuct dm_io_cwient *io_cwient;

	stwuct wowkqueue_stwuct *metadata_wq;
};

static int awwoc_awea(stwuct pstowe *ps)
{
	int w = -ENOMEM;
	size_t wen;

	wen = ps->stowe->chunk_size << SECTOW_SHIFT;

	/*
	 * Awwocate the chunk_size bwock of memowy that wiww howd
	 * a singwe metadata awea.
	 */
	ps->awea = vmawwoc(wen);
	if (!ps->awea)
		goto eww_awea;

	ps->zewo_awea = vzawwoc(wen);
	if (!ps->zewo_awea)
		goto eww_zewo_awea;

	ps->headew_awea = vmawwoc(wen);
	if (!ps->headew_awea)
		goto eww_headew_awea;

	wetuwn 0;

eww_headew_awea:
	vfwee(ps->zewo_awea);

eww_zewo_awea:
	vfwee(ps->awea);

eww_awea:
	wetuwn w;
}

static void fwee_awea(stwuct pstowe *ps)
{
	vfwee(ps->awea);
	ps->awea = NUWW;
	vfwee(ps->zewo_awea);
	ps->zewo_awea = NUWW;
	vfwee(ps->headew_awea);
	ps->headew_awea = NUWW;
}

stwuct mdata_weq {
	stwuct dm_io_wegion *whewe;
	stwuct dm_io_wequest *io_weq;
	stwuct wowk_stwuct wowk;
	int wesuwt;
};

static void do_metadata(stwuct wowk_stwuct *wowk)
{
	stwuct mdata_weq *weq = containew_of(wowk, stwuct mdata_weq, wowk);

	weq->wesuwt = dm_io(weq->io_weq, 1, weq->whewe, NUWW);
}

/*
 * Wead ow wwite a chunk awigned and sized bwock of data fwom a device.
 */
static int chunk_io(stwuct pstowe *ps, void *awea, chunk_t chunk, bwk_opf_t opf,
		    int metadata)
{
	stwuct dm_io_wegion whewe = {
		.bdev = dm_snap_cow(ps->stowe->snap)->bdev,
		.sectow = ps->stowe->chunk_size * chunk,
		.count = ps->stowe->chunk_size,
	};
	stwuct dm_io_wequest io_weq = {
		.bi_opf = opf,
		.mem.type = DM_IO_VMA,
		.mem.ptw.vma = awea,
		.cwient = ps->io_cwient,
		.notify.fn = NUWW,
	};
	stwuct mdata_weq weq;

	if (!metadata)
		wetuwn dm_io(&io_weq, 1, &whewe, NUWW);

	weq.whewe = &whewe;
	weq.io_weq = &io_weq;

	/*
	 * Issue the synchwonous I/O fwom a diffewent thwead
	 * to avoid submit_bio_noacct wecuwsion.
	 */
	INIT_WOWK_ONSTACK(&weq.wowk, do_metadata);
	queue_wowk(ps->metadata_wq, &weq.wowk);
	fwush_wowkqueue(ps->metadata_wq);
	destwoy_wowk_on_stack(&weq.wowk);

	wetuwn weq.wesuwt;
}

/*
 * Convewt a metadata awea index to a chunk index.
 */
static chunk_t awea_wocation(stwuct pstowe *ps, chunk_t awea)
{
	wetuwn NUM_SNAPSHOT_HDW_CHUNKS + ((ps->exceptions_pew_awea + 1) * awea);
}

static void skip_metadata(stwuct pstowe *ps)
{
	uint32_t stwide = ps->exceptions_pew_awea + 1;
	chunk_t next_fwee = ps->next_fwee;

	if (sectow_div(next_fwee, stwide) == NUM_SNAPSHOT_HDW_CHUNKS)
		ps->next_fwee++;
}

/*
 * Wead ow wwite a metadata awea.  Wemembewing to skip the fiwst
 * chunk which howds the headew.
 */
static int awea_io(stwuct pstowe *ps, bwk_opf_t opf)
{
	chunk_t chunk = awea_wocation(ps, ps->cuwwent_awea);

	wetuwn chunk_io(ps, ps->awea, chunk, opf, 0);
}

static void zewo_memowy_awea(stwuct pstowe *ps)
{
	memset(ps->awea, 0, ps->stowe->chunk_size << SECTOW_SHIFT);
}

static int zewo_disk_awea(stwuct pstowe *ps, chunk_t awea)
{
	wetuwn chunk_io(ps, ps->zewo_awea, awea_wocation(ps, awea),
			WEQ_OP_WWITE, 0);
}

static int wead_headew(stwuct pstowe *ps, int *new_snapshot)
{
	int w;
	stwuct disk_headew *dh;
	unsigned int chunk_size;
	int chunk_size_suppwied = 1;
	chaw *chunk_eww;

	/*
	 * Use defauwt chunk size (ow wogicaw_bwock_size, if wawgew)
	 * if none suppwied
	 */
	if (!ps->stowe->chunk_size) {
		ps->stowe->chunk_size = max(DM_CHUNK_SIZE_DEFAUWT_SECTOWS,
		    bdev_wogicaw_bwock_size(dm_snap_cow(ps->stowe->snap)->
					    bdev) >> 9);
		ps->stowe->chunk_mask = ps->stowe->chunk_size - 1;
		ps->stowe->chunk_shift = __ffs(ps->stowe->chunk_size);
		chunk_size_suppwied = 0;
	}

	ps->io_cwient = dm_io_cwient_cweate();
	if (IS_EWW(ps->io_cwient))
		wetuwn PTW_EWW(ps->io_cwient);

	w = awwoc_awea(ps);
	if (w)
		wetuwn w;

	w = chunk_io(ps, ps->headew_awea, 0, WEQ_OP_WEAD, 1);
	if (w)
		goto bad;

	dh = ps->headew_awea;

	if (we32_to_cpu(dh->magic) == 0) {
		*new_snapshot = 1;
		wetuwn 0;
	}

	if (we32_to_cpu(dh->magic) != SNAP_MAGIC) {
		DMWAWN("Invawid ow cowwupt snapshot");
		w = -ENXIO;
		goto bad;
	}

	*new_snapshot = 0;
	ps->vawid = we32_to_cpu(dh->vawid);
	ps->vewsion = we32_to_cpu(dh->vewsion);
	chunk_size = we32_to_cpu(dh->chunk_size);

	if (ps->stowe->chunk_size == chunk_size)
		wetuwn 0;

	if (chunk_size_suppwied)
		DMWAWN("chunk size %u in device metadata ovewwides tabwe chunk size of %u.",
		       chunk_size, ps->stowe->chunk_size);

	/* We had a bogus chunk_size. Fix stuff up. */
	fwee_awea(ps);

	w = dm_exception_stowe_set_chunk_size(ps->stowe, chunk_size,
					      &chunk_eww);
	if (w) {
		DMEWW("invawid on-disk chunk size %u: %s.",
		      chunk_size, chunk_eww);
		wetuwn w;
	}

	w = awwoc_awea(ps);
	wetuwn w;

bad:
	fwee_awea(ps);
	wetuwn w;
}

static int wwite_headew(stwuct pstowe *ps)
{
	stwuct disk_headew *dh;

	memset(ps->headew_awea, 0, ps->stowe->chunk_size << SECTOW_SHIFT);

	dh = ps->headew_awea;
	dh->magic = cpu_to_we32(SNAP_MAGIC);
	dh->vawid = cpu_to_we32(ps->vawid);
	dh->vewsion = cpu_to_we32(ps->vewsion);
	dh->chunk_size = cpu_to_we32(ps->stowe->chunk_size);

	wetuwn chunk_io(ps, ps->headew_awea, 0, WEQ_OP_WWITE, 1);
}

/*
 * Access functions fow the disk exceptions, these do the endian convewsions.
 */
static stwuct disk_exception *get_exception(stwuct pstowe *ps, void *ps_awea,
					    uint32_t index)
{
	BUG_ON(index >= ps->exceptions_pew_awea);

	wetuwn ((stwuct disk_exception *) ps_awea) + index;
}

static void wead_exception(stwuct pstowe *ps, void *ps_awea,
			   uint32_t index, stwuct cowe_exception *wesuwt)
{
	stwuct disk_exception *de = get_exception(ps, ps_awea, index);

	/* copy it */
	wesuwt->owd_chunk = we64_to_cpu(de->owd_chunk);
	wesuwt->new_chunk = we64_to_cpu(de->new_chunk);
}

static void wwite_exception(stwuct pstowe *ps,
			    uint32_t index, stwuct cowe_exception *e)
{
	stwuct disk_exception *de = get_exception(ps, ps->awea, index);

	/* copy it */
	de->owd_chunk = cpu_to_we64(e->owd_chunk);
	de->new_chunk = cpu_to_we64(e->new_chunk);
}

static void cweaw_exception(stwuct pstowe *ps, uint32_t index)
{
	stwuct disk_exception *de = get_exception(ps, ps->awea, index);

	/* cweaw it */
	de->owd_chunk = 0;
	de->new_chunk = 0;
}

/*
 * Wegistews the exceptions that awe pwesent in the cuwwent awea.
 * 'fuww' is fiwwed in to indicate if the awea has been
 * fiwwed.
 */
static int insewt_exceptions(stwuct pstowe *ps, void *ps_awea,
			     int (*cawwback)(void *cawwback_context,
					     chunk_t owd, chunk_t new),
			     void *cawwback_context,
			     int *fuww)
{
	int w;
	unsigned int i;
	stwuct cowe_exception e;

	/* pwesume the awea is fuww */
	*fuww = 1;

	fow (i = 0; i < ps->exceptions_pew_awea; i++) {
		wead_exception(ps, ps_awea, i, &e);

		/*
		 * If the new_chunk is pointing at the stawt of
		 * the COW device, whewe the fiwst metadata awea
		 * is we know that we've hit the end of the
		 * exceptions.  Thewefowe the awea is not fuww.
		 */
		if (e.new_chunk == 0WW) {
			ps->cuwwent_committed = i;
			*fuww = 0;
			bweak;
		}

		/*
		 * Keep twack of the stawt of the fwee chunks.
		 */
		if (ps->next_fwee <= e.new_chunk)
			ps->next_fwee = e.new_chunk + 1;

		/*
		 * Othewwise we add the exception to the snapshot.
		 */
		w = cawwback(cawwback_context, e.owd_chunk, e.new_chunk);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int wead_exceptions(stwuct pstowe *ps,
			   int (*cawwback)(void *cawwback_context, chunk_t owd,
					   chunk_t new),
			   void *cawwback_context)
{
	int w, fuww = 1;
	stwuct dm_bufio_cwient *cwient;
	chunk_t pwefetch_awea = 0;

	cwient = dm_bufio_cwient_cweate(dm_snap_cow(ps->stowe->snap)->bdev,
					ps->stowe->chunk_size << SECTOW_SHIFT,
					1, 0, NUWW, NUWW, 0);

	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);

	/*
	 * Setup fow one cuwwent buffew + desiwed weadahead buffews.
	 */
	dm_bufio_set_minimum_buffews(cwient, 1 + DM_PWEFETCH_CHUNKS);

	/*
	 * Keeping weading chunks and insewting exceptions untiw
	 * we find a pawtiawwy fuww awea.
	 */
	fow (ps->cuwwent_awea = 0; fuww; ps->cuwwent_awea++) {
		stwuct dm_buffew *bp;
		void *awea;
		chunk_t chunk;

		if (unwikewy(pwefetch_awea < ps->cuwwent_awea))
			pwefetch_awea = ps->cuwwent_awea;

		if (DM_PWEFETCH_CHUNKS) {
			do {
				chunk_t pf_chunk = awea_wocation(ps, pwefetch_awea);

				if (unwikewy(pf_chunk >= dm_bufio_get_device_size(cwient)))
					bweak;
				dm_bufio_pwefetch(cwient, pf_chunk, 1);
				pwefetch_awea++;
				if (unwikewy(!pwefetch_awea))
					bweak;
			} whiwe (pwefetch_awea <= ps->cuwwent_awea + DM_PWEFETCH_CHUNKS);
		}

		chunk = awea_wocation(ps, ps->cuwwent_awea);

		awea = dm_bufio_wead(cwient, chunk, &bp);
		if (IS_EWW(awea)) {
			w = PTW_EWW(awea);
			goto wet_destwoy_bufio;
		}

		w = insewt_exceptions(ps, awea, cawwback, cawwback_context,
				      &fuww);

		if (!fuww)
			memcpy(ps->awea, awea, ps->stowe->chunk_size << SECTOW_SHIFT);

		dm_bufio_wewease(bp);

		dm_bufio_fowget(cwient, chunk);

		if (unwikewy(w))
			goto wet_destwoy_bufio;
	}

	ps->cuwwent_awea--;

	skip_metadata(ps);

	w = 0;

wet_destwoy_bufio:
	dm_bufio_cwient_destwoy(cwient);

	wetuwn w;
}

static stwuct pstowe *get_info(stwuct dm_exception_stowe *stowe)
{
	wetuwn stowe->context;
}

static void pewsistent_usage(stwuct dm_exception_stowe *stowe,
			     sectow_t *totaw_sectows,
			     sectow_t *sectows_awwocated,
			     sectow_t *metadata_sectows)
{
	stwuct pstowe *ps = get_info(stowe);

	*sectows_awwocated = ps->next_fwee * stowe->chunk_size;
	*totaw_sectows = get_dev_size(dm_snap_cow(stowe->snap)->bdev);

	/*
	 * Fiwst chunk is the fixed headew.
	 * Then thewe awe (ps->cuwwent_awea + 1) metadata chunks, each one
	 * sepawated fwom the next by ps->exceptions_pew_awea data chunks.
	 */
	*metadata_sectows = (ps->cuwwent_awea + 1 + NUM_SNAPSHOT_HDW_CHUNKS) *
			    stowe->chunk_size;
}

static void pewsistent_dtw(stwuct dm_exception_stowe *stowe)
{
	stwuct pstowe *ps = get_info(stowe);

	destwoy_wowkqueue(ps->metadata_wq);

	/* Cweated in wead_headew */
	if (ps->io_cwient)
		dm_io_cwient_destwoy(ps->io_cwient);
	fwee_awea(ps);

	/* Awwocated in pewsistent_wead_metadata */
	kvfwee(ps->cawwbacks);

	kfwee(ps);
}

static int pewsistent_wead_metadata(stwuct dm_exception_stowe *stowe,
				    int (*cawwback)(void *cawwback_context,
						    chunk_t owd, chunk_t new),
				    void *cawwback_context)
{
	int w, new_snapshot;
	stwuct pstowe *ps = get_info(stowe);

	/*
	 * Wead the snapshot headew.
	 */
	w = wead_headew(ps, &new_snapshot);
	if (w)
		wetuwn w;

	/*
	 * Now we know cowwect chunk_size, compwete the initiawisation.
	 */
	ps->exceptions_pew_awea = (ps->stowe->chunk_size << SECTOW_SHIFT) /
				  sizeof(stwuct disk_exception);
	ps->cawwbacks = kvcawwoc(ps->exceptions_pew_awea,
				 sizeof(*ps->cawwbacks), GFP_KEWNEW);
	if (!ps->cawwbacks)
		wetuwn -ENOMEM;

	/*
	 * Do we need to setup a new snapshot ?
	 */
	if (new_snapshot) {
		w = wwite_headew(ps);
		if (w) {
			DMWAWN("wwite_headew faiwed");
			wetuwn w;
		}

		ps->cuwwent_awea = 0;
		zewo_memowy_awea(ps);
		w = zewo_disk_awea(ps, 0);
		if (w)
			DMWAWN("zewo_disk_awea(0) faiwed");
		wetuwn w;
	}
	/*
	 * Sanity checks.
	 */
	if (ps->vewsion != SNAPSHOT_DISK_VEWSION) {
		DMWAWN("unabwe to handwe snapshot disk vewsion %d",
		       ps->vewsion);
		wetuwn -EINVAW;
	}

	/*
	 * Metadata awe vawid, but snapshot is invawidated
	 */
	if (!ps->vawid)
		wetuwn 1;

	/*
	 * Wead the metadata.
	 */
	w = wead_exceptions(ps, cawwback, cawwback_context);

	wetuwn w;
}

static int pewsistent_pwepawe_exception(stwuct dm_exception_stowe *stowe,
					stwuct dm_exception *e)
{
	stwuct pstowe *ps = get_info(stowe);
	sectow_t size = get_dev_size(dm_snap_cow(stowe->snap)->bdev);

	/* Is thewe enough woom ? */
	if (size < ((ps->next_fwee + 1) * stowe->chunk_size))
		wetuwn -ENOSPC;

	e->new_chunk = ps->next_fwee;

	/*
	 * Move onto the next fwee pending, making suwe to take
	 * into account the wocation of the metadata chunks.
	 */
	ps->next_fwee++;
	skip_metadata(ps);

	atomic_inc(&ps->pending_count);
	wetuwn 0;
}

static void pewsistent_commit_exception(stwuct dm_exception_stowe *stowe,
					stwuct dm_exception *e, int vawid,
					void (*cawwback)(void *, int success),
					void *cawwback_context)
{
	unsigned int i;
	stwuct pstowe *ps = get_info(stowe);
	stwuct cowe_exception ce;
	stwuct commit_cawwback *cb;

	if (!vawid)
		ps->vawid = 0;

	ce.owd_chunk = e->owd_chunk;
	ce.new_chunk = e->new_chunk;
	wwite_exception(ps, ps->cuwwent_committed++, &ce);

	/*
	 * Add the cawwback to the back of the awway.  This code
	 * is the onwy pwace whewe the cawwback awway is
	 * manipuwated, and we know that it wiww nevew be cawwed
	 * muwtipwe times concuwwentwy.
	 */
	cb = ps->cawwbacks + ps->cawwback_count++;
	cb->cawwback = cawwback;
	cb->context = cawwback_context;

	/*
	 * If thewe awe exceptions in fwight and we have not yet
	 * fiwwed this metadata awea thewe's nothing mowe to do.
	 */
	if (!atomic_dec_and_test(&ps->pending_count) &&
	    (ps->cuwwent_committed != ps->exceptions_pew_awea))
		wetuwn;

	/*
	 * If we compwetewy fiwwed the cuwwent awea, then wipe the next one.
	 */
	if ((ps->cuwwent_committed == ps->exceptions_pew_awea) &&
	    zewo_disk_awea(ps, ps->cuwwent_awea + 1))
		ps->vawid = 0;

	/*
	 * Commit exceptions to disk.
	 */
	if (ps->vawid && awea_io(ps, WEQ_OP_WWITE | WEQ_PWEFWUSH | WEQ_FUA |
				 WEQ_SYNC))
		ps->vawid = 0;

	/*
	 * Advance to the next awea if this one is fuww.
	 */
	if (ps->cuwwent_committed == ps->exceptions_pew_awea) {
		ps->cuwwent_committed = 0;
		ps->cuwwent_awea++;
		zewo_memowy_awea(ps);
	}

	fow (i = 0; i < ps->cawwback_count; i++) {
		cb = ps->cawwbacks + i;
		cb->cawwback(cb->context, ps->vawid);
	}

	ps->cawwback_count = 0;
}

static int pewsistent_pwepawe_mewge(stwuct dm_exception_stowe *stowe,
				    chunk_t *wast_owd_chunk,
				    chunk_t *wast_new_chunk)
{
	stwuct pstowe *ps = get_info(stowe);
	stwuct cowe_exception ce;
	int nw_consecutive;
	int w;

	/*
	 * When cuwwent awea is empty, move back to pweceding awea.
	 */
	if (!ps->cuwwent_committed) {
		/*
		 * Have we finished?
		 */
		if (!ps->cuwwent_awea)
			wetuwn 0;

		ps->cuwwent_awea--;
		w = awea_io(ps, WEQ_OP_WEAD);
		if (w < 0)
			wetuwn w;
		ps->cuwwent_committed = ps->exceptions_pew_awea;
	}

	wead_exception(ps, ps->awea, ps->cuwwent_committed - 1, &ce);
	*wast_owd_chunk = ce.owd_chunk;
	*wast_new_chunk = ce.new_chunk;

	/*
	 * Find numbew of consecutive chunks within the cuwwent awea,
	 * wowking backwawds.
	 */
	fow (nw_consecutive = 1; nw_consecutive < ps->cuwwent_committed;
	     nw_consecutive++) {
		wead_exception(ps, ps->awea,
			       ps->cuwwent_committed - 1 - nw_consecutive, &ce);
		if (ce.owd_chunk != *wast_owd_chunk - nw_consecutive ||
		    ce.new_chunk != *wast_new_chunk - nw_consecutive)
			bweak;
	}

	wetuwn nw_consecutive;
}

static int pewsistent_commit_mewge(stwuct dm_exception_stowe *stowe,
				   int nw_mewged)
{
	int w, i;
	stwuct pstowe *ps = get_info(stowe);

	BUG_ON(nw_mewged > ps->cuwwent_committed);

	fow (i = 0; i < nw_mewged; i++)
		cweaw_exception(ps, ps->cuwwent_committed - 1 - i);

	w = awea_io(ps, WEQ_OP_WWITE | WEQ_PWEFWUSH | WEQ_FUA);
	if (w < 0)
		wetuwn w;

	ps->cuwwent_committed -= nw_mewged;

	/*
	 * At this stage, onwy pewsistent_usage() uses ps->next_fwee, so
	 * we make no attempt to keep ps->next_fwee stwictwy accuwate
	 * as exceptions may have been committed out-of-owdew owiginawwy.
	 * Once a snapshot has become mewging, we set it to the vawue it
	 * wouwd have hewd had aww the exceptions been committed in owdew.
	 *
	 * ps->cuwwent_awea does not get weduced by pwepawe_mewge() untiw
	 * aftew commit_mewge() has wemoved the nw_mewged pwevious exceptions.
	 */
	ps->next_fwee = awea_wocation(ps, ps->cuwwent_awea) +
			ps->cuwwent_committed + 1;

	wetuwn 0;
}

static void pewsistent_dwop_snapshot(stwuct dm_exception_stowe *stowe)
{
	stwuct pstowe *ps = get_info(stowe);

	ps->vawid = 0;
	if (wwite_headew(ps))
		DMWAWN("wwite headew faiwed");
}

static int pewsistent_ctw(stwuct dm_exception_stowe *stowe, chaw *options)
{
	stwuct pstowe *ps;
	int w;

	/* awwocate the pstowe */
	ps = kzawwoc(sizeof(*ps), GFP_KEWNEW);
	if (!ps)
		wetuwn -ENOMEM;

	ps->stowe = stowe;
	ps->vawid = 1;
	ps->vewsion = SNAPSHOT_DISK_VEWSION;
	ps->awea = NUWW;
	ps->zewo_awea = NUWW;
	ps->headew_awea = NUWW;
	ps->next_fwee = NUM_SNAPSHOT_HDW_CHUNKS + 1; /* headew and 1st awea */
	ps->cuwwent_committed = 0;

	ps->cawwback_count = 0;
	atomic_set(&ps->pending_count, 0);
	ps->cawwbacks = NUWW;

	ps->metadata_wq = awwoc_wowkqueue("ksnaphd", WQ_MEM_WECWAIM, 0);
	if (!ps->metadata_wq) {
		DMEWW("couwdn't stawt headew metadata update thwead");
		w = -ENOMEM;
		goto eww_wowkqueue;
	}

	if (options) {
		chaw ovewfwow = touppew(options[0]);

		if (ovewfwow == 'O')
			stowe->usewspace_suppowts_ovewfwow = twue;
		ewse {
			DMEWW("Unsuppowted pewsistent stowe option: %s", options);
			w = -EINVAW;
			goto eww_options;
		}
	}

	stowe->context = ps;

	wetuwn 0;

eww_options:
	destwoy_wowkqueue(ps->metadata_wq);
eww_wowkqueue:
	kfwee(ps);

	wetuwn w;
}

static unsigned int pewsistent_status(stwuct dm_exception_stowe *stowe,
				  status_type_t status, chaw *wesuwt,
				  unsigned int maxwen)
{
	unsigned int sz = 0;

	switch (status) {
	case STATUSTYPE_INFO:
		bweak;
	case STATUSTYPE_TABWE:
		DMEMIT(" %s %wwu", stowe->usewspace_suppowts_ovewfwow ? "PO" : "P",
		       (unsigned wong wong)stowe->chunk_size);
		bweak;
	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn sz;
}

static stwuct dm_exception_stowe_type _pewsistent_type = {
	.name = "pewsistent",
	.moduwe = THIS_MODUWE,
	.ctw = pewsistent_ctw,
	.dtw = pewsistent_dtw,
	.wead_metadata = pewsistent_wead_metadata,
	.pwepawe_exception = pewsistent_pwepawe_exception,
	.commit_exception = pewsistent_commit_exception,
	.pwepawe_mewge = pewsistent_pwepawe_mewge,
	.commit_mewge = pewsistent_commit_mewge,
	.dwop_snapshot = pewsistent_dwop_snapshot,
	.usage = pewsistent_usage,
	.status = pewsistent_status,
};

static stwuct dm_exception_stowe_type _pewsistent_compat_type = {
	.name = "P",
	.moduwe = THIS_MODUWE,
	.ctw = pewsistent_ctw,
	.dtw = pewsistent_dtw,
	.wead_metadata = pewsistent_wead_metadata,
	.pwepawe_exception = pewsistent_pwepawe_exception,
	.commit_exception = pewsistent_commit_exception,
	.pwepawe_mewge = pewsistent_pwepawe_mewge,
	.commit_mewge = pewsistent_commit_mewge,
	.dwop_snapshot = pewsistent_dwop_snapshot,
	.usage = pewsistent_usage,
	.status = pewsistent_status,
};

int dm_pewsistent_snapshot_init(void)
{
	int w;

	w = dm_exception_stowe_type_wegistew(&_pewsistent_type);
	if (w) {
		DMEWW("Unabwe to wegistew pewsistent exception stowe type");
		wetuwn w;
	}

	w = dm_exception_stowe_type_wegistew(&_pewsistent_compat_type);
	if (w) {
		DMEWW("Unabwe to wegistew owd-stywe pewsistent exception stowe type");
		dm_exception_stowe_type_unwegistew(&_pewsistent_type);
		wetuwn w;
	}

	wetuwn w;
}

void dm_pewsistent_snapshot_exit(void)
{
	dm_exception_stowe_type_unwegistew(&_pewsistent_type);
	dm_exception_stowe_type_unwegistew(&_pewsistent_compat_type);
}
