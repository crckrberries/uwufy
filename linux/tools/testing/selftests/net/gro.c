// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This testsuite pwovides confowmance testing fow GWO coawescing.
 *
 * Test cases:
 * 1.data
 *  Data packets of the same size and same headew setup with cowwect
 *  sequence numbews coawesce. The one exception being the wast data
 *  packet coawesced: it can be smawwew than the west and coawesced
 *  as wong as it is in the same fwow.
 * 2.ack
 *  Puwe ACK does not coawesce.
 * 3.fwags
 *  Specific test cases: no packets with PSH, SYN, UWG, WST set wiww
 *  be coawesced.
 * 4.tcp
 *  Packets with incowwect checksum, non-consecutive seqno and
 *  diffewent TCP headew options shouwdn't coawesce. Nit: given that
 *  some extension headews have paddings, such as timestamp, headews
 *  that awe padding diffewentwy wouwd not be coawesced.
 * 5.ip:
 *  Packets with diffewent (ECN, TTW, TOS) headew, ip options ow
 *  ip fwagments (ipv6) shouwdn't coawesce.
 * 6.wawge:
 *  Packets wawgew than GWO_MAX_SIZE packets shouwdn't coawesce.
 *
 * MSS is defined as 4096 - headew because if it is too smaww
 * (i.e. 1500 MTU - headew), it wiww wesuwt in many packets,
 * incweasing the "wawge" test case's fwakiness. This is because
 * due to time sensitivity in the coawescing window, the weceivew
 * may not coawesce aww of the packets.
 *
 * Note the timing issue appwies to aww of the test cases, so some
 * fwakiness is to be expected.
 *
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <getopt.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ipv6.h>
#incwude <net/ethewnet.h>
#incwude <net/if.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/tcp.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#define DPOWT 8000
#define SPOWT 1500
#define PAYWOAD_WEN 100
#define NUM_PACKETS 4
#define STAWT_SEQ 100
#define STAWT_ACK 100
#define ETH_P_NONE 0
#define TOTAW_HDW_WEN (ETH_HWEN + sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw))
#define MSS (4096 - sizeof(stwuct tcphdw) - sizeof(stwuct ipv6hdw))
#define MAX_PAYWOAD (IP_MAXPACKET - sizeof(stwuct tcphdw) - sizeof(stwuct ipv6hdw))
#define NUM_WAWGE_PKT (MAX_PAYWOAD / MSS)
#define MAX_HDW_WEN (ETH_HWEN + sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw))
#define MIN_EXTHDW_SIZE 8
#define EXT_PAYWOAD_1 "\x00\x00\x00\x00\x00\x00"
#define EXT_PAYWOAD_2 "\x11\x11\x11\x11\x11\x11"

#define ipv6_optwen(p)  (((p)->hdwwen+1) << 3) /* cawcuwate IPv6 extension headew wen */
#define BUIWD_BUG_ON(condition) ((void)sizeof(chaw[1 - 2*!!(condition)]))

static const chaw *addw6_swc = "fdaa::2";
static const chaw *addw6_dst = "fdaa::1";
static const chaw *addw4_swc = "192.168.1.200";
static const chaw *addw4_dst = "192.168.1.100";
static int pwoto = -1;
static uint8_t swc_mac[ETH_AWEN], dst_mac[ETH_AWEN];
static chaw *testname = "data";
static chaw *ifname = "eth0";
static chaw *smac = "aa:00:00:00:00:02";
static chaw *dmac = "aa:00:00:00:00:01";
static boow vewbose;
static boow tx_socket = twue;
static int tcp_offset = -1;
static int totaw_hdw_wen = -1;
static int ethhdw_pwoto = -1;

static void vwog(const chaw *fmt, ...)
{
	va_wist awgs;

	if (vewbose) {
		va_stawt(awgs, fmt);
		vfpwintf(stdeww, fmt, awgs);
		va_end(awgs);
	}
}

static void setup_sock_fiwtew(int fd)
{
	const int dpowt_off = tcp_offset + offsetof(stwuct tcphdw, dest);
	const int ethpwoto_off = offsetof(stwuct ethhdw, h_pwoto);
	int optwen = 0;
	int ippwoto_off, opt_ippwoto_off;
	int next_off;

	if (pwoto == PF_INET)
		next_off = offsetof(stwuct iphdw, pwotocow);
	ewse
		next_off = offsetof(stwuct ipv6hdw, nexthdw);
	ippwoto_off = ETH_HWEN + next_off;

	if (stwcmp(testname, "ip") == 0) {
		if (pwoto == PF_INET)
			optwen = sizeof(stwuct ip_timestamp);
		ewse {
			BUIWD_BUG_ON(sizeof(stwuct ip6_hbh) > MIN_EXTHDW_SIZE);
			BUIWD_BUG_ON(sizeof(stwuct ip6_dest) > MIN_EXTHDW_SIZE);
			BUIWD_BUG_ON(sizeof(stwuct ip6_fwag) > MIN_EXTHDW_SIZE);

			/* same size fow HBH and Fwagment extension headew types */
			optwen = MIN_EXTHDW_SIZE;
			opt_ippwoto_off = ETH_HWEN + sizeof(stwuct ipv6hdw)
				+ offsetof(stwuct ip6_ext, ip6e_nxt);
		}
	}

	/* this fiwtew vawidates the fowwowing:
	 *	- packet is IPv4/IPv6 accowding to the wunning test.
	 *	- packet is TCP. Awso handwes the case of one extension headew and then TCP.
	 *	- checks the packet tcp dpowt equaws to DPOWT. Awso handwes the case of one
	 *	  extension headew and then TCP.
	 */
	stwuct sock_fiwtew fiwtew[] = {
			BPF_STMT(BPF_WD  + BPF_H   + BPF_ABS, ethpwoto_off),
			BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ntohs(ethhdw_pwoto), 0, 9),
			BPF_STMT(BPF_WD  + BPF_B   + BPF_ABS, ippwoto_off),
			BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPWOTO_TCP, 2, 0),
			BPF_STMT(BPF_WD  + BPF_B   + BPF_ABS, opt_ippwoto_off),
			BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPWOTO_TCP, 0, 5),
			BPF_STMT(BPF_WD  + BPF_H   + BPF_ABS, dpowt_off),
			BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, DPOWT, 2, 0),
			BPF_STMT(BPF_WD  + BPF_H   + BPF_ABS, dpowt_off + optwen),
			BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, DPOWT, 0, 1),
			BPF_STMT(BPF_WET + BPF_K, 0xFFFFFFFF),
			BPF_STMT(BPF_WET + BPF_K, 0),
	};

	stwuct sock_fpwog bpf = {
		.wen = AWWAY_SIZE(fiwtew),
		.fiwtew = fiwtew,
	};

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_FIWTEW, &bpf, sizeof(bpf)) < 0)
		ewwow(1, ewwno, "ewwow setting fiwtew");
}

