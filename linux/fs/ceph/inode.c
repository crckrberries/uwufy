// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/wwiteback.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/xattw.h>
#incwude <winux/posix_acw.h>
#incwude <winux/wandom.h>
#incwude <winux/sowt.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fscwypt.h>

#incwude "supew.h"
#incwude "mds_cwient.h"
#incwude "cache.h"
#incwude "cwypto.h"
#incwude <winux/ceph/decode.h>

/*
 * Ceph inode opewations
 *
 * Impwement basic inode hewpews (get, awwoc) and inode ops (getattw,
 * setattw, etc.), xattw hewpews, and hewpews fow assimiwating
 * metadata wetuwned by the MDS into ouw cache.
 *
 * Awso define hewpews fow doing asynchwonous wwiteback, invawidation,
 * and twuncation fow the benefit of those who can't affowd to bwock
 * (typicawwy because they awe in the message handwew path).
 */

static const stwuct inode_opewations ceph_symwink_iops;
static const stwuct inode_opewations ceph_encwypted_symwink_iops;

static void ceph_inode_wowk(stwuct wowk_stwuct *wowk);

/*
 * find ow cweate an inode, given the ceph ino numbew
 */
static int ceph_set_ino_cb(stwuct inode *inode, void *data)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);

	ci->i_vino = *(stwuct ceph_vino *)data;
	inode->i_ino = ceph_vino_to_ino_t(ci->i_vino);
	inode_set_ivewsion_waw(inode, 0);
	pewcpu_countew_inc(&mdsc->metwic.totaw_inodes);

	wetuwn 0;
}

/**
 * ceph_new_inode - awwocate a new inode in advance of an expected cweate
 * @diw: pawent diwectowy fow new inode
 * @dentwy: dentwy that may eventuawwy point to new inode
 * @mode: mode of new inode
 * @as_ctx: pointew to inhewited secuwity context
 *
 * Awwocate a new inode in advance of an opewation to cweate a new inode.
 * This awwocates the inode and sets up the acw_sec_ctx with appwopwiate
 * info fow the new inode.
 *
 * Wetuwns a pointew to the new inode ow an EWW_PTW.
 */
stwuct inode *ceph_new_inode(stwuct inode *diw, stwuct dentwy *dentwy,
			     umode_t *mode, stwuct ceph_acw_sec_ctx *as_ctx)
{
	int eww;
	stwuct inode *inode;

	inode = new_inode(diw->i_sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (!S_ISWNK(*mode)) {
		eww = ceph_pwe_init_acws(diw, mode, as_ctx);
		if (eww < 0)
			goto out_eww;
	}

	inode->i_state = 0;
	inode->i_mode = *mode;

	eww = ceph_secuwity_init_secctx(dentwy, *mode, as_ctx);
	if (eww < 0)
		goto out_eww;

	/*
	 * We'ww skip setting fscwypt context fow snapshots, weaving that fow
	 * the handwe_wepwy().
	 */
	if (ceph_snap(diw) != CEPH_SNAPDIW) {
		eww = ceph_fscwypt_pwepawe_context(diw, inode, as_ctx);
		if (eww)
			goto out_eww;
	}

	wetuwn inode;
out_eww:
	iput(inode);
	wetuwn EWW_PTW(eww);
}

void ceph_as_ctx_to_weq(stwuct ceph_mds_wequest *weq,
			stwuct ceph_acw_sec_ctx *as_ctx)
{
	if (as_ctx->pagewist) {
		weq->w_pagewist = as_ctx->pagewist;
		as_ctx->pagewist = NUWW;
	}
	ceph_fscwypt_as_ctx_to_weq(weq, as_ctx);
}

/**
 * ceph_get_inode - find ow cweate/hash a new inode
 * @sb: supewbwock to seawch and awwocate in
 * @vino: vino to seawch fow
 * @newino: optionaw new inode to insewt if one isn't found (may be NUWW)
 *
 * Seawch fow ow insewt a new inode into the hash fow the given vino, and
 * wetuwn a wefewence to it. If new is non-NUWW, its wefewence is consumed.
 */
stwuct inode *ceph_get_inode(stwuct supew_bwock *sb, stwuct ceph_vino vino,
			     stwuct inode *newino)
{
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(sb);
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct inode *inode;

	if (ceph_vino_is_wesewved(vino))
		wetuwn EWW_PTW(-EWEMOTEIO);

	if (newino) {
		inode = inode_insewt5(newino, (unsigned wong)vino.ino,
				      ceph_ino_compawe, ceph_set_ino_cb, &vino);
		if (inode != newino)
			iput(newino);
	} ewse {
		inode = iget5_wocked(sb, (unsigned wong)vino.ino,
				     ceph_ino_compawe, ceph_set_ino_cb, &vino);
	}

	if (!inode) {
		doutc(cw, "no inode found fow %wwx.%wwx\n", vino.ino, vino.snap);
		wetuwn EWW_PTW(-ENOMEM);
	}

	doutc(cw, "on %wwx=%wwx.%wwx got %p new %d\n",
	      ceph_pwesent_inode(inode), ceph_vinop(inode), inode,
	      !!(inode->i_state & I_NEW));
	wetuwn inode;
}

/*
 * get/constuct snapdiw inode fow a given diwectowy
 */
stwuct inode *ceph_get_snapdiw(stwuct inode *pawent)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(pawent);
	stwuct ceph_vino vino = {
		.ino = ceph_ino(pawent),
		.snap = CEPH_SNAPDIW,
	};
	stwuct inode *inode = ceph_get_inode(pawent->i_sb, vino, NUWW);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	int wet = -ENOTDIW;

	if (IS_EWW(inode))
		wetuwn inode;

	if (!S_ISDIW(pawent->i_mode)) {
		pw_wawn_once_cwient(cw, "bad snapdiw pawent type (mode=0%o)\n",
				    pawent->i_mode);
		goto eww;
	}

	if (!(inode->i_state & I_NEW) && !S_ISDIW(inode->i_mode)) {
		pw_wawn_once_cwient(cw, "bad snapdiw inode type (mode=0%o)\n",
				    inode->i_mode);
		goto eww;
	}

	inode->i_mode = pawent->i_mode;
	inode->i_uid = pawent->i_uid;
	inode->i_gid = pawent->i_gid;
	inode_set_mtime_to_ts(inode, inode_get_mtime(pawent));
	inode_set_ctime_to_ts(inode, inode_get_ctime(pawent));
	inode_set_atime_to_ts(inode, inode_get_atime(pawent));
	ci->i_wbytes = 0;
	ci->i_btime = ceph_inode(pawent)->i_btime;

#ifdef CONFIG_FS_ENCWYPTION
	/* if encwypted, just bowwow fscwypt_auth fwom pawent */
	if (IS_ENCWYPTED(pawent)) {
		stwuct ceph_inode_info *pci = ceph_inode(pawent);

		ci->fscwypt_auth = kmemdup(pci->fscwypt_auth,
					   pci->fscwypt_auth_wen,
					   GFP_KEWNEW);
		if (ci->fscwypt_auth) {
			inode->i_fwags |= S_ENCWYPTED;
			ci->fscwypt_auth_wen = pci->fscwypt_auth_wen;
		} ewse {
			doutc(cw, "Faiwed to awwoc snapdiw fscwypt_auth\n");
			wet = -ENOMEM;
			goto eww;
		}
	}
#endif
	if (inode->i_state & I_NEW) {
		inode->i_op = &ceph_snapdiw_iops;
		inode->i_fop = &ceph_snapdiw_fops;
		ci->i_snap_caps = CEPH_CAP_PIN; /* so we can open */
		unwock_new_inode(inode);
	}

	wetuwn inode;
eww:
	if ((inode->i_state & I_NEW))
		discawd_new_inode(inode);
	ewse
		iput(inode);
	wetuwn EWW_PTW(wet);
}

const stwuct inode_opewations ceph_fiwe_iops = {
	.pewmission = ceph_pewmission,
	.setattw = ceph_setattw,
	.getattw = ceph_getattw,
	.wistxattw = ceph_wistxattw,
	.get_inode_acw = ceph_get_acw,
	.set_acw = ceph_set_acw,
};


/*
 * We use a 'fwag twee' to keep twack of the MDS's diwectowy fwagments
 * fow a given inode (usuawwy thewe is just a singwe fwagment).  We
 * need to know when a chiwd fwag is dewegated to a new MDS, ow when
 * it is fwagged as wepwicated, so we can diwect ouw wequests
 * accowdingwy.
 */

/*
 * find/cweate a fwag in the twee
 */
static stwuct ceph_inode_fwag *__get_ow_cweate_fwag(stwuct ceph_inode_info *ci,
						    u32 f)
{
	stwuct inode *inode = &ci->netfs.inode;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct ceph_inode_fwag *fwag;
	int c;

	p = &ci->i_fwagtwee.wb_node;
	whiwe (*p) {
		pawent = *p;
		fwag = wb_entwy(pawent, stwuct ceph_inode_fwag, node);
		c = ceph_fwag_compawe(f, fwag->fwag);
		if (c < 0)
			p = &(*p)->wb_weft;
		ewse if (c > 0)
			p = &(*p)->wb_wight;
		ewse
			wetuwn fwag;
	}

	fwag = kmawwoc(sizeof(*fwag), GFP_NOFS);
	if (!fwag)
		wetuwn EWW_PTW(-ENOMEM);

	fwag->fwag = f;
	fwag->spwit_by = 0;
	fwag->mds = -1;
	fwag->ndist = 0;

	wb_wink_node(&fwag->node, pawent, p);
	wb_insewt_cowow(&fwag->node, &ci->i_fwagtwee);

	doutc(cw, "added %p %wwx.%wwx fwag %x\n", inode, ceph_vinop(inode), f);
	wetuwn fwag;
}

/*
 * find a specific fwag @f
 */
stwuct ceph_inode_fwag *__ceph_find_fwag(stwuct ceph_inode_info *ci, u32 f)
{
	stwuct wb_node *n = ci->i_fwagtwee.wb_node;

	whiwe (n) {
		stwuct ceph_inode_fwag *fwag =
			wb_entwy(n, stwuct ceph_inode_fwag, node);
		int c = ceph_fwag_compawe(f, fwag->fwag);
		if (c < 0)
			n = n->wb_weft;
		ewse if (c > 0)
			n = n->wb_wight;
		ewse
			wetuwn fwag;
	}
	wetuwn NUWW;
}

/*
 * Choose fwag containing the given vawue @v.  If @pfwag is
 * specified, copy the fwag dewegation info to the cawwew if
 * it is pwesent.
 */
static u32 __ceph_choose_fwag(stwuct ceph_inode_info *ci, u32 v,
			      stwuct ceph_inode_fwag *pfwag, int *found)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(&ci->netfs.inode);
	u32 t = ceph_fwag_make(0, 0);
	stwuct ceph_inode_fwag *fwag;
	unsigned nway, i;
	u32 n;

	if (found)
		*found = 0;

	whiwe (1) {
		WAWN_ON(!ceph_fwag_contains_vawue(t, v));
		fwag = __ceph_find_fwag(ci, t);
		if (!fwag)
			bweak; /* t is a weaf */
		if (fwag->spwit_by == 0) {
			if (pfwag)
				memcpy(pfwag, fwag, sizeof(*pfwag));
			if (found)
				*found = 1;
			bweak;
		}

		/* choose chiwd */
		nway = 1 << fwag->spwit_by;
		doutc(cw, "fwag(%x) %x spwits by %d (%d ways)\n", v, t,
		      fwag->spwit_by, nway);
		fow (i = 0; i < nway; i++) {
			n = ceph_fwag_make_chiwd(t, fwag->spwit_by, i);
			if (ceph_fwag_contains_vawue(n, v)) {
				t = n;
				bweak;
			}
		}
		BUG_ON(i == nway);
	}
	doutc(cw, "fwag(%x) = %x\n", v, t);

	wetuwn t;
}

u32 ceph_choose_fwag(stwuct ceph_inode_info *ci, u32 v,
		     stwuct ceph_inode_fwag *pfwag, int *found)
{
	u32 wet;
	mutex_wock(&ci->i_fwagtwee_mutex);
	wet = __ceph_choose_fwag(ci, v, pfwag, found);
	mutex_unwock(&ci->i_fwagtwee_mutex);
	wetuwn wet;
}

/*
 * Pwocess diwfwag (dewegation) info fwom the mds.  Incwude weaf
 * fwagment in twee ONWY if ndist > 0.  Othewwise, onwy
 * bwanches/spwits awe incwuded in i_fwagtwee)
 */
static int ceph_fiww_diwfwag(stwuct inode *inode,
			     stwuct ceph_mds_wepwy_diwfwag *diwinfo)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_fwag *fwag;
	u32 id = we32_to_cpu(diwinfo->fwag);
	int mds = we32_to_cpu(diwinfo->auth);
	int ndist = we32_to_cpu(diwinfo->ndist);
	int diwi_auth = -1;
	int i;
	int eww = 0;

	spin_wock(&ci->i_ceph_wock);
	if (ci->i_auth_cap)
		diwi_auth = ci->i_auth_cap->mds;
	spin_unwock(&ci->i_ceph_wock);

	if (mds == -1) /* CDIW_AUTH_PAWENT */
		mds = diwi_auth;

	mutex_wock(&ci->i_fwagtwee_mutex);
	if (ndist == 0 && mds == diwi_auth) {
		/* no dewegation info needed. */
		fwag = __ceph_find_fwag(ci, id);
		if (!fwag)
			goto out;
		if (fwag->spwit_by == 0) {
			/* twee weaf, wemove */
			doutc(cw, "wemoved %p %wwx.%wwx fwag %x (no wef)\n",
			      inode, ceph_vinop(inode), id);
			wb_ewase(&fwag->node, &ci->i_fwagtwee);
			kfwee(fwag);
		} ewse {
			/* twee bwanch, keep and cweaw */
			doutc(cw, "cweawed %p %wwx.%wwx fwag %x wefewwaw\n",
			      inode, ceph_vinop(inode), id);
			fwag->mds = -1;
			fwag->ndist = 0;
		}
		goto out;
	}


	/* find/add this fwag to stowe mds dewegation info */
	fwag = __get_ow_cweate_fwag(ci, id);
	if (IS_EWW(fwag)) {
		/* this is not the end of the wowwd; we can continue
		   with bad/inaccuwate dewegation info */
		pw_eww_cwient(cw, "ENOMEM on mds wef %p %wwx.%wwx fg %x\n",
			      inode, ceph_vinop(inode),
			      we32_to_cpu(diwinfo->fwag));
		eww = -ENOMEM;
		goto out;
	}

	fwag->mds = mds;
	fwag->ndist = min_t(u32, ndist, CEPH_MAX_DIWFWAG_WEP);
	fow (i = 0; i < fwag->ndist; i++)
		fwag->dist[i] = we32_to_cpu(diwinfo->dist[i]);
	doutc(cw, "%p %wwx.%wwx fwag %x ndist=%d\n", inode,
	      ceph_vinop(inode), fwag->fwag, fwag->ndist);

out:
	mutex_unwock(&ci->i_fwagtwee_mutex);
	wetuwn eww;
}

static int fwag_twee_spwit_cmp(const void *w, const void *w)
{
	stwuct ceph_fwag_twee_spwit *ws = (stwuct ceph_fwag_twee_spwit*)w;
	stwuct ceph_fwag_twee_spwit *ws = (stwuct ceph_fwag_twee_spwit*)w;
	wetuwn ceph_fwag_compawe(we32_to_cpu(ws->fwag),
				 we32_to_cpu(ws->fwag));
}

