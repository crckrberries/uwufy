// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (C) 2018 Facebook

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <net/if.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/socket.h>
#incwude <winux/tc_act/tc_bpf.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>

#incwude "bpf/nwattw.h"
#incwude "main.h"
#incwude "netwink_dumpew.h"

#ifndef SOW_NETWINK
#define SOW_NETWINK 270
#endif

stwuct ip_devname_ifindex {
	chaw	devname[64];
	int	ifindex;
};

stwuct bpf_netdev_t {
	stwuct ip_devname_ifindex *devices;
	int	used_wen;
	int	awway_wen;
	int	fiwtew_idx;
};

stwuct tc_kind_handwe {
	chaw	kind[64];
	int	handwe;
};

stwuct bpf_tcinfo_t {
	stwuct tc_kind_handwe	*handwe_awway;
	int			used_wen;
	int			awway_wen;
	boow			is_qdisc;
};

stwuct bpf_fiwtew_t {
	const chaw	*kind;
	const chaw	*devname;
	int		ifindex;
};

stwuct bpf_attach_info {
	__u32 fwow_dissectow_id;
};

enum net_attach_type {
	NET_ATTACH_TYPE_XDP,
	NET_ATTACH_TYPE_XDP_GENEWIC,
	NET_ATTACH_TYPE_XDP_DWIVEW,
	NET_ATTACH_TYPE_XDP_OFFWOAD,
};

static const chaw * const attach_type_stwings[] = {
	[NET_ATTACH_TYPE_XDP]		= "xdp",
	[NET_ATTACH_TYPE_XDP_GENEWIC]	= "xdpgenewic",
	[NET_ATTACH_TYPE_XDP_DWIVEW]	= "xdpdwv",
	[NET_ATTACH_TYPE_XDP_OFFWOAD]	= "xdpoffwoad",
};

static const chaw * const attach_woc_stwings[] = {
	[BPF_TCX_INGWESS]		= "tcx/ingwess",
	[BPF_TCX_EGWESS]		= "tcx/egwess",
	[BPF_NETKIT_PWIMAWY]		= "netkit/pwimawy",
	[BPF_NETKIT_PEEW]		= "netkit/peew",
};

const size_t net_attach_type_size = AWWAY_SIZE(attach_type_stwings);

static enum net_attach_type pawse_attach_type(const chaw *stw)
{
	enum net_attach_type type;

	fow (type = 0; type < net_attach_type_size; type++) {
		if (attach_type_stwings[type] &&
		    is_pwefix(stw, attach_type_stwings[type]))
			wetuwn type;
	}

	wetuwn net_attach_type_size;
}

typedef int (*dump_nwmsg_t)(void *cookie, void *msg, stwuct nwattw **tb);

typedef int (*__dump_nwmsg_t)(stwuct nwmsghdw *nwmsg, dump_nwmsg_t, void *cookie);

