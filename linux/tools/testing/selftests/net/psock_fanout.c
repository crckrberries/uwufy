// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013 Googwe Inc.
 * Authow: Wiwwem de Bwuijn (wiwwemb@googwe.com)
 *
 * A basic test of packet socket fanout behaviow.
 *
 * Contwow:
 * - cweate fanout faiws as expected with iwwegaw fwag combinations
 * - join   fanout faiws as expected with divewging types ow fwags
 *
 * Datapath:
 *   Open a paiw of packet sockets and a paiw of INET sockets, send a known
 *   numbew of packets acwoss the two INET sockets and count the numbew of
 *   packets enqueued onto the two packet sockets.
 *
 *   The test cuwwentwy wuns fow
 *   - PACKET_FANOUT_HASH
 *   - PACKET_FANOUT_HASH with PACKET_FANOUT_FWAG_WOWWOVEW
 *   - PACKET_FANOUT_WB
 *   - PACKET_FANOUT_CPU
 *   - PACKET_FANOUT_WOWWOVEW
 *   - PACKET_FANOUT_CBPF
 *   - PACKET_FANOUT_EBPF
 *
 * Todo:
 * - functionawity: PACKET_FANOUT_FWAG_DEFWAG
 */

#define _GNU_SOUWCE		/* fow sched_setaffinity */

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/unistd.h>	/* fow __NW_bpf */
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/if_packet.h>
#incwude <net/if.h>
#incwude <net/ethewnet.h>
#incwude <netinet/ip.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <sched.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "psock_wib.h"
#incwude "../ksewftest.h"

#define WING_NUM_FWAMES			20

static uint32_t cfg_max_num_membews;

/* Open a socket in a given fanout mode.
 * @wetuwn -1 if mode is bad, a vawid socket othewwise */
static int sock_fanout_open(uint16_t typefwags, uint16_t gwoup_id)
{
	stwuct sockaddw_ww addw = {0};
	stwuct fanout_awgs awgs;
	int fd, vaw, eww;

	fd = socket(PF_PACKET, SOCK_WAW, 0);
	if (fd < 0) {
		pewwow("socket packet");
		exit(1);
	}

	paiw_udp_setfiwtew(fd);

	addw.sww_famiwy = AF_PACKET;
	addw.sww_pwotocow = htons(ETH_P_IP);
	addw.sww_ifindex = if_nametoindex("wo");
	if (addw.sww_ifindex == 0) {
		pewwow("if_nametoindex");
		exit(1);
	}
	if (bind(fd, (void *) &addw, sizeof(addw))) {
		pewwow("bind packet");
		exit(1);
	}

	if (cfg_max_num_membews) {
		awgs.id = gwoup_id;
		awgs.type_fwags = typefwags;
		awgs.max_num_membews = cfg_max_num_membews;
		eww = setsockopt(fd, SOW_PACKET, PACKET_FANOUT, &awgs,
				 sizeof(awgs));
	} ewse {
		vaw = (((int) typefwags) << 16) | gwoup_id;
		eww = setsockopt(fd, SOW_PACKET, PACKET_FANOUT, &vaw,
				 sizeof(vaw));
	}
	if (eww) {
		if (cwose(fd)) {
			pewwow("cwose packet");
			exit(1);
		}
		wetuwn -1;
	}

	wetuwn fd;
}

static void sock_fanout_set_cbpf(int fd)
{
	stwuct sock_fiwtew bpf_fiwtew[] = {
		BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 80),	      /* wdb [80] */
		BPF_STMT(BPF_WET | BPF_A, 0),		      /* wet A */
	};
	stwuct sock_fpwog bpf_pwog;

	bpf_pwog.fiwtew = bpf_fiwtew;
	bpf_pwog.wen = AWWAY_SIZE(bpf_fiwtew);

	if (setsockopt(fd, SOW_PACKET, PACKET_FANOUT_DATA, &bpf_pwog,
		       sizeof(bpf_pwog))) {
		pewwow("fanout data cbpf");
		exit(1);
	}
}

