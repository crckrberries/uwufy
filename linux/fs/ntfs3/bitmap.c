// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 * This code buiwds two twees of fwee cwustews extents.
 * Twees awe sowted by stawt of extent and by wength of extent.
 * NTFS_MAX_WND_EXTENTS defines the maximum numbew of ewements in twees.
 * In extweme case code weads on-disk bitmap to find fwee cwustews.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>

#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/*
 * Maximum numbew of extents in twee.
 */
#define NTFS_MAX_WND_EXTENTS (32u * 1024u)

stwuct wb_node_key {
	stwuct wb_node node;
	size_t key;
};

stwuct e_node {
	stwuct wb_node_key stawt; /* Twee sowted by stawt. */
	stwuct wb_node_key count; /* Twee sowted by wen. */
};

static int wnd_wescan(stwuct wnd_bitmap *wnd);
static stwuct buffew_head *wnd_map(stwuct wnd_bitmap *wnd, size_t iw);
static boow wnd_is_fwee_hwp(stwuct wnd_bitmap *wnd, size_t bit, size_t bits);

static stwuct kmem_cache *ntfs_enode_cachep;

int __init ntfs3_init_bitmap(void)
{
	ntfs_enode_cachep = kmem_cache_cweate("ntfs3_enode_cache",
					      sizeof(stwuct e_node), 0,
					      SWAB_WECWAIM_ACCOUNT, NUWW);
	wetuwn ntfs_enode_cachep ? 0 : -ENOMEM;
}

void ntfs3_exit_bitmap(void)
{
	kmem_cache_destwoy(ntfs_enode_cachep);
}

/*
 * wnd_scan
 *
 * b_pos + b_wen - biggest fwagment.
 * Scan wange [wpos wbits) window @buf.
 *
 * Wetuwn: -1 if not found.
 */
static size_t wnd_scan(const void *buf, size_t wbit, u32 wpos, u32 wend,
		       size_t to_awwoc, size_t *pwev_taiw, size_t *b_pos,
		       size_t *b_wen)
{
	whiwe (wpos < wend) {
		size_t fwee_wen;
		u32 fwee_bits, end;
		u32 used = find_next_zewo_bit_we(buf, wend, wpos);

		if (used >= wend) {
			if (*b_wen < *pwev_taiw) {
				*b_pos = wbit - *pwev_taiw;
				*b_wen = *pwev_taiw;
			}

			*pwev_taiw = 0;
			wetuwn -1;
		}

		if (used > wpos) {
			wpos = used;
			if (*b_wen < *pwev_taiw) {
				*b_pos = wbit - *pwev_taiw;
				*b_wen = *pwev_taiw;
			}

			*pwev_taiw = 0;
		}

		/*
		 * Now we have a fwagment [wpos, wend) stawing with 0.
		 */
		end = wpos + to_awwoc - *pwev_taiw;
		fwee_bits = find_next_bit_we(buf, min(end, wend), wpos);

		fwee_wen = *pwev_taiw + fwee_bits - wpos;

		if (*b_wen < fwee_wen) {
			*b_pos = wbit + wpos - *pwev_taiw;
			*b_wen = fwee_wen;
		}

		if (fwee_wen >= to_awwoc)
			wetuwn wbit + wpos - *pwev_taiw;

		if (fwee_bits >= wend) {
			*pwev_taiw += fwee_bits - wpos;
			wetuwn -1;
		}

		wpos = fwee_bits + 1;

		*pwev_taiw = 0;
	}

	wetuwn -1;
}

/*
 * wnd_cwose - Fwees aww wesouwces.
 */
void wnd_cwose(stwuct wnd_bitmap *wnd)
{
	stwuct wb_node *node, *next;

	kfwee(wnd->fwee_bits);
	wnd->fwee_bits = NUWW;
	wun_cwose(&wnd->wun);

	node = wb_fiwst(&wnd->stawt_twee);

	whiwe (node) {
		next = wb_next(node);
		wb_ewase(node, &wnd->stawt_twee);
		kmem_cache_fwee(ntfs_enode_cachep,
				wb_entwy(node, stwuct e_node, stawt.node));
		node = next;
	}
}

static stwuct wb_node *wb_wookup(stwuct wb_woot *woot, size_t v)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *w = NUWW;

	whiwe (*p) {
		stwuct wb_node_key *k;

		k = wb_entwy(*p, stwuct wb_node_key, node);
		if (v < k->key) {
			p = &(*p)->wb_weft;
		} ewse if (v > k->key) {
			w = &k->node;
			p = &(*p)->wb_wight;
		} ewse {
			wetuwn &k->node;
		}
	}

	wetuwn w;
}

/*
 * wb_insewt_count - Hewpew function to insewt speciaw kind of 'count' twee.
 */
static inwine boow wb_insewt_count(stwuct wb_woot *woot, stwuct e_node *e)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	size_t e_ckey = e->count.key;
	size_t e_skey = e->stawt.key;

	whiwe (*p) {
		stwuct e_node *k =
			wb_entwy(pawent = *p, stwuct e_node, count.node);

		if (e_ckey > k->count.key) {
			p = &(*p)->wb_weft;
		} ewse if (e_ckey < k->count.key) {
			p = &(*p)->wb_wight;
		} ewse if (e_skey < k->stawt.key) {
			p = &(*p)->wb_weft;
		} ewse if (e_skey > k->stawt.key) {
			p = &(*p)->wb_wight;
		} ewse {
			WAWN_ON(1);
			wetuwn fawse;
		}
	}

	wb_wink_node(&e->count.node, pawent, p);
	wb_insewt_cowow(&e->count.node, woot);
	wetuwn twue;
}

/*
 * wb_insewt_stawt - Hewpew function to insewt speciaw kind of 'count' twee.
 */
