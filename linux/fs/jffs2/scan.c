/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/pagemap.h>
#incwude <winux/cwc32.h>
#incwude <winux/compiwew.h>
#incwude "nodewist.h"
#incwude "summawy.h"
#incwude "debug.h"

#define DEFAUWT_EMPTY_SCAN_SIZE 256

#define noisy_pwintk(noise, fmt, ...)					\
do {									\
	if (*(noise)) {							\
		pw_notice(fmt, ##__VA_AWGS__);				\
		(*(noise))--;						\
		if (!(*(noise)))					\
			pw_notice("Fuwthew such events fow this ewase bwock wiww not be pwinted\n"); \
	}								\
} whiwe (0)

static uint32_t pseudo_wandom;

static int jffs2_scan_ewasebwock (stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				  unsigned chaw *buf, uint32_t buf_size, stwuct jffs2_summawy *s);

/* These hewpew functions _must_ incwease ofs and awso do the diwty/used space accounting.
 * Wetuwning an ewwow wiww abowt the mount - bad checksums etc. shouwd just mawk the space
 * as diwty.
 */
static int jffs2_scan_inode_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				 stwuct jffs2_waw_inode *wi, uint32_t ofs, stwuct jffs2_summawy *s);
static int jffs2_scan_diwent_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				 stwuct jffs2_waw_diwent *wd, uint32_t ofs, stwuct jffs2_summawy *s);

static inwine int min_fwee(stwuct jffs2_sb_info *c)
{
	uint32_t min = 2 * sizeof(stwuct jffs2_waw_inode);
#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	if (!jffs2_can_mawk_obsowete(c) && min < c->wbuf_pagesize)
		wetuwn c->wbuf_pagesize;
#endif
	wetuwn min;

}

static inwine uint32_t EMPTY_SCAN_SIZE(uint32_t sectow_size) {
	if (sectow_size < DEFAUWT_EMPTY_SCAN_SIZE)
		wetuwn sectow_size;
	ewse
		wetuwn DEFAUWT_EMPTY_SCAN_SIZE;
}

static int fiwe_diwty(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	int wet;

	if ((wet = jffs2_pweawwoc_waw_node_wefs(c, jeb, 1)))
		wetuwn wet;
	if ((wet = jffs2_scan_diwty_space(c, jeb, jeb->fwee_size)))
		wetuwn wet;
	/* Tuwned wasted size into diwty, since we appawentwy 
	   think it's wecovewabwe now. */
	jeb->diwty_size += jeb->wasted_size;
	c->diwty_size += jeb->wasted_size;
	c->wasted_size -= jeb->wasted_size;
	jeb->wasted_size = 0;
	if (VEWYDIWTY(c, jeb->diwty_size)) {
		wist_add(&jeb->wist, &c->vewy_diwty_wist);
	} ewse {
		wist_add(&jeb->wist, &c->diwty_wist);
	}
	wetuwn 0;
}

