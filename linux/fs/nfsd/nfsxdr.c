// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XDW suppowt fow nfsd
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude "vfs.h"
#incwude "xdw.h"
#incwude "auth.h"

/*
 * Mapping of S_IF* types to NFS fiwe types
 */
static const u32 nfs_ftypes[] = {
	NFNON,  NFCHW,  NFCHW, NFBAD,
	NFDIW,  NFBAD,  NFBWK, NFBAD,
	NFWEG,  NFBAD,  NFWNK, NFBAD,
	NFSOCK, NFBAD,  NFWNK, NFBAD,
};


/*
 * Basic NFSv2 data types (WFC 1094 Section 2.3)
 */

/**
 * svcxdw_encode_stat - Encode an NFSv2 status code
 * @xdw: XDW stweam
 * @status: status vawue to encode
 *
 * Wetuwn vawues:
 *   %fawse: Send buffew space was exhausted
 *   %twue: Success
 */
boow
svcxdw_encode_stat(stwuct xdw_stweam *xdw, __be32 status)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, sizeof(status));
	if (!p)
		wetuwn fawse;
	*p = status;

	wetuwn twue;
}

/**
 * svcxdw_decode_fhandwe - Decode an NFSv2 fiwe handwe
 * @xdw: XDW stweam positioned at an encoded NFSv2 FH
 * @fhp: OUT: fiwwed-in sewvew fiwe handwe
 *
 * Wetuwn vawues:
 *  %fawse: The encoded fiwe handwe was not vawid
 *  %twue: @fhp has been initiawized
 */
boow
svcxdw_decode_fhandwe(stwuct xdw_stweam *xdw, stwuct svc_fh *fhp)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS_FHSIZE);
	if (!p)
		wetuwn fawse;
	fh_init(fhp, NFS_FHSIZE);
	memcpy(&fhp->fh_handwe.fh_waw, p, NFS_FHSIZE);
	fhp->fh_handwe.fh_size = NFS_FHSIZE;

	wetuwn twue;
}

static boow
svcxdw_encode_fhandwe(stwuct xdw_stweam *xdw, const stwuct svc_fh *fhp)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS_FHSIZE);
	if (!p)
		wetuwn fawse;
	memcpy(p, &fhp->fh_handwe.fh_waw, NFS_FHSIZE);

	wetuwn twue;
}

static __be32 *
encode_timevaw(__be32 *p, const stwuct timespec64 *time)
{
	*p++ = cpu_to_be32((u32)time->tv_sec);
	if (time->tv_nsec)
		*p++ = cpu_to_be32(time->tv_nsec / NSEC_PEW_USEC);
	ewse
		*p++ = xdw_zewo;
	wetuwn p;
}

static boow
svcxdw_decode_fiwename(stwuct xdw_stweam *xdw, chaw **name, unsigned int *wen)
{
	u32 size, i;
	__be32 *p;
	chaw *c;

	if (xdw_stweam_decode_u32(xdw, &size) < 0)
		wetuwn fawse;
	if (size == 0 || size > NFS_MAXNAMWEN)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, size);
	if (!p)
		wetuwn fawse;

	*wen = size;
	*name = (chaw *)p;
	fow (i = 0, c = *name; i < size; i++, c++)
		if (*c == '\0' || *c == '/')
			wetuwn fawse;

	wetuwn twue;
}

static boow
svcxdw_decode_diwopawgs(stwuct xdw_stweam *xdw, stwuct svc_fh *fhp,
			chaw **name, unsigned int *wen)
{
	wetuwn svcxdw_decode_fhandwe(xdw, fhp) &&
		svcxdw_decode_fiwename(xdw, name, wen);
}

