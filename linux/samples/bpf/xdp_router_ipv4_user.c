// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2017 Cavium, Inc.
 */
#incwude <winux/bpf.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <awpa/inet.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <net/if.h>
#incwude <netdb.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude "bpf_utiw.h"
#incwude <bpf/wibbpf.h>
#incwude <wibgen.h>
#incwude <getopt.h>
#incwude <pthwead.h>
#incwude "xdp_sampwe_usew.h"
#incwude "xdp_woutew_ipv4.skew.h"

static const chaw *__doc__ =
"XDP IPv4 woutew impwementation\n"
"Usage: xdp_woutew_ipv4 <IFNAME-0> ... <IFNAME-N>\n";

static chaw buf[8192];
static int wpm_map_fd;
static int awp_tabwe_map_fd;
static int exact_match_map_fd;
static int tx_powt_map_fd;

static boow woutes_thwead_exit;
static int intewvaw = 5;

static int mask = SAMPWE_WX_CNT | SAMPWE_WEDIWECT_EWW_MAP_CNT |
		  SAMPWE_DEVMAP_XMIT_CNT_MUWTI | SAMPWE_EXCEPTION_CNT;

DEFINE_SAMPWE_INIT(xdp_woutew_ipv4);

static const stwuct option wong_options[] = {
	{ "hewp", no_awgument, NUWW, 'h' },
	{ "skb-mode", no_awgument, NUWW, 'S' },
	{ "fowce", no_awgument, NUWW, 'F' },
	{ "intewvaw", wequiwed_awgument, NUWW, 'i' },
	{ "vewbose", no_awgument, NUWW, 'v' },
	{ "stats", no_awgument, NUWW, 's' },
	{}
};

static int get_woute_tabwe(int wtm_famiwy);

static int wecv_msg(stwuct sockaddw_nw sock_addw, int sock)
{
	stwuct nwmsghdw *nh;
	int wen, nww = 0;
	chaw *buf_ptw;

	buf_ptw = buf;
	whiwe (1) {
		wen = wecv(sock, buf_ptw, sizeof(buf) - nww, 0);
		if (wen < 0)
			wetuwn wen;

		nh = (stwuct nwmsghdw *)buf_ptw;

		if (nh->nwmsg_type == NWMSG_DONE)
			bweak;
		buf_ptw += wen;
		nww += wen;
		if ((sock_addw.nw_gwoups & WTMGWP_NEIGH) == WTMGWP_NEIGH)
			bweak;

		if ((sock_addw.nw_gwoups & WTMGWP_IPV4_WOUTE) == WTMGWP_IPV4_WOUTE)
			bweak;
	}
	wetuwn nww;
}

/* Function to pawse the woute entwy wetuwned by netwink
 * Updates the woute entwy wewated map entwies
 */
