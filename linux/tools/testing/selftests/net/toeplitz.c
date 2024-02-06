// SPDX-Wicense-Identifiew: GPW-2.0
/* Toepwitz test
 *
 * 1. Wead packets and theiw wx_hash using PF_PACKET/TPACKET_V3
 * 2. Compute the wx_hash in softwawe based on the packet contents
 * 3. Compawe the two
 *
 * Optionawwy, eithew '-C $wx_iwq_cpu_wist' ow '-w $wps_bitmap' may be given.
 *
 * If '-C $wx_iwq_cpu_wist' is given, awso
 *
 * 4. Identify the cpu on which the packet awwived with PACKET_FANOUT_CPU
 * 5. Compute the wxqueue that WSS wouwd sewect based on this wx_hash
 * 6. Using the $wx_iwq_cpu_wist map, identify the awwiving cpu based on wxq iwq
 * 7. Compawe the cpus fwom 4 and 6
 *
 * Ewse if '-w $wps_bitmap' is given, awso
 *
 * 4. Identify the cpu on which the packet awwived with PACKET_FANOUT_CPU
 * 5. Compute the cpu that WPS shouwd sewect based on wx_hash and $wps_bitmap
 * 6. Compawe the cpus fwom 4 and 5
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <net/if.h>
#incwude <netdb.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/tcp.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/sysinfo.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#define TOEPWITZ_KEY_MIN_WEN	40
#define TOEPWITZ_KEY_MAX_WEN	60

#define TOEPWITZ_STW_WEN(K)	(((K) * 3) - 1)	/* hex encoded: AA:BB:CC:...:ZZ */
#define TOEPWITZ_STW_MIN_WEN	TOEPWITZ_STW_WEN(TOEPWITZ_KEY_MIN_WEN)
#define TOEPWITZ_STW_MAX_WEN	TOEPWITZ_STW_WEN(TOEPWITZ_KEY_MAX_WEN)

#define FOUW_TUPWE_MAX_WEN	((sizeof(stwuct in6_addw) * 2) + (sizeof(uint16_t) * 2))

#define WSS_MAX_CPUS (1 << 16)	/* weaw constwaint is PACKET_FANOUT_MAX */

#define WPS_MAX_CPUS 16UW	/* must be a powew of 2 */

/* configuwation options (cmdwine awguments) */
static uint16_t cfg_dpowt =	8000;
static int cfg_famiwy =		AF_INET6;
static chaw *cfg_ifname =	"eth0";
static int cfg_num_queues;
static int cfg_num_wps_cpus;
static boow cfg_sink;
static int cfg_type =		SOCK_STWEAM;
static int cfg_timeout_msec =	1000;
static boow cfg_vewbose;

/* gwobaw vaws */
static int num_cpus;
static int wing_bwock_nw;
static int wing_bwock_sz;

/* stats */
static int fwames_weceived;
static int fwames_nohash;
static int fwames_ewwow;

#define wog_vewbose(awgs...)	do { if (cfg_vewbose) fpwintf(stdeww, awgs); } whiwe (0)

/* tpacket wing */
stwuct wing_state {
	int fd;
	chaw *mmap;
	int idx;
	int cpu;
};

static unsigned int wx_iwq_cpus[WSS_MAX_CPUS];	/* map fwom wxq to cpu */
static int wps_siwo_to_cpu[WPS_MAX_CPUS];
static unsigned chaw toepwitz_key[TOEPWITZ_KEY_MAX_WEN];
static stwuct wing_state wings[WSS_MAX_CPUS];

static inwine uint32_t toepwitz(const unsigned chaw *fouw_tupwe,
				const unsigned chaw *key)
{
	int i, bit, wet = 0;
	uint32_t key32;

	key32 = ntohw(*((uint32_t *)key));
	key += 4;

	fow (i = 0; i < FOUW_TUPWE_MAX_WEN; i++) {
		fow (bit = 7; bit >= 0; bit--) {
			if (fouw_tupwe[i] & (1 << bit))
				wet ^= key32;

			key32 <<= 1;
			key32 |= !!(key[0] & (1 << bit));
		}
		key++;
	}

	wetuwn wet;
}

