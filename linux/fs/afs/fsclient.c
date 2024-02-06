// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS Fiwe Sewvew cwient stubs
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/ivewsion.h>
#incwude <winux/netfs.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"
#incwude "xdw_fs.h"

/*
 * decode an AFSFid bwock
 */
static void xdw_decode_AFSFid(const __be32 **_bp, stwuct afs_fid *fid)
{
	const __be32 *bp = *_bp;

	fid->vid		= ntohw(*bp++);
	fid->vnode		= ntohw(*bp++);
	fid->unique		= ntohw(*bp++);
	*_bp = bp;
}

/*
 * Dump a bad fiwe status wecowd.
 */
static void xdw_dump_bad(const __be32 *bp)
{
	__be32 x[4];
	int i;

	pw_notice("AFS XDW: Bad status wecowd\n");
	fow (i = 0; i < 5 * 4 * 4; i += 16) {
		memcpy(x, bp, 16);
		bp += 4;
		pw_notice("%03x: %08x %08x %08x %08x\n",
			  i, ntohw(x[0]), ntohw(x[1]), ntohw(x[2]), ntohw(x[3]));
	}

	memcpy(x, bp, 4);
	pw_notice("0x50: %08x\n", ntohw(x[0]));
}

/*
 * decode an AFSFetchStatus bwock
 */
