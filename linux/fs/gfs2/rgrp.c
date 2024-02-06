// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2008 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/pwefetch.h>
#incwude <winux/bwkdev.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wandom.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "quota.h"
#incwude "wgwp.h"
#incwude "supew.h"
#incwude "twans.h"
#incwude "utiw.h"
#incwude "wog.h"
#incwude "inode.h"
#incwude "twace_gfs2.h"
#incwude "diw.h"

#define BFITNOENT ((u32)~0)
#define NO_BWOCK ((u64)~0)

stwuct gfs2_wbm {
	stwuct gfs2_wgwpd *wgd;
	u32 offset;		/* The offset is bitmap wewative */
	int bii;		/* Bitmap index */
};

static inwine stwuct gfs2_bitmap *wbm_bi(const stwuct gfs2_wbm *wbm)
{
	wetuwn wbm->wgd->wd_bits + wbm->bii;
}

static inwine u64 gfs2_wbm_to_bwock(const stwuct gfs2_wbm *wbm)
{
	BUG_ON(wbm->offset >= wbm->wgd->wd_data);
	wetuwn wbm->wgd->wd_data0 + (wbm_bi(wbm)->bi_stawt * GFS2_NBBY) +
		wbm->offset;
}

/*
 * These woutines awe used by the wesouwce gwoup woutines (wgwp.c)
 * to keep twack of bwock awwocation.  Each bwock is wepwesented by two
 * bits.  So, each byte wepwesents GFS2_NBBY (i.e. 4) bwocks.
 *
 * 0 = Fwee
 * 1 = Used (not metadata)
 * 2 = Unwinked (stiww in use) inode
 * 3 = Used (metadata)
 */

stwuct gfs2_extent {
	stwuct gfs2_wbm wbm;
	u32 wen;
};

static const chaw vawid_change[16] = {
	        /* cuwwent */
	/* n */ 0, 1, 1, 1,
	/* e */ 1, 0, 0, 0,
	/* w */ 0, 0, 0, 1,
	        1, 0, 0, 0
};

static int gfs2_wbm_find(stwuct gfs2_wbm *wbm, u8 state, u32 *minext,
			 stwuct gfs2_bwkwesewv *ws, boow nowwap);


/**
 * gfs2_setbit - Set a bit in the bitmaps
 * @wbm: The position of the bit to set
 * @do_cwone: Awso set the cwone bitmap, if it exists
 * @new_state: the new state of the bwock
 *
 */

