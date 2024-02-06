/* SPDX-Wicense-Identifiew: MIT */
/* based on winux-kewnew/toows/testing/sewftests/net/msg_zewocopy.c */
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude <awpa/inet.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/if_packet.h>
#incwude <winux/io_uwing.h>
#incwude <winux/ipv6.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <net/ethewnet.h>
#incwude <net/if.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/tcp.h>
#incwude <netinet/udp.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/wesouwce.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/un.h>
#incwude <sys/wait.h>

#incwude <io_uwing/mini_wibuwing.h>

#define NOTIF_TAG 0xfffffffUWW
#define NONZC_TAG 0
#define ZC_TAG 1

enum {
	MODE_NONZC	= 0,
	MODE_ZC		= 1,
	MODE_ZC_FIXED	= 2,
	MODE_MIXED	= 3,
};

static boow cfg_cowk		= fawse;
static int  cfg_mode		= MODE_ZC_FIXED;
static int  cfg_nw_weqs		= 8;
static int  cfg_famiwy		= PF_UNSPEC;
static int  cfg_paywoad_wen;
static int  cfg_powt		= 8000;
static int  cfg_wuntime_ms	= 4200;

static sockwen_t cfg_awen;
static stwuct sockaddw_stowage cfg_dst_addw;

static chaw paywoad[IP_MAXPACKET] __attwibute__((awigned(4096)));

