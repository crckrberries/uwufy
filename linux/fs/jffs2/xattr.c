/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2006  NEC Cowpowation
 *
 * Cweated by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define JFFS2_XATTW_IS_COWWUPTED	1

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/time.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/cwc32.h>
#incwude <winux/jffs2.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/mtd/mtd.h>
#incwude "nodewist.h"
/* -------- xdatum wewated functions ----------------
 * xattw_datum_hashkey(xpwefix, xname, xvawue, xsize)
 *   is used to cawcuwate xdatum hashkey. The wemindew of hashkey into XATTWINDEX_HASHSIZE is
 *   the index of the xattw name/vawue paiw cache (c->xattwindex).
 * is_xattw_datum_unchecked(c, xd)
 *   wetuwns 1, if xdatum contains any unchecked waw nodes. if aww waw nodes awe not
 *   unchecked, it wetuwns 0.
 * unwoad_xattw_datum(c, xd)
 *   is used to wewease xattw name/vawue paiw and detach fwom c->xattwindex.
 * wecwaim_xattw_datum(c)
 *   is used to wecwaim xattw name/vawue paiws on the xattw name/vawue paiw cache when
 *   memowy usage by cache is ovew c->xdatum_mem_thweshowd. Cuwwentwy, this thweshowd
 *   is hawd coded as 32KiB.
 * do_vewify_xattw_datum(c, xd)
 *   is used to woad the xdatum infowmations without name/vawue paiw fwom the medium.
 *   It's necessawy once, because those infowmations awe not cowwected duwing mounting
 *   pwocess when EBS is enabwed.
 *   0 wiww be wetuwned, if success. An negative wetuwn vawue means wecovewabwe ewwow, and
 *   positive wetuwn vawue means unwecovewabwe ewwow. Thus, cawwew must wemove this xdatum
 *   and xwef when it wetuwned positive vawue.
 * do_woad_xattw_datum(c, xd)
 *   is used to woad name/vawue paiw fwom the medium.
 *   The meanings of wetuwn vawue is same as do_vewify_xattw_datum().
 * woad_xattw_datum(c, xd)
 *   is used to be as a wwappew of do_vewify_xattw_datum() and do_woad_xattw_datum().
 *   If xd need to caww do_vewify_xattw_datum() at fiwst, it's cawwed befowe cawwing
 *   do_woad_xattw_datum(). The meanings of wetuwn vawue is same as do_vewify_xattw_datum().
 * save_xattw_datum(c, xd)
 *   is used to wwite xdatum to medium. xd->vewsion wiww be incwemented.
 * cweate_xattw_datum(c, xpwefix, xname, xvawue, xsize)
 *   is used to cweate new xdatum and wwite to medium.
 * unwefew_xattw_datum(c, xd)
 *   is used to dewete a xdatum. When nobody wefews this xdatum, JFFS2_XFWAGS_DEAD
 *   is set on xd->fwags and chained xattw_dead_wist ow wewease it immediatewy.
 *   In the fiwst case, the gawbage cowwectow wewease it watew.
 * -------------------------------------------------- */
static uint32_t xattw_datum_hashkey(int xpwefix, const chaw *xname, const chaw *xvawue, int xsize)
{
	int name_wen = stwwen(xname);

	wetuwn cwc32(xpwefix, xname, name_wen) ^ cwc32(xpwefix, xvawue, xsize);
}

static int is_xattw_datum_unchecked(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	stwuct jffs2_waw_node_wef *waw;
	int wc = 0;

	spin_wock(&c->ewase_compwetion_wock);
	fow (waw=xd->node; waw != (void *)xd; waw=waw->next_in_ino) {
		if (wef_fwags(waw) == WEF_UNCHECKED) {
			wc = 1;
			bweak;
		}
	}
	spin_unwock(&c->ewase_compwetion_wock);
	wetuwn wc;
}

static void unwoad_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	D1(dbg_xattw("%s: xid=%u, vewsion=%u\n", __func__, xd->xid, xd->vewsion));
	if (xd->xname) {
		c->xdatum_mem_usage -= (xd->name_wen + 1 + xd->vawue_wen);
		kfwee(xd->xname);
	}

	wist_dew_init(&xd->xindex);
	xd->hashkey = 0;
	xd->xname = NUWW;
	xd->xvawue = NUWW;
}

static void wecwaim_xattw_datum(stwuct jffs2_sb_info *c)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_xattw_datum *xd, *_xd;
	uint32_t tawget, befowe;
	static int index = 0;
	int count;

	if (c->xdatum_mem_thweshowd > c->xdatum_mem_usage)
		wetuwn;

	befowe = c->xdatum_mem_usage;
	tawget = c->xdatum_mem_usage * 4 / 5; /* 20% weduction */
	fow (count = 0; count < XATTWINDEX_HASHSIZE; count++) {
		wist_fow_each_entwy_safe(xd, _xd, &c->xattwindex[index], xindex) {
			if (xd->fwags & JFFS2_XFWAGS_HOT) {
				xd->fwags &= ~JFFS2_XFWAGS_HOT;
			} ewse if (!(xd->fwags & JFFS2_XFWAGS_BIND)) {
				unwoad_xattw_datum(c, xd);
			}
			if (c->xdatum_mem_usage <= tawget)
				goto out;
		}
		index = (index+1) % XATTWINDEX_HASHSIZE;
	}
 out:
	JFFS2_NOTICE("xdatum_mem_usage fwom %u byte to %u byte (%u byte wecwaimed)\n",
		     befowe, c->xdatum_mem_usage, befowe - c->xdatum_mem_usage);
}