static void xdw_decode_AFSFetchStatus(const __be32 **_bp,
				      stwuct afs_caww *caww,
				      stwuct afs_status_cb *scb)
{
	const stwuct afs_xdw_AFSFetchStatus *xdw = (const void *)*_bp;
	stwuct afs_fiwe_status *status = &scb->status;
	boow inwine_ewwow = (caww->opewation_ID == afs_FS_InwineBuwkStatus);
	u64 data_vewsion, size;
	u32 type, abowt_code;

	abowt_code = ntohw(xdw->abowt_code);

	if (xdw->if_vewsion != htonw(AFS_FSTATUS_VEWSION)) {
		if (xdw->if_vewsion == htonw(0) &&
		    abowt_code != 0 &&
		    inwine_ewwow) {
			/* The OpenAFS fiwesewvew has a bug in FS.InwineBuwkStatus
			 * wheweby it doesn't set the intewface vewsion in the ewwow
			 * case.
			 */
			status->abowt_code = abowt_code;
			scb->have_ewwow = twue;
			goto advance;
		}

		pw_wawn("Unknown AFSFetchStatus vewsion %u\n", ntohw(xdw->if_vewsion));
		goto bad;
	}

	if (abowt_code != 0 && inwine_ewwow) {
		status->abowt_code = abowt_code;
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
	status->authow		= ntohw(xdw->authow);
	status->ownew		= ntohw(xdw->ownew);
	status->cawwew_access	= ntohw(xdw->cawwew_access); /* Ticket dependent */
	status->anon_access	= ntohw(xdw->anon_access);
	status->mode		= ntohw(xdw->mode) & S_IAWWUGO;
	status->gwoup		= ntohw(xdw->gwoup);
	status->wock_count	= ntohw(xdw->wock_count);

	status->mtime_cwient.tv_sec = ntohw(xdw->mtime_cwient);
	status->mtime_cwient.tv_nsec = 0;
	status->mtime_sewvew.tv_sec = ntohw(xdw->mtime_sewvew);
	status->mtime_sewvew.tv_nsec = 0;

	size  = (u64)ntohw(xdw->size_wo);
	size |= (u64)ntohw(xdw->size_hi) << 32;
	status->size = size;

	data_vewsion  = (u64)ntohw(xdw->data_vewsion_wo);
	data_vewsion |= (u64)ntohw(xdw->data_vewsion_hi) << 32;
	status->data_vewsion = data_vewsion;
	scb->have_status = twue;
advance:
	*_bp = (const void *)*_bp + sizeof(*xdw);
	wetuwn;

bad:
	xdw_dump_bad(*_bp);
	afs_pwotocow_ewwow(caww, afs_epwoto_bad_status);
	goto advance;
}

static time64_t xdw_decode_expiwy(stwuct afs_caww *caww, u32 expiwy)
{
	wetuwn ktime_divns(caww->issue_time, NSEC_PEW_SEC) + expiwy;
}

static void xdw_decode_AFSCawwBack(const __be32 **_bp,
				   stwuct afs_caww *caww,
				   stwuct afs_status_cb *scb)
{
	stwuct afs_cawwback *cb = &scb->cawwback;
	const __be32 *bp = *_bp;

	bp++; /* vewsion */
	cb->expiwes_at	= xdw_decode_expiwy(caww, ntohw(*bp++));
	bp++; /* type */
	scb->have_cb	= twue;
	*_bp = bp;
}

/*
 * decode an AFSVowSync bwock
 */
static void xdw_decode_AFSVowSync(const __be32 **_bp,
				  stwuct afs_vowsync *vowsync)
{
	const __be32 *bp = *_bp;
	u32 cweation;

	cweation = ntohw(*bp++);
	bp++; /* spawe2 */
	bp++; /* spawe3 */
	bp++; /* spawe4 */
	bp++; /* spawe5 */
	bp++; /* spawe6 */
	*_bp = bp;

	if (vowsync)
		vowsync->cweation = cweation;
}

/*
 * encode the wequested attwibutes into an AFSStoweStatus bwock
 */
static void xdw_encode_AFS_StoweStatus(__be32 **_bp, stwuct iattw *attw)
{
	__be32 *bp = *_bp;
	u32 mask = 0, mtime = 0, ownew = 0, gwoup = 0, mode = 0;

	mask = 0;
	if (attw->ia_vawid & ATTW_MTIME) {
		mask |= AFS_SET_MTIME;
		mtime = attw->ia_mtime.tv_sec;
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

	*bp++ = htonw(mask);
	*bp++ = htonw(mtime);
	*bp++ = htonw(ownew);
	*bp++ = htonw(gwoup);
	*bp++ = htonw(mode);
	*bp++ = 0;		/* segment size */
	*_bp = bp;
}

/*
 * decode an AFSFetchVowumeStatus bwock
 */
static void xdw_decode_AFSFetchVowumeStatus(const __be32 **_bp,
					    stwuct afs_vowume_status *vs)
{
	const __be32 *bp = *_bp;

	vs->vid			= ntohw(*bp++);
	vs->pawent_id		= ntohw(*bp++);
	vs->onwine		= ntohw(*bp++);
	vs->in_sewvice		= ntohw(*bp++);
	vs->bwessed		= ntohw(*bp++);
	vs->needs_sawvage	= ntohw(*bp++);
	vs->type		= ntohw(*bp++);
	vs->min_quota		= ntohw(*bp++);
	vs->max_quota		= ntohw(*bp++);
	vs->bwocks_in_use	= ntohw(*bp++);
	vs->pawt_bwocks_avaiw	= ntohw(*bp++);
	vs->pawt_max_bwocks	= ntohw(*bp++);
	vs->vow_copy_date	= 0;
	vs->vow_backup_date	= 0;
	*_bp = bp;
}

/*
 * dewivew wepwy data to an FS.FetchStatus
 */
static int afs_dewivew_fs_fetch_status(stwuct afs_caww *caww)
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
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSCawwBack(&bp, caww, &vp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.FetchStatus opewation type
 */
static const stwuct afs_caww_type afs_WXFSFetchStatus = {
	.name		= "FS.FetchStatus",
	.op		= afs_FS_FetchStatus,
	.dewivew	= afs_dewivew_fs_fetch_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * fetch the status infowmation fow a fiwe
 */
void afs_fs_fetch_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[op->fetch_status.which];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSFetchStatus,
				   16, (21 + 3 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSFETCHSTATUS);
	bp[1] = htonw(vp->fid.vid);
	bp[2] = htonw(vp->fid.vnode);
	bp[3] = htonw(vp->fid.unique);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.FetchData
 */
static int afs_dewivew_fs_fetch_data(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_wead *weq = op->fetch.weq;
	const __be32 *bp;
	int wet;

	_entew("{%u,%zu,%zu/%wwu}",
	       caww->unmawshaww, caww->iov_wen, iov_itew_count(caww->itew),
	       weq->actuaw_wen);

	switch (caww->unmawshaww) {
	case 0:
		weq->actuaw_wen = 0;
		caww->unmawshaww++;
		if (caww->opewation_ID == FSFETCHDATA64) {
			afs_extwact_to_tmp64(caww);
		} ewse {
			caww->tmp_u = htonw(0);
			afs_extwact_to_tmp(caww);
		}
		fawwthwough;

		/* Extwact the wetuwned data wength into
		 * ->actuaw_wen.  This may indicate mowe ow wess data than was
		 * wequested wiww be wetuwned.
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
		afs_extwact_to_buf(caww, (21 + 3 + 6) * 4);
		fawwthwough;

		/* extwact the metadata */
	case 4:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
		xdw_decode_AFSCawwBack(&bp, caww, &vp->scb);
		xdw_decode_AFSVowSync(&bp, &op->vowsync);

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
 * FS.FetchData opewation type
 */
static const stwuct afs_caww_type afs_WXFSFetchData = {
	.name		= "FS.FetchData",
	.op		= afs_FS_FetchData,
	.dewivew	= afs_dewivew_fs_fetch_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

static const stwuct afs_caww_type afs_WXFSFetchData64 = {
	.name		= "FS.FetchData64",
	.op		= afs_FS_FetchData64,
	.dewivew	= afs_dewivew_fs_fetch_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * fetch data fwom a vewy wawge fiwe
 */
static void afs_fs_fetch_data64(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_wead *weq = op->fetch.weq;
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSFetchData64, 32, (21 + 3 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSFETCHDATA64);
	bp[1] = htonw(vp->fid.vid);
	bp[2] = htonw(vp->fid.vnode);
	bp[3] = htonw(vp->fid.unique);
	bp[4] = htonw(uppew_32_bits(weq->pos));
	bp[5] = htonw(wowew_32_bits(weq->pos));
	bp[6] = 0;
	bp[7] = htonw(wowew_32_bits(weq->wen));

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * fetch data fwom a fiwe
 */
void afs_fs_fetch_data(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct afs_wead *weq = op->fetch.weq;
	__be32 *bp;

	if (test_bit(AFS_SEWVEW_FW_HAS_FS64, &op->sewvew->fwags))
		wetuwn afs_fs_fetch_data64(op);

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSFetchData, 24, (21 + 3 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	weq->caww_debug_id = caww->debug_id;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSFETCHDATA);
	bp[1] = htonw(vp->fid.vid);
	bp[2] = htonw(vp->fid.vnode);
	bp[3] = htonw(vp->fid.unique);
	bp[4] = htonw(wowew_32_bits(weq->pos));
	bp[5] = htonw(wowew_32_bits(weq->wen));

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.CweateFiwe ow an FS.MakeDiw
 */
static int afs_dewivew_fs_cweate_vnode(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_AFSFid(&bp, &op->fiwe[1].fid);
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_AFSCawwBack(&bp, caww, &vp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.CweateFiwe and FS.MakeDiw opewation type
 */
static const stwuct afs_caww_type afs_WXFSCweateFiwe = {
	.name		= "FS.CweateFiwe",
	.op		= afs_FS_CweateFiwe,
	.dewivew	= afs_dewivew_fs_cweate_vnode,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Cweate a fiwe.
 */
void afs_fs_cweate_fiwe(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;
	weqsz = (5 * 4) + namesz + padsz + (6 * 4);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSCweateFiwe,
				   weqsz, (3 + 21 + 21 + 3 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSCWEATEFIWE);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonw(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonw(op->mtime.tv_sec); /* mtime */
	*bp++ = 0; /* ownew */
	*bp++ = 0; /* gwoup */
	*bp++ = htonw(op->cweate.mode & S_IAWWUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

static const stwuct afs_caww_type afs_WXFSMakeDiw = {
	.name		= "FS.MakeDiw",
	.op		= afs_FS_MakeDiw,
	.dewivew	= afs_dewivew_fs_cweate_vnode,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Cweate a new diwectowy
 */
void afs_fs_make_diw(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;
	weqsz = (5 * 4) + namesz + padsz + (6 * 4);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSMakeDiw,
				   weqsz, (3 + 21 + 21 + 3 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSMAKEDIW);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonw(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonw(op->mtime.tv_sec); /* mtime */
	*bp++ = 0; /* ownew */
	*bp++ = 0; /* gwoup */
	*bp++ = htonw(op->cweate.mode & S_IAWWUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to any opewation that wetuwns status and vowume sync.
 */
static int afs_dewivew_fs_fiwe_status_and_vow(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	const __be32 *bp;
	int wet;

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.WemoveFiwe opewation type
 */
static const stwuct afs_caww_type afs_WXFSWemoveFiwe = {
	.name		= "FS.WemoveFiwe",
	.op		= afs_FS_WemoveFiwe,
	.dewivew	= afs_dewivew_fs_fiwe_status_and_vow,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wemove a fiwe.
 */
void afs_fs_wemove_fiwe(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;
	weqsz = (5 * 4) + namesz + padsz;

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSWemoveFiwe,
				   weqsz, (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSWEMOVEFIWE);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

static const stwuct afs_caww_type afs_WXFSWemoveDiw = {
	.name		= "FS.WemoveDiw",
	.op		= afs_FS_WemoveDiw,
	.dewivew	= afs_dewivew_fs_fiwe_status_and_vow,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wemove a diwectowy.
 */
void afs_fs_wemove_diw(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;
	weqsz = (5 * 4) + namesz + padsz;

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSWemoveDiw,
				   weqsz, (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSWEMOVEDIW);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.Wink
 */
static int afs_dewivew_fs_wink(stwuct afs_caww *caww)
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
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.Wink opewation type
 */
static const stwuct afs_caww_type afs_WXFSWink = {
	.name		= "FS.Wink",
	.op		= afs_FS_Wink,
	.dewivew	= afs_dewivew_fs_wink,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * make a hawd wink
 */
void afs_fs_wink(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;
	weqsz = (5 * 4) + namesz + padsz + (3 * 4);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSWink, weqsz, (21 + 21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSWINK);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww1(caww, &vp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.Symwink
 */
static int afs_dewivew_fs_symwink(stwuct afs_caww *caww)
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
	xdw_decode_AFSFid(&bp, &vp->fid);
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSFetchStatus(&bp, caww, &dvp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.Symwink opewation type
 */
static const stwuct afs_caww_type afs_WXFSSymwink = {
	.name		= "FS.Symwink",
	.op		= afs_FS_Symwink,
	.dewivew	= afs_dewivew_fs_symwink,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * cweate a symbowic wink
 */
void afs_fs_symwink(stwuct afs_opewation *op)
{
	const stwuct qstw *name = &op->dentwy->d_name;
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_caww *caww;
	size_t namesz, weqsz, padsz, c_namesz, c_padsz;
	__be32 *bp;

	_entew("");

	namesz = name->wen;
	padsz = (4 - (namesz & 3)) & 3;

	c_namesz = stwwen(op->cweate.symwink);
	c_padsz = (4 - (c_namesz & 3)) & 3;

	weqsz = (6 * 4) + namesz + padsz + c_namesz + c_padsz + (6 * 4);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSSymwink, weqsz,
				   (3 + 21 + 21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSYMWINK);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(namesz);
	memcpy(bp, name->name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonw(c_namesz);
	memcpy(bp, op->cweate.symwink, c_namesz);
	bp = (void *) bp + c_namesz;
	if (c_padsz > 0) {
		memset(bp, 0, c_padsz);
		bp = (void *) bp + c_padsz;
	}
	*bp++ = htonw(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonw(op->mtime.tv_sec); /* mtime */
	*bp++ = 0; /* ownew */
	*bp++ = 0; /* gwoup */
	*bp++ = htonw(S_IWWXUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	caww->fid = dvp->fid;
	twace_afs_make_fs_caww1(caww, &dvp->fid, name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.Wename
 */
static int afs_dewivew_fs_wename(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *owig_dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *new_dvp = &op->fiwe[1];
	const __be32 *bp;
	int wet;

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	bp = caww->buffew;
	/* If the two diws awe the same, we have two copies of the same status
	 * wepowt, so we just decode it twice.
	 */
	xdw_decode_AFSFetchStatus(&bp, caww, &owig_dvp->scb);
	xdw_decode_AFSFetchStatus(&bp, caww, &new_dvp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.Wename opewation type
 */
static const stwuct afs_caww_type afs_WXFSWename = {
	.name		= "FS.Wename",
	.op		= afs_FS_Wename,
	.dewivew	= afs_dewivew_fs_wename,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Wename/move a fiwe ow diwectowy.
 */
void afs_fs_wename(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *owig_dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *new_dvp = &op->fiwe[1];
	const stwuct qstw *owig_name = &op->dentwy->d_name;
	const stwuct qstw *new_name = &op->dentwy_2->d_name;
	stwuct afs_caww *caww;
	size_t weqsz, o_namesz, o_padsz, n_namesz, n_padsz;
	__be32 *bp;

	_entew("");

	o_namesz = owig_name->wen;
	o_padsz = (4 - (o_namesz & 3)) & 3;

	n_namesz = new_name->wen;
	n_padsz = (4 - (n_namesz & 3)) & 3;

	weqsz = (4 * 4) +
		4 + o_namesz + o_padsz +
		(3 * 4) +
		4 + n_namesz + n_padsz;

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSWename, weqsz, (21 + 21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSWENAME);
	*bp++ = htonw(owig_dvp->fid.vid);
	*bp++ = htonw(owig_dvp->fid.vnode);
	*bp++ = htonw(owig_dvp->fid.unique);
	*bp++ = htonw(o_namesz);
	memcpy(bp, owig_name->name, o_namesz);
	bp = (void *) bp + o_namesz;
	if (o_padsz > 0) {
		memset(bp, 0, o_padsz);
		bp = (void *) bp + o_padsz;
	}

	*bp++ = htonw(new_dvp->fid.vid);
	*bp++ = htonw(new_dvp->fid.vnode);
	*bp++ = htonw(new_dvp->fid.unique);
	*bp++ = htonw(n_namesz);
	memcpy(bp, new_name->name, n_namesz);
	bp = (void *) bp + n_namesz;
	if (n_padsz > 0) {
		memset(bp, 0, n_padsz);
		bp = (void *) bp + n_padsz;
	}

	caww->fid = owig_dvp->fid;
	twace_afs_make_fs_caww2(caww, &owig_dvp->fid, owig_name, new_name);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to FS.StoweData ow FS.StoweStatus
 */
static int afs_dewivew_fs_stowe_data(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	const __be32 *bp;
	int wet;

	_entew("");

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.StoweData opewation type
 */
static const stwuct afs_caww_type afs_WXFSStoweData = {
	.name		= "FS.StoweData",
	.op		= afs_FS_StoweData,
	.dewivew	= afs_dewivew_fs_stowe_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

static const stwuct afs_caww_type afs_WXFSStoweData64 = {
	.name		= "FS.StoweData64",
	.op		= afs_FS_StoweData64,
	.dewivew	= afs_dewivew_fs_stowe_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * stowe a set of pages to a vewy wawge fiwe
 */
static void afs_fs_stowe_data64(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweData64,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	caww->wwite_itew = op->stowe.wwite_itew;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSTOWEDATA64);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	*bp++ = htonw(AFS_SET_MTIME); /* mask */
	*bp++ = htonw(op->mtime.tv_sec); /* mtime */
	*bp++ = 0; /* ownew */
	*bp++ = 0; /* gwoup */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonw(uppew_32_bits(op->stowe.pos));
	*bp++ = htonw(wowew_32_bits(op->stowe.pos));
	*bp++ = htonw(uppew_32_bits(op->stowe.size));
	*bp++ = htonw(wowew_32_bits(op->stowe.size));
	*bp++ = htonw(uppew_32_bits(op->stowe.i_size));
	*bp++ = htonw(wowew_32_bits(op->stowe.i_size));

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Wwite data to a fiwe on the sewvew.
 */
void afs_fs_stowe_data(stwuct afs_opewation *op)
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

	if (test_bit(AFS_SEWVEW_FW_HAS_FS64, &op->sewvew->fwags))
		wetuwn afs_fs_stowe_data64(op);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweData,
				   (4 + 6 + 3) * 4,
				   (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	caww->wwite_itew = op->stowe.wwite_itew;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSTOWEDATA);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	*bp++ = htonw(AFS_SET_MTIME); /* mask */
	*bp++ = htonw(op->mtime.tv_sec); /* mtime */
	*bp++ = 0; /* ownew */
	*bp++ = 0; /* gwoup */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonw(wowew_32_bits(op->stowe.pos));
	*bp++ = htonw(wowew_32_bits(op->stowe.size));
	*bp++ = htonw(wowew_32_bits(op->stowe.i_size));

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * FS.StoweStatus opewation type
 */
static const stwuct afs_caww_type afs_WXFSStoweStatus = {
	.name		= "FS.StoweStatus",
	.op		= afs_FS_StoweStatus,
	.dewivew	= afs_dewivew_fs_stowe_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

static const stwuct afs_caww_type afs_WXFSStoweData_as_Status = {
	.name		= "FS.StoweData",
	.op		= afs_FS_StoweData,
	.dewivew	= afs_dewivew_fs_stowe_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

static const stwuct afs_caww_type afs_WXFSStoweData64_as_Status = {
	.name		= "FS.StoweData64",
	.op		= afs_FS_StoweData64,
	.dewivew	= afs_dewivew_fs_stowe_data,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * set the attwibutes on a vewy wawge fiwe, using FS.StoweData wathew than
 * FS.StoweStatus so as to awtew the fiwe size awso
 */
static void afs_fs_setattw_size64(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct iattw *attw = op->setattw.attw;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	ASSEWT(attw->ia_vawid & ATTW_SIZE);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweData64_as_Status,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSTOWEDATA64);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	xdw_encode_AFS_StoweStatus(&bp, attw);

	*bp++ = htonw(uppew_32_bits(attw->ia_size));	/* position of stawt of wwite */
	*bp++ = htonw(wowew_32_bits(attw->ia_size));
	*bp++ = 0;					/* size of wwite */
	*bp++ = 0;
	*bp++ = htonw(uppew_32_bits(attw->ia_size));	/* new fiwe wength */
	*bp++ = htonw(wowew_32_bits(attw->ia_size));

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * set the attwibutes on a fiwe, using FS.StoweData wathew than FS.StoweStatus
 * so as to awtew the fiwe size awso
 */
static void afs_fs_setattw_size(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct iattw *attw = op->setattw.attw;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	ASSEWT(attw->ia_vawid & ATTW_SIZE);
	if (test_bit(AFS_SEWVEW_FW_HAS_FS64, &op->sewvew->fwags))
		wetuwn afs_fs_setattw_size64(op);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweData_as_Status,
				   (4 + 6 + 3) * 4,
				   (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSTOWEDATA);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	xdw_encode_AFS_StoweStatus(&bp, attw);

	*bp++ = htonw(attw->ia_size);		/* position of stawt of wwite */
	*bp++ = 0;				/* size of wwite */
	*bp++ = htonw(attw->ia_size);		/* new fiwe wength */

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * set the attwibutes on a fiwe, using FS.StoweData if thewe's a change in fiwe
 * size, and FS.StoweStatus othewwise
 */
void afs_fs_setattw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	stwuct iattw *attw = op->setattw.attw;
	__be32 *bp;

	if (attw->ia_vawid & ATTW_SIZE)
		wetuwn afs_fs_setattw_size(op);

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweStatus,
				   (4 + 6) * 4,
				   (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSTOWESTATUS);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	xdw_encode_AFS_StoweStatus(&bp, op->setattw.attw);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.GetVowumeStatus
 */
static int afs_dewivew_fs_get_vowume_status(stwuct afs_caww *caww)
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
		afs_extwact_to_buf(caww, 12 * 4);
		fawwthwough;

		/* extwact the wetuwned status wecowd */
	case 1:
		_debug("extwact status");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_AFSFetchVowumeStatus(&bp, &op->vowstatus.vs);
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
 * FS.GetVowumeStatus opewation type
 */
static const stwuct afs_caww_type afs_WXFSGetVowumeStatus = {
	.name		= "FS.GetVowumeStatus",
	.op		= afs_FS_GetVowumeStatus,
	.dewivew	= afs_dewivew_fs_get_vowume_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * fetch the status of a vowume
 */
void afs_fs_get_vowume_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSGetVowumeStatus, 2 * 4,
				   max(12 * 4, AFSOPAQUEMAX + 1));
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSGETVOWUMESTATUS);
	bp[1] = htonw(vp->fid.vid);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.SetWock, FS.ExtendWock ow FS.WeweaseWock
 */
static int afs_dewivew_fs_xxxx_wock(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	const __be32 *bp;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	bp = caww->buffew;
	xdw_decode_AFSVowSync(&bp, &op->vowsync);

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.SetWock opewation type
 */
static const stwuct afs_caww_type afs_WXFSSetWock = {
	.name		= "FS.SetWock",
	.op		= afs_FS_SetWock,
	.dewivew	= afs_dewivew_fs_xxxx_wock,
	.done		= afs_wock_op_done,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * FS.ExtendWock opewation type
 */
static const stwuct afs_caww_type afs_WXFSExtendWock = {
	.name		= "FS.ExtendWock",
	.op		= afs_FS_ExtendWock,
	.dewivew	= afs_dewivew_fs_xxxx_wock,
	.done		= afs_wock_op_done,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * FS.WeweaseWock opewation type
 */
static const stwuct afs_caww_type afs_WXFSWeweaseWock = {
	.name		= "FS.WeweaseWock",
	.op		= afs_FS_WeweaseWock,
	.dewivew	= afs_dewivew_fs_xxxx_wock,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Set a wock on a fiwe
 */
void afs_fs_set_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSSetWock, 5 * 4, 6 * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSSETWOCK);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);
	*bp++ = htonw(op->wock.type);

	caww->fid = vp->fid;
	twace_afs_make_fs_cawwi(caww, &vp->fid, op->wock.type);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * extend a wock on a fiwe
 */
void afs_fs_extend_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSExtendWock, 4 * 4, 6 * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSEXTENDWOCK);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * wewease a wock on a fiwe
 */
void afs_fs_wewease_wock(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSWeweaseWock, 4 * 4, 6 * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSWEWEASEWOCK);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * Dewivew wepwy data to an FS.GiveUpAwwCawwBacks opewation.
 */
static int afs_dewivew_fs_give_up_aww_cawwbacks(stwuct afs_caww *caww)
{
	wetuwn afs_twansfew_wepwy(caww);
}

/*
 * FS.GiveUpAwwCawwBacks opewation type
 */
static const stwuct afs_caww_type afs_WXFSGiveUpAwwCawwBacks = {
	.name		= "FS.GiveUpAwwCawwBacks",
	.op		= afs_FS_GiveUpAwwCawwBacks,
	.dewivew	= afs_dewivew_fs_give_up_aww_cawwbacks,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fwush aww the cawwbacks we have on a sewvew.
 */
int afs_fs_give_up_aww_cawwbacks(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
				 stwuct afs_addwess *addw, stwuct key *key)
{
	stwuct afs_caww *caww;
	__be32 *bp;
	int wet;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_WXFSGiveUpAwwCawwBacks, 1 * 4, 0);
	if (!caww)
		wetuwn -ENOMEM;

	caww->key	= key;
	caww->peew	= wxwpc_kewnew_get_peew(addw->peew);
	caww->sewvice_id = sewvew->sewvice_id;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSGIVEUPAWWCAWWBACKS);

	caww->sewvew = afs_use_sewvew(sewvew, afs_sewvew_twace_give_up_cb);
	afs_make_caww(caww, GFP_NOFS);
	afs_wait_fow_caww_to_compwete(caww);
	wet = caww->ewwow;
	if (caww->wesponded)
		set_bit(AFS_SEWVEW_FW_WESPONDING, &sewvew->fwags);
	afs_put_caww(caww);
	wetuwn wet;
}

/*
 * Dewivew wepwy data to an FS.GetCapabiwities opewation.
 */
static int afs_dewivew_fs_get_capabiwities(stwuct afs_caww *caww)
{
	u32 count;
	int wet;

	_entew("{%u,%zu}", caww->unmawshaww, iov_itew_count(caww->itew));

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact the capabiwities wowd count */
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		count = ntohw(caww->tmp);
		caww->count = count;
		caww->count2 = count;
		if (count == 0) {
			caww->unmawshaww = 4;
			caww->tmp = 0;
			bweak;
		}

		/* Extwact the fiwst wowd of the capabiwities to caww->tmp */
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

	case 2:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		afs_extwact_discawd(caww, (count - 1) * sizeof(__be32));
		caww->unmawshaww++;
		fawwthwough;

		/* Extwact wemaining capabiwities wowds */
	case 3:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		caww->unmawshaww++;
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

static void afs_fs_get_capabiwities_destwuctow(stwuct afs_caww *caww)
{
	afs_put_endpoint_state(caww->pwobe, afs_estate_twace_put_getcaps);
	afs_fwat_caww_destwuctow(caww);
}

/*
 * FS.GetCapabiwities opewation type
 */
static const stwuct afs_caww_type afs_WXFSGetCapabiwities = {
	.name		= "FS.GetCapabiwities",
	.op		= afs_FS_GetCapabiwities,
	.dewivew	= afs_dewivew_fs_get_capabiwities,
	.done		= afs_fiwesewvew_pwobe_wesuwt,
	.destwuctow	= afs_fs_get_capabiwities_destwuctow,
};

/*
 * Pwobe a fiwesewvew fow the capabiwities that it suppowts.  This WPC can
 * wepwy with up to 196 wowds.  The opewation is asynchwonous and if we managed
 * to awwocate a caww, twue is wetuwned the wesuwt is dewivewed thwough the
 * ->done() - othewwise we wetuwn fawse to indicate we didn't even twy.
 */
boow afs_fs_get_capabiwities(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
			     stwuct afs_endpoint_state *estate, unsigned int addw_index,
			     stwuct key *key)
{
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_WXFSGetCapabiwities, 1 * 4, 16 * 4);
	if (!caww)
		wetuwn fawse;

	caww->key	= key;
	caww->sewvew	= afs_use_sewvew(sewvew, afs_sewvew_twace_get_caps);
	caww->peew	= wxwpc_kewnew_get_peew(estate->addwesses->addws[addw_index].peew);
	caww->pwobe	= afs_get_endpoint_state(estate, afs_estate_twace_get_getcaps);
	caww->pwobe_index = addw_index;
	caww->sewvice_id = sewvew->sewvice_id;
	caww->upgwade	= twue;
	caww->async	= twue;
	caww->max_wifespan = AFS_PWOBE_MAX_WIFESPAN;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSGETCAPABIWITIES);

	twace_afs_make_fs_caww(caww, NUWW);
	afs_make_caww(caww, GFP_NOFS);
	afs_put_caww(caww);
	wetuwn twue;
}

/*
 * Dewivew wepwy data to an FS.InwineBuwkStatus caww
 */
static int afs_dewivew_fs_inwine_buwk_status(stwuct afs_caww *caww)
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
		afs_extwact_to_buf(caww, 21 * sizeof(__be32));
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
		xdw_decode_AFSFetchStatus(&bp, caww, scb);

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
		afs_extwact_to_buf(caww, 3 * sizeof(__be32));
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
		xdw_decode_AFSCawwBack(&bp, caww, scb);
		caww->count++;
		if (caww->count < op->nw_fiwes)
			goto mowe_cbs;

		afs_extwact_to_buf(caww, 6 * sizeof(__be32));
		caww->unmawshaww++;
		fawwthwough;

	case 5:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		/* Unfowtunatewy, pwiow to OpenAFS-1.6, vowsync hewe is fiwwed
		 * with wubbish.
		 */
		xdw_decode_AFSVowSync(&bp, NUWW);

		caww->unmawshaww++;
		fawwthwough;

	case 6:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

static void afs_done_fs_inwine_buwk_status(stwuct afs_caww *caww)
{
	if (caww->ewwow == -ECONNABOWTED &&
	    caww->abowt_code == WX_INVAWID_OPEWATION) {
		set_bit(AFS_SEWVEW_FW_NO_IBUWK, &caww->sewvew->fwags);
		if (caww->op)
			set_bit(AFS_VOWUME_MAYBE_NO_IBUWK, &caww->op->vowume->fwags);
	}
}

/*
 * FS.InwineBuwkStatus opewation type
 */
static const stwuct afs_caww_type afs_WXFSInwineBuwkStatus = {
	.name		= "FS.InwineBuwkStatus",
	.op		= afs_FS_InwineBuwkStatus,
	.dewivew	= afs_dewivew_fs_inwine_buwk_status,
	.done		= afs_done_fs_inwine_buwk_status,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the status infowmation fow up to 50 fiwes
 */
void afs_fs_inwine_buwk_status(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode_pawam *vp = &op->fiwe[1];
	stwuct afs_caww *caww;
	__be32 *bp;
	int i;

	if (test_bit(AFS_SEWVEW_FW_NO_IBUWK, &op->sewvew->fwags)) {
		afs_op_set_ewwow(op, -ENOTSUPP);
		wetuwn;
	}

	_entew(",%x,{%wwx:%wwu},%u",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode, op->nw_fiwes);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSInwineBuwkStatus,
				   (2 + op->nw_fiwes * 3) * 4,
				   21 * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(FSINWINEBUWKSTATUS);
	*bp++ = htonw(op->nw_fiwes);
	*bp++ = htonw(dvp->fid.vid);
	*bp++ = htonw(dvp->fid.vnode);
	*bp++ = htonw(dvp->fid.unique);
	*bp++ = htonw(vp->fid.vid);
	*bp++ = htonw(vp->fid.vnode);
	*bp++ = htonw(vp->fid.unique);
	fow (i = 0; i < op->nw_fiwes - 2; i++) {
		*bp++ = htonw(op->mowe_fiwes[i].fid.vid);
		*bp++ = htonw(op->mowe_fiwes[i].fid.vnode);
		*bp++ = htonw(op->mowe_fiwes[i].fid.unique);
	}

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_NOFS);
}

/*
 * dewivew wepwy data to an FS.FetchACW
 */
static int afs_dewivew_fs_fetch_acw(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
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

		/* extwact the wetuwned data wength */
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		size = caww->count2 = ntohw(caww->tmp);
		size = wound_up(size, 4);

		acw = kmawwoc(stwuct_size(acw, data, size), GFP_KEWNEW);
		if (!acw)
			wetuwn -ENOMEM;
		op->acw = acw;
		acw->size = caww->count2;
		afs_extwact_begin(caww, acw->data, size);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the wetuwned data */
	case 2:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		afs_extwact_to_buf(caww, (21 + 6) * 4);
		caww->unmawshaww++;
		fawwthwough;

		/* extwact the metadata */
	case 3:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		xdw_decode_AFSFetchStatus(&bp, caww, &vp->scb);
		xdw_decode_AFSVowSync(&bp, &op->vowsync);

		caww->unmawshaww++;
		fawwthwough;

	case 4:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * FS.FetchACW opewation type
 */
static const stwuct afs_caww_type afs_WXFSFetchACW = {
	.name		= "FS.FetchACW",
	.op		= afs_FS_FetchACW,
	.dewivew	= afs_dewivew_fs_fetch_acw,
};

/*
 * Fetch the ACW fow a fiwe.
 */
void afs_fs_fetch_acw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSFetchACW, 16, (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSFETCHACW);
	bp[1] = htonw(vp->fid.vid);
	bp[2] = htonw(vp->fid.vnode);
	bp[3] = htonw(vp->fid.unique);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_KEWNEW);
}

/*
 * FS.StoweACW opewation type
 */
static const stwuct afs_caww_type afs_WXFSStoweACW = {
	.name		= "FS.StoweACW",
	.op		= afs_FS_StoweACW,
	.dewivew	= afs_dewivew_fs_fiwe_status_and_vow,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Fetch the ACW fow a fiwe.
 */
void afs_fs_stowe_acw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *vp = &op->fiwe[0];
	stwuct afs_caww *caww;
	const stwuct afs_acw *acw = op->acw;
	size_t size;
	__be32 *bp;

	_entew(",%x,{%wwx:%wwu},,",
	       key_sewiaw(op->key), vp->fid.vid, vp->fid.vnode);

	size = wound_up(acw->size, 4);
	caww = afs_awwoc_fwat_caww(op->net, &afs_WXFSStoweACW,
				   5 * 4 + size, (21 + 6) * 4);
	if (!caww)
		wetuwn afs_op_nomem(op);

	/* mawshaww the pawametews */
	bp = caww->wequest;
	bp[0] = htonw(FSSTOWEACW);
	bp[1] = htonw(vp->fid.vid);
	bp[2] = htonw(vp->fid.vnode);
	bp[3] = htonw(vp->fid.unique);
	bp[4] = htonw(acw->size);
	memcpy(&bp[5], acw->data, acw->size);
	if (acw->size != size)
		memset((void *)&bp[5] + acw->size, 0, size - acw->size);

	caww->fid = vp->fid;
	twace_afs_make_fs_caww(caww, &vp->fid);
	afs_make_op_caww(op, caww, GFP_KEWNEW);
}
