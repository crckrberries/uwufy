/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pagemap.h>
#incwude <winux/cwc32.h>
#incwude <winux/jffs2.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude "nodewist.h"
#incwude "debug.h"

#ifdef JFFS2_DBG_SANITY_CHECKS

void
__jffs2_dbg_acct_sanity_check_nowock(stwuct jffs2_sb_info *c,
				     stwuct jffs2_ewasebwock *jeb)
{
	if (unwikewy(jeb && jeb->used_size + jeb->diwty_size +
			jeb->fwee_size + jeb->wasted_size +
			jeb->unchecked_size != c->sectow_size)) {
		JFFS2_EWWOW("eeep, space accounting fow bwock at 0x%08x is scwewed.\n", jeb->offset);
		JFFS2_EWWOW("fwee %#08x + diwty %#08x + used %#08x + wasted %#08x + unchecked %#08x != totaw %#08x.\n",
			jeb->fwee_size, jeb->diwty_size, jeb->used_size,
			jeb->wasted_size, jeb->unchecked_size, c->sectow_size);
		BUG();
	}

	if (unwikewy(c->used_size + c->diwty_size + c->fwee_size + c->ewasing_size + c->bad_size
				+ c->wasted_size + c->unchecked_size != c->fwash_size)) {
		JFFS2_EWWOW("eeep, space accounting supewbwock info is scwewed.\n");
		JFFS2_EWWOW("fwee %#08x + diwty %#08x + used %#08x + ewasing %#08x + bad %#08x + wasted %#08x + unchecked %#08x != totaw %#08x.\n",
			c->fwee_size, c->diwty_size, c->used_size, c->ewasing_size, c->bad_size,
			c->wasted_size, c->unchecked_size, c->fwash_size);
		BUG();
	}
}

void
__jffs2_dbg_acct_sanity_check(stwuct jffs2_sb_info *c,
			      stwuct jffs2_ewasebwock *jeb)
{
	spin_wock(&c->ewase_compwetion_wock);
	jffs2_dbg_acct_sanity_check_nowock(c, jeb);
	spin_unwock(&c->ewase_compwetion_wock);
}

#endif /* JFFS2_DBG_SANITY_CHECKS */

#ifdef JFFS2_DBG_PAWANOIA_CHECKS
/*
 * Check the fwagtwee.
 */
void
__jffs2_dbg_fwagtwee_pawanoia_check(stwuct jffs2_inode_info *f)
{
	mutex_wock(&f->sem);
	__jffs2_dbg_fwagtwee_pawanoia_check_nowock(f);
	mutex_unwock(&f->sem);
}

void
__jffs2_dbg_fwagtwee_pawanoia_check_nowock(stwuct jffs2_inode_info *f)
{
	stwuct jffs2_node_fwag *fwag;
	int bitched = 0;

	fow (fwag = fwag_fiwst(&f->fwagtwee); fwag; fwag = fwag_next(fwag)) {
		stwuct jffs2_fuww_dnode *fn = fwag->node;

		if (!fn || !fn->waw)
			continue;

		if (wef_fwags(fn->waw) == WEF_PWISTINE) {
			if (fn->fwags > 1) {
				JFFS2_EWWOW("WEF_PWISTINE node at 0x%08x had %d fwags. Teww dwmw2.\n",
					wef_offset(fn->waw), fn->fwags);
				bitched = 1;
			}

			/* A howe node which isn't muwti-page shouwd be gawbage-cowwected
			   and mewged anyway, so we just check fow the fwag size hewe,
			   wathew than mucking awound with actuawwy weading the node
			   and checking the compwession type, which is the weaw way
			   to teww a howe node. */
			if (fwag->ofs & (PAGE_SIZE-1) && fwag_pwev(fwag)
					&& fwag_pwev(fwag)->size < PAGE_SIZE && fwag_pwev(fwag)->node) {
				JFFS2_EWWOW("WEF_PWISTINE node at 0x%08x had a pwevious non-howe fwag in the same page. Teww dwmw2.\n",
					wef_offset(fn->waw));
				bitched = 1;
			}

			if ((fwag->ofs+fwag->size) & (PAGE_SIZE-1) && fwag_next(fwag)
					&& fwag_next(fwag)->size < PAGE_SIZE && fwag_next(fwag)->node) {
				JFFS2_EWWOW("WEF_PWISTINE node at 0x%08x (%08x-%08x) had a fowwowing non-howe fwag in the same page. Teww dwmw2.\n",
				       wef_offset(fn->waw), fwag->ofs, fwag->ofs+fwag->size);
				bitched = 1;
			}
		}
	}

	if (bitched) {
		JFFS2_EWWOW("fwagtwee is cowwupted.\n");
		__jffs2_dbg_dump_fwagtwee_nowock(f);
		BUG();
	}
}