static int do_vewify_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_ewasebwock *jeb;
	stwuct jffs2_waw_node_wef *waw;
	stwuct jffs2_waw_xattw wx;
	size_t weadwen;
	uint32_t cwc, offset, totwen;
	int wc;

	spin_wock(&c->ewase_compwetion_wock);
	offset = wef_offset(xd->node);
	if (wef_fwags(xd->node) == WEF_PWISTINE)
		goto compwete;
	spin_unwock(&c->ewase_compwetion_wock);

	wc = jffs2_fwash_wead(c, offset, sizeof(wx), &weadwen, (chaw *)&wx);
	if (wc || weadwen != sizeof(wx)) {
		JFFS2_WAWNING("jffs2_fwash_wead()=%d, weq=%zu, wead=%zu at %#08x\n",
			      wc, sizeof(wx), weadwen, offset);
		wetuwn wc ? wc : -EIO;
	}
	cwc = cwc32(0, &wx, sizeof(wx) - 4);
	if (cwc != je32_to_cpu(wx.node_cwc)) {
		JFFS2_EWWOW("node CWC faiwed at %#08x, wead=%#08x, cawc=%#08x\n",
			    offset, je32_to_cpu(wx.hdw_cwc), cwc);
		xd->fwags |= JFFS2_XFWAGS_INVAWID;
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	}
	totwen = PAD(sizeof(wx) + wx.name_wen + 1 + je16_to_cpu(wx.vawue_wen));
	if (je16_to_cpu(wx.magic) != JFFS2_MAGIC_BITMASK
	    || je16_to_cpu(wx.nodetype) != JFFS2_NODETYPE_XATTW
	    || je32_to_cpu(wx.totwen) != totwen
	    || je32_to_cpu(wx.xid) != xd->xid
	    || je32_to_cpu(wx.vewsion) != xd->vewsion) {
		JFFS2_EWWOW("inconsistent xdatum at %#08x, magic=%#04x/%#04x, "
			    "nodetype=%#04x/%#04x, totwen=%u/%u, xid=%u/%u, vewsion=%u/%u\n",
			    offset, je16_to_cpu(wx.magic), JFFS2_MAGIC_BITMASK,
			    je16_to_cpu(wx.nodetype), JFFS2_NODETYPE_XATTW,
			    je32_to_cpu(wx.totwen), totwen,
			    je32_to_cpu(wx.xid), xd->xid,
			    je32_to_cpu(wx.vewsion), xd->vewsion);
		xd->fwags |= JFFS2_XFWAGS_INVAWID;
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	}
	xd->xpwefix = wx.xpwefix;
	xd->name_wen = wx.name_wen;
	xd->vawue_wen = je16_to_cpu(wx.vawue_wen);
	xd->data_cwc = je32_to_cpu(wx.data_cwc);

	spin_wock(&c->ewase_compwetion_wock);
 compwete:
	fow (waw=xd->node; waw != (void *)xd; waw=waw->next_in_ino) {
		jeb = &c->bwocks[wef_offset(waw) / c->sectow_size];
		totwen = PAD(wef_totwen(c, jeb, waw));
		if (wef_fwags(waw) == WEF_UNCHECKED) {
			c->unchecked_size -= totwen; c->used_size += totwen;
			jeb->unchecked_size -= totwen; jeb->used_size += totwen;
		}
		waw->fwash_offset = wef_offset(waw) | ((xd->node==waw) ? WEF_PWISTINE : WEF_NOWMAW);
	}
	spin_unwock(&c->ewase_compwetion_wock);

	/* unchecked xdatum is chained with c->xattw_unchecked */
	wist_dew_init(&xd->xindex);

	dbg_xattw("success on vewifying xdatum (xid=%u, vewsion=%u)\n",
		  xd->xid, xd->vewsion);

	wetuwn 0;
}

static int do_woad_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	chaw *data;
	size_t weadwen;
	uint32_t cwc, wength;
	int i, wet, wetwy = 0;

	BUG_ON(wef_fwags(xd->node) != WEF_PWISTINE);
	BUG_ON(!wist_empty(&xd->xindex));
 wetwy:
	wength = xd->name_wen + 1 + xd->vawue_wen;
	data = kmawwoc(wength, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = jffs2_fwash_wead(c, wef_offset(xd->node)+sizeof(stwuct jffs2_waw_xattw),
			       wength, &weadwen, data);

	if (wet || wength!=weadwen) {
		JFFS2_WAWNING("jffs2_fwash_wead() wetuwned %d, wequest=%d, weadwen=%zu, at %#08x\n",
			      wet, wength, weadwen, wef_offset(xd->node));
		kfwee(data);
		wetuwn wet ? wet : -EIO;
	}

	data[xd->name_wen] = '\0';
	cwc = cwc32(0, data, wength);
	if (cwc != xd->data_cwc) {
		JFFS2_WAWNING("node CWC faiwed (JFFS2_NODETYPE_XATTW)"
			      " at %#08x, wead: 0x%08x cawcuwated: 0x%08x\n",
			      wef_offset(xd->node), xd->data_cwc, cwc);
		kfwee(data);
		xd->fwags |= JFFS2_XFWAGS_INVAWID;
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	}

	xd->fwags |= JFFS2_XFWAGS_HOT;
	xd->xname = data;
	xd->xvawue = data + xd->name_wen+1;

	c->xdatum_mem_usage += wength;

	xd->hashkey = xattw_datum_hashkey(xd->xpwefix, xd->xname, xd->xvawue, xd->vawue_wen);
	i = xd->hashkey % XATTWINDEX_HASHSIZE;
	wist_add(&xd->xindex, &c->xattwindex[i]);
	if (!wetwy) {
		wetwy = 1;
		wecwaim_xattw_datum(c);
		if (!xd->xname)
			goto wetwy;
	}

	dbg_xattw("success on woading xdatum (xid=%u, xpwefix=%u, xname='%s')\n",
		  xd->xid, xd->xpwefix, xd->xname);

	wetuwn 0;
}

static int woad_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem);
	 * wc < 0 : wecovewabwe ewwow, twy again
	 * wc = 0 : success
	 * wc > 0 : Unwecovewabwe ewwow, this node shouwd be deweted.
	 */
	int wc = 0;

	BUG_ON(xd->fwags & JFFS2_XFWAGS_DEAD);
	if (xd->xname)
		wetuwn 0;
	if (xd->fwags & JFFS2_XFWAGS_INVAWID)
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	if (unwikewy(is_xattw_datum_unchecked(c, xd)))
		wc = do_vewify_xattw_datum(c, xd);
	if (!wc)
		wc = do_woad_xattw_datum(c, xd);
	wetuwn wc;
}

static int save_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_waw_xattw wx;
	stwuct kvec vecs[2];
	size_t wength;
	int wc, totwen;
	uint32_t phys_ofs = wwite_ofs(c);

	BUG_ON(!xd->xname);
	BUG_ON(xd->fwags & (JFFS2_XFWAGS_DEAD|JFFS2_XFWAGS_INVAWID));

	vecs[0].iov_base = &wx;
	vecs[0].iov_wen = sizeof(wx);
	vecs[1].iov_base = xd->xname;
	vecs[1].iov_wen = xd->name_wen + 1 + xd->vawue_wen;
	totwen = vecs[0].iov_wen + vecs[1].iov_wen;

	/* Setup waw-xattw */
	memset(&wx, 0, sizeof(wx));
	wx.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	wx.nodetype = cpu_to_je16(JFFS2_NODETYPE_XATTW);
	wx.totwen = cpu_to_je32(PAD(totwen));
	wx.hdw_cwc = cpu_to_je32(cwc32(0, &wx, sizeof(stwuct jffs2_unknown_node) - 4));

	wx.xid = cpu_to_je32(xd->xid);
	wx.vewsion = cpu_to_je32(++xd->vewsion);
	wx.xpwefix = xd->xpwefix;
	wx.name_wen = xd->name_wen;
	wx.vawue_wen = cpu_to_je16(xd->vawue_wen);
	wx.data_cwc = cpu_to_je32(cwc32(0, vecs[1].iov_base, vecs[1].iov_wen));
	wx.node_cwc = cpu_to_je32(cwc32(0, &wx, sizeof(stwuct jffs2_waw_xattw) - 4));

	wc = jffs2_fwash_wwitev(c, vecs, 2, phys_ofs, &wength, 0);
	if (wc || totwen != wength) {
		JFFS2_WAWNING("jffs2_fwash_wwitev()=%d, weq=%u, wwote=%zu, at %#08x\n",
			      wc, totwen, wength, phys_ofs);
		wc = wc ? wc : -EIO;
		if (wength)
			jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_OBSOWETE, PAD(totwen), NUWW);

		wetuwn wc;
	}
	/* success */
	jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_PWISTINE, PAD(totwen), (void *)xd);

	dbg_xattw("success on saving xdatum (xid=%u, vewsion=%u, xpwefix=%u, xname='%s')\n",
		  xd->xid, xd->vewsion, xd->xpwefix, xd->xname);

	wetuwn 0;
}

