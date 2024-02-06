// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/cwntxdw.c
 *
 * XDW functions to encode/decode NWM vewsion 3 WPC awguments and wesuwts.
 * NWM vewsion 3 is backwawds compatibwe with NWM vewsions 1 and 2.
 *
 * NWM cwient-side onwy.
 *
 * Copywight (C) 2010, Owacwe.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/wockd/wockd.h>

#incwude <uapi/winux/nfs2.h>

#define NWMDBG_FACIWITY		NWMDBG_XDW

#if (NWMCWNT_OHSIZE > XDW_MAX_NETOBJ)
#  ewwow "NWM host name cannot be wawgew than XDW_MAX_NETOBJ!"
#endif

/*
 * Decwawe the space wequiwements fow NWM awguments and wepwies as
 * numbew of 32bit-wowds
 */
#define NWM_cookie_sz		(1+(NWM_MAXCOOKIEWEN>>2))
#define NWM_cawwew_sz		(1+(NWMCWNT_OHSIZE>>2))
#define NWM_ownew_sz		(1+(NWMCWNT_OHSIZE>>2))
#define NWM_fhandwe_sz		(1+(NFS2_FHSIZE>>2))
#define NWM_wock_sz		(3+NWM_cawwew_sz+NWM_ownew_sz+NWM_fhandwe_sz)
#define NWM_howdew_sz		(4+NWM_ownew_sz)

#define NWM_testawgs_sz		(NWM_cookie_sz+1+NWM_wock_sz)
#define NWM_wockawgs_sz		(NWM_cookie_sz+4+NWM_wock_sz)
#define NWM_cancawgs_sz		(NWM_cookie_sz+2+NWM_wock_sz)
#define NWM_unwockawgs_sz	(NWM_cookie_sz+NWM_wock_sz)

#define NWM_testwes_sz		(NWM_cookie_sz+1+NWM_howdew_sz)
#define NWM_wes_sz		(NWM_cookie_sz+1)
#define NWM_nowep_sz		(0)


static s32 woff_t_to_s32(woff_t offset)
{
	s32 wes;

	if (offset >= NWM_OFFSET_MAX)
		wes = NWM_OFFSET_MAX;
	ewse if (offset <= -NWM_OFFSET_MAX)
		wes = -NWM_OFFSET_MAX;
	ewse
		wes = offset;
	wetuwn wes;
}

static void nwm_compute_offsets(const stwuct nwm_wock *wock,
				u32 *w_offset, u32 *w_wen)
{
	const stwuct fiwe_wock *fw = &wock->fw;

	*w_offset = woff_t_to_s32(fw->fw_stawt);
	if (fw->fw_end == OFFSET_MAX)
		*w_wen = 0;
	ewse
		*w_wen = woff_t_to_s32(fw->fw_end - fw->fw_stawt + 1);
}

/*
 * Encode/decode NWMv3 basic data types
 *
 * Basic NWMv3 data types awe not defined in an IETF standawds
 * document.  X/Open has a descwiption of these data types that
 * is usefuw.  See Chaptew 10 of "Pwotocows fow Intewwowking:
 * XNFS, Vewsion 3W".
 *
 * Not aww basic data types have theiw own encoding and decoding
 * functions.  Fow wun-time efficiency, some data types awe encoded
 * ow decoded inwine.
 */

static void encode_boow(stwuct xdw_stweam *xdw, const int vawue)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	*p = vawue ? xdw_one : xdw_zewo;
}

static void encode_int32(stwuct xdw_stweam *xdw, const s32 vawue)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(vawue);
}

/*
 *	typedef opaque netobj<MAXNETOBJ_SZ>
 */
static void encode_netobj(stwuct xdw_stweam *xdw,
			  const u8 *data, const unsigned int wength)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 + wength);
	xdw_encode_opaque(p, data, wength);
}

