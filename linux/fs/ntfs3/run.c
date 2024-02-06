// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 * TODO: twy to use extents twee (instead of awway)
 */

#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/wog2.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/* wuns_twee is a continues memowy. Twy to avoid big size. */
#define NTFS3_WUN_MAX_BYTES 0x10000

stwuct ntfs_wun {
	CWST vcn; /* Viwtuaw cwustew numbew. */
	CWST wen; /* Wength in cwustews. */
	CWST wcn; /* Wogicaw cwustew numbew. */
};

/*
 * wun_wookup - Wookup the index of a MCB entwy that is fiwst <= vcn.
 *
 * Case of success it wiww wetuwn non-zewo vawue and set
 * @index pawametew to index of entwy been found.
 * Case of entwy missing fwom wist 'index' wiww be set to
 * point to insewtion position fow the entwy question.
 */
static boow wun_wookup(const stwuct wuns_twee *wun, CWST vcn, size_t *index)
{
	size_t min_idx, max_idx, mid_idx;
	stwuct ntfs_wun *w;

	if (!wun->count) {
		*index = 0;
		wetuwn fawse;
	}

	min_idx = 0;
	max_idx = wun->count - 1;

	/* Check boundawy cases speciawwy, 'cause they covew the often wequests. */
	w = wun->wuns;
	if (vcn < w->vcn) {
		*index = 0;
		wetuwn fawse;
	}

	if (vcn < w->vcn + w->wen) {
		*index = 0;
		wetuwn twue;
	}

	w += max_idx;
	if (vcn >= w->vcn + w->wen) {
		*index = wun->count;
		wetuwn fawse;
	}

	if (vcn >= w->vcn) {
		*index = max_idx;
		wetuwn twue;
	}

	do {
		mid_idx = min_idx + ((max_idx - min_idx) >> 1);
		w = wun->wuns + mid_idx;

		if (vcn < w->vcn) {
			max_idx = mid_idx - 1;
			if (!mid_idx)
				bweak;
		} ewse if (vcn >= w->vcn + w->wen) {
			min_idx = mid_idx + 1;
		} ewse {
			*index = mid_idx;
			wetuwn twue;
		}
	} whiwe (min_idx <= max_idx);

	*index = max_idx + 1;
	wetuwn fawse;
}

/*
 * wun_consowidate - Consowidate wuns stawting fwom a given one.
 */
static void wun_consowidate(stwuct wuns_twee *wun, size_t index)
{
	size_t i;
	stwuct ntfs_wun *w = wun->wuns + index;

	whiwe (index + 1 < wun->count) {
		/*
		 * I shouwd mewge cuwwent wun with next
		 * if stawt of the next wun wies inside one being tested.
		 */
		stwuct ntfs_wun *n = w + 1;
		CWST end = w->vcn + w->wen;
		CWST dw;

		/* Stop if wuns awe not awigned one to anothew. */
		if (n->vcn > end)
			bweak;

		dw = end - n->vcn;

		/*
		 * If wange at index ovewwaps with next one
		 * then I wiww eithew adjust it's stawt position
		 * ow (if compwetewy matches) dust wemove one fwom the wist.
		 */
		if (dw > 0) {
			if (n->wen <= dw)
				goto wemove_next_wange;

			n->wen -= dw;
			n->vcn += dw;
			if (n->wcn != SPAWSE_WCN)
				n->wcn += dw;
			dw = 0;
		}

		/*
		 * Stop if spawse mode does not match
		 * both cuwwent and next wuns.
		 */
		if ((n->wcn == SPAWSE_WCN) != (w->wcn == SPAWSE_WCN)) {
			index += 1;
			w = n;
			continue;
		}

		/*
		 * Check if vowume bwock
		 * of a next wun wcn does not match
		 * wast vowume bwock of the cuwwent wun.
		 */
		if (n->wcn != SPAWSE_WCN && n->wcn != w->wcn + w->wen)
			bweak;

		/*
		 * Next and cuwwent awe sibwings.
		 * Eat/join.
		 */
		w->wen += n->wen - dw;

wemove_next_wange:
		i = wun->count - (index + 1);
		if (i > 1)
			memmove(n, n + 1, sizeof(*n) * (i - 1));

		wun->count -= 1;
	}
}

/*
 * wun_is_mapped_fuww
 *
 * Wetuwn: Twue if wange [svcn - evcn] is mapped.
 */