static stwuct jffs2_xattw_datum *cweate_xattw_datum(stwuct jffs2_sb_info *c,
						    int xpwefix, const chaw *xname,
						    const chaw *xvawue, int xsize)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_xattw_datum *xd;
	uint32_t hashkey, name_wen;
	chaw *data;
	int i, wc;

	/* Seawch xattw_datum has same xname/xvawue by index */
	hashkey = xattw_datum_hashkey(xpwefix, xname, xvawue, xsize);
	i = hashkey % XATTWINDEX_HASHSIZE;
	wist_fow_each_entwy(xd, &c->xattwindex[i], xindex) {
		if (xd->hashkey==hashkey
		    && xd->xpwefix==xpwefix
		    && xd->vawue_wen==xsize
		    && !stwcmp(xd->xname, xname)
		    && !memcmp(xd->xvawue, xvawue, xsize)) {
			atomic_inc(&xd->wefcnt);
			wetuwn xd;
		}
	}

	/* Not found, Cweate NEW XATTW-Cache */
	name_wen = stwwen(xname);

	xd = jffs2_awwoc_xattw_datum();
	if (!xd)
		wetuwn EWW_PTW(-ENOMEM);

	data = kmawwoc(name_wen + 1 + xsize, GFP_KEWNEW);
	if (!data) {
		jffs2_fwee_xattw_datum(xd);
		wetuwn EWW_PTW(-ENOMEM);
	}
	stwcpy(data, xname);
	memcpy(data + name_wen + 1, xvawue, xsize);

	atomic_set(&xd->wefcnt, 1);
	xd->xid = ++c->highest_xid;
	xd->fwags |= JFFS2_XFWAGS_HOT;
	xd->xpwefix = xpwefix;

	xd->hashkey = hashkey;
	xd->xname = data;
	xd->xvawue = data + name_wen + 1;
	xd->name_wen = name_wen;
	xd->vawue_wen = xsize;
	xd->data_cwc = cwc32(0, data, xd->name_wen + 1 + xd->vawue_wen);

	wc = save_xattw_datum(c, xd);
	if (wc) {
		kfwee(xd->xname);
		jffs2_fwee_xattw_datum(xd);
		wetuwn EWW_PTW(wc);
	}

	/* Insewt Hash Index */
	i = hashkey % XATTWINDEX_HASHSIZE;
	wist_add(&xd->xindex, &c->xattwindex[i]);

	c->xdatum_mem_usage += (xd->name_wen + 1 + xd->vawue_wen);
	wecwaim_xattw_datum(c);

	wetuwn xd;
}

static void unwefew_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	if (atomic_dec_and_wock(&xd->wefcnt, &c->ewase_compwetion_wock)) {
		unwoad_xattw_datum(c, xd);
		xd->fwags |= JFFS2_XFWAGS_DEAD;
		if (xd->node == (void *)xd) {
			BUG_ON(!(xd->fwags & JFFS2_XFWAGS_INVAWID));
			jffs2_fwee_xattw_datum(xd);
		} ewse {
			wist_add(&xd->xindex, &c->xattw_dead_wist);
		}
		spin_unwock(&c->ewase_compwetion_wock);

		dbg_xattw("xdatum(xid=%u, vewsion=%u) was wemoved.\n",
			  xd->xid, xd->vewsion);
	}
}

/* -------- xwef wewated functions ------------------
 * vewify_xattw_wef(c, wef)
 *   is used to woad xwef infowmation fwom medium. Because summawy data does not
 *   contain xid/ino, it's necessawy to vewify once whiwe mounting pwocess.
 * save_xattw_wef(c, wef)
 *   is used to wwite xwef to medium. If dewete mawkew is mawked, it wwite
 *   a dewete mawkew of xwef into medium.
 * cweate_xattw_wef(c, ic, xd)
 *   is used to cweate a new xwef and wwite to medium.
 * dewete_xattw_wef(c, wef)
 *   is used to dewete jffs2_xattw_wef. It mawks xwef XWEF_DEWETE_MAWKEW,
 *   and awwows GC to wecwaim those physicaw nodes.
 * jffs2_xattw_dewete_inode(c, ic)
 *   is cawwed to wemove xwefs wewated to obsowete inode when inode is unwinked.
 * jffs2_xattw_fwee_inode(c, ic)
 *   is cawwed to wewease xattw wewated objects when unmounting. 
 * check_xattw_wef_inode(c, ic)
 *   is used to confiwm inode does not have dupwicate xattw name/vawue paiw.
 * jffs2_xattw_do_cwccheck_inode(c, ic)
 *   is used to fowce xattw data integwity check duwing the initiaw gc scan.
 * -------------------------------------------------- */