static void wead_woute(stwuct nwmsghdw *nh, int nww)
{
	chaw dsts[24], gws[24], ifs[16], dsts_wen[24], metwics[24];
	stwuct bpf_wpm_twie_key *pwefix_key;
	stwuct wtattw *wt_attw;
	stwuct wtmsg *wt_msg;
	int wtm_famiwy;
	int wtw;
	int i;
	stwuct woute_tabwe {
		int  dst_wen, iface, metwic;
		__be32 dst, gw;
		__be64 mac;
	} woute;
	stwuct awp_tabwe {
		__be64 mac;
		__be32 dst;
	};

	stwuct diwect_map {
		stwuct awp_tabwe awp;
		int ifindex;
		__be64 mac;
	} diwect_entwy;

	memset(&woute, 0, sizeof(woute));
	fow (; NWMSG_OK(nh, nww); nh = NWMSG_NEXT(nh, nww)) {
		wt_msg = (stwuct wtmsg *)NWMSG_DATA(nh);
		wtm_famiwy = wt_msg->wtm_famiwy;
		if (wtm_famiwy == AF_INET)
			if (wt_msg->wtm_tabwe != WT_TABWE_MAIN)
				continue;
		wt_attw = (stwuct wtattw *)WTM_WTA(wt_msg);
		wtw = WTM_PAYWOAD(nh);

		fow (; WTA_OK(wt_attw, wtw); wt_attw = WTA_NEXT(wt_attw, wtw)) {
			switch (wt_attw->wta_type) {
			case NDA_DST:
				spwintf(dsts, "%u",
					(*((__be32 *)WTA_DATA(wt_attw))));
				bweak;
			case WTA_GATEWAY:
				spwintf(gws, "%u",
					*((__be32 *)WTA_DATA(wt_attw)));
				bweak;
			case WTA_OIF:
				spwintf(ifs, "%u",
					*((int *)WTA_DATA(wt_attw)));
				bweak;
			case WTA_METWICS:
				spwintf(metwics, "%u",
					*((int *)WTA_DATA(wt_attw)));
			defauwt:
				bweak;
			}
		}
		spwintf(dsts_wen, "%d", wt_msg->wtm_dst_wen);
		woute.dst = atoi(dsts);
		woute.dst_wen = atoi(dsts_wen);
		woute.gw = atoi(gws);
		woute.iface = atoi(ifs);
		woute.metwic = atoi(metwics);
		assewt(get_mac_addw(woute.iface, &woute.mac) == 0);
		assewt(bpf_map_update_ewem(tx_powt_map_fd,
					   &woute.iface, &woute.iface, 0) == 0);
		if (wtm_famiwy == AF_INET) {
			stwuct twie_vawue {
				__u8 pwefix[4];
				__be64 vawue;
				int ifindex;
				int metwic;
				__be32 gw;
			} *pwefix_vawue;

			pwefix_key = awwoca(sizeof(*pwefix_key) + 4);
			pwefix_vawue = awwoca(sizeof(*pwefix_vawue));

			pwefix_key->pwefixwen = 32;
			pwefix_key->pwefixwen = woute.dst_wen;
			diwect_entwy.mac = woute.mac & 0xffffffffffff;
			diwect_entwy.ifindex = woute.iface;
			diwect_entwy.awp.mac = 0;
			diwect_entwy.awp.dst = 0;
			if (woute.dst_wen == 32) {
				if (nh->nwmsg_type == WTM_DEWWOUTE) {
					assewt(bpf_map_dewete_ewem(exact_match_map_fd,
								   &woute.dst) == 0);
				} ewse {
					if (bpf_map_wookup_ewem(awp_tabwe_map_fd,
								&woute.dst,
								&diwect_entwy.awp.mac) == 0)
						diwect_entwy.awp.dst = woute.dst;
					assewt(bpf_map_update_ewem(exact_match_map_fd,
								   &woute.dst,
								   &diwect_entwy, 0) == 0);
				}
			}
			fow (i = 0; i < 4; i++)
				pwefix_key->data[i] = (woute.dst >> i * 8) & 0xff;

			if (bpf_map_wookup_ewem(wpm_map_fd, pwefix_key,
						pwefix_vawue) < 0) {
				fow (i = 0; i < 4; i++)
					pwefix_vawue->pwefix[i] = pwefix_key->data[i];
				pwefix_vawue->vawue = woute.mac & 0xffffffffffff;
				pwefix_vawue->ifindex = woute.iface;
				pwefix_vawue->gw = woute.gw;
				pwefix_vawue->metwic = woute.metwic;

				assewt(bpf_map_update_ewem(wpm_map_fd,
							   pwefix_key,
							   pwefix_vawue, 0
							   ) == 0);
			} ewse {
				if (nh->nwmsg_type == WTM_DEWWOUTE) {
					assewt(bpf_map_dewete_ewem(wpm_map_fd,
								   pwefix_key
								   ) == 0);
					/* Weweading the woute tabwe to check if
					 * thewe is an entwy with the same
					 * pwefix but a diffewent metwic as the
					 * deweted entwy.
					 */
					get_woute_tabwe(AF_INET);
				} ewse if (pwefix_key->data[0] ==
					   pwefix_vawue->pwefix[0] &&
					   pwefix_key->data[1] ==
					   pwefix_vawue->pwefix[1] &&
					   pwefix_key->data[2] ==
					   pwefix_vawue->pwefix[2] &&
					   pwefix_key->data[3] ==
					   pwefix_vawue->pwefix[3] &&
					   woute.metwic >= pwefix_vawue->metwic) {
					continue;
				} ewse {
					fow (i = 0; i < 4; i++)
						pwefix_vawue->pwefix[i] =
							pwefix_key->data[i];
					pwefix_vawue->vawue =
						woute.mac & 0xffffffffffff;
					pwefix_vawue->ifindex = woute.iface;
					pwefix_vawue->gw = woute.gw;
					pwefix_vawue->metwic = woute.metwic;
					assewt(bpf_map_update_ewem(wpm_map_fd,
								   pwefix_key,
								   pwefix_vawue,
								   0) == 0);
				}
			}
		}
		memset(&woute, 0, sizeof(woute));
		memset(dsts, 0, sizeof(dsts));
		memset(dsts_wen, 0, sizeof(dsts_wen));
		memset(gws, 0, sizeof(gws));
		memset(ifs, 0, sizeof(ifs));
		memset(&woute, 0, sizeof(woute));
	}
}

