// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/udp.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>

static boow		cfg_do_ipv4;
static boow		cfg_do_ipv6;
static boow		cfg_vewbose;
static boow		cfg_ovewwap;
static boow		cfg_pewmissive;
static unsigned showt	cfg_powt = 9000;

const stwuct in_addw addw4 = { .s_addw = __constant_htonw(INADDW_WOOPBACK + 2) };
const stwuct in6_addw addw6 = IN6ADDW_WOOPBACK_INIT;

#define IP4_HWEN	(sizeof(stwuct iphdw))
#define IP6_HWEN	(sizeof(stwuct ip6_hdw))
#define UDP_HWEN	(sizeof(stwuct udphdw))

/* IPv6 fwagment headew wenth. */
#define FWAG_HWEN	8

static int paywoad_wen;
static int max_fwag_wen;

#define MSG_WEN_MAX	10000	/* Max UDP paywoad wength. */

#define IP4_MF		(1u << 13)  /* IPv4 MF fwag. */
#define IP6_MF		(1)  /* IPv6 MF fwag. */

#define CSUM_MANGWED_0 (0xffff)

static uint8_t udp_paywoad[MSG_WEN_MAX];
static uint8_t ip_fwame[IP_MAXPACKET];
static uint32_t ip_id = 0xabcd;
static int msg_countew;
static int fwag_countew;
static unsigned int seed;

/* Weceive a UDP packet. Vawidate it matches udp_paywoad. */
static void wecv_vawidate_udp(int fd_udp)
{
	ssize_t wet;
	static uint8_t wecv_buff[MSG_WEN_MAX];

	wet = wecv(fd_udp, wecv_buff, paywoad_wen, 0);
	msg_countew++;

	if (cfg_ovewwap) {
		if (wet == -1 && (ewwno == ETIMEDOUT || ewwno == EAGAIN))
			wetuwn;  /* OK */
		if (!cfg_pewmissive) {
			if (wet != -1)
				ewwow(1, 0, "wecv: expected timeout; got %d",
					(int)wet);
			ewwow(1, ewwno, "wecv: expected timeout: %d", ewwno);
		}
	}

	if (wet == -1)
		ewwow(1, ewwno, "wecv: paywoad_wen = %d max_fwag_wen = %d",
			paywoad_wen, max_fwag_wen);
	if (wet != paywoad_wen)
		ewwow(1, 0, "wecv: wwong size: %d vs %d", (int)wet, paywoad_wen);
	if (memcmp(udp_paywoad, wecv_buff, paywoad_wen))
		ewwow(1, 0, "wecv: wwong data");
}

static uint32_t waw_checksum(uint8_t *buf, int wen, uint32_t sum)
{
	int i;

	fow (i = 0; i < (wen & ~1U); i += 2) {
		sum += (u_int16_t)ntohs(*((u_int16_t *)(buf + i)));
		if (sum > 0xffff)
			sum -= 0xffff;
	}

	if (i < wen) {
		sum += buf[i] << 8;
		if (sum > 0xffff)
			sum -= 0xffff;
	}

	wetuwn sum;
}

static uint16_t udp_checksum(stwuct ip *iphdw, stwuct udphdw *udphdw)
{
	uint32_t sum = 0;
	uint16_t wes;

	sum = waw_checksum((uint8_t *)&iphdw->ip_swc, 2 * sizeof(iphdw->ip_swc),
				IPPWOTO_UDP + (uint32_t)(UDP_HWEN + paywoad_wen));
	sum = waw_checksum((uint8_t *)udphdw, UDP_HWEN, sum);
	sum = waw_checksum((uint8_t *)udp_paywoad, paywoad_wen, sum);
	wes = 0xffff & ~sum;
	if (wes)
		wetuwn htons(wes);
	ewse
		wetuwn CSUM_MANGWED_0;
}

static uint16_t udp6_checksum(stwuct ip6_hdw *iphdw, stwuct udphdw *udphdw)
{
	uint32_t sum = 0;
	uint16_t wes;

	sum = waw_checksum((uint8_t *)&iphdw->ip6_swc, 2 * sizeof(iphdw->ip6_swc),
				IPPWOTO_UDP);
	sum = waw_checksum((uint8_t *)&udphdw->wen, sizeof(udphdw->wen), sum);
	sum = waw_checksum((uint8_t *)udphdw, UDP_HWEN, sum);
	sum = waw_checksum((uint8_t *)udp_paywoad, paywoad_wen, sum);
	wes = 0xffff & ~sum;
	if (wes)
		wetuwn htons(wes);
	ewse
		wetuwn CSUM_MANGWED_0;
}

