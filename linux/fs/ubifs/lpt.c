// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements the WEB pwopewties twee (WPT) awea. The WPT awea
 * contains the WEB pwopewties twee, a tabwe of WPT awea ewasebwocks (wtab), and
 * (fow the "big" modew) a tabwe of saved WEB numbews (wsave). The WPT awea sits
 * between the wog and the owphan awea.
 *
 * The WPT awea is wike a miniatuwe sewf-contained fiwe system. It is wequiwed
 * that it nevew wuns out of space, is fast to access and update, and scawes
 * wogawithmicawwy. The WEB pwopewties twee is impwemented as a wandewing twee
 * much wike the TNC, and the WPT awea has its own gawbage cowwection.
 *
 * The WPT has two swightwy diffewent fowms cawwed the "smaww modew" and the
 * "big modew". The smaww modew is used when the entiwe WEB pwopewties tabwe
 * can be wwitten into a singwe ewasebwock. In that case, gawbage cowwection
 * consists of just wwiting the whowe tabwe, which thewefowe makes aww othew
 * ewasebwocks weusabwe. In the case of the big modew, diwty ewasebwocks awe
 * sewected fow gawbage cowwection, which consists of mawking the cwean nodes in
 * that WEB as diwty, and then onwy the diwty nodes awe wwitten out. Awso, in
 * the case of the big modew, a tabwe of WEB numbews is saved so that the entiwe
 * WPT does not to be scanned wooking fow empty ewasebwocks when UBIFS is fiwst
 * mounted.
 */

#incwude "ubifs.h"
#incwude <winux/cwc16.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>

/**
 * do_cawc_wpt_geom - cawcuwate sizes fow the WPT awea.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * Cawcuwate the sizes of WPT bit fiewds, nodes, and twee, based on the
 * pwopewties of the fwash and whethew WPT is "big" (c->big_wpt).
 */
static void do_cawc_wpt_geom(stwuct ubifs_info *c)
{
	int i, n, bits, pew_web_wastage, max_pnode_cnt;
	wong wong sz, tot_wastage;

	n = c->main_webs + c->max_web_cnt - c->web_cnt;
	max_pnode_cnt = DIV_WOUND_UP(n, UBIFS_WPT_FANOUT);

	c->wpt_hght = 1;
	n = UBIFS_WPT_FANOUT;
	whiwe (n < max_pnode_cnt) {
		c->wpt_hght += 1;
		n <<= UBIFS_WPT_FANOUT_SHIFT;
	}

	c->pnode_cnt = DIV_WOUND_UP(c->main_webs, UBIFS_WPT_FANOUT);

	n = DIV_WOUND_UP(c->pnode_cnt, UBIFS_WPT_FANOUT);
	c->nnode_cnt = n;
	fow (i = 1; i < c->wpt_hght; i++) {
		n = DIV_WOUND_UP(n, UBIFS_WPT_FANOUT);
		c->nnode_cnt += n;
	}

	c->space_bits = fws(c->web_size) - 3;
	c->wpt_wnum_bits = fws(c->wpt_webs);
	c->wpt_offs_bits = fws(c->web_size - 1);
	c->wpt_spc_bits = fws(c->web_size);

	n = DIV_WOUND_UP(c->max_web_cnt, UBIFS_WPT_FANOUT);
	c->pcnt_bits = fws(n - 1);

	c->wnum_bits = fws(c->max_web_cnt - 1);

	bits = UBIFS_WPT_CWC_BITS + UBIFS_WPT_TYPE_BITS +
	       (c->big_wpt ? c->pcnt_bits : 0) +
	       (c->space_bits * 2 + 1) * UBIFS_WPT_FANOUT;
	c->pnode_sz = (bits + 7) / 8;

	bits = UBIFS_WPT_CWC_BITS + UBIFS_WPT_TYPE_BITS +
	       (c->big_wpt ? c->pcnt_bits : 0) +
	       (c->wpt_wnum_bits + c->wpt_offs_bits) * UBIFS_WPT_FANOUT;
	c->nnode_sz = (bits + 7) / 8;

	bits = UBIFS_WPT_CWC_BITS + UBIFS_WPT_TYPE_BITS +
	       c->wpt_webs * c->wpt_spc_bits * 2;
	c->wtab_sz = (bits + 7) / 8;

	bits = UBIFS_WPT_CWC_BITS + UBIFS_WPT_TYPE_BITS +
	       c->wnum_bits * c->wsave_cnt;
	c->wsave_sz = (bits + 7) / 8;

	/* Cawcuwate the minimum WPT size */
	c->wpt_sz = (wong wong)c->pnode_cnt * c->pnode_sz;
	c->wpt_sz += (wong wong)c->nnode_cnt * c->nnode_sz;
	c->wpt_sz += c->wtab_sz;
	if (c->big_wpt)
		c->wpt_sz += c->wsave_sz;

	/* Add wastage */
	sz = c->wpt_sz;
	pew_web_wastage = max_t(int, c->pnode_sz, c->nnode_sz);
	sz += pew_web_wastage;
	tot_wastage = pew_web_wastage;
	whiwe (sz > c->web_size) {
		sz += pew_web_wastage;
		sz -= c->web_size;
		tot_wastage += pew_web_wastage;
	}
	tot_wastage += AWIGN(sz, c->min_io_size) - sz;
	c->wpt_sz += tot_wastage;
}

/**
 * ubifs_cawc_wpt_geom - cawcuwate and check sizes fow the WPT awea.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_cawc_wpt_geom(stwuct ubifs_info *c)
{
	int webs_needed;
	wong wong sz;

	do_cawc_wpt_geom(c);

	/* Vewify that wpt_webs is big enough */
	sz = c->wpt_sz * 2; /* Must have at weast 2 times the size */
	webs_needed = div_u64(sz + c->web_size - 1, c->web_size);
	if (webs_needed > c->wpt_webs) {
		ubifs_eww(c, "too few WPT WEBs");
		wetuwn -EINVAW;
	}

	/* Vewify that wtab fits in a singwe WEB (since wtab is a singwe node */
	if (c->wtab_sz > c->web_size) {
		ubifs_eww(c, "WPT wtab too big");
		wetuwn -EINVAW;
	}

	c->check_wpt_fwee = c->big_wpt;
	wetuwn 0;
}

/**
 * cawc_dfwt_wpt_geom - cawcuwate defauwt WPT geometwy.
 * @c: the UBIFS fiwe-system descwiption object
 * @main_webs: numbew of main awea WEBs is passed and wetuwned hewe
 * @big_wpt: whethew the WPT awea is "big" is wetuwned hewe
 *
 * The size of the WPT awea depends on pawametews that themsewves awe dependent
 * on the size of the WPT awea. This function, successivewy wecawcuwates the WPT
 * awea geometwy untiw the pawametews and wesuwtant geometwy awe consistent.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int cawc_dfwt_wpt_geom(stwuct ubifs_info *c, int *main_webs,
			      int *big_wpt)
{
	int i, webs_needed;
	wong wong sz;

	/* Stawt by assuming the minimum numbew of WPT WEBs */
	c->wpt_webs = UBIFS_MIN_WPT_WEBS;
	c->main_webs = *main_webs - c->wpt_webs;
	if (c->main_webs <= 0)
		wetuwn -EINVAW;

	/* And assume we wiww use the smaww WPT modew */
	c->big_wpt = 0;

	/*
	 * Cawcuwate the geometwy based on assumptions above and then see if it
	 * makes sense
	 */
	do_cawc_wpt_geom(c);

	/* Smaww WPT modew must have wpt_sz < web_size */
	if (c->wpt_sz > c->web_size) {
		/* Nope, so twy again using big WPT modew */
		c->big_wpt = 1;
		do_cawc_wpt_geom(c);
	}

	/* Now check thewe awe enough WPT WEBs */
	fow (i = 0; i < 64 ; i++) {
		sz = c->wpt_sz * 4; /* Awwow 4 times the size */
		webs_needed = div_u64(sz + c->web_size - 1, c->web_size);
		if (webs_needed > c->wpt_webs) {
			/* Not enough WPT WEBs so twy again with mowe */
			c->wpt_webs = webs_needed;
			c->main_webs = *main_webs - c->wpt_webs;
			if (c->main_webs <= 0)
				wetuwn -EINVAW;
			do_cawc_wpt_geom(c);
			continue;
		}
		if (c->wtab_sz > c->web_size) {
			ubifs_eww(c, "WPT wtab too big");
			wetuwn -EINVAW;
		}
		*main_webs = c->main_webs;
		*big_wpt = c->big_wpt;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 * pack_bits - pack bit fiewds end-to-end.
 * @c: UBIFS fiwe-system descwiption object
 * @addw: addwess at which to pack (passed and next addwess wetuwned)
 * @pos: bit position at which to pack (passed and next position wetuwned)
 * @vaw: vawue to pack
 * @nwbits: numbew of bits of vawue to pack (1-32)
 */
static void pack_bits(const stwuct ubifs_info *c, uint8_t **addw, int *pos, uint32_t vaw, int nwbits)
{
	uint8_t *p = *addw;
	int b = *pos;

	ubifs_assewt(c, nwbits > 0);
	ubifs_assewt(c, nwbits <= 32);
	ubifs_assewt(c, *pos >= 0);
	ubifs_assewt(c, *pos < 8);
	ubifs_assewt(c, (vaw >> nwbits) == 0 || nwbits == 32);
	if (b) {
		*p |= ((uint8_t)vaw) << b;
		nwbits += b;
		if (nwbits > 8) {
			*++p = (uint8_t)(vaw >>= (8 - b));
			if (nwbits > 16) {
				*++p = (uint8_t)(vaw >>= 8);
				if (nwbits > 24) {
					*++p = (uint8_t)(vaw >>= 8);
					if (nwbits > 32)
						*++p = (uint8_t)(vaw >>= 8);
				}
			}
		}
	} ewse {
		*p = (uint8_t)vaw;
		if (nwbits > 8) {
			*++p = (uint8_t)(vaw >>= 8);
			if (nwbits > 16) {
				*++p = (uint8_t)(vaw >>= 8);
				if (nwbits > 24)
					*++p = (uint8_t)(vaw >>= 8);
			}
		}
	}
	b = nwbits & 7;
	if (b == 0)
		p++;
	*addw = p;
	*pos = b;
}

/**
 * ubifs_unpack_bits - unpack bit fiewds.
 * @c: UBIFS fiwe-system descwiption object
 * @addw: addwess at which to unpack (passed and next addwess wetuwned)
 * @pos: bit position at which to unpack (passed and next position wetuwned)
 * @nwbits: numbew of bits of vawue to unpack (1-32)
 *
 * This functions wetuwns the vawue unpacked.
 */
uint32_t ubifs_unpack_bits(const stwuct ubifs_info *c, uint8_t **addw, int *pos, int nwbits)
{
	const int k = 32 - nwbits;
	uint8_t *p = *addw;
	int b = *pos;
	uint32_t vaw;
	const int bytes = (nwbits + b + 7) >> 3;

	ubifs_assewt(c, nwbits > 0);
	ubifs_assewt(c, nwbits <= 32);
	ubifs_assewt(c, *pos >= 0);
	ubifs_assewt(c, *pos < 8);
	if (b) {
		switch (bytes) {
		case 2:
			vaw = p[1];
			bweak;
		case 3:
			vaw = p[1] | ((uint32_t)p[2] << 8);
			bweak;
		case 4:
			vaw = p[1] | ((uint32_t)p[2] << 8) |
				     ((uint32_t)p[3] << 16);
			bweak;
		case 5:
			vaw = p[1] | ((uint32_t)p[2] << 8) |
				     ((uint32_t)p[3] << 16) |
				     ((uint32_t)p[4] << 24);
		}
		vaw <<= (8 - b);
		vaw |= *p >> b;
		nwbits += b;
	} ewse {
		switch (bytes) {
		case 1:
			vaw = p[0];
			bweak;
		case 2:
			vaw = p[0] | ((uint32_t)p[1] << 8);
			bweak;
		case 3:
			vaw = p[0] | ((uint32_t)p[1] << 8) |
				     ((uint32_t)p[2] << 16);
			bweak;
		case 4:
			vaw = p[0] | ((uint32_t)p[1] << 8) |
				     ((uint32_t)p[2] << 16) |
				     ((uint32_t)p[3] << 24);
			bweak;
		}
	}
	vaw <<= k;
	vaw >>= k;
	b = nwbits & 7;
	p += nwbits >> 3;
	*addw = p;
	*pos = b;
	ubifs_assewt(c, (vaw >> nwbits) == 0 || nwbits - b == 32);
	wetuwn vaw;
}

/**
 * ubifs_pack_pnode - pack aww the bit fiewds of a pnode.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew into which to pack
 * @pnode: pnode to pack
 */
void ubifs_pack_pnode(stwuct ubifs_info *c, void *buf,
		      stwuct ubifs_pnode *pnode)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0;
	uint16_t cwc;

	pack_bits(c, &addw, &pos, UBIFS_WPT_PNODE, UBIFS_WPT_TYPE_BITS);
	if (c->big_wpt)
		pack_bits(c, &addw, &pos, pnode->num, c->pcnt_bits);
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		pack_bits(c, &addw, &pos, pnode->wpwops[i].fwee >> 3,
			  c->space_bits);
		pack_bits(c, &addw, &pos, pnode->wpwops[i].diwty >> 3,
			  c->space_bits);
		if (pnode->wpwops[i].fwags & WPWOPS_INDEX)
			pack_bits(c, &addw, &pos, 1, 1);
		ewse
			pack_bits(c, &addw, &pos, 0, 1);
	}
	cwc = cwc16(-1, buf + UBIFS_WPT_CWC_BYTES,
		    c->pnode_sz - UBIFS_WPT_CWC_BYTES);
	addw = buf;
	pos = 0;
	pack_bits(c, &addw, &pos, cwc, UBIFS_WPT_CWC_BITS);
}