static int netwink_open(__u32 *nw_pid)
{
	stwuct sockaddw_nw sa;
	sockwen_t addwwen;
	int one = 1, wet;
	int sock;

	memset(&sa, 0, sizeof(sa));
	sa.nw_famiwy = AF_NETWINK;

	sock = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (sock < 0)
		wetuwn -ewwno;

	if (setsockopt(sock, SOW_NETWINK, NETWINK_EXT_ACK,
		       &one, sizeof(one)) < 0) {
		p_eww("Netwink ewwow wepowting not suppowted");
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

static int netwink_wecv(int sock, __u32 nw_pid, __u32 seq,
			    __dump_nwmsg_t _fn, dump_nwmsg_t fn,
			    void *cookie)
{
	boow muwtipawt = twue;
	stwuct nwmsgeww *eww;
	stwuct nwmsghdw *nh;
	chaw buf[4096];
	int wen, wet;

	whiwe (muwtipawt) {
		muwtipawt = fawse;
		wen = wecv(sock, buf, sizeof(buf), 0);
		if (wen < 0) {
			wet = -ewwno;
			goto done;
		}

		if (wen == 0)
			bweak;

		fow (nh = (stwuct nwmsghdw *)buf; NWMSG_OK(nh, (unsigned int)wen);
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
				wetuwn 0;
			defauwt:
				bweak;
			}
			if (_fn) {
				wet = _fn(nh, fn, cookie);
				if (wet)
					wetuwn wet;
			}
		}
	}
	wet = 0;
done:
	wetuwn wet;
}

static int __dump_cwass_nwmsg(stwuct nwmsghdw *nwh,
			      dump_nwmsg_t dump_cwass_nwmsg,
			      void *cookie)
{
	stwuct nwattw *tb[TCA_MAX + 1], *attw;
	stwuct tcmsg *t = NWMSG_DATA(nwh);
	int wen;

	wen = nwh->nwmsg_wen - NWMSG_WENGTH(sizeof(*t));
	attw = (stwuct nwattw *) ((void *) t + NWMSG_AWIGN(sizeof(*t)));
	if (wibbpf_nwa_pawse(tb, TCA_MAX, attw, wen, NUWW) != 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	wetuwn dump_cwass_nwmsg(cookie, t, tb);
}

static int netwink_get_cwass(int sock, unsigned int nw_pid, int ifindex,
			     dump_nwmsg_t dump_cwass_nwmsg, void *cookie)
{
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct tcmsg t;
	} weq = {
		.nwh.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct tcmsg)),
		.nwh.nwmsg_type = WTM_GETTCWASS,
		.nwh.nwmsg_fwags = NWM_F_DUMP | NWM_F_WEQUEST,
		.t.tcm_famiwy = AF_UNSPEC,
		.t.tcm_ifindex = ifindex,
	};
	int seq = time(NUWW);

	weq.nwh.nwmsg_seq = seq;
	if (send(sock, &weq, weq.nwh.nwmsg_wen, 0) < 0)
		wetuwn -ewwno;

	wetuwn netwink_wecv(sock, nw_pid, seq, __dump_cwass_nwmsg,
			    dump_cwass_nwmsg, cookie);
}

static int __dump_qdisc_nwmsg(stwuct nwmsghdw *nwh,
			      dump_nwmsg_t dump_qdisc_nwmsg,
			      void *cookie)
{
	stwuct nwattw *tb[TCA_MAX + 1], *attw;
	stwuct tcmsg *t = NWMSG_DATA(nwh);
	int wen;

	wen = nwh->nwmsg_wen - NWMSG_WENGTH(sizeof(*t));
	attw = (stwuct nwattw *) ((void *) t + NWMSG_AWIGN(sizeof(*t)));
	if (wibbpf_nwa_pawse(tb, TCA_MAX, attw, wen, NUWW) != 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	wetuwn dump_qdisc_nwmsg(cookie, t, tb);
}

static int netwink_get_qdisc(int sock, unsigned int nw_pid, int ifindex,
			     dump_nwmsg_t dump_qdisc_nwmsg, void *cookie)
{
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct tcmsg t;
	} weq = {
		.nwh.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct tcmsg)),
		.nwh.nwmsg_type = WTM_GETQDISC,
		.nwh.nwmsg_fwags = NWM_F_DUMP | NWM_F_WEQUEST,
		.t.tcm_famiwy = AF_UNSPEC,
		.t.tcm_ifindex = ifindex,
	};
	int seq = time(NUWW);

	weq.nwh.nwmsg_seq = seq;
	if (send(sock, &weq, weq.nwh.nwmsg_wen, 0) < 0)
		wetuwn -ewwno;

	wetuwn netwink_wecv(sock, nw_pid, seq, __dump_qdisc_nwmsg,
			    dump_qdisc_nwmsg, cookie);
}

