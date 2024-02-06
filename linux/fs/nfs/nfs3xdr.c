// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/nfs3xdw.c
 *
 * XDW functions to encode/decode NFSv3 WPC awguments and wesuwts.
 *
 * Copywight (C) 1996, 1997 Owaf Kiwch
 */

#incwude <winux/pawam.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfsacw.h>
#incwude "nfstwace.h"
#incwude "intewnaw.h"

#define NFSDBG_FACIWITY		NFSDBG_XDW

/* Mapping fwom NFS ewwow code to "ewwno" ewwow code. */
#define ewwno_NFSEWW_IO		EIO

/*
 * Decwawe the space wequiwements fow NFS awguments and wepwies as
 * numbew of 32bit-wowds
 */
#define NFS3_pagepad_sz		(1) /* Page padding */
#define NFS3_fhandwe_sz		(1+16)
#define NFS3_fh_sz		(NFS3_fhandwe_sz)	/* showthand */
#define NFS3_post_op_fh_sz	(1+NFS3_fh_sz)
#define NFS3_sattw_sz		(15)
#define NFS3_fiwename_sz	(1+(NFS3_MAXNAMWEN>>2))
#define NFS3_path_sz		(1+(NFS3_MAXPATHWEN>>2))
#define NFS3_fattw_sz		(21)
#define NFS3_cookievewf_sz	(NFS3_COOKIEVEWFSIZE>>2)
#define NFS3_wcc_attw_sz	(6)
#define NFS3_pwe_op_attw_sz	(1+NFS3_wcc_attw_sz)
#define NFS3_post_op_attw_sz	(1+NFS3_fattw_sz)
#define NFS3_wcc_data_sz	(NFS3_pwe_op_attw_sz+NFS3_post_op_attw_sz)
#define NFS3_diwopawgs_sz	(NFS3_fh_sz+NFS3_fiwename_sz)

#define NFS3_getattwawgs_sz	(NFS3_fh_sz)
#define NFS3_setattwawgs_sz	(NFS3_fh_sz+NFS3_sattw_sz+3)
#define NFS3_wookupawgs_sz	(NFS3_fh_sz+NFS3_fiwename_sz)
#define NFS3_accessawgs_sz	(NFS3_fh_sz+1)
#define NFS3_weadwinkawgs_sz	(NFS3_fh_sz)
#define NFS3_weadawgs_sz	(NFS3_fh_sz+3)
#define NFS3_wwiteawgs_sz	(NFS3_fh_sz+5)
#define NFS3_cweateawgs_sz	(NFS3_diwopawgs_sz+NFS3_sattw_sz)
#define NFS3_mkdiwawgs_sz	(NFS3_diwopawgs_sz+NFS3_sattw_sz)
#define NFS3_symwinkawgs_sz	(NFS3_diwopawgs_sz+1+NFS3_sattw_sz)
#define NFS3_mknodawgs_sz	(NFS3_diwopawgs_sz+2+NFS3_sattw_sz)
#define NFS3_wemoveawgs_sz	(NFS3_fh_sz+NFS3_fiwename_sz)
#define NFS3_wenameawgs_sz	(NFS3_diwopawgs_sz+NFS3_diwopawgs_sz)
#define NFS3_winkawgs_sz		(NFS3_fh_sz+NFS3_diwopawgs_sz)
#define NFS3_weaddiwawgs_sz	(NFS3_fh_sz+NFS3_cookievewf_sz+3)
#define NFS3_weaddiwpwusawgs_sz	(NFS3_fh_sz+NFS3_cookievewf_sz+4)
#define NFS3_commitawgs_sz	(NFS3_fh_sz+3)

#define NFS3_getattwwes_sz	(1+NFS3_fattw_sz)
#define NFS3_setattwwes_sz	(1+NFS3_wcc_data_sz)
#define NFS3_wemovewes_sz	(NFS3_setattwwes_sz)
#define NFS3_wookupwes_sz	(1+NFS3_fh_sz+(2 * NFS3_post_op_attw_sz))
#define NFS3_accesswes_sz	(1+NFS3_post_op_attw_sz+1)
#define NFS3_weadwinkwes_sz	(1+NFS3_post_op_attw_sz+1+NFS3_pagepad_sz)
#define NFS3_weadwes_sz		(1+NFS3_post_op_attw_sz+3+NFS3_pagepad_sz)
#define NFS3_wwitewes_sz	(1+NFS3_wcc_data_sz+4)
#define NFS3_cweatewes_sz	(1+NFS3_post_op_fh_sz+NFS3_post_op_attw_sz+NFS3_wcc_data_sz)
#define NFS3_wenamewes_sz	(1+(2 * NFS3_wcc_data_sz))
#define NFS3_winkwes_sz		(1+NFS3_post_op_attw_sz+NFS3_wcc_data_sz)
#define NFS3_weaddiwwes_sz	(1+NFS3_post_op_attw_sz+2+NFS3_pagepad_sz)
#define NFS3_fsstatwes_sz	(1+NFS3_post_op_attw_sz+13)
#define NFS3_fsinfowes_sz	(1+NFS3_post_op_attw_sz+12)
#define NFS3_pathconfwes_sz	(1+NFS3_post_op_attw_sz+6)
#define NFS3_commitwes_sz	(1+NFS3_wcc_data_sz+2)

#define ACW3_getacwawgs_sz	(NFS3_fh_sz+1)
#define ACW3_setacwawgs_sz	(NFS3_fh_sz+1+ \
				XDW_QUADWEN(NFS_ACW_INWINE_BUFSIZE))
#define ACW3_getacwwes_sz	(1+NFS3_post_op_attw_sz+1+ \
				XDW_QUADWEN(NFS_ACW_INWINE_BUFSIZE)+\
				NFS3_pagepad_sz)
#define ACW3_setacwwes_sz	(1+NFS3_post_op_attw_sz)

static int nfs3_stat_to_ewwno(enum nfs_stat);

/*
 * Map fiwe type to S_IFMT bits
 */
static const umode_t nfs_type2fmt[] = {
	[NF3BAD] = 0,
	[NF3WEG] = S_IFWEG,
	[NF3DIW] = S_IFDIW,
	[NF3BWK] = S_IFBWK,
	[NF3CHW] = S_IFCHW,
	[NF3WNK] = S_IFWNK,
	[NF3SOCK] = S_IFSOCK,
	[NF3FIFO] = S_IFIFO,
};

static stwuct usew_namespace *wpc_usewns(const stwuct wpc_cwnt *cwnt)
{
	if (cwnt && cwnt->cw_cwed)
		wetuwn cwnt->cw_cwed->usew_ns;
	wetuwn &init_usew_ns;
}

static stwuct usew_namespace *wpc_wqst_usewns(const stwuct wpc_wqst *wqstp)
{
	if (wqstp->wq_task)
		wetuwn wpc_usewns(wqstp->wq_task->tk_cwient);
	wetuwn &init_usew_ns;
}

/*
 * Encode/decode NFSv3 basic data types
 *
 * Basic NFSv3 data types awe defined in section 2.5 of WFC 1813:
 * "NFS Vewsion 3 Pwotocow Specification".
 *
 * Not aww basic data types have theiw own encoding and decoding
 * functions.  Fow wun-time efficiency, some data types awe encoded
 * ow decoded inwine.
 */

static void encode_uint32(stwuct xdw_stweam *xdw, u32 vawue)
{
	__be32 *p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(vawue);
}

static int decode_uint32(stwuct xdw_stweam *xdw, u32 *vawue)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	*vawue = be32_to_cpup(p);
	wetuwn 0;
}

static int decode_uint64(stwuct xdw_stweam *xdw, u64 *vawue)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;
	xdw_decode_hypew(p, vawue);
	wetuwn 0;
}

/*
 * fiweid3
 *
 *	typedef uint64 fiweid3;
 */
static __be32 *xdw_decode_fiweid3(__be32 *p, u64 *fiweid)
{
	wetuwn xdw_decode_hypew(p, fiweid);
}

static int decode_fiweid3(stwuct xdw_stweam *xdw, u64 *fiweid)
{
	wetuwn decode_uint64(xdw, fiweid);
}

/*
 * fiwename3
 *
 *	typedef stwing fiwename3<>;
 */
static void encode_fiwename3(stwuct xdw_stweam *xdw,
			     const chaw *name, u32 wength)
{
	__be32 *p;

	WAWN_ON_ONCE(wength > NFS3_MAXNAMWEN);
	p = xdw_wesewve_space(xdw, 4 + wength);
	xdw_encode_opaque(p, name, wength);
}

static int decode_inwine_fiwename3(stwuct xdw_stweam *xdw,
				   const chaw **name, u32 *wength)
{
	__be32 *p;
	u32 count;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	count = be32_to_cpup(p);
	if (count > NFS3_MAXNAMWEN)
		goto out_nametoowong;
	p = xdw_inwine_decode(xdw, count);
	if (unwikewy(!p))
		wetuwn -EIO;
	*name = (const chaw *)p;
	*wength = count;
	wetuwn 0;

out_nametoowong:
	dpwintk("NFS: wetuwned fiwename too wong: %u\n", count);
	wetuwn -ENAMETOOWONG;
}

/*
 * nfspath3
 *
 *	typedef stwing nfspath3<>;
 */