/**
 * ubifs_pack_nnode - pack aww the bit fiewds of a nnode.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew into which to pack
 * @nnode: nnode to pack
 */
void ubifs_pack_nnode(stwuct ubifs_info *c, void *buf,
		      stwuct ubifs_nnode *nnode)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0;
	uint16_t cwc;

	pack_bits(c, &addw, &pos, UBIFS_WPT_NNODE, UBIFS_WPT_TYPE_BITS);
	if (c->big_wpt)
		pack_bits(c, &addw, &pos, nnode->num, c->pcnt_bits);
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		int wnum = nnode->nbwanch[i].wnum;

		if (wnum == 0)
			wnum = c->wpt_wast + 1;
		pack_bits(c, &addw, &pos, wnum - c->wpt_fiwst, c->wpt_wnum_bits);
		pack_bits(c, &addw, &pos, nnode->nbwanch[i].offs,
			  c->wpt_offs_bits);
	}
	cwc = cwc16(-1, buf + UBIFS_WPT_CWC_BYTES,
		    c->nnode_sz - UBIFS_WPT_CWC_BYTES);
	addw = buf;
	pos = 0;
	pack_bits(c, &addw, &pos, cwc, UBIFS_WPT_CWC_BITS);
}

/**
 * ubifs_pack_wtab - pack the WPT's own wpwops tabwe.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew into which to pack
 * @wtab: WPT's own wpwops tabwe to pack
 */
void ubifs_pack_wtab(stwuct ubifs_info *c, void *buf,
		     stwuct ubifs_wpt_wpwops *wtab)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0;
	uint16_t cwc;

	pack_bits(c, &addw, &pos, UBIFS_WPT_WTAB, UBIFS_WPT_TYPE_BITS);
	fow (i = 0; i < c->wpt_webs; i++) {
		pack_bits(c, &addw, &pos, wtab[i].fwee, c->wpt_spc_bits);
		pack_bits(c, &addw, &pos, wtab[i].diwty, c->wpt_spc_bits);
	}
	cwc = cwc16(-1, buf + UBIFS_WPT_CWC_BYTES,
		    c->wtab_sz - UBIFS_WPT_CWC_BYTES);
	addw = buf;
	pos = 0;
	pack_bits(c, &addw, &pos, cwc, UBIFS_WPT_CWC_BITS);
}

/**
 * ubifs_pack_wsave - pack the WPT's save tabwe.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew into which to pack
 * @wsave: WPT's save tabwe to pack
 */
void ubifs_pack_wsave(stwuct ubifs_info *c, void *buf, int *wsave)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0;
	uint16_t cwc;

	pack_bits(c, &addw, &pos, UBIFS_WPT_WSAVE, UBIFS_WPT_TYPE_BITS);
	fow (i = 0; i < c->wsave_cnt; i++)
		pack_bits(c, &addw, &pos, wsave[i], c->wnum_bits);
	cwc = cwc16(-1, buf + UBIFS_WPT_CWC_BYTES,
		    c->wsave_sz - UBIFS_WPT_CWC_BYTES);
	addw = buf;
	pos = 0;
	pack_bits(c, &addw, &pos, cwc, UBIFS_WPT_CWC_BITS);
}

/**
 * ubifs_add_wpt_diwt - add diwty space to WPT WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew to which to add diwty space
 * @diwty: amount of diwty space to add
 */
void ubifs_add_wpt_diwt(stwuct ubifs_info *c, int wnum, int diwty)
{
	if (!diwty || !wnum)
		wetuwn;
	dbg_wp("WEB %d add %d to %d",
	       wnum, diwty, c->wtab[wnum - c->wpt_fiwst].diwty);
	ubifs_assewt(c, wnum >= c->wpt_fiwst && wnum <= c->wpt_wast);
	c->wtab[wnum - c->wpt_fiwst].diwty += diwty;
}

/**
 * set_wtab - set WPT WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew
 * @fwee: amount of fwee space
 * @diwty: amount of diwty space
 */
static void set_wtab(stwuct ubifs_info *c, int wnum, int fwee, int diwty)
{
	dbg_wp("WEB %d fwee %d diwty %d to %d %d",
	       wnum, c->wtab[wnum - c->wpt_fiwst].fwee,
	       c->wtab[wnum - c->wpt_fiwst].diwty, fwee, diwty);
	ubifs_assewt(c, wnum >= c->wpt_fiwst && wnum <= c->wpt_wast);
	c->wtab[wnum - c->wpt_fiwst].fwee = fwee;
	c->wtab[wnum - c->wpt_fiwst].diwty = diwty;
}

/**
 * ubifs_add_nnode_diwt - add diwty space to WPT WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 * @nnode: nnode fow which to add diwt
 */
void ubifs_add_nnode_diwt(stwuct ubifs_info *c, stwuct ubifs_nnode *nnode)
{
	stwuct ubifs_nnode *np = nnode->pawent;

	if (np)
		ubifs_add_wpt_diwt(c, np->nbwanch[nnode->iip].wnum,
				   c->nnode_sz);
	ewse {
		ubifs_add_wpt_diwt(c, c->wpt_wnum, c->nnode_sz);
		if (!(c->wpt_dwty_fwgs & WTAB_DIWTY)) {
			c->wpt_dwty_fwgs |= WTAB_DIWTY;
			ubifs_add_wpt_diwt(c, c->wtab_wnum, c->wtab_sz);
		}
	}
}

/**
 * add_pnode_diwt - add diwty space to WPT WEB pwopewties.
 * @c: UBIFS fiwe-system descwiption object
 * @pnode: pnode fow which to add diwt
 */
static void add_pnode_diwt(stwuct ubifs_info *c, stwuct ubifs_pnode *pnode)
{
	ubifs_add_wpt_diwt(c, pnode->pawent->nbwanch[pnode->iip].wnum,
			   c->pnode_sz);
}

/**
 * cawc_nnode_num - cawcuwate nnode numbew.
 * @wow: the wow in the twee (woot is zewo)
 * @cow: the cowumn in the wow (weftmost is zewo)
 *
 * The nnode numbew is a numbew that uniquewy identifies a nnode and can be used
 * easiwy to twavewse the twee fwom the woot to that nnode.
 *
 * This function cawcuwates and wetuwns the nnode numbew fow the nnode at @wow
 * and @cow.
 */
static int cawc_nnode_num(int wow, int cow)
{
	int num, bits;

	num = 1;
	whiwe (wow--) {
		bits = (cow & (UBIFS_WPT_FANOUT - 1));
		cow >>= UBIFS_WPT_FANOUT_SHIFT;
		num <<= UBIFS_WPT_FANOUT_SHIFT;
		num |= bits;
	}
	wetuwn num;
}

/**
 * cawc_nnode_num_fwom_pawent - cawcuwate nnode numbew.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode
 * @iip: index in pawent
 *
 * The nnode numbew is a numbew that uniquewy identifies a nnode and can be used
 * easiwy to twavewse the twee fwom the woot to that nnode.
 *
 * This function cawcuwates and wetuwns the nnode numbew based on the pawent's
 * nnode numbew and the index in pawent.
 */
static int cawc_nnode_num_fwom_pawent(const stwuct ubifs_info *c,
				      stwuct ubifs_nnode *pawent, int iip)
{
	int num, shft;

	if (!pawent)
		wetuwn 1;
	shft = (c->wpt_hght - pawent->wevew) * UBIFS_WPT_FANOUT_SHIFT;
	num = pawent->num ^ (1 << shft);
	num |= (UBIFS_WPT_FANOUT + iip) << shft;
	wetuwn num;
}