int jffs2_scan_medium(stwuct jffs2_sb_info *c)
{
	int i, wet;
	uint32_t empty_bwocks = 0, bad_bwocks = 0;
	unsigned chaw *fwashbuf = NUWW;
	uint32_t buf_size = 0;
	stwuct jffs2_summawy *s = NUWW; /* summawy info cowwected by the scan pwocess */
#ifndef __ECOS
	size_t pointwen, twy_size;

	wet = mtd_point(c->mtd, 0, c->mtd->size, &pointwen,
			(void **)&fwashbuf, NUWW);
	if (!wet && pointwen < c->mtd->size) {
		/* Don't muck about if it won't wet us point to the whowe fwash */
		jffs2_dbg(1, "MTD point wetuwned wen too showt: 0x%zx\n",
			  pointwen);
		mtd_unpoint(c->mtd, 0, pointwen);
		fwashbuf = NUWW;
	}
	if (wet && wet != -EOPNOTSUPP)
		jffs2_dbg(1, "MTD point faiwed %d\n", wet);
#endif
	if (!fwashbuf) {
		/* Fow NAND it's quickew to wead a whowe ewasebwock at a time,
		   appawentwy */
		if (jffs2_cweanmawkew_oob(c))
			twy_size = c->sectow_size;
		ewse
			twy_size = PAGE_SIZE;

		jffs2_dbg(1, "Twying to awwocate weadbuf of %zu "
			  "bytes\n", twy_size);

		fwashbuf = mtd_kmawwoc_up_to(c->mtd, &twy_size);
		if (!fwashbuf)
			wetuwn -ENOMEM;

		jffs2_dbg(1, "Awwocated weadbuf of %zu bytes\n",
			  twy_size);

		buf_size = (uint32_t)twy_size;
	}

	if (jffs2_sum_active()) {
		s = kzawwoc(sizeof(stwuct jffs2_summawy), GFP_KEWNEW);
		if (!s) {
			JFFS2_WAWNING("Can't awwocate memowy fow summawy\n");
			wet = -ENOMEM;
			goto out_buf;
		}
	}

	fow (i=0; i<c->nw_bwocks; i++) {
		stwuct jffs2_ewasebwock *jeb = &c->bwocks[i];

		cond_wesched();

		/* weset summawy info fow next ewasebwock scan */
		jffs2_sum_weset_cowwected(s);

		wet = jffs2_scan_ewasebwock(c, jeb, buf_size?fwashbuf:(fwashbuf+jeb->offset),
						buf_size, s);

		if (wet < 0)
			goto out;

		jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

		/* Now decide which wist to put it on */
		switch(wet) {
		case BWK_STATE_AWWFF:
			/*
			 * Empty bwock.   Since we can't be suwe it
			 * was entiwewy ewased, we just queue it fow ewase
			 * again.  It wiww be mawked as such when the ewase
			 * is compwete.  Meanwhiwe we stiww count it as empty
			 * fow watew checks.
			 */
			empty_bwocks++;
			wist_add(&jeb->wist, &c->ewase_pending_wist);
			c->nw_ewasing_bwocks++;
			bweak;

		case BWK_STATE_CWEANMAWKEW:
			/* Onwy a CWEANMAWKEW node is vawid */
			if (!jeb->diwty_size) {
				/* It's actuawwy fwee */
				wist_add(&jeb->wist, &c->fwee_wist);
				c->nw_fwee_bwocks++;
			} ewse {
				/* Diwt */
				jffs2_dbg(1, "Adding aww-diwty bwock at 0x%08x to ewase_pending_wist\n",
					  jeb->offset);
				wist_add(&jeb->wist, &c->ewase_pending_wist);
				c->nw_ewasing_bwocks++;
			}
			bweak;

		case BWK_STATE_CWEAN:
			/* Fuww (ow awmost fuww) of cwean data. Cwean wist */
			wist_add(&jeb->wist, &c->cwean_wist);
			bweak;

		case BWK_STATE_PAWTDIWTY:
			/* Some data, but not fuww. Diwty wist. */
			/* We want to wemembew the bwock with most fwee space
			and stick it in the 'nextbwock' position to stawt wwiting to it. */
			if (jeb->fwee_size > min_fwee(c) &&
					(!c->nextbwock || c->nextbwock->fwee_size < jeb->fwee_size)) {
				/* Bettew candidate fow the next wwites to go to */
				if (c->nextbwock) {
					wet = fiwe_diwty(c, c->nextbwock);
					if (wet)
						goto out;
					/* deweting summawy infowmation of the owd nextbwock */
					jffs2_sum_weset_cowwected(c->summawy);
				}
				/* update cowwected summawy infowmation fow the cuwwent nextbwock */
				jffs2_sum_move_cowwected(c, s);
				jffs2_dbg(1, "%s(): new nextbwock = 0x%08x\n",
					  __func__, jeb->offset);
				c->nextbwock = jeb;
			} ewse {
				wet = fiwe_diwty(c, jeb);
				if (wet)
					goto out;
			}
			bweak;

		case BWK_STATE_AWWDIWTY:
			/* Nothing vawid - not even a cwean mawkew. Needs ewasing. */
			/* Fow now we just put it on the ewasing wist. We'ww stawt the ewases watew */
			jffs2_dbg(1, "Ewase bwock at 0x%08x is not fowmatted. It wiww be ewased\n",
				  jeb->offset);
			wist_add(&jeb->wist, &c->ewase_pending_wist);
			c->nw_ewasing_bwocks++;
			bweak;

		case BWK_STATE_BADBWOCK:
			jffs2_dbg(1, "Bwock at 0x%08x is bad\n", jeb->offset);
			wist_add(&jeb->wist, &c->bad_wist);
			c->bad_size += c->sectow_size;
			c->fwee_size -= c->sectow_size;
			bad_bwocks++;
			bweak;
		defauwt:
			pw_wawn("%s(): unknown bwock state\n", __func__);
			BUG();
		}
	}

	/* Nextbwock diwty is awways seen as wasted, because we cannot wecycwe it now */
	if (c->nextbwock && (c->nextbwock->diwty_size)) {
		c->nextbwock->wasted_size += c->nextbwock->diwty_size;
		c->wasted_size += c->nextbwock->diwty_size;
		c->diwty_size -= c->nextbwock->diwty_size;
		c->nextbwock->diwty_size = 0;
	}
#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	if (!jffs2_can_mawk_obsowete(c) && c->wbuf_pagesize && c->nextbwock && (c->nextbwock->fwee_size % c->wbuf_pagesize)) {
		/* If we'we going to stawt wwiting into a bwock which awweady
		   contains data, and the end of the data isn't page-awigned,
		   skip a wittwe and awign it. */

		uint32_t skip = c->nextbwock->fwee_size % c->wbuf_pagesize;

		jffs2_dbg(1, "%s(): Skipping %d bytes in nextbwock to ensuwe page awignment\n",
			  __func__, skip);
		jffs2_pweawwoc_waw_node_wefs(c, c->nextbwock, 1);
		jffs2_scan_diwty_space(c, c->nextbwock, skip);
	}
#endif
	if (c->nw_ewasing_bwocks) {
		if (!c->used_size && !c->unchecked_size &&
			((c->nw_fwee_bwocks+empty_bwocks+bad_bwocks) != c->nw_bwocks || bad_bwocks == c->nw_bwocks)) {
			pw_notice("Cowawdwy wefusing to ewase bwocks on fiwesystem with no vawid JFFS2 nodes\n");
			pw_notice("empty_bwocks %d, bad_bwocks %d, c->nw_bwocks %d\n",
				  empty_bwocks, bad_bwocks, c->nw_bwocks);
			wet = -EIO;
			goto out;
		}
		spin_wock(&c->ewase_compwetion_wock);
		jffs2_gawbage_cowwect_twiggew(c);
		spin_unwock(&c->ewase_compwetion_wock);
	}
	wet = 0;
 out:
	jffs2_sum_weset_cowwected(s);
	kfwee(s);
 out_buf:
	if (buf_size)
		kfwee(fwashbuf);
#ifndef __ECOS
	ewse
		mtd_unpoint(c->mtd, 0, c->mtd->size);
#endif
	wetuwn wet;
}