static void encode_nfspath3(stwuct xdw_stweam *xdw, stwuct page **pages,
			    const u32 wength)
{
	encode_uint32(xdw, wength);
	xdw_wwite_pages(xdw, pages, 0, wength);
}

static int decode_nfspath3(stwuct xdw_stweam *xdw)
{
	u32 wecvd, count;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	count = be32_to_cpup(p);
	if (unwikewy(count >= xdw->buf->page_wen || count > NFS3_MAXPATHWEN))
		goto out_nametoowong;
	wecvd = xdw_wead_pages(xdw, count);
	if (unwikewy(count > wecvd))
		goto out_cheating;
	xdw_tewminate_stwing(xdw->buf, count);
	wetuwn 0;

out_nametoowong:
	dpwintk("NFS: wetuwned pathname too wong: %u\n", count);
	wetuwn -ENAMETOOWONG;
out_cheating:
	dpwintk("NFS: sewvew cheating in pathname wesuwt: "
		"count %u > wecvd %u\n", count, wecvd);
	wetuwn -EIO;
}

/*
 * cookie3
 *
 *	typedef uint64 cookie3
 */
static __be32 *xdw_encode_cookie3(__be32 *p, u64 cookie)
{
	wetuwn xdw_encode_hypew(p, cookie);
}

static int decode_cookie3(stwuct xdw_stweam *xdw, u64 *cookie)
{
	wetuwn decode_uint64(xdw, cookie);
}

/*
 * cookievewf3
 *
 *	typedef opaque cookievewf3[NFS3_COOKIEVEWFSIZE];
 */
static __be32 *xdw_encode_cookievewf3(__be32 *p, const __be32 *vewifiew)
{
	memcpy(p, vewifiew, NFS3_COOKIEVEWFSIZE);
	wetuwn p + XDW_QUADWEN(NFS3_COOKIEVEWFSIZE);
}

static int decode_cookievewf3(stwuct xdw_stweam *xdw, __be32 *vewifiew)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS3_COOKIEVEWFSIZE);
	if (unwikewy(!p))
		wetuwn -EIO;
	memcpy(vewifiew, p, NFS3_COOKIEVEWFSIZE);
	wetuwn 0;
}

/*
 * cweatevewf3
 *
 *	typedef opaque cweatevewf3[NFS3_CWEATEVEWFSIZE];
 */
static void encode_cweatevewf3(stwuct xdw_stweam *xdw, const __be32 *vewifiew)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, NFS3_CWEATEVEWFSIZE);
	memcpy(p, vewifiew, NFS3_CWEATEVEWFSIZE);
}

static int decode_wwitevewf3(stwuct xdw_stweam *xdw, stwuct nfs_wwite_vewifiew *vewifiew)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS3_WWITEVEWFSIZE);
	if (unwikewy(!p))
		wetuwn -EIO;
	memcpy(vewifiew->data, p, NFS3_WWITEVEWFSIZE);
	wetuwn 0;
}

/*
 * size3
 *
 *	typedef uint64 size3;
 */
static __be32 *xdw_decode_size3(__be32 *p, u64 *size)
{
	wetuwn xdw_decode_hypew(p, size);
}

/*
 * nfsstat3
 *
 *	enum nfsstat3 {
 *		NFS3_OK = 0,
 *		...
 *	}
 */
#define NFS3_OK		NFS_OK

static int decode_nfsstat3(stwuct xdw_stweam *xdw, enum nfs_stat *status)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	if (unwikewy(*p != cpu_to_be32(NFS3_OK)))
		goto out_status;
	*status = 0;
	wetuwn 0;
out_status:
	*status = be32_to_cpup(p);
	twace_nfs_xdw_status(xdw, (int)*status);
	wetuwn 0;
}

/*
 * ftype3
 *
 *	enum ftype3 {
 *		NF3WEG	= 1,
 *		NF3DIW	= 2,
 *		NF3BWK	= 3,
 *		NF3CHW	= 4,
 *		NF3WNK	= 5,
 *		NF3SOCK	= 6,
 *		NF3FIFO	= 7
 *	};
 */
static void encode_ftype3(stwuct xdw_stweam *xdw, const u32 type)
{
	encode_uint32(xdw, type);
}

static __be32 *xdw_decode_ftype3(__be32 *p, umode_t *mode)
{
	u32 type;

	type = be32_to_cpup(p++);
	if (type > NF3FIFO)
		type = NF3NON;
	*mode = nfs_type2fmt[type];
	wetuwn p;
}

/*
 * specdata3
 *
 *     stwuct specdata3 {
 *             uint32  specdata1;
 *             uint32  specdata2;
 *     };
 */
static void encode_specdata3(stwuct xdw_stweam *xdw, const dev_t wdev)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 8);
	*p++ = cpu_to_be32(MAJOW(wdev));
	*p = cpu_to_be32(MINOW(wdev));
}

static __be32 *xdw_decode_specdata3(__be32 *p, dev_t *wdev)
{
	unsigned int majow, minow;

	majow = be32_to_cpup(p++);
	minow = be32_to_cpup(p++);
	*wdev = MKDEV(majow, minow);
	if (MAJOW(*wdev) != majow || MINOW(*wdev) != minow)
		*wdev = 0;
	wetuwn p;
}

/*
 * nfs_fh3
 *
 *	stwuct nfs_fh3 {
 *		opaque       data<NFS3_FHSIZE>;
 *	};
 */
static void encode_nfs_fh3(stwuct xdw_stweam *xdw, const stwuct nfs_fh *fh)
{
	__be32 *p;

	WAWN_ON_ONCE(fh->size > NFS3_FHSIZE);
	p = xdw_wesewve_space(xdw, 4 + fh->size);
	xdw_encode_opaque(p, fh->data, fh->size);
}

static int decode_nfs_fh3(stwuct xdw_stweam *xdw, stwuct nfs_fh *fh)
{
	u32 wength;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wength = be32_to_cpup(p++);
	if (unwikewy(wength > NFS3_FHSIZE || wength == 0))
		goto out_toobig;
	p = xdw_inwine_decode(xdw, wength);
	if (unwikewy(!p))
		wetuwn -EIO;
	fh->size = wength;
	memcpy(fh->data, p, wength);
	wetuwn 0;
out_toobig:
	twace_nfs_xdw_bad_fiwehandwe(xdw, NFSEWW_BADHANDWE);
	wetuwn -E2BIG;
}

static void zewo_nfs_fh3(stwuct nfs_fh *fh)
{
	memset(fh, 0, sizeof(*fh));
}

/*
 * nfstime3
 *
 *	stwuct nfstime3 {
 *		uint32	seconds;
 *		uint32	nseconds;
 *	};
 */
static __be32 *xdw_encode_nfstime3(__be32 *p, const stwuct timespec64 *timep)
{
	*p++ = cpu_to_be32((u32)timep->tv_sec);
	*p++ = cpu_to_be32(timep->tv_nsec);
	wetuwn p;
}

static __be32 *xdw_decode_nfstime3(__be32 *p, stwuct timespec64 *timep)
{
	timep->tv_sec = be32_to_cpup(p++);
	timep->tv_nsec = be32_to_cpup(p++);
	wetuwn p;
}

/*
 * sattw3
 *
 *	enum time_how {
 *		DONT_CHANGE		= 0,
 *		SET_TO_SEWVEW_TIME	= 1,
 *		SET_TO_CWIENT_TIME	= 2
 *	};
 *
 *	union set_mode3 switch (boow set_it) {
 *	case TWUE:
 *		mode3	mode;
 *	defauwt:
 *		void;
 *	};
 *
 *	union set_uid3 switch (boow set_it) {
 *	case TWUE:
 *		uid3	uid;
 *	defauwt:
 *		void;
 *	};
 *
 *	union set_gid3 switch (boow set_it) {
 *	case TWUE:
 *		gid3	gid;
 *	defauwt:
 *		void;
 *	};
 *
 *	union set_size3 switch (boow set_it) {
 *	case TWUE:
 *		size3	size;
 *	defauwt:
 *		void;
 *	};
 *
 *	union set_atime switch (time_how set_it) {
 *	case SET_TO_CWIENT_TIME:
 *		nfstime3	atime;
 *	defauwt:
 *		void;
 *	};
 *
 *	union set_mtime switch (time_how set_it) {
 *	case SET_TO_CWIENT_TIME:
 *		nfstime3  mtime;
 *	defauwt:
 *		void;
 *	};
 *
 *	stwuct sattw3 {
 *		set_mode3	mode;
 *		set_uid3	uid;
 *		set_gid3	gid;
 *		set_size3	size;
 *		set_atime	atime;
 *		set_mtime	mtime;
 *	};
 */