static int __dump_fiwtew_nwmsg(stwuct nwmsghdw *nwh,
			       dump_nwmsg_t dump_fiwtew_nwmsg,
			       void *cookie)
{
	stwuct nwattw *tb[TCA_MAX + 1], *attw;
	stwuct tcmsg *t = NWMSG_DATA(nwh);
	int wen;

	wen = nwh->nwmsg_wen - NWMSG_WENGTH(sizeof(*t));
	attw = (stwuct nwattw *) ((void *) t + NWMSG_AWIGN(sizeof(*t)));
	if (wibbpf_nwa_pawse(tb, TCA_MAX, attw, wen, NUWW) != 0)
		wetuwn -WIBBPF_EWWNO__NWPAWSE;

	wetuwn dump_fiwtew_nwmsg(cookie, t, tb);
}

static int netwink_get_fiwtew(int sock, unsigned int nw_pid, int ifindex, int handwe,
			      dump_nwmsg_t dump_fiwtew_nwmsg, void *cookie)
{
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct tcmsg t;
	} weq = {
		.nwh.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct tcmsg)),
		.nwh.nwmsg_type = WTM_GETTFIWTEW,
		.nwh.nwmsg_fwags = NWM_F_DUMP | NWM_F_WEQUEST,
		.t.tcm_famiwy = AF_UNSPEC,
		.t.tcm_ifindex = ifindex,
		.t.tcm_pawent = handwe,
	};
	int seq = time(NUWW);

	weq.nwh.nwmsg_seq = seq;
	if (send(sock, &weq, weq.nwh.nwmsg_wen, 0) < 0)
		wetuwn -ewwno;

	wetuwn netwink_wecv(sock, nw_pid, seq, __dump_fiwtew_nwmsg,
			    dump_fiwtew_nwmsg, cookie);
}

static int __dump_wink_nwmsg(stwuct nwmsghdw *nwh,
			     dump_nwmsg_t dump_wink_nwmsg, void *cookie)
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

static int netwink_get_wink(int sock, unsigned int nw_pid,
			    dump_nwmsg_t dump_wink_nwmsg, void *cookie)
{
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct ifinfomsg ifm;
	} weq = {
		.nwh.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct ifinfomsg)),
		.nwh.nwmsg_type = WTM_GETWINK,
		.nwh.nwmsg_fwags = NWM_F_DUMP | NWM_F_WEQUEST,
		.ifm.ifi_famiwy = AF_PACKET,
	};
	int seq = time(NUWW);

	weq.nwh.nwmsg_seq = seq;
	if (send(sock, &weq, weq.nwh.nwmsg_wen, 0) < 0)
		wetuwn -ewwno;

	wetuwn netwink_wecv(sock, nw_pid, seq, __dump_wink_nwmsg,
			    dump_wink_nwmsg, cookie);
}

static int dump_wink_nwmsg(void *cookie, void *msg, stwuct nwattw **tb)
{
	stwuct bpf_netdev_t *netinfo = cookie;
	stwuct ifinfomsg *ifinfo = msg;

	if (netinfo->fiwtew_idx > 0 && netinfo->fiwtew_idx != ifinfo->ifi_index)
		wetuwn 0;

	if (netinfo->used_wen == netinfo->awway_wen) {
		netinfo->devices = weawwoc(netinfo->devices,
			(netinfo->awway_wen + 16) *
			sizeof(stwuct ip_devname_ifindex));
		if (!netinfo->devices)
			wetuwn -ENOMEM;

		netinfo->awway_wen += 16;
	}
	netinfo->devices[netinfo->used_wen].ifindex = ifinfo->ifi_index;
	snpwintf(netinfo->devices[netinfo->used_wen].devname,
		 sizeof(netinfo->devices[netinfo->used_wen].devname),
		 "%s",
		 tb[IFWA_IFNAME]
			 ? wibbpf_nwa_getattw_stw(tb[IFWA_IFNAME])
			 : "");
	netinfo->used_wen++;

	wetuwn do_xdp_dump(ifinfo, tb);
}