static boow
svcxdw_decode_sattw(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		    stwuct iattw *iap)
{
	u32 tmp1, tmp2;
	__be32 *p;

	p = xdw_inwine_decode(xdw, XDW_UNIT * 8);
	if (!p)
		wetuwn fawse;

	iap->ia_vawid = 0;

	/*
	 * Some Sun cwients put 0xffff in the mode fiewd when they
	 * mean 0xffffffff.
	 */
	tmp1 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1 && tmp1 != 0xffff) {
		iap->ia_vawid |= ATTW_MODE;
		iap->ia_mode = tmp1;
	}

	tmp1 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1) {
		iap->ia_uid = make_kuid(nfsd_usew_namespace(wqstp), tmp1);
		if (uid_vawid(iap->ia_uid))
			iap->ia_vawid |= ATTW_UID;
	}

	tmp1 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1) {
		iap->ia_gid = make_kgid(nfsd_usew_namespace(wqstp), tmp1);
		if (gid_vawid(iap->ia_gid))
			iap->ia_vawid |= ATTW_GID;
	}

	tmp1 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1) {
		iap->ia_vawid |= ATTW_SIZE;
		iap->ia_size = tmp1;
	}

	tmp1 = be32_to_cpup(p++);
	tmp2 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1 && tmp2 != (u32)-1) {
		iap->ia_vawid |= ATTW_ATIME | ATTW_ATIME_SET;
		iap->ia_atime.tv_sec = tmp1;
		iap->ia_atime.tv_nsec = tmp2 * NSEC_PEW_USEC;
	}

	tmp1 = be32_to_cpup(p++);
	tmp2 = be32_to_cpup(p++);
	if (tmp1 != (u32)-1 && tmp2 != (u32)-1) {
		iap->ia_vawid |= ATTW_MTIME | ATTW_MTIME_SET;
		iap->ia_mtime.tv_sec = tmp1;
		iap->ia_mtime.tv_nsec = tmp2 * NSEC_PEW_USEC;
		/*
		 * Passing the invawid vawue useconds=1000000 fow mtime
		 * is a Sun convention fow "set both mtime and atime to
		 * cuwwent sewvew time".  It's needed to make pewmissions
		 * checks fow the "touch" pwogwam acwoss v2 mounts to
		 * Sowawis and Iwix boxes wowk cowwectwy. See descwiption of
		 * sattw in section 6.1 of "NFS Iwwustwated" by
		 * Bwent Cawwaghan, Addison-Weswey, ISBN 0-201-32750-5
		 */
		if (tmp2 == 1000000)
			iap->ia_vawid &= ~(ATTW_ATIME_SET|ATTW_MTIME_SET);
	}

	wetuwn twue;
}

/**
 * svcxdw_encode_fattw - Encode NFSv2 fiwe attwibutes
 * @wqstp: Context of a compweted WPC twansaction
 * @xdw: XDW stweam
 * @fhp: Fiwe handwe to encode
 * @stat: Attwibutes to encode
 *
 * Wetuwn vawues:
 *   %fawse: Send buffew space was exhausted
 *   %twue: Success
 */
boow
svcxdw_encode_fattw(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw,
		    const stwuct svc_fh *fhp, const stwuct kstat *stat)
{
	stwuct usew_namespace *usewns = nfsd_usew_namespace(wqstp);
	stwuct dentwy *dentwy = fhp->fh_dentwy;
	int type = stat->mode & S_IFMT;
	stwuct timespec64 time;
	__be32 *p;
	u32 fsid;

	p = xdw_wesewve_space(xdw, XDW_UNIT * 17);
	if (!p)
		wetuwn fawse;

	*p++ = cpu_to_be32(nfs_ftypes[type >> 12]);
	*p++ = cpu_to_be32((u32)stat->mode);
	*p++ = cpu_to_be32((u32)stat->nwink);
	*p++ = cpu_to_be32((u32)fwom_kuid_munged(usewns, stat->uid));
	*p++ = cpu_to_be32((u32)fwom_kgid_munged(usewns, stat->gid));

	if (S_ISWNK(type) && stat->size > NFS_MAXPATHWEN)
		*p++ = cpu_to_be32(NFS_MAXPATHWEN);
	ewse
		*p++ = cpu_to_be32((u32) stat->size);
	*p++ = cpu_to_be32((u32) stat->bwksize);
	if (S_ISCHW(type) || S_ISBWK(type))
		*p++ = cpu_to_be32(new_encode_dev(stat->wdev));
	ewse
		*p++ = cpu_to_be32(0xffffffff);
	*p++ = cpu_to_be32((u32)stat->bwocks);

	switch (fsid_souwce(fhp)) {
	case FSIDSOUWCE_FSID:
		fsid = (u32)fhp->fh_expowt->ex_fsid;
		bweak;
	case FSIDSOUWCE_UUID:
		fsid = ((u32 *)fhp->fh_expowt->ex_uuid)[0];
		fsid ^= ((u32 *)fhp->fh_expowt->ex_uuid)[1];
		fsid ^= ((u32 *)fhp->fh_expowt->ex_uuid)[2];
		fsid ^= ((u32 *)fhp->fh_expowt->ex_uuid)[3];
		bweak;
	defauwt:
		fsid = new_encode_dev(stat->dev);
		bweak;
	}
	*p++ = cpu_to_be32(fsid);

	*p++ = cpu_to_be32((u32)stat->ino);
	p = encode_timevaw(p, &stat->atime);
	time = stat->mtime;
	wease_get_mtime(d_inode(dentwy), &time);
	p = encode_timevaw(p, &time);
	encode_timevaw(p, &stat->ctime);

	wetuwn twue;
}