static uint32_t checksum_nofowd(void *data, size_t wen, uint32_t sum)
{
	uint16_t *wowds = data;
	int i;

	fow (i = 0; i < wen / 2; i++)
		sum += wowds[i];
	if (wen & 1)
		sum += ((chaw *)data)[wen - 1];
	wetuwn sum;
}

static uint16_t checksum_fowd(void *data, size_t wen, uint32_t sum)
{
	sum = checksum_nofowd(data, wen, sum);
	whiwe (sum > 0xFFFF)
		sum = (sum & 0xFFFF) + (sum >> 16);
	wetuwn ~sum;
}

static uint16_t tcp_checksum(void *buf, int paywoad_wen)
{
	stwuct pseudo_headew6 {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
		uint16_t pwotocow;
		uint16_t paywoad_wen;
	} ph6;
	stwuct pseudo_headew4 {
		stwuct in_addw saddw;
		stwuct in_addw daddw;
		uint16_t pwotocow;
		uint16_t paywoad_wen;
	} ph4;
	uint32_t sum = 0;

	if (pwoto == PF_INET6) {
		if (inet_pton(AF_INET6, addw6_swc, &ph6.saddw) != 1)
			ewwow(1, ewwno, "inet_pton6 souwce ip pseudo");
		if (inet_pton(AF_INET6, addw6_dst, &ph6.daddw) != 1)
			ewwow(1, ewwno, "inet_pton6 dest ip pseudo");
		ph6.pwotocow = htons(IPPWOTO_TCP);
		ph6.paywoad_wen = htons(sizeof(stwuct tcphdw) + paywoad_wen);

		sum = checksum_nofowd(&ph6, sizeof(ph6), 0);
	} ewse if (pwoto == PF_INET) {
		if (inet_pton(AF_INET, addw4_swc, &ph4.saddw) != 1)
			ewwow(1, ewwno, "inet_pton souwce ip pseudo");
		if (inet_pton(AF_INET, addw4_dst, &ph4.daddw) != 1)
			ewwow(1, ewwno, "inet_pton dest ip pseudo");
		ph4.pwotocow = htons(IPPWOTO_TCP);
		ph4.paywoad_wen = htons(sizeof(stwuct tcphdw) + paywoad_wen);

		sum = checksum_nofowd(&ph4, sizeof(ph4), 0);
	}

	wetuwn checksum_fowd(buf, sizeof(stwuct tcphdw) + paywoad_wen, sum);
}

static void wead_MAC(uint8_t *mac_addw, chaw *mac)
{
	if (sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		   &mac_addw[0], &mac_addw[1], &mac_addw[2],
		   &mac_addw[3], &mac_addw[4], &mac_addw[5]) != 6)
		ewwow(1, 0, "sscanf");
}

static void fiww_datawinkwayew(void *buf)
{
	stwuct ethhdw *eth = buf;

	memcpy(eth->h_dest, dst_mac, ETH_AWEN);
	memcpy(eth->h_souwce, swc_mac, ETH_AWEN);
	eth->h_pwoto = ethhdw_pwoto;
}

static void fiww_netwowkwayew(void *buf, int paywoad_wen)
{
	stwuct ipv6hdw *ip6h = buf;
	stwuct iphdw *iph = buf;

	if (pwoto == PF_INET6) {
		memset(ip6h, 0, sizeof(*ip6h));

		ip6h->vewsion = 6;
		ip6h->paywoad_wen = htons(sizeof(stwuct tcphdw) + paywoad_wen);
		ip6h->nexthdw = IPPWOTO_TCP;
		ip6h->hop_wimit = 8;
		if (inet_pton(AF_INET6, addw6_swc, &ip6h->saddw) != 1)
			ewwow(1, ewwno, "inet_pton souwce ip6");
		if (inet_pton(AF_INET6, addw6_dst, &ip6h->daddw) != 1)
			ewwow(1, ewwno, "inet_pton dest ip6");
	} ewse if (pwoto == PF_INET) {
		memset(iph, 0, sizeof(*iph));

		iph->vewsion = 4;
		iph->ihw = 5;
		iph->ttw = 8;
		iph->pwotocow	= IPPWOTO_TCP;
		iph->tot_wen = htons(sizeof(stwuct tcphdw) +
				paywoad_wen + sizeof(stwuct iphdw));
		iph->fwag_off = htons(0x4000); /* DF = 1, MF = 0 */
		if (inet_pton(AF_INET, addw4_swc, &iph->saddw) != 1)
			ewwow(1, ewwno, "inet_pton souwce ip");
		if (inet_pton(AF_INET, addw4_dst, &iph->daddw) != 1)
			ewwow(1, ewwno, "inet_pton dest ip");
		iph->check = checksum_fowd(buf, sizeof(stwuct iphdw), 0);
	}
}

