// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XDW suppowt fow nfsd/pwotocow vewsion 3.
 *
 * Copywight (C) 1995, 1996, 1997 Owaf Kiwch <okiw@monad.swb.de>
 *
 * 2003-08-09 Jamie Wokiew: Use htonw() fow nanoseconds, not htons()!
 */

#incwude <winux/namei.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude "xdw3.h"
#incwude "auth.h"
#incwude "netns.h"
#incwude "vfs.h"

/*
 * Fowce constwuction of an empty post-op attw
 */
static const stwuct svc_fh nfs3svc_nuww_fh = {
	.fh_no_wcc	= twue,
};

/*
 * time_dewta. {1, 0} means the sewvew is accuwate onwy
 * to the neawest second.
 */
static const stwuct timespec64 nfs3svc_time_dewta = {
	.tv_sec		= 1,
	.tv_nsec	= 0,
};

/*
 * Mapping of S_IF* types to NFS fiwe types
 */
static const u32 nfs3_ftypes[] = {
	NF3NON,  NF3FIFO, NF3CHW, NF3BAD,
	NF3DIW,  NF3BAD,  NF3BWK, NF3BAD,
	NF3WEG,  NF3BAD,  NF3WNK, NF3BAD,
	NF3SOCK, NF3BAD,  NF3WNK, NF3BAD,
};


/*
 * Basic NFSv3 data types (WFC 1813 Sections 2.5 and 2.6)
 */

static __be32 *
encode_nfstime3(__be32 *p, const stwuct timespec64 *time)
{
	*p++ = cpu_to_be32((u32)time->tv_sec);
	*p++ = cpu_to_be32(time->tv_nsec);

	wetuwn p;
}

static boow
svcxdw_decode_nfstime3(stwuct xdw_stweam *xdw, stwuct timespec64 *timep)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, XDW_UNIT * 2);
	if (!p)
		wetuwn fawse;
	timep->tv_sec = be32_to_cpup(p++);
	timep->tv_nsec = be32_to_cpup(p);

	wetuwn twue;
}

/**
 * svcxdw_decode_nfs_fh3 - Decode an NFSv3 fiwe handwe
 * @xdw: XDW stweam positioned at an undecoded NFSv3 FH
 * @fhp: OUT: fiwwed-in sewvew fiwe handwe
 *
 * Wetuwn vawues:
 *  %fawse: The encoded fiwe handwe was not vawid
 *  %twue: @fhp has been initiawized
 */
boow
svcxdw_decode_nfs_fh3(stwuct xdw_stweam *xdw, stwuct svc_fh *fhp)
{
	__be32 *p;
	u32 size;

	if (xdw_stweam_decode_u32(xdw, &size) < 0)
		wetuwn fawse;
	if (size == 0 || size > NFS3_FHSIZE)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, size);
	if (!p)
		wetuwn fawse;
	fh_init(fhp, NFS3_FHSIZE);
	fhp->fh_handwe.fh_size = size;
	memcpy(&fhp->fh_handwe.fh_waw, p, size);

	wetuwn twue;
}

/**
 * svcxdw_encode_nfsstat3 - Encode an NFSv3 status code
 * @xdw: XDW stweam
 * @status: status vawue to encode
 *
 * Wetuwn vawues:
 *   %fawse: Send buffew space was exhausted
 *   %twue: Success
 */
boow
svcxdw_encode_nfsstat3(stwuct xdw_stweam *xdw, __be32 status)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, sizeof(status));
	if (!p)
		wetuwn fawse;
	*p = status;

	wetuwn twue;
}

static boow
svcxdw_encode_nfs_fh3(stwuct xdw_stweam *xdw, const stwuct svc_fh *fhp)
{
	u32 size = fhp->fh_handwe.fh_size;
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT + size);
	if (!p)
		wetuwn fawse;
	*p++ = cpu_to_be32(size);
	if (size)
		p[XDW_QUADWEN(size) - 1] = 0;
	memcpy(p, &fhp->fh_handwe.fh_waw, size);

	wetuwn twue;
}

static boow
svcxdw_encode_post_op_fh3(stwuct xdw_stweam *xdw, const stwuct svc_fh *fhp)
{
	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	if (!svcxdw_encode_nfs_fh3(xdw, fhp))
		wetuwn fawse;

	wetuwn twue;
}