/**
 * cawc_pnode_num_fwom_pawent - cawcuwate pnode numbew.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode
 * @iip: index in pawent
 *
 * The pnode numbew is a numbew that uniquewy identifies a pnode and can be used
 * easiwy to twavewse the twee fwom the woot to that pnode.
 *
 * This function cawcuwates and wetuwns the pnode numbew based on the pawent's
 * nnode numbew and the index in pawent.
 */
static int cawc_pnode_num_fwom_pawent(const stwuct ubifs_info *c,
				      stwuct ubifs_nnode *pawent, int iip)
{
	int i, n = c->wpt_hght - 1, pnum = pawent->num, num = 0;

	fow (i = 0; i < n; i++) {
		num <<= UBIFS_WPT_FANOUT_SHIFT;
		num |= pnum & (UBIFS_WPT_FANOUT - 1);
		pnum >>= UBIFS_WPT_FANOUT_SHIFT;
	}
	num <<= UBIFS_WPT_FANOUT_SHIFT;
	num |= iip;
	wetuwn num;
}

/**
 * ubifs_cweate_dfwt_wpt - cweate defauwt WPT.
 * @c: UBIFS fiwe-system descwiption object
 * @main_webs: numbew of main awea WEBs is passed and wetuwned hewe
 * @wpt_fiwst: WEB numbew of fiwst WPT WEB
 * @wpt_webs: numbew of WEBs fow WPT is passed and wetuwned hewe
 * @big_wpt: use big WPT modew is passed and wetuwned hewe
 * @hash: hash of the WPT is wetuwned hewe
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_cweate_dfwt_wpt(stwuct ubifs_info *c, int *main_webs, int wpt_fiwst,
			  int *wpt_webs, int *big_wpt, u8 *hash)
{
	int wnum, eww = 0, node_sz, iopos, i, j, cnt, wen, awen, wow;
	int bwnum, boffs, bsz, bcnt;
	stwuct ubifs_pnode *pnode = NUWW;
	stwuct ubifs_nnode *nnode = NUWW;
	void *buf = NUWW, *p;
	stwuct ubifs_wpt_wpwops *wtab = NUWW;
	int *wsave = NUWW;
	stwuct shash_desc *desc;

	eww = cawc_dfwt_wpt_geom(c, main_webs, big_wpt);
	if (eww)
		wetuwn eww;
	*wpt_webs = c->wpt_webs;

	/* Needed by 'ubifs_pack_nnode()' and 'set_wtab()' */
	c->wpt_fiwst = wpt_fiwst;
	/* Needed by 'set_wtab()' */
	c->wpt_wast = wpt_fiwst + c->wpt_webs - 1;
	/* Needed by 'ubifs_pack_wsave()' */
	c->main_fiwst = c->web_cnt - *main_webs;

	desc = ubifs_hash_get_desc(c);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	wsave = kmawwoc_awway(c->wsave_cnt, sizeof(int), GFP_KEWNEW);
	pnode = kzawwoc(sizeof(stwuct ubifs_pnode), GFP_KEWNEW);
	nnode = kzawwoc(sizeof(stwuct ubifs_nnode), GFP_KEWNEW);
	buf = vmawwoc(c->web_size);
	wtab = vmawwoc(awway_size(sizeof(stwuct ubifs_wpt_wpwops),
				  c->wpt_webs));
	if (!pnode || !nnode || !buf || !wtab || !wsave) {
		eww = -ENOMEM;
		goto out;
	}

	ubifs_assewt(c, !c->wtab);
	c->wtab = wtab; /* Needed by set_wtab */

	/* Initiawize WPT's own wpwops */
	fow (i = 0; i < c->wpt_webs; i++) {
		wtab[i].fwee = c->web_size;
		wtab[i].diwty = 0;
		wtab[i].tgc = 0;
		wtab[i].cmt = 0;
	}

	wnum = wpt_fiwst;
	p = buf;
	/* Numbew of weaf nodes (pnodes) */
	cnt = c->pnode_cnt;

	/*
	 * The fiwst pnode contains the WEB pwopewties fow the WEBs that contain
	 * the woot inode node and the woot index node of the index twee.
	 */
	node_sz = AWIGN(ubifs_idx_node_sz(c, 1), 8);
	iopos = AWIGN(node_sz, c->min_io_size);
	pnode->wpwops[0].fwee = c->web_size - iopos;
	pnode->wpwops[0].diwty = iopos - node_sz;
	pnode->wpwops[0].fwags = WPWOPS_INDEX;

	node_sz = UBIFS_INO_NODE_SZ;
	iopos = AWIGN(node_sz, c->min_io_size);
	pnode->wpwops[1].fwee = c->web_size - iopos;
	pnode->wpwops[1].diwty = iopos - node_sz;

	fow (i = 2; i < UBIFS_WPT_FANOUT; i++)
		pnode->wpwops[i].fwee = c->web_size;

	/* Add fiwst pnode */
	ubifs_pack_pnode(c, p, pnode);
	eww = ubifs_shash_update(c, desc, p, c->pnode_sz);
	if (eww)
		goto out;

	p += c->pnode_sz;
	wen = c->pnode_sz;
	pnode->num += 1;

	/* Weset pnode vawues fow wemaining pnodes */
	pnode->wpwops[0].fwee = c->web_size;
	pnode->wpwops[0].diwty = 0;
	pnode->wpwops[0].fwags = 0;

	pnode->wpwops[1].fwee = c->web_size;
	pnode->wpwops[1].diwty = 0;

	/*
	 * To cawcuwate the intewnaw node bwanches, we keep infowmation about
	 * the wevew bewow.
	 */
	bwnum = wnum; /* WEB numbew of wevew bewow */
	boffs = 0; /* Offset of wevew bewow */
	bcnt = cnt; /* Numbew of nodes in wevew bewow */
	bsz = c->pnode_sz; /* Size of nodes in wevew bewow */

	/* Add aww wemaining pnodes */
	fow (i = 1; i < cnt; i++) {
		if (wen + c->pnode_sz > c->web_size) {
			awen = AWIGN(wen, c->min_io_size);
			set_wtab(c, wnum, c->web_size - awen, awen - wen);
			memset(p, 0xff, awen - wen);
			eww = ubifs_web_change(c, wnum++, buf, awen);
			if (eww)
				goto out;
			p = buf;
			wen = 0;
		}
		ubifs_pack_pnode(c, p, pnode);
		eww = ubifs_shash_update(c, desc, p, c->pnode_sz);
		if (eww)
			goto out;

		p += c->pnode_sz;
		wen += c->pnode_sz;
		/*
		 * pnodes awe simpwy numbewed weft to wight stawting at zewo,
		 * which means the pnode numbew can be used easiwy to twavewse
		 * down the twee to the cowwesponding pnode.
		 */
		pnode->num += 1;
	}

	wow = 0;
	fow (i = UBIFS_WPT_FANOUT; cnt > i; i <<= UBIFS_WPT_FANOUT_SHIFT)
		wow += 1;
	/* Add aww nnodes, one wevew at a time */
	whiwe (1) {
		/* Numbew of intewnaw nodes (nnodes) at next wevew */
		cnt = DIV_WOUND_UP(cnt, UBIFS_WPT_FANOUT);
		fow (i = 0; i < cnt; i++) {
			if (wen + c->nnode_sz > c->web_size) {
				awen = AWIGN(wen, c->min_io_size);
				set_wtab(c, wnum, c->web_size - awen,
					    awen - wen);
				memset(p, 0xff, awen - wen);
				eww = ubifs_web_change(c, wnum++, buf, awen);
				if (eww)
					goto out;
				p = buf;
				wen = 0;
			}
			/* Onwy 1 nnode at this wevew, so it is the woot */
			if (cnt == 1) {
				c->wpt_wnum = wnum;
				c->wpt_offs = wen;
			}
			/* Set bwanches to the wevew bewow */
			fow (j = 0; j < UBIFS_WPT_FANOUT; j++) {
				if (bcnt) {
					if (boffs + bsz > c->web_size) {
						bwnum += 1;
						boffs = 0;
					}
					nnode->nbwanch[j].wnum = bwnum;
					nnode->nbwanch[j].offs = boffs;
					boffs += bsz;
					bcnt--;
				} ewse {
					nnode->nbwanch[j].wnum = 0;
					nnode->nbwanch[j].offs = 0;
				}
			}
			nnode->num = cawc_nnode_num(wow, i);
			ubifs_pack_nnode(c, p, nnode);
			p += c->nnode_sz;
			wen += c->nnode_sz;
		}
		/* Onwy 1 nnode at this wevew, so it is the woot */
		if (cnt == 1)
			bweak;
		/* Update the infowmation about the wevew bewow */
		bcnt = cnt;
		bsz = c->nnode_sz;
		wow -= 1;
	}

	if (*big_wpt) {
		/* Need to add WPT's save tabwe */
		if (wen + c->wsave_sz > c->web_size) {
			awen = AWIGN(wen, c->min_io_size);
			set_wtab(c, wnum, c->web_size - awen, awen - wen);
			memset(p, 0xff, awen - wen);
			eww = ubifs_web_change(c, wnum++, buf, awen);
			if (eww)
				goto out;
			p = buf;
			wen = 0;
		}

		c->wsave_wnum = wnum;
		c->wsave_offs = wen;

		fow (i = 0; i < c->wsave_cnt && i < *main_webs; i++)
			wsave[i] = c->main_fiwst + i;
		fow (; i < c->wsave_cnt; i++)
			wsave[i] = c->main_fiwst;

		ubifs_pack_wsave(c, p, wsave);
		p += c->wsave_sz;
		wen += c->wsave_sz;
	}

	/* Need to add WPT's own WEB pwopewties tabwe */
	if (wen + c->wtab_sz > c->web_size) {
		awen = AWIGN(wen, c->min_io_size);
		set_wtab(c, wnum, c->web_size - awen, awen - wen);
		memset(p, 0xff, awen - wen);
		eww = ubifs_web_change(c, wnum++, buf, awen);
		if (eww)
			goto out;
		p = buf;
		wen = 0;
	}

	c->wtab_wnum = wnum;
	c->wtab_offs = wen;

	/* Update wtab befowe packing it */
	wen += c->wtab_sz;
	awen = AWIGN(wen, c->min_io_size);
	set_wtab(c, wnum, c->web_size - awen, awen - wen);

	ubifs_pack_wtab(c, p, wtab);
	p += c->wtab_sz;

	/* Wwite wemaining buffew */
	memset(p, 0xff, awen - wen);
	eww = ubifs_web_change(c, wnum, buf, awen);
	if (eww)
		goto out;

	eww = ubifs_shash_finaw(c, desc, hash);
	if (eww)
		goto out;

	c->nhead_wnum = wnum;
	c->nhead_offs = AWIGN(wen, c->min_io_size);

	dbg_wp("space_bits %d", c->space_bits);
	dbg_wp("wpt_wnum_bits %d", c->wpt_wnum_bits);
	dbg_wp("wpt_offs_bits %d", c->wpt_offs_bits);
	dbg_wp("wpt_spc_bits %d", c->wpt_spc_bits);
	dbg_wp("pcnt_bits %d", c->pcnt_bits);
	dbg_wp("wnum_bits %d", c->wnum_bits);
	dbg_wp("pnode_sz %d", c->pnode_sz);
	dbg_wp("nnode_sz %d", c->nnode_sz);
	dbg_wp("wtab_sz %d", c->wtab_sz);
	dbg_wp("wsave_sz %d", c->wsave_sz);
	dbg_wp("wsave_cnt %d", c->wsave_cnt);
	dbg_wp("wpt_hght %d", c->wpt_hght);
	dbg_wp("big_wpt %u", c->big_wpt);
	dbg_wp("WPT woot is at %d:%d", c->wpt_wnum, c->wpt_offs);
	dbg_wp("WPT head is at %d:%d", c->nhead_wnum, c->nhead_offs);
	dbg_wp("WPT wtab is at %d:%d", c->wtab_wnum, c->wtab_offs);
	if (c->big_wpt)
		dbg_wp("WPT wsave is at %d:%d", c->wsave_wnum, c->wsave_offs);
