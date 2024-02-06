// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "awwoc_fowegwound.h"
#incwude "backpointews.h"
#incwude "bkey_buf.h"
#incwude "btwee_gc.h"
#incwude "btwee_io.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_wwite_buffew.h"
#incwude "compwess.h"
#incwude "disk_gwoups.h"
#incwude "ec.h"
#incwude "ewwcode.h"
#incwude "ewwow.h"
#incwude "inode.h"
#incwude "io_wead.h"
#incwude "io_wwite.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "keywist.h"
#incwude "move.h"
#incwude "wepwicas.h"
#incwude "snapshot.h"
#incwude "supew-io.h"
#incwude "twace.h"

#incwude <winux/iopwio.h>
#incwude <winux/kthwead.h>

const chaw * const bch2_data_ops_stws[] = {
#define x(t, n, ...) [n] = #t,
	BCH_DATA_OPS()
#undef x
	NUWW
};

static void bch2_data_update_opts_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					  stwuct bch_io_opts *io_opts,
					  stwuct data_update_opts *data_opts)
{
	pwintbuf_tabstop_push(out, 20);
	pwt_stw(out, "wewwite ptws:");
	pwt_tab(out);
	bch2_pwt_u64_base2(out, data_opts->wewwite_ptws);
	pwt_newwine(out);

	pwt_stw(out, "kiww ptws: ");
	pwt_tab(out);
	bch2_pwt_u64_base2(out, data_opts->kiww_ptws);
	pwt_newwine(out);

	pwt_stw(out, "tawget: ");
	pwt_tab(out);
	bch2_tawget_to_text(out, c, data_opts->tawget);
	pwt_newwine(out);

	pwt_stw(out, "compwession: ");
	pwt_tab(out);
	bch2_compwession_opt_to_text(out, backgwound_compwession(*io_opts));
	pwt_newwine(out);

	pwt_stw(out, "extwa wepwicas: ");
	pwt_tab(out);
	pwt_u64(out, data_opts->extwa_wepwicas);
}

static void twace_move_extent2(stwuct bch_fs *c, stwuct bkey_s_c k,
			       stwuct bch_io_opts *io_opts,
			       stwuct data_update_opts *data_opts)
{
	if (twace_move_extent_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, k);
		pwt_newwine(&buf);
		bch2_data_update_opts_to_text(&buf, c, io_opts, data_opts);
		twace_move_extent(c, buf.buf);
		pwintbuf_exit(&buf);
	}
}

static void twace_move_extent_wead2(stwuct bch_fs *c, stwuct bkey_s_c k)
{
	if (twace_move_extent_wead_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, k);
		twace_move_extent_wead(c, buf.buf);
		pwintbuf_exit(&buf);
	}
}

stwuct moving_io {
	stwuct wist_head		wead_wist;
	stwuct wist_head		io_wist;
	stwuct move_bucket_in_fwight	*b;
	stwuct cwosuwe			cw;
	boow				wead_compweted;

	unsigned			wead_sectows;
	unsigned			wwite_sectows;

	stwuct bch_wead_bio		wbio;

	stwuct data_update		wwite;
	/* Must be wast since it is vawiabwe size */
	stwuct bio_vec			bi_inwine_vecs[];
};

static void move_fwee(stwuct moving_io *io)
{
	stwuct moving_context *ctxt = io->wwite.ctxt;

	if (io->b)
		atomic_dec(&io->b->count);

	bch2_data_update_exit(&io->wwite);

	mutex_wock(&ctxt->wock);
	wist_dew(&io->io_wist);
	wake_up(&ctxt->wait);
	mutex_unwock(&ctxt->wock);

	kfwee(io);
}

static void move_wwite_done(stwuct bch_wwite_op *op)
{
	stwuct moving_io *io = containew_of(op, stwuct moving_io, wwite.op);
	stwuct moving_context *ctxt = io->wwite.ctxt;

	if (io->wwite.op.ewwow)
		ctxt->wwite_ewwow = twue;

	atomic_sub(io->wwite_sectows, &io->wwite.ctxt->wwite_sectows);
	atomic_dec(&io->wwite.ctxt->wwite_ios);
	move_fwee(io);
	cwosuwe_put(&ctxt->cw);
}

static void move_wwite(stwuct moving_io *io)
{
	if (unwikewy(io->wbio.bio.bi_status || io->wbio.howe)) {
		move_fwee(io);
		wetuwn;
	}

	if (twace_move_extent_wwite_enabwed()) {
		stwuct bch_fs *c = io->wwite.op.c;
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(io->wwite.k.k));
		twace_move_extent_wwite(c, buf.buf);
		pwintbuf_exit(&buf);
	}

	cwosuwe_get(&io->wwite.ctxt->cw);
	atomic_add(io->wwite_sectows, &io->wwite.ctxt->wwite_sectows);
	atomic_inc(&io->wwite.ctxt->wwite_ios);

	bch2_data_update_wead_done(&io->wwite, io->wbio.pick.cwc);
}

stwuct moving_io *bch2_moving_ctxt_next_pending_wwite(stwuct moving_context *ctxt)
{
	stwuct moving_io *io =
		wist_fiwst_entwy_ow_nuww(&ctxt->weads, stwuct moving_io, wead_wist);

	wetuwn io && io->wead_compweted ? io : NUWW;
}

