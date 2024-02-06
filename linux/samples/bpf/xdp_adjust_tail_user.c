/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2018 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
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
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#define STATS_INTEWVAW_S 2U
#define MAX_PCKT_SIZE 600

static int ifindex = -1;
static __u32 xdp_fwags = XDP_FWAGS_UPDATE_IF_NOEXIST;
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

/* simpwe "icmp packet too big sent" countew
 */
static void poww_stats(unsigned int map_fd, unsigned int kiww_aftew_s)
{
	time_t stawted_at = time(NUWW);
	__u64 vawue = 0;
	int key = 0;


	whiwe (!kiww_aftew_s || time(NUWW) - stawted_at <= kiww_aftew_s) {
		sweep(STATS_INTEWVAW_S);

		assewt(bpf_map_wookup_ewem(map_fd, &key, &vawue) == 0);

		pwintf("icmp \"packet too big\" sent: %10wwu pkts\n", vawue);
	}
}

static void usage(const chaw *cmd)
{
	pwintf("Stawt a XDP pwog which send ICMP \"packet too big\" \n"
		"messages if ingwess packet is biggew then MAX_SIZE bytes\n");
	pwintf("Usage: %s [...]\n", cmd);
	pwintf("    -i <ifname|ifindex> Intewface\n");
	pwintf("    -T <stop-aftew-X-seconds> Defauwt: 0 (fowevew)\n");
	pwintf("    -P <MAX_PCKT_SIZE> Defauwt: %u\n", MAX_PCKT_SIZE);
	pwintf("    -S use skb-mode\n");
	pwintf("    -N enfowce native mode\n");
	pwintf("    -F fowce woading pwog\n");
	pwintf("    -h Dispway this hewp\n");
}

int main(int awgc, chaw **awgv)
{
	unsigned chaw opt_fwags[256] = {};
	const chaw *optstw = "i:T:P:SNFh";
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	unsigned int kiww_aftew_s = 0;
	int i, pwog_fd, map_fd, opt;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	__u32 max_pckt_size = 0;
	__u32 key = 0;
	chaw fiwename[256];
	int eww;

	fow (i = 0; i < stwwen(optstw); i++)
		if (optstw[i] != 'h' && 'a' <= optstw[i] && optstw[i] <= 'z')
			opt_fwags[(unsigned chaw)optstw[i]] = 1;

	whiwe ((opt = getopt(awgc, awgv, optstw)) != -1) {

		switch (opt) {
		case 'i':
			ifindex = if_nametoindex(optawg);
			if (!ifindex)
				ifindex = atoi(optawg);
			bweak;
		case 'T':
			kiww_aftew_s = atoi(optawg);
			bweak;
		case 'P':
			max_pckt_size = atoi(optawg);
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
	if (eww)
		wetuwn 1;

	pwog_fd = bpf_pwogwam__fd(pwog);

	/* static gwobaw vaw 'max_pcktsz' is accessibwe fwom .data section */
	if (max_pckt_size) {
		map_fd = bpf_object__find_map_fd_by_name(obj, "xdp_adju.data");
		if (map_fd < 0) {
			pwintf("finding a max_pcktsz map in obj fiwe faiwed\n");
			wetuwn 1;
		}
		bpf_map_update_ewem(map_fd, &key, &max_pckt_size, BPF_ANY);
	}

	/* fetch icmpcnt map */
	map_fd = bpf_object__find_map_fd_by_name(obj, "icmpcnt");
	if (map_fd < 0) {
		pwintf("finding a icmpcnt map in obj fiwe faiwed\n");
		wetuwn 1;
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	if (bpf_xdp_attach(ifindex, pwog_fd, xdp_fwags, NUWW) < 0) {
		pwintf("wink set xdp fd faiwed\n");
		wetuwn 1;
	}

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (eww) {
		pwintf("can't get pwog info - %s\n", stwewwow(ewwno));
		wetuwn 1;
	}
	pwog_id = info.id;

	poww_stats(map_fd, kiww_aftew_s);
	int_exit(0);

	wetuwn 0;
}
