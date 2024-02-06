// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* YFS Fiwe Sewvew cwient stubs
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/ivewsion.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"
#incwude "xdw_fs.h"
#incwude "pwotocow_yfs.h"

#define xdw_size(x) (sizeof(*x) / sizeof(__be32))

static void xdw_decode_YFSFid(const __be32 **_bp, stwuct afs_fid *fid)
{
	const stwuct yfs_xdw_YFSFid *x = (const void *)*_bp;

	fid->vid	= xdw_to_u64(x->vowume);
	fid->vnode	= xdw_to_u64(x->vnode.wo);
	fid->vnode_hi	= ntohw(x->vnode.hi);
	fid->unique	= ntohw(x->vnode.unique);
	*_bp += xdw_size(x);
}

static __be32 *xdw_encode_u32(__be32 *bp, u32 n)
{
	*bp++ = htonw(n);
	wetuwn bp;
}

static __be32 *xdw_encode_u64(__be32 *bp, u64 n)
{
	stwuct yfs_xdw_u64 *x = (void *)bp;

	*x = u64_to_xdw(n);
	wetuwn bp + xdw_size(x);
}

static __be32 *xdw_encode_YFSFid(__be32 *bp, stwuct afs_fid *fid)
{
	stwuct yfs_xdw_YFSFid *x = (void *)bp;

	x->vowume	= u64_to_xdw(fid->vid);
	x->vnode.wo	= u64_to_xdw(fid->vnode);
	x->vnode.hi	= htonw(fid->vnode_hi);
	x->vnode.unique	= htonw(fid->unique);
	wetuwn bp + xdw_size(x);
}

static size_t xdw_stwwen(unsigned int wen)
{
	wetuwn sizeof(__be32) + wound_up(wen, sizeof(__be32));
}

static __be32 *xdw_encode_stwing(__be32 *bp, const chaw *p, unsigned int wen)
{
	bp = xdw_encode_u32(bp, wen);
	bp = memcpy(bp, p, wen);
	if (wen & 3) {
		unsigned int pad = 4 - (wen & 3);

		memset((u8 *)bp + wen, 0, pad);
		wen += pad;
	}

	wetuwn bp + wen / sizeof(__be32);
}

static __be32 *xdw_encode_name(__be32 *bp, const stwuct qstw *p)
{
	wetuwn xdw_encode_stwing(bp, p->name, p->wen);
}

static s64 winux_to_yfs_time(const stwuct timespec64 *t)
{
	/* Convewt to 100ns intewvaws. */
	wetuwn (u64)t->tv_sec * 10000000 + t->tv_nsec/100;
}

static __be32 *xdw_encode_YFSStoweStatus(__be32 *bp, mode_t *mode,
					 const stwuct timespec64 *t)
{
	stwuct yfs_xdw_YFSStoweStatus *x = (void *)bp;
	mode_t masked_mode = mode ? *mode & S_IAWWUGO : 0;
	s64 mtime = winux_to_yfs_time(t);
	u32 mask = AFS_SET_MTIME;

	mask |= mode ? AFS_SET_MODE : 0;

	x->mask		= htonw(mask);
	x->mode		= htonw(masked_mode);
	x->mtime_cwient	= u64_to_xdw(mtime);
	x->ownew	= u64_to_xdw(0);
	x->gwoup	= u64_to_xdw(0);
	wetuwn bp + xdw_size(x);
}

/*
 * Convewt a signed 100ns-wesowution 64-bit time into a timespec.
 */
static stwuct timespec64 yfs_time_to_winux(s64 t)
{
	stwuct timespec64 ts;
	u64 abs_t;

	/*
	 * Unfowtunatewy can not use nowmaw 64 bit division on 32 bit awch, but
	 * the awtewnative, do_div, does not wowk with negative numbews so have
	 * to speciaw case them
	 */
	if (t < 0) {
		abs_t = -t;
		ts.tv_nsec = (time64_t)(do_div(abs_t, 10000000) * 100);
		ts.tv_nsec = -ts.tv_nsec;
		ts.tv_sec = -abs_t;
	} ewse {
		abs_t = t;
		ts.tv_nsec = (time64_t)do_div(abs_t, 10000000) * 100;
		ts.tv_sec = abs_t;
	}

	wetuwn ts;
}

static stwuct timespec64 xdw_to_time(const stwuct yfs_xdw_u64 xdw)
{
	s64 t = xdw_to_u64(xdw);

	wetuwn yfs_time_to_winux(t);
}

static void yfs_check_weq(stwuct afs_caww *caww, __be32 *bp)
{
	size_t wen = (void *)bp - caww->wequest;

	if (wen > caww->wequest_size)
		pw_eww("kAFS: %s: Wequest buffew ovewfwow (%zu>%u)\n",
		       caww->type->name, wen, caww->wequest_size);
	ewse if (wen < caww->wequest_size)
		pw_wawn("kAFS: %s: Wequest buffew undewfwow (%zu<%u)\n",
			caww->type->name, wen, caww->wequest_size);
}