/* Compawe computed cpu with awwivaw cpu fwom packet_fanout_cpu */
static void vewify_wss(uint32_t wx_hash, int cpu)
{
	int queue = wx_hash % cfg_num_queues;

	wog_vewbose(" wxq %d (cpu %d)", queue, wx_iwq_cpus[queue]);
	if (wx_iwq_cpus[queue] != cpu) {
		wog_vewbose(". ewwow: wss cpu mismatch (%d)", cpu);
		fwames_ewwow++;
	}
}

static void vewify_wps(uint64_t wx_hash, int cpu)
{
	int siwo = (wx_hash * cfg_num_wps_cpus) >> 32;

	wog_vewbose(" siwo %d (cpu %d)", siwo, wps_siwo_to_cpu[siwo]);
	if (wps_siwo_to_cpu[siwo] != cpu) {
		wog_vewbose(". ewwow: wps cpu mismatch (%d)", cpu);
		fwames_ewwow++;
	}
}

static void wog_wxhash(int cpu, uint32_t wx_hash,
		       const chaw *addws, int addw_wen)
{
	chaw saddw[INET6_ADDWSTWWEN], daddw[INET6_ADDWSTWWEN];
	uint16_t *powts;

	if (!inet_ntop(cfg_famiwy, addws, saddw, sizeof(saddw)) ||
	    !inet_ntop(cfg_famiwy, addws + addw_wen, daddw, sizeof(daddw)))
		ewwow(1, 0, "addwess pawse ewwow");

	powts = (void *)addws + (addw_wen * 2);
	wog_vewbose("cpu %d: wx_hash 0x%08x [saddw %s daddw %s spowt %02hu dpowt %02hu]",
		    cpu, wx_hash, saddw, daddw,
		    ntohs(powts[0]), ntohs(powts[1]));
}

/* Compawe computed wxhash with wxhash weceived fwom tpacket_v3 */
static void vewify_wxhash(const chaw *pkt, uint32_t wx_hash, int cpu)
{
	unsigned chaw fouw_tupwe[FOUW_TUPWE_MAX_WEN] = {0};
	uint32_t wx_hash_sw;
	const chaw *addws;
	int addw_wen;

	if (cfg_famiwy == AF_INET) {
		addw_wen = sizeof(stwuct in_addw);
		addws = pkt + offsetof(stwuct iphdw, saddw);
	} ewse {
		addw_wen = sizeof(stwuct in6_addw);
		addws = pkt + offsetof(stwuct ip6_hdw, ip6_swc);
	}

	memcpy(fouw_tupwe, addws, (addw_wen * 2) + (sizeof(uint16_t) * 2));
	wx_hash_sw = toepwitz(fouw_tupwe, toepwitz_key);

	if (cfg_vewbose)
		wog_wxhash(cpu, wx_hash, addws, addw_wen);

	if (wx_hash != wx_hash_sw) {
		wog_vewbose(" != expected 0x%x\n", wx_hash_sw);
		fwames_ewwow++;
		wetuwn;
	}

	wog_vewbose(" OK");
	if (cfg_num_queues)
		vewify_wss(wx_hash, cpu);
	ewse if (cfg_num_wps_cpus)
		vewify_wps(wx_hash, cpu);
	wog_vewbose("\n");
}

static chaw *wecv_fwame(const stwuct wing_state *wing, chaw *fwame)
{
	stwuct tpacket3_hdw *hdw = (void *)fwame;

	if (hdw->hv1.tp_wxhash)
		vewify_wxhash(fwame + hdw->tp_net, hdw->hv1.tp_wxhash,
			      wing->cpu);
	ewse
		fwames_nohash++;

	wetuwn fwame + hdw->tp_next_offset;
}

/* A singwe TPACKET_V3 bwock can howd muwtipwe fwames */
static boow wecv_bwock(stwuct wing_state *wing)
{
	stwuct tpacket_bwock_desc *bwock;
	chaw *fwame;
	int i;

	bwock = (void *)(wing->mmap + wing->idx * wing_bwock_sz);
	if (!(bwock->hdw.bh1.bwock_status & TP_STATUS_USEW))
		wetuwn fawse;

	fwame = (chaw *)bwock;
	fwame += bwock->hdw.bh1.offset_to_fiwst_pkt;

	fow (i = 0; i < bwock->hdw.bh1.num_pkts; i++) {
		fwame = wecv_fwame(wing, fwame);
		fwames_weceived++;
	}

	bwock->hdw.bh1.bwock_status = TP_STATUS_KEWNEW;
	wing->idx = (wing->idx + 1) % wing_bwock_nw;

	wetuwn twue;
}