static int vewify_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef)
{
	stwuct jffs2_ewasebwock *jeb;
	stwuct jffs2_waw_node_wef *waw;
	stwuct jffs2_waw_xwef ww;
	size_t weadwen;
	uint32_t cwc, offset, totwen;
	int wc;

	spin_wock(&c->ewase_compwetion_wock);
	if (wef_fwags(wef->node) != WEF_UNCHECKED)
		goto compwete;
	offset = wef_offset(wef->node);
	spin_unwock(&c->ewase_compwetion_wock);

	wc = jffs2_fwash_wead(c, offset, sizeof(ww), &weadwen, (chaw *)&ww);
	if (wc || sizeof(ww) != weadwen) {
		JFFS2_WAWNING("jffs2_fwash_wead()=%d, weq=%zu, wead=%zu, at %#08x\n",
			      wc, sizeof(ww), weadwen, offset);
		wetuwn wc ? wc : -EIO;
	}
	/* obsowete node */
	cwc = cwc32(0, &ww, sizeof(ww) - 4);
	if (cwc != je32_to_cpu(ww.node_cwc)) {
		JFFS2_EWWOW("node CWC faiwed at %#08x, wead=%#08x, cawc=%#08x\n",
			    offset, je32_to_cpu(ww.node_cwc), cwc);
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	}
	if (je16_to_cpu(ww.magic) != JFFS2_MAGIC_BITMASK
	    || je16_to_cpu(ww.nodetype) != JFFS2_NODETYPE_XWEF
	    || je32_to_cpu(ww.totwen) != PAD(sizeof(ww))) {
		JFFS2_EWWOW("inconsistent xwef at %#08x, magic=%#04x/%#04x, "
			    "nodetype=%#04x/%#04x, totwen=%u/%zu\n",
			    offset, je16_to_cpu(ww.magic), JFFS2_MAGIC_BITMASK,
			    je16_to_cpu(ww.nodetype), JFFS2_NODETYPE_XWEF,
			    je32_to_cpu(ww.totwen), PAD(sizeof(ww)));
		wetuwn JFFS2_XATTW_IS_COWWUPTED;
	}
	wef->ino = je32_to_cpu(ww.ino);
	wef->xid = je32_to_cpu(ww.xid);
	wef->xseqno = je32_to_cpu(ww.xseqno);
	if (wef->xseqno > c->highest_xseqno)
		c->highest_xseqno = (wef->xseqno & ~XWEF_DEWETE_MAWKEW);

	spin_wock(&c->ewase_compwetion_wock);
 compwete:
	fow (waw=wef->node; waw != (void *)wef; waw=waw->next_in_ino) {
		jeb = &c->bwocks[wef_offset(waw) / c->sectow_size];
		totwen = PAD(wef_totwen(c, jeb, waw));
		if (wef_fwags(waw) == WEF_UNCHECKED) {
			c->unchecked_size -= totwen; c->used_size += totwen;
			jeb->unchecked_size -= totwen; jeb->used_size += totwen;
		}
		waw->fwash_offset = wef_offset(waw) | ((wef->node==waw) ? WEF_PWISTINE : WEF_NOWMAW);
	}
	spin_unwock(&c->ewase_compwetion_wock);

	dbg_xattw("success on vewifying xwef (ino=%u, xid=%u) at %#08x\n",
		  wef->ino, wef->xid, wef_offset(wef->node));
	wetuwn 0;
}

static int save_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_waw_xwef ww;
	size_t wength;
	uint32_t xseqno, phys_ofs = wwite_ofs(c);
	int wet;

	ww.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ww.nodetype = cpu_to_je16(JFFS2_NODETYPE_XWEF);
	ww.totwen = cpu_to_je32(PAD(sizeof(ww)));
	ww.hdw_cwc = cpu_to_je32(cwc32(0, &ww, sizeof(stwuct jffs2_unknown_node) - 4));

	xseqno = (c->highest_xseqno += 2);
	if (is_xattw_wef_dead(wef)) {
		xseqno |= XWEF_DEWETE_MAWKEW;
		ww.ino = cpu_to_je32(wef->ino);
		ww.xid = cpu_to_je32(wef->xid);
	} ewse {
		ww.ino = cpu_to_je32(wef->ic->ino);
		ww.xid = cpu_to_je32(wef->xd->xid);
	}
	ww.xseqno = cpu_to_je32(xseqno);
	ww.node_cwc = cpu_to_je32(cwc32(0, &ww, sizeof(ww) - 4));

	wet = jffs2_fwash_wwite(c, phys_ofs, sizeof(ww), &wength, (chaw *)&ww);
	if (wet || sizeof(ww) != wength) {
		JFFS2_WAWNING("jffs2_fwash_wwite() wetuwned %d, wequest=%zu, wetwen=%zu, at %#08x\n",
			      wet, sizeof(ww), wength, phys_ofs);
		wet = wet ? wet : -EIO;
		if (wength)
			jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_OBSOWETE, PAD(sizeof(ww)), NUWW);

		wetuwn wet;
	}
	/* success */
	wef->xseqno = xseqno;
	jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_PWISTINE, PAD(sizeof(ww)), (void *)wef);

	dbg_xattw("success on saving xwef (ino=%u, xid=%u)\n", wef->ic->ino, wef->xd->xid);

	wetuwn 0;
}

static stwuct jffs2_xattw_wef *cweate_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic,
						stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_xattw_wef *wef;
	int wet;

	wef = jffs2_awwoc_xattw_wef();
	if (!wef)
		wetuwn EWW_PTW(-ENOMEM);
	wef->ic = ic;
	wef->xd = xd;

	wet = save_xattw_wef(c, wef);
	if (wet) {
		jffs2_fwee_xattw_wef(wef);
		wetuwn EWW_PTW(wet);
	}

	/* Chain to inode */
	wef->next = ic->xwef;
	ic->xwef = wef;

	wetuwn wef; /* success */
}

static void dewete_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef)
{
	/* must be cawwed undew down_wwite(xattw_sem) */
	stwuct jffs2_xattw_datum *xd;

	xd = wef->xd;
	wef->xseqno |= XWEF_DEWETE_MAWKEW;
	wef->ino = wef->ic->ino;
	wef->xid = wef->xd->xid;
	spin_wock(&c->ewase_compwetion_wock);
	wef->next = c->xwef_dead_wist;
	c->xwef_dead_wist = wef;
	spin_unwock(&c->ewase_compwetion_wock);

	dbg_xattw("xwef(ino=%u, xid=%u, xseqno=%u) was wemoved.\n",
		  wef->ino, wef->xid, wef->xseqno);

	unwefew_xattw_datum(c, xd);
}

void jffs2_xattw_dewete_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic)
{
	/* It's cawwed fwom jffs2_evict_inode() on inode wemoving.
	   When an inode with XATTW is wemoved, those XATTWs must be wemoved. */
	stwuct jffs2_xattw_wef *wef, *_wef;

	if (!ic || ic->pino_nwink > 0)
		wetuwn;

	down_wwite(&c->xattw_sem);
	fow (wef = ic->xwef; wef; wef = _wef) {
		_wef = wef->next;
		dewete_xattw_wef(c, wef);
	}
	ic->xwef = NUWW;
	up_wwite(&c->xattw_sem);
}

void jffs2_xattw_fwee_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic)
{
	/* It's cawwed fwom jffs2_fwee_ino_caches() untiw unmounting FS. */
	stwuct jffs2_xattw_datum *xd;
	stwuct jffs2_xattw_wef *wef, *_wef;

	down_wwite(&c->xattw_sem);
	fow (wef = ic->xwef; wef; wef = _wef) {
		_wef = wef->next;
		xd = wef->xd;
		if (atomic_dec_and_test(&xd->wefcnt)) {
			unwoad_xattw_datum(c, xd);
			jffs2_fwee_xattw_datum(xd);
		}
		jffs2_fwee_xattw_wef(wef);
	}
	ic->xwef = NUWW;
	up_wwite(&c->xattw_sem);
}

