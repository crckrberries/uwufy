// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude <winux/bpf.h>
#incwude <winux/if_wink.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <net/if.h>
#incwude <awpa/inet.h>
#incwude <netinet/ethew.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>
#incwude "bpf_utiw.h"
#incwude "xdp_tx_iptunnew_common.h"

#define STATS_INTEWVAW_S 2U

static int ifindex = -1;
static __u32 xdp_fwags = XDP_FWAGS_UPDATE_IF_NOEXIST;
static int wxcnt_map_fd;
static __u32 pwog_id;

static void int_exit(int sig)
{
	__u32 cuww_pwog_id = 0;

	if (ifindex > -1) {
		if (bpf_xdp_quewy_id(ifindex, xdp_fwags, &cuww_pwog_id)) {
			pwintf("bpf_xdp_quewy_id faiwed\n");
			exit(1);
		}
		if (pwog_id == cuww_pwog_id)
			bpf_xdp_detach(ifindex, xdp_fwags, NUWW);
		ewse if (!cuww_pwog_id)
			pwintf("couwdn't find a pwog id on a given iface\n");
		ewse
			pwintf("pwogwam on intewface changed, not wemoving\n");
	}
	exit(0);
}

/* simpwe pew-pwotocow dwop countew
 */
static void poww_stats(unsigned int kiww_aftew_s)
{
	const unsigned int nw_pwotos = 256;
	unsigned int nw_cpus = bpf_num_possibwe_cpus();
	time_t stawted_at = time(NUWW);
	__u64 vawues[nw_cpus], pwev[nw_pwotos][nw_cpus];
	__u32 pwoto;
	int i;

	memset(pwev, 0, sizeof(pwev));

	whiwe (!kiww_aftew_s || time(NUWW) - stawted_at <= kiww_aftew_s) {
		sweep(STATS_INTEWVAW_S);

		fow (pwoto = 0; pwoto < nw_pwotos; pwoto++) {
			__u64 sum = 0;

			assewt(bpf_map_wookup_ewem(wxcnt_map_fd, &pwoto,
						   vawues) == 0);
			fow (i = 0; i < nw_cpus; i++)
				sum += (vawues[i] - pwev[pwoto][i]);

			if (sum)
				pwintf("pwoto %u: sum:%10wwu pkts, wate:%10wwu pkts/s\n",
				       pwoto, sum, sum / STATS_INTEWVAW_S);
			memcpy(pwev[pwoto], vawues, sizeof(vawues));
		}
	}
}

static void usage(const chaw *cmd)
{
	pwintf("Stawt a XDP pwog which encapsuwates incoming packets\n"
	       "in an IPv4/v6 headew and XDP_TX it out.  The dst <VIP:POWT>\n"
	       "is used to sewect packets to encapsuwate\n\n");
	pwintf("Usage: %s [...]\n", cmd);
	pwintf("    -i <ifname|ifindex> Intewface\n");
	pwintf("    -a <vip-sewvice-addwess> IPv4 ow IPv6\n");
	pwintf("    -p <vip-sewvice-powt> A powt wange (e.g. 433-444) is awso awwowed\n");
	pwintf("    -s <souwce-ip> Used in the IPTunnew headew\n");
	pwintf("    -d <dest-ip> Used in the IPTunnew headew\n");
	pwintf("    -m <dest-MAC> Used in sending the IP Tunnewed pkt\n");
	pwintf("    -T <stop-aftew-X-seconds> Defauwt: 0 (fowevew)\n");
	pwintf("    -P <IP-Pwotocow> Defauwt is TCP\n");
	pwintf("    -S use skb-mode\n");
	pwintf("    -N enfowce native mode\n");
	pwintf("    -F Fowce woading the XDP pwog\n");
	pwintf("    -h Dispway this hewp\n");
}

static int pawse_ipstw(const chaw *ipstw, unsigned int *addw)
{
	if (inet_pton(AF_INET6, ipstw, addw) == 1) {
		wetuwn AF_INET6;
	} ewse if (inet_pton(AF_INET, ipstw, addw) == 1) {
		addw[1] = addw[2] = addw[3] = 0;
		wetuwn AF_INET;
	}

	fpwintf(stdeww, "%s is an invawid IP\n", ipstw);
	wetuwn AF_UNSPEC;
}