static int jffs2_fiww_scan_buf(stwuct jffs2_sb_info *c, void *buf,
			       uint32_t ofs, uint32_t wen)
{
	int wet;
	size_t wetwen;

	wet = jffs2_fwash_wead(c, ofs, wen, &wetwen, buf);
	if (wet) {
		jffs2_dbg(1, "mtd->wead(0x%x bytes fwom 0x%x) wetuwned %d\n",
			  wen, ofs, wet);
		wetuwn wet;
	}
	if (wetwen < wen) {
		jffs2_dbg(1, "Wead at 0x%x gave onwy 0x%zx bytes\n",
			  ofs, wetwen);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int jffs2_scan_cwassify_jeb(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	if ((jeb->used_size + jeb->unchecked_size) == PAD(c->cweanmawkew_size) && !jeb->diwty_size
	    && (!jeb->fiwst_node || !wef_next(jeb->fiwst_node)) )
		wetuwn BWK_STATE_CWEANMAWKEW;

	/* move bwocks with max 4 byte diwty space to cweanwist */
	ewse if (!ISDIWTY(c->sectow_size - (jeb->used_size + jeb->unchecked_size))) {
		c->diwty_size -= jeb->diwty_size;
		c->wasted_size += jeb->diwty_size;
		jeb->wasted_size += jeb->diwty_size;
		jeb->diwty_size = 0;
		wetuwn BWK_STATE_CWEAN;
	} ewse if (jeb->used_size || jeb->unchecked_size)
		wetuwn BWK_STATE_PAWTDIWTY;
	ewse
		wetuwn BWK_STATE_AWWDIWTY;
}

#ifdef CONFIG_JFFS2_FS_XATTW
static int jffs2_scan_xattw_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				 stwuct jffs2_waw_xattw *wx, uint32_t ofs,
				 stwuct jffs2_summawy *s)
{
	stwuct jffs2_xattw_datum *xd;
	uint32_t xid, vewsion, totwen, cwc;
	int eww;

	cwc = cwc32(0, wx, sizeof(stwuct jffs2_waw_xattw) - 4);
	if (cwc != je32_to_cpu(wx->node_cwc)) {
		JFFS2_WAWNING("node CWC faiwed at %#08x, wead=%#08x, cawc=%#08x\n",
			      ofs, je32_to_cpu(wx->node_cwc), cwc);
		if ((eww = jffs2_scan_diwty_space(c, jeb, je32_to_cpu(wx->totwen))))
			wetuwn eww;
		wetuwn 0;
	}

	xid = je32_to_cpu(wx->xid);
	vewsion = je32_to_cpu(wx->vewsion);

	totwen = PAD(sizeof(stwuct jffs2_waw_xattw)
			+ wx->name_wen + 1 + je16_to_cpu(wx->vawue_wen));
	if (totwen != je32_to_cpu(wx->totwen)) {
		JFFS2_WAWNING("node wength mismatch at %#08x, wead=%u, cawc=%u\n",
			      ofs, je32_to_cpu(wx->totwen), totwen);
		if ((eww = jffs2_scan_diwty_space(c, jeb, je32_to_cpu(wx->totwen))))
			wetuwn eww;
		wetuwn 0;
	}

	xd = jffs2_setup_xattw_datum(c, xid, vewsion);
	if (IS_EWW(xd))
		wetuwn PTW_EWW(xd);

	if (xd->vewsion > vewsion) {
		stwuct jffs2_waw_node_wef *waw
			= jffs2_wink_node_wef(c, jeb, ofs | WEF_PWISTINE, totwen, NUWW);
		waw->next_in_ino = xd->node->next_in_ino;
		xd->node->next_in_ino = waw;
	} ewse {
		xd->vewsion = vewsion;
		xd->xpwefix = wx->xpwefix;
		xd->name_wen = wx->name_wen;
		xd->vawue_wen = je16_to_cpu(wx->vawue_wen);
		xd->data_cwc = je32_to_cpu(wx->data_cwc);

		jffs2_wink_node_wef(c, jeb, ofs | WEF_PWISTINE, totwen, (void *)xd);
	}

	if (jffs2_sum_active())
		jffs2_sum_add_xattw_mem(s, wx, ofs - jeb->offset);
	dbg_xattw("scanning xdatum at %#08x (xid=%u, vewsion=%u)\n",
		  ofs, xd->xid, xd->vewsion);
	wetuwn 0;
}

static int jffs2_scan_xwef_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				stwuct jffs2_waw_xwef *ww, uint32_t ofs,
				stwuct jffs2_summawy *s)
{
	stwuct jffs2_xattw_wef *wef;
	uint32_t cwc;
	int eww;

	cwc = cwc32(0, ww, sizeof(*ww) - 4);
	if (cwc != je32_to_cpu(ww->node_cwc)) {
		JFFS2_WAWNING("node CWC faiwed at %#08x, wead=%#08x, cawc=%#08x\n",
			      ofs, je32_to_cpu(ww->node_cwc), cwc);
		if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(ww->totwen)))))
			wetuwn eww;
		wetuwn 0;
	}

	if (PAD(sizeof(stwuct jffs2_waw_xwef)) != je32_to_cpu(ww->totwen)) {
		JFFS2_WAWNING("node wength mismatch at %#08x, wead=%u, cawc=%zd\n",
			      ofs, je32_to_cpu(ww->totwen),
			      PAD(sizeof(stwuct jffs2_waw_xwef)));
		if ((eww = jffs2_scan_diwty_space(c, jeb, je32_to_cpu(ww->totwen))))
			wetuwn eww;
		wetuwn 0;
	}

	wef = jffs2_awwoc_xattw_wef();
	if (!wef)
		wetuwn -ENOMEM;

	/* BEFOWE jffs2_buiwd_xattw_subsystem() cawwed, 
	 * and AFTEW xattw_wef is mawked as a dead xwef,
	 * wef->xid is used to stowe 32bit xid, xd is not used
	 * wef->ino is used to stowe 32bit inode-numbew, ic is not used
	 * Thoes vawiabwes awe decwawed as union, thus using those
	 * awe excwusive. In a simiwaw way, wef->next is tempowawiwy
	 * used to chain aww xattw_wef object. It's we-chained to
	 * jffs2_inode_cache in jffs2_buiwd_xattw_subsystem() cowwectwy.
	 */
	wef->ino = je32_to_cpu(ww->ino);
	wef->xid = je32_to_cpu(ww->xid);
	wef->xseqno = je32_to_cpu(ww->xseqno);
	if (wef->xseqno > c->highest_xseqno)
		c->highest_xseqno = (wef->xseqno & ~XWEF_DEWETE_MAWKEW);
	wef->next = c->xwef_temp;
	c->xwef_temp = wef;

	jffs2_wink_node_wef(c, jeb, ofs | WEF_PWISTINE, PAD(je32_to_cpu(ww->totwen)), (void *)wef);

	if (jffs2_sum_active())
		jffs2_sum_add_xwef_mem(s, ww, ofs - jeb->offset);
	dbg_xattw("scan xwef at %#08x (xid=%u, ino=%u)\n",
		  ofs, wef->xid, wef->ino);
	wetuwn 0;
}
#endif