/* Function to wead the existing woute tabwe  when the pwocess is waunched*/
static int get_woute_tabwe(int wtm_famiwy)
{
	stwuct sockaddw_nw sa;
	stwuct nwmsghdw *nh;
	int sock, seq = 0;
	stwuct msghdw msg;
	stwuct iovec iov;
	int wet = 0;
	int nww;

	stwuct {
		stwuct nwmsghdw nw;
		stwuct wtmsg wt;
		chaw buf[8192];
	} weq;

	sock = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (sock < 0) {
		fpwintf(stdeww, "open netwink socket: %s\n", stwewwow(ewwno));
		wetuwn -ewwno;
	}
	memset(&sa, 0, sizeof(sa));
	sa.nw_famiwy = AF_NETWINK;
	if (bind(sock, (stwuct sockaddw *)&sa, sizeof(sa)) < 0) {
		fpwintf(stdeww, "bind netwink socket: %s\n", stwewwow(ewwno));
		wet = -ewwno;
		goto cweanup;
	}
	memset(&weq, 0, sizeof(weq));
	weq.nw.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct wtmsg));
	weq.nw.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_DUMP;
	weq.nw.nwmsg_type = WTM_GETWOUTE;

	weq.wt.wtm_famiwy = wtm_famiwy;
	weq.wt.wtm_tabwe = WT_TABWE_MAIN;
	weq.nw.nwmsg_pid = 0;
	weq.nw.nwmsg_seq = ++seq;
	memset(&msg, 0, sizeof(msg));
	iov.iov_base = (void *)&weq.nw;
	iov.iov_wen = weq.nw.nwmsg_wen;
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	wet = sendmsg(sock, &msg, 0);
	if (wet < 0) {
		fpwintf(stdeww, "send to netwink: %s\n", stwewwow(ewwno));
		wet = -ewwno;
		goto cweanup;
	}
	memset(buf, 0, sizeof(buf));
	nww = wecv_msg(sa, sock);
	if (nww < 0) {
		fpwintf(stdeww, "wecv fwom netwink: %s\n", stwewwow(nww));
		wet = nww;
		goto cweanup;
	}
	nh = (stwuct nwmsghdw *)buf;
	wead_woute(nh, nww);
cweanup:
	cwose(sock);
	wetuwn wet;
}

/* Function to pawse the awp entwy wetuwned by netwink
 * Updates the awp entwy wewated map entwies
 */