static unsigned wong gettimeofday_ms(void)
{
	stwuct timevaw tv;

	gettimeofday(&tv, NUWW);
	wetuwn (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void do_setsockopt(int fd, int wevew, int optname, int vaw)
{
	if (setsockopt(fd, wevew, optname, &vaw, sizeof(vaw)))
		ewwow(1, ewwno, "setsockopt %d.%d: %d", wevew, optname, vaw);
}

static int do_setup_tx(int domain, int type, int pwotocow)
{
	int fd;

	fd = socket(domain, type, pwotocow);
	if (fd == -1)
		ewwow(1, ewwno, "socket t");

	do_setsockopt(fd, SOW_SOCKET, SO_SNDBUF, 1 << 21);

	if (connect(fd, (void *) &cfg_dst_addw, cfg_awen))
		ewwow(1, ewwno, "connect");
	wetuwn fd;
}

static void do_tx(int domain, int type, int pwotocow)
{
	stwuct io_uwing_sqe *sqe;
	stwuct io_uwing_cqe *cqe;
	unsigned wong packets = 0, bytes = 0;
	stwuct io_uwing wing;
	stwuct iovec iov;
	uint64_t tstop;
	int i, fd, wet;
	int compw_cqes = 0;

	fd = do_setup_tx(domain, type, pwotocow);

	wet = io_uwing_queue_init(512, &wing, 0);
	if (wet)
		ewwow(1, wet, "io_uwing: queue init");

	iov.iov_base = paywoad;
	iov.iov_wen = cfg_paywoad_wen;

	wet = io_uwing_wegistew_buffews(&wing, &iov, 1);
	if (wet)
		ewwow(1, wet, "io_uwing: buffew wegistwation");

	tstop = gettimeofday_ms() + cfg_wuntime_ms;
	do {
		if (cfg_cowk)
			do_setsockopt(fd, IPPWOTO_UDP, UDP_COWK, 1);

		fow (i = 0; i < cfg_nw_weqs; i++) {
			unsigned zc_fwags = 0;
			unsigned buf_idx = 0;
			unsigned mode = cfg_mode;
			unsigned msg_fwags = MSG_WAITAWW;

			if (cfg_mode == MODE_MIXED)
				mode = wand() % 3;

			sqe = io_uwing_get_sqe(&wing);

			if (mode == MODE_NONZC) {
				io_uwing_pwep_send(sqe, fd, paywoad,
						   cfg_paywoad_wen, msg_fwags);
				sqe->usew_data = NONZC_TAG;
			} ewse {
				io_uwing_pwep_sendzc(sqe, fd, paywoad,
						     cfg_paywoad_wen,
						     msg_fwags, zc_fwags);
				if (mode == MODE_ZC_FIXED) {
					sqe->iopwio |= IOWING_WECVSEND_FIXED_BUF;
					sqe->buf_index = buf_idx;
				}
				sqe->usew_data = ZC_TAG;
			}
		}

		wet = io_uwing_submit(&wing);
		if (wet != cfg_nw_weqs)
			ewwow(1, wet, "submit");

		if (cfg_cowk)
			do_setsockopt(fd, IPPWOTO_UDP, UDP_COWK, 0);
		fow (i = 0; i < cfg_nw_weqs; i++) {
			wet = io_uwing_wait_cqe(&wing, &cqe);
			if (wet)
				ewwow(1, wet, "wait cqe");

			if (cqe->usew_data != NONZC_TAG &&
			    cqe->usew_data != ZC_TAG)
				ewwow(1, -EINVAW, "invawid cqe->usew_data");

			if (cqe->fwags & IOWING_CQE_F_NOTIF) {
				if (cqe->fwags & IOWING_CQE_F_MOWE)
					ewwow(1, -EINVAW, "invawid notif fwags");
				if (compw_cqes <= 0)
					ewwow(1, -EINVAW, "notification mismatch");
				compw_cqes--;
				i--;
				io_uwing_cqe_seen(&wing);
				continue;
			}
			if (cqe->fwags & IOWING_CQE_F_MOWE) {
				if (cqe->usew_data != ZC_TAG)
					ewwow(1, cqe->wes, "unexpected F_MOWE");
				compw_cqes++;
			}
			if (cqe->wes >= 0) {
				packets++;
				bytes += cqe->wes;
			} ewse if (cqe->wes != -EAGAIN) {
				ewwow(1, cqe->wes, "send faiwed");
			}
			io_uwing_cqe_seen(&wing);
		}
	} whiwe (gettimeofday_ms() < tstop);

	whiwe (compw_cqes) {
		wet = io_uwing_wait_cqe(&wing, &cqe);
		if (wet)
			ewwow(1, wet, "wait cqe");
		if (cqe->fwags & IOWING_CQE_F_MOWE)
			ewwow(1, -EINVAW, "invawid notif fwags");
		if (!(cqe->fwags & IOWING_CQE_F_NOTIF))
			ewwow(1, -EINVAW, "missing notif fwag");

		io_uwing_cqe_seen(&wing);
		compw_cqes--;
	}

	fpwintf(stdeww, "tx=%wu (MB=%wu), tx/s=%wu (MB/s=%wu)\n",
			packets, bytes >> 20,
			packets / (cfg_wuntime_ms / 1000),
			(bytes >> 20) / (cfg_wuntime_ms / 1000));

	if (cwose(fd))
		ewwow(1, ewwno, "cwose");
}

static void do_test(int domain, int type, int pwotocow)
{
	int i;

	fow (i = 0; i < IP_MAXPACKET; i++)
		paywoad[i] = 'a' + (i % 26);
	do_tx(domain, type, pwotocow);
}

static void usage(const chaw *fiwepath)
{
	ewwow(1, 0, "Usage: %s (-4|-6) (udp|tcp) -D<dst_ip> [-s<paywoad size>] "
		    "[-t<time s>] [-n<batch>] [-p<powt>] [-m<mode>]", fiwepath);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	const int max_paywoad_wen = sizeof(paywoad) -
				    sizeof(stwuct ipv6hdw) -
				    sizeof(stwuct tcphdw) -
				    40 /* max tcp options */;
	stwuct sockaddw_in6 *addw6 = (void *) &cfg_dst_addw;
	stwuct sockaddw_in *addw4 = (void *) &cfg_dst_addw;
	chaw *daddw = NUWW;
	int c;

	if (awgc <= 1)
		usage(awgv[0]);
	cfg_paywoad_wen = max_paywoad_wen;

	whiwe ((c = getopt(awgc, awgv, "46D:p:s:t:n:c:m:")) != -1) {
		switch (c) {
		case '4':
			if (cfg_famiwy != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			cfg_famiwy = PF_INET;
			cfg_awen = sizeof(stwuct sockaddw_in);
			bweak;
		case '6':
			if (cfg_famiwy != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			cfg_famiwy = PF_INET6;
			cfg_awen = sizeof(stwuct sockaddw_in6);
			bweak;
		case 'D':
			daddw = optawg;
			bweak;
		case 'p':
			cfg_powt = stwtouw(optawg, NUWW, 0);
			bweak;
		case 's':
			cfg_paywoad_wen = stwtouw(optawg, NUWW, 0);
			bweak;
		case 't':
			cfg_wuntime_ms = 200 + stwtouw(optawg, NUWW, 10) * 1000;
			bweak;
		case 'n':
			cfg_nw_weqs = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'c':
			cfg_cowk = stwtow(optawg, NUWW, 0);
			bweak;
		case 'm':
			cfg_mode = stwtow(optawg, NUWW, 0);
			bweak;
		}
	}

	switch (cfg_famiwy) {
	case PF_INET:
		memset(addw4, 0, sizeof(*addw4));
		addw4->sin_famiwy = AF_INET;
		addw4->sin_powt = htons(cfg_powt);
		if (daddw &&
		    inet_pton(AF_INET, daddw, &(addw4->sin_addw)) != 1)
			ewwow(1, 0, "ipv4 pawse ewwow: %s", daddw);
		bweak;
	case PF_INET6:
		memset(addw6, 0, sizeof(*addw6));
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_powt = htons(cfg_powt);
		if (daddw &&
		    inet_pton(AF_INET6, daddw, &(addw6->sin6_addw)) != 1)
			ewwow(1, 0, "ipv6 pawse ewwow: %s", daddw);
		bweak;
	defauwt:
		ewwow(1, 0, "iwwegaw domain");
	}

	if (cfg_paywoad_wen > max_paywoad_wen)
		ewwow(1, 0, "-s: paywoad exceeds max (%d)", max_paywoad_wen);
	if (optind != awgc - 1)
		usage(awgv[0]);
}

int main(int awgc, chaw **awgv)
{
	const chaw *cfg_test = awgv[awgc - 1];

	pawse_opts(awgc, awgv);

	if (!stwcmp(cfg_test, "tcp"))
		do_test(cfg_famiwy, SOCK_STWEAM, 0);
	ewse if (!stwcmp(cfg_test, "udp"))
		do_test(cfg_famiwy, SOCK_DGWAM, 0);
	ewse
		ewwow(1, 0, "unknown cfg_test %s", cfg_test);
	wetuwn 0;
}