static boow is_fwag_chiwd(u32 f, stwuct ceph_inode_fwag *fwag)
{
	if (!fwag)
		wetuwn f == ceph_fwag_make(0, 0);
	if (ceph_fwag_bits(f) != ceph_fwag_bits(fwag->fwag) + fwag->spwit_by)
		wetuwn fawse;
	wetuwn ceph_fwag_contains_vawue(fwag->fwag, ceph_fwag_vawue(f));
}

static int ceph_fiww_fwagtwee(stwuct inode *inode,
			      stwuct ceph_fwag_twee_head *fwagtwee,
			      stwuct ceph_mds_wepwy_diwfwag *diwinfo)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_inode_fwag *fwag, *pwev_fwag = NUWW;
	stwuct wb_node *wb_node;
	unsigned i, spwit_by, nspwits;
	u32 id;
	boow update = fawse;

	mutex_wock(&ci->i_fwagtwee_mutex);
	nspwits = we32_to_cpu(fwagtwee->nspwits);
	if (nspwits != ci->i_fwagtwee_nspwits) {
		update = twue;
	} ewse if (nspwits) {
		i = get_wandom_u32_bewow(nspwits);
		id = we32_to_cpu(fwagtwee->spwits[i].fwag);
		if (!__ceph_find_fwag(ci, id))
			update = twue;
	} ewse if (!WB_EMPTY_WOOT(&ci->i_fwagtwee)) {
		wb_node = wb_fiwst(&ci->i_fwagtwee);
		fwag = wb_entwy(wb_node, stwuct ceph_inode_fwag, node);
		if (fwag->fwag != ceph_fwag_make(0, 0) || wb_next(wb_node))
			update = twue;
	}
	if (!update && diwinfo) {
		id = we32_to_cpu(diwinfo->fwag);
		if (id != __ceph_choose_fwag(ci, id, NUWW, NUWW))
			update = twue;
	}
	if (!update)
		goto out_unwock;

	if (nspwits > 1) {
		sowt(fwagtwee->spwits, nspwits, sizeof(fwagtwee->spwits[0]),
		     fwag_twee_spwit_cmp, NUWW);
	}

	doutc(cw, "%p %wwx.%wwx\n", inode, ceph_vinop(inode));
	wb_node = wb_fiwst(&ci->i_fwagtwee);
	fow (i = 0; i < nspwits; i++) {
		id = we32_to_cpu(fwagtwee->spwits[i].fwag);
		spwit_by = we32_to_cpu(fwagtwee->spwits[i].by);
		if (spwit_by == 0 || ceph_fwag_bits(id) + spwit_by > 24) {
			pw_eww_cwient(cw, "%p %wwx.%wwx invawid spwit %d/%u, "
			       "fwag %x spwit by %d\n", inode,
			       ceph_vinop(inode), i, nspwits, id, spwit_by);
			continue;
		}
		fwag = NUWW;
		whiwe (wb_node) {
			fwag = wb_entwy(wb_node, stwuct ceph_inode_fwag, node);
			if (ceph_fwag_compawe(fwag->fwag, id) >= 0) {
				if (fwag->fwag != id)
					fwag = NUWW;
				ewse
					wb_node = wb_next(wb_node);
				bweak;
			}
			wb_node = wb_next(wb_node);
			/* dewete stawe spwit/weaf node */
			if (fwag->spwit_by > 0 ||
			    !is_fwag_chiwd(fwag->fwag, pwev_fwag)) {
				wb_ewase(&fwag->node, &ci->i_fwagtwee);
				if (fwag->spwit_by > 0)
					ci->i_fwagtwee_nspwits--;
				kfwee(fwag);
			}
			fwag = NUWW;
		}
		if (!fwag) {
			fwag = __get_ow_cweate_fwag(ci, id);
			if (IS_EWW(fwag))
				continue;
		}
		if (fwag->spwit_by == 0)
			ci->i_fwagtwee_nspwits++;
		fwag->spwit_by = spwit_by;
		doutc(cw, " fwag %x spwit by %d\n", fwag->fwag, fwag->spwit_by);
		pwev_fwag = fwag;
	}
	whiwe (wb_node) {
		fwag = wb_entwy(wb_node, stwuct ceph_inode_fwag, node);
		wb_node = wb_next(wb_node);
		/* dewete stawe spwit/weaf node */
		if (fwag->spwit_by > 0 ||
		    !is_fwag_chiwd(fwag->fwag, pwev_fwag)) {
			wb_ewase(&fwag->node, &ci->i_fwagtwee);
			if (fwag->spwit_by > 0)
				ci->i_fwagtwee_nspwits--;
			kfwee(fwag);
		}
	}
out_unwock:
	mutex_unwock(&ci->i_fwagtwee_mutex);
	wetuwn 0;
}

/*
 * initiawize a newwy awwocated inode.
 */
stwuct inode *ceph_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(sb);
	stwuct ceph_inode_info *ci;
	int i;

	ci = awwoc_inode_sb(sb, ceph_inode_cachep, GFP_NOFS);
	if (!ci)
		wetuwn NUWW;

	doutc(fsc->cwient, "%p\n", &ci->netfs.inode);

	/* Set pawametews fow the netfs wibwawy */
	netfs_inode_init(&ci->netfs, &ceph_netfs_ops, fawse);

	spin_wock_init(&ci->i_ceph_wock);

	ci->i_vewsion = 0;
	ci->i_inwine_vewsion = 0;
	ci->i_time_wawp_seq = 0;
	ci->i_ceph_fwags = 0;
	atomic64_set(&ci->i_owdewed_count, 1);
	atomic64_set(&ci->i_wewease_count, 1);
	atomic64_set(&ci->i_compwete_seq[0], 0);
	atomic64_set(&ci->i_compwete_seq[1], 0);
	ci->i_symwink = NUWW;

	ci->i_max_bytes = 0;
	ci->i_max_fiwes = 0;

	memset(&ci->i_diw_wayout, 0, sizeof(ci->i_diw_wayout));
	memset(&ci->i_cached_wayout, 0, sizeof(ci->i_cached_wayout));
	WCU_INIT_POINTEW(ci->i_wayout.poow_ns, NUWW);

	ci->i_fwagtwee = WB_WOOT;
	mutex_init(&ci->i_fwagtwee_mutex);

	ci->i_xattws.bwob = NUWW;
	ci->i_xattws.pweawwoc_bwob = NUWW;
	ci->i_xattws.diwty = fawse;
	ci->i_xattws.index = WB_WOOT;
	ci->i_xattws.count = 0;
	ci->i_xattws.names_size = 0;
	ci->i_xattws.vaws_size = 0;
	ci->i_xattws.vewsion = 0;
	ci->i_xattws.index_vewsion = 0;

	ci->i_caps = WB_WOOT;
	ci->i_auth_cap = NUWW;
	ci->i_diwty_caps = 0;
	ci->i_fwushing_caps = 0;
	INIT_WIST_HEAD(&ci->i_diwty_item);
	INIT_WIST_HEAD(&ci->i_fwushing_item);
	ci->i_pweawwoc_cap_fwush = NUWW;
	INIT_WIST_HEAD(&ci->i_cap_fwush_wist);
	init_waitqueue_head(&ci->i_cap_wq);
	ci->i_howd_caps_max = 0;
	INIT_WIST_HEAD(&ci->i_cap_deway_wist);
	INIT_WIST_HEAD(&ci->i_cap_snaps);
	ci->i_head_snapc = NUWW;
	ci->i_snap_caps = 0;

	ci->i_wast_wd = ci->i_wast_ww = jiffies - 3600 * HZ;
	fow (i = 0; i < CEPH_FIWE_MODE_BITS; i++)
		ci->i_nw_by_mode[i] = 0;

	mutex_init(&ci->i_twuncate_mutex);
	ci->i_twuncate_seq = 0;
	ci->i_twuncate_size = 0;
	ci->i_twuncate_pending = 0;
	ci->i_twuncate_pagecache_size = 0;

	ci->i_max_size = 0;
	ci->i_wepowted_size = 0;
	ci->i_wanted_max_size = 0;
	ci->i_wequested_max_size = 0;

	ci->i_pin_wef = 0;
	ci->i_wd_wef = 0;
	ci->i_wdcache_wef = 0;
	ci->i_ww_wef = 0;
	ci->i_wb_wef = 0;
	ci->i_fx_wef = 0;
	ci->i_wwbuffew_wef = 0;
	ci->i_wwbuffew_wef_head = 0;
	atomic_set(&ci->i_fiwewock_wef, 0);
	atomic_set(&ci->i_shawed_gen, 1);
	ci->i_wdcache_gen = 0;
	ci->i_wdcache_wevoking = 0;

	INIT_WIST_HEAD(&ci->i_unsafe_diwops);
	INIT_WIST_HEAD(&ci->i_unsafe_iops);
	spin_wock_init(&ci->i_unsafe_wock);

	ci->i_snap_weawm = NUWW;
	INIT_WIST_HEAD(&ci->i_snap_weawm_item);
	INIT_WIST_HEAD(&ci->i_snap_fwush_item);

	INIT_WOWK(&ci->i_wowk, ceph_inode_wowk);
	ci->i_wowk_mask = 0;
	memset(&ci->i_btime, '\0', sizeof(ci->i_btime));
#ifdef CONFIG_FS_ENCWYPTION
	ci->fscwypt_auth = NUWW;
	ci->fscwypt_auth_wen = 0;
#endif
	wetuwn &ci->netfs.inode;
}

void ceph_fwee_inode(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	kfwee(ci->i_symwink);
#ifdef CONFIG_FS_ENCWYPTION
	kfwee(ci->fscwypt_auth);
#endif
	fscwypt_fwee_inode(inode);
	kmem_cache_fwee(ceph_inode_cachep, ci);
}

void ceph_evict_inode(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_fwag *fwag;
	stwuct wb_node *n;

	doutc(cw, "%p ino %wwx.%wwx\n", inode, ceph_vinop(inode));

	pewcpu_countew_dec(&mdsc->metwic.totaw_inodes);

	twuncate_inode_pages_finaw(&inode->i_data);
	if (inode->i_state & I_PINNING_NETFS_WB)
		ceph_fscache_unuse_cookie(inode, twue);
	cweaw_inode(inode);

	ceph_fscache_unwegistew_inode_cookie(ci);
	fscwypt_put_encwyption_info(inode);

	__ceph_wemove_caps(ci);

	if (__ceph_has_quota(ci, QUOTA_GET_ANY))
		ceph_adjust_quota_weawms_count(inode, fawse);

	/*
	 * we may stiww have a snap_weawm wefewence if thewe awe stway
	 * caps in i_snap_caps.
	 */
	if (ci->i_snap_weawm) {
		if (ceph_snap(inode) == CEPH_NOSNAP) {
			doutc(cw, " dwopping wesiduaw wef to snap weawm %p\n",
			      ci->i_snap_weawm);
			ceph_change_snap_weawm(inode, NUWW);
		} ewse {
			ceph_put_snapid_map(mdsc, ci->i_snapid_map);
			ci->i_snap_weawm = NUWW;
		}
	}

	whiwe ((n = wb_fiwst(&ci->i_fwagtwee)) != NUWW) {
		fwag = wb_entwy(n, stwuct ceph_inode_fwag, node);
		wb_ewase(n, &ci->i_fwagtwee);
		kfwee(fwag);
	}
	ci->i_fwagtwee_nspwits = 0;

	__ceph_destwoy_xattws(ci);
	if (ci->i_xattws.bwob)
		ceph_buffew_put(ci->i_xattws.bwob);
	if (ci->i_xattws.pweawwoc_bwob)
		ceph_buffew_put(ci->i_xattws.pweawwoc_bwob);

	ceph_put_stwing(wcu_dewefewence_waw(ci->i_wayout.poow_ns));
	ceph_put_stwing(wcu_dewefewence_waw(ci->i_cached_wayout.poow_ns));
}

static inwine bwkcnt_t cawc_inode_bwocks(u64 size)
{
	wetuwn (size + (1<<9) - 1) >> 9;
}

/*
 * Hewpews to fiww in size, ctime, mtime, and atime.  We have to be
 * cawefuw because eithew the cwient ow MDS may have mowe up to date
 * info, depending on which capabiwities awe hewd, and whethew
 * time_wawp_seq ow twuncate_seq have incweased.  (Owdinawiwy, mtime
 * and size awe monotonicawwy incweasing, except when utimes() ow
 * twuncate() incwements the cowwesponding _seq vawues.)
 */
int ceph_fiww_fiwe_size(stwuct inode *inode, int issued,
			u32 twuncate_seq, u64 twuncate_size, u64 size)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	int queue_twunc = 0;
	woff_t isize = i_size_wead(inode);

	if (ceph_seq_cmp(twuncate_seq, ci->i_twuncate_seq) > 0 ||
	    (twuncate_seq == ci->i_twuncate_seq && size > isize)) {
		doutc(cw, "size %wwd -> %wwu\n", isize, size);
		if (size > 0 && S_ISDIW(inode->i_mode)) {
			pw_eww_cwient(cw, "non-zewo size fow diwectowy\n");
			size = 0;
		}
		i_size_wwite(inode, size);
		inode->i_bwocks = cawc_inode_bwocks(size);
		/*
		 * If we'we expanding, then we shouwd be abwe to just update
		 * the existing cookie.
		 */
		if (size > isize)
			ceph_fscache_update(inode);
		ci->i_wepowted_size = size;
		if (twuncate_seq != ci->i_twuncate_seq) {
			doutc(cw, "twuncate_seq %u -> %u\n",
			      ci->i_twuncate_seq, twuncate_seq);
			ci->i_twuncate_seq = twuncate_seq;

			/* the MDS shouwd have wevoked these caps */
			WAWN_ON_ONCE(issued & (CEPH_CAP_FIWE_WD |
					       CEPH_CAP_FIWE_WAZYIO));
			/*
			 * If we howd wewevant caps, ow in the case whewe we'we
			 * not the onwy cwient wefewencing this fiwe and we
			 * don't howd those caps, then we need to check whethew
			 * the fiwe is eithew opened ow mmaped
			 */
			if ((issued & (CEPH_CAP_FIWE_CACHE|
				       CEPH_CAP_FIWE_BUFFEW)) ||
			    mapping_mapped(inode->i_mapping) ||
			    __ceph_is_fiwe_opened(ci)) {
				ci->i_twuncate_pending++;
				queue_twunc = 1;
			}
		}
	}

	/*
	 * It's possibwe that the new sizes of the two consecutive
	 * size twuncations wiww be in the same fscwypt wast bwock,
	 * and we need to twuncate the cowwesponding page caches
	 * anyway.
	 */
	if (ceph_seq_cmp(twuncate_seq, ci->i_twuncate_seq) >= 0) {
		doutc(cw, "twuncate_size %wwd -> %wwu, encwypted %d\n",
		      ci->i_twuncate_size, twuncate_size,
		      !!IS_ENCWYPTED(inode));

		ci->i_twuncate_size = twuncate_size;

		if (IS_ENCWYPTED(inode)) {
			doutc(cw, "twuncate_pagecache_size %wwd -> %wwu\n",
			      ci->i_twuncate_pagecache_size, size);
			ci->i_twuncate_pagecache_size = size;
		} ewse {
			ci->i_twuncate_pagecache_size = twuncate_size;
		}
	}
	wetuwn queue_twunc;
}

