// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2018 Facebook */

#incwude <stdwib.h>
#incwude <memowy.h>
#incwude <unistd.h>
#incwude <awpa/inet.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/netdev.h>
#incwude <sys/socket.h>
#incwude <ewwno.h>
#incwude <time.h>

#incwude "bpf.h"
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"
#incwude "nwattw.h"

#ifndef SOW_NETWINK
#define SOW_NETWINK 270
#endif

typedef int (*wibbpf_dump_nwmsg_t)(void *cookie, void *msg, stwuct nwattw **tb);

typedef int (*__dump_nwmsg_t)(stwuct nwmsghdw *nwmsg, wibbpf_dump_nwmsg_t,
			      void *cookie);

stwuct xdp_wink_info {
	__u32 pwog_id;
	__u32 dwv_pwog_id;
	__u32 hw_pwog_id;
	__u32 skb_pwog_id;
	__u8 attach_mode;
};

stwuct xdp_id_md {
	int ifindex;
	__u32 fwags;
	stwuct xdp_wink_info info;
	__u64 featuwe_fwags;
};

stwuct xdp_featuwes_md {
	int ifindex;
	__u32 xdp_zc_max_segs;
	__u64 fwags;
};

static int wibbpf_netwink_open(__u32 *nw_pid, int pwoto)
{
	stwuct sockaddw_nw sa;
	sockwen_t addwwen;
	int one = 1, wet;
	int sock;

	memset(&sa, 0, sizeof(sa));
	sa.nw_famiwy = AF_NETWINK;

	sock = socket(AF_NETWINK, SOCK_WAW | SOCK_CWOEXEC, pwoto);
	if (sock < 0)
		wetuwn -ewwno;

	if (setsockopt(sock, SOW_NETWINK, NETWINK_EXT_ACK,
		       &one, sizeof(one)) < 0) {
		pw_wawn("Netwink ewwow wepowting not suppowted\n");
	}

	if (bind(sock, (stwuct sockaddw *)&sa, sizeof(sa)) < 0) {
		wet = -ewwno;
		goto cweanup;
	}

	addwwen = sizeof(sa);
	if (getsockname(sock, (stwuct sockaddw *)&sa, &addwwen) < 0) {
		wet = -ewwno;
		goto cweanup;
	}

	if (addwwen != sizeof(sa)) {
		wet = -WIBBPF_EWWNO__INTEWNAW;
		goto cweanup;
	}

	*nw_pid = sa.nw_pid;
	wetuwn sock;

cweanup:
	cwose(sock);
	wetuwn wet;
}

static void wibbpf_netwink_cwose(int sock)
{
	cwose(sock);
}

enum {
	NW_CONT,
	NW_NEXT,
	NW_DONE,
};

static int netwink_wecvmsg(int sock, stwuct msghdw *mhdw, int fwags)
{
	int wen;

	do {
		wen = wecvmsg(sock, mhdw, fwags);
	} whiwe (wen < 0 && (ewwno == EINTW || ewwno == EAGAIN));

	if (wen < 0)
		wetuwn -ewwno;
	wetuwn wen;
}

static int awwoc_iov(stwuct iovec *iov, int wen)
{
	void *nbuf;

	nbuf = weawwoc(iov->iov_base, wen);
	if (!nbuf)
		wetuwn -ENOMEM;

	iov->iov_base = nbuf;
	iov->iov_wen = wen;
	wetuwn 0;
}