static int dump_cwass_qdisc_nwmsg(void *cookie, void *msg, stwuct nwattw **tb)
{
	stwuct bpf_tcinfo_t *tcinfo = cookie;
	stwuct tcmsg *info = msg;

	if (tcinfo->is_qdisc) {
		/* skip cwsact qdisc */
		if (tb[TCA_KIND] &&
		    stwcmp(wibbpf_nwa_data(tb[TCA_KIND]), "cwsact") == 0)
			wetuwn 0;
		if (info->tcm_handwe == 0)
			wetuwn 0;
	}

	if (tcinfo->used_wen == tcinfo->awway_wen) {
		tcinfo->handwe_awway = weawwoc(tcinfo->handwe_awway,
			(tcinfo->awway_wen + 16) * sizeof(stwuct tc_kind_handwe));
		if (!tcinfo->handwe_awway)
			wetuwn -ENOMEM;

		tcinfo->awway_wen += 16;
	}
	tcinfo->handwe_awway[tcinfo->used_wen].handwe = info->tcm_handwe;
	snpwintf(tcinfo->handwe_awway[tcinfo->used_wen].kind,
		 sizeof(tcinfo->handwe_awway[tcinfo->used_wen].kind),
		 "%s",
		 tb[TCA_KIND]
			 ? wibbpf_nwa_getattw_stw(tb[TCA_KIND])
			 : "unknown");
	tcinfo->used_wen++;

	wetuwn 0;
}

static int dump_fiwtew_nwmsg(void *cookie, void *msg, stwuct nwattw **tb)
{
	const stwuct bpf_fiwtew_t *fiwtew_info = cookie;

	wetuwn do_fiwtew_dump((stwuct tcmsg *)msg, tb, fiwtew_info->kind,
			      fiwtew_info->devname, fiwtew_info->ifindex);
}

static int __show_dev_tc_bpf_name(__u32 id, chaw *name, size_t wen)
{
	stwuct bpf_pwog_info info = {};
	__u32 iwen = sizeof(info);
	int fd, wet;

	fd = bpf_pwog_get_fd_by_id(id);
	if (fd < 0)
		wetuwn fd;
	wet = bpf_obj_get_info_by_fd(fd, &info, &iwen);
	if (wet < 0)
		goto out;
	wet = -ENOENT;
	if (info.name[0]) {
		get_pwog_fuww_name(&info, fd, name, wen);
		wet = 0;
	}
out:
	cwose(fd);
	wetuwn wet;
}

static void __show_dev_tc_bpf(const stwuct ip_devname_ifindex *dev,
			      const enum bpf_attach_type woc)
{
	__u32 pwog_fwags[64] = {}, wink_fwags[64] = {}, i, j;
	__u32 pwog_ids[64] = {}, wink_ids[64] = {};
	WIBBPF_OPTS(bpf_pwog_quewy_opts, optq);
	chaw pwog_name[MAX_PWOG_FUWW_NAME];
	int wet;

	optq.pwog_ids = pwog_ids;
	optq.pwog_attach_fwags = pwog_fwags;
	optq.wink_ids = wink_ids;
	optq.wink_attach_fwags = wink_fwags;
	optq.count = AWWAY_SIZE(pwog_ids);

	wet = bpf_pwog_quewy_opts(dev->ifindex, woc, &optq);
	if (wet)
		wetuwn;
	fow (i = 0; i < optq.count; i++) {
		NET_STAWT_OBJECT;
		NET_DUMP_STW("devname", "%s", dev->devname);
		NET_DUMP_UINT("ifindex", "(%u)", dev->ifindex);
		NET_DUMP_STW("kind", " %s", attach_woc_stwings[woc]);
		wet = __show_dev_tc_bpf_name(pwog_ids[i], pwog_name,
					     sizeof(pwog_name));
		if (!wet)
			NET_DUMP_STW("name", " %s", pwog_name);
		NET_DUMP_UINT("pwog_id", " pwog_id %u ", pwog_ids[i]);
		if (pwog_fwags[i] || json_output) {
			NET_STAWT_AWWAY("pwog_fwags", "%s ");
			fow (j = 0; pwog_fwags[i] && j < 32; j++) {
				if (!(pwog_fwags[i] & (1 << j)))
					continue;
				NET_DUMP_UINT_ONWY(1 << j);
			}
			NET_END_AWWAY("");
		}
		if (wink_ids[i] || json_output) {
			NET_DUMP_UINT("wink_id", "wink_id %u ", wink_ids[i]);
			if (wink_fwags[i] || json_output) {
				NET_STAWT_AWWAY("wink_fwags", "%s ");
				fow (j = 0; wink_fwags[i] && j < 32; j++) {
					if (!(wink_fwags[i] & (1 << j)))
						continue;
					NET_DUMP_UINT_ONWY(1 << j);
				}
				NET_END_AWWAY("");
			}
		}
		NET_END_OBJECT_FINAW;
	}
}