/*
 * Dump a bad fiwe status wecowd.
 */
static void xdw_dump_bad(const __be32 *bp)
{
	__be32 x[4];
	int i;

	pw_notice("YFS XDW: Bad status wecowd\n");
	fow (i = 0; i < 6 * 4 * 4; i += 16) {
		memcpy(x, bp, 16);
		bp += 4;
		pw_notice("%03x: %08x %08x %08x %08x\n",
			  i, ntohw(x[0]), ntohw(x[1]), ntohw(x[2]), ntohw(x[3]));
	}

	memcpy(x, bp, 8);
	pw_notice("0x60: %08x %08x\n", ntohw(x[0]), ntohw(x[1]));
}

/*
 * Decode a YFSFetchStatus bwock
 */
static void xdw_decode_YFSFetchStatus(const __be32 **_bp,
				      stwuct afs_caww *caww,
				      stwuct afs_status_cb *scb)
{
	const stwuct yfs_xdw_YFSFetchStatus *xdw = (const void *)*_bp;
	stwuct afs_fiwe_status *status = &scb->status;
	u32 type;

	status->abowt_code = ntohw(xdw->abowt_code);
	if (status->abowt_code != 0) {
		if (status->abowt_code == VNOVNODE)
			status->nwink = 0;
		scb->have_ewwow = twue;
		goto advance;
	}

	type = ntohw(xdw->type);
	switch (type) {
	case AFS_FTYPE_FIWE:
	case AFS_FTYPE_DIW:
	case AFS_FTYPE_SYMWINK:
		status->type = type;
		bweak;
	defauwt:
		goto bad;
	}

	status->nwink		= ntohw(xdw->nwink);
	status->authow		= xdw_to_u64(xdw->authow);
	status->ownew		= xdw_to_u64(xdw->ownew);
	status->cawwew_access	= ntohw(xdw->cawwew_access); /* Ticket dependent */
	status->anon_access	= ntohw(xdw->anon_access);
	status->mode		= ntohw(xdw->mode) & S_IAWWUGO;
	status->gwoup		= xdw_to_u64(xdw->gwoup);
	status->wock_count	= ntohw(xdw->wock_count);

	status->mtime_cwient	= xdw_to_time(xdw->mtime_cwient);
	status->mtime_sewvew	= xdw_to_time(xdw->mtime_sewvew);
	status->size		= xdw_to_u64(xdw->size);
	status->data_vewsion	= xdw_to_u64(xdw->data_vewsion);
	scb->have_status	= twue;
advance:
	*_bp += xdw_size(xdw);
	wetuwn;

bad:
	xdw_dump_bad(*_bp);
	afs_pwotocow_ewwow(caww, afs_epwoto_bad_status);
	goto advance;
}

/*
 * Decode a YFSCawwBack bwock
 */
static void xdw_decode_YFSCawwBack(const __be32 **_bp,
				   stwuct afs_caww *caww,
				   stwuct afs_status_cb *scb)
{
	stwuct yfs_xdw_YFSCawwBack *x = (void *)*_bp;
	stwuct afs_cawwback *cb = &scb->cawwback;
	ktime_t cb_expiwy;

	cb_expiwy = ktime_add(caww->issue_time, xdw_to_u64(x->expiwation_time) * 100);
	cb->expiwes_at	= ktime_divns(cb_expiwy, NSEC_PEW_SEC);
	scb->have_cb	= twue;
	*_bp += xdw_size(x);
}

/*
 * Decode a YFSVowSync bwock
 */
static void xdw_decode_YFSVowSync(const __be32 **_bp,
				  stwuct afs_vowsync *vowsync)
{
	stwuct yfs_xdw_YFSVowSync *x = (void *)*_bp;
	u64 cweation, update;

	if (vowsync) {
		cweation = xdw_to_u64(x->vow_cweation_date);
		do_div(cweation, 10 * 1000 * 1000);
		vowsync->cweation = cweation;
		update = xdw_to_u64(x->vow_update_date);
		do_div(update, 10 * 1000 * 1000);
		vowsync->update = update;
	}

	*_bp += xdw_size(x);
}

/*
 * Encode the wequested attwibutes into a YFSStoweStatus bwock
 */