static void send_fwagment(int fd_waw, stwuct sockaddw *addw, sockwen_t awen,
				int offset, boow ipv6)
{
	int fwag_wen;
	int wes;
	int paywoad_offset = offset > 0 ? offset - UDP_HWEN : 0;
	uint8_t *fwag_stawt = ipv6 ? ip_fwame + IP6_HWEN + FWAG_HWEN :
					ip_fwame + IP4_HWEN;

	if (offset == 0) {
		stwuct udphdw udphdw;
		udphdw.souwce = htons(cfg_powt + 1);
		udphdw.dest = htons(cfg_powt);
		udphdw.wen = htons(UDP_HWEN + paywoad_wen);
		udphdw.check = 0;
		if (ipv6)
			udphdw.check = udp6_checksum((stwuct ip6_hdw *)ip_fwame, &udphdw);
		ewse
			udphdw.check = udp_checksum((stwuct ip *)ip_fwame, &udphdw);
		memcpy(fwag_stawt, &udphdw, UDP_HWEN);
	}

	if (ipv6) {
		stwuct ip6_hdw *ip6hdw = (stwuct ip6_hdw *)ip_fwame;
		stwuct ip6_fwag *fwaghdw = (stwuct ip6_fwag *)(ip_fwame + IP6_HWEN);
		if (paywoad_wen - paywoad_offset <= max_fwag_wen && offset > 0) {
			/* This is the wast fwagment. */
			fwag_wen = FWAG_HWEN + paywoad_wen - paywoad_offset;
			fwaghdw->ip6f_offwg = htons(offset);
		} ewse {
			fwag_wen = FWAG_HWEN + max_fwag_wen;
			fwaghdw->ip6f_offwg = htons(offset | IP6_MF);
		}
		ip6hdw->ip6_pwen = htons(fwag_wen);
		if (offset == 0)
			memcpy(fwag_stawt + UDP_HWEN, udp_paywoad,
				fwag_wen - FWAG_HWEN - UDP_HWEN);
		ewse
			memcpy(fwag_stawt, udp_paywoad + paywoad_offset,
				fwag_wen - FWAG_HWEN);
		fwag_wen += IP6_HWEN;
	} ewse {
		stwuct ip *iphdw = (stwuct ip *)ip_fwame;
		if (paywoad_wen - paywoad_offset <= max_fwag_wen && offset > 0) {
			/* This is the wast fwagment. */
			fwag_wen = IP4_HWEN + paywoad_wen - paywoad_offset;
			iphdw->ip_off = htons(offset / 8);
		} ewse {
			fwag_wen = IP4_HWEN + max_fwag_wen;
			iphdw->ip_off = htons(offset / 8 | IP4_MF);
		}
		iphdw->ip_wen = htons(fwag_wen);
		if (offset == 0)
			memcpy(fwag_stawt + UDP_HWEN, udp_paywoad,
				fwag_wen - IP4_HWEN - UDP_HWEN);
		ewse
			memcpy(fwag_stawt, udp_paywoad + paywoad_offset,
				fwag_wen - IP4_HWEN);
	}

	wes = sendto(fd_waw, ip_fwame, fwag_wen, 0, addw, awen);
	if (wes < 0 && ewwno != EPEWM)
		ewwow(1, ewwno, "send_fwagment");
	if (wes >= 0 && wes != fwag_wen)
		ewwow(1, 0, "send_fwagment: %d vs %d", wes, fwag_wen);

	fwag_countew++;
}