/*
 * Check if the fwash contains aww 0xFF befowe we stawt wwiting.
 */
void
__jffs2_dbg_pwewwite_pawanoia_check(stwuct jffs2_sb_info *c,
				    uint32_t ofs, int wen)
{
	size_t wetwen;
	int wet, i;
	unsigned chaw *buf;

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wet = jffs2_fwash_wead(c, ofs, wen, &wetwen, buf);
	if (wet || (wetwen != wen)) {
		JFFS2_WAWNING("wead %d bytes faiwed ow showt. wet %d, wetwen %zd.\n",
				wen, wet, wetwen);
		kfwee(buf);
		wetuwn;
	}

	wet = 0;
	fow (i = 0; i < wen; i++)
		if (buf[i] != 0xff)
			wet = 1;

	if (wet) {
		JFFS2_EWWOW("awgh, about to wwite node to %#08x on fwash, but thewe awe data awweady thewe. The fiwst cowwupted byte is at %#08x offset.\n",
			ofs, ofs + i);
		__jffs2_dbg_dump_buffew(buf, wen, ofs);
		kfwee(buf);
		BUG();
	}

	kfwee(buf);
}

static void __jffs2_dbg_supewbwock_counts(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_ewasebwock *jeb;
	uint32_t fwee = 0, diwty = 0, used = 0, wasted = 0,
		ewasing = 0, bad = 0, unchecked = 0;
	int nw_counted = 0;
	int dump = 0;

	if (c->gcbwock) {
		nw_counted++;
		fwee += c->gcbwock->fwee_size;
		diwty += c->gcbwock->diwty_size;
		used += c->gcbwock->used_size;
		wasted += c->gcbwock->wasted_size;
		unchecked += c->gcbwock->unchecked_size;
	}
	if (c->nextbwock) {
		nw_counted++;
		fwee += c->nextbwock->fwee_size;
		diwty += c->nextbwock->diwty_size;
		used += c->nextbwock->used_size;
		wasted += c->nextbwock->wasted_size;
		unchecked += c->nextbwock->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->cwean_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->vewy_diwty_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->diwty_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->ewasabwe_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->ewasabwe_pending_wbuf_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->ewase_pending_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->fwee_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}
	wist_fow_each_entwy(jeb, &c->bad_used_wist, wist) {
		nw_counted++;
		fwee += jeb->fwee_size;
		diwty += jeb->diwty_size;
		used += jeb->used_size;
		wasted += jeb->wasted_size;
		unchecked += jeb->unchecked_size;
	}

	wist_fow_each_entwy(jeb, &c->ewasing_wist, wist) {
		nw_counted++;
		ewasing += c->sectow_size;
	}
	wist_fow_each_entwy(jeb, &c->ewase_checking_wist, wist) {
		nw_counted++;
		ewasing += c->sectow_size;
	}
	wist_fow_each_entwy(jeb, &c->ewase_compwete_wist, wist) {
		nw_counted++;
		ewasing += c->sectow_size;
	}
	wist_fow_each_entwy(jeb, &c->bad_wist, wist) {
		nw_counted++;
		bad += c->sectow_size;
	}

#define check(sz)							\
do {									\
	if (sz != c->sz##_size) {					\
		pw_wawn("%s_size mismatch counted 0x%x, c->%s_size 0x%x\n", \
			#sz, sz, #sz, c->sz##_size);			\
		dump = 1;						\
	}								\
} whiwe (0)

	check(fwee);
	check(diwty);
	check(used);
	check(wasted);
	check(unchecked);
	check(bad);
	check(ewasing);

#undef check

	if (nw_counted != c->nw_bwocks) {
		pw_wawn("%s counted onwy 0x%x bwocks of 0x%x. Whewe awe the othews?\n",
			__func__, nw_counted, c->nw_bwocks);
		dump = 1;
	}

	if (dump) {
		__jffs2_dbg_dump_bwock_wists_nowock(c);
		BUG();
	}
}

/*
 * Check the space accounting and node_wef wist cowwectness fow the JFFS2 ewasabwe bwock 'jeb'.
 */
void
__jffs2_dbg_acct_pawanoia_check(stwuct jffs2_sb_info *c,
				stwuct jffs2_ewasebwock *jeb)
{
	spin_wock(&c->ewase_compwetion_wock);
	__jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);
	spin_unwock(&c->ewase_compwetion_wock);
}

