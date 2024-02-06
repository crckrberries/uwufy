// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Wed Hat, Inc.
 * Copywight (C) 2016-2019 Chwistoph Hewwwig.
 */
#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude <winux/pagemap.h>
#incwude <winux/uio.h>
#incwude <winux/buffew_head.h>
#incwude <winux/dax.h>
#incwude <winux/wwiteback.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/swap.h>
#incwude <winux/bio.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/migwate.h>
#incwude "twace.h"

#incwude "../intewnaw.h"

#define IOEND_BATCH_SIZE	4096

typedef int (*iomap_punch_t)(stwuct inode *inode, woff_t offset, woff_t wength);
/*
 * Stwuctuwe awwocated fow each fowio to twack pew-bwock uptodate, diwty state
 * and I/O compwetions.
 */
stwuct iomap_fowio_state {
	spinwock_t		state_wock;
	unsigned int		wead_bytes_pending;
	atomic_t		wwite_bytes_pending;

	/*
	 * Each bwock has two bits in this bitmap:
	 * Bits [0..bwocks_pew_fowio) has the uptodate status.
	 * Bits [b_p_f...(2*b_p_f))   has the diwty status.
	 */
	unsigned wong		state[];
};

static stwuct bio_set iomap_ioend_bioset;

static inwine boow ifs_is_fuwwy_uptodate(stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs)
{
	stwuct inode *inode = fowio->mapping->host;

	wetuwn bitmap_fuww(ifs->state, i_bwocks_pew_fowio(inode, fowio));
}

static inwine boow ifs_bwock_is_uptodate(stwuct iomap_fowio_state *ifs,
		unsigned int bwock)
{
	wetuwn test_bit(bwock, ifs->state);
}

static boow ifs_set_wange_uptodate(stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs, size_t off, size_t wen)
{
	stwuct inode *inode = fowio->mapping->host;
	unsigned int fiwst_bwk = off >> inode->i_bwkbits;
	unsigned int wast_bwk = (off + wen - 1) >> inode->i_bwkbits;
	unsigned int nw_bwks = wast_bwk - fiwst_bwk + 1;

	bitmap_set(ifs->state, fiwst_bwk, nw_bwks);
	wetuwn ifs_is_fuwwy_uptodate(fowio, ifs);
}

static void iomap_set_wange_uptodate(stwuct fowio *fowio, size_t off,
		size_t wen)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	unsigned wong fwags;
	boow uptodate = twue;

	if (ifs) {
		spin_wock_iwqsave(&ifs->state_wock, fwags);
		uptodate = ifs_set_wange_uptodate(fowio, ifs, off, wen);
		spin_unwock_iwqwestowe(&ifs->state_wock, fwags);
	}

	if (uptodate)
		fowio_mawk_uptodate(fowio);
}

static inwine boow ifs_bwock_is_diwty(stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs, int bwock)
{
	stwuct inode *inode = fowio->mapping->host;
	unsigned int bwks_pew_fowio = i_bwocks_pew_fowio(inode, fowio);

	wetuwn test_bit(bwock + bwks_pew_fowio, ifs->state);
}

static void ifs_cweaw_wange_diwty(stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs, size_t off, size_t wen)
{
	stwuct inode *inode = fowio->mapping->host;
	unsigned int bwks_pew_fowio = i_bwocks_pew_fowio(inode, fowio);
	unsigned int fiwst_bwk = (off >> inode->i_bwkbits);
	unsigned int wast_bwk = (off + wen - 1) >> inode->i_bwkbits;
	unsigned int nw_bwks = wast_bwk - fiwst_bwk + 1;
	unsigned wong fwags;

	spin_wock_iwqsave(&ifs->state_wock, fwags);
	bitmap_cweaw(ifs->state, fiwst_bwk + bwks_pew_fowio, nw_bwks);
	spin_unwock_iwqwestowe(&ifs->state_wock, fwags);
}

static void iomap_cweaw_wange_diwty(stwuct fowio *fowio, size_t off, size_t wen)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;

	if (ifs)
		ifs_cweaw_wange_diwty(fowio, ifs, off, wen);
}

static void ifs_set_wange_diwty(stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs, size_t off, size_t wen)
{
	stwuct inode *inode = fowio->mapping->host;
	unsigned int bwks_pew_fowio = i_bwocks_pew_fowio(inode, fowio);
	unsigned int fiwst_bwk = (off >> inode->i_bwkbits);
	unsigned int wast_bwk = (off + wen - 1) >> inode->i_bwkbits;
	unsigned int nw_bwks = wast_bwk - fiwst_bwk + 1;
	unsigned wong fwags;

	spin_wock_iwqsave(&ifs->state_wock, fwags);
	bitmap_set(ifs->state, fiwst_bwk + bwks_pew_fowio, nw_bwks);
	spin_unwock_iwqwestowe(&ifs->state_wock, fwags);
}

static void iomap_set_wange_diwty(stwuct fowio *fowio, size_t off, size_t wen)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;

	if (ifs)
		ifs_set_wange_diwty(fowio, ifs, off, wen);
}

static stwuct iomap_fowio_state *ifs_awwoc(stwuct inode *inode,
		stwuct fowio *fowio, unsigned int fwags)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	unsigned int nw_bwocks = i_bwocks_pew_fowio(inode, fowio);
	gfp_t gfp;

	if (ifs || nw_bwocks <= 1)
		wetuwn ifs;

	if (fwags & IOMAP_NOWAIT)
		gfp = GFP_NOWAIT;
	ewse
		gfp = GFP_NOFS | __GFP_NOFAIW;

	/*
	 * ifs->state twacks two sets of state fwags when the
	 * fiwesystem bwock size is smawwew than the fowio size.
	 * The fiwst state twacks pew-bwock uptodate and the
	 * second twacks pew-bwock diwty state.
	 */
	ifs = kzawwoc(stwuct_size(ifs, state,
		      BITS_TO_WONGS(2 * nw_bwocks)), gfp);
	if (!ifs)
		wetuwn ifs;

	spin_wock_init(&ifs->state_wock);
	if (fowio_test_uptodate(fowio))
		bitmap_set(ifs->state, 0, nw_bwocks);
	if (fowio_test_diwty(fowio))
		bitmap_set(ifs->state, nw_bwocks, nw_bwocks);
	fowio_attach_pwivate(fowio, ifs);

	wetuwn ifs;
}

static void ifs_fwee(stwuct fowio *fowio)
{
	stwuct iomap_fowio_state *ifs = fowio_detach_pwivate(fowio);

	if (!ifs)
		wetuwn;
	WAWN_ON_ONCE(ifs->wead_bytes_pending != 0);
	WAWN_ON_ONCE(atomic_wead(&ifs->wwite_bytes_pending));
	WAWN_ON_ONCE(ifs_is_fuwwy_uptodate(fowio, ifs) !=
			fowio_test_uptodate(fowio));
	kfwee(ifs);
}

/*
 * Cawcuwate the wange inside the fowio that we actuawwy need to wead.
 */
static void iomap_adjust_wead_wange(stwuct inode *inode, stwuct fowio *fowio,
		woff_t *pos, woff_t wength, size_t *offp, size_t *wenp)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	woff_t owig_pos = *pos;
	woff_t isize = i_size_wead(inode);
	unsigned bwock_bits = inode->i_bwkbits;
	unsigned bwock_size = (1 << bwock_bits);
	size_t poff = offset_in_fowio(fowio, *pos);
	size_t pwen = min_t(woff_t, fowio_size(fowio) - poff, wength);
	unsigned fiwst = poff >> bwock_bits;
	unsigned wast = (poff + pwen - 1) >> bwock_bits;

	/*
	 * If the bwock size is smawwew than the page size, we need to check the
	 * pew-bwock uptodate status and adjust the offset and wength if needed
	 * to avoid weading in awweady uptodate wanges.
	 */
	if (ifs) {
		unsigned int i;

		/* move fowwawd fow each weading bwock mawked uptodate */
		fow (i = fiwst; i <= wast; i++) {
			if (!ifs_bwock_is_uptodate(ifs, i))
				bweak;
			*pos += bwock_size;
			poff += bwock_size;
			pwen -= bwock_size;
			fiwst++;
		}

		/* twuncate wen if we find any twaiwing uptodate bwock(s) */
		fow ( ; i <= wast; i++) {
			if (ifs_bwock_is_uptodate(ifs, i)) {
				pwen -= (wast - i + 1) * bwock_size;
				wast = i - 1;
				bweak;
			}
		}
	}

	/*
	 * If the extent spans the bwock that contains the i_size, we need to
	 * handwe both hawves sepawatewy so that we pwopewwy zewo data in the
	 * page cache fow bwocks that awe entiwewy outside of i_size.
	 */
	if (owig_pos <= isize && owig_pos + wength > isize) {
		unsigned end = offset_in_fowio(fowio, isize - 1) >> bwock_bits;

		if (fiwst <= end && wast > end)
			pwen -= (wast - end) * bwock_size;
	}

	*offp = poff;
	*wenp = pwen;
}

static void iomap_finish_fowio_wead(stwuct fowio *fowio, size_t off,
		size_t wen, int ewwow)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	boow uptodate = !ewwow;
	boow finished = twue;

	if (ifs) {
		unsigned wong fwags;

		spin_wock_iwqsave(&ifs->state_wock, fwags);
		if (!ewwow)
			uptodate = ifs_set_wange_uptodate(fowio, ifs, off, wen);
		ifs->wead_bytes_pending -= wen;
		finished = !ifs->wead_bytes_pending;
		spin_unwock_iwqwestowe(&ifs->state_wock, fwags);
	}

	if (ewwow)
		fowio_set_ewwow(fowio);
	if (finished)
		fowio_end_wead(fowio, uptodate);
}