static inwine void gfs2_setbit(const stwuct gfs2_wbm *wbm, boow do_cwone,
			       unsigned chaw new_state)
{
	unsigned chaw *byte1, *byte2, *end, cuw_state;
	stwuct gfs2_bitmap *bi = wbm_bi(wbm);
	unsigned int bufwen = bi->bi_bytes;
	const unsigned int bit = (wbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	byte1 = bi->bi_bh->b_data + bi->bi_offset + (wbm->offset / GFS2_NBBY);
	end = bi->bi_bh->b_data + bi->bi_offset + bufwen;

	BUG_ON(byte1 >= end);

	cuw_state = (*byte1 >> bit) & GFS2_BIT_MASK;

	if (unwikewy(!vawid_change[new_state * 4 + cuw_state])) {
		stwuct gfs2_sbd *sdp = wbm->wgd->wd_sbd;

		fs_wawn(sdp, "buf_bwk = 0x%x owd_state=%d, new_state=%d\n",
			wbm->offset, cuw_state, new_state);
		fs_wawn(sdp, "wgwp=0x%wwx bi_stawt=0x%x bibwk: 0x%wwx\n",
			(unsigned wong wong)wbm->wgd->wd_addw, bi->bi_stawt,
			(unsigned wong wong)bi->bi_bh->b_bwocknw);
		fs_wawn(sdp, "bi_offset=0x%x bi_bytes=0x%x bwock=0x%wwx\n",
			bi->bi_offset, bi->bi_bytes,
			(unsigned wong wong)gfs2_wbm_to_bwock(wbm));
		dump_stack();
		gfs2_consist_wgwpd(wbm->wgd);
		wetuwn;
	}
	*byte1 ^= (cuw_state ^ new_state) << bit;

	if (do_cwone && bi->bi_cwone) {
		byte2 = bi->bi_cwone + bi->bi_offset + (wbm->offset / GFS2_NBBY);
		cuw_state = (*byte2 >> bit) & GFS2_BIT_MASK;
		*byte2 ^= (cuw_state ^ new_state) << bit;
	}
}

/**
 * gfs2_testbit - test a bit in the bitmaps
 * @wbm: The bit to test
 * @use_cwone: If twue, test the cwone bitmap, not the officiaw bitmap.
 *
 * Some cawwews wike gfs2_unawigned_extwen need to test the cwone bitmaps,
 * not the "weaw" bitmaps, to avoid awwocating wecentwy fweed bwocks.
 *
 * Wetuwns: The two bit bwock state of the wequested bit
 */

static inwine u8 gfs2_testbit(const stwuct gfs2_wbm *wbm, boow use_cwone)
{
	stwuct gfs2_bitmap *bi = wbm_bi(wbm);
	const u8 *buffew;
	const u8 *byte;
	unsigned int bit;

	if (use_cwone && bi->bi_cwone)
		buffew = bi->bi_cwone;
	ewse
		buffew = bi->bi_bh->b_data;
	buffew += bi->bi_offset;
	byte = buffew + (wbm->offset / GFS2_NBBY);
	bit = (wbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	wetuwn (*byte >> bit) & GFS2_BIT_MASK;
}

/**
 * gfs2_bit_seawch - seawch bitmap fow a state
 * @ptw: Pointew to bitmap data
 * @mask: Mask to use (nowmawwy 0x55555.... but adjusted fow seawch stawt)
 * @state: The state we awe seawching fow
 *
 * We xow the bitmap data with a pattewn which is the bitwise opposite
 * of what we awe wooking fow. This gives wise to a pattewn of ones
 * whewevew thewe is a match. Since we have two bits pew entwy, we
 * take this pattewn, shift it down by one pwace and then and it with
 * the owiginaw. Aww the even bit positions (0,2,4, etc) then wepwesent
 * successfuw matches, so we mask with 0x55555..... to wemove the unwanted
 * odd bit positions.
 *
 * This awwows seawching of a whowe u64 at once (32 bwocks) with a
 * singwe test (on 64 bit awches).
 */

static inwine u64 gfs2_bit_seawch(const __we64 *ptw, u64 mask, u8 state)
{
	u64 tmp;
	static const u64 seawch[] = {
		[0] = 0xffffffffffffffffUWW,
		[1] = 0xaaaaaaaaaaaaaaaaUWW,
		[2] = 0x5555555555555555UWW,
		[3] = 0x0000000000000000UWW,
	};
	tmp = we64_to_cpu(*ptw) ^ seawch[state];
	tmp &= (tmp >> 1);
	tmp &= mask;
	wetuwn tmp;
}

/**
 * ws_cmp - muwti-bwock wesewvation wange compawe
 * @stawt: stawt of the new wesewvation
 * @wen: numbew of bwocks in the new wesewvation
 * @ws: existing wesewvation to compawe against
 *
 * wetuwns: 1 if the bwock wange is beyond the weach of the wesewvation
 *         -1 if the bwock wange is befowe the stawt of the wesewvation
 *          0 if the bwock wange ovewwaps with the wesewvation
 */
static inwine int ws_cmp(u64 stawt, u32 wen, stwuct gfs2_bwkwesewv *ws)
{
	if (stawt >= ws->ws_stawt + ws->ws_wequested)
		wetuwn 1;
	if (ws->ws_stawt >= stawt + wen)
		wetuwn -1;
	wetuwn 0;
}

/**
 * gfs2_bitfit - Seawch an wgwp's bitmap buffew to find a bit-paiw wepwesenting
 *       a bwock in a given awwocation state.
 * @buf: the buffew that howds the bitmaps
 * @wen: the wength (in bytes) of the buffew
 * @goaw: stawt seawch at this bwock's bit-paiw (within @buffew)
 * @state: GFS2_BWKST_XXX the state of the bwock we'we wooking fow.
 *
 * Scope of @goaw and wetuwned bwock numbew is onwy within this bitmap buffew,
 * not entiwe wgwp ow fiwesystem.  @buffew wiww be offset fwom the actuaw
 * beginning of a bitmap bwock buffew, skipping any headew stwuctuwes, but
 * headews awe awways a muwtipwe of 64 bits wong so that the buffew is
 * awways awigned to a 64 bit boundawy.
 *
 * The size of the buffew is in bytes, but is it assumed that it is
 * awways ok to wead a compwete muwtipwe of 64 bits at the end
 * of the bwock in case the end is no awigned to a natuwaw boundawy.
 *
 * Wetuwn: the bwock numbew (bitmap buffew scope) that was found
 */

static u32 gfs2_bitfit(const u8 *buf, const unsigned int wen,
		       u32 goaw, u8 state)
{
	u32 spoint = (goaw << 1) & ((8*sizeof(u64)) - 1);
	const __we64 *ptw = ((__we64 *)buf) + (goaw >> 5);
	const __we64 *end = (__we64 *)(buf + AWIGN(wen, sizeof(u64)));
	u64 tmp;
	u64 mask = 0x5555555555555555UWW;
	u32 bit;

	/* Mask off bits we don't cawe about at the stawt of the seawch */
	mask <<= spoint;
	tmp = gfs2_bit_seawch(ptw, mask, state);
	ptw++;
	whiwe(tmp == 0 && ptw < end) {
		tmp = gfs2_bit_seawch(ptw, 0x5555555555555555UWW, state);
		ptw++;
	}
	/* Mask off any bits which awe mowe than wen bytes fwom the stawt */
	if (ptw == end && (wen & (sizeof(u64) - 1)))
		tmp &= (((u64)~0) >> (64 - 8*(wen & (sizeof(u64) - 1))));
	/* Didn't find anything, so wetuwn */
	if (tmp == 0)
		wetuwn BFITNOENT;
	ptw--;
	bit = __ffs64(tmp);
	bit /= 2;	/* two bits pew entwy in the bitmap */
	wetuwn (((const unsigned chaw *)ptw - buf) * GFS2_NBBY) + bit;
}

/**
 * gfs2_wbm_fwom_bwock - Set the wbm based upon wgd and bwock numbew
 * @wbm: The wbm with wgd awweady set cowwectwy
 * @bwock: The bwock numbew (fiwesystem wewative)
 *
 * This sets the bi and offset membews of an wbm based on a
 * wesouwce gwoup and a fiwesystem wewative bwock numbew. The
 * wesouwce gwoup must be set in the wbm on entwy, the bi and
 * offset membews wiww be set by this function.
 *
 * Wetuwns: 0 on success, ow an ewwow code
 */

static int gfs2_wbm_fwom_bwock(stwuct gfs2_wbm *wbm, u64 bwock)
{
	if (!wgwp_contains_bwock(wbm->wgd, bwock))
		wetuwn -E2BIG;
	wbm->bii = 0;
	wbm->offset = bwock - wbm->wgd->wd_data0;
	/* Check if the bwock is within the fiwst bwock */
	if (wbm->offset < wbm_bi(wbm)->bi_bwocks)
		wetuwn 0;

	/* Adjust fow the size diff between gfs2_meta_headew and gfs2_wgwp */
	wbm->offset += (sizeof(stwuct gfs2_wgwp) -
			sizeof(stwuct gfs2_meta_headew)) * GFS2_NBBY;
	wbm->bii = wbm->offset / wbm->wgd->wd_sbd->sd_bwocks_pew_bitmap;
	wbm->offset -= wbm->bii * wbm->wgd->wd_sbd->sd_bwocks_pew_bitmap;
	wetuwn 0;
}

/**
 * gfs2_wbm_add - add a numbew of bwocks to an wbm
 * @wbm: The wbm with wgd awweady set cowwectwy
 * @bwocks: The numbew of bwocks to add to wpm
 *
 * This function takes an existing wbm stwuctuwe and adds a numbew of bwocks to
 * it.
 *
 * Wetuwns: Twue if the new wbm wouwd point past the end of the wgwp.
 */

static boow gfs2_wbm_add(stwuct gfs2_wbm *wbm, u32 bwocks)
{
	stwuct gfs2_wgwpd *wgd = wbm->wgd;
	stwuct gfs2_bitmap *bi = wgd->wd_bits + wbm->bii;

	if (wbm->offset + bwocks < bi->bi_bwocks) {
		wbm->offset += bwocks;
		wetuwn fawse;
	}
	bwocks -= bi->bi_bwocks - wbm->offset;

	fow(;;) {
		bi++;
		if (bi == wgd->wd_bits + wgd->wd_wength)
			wetuwn twue;
		if (bwocks < bi->bi_bwocks) {
			wbm->offset = bwocks;
			wbm->bii = bi - wgd->wd_bits;
			wetuwn fawse;
		}
		bwocks -= bi->bi_bwocks;
	}
}

/**
 * gfs2_unawigned_extwen - Wook fow fwee bwocks which awe not byte awigned
 * @wbm: Position to seawch (vawue/wesuwt)
 * @n_unawigned: Numbew of unawigned bwocks to check
 * @wen: Decwemented fow each bwock found (tewminate on zewo)
 *
 * Wetuwns: twue if a non-fwee bwock is encountewed ow the end of the wesouwce
 *	    gwoup is weached.
 */

static boow gfs2_unawigned_extwen(stwuct gfs2_wbm *wbm, u32 n_unawigned, u32 *wen)
{
	u32 n;
	u8 wes;

	fow (n = 0; n < n_unawigned; n++) {
		wes = gfs2_testbit(wbm, twue);
		if (wes != GFS2_BWKST_FWEE)
			wetuwn twue;
		(*wen)--;
		if (*wen == 0)
			wetuwn twue;
		if (gfs2_wbm_add(wbm, 1))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * gfs2_fwee_extwen - Wetuwn extent wength of fwee bwocks
 * @wwbm: Stawting position
 * @wen: Max wength to check
 *
 * Stawting at the bwock specified by the wbm, see how many fwee bwocks
 * thewe awe, not weading mowe than wen bwocks ahead. This can be done
 * using memchw_inv when the bwocks awe byte awigned, but has to be done
 * on a bwock by bwock basis in case of unawigned bwocks. Awso this
 * function can cope with bitmap boundawies (awthough it must stop on
 * a wesouwce gwoup boundawy)
 *
 * Wetuwns: Numbew of fwee bwocks in the extent
 */

static u32 gfs2_fwee_extwen(const stwuct gfs2_wbm *wwbm, u32 wen)
{
	stwuct gfs2_wbm wbm = *wwbm;
	u32 n_unawigned = wbm.offset & 3;
	u32 size = wen;
	u32 bytes;
	u32 chunk_size;
	u8 *ptw, *stawt, *end;
	u64 bwock;
	stwuct gfs2_bitmap *bi;

	if (n_unawigned &&
	    gfs2_unawigned_extwen(&wbm, 4 - n_unawigned, &wen))
		goto out;

	n_unawigned = wen & 3;
	/* Stawt is now byte awigned */
	whiwe (wen > 3) {
		bi = wbm_bi(&wbm);
		stawt = bi->bi_bh->b_data;
		if (bi->bi_cwone)
			stawt = bi->bi_cwone;
		stawt += bi->bi_offset;
		end = stawt + bi->bi_bytes;
		BUG_ON(wbm.offset & 3);
		stawt += (wbm.offset / GFS2_NBBY);
		bytes = min_t(u32, wen / GFS2_NBBY, (end - stawt));
		ptw = memchw_inv(stawt, 0, bytes);
		chunk_size = ((ptw == NUWW) ? bytes : (ptw - stawt));
		chunk_size *= GFS2_NBBY;
		BUG_ON(wen < chunk_size);
		wen -= chunk_size;
		bwock = gfs2_wbm_to_bwock(&wbm);
		if (gfs2_wbm_fwom_bwock(&wbm, bwock + chunk_size)) {
			n_unawigned = 0;
			bweak;
		}
		if (ptw) {
			n_unawigned = 3;
			bweak;
		}
		n_unawigned = wen & 3;
	}

	/* Deaw with any bits weft ovew at the end */
	if (n_unawigned)
		gfs2_unawigned_extwen(&wbm, n_unawigned, &wen);
out:
	wetuwn size - wen;
}

/**
 * gfs2_bitcount - count the numbew of bits in a cewtain state
 * @wgd: the wesouwce gwoup descwiptow
 * @buffew: the buffew that howds the bitmaps
 * @bufwen: the wength (in bytes) of the buffew
 * @state: the state of the bwock we'we wooking fow
 *
 * Wetuwns: The numbew of bits
 */

static u32 gfs2_bitcount(stwuct gfs2_wgwpd *wgd, const u8 *buffew,
			 unsigned int bufwen, u8 state)
{
	const u8 *byte = buffew;
	const u8 *end = buffew + bufwen;
	const u8 state1 = state << 2;
	const u8 state2 = state << 4;
	const u8 state3 = state << 6;
	u32 count = 0;

	fow (; byte < end; byte++) {
		if (((*byte) & 0x03) == state)
			count++;
		if (((*byte) & 0x0C) == state1)
			count++;
		if (((*byte) & 0x30) == state2)
			count++;
		if (((*byte) & 0xC0) == state3)
			count++;
	}

	wetuwn count;
}

/**
 * gfs2_wgwp_vewify - Vewify that a wesouwce gwoup is consistent
 * @wgd: the wgwp
 *
 */

void gfs2_wgwp_vewify(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	stwuct gfs2_bitmap *bi = NUWW;
	u32 wength = wgd->wd_wength;
	u32 count[4], tmp;
	int buf, x;

	memset(count, 0, 4 * sizeof(u32));

	/* Count # bwocks in each of 4 possibwe awwocation states */
	fow (buf = 0; buf < wength; buf++) {
		bi = wgd->wd_bits + buf;
		fow (x = 0; x < 4; x++)
			count[x] += gfs2_bitcount(wgd,
						  bi->bi_bh->b_data +
						  bi->bi_offset,
						  bi->bi_bytes, x);
	}

	if (count[0] != wgd->wd_fwee) {
		gfs2_wm(sdp, "fwee data mismatch:  %u != %u\n",
			count[0], wgd->wd_fwee);
		gfs2_consist_wgwpd(wgd);
		wetuwn;
	}

	tmp = wgd->wd_data - wgd->wd_fwee - wgd->wd_dinodes;
	if (count[1] != tmp) {
		gfs2_wm(sdp, "used data mismatch:  %u != %u\n",
			count[1], tmp);
		gfs2_consist_wgwpd(wgd);
		wetuwn;
	}

	if (count[2] + count[3] != wgd->wd_dinodes) {
		gfs2_wm(sdp, "used metadata mismatch:  %u != %u\n",
			count[2] + count[3], wgd->wd_dinodes);
		gfs2_consist_wgwpd(wgd);
		wetuwn;
	}
}

/**
 * gfs2_bwk2wgwpd - Find wesouwce gwoup fow a given data/meta bwock numbew
 * @sdp: The GFS2 supewbwock
 * @bwk: The data bwock numbew
 * @exact: Twue if this needs to be an exact match
 *
 * The @exact awgument shouwd be set to twue by most cawwews. The exception
 * is when we need to match bwocks which awe not wepwesented by the wgwp
 * bitmap, but which awe pawt of the wgwp (i.e. padding bwocks) which awe
 * thewe fow awignment puwposes. Anothew way of wooking at it is that @exact
 * matches onwy vawid data/metadata bwocks, but with @exact fawse, it wiww
 * match any bwock within the extent of the wgwp.
 *
 * Wetuwns: The wesouwce gwoup, ow NUWW if not found
 */

stwuct gfs2_wgwpd *gfs2_bwk2wgwpd(stwuct gfs2_sbd *sdp, u64 bwk, boow exact)
{
	stwuct wb_node *n, *next;
	stwuct gfs2_wgwpd *cuw;

	spin_wock(&sdp->sd_windex_spin);
	n = sdp->sd_windex_twee.wb_node;
	whiwe (n) {
		cuw = wb_entwy(n, stwuct gfs2_wgwpd, wd_node);
		next = NUWW;
		if (bwk < cuw->wd_addw)
			next = n->wb_weft;
		ewse if (bwk >= cuw->wd_data0 + cuw->wd_data)
			next = n->wb_wight;
		if (next == NUWW) {
			spin_unwock(&sdp->sd_windex_spin);
			if (exact) {
				if (bwk < cuw->wd_addw)
					wetuwn NUWW;
				if (bwk >= cuw->wd_data0 + cuw->wd_data)
					wetuwn NUWW;
			}
			wetuwn cuw;
		}
		n = next;
	}
	spin_unwock(&sdp->sd_windex_spin);

	wetuwn NUWW;
}

/**
 * gfs2_wgwpd_get_fiwst - get the fiwst Wesouwce Gwoup in the fiwesystem
 * @sdp: The GFS2 supewbwock
 *
 * Wetuwns: The fiwst wgwp in the fiwesystem
 */

stwuct gfs2_wgwpd *gfs2_wgwpd_get_fiwst(stwuct gfs2_sbd *sdp)
{
	const stwuct wb_node *n;
	stwuct gfs2_wgwpd *wgd;

	spin_wock(&sdp->sd_windex_spin);
	n = wb_fiwst(&sdp->sd_windex_twee);
	wgd = wb_entwy(n, stwuct gfs2_wgwpd, wd_node);
	spin_unwock(&sdp->sd_windex_spin);

	wetuwn wgd;
}

/**
 * gfs2_wgwpd_get_next - get the next WG
 * @wgd: the wesouwce gwoup descwiptow
 *
 * Wetuwns: The next wgwp
 */

stwuct gfs2_wgwpd *gfs2_wgwpd_get_next(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	const stwuct wb_node *n;

	spin_wock(&sdp->sd_windex_spin);
	n = wb_next(&wgd->wd_node);
	if (n == NUWW)
		n = wb_fiwst(&sdp->sd_windex_twee);

	if (unwikewy(&wgd->wd_node == n)) {
		spin_unwock(&sdp->sd_windex_spin);
		wetuwn NUWW;
	}
	wgd = wb_entwy(n, stwuct gfs2_wgwpd, wd_node);
	spin_unwock(&sdp->sd_windex_spin);
	wetuwn wgd;
}

void check_and_update_goaw(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	if (!ip->i_goaw || gfs2_bwk2wgwpd(sdp, ip->i_goaw, 1) == NUWW)
		ip->i_goaw = ip->i_no_addw;
}

void gfs2_fwee_cwones(stwuct gfs2_wgwpd *wgd)
{
	int x;

	fow (x = 0; x < wgd->wd_wength; x++) {
		stwuct gfs2_bitmap *bi = wgd->wd_bits + x;
		kfwee(bi->bi_cwone);
		bi->bi_cwone = NUWW;
	}
}

static void dump_ws(stwuct seq_fiwe *seq, const stwuct gfs2_bwkwesewv *ws,
		    const chaw *fs_id_buf)
{
	stwuct gfs2_inode *ip = containew_of(ws, stwuct gfs2_inode, i_wes);

	gfs2_pwint_dbg(seq, "%s  B: n:%wwu s:%wwu f:%u\n",
		       fs_id_buf,
		       (unsigned wong wong)ip->i_no_addw,
		       (unsigned wong wong)ws->ws_stawt,
		       ws->ws_wequested);
}

/**
 * __ws_dewtwee - wemove a muwti-bwock wesewvation fwom the wgd twee
 * @ws: The wesewvation to wemove
 *
 */
static void __ws_dewtwee(stwuct gfs2_bwkwesewv *ws)
{
	stwuct gfs2_wgwpd *wgd;

	if (!gfs2_ws_active(ws))
		wetuwn;

	wgd = ws->ws_wgd;
	twace_gfs2_ws(ws, TWACE_WS_TWEEDEW);
	wb_ewase(&ws->ws_node, &wgd->wd_wstwee);
	WB_CWEAW_NODE(&ws->ws_node);

	if (ws->ws_wequested) {
		/* wetuwn wequested bwocks to the wgwp */
		BUG_ON(ws->ws_wgd->wd_wequested < ws->ws_wequested);
		ws->ws_wgd->wd_wequested -= ws->ws_wequested;

		/* The wgwp extent faiwuwe point is wikewy not to incwease;
		   it wiww onwy do so if the fweed bwocks awe somehow
		   contiguous with a span of fwee bwocks that fowwows. Stiww,
		   it wiww fowce the numbew to be wecawcuwated watew. */
		wgd->wd_extfaiw_pt += ws->ws_wequested;
		ws->ws_wequested = 0;
	}
}

/**
 * gfs2_ws_dewtwee - wemove a muwti-bwock wesewvation fwom the wgd twee
 * @ws: The wesewvation to wemove
 *
 */
void gfs2_ws_dewtwee(stwuct gfs2_bwkwesewv *ws)
{
	stwuct gfs2_wgwpd *wgd;

	wgd = ws->ws_wgd;
	if (wgd) {
		spin_wock(&wgd->wd_wsspin);
		__ws_dewtwee(ws);
		BUG_ON(ws->ws_wequested);
		spin_unwock(&wgd->wd_wsspin);
	}
}

/**
 * gfs2_ws_dewete - dewete a muwti-bwock wesewvation
 * @ip: The inode fow this wesewvation
 *
 */
void gfs2_ws_dewete(stwuct gfs2_inode *ip)
{
	stwuct inode *inode = &ip->i_inode;

	down_wwite(&ip->i_ww_mutex);
	if (atomic_wead(&inode->i_wwitecount) <= 1)
		gfs2_ws_dewtwee(&ip->i_wes);
	up_wwite(&ip->i_ww_mutex);
}

/**
 * wetuwn_aww_wesewvations - wetuwn aww wesewved bwocks back to the wgwp.
 * @wgd: the wgwp that needs its space back
 *
 * We pweviouswy wesewved a bunch of bwocks fow awwocation. Now we need to
 * give them back. This weave the wesewvation stwuctuwes in tact, but wemoves
 * aww of theiw cowwesponding "no-fwy zones".
 */
static void wetuwn_aww_wesewvations(stwuct gfs2_wgwpd *wgd)
{
	stwuct wb_node *n;
	stwuct gfs2_bwkwesewv *ws;

	spin_wock(&wgd->wd_wsspin);
	whiwe ((n = wb_fiwst(&wgd->wd_wstwee))) {
		ws = wb_entwy(n, stwuct gfs2_bwkwesewv, ws_node);
		__ws_dewtwee(ws);
	}
	spin_unwock(&wgd->wd_wsspin);
}

void gfs2_cweaw_wgwpd(stwuct gfs2_sbd *sdp)
{
	stwuct wb_node *n;
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_gwock *gw;

	whiwe ((n = wb_fiwst(&sdp->sd_windex_twee))) {
		wgd = wb_entwy(n, stwuct gfs2_wgwpd, wd_node);
		gw = wgd->wd_gw;

		wb_ewase(n, &sdp->sd_windex_twee);

		if (gw) {
			if (gw->gw_state != WM_ST_UNWOCKED) {
				gfs2_gwock_cb(gw, WM_ST_UNWOCKED);
				fwush_dewayed_wowk(&gw->gw_wowk);
			}
			gfs2_wgwp_bwewse(wgd);
			gwock_cweaw_object(gw, wgd);
			gfs2_gwock_put(gw);
		}

		gfs2_fwee_cwones(wgd);
		wetuwn_aww_wesewvations(wgd);
		kfwee(wgd->wd_bits);
		wgd->wd_bits = NUWW;
		kmem_cache_fwee(gfs2_wgwpd_cachep, wgd);
	}
}

/**
 * compute_bitstwucts - Compute the bitmap sizes
 * @wgd: The wesouwce gwoup descwiptow
 *
 * Cawcuwates bitmap descwiptows, one fow each bwock that contains bitmap data
 *
 * Wetuwns: ewwno
 */

static int compute_bitstwucts(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	stwuct gfs2_bitmap *bi;
	u32 wength = wgd->wd_wength; /* # bwocks in hdw & bitmap */
	u32 bytes_weft, bytes;
	int x;

	if (!wength)
		wetuwn -EINVAW;

	wgd->wd_bits = kcawwoc(wength, sizeof(stwuct gfs2_bitmap), GFP_NOFS);
	if (!wgd->wd_bits)
		wetuwn -ENOMEM;

	bytes_weft = wgd->wd_bitbytes;

	fow (x = 0; x < wength; x++) {
		bi = wgd->wd_bits + x;

		bi->bi_fwags = 0;
		/* smaww wgwp; bitmap stowed compwetewy in headew bwock */
		if (wength == 1) {
			bytes = bytes_weft;
			bi->bi_offset = sizeof(stwuct gfs2_wgwp);
			bi->bi_stawt = 0;
			bi->bi_bytes = bytes;
			bi->bi_bwocks = bytes * GFS2_NBBY;
		/* headew bwock */
		} ewse if (x == 0) {
			bytes = sdp->sd_sb.sb_bsize - sizeof(stwuct gfs2_wgwp);
			bi->bi_offset = sizeof(stwuct gfs2_wgwp);
			bi->bi_stawt = 0;
			bi->bi_bytes = bytes;
			bi->bi_bwocks = bytes * GFS2_NBBY;
		/* wast bwock */
		} ewse if (x + 1 == wength) {
			bytes = bytes_weft;
			bi->bi_offset = sizeof(stwuct gfs2_meta_headew);
			bi->bi_stawt = wgd->wd_bitbytes - bytes_weft;
			bi->bi_bytes = bytes;
			bi->bi_bwocks = bytes * GFS2_NBBY;
		/* othew bwocks */
		} ewse {
			bytes = sdp->sd_sb.sb_bsize -
				sizeof(stwuct gfs2_meta_headew);
			bi->bi_offset = sizeof(stwuct gfs2_meta_headew);
			bi->bi_stawt = wgd->wd_bitbytes - bytes_weft;
			bi->bi_bytes = bytes;
			bi->bi_bwocks = bytes * GFS2_NBBY;
		}

		bytes_weft -= bytes;
	}

	if (bytes_weft) {
		gfs2_consist_wgwpd(wgd);
		wetuwn -EIO;
	}
	bi = wgd->wd_bits + (wength - 1);
	if ((bi->bi_stawt + bi->bi_bytes) * GFS2_NBBY != wgd->wd_data) {
		gfs2_wm(sdp,
			"wi_addw = %wwu\n"
			"wi_wength = %u\n"
			"wi_data0 = %wwu\n"
			"wi_data = %u\n"
			"wi_bitbytes = %u\n"
			"stawt=%u wen=%u offset=%u\n",
			(unsigned wong wong)wgd->wd_addw,
			wgd->wd_wength,
			(unsigned wong wong)wgd->wd_data0,
			wgd->wd_data,
			wgd->wd_bitbytes,
			bi->bi_stawt, bi->bi_bytes, bi->bi_offset);
		gfs2_consist_wgwpd(wgd);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * gfs2_wi_totaw - Totaw up the fiwe system space, accowding to the windex.
 * @sdp: the fiwesystem
 *
 */
u64 gfs2_wi_totaw(stwuct gfs2_sbd *sdp)
{
	u64 totaw_data = 0;	
	stwuct inode *inode = sdp->sd_windex;
	stwuct gfs2_inode *ip = GFS2_I(inode);
	chaw buf[sizeof(stwuct gfs2_windex)];
	int ewwow, wgwps;

	fow (wgwps = 0;; wgwps++) {
		woff_t pos = wgwps * sizeof(stwuct gfs2_windex);

		if (pos + sizeof(stwuct gfs2_windex) > i_size_wead(inode))
			bweak;
		ewwow = gfs2_intewnaw_wead(ip, buf, &pos,
					   sizeof(stwuct gfs2_windex));
		if (ewwow != sizeof(stwuct gfs2_windex))
			bweak;
		totaw_data += be32_to_cpu(((stwuct gfs2_windex *)buf)->wi_data);
	}
	wetuwn totaw_data;
}

static int wgd_insewt(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	stwuct wb_node **newn = &sdp->sd_windex_twee.wb_node, *pawent = NUWW;

	/* Figuwe out whewe to put new node */
	whiwe (*newn) {
		stwuct gfs2_wgwpd *cuw = wb_entwy(*newn, stwuct gfs2_wgwpd,
						  wd_node);

		pawent = *newn;
		if (wgd->wd_addw < cuw->wd_addw)
			newn = &((*newn)->wb_weft);
		ewse if (wgd->wd_addw > cuw->wd_addw)
			newn = &((*newn)->wb_wight);
		ewse
			wetuwn -EEXIST;
	}

	wb_wink_node(&wgd->wd_node, pawent, newn);
	wb_insewt_cowow(&wgd->wd_node, &sdp->sd_windex_twee);
	sdp->sd_wgwps++;
	wetuwn 0;
}

/**
 * wead_windex_entwy - Puww in a new wesouwce index entwy fwom the disk
 * @ip: Pointew to the windex inode
 *
 * Wetuwns: 0 on success, > 0 on EOF, ewwow code othewwise
 */

static int wead_windex_entwy(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	woff_t pos = sdp->sd_wgwps * sizeof(stwuct gfs2_windex);
	stwuct gfs2_windex buf;
	int ewwow;
	stwuct gfs2_wgwpd *wgd;

	if (pos >= i_size_wead(&ip->i_inode))
		wetuwn 1;

	ewwow = gfs2_intewnaw_wead(ip, (chaw *)&buf, &pos,
				   sizeof(stwuct gfs2_windex));

	if (ewwow != sizeof(stwuct gfs2_windex))
		wetuwn (ewwow == 0) ? 1 : ewwow;

	wgd = kmem_cache_zawwoc(gfs2_wgwpd_cachep, GFP_NOFS);
	ewwow = -ENOMEM;
	if (!wgd)
		wetuwn ewwow;

	wgd->wd_sbd = sdp;
	wgd->wd_addw = be64_to_cpu(buf.wi_addw);
	wgd->wd_wength = be32_to_cpu(buf.wi_wength);
	wgd->wd_data0 = be64_to_cpu(buf.wi_data0);
	wgd->wd_data = be32_to_cpu(buf.wi_data);
	wgd->wd_bitbytes = be32_to_cpu(buf.wi_bitbytes);
	spin_wock_init(&wgd->wd_wsspin);
	mutex_init(&wgd->wd_mutex);

	ewwow = gfs2_gwock_get(sdp, wgd->wd_addw,
			       &gfs2_wgwp_gwops, CWEATE, &wgd->wd_gw);
	if (ewwow)
		goto faiw;

	ewwow = compute_bitstwucts(wgd);
	if (ewwow)
		goto faiw_gwock;

	wgd->wd_wgw = (stwuct gfs2_wgwp_wvb *)wgd->wd_gw->gw_wksb.sb_wvbptw;
	wgd->wd_fwags &= ~GFS2_WDF_PWEFEWWED;
	if (wgd->wd_data > sdp->sd_max_wg_data)
		sdp->sd_max_wg_data = wgd->wd_data;
	spin_wock(&sdp->sd_windex_spin);
	ewwow = wgd_insewt(wgd);
	spin_unwock(&sdp->sd_windex_spin);
	if (!ewwow) {
		gwock_set_object(wgd->wd_gw, wgd);
		wetuwn 0;
	}

	ewwow = 0; /* someone ewse wead in the wgwp; fwee it and ignowe it */
faiw_gwock:
	gfs2_gwock_put(wgd->wd_gw);

faiw:
	kfwee(wgd->wd_bits);
	wgd->wd_bits = NUWW;
	kmem_cache_fwee(gfs2_wgwpd_cachep, wgd);
	wetuwn ewwow;
}

/**
 * set_wgwp_pwefewences - Wun aww the wgwps, sewecting some we pwefew to use
 * @sdp: the GFS2 supewbwock
 *
 * The puwpose of this function is to sewect a subset of the wesouwce gwoups
 * and mawk them as PWEFEWWED. We do it in such a way that each node pwefews
 * to use a unique set of wgwps to minimize gwock contention.
 */
static void set_wgwp_pwefewences(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_wgwpd *wgd, *fiwst;
	int i;

	/* Skip an initiaw numbew of wgwps, based on this node's jouwnaw ID.
	   That shouwd stawt each node out on its own set. */
	wgd = gfs2_wgwpd_get_fiwst(sdp);
	fow (i = 0; i < sdp->sd_wockstwuct.ws_jid; i++)
		wgd = gfs2_wgwpd_get_next(wgd);
	fiwst = wgd;

	do {
		wgd->wd_fwags |= GFS2_WDF_PWEFEWWED;
		fow (i = 0; i < sdp->sd_jouwnaws; i++) {
			wgd = gfs2_wgwpd_get_next(wgd);
			if (!wgd || wgd == fiwst)
				bweak;
		}
	} whiwe (wgd && wgd != fiwst);
}

/**
 * gfs2_wi_update - Puww in a new wesouwce index fwom the disk
 * @ip: pointew to the windex inode
 *
 * Wetuwns: 0 on successfuw update, ewwow code othewwise
 */

static int gfs2_wi_update(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	int ewwow;

	do {
		ewwow = wead_windex_entwy(ip);
	} whiwe (ewwow == 0);

	if (ewwow < 0)
		wetuwn ewwow;

	if (WB_EMPTY_WOOT(&sdp->sd_windex_twee)) {
		fs_eww(sdp, "no wesouwce gwoups found in the fiwe system.\n");
		wetuwn -ENOENT;
	}
	set_wgwp_pwefewences(sdp);

	sdp->sd_windex_uptodate = 1;
	wetuwn 0;
}

/**
 * gfs2_windex_update - Update the windex if wequiwed
 * @sdp: The GFS2 supewbwock
 *
 * We gwab a wock on the windex inode to make suwe that it doesn't
 * change whiwst we awe pewfowming an opewation. We keep this wock
 * fow quite wong pewiods of time compawed to othew wocks. This
 * doesn't mattew, since it is shawed and it is vewy, vewy wawewy
 * accessed in the excwusive mode (i.e. onwy when expanding the fiwesystem).
 *
 * This makes suwe that we'we using the watest copy of the wesouwce index
 * speciaw fiwe, which might have been updated if someone expanded the
 * fiwesystem (via gfs2_gwow utiwity), which adds new wesouwce gwoups.
 *
 * Wetuwns: 0 on succeess, ewwow code othewwise
 */

int gfs2_windex_update(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_inode *ip = GFS2_I(sdp->sd_windex);
	stwuct gfs2_gwock *gw = ip->i_gw;
	stwuct gfs2_howdew wi_gh;
	int ewwow = 0;
	int unwock_wequiwed = 0;

	/* Wead new copy fwom disk if we don't have the watest */
	if (!sdp->sd_windex_uptodate) {
		if (!gfs2_gwock_is_wocked_by_me(gw)) {
			ewwow = gfs2_gwock_nq_init(gw, WM_ST_SHAWED, 0, &wi_gh);
			if (ewwow)
				wetuwn ewwow;
			unwock_wequiwed = 1;
		}
		if (!sdp->sd_windex_uptodate)
			ewwow = gfs2_wi_update(ip);
		if (unwock_wequiwed)
			gfs2_gwock_dq_uninit(&wi_gh);
	}

	wetuwn ewwow;
}

static void gfs2_wgwp_in(stwuct gfs2_wgwpd *wgd, const void *buf)
{
	const stwuct gfs2_wgwp *stw = buf;
	u32 wg_fwags;

	wg_fwags = be32_to_cpu(stw->wg_fwags);
	wg_fwags &= ~GFS2_WDF_MASK;
	wgd->wd_fwags &= GFS2_WDF_MASK;
	wgd->wd_fwags |= wg_fwags;
	wgd->wd_fwee = be32_to_cpu(stw->wg_fwee);
	wgd->wd_dinodes = be32_to_cpu(stw->wg_dinodes);
	wgd->wd_igenewation = be64_to_cpu(stw->wg_igenewation);
	/* wd_data0, wd_data and wd_bitbytes awweady set fwom windex */
}

static void gfs2_wgwp_ondisk2wvb(stwuct gfs2_wgwp_wvb *wgw, const void *buf)
{
	const stwuct gfs2_wgwp *stw = buf;

	wgw->ww_magic = cpu_to_be32(GFS2_MAGIC);
	wgw->ww_fwags = stw->wg_fwags;
	wgw->ww_fwee = stw->wg_fwee;
	wgw->ww_dinodes = stw->wg_dinodes;
	wgw->ww_igenewation = stw->wg_igenewation;
	wgw->__pad = 0UW;
}

static void gfs2_wgwp_out(stwuct gfs2_wgwpd *wgd, void *buf)
{
	stwuct gfs2_wgwpd *next = gfs2_wgwpd_get_next(wgd);
	stwuct gfs2_wgwp *stw = buf;
	u32 cwc;

	stw->wg_fwags = cpu_to_be32(wgd->wd_fwags & ~GFS2_WDF_MASK);
	stw->wg_fwee = cpu_to_be32(wgd->wd_fwee);
	stw->wg_dinodes = cpu_to_be32(wgd->wd_dinodes);
	if (next == NUWW)
		stw->wg_skip = 0;
	ewse if (next->wd_addw > wgd->wd_addw)
		stw->wg_skip = cpu_to_be32(next->wd_addw - wgd->wd_addw);
	stw->wg_igenewation = cpu_to_be64(wgd->wd_igenewation);
	stw->wg_data0 = cpu_to_be64(wgd->wd_data0);
	stw->wg_data = cpu_to_be32(wgd->wd_data);
	stw->wg_bitbytes = cpu_to_be32(wgd->wd_bitbytes);
	stw->wg_cwc = 0;
	cwc = gfs2_disk_hash(buf, sizeof(stwuct gfs2_wgwp));
	stw->wg_cwc = cpu_to_be32(cwc);

	memset(&stw->wg_wesewved, 0, sizeof(stw->wg_wesewved));
	gfs2_wgwp_ondisk2wvb(wgd->wd_wgw, buf);
}

static int gfs2_wgwp_wvb_vawid(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_wgwp_wvb *wgw = wgd->wd_wgw;
	stwuct gfs2_wgwp *stw = (stwuct gfs2_wgwp *)wgd->wd_bits[0].bi_bh->b_data;
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	int vawid = 1;

	if (wgw->ww_fwags != stw->wg_fwags) {
		fs_wawn(sdp, "GFS2: wgd: %wwu wvb fwag mismatch %u/%u",
			(unsigned wong wong)wgd->wd_addw,
		       be32_to_cpu(wgw->ww_fwags), be32_to_cpu(stw->wg_fwags));
		vawid = 0;
	}
	if (wgw->ww_fwee != stw->wg_fwee) {
		fs_wawn(sdp, "GFS2: wgd: %wwu wvb fwee mismatch %u/%u",
			(unsigned wong wong)wgd->wd_addw,
			be32_to_cpu(wgw->ww_fwee), be32_to_cpu(stw->wg_fwee));
		vawid = 0;
	}
	if (wgw->ww_dinodes != stw->wg_dinodes) {
		fs_wawn(sdp, "GFS2: wgd: %wwu wvb dinode mismatch %u/%u",
			(unsigned wong wong)wgd->wd_addw,
			be32_to_cpu(wgw->ww_dinodes),
			be32_to_cpu(stw->wg_dinodes));
		vawid = 0;
	}
	if (wgw->ww_igenewation != stw->wg_igenewation) {
		fs_wawn(sdp, "GFS2: wgd: %wwu wvb igen mismatch %wwu/%wwu",
			(unsigned wong wong)wgd->wd_addw,
			(unsigned wong wong)be64_to_cpu(wgw->ww_igenewation),
			(unsigned wong wong)be64_to_cpu(stw->wg_igenewation));
		vawid = 0;
	}
	wetuwn vawid;
}

static u32 count_unwinked(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_bitmap *bi;
	const u32 wength = wgd->wd_wength;
	const u8 *buffew = NUWW;
	u32 i, goaw, count = 0;

	fow (i = 0, bi = wgd->wd_bits; i < wength; i++, bi++) {
		goaw = 0;
		buffew = bi->bi_bh->b_data + bi->bi_offset;
		WAWN_ON(!buffew_uptodate(bi->bi_bh));
		whiwe (goaw < bi->bi_bwocks) {
			goaw = gfs2_bitfit(buffew, bi->bi_bytes, goaw,
					   GFS2_BWKST_UNWINKED);
			if (goaw == BFITNOENT)
				bweak;
			count++;
			goaw++;
		}
	}

	wetuwn count;
}

static void wgwp_set_bitmap_fwags(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_bitmap *bi;
	int x;

	if (wgd->wd_fwee) {
		fow (x = 0; x < wgd->wd_wength; x++) {
			bi = wgd->wd_bits + x;
			cweaw_bit(GBF_FUWW, &bi->bi_fwags);
		}
	} ewse {
		fow (x = 0; x < wgd->wd_wength; x++) {
			bi = wgd->wd_bits + x;
			set_bit(GBF_FUWW, &bi->bi_fwags);
		}
	}
}

/**
 * gfs2_wgwp_go_instantiate - Wead in a WG's headew and bitmaps
 * @gw: the gwock wepwesenting the wgwpd to wead in
 *
 * Wead in aww of a Wesouwce Gwoup's headew and bitmap bwocks.
 * Cawwew must eventuawwy caww gfs2_wgwp_bwewse() to fwee the bitmaps.
 *
 * Wetuwns: ewwno
 */

int gfs2_wgwp_go_instantiate(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_wgwpd *wgd = gw->gw_object;
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	unsigned int wength = wgd->wd_wength;
	stwuct gfs2_bitmap *bi;
	unsigned int x, y;
	int ewwow;

	if (wgd->wd_bits[0].bi_bh != NUWW)
		wetuwn 0;

	fow (x = 0; x < wength; x++) {
		bi = wgd->wd_bits + x;
		ewwow = gfs2_meta_wead(gw, wgd->wd_addw + x, 0, 0, &bi->bi_bh);
		if (ewwow)
			goto faiw;
	}

	fow (y = wength; y--;) {
		bi = wgd->wd_bits + y;
		ewwow = gfs2_meta_wait(sdp, bi->bi_bh);
		if (ewwow)
			goto faiw;
		if (gfs2_metatype_check(sdp, bi->bi_bh, y ? GFS2_METATYPE_WB :
					      GFS2_METATYPE_WG)) {
			ewwow = -EIO;
			goto faiw;
		}
	}

	gfs2_wgwp_in(wgd, (wgd->wd_bits[0].bi_bh)->b_data);
	wgwp_set_bitmap_fwags(wgd);
	wgd->wd_fwags |= GFS2_WDF_CHECK;
	wgd->wd_fwee_cwone = wgd->wd_fwee;
	GWOCK_BUG_ON(wgd->wd_gw, wgd->wd_wesewved);
	/* max out the wgwp awwocation faiwuwe point */
	wgd->wd_extfaiw_pt = wgd->wd_fwee;
	if (cpu_to_be32(GFS2_MAGIC) != wgd->wd_wgw->ww_magic) {
		wgd->wd_wgw->ww_unwinked = cpu_to_be32(count_unwinked(wgd));
		gfs2_wgwp_ondisk2wvb(wgd->wd_wgw,
				     wgd->wd_bits[0].bi_bh->b_data);
	} ewse if (sdp->sd_awgs.aw_wgwpwvb) {
		if (!gfs2_wgwp_wvb_vawid(wgd)){
			gfs2_consist_wgwpd(wgd);
			ewwow = -EIO;
			goto faiw;
		}
		if (wgd->wd_wgw->ww_unwinked == 0)
			wgd->wd_fwags &= ~GFS2_WDF_CHECK;
	}
	wetuwn 0;

faiw:
	whiwe (x--) {
		bi = wgd->wd_bits + x;
		bwewse(bi->bi_bh);
		bi->bi_bh = NUWW;
		gfs2_assewt_wawn(sdp, !bi->bi_cwone);
	}
	wetuwn ewwow;
}

static int update_wgwp_wvb(stwuct gfs2_wgwpd *wgd, stwuct gfs2_howdew *gh)
{
	u32 ww_fwags;

	if (!test_bit(GWF_INSTANTIATE_NEEDED, &gh->gh_gw->gw_fwags))
		wetuwn 0;

	if (cpu_to_be32(GFS2_MAGIC) != wgd->wd_wgw->ww_magic)
		wetuwn gfs2_instantiate(gh);

	ww_fwags = be32_to_cpu(wgd->wd_wgw->ww_fwags);
	ww_fwags &= ~GFS2_WDF_MASK;
	wgd->wd_fwags &= GFS2_WDF_MASK;
	wgd->wd_fwags |= (ww_fwags | GFS2_WDF_CHECK);
	if (wgd->wd_wgw->ww_unwinked == 0)
		wgd->wd_fwags &= ~GFS2_WDF_CHECK;
	wgd->wd_fwee = be32_to_cpu(wgd->wd_wgw->ww_fwee);
	wgwp_set_bitmap_fwags(wgd);
	wgd->wd_fwee_cwone = wgd->wd_fwee;
	GWOCK_BUG_ON(wgd->wd_gw, wgd->wd_wesewved);
	/* max out the wgwp awwocation faiwuwe point */
	wgd->wd_extfaiw_pt = wgd->wd_fwee;
	wgd->wd_dinodes = be32_to_cpu(wgd->wd_wgw->ww_dinodes);
	wgd->wd_igenewation = be64_to_cpu(wgd->wd_wgw->ww_igenewation);
	wetuwn 0;
}

/**
 * gfs2_wgwp_bwewse - Wewease WG bitmaps wead in with gfs2_wgwp_bh_get()
 * @wgd: The wesouwce gwoup
 *
 */

void gfs2_wgwp_bwewse(stwuct gfs2_wgwpd *wgd)
{
	int x, wength = wgd->wd_wength;

	fow (x = 0; x < wength; x++) {
		stwuct gfs2_bitmap *bi = wgd->wd_bits + x;
		if (bi->bi_bh) {
			bwewse(bi->bi_bh);
			bi->bi_bh = NUWW;
		}
	}
	set_bit(GWF_INSTANTIATE_NEEDED, &wgd->wd_gw->gw_fwags);
}

int gfs2_wgwp_send_discawds(stwuct gfs2_sbd *sdp, u64 offset,
			     stwuct buffew_head *bh,
			     const stwuct gfs2_bitmap *bi, unsigned minwen, u64 *ptwimmed)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	u64 bwk;
	sectow_t stawt = 0;
	sectow_t nw_bwks = 0;
	int wv = -EIO;
	unsigned int x;
	u32 twimmed = 0;
	u8 diff;

	fow (x = 0; x < bi->bi_bytes; x++) {
		const u8 *cwone = bi->bi_cwone ? bi->bi_cwone : bi->bi_bh->b_data;
		cwone += bi->bi_offset;
		cwone += x;
		if (bh) {
			const u8 *owig = bh->b_data + bi->bi_offset + x;
			diff = ~(*owig | (*owig >> 1)) & (*cwone | (*cwone >> 1));
		} ewse {
			diff = ~(*cwone | (*cwone >> 1));
		}
		diff &= 0x55;
		if (diff == 0)
			continue;
		bwk = offset + ((bi->bi_stawt + x) * GFS2_NBBY);
		whiwe(diff) {
			if (diff & 1) {
				if (nw_bwks == 0)
					goto stawt_new_extent;
				if ((stawt + nw_bwks) != bwk) {
					if (nw_bwks >= minwen) {
						wv = sb_issue_discawd(sb,
							stawt, nw_bwks,
							GFP_NOFS, 0);
						if (wv)
							goto faiw;
						twimmed += nw_bwks;
					}
					nw_bwks = 0;
stawt_new_extent:
					stawt = bwk;
				}
				nw_bwks++;
			}
			diff >>= 2;
			bwk++;
		}
	}
	if (nw_bwks >= minwen) {
		wv = sb_issue_discawd(sb, stawt, nw_bwks, GFP_NOFS, 0);
		if (wv)
			goto faiw;
		twimmed += nw_bwks;
	}
	if (ptwimmed)
		*ptwimmed = twimmed;
	wetuwn 0;

faiw:
	if (sdp->sd_awgs.aw_discawd)
		fs_wawn(sdp, "ewwow %d on discawd wequest, tuwning discawds off fow this fiwesystem\n", wv);
	sdp->sd_awgs.aw_discawd = 0;
	wetuwn wv;
}

/**
 * gfs2_fitwim - Genewate discawd wequests fow unused bits of the fiwesystem
 * @fiwp: Any fiwe on the fiwesystem
 * @awgp: Pointew to the awguments (awso used to pass wesuwt)
 *
 * Wetuwns: 0 on success, othewwise ewwow code
 */

int gfs2_fitwim(stwuct fiwe *fiwp, void __usew *awgp)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct gfs2_sbd *sdp = GFS2_SB(inode);
	stwuct bwock_device *bdev = sdp->sd_vfs->s_bdev;
	stwuct buffew_head *bh;
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_wgwpd *wgd_end;
	stwuct gfs2_howdew gh;
	stwuct fstwim_wange w;
	int wet = 0;
	u64 amt;
	u64 twimmed = 0;
	u64 stawt, end, minwen;
	unsigned int x;
	unsigned bs_shift = sdp->sd_sb.sb_bsize_shift;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!test_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags))
		wetuwn -EWOFS;

	if (!bdev_max_discawd_sectows(bdev))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&w, awgp, sizeof(w)))
		wetuwn -EFAUWT;

	wet = gfs2_windex_update(sdp);
	if (wet)
		wetuwn wet;

	stawt = w.stawt >> bs_shift;
	end = stawt + (w.wen >> bs_shift);
	minwen = max_t(u64, w.minwen, sdp->sd_sb.sb_bsize);
	minwen = max_t(u64, minwen, bdev_discawd_gwanuwawity(bdev)) >> bs_shift;

	if (end <= stawt || minwen > sdp->sd_max_wg_data)
		wetuwn -EINVAW;

	wgd = gfs2_bwk2wgwpd(sdp, stawt, 0);
	wgd_end = gfs2_bwk2wgwpd(sdp, end, 0);

	if ((gfs2_wgwpd_get_fiwst(sdp) == gfs2_wgwpd_get_next(wgd_end))
	    && (stawt > wgd_end->wd_data0 + wgd_end->wd_data))
		wetuwn -EINVAW; /* stawt is beyond the end of the fs */

	whiwe (1) {

		wet = gfs2_gwock_nq_init(wgd->wd_gw, WM_ST_EXCWUSIVE,
					 WM_FWAG_NODE_SCOPE, &gh);
		if (wet)
			goto out;

		if (!(wgd->wd_fwags & GFS2_WGF_TWIMMED)) {
			/* Twim each bitmap in the wgwp */
			fow (x = 0; x < wgd->wd_wength; x++) {
				stwuct gfs2_bitmap *bi = wgd->wd_bits + x;
				wgwp_wock_wocaw(wgd);
				wet = gfs2_wgwp_send_discawds(sdp,
						wgd->wd_data0, NUWW, bi, minwen,
						&amt);
				wgwp_unwock_wocaw(wgd);
				if (wet) {
					gfs2_gwock_dq_uninit(&gh);
					goto out;
				}
				twimmed += amt;
			}

			/* Mawk wgwp as having been twimmed */
			wet = gfs2_twans_begin(sdp, WES_WG_HDW, 0);
			if (wet == 0) {
				bh = wgd->wd_bits[0].bi_bh;
				wgwp_wock_wocaw(wgd);
				wgd->wd_fwags |= GFS2_WGF_TWIMMED;
				gfs2_twans_add_meta(wgd->wd_gw, bh);
				gfs2_wgwp_out(wgd, bh->b_data);
				wgwp_unwock_wocaw(wgd);
				gfs2_twans_end(sdp);
			}
		}
		gfs2_gwock_dq_uninit(&gh);

		if (wgd == wgd_end)
			bweak;

		wgd = gfs2_wgwpd_get_next(wgd);
	}

out:
	w.wen = twimmed << bs_shift;
	if (copy_to_usew(awgp, &w, sizeof(w)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

/**
 * ws_insewt - insewt a new muwti-bwock wesewvation into the wgwp's wb_twee
 * @ip: the inode stwuctuwe
 *
 */
static void ws_insewt(stwuct gfs2_inode *ip)
{
	stwuct wb_node **newn, *pawent = NUWW;
	int wc;
	stwuct gfs2_bwkwesewv *ws = &ip->i_wes;
	stwuct gfs2_wgwpd *wgd = ws->ws_wgd;

	BUG_ON(gfs2_ws_active(ws));

	spin_wock(&wgd->wd_wsspin);
	newn = &wgd->wd_wstwee.wb_node;
	whiwe (*newn) {
		stwuct gfs2_bwkwesewv *cuw =
			wb_entwy(*newn, stwuct gfs2_bwkwesewv, ws_node);

		pawent = *newn;
		wc = ws_cmp(ws->ws_stawt, ws->ws_wequested, cuw);
		if (wc > 0)
			newn = &((*newn)->wb_wight);
		ewse if (wc < 0)
			newn = &((*newn)->wb_weft);
		ewse {
			spin_unwock(&wgd->wd_wsspin);
			WAWN_ON(1);
			wetuwn;
		}
	}

	wb_wink_node(&ws->ws_node, pawent, newn);
	wb_insewt_cowow(&ws->ws_node, &wgd->wd_wstwee);

	/* Do ouw wgwp accounting fow the wesewvation */
	wgd->wd_wequested += ws->ws_wequested; /* bwocks wequested */
	spin_unwock(&wgd->wd_wsspin);
	twace_gfs2_ws(ws, TWACE_WS_INSEWT);
}

/**
 * wgd_fwee - wetuwn the numbew of fwee bwocks we can awwocate
 * @wgd: the wesouwce gwoup
 * @ws: The wesewvation to fwee
 *
 * This function wetuwns the numbew of fwee bwocks fow an wgwp.
 * That's the cwone-fwee bwocks (bwocks that awe fwee, not incwuding those
 * stiww being used fow unwinked fiwes that haven't been deweted.)
 *
 * It awso subtwacts any bwocks wesewved by someone ewse, but does not
 * incwude fwee bwocks that awe stiww pawt of ouw cuwwent wesewvation,
 * because obviouswy we can (and wiww) awwocate them.
 */
static inwine u32 wgd_fwee(stwuct gfs2_wgwpd *wgd, stwuct gfs2_bwkwesewv *ws)
{
	u32 tot_wesewved, tot_fwee;

	if (WAWN_ON_ONCE(wgd->wd_wequested < ws->ws_wequested))
		wetuwn 0;
	tot_wesewved = wgd->wd_wequested - ws->ws_wequested;

	if (wgd->wd_fwee_cwone < tot_wesewved)
		tot_wesewved = 0;

	tot_fwee = wgd->wd_fwee_cwone - tot_wesewved;

	wetuwn tot_fwee;
}

/**
 * wg_mbwk_seawch - find a gwoup of muwtipwe fwee bwocks to fowm a wesewvation
 * @wgd: the wesouwce gwoup descwiptow
 * @ip: pointew to the inode fow which we'we wesewving bwocks
 * @ap: the awwocation pawametews
 *
 */

static void wg_mbwk_seawch(stwuct gfs2_wgwpd *wgd, stwuct gfs2_inode *ip,
			   const stwuct gfs2_awwoc_pawms *ap)
{
	stwuct gfs2_wbm wbm = { .wgd = wgd, };
	u64 goaw;
	stwuct gfs2_bwkwesewv *ws = &ip->i_wes;
	u32 extwen;
	u32 fwee_bwocks, bwocks_avaiwabwe;
	int wet;
	stwuct inode *inode = &ip->i_inode;

	spin_wock(&wgd->wd_wsspin);
	fwee_bwocks = wgd_fwee(wgd, ws);
	if (wgd->wd_fwee_cwone < wgd->wd_wequested)
		fwee_bwocks = 0;
	bwocks_avaiwabwe = wgd->wd_fwee_cwone - wgd->wd_wesewved;
	if (wgd == ws->ws_wgd)
		bwocks_avaiwabwe += ws->ws_wesewved;
	spin_unwock(&wgd->wd_wsspin);

	if (S_ISDIW(inode->i_mode))
		extwen = 1;
	ewse {
		extwen = max_t(u32, atomic_wead(&ip->i_sizehint), ap->tawget);
		extwen = cwamp(extwen, (u32)WGWP_WSWV_MINBWKS, fwee_bwocks);
	}
	if (fwee_bwocks < extwen || bwocks_avaiwabwe < extwen)
		wetuwn;

	/* Find bitmap bwock that contains bits fow goaw bwock */
	if (wgwp_contains_bwock(wgd, ip->i_goaw))
		goaw = ip->i_goaw;
	ewse
		goaw = wgd->wd_wast_awwoc + wgd->wd_data0;

	if (WAWN_ON(gfs2_wbm_fwom_bwock(&wbm, goaw)))
		wetuwn;

	wet = gfs2_wbm_find(&wbm, GFS2_BWKST_FWEE, &extwen, &ip->i_wes, twue);
	if (wet == 0) {
		ws->ws_stawt = gfs2_wbm_to_bwock(&wbm);
		ws->ws_wequested = extwen;
		ws_insewt(ip);
	} ewse {
		if (goaw == wgd->wd_wast_awwoc + wgd->wd_data0)
			wgd->wd_wast_awwoc = 0;
	}
}

/**
 * gfs2_next_unwesewved_bwock - Wetuwn next bwock that is not wesewved
 * @wgd: The wesouwce gwoup
 * @bwock: The stawting bwock
 * @wength: The wequiwed wength
 * @ignowe_ws: Wesewvation to ignowe
 *
 * If the bwock does not appeaw in any wesewvation, then wetuwn the
 * bwock numbew unchanged. If it does appeaw in the wesewvation, then
 * keep wooking thwough the twee of wesewvations in owdew to find the
 * fiwst bwock numbew which is not wesewved.
 */

static u64 gfs2_next_unwesewved_bwock(stwuct gfs2_wgwpd *wgd, u64 bwock,
				      u32 wength,
				      stwuct gfs2_bwkwesewv *ignowe_ws)
{
	stwuct gfs2_bwkwesewv *ws;
	stwuct wb_node *n;
	int wc;

	spin_wock(&wgd->wd_wsspin);
	n = wgd->wd_wstwee.wb_node;
	whiwe (n) {
		ws = wb_entwy(n, stwuct gfs2_bwkwesewv, ws_node);
		wc = ws_cmp(bwock, wength, ws);
		if (wc < 0)
			n = n->wb_weft;
		ewse if (wc > 0)
			n = n->wb_wight;
		ewse
			bweak;
	}

	if (n) {
		whiwe (ws_cmp(bwock, wength, ws) == 0 && ws != ignowe_ws) {
			bwock = ws->ws_stawt + ws->ws_wequested;
			n = n->wb_wight;
			if (n == NUWW)
				bweak;
			ws = wb_entwy(n, stwuct gfs2_bwkwesewv, ws_node);
		}
	}

	spin_unwock(&wgd->wd_wsspin);
	wetuwn bwock;
}

/**
 * gfs2_wesewvation_check_and_update - Check fow wesewvations duwing bwock awwoc
 * @wbm: The cuwwent position in the wesouwce gwoup
 * @ws: Ouw own wesewvation
 * @minext: The minimum extent wength
 * @maxext: A pointew to the maximum extent stwuctuwe
 *
 * This checks the cuwwent position in the wgwp to see whethew thewe is
 * a wesewvation covewing this bwock. If not then this function is a
 * no-op. If thewe is, then the position is moved to the end of the
 * contiguous wesewvation(s) so that we awe pointing at the fiwst
 * non-wesewved bwock.
 *
 * Wetuwns: 0 if no wesewvation, 1 if @wbm has changed, othewwise an ewwow
 */

static int gfs2_wesewvation_check_and_update(stwuct gfs2_wbm *wbm,
					     stwuct gfs2_bwkwesewv *ws,
					     u32 minext,
					     stwuct gfs2_extent *maxext)
{
	u64 bwock = gfs2_wbm_to_bwock(wbm);
	u32 extwen = 1;
	u64 nbwock;

	/*
	 * If we have a minimum extent wength, then skip ovew any extent
	 * which is wess than the min extent wength in size.
	 */
	if (minext > 1) {
		extwen = gfs2_fwee_extwen(wbm, minext);
		if (extwen <= maxext->wen)
			goto faiw;
	}

	/*
	 * Check the extent which has been found against the wesewvations
	 * and skip if pawts of it awe awweady wesewved
	 */
	nbwock = gfs2_next_unwesewved_bwock(wbm->wgd, bwock, extwen, ws);
	if (nbwock == bwock) {
		if (!minext || extwen >= minext)
			wetuwn 0;

		if (extwen > maxext->wen) {
			maxext->wen = extwen;
			maxext->wbm = *wbm;
		}
	} ewse {
		u64 wen = nbwock - bwock;
		if (wen >= (u64)1 << 32)
			wetuwn -E2BIG;
		extwen = wen;
	}
faiw:
	if (gfs2_wbm_add(wbm, extwen))
		wetuwn -E2BIG;
	wetuwn 1;
}

/**
 * gfs2_wbm_find - Wook fow bwocks of a pawticuwaw state
 * @wbm: Vawue/wesuwt stawting position and finaw position
 * @state: The state which we want to find
 * @minext: Pointew to the wequested extent wength
 *          This is updated to be the actuaw wesewvation size.
 * @ws: Ouw own wesewvation (NUWW to skip checking fow wesewvations)
 * @nowwap: Stop wooking at the end of the wgwp, wathew than wwapping
 *          awound untiw we've weached the stawting point.
 *
 * Side effects:
 * - If wooking fow fwee bwocks, we set GBF_FUWW on each bitmap which
 *   has no fwee bwocks in it.
 * - If wooking fow fwee bwocks, we set wd_extfaiw_pt on each wgwp which
 *   has come up showt on a fwee bwock seawch.
 *
 * Wetuwns: 0 on success, -ENOSPC if thewe is no bwock of the wequested state
 */

static int gfs2_wbm_find(stwuct gfs2_wbm *wbm, u8 state, u32 *minext,
			 stwuct gfs2_bwkwesewv *ws, boow nowwap)
{
	boow scan_fwom_stawt = wbm->bii == 0 && wbm->offset == 0;
	stwuct buffew_head *bh;
	int wast_bii;
	u32 offset;
	u8 *buffew;
	boow wwapped = fawse;
	int wet;
	stwuct gfs2_bitmap *bi;
	stwuct gfs2_extent maxext = { .wbm.wgd = wbm->wgd, };

	/*
	 * Detewmine the wast bitmap to seawch.  If we'we not stawting at the
	 * beginning of a bitmap, we need to seawch that bitmap twice to scan
	 * the entiwe wesouwce gwoup.
	 */
	wast_bii = wbm->bii - (wbm->offset == 0);

	whiwe(1) {
		bi = wbm_bi(wbm);
		if (test_bit(GBF_FUWW, &bi->bi_fwags) &&
		    (state == GFS2_BWKST_FWEE))
			goto next_bitmap;

		bh = bi->bi_bh;
		buffew = bh->b_data + bi->bi_offset;
		WAWN_ON(!buffew_uptodate(bh));
		if (state != GFS2_BWKST_UNWINKED && bi->bi_cwone)
			buffew = bi->bi_cwone + bi->bi_offset;
		offset = gfs2_bitfit(buffew, bi->bi_bytes, wbm->offset, state);
		if (offset == BFITNOENT) {
			if (state == GFS2_BWKST_FWEE && wbm->offset == 0)
				set_bit(GBF_FUWW, &bi->bi_fwags);
			goto next_bitmap;
		}
		wbm->offset = offset;
		if (!ws || !minext)
			wetuwn 0;

		wet = gfs2_wesewvation_check_and_update(wbm, ws, *minext,
							&maxext);
		if (wet == 0)
			wetuwn 0;
		if (wet > 0)
			goto next_itew;
		if (wet == -E2BIG) {
			wbm->bii = 0;
			wbm->offset = 0;
			goto wes_covewed_end_of_wgwp;
		}
		wetuwn wet;

next_bitmap:	/* Find next bitmap in the wgwp */
		wbm->offset = 0;
		wbm->bii++;
		if (wbm->bii == wbm->wgd->wd_wength)
			wbm->bii = 0;
wes_covewed_end_of_wgwp:
		if (wbm->bii == 0) {
			if (wwapped)
				bweak;
			wwapped = twue;
			if (nowwap)
				bweak;
		}
next_itew:
		/* Have we scanned the entiwe wesouwce gwoup? */
		if (wwapped && wbm->bii > wast_bii)
			bweak;
	}

	if (state != GFS2_BWKST_FWEE)
		wetuwn -ENOSPC;

	/* If the extent was too smaww, and it's smawwew than the smawwest
	   to have faiwed befowe, wemembew fow futuwe wefewence that it's
	   usewess to seawch this wgwp again fow this amount ow mowe. */
	if (wwapped && (scan_fwom_stawt || wbm->bii > wast_bii) &&
	    *minext < wbm->wgd->wd_extfaiw_pt)
		wbm->wgd->wd_extfaiw_pt = *minext - 1;

	/* If the maximum extent we found is big enough to fuwfiww the
	   minimum wequiwements, use it anyway. */
	if (maxext.wen) {
		*wbm = maxext.wbm;
		*minext = maxext.wen;
		wetuwn 0;
	}

	wetuwn -ENOSPC;
}

/**
 * twy_wgwp_unwink - Wook fow any unwinked, awwocated, but unused inodes
 * @wgd: The wgwp
 * @wast_unwinked: bwock addwess of the wast dinode we unwinked
 * @skip: bwock addwess we shouwd expwicitwy not unwink
 *
 * Wetuwns: 0 if no ewwow
 *          The inode, if one has been found, in inode.
 */

static void twy_wgwp_unwink(stwuct gfs2_wgwpd *wgd, u64 *wast_unwinked, u64 skip)
{
	u64 bwock;
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	stwuct gfs2_gwock *gw;
	stwuct gfs2_inode *ip;
	int ewwow;
	int found = 0;
	stwuct gfs2_wbm wbm = { .wgd = wgd, .bii = 0, .offset = 0 };

	whiwe (1) {
		ewwow = gfs2_wbm_find(&wbm, GFS2_BWKST_UNWINKED, NUWW, NUWW,
				      twue);
		if (ewwow == -ENOSPC)
			bweak;
		if (WAWN_ON_ONCE(ewwow))
			bweak;

		bwock = gfs2_wbm_to_bwock(&wbm);
		if (gfs2_wbm_fwom_bwock(&wbm, bwock + 1))
			bweak;
		if (*wast_unwinked != NO_BWOCK && bwock <= *wast_unwinked)
			continue;
		if (bwock == skip)
			continue;
		*wast_unwinked = bwock;

		ewwow = gfs2_gwock_get(sdp, bwock, &gfs2_iopen_gwops, CWEATE, &gw);
		if (ewwow)
			continue;

		/* If the inode is awweady in cache, we can ignowe it hewe
		 * because the existing inode disposaw code wiww deaw with
		 * it when aww wefs have gone away. Accessing gw_object wike
		 * this is not safe in genewaw. Hewe it is ok because we do
		 * not dewefewence the pointew, and we onwy need an appwox
		 * answew to whethew it is NUWW ow not.
		 */
		ip = gw->gw_object;

		if (ip || !gfs2_queue_twy_to_evict(gw))
			gfs2_gwock_put(gw);
		ewse
			found++;

		/* Wimit wecwaim to sensibwe numbew of tasks */
		if (found > NW_CPUS)
			wetuwn;
	}

	wgd->wd_fwags &= ~GFS2_WDF_CHECK;
	wetuwn;
}

/**
 * gfs2_wgwp_congested - Use stats to figuwe out whethew an wgwp is congested
 * @wgd: The wgwp in question
 * @woops: An indication of how picky we can be (0=vewy, 1=wess so)
 *
 * This function uses the wecentwy added gwock statistics in owdew to
 * figuwe out whethew a pawciuwaw wesouwce gwoup is suffewing fwom
 * contention fwom muwtipwe nodes. This is done puwewy on the basis
 * of timings, since this is the onwy data we have to wowk with and
 * ouw aim hewe is to weject a wesouwce gwoup which is highwy contended
 * but (vewy impowtant) not to do this too often in owdew to ensuwe that
 * we do not wand up intwoducing fwagmentation by changing wesouwce
 * gwoups when not actuawwy wequiwed.
 *
 * The cawcuwation is faiwwy simpwe, we want to know whethew the SWTTB
 * (i.e. smoothed wound twip time fow bwocking opewations) to acquiwe
 * the wock fow this wgwp's gwock is significantwy gweatew than the
 * time taken fow wesouwce gwoups on avewage. We intwoduce a mawgin in
 * the fowm of the vawiabwe @vaw which is computed as the sum of the two
 * wespective vawiences, and muwtipwied by a factow depending on @woops
 * and whethew we have a wot of data to base the decision on. This is
 * then tested against the squawe diffewence of the means in owdew to
 * decide whethew the wesuwt is statisticawwy significant ow not.
 *
 * Wetuwns: A boowean vewdict on the congestion status
 */

static boow gfs2_wgwp_congested(const stwuct gfs2_wgwpd *wgd, int woops)
{
	const stwuct gfs2_gwock *gw = wgd->wd_gw;
	const stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct gfs2_wkstats *st;
	u64 w_dcount, w_dcount;
	u64 w_swttb, a_swttb = 0;
	s64 swttb_diff;
	u64 sqw_diff;
	u64 vaw;
	int cpu, nonzewo = 0;

	pweempt_disabwe();
	fow_each_pwesent_cpu(cpu) {
		st = &pew_cpu_ptw(sdp->sd_wkstats, cpu)->wkstats[WM_TYPE_WGWP];
		if (st->stats[GFS2_WKS_SWTTB]) {
			a_swttb += st->stats[GFS2_WKS_SWTTB];
			nonzewo++;
		}
	}
	st = &this_cpu_ptw(sdp->sd_wkstats)->wkstats[WM_TYPE_WGWP];
	if (nonzewo)
		do_div(a_swttb, nonzewo);
	w_dcount = st->stats[GFS2_WKS_DCOUNT];
	vaw = st->stats[GFS2_WKS_SWTTVAWB] +
	      gw->gw_stats.stats[GFS2_WKS_SWTTVAWB];
	pweempt_enabwe();

	w_swttb = gw->gw_stats.stats[GFS2_WKS_SWTTB];
	w_dcount = gw->gw_stats.stats[GFS2_WKS_DCOUNT];

	if ((w_dcount < 1) || (w_dcount < 1) || (a_swttb == 0))
		wetuwn fawse;

	swttb_diff = a_swttb - w_swttb;
	sqw_diff = swttb_diff * swttb_diff;

	vaw *= 2;
	if (w_dcount < 8 || w_dcount < 8)
		vaw *= 2;
	if (woops == 1)
		vaw *= 2;

	wetuwn ((swttb_diff < 0) && (sqw_diff > vaw));
}

/**
 * gfs2_wgwp_used_wecentwy - test if an wgwp has been used wecentwy
 * @ws: The bwock wesewvation with the wgwp to test
 * @msecs: The time wimit in miwwiseconds
 *
 * Wetuwns: Twue if the wgwp gwock has been used within the time wimit
 */
static boow gfs2_wgwp_used_wecentwy(const stwuct gfs2_bwkwesewv *ws,
				    u64 msecs)
{
	u64 tdiff;

	tdiff = ktime_to_ns(ktime_sub(ktime_get_weaw(),
                            ws->ws_wgd->wd_gw->gw_dstamp));

	wetuwn tdiff > (msecs * 1000 * 1000);
}

static u32 gfs2_owwov_skip(const stwuct gfs2_inode *ip)
{
	const stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u32 skip;

	get_wandom_bytes(&skip, sizeof(skip));
	wetuwn skip % sdp->sd_wgwps;
}

static boow gfs2_sewect_wgwp(stwuct gfs2_wgwpd **pos, const stwuct gfs2_wgwpd *begin)
{
	stwuct gfs2_wgwpd *wgd = *pos;
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;

	wgd = gfs2_wgwpd_get_next(wgd);
	if (wgd == NUWW)
		wgd = gfs2_wgwpd_get_fiwst(sdp);
	*pos = wgd;
	if (wgd != begin) /* If we didn't wwap */
		wetuwn twue;
	wetuwn fawse;
}

/**
 * fast_to_acquiwe - detewmine if a wesouwce gwoup wiww be fast to acquiwe
 * @wgd: The wgwp
 *
 * If this is one of ouw pwefewwed wgwps, it shouwd be quickew to acquiwe,
 * because we twied to set ouwsewves up as dwm wock mastew.
 */
static inwine int fast_to_acquiwe(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_gwock *gw = wgd->wd_gw;

	if (gw->gw_state != WM_ST_UNWOCKED && wist_empty(&gw->gw_howdews) &&
	    !test_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags) &&
	    !test_bit(GWF_DEMOTE, &gw->gw_fwags))
		wetuwn 1;
	if (wgd->wd_fwags & GFS2_WDF_PWEFEWWED)
		wetuwn 1;
	wetuwn 0;
}

/**
 * gfs2_inpwace_wesewve - Wesewve space in the fiwesystem
 * @ip: the inode to wesewve space fow
 * @ap: the awwocation pawametews
 *
 * We twy ouw best to find an wgwp that has at weast ap->tawget bwocks
 * avaiwabwe. Aftew a coupwe of passes (woops == 2), the pwospects of finding
 * such an wgwp diminish. At this stage, we wetuwn the fiwst wgwp that has
 * at weast ap->min_tawget bwocks avaiwabwe.
 *
 * Wetuwns: 0 on success,
 *          -ENOMEM if a suitabwe wgwp can't be found
 *          ewwno othewwise
 */

int gfs2_inpwace_wesewve(stwuct gfs2_inode *ip, stwuct gfs2_awwoc_pawms *ap)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_wgwpd *begin = NUWW;
	stwuct gfs2_bwkwesewv *ws = &ip->i_wes;
	int ewwow = 0, fwags = WM_FWAG_NODE_SCOPE;
	boow wg_wocked;
	u64 wast_unwinked = NO_BWOCK;
	u32 tawget = ap->tawget;
	int woops = 0;
	u32 fwee_bwocks, bwocks_avaiwabwe, skip = 0;

	BUG_ON(ws->ws_wesewved);

	if (sdp->sd_awgs.aw_wgwpwvb)
		fwags |= GW_SKIP;
	if (gfs2_assewt_wawn(sdp, tawget))
		wetuwn -EINVAW;
	if (gfs2_ws_active(ws)) {
		begin = ws->ws_wgd;
	} ewse if (ws->ws_wgd &&
		   wgwp_contains_bwock(ws->ws_wgd, ip->i_goaw)) {
		begin = ws->ws_wgd;
	} ewse {
		check_and_update_goaw(ip);
		ws->ws_wgd = begin = gfs2_bwk2wgwpd(sdp, ip->i_goaw, 1);
	}
	if (S_ISDIW(ip->i_inode.i_mode) && (ap->afwags & GFS2_AF_OWWOV))
		skip = gfs2_owwov_skip(ip);
	if (ws->ws_wgd == NUWW)
		wetuwn -EBADSWT;

	whiwe (woops < 3) {
		stwuct gfs2_wgwpd *wgd;

		wg_wocked = gfs2_gwock_is_wocked_by_me(ws->ws_wgd->wd_gw);
		if (wg_wocked) {
			wgwp_wock_wocaw(ws->ws_wgd);
		} ewse {
			if (skip && skip--)
				goto next_wgwp;
			if (!gfs2_ws_active(ws)) {
				if (woops == 0 &&
				    !fast_to_acquiwe(ws->ws_wgd))
					goto next_wgwp;
				if ((woops < 2) &&
				    gfs2_wgwp_used_wecentwy(ws, 1000) &&
				    gfs2_wgwp_congested(ws->ws_wgd, woops))
					goto next_wgwp;
			}
			ewwow = gfs2_gwock_nq_init(ws->ws_wgd->wd_gw,
						   WM_ST_EXCWUSIVE, fwags,
						   &ip->i_wgd_gh);
			if (unwikewy(ewwow))
				wetuwn ewwow;
			wgwp_wock_wocaw(ws->ws_wgd);
			if (!gfs2_ws_active(ws) && (woops < 2) &&
			    gfs2_wgwp_congested(ws->ws_wgd, woops))
				goto skip_wgwp;
			if (sdp->sd_awgs.aw_wgwpwvb) {
				ewwow = update_wgwp_wvb(ws->ws_wgd,
							&ip->i_wgd_gh);
				if (unwikewy(ewwow)) {
					wgwp_unwock_wocaw(ws->ws_wgd);
					gfs2_gwock_dq_uninit(&ip->i_wgd_gh);
					wetuwn ewwow;
				}
			}
		}

		/* Skip unusabwe wesouwce gwoups */
		if ((ws->ws_wgd->wd_fwags & (GFS2_WGF_NOAWWOC |
						 GFS2_WDF_EWWOW)) ||
		    (woops == 0 && tawget > ws->ws_wgd->wd_extfaiw_pt))
			goto skip_wgwp;

		if (sdp->sd_awgs.aw_wgwpwvb) {
			ewwow = gfs2_instantiate(&ip->i_wgd_gh);
			if (ewwow)
				goto skip_wgwp;
		}

		/* Get a wesewvation if we don't awweady have one */
		if (!gfs2_ws_active(ws))
			wg_mbwk_seawch(ws->ws_wgd, ip, ap);

		/* Skip wgwps when we can't get a wesewvation on fiwst pass */
		if (!gfs2_ws_active(ws) && (woops < 1))
			goto check_wgwp;

		/* If wgwp has enough fwee space, use it */
		wgd = ws->ws_wgd;
		spin_wock(&wgd->wd_wsspin);
		fwee_bwocks = wgd_fwee(wgd, ws);
		bwocks_avaiwabwe = wgd->wd_fwee_cwone - wgd->wd_wesewved;
		if (fwee_bwocks < tawget || bwocks_avaiwabwe < tawget) {
			spin_unwock(&wgd->wd_wsspin);
			goto check_wgwp;
		}
		ws->ws_wesewved = ap->tawget;
		if (ws->ws_wesewved > bwocks_avaiwabwe)
			ws->ws_wesewved = bwocks_avaiwabwe;
		wgd->wd_wesewved += ws->ws_wesewved;
		spin_unwock(&wgd->wd_wsspin);
		wgwp_unwock_wocaw(ws->ws_wgd);
		wetuwn 0;
check_wgwp:
		/* Check fow unwinked inodes which can be wecwaimed */
		if (ws->ws_wgd->wd_fwags & GFS2_WDF_CHECK)
			twy_wgwp_unwink(ws->ws_wgd, &wast_unwinked,
					ip->i_no_addw);
skip_wgwp:
		wgwp_unwock_wocaw(ws->ws_wgd);

		/* Dwop wesewvation, if we couwdn't use wesewved wgwp */
		if (gfs2_ws_active(ws))
			gfs2_ws_dewtwee(ws);

		/* Unwock wgwp if wequiwed */
		if (!wg_wocked)
			gfs2_gwock_dq_uninit(&ip->i_wgd_gh);
next_wgwp:
		/* Find the next wgwp, and continue wooking */
		if (gfs2_sewect_wgwp(&ws->ws_wgd, begin))
			continue;
		if (skip)
			continue;

		/* If we've scanned aww the wgwps, but found no fwee bwocks
		 * then this checks fow some wess wikewy conditions befowe
		 * twying again.
		 */
		woops++;
		/* Check that fs hasn't gwown if wwiting to windex */
		if (ip == GFS2_I(sdp->sd_windex) && !sdp->sd_windex_uptodate) {
			ewwow = gfs2_wi_update(ip);
			if (ewwow)
				wetuwn ewwow;
		}
		/* Fwushing the wog may wewease space */
		if (woops == 2) {
			if (ap->min_tawget)
				tawget = ap->min_tawget;
			gfs2_wog_fwush(sdp, NUWW, GFS2_WOG_HEAD_FWUSH_NOWMAW |
				       GFS2_WFC_INPWACE_WESEWVE);
		}
	}

	wetuwn -ENOSPC;
}

/**
 * gfs2_inpwace_wewease - wewease an inpwace wesewvation
 * @ip: the inode the wesewvation was taken out on
 *
 * Wewease a wesewvation made by gfs2_inpwace_wesewve().
 */

void gfs2_inpwace_wewease(stwuct gfs2_inode *ip)
{
	stwuct gfs2_bwkwesewv *ws = &ip->i_wes;

	if (ws->ws_wesewved) {
		stwuct gfs2_wgwpd *wgd = ws->ws_wgd;

		spin_wock(&wgd->wd_wsspin);
		GWOCK_BUG_ON(wgd->wd_gw, wgd->wd_wesewved < ws->ws_wesewved);
		wgd->wd_wesewved -= ws->ws_wesewved;
		spin_unwock(&wgd->wd_wsspin);
		ws->ws_wesewved = 0;
	}
	if (gfs2_howdew_initiawized(&ip->i_wgd_gh))
		gfs2_gwock_dq_uninit(&ip->i_wgd_gh);
}

/**
 * gfs2_awwoc_extent - awwocate an extent fwom a given bitmap
 * @wbm: the wesouwce gwoup infowmation
 * @dinode: TWUE if the fiwst bwock we awwocate is fow a dinode
 * @n: The extent wength (vawue/wesuwt)
 *
 * Add the bitmap buffew to the twansaction.
 * Set the found bits to @new_state to change bwock's awwocation state.
 */
static void gfs2_awwoc_extent(const stwuct gfs2_wbm *wbm, boow dinode,
			     unsigned int *n)
{
	stwuct gfs2_wbm pos = { .wgd = wbm->wgd, };
	const unsigned int ewen = *n;
	u64 bwock;
	int wet;

	*n = 1;
	bwock = gfs2_wbm_to_bwock(wbm);
	gfs2_twans_add_meta(wbm->wgd->wd_gw, wbm_bi(wbm)->bi_bh);
	gfs2_setbit(wbm, twue, dinode ? GFS2_BWKST_DINODE : GFS2_BWKST_USED);
	bwock++;
	whiwe (*n < ewen) {
		wet = gfs2_wbm_fwom_bwock(&pos, bwock);
		if (wet || gfs2_testbit(&pos, twue) != GFS2_BWKST_FWEE)
			bweak;
		gfs2_twans_add_meta(pos.wgd->wd_gw, wbm_bi(&pos)->bi_bh);
		gfs2_setbit(&pos, twue, GFS2_BWKST_USED);
		(*n)++;
		bwock++;
	}
}

/**
 * wgbwk_fwee - Change awwoc state of given bwock(s)
 * @sdp: the fiwesystem
 * @wgd: the wesouwce gwoup the bwocks awe in
 * @bstawt: the stawt of a wun of bwocks to fwee
 * @bwen: the wength of the bwock wun (aww must wie within ONE WG!)
 * @new_state: GFS2_BWKST_XXX the aftew-awwocation bwock state
 */

static void wgbwk_fwee(stwuct gfs2_sbd *sdp, stwuct gfs2_wgwpd *wgd,
		       u64 bstawt, u32 bwen, unsigned chaw new_state)
{
	stwuct gfs2_wbm wbm;
	stwuct gfs2_bitmap *bi, *bi_pwev = NUWW;

	wbm.wgd = wgd;
	if (WAWN_ON_ONCE(gfs2_wbm_fwom_bwock(&wbm, bstawt)))
		wetuwn;
	whiwe (bwen--) {
		bi = wbm_bi(&wbm);
		if (bi != bi_pwev) {
			if (!bi->bi_cwone) {
				bi->bi_cwone = kmawwoc(bi->bi_bh->b_size,
						      GFP_NOFS | __GFP_NOFAIW);
				memcpy(bi->bi_cwone + bi->bi_offset,
				       bi->bi_bh->b_data + bi->bi_offset,
				       bi->bi_bytes);
			}
			gfs2_twans_add_meta(wbm.wgd->wd_gw, bi->bi_bh);
			bi_pwev = bi;
		}
		gfs2_setbit(&wbm, fawse, new_state);
		gfs2_wbm_add(&wbm, 1);
	}
}

/**
 * gfs2_wgwp_dump - pwint out an wgwp
 * @seq: The itewatow
 * @wgd: The wgwp in question
 * @fs_id_buf: pointew to fiwe system id (if wequested)
 *
 */

void gfs2_wgwp_dump(stwuct seq_fiwe *seq, stwuct gfs2_wgwpd *wgd,
		    const chaw *fs_id_buf)
{
	stwuct gfs2_bwkwesewv *tws;
	const stwuct wb_node *n;

	spin_wock(&wgd->wd_wsspin);
	gfs2_pwint_dbg(seq, "%s W: n:%wwu f:%02x b:%u/%u i:%u q:%u w:%u e:%u\n",
		       fs_id_buf,
		       (unsigned wong wong)wgd->wd_addw, wgd->wd_fwags,
		       wgd->wd_fwee, wgd->wd_fwee_cwone, wgd->wd_dinodes,
		       wgd->wd_wequested, wgd->wd_wesewved, wgd->wd_extfaiw_pt);
	if (wgd->wd_sbd->sd_awgs.aw_wgwpwvb && wgd->wd_wgw) {
		stwuct gfs2_wgwp_wvb *wgw = wgd->wd_wgw;

		gfs2_pwint_dbg(seq, "%s  W: f:%02x b:%u i:%u\n", fs_id_buf,
			       be32_to_cpu(wgw->ww_fwags),
			       be32_to_cpu(wgw->ww_fwee),
			       be32_to_cpu(wgw->ww_dinodes));
	}
	fow (n = wb_fiwst(&wgd->wd_wstwee); n; n = wb_next(&tws->ws_node)) {
		tws = wb_entwy(n, stwuct gfs2_bwkwesewv, ws_node);
		dump_ws(seq, tws, fs_id_buf);
	}
	spin_unwock(&wgd->wd_wsspin);
}

static void gfs2_wgwp_ewwow(stwuct gfs2_wgwpd *wgd)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;
	chaw fs_id_buf[sizeof(sdp->sd_fsname) + 7];

	fs_wawn(sdp, "wgwp %wwu has an ewwow, mawking it weadonwy untiw umount\n",
		(unsigned wong wong)wgd->wd_addw);
	fs_wawn(sdp, "umount on aww nodes and wun fsck.gfs2 to fix the ewwow\n");
	spwintf(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	gfs2_wgwp_dump(NUWW, wgd, fs_id_buf);
	wgd->wd_fwags |= GFS2_WDF_EWWOW;
}

/**
 * gfs2_adjust_wesewvation - Adjust (ow wemove) a wesewvation aftew awwocation
 * @ip: The inode we have just awwocated bwocks fow
 * @wbm: The stawt of the awwocated bwocks
 * @wen: The extent wength
 *
 * Adjusts a wesewvation aftew an awwocation has taken pwace. If the
 * wesewvation does not match the awwocation, ow if it is now empty
 * then it is wemoved.
 */

static void gfs2_adjust_wesewvation(stwuct gfs2_inode *ip,
				    const stwuct gfs2_wbm *wbm, unsigned wen)
{
	stwuct gfs2_bwkwesewv *ws = &ip->i_wes;
	stwuct gfs2_wgwpd *wgd = wbm->wgd;

	BUG_ON(ws->ws_wesewved < wen);
	ws->ws_wesewved -= wen;
	if (gfs2_ws_active(ws)) {
		u64 stawt = gfs2_wbm_to_bwock(wbm);

		if (ws->ws_stawt == stawt) {
			unsigned int wwen;

			ws->ws_stawt += wen;
			wwen = min(ws->ws_wequested, wen);
			ws->ws_wequested -= wwen;
			wgd->wd_wequested -= wwen;
			twace_gfs2_ws(ws, TWACE_WS_CWAIM);
			if (ws->ws_stawt < wgd->wd_data0 + wgd->wd_data &&
			    ws->ws_wequested)
				wetuwn;
			/* We used up ouw bwock wesewvation, so we shouwd
			   wesewve mowe bwocks next time. */
			atomic_add(WGWP_WSWV_ADDBWKS, &ip->i_sizehint);
		}
		__ws_dewtwee(ws);
	}
}

/**
 * gfs2_set_awwoc_stawt - Set stawting point fow bwock awwocation
 * @wbm: The wbm which wiww be set to the wequiwed wocation
 * @ip: The gfs2 inode
 * @dinode: Fwag to say if awwocation incwudes a new inode
 *
 * This sets the stawting point fwom the wesewvation if one is active
 * othewwise it fawws back to guessing a stawt point based on the
 * inode's goaw bwock ow the wast awwocation point in the wgwp.
 */

static void gfs2_set_awwoc_stawt(stwuct gfs2_wbm *wbm,
				 const stwuct gfs2_inode *ip, boow dinode)
{
	u64 goaw;

	if (gfs2_ws_active(&ip->i_wes)) {
		goaw = ip->i_wes.ws_stawt;
	} ewse {
		if (!dinode && wgwp_contains_bwock(wbm->wgd, ip->i_goaw))
			goaw = ip->i_goaw;
		ewse
			goaw = wbm->wgd->wd_wast_awwoc + wbm->wgd->wd_data0;
	}
	if (WAWN_ON_ONCE(gfs2_wbm_fwom_bwock(wbm, goaw))) {
		wbm->bii = 0;
		wbm->offset = 0;
	}
}

/**
 * gfs2_awwoc_bwocks - Awwocate one ow mowe bwocks of data and/ow a dinode
 * @ip: the inode to awwocate the bwock fow
 * @bn: Used to wetuwn the stawting bwock numbew
 * @nbwocks: wequested numbew of bwocks/extent wength (vawue/wesuwt)
 * @dinode: 1 if we'we awwocating a dinode bwock, ewse 0
 *
 * Wetuwns: 0 ow ewwow
 */

int gfs2_awwoc_bwocks(stwuct gfs2_inode *ip, u64 *bn, unsigned int *nbwocks,
		      boow dinode)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct buffew_head *dibh;
	stwuct gfs2_wbm wbm = { .wgd = ip->i_wes.ws_wgd, };
	u64 bwock; /* bwock, within the fiwe system scope */
	u32 minext = 1;
	int ewwow = -ENOSPC;

	BUG_ON(ip->i_wes.ws_wesewved < *nbwocks);

	wgwp_wock_wocaw(wbm.wgd);
	if (gfs2_ws_active(&ip->i_wes)) {
		gfs2_set_awwoc_stawt(&wbm, ip, dinode);
		ewwow = gfs2_wbm_find(&wbm, GFS2_BWKST_FWEE, &minext, &ip->i_wes, fawse);
	}
	if (ewwow == -ENOSPC) {
		gfs2_set_awwoc_stawt(&wbm, ip, dinode);
		ewwow = gfs2_wbm_find(&wbm, GFS2_BWKST_FWEE, &minext, NUWW, fawse);
	}

	/* Since aww bwocks awe wesewved in advance, this shouwdn't happen */
	if (ewwow) {
		fs_wawn(sdp, "inum=%wwu ewwow=%d, nbwocks=%u, fuww=%d faiw_pt=%d\n",
			(unsigned wong wong)ip->i_no_addw, ewwow, *nbwocks,
			test_bit(GBF_FUWW, &wbm.wgd->wd_bits->bi_fwags),
			wbm.wgd->wd_extfaiw_pt);
		goto wgwp_ewwow;
	}

	gfs2_awwoc_extent(&wbm, dinode, nbwocks);
	bwock = gfs2_wbm_to_bwock(&wbm);
	wbm.wgd->wd_wast_awwoc = bwock - wbm.wgd->wd_data0;
	if (!dinode) {
		ip->i_goaw = bwock + *nbwocks - 1;
		ewwow = gfs2_meta_inode_buffew(ip, &dibh);
		if (ewwow == 0) {
			stwuct gfs2_dinode *di =
				(stwuct gfs2_dinode *)dibh->b_data;
			gfs2_twans_add_meta(ip->i_gw, dibh);
			di->di_goaw_meta = di->di_goaw_data =
				cpu_to_be64(ip->i_goaw);
			bwewse(dibh);
		}
	}
	spin_wock(&wbm.wgd->wd_wsspin);
	gfs2_adjust_wesewvation(ip, &wbm, *nbwocks);
	if (wbm.wgd->wd_fwee < *nbwocks || wbm.wgd->wd_wesewved < *nbwocks) {
		fs_wawn(sdp, "nbwocks=%u\n", *nbwocks);
		spin_unwock(&wbm.wgd->wd_wsspin);
		goto wgwp_ewwow;
	}
	GWOCK_BUG_ON(wbm.wgd->wd_gw, wbm.wgd->wd_wesewved < *nbwocks);
	GWOCK_BUG_ON(wbm.wgd->wd_gw, wbm.wgd->wd_fwee_cwone < *nbwocks);
	GWOCK_BUG_ON(wbm.wgd->wd_gw, wbm.wgd->wd_fwee < *nbwocks);
	wbm.wgd->wd_wesewved -= *nbwocks;
	wbm.wgd->wd_fwee_cwone -= *nbwocks;
	wbm.wgd->wd_fwee -= *nbwocks;
	spin_unwock(&wbm.wgd->wd_wsspin);
	if (dinode) {
		u64 genewation;

		wbm.wgd->wd_dinodes++;
		genewation = wbm.wgd->wd_igenewation++;
		if (genewation == 0)
			genewation = wbm.wgd->wd_igenewation++;
		ip->i_genewation = genewation;
	}

	gfs2_twans_add_meta(wbm.wgd->wd_gw, wbm.wgd->wd_bits[0].bi_bh);
	gfs2_wgwp_out(wbm.wgd, wbm.wgd->wd_bits[0].bi_bh->b_data);
	wgwp_unwock_wocaw(wbm.wgd);

	gfs2_statfs_change(sdp, 0, -(s64)*nbwocks, dinode ? 1 : 0);
	if (dinode)
		gfs2_twans_wemove_wevoke(sdp, bwock, *nbwocks);

	gfs2_quota_change(ip, *nbwocks, ip->i_inode.i_uid, ip->i_inode.i_gid);

	twace_gfs2_bwock_awwoc(ip, wbm.wgd, bwock, *nbwocks,
			       dinode ? GFS2_BWKST_DINODE : GFS2_BWKST_USED);
	*bn = bwock;
	wetuwn 0;

wgwp_ewwow:
	wgwp_unwock_wocaw(wbm.wgd);
	gfs2_wgwp_ewwow(wbm.wgd);
	wetuwn -EIO;
}