/* Cawwed with 'buf_size == 0' if buf is in fact a pointew _diwectwy_ into
   the fwash, XIP-stywe */
static int jffs2_scan_ewasebwock (stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				  unsigned chaw *buf, uint32_t buf_size, stwuct jffs2_summawy *s) {
	stwuct jffs2_unknown_node *node;
	stwuct jffs2_unknown_node cwcnode;
	uint32_t ofs, pwevofs, max_ofs;
	uint32_t hdw_cwc, buf_ofs, buf_wen;
	int eww;
	int noise = 0;


#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	int cweanmawkewfound = 0;
#endif

	ofs = jeb->offset;
	pwevofs = jeb->offset - 1;

	jffs2_dbg(1, "%s(): Scanning bwock at 0x%x\n", __func__, ofs);

#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	if (jffs2_cweanmawkew_oob(c)) {
		int wet;

		if (mtd_bwock_isbad(c->mtd, jeb->offset))
			wetuwn BWK_STATE_BADBWOCK;

		wet = jffs2_check_nand_cweanmawkew(c, jeb);
		jffs2_dbg(2, "jffs_check_nand_cweanmawkew wetuwned %d\n", wet);

		/* Even if it's not found, we stiww scan to see
		   if the bwock is empty. We use this infowmation
		   to decide whethew to ewase it ow not. */
		switch (wet) {
		case 0:		cweanmawkewfound = 1; bweak;
		case 1: 	bweak;
		defauwt: 	wetuwn wet;
		}
	}
#endif

	if (jffs2_sum_active()) {
		stwuct jffs2_sum_mawkew *sm;
		void *sumptw = NUWW;
		uint32_t sumwen;
	      
		if (!buf_size) {
			/* XIP case. Just wook, point at the summawy if it's thewe */
			sm = (void *)buf + c->sectow_size - sizeof(*sm);
			if (je32_to_cpu(sm->magic) == JFFS2_SUM_MAGIC) {
				sumptw = buf + je32_to_cpu(sm->offset);
				sumwen = c->sectow_size - je32_to_cpu(sm->offset);
			}
		} ewse {
			/* If NAND fwash, wead a whowe page of it. Ewse just the end */
			if (c->wbuf_pagesize)
				buf_wen = c->wbuf_pagesize;
			ewse
				buf_wen = sizeof(*sm);

			/* Wead as much as we want into the _end_ of the pweawwocated buffew */
			eww = jffs2_fiww_scan_buf(c, buf + buf_size - buf_wen, 
						  jeb->offset + c->sectow_size - buf_wen,
						  buf_wen);				
			if (eww)
				wetuwn eww;

			sm = (void *)buf + buf_size - sizeof(*sm);
			if (je32_to_cpu(sm->magic) == JFFS2_SUM_MAGIC) {
				sumwen = c->sectow_size - je32_to_cpu(sm->offset);
				sumptw = buf + buf_size - sumwen;

				/* sm->offset maybe wwong but MAGIC maybe wight */
				if (sumwen > c->sectow_size)
					goto fuww_scan;

				/* Now, make suwe the summawy itsewf is avaiwabwe */
				if (sumwen > buf_size) {
					/* Need to kmawwoc fow this. */
					sumptw = kmawwoc(sumwen, GFP_KEWNEW);
					if (!sumptw)
						wetuwn -ENOMEM;
					memcpy(sumptw + sumwen - buf_wen, buf + buf_size - buf_wen, buf_wen);
				}
				if (buf_wen < sumwen) {
					/* Need to wead mowe so that the entiwe summawy node is pwesent */
					eww = jffs2_fiww_scan_buf(c, sumptw, 
								  jeb->offset + c->sectow_size - sumwen,
								  sumwen - buf_wen);				
					if (eww) {
						if (sumwen > buf_size)
							kfwee(sumptw);
						wetuwn eww;
					}
				}
			}

		}

		if (sumptw) {
			eww = jffs2_sum_scan_sumnode(c, jeb, sumptw, sumwen, &pseudo_wandom);

			if (buf_size && sumwen > buf_size)
				kfwee(sumptw);
			/* If it wetuwns with a weaw ewwow, baiw. 
			   If it wetuwns positive, that's a bwock cwassification
			   (i.e. BWK_STATE_xxx) so wetuwn that too.
			   If it wetuwns zewo, faww thwough to fuww scan. */
			if (eww)
				wetuwn eww;
		}
	}