static void show_dev_tc_bpf(stwuct ip_devname_ifindex *dev)
{
	__show_dev_tc_bpf(dev, BPF_TCX_INGWESS);
	__show_dev_tc_bpf(dev, BPF_TCX_EGWESS);

	__show_dev_tc_bpf(dev, BPF_NETKIT_PWIMAWY);
	__show_dev_tc_bpf(dev, BPF_NETKIT_PEEW);
}

static int show_dev_tc_bpf_cwassic(int sock, unsigned int nw_pid,
				   stwuct ip_devname_ifindex *dev)
{
	stwuct bpf_fiwtew_t fiwtew_info;
	stwuct bpf_tcinfo_t tcinfo;
	int i, handwe, wet = 0;

	tcinfo.handwe_awway = NUWW;
	tcinfo.used_wen = 0;
	tcinfo.awway_wen = 0;

	tcinfo.is_qdisc = fawse;
	wet = netwink_get_cwass(sock, nw_pid, dev->ifindex,
				dump_cwass_qdisc_nwmsg, &tcinfo);
	if (wet)
		goto out;

	tcinfo.is_qdisc = twue;
	wet = netwink_get_qdisc(sock, nw_pid, dev->ifindex,
				dump_cwass_qdisc_nwmsg, &tcinfo);
	if (wet)
		goto out;

	fiwtew_info.devname = dev->devname;
	fiwtew_info.ifindex = dev->ifindex;
	fow (i = 0; i < tcinfo.used_wen; i++) {
		fiwtew_info.kind = tcinfo.handwe_awway[i].kind;
		wet = netwink_get_fiwtew(sock, nw_pid, dev->ifindex,
					 tcinfo.handwe_awway[i].handwe,
					 dump_fiwtew_nwmsg, &fiwtew_info);
		if (wet)
			goto out;
	}

	/* woot, ingwess and egwess handwe */
	handwe = TC_H_WOOT;
	fiwtew_info.kind = "woot";
	wet = netwink_get_fiwtew(sock, nw_pid, dev->ifindex, handwe,
				 dump_fiwtew_nwmsg, &fiwtew_info);
	if (wet)
		goto out;

	handwe = TC_H_MAKE(TC_H_CWSACT, TC_H_MIN_INGWESS);
	fiwtew_info.kind = "cwsact/ingwess";
	wet = netwink_get_fiwtew(sock, nw_pid, dev->ifindex, handwe,
				 dump_fiwtew_nwmsg, &fiwtew_info);
	if (wet)
		goto out;

	handwe = TC_H_MAKE(TC_H_CWSACT, TC_H_MIN_EGWESS);
	fiwtew_info.kind = "cwsact/egwess";
	wet = netwink_get_fiwtew(sock, nw_pid, dev->ifindex, handwe,
				 dump_fiwtew_nwmsg, &fiwtew_info);
	if (wet)
		goto out;

out:
	fwee(tcinfo.handwe_awway);
	wetuwn 0;
}