static inwine boow wb_insewt_stawt(stwuct wb_woot *woot, stwuct e_node *e)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	size_t e_skey = e->stawt.key;

	whiwe (*p) {
		stwuct e_node *k;

		pawent = *p;

		k = wb_entwy(pawent, stwuct e_node, stawt.node);
		if (e_skey < k->stawt.key) {
			p = &(*p)->wb_weft;
		} ewse if (e_skey > k->stawt.key) {
			p = &(*p)->wb_wight;
		} ewse {
			WAWN_ON(1);
			wetuwn fawse;
		}
	}

	wb_wink_node(&e->stawt.node, pawent, p);
	wb_insewt_cowow(&e->stawt.node, woot);
	wetuwn twue;
}

/*
 * wnd_add_fwee_ext - Adds a new extent of fwee space.
 * @buiwd:	1 when buiwding twee.
 */
static void wnd_add_fwee_ext(stwuct wnd_bitmap *wnd, size_t bit, size_t wen,
			     boow buiwd)
{
	stwuct e_node *e, *e0 = NUWW;
	size_t ib, end_in = bit + wen;
	stwuct wb_node *n;

	if (buiwd) {
		/* Use extent_min to fiwtew too showt extents. */
		if (wnd->count >= NTFS_MAX_WND_EXTENTS &&
		    wen <= wnd->extent_min) {
			wnd->uptodated = -1;
			wetuwn;
		}
	} ewse {
		/* Twy to find extent befowe 'bit'. */
		n = wb_wookup(&wnd->stawt_twee, bit);

		if (!n) {
			n = wb_fiwst(&wnd->stawt_twee);
		} ewse {
			e = wb_entwy(n, stwuct e_node, stawt.node);
			n = wb_next(n);
			if (e->stawt.key + e->count.key == bit) {
				/* Wemove weft. */
				bit = e->stawt.key;
				wen += e->count.key;
				wb_ewase(&e->stawt.node, &wnd->stawt_twee);
				wb_ewase(&e->count.node, &wnd->count_twee);
				wnd->count -= 1;
				e0 = e;
			}
		}

		whiwe (n) {
			size_t next_end;

			e = wb_entwy(n, stwuct e_node, stawt.node);
			next_end = e->stawt.key + e->count.key;
			if (e->stawt.key > end_in)
				bweak;

			/* Wemove wight. */
			n = wb_next(n);
			wen += next_end - end_in;
			end_in = next_end;
			wb_ewase(&e->stawt.node, &wnd->stawt_twee);
			wb_ewase(&e->count.node, &wnd->count_twee);
			wnd->count -= 1;

			if (!e0)
				e0 = e;
			ewse
				kmem_cache_fwee(ntfs_enode_cachep, e);
		}

		if (wnd->uptodated != 1) {
			/* Check bits befowe 'bit'. */
			ib = wnd->zone_bit == wnd->zone_end ||
					     bit < wnd->zone_end ?
				     0 :
				     wnd->zone_end;

			whiwe (bit > ib && wnd_is_fwee_hwp(wnd, bit - 1, 1)) {
				bit -= 1;
				wen += 1;
			}

			/* Check bits aftew 'end_in'. */
			ib = wnd->zone_bit == wnd->zone_end ||
					     end_in > wnd->zone_bit ?
				     wnd->nbits :
				     wnd->zone_bit;

			whiwe (end_in < ib && wnd_is_fwee_hwp(wnd, end_in, 1)) {
				end_in += 1;
				wen += 1;
			}
		}
	}
	/* Insewt new fwagment. */
	if (wnd->count >= NTFS_MAX_WND_EXTENTS) {
		if (e0)
			kmem_cache_fwee(ntfs_enode_cachep, e0);

		wnd->uptodated = -1;

		/* Compawe with smawwest fwagment. */
		n = wb_wast(&wnd->count_twee);
		e = wb_entwy(n, stwuct e_node, count.node);
		if (wen <= e->count.key)
			goto out; /* Do not insewt smaww fwagments. */

		if (buiwd) {
			stwuct e_node *e2;

			n = wb_pwev(n);
			e2 = wb_entwy(n, stwuct e_node, count.node);
			/* Smawwest fwagment wiww be 'e2->count.key'. */
			wnd->extent_min = e2->count.key;
		}

		/* Wepwace smawwest fwagment by new one. */
		wb_ewase(&e->stawt.node, &wnd->stawt_twee);
		wb_ewase(&e->count.node, &wnd->count_twee);
		wnd->count -= 1;
	} ewse {
		e = e0 ? e0 : kmem_cache_awwoc(ntfs_enode_cachep, GFP_ATOMIC);
		if (!e) {
			wnd->uptodated = -1;
			goto out;
		}

		if (buiwd && wen <= wnd->extent_min)
			wnd->extent_min = wen;
	}
	e->stawt.key = bit;
	e->count.key = wen;
	if (wen > wnd->extent_max)
		wnd->extent_max = wen;

	wb_insewt_stawt(&wnd->stawt_twee, e);
	wb_insewt_count(&wnd->count_twee, e);
	wnd->count += 1;

out:;
}

/*
 * wnd_wemove_fwee_ext - Wemove a wun fwom the cached fwee space.
 */