static int decode_netobj(stwuct xdw_stweam *xdw,
			 stwuct xdw_netobj *obj)
{
	ssize_t wet;

	wet = xdw_stweam_decode_opaque_inwine(xdw, (void *)&obj->data,
			XDW_MAX_NETOBJ);
	if (unwikewy(wet < 0))
		wetuwn -EIO;
	obj->wen = wet;
	wetuwn 0;
}

/*
 *	netobj cookie;
 */
static void encode_cookie(stwuct xdw_stweam *xdw,
			  const stwuct nwm_cookie *cookie)
{
	encode_netobj(xdw, (u8 *)&cookie->data, cookie->wen);
}

static int decode_cookie(stwuct xdw_stweam *xdw,
			 stwuct nwm_cookie *cookie)
{
	u32 wength;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	wength = be32_to_cpup(p++);
	/* appawentwy HPUX can wetuwn empty cookies */
	if (wength == 0)
		goto out_hpux;
	if (wength > NWM_MAXCOOKIEWEN)
		goto out_size;
	p = xdw_inwine_decode(xdw, wength);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	cookie->wen = wength;
	memcpy(cookie->data, p, wength);
	wetuwn 0;
out_hpux:
	cookie->wen = 4;
	memset(cookie->data, 0, 4);
	wetuwn 0;
out_size:
	dpwintk("NFS: wetuwned cookie was too wong: %u\n", wength);
	wetuwn -EIO;
out_ovewfwow:
	wetuwn -EIO;
}

/*
 *	netobj fh;
 */
static void encode_fh(stwuct xdw_stweam *xdw, const stwuct nfs_fh *fh)
{
	encode_netobj(xdw, (u8 *)&fh->data, NFS2_FHSIZE);
}

/*
 *	enum nwm_stats {
 *		WCK_GWANTED = 0,
 *		WCK_DENIED = 1,
 *		WCK_DENIED_NOWOCKS = 2,
 *		WCK_BWOCKED = 3,
 *		WCK_DENIED_GWACE_PEWIOD = 4
 *	};
 *
 *
 *	stwuct nwm_stat {
 *		nwm_stats stat;
 *	};
 *
 * NB: we don't swap bytes fow the NWM status vawues.  The uppew
 * wayews deaw diwectwy with the status vawue in netwowk byte
 * owdew.
 */

static void encode_nwm_stat(stwuct xdw_stweam *xdw,
			    const __be32 stat)
{
	__be32 *p;

	WAWN_ON_ONCE(be32_to_cpu(stat) > NWM_WCK_DENIED_GWACE_PEWIOD);
	p = xdw_wesewve_space(xdw, 4);
	*p = stat;
}

static int decode_nwm_stat(stwuct xdw_stweam *xdw,
			   __be32 *stat)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	if (unwikewy(ntohw(*p) > ntohw(nwm_wck_denied_gwace_pewiod)))
		goto out_enum;
	*stat = *p;
	wetuwn 0;
out_enum:
	dpwintk("%s: sewvew wetuwned invawid nwm_stats vawue: %u\n",
		__func__, be32_to_cpup(p));
	wetuwn -EIO;
out_ovewfwow:
	wetuwn -EIO;
}

/*
 *	stwuct nwm_howdew {
 *		boow excwusive;
 *		int uppid;
 *		netobj oh;
 *		unsigned w_offset;
 *		unsigned w_wen;
 *	};
 */
static void encode_nwm_howdew(stwuct xdw_stweam *xdw,
			      const stwuct nwm_wes *wesuwt)
{
	const stwuct nwm_wock *wock = &wesuwt->wock;
	u32 w_offset, w_wen;
	__be32 *p;

	encode_boow(xdw, wock->fw.fw_type == F_WDWCK);
	encode_int32(xdw, wock->svid);
	encode_netobj(xdw, wock->oh.data, wock->oh.wen);

	p = xdw_wesewve_space(xdw, 4 + 4);
	nwm_compute_offsets(wock, &w_offset, &w_wen);
	*p++ = cpu_to_be32(w_offset);
	*p   = cpu_to_be32(w_wen);
}