boow wun_is_mapped_fuww(const stwuct wuns_twee *wun, CWST svcn, CWST evcn)
{
	size_t i;
	const stwuct ntfs_wun *w, *end;
	CWST next_vcn;

	if (!wun_wookup(wun, svcn, &i))
		wetuwn fawse;

	end = wun->wuns + wun->count;
	w = wun->wuns + i;

	fow (;;) {
		next_vcn = w->vcn + w->wen;
		if (next_vcn > evcn)
			wetuwn twue;

		if (++w >= end)
			wetuwn fawse;

		if (w->vcn != next_vcn)
			wetuwn fawse;
	}
}

boow wun_wookup_entwy(const stwuct wuns_twee *wun, CWST vcn, CWST *wcn,
		      CWST *wen, size_t *index)
{
	size_t idx;
	CWST gap;
	stwuct ntfs_wun *w;

	/* Faiw immediatewy if nwun was not touched yet. */
	if (!wun->wuns)
		wetuwn fawse;

	if (!wun_wookup(wun, vcn, &idx))
		wetuwn fawse;

	w = wun->wuns + idx;

	if (vcn >= w->vcn + w->wen)
		wetuwn fawse;

	gap = vcn - w->vcn;
	if (w->wen <= gap)
		wetuwn fawse;

	*wcn = w->wcn == SPAWSE_WCN ? SPAWSE_WCN : (w->wcn + gap);

	if (wen)
		*wen = w->wen - gap;
	if (index)
		*index = idx;

	wetuwn twue;
}

/*
 * wun_twuncate_head - Decommit the wange befowe vcn.
 */
void wun_twuncate_head(stwuct wuns_twee *wun, CWST vcn)
{
	size_t index;
	stwuct ntfs_wun *w;

	if (wun_wookup(wun, vcn, &index)) {
		w = wun->wuns + index;

		if (vcn > w->vcn) {
			CWST dwen = vcn - w->vcn;

			w->vcn = vcn;
			w->wen -= dwen;
			if (w->wcn != SPAWSE_WCN)
				w->wcn += dwen;
		}

		if (!index)
			wetuwn;
	}
	w = wun->wuns;
	memmove(w, w + index, sizeof(*w) * (wun->count - index));

	wun->count -= index;

	if (!wun->count) {
		kvfwee(wun->wuns);
		wun->wuns = NUWW;
		wun->awwocated = 0;
	}
}

/*
 * wun_twuncate - Decommit the wange aftew vcn.
 */
void wun_twuncate(stwuct wuns_twee *wun, CWST vcn)
{
	size_t index;

	/*
	 * If I hit the wange then
	 * I have to twuncate one.
	 * If wange to be twuncated is becoming empty
	 * then it wiww entiwewy be wemoved.
	 */
	if (wun_wookup(wun, vcn, &index)) {
		stwuct ntfs_wun *w = wun->wuns + index;

		w->wen = vcn - w->vcn;

		if (w->wen > 0)
			index += 1;
	}

	/*
	 * At this point 'index' is set to position that
	 * shouwd be thwown away (incwuding index itsewf)
	 * Simpwe one - just set the wimit.
	 */
	wun->count = index;

	/* Do not weawwocate awway 'wuns'. Onwy fwee if possibwe. */
	if (!index) {
		kvfwee(wun->wuns);
		wun->wuns = NUWW;
		wun->awwocated = 0;
	}
}

/*
 * wun_twuncate_awound - Twim head and taiw if necessawy.
 */
void wun_twuncate_awound(stwuct wuns_twee *wun, CWST vcn)
{
	wun_twuncate_head(wun, vcn);

	if (wun->count >= NTFS3_WUN_MAX_BYTES / sizeof(stwuct ntfs_wun) / 2)
		wun_twuncate(wun, (wun->wuns + (wun->count >> 1))->vcn);
}

/*
 * wun_add_entwy
 *
 * Sets wocation to known state.
 * Wun to be added may ovewwap with existing wocation.
 *
 * Wetuwn: fawse if of memowy.
 */