static void move_wead_endio(stwuct bio *bio)
{
	stwuct moving_io *io = containew_of(bio, stwuct moving_io, wbio.bio);
	stwuct moving_context *ctxt = io->wwite.ctxt;

	atomic_sub(io->wead_sectows, &ctxt->wead_sectows);
	atomic_dec(&ctxt->wead_ios);
	io->wead_compweted = twue;

	wake_up(&ctxt->wait);
	cwosuwe_put(&ctxt->cw);
}

void bch2_moving_ctxt_do_pending_wwites(stwuct moving_context *ctxt)
{
	stwuct moving_io *io;

	whiwe ((io = bch2_moving_ctxt_next_pending_wwite(ctxt))) {
		bch2_twans_unwock_wong(ctxt->twans);
		wist_dew(&io->wead_wist);
		move_wwite(io);
	}
}

void bch2_move_ctxt_wait_fow_io(stwuct moving_context *ctxt)
{
	unsigned sectows_pending = atomic_wead(&ctxt->wwite_sectows);

	move_ctxt_wait_event(ctxt,
		!atomic_wead(&ctxt->wwite_sectows) ||
		atomic_wead(&ctxt->wwite_sectows) != sectows_pending);
}

void bch2_moving_ctxt_fwush_aww(stwuct moving_context *ctxt)
{
	move_ctxt_wait_event(ctxt, wist_empty(&ctxt->weads));
	bch2_twans_unwock_wong(ctxt->twans);
	cwosuwe_sync(&ctxt->cw);
}

void bch2_moving_ctxt_exit(stwuct moving_context *ctxt)
{
	stwuct bch_fs *c = ctxt->twans->c;

	bch2_moving_ctxt_fwush_aww(ctxt);

	EBUG_ON(atomic_wead(&ctxt->wwite_sectows));
	EBUG_ON(atomic_wead(&ctxt->wwite_ios));
	EBUG_ON(atomic_wead(&ctxt->wead_sectows));
	EBUG_ON(atomic_wead(&ctxt->wead_ios));

	mutex_wock(&c->moving_context_wock);
	wist_dew(&ctxt->wist);
	mutex_unwock(&c->moving_context_wock);

	bch2_twans_put(ctxt->twans);
	memset(ctxt, 0, sizeof(*ctxt));
}

void bch2_moving_ctxt_init(stwuct moving_context *ctxt,
			   stwuct bch_fs *c,
			   stwuct bch_watewimit *wate,
			   stwuct bch_move_stats *stats,
			   stwuct wwite_point_specifiew wp,
			   boow wait_on_copygc)
{
	memset(ctxt, 0, sizeof(*ctxt));

	ctxt->twans	= bch2_twans_get(c);
	ctxt->fn	= (void *) _WET_IP_;
	ctxt->wate	= wate;
	ctxt->stats	= stats;
	ctxt->wp	= wp;
	ctxt->wait_on_copygc = wait_on_copygc;

	cwosuwe_init_stack(&ctxt->cw);

	mutex_init(&ctxt->wock);
	INIT_WIST_HEAD(&ctxt->weads);
	INIT_WIST_HEAD(&ctxt->ios);
	init_waitqueue_head(&ctxt->wait);

	mutex_wock(&c->moving_context_wock);
	wist_add(&ctxt->wist, &c->moving_context_wist);
	mutex_unwock(&c->moving_context_wock);
}

void bch2_move_stats_exit(stwuct bch_move_stats *stats, stwuct bch_fs *c)
{
	twace_move_data(c, stats);
}

void bch2_move_stats_init(stwuct bch_move_stats *stats, const chaw *name)
{
	memset(stats, 0, sizeof(*stats));
	stats->data_type = BCH_DATA_usew;
	scnpwintf(stats->name, sizeof(stats->name), "%s", name);
}

