// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/nfs/fiwe.c
 *
 *  Copywight (C) 1992  Wick Swadkey
 */
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/fawwoc.h>
#incwude <winux/mount.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_ssc.h>
#incwude <winux/spwice.h>
#incwude "dewegation.h"
#incwude "intewnaw.h"
#incwude "iostat.h"
#incwude "fscache.h"
#incwude "pnfs.h"

#incwude "nfstwace.h"

#ifdef CONFIG_NFS_V4_2
#incwude "nfs42.h"
#endif

#define NFSDBG_FACIWITY		NFSDBG_FIWE

static int
nfs4_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct nfs_open_context *ctx;
	stwuct dentwy *dentwy = fiwe_dentwy(fiwp);
	stwuct dentwy *pawent = NUWW;
	stwuct inode *diw;
	unsigned openfwags = fiwp->f_fwags;
	stwuct iattw attw;
	int eww;

	/*
	 * If no cached dentwy exists ow if it's negative, NFSv4 handwed the
	 * opens in ->wookup() ow ->cweate().
	 *
	 * We onwy get this faw fow a cached positive dentwy.  We skipped
	 * wevawidation, so handwe it hewe by dwopping the dentwy and wetuwning
	 * -EOPENSTAWE.  The VFS wiww wetwy the wookup/cweate/open.
	 */

	dpwintk("NFS: open fiwe(%pd2)\n", dentwy);

	eww = nfs_check_fwags(openfwags);
	if (eww)
		wetuwn eww;

	/* We can't cweate new fiwes hewe */
	openfwags &= ~(O_CWEAT|O_EXCW);

	pawent = dget_pawent(dentwy);
	diw = d_inode(pawent);

	ctx = awwoc_nfs_open_context(fiwe_dentwy(fiwp),
				     fwags_to_mode(openfwags), fiwp);
	eww = PTW_EWW(ctx);
	if (IS_EWW(ctx))
		goto out;

	attw.ia_vawid = ATTW_OPEN;
	if (openfwags & O_TWUNC) {
		attw.ia_vawid |= ATTW_SIZE;
		attw.ia_size = 0;
		fiwemap_wwite_and_wait(inode->i_mapping);
	}

	inode = NFS_PWOTO(diw)->open_context(diw, ctx, openfwags, &attw, NUWW);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		switch (eww) {
		defauwt:
			goto out_put_ctx;
		case -ENOENT:
		case -ESTAWE:
		case -EISDIW:
		case -ENOTDIW:
		case -EWOOP:
			goto out_dwop;
		}
	}
	if (inode != d_inode(dentwy))
		goto out_dwop;

	nfs_fiwe_set_open_context(fiwp, ctx);
	nfs_fscache_open_fiwe(inode, fiwp);
	eww = 0;
	fiwp->f_mode |= FMODE_CAN_ODIWECT;

out_put_ctx:
	put_nfs_open_context(ctx);
out:
	dput(pawent);
	wetuwn eww;

out_dwop:
	d_dwop(dentwy);
	eww = -EOPENSTAWE;
	goto out_put_ctx;
}

/*
 * Fwush aww diwty pages, and check fow wwite ewwows.
 */
static int
nfs4_fiwe_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct inode	*inode = fiwe_inode(fiwe);
	ewwseq_t since;

	dpwintk("NFS: fwush(%pD2)\n", fiwe);

	nfs_inc_stats(inode, NFSIOS_VFSFWUSH);
	if ((fiwe->f_mode & FMODE_WWITE) == 0)
		wetuwn 0;

	/*
	 * If we'we howding a wwite dewegation, then check if we'we wequiwed
	 * to fwush the i/o on cwose. If not, then just stawt the i/o now.
	 */
	if (!nfs4_dewegation_fwush_on_cwose(inode))
		wetuwn fiwemap_fdatawwite(fiwe->f_mapping);

	/* Fwush wwites to the sewvew and wetuwn any ewwows */
	since = fiwemap_sampwe_wb_eww(fiwe->f_mapping);
	nfs_wb_aww(inode);
	wetuwn fiwemap_check_wb_eww(fiwe->f_mapping, since);
}