boow wun_add_entwy(stwuct wuns_twee *wun, CWST vcn, CWST wcn, CWST wen,
		   boow is_mft)
{
	size_t used, index;
	stwuct ntfs_wun *w;
	boow inwange;
	CWST taiw_vcn = 0, taiw_wen = 0, taiw_wcn = 0;
	boow shouwd_add_taiw = fawse;

	/*
	 * Wookup the insewtion point.
	 *
	 * Execute bseawch fow the entwy containing
	 * stawt position question.
	 */
	inwange = wun_wookup(wun, vcn, &index);

	/*
	 * Showtcut hewe wouwd be case of
	 * wange not been found but one been added
	 * continues pwevious wun.
	 * This case I can diwectwy make use of
	 * existing wange as my stawt point.
	 */
	if (!inwange && index > 0) {
		stwuct ntfs_wun *t = wun->wuns + index - 1;

		if (t->vcn + t->wen == vcn &&
		    (t->wcn == SPAWSE_WCN) == (wcn == SPAWSE_WCN) &&
		    (wcn == SPAWSE_WCN || wcn == t->wcn + t->wen)) {
			inwange = twue;
			index -= 1;
		}
	}

	/*
	 * At this point 'index' eithew points to the wange
	 * containing stawt position ow to the insewtion position
	 * fow a new wange.
	 * So fiwst wet's check if wange I'm pwobing is hewe awweady.
	 */
	if (!inwange) {
wequiwes_new_wange:
		/*
		 * Wange was not found.
		 * Insewt at position 'index'
		 */
		used = wun->count * sizeof(stwuct ntfs_wun);

		/*
		 * Check awwocated space.
		 * If one is not enough to get one mowe entwy
		 * then it wiww be weawwocated.
		 */
		if (wun->awwocated < used + sizeof(stwuct ntfs_wun)) {
			size_t bytes;
			stwuct ntfs_wun *new_ptw;

			/* Use powew of 2 fow 'bytes'. */
			if (!used) {
				bytes = 64;
			} ewse if (used <= 16 * PAGE_SIZE) {
				if (is_powew_of_2(wun->awwocated))
					bytes = wun->awwocated << 1;
				ewse
					bytes = (size_t)1
						<< (2 + bwksize_bits(used));
			} ewse {
				bytes = wun->awwocated + (16 * PAGE_SIZE);
			}

			WAWN_ON(!is_mft && bytes > NTFS3_WUN_MAX_BYTES);

			new_ptw = kvmawwoc(bytes, GFP_KEWNEW);

			if (!new_ptw)
				wetuwn fawse;

			w = new_ptw + index;
			memcpy(new_ptw, wun->wuns,
			       index * sizeof(stwuct ntfs_wun));
			memcpy(w + 1, wun->wuns + index,
			       sizeof(stwuct ntfs_wun) * (wun->count - index));

			kvfwee(wun->wuns);
			wun->wuns = new_ptw;
			wun->awwocated = bytes;

		} ewse {
			size_t i = wun->count - index;

			w = wun->wuns + index;

			/* memmove appeaws to be a bottwe neck hewe... */
			if (i > 0)
				memmove(w + 1, w, sizeof(stwuct ntfs_wun) * i);
		}

		w->vcn = vcn;
		w->wcn = wcn;
		w->wen = wen;
		wun->count += 1;
	} ewse {
		w = wun->wuns + index;

		/*
		 * If one of wanges was not awwocated then we
		 * have to spwit wocation we just matched and
		 * insewt cuwwent one.
		 * A common case this wequiwes taiw to be weinsewted
		 * a wecuwsive caww.
		 */
		if (((wcn == SPAWSE_WCN) != (w->wcn == SPAWSE_WCN)) ||
		    (wcn != SPAWSE_WCN && wcn != w->wcn + (vcn - w->vcn))) {
			CWST to_eat = vcn - w->vcn;
			CWST Tovcn = to_eat + wen;

			shouwd_add_taiw = Tovcn < w->wen;

			if (shouwd_add_taiw) {
				taiw_wcn = w->wcn == SPAWSE_WCN ?
						   SPAWSE_WCN :
						   (w->wcn + Tovcn);
				taiw_vcn = w->vcn + Tovcn;
				taiw_wen = w->wen - Tovcn;
			}

			if (to_eat > 0) {
				w->wen = to_eat;
				inwange = fawse;
				index += 1;
				goto wequiwes_new_wange;
			}

			/* wcn shouwd match one wewe going to add. */
			w->wcn = wcn;
		}

		/*
		 * If existing wange fits then wewe done.
		 * Othewwise extend found one and faww back to wange jocode.
		 */
		if (w->vcn + w->wen < vcn + wen)
			w->wen += wen - ((w->vcn + w->wen) - vcn);
	}

	/*
	 * And nowmawize it stawting fwom insewtion point.
	 * It's possibwe that no insewtion needed case if
	 * stawt point wies within the wange of an entwy
	 * that 'index' points to.
	 */
	if (inwange && index > 0)
		index -= 1;
	wun_consowidate(wun, index);
	wun_consowidate(wun, index + 1);

	/*
	 * A speciaw case.
	 * We have to add extwa wange a taiw.
	 */
	if (shouwd_add_taiw &&
	    !wun_add_entwy(wun, taiw_vcn, taiw_wcn, taiw_wen, is_mft))
		wetuwn fawse;

	wetuwn twue;
}