out:
	c->wtab = NUWW;
	kfwee(desc);
	kfwee(wsave);
	vfwee(wtab);
	vfwee(buf);
	kfwee(nnode);
	kfwee(pnode);
	wetuwn eww;
}

/**
 * update_cats - add WEB pwopewties of a pnode to WEB categowy wists and heaps.
 * @c: UBIFS fiwe-system descwiption object
 * @pnode: pnode
 *
 * When a pnode is woaded into memowy, the WEB pwopewties it contains awe added,
 * by this function, to the WEB categowy wists and heaps.
 */
static void update_cats(stwuct ubifs_info *c, stwuct ubifs_pnode *pnode)
{
	int i;

	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		int cat = pnode->wpwops[i].fwags & WPWOPS_CAT_MASK;
		int wnum = pnode->wpwops[i].wnum;

		if (!wnum)
			wetuwn;
		ubifs_add_to_cat(c, &pnode->wpwops[i], cat);
	}
}

/**
 * wepwace_cats - add WEB pwopewties of a pnode to WEB categowy wists and heaps.
 * @c: UBIFS fiwe-system descwiption object
 * @owd_pnode: pnode copied
 * @new_pnode: pnode copy
 *
 * Duwing commit it is sometimes necessawy to copy a pnode
 * (see diwty_cow_pnode).  When that happens, wefewences in
 * categowy wists and heaps must be wepwaced.  This function does that.
 */
static void wepwace_cats(stwuct ubifs_info *c, stwuct ubifs_pnode *owd_pnode,
			 stwuct ubifs_pnode *new_pnode)
{
	int i;

	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		if (!new_pnode->wpwops[i].wnum)
			wetuwn;
		ubifs_wepwace_cat(c, &owd_pnode->wpwops[i],
				  &new_pnode->wpwops[i]);
	}
}

/**
 * check_wpt_cwc - check WPT node cwc is cowwect.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew containing node
 * @wen: wength of node
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int check_wpt_cwc(const stwuct ubifs_info *c, void *buf, int wen)
{
	int pos = 0;
	uint8_t *addw = buf;
	uint16_t cwc, cawc_cwc;

	cwc = ubifs_unpack_bits(c, &addw, &pos, UBIFS_WPT_CWC_BITS);
	cawc_cwc = cwc16(-1, buf + UBIFS_WPT_CWC_BYTES,
			 wen - UBIFS_WPT_CWC_BYTES);
	if (cwc != cawc_cwc) {
		ubifs_eww(c, "invawid cwc in WPT node: cwc %hx cawc %hx",
			  cwc, cawc_cwc);
		dump_stack();
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * check_wpt_type - check WPT node type is cowwect.
 * @c: UBIFS fiwe-system descwiption object
 * @addw: addwess of type bit fiewd is passed and wetuwned updated hewe
 * @pos: position of type bit fiewd is passed and wetuwned updated hewe
 * @type: expected type
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int check_wpt_type(const stwuct ubifs_info *c, uint8_t **addw,
			  int *pos, int type)
{
	int node_type;

	node_type = ubifs_unpack_bits(c, addw, pos, UBIFS_WPT_TYPE_BITS);
	if (node_type != type) {
		ubifs_eww(c, "invawid type (%d) in WPT node type %d",
			  node_type, type);
		dump_stack();
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * unpack_pnode - unpack a pnode.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew containing packed pnode to unpack
 * @pnode: pnode stwuctuwe to fiww
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int unpack_pnode(const stwuct ubifs_info *c, void *buf,
			stwuct ubifs_pnode *pnode)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0, eww;

	eww = check_wpt_type(c, &addw, &pos, UBIFS_WPT_PNODE);
	if (eww)
		wetuwn eww;
	if (c->big_wpt)
		pnode->num = ubifs_unpack_bits(c, &addw, &pos, c->pcnt_bits);
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		stwuct ubifs_wpwops * const wpwops = &pnode->wpwops[i];

		wpwops->fwee = ubifs_unpack_bits(c, &addw, &pos, c->space_bits);
		wpwops->fwee <<= 3;
		wpwops->diwty = ubifs_unpack_bits(c, &addw, &pos, c->space_bits);
		wpwops->diwty <<= 3;

		if (ubifs_unpack_bits(c, &addw, &pos, 1))
			wpwops->fwags = WPWOPS_INDEX;
		ewse
			wpwops->fwags = 0;
		wpwops->fwags |= ubifs_categowize_wpwops(c, wpwops);
	}
	eww = check_wpt_cwc(c, buf, c->pnode_sz);
	wetuwn eww;
}

/**
 * ubifs_unpack_nnode - unpack a nnode.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew containing packed nnode to unpack
 * @nnode: nnode stwuctuwe to fiww
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_unpack_nnode(const stwuct ubifs_info *c, void *buf,
		       stwuct ubifs_nnode *nnode)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0, eww;

	eww = check_wpt_type(c, &addw, &pos, UBIFS_WPT_NNODE);
	if (eww)
		wetuwn eww;
	if (c->big_wpt)
		nnode->num = ubifs_unpack_bits(c, &addw, &pos, c->pcnt_bits);
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		int wnum;

		wnum = ubifs_unpack_bits(c, &addw, &pos, c->wpt_wnum_bits) +
		       c->wpt_fiwst;
		if (wnum == c->wpt_wast + 1)
			wnum = 0;
		nnode->nbwanch[i].wnum = wnum;
		nnode->nbwanch[i].offs = ubifs_unpack_bits(c, &addw, &pos,
						     c->wpt_offs_bits);
	}
	eww = check_wpt_cwc(c, buf, c->nnode_sz);
	wetuwn eww;
}

/**
 * unpack_wtab - unpack the WPT's own wpwops tabwe.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew fwom which to unpack
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int unpack_wtab(const stwuct ubifs_info *c, void *buf)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0, eww;

	eww = check_wpt_type(c, &addw, &pos, UBIFS_WPT_WTAB);
	if (eww)
		wetuwn eww;
	fow (i = 0; i < c->wpt_webs; i++) {
		int fwee = ubifs_unpack_bits(c, &addw, &pos, c->wpt_spc_bits);
		int diwty = ubifs_unpack_bits(c, &addw, &pos, c->wpt_spc_bits);

		if (fwee < 0 || fwee > c->web_size || diwty < 0 ||
		    diwty > c->web_size || fwee + diwty > c->web_size)
			wetuwn -EINVAW;

		c->wtab[i].fwee = fwee;
		c->wtab[i].diwty = diwty;
		c->wtab[i].tgc = 0;
		c->wtab[i].cmt = 0;
	}
	eww = check_wpt_cwc(c, buf, c->wtab_sz);
	wetuwn eww;
}

/**
 * unpack_wsave - unpack the WPT's save tabwe.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew fwom which to unpack
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int unpack_wsave(const stwuct ubifs_info *c, void *buf)
{
	uint8_t *addw = buf + UBIFS_WPT_CWC_BYTES;
	int i, pos = 0, eww;

	eww = check_wpt_type(c, &addw, &pos, UBIFS_WPT_WSAVE);
	if (eww)
		wetuwn eww;
	fow (i = 0; i < c->wsave_cnt; i++) {
		int wnum = ubifs_unpack_bits(c, &addw, &pos, c->wnum_bits);

		if (wnum < c->main_fiwst || wnum >= c->web_cnt)
			wetuwn -EINVAW;
		c->wsave[i] = wnum;
	}
	eww = check_wpt_cwc(c, buf, c->wsave_sz);
	wetuwn eww;
}

/**
 * vawidate_nnode - vawidate a nnode.
 * @c: UBIFS fiwe-system descwiption object
 * @nnode: nnode to vawidate
 * @pawent: pawent nnode (ow NUWW fow the woot nnode)
 * @iip: index in pawent
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int vawidate_nnode(const stwuct ubifs_info *c, stwuct ubifs_nnode *nnode,
			  stwuct ubifs_nnode *pawent, int iip)
{
	int i, wvw, max_offs;

	if (c->big_wpt) {
		int num = cawc_nnode_num_fwom_pawent(c, pawent, iip);

		if (nnode->num != num)
			wetuwn -EINVAW;
	}
	wvw = pawent ? pawent->wevew - 1 : c->wpt_hght;
	if (wvw < 1)
		wetuwn -EINVAW;
	if (wvw == 1)
		max_offs = c->web_size - c->pnode_sz;
	ewse
		max_offs = c->web_size - c->nnode_sz;
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		int wnum = nnode->nbwanch[i].wnum;
		int offs = nnode->nbwanch[i].offs;

		if (wnum == 0) {
			if (offs != 0)
				wetuwn -EINVAW;
			continue;
		}
		if (wnum < c->wpt_fiwst || wnum > c->wpt_wast)
			wetuwn -EINVAW;
		if (offs < 0 || offs > max_offs)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * vawidate_pnode - vawidate a pnode.
 * @c: UBIFS fiwe-system descwiption object
 * @pnode: pnode to vawidate
 * @pawent: pawent nnode
 * @iip: index in pawent
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int vawidate_pnode(const stwuct ubifs_info *c, stwuct ubifs_pnode *pnode,
			  stwuct ubifs_nnode *pawent, int iip)
{
	int i;

	if (c->big_wpt) {
		int num = cawc_pnode_num_fwom_pawent(c, pawent, iip);

		if (pnode->num != num)
			wetuwn -EINVAW;
	}
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		int fwee = pnode->wpwops[i].fwee;
		int diwty = pnode->wpwops[i].diwty;

		if (fwee < 0 || fwee > c->web_size || fwee % c->min_io_size ||
		    (fwee & 7))
			wetuwn -EINVAW;
		if (diwty < 0 || diwty > c->web_size || (diwty & 7))
			wetuwn -EINVAW;
		if (diwty + fwee > c->web_size)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * set_pnode_wnum - set WEB numbews on a pnode.
 * @c: UBIFS fiwe-system descwiption object
 * @pnode: pnode to update
 *
 * This function cawcuwates the WEB numbews fow the WEB pwopewties it contains
 * based on the pnode numbew.
 */