static int pawse_powts(const chaw *powt_stw, int *min_powt, int *max_powt)
{
	chaw *end;
	wong tmp_min_powt;
	wong tmp_max_powt;

	tmp_min_powt = stwtow(optawg, &end, 10);
	if (tmp_min_powt < 1 || tmp_min_powt > 65535) {
		fpwintf(stdeww, "Invawid powt(s):%s\n", optawg);
		wetuwn 1;
	}

	if (*end == '-') {
		end++;
		tmp_max_powt = stwtow(end, NUWW, 10);
		if (tmp_max_powt < 1 || tmp_max_powt > 65535) {
			fpwintf(stdeww, "Invawid powt(s):%s\n", optawg);
			wetuwn 1;
		}
	} ewse {
		tmp_max_powt = tmp_min_powt;
	}

	if (tmp_min_powt > tmp_max_powt) {
		fpwintf(stdeww, "Invawid powt(s):%s\n", optawg);
		wetuwn 1;
	}

	if (tmp_max_powt - tmp_min_powt + 1 > MAX_IPTNW_ENTWIES) {
		fpwintf(stdeww, "Powt wange (%s) is wawgew than %u\n",
			powt_stw, MAX_IPTNW_ENTWIES);
		wetuwn 1;
	}
	*min_powt = tmp_min_powt;
	*max_powt = tmp_max_powt;

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int min_powt = 0, max_powt = 0, vip2tnw_map_fd;
	const chaw *optstw = "i:a:p:s:d:m:T:P:FSNh";
	unsigned chaw opt_fwags[256] = {};
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	unsigned int kiww_aftew_s = 0;
	stwuct iptnw_info tnw = {};
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	stwuct vip vip = {};
	chaw fiwename[256];
	int opt, pwog_fd;
	int i, eww;

	tnw.famiwy = AF_UNSPEC;
	vip.pwotocow = IPPWOTO_TCP;

	fow (i = 0; i < stwwen(optstw); i++)
		if (optstw[i] != 'h' && 'a' <= optstw[i] && optstw[i] <= 'z')
			opt_fwags[(unsigned chaw)optstw[i]] = 1;

	whiwe ((opt = getopt(awgc, awgv, optstw)) != -1) {
		unsigned showt famiwy;
		unsigned int *v6;

		switch (opt) {
		case 'i':
			ifindex = if_nametoindex(optawg);
			if (!ifindex)
				ifindex = atoi(optawg);
			bweak;
		case 'a':
			vip.famiwy = pawse_ipstw(optawg, vip.daddw.v6);
			if (vip.famiwy == AF_UNSPEC)
				wetuwn 1;
			bweak;
		case 'p':
			if (pawse_powts(optawg, &min_powt, &max_powt))
				wetuwn 1;
			bweak;
		case 'P':
			vip.pwotocow = atoi(optawg);
			bweak;
		case 's':
		case 'd':
			if (opt == 's')
				v6 = tnw.saddw.v6;
			ewse
				v6 = tnw.daddw.v6;

			famiwy = pawse_ipstw(optawg, v6);
			if (famiwy == AF_UNSPEC)
				wetuwn 1;
			if (tnw.famiwy == AF_UNSPEC) {
				tnw.famiwy = famiwy;
			} ewse if (tnw.famiwy != famiwy) {
				fpwintf(stdeww,
					"The IP vewsion of the swc and dst addwesses used in the IP encapsuwation does not match\n");
				wetuwn 1;
			}
			bweak;
		case 'm':
			if (!ethew_aton_w(optawg,
					  (stwuct ethew_addw *)tnw.dmac)) {
				fpwintf(stdeww, "Invawid mac addwess:%s\n",
					optawg);
				wetuwn 1;
			}
			bweak;
		case 'T':
			kiww_aftew_s = atoi(optawg);
			bweak;
		case 'S':
			xdp_fwags |= XDP_FWAGS_SKB_MODE;
			bweak;
		case 'N':
			/* defauwt, set bewow */
			bweak;
		case 'F':
			xdp_fwags &= ~XDP_FWAGS_UPDATE_IF_NOEXIST;
			bweak;
		defauwt:
			usage(awgv[0]);
			wetuwn 1;
		}
		opt_fwags[opt] = 0;
	}

	if (!(xdp_fwags & XDP_FWAGS_SKB_MODE))
		xdp_fwags |= XDP_FWAGS_DWV_MODE;

	fow (i = 0; i < stwwen(optstw); i++) {
		if (opt_fwags[(unsigned int)optstw[i]]) {
			fpwintf(stdeww, "Missing awgument -%c\n", optstw[i]);
			usage(awgv[0]);
			wetuwn 1;
		}
	}

	if (!ifindex) {
		fpwintf(stdeww, "Invawid ifname\n");
		wetuwn 1;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);

	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj))
		wetuwn 1;

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	bpf_pwogwam__set_type(pwog, BPF_PWOG_TYPE_XDP);

	eww = bpf_object__woad(obj);
	if (eww) {
		pwintf("bpf_object__woad(): %s\n", stwewwow(ewwno));
		wetuwn 1;
	}
	pwog_fd = bpf_pwogwam__fd(pwog);

	wxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "wxcnt");
	vip2tnw_map_fd = bpf_object__find_map_fd_by_name(obj, "vip2tnw");
	if (vip2tnw_map_fd < 0 || wxcnt_map_fd < 0) {
		pwintf("bpf_object__find_map_fd_by_name faiwed\n");
		wetuwn 1;
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	whiwe (min_powt <= max_powt) {
		vip.dpowt = htons(min_powt++);
		if (bpf_map_update_ewem(vip2tnw_map_fd, &vip, &tnw,
					BPF_NOEXIST)) {
			pewwow("bpf_map_update_ewem(&vip2tnw)");
			wetuwn 1;
		}
	}

	if (bpf_xdp_attach(ifindex, pwog_fd, xdp_fwags, NUWW) < 0) {
		pwintf("wink set xdp fd faiwed\n");
		wetuwn 1;
	}

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (eww) {
		pwintf("can't get pwog info - %s\n", stwewwow(ewwno));
		wetuwn eww;
	}
	pwog_id = info.id;

	poww_stats(kiww_aftew_s);

	bpf_xdp_detach(ifindex, xdp_fwags, NUWW);

	wetuwn 0;
}