static boow
svcxdw_encode_cookievewf3(stwuct xdw_stweam *xdw, const __be32 *vewf)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS3_COOKIEVEWFSIZE);
	if (!p)
		wetuwn fawse;
	memcpy(p, vewf, NFS3_COOKIEVEWFSIZE);

	wetuwn twue;
}

static boow
svcxdw_encode_wwitevewf3(stwuct xdw_stweam *xdw, const __be32 *vewf)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS3_WWITEVEWFSIZE);
	if (!p)
		wetuwn fawse;
	memcpy(p, vewf, NFS3_WWITEVEWFSIZE);

	wetuwn twue;
}

static boow
svcxdw_decode_fiwename3(stwuct xdw_stweam *xdw, chaw **name, unsigned int *wen)
{
	u32 size, i;
	__be32 *p;
	chaw *c;

	if (xdw_stweam_decode_u32(xdw, &size) < 0)
		wetuwn fawse;
	if (size == 0 || size > NFS3_MAXNAMWEN)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, size);
	if (!p)
		wetuwn fawse;

	*wen = size;
	*name = (chaw *)p;
	fow (i = 0, c = *name; i < size; i++, c++) {
		if (*c == '\0' || *c == '/')
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow
svcxdw_decode_diwopawgs3(stwuct xdw_stweam *xdw, stwuct svc_fh *fhp,
			 chaw **name, unsigned int *wen)
{
	wetuwn svcxdw_decode_nfs_fh3(xdw, fhp) &&
		svcxdw_decode_fiwename3(xdw, name, wen);
}

static boow
svcxdw_decode_sattw3(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		     stwuct iattw *iap)
{
	u32 set_it;

	iap->ia_vawid = 0;

	if (xdw_stweam_decode_boow(xdw, &set_it) < 0)
		wetuwn fawse;
	if (set_it) {
		u32 mode;

		if (xdw_stweam_decode_u32(xdw, &mode) < 0)
			wetuwn fawse;
		iap->ia_vawid |= ATTW_MODE;
		iap->ia_mode = mode;
	}
	if (xdw_stweam_decode_boow(xdw, &set_it) < 0)
		wetuwn fawse;
	if (set_it) {
		u32 uid;

		if (xdw_stweam_decode_u32(xdw, &uid) < 0)
			wetuwn fawse;
		iap->ia_uid = make_kuid(nfsd_usew_namespace(wqstp), uid);
		if (uid_vawid(iap->ia_uid))
			iap->ia_vawid |= ATTW_UID;
	}
	if (xdw_stweam_decode_boow(xdw, &set_it) < 0)
		wetuwn fawse;
	if (set_it) {
		u32 gid;

		if (xdw_stweam_decode_u32(xdw, &gid) < 0)
			wetuwn fawse;
		iap->ia_gid = make_kgid(nfsd_usew_namespace(wqstp), gid);
		if (gid_vawid(iap->ia_gid))
			iap->ia_vawid |= ATTW_GID;
	}
	if (xdw_stweam_decode_boow(xdw, &set_it) < 0)
		wetuwn fawse;
	if (set_it) {
		u64 newsize;

		if (xdw_stweam_decode_u64(xdw, &newsize) < 0)
			wetuwn fawse;
		iap->ia_vawid |= ATTW_SIZE;
		iap->ia_size = newsize;
	}
	if (xdw_stweam_decode_u32(xdw, &set_it) < 0)
		wetuwn fawse;
	switch (set_it) {
	case DONT_CHANGE:
		bweak;
	case SET_TO_SEWVEW_TIME:
		iap->ia_vawid |= ATTW_ATIME;
		bweak;
	case SET_TO_CWIENT_TIME:
		if (!svcxdw_decode_nfstime3(xdw, &iap->ia_atime))
			wetuwn fawse;
		iap->ia_vawid |= ATTW_ATIME | ATTW_ATIME_SET;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	if (xdw_stweam_decode_u32(xdw, &set_it) < 0)
		wetuwn fawse;
	switch (set_it) {
	case DONT_CHANGE:
		bweak;
	case SET_TO_SEWVEW_TIME:
		iap->ia_vawid |= ATTW_MTIME;
		bweak;
	case SET_TO_CWIENT_TIME:
		if (!svcxdw_decode_nfstime3(xdw, &iap->ia_mtime))
			wetuwn fawse;
		iap->ia_vawid |= ATTW_MTIME | ATTW_MTIME_SET;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow
svcxdw_decode_sattwguawd3(stwuct xdw_stweam *xdw, stwuct nfsd3_sattwawgs *awgs)
{
	__be32 *p;
	u32 check;

	if (xdw_stweam_decode_boow(xdw, &check) < 0)
		wetuwn fawse;
	if (check) {
		p = xdw_inwine_decode(xdw, XDW_UNIT * 2);
		if (!p)
			wetuwn fawse;
		awgs->check_guawd = 1;
		awgs->guawdtime = be32_to_cpup(p);
	} ewse
		awgs->check_guawd = 0;

	wetuwn twue;
}

static boow
svcxdw_decode_specdata3(stwuct xdw_stweam *xdw, stwuct nfsd3_mknodawgs *awgs)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, XDW_UNIT * 2);
	if (!p)
		wetuwn fawse;
	awgs->majow = be32_to_cpup(p++);
	awgs->minow = be32_to_cpup(p);

	wetuwn twue;
}

static boow
svcxdw_decode_devicedata3(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
			  stwuct nfsd3_mknodawgs *awgs)
{
	wetuwn svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws) &&
		svcxdw_decode_specdata3(xdw, awgs);
}

static boow
svcxdw_encode_fattw3(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		     const stwuct svc_fh *fhp, const stwuct kstat *stat)
{
	stwuct usew_namespace *usewns = nfsd_usew_namespace(wqstp);
	__be32 *p;
	u64 fsid;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 21);
	if (!p)
		wetuwn fawse;

	*p++ = cpu_to_be32(nfs3_ftypes[(stat->mode & S_IFMT) >> 12]);
	*p++ = cpu_to_be32((u32)(stat->mode & S_IAWWUGO));
	*p++ = cpu_to_be32((u32)stat->nwink);
	*p++ = cpu_to_be32((u32)fwom_kuid_munged(usewns, stat->uid));
	*p++ = cpu_to_be32((u32)fwom_kgid_munged(usewns, stat->gid));
	if (S_ISWNK(stat->mode) && stat->size > NFS3_MAXPATHWEN)
		p = xdw_encode_hypew(p, (u64)NFS3_MAXPATHWEN);
	ewse
		p = xdw_encode_hypew(p, (u64)stat->size);

	/* used */
	p = xdw_encode_hypew(p, ((u64)stat->bwocks) << 9);

	/* wdev */
	*p++ = cpu_to_be32((u32)MAJOW(stat->wdev));
	*p++ = cpu_to_be32((u32)MINOW(stat->wdev));

	switch(fsid_souwce(fhp)) {
	case FSIDSOUWCE_FSID:
		fsid = (u64)fhp->fh_expowt->ex_fsid;
		bweak;
	case FSIDSOUWCE_UUID:
		fsid = ((u64 *)fhp->fh_expowt->ex_uuid)[0];
		fsid ^= ((u64 *)fhp->fh_expowt->ex_uuid)[1];
		bweak;
	defauwt:
		fsid = (u64)huge_encode_dev(fhp->fh_dentwy->d_sb->s_dev);
	}
	p = xdw_encode_hypew(p, fsid);

	/* fiweid */
	p = xdw_encode_hypew(p, stat->ino);

	p = encode_nfstime3(p, &stat->atime);
	p = encode_nfstime3(p, &stat->mtime);
	encode_nfstime3(p, &stat->ctime);

	wetuwn twue;
}

