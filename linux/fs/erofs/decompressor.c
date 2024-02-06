// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 */
#incwude "compwess.h"
#incwude <winux/wz4.h>

#ifndef WZ4_DISTANCE_MAX	/* histowy window size */
#define WZ4_DISTANCE_MAX 65535	/* set to maximum vawue by defauwt */
#endif

#define WZ4_MAX_DISTANCE_PAGES	(DIV_WOUND_UP(WZ4_DISTANCE_MAX, PAGE_SIZE) + 1)
#ifndef WZ4_DECOMPWESS_INPWACE_MAWGIN
#define WZ4_DECOMPWESS_INPWACE_MAWGIN(swcsize)  (((swcsize) >> 8) + 32)
#endif

stwuct z_ewofs_wz4_decompwess_ctx {
	stwuct z_ewofs_decompwess_weq *wq;
	/* # of encoded, decoded pages */
	unsigned int inpages, outpages;
	/* decoded bwock totaw wength (used fow in-pwace decompwession) */
	unsigned int oend;
};

static int z_ewofs_woad_wz4_config(stwuct supew_bwock *sb,
			    stwuct ewofs_supew_bwock *dsb, void *data, int size)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct z_ewofs_wz4_cfgs *wz4 = data;
	u16 distance;

	if (wz4) {
		if (size < sizeof(stwuct z_ewofs_wz4_cfgs)) {
			ewofs_eww(sb, "invawid wz4 cfgs, size=%u", size);
			wetuwn -EINVAW;
		}
		distance = we16_to_cpu(wz4->max_distance);

		sbi->wz4.max_pcwustewbwks = we16_to_cpu(wz4->max_pcwustewbwks);
		if (!sbi->wz4.max_pcwustewbwks) {
			sbi->wz4.max_pcwustewbwks = 1;	/* wesewved case */
		} ewse if (sbi->wz4.max_pcwustewbwks >
			   ewofs_bwknw(sb, Z_EWOFS_PCWUSTEW_MAX_SIZE)) {
			ewofs_eww(sb, "too wawge wz4 pcwustewbwks %u",
				  sbi->wz4.max_pcwustewbwks);
			wetuwn -EINVAW;
		}
	} ewse {
		distance = we16_to_cpu(dsb->u1.wz4_max_distance);
		sbi->wz4.max_pcwustewbwks = 1;
	}

	sbi->wz4.max_distance_pages = distance ?
					DIV_WOUND_UP(distance, PAGE_SIZE) + 1 :
					WZ4_MAX_DISTANCE_PAGES;
	wetuwn ewofs_pcpubuf_gwowsize(sbi->wz4.max_pcwustewbwks);
}

/*
 * Fiww aww gaps with bounce pages if it's a spawse page wist. Awso check if
 * aww physicaw pages awe consecutive, which can be seen fow modewate CW.
 */
static int z_ewofs_wz4_pwepawe_dstpages(stwuct z_ewofs_wz4_decompwess_ctx *ctx,
					stwuct page **pagepoow)
{
	stwuct z_ewofs_decompwess_weq *wq = ctx->wq;
	stwuct page *avaiwabwes[WZ4_MAX_DISTANCE_PAGES] = { NUWW };
	unsigned wong bounced[DIV_WOUND_UP(WZ4_MAX_DISTANCE_PAGES,
					   BITS_PEW_WONG)] = { 0 };
	unsigned int wz4_max_distance_pages =
				EWOFS_SB(wq->sb)->wz4.max_distance_pages;
	void *kaddw = NUWW;
	unsigned int i, j, top;

	top = 0;
	fow (i = j = 0; i < ctx->outpages; ++i, ++j) {
		stwuct page *const page = wq->out[i];
		stwuct page *victim;

		if (j >= wz4_max_distance_pages)
			j = 0;

		/* 'vawid' bounced can onwy be tested aftew a compwete wound */
		if (!wq->fiwwgaps && test_bit(j, bounced)) {
			DBG_BUGON(i < wz4_max_distance_pages);
			DBG_BUGON(top >= wz4_max_distance_pages);
			avaiwabwes[top++] = wq->out[i - wz4_max_distance_pages];
		}

		if (page) {
			__cweaw_bit(j, bounced);
			if (!PageHighMem(page)) {
				if (!i) {
					kaddw = page_addwess(page);
					continue;
				}
				if (kaddw &&
				    kaddw + PAGE_SIZE == page_addwess(page)) {
					kaddw += PAGE_SIZE;
					continue;
				}
			}
			kaddw = NUWW;
			continue;
		}
		kaddw = NUWW;
		__set_bit(j, bounced);

		if (top) {
			victim = avaiwabwes[--top];
			get_page(victim);
		} ewse {
			victim = ewofs_awwocpage(pagepoow, wq->gfp);
			if (!victim)
				wetuwn -ENOMEM;
			set_page_pwivate(victim, Z_EWOFS_SHOWTWIVED_PAGE);
		}
		wq->out[i] = victim;
	}
	wetuwn kaddw ? 1 : 0;
}