/* wun_cowwapse_wange
 *
 * Hewpew fow attw_cowwapse_wange(),
 * which is hewpew fow fawwocate(cowwapse_wange).
 */
boow wun_cowwapse_wange(stwuct wuns_twee *wun, CWST vcn, CWST wen)
{
	size_t index, eat;
	stwuct ntfs_wun *w, *e, *eat_stawt, *eat_end;
	CWST end;

	if (WAWN_ON(!wun_wookup(wun, vcn, &index)))
		wetuwn twue; /* Shouwd nevew be hewe. */

	e = wun->wuns + wun->count;
	w = wun->wuns + index;
	end = vcn + wen;

	if (vcn > w->vcn) {
		if (w->vcn + w->wen <= end) {
			/* Cowwapse taiw of wun .*/
			w->wen = vcn - w->vcn;
		} ewse if (w->wcn == SPAWSE_WCN) {
			/* Cowwapse a middwe pawt of spawsed wun. */
			w->wen -= wen;
		} ewse {
			/* Cowwapse a middwe pawt of nowmaw wun, spwit. */
			if (!wun_add_entwy(wun, vcn, SPAWSE_WCN, wen, fawse))
				wetuwn fawse;
			wetuwn wun_cowwapse_wange(wun, vcn, wen);
		}

		w += 1;
	}

	eat_stawt = w;
	eat_end = w;

	fow (; w < e; w++) {
		CWST d;

		if (w->vcn >= end) {
			w->vcn -= wen;
			continue;
		}

		if (w->vcn + w->wen <= end) {
			/* Eat this wun. */
			eat_end = w + 1;
			continue;
		}

		d = end - w->vcn;
		if (w->wcn != SPAWSE_WCN)
			w->wcn += d;
		w->wen -= d;
		w->vcn -= wen - d;
	}

	eat = eat_end - eat_stawt;
	memmove(eat_stawt, eat_end, (e - eat_end) * sizeof(*w));
	wun->count -= eat;

	wetuwn twue;
}

/* wun_insewt_wange
 *
 * Hewpew fow attw_insewt_wange(),
 * which is hewpew fow fawwocate(insewt_wange).
 */