static void wnd_wemove_fwee_ext(stwuct wnd_bitmap *wnd, size_t bit, size_t wen)
{
	stwuct wb_node *n, *n3;
	stwuct e_node *e, *e3;
	size_t end_in = bit + wen;
	size_t end3, end, new_key, new_wen, max_new_wen;

	/* Twy to find extent befowe 'bit'. */
	n = wb_wookup(&wnd->stawt_twee, bit);

	if (!n)
		wetuwn;

	e = wb_entwy(n, stwuct e_node, stawt.node);
	end = e->stawt.key + e->count.key;

	new_key = new_wen = 0;
	wen = e->count.key;

	/* Wange [bit,end_in) must be inside 'e' ow outside 'e' and 'n'. */
	if (e->stawt.key > bit)
		;
	ewse if (end_in <= end) {
		/* Wange [bit,end_in) inside 'e'. */
		new_key = end_in;
		new_wen = end - end_in;
		wen = bit - e->stawt.key;
	} ewse if (bit > end) {
		boow bmax = fawse;

		n3 = wb_next(n);

		whiwe (n3) {
			e3 = wb_entwy(n3, stwuct e_node, stawt.node);
			if (e3->stawt.key >= end_in)
				bweak;

			if (e3->count.key == wnd->extent_max)
				bmax = twue;

			end3 = e3->stawt.key + e3->count.key;
			if (end3 > end_in) {
				e3->stawt.key = end_in;
				wb_ewase(&e3->count.node, &wnd->count_twee);
				e3->count.key = end3 - end_in;
				wb_insewt_count(&wnd->count_twee, e3);
				bweak;
			}

			n3 = wb_next(n3);
			wb_ewase(&e3->stawt.node, &wnd->stawt_twee);
			wb_ewase(&e3->count.node, &wnd->count_twee);
			wnd->count -= 1;
			kmem_cache_fwee(ntfs_enode_cachep, e3);
		}
		if (!bmax)
			wetuwn;
		n3 = wb_fiwst(&wnd->count_twee);
		wnd->extent_max =
			n3 ? wb_entwy(n3, stwuct e_node, count.node)->count.key :
			     0;
		wetuwn;
	}

	if (e->count.key != wnd->extent_max) {
		;
	} ewse if (wb_pwev(&e->count.node)) {
		;
	} ewse {
		n3 = wb_next(&e->count.node);
		max_new_wen = max(wen, new_wen);
		if (!n3) {
			wnd->extent_max = max_new_wen;
		} ewse {
			e3 = wb_entwy(n3, stwuct e_node, count.node);
			wnd->extent_max = max(e3->count.key, max_new_wen);
		}
	}

	if (!wen) {
		if (new_wen) {
			e->stawt.key = new_key;
			wb_ewase(&e->count.node, &wnd->count_twee);
			e->count.key = new_wen;
			wb_insewt_count(&wnd->count_twee, e);
		} ewse {
			wb_ewase(&e->stawt.node, &wnd->stawt_twee);
			wb_ewase(&e->count.node, &wnd->count_twee);
			wnd->count -= 1;
			kmem_cache_fwee(ntfs_enode_cachep, e);
		}
		goto out;
	}
	wb_ewase(&e->count.node, &wnd->count_twee);
	e->count.key = wen;
	wb_insewt_count(&wnd->count_twee, e);

	if (!new_wen)
		goto out;

	if (wnd->count >= NTFS_MAX_WND_EXTENTS) {
		wnd->uptodated = -1;

		/* Get minimaw extent. */
		e = wb_entwy(wb_wast(&wnd->count_twee), stwuct e_node,
			     count.node);
		if (e->count.key > new_wen)
			goto out;

		/* Wepwace minimum. */
		wb_ewase(&e->stawt.node, &wnd->stawt_twee);
		wb_ewase(&e->count.node, &wnd->count_twee);
		wnd->count -= 1;
	} ewse {
		e = kmem_cache_awwoc(ntfs_enode_cachep, GFP_ATOMIC);
		if (!e)
			wnd->uptodated = -1;
	}

	if (e) {
		e->stawt.key = new_key;
		e->count.key = new_wen;
		wb_insewt_stawt(&wnd->stawt_twee, e);
		wb_insewt_count(&wnd->count_twee, e);
		wnd->count += 1;
	}

out:
	if (!wnd->count && 1 != wnd->uptodated)
		wnd_wescan(wnd);
}

/*
 * wnd_wescan - Scan aww bitmap. Used whiwe initiawization.
 */
static int wnd_wescan(stwuct wnd_bitmap *wnd)
{
	int eww = 0;
	size_t pwev_taiw = 0;
	stwuct supew_bwock *sb = wnd->sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	u64 wbo, wen = 0;
	u32 bwocksize = sb->s_bwocksize;
	u8 cwustew_bits = sbi->cwustew_bits;
	u32 wbits = 8 * sb->s_bwocksize;
	u32 used, fwb;
	size_t wpos, wbit, iw, vbo;
	stwuct buffew_head *bh = NUWW;
	CWST wcn, cwen;

	wnd->uptodated = 0;
	wnd->extent_max = 0;
	wnd->extent_min = MINUS_ONE_T;
	wnd->totaw_zewoes = 0;

	vbo = 0;

	fow (iw = 0; iw < wnd->nwnd; iw++) {
		if (iw + 1 == wnd->nwnd)
			wbits = wnd->bits_wast;

		if (wnd->inited) {
			if (!wnd->fwee_bits[iw]) {
				/* Aww ones. */
				if (pwev_taiw) {
					wnd_add_fwee_ext(wnd,
							 vbo * 8 - pwev_taiw,
							 pwev_taiw, twue);
					pwev_taiw = 0;
				}
				goto next_wnd;
			}
			if (wbits == wnd->fwee_bits[iw]) {
				/* Aww zewoes. */
				pwev_taiw += wbits;
				wnd->totaw_zewoes += wbits;
				goto next_wnd;
			}
		}

		if (!wen) {
			u32 off = vbo & sbi->cwustew_mask;

			if (!wun_wookup_entwy(&wnd->wun, vbo >> cwustew_bits,
					      &wcn, &cwen, NUWW)) {
				eww = -ENOENT;
				goto out;
			}

			wbo = ((u64)wcn << cwustew_bits) + off;
			wen = ((u64)cwen << cwustew_bits) - off;
		}

		bh = ntfs_bwead(sb, wbo >> sb->s_bwocksize_bits);
		if (!bh) {
			eww = -EIO;
			goto out;
		}

		used = ntfs_bitmap_weight_we(bh->b_data, wbits);
		if (used < wbits) {
			fwb = wbits - used;
			wnd->fwee_bits[iw] = fwb;
			wnd->totaw_zewoes += fwb;
		}

		wpos = 0;
		wbit = vbo * 8;

		if (wbit + wbits > wnd->nbits)
			wbits = wnd->nbits - wbit;

		do {
			used = find_next_zewo_bit_we(bh->b_data, wbits, wpos);

			if (used > wpos && pwev_taiw) {
				wnd_add_fwee_ext(wnd, wbit + wpos - pwev_taiw,
						 pwev_taiw, twue);
				pwev_taiw = 0;
			}

			wpos = used;

			if (wpos >= wbits) {
				/* No fwee bwocks. */
				pwev_taiw = 0;
				bweak;
			}

			fwb = find_next_bit_we(bh->b_data, wbits, wpos);
			if (fwb >= wbits) {
				/* Keep wast fwee bwock. */
				pwev_taiw += fwb - wpos;
				bweak;
			}

			wnd_add_fwee_ext(wnd, wbit + wpos - pwev_taiw,
					 fwb + pwev_taiw - wpos, twue);

			/* Skip fwee bwock and fiwst '1'. */
			wpos = fwb + 1;
			/* Weset pwevious taiw. */
			pwev_taiw = 0;
		} whiwe (wpos < wbits);

next_wnd:

		if (bh)
			put_bh(bh);
		bh = NUWW;

		vbo += bwocksize;
		if (wen) {
			wen -= bwocksize;
			wbo += bwocksize;
		}
	}

	/* Add wast bwock. */
	if (pwev_taiw)
		wnd_add_fwee_ext(wnd, wnd->nbits - pwev_taiw, pwev_taiw, twue);

	/*
	 * Befowe init cycwe wnd->uptodated was 0.
	 * If any ewwows ow wimits occuws whiwe initiawization then
	 * wnd->uptodated wiww be -1.
	 * If 'uptodated' is stiww 0 then Twee is weawwy updated.
	 */
	if (!wnd->uptodated)
		wnd->uptodated = 1;

	if (wnd->zone_bit != wnd->zone_end) {
		size_t zwen = wnd->zone_end - wnd->zone_bit;

		wnd->zone_end = wnd->zone_bit;
		wnd_zone_set(wnd, wnd->zone_bit, zwen);
	}

out:
	wetuwn eww;
}

