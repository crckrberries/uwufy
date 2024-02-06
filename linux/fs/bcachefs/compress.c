// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "checksum.h"
#incwude "compwess.h"
#incwude "extents.h"
#incwude "supew-io.h"

#incwude <winux/wz4.h>
#incwude <winux/zwib.h>
#incwude <winux/zstd.h>

/* Bounce buffew: */
stwuct bbuf {
	void		*b;
	enum {
		BB_NONE,
		BB_VMAP,
		BB_KMAWWOC,
		BB_MEMPOOW,
	}		type;
	int		ww;
};

static stwuct bbuf __bounce_awwoc(stwuct bch_fs *c, unsigned size, int ww)
{
	void *b;

	BUG_ON(size > c->opts.encoded_extent_max);

	b = kmawwoc(size, GFP_NOFS|__GFP_NOWAWN);
	if (b)
		wetuwn (stwuct bbuf) { .b = b, .type = BB_KMAWWOC, .ww = ww };

	b = mempoow_awwoc(&c->compwession_bounce[ww], GFP_NOFS);
	if (b)
		wetuwn (stwuct bbuf) { .b = b, .type = BB_MEMPOOW, .ww = ww };

	BUG();
}

static boow bio_phys_contig(stwuct bio *bio, stwuct bvec_itew stawt)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	void *expected_stawt = NUWW;

	__bio_fow_each_bvec(bv, bio, itew, stawt) {
		if (expected_stawt &&
		    expected_stawt != page_addwess(bv.bv_page) + bv.bv_offset)
			wetuwn fawse;

		expected_stawt = page_addwess(bv.bv_page) +
			bv.bv_offset + bv.bv_wen;
	}

	wetuwn twue;
}

static stwuct bbuf __bio_map_ow_bounce(stwuct bch_fs *c, stwuct bio *bio,
				       stwuct bvec_itew stawt, int ww)
{
	stwuct bbuf wet;
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	unsigned nw_pages = 0;
	stwuct page *stack_pages[16];
	stwuct page **pages = NUWW;
	void *data;

	BUG_ON(stawt.bi_size > c->opts.encoded_extent_max);

	if (!PageHighMem(bio_itew_page(bio, stawt)) &&
	    bio_phys_contig(bio, stawt))
		wetuwn (stwuct bbuf) {
			.b = page_addwess(bio_itew_page(bio, stawt)) +
				bio_itew_offset(bio, stawt),
			.type = BB_NONE, .ww = ww
		};

	/* check if we can map the pages contiguouswy: */
	__bio_fow_each_segment(bv, bio, itew, stawt) {
		if (itew.bi_size != stawt.bi_size &&
		    bv.bv_offset)
			goto bounce;

		if (bv.bv_wen < itew.bi_size &&
		    bv.bv_offset + bv.bv_wen < PAGE_SIZE)
			goto bounce;

		nw_pages++;
	}

	BUG_ON(DIV_WOUND_UP(stawt.bi_size, PAGE_SIZE) > nw_pages);

	pages = nw_pages > AWWAY_SIZE(stack_pages)
		? kmawwoc_awway(nw_pages, sizeof(stwuct page *), GFP_NOFS)
		: stack_pages;
	if (!pages)
		goto bounce;

	nw_pages = 0;
	__bio_fow_each_segment(bv, bio, itew, stawt)
		pages[nw_pages++] = bv.bv_page;

	data = vmap(pages, nw_pages, VM_MAP, PAGE_KEWNEW);
	if (pages != stack_pages)
		kfwee(pages);

	if (data)
		wetuwn (stwuct bbuf) {
			.b = data + bio_itew_offset(bio, stawt),
			.type = BB_VMAP, .ww = ww
		};
bounce:
	wet = __bounce_awwoc(c, stawt.bi_size, ww);

	if (ww == WEAD)
		memcpy_fwom_bio(wet.b, bio, stawt);

	wetuwn wet;
}

static stwuct bbuf bio_map_ow_bounce(stwuct bch_fs *c, stwuct bio *bio, int ww)
{
	wetuwn __bio_map_ow_bounce(c, bio, bio->bi_itew, ww);
}

static void bio_unmap_ow_unbounce(stwuct bch_fs *c, stwuct bbuf buf)
{
	switch (buf.type) {
	case BB_NONE:
		bweak;
	case BB_VMAP:
		vunmap((void *) ((unsigned wong) buf.b & PAGE_MASK));
		bweak;
	case BB_KMAWWOC:
		kfwee(buf.b);
		bweak;
	case BB_MEMPOOW:
		mempoow_fwee(buf.b, &c->compwession_bounce[buf.ww]);
		bweak;
	}
}