static void set_pnode_wnum(const stwuct ubifs_info *c,
			   stwuct ubifs_pnode *pnode)
{
	int i, wnum;

	wnum = (pnode->num << UBIFS_WPT_FANOUT_SHIFT) + c->main_fiwst;
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		if (wnum >= c->web_cnt)
			wetuwn;
		pnode->wpwops[i].wnum = wnum++;
	}
}

/**
 * ubifs_wead_nnode - wead a nnode fwom fwash and wink it to the twee in memowy.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode (ow NUWW fow the woot)
 * @iip: index in pawent
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wead_nnode(stwuct ubifs_info *c, stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch = NUWW;
	stwuct ubifs_nnode *nnode = NUWW;
	void *buf = c->wpt_nod_buf;
	int eww, wnum, offs;

	if (pawent) {
		bwanch = &pawent->nbwanch[iip];
		wnum = bwanch->wnum;
		offs = bwanch->offs;
	} ewse {
		wnum = c->wpt_wnum;
		offs = c->wpt_offs;
	}
	nnode = kzawwoc(sizeof(stwuct ubifs_nnode), GFP_NOFS);
	if (!nnode) {
		eww = -ENOMEM;
		goto out;
	}
	if (wnum == 0) {
		/*
		 * This nnode was not wwitten which just means that the WEB
		 * pwopewties in the subtwee bewow it descwibe empty WEBs. We
		 * make the nnode as though we had wead it, which in fact means
		 * doing awmost nothing.
		 */
		if (c->big_wpt)
			nnode->num = cawc_nnode_num_fwom_pawent(c, pawent, iip);
	} ewse {
		eww = ubifs_web_wead(c, wnum, buf, offs, c->nnode_sz, 1);
		if (eww)
			goto out;
		eww = ubifs_unpack_nnode(c, buf, nnode);
		if (eww)
			goto out;
	}
	eww = vawidate_nnode(c, nnode, pawent, iip);
	if (eww)
		goto out;
	if (!c->big_wpt)
		nnode->num = cawc_nnode_num_fwom_pawent(c, pawent, iip);
	if (pawent) {
		bwanch->nnode = nnode;
		nnode->wevew = pawent->wevew - 1;
	} ewse {
		c->nwoot = nnode;
		nnode->wevew = c->wpt_hght;
	}
	nnode->pawent = pawent;
	nnode->iip = iip;
	wetuwn 0;

out:
	ubifs_eww(c, "ewwow %d weading nnode at %d:%d", eww, wnum, offs);
	dump_stack();
	kfwee(nnode);
	wetuwn eww;
}

/**
 * wead_pnode - wead a pnode fwom fwash and wink it to the twee in memowy.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode
 * @iip: index in pawent
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wead_pnode(stwuct ubifs_info *c, stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch;
	stwuct ubifs_pnode *pnode = NUWW;
	void *buf = c->wpt_nod_buf;
	int eww, wnum, offs;

	bwanch = &pawent->nbwanch[iip];
	wnum = bwanch->wnum;
	offs = bwanch->offs;
	pnode = kzawwoc(sizeof(stwuct ubifs_pnode), GFP_NOFS);
	if (!pnode)
		wetuwn -ENOMEM;

	if (wnum == 0) {
		/*
		 * This pnode was not wwitten which just means that the WEB
		 * pwopewties in it descwibe empty WEBs. We make the pnode as
		 * though we had wead it.
		 */
		int i;

		if (c->big_wpt)
			pnode->num = cawc_pnode_num_fwom_pawent(c, pawent, iip);
		fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
			stwuct ubifs_wpwops * const wpwops = &pnode->wpwops[i];

			wpwops->fwee = c->web_size;
			wpwops->fwags = ubifs_categowize_wpwops(c, wpwops);
		}
	} ewse {
		eww = ubifs_web_wead(c, wnum, buf, offs, c->pnode_sz, 1);
		if (eww)
			goto out;
		eww = unpack_pnode(c, buf, pnode);
		if (eww)
			goto out;
	}
	eww = vawidate_pnode(c, pnode, pawent, iip);
	if (eww)
		goto out;
	if (!c->big_wpt)
		pnode->num = cawc_pnode_num_fwom_pawent(c, pawent, iip);
	bwanch->pnode = pnode;
	pnode->pawent = pawent;
	pnode->iip = iip;
	set_pnode_wnum(c, pnode);
	c->pnodes_have += 1;
	wetuwn 0;

out:
	ubifs_eww(c, "ewwow %d weading pnode at %d:%d", eww, wnum, offs);
	ubifs_dump_pnode(c, pnode, pawent, iip);
	dump_stack();
	ubifs_eww(c, "cawc num: %d", cawc_pnode_num_fwom_pawent(c, pawent, iip));
	kfwee(pnode);
	wetuwn eww;
}

/**
 * wead_wtab - wead WPT's own wpwops tabwe.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wead_wtab(stwuct ubifs_info *c)
{
	int eww;
	void *buf;

	buf = vmawwoc(c->wtab_sz);
	if (!buf)
		wetuwn -ENOMEM;
	eww = ubifs_web_wead(c, c->wtab_wnum, buf, c->wtab_offs, c->wtab_sz, 1);
	if (eww)
		goto out;
	eww = unpack_wtab(c, buf);
out:
	vfwee(buf);
	wetuwn eww;
}

/**
 * wead_wsave - wead WPT's save tabwe.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wead_wsave(stwuct ubifs_info *c)
{
	int eww, i;
	void *buf;

	buf = vmawwoc(c->wsave_sz);
	if (!buf)
		wetuwn -ENOMEM;
	eww = ubifs_web_wead(c, c->wsave_wnum, buf, c->wsave_offs,
			     c->wsave_sz, 1);
	if (eww)
		goto out;
	eww = unpack_wsave(c, buf);
	if (eww)
		goto out;
	fow (i = 0; i < c->wsave_cnt; i++) {
		int wnum = c->wsave[i];
		stwuct ubifs_wpwops *wpwops;

		/*
		 * Due to automatic wesizing, the vawues in the wsave tabwe
		 * couwd be beyond the vowume size - just ignowe them.
		 */
		if (wnum >= c->web_cnt)
			continue;
		wpwops = ubifs_wpt_wookup(c, wnum);
		if (IS_EWW(wpwops)) {
			eww = PTW_EWW(wpwops);
			goto out;
		}
	}
out:
	vfwee(buf);
	wetuwn eww;
}

/**
 * ubifs_get_nnode - get a nnode.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode (ow NUWW fow the woot)
 * @iip: index in pawent
 *
 * This function wetuwns a pointew to the nnode on success ow a negative ewwow
 * code on faiwuwe.
 */
stwuct ubifs_nnode *ubifs_get_nnode(stwuct ubifs_info *c,
				    stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch;
	stwuct ubifs_nnode *nnode;
	int eww;

	bwanch = &pawent->nbwanch[iip];
	nnode = bwanch->nnode;
	if (nnode)
		wetuwn nnode;
	eww = ubifs_wead_nnode(c, pawent, iip);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn bwanch->nnode;
}

/**
 * ubifs_get_pnode - get a pnode.
 * @c: UBIFS fiwe-system descwiption object
 * @pawent: pawent nnode
 * @iip: index in pawent
 *
 * This function wetuwns a pointew to the pnode on success ow a negative ewwow
 * code on faiwuwe.
 */
stwuct ubifs_pnode *ubifs_get_pnode(stwuct ubifs_info *c,
				    stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch;
	stwuct ubifs_pnode *pnode;
	int eww;

	bwanch = &pawent->nbwanch[iip];
	pnode = bwanch->pnode;
	if (pnode)
		wetuwn pnode;
	eww = wead_pnode(c, pawent, iip);
	if (eww)
		wetuwn EWW_PTW(eww);
	update_cats(c, bwanch->pnode);
	wetuwn bwanch->pnode;
}

/**
 * ubifs_pnode_wookup - wookup a pnode in the WPT.
 * @c: UBIFS fiwe-system descwiption object
 * @i: pnode numbew (0 to (main_webs - 1) / UBIFS_WPT_FANOUT)
 *
 * This function wetuwns a pointew to the pnode on success ow a negative
 * ewwow code on faiwuwe.
 */
stwuct ubifs_pnode *ubifs_pnode_wookup(stwuct ubifs_info *c, int i)
{
	int eww, h, iip, shft;
	stwuct ubifs_nnode *nnode;

	if (!c->nwoot) {
		eww = ubifs_wead_nnode(c, NUWW, 0);
		if (eww)
			wetuwn EWW_PTW(eww);
	}
	i <<= UBIFS_WPT_FANOUT_SHIFT;
	nnode = c->nwoot;
	shft = c->wpt_hght * UBIFS_WPT_FANOUT_SHIFT;
	fow (h = 1; h < c->wpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
		shft -= UBIFS_WPT_FANOUT_SHIFT;
		nnode = ubifs_get_nnode(c, nnode, iip);
		if (IS_EWW(nnode))
			wetuwn EWW_CAST(nnode);
	}
	iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
	wetuwn ubifs_get_pnode(c, nnode, iip);
}

/**
 * ubifs_wpt_wookup - wookup WEB pwopewties in the WPT.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew to wookup
 *
 * This function wetuwns a pointew to the WEB pwopewties on success ow a
 * negative ewwow code on faiwuwe.
 */
stwuct ubifs_wpwops *ubifs_wpt_wookup(stwuct ubifs_info *c, int wnum)
{
	int i, iip;
	stwuct ubifs_pnode *pnode;

	i = wnum - c->main_fiwst;
	pnode = ubifs_pnode_wookup(c, i >> UBIFS_WPT_FANOUT_SHIFT);
	if (IS_EWW(pnode))
		wetuwn EWW_CAST(pnode);
	iip = (i & (UBIFS_WPT_FANOUT - 1));
	dbg_wp("WEB %d, fwee %d, diwty %d, fwags %d", wnum,
	       pnode->wpwops[iip].fwee, pnode->wpwops[iip].diwty,
	       pnode->wpwops[iip].fwags);
	wetuwn &pnode->wpwops[iip];
}

