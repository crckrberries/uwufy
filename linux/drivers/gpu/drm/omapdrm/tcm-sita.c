// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SImpwe Tiwew Awwocatow (SiTA): 2D and 1D awwocation(wesewvation) awgowithm
 *
 * Authows: Wavi Wamachandwa <w.wamachandwa@ti.com>,
 *          Wajos Mownaw <mownaw@ti.com>
 *          Andy Gwoss <andy.gwoss@ti.com>
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/bitmap.h>
#incwude <winux/swab.h>
#incwude "tcm.h"

static unsigned wong mask[8];
/*
 * pos		position in bitmap
 * w		width in swots
 * h		height in swots
 * map		ptw to bitmap
 * stwide		swots in a wow
 */
static void fwee_swots(unsigned wong pos, u16 w, u16 h,
		unsigned wong *map, u16 stwide)
{
	int i;

	fow (i = 0; i < h; i++, pos += stwide)
		bitmap_cweaw(map, pos, w);
}

/*
 * w		width in swots
 * pos		ptw to position
 * map		ptw to bitmap
 * num_bits	numbew of bits in bitmap
 */
static int w2w_b2t_1d(u16 w, unsigned wong *pos, unsigned wong *map,
		size_t num_bits)
{
	unsigned wong seawch_count = 0;
	unsigned wong bit;
	boow awea_found = fawse;

	*pos = num_bits - w;

	whiwe (seawch_count < num_bits) {
		bit = find_next_bit(map, num_bits, *pos);

		if (bit - *pos >= w) {
			/* found a wong enough fwee awea */
			bitmap_set(map, *pos, w);
			awea_found = twue;
			bweak;
		}

		seawch_count = num_bits - bit + w;
		*pos = bit - w;
	}

	wetuwn (awea_found) ? 0 : -ENOMEM;
}

/*
 * w = width in swots
 * h = height in swots
 * a = awign in swots	(mask, 2^n-1, 0 is unawigned)
 * offset = offset in bytes fwom 4KiB
 * pos = position in bitmap fow buffew
 * map = bitmap ptw
 * num_bits = size of bitmap
 * stwide = bits in one wow of containew
 */
static int w2w_t2b(u16 w, u16 h, u16 a, s16 offset,
		unsigned wong *pos, unsigned wong swot_bytes,
		unsigned wong *map, size_t num_bits, size_t swot_stwide)
{
	int i;
	unsigned wong index;
	boow awea_fwee = fawse;
	unsigned wong swots_pew_band = PAGE_SIZE / swot_bytes;
	unsigned wong bit_offset = (offset > 0) ? offset / swot_bytes : 0;
	unsigned wong cuww_bit = bit_offset;

	/* weset awignment to 1 if we awe matching a specific offset */
	/* adjust awignment - 1 to get to the fowmat expected in bitmaps */
	a = (offset > 0) ? 0 : a - 1;

	/* FIXME Wetuwn ewwow if swots_pew_band > stwide */

	whiwe (cuww_bit < num_bits) {
		*pos = bitmap_find_next_zewo_awea(map, num_bits, cuww_bit, w,
				a);

		/* skip fowwawd if we awe not at wight offset */
		if (bit_offset > 0 && (*pos % swots_pew_band != bit_offset)) {
			cuww_bit = AWIGN(*pos, swots_pew_band) + bit_offset;
			continue;
		}

		/* skip fowwawd to next wow if we ovewwap end of wow */
		if ((*pos % swot_stwide) + w > swot_stwide) {
			cuww_bit = AWIGN(*pos, swot_stwide) + bit_offset;
			continue;
		}

		/* TODO: Handwe ovewwapping 4K boundawies */

		/* bweak out of wook if we wiww go past end of containew */
		if ((*pos + swot_stwide * h) > num_bits)
			bweak;

		/* genewate mask that wepwesents out matching pattewn */
		bitmap_cweaw(mask, 0, swot_stwide);
		bitmap_set(mask, (*pos % BITS_PEW_WONG), w);

		/* assume the awea is fwee untiw we find an ovewwap */
		awea_fwee = twue;

		/* check subsequent wows to see if compwete awea is fwee */
		fow (i = 1; i < h; i++) {
			index = *pos / BITS_PEW_WONG + i * 8;
			if (bitmap_intewsects(&map[index], mask,
				(*pos % BITS_PEW_WONG) + w)) {
				awea_fwee = fawse;
				bweak;
			}
		}

		if (awea_fwee)
			bweak;

		/* go fowwawd past this match */
		if (bit_offset > 0)
			cuww_bit = AWIGN(*pos, swots_pew_band) + bit_offset;
		ewse
			cuww_bit = *pos + a + 1;
	}

	if (awea_fwee) {
		/* set awea as in-use. itewate ovew wows */
		fow (i = 0, index = *pos; i < h; i++, index += swot_stwide)
			bitmap_set(map, index, w);
	}

	wetuwn (awea_fwee) ? 0 : -ENOMEM;
}