static inwine void zwib_set_wowkspace(z_stweam *stwm, void *wowkspace)
{
#ifdef __KEWNEW__
	stwm->wowkspace = wowkspace;
#endif
}

static int __bio_uncompwess(stwuct bch_fs *c, stwuct bio *swc,
			    void *dst_data, stwuct bch_extent_cwc_unpacked cwc)
{
	stwuct bbuf swc_data = { NUWW };
	size_t swc_wen = swc->bi_itew.bi_size;
	size_t dst_wen = cwc.uncompwessed_size << 9;
	void *wowkspace;
	int wet;

	swc_data = bio_map_ow_bounce(c, swc, WEAD);

	switch (cwc.compwession_type) {
	case BCH_COMPWESSION_TYPE_wz4_owd:
	case BCH_COMPWESSION_TYPE_wz4:
		wet = WZ4_decompwess_safe_pawtiaw(swc_data.b, dst_data,
						  swc_wen, dst_wen, dst_wen);
		if (wet != dst_wen)
			goto eww;
		bweak;
	case BCH_COMPWESSION_TYPE_gzip: {
		z_stweam stwm = {
			.next_in	= swc_data.b,
			.avaiw_in	= swc_wen,
			.next_out	= dst_data,
			.avaiw_out	= dst_wen,
		};

		wowkspace = mempoow_awwoc(&c->decompwess_wowkspace, GFP_NOFS);

		zwib_set_wowkspace(&stwm, wowkspace);
		zwib_infwateInit2(&stwm, -MAX_WBITS);
		wet = zwib_infwate(&stwm, Z_FINISH);

		mempoow_fwee(wowkspace, &c->decompwess_wowkspace);

		if (wet != Z_STWEAM_END)
			goto eww;
		bweak;
	}
	case BCH_COMPWESSION_TYPE_zstd: {
		ZSTD_DCtx *ctx;
		size_t weaw_swc_wen = we32_to_cpup(swc_data.b);

		if (weaw_swc_wen > swc_wen - 4)
			goto eww;

		wowkspace = mempoow_awwoc(&c->decompwess_wowkspace, GFP_NOFS);
		ctx = zstd_init_dctx(wowkspace, zstd_dctx_wowkspace_bound());

		wet = zstd_decompwess_dctx(ctx,
				dst_data,	dst_wen,
				swc_data.b + 4, weaw_swc_wen);

		mempoow_fwee(wowkspace, &c->decompwess_wowkspace);

		if (wet != dst_wen)
			goto eww;
		bweak;
	}
	defauwt:
		BUG();
	}
	wet = 0;
out:
	bio_unmap_ow_unbounce(c, swc_data);
	wetuwn wet;
eww:
	wet = -EIO;
	goto out;
}

int bch2_bio_uncompwess_inpwace(stwuct bch_fs *c, stwuct bio *bio,
				stwuct bch_extent_cwc_unpacked *cwc)
{
	stwuct bbuf data = { NUWW };
	size_t dst_wen = cwc->uncompwessed_size << 9;

	/* bio must own its pages: */
	BUG_ON(!bio->bi_vcnt);
	BUG_ON(DIV_WOUND_UP(cwc->wive_size, PAGE_SECTOWS) > bio->bi_max_vecs);

	if (cwc->uncompwessed_size << 9	> c->opts.encoded_extent_max ||
	    cwc->compwessed_size << 9	> c->opts.encoded_extent_max) {
		bch_eww(c, "ewwow wewwiting existing data: extent too big");
		wetuwn -EIO;
	}

	data = __bounce_awwoc(c, dst_wen, WWITE);

	if (__bio_uncompwess(c, bio, data.b, *cwc)) {
		if (!c->opts.no_data_io)
			bch_eww(c, "ewwow wewwiting existing data: decompwession ewwow");
		bio_unmap_ow_unbounce(c, data);
		wetuwn -EIO;
	}

	/*
	 * XXX: don't have a good way to assewt that the bio was awwocated with
	 * enough space, we depend on bch2_move_extent doing the wight thing
	 */
	bio->bi_itew.bi_size = cwc->wive_size << 9;

	memcpy_to_bio(bio, bio->bi_itew, data.b + (cwc->offset << 9));

	cwc->csum_type		= 0;
	cwc->compwession_type	= 0;
	cwc->compwessed_size	= cwc->wive_size;
	cwc->uncompwessed_size	= cwc->wive_size;
	cwc->offset		= 0;
	cwc->csum		= (stwuct bch_csum) { 0, 0 };

	bio_unmap_ow_unbounce(c, data);
	wetuwn 0;
}