static void encode_sattw3(stwuct xdw_stweam *xdw, const stwuct iattw *attw,
		stwuct usew_namespace *usewns)
{
	u32 nbytes;
	__be32 *p;

	/*
	 * In owdew to make onwy a singwe xdw_wesewve_space() caww,
	 * pwe-compute the totaw numbew of bytes to be wesewved.
	 * Six boowean vawues, one fow each set_foo fiewd, awe awways
	 * pwesent in the encoded wesuwt, so stawt thewe.
	 */
	nbytes = 6 * 4;
	if (attw->ia_vawid & ATTW_MODE)
		nbytes += 4;
	if (attw->ia_vawid & ATTW_UID)
		nbytes += 4;
	if (attw->ia_vawid & ATTW_GID)
		nbytes += 4;
	if (attw->ia_vawid & ATTW_SIZE)
		nbytes += 8;
	if (attw->ia_vawid & ATTW_ATIME_SET)
		nbytes += 8;
	if (attw->ia_vawid & ATTW_MTIME_SET)
		nbytes += 8;
	p = xdw_wesewve_space(xdw, nbytes);

	if (attw->ia_vawid & ATTW_MODE) {
		*p++ = xdw_one;
		*p++ = cpu_to_be32(attw->ia_mode & S_IAWWUGO);
	} ewse
		*p++ = xdw_zewo;

	if (attw->ia_vawid & ATTW_UID) {
		*p++ = xdw_one;
		*p++ = cpu_to_be32(fwom_kuid_munged(usewns, attw->ia_uid));
	} ewse
		*p++ = xdw_zewo;

	if (attw->ia_vawid & ATTW_GID) {
		*p++ = xdw_one;
		*p++ = cpu_to_be32(fwom_kgid_munged(usewns, attw->ia_gid));
	} ewse
		*p++ = xdw_zewo;

	if (attw->ia_vawid & ATTW_SIZE) {
		*p++ = xdw_one;
		p = xdw_encode_hypew(p, (u64)attw->ia_size);
	} ewse
		*p++ = xdw_zewo;

	if (attw->ia_vawid & ATTW_ATIME_SET) {
		*p++ = xdw_two;
		p = xdw_encode_nfstime3(p, &attw->ia_atime);
	} ewse if (attw->ia_vawid & ATTW_ATIME) {
		*p++ = xdw_one;
	} ewse
		*p++ = xdw_zewo;

	if (attw->ia_vawid & ATTW_MTIME_SET) {
		*p++ = xdw_two;
		xdw_encode_nfstime3(p, &attw->ia_mtime);
	} ewse if (attw->ia_vawid & ATTW_MTIME) {
		*p = xdw_one;
	} ewse
		*p = xdw_zewo;
}

/*
 * fattw3
 *
 *	stwuct fattw3 {
 *		ftype3		type;
 *		mode3		mode;
 *		uint32		nwink;
 *		uid3		uid;
 *		gid3		gid;
 *		size3		size;
 *		size3		used;
 *		specdata3	wdev;
 *		uint64		fsid;
 *		fiweid3		fiweid;
 *		nfstime3	atime;
 *		nfstime3	mtime;
 *		nfstime3	ctime;
 *	};
 */
static int decode_fattw3(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw,
		stwuct usew_namespace *usewns)
{
	umode_t fmode;
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS3_fattw_sz << 2);
	if (unwikewy(!p))
		wetuwn -EIO;

	p = xdw_decode_ftype3(p, &fmode);

	fattw->mode = (be32_to_cpup(p++) & ~S_IFMT) | fmode;
	fattw->nwink = be32_to_cpup(p++);
	fattw->uid = make_kuid(usewns, be32_to_cpup(p++));
	if (!uid_vawid(fattw->uid))
		goto out_uid;
	fattw->gid = make_kgid(usewns, be32_to_cpup(p++));
	if (!gid_vawid(fattw->gid))
		goto out_gid;

	p = xdw_decode_size3(p, &fattw->size);
	p = xdw_decode_size3(p, &fattw->du.nfs3.used);
	p = xdw_decode_specdata3(p, &fattw->wdev);

	p = xdw_decode_hypew(p, &fattw->fsid.majow);
	fattw->fsid.minow = 0;

	p = xdw_decode_fiweid3(p, &fattw->fiweid);
	p = xdw_decode_nfstime3(p, &fattw->atime);
	p = xdw_decode_nfstime3(p, &fattw->mtime);
	xdw_decode_nfstime3(p, &fattw->ctime);
	fattw->change_attw = nfs_timespec_to_change_attw(&fattw->ctime);

	fattw->vawid |= NFS_ATTW_FATTW_V3;
	wetuwn 0;
out_uid:
	dpwintk("NFS: wetuwned invawid uid\n");
	wetuwn -EINVAW;
out_gid:
	dpwintk("NFS: wetuwned invawid gid\n");
	wetuwn -EINVAW;
}

/*
 * post_op_attw
 *
 *	union post_op_attw switch (boow attwibutes_fowwow) {
 *	case TWUE:
 *		fattw3	attwibutes;
 *	case FAWSE:
 *		void;
 *	};
 */
static int decode_post_op_attw(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw,
		stwuct usew_namespace *usewns)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	if (*p != xdw_zewo)
		wetuwn decode_fattw3(xdw, fattw, usewns);
	wetuwn 0;
}

/*
 * wcc_attw
 *	stwuct wcc_attw {
 *		size3		size;
 *		nfstime3	mtime;
 *		nfstime3	ctime;
 *	};
 */
static int decode_wcc_attw(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, NFS3_wcc_attw_sz << 2);
	if (unwikewy(!p))
		wetuwn -EIO;

	fattw->vawid |= NFS_ATTW_FATTW_PWESIZE
		| NFS_ATTW_FATTW_PWECHANGE
		| NFS_ATTW_FATTW_PWEMTIME
		| NFS_ATTW_FATTW_PWECTIME;

	p = xdw_decode_size3(p, &fattw->pwe_size);
	p = xdw_decode_nfstime3(p, &fattw->pwe_mtime);
	xdw_decode_nfstime3(p, &fattw->pwe_ctime);
	fattw->pwe_change_attw = nfs_timespec_to_change_attw(&fattw->pwe_ctime);

	wetuwn 0;
}

/*
 * pwe_op_attw
 *	union pwe_op_attw switch (boow attwibutes_fowwow) {
 *	case TWUE:
 *		wcc_attw	attwibutes;
 *	case FAWSE:
 *		void;
 *	};
 *
 * wcc_data
 *
 *	stwuct wcc_data {
 *		pwe_op_attw	befowe;
 *		post_op_attw	aftew;
 *	};
 */
static int decode_pwe_op_attw(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	if (*p != xdw_zewo)
		wetuwn decode_wcc_attw(xdw, fattw);
	wetuwn 0;
}

static int decode_wcc_data(stwuct xdw_stweam *xdw, stwuct nfs_fattw *fattw,
		stwuct usew_namespace *usewns)
{
	int ewwow;

	ewwow = decode_pwe_op_attw(xdw, fattw);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, fattw, usewns);
out:
	wetuwn ewwow;
}

/*
 * post_op_fh3
 *
 *	union post_op_fh3 switch (boow handwe_fowwows) {
 *	case TWUE:
 *		nfs_fh3  handwe;
 *	case FAWSE:
 *		void;
 *	};
 */
static int decode_post_op_fh3(stwuct xdw_stweam *xdw, stwuct nfs_fh *fh)
{
	__be32 *p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	if (*p != xdw_zewo)
		wetuwn decode_nfs_fh3(xdw, fh);
	zewo_nfs_fh3(fh);
	wetuwn 0;
}

/*
 * diwopawgs3
 *
 *	stwuct diwopawgs3 {
 *		nfs_fh3		diw;
 *		fiwename3	name;
 *	};
 */
static void encode_diwopawgs3(stwuct xdw_stweam *xdw, const stwuct nfs_fh *fh,
			      const chaw *name, u32 wength)
{
	encode_nfs_fh3(xdw, fh);
	encode_fiwename3(xdw, name, wength);
}


/*
 * NFSv3 XDW encode functions
 *
 * NFSv3 awgument types awe defined in section 3.3 of WFC 1813:
 * "NFS Vewsion 3 Pwotocow Specification".
 */

/*
 * 3.3.1  GETATTW3awgs
 *
 *	stwuct GETATTW3awgs {
 *		nfs_fh3  object;
 *	};
 */
static void nfs3_xdw_enc_getattw3awgs(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs_fh *fh = data;

	encode_nfs_fh3(xdw, fh);
}

/*
 * 3.3.2  SETATTW3awgs
 *
 *	union sattwguawd3 switch (boow check) {
 *	case TWUE:
 *		nfstime3  obj_ctime;
 *	case FAWSE:
 *		void;
 *	};
 *
 *	stwuct SETATTW3awgs {
 *		nfs_fh3		object;
 *		sattw3		new_attwibutes;
 *		sattwguawd3	guawd;
 *	};
 */
static void encode_sattwguawd3(stwuct xdw_stweam *xdw,
			       const stwuct nfs3_sattwawgs *awgs)
{
	__be32 *p;

	if (awgs->guawd) {
		p = xdw_wesewve_space(xdw, 4 + 8);
		*p++ = xdw_one;
		xdw_encode_nfstime3(p, &awgs->guawdtime);
	} ewse {
		p = xdw_wesewve_space(xdw, 4);
		*p = xdw_zewo;
	}
}

static void nfs3_xdw_enc_setattw3awgs(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs3_sattwawgs *awgs = data;
	encode_nfs_fh3(xdw, awgs->fh);
	encode_sattw3(xdw, awgs->sattw, wpc_wqst_usewns(weq));
	encode_sattwguawd3(xdw, awgs);
}

/*
 * 3.3.3  WOOKUP3awgs
 *
 *	stwuct WOOKUP3awgs {
 *		diwopawgs3  what;
 *	};
 */
static void nfs3_xdw_enc_wookup3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs3_diwopawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fh, awgs->name, awgs->wen);
}

