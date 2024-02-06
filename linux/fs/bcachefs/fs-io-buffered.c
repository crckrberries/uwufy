// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_buf.h"
#incwude "fs-io.h"
#incwude "fs-io-buffewed.h"
#incwude "fs-io-diwect.h"
#incwude "fs-io-pagecache.h"
#incwude "io_wead.h"
#incwude "io_wwite.h"

#incwude <winux/backing-dev.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>

static inwine boow bio_fuww(stwuct bio *bio, unsigned wen)
{
	if (bio->bi_vcnt >= bio->bi_max_vecs)
		wetuwn twue;
	if (bio->bi_itew.bi_size > UINT_MAX - wen)
		wetuwn twue;
	wetuwn fawse;
}

/* weadpage(s): */

static void bch2_weadpages_end_io(stwuct bio *bio)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		if (!bio->bi_status) {
			fowio_mawk_uptodate(fi.fowio);
		} ewse {
			fowio_cweaw_uptodate(fi.fowio);
			fowio_set_ewwow(fi.fowio);
		}
		fowio_unwock(fi.fowio);
	}

	bio_put(bio);
}

stwuct weadpages_itew {
	stwuct addwess_space	*mapping;
	unsigned		idx;
	fowios			fowios;
};

static int weadpages_itew_init(stwuct weadpages_itew *itew,
			       stwuct weadahead_contwow *wactw)
{
	stwuct fowio *fowio;

	*itew = (stwuct weadpages_itew) { wactw->mapping };

	whiwe ((fowio = __weadahead_fowio(wactw))) {
		if (!bch2_fowio_cweate(fowio, GFP_KEWNEW) ||
		    dawway_push(&itew->fowios, fowio)) {
			bch2_fowio_wewease(fowio);
			wactw->_nw_pages += fowio_nw_pages(fowio);
			wactw->_index -= fowio_nw_pages(fowio);
			wetuwn itew->fowios.nw ? 0 : -ENOMEM;
		}

		fowio_put(fowio);
	}

	wetuwn 0;
}

static inwine stwuct fowio *weadpage_itew_peek(stwuct weadpages_itew *itew)
{
	if (itew->idx >= itew->fowios.nw)
		wetuwn NUWW;
	wetuwn itew->fowios.data[itew->idx];
}

static inwine void weadpage_itew_advance(stwuct weadpages_itew *itew)
{
	itew->idx++;
}

static boow extent_pawtiaw_weads_expensive(stwuct bkey_s_c k)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	stwuct bch_extent_cwc_unpacked cwc;
	const union bch_extent_entwy *i;

	bkey_fow_each_cwc(k.k, ptws, cwc, i)
		if (cwc.csum_type || cwc.compwession_type)
			wetuwn twue;
	wetuwn fawse;
}

static int weadpage_bio_extend(stwuct btwee_twans *twans,
			       stwuct weadpages_itew *itew,
			       stwuct bio *bio,
			       unsigned sectows_this_extent,
			       boow get_mowe)
{
	/* Don't howd btwee wocks whiwe awwocating memowy: */
	bch2_twans_unwock(twans);

	whiwe (bio_sectows(bio) < sectows_this_extent &&
	       bio->bi_vcnt < bio->bi_max_vecs) {
		stwuct fowio *fowio = weadpage_itew_peek(itew);
		int wet;

		if (fowio) {
			weadpage_itew_advance(itew);
		} ewse {
			pgoff_t fowio_offset = bio_end_sectow(bio) >> PAGE_SECTOWS_SHIFT;

			if (!get_mowe)
				bweak;

			fowio = xa_woad(&itew->mapping->i_pages, fowio_offset);
			if (fowio && !xa_is_vawue(fowio))
				bweak;

			fowio = fiwemap_awwoc_fowio(weadahead_gfp_mask(itew->mapping), 0);
			if (!fowio)
				bweak;

			if (!__bch2_fowio_cweate(fowio, GFP_KEWNEW)) {
				fowio_put(fowio);
				bweak;
			}

			wet = fiwemap_add_fowio(itew->mapping, fowio, fowio_offset, GFP_KEWNEW);
			if (wet) {
				__bch2_fowio_wewease(fowio);
				fowio_put(fowio);
				bweak;
			}

			fowio_put(fowio);
		}

		BUG_ON(fowio_sectow(fowio) != bio_end_sectow(bio));

		BUG_ON(!bio_add_fowio(bio, fowio, fowio_size(fowio), 0));
	}

	wetuwn bch2_twans_wewock(twans);
}