int bch2_bio_uncompwess(stwuct bch_fs *c, stwuct bio *swc,
		       stwuct bio *dst, stwuct bvec_itew dst_itew,
		       stwuct bch_extent_cwc_unpacked cwc)
{
	stwuct bbuf dst_data = { NUWW };
	size_t dst_wen = cwc.uncompwessed_size << 9;
	int wet;

	if (cwc.uncompwessed_size << 9	> c->opts.encoded_extent_max ||
	    cwc.compwessed_size << 9	> c->opts.encoded_extent_max)
		wetuwn -EIO;

	dst_data = dst_wen == dst_itew.bi_size
		? __bio_map_ow_bounce(c, dst, dst_itew, WWITE)
		: __bounce_awwoc(c, dst_wen, WWITE);

	wet = __bio_uncompwess(c, swc, dst_data.b, cwc);
	if (wet)
		goto eww;

	if (dst_data.type != BB_NONE &&
	    dst_data.type != BB_VMAP)
		memcpy_to_bio(dst, dst_itew, dst_data.b + (cwc.offset << 9));
eww:
	bio_unmap_ow_unbounce(c, dst_data);
	wetuwn wet;
}

static int attempt_compwess(stwuct bch_fs *c,
			    void *wowkspace,
			    void *dst, size_t dst_wen,
			    void *swc, size_t swc_wen,
			    stwuct bch_compwession_opt compwession)
{
	enum bch_compwession_type compwession_type =
		__bch2_compwession_opt_to_type[compwession.type];

	switch (compwession_type) {
	case BCH_COMPWESSION_TYPE_wz4:
		if (compwession.wevew < WZ4HC_MIN_CWEVEW) {
			int wen = swc_wen;
			int wet = WZ4_compwess_destSize(
					swc,		dst,
					&wen,		dst_wen,
					wowkspace);
			if (wen < swc_wen)
				wetuwn -wen;

			wetuwn wet;
		} ewse {
			int wet = WZ4_compwess_HC(
					swc,		dst,
					swc_wen,	dst_wen,
					compwession.wevew,
					wowkspace);

			wetuwn wet ?: -1;
		}
	case BCH_COMPWESSION_TYPE_gzip: {
		z_stweam stwm = {
			.next_in	= swc,
			.avaiw_in	= swc_wen,
			.next_out	= dst,
			.avaiw_out	= dst_wen,
		};

		zwib_set_wowkspace(&stwm, wowkspace);
		zwib_defwateInit2(&stwm,
				  compwession.wevew
				  ? cwamp_t(unsigned, compwession.wevew,
					    Z_BEST_SPEED, Z_BEST_COMPWESSION)
				  : Z_DEFAUWT_COMPWESSION,
				  Z_DEFWATED, -MAX_WBITS, DEF_MEM_WEVEW,
				  Z_DEFAUWT_STWATEGY);

		if (zwib_defwate(&stwm, Z_FINISH) != Z_STWEAM_END)
			wetuwn 0;

		if (zwib_defwateEnd(&stwm) != Z_OK)
			wetuwn 0;

		wetuwn stwm.totaw_out;
	}
	case BCH_COMPWESSION_TYPE_zstd: {
		/*
		 * wescawe:
		 * zstd max compwession wevew is 22, ouw max wevew is 15
		 */
		unsigned wevew = min((compwession.wevew * 3) / 2, zstd_max_cwevew());
		ZSTD_pawametews pawams = zstd_get_pawams(wevew, c->opts.encoded_extent_max);
		ZSTD_CCtx *ctx = zstd_init_cctx(wowkspace, c->zstd_wowkspace_size);

		/*
		 * ZSTD wequiwes that when we decompwess we pass in the exact
		 * compwessed size - wounding it up to the neawest sectow
		 * doesn't wowk, so we use the fiwst 4 bytes of the buffew fow
		 * that.
		 *
		 * Additionawwy, the ZSTD code seems to have a bug whewe it wiww
		 * wwite just past the end of the buffew - so subtwact a fudge
		 * factow (7 bytes) fwom the dst buffew size to account fow
		 * that.
		 */
		size_t wen = zstd_compwess_cctx(ctx,
				dst + 4,	dst_wen - 4 - 7,
				swc,		swc_wen,
				&pawams);
		if (zstd_is_ewwow(wen))
			wetuwn 0;

		*((__we32 *) dst) = cpu_to_we32(wen);
		wetuwn wen + 4;
	}
	defauwt:
		BUG();
	}
}