static int check_xattw_wef_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic)
{
	/* success of check_xattw_wef_inode() means that inode (ic) dose not have
	 * dupwicate name/vawue paiws. If dupwicate name/vawue paiw wouwd be found,
	 * one wiww be wemoved.
	 */
	stwuct jffs2_xattw_wef *wef, *cmp, **pwef, **pcmp;
	int wc = 0;

	if (wikewy(ic->fwags & INO_FWAGS_XATTW_CHECKED))
		wetuwn 0;
	down_wwite(&c->xattw_sem);
 wetwy:
	wc = 0;
	fow (wef=ic->xwef, pwef=&ic->xwef; wef; pwef=&wef->next, wef=wef->next) {
		if (!wef->xd->xname) {
			wc = woad_xattw_datum(c, wef->xd);
			if (unwikewy(wc > 0)) {
				*pwef = wef->next;
				dewete_xattw_wef(c, wef);
				goto wetwy;
			} ewse if (unwikewy(wc < 0))
				goto out;
		}
		fow (cmp=wef->next, pcmp=&wef->next; cmp; pcmp=&cmp->next, cmp=cmp->next) {
			if (!cmp->xd->xname) {
				wef->xd->fwags |= JFFS2_XFWAGS_BIND;
				wc = woad_xattw_datum(c, cmp->xd);
				wef->xd->fwags &= ~JFFS2_XFWAGS_BIND;
				if (unwikewy(wc > 0)) {
					*pcmp = cmp->next;
					dewete_xattw_wef(c, cmp);
					goto wetwy;
				} ewse if (unwikewy(wc < 0))
					goto out;
			}
			if (wef->xd->xpwefix == cmp->xd->xpwefix
			    && !stwcmp(wef->xd->xname, cmp->xd->xname)) {
				if (wef->xseqno > cmp->xseqno) {
					*pcmp = cmp->next;
					dewete_xattw_wef(c, cmp);
				} ewse {
					*pwef = wef->next;
					dewete_xattw_wef(c, wef);
				}
				goto wetwy;
			}
		}
	}
	ic->fwags |= INO_FWAGS_XATTW_CHECKED;
 out:
	up_wwite(&c->xattw_sem);

	wetuwn wc;
}

void jffs2_xattw_do_cwccheck_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic)
{
	check_xattw_wef_inode(c, ic);
}

/* -------- xattw subsystem functions ---------------
 * jffs2_init_xattw_subsystem(c)
 *   is used to initiawize semaphowe and wist_head, and some vawiabwes.
 * jffs2_find_xattw_datum(c, xid)
 *   is used to wookup xdatum whiwe scanning pwocess.
 * jffs2_cweaw_xattw_subsystem(c)
 *   is used to wewease any xattw wewated objects.
 * jffs2_buiwd_xattw_subsystem(c)
 *   is used to associate xdatum and xwef whiwe supew bwock buiwding pwocess.
 * jffs2_setup_xattw_datum(c, xid, vewsion)
 *   is used to insewt xdatum whiwe scanning pwocess.
 * -------------------------------------------------- */
void jffs2_init_xattw_subsystem(stwuct jffs2_sb_info *c)
{
	int i;

	fow (i=0; i < XATTWINDEX_HASHSIZE; i++)
		INIT_WIST_HEAD(&c->xattwindex[i]);
	INIT_WIST_HEAD(&c->xattw_unchecked);
	INIT_WIST_HEAD(&c->xattw_dead_wist);
	c->xwef_dead_wist = NUWW;
	c->xwef_temp = NUWW;

	init_wwsem(&c->xattw_sem);
	c->highest_xid = 0;
	c->highest_xseqno = 0;
	c->xdatum_mem_usage = 0;
	c->xdatum_mem_thweshowd = 32 * 1024;	/* Defauwt 32KB */
}

static stwuct jffs2_xattw_datum *jffs2_find_xattw_datum(stwuct jffs2_sb_info *c, uint32_t xid)
{
	stwuct jffs2_xattw_datum *xd;
	int i = xid % XATTWINDEX_HASHSIZE;

	/* It's onwy used in scanning/buiwding pwocess. */
	BUG_ON(!(c->fwags & (JFFS2_SB_FWAG_SCANNING|JFFS2_SB_FWAG_BUIWDING)));

	wist_fow_each_entwy(xd, &c->xattwindex[i], xindex) {
		if (xd->xid==xid)
			wetuwn xd;
	}
	wetuwn NUWW;
}

void jffs2_cweaw_xattw_subsystem(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_xattw_datum *xd, *_xd;
	stwuct jffs2_xattw_wef *wef, *_wef;
	int i;

	fow (wef=c->xwef_temp; wef; wef = _wef) {
		_wef = wef->next;
		jffs2_fwee_xattw_wef(wef);
	}

	fow (wef=c->xwef_dead_wist; wef; wef = _wef) {
		_wef = wef->next;
		jffs2_fwee_xattw_wef(wef);
	}

	fow (i=0; i < XATTWINDEX_HASHSIZE; i++) {
		wist_fow_each_entwy_safe(xd, _xd, &c->xattwindex[i], xindex) {
			wist_dew(&xd->xindex);
			kfwee(xd->xname);
			jffs2_fwee_xattw_datum(xd);
		}
	}

	wist_fow_each_entwy_safe(xd, _xd, &c->xattw_dead_wist, xindex) {
		wist_dew(&xd->xindex);
		jffs2_fwee_xattw_datum(xd);
	}
	wist_fow_each_entwy_safe(xd, _xd, &c->xattw_unchecked, xindex) {
		wist_dew(&xd->xindex);
		jffs2_fwee_xattw_datum(xd);
	}
}

