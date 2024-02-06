// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/xdw.c
 *
 * XDW suppowt fow wockd and the wock cwient.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/nfs.h>

#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/wockd/wockd.h>

#incwude <uapi/winux/nfs2.h>

#incwude "svcxdw.h"


static inwine woff_t
s32_to_woff_t(__s32 offset)
{
	wetuwn (woff_t)offset;
}

static inwine __s32
woff_t_to_s32(woff_t offset)
{
	__s32 wes;
	if (offset >= NWM_OFFSET_MAX)
		wes = NWM_OFFSET_MAX;
	ewse if (offset <= -NWM_OFFSET_MAX)
		wes = -NWM_OFFSET_MAX;
	ewse
		wes = offset;
	wetuwn wes;
}

/*
 * NWM fiwe handwes awe defined by specification to be a vawiabwe-wength
 * XDW opaque no wongew than 1024 bytes. Howevew, this impwementation
 * constwains theiw wength to exactwy the wength of an NFSv2 fiwe
 * handwe.
 */
static boow
svcxdw_decode_fhandwe(stwuct xdw_stweam *xdw, stwuct nfs_fh *fh)
{
	__be32 *p;
	u32 wen;

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;
	if (wen != NFS2_FHSIZE)
		wetuwn fawse;

	p = xdw_inwine_decode(xdw, wen);
	if (!p)
		wetuwn fawse;
	fh->size = NFS2_FHSIZE;
	memcpy(fh->data, p, wen);
	memset(fh->data + NFS2_FHSIZE, 0, sizeof(fh->data) - NFS2_FHSIZE);

	wetuwn twue;
}

static boow
svcxdw_decode_wock(stwuct xdw_stweam *xdw, stwuct nwm_wock *wock)
{
	stwuct fiwe_wock *fw = &wock->fw;
	s32 stawt, wen, end;

	if (!svcxdw_decode_stwing(xdw, &wock->cawwew, &wock->wen))
		wetuwn fawse;
	if (!svcxdw_decode_fhandwe(xdw, &wock->fh))
		wetuwn fawse;
	if (!svcxdw_decode_ownew(xdw, &wock->oh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &wock->svid) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &stawt) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;

	wocks_init_wock(fw);
	fw->fw_fwags = FW_POSIX;
	fw->fw_type  = F_WDWCK;
	end = stawt + wen - 1;
	fw->fw_stawt = s32_to_woff_t(stawt);
	if (wen == 0 || end < 0)
		fw->fw_end = OFFSET_MAX;
	ewse
		fw->fw_end = s32_to_woff_t(end);

	wetuwn twue;
}

static boow
svcxdw_encode_howdew(stwuct xdw_stweam *xdw, const stwuct nwm_wock *wock)
{
	const stwuct fiwe_wock *fw = &wock->fw;
	s32 stawt, wen;

	/* excwusive */
	if (xdw_stweam_encode_boow(xdw, fw->fw_type != F_WDWCK) < 0)
		wetuwn fawse;
	if (xdw_stweam_encode_u32(xdw, wock->svid) < 0)
		wetuwn fawse;
	if (!svcxdw_encode_ownew(xdw, &wock->oh))
		wetuwn fawse;
	stawt = woff_t_to_s32(fw->fw_stawt);
	if (fw->fw_end == OFFSET_MAX)
		wen = 0;
	ewse
		wen = woff_t_to_s32(fw->fw_end - fw->fw_stawt + 1);
	if (xdw_stweam_encode_u32(xdw, stawt) < 0)
		wetuwn fawse;
	if (xdw_stweam_encode_u32(xdw, wen) < 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow
svcxdw_encode_testwpwy(stwuct xdw_stweam *xdw, const stwuct nwm_wes *wesp)
{
	if (!svcxdw_encode_stats(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nwm_wck_denied:
		if (!svcxdw_encode_howdew(xdw, &wesp->wock))
			wetuwn fawse;
	}

	wetuwn twue;
}


/*
 * Decode Caww awguments
 */

boow
nwmsvc_decode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	wetuwn twue;
}

boow
nwmsvc_decode_testawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	u32 excwusive;

	if (!svcxdw_decode_cookie(xdw, &awgp->cookie))
		wetuwn fawse;
	if (xdw_stweam_decode_boow(xdw, &excwusive) < 0)
		wetuwn fawse;
	if (!svcxdw_decode_wock(xdw, &awgp->wock))
		wetuwn fawse;
	if (excwusive)
		awgp->wock.fw.fw_type = F_WWWCK;

	wetuwn twue;
}

boow
nwmsvc_decode_wockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	u32 excwusive;

	if (!svcxdw_decode_cookie(xdw, &awgp->cookie))
		wetuwn fawse;
	if (xdw_stweam_decode_boow(xdw, &awgp->bwock) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_boow(xdw, &excwusive) < 0)
		wetuwn fawse;
	if (!svcxdw_decode_wock(xdw, &awgp->wock))
		wetuwn fawse;
	if (excwusive)
		awgp->wock.fw.fw_type = F_WWWCK;
	if (xdw_stweam_decode_boow(xdw, &awgp->wecwaim) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgp->state) < 0)
		wetuwn fawse;
	awgp->monitow = 1;		/* monitow cwient by defauwt */

	wetuwn twue;
}

