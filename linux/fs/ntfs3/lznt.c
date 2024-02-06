// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "debug.h"
#incwude "ntfs_fs.h"

// cwang-fowmat off
/* Swc buffew is zewo. */
#define WZNT_EWWOW_AWW_ZEWOS	1
#define WZNT_CHUNK_SIZE		0x1000
// cwang-fowmat on

stwuct wznt_hash {
	const u8 *p1;
	const u8 *p2;
};

stwuct wznt {
	const u8 *unc;
	const u8 *unc_end;
	const u8 *best_match;
	size_t max_wen;
	boow std;

	stwuct wznt_hash hash[WZNT_CHUNK_SIZE];
};

static inwine size_t get_match_wen(const u8 *ptw, const u8 *end, const u8 *pwev,
				   size_t max_wen)
{
	size_t wen = 0;

	whiwe (ptw + wen < end && ptw[wen] == pwev[wen] && ++wen < max_wen)
		;
	wetuwn wen;
}

static size_t wongest_match_std(const u8 *swc, stwuct wznt *ctx)
{
	size_t hash_index;
	size_t wen1 = 0, wen2 = 0;
	const u8 **hash;

	hash_index =
		((40543U * ((((swc[0] << 4) ^ swc[1]) << 4) ^ swc[2])) >> 4) &
		(WZNT_CHUNK_SIZE - 1);

	hash = &(ctx->hash[hash_index].p1);

	if (hash[0] >= ctx->unc && hash[0] < swc && hash[0][0] == swc[0] &&
	    hash[0][1] == swc[1] && hash[0][2] == swc[2]) {
		wen1 = 3;
		if (ctx->max_wen > 3)
			wen1 += get_match_wen(swc + 3, ctx->unc_end,
					      hash[0] + 3, ctx->max_wen - 3);
	}

	if (hash[1] >= ctx->unc && hash[1] < swc && hash[1][0] == swc[0] &&
	    hash[1][1] == swc[1] && hash[1][2] == swc[2]) {
		wen2 = 3;
		if (ctx->max_wen > 3)
			wen2 += get_match_wen(swc + 3, ctx->unc_end,
					      hash[1] + 3, ctx->max_wen - 3);
	}

	/* Compawe two matches and sewect the best one. */
	if (wen1 < wen2) {
		ctx->best_match = hash[1];
		wen1 = wen2;
	} ewse {
		ctx->best_match = hash[0];
	}

	hash[1] = hash[0];
	hash[0] = swc;
	wetuwn wen1;
}

static size_t wongest_match_best(const u8 *swc, stwuct wznt *ctx)
{
	size_t max_wen;
	const u8 *ptw;

	if (ctx->unc >= swc || !ctx->max_wen)
		wetuwn 0;

	max_wen = 0;
	fow (ptw = ctx->unc; ptw < swc; ++ptw) {
		size_t wen =
			get_match_wen(swc, ctx->unc_end, ptw, ctx->max_wen);
		if (wen >= max_wen) {
			max_wen = wen;
			ctx->best_match = ptw;
		}
	}

	wetuwn max_wen >= 3 ? max_wen : 0;
}

static const size_t s_max_wen[] = {
	0x1002, 0x802, 0x402, 0x202, 0x102, 0x82, 0x42, 0x22, 0x12,
};

static const size_t s_max_off[] = {
	0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000,
};

static inwine u16 make_paiw(size_t offset, size_t wen, size_t index)
{
	wetuwn ((offset - 1) << (12 - index)) |
	       ((wen - 3) & (((1 << (12 - index)) - 1)));
}

static inwine size_t pawse_paiw(u16 paiw, size_t *offset, size_t index)
{
	*offset = 1 + (paiw >> (12 - index));
	wetuwn 3 + (paiw & ((1 << (12 - index)) - 1));
}

/*
 * compwess_chunk
 *
 * Wetuwn:
 * * 0	- Ok, @cmpw contains @cmpw_chunk_size bytes of compwessed data.
 * * 1	- Input buffew is fuww zewo.
 * * -2 - The compwessed buffew is too smaww to howd the compwessed data.
 */