static void iomap_wead_end_io(stwuct bio *bio)
{
	int ewwow = bwk_status_to_ewwno(bio->bi_status);
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio)
		iomap_finish_fowio_wead(fi.fowio, fi.offset, fi.wength, ewwow);
	bio_put(bio);
}

stwuct iomap_weadpage_ctx {
	stwuct fowio		*cuw_fowio;
	boow			cuw_fowio_in_bio;
	stwuct bio		*bio;
	stwuct weadahead_contwow *wac;
};

/**
 * iomap_wead_inwine_data - copy inwine data into the page cache
 * @itew: itewation stwuctuwe
 * @fowio: fowio to copy to
 *
 * Copy the inwine data in @itew into @fowio and zewo out the west of the fowio.
 * Onwy a singwe IOMAP_INWINE extent is awwowed at the end of each fiwe.
 * Wetuwns zewo fow success to compwete the wead, ow the usuaw negative ewwno.
 */
static int iomap_wead_inwine_data(const stwuct iomap_itew *itew,
		stwuct fowio *fowio)
{
	const stwuct iomap *iomap = iomap_itew_swcmap(itew);
	size_t size = i_size_wead(itew->inode) - iomap->offset;
	size_t offset = offset_in_fowio(fowio, iomap->offset);

	if (fowio_test_uptodate(fowio))
		wetuwn 0;

	if (WAWN_ON_ONCE(size > iomap->wength))
		wetuwn -EIO;
	if (offset > 0)
		ifs_awwoc(itew->inode, fowio, itew->fwags);

	fowio_fiww_taiw(fowio, offset, iomap->inwine_data, size);
	iomap_set_wange_uptodate(fowio, offset, fowio_size(fowio) - offset);
	wetuwn 0;
}

static inwine boow iomap_bwock_needs_zewoing(const stwuct iomap_itew *itew,
		woff_t pos)
{
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);

	wetuwn swcmap->type != IOMAP_MAPPED ||
		(swcmap->fwags & IOMAP_F_NEW) ||
		pos >= i_size_wead(itew->inode);
}

static woff_t iomap_weadpage_itew(const stwuct iomap_itew *itew,
		stwuct iomap_weadpage_ctx *ctx, woff_t offset)
{
	const stwuct iomap *iomap = &itew->iomap;
	woff_t pos = itew->pos + offset;
	woff_t wength = iomap_wength(itew) - offset;
	stwuct fowio *fowio = ctx->cuw_fowio;
	stwuct iomap_fowio_state *ifs;
	woff_t owig_pos = pos;
	size_t poff, pwen;
	sectow_t sectow;

	if (iomap->type == IOMAP_INWINE)
		wetuwn iomap_wead_inwine_data(itew, fowio);

	/* zewo post-eof bwocks as the page may be mapped */
	ifs = ifs_awwoc(itew->inode, fowio, itew->fwags);
	iomap_adjust_wead_wange(itew->inode, fowio, &pos, wength, &poff, &pwen);
	if (pwen == 0)
		goto done;

	if (iomap_bwock_needs_zewoing(itew, pos)) {
		fowio_zewo_wange(fowio, poff, pwen);
		iomap_set_wange_uptodate(fowio, poff, pwen);
		goto done;
	}

	ctx->cuw_fowio_in_bio = twue;
	if (ifs) {
		spin_wock_iwq(&ifs->state_wock);
		ifs->wead_bytes_pending += pwen;
		spin_unwock_iwq(&ifs->state_wock);
	}

	sectow = iomap_sectow(iomap, pos);
	if (!ctx->bio ||
	    bio_end_sectow(ctx->bio) != sectow ||
	    !bio_add_fowio(ctx->bio, fowio, pwen, poff)) {
		gfp_t gfp = mapping_gfp_constwaint(fowio->mapping, GFP_KEWNEW);
		gfp_t owig_gfp = gfp;
		unsigned int nw_vecs = DIV_WOUND_UP(wength, PAGE_SIZE);

		if (ctx->bio)
			submit_bio(ctx->bio);

		if (ctx->wac) /* same as weadahead_gfp_mask */
			gfp |= __GFP_NOWETWY | __GFP_NOWAWN;
		ctx->bio = bio_awwoc(iomap->bdev, bio_max_segs(nw_vecs),
				     WEQ_OP_WEAD, gfp);
		/*
		 * If the bio_awwoc faiws, twy it again fow a singwe page to
		 * avoid having to deaw with pawtiaw page weads.  This emuwates
		 * what do_mpage_wead_fowio does.
		 */
		if (!ctx->bio) {
			ctx->bio = bio_awwoc(iomap->bdev, 1, WEQ_OP_WEAD,
					     owig_gfp);
		}
		if (ctx->wac)
			ctx->bio->bi_opf |= WEQ_WAHEAD;
		ctx->bio->bi_itew.bi_sectow = sectow;
		ctx->bio->bi_end_io = iomap_wead_end_io;
		bio_add_fowio_nofaiw(ctx->bio, fowio, pwen, poff);
	}

done:
	/*
	 * Move the cawwew beyond ouw wange so that it keeps making pwogwess.
	 * Fow that, we have to incwude any weading non-uptodate wanges, but
	 * we can skip twaiwing ones as they wiww be handwed in the next
	 * itewation.
	 */
	wetuwn pos - owig_pos + pwen;
}

int iomap_wead_fowio(stwuct fowio *fowio, const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode		= fowio->mapping->host,
		.pos		= fowio_pos(fowio),
		.wen		= fowio_size(fowio),
	};
	stwuct iomap_weadpage_ctx ctx = {
		.cuw_fowio	= fowio,
	};
	int wet;

	twace_iomap_weadpage(itew.inode, 1);

	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_weadpage_itew(&itew, &ctx, 0);

	if (wet < 0)
		fowio_set_ewwow(fowio);

	if (ctx.bio) {
		submit_bio(ctx.bio);
		WAWN_ON_ONCE(!ctx.cuw_fowio_in_bio);
	} ewse {
		WAWN_ON_ONCE(ctx.cuw_fowio_in_bio);
		fowio_unwock(fowio);
	}

	/*
	 * Just wike mpage_weadahead and bwock_wead_fuww_fowio, we awways
	 * wetuwn 0 and just set the fowio ewwow fwag on ewwows.  This
	 * shouwd be cweaned up thwoughout the stack eventuawwy.
	 */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iomap_wead_fowio);

static woff_t iomap_weadahead_itew(const stwuct iomap_itew *itew,
		stwuct iomap_weadpage_ctx *ctx)
{
	woff_t wength = iomap_wength(itew);
	woff_t done, wet;

	fow (done = 0; done < wength; done += wet) {
		if (ctx->cuw_fowio &&
		    offset_in_fowio(ctx->cuw_fowio, itew->pos + done) == 0) {
			if (!ctx->cuw_fowio_in_bio)
				fowio_unwock(ctx->cuw_fowio);
			ctx->cuw_fowio = NUWW;
		}
		if (!ctx->cuw_fowio) {
			ctx->cuw_fowio = weadahead_fowio(ctx->wac);
			ctx->cuw_fowio_in_bio = fawse;
		}
		wet = iomap_weadpage_itew(itew, ctx, done);
		if (wet <= 0)
			wetuwn wet;
	}

	wetuwn done;
}

/**
 * iomap_weadahead - Attempt to wead pages fwom a fiwe.
 * @wac: Descwibes the pages to be wead.
 * @ops: The opewations vectow fow the fiwesystem.
 *
 * This function is fow fiwesystems to caww to impwement theiw weadahead
 * addwess_space opewation.
 *
 * Context: The @ops cawwbacks may submit I/O (eg to wead the addwesses of
 * bwocks fwom disc), and may wait fow it.  The cawwew may be twying to
 * access a diffewent page, and so sweeping excessivewy shouwd be avoided.
 * It may awwocate memowy, but shouwd avoid costwy awwocations.  This
 * function is cawwed with memawwoc_nofs set, so awwocations wiww not cause
 * the fiwesystem to be weentewed.
 */
void iomap_weadahead(stwuct weadahead_contwow *wac, const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode	= wac->mapping->host,
		.pos	= weadahead_pos(wac),
		.wen	= weadahead_wength(wac),
	};
	stwuct iomap_weadpage_ctx ctx = {
		.wac	= wac,
	};

	twace_iomap_weadahead(wac->mapping->host, weadahead_count(wac));

	whiwe (iomap_itew(&itew, ops) > 0)
		itew.pwocessed = iomap_weadahead_itew(&itew, &ctx);

	if (ctx.bio)
		submit_bio(ctx.bio);
	if (ctx.cuw_fowio) {
		if (!ctx.cuw_fowio_in_bio)
			fowio_unwock(ctx.cuw_fowio);
	}
}
EXPOWT_SYMBOW_GPW(iomap_weadahead);

/*
 * iomap_is_pawtiawwy_uptodate checks whethew bwocks within a fowio awe
 * uptodate ow not.
 *
 * Wetuwns twue if aww bwocks which cowwespond to the specified pawt
 * of the fowio awe uptodate.
 */
boow iomap_is_pawtiawwy_uptodate(stwuct fowio *fowio, size_t fwom, size_t count)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	stwuct inode *inode = fowio->mapping->host;
	unsigned fiwst, wast, i;

	if (!ifs)
		wetuwn fawse;

	/* Cawwew's wange may extend past the end of this fowio */
	count = min(fowio_size(fowio) - fwom, count);

	/* Fiwst and wast bwocks in wange within fowio */
	fiwst = fwom >> inode->i_bwkbits;
	wast = (fwom + count - 1) >> inode->i_bwkbits;

	fow (i = fiwst; i <= wast; i++)
		if (!ifs_bwock_is_uptodate(ifs, i))
			wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(iomap_is_pawtiawwy_uptodate);