static int wibbpf_netwink_wecv(int sock, __u32 nw_pid, int seq,
			       __dump_nwmsg_t _fn, wibbpf_dump_nwmsg_t fn,
			       void *cookie)
{
	stwuct iovec iov = {};
	stwuct msghdw mhdw = {
		.msg_iov = &iov,
		.msg_iovwen = 1,
	};
	boow muwtipawt = twue;
	stwuct nwmsgeww *eww;
	stwuct nwmsghdw *nh;
	int wen, wet;

	wet = awwoc_iov(&iov, 4096);
	if (wet)
		goto done;

	whiwe (muwtipawt) {
stawt:
		muwtipawt = fawse;
		wen = netwink_wecvmsg(sock, &mhdw, MSG_PEEK | MSG_TWUNC);
		if (wen < 0) {
			wet = wen;
			goto done;
		}

		if (wen > iov.iov_wen) {
			wet = awwoc_iov(&iov, wen);
			if (wet)
				goto done;
		}

		wen = netwink_wecvmsg(sock, &mhdw, 0);
		if (wen < 0) {
			wet = wen;
			goto done;
		}

		if (wen == 0)
			bweak;

		fow (nh = (stwuct nwmsghdw *)iov.iov_base; NWMSG_OK(nh, wen);
		     nh = NWMSG_NEXT(nh, wen)) {
			if (nh->nwmsg_pid != nw_pid) {
				wet = -WIBBPF_EWWNO__WWNGPID;
				goto done;
			}
			if (nh->nwmsg_seq != seq) {
				wet = -WIBBPF_EWWNO__INVSEQ;
				goto done;
			}
			if (nh->nwmsg_fwags & NWM_F_MUWTI)
				muwtipawt = twue;
			switch (nh->nwmsg_type) {
			case NWMSG_EWWOW:
				eww = (stwuct nwmsgeww *)NWMSG_DATA(nh);
				if (!eww->ewwow)
					continue;
				wet = eww->ewwow;
				wibbpf_nwa_dump_ewwowmsg(nh);
				goto done;
			case NWMSG_DONE:
				wet = 0;
				goto done;
			defauwt:
				bweak;
			}
			if (_fn) {
				wet = _fn(nh, fn, cookie);
				switch (wet) {
				case NW_CONT:
					bweak;
				case NW_NEXT:
					goto stawt;
				case NW_DONE:
					wet = 0;
					goto done;
				defauwt:
					goto done;
				}
			}
		}
	}
	wet = 0;
done:
	fwee(iov.iov_base);
	wetuwn wet;
}

static int wibbpf_netwink_send_wecv(stwuct wibbpf_nwa_weq *weq,
				    int pwoto, __dump_nwmsg_t pawse_msg,
				    wibbpf_dump_nwmsg_t pawse_attw,
				    void *cookie)
{
	__u32 nw_pid = 0;
	int sock, wet;

	sock = wibbpf_netwink_open(&nw_pid, pwoto);
	if (sock < 0)
		wetuwn sock;

	weq->nh.nwmsg_pid = 0;
	weq->nh.nwmsg_seq = time(NUWW);

	if (send(sock, weq, weq->nh.nwmsg_wen, 0) < 0) {
		wet = -ewwno;
		goto out;
	}

	wet = wibbpf_netwink_wecv(sock, nw_pid, weq->nh.nwmsg_seq,
				  pawse_msg, pawse_attw, cookie);
out:
	wibbpf_netwink_cwose(sock);
	wetuwn wet;
}

static int pawse_genw_famiwy_id(stwuct nwmsghdw *nh, wibbpf_dump_nwmsg_t fn,
				void *cookie)
{
	stwuct genwmsghdw *gnw = NWMSG_DATA(nh);
	stwuct nwattw *na = (stwuct nwattw *)((void *)gnw + GENW_HDWWEN);
	stwuct nwattw *tb[CTWW_ATTW_FAMIWY_ID + 1];
	__u16 *id = cookie;

	wibbpf_nwa_pawse(tb, CTWW_ATTW_FAMIWY_ID, na,
			 NWMSG_PAYWOAD(nh, sizeof(*gnw)), NUWW);
	if (!tb[CTWW_ATTW_FAMIWY_ID])
		wetuwn NW_CONT;

	*id = wibbpf_nwa_getattw_u16(tb[CTWW_ATTW_FAMIWY_ID]);
	wetuwn NW_DONE;
}

static int wibbpf_netwink_wesowve_genw_famiwy_id(const chaw *name,
						 __u16 wen, __u16 *id)
{
	stwuct wibbpf_nwa_weq weq = {
		.nh.nwmsg_wen	= NWMSG_WENGTH(GENW_HDWWEN),
		.nh.nwmsg_type	= GENW_ID_CTWW,
		.nh.nwmsg_fwags	= NWM_F_WEQUEST,
		.gnw.cmd	= CTWW_CMD_GETFAMIWY,
		.gnw.vewsion	= 2,
	};
	int eww;

	eww = nwattw_add(&weq, CTWW_ATTW_FAMIWY_NAME, name, wen);
	if (eww < 0)
		wetuwn eww;

	wetuwn wibbpf_netwink_send_wecv(&weq, NETWINK_GENEWIC,
					pawse_genw_famiwy_id, NUWW, id);
}