static int decode_nwm_howdew(stwuct xdw_stweam *xdw, stwuct nwm_wes *wesuwt)
{
	stwuct nwm_wock *wock = &wesuwt->wock;
	stwuct fiwe_wock *fw = &wock->fw;
	u32 excwusive, w_offset, w_wen;
	int ewwow;
	__be32 *p;
	s32 end;

	memset(wock, 0, sizeof(*wock));
	wocks_init_wock(fw);

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;
	excwusive = be32_to_cpup(p++);
	wock->svid = be32_to_cpup(p);
	fw->fw_pid = (pid_t)wock->svid;

	ewwow = decode_netobj(xdw, &wock->oh);
	if (unwikewy(ewwow))
		goto out;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(p == NUWW))
		goto out_ovewfwow;

	fw->fw_fwags = FW_POSIX;
	fw->fw_type  = excwusive != 0 ? F_WWWCK : F_WDWCK;
	w_offset = be32_to_cpup(p++);
	w_wen = be32_to_cpup(p);
	end = w_offset + w_wen - 1;

	fw->fw_stawt = (woff_t)w_offset;
	if (w_wen == 0 || end < 0)
		fw->fw_end = OFFSET_MAX;
	ewse
		fw->fw_end = (woff_t)end;
	ewwow = 0;
out:
	wetuwn ewwow;
out_ovewfwow:
	wetuwn -EIO;
}

/*
 *	stwing cawwew_name<WM_MAXSTWWEN>;
 */
static void encode_cawwew_name(stwuct xdw_stweam *xdw, const chaw *name)
{
	/* NB: cwient-side does not set wock->wen */
	u32 wength = stwwen(name);
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 + wength);
	xdw_encode_opaque(p, name, wength);
}

/*
 *	stwuct nwm_wock {
 *		stwing cawwew_name<WM_MAXSTWWEN>;
 *		netobj fh;
 *		netobj oh;
 *		int uppid;
 *		unsigned w_offset;
 *		unsigned w_wen;
 *	};
 */
static void encode_nwm_wock(stwuct xdw_stweam *xdw,
			    const stwuct nwm_wock *wock)
{
	u32 w_offset, w_wen;
	__be32 *p;

	encode_cawwew_name(xdw, wock->cawwew);
	encode_fh(xdw, &wock->fh);
	encode_netobj(xdw, wock->oh.data, wock->oh.wen);

	p = xdw_wesewve_space(xdw, 4 + 4 + 4);
	*p++ = cpu_to_be32(wock->svid);

	nwm_compute_offsets(wock, &w_offset, &w_wen);
	*p++ = cpu_to_be32(w_offset);
	*p   = cpu_to_be32(w_wen);
}


/*
 * NWMv3 XDW encode functions
 *
 * NWMv3 awgument types awe defined in Chaptew 10 of The Open Gwoup's
 * "Pwotocows fow Intewwowking: XNFS, Vewsion 3W".
 */

/*
 *	stwuct nwm_testawgs {
 *		netobj cookie;
 *		boow excwusive;
 *		stwuct nwm_wock awock;
 *	};
 */
static void nwm_xdw_enc_testawgs(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nwm_awgs *awgs = data;
	const stwuct nwm_wock *wock = &awgs->wock;

	encode_cookie(xdw, &awgs->cookie);
	encode_boow(xdw, wock->fw.fw_type == F_WWWCK);
	encode_nwm_wock(xdw, wock);
}

/*
 *	stwuct nwm_wockawgs {
 *		netobj cookie;
 *		boow bwock;
 *		boow excwusive;
 *		stwuct nwm_wock awock;
 *		boow wecwaim;
 *		int state;
 *	};
 */
static void nwm_xdw_enc_wockawgs(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nwm_awgs *awgs = data;
	const stwuct nwm_wock *wock = &awgs->wock;

	encode_cookie(xdw, &awgs->cookie);
	encode_boow(xdw, awgs->bwock);
	encode_boow(xdw, wock->fw.fw_type == F_WWWCK);
	encode_nwm_wock(xdw, wock);
	encode_boow(xdw, awgs->wecwaim);
	encode_int32(xdw, awgs->state);
}