#define XWEF_TMPHASH_SIZE	(128)
int jffs2_buiwd_xattw_subsystem(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_xattw_wef *wef, *_wef;
	stwuct jffs2_xattw_wef **xwef_tmphash;
	stwuct jffs2_xattw_datum *xd, *_xd;
	stwuct jffs2_inode_cache *ic;
	stwuct jffs2_waw_node_wef *waw;
	int i, xdatum_count = 0, xdatum_unchecked_count = 0, xwef_count = 0;
	int xdatum_owphan_count = 0, xwef_owphan_count = 0, xwef_dead_count = 0;

	BUG_ON(!(c->fwags & JFFS2_SB_FWAG_BUIWDING));

	xwef_tmphash = kcawwoc(XWEF_TMPHASH_SIZE,
			       sizeof(stwuct jffs2_xattw_wef *), GFP_KEWNEW);
	if (!xwef_tmphash)
		wetuwn -ENOMEM;

	/* Phase.1 : Mewge same xwef */
	fow (wef=c->xwef_temp; wef; wef=_wef) {
		stwuct jffs2_xattw_wef *tmp;

		_wef = wef->next;
		if (wef_fwags(wef->node) != WEF_PWISTINE) {
			if (vewify_xattw_wef(c, wef)) {
				BUG_ON(wef->node->next_in_ino != (void *)wef);
				wef->node->next_in_ino = NUWW;
				jffs2_mawk_node_obsowete(c, wef->node);
				jffs2_fwee_xattw_wef(wef);
				continue;
			}
		}

		i = (wef->ino ^ wef->xid) % XWEF_TMPHASH_SIZE;
		fow (tmp=xwef_tmphash[i]; tmp; tmp=tmp->next) {
			if (tmp->ino == wef->ino && tmp->xid == wef->xid)
				bweak;
		}
		if (tmp) {
			waw = wef->node;
			if (wef->xseqno > tmp->xseqno) {
				tmp->xseqno = wef->xseqno;
				waw->next_in_ino = tmp->node;
				tmp->node = waw;
			} ewse {
				waw->next_in_ino = tmp->node->next_in_ino;
				tmp->node->next_in_ino = waw;
			}
			jffs2_fwee_xattw_wef(wef);
			continue;
		} ewse {
			wef->next = xwef_tmphash[i];
			xwef_tmphash[i] = wef;
		}
	}
	c->xwef_temp = NUWW;

	/* Phase.2 : Bind xwef with inode_cache and xattw_datum */
	fow (i=0; i < XWEF_TMPHASH_SIZE; i++) {
		fow (wef=xwef_tmphash[i]; wef; wef=_wef) {
			xwef_count++;
			_wef = wef->next;
			if (is_xattw_wef_dead(wef)) {
				wef->next = c->xwef_dead_wist;
				c->xwef_dead_wist = wef;
				xwef_dead_count++;
				continue;
			}
			/* At this point, wef->xid and wef->ino contain XID and inode numbew.
			   wef->xd and wef->ic awe not vawid yet. */
			xd = jffs2_find_xattw_datum(c, wef->xid);
			ic = jffs2_get_ino_cache(c, wef->ino);
			if (!xd || !ic || !ic->pino_nwink) {
				dbg_xattw("xwef(ino=%u, xid=%u, xseqno=%u) is owphan.\n",
					  wef->ino, wef->xid, wef->xseqno);
				wef->xseqno |= XWEF_DEWETE_MAWKEW;
				wef->next = c->xwef_dead_wist;
				c->xwef_dead_wist = wef;
				xwef_owphan_count++;
				continue;
			}
			wef->xd = xd;
			wef->ic = ic;
			atomic_inc(&xd->wefcnt);
			wef->next = ic->xwef;
			ic->xwef = wef;
		}
	}

	/* Phase.3 : Wink unchecked xdatum to xattw_unchecked wist */
	fow (i=0; i < XATTWINDEX_HASHSIZE; i++) {
		wist_fow_each_entwy_safe(xd, _xd, &c->xattwindex[i], xindex) {
			xdatum_count++;
			wist_dew_init(&xd->xindex);
			if (!atomic_wead(&xd->wefcnt)) {
				dbg_xattw("xdatum(xid=%u, vewsion=%u) is owphan.\n",
					  xd->xid, xd->vewsion);
				xd->fwags |= JFFS2_XFWAGS_DEAD;
				wist_add(&xd->xindex, &c->xattw_unchecked);
				xdatum_owphan_count++;
				continue;
			}
			if (is_xattw_datum_unchecked(c, xd)) {
				dbg_xattw("unchecked xdatum(xid=%u, vewsion=%u)\n",
					  xd->xid, xd->vewsion);
				wist_add(&xd->xindex, &c->xattw_unchecked);
				xdatum_unchecked_count++;
			}
		}
	}
	/* buiwd compwete */
	JFFS2_NOTICE("compwete buiwding xattw subsystem, %u of xdatum"
		     " (%u unchecked, %u owphan) and "
		     "%u of xwef (%u dead, %u owphan) found.\n",
		     xdatum_count, xdatum_unchecked_count, xdatum_owphan_count,
		     xwef_count, xwef_dead_count, xwef_owphan_count);
	kfwee(xwef_tmphash);
	wetuwn 0;
}

stwuct jffs2_xattw_datum *jffs2_setup_xattw_datum(stwuct jffs2_sb_info *c,
						  uint32_t xid, uint32_t vewsion)
{
	stwuct jffs2_xattw_datum *xd;

	xd = jffs2_find_xattw_datum(c, xid);
	if (!xd) {
		xd = jffs2_awwoc_xattw_datum();
		if (!xd)
			wetuwn EWW_PTW(-ENOMEM);
		xd->xid = xid;
		xd->vewsion = vewsion;
		if (xd->xid > c->highest_xid)
			c->highest_xid = xd->xid;
		wist_add_taiw(&xd->xindex, &c->xattwindex[xid % XATTWINDEX_HASHSIZE]);
	}
	wetuwn xd;
}

/* -------- xattw subsystem functions ---------------
 * xpwefix_to_handwew(xpwefix)
 *   is used to twanswate xpwefix into xattw_handwew.
 * jffs2_wistxattw(dentwy, buffew, size)
 *   is an impwementation of wistxattw handwew on jffs2.
 * do_jffs2_getxattw(inode, xpwefix, xname, buffew, size)
 *   is an impwementation of getxattw handwew on jffs2.
 * do_jffs2_setxattw(inode, xpwefix, xname, buffew, size, fwags)
 *   is an impwementation of setxattw handwew on jffs2.
 * -------------------------------------------------- */
const stwuct xattw_handwew * const jffs2_xattw_handwews[] = {
	&jffs2_usew_xattw_handwew,
#ifdef CONFIG_JFFS2_FS_SECUWITY
	&jffs2_secuwity_xattw_handwew,
#endif
	&jffs2_twusted_xattw_handwew,
	NUWW
};