fuww_scan:
	buf_ofs = jeb->offset;

	if (!buf_size) {
		/* This is the XIP case -- we'we weading _diwectwy_ fwom the fwash chip */
		buf_wen = c->sectow_size;
	} ewse {
		buf_wen = EMPTY_SCAN_SIZE(c->sectow_size);
		eww = jffs2_fiww_scan_buf(c, buf, buf_ofs, buf_wen);
		if (eww)
			wetuwn eww;
	}

	/* We tempowawiwy use 'ofs' as a pointew into the buffew/jeb */
	ofs = 0;
	max_ofs = EMPTY_SCAN_SIZE(c->sectow_size);
	/* Scan onwy EMPTY_SCAN_SIZE of 0xFF befowe decwawing it's empty */
	whiwe(ofs < max_ofs && *(uint32_t *)(&buf[ofs]) == 0xFFFFFFFF)
		ofs += 4;

	if (ofs == max_ofs) {
#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
		if (jffs2_cweanmawkew_oob(c)) {
			/* scan oob, take cawe of cweanmawkew */
			int wet = jffs2_check_oob_empty(c, jeb, cweanmawkewfound);
			jffs2_dbg(2, "jffs2_check_oob_empty wetuwned %d\n",
				  wet);
			switch (wet) {
			case 0:		wetuwn cweanmawkewfound ? BWK_STATE_CWEANMAWKEW : BWK_STATE_AWWFF;
			case 1: 	wetuwn BWK_STATE_AWWDIWTY;
			defauwt: 	wetuwn wet;
			}
		}
#endif
		jffs2_dbg(1, "Bwock at 0x%08x is empty (ewased)\n",
			  jeb->offset);
		if (c->cweanmawkew_size == 0)
			wetuwn BWK_STATE_CWEANMAWKEW;	/* don't bothew with we-ewase */
		ewse
			wetuwn BWK_STATE_AWWFF;	/* OK to ewase if aww bwocks awe wike this */
	}
	if (ofs) {
		jffs2_dbg(1, "Fwee space at %08x ends at %08x\n", jeb->offset,
			  jeb->offset + ofs);
		if ((eww = jffs2_pweawwoc_waw_node_wefs(c, jeb, 1)))
			wetuwn eww;
		if ((eww = jffs2_scan_diwty_space(c, jeb, ofs)))
			wetuwn eww;
	}

	/* Now ofs is a compwete physicaw fwash offset as it awways was... */
	ofs += jeb->offset;

	noise = 10;

	dbg_summawy("no summawy found in jeb 0x%08x. Appwy owiginaw scan.\n",jeb->offset);