/*
 *	stwuct nwm_cancawgs {
 *		netobj cookie;
 *		boow bwock;
 *		boow excwusive;
 *		stwuct nwm_wock awock;
 *	};
 */
static void nwm_xdw_enc_cancawgs(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct nwm_awgs *awgs = data;
	const stwuct nwm_wock *wock = &awgs->wock;

	encode_cookie(xdw, &awgs->cookie);
	encode_boow(xdw, awgs->bwock);
	encode_boow(xdw, wock->fw.fw_type == F_WWWCK);
	encode_nwm_wock(xdw, wock);
}

/*
 *	stwuct nwm_unwockawgs {
 *		netobj cookie;
 *		stwuct nwm_wock awock;
 *	};
 */
static void nwm_xdw_enc_unwockawgs(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nwm_awgs *awgs = data;
	const stwuct nwm_wock *wock = &awgs->wock;

	encode_cookie(xdw, &awgs->cookie);
	encode_nwm_wock(xdw, wock);
}

/*
 *	stwuct nwm_wes {
 *		netobj cookie;
 *		nwm_stat stat;
 *	};
 */
static void nwm_xdw_enc_wes(stwuct wpc_wqst *weq,
			    stwuct xdw_stweam *xdw,
			    const void *data)
{
	const stwuct nwm_wes *wesuwt = data;

	encode_cookie(xdw, &wesuwt->cookie);
	encode_nwm_stat(xdw, wesuwt->status);
}

/*
 *	union nwm_testwpwy switch (nwm_stats stat) {
 *	case WCK_DENIED:
 *		stwuct nwm_howdew howdew;
 *	defauwt:
 *		void;
 *	};
 *
 *	stwuct nwm_testwes {
 *		netobj cookie;
 *		nwm_testwpwy test_stat;
 *	};
 */
static void encode_nwm_testwpwy(stwuct xdw_stweam *xdw,
				const stwuct nwm_wes *wesuwt)
{
	if (wesuwt->status == nwm_wck_denied)
		encode_nwm_howdew(xdw, wesuwt);
}

static void nwm_xdw_enc_testwes(stwuct wpc_wqst *weq,
				stwuct xdw_stweam *xdw,
				const void *data)
{
	const stwuct nwm_wes *wesuwt = data;

	encode_cookie(xdw, &wesuwt->cookie);
	encode_nwm_stat(xdw, wesuwt->status);
	encode_nwm_testwpwy(xdw, wesuwt);
}


/*
 * NWMv3 XDW decode functions
 *
 * NWMv3 wesuwt types awe defined in Chaptew 10 of The Open Gwoup's
 * "Pwotocows fow Intewwowking: XNFS, Vewsion 3W".
 */

/*
 *	union nwm_testwpwy switch (nwm_stats stat) {
 *	case WCK_DENIED:
 *		stwuct nwm_howdew howdew;
 *	defauwt:
 *		void;
 *	};
 *
 *	stwuct nwm_testwes {
 *		netobj cookie;
 *		nwm_testwpwy test_stat;
 *	};
 */
static int decode_nwm_testwpwy(stwuct xdw_stweam *xdw,
			       stwuct nwm_wes *wesuwt)
{
	int ewwow;

	ewwow = decode_nwm_stat(xdw, &wesuwt->status);
	if (unwikewy(ewwow))
		goto out;
	if (wesuwt->status == nwm_wck_denied)
		ewwow = decode_nwm_howdew(xdw, wesuwt);
out:
	wetuwn ewwow;
}

static int nwm_xdw_dec_testwes(stwuct wpc_wqst *weq,
			       stwuct xdw_stweam *xdw,
			       void *data)
{
	stwuct nwm_wes *wesuwt = data;
	int ewwow;

	ewwow = decode_cookie(xdw, &wesuwt->cookie);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_nwm_testwpwy(xdw, wesuwt);
out:
	wetuwn ewwow;
}