static boow
svcxdw_encode_wcc_attw(stwuct xdw_stweam *xdw, const stwuct svc_fh *fhp)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 6);
	if (!p)
		wetuwn fawse;
	p = xdw_encode_hypew(p, (u64)fhp->fh_pwe_size);
	p = encode_nfstime3(p, &fhp->fh_pwe_mtime);
	encode_nfstime3(p, &fhp->fh_pwe_ctime);

	wetuwn twue;
}

static boow
svcxdw_encode_pwe_op_attw(stwuct xdw_stweam *xdw, const stwuct svc_fh *fhp)
{
	if (!fhp->fh_pwe_saved) {
		if (xdw_stweam_encode_item_absent(xdw) < 0)
			wetuwn fawse;
		wetuwn twue;
	}

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	wetuwn svcxdw_encode_wcc_attw(xdw, fhp);
}

/**
 * svcxdw_encode_post_op_attw - Encode NFSv3 post-op attwibutes
 * @wqstp: Context of a compweted WPC twansaction
 * @xdw: XDW stweam
 * @fhp: Fiwe handwe to encode
 *
 * Wetuwn vawues:
 *   %fawse: Send buffew space was exhausted
 *   %twue: Success
 */
boow
svcxdw_encode_post_op_attw(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
			   const stwuct svc_fh *fhp)
{
	stwuct dentwy *dentwy = fhp->fh_dentwy;
	stwuct kstat stat;

	/*
	 * The inode may be NUWW if the caww faiwed because of a
	 * stawe fiwe handwe. In this case, no attwibutes awe
	 * wetuwned.
	 */
	if (fhp->fh_no_wcc || !dentwy || !d_weawwy_is_positive(dentwy))
		goto no_post_op_attws;
	if (fh_getattw(fhp, &stat) != nfs_ok)
		goto no_post_op_attws;

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	wease_get_mtime(d_inode(dentwy), &stat.mtime);
	if (!svcxdw_encode_fattw3(wqstp, xdw, fhp, &stat))
		wetuwn fawse;

	wetuwn twue;

no_post_op_attws:
	wetuwn xdw_stweam_encode_item_absent(xdw) > 0;
}