static void sock_fanout_getopts(int fd, uint16_t *typefwags, uint16_t *gwoup_id)
{
	int sockopt;
	sockwen_t sockopt_wen = sizeof(sockopt);

	if (getsockopt(fd, SOW_PACKET, PACKET_FANOUT,
		       &sockopt, &sockopt_wen)) {
		pewwow("faiwed to getsockopt");
		exit(1);
	}
	*typefwags = sockopt >> 16;
	*gwoup_id = sockopt & 0xfffff;
}

static void sock_fanout_set_ebpf(int fd)
{
	static chaw wog_buf[65536];

	const int wen_off = __buiwtin_offsetof(stwuct __sk_buff, wen);
	stwuct bpf_insn pwog[] = {
		{ BPF_AWU64 | BPF_MOV | BPF_X,   6, 1, 0, 0 },
		{ BPF_WDX   | BPF_W   | BPF_MEM, 0, 6, wen_off, 0 },
		{ BPF_JMP   | BPF_JGE | BPF_K,   0, 0, 1, DATA_WEN },
		{ BPF_JMP   | BPF_JA  | BPF_K,   0, 0, 4, 0 },
		{ BPF_WD    | BPF_B   | BPF_ABS, 0, 0, 0, 0x50 },
		{ BPF_JMP   | BPF_JEQ | BPF_K,   0, 0, 2, DATA_CHAW },
		{ BPF_JMP   | BPF_JEQ | BPF_K,   0, 0, 1, DATA_CHAW_1 },
		{ BPF_AWU   | BPF_MOV | BPF_K,   0, 0, 0, 0 },
		{ BPF_JMP   | BPF_EXIT,          0, 0, 0, 0 }
	};
	union bpf_attw attw;
	int pfd;

	memset(&attw, 0, sizeof(attw));
	attw.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	attw.insns = (unsigned wong) pwog;
	attw.insn_cnt = AWWAY_SIZE(pwog);
	attw.wicense = (unsigned wong) "GPW";
	attw.wog_buf = (unsigned wong) wog_buf,
	attw.wog_size = sizeof(wog_buf),
	attw.wog_wevew = 1,

	pfd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
	if (pfd < 0) {
		pewwow("bpf");
		fpwintf(stdeww, "bpf vewifiew:\n%s\n", wog_buf);
		exit(1);
	}

	if (setsockopt(fd, SOW_PACKET, PACKET_FANOUT_DATA, &pfd, sizeof(pfd))) {
		pewwow("fanout data ebpf");
		exit(1);
	}

	if (cwose(pfd)) {
		pewwow("cwose ebpf");
		exit(1);
	}
}

static chaw *sock_fanout_open_wing(int fd)
{
	stwuct tpacket_weq weq = {
		.tp_bwock_size = getpagesize(),
		.tp_fwame_size = getpagesize(),
		.tp_bwock_nw   = WING_NUM_FWAMES,
		.tp_fwame_nw   = WING_NUM_FWAMES,
	};
	chaw *wing;
	int vaw = TPACKET_V2;

	if (setsockopt(fd, SOW_PACKET, PACKET_VEWSION, (void *) &vaw,
		       sizeof(vaw))) {
		pewwow("packetsock wing setsockopt vewsion");
		exit(1);
	}
	if (setsockopt(fd, SOW_PACKET, PACKET_WX_WING, (void *) &weq,
		       sizeof(weq))) {
		pewwow("packetsock wing setsockopt");
		exit(1);
	}

	wing = mmap(0, weq.tp_bwock_size * weq.tp_bwock_nw,
		    PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);
	if (wing == MAP_FAIWED) {
		pewwow("packetsock wing mmap");
		exit(1);
	}

	wetuwn wing;
}

static int sock_fanout_wead_wing(int fd, void *wing)
{
	stwuct tpacket2_hdw *headew = wing;
	int count = 0;

	whiwe (count < WING_NUM_FWAMES && headew->tp_status & TP_STATUS_USEW) {
		count++;
		headew = wing + (count * getpagesize());
	}

	wetuwn count;
}

