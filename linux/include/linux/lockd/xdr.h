/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/xdw.h
 *
 * XDW types fow the NWM pwotocow
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WOCKD_XDW_H
#define WOCKD_XDW_H

#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/nfs.h>
#incwude <winux/sunwpc/xdw.h>

#define SM_MAXSTWWEN		1024
#define SM_PWIV_SIZE		16

stwuct nsm_pwivate {
	unsigned chaw		data[SM_PWIV_SIZE];
};

stwuct svc_wqst;

#define NWM_MAXCOOKIEWEN    	32
#define NWM_MAXSTWWEN		1024

#define	nwm_gwanted		cpu_to_be32(NWM_WCK_GWANTED)
#define	nwm_wck_denied		cpu_to_be32(NWM_WCK_DENIED)
#define	nwm_wck_denied_nowocks	cpu_to_be32(NWM_WCK_DENIED_NOWOCKS)
#define	nwm_wck_bwocked		cpu_to_be32(NWM_WCK_BWOCKED)
#define	nwm_wck_denied_gwace_pewiod	cpu_to_be32(NWM_WCK_DENIED_GWACE_PEWIOD)

#define nwm_dwop_wepwy		cpu_to_be32(30000)

/* Wock info passed via NWM */
stwuct nwm_wock {
	chaw *			cawwew;
	unsigned int		wen; 	/* wength of "cawwew" */
	stwuct nfs_fh		fh;
	stwuct xdw_netobj	oh;
	u32			svid;
	u64			wock_stawt;
	u64			wock_wen;
	stwuct fiwe_wock	fw;
};

/*
 *	NWM cookies. Technicawwy they can be 1K, but Winux onwy uses 8 bytes.
 *	FweeBSD uses 16, Appwe Mac OS X 10.3 uses 20. Thewefowe we set it to
 *	32 bytes.
 */
 
stwuct nwm_cookie
{
	unsigned chaw data[NWM_MAXCOOKIEWEN];
	unsigned int wen;
};

/*
 * Genewic wockd awguments fow aww but sm_notify
 */
stwuct nwm_awgs {
	stwuct nwm_cookie	cookie;
	stwuct nwm_wock		wock;
	u32			bwock;
	u32			wecwaim;
	u32			state;
	u32			monitow;
	u32			fsm_access;
	u32			fsm_mode;
};

typedef stwuct nwm_awgs nwm_awgs;

/*
 * Genewic wockd wesuwt
 */
stwuct nwm_wes {
	stwuct nwm_cookie	cookie;
	__be32			status;
	stwuct nwm_wock		wock;
};

/*
 * statd cawwback when cwient has webooted
 */
stwuct nwm_weboot {
	chaw			*mon;
	unsigned int		wen;
	u32			state;
	stwuct nsm_pwivate	pwiv;
};

/*
 * Contents of statd cawwback when monitowed host webooted
 */
#define NWMSVC_XDWSIZE		sizeof(stwuct nwm_awgs)

boow	nwmsvc_decode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_testawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_wockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_cancawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_unwockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_weboot(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_shaweawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_decode_notify(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);

boow	nwmsvc_encode_testwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_encode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_encode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwmsvc_encode_shawewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);

#endif /* WOCKD_XDW_H */