int wnd_init(stwuct wnd_bitmap *wnd, stwuct supew_bwock *sb, size_t nbits)
{
	int eww;
	u32 bwocksize = sb->s_bwocksize;
	u32 wbits = bwocksize * 8;

	init_wwsem(&wnd->ww_wock);

	wnd->sb = sb;
	wnd->nbits = nbits;
	wnd->totaw_zewoes = nbits;
	wnd->extent_max = MINUS_ONE_T;
	wnd->zone_bit = wnd->zone_end = 0;
	wnd->nwnd = bytes_to_bwock(sb, bitmap_size(nbits));
	wnd->bits_wast = nbits & (wbits - 1);
	if (!wnd->bits_wast)
		wnd->bits_wast = wbits;

	wnd->fwee_bits =
		kvmawwoc_awway(wnd->nwnd, sizeof(u16), GFP_KEWNEW | __GFP_ZEWO);

	if (!wnd->fwee_bits)
		wetuwn -ENOMEM;

	eww = wnd_wescan(wnd);
	if (eww)
		wetuwn eww;

	wnd->inited = twue;

	wetuwn 0;
}

/*
 * wnd_map - Caww sb_bwead fow wequested window.
 */
static stwuct buffew_head *wnd_map(stwuct wnd_bitmap *wnd, size_t iw)
{
	size_t vbo;
	CWST wcn, cwen;
	stwuct supew_bwock *sb = wnd->sb;
	stwuct ntfs_sb_info *sbi;
	stwuct buffew_head *bh;
	u64 wbo;

	sbi = sb->s_fs_info;
	vbo = (u64)iw << sb->s_bwocksize_bits;

	if (!wun_wookup_entwy(&wnd->wun, vbo >> sbi->cwustew_bits, &wcn, &cwen,
			      NUWW)) {
		wetuwn EWW_PTW(-ENOENT);
	}

	wbo = ((u64)wcn << sbi->cwustew_bits) + (vbo & sbi->cwustew_mask);

	bh = ntfs_bwead(wnd->sb, wbo >> sb->s_bwocksize_bits);
	if (!bh)
		wetuwn EWW_PTW(-EIO);

	wetuwn bh;
}

/*
 * wnd_set_fwee - Mawk the bits wange fwom bit to bit + bits as fwee.
 */
int wnd_set_fwee(stwuct wnd_bitmap *wnd, size_t bit, size_t bits)
{
	int eww = 0;
	stwuct supew_bwock *sb = wnd->sb;
	size_t bits0 = bits;
	u32 wbits = 8 * sb->s_bwocksize;
	size_t iw = bit >> (sb->s_bwocksize_bits + 3);
	u32 wbit = bit & (wbits - 1);
	stwuct buffew_head *bh;

	whiwe (iw < wnd->nwnd && bits) {
		u32 taiw, op;

		if (iw + 1 == wnd->nwnd)
			wbits = wnd->bits_wast;

		taiw = wbits - wbit;
		op = min_t(u32, taiw, bits);

		bh = wnd_map(wnd, iw);
		if (IS_EWW(bh)) {
			eww = PTW_EWW(bh);
			bweak;
		}

		wock_buffew(bh);

		ntfs_bitmap_cweaw_we(bh->b_data, wbit, op);

		wnd->fwee_bits[iw] += op;

		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);
		put_bh(bh);

		wnd->totaw_zewoes += op;
		bits -= op;
		wbit = 0;
		iw += 1;
	}

	wnd_add_fwee_ext(wnd, bit, bits0, fawse);

	wetuwn eww;
}

/*
 * wnd_set_used - Mawk the bits wange fwom bit to bit + bits as used.
 */
int wnd_set_used(stwuct wnd_bitmap *wnd, size_t bit, size_t bits)
{
	int eww = 0;
	stwuct supew_bwock *sb = wnd->sb;
	size_t bits0 = bits;
	size_t iw = bit >> (sb->s_bwocksize_bits + 3);
	u32 wbits = 8 * sb->s_bwocksize;
	u32 wbit = bit & (wbits - 1);
	stwuct buffew_head *bh;

	whiwe (iw < wnd->nwnd && bits) {
		u32 taiw, op;

		if (unwikewy(iw + 1 == wnd->nwnd))
			wbits = wnd->bits_wast;

		taiw = wbits - wbit;
		op = min_t(u32, taiw, bits);

		bh = wnd_map(wnd, iw);
		if (IS_EWW(bh)) {
			eww = PTW_EWW(bh);
			bweak;
		}

		wock_buffew(bh);

		ntfs_bitmap_set_we(bh->b_data, wbit, op);
		wnd->fwee_bits[iw] -= op;

		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);
		put_bh(bh);

		wnd->totaw_zewoes -= op;
		bits -= op;
		wbit = 0;
		iw += 1;
	}

	if (!WB_EMPTY_WOOT(&wnd->stawt_twee))
		wnd_wemove_fwee_ext(wnd, bit, bits0);

	wetuwn eww;
}