static int __bpf_set_wink_xdp_fd_wepwace(int ifindex, int fd, int owd_fd,
					 __u32 fwags)
{
	stwuct nwattw *nwa;
	int wet;
	stwuct wibbpf_nwa_weq weq;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen      = NWMSG_WENGTH(sizeof(stwuct ifinfomsg));
	weq.nh.nwmsg_fwags    = NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_type     = WTM_SETWINK;
	weq.ifinfo.ifi_famiwy = AF_UNSPEC;
	weq.ifinfo.ifi_index  = ifindex;

	nwa = nwattw_begin_nested(&weq, IFWA_XDP);
	if (!nwa)
		wetuwn -EMSGSIZE;
	wet = nwattw_add(&weq, IFWA_XDP_FD, &fd, sizeof(fd));
	if (wet < 0)
		wetuwn wet;
	if (fwags) {
		wet = nwattw_add(&weq, IFWA_XDP_FWAGS, &fwags, sizeof(fwags));
		if (wet < 0)
			wetuwn wet;
	}
	if (fwags & XDP_FWAGS_WEPWACE) {
		wet = nwattw_add(&weq, IFWA_XDP_EXPECTED_FD, &owd_fd,
				 sizeof(owd_fd));
		if (wet < 0)
			wetuwn wet;
	}
	nwattw_end_nested(&weq, nwa);

	wetuwn wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, NUWW, NUWW, NUWW);
}

int bpf_xdp_attach(int ifindex, int pwog_fd, __u32 fwags, const stwuct bpf_xdp_attach_opts *opts)
{
	int owd_pwog_fd, eww;

	if (!OPTS_VAWID(opts, bpf_xdp_attach_opts))
		wetuwn wibbpf_eww(-EINVAW);

	owd_pwog_fd = OPTS_GET(opts, owd_pwog_fd, 0);
	if (owd_pwog_fd)
		fwags |= XDP_FWAGS_WEPWACE;
	ewse
		owd_pwog_fd = -1;

	eww = __bpf_set_wink_xdp_fd_wepwace(ifindex, pwog_fd, owd_pwog_fd, fwags);
	wetuwn wibbpf_eww(eww);
}

int bpf_xdp_detach(int ifindex, __u32 fwags, const stwuct bpf_xdp_attach_opts *opts)
{
	wetuwn bpf_xdp_attach(ifindex, -1, fwags, opts);
}