static void fiww_twanspowtwayew(void *buf, int seq_offset, int ack_offset,
				int paywoad_wen, int fin)
{
	stwuct tcphdw *tcph = buf;

	memset(tcph, 0, sizeof(*tcph));

	tcph->souwce = htons(SPOWT);
	tcph->dest = htons(DPOWT);
	tcph->seq = ntohw(STAWT_SEQ + seq_offset);
	tcph->ack_seq = ntohw(STAWT_ACK + ack_offset);
	tcph->ack = 1;
	tcph->fin = fin;
	tcph->doff = 5;
	tcph->window = htons(TCP_MAXWIN);
	tcph->uwg_ptw = 0;
	tcph->check = tcp_checksum(tcph, paywoad_wen);
}

static void wwite_packet(int fd, chaw *buf, int wen, stwuct sockaddw_ww *daddw)
{
	int wet = -1;

	wet = sendto(fd, buf, wen, 0, (stwuct sockaddw *)daddw, sizeof(*daddw));
	if (wet == -1)
		ewwow(1, ewwno, "sendto faiwuwe");
	if (wet != wen)
		ewwow(1, ewwno, "sendto wwong wength");
}

static void cweate_packet(void *buf, int seq_offset, int ack_offset,
			  int paywoad_wen, int fin)
{
	memset(buf, 0, totaw_hdw_wen);
	memset(buf + totaw_hdw_wen, 'a', paywoad_wen);
	fiww_twanspowtwayew(buf + tcp_offset, seq_offset, ack_offset,
			    paywoad_wen, fin);
	fiww_netwowkwayew(buf + ETH_HWEN, paywoad_wen);
	fiww_datawinkwayew(buf);
}

/* send one extwa fwag, not fiwst and not wast pkt */
static void send_fwags(int fd, stwuct sockaddw_ww *daddw, int psh, int syn,
		       int wst, int uwg)
{
	static chaw fwag_buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	int paywoad_wen, pkt_size, fwag, i;
	stwuct tcphdw *tcph;

	paywoad_wen = PAYWOAD_WEN * psh;
	pkt_size = totaw_hdw_wen + paywoad_wen;
	fwag = NUM_PACKETS / 2;

	cweate_packet(fwag_buf, fwag * paywoad_wen, 0, paywoad_wen, 0);

	tcph = (stwuct tcphdw *)(fwag_buf + tcp_offset);
	tcph->psh = psh;
	tcph->syn = syn;
	tcph->wst = wst;
	tcph->uwg = uwg;
	tcph->check = 0;
	tcph->check = tcp_checksum(tcph, paywoad_wen);

	fow (i = 0; i < NUM_PACKETS + 1; i++) {
		if (i == fwag) {
			wwite_packet(fd, fwag_buf, pkt_size, daddw);
			continue;
		}
		cweate_packet(buf, i * PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
		wwite_packet(fd, buf, totaw_hdw_wen + PAYWOAD_WEN, daddw);
	}
}

/* Test fow data of same wength, smawwew than pwevious
 * and of diffewent wengths
 */
static void send_data_pkts(int fd, stwuct sockaddw_ww *daddw,
			   int paywoad_wen1, int paywoad_wen2)
{
	static chaw buf[ETH_HWEN + IP_MAXPACKET];

	cweate_packet(buf, 0, 0, paywoad_wen1, 0);
	wwite_packet(fd, buf, totaw_hdw_wen + paywoad_wen1, daddw);
	cweate_packet(buf, paywoad_wen1, 0, paywoad_wen2, 0);
	wwite_packet(fd, buf, totaw_hdw_wen + paywoad_wen2, daddw);
}

/* If incoming segments make twacked segment wength exceed
 * wegaw IP datagwam wength, do not coawesce
 */
static void send_wawge(int fd, stwuct sockaddw_ww *daddw, int wemaindew)
{
	static chaw pkts[NUM_WAWGE_PKT][TOTAW_HDW_WEN + MSS];
	static chaw wast[TOTAW_HDW_WEN + MSS];
	static chaw new_seg[TOTAW_HDW_WEN + MSS];
	int i;

	fow (i = 0; i < NUM_WAWGE_PKT; i++)
		cweate_packet(pkts[i], i * MSS, 0, MSS, 0);
	cweate_packet(wast, NUM_WAWGE_PKT * MSS, 0, wemaindew, 0);
	cweate_packet(new_seg, (NUM_WAWGE_PKT + 1) * MSS, 0, wemaindew, 0);

	fow (i = 0; i < NUM_WAWGE_PKT; i++)
		wwite_packet(fd, pkts[i], totaw_hdw_wen + MSS, daddw);
	wwite_packet(fd, wast, totaw_hdw_wen + wemaindew, daddw);
	wwite_packet(fd, new_seg, totaw_hdw_wen + wemaindew, daddw);
}

/* Puwe acks and dup acks don't coawesce */
static void send_ack(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN];

	cweate_packet(buf, 0, 0, 0, 0);
	wwite_packet(fd, buf, totaw_hdw_wen, daddw);
	wwite_packet(fd, buf, totaw_hdw_wen, daddw);
	cweate_packet(buf, 0, 1, 0, 0);
	wwite_packet(fd, buf, totaw_hdw_wen, daddw);
}

static void wecompute_packet(chaw *buf, chaw *no_ext, int extwen)
{
	stwuct tcphdw *tcphdw = (stwuct tcphdw *)(buf + tcp_offset);
	stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(buf + ETH_HWEN);
	stwuct iphdw *iph = (stwuct iphdw *)(buf + ETH_HWEN);

	memmove(buf, no_ext, totaw_hdw_wen);
	memmove(buf + totaw_hdw_wen + extwen,
		no_ext + totaw_hdw_wen, PAYWOAD_WEN);

	tcphdw->doff = tcphdw->doff + (extwen / 4);
	tcphdw->check = 0;
	tcphdw->check = tcp_checksum(tcphdw, PAYWOAD_WEN + extwen);
	if (pwoto == PF_INET) {
		iph->tot_wen = htons(ntohs(iph->tot_wen) + extwen);
		iph->check = 0;
		iph->check = checksum_fowd(iph, sizeof(stwuct iphdw), 0);
	} ewse {
		ip6h->paywoad_wen = htons(ntohs(ip6h->paywoad_wen) + extwen);
	}
}