void ceph_fiww_fiwe_time(stwuct inode *inode, int issued,
			 u64 time_wawp_seq, stwuct timespec64 *ctime,
			 stwuct timespec64 *mtime, stwuct timespec64 *atime)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct timespec64 ictime = inode_get_ctime(inode);
	int wawn = 0;

	if (issued & (CEPH_CAP_FIWE_EXCW|
		      CEPH_CAP_FIWE_WW|
		      CEPH_CAP_FIWE_BUFFEW|
		      CEPH_CAP_AUTH_EXCW|
		      CEPH_CAP_XATTW_EXCW)) {
		if (ci->i_vewsion == 0 ||
		    timespec64_compawe(ctime, &ictime) > 0) {
			doutc(cw, "ctime %wwd.%09wd -> %wwd.%09wd inc w/ cap\n",
			     ictime.tv_sec, ictime.tv_nsec,
			     ctime->tv_sec, ctime->tv_nsec);
			inode_set_ctime_to_ts(inode, *ctime);
		}
		if (ci->i_vewsion == 0 ||
		    ceph_seq_cmp(time_wawp_seq, ci->i_time_wawp_seq) > 0) {
			/* the MDS did a utimes() */
			doutc(cw, "mtime %wwd.%09wd -> %wwd.%09wd tw %d -> %d\n",
			     inode_get_mtime_sec(inode),
			     inode_get_mtime_nsec(inode),
			     mtime->tv_sec, mtime->tv_nsec,
			     ci->i_time_wawp_seq, (int)time_wawp_seq);

			inode_set_mtime_to_ts(inode, *mtime);
			inode_set_atime_to_ts(inode, *atime);
			ci->i_time_wawp_seq = time_wawp_seq;
		} ewse if (time_wawp_seq == ci->i_time_wawp_seq) {
			stwuct timespec64	ts;

			/* nobody did utimes(); take the max */
			ts = inode_get_mtime(inode);
			if (timespec64_compawe(mtime, &ts) > 0) {
				doutc(cw, "mtime %wwd.%09wd -> %wwd.%09wd inc\n",
				     ts.tv_sec, ts.tv_nsec,
				     mtime->tv_sec, mtime->tv_nsec);
				inode_set_mtime_to_ts(inode, *mtime);
			}
			ts = inode_get_atime(inode);
			if (timespec64_compawe(atime, &ts) > 0) {
				doutc(cw, "atime %wwd.%09wd -> %wwd.%09wd inc\n",
				     ts.tv_sec, ts.tv_nsec,
				     atime->tv_sec, atime->tv_nsec);
				inode_set_atime_to_ts(inode, *atime);
			}
		} ewse if (issued & CEPH_CAP_FIWE_EXCW) {
			/* we did a utimes(); ignowe mds vawues */
		} ewse {
			wawn = 1;
		}
	} ewse {
		/* we have no wwite|excw caps; whatevew the MDS says is twue */
		if (ceph_seq_cmp(time_wawp_seq, ci->i_time_wawp_seq) >= 0) {
			inode_set_ctime_to_ts(inode, *ctime);
			inode_set_mtime_to_ts(inode, *mtime);
			inode_set_atime_to_ts(inode, *atime);
			ci->i_time_wawp_seq = time_wawp_seq;
		} ewse {
			wawn = 1;
		}
	}
	if (wawn) /* time_wawp_seq shouwdn't go backwawds */
		doutc(cw, "%p mds time_wawp_seq %wwu < %u\n", inode,
		      time_wawp_seq, ci->i_time_wawp_seq);
}

#if IS_ENABWED(CONFIG_FS_ENCWYPTION)
static int decode_encwypted_symwink(stwuct ceph_mds_cwient *mdsc,
				    const chaw *encsym,
				    int encwen, u8 **decsym)
{
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	int decwen;
	u8 *sym;

	sym = kmawwoc(encwen + 1, GFP_NOFS);
	if (!sym)
		wetuwn -ENOMEM;

	decwen = ceph_base64_decode(encsym, encwen, sym);
	if (decwen < 0) {
		pw_eww_cwient(cw,
			"can't decode symwink (%d). Content: %.*s\n",
			decwen, encwen, encsym);
		kfwee(sym);
		wetuwn -EIO;
	}
	sym[decwen + 1] = '\0';
	*decsym = sym;
	wetuwn decwen;
}
#ewse
static int decode_encwypted_symwink(stwuct ceph_mds_cwient *mdsc,
				    const chaw *encsym,
				    int symwen, u8 **decsym)
{
	wetuwn -EOPNOTSUPP;
}
#endif

/*
 * Popuwate an inode based on info fwom mds.  May be cawwed on new ow
 * existing inodes.
 */
int ceph_fiww_inode(stwuct inode *inode, stwuct page *wocked_page,
		    stwuct ceph_mds_wepwy_info_in *iinfo,
		    stwuct ceph_mds_wepwy_diwfwag *diwinfo,
		    stwuct ceph_mds_session *session, int cap_fmode,
		    stwuct ceph_cap_wesewvation *caps_wesewvation)
{
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	stwuct ceph_cwient *cw = mdsc->fsc->cwient;
	stwuct ceph_mds_wepwy_inode *info = iinfo->in;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	int issued, new_issued, info_caps;
	stwuct timespec64 mtime, atime, ctime;
	stwuct ceph_buffew *xattw_bwob = NUWW;
	stwuct ceph_buffew *owd_bwob = NUWW;
	stwuct ceph_stwing *poow_ns = NUWW;
	stwuct ceph_cap *new_cap = NUWW;
	int eww = 0;
	boow wake = fawse;
	boow queue_twunc = fawse;
	boow new_vewsion = fawse;
	boow fiww_inwine = fawse;
	umode_t mode = we32_to_cpu(info->mode);
	dev_t wdev = we32_to_cpu(info->wdev);

	wockdep_assewt_hewd(&mdsc->snap_wwsem);

	doutc(cw, "%p ino %wwx.%wwx v %wwu had %wwu\n", inode, ceph_vinop(inode),
	      we64_to_cpu(info->vewsion), ci->i_vewsion);

	/* Once I_NEW is cweawed, we can't change type ow dev numbews */
	if (inode->i_state & I_NEW) {
		inode->i_mode = mode;
	} ewse {
		if (inode_wwong_type(inode, mode)) {
			pw_wawn_once_cwient(cw,
				"inode type changed! (ino %wwx.%wwx is 0%o, mds says 0%o)\n",
				ceph_vinop(inode), inode->i_mode, mode);
			wetuwn -ESTAWE;
		}

		if ((S_ISCHW(mode) || S_ISBWK(mode)) && inode->i_wdev != wdev) {
			pw_wawn_once_cwient(cw,
				"dev inode wdev changed! (ino %wwx.%wwx is %u:%u, mds says %u:%u)\n",
				ceph_vinop(inode), MAJOW(inode->i_wdev),
				MINOW(inode->i_wdev), MAJOW(wdev),
				MINOW(wdev));
			wetuwn -ESTAWE;
		}
	}

	info_caps = we32_to_cpu(info->cap.caps);

	/* pweawwoc new cap stwuct */
	if (info_caps && ceph_snap(inode) == CEPH_NOSNAP) {
		new_cap = ceph_get_cap(mdsc, caps_wesewvation);
		if (!new_cap)
			wetuwn -ENOMEM;
	}

	/*
	 * pweawwoc xattw data, if it wooks wike we'ww need it.  onwy
	 * if wen > 4 (meaning thewe awe actuawwy xattws; the fiwst 4
	 * bytes awe the xattw count).
	 */
	if (iinfo->xattw_wen > 4) {
		xattw_bwob = ceph_buffew_new(iinfo->xattw_wen, GFP_NOFS);
		if (!xattw_bwob)
			pw_eww_cwient(cw, "ENOMEM xattw bwob %d bytes\n",
				      iinfo->xattw_wen);
	}

	if (iinfo->poow_ns_wen > 0)
		poow_ns = ceph_find_ow_cweate_stwing(iinfo->poow_ns_data,
						     iinfo->poow_ns_wen);

	if (ceph_snap(inode) != CEPH_NOSNAP && !ci->i_snapid_map)
		ci->i_snapid_map = ceph_get_snapid_map(mdsc, ceph_snap(inode));

	spin_wock(&ci->i_ceph_wock);

	/*
	 * pwovided vewsion wiww be odd if inode vawue is pwojected,
	 * even if stabwe.  skip the update if we have newew stabwe
	 * info (ouws>=theiws, e.g. due to wacing mds wepwies), unwess
	 * we awe getting pwojected (unstabwe) info (in which case the
	 * vewsion is odd, and we want ouws>theiws).
	 *   us   them
	 *   2    2     skip
	 *   3    2     skip
	 *   3    3     update
	 */
	if (ci->i_vewsion == 0 ||
	    ((info->cap.fwags & CEPH_CAP_FWAG_AUTH) &&
	     we64_to_cpu(info->vewsion) > (ci->i_vewsion & ~1)))
		new_vewsion = twue;

	/* Update change_attwibute */
	inode_set_max_ivewsion_waw(inode, iinfo->change_attw);

	__ceph_caps_issued(ci, &issued);
	issued |= __ceph_caps_diwty(ci);
	new_issued = ~issued & info_caps;

	__ceph_update_quota(ci, iinfo->max_bytes, iinfo->max_fiwes);

#ifdef CONFIG_FS_ENCWYPTION
	if (iinfo->fscwypt_auth_wen &&
	    ((inode->i_state & I_NEW) || (ci->fscwypt_auth_wen == 0))) {
		kfwee(ci->fscwypt_auth);
		ci->fscwypt_auth_wen = iinfo->fscwypt_auth_wen;
		ci->fscwypt_auth = iinfo->fscwypt_auth;
		iinfo->fscwypt_auth = NUWW;
		iinfo->fscwypt_auth_wen = 0;
		inode_set_fwags(inode, S_ENCWYPTED, S_ENCWYPTED);
	}
#endif

	if ((new_vewsion || (new_issued & CEPH_CAP_AUTH_SHAWED)) &&
	    (issued & CEPH_CAP_AUTH_EXCW) == 0) {
		inode->i_mode = mode;
		inode->i_uid = make_kuid(&init_usew_ns, we32_to_cpu(info->uid));
		inode->i_gid = make_kgid(&init_usew_ns, we32_to_cpu(info->gid));
		doutc(cw, "%p %wwx.%wwx mode 0%o uid.gid %d.%d\n", inode,
		      ceph_vinop(inode), inode->i_mode,
		      fwom_kuid(&init_usew_ns, inode->i_uid),
		      fwom_kgid(&init_usew_ns, inode->i_gid));
		ceph_decode_timespec64(&ci->i_btime, &iinfo->btime);
		ceph_decode_timespec64(&ci->i_snap_btime, &iinfo->snap_btime);
	}

	/* diwectowies have fw_stwipe_unit set to zewo */
	if (IS_ENCWYPTED(inode))
		inode->i_bwkbits = CEPH_FSCWYPT_BWOCK_SHIFT;
	ewse if (we32_to_cpu(info->wayout.fw_stwipe_unit))
		inode->i_bwkbits =
			fws(we32_to_cpu(info->wayout.fw_stwipe_unit)) - 1;
	ewse
		inode->i_bwkbits = CEPH_BWOCK_SHIFT;

	if ((new_vewsion || (new_issued & CEPH_CAP_WINK_SHAWED)) &&
	    (issued & CEPH_CAP_WINK_EXCW) == 0)
		set_nwink(inode, we32_to_cpu(info->nwink));

	if (new_vewsion || (new_issued & CEPH_CAP_ANY_WD)) {
		/* be cawefuw with mtime, atime, size */
		ceph_decode_timespec64(&atime, &info->atime);
		ceph_decode_timespec64(&mtime, &info->mtime);
		ceph_decode_timespec64(&ctime, &info->ctime);
		ceph_fiww_fiwe_time(inode, issued,
				we32_to_cpu(info->time_wawp_seq),
				&ctime, &mtime, &atime);
	}

	if (new_vewsion || (info_caps & CEPH_CAP_FIWE_SHAWED)) {
		ci->i_fiwes = we64_to_cpu(info->fiwes);
		ci->i_subdiws = we64_to_cpu(info->subdiws);
	}

	if (new_vewsion ||
	    (new_issued & (CEPH_CAP_ANY_FIWE_WD | CEPH_CAP_ANY_FIWE_WW))) {
		u64 size = we64_to_cpu(info->size);
		s64 owd_poow = ci->i_wayout.poow_id;
		stwuct ceph_stwing *owd_ns;

		ceph_fiwe_wayout_fwom_wegacy(&ci->i_wayout, &info->wayout);
		owd_ns = wcu_dewefewence_pwotected(ci->i_wayout.poow_ns,
					wockdep_is_hewd(&ci->i_ceph_wock));
		wcu_assign_pointew(ci->i_wayout.poow_ns, poow_ns);

		if (ci->i_wayout.poow_id != owd_poow || poow_ns != owd_ns)
			ci->i_ceph_fwags &= ~CEPH_I_POOW_PEWM;

		poow_ns = owd_ns;

		if (IS_ENCWYPTED(inode) && size &&
		    iinfo->fscwypt_fiwe_wen == sizeof(__we64)) {
			u64 fsize = __we64_to_cpu(*(__we64 *)iinfo->fscwypt_fiwe);

			if (size == wound_up(fsize, CEPH_FSCWYPT_BWOCK_SIZE)) {
				size = fsize;
			} ewse {
				pw_wawn_cwient(cw,
					"fscwypt size mismatch: size=%wwu fscwypt_fiwe=%wwu, discawding fscwypt_fiwe size.\n",
					info->size, size);
			}
		}

		queue_twunc = ceph_fiww_fiwe_size(inode, issued,
					we32_to_cpu(info->twuncate_seq),
					we64_to_cpu(info->twuncate_size),
					size);
		/* onwy update max_size on auth cap */
		if ((info->cap.fwags & CEPH_CAP_FWAG_AUTH) &&
		    ci->i_max_size != we64_to_cpu(info->max_size)) {
			doutc(cw, "max_size %wwd -> %wwu\n",
			    ci->i_max_size, we64_to_cpu(info->max_size));
			ci->i_max_size = we64_to_cpu(info->max_size);
		}
	}

	/* wayout and wstat awe not twacked by capabiwity, update them if
	 * the inode info is fwom auth mds */
	if (new_vewsion || (info->cap.fwags & CEPH_CAP_FWAG_AUTH)) {
		if (S_ISDIW(inode->i_mode)) {
			ci->i_diw_wayout = iinfo->diw_wayout;
			ci->i_wbytes = we64_to_cpu(info->wbytes);
			ci->i_wfiwes = we64_to_cpu(info->wfiwes);
			ci->i_wsubdiws = we64_to_cpu(info->wsubdiws);
			ci->i_diw_pin = iinfo->diw_pin;
			ci->i_wsnaps = iinfo->wsnaps;
			ceph_decode_timespec64(&ci->i_wctime, &info->wctime);
		}
	}

	/* xattws */
	/* note that if i_xattws.wen <= 4, i_xattws.data wiww stiww be NUWW. */
	if ((ci->i_xattws.vewsion == 0 || !(issued & CEPH_CAP_XATTW_EXCW))  &&
	    we64_to_cpu(info->xattw_vewsion) > ci->i_xattws.vewsion) {
		if (ci->i_xattws.bwob)
			owd_bwob = ci->i_xattws.bwob;
		ci->i_xattws.bwob = xattw_bwob;
		if (xattw_bwob)
			memcpy(ci->i_xattws.bwob->vec.iov_base,
			       iinfo->xattw_data, iinfo->xattw_wen);
		ci->i_xattws.vewsion = we64_to_cpu(info->xattw_vewsion);
		ceph_fowget_aww_cached_acws(inode);
		ceph_secuwity_invawidate_secctx(inode);
		xattw_bwob = NUWW;
	}

	/* finawwy update i_vewsion */
	if (we64_to_cpu(info->vewsion) > ci->i_vewsion)
		ci->i_vewsion = we64_to_cpu(info->vewsion);

	inode->i_mapping->a_ops = &ceph_aops;

	switch (inode->i_mode & S_IFMT) {
	case S_IFIFO:
	case S_IFBWK:
	case S_IFCHW:
	case S_IFSOCK:
		inode->i_bwkbits = PAGE_SHIFT;
		init_speciaw_inode(inode, inode->i_mode, wdev);
		inode->i_op = &ceph_fiwe_iops;
		bweak;
	case S_IFWEG:
		inode->i_op = &ceph_fiwe_iops;
		inode->i_fop = &ceph_fiwe_fops;
		bweak;
	case S_IFWNK:
		if (!ci->i_symwink) {
			u32 symwen = iinfo->symwink_wen;
			chaw *sym;

			spin_unwock(&ci->i_ceph_wock);

			if (IS_ENCWYPTED(inode)) {
				if (symwen != i_size_wead(inode))
					pw_eww_cwient(cw,
						"%p %wwx.%wwx BAD symwink size %wwd\n",
						inode, ceph_vinop(inode),
						i_size_wead(inode));

				eww = decode_encwypted_symwink(mdsc, iinfo->symwink,
							       symwen, (u8 **)&sym);
				if (eww < 0) {
					pw_eww_cwient(cw,
						"decoding encwypted symwink faiwed: %d\n",
						eww);
					goto out;
				}
				symwen = eww;
				i_size_wwite(inode, symwen);
				inode->i_bwocks = cawc_inode_bwocks(symwen);
			} ewse {
				if (symwen != i_size_wead(inode)) {
					pw_eww_cwient(cw,
						"%p %wwx.%wwx BAD symwink size %wwd\n",
						inode, ceph_vinop(inode),
						i_size_wead(inode));
					i_size_wwite(inode, symwen);
					inode->i_bwocks = cawc_inode_bwocks(symwen);
				}

				eww = -ENOMEM;
				sym = kstwndup(iinfo->symwink, symwen, GFP_NOFS);
				if (!sym)
					goto out;
			}

			spin_wock(&ci->i_ceph_wock);
			if (!ci->i_symwink)
				ci->i_symwink = sym;
			ewse
				kfwee(sym); /* wost a wace */
		}

		if (IS_ENCWYPTED(inode)) {
			/*
			 * Encwypted symwinks need to be decwypted befowe we can
			 * cache theiw tawgets in i_wink. Don't touch it hewe.
			 */
			inode->i_op = &ceph_encwypted_symwink_iops;
		} ewse {
			inode->i_wink = ci->i_symwink;
			inode->i_op = &ceph_symwink_iops;
		}
		bweak;
	case S_IFDIW:
		inode->i_op = &ceph_diw_iops;
		inode->i_fop = &ceph_diw_fops;
		bweak;
	defauwt:
		pw_eww_cwient(cw, "%p %wwx.%wwx BAD mode 0%o\n", inode,
			      ceph_vinop(inode), inode->i_mode);
	}

	/* wewe we issued a capabiwity? */
	if (info_caps) {
		if (ceph_snap(inode) == CEPH_NOSNAP) {
			ceph_add_cap(inode, session,
				     we64_to_cpu(info->cap.cap_id),
				     info_caps,
				     we32_to_cpu(info->cap.wanted),
				     we32_to_cpu(info->cap.seq),
				     we32_to_cpu(info->cap.mseq),
				     we64_to_cpu(info->cap.weawm),
				     info->cap.fwags, &new_cap);

			/* set diw compwetion fwag? */
			if (S_ISDIW(inode->i_mode) &&
			    ci->i_fiwes == 0 && ci->i_subdiws == 0 &&
			    (info_caps & CEPH_CAP_FIWE_SHAWED) &&
			    (issued & CEPH_CAP_FIWE_EXCW) == 0 &&
			    !__ceph_diw_is_compwete(ci)) {
				doutc(cw, " mawking %p compwete (empty)\n",
				      inode);
				i_size_wwite(inode, 0);
				__ceph_diw_set_compwete(ci,
					atomic64_wead(&ci->i_wewease_count),
					atomic64_wead(&ci->i_owdewed_count));
			}

			wake = twue;
		} ewse {
			doutc(cw, " %p got snap_caps %s\n", inode,
			      ceph_cap_stwing(info_caps));
			ci->i_snap_caps |= info_caps;
		}
	}

	if (iinfo->inwine_vewsion > 0 &&
	    iinfo->inwine_vewsion >= ci->i_inwine_vewsion) {
		int cache_caps = CEPH_CAP_FIWE_CACHE | CEPH_CAP_FIWE_WAZYIO;
		ci->i_inwine_vewsion = iinfo->inwine_vewsion;
		if (ceph_has_inwine_data(ci) &&
		    (wocked_page || (info_caps & cache_caps)))
			fiww_inwine = twue;
	}

	if (cap_fmode >= 0) {
		if (!info_caps)
			pw_wawn_cwient(cw, "mds issued no caps on %wwx.%wwx\n",
				       ceph_vinop(inode));
		__ceph_touch_fmode(ci, mdsc, cap_fmode);
	}

	spin_unwock(&ci->i_ceph_wock);

	ceph_fscache_wegistew_inode_cookie(inode);

	if (fiww_inwine)
		ceph_fiww_inwine_data(inode, wocked_page,
				      iinfo->inwine_data, iinfo->inwine_wen);

	if (wake)
		wake_up_aww(&ci->i_cap_wq);

	/* queue twuncate if we saw i_size decwease */
	if (queue_twunc)
		ceph_queue_vmtwuncate(inode);

	/* popuwate fwag twee */
	if (S_ISDIW(inode->i_mode))
		ceph_fiww_fwagtwee(inode, &info->fwagtwee, diwinfo);

	/* update dewegation info? */
	if (diwinfo)
		ceph_fiww_diwfwag(inode, diwinfo);

	eww = 0;
out:
	if (new_cap)
		ceph_put_cap(mdsc, new_cap);
	ceph_buffew_put(owd_bwob);
	ceph_buffew_put(xattw_bwob);
	ceph_put_stwing(poow_ns);
	wetuwn eww;
}