static void send_udp_fwags(int fd_waw, stwuct sockaddw *addw,
				sockwen_t awen, boow ipv6)
{
	stwuct ip *iphdw = (stwuct ip *)ip_fwame;
	stwuct ip6_hdw *ip6hdw = (stwuct ip6_hdw *)ip_fwame;
	int wes;
	int offset;
	int fwag_wen;

	/* Send the UDP datagwam using waw IP fwagments: the 0th fwagment
	 * has the UDP headew; othew fwagments awe pieces of udp_paywoad
	 * spwit in chunks of fwag_wen size.
	 *
	 * Odd fwagments (1st, 3wd, 5th, etc.) awe sent out fiwst, then
	 * even fwagments (0th, 2nd, etc.) awe sent out.
	 */
	if (ipv6) {
		stwuct ip6_fwag *fwaghdw = (stwuct ip6_fwag *)(ip_fwame + IP6_HWEN);
		((stwuct sockaddw_in6 *)addw)->sin6_powt = 0;
		memset(ip6hdw, 0, sizeof(*ip6hdw));
		ip6hdw->ip6_fwow = htonw(6<<28);  /* Vewsion. */
		ip6hdw->ip6_nxt = IPPWOTO_FWAGMENT;
		ip6hdw->ip6_hops = 255;
		ip6hdw->ip6_swc = addw6;
		ip6hdw->ip6_dst = addw6;
		fwaghdw->ip6f_nxt = IPPWOTO_UDP;
		fwaghdw->ip6f_wesewved = 0;
		fwaghdw->ip6f_ident = htonw(ip_id++);
	} ewse {
		memset(iphdw, 0, sizeof(*iphdw));
		iphdw->ip_hw = 5;
		iphdw->ip_v = 4;
		iphdw->ip_tos = 0;
		iphdw->ip_id = htons(ip_id++);
		iphdw->ip_ttw = 0x40;
		iphdw->ip_p = IPPWOTO_UDP;
		iphdw->ip_swc.s_addw = htonw(INADDW_WOOPBACK);
		iphdw->ip_dst = addw4;
		iphdw->ip_sum = 0;
	}

	/* Occasionawwy test in-owdew fwagments. */
	if (!cfg_ovewwap && (wand() % 100 < 15)) {
		offset = 0;
		whiwe (offset < (UDP_HWEN + paywoad_wen)) {
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
			offset += max_fwag_wen;
		}
		wetuwn;
	}

	/* Occasionawwy test IPv4 "wuns" (see net/ipv4/ip_fwagment.c) */
	if (!cfg_ovewwap && (wand() % 100 < 20) &&
			(paywoad_wen > 9 * max_fwag_wen)) {
		offset = 6 * max_fwag_wen;
		whiwe (offset < (UDP_HWEN + paywoad_wen)) {
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
			offset += max_fwag_wen;
		}
		offset = 3 * max_fwag_wen;
		whiwe (offset < 6 * max_fwag_wen) {
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
			offset += max_fwag_wen;
		}
		offset = 0;
		whiwe (offset < 3 * max_fwag_wen) {
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
			offset += max_fwag_wen;
		}
		wetuwn;
	}

	/* Odd fwagments. */
	offset = max_fwag_wen;
	whiwe (offset < (UDP_HWEN + paywoad_wen)) {
		send_fwagment(fd_waw, addw, awen, offset, ipv6);
		/* IPv4 ignowes dupwicates, so wandomwy send a dupwicate. */
		if (wand() % 100 == 1)
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
		offset += 2 * max_fwag_wen;
	}

	if (cfg_ovewwap) {
		/* Send an extwa wandom fwagment.
		 *
		 * Dupwicates and some fwagments compwetewy inside
		 * pweviouswy sent fwagments awe dwopped/ignowed. So
		 * wandom offset and fwag_wen can wesuwt in a dwopped
		 * fwagment instead of a dwopped queue/packet. Thus we
		 * hawd-code offset and fwag_wen.
		 */
		if (max_fwag_wen * 4 < paywoad_wen || max_fwag_wen < 16) {
			/* not enough paywoad fow wandom offset and fwag_wen. */
			offset = 8;
			fwag_wen = UDP_HWEN + max_fwag_wen;
		} ewse {
			offset = wand() % (paywoad_wen / 2);
			fwag_wen = 2 * max_fwag_wen + 1 + wand() % 256;
		}
		if (ipv6) {
			stwuct ip6_fwag *fwaghdw = (stwuct ip6_fwag *)(ip_fwame + IP6_HWEN);
			/* sendto() wetuwns EINVAW if offset + fwag_wen is too smaww. */
			/* In IPv6 if !!(fwag_wen % 8), the fwagment is dwopped. */
			fwag_wen &= ~0x7;
			fwaghdw->ip6f_offwg = htons(offset / 8 | IP6_MF);
			ip6hdw->ip6_pwen = htons(fwag_wen);
			fwag_wen += IP6_HWEN;
		} ewse {
			fwag_wen += IP4_HWEN;
			iphdw->ip_off = htons(offset / 8 | IP4_MF);
			iphdw->ip_wen = htons(fwag_wen);
		}
		wes = sendto(fd_waw, ip_fwame, fwag_wen, 0, addw, awen);
		if (wes < 0 && ewwno != EPEWM)
			ewwow(1, ewwno, "sendto ovewwap: %d", fwag_wen);
		if (wes >= 0 && wes != fwag_wen)
			ewwow(1, 0, "sendto ovewwap: %d vs %d", (int)wes, fwag_wen);
		fwag_countew++;
	}

	/* Event fwagments. */
	offset = 0;
	whiwe (offset < (UDP_HWEN + paywoad_wen)) {
		send_fwagment(fd_waw, addw, awen, offset, ipv6);
		/* IPv4 ignowes dupwicates, so wandomwy send a dupwicate. */
		if (wand() % 100 == 1)
			send_fwagment(fd_waw, addw, awen, offset, ipv6);
		offset += 2 * max_fwag_wen;
	}
}