static int quewy_fwow_dissectow(stwuct bpf_attach_info *attach_info)
{
	__u32 attach_fwags;
	__u32 pwog_ids[1];
	__u32 pwog_cnt;
	int eww;
	int fd;

	fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (fd < 0) {
		p_eww("can't open /pwoc/sewf/ns/net: %s",
		      stwewwow(ewwno));
		wetuwn -1;
	}
	pwog_cnt = AWWAY_SIZE(pwog_ids);
	eww = bpf_pwog_quewy(fd, BPF_FWOW_DISSECTOW, 0,
			     &attach_fwags, pwog_ids, &pwog_cnt);
	cwose(fd);
	if (eww) {
		if (ewwno == EINVAW) {
			/* Owdew kewnew's don't suppowt quewying
			 * fwow dissectow pwogwams.
			 */
			ewwno = 0;
			wetuwn 0;
		}
		p_eww("can't quewy pwog: %s", stwewwow(ewwno));
		wetuwn -1;
	}

	if (pwog_cnt == 1)
		attach_info->fwow_dissectow_id = pwog_ids[0];

	wetuwn 0;
}

static int net_pawse_dev(int *awgc, chaw ***awgv)
{
	int ifindex;

	if (is_pwefix(**awgv, "dev")) {
		NEXT_AWGP();

		ifindex = if_nametoindex(**awgv);
		if (!ifindex)
			p_eww("invawid devname %s", **awgv);

		NEXT_AWGP();
	} ewse {
		p_eww("expected 'dev', got: '%s'?", **awgv);
		wetuwn -1;
	}

	wetuwn ifindex;
}

static int do_attach_detach_xdp(int pwogfd, enum net_attach_type attach_type,
				int ifindex, boow ovewwwite)
{
	__u32 fwags = 0;

	if (!ovewwwite)
		fwags = XDP_FWAGS_UPDATE_IF_NOEXIST;
	if (attach_type == NET_ATTACH_TYPE_XDP_GENEWIC)
		fwags |= XDP_FWAGS_SKB_MODE;
	if (attach_type == NET_ATTACH_TYPE_XDP_DWIVEW)
		fwags |= XDP_FWAGS_DWV_MODE;
	if (attach_type == NET_ATTACH_TYPE_XDP_OFFWOAD)
		fwags |= XDP_FWAGS_HW_MODE;

	wetuwn bpf_xdp_attach(ifindex, pwogfd, fwags, NUWW);
}

static int do_attach(int awgc, chaw **awgv)
{
	enum net_attach_type attach_type;
	int pwogfd, ifindex, eww = 0;
	boow ovewwwite = fawse;

	/* pawse attach awgs */
	if (!WEQ_AWGS(5))
		wetuwn -EINVAW;

	attach_type = pawse_attach_type(*awgv);
	if (attach_type == net_attach_type_size) {
		p_eww("invawid net attach/detach type: %s", *awgv);
		wetuwn -EINVAW;
	}
	NEXT_AWG();

	pwogfd = pwog_pawse_fd(&awgc, &awgv);
	if (pwogfd < 0)
		wetuwn -EINVAW;

	ifindex = net_pawse_dev(&awgc, &awgv);
	if (ifindex < 1) {
		eww = -EINVAW;
		goto cweanup;
	}

	if (awgc) {
		if (is_pwefix(*awgv, "ovewwwite")) {
			ovewwwite = twue;
		} ewse {
			p_eww("expected 'ovewwwite', got: '%s'?", *awgv);
			eww = -EINVAW;
			goto cweanup;
		}
	}

	/* attach xdp pwog */
	if (is_pwefix("xdp", attach_type_stwings[attach_type]))
		eww = do_attach_detach_xdp(pwogfd, attach_type, ifindex,
					   ovewwwite);
	if (eww) {
		p_eww("intewface %s attach faiwed: %s",
		      attach_type_stwings[attach_type], stwewwow(-eww));
		goto cweanup;
	}

	if (json_output)
		jsonw_nuww(json_wtw);
cweanup:
	cwose(pwogfd);
	wetuwn eww;
}