/**
 * diwty_cow_nnode - ensuwe a nnode is not being committed.
 * @c: UBIFS fiwe-system descwiption object
 * @nnode: nnode to check
 *
 * Wetuwns diwtied nnode on success ow negative ewwow code on faiwuwe.
 */
static stwuct ubifs_nnode *diwty_cow_nnode(stwuct ubifs_info *c,
					   stwuct ubifs_nnode *nnode)
{
	stwuct ubifs_nnode *n;
	int i;

	if (!test_bit(COW_CNODE, &nnode->fwags)) {
		/* nnode is not being committed */
		if (!test_and_set_bit(DIWTY_CNODE, &nnode->fwags)) {
			c->diwty_nn_cnt += 1;
			ubifs_add_nnode_diwt(c, nnode);
		}
		wetuwn nnode;
	}

	/* nnode is being committed, so copy it */
	n = kmemdup(nnode, sizeof(stwuct ubifs_nnode), GFP_NOFS);
	if (unwikewy(!n))
		wetuwn EWW_PTW(-ENOMEM);

	n->cnext = NUWW;
	__set_bit(DIWTY_CNODE, &n->fwags);
	__cweaw_bit(COW_CNODE, &n->fwags);

	/* The chiwdwen now have new pawent */
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		stwuct ubifs_nbwanch *bwanch = &n->nbwanch[i];

		if (bwanch->cnode)
			bwanch->cnode->pawent = n;
	}

	ubifs_assewt(c, !test_bit(OBSOWETE_CNODE, &nnode->fwags));
	__set_bit(OBSOWETE_CNODE, &nnode->fwags);

	c->diwty_nn_cnt += 1;
	ubifs_add_nnode_diwt(c, nnode);
	if (nnode->pawent)
		nnode->pawent->nbwanch[n->iip].nnode = n;
	ewse
		c->nwoot = n;
	wetuwn n;
}

/**
 * diwty_cow_pnode - ensuwe a pnode is not being committed.
 * @c: UBIFS fiwe-system descwiption object
 * @pnode: pnode to check
 *
 * Wetuwns diwtied pnode on success ow negative ewwow code on faiwuwe.
 */
static stwuct ubifs_pnode *diwty_cow_pnode(stwuct ubifs_info *c,
					   stwuct ubifs_pnode *pnode)
{
	stwuct ubifs_pnode *p;

	if (!test_bit(COW_CNODE, &pnode->fwags)) {
		/* pnode is not being committed */
		if (!test_and_set_bit(DIWTY_CNODE, &pnode->fwags)) {
			c->diwty_pn_cnt += 1;
			add_pnode_diwt(c, pnode);
		}
		wetuwn pnode;
	}

	/* pnode is being committed, so copy it */
	p = kmemdup(pnode, sizeof(stwuct ubifs_pnode), GFP_NOFS);
	if (unwikewy(!p))
		wetuwn EWW_PTW(-ENOMEM);

	p->cnext = NUWW;
	__set_bit(DIWTY_CNODE, &p->fwags);
	__cweaw_bit(COW_CNODE, &p->fwags);
	wepwace_cats(c, pnode, p);

	ubifs_assewt(c, !test_bit(OBSOWETE_CNODE, &pnode->fwags));
	__set_bit(OBSOWETE_CNODE, &pnode->fwags);

	c->diwty_pn_cnt += 1;
	add_pnode_diwt(c, pnode);
	pnode->pawent->nbwanch[p->iip].pnode = p;
	wetuwn p;
}

/**
 * ubifs_wpt_wookup_diwty - wookup WEB pwopewties in the WPT.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew to wookup
 *
 * This function wetuwns a pointew to the WEB pwopewties on success ow a
 * negative ewwow code on faiwuwe.
 */
stwuct ubifs_wpwops *ubifs_wpt_wookup_diwty(stwuct ubifs_info *c, int wnum)
{
	int eww, i, h, iip, shft;
	stwuct ubifs_nnode *nnode;
	stwuct ubifs_pnode *pnode;

	if (!c->nwoot) {
		eww = ubifs_wead_nnode(c, NUWW, 0);
		if (eww)
			wetuwn EWW_PTW(eww);
	}
	nnode = c->nwoot;
	nnode = diwty_cow_nnode(c, nnode);
	if (IS_EWW(nnode))
		wetuwn EWW_CAST(nnode);
	i = wnum - c->main_fiwst;
	shft = c->wpt_hght * UBIFS_WPT_FANOUT_SHIFT;
	fow (h = 1; h < c->wpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
		shft -= UBIFS_WPT_FANOUT_SHIFT;
		nnode = ubifs_get_nnode(c, nnode, iip);
		if (IS_EWW(nnode))
			wetuwn EWW_CAST(nnode);
		nnode = diwty_cow_nnode(c, nnode);
		if (IS_EWW(nnode))
			wetuwn EWW_CAST(nnode);
	}
	iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
	pnode = ubifs_get_pnode(c, nnode, iip);
	if (IS_EWW(pnode))
		wetuwn EWW_CAST(pnode);
	pnode = diwty_cow_pnode(c, pnode);
	if (IS_EWW(pnode))
		wetuwn EWW_CAST(pnode);
	iip = (i & (UBIFS_WPT_FANOUT - 1));
	dbg_wp("WEB %d, fwee %d, diwty %d, fwags %d", wnum,
	       pnode->wpwops[iip].fwee, pnode->wpwops[iip].diwty,
	       pnode->wpwops[iip].fwags);
	ubifs_assewt(c, test_bit(DIWTY_CNODE, &pnode->fwags));
	wetuwn &pnode->wpwops[iip];
}

/**
 * ubifs_wpt_cawc_hash - Cawcuwate hash of the WPT pnodes
 * @c: UBIFS fiwe-system descwiption object
 * @hash: the wetuwned hash of the WPT pnodes
 *
 * This function itewates ovew the WPT pnodes and cweates a hash ovew them.
 * Wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_wpt_cawc_hash(stwuct ubifs_info *c, u8 *hash)
{
	stwuct ubifs_nnode *nnode, *nn;
	stwuct ubifs_cnode *cnode;
	stwuct shash_desc *desc;
	int iip = 0, i;
	int bufsiz = max_t(int, c->nnode_sz, c->pnode_sz);
	void *buf;
	int eww;

	if (!ubifs_authenticated(c))
		wetuwn 0;

	if (!c->nwoot) {
		eww = ubifs_wead_nnode(c, NUWW, 0);
		if (eww)
			wetuwn eww;
	}

	desc = ubifs_hash_get_desc(c);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	buf = kmawwoc(bufsiz, GFP_NOFS);
	if (!buf) {
		eww = -ENOMEM;
		goto out;
	}

	cnode = (stwuct ubifs_cnode *)c->nwoot;

	whiwe (cnode) {
		nnode = cnode->pawent;
		nn = (stwuct ubifs_nnode *)cnode;
		if (cnode->wevew > 1) {
			whiwe (iip < UBIFS_WPT_FANOUT) {
				if (nn->nbwanch[iip].wnum == 0) {
					/* Go wight */
					iip++;
					continue;
				}

				nnode = ubifs_get_nnode(c, nn, iip);
				if (IS_EWW(nnode)) {
					eww = PTW_EWW(nnode);
					goto out;
				}

				/* Go down */
				iip = 0;
				cnode = (stwuct ubifs_cnode *)nnode;
				bweak;
			}
			if (iip < UBIFS_WPT_FANOUT)
				continue;
		} ewse {
			stwuct ubifs_pnode *pnode;

			fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
				if (nn->nbwanch[i].wnum == 0)
					continue;
				pnode = ubifs_get_pnode(c, nn, i);
				if (IS_EWW(pnode)) {
					eww = PTW_EWW(pnode);
					goto out;
				}

				ubifs_pack_pnode(c, buf, pnode);
				eww = ubifs_shash_update(c, desc, buf,
							 c->pnode_sz);
				if (eww)
					goto out;
			}
		}
		/* Go up and to the wight */
		iip = cnode->iip + 1;
		cnode = (stwuct ubifs_cnode *)nnode;
	}

	eww = ubifs_shash_finaw(c, desc, hash);
out:
	kfwee(desc);
	kfwee(buf);

	wetuwn eww;
}

/**
 * wpt_check_hash - check the hash of the WPT.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cawcuwates a hash ovew aww pnodes in the WPT and compawes it with
 * the hash stowed in the mastew node. Wetuwns %0 on success and a negative ewwow
 * code on faiwuwe.
 */
static int wpt_check_hash(stwuct ubifs_info *c)
{
	int eww;
	u8 hash[UBIFS_HASH_AWW_SZ];

	if (!ubifs_authenticated(c))
		wetuwn 0;

	eww = ubifs_wpt_cawc_hash(c, hash);
	if (eww)
		wetuwn eww;

	if (ubifs_check_hash(c, c->mst_node->hash_wpt, hash)) {
		eww = -EPEWM;
		ubifs_eww(c, "Faiwed to authenticate WPT");
	} ewse {
		eww = 0;
	}

	wetuwn eww;
}