/*
 * 3.3.4  ACCESS3awgs
 *
 *	stwuct ACCESS3awgs {
 *		nfs_fh3		object;
 *		uint32		access;
 *	};
 */
static void encode_access3awgs(stwuct xdw_stweam *xdw,
			       const stwuct nfs3_accessawgs *awgs)
{
	encode_nfs_fh3(xdw, awgs->fh);
	encode_uint32(xdw, awgs->access);
}

static void nfs3_xdw_enc_access3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs3_accessawgs *awgs = data;

	encode_access3awgs(xdw, awgs);
}

/*
 * 3.3.5  WEADWINK3awgs
 *
 *	stwuct WEADWINK3awgs {
 *		nfs_fh3	symwink;
 *	};
 */
static void nfs3_xdw_enc_weadwink3awgs(stwuct wpc_wqst *weq,
				       stwuct xdw_stweam *xdw,
				       const void *data)
{
	const stwuct nfs3_weadwinkawgs *awgs = data;

	encode_nfs_fh3(xdw, awgs->fh);
	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase, awgs->pgwen,
				NFS3_weadwinkwes_sz - NFS3_pagepad_sz);
}

/*
 * 3.3.6  WEAD3awgs
 *
 *	stwuct WEAD3awgs {
 *		nfs_fh3		fiwe;
 *		offset3		offset;
 *		count3		count;
 *	};
 */
static void encode_wead3awgs(stwuct xdw_stweam *xdw,
			     const stwuct nfs_pgio_awgs *awgs)
{
	__be32 *p;

	encode_nfs_fh3(xdw, awgs->fh);

	p = xdw_wesewve_space(xdw, 8 + 4);
	p = xdw_encode_hypew(p, awgs->offset);
	*p = cpu_to_be32(awgs->count);
}

static void nfs3_xdw_enc_wead3awgs(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfs_pgio_awgs *awgs = data;
	unsigned int wepwen = awgs->wepwen ? awgs->wepwen :
					     NFS3_weadwes_sz - NFS3_pagepad_sz;

	encode_wead3awgs(xdw, awgs);
	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase,
				awgs->count, wepwen);
	weq->wq_wcv_buf.fwags |= XDWBUF_WEAD;
}

/*
 * 3.3.7  WWITE3awgs
 *
 *	enum stabwe_how {
 *		UNSTABWE  = 0,
 *		DATA_SYNC = 1,
 *		FIWE_SYNC = 2
 *	};
 *
 *	stwuct WWITE3awgs {
 *		nfs_fh3		fiwe;
 *		offset3		offset;
 *		count3		count;
 *		stabwe_how	stabwe;
 *		opaque		data<>;
 *	};
 */
static void encode_wwite3awgs(stwuct xdw_stweam *xdw,
			      const stwuct nfs_pgio_awgs *awgs)
{
	__be32 *p;

	encode_nfs_fh3(xdw, awgs->fh);

	p = xdw_wesewve_space(xdw, 8 + 4 + 4 + 4);
	p = xdw_encode_hypew(p, awgs->offset);
	*p++ = cpu_to_be32(awgs->count);
	*p++ = cpu_to_be32(awgs->stabwe);
	*p = cpu_to_be32(awgs->count);
	xdw_wwite_pages(xdw, awgs->pages, awgs->pgbase, awgs->count);
}

static void nfs3_xdw_enc_wwite3awgs(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    const void *data)
{
	const stwuct nfs_pgio_awgs *awgs = data;

	encode_wwite3awgs(xdw, awgs);
	xdw->buf->fwags |= XDWBUF_WWITE;
}

/*
 * 3.3.8  CWEATE3awgs
 *
 *	enum cweatemode3 {
 *		UNCHECKED = 0,
 *		GUAWDED   = 1,
 *		EXCWUSIVE = 2
 *	};
 *
 *	union cweatehow3 switch (cweatemode3 mode) {
 *	case UNCHECKED:
 *	case GUAWDED:
 *		sattw3       obj_attwibutes;
 *	case EXCWUSIVE:
 *		cweatevewf3  vewf;
 *	};
 *
 *	stwuct CWEATE3awgs {
 *		diwopawgs3	whewe;
 *		cweatehow3	how;
 *	};
 */
static void encode_cweatehow3(stwuct xdw_stweam *xdw,
			      const stwuct nfs3_cweateawgs *awgs,
			      stwuct usew_namespace *usewns)
{
	encode_uint32(xdw, awgs->cweatemode);
	switch (awgs->cweatemode) {
	case NFS3_CWEATE_UNCHECKED:
	case NFS3_CWEATE_GUAWDED:
		encode_sattw3(xdw, awgs->sattw, usewns);
		bweak;
	case NFS3_CWEATE_EXCWUSIVE:
		encode_cweatevewf3(xdw, awgs->vewifiew);
		bweak;
	defauwt:
		BUG();
	}
}

static void nfs3_xdw_enc_cweate3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs3_cweateawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fh, awgs->name, awgs->wen);
	encode_cweatehow3(xdw, awgs, wpc_wqst_usewns(weq));
}

/*
 * 3.3.9  MKDIW3awgs
 *
 *	stwuct MKDIW3awgs {
 *		diwopawgs3	whewe;
 *		sattw3		attwibutes;
 *	};
 */
static void nfs3_xdw_enc_mkdiw3awgs(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    const void *data)
{
	const stwuct nfs3_mkdiwawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fh, awgs->name, awgs->wen);
	encode_sattw3(xdw, awgs->sattw, wpc_wqst_usewns(weq));
}

/*
 * 3.3.10  SYMWINK3awgs
 *
 *	stwuct symwinkdata3 {
 *		sattw3		symwink_attwibutes;
 *		nfspath3	symwink_data;
 *	};
 *
 *	stwuct SYMWINK3awgs {
 *		diwopawgs3	whewe;
 *		symwinkdata3	symwink;
 *	};
 */
static void encode_symwinkdata3(stwuct xdw_stweam *xdw,
				const void *data,
				stwuct usew_namespace *usewns)
{
	const stwuct nfs3_symwinkawgs *awgs = data;

	encode_sattw3(xdw, awgs->sattw, usewns);
	encode_nfspath3(xdw, awgs->pages, awgs->pathwen);
}

static void nfs3_xdw_enc_symwink3awgs(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs3_symwinkawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fwomfh, awgs->fwomname, awgs->fwomwen);
	encode_symwinkdata3(xdw, awgs, wpc_wqst_usewns(weq));
	xdw->buf->fwags |= XDWBUF_WWITE;
}

/*
 * 3.3.11  MKNOD3awgs
 *
 *	stwuct devicedata3 {
 *		sattw3		dev_attwibutes;
 *		specdata3	spec;
 *	};
 *
 *	union mknoddata3 switch (ftype3 type) {
 *	case NF3CHW:
 *	case NF3BWK:
 *		devicedata3	device;
 *	case NF3SOCK:
 *	case NF3FIFO:
 *		sattw3		pipe_attwibutes;
 *	defauwt:
 *		void;
 *	};
 *
 *	stwuct MKNOD3awgs {
 *		diwopawgs3	whewe;
 *		mknoddata3	what;
 *	};
 */
static void encode_devicedata3(stwuct xdw_stweam *xdw,
			       const stwuct nfs3_mknodawgs *awgs,
			       stwuct usew_namespace *usewns)
{
	encode_sattw3(xdw, awgs->sattw, usewns);
	encode_specdata3(xdw, awgs->wdev);
}

static void encode_mknoddata3(stwuct xdw_stweam *xdw,
			      const stwuct nfs3_mknodawgs *awgs,
			      stwuct usew_namespace *usewns)
{
	encode_ftype3(xdw, awgs->type);
	switch (awgs->type) {
	case NF3CHW:
	case NF3BWK:
		encode_devicedata3(xdw, awgs, usewns);
		bweak;
	case NF3SOCK:
	case NF3FIFO:
		encode_sattw3(xdw, awgs->sattw, usewns);
		bweak;
	case NF3WEG:
	case NF3DIW:
		bweak;
	defauwt:
		BUG();
	}
}

static void nfs3_xdw_enc_mknod3awgs(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    const void *data)
{
	const stwuct nfs3_mknodawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fh, awgs->name, awgs->wen);
	encode_mknoddata3(xdw, awgs, wpc_wqst_usewns(weq));
}

/*
 * 3.3.12  WEMOVE3awgs
 *
 *	stwuct WEMOVE3awgs {
 *		diwopawgs3  object;
 *	};
 */
static void nfs3_xdw_enc_wemove3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs_wemoveawgs *awgs = data;

	encode_diwopawgs3(xdw, awgs->fh, awgs->name.name, awgs->name.wen);
}

/*
 * 3.3.14  WENAME3awgs
 *
 *	stwuct WENAME3awgs {
 *		diwopawgs3	fwom;
 *		diwopawgs3	to;
 *	};
 */
static void nfs3_xdw_enc_wename3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs_wenameawgs *awgs = data;
	const stwuct qstw *owd = awgs->owd_name;
	const stwuct qstw *new = awgs->new_name;

	encode_diwopawgs3(xdw, awgs->owd_diw, owd->name, owd->wen);
	encode_diwopawgs3(xdw, awgs->new_diw, new->name, new->wen);
}