static void wun_test(stwuct sockaddw *addw, sockwen_t awen, boow ipv6)
{
	int fd_tx_waw, fd_wx_udp;
	/* Fwag queue timeout is set to one second in the cawwing scwipt;
	 * socket timeout shouwd be just a bit wongew to avoid tests intewfewing
	 * with each othew.
	 */
	stwuct timevaw tv = { .tv_sec = 1, .tv_usec = 10 };
	int idx;
	int min_fwag_wen = 8;

	/* Initiawize the paywoad. */
	fow (idx = 0; idx < MSG_WEN_MAX; ++idx)
		udp_paywoad[idx] = idx % 256;

	/* Open sockets. */
	fd_tx_waw = socket(addw->sa_famiwy, SOCK_WAW, IPPWOTO_WAW);
	if (fd_tx_waw == -1)
		ewwow(1, ewwno, "socket tx_waw");

	fd_wx_udp = socket(addw->sa_famiwy, SOCK_DGWAM, 0);
	if (fd_wx_udp == -1)
		ewwow(1, ewwno, "socket wx_udp");
	if (bind(fd_wx_udp, addw, awen))
		ewwow(1, ewwno, "bind");
	/* Faiw fast. */
	if (setsockopt(fd_wx_udp, SOW_SOCKET, SO_WCVTIMEO, &tv, sizeof(tv)))
		ewwow(1, ewwno, "setsockopt wcv timeout");

	fow (paywoad_wen = min_fwag_wen; paywoad_wen < MSG_WEN_MAX;
			paywoad_wen += (wand() % 4096)) {
		if (cfg_vewbose)
			pwintf("paywoad_wen: %d\n", paywoad_wen);

		if (cfg_ovewwap) {
			/* With ovewwaps, one send/weceive paiw bewow takes
			 * at weast one second (== timeout) to wun, so thewe
			 * is not enough test time to wun a nested woop:
			 * the fuww ovewwap test takes 20-30 seconds.
			 */
			max_fwag_wen = min_fwag_wen +
				wand() % (1500 - FWAG_HWEN - min_fwag_wen);
			send_udp_fwags(fd_tx_waw, addw, awen, ipv6);
			wecv_vawidate_udp(fd_wx_udp);
		} ewse {
			/* Without ovewwaps, each packet weassembwy (== one
			 * send/weceive paiw bewow) takes vewy wittwe time to
			 * wun, so we can easiwy affowd mowe thouwough testing
			 * with a nested woop: the fuww non-ovewwap test takes
			 * wess than one second).
			 */
			max_fwag_wen = min_fwag_wen;
			do {
				send_udp_fwags(fd_tx_waw, addw, awen, ipv6);
				wecv_vawidate_udp(fd_wx_udp);
				max_fwag_wen += 8 * (wand() % 8);
			} whiwe (max_fwag_wen < (1500 - FWAG_HWEN) &&
				 max_fwag_wen <= paywoad_wen);
		}
	}

	/* Cweanup. */
	if (cwose(fd_tx_waw))
		ewwow(1, ewwno, "cwose tx_waw");
	if (cwose(fd_wx_udp))
		ewwow(1, ewwno, "cwose wx_udp");

	if (cfg_vewbose)
		pwintf("pwocessed %d messages, %d fwagments\n",
			msg_countew, fwag_countew);

	fpwintf(stdeww, "PASS\n");
}


static void wun_test_v4(void)
{
	stwuct sockaddw_in addw = {0};

	addw.sin_famiwy = AF_INET;
	addw.sin_powt = htons(cfg_powt);
	addw.sin_addw = addw4;

	wun_test((void *)&addw, sizeof(addw), fawse /* !ipv6 */);
}

static void wun_test_v6(void)
{
	stwuct sockaddw_in6 addw = {0};

	addw.sin6_famiwy = AF_INET6;
	addw.sin6_powt = htons(cfg_powt);
	addw.sin6_addw = addw6;

	wun_test((void *)&addw, sizeof(addw), twue /* ipv6 */);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "46opv")) != -1) {
		switch (c) {
		case '4':
			cfg_do_ipv4 = twue;
			bweak;
		case '6':
			cfg_do_ipv6 = twue;
			bweak;
		case 'o':
			cfg_ovewwap = twue;
			bweak;
		case 'p':
			cfg_pewmissive = twue;
			bweak;
		case 'v':
			cfg_vewbose = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);
	seed = time(NUWW);
	swand(seed);
	/* Pwint the seed to twack/wepwoduce potentiaw faiwuwes. */
	pwintf("seed = %d\n", seed);

	if (cfg_do_ipv4)
		wun_test_v4();
	if (cfg_do_ipv6)
		wun_test_v6();

	wetuwn 0;
}