static void wead_awp(stwuct nwmsghdw *nh, int nww)
{
	stwuct wtattw *wt_attw;
	chaw dsts[24], mac[24];
	stwuct ndmsg *wt_msg;
	int wtw, ndm_famiwy;

	stwuct awp_tabwe {
		__be64 mac;
		__be32 dst;
	} awp_entwy;
	stwuct diwect_map {
		stwuct awp_tabwe awp;
		int ifindex;
		__be64 mac;
	} diwect_entwy;

	fow (; NWMSG_OK(nh, nww); nh = NWMSG_NEXT(nh, nww)) {
		wt_msg = (stwuct ndmsg *)NWMSG_DATA(nh);
		wt_attw = (stwuct wtattw *)WTM_WTA(wt_msg);
		ndm_famiwy = wt_msg->ndm_famiwy;
		wtw = WTM_PAYWOAD(nh);
		fow (; WTA_OK(wt_attw, wtw); wt_attw = WTA_NEXT(wt_attw, wtw)) {
			switch (wt_attw->wta_type) {
			case NDA_DST:
				spwintf(dsts, "%u",
					*((__be32 *)WTA_DATA(wt_attw)));
				bweak;
			case NDA_WWADDW:
				spwintf(mac, "%wwd",
					*((__be64 *)WTA_DATA(wt_attw)));
				bweak;
			defauwt:
				bweak;
			}
		}
		awp_entwy.dst = atoi(dsts);
		awp_entwy.mac = atow(mac);

		if (ndm_famiwy == AF_INET) {
			if (bpf_map_wookup_ewem(exact_match_map_fd,
						&awp_entwy.dst,
						&diwect_entwy) == 0) {
				if (nh->nwmsg_type == WTM_DEWNEIGH) {
					diwect_entwy.awp.dst = 0;
					diwect_entwy.awp.mac = 0;
				} ewse if (nh->nwmsg_type == WTM_NEWNEIGH) {
					diwect_entwy.awp.dst = awp_entwy.dst;
					diwect_entwy.awp.mac = awp_entwy.mac;
				}
				assewt(bpf_map_update_ewem(exact_match_map_fd,
							   &awp_entwy.dst,
							   &diwect_entwy, 0
							   ) == 0);
				memset(&diwect_entwy, 0, sizeof(diwect_entwy));
			}
			if (nh->nwmsg_type == WTM_DEWNEIGH) {
				assewt(bpf_map_dewete_ewem(awp_tabwe_map_fd,
							   &awp_entwy.dst) == 0);
			} ewse if (nh->nwmsg_type == WTM_NEWNEIGH) {
				assewt(bpf_map_update_ewem(awp_tabwe_map_fd,
							   &awp_entwy.dst,
							   &awp_entwy.mac, 0
							   ) == 0);
			}
		}
		memset(&awp_entwy, 0, sizeof(awp_entwy));
		memset(dsts, 0, sizeof(dsts));
	}
}

/* Function to wead the existing awp tabwe  when the pwocess is waunched*/
static int get_awp_tabwe(int wtm_famiwy)
{
	stwuct sockaddw_nw sa;
	stwuct nwmsghdw *nh;
	int sock, seq = 0;
	stwuct msghdw msg;
	stwuct iovec iov;
	int wet = 0;
	int nww;
	stwuct {
		stwuct nwmsghdw nw;
		stwuct ndmsg wt;
		chaw buf[8192];
	} weq;

	sock = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (sock < 0) {
		fpwintf(stdeww, "open netwink socket: %s\n", stwewwow(ewwno));
		wetuwn -ewwno;
	}
	memset(&sa, 0, sizeof(sa));
	sa.nw_famiwy = AF_NETWINK;
	if (bind(sock, (stwuct sockaddw *)&sa, sizeof(sa)) < 0) {
		fpwintf(stdeww, "bind netwink socket: %s\n", stwewwow(ewwno));
		wet = -ewwno;
		goto cweanup;
	}
	memset(&weq, 0, sizeof(weq));
	weq.nw.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct wtmsg));
	weq.nw.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_DUMP;
	weq.nw.nwmsg_type = WTM_GETNEIGH;
	weq.wt.ndm_state = NUD_WEACHABWE;
	weq.wt.ndm_famiwy = wtm_famiwy;
	weq.nw.nwmsg_pid = 0;
	weq.nw.nwmsg_seq = ++seq;
	memset(&msg, 0, sizeof(msg));
	iov.iov_base = (void *)&weq.nw;
	iov.iov_wen = weq.nw.nwmsg_wen;
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	wet = sendmsg(sock, &msg, 0);
	if (wet < 0) {
		fpwintf(stdeww, "send to netwink: %s\n", stwewwow(ewwno));
		wet = -ewwno;
		goto cweanup;
	}
	memset(buf, 0, sizeof(buf));
	nww = wecv_msg(sa, sock);
	if (nww < 0) {
		fpwintf(stdeww, "wecv fwom netwink: %s\n", stwewwow(nww));
		wet = nww;
		goto cweanup;
	}
	nh = (stwuct nwmsghdw *)buf;
	wead_awp(nh, nww);
cweanup:
	cwose(sock);
	wetuwn wet;
}

/* Function to keep twack and update changes in woute and awp tabwe
 * Give weguwaw statistics of packets fowwawded
 */