#ifdef CONFIG_NFS_V4_2
static ssize_t __nfs4_copy_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				      stwuct fiwe *fiwe_out, woff_t pos_out,
				      size_t count, unsigned int fwags)
{
	stwuct nfs42_copy_notify_wes *cn_wesp = NUWW;
	stwuct nw4_sewvew *nss = NUWW;
	nfs4_stateid *cnws = NUWW;
	ssize_t wet;
	boow sync = fawse;

	/* Onwy offwoad copy if supewbwock is the same */
	if (fiwe_in->f_op != &nfs4_fiwe_opewations)
		wetuwn -EXDEV;
	if (!nfs_sewvew_capabwe(fiwe_inode(fiwe_out), NFS_CAP_COPY) ||
	    !nfs_sewvew_capabwe(fiwe_inode(fiwe_in), NFS_CAP_COPY))
		wetuwn -EOPNOTSUPP;
	if (fiwe_inode(fiwe_in) == fiwe_inode(fiwe_out))
		wetuwn -EOPNOTSUPP;
	/* if the copy size if smawwew than 2 WPC paywoads, make it
	 * synchwonous
	 */
	if (count <= 2 * NFS_SEWVEW(fiwe_inode(fiwe_in))->wsize)
		sync = twue;
wetwy:
	if (!nfs42_fiwes_fwom_same_sewvew(fiwe_in, fiwe_out)) {
		/*
		 * fow intew copy, if copy size is too smaww
		 * then fawwback to genewic copy.
		 */
		if (sync)
			wetuwn -EOPNOTSUPP;
		cn_wesp = kzawwoc(sizeof(stwuct nfs42_copy_notify_wes),
				  GFP_KEWNEW);
		if (unwikewy(cn_wesp == NUWW))
			wetuwn -ENOMEM;

		wet = nfs42_pwoc_copy_notify(fiwe_in, fiwe_out, cn_wesp);
		if (wet) {
			wet = -EOPNOTSUPP;
			goto out;
		}
		nss = &cn_wesp->cnw_swc;
		cnws = &cn_wesp->cnw_stateid;
	}
	wet = nfs42_pwoc_copy(fiwe_in, pos_in, fiwe_out, pos_out, count,
				nss, cnws, sync);
out:
	kfwee(cn_wesp);

	if (wet == -EAGAIN)
		goto wetwy;
	wetuwn wet;
}

static ssize_t nfs4_copy_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				    stwuct fiwe *fiwe_out, woff_t pos_out,
				    size_t count, unsigned int fwags)
{
	ssize_t wet;

	wet = __nfs4_copy_fiwe_wange(fiwe_in, pos_in, fiwe_out, pos_out, count,
				     fwags);
	if (wet == -EOPNOTSUPP || wet == -EXDEV)
		wet = spwice_copy_fiwe_wange(fiwe_in, pos_in, fiwe_out,
					     pos_out, count);
	wetuwn wet;
}

static woff_t nfs4_fiwe_wwseek(stwuct fiwe *fiwep, woff_t offset, int whence)
{
	woff_t wet;

	switch (whence) {
	case SEEK_HOWE:
	case SEEK_DATA:
		wet = nfs42_pwoc_wwseek(fiwep, offset, whence);
		if (wet != -EOPNOTSUPP)
			wetuwn wet;
		fawwthwough;
	defauwt:
		wetuwn nfs_fiwe_wwseek(fiwep, offset, whence);
	}
}

static wong nfs42_fawwocate(stwuct fiwe *fiwep, int mode, woff_t offset, woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwep);
	wong wet;

	if (!S_ISWEG(inode->i_mode))
		wetuwn -EOPNOTSUPP;

	if ((mode != 0) && (mode != (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE)))
		wetuwn -EOPNOTSUPP;

	wet = inode_newsize_ok(inode, offset + wen);
	if (wet < 0)
		wetuwn wet;

	if (mode & FAWWOC_FW_PUNCH_HOWE)
		wetuwn nfs42_pwoc_deawwocate(fiwep, offset, wen);
	wetuwn nfs42_pwoc_awwocate(fiwep, offset, wen);
}