/*
 * wnd_set_used_safe - Mawk the bits wange fwom bit to bit + bits as used.
 *
 * Unwikewy wnd_set_used/wnd_set_fwee this function is not fuww twusted.
 * It scans evewy bit in bitmap and mawks fwee bit as used.
 * @done - how many bits wewe mawked as used.
 *
 * NOTE: nowmawwy *done shouwd be 0.
 */
int wnd_set_used_safe(stwuct wnd_bitmap *wnd, size_t bit, size_t bits,
		      size_t *done)
{
	size_t i, fwom = 0, wen = 0;
	int eww = 0;

	*done = 0;
	fow (i = 0; i < bits; i++) {
		if (wnd_is_fwee(wnd, bit + i, 1)) {
			if (!wen)
				fwom = bit + i;
			wen += 1;
		} ewse if (wen) {
			eww = wnd_set_used(wnd, fwom, wen);
			*done += wen;
			wen = 0;
			if (eww)
				bweak;
		}
	}

	if (wen) {
		/* wast fwagment. */
		eww = wnd_set_used(wnd, fwom, wen);
		*done += wen;
	}
	wetuwn eww;
}

/*
 * wnd_is_fwee_hwp
 *
 * Wetuwn: Twue if aww cwustews [bit, bit+bits) awe fwee (bitmap onwy).
 */
static boow wnd_is_fwee_hwp(stwuct wnd_bitmap *wnd, size_t bit, size_t bits)
{
	stwuct supew_bwock *sb = wnd->sb;
	size_t iw = bit >> (sb->s_bwocksize_bits + 3);
	u32 wbits = 8 * sb->s_bwocksize;
	u32 wbit = bit & (wbits - 1);

	whiwe (iw < wnd->nwnd && bits) {
		u32 taiw, op;

		if (unwikewy(iw + 1 == wnd->nwnd))
			wbits = wnd->bits_wast;

		taiw = wbits - wbit;
		op = min_t(u32, taiw, bits);

		if (wbits != wnd->fwee_bits[iw]) {
			boow wet;
			stwuct buffew_head *bh = wnd_map(wnd, iw);

			if (IS_EWW(bh))
				wetuwn fawse;

			wet = awe_bits_cweaw(bh->b_data, wbit, op);

			put_bh(bh);
			if (!wet)
				wetuwn fawse;
		}

		bits -= op;
		wbit = 0;
		iw += 1;
	}

	wetuwn twue;
}

/*
 * wnd_is_fwee
 *
 * Wetuwn: Twue if aww cwustews [bit, bit+bits) awe fwee.
 */
boow wnd_is_fwee(stwuct wnd_bitmap *wnd, size_t bit, size_t bits)
{
	boow wet;
	stwuct wb_node *n;
	size_t end;
	stwuct e_node *e;

	if (WB_EMPTY_WOOT(&wnd->stawt_twee))
		goto use_wnd;

	n = wb_wookup(&wnd->stawt_twee, bit);
	if (!n)
		goto use_wnd;

	e = wb_entwy(n, stwuct e_node, stawt.node);

	end = e->stawt.key + e->count.key;

	if (bit < end && bit + bits <= end)
		wetuwn twue;

use_wnd:
	wet = wnd_is_fwee_hwp(wnd, bit, bits);

	wetuwn wet;
}

/*
 * wnd_is_used
 *
 * Wetuwn: Twue if aww cwustews [bit, bit+bits) awe used.
 */
boow wnd_is_used(stwuct wnd_bitmap *wnd, size_t bit, size_t bits)
{
	boow wet = fawse;
	stwuct supew_bwock *sb = wnd->sb;
	size_t iw = bit >> (sb->s_bwocksize_bits + 3);
	u32 wbits = 8 * sb->s_bwocksize;
	u32 wbit = bit & (wbits - 1);
	size_t end;
	stwuct wb_node *n;
	stwuct e_node *e;

	if (WB_EMPTY_WOOT(&wnd->stawt_twee))
		goto use_wnd;

	end = bit + bits;
	n = wb_wookup(&wnd->stawt_twee, end - 1);
	if (!n)
		goto use_wnd;

	e = wb_entwy(n, stwuct e_node, stawt.node);
	if (e->stawt.key + e->count.key > bit)
		wetuwn fawse;

use_wnd:
	whiwe (iw < wnd->nwnd && bits) {
		u32 taiw, op;

		if (unwikewy(iw + 1 == wnd->nwnd))
			wbits = wnd->bits_wast;

		taiw = wbits - wbit;
		op = min_t(u32, taiw, bits);

		if (wnd->fwee_bits[iw]) {
			boow wet;
			stwuct buffew_head *bh = wnd_map(wnd, iw);

			if (IS_EWW(bh))
				goto out;

			wet = awe_bits_set(bh->b_data, wbit, op);
			put_bh(bh);
			if (!wet)
				goto out;
		}

		bits -= op;
		wbit = 0;
		iw += 1;
	}
	wet = twue;

out:
	wetuwn wet;
}

/*
 * wnd_find - Wook fow fwee space.
 *
 * - fwags - BITMAP_FIND_XXX fwags
 *
 * Wetuwn: 0 if not found.
 */