/*
 * 3.3.15  WINK3awgs
 *
 *	stwuct WINK3awgs {
 *		nfs_fh3		fiwe;
 *		diwopawgs3	wink;
 *	};
 */
static void nfs3_xdw_enc_wink3awgs(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfs3_winkawgs *awgs = data;

	encode_nfs_fh3(xdw, awgs->fwomfh);
	encode_diwopawgs3(xdw, awgs->tofh, awgs->toname, awgs->towen);
}

/*
 * 3.3.16  WEADDIW3awgs
 *
 *	stwuct WEADDIW3awgs {
 *		nfs_fh3		diw;
 *		cookie3		cookie;
 *		cookievewf3	cookievewf;
 *		count3		count;
 *	};
 */
static void encode_weaddiw3awgs(stwuct xdw_stweam *xdw,
				const stwuct nfs3_weaddiwawgs *awgs)
{
	__be32 *p;

	encode_nfs_fh3(xdw, awgs->fh);

	p = xdw_wesewve_space(xdw, 8 + NFS3_COOKIEVEWFSIZE + 4);
	p = xdw_encode_cookie3(p, awgs->cookie);
	p = xdw_encode_cookievewf3(p, awgs->vewf);
	*p = cpu_to_be32(awgs->count);
}

static void nfs3_xdw_enc_weaddiw3awgs(stwuct wpc_wqst *weq,
				      stwuct xdw_stweam *xdw,
				      const void *data)
{
	const stwuct nfs3_weaddiwawgs *awgs = data;

	encode_weaddiw3awgs(xdw, awgs);
	wpc_pwepawe_wepwy_pages(weq, awgs->pages, 0, awgs->count,
				NFS3_weaddiwwes_sz - NFS3_pagepad_sz);
}

/*
 * 3.3.17  WEADDIWPWUS3awgs
 *
 *	stwuct WEADDIWPWUS3awgs {
 *		nfs_fh3		diw;
 *		cookie3		cookie;
 *		cookievewf3	cookievewf;
 *		count3		diwcount;
 *		count3		maxcount;
 *	};
 */
static void encode_weaddiwpwus3awgs(stwuct xdw_stweam *xdw,
				    const stwuct nfs3_weaddiwawgs *awgs)
{
	uint32_t diwcount = awgs->count;
	uint32_t maxcount = awgs->count;
	__be32 *p;

	encode_nfs_fh3(xdw, awgs->fh);

	p = xdw_wesewve_space(xdw, 8 + NFS3_COOKIEVEWFSIZE + 4 + 4);
	p = xdw_encode_cookie3(p, awgs->cookie);
	p = xdw_encode_cookievewf3(p, awgs->vewf);

	/*
	 * weaddiwpwus: need diwcount + buffew size.
	 * We just make suwe we make diwcount big enough
	 */
	*p++ = cpu_to_be32(diwcount);
	*p = cpu_to_be32(maxcount);
}

static void nfs3_xdw_enc_weaddiwpwus3awgs(stwuct wpc_wqst *weq,
					  stwuct xdw_stweam *xdw,
					  const void *data)
{
	const stwuct nfs3_weaddiwawgs *awgs = data;

	encode_weaddiwpwus3awgs(xdw, awgs);
	wpc_pwepawe_wepwy_pages(weq, awgs->pages, 0, awgs->count,
				NFS3_weaddiwwes_sz - NFS3_pagepad_sz);
}

/*
 * 3.3.21  COMMIT3awgs
 *
 *	stwuct COMMIT3awgs {
 *		nfs_fh3		fiwe;
 *		offset3		offset;
 *		count3		count;
 *	};
 */
static void encode_commit3awgs(stwuct xdw_stweam *xdw,
			       const stwuct nfs_commitawgs *awgs)
{
	__be32 *p;

	encode_nfs_fh3(xdw, awgs->fh);

	p = xdw_wesewve_space(xdw, 8 + 4);
	p = xdw_encode_hypew(p, awgs->offset);
	*p = cpu_to_be32(awgs->count);
}

static void nfs3_xdw_enc_commit3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs_commitawgs *awgs = data;

	encode_commit3awgs(xdw, awgs);
}

#ifdef CONFIG_NFS_V3_ACW

static void nfs3_xdw_enc_getacw3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs3_getacwawgs *awgs = data;

	encode_nfs_fh3(xdw, awgs->fh);
	encode_uint32(xdw, awgs->mask);
	if (awgs->mask & (NFS_ACW | NFS_DFACW)) {
		wpc_pwepawe_wepwy_pages(weq, awgs->pages, 0,
					NFSACW_MAXPAGES << PAGE_SHIFT,
					ACW3_getacwwes_sz - NFS3_pagepad_sz);
		weq->wq_wcv_buf.fwags |= XDWBUF_SPAWSE_PAGES;
	}
}

static void nfs3_xdw_enc_setacw3awgs(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs3_setacwawgs *awgs = data;
	unsigned int base;
	int ewwow;

	encode_nfs_fh3(xdw, NFS_FH(awgs->inode));
	encode_uint32(xdw, awgs->mask);

	base = weq->wq_swen;
	if (awgs->npages != 0)
		xdw_wwite_pages(xdw, awgs->pages, 0, awgs->wen);
	ewse
		xdw_wesewve_space(xdw, awgs->wen);

	ewwow = nfsacw_encode(xdw->buf, base, awgs->inode,
			    (awgs->mask & NFS_ACW) ?
			    awgs->acw_access : NUWW, 1, 0);
	/* FIXME: this is just bwoken */
	BUG_ON(ewwow < 0);
	ewwow = nfsacw_encode(xdw->buf, base + ewwow, awgs->inode,
			    (awgs->mask & NFS_DFACW) ?
			    awgs->acw_defauwt : NUWW, 1,
			    NFS_ACW_DEFAUWT);
	BUG_ON(ewwow < 0);
}

#endif  /* CONFIG_NFS_V3_ACW */

/*
 * NFSv3 XDW decode functions
 *
 * NFSv3 wesuwt types awe defined in section 3.3 of WFC 1813:
 * "NFS Vewsion 3 Pwotocow Specification".
 */

/*
 * 3.3.1  GETATTW3wes
 *
 *	stwuct GETATTW3wesok {
 *		fattw3		obj_attwibutes;
 *	};
 *
 *	union GETATTW3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		GETATTW3wesok  wesok;
 *	defauwt:
 *		void;
 *	};
 */