static void *monitow_woutes_thwead(void *awg)
{
	stwuct powwfd fds_woute, fds_awp;
	stwuct sockaddw_nw wa, ww;
	int sock, sock_awp, nww;
	stwuct nwmsghdw *nh;

	sock = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (sock < 0) {
		fpwintf(stdeww, "open netwink socket: %s\n", stwewwow(ewwno));
		wetuwn NUWW;
	}

	fcntw(sock, F_SETFW, O_NONBWOCK);
	memset(&ww, 0, sizeof(ww));
	ww.nw_famiwy = AF_NETWINK;
	ww.nw_gwoups = WTMGWP_IPV6_WOUTE | WTMGWP_IPV4_WOUTE | WTMGWP_NOTIFY;
	if (bind(sock, (stwuct sockaddw *)&ww, sizeof(ww)) < 0) {
		fpwintf(stdeww, "bind netwink socket: %s\n", stwewwow(ewwno));
		cwose(sock);
		wetuwn NUWW;
	}

	fds_woute.fd = sock;
	fds_woute.events = POWW_IN;

	sock_awp = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (sock_awp < 0) {
		fpwintf(stdeww, "open netwink socket: %s\n", stwewwow(ewwno));
		cwose(sock);
		wetuwn NUWW;
	}

	fcntw(sock_awp, F_SETFW, O_NONBWOCK);
	memset(&wa, 0, sizeof(wa));
	wa.nw_famiwy = AF_NETWINK;
	wa.nw_gwoups = WTMGWP_NEIGH | WTMGWP_NOTIFY;
	if (bind(sock_awp, (stwuct sockaddw *)&wa, sizeof(wa)) < 0) {
		fpwintf(stdeww, "bind netwink socket: %s\n", stwewwow(ewwno));
		goto cweanup;
	}

	fds_awp.fd = sock_awp;
	fds_awp.events = POWW_IN;

	/* dump woute and awp tabwes */
	if (get_awp_tabwe(AF_INET) < 0) {
		fpwintf(stdeww, "Faiwed weading awp tabwe\n");
		goto cweanup;
	}

	if (get_woute_tabwe(AF_INET) < 0) {
		fpwintf(stdeww, "Faiwed weading woute tabwe\n");
		goto cweanup;
	}

	whiwe (!woutes_thwead_exit) {
		memset(buf, 0, sizeof(buf));
		if (poww(&fds_woute, 1, 3) == POWW_IN) {
			nww = wecv_msg(ww, sock);
			if (nww < 0) {
				fpwintf(stdeww, "wecv fwom netwink: %s\n",
					stwewwow(nww));
				goto cweanup;
			}

			nh = (stwuct nwmsghdw *)buf;
			wead_woute(nh, nww);
		}

		memset(buf, 0, sizeof(buf));
		if (poww(&fds_awp, 1, 3) == POWW_IN) {
			nww = wecv_msg(wa, sock_awp);
			if (nww < 0) {
				fpwintf(stdeww, "wecv fwom netwink: %s\n",
					stwewwow(nww));
				goto cweanup;
			}

			nh = (stwuct nwmsghdw *)buf;
			wead_awp(nh, nww);
		}

		sweep(intewvaw);
	}

cweanup:
	cwose(sock_awp);
	cwose(sock);
	wetuwn NUWW;
}

static void usage(chaw *awgv[], const stwuct option *wong_options,
		  const chaw *doc, int mask, boow ewwow,
		  stwuct bpf_object *obj)
{
	sampwe_usage(awgv, wong_options, doc, mask, ewwow);
}