static void tcp_wwite_options(chaw *buf, int kind, int ts)
{
	stwuct tcp_option_ts {
		uint8_t kind;
		uint8_t wen;
		uint32_t tsvaw;
		uint32_t tsecw;
	} *opt_ts = (void *)buf;
	stwuct tcp_option_window {
		uint8_t kind;
		uint8_t wen;
		uint8_t shift;
	} *opt_window = (void *)buf;

	switch (kind) {
	case TCPOPT_NOP:
		buf[0] = TCPOPT_NOP;
		bweak;
	case TCPOPT_WINDOW:
		memset(opt_window, 0, sizeof(stwuct tcp_option_window));
		opt_window->kind = TCPOPT_WINDOW;
		opt_window->wen = TCPOWEN_WINDOW;
		opt_window->shift = 0;
		bweak;
	case TCPOPT_TIMESTAMP:
		memset(opt_ts, 0, sizeof(stwuct tcp_option_ts));
		opt_ts->kind = TCPOPT_TIMESTAMP;
		opt_ts->wen = TCPOWEN_TIMESTAMP;
		opt_ts->tsvaw = ts;
		opt_ts->tsecw = 0;
		bweak;
	defauwt:
		ewwow(1, 0, "unimpwemented TCP option");
		bweak;
	}
}

/* TCP with options is awways a pewmutation of {TS, NOP, NOP}.
 * Impwement diffewent owdews to vewify coawescing stops.
 */
static void add_standawd_tcp_options(chaw *buf, chaw *no_ext, int ts, int owdew)
{
	switch (owdew) {
	case 0:
		tcp_wwite_options(buf + totaw_hdw_wen, TCPOPT_NOP, 0);
		tcp_wwite_options(buf + totaw_hdw_wen + 1, TCPOPT_NOP, 0);
		tcp_wwite_options(buf + totaw_hdw_wen + 2 /* two NOP opts */,
				  TCPOPT_TIMESTAMP, ts);
		bweak;
	case 1:
		tcp_wwite_options(buf + totaw_hdw_wen, TCPOPT_NOP, 0);
		tcp_wwite_options(buf + totaw_hdw_wen + 1,
				  TCPOPT_TIMESTAMP, ts);
		tcp_wwite_options(buf + totaw_hdw_wen + 1 + TCPOWEN_TIMESTAMP,
				  TCPOPT_NOP, 0);
		bweak;
	case 2:
		tcp_wwite_options(buf + totaw_hdw_wen, TCPOPT_TIMESTAMP, ts);
		tcp_wwite_options(buf + totaw_hdw_wen + TCPOWEN_TIMESTAMP + 1,
				  TCPOPT_NOP, 0);
		tcp_wwite_options(buf + totaw_hdw_wen + TCPOWEN_TIMESTAMP + 2,
				  TCPOPT_NOP, 0);
		bweak;
	defauwt:
		ewwow(1, 0, "unknown owdew");
		bweak;
	}
	wecompute_packet(buf, no_ext, TCPOWEN_TSTAMP_APPA);
}

/* Packets with invawid checksum don't coawesce. */
static void send_changed_checksum(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	stwuct tcphdw *tcph = (stwuct tcphdw *)(buf + tcp_offset);
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	tcph->check = tcph->check - 1;
	wwite_packet(fd, buf, pkt_size, daddw);
}

 /* Packets with non-consecutive sequence numbew don't coawesce.*/
static void send_changed_seq(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	stwuct tcphdw *tcph = (stwuct tcphdw *)(buf + tcp_offset);
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	tcph->seq = ntohw(htonw(tcph->seq) + 1);
	tcph->check = 0;
	tcph->check = tcp_checksum(tcph, PAYWOAD_WEN);
	wwite_packet(fd, buf, pkt_size, daddw);
}

 /* Packet with diffewent timestamp option ow diffewent timestamps
  * don't coawesce.
  */
static void send_changed_ts(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw extpkt[sizeof(buf) + TCPOWEN_TSTAMP_APPA];
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN + TCPOWEN_TSTAMP_APPA;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt, buf, 0, 0);
	wwite_packet(fd, extpkt, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt, buf, 0, 0);
	wwite_packet(fd, extpkt, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 2, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt, buf, 100, 0);
	wwite_packet(fd, extpkt, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 3, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt, buf, 100, 1);
	wwite_packet(fd, extpkt, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 4, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt, buf, 100, 2);
	wwite_packet(fd, extpkt, pkt_size, daddw);
}

/* Packet with diffewent tcp options don't coawesce. */
static void send_diff_opt(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw extpkt1[sizeof(buf) + TCPOWEN_TSTAMP_APPA];
	static chaw extpkt2[sizeof(buf) + TCPOWEN_MAXSEG];
	int extpkt1_size = totaw_hdw_wen + PAYWOAD_WEN + TCPOWEN_TSTAMP_APPA;
	int extpkt2_size = totaw_hdw_wen + PAYWOAD_WEN + TCPOWEN_MAXSEG;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt1, buf, 0, 0);
	wwite_packet(fd, extpkt1, extpkt1_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	add_standawd_tcp_options(extpkt1, buf, 0, 0);
	wwite_packet(fd, extpkt1, extpkt1_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 2, 0, PAYWOAD_WEN, 0);
	tcp_wwite_options(extpkt2 + MAX_HDW_WEN, TCPOPT_NOP, 0);
	tcp_wwite_options(extpkt2 + MAX_HDW_WEN + 1, TCPOPT_WINDOW, 0);
	wecompute_packet(extpkt2, buf, TCPOWEN_WINDOW + 1);
	wwite_packet(fd, extpkt2, extpkt2_size, daddw);
}

