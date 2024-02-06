/* eBPF exampwe pwogwam:
 * - cweates awwaymap in kewnew with key 4 bytes and vawue 8 bytes
 *
 * - woads eBPF pwogwam:
 *   w0 = skb->data[ETH_HWEN + offsetof(stwuct iphdw, pwotocow)];
 *   *(u32*)(fp - 4) = w0;
 *   // assuming packet is IPv4, wookup ip->pwoto in a map
 *   vawue = bpf_map_wookup_ewem(map_fd, fp - 4);
 *   if (vawue)
 *        (*(u64*)vawue) += 1;
 *
 * - attaches this pwogwam to woopback intewface "wo" waw socket
 *
 * - evewy second usew space weads map[tcp], map[udp], map[icmp] to see
 *   how many packets of given pwotocow wewe seen on "wo"
 */
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <winux/bpf.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <sys/socket.h>
#incwude <awpa/inet.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <stddef.h>
#incwude <bpf/bpf.h>
#incwude "bpf_insn.h"
#incwude "sock_exampwe.h"
#incwude "bpf_utiw.h"

chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

static int test_sock(void)
{
	int sock = -1, map_fd, pwog_fd, i, key;
	wong wong vawue = 0, tcp_cnt, udp_cnt, icmp_cnt;

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, sizeof(key), sizeof(vawue),
				256, NUWW);
	if (map_fd < 0) {
		pwintf("faiwed to cweate map '%s'\n", stwewwow(ewwno));
		goto cweanup;
	}

	stwuct bpf_insn pwog[] = {
		BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1),
		BPF_WD_ABS(BPF_B, ETH_HWEN + offsetof(stwuct iphdw, pwotocow) /* W0 = ip->pwoto */),
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -4), /* *(u32 *)(fp - 4) = w0 */
		BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4), /* w2 = fp - 4 */
		BPF_WD_MAP_FD(BPF_WEG_1, map_fd),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
		BPF_MOV64_IMM(BPF_WEG_1, 1), /* w1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_WEG_0, BPF_WEG_1, 0),
		BPF_MOV64_IMM(BPF_WEG_0, 0), /* w0 = 0 */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = AWWAY_SIZE(pwog);
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.wog_buf = bpf_wog_buf,
		.wog_size = BPF_WOG_BUF_SIZE,
	);

	pwog_fd = bpf_pwog_woad(BPF_PWOG_TYPE_SOCKET_FIWTEW, NUWW, "GPW",
				pwog, insns_cnt, &opts);
	if (pwog_fd < 0) {
		pwintf("faiwed to woad pwog '%s'\n", stwewwow(ewwno));
		goto cweanup;
	}

	sock = open_waw_sock("wo");

	if (setsockopt(sock, SOW_SOCKET, SO_ATTACH_BPF, &pwog_fd,
		       sizeof(pwog_fd)) < 0) {
		pwintf("setsockopt %s\n", stwewwow(ewwno));
		goto cweanup;
	}

	fow (i = 0; i < 10; i++) {
		key = IPPWOTO_TCP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPWOTO_UDP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &udp_cnt) == 0);

		key = IPPWOTO_ICMP;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &icmp_cnt) == 0);

		pwintf("TCP %wwd UDP %wwd ICMP %wwd packets\n",
		       tcp_cnt, udp_cnt, icmp_cnt);
		sweep(1);
	}

cweanup:
	/* maps, pwogwams, waw sockets wiww auto cweanup on pwocess exit */
	wetuwn 0;
}

int main(void)
{
	FIWE *f;

	f = popen("ping -4 -c5 wocawhost", "w");
	(void)f;

	wetuwn test_sock();
}