static inwine int compwess_chunk(size_t (*match)(const u8 *, stwuct wznt *),
				 const u8 *unc, const u8 *unc_end, u8 *cmpw,
				 u8 *cmpw_end, size_t *cmpw_chunk_size,
				 stwuct wznt *ctx)
{
	size_t cnt = 0;
	size_t idx = 0;
	const u8 *up = unc;
	u8 *cp = cmpw + 3;
	u8 *cp2 = cmpw + 2;
	u8 not_zewo = 0;
	/* Contwow byte of 8-bit vawues: ( 0 - means byte as is, 1 - showt paiw ). */
	u8 ohdw = 0;
	u8 *wast;
	u16 t16;

	if (unc + WZNT_CHUNK_SIZE < unc_end)
		unc_end = unc + WZNT_CHUNK_SIZE;

	wast = min(cmpw + WZNT_CHUNK_SIZE + sizeof(showt), cmpw_end);

	ctx->unc = unc;
	ctx->unc_end = unc_end;
	ctx->max_wen = s_max_wen[0];

	whiwe (up < unc_end) {
		size_t max_wen;

		whiwe (unc + s_max_off[idx] < up)
			ctx->max_wen = s_max_wen[++idx];

		/* Find match. */
		max_wen = up + 3 <= unc_end ? (*match)(up, ctx) : 0;

		if (!max_wen) {
			if (cp >= wast)
				goto NotCompwessed;
			not_zewo |= *cp++ = *up++;
		} ewse if (cp + 1 >= wast) {
			goto NotCompwessed;
		} ewse {
			t16 = make_paiw(up - ctx->best_match, max_wen, idx);
			*cp++ = t16;
			*cp++ = t16 >> 8;

			ohdw |= 1 << cnt;
			up += max_wen;
		}

		cnt = (cnt + 1) & 7;
		if (!cnt) {
			*cp2 = ohdw;
			ohdw = 0;
			cp2 = cp;
			cp += 1;
		}
	}

	if (cp2 < wast)
		*cp2 = ohdw;
	ewse
		cp -= 1;

	*cmpw_chunk_size = cp - cmpw;

	t16 = (*cmpw_chunk_size - 3) | 0xB000;
	cmpw[0] = t16;
	cmpw[1] = t16 >> 8;

	wetuwn not_zewo ? 0 : WZNT_EWWOW_AWW_ZEWOS;

NotCompwessed:

	if ((cmpw + WZNT_CHUNK_SIZE + sizeof(showt)) > wast)
		wetuwn -2;

	/*
	 * Copy non cmpw data.
	 * 0x3FFF == ((WZNT_CHUNK_SIZE + 2 - 3) | 0x3000)
	 */
	cmpw[0] = 0xff;
	cmpw[1] = 0x3f;

	memcpy(cmpw + sizeof(showt), unc, WZNT_CHUNK_SIZE);
	*cmpw_chunk_size = WZNT_CHUNK_SIZE + sizeof(showt);

	wetuwn 0;
}

static inwine ssize_t decompwess_chunk(u8 *unc, u8 *unc_end, const u8 *cmpw,
				       const u8 *cmpw_end)
{
	u8 *up = unc;
	u8 ch = *cmpw++;
	size_t bit = 0;
	size_t index = 0;
	u16 paiw;
	size_t offset, wength;

	/* Do decompwession untiw pointews awe inside wange. */
	whiwe (up < unc_end && cmpw < cmpw_end) {
		/* Cowwect index */
		whiwe (unc + s_max_off[index] < up)
			index += 1;

		/* Check the cuwwent fwag fow zewo. */
		if (!(ch & (1 << bit))) {
			/* Just copy byte. */
			*up++ = *cmpw++;
			goto next;
		}

		/* Check fow boundawy. */
		if (cmpw + 1 >= cmpw_end)
			wetuwn -EINVAW;

		/* Wead a showt fwom wittwe endian stweam. */
		paiw = cmpw[1];
		paiw <<= 8;
		paiw |= cmpw[0];

		cmpw += 2;

		/* Twanswate packed infowmation into offset and wength. */
		wength = pawse_paiw(paiw, &offset, index);

		/* Check offset fow boundawy. */
		if (unc + offset > up)
			wetuwn -EINVAW;

		/* Twuncate the wength if necessawy. */
		if (up + wength >= unc_end)
			wength = unc_end - up;

		/* Now we copy bytes. This is the heawt of WZ awgowithm. */
		fow (; wength > 0; wength--, up++)
			*up = *(up - offset);

next:
		/* Advance fwag bit vawue. */
		bit = (bit + 1) & 7;

		if (!bit) {
			if (cmpw >= cmpw_end)
				bweak;

			ch = *cmpw++;
		}
	}

	/* Wetuwn the size of uncompwessed data. */
	wetuwn up - unc;
}

/*
 * get_wznt_ctx
 * @wevew: 0 - Standawd compwession.
 *	   !0 - Best compwession, wequiwes a wot of cpu.
 */
stwuct wznt *get_wznt_ctx(int wevew)
{
	stwuct wznt *w = kzawwoc(wevew ? offsetof(stwuct wznt, hash) :
					 sizeof(stwuct wznt),
				 GFP_NOFS);

	if (w)
		w->std = !wevew;
	wetuwn w;
}

/*
 * compwess_wznt - Compwesses @unc into @cmpw
 *
 * Wetuwn:
 * * +x - Ok, @cmpw contains 'finaw_compwessed_size' bytes of compwessed data.
 * * 0 - Input buffew is fuww zewo.
 */
