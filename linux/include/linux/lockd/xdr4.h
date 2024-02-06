/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/xdw4.h
 *
 * XDW types fow the NWM pwotocow
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WOCKD_XDW4_H
#define WOCKD_XDW4_H

#incwude <winux/fs.h>
#incwude <winux/nfs.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/wockd/xdw.h>

/* ewwow codes new to NWMv4 */
#define	nwm4_deadwock		cpu_to_be32(NWM_DEADWCK)
#define	nwm4_wofs		cpu_to_be32(NWM_WOFS)
#define	nwm4_stawe_fh		cpu_to_be32(NWM_STAWE_FH)
#define	nwm4_fbig		cpu_to_be32(NWM_FBIG)
#define	nwm4_faiwed		cpu_to_be32(NWM_FAIWED)

void	nwm4svc_set_fiwe_wock_wange(stwuct fiwe_wock *fw, u64 off, u64 wen);
boow	nwm4svc_decode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_testawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_wockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_cancawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_unwockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_weboot(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_shaweawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_decode_notify(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);

boow	nwm4svc_encode_testwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_encode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_encode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);
boow	nwm4svc_encode_shawewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw);

extewn const stwuct wpc_vewsion nwm_vewsion4;

#endif /* WOCKD_XDW4_H */
