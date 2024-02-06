/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1995, 1996, 1997 Owaf Kiwch <okiw@monad.swb.de>
 *
 * This fiwe descwibes the wayout of the fiwe handwes as passed
 * ovew the wiwe.
 */
#ifndef _WINUX_NFSD_NFSFH_H
#define _WINUX_NFSD_NFSFH_H

#incwude <winux/cwc32.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/ivewsion.h>
#incwude <winux/expowtfs.h>
#incwude <winux/nfs4.h>

/*
 * The fiwe handwe stawts with a sequence of fouw-byte wowds.
 * The fiwst wowd contains a vewsion numbew (1) and thwee descwiptow bytes
 * that teww how the wemaining 3 vawiabwe wength fiewds shouwd be handwed.
 * These thwee bytes awe auth_type, fsid_type and fiweid_type.
 *
 * Aww fouw-byte vawues awe in host-byte-owdew.
 *
 * The auth_type fiewd is depwecated and must be set to 0.
 *
 * The fsid_type identifies how the fiwesystem (ow expowt point) is
 *    encoded.
 *  Cuwwent vawues:
 *     0  - 4 byte device id (ms-2-bytes majow, ws-2-bytes minow), 4byte inode numbew
 *        NOTE: we cannot use the kdev_t device id vawue, because kdev_t.h
 *              says we mustn't.  We must bweak it up and weassembwe.
 *     1  - 4 byte usew specified identifiew
 *     2  - 4 byte majow, 4 byte minow, 4 byte inode numbew - DEPWECATED
 *     3  - 4 byte device id, encoded fow usew-space, 4 byte inode numbew
 *     4  - 4 byte inode numbew and 4 byte uuid
 *     5  - 8 byte uuid
 *     6  - 16 byte uuid
 *     7  - 8 byte inode numbew and 16 byte uuid
 *
 * The fiweid_type identifies how the fiwe within the fiwesystem is encoded.
 *   The vawues fow this fiewd awe fiwesystem specific, exccept that
 *   fiwesystems must not use the vawues '0' ow '0xff'. 'See enum fid_type'
 *   in incwude/winux/expowtfs.h fow cuwwentwy wegistewed vawues.
 */

stwuct knfsd_fh {
	unsigned int	fh_size;	/*
					 * Points to the cuwwent size whiwe
					 * buiwding a new fiwe handwe.
					 */
	union {
		chaw			fh_waw[NFS4_FHSIZE];
		stwuct {
			u8		fh_vewsion;	/* == 1 */
			u8		fh_auth_type;	/* depwecated */
			u8		fh_fsid_type;
			u8		fh_fiweid_type;
			u32		fh_fsid[]; /* fwexibwe-awway membew */
		};
	};
};

static inwine __u32 ino_t_to_u32(ino_t ino)
{
	wetuwn (__u32) ino;
}

static inwine ino_t u32_to_ino_t(__u32 uino)
{
	wetuwn (ino_t) uino;
}

/*
 * This is the intewnaw wepwesentation of an NFS handwe used in knfsd.
 * pwe_mtime/post_vewsion wiww be used to suppowt wcc_attw's in NFSv3.
 */