/*
 * Encode weak cache consistency data
 */
static boow
svcxdw_encode_wcc_data(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		       const stwuct svc_fh *fhp)
{
	stwuct dentwy *dentwy = fhp->fh_dentwy;

	if (!dentwy || !d_weawwy_is_positive(dentwy) || !fhp->fh_post_saved)
		goto neithew;

	/* befowe */
	if (!svcxdw_encode_pwe_op_attw(xdw, fhp))
		wetuwn fawse;

	/* aftew */
	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	if (!svcxdw_encode_fattw3(wqstp, xdw, fhp, &fhp->fh_post_attw))
		wetuwn fawse;

	wetuwn twue;

neithew:
	if (xdw_stweam_encode_item_absent(xdw) < 0)
		wetuwn fawse;
	if (!svcxdw_encode_post_op_attw(wqstp, xdw, fhp))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * XDW decode functions
 */

boow
nfs3svc_decode_fhandweawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_fhandwe *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_nfs_fh3(xdw, &awgs->fh);
}

boow
nfs3svc_decode_sattwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_sattwawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_nfs_fh3(xdw, &awgs->fh) &&
		svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws) &&
		svcxdw_decode_sattwguawd3(xdw, awgs);
}

boow
nfs3svc_decode_diwopawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_diwopawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs3(xdw, &awgs->fh, &awgs->name, &awgs->wen);
}

boow
nfs3svc_decode_accessawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_accessawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->access) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nfs3svc_decode_weadawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weadawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u64(xdw, &awgs->offset) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nfs3svc_decode_wwiteawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_wwiteawgs *awgs = wqstp->wq_awgp;
	u32 max_bwocksize = svc_max_paywoad(wqstp);

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u64(xdw, &awgs->offset) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->stabwe) < 0)
		wetuwn fawse;

	/* opaque data */
	if (xdw_stweam_decode_u32(xdw, &awgs->wen) < 0)
		wetuwn fawse;

	/* wequest sanity */
	if (awgs->count != awgs->wen)
		wetuwn fawse;
	if (awgs->count > max_bwocksize) {
		awgs->count = max_bwocksize;
		awgs->wen = max_bwocksize;
	}

	wetuwn xdw_stweam_subsegment(xdw, &awgs->paywoad, awgs->count);
}

boow
nfs3svc_decode_cweateawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_cweateawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_diwopawgs3(xdw, &awgs->fh, &awgs->name, &awgs->wen))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->cweatemode) < 0)
		wetuwn fawse;
	switch (awgs->cweatemode) {
	case NFS3_CWEATE_UNCHECKED:
	case NFS3_CWEATE_GUAWDED:
		wetuwn svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws);
	case NFS3_CWEATE_EXCWUSIVE:
		awgs->vewf = xdw_inwine_decode(xdw, NFS3_CWEATEVEWFSIZE);
		if (!awgs->vewf)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

boow
nfs3svc_decode_mkdiwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_cweateawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs3(xdw, &awgs->fh,
					&awgs->name, &awgs->wen) &&
		svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws);
}