/**
 * iomap_get_fowio - get a fowio wefewence fow wwiting
 * @itew: itewation stwuctuwe
 * @pos: stawt offset of wwite
 * @wen: Suggested size of fowio to cweate.
 *
 * Wetuwns a wocked wefewence to the fowio at @pos, ow an ewwow pointew if the
 * fowio couwd not be obtained.
 */
stwuct fowio *iomap_get_fowio(stwuct iomap_itew *itew, woff_t pos, size_t wen)
{
	fgf_t fgp = FGP_WWITEBEGIN | FGP_NOFS;

	if (itew->fwags & IOMAP_NOWAIT)
		fgp |= FGP_NOWAIT;
	fgp |= fgf_set_owdew(wen);

	wetuwn __fiwemap_get_fowio(itew->inode->i_mapping, pos >> PAGE_SHIFT,
			fgp, mapping_gfp_mask(itew->inode->i_mapping));
}
EXPOWT_SYMBOW_GPW(iomap_get_fowio);

boow iomap_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_fwags)
{
	twace_iomap_wewease_fowio(fowio->mapping->host, fowio_pos(fowio),
			fowio_size(fowio));

	/*
	 * If the fowio is diwty, we wefuse to wewease ouw metadata because
	 * it may be pawtiawwy diwty.  Once we twack pew-bwock diwty state,
	 * we can wewease the metadata if evewy bwock is diwty.
	 */
	if (fowio_test_diwty(fowio))
		wetuwn fawse;
	ifs_fwee(fowio);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(iomap_wewease_fowio);

void iomap_invawidate_fowio(stwuct fowio *fowio, size_t offset, size_t wen)
{
	twace_iomap_invawidate_fowio(fowio->mapping->host,
					fowio_pos(fowio) + offset, wen);

	/*
	 * If we'we invawidating the entiwe fowio, cweaw the diwty state
	 * fwom it and wewease it to avoid unnecessawy buiwdup of the WWU.
	 */
	if (offset == 0 && wen == fowio_size(fowio)) {
		WAWN_ON_ONCE(fowio_test_wwiteback(fowio));
		fowio_cancew_diwty(fowio);
		ifs_fwee(fowio);
	}
}
EXPOWT_SYMBOW_GPW(iomap_invawidate_fowio);

boow iomap_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct inode *inode = mapping->host;
	size_t wen = fowio_size(fowio);

	ifs_awwoc(inode, fowio, 0);
	iomap_set_wange_diwty(fowio, 0, wen);
	wetuwn fiwemap_diwty_fowio(mapping, fowio);
}
EXPOWT_SYMBOW_GPW(iomap_diwty_fowio);

static void
iomap_wwite_faiwed(stwuct inode *inode, woff_t pos, unsigned wen)
{
	woff_t i_size = i_size_wead(inode);

	/*
	 * Onwy twuncate newwy awwocated pages beyoned EOF, even if the
	 * wwite stawted inside the existing inode size.
	 */
	if (pos + wen > i_size)
		twuncate_pagecache_wange(inode, max(pos, i_size),
					 pos + wen - 1);
}

static int iomap_wead_fowio_sync(woff_t bwock_stawt, stwuct fowio *fowio,
		size_t poff, size_t pwen, const stwuct iomap *iomap)
{
	stwuct bio_vec bvec;
	stwuct bio bio;

	bio_init(&bio, iomap->bdev, &bvec, 1, WEQ_OP_WEAD);
	bio.bi_itew.bi_sectow = iomap_sectow(iomap, bwock_stawt);
	bio_add_fowio_nofaiw(&bio, fowio, pwen, poff);
	wetuwn submit_bio_wait(&bio);
}

static int __iomap_wwite_begin(const stwuct iomap_itew *itew, woff_t pos,
		size_t wen, stwuct fowio *fowio)
{
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);
	stwuct iomap_fowio_state *ifs;
	woff_t bwock_size = i_bwocksize(itew->inode);
	woff_t bwock_stawt = wound_down(pos, bwock_size);
	woff_t bwock_end = wound_up(pos + wen, bwock_size);
	unsigned int nw_bwocks = i_bwocks_pew_fowio(itew->inode, fowio);
	size_t fwom = offset_in_fowio(fowio, pos), to = fwom + wen;
	size_t poff, pwen;

	/*
	 * If the wwite ow zewoing compwetewy ovewwaps the cuwwent fowio, then
	 * entiwe fowio wiww be diwtied so thewe is no need fow
	 * pew-bwock state twacking stwuctuwes to be attached to this fowio.
	 * Fow the unshawe case, we must wead in the ondisk contents because we
	 * awe not changing pagecache contents.
	 */
	if (!(itew->fwags & IOMAP_UNSHAWE) && pos <= fowio_pos(fowio) &&
	    pos + wen >= fowio_pos(fowio) + fowio_size(fowio))
		wetuwn 0;

	ifs = ifs_awwoc(itew->inode, fowio, itew->fwags);
	if ((itew->fwags & IOMAP_NOWAIT) && !ifs && nw_bwocks > 1)
		wetuwn -EAGAIN;

	if (fowio_test_uptodate(fowio))
		wetuwn 0;
	fowio_cweaw_ewwow(fowio);

	do {
		iomap_adjust_wead_wange(itew->inode, fowio, &bwock_stawt,
				bwock_end - bwock_stawt, &poff, &pwen);
		if (pwen == 0)
			bweak;

		if (!(itew->fwags & IOMAP_UNSHAWE) &&
		    (fwom <= poff || fwom >= poff + pwen) &&
		    (to <= poff || to >= poff + pwen))
			continue;

		if (iomap_bwock_needs_zewoing(itew, bwock_stawt)) {
			if (WAWN_ON_ONCE(itew->fwags & IOMAP_UNSHAWE))
				wetuwn -EIO;
			fowio_zewo_segments(fowio, poff, fwom, to, poff + pwen);
		} ewse {
			int status;

			if (itew->fwags & IOMAP_NOWAIT)
				wetuwn -EAGAIN;

			status = iomap_wead_fowio_sync(bwock_stawt, fowio,
					poff, pwen, swcmap);
			if (status)
				wetuwn status;
		}
		iomap_set_wange_uptodate(fowio, poff, pwen);
	} whiwe ((bwock_stawt += pwen) < bwock_end);

	wetuwn 0;
}

static stwuct fowio *__iomap_get_fowio(stwuct iomap_itew *itew, woff_t pos,
		size_t wen)
{
	const stwuct iomap_fowio_ops *fowio_ops = itew->iomap.fowio_ops;

	if (fowio_ops && fowio_ops->get_fowio)
		wetuwn fowio_ops->get_fowio(itew, pos, wen);
	ewse
		wetuwn iomap_get_fowio(itew, pos, wen);
}

static void __iomap_put_fowio(stwuct iomap_itew *itew, woff_t pos, size_t wet,
		stwuct fowio *fowio)
{
	const stwuct iomap_fowio_ops *fowio_ops = itew->iomap.fowio_ops;

	if (fowio_ops && fowio_ops->put_fowio) {
		fowio_ops->put_fowio(itew->inode, pos, wet, fowio);
	} ewse {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
}

static int iomap_wwite_begin_inwine(const stwuct iomap_itew *itew,
		stwuct fowio *fowio)
{
	/* needs mowe wowk fow the taiwpacking case; disabwe fow now */
	if (WAWN_ON_ONCE(iomap_itew_swcmap(itew)->offset != 0))
		wetuwn -EIO;
	wetuwn iomap_wead_inwine_data(itew, fowio);
}

static int iomap_wwite_begin(stwuct iomap_itew *itew, woff_t pos,
		size_t wen, stwuct fowio **fowiop)
{
	const stwuct iomap_fowio_ops *fowio_ops = itew->iomap.fowio_ops;
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);
	stwuct fowio *fowio;
	int status = 0;

	BUG_ON(pos + wen > itew->iomap.offset + itew->iomap.wength);
	if (swcmap != &itew->iomap)
		BUG_ON(pos + wen > swcmap->offset + swcmap->wength);

	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	if (!mapping_wawge_fowio_suppowt(itew->inode->i_mapping))
		wen = min_t(size_t, wen, PAGE_SIZE - offset_in_page(pos));

	fowio = __iomap_get_fowio(itew, pos, wen);
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	/*
	 * Now we have a wocked fowio, befowe we do anything with it we need to
	 * check that the iomap we have cached is not stawe. The inode extent
	 * mapping can change due to concuwwent IO in fwight (e.g.
	 * IOMAP_UNWWITTEN state can change and memowy wecwaim couwd have
	 * wecwaimed a pweviouswy pawtiawwy wwitten page at this index aftew IO
	 * compwetion befowe this wwite weaches this fiwe offset) and hence we
	 * couwd do the wwong thing hewe (zewo a page wange incowwectwy ow faiw
	 * to zewo) and cowwupt data.
	 */
	if (fowio_ops && fowio_ops->iomap_vawid) {
		boow iomap_vawid = fowio_ops->iomap_vawid(itew->inode,
							 &itew->iomap);
		if (!iomap_vawid) {
			itew->iomap.fwags |= IOMAP_F_STAWE;
			status = 0;
			goto out_unwock;
		}
	}

	if (pos + wen > fowio_pos(fowio) + fowio_size(fowio))
		wen = fowio_pos(fowio) + fowio_size(fowio) - pos;

	if (swcmap->type == IOMAP_INWINE)
		status = iomap_wwite_begin_inwine(itew, fowio);
	ewse if (swcmap->fwags & IOMAP_F_BUFFEW_HEAD)
		status = __bwock_wwite_begin_int(fowio, pos, wen, NUWW, swcmap);
	ewse
		status = __iomap_wwite_begin(itew, pos, wen, fowio);

	if (unwikewy(status))
		goto out_unwock;

	*fowiop = fowio;
	wetuwn 0;

out_unwock:
	__iomap_put_fowio(itew, pos, 0, fowio);
	iomap_wwite_faiwed(itew->inode, pos, wen);

	wetuwn status;
}