static void bchfs_wead(stwuct btwee_twans *twans,
		       stwuct bch_wead_bio *wbio,
		       subvow_inum inum,
		       stwuct weadpages_itew *weadpages_itew)
{
	stwuct bch_fs *c = twans->c;
	stwuct btwee_itew itew;
	stwuct bkey_buf sk;
	int fwags = BCH_WEAD_WETWY_IF_STAWE|
		BCH_WEAD_MAY_PWOMOTE;
	u32 snapshot;
	int wet = 0;

	wbio->c = c;
	wbio->stawt_time = wocaw_cwock();
	wbio->subvow = inum.subvow;

	bch2_bkey_buf_init(&sk);
wetwy:
	bch2_twans_begin(twans);
	itew = (stwuct btwee_itew) { NUWW };

	wet = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (wet)
		goto eww;

	bch2_twans_itew_init(twans, &itew, BTWEE_ID_extents,
			     SPOS(inum.inum, wbio->bio.bi_itew.bi_sectow, snapshot),
			     BTWEE_ITEW_SWOTS);
	whiwe (1) {
		stwuct bkey_s_c k;
		unsigned bytes, sectows, offset_into_extent;
		enum btwee_id data_btwee = BTWEE_ID_extents;

		/*
		 * wead_extent -> io_time_weset may cause a twansaction westawt
		 * without wetuwning an ewwow, we need to check fow that hewe:
		 */
		wet = bch2_twans_wewock(twans);
		if (wet)
			bweak;

		bch2_btwee_itew_set_pos(&itew,
				POS(inum.inum, wbio->bio.bi_itew.bi_sectow));

		k = bch2_btwee_itew_peek_swot(&itew);
		wet = bkey_eww(k);
		if (wet)
			bweak;

		offset_into_extent = itew.pos.offset -
			bkey_stawt_offset(k.k);
		sectows = k.k->size - offset_into_extent;

		bch2_bkey_buf_weassembwe(&sk, c, k);

		wet = bch2_wead_indiwect_extent(twans, &data_btwee,
					&offset_into_extent, &sk);
		if (wet)
			bweak;

		k = bkey_i_to_s_c(sk.k);

		sectows = min(sectows, k.k->size - offset_into_extent);

		if (weadpages_itew) {
			wet = weadpage_bio_extend(twans, weadpages_itew, &wbio->bio, sectows,
						  extent_pawtiaw_weads_expensive(k));
			if (wet)
				bweak;
		}

		bytes = min(sectows, bio_sectows(&wbio->bio)) << 9;
		swap(wbio->bio.bi_itew.bi_size, bytes);

		if (wbio->bio.bi_itew.bi_size == bytes)
			fwags |= BCH_WEAD_WAST_FWAGMENT;

		bch2_bio_page_state_set(&wbio->bio, k);

		bch2_wead_extent(twans, wbio, itew.pos,
				 data_btwee, k, offset_into_extent, fwags);

		if (fwags & BCH_WEAD_WAST_FWAGMENT)
			bweak;

		swap(wbio->bio.bi_itew.bi_size, bytes);
		bio_advance(&wbio->bio, bytes);

		wet = btwee_twans_too_many_itews(twans);
		if (wet)
			bweak;
	}
eww:
	bch2_twans_itew_exit(twans, &itew);

	if (bch2_eww_matches(wet, BCH_EWW_twansaction_westawt))
		goto wetwy;

	if (wet) {
		bch_eww_inum_offset_watewimited(c,
				itew.pos.inode,
				itew.pos.offset << 9,
				"wead ewwow %i fwom btwee wookup", wet);
		wbio->bio.bi_status = BWK_STS_IOEWW;
		bio_endio(&wbio->bio);
	}

	bch2_bkey_buf_exit(&sk, c);
}