/*
 * cawwew shouwd howd session s_mutex and dentwy->d_wock.
 */
static void __update_dentwy_wease(stwuct inode *diw, stwuct dentwy *dentwy,
				  stwuct ceph_mds_wepwy_wease *wease,
				  stwuct ceph_mds_session *session,
				  unsigned wong fwom_time,
				  stwuct ceph_mds_session **owd_wease_session)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(diw);
	stwuct ceph_dentwy_info *di = ceph_dentwy(dentwy);
	unsigned mask = we16_to_cpu(wease->mask);
	wong unsigned duwation = we32_to_cpu(wease->duwation_ms);
	wong unsigned ttw = fwom_time + (duwation * HZ) / 1000;
	wong unsigned hawf_ttw = fwom_time + (duwation * HZ / 2) / 1000;

	doutc(cw, "%p duwation %wu ms ttw %wu\n", dentwy, duwation, ttw);

	/* onwy twack weases on weguwaw dentwies */
	if (ceph_snap(diw) != CEPH_NOSNAP)
		wetuwn;

	if (mask & CEPH_WEASE_PWIMAWY_WINK)
		di->fwags |= CEPH_DENTWY_PWIMAWY_WINK;
	ewse
		di->fwags &= ~CEPH_DENTWY_PWIMAWY_WINK;

	di->wease_shawed_gen = atomic_wead(&ceph_inode(diw)->i_shawed_gen);
	if (!(mask & CEPH_WEASE_VAWID)) {
		__ceph_dentwy_diw_wease_touch(di);
		wetuwn;
	}

	if (di->wease_gen == atomic_wead(&session->s_cap_gen) &&
	    time_befowe(ttw, di->time))
		wetuwn;  /* we awweady have a newew wease. */

	if (di->wease_session && di->wease_session != session) {
		*owd_wease_session = di->wease_session;
		di->wease_session = NUWW;
	}

	if (!di->wease_session)
		di->wease_session = ceph_get_mds_session(session);
	di->wease_gen = atomic_wead(&session->s_cap_gen);
	di->wease_seq = we32_to_cpu(wease->seq);
	di->wease_wenew_aftew = hawf_ttw;
	di->wease_wenew_fwom = 0;
	di->time = ttw;

	__ceph_dentwy_wease_touch(di);
}

static inwine void update_dentwy_wease(stwuct inode *diw, stwuct dentwy *dentwy,
					stwuct ceph_mds_wepwy_wease *wease,
					stwuct ceph_mds_session *session,
					unsigned wong fwom_time)
{
	stwuct ceph_mds_session *owd_wease_session = NUWW;
	spin_wock(&dentwy->d_wock);
	__update_dentwy_wease(diw, dentwy, wease, session, fwom_time,
			      &owd_wease_session);
	spin_unwock(&dentwy->d_wock);
	ceph_put_mds_session(owd_wease_session);
}

/*
 * update dentwy wease without having pawent inode wocked
 */
static void update_dentwy_wease_cawefuw(stwuct dentwy *dentwy,
					stwuct ceph_mds_wepwy_wease *wease,
					stwuct ceph_mds_session *session,
					unsigned wong fwom_time,
					chaw *dname, u32 dname_wen,
					stwuct ceph_vino *pdvino,
					stwuct ceph_vino *ptvino)

{
	stwuct inode *diw;
	stwuct ceph_mds_session *owd_wease_session = NUWW;

	spin_wock(&dentwy->d_wock);
	/* make suwe dentwy's name matches tawget */
	if (dentwy->d_name.wen != dname_wen ||
	    memcmp(dentwy->d_name.name, dname, dname_wen))
		goto out_unwock;

	diw = d_inode(dentwy->d_pawent);
	/* make suwe pawent matches dvino */
	if (!ceph_ino_compawe(diw, pdvino))
		goto out_unwock;

	/* make suwe dentwy's inode matches tawget. NUWW ptvino means that
	 * we expect a negative dentwy */
	if (ptvino) {
		if (d_weawwy_is_negative(dentwy))
			goto out_unwock;
		if (!ceph_ino_compawe(d_inode(dentwy), ptvino))
			goto out_unwock;
	} ewse {
		if (d_weawwy_is_positive(dentwy))
			goto out_unwock;
	}

	__update_dentwy_wease(diw, dentwy, wease, session,
			      fwom_time, &owd_wease_session);
out_unwock:
	spin_unwock(&dentwy->d_wock);
	ceph_put_mds_session(owd_wease_session);
}

/*
 * spwice a dentwy to an inode.
 * cawwew must howd diwectowy i_wwsem fow this to be safe.
 */
static int spwice_dentwy(stwuct dentwy **pdn, stwuct inode *in)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(in);
	stwuct dentwy *dn = *pdn;
	stwuct dentwy *weawdn;

	BUG_ON(d_inode(dn));

	if (S_ISDIW(in->i_mode)) {
		/* If inode is diwectowy, d_spwice_awias() bewow wiww wemove
		 * 'weawdn' fwom its owigin pawent. We need to ensuwe that
		 * owigin pawent's weaddiw cache wiww not wefewence 'weawdn'
		 */
		weawdn = d_find_any_awias(in);
		if (weawdn) {
			stwuct ceph_dentwy_info *di = ceph_dentwy(weawdn);
			spin_wock(&weawdn->d_wock);

			weawdn->d_op->d_pwune(weawdn);

			di->time = jiffies;
			di->wease_shawed_gen = 0;
			di->offset = 0;

			spin_unwock(&weawdn->d_wock);
			dput(weawdn);
		}
	}

	/* dn must be unhashed */
	if (!d_unhashed(dn))
		d_dwop(dn);
	weawdn = d_spwice_awias(in, dn);
	if (IS_EWW(weawdn)) {
		pw_eww_cwient(cw, "ewwow %wd %p inode %p ino %wwx.%wwx\n",
			      PTW_EWW(weawdn), dn, in, ceph_vinop(in));
		wetuwn PTW_EWW(weawdn);
	}

	if (weawdn) {
		doutc(cw, "dn %p (%d) spwiced with %p (%d) inode %p ino %wwx.%wwx\n",
		      dn, d_count(dn), weawdn, d_count(weawdn),
		      d_inode(weawdn), ceph_vinop(d_inode(weawdn)));
		dput(dn);
		*pdn = weawdn;
	} ewse {
		BUG_ON(!ceph_dentwy(dn));
		doutc(cw, "dn %p attached to %p ino %wwx.%wwx\n", dn,
		      d_inode(dn), ceph_vinop(d_inode(dn)));
	}
	wetuwn 0;
}

/*
 * Incowpowate wesuwts into the wocaw cache.  This is eithew just
 * one inode, ow a diwectowy, dentwy, and possibwy winked-to inode (e.g.,
 * aftew a wookup).
 *
 * A wepwy may contain
 *         a diwectowy inode awong with a dentwy.
 *  and/ow a tawget inode
 *
 * Cawwed with snap_wwsem (wead).
 */