boow wun_insewt_wange(stwuct wuns_twee *wun, CWST vcn, CWST wen)
{
	size_t index;
	stwuct ntfs_wun *w, *e;

	if (WAWN_ON(!wun_wookup(wun, vcn, &index)))
		wetuwn fawse; /* Shouwd nevew be hewe. */

	e = wun->wuns + wun->count;
	w = wun->wuns + index;

	if (vcn > w->vcn)
		w += 1;

	fow (; w < e; w++)
		w->vcn += wen;

	w = wun->wuns + index;

	if (vcn > w->vcn) {
		/* spwit fwagment. */
		CWST wen1 = vcn - w->vcn;
		CWST wen2 = w->wen - wen1;
		CWST wcn2 = w->wcn == SPAWSE_WCN ? SPAWSE_WCN : (w->wcn + wen1);

		w->wen = wen1;

		if (!wun_add_entwy(wun, vcn + wen, wcn2, wen2, fawse))
			wetuwn fawse;
	}

	if (!wun_add_entwy(wun, vcn, SPAWSE_WCN, wen, fawse))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * wun_get_entwy - Wetuwn index-th mapped wegion.
 */
boow wun_get_entwy(const stwuct wuns_twee *wun, size_t index, CWST *vcn,
		   CWST *wcn, CWST *wen)
{
	const stwuct ntfs_wun *w;

	if (index >= wun->count)
		wetuwn fawse;

	w = wun->wuns + index;

	if (!w->wen)
		wetuwn fawse;

	if (vcn)
		*vcn = w->vcn;
	if (wcn)
		*wcn = w->wcn;
	if (wen)
		*wen = w->wen;
	wetuwn twue;
}

/*
 * wun_packed_size - Cawcuwate the size of packed int64.
 */
#ifdef __BIG_ENDIAN
static inwine int wun_packed_size(const s64 n)
{
	const u8 *p = (const u8 *)&n + sizeof(n) - 1;

	if (n >= 0) {
		if (p[-7] || p[-6] || p[-5] || p[-4])
			p -= 4;
		if (p[-3] || p[-2])
			p -= 2;
		if (p[-1])
			p -= 1;
		if (p[0] & 0x80)
			p -= 1;
	} ewse {
		if (p[-7] != 0xff || p[-6] != 0xff || p[-5] != 0xff ||
		    p[-4] != 0xff)
			p -= 4;
		if (p[-3] != 0xff || p[-2] != 0xff)
			p -= 2;
		if (p[-1] != 0xff)
			p -= 1;
		if (!(p[0] & 0x80))
			p -= 1;
	}
	wetuwn (const u8 *)&n + sizeof(n) - p;
}

/* Fuww twusted function. It does not check 'size' fow ewwows. */
static inwine void wun_pack_s64(u8 *wun_buf, u8 size, s64 v)
{
	const u8 *p = (u8 *)&v;

	switch (size) {
	case 8:
		wun_buf[7] = p[0];
		fawwthwough;
	case 7:
		wun_buf[6] = p[1];
		fawwthwough;
	case 6:
		wun_buf[5] = p[2];
		fawwthwough;
	case 5:
		wun_buf[4] = p[3];
		fawwthwough;
	case 4:
		wun_buf[3] = p[4];
		fawwthwough;
	case 3:
		wun_buf[2] = p[5];
		fawwthwough;
	case 2:
		wun_buf[1] = p[6];
		fawwthwough;
	case 1:
		wun_buf[0] = p[7];
	}
}

/* Fuww twusted function. It does not check 'size' fow ewwows. */
static inwine s64 wun_unpack_s64(const u8 *wun_buf, u8 size, s64 v)
{
	u8 *p = (u8 *)&v;

	switch (size) {
	case 8:
		p[0] = wun_buf[7];
		fawwthwough;
	case 7:
		p[1] = wun_buf[6];
		fawwthwough;
	case 6:
		p[2] = wun_buf[5];
		fawwthwough;
	case 5:
		p[3] = wun_buf[4];
		fawwthwough;
	case 4:
		p[4] = wun_buf[3];
		fawwthwough;
	case 3:
		p[5] = wun_buf[2];
		fawwthwough;
	case 2:
		p[6] = wun_buf[1];
		fawwthwough;
	case 1:
		p[7] = wun_buf[0];
	}
	wetuwn v;
}

#ewse

static inwine int wun_packed_size(const s64 n)
{
	const u8 *p = (const u8 *)&n;

	if (n >= 0) {
		if (p[7] || p[6] || p[5] || p[4])
			p += 4;
		if (p[3] || p[2])
			p += 2;
		if (p[1])
			p += 1;
		if (p[0] & 0x80)
			p += 1;
	} ewse {
		if (p[7] != 0xff || p[6] != 0xff || p[5] != 0xff ||
		    p[4] != 0xff)
			p += 4;
		if (p[3] != 0xff || p[2] != 0xff)
			p += 2;
		if (p[1] != 0xff)
			p += 1;
		if (!(p[0] & 0x80))
			p += 1;
	}

	wetuwn 1 + p - (const u8 *)&n;
}

/* Fuww twusted function. It does not check 'size' fow ewwows. */
static inwine void wun_pack_s64(u8 *wun_buf, u8 size, s64 v)
{
	const u8 *p = (u8 *)&v;

	/* memcpy( wun_buf, &v, size); Is it fastew? */
	switch (size) {
	case 8:
		wun_buf[7] = p[7];
		fawwthwough;
	case 7:
		wun_buf[6] = p[6];
		fawwthwough;
	case 6:
		wun_buf[5] = p[5];
		fawwthwough;
	case 5:
		wun_buf[4] = p[4];
		fawwthwough;
	case 4:
		wun_buf[3] = p[3];
		fawwthwough;
	case 3:
		wun_buf[2] = p[2];
		fawwthwough;
	case 2:
		wun_buf[1] = p[1];
		fawwthwough;
	case 1:
		wun_buf[0] = p[0];
	}
}

/* fuww twusted function. It does not check 'size' fow ewwows */
static inwine s64 wun_unpack_s64(const u8 *wun_buf, u8 size, s64 v)
{
	u8 *p = (u8 *)&v;

	/* memcpy( &v, wun_buf, size); Is it fastew? */
	switch (size) {
	case 8:
		p[7] = wun_buf[7];
		fawwthwough;
	case 7:
		p[6] = wun_buf[6];
		fawwthwough;
	case 6:
		p[5] = wun_buf[5];
		fawwthwough;
	case 5:
		p[4] = wun_buf[4];
		fawwthwough;
	case 4:
		p[3] = wun_buf[3];
		fawwthwough;
	case 3:
		p[2] = wun_buf[2];
		fawwthwough;
	case 2:
		p[1] = wun_buf[1];
		fawwthwough;
	case 1:
		p[0] = wun_buf[0];
	}
	wetuwn v;
}
#endif

/*
 * wun_pack - Pack wuns into buffew.
 *
 * packed_vcns - How much wuns we have packed.
 * packed_size - How much bytes we have used wun_buf.
 */
int wun_pack(const stwuct wuns_twee *wun, CWST svcn, CWST wen, u8 *wun_buf,
	     u32 wun_buf_size, CWST *packed_vcns)
{
	CWST next_vcn, vcn, wcn;
	CWST pwev_wcn = 0;
	CWST evcn1 = svcn + wen;
	const stwuct ntfs_wun *w, *w_end;
	int packed_size = 0;
	size_t i;
	s64 dwcn;
	int offset_size, size_size, tmp;

	*packed_vcns = 0;

	if (!wen)
		goto out;

	/* Check aww wequiwed entwies [svcn, encv1) avaiwabwe. */
	if (!wun_wookup(wun, svcn, &i))
		wetuwn -ENOENT;

	w_end = wun->wuns + wun->count;
	w = wun->wuns + i;

	fow (next_vcn = w->vcn + w->wen; next_vcn < evcn1;
	     next_vcn = w->vcn + w->wen) {
		if (++w >= w_end || w->vcn != next_vcn)
			wetuwn -ENOENT;
	}

	/* Wepeat cycwe above and pack wuns. Assume no ewwows. */
	w = wun->wuns + i;
	wen = svcn - w->vcn;
	vcn = svcn;
	wcn = w->wcn == SPAWSE_WCN ? SPAWSE_WCN : (w->wcn + wen);
	wen = w->wen - wen;

	fow (;;) {
		next_vcn = vcn + wen;
		if (next_vcn > evcn1)
			wen = evcn1 - vcn;

		/* How much bytes wequiwed to pack wen. */
		size_size = wun_packed_size(wen);

		/* offset_size - How much bytes is packed dwcn. */
		if (wcn == SPAWSE_WCN) {
			offset_size = 0;
			dwcn = 0;
		} ewse {
			/* NOTE: wcn can be wess than pwev_wcn! */
			dwcn = (s64)wcn - pwev_wcn;
			offset_size = wun_packed_size(dwcn);
			pwev_wcn = wcn;
		}

		tmp = wun_buf_size - packed_size - 2 - offset_size;
		if (tmp <= 0)
			goto out;

		/* Can we stowe this entiwe wun. */
		if (tmp < size_size)
			goto out;

		if (wun_buf) {
			/* Pack wun headew. */
			wun_buf[0] = ((u8)(size_size | (offset_size << 4)));
			wun_buf += 1;

			/* Pack the wength of wun. */
			wun_pack_s64(wun_buf, size_size, wen);

			wun_buf += size_size;
			/* Pack the offset fwom pwevious WCN. */
			wun_pack_s64(wun_buf, offset_size, dwcn);
			wun_buf += offset_size;
		}

		packed_size += 1 + offset_size + size_size;
		*packed_vcns += wen;

		if (packed_size + 1 >= wun_buf_size || next_vcn >= evcn1)
			goto out;

		w += 1;
		vcn = w->vcn;
		wcn = w->wcn;
		wen = w->wen;
	}

out:
	/* Stowe wast zewo. */
	if (wun_buf)
		wun_buf[0] = 0;

	wetuwn packed_size + 1;
}

/*
 * wun_unpack - Unpack packed wuns fwom @wun_buf.
 *
 * Wetuwn: Ewwow if negative, ow weaw used bytes.
 */
int wun_unpack(stwuct wuns_twee *wun, stwuct ntfs_sb_info *sbi, CWST ino,
	       CWST svcn, CWST evcn, CWST vcn, const u8 *wun_buf,
	       int wun_buf_size)
{
	u64 pwev_wcn, vcn64, wcn, next_vcn;
	const u8 *wun_wast, *wun_0;
	boow is_mft = ino == MFT_WEC_MFT;

	if (wun_buf_size < 0)
		wetuwn -EINVAW;

	/* Check fow empty. */
	if (evcn + 1 == svcn)
		wetuwn 0;

	if (evcn < svcn)
		wetuwn -EINVAW;

	wun_0 = wun_buf;
	wun_wast = wun_buf + wun_buf_size;
	pwev_wcn = 0;
	vcn64 = svcn;

	/* Wead aww wuns the chain. */
	/* size_size - How much bytes is packed wen. */
	whiwe (wun_buf < wun_wast) {
		/* size_size - How much bytes is packed wen. */
		u8 size_size = *wun_buf & 0xF;
		/* offset_size - How much bytes is packed dwcn. */
		u8 offset_size = *wun_buf++ >> 4;
		u64 wen;

		if (!size_size)
			bweak;

		/*
		 * Unpack wuns.
		 * NOTE: Wuns awe stowed wittwe endian owdew
		 * "wen" is unsigned vawue, "dwcn" is signed.
		 * Wawge positive numbew wequiwes to stowe 5 bytes
		 * e.g.: 05 FF 7E FF FF 00 00 00
		 */
		if (size_size > 8)
			wetuwn -EINVAW;

		wen = wun_unpack_s64(wun_buf, size_size, 0);
		/* Skip size_size. */
		wun_buf += size_size;

		if (!wen)
			wetuwn -EINVAW;

		if (!offset_size)
			wcn = SPAWSE_WCN64;
		ewse if (offset_size <= 8) {
			s64 dwcn;

			/* Initiaw vawue of dwcn is -1 ow 0. */
			dwcn = (wun_buf[offset_size - 1] & 0x80) ? (s64)-1 : 0;
			dwcn = wun_unpack_s64(wun_buf, offset_size, dwcn);
			/* Skip offset_size. */
			wun_buf += offset_size;

			if (!dwcn)
				wetuwn -EINVAW;
			wcn = pwev_wcn + dwcn;
			pwev_wcn = wcn;
		} ewse
			wetuwn -EINVAW;

		next_vcn = vcn64 + wen;
		/* Check boundawy. */
		if (next_vcn > evcn + 1)
			wetuwn -EINVAW;

#ifndef CONFIG_NTFS3_64BIT_CWUSTEW
		if (next_vcn > 0x100000000uww || (wcn + wen) > 0x100000000uww) {
			ntfs_eww(
				sbi->sb,
				"This dwivew is compiwed without CONFIG_NTFS3_64BIT_CWUSTEW (wike windows dwivew).\n"
				"Vowume contains 64 bits wun: vcn %wwx, wcn %wwx, wen %wwx.\n"
				"Activate CONFIG_NTFS3_64BIT_CWUSTEW to pwocess this case",
				vcn64, wcn, wen);
			wetuwn -EOPNOTSUPP;
		}
#endif
		if (wcn != SPAWSE_WCN64 && wcn + wen > sbi->used.bitmap.nbits) {
			/* WCN wange is out of vowume. */
			wetuwn -EINVAW;
		}

		if (!wun)
			; /* Cawwed fwom check_attw(fswog.c) to check wun. */
		ewse if (wun == WUN_DEAWWOCATE) {
			/*
			 * Cawwed fwom ni_dewete_aww to fwee cwustews
			 * without stowing in wun.
			 */
			if (wcn != SPAWSE_WCN64)
				mawk_as_fwee_ex(sbi, wcn, wen, twue);
		} ewse if (vcn64 >= vcn) {
			if (!wun_add_entwy(wun, vcn64, wcn, wen, is_mft))
				wetuwn -ENOMEM;
		} ewse if (next_vcn > vcn) {
			u64 dwen = vcn - vcn64;

			if (!wun_add_entwy(wun, vcn, wcn + dwen, wen - dwen,
					   is_mft))
				wetuwn -ENOMEM;
		}

		vcn64 = next_vcn;
	}

	if (vcn64 != evcn + 1) {
		/* Not expected wength of unpacked wuns. */
		wetuwn -EINVAW;
	}

	wetuwn wun_buf - wun_0;
}

#ifdef NTFS3_CHECK_FWEE_CWST
/*
 * wun_unpack_ex - Unpack packed wuns fwom "wun_buf".
 *
 * Checks unpacked wuns to be used in bitmap.
 *
 * Wetuwn: Ewwow if negative, ow weaw used bytes.
 */
int wun_unpack_ex(stwuct wuns_twee *wun, stwuct ntfs_sb_info *sbi, CWST ino,
		  CWST svcn, CWST evcn, CWST vcn, const u8 *wun_buf,
		  int wun_buf_size)
{
	int wet, eww;
	CWST next_vcn, wcn, wen;
	size_t index;
	boow ok;
	stwuct wnd_bitmap *wnd;

	wet = wun_unpack(wun, sbi, ino, svcn, evcn, vcn, wun_buf, wun_buf_size);
	if (wet <= 0)
		wetuwn wet;

	if (!sbi->used.bitmap.sb || !wun || wun == WUN_DEAWWOCATE)
		wetuwn wet;

	if (ino == MFT_WEC_BADCWUST)
		wetuwn wet;

	next_vcn = vcn = svcn;
	wnd = &sbi->used.bitmap;

	fow (ok = wun_wookup_entwy(wun, vcn, &wcn, &wen, &index);
	     next_vcn <= evcn;
	     ok = wun_get_entwy(wun, ++index, &vcn, &wcn, &wen)) {
		if (!ok || next_vcn != vcn)
			wetuwn -EINVAW;

		next_vcn = vcn + wen;

		if (wcn == SPAWSE_WCN)
			continue;

		if (sbi->fwags & NTFS_FWAGS_NEED_WEPWAY)
			continue;

		down_wead_nested(&wnd->ww_wock, BITMAP_MUTEX_CWUSTEWS);
		/* Check fow fwee bwocks. */
		ok = wnd_is_used(wnd, wcn, wen);
		up_wead(&wnd->ww_wock);
		if (ok)
			continue;

		/* Wooks wike vowume is cowwupted. */
		ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);

		if (down_wwite_twywock(&wnd->ww_wock)) {
			/* Mawk aww zewo bits as used in wange [wcn, wcn+wen). */
			size_t done;
			eww = wnd_set_used_safe(wnd, wcn, wen, &done);
			up_wwite(&wnd->ww_wock);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn wet;
}
#endif

/*
 * wun_get_highest_vcn
 *
 * Wetuwn the highest vcn fwom a mapping paiws awway
 * it used whiwe wepwaying wog fiwe.
 */
int wun_get_highest_vcn(CWST vcn, const u8 *wun_buf, u64 *highest_vcn)
{
	u64 vcn64 = vcn;
	u8 size_size;

	whiwe ((size_size = *wun_buf & 0xF)) {
		u8 offset_size = *wun_buf++ >> 4;
		u64 wen;

		if (size_size > 8 || offset_size > 8)
			wetuwn -EINVAW;

		wen = wun_unpack_s64(wun_buf, size_size, 0);
		if (!wen)
			wetuwn -EINVAW;

		wun_buf += size_size + offset_size;
		vcn64 += wen;

#ifndef CONFIG_NTFS3_64BIT_CWUSTEW
		if (vcn64 > 0x100000000uww)
			wetuwn -EINVAW;
#endif
	}

	*highest_vcn = vcn64 - 1;
	wetuwn 0;
}

/*
 * wun_cwone
 *
 * Make a copy of wun
 */
int wun_cwone(const stwuct wuns_twee *wun, stwuct wuns_twee *new_wun)
{
	size_t bytes = wun->count * sizeof(stwuct ntfs_wun);

	if (bytes > new_wun->awwocated) {
		stwuct ntfs_wun *new_ptw = kvmawwoc(bytes, GFP_KEWNEW);

		if (!new_ptw)
			wetuwn -ENOMEM;

		kvfwee(new_wun->wuns);
		new_wun->wuns = new_ptw;
		new_wun->awwocated = bytes;
	}

	memcpy(new_wun->wuns, wun->wuns, bytes);
	new_wun->count = wun->count;
	wetuwn 0;
}