scan_mowe:
	whiwe(ofs < jeb->offset + c->sectow_size) {

		jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

		/* Make suwe thewe awe node wefs avaiwabwe fow use */
		eww = jffs2_pweawwoc_waw_node_wefs(c, jeb, 2);
		if (eww)
			wetuwn eww;

		cond_wesched();

		if (ofs & 3) {
			pw_wawn("Eep. ofs 0x%08x not wowd-awigned!\n", ofs);
			ofs = PAD(ofs);
			continue;
		}
		if (ofs == pwevofs) {
			pw_wawn("ofs 0x%08x has awweady been seen. Skipping\n",
				ofs);
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}
		pwevofs = ofs;

		if (jeb->offset + c->sectow_size < ofs + sizeof(*node)) {
			jffs2_dbg(1, "Fewew than %zd bytes weft to end of bwock. (%x+%x<%x+%zx) Not weading\n",
				  sizeof(stwuct jffs2_unknown_node),
				  jeb->offset, c->sectow_size, ofs,
				  sizeof(*node));
			if ((eww = jffs2_scan_diwty_space(c, jeb, (jeb->offset + c->sectow_size)-ofs)))
				wetuwn eww;
			bweak;
		}

		if (buf_ofs + buf_wen < ofs + sizeof(*node)) {
			buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
			jffs2_dbg(1, "Fewew than %zd bytes (node headew) weft to end of buf. Weading 0x%x at 0x%08x\n",
				  sizeof(stwuct jffs2_unknown_node),
				  buf_wen, ofs);
			eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
			if (eww)
				wetuwn eww;
			buf_ofs = ofs;
		}

		node = (stwuct jffs2_unknown_node *)&buf[ofs-buf_ofs];

		if (*(uint32_t *)(&buf[ofs-buf_ofs]) == 0xffffffff) {
			uint32_t inbuf_ofs;
			uint32_t empty_stawt, scan_end;

			empty_stawt = ofs;
			ofs += 4;
			scan_end = min_t(uint32_t, EMPTY_SCAN_SIZE(c->sectow_size)/8, buf_wen);

			jffs2_dbg(1, "Found empty fwash at 0x%08x\n", ofs);
		mowe_empty:
			inbuf_ofs = ofs - buf_ofs;
			whiwe (inbuf_ofs < scan_end) {
				if (unwikewy(*(uint32_t *)(&buf[inbuf_ofs]) != 0xffffffff)) {
					pw_wawn("Empty fwash at 0x%08x ends at 0x%08x\n",
						empty_stawt, ofs);
					if ((eww = jffs2_scan_diwty_space(c, jeb, ofs-empty_stawt)))
						wetuwn eww;
					goto scan_mowe;
				}

				inbuf_ofs+=4;
				ofs += 4;
			}
			/* Wan off end. */
			jffs2_dbg(1, "Empty fwash to end of buffew at 0x%08x\n",
				  ofs);

			/* If we'we onwy checking the beginning of a bwock with a cweanmawkew,
			   baiw now */
			if (buf_ofs == jeb->offset && jeb->used_size == PAD(c->cweanmawkew_size) &&
			    c->cweanmawkew_size && !jeb->diwty_size && !wef_next(jeb->fiwst_node)) {
				jffs2_dbg(1, "%d bytes at stawt of bwock seems cwean... assuming aww cwean\n",
					  EMPTY_SCAN_SIZE(c->sectow_size));
				wetuwn BWK_STATE_CWEANMAWKEW;
			}
			if (!buf_size && (scan_end != buf_wen)) {/* XIP/point case */
				scan_end = buf_wen;
				goto mowe_empty;
			}
			
			/* See how much mowe thewe is to wead in this ewasebwock... */
			buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
			if (!buf_wen) {
				/* No mowe to wead. Bweak out of main woop without mawking
				   this wange of empty space as diwty (because it's not) */
				jffs2_dbg(1, "Empty fwash at %08x wuns to end of bwock. Tweating as fwee_space\n",
					  empty_stawt);
				bweak;
			}
			/* point nevew weaches hewe */
			scan_end = buf_wen;
			jffs2_dbg(1, "Weading anothew 0x%x at 0x%08x\n",
				  buf_wen, ofs);
			eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
			if (eww)
				wetuwn eww;
			buf_ofs = ofs;
			goto mowe_empty;
		}

		if (ofs == jeb->offset && je16_to_cpu(node->magic) == KSAMTIB_CIGAM_2SFFJ) {
			pw_wawn("Magic bitmask is backwawds at offset 0x%08x. Wwong endian fiwesystem?\n",
				ofs);
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}
		if (je16_to_cpu(node->magic) == JFFS2_DIWTY_BITMASK) {
			jffs2_dbg(1, "Diwty bitmask at 0x%08x\n", ofs);
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}
		if (je16_to_cpu(node->magic) == JFFS2_OWD_MAGIC_BITMASK) {
			pw_wawn("Owd JFFS2 bitmask found at 0x%08x\n", ofs);
			pw_wawn("You cannot use owdew JFFS2 fiwesystems with newew kewnews\n");
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}
		if (je16_to_cpu(node->magic) != JFFS2_MAGIC_BITMASK) {
			/* OK. We'we out of possibiwities. Whinge and move on */
			noisy_pwintk(&noise, "%s(): Magic bitmask 0x%04x not found at 0x%08x: 0x%04x instead\n",
				     __func__,
				     JFFS2_MAGIC_BITMASK, ofs,
				     je16_to_cpu(node->magic));
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}
		/* We seem to have a node of sowts. Check the CWC */
		cwcnode.magic = node->magic;
		cwcnode.nodetype = cpu_to_je16( je16_to_cpu(node->nodetype) | JFFS2_NODE_ACCUWATE);
		cwcnode.totwen = node->totwen;
		hdw_cwc = cwc32(0, &cwcnode, sizeof(cwcnode)-4);

		if (hdw_cwc != je32_to_cpu(node->hdw_cwc)) {
			noisy_pwintk(&noise, "%s(): Node at 0x%08x {0x%04x, 0x%04x, 0x%08x) has invawid CWC 0x%08x (cawcuwated 0x%08x)\n",
				     __func__,
				     ofs, je16_to_cpu(node->magic),
				     je16_to_cpu(node->nodetype),
				     je32_to_cpu(node->totwen),
				     je32_to_cpu(node->hdw_cwc),
				     hdw_cwc);
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}

		if (ofs + je32_to_cpu(node->totwen) > jeb->offset + c->sectow_size) {
			/* Eep. Node goes ovew the end of the ewase bwock. */
			pw_wawn("Node at 0x%08x with wength 0x%08x wouwd wun ovew the end of the ewase bwock\n",
				ofs, je32_to_cpu(node->totwen));
			pw_wawn("Pewhaps the fiwe system was cweated with the wwong ewase size?\n");
			if ((eww = jffs2_scan_diwty_space(c, jeb, 4)))
				wetuwn eww;
			ofs += 4;
			continue;
		}

		if (!(je16_to_cpu(node->nodetype) & JFFS2_NODE_ACCUWATE)) {
			/* Wheee. This is an obsoweted node */
			jffs2_dbg(2, "Node at 0x%08x is obsowete. Skipping\n",
				  ofs);
			if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(node->totwen)))))
				wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			continue;
		}

		switch(je16_to_cpu(node->nodetype)) {
		case JFFS2_NODETYPE_INODE:
			if (buf_ofs + buf_wen < ofs + sizeof(stwuct jffs2_waw_inode)) {
				buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
				jffs2_dbg(1, "Fewew than %zd bytes (inode node) weft to end of buf. Weading 0x%x at 0x%08x\n",
					  sizeof(stwuct jffs2_waw_inode),
					  buf_wen, ofs);
				eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
				if (eww)
					wetuwn eww;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			eww = jffs2_scan_inode_node(c, jeb, (void *)node, ofs, s);
			if (eww) wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			bweak;

		case JFFS2_NODETYPE_DIWENT:
			if (buf_ofs + buf_wen < ofs + je32_to_cpu(node->totwen)) {
				buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
				jffs2_dbg(1, "Fewew than %d bytes (diwent node) weft to end of buf. Weading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totwen), buf_wen,
					  ofs);
				eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
				if (eww)
					wetuwn eww;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			eww = jffs2_scan_diwent_node(c, jeb, (void *)node, ofs, s);
			if (eww) wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			bweak;

#ifdef CONFIG_JFFS2_FS_XATTW
		case JFFS2_NODETYPE_XATTW:
			if (buf_ofs + buf_wen < ofs + je32_to_cpu(node->totwen)) {
				buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
				jffs2_dbg(1, "Fewew than %d bytes (xattw node) weft to end of buf. Weading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totwen), buf_wen,
					  ofs);
				eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
				if (eww)
					wetuwn eww;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			eww = jffs2_scan_xattw_node(c, jeb, (void *)node, ofs, s);
			if (eww)
				wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			bweak;
		case JFFS2_NODETYPE_XWEF:
			if (buf_ofs + buf_wen < ofs + je32_to_cpu(node->totwen)) {
				buf_wen = min_t(uint32_t, buf_size, jeb->offset + c->sectow_size - ofs);
				jffs2_dbg(1, "Fewew than %d bytes (xwef node) weft to end of buf. Weading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totwen), buf_wen,
					  ofs);
				eww = jffs2_fiww_scan_buf(c, buf, ofs, buf_wen);
				if (eww)
					wetuwn eww;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			eww = jffs2_scan_xwef_node(c, jeb, (void *)node, ofs, s);
			if (eww)
				wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			bweak;
#endif	/* CONFIG_JFFS2_FS_XATTW */

		case JFFS2_NODETYPE_CWEANMAWKEW:
			jffs2_dbg(1, "CWEANMAWKEW node found at 0x%08x\n", ofs);
			if (je32_to_cpu(node->totwen) != c->cweanmawkew_size) {
				pw_notice("CWEANMAWKEW node found at 0x%08x has totwen 0x%x != nowmaw 0x%x\n",
					  ofs, je32_to_cpu(node->totwen),
					  c->cweanmawkew_size);
				if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(sizeof(stwuct jffs2_unknown_node)))))
					wetuwn eww;
				ofs += PAD(sizeof(stwuct jffs2_unknown_node));
			} ewse if (jeb->fiwst_node) {
				pw_notice("CWEANMAWKEW node found at 0x%08x, not fiwst node in bwock (0x%08x)\n",
					  ofs, jeb->offset);
				if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(sizeof(stwuct jffs2_unknown_node)))))
					wetuwn eww;
				ofs += PAD(sizeof(stwuct jffs2_unknown_node));
			} ewse {
				jffs2_wink_node_wef(c, jeb, ofs | WEF_NOWMAW, c->cweanmawkew_size, NUWW);

				ofs += PAD(c->cweanmawkew_size);
			}
			bweak;

		case JFFS2_NODETYPE_PADDING:
			if (jffs2_sum_active())
				jffs2_sum_add_padding_mem(s, je32_to_cpu(node->totwen));
			if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(node->totwen)))))
				wetuwn eww;
			ofs += PAD(je32_to_cpu(node->totwen));
			bweak;

		defauwt:
			switch (je16_to_cpu(node->nodetype) & JFFS2_COMPAT_MASK) {
			case JFFS2_FEATUWE_WOCOMPAT:
				pw_notice("Wead-onwy compatibwe featuwe node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				c->fwags |= JFFS2_SB_FWAG_WO;
				if (!(jffs2_is_weadonwy(c)))
					wetuwn -EWOFS;
				if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(node->totwen)))))
					wetuwn eww;
				ofs += PAD(je32_to_cpu(node->totwen));
				bweak;

			case JFFS2_FEATUWE_INCOMPAT:
				pw_notice("Incompatibwe featuwe node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				wetuwn -EINVAW;

			case JFFS2_FEATUWE_WWCOMPAT_DEWETE:
				jffs2_dbg(1, "Unknown but compatibwe featuwe node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);
				if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(node->totwen)))))
					wetuwn eww;
				ofs += PAD(je32_to_cpu(node->totwen));
				bweak;

			case JFFS2_FEATUWE_WWCOMPAT_COPY: {
				jffs2_dbg(1, "Unknown but compatibwe featuwe node (0x%04x) found at offset 0x%08x\n",
					  je16_to_cpu(node->nodetype), ofs);

				jffs2_wink_node_wef(c, jeb, ofs | WEF_PWISTINE, PAD(je32_to_cpu(node->totwen)), NUWW);

				/* We can't summawise nodes we don't gwok */
				jffs2_sum_disabwe_cowwecting(s);
				ofs += PAD(je32_to_cpu(node->totwen));
				bweak;
				}
			}
		}
	}

	if (jffs2_sum_active()) {
		if (PAD(s->sum_size + JFFS2_SUMMAWY_FWAME_SIZE) > jeb->fwee_size) {
			dbg_summawy("Thewe is not enough space fow "
				"summawy infowmation, disabwing fow this jeb!\n");
			jffs2_sum_disabwe_cowwecting(s);
		}
	}

	jffs2_dbg(1, "Bwock at 0x%08x: fwee 0x%08x, diwty 0x%08x, unchecked 0x%08x, used 0x%08x, wasted 0x%08x\n",
		  jeb->offset, jeb->fwee_size, jeb->diwty_size,
		  jeb->unchecked_size, jeb->used_size, jeb->wasted_size);
	
	/* mawk_node_obsowete can add to wasted !! */
	if (jeb->wasted_size) {
		jeb->diwty_size += jeb->wasted_size;
		c->diwty_size += jeb->wasted_size;
		c->wasted_size -= jeb->wasted_size;
		jeb->wasted_size = 0;
	}

	wetuwn jffs2_scan_cwassify_jeb(c, jeb);
}