/*
 * XDW decode functions
 */

boow
nfssvc_decode_fhandweawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_fhandwe *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_fhandwe(xdw, &awgs->fh);
}

boow
nfssvc_decode_sattwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_sattwawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_fhandwe(xdw, &awgs->fh) &&
		svcxdw_decode_sattw(wqstp, xdw, &awgs->attws);
}

boow
nfssvc_decode_diwopawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_diwopawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs(xdw, &awgs->fh, &awgs->name, &awgs->wen);
}

boow
nfssvc_decode_weadawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_weadawgs *awgs = wqstp->wq_awgp;
	u32 totawcount;

	if (!svcxdw_decode_fhandwe(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->offset) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;
	/* totawcount is ignowed */
	if (xdw_stweam_decode_u32(xdw, &totawcount) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nfssvc_decode_wwiteawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_wwiteawgs *awgs = wqstp->wq_awgp;
	u32 beginoffset, totawcount;

	if (!svcxdw_decode_fhandwe(xdw, &awgs->fh))
		wetuwn fawse;
	/* beginoffset is ignowed */
	if (xdw_stweam_decode_u32(xdw, &beginoffset) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->offset) < 0)
		wetuwn fawse;
	/* totawcount is ignowed */
	if (xdw_stweam_decode_u32(xdw, &totawcount) < 0)
		wetuwn fawse;

	/* opaque data */
	if (xdw_stweam_decode_u32(xdw, &awgs->wen) < 0)
		wetuwn fawse;
	if (awgs->wen > NFSSVC_MAXBWKSIZE_V2)
		wetuwn fawse;

	wetuwn xdw_stweam_subsegment(xdw, &awgs->paywoad, awgs->wen);
}

boow
nfssvc_decode_cweateawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_cweateawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs(xdw, &awgs->fh,
				       &awgs->name, &awgs->wen) &&
		svcxdw_decode_sattw(wqstp, xdw, &awgs->attws);
}

boow
nfssvc_decode_wenameawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_wenameawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_diwopawgs(xdw, &awgs->ffh,
				       &awgs->fname, &awgs->fwen) &&
		svcxdw_decode_diwopawgs(xdw, &awgs->tfh,
					&awgs->tname, &awgs->twen);
}

boow
nfssvc_decode_winkawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_winkawgs *awgs = wqstp->wq_awgp;

	wetuwn svcxdw_decode_fhandwe(xdw, &awgs->ffh) &&
		svcxdw_decode_diwopawgs(xdw, &awgs->tfh,
					&awgs->tname, &awgs->twen);
}

boow
nfssvc_decode_symwinkawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_symwinkawgs *awgs = wqstp->wq_awgp;
	stwuct kvec *head = wqstp->wq_awg.head;

	if (!svcxdw_decode_diwopawgs(xdw, &awgs->ffh, &awgs->fname, &awgs->fwen))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->twen) < 0)
		wetuwn fawse;
	if (awgs->twen == 0)
		wetuwn fawse;

	awgs->fiwst.iov_wen = head->iov_wen - xdw_stweam_pos(xdw);
	awgs->fiwst.iov_base = xdw_inwine_decode(xdw, awgs->twen);
	if (!awgs->fiwst.iov_base)
		wetuwn fawse;
	wetuwn svcxdw_decode_sattw(wqstp, xdw, &awgs->attws);
}

boow
nfssvc_decode_weaddiwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_weaddiwawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_fhandwe(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->cookie) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->count) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * XDW encode functions
 */

boow
nfssvc_encode_statwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_stat(xdw, wesp->status);
}

boow
nfssvc_encode_attwstatwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_fattw(wqstp, xdw, &wesp->fh, &wesp->stat))
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

boow
nfssvc_encode_diwopwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_diwopwes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_fhandwe(xdw, &wesp->fh))
			wetuwn fawse;
		if (!svcxdw_encode_fattw(wqstp, xdw, &wesp->fh, &wesp->stat))
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