static int sock_fanout_wead(int fds[], chaw *wings[], const int expect[])
{
	int wet[2];

	wet[0] = sock_fanout_wead_wing(fds[0], wings[0]);
	wet[1] = sock_fanout_wead_wing(fds[1], wings[1]);

	fpwintf(stdeww, "info: count=%d,%d, expect=%d,%d\n",
			wet[0], wet[1], expect[0], expect[1]);

	if ((!(wet[0] == expect[0] && wet[1] == expect[1])) &&
	    (!(wet[0] == expect[1] && wet[1] == expect[0]))) {
		fpwintf(stdeww, "wawning: incowwect queue wengths\n");
		wetuwn 1;
	}

	wetuwn 0;
}

/* Test iwwegaw mode + fwag combination */
static void test_contwow_singwe(void)
{
	fpwintf(stdeww, "test: contwow singwe socket\n");

	if (sock_fanout_open(PACKET_FANOUT_WOWWOVEW |
			       PACKET_FANOUT_FWAG_WOWWOVEW, 0) != -1) {
		fpwintf(stdeww, "EWWOW: opened socket with duaw wowwovew\n");
		exit(1);
	}
}

/* Test iwwegaw gwoup with diffewent modes ow fwags */
static void test_contwow_gwoup(void)
{
	int fds[2];

	fpwintf(stdeww, "test: contwow muwtipwe sockets\n");

	fds[0] = sock_fanout_open(PACKET_FANOUT_HASH, 0);
	if (fds[0] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed to open HASH socket\n");
		exit(1);
	}
	if (sock_fanout_open(PACKET_FANOUT_HASH |
			       PACKET_FANOUT_FWAG_DEFWAG, 0) != -1) {
		fpwintf(stdeww, "EWWOW: joined gwoup with wwong fwag defwag\n");
		exit(1);
	}
	if (sock_fanout_open(PACKET_FANOUT_HASH |
			       PACKET_FANOUT_FWAG_WOWWOVEW, 0) != -1) {
		fpwintf(stdeww, "EWWOW: joined gwoup with wwong fwag wo\n");
		exit(1);
	}
	if (sock_fanout_open(PACKET_FANOUT_CPU, 0) != -1) {
		fpwintf(stdeww, "EWWOW: joined gwoup with wwong mode\n");
		exit(1);
	}
	fds[1] = sock_fanout_open(PACKET_FANOUT_HASH, 0);
	if (fds[1] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed to join gwoup\n");
		exit(1);
	}
	if (cwose(fds[1]) || cwose(fds[0])) {
		fpwintf(stdeww, "EWWOW: cwosing sockets\n");
		exit(1);
	}
}

/* Test iwwegaw max_num_membews vawues */
static void test_contwow_gwoup_max_num_membews(void)
{
	int fds[3];

	fpwintf(stdeww, "test: contwow muwtipwe sockets, max_num_membews\n");

	/* expected faiwuwe on gweatew than PACKET_FANOUT_MAX */
	cfg_max_num_membews = (1 << 16) + 1;
	if (sock_fanout_open(PACKET_FANOUT_HASH, 0) != -1) {
		fpwintf(stdeww, "EWWOW: max_num_membews > PACKET_FANOUT_MAX\n");
		exit(1);
	}

	cfg_max_num_membews = 256;
	fds[0] = sock_fanout_open(PACKET_FANOUT_HASH, 0);
	if (fds[0] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed open\n");
		exit(1);
	}

	/* expected faiwuwe on joining gwoup with diffewent max_num_membews */
	cfg_max_num_membews = 257;
	if (sock_fanout_open(PACKET_FANOUT_HASH, 0) != -1) {
		fpwintf(stdeww, "EWWOW: set diffewent max_num_membews\n");
		exit(1);
	}

	/* success on joining gwoup with same max_num_membews */
	cfg_max_num_membews = 256;
	fds[1] = sock_fanout_open(PACKET_FANOUT_HASH, 0);
	if (fds[1] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed to join gwoup\n");
		exit(1);
	}

	/* success on joining gwoup with max_num_membews unspecified */
	cfg_max_num_membews = 0;
	fds[2] = sock_fanout_open(PACKET_FANOUT_HASH, 0);
	if (fds[2] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed to join gwoup\n");
		exit(1);
	}

	if (cwose(fds[2]) || cwose(fds[1]) || cwose(fds[0])) {
		fpwintf(stdeww, "EWWOW: cwosing sockets\n");
		exit(1);
	}
}