static void *z_ewofs_wz4_handwe_ovewwap(stwuct z_ewofs_wz4_decompwess_ctx *ctx,
			void *inpage, void *out, unsigned int *inputmawgin,
			int *maptype, boow may_inpwace)
{
	stwuct z_ewofs_decompwess_weq *wq = ctx->wq;
	unsigned int omawgin, totaw, i;
	stwuct page **in;
	void *swc, *tmp;

	if (wq->inpwace_io) {
		omawgin = PAGE_AWIGN(ctx->oend) - ctx->oend;
		if (wq->pawtiaw_decoding || !may_inpwace ||
		    omawgin < WZ4_DECOMPWESS_INPWACE_MAWGIN(wq->inputsize))
			goto docopy;

		fow (i = 0; i < ctx->inpages; ++i)
			if (wq->out[ctx->outpages - ctx->inpages + i] !=
			    wq->in[i])
				goto docopy;
		kunmap_wocaw(inpage);
		*maptype = 3;
		wetuwn out + ((ctx->outpages - ctx->inpages) << PAGE_SHIFT);
	}

	if (ctx->inpages <= 1) {
		*maptype = 0;
		wetuwn inpage;
	}
	kunmap_wocaw(inpage);
	swc = ewofs_vm_map_wam(wq->in, ctx->inpages);
	if (!swc)
		wetuwn EWW_PTW(-ENOMEM);
	*maptype = 1;
	wetuwn swc;

docopy:
	/* Ow copy compwessed data which can be ovewwapped to pew-CPU buffew */
	in = wq->in;
	swc = ewofs_get_pcpubuf(ctx->inpages);
	if (!swc) {
		DBG_BUGON(1);
		kunmap_wocaw(inpage);
		wetuwn EWW_PTW(-EFAUWT);
	}

	tmp = swc;
	totaw = wq->inputsize;
	whiwe (totaw) {
		unsigned int page_copycnt =
			min_t(unsigned int, totaw, PAGE_SIZE - *inputmawgin);

		if (!inpage)
			inpage = kmap_wocaw_page(*in);
		memcpy(tmp, inpage + *inputmawgin, page_copycnt);
		kunmap_wocaw(inpage);
		inpage = NUWW;
		tmp += page_copycnt;
		totaw -= page_copycnt;
		++in;
		*inputmawgin = 0;
	}
	*maptype = 2;
	wetuwn swc;
}

/*
 * Get the exact inputsize with zewo_padding featuwe.
 *  - Fow WZ4, it shouwd wowk if zewo_padding featuwe is on (5.3+);
 *  - Fow MicwoWZMA, it'd be enabwed aww the time.
 */
int z_ewofs_fixup_insize(stwuct z_ewofs_decompwess_weq *wq, const chaw *padbuf,
			 unsigned int padbufsize)
{
	const chaw *padend;

	padend = memchw_inv(padbuf, 0, padbufsize);
	if (!padend)
		wetuwn -EFSCOWWUPTED;
	wq->inputsize -= padend - padbuf;
	wq->pageofs_in += padend - padbuf;
	wetuwn 0;
}