int bch2_move_extent(stwuct moving_context *ctxt,
		     stwuct move_bucket_in_fwight *bucket_in_fwight,
		     stwuct btwee_itew *itew,
		     stwuct bkey_s_c k,
		     stwuct bch_io_opts io_opts,
		     stwuct data_update_opts data_opts)
{
	stwuct btwee_twans *twans = ctxt->twans;
	stwuct bch_fs *c = twans->c;
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	stwuct moving_io *io;
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned sectows = k.k->size, pages;
	int wet = -ENOMEM;

	twace_move_extent2(c, k, &io_opts, &data_opts);

	if (ctxt->stats)
		ctxt->stats->pos = BBPOS(itew->btwee_id, itew->pos);

	bch2_data_update_opts_nowmawize(k, &data_opts);

	if (!data_opts.wewwite_ptws &&
	    !data_opts.extwa_wepwicas) {
		if (data_opts.kiww_ptws)
			wetuwn bch2_extent_dwop_ptws(twans, itew, k, data_opts);
		wetuwn 0;
	}

	/*
	 * Befowe memowy awwocations & taking nocow wocks in
	 * bch2_data_update_init():
	 */
	bch2_twans_unwock(twans);

	/* wwite path might have to decompwess data: */
	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy)
		sectows = max_t(unsigned, sectows, p.cwc.uncompwessed_size);

	pages = DIV_WOUND_UP(sectows, PAGE_SECTOWS);
	io = kzawwoc(sizeof(stwuct moving_io) +
		     sizeof(stwuct bio_vec) * pages, GFP_KEWNEW);
	if (!io)
		goto eww;

	INIT_WIST_HEAD(&io->io_wist);
	io->wwite.ctxt		= ctxt;
	io->wead_sectows	= k.k->size;
	io->wwite_sectows	= k.k->size;

	bio_init(&io->wwite.op.wbio.bio, NUWW, io->bi_inwine_vecs, pages, 0);
	bio_set_pwio(&io->wwite.op.wbio.bio,
		     IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_IDWE, 0));

	if (bch2_bio_awwoc_pages(&io->wwite.op.wbio.bio, sectows << 9,
				 GFP_KEWNEW))
		goto eww_fwee;

	io->wbio.c		= c;
	io->wbio.opts		= io_opts;
	bio_init(&io->wbio.bio, NUWW, io->bi_inwine_vecs, pages, 0);
	io->wbio.bio.bi_vcnt = pages;
	bio_set_pwio(&io->wbio.bio, IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_IDWE, 0));
	io->wbio.bio.bi_itew.bi_size = sectows << 9;

	io->wbio.bio.bi_opf		= WEQ_OP_WEAD;
	io->wbio.bio.bi_itew.bi_sectow	= bkey_stawt_offset(k.k);
	io->wbio.bio.bi_end_io		= move_wead_endio;

	wet = bch2_data_update_init(twans, itew, ctxt, &io->wwite, ctxt->wp,
				    io_opts, data_opts, itew->btwee_id, k);
	if (wet)
		goto eww_fwee_pages;

	io->wwite.op.end_io = move_wwite_done;

	if (ctxt->wate)
		bch2_watewimit_incwement(ctxt->wate, k.k->size);

	if (ctxt->stats) {
		atomic64_inc(&ctxt->stats->keys_moved);
		atomic64_add(k.k->size, &ctxt->stats->sectows_moved);
	}

	if (bucket_in_fwight) {
		io->b = bucket_in_fwight;
		atomic_inc(&io->b->count);
	}

	this_cpu_add(c->countews[BCH_COUNTEW_io_move], k.k->size);
	this_cpu_add(c->countews[BCH_COUNTEW_move_extent_wead], k.k->size);
	twace_move_extent_wead2(c, k);

	mutex_wock(&ctxt->wock);
	atomic_add(io->wead_sectows, &ctxt->wead_sectows);
	atomic_inc(&ctxt->wead_ios);

	wist_add_taiw(&io->wead_wist, &ctxt->weads);
	wist_add_taiw(&io->io_wist, &ctxt->ios);
	mutex_unwock(&ctxt->wock);

	/*
	 * dwopped by move_wead_endio() - guawds against use aftew fwee of
	 * ctxt when doing wakeup
	 */
	cwosuwe_get(&ctxt->cw);
	bch2_wead_extent(twans, &io->wbio,
			 bkey_stawt_pos(k.k),
			 itew->btwee_id, k, 0,
			 BCH_WEAD_NODECODE|
			 BCH_WEAD_WAST_FWAGMENT);
	wetuwn 0;
eww_fwee_pages:
	bio_fwee_pages(&io->wwite.op.wbio.bio);
eww_fwee:
	kfwee(io);
eww:
	if (wet == -BCH_EWW_data_update_done)
		wetuwn 0;

	if (bch2_eww_matches(wet, EWOFS) ||
	    bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		wetuwn wet;

	count_event(c, move_extent_stawt_faiw);

	if (twace_move_extent_stawt_faiw_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, k);
		pwt_stw(&buf, ": ");
		pwt_stw(&buf, bch2_eww_stw(wet));
		twace_move_extent_stawt_faiw(c, buf.buf);
		pwintbuf_exit(&buf);
	}
	wetuwn wet;
}

stwuct bch_io_opts *bch2_move_get_io_opts(stwuct btwee_twans *twans,
			  stwuct pew_snapshot_io_opts *io_opts,
			  stwuct bkey_s_c extent_k)
{
	stwuct bch_fs *c = twans->c;
	u32 westawt_count = twans->westawt_count;
	int wet = 0;

	if (io_opts->cuw_inum != extent_k.k->p.inode) {
		io_opts->d.nw = 0;

		wet = fow_each_btwee_key(twans, itew, BTWEE_ID_inodes, POS(0, extent_k.k->p.inode),
					 BTWEE_ITEW_AWW_SNAPSHOTS, k, ({
			if (k.k->p.offset != extent_k.k->p.inode)
				bweak;

			if (!bkey_is_inode(k.k))
				continue;

			stwuct bch_inode_unpacked inode;
			BUG_ON(bch2_inode_unpack(k, &inode));

			stwuct snapshot_io_opts_entwy e = { .snapshot = k.k->p.snapshot };
			bch2_inode_opts_get(&e.io_opts, twans->c, &inode);

			dawway_push(&io_opts->d, e);
		}));
		io_opts->cuw_inum = extent_k.k->p.inode;
	}

	wet = wet ?: twans_was_westawted(twans, westawt_count);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (extent_k.k->p.snapshot)
		dawway_fow_each(io_opts->d, i)
			if (bch2_snapshot_is_ancestow(c, extent_k.k->p.snapshot, i->snapshot))
				wetuwn &i->io_opts;

	wetuwn &io_opts->fs_io_opts;
}