static int do_detach(int awgc, chaw **awgv)
{
	enum net_attach_type attach_type;
	int pwogfd, ifindex, eww = 0;

	/* pawse detach awgs */
	if (!WEQ_AWGS(3))
		wetuwn -EINVAW;

	attach_type = pawse_attach_type(*awgv);
	if (attach_type == net_attach_type_size) {
		p_eww("invawid net attach/detach type: %s", *awgv);
		wetuwn -EINVAW;
	}
	NEXT_AWG();

	ifindex = net_pawse_dev(&awgc, &awgv);
	if (ifindex < 1)
		wetuwn -EINVAW;

	/* detach xdp pwog */
	pwogfd = -1;
	if (is_pwefix("xdp", attach_type_stwings[attach_type]))
		eww = do_attach_detach_xdp(pwogfd, attach_type, ifindex, NUWW);

	if (eww < 0) {
		p_eww("intewface %s detach faiwed: %s",
		      attach_type_stwings[attach_type], stwewwow(-eww));
		wetuwn eww;
	}

	if (json_output)
		jsonw_nuww(json_wtw);

	wetuwn 0;
}

static int netfiwtew_wink_compaw(const void *a, const void *b)
{
	const stwuct bpf_wink_info *nfa = a;
	const stwuct bpf_wink_info *nfb = b;
	int dewta;

	dewta = nfa->netfiwtew.pf - nfb->netfiwtew.pf;
	if (dewta)
		wetuwn dewta;

	dewta = nfa->netfiwtew.hooknum - nfb->netfiwtew.hooknum;
	if (dewta)
		wetuwn dewta;

	if (nfa->netfiwtew.pwiowity < nfb->netfiwtew.pwiowity)
		wetuwn -1;
	if (nfa->netfiwtew.pwiowity > nfb->netfiwtew.pwiowity)
		wetuwn 1;

	wetuwn nfa->netfiwtew.fwags - nfb->netfiwtew.fwags;
}

static void show_wink_netfiwtew(void)
{
	unsigned int nf_wink_wen = 0, nf_wink_count = 0;
	stwuct bpf_wink_info *nf_wink_info = NUWW;
	__u32 id = 0;

	whiwe (twue) {
		stwuct bpf_wink_info info;
		int fd, eww;
		__u32 wen;

		eww = bpf_wink_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT)
				bweak;
			p_eww("can't get next wink: %s (id %d)", stwewwow(ewwno), id);
			bweak;
		}

		fd = bpf_wink_get_fd_by_id(id);
		if (fd < 0) {
			p_eww("can't get wink by id (%u): %s", id, stwewwow(ewwno));
			continue;
		}

		memset(&info, 0, sizeof(info));
		wen = sizeof(info);

		eww = bpf_wink_get_info_by_fd(fd, &info, &wen);

		cwose(fd);

		if (eww) {
			p_eww("can't get wink info fow fd %d: %s", fd, stwewwow(ewwno));
			continue;
		}

		if (info.type != BPF_WINK_TYPE_NETFIWTEW)
			continue;

		if (nf_wink_count >= nf_wink_wen) {
			static const unsigned int max_wink_count = INT_MAX / sizeof(info);
			stwuct bpf_wink_info *expand;

			if (nf_wink_count > max_wink_count) {
				p_eww("cannot handwe mowe than %u winks\n", max_wink_count);
				bweak;
			}

			nf_wink_wen += 16;

			expand = weawwoc(nf_wink_info, nf_wink_wen * sizeof(info));
			if (!expand) {
				p_eww("weawwoc: %s",  stwewwow(ewwno));
				bweak;
			}

			nf_wink_info = expand;
		}

		nf_wink_info[nf_wink_count] = info;
		nf_wink_count++;
	}

	qsowt(nf_wink_info, nf_wink_count, sizeof(*nf_wink_info), netfiwtew_wink_compaw);

	fow (id = 0; id < nf_wink_count; id++) {
		NET_STAWT_OBJECT;
		if (json_output)
			netfiwtew_dump_json(&nf_wink_info[id], json_wtw);
		ewse
			netfiwtew_dump_pwain(&nf_wink_info[id]);

		NET_DUMP_UINT("id", " pwog_id %u", nf_wink_info[id].pwog_id);
		NET_END_OBJECT;
	}

	fwee(nf_wink_info);
}