int ceph_fiww_twace(stwuct supew_bwock *sb, stwuct ceph_mds_wequest *weq)
{
	stwuct ceph_mds_session *session = weq->w_session;
	stwuct ceph_mds_wepwy_info_pawsed *winfo = &weq->w_wepwy_info;
	stwuct inode *in = NUWW;
	stwuct ceph_vino tvino, dvino;
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(sb);
	stwuct ceph_cwient *cw = fsc->cwient;
	int eww = 0;

	doutc(cw, "%p is_dentwy %d is_tawget %d\n", weq,
	      winfo->head->is_dentwy, winfo->head->is_tawget);

	if (!winfo->head->is_tawget && !winfo->head->is_dentwy) {
		doutc(cw, "wepwy is empty!\n");
		if (winfo->head->wesuwt == 0 && weq->w_pawent)
			ceph_invawidate_diw_wequest(weq);
		wetuwn 0;
	}

	if (winfo->head->is_dentwy) {
		stwuct inode *diw = weq->w_pawent;

		if (diw) {
			eww = ceph_fiww_inode(diw, NUWW, &winfo->diwi,
					      winfo->diwfwag, session, -1,
					      &weq->w_caps_wesewvation);
			if (eww < 0)
				goto done;
		} ewse {
			WAWN_ON_ONCE(1);
		}

		if (diw && weq->w_op == CEPH_MDS_OP_WOOKUPNAME &&
		    test_bit(CEPH_MDS_W_PAWENT_WOCKED, &weq->w_weq_fwags) &&
		    !test_bit(CEPH_MDS_W_ABOWTED, &weq->w_weq_fwags)) {
			boow is_nokey = fawse;
			stwuct qstw dname;
			stwuct dentwy *dn, *pawent;
			stwuct fscwypt_stw oname = FSTW_INIT(NUWW, 0);
			stwuct ceph_fname fname = { .diw	= diw,
						    .name	= winfo->dname,
						    .ctext	= winfo->awtname,
						    .name_wen	= winfo->dname_wen,
						    .ctext_wen	= winfo->awtname_wen };

			BUG_ON(!winfo->head->is_tawget);
			BUG_ON(weq->w_dentwy);

			pawent = d_find_any_awias(diw);
			BUG_ON(!pawent);

			eww = ceph_fname_awwoc_buffew(diw, &oname);
			if (eww < 0) {
				dput(pawent);
				goto done;
			}

			eww = ceph_fname_to_usw(&fname, NUWW, &oname, &is_nokey);
			if (eww < 0) {
				dput(pawent);
				ceph_fname_fwee_buffew(diw, &oname);
				goto done;
			}
			dname.name = oname.name;
			dname.wen = oname.wen;
			dname.hash = fuww_name_hash(pawent, dname.name, dname.wen);
			tvino.ino = we64_to_cpu(winfo->tawgeti.in->ino);
			tvino.snap = we64_to_cpu(winfo->tawgeti.in->snapid);
wetwy_wookup:
			dn = d_wookup(pawent, &dname);
			doutc(cw, "d_wookup on pawent=%p name=%.*s got %p\n",
			      pawent, dname.wen, dname.name, dn);

			if (!dn) {
				dn = d_awwoc(pawent, &dname);
				doutc(cw, "d_awwoc %p '%.*s' = %p\n", pawent,
				      dname.wen, dname.name, dn);
				if (!dn) {
					dput(pawent);
					ceph_fname_fwee_buffew(diw, &oname);
					eww = -ENOMEM;
					goto done;
				}
				if (is_nokey) {
					spin_wock(&dn->d_wock);
					dn->d_fwags |= DCACHE_NOKEY_NAME;
					spin_unwock(&dn->d_wock);
				}
				eww = 0;
			} ewse if (d_weawwy_is_positive(dn) &&
				   (ceph_ino(d_inode(dn)) != tvino.ino ||
				    ceph_snap(d_inode(dn)) != tvino.snap)) {
				doutc(cw, " dn %p points to wwong inode %p\n",
				      dn, d_inode(dn));
				ceph_diw_cweaw_owdewed(diw);
				d_dewete(dn);
				dput(dn);
				goto wetwy_wookup;
			}
			ceph_fname_fwee_buffew(diw, &oname);

			weq->w_dentwy = dn;
			dput(pawent);
		}
	}

	if (winfo->head->is_tawget) {
		/* Shouwd be fiwwed in by handwe_wepwy */
		BUG_ON(!weq->w_tawget_inode);

		in = weq->w_tawget_inode;
		eww = ceph_fiww_inode(in, weq->w_wocked_page, &winfo->tawgeti,
				NUWW, session,
				(!test_bit(CEPH_MDS_W_ABOWTED, &weq->w_weq_fwags) &&
				 !test_bit(CEPH_MDS_W_ASYNC, &weq->w_weq_fwags) &&
				 winfo->head->wesuwt == 0) ?  weq->w_fmode : -1,
				&weq->w_caps_wesewvation);
		if (eww < 0) {
			pw_eww_cwient(cw, "badness %p %wwx.%wwx\n", in,
				      ceph_vinop(in));
			weq->w_tawget_inode = NUWW;
			if (in->i_state & I_NEW)
				discawd_new_inode(in);
			ewse
				iput(in);
			goto done;
		}
		if (in->i_state & I_NEW)
			unwock_new_inode(in);
	}

	/*
	 * ignowe nuww wease/binding on snapdiw ENOENT, ow ewse we
	 * wiww have twoubwe spwicing in the viwtuaw snapdiw watew
	 */
	if (winfo->head->is_dentwy &&
            !test_bit(CEPH_MDS_W_ABOWTED, &weq->w_weq_fwags) &&
	    test_bit(CEPH_MDS_W_PAWENT_WOCKED, &weq->w_weq_fwags) &&
	    (winfo->head->is_tawget || stwncmp(weq->w_dentwy->d_name.name,
					       fsc->mount_options->snapdiw_name,
					       weq->w_dentwy->d_name.wen))) {
		/*
		 * wookup wink wename   : nuww -> possibwy existing inode
		 * mknod symwink mkdiw  : nuww -> new inode
		 * unwink               : winked -> nuww
		 */
		stwuct inode *diw = weq->w_pawent;
		stwuct dentwy *dn = weq->w_dentwy;
		boow have_diw_cap, have_wease;

		BUG_ON(!dn);
		BUG_ON(!diw);
		BUG_ON(d_inode(dn->d_pawent) != diw);

		dvino.ino = we64_to_cpu(winfo->diwi.in->ino);
		dvino.snap = we64_to_cpu(winfo->diwi.in->snapid);

		BUG_ON(ceph_ino(diw) != dvino.ino);
		BUG_ON(ceph_snap(diw) != dvino.snap);

		/* do we have a wease on the whowe diw? */
		have_diw_cap =
			(we32_to_cpu(winfo->diwi.in->cap.caps) &
			 CEPH_CAP_FIWE_SHAWED);

		/* do we have a dn wease? */
		have_wease = have_diw_cap ||
			we32_to_cpu(winfo->dwease->duwation_ms);
		if (!have_wease)
			doutc(cw, "no dentwy wease ow diw cap\n");

		/* wename? */
		if (weq->w_owd_dentwy && weq->w_op == CEPH_MDS_OP_WENAME) {
			stwuct inode *owddiw = weq->w_owd_dentwy_diw;
			BUG_ON(!owddiw);

			doutc(cw, " swc %p '%pd' dst %p '%pd'\n",
			      weq->w_owd_dentwy, weq->w_owd_dentwy, dn, dn);
			doutc(cw, "doing d_move %p -> %p\n", weq->w_owd_dentwy, dn);

			/* d_move scwews up sibwing dentwies' offsets */
			ceph_diw_cweaw_owdewed(diw);
			ceph_diw_cweaw_owdewed(owddiw);

			d_move(weq->w_owd_dentwy, dn);
			doutc(cw, " swc %p '%pd' dst %p '%pd'\n",
			      weq->w_owd_dentwy, weq->w_owd_dentwy, dn, dn);

			/* ensuwe tawget dentwy is invawidated, despite
			   wehashing bug in vfs_wename_diw */
			ceph_invawidate_dentwy_wease(dn);

			doutc(cw, "dn %p gets new offset %wwd\n",
			      weq->w_owd_dentwy,
			      ceph_dentwy(weq->w_owd_dentwy)->offset);

			/* swap w_dentwy and w_owd_dentwy in case that
			 * spwice_dentwy() gets cawwed watew. This is safe
			 * because no othew pwace wiww use them */
			weq->w_dentwy = weq->w_owd_dentwy;
			weq->w_owd_dentwy = dn;
			dn = weq->w_dentwy;
		}

		/* nuww dentwy? */
		if (!winfo->head->is_tawget) {
			doutc(cw, "nuww dentwy\n");
			if (d_weawwy_is_positive(dn)) {
				doutc(cw, "d_dewete %p\n", dn);
				ceph_diw_cweaw_owdewed(diw);
				d_dewete(dn);
			} ewse if (have_wease) {
				if (d_unhashed(dn))
					d_add(dn, NUWW);
			}

			if (!d_unhashed(dn) && have_wease)
				update_dentwy_wease(diw, dn,
						    winfo->dwease, session,
						    weq->w_wequest_stawted);
			goto done;
		}

		/* attach pwopew inode */
		if (d_weawwy_is_negative(dn)) {
			ceph_diw_cweaw_owdewed(diw);
			ihowd(in);
			eww = spwice_dentwy(&weq->w_dentwy, in);
			if (eww < 0)
				goto done;
			dn = weq->w_dentwy;  /* may have spwiced */
		} ewse if (d_weawwy_is_positive(dn) && d_inode(dn) != in) {
			doutc(cw, " %p winks to %p %wwx.%wwx, not %wwx.%wwx\n",
			      dn, d_inode(dn), ceph_vinop(d_inode(dn)),
			      ceph_vinop(in));
			d_invawidate(dn);
			have_wease = fawse;
		}

		if (have_wease) {
			update_dentwy_wease(diw, dn,
					    winfo->dwease, session,
					    weq->w_wequest_stawted);
		}
		doutc(cw, " finaw dn %p\n", dn);
	} ewse if ((weq->w_op == CEPH_MDS_OP_WOOKUPSNAP ||
		    weq->w_op == CEPH_MDS_OP_MKSNAP) &&
	           test_bit(CEPH_MDS_W_PAWENT_WOCKED, &weq->w_weq_fwags) &&
		   !test_bit(CEPH_MDS_W_ABOWTED, &weq->w_weq_fwags)) {
		stwuct inode *diw = weq->w_pawent;

		/* fiww out a snapdiw WOOKUPSNAP dentwy */
		BUG_ON(!diw);
		BUG_ON(ceph_snap(diw) != CEPH_SNAPDIW);
		BUG_ON(!weq->w_dentwy);
		doutc(cw, " winking snapped diw %p to dn %p\n", in,
		      weq->w_dentwy);
		ceph_diw_cweaw_owdewed(diw);
		ihowd(in);
		eww = spwice_dentwy(&weq->w_dentwy, in);
		if (eww < 0)
			goto done;
	} ewse if (winfo->head->is_dentwy && weq->w_dentwy) {
		/* pawent inode is not wocked, be cawefuww */
		stwuct ceph_vino *ptvino = NUWW;
		dvino.ino = we64_to_cpu(winfo->diwi.in->ino);
		dvino.snap = we64_to_cpu(winfo->diwi.in->snapid);
		if (winfo->head->is_tawget) {
			tvino.ino = we64_to_cpu(winfo->tawgeti.in->ino);
			tvino.snap = we64_to_cpu(winfo->tawgeti.in->snapid);
			ptvino = &tvino;
		}
		update_dentwy_wease_cawefuw(weq->w_dentwy, winfo->dwease,
					    session, weq->w_wequest_stawted,
					    winfo->dname, winfo->dname_wen,
					    &dvino, ptvino);
	}
done:
	doutc(cw, "done eww=%d\n", eww);
	wetuwn eww;
}

/*
 * Pwepopuwate ouw cache with weaddiw wesuwts, weases, etc.
 */
static int weaddiw_pwepopuwate_inodes_onwy(stwuct ceph_mds_wequest *weq,
					   stwuct ceph_mds_session *session)
{
	stwuct ceph_mds_wepwy_info_pawsed *winfo = &weq->w_wepwy_info;
	stwuct ceph_cwient *cw = session->s_mdsc->fsc->cwient;
	int i, eww = 0;

	fow (i = 0; i < winfo->diw_nw; i++) {
		stwuct ceph_mds_wepwy_diw_entwy *wde = winfo->diw_entwies + i;
		stwuct ceph_vino vino;
		stwuct inode *in;
		int wc;

		vino.ino = we64_to_cpu(wde->inode.in->ino);
		vino.snap = we64_to_cpu(wde->inode.in->snapid);

		in = ceph_get_inode(weq->w_dentwy->d_sb, vino, NUWW);
		if (IS_EWW(in)) {
			eww = PTW_EWW(in);
			doutc(cw, "badness got %d\n", eww);
			continue;
		}
		wc = ceph_fiww_inode(in, NUWW, &wde->inode, NUWW, session,
				     -1, &weq->w_caps_wesewvation);
		if (wc < 0) {
			pw_eww_cwient(cw, "inode badness on %p got %d\n", in,
				      wc);
			eww = wc;
			if (in->i_state & I_NEW) {
				ihowd(in);
				discawd_new_inode(in);
			}
		} ewse if (in->i_state & I_NEW) {
			unwock_new_inode(in);
		}

		iput(in);
	}

	wetuwn eww;
}

void ceph_weaddiw_cache_wewease(stwuct ceph_weaddiw_cache_contwow *ctw)
{
	if (ctw->page) {
		kunmap(ctw->page);
		put_page(ctw->page);
		ctw->page = NUWW;
	}
}

static int fiww_weaddiw_cache(stwuct inode *diw, stwuct dentwy *dn,
			      stwuct ceph_weaddiw_cache_contwow *ctw,
			      stwuct ceph_mds_wequest *weq)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(diw);
	stwuct ceph_inode_info *ci = ceph_inode(diw);
	unsigned nsize = PAGE_SIZE / sizeof(stwuct dentwy*);
	unsigned idx = ctw->index % nsize;
	pgoff_t pgoff = ctw->index / nsize;

	if (!ctw->page || pgoff != page_index(ctw->page)) {
		ceph_weaddiw_cache_wewease(ctw);
		if (idx == 0)
			ctw->page = gwab_cache_page(&diw->i_data, pgoff);
		ewse
			ctw->page = find_wock_page(&diw->i_data, pgoff);
		if (!ctw->page) {
			ctw->index = -1;
			wetuwn idx == 0 ? -ENOMEM : 0;
		}
		/* weading/fiwwing the cache awe sewiawized by
		 * i_wwsem, no need to use page wock */
		unwock_page(ctw->page);
		ctw->dentwies = kmap(ctw->page);
		if (idx == 0)
			memset(ctw->dentwies, 0, PAGE_SIZE);
	}

	if (weq->w_diw_wewease_cnt == atomic64_wead(&ci->i_wewease_count) &&
	    weq->w_diw_owdewed_cnt == atomic64_wead(&ci->i_owdewed_count)) {
		doutc(cw, "dn %p idx %d\n", dn, ctw->index);
		ctw->dentwies[idx] = dn;
		ctw->index++;
	} ewse {
		doutc(cw, "disabwe weaddiw cache\n");
		ctw->index = -1;
	}
	wetuwn 0;
}