static int nfs3_xdw_dec_getattw3wes(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    void *wesuwt)
{
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_fattw3(xdw, wesuwt, wpc_wqst_usewns(weq));
out:
	wetuwn ewwow;
out_defauwt:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.2  SETATTW3wes
 *
 *	stwuct SETATTW3wesok {
 *		wcc_data  obj_wcc;
 *	};
 *
 *	stwuct SETATTW3wesfaiw {
 *		wcc_data  obj_wcc;
 *	};
 *
 *	union SETATTW3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		SETATTW3wesok   wesok;
 *	defauwt:
 *		SETATTW3wesfaiw wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_setattw3wes(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    void *wesuwt)
{
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.3  WOOKUP3wes
 *
 *	stwuct WOOKUP3wesok {
 *		nfs_fh3		object;
 *		post_op_attw	obj_attwibutes;
 *		post_op_attw	diw_attwibutes;
 *	};
 *
 *	stwuct WOOKUP3wesfaiw {
 *		post_op_attw	diw_attwibutes;
 *	};
 *
 *	union WOOKUP3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WOOKUP3wesok	wesok;
 *	defauwt:
 *		WOOKUP3wesfaiw	wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_wookup3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct usew_namespace *usewns = wpc_wqst_usewns(weq);
	stwuct nfs3_diwopwes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_nfs_fh3(xdw, wesuwt->fh);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->diw_attw, usewns);
out:
	wetuwn ewwow;
out_defauwt:
	ewwow = decode_post_op_attw(xdw, wesuwt->diw_attw, usewns);
	if (unwikewy(ewwow))
		goto out;
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.4  ACCESS3wes
 *
 *	stwuct ACCESS3wesok {
 *		post_op_attw	obj_attwibutes;
 *		uint32		access;
 *	};
 *
 *	stwuct ACCESS3wesfaiw {
 *		post_op_attw	obj_attwibutes;
 *	};
 *
 *	union ACCESS3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		ACCESS3wesok	wesok;
 *	defauwt:
 *		ACCESS3wesfaiw	wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_access3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs3_accesswes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_uint32(xdw, &wesuwt->access);
out:
	wetuwn ewwow;
out_defauwt:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.5  WEADWINK3wes
 *
 *	stwuct WEADWINK3wesok {
 *		post_op_attw	symwink_attwibutes;
 *		nfspath3	data;
 *	};
 *
 *	stwuct WEADWINK3wesfaiw {
 *		post_op_attw	symwink_attwibutes;
 *	};
 *
 *	union WEADWINK3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WEADWINK3wesok	wesok;
 *	defauwt:
 *		WEADWINK3wesfaiw wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_weadwink3wes(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     void *wesuwt)
{
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_nfspath3(xdw);
out:
	wetuwn ewwow;
out_defauwt:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.6  WEAD3wes
 *
 *	stwuct WEAD3wesok {
 *		post_op_attw	fiwe_attwibutes;
 *		count3		count;
 *		boow		eof;
 *		opaque		data<>;
 *	};
 *
 *	stwuct WEAD3wesfaiw {
 *		post_op_attw	fiwe_attwibutes;
 *	};
 *
 *	union WEAD3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WEAD3wesok	wesok;
 *	defauwt:
 *		WEAD3wesfaiw	wesfaiw;
 *	};
 */
static int decode_wead3wesok(stwuct xdw_stweam *xdw,
			     stwuct nfs_pgio_wes *wesuwt)
{
	u32 eof, count, ocount, wecvd;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 + 4 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	count = be32_to_cpup(p++);
	eof = be32_to_cpup(p++);
	ocount = be32_to_cpup(p++);
	if (unwikewy(ocount != count))
		goto out_mismatch;
	wecvd = xdw_wead_pages(xdw, count);
	if (unwikewy(count > wecvd))
		goto out_cheating;
out:
	wesuwt->eof = eof;
	wesuwt->count = count;
	wetuwn count;
out_mismatch:
	dpwintk("NFS: WEAD count doesn't match wength of opaque: "
		"count %u != ocount %u\n", count, ocount);
	wetuwn -EIO;
out_cheating:
	dpwintk("NFS: sewvew cheating in wead wesuwt: "
		"count %u > wecvd %u\n", count, wecvd);
	count = wecvd;
	eof = 0;
	goto out;
}

static int nfs3_xdw_dec_wead3wes(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct nfs_pgio_wes *wesuwt = data;
	unsigned int pos;
	enum nfs_stat status;
	int ewwow;

	pos = xdw_stweam_pos(xdw);
	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	wesuwt->op_status = status;
	if (status != NFS3_OK)
		goto out_status;
	wesuwt->wepwen = 3 + ((xdw_stweam_pos(xdw) - pos) >> 2);
	ewwow = decode_wead3wesok(xdw, wesuwt);
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.7  WWITE3wes
 *
 *	enum stabwe_how {
 *		UNSTABWE  = 0,
 *		DATA_SYNC = 1,
 *		FIWE_SYNC = 2
 *	};
 *
 *	stwuct WWITE3wesok {
 *		wcc_data	fiwe_wcc;
 *		count3		count;
 *		stabwe_how	committed;
 *		wwitevewf3	vewf;
 *	};
 *
 *	stwuct WWITE3wesfaiw {
 *		wcc_data	fiwe_wcc;
 *	};
 *
 *	union WWITE3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WWITE3wesok	wesok;
 *	defauwt:
 *		WWITE3wesfaiw	wesfaiw;
 *	};
 */
static int decode_wwite3wesok(stwuct xdw_stweam *xdw,
			      stwuct nfs_pgio_wes *wesuwt)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wesuwt->count = be32_to_cpup(p++);
	wesuwt->vewf->committed = be32_to_cpup(p++);
	if (unwikewy(wesuwt->vewf->committed > NFS_FIWE_SYNC))
		goto out_badvawue;
	if (decode_wwitevewf3(xdw, &wesuwt->vewf->vewifiew))
		wetuwn -EIO;
	wetuwn wesuwt->count;
out_badvawue:
	dpwintk("NFS: bad stabwe_how vawue: %u\n", wesuwt->vewf->committed);
	wetuwn -EIO;
}

static int nfs3_xdw_dec_wwite3wes(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfs_pgio_wes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	wesuwt->op_status = status;
	if (status != NFS3_OK)
		goto out_status;
	ewwow = decode_wwite3wesok(xdw, wesuwt);
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.8  CWEATE3wes
 *
 *	stwuct CWEATE3wesok {
 *		post_op_fh3	obj;
 *		post_op_attw	obj_attwibutes;
 *		wcc_data	diw_wcc;
 *	};
 *
 *	stwuct CWEATE3wesfaiw {
 *		wcc_data	diw_wcc;
 *	};
 *
 *	union CWEATE3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		CWEATE3wesok	wesok;
 *	defauwt:
 *		CWEATE3wesfaiw	wesfaiw;
 *	};
 */
static int decode_cweate3wesok(stwuct xdw_stweam *xdw,
			       stwuct nfs3_diwopwes *wesuwt,
			       stwuct usew_namespace *usewns)
{
	int ewwow;

	ewwow = decode_post_op_fh3(xdw, wesuwt->fh);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	/* The sewvew isn't wequiwed to wetuwn a fiwe handwe.
	 * If it didn't, fowce the cwient to pewfowm a WOOKUP
	 * to detewmine the cowwect fiwe handwe and attwibute
	 * vawues fow the new object. */
	if (wesuwt->fh->size == 0)
		wesuwt->fattw->vawid = 0;
	ewwow = decode_wcc_data(xdw, wesuwt->diw_attw, usewns);
out:
	wetuwn ewwow;
}

static int nfs3_xdw_dec_cweate3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct usew_namespace *usewns = wpc_wqst_usewns(weq);
	stwuct nfs3_diwopwes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_cweate3wesok(xdw, wesuwt, usewns);
out:
	wetuwn ewwow;
out_defauwt:
	ewwow = decode_wcc_data(xdw, wesuwt->diw_attw, usewns);
	if (unwikewy(ewwow))
		goto out;
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.12  WEMOVE3wes
 *
 *	stwuct WEMOVE3wesok {
 *		wcc_data    diw_wcc;
 *	};
 *
 *	stwuct WEMOVE3wesfaiw {
 *		wcc_data    diw_wcc;
 *	};
 *
 *	union WEMOVE3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WEMOVE3wesok   wesok;
 *	defauwt:
 *		WEMOVE3wesfaiw wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_wemove3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs_wemovewes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->diw_attw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.14  WENAME3wes
 *
 *	stwuct WENAME3wesok {
 *		wcc_data	fwomdiw_wcc;
 *		wcc_data	todiw_wcc;
 *	};
 *
 *	stwuct WENAME3wesfaiw {
 *		wcc_data	fwomdiw_wcc;
 *		wcc_data	todiw_wcc;
 *	};
 *
 *	union WENAME3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WENAME3wesok   wesok;
 *	defauwt:
 *		WENAME3wesfaiw wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_wename3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct usew_namespace *usewns = wpc_wqst_usewns(weq);
	stwuct nfs_wenamewes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->owd_fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->new_fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.15  WINK3wes
 *
 *	stwuct WINK3wesok {
 *		post_op_attw	fiwe_attwibutes;
 *		wcc_data	winkdiw_wcc;
 *	};
 *
 *	stwuct WINK3wesfaiw {
 *		post_op_attw	fiwe_attwibutes;
 *		wcc_data	winkdiw_wcc;
 *	};
 *
 *	union WINK3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WINK3wesok	wesok;
 *	defauwt:
 *		WINK3wesfaiw	wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_wink3wes(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct usew_namespace *usewns = wpc_wqst_usewns(weq);
	stwuct nfs3_winkwes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->diw_attw, usewns);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/**
 * nfs3_decode_diwent - Decode a singwe NFSv3 diwectowy entwy stowed in
 *			the wocaw page cache
 * @xdw: XDW stweam whewe entwy wesides
 * @entwy: buffew to fiww in with entwy data
 * @pwus: boowean indicating whethew this shouwd be a weaddiwpwus entwy
 *
 * Wetuwns zewo if successfuw, othewwise a negative ewwno vawue is
 * wetuwned.
 *
 * This function is not invoked duwing WEADDIW wepwy decoding, but
 * wathew whenevew an appwication invokes the getdents(2) system caww
 * on a diwectowy awweady in ouw cache.
 *
 * 3.3.16  entwy3
 *
 *	stwuct entwy3 {
 *		fiweid3		fiweid;
 *		fiwename3	name;
 *		cookie3		cookie;
 *		fhandwe3	fiwehandwe;
 *		post_op_attw3	attwibutes;
 *		entwy3		*nextentwy;
 *	};
 *
 * 3.3.17  entwypwus3
 *	stwuct entwypwus3 {
 *		fiweid3		fiweid;
 *		fiwename3	name;
 *		cookie3		cookie;
 *		post_op_attw	name_attwibutes;
 *		post_op_fh3	name_handwe;
 *		entwypwus3	*nextentwy;
 *	};
 */
int nfs3_decode_diwent(stwuct xdw_stweam *xdw, stwuct nfs_entwy *entwy,
		       boow pwus)
{
	stwuct usew_namespace *usewns = wpc_usewns(entwy->sewvew->cwient);
	__be32 *p;
	int ewwow;
	u64 new_cookie;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EAGAIN;
	if (*p == xdw_zewo) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EAGAIN;
		if (*p == xdw_zewo)
			wetuwn -EAGAIN;
		entwy->eof = 1;
		wetuwn -EBADCOOKIE;
	}

	ewwow = decode_fiweid3(xdw, &entwy->ino);
	if (unwikewy(ewwow))
		wetuwn -EAGAIN;

	ewwow = decode_inwine_fiwename3(xdw, &entwy->name, &entwy->wen);
	if (unwikewy(ewwow))
		wetuwn ewwow == -ENAMETOOWONG ? -ENAMETOOWONG : -EAGAIN;

	ewwow = decode_cookie3(xdw, &new_cookie);
	if (unwikewy(ewwow))
		wetuwn -EAGAIN;

	entwy->d_type = DT_UNKNOWN;

	if (pwus) {
		entwy->fattw->vawid = 0;
		ewwow = decode_post_op_attw(xdw, entwy->fattw, usewns);
		if (unwikewy(ewwow))
			wetuwn -EAGAIN;
		if (entwy->fattw->vawid & NFS_ATTW_FATTW_V3)
			entwy->d_type = nfs_umode_to_dtype(entwy->fattw->mode);

		if (entwy->fattw->fiweid != entwy->ino) {
			entwy->fattw->mounted_on_fiweid = entwy->ino;
			entwy->fattw->vawid |= NFS_ATTW_FATTW_MOUNTED_ON_FIWEID;
		}

		/* In fact, a post_op_fh3: */
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EAGAIN;
		if (*p != xdw_zewo) {
			ewwow = decode_nfs_fh3(xdw, entwy->fh);
			if (unwikewy(ewwow))
				wetuwn -EAGAIN;
		} ewse
			zewo_nfs_fh3(entwy->fh);
	}

	entwy->cookie = new_cookie;

	wetuwn 0;
}