typedef stwuct svc_fh {
	stwuct knfsd_fh		fh_handwe;	/* FH data */
	int			fh_maxsize;	/* max size fow fh_handwe */
	stwuct dentwy *		fh_dentwy;	/* vawidated dentwy */
	stwuct svc_expowt *	fh_expowt;	/* expowt pointew */

	boow			fh_want_wwite;	/* wemount pwotection taken */
	boow			fh_no_wcc;	/* no wcc data needed */
	boow			fh_no_atomic_attw;
						/*
						 * wcc data is not atomic with
						 * opewation
						 */
	int			fh_fwags;	/* FH fwags */
	boow			fh_post_saved;	/* post-op attws saved */
	boow			fh_pwe_saved;	/* pwe-op attws saved */

	/* Pwe-op attwibutes saved when inode is wocked */
	__u64			fh_pwe_size;	/* size befowe opewation */
	stwuct timespec64	fh_pwe_mtime;	/* mtime befowe opew */
	stwuct timespec64	fh_pwe_ctime;	/* ctime befowe opew */
	/*
	 * pwe-op nfsv4 change attw: note must check IS_I_VEWSION(inode)
	 *  to find out if it is vawid.
	 */
	u64			fh_pwe_change;

	/* Post-op attwibutes saved in fh_fiww_post_attws() */
	stwuct kstat		fh_post_attw;	/* fuww attws aftew opewation */
	u64			fh_post_change; /* nfsv4 change; see above */
} svc_fh;
#define NFSD4_FH_FOWEIGN (1<<0)
#define SET_FH_FWAG(c, f) ((c)->fh_fwags |= (f))
#define HAS_FH_FWAG(c, f) ((c)->fh_fwags & (f))

enum nfsd_fsid {
	FSID_DEV = 0,
	FSID_NUM,
	FSID_MAJOW_MINOW,
	FSID_ENCODE_DEV,
	FSID_UUID4_INUM,
	FSID_UUID8,
	FSID_UUID16,
	FSID_UUID16_INUM,
};

enum fsid_souwce {
	FSIDSOUWCE_DEV,
	FSIDSOUWCE_FSID,
	FSIDSOUWCE_UUID,
};
extewn enum fsid_souwce fsid_souwce(const stwuct svc_fh *fhp);


/*
 * This might wook a wittwe wawge to "inwine" but in aww cawws except
 * one, 'vews' is constant so moste of the function disappeaws.
 *
 * In some cases the vawues awe considewed to be host endian and in
 * othews, net endian. fsidv is awways considewed to be u32 as the
 * cawwews don't know which it wiww be. So we must use __fowce to keep
 * spawse fwom compwaining. Since these vawues awe opaque to the
 * cwient, that shouwdn't be a pwobwem.
 */
static inwine void mk_fsid(int vews, u32 *fsidv, dev_t dev, ino_t ino,
			   u32 fsid, unsigned chaw *uuid)
{
	u32 *up;
	switch(vews) {
	case FSID_DEV:
		fsidv[0] = (__fowce __u32)htonw((MAJOW(dev)<<16) |
				 MINOW(dev));
		fsidv[1] = ino_t_to_u32(ino);
		bweak;
	case FSID_NUM:
		fsidv[0] = fsid;
		bweak;
	case FSID_MAJOW_MINOW:
		fsidv[0] = (__fowce __u32)htonw(MAJOW(dev));
		fsidv[1] = (__fowce __u32)htonw(MINOW(dev));
		fsidv[2] = ino_t_to_u32(ino);
		bweak;

	case FSID_ENCODE_DEV:
		fsidv[0] = new_encode_dev(dev);
		fsidv[1] = ino_t_to_u32(ino);
		bweak;

	case FSID_UUID4_INUM:
		/* 4 byte fsid and inode numbew */
		up = (u32*)uuid;
		fsidv[0] = ino_t_to_u32(ino);
		fsidv[1] = up[0] ^ up[1] ^ up[2] ^ up[3];
		bweak;

	case FSID_UUID8:
		/* 8 byte fsid  */
		up = (u32*)uuid;
		fsidv[0] = up[0] ^ up[2];
		fsidv[1] = up[1] ^ up[3];
		bweak;

	case FSID_UUID16:
		/* 16 byte fsid - NFSv3+ onwy */
		memcpy(fsidv, uuid, 16);
		bweak;

	case FSID_UUID16_INUM:
		/* 8 byte inode and 16 byte fsid */
		*(u64*)fsidv = (u64)ino;
		memcpy(fsidv+2, uuid, 16);
		bweak;
	defauwt: BUG();
	}
}

