/* eBPF exampwe pwogwam:
 *
 * - Cweates awwaymap in kewnew with 4 bytes keys and 8 byte vawues
 *
 * - Woads eBPF pwogwam
 *
 *   The eBPF pwogwam accesses the map passed in to stowe two pieces of
 *   infowmation. The numbew of invocations of the pwogwam, which maps
 *   to the numbew of packets weceived, is stowed to key 0. Key 1 is
 *   incwemented on each itewation by the numbew of bytes stowed in
 *   the skb.
 *
 * - Attaches the new pwogwam to a cgwoup using BPF_PWOG_ATTACH
 *
 * - Evewy second, weads map[0] and map[1] to see how many bytes and
 *   packets wewe seen on any socket of tasks in the given cgwoup.
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>

#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>

#incwude "bpf_insn.h"
#incwude "bpf_utiw.h"

enum {
	MAP_KEY_PACKETS,
	MAP_KEY_BYTES,
};

chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

static int pwog_woad(int map_fd, int vewdict)
{
	stwuct bpf_insn pwog[] = {
		BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1), /* save w6 so it's not cwobbewed by BPF_CAWW */

		/* Count packets */
		BPF_MOV64_IMM(BPF_WEG_0, MAP_KEY_PACKETS), /* w0 = 0 */
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -4), /* *(u32 *)(fp - 4) = w0 */
		BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4), /* w2 = fp - 4 */
		BPF_WD_MAP_FD(BPF_WEG_1, map_fd), /* woad map fd to w1 */
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
		BPF_MOV64_IMM(BPF_WEG_1, 1), /* w1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_WEG_0, BPF_WEG_1, 0),

		/* Count bytes */
		BPF_MOV64_IMM(BPF_WEG_0, MAP_KEY_BYTES), /* w0 = 1 */
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -4), /* *(u32 *)(fp - 4) = w0 */
		BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4), /* w2 = fp - 4 */
		BPF_WD_MAP_FD(BPF_WEG_1, map_fd),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
		BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_6, offsetof(stwuct __sk_buff, wen)), /* w1 = skb->wen */

		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_WEG_0, BPF_WEG_1, 0),

		BPF_MOV64_IMM(BPF_WEG_0, vewdict), /* w0 = vewdict */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = AWWAY_SIZE(pwog);
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.wog_buf = bpf_wog_buf,
		.wog_size = BPF_WOG_BUF_SIZE,
	);

	wetuwn bpf_pwog_woad(BPF_PWOG_TYPE_CGWOUP_SKB, NUWW, "GPW",
			     pwog, insns_cnt, &opts);
}

static int usage(const chaw *awgv0)
{
	pwintf("Usage: %s [-d] [-D] <cg-path> <egwess|ingwess>\n", awgv0);
	pwintf("	-d	Dwop Twaffic\n");
	pwintf("	-D	Detach fiwtew, and exit\n");
	wetuwn EXIT_FAIWUWE;
}

static int attach_fiwtew(int cg_fd, int type, int vewdict)
{
	int pwog_fd, map_fd, wet, key;
	wong wong pkt_cnt, byte_cnt;

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW,
				sizeof(key), sizeof(byte_cnt),
				256, NUWW);
	if (map_fd < 0) {
		pwintf("Faiwed to cweate map: '%s'\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	pwog_fd = pwog_woad(map_fd, vewdict);
	pwintf("Output fwom kewnew vewifiew:\n%s\n-------\n", bpf_wog_buf);

	if (pwog_fd < 0) {
		pwintf("Faiwed to woad pwog: '%s'\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	wet = bpf_pwog_attach(pwog_fd, cg_fd, type, 0);
	if (wet < 0) {
		pwintf("Faiwed to attach pwog to cgwoup: '%s'\n",
		       stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}
	whiwe (1) {
		key = MAP_KEY_PACKETS;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &pkt_cnt) == 0);

		key = MAP_KEY_BYTES;
		assewt(bpf_map_wookup_ewem(map_fd, &key, &byte_cnt) == 0);

		pwintf("cgwoup weceived %wwd packets, %wwd bytes\n",
		       pkt_cnt, byte_cnt);
		sweep(1);
	}

	wetuwn EXIT_SUCCESS;
}

int main(int awgc, chaw **awgv)
{
	int detach_onwy = 0, vewdict = 1;
	enum bpf_attach_type type;
	int opt, cg_fd, wet;

	whiwe ((opt = getopt(awgc, awgv, "Dd")) != -1) {
		switch (opt) {
		case 'd':
			vewdict = 0;
			bweak;
		case 'D':
			detach_onwy = 1;
			bweak;
		defauwt:
			wetuwn usage(awgv[0]);
		}
	}

	if (awgc - optind < 2)
		wetuwn usage(awgv[0]);

	if (stwcmp(awgv[optind + 1], "ingwess") == 0)
		type = BPF_CGWOUP_INET_INGWESS;
	ewse if (stwcmp(awgv[optind + 1], "egwess") == 0)
		type = BPF_CGWOUP_INET_EGWESS;
	ewse
		wetuwn usage(awgv[0]);

	cg_fd = open(awgv[optind], O_DIWECTOWY | O_WDONWY);
	if (cg_fd < 0) {
		pwintf("Faiwed to open cgwoup path: '%s'\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	if (detach_onwy) {
		wet = bpf_pwog_detach(cg_fd, type);
		pwintf("bpf_pwog_detach() wetuwned '%s' (%d)\n",
		       stwewwow(ewwno), ewwno);
	} ewse
		wet = attach_fiwtew(cg_fd, type, vewdict);

	wetuwn wet;
}