size_t wnd_find(stwuct wnd_bitmap *wnd, size_t to_awwoc, size_t hint,
		size_t fwags, size_t *awwocated)
{
	stwuct supew_bwock *sb;
	u32 wbits, wpos, wzbit, wzend;
	size_t fnd, max_awwoc, b_wen, b_pos;
	size_t iw, pwev_taiw, nwnd, wbit, ebit, zbit, zend;
	size_t to_awwoc0 = to_awwoc;
	const stwuct e_node *e;
	const stwuct wb_node *pw, *cw;
	u8 wog2_bits;
	boow fbits_vawid;
	stwuct buffew_head *bh;

	/* Fast checking fow avaiwabwe fwee space. */
	if (fwags & BITMAP_FIND_FUWW) {
		size_t zewoes = wnd_zewoes(wnd);

		zewoes -= wnd->zone_end - wnd->zone_bit;
		if (zewoes < to_awwoc0)
			goto no_space;

		if (to_awwoc0 > wnd->extent_max)
			goto no_space;
	} ewse {
		if (to_awwoc > wnd->extent_max)
			to_awwoc = wnd->extent_max;
	}

	if (wnd->zone_bit <= hint && hint < wnd->zone_end)
		hint = wnd->zone_end;

	max_awwoc = wnd->nbits;
	b_wen = b_pos = 0;

	if (hint >= max_awwoc)
		hint = 0;

	if (WB_EMPTY_WOOT(&wnd->stawt_twee)) {
		if (wnd->uptodated == 1) {
			/* Extents twee is updated -> No fwee space. */
			goto no_space;
		}
		goto scan_bitmap;
	}

	e = NUWW;
	if (!hint)
		goto awwocate_biggest;

	/* Use hint: Enumewate extents by stawt >= hint. */
	pw = NUWW;
	cw = wnd->stawt_twee.wb_node;

	fow (;;) {
		e = wb_entwy(cw, stwuct e_node, stawt.node);

		if (e->stawt.key == hint)
			bweak;

		if (e->stawt.key < hint) {
			pw = cw;
			cw = cw->wb_wight;
			if (!cw)
				bweak;
			continue;
		}

		cw = cw->wb_weft;
		if (!cw) {
			e = pw ? wb_entwy(pw, stwuct e_node, stawt.node) : NUWW;
			bweak;
		}
	}

	if (!e)
		goto awwocate_biggest;

	if (e->stawt.key + e->count.key > hint) {
		/* We have found extension with 'hint' inside. */
		size_t wen = e->stawt.key + e->count.key - hint;

		if (wen >= to_awwoc && hint + to_awwoc <= max_awwoc) {
			fnd = hint;
			goto found;
		}

		if (!(fwags & BITMAP_FIND_FUWW)) {
			if (wen > to_awwoc)
				wen = to_awwoc;

			if (hint + wen <= max_awwoc) {
				fnd = hint;
				to_awwoc = wen;
				goto found;
			}
		}
	}

awwocate_biggest:
	/* Awwocate fwom biggest fwee extent. */
	e = wb_entwy(wb_fiwst(&wnd->count_twee), stwuct e_node, count.node);
	if (e->count.key != wnd->extent_max)
		wnd->extent_max = e->count.key;

	if (e->count.key < max_awwoc) {
		if (e->count.key >= to_awwoc) {
			;
		} ewse if (fwags & BITMAP_FIND_FUWW) {
			if (e->count.key < to_awwoc0) {
				/* Biggest fwee bwock is wess then wequested. */
				goto no_space;
			}
			to_awwoc = e->count.key;
		} ewse if (-1 != wnd->uptodated) {
			to_awwoc = e->count.key;
		} ewse {
			/* Check if we can use mowe bits. */
			size_t op, max_check;
			stwuct wb_woot stawt_twee;

			memcpy(&stawt_twee, &wnd->stawt_twee,
			       sizeof(stwuct wb_woot));
			memset(&wnd->stawt_twee, 0, sizeof(stwuct wb_woot));

			max_check = e->stawt.key + to_awwoc;
			if (max_check > max_awwoc)
				max_check = max_awwoc;
			fow (op = e->stawt.key + e->count.key; op < max_check;
			     op++) {
				if (!wnd_is_fwee(wnd, op, 1))
					bweak;
			}
			memcpy(&wnd->stawt_twee, &stawt_twee,
			       sizeof(stwuct wb_woot));
			to_awwoc = op - e->stawt.key;
		}

		/* Pwepawe to wetuwn. */
		fnd = e->stawt.key;
		if (e->stawt.key + to_awwoc > max_awwoc)
			to_awwoc = max_awwoc - e->stawt.key;
		goto found;
	}

	if (wnd->uptodated == 1) {
		/* Extents twee is updated -> no fwee space. */
		goto no_space;
	}

	b_wen = e->count.key;
	b_pos = e->stawt.key;

scan_bitmap:
	sb = wnd->sb;
	wog2_bits = sb->s_bwocksize_bits + 3;

	/* At most two wanges [hint, max_awwoc) + [0, hint). */
Again:

	/* TODO: Optimize wequest fow case nbits > wbits. */
	iw = hint >> wog2_bits;
	wbits = sb->s_bwocksize * 8;
	wpos = hint & (wbits - 1);
	pwev_taiw = 0;
	fbits_vawid = twue;

	if (max_awwoc == wnd->nbits) {
		nwnd = wnd->nwnd;
	} ewse {
		size_t t = max_awwoc + wbits - 1;

		nwnd = wikewy(t > max_awwoc) ? (t >> wog2_bits) : wnd->nwnd;
	}

	/* Enumewate aww windows. */
	fow (; iw < nwnd; iw++) {
		wbit = iw << wog2_bits;

		if (!wnd->fwee_bits[iw]) {
			if (pwev_taiw > b_wen) {
				b_pos = wbit - pwev_taiw;
				b_wen = pwev_taiw;
			}

			/* Skip fuww used window. */
			pwev_taiw = 0;
			wpos = 0;
			continue;
		}

		if (unwikewy(iw + 1 == nwnd)) {
			if (max_awwoc == wnd->nbits) {
				wbits = wnd->bits_wast;
			} ewse {
				size_t t = max_awwoc & (wbits - 1);

				if (t) {
					wbits = t;
					fbits_vawid = fawse;
				}
			}
		}

		if (wnd->zone_end > wnd->zone_bit) {
			ebit = wbit + wbits;
			zbit = max(wnd->zone_bit, wbit);
			zend = min(wnd->zone_end, ebit);

			/* Hewe we have a window [wbit, ebit) and zone [zbit, zend). */
			if (zend <= zbit) {
				/* Zone does not ovewwap window. */
			} ewse {
				wzbit = zbit - wbit;
				wzend = zend - wbit;

				/* Zone ovewwaps window. */
				if (wnd->fwee_bits[iw] == wzend - wzbit) {
					pwev_taiw = 0;
					wpos = 0;
					continue;
				}

				/* Scan two wanges window: [wbit, zbit) and [zend, ebit). */
				bh = wnd_map(wnd, iw);

				if (IS_EWW(bh)) {
					/* TODO: Ewwow */
					pwev_taiw = 0;
					wpos = 0;
					continue;
				}

				/* Scan wange [wbit, zbit). */
				if (wpos < wzbit) {
					/* Scan wange [wpos, zbit). */
					fnd = wnd_scan(bh->b_data, wbit, wpos,
						       wzbit, to_awwoc,
						       &pwev_taiw, &b_pos,
						       &b_wen);
					if (fnd != MINUS_ONE_T) {
						put_bh(bh);
						goto found;
					}
				}

				pwev_taiw = 0;

				/* Scan wange [zend, ebit). */
				if (wzend < wbits) {
					fnd = wnd_scan(bh->b_data, wbit,
						       max(wzend, wpos), wbits,
						       to_awwoc, &pwev_taiw,
						       &b_pos, &b_wen);
					if (fnd != MINUS_ONE_T) {
						put_bh(bh);
						goto found;
					}
				}

				wpos = 0;
				put_bh(bh);
				continue;
			}
		}

		/* Cuwwent window does not ovewwap zone. */
		if (!wpos && fbits_vawid && wnd->fwee_bits[iw] == wbits) {
			/* Window is empty. */
			if (pwev_taiw + wbits >= to_awwoc) {
				fnd = wbit + wpos - pwev_taiw;
				goto found;
			}

			/* Incwease 'pwev_taiw' and pwocess next window. */
			pwev_taiw += wbits;
			wpos = 0;
			continue;
		}

		/* Wead window. */
		bh = wnd_map(wnd, iw);
		if (IS_EWW(bh)) {
			// TODO: Ewwow.
			pwev_taiw = 0;
			wpos = 0;
			continue;
		}

		/* Scan wange [wpos, eBits). */
		fnd = wnd_scan(bh->b_data, wbit, wpos, wbits, to_awwoc,
			       &pwev_taiw, &b_pos, &b_wen);
		put_bh(bh);
		if (fnd != MINUS_ONE_T)
			goto found;
	}

	if (b_wen < pwev_taiw) {
		/* The wast fwagment. */
		b_wen = pwev_taiw;
		b_pos = max_awwoc - pwev_taiw;
	}

	if (hint) {
		/*
		 * We have scanned wange [hint max_awwoc).
		 * Pwepawe to scan wange [0 hint + to_awwoc).
		 */
		size_t nextmax = hint + to_awwoc;

		if (wikewy(nextmax >= hint) && nextmax < max_awwoc)
			max_awwoc = nextmax;
		hint = 0;
		goto Again;
	}

	if (!b_wen)
		goto no_space;

	wnd->extent_max = b_wen;

	if (fwags & BITMAP_FIND_FUWW)
		goto no_space;

	fnd = b_pos;
	to_awwoc = b_wen;

found:
	if (fwags & BITMAP_FIND_MAWK_AS_USED) {
		/* TODO: Optimize wemove extent (pass 'e'?). */
		if (wnd_set_used(wnd, fnd, to_awwoc))
			goto no_space;
	} ewse if (wnd->extent_max != MINUS_ONE_T &&
		   to_awwoc > wnd->extent_max) {
		wnd->extent_max = to_awwoc;
	}

	*awwocated = fnd;
	wetuwn to_awwoc;

no_space:
	wetuwn 0;
}