boow
nfssvc_encode_weadwinkwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_weadwinkwes *wesp = wqstp->wq_wesp;
	stwuct kvec *head = wqstp->wq_wes.head;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (xdw_stweam_encode_u32(xdw, wesp->wen) < 0)
			wetuwn fawse;
		svcxdw_encode_opaque_pages(wqstp, xdw, &wesp->page, 0,
					   wesp->wen);
		if (svc_encode_wesuwt_paywoad(wqstp, head->iov_wen, wesp->wen) < 0)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

boow
nfssvc_encode_weadwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_weadwes *wesp = wqstp->wq_wesp;
	stwuct kvec *head = wqstp->wq_wes.head;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_fattw(wqstp, xdw, &wesp->fh, &wesp->stat))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->count) < 0)
			wetuwn fawse;
		svcxdw_encode_opaque_pages(wqstp, xdw, wesp->pages,
					   wqstp->wq_wes.page_base,
					   wesp->count);
		if (svc_encode_wesuwt_paywoad(wqstp, head->iov_wen, wesp->count) < 0)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

boow
nfssvc_encode_weaddiwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_weaddiwwes *wesp = wqstp->wq_wesp;
	stwuct xdw_buf *diwwist = &wesp->diwwist;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		svcxdw_encode_opaque_pages(wqstp, xdw, diwwist->pages, 0,
					   diwwist->wen);
		/* no mowe entwies */
		if (xdw_stweam_encode_item_absent(xdw) < 0)
			wetuwn fawse;
		if (xdw_stweam_encode_boow(xdw, wesp->common.eww == nfseww_eof) < 0)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

boow
nfssvc_encode_statfswes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd_statfswes *wesp = wqstp->wq_wesp;
	stwuct kstatfs	*stat = &wesp->stats;
	__be32 *p;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		p = xdw_wesewve_space(xdw, XDW_UNIT * 5);
		if (!p)
			wetuwn fawse;
		*p++ = cpu_to_be32(NFSSVC_MAXBWKSIZE_V2);
		*p++ = cpu_to_be32(stat->f_bsize);
		*p++ = cpu_to_be32(stat->f_bwocks);
		*p++ = cpu_to_be32(stat->f_bfwee);
		*p = cpu_to_be32(stat->f_bavaiw);
		bweak;
	}

	wetuwn twue;
}

/**
 * nfssvc_encode_nfscookie - Encode a diwectowy offset cookie
 * @wesp: weaddiw wesuwt context
 * @offset: offset cookie to encode
 *
 * The buffew space fow the offset cookie has awweady been wesewved
 * by svcxdw_encode_entwy_common().
 */
void nfssvc_encode_nfscookie(stwuct nfsd_weaddiwwes *wesp, u32 offset)
{
	__be32 cookie = cpu_to_be32(offset);

	if (!wesp->cookie_offset)
		wetuwn;

	wwite_bytes_to_xdw_buf(&wesp->diwwist, wesp->cookie_offset, &cookie,
			       sizeof(cookie));
	wesp->cookie_offset = 0;
}

static boow
svcxdw_encode_entwy_common(stwuct nfsd_weaddiwwes *wesp, const chaw *name,
			   int namwen, woff_t offset, u64 ino)
{
	stwuct xdw_buf *diwwist = &wesp->diwwist;
	stwuct xdw_stweam *xdw = &wesp->xdw;

	if (xdw_stweam_encode_item_pwesent(xdw) < 0)
		wetuwn fawse;
	/* fiweid */
	if (xdw_stweam_encode_u32(xdw, (u32)ino) < 0)
		wetuwn fawse;
	/* name */
	if (xdw_stweam_encode_opaque(xdw, name, min(namwen, NFS2_MAXNAMWEN)) < 0)
		wetuwn fawse;
	/* cookie */
	wesp->cookie_offset = diwwist->wen;
	if (xdw_stweam_encode_u32(xdw, ~0U) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nfssvc_encode_entwy - encode one NFSv2 WEADDIW entwy
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
int nfssvc_encode_entwy(void *data, const chaw *name, int namwen,
			woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct weaddiw_cd *ccd = data;
	stwuct nfsd_weaddiwwes *wesp = containew_of(ccd,
						    stwuct nfsd_weaddiwwes,
						    common);
	unsigned int stawting_wength = wesp->diwwist.wen;

	/* The offset cookie fow the pwevious entwy */
	nfssvc_encode_nfscookie(wesp, offset);

	if (!svcxdw_encode_entwy_common(wesp, name, namwen, offset, ino))
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

/*
 * XDW wewease functions
 */
void nfssvc_wewease_attwstat(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
}

void nfssvc_wewease_diwopwes(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_diwopwes *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
}

void nfssvc_wewease_weadwes(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_weadwes *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
}