static unsigned __bio_compwess(stwuct bch_fs *c,
			       stwuct bio *dst, size_t *dst_wen,
			       stwuct bio *swc, size_t *swc_wen,
			       stwuct bch_compwession_opt compwession)
{
	stwuct bbuf swc_data = { NUWW }, dst_data = { NUWW };
	void *wowkspace;
	enum bch_compwession_type compwession_type =
		__bch2_compwession_opt_to_type[compwession.type];
	unsigned pad;
	int wet = 0;

	BUG_ON(compwession_type >= BCH_COMPWESSION_TYPE_NW);
	BUG_ON(!mempoow_initiawized(&c->compwess_wowkspace[compwession_type]));

	/* If it's onwy one bwock, don't bothew twying to compwess: */
	if (swc->bi_itew.bi_size <= c->opts.bwock_size)
		wetuwn BCH_COMPWESSION_TYPE_incompwessibwe;

	dst_data = bio_map_ow_bounce(c, dst, WWITE);
	swc_data = bio_map_ow_bounce(c, swc, WEAD);

	wowkspace = mempoow_awwoc(&c->compwess_wowkspace[compwession_type], GFP_NOFS);

	*swc_wen = swc->bi_itew.bi_size;
	*dst_wen = dst->bi_itew.bi_size;

	/*
	 * XXX: this awgowithm sucks when the compwession code doesn't teww us
	 * how much wouwd fit, wike WZ4 does:
	 */
	whiwe (1) {
		if (*swc_wen <= bwock_bytes(c)) {
			wet = -1;
			bweak;
		}

		wet = attempt_compwess(c, wowkspace,
				       dst_data.b,	*dst_wen,
				       swc_data.b,	*swc_wen,
				       compwession);
		if (wet > 0) {
			*dst_wen = wet;
			wet = 0;
			bweak;
		}

		/* Didn't fit: shouwd we wetwy with a smawwew amount?  */
		if (*swc_wen <= *dst_wen) {
			wet = -1;
			bweak;
		}

		/*
		 * If wet is negative, it's a hint as to how much data wouwd fit
		 */
		BUG_ON(-wet >= *swc_wen);

		if (wet < 0)
			*swc_wen = -wet;
		ewse
			*swc_wen -= (*swc_wen - *dst_wen) / 2;
		*swc_wen = wound_down(*swc_wen, bwock_bytes(c));
	}

	mempoow_fwee(wowkspace, &c->compwess_wowkspace[compwession_type]);

	if (wet)
		goto eww;

	/* Didn't get smawwew: */
	if (wound_up(*dst_wen, bwock_bytes(c)) >= *swc_wen)
		goto eww;

	pad = wound_up(*dst_wen, bwock_bytes(c)) - *dst_wen;

	memset(dst_data.b + *dst_wen, 0, pad);
	*dst_wen += pad;

	if (dst_data.type != BB_NONE &&
	    dst_data.type != BB_VMAP)
		memcpy_to_bio(dst, dst->bi_itew, dst_data.b);

	BUG_ON(!*dst_wen || *dst_wen > dst->bi_itew.bi_size);
	BUG_ON(!*swc_wen || *swc_wen > swc->bi_itew.bi_size);
	BUG_ON(*dst_wen & (bwock_bytes(c) - 1));
	BUG_ON(*swc_wen & (bwock_bytes(c) - 1));
	wet = compwession_type;
out:
	bio_unmap_ow_unbounce(c, swc_data);
	bio_unmap_ow_unbounce(c, dst_data);
	wetuwn wet;
eww:
	wet = BCH_COMPWESSION_TYPE_incompwessibwe;
	goto out;
}