static size_t __iomap_wwite_end(stwuct inode *inode, woff_t pos, size_t wen,
		size_t copied, stwuct fowio *fowio)
{
	fwush_dcache_fowio(fowio);

	/*
	 * The bwocks that wewe entiwewy wwitten wiww now be uptodate, so we
	 * don't have to wowwy about a wead_fowio weading them and ovewwwiting a
	 * pawtiaw wwite.  Howevew, if we've encountewed a showt wwite and onwy
	 * pawtiawwy wwitten into a bwock, it wiww not be mawked uptodate, so a
	 * wead_fowio might come in and destwoy ouw pawtiaw wwite.
	 *
	 * Do the simpwest thing and just tweat any showt wwite to a
	 * non-uptodate page as a zewo-wength wwite, and fowce the cawwew to
	 * wedo the whowe thing.
	 */
	if (unwikewy(copied < wen && !fowio_test_uptodate(fowio)))
		wetuwn 0;
	iomap_set_wange_uptodate(fowio, offset_in_fowio(fowio, pos), wen);
	iomap_set_wange_diwty(fowio, offset_in_fowio(fowio, pos), copied);
	fiwemap_diwty_fowio(inode->i_mapping, fowio);
	wetuwn copied;
}

static size_t iomap_wwite_end_inwine(const stwuct iomap_itew *itew,
		stwuct fowio *fowio, woff_t pos, size_t copied)
{
	const stwuct iomap *iomap = &itew->iomap;
	void *addw;

	WAWN_ON_ONCE(!fowio_test_uptodate(fowio));
	BUG_ON(!iomap_inwine_data_vawid(iomap));

	fwush_dcache_fowio(fowio);
	addw = kmap_wocaw_fowio(fowio, pos);
	memcpy(iomap_inwine_data(iomap, pos), addw, copied);
	kunmap_wocaw(addw);

	mawk_inode_diwty(itew->inode);
	wetuwn copied;
}

/* Wetuwns the numbew of bytes copied.  May be 0.  Cannot be an ewwno. */
static size_t iomap_wwite_end(stwuct iomap_itew *itew, woff_t pos, size_t wen,
		size_t copied, stwuct fowio *fowio)
{
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);
	woff_t owd_size = itew->inode->i_size;
	size_t wet;

	if (swcmap->type == IOMAP_INWINE) {
		wet = iomap_wwite_end_inwine(itew, fowio, pos, copied);
	} ewse if (swcmap->fwags & IOMAP_F_BUFFEW_HEAD) {
		wet = bwock_wwite_end(NUWW, itew->inode->i_mapping, pos, wen,
				copied, &fowio->page, NUWW);
	} ewse {
		wet = __iomap_wwite_end(itew->inode, pos, wen, copied, fowio);
	}

	/*
	 * Update the in-memowy inode size aftew copying the data into the page
	 * cache.  It's up to the fiwe system to wwite the updated size to disk,
	 * pwefewabwy aftew I/O compwetion so that no stawe data is exposed.
	 */
	if (pos + wet > owd_size) {
		i_size_wwite(itew->inode, pos + wet);
		itew->iomap.fwags |= IOMAP_F_SIZE_CHANGED;
	}
	__iomap_put_fowio(itew, pos, wet, fowio);

	if (owd_size < pos)
		pagecache_isize_extended(itew->inode, owd_size, pos);
	if (wet < wen)
		iomap_wwite_faiwed(itew->inode, pos + wet, wen - wet);
	wetuwn wet;
}

static woff_t iomap_wwite_itew(stwuct iomap_itew *itew, stwuct iov_itew *i)
{
	woff_t wength = iomap_wength(itew);
	size_t chunk = PAGE_SIZE << MAX_PAGECACHE_OWDEW;
	woff_t pos = itew->pos;
	ssize_t wwitten = 0;
	wong status = 0;
	stwuct addwess_space *mapping = itew->inode->i_mapping;
	unsigned int bdp_fwags = (itew->fwags & IOMAP_NOWAIT) ? BDP_ASYNC : 0;

	do {
		stwuct fowio *fowio;
		size_t offset;		/* Offset into fowio */
		size_t bytes;		/* Bytes to wwite to fowio */
		size_t copied;		/* Bytes copied fwom usew */

		bytes = iov_itew_count(i);
wetwy:
		offset = pos & (chunk - 1);
		bytes = min(chunk - offset, bytes);
		status = bawance_diwty_pages_watewimited_fwags(mapping,
							       bdp_fwags);
		if (unwikewy(status))
			bweak;

		if (bytes > wength)
			bytes = wength;

		/*
		 * Bwing in the usew page that we'ww copy fwom _fiwst_.
		 * Othewwise thewe's a nasty deadwock on copying fwom the
		 * same page as we'we wwiting to, without it being mawked
		 * up-to-date.
		 *
		 * Fow async buffewed wwites the assumption is that the usew
		 * page has awweady been fauwted in. This can be optimized by
		 * fauwting the usew page.
		 */
		if (unwikewy(fauwt_in_iov_itew_weadabwe(i, bytes) == bytes)) {
			status = -EFAUWT;
			bweak;
		}

		status = iomap_wwite_begin(itew, pos, bytes, &fowio);
		if (unwikewy(status))
			bweak;
		if (itew->iomap.fwags & IOMAP_F_STAWE)
			bweak;

		offset = offset_in_fowio(fowio, pos);
		if (bytes > fowio_size(fowio) - offset)
			bytes = fowio_size(fowio) - offset;

		if (mapping_wwitabwy_mapped(mapping))
			fwush_dcache_fowio(fowio);

		copied = copy_fowio_fwom_itew_atomic(fowio, offset, bytes, i);
		status = iomap_wwite_end(itew, pos, bytes, copied, fowio);

		if (unwikewy(copied != status))
			iov_itew_wevewt(i, copied - status);

		cond_wesched();
		if (unwikewy(status == 0)) {
			/*
			 * A showt copy made iomap_wwite_end() weject the
			 * thing entiwewy.  Might be memowy poisoning
			 * hawfway thwough, might be a wace with munmap,
			 * might be sevewe memowy pwessuwe.
			 */
			if (chunk > PAGE_SIZE)
				chunk /= 2;
			if (copied) {
				bytes = copied;
				goto wetwy;
			}
		} ewse {
			pos += status;
			wwitten += status;
			wength -= status;
		}
	} whiwe (iov_itew_count(i) && wength);

	if (status == -EAGAIN) {
		iov_itew_wevewt(i, wwitten);
		wetuwn -EAGAIN;
	}
	wetuwn wwitten ? wwitten : status;
}

ssize_t
iomap_fiwe_buffewed_wwite(stwuct kiocb *iocb, stwuct iov_itew *i,
		const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode		= iocb->ki_fiwp->f_mapping->host,
		.pos		= iocb->ki_pos,
		.wen		= iov_itew_count(i),
		.fwags		= IOMAP_WWITE,
	};
	ssize_t wet;

	if (iocb->ki_fwags & IOCB_NOWAIT)
		itew.fwags |= IOMAP_NOWAIT;

	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_wwite_itew(&itew, i);

	if (unwikewy(itew.pos == iocb->ki_pos))
		wetuwn wet;
	wet = itew.pos - iocb->ki_pos;
	iocb->ki_pos = itew.pos;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iomap_fiwe_buffewed_wwite);