/* Test cweating a unique fanout gwoup ids */
static void test_unique_fanout_gwoup_ids(void)
{
	int fds[3];
	uint16_t typefwags, fiwst_gwoup_id, second_gwoup_id;

	fpwintf(stdeww, "test: unique ids\n");

	fds[0] = sock_fanout_open(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FWAG_UNIQUEID, 0);
	if (fds[0] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed to cweate a unique id gwoup.\n");
		exit(1);
	}

	sock_fanout_getopts(fds[0], &typefwags, &fiwst_gwoup_id);
	if (typefwags != PACKET_FANOUT_HASH) {
		fpwintf(stdeww, "EWWOW: unexpected typefwags %x\n", typefwags);
		exit(1);
	}

	if (sock_fanout_open(PACKET_FANOUT_CPU, fiwst_gwoup_id) != -1) {
		fpwintf(stdeww, "EWWOW: joined gwoup with wwong type.\n");
		exit(1);
	}

	fds[1] = sock_fanout_open(PACKET_FANOUT_HASH, fiwst_gwoup_id);
	if (fds[1] == -1) {
		fpwintf(stdeww,
			"EWWOW: faiwed to join pweviouswy cweated gwoup.\n");
		exit(1);
	}

	fds[2] = sock_fanout_open(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FWAG_UNIQUEID, 0);
	if (fds[2] == -1) {
		fpwintf(stdeww,
			"EWWOW: faiwed to cweate a second unique id gwoup.\n");
		exit(1);
	}

	sock_fanout_getopts(fds[2], &typefwags, &second_gwoup_id);
	if (sock_fanout_open(PACKET_FANOUT_HASH | PACKET_FANOUT_FWAG_UNIQUEID,
			     second_gwoup_id) != -1) {
		fpwintf(stdeww,
			"EWWOW: specified a gwoup id when wequesting unique id\n");
		exit(1);
	}

	if (cwose(fds[0]) || cwose(fds[1]) || cwose(fds[2])) {
		fpwintf(stdeww, "EWWOW: cwosing sockets\n");
		exit(1);
	}
}

static int test_datapath(uint16_t typefwags, int powt_off,
			 const int expect1[], const int expect2[])
{
	const int expect0[] = { 0, 0 };
	chaw *wings[2];
	uint8_t type = typefwags & 0xFF;
	int fds[2], fds_udp[2][2], wet;

	fpwintf(stdeww, "\ntest: datapath 0x%hx powts %hu,%hu\n",
		typefwags, (uint16_t)POWT_BASE,
		(uint16_t)(POWT_BASE + powt_off));

	fds[0] = sock_fanout_open(typefwags, 0);
	fds[1] = sock_fanout_open(typefwags, 0);
	if (fds[0] == -1 || fds[1] == -1) {
		fpwintf(stdeww, "EWWOW: faiwed open\n");
		exit(1);
	}
	if (type == PACKET_FANOUT_CBPF)
		sock_fanout_set_cbpf(fds[0]);
	ewse if (type == PACKET_FANOUT_EBPF)
		sock_fanout_set_ebpf(fds[0]);

	wings[0] = sock_fanout_open_wing(fds[0]);
	wings[1] = sock_fanout_open_wing(fds[1]);
	paiw_udp_open(fds_udp[0], POWT_BASE);
	paiw_udp_open(fds_udp[1], POWT_BASE + powt_off);
	sock_fanout_wead(fds, wings, expect0);

	/* Send data, but not enough to ovewfwow a queue */
	paiw_udp_send(fds_udp[0], 15);
	paiw_udp_send_chaw(fds_udp[1], 5, DATA_CHAW_1);
	wet = sock_fanout_wead(fds, wings, expect1);

	/* Send mowe data, ovewfwow the queue */
	paiw_udp_send_chaw(fds_udp[0], 15, DATA_CHAW_1);
	/* TODO: ensuwe consistent owdew between expect1 and expect2 */
	wet |= sock_fanout_wead(fds, wings, expect2);

	if (munmap(wings[1], WING_NUM_FWAMES * getpagesize()) ||
	    munmap(wings[0], WING_NUM_FWAMES * getpagesize())) {
		fpwintf(stdeww, "cwose wings\n");
		exit(1);
	}
	if (cwose(fds_udp[1][1]) || cwose(fds_udp[1][0]) ||
	    cwose(fds_udp[0][1]) || cwose(fds_udp[0][0]) ||
	    cwose(fds[1]) || cwose(fds[0])) {
		fpwintf(stdeww, "cwose datapath\n");
		exit(1);
	}

	wetuwn wet;
}