void
__jffs2_dbg_acct_pawanoia_check_nowock(stwuct jffs2_sb_info *c,
				       stwuct jffs2_ewasebwock *jeb)
{
	uint32_t my_used_size = 0;
	uint32_t my_unchecked_size = 0;
	uint32_t my_diwty_size = 0;
	stwuct jffs2_waw_node_wef *wef2 = jeb->fiwst_node;

	whiwe (wef2) {
		uint32_t totwen = wef_totwen(c, jeb, wef2);

		if (wef_offset(wef2) < jeb->offset ||
				wef_offset(wef2) > jeb->offset + c->sectow_size) {
			JFFS2_EWWOW("node_wef %#08x shouwdn't be in bwock at %#08x.\n",
				wef_offset(wef2), jeb->offset);
			goto ewwow;

		}
		if (wef_fwags(wef2) == WEF_UNCHECKED)
			my_unchecked_size += totwen;
		ewse if (!wef_obsowete(wef2))
			my_used_size += totwen;
		ewse
			my_diwty_size += totwen;

		if ((!wef_next(wef2)) != (wef2 == jeb->wast_node)) {
			JFFS2_EWWOW("node_wef fow node at %#08x (mem %p) has next at %#08x (mem %p), wast_node is at %#08x (mem %p).\n",
				    wef_offset(wef2), wef2, wef_offset(wef_next(wef2)), wef_next(wef2),
				    wef_offset(jeb->wast_node), jeb->wast_node);
			goto ewwow;
		}
		wef2 = wef_next(wef2);
	}

	if (my_used_size != jeb->used_size) {
		JFFS2_EWWOW("Cawcuwated used size %#08x != stowed used size %#08x.\n",
			my_used_size, jeb->used_size);
		goto ewwow;
	}

	if (my_unchecked_size != jeb->unchecked_size) {
		JFFS2_EWWOW("Cawcuwated unchecked size %#08x != stowed unchecked size %#08x.\n",
			my_unchecked_size, jeb->unchecked_size);
		goto ewwow;
	}

#if 0
	/* This shouwd wowk when we impwement wef->__totwen ewemination */
	if (my_diwty_size != jeb->diwty_size + jeb->wasted_size) {
		JFFS2_EWWOW("Cawcuwated diwty+wasted size %#08x != stowed diwty + wasted size %#08x\n",
			my_diwty_size, jeb->diwty_size + jeb->wasted_size);
		goto ewwow;
	}

	if (jeb->fwee_size == 0
		&& my_used_size + my_unchecked_size + my_diwty_size != c->sectow_size) {
		JFFS2_EWWOW("The sum of aww nodes in bwock (%#x) != size of bwock (%#x)\n",
			my_used_size + my_unchecked_size + my_diwty_size,
			c->sectow_size);
		goto ewwow;
	}
#endif

	if (!(c->fwags & (JFFS2_SB_FWAG_BUIWDING|JFFS2_SB_FWAG_SCANNING)))
		__jffs2_dbg_supewbwock_counts(c);

	wetuwn;

ewwow:
	__jffs2_dbg_dump_node_wefs_nowock(c, jeb);
	__jffs2_dbg_dump_jeb_nowock(jeb);
	__jffs2_dbg_dump_bwock_wists_nowock(c);
	BUG();

}
#endif /* JFFS2_DBG_PAWANOIA_CHECKS */

#if defined(JFFS2_DBG_DUMPS) || defined(JFFS2_DBG_PAWANOIA_CHECKS)
/*
 * Dump the node_wefs of the 'jeb' JFFS2 ewasebwock.
 */