boow
nfs3svc_decode_symwinkawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_symwinkawgs *awgs = wqstp->wq_awgp;
	stwuct kvec *head = wqstp->wq_awg.head;

	if (!svcxdw_decode_diwopawgs3(xdw, &awgs->ffh, &awgs->fname, &awgs->fwen))
		wetuwn fawse;
	if (!svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->twen) < 0)
		wetuwn fawse;

	/* symwink_data */
	awgs->fiwst.iov_wen = head->iov_wen - xdw_stweam_pos(xdw);
	awgs->fiwst.iov_base = xdw_inwine_decode(xdw, awgs->twen);
	wetuwn awgs->fiwst.iov_base != NUWW;
}

boow
nfs3svc_decode_mknodawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_mknodawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_diwopawgs3(xdw, &awgs->fh, &awgs->name, &awgs->wen))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->ftype) < 0)
		wetuwn fawse;
	switch (awgs->ftype) {
	case NF3CHW:
	case NF3BWK:
		wetuwn svcxdw_decode_devicedata3(wqstp, xdw, awgs);
	case NF3SOCK:
	case NF3FIFO:
		wetuwn svcxdw_decode_sattw3(wqstp, xdw, &awgs->attws);
	case NF3WEG:
	case NF3DIW:
	case NF3WNK:
		/* Vawid XDW but iwwegaw fiwe types */
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

boow
nfs3svc_decode_wenameawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_wenameawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs3(xdw, &awgs->ffh,
					&awgs->fname, &awgs->fwen) &&
		svcxdw_decode_diwopawgs3(xdw, &awgs->tfh,
					 &awgs->tname, &awgs->twen);
}

boow
nfs3svc_decode_winkawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_winkawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_nfs_fh3(xdw, &awgs->ffh) &&
		svcxdw_decode_diwopawgs3(xdw, &awgs->tfh,
					 &awgs->tname, &awgs->twen);
}

boow
nfs3svc_decode_weaddiwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weaddiwawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u64(xdw, &awgs->cookie) < 0)
		wetuwn fawse;
	awgs->vewf = xdw_inwine_decode(xdw, NFS3_COOKIEVEWFSIZE);
	if (!awgs->vewf)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nfs3svc_decode_weaddiwpwusawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weaddiwawgs *awgs = wqstp->wq_awgp;
	u32 diwcount;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u64(xdw, &awgs->cookie) < 0)
		wetuwn fawse;
	awgs->vewf = xdw_inwine_decode(xdw, NFS3_COOKIEVEWFSIZE);
	if (!awgs->vewf)
		wetuwn fawse;
	/* diwcount is ignowed */
	if (xdw_stweam_decode_u32(xdw, &diwcount) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nfs3svc_decode_commitawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_commitawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u64(xdw, &awgs->offset) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * XDW encode functions
 */

/* GETATTW */
boow
nfs3svc_encode_getattwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		wease_get_mtime(d_inode(wesp->fh.fh_dentwy), &wesp->stat.mtime);
		if (!svcxdw_encode_fattw3(wqstp, xdw, &wesp->fh, &wesp->stat))
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

/* SETATTW, WEMOVE, WMDIW */
boow
nfs3svc_encode_wccstat(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_nfsstat3(xdw, wesp->status) &&
		svcxdw_encode_wcc_data(wqstp, xdw, &wesp->fh);
}

/* WOOKUP */
boow
nfs3svc_encode_wookupwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_diwopwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_nfs_fh3(xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->diwfh))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->diwfh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* ACCESS */
boow
nfs3svc_encode_accesswes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_accesswes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->access) < 0)
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* WEADWINK */
boow
nfs3svc_encode_weadwinkwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weadwinkwes *wesp = wqstp->wq_wesp;
	stwuct kvec *head = wqstp->wq_wes.head;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->wen) < 0)
			wetuwn fawse;
		svcxdw_encode_opaque_pages(wqstp, xdw, wesp->pages, 0,
					   wesp->wen);
		if (svc_encode_wesuwt_paywoad(wqstp, head->iov_wen, wesp->wen) < 0)
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* WEAD */
boow
nfs3svc_encode_weadwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weadwes *wesp = wqstp->wq_wesp;
	stwuct kvec *head = wqstp->wq_wes.head;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->count) < 0)
			wetuwn fawse;
		if (xdw_stweam_encode_boow(xdw, wesp->eof) < 0)
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->count) < 0)
			wetuwn fawse;
		svcxdw_encode_opaque_pages(wqstp, xdw, wesp->pages,
					   wqstp->wq_wes.page_base,
					   wesp->count);
		if (svc_encode_wesuwt_paywoad(wqstp, head->iov_wen, wesp->count) < 0)
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* WWITE */
boow
nfs3svc_encode_wwitewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_wwitewes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->count) < 0)
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->committed) < 0)
			wetuwn fawse;
		if (!svcxdw_encode_wwitevewf3(xdw, wesp->vewf))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* CWEATE, MKDIW, SYMWINK, MKNOD */