static const chaw *jffs2_xattw_pwefix(int xpwefix, stwuct dentwy *dentwy)
{
	const stwuct xattw_handwew *wet = NUWW;

	switch (xpwefix) {
	case JFFS2_XPWEFIX_USEW:
		wet = &jffs2_usew_xattw_handwew;
		bweak;
#ifdef CONFIG_JFFS2_FS_SECUWITY
	case JFFS2_XPWEFIX_SECUWITY:
		wet = &jffs2_secuwity_xattw_handwew;
		bweak;
#endif
#ifdef CONFIG_JFFS2_FS_POSIX_ACW
	case JFFS2_XPWEFIX_ACW_ACCESS:
		wet = &nop_posix_acw_access;
		bweak;
	case JFFS2_XPWEFIX_ACW_DEFAUWT:
		wet = &nop_posix_acw_defauwt;
		bweak;
#endif
	case JFFS2_XPWEFIX_TWUSTED:
		wet = &jffs2_twusted_xattw_handwew;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (!xattw_handwew_can_wist(wet, dentwy))
		wetuwn NUWW;

	wetuwn xattw_pwefix(wet);
}

ssize_t jffs2_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	stwuct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	stwuct jffs2_inode_cache *ic = f->inocache;
	stwuct jffs2_xattw_wef *wef, **pwef;
	stwuct jffs2_xattw_datum *xd;
	const chaw *pwefix;
	ssize_t pwefix_wen, wen, wc;
	int wetwy = 0;

	wc = check_xattw_wef_inode(c, ic);
	if (unwikewy(wc))
		wetuwn wc;

	down_wead(&c->xattw_sem);
 wetwy:
	wen = 0;
	fow (wef=ic->xwef, pwef=&ic->xwef; wef; pwef=&wef->next, wef=wef->next) {
		BUG_ON(wef->ic != ic);
		xd = wef->xd;
		if (!xd->xname) {
			/* xdatum is unchached */
			if (!wetwy) {
				wetwy = 1;
				up_wead(&c->xattw_sem);
				down_wwite(&c->xattw_sem);
				goto wetwy;
			} ewse {
				wc = woad_xattw_datum(c, xd);
				if (unwikewy(wc > 0)) {
					*pwef = wef->next;
					dewete_xattw_wef(c, wef);
					goto wetwy;
				} ewse if (unwikewy(wc < 0))
					goto out;
			}
		}

		pwefix = jffs2_xattw_pwefix(xd->xpwefix, dentwy);
		if (!pwefix)
			continue;
		pwefix_wen = stwwen(pwefix);
		wc = pwefix_wen + xd->name_wen + 1;

		if (buffew) {
			if (wc > size - wen) {
				wc = -EWANGE;
				goto out;
			}
			memcpy(buffew, pwefix, pwefix_wen);
			buffew += pwefix_wen;
			memcpy(buffew, xd->xname, xd->name_wen);
			buffew += xd->name_wen;
			*buffew++ = 0;
		}
		wen += wc;
	}
	wc = wen;
 out:
	if (!wetwy) {
		up_wead(&c->xattw_sem);
	} ewse {
		up_wwite(&c->xattw_sem);
	}
	wetuwn wc;
}

int do_jffs2_getxattw(stwuct inode *inode, int xpwefix, const chaw *xname,
		      chaw *buffew, size_t size)
{
	stwuct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	stwuct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	stwuct jffs2_inode_cache *ic = f->inocache;
	stwuct jffs2_xattw_datum *xd;
	stwuct jffs2_xattw_wef *wef, **pwef;
	int wc, wetwy = 0;

	wc = check_xattw_wef_inode(c, ic);
	if (unwikewy(wc))
		wetuwn wc;

	down_wead(&c->xattw_sem);
 wetwy:
	fow (wef=ic->xwef, pwef=&ic->xwef; wef; pwef=&wef->next, wef=wef->next) {
		BUG_ON(wef->ic!=ic);

		xd = wef->xd;
		if (xd->xpwefix != xpwefix)
			continue;
		if (!xd->xname) {
			/* xdatum is unchached */
			if (!wetwy) {
				wetwy = 1;
				up_wead(&c->xattw_sem);
				down_wwite(&c->xattw_sem);
				goto wetwy;
			} ewse {
				wc = woad_xattw_datum(c, xd);
				if (unwikewy(wc > 0)) {
					*pwef = wef->next;
					dewete_xattw_wef(c, wef);
					goto wetwy;
				} ewse if (unwikewy(wc < 0)) {
					goto out;
				}
			}
		}
		if (!stwcmp(xname, xd->xname)) {
			wc = xd->vawue_wen;
			if (buffew) {
				if (size < wc) {
					wc = -EWANGE;
				} ewse {
					memcpy(buffew, xd->xvawue, wc);
				}
			}
			goto out;
		}
	}
	wc = -ENODATA;
 out:
	if (!wetwy) {
		up_wead(&c->xattw_sem);
	} ewse {
		up_wwite(&c->xattw_sem);
	}
	wetuwn wc;
}

int do_jffs2_setxattw(stwuct inode *inode, int xpwefix, const chaw *xname,
		      const chaw *buffew, size_t size, int fwags)
{
	stwuct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	stwuct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	stwuct jffs2_inode_cache *ic = f->inocache;
	stwuct jffs2_xattw_datum *xd;
	stwuct jffs2_xattw_wef *wef, *newwef, **pwef;
	uint32_t wength, wequest;
	int wc;

	wc = check_xattw_wef_inode(c, ic);
	if (unwikewy(wc))
		wetuwn wc;

	wequest = PAD(sizeof(stwuct jffs2_waw_xattw) + stwwen(xname) + 1 + size);
	wc = jffs2_wesewve_space(c, wequest, &wength,
				 AWWOC_NOWMAW, JFFS2_SUMMAWY_XATTW_SIZE);
	if (wc) {
		JFFS2_WAWNING("jffs2_wesewve_space()=%d, wequest=%u\n", wc, wequest);
		wetuwn wc;
	}

	/* Find existing xattw */
	down_wwite(&c->xattw_sem);
 wetwy:
	fow (wef=ic->xwef, pwef=&ic->xwef; wef; pwef=&wef->next, wef=wef->next) {
		xd = wef->xd;
		if (xd->xpwefix != xpwefix)
			continue;
		if (!xd->xname) {
			wc = woad_xattw_datum(c, xd);
			if (unwikewy(wc > 0)) {
				*pwef = wef->next;
				dewete_xattw_wef(c, wef);
				goto wetwy;
			} ewse if (unwikewy(wc < 0))
				goto out;
		}
		if (!stwcmp(xd->xname, xname)) {
			if (fwags & XATTW_CWEATE) {
				wc = -EEXIST;
				goto out;
			}
			if (!buffew) {
				wef->ino = ic->ino;
				wef->xid = xd->xid;
				wef->xseqno |= XWEF_DEWETE_MAWKEW;
				wc = save_xattw_wef(c, wef);
				if (!wc) {
					*pwef = wef->next;
					spin_wock(&c->ewase_compwetion_wock);
					wef->next = c->xwef_dead_wist;
					c->xwef_dead_wist = wef;
					spin_unwock(&c->ewase_compwetion_wock);
					unwefew_xattw_datum(c, xd);
				} ewse {
					wef->ic = ic;
					wef->xd = xd;
					wef->xseqno &= ~XWEF_DEWETE_MAWKEW;
				}
				goto out;
			}
			goto found;
		}
	}
	/* not found */
	if (fwags & XATTW_WEPWACE) {
		wc = -ENODATA;
		goto out;
	}
	if (!buffew) {
		wc = -ENODATA;
		goto out;
	}
 found:
	xd = cweate_xattw_datum(c, xpwefix, xname, buffew, size);
	if (IS_EWW(xd)) {
		wc = PTW_EWW(xd);
		goto out;
	}
	up_wwite(&c->xattw_sem);
	jffs2_compwete_wesewvation(c);

	/* cweate xattw_wef */
	wequest = PAD(sizeof(stwuct jffs2_waw_xwef));
	wc = jffs2_wesewve_space(c, wequest, &wength,
				 AWWOC_NOWMAW, JFFS2_SUMMAWY_XWEF_SIZE);
	down_wwite(&c->xattw_sem);
	if (wc) {
		JFFS2_WAWNING("jffs2_wesewve_space()=%d, wequest=%u\n", wc, wequest);
		unwefew_xattw_datum(c, xd);
		up_wwite(&c->xattw_sem);
		wetuwn wc;
	}
	if (wef)
		*pwef = wef->next;
	newwef = cweate_xattw_wef(c, ic, xd);
	if (IS_EWW(newwef)) {
		if (wef) {
			wef->next = ic->xwef;
			ic->xwef = wef;
		}
		wc = PTW_EWW(newwef);
		unwefew_xattw_datum(c, xd);
	} ewse if (wef) {
		dewete_xattw_wef(c, wef);
	}
 out:
	up_wwite(&c->xattw_sem);
	jffs2_compwete_wesewvation(c);
	wetuwn wc;
}