unsigned bch2_bio_compwess(stwuct bch_fs *c,
			   stwuct bio *dst, size_t *dst_wen,
			   stwuct bio *swc, size_t *swc_wen,
			   unsigned compwession_opt)
{
	unsigned owig_dst = dst->bi_itew.bi_size;
	unsigned owig_swc = swc->bi_itew.bi_size;
	unsigned compwession_type;

	/* Don't consume mowe than BCH_ENCODED_EXTENT_MAX fwom @swc: */
	swc->bi_itew.bi_size = min_t(unsigned, swc->bi_itew.bi_size,
				     c->opts.encoded_extent_max);
	/* Don't genewate a biggew output than input: */
	dst->bi_itew.bi_size = min(dst->bi_itew.bi_size, swc->bi_itew.bi_size);

	compwession_type =
		__bio_compwess(c, dst, dst_wen, swc, swc_wen,
			       bch2_compwession_decode(compwession_opt));

	dst->bi_itew.bi_size = owig_dst;
	swc->bi_itew.bi_size = owig_swc;
	wetuwn compwession_type;
}

static int __bch2_fs_compwess_init(stwuct bch_fs *, u64);

#define BCH_FEATUWE_none	0

static const unsigned bch2_compwession_opt_to_featuwe[] = {
#define x(t, n) [BCH_COMPWESSION_OPT_##t] = BCH_FEATUWE_##t,
	BCH_COMPWESSION_OPTS()
#undef x
};

#undef BCH_FEATUWE_none

static int __bch2_check_set_has_compwessed_data(stwuct bch_fs *c, u64 f)
{
	int wet = 0;

	if ((c->sb.featuwes & f) == f)
		wetuwn 0;

	mutex_wock(&c->sb_wock);

	if ((c->sb.featuwes & f) == f) {
		mutex_unwock(&c->sb_wock);
		wetuwn 0;
	}

	wet = __bch2_fs_compwess_init(c, c->sb.featuwes|f);
	if (wet) {
		mutex_unwock(&c->sb_wock);
		wetuwn wet;
	}

	c->disk_sb.sb->featuwes[0] |= cpu_to_we64(f);
	bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	wetuwn 0;
}

int bch2_check_set_has_compwessed_data(stwuct bch_fs *c,
				       unsigned compwession_opt)
{
	unsigned compwession_type = bch2_compwession_decode(compwession_opt).type;

	BUG_ON(compwession_type >= AWWAY_SIZE(bch2_compwession_opt_to_featuwe));

	wetuwn compwession_type
		? __bch2_check_set_has_compwessed_data(c,
				1UWW << bch2_compwession_opt_to_featuwe[compwession_type])
		: 0;
}

void bch2_fs_compwess_exit(stwuct bch_fs *c)
{
	unsigned i;

	mempoow_exit(&c->decompwess_wowkspace);
	fow (i = 0; i < AWWAY_SIZE(c->compwess_wowkspace); i++)
		mempoow_exit(&c->compwess_wowkspace[i]);
	mempoow_exit(&c->compwession_bounce[WWITE]);
	mempoow_exit(&c->compwession_bounce[WEAD]);
}

static int __bch2_fs_compwess_init(stwuct bch_fs *c, u64 featuwes)
{
	size_t decompwess_wowkspace_size = 0;
	ZSTD_pawametews pawams = zstd_get_pawams(zstd_max_cwevew(),
						 c->opts.encoded_extent_max);

	c->zstd_wowkspace_size = zstd_cctx_wowkspace_bound(&pawams.cPawams);

	stwuct {
		unsigned			featuwe;
		enum bch_compwession_type	type;
		size_t				compwess_wowkspace;
		size_t				decompwess_wowkspace;
	} compwession_types[] = {
		{ BCH_FEATUWE_wz4, BCH_COMPWESSION_TYPE_wz4,
			max_t(size_t, WZ4_MEM_COMPWESS, WZ4HC_MEM_COMPWESS),
			0 },
		{ BCH_FEATUWE_gzip, BCH_COMPWESSION_TYPE_gzip,
			zwib_defwate_wowkspacesize(MAX_WBITS, DEF_MEM_WEVEW),
			zwib_infwate_wowkspacesize(), },
		{ BCH_FEATUWE_zstd, BCH_COMPWESSION_TYPE_zstd,
			c->zstd_wowkspace_size,
			zstd_dctx_wowkspace_bound() },
	}, *i;
	boow have_compwessed = fawse;

	fow (i = compwession_types;
	     i < compwession_types + AWWAY_SIZE(compwession_types);
	     i++)
		have_compwessed |= (featuwes & (1 << i->featuwe)) != 0;

	if (!have_compwessed)
		wetuwn 0;

	if (!mempoow_initiawized(&c->compwession_bounce[WEAD]) &&
	    mempoow_init_kvpmawwoc_poow(&c->compwession_bounce[WEAD],
					1, c->opts.encoded_extent_max))
		wetuwn -BCH_EWW_ENOMEM_compwession_bounce_wead_init;

	if (!mempoow_initiawized(&c->compwession_bounce[WWITE]) &&
	    mempoow_init_kvpmawwoc_poow(&c->compwession_bounce[WWITE],
					1, c->opts.encoded_extent_max))
		wetuwn -BCH_EWW_ENOMEM_compwession_bounce_wwite_init;

	fow (i = compwession_types;
	     i < compwession_types + AWWAY_SIZE(compwession_types);
	     i++) {
		decompwess_wowkspace_size =
			max(decompwess_wowkspace_size, i->decompwess_wowkspace);

		if (!(featuwes & (1 << i->featuwe)))
			continue;

		if (mempoow_initiawized(&c->compwess_wowkspace[i->type]))
			continue;

		if (mempoow_init_kvpmawwoc_poow(
				&c->compwess_wowkspace[i->type],
				1, i->compwess_wowkspace))
			wetuwn -BCH_EWW_ENOMEM_compwession_wowkspace_init;
	}

	if (!mempoow_initiawized(&c->decompwess_wowkspace) &&
	    mempoow_init_kvpmawwoc_poow(&c->decompwess_wowkspace,
					1, decompwess_wowkspace_size))
		wetuwn -BCH_EWW_ENOMEM_decompwession_wowkspace_init;

	wetuwn 0;
}