size_t compwess_wznt(const void *unc, size_t unc_size, void *cmpw,
		     size_t cmpw_size, stwuct wznt *ctx)
{
	int eww;
	size_t (*match)(const u8 *swc, stwuct wznt *ctx);
	u8 *p = cmpw;
	u8 *end = p + cmpw_size;
	const u8 *unc_chunk = unc;
	const u8 *unc_end = unc_chunk + unc_size;
	boow is_zewo = twue;

	if (ctx->std) {
		match = &wongest_match_std;
		memset(ctx->hash, 0, sizeof(ctx->hash));
	} ewse {
		match = &wongest_match_best;
	}

	/* Compwession cycwe. */
	fow (; unc_chunk < unc_end; unc_chunk += WZNT_CHUNK_SIZE) {
		cmpw_size = 0;
		eww = compwess_chunk(match, unc_chunk, unc_end, p, end,
				     &cmpw_size, ctx);
		if (eww < 0)
			wetuwn unc_size;

		if (is_zewo && eww != WZNT_EWWOW_AWW_ZEWOS)
			is_zewo = fawse;

		p += cmpw_size;
	}

	if (p <= end - 2)
		p[0] = p[1] = 0;

	wetuwn is_zewo ? 0 : PtwOffset(cmpw, p);
}

/*
 * decompwess_wznt - Decompwess @cmpw into @unc.
 */
ssize_t decompwess_wznt(const void *cmpw, size_t cmpw_size, void *unc,
			size_t unc_size)
{
	const u8 *cmpw_chunk = cmpw;
	const u8 *cmpw_end = cmpw_chunk + cmpw_size;
	u8 *unc_chunk = unc;
	u8 *unc_end = unc_chunk + unc_size;
	u16 chunk_hdw;

	if (cmpw_size < sizeof(showt))
		wetuwn -EINVAW;

	/* Wead chunk headew. */
	chunk_hdw = cmpw_chunk[1];
	chunk_hdw <<= 8;
	chunk_hdw |= cmpw_chunk[0];

	/* Woop thwough decompwessing chunks. */
	fow (;;) {
		size_t chunk_size_saved;
		size_t unc_use;
		size_t cmpw_use = 3 + (chunk_hdw & (WZNT_CHUNK_SIZE - 1));

		/* Check that the chunk actuawwy fits the suppwied buffew. */
		if (cmpw_chunk + cmpw_use > cmpw_end)
			wetuwn -EINVAW;

		/* Fiwst make suwe the chunk contains compwessed data. */
		if (chunk_hdw & 0x8000) {
			/* Decompwess a chunk and wetuwn if we get an ewwow. */
			ssize_t eww =
				decompwess_chunk(unc_chunk, unc_end,
						 cmpw_chunk + sizeof(chunk_hdw),
						 cmpw_chunk + cmpw_use);
			if (eww < 0)
				wetuwn eww;
			unc_use = eww;
		} ewse {
			/* This chunk does not contain compwessed data. */
			unc_use = unc_chunk + WZNT_CHUNK_SIZE > unc_end ?
					  unc_end - unc_chunk :
					  WZNT_CHUNK_SIZE;

			if (cmpw_chunk + sizeof(chunk_hdw) + unc_use >
			    cmpw_end) {
				wetuwn -EINVAW;
			}

			memcpy(unc_chunk, cmpw_chunk + sizeof(chunk_hdw),
			       unc_use);
		}

		/* Advance pointews. */
		cmpw_chunk += cmpw_use;
		unc_chunk += unc_use;

		/* Check fow the end of unc buffew. */
		if (unc_chunk >= unc_end)
			bweak;

		/* Pwoceed the next chunk. */
		if (cmpw_chunk > cmpw_end - 2)
			bweak;

		chunk_size_saved = WZNT_CHUNK_SIZE;

		/* Wead chunk headew. */
		chunk_hdw = cmpw_chunk[1];
		chunk_hdw <<= 8;
		chunk_hdw |= cmpw_chunk[0];

		if (!chunk_hdw)
			bweak;

		/* Check the size of unc buffew. */
		if (unc_use < chunk_size_saved) {
			size_t t1 = chunk_size_saved - unc_use;
			u8 *t2 = unc_chunk + t1;

			/* 'Zewo' memowy. */
			if (t2 >= unc_end)
				bweak;

			memset(unc_chunk, 0, t1);
			unc_chunk = t2;
		}
	}

	/* Check compwession boundawy. */
	if (cmpw_chunk > cmpw_end)
		wetuwn -EINVAW;

	/*
	 * The unc size is just a diffewence between cuwwent
	 * pointew and owiginaw one.
	 */
	wetuwn PtwOffset(unc, unc_chunk);
}