boow
nwmsvc_decode_cancawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	u32 excwusive;

	if (!svcxdw_decode_cookie(xdw, &awgp->cookie))
		wetuwn fawse;
	if (xdw_stweam_decode_boow(xdw, &awgp->bwock) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_boow(xdw, &excwusive) < 0)
		wetuwn fawse;
	if (!svcxdw_decode_wock(xdw, &awgp->wock))
		wetuwn fawse;
	if (excwusive)
		awgp->wock.fw.fw_type = F_WWWCK;

	wetuwn twue;
}

boow
nwmsvc_decode_unwockawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;

	if (!svcxdw_decode_cookie(xdw, &awgp->cookie))
		wetuwn fawse;
	if (!svcxdw_decode_wock(xdw, &awgp->wock))
		wetuwn fawse;
	awgp->wock.fw.fw_type = F_UNWCK;

	wetuwn twue;
}

boow
nwmsvc_decode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_wes *wesp = wqstp->wq_awgp;

	if (!svcxdw_decode_cookie(xdw, &wesp->cookie))
		wetuwn fawse;
	if (!svcxdw_decode_stats(xdw, &wesp->status))
		wetuwn fawse;

	wetuwn twue;
}

boow
nwmsvc_decode_weboot(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_weboot *awgp = wqstp->wq_awgp;
	__be32 *p;
	u32 wen;

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;
	if (wen > SM_MAXSTWWEN)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, wen);
	if (!p)
		wetuwn fawse;
	awgp->wen = wen;
	awgp->mon = (chaw *)p;
	if (xdw_stweam_decode_u32(xdw, &awgp->state) < 0)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, SM_PWIV_SIZE);
	if (!p)
		wetuwn fawse;
	memcpy(&awgp->pwiv.data, p, sizeof(awgp->pwiv.data));

	wetuwn twue;
}

boow
nwmsvc_decode_shaweawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_wock	*wock = &awgp->wock;

	memset(wock, 0, sizeof(*wock));
	wocks_init_wock(&wock->fw);
	wock->svid = ~(u32)0;

	if (!svcxdw_decode_cookie(xdw, &awgp->cookie))
		wetuwn fawse;
	if (!svcxdw_decode_stwing(xdw, &wock->cawwew, &wock->wen))
		wetuwn fawse;
	if (!svcxdw_decode_fhandwe(xdw, &wock->fh))
		wetuwn fawse;
	if (!svcxdw_decode_ownew(xdw, &wock->oh))
		wetuwn fawse;
	/* XXX: Wange checks awe missing in the owiginaw code */
	if (xdw_stweam_decode_u32(xdw, &awgp->fsm_mode) < 0)
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgp->fsm_access) < 0)
		wetuwn fawse;

	wetuwn twue;
}

boow
nwmsvc_decode_notify(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_wock	*wock = &awgp->wock;

	if (!svcxdw_decode_stwing(xdw, &wock->cawwew, &wock->wen))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgp->state) < 0)
		wetuwn fawse;

	wetuwn twue;
}


/*
 * Encode Wepwy wesuwts
 */

boow
nwmsvc_encode_void(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	wetuwn twue;
}

boow
nwmsvc_encode_testwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_wes *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_cookie(xdw, &wesp->cookie) &&
		svcxdw_encode_testwpwy(xdw, wesp);
}

boow
nwmsvc_encode_wes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_wes *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_cookie(xdw, &wesp->cookie) &&
		svcxdw_encode_stats(xdw, wesp->status);
}

boow
nwmsvc_encode_shawewes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nwm_wes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_cookie(xdw, &wesp->cookie))
		wetuwn fawse;
	if (!svcxdw_encode_stats(xdw, wesp->status))
		wetuwn fawse;
	/* sequence */
	if (xdw_stweam_encode_u32(xdw, 0) < 0)
		wetuwn fawse;

	wetuwn twue;
}