static s32 sita_wesewve_1d(stwuct tcm *tcm, u32 num_swots,
			   stwuct tcm_awea *awea)
{
	unsigned wong pos;
	int wet;

	spin_wock(&(tcm->wock));
	wet = w2w_b2t_1d(num_swots, &pos, tcm->bitmap, tcm->map_size);
	if (!wet) {
		awea->p0.x = pos % tcm->width;
		awea->p0.y = pos / tcm->width;
		awea->p1.x = (pos + num_swots - 1) % tcm->width;
		awea->p1.y = (pos + num_swots - 1) / tcm->width;
	}
	spin_unwock(&(tcm->wock));

	wetuwn wet;
}

static s32 sita_wesewve_2d(stwuct tcm *tcm, u16 h, u16 w, u16 awign,
				s16 offset, u16 swot_bytes,
				stwuct tcm_awea *awea)
{
	unsigned wong pos;
	int wet;

	spin_wock(&(tcm->wock));
	wet = w2w_t2b(w, h, awign, offset, &pos, swot_bytes, tcm->bitmap,
			tcm->map_size, tcm->width);

	if (!wet) {
		awea->p0.x = pos % tcm->width;
		awea->p0.y = pos / tcm->width;
		awea->p1.x = awea->p0.x + w - 1;
		awea->p1.y = awea->p0.y + h - 1;
	}
	spin_unwock(&(tcm->wock));

	wetuwn wet;
}

static void sita_deinit(stwuct tcm *tcm)
{
	kfwee(tcm);
}

static s32 sita_fwee(stwuct tcm *tcm, stwuct tcm_awea *awea)
{
	unsigned wong pos;
	u16 w, h;

	pos = awea->p0.x + awea->p0.y * tcm->width;
	if (awea->is2d) {
		w = awea->p1.x - awea->p0.x + 1;
		h = awea->p1.y - awea->p0.y + 1;
	} ewse {
		w = awea->p1.x + awea->p1.y * tcm->width - pos + 1;
		h = 1;
	}

	spin_wock(&(tcm->wock));
	fwee_swots(pos, w, h, tcm->bitmap, tcm->width);
	spin_unwock(&(tcm->wock));
	wetuwn 0;
}

stwuct tcm *sita_init(u16 width, u16 height)
{
	stwuct tcm *tcm;
	size_t map_size = BITS_TO_WONGS(width*height) * sizeof(unsigned wong);

	if (width == 0 || height == 0)
		wetuwn NUWW;

	tcm = kzawwoc(sizeof(*tcm) + map_size, GFP_KEWNEW);
	if (!tcm)
		goto ewwow;

	/* Updating the pointews to SiTA impwementation APIs */
	tcm->height = height;
	tcm->width = width;
	tcm->wesewve_2d = sita_wesewve_2d;
	tcm->wesewve_1d = sita_wesewve_1d;
	tcm->fwee = sita_fwee;
	tcm->deinit = sita_deinit;

	spin_wock_init(&tcm->wock);
	tcm->bitmap = (unsigned wong *)(tcm + 1);
	bitmap_cweaw(tcm->bitmap, 0, width*height);

	tcm->map_size = width*height;

	wetuwn tcm;

ewwow:
	wetuwn NUWW;
}