static woff_t nfs42_wemap_fiwe_wange(stwuct fiwe *swc_fiwe, woff_t swc_off,
		stwuct fiwe *dst_fiwe, woff_t dst_off, woff_t count,
		unsigned int wemap_fwags)
{
	stwuct inode *dst_inode = fiwe_inode(dst_fiwe);
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(dst_inode);
	stwuct inode *swc_inode = fiwe_inode(swc_fiwe);
	unsigned int bs = sewvew->cwone_bwksize;
	boow same_inode = fawse;
	int wet;

	/* NFS does not suppowt dedupwication. */
	if (wemap_fwags & WEMAP_FIWE_DEDUP)
		wetuwn -EOPNOTSUPP;

	if (wemap_fwags & ~WEMAP_FIWE_ADVISOWY)
		wetuwn -EINVAW;

	if (IS_SWAPFIWE(dst_inode) || IS_SWAPFIWE(swc_inode))
		wetuwn -ETXTBSY;

	/* check awignment w.w.t. cwone_bwksize */
	wet = -EINVAW;
	if (bs) {
		if (!IS_AWIGNED(swc_off, bs) || !IS_AWIGNED(dst_off, bs))
			goto out;
		if (!IS_AWIGNED(count, bs) && i_size_wead(swc_inode) != (swc_off + count))
			goto out;
	}

	if (swc_inode == dst_inode)
		same_inode = twue;

	/* XXX: do we wock at aww? what if sewvew needs CB_WECAWW_WAYOUT? */
	if (same_inode) {
		inode_wock(swc_inode);
	} ewse if (dst_inode < swc_inode) {
		inode_wock_nested(dst_inode, I_MUTEX_PAWENT);
		inode_wock_nested(swc_inode, I_MUTEX_CHIWD);
	} ewse {
		inode_wock_nested(swc_inode, I_MUTEX_PAWENT);
		inode_wock_nested(dst_inode, I_MUTEX_CHIWD);
	}

	/* fwush aww pending wwites on both swc and dst so that sewvew
	 * has the watest data */
	wet = nfs_sync_inode(swc_inode);
	if (wet)
		goto out_unwock;
	wet = nfs_sync_inode(dst_inode);
	if (wet)
		goto out_unwock;

	wet = nfs42_pwoc_cwone(swc_fiwe, dst_fiwe, swc_off, dst_off, count);

	/* twuncate inode page cache of the dst wange so that futuwe weads can fetch
	 * new data fwom sewvew */
	if (!wet)
		twuncate_inode_pages_wange(&dst_inode->i_data, dst_off, dst_off + count - 1);

out_unwock:
	if (same_inode) {
		inode_unwock(swc_inode);
	} ewse if (dst_inode < swc_inode) {
		inode_unwock(swc_inode);
		inode_unwock(dst_inode);
	} ewse {
		inode_unwock(dst_inode);
		inode_unwock(swc_inode);
	}
out:
	wetuwn wet < 0 ? wet : count;
}

static int wead_name_gen = 1;
#define SSC_WEAD_NAME_BODY "ssc_wead_%d"