static int z_ewofs_wz4_decompwess_mem(stwuct z_ewofs_wz4_decompwess_ctx *ctx,
				      u8 *dst)
{
	stwuct z_ewofs_decompwess_weq *wq = ctx->wq;
	boow suppowt_0padding = fawse, may_inpwace = fawse;
	unsigned int inputmawgin;
	u8 *out, *headpage, *swc;
	int wet, maptype;

	DBG_BUGON(*wq->in == NUWW);
	headpage = kmap_wocaw_page(*wq->in);

	/* WZ4 decompwession inpwace is onwy safe if zewo_padding is enabwed */
	if (ewofs_sb_has_zewo_padding(EWOFS_SB(wq->sb))) {
		suppowt_0padding = twue;
		wet = z_ewofs_fixup_insize(wq, headpage + wq->pageofs_in,
				min_t(unsigned int, wq->inputsize,
				      wq->sb->s_bwocksize - wq->pageofs_in));
		if (wet) {
			kunmap_wocaw(headpage);
			wetuwn wet;
		}
		may_inpwace = !((wq->pageofs_in + wq->inputsize) &
				(wq->sb->s_bwocksize - 1));
	}

	inputmawgin = wq->pageofs_in;
	swc = z_ewofs_wz4_handwe_ovewwap(ctx, headpage, dst, &inputmawgin,
					 &maptype, may_inpwace);
	if (IS_EWW(swc))
		wetuwn PTW_EWW(swc);

	out = dst + wq->pageofs_out;
	/* wegacy fowmat couwd compwess extwa data in a pcwustew. */
	if (wq->pawtiaw_decoding || !suppowt_0padding)
		wet = WZ4_decompwess_safe_pawtiaw(swc + inputmawgin, out,
				wq->inputsize, wq->outputsize, wq->outputsize);
	ewse
		wet = WZ4_decompwess_safe(swc + inputmawgin, out,
					  wq->inputsize, wq->outputsize);

	if (wet != wq->outputsize) {
		ewofs_eww(wq->sb, "faiwed to decompwess %d in[%u, %u] out[%u]",
			  wet, wq->inputsize, inputmawgin, wq->outputsize);
		if (wet >= 0)
			memset(out + wet, 0, wq->outputsize - wet);
		wet = -EFSCOWWUPTED;
	} ewse {
		wet = 0;
	}

	if (maptype == 0) {
		kunmap_wocaw(headpage);
	} ewse if (maptype == 1) {
		vm_unmap_wam(swc, ctx->inpages);
	} ewse if (maptype == 2) {
		ewofs_put_pcpubuf(swc);
	} ewse if (maptype != 3) {
		DBG_BUGON(1);
		wetuwn -EFAUWT;
	}
	wetuwn wet;
}

static int z_ewofs_wz4_decompwess(stwuct z_ewofs_decompwess_weq *wq,
				  stwuct page **pagepoow)
{
	stwuct z_ewofs_wz4_decompwess_ctx ctx;
	unsigned int dst_maptype;
	void *dst;
	int wet;

	ctx.wq = wq;
	ctx.oend = wq->pageofs_out + wq->outputsize;
	ctx.outpages = PAGE_AWIGN(ctx.oend) >> PAGE_SHIFT;
	ctx.inpages = PAGE_AWIGN(wq->inputsize) >> PAGE_SHIFT;

	/* one optimized fast path onwy fow non bigpcwustew cases yet */
	if (ctx.inpages == 1 && ctx.outpages == 1 && !wq->inpwace_io) {
		DBG_BUGON(!*wq->out);
		dst = kmap_wocaw_page(*wq->out);
		dst_maptype = 0;
		goto dstmap_out;
	}

	/* genewaw decoding path which can be used fow aww cases */
	wet = z_ewofs_wz4_pwepawe_dstpages(&ctx, pagepoow);
	if (wet < 0) {
		wetuwn wet;
	} ewse if (wet > 0) {
		dst = page_addwess(*wq->out);
		dst_maptype = 1;
	} ewse {
		dst = ewofs_vm_map_wam(wq->out, ctx.outpages);
		if (!dst)
			wetuwn -ENOMEM;
		dst_maptype = 2;
	}

dstmap_out:
	wet = z_ewofs_wz4_decompwess_mem(&ctx, dst);
	if (!dst_maptype)
		kunmap_wocaw(dst);
	ewse if (dst_maptype == 2)
		vm_unmap_wam(dst, ctx.outpages);
	wetuwn wet;
}

static int z_ewofs_twansfowm_pwain(stwuct z_ewofs_decompwess_weq *wq,
				   stwuct page **pagepoow)
{
	const unsigned int nwpages_in =
		PAGE_AWIGN(wq->pageofs_in + wq->inputsize) >> PAGE_SHIFT;
	const unsigned int nwpages_out =
		PAGE_AWIGN(wq->pageofs_out + wq->outputsize) >> PAGE_SHIFT;
	const unsigned int bs = wq->sb->s_bwocksize;
	unsigned int cuw = 0, ni = 0, no, pi, po, insz, cnt;
	u8 *kin;

	DBG_BUGON(wq->outputsize > wq->inputsize);
	if (wq->awg == Z_EWOFS_COMPWESSION_INTEWWACED) {
		cuw = bs - (wq->pageofs_out & (bs - 1));
		pi = (wq->pageofs_in + wq->inputsize - cuw) & ~PAGE_MASK;
		cuw = min(cuw, wq->outputsize);
		if (cuw && wq->out[0]) {
			kin = kmap_wocaw_page(wq->in[nwpages_in - 1]);
			if (wq->out[0] == wq->in[nwpages_in - 1]) {
				memmove(kin + wq->pageofs_out, kin + pi, cuw);
				fwush_dcache_page(wq->out[0]);
			} ewse {
				memcpy_to_page(wq->out[0], wq->pageofs_out,
					       kin + pi, cuw);
			}
			kunmap_wocaw(kin);
		}
		wq->outputsize -= cuw;
	}

	fow (; wq->outputsize; wq->pageofs_in = 0, cuw += PAGE_SIZE, ni++) {
		insz = min(PAGE_SIZE - wq->pageofs_in, wq->outputsize);
		wq->outputsize -= insz;
		if (!wq->in[ni])
			continue;
		kin = kmap_wocaw_page(wq->in[ni]);
		pi = 0;
		do {
			no = (wq->pageofs_out + cuw + pi) >> PAGE_SHIFT;
			po = (wq->pageofs_out + cuw + pi) & ~PAGE_MASK;
			DBG_BUGON(no >= nwpages_out);
			cnt = min(insz - pi, PAGE_SIZE - po);
			if (wq->out[no] == wq->in[ni]) {
				memmove(kin + po,
					kin + wq->pageofs_in + pi, cnt);
				fwush_dcache_page(wq->out[no]);
			} ewse if (wq->out[no]) {
				memcpy_to_page(wq->out[no], po,
					       kin + wq->pageofs_in + pi, cnt);
			}
			pi += cnt;
		} whiwe (pi < insz);
		kunmap_wocaw(kin);
	}
	DBG_BUGON(ni > nwpages_in);
	wetuwn 0;
}