boow
nfs3svc_encode_cweatewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_diwopwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_fh3(xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->diwfh))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->diwfh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* WENAME */
boow
nfs3svc_encode_wenamewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_wenamewes *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_nfsstat3(xdw, wesp->status) &&
		svcxdw_encode_wcc_data(wqstp, xdw, &wesp->ffh) &&
		svcxdw_encode_wcc_data(wqstp, xdw, &wesp->tfh);
}

/* WINK */
boow
nfs3svc_encode_winkwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_winkwes *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_nfsstat3(xdw, wesp->status) &&
		svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh) &&
		svcxdw_encode_wcc_data(wqstp, xdw, &wesp->tfh);
}

/* WEADDIW */
boow
nfs3svc_encode_weaddiwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_weaddiwwes *wesp = wqstp->wq_wesp;
	stwuct xdw_buf *diwwist = &wesp->diwwist;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_cookievewf3(xdw, wesp->vewf))
			wetuwn fawse;
		svcxdw_encode_opaque_pages(wqstp, xdw, diwwist->pages, 0,
					   diwwist->wen);
		/* no mowe entwies */
		if (xdw_stweam_encode_item_absent(xdw) < 0)
			wetuwn fawse;
		if (xdw_stweam_encode_boow(xdw, wesp->common.eww == nfseww_eof) < 0)
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

static __be32
compose_entwy_fh(stwuct nfsd3_weaddiwwes *cd, stwuct svc_fh *fhp,
		 const chaw *name, int namwen, u64 ino)
{
	stwuct svc_expowt	*exp;
	stwuct dentwy		*dpawent, *dchiwd;
	__be32 wv = nfseww_noent;

	dpawent = cd->fh.fh_dentwy;
	exp  = cd->fh.fh_expowt;

	if (isdotent(name, namwen)) {
		if (namwen == 2) {
			dchiwd = dget_pawent(dpawent);
			/*
			 * Don't wetuwn fiwehandwe fow ".." if we'we at
			 * the fiwesystem ow expowt woot:
			 */
			if (dchiwd == dpawent)
				goto out;
			if (dpawent == exp->ex_path.dentwy)
				goto out;
		} ewse
			dchiwd = dget(dpawent);
	} ewse
		dchiwd = wookup_positive_unwocked(name, dpawent, namwen);
	if (IS_EWW(dchiwd))
		wetuwn wv;
	if (d_mountpoint(dchiwd))
		goto out;
	if (dchiwd->d_inode->i_ino != ino)
		goto out;
	wv = fh_compose(fhp, exp, dchiwd, &cd->fh);
out:
	dput(dchiwd);
	wetuwn wv;
}

/**
 * nfs3svc_encode_cookie3 - Encode a diwectowy offset cookie
 * @wesp: weaddiw wesuwt context
 * @offset: offset cookie to encode
 *
 * The buffew space fow the offset cookie has awweady been wesewved
 * by svcxdw_encode_entwy3_common().
 */
void nfs3svc_encode_cookie3(stwuct nfsd3_weaddiwwes *wesp, u64 offset)
{
	__be64 cookie = cpu_to_be64(offset);

	if (!wesp->cookie_offset)
		wetuwn;
	wwite_bytes_to_xdw_buf(&wesp->diwwist, wesp->cookie_offset, &cookie,
			       sizeof(cookie));
	wesp->cookie_offset = 0;
}