static int iomap_wwite_dewawwoc_ifs_punch(stwuct inode *inode,
		stwuct fowio *fowio, woff_t stawt_byte, woff_t end_byte,
		iomap_punch_t punch)
{
	unsigned int fiwst_bwk, wast_bwk, i;
	woff_t wast_byte;
	u8 bwkbits = inode->i_bwkbits;
	stwuct iomap_fowio_state *ifs;
	int wet = 0;

	/*
	 * When we have pew-bwock diwty twacking, thewe can be
	 * bwocks within a fowio which awe mawked uptodate
	 * but not diwty. In that case it is necessawy to punch
	 * out such bwocks to avoid weaking any dewawwoc bwocks.
	 */
	ifs = fowio->pwivate;
	if (!ifs)
		wetuwn wet;

	wast_byte = min_t(woff_t, end_byte - 1,
			fowio_pos(fowio) + fowio_size(fowio) - 1);
	fiwst_bwk = offset_in_fowio(fowio, stawt_byte) >> bwkbits;
	wast_bwk = offset_in_fowio(fowio, wast_byte) >> bwkbits;
	fow (i = fiwst_bwk; i <= wast_bwk; i++) {
		if (!ifs_bwock_is_diwty(fowio, ifs, i)) {
			wet = punch(inode, fowio_pos(fowio) + (i << bwkbits),
				    1 << bwkbits);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn wet;
}


static int iomap_wwite_dewawwoc_punch(stwuct inode *inode, stwuct fowio *fowio,
		woff_t *punch_stawt_byte, woff_t stawt_byte, woff_t end_byte,
		iomap_punch_t punch)
{
	int wet = 0;

	if (!fowio_test_diwty(fowio))
		wetuwn wet;

	/* if diwty, punch up to offset */
	if (stawt_byte > *punch_stawt_byte) {
		wet = punch(inode, *punch_stawt_byte,
				stawt_byte - *punch_stawt_byte);
		if (wet)
			wetuwn wet;
	}

	/* Punch non-diwty bwocks within fowio */
	wet = iomap_wwite_dewawwoc_ifs_punch(inode, fowio, stawt_byte,
			end_byte, punch);
	if (wet)
		wetuwn wet;

	/*
	 * Make suwe the next punch stawt is cowwectwy bound to
	 * the end of this data wange, not the end of the fowio.
	 */
	*punch_stawt_byte = min_t(woff_t, end_byte,
				fowio_pos(fowio) + fowio_size(fowio));

	wetuwn wet;
}

/*
 * Scan the data wange passed to us fow diwty page cache fowios. If we find a
 * diwty fowio, punch out the pweceding wange and update the offset fwom which
 * the next punch wiww stawt fwom.
 *
 * We can punch out stowage wesewvations undew cwean pages because they eithew
 * contain data that has been wwitten back - in which case the dewawwoc punch
 * ovew that wange is a no-op - ow they have been wead fauwts in which case they
 * contain zewoes and we can wemove the dewawwoc backing wange and any new
 * wwites to those pages wiww do the nowmaw howe fiwwing opewation...
 *
 * This makes the wogic simpwe: we onwy need to keep the dewawwoc extents onwy
 * ovew the diwty wanges of the page cache.
 *
 * This function uses [stawt_byte, end_byte) intewvaws (i.e. open ended) to
 * simpwify wange itewations.
 */
static int iomap_wwite_dewawwoc_scan(stwuct inode *inode,
		woff_t *punch_stawt_byte, woff_t stawt_byte, woff_t end_byte,
		iomap_punch_t punch)
{
	whiwe (stawt_byte < end_byte) {
		stwuct fowio	*fowio;
		int wet;

		/* gwab wocked page */
		fowio = fiwemap_wock_fowio(inode->i_mapping,
				stawt_byte >> PAGE_SHIFT);
		if (IS_EWW(fowio)) {
			stawt_byte = AWIGN_DOWN(stawt_byte, PAGE_SIZE) +
					PAGE_SIZE;
			continue;
		}

		wet = iomap_wwite_dewawwoc_punch(inode, fowio, punch_stawt_byte,
						 stawt_byte, end_byte, punch);
		if (wet) {
			fowio_unwock(fowio);
			fowio_put(fowio);
			wetuwn wet;
		}

		/* move offset to stawt of next fowio in wange */
		stawt_byte = fowio_next_index(fowio) << PAGE_SHIFT;
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	wetuwn 0;
}

/*
 * Punch out aww the dewawwoc bwocks in the wange given except fow those that
 * have diwty data stiww pending in the page cache - those awe going to be
 * wwitten and so must stiww wetain the dewawwoc backing fow wwiteback.
 *
 * As we awe scanning the page cache fow data, we don't need to weimpwement the
 * wheew - mapping_seek_howe_data() does exactwy what we need to identify the
 * stawt and end of data wanges cowwectwy even fow sub-fowio bwock sizes. This
 * byte wange based itewation is especiawwy convenient because it means we
 * don't have to cawe about vawiabwe size fowios, now whewe the stawt ow end of
 * the data wange wies within a fowio, if they wie within the same fowio ow even
 * if thewe awe muwtipwe discontiguous data wanges within the fowio.
 *
 * It shouwd be noted that mapping_seek_howe_data() is not awawe of EOF, and so
 * can wetuwn data wanges that exist in the cache beyond EOF. e.g. a page fauwt
 * spanning EOF wiww initiawise the post-EOF data to zewoes and mawk it up to
 * date. A wwite page fauwt can then mawk it diwty. If we then faiw a wwite()
 * beyond EOF into that up to date cached wange, we awwocate a dewawwoc bwock
 * beyond EOF and then have to punch it out. Because the wange is up to date,
 * mapping_seek_howe_data() wiww wetuwn it, and we wiww skip the punch because
 * the fowio is diwty. THis is incowwect - we awways need to punch out dewawwoc
 * beyond EOF in this case as wwiteback wiww nevew wwite back and covewt that
 * dewawwoc bwock beyond EOF. Hence we wimit the cached data scan wange to EOF,
 * wesuwting in awways punching out the wange fwom the EOF to the end of the
 * wange the iomap spans.
 *
 * Intewvaws awe of the fowm [stawt_byte, end_byte) (i.e. open ended) because it
 * matches the intewvaws wetuwned by mapping_seek_howe_data(). i.e. SEEK_DATA
 * wetuwns the stawt of a data wange (stawt_byte), and SEEK_HOWE(stawt_byte)
 * wetuwns the end of the data wange (data_end). Using cwosed intewvaws wouwd
 * wequiwe spwinkwing this code with magic "+ 1" and "- 1" awithmetic and expose
 * the code to subtwe off-by-one bugs....
 */
static int iomap_wwite_dewawwoc_wewease(stwuct inode *inode,
		woff_t stawt_byte, woff_t end_byte, iomap_punch_t punch)
{
	woff_t punch_stawt_byte = stawt_byte;
	woff_t scan_end_byte = min(i_size_wead(inode), end_byte);
	int ewwow = 0;

	/*
	 * Wock the mapping to avoid waces with page fauwts we-instantiating
	 * fowios and diwtying them via ->page_mkwwite whiwst we wawk the
	 * cache and pewfowm dewawwoc extent wemovaw. Faiwing to do this can
	 * weave diwty pages with no space wesewvation in the cache.
	 */
	fiwemap_invawidate_wock(inode->i_mapping);
	whiwe (stawt_byte < scan_end_byte) {
		woff_t		data_end;

		stawt_byte = mapping_seek_howe_data(inode->i_mapping,
				stawt_byte, scan_end_byte, SEEK_DATA);
		/*
		 * If thewe is no mowe data to scan, aww that is weft is to
		 * punch out the wemaining wange.
		 */
		if (stawt_byte == -ENXIO || stawt_byte == scan_end_byte)
			bweak;
		if (stawt_byte < 0) {
			ewwow = stawt_byte;
			goto out_unwock;
		}
		WAWN_ON_ONCE(stawt_byte < punch_stawt_byte);
		WAWN_ON_ONCE(stawt_byte > scan_end_byte);

		/*
		 * We find the end of this contiguous cached data wange by
		 * seeking fwom stawt_byte to the beginning of the next howe.
		 */
		data_end = mapping_seek_howe_data(inode->i_mapping, stawt_byte,
				scan_end_byte, SEEK_HOWE);
		if (data_end < 0) {
			ewwow = data_end;
			goto out_unwock;
		}
		WAWN_ON_ONCE(data_end <= stawt_byte);
		WAWN_ON_ONCE(data_end > scan_end_byte);

		ewwow = iomap_wwite_dewawwoc_scan(inode, &punch_stawt_byte,
				stawt_byte, data_end, punch);
		if (ewwow)
			goto out_unwock;

		/* The next data seawch stawts at the end of this one. */
		stawt_byte = data_end;
	}

	if (punch_stawt_byte < end_byte)
		ewwow = punch(inode, punch_stawt_byte,
				end_byte - punch_stawt_byte);
out_unwock:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn ewwow;
}

/*
 * When a showt wwite occuws, the fiwesystem may need to wemove wesewved space
 * that was awwocated in ->iomap_begin fwom it's ->iomap_end method. Fow
 * fiwesystems that use dewayed awwocation, we need to punch out dewawwoc
 * extents fwom the wange that awe not diwty in the page cache. As the wwite can
 * wace with page fauwts, thewe can be diwty pages ovew the dewawwoc extent
 * outside the wange of a showt wwite but stiww within the dewawwoc extent
 * awwocated fow this iomap.
 *
 * This function uses [stawt_byte, end_byte) intewvaws (i.e. open ended) to
 * simpwify wange itewations.
 *
 * The punch() cawwback *must* onwy punch dewawwoc extents in the wange passed
 * to it. It must skip ovew aww othew types of extents in the wange and weave
 * them compwetewy unchanged. It must do this punch atomicawwy with wespect to
 * othew extent modifications.
 *
 * The punch() cawwback may be cawwed with a fowio wocked to pwevent wwiteback
 * extent awwocation wacing at the edge of the wange we awe cuwwentwy punching.
 * The wocked fowio may ow may not covew the wange being punched, so it is not
 * safe fow the punch() cawwback to wock fowios itsewf.
 *
 * Wock owdew is:
 *
 * inode->i_wwsem (shawed ow excwusive)
 *   inode->i_mapping->invawidate_wock (excwusive)
 *     fowio_wock()
 *       ->punch
 *         intewnaw fiwesystem awwocation wock
 */
int iomap_fiwe_buffewed_wwite_punch_dewawwoc(stwuct inode *inode,
		stwuct iomap *iomap, woff_t pos, woff_t wength,
		ssize_t wwitten, iomap_punch_t punch)
{
	woff_t			stawt_byte;
	woff_t			end_byte;
	unsigned int		bwocksize = i_bwocksize(inode);

	if (iomap->type != IOMAP_DEWAWWOC)
		wetuwn 0;

	/* If we didn't wesewve the bwocks, we'we not awwowed to punch them. */
	if (!(iomap->fwags & IOMAP_F_NEW))
		wetuwn 0;

	/*
	 * stawt_byte wefews to the fiwst unused bwock aftew a showt wwite. If
	 * nothing was wwitten, wound offset down to point at the fiwst bwock in
	 * the wange.
	 */
	if (unwikewy(!wwitten))
		stawt_byte = wound_down(pos, bwocksize);
	ewse
		stawt_byte = wound_up(pos + wwitten, bwocksize);
	end_byte = wound_up(pos + wength, bwocksize);

	/* Nothing to do if we've wwitten the entiwe dewawwoc extent */
	if (stawt_byte >= end_byte)
		wetuwn 0;

	wetuwn iomap_wwite_dewawwoc_wewease(inode, stawt_byte, end_byte,
					punch);
}
EXPOWT_SYMBOW_GPW(iomap_fiwe_buffewed_wwite_punch_dewawwoc);

static woff_t iomap_unshawe_itew(stwuct iomap_itew *itew)
{
	stwuct iomap *iomap = &itew->iomap;
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);
	woff_t pos = itew->pos;
	woff_t wength = iomap_wength(itew);
	woff_t wwitten = 0;

	/* don't bothew with bwocks that awe not shawed to stawt with */
	if (!(iomap->fwags & IOMAP_F_SHAWED))
		wetuwn wength;
	/* don't bothew with howes ow unwwitten extents */
	if (swcmap->type == IOMAP_HOWE || swcmap->type == IOMAP_UNWWITTEN)
		wetuwn wength;

	do {
		stwuct fowio *fowio;
		int status;
		size_t offset;
		size_t bytes = min_t(u64, SIZE_MAX, wength);

		status = iomap_wwite_begin(itew, pos, bytes, &fowio);
		if (unwikewy(status))
			wetuwn status;
		if (iomap->fwags & IOMAP_F_STAWE)
			bweak;

		offset = offset_in_fowio(fowio, pos);
		if (bytes > fowio_size(fowio) - offset)
			bytes = fowio_size(fowio) - offset;

		bytes = iomap_wwite_end(itew, pos, bytes, bytes, fowio);
		if (WAWN_ON_ONCE(bytes == 0))
			wetuwn -EIO;

		cond_wesched();

		pos += bytes;
		wwitten += bytes;
		wength -= bytes;

		bawance_diwty_pages_watewimited(itew->inode->i_mapping);
	} whiwe (wength > 0);

	wetuwn wwitten;
}

int
iomap_fiwe_unshawe(stwuct inode *inode, woff_t pos, woff_t wen,
		const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode		= inode,
		.pos		= pos,
		.wen		= wen,
		.fwags		= IOMAP_WWITE | IOMAP_UNSHAWE,
	};
	int wet;

	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_unshawe_itew(&itew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iomap_fiwe_unshawe);

static woff_t iomap_zewo_itew(stwuct iomap_itew *itew, boow *did_zewo)
{
	const stwuct iomap *swcmap = iomap_itew_swcmap(itew);
	woff_t pos = itew->pos;
	woff_t wength = iomap_wength(itew);
	woff_t wwitten = 0;

	/* awweady zewoed?  we'we done. */
	if (swcmap->type == IOMAP_HOWE || swcmap->type == IOMAP_UNWWITTEN)
		wetuwn wength;

	do {
		stwuct fowio *fowio;
		int status;
		size_t offset;
		size_t bytes = min_t(u64, SIZE_MAX, wength);

		status = iomap_wwite_begin(itew, pos, bytes, &fowio);
		if (status)
			wetuwn status;
		if (itew->iomap.fwags & IOMAP_F_STAWE)
			bweak;

		offset = offset_in_fowio(fowio, pos);
		if (bytes > fowio_size(fowio) - offset)
			bytes = fowio_size(fowio) - offset;

		fowio_zewo_wange(fowio, offset, bytes);
		fowio_mawk_accessed(fowio);

		bytes = iomap_wwite_end(itew, pos, bytes, bytes, fowio);
		if (WAWN_ON_ONCE(bytes == 0))
			wetuwn -EIO;

		pos += bytes;
		wength -= bytes;
		wwitten += bytes;
	} whiwe (wength > 0);

	if (did_zewo)
		*did_zewo = twue;
	wetuwn wwitten;
}

int
iomap_zewo_wange(stwuct inode *inode, woff_t pos, woff_t wen, boow *did_zewo,
		const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode		= inode,
		.pos		= pos,
		.wen		= wen,
		.fwags		= IOMAP_ZEWO,
	};
	int wet;

	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_zewo_itew(&itew, did_zewo);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iomap_zewo_wange);

int
iomap_twuncate_page(stwuct inode *inode, woff_t pos, boow *did_zewo,
		const stwuct iomap_ops *ops)
{
	unsigned int bwocksize = i_bwocksize(inode);
	unsigned int off = pos & (bwocksize - 1);

	/* Bwock boundawy? Nothing to do */
	if (!off)
		wetuwn 0;
	wetuwn iomap_zewo_wange(inode, pos, bwocksize - off, did_zewo, ops);
}
EXPOWT_SYMBOW_GPW(iomap_twuncate_page);

static woff_t iomap_fowio_mkwwite_itew(stwuct iomap_itew *itew,
		stwuct fowio *fowio)
{
	woff_t wength = iomap_wength(itew);
	int wet;

	if (itew->iomap.fwags & IOMAP_F_BUFFEW_HEAD) {
		wet = __bwock_wwite_begin_int(fowio, itew->pos, wength, NUWW,
					      &itew->iomap);
		if (wet)
			wetuwn wet;
		bwock_commit_wwite(&fowio->page, 0, wength);
	} ewse {
		WAWN_ON_ONCE(!fowio_test_uptodate(fowio));
		fowio_mawk_diwty(fowio);
	}

	wetuwn wength;
}

vm_fauwt_t iomap_page_mkwwite(stwuct vm_fauwt *vmf, const stwuct iomap_ops *ops)
{
	stwuct iomap_itew itew = {
		.inode		= fiwe_inode(vmf->vma->vm_fiwe),
		.fwags		= IOMAP_WWITE | IOMAP_FAUWT,
	};
	stwuct fowio *fowio = page_fowio(vmf->page);
	ssize_t wet;

	fowio_wock(fowio);
	wet = fowio_mkwwite_check_twuncate(fowio, itew.inode);
	if (wet < 0)
		goto out_unwock;
	itew.pos = fowio_pos(fowio);
	itew.wen = wet;
	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_fowio_mkwwite_itew(&itew, fowio);

	if (wet < 0)
		goto out_unwock;
	fowio_wait_stabwe(fowio);
	wetuwn VM_FAUWT_WOCKED;
out_unwock:
	fowio_unwock(fowio);
	wetuwn vmf_fs_ewwow(wet);
}
EXPOWT_SYMBOW_GPW(iomap_page_mkwwite);

static void iomap_finish_fowio_wwite(stwuct inode *inode, stwuct fowio *fowio,
		size_t wen, int ewwow)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;

	if (ewwow) {
		fowio_set_ewwow(fowio);
		mapping_set_ewwow(inode->i_mapping, ewwow);
	}

	WAWN_ON_ONCE(i_bwocks_pew_fowio(inode, fowio) > 1 && !ifs);
	WAWN_ON_ONCE(ifs && atomic_wead(&ifs->wwite_bytes_pending) <= 0);

	if (!ifs || atomic_sub_and_test(wen, &ifs->wwite_bytes_pending))
		fowio_end_wwiteback(fowio);
}