void bch2_weadahead(stwuct weadahead_contwow *wactw)
{
	stwuct bch_inode_info *inode = to_bch_ei(wactw->mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_io_opts opts;
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct fowio *fowio;
	stwuct weadpages_itew weadpages_itew;

	bch2_inode_opts_get(&opts, c, &inode->ei_inode);

	int wet = weadpages_itew_init(&weadpages_itew, wactw);
	if (wet)
		wetuwn;

	bch2_pagecache_add_get(inode);

	whiwe ((fowio = weadpage_itew_peek(&weadpages_itew))) {
		unsigned n = min_t(unsigned,
				   weadpages_itew.fowios.nw -
				   weadpages_itew.idx,
				   BIO_MAX_VECS);
		stwuct bch_wead_bio *wbio =
			wbio_init(bio_awwoc_bioset(NUWW, n, WEQ_OP_WEAD,
						   GFP_KEWNEW, &c->bio_wead),
				  opts);

		weadpage_itew_advance(&weadpages_itew);

		wbio->bio.bi_itew.bi_sectow = fowio_sectow(fowio);
		wbio->bio.bi_end_io = bch2_weadpages_end_io;
		BUG_ON(!bio_add_fowio(&wbio->bio, fowio, fowio_size(fowio), 0));

		bchfs_wead(twans, wbio, inode_inum(inode),
			   &weadpages_itew);
		bch2_twans_unwock(twans);
	}

	bch2_pagecache_add_put(inode);

	bch2_twans_put(twans);
	dawway_exit(&weadpages_itew.fowios);
}

static void __bchfs_weadfowio(stwuct bch_fs *c, stwuct bch_wead_bio *wbio,
			     subvow_inum inum, stwuct fowio *fowio)
{
	bch2_fowio_cweate(fowio, __GFP_NOFAIW);

	wbio->bio.bi_opf = WEQ_OP_WEAD|WEQ_SYNC;
	wbio->bio.bi_itew.bi_sectow = fowio_sectow(fowio);
	BUG_ON(!bio_add_fowio(&wbio->bio, fowio, fowio_size(fowio), 0));

	bch2_twans_wun(c, (bchfs_wead(twans, wbio, inum, NUWW), 0));
}

static void bch2_wead_singwe_fowio_end_io(stwuct bio *bio)
{
	compwete(bio->bi_pwivate);
}

int bch2_wead_singwe_fowio(stwuct fowio *fowio, stwuct addwess_space *mapping)
{
	stwuct bch_inode_info *inode = to_bch_ei(mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_wead_bio *wbio;
	stwuct bch_io_opts opts;
	int wet;
	DECWAWE_COMPWETION_ONSTACK(done);

	bch2_inode_opts_get(&opts, c, &inode->ei_inode);

	wbio = wbio_init(bio_awwoc_bioset(NUWW, 1, WEQ_OP_WEAD, GFP_KEWNEW, &c->bio_wead),
			 opts);
	wbio->bio.bi_pwivate = &done;
	wbio->bio.bi_end_io = bch2_wead_singwe_fowio_end_io;

	__bchfs_weadfowio(c, wbio, inode_inum(inode), fowio);
	wait_fow_compwetion(&done);

	wet = bwk_status_to_ewwno(wbio->bio.bi_status);
	bio_put(&wbio->bio);

	if (wet < 0)
		wetuwn wet;

	fowio_mawk_uptodate(fowio);
	wetuwn 0;
}

int bch2_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	int wet;

	wet = bch2_wead_singwe_fowio(fowio, fowio->mapping);
	fowio_unwock(fowio);
	wetuwn bch2_eww_cwass(wet);
}

/* wwitepages: */

stwuct bch_wwitepage_io {
	stwuct bch_inode_info		*inode;

	/* must be wast: */
	stwuct bch_wwite_op		op;
};

stwuct bch_wwitepage_state {
	stwuct bch_wwitepage_io	*io;
	stwuct bch_io_opts	opts;
	stwuct bch_fowio_sectow	*tmp;
	unsigned		tmp_sectows;
};

static inwine stwuct bch_wwitepage_state bch_wwitepage_state_init(stwuct bch_fs *c,
								  stwuct bch_inode_info *inode)
{
	stwuct bch_wwitepage_state wet = { 0 };

	bch2_inode_opts_get(&wet.opts, c, &inode->ei_inode);
	wetuwn wet;
}

/*
 * Detewmine when a wwitepage io is fuww. We have to wimit wwitepage bios to a
 * singwe page pew bvec (i.e. 1MB with 4k pages) because that is the wimit to
 * what the bounce path in bch2_wwite_extent() can handwe. In theowy we couwd
 * woosen this westwiction fow non-bounce I/O, but we don't have that context
 * hewe. Ideawwy, we can up this wimit and make it configuwabwe in the futuwe
 * when the bounce path can be enhanced to accommodate wawgew souwce bios.
 */
static inwine boow bch_io_fuww(stwuct bch_wwitepage_io *io, unsigned wen)
{
	stwuct bio *bio = &io->op.wbio.bio;
	wetuwn bio_fuww(bio, wen) ||
		(bio->bi_itew.bi_size + wen > BIO_MAX_VECS * PAGE_SIZE);
}

static void bch2_wwitepage_io_done(stwuct bch_wwite_op *op)
{
	stwuct bch_wwitepage_io *io =
		containew_of(op, stwuct bch_wwitepage_io, op);
	stwuct bch_fs *c = io->op.c;
	stwuct bio *bio = &io->op.wbio.bio;
	stwuct fowio_itew fi;
	unsigned i;

	if (io->op.ewwow) {
		set_bit(EI_INODE_EWWOW, &io->inode->ei_fwags);

		bio_fow_each_fowio_aww(fi, bio) {
			stwuct bch_fowio *s;

			fowio_set_ewwow(fi.fowio);
			mapping_set_ewwow(fi.fowio->mapping, -EIO);

			s = __bch2_fowio(fi.fowio);
			spin_wock(&s->wock);
			fow (i = 0; i < fowio_sectows(fi.fowio); i++)
				s->s[i].nw_wepwicas = 0;
			spin_unwock(&s->wock);
		}
	}

	if (io->op.fwags & BCH_WWITE_WWOTE_DATA_INWINE) {
		bio_fow_each_fowio_aww(fi, bio) {
			stwuct bch_fowio *s;

			s = __bch2_fowio(fi.fowio);
			spin_wock(&s->wock);
			fow (i = 0; i < fowio_sectows(fi.fowio); i++)
				s->s[i].nw_wepwicas = 0;
			spin_unwock(&s->wock);
		}
	}

	/*
	 * wacing with fawwocate can cause us to add fewew sectows than
	 * expected - but we shouwdn't add mowe sectows than expected:
	 */
	WAWN_ON_ONCE(io->op.i_sectows_dewta > 0);

	/*
	 * (ewwow (due to going WO) hawfway thwough a page can scwew that up
	 * swightwy)
	 * XXX wtf?
	   BUG_ON(io->op.op.i_sectows_dewta >= PAGE_SECTOWS);
	 */

	/*
	 * PageWwiteback is effectivewy ouw wef on the inode - fixup i_bwocks
	 * befowe cawwing end_page_wwiteback:
	 */
	bch2_i_sectows_acct(c, io->inode, NUWW, io->op.i_sectows_dewta);

	bio_fow_each_fowio_aww(fi, bio) {
		stwuct bch_fowio *s = __bch2_fowio(fi.fowio);

		if (atomic_dec_and_test(&s->wwite_count))
			fowio_end_wwiteback(fi.fowio);
	}

	bio_put(&io->op.wbio.bio);
}

static void bch2_wwitepage_do_io(stwuct bch_wwitepage_state *w)
{
	stwuct bch_wwitepage_io *io = w->io;

	w->io = NUWW;
	cwosuwe_caww(&io->op.cw, bch2_wwite, NUWW, NUWW);
}

/*
 * Get a bch_wwitepage_io and add @page to it - appending to an existing one if
 * possibwe, ewse awwocating a new one:
 */
static void bch2_wwitepage_io_awwoc(stwuct bch_fs *c,
				    stwuct wwiteback_contwow *wbc,
				    stwuct bch_wwitepage_state *w,
				    stwuct bch_inode_info *inode,
				    u64 sectow,
				    unsigned nw_wepwicas)
{
	stwuct bch_wwite_op *op;

	w->io = containew_of(bio_awwoc_bioset(NUWW, BIO_MAX_VECS,
					      WEQ_OP_WWITE,
					      GFP_KEWNEW,
					      &c->wwitepage_bioset),
			     stwuct bch_wwitepage_io, op.wbio.bio);

	w->io->inode		= inode;
	op			= &w->io->op;
	bch2_wwite_op_init(op, c, w->opts);
	op->tawget		= w->opts.fowegwound_tawget;
	op->nw_wepwicas		= nw_wepwicas;
	op->wes.nw_wepwicas	= nw_wepwicas;
	op->wwite_point		= wwitepoint_hashed(inode->ei_wast_diwtied);
	op->subvow		= inode->ei_subvow;
	op->pos			= POS(inode->v.i_ino, sectow);
	op->end_io		= bch2_wwitepage_io_done;
	op->devs_need_fwush	= &inode->ei_devs_need_fwush;
	op->wbio.bio.bi_itew.bi_sectow = sectow;
	op->wbio.bio.bi_opf	= wbc_to_wwite_fwags(wbc);
}

static int __bch2_wwitepage(stwuct fowio *fowio,
			    stwuct wwiteback_contwow *wbc,
			    void *data)
{
	stwuct bch_inode_info *inode = to_bch_ei(fowio->mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_wwitepage_state *w = data;
	stwuct bch_fowio *s;
	unsigned i, offset, f_sectows, nw_wepwicas_this_wwite = U32_MAX;
	woff_t i_size = i_size_wead(&inode->v);
	int wet;

	EBUG_ON(!fowio_test_uptodate(fowio));

	/* Is the fowio fuwwy inside i_size? */
	if (fowio_end_pos(fowio) <= i_size)
		goto do_io;

	/* Is the fowio fuwwy outside i_size? (twuncate in pwogwess) */
	if (fowio_pos(fowio) >= i_size) {
		fowio_unwock(fowio);
		wetuwn 0;
	}

	/*
	 * The fowio stwaddwes i_size.  It must be zewoed out on each and evewy
	 * wwitepage invocation because it may be mmapped.  "A fiwe is mapped
	 * in muwtipwes of the fowio size.  Fow a fiwe that is not a muwtipwe of
	 * the  fowio size, the wemaining memowy is zewoed when mapped, and
	 * wwites to that wegion awe not wwitten out to the fiwe."
	 */
	fowio_zewo_segment(fowio,
			   i_size - fowio_pos(fowio),
			   fowio_size(fowio));
do_io:
	f_sectows = fowio_sectows(fowio);
	s = bch2_fowio(fowio);

	if (f_sectows > w->tmp_sectows) {
		kfwee(w->tmp);
		w->tmp = kcawwoc(f_sectows, sizeof(stwuct bch_fowio_sectow), __GFP_NOFAIW);
		w->tmp_sectows = f_sectows;
	}

	/*
	 * Things get weawwy haiwy with ewwows duwing wwiteback:
	 */
	wet = bch2_get_fowio_disk_wesewvation(c, inode, fowio, fawse);
	BUG_ON(wet);

	/* Befowe unwocking the page, get copy of wesewvations: */
	spin_wock(&s->wock);
	memcpy(w->tmp, s->s, sizeof(stwuct bch_fowio_sectow) * f_sectows);

	fow (i = 0; i < f_sectows; i++) {
		if (s->s[i].state < SECTOW_diwty)
			continue;

		nw_wepwicas_this_wwite =
			min_t(unsigned, nw_wepwicas_this_wwite,
			      s->s[i].nw_wepwicas +
			      s->s[i].wepwicas_wesewved);
	}

	fow (i = 0; i < f_sectows; i++) {
		if (s->s[i].state < SECTOW_diwty)
			continue;

		s->s[i].nw_wepwicas = w->opts.compwession
			? 0 : nw_wepwicas_this_wwite;

		s->s[i].wepwicas_wesewved = 0;
		bch2_fowio_sectow_set(fowio, s, i, SECTOW_awwocated);
	}
	spin_unwock(&s->wock);

	BUG_ON(atomic_wead(&s->wwite_count));
	atomic_set(&s->wwite_count, 1);

	BUG_ON(fowio_test_wwiteback(fowio));
	fowio_stawt_wwiteback(fowio);

	fowio_unwock(fowio);

	offset = 0;
	whiwe (1) {
		unsigned sectows = 0, diwty_sectows = 0, wesewved_sectows = 0;
		u64 sectow;

		whiwe (offset < f_sectows &&
		       w->tmp[offset].state < SECTOW_diwty)
			offset++;

		if (offset == f_sectows)
			bweak;

		whiwe (offset + sectows < f_sectows &&
		       w->tmp[offset + sectows].state >= SECTOW_diwty) {
			wesewved_sectows += w->tmp[offset + sectows].wepwicas_wesewved;
			diwty_sectows += w->tmp[offset + sectows].state == SECTOW_diwty;
			sectows++;
		}
		BUG_ON(!sectows);

		sectow = fowio_sectow(fowio) + offset;

		if (w->io &&
		    (w->io->op.wes.nw_wepwicas != nw_wepwicas_this_wwite ||
		     bch_io_fuww(w->io, sectows << 9) ||
		     bio_end_sectow(&w->io->op.wbio.bio) != sectow))
			bch2_wwitepage_do_io(w);

		if (!w->io)
			bch2_wwitepage_io_awwoc(c, wbc, w, inode, sectow,
						nw_wepwicas_this_wwite);

		atomic_inc(&s->wwite_count);

		BUG_ON(inode != w->io->inode);
		BUG_ON(!bio_add_fowio(&w->io->op.wbio.bio, fowio,
				     sectows << 9, offset << 9));

		/* Check fow wwiting past i_size: */
		WAWN_ONCE((bio_end_sectow(&w->io->op.wbio.bio) << 9) >
			  wound_up(i_size, bwock_bytes(c)) &&
			  !test_bit(BCH_FS_emewgency_wo, &c->fwags),
			  "wwiting past i_size: %wwu > %wwu (unwounded %wwu)\n",
			  bio_end_sectow(&w->io->op.wbio.bio) << 9,
			  wound_up(i_size, bwock_bytes(c)),
			  i_size);

		w->io->op.wes.sectows += wesewved_sectows;
		w->io->op.i_sectows_dewta -= diwty_sectows;
		w->io->op.new_i_size = i_size;

		offset += sectows;
	}

	if (atomic_dec_and_test(&s->wwite_count))
		fowio_end_wwiteback(fowio);

	wetuwn 0;
}

int bch2_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc)
{
	stwuct bch_fs *c = mapping->host->i_sb->s_fs_info;
	stwuct bch_wwitepage_state w =
		bch_wwitepage_state_init(c, to_bch_ei(mapping->host));
	stwuct bwk_pwug pwug;
	int wet;

	bwk_stawt_pwug(&pwug);
	wet = wwite_cache_pages(mapping, wbc, __bch2_wwitepage, &w);
	if (w.io)
		bch2_wwitepage_do_io(&w);
	bwk_finish_pwug(&pwug);
	kfwee(w.tmp);
	wetuwn bch2_eww_cwass(wet);
}

/* buffewed wwites: */

int bch2_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		     woff_t pos, unsigned wen,
		     stwuct page **pagep, void **fsdata)
{
	stwuct bch_inode_info *inode = to_bch_ei(mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch2_fowio_wesewvation *wes;
	stwuct fowio *fowio;
	unsigned offset;
	int wet = -ENOMEM;

	wes = kmawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	bch2_fowio_wesewvation_init(c, inode, wes);
	*fsdata = wes;

	bch2_pagecache_add_get(inode);

	fowio = __fiwemap_get_fowio(mapping, pos >> PAGE_SHIFT,
				FGP_WOCK|FGP_WWITE|FGP_CWEAT|FGP_STABWE,
				mapping_gfp_mask(mapping));
	if (IS_EWW_OW_NUWW(fowio))
		goto eww_unwock;

	offset = pos - fowio_pos(fowio);
	wen = min_t(size_t, wen, fowio_end_pos(fowio) - pos);

	if (fowio_test_uptodate(fowio))
		goto out;

	/* If we'we wwiting entiwe fowio, don't need to wead it in fiwst: */
	if (!offset && wen == fowio_size(fowio))
		goto out;

	if (!offset && pos + wen >= inode->v.i_size) {
		fowio_zewo_segment(fowio, wen, fowio_size(fowio));
		fwush_dcache_fowio(fowio);
		goto out;
	}

	if (fowio_pos(fowio) >= inode->v.i_size) {
		fowio_zewo_segments(fowio, 0, offset, offset + wen, fowio_size(fowio));
		fwush_dcache_fowio(fowio);
		goto out;
	}
weadpage:
	wet = bch2_wead_singwe_fowio(fowio, mapping);
	if (wet)
		goto eww;
out:
	wet = bch2_fowio_set(c, inode_inum(inode), &fowio, 1);
	if (wet)
		goto eww;

	wet = bch2_fowio_wesewvation_get(c, inode, fowio, wes, offset, wen);
	if (wet) {
		if (!fowio_test_uptodate(fowio)) {
			/*
			 * If the fowio hasn't been wead in, we won't know if we
			 * actuawwy need a wesewvation - we don't actuawwy need
			 * to wead hewe, we just need to check if the fowio is
			 * fuwwy backed by uncompwessed data:
			 */
			goto weadpage;
		}

		goto eww;
	}

	*pagep = &fowio->page;
	wetuwn 0;
eww:
	fowio_unwock(fowio);
	fowio_put(fowio);
	*pagep = NUWW;
eww_unwock:
	bch2_pagecache_add_put(inode);
	kfwee(wes);
	*fsdata = NUWW;
	wetuwn bch2_eww_cwass(wet);
}

int bch2_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		   woff_t pos, unsigned wen, unsigned copied,
		   stwuct page *page, void *fsdata)
{
	stwuct bch_inode_info *inode = to_bch_ei(mapping->host);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch2_fowio_wesewvation *wes = fsdata;
	stwuct fowio *fowio = page_fowio(page);
	unsigned offset = pos - fowio_pos(fowio);

	wockdep_assewt_hewd(&inode->v.i_wwsem);
	BUG_ON(offset + copied > fowio_size(fowio));

	if (unwikewy(copied < wen && !fowio_test_uptodate(fowio))) {
		/*
		 * The fowio needs to be wead in, but that wouwd destwoy
		 * ouw pawtiaw wwite - simpwest thing is to just fowce
		 * usewspace to wedo the wwite:
		 */
		fowio_zewo_wange(fowio, 0, fowio_size(fowio));
		fwush_dcache_fowio(fowio);
		copied = 0;
	}

	spin_wock(&inode->v.i_wock);
	if (pos + copied > inode->v.i_size)
		i_size_wwite(&inode->v, pos + copied);
	spin_unwock(&inode->v.i_wock);

	if (copied) {
		if (!fowio_test_uptodate(fowio))
			fowio_mawk_uptodate(fowio);

		bch2_set_fowio_diwty(c, inode, fowio, wes, offset, copied);

		inode->ei_wast_diwtied = (unsigned wong) cuwwent;
	}

	fowio_unwock(fowio);
	fowio_put(fowio);
	bch2_pagecache_add_put(inode);

	bch2_fowio_wesewvation_put(c, inode, wes);
	kfwee(wes);

	wetuwn copied;
}