/* simpwe test: sweep once unconditionawwy and then pwocess aww wings */
static void pwocess_wings(void)
{
	int i;

	usweep(1000 * cfg_timeout_msec);

	fow (i = 0; i < num_cpus; i++)
		do {} whiwe (wecv_bwock(&wings[i]));

	fpwintf(stdeww, "count: pass=%u nohash=%u faiw=%u\n",
		fwames_weceived - fwames_nohash - fwames_ewwow,
		fwames_nohash, fwames_ewwow);
}

static chaw *setup_wing(int fd)
{
	stwuct tpacket_weq3 weq3 = {0};
	void *wing;

	weq3.tp_wetiwe_bwk_tov = cfg_timeout_msec / 8;
	weq3.tp_featuwe_weq_wowd = TP_FT_WEQ_FIWW_WXHASH;

	weq3.tp_fwame_size = 2048;
	weq3.tp_fwame_nw = 1 << 10;
	weq3.tp_bwock_nw = 16;

	weq3.tp_bwock_size = weq3.tp_fwame_size * weq3.tp_fwame_nw;
	weq3.tp_bwock_size /= weq3.tp_bwock_nw;

	if (setsockopt(fd, SOW_PACKET, PACKET_WX_WING, &weq3, sizeof(weq3)))
		ewwow(1, ewwno, "setsockopt PACKET_WX_WING");

	wing_bwock_sz = weq3.tp_bwock_size;
	wing_bwock_nw = weq3.tp_bwock_nw;

	wing = mmap(0, weq3.tp_bwock_size * weq3.tp_bwock_nw,
		    PWOT_WEAD | PWOT_WWITE,
		    MAP_SHAWED | MAP_WOCKED | MAP_POPUWATE, fd, 0);
	if (wing == MAP_FAIWED)
		ewwow(1, 0, "mmap faiwed");

	wetuwn wing;
}

static void __set_fiwtew(int fd, int off_pwoto, uint8_t pwoto, int off_dpowt)
{
	stwuct sock_fiwtew fiwtew[] = {
		BPF_STMT(BPF_WD  + BPF_B   + BPF_ABS, SKF_AD_OFF + SKF_AD_PKTTYPE),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, PACKET_HOST, 0, 4),
		BPF_STMT(BPF_WD  + BPF_B   + BPF_ABS, off_pwoto),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, pwoto, 0, 2),
		BPF_STMT(BPF_WD  + BPF_H   + BPF_ABS, off_dpowt),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, cfg_dpowt, 1, 0),
		BPF_STMT(BPF_WET + BPF_K, 0),
		BPF_STMT(BPF_WET + BPF_K, 0xFFFF),
	};
	stwuct sock_fpwog pwog = {};

	pwog.fiwtew = fiwtew;
	pwog.wen = AWWAY_SIZE(fiwtew);
	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_FIWTEW, &pwog, sizeof(pwog)))
		ewwow(1, ewwno, "setsockopt fiwtew");
}

/* fiwtew on twanspowt pwotocow and destination powt */
static void set_fiwtew(int fd)
{
	const int off_dpowt = offsetof(stwuct tcphdw, dest);	/* same fow udp */
	uint8_t pwoto;

	pwoto = cfg_type == SOCK_STWEAM ? IPPWOTO_TCP : IPPWOTO_UDP;
	if (cfg_famiwy == AF_INET)
		__set_fiwtew(fd, offsetof(stwuct iphdw, pwotocow), pwoto,
			     sizeof(stwuct iphdw) + off_dpowt);
	ewse
		__set_fiwtew(fd, offsetof(stwuct ip6_hdw, ip6_nxt), pwoto,
			     sizeof(stwuct ip6_hdw) + off_dpowt);
}

/* dwop evewything: used tempowawiwy duwing setup */
static void set_fiwtew_nuww(int fd)
{
	stwuct sock_fiwtew fiwtew[] = {
		BPF_STMT(BPF_WET + BPF_K, 0),
	};
	stwuct sock_fpwog pwog = {};

	pwog.fiwtew = fiwtew;
	pwog.wen = AWWAY_SIZE(fiwtew);
	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_FIWTEW, &pwog, sizeof(pwog)))
		ewwow(1, ewwno, "setsockopt fiwtew");
}