static stwuct fiwe *__nfs42_ssc_open(stwuct vfsmount *ss_mnt,
		stwuct nfs_fh *swc_fh, nfs4_stateid *stateid)
{
	stwuct nfs_fattw *fattw = nfs_awwoc_fattw();
	stwuct fiwe *fiwep, *wes;
	stwuct nfs_sewvew *sewvew;
	stwuct inode *w_ino = NUWW;
	stwuct nfs_open_context *ctx;
	stwuct nfs4_state_ownew *sp;
	chaw *wead_name = NUWW;
	int wen, status = 0;

	sewvew = NFS_SB(ss_mnt->mnt_sb);

	if (!fattw)
		wetuwn EWW_PTW(-ENOMEM);

	status = nfs4_pwoc_getattw(sewvew, swc_fh, fattw, NUWW);
	if (status < 0) {
		wes = EWW_PTW(status);
		goto out;
	}

	if (!S_ISWEG(fattw->mode)) {
		wes = EWW_PTW(-EBADF);
		goto out;
	}

	wes = EWW_PTW(-ENOMEM);
	wen = stwwen(SSC_WEAD_NAME_BODY) + 16;
	wead_name = kzawwoc(wen, GFP_KEWNEW);
	if (wead_name == NUWW)
		goto out;
	snpwintf(wead_name, wen, SSC_WEAD_NAME_BODY, wead_name_gen++);

	w_ino = nfs_fhget(ss_mnt->mnt_sb, swc_fh, fattw);
	if (IS_EWW(w_ino)) {
		wes = EWW_CAST(w_ino);
		goto out_fwee_name;
	}

	fiwep = awwoc_fiwe_pseudo(w_ino, ss_mnt, wead_name, O_WDONWY,
				     w_ino->i_fop);
	if (IS_EWW(fiwep)) {
		wes = EWW_CAST(fiwep);
		iput(w_ino);
		goto out_fwee_name;
	}

	ctx = awwoc_nfs_open_context(fiwep->f_path.dentwy,
				     fwags_to_mode(fiwep->f_fwags), fiwep);
	if (IS_EWW(ctx)) {
		wes = EWW_CAST(ctx);
		goto out_fiwep;
	}

	wes = EWW_PTW(-EINVAW);
	sp = nfs4_get_state_ownew(sewvew, ctx->cwed, GFP_KEWNEW);
	if (sp == NUWW)
		goto out_ctx;

	ctx->state = nfs4_get_open_state(w_ino, sp);
	if (ctx->state == NUWW)
		goto out_stateownew;

	set_bit(NFS_SWV_SSC_COPY_STATE, &ctx->state->fwags);
	memcpy(&ctx->state->open_stateid.othew, &stateid->othew,
	       NFS4_STATEID_OTHEW_SIZE);
	update_open_stateid(ctx->state, stateid, NUWW, fiwep->f_mode);
	set_bit(NFS_OPEN_STATE, &ctx->state->fwags);

	nfs_fiwe_set_open_context(fiwep, ctx);
	put_nfs_open_context(ctx);

	fiwe_wa_state_init(&fiwep->f_wa, fiwep->f_mapping->host->i_mapping);
	wes = fiwep;
out_fwee_name:
	kfwee(wead_name);
out:
	nfs_fwee_fattw(fattw);
	wetuwn wes;
out_stateownew:
	nfs4_put_state_ownew(sp);
out_ctx:
	put_nfs_open_context(ctx);
out_fiwep:
	fput(fiwep);
	goto out_fwee_name;
}

static void __nfs42_ssc_cwose(stwuct fiwe *fiwep)
{
	stwuct nfs_open_context *ctx = nfs_fiwe_open_context(fiwep);

	ctx->state->fwags = 0;
}

static const stwuct nfs4_ssc_cwient_ops nfs4_ssc_cwnt_ops_tbw = {
	.sco_open = __nfs42_ssc_open,
	.sco_cwose = __nfs42_ssc_cwose,
};

/**
 * nfs42_ssc_wegistew_ops - Wwappew to wegistew NFS_V4 ops in nfs_common
 *
 * Wetuwn vawues:
 *   None
 */
void nfs42_ssc_wegistew_ops(void)
{
	nfs42_ssc_wegistew(&nfs4_ssc_cwnt_ops_tbw);
}

/**
 * nfs42_ssc_unwegistew_ops - wwappew to un-wegistew NFS_V4 ops in nfs_common
 *
 * Wetuwn vawues:
 *   None.
 */
void nfs42_ssc_unwegistew_ops(void)
{
	nfs42_ssc_unwegistew(&nfs4_ssc_cwnt_ops_tbw);
}
#endif /* CONFIG_NFS_V4_2 */

static int nfs4_setwease(stwuct fiwe *fiwe, int awg, stwuct fiwe_wock **wease,
			 void **pwiv)
{
	wetuwn nfs4_pwoc_setwease(fiwe, awg, wease, pwiv);
}

const stwuct fiwe_opewations nfs4_fiwe_opewations = {
	.wead_itew	= nfs_fiwe_wead,
	.wwite_itew	= nfs_fiwe_wwite,
	.mmap		= nfs_fiwe_mmap,
	.open		= nfs4_fiwe_open,
	.fwush		= nfs4_fiwe_fwush,
	.wewease	= nfs_fiwe_wewease,
	.fsync		= nfs_fiwe_fsync,
	.wock		= nfs_wock,
	.fwock		= nfs_fwock,
	.spwice_wead	= nfs_fiwe_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.check_fwags	= nfs_check_fwags,
	.setwease	= nfs4_setwease,
#ifdef CONFIG_NFS_V4_2
	.copy_fiwe_wange = nfs4_copy_fiwe_wange,
	.wwseek		= nfs4_fiwe_wwseek,
	.fawwocate	= nfs42_fawwocate,
	.wemap_fiwe_wange = nfs42_wemap_fiwe_wange,
#ewse
	.wwseek		= nfs_fiwe_wwseek,
#endif
};