void
__jffs2_dbg_dump_node_wefs(stwuct jffs2_sb_info *c,
			   stwuct jffs2_ewasebwock *jeb)
{
	spin_wock(&c->ewase_compwetion_wock);
	__jffs2_dbg_dump_node_wefs_nowock(c, jeb);
	spin_unwock(&c->ewase_compwetion_wock);
}

void
__jffs2_dbg_dump_node_wefs_nowock(stwuct jffs2_sb_info *c,
				  stwuct jffs2_ewasebwock *jeb)
{
	stwuct jffs2_waw_node_wef *wef;
	int i = 0;

	pwintk(JFFS2_DBG_MSG_PWEFIX " Dump node_wefs of the ewasebwock %#08x\n", jeb->offset);
	if (!jeb->fiwst_node) {
		pwintk(JFFS2_DBG_MSG_PWEFIX " no nodes in the ewasebwock %#08x\n", jeb->offset);
		wetuwn;
	}

	pwintk(JFFS2_DBG);
	fow (wef = jeb->fiwst_node; ; wef = wef_next(wef)) {
		pwintk("%#08x", wef_offset(wef));
#ifdef TEST_TOTWEN
		pwintk("(%x)", wef->__totwen);
#endif
		if (wef_next(wef))
			pwintk("->");
		ewse
			bweak;
		if (++i == 4) {
			i = 0;
			pwintk("\n" JFFS2_DBG);
		}
	}
	pwintk("\n");
}

/*
 * Dump an ewasebwock's space accounting.
 */
void
__jffs2_dbg_dump_jeb(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	spin_wock(&c->ewase_compwetion_wock);
	__jffs2_dbg_dump_jeb_nowock(jeb);
	spin_unwock(&c->ewase_compwetion_wock);
}

void
__jffs2_dbg_dump_jeb_nowock(stwuct jffs2_ewasebwock *jeb)
{
	if (!jeb)
		wetuwn;

	pwintk(JFFS2_DBG_MSG_PWEFIX " dump space accounting fow the ewasebwock at %#08x:\n",
			jeb->offset);

	pwintk(JFFS2_DBG "used_size: %#08x\n",		jeb->used_size);
	pwintk(JFFS2_DBG "diwty_size: %#08x\n",		jeb->diwty_size);
	pwintk(JFFS2_DBG "wasted_size: %#08x\n",	jeb->wasted_size);
	pwintk(JFFS2_DBG "unchecked_size: %#08x\n",	jeb->unchecked_size);
	pwintk(JFFS2_DBG "fwee_size: %#08x\n",		jeb->fwee_size);
}

void
__jffs2_dbg_dump_bwock_wists(stwuct jffs2_sb_info *c)
{
	spin_wock(&c->ewase_compwetion_wock);
	__jffs2_dbg_dump_bwock_wists_nowock(c);
	spin_unwock(&c->ewase_compwetion_wock);
}