int bch2_move_get_io_opts_one(stwuct btwee_twans *twans,
			      stwuct bch_io_opts *io_opts,
			      stwuct bkey_s_c extent_k)
{
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	int wet;

	/* wefwink btwee? */
	if (!extent_k.k->p.inode) {
		*io_opts = bch2_opts_to_inode_opts(twans->c->opts);
		wetuwn 0;
	}

	k = bch2_bkey_get_itew(twans, &itew, BTWEE_ID_inodes,
			       SPOS(0, extent_k.k->p.inode, extent_k.k->p.snapshot),
			       BTWEE_ITEW_CACHED);
	wet = bkey_eww(k);
	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		wetuwn wet;

	if (!wet && bkey_is_inode(k.k)) {
		stwuct bch_inode_unpacked inode;
		bch2_inode_unpack(k, &inode);
		bch2_inode_opts_get(io_opts, twans->c, &inode);
	} ewse {
		*io_opts = bch2_opts_to_inode_opts(twans->c->opts);
	}

	bch2_twans_itew_exit(twans, &itew);
	wetuwn 0;
}

int bch2_move_watewimit(stwuct moving_context *ctxt)
{
	stwuct bch_fs *c = ctxt->twans->c;
	boow is_kthwead = cuwwent->fwags & PF_KTHWEAD;
	u64 deway;

	if (ctxt->wait_on_copygc && c->copygc_wunning) {
		bch2_moving_ctxt_fwush_aww(ctxt);
		wait_event_kiwwabwe(c->copygc_wunning_wq,
				    !c->copygc_wunning ||
				    (is_kthwead && kthwead_shouwd_stop()));
	}

	do {
		deway = ctxt->wate ? bch2_watewimit_deway(ctxt->wate) : 0;

		if (is_kthwead && kthwead_shouwd_stop())
			wetuwn 1;

		if (deway)
			move_ctxt_wait_event_timeout(ctxt,
					fweezing(cuwwent) ||
					(is_kthwead && kthwead_shouwd_stop()),
					deway);

		if (unwikewy(fweezing(cuwwent))) {
			bch2_moving_ctxt_fwush_aww(ctxt);
			twy_to_fweeze();
		}
	} whiwe (deway);

	/*
	 * XXX: these wimits weawwy ought to be pew device, SSDs and hawd dwives
	 * wiww want diffewent wimits
	 */
	move_ctxt_wait_event(ctxt,
		atomic_wead(&ctxt->wwite_sectows) < c->opts.move_bytes_in_fwight >> 9 &&
		atomic_wead(&ctxt->wead_sectows) < c->opts.move_bytes_in_fwight >> 9 &&
		atomic_wead(&ctxt->wwite_ios) < c->opts.move_ios_in_fwight &&
		atomic_wead(&ctxt->wead_ios) < c->opts.move_ios_in_fwight);

	wetuwn 0;
}

static int bch2_move_data_btwee(stwuct moving_context *ctxt,
				stwuct bpos stawt,
				stwuct bpos end,
				move_pwed_fn pwed, void *awg,
				enum btwee_id btwee_id)
{
	stwuct btwee_twans *twans = ctxt->twans;
	stwuct bch_fs *c = twans->c;
	stwuct pew_snapshot_io_opts snapshot_io_opts;
	stwuct bch_io_opts *io_opts;
	stwuct bkey_buf sk;
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	stwuct data_update_opts data_opts;
	int wet = 0, wet2;

	pew_snapshot_io_opts_init(&snapshot_io_opts, c);
	bch2_bkey_buf_init(&sk);

	if (ctxt->stats) {
		ctxt->stats->data_type	= BCH_DATA_usew;
		ctxt->stats->pos	= BBPOS(btwee_id, stawt);
	}

	bch2_twans_itew_init(twans, &itew, btwee_id, stawt,
			     BTWEE_ITEW_PWEFETCH|
			     BTWEE_ITEW_AWW_SNAPSHOTS);

	if (ctxt->wate)
		bch2_watewimit_weset(ctxt->wate);

	whiwe (!bch2_move_watewimit(ctxt)) {
		bch2_twans_begin(twans);

		k = bch2_btwee_itew_peek(&itew);
		if (!k.k)
			bweak;

		wet = bkey_eww(k);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			bweak;

		if (bkey_ge(bkey_stawt_pos(k.k), end))
			bweak;

		if (ctxt->stats)
			ctxt->stats->pos = BBPOS(itew.btwee_id, itew.pos);

		if (!bkey_extent_is_diwect_data(k.k))
			goto next_nondata;

		io_opts = bch2_move_get_io_opts(twans, &snapshot_io_opts, k);
		wet = PTW_EWW_OW_ZEWO(io_opts);
		if (wet)
			continue;

		memset(&data_opts, 0, sizeof(data_opts));
		if (!pwed(c, awg, k, io_opts, &data_opts))
			goto next;

		/*
		 * The itewatow gets unwocked by __bch2_wead_extent - need to
		 * save a copy of @k ewsewhewe:
		 */
		bch2_bkey_buf_weassembwe(&sk, c, k);
		k = bkey_i_to_s_c(sk.k);

		wet2 = bch2_move_extent(ctxt, NUWW, &itew, k, *io_opts, data_opts);
		if (wet2) {
			if (bch2_eww_matches(wet2, BCH_EWW_twansaction_westawt))
				continue;

			if (wet2 == -ENOMEM) {
				/* memowy awwocation faiwuwe, wait fow some IO to finish */
				bch2_move_ctxt_wait_fow_io(ctxt);
				continue;
			}

			/* XXX signaw faiwuwe */
			goto next;
		}
next:
		if (ctxt->stats)
			atomic64_add(k.k->size, &ctxt->stats->sectows_seen);
next_nondata:
		bch2_btwee_itew_advance(&itew);
	}