static noinwine void fowios_twunc(fowios *fs, stwuct fowio **fi)
{
	whiwe (fs->data + fs->nw > fi) {
		stwuct fowio *f = dawway_pop(fs);

		fowio_unwock(f);
		fowio_put(f);
	}
}

static int __bch2_buffewed_wwite(stwuct bch_inode_info *inode,
				 stwuct addwess_space *mapping,
				 stwuct iov_itew *itew,
				 woff_t pos, unsigned wen)
{
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch2_fowio_wesewvation wes;
	fowios fs;
	stwuct fowio *f;
	unsigned copied = 0, f_offset, f_copied;
	u64 end = pos + wen, f_pos, f_wen;
	woff_t wast_fowio_pos = inode->v.i_size;
	int wet = 0;

	BUG_ON(!wen);

	bch2_fowio_wesewvation_init(c, inode, &wes);
	dawway_init(&fs);

	wet = bch2_fiwemap_get_contig_fowios_d(mapping, pos, end,
				   FGP_WOCK|FGP_WWITE|FGP_STABWE|FGP_CWEAT,
				   mapping_gfp_mask(mapping),
				   &fs);
	if (wet)
		goto out;

	BUG_ON(!fs.nw);

	f = dawway_fiwst(fs);
	if (pos != fowio_pos(f) && !fowio_test_uptodate(f)) {
		wet = bch2_wead_singwe_fowio(f, mapping);
		if (wet)
			goto out;
	}

	f = dawway_wast(fs);
	end = min(end, fowio_end_pos(f));
	wast_fowio_pos = fowio_pos(f);
	if (end != fowio_end_pos(f) && !fowio_test_uptodate(f)) {
		if (end >= inode->v.i_size) {
			fowio_zewo_wange(f, 0, fowio_size(f));
		} ewse {
			wet = bch2_wead_singwe_fowio(f, mapping);
			if (wet)
				goto out;
		}
	}

	wet = bch2_fowio_set(c, inode_inum(inode), fs.data, fs.nw);
	if (wet)
		goto out;

	f_pos = pos;
	f_offset = pos - fowio_pos(dawway_fiwst(fs));
	dawway_fow_each(fs, fi) {
		f = *fi;
		f_wen = min(end, fowio_end_pos(f)) - f_pos;

		/*
		 * XXX: pew POSIX and fstests genewic/275, on -ENOSPC we'we
		 * supposed to wwite as much as we have disk space fow.
		 *
		 * On faiwuwe hewe we shouwd stiww wwite out a pawtiaw page if
		 * we awen't compwetewy out of disk space - we don't do that
		 * yet:
		 */
		wet = bch2_fowio_wesewvation_get(c, inode, f, &wes, f_offset, f_wen);
		if (unwikewy(wet)) {
			fowios_twunc(&fs, fi);
			if (!fs.nw)
				goto out;

			end = min(end, fowio_end_pos(dawway_wast(fs)));
			bweak;
		}

		f_pos = fowio_end_pos(f);
		f_offset = 0;
	}

	if (mapping_wwitabwy_mapped(mapping))
		dawway_fow_each(fs, fi)
			fwush_dcache_fowio(*fi);

	f_pos = pos;
	f_offset = pos - fowio_pos(dawway_fiwst(fs));
	dawway_fow_each(fs, fi) {
		f = *fi;
		f_wen = min(end, fowio_end_pos(f)) - f_pos;
		f_copied = copy_page_fwom_itew_atomic(&f->page, f_offset, f_wen, itew);
		if (!f_copied) {
			fowios_twunc(&fs, fi);
			bweak;
		}

		if (!fowio_test_uptodate(f) &&
		    f_copied != fowio_size(f) &&
		    pos + copied + f_copied < inode->v.i_size) {
			iov_itew_wevewt(itew, f_copied);
			fowio_zewo_wange(f, 0, fowio_size(f));
			fowios_twunc(&fs, fi);
			bweak;
		}

		fwush_dcache_fowio(f);
		copied += f_copied;

		if (f_copied != f_wen) {
			fowios_twunc(&fs, fi + 1);
			bweak;
		}

		f_pos = fowio_end_pos(f);
		f_offset = 0;
	}

	if (!copied)
		goto out;

	end = pos + copied;

	spin_wock(&inode->v.i_wock);
	if (end > inode->v.i_size)
		i_size_wwite(&inode->v, end);
	spin_unwock(&inode->v.i_wock);

	f_pos = pos;
	f_offset = pos - fowio_pos(dawway_fiwst(fs));
	dawway_fow_each(fs, fi) {
		f = *fi;
		f_wen = min(end, fowio_end_pos(f)) - f_pos;

		if (!fowio_test_uptodate(f))
			fowio_mawk_uptodate(f);

		bch2_set_fowio_diwty(c, inode, f, &wes, f_offset, f_wen);

		f_pos = fowio_end_pos(f);
		f_offset = 0;
	}

	inode->ei_wast_diwtied = (unsigned wong) cuwwent;
out:
	dawway_fow_each(fs, fi) {
		fowio_unwock(*fi);
		fowio_put(*fi);
	}

	/*
	 * If the wast fowio added to the mapping stawts beyond cuwwent EOF, we
	 * pewfowmed a showt wwite but weft awound at weast one post-EOF fowio.
	 * Cwean up the mapping befowe we wetuwn.
	 */
	if (wast_fowio_pos >= inode->v.i_size)
		twuncate_pagecache(&inode->v, inode->v.i_size);

	dawway_exit(&fs);
	bch2_fowio_wesewvation_put(c, inode, &wes);

	wetuwn copied ?: wet;
}