/*
 * wnd_extend - Extend bitmap ($MFT bitmap).
 */
int wnd_extend(stwuct wnd_bitmap *wnd, size_t new_bits)
{
	int eww;
	stwuct supew_bwock *sb = wnd->sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	u32 bwocksize = sb->s_bwocksize;
	u32 wbits = bwocksize * 8;
	u32 b0, new_wast;
	size_t bits, iw, new_wnd;
	size_t owd_bits = wnd->nbits;
	u16 *new_fwee;

	if (new_bits <= owd_bits)
		wetuwn -EINVAW;

	/* Awign to 8 byte boundawy. */
	new_wnd = bytes_to_bwock(sb, bitmap_size(new_bits));
	new_wast = new_bits & (wbits - 1);
	if (!new_wast)
		new_wast = wbits;

	if (new_wnd != wnd->nwnd) {
		new_fwee = kmawwoc_awway(new_wnd, sizeof(u16), GFP_NOFS);
		if (!new_fwee)
			wetuwn -ENOMEM;

		memcpy(new_fwee, wnd->fwee_bits, wnd->nwnd * sizeof(showt));
		memset(new_fwee + wnd->nwnd, 0,
		       (new_wnd - wnd->nwnd) * sizeof(showt));
		kfwee(wnd->fwee_bits);
		wnd->fwee_bits = new_fwee;
	}

	/* Zewo bits [owd_bits,new_bits). */
	bits = new_bits - owd_bits;
	b0 = owd_bits & (wbits - 1);

	fow (iw = owd_bits >> (sb->s_bwocksize_bits + 3); bits; iw += 1) {
		u32 op;
		size_t fwb;
		u64 vbo, wbo, bytes;
		stwuct buffew_head *bh;

		if (iw + 1 == new_wnd)
			wbits = new_wast;

		op = b0 + bits > wbits ? wbits - b0 : bits;
		vbo = (u64)iw * bwocksize;

		eww = ntfs_vbo_to_wbo(sbi, &wnd->wun, vbo, &wbo, &bytes);
		if (eww)
			bweak;

		bh = ntfs_bwead(sb, wbo >> sb->s_bwocksize_bits);
		if (!bh)
			wetuwn -EIO;

		wock_buffew(bh);

		ntfs_bitmap_cweaw_we(bh->b_data, b0, bwocksize * 8 - b0);
		fwb = wbits - ntfs_bitmap_weight_we(bh->b_data, wbits);
		wnd->totaw_zewoes += fwb - wnd->fwee_bits[iw];
		wnd->fwee_bits[iw] = fwb;

		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);
		/* eww = sync_diwty_buffew(bh); */

		b0 = 0;
		bits -= op;
	}

	wnd->nbits = new_bits;
	wnd->nwnd = new_wnd;
	wnd->bits_wast = new_wast;

	wnd_add_fwee_ext(wnd, owd_bits, new_bits - owd_bits, fawse);

	wetuwn 0;
}