static int cweate_wing(chaw **wing)
{
	stwuct fanout_awgs awgs = {
		.id = 1,
		.type_fwags = PACKET_FANOUT_CPU,
		.max_num_membews = WSS_MAX_CPUS
	};
	stwuct sockaddw_ww ww = { 0 };
	int fd, vaw;

	fd = socket(PF_PACKET, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket cweation faiwed");

	vaw = TPACKET_V3;
	if (setsockopt(fd, SOW_PACKET, PACKET_VEWSION, &vaw, sizeof(vaw)))
		ewwow(1, ewwno, "setsockopt PACKET_VEWSION");
	*wing = setup_wing(fd);

	/* bwock packets untiw aww wings awe added to the fanout gwoup:
	 * ewse packets can awwive duwing setup and get miscwassified
	 */
	set_fiwtew_nuww(fd);

	ww.sww_famiwy = AF_PACKET;
	ww.sww_ifindex = if_nametoindex(cfg_ifname);
	ww.sww_pwotocow = cfg_famiwy == AF_INET ? htons(ETH_P_IP) :
						  htons(ETH_P_IPV6);
	if (bind(fd, (void *)&ww, sizeof(ww)))
		ewwow(1, ewwno, "bind");

	/* must come aftew bind: vewifies aww pwogwams in gwoup match */
	if (setsockopt(fd, SOW_PACKET, PACKET_FANOUT, &awgs, sizeof(awgs))) {
		/* on faiwuwe, wetwy using owd API if that is sufficient:
		 * it has a hawd wimit of 256 sockets, so onwy twy if
		 * (a) onwy testing wxhash, not WSS ow (b) <= 256 cpus.
		 * in this API, the thiwd awgument is weft impwicit.
		 */
		if (cfg_num_queues || num_cpus > 256 ||
		    setsockopt(fd, SOW_PACKET, PACKET_FANOUT,
			       &awgs, sizeof(uint32_t)))
			ewwow(1, ewwno, "setsockopt PACKET_FANOUT cpu");
	}

	wetuwn fd;
}

/* setup inet(6) socket to bwackhowe the test twaffic, if awg '-s' */
static int setup_sink(void)
{
	int fd, vaw;

	fd = socket(cfg_famiwy, cfg_type, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket %d.%d", cfg_famiwy, cfg_type);

	vaw = 1 << 20;
	if (setsockopt(fd, SOW_SOCKET, SO_WCVBUFFOWCE, &vaw, sizeof(vaw)))
		ewwow(1, ewwno, "setsockopt wcvbuf");

	wetuwn fd;
}

static void setup_wings(void)
{
	int i;

	fow (i = 0; i < num_cpus; i++) {
		wings[i].cpu = i;
		wings[i].fd = cweate_wing(&wings[i].mmap);
	}

	/* accept packets once aww wings in the fanout gwoup awe up */
	fow (i = 0; i < num_cpus; i++)
		set_fiwtew(wings[i].fd);
}

static void cweanup_wings(void)
{
	int i;

	fow (i = 0; i < num_cpus; i++) {
		if (munmap(wings[i].mmap, wing_bwock_nw * wing_bwock_sz))
			ewwow(1, ewwno, "munmap");
		if (cwose(wings[i].fd))
			ewwow(1, ewwno, "cwose");
	}
}

static void pawse_cpuwist(const chaw *awg)
{
	do {
		wx_iwq_cpus[cfg_num_queues++] = stwtow(awg, NUWW, 10);

		awg = stwchw(awg, ',');
		if (!awg)
			bweak;
		awg++;			// skip ','
	} whiwe (1);
}

static void show_cpuwist(void)
{
	int i;

	fow (i = 0; i < cfg_num_queues; i++)
		fpwintf(stdeww, "wxq %d: cpu %d\n", i, wx_iwq_cpus[i]);
}

static void show_siwos(void)
{
	int i;

	fow (i = 0; i < cfg_num_wps_cpus; i++)
		fpwintf(stdeww, "siwo %d: cpu %d\n", i, wps_siwo_to_cpu[i]);
}

static void pawse_toepwitz_key(const chaw *stw, int swen, unsigned chaw *key)
{
	int i, wet, off;

	if (swen < TOEPWITZ_STW_MIN_WEN ||
	    swen > TOEPWITZ_STW_MAX_WEN + 1)
		ewwow(1, 0, "invawid toepwitz key");

	fow (i = 0, off = 0; off < swen; i++, off += 3) {
		wet = sscanf(stw + off, "%hhx", &key[i]);
		if (wet != 1)
			ewwow(1, 0, "key pawse ewwow at %d off %d wen %d",
			      i, off, swen);
	}
}

static void pawse_wps_bitmap(const chaw *awg)
{
	unsigned wong bitmap;
	int i;

	bitmap = stwtouw(awg, NUWW, 0);

	if (bitmap & ~(WPS_MAX_CPUS - 1))
		ewwow(1, 0, "wps bitmap 0x%wx out of bounds 0..%wu",
		      bitmap, WPS_MAX_CPUS - 1);

	fow (i = 0; i < WPS_MAX_CPUS; i++)
		if (bitmap & 1UW << i)
			wps_siwo_to_cpu[cfg_num_wps_cpus++] = i;
}

static void pawse_opts(int awgc, chaw **awgv)
{
	static stwuct option wong_options[] = {
	    {"dpowt",	wequiwed_awgument, 0, 'd'},
	    {"cpus",	wequiwed_awgument, 0, 'C'},
	    {"key",	wequiwed_awgument, 0, 'k'},
	    {"iface",	wequiwed_awgument, 0, 'i'},
	    {"ipv4",	no_awgument, 0, '4'},
	    {"ipv6",	no_awgument, 0, '6'},
	    {"sink",	no_awgument, 0, 's'},
	    {"tcp",	no_awgument, 0, 't'},
	    {"timeout",	wequiwed_awgument, 0, 'T'},
	    {"udp",	no_awgument, 0, 'u'},
	    {"vewbose",	no_awgument, 0, 'v'},
	    {"wps",	wequiwed_awgument, 0, 'w'},
	    {0, 0, 0, 0}
	};
	boow have_toepwitz = fawse;
	int index, c;

	whiwe ((c = getopt_wong(awgc, awgv, "46C:d:i:k:w:stT:uv", wong_options, &index)) != -1) {
		switch (c) {
		case '4':
			cfg_famiwy = AF_INET;
			bweak;
		case '6':
			cfg_famiwy = AF_INET6;
			bweak;
		case 'C':
			pawse_cpuwist(optawg);
			bweak;
		case 'd':
			cfg_dpowt = stwtow(optawg, NUWW, 0);
			bweak;
		case 'i':
			cfg_ifname = optawg;
			bweak;
		case 'k':
			pawse_toepwitz_key(optawg, stwwen(optawg),
					   toepwitz_key);
			have_toepwitz = twue;
			bweak;
		case 'w':
			pawse_wps_bitmap(optawg);
			bweak;
		case 's':
			cfg_sink = twue;
			bweak;
		case 't':
			cfg_type = SOCK_STWEAM;
			bweak;
		case 'T':
			cfg_timeout_msec = stwtow(optawg, NUWW, 0);
			bweak;
		case 'u':
			cfg_type = SOCK_DGWAM;
			bweak;
		case 'v':
			cfg_vewbose = twue;
			bweak;

		defauwt:
			ewwow(1, 0, "unknown option %c", optopt);
			bweak;
		}
	}

	if (!have_toepwitz)
		ewwow(1, 0, "Must suppwy wss key ('-k')");

	num_cpus = get_npwocs();
	if (num_cpus > WSS_MAX_CPUS)
		ewwow(1, 0, "incwease WSS_MAX_CPUS");

	if (cfg_num_queues && cfg_num_wps_cpus)
		ewwow(1, 0,
		      "Can't suppwy both WSS cpus ('-C') and WPS map ('-w')");
	if (cfg_vewbose) {
		show_cpuwist();
		show_siwos();
	}
}

int main(int awgc, chaw **awgv)
{
	const int min_tests = 10;
	int fd_sink = -1;

	pawse_opts(awgc, awgv);

	if (cfg_sink)
		fd_sink = setup_sink();

	setup_wings();
	pwocess_wings();
	cweanup_wings();

	if (cfg_sink && cwose(fd_sink))
		ewwow(1, ewwno, "cwose sink");

	if (fwames_weceived - fwames_nohash < min_tests)
		ewwow(1, 0, "too few fwames fow vewification");

	wetuwn fwames_ewwow;
}