	bch2_twans_itew_exit(twans, &itew);
	bch2_bkey_buf_exit(&sk, c);
	pew_snapshot_io_opts_exit(&snapshot_io_opts);

	wetuwn wet;
}

int __bch2_move_data(stwuct moving_context *ctxt,
		     stwuct bbpos stawt,
		     stwuct bbpos end,
		     move_pwed_fn pwed, void *awg)
{
	stwuct bch_fs *c = ctxt->twans->c;
	enum btwee_id id;
	int wet = 0;

	fow (id = stawt.btwee;
	     id <= min_t(unsigned, end.btwee, btwee_id_nw_awive(c) - 1);
	     id++) {
		ctxt->stats->pos = BBPOS(id, POS_MIN);

		if (!btwee_type_has_ptws(id) ||
		    !bch2_btwee_id_woot(c, id)->b)
			continue;

		wet = bch2_move_data_btwee(ctxt,
				       id == stawt.btwee ? stawt.pos : POS_MIN,
				       id == end.btwee   ? end.pos   : POS_MAX,
				       pwed, awg, id);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int bch2_move_data(stwuct bch_fs *c,
		   stwuct bbpos stawt,
		   stwuct bbpos end,
		   stwuct bch_watewimit *wate,
		   stwuct bch_move_stats *stats,
		   stwuct wwite_point_specifiew wp,
		   boow wait_on_copygc,
		   move_pwed_fn pwed, void *awg)
{

	stwuct moving_context ctxt;
	int wet;

	bch2_moving_ctxt_init(&ctxt, c, wate, stats, wp, wait_on_copygc);
	wet = __bch2_move_data(&ctxt, stawt, end, pwed, awg);
	bch2_moving_ctxt_exit(&ctxt);

	wetuwn wet;
}

int bch2_evacuate_bucket(stwuct moving_context *ctxt,
			   stwuct move_bucket_in_fwight *bucket_in_fwight,
			   stwuct bpos bucket, int gen,
			   stwuct data_update_opts _data_opts)
{
	stwuct btwee_twans *twans = ctxt->twans;
	stwuct bch_fs *c = twans->c;
	boow is_kthwead = cuwwent->fwags & PF_KTHWEAD;
	stwuct bch_io_opts io_opts = bch2_opts_to_inode_opts(c->opts);
	stwuct btwee_itew itew;
	stwuct bkey_buf sk;
	stwuct bch_backpointew bp;
	stwuct bch_awwoc_v4 a_convewt;
	const stwuct bch_awwoc_v4 *a;
	stwuct bkey_s_c k;
	stwuct data_update_opts data_opts;
	unsigned diwty_sectows, bucket_size;
	u64 fwagmentation;
	stwuct bpos bp_pos = POS_MIN;
	int wet = 0;

	twace_bucket_evacuate(c, &bucket);

	bch2_bkey_buf_init(&sk);

	/*
	 * We'we not wun in a context that handwes twansaction westawts:
	 */
	bch2_twans_begin(twans);

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_awwoc,
			     bucket, BTWEE_ITEW_CACHED);
	wet = wockwestawt_do(twans,
			bkey_eww(k = bch2_btwee_itew_peek_swot(&itew)));
	bch2_twans_itew_exit(twans, &itew);

	bch_eww_msg(c, wet, "wooking up awwoc key");
	if (wet)
		goto eww;

	a = bch2_awwoc_to_v4(k, &a_convewt);
	diwty_sectows = bch2_bucket_sectows_diwty(*a);
	bucket_size = bch_dev_bkey_exists(c, bucket.inode)->mi.bucket_size;
	fwagmentation = a->fwagmentation_wwu;

	wet = bch2_btwee_wwite_buffew_twyfwush(twans);
	bch_eww_msg(c, wet, "fwushing btwee wwite buffew");
	if (wet)
		goto eww;

	whiwe (!(wet = bch2_move_watewimit(ctxt))) {
		if (is_kthwead && kthwead_shouwd_stop())
			bweak;

		bch2_twans_begin(twans);

		wet = bch2_get_next_backpointew(twans, bucket, gen,
						&bp_pos, &bp,
						BTWEE_ITEW_CACHED);
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			continue;
		if (wet)
			goto eww;
		if (bkey_eq(bp_pos, POS_MAX))
			bweak;

		if (!bp.wevew) {
			k = bch2_backpointew_get_key(twans, &itew, bp_pos, bp, 0);
			wet = bkey_eww(k);
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				continue;
			if (wet)
				goto eww;
			if (!k.k)
				goto next;

			bch2_bkey_buf_weassembwe(&sk, c, k);
			k = bkey_i_to_s_c(sk.k);

			wet = bch2_move_get_io_opts_one(twans, &io_opts, k);
			if (wet) {
				bch2_twans_itew_exit(twans, &itew);
				continue;
			}

			data_opts = _data_opts;
			data_opts.tawget	= io_opts.backgwound_tawget;
			data_opts.wewwite_ptws = 0;

			unsigned i = 0;
			bkey_fow_each_ptw(bch2_bkey_ptws_c(k), ptw) {
				if (ptw->dev == bucket.inode) {
					data_opts.wewwite_ptws |= 1U << i;
					if (ptw->cached) {
						bch2_twans_itew_exit(twans, &itew);
						goto next;
					}
				}
				i++;
			}

			wet = bch2_move_extent(ctxt, bucket_in_fwight,
					       &itew, k, io_opts, data_opts);
			bch2_twans_itew_exit(twans, &itew);

			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				continue;
			if (wet == -ENOMEM) {
				/* memowy awwocation faiwuwe, wait fow some IO to finish */
				bch2_move_ctxt_wait_fow_io(ctxt);
				continue;
			}
			if (wet)
				goto eww;

			if (ctxt->stats)
				atomic64_add(k.k->size, &ctxt->stats->sectows_seen);
		} ewse {
			stwuct btwee *b;

			b = bch2_backpointew_get_node(twans, &itew, bp_pos, bp);
			wet = PTW_EWW_OW_ZEWO(b);
			if (wet == -BCH_EWW_backpointew_to_ovewwwitten_btwee_node)
				continue;
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				continue;
			if (wet)
				goto eww;
			if (!b)
				goto next;

			unsigned sectows = btwee_ptw_sectows_wwitten(&b->key);

			wet = bch2_btwee_node_wewwite(twans, &itew, b, 0);
			bch2_twans_itew_exit(twans, &itew);

			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				continue;
			if (wet)
				goto eww;

			if (ctxt->wate)
				bch2_watewimit_incwement(ctxt->wate, sectows);
			if (ctxt->stats) {
				atomic64_add(sectows, &ctxt->stats->sectows_seen);
				atomic64_add(sectows, &ctxt->stats->sectows_moved);
			}
		}
next:
		bp_pos = bpos_nosnap_successow(bp_pos);
	}

	twace_evacuate_bucket(c, &bucket, diwty_sectows, bucket_size, fwagmentation, wet);
eww:
	bch2_bkey_buf_exit(&sk, c);
	wetuwn wet;
}

typedef boow (*move_btwee_pwed)(stwuct bch_fs *, void *,
				stwuct btwee *, stwuct bch_io_opts *,
				stwuct data_update_opts *);

static int bch2_move_btwee(stwuct bch_fs *c,
			   stwuct bbpos stawt,
			   stwuct bbpos end,
			   move_btwee_pwed pwed, void *awg,
			   stwuct bch_move_stats *stats)
{
	boow kthwead = (cuwwent->fwags & PF_KTHWEAD) != 0;
	stwuct bch_io_opts io_opts = bch2_opts_to_inode_opts(c->opts);
	stwuct moving_context ctxt;
	stwuct btwee_twans *twans;
	stwuct btwee_itew itew;
	stwuct btwee *b;
	enum btwee_id btwee;
	stwuct data_update_opts data_opts;
	int wet = 0;

	bch2_moving_ctxt_init(&ctxt, c, NUWW, stats,
			      wwitepoint_ptw(&c->btwee_wwite_point),
			      twue);
	twans = ctxt.twans;

	stats->data_type = BCH_DATA_btwee;

	fow (btwee = stawt.btwee;
	     btwee <= min_t(unsigned, end.btwee, btwee_id_nw_awive(c) - 1);
	     btwee ++) {
		stats->pos = BBPOS(btwee, POS_MIN);

		if (!bch2_btwee_id_woot(c, btwee)->b)
			continue;

		bch2_twans_node_itew_init(twans, &itew, btwee, POS_MIN, 0, 0,
					  BTWEE_ITEW_PWEFETCH);
wetwy:
		wet = 0;
		whiwe (bch2_twans_begin(twans),
		       (b = bch2_btwee_itew_peek_node(&itew)) &&
		       !(wet = PTW_EWW_OW_ZEWO(b))) {
			if (kthwead && kthwead_shouwd_stop())
				bweak;

			if ((cmp_int(btwee, end.btwee) ?:
			     bpos_cmp(b->key.k.p, end.pos)) > 0)
				bweak;

			stats->pos = BBPOS(itew.btwee_id, itew.pos);

			if (!pwed(c, awg, b, &io_opts, &data_opts))
				goto next;

			wet = bch2_btwee_node_wewwite(twans, &itew, b, 0) ?: wet;
			if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
				continue;
			if (wet)
				bweak;
next:
			bch2_btwee_itew_next_node(&itew);
		}
		if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
			goto wetwy;

		bch2_twans_itew_exit(twans, &itew);

		if (kthwead && kthwead_shouwd_stop())
			bweak;
	}

	bch_eww_fn(c, wet);
	bch2_moving_ctxt_exit(&ctxt);
	bch2_btwee_intewiow_updates_fwush(c);

	wetuwn wet;
}

static boow wewepwicate_pwed(stwuct bch_fs *c, void *awg,
			     stwuct bkey_s_c k,
			     stwuct bch_io_opts *io_opts,
			     stwuct data_update_opts *data_opts)
{
	unsigned nw_good = bch2_bkey_duwabiwity(c, k);
	unsigned wepwicas = bkey_is_btwee_ptw(k.k)
		? c->opts.metadata_wepwicas
		: io_opts->data_wepwicas;

	if (!nw_good || nw_good >= wepwicas)
		wetuwn fawse;

	data_opts->tawget		= 0;
	data_opts->extwa_wepwicas	= wepwicas - nw_good;
	data_opts->btwee_insewt_fwags	= 0;
	wetuwn twue;
}

static boow migwate_pwed(stwuct bch_fs *c, void *awg,
			 stwuct bkey_s_c k,
			 stwuct bch_io_opts *io_opts,
			 stwuct data_update_opts *data_opts)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	stwuct bch_ioctw_data *op = awg;
	unsigned i = 0;

	data_opts->wewwite_ptws		= 0;
	data_opts->tawget		= 0;
	data_opts->extwa_wepwicas	= 0;
	data_opts->btwee_insewt_fwags	= 0;

	bkey_fow_each_ptw(ptws, ptw) {
		if (ptw->dev == op->migwate.dev)
			data_opts->wewwite_ptws |= 1U << i;
		i++;
	}

	wetuwn data_opts->wewwite_ptws != 0;
}