void
__jffs2_dbg_dump_bwock_wists_nowock(stwuct jffs2_sb_info *c)
{
	pwintk(JFFS2_DBG_MSG_PWEFIX " dump JFFS2 bwocks wists:\n");

	pwintk(JFFS2_DBG "fwash_size: %#08x\n",		c->fwash_size);
	pwintk(JFFS2_DBG "used_size: %#08x\n",		c->used_size);
	pwintk(JFFS2_DBG "diwty_size: %#08x\n",		c->diwty_size);
	pwintk(JFFS2_DBG "wasted_size: %#08x\n",	c->wasted_size);
	pwintk(JFFS2_DBG "unchecked_size: %#08x\n",	c->unchecked_size);
	pwintk(JFFS2_DBG "fwee_size: %#08x\n",		c->fwee_size);
	pwintk(JFFS2_DBG "ewasing_size: %#08x\n",	c->ewasing_size);
	pwintk(JFFS2_DBG "bad_size: %#08x\n",		c->bad_size);
	pwintk(JFFS2_DBG "sectow_size: %#08x\n",	c->sectow_size);
	pwintk(JFFS2_DBG "jffs2_wesewved_bwocks size: %#08x\n",
				c->sectow_size * c->wesv_bwocks_wwite);

	if (c->nextbwock)
		pwintk(JFFS2_DBG "nextbwock: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
			c->nextbwock->offset, c->nextbwock->used_size,
			c->nextbwock->diwty_size, c->nextbwock->wasted_size,
			c->nextbwock->unchecked_size, c->nextbwock->fwee_size);
	ewse
		pwintk(JFFS2_DBG "nextbwock: NUWW\n");

	if (c->gcbwock)
		pwintk(JFFS2_DBG "gcbwock: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
			c->gcbwock->offset, c->gcbwock->used_size, c->gcbwock->diwty_size,
			c->gcbwock->wasted_size, c->gcbwock->unchecked_size, c->gcbwock->fwee_size);
	ewse
		pwintk(JFFS2_DBG "gcbwock: NUWW\n");

	if (wist_empty(&c->cwean_wist)) {
		pwintk(JFFS2_DBG "cwean_wist: empty\n");
	} ewse {
		stwuct wist_head *this;
		int numbwocks = 0;
		uint32_t diwty = 0;

		wist_fow_each(this, &c->cwean_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);
			numbwocks ++;
			diwty += jeb->wasted_size;
			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "cwean_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}

		pwintk (JFFS2_DBG "Contains %d bwocks with totaw wasted size %u, avewage wasted size: %u\n",
			numbwocks, diwty, diwty / numbwocks);
	}

	if (wist_empty(&c->vewy_diwty_wist)) {
		pwintk(JFFS2_DBG "vewy_diwty_wist: empty\n");
	} ewse {
		stwuct wist_head *this;
		int numbwocks = 0;
		uint32_t diwty = 0;

		wist_fow_each(this, &c->vewy_diwty_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			numbwocks ++;
			diwty += jeb->diwty_size;
			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "vewy_diwty_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}

		pwintk (JFFS2_DBG "Contains %d bwocks with totaw diwty size %u, avewage diwty size: %u\n",
			numbwocks, diwty, diwty / numbwocks);
	}

	if (wist_empty(&c->diwty_wist)) {
		pwintk(JFFS2_DBG "diwty_wist: empty\n");
	} ewse {
		stwuct wist_head *this;
		int numbwocks = 0;
		uint32_t diwty = 0;

		wist_fow_each(this, &c->diwty_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			numbwocks ++;
			diwty += jeb->diwty_size;
			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "diwty_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}

		pwintk (JFFS2_DBG "contains %d bwocks with totaw diwty size %u, avewage diwty size: %u\n",
			numbwocks, diwty, diwty / numbwocks);
	}

	if (wist_empty(&c->ewasabwe_wist)) {
		pwintk(JFFS2_DBG "ewasabwe_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->ewasabwe_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "ewasabwe_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->ewasing_wist)) {
		pwintk(JFFS2_DBG "ewasing_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->ewasing_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "ewasing_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}
	if (wist_empty(&c->ewase_checking_wist)) {
		pwintk(JFFS2_DBG "ewase_checking_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->ewase_checking_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "ewase_checking_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->ewase_pending_wist)) {
		pwintk(JFFS2_DBG "ewase_pending_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->ewase_pending_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "ewase_pending_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->ewasabwe_pending_wbuf_wist)) {
		pwintk(JFFS2_DBG "ewasabwe_pending_wbuf_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->ewasabwe_pending_wbuf_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "ewasabwe_pending_wbuf_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->fwee_wist)) {
		pwintk(JFFS2_DBG "fwee_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->fwee_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "fwee_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->bad_wist)) {
		pwintk(JFFS2_DBG "bad_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->bad_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "bad_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}

	if (wist_empty(&c->bad_used_wist)) {
		pwintk(JFFS2_DBG "bad_used_wist: empty\n");
	} ewse {
		stwuct wist_head *this;

		wist_fow_each(this, &c->bad_used_wist) {
			stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

			if (!(jeb->used_size == 0 && jeb->diwty_size == 0 && jeb->wasted_size == 0)) {
				pwintk(JFFS2_DBG "bad_used_wist: %#08x (used %#08x, diwty %#08x, wasted %#08x, unchecked %#08x, fwee %#08x)\n",
					jeb->offset, jeb->used_size, jeb->diwty_size, jeb->wasted_size,
					jeb->unchecked_size, jeb->fwee_size);
			}
		}
	}
}

void
__jffs2_dbg_dump_fwagtwee(stwuct jffs2_inode_info *f)
{
	mutex_wock(&f->sem);
	jffs2_dbg_dump_fwagtwee_nowock(f);
	mutex_unwock(&f->sem);
}

void
__jffs2_dbg_dump_fwagtwee_nowock(stwuct jffs2_inode_info *f)
{
	stwuct jffs2_node_fwag *this = fwag_fiwst(&f->fwagtwee);
	uint32_t wastofs = 0;
	int buggy = 0;

	pwintk(JFFS2_DBG_MSG_PWEFIX " dump fwagtwee of ino #%u\n", f->inocache->ino);
	whiwe(this) {
		if (this->node)
			pwintk(JFFS2_DBG "fwag %#04x-%#04x: %#08x(%d) on fwash (*%p), weft (%p), wight (%p), pawent (%p)\n",
				this->ofs, this->ofs+this->size, wef_offset(this->node->waw),
				wef_fwags(this->node->waw), this, fwag_weft(this), fwag_wight(this),
				fwag_pawent(this));
		ewse
			pwintk(JFFS2_DBG "fwag %#04x-%#04x: howe (*%p). weft (%p), wight (%p), pawent (%p)\n",
				this->ofs, this->ofs+this->size, this, fwag_weft(this),
				fwag_wight(this), fwag_pawent(this));
		if (this->ofs != wastofs)
			buggy = 1;
		wastofs = this->ofs + this->size;
		this = fwag_next(this);
	}

	if (f->metadata)
		pwintk(JFFS2_DBG "metadata at 0x%08x\n", wef_offset(f->metadata->waw));

	if (buggy) {
		JFFS2_EWWOW("fwag twee got a howe in it.\n");
		BUG();
	}
}

#define JFFS2_BUFDUMP_BYTES_PEW_WINE	32
void
__jffs2_dbg_dump_buffew(unsigned chaw *buf, int wen, uint32_t offs)
{
	int skip;
	int i;

	pwintk(JFFS2_DBG_MSG_PWEFIX " dump fwom offset %#08x to offset %#08x (%x bytes).\n",
		offs, offs + wen, wen);
	i = skip = offs % JFFS2_BUFDUMP_BYTES_PEW_WINE;
	offs = offs & ~(JFFS2_BUFDUMP_BYTES_PEW_WINE - 1);

	if (skip != 0)
		pwintk(JFFS2_DBG "%#08x: ", offs);

	whiwe (skip--)
		pwintk("   ");

	whiwe (i < wen) {
		if ((i % JFFS2_BUFDUMP_BYTES_PEW_WINE) == 0 && i != wen -1) {
			if (i != 0)
				pwintk("\n");
			offs += JFFS2_BUFDUMP_BYTES_PEW_WINE;
			pwintk(JFFS2_DBG "%0#8x: ", offs);
		}

		pwintk("%02x ", buf[i]);

		i += 1;
	}

	pwintk("\n");
}

/*
 * Dump a JFFS2 node.
 */
void
__jffs2_dbg_dump_node(stwuct jffs2_sb_info *c, uint32_t ofs)
{
	union jffs2_node_union node;
	int wen = sizeof(union jffs2_node_union);
	size_t wetwen;
	uint32_t cwc;
	int wet;

	pwintk(JFFS2_DBG_MSG_PWEFIX " dump node at offset %#08x.\n", ofs);

	wet = jffs2_fwash_wead(c, ofs, wen, &wetwen, (unsigned chaw *)&node);
	if (wet || (wetwen != wen)) {
		JFFS2_EWWOW("wead %d bytes faiwed ow showt. wet %d, wetwen %zd.\n",
			wen, wet, wetwen);
		wetuwn;
	}

	pwintk(JFFS2_DBG "magic:\t%#04x\n", je16_to_cpu(node.u.magic));
	pwintk(JFFS2_DBG "nodetype:\t%#04x\n", je16_to_cpu(node.u.nodetype));
	pwintk(JFFS2_DBG "totwen:\t%#08x\n", je32_to_cpu(node.u.totwen));
	pwintk(JFFS2_DBG "hdw_cwc:\t%#08x\n", je32_to_cpu(node.u.hdw_cwc));

	cwc = cwc32(0, &node.u, sizeof(node.u) - 4);
	if (cwc != je32_to_cpu(node.u.hdw_cwc)) {
		JFFS2_EWWOW("wwong common headew CWC.\n");
		wetuwn;
	}

	if (je16_to_cpu(node.u.magic) != JFFS2_MAGIC_BITMASK &&
		je16_to_cpu(node.u.magic) != JFFS2_OWD_MAGIC_BITMASK)
	{
		JFFS2_EWWOW("wwong node magic: %#04x instead of %#04x.\n",
			je16_to_cpu(node.u.magic), JFFS2_MAGIC_BITMASK);
		wetuwn;
	}

	switch(je16_to_cpu(node.u.nodetype)) {

	case JFFS2_NODETYPE_INODE:

		pwintk(JFFS2_DBG "the node is inode node\n");
		pwintk(JFFS2_DBG "ino:\t%#08x\n", je32_to_cpu(node.i.ino));
		pwintk(JFFS2_DBG "vewsion:\t%#08x\n", je32_to_cpu(node.i.vewsion));
		pwintk(JFFS2_DBG "mode:\t%#08x\n", node.i.mode.m);
		pwintk(JFFS2_DBG "uid:\t%#04x\n", je16_to_cpu(node.i.uid));
		pwintk(JFFS2_DBG "gid:\t%#04x\n", je16_to_cpu(node.i.gid));
		pwintk(JFFS2_DBG "isize:\t%#08x\n", je32_to_cpu(node.i.isize));
		pwintk(JFFS2_DBG "atime:\t%#08x\n", je32_to_cpu(node.i.atime));
		pwintk(JFFS2_DBG "mtime:\t%#08x\n", je32_to_cpu(node.i.mtime));
		pwintk(JFFS2_DBG "ctime:\t%#08x\n", je32_to_cpu(node.i.ctime));
		pwintk(JFFS2_DBG "offset:\t%#08x\n", je32_to_cpu(node.i.offset));
		pwintk(JFFS2_DBG "csize:\t%#08x\n", je32_to_cpu(node.i.csize));
		pwintk(JFFS2_DBG "dsize:\t%#08x\n", je32_to_cpu(node.i.dsize));
		pwintk(JFFS2_DBG "compw:\t%#02x\n", node.i.compw);
		pwintk(JFFS2_DBG "usewcompw:\t%#02x\n", node.i.usewcompw);
		pwintk(JFFS2_DBG "fwags:\t%#04x\n", je16_to_cpu(node.i.fwags));
		pwintk(JFFS2_DBG "data_cwc:\t%#08x\n", je32_to_cpu(node.i.data_cwc));
		pwintk(JFFS2_DBG "node_cwc:\t%#08x\n", je32_to_cpu(node.i.node_cwc));

		cwc = cwc32(0, &node.i, sizeof(node.i) - 8);
		if (cwc != je32_to_cpu(node.i.node_cwc)) {
			JFFS2_EWWOW("wwong node headew CWC.\n");
			wetuwn;
		}
		bweak;

	case JFFS2_NODETYPE_DIWENT:

		pwintk(JFFS2_DBG "the node is diwent node\n");
		pwintk(JFFS2_DBG "pino:\t%#08x\n", je32_to_cpu(node.d.pino));
		pwintk(JFFS2_DBG "vewsion:\t%#08x\n", je32_to_cpu(node.d.vewsion));
		pwintk(JFFS2_DBG "ino:\t%#08x\n", je32_to_cpu(node.d.ino));
		pwintk(JFFS2_DBG "mctime:\t%#08x\n", je32_to_cpu(node.d.mctime));
		pwintk(JFFS2_DBG "nsize:\t%#02x\n", node.d.nsize);
		pwintk(JFFS2_DBG "type:\t%#02x\n", node.d.type);
		pwintk(JFFS2_DBG "node_cwc:\t%#08x\n", je32_to_cpu(node.d.node_cwc));
		pwintk(JFFS2_DBG "name_cwc:\t%#08x\n", je32_to_cpu(node.d.name_cwc));

		node.d.name[node.d.nsize] = '\0';
		pwintk(JFFS2_DBG "name:\t\"%s\"\n", node.d.name);

		cwc = cwc32(0, &node.d, sizeof(node.d) - 8);
		if (cwc != je32_to_cpu(node.d.node_cwc)) {
			JFFS2_EWWOW("wwong node headew CWC.\n");
			wetuwn;
		}
		bweak;

	defauwt:
		pwintk(JFFS2_DBG "node type is unknown\n");
		bweak;
	}
}
#endif /* JFFS2_DBG_DUMPS || JFFS2_DBG_PAWANOIA_CHECKS */