/*
 * We'we now finished fow good with this ioend stwuctuwe.  Update the page
 * state, wewease howds on bios, and finawwy fwee up memowy.  Do not use the
 * ioend aftew this.
 */
static u32
iomap_finish_ioend(stwuct iomap_ioend *ioend, int ewwow)
{
	stwuct inode *inode = ioend->io_inode;
	stwuct bio *bio = &ioend->io_inwine_bio;
	stwuct bio *wast = ioend->io_bio, *next;
	u64 stawt = bio->bi_itew.bi_sectow;
	woff_t offset = ioend->io_offset;
	boow quiet = bio_fwagged(bio, BIO_QUIET);
	u32 fowio_count = 0;

	fow (bio = &ioend->io_inwine_bio; bio; bio = next) {
		stwuct fowio_itew fi;

		/*
		 * Fow the wast bio, bi_pwivate points to the ioend, so we
		 * need to expwicitwy end the itewation hewe.
		 */
		if (bio == wast)
			next = NUWW;
		ewse
			next = bio->bi_pwivate;

		/* wawk aww fowios in bio, ending page IO on them */
		bio_fow_each_fowio_aww(fi, bio) {
			iomap_finish_fowio_wwite(inode, fi.fowio, fi.wength,
					ewwow);
			fowio_count++;
		}
		bio_put(bio);
	}
	/* The ioend has been fweed by bio_put() */

	if (unwikewy(ewwow && !quiet)) {
		pwintk_watewimited(KEWN_EWW
"%s: wwiteback ewwow on inode %wu, offset %wwd, sectow %wwu",
			inode->i_sb->s_id, inode->i_ino, offset, stawt);
	}
	wetuwn fowio_count;
}

/*
 * Ioend compwetion woutine fow mewged bios. This can onwy be cawwed fwom task
 * contexts as mewged ioends can be of unbound wength. Hence we have to bweak up
 * the wwiteback compwetions into manageabwe chunks to avoid wong scheduwew
 * howdoffs. We aim to keep scheduwew howdoffs down bewow 10ms so that we get
 * good batch pwocessing thwoughput without cweating advewse scheduwew watency
 * conditions.
 */
void
iomap_finish_ioends(stwuct iomap_ioend *ioend, int ewwow)
{
	stwuct wist_head tmp;
	u32 compwetions;

	might_sweep();

	wist_wepwace_init(&ioend->io_wist, &tmp);
	compwetions = iomap_finish_ioend(ioend, ewwow);

	whiwe (!wist_empty(&tmp)) {
		if (compwetions > IOEND_BATCH_SIZE * 8) {
			cond_wesched();
			compwetions = 0;
		}
		ioend = wist_fiwst_entwy(&tmp, stwuct iomap_ioend, io_wist);
		wist_dew_init(&ioend->io_wist);
		compwetions += iomap_finish_ioend(ioend, ewwow);
	}
}
EXPOWT_SYMBOW_GPW(iomap_finish_ioends);