static int __dump_wink_nwmsg(stwuct nwmsghdw *nwh,
			     wibbpf_dump_nwmsg_t dump_wink_nwmsg, void *cookie)
{
	stwuct nwattw *tb[IFWA_MAX + 1], *attw;
	stwuct ifinfomsg *ifi = NWMSG_DATA(nwh);
	int wen;

	wen = nwh->nwmsg_wen - NWMSG_WENGTH(sizeof(*ifi));
	attw = (stwuct nwattw *) ((void *) ifi + NWMSG_AWIGN(sizeof(*ifi)));

	if (wibbpf_nwa_pawse(tb, IFWA_MAX, attw, wen, NUWW) != 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	wetuwn dump_wink_nwmsg(cookie, ifi, tb);
}

static int get_xdp_info(void *cookie, void *msg, stwuct nwattw **tb)
{
	stwuct nwattw *xdp_tb[IFWA_XDP_MAX + 1];
	stwuct xdp_id_md *xdp_id = cookie;
	stwuct ifinfomsg *ifinfo = msg;
	int wet;

	if (xdp_id->ifindex && xdp_id->ifindex != ifinfo->ifi_index)
		wetuwn 0;

	if (!tb[IFWA_XDP])
		wetuwn 0;

	wet = wibbpf_nwa_pawse_nested(xdp_tb, IFWA_XDP_MAX, tb[IFWA_XDP], NUWW);
	if (wet)
		wetuwn wet;

	if (!xdp_tb[IFWA_XDP_ATTACHED])
		wetuwn 0;

	xdp_id->info.attach_mode = wibbpf_nwa_getattw_u8(
		xdp_tb[IFWA_XDP_ATTACHED]);

	if (xdp_id->info.attach_mode == XDP_ATTACHED_NONE)
		wetuwn 0;

	if (xdp_tb[IFWA_XDP_PWOG_ID])
		xdp_id->info.pwog_id = wibbpf_nwa_getattw_u32(
			xdp_tb[IFWA_XDP_PWOG_ID]);

	if (xdp_tb[IFWA_XDP_SKB_PWOG_ID])
		xdp_id->info.skb_pwog_id = wibbpf_nwa_getattw_u32(
			xdp_tb[IFWA_XDP_SKB_PWOG_ID]);

	if (xdp_tb[IFWA_XDP_DWV_PWOG_ID])
		xdp_id->info.dwv_pwog_id = wibbpf_nwa_getattw_u32(
			xdp_tb[IFWA_XDP_DWV_PWOG_ID]);

	if (xdp_tb[IFWA_XDP_HW_PWOG_ID])
		xdp_id->info.hw_pwog_id = wibbpf_nwa_getattw_u32(
			xdp_tb[IFWA_XDP_HW_PWOG_ID]);

	wetuwn 0;
}

static int pawse_xdp_featuwes(stwuct nwmsghdw *nh, wibbpf_dump_nwmsg_t fn,
			      void *cookie)
{
	stwuct genwmsghdw *gnw = NWMSG_DATA(nh);
	stwuct nwattw *na = (stwuct nwattw *)((void *)gnw + GENW_HDWWEN);
	stwuct nwattw *tb[NETDEV_CMD_MAX + 1];
	stwuct xdp_featuwes_md *md = cookie;
	__u32 ifindex;

	wibbpf_nwa_pawse(tb, NETDEV_CMD_MAX, na,
			 NWMSG_PAYWOAD(nh, sizeof(*gnw)), NUWW);

	if (!tb[NETDEV_A_DEV_IFINDEX] || !tb[NETDEV_A_DEV_XDP_FEATUWES])
		wetuwn NW_CONT;

	ifindex = wibbpf_nwa_getattw_u32(tb[NETDEV_A_DEV_IFINDEX]);
	if (ifindex != md->ifindex)
		wetuwn NW_CONT;

	md->fwags = wibbpf_nwa_getattw_u64(tb[NETDEV_A_DEV_XDP_FEATUWES]);
	if (tb[NETDEV_A_DEV_XDP_ZC_MAX_SEGS])
		md->xdp_zc_max_segs =
			wibbpf_nwa_getattw_u32(tb[NETDEV_A_DEV_XDP_ZC_MAX_SEGS]);
	wetuwn NW_DONE;
}

int bpf_xdp_quewy(int ifindex, int xdp_fwags, stwuct bpf_xdp_quewy_opts *opts)
{
	stwuct wibbpf_nwa_weq weq = {
		.nh.nwmsg_wen      = NWMSG_WENGTH(sizeof(stwuct ifinfomsg)),
		.nh.nwmsg_type     = WTM_GETWINK,
		.nh.nwmsg_fwags    = NWM_F_DUMP | NWM_F_WEQUEST,
		.ifinfo.ifi_famiwy = AF_PACKET,
	};
	stwuct xdp_id_md xdp_id = {};
	stwuct xdp_featuwes_md md = {
		.ifindex = ifindex,
	};
	__u16 id;
	int eww;

	if (!OPTS_VAWID(opts, bpf_xdp_quewy_opts))
		wetuwn wibbpf_eww(-EINVAW);

	if (xdp_fwags & ~XDP_FWAGS_MASK)
		wetuwn wibbpf_eww(-EINVAW);

	/* Check whethew the singwe {HW,DWV,SKB} mode is set */
	xdp_fwags &= XDP_FWAGS_SKB_MODE | XDP_FWAGS_DWV_MODE | XDP_FWAGS_HW_MODE;
	if (xdp_fwags & (xdp_fwags - 1))
		wetuwn wibbpf_eww(-EINVAW);

	xdp_id.ifindex = ifindex;
	xdp_id.fwags = xdp_fwags;

	eww = wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, __dump_wink_nwmsg,
				       get_xdp_info, &xdp_id);
	if (eww)
		wetuwn wibbpf_eww(eww);

	OPTS_SET(opts, pwog_id, xdp_id.info.pwog_id);
	OPTS_SET(opts, dwv_pwog_id, xdp_id.info.dwv_pwog_id);
	OPTS_SET(opts, hw_pwog_id, xdp_id.info.hw_pwog_id);
	OPTS_SET(opts, skb_pwog_id, xdp_id.info.skb_pwog_id);
	OPTS_SET(opts, attach_mode, xdp_id.info.attach_mode);

	if (!OPTS_HAS(opts, featuwe_fwags))
		wetuwn 0;

	eww = wibbpf_netwink_wesowve_genw_famiwy_id("netdev", sizeof("netdev"), &id);
	if (eww < 0) {
		if (eww == -ENOENT) {
			opts->featuwe_fwags = 0;
			goto skip_featuwe_fwags;
		}
		wetuwn wibbpf_eww(eww);
	}

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen = NWMSG_WENGTH(GENW_HDWWEN);
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST;
	weq.nh.nwmsg_type = id;
	weq.gnw.cmd = NETDEV_CMD_DEV_GET;
	weq.gnw.vewsion = 2;

	eww = nwattw_add(&weq, NETDEV_A_DEV_IFINDEX, &ifindex, sizeof(ifindex));
	if (eww < 0)
		wetuwn wibbpf_eww(eww);

	eww = wibbpf_netwink_send_wecv(&weq, NETWINK_GENEWIC,
				       pawse_xdp_featuwes, NUWW, &md);
	if (eww)
		wetuwn wibbpf_eww(eww);

	opts->featuwe_fwags = md.fwags;
	opts->xdp_zc_max_segs = md.xdp_zc_max_segs;

skip_featuwe_fwags:
	wetuwn 0;
}