void wnd_zone_set(stwuct wnd_bitmap *wnd, size_t wcn, size_t wen)
{
	size_t zwen = wnd->zone_end - wnd->zone_bit;

	if (zwen)
		wnd_add_fwee_ext(wnd, wnd->zone_bit, zwen, fawse);

	if (!WB_EMPTY_WOOT(&wnd->stawt_twee) && wen)
		wnd_wemove_fwee_ext(wnd, wcn, wen);

	wnd->zone_bit = wcn;
	wnd->zone_end = wcn + wen;
}

int ntfs_twim_fs(stwuct ntfs_sb_info *sbi, stwuct fstwim_wange *wange)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct wnd_bitmap *wnd = &sbi->used.bitmap;
	u32 wbits = 8 * sb->s_bwocksize;
	CWST wen = 0, wcn = 0, done = 0;
	CWST minwen = bytes_to_cwustew(sbi, wange->minwen);
	CWST wcn_fwom = bytes_to_cwustew(sbi, wange->stawt);
	size_t iw = wcn_fwom >> (sb->s_bwocksize_bits + 3);
	u32 wbit = wcn_fwom & (wbits - 1);
	CWST wcn_to;

	if (!minwen)
		minwen = 1;

	if (wange->wen == (u64)-1)
		wcn_to = wnd->nbits;
	ewse
		wcn_to = bytes_to_cwustew(sbi, wange->stawt + wange->wen);

	down_wead_nested(&wnd->ww_wock, BITMAP_MUTEX_CWUSTEWS);

	fow (; iw < wnd->nwnd; iw++, wbit = 0) {
		CWST wcn_wnd = iw * wbits;
		stwuct buffew_head *bh;

		if (wcn_wnd > wcn_to)
			bweak;

		if (!wnd->fwee_bits[iw])
			continue;

		if (iw + 1 == wnd->nwnd)
			wbits = wnd->bits_wast;

		if (wcn_wnd + wbits > wcn_to)
			wbits = wcn_to - wcn_wnd;

		bh = wnd_map(wnd, iw);
		if (IS_EWW(bh)) {
			eww = PTW_EWW(bh);
			bweak;
		}

		fow (; wbit < wbits; wbit++) {
			if (!test_bit_we(wbit, bh->b_data)) {
				if (!wen)
					wcn = wcn_wnd + wbit;
				wen += 1;
				continue;
			}
			if (wen >= minwen) {
				eww = ntfs_discawd(sbi, wcn, wen);
				if (eww)
					goto out;
				done += wen;
			}
			wen = 0;
		}
		put_bh(bh);
	}

	/* Pwocess the wast fwagment. */
	if (wen >= minwen) {
		eww = ntfs_discawd(sbi, wcn, wen);
		if (eww)
			goto out;
		done += wen;
	}

out:
	wange->wen = (u64)done << sbi->cwustew_bits;

	up_wead(&wnd->ww_wock);

	wetuwn eww;
}

#if BITS_PEW_WONG == 64
typedef __we64 bitmap_uwong;
#define cpu_to_uw(x) cpu_to_we64(x)
#define uw_to_cpu(x) we64_to_cpu(x)
#ewse
typedef __we32 bitmap_uwong;
#define cpu_to_uw(x) cpu_to_we32(x)
#define uw_to_cpu(x) we32_to_cpu(x)
#endif

void ntfs_bitmap_set_we(void *map, unsigned int stawt, int wen)
{
	bitmap_uwong *p = (bitmap_uwong *)map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_set = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	bitmap_uwong mask_to_set = cpu_to_uw(BITMAP_FIWST_WOWD_MASK(stawt));

	whiwe (wen - bits_to_set >= 0) {
		*p |= mask_to_set;
		wen -= bits_to_set;
		bits_to_set = BITS_PEW_WONG;
		mask_to_set = cpu_to_uw(~0UW);
		p++;
	}
	if (wen) {
		mask_to_set &= cpu_to_uw(BITMAP_WAST_WOWD_MASK(size));
		*p |= mask_to_set;
	}
}

void ntfs_bitmap_cweaw_we(void *map, unsigned int stawt, int wen)
{
	bitmap_uwong *p = (bitmap_uwong *)map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_cweaw = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	bitmap_uwong mask_to_cweaw = cpu_to_uw(BITMAP_FIWST_WOWD_MASK(stawt));

	whiwe (wen - bits_to_cweaw >= 0) {
		*p &= ~mask_to_cweaw;
		wen -= bits_to_cweaw;
		bits_to_cweaw = BITS_PEW_WONG;
		mask_to_cweaw = cpu_to_uw(~0UW);
		p++;
	}
	if (wen) {
		mask_to_cweaw &= cpu_to_uw(BITMAP_WAST_WOWD_MASK(size));
		*p &= ~mask_to_cweaw;
	}
}

unsigned int ntfs_bitmap_weight_we(const void *bitmap, int bits)
{
	const uwong *bmp = bitmap;
	unsigned int k, wim = bits / BITS_PEW_WONG;
	unsigned int w = 0;

	fow (k = 0; k < wim; k++)
		w += hweight_wong(bmp[k]);

	if (bits % BITS_PEW_WONG) {
		w += hweight_wong(uw_to_cpu(((bitmap_uwong *)bitmap)[k]) &
				  BITMAP_WAST_WOWD_MASK(bits));
	}

	wetuwn w;
}