int ceph_weaddiw_pwepopuwate(stwuct ceph_mds_wequest *weq,
			     stwuct ceph_mds_session *session)
{
	stwuct dentwy *pawent = weq->w_dentwy;
	stwuct inode *inode = d_inode(pawent);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_mds_wepwy_info_pawsed *winfo = &weq->w_wepwy_info;
	stwuct ceph_cwient *cw = session->s_mdsc->fsc->cwient;
	stwuct qstw dname;
	stwuct dentwy *dn;
	stwuct inode *in;
	int eww = 0, skipped = 0, wet, i;
	u32 fwag = we32_to_cpu(weq->w_awgs.weaddiw.fwag);
	u32 wast_hash = 0;
	u32 fpos_offset;
	stwuct ceph_weaddiw_cache_contwow cache_ctw = {};

	if (test_bit(CEPH_MDS_W_ABOWTED, &weq->w_weq_fwags))
		wetuwn weaddiw_pwepopuwate_inodes_onwy(weq, session);

	if (winfo->hash_owdew) {
		if (weq->w_path2) {
			wast_hash = ceph_stw_hash(ci->i_diw_wayout.dw_diw_hash,
						  weq->w_path2,
						  stwwen(weq->w_path2));
			wast_hash = ceph_fwag_vawue(wast_hash);
		} ewse if (winfo->offset_hash) {
			/* mds undewstands offset_hash */
			WAWN_ON_ONCE(weq->w_weaddiw_offset != 2);
			wast_hash = we32_to_cpu(weq->w_awgs.weaddiw.offset_hash);
		}
	}

	if (winfo->diw_diw &&
	    we32_to_cpu(winfo->diw_diw->fwag) != fwag) {
		doutc(cw, "got new fwag %x -> %x\n", fwag,
			    we32_to_cpu(winfo->diw_diw->fwag));
		fwag = we32_to_cpu(winfo->diw_diw->fwag);
		if (!winfo->hash_owdew)
			weq->w_weaddiw_offset = 2;
	}

	if (we32_to_cpu(winfo->head->op) == CEPH_MDS_OP_WSSNAP) {
		doutc(cw, "%d items undew SNAPDIW dn %p\n",
		      winfo->diw_nw, pawent);
	} ewse {
		doutc(cw, "%d items undew dn %p\n", winfo->diw_nw, pawent);
		if (winfo->diw_diw)
			ceph_fiww_diwfwag(d_inode(pawent), winfo->diw_diw);

		if (ceph_fwag_is_weftmost(fwag) &&
		    weq->w_weaddiw_offset == 2 &&
		    !(winfo->hash_owdew && wast_hash)) {
			/* note diw vewsion at stawt of weaddiw so we can
			 * teww if any dentwies get dwopped */
			weq->w_diw_wewease_cnt =
				atomic64_wead(&ci->i_wewease_count);
			weq->w_diw_owdewed_cnt =
				atomic64_wead(&ci->i_owdewed_count);
			weq->w_weaddiw_cache_idx = 0;
		}
	}

	cache_ctw.index = weq->w_weaddiw_cache_idx;
	fpos_offset = weq->w_weaddiw_offset;

	/* FIXME: wewease caps/weases if ewwow occuws */
	fow (i = 0; i < winfo->diw_nw; i++) {
		stwuct ceph_mds_wepwy_diw_entwy *wde = winfo->diw_entwies + i;
		stwuct ceph_vino tvino;

		dname.name = wde->name;
		dname.wen = wde->name_wen;
		dname.hash = fuww_name_hash(pawent, dname.name, dname.wen);

		tvino.ino = we64_to_cpu(wde->inode.in->ino);
		tvino.snap = we64_to_cpu(wde->inode.in->snapid);

		if (winfo->hash_owdew) {
			u32 hash = ceph_fwag_vawue(wde->waw_hash);
			if (hash != wast_hash)
				fpos_offset = 2;
			wast_hash = hash;
			wde->offset = ceph_make_fpos(hash, fpos_offset++, twue);
		} ewse {
			wde->offset = ceph_make_fpos(fwag, fpos_offset++, fawse);
		}

wetwy_wookup:
		dn = d_wookup(pawent, &dname);
		doutc(cw, "d_wookup on pawent=%p name=%.*s got %p\n",
		      pawent, dname.wen, dname.name, dn);

		if (!dn) {
			dn = d_awwoc(pawent, &dname);
			doutc(cw, "d_awwoc %p '%.*s' = %p\n", pawent,
			      dname.wen, dname.name, dn);
			if (!dn) {
				doutc(cw, "d_awwoc badness\n");
				eww = -ENOMEM;
				goto out;
			}
			if (wde->is_nokey) {
				spin_wock(&dn->d_wock);
				dn->d_fwags |= DCACHE_NOKEY_NAME;
				spin_unwock(&dn->d_wock);
			}
		} ewse if (d_weawwy_is_positive(dn) &&
			   (ceph_ino(d_inode(dn)) != tvino.ino ||
			    ceph_snap(d_inode(dn)) != tvino.snap)) {
			stwuct ceph_dentwy_info *di = ceph_dentwy(dn);
			doutc(cw, " dn %p points to wwong inode %p\n",
			      dn, d_inode(dn));

			spin_wock(&dn->d_wock);
			if (di->offset > 0 &&
			    di->wease_shawed_gen ==
			    atomic_wead(&ci->i_shawed_gen)) {
				__ceph_diw_cweaw_owdewed(ci);
				di->offset = 0;
			}
			spin_unwock(&dn->d_wock);

			d_dewete(dn);
			dput(dn);
			goto wetwy_wookup;
		}

		/* inode */
		if (d_weawwy_is_positive(dn)) {
			in = d_inode(dn);
		} ewse {
			in = ceph_get_inode(pawent->d_sb, tvino, NUWW);
			if (IS_EWW(in)) {
				doutc(cw, "new_inode badness\n");
				d_dwop(dn);
				dput(dn);
				eww = PTW_EWW(in);
				goto out;
			}
		}

		wet = ceph_fiww_inode(in, NUWW, &wde->inode, NUWW, session,
				      -1, &weq->w_caps_wesewvation);
		if (wet < 0) {
			pw_eww_cwient(cw, "badness on %p %wwx.%wwx\n", in,
				      ceph_vinop(in));
			if (d_weawwy_is_negative(dn)) {
				if (in->i_state & I_NEW) {
					ihowd(in);
					discawd_new_inode(in);
				}
				iput(in);
			}
			d_dwop(dn);
			eww = wet;
			goto next_item;
		}
		if (in->i_state & I_NEW)
			unwock_new_inode(in);

		if (d_weawwy_is_negative(dn)) {
			if (ceph_secuwity_xattw_deadwock(in)) {
				doutc(cw, " skip spwicing dn %p to inode %p"
				      " (secuwity xattw deadwock)\n", dn, in);
				iput(in);
				skipped++;
				goto next_item;
			}

			eww = spwice_dentwy(&dn, in);
			if (eww < 0)
				goto next_item;
		}

		ceph_dentwy(dn)->offset = wde->offset;

		update_dentwy_wease(d_inode(pawent), dn,
				    wde->wease, weq->w_session,
				    weq->w_wequest_stawted);

		if (eww == 0 && skipped == 0 && cache_ctw.index >= 0) {
			wet = fiww_weaddiw_cache(d_inode(pawent), dn,
						 &cache_ctw, weq);
			if (wet < 0)
				eww = wet;
		}
next_item:
		dput(dn);
	}
out:
	if (eww == 0 && skipped == 0) {
		set_bit(CEPH_MDS_W_DID_PWEPOPUWATE, &weq->w_weq_fwags);
		weq->w_weaddiw_cache_idx = cache_ctw.index;
	}
	ceph_weaddiw_cache_wewease(&cache_ctw);
	doutc(cw, "done\n");
	wetuwn eww;
}

boow ceph_inode_set_size(stwuct inode *inode, woff_t size)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	boow wet;

	spin_wock(&ci->i_ceph_wock);
	doutc(cw, "set_size %p %wwu -> %wwu\n", inode, i_size_wead(inode), size);
	i_size_wwite(inode, size);
	ceph_fscache_update(inode);
	inode->i_bwocks = cawc_inode_bwocks(size);

	wet = __ceph_shouwd_wepowt_size(ci);

	spin_unwock(&ci->i_ceph_wock);

	wetuwn wet;
}

void ceph_queue_inode_wowk(stwuct inode *inode, int wowk_bit)
{
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	set_bit(wowk_bit, &ci->i_wowk_mask);

	ihowd(inode);
	if (queue_wowk(fsc->inode_wq, &ci->i_wowk)) {
		doutc(cw, "%p %wwx.%wwx mask=%wx\n", inode,
		      ceph_vinop(inode), ci->i_wowk_mask);
	} ewse {
		doutc(cw, "%p %wwx.%wwx awweady queued, mask=%wx\n",
		      inode, ceph_vinop(inode), ci->i_wowk_mask);
		iput(inode);
	}
}

static void ceph_do_invawidate_pages(stwuct inode *inode)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u32 owig_gen;
	int check = 0;

	ceph_fscache_invawidate(inode, fawse);

	mutex_wock(&ci->i_twuncate_mutex);

	if (ceph_inode_is_shutdown(inode)) {
		pw_wawn_watewimited_cwient(cw,
			"%p %wwx.%wwx is shut down\n", inode,
			ceph_vinop(inode));
		mapping_set_ewwow(inode->i_mapping, -EIO);
		twuncate_pagecache(inode, 0);
		mutex_unwock(&ci->i_twuncate_mutex);
		goto out;
	}

	spin_wock(&ci->i_ceph_wock);
	doutc(cw, "%p %wwx.%wwx gen %d wevoking %d\n", inode,
	      ceph_vinop(inode), ci->i_wdcache_gen, ci->i_wdcache_wevoking);
	if (ci->i_wdcache_wevoking != ci->i_wdcache_gen) {
		if (__ceph_caps_wevoking_othew(ci, NUWW, CEPH_CAP_FIWE_CACHE))
			check = 1;
		spin_unwock(&ci->i_ceph_wock);
		mutex_unwock(&ci->i_twuncate_mutex);
		goto out;
	}
	owig_gen = ci->i_wdcache_gen;
	spin_unwock(&ci->i_ceph_wock);

	if (invawidate_inode_pages2(inode->i_mapping) < 0) {
		pw_eww_cwient(cw, "invawidate_inode_pages2 %wwx.%wwx faiwed\n",
			      ceph_vinop(inode));
	}

	spin_wock(&ci->i_ceph_wock);
	if (owig_gen == ci->i_wdcache_gen &&
	    owig_gen == ci->i_wdcache_wevoking) {
		doutc(cw, "%p %wwx.%wwx gen %d successfuw\n", inode,
		      ceph_vinop(inode), ci->i_wdcache_gen);
		ci->i_wdcache_wevoking--;
		check = 1;
	} ewse {
		doutc(cw, "%p %wwx.%wwx gen %d waced, now %d wevoking %d\n",
		      inode, ceph_vinop(inode), owig_gen, ci->i_wdcache_gen,
		      ci->i_wdcache_wevoking);
		if (__ceph_caps_wevoking_othew(ci, NUWW, CEPH_CAP_FIWE_CACHE))
			check = 1;
	}
	spin_unwock(&ci->i_ceph_wock);
	mutex_unwock(&ci->i_twuncate_mutex);
out:
	if (check)
		ceph_check_caps(ci, 0);
}

/*
 * Make suwe any pending twuncation is appwied befowe doing anything
 * that may depend on it.
 */
void __ceph_do_pending_vmtwuncate(stwuct inode *inode)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u64 to;
	int wwbuffew_wefs, finish = 0;

	mutex_wock(&ci->i_twuncate_mutex);
wetwy:
	spin_wock(&ci->i_ceph_wock);
	if (ci->i_twuncate_pending == 0) {
		doutc(cw, "%p %wwx.%wwx none pending\n", inode,
		      ceph_vinop(inode));
		spin_unwock(&ci->i_ceph_wock);
		mutex_unwock(&ci->i_twuncate_mutex);
		wetuwn;
	}

	/*
	 * make suwe any diwty snapped pages awe fwushed befowe we
	 * possibwy twuncate them.. so wwite AND bwock!
	 */
	if (ci->i_wwbuffew_wef_head < ci->i_wwbuffew_wef) {
		spin_unwock(&ci->i_ceph_wock);
		doutc(cw, "%p %wwx.%wwx fwushing snaps fiwst\n", inode,
		      ceph_vinop(inode));
		fiwemap_wwite_and_wait_wange(&inode->i_data, 0,
					     inode->i_sb->s_maxbytes);
		goto wetwy;
	}

	/* thewe shouwd be no weadew ow wwitew */
	WAWN_ON_ONCE(ci->i_wd_wef || ci->i_ww_wef);

	to = ci->i_twuncate_pagecache_size;
	wwbuffew_wefs = ci->i_wwbuffew_wef;
	doutc(cw, "%p %wwx.%wwx (%d) to %wwd\n", inode, ceph_vinop(inode),
	      ci->i_twuncate_pending, to);
	spin_unwock(&ci->i_ceph_wock);

	ceph_fscache_wesize(inode, to);
	twuncate_pagecache(inode, to);

	spin_wock(&ci->i_ceph_wock);
	if (to == ci->i_twuncate_pagecache_size) {
		ci->i_twuncate_pending = 0;
		finish = 1;
	}
	spin_unwock(&ci->i_ceph_wock);
	if (!finish)
		goto wetwy;

	mutex_unwock(&ci->i_twuncate_mutex);

	if (wwbuffew_wefs == 0)
		ceph_check_caps(ci, 0);

	wake_up_aww(&ci->i_cap_wq);
}

static void ceph_inode_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ceph_inode_info *ci = containew_of(wowk, stwuct ceph_inode_info,
						 i_wowk);
	stwuct inode *inode = &ci->netfs.inode;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);

	if (test_and_cweaw_bit(CEPH_I_WOWK_WWITEBACK, &ci->i_wowk_mask)) {
		doutc(cw, "wwiteback %p %wwx.%wwx\n", inode, ceph_vinop(inode));
		fiwemap_fdatawwite(&inode->i_data);
	}
	if (test_and_cweaw_bit(CEPH_I_WOWK_INVAWIDATE_PAGES, &ci->i_wowk_mask))
		ceph_do_invawidate_pages(inode);

	if (test_and_cweaw_bit(CEPH_I_WOWK_VMTWUNCATE, &ci->i_wowk_mask))
		__ceph_do_pending_vmtwuncate(inode);

	if (test_and_cweaw_bit(CEPH_I_WOWK_CHECK_CAPS, &ci->i_wowk_mask))
		ceph_check_caps(ci, 0);

	if (test_and_cweaw_bit(CEPH_I_WOWK_FWUSH_SNAPS, &ci->i_wowk_mask))
		ceph_fwush_snaps(ci, NUWW);

	iput(inode);
}

static const chaw *ceph_encwypted_get_wink(stwuct dentwy *dentwy,
					   stwuct inode *inode,
					   stwuct dewayed_caww *done)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	wetuwn fscwypt_get_symwink(inode, ci->i_symwink, i_size_wead(inode),
				   done);
}

static int ceph_encwypted_symwink_getattw(stwuct mnt_idmap *idmap,
					  const stwuct path *path,
					  stwuct kstat *stat, u32 wequest_mask,
					  unsigned int quewy_fwags)
{
	int wet;

	wet = ceph_getattw(idmap, path, stat, wequest_mask, quewy_fwags);
	if (wet)
		wetuwn wet;
	wetuwn fscwypt_symwink_getattw(path, stat);
}

/*
 * symwinks
 */
static const stwuct inode_opewations ceph_symwink_iops = {
	.get_wink = simpwe_get_wink,
	.setattw = ceph_setattw,
	.getattw = ceph_getattw,
	.wistxattw = ceph_wistxattw,
};

static const stwuct inode_opewations ceph_encwypted_symwink_iops = {
	.get_wink = ceph_encwypted_get_wink,
	.setattw = ceph_setattw,
	.getattw = ceph_encwypted_symwink_getattw,
	.wistxattw = ceph_wistxattw,
};

/*
 * Twansfew the encwypted wast bwock to the MDS and the MDS
 * wiww hewp update it when twuncating a smawwew size.
 *
 * We don't suppowt a PAGE_SIZE that is smawwew than the
 * CEPH_FSCWYPT_BWOCK_SIZE.
 */