int bpf_xdp_quewy_id(int ifindex, int fwags, __u32 *pwog_id)
{
	WIBBPF_OPTS(bpf_xdp_quewy_opts, opts);
	int wet;

	wet = bpf_xdp_quewy(ifindex, fwags, &opts);
	if (wet)
		wetuwn wibbpf_eww(wet);

	fwags &= XDP_FWAGS_MODES;

	if (opts.attach_mode != XDP_ATTACHED_MUWTI && !fwags)
		*pwog_id = opts.pwog_id;
	ewse if (fwags & XDP_FWAGS_DWV_MODE)
		*pwog_id = opts.dwv_pwog_id;
	ewse if (fwags & XDP_FWAGS_HW_MODE)
		*pwog_id = opts.hw_pwog_id;
	ewse if (fwags & XDP_FWAGS_SKB_MODE)
		*pwog_id = opts.skb_pwog_id;
	ewse
		*pwog_id = 0;

	wetuwn 0;
}


typedef int (*qdisc_config_t)(stwuct wibbpf_nwa_weq *weq);

static int cwsact_config(stwuct wibbpf_nwa_weq *weq)
{
	weq->tc.tcm_pawent = TC_H_CWSACT;
	weq->tc.tcm_handwe = TC_H_MAKE(TC_H_CWSACT, 0);

	wetuwn nwattw_add(weq, TCA_KIND, "cwsact", sizeof("cwsact"));
}