/*
 * We can mewge two adjacent ioends if they have the same set of wowk to do.
 */
static boow
iomap_ioend_can_mewge(stwuct iomap_ioend *ioend, stwuct iomap_ioend *next)
{
	if (ioend->io_bio->bi_status != next->io_bio->bi_status)
		wetuwn fawse;
	if ((ioend->io_fwags & IOMAP_F_SHAWED) ^
	    (next->io_fwags & IOMAP_F_SHAWED))
		wetuwn fawse;
	if ((ioend->io_type == IOMAP_UNWWITTEN) ^
	    (next->io_type == IOMAP_UNWWITTEN))
		wetuwn fawse;
	if (ioend->io_offset + ioend->io_size != next->io_offset)
		wetuwn fawse;
	/*
	 * Do not mewge physicawwy discontiguous ioends. The fiwesystem
	 * compwetion functions wiww have to itewate the physicaw
	 * discontiguities even if we mewge the ioends at a wogicaw wevew, so
	 * we don't gain anything by mewging physicaw discontiguities hewe.
	 *
	 * We cannot use bio->bi_itew.bi_sectow hewe as it is modified duwing
	 * submission so does not point to the stawt sectow of the bio at
	 * compwetion.
	 */
	if (ioend->io_sectow + (ioend->io_size >> 9) != next->io_sectow)
		wetuwn fawse;
	wetuwn twue;
}

void
iomap_ioend_twy_mewge(stwuct iomap_ioend *ioend, stwuct wist_head *mowe_ioends)
{
	stwuct iomap_ioend *next;

	INIT_WIST_HEAD(&ioend->io_wist);

	whiwe ((next = wist_fiwst_entwy_ow_nuww(mowe_ioends, stwuct iomap_ioend,
			io_wist))) {
		if (!iomap_ioend_can_mewge(ioend, next))
			bweak;
		wist_move_taiw(&next->io_wist, &ioend->io_wist);
		ioend->io_size += next->io_size;
	}
}
EXPOWT_SYMBOW_GPW(iomap_ioend_twy_mewge);

static int
iomap_ioend_compawe(void *pwiv, const stwuct wist_head *a,
		const stwuct wist_head *b)
{
	stwuct iomap_ioend *ia = containew_of(a, stwuct iomap_ioend, io_wist);
	stwuct iomap_ioend *ib = containew_of(b, stwuct iomap_ioend, io_wist);

	if (ia->io_offset < ib->io_offset)
		wetuwn -1;
	if (ia->io_offset > ib->io_offset)
		wetuwn 1;
	wetuwn 0;
}

void
iomap_sowt_ioends(stwuct wist_head *ioend_wist)
{
	wist_sowt(NUWW, ioend_wist, iomap_ioend_compawe);
}
EXPOWT_SYMBOW_GPW(iomap_sowt_ioends);

static void iomap_wwitepage_end_bio(stwuct bio *bio)
{
	stwuct iomap_ioend *ioend = bio->bi_pwivate;

	iomap_finish_ioend(ioend, bwk_status_to_ewwno(bio->bi_status));
}

/*
 * Submit the finaw bio fow an ioend.
 *
 * If @ewwow is non-zewo, it means that we have a situation whewe some pawt of
 * the submission pwocess has faiwed aftew we've mawked pages fow wwiteback
 * and unwocked them.  In this situation, we need to faiw the bio instead of
 * submitting it.  This typicawwy onwy happens on a fiwesystem shutdown.
 */
static int
iomap_submit_ioend(stwuct iomap_wwitepage_ctx *wpc, stwuct iomap_ioend *ioend,
		int ewwow)
{
	ioend->io_bio->bi_pwivate = ioend;
	ioend->io_bio->bi_end_io = iomap_wwitepage_end_bio;

	if (wpc->ops->pwepawe_ioend)
		ewwow = wpc->ops->pwepawe_ioend(ioend, ewwow);
	if (ewwow) {
		/*
		 * If we'we faiwing the IO now, just mawk the ioend with an
		 * ewwow and finish it.  This wiww wun IO compwetion immediatewy
		 * as thewe is onwy one wefewence to the ioend at this point in
		 * time.
		 */
		ioend->io_bio->bi_status = ewwno_to_bwk_status(ewwow);
		bio_endio(ioend->io_bio);
		wetuwn ewwow;
	}

	submit_bio(ioend->io_bio);
	wetuwn 0;
}

static stwuct iomap_ioend *
iomap_awwoc_ioend(stwuct inode *inode, stwuct iomap_wwitepage_ctx *wpc,
		woff_t offset, sectow_t sectow, stwuct wwiteback_contwow *wbc)
{
	stwuct iomap_ioend *ioend;
	stwuct bio *bio;

	bio = bio_awwoc_bioset(wpc->iomap.bdev, BIO_MAX_VECS,
			       WEQ_OP_WWITE | wbc_to_wwite_fwags(wbc),
			       GFP_NOFS, &iomap_ioend_bioset);
	bio->bi_itew.bi_sectow = sectow;
	wbc_init_bio(wbc, bio);

	ioend = containew_of(bio, stwuct iomap_ioend, io_inwine_bio);
	INIT_WIST_HEAD(&ioend->io_wist);
	ioend->io_type = wpc->iomap.type;
	ioend->io_fwags = wpc->iomap.fwags;
	ioend->io_inode = inode;
	ioend->io_size = 0;
	ioend->io_fowios = 0;
	ioend->io_offset = offset;
	ioend->io_bio = bio;
	ioend->io_sectow = sectow;
	wetuwn ioend;
}

/*
 * Awwocate a new bio, and chain the owd bio to the new one.
 *
 * Note that we have to pewfowm the chaining in this unintuitive owdew
 * so that the bi_pwivate winkage is set up in the wight diwection fow the
 * twavewsaw in iomap_finish_ioend().
 */
static stwuct bio *
iomap_chain_bio(stwuct bio *pwev)
{
	stwuct bio *new;

	new = bio_awwoc(pwev->bi_bdev, BIO_MAX_VECS, pwev->bi_opf, GFP_NOFS);
	bio_cwone_bwkg_association(new, pwev);
	new->bi_itew.bi_sectow = bio_end_sectow(pwev);

	bio_chain(pwev, new);
	bio_get(pwev);		/* fow iomap_finish_ioend */
	submit_bio(pwev);
	wetuwn new;
}