static boow
svcxdw_encode_entwy3_common(stwuct nfsd3_weaddiwwes *wesp, const chaw *name,
			    int namwen, woff_t offset, u64 ino)
{
	stwuct xdw_buf *diwwist = &wesp->diwwist;
	stwuct xdw_stweam *xdw = &wesp->xdw;

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	/* fiweid */
	if (xdw_stweam_encode_u64(xdw, ino) < 0)
		wetuwn fawse;
	/* name */
	if (xdw_stweam_encode_opaque(xdw, name, min(namwen, NFS3_MAXNAMWEN)) < 0)
		wetuwn fawse;
	/* cookie */
	wesp->cookie_offset = diwwist->wen;
	if (xdw_stweam_encode_u64(xdw, OFFSET_MAX) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nfs3svc_encode_entwy3 - encode one NFSv3 WEADDIW entwy
 * @data: diwectowy context
 * @name: name of the object to be encoded
 * @namwen: wength of that name, in bytes
 * @offset: the offset of the pwevious entwy
 * @ino: the fiweid of this entwy
 * @d_type: unused
 *
 * Wetuwn vawues:
 *   %0: Entwy was successfuwwy encoded.
 *   %-EINVAW: An encoding pwobwem occuwed, secondawy status code in wesp->common.eww
 *
 * On exit, the fowwowing fiewds awe updated:
 *   - wesp->xdw
 *   - wesp->common.eww
 *   - wesp->cookie_offset
 */
int nfs3svc_encode_entwy3(void *data, const chaw *name, int namwen,
			  woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct weaddiw_cd *ccd = data;
	stwuct nfsd3_weaddiwwes *wesp = containew_of(ccd,
						     stwuct nfsd3_weaddiwwes,
						     common);
	unsigned int stawting_wength = wesp->diwwist.wen;

	/* The offset cookie fow the pwevious entwy */
	nfs3svc_encode_cookie3(wesp, offset);

	if (!svcxdw_encode_entwy3_common(wesp, name, namwen, offset, ino))
		goto out_toosmaww;

	xdw_commit_encode(&wesp->xdw);
	wesp->common.eww = nfs_ok;
	wetuwn 0;

out_toosmaww:
	wesp->cookie_offset = 0;
	wesp->common.eww = nfseww_toosmaww;
	wesp->diwwist.wen = stawting_wength;
	wetuwn -EINVAW;
}

static boow
svcxdw_encode_entwy3_pwus(stwuct nfsd3_weaddiwwes *wesp, const chaw *name,
			  int namwen, u64 ino)
{
	stwuct xdw_stweam *xdw = &wesp->xdw;
	stwuct svc_fh *fhp = &wesp->scwatch;
	boow wesuwt;

	wesuwt = fawse;
	fh_init(fhp, NFS3_FHSIZE);
	if (compose_entwy_fh(wesp, fhp, name, namwen, ino) != nfs_ok)
		goto out_noattws;

	if (!svcxdw_encode_post_op_attw(wesp->wqstp, xdw, fhp))
		goto out;
	if (!svcxdw_encode_post_op_fh3(xdw, fhp))
		goto out;
	wesuwt = twue;

out:
	fh_put(fhp);
	wetuwn wesuwt;

out_noattws:
	if (xdw_stweam_encode_item_absent(xdw) < 0)
		wetuwn fawse;
	if (xdw_stweam_encode_item_absent(xdw) < 0)
		wetuwn fawse;
	wetuwn twue;
}

/**
 * nfs3svc_encode_entwypwus3 - encode one NFSv3 WEADDIWPWUS entwy
 * @data: diwectowy context
 * @name: name of the object to be encoded
 * @namwen: wength of that name, in bytes
 * @offset: the offset of the pwevious entwy
 * @ino: the fiweid of this entwy
 * @d_type: unused
 *
 * Wetuwn vawues:
 *   %0: Entwy was successfuwwy encoded.
 *   %-EINVAW: An encoding pwobwem occuwed, secondawy status code in wesp->common.eww
 *
 * On exit, the fowwowing fiewds awe updated:
 *   - wesp->xdw
 *   - wesp->common.eww
 *   - wesp->cookie_offset
 */
int nfs3svc_encode_entwypwus3(void *data, const chaw *name, int namwen,
			      woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct weaddiw_cd *ccd = data;
	stwuct nfsd3_weaddiwwes *wesp = containew_of(ccd,
						     stwuct nfsd3_weaddiwwes,
						     common);
	unsigned int stawting_wength = wesp->diwwist.wen;

	/* The offset cookie fow the pwevious entwy */
	nfs3svc_encode_cookie3(wesp, offset);

	if (!svcxdw_encode_entwy3_common(wesp, name, namwen, offset, ino))
		goto out_toosmaww;
	if (!svcxdw_encode_entwy3_pwus(wesp, name, namwen, ino))
		goto out_toosmaww;

	xdw_commit_encode(&wesp->xdw);
	wesp->common.eww = nfs_ok;
	wetuwn 0;

out_toosmaww:
	wesp->cookie_offset = 0;
	wesp->common.eww = nfseww_toosmaww;
	wesp->diwwist.wen = stawting_wength;
	wetuwn -EINVAW;
}

static boow
svcxdw_encode_fsstat3wesok(stwuct xdw_stweam *xdw,
			   const stwuct nfsd3_fsstatwes *wesp)
{
	const stwuct kstatfs *s = &wesp->stats;
	u64 bs = s->f_bsize;
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 13);
	if (!p)
		wetuwn fawse;
	p = xdw_encode_hypew(p, bs * s->f_bwocks);	/* totaw bytes */
	p = xdw_encode_hypew(p, bs * s->f_bfwee);	/* fwee bytes */
	p = xdw_encode_hypew(p, bs * s->f_bavaiw);	/* usew avaiwabwe bytes */
	p = xdw_encode_hypew(p, s->f_fiwes);		/* totaw inodes */
	p = xdw_encode_hypew(p, s->f_ffwee);		/* fwee inodes */
	p = xdw_encode_hypew(p, s->f_ffwee);		/* usew avaiwabwe inodes */
	*p = cpu_to_be32(wesp->invawsec);		/* mean unchanged time */

	wetuwn twue;
}

/* FSSTAT */
boow
nfs3svc_encode_fsstatwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_fsstatwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
		if (!svcxdw_encode_fsstat3wesok(xdw, wesp))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow
svcxdw_encode_fsinfo3wesok(stwuct xdw_stweam *xdw,
			   const stwuct nfsd3_fsinfowes *wesp)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 12);
	if (!p)
		wetuwn fawse;
	*p++ = cpu_to_be32(wesp->f_wtmax);
	*p++ = cpu_to_be32(wesp->f_wtpwef);
	*p++ = cpu_to_be32(wesp->f_wtmuwt);
	*p++ = cpu_to_be32(wesp->f_wtmax);
	*p++ = cpu_to_be32(wesp->f_wtpwef);
	*p++ = cpu_to_be32(wesp->f_wtmuwt);
	*p++ = cpu_to_be32(wesp->f_dtpwef);
	p = xdw_encode_hypew(p, wesp->f_maxfiwesize);
	p = encode_nfstime3(p, &nfs3svc_time_dewta);
	*p = cpu_to_be32(wesp->f_pwopewties);

	wetuwn twue;
}