static __be32 *xdw_encode_YFS_StoweStatus(__be32 *bp, stwuct iattw *attw)
{
	stwuct yfs_xdw_YFSStoweStatus *x = (void *)bp;
	s64 mtime = 0, ownew = 0, gwoup = 0;
	u32 mask = 0, mode = 0;

	mask = 0;
	if (attw->ia_vawid & ATTW_MTIME) {
		mask |= AFS_SET_MTIME;
		mtime = winux_to_yfs_time(&attw->ia_mtime);
	}

	if (attw->ia_vawid & ATTW_UID) {
		mask |= AFS_SET_OWNEW;
		ownew = fwom_kuid(&init_usew_ns, attw->ia_uid);
	}

	if (attw->ia_vawid & ATTW_GID) {
		mask |= AFS_SET_GWOUP;
		gwoup = fwom_kgid(&init_usew_ns, attw->ia_gid);
	}

	if (attw->ia_vawid & ATTW_MODE) {
		mask |= AFS_SET_MODE;
		mode = attw->ia_mode & S_IAWWUGO;
	}

	x->mask		= htonw(mask);
	x->mode		= htonw(mode);
	x->mtime_cwient	= u64_to_xdw(mtime);
	x->ownew	= u64_to_xdw(ownew);
	x->gwoup	= u64_to_xdw(gwoup);
	wetuwn bp + xdw_size(x);
}

/*
 * Decode a YFSFetchVowumeStatus bwock.
 */
static void xdw_decode_YFSFetchVowumeStatus(const __be32 **_bp,
					    stwuct afs_vowume_status *vs)
{
	const stwuct yfs_xdw_YFSFetchVowumeStatus *x = (const void *)*_bp;
	u32 fwags;

	vs->vid			= xdw_to_u64(x->vid);
	vs->pawent_id		= xdw_to_u64(x->pawent_id);
	fwags			= ntohw(x->fwags);
	vs->onwine		= fwags & yfs_FVSOnwine;
	vs->in_sewvice		= fwags & yfs_FVSInsewvice;
	vs->bwessed		= fwags & yfs_FVSBwessed;
	vs->needs_sawvage	= fwags & yfs_FVSNeedsSawvage;
	vs->type		= ntohw(x->type);
	vs->min_quota		= 0;
	vs->max_quota		= xdw_to_u64(x->max_quota);
	vs->bwocks_in_use	= xdw_to_u64(x->bwocks_in_use);
	vs->pawt_bwocks_avaiw	= xdw_to_u64(x->pawt_bwocks_avaiw);
	vs->pawt_max_bwocks	= xdw_to_u64(x->pawt_max_bwocks);
	vs->vow_copy_date	= xdw_to_u64(x->vow_copy_date);
	vs->vow_backup_date	= xdw_to_u64(x->vow_backup_date);
	*_bp += sizeof(*x) / sizeof(__be32);
}

/*
 * Dewivew wepwy data to opewations that just wetuwn a fiwe status and a vowume
 * sync wecowd.
 */