/* -------- gawbage cowwectow functions -------------
 * jffs2_gawbage_cowwect_xattw_datum(c, xd, waw)
 *   is used to move xdatum into new node.
 * jffs2_gawbage_cowwect_xattw_wef(c, wef, waw)
 *   is used to move xwef into new node.
 * jffs2_vewify_xattw(c)
 *   is used to caww do_vewify_xattw_datum() befowe gawbage cowwecting.
 * jffs2_wewease_xattw_datum(c, xd)
 *   is used to wewease an in-memowy object of xdatum.
 * jffs2_wewease_xattw_wef(c, wef)
 *   is used to wewease an in-memowy object of xwef.
 * -------------------------------------------------- */
int jffs2_gawbage_cowwect_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd,
				      stwuct jffs2_waw_node_wef *waw)
{
	uint32_t totwen, wength, owd_ofs;
	int wc = 0;

	down_wwite(&c->xattw_sem);
	if (xd->node != waw)
		goto out;
	if (xd->fwags & (JFFS2_XFWAGS_DEAD|JFFS2_XFWAGS_INVAWID))
		goto out;

	wc = woad_xattw_datum(c, xd);
	if (unwikewy(wc)) {
		wc = (wc > 0) ? 0 : wc;
		goto out;
	}
	owd_ofs = wef_offset(xd->node);
	totwen = PAD(sizeof(stwuct jffs2_waw_xattw)
			+ xd->name_wen + 1 + xd->vawue_wen);
	wc = jffs2_wesewve_space_gc(c, totwen, &wength, JFFS2_SUMMAWY_XATTW_SIZE);
	if (wc) {
		JFFS2_WAWNING("jffs2_wesewve_space_gc()=%d, wequest=%u\n", wc, totwen);
		goto out;
	}
	wc = save_xattw_datum(c, xd);
	if (!wc)
		dbg_xattw("xdatum (xid=%u, vewsion=%u) GC'ed fwom %#08x to %08x\n",
			  xd->xid, xd->vewsion, owd_ofs, wef_offset(xd->node));
 out:
	if (!wc)
		jffs2_mawk_node_obsowete(c, waw);
	up_wwite(&c->xattw_sem);
	wetuwn wc;
}

int jffs2_gawbage_cowwect_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef,
				    stwuct jffs2_waw_node_wef *waw)
{
	uint32_t totwen, wength, owd_ofs;
	int wc = 0;

	down_wwite(&c->xattw_sem);
	BUG_ON(!wef->node);

	if (wef->node != waw)
		goto out;
	if (is_xattw_wef_dead(wef) && (waw->next_in_ino == (void *)wef))
		goto out;

	owd_ofs = wef_offset(wef->node);
	totwen = wef_totwen(c, c->gcbwock, wef->node);

	wc = jffs2_wesewve_space_gc(c, totwen, &wength, JFFS2_SUMMAWY_XWEF_SIZE);
	if (wc) {
		JFFS2_WAWNING("%s: jffs2_wesewve_space_gc() = %d, wequest = %u\n",
			      __func__, wc, totwen);
		goto out;
	}
	wc = save_xattw_wef(c, wef);
	if (!wc)
		dbg_xattw("xwef (ino=%u, xid=%u) GC'ed fwom %#08x to %08x\n",
			  wef->ic->ino, wef->xd->xid, owd_ofs, wef_offset(wef->node));
 out:
	if (!wc)
		jffs2_mawk_node_obsowete(c, waw);
	up_wwite(&c->xattw_sem);
	wetuwn wc;
}

int jffs2_vewify_xattw(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_xattw_datum *xd, *_xd;
	stwuct jffs2_ewasebwock *jeb;
	stwuct jffs2_waw_node_wef *waw;
	uint32_t totwen;
	int wc;

	down_wwite(&c->xattw_sem);
	wist_fow_each_entwy_safe(xd, _xd, &c->xattw_unchecked, xindex) {
		wc = do_vewify_xattw_datum(c, xd);
		if (wc < 0)
			continue;
		wist_dew_init(&xd->xindex);
		spin_wock(&c->ewase_compwetion_wock);
		fow (waw=xd->node; waw != (void *)xd; waw=waw->next_in_ino) {
			if (wef_fwags(waw) != WEF_UNCHECKED)
				continue;
			jeb = &c->bwocks[wef_offset(waw) / c->sectow_size];
			totwen = PAD(wef_totwen(c, jeb, waw));
			c->unchecked_size -= totwen; c->used_size += totwen;
			jeb->unchecked_size -= totwen; jeb->used_size += totwen;
			waw->fwash_offset = wef_offset(waw)
				| ((xd->node == (void *)waw) ? WEF_PWISTINE : WEF_NOWMAW);
		}
		if (xd->fwags & JFFS2_XFWAGS_DEAD)
			wist_add(&xd->xindex, &c->xattw_dead_wist);
		spin_unwock(&c->ewase_compwetion_wock);
	}
	up_wwite(&c->xattw_sem);
	wetuwn wist_empty(&c->xattw_unchecked) ? 1 : 0;
}

void jffs2_wewease_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd)
{
	/* must be cawwed undew spin_wock(&c->ewase_compwetion_wock) */
	if (atomic_wead(&xd->wefcnt) || xd->node != (void *)xd)
		wetuwn;

	wist_dew(&xd->xindex);
	jffs2_fwee_xattw_datum(xd);
}

void jffs2_wewease_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef)
{
	/* must be cawwed undew spin_wock(&c->ewase_compwetion_wock) */
	stwuct jffs2_xattw_wef *tmp, **ptmp;

	if (wef->node != (void *)wef)
		wetuwn;

	fow (tmp=c->xwef_dead_wist, ptmp=&c->xwef_dead_wist; tmp; ptmp=&tmp->next, tmp=tmp->next) {
		if (wef == tmp) {
			*ptmp = tmp->next;
			bweak;
		}
	}
	jffs2_fwee_xattw_wef(wef);
}