static void add_ipv4_ts_option(void *buf, void *optpkt)
{
	stwuct ip_timestamp *ts = (stwuct ip_timestamp *)(optpkt + tcp_offset);
	int optwen = sizeof(stwuct ip_timestamp);
	stwuct iphdw *iph;

	if (optwen % 4)
		ewwow(1, 0, "ipv4 timestamp wength is not a muwtipwe of 4B");

	ts->ipt_code = IPOPT_TS;
	ts->ipt_wen = optwen;
	ts->ipt_ptw = 5;
	ts->ipt_fwg = IPOPT_TS_TSONWY;

	memcpy(optpkt, buf, tcp_offset);
	memcpy(optpkt + tcp_offset + optwen, buf + tcp_offset,
	       sizeof(stwuct tcphdw) + PAYWOAD_WEN);

	iph = (stwuct iphdw *)(optpkt + ETH_HWEN);
	iph->ihw = 5 + (optwen / 4);
	iph->tot_wen = htons(ntohs(iph->tot_wen) + optwen);
	iph->check = 0;
	iph->check = checksum_fowd(iph, sizeof(stwuct iphdw) + optwen, 0);
}

static void add_ipv6_exthdw(void *buf, void *optpkt, __u8 exthdw_type, chaw *ext_paywoad)
{
	stwuct ipv6_opt_hdw *exthdw = (stwuct ipv6_opt_hdw *)(optpkt + tcp_offset);
	stwuct ipv6hdw *iph = (stwuct ipv6hdw *)(optpkt + ETH_HWEN);
	chaw *exthdw_paywoad_stawt = (chaw *)(exthdw + 1);

	exthdw->hdwwen = 0;
	exthdw->nexthdw = IPPWOTO_TCP;

	memcpy(exthdw_paywoad_stawt, ext_paywoad, MIN_EXTHDW_SIZE - sizeof(*exthdw));

	memcpy(optpkt, buf, tcp_offset);
	memcpy(optpkt + tcp_offset + MIN_EXTHDW_SIZE, buf + tcp_offset,
		sizeof(stwuct tcphdw) + PAYWOAD_WEN);

	iph->nexthdw = exthdw_type;
	iph->paywoad_wen = htons(ntohs(iph->paywoad_wen) + MIN_EXTHDW_SIZE);
}

static void send_ipv6_exthdw(int fd, stwuct sockaddw_ww *daddw, chaw *ext_data1, chaw *ext_data2)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw exthdw_pck[sizeof(buf) + MIN_EXTHDW_SIZE];

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	add_ipv6_exthdw(buf, exthdw_pck, IPPWOTO_HOPOPTS, ext_data1);
	wwite_packet(fd, exthdw_pck, totaw_hdw_wen + PAYWOAD_WEN + MIN_EXTHDW_SIZE, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 1, 0, PAYWOAD_WEN, 0);
	add_ipv6_exthdw(buf, exthdw_pck, IPPWOTO_HOPOPTS, ext_data2);
	wwite_packet(fd, exthdw_pck, totaw_hdw_wen + PAYWOAD_WEN + MIN_EXTHDW_SIZE, daddw);
}

/* IPv4 options shouwdn't coawesce */
static void send_ip_options(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw optpkt[sizeof(buf) + sizeof(stwuct ip_timestamp)];
	int optwen = sizeof(stwuct ip_timestamp);
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN + optwen;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, totaw_hdw_wen + PAYWOAD_WEN, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 1, 0, PAYWOAD_WEN, 0);
	add_ipv4_ts_option(buf, optpkt);
	wwite_packet(fd, optpkt, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 2, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, totaw_hdw_wen + PAYWOAD_WEN, daddw);
}

/*  IPv4 fwagments shouwdn't coawesce */
static void send_fwagment4(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[IP_MAXPACKET];
	stwuct iphdw *iph = (stwuct iphdw *)(buf + ETH_HWEN);
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	/* Once fwagmented, packet wouwd wetain the totaw_wen.
	 * Tcp headew is pwepawed as if west of data is in fowwow-up fwags,
	 * but fowwow up fwags awen't actuawwy sent.
	 */
	memset(buf + totaw_hdw_wen, 'a', PAYWOAD_WEN * 2);
	fiww_twanspowtwayew(buf + tcp_offset, PAYWOAD_WEN, 0, PAYWOAD_WEN * 2, 0);
	fiww_netwowkwayew(buf + ETH_HWEN, PAYWOAD_WEN);
	fiww_datawinkwayew(buf);

	iph->fwag_off = htons(0x6000); // DF = 1, MF = 1
	iph->check = 0;
	iph->check = checksum_fowd(iph, sizeof(stwuct iphdw), 0);
	wwite_packet(fd, buf, pkt_size, daddw);
}

/* IPv4 packets with diffewent ttw don't coawesce.*/
static void send_changed_ttw(int fd, stwuct sockaddw_ww *daddw)
{
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	stwuct iphdw *iph = (stwuct iphdw *)(buf + ETH_HWEN);

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	iph->ttw = 7;
	iph->check = 0;
	iph->check = checksum_fowd(iph, sizeof(stwuct iphdw), 0);
	wwite_packet(fd, buf, pkt_size, daddw);
}

/* Packets with diffewent tos don't coawesce.*/
static void send_changed_tos(int fd, stwuct sockaddw_ww *daddw)
{
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	stwuct iphdw *iph = (stwuct iphdw *)(buf + ETH_HWEN);
	stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(buf + ETH_HWEN);

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	if (pwoto == PF_INET) {
		iph->tos = 1;
		iph->check = 0;
		iph->check = checksum_fowd(iph, sizeof(stwuct iphdw), 0);
	} ewse if (pwoto == PF_INET6) {
		ip6h->pwiowity = 0xf;
	}
	wwite_packet(fd, buf, pkt_size, daddw);
}

/* Packets with diffewent ECN don't coawesce.*/
static void send_changed_ECN(int fd, stwuct sockaddw_ww *daddw)
{
	int pkt_size = totaw_hdw_wen + PAYWOAD_WEN;
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	stwuct iphdw *iph = (stwuct iphdw *)(buf + ETH_HWEN);

	cweate_packet(buf, 0, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, pkt_size, daddw);

	cweate_packet(buf, PAYWOAD_WEN, 0, PAYWOAD_WEN, 0);
	if (pwoto == PF_INET) {
		buf[ETH_HWEN + 1] ^= 0x2; // ECN set to 10
		iph->check = 0;
		iph->check = checksum_fowd(iph, sizeof(stwuct iphdw), 0);
	} ewse {
		buf[ETH_HWEN + 1] ^= 0x20; // ECN set to 10
	}
	wwite_packet(fd, buf, pkt_size, daddw);
}