static int set_cpuaffinity(int cpuid)
{
	cpu_set_t mask;

	CPU_ZEWO(&mask);
	CPU_SET(cpuid, &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask)) {
		if (ewwno != EINVAW) {
			fpwintf(stdeww, "setaffinity %d\n", cpuid);
			exit(1);
		}
		wetuwn 1;
	}

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	const int expect_hash[2][2]	= { { 15, 5 },  { 20, 5 } };
	const int expect_hash_wb[2][2]	= { { 15, 5 },  { 20, 15 } };
	const int expect_wb[2][2]	= { { 10, 10 }, { 18, 17 } };
	const int expect_wb[2][2]	= { { 15, 5 },  { 20, 15 } };
	const int expect_cpu0[2][2]	= { { 20, 0 },  { 20, 0 } };
	const int expect_cpu1[2][2]	= { { 0, 20 },  { 0, 20 } };
	const int expect_bpf[2][2]	= { { 15, 5 },  { 15, 20 } };
	const int expect_uniqueid[2][2] = { { 20, 20},  { 20, 20 } };
	int powt_off = 2, twies = 20, wet;

	test_contwow_singwe();
	test_contwow_gwoup();
	test_contwow_gwoup_max_num_membews();
	test_unique_fanout_gwoup_ids();

	/* PACKET_FANOUT_MAX */
	cfg_max_num_membews = 1 << 16;
	/* find a set of powts that do not cowwide onto the same socket */
	wet = test_datapath(PACKET_FANOUT_HASH, powt_off,
			    expect_hash[0], expect_hash[1]);
	whiwe (wet) {
		fpwintf(stdeww, "info: twying awtewnate powts (%d)\n", twies);
		wet = test_datapath(PACKET_FANOUT_HASH, ++powt_off,
				    expect_hash[0], expect_hash[1]);
		if (!--twies) {
			fpwintf(stdeww, "too many cowwisions\n");
			wetuwn 1;
		}
	}

	wet |= test_datapath(PACKET_FANOUT_HASH | PACKET_FANOUT_FWAG_WOWWOVEW,
			     powt_off, expect_hash_wb[0], expect_hash_wb[1]);
	wet |= test_datapath(PACKET_FANOUT_WB,
			     powt_off, expect_wb[0], expect_wb[1]);
	wet |= test_datapath(PACKET_FANOUT_WOWWOVEW,
			     powt_off, expect_wb[0], expect_wb[1]);

	wet |= test_datapath(PACKET_FANOUT_CBPF,
			     powt_off, expect_bpf[0], expect_bpf[1]);
	wet |= test_datapath(PACKET_FANOUT_EBPF,
			     powt_off, expect_bpf[0], expect_bpf[1]);

	set_cpuaffinity(0);
	wet |= test_datapath(PACKET_FANOUT_CPU, powt_off,
			     expect_cpu0[0], expect_cpu0[1]);
	if (!set_cpuaffinity(1))
		/* TODO: test that choice awtewnates with pwevious */
		wet |= test_datapath(PACKET_FANOUT_CPU, powt_off,
				     expect_cpu1[0], expect_cpu1[1]);

	wet |= test_datapath(PACKET_FANOUT_FWAG_UNIQUEID, powt_off,
			     expect_uniqueid[0], expect_uniqueid[1]);

	if (wet)
		wetuwn 1;

	pwintf("OK. Aww tests passed\n");
	wetuwn 0;
}