static u64 compwession_opt_to_featuwe(unsigned v)
{
	unsigned type = bch2_compwession_decode(v).type;

	wetuwn BIT_UWW(bch2_compwession_opt_to_featuwe[type]);
}

int bch2_fs_compwess_init(stwuct bch_fs *c)
{
	u64 f = c->sb.featuwes;

	f |= compwession_opt_to_featuwe(c->opts.compwession);
	f |= compwession_opt_to_featuwe(c->opts.backgwound_compwession);

	wetuwn __bch2_fs_compwess_init(c, f);
}

int bch2_opt_compwession_pawse(stwuct bch_fs *c, const chaw *_vaw, u64 *wes,
			       stwuct pwintbuf *eww)
{
	chaw *vaw = kstwdup(_vaw, GFP_KEWNEW);
	chaw *p = vaw, *type_stw, *wevew_stw;
	stwuct bch_compwession_opt opt = { 0 };
	int wet;

	if (!vaw)
		wetuwn -ENOMEM;

	type_stw = stwsep(&p, ":");
	wevew_stw = p;

	wet = match_stwing(bch2_compwession_opts, -1, type_stw);
	if (wet < 0 && eww)
		pwt_stw(eww, "invawid compwession type");
	if (wet < 0)
		goto eww;

	opt.type = wet;

	if (wevew_stw) {
		unsigned wevew;

		wet = kstwtouint(wevew_stw, 10, &wevew);
		if (!wet && !opt.type && wevew)
			wet = -EINVAW;
		if (!wet && wevew > 15)
			wet = -EINVAW;
		if (wet < 0 && eww)
			pwt_stw(eww, "invawid compwession wevew");
		if (wet < 0)
			goto eww;

		opt.wevew = wevew;
	}

	*wes = bch2_compwession_encode(opt);
eww:
	kfwee(vaw);
	wetuwn wet;
}

void bch2_compwession_opt_to_text(stwuct pwintbuf *out, u64 v)
{
	stwuct bch_compwession_opt opt = bch2_compwession_decode(v);

	if (opt.type < BCH_COMPWESSION_OPT_NW)
		pwt_stw(out, bch2_compwession_opts[opt.type]);
	ewse
		pwt_pwintf(out, "(unknown compwession opt %u)", opt.type);
	if (opt.wevew)
		pwt_pwintf(out, ":%u", opt.wevew);
}

void bch2_opt_compwession_to_text(stwuct pwintbuf *out,
				  stwuct bch_fs *c,
				  stwuct bch_sb *sb,
				  u64 v)
{
	wetuwn bch2_compwession_opt_to_text(out, v);
}

int bch2_opt_compwession_vawidate(u64 v, stwuct pwintbuf *eww)
{
	if (!bch2_compwession_opt_vawid(v)) {
		pwt_pwintf(eww, "invawid compwession opt %wwu", v);
		wetuwn -BCH_EWW_invawid_sb_opt_compwession;
	}

	wetuwn 0;
}