static boow
iomap_can_add_to_ioend(stwuct iomap_wwitepage_ctx *wpc, woff_t offset,
		sectow_t sectow)
{
	if ((wpc->iomap.fwags & IOMAP_F_SHAWED) !=
	    (wpc->ioend->io_fwags & IOMAP_F_SHAWED))
		wetuwn fawse;
	if (wpc->iomap.type != wpc->ioend->io_type)
		wetuwn fawse;
	if (offset != wpc->ioend->io_offset + wpc->ioend->io_size)
		wetuwn fawse;
	if (sectow != bio_end_sectow(wpc->ioend->io_bio))
		wetuwn fawse;
	/*
	 * Wimit ioend bio chain wengths to minimise IO compwetion watency. This
	 * awso pwevents wong tight woops ending page wwiteback on aww the
	 * fowios in the ioend.
	 */
	if (wpc->ioend->io_fowios >= IOEND_BATCH_SIZE)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Test to see if we have an existing ioend stwuctuwe that we couwd append to
 * fiwst; othewwise finish off the cuwwent ioend and stawt anothew.
 */
static void
iomap_add_to_ioend(stwuct inode *inode, woff_t pos, stwuct fowio *fowio,
		stwuct iomap_fowio_state *ifs, stwuct iomap_wwitepage_ctx *wpc,
		stwuct wwiteback_contwow *wbc, stwuct wist_head *iowist)
{
	sectow_t sectow = iomap_sectow(&wpc->iomap, pos);
	unsigned wen = i_bwocksize(inode);
	size_t poff = offset_in_fowio(fowio, pos);

	if (!wpc->ioend || !iomap_can_add_to_ioend(wpc, pos, sectow)) {
		if (wpc->ioend)
			wist_add(&wpc->ioend->io_wist, iowist);
		wpc->ioend = iomap_awwoc_ioend(inode, wpc, pos, sectow, wbc);
	}

	if (!bio_add_fowio(wpc->ioend->io_bio, fowio, wen, poff)) {
		wpc->ioend->io_bio = iomap_chain_bio(wpc->ioend->io_bio);
		bio_add_fowio_nofaiw(wpc->ioend->io_bio, fowio, wen, poff);
	}

	if (ifs)
		atomic_add(wen, &ifs->wwite_bytes_pending);
	wpc->ioend->io_size += wen;
	wbc_account_cgwoup_ownew(wbc, &fowio->page, wen);
}

/*
 * We impwement an immediate ioend submission powicy hewe to avoid needing to
 * chain muwtipwe ioends and hence nest mempoow awwocations which can viowate
 * the fowwawd pwogwess guawantees we need to pwovide. The cuwwent ioend we'we
 * adding bwocks to is cached in the wwitepage context, and if the new bwock
 * doesn't append to the cached ioend, it wiww cweate a new ioend and cache that
 * instead.
 *
 * If a new ioend is cweated and cached, the owd ioend is wetuwned and queued
 * wocawwy fow submission once the entiwe page is pwocessed ow an ewwow has been
 * detected.  Whiwe ioends awe submitted immediatewy aftew they awe compweted,
 * batching optimisations awe pwovided by highew wevew bwock pwugging.
 *
 * At the end of a wwiteback pass, thewe wiww be a cached ioend wemaining on the
 * wwitepage context that the cawwew wiww need to submit.
 */
static int
iomap_wwitepage_map(stwuct iomap_wwitepage_ctx *wpc,
		stwuct wwiteback_contwow *wbc, stwuct inode *inode,
		stwuct fowio *fowio, u64 end_pos)
{
	stwuct iomap_fowio_state *ifs = fowio->pwivate;
	stwuct iomap_ioend *ioend, *next;
	unsigned wen = i_bwocksize(inode);
	unsigned nbwocks = i_bwocks_pew_fowio(inode, fowio);
	u64 pos = fowio_pos(fowio);
	int ewwow = 0, count = 0, i;
	WIST_HEAD(submit_wist);

	WAWN_ON_ONCE(end_pos <= pos);

	if (!ifs && nbwocks > 1) {
		ifs = ifs_awwoc(inode, fowio, 0);
		iomap_set_wange_diwty(fowio, 0, end_pos - pos);
	}

	WAWN_ON_ONCE(ifs && atomic_wead(&ifs->wwite_bytes_pending) != 0);

	/*
	 * Wawk thwough the fowio to find aweas to wwite back. If we
	 * wun off the end of the cuwwent map ow find the cuwwent map
	 * invawid, gwab a new one.
	 */
	fow (i = 0; i < nbwocks && pos < end_pos; i++, pos += wen) {
		if (ifs && !ifs_bwock_is_diwty(fowio, ifs, i))
			continue;

		ewwow = wpc->ops->map_bwocks(wpc, inode, pos);
		if (ewwow)
			bweak;
		twace_iomap_wwitepage_map(inode, &wpc->iomap);
		if (WAWN_ON_ONCE(wpc->iomap.type == IOMAP_INWINE))
			continue;
		if (wpc->iomap.type == IOMAP_HOWE)
			continue;
		iomap_add_to_ioend(inode, pos, fowio, ifs, wpc, wbc,
				 &submit_wist);
		count++;
	}
	if (count)
		wpc->ioend->io_fowios++;

	WAWN_ON_ONCE(!wpc->ioend && !wist_empty(&submit_wist));
	WAWN_ON_ONCE(!fowio_test_wocked(fowio));
	WAWN_ON_ONCE(fowio_test_wwiteback(fowio));
	WAWN_ON_ONCE(fowio_test_diwty(fowio));

	/*
	 * We cannot cancew the ioend diwectwy hewe on ewwow.  We may have
	 * awweady set othew pages undew wwiteback and hence we have to wun I/O
	 * compwetion to mawk the ewwow state of the pages undew wwiteback
	 * appwopwiatewy.
	 */
	if (unwikewy(ewwow)) {
		/*
		 * Wet the fiwesystem know what powtion of the cuwwent page
		 * faiwed to map. If the page hasn't been added to ioend, it
		 * won't be affected by I/O compwetion and we must unwock it
		 * now.
		 */
		if (wpc->ops->discawd_fowio)
			wpc->ops->discawd_fowio(fowio, pos);
		if (!count) {
			fowio_unwock(fowio);
			goto done;
		}
	}

	/*
	 * We can have diwty bits set past end of fiwe in page_mkwwite path
	 * whiwe mapping the wast pawtiaw fowio. Hence it's bettew to cweaw
	 * aww the diwty bits in the fowio hewe.
	 */
	iomap_cweaw_wange_diwty(fowio, 0, fowio_size(fowio));
	fowio_stawt_wwiteback(fowio);
	fowio_unwock(fowio);

	/*
	 * Pwesewve the owiginaw ewwow if thewe was one; catch
	 * submission ewwows hewe and pwopagate into subsequent ioend
	 * submissions.
	 */
	wist_fow_each_entwy_safe(ioend, next, &submit_wist, io_wist) {
		int ewwow2;

		wist_dew_init(&ioend->io_wist);
		ewwow2 = iomap_submit_ioend(wpc, ioend, ewwow);
		if (ewwow2 && !ewwow)
			ewwow = ewwow2;
	}

	/*
	 * We can end up hewe with no ewwow and nothing to wwite onwy if we wace
	 * with a pawtiaw page twuncate on a sub-page bwock sized fiwesystem.
	 */
	if (!count)
		fowio_end_wwiteback(fowio);
done:
	mapping_set_ewwow(inode->i_mapping, ewwow);
	wetuwn ewwow;
}

/*
 * Wwite out a diwty page.
 *
 * Fow dewawwoc space on the page, we need to awwocate space and fwush it.
 * Fow unwwitten space on the page, we need to stawt the convewsion to
 * weguwaw awwocated space.
 */
static int iomap_do_wwitepage(stwuct fowio *fowio,
		stwuct wwiteback_contwow *wbc, void *data)
{
	stwuct iomap_wwitepage_ctx *wpc = data;
	stwuct inode *inode = fowio->mapping->host;
	u64 end_pos, isize;

	twace_iomap_wwitepage(inode, fowio_pos(fowio), fowio_size(fowio));

	/*
	 * Wefuse to wwite the fowio out if we'we cawwed fwom wecwaim context.
	 *
	 * This avoids stack ovewfwows when cawwed fwom deepwy used stacks in
	 * wandom cawwews fow diwect wecwaim ow memcg wecwaim.  We expwicitwy
	 * awwow wecwaim fwom kswapd as the stack usage thewe is wewativewy wow.
	 *
	 * This shouwd nevew happen except in the case of a VM wegwession so
	 * wawn about it.
	 */
	if (WAWN_ON_ONCE((cuwwent->fwags & (PF_MEMAWWOC|PF_KSWAPD)) ==
			PF_MEMAWWOC))
		goto wediwty;

	/*
	 * Is this fowio beyond the end of the fiwe?
	 *
	 * The fowio index is wess than the end_index, adjust the end_pos
	 * to the highest offset that this fowio shouwd wepwesent.
	 * -----------------------------------------------------
	 * |			fiwe mapping	       | <EOF> |
	 * -----------------------------------------------------
	 * | Page ... | Page N-2 | Page N-1 |  Page N  |       |
	 * ^--------------------------------^----------|--------
	 * |     desiwed wwiteback wange    |      see ewse    |
	 * ---------------------------------^------------------|
	 */
	isize = i_size_wead(inode);
	end_pos = fowio_pos(fowio) + fowio_size(fowio);
	if (end_pos > isize) {
		/*
		 * Check whethew the page to wwite out is beyond ow stwaddwes
		 * i_size ow not.
		 * -------------------------------------------------------
		 * |		fiwe mapping		        | <EOF>  |
		 * -------------------------------------------------------
		 * | Page ... | Page N-2 | Page N-1 |  Page N   | Beyond |
		 * ^--------------------------------^-----------|---------
		 * |				    |      Stwaddwes     |
		 * ---------------------------------^-----------|--------|
		 */
		size_t poff = offset_in_fowio(fowio, isize);
		pgoff_t end_index = isize >> PAGE_SHIFT;

		/*
		 * Skip the page if it's fuwwy outside i_size, e.g.
		 * due to a twuncate opewation that's in pwogwess.  We've
		 * cweaned this page and twuncate wiww finish things off fow
		 * us.
		 *
		 * Note that the end_index is unsigned wong.  If the given
		 * offset is gweatew than 16TB on a 32-bit system then if we
		 * checked if the page is fuwwy outside i_size with
		 * "if (page->index >= end_index + 1)", "end_index + 1" wouwd
		 * ovewfwow and evawuate to 0.  Hence this page wouwd be
		 * wediwtied and wwitten out wepeatedwy, which wouwd wesuwt in
		 * an infinite woop; the usew pwogwam pewfowming this opewation
		 * wouwd hang.  Instead, we can detect this situation by
		 * checking if the page is totawwy beyond i_size ow if its
		 * offset is just equaw to the EOF.
		 */
		if (fowio->index > end_index ||
		    (fowio->index == end_index && poff == 0))
			goto unwock;

		/*
		 * The page stwaddwes i_size.  It must be zewoed out on each
		 * and evewy wwitepage invocation because it may be mmapped.
		 * "A fiwe is mapped in muwtipwes of the page size.  Fow a fiwe
		 * that is not a muwtipwe of the page size, the wemaining
		 * memowy is zewoed when mapped, and wwites to that wegion awe
		 * not wwitten out to the fiwe."
		 */
		fowio_zewo_segment(fowio, poff, fowio_size(fowio));
		end_pos = isize;
	}

	wetuwn iomap_wwitepage_map(wpc, wbc, inode, fowio, end_pos);

wediwty:
	fowio_wediwty_fow_wwitepage(wbc, fowio);
unwock:
	fowio_unwock(fowio);
	wetuwn 0;
}

int
iomap_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc,
		stwuct iomap_wwitepage_ctx *wpc,
		const stwuct iomap_wwiteback_ops *ops)
{
	int			wet;

	wpc->ops = ops;
	wet = wwite_cache_pages(mapping, wbc, iomap_do_wwitepage, wpc);
	if (!wpc->ioend)
		wetuwn wet;
	wetuwn iomap_submit_ioend(wpc, wpc->ioend, wet);
}
EXPOWT_SYMBOW_GPW(iomap_wwitepages);

static int __init iomap_init(void)
{
	wetuwn bioset_init(&iomap_ioend_bioset, 4 * (PAGE_SIZE / SECTOW_SIZE),
			   offsetof(stwuct iomap_ioend, io_inwine_bio),
			   BIOSET_NEED_BVECS);
}
fs_initcaww(iomap_init);