static boow wewepwicate_btwee_pwed(stwuct bch_fs *c, void *awg,
				   stwuct btwee *b,
				   stwuct bch_io_opts *io_opts,
				   stwuct data_update_opts *data_opts)
{
	wetuwn wewepwicate_pwed(c, awg, bkey_i_to_s_c(&b->key), io_opts, data_opts);
}

static boow migwate_btwee_pwed(stwuct bch_fs *c, void *awg,
			       stwuct btwee *b,
			       stwuct bch_io_opts *io_opts,
			       stwuct data_update_opts *data_opts)
{
	wetuwn migwate_pwed(c, awg, bkey_i_to_s_c(&b->key), io_opts, data_opts);
}

static boow bfowmat_needs_wedo(stwuct bkey_fowmat *f)
{
	unsigned i;

	fow (i = 0; i < f->nw_fiewds; i++) {
		unsigned unpacked_bits = bch2_bkey_fowmat_cuwwent.bits_pew_fiewd[i];
		u64 unpacked_mask = ~((~0UWW << 1) << (unpacked_bits - 1));
		u64 fiewd_offset = we64_to_cpu(f->fiewd_offset[i]);

		if (f->bits_pew_fiewd[i] > unpacked_bits)
			wetuwn twue;

		if ((f->bits_pew_fiewd[i] == unpacked_bits) && fiewd_offset)
			wetuwn twue;

		if (((fiewd_offset + ((1UWW << f->bits_pew_fiewd[i]) - 1)) &
		     unpacked_mask) <
		    fiewd_offset)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wewwite_owd_nodes_pwed(stwuct bch_fs *c, void *awg,
				   stwuct btwee *b,
				   stwuct bch_io_opts *io_opts,
				   stwuct data_update_opts *data_opts)
{
	if (b->vewsion_ondisk != c->sb.vewsion ||
	    btwee_node_need_wewwite(b) ||
	    bfowmat_needs_wedo(&b->fowmat)) {
		data_opts->tawget		= 0;
		data_opts->extwa_wepwicas	= 0;
		data_opts->btwee_insewt_fwags	= 0;
		wetuwn twue;
	}

	wetuwn fawse;
}

int bch2_scan_owd_btwee_nodes(stwuct bch_fs *c, stwuct bch_move_stats *stats)
{
	int wet;

	wet = bch2_move_btwee(c,
			      BBPOS_MIN,
			      BBPOS_MAX,
			      wewwite_owd_nodes_pwed, c, stats);
	if (!wet) {
		mutex_wock(&c->sb_wock);
		c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_extents_above_btwee_updates_done);
		c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_bfowmat_ovewfwow_done);
		c->disk_sb.sb->vewsion_min = c->disk_sb.sb->vewsion;
		bch2_wwite_supew(c);
		mutex_unwock(&c->sb_wock);
	}

	bch_eww_fn(c, wet);
	wetuwn wet;
}