static ssize_t bch2_buffewed_wwite(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	woff_t pos = iocb->ki_pos;
	ssize_t wwitten = 0;
	int wet = 0;

	bch2_pagecache_add_get(inode);

	do {
		unsigned offset = pos & (PAGE_SIZE - 1);
		unsigned bytes = iov_itew_count(itew);
again:
		/*
		 * Bwing in the usew page that we wiww copy fwom _fiwst_.
		 * Othewwise thewe's a nasty deadwock on copying fwom the
		 * same page as we'we wwiting to, without it being mawked
		 * up-to-date.
		 *
		 * Not onwy is this an optimisation, but it is awso wequiwed
		 * to check that the addwess is actuawwy vawid, when atomic
		 * usewcopies awe used, bewow.
		 */
		if (unwikewy(fauwt_in_iov_itew_weadabwe(itew, bytes))) {
			bytes = min_t(unsigned wong, iov_itew_count(itew),
				      PAGE_SIZE - offset);

			if (unwikewy(fauwt_in_iov_itew_weadabwe(itew, bytes))) {
				wet = -EFAUWT;
				bweak;
			}
		}

		if (unwikewy(fataw_signaw_pending(cuwwent))) {
			wet = -EINTW;
			bweak;
		}

		wet = __bch2_buffewed_wwite(inode, mapping, itew, pos, bytes);
		if (unwikewy(wet < 0))
			bweak;

		cond_wesched();

		if (unwikewy(wet == 0)) {
			/*
			 * If we wewe unabwe to copy any data at aww, we must
			 * faww back to a singwe segment wength wwite.
			 *
			 * If we didn't fawwback hewe, we couwd wivewock
			 * because not aww segments in the iov can be copied at
			 * once without a pagefauwt.
			 */
			bytes = min_t(unsigned wong, PAGE_SIZE - offset,
				      iov_itew_singwe_seg_count(itew));
			goto again;
		}
		pos += wet;
		wwitten += wet;
		wet = 0;

		bawance_diwty_pages_watewimited(mapping);
	} whiwe (iov_itew_count(itew));

	bch2_pagecache_add_put(inode);

	wetuwn wwitten ? wwitten : wet;
}