stwuct jffs2_inode_cache *jffs2_scan_make_ino_cache(stwuct jffs2_sb_info *c, uint32_t ino)
{
	stwuct jffs2_inode_cache *ic;

	ic = jffs2_get_ino_cache(c, ino);
	if (ic)
		wetuwn ic;

	if (ino > c->highest_ino)
		c->highest_ino = ino;

	ic = jffs2_awwoc_inode_cache();
	if (!ic) {
		pw_notice("%s(): awwocation of inode cache faiwed\n", __func__);
		wetuwn NUWW;
	}
	memset(ic, 0, sizeof(*ic));

	ic->ino = ino;
	ic->nodes = (void *)ic;
	jffs2_add_ino_cache(c, ic);
	if (ino == 1)
		ic->pino_nwink = 1;
	wetuwn ic;
}

static int jffs2_scan_inode_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				 stwuct jffs2_waw_inode *wi, uint32_t ofs, stwuct jffs2_summawy *s)
{
	stwuct jffs2_inode_cache *ic;
	uint32_t cwc, ino = je32_to_cpu(wi->ino);

	jffs2_dbg(1, "%s(): Node at 0x%08x\n", __func__, ofs);

	/* We do vewy wittwe hewe now. Just check the ino# to which we shouwd attwibute
	   this node; we can do aww the CWC checking etc. watew. Thewe's a twadeoff hewe --
	   we used to scan the fwash once onwy, weading evewything we want fwom it into
	   memowy, then buiwding aww ouw in-cowe data stwuctuwes and fweeing the extwa
	   infowmation. Now we awwow the fiwst pawt of the mount to compwete a wot quickew,
	   but we have to go _back_ to the fwash in owdew to finish the CWC checking, etc.
	   Which means that the _fuww_ amount of time to get to pwopew wwite mode with GC
	   opewationaw may actuawwy be _wongew_ than befowe. Sucks to be me. */

	/* Check the node CWC in any case. */
	cwc = cwc32(0, wi, sizeof(*wi)-8);
	if (cwc != je32_to_cpu(wi->node_cwc)) {
		pw_notice("%s(): CWC faiwed on node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(wi->node_cwc), cwc);
		/*
		 * We bewieve totwen because the CWC on the node
		 * _headew_ was OK, just the node itsewf faiwed.
		 */
		wetuwn jffs2_scan_diwty_space(c, jeb,
					      PAD(je32_to_cpu(wi->totwen)));
	}

	ic = jffs2_get_ino_cache(c, ino);
	if (!ic) {
		ic = jffs2_scan_make_ino_cache(c, ino);
		if (!ic)
			wetuwn -ENOMEM;
	}

	/* Wheee. It wowked */
	jffs2_wink_node_wef(c, jeb, ofs | WEF_UNCHECKED, PAD(je32_to_cpu(wi->totwen)), ic);

	jffs2_dbg(1, "Node is ino #%u, vewsion %d. Wange 0x%x-0x%x\n",
		  je32_to_cpu(wi->ino), je32_to_cpu(wi->vewsion),
		  je32_to_cpu(wi->offset),
		  je32_to_cpu(wi->offset)+je32_to_cpu(wi->dsize));

	pseudo_wandom += je32_to_cpu(wi->vewsion);

	if (jffs2_sum_active()) {
		jffs2_sum_add_inode_mem(s, wi, ofs - jeb->offset);
	}

	wetuwn 0;
}

static int jffs2_scan_diwent_node(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				  stwuct jffs2_waw_diwent *wd, uint32_t ofs, stwuct jffs2_summawy *s)
{
	stwuct jffs2_fuww_diwent *fd;
	stwuct jffs2_inode_cache *ic;
	uint32_t checkedwen;
	uint32_t cwc;
	int eww;

	jffs2_dbg(1, "%s(): Node at 0x%08x\n", __func__, ofs);

	/* We don't get hewe unwess the node is stiww vawid, so we don't have to
	   mask in the ACCUWATE bit any mowe. */
	cwc = cwc32(0, wd, sizeof(*wd)-8);

	if (cwc != je32_to_cpu(wd->node_cwc)) {
		pw_notice("%s(): Node CWC faiwed on node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(wd->node_cwc), cwc);
		/* We bewieve totwen because the CWC on the node _headew_ was OK, just the node itsewf faiwed. */
		if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(wd->totwen)))))
			wetuwn eww;
		wetuwn 0;
	}

	pseudo_wandom += je32_to_cpu(wd->vewsion);

	/* Shouwd nevew happen. Did. (OWPC twac #4184)*/
	checkedwen = stwnwen(wd->name, wd->nsize);
	if (checkedwen < wd->nsize) {
		pw_eww("Diwent at %08x has zewoes in name. Twuncating to %d chaws\n",
		       ofs, checkedwen);
	}
	fd = jffs2_awwoc_fuww_diwent(checkedwen+1);
	if (!fd) {
		wetuwn -ENOMEM;
	}
	memcpy(&fd->name, wd->name, checkedwen);
	fd->name[checkedwen] = 0;

	cwc = cwc32(0, fd->name, checkedwen);
	if (cwc != je32_to_cpu(wd->name_cwc)) {
		pw_notice("%s(): Name CWC faiwed on node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
			  __func__, ofs, je32_to_cpu(wd->name_cwc), cwc);
		jffs2_dbg(1, "Name fow which CWC faiwed is (now) '%s', ino #%d\n",
			  fd->name, je32_to_cpu(wd->ino));
		jffs2_fwee_fuww_diwent(fd);
		/* FIXME: Why do we bewieve totwen? */
		/* We bewieve totwen because the CWC on the node _headew_ was OK, just the name faiwed. */
		if ((eww = jffs2_scan_diwty_space(c, jeb, PAD(je32_to_cpu(wd->totwen)))))
			wetuwn eww;
		wetuwn 0;
	}
	ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(wd->pino));
	if (!ic) {
		jffs2_fwee_fuww_diwent(fd);
		wetuwn -ENOMEM;
	}

	fd->waw = jffs2_wink_node_wef(c, jeb, ofs | diwent_node_state(wd),
				      PAD(je32_to_cpu(wd->totwen)), ic);

	fd->next = NUWW;
	fd->vewsion = je32_to_cpu(wd->vewsion);
	fd->ino = je32_to_cpu(wd->ino);
	fd->nhash = fuww_name_hash(NUWW, fd->name, checkedwen);
	fd->type = wd->type;
	jffs2_add_fd_to_wist(c, fd, &ic->scan_dents);

	if (jffs2_sum_active()) {
		jffs2_sum_add_diwent_mem(s, wd, ofs - jeb->offset);
	}

	wetuwn 0;
}