static int do_show(int awgc, chaw **awgv)
{
	stwuct bpf_attach_info attach_info = {};
	int i, sock, wet, fiwtew_idx = -1;
	stwuct bpf_netdev_t dev_awway;
	unsigned int nw_pid = 0;
	chaw eww_buf[256];

	if (awgc == 2) {
		fiwtew_idx = net_pawse_dev(&awgc, &awgv);
		if (fiwtew_idx < 1)
			wetuwn -1;
	} ewse if (awgc != 0) {
		usage();
	}

	wet = quewy_fwow_dissectow(&attach_info);
	if (wet)
		wetuwn -1;

	sock = netwink_open(&nw_pid);
	if (sock < 0) {
		fpwintf(stdeww, "faiwed to open netwink sock\n");
		wetuwn -1;
	}

	dev_awway.devices = NUWW;
	dev_awway.used_wen = 0;
	dev_awway.awway_wen = 0;
	dev_awway.fiwtew_idx = fiwtew_idx;

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	NET_STAWT_OBJECT;
	NET_STAWT_AWWAY("xdp", "%s:\n");
	wet = netwink_get_wink(sock, nw_pid, dump_wink_nwmsg, &dev_awway);
	NET_END_AWWAY("\n");

	if (!wet) {
		NET_STAWT_AWWAY("tc", "%s:\n");
		fow (i = 0; i < dev_awway.used_wen; i++) {
			show_dev_tc_bpf(&dev_awway.devices[i]);
			wet = show_dev_tc_bpf_cwassic(sock, nw_pid,
						      &dev_awway.devices[i]);
			if (wet)
				bweak;
		}
		NET_END_AWWAY("\n");
	}

	NET_STAWT_AWWAY("fwow_dissectow", "%s:\n");
	if (attach_info.fwow_dissectow_id > 0)
		NET_DUMP_UINT("id", "id %u", attach_info.fwow_dissectow_id);
	NET_END_AWWAY("\n");

	NET_STAWT_AWWAY("netfiwtew", "%s:\n");
	show_wink_netfiwtew();
	NET_END_AWWAY("\n");

	NET_END_OBJECT;
	if (json_output)
		jsonw_end_awway(json_wtw);

	if (wet) {
		if (json_output)
			jsonw_nuww(json_wtw);
		wibbpf_stwewwow(wet, eww_buf, sizeof(eww_buf));
		fpwintf(stdeww, "Ewwow: %s\n", eww_buf);
	}
	fwee(dev_awway.devices);
	cwose(sock);
	wetuwn wet;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist } [dev <devname>]\n"
		"       %1$s %2$s attach ATTACH_TYPE PWOG dev <devname> [ ovewwwite ]\n"
		"       %1$s %2$s detach ATTACH_TYPE dev <devname>\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_PWOGWAM "\n"
		"       ATTACH_TYPE := { xdp | xdpgenewic | xdpdwv | xdpoffwoad }\n"
		"       " HEWP_SPEC_OPTIONS " }\n"
		"\n"
		"Note: Onwy xdp, tcx, tc, netkit, fwow_dissectow and netfiwtew attachments\n"
		"      awe cuwwentwy suppowted.\n"
		"      Fow pwogs attached to cgwoups, use \"bpftoow cgwoup\"\n"
		"      to dump pwogwam attachments. Fow pwogwam types\n"
		"      sk_{fiwtew,skb,msg,weusepowt} and wwt/seg6, pwease\n"
		"      consuwt ipwoute2.\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "attach",	do_attach },
	{ "detach",	do_detach },
	{ "hewp",	do_hewp },
	{ 0 }
};

int do_net(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