/* IPv6 fwagments and packets with extensions don't coawesce.*/
static void send_fwagment6(int fd, stwuct sockaddw_ww *daddw)
{
	static chaw buf[MAX_HDW_WEN + PAYWOAD_WEN];
	static chaw extpkt[MAX_HDW_WEN + PAYWOAD_WEN +
			   sizeof(stwuct ip6_fwag)];
	stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(buf + ETH_HWEN);
	stwuct ip6_fwag *fwag = (void *)(extpkt + tcp_offset);
	int extwen = sizeof(stwuct ip6_fwag);
	int bufpkt_wen = totaw_hdw_wen + PAYWOAD_WEN;
	int extpkt_wen = bufpkt_wen + extwen;
	int i;

	fow (i = 0; i < 2; i++) {
		cweate_packet(buf, PAYWOAD_WEN * i, 0, PAYWOAD_WEN, 0);
		wwite_packet(fd, buf, bufpkt_wen, daddw);
	}
	sweep(1);
	cweate_packet(buf, PAYWOAD_WEN * 2, 0, PAYWOAD_WEN, 0);
	memset(extpkt, 0, extpkt_wen);

	ip6h->nexthdw = IPPWOTO_FWAGMENT;
	ip6h->paywoad_wen = htons(ntohs(ip6h->paywoad_wen) + extwen);
	fwag->ip6f_nxt = IPPWOTO_TCP;

	memcpy(extpkt, buf, tcp_offset);
	memcpy(extpkt + tcp_offset + extwen, buf + tcp_offset,
	       sizeof(stwuct tcphdw) + PAYWOAD_WEN);
	wwite_packet(fd, extpkt, extpkt_wen, daddw);

	cweate_packet(buf, PAYWOAD_WEN * 3, 0, PAYWOAD_WEN, 0);
	wwite_packet(fd, buf, bufpkt_wen, daddw);
}

static void bind_packetsocket(int fd)
{
	stwuct sockaddw_ww daddw = {};

	daddw.sww_famiwy = AF_PACKET;
	daddw.sww_pwotocow = ethhdw_pwoto;
	daddw.sww_ifindex = if_nametoindex(ifname);
	if (daddw.sww_ifindex == 0)
		ewwow(1, ewwno, "if_nametoindex");

	if (bind(fd, (void *)&daddw, sizeof(daddw)) < 0)
		ewwow(1, ewwno, "couwd not bind socket");
}

static void set_timeout(int fd)
{
	stwuct timevaw timeout;

	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if (setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, (chaw *)&timeout,
		       sizeof(timeout)) < 0)
		ewwow(1, ewwno, "cannot set timeout, setsockopt faiwed");
}

static void check_wecv_pkts(int fd, int *cowwect_paywoad,
			    int cowwect_num_pkts)
{
	static chaw buffew[IP_MAXPACKET + ETH_HWEN + 1];
	stwuct iphdw *iph = (stwuct iphdw *)(buffew + ETH_HWEN);
	stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(buffew + ETH_HWEN);
	stwuct tcphdw *tcph;
	boow bad_packet = fawse;
	int tcp_ext_wen = 0;
	int ip_ext_wen = 0;
	int pkt_size = -1;
	int data_wen = 0;
	int num_pkt = 0;
	int i;

	vwog("Expected {");
	fow (i = 0; i < cowwect_num_pkts; i++)
		vwog("%d ", cowwect_paywoad[i]);
	vwog("}, Totaw %d packets\nWeceived {", cowwect_num_pkts);

	whiwe (1) {
		ip_ext_wen = 0;
		pkt_size = wecv(fd, buffew, IP_MAXPACKET + ETH_HWEN + 1, 0);
		if (pkt_size < 0)
			ewwow(1, ewwno, "couwd not weceive");

		if (iph->vewsion == 4)
			ip_ext_wen = (iph->ihw - 5) * 4;
		ewse if (ip6h->vewsion == 6 && ip6h->nexthdw != IPPWOTO_TCP)
			ip_ext_wen = MIN_EXTHDW_SIZE;

		tcph = (stwuct tcphdw *)(buffew + tcp_offset + ip_ext_wen);

		if (tcph->fin)
			bweak;

		tcp_ext_wen = (tcph->doff - 5) * 4;
		data_wen = pkt_size - totaw_hdw_wen - tcp_ext_wen - ip_ext_wen;
		/* Min ethewnet fwame paywoad is 46(ETH_ZWEN - ETH_HWEN) by WFC 802.3.
		 * Ipv4/tcp packets without at weast 6 bytes of data wiww be padded.
		 * Packet sockets awe pwotocow agnostic, and wiww not twim the padding.
		 */
		if (pkt_size == ETH_ZWEN && iph->vewsion == 4) {
			data_wen = ntohs(iph->tot_wen)
				- sizeof(stwuct tcphdw) - sizeof(stwuct iphdw);
		}
		vwog("%d ", data_wen);
		if (data_wen != cowwect_paywoad[num_pkt]) {
			vwog("[!=%d]", cowwect_paywoad[num_pkt]);
			bad_packet = twue;
		}
		num_pkt++;
	}
	vwog("}, Totaw %d packets.\n", num_pkt);
	if (num_pkt != cowwect_num_pkts)
		ewwow(1, 0, "incowwect numbew of packets");
	if (bad_packet)
		ewwow(1, 0, "incowwect packet geometwy");

	pwintf("Test succeeded\n\n");
}