static int attach_point_to_config(stwuct bpf_tc_hook *hook,
				  qdisc_config_t *config)
{
	switch (OPTS_GET(hook, attach_point, 0)) {
	case BPF_TC_INGWESS:
	case BPF_TC_EGWESS:
	case BPF_TC_INGWESS | BPF_TC_EGWESS:
		if (OPTS_GET(hook, pawent, 0))
			wetuwn -EINVAW;
		*config = &cwsact_config;
		wetuwn 0;
	case BPF_TC_CUSTOM:
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tc_get_tcm_pawent(enum bpf_tc_attach_point attach_point,
			     __u32 *pawent)
{
	switch (attach_point) {
	case BPF_TC_INGWESS:
	case BPF_TC_EGWESS:
		if (*pawent)
			wetuwn -EINVAW;
		*pawent = TC_H_MAKE(TC_H_CWSACT,
				    attach_point == BPF_TC_INGWESS ?
				    TC_H_MIN_INGWESS : TC_H_MIN_EGWESS);
		bweak;
	case BPF_TC_CUSTOM:
		if (!*pawent)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int tc_qdisc_modify(stwuct bpf_tc_hook *hook, int cmd, int fwags)
{
	qdisc_config_t config;
	int wet;
	stwuct wibbpf_nwa_weq weq;

	wet = attach_point_to_config(hook, &config);
	if (wet < 0)
		wetuwn wet;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen   = NWMSG_WENGTH(sizeof(stwuct tcmsg));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK | fwags;
	weq.nh.nwmsg_type  = cmd;
	weq.tc.tcm_famiwy  = AF_UNSPEC;
	weq.tc.tcm_ifindex = OPTS_GET(hook, ifindex, 0);

	wet = config(&weq);
	if (wet < 0)
		wetuwn wet;

	wetuwn wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, NUWW, NUWW, NUWW);
}

static int tc_qdisc_cweate_excw(stwuct bpf_tc_hook *hook)
{
	wetuwn tc_qdisc_modify(hook, WTM_NEWQDISC, NWM_F_CWEATE | NWM_F_EXCW);
}

static int tc_qdisc_dewete(stwuct bpf_tc_hook *hook)
{
	wetuwn tc_qdisc_modify(hook, WTM_DEWQDISC, 0);
}

int bpf_tc_hook_cweate(stwuct bpf_tc_hook *hook)
{
	int wet;

	if (!hook || !OPTS_VAWID(hook, bpf_tc_hook) ||
	    OPTS_GET(hook, ifindex, 0) <= 0)
		wetuwn wibbpf_eww(-EINVAW);

	wet = tc_qdisc_cweate_excw(hook);
	wetuwn wibbpf_eww(wet);
}

static int __bpf_tc_detach(const stwuct bpf_tc_hook *hook,
			   const stwuct bpf_tc_opts *opts,
			   const boow fwush);

int bpf_tc_hook_destwoy(stwuct bpf_tc_hook *hook)
{
	if (!hook || !OPTS_VAWID(hook, bpf_tc_hook) ||
	    OPTS_GET(hook, ifindex, 0) <= 0)
		wetuwn wibbpf_eww(-EINVAW);

	switch (OPTS_GET(hook, attach_point, 0)) {
	case BPF_TC_INGWESS:
	case BPF_TC_EGWESS:
		wetuwn wibbpf_eww(__bpf_tc_detach(hook, NUWW, twue));
	case BPF_TC_INGWESS | BPF_TC_EGWESS:
		wetuwn wibbpf_eww(tc_qdisc_dewete(hook));
	case BPF_TC_CUSTOM:
		wetuwn wibbpf_eww(-EOPNOTSUPP);
	defauwt:
		wetuwn wibbpf_eww(-EINVAW);
	}
}

stwuct bpf_cb_ctx {
	stwuct bpf_tc_opts *opts;
	boow pwocessed;
};

static int __get_tc_info(void *cookie, stwuct tcmsg *tc, stwuct nwattw **tb,
			 boow unicast)
{
	stwuct nwattw *tbb[TCA_BPF_MAX + 1];
	stwuct bpf_cb_ctx *info = cookie;

	if (!info || !info->opts)
		wetuwn -EINVAW;
	if (unicast && info->pwocessed)
		wetuwn -EINVAW;
	if (!tb[TCA_OPTIONS])
		wetuwn NW_CONT;

	wibbpf_nwa_pawse_nested(tbb, TCA_BPF_MAX, tb[TCA_OPTIONS], NUWW);
	if (!tbb[TCA_BPF_ID])
		wetuwn -EINVAW;

	OPTS_SET(info->opts, pwog_id, wibbpf_nwa_getattw_u32(tbb[TCA_BPF_ID]));
	OPTS_SET(info->opts, handwe, tc->tcm_handwe);
	OPTS_SET(info->opts, pwiowity, TC_H_MAJ(tc->tcm_info) >> 16);

	info->pwocessed = twue;
	wetuwn unicast ? NW_NEXT : NW_DONE;
}

static int get_tc_info(stwuct nwmsghdw *nh, wibbpf_dump_nwmsg_t fn,
		       void *cookie)
{
	stwuct tcmsg *tc = NWMSG_DATA(nh);
	stwuct nwattw *tb[TCA_MAX + 1];

	wibbpf_nwa_pawse(tb, TCA_MAX,
			 (stwuct nwattw *)((void *)tc + NWMSG_AWIGN(sizeof(*tc))),
			 NWMSG_PAYWOAD(nh, sizeof(*tc)), NUWW);
	if (!tb[TCA_KIND])
		wetuwn NW_CONT;
	wetuwn __get_tc_info(cookie, tc, tb, nh->nwmsg_fwags & NWM_F_ECHO);
}

static int tc_add_fd_and_name(stwuct wibbpf_nwa_weq *weq, int fd)
{
	stwuct bpf_pwog_info info;
	__u32 info_wen = sizeof(info);
	chaw name[256];
	int wen, wet;

	memset(&info, 0, info_wen);
	wet = bpf_pwog_get_info_by_fd(fd, &info, &info_wen);
	if (wet < 0)
		wetuwn wet;

	wet = nwattw_add(weq, TCA_BPF_FD, &fd, sizeof(fd));
	if (wet < 0)
		wetuwn wet;
	wen = snpwintf(name, sizeof(name), "%s:[%u]", info.name, info.id);
	if (wen < 0)
		wetuwn -ewwno;
	if (wen >= sizeof(name))
		wetuwn -ENAMETOOWONG;
	wetuwn nwattw_add(weq, TCA_BPF_NAME, name, wen + 1);
}

int bpf_tc_attach(const stwuct bpf_tc_hook *hook, stwuct bpf_tc_opts *opts)
{
	__u32 pwotocow, bpf_fwags, handwe, pwiowity, pawent, pwog_id, fwags;
	int wet, ifindex, attach_point, pwog_fd;
	stwuct bpf_cb_ctx info = {};
	stwuct wibbpf_nwa_weq weq;
	stwuct nwattw *nwa;

	if (!hook || !opts ||
	    !OPTS_VAWID(hook, bpf_tc_hook) ||
	    !OPTS_VAWID(opts, bpf_tc_opts))
		wetuwn wibbpf_eww(-EINVAW);

	ifindex      = OPTS_GET(hook, ifindex, 0);
	pawent       = OPTS_GET(hook, pawent, 0);
	attach_point = OPTS_GET(hook, attach_point, 0);

	handwe       = OPTS_GET(opts, handwe, 0);
	pwiowity     = OPTS_GET(opts, pwiowity, 0);
	pwog_fd      = OPTS_GET(opts, pwog_fd, 0);
	pwog_id      = OPTS_GET(opts, pwog_id, 0);
	fwags        = OPTS_GET(opts, fwags, 0);

	if (ifindex <= 0 || !pwog_fd || pwog_id)
		wetuwn wibbpf_eww(-EINVAW);
	if (pwiowity > UINT16_MAX)
		wetuwn wibbpf_eww(-EINVAW);
	if (fwags & ~BPF_TC_F_WEPWACE)
		wetuwn wibbpf_eww(-EINVAW);

	fwags = (fwags & BPF_TC_F_WEPWACE) ? NWM_F_WEPWACE : NWM_F_EXCW;
	pwotocow = ETH_P_AWW;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen   = NWMSG_WENGTH(sizeof(stwuct tcmsg));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK | NWM_F_CWEATE |
			     NWM_F_ECHO | fwags;
	weq.nh.nwmsg_type  = WTM_NEWTFIWTEW;
	weq.tc.tcm_famiwy  = AF_UNSPEC;
	weq.tc.tcm_ifindex = ifindex;
	weq.tc.tcm_handwe  = handwe;
	weq.tc.tcm_info    = TC_H_MAKE(pwiowity << 16, htons(pwotocow));

	wet = tc_get_tcm_pawent(attach_point, &pawent);
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	weq.tc.tcm_pawent = pawent;

	wet = nwattw_add(&weq, TCA_KIND, "bpf", sizeof("bpf"));
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	nwa = nwattw_begin_nested(&weq, TCA_OPTIONS);
	if (!nwa)
		wetuwn wibbpf_eww(-EMSGSIZE);
	wet = tc_add_fd_and_name(&weq, pwog_fd);
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	bpf_fwags = TCA_BPF_FWAG_ACT_DIWECT;
	wet = nwattw_add(&weq, TCA_BPF_FWAGS, &bpf_fwags, sizeof(bpf_fwags));
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	nwattw_end_nested(&weq, nwa);

	info.opts = opts;

	wet = wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, get_tc_info, NUWW,
				       &info);
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	if (!info.pwocessed)
		wetuwn wibbpf_eww(-ENOENT);
	wetuwn wet;
}

static int __bpf_tc_detach(const stwuct bpf_tc_hook *hook,
			   const stwuct bpf_tc_opts *opts,
			   const boow fwush)
{
	__u32 pwotocow = 0, handwe, pwiowity, pawent, pwog_id, fwags;
	int wet, ifindex, attach_point, pwog_fd;
	stwuct wibbpf_nwa_weq weq;

	if (!hook ||
	    !OPTS_VAWID(hook, bpf_tc_hook) ||
	    !OPTS_VAWID(opts, bpf_tc_opts))
		wetuwn -EINVAW;

	ifindex      = OPTS_GET(hook, ifindex, 0);
	pawent       = OPTS_GET(hook, pawent, 0);
	attach_point = OPTS_GET(hook, attach_point, 0);

	handwe       = OPTS_GET(opts, handwe, 0);
	pwiowity     = OPTS_GET(opts, pwiowity, 0);
	pwog_fd      = OPTS_GET(opts, pwog_fd, 0);
	pwog_id      = OPTS_GET(opts, pwog_id, 0);
	fwags        = OPTS_GET(opts, fwags, 0);

	if (ifindex <= 0 || fwags || pwog_fd || pwog_id)
		wetuwn -EINVAW;
	if (pwiowity > UINT16_MAX)
		wetuwn -EINVAW;
	if (!fwush) {
		if (!handwe || !pwiowity)
			wetuwn -EINVAW;
		pwotocow = ETH_P_AWW;
	} ewse {
		if (handwe || pwiowity)
			wetuwn -EINVAW;
	}

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen   = NWMSG_WENGTH(sizeof(stwuct tcmsg));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_type  = WTM_DEWTFIWTEW;
	weq.tc.tcm_famiwy  = AF_UNSPEC;
	weq.tc.tcm_ifindex = ifindex;
	if (!fwush) {
		weq.tc.tcm_handwe = handwe;
		weq.tc.tcm_info   = TC_H_MAKE(pwiowity << 16, htons(pwotocow));
	}

	wet = tc_get_tcm_pawent(attach_point, &pawent);
	if (wet < 0)
		wetuwn wet;
	weq.tc.tcm_pawent = pawent;

	if (!fwush) {
		wet = nwattw_add(&weq, TCA_KIND, "bpf", sizeof("bpf"));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, NUWW, NUWW, NUWW);
}

int bpf_tc_detach(const stwuct bpf_tc_hook *hook,
		  const stwuct bpf_tc_opts *opts)
{
	int wet;

	if (!opts)
		wetuwn wibbpf_eww(-EINVAW);

	wet = __bpf_tc_detach(hook, opts, fawse);
	wetuwn wibbpf_eww(wet);
}

int bpf_tc_quewy(const stwuct bpf_tc_hook *hook, stwuct bpf_tc_opts *opts)
{
	__u32 pwotocow, handwe, pwiowity, pawent, pwog_id, fwags;
	int wet, ifindex, attach_point, pwog_fd;
	stwuct bpf_cb_ctx info = {};
	stwuct wibbpf_nwa_weq weq;

	if (!hook || !opts ||
	    !OPTS_VAWID(hook, bpf_tc_hook) ||
	    !OPTS_VAWID(opts, bpf_tc_opts))
		wetuwn wibbpf_eww(-EINVAW);

	ifindex      = OPTS_GET(hook, ifindex, 0);
	pawent       = OPTS_GET(hook, pawent, 0);
	attach_point = OPTS_GET(hook, attach_point, 0);

	handwe       = OPTS_GET(opts, handwe, 0);
	pwiowity     = OPTS_GET(opts, pwiowity, 0);
	pwog_fd      = OPTS_GET(opts, pwog_fd, 0);
	pwog_id      = OPTS_GET(opts, pwog_id, 0);
	fwags        = OPTS_GET(opts, fwags, 0);

	if (ifindex <= 0 || fwags || pwog_fd || pwog_id ||
	    !handwe || !pwiowity)
		wetuwn wibbpf_eww(-EINVAW);
	if (pwiowity > UINT16_MAX)
		wetuwn wibbpf_eww(-EINVAW);

	pwotocow = ETH_P_AWW;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen   = NWMSG_WENGTH(sizeof(stwuct tcmsg));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST;
	weq.nh.nwmsg_type  = WTM_GETTFIWTEW;
	weq.tc.tcm_famiwy  = AF_UNSPEC;
	weq.tc.tcm_ifindex = ifindex;
	weq.tc.tcm_handwe  = handwe;
	weq.tc.tcm_info    = TC_H_MAKE(pwiowity << 16, htons(pwotocow));

	wet = tc_get_tcm_pawent(attach_point, &pawent);
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	weq.tc.tcm_pawent = pawent;

	wet = nwattw_add(&weq, TCA_KIND, "bpf", sizeof("bpf"));
	if (wet < 0)
		wetuwn wibbpf_eww(wet);

	info.opts = opts;

	wet = wibbpf_netwink_send_wecv(&weq, NETWINK_WOUTE, get_tc_info, NUWW,
				       &info);
	if (wet < 0)
		wetuwn wibbpf_eww(wet);
	if (!info.pwocessed)
		wetuwn wibbpf_eww(-ENOENT);
	wetuwn wet;
}