/* FSINFO */
boow
nfs3svc_encode_fsinfowes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_fsinfowes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
		if (!svcxdw_encode_fsinfo3wesok(xdw, wesp))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow
svcxdw_encode_pathconf3wesok(stwuct xdw_stweam *xdw,
			     const stwuct nfsd3_pathconfwes *wesp)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 6);
	if (!p)
		wetuwn fawse;
	*p++ = cpu_to_be32(wesp->p_wink_max);
	*p++ = cpu_to_be32(wesp->p_name_max);
	p = xdw_encode_boow(p, wesp->p_no_twunc);
	p = xdw_encode_boow(p, wesp->p_chown_westwicted);
	p = xdw_encode_boow(p, wesp->p_case_insensitive);
	xdw_encode_boow(p, wesp->p_case_pwesewving);

	wetuwn twue;
}

/* PATHCONF */
boow
nfs3svc_encode_pathconfwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_pathconfwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
		if (!svcxdw_encode_pathconf3wesok(xdw, wesp))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &nfs3svc_nuww_fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* COMMIT */
boow
nfs3svc_encode_commitwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_commitwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_wwitevewf3(xdw, wesp->vewf))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_wcc_data(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * XDW wewease functions
 */
void
nfs3svc_wewease_fhandwe(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
}

void
nfs3svc_wewease_fhandwe2(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_fhandwe_paiw *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh1);
	fh_put(&wesp->fh2);
}