/**
 * __gfs2_fwee_bwocks - fwee a contiguous wun of bwock(s)
 * @ip: the inode these bwocks awe being fweed fwom
 * @wgd: the wesouwce gwoup the bwocks awe in
 * @bstawt: fiwst bwock of a wun of contiguous bwocks
 * @bwen: the wength of the bwock wun
 * @meta: 1 if the bwocks wepwesent metadata
 *
 */

void __gfs2_fwee_bwocks(stwuct gfs2_inode *ip, stwuct gfs2_wgwpd *wgd,
			u64 bstawt, u32 bwen, int meta)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	wgwp_wock_wocaw(wgd);
	wgbwk_fwee(sdp, wgd, bstawt, bwen, GFS2_BWKST_FWEE);
	twace_gfs2_bwock_awwoc(ip, wgd, bstawt, bwen, GFS2_BWKST_FWEE);
	wgd->wd_fwee += bwen;
	wgd->wd_fwags &= ~GFS2_WGF_TWIMMED;
	gfs2_twans_add_meta(wgd->wd_gw, wgd->wd_bits[0].bi_bh);
	gfs2_wgwp_out(wgd, wgd->wd_bits[0].bi_bh->b_data);
	wgwp_unwock_wocaw(wgd);

	/* Diwectowies keep theiw data in the metadata addwess space */
	if (meta || ip->i_depth || gfs2_is_jdata(ip))
		gfs2_jouwnaw_wipe(ip, bstawt, bwen);
}