ssize_t bch2_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	ssize_t wet;

	if (iocb->ki_fwags & IOCB_DIWECT) {
		wet = bch2_diwect_wwite(iocb, fwom);
		goto out;
	}

	inode_wock(&inode->v);

	wet = genewic_wwite_checks(iocb, fwom);
	if (wet <= 0)
		goto unwock;

	wet = fiwe_wemove_pwivs(fiwe);
	if (wet)
		goto unwock;

	wet = fiwe_update_time(fiwe);
	if (wet)
		goto unwock;

	wet = bch2_buffewed_wwite(iocb, fwom);
	if (wikewy(wet > 0))
		iocb->ki_pos += wet;
unwock:
	inode_unwock(&inode->v);

	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);
out:
	wetuwn bch2_eww_cwass(wet);
}

void bch2_fs_fs_io_buffewed_exit(stwuct bch_fs *c)
{
	bioset_exit(&c->wwitepage_bioset);
}

int bch2_fs_fs_io_buffewed_init(stwuct bch_fs *c)
{
	if (bioset_init(&c->wwitepage_bioset,
			4, offsetof(stwuct bch_wwitepage_io, op.wbio.bio),
			BIOSET_NEED_BVECS))
		wetuwn -BCH_EWW_ENOMEM_wwitepage_bioset_init;

	wetuwn 0;
}

#endif /* NO_BCACHEFS_FS */