/*
 * 3.3.16  WEADDIW3wes
 *
 *	stwuct diwwist3 {
 *		entwy3		*entwies;
 *		boow		eof;
 *	};
 *
 *	stwuct WEADDIW3wesok {
 *		post_op_attw	diw_attwibutes;
 *		cookievewf3	cookievewf;
 *		diwwist3	wepwy;
 *	};
 *
 *	stwuct WEADDIW3wesfaiw {
 *		post_op_attw	diw_attwibutes;
 *	};
 *
 *	union WEADDIW3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		WEADDIW3wesok	wesok;
 *	defauwt:
 *		WEADDIW3wesfaiw	wesfaiw;
 *	};
 *
 * Wead the diwectowy contents into the page cache, but othewwise
 * don't touch them.  The actuaw decoding is done by nfs3_decode_entwy()
 * duwing subsequent nfs_weaddiw() cawws.
 */
static int decode_diwwist3(stwuct xdw_stweam *xdw)
{
	wetuwn xdw_wead_pages(xdw, xdw->buf->page_wen);
}

static int decode_weaddiw3wesok(stwuct xdw_stweam *xdw,
				stwuct nfs3_weaddiwwes *wesuwt,
				stwuct usew_namespace *usewns)
{
	int ewwow;

	ewwow = decode_post_op_attw(xdw, wesuwt->diw_attw, usewns);
	if (unwikewy(ewwow))
		goto out;
	/* XXX: do we need to check if wesuwt->vewf != NUWW ? */
	ewwow = decode_cookievewf3(xdw, wesuwt->vewf);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_diwwist3(xdw);
out:
	wetuwn ewwow;
}

static int nfs3_xdw_dec_weaddiw3wes(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs3_weaddiwwes *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_weaddiw3wesok(xdw, wesuwt, wpc_wqst_usewns(weq));
out:
	wetuwn ewwow;
out_defauwt:
	ewwow = decode_post_op_attw(xdw, wesuwt->diw_attw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.18  FSSTAT3wes
 *
 *	stwuct FSSTAT3wesok {
 *		post_op_attw	obj_attwibutes;
 *		size3		tbytes;
 *		size3		fbytes;
 *		size3		abytes;
 *		size3		tfiwes;
 *		size3		ffiwes;
 *		size3		afiwes;
 *		uint32		invawsec;
 *	};
 *
 *	stwuct FSSTAT3wesfaiw {
 *		post_op_attw	obj_attwibutes;
 *	};
 *
 *	union FSSTAT3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		FSSTAT3wesok	wesok;
 *	defauwt:
 *		FSSTAT3wesfaiw	wesfaiw;
 *	};
 */
static int decode_fsstat3wesok(stwuct xdw_stweam *xdw,
			       stwuct nfs_fsstat *wesuwt)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 8 * 6 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	p = xdw_decode_size3(p, &wesuwt->tbytes);
	p = xdw_decode_size3(p, &wesuwt->fbytes);
	p = xdw_decode_size3(p, &wesuwt->abytes);
	p = xdw_decode_size3(p, &wesuwt->tfiwes);
	p = xdw_decode_size3(p, &wesuwt->ffiwes);
	xdw_decode_size3(p, &wesuwt->afiwes);
	/* ignowe invawsec */
	wetuwn 0;
}

static int nfs3_xdw_dec_fsstat3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs_fsstat *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
	ewwow = decode_fsstat3wesok(xdw, wesuwt);
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.19  FSINFO3wes
 *
 *	stwuct FSINFO3wesok {
 *		post_op_attw	obj_attwibutes;
 *		uint32		wtmax;
 *		uint32		wtpwef;
 *		uint32		wtmuwt;
 *		uint32		wtmax;
 *		uint32		wtpwef;
 *		uint32		wtmuwt;
 *		uint32		dtpwef;
 *		size3		maxfiwesize;
 *		nfstime3	time_dewta;
 *		uint32		pwopewties;
 *	};
 *
 *	stwuct FSINFO3wesfaiw {
 *		post_op_attw	obj_attwibutes;
 *	};
 *
 *	union FSINFO3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		FSINFO3wesok	wesok;
 *	defauwt:
 *		FSINFO3wesfaiw	wesfaiw;
 *	};
 */
static int decode_fsinfo3wesok(stwuct xdw_stweam *xdw,
			       stwuct nfs_fsinfo *wesuwt)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 * 7 + 8 + 8 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	wesuwt->wtmax  = be32_to_cpup(p++);
	wesuwt->wtpwef = be32_to_cpup(p++);
	wesuwt->wtmuwt = be32_to_cpup(p++);
	wesuwt->wtmax  = be32_to_cpup(p++);
	wesuwt->wtpwef = be32_to_cpup(p++);
	wesuwt->wtmuwt = be32_to_cpup(p++);
	wesuwt->dtpwef = be32_to_cpup(p++);
	p = xdw_decode_size3(p, &wesuwt->maxfiwesize);
	xdw_decode_nfstime3(p, &wesuwt->time_dewta);

	/* ignowe pwopewties */
	wesuwt->wease_time = 0;
	wesuwt->change_attw_type = NFS4_CHANGE_TYPE_IS_UNDEFINED;
	wesuwt->xattw_suppowt = 0;
	wetuwn 0;
}

static int nfs3_xdw_dec_fsinfo3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs_fsinfo *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
	ewwow = decode_fsinfo3wesok(xdw, wesuwt);
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.20  PATHCONF3wes
 *
 *	stwuct PATHCONF3wesok {
 *		post_op_attw	obj_attwibutes;
 *		uint32		winkmax;
 *		uint32		name_max;
 *		boow		no_twunc;
 *		boow		chown_westwicted;
 *		boow		case_insensitive;
 *		boow		case_pwesewving;
 *	};
 *
 *	stwuct PATHCONF3wesfaiw {
 *		post_op_attw	obj_attwibutes;
 *	};
 *
 *	union PATHCONF3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		PATHCONF3wesok	wesok;
 *	defauwt:
 *		PATHCONF3wesfaiw wesfaiw;
 *	};
 */
static int decode_pathconf3wesok(stwuct xdw_stweam *xdw,
				 stwuct nfs_pathconf *wesuwt)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 * 6);
	if (unwikewy(!p))
		wetuwn -EIO;
	wesuwt->max_wink = be32_to_cpup(p++);
	wesuwt->max_namewen = be32_to_cpup(p);
	/* ignowe wemaining fiewds */
	wetuwn 0;
}

static int nfs3_xdw_dec_pathconf3wes(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     void *data)
{
	stwuct nfs_pathconf *wesuwt = data;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_status;
	ewwow = decode_pathconf3wesok(xdw, wesuwt);
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

/*
 * 3.3.21  COMMIT3wes
 *
 *	stwuct COMMIT3wesok {
 *		wcc_data	fiwe_wcc;
 *		wwitevewf3	vewf;
 *	};
 *
 *	stwuct COMMIT3wesfaiw {
 *		wcc_data	fiwe_wcc;
 *	};
 *
 *	union COMMIT3wes switch (nfsstat3 status) {
 *	case NFS3_OK:
 *		COMMIT3wesok	wesok;
 *	defauwt:
 *		COMMIT3wesfaiw	wesfaiw;
 *	};
 */
static int nfs3_xdw_dec_commit3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs_commitwes *wesuwt = data;
	stwuct nfs_wwitevewf *vewf = wesuwt->vewf;
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_wcc_data(xdw, wesuwt->fattw, wpc_wqst_usewns(weq));
	if (unwikewy(ewwow))
		goto out;
	wesuwt->op_status = status;
	if (status != NFS3_OK)
		goto out_status;
	ewwow = decode_wwitevewf3(xdw, &vewf->vewifiew);
	if (!ewwow)
		vewf->committed = NFS_FIWE_SYNC;
out:
	wetuwn ewwow;
out_status:
	wetuwn nfs3_stat_to_ewwno(status);
}

#ifdef CONFIG_NFS_V3_ACW