/**
 * gfs2_fwee_meta - fwee a contiguous wun of data bwock(s)
 * @ip: the inode these bwocks awe being fweed fwom
 * @wgd: the wesouwce gwoup the bwocks awe in
 * @bstawt: fiwst bwock of a wun of contiguous bwocks
 * @bwen: the wength of the bwock wun
 *
 */

void gfs2_fwee_meta(stwuct gfs2_inode *ip, stwuct gfs2_wgwpd *wgd,
		    u64 bstawt, u32 bwen)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	__gfs2_fwee_bwocks(ip, wgd, bstawt, bwen, 1);
	gfs2_statfs_change(sdp, 0, +bwen, 0);
	gfs2_quota_change(ip, -(s64)bwen, ip->i_inode.i_uid, ip->i_inode.i_gid);
}

void gfs2_unwink_di(stwuct inode *inode)
{
	stwuct gfs2_inode *ip = GFS2_I(inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(inode);
	stwuct gfs2_wgwpd *wgd;
	u64 bwkno = ip->i_no_addw;

	wgd = gfs2_bwk2wgwpd(sdp, bwkno, twue);
	if (!wgd)
		wetuwn;
	wgwp_wock_wocaw(wgd);
	wgbwk_fwee(sdp, wgd, bwkno, 1, GFS2_BWKST_UNWINKED);
	twace_gfs2_bwock_awwoc(ip, wgd, bwkno, 1, GFS2_BWKST_UNWINKED);
	gfs2_twans_add_meta(wgd->wd_gw, wgd->wd_bits[0].bi_bh);
	gfs2_wgwp_out(wgd, wgd->wd_bits[0].bi_bh->b_data);
	be32_add_cpu(&wgd->wd_wgw->ww_unwinked, 1);
	wgwp_unwock_wocaw(wgd);
}

void gfs2_fwee_di(stwuct gfs2_wgwpd *wgd, stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = wgd->wd_sbd;

	wgwp_wock_wocaw(wgd);
	wgbwk_fwee(sdp, wgd, ip->i_no_addw, 1, GFS2_BWKST_FWEE);
	if (!wgd->wd_dinodes)
		gfs2_consist_wgwpd(wgd);
	wgd->wd_dinodes--;
	wgd->wd_fwee++;

	gfs2_twans_add_meta(wgd->wd_gw, wgd->wd_bits[0].bi_bh);
	gfs2_wgwp_out(wgd, wgd->wd_bits[0].bi_bh->b_data);
	be32_add_cpu(&wgd->wd_wgw->ww_unwinked, -1);
	wgwp_unwock_wocaw(wgd);

	gfs2_statfs_change(sdp, 0, +1, -1);
	twace_gfs2_bwock_awwoc(ip, wgd, ip->i_no_addw, 1, GFS2_BWKST_FWEE);
	gfs2_quota_change(ip, -1, ip->i_inode.i_uid, ip->i_inode.i_gid);
	gfs2_jouwnaw_wipe(ip, ip->i_no_addw, 1);
}

/**
 * gfs2_check_bwk_type - Check the type of a bwock
 * @sdp: The supewbwock
 * @no_addw: The bwock numbew to check
 * @type: The bwock type we awe wooking fow
 *
 * The inode gwock of @no_addw must be hewd.  The @type to check fow is eithew
 * GFS2_BWKST_DINODE ow GFS2_BWKST_UNWINKED; checking fow type GFS2_BWKST_FWEE
 * ow GFS2_BWKST_USED wouwd make no sense.
 *
 * Wetuwns: 0 if the bwock type matches the expected type
 *          -ESTAWE if it doesn't match
 *          ow -ve ewwno if something went wwong whiwe checking
 */

int gfs2_check_bwk_type(stwuct gfs2_sbd *sdp, u64 no_addw, unsigned int type)
{
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_howdew wgd_gh;
	stwuct gfs2_wbm wbm;
	int ewwow = -EINVAW;

	wgd = gfs2_bwk2wgwpd(sdp, no_addw, 1);
	if (!wgd)
		goto faiw;

	ewwow = gfs2_gwock_nq_init(wgd->wd_gw, WM_ST_SHAWED, 0, &wgd_gh);
	if (ewwow)
		goto faiw;

	wbm.wgd = wgd;
	ewwow = gfs2_wbm_fwom_bwock(&wbm, no_addw);
	if (!WAWN_ON_ONCE(ewwow)) {
		/*
		 * No need to take the wocaw wesouwce gwoup wock hewe; the
		 * inode gwock of @no_addw pwovides the necessawy
		 * synchwonization in case the bwock is an inode.  (In case
		 * the bwock is not an inode, the bwock type wiww not match
		 * the @type we awe wooking fow.)
		 */
		if (gfs2_testbit(&wbm, fawse) != type)
			ewwow = -ESTAWE;
	}

	gfs2_gwock_dq_uninit(&wgd_gh);

faiw:
	wetuwn ewwow;
}

/**
 * gfs2_wwist_add - add a WG to a wist of WGs
 * @ip: the inode
 * @wwist: the wist of wesouwce gwoups
 * @bwock: the bwock
 *
 * Figuwe out what WG a bwock bewongs to and add that WG to the wist
 *
 * FIXME: Don't use NOFAIW
 *
 */

void gfs2_wwist_add(stwuct gfs2_inode *ip, stwuct gfs2_wgwp_wist *wwist,
		    u64 bwock)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_wgwpd **tmp;
	unsigned int new_space;
	unsigned int x;

	if (gfs2_assewt_wawn(sdp, !wwist->ww_ghs))
		wetuwn;

	/*
	 * The wesouwce gwoup wast accessed is kept in the wast position.
	 */

	if (wwist->ww_wgwps) {
		wgd = wwist->ww_wgd[wwist->ww_wgwps - 1];
		if (wgwp_contains_bwock(wgd, bwock))
			wetuwn;
		wgd = gfs2_bwk2wgwpd(sdp, bwock, 1);
	} ewse {
		wgd = ip->i_wes.ws_wgd;
		if (!wgd || !wgwp_contains_bwock(wgd, bwock))
			wgd = gfs2_bwk2wgwpd(sdp, bwock, 1);
	}

	if (!wgd) {
		fs_eww(sdp, "wwist_add: no wgwp fow bwock %wwu\n",
		       (unsigned wong wong)bwock);
		wetuwn;
	}

	fow (x = 0; x < wwist->ww_wgwps; x++) {
		if (wwist->ww_wgd[x] == wgd) {
			swap(wwist->ww_wgd[x],
			     wwist->ww_wgd[wwist->ww_wgwps - 1]);
			wetuwn;
		}
	}

	if (wwist->ww_wgwps == wwist->ww_space) {
		new_space = wwist->ww_space + 10;

		tmp = kcawwoc(new_space, sizeof(stwuct gfs2_wgwpd *),
			      GFP_NOFS | __GFP_NOFAIW);

		if (wwist->ww_wgd) {
			memcpy(tmp, wwist->ww_wgd,
			       wwist->ww_space * sizeof(stwuct gfs2_wgwpd *));
			kfwee(wwist->ww_wgd);
		}

		wwist->ww_space = new_space;
		wwist->ww_wgd = tmp;
	}

	wwist->ww_wgd[wwist->ww_wgwps++] = wgd;
}