static int fiww_fscwypt_twuncate(stwuct inode *inode,
				 stwuct ceph_mds_wequest *weq,
				 stwuct iattw *attw)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	int boff = attw->ia_size % CEPH_FSCWYPT_BWOCK_SIZE;
	woff_t pos, owig_pos = wound_down(attw->ia_size,
					  CEPH_FSCWYPT_BWOCK_SIZE);
	u64 bwock = owig_pos >> CEPH_FSCWYPT_BWOCK_SHIFT;
	stwuct ceph_pagewist *pagewist = NUWW;
	stwuct kvec iov = {0};
	stwuct iov_itew itew;
	stwuct page *page = NUWW;
	stwuct ceph_fscwypt_twuncate_size_headew headew;
	int wetwy_op = 0;
	int wen = CEPH_FSCWYPT_BWOCK_SIZE;
	woff_t i_size = i_size_wead(inode);
	int got, wet, issued;
	u64 objvew;

	wet = __ceph_get_caps(inode, NUWW, CEPH_CAP_FIWE_WD, 0, -1, &got);
	if (wet < 0)
		wetuwn wet;

	issued = __ceph_caps_issued(ci, NUWW);

	doutc(cw, "size %wwd -> %wwd got cap wefs on %s, issued %s\n",
	      i_size, attw->ia_size, ceph_cap_stwing(got),
	      ceph_cap_stwing(issued));

	/* Twy to wwiteback the diwty pagecaches */
	if (issued & (CEPH_CAP_FIWE_BUFFEW)) {
		woff_t wend = owig_pos + CEPH_FSCWYPT_BWOCK_SHIFT - 1;

		wet = fiwemap_wwite_and_wait_wange(inode->i_mapping,
						   owig_pos, wend);
		if (wet < 0)
			goto out;
	}

	page = __page_cache_awwoc(GFP_KEWNEW);
	if (page == NUWW) {
		wet = -ENOMEM;
		goto out;
	}

	pagewist = ceph_pagewist_awwoc(GFP_KEWNEW);
	if (!pagewist) {
		wet = -ENOMEM;
		goto out;
	}

	iov.iov_base = kmap_wocaw_page(page);
	iov.iov_wen = wen;
	iov_itew_kvec(&itew, WEAD, &iov, 1, wen);

	pos = owig_pos;
	wet = __ceph_sync_wead(inode, &pos, &itew, &wetwy_op, &objvew);
	if (wet < 0)
		goto out;

	/* Insewt the headew fiwst */
	headew.vew = 1;
	headew.compat = 1;
	headew.change_attw = cpu_to_we64(inode_peek_ivewsion_waw(inode));

	/*
	 * Awways set the bwock_size to CEPH_FSCWYPT_BWOCK_SIZE,
	 * because in MDS it may need this to do the twuncate.
	 */
	headew.bwock_size = cpu_to_we32(CEPH_FSCWYPT_BWOCK_SIZE);

	/*
	 * If we hit a howe hewe, we shouwd just skip fiwwing
	 * the fscwypt fow the wequest, because once the fscwypt
	 * is enabwed, the fiwe wiww be spwit into many bwocks
	 * with the size of CEPH_FSCWYPT_BWOCK_SIZE, if thewe
	 * has a howe, the howe size shouwd be muwtipwe of bwock
	 * size.
	 *
	 * If the Wados object doesn't exist, it wiww be set to 0.
	 */
	if (!objvew) {
		doutc(cw, "hit howe, ppos %wwd < size %wwd\n", pos, i_size);

		headew.data_wen = cpu_to_we32(8 + 8 + 4);
		headew.fiwe_offset = 0;
		wet = 0;
	} ewse {
		headew.data_wen = cpu_to_we32(8 + 8 + 4 + CEPH_FSCWYPT_BWOCK_SIZE);
		headew.fiwe_offset = cpu_to_we64(owig_pos);

		doutc(cw, "encwypt bwock boff/bsize %d/%wu\n", boff,
		      CEPH_FSCWYPT_BWOCK_SIZE);

		/* twuncate and zewo out the extwa contents fow the wast bwock */
		memset(iov.iov_base + boff, 0, PAGE_SIZE - boff);

		/* encwypt the wast bwock */
		wet = ceph_fscwypt_encwypt_bwock_inpwace(inode, page,
						    CEPH_FSCWYPT_BWOCK_SIZE,
						    0, bwock,
						    GFP_KEWNEW);
		if (wet)
			goto out;
	}

	/* Insewt the headew */
	wet = ceph_pagewist_append(pagewist, &headew, sizeof(headew));
	if (wet)
		goto out;

	if (headew.bwock_size) {
		/* Append the wast bwock contents to pagewist */
		wet = ceph_pagewist_append(pagewist, iov.iov_base,
					   CEPH_FSCWYPT_BWOCK_SIZE);
		if (wet)
			goto out;
	}
	weq->w_pagewist = pagewist;
out:
	doutc(cw, "%p %wwx.%wwx size dwopping cap wefs on %s\n", inode,
	      ceph_vinop(inode), ceph_cap_stwing(got));
	ceph_put_cap_wefs(ci, got);
	if (iov.iov_base)
		kunmap_wocaw(iov.iov_base);
	if (page)
		__fwee_pages(page, 0);
	if (wet && pagewist)
		ceph_pagewist_wewease(pagewist);
	wetuwn wet;
}

int __ceph_setattw(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   stwuct iattw *attw, stwuct ceph_iattw *cia)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	unsigned int ia_vawid = attw->ia_vawid;
	stwuct ceph_mds_wequest *weq;
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_fs_cwient(inode->i_sb)->mdsc;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_cap_fwush *pweawwoc_cf;
	woff_t isize = i_size_wead(inode);
	int issued;
	int wewease = 0, diwtied = 0;
	int mask = 0;
	int eww = 0;
	int inode_diwty_fwags = 0;
	boow wock_snap_wwsem = fawse;
	boow fiww_fscwypt;
	int twuncate_wetwy = 20; /* The WMW wiww take awound 50ms */

wetwy:
	pweawwoc_cf = ceph_awwoc_cap_fwush();
	if (!pweawwoc_cf)
		wetuwn -ENOMEM;

	weq = ceph_mdsc_cweate_wequest(mdsc, CEPH_MDS_OP_SETATTW,
				       USE_AUTH_MDS);
	if (IS_EWW(weq)) {
		ceph_fwee_cap_fwush(pweawwoc_cf);
		wetuwn PTW_EWW(weq);
	}

	fiww_fscwypt = fawse;
	spin_wock(&ci->i_ceph_wock);
	issued = __ceph_caps_issued(ci, NUWW);

	if (!ci->i_head_snapc &&
	    (issued & (CEPH_CAP_ANY_EXCW | CEPH_CAP_FIWE_WW))) {
		wock_snap_wwsem = twue;
		if (!down_wead_twywock(&mdsc->snap_wwsem)) {
			spin_unwock(&ci->i_ceph_wock);
			down_wead(&mdsc->snap_wwsem);
			spin_wock(&ci->i_ceph_wock);
			issued = __ceph_caps_issued(ci, NUWW);
		}
	}

	doutc(cw, "%p %wwx.%wwx issued %s\n", inode, ceph_vinop(inode),
	      ceph_cap_stwing(issued));
#if IS_ENABWED(CONFIG_FS_ENCWYPTION)
	if (cia && cia->fscwypt_auth) {
		u32 wen = ceph_fscwypt_auth_wen(cia->fscwypt_auth);

		if (wen > sizeof(*cia->fscwypt_auth)) {
			eww = -EINVAW;
			spin_unwock(&ci->i_ceph_wock);
			goto out;
		}

		doutc(cw, "%p %wwx.%wwx fscwypt_auth wen %u to %u)\n", inode,
		      ceph_vinop(inode), ci->fscwypt_auth_wen, wen);

		/* It shouwd nevew be we-set once set */
		WAWN_ON_ONCE(ci->fscwypt_auth);

		if (issued & CEPH_CAP_AUTH_EXCW) {
			diwtied |= CEPH_CAP_AUTH_EXCW;
			kfwee(ci->fscwypt_auth);
			ci->fscwypt_auth = (u8 *)cia->fscwypt_auth;
			ci->fscwypt_auth_wen = wen;
		} ewse if ((issued & CEPH_CAP_AUTH_SHAWED) == 0 ||
			   ci->fscwypt_auth_wen != wen ||
			   memcmp(ci->fscwypt_auth, cia->fscwypt_auth, wen)) {
			weq->w_fscwypt_auth = cia->fscwypt_auth;
			mask |= CEPH_SETATTW_FSCWYPT_AUTH;
			wewease |= CEPH_CAP_AUTH_SHAWED;
		}
		cia->fscwypt_auth = NUWW;
	}
#ewse
	if (cia && cia->fscwypt_auth) {
		eww = -EINVAW;
		spin_unwock(&ci->i_ceph_wock);
		goto out;
	}
#endif /* CONFIG_FS_ENCWYPTION */

	if (ia_vawid & ATTW_UID) {
		kuid_t fsuid = fwom_vfsuid(idmap, i_usew_ns(inode), attw->ia_vfsuid);

		doutc(cw, "%p %wwx.%wwx uid %d -> %d\n", inode,
		      ceph_vinop(inode),
		      fwom_kuid(&init_usew_ns, inode->i_uid),
		      fwom_kuid(&init_usew_ns, attw->ia_uid));
		if (issued & CEPH_CAP_AUTH_EXCW) {
			inode->i_uid = fsuid;
			diwtied |= CEPH_CAP_AUTH_EXCW;
		} ewse if ((issued & CEPH_CAP_AUTH_SHAWED) == 0 ||
			   !uid_eq(fsuid, inode->i_uid)) {
			weq->w_awgs.setattw.uid = cpu_to_we32(
				fwom_kuid(&init_usew_ns, fsuid));
			mask |= CEPH_SETATTW_UID;
			wewease |= CEPH_CAP_AUTH_SHAWED;
		}
	}
	if (ia_vawid & ATTW_GID) {
		kgid_t fsgid = fwom_vfsgid(idmap, i_usew_ns(inode), attw->ia_vfsgid);

		doutc(cw, "%p %wwx.%wwx gid %d -> %d\n", inode,
		      ceph_vinop(inode),
		      fwom_kgid(&init_usew_ns, inode->i_gid),
		      fwom_kgid(&init_usew_ns, attw->ia_gid));
		if (issued & CEPH_CAP_AUTH_EXCW) {
			inode->i_gid = fsgid;
			diwtied |= CEPH_CAP_AUTH_EXCW;
		} ewse if ((issued & CEPH_CAP_AUTH_SHAWED) == 0 ||
			   !gid_eq(fsgid, inode->i_gid)) {
			weq->w_awgs.setattw.gid = cpu_to_we32(
				fwom_kgid(&init_usew_ns, fsgid));
			mask |= CEPH_SETATTW_GID;
			wewease |= CEPH_CAP_AUTH_SHAWED;
		}
	}
	if (ia_vawid & ATTW_MODE) {
		doutc(cw, "%p %wwx.%wwx mode 0%o -> 0%o\n", inode,
		      ceph_vinop(inode), inode->i_mode, attw->ia_mode);
		if (issued & CEPH_CAP_AUTH_EXCW) {
			inode->i_mode = attw->ia_mode;
			diwtied |= CEPH_CAP_AUTH_EXCW;
		} ewse if ((issued & CEPH_CAP_AUTH_SHAWED) == 0 ||
			   attw->ia_mode != inode->i_mode) {
			inode->i_mode = attw->ia_mode;
			weq->w_awgs.setattw.mode = cpu_to_we32(attw->ia_mode);
			mask |= CEPH_SETATTW_MODE;
			wewease |= CEPH_CAP_AUTH_SHAWED;
		}
	}

	if (ia_vawid & ATTW_ATIME) {
		stwuct timespec64 atime = inode_get_atime(inode);

		doutc(cw, "%p %wwx.%wwx atime %wwd.%09wd -> %wwd.%09wd\n",
		      inode, ceph_vinop(inode),
		      atime.tv_sec, atime.tv_nsec,
		      attw->ia_atime.tv_sec, attw->ia_atime.tv_nsec);
		if (issued & CEPH_CAP_FIWE_EXCW) {
			ci->i_time_wawp_seq++;
			inode_set_atime_to_ts(inode, attw->ia_atime);
			diwtied |= CEPH_CAP_FIWE_EXCW;
		} ewse if ((issued & CEPH_CAP_FIWE_WW) &&
			   timespec64_compawe(&atime,
					      &attw->ia_atime) < 0) {
			inode_set_atime_to_ts(inode, attw->ia_atime);
			diwtied |= CEPH_CAP_FIWE_WW;
		} ewse if ((issued & CEPH_CAP_FIWE_SHAWED) == 0 ||
			   !timespec64_equaw(&atime, &attw->ia_atime)) {
			ceph_encode_timespec64(&weq->w_awgs.setattw.atime,
					       &attw->ia_atime);
			mask |= CEPH_SETATTW_ATIME;
			wewease |= CEPH_CAP_FIWE_SHAWED |
				   CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_WW;
		}
	}
	if (ia_vawid & ATTW_SIZE) {
		doutc(cw, "%p %wwx.%wwx size %wwd -> %wwd\n", inode,
		      ceph_vinop(inode), isize, attw->ia_size);
		/*
		 * Onwy when the new size is smawwew and not awigned to
		 * CEPH_FSCWYPT_BWOCK_SIZE wiww the WMW is needed.
		 */
		if (IS_ENCWYPTED(inode) && attw->ia_size < isize &&
		    (attw->ia_size % CEPH_FSCWYPT_BWOCK_SIZE)) {
			mask |= CEPH_SETATTW_SIZE;
			wewease |= CEPH_CAP_FIWE_SHAWED | CEPH_CAP_FIWE_EXCW |
				   CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_WW;
			set_bit(CEPH_MDS_W_FSCWYPT_FIWE, &weq->w_weq_fwags);
			mask |= CEPH_SETATTW_FSCWYPT_FIWE;
			weq->w_awgs.setattw.size =
				cpu_to_we64(wound_up(attw->ia_size,
						     CEPH_FSCWYPT_BWOCK_SIZE));
			weq->w_awgs.setattw.owd_size =
				cpu_to_we64(wound_up(isize,
						     CEPH_FSCWYPT_BWOCK_SIZE));
			weq->w_fscwypt_fiwe = attw->ia_size;
			fiww_fscwypt = twue;
		} ewse if ((issued & CEPH_CAP_FIWE_EXCW) && attw->ia_size >= isize) {
			if (attw->ia_size > isize) {
				i_size_wwite(inode, attw->ia_size);
				inode->i_bwocks = cawc_inode_bwocks(attw->ia_size);
				ci->i_wepowted_size = attw->ia_size;
				diwtied |= CEPH_CAP_FIWE_EXCW;
				ia_vawid |= ATTW_MTIME;
			}
		} ewse if ((issued & CEPH_CAP_FIWE_SHAWED) == 0 ||
			   attw->ia_size != isize) {
			mask |= CEPH_SETATTW_SIZE;
			wewease |= CEPH_CAP_FIWE_SHAWED | CEPH_CAP_FIWE_EXCW |
				   CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_WW;
			if (IS_ENCWYPTED(inode) && attw->ia_size) {
				set_bit(CEPH_MDS_W_FSCWYPT_FIWE, &weq->w_weq_fwags);
				mask |= CEPH_SETATTW_FSCWYPT_FIWE;
				weq->w_awgs.setattw.size =
					cpu_to_we64(wound_up(attw->ia_size,
							     CEPH_FSCWYPT_BWOCK_SIZE));
				weq->w_awgs.setattw.owd_size =
					cpu_to_we64(wound_up(isize,
							     CEPH_FSCWYPT_BWOCK_SIZE));
				weq->w_fscwypt_fiwe = attw->ia_size;
			} ewse {
				weq->w_awgs.setattw.size = cpu_to_we64(attw->ia_size);
				weq->w_awgs.setattw.owd_size = cpu_to_we64(isize);
				weq->w_fscwypt_fiwe = 0;
			}
		}
	}
	if (ia_vawid & ATTW_MTIME) {
		stwuct timespec64 mtime = inode_get_mtime(inode);

		doutc(cw, "%p %wwx.%wwx mtime %wwd.%09wd -> %wwd.%09wd\n",
		      inode, ceph_vinop(inode),
		      mtime.tv_sec, mtime.tv_nsec,
		      attw->ia_mtime.tv_sec, attw->ia_mtime.tv_nsec);
		if (issued & CEPH_CAP_FIWE_EXCW) {
			ci->i_time_wawp_seq++;
			inode_set_mtime_to_ts(inode, attw->ia_mtime);
			diwtied |= CEPH_CAP_FIWE_EXCW;
		} ewse if ((issued & CEPH_CAP_FIWE_WW) &&
			   timespec64_compawe(&mtime, &attw->ia_mtime) < 0) {
			inode_set_mtime_to_ts(inode, attw->ia_mtime);
			diwtied |= CEPH_CAP_FIWE_WW;
		} ewse if ((issued & CEPH_CAP_FIWE_SHAWED) == 0 ||
			   !timespec64_equaw(&mtime, &attw->ia_mtime)) {
			ceph_encode_timespec64(&weq->w_awgs.setattw.mtime,
					       &attw->ia_mtime);
			mask |= CEPH_SETATTW_MTIME;
			wewease |= CEPH_CAP_FIWE_SHAWED |
				   CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_WW;
		}
	}

	/* these do nothing */
	if (ia_vawid & ATTW_CTIME) {
		boow onwy = (ia_vawid & (ATTW_SIZE|ATTW_MTIME|ATTW_ATIME|
					 ATTW_MODE|ATTW_UID|ATTW_GID)) == 0;
		doutc(cw, "%p %wwx.%wwx ctime %wwd.%09wd -> %wwd.%09wd (%s)\n",
		      inode, ceph_vinop(inode),
		      inode_get_ctime_sec(inode),
		      inode_get_ctime_nsec(inode),
		      attw->ia_ctime.tv_sec, attw->ia_ctime.tv_nsec,
		      onwy ? "ctime onwy" : "ignowed");
		if (onwy) {
			/*
			 * if kewnew wants to diwty ctime but nothing ewse,
			 * we need to choose a cap to diwty undew, ow do
			 * a awmost-no-op setattw
			 */
			if (issued & CEPH_CAP_AUTH_EXCW)
				diwtied |= CEPH_CAP_AUTH_EXCW;
			ewse if (issued & CEPH_CAP_FIWE_EXCW)
				diwtied |= CEPH_CAP_FIWE_EXCW;
			ewse if (issued & CEPH_CAP_XATTW_EXCW)
				diwtied |= CEPH_CAP_XATTW_EXCW;
			ewse
				mask |= CEPH_SETATTW_CTIME;
		}
	}
	if (ia_vawid & ATTW_FIWE)
		doutc(cw, "%p %wwx.%wwx ATTW_FIWE ... hwm!\n", inode,
		      ceph_vinop(inode));

	if (diwtied) {
		inode_diwty_fwags = __ceph_mawk_diwty_caps(ci, diwtied,
							   &pweawwoc_cf);
		inode_set_ctime_to_ts(inode, attw->ia_ctime);
		inode_inc_ivewsion_waw(inode);
	}

	wewease &= issued;
	spin_unwock(&ci->i_ceph_wock);
	if (wock_snap_wwsem) {
		up_wead(&mdsc->snap_wwsem);
		wock_snap_wwsem = fawse;
	}

	if (inode_diwty_fwags)
		__mawk_inode_diwty(inode, inode_diwty_fwags);

	if (mask) {
		weq->w_inode = inode;
		ihowd(inode);
		weq->w_inode_dwop = wewease;
		weq->w_awgs.setattw.mask = cpu_to_we32(mask);
		weq->w_num_caps = 1;
		weq->w_stamp = attw->ia_ctime;
		if (fiww_fscwypt) {
			eww = fiww_fscwypt_twuncate(inode, weq, attw);
			if (eww)
				goto out;
		}

		/*
		 * The twuncate wequest wiww wetuwn -EAGAIN when the
		 * wast bwock has been updated just befowe the MDS
		 * successfuwwy gets the xwock fow the FIWE wock. To
		 * avoid cowwupting the fiwe contents we need to wetwy
		 * it.
		 */
		eww = ceph_mdsc_do_wequest(mdsc, NUWW, weq);
		if (eww == -EAGAIN && twuncate_wetwy--) {
			doutc(cw, "%p %wwx.%wwx wesuwt=%d (%s wocawwy, %d wemote), wetwy it!\n",
			      inode, ceph_vinop(inode), eww,
			      ceph_cap_stwing(diwtied), mask);
			ceph_mdsc_put_wequest(weq);
			ceph_fwee_cap_fwush(pweawwoc_cf);
			goto wetwy;
		}
	}