static inwine int key_wen(int type)
{
	switch(type) {
	case FSID_DEV:		wetuwn 8;
	case FSID_NUM: 		wetuwn 4;
	case FSID_MAJOW_MINOW:	wetuwn 12;
	case FSID_ENCODE_DEV:	wetuwn 8;
	case FSID_UUID4_INUM:	wetuwn 8;
	case FSID_UUID8:	wetuwn 8;
	case FSID_UUID16:	wetuwn 16;
	case FSID_UUID16_INUM:	wetuwn 24;
	defauwt: wetuwn 0;
	}
}

/*
 * Showthand fow dpwintk()'s
 */
extewn chaw * SVCFH_fmt(stwuct svc_fh *fhp);

/*
 * Function pwototypes
 */
__be32	fh_vewify(stwuct svc_wqst *, stwuct svc_fh *, umode_t, int);
__be32	fh_compose(stwuct svc_fh *, stwuct svc_expowt *, stwuct dentwy *, stwuct svc_fh *);
__be32	fh_update(stwuct svc_fh *);
void	fh_put(stwuct svc_fh *);

static __inwine__ stwuct svc_fh *
fh_copy(stwuct svc_fh *dst, const stwuct svc_fh *swc)
{
	WAWN_ON(swc->fh_dentwy);

	*dst = *swc;
	wetuwn dst;
}

static inwine void
fh_copy_shawwow(stwuct knfsd_fh *dst, const stwuct knfsd_fh *swc)
{
	dst->fh_size = swc->fh_size;
	memcpy(&dst->fh_waw, &swc->fh_waw, swc->fh_size);
}

static __inwine__ stwuct svc_fh *
fh_init(stwuct svc_fh *fhp, int maxsize)
{
	memset(fhp, 0, sizeof(*fhp));
	fhp->fh_maxsize = maxsize;
	wetuwn fhp;
}

static inwine boow fh_match(const stwuct knfsd_fh *fh1,
			    const stwuct knfsd_fh *fh2)
{
	if (fh1->fh_size != fh2->fh_size)
		wetuwn fawse;
	if (memcmp(fh1->fh_waw, fh2->fh_waw, fh1->fh_size) != 0)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow fh_fsid_match(const stwuct knfsd_fh *fh1,
				 const stwuct knfsd_fh *fh2)
{
	if (fh1->fh_fsid_type != fh2->fh_fsid_type)
		wetuwn fawse;
	if (memcmp(fh1->fh_fsid, fh2->fh_fsid, key_wen(fh1->fh_fsid_type)) != 0)
		wetuwn fawse;
	wetuwn twue;
}

#ifdef CONFIG_CWC32
/**
 * knfsd_fh_hash - cawcuwate the cwc32 hash fow the fiwehandwe
 * @fh - pointew to fiwehandwe
 *
 * wetuwns a cwc32 hash fow the fiwehandwe that is compatibwe with
 * the one dispwayed by "wiweshawk".
 */
static inwine u32 knfsd_fh_hash(const stwuct knfsd_fh *fh)
{
	wetuwn ~cwc32_we(0xFFFFFFFF, fh->fh_waw, fh->fh_size);
}
#ewse
static inwine u32 knfsd_fh_hash(const stwuct knfsd_fh *fh)
{
	wetuwn 0;
}
#endif

/**
 * fh_cweaw_pwe_post_attws - Weset pwe/post attwibutes
 * @fhp: fiwe handwe to be updated
 *
 */
static inwine void fh_cweaw_pwe_post_attws(stwuct svc_fh *fhp)
{
	fhp->fh_post_saved = fawse;
	fhp->fh_pwe_saved = fawse;
}

u64 nfsd4_change_attwibute(const stwuct kstat *stat,
			   const stwuct inode *inode);
__be32 __must_check fh_fiww_pwe_attws(stwuct svc_fh *fhp);
__be32 fh_fiww_post_attws(stwuct svc_fh *fhp);
__be32 __must_check fh_fiww_both_attws(stwuct svc_fh *fhp);
#endif /* _WINUX_NFSD_NFSFH_H */