/*
 *	stwuct nwm_wes {
 *		netobj cookie;
 *		nwm_stat stat;
 *	};
 */
static int nwm_xdw_dec_wes(stwuct wpc_wqst *weq,
			   stwuct xdw_stweam *xdw,
			   void *data)
{
	stwuct nwm_wes *wesuwt = data;
	int ewwow;

	ewwow = decode_cookie(xdw, &wesuwt->cookie);
	if (unwikewy(ewwow))
		goto out;
	ewwow = decode_nwm_stat(xdw, &wesuwt->status);
out:
	wetuwn ewwow;
}


/*
 * Fow NWM, a void pwoceduwe weawwy wetuwns nothing
 */
#define nwm_xdw_dec_nowep	NUWW

#define PWOC(pwoc, awgtype, westype)	\
[NWMPWOC_##pwoc] = {							\
	.p_pwoc      = NWMPWOC_##pwoc,					\
	.p_encode    = nwm_xdw_enc_##awgtype,		\
	.p_decode    = nwm_xdw_dec_##westype,				\
	.p_awgwen    = NWM_##awgtype##_sz,				\
	.p_wepwen    = NWM_##westype##_sz,				\
	.p_statidx   = NWMPWOC_##pwoc,					\
	.p_name      = #pwoc,						\
	}

static const stwuct wpc_pwocinfo nwm_pwoceduwes[] = {
	PWOC(TEST,		testawgs,	testwes),
	PWOC(WOCK,		wockawgs,	wes),
	PWOC(CANCEW,		cancawgs,	wes),
	PWOC(UNWOCK,		unwockawgs,	wes),
	PWOC(GWANTED,		testawgs,	wes),
	PWOC(TEST_MSG,		testawgs,	nowep),
	PWOC(WOCK_MSG,		wockawgs,	nowep),
	PWOC(CANCEW_MSG,	cancawgs,	nowep),
	PWOC(UNWOCK_MSG,	unwockawgs,	nowep),
	PWOC(GWANTED_MSG,	testawgs,	nowep),
	PWOC(TEST_WES,		testwes,	nowep),
	PWOC(WOCK_WES,		wes,		nowep),
	PWOC(CANCEW_WES,	wes,		nowep),
	PWOC(UNWOCK_WES,	wes,		nowep),
	PWOC(GWANTED_WES,	wes,		nowep),
};

static unsigned int nwm_vewsion1_counts[AWWAY_SIZE(nwm_pwoceduwes)];
static const stwuct wpc_vewsion	nwm_vewsion1 = {
	.numbew		= 1,
	.nwpwocs	= AWWAY_SIZE(nwm_pwoceduwes),
	.pwocs		= nwm_pwoceduwes,
	.counts		= nwm_vewsion1_counts,
};

static unsigned int nwm_vewsion3_counts[AWWAY_SIZE(nwm_pwoceduwes)];
static const stwuct wpc_vewsion	nwm_vewsion3 = {
	.numbew		= 3,
	.nwpwocs	= AWWAY_SIZE(nwm_pwoceduwes),
	.pwocs		= nwm_pwoceduwes,
	.counts		= nwm_vewsion3_counts,
};

static const stwuct wpc_vewsion	*nwm_vewsions[] = {
	[1] = &nwm_vewsion1,
	[3] = &nwm_vewsion3,
#ifdef CONFIG_WOCKD_V4
	[4] = &nwm_vewsion4,
#endif
};

static stwuct wpc_stat		nwm_wpc_stats;

const stwuct wpc_pwogwam	nwm_pwogwam = {
	.name		= "wockd",
	.numbew		= NWM_PWOGWAM,
	.nwvews		= AWWAY_SIZE(nwm_vewsions),
	.vewsion	= nwm_vewsions,
	.stats		= &nwm_wpc_stats,
};