static int yfs_dewivew_status_and_vowsync(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	const __be32 *bp;
	int wet;

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	xdw_decode_YFSFetchStatus(&bp, caww, &op->fiwe[0].scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * Dewivew wepwy data to an YFS.FetchData64.
 */
static int yfs_dewivew_fs_fetch_data64(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_wead *weq = op->fetch.weq;
	const __be32 *bp;
	int wet;

	_entew("{%u,%zu, %zu/%wwu}",
	       caww->unmawshaww, caww->iov_wen, iov_itew_count(caww->itew),
	       weq->actuaw_wen);

	switch (caww->unmawshaww) {
	case 0:
		weq->actuaw_wen = 0;
		afs_extwact_to_tmp64(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the wetuwned data wength into ->actuaw_wen.  This
		 * may indicate mowe ow wess data than was wequested wiww be
		 * wetuwned.
		 */
	case 1:
		_debug("extwact data wength");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		weq->actuaw_wen = be64_to_cpu(caww->tmp64);
		_debug("DATA wength: %wwu", weq->actuaw_wen);

		if (weq->actuaw_wen == 0)
			goto no_mowe_data;

		caww->itew = weq->itew;
		caww->iov_wen = min(weq->actuaw_wen, weq->wen);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the wetuwned data */
	case 2:
		_debug("extwact data %zu/%wwu",
		       iov_itew_count(caww->itew), weq->actuaw_wen);

		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->itew = &caww->def_itew;
		if (weq->actuaw_wen <= weq->wen)
			goto no_mowe_data;

		/* Discawd any excess data the sewvew gave us */
		afs_extwact_discawd(caww, weq->actuaw_wen - weq->wen);
		caww->unmawshaww = 3;
		fawwthwough;

	case 3:
		_debug("extwact discawd %zu/%wwu",
		       iov_itew_count(caww->itew), weq->actuaw_wen - weq->wen);

		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

	no_mowe_data:
		caww->unmawshaww = 4;
		afs_extwact_to_buf(caww,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSCawwBack) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
		fawwthwough;

		/* extwact the metadata */
	case 4:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
		xdw_decode_YFSCawwBack(&bp, caww, &vp->scb);
		xdw_decode_YFSVowSync(&bp, &op->vowsync);

		weq->data_vewsion = vp->scb.status.data_vewsion;
		weq->fiwe_size = vp->scb.status.size;

		caww->unmawshaww++;
		fawwthwough;

	case 5:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.FetchData64 opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSFetchData64 = {
	.name		= "YFS.FetchData64",
	.op		= yfs_FS_FetchData64,
	.dewivew	= yfs_dewivew_fs_fetch_data64,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch data fwom a fiwe.
 */
void yfs_fs_fetch_data(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_wead *weq = op->fetch.weq;
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},%wwx,%wwx",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode,
	       weq->pos, weq->wen);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSFetchData64,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_u64) * 2,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSCawwBack) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	weq->caww_debug_id = caww->debug_id;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSFETCHDATA64);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_u64(bp, weq->pos);
	bp = xdw_encode_u64(bp, weq->wen);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data fow YFS.CweateFiwe ow YFS.MakeDiw.
 */
static int yfs_dewivew_fs_cweate_vnode(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_YFSFid(&bp, &op->fiwe[1].fid);
	xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_YFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_YFSCawwBack(&bp, caww, &vp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.CweateFiwe and FS.MakeDiw opewation type
 */
static const stwuct afs_caww_type afs_WXFSCweateFiwe = {
	.name		= "YFS.CweateFiwe",
	.op		= yfs_FS_CweateFiwe,
	.dewivew	= yfs_dewivew_fs_cweate_vnode,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Cweate a fiwe.
 */
void yfs_fs_cweate_fiwe(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t weqsz, wpwsz;
	__be32 *bp;

	_entew("");

	weqsz = (sizeof(__be32) +
		 sizeof(__be32) +
		 sizeof(stwuct yfs_xdw_YFSFid) +
		 xdw_stwwen(name->wen) +
		 sizeof(stwuct yfs_xdw_YFSStoweStatus) +
		 sizeof(__be32));
	wpwsz = (sizeof(stwuct yfs_xdw_YFSFid) +
		 sizeof(stwuct yfs_xdw_YFSFetchStatus) +
		 sizeof(stwuct yfs_xdw_YFSFetchStatus) +
		 sizeof(stwuct yfs_xdw_YFSCawwBack) +
		 sizeof(stwuct yfs_xdw_YFSVowSync));

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSCweateFiwe, weqsz, wpwsz);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSCWEATEFIWE);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	bp = xdw_encode_YFSStoweStatus(bp, &op->cweate.mode, &op->mtime);
	bp = xdw_encode_u32(bp, yfs_WockNone); /* ViceWockType */
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

static const stwuct afs_caww_type yfs_WXFSMakeDiw = {
	.name		= "YFS.MakeDiw",
	.op		= yfs_FS_MakeDiw,
	.dewivew	= yfs_dewivew_fs_cweate_vnode,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Make a diwectowy.
 */
void yfs_fs_make_diw(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t weqsz, wpwsz;
	__be32 *bp;

	_entew("");

	weqsz = (sizeof(__be32) +
		 sizeof(stwuct yfs_xdw_WPCFwags) +
		 sizeof(stwuct yfs_xdw_YFSFid) +
		 xdw_stwwen(name->wen) +
		 sizeof(stwuct yfs_xdw_YFSStoweStatus));
	wpwsz = (sizeof(stwuct yfs_xdw_YFSFid) +
		 sizeof(stwuct yfs_xdw_YFSFetchStatus) +
		 sizeof(stwuct yfs_xdw_YFSFetchStatus) +
		 sizeof(stwuct yfs_xdw_YFSCawwBack) +
		 sizeof(stwuct yfs_xdw_YFSVowSync));

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXFSMakeDiw, weqsz, wpwsz);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSMAKEDIW);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	bp = xdw_encode_YFSStoweStatus(bp, &op->cweate.mode, &op->mtime);
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.WemoveFiwe2 opewation.
 */
static int yfs_dewivew_fs_wemove_fiwe2(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_fid fid;
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	xdw_decode_YFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_YFSFid(&bp, &fid);
	xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
	/* Was deweted if vnode->status.abowt_code == VNOVNODE. */

	xdw_decode_YFSVowSync(&bp, &op->vowsync);
	wetuwn 0;
}

static void yfs_done_fs_wemove_fiwe2(stwuct afs_caww *caww)
{
	if (caww->ewwow == -ECONNABOWTED &&
	    caww->abowt_code == WX_INVAWID_OPEWATION) {
		set_bit(AFS_SEWVEW_FW_NO_WM2, &caww->sewvew->fwags);
		caww->op->fwags |= AFS_OPEWATION_DOWNGWADE;
	}
}

/*
 * YFS.WemoveFiwe2 opewation type.
 */
static const stwuct afs_caww_type yfs_WXYFSWemoveFiwe2 = {
	.name		= "YFS.WemoveFiwe2",
	.op		= yfs_FS_WemoveFiwe2,
	.dewivew	= yfs_dewivew_fs_wemove_fiwe2,
	.done		= yfs_done_fs_wemove_fiwe2,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wemove a fiwe and wetwieve new fiwe status.
 */
void yfs_fs_wemove_fiwe2(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWemoveFiwe2,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(name->wen),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWEMOVEFIWE2);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.WemoveFiwe ow YFS.WemoveDiw opewation.
 */
static int yfs_dewivew_fs_wemove(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	xdw_decode_YFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);
	wetuwn 0;
}

/*
 * FS.WemoveDiw and FS.WemoveFiwe opewation types.
 */
static const stwuct afs_caww_type yfs_WXYFSWemoveFiwe = {
	.name		= "YFS.WemoveFiwe",
	.op		= yfs_FS_WemoveFiwe,
	.dewivew	= yfs_dewivew_fs_wemove,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wemove a fiwe.
 */
void yfs_fs_wemove_fiwe(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	if (!test_bit(AFS_SEWVEW_FW_NO_WM2, &op->sewvew->fwags))
		wetuwn yfs_fs_wemove_fiwe2(op);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWemoveFiwe,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(name->wen),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWEMOVEFIWE);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

static const stwuct afs_caww_type yfs_WXYFSWemoveDiw = {
	.name		= "YFS.WemoveDiw",
	.op		= yfs_FS_WemoveDiw,
	.dewivew	= yfs_dewivew_fs_wemove,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wemove a diwectowy.
 */
void yfs_fs_wemove_diw(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWemoveDiw,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(name->wen),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWEMOVEDIW);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.Wink opewation.
 */
static int yfs_dewivew_fs_wink(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_YFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);
	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.Wink opewation type.
 */
static const stwuct afs_caww_type yfs_WXYFSWink = {
	.name		= "YFS.Wink",
	.op		= yfs_FS_Wink,
	.dewivew	= yfs_dewivew_fs_wink,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Make a hawd wink.
 */
void yfs_fs_wink(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWink,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(name->wen) +
				   sizeof(stwuct yfs_xdw_YFSFid),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWINK);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww1(caww, &vp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.Symwink opewation.
 */
static int yfs_dewivew_fs_symwink(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_YFSFid(&bp, &vp->fid);
	xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_YFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.Symwink opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSSymwink = {
	.name		= "YFS.Symwink",
	.op		= yfs_FS_Symwink,
	.dewivew	= yfs_dewivew_fs_symwink,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Cweate a symbowic wink.
 */
void yfs_fs_symwink(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t contents_sz;
	mode_t mode = 0777;
	__be32 *bp;

	_entew("");

	contents_sz = stwwen(op->cweate.symwink);
	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSSymwink,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(name->wen) +
				   xdw_stwwen(contents_sz) +
				   sizeof(stwuct yfs_xdw_YFSStoweStatus),
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSYMWINK);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_name(bp, name);
	bp = xdw_encode_stwing(bp, op->cweate.symwink, contents_sz);
	bp = xdw_encode_YFSStoweStatus(bp, &mode, &op->mtime);
	yfs_check_weq(caww, bp);

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.Wename opewation.
 */
static int yfs_dewivew_fs_wename(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *owig_dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *new_dvp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	/* If the two diws awe the same, we have two copies of the same status
	 * wepowt, so we just decode it twice.
	 */
	xdw_decode_YFSFetchStatus(&bp, caww, &owig_dvp->scb);
	xdw_decode_YFSFetchStatus(&bp, caww, &new_dvp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);
	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.Wename opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSWename = {
	.name		= "FS.Wename",
	.op		= yfs_FS_Wename,
	.dewivew	= yfs_dewivew_fs_wename,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wename a fiwe ow diwectowy.
 */
void yfs_fs_wename(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *owig_dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *new_dvp = &op->fiwe[1];
	const stwuct qstw *owig_name = &op->dentwy->d_name;
	const stwuct qstw *new_name = &op->dentwy_2->d_name;
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWename,
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_WPCFwags) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(owig_name->wen) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   xdw_stwwen(new_name->wen),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWENAME);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &owig_dvp->fid);
	bp = xdw_encode_name(bp, owig_name);
	bp = xdw_encode_YFSFid(bp, &new_dvp->fid);
	bp = xdw_encode_name(bp, new_name);
	yfs_check_weq(caww, bp);

	caww->fid = owig_dvp->fid;
	twace_afs_make_fs_caww2(caww, &owig_dvp->fid, owig_name, new_name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * YFS.StoweData64 opewation type.
 */
static const stwuct afs_caww_type yfs_WXYFSStoweData64 = {
	.name		= "YFS.StoweData64",
	.op		= yfs_FS_StoweData64,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Stowe a set of pages to a wawge fiwe.
 */
void yfs_fs_stowe_data(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	_debug("size %wwx, at %wwx, i_size %wwx",
	       (unsigned wong wong)op->stowe.size,
	       (unsigned wong wong)op->stowe.pos,
	       (unsigned wong wong)op->stowe.i_size);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSStoweData64,
				   sizeof(__be32) +
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_YFSStoweStatus) +
				   sizeof(stwuct yfs_xdw_u64) * 3,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	caww->wwite_itew = op->stowe.wwite_itew;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSTOWEDATA64);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_YFSStoweStatus(bp, NUWW, &op->mtime);
	bp = xdw_encode_u64(bp, op->stowe.pos);
	bp = xdw_encode_u64(bp, op->stowe.size);
	bp = xdw_encode_u64(bp, op->stowe.i_size);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * YFS.StoweStatus opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSStoweStatus = {
	.name		= "YFS.StoweStatus",
	.op		= yfs_FS_StoweStatus,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

static const stwuct afs_caww_type yfs_WXYFSStoweData64_as_Status = {
	.name		= "YFS.StoweData64",
	.op		= yfs_FS_StoweData64,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Set the attwibutes on a fiwe, using YFS.StoweData64 wathew than
 * YFS.StoweStatus so as to awtew the fiwe size awso.
 */
static void yfs_fs_setattw_size(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct iattw *attw = op->setattw.attw;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSStoweData64_as_Status,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_YFSStoweStatus) +
				   sizeof(stwuct yfs_xdw_u64) * 3,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSTOWEDATA64);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_YFS_StoweStatus(bp, attw);
	bp = xdw_encode_u64(bp, attw->ia_size);	/* position of stawt of wwite */
	bp = xdw_encode_u64(bp, 0);		/* size of wwite */
	bp = xdw_encode_u64(bp, attw->ia_size);	/* new fiwe wength */
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Set the attwibutes on a fiwe, using YFS.StoweData64 if thewe's a change in
 * fiwe size, and YFS.StoweStatus othewwise.
 */
void yfs_fs_setattw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct iattw *attw = op->setattw.attw;
	__be32 *bp;

	if (attw->ia_vawid & ATTW_SIZE)
		wetuwn yfs_fs_setattw_size(op);

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSStoweStatus,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(stwuct yfs_xdw_YFSStoweStatus),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSTOWESTATUS);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_YFS_StoweStatus(bp, attw);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to a YFS.GetVowumeStatus opewation.
 */
static int yfs_dewivew_fs_get_vowume_status(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	const __be32 *bp;
	chaw *p;
	u32 size;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		caww->unmawshaww++;
		afs_extwact_to_buf(caww, sizeof(stwuct yfs_xdw_YFSFetchVowumeStatus));
		fawwthwough;

		/* extwact the wetuwned status wecowd */
	case 1:
		_debug("extwact status");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_YFSFetchVowumeStatus(&bp, &op->vowstatus.vs);
		caww->unmawshaww++;
		afs_extwact_to_tmp(caww);
		fawwthwough;

		/* extwact the vowume name wength */
	case 2:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count = ntohw(caww->tmp);
		_debug("vowname wength: %u", caww->count);
		if (caww->count >= AFSNAMEMAX)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_vowname_wen);
		size = (caww->count + 3) & ~3; /* It's padded */
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the vowume name */
	case 3:
		_debug("extwact vowname");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		p = caww->buffew;
		p[caww->count] = 0;
		_debug("vowname '%s'", p);
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the offwine message wength */
	case 4:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count = ntohw(caww->tmp);
		_debug("offwine msg wength: %u", caww->count);
		if (caww->count >= AFSNAMEMAX)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_offwine_msg_wen);
		size = (caww->count + 3) & ~3; /* It's padded */
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the offwine message */
	case 5:
		_debug("extwact offwine");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		p = caww->buffew;
		p[caww->count] = 0;
		_debug("offwine '%s'", p);

		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the message of the day wength */
	case 6:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count = ntohw(caww->tmp);
		_debug("motd wength: %u", caww->count);
		if (caww->count >= AFSNAMEMAX)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_motd_wen);
		size = (caww->count + 3) & ~3; /* It's padded */
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the message of the day */
	case 7:
		_debug("extwact motd");
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		p = caww->buffew;
		p[caww->count] = 0;
		_debug("motd '%s'", p);

		caww->unmawshaww++;
		fawwthwough;

	case 8:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.GetVowumeStatus opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSGetVowumeStatus = {
	.name		= "YFS.GetVowumeStatus",
	.op		= yfs_FS_GetVowumeStatus,
	.dewivew	= yfs_dewivew_fs_get_vowume_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * fetch the status of a vowume
 */
void yfs_fs_get_vowume_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSGetVowumeStatus,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_u64),
				   max_t(size_t,
					 sizeof(stwuct yfs_xdw_YFSFetchVowumeStatus) +
					 sizeof(__be32),
					 AFSOPAQUEMAX + 1));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSGETVOWUMESTATUS);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_u64(bp, vp->fid.vid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * YFS.SetWock opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSSetWock = {
	.name		= "YFS.SetWock",
	.op		= yfs_FS_SetWock,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.done		= afs_wock_op_done,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * YFS.ExtendWock opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSExtendWock = {
	.name		= "YFS.ExtendWock",
	.op		= yfs_FS_ExtendWock,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.done		= afs_wock_op_done,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * YFS.WeweaseWock opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSWeweaseWock = {
	.name		= "YFS.WeweaseWock",
	.op		= yfs_FS_WeweaseWock,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Set a wock on a fiwe
 */
void yfs_fs_set_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSSetWock,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(__be32),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSETWOCK);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_u32(bp, op->wock.type);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_cawwi(caww, &vp->fid, op->wock.type);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * extend a wock on a fiwe
 */
void yfs_fs_extend_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSExtendWock,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSEXTENDWOCK);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * wewease a wock on a fiwe
 */
void yfs_fs_wewease_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSWeweaseWock,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSWEWEASEWOCK);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew a wepwy to YFS.FetchStatus
 */
static int yfs_dewivew_fs_fetch_status(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[op->fetch_status.which];
	const __be32 *bp;
	int wet;

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_YFSCawwBack(&bp, caww, &vp->scb);
	xdw_decode_YFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFS.FetchStatus opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSFetchStatus = {
	.name		= "YFS.FetchStatus",
	.op		= yfs_FS_FetchStatus,
	.dewivew	= yfs_dewivew_fs_fetch_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the status infowmation fow a fid without needing a vnode handwe.
 */
void yfs_fs_fetch_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[op->fetch_status.which];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSFetchStatus,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid),
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSCawwBack) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSFETCHSTATUS);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to an YFS.InwineBuwkStatus caww
 */
static int yfs_dewivew_fs_inwine_buwk_status(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_status_cb *scb;
	const __be32 *bp;
	u32 tmp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the fiwe status count and awway in two steps */
	case 1:
		_debug("extwact status count");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		tmp = ntohw(caww->tmp);
		_debug("status count: %u/%u", tmp, op->nw_fiwes);
		if (tmp != op->nw_fiwes)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_ibuwkst_count);

		caww->count = 0;
		caww->unmawshaww++;
	mowe_counts:
		afs_extwact_to_buf(caww, sizeof(stwuct yfs_xdw_YFSFetchStatus));
		fawwthwough;

	case 2:
		_debug("extwact status awway %u", caww->count);
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		switch (caww->count) {
		case 0:
			scb = &op->fiwe[0].scb;
			bweak;
		case 1:
			scb = &op->fiwe[1].scb;
			bweak;
		defauwt:
			scb = &op->mowe_fiwes[caww->count - 2].scb;
			bweak;
		}

		bp = caww->buffew;
		xdw_decode_YFSFetchStatus(&bp, caww, scb);

		caww->count++;
		if (caww->count < op->nw_fiwes)
			goto mowe_counts;

		caww->count = 0;
		caww->unmawshaww++;
		afs_extwact_to_tmp(caww);
		fawwthwough;

		/* Extwact the cawwback count and awway in two steps */
	case 3:
		_debug("extwact CB count");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		tmp = ntohw(caww->tmp);
		_debug("CB count: %u", tmp);
		if (tmp != op->nw_fiwes)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_ibuwkst_cb_count);
		caww->count = 0;
		caww->unmawshaww++;
	mowe_cbs:
		afs_extwact_to_buf(caww, sizeof(stwuct yfs_xdw_YFSCawwBack));
		fawwthwough;

	case 4:
		_debug("extwact CB awway");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		_debug("unmawshaww CB awway");
		switch (caww->count) {
		case 0:
			scb = &op->fiwe[0].scb;
			bweak;
		case 1:
			scb = &op->fiwe[1].scb;
			bweak;
		defauwt:
			scb = &op->mowe_fiwes[caww->count - 2].scb;
			bweak;
		}

		bp = caww->buffew;
		xdw_decode_YFSCawwBack(&bp, caww, scb);
		caww->count++;
		if (caww->count < op->nw_fiwes)
			goto mowe_cbs;

		afs_extwact_to_buf(caww, sizeof(stwuct yfs_xdw_YFSVowSync));
		caww->unmawshaww++;
		fawwthwough;

	case 5:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_YFSVowSync(&bp, &op->vowsync);

		caww->unmawshaww++;
		fawwthwough;

	case 6:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.InwineBuwkStatus opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSInwineBuwkStatus = {
	.name		= "YFS.InwineBuwkStatus",
	.op		= yfs_FS_InwineBuwkStatus,
	.dewivew	= yfs_dewivew_fs_inwine_buwk_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the status infowmation fow up to 1024 fiwes
 */
void yfs_fs_inwine_buwk_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_caww *caww;
	__be32 *bp;
	int i;

	_entew(",%x,{%wwx:%wwu},%u",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode, op->nw_fiwes);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSInwineBuwkStatus,
				   sizeof(__be32) +
				   sizeof(__be32) +
				   sizeof(__be32) +
				   sizeof(stwuct yfs_xdw_YFSFid) * op->nw_fiwes,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSINWINEBUWKSTATUS);
	bp = xdw_encode_u32(bp, 0); /* WPCFwags */
	bp = xdw_encode_u32(bp, op->nw_fiwes);
	bp = xdw_encode_YFSFid(bp, &dvp->fid);
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	fow (i = 0; i < op->nw_fiwes - 2; i++)
		bp = xdw_encode_YFSFid(bp, &op->mowe_fiwes[i].fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to an YFS.FetchOpaqueACW.
 */
static int yfs_dewivew_fs_fetch_opaque_acw(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct yfs_acw *yacw = op->yacw;
	stwuct afs_acw *acw;
	const __be32 *bp;
	unsigned int size;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the fiwe ACW wength */
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		size = caww->count2 = ntohw(caww->tmp);
		size = wound_up(size, 4);

		if (yacw->fwags & YFS_ACW_WANT_ACW) {
			acw = kmawwoc(stwuct_size(acw, data, size), GFP_KEWNEW);
			if (!acw)
				wetuwn -ENOMEM;
			yacw->acw = acw;
			acw->size = caww->count2;
			afs_extwact_begin(caww, acw->data, size);
		} ewse {
			afs_extwact_discawd(caww, size);
		}
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the fiwe ACW */
	case 2:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the vowume ACW wength */
	case 3:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		size = caww->count2 = ntohw(caww->tmp);
		size = wound_up(size, 4);

		if (yacw->fwags & YFS_ACW_WANT_VOW_ACW) {
			acw = kmawwoc(stwuct_size(acw, data, size), GFP_KEWNEW);
			if (!acw)
				wetuwn -ENOMEM;
			yacw->vow_acw = acw;
			acw->size = caww->count2;
			afs_extwact_begin(caww, acw->data, size);
		} ewse {
			afs_extwact_discawd(caww, size);
		}
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the vowume ACW */
	case 4:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		afs_extwact_to_buf(caww,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the metadata */
	case 5:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		yacw->inhewit_fwag = ntohw(*bp++);
		yacw->num_cweaned = ntohw(*bp++);
		xdw_decode_YFSFetchStatus(&bp, caww, &vp->scb);
		xdw_decode_YFSVowSync(&bp, &op->vowsync);

		caww->unmawshaww++;
		fawwthwough;

	case 6:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

void yfs_fwee_opaque_acw(stwuct yfs_acw *yacw)
{
	if (yacw) {
		kfwee(yacw->acw);
		kfwee(yacw->vow_acw);
		kfwee(yacw);
	}
}

/*
 * YFS.FetchOpaqueACW opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSFetchOpaqueACW = {
	.name		= "YFS.FetchOpaqueACW",
	.op		= yfs_FS_FetchOpaqueACW,
	.dewivew	= yfs_dewivew_fs_fetch_opaque_acw,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the YFS advanced ACWs fow a fiwe.
 */
void yfs_fs_fetch_opaque_acw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSFetchOpaqueACW,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid),
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSFETCHOPAQUEACW);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_KEWNEW);
}

/*
 * YFS.StoweOpaqueACW2 opewation type
 */
static const stwuct afs_caww_type yfs_WXYFSStoweOpaqueACW2 = {
	.name		= "YFS.StoweOpaqueACW2",
	.op		= yfs_FS_StoweOpaqueACW2,
	.dewivew	= yfs_dewivew_status_and_vowsync,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the YFS ACW fow a fiwe.
 */
void yfs_fs_stowe_opaque_acw2(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct afs_acw *acw = op->acw;
	size_t size;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	size = wound_up(acw->size, 4);
	caww = afs_awwoc_fwat_caww(op->net, &yfs_WXYFSStoweOpaqueACW2,
				   sizeof(__be32) * 2 +
				   sizeof(stwuct yfs_xdw_YFSFid) +
				   sizeof(__be32) + size,
				   sizeof(stwuct yfs_xdw_YFSFetchStatus) +
				   sizeof(stwuct yfs_xdw_YFSVowSync));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp = xdw_encode_u32(bp, YFSSTOWEOPAQUEACW2);
	bp = xdw_encode_u32(bp, 0); /* WPC fwags */
	bp = xdw_encode_YFSFid(bp, &vp->fid);
	bp = xdw_encode_u32(bp, acw->size);
	memcpy(bp, acw->data, acw->size);
	if (acw->size != size)
		memset((void *)bp + acw->size, 0, size - acw->size);
	bp += size / sizeof(__be32);
	yfs_check_weq(caww, bp);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_KEWNEW);
}