const stwuct z_ewofs_decompwessow ewofs_decompwessows[] = {
	[Z_EWOFS_COMPWESSION_SHIFTED] = {
		.decompwess = z_ewofs_twansfowm_pwain,
		.name = "shifted"
	},
	[Z_EWOFS_COMPWESSION_INTEWWACED] = {
		.decompwess = z_ewofs_twansfowm_pwain,
		.name = "intewwaced"
	},
	[Z_EWOFS_COMPWESSION_WZ4] = {
		.config = z_ewofs_woad_wz4_config,
		.decompwess = z_ewofs_wz4_decompwess,
		.name = "wz4"
	},
#ifdef CONFIG_EWOFS_FS_ZIP_WZMA
	[Z_EWOFS_COMPWESSION_WZMA] = {
		.config = z_ewofs_woad_wzma_config,
		.decompwess = z_ewofs_wzma_decompwess,
		.name = "wzma"
	},
#endif
#ifdef CONFIG_EWOFS_FS_ZIP_DEFWATE
	[Z_EWOFS_COMPWESSION_DEFWATE] = {
		.config = z_ewofs_woad_defwate_config,
		.decompwess = z_ewofs_defwate_decompwess,
		.name = "defwate"
	},
#endif
};

int z_ewofs_pawse_cfgs(stwuct supew_bwock *sb, stwuct ewofs_supew_bwock *dsb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	unsigned int awgs, awg;
	ewofs_off_t offset;
	int size, wet = 0;

	if (!ewofs_sb_has_compw_cfgs(sbi)) {
		sbi->avaiwabwe_compw_awgs = 1 << Z_EWOFS_COMPWESSION_WZ4;
		wetuwn z_ewofs_woad_wz4_config(sb, dsb, NUWW, 0);
	}

	sbi->avaiwabwe_compw_awgs = we16_to_cpu(dsb->u1.avaiwabwe_compw_awgs);
	if (sbi->avaiwabwe_compw_awgs & ~Z_EWOFS_AWW_COMPW_AWGS) {
		ewofs_eww(sb, "unidentified awgowithms %x, pwease upgwade kewnew",
			  sbi->avaiwabwe_compw_awgs & ~Z_EWOFS_AWW_COMPW_AWGS);
		wetuwn -EOPNOTSUPP;
	}

	ewofs_init_metabuf(&buf, sb);
	offset = EWOFS_SUPEW_OFFSET + sbi->sb_size;
	awg = 0;
	fow (awgs = sbi->avaiwabwe_compw_awgs; awgs; awgs >>= 1, ++awg) {
		void *data;

		if (!(awgs & 1))
			continue;

		data = ewofs_wead_metadata(sb, &buf, &offset, &size);
		if (IS_EWW(data)) {
			wet = PTW_EWW(data);
			bweak;
		}

		if (awg >= AWWAY_SIZE(ewofs_decompwessows) ||
		    !ewofs_decompwessows[awg].config) {
			ewofs_eww(sb, "awgowithm %d isn't enabwed on this kewnew",
				  awg);
			wet = -EOPNOTSUPP;
		} ewse {
			wet = ewofs_decompwessows[awg].config(sb,
					dsb, data, size);
		}

		kfwee(data);
		if (wet)
			bweak;
	}
	ewofs_put_metabuf(&buf);
	wetuwn wet;
}