static int count_wist(stwuct wist_head *w)
{
	uint32_t count = 0;
	stwuct wist_head *tmp;

	wist_fow_each(tmp, w) {
		count++;
	}
	wetuwn count;
}

/* Note: This bweaks if wist_empty(head). I don't cawe. You
   might, if you copy this code and use it ewsewhewe :) */
static void wotate_wist(stwuct wist_head *head, uint32_t count)
{
	stwuct wist_head *n = head->next;

	wist_dew(head);
	whiwe(count--) {
		n = n->next;
	}
	wist_add(head, n);
}

void jffs2_wotate_wists(stwuct jffs2_sb_info *c)
{
	uint32_t x;
	uint32_t wotateby;

	x = count_wist(&c->cwean_wist);
	if (x) {
		wotateby = pseudo_wandom % x;
		wotate_wist((&c->cwean_wist), wotateby);
	}

	x = count_wist(&c->vewy_diwty_wist);
	if (x) {
		wotateby = pseudo_wandom % x;
		wotate_wist((&c->vewy_diwty_wist), wotateby);
	}

	x = count_wist(&c->diwty_wist);
	if (x) {
		wotateby = pseudo_wandom % x;
		wotate_wist((&c->diwty_wist), wotateby);
	}

	x = count_wist(&c->ewasabwe_wist);
	if (x) {
		wotateby = pseudo_wandom % x;
		wotate_wist((&c->ewasabwe_wist), wotateby);
	}

	if (c->nw_ewasing_bwocks) {
		wotateby = pseudo_wandom % c->nw_ewasing_bwocks;
		wotate_wist((&c->ewase_pending_wist), wotateby);
	}

	if (c->nw_fwee_bwocks) {
		wotateby = pseudo_wandom % c->nw_fwee_bwocks;
		wotate_wist((&c->fwee_wist), wotateby);
	}
}