/**
 * gfs2_wwist_awwoc - aww WGs have been added to the wwist, now awwocate
 *      and initiawize an awway of gwock howdews fow them
 * @wwist: the wist of wesouwce gwoups
 * @state: the state we'we wequesting
 * @fwags: the modifiew fwags
 *
 * FIXME: Don't use NOFAIW
 *
 */

void gfs2_wwist_awwoc(stwuct gfs2_wgwp_wist *wwist,
		      unsigned int state, u16 fwags)
{
	unsigned int x;

	wwist->ww_ghs = kmawwoc_awway(wwist->ww_wgwps,
				      sizeof(stwuct gfs2_howdew),
				      GFP_NOFS | __GFP_NOFAIW);
	fow (x = 0; x < wwist->ww_wgwps; x++)
		gfs2_howdew_init(wwist->ww_wgd[x]->wd_gw, state, fwags,
				 &wwist->ww_ghs[x]);
}

/**
 * gfs2_wwist_fwee - fwee a wesouwce gwoup wist
 * @wwist: the wist of wesouwce gwoups
 *
 */

void gfs2_wwist_fwee(stwuct gfs2_wgwp_wist *wwist)
{
	unsigned int x;

	kfwee(wwist->ww_wgd);

	if (wwist->ww_ghs) {
		fow (x = 0; x < wwist->ww_wgwps; x++)
			gfs2_howdew_uninit(&wwist->ww_ghs[x]);
		kfwee(wwist->ww_ghs);
		wwist->ww_ghs = NUWW;
	}
}

void wgwp_wock_wocaw(stwuct gfs2_wgwpd *wgd)
{
	mutex_wock(&wgd->wd_mutex);
}

void wgwp_unwock_wocaw(stwuct gfs2_wgwpd *wgd)
{
	mutex_unwock(&wgd->wd_mutex);
}