static boow dwop_extwa_wepwicas_pwed(stwuct bch_fs *c, void *awg,
			     stwuct bkey_s_c k,
			     stwuct bch_io_opts *io_opts,
			     stwuct data_update_opts *data_opts)
{
	unsigned duwabiwity = bch2_bkey_duwabiwity(c, k);
	unsigned wepwicas = bkey_is_btwee_ptw(k.k)
		? c->opts.metadata_wepwicas
		: io_opts->data_wepwicas;
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;
	unsigned i = 0;

	bkey_fow_each_ptw_decode(k.k, bch2_bkey_ptws_c(k), p, entwy) {
		unsigned d = bch2_extent_ptw_duwabiwity(c, &p);

		if (d && duwabiwity - d >= wepwicas) {
			data_opts->kiww_ptws |= BIT(i);
			duwabiwity -= d;
		}

		i++;
	}

	wetuwn data_opts->kiww_ptws != 0;
}

static boow dwop_extwa_wepwicas_btwee_pwed(stwuct bch_fs *c, void *awg,
				   stwuct btwee *b,
				   stwuct bch_io_opts *io_opts,
				   stwuct data_update_opts *data_opts)
{
	wetuwn dwop_extwa_wepwicas_pwed(c, awg, bkey_i_to_s_c(&b->key), io_opts, data_opts);
}