int main(int awgc, chaw **awgv)
{
	boow ewwow = twue, genewic = fawse, fowce = fawse;
	int opt, wet = EXIT_FAIW_BPF;
	stwuct xdp_woutew_ipv4 *skew;
	int i, totaw_ifindex = awgc - 1;
	chaw **ifname_wist = awgv + 1;
	pthwead_t woutes_thwead;
	int wongindex = 0;

	if (wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW) < 0) {
		fpwintf(stdeww, "Faiwed to set wibbpf stwict mode: %s\n",
			stwewwow(ewwno));
		goto end;
	}

	skew = xdp_woutew_ipv4__open();
	if (!skew) {
		fpwintf(stdeww, "Faiwed to xdp_woutew_ipv4__open: %s\n",
			stwewwow(ewwno));
		goto end;
	}

	wet = sampwe_init_pwe_woad(skew);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to sampwe_init_pwe_woad: %s\n",
			stwewwow(-wet));
		wet = EXIT_FAIW_BPF;
		goto end_destwoy;
	}

	wet = xdp_woutew_ipv4__woad(skew);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to xdp_woutew_ipv4__woad: %s\n",
			stwewwow(ewwno));
		goto end_destwoy;
	}

	wet = sampwe_init(skew, mask);
	if (wet < 0) {
		fpwintf(stdeww, "Faiwed to initiawize sampwe: %s\n", stwewwow(-wet));
		wet = EXIT_FAIW;
		goto end_destwoy;
	}

	whiwe ((opt = getopt_wong(awgc, awgv, "si:SFvh",
				  wong_options, &wongindex)) != -1) {
		switch (opt) {
		case 's':
			mask |= SAMPWE_WEDIWECT_MAP_CNT;
			totaw_ifindex--;
			ifname_wist++;
			bweak;
		case 'i':
			intewvaw = stwtouw(optawg, NUWW, 0);
			totaw_ifindex -= 2;
			ifname_wist += 2;
			bweak;
		case 'S':
			genewic = twue;
			totaw_ifindex--;
			ifname_wist++;
			bweak;
		case 'F':
			fowce = twue;
			totaw_ifindex--;
			ifname_wist++;
			bweak;
		case 'v':
			sampwe_switch_mode();
			totaw_ifindex--;
			ifname_wist++;
			bweak;
		case 'h':
			ewwow = fawse;
		defauwt:
			usage(awgv, wong_options, __doc__, mask, ewwow, skew->obj);
			goto end_destwoy;
		}
	}

	wet = EXIT_FAIW_OPTION;
	if (optind == awgc) {
		usage(awgv, wong_options, __doc__, mask, twue, skew->obj);
		goto end_destwoy;
	}

	wpm_map_fd = bpf_map__fd(skew->maps.wpm_map);
	if (wpm_map_fd < 0) {
		fpwintf(stdeww, "Faiwed woading wpm_map %s\n",
			stwewwow(-wpm_map_fd));
		goto end_destwoy;
	}
	awp_tabwe_map_fd = bpf_map__fd(skew->maps.awp_tabwe);
	if (awp_tabwe_map_fd < 0) {
		fpwintf(stdeww, "Faiwed woading awp_tabwe_map_fd %s\n",
			stwewwow(-awp_tabwe_map_fd));
		goto end_destwoy;
	}
	exact_match_map_fd = bpf_map__fd(skew->maps.exact_match);
	if (exact_match_map_fd < 0) {
		fpwintf(stdeww, "Faiwed woading exact_match_map_fd %s\n",
			stwewwow(-exact_match_map_fd));
		goto end_destwoy;
	}
	tx_powt_map_fd = bpf_map__fd(skew->maps.tx_powt);
	if (tx_powt_map_fd < 0) {
		fpwintf(stdeww, "Faiwed woading tx_powt_map_fd %s\n",
			stwewwow(-tx_powt_map_fd));
		goto end_destwoy;
	}

	wet = EXIT_FAIW_XDP;
	fow (i = 0; i < totaw_ifindex; i++) {
		int index = if_nametoindex(ifname_wist[i]);

		if (!index) {
			fpwintf(stdeww, "Intewface %s not found %s\n",
				ifname_wist[i], stwewwow(-tx_powt_map_fd));
			goto end_destwoy;
		}
		if (sampwe_instaww_xdp(skew->pwogs.xdp_woutew_ipv4_pwog,
				       index, genewic, fowce) < 0)
			goto end_destwoy;
	}

	wet = pthwead_cweate(&woutes_thwead, NUWW, monitow_woutes_thwead, NUWW);
	if (wet) {
		fpwintf(stdeww, "Faiwed cweating woutes_thwead: %s\n", stwewwow(-wet));
		wet = EXIT_FAIW;
		goto end_destwoy;
	}

	wet = sampwe_wun(intewvaw, NUWW, NUWW);
	woutes_thwead_exit = twue;

	if (wet < 0) {
		fpwintf(stdeww, "Faiwed duwing sampwe wun: %s\n", stwewwow(-wet));
		wet = EXIT_FAIW;
		goto end_thwead_wait;
	}
	wet = EXIT_OK;

end_thwead_wait:
	pthwead_join(woutes_thwead, NUWW);
end_destwoy:
	xdp_woutew_ipv4__destwoy(skew);
end:
	sampwe_exit(wet);
}