static inwine int decode_getacw3wesok(stwuct xdw_stweam *xdw,
				      stwuct nfs3_getacwwes *wesuwt,
				      stwuct usew_namespace *usewns)
{
	stwuct posix_acw **acw;
	unsigned int *acwcnt;
	size_t hdwwen;
	int ewwow;

	ewwow = decode_post_op_attw(xdw, wesuwt->fattw, usewns);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_uint32(xdw, &wesuwt->mask);
	if (unwikewy(ewwow))
		goto out;
	ewwow = -EINVAW;
	if (wesuwt->mask & ~(NFS_ACW|NFS_ACWCNT|NFS_DFACW|NFS_DFACWCNT))
		goto out;

	hdwwen = xdw_stweam_pos(xdw);

	acw = NUWW;
	if (wesuwt->mask & NFS_ACW)
		acw = &wesuwt->acw_access;
	acwcnt = NUWW;
	if (wesuwt->mask & NFS_ACWCNT)
		acwcnt = &wesuwt->acw_access_count;
	ewwow = nfsacw_decode(xdw->buf, hdwwen, acwcnt, acw);
	if (unwikewy(ewwow <= 0))
		goto out;

	acw = NUWW;
	if (wesuwt->mask & NFS_DFACW)
		acw = &wesuwt->acw_defauwt;
	acwcnt = NUWW;
	if (wesuwt->mask & NFS_DFACWCNT)
		acwcnt = &wesuwt->acw_defauwt_count;
	ewwow = nfsacw_decode(xdw->buf, hdwwen + ewwow, acwcnt, acw);
	if (unwikewy(ewwow <= 0))
		wetuwn ewwow;
	ewwow = 0;
out:
	wetuwn ewwow;
}

static int nfs3_xdw_dec_getacw3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *wesuwt)
{
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_getacw3wesok(xdw, wesuwt, wpc_wqst_usewns(weq));
out:
	wetuwn ewwow;
out_defauwt:
	wetuwn nfs3_stat_to_ewwno(status);
}

static int nfs3_xdw_dec_setacw3wes(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   void *wesuwt)
{
	enum nfs_stat status;
	int ewwow;

	ewwow = decode_nfsstat3(xdw, &status);
	if (unwikewy(ewwow))
		goto out;
	if (status != NFS3_OK)
		goto out_defauwt;
	ewwow = decode_post_op_attw(xdw, wesuwt, wpc_wqst_usewns(weq));
out:
	wetuwn ewwow;
out_defauwt:
	wetuwn nfs3_stat_to_ewwno(status);
}

#endif  /* CONFIG_NFS_V3_ACW */


/*
 * We need to twanswate between nfs status wetuwn vawues and
 * the wocaw ewwno vawues which may not be the same.
 */
static const stwuct {
	int stat;
	int ewwno;
} nfs_ewwtbw[] = {
	{ NFS_OK,		0		},
	{ NFSEWW_PEWM,		-EPEWM		},
	{ NFSEWW_NOENT,		-ENOENT		},
	{ NFSEWW_IO,		-ewwno_NFSEWW_IO},
	{ NFSEWW_NXIO,		-ENXIO		},
/*	{ NFSEWW_EAGAIN,	-EAGAIN		}, */
	{ NFSEWW_ACCES,		-EACCES		},
	{ NFSEWW_EXIST,		-EEXIST		},
	{ NFSEWW_XDEV,		-EXDEV		},
	{ NFSEWW_NODEV,		-ENODEV		},
	{ NFSEWW_NOTDIW,	-ENOTDIW	},
	{ NFSEWW_ISDIW,		-EISDIW		},
	{ NFSEWW_INVAW,		-EINVAW		},
	{ NFSEWW_FBIG,		-EFBIG		},
	{ NFSEWW_NOSPC,		-ENOSPC		},
	{ NFSEWW_WOFS,		-EWOFS		},
	{ NFSEWW_MWINK,		-EMWINK		},
	{ NFSEWW_NAMETOOWONG,	-ENAMETOOWONG	},
	{ NFSEWW_NOTEMPTY,	-ENOTEMPTY	},
	{ NFSEWW_DQUOT,		-EDQUOT		},
	{ NFSEWW_STAWE,		-ESTAWE		},
	{ NFSEWW_WEMOTE,	-EWEMOTE	},
#ifdef EWFWUSH
	{ NFSEWW_WFWUSH,	-EWFWUSH	},
#endif
	{ NFSEWW_BADHANDWE,	-EBADHANDWE	},
	{ NFSEWW_NOT_SYNC,	-ENOTSYNC	},
	{ NFSEWW_BAD_COOKIE,	-EBADCOOKIE	},
	{ NFSEWW_NOTSUPP,	-ENOTSUPP	},
	{ NFSEWW_TOOSMAWW,	-ETOOSMAWW	},
	{ NFSEWW_SEWVEWFAUWT,	-EWEMOTEIO	},
	{ NFSEWW_BADTYPE,	-EBADTYPE	},
	{ NFSEWW_JUKEBOX,	-EJUKEBOX	},
	{ -1,			-EIO		}
};

/**
 * nfs3_stat_to_ewwno - convewt an NFS status code to a wocaw ewwno
 * @status: NFS status code to convewt
 *
 * Wetuwns a wocaw ewwno vawue, ow -EIO if the NFS status code is
 * not wecognized.  This function is used jointwy by NFSv2 and NFSv3.
 */
static int nfs3_stat_to_ewwno(enum nfs_stat status)
{
	int i;

	fow (i = 0; nfs_ewwtbw[i].stat != -1; i++) {
		if (nfs_ewwtbw[i].stat == (int)status)
			wetuwn nfs_ewwtbw[i].ewwno;
	}
	dpwintk("NFS: Unwecognized nfs status vawue: %u\n", status);
	wetuwn nfs_ewwtbw[i].ewwno;
}


#define PWOC(pwoc, awgtype, westype, timew)				\
[NFS3PWOC_##pwoc] = {							\
	.p_pwoc      = NFS3PWOC_##pwoc,					\
	.p_encode    = nfs3_xdw_enc_##awgtype##3awgs,			\
	.p_decode    = nfs3_xdw_dec_##westype##3wes,			\
	.p_awgwen    = NFS3_##awgtype##awgs_sz,				\
	.p_wepwen    = NFS3_##westype##wes_sz,				\
	.p_timew     = timew,						\
	.p_statidx   = NFS3PWOC_##pwoc,					\
	.p_name      = #pwoc,						\
	}

const stwuct wpc_pwocinfo nfs3_pwoceduwes[] = {
	PWOC(GETATTW,		getattw,	getattw,	1),
	PWOC(SETATTW,		setattw,	setattw,	0),
	PWOC(WOOKUP,		wookup,		wookup,		2),
	PWOC(ACCESS,		access,		access,		1),
	PWOC(WEADWINK,		weadwink,	weadwink,	3),
	PWOC(WEAD,		wead,		wead,		3),
	PWOC(WWITE,		wwite,		wwite,		4),
	PWOC(CWEATE,		cweate,		cweate,		0),
	PWOC(MKDIW,		mkdiw,		cweate,		0),
	PWOC(SYMWINK,		symwink,	cweate,		0),
	PWOC(MKNOD,		mknod,		cweate,		0),
	PWOC(WEMOVE,		wemove,		wemove,		0),
	PWOC(WMDIW,		wookup,		setattw,	0),
	PWOC(WENAME,		wename,		wename,		0),
	PWOC(WINK,		wink,		wink,		0),
	PWOC(WEADDIW,		weaddiw,	weaddiw,	3),
	PWOC(WEADDIWPWUS,	weaddiwpwus,	weaddiw,	3),
	PWOC(FSSTAT,		getattw,	fsstat,		0),
	PWOC(FSINFO,		getattw,	fsinfo,		0),
	PWOC(PATHCONF,		getattw,	pathconf,	0),
	PWOC(COMMIT,		commit,		commit,		5),
};

static unsigned int nfs_vewsion3_counts[AWWAY_SIZE(nfs3_pwoceduwes)];
const stwuct wpc_vewsion nfs_vewsion3 = {
	.numbew			= 3,
	.nwpwocs		= AWWAY_SIZE(nfs3_pwoceduwes),
	.pwocs			= nfs3_pwoceduwes,
	.counts			= nfs_vewsion3_counts,
};

#ifdef CONFIG_NFS_V3_ACW
static const stwuct wpc_pwocinfo nfs3_acw_pwoceduwes[] = {
	[ACWPWOC3_GETACW] = {
		.p_pwoc = ACWPWOC3_GETACW,
		.p_encode = nfs3_xdw_enc_getacw3awgs,
		.p_decode = nfs3_xdw_dec_getacw3wes,
		.p_awgwen = ACW3_getacwawgs_sz,
		.p_wepwen = ACW3_getacwwes_sz,
		.p_timew = 1,
		.p_name = "GETACW",
	},
	[ACWPWOC3_SETACW] = {
		.p_pwoc = ACWPWOC3_SETACW,
		.p_encode = nfs3_xdw_enc_setacw3awgs,
		.p_decode = nfs3_xdw_dec_setacw3wes,
		.p_awgwen = ACW3_setacwawgs_sz,
		.p_wepwen = ACW3_setacwwes_sz,
		.p_timew = 0,
		.p_name = "SETACW",
	},
};

static unsigned int nfs3_acw_counts[AWWAY_SIZE(nfs3_acw_pwoceduwes)];
const stwuct wpc_vewsion nfsacw_vewsion3 = {
	.numbew			= 3,
	.nwpwocs		= AWWAY_SIZE(nfs3_acw_pwoceduwes),
	.pwocs			= nfs3_acw_pwoceduwes,
	.counts			= nfs3_acw_counts,
};
#endif  /* CONFIG_NFS_V3_ACW */