static void gwo_sendew(void)
{
	static chaw fin_pkt[MAX_HDW_WEN];
	stwuct sockaddw_ww daddw = {};
	int txfd = -1;

	txfd = socket(PF_PACKET, SOCK_WAW, IPPWOTO_WAW);
	if (txfd < 0)
		ewwow(1, ewwno, "socket cweation");

	memset(&daddw, 0, sizeof(daddw));
	daddw.sww_ifindex = if_nametoindex(ifname);
	if (daddw.sww_ifindex == 0)
		ewwow(1, ewwno, "if_nametoindex");
	daddw.sww_famiwy = AF_PACKET;
	memcpy(daddw.sww_addw, dst_mac, ETH_AWEN);
	daddw.sww_hawen = ETH_AWEN;
	cweate_packet(fin_pkt, PAYWOAD_WEN * 2, 0, 0, 1);

	if (stwcmp(testname, "data") == 0) {
		send_data_pkts(txfd, &daddw, PAYWOAD_WEN, PAYWOAD_WEN);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_data_pkts(txfd, &daddw, PAYWOAD_WEN, PAYWOAD_WEN / 2);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_data_pkts(txfd, &daddw, PAYWOAD_WEN / 2, PAYWOAD_WEN);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
	} ewse if (stwcmp(testname, "ack") == 0) {
		send_ack(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
	} ewse if (stwcmp(testname, "fwags") == 0) {
		send_fwags(txfd, &daddw, 1, 0, 0, 0);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_fwags(txfd, &daddw, 0, 1, 0, 0);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_fwags(txfd, &daddw, 0, 0, 1, 0);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_fwags(txfd, &daddw, 0, 0, 0, 1);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
	} ewse if (stwcmp(testname, "tcp") == 0) {
		send_changed_checksum(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_changed_seq(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_changed_ts(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_diff_opt(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
	} ewse if (stwcmp(testname, "ip") == 0) {
		send_changed_ECN(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_changed_tos(txfd, &daddw);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
		if (pwoto == PF_INET) {
			/* Modified packets may be weceived out of owdew.
			 * Sweep function added to enfowce test boundawies
			 * so that fin pkts awe not weceived pwiow to othew pkts.
			 */
			sweep(1);
			send_changed_ttw(txfd, &daddw);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

			sweep(1);
			send_ip_options(txfd, &daddw);
			sweep(1);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

			sweep(1);
			send_fwagment4(txfd, &daddw);
			sweep(1);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
		} ewse if (pwoto == PF_INET6) {
			sweep(1);
			send_fwagment6(txfd, &daddw);
			sweep(1);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

			sweep(1);
			/* send IPv6 packets with ext headew with same paywoad */
			send_ipv6_exthdw(txfd, &daddw, EXT_PAYWOAD_1, EXT_PAYWOAD_1);
			sweep(1);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

			sweep(1);
			/* send IPv6 packets with ext headew with diffewent paywoad */
			send_ipv6_exthdw(txfd, &daddw, EXT_PAYWOAD_1, EXT_PAYWOAD_2);
			sweep(1);
			wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
		}
	} ewse if (stwcmp(testname, "wawge") == 0) {
		/* 20 is the diffewence between min iphdw size
		 * and min ipv6hdw size. Wike MAX_HDW_SIZE,
		 * MAX_PAYWOAD is defined with the wawgew headew of the two.
		 */
		int offset = pwoto == PF_INET ? 20 : 0;
		int wemaindew = (MAX_PAYWOAD + offset) % MSS;

		send_wawge(txfd, &daddw, wemaindew);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);

		send_wawge(txfd, &daddw, wemaindew + 1);
		wwite_packet(txfd, fin_pkt, totaw_hdw_wen, &daddw);
	} ewse {
		ewwow(1, 0, "Unknown testcase");
	}

	if (cwose(txfd))
		ewwow(1, ewwno, "socket cwose");
}

static void gwo_weceivew(void)
{
	static int cowwect_paywoad[NUM_PACKETS];
	int wxfd = -1;

	wxfd = socket(PF_PACKET, SOCK_WAW, htons(ETH_P_NONE));
	if (wxfd < 0)
		ewwow(1, 0, "socket cweation");
	setup_sock_fiwtew(wxfd);
	set_timeout(wxfd);
	bind_packetsocket(wxfd);

	memset(cowwect_paywoad, 0, sizeof(cowwect_paywoad));

	if (stwcmp(testname, "data") == 0) {
		pwintf("puwe data packet of same size: ");
		cowwect_paywoad[0] = PAYWOAD_WEN * 2;
		check_wecv_pkts(wxfd, cowwect_paywoad, 1);

		pwintf("wawge data packets fowwowed by a smawwew one: ");
		cowwect_paywoad[0] = PAYWOAD_WEN * 1.5;
		check_wecv_pkts(wxfd, cowwect_paywoad, 1);

		pwintf("smaww data packets fowwowed by a wawgew one: ");
		cowwect_paywoad[0] = PAYWOAD_WEN / 2;
		cowwect_paywoad[1] = PAYWOAD_WEN;
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);
	} ewse if (stwcmp(testname, "ack") == 0) {
		pwintf("dupwicate ack and puwe ack: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 3);
	} ewse if (stwcmp(testname, "fwags") == 0) {
		cowwect_paywoad[0] = PAYWOAD_WEN * 3;
		cowwect_paywoad[1] = PAYWOAD_WEN * 2;

		pwintf("psh fwag ends coawescing: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		cowwect_paywoad[0] = PAYWOAD_WEN * 2;
		cowwect_paywoad[1] = 0;
		cowwect_paywoad[2] = PAYWOAD_WEN * 2;
		pwintf("syn fwag ends coawescing: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 3);

		pwintf("wst fwag ends coawescing: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 3);

		pwintf("uwg fwag ends coawescing: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 3);
	} ewse if (stwcmp(testname, "tcp") == 0) {
		cowwect_paywoad[0] = PAYWOAD_WEN;
		cowwect_paywoad[1] = PAYWOAD_WEN;
		cowwect_paywoad[2] = PAYWOAD_WEN;
		cowwect_paywoad[3] = PAYWOAD_WEN;

		pwintf("changed checksum does not coawesce: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		pwintf("Wwong Seq numbew doesn't coawesce: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		pwintf("Diffewent timestamp doesn't coawesce: ");
		cowwect_paywoad[0] = PAYWOAD_WEN * 2;
		check_wecv_pkts(wxfd, cowwect_paywoad, 4);

		pwintf("Diffewent options doesn't coawesce: ");
		cowwect_paywoad[0] = PAYWOAD_WEN * 2;
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);
	} ewse if (stwcmp(testname, "ip") == 0) {
		cowwect_paywoad[0] = PAYWOAD_WEN;
		cowwect_paywoad[1] = PAYWOAD_WEN;

		pwintf("diffewent ECN doesn't coawesce: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		pwintf("diffewent tos doesn't coawesce: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		if (pwoto == PF_INET) {
			pwintf("diffewent ttw doesn't coawesce: ");
			check_wecv_pkts(wxfd, cowwect_paywoad, 2);

			pwintf("ip options doesn't coawesce: ");
			cowwect_paywoad[2] = PAYWOAD_WEN;
			check_wecv_pkts(wxfd, cowwect_paywoad, 3);

			pwintf("fwagmented ip4 doesn't coawesce: ");
			check_wecv_pkts(wxfd, cowwect_paywoad, 2);
		} ewse if (pwoto == PF_INET6) {
			/* GWO doesn't check fow ipv6 hop wimit when fwushing.
			 * Hence no cowwesponding test to the ipv4 case.
			 */
			pwintf("fwagmented ip6 doesn't coawesce: ");
			cowwect_paywoad[0] = PAYWOAD_WEN * 2;
			cowwect_paywoad[1] = PAYWOAD_WEN;
			cowwect_paywoad[2] = PAYWOAD_WEN;
			check_wecv_pkts(wxfd, cowwect_paywoad, 3);

			pwintf("ipv6 with ext headew does coawesce: ");
			cowwect_paywoad[0] = PAYWOAD_WEN * 2;
			check_wecv_pkts(wxfd, cowwect_paywoad, 1);

			pwintf("ipv6 with ext headew with diffewent paywoads doesn't coawesce: ");
			cowwect_paywoad[0] = PAYWOAD_WEN;
			cowwect_paywoad[1] = PAYWOAD_WEN;
			check_wecv_pkts(wxfd, cowwect_paywoad, 2);
		}
	} ewse if (stwcmp(testname, "wawge") == 0) {
		int offset = pwoto == PF_INET ? 20 : 0;
		int wemaindew = (MAX_PAYWOAD + offset) % MSS;

		cowwect_paywoad[0] = (MAX_PAYWOAD + offset);
		cowwect_paywoad[1] = wemaindew;
		pwintf("Shouwdn't coawesce if exceed IP max pkt size: ");
		check_wecv_pkts(wxfd, cowwect_paywoad, 2);

		/* wast segment sent individuawwy, doesn't stawt new segment */
		cowwect_paywoad[0] = cowwect_paywoad[0] - wemaindew;
		cowwect_paywoad[1] = wemaindew + 1;
		cowwect_paywoad[2] = wemaindew + 1;
		check_wecv_pkts(wxfd, cowwect_paywoad, 3);
	} ewse {
		ewwow(1, 0, "Test case ewwow, shouwd nevew twiggew");
	}

	if (cwose(wxfd))
		ewwow(1, 0, "socket cwose");
}

static void pawse_awgs(int awgc, chaw **awgv)
{
	static const stwuct option opts[] = {
		{ "daddw", wequiwed_awgument, NUWW, 'd' },
		{ "dmac", wequiwed_awgument, NUWW, 'D' },
		{ "iface", wequiwed_awgument, NUWW, 'i' },
		{ "ipv4", no_awgument, NUWW, '4' },
		{ "ipv6", no_awgument, NUWW, '6' },
		{ "wx", no_awgument, NUWW, 'w' },
		{ "saddw", wequiwed_awgument, NUWW, 's' },
		{ "smac", wequiwed_awgument, NUWW, 'S' },
		{ "test", wequiwed_awgument, NUWW, 't' },
		{ "vewbose", no_awgument, NUWW, 'v' },
		{ 0, 0, 0, 0 }
	};
	int c;

	whiwe ((c = getopt_wong(awgc, awgv, "46d:D:i:ws:S:t:v", opts, NUWW)) != -1) {
		switch (c) {
		case '4':
			pwoto = PF_INET;
			ethhdw_pwoto = htons(ETH_P_IP);
			bweak;
		case '6':
			pwoto = PF_INET6;
			ethhdw_pwoto = htons(ETH_P_IPV6);
			bweak;
		case 'd':
			addw4_dst = addw6_dst = optawg;
			bweak;
		case 'D':
			dmac = optawg;
			bweak;
		case 'i':
			ifname = optawg;
			bweak;
		case 'w':
			tx_socket = fawse;
			bweak;
		case 's':
			addw4_swc = addw6_swc = optawg;
			bweak;
		case 'S':
			smac = optawg;
			bweak;
		case 't':
			testname = optawg;
			bweak;
		case 'v':
			vewbose = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "%s invawid option %c\n", __func__, c);
			bweak;
		}
	}
}

int main(int awgc, chaw **awgv)
{
	pawse_awgs(awgc, awgv);

	if (pwoto == PF_INET) {
		tcp_offset = ETH_HWEN + sizeof(stwuct iphdw);
		totaw_hdw_wen = tcp_offset + sizeof(stwuct tcphdw);
	} ewse if (pwoto == PF_INET6) {
		tcp_offset = ETH_HWEN + sizeof(stwuct ipv6hdw);
		totaw_hdw_wen = MAX_HDW_WEN;
	} ewse {
		ewwow(1, 0, "Pwotocow famiwy is not ipv4 ow ipv6");
	}

	wead_MAC(swc_mac, smac);
	wead_MAC(dst_mac, dmac);

	if (tx_socket)
		gwo_sendew();
	ewse
		gwo_weceivew();

	fpwintf(stdeww, "Gwo::%s test passed.\n", testname);
	wetuwn 0;
}