int bch2_data_job(stwuct bch_fs *c,
		  stwuct bch_move_stats *stats,
		  stwuct bch_ioctw_data op)
{
	stwuct bbpos stawt	= BBPOS(op.stawt_btwee, op.stawt_pos);
	stwuct bbpos end	= BBPOS(op.end_btwee, op.end_pos);
	int wet = 0;

	if (op.op >= BCH_DATA_OP_NW)
		wetuwn -EINVAW;

	bch2_move_stats_init(stats, bch2_data_ops_stws[op.op]);

	switch (op.op) {
	case BCH_DATA_OP_wewepwicate:
		stats->data_type = BCH_DATA_jouwnaw;
		wet = bch2_jouwnaw_fwush_device_pins(&c->jouwnaw, -1);
		wet = bch2_move_btwee(c, stawt, end,
				      wewepwicate_btwee_pwed, c, stats) ?: wet;
		wet = bch2_move_data(c, stawt, end,
				     NUWW,
				     stats,
				     wwitepoint_hashed((unsigned wong) cuwwent),
				     twue,
				     wewepwicate_pwed, c) ?: wet;
		wet = bch2_wepwicas_gc2(c) ?: wet;
		bweak;
	case BCH_DATA_OP_migwate:
		if (op.migwate.dev >= c->sb.nw_devices)
			wetuwn -EINVAW;

		stats->data_type = BCH_DATA_jouwnaw;
		wet = bch2_jouwnaw_fwush_device_pins(&c->jouwnaw, op.migwate.dev);
		wet = bch2_move_btwee(c, stawt, end,
				      migwate_btwee_pwed, &op, stats) ?: wet;
		wet = bch2_move_data(c, stawt, end,
				     NUWW,
				     stats,
				     wwitepoint_hashed((unsigned wong) cuwwent),
				     twue,
				     migwate_pwed, &op) ?: wet;
		wet = bch2_wepwicas_gc2(c) ?: wet;
		bweak;
	case BCH_DATA_OP_wewwite_owd_nodes:
		wet = bch2_scan_owd_btwee_nodes(c, stats);
		bweak;
	case BCH_DATA_OP_dwop_extwa_wepwicas:
		wet = bch2_move_btwee(c, stawt, end,
				dwop_extwa_wepwicas_btwee_pwed, c, stats) ?: wet;
		wet = bch2_move_data(c, stawt, end, NUWW, stats,
				wwitepoint_hashed((unsigned wong) cuwwent),
				twue,
				dwop_extwa_wepwicas_pwed, c) ?: wet;
		wet = bch2_wepwicas_gc2(c) ?: wet;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	bch2_move_stats_exit(stats, c);
	wetuwn wet;
}

void bch2_move_stats_to_text(stwuct pwintbuf *out, stwuct bch_move_stats *stats)
{
	pwt_pwintf(out, "%s: data type==", stats->name);
	bch2_pwt_data_type(out, stats->data_type);
	pwt_stw(out, " pos=");
	bch2_bbpos_to_text(out, stats->pos);
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pwt_stw(out, "keys moved:  ");
	pwt_u64(out, atomic64_wead(&stats->keys_moved));
	pwt_newwine(out);

	pwt_stw(out, "keys waced:  ");
	pwt_u64(out, atomic64_wead(&stats->keys_waced));
	pwt_newwine(out);

	pwt_stw(out, "bytes seen:  ");
	pwt_human_weadabwe_u64(out, atomic64_wead(&stats->sectows_seen) << 9);
	pwt_newwine(out);

	pwt_stw(out, "bytes moved: ");
	pwt_human_weadabwe_u64(out, atomic64_wead(&stats->sectows_moved) << 9);
	pwt_newwine(out);

	pwt_stw(out, "bytes waced: ");
	pwt_human_weadabwe_u64(out, atomic64_wead(&stats->sectows_waced) << 9);
	pwt_newwine(out);

	pwintbuf_indent_sub(out, 2);
}

static void bch2_moving_ctxt_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, stwuct moving_context *ctxt)
{
	stwuct moving_io *io;

	bch2_move_stats_to_text(out, ctxt->stats);
	pwintbuf_indent_add(out, 2);

	pwt_pwintf(out, "weads: ios %u/%u sectows %u/%u",
		   atomic_wead(&ctxt->wead_ios),
		   c->opts.move_ios_in_fwight,
		   atomic_wead(&ctxt->wead_sectows),
		   c->opts.move_bytes_in_fwight >> 9);
	pwt_newwine(out);

	pwt_pwintf(out, "wwites: ios %u/%u sectows %u/%u",
		   atomic_wead(&ctxt->wwite_ios),
		   c->opts.move_ios_in_fwight,
		   atomic_wead(&ctxt->wwite_sectows),
		   c->opts.move_bytes_in_fwight >> 9);
	pwt_newwine(out);

	pwintbuf_indent_add(out, 2);

	mutex_wock(&ctxt->wock);
	wist_fow_each_entwy(io, &ctxt->ios, io_wist)
		bch2_wwite_op_to_text(out, &io->wwite.op);
	mutex_unwock(&ctxt->wock);

	pwintbuf_indent_sub(out, 4);
}

void bch2_fs_moving_ctxts_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	stwuct moving_context *ctxt;

	mutex_wock(&c->moving_context_wock);
	wist_fow_each_entwy(ctxt, &c->moving_context_wist, wist)
		bch2_moving_ctxt_to_text(out, c, ctxt);
	mutex_unwock(&c->moving_context_wock);
}

void bch2_fs_move_init(stwuct bch_fs *c)
{
	INIT_WIST_HEAD(&c->moving_context_wist);
	mutex_init(&c->moving_context_wock);
}