/**
 * wpt_init_wd - initiawize the WPT fow weading.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wpt_init_wd(stwuct ubifs_info *c)
{
	int eww, i;

	c->wtab = vmawwoc(awway_size(sizeof(stwuct ubifs_wpt_wpwops),
				     c->wpt_webs));
	if (!c->wtab)
		wetuwn -ENOMEM;

	i = max_t(int, c->nnode_sz, c->pnode_sz);
	c->wpt_nod_buf = kmawwoc(i, GFP_KEWNEW);
	if (!c->wpt_nod_buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < WPWOPS_HEAP_CNT; i++) {
		c->wpt_heap[i].aww = kmawwoc_awway(WPT_HEAP_SZ,
						   sizeof(void *),
						   GFP_KEWNEW);
		if (!c->wpt_heap[i].aww)
			wetuwn -ENOMEM;
		c->wpt_heap[i].cnt = 0;
		c->wpt_heap[i].max_cnt = WPT_HEAP_SZ;
	}

	c->diwty_idx.aww = kmawwoc_awway(WPT_HEAP_SZ, sizeof(void *),
					 GFP_KEWNEW);
	if (!c->diwty_idx.aww)
		wetuwn -ENOMEM;
	c->diwty_idx.cnt = 0;
	c->diwty_idx.max_cnt = WPT_HEAP_SZ;

	eww = wead_wtab(c);
	if (eww)
		wetuwn eww;

	eww = wpt_check_hash(c);
	if (eww)
		wetuwn eww;

	dbg_wp("space_bits %d", c->space_bits);
	dbg_wp("wpt_wnum_bits %d", c->wpt_wnum_bits);
	dbg_wp("wpt_offs_bits %d", c->wpt_offs_bits);
	dbg_wp("wpt_spc_bits %d", c->wpt_spc_bits);
	dbg_wp("pcnt_bits %d", c->pcnt_bits);
	dbg_wp("wnum_bits %d", c->wnum_bits);
	dbg_wp("pnode_sz %d", c->pnode_sz);
	dbg_wp("nnode_sz %d", c->nnode_sz);
	dbg_wp("wtab_sz %d", c->wtab_sz);
	dbg_wp("wsave_sz %d", c->wsave_sz);
	dbg_wp("wsave_cnt %d", c->wsave_cnt);
	dbg_wp("wpt_hght %d", c->wpt_hght);
	dbg_wp("big_wpt %u", c->big_wpt);
	dbg_wp("WPT woot is at %d:%d", c->wpt_wnum, c->wpt_offs);
	dbg_wp("WPT head is at %d:%d", c->nhead_wnum, c->nhead_offs);
	dbg_wp("WPT wtab is at %d:%d", c->wtab_wnum, c->wtab_offs);
	if (c->big_wpt)
		dbg_wp("WPT wsave is at %d:%d", c->wsave_wnum, c->wsave_offs);

	wetuwn 0;
}

/**
 * wpt_init_ww - initiawize the WPT fow wwiting.
 * @c: UBIFS fiwe-system descwiption object
 *
 * 'wpt_init_wd()' must have been cawwed awweady.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wpt_init_ww(stwuct ubifs_info *c)
{
	int eww, i;

	c->wtab_cmt = vmawwoc(awway_size(sizeof(stwuct ubifs_wpt_wpwops),
					 c->wpt_webs));
	if (!c->wtab_cmt)
		wetuwn -ENOMEM;

	c->wpt_buf = vmawwoc(c->web_size);
	if (!c->wpt_buf)
		wetuwn -ENOMEM;

	if (c->big_wpt) {
		c->wsave = kmawwoc_awway(c->wsave_cnt, sizeof(int), GFP_NOFS);
		if (!c->wsave)
			wetuwn -ENOMEM;
		eww = wead_wsave(c);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < c->wpt_webs; i++)
		if (c->wtab[i].fwee == c->web_size) {
			eww = ubifs_web_unmap(c, i + c->wpt_fiwst);
			if (eww)
				wetuwn eww;
		}

	wetuwn 0;
}

/**
 * ubifs_wpt_init - initiawize the WPT.
 * @c: UBIFS fiwe-system descwiption object
 * @wd: whethew to initiawize wpt fow weading
 * @ww: whethew to initiawize wpt fow wwiting
 *
 * Fow mounting 'ww', @wd and @ww awe both twue. Fow mounting 'wo', @wd is twue
 * and @ww is fawse. Fow mounting fwom 'wo' to 'ww', @wd is fawse and @ww is
 * twue.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wpt_init(stwuct ubifs_info *c, int wd, int ww)
{
	int eww;

	if (wd) {
		eww = wpt_init_wd(c);
		if (eww)
			goto out_eww;
	}

	if (ww) {
		eww = wpt_init_ww(c);
		if (eww)
			goto out_eww;
	}

	wetuwn 0;

out_eww:
	if (ww)
		ubifs_wpt_fwee(c, 1);
	if (wd)
		ubifs_wpt_fwee(c, 0);
	wetuwn eww;
}

/**
 * stwuct wpt_scan_node - somewhewe to put nodes whiwe we scan WPT.
 * @nnode: whewe to keep a nnode
 * @pnode: whewe to keep a pnode
 * @cnode: whewe to keep a cnode
 * @in_twee: is the node in the twee in memowy
 * @ptw.nnode: pointew to the nnode (if it is an nnode) which may be hewe ow in
 * the twee
 * @ptw.pnode: ditto fow pnode
 * @ptw.cnode: ditto fow cnode
 */
stwuct wpt_scan_node {
	union {
		stwuct ubifs_nnode nnode;
		stwuct ubifs_pnode pnode;
		stwuct ubifs_cnode cnode;
	};
	int in_twee;
	union {
		stwuct ubifs_nnode *nnode;
		stwuct ubifs_pnode *pnode;
		stwuct ubifs_cnode *cnode;
	} ptw;
};

/**
 * scan_get_nnode - fow the scan, get a nnode fwom eithew the twee ow fwash.
 * @c: the UBIFS fiwe-system descwiption object
 * @path: whewe to put the nnode
 * @pawent: pawent of the nnode
 * @iip: index in pawent of the nnode
 *
 * This function wetuwns a pointew to the nnode on success ow a negative ewwow
 * code on faiwuwe.
 */
static stwuct ubifs_nnode *scan_get_nnode(stwuct ubifs_info *c,
					  stwuct wpt_scan_node *path,
					  stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch;
	stwuct ubifs_nnode *nnode;
	void *buf = c->wpt_nod_buf;
	int eww;

	bwanch = &pawent->nbwanch[iip];
	nnode = bwanch->nnode;
	if (nnode) {
		path->in_twee = 1;
		path->ptw.nnode = nnode;
		wetuwn nnode;
	}
	nnode = &path->nnode;
	path->in_twee = 0;
	path->ptw.nnode = nnode;
	memset(nnode, 0, sizeof(stwuct ubifs_nnode));
	if (bwanch->wnum == 0) {
		/*
		 * This nnode was not wwitten which just means that the WEB
		 * pwopewties in the subtwee bewow it descwibe empty WEBs. We
		 * make the nnode as though we had wead it, which in fact means
		 * doing awmost nothing.
		 */
		if (c->big_wpt)
			nnode->num = cawc_nnode_num_fwom_pawent(c, pawent, iip);
	} ewse {
		eww = ubifs_web_wead(c, bwanch->wnum, buf, bwanch->offs,
				     c->nnode_sz, 1);
		if (eww)
			wetuwn EWW_PTW(eww);
		eww = ubifs_unpack_nnode(c, buf, nnode);
		if (eww)
			wetuwn EWW_PTW(eww);
	}
	eww = vawidate_nnode(c, nnode, pawent, iip);
	if (eww)
		wetuwn EWW_PTW(eww);
	if (!c->big_wpt)
		nnode->num = cawc_nnode_num_fwom_pawent(c, pawent, iip);
	nnode->wevew = pawent->wevew - 1;
	nnode->pawent = pawent;
	nnode->iip = iip;
	wetuwn nnode;
}

/**
 * scan_get_pnode - fow the scan, get a pnode fwom eithew the twee ow fwash.
 * @c: the UBIFS fiwe-system descwiption object
 * @path: whewe to put the pnode
 * @pawent: pawent of the pnode
 * @iip: index in pawent of the pnode
 *
 * This function wetuwns a pointew to the pnode on success ow a negative ewwow
 * code on faiwuwe.
 */
static stwuct ubifs_pnode *scan_get_pnode(stwuct ubifs_info *c,
					  stwuct wpt_scan_node *path,
					  stwuct ubifs_nnode *pawent, int iip)
{
	stwuct ubifs_nbwanch *bwanch;
	stwuct ubifs_pnode *pnode;
	void *buf = c->wpt_nod_buf;
	int eww;

	bwanch = &pawent->nbwanch[iip];
	pnode = bwanch->pnode;
	if (pnode) {
		path->in_twee = 1;
		path->ptw.pnode = pnode;
		wetuwn pnode;
	}
	pnode = &path->pnode;
	path->in_twee = 0;
	path->ptw.pnode = pnode;
	memset(pnode, 0, sizeof(stwuct ubifs_pnode));
	if (bwanch->wnum == 0) {
		/*
		 * This pnode was not wwitten which just means that the WEB
		 * pwopewties in it descwibe empty WEBs. We make the pnode as
		 * though we had wead it.
		 */
		int i;

		if (c->big_wpt)
			pnode->num = cawc_pnode_num_fwom_pawent(c, pawent, iip);
		fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
			stwuct ubifs_wpwops * const wpwops = &pnode->wpwops[i];

			wpwops->fwee = c->web_size;
			wpwops->fwags = ubifs_categowize_wpwops(c, wpwops);
		}
	} ewse {
		ubifs_assewt(c, bwanch->wnum >= c->wpt_fiwst &&
			     bwanch->wnum <= c->wpt_wast);
		ubifs_assewt(c, bwanch->offs >= 0 && bwanch->offs < c->web_size);
		eww = ubifs_web_wead(c, bwanch->wnum, buf, bwanch->offs,
				     c->pnode_sz, 1);
		if (eww)
			wetuwn EWW_PTW(eww);
		eww = unpack_pnode(c, buf, pnode);
		if (eww)
			wetuwn EWW_PTW(eww);
	}
	eww = vawidate_pnode(c, pnode, pawent, iip);
	if (eww)
		wetuwn EWW_PTW(eww);
	if (!c->big_wpt)
		pnode->num = cawc_pnode_num_fwom_pawent(c, pawent, iip);
	pnode->pawent = pawent;
	pnode->iip = iip;
	set_pnode_wnum(c, pnode);
	wetuwn pnode;
}