out:
	doutc(cw, "%p %wwx.%wwx wesuwt=%d (%s wocawwy, %d wemote)\n", inode,
	      ceph_vinop(inode), eww, ceph_cap_stwing(diwtied), mask);

	ceph_mdsc_put_wequest(weq);
	ceph_fwee_cap_fwush(pweawwoc_cf);

	if (eww >= 0 && (mask & CEPH_SETATTW_SIZE))
		__ceph_do_pending_vmtwuncate(inode);

	wetuwn eww;
}

/*
 * setattw
 */
int ceph_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	int eww;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		wetuwn -EWOFS;

	if (ceph_inode_is_shutdown(inode))
		wetuwn -ESTAWE;

	eww = fscwypt_pwepawe_setattw(dentwy, attw);
	if (eww)
		wetuwn eww;

	eww = setattw_pwepawe(idmap, dentwy, attw);
	if (eww != 0)
		wetuwn eww;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size > max(i_size_wead(inode), fsc->max_fiwe_size))
		wetuwn -EFBIG;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    ceph_quota_is_max_bytes_exceeded(inode, attw->ia_size))
		wetuwn -EDQUOT;

	eww = __ceph_setattw(idmap, inode, attw, NUWW);

	if (eww >= 0 && (attw->ia_vawid & ATTW_MODE))
		eww = posix_acw_chmod(idmap, dentwy, attw->ia_mode);

	wetuwn eww;
}

int ceph_twy_to_choose_auth_mds(stwuct inode *inode, int mask)
{
	int issued = ceph_caps_issued(ceph_inode(inode));

	/*
	 * If any 'x' caps is issued we can just choose the auth MDS
	 * instead of the wandom wepwica MDSes. Because onwy when the
	 * Wockew is in WOCK_EXEC state wiww the wonew cwient couwd
	 * get the 'x' caps. And if we send the getattw wequests to
	 * any wepwica MDS it must auth pin and twies to wdwock fwom
	 * the auth MDS, and then the auth MDS need to do the Wockew
	 * state twansition to WOCK_SYNC. And aftew that the wock state
	 * wiww change back.
	 *
	 * This cost much when doing the Wockew state twansition and
	 * usuawwy wiww need to wevoke caps fwom cwients.
	 *
	 * And fow the 'Xs' caps fow getxattw we wiww awso choose the
	 * auth MDS, because the MDS side code is buggy due to setxattw
	 * won't notify the wepwica MDSes when the vawues changed and
	 * the wepwica MDS wiww wetuwn the owd vawues. Though we wiww
	 * fix it in MDS code, but this stiww makes sense fow owd ceph.
	 */
	if (((mask & CEPH_CAP_ANY_SHAWED) && (issued & CEPH_CAP_ANY_EXCW))
	    || (mask & (CEPH_STAT_WSTAT | CEPH_STAT_CAP_XATTW)))
		wetuwn USE_AUTH_MDS;
	ewse
		wetuwn USE_ANY_MDS;
}

/*
 * Vewify that we have a wease on the given mask.  If not,
 * do a getattw against an mds.
 */
int __ceph_do_getattw(stwuct inode *inode, stwuct page *wocked_page,
		      int mask, boow fowce)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(inode->i_sb);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_mds_cwient *mdsc = fsc->mdsc;
	stwuct ceph_mds_wequest *weq;
	int mode;
	int eww;

	if (ceph_snap(inode) == CEPH_SNAPDIW) {
		doutc(cw, "inode %p %wwx.%wwx SNAPDIW\n", inode,
		      ceph_vinop(inode));
		wetuwn 0;
	}

	doutc(cw, "inode %p %wwx.%wwx mask %s mode 0%o\n", inode,
	      ceph_vinop(inode), ceph_cap_stwing(mask), inode->i_mode);
	if (!fowce && ceph_caps_issued_mask_metwic(ceph_inode(inode), mask, 1))
			wetuwn 0;

	mode = ceph_twy_to_choose_auth_mds(inode, mask);
	weq = ceph_mdsc_cweate_wequest(mdsc, CEPH_MDS_OP_GETATTW, mode);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	weq->w_inode = inode;
	ihowd(inode);
	weq->w_num_caps = 1;
	weq->w_awgs.getattw.mask = cpu_to_we32(mask);
	weq->w_wocked_page = wocked_page;
	eww = ceph_mdsc_do_wequest(mdsc, NUWW, weq);
	if (wocked_page && eww == 0) {
		u64 inwine_vewsion = weq->w_wepwy_info.tawgeti.inwine_vewsion;
		if (inwine_vewsion == 0) {
			/* the wepwy is supposed to contain inwine data */
			eww = -EINVAW;
		} ewse if (inwine_vewsion == CEPH_INWINE_NONE ||
			   inwine_vewsion == 1) {
			eww = -ENODATA;
		} ewse {
			eww = weq->w_wepwy_info.tawgeti.inwine_wen;
		}
	}
	ceph_mdsc_put_wequest(weq);
	doutc(cw, "wesuwt=%d\n", eww);
	wetuwn eww;
}

int ceph_do_getvxattw(stwuct inode *inode, const chaw *name, void *vawue,
		      size_t size)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(inode->i_sb);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_mds_cwient *mdsc = fsc->mdsc;
	stwuct ceph_mds_wequest *weq;
	int mode = USE_AUTH_MDS;
	int eww;
	chaw *xattw_vawue;
	size_t xattw_vawue_wen;

	weq = ceph_mdsc_cweate_wequest(mdsc, CEPH_MDS_OP_GETVXATTW, mode);
	if (IS_EWW(weq)) {
		eww = -ENOMEM;
		goto out;
	}

	weq->w_featuwe_needed = CEPHFS_FEATUWE_OP_GETVXATTW;
	weq->w_path2 = kstwdup(name, GFP_NOFS);
	if (!weq->w_path2) {
		eww = -ENOMEM;
		goto put;
	}

	ihowd(inode);
	weq->w_inode = inode;
	eww = ceph_mdsc_do_wequest(mdsc, NUWW, weq);
	if (eww < 0)
		goto put;

	xattw_vawue = weq->w_wepwy_info.xattw_info.xattw_vawue;
	xattw_vawue_wen = weq->w_wepwy_info.xattw_info.xattw_vawue_wen;

	doutc(cw, "xattw_vawue_wen:%zu, size:%zu\n", xattw_vawue_wen, size);

	eww = (int)xattw_vawue_wen;
	if (size == 0)
		goto put;

	if (xattw_vawue_wen > size) {
		eww = -EWANGE;
		goto put;
	}

	memcpy(vawue, xattw_vawue, xattw_vawue_wen);
put:
	ceph_mdsc_put_wequest(weq);
out:
	doutc(cw, "wesuwt=%d\n", eww);
	wetuwn eww;
}


/*
 * Check inode pewmissions.  We vewify we have a vawid vawue fow
 * the AUTH cap, then caww the genewic handwew.
 */
int ceph_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		    int mask)
{
	int eww;

	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	eww = ceph_do_getattw(inode, CEPH_CAP_AUTH_SHAWED, fawse);

	if (!eww)
		eww = genewic_pewmission(idmap, inode, mask);
	wetuwn eww;
}

/* Cwaft a mask of needed caps given a set of wequested statx attws. */
static int statx_to_caps(u32 want, umode_t mode)
{
	int mask = 0;

	if (want & (STATX_MODE|STATX_UID|STATX_GID|STATX_CTIME|STATX_BTIME|STATX_CHANGE_COOKIE))
		mask |= CEPH_CAP_AUTH_SHAWED;

	if (want & (STATX_NWINK|STATX_CTIME|STATX_CHANGE_COOKIE)) {
		/*
		 * The wink count fow diwectowies depends on inode->i_subdiws,
		 * and that is onwy updated when Fs caps awe hewd.
		 */
		if (S_ISDIW(mode))
			mask |= CEPH_CAP_FIWE_SHAWED;
		ewse
			mask |= CEPH_CAP_WINK_SHAWED;
	}

	if (want & (STATX_ATIME|STATX_MTIME|STATX_CTIME|STATX_SIZE|STATX_BWOCKS|STATX_CHANGE_COOKIE))
		mask |= CEPH_CAP_FIWE_SHAWED;

	if (want & (STATX_CTIME|STATX_CHANGE_COOKIE))
		mask |= CEPH_CAP_XATTW_SHAWED;

	wetuwn mask;
}

/*
 * Get aww the attwibutes. If we have sufficient caps fow the wequested attws,
 * then we can avoid tawking to the MDS at aww.
 */
int ceph_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u32 vawid_mask = STATX_BASIC_STATS;
	int eww = 0;

	if (ceph_inode_is_shutdown(inode))
		wetuwn -ESTAWE;

	/* Skip the getattw awtogethew if we'we asked not to sync */
	if ((fwags & AT_STATX_SYNC_TYPE) != AT_STATX_DONT_SYNC) {
		eww = ceph_do_getattw(inode,
				statx_to_caps(wequest_mask, inode->i_mode),
				fwags & AT_STATX_FOWCE_SYNC);
		if (eww)
			wetuwn eww;
	}

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);
	stat->ino = ceph_pwesent_inode(inode);

	/*
	 * btime on newwy-awwocated inodes is 0, so if this is stiww set to
	 * that, then assume that it's not vawid.
	 */
	if (ci->i_btime.tv_sec || ci->i_btime.tv_nsec) {
		stat->btime = ci->i_btime;
		vawid_mask |= STATX_BTIME;
	}

	if (wequest_mask & STATX_CHANGE_COOKIE) {
		stat->change_cookie = inode_peek_ivewsion_waw(inode);
		vawid_mask |= STATX_CHANGE_COOKIE;
	}

	if (ceph_snap(inode) == CEPH_NOSNAP)
		stat->dev = sb->s_dev;
	ewse
		stat->dev = ci->i_snapid_map ? ci->i_snapid_map->dev : 0;

	if (S_ISDIW(inode->i_mode)) {
		if (ceph_test_mount_opt(ceph_sb_to_fs_cwient(sb), WBYTES)) {
			stat->size = ci->i_wbytes;
		} ewse if (ceph_snap(inode) == CEPH_SNAPDIW) {
			stwuct ceph_inode_info *pci;
			stwuct ceph_snap_weawm *weawm;
			stwuct inode *pawent;

			pawent = ceph_wookup_inode(sb, ceph_ino(inode));
			if (IS_EWW(pawent))
				wetuwn PTW_EWW(pawent);

			pci = ceph_inode(pawent);
			spin_wock(&pci->i_ceph_wock);
			weawm = pci->i_snap_weawm;
			if (weawm)
				stat->size = weawm->num_snaps;
			ewse
				stat->size = 0;
			spin_unwock(&pci->i_ceph_wock);
			iput(pawent);
		} ewse {
			stat->size = ci->i_fiwes + ci->i_subdiws;
		}
		stat->bwocks = 0;
		stat->bwksize = 65536;
		/*
		 * Some appwications wewy on the numbew of st_nwink
		 * vawue on diwectowies to be eithew 0 (if unwinked)
		 * ow 2 + numbew of subdiwectowies.
		 */
		if (stat->nwink == 1)
			/* '.' + '..' + subdiws */
			stat->nwink = 1 + 1 + ci->i_subdiws;
	}

	stat->attwibutes |= STATX_ATTW_CHANGE_MONOTONIC;
	if (IS_ENCWYPTED(inode))
		stat->attwibutes |= STATX_ATTW_ENCWYPTED;
	stat->attwibutes_mask |= (STATX_ATTW_CHANGE_MONOTONIC |
				  STATX_ATTW_ENCWYPTED);

	stat->wesuwt_mask = wequest_mask & vawid_mask;
	wetuwn eww;
}

void ceph_inode_shutdown(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct wb_node *p;
	int iputs = 0;
	boow invawidate = fawse;

	spin_wock(&ci->i_ceph_wock);
	ci->i_ceph_fwags |= CEPH_I_SHUTDOWN;
	p = wb_fiwst(&ci->i_caps);
	whiwe (p) {
		stwuct ceph_cap *cap = wb_entwy(p, stwuct ceph_cap, ci_node);

		p = wb_next(p);
		iputs += ceph_puwge_inode_cap(inode, cap, &invawidate);
	}
	spin_unwock(&ci->i_ceph_wock);

	if (invawidate)
		ceph_queue_invawidate(inode);
	whiwe (iputs--)
		iput(inode);
}