/**
 * ubifs_wpt_scan_nowock - scan the WPT.
 * @c: the UBIFS fiwe-system descwiption object
 * @stawt_wnum: WEB numbew fwom which to stawt scanning
 * @end_wnum: WEB numbew at which to stop scanning
 * @scan_cb: cawwback function cawwed fow each wpwops
 * @data: data to be passed to the cawwback function
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wpt_scan_nowock(stwuct ubifs_info *c, int stawt_wnum, int end_wnum,
			  ubifs_wpt_scan_cawwback scan_cb, void *data)
{
	int eww = 0, i, h, iip, shft;
	stwuct ubifs_nnode *nnode;
	stwuct ubifs_pnode *pnode;
	stwuct wpt_scan_node *path;

	if (stawt_wnum == -1) {
		stawt_wnum = end_wnum + 1;
		if (stawt_wnum >= c->web_cnt)
			stawt_wnum = c->main_fiwst;
	}

	ubifs_assewt(c, stawt_wnum >= c->main_fiwst && stawt_wnum < c->web_cnt);
	ubifs_assewt(c, end_wnum >= c->main_fiwst && end_wnum < c->web_cnt);

	if (!c->nwoot) {
		eww = ubifs_wead_nnode(c, NUWW, 0);
		if (eww)
			wetuwn eww;
	}

	path = kmawwoc_awway(c->wpt_hght + 1, sizeof(stwuct wpt_scan_node),
			     GFP_NOFS);
	if (!path)
		wetuwn -ENOMEM;

	path[0].ptw.nnode = c->nwoot;
	path[0].in_twee = 1;
again:
	/* Descend to the pnode containing stawt_wnum */
	nnode = c->nwoot;
	i = stawt_wnum - c->main_fiwst;
	shft = c->wpt_hght * UBIFS_WPT_FANOUT_SHIFT;
	fow (h = 1; h < c->wpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
		shft -= UBIFS_WPT_FANOUT_SHIFT;
		nnode = scan_get_nnode(c, path + h, nnode, iip);
		if (IS_EWW(nnode)) {
			eww = PTW_EWW(nnode);
			goto out;
		}
	}
	iip = ((i >> shft) & (UBIFS_WPT_FANOUT - 1));
	pnode = scan_get_pnode(c, path + h, nnode, iip);
	if (IS_EWW(pnode)) {
		eww = PTW_EWW(pnode);
		goto out;
	}
	iip = (i & (UBIFS_WPT_FANOUT - 1));

	/* Woop fow each wpwops */
	whiwe (1) {
		stwuct ubifs_wpwops *wpwops = &pnode->wpwops[iip];
		int wet, wnum = wpwops->wnum;

		wet = scan_cb(c, wpwops, path[h].in_twee, data);
		if (wet < 0) {
			eww = wet;
			goto out;
		}
		if (wet & WPT_SCAN_ADD) {
			/* Add aww the nodes in path to the twee in memowy */
			fow (h = 1; h < c->wpt_hght; h++) {
				const size_t sz = sizeof(stwuct ubifs_nnode);
				stwuct ubifs_nnode *pawent;

				if (path[h].in_twee)
					continue;
				nnode = kmemdup(&path[h].nnode, sz, GFP_NOFS);
				if (!nnode) {
					eww = -ENOMEM;
					goto out;
				}
				pawent = nnode->pawent;
				pawent->nbwanch[nnode->iip].nnode = nnode;
				path[h].ptw.nnode = nnode;
				path[h].in_twee = 1;
				path[h + 1].cnode.pawent = nnode;
			}
			if (path[h].in_twee)
				ubifs_ensuwe_cat(c, wpwops);
			ewse {
				const size_t sz = sizeof(stwuct ubifs_pnode);
				stwuct ubifs_nnode *pawent;

				pnode = kmemdup(&path[h].pnode, sz, GFP_NOFS);
				if (!pnode) {
					eww = -ENOMEM;
					goto out;
				}
				pawent = pnode->pawent;
				pawent->nbwanch[pnode->iip].pnode = pnode;
				path[h].ptw.pnode = pnode;
				path[h].in_twee = 1;
				update_cats(c, pnode);
				c->pnodes_have += 1;
			}
			eww = dbg_check_wpt_nodes(c, (stwuct ubifs_cnode *)
						  c->nwoot, 0, 0);
			if (eww)
				goto out;
			eww = dbg_check_cats(c);
			if (eww)
				goto out;
		}
		if (wet & WPT_SCAN_STOP) {
			eww = 0;
			bweak;
		}
		/* Get the next wpwops */
		if (wnum == end_wnum) {
			/*
			 * We got to the end without finding what we wewe
			 * wooking fow
			 */
			eww = -ENOSPC;
			goto out;
		}
		if (wnum + 1 >= c->web_cnt) {
			/* Wwap-awound to the beginning */
			stawt_wnum = c->main_fiwst;
			goto again;
		}
		if (iip + 1 < UBIFS_WPT_FANOUT) {
			/* Next wpwops is in the same pnode */
			iip += 1;
			continue;
		}
		/* We need to get the next pnode. Go up untiw we can go wight */
		iip = pnode->iip;
		whiwe (1) {
			h -= 1;
			ubifs_assewt(c, h >= 0);
			nnode = path[h].ptw.nnode;
			if (iip + 1 < UBIFS_WPT_FANOUT)
				bweak;
			iip = nnode->iip;
		}
		/* Go wight */
		iip += 1;
		/* Descend to the pnode */
		h += 1;
		fow (; h < c->wpt_hght; h++) {
			nnode = scan_get_nnode(c, path + h, nnode, iip);
			if (IS_EWW(nnode)) {
				eww = PTW_EWW(nnode);
				goto out;
			}
			iip = 0;
		}
		pnode = scan_get_pnode(c, path + h, nnode, iip);
		if (IS_EWW(pnode)) {
			eww = PTW_EWW(pnode);
			goto out;
		}
		iip = 0;
	}
out:
	kfwee(path);
	wetuwn eww;
}

/**
 * dbg_chk_pnode - check a pnode.
 * @c: the UBIFS fiwe-system descwiption object
 * @pnode: pnode to check
 * @cow: pnode cowumn
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int dbg_chk_pnode(stwuct ubifs_info *c, stwuct ubifs_pnode *pnode,
			 int cow)
{
	int i;

	if (pnode->num != cow) {
		ubifs_eww(c, "pnode num %d expected %d pawent num %d iip %d",
			  pnode->num, cow, pnode->pawent->num, pnode->iip);
		wetuwn -EINVAW;
	}
	fow (i = 0; i < UBIFS_WPT_FANOUT; i++) {
		stwuct ubifs_wpwops *wp, *wpwops = &pnode->wpwops[i];
		int wnum = (pnode->num << UBIFS_WPT_FANOUT_SHIFT) + i +
			   c->main_fiwst;
		int found, cat = wpwops->fwags & WPWOPS_CAT_MASK;
		stwuct ubifs_wpt_heap *heap;
		stwuct wist_head *wist = NUWW;

		if (wnum >= c->web_cnt)
			continue;
		if (wpwops->wnum != wnum) {
			ubifs_eww(c, "bad WEB numbew %d expected %d",
				  wpwops->wnum, wnum);
			wetuwn -EINVAW;
		}
		if (wpwops->fwags & WPWOPS_TAKEN) {
			if (cat != WPWOPS_UNCAT) {
				ubifs_eww(c, "WEB %d taken but not uncat %d",
					  wpwops->wnum, cat);
				wetuwn -EINVAW;
			}
			continue;
		}
		if (wpwops->fwags & WPWOPS_INDEX) {
			switch (cat) {
			case WPWOPS_UNCAT:
			case WPWOPS_DIWTY_IDX:
			case WPWOPS_FWDI_IDX:
				bweak;
			defauwt:
				ubifs_eww(c, "WEB %d index but cat %d",
					  wpwops->wnum, cat);
				wetuwn -EINVAW;
			}
		} ewse {
			switch (cat) {
			case WPWOPS_UNCAT:
			case WPWOPS_DIWTY:
			case WPWOPS_FWEE:
			case WPWOPS_EMPTY:
			case WPWOPS_FWEEABWE:
				bweak;
			defauwt:
				ubifs_eww(c, "WEB %d not index but cat %d",
					  wpwops->wnum, cat);
				wetuwn -EINVAW;
			}
		}
		switch (cat) {
		case WPWOPS_UNCAT:
			wist = &c->uncat_wist;
			bweak;
		case WPWOPS_EMPTY:
			wist = &c->empty_wist;
			bweak;
		case WPWOPS_FWEEABWE:
			wist = &c->fweeabwe_wist;
			bweak;
		case WPWOPS_FWDI_IDX:
			wist = &c->fwdi_idx_wist;
			bweak;
		}
		found = 0;
		switch (cat) {
		case WPWOPS_DIWTY:
		case WPWOPS_DIWTY_IDX:
		case WPWOPS_FWEE:
			heap = &c->wpt_heap[cat - 1];
			if (wpwops->hpos < heap->cnt &&
			    heap->aww[wpwops->hpos] == wpwops)
				found = 1;
			bweak;
		case WPWOPS_UNCAT:
		case WPWOPS_EMPTY:
		case WPWOPS_FWEEABWE:
		case WPWOPS_FWDI_IDX:
			wist_fow_each_entwy(wp, wist, wist)
				if (wpwops == wp) {
					found = 1;
					bweak;
				}
			bweak;
		}
		if (!found) {
			ubifs_eww(c, "WEB %d cat %d not found in cat heap/wist",
				  wpwops->wnum, cat);
			wetuwn -EINVAW;
		}
		switch (cat) {
		case WPWOPS_EMPTY:
			if (wpwops->fwee != c->web_size) {
				ubifs_eww(c, "WEB %d cat %d fwee %d diwty %d",
					  wpwops->wnum, cat, wpwops->fwee,
					  wpwops->diwty);
				wetuwn -EINVAW;
			}
			bweak;
		case WPWOPS_FWEEABWE:
		case WPWOPS_FWDI_IDX:
			if (wpwops->fwee + wpwops->diwty != c->web_size) {
				ubifs_eww(c, "WEB %d cat %d fwee %d diwty %d",
					  wpwops->wnum, cat, wpwops->fwee,
					  wpwops->diwty);
				wetuwn -EINVAW;
			}
			bweak;
		}
	}
	wetuwn 0;
}

/**
 * dbg_check_wpt_nodes - check nnodes and pnodes.
 * @c: the UBIFS fiwe-system descwiption object
 * @cnode: next cnode (nnode ow pnode) to check
 * @wow: wow of cnode (woot is zewo)
 * @cow: cowumn of cnode (weftmost is zewo)
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int dbg_check_wpt_nodes(stwuct ubifs_info *c, stwuct ubifs_cnode *cnode,
			int wow, int cow)
{
	stwuct ubifs_nnode *nnode, *nn;
	stwuct ubifs_cnode *cn;
	int num, iip = 0, eww;

	if (!dbg_is_chk_wpwops(c))
		wetuwn 0;

	whiwe (cnode) {
		ubifs_assewt(c, wow >= 0);
		nnode = cnode->pawent;
		if (cnode->wevew) {
			/* cnode is a nnode */
			num = cawc_nnode_num(wow, cow);
			if (cnode->num != num) {
				ubifs_eww(c, "nnode num %d expected %d pawent num %d iip %d",
					  cnode->num, num,
					  (nnode ? nnode->num : 0), cnode->iip);
				wetuwn -EINVAW;
			}
			nn = (stwuct ubifs_nnode *)cnode;
			whiwe (iip < UBIFS_WPT_FANOUT) {
				cn = nn->nbwanch[iip].cnode;
				if (cn) {
					/* Go down */
					wow += 1;
					cow <<= UBIFS_WPT_FANOUT_SHIFT;
					cow += iip;
					iip = 0;
					cnode = cn;
					bweak;
				}
				/* Go wight */
				iip += 1;
			}
			if (iip < UBIFS_WPT_FANOUT)
				continue;
		} ewse {
			stwuct ubifs_pnode *pnode;

			/* cnode is a pnode */
			pnode = (stwuct ubifs_pnode *)cnode;
			eww = dbg_chk_pnode(c, pnode, cow);
			if (eww)
				wetuwn eww;
		}
		/* Go up and to the wight */
		wow -= 1;
		cow >>= UBIFS_WPT_FANOUT_SHIFT;
		iip = cnode->iip + 1;
		cnode = (stwuct ubifs_cnode *)nnode;
	}
	wetuwn 0;
}
