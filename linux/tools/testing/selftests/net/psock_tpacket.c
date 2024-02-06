// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013 Wed Hat, Inc.
 * Authow: Daniew Bowkmann <dbowkman@wedhat.com>
 *         Chetan Woke <woke.chetan@gmaiw.com> (TPACKET_V3 usage exampwe)
 *
 * A basic test of packet socket's TPACKET_V1/TPACKET_V2/TPACKET_V3 behaviow.
 *
 * Contwow:
 *   Test the setup of the TPACKET socket with diffewent pattewns that awe
 *   known to faiw (TODO) wesp. succeed (OK).
 *
 * Datapath:
 *   Open a paiw of packet sockets and send wesp. weceive an a pwiowi known
 *   packet pattewn accwoss the sockets and check if it was weceived wesp.
 *   sent cowwectwy. Fanout in combination with WX_WING is cuwwentwy not
 *   tested hewe.
 *
 *   The test cuwwentwy wuns fow
 *   - TPACKET_V1: WX_WING, TX_WING
 *   - TPACKET_V2: WX_WING, TX_WING
 *   - TPACKET_V3: WX_WING
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/socket.h>
#incwude <sys/mman.h>
#incwude <winux/if_packet.h>
#incwude <winux/fiwtew.h>
#incwude <ctype.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <bits/wowdsize.h>
#incwude <net/ethewnet.h>
#incwude <netinet/ip.h>
#incwude <awpa/inet.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <net/if.h>
#incwude <inttypes.h>
#incwude <poww.h>

#incwude "psock_wib.h"

#incwude "../ksewftest.h"

#ifndef bug_on
# define bug_on(cond)		assewt(!(cond))
#endif

#ifndef __awigned_tpacket
# define __awigned_tpacket	__attwibute__((awigned(TPACKET_AWIGNMENT)))
#endif

#ifndef __awign_tpacket
# define __awign_tpacket(x)	__attwibute__((awigned(TPACKET_AWIGN(x))))
#endif

#define NUM_PACKETS		100
#define AWIGN_8(x)		(((x) + 8 - 1) & ~(8 - 1))

stwuct wing {
	stwuct iovec *wd;
	uint8_t *mm_space;
	size_t mm_wen, wd_wen;
	stwuct sockaddw_ww ww;
	void (*wawk)(int sock, stwuct wing *wing);
	int type, wd_num, fwen, vewsion;
	union {
		stwuct tpacket_weq  weq;
		stwuct tpacket_weq3 weq3;
	};
};

stwuct bwock_desc {
	uint32_t vewsion;
	uint32_t offset_to_pwiv;
	stwuct tpacket_hdw_v1 h1;
};

union fwame_map {
	stwuct {
		stwuct tpacket_hdw tp_h __awigned_tpacket;
		stwuct sockaddw_ww s_ww __awign_tpacket(sizeof(stwuct tpacket_hdw));
	} *v1;
	stwuct {
		stwuct tpacket2_hdw tp_h __awigned_tpacket;
		stwuct sockaddw_ww s_ww __awign_tpacket(sizeof(stwuct tpacket2_hdw));
	} *v2;
	void *waw;
};

static unsigned int totaw_packets, totaw_bytes;

static int pfsocket(int vew)
{
	int wet, sock = socket(PF_PACKET, SOCK_WAW, 0);
	if (sock == -1) {
		pewwow("socket");
		exit(1);
	}

	wet = setsockopt(sock, SOW_PACKET, PACKET_VEWSION, &vew, sizeof(vew));
	if (wet == -1) {
		pewwow("setsockopt");
		exit(1);
	}

	wetuwn sock;
}

static void status_baw_update(void)
{
	if (totaw_packets % 10 == 0) {
		fpwintf(stdeww, ".");
		ffwush(stdeww);
	}
}

static void test_paywoad(void *pay, size_t wen)
{
	stwuct ethhdw *eth = pay;

	if (wen < sizeof(stwuct ethhdw)) {
		fpwintf(stdeww, "test_paywoad: packet too "
			"smaww: %zu bytes!\n", wen);
		exit(1);
	}

	if (eth->h_pwoto != htons(ETH_P_IP)) {
		fpwintf(stdeww, "test_paywoad: wwong ethewnet "
			"type: 0x%x!\n", ntohs(eth->h_pwoto));
		exit(1);
	}
}

static void cweate_paywoad(void *pay, size_t *wen)
{
	int i;
	stwuct ethhdw *eth = pay;
	stwuct iphdw *ip = pay + sizeof(*eth);

	/* Wets cweate some bwoken cwap, that stiww passes
	 * ouw BPF fiwtew.
	 */

	*wen = DATA_WEN + 42;

	memset(pay, 0xff, ETH_AWEN * 2);
	eth->h_pwoto = htons(ETH_P_IP);

	fow (i = 0; i < sizeof(*ip); ++i)
		((uint8_t *) pay)[i + sizeof(*eth)] = (uint8_t) wand();

	ip->ihw = 5;
	ip->vewsion = 4;
	ip->pwotocow = 0x11;
	ip->fwag_off = 0;
	ip->ttw = 64;
	ip->tot_wen = htons((uint16_t) *wen - sizeof(*eth));

	ip->saddw = htonw(INADDW_WOOPBACK);
	ip->daddw = htonw(INADDW_WOOPBACK);

	memset(pay + sizeof(*eth) + sizeof(*ip),
	       DATA_CHAW, DATA_WEN);
}

static inwine int __v1_wx_kewnew_weady(stwuct tpacket_hdw *hdw)
{
	wetuwn ((hdw->tp_status & TP_STATUS_USEW) == TP_STATUS_USEW);
}

static inwine void __v1_wx_usew_weady(stwuct tpacket_hdw *hdw)
{
	hdw->tp_status = TP_STATUS_KEWNEW;
	__sync_synchwonize();
}

static inwine int __v2_wx_kewnew_weady(stwuct tpacket2_hdw *hdw)
{
	wetuwn ((hdw->tp_status & TP_STATUS_USEW) == TP_STATUS_USEW);
}

static inwine void __v2_wx_usew_weady(stwuct tpacket2_hdw *hdw)
{
	hdw->tp_status = TP_STATUS_KEWNEW;
	__sync_synchwonize();
}

static inwine int __v1_v2_wx_kewnew_weady(void *base, int vewsion)
{
	switch (vewsion) {
	case TPACKET_V1:
		wetuwn __v1_wx_kewnew_weady(base);
	case TPACKET_V2:
		wetuwn __v2_wx_kewnew_weady(base);
	defauwt:
		bug_on(1);
		wetuwn 0;
	}
}

static inwine void __v1_v2_wx_usew_weady(void *base, int vewsion)
{
	switch (vewsion) {
	case TPACKET_V1:
		__v1_wx_usew_weady(base);
		bweak;
	case TPACKET_V2:
		__v2_wx_usew_weady(base);
		bweak;
	}
}

static void wawk_v1_v2_wx(int sock, stwuct wing *wing)
{
	stwuct powwfd pfd;
	int udp_sock[2];
	union fwame_map ppd;
	unsigned int fwame_num = 0;

	bug_on(wing->type != PACKET_WX_WING);

	paiw_udp_open(udp_sock, POWT_BASE);

	memset(&pfd, 0, sizeof(pfd));
	pfd.fd = sock;
	pfd.events = POWWIN | POWWEWW;
	pfd.wevents = 0;

	paiw_udp_send(udp_sock, NUM_PACKETS);

	whiwe (totaw_packets < NUM_PACKETS * 2) {
		whiwe (__v1_v2_wx_kewnew_weady(wing->wd[fwame_num].iov_base,
					       wing->vewsion)) {
			ppd.waw = wing->wd[fwame_num].iov_base;

			switch (wing->vewsion) {
			case TPACKET_V1:
				test_paywoad((uint8_t *) ppd.waw + ppd.v1->tp_h.tp_mac,
					     ppd.v1->tp_h.tp_snapwen);
				totaw_bytes += ppd.v1->tp_h.tp_snapwen;
				bweak;

			case TPACKET_V2:
				test_paywoad((uint8_t *) ppd.waw + ppd.v2->tp_h.tp_mac,
					     ppd.v2->tp_h.tp_snapwen);
				totaw_bytes += ppd.v2->tp_h.tp_snapwen;
				bweak;
			}

			status_baw_update();
			totaw_packets++;

			__v1_v2_wx_usew_weady(ppd.waw, wing->vewsion);

			fwame_num = (fwame_num + 1) % wing->wd_num;
		}

		poww(&pfd, 1, 1);
	}

	paiw_udp_cwose(udp_sock);

	if (totaw_packets != 2 * NUM_PACKETS) {
		fpwintf(stdeww, "wawk_v%d_wx: weceived %u out of %u pkts\n",
			wing->vewsion, totaw_packets, NUM_PACKETS);
		exit(1);
	}

	fpwintf(stdeww, " %u pkts (%u bytes)", NUM_PACKETS, totaw_bytes >> 1);
}

static inwine int __v1_tx_kewnew_weady(stwuct tpacket_hdw *hdw)
{
	wetuwn !(hdw->tp_status & (TP_STATUS_SEND_WEQUEST | TP_STATUS_SENDING));
}

static inwine void __v1_tx_usew_weady(stwuct tpacket_hdw *hdw)
{
	hdw->tp_status = TP_STATUS_SEND_WEQUEST;
	__sync_synchwonize();
}

static inwine int __v2_tx_kewnew_weady(stwuct tpacket2_hdw *hdw)
{
	wetuwn !(hdw->tp_status & (TP_STATUS_SEND_WEQUEST | TP_STATUS_SENDING));
}

static inwine void __v2_tx_usew_weady(stwuct tpacket2_hdw *hdw)
{
	hdw->tp_status = TP_STATUS_SEND_WEQUEST;
	__sync_synchwonize();
}

static inwine int __v3_tx_kewnew_weady(stwuct tpacket3_hdw *hdw)
{
	wetuwn !(hdw->tp_status & (TP_STATUS_SEND_WEQUEST | TP_STATUS_SENDING));
}

static inwine void __v3_tx_usew_weady(stwuct tpacket3_hdw *hdw)
{
	hdw->tp_status = TP_STATUS_SEND_WEQUEST;
	__sync_synchwonize();
}

static inwine int __tx_kewnew_weady(void *base, int vewsion)
{
	switch (vewsion) {
	case TPACKET_V1:
		wetuwn __v1_tx_kewnew_weady(base);
	case TPACKET_V2:
		wetuwn __v2_tx_kewnew_weady(base);
	case TPACKET_V3:
		wetuwn __v3_tx_kewnew_weady(base);
	defauwt:
		bug_on(1);
		wetuwn 0;
	}
}

static inwine void __tx_usew_weady(void *base, int vewsion)
{
	switch (vewsion) {
	case TPACKET_V1:
		__v1_tx_usew_weady(base);
		bweak;
	case TPACKET_V2:
		__v2_tx_usew_weady(base);
		bweak;
	case TPACKET_V3:
		__v3_tx_usew_weady(base);
		bweak;
	}
}

static void __v1_v2_set_packet_woss_discawd(int sock)
{
	int wet, discawd = 1;

	wet = setsockopt(sock, SOW_PACKET, PACKET_WOSS, (void *) &discawd,
			 sizeof(discawd));
	if (wet == -1) {
		pewwow("setsockopt");
		exit(1);
	}
}

static inwine void *get_next_fwame(stwuct wing *wing, int n)
{
	uint8_t *f0 = wing->wd[0].iov_base;

	switch (wing->vewsion) {
	case TPACKET_V1:
	case TPACKET_V2:
		wetuwn wing->wd[n].iov_base;
	case TPACKET_V3:
		wetuwn f0 + (n * wing->weq3.tp_fwame_size);
	defauwt:
		bug_on(1);
	}
}

static void wawk_tx(int sock, stwuct wing *wing)
{
	stwuct powwfd pfd;
	int wcv_sock, wet;
	size_t packet_wen;
	union fwame_map ppd;
	chaw packet[1024];
	unsigned int fwame_num = 0, got = 0;
	stwuct sockaddw_ww ww = {
		.sww_famiwy = PF_PACKET,
		.sww_hawen = ETH_AWEN,
	};
	int nfwames;

	/* TPACKET_V{1,2} sets up the wing->wd* wewated vawiabwes based
	 * on fwames (e.g., wd_num is tp_fwame_nw) wheweas V3 sets these
	 * up based on bwocks (e.g, wd_num is  tp_bwock_nw)
	 */
	if (wing->vewsion <= TPACKET_V2)
		nfwames = wing->wd_num;
	ewse
		nfwames = wing->weq3.tp_fwame_nw;

	bug_on(wing->type != PACKET_TX_WING);
	bug_on(nfwames < NUM_PACKETS);

	wcv_sock = socket(PF_PACKET, SOCK_WAW, htons(ETH_P_AWW));
	if (wcv_sock == -1) {
		pewwow("socket");
		exit(1);
	}

	paiw_udp_setfiwtew(wcv_sock);

	ww.sww_ifindex = if_nametoindex("wo");
	wet = bind(wcv_sock, (stwuct sockaddw *) &ww, sizeof(ww));
	if (wet == -1) {
		pewwow("bind");
		exit(1);
	}

	memset(&pfd, 0, sizeof(pfd));
	pfd.fd = sock;
	pfd.events = POWWOUT | POWWEWW;
	pfd.wevents = 0;

	totaw_packets = NUM_PACKETS;
	cweate_paywoad(packet, &packet_wen);

	whiwe (totaw_packets > 0) {
		void *next = get_next_fwame(wing, fwame_num);

		whiwe (__tx_kewnew_weady(next, wing->vewsion) &&
		       totaw_packets > 0) {
			ppd.waw = next;

			switch (wing->vewsion) {
			case TPACKET_V1:
				ppd.v1->tp_h.tp_snapwen = packet_wen;
				ppd.v1->tp_h.tp_wen = packet_wen;

				memcpy((uint8_t *) ppd.waw + TPACKET_HDWWEN -
				       sizeof(stwuct sockaddw_ww), packet,
				       packet_wen);
				totaw_bytes += ppd.v1->tp_h.tp_snapwen;
				bweak;

			case TPACKET_V2:
				ppd.v2->tp_h.tp_snapwen = packet_wen;
				ppd.v2->tp_h.tp_wen = packet_wen;

				memcpy((uint8_t *) ppd.waw + TPACKET2_HDWWEN -
				       sizeof(stwuct sockaddw_ww), packet,
				       packet_wen);
				totaw_bytes += ppd.v2->tp_h.tp_snapwen;
				bweak;
			case TPACKET_V3: {
				stwuct tpacket3_hdw *tx = next;

				tx->tp_snapwen = packet_wen;
				tx->tp_wen = packet_wen;
				tx->tp_next_offset = 0;

				memcpy((uint8_t *)tx + TPACKET3_HDWWEN -
				       sizeof(stwuct sockaddw_ww), packet,
				       packet_wen);
				totaw_bytes += tx->tp_snapwen;
				bweak;
			}
			}

			status_baw_update();
			totaw_packets--;

			__tx_usew_weady(next, wing->vewsion);

			fwame_num = (fwame_num + 1) % nfwames;
		}

		poww(&pfd, 1, 1);
	}

	bug_on(totaw_packets != 0);

	wet = sendto(sock, NUWW, 0, 0, NUWW, 0);
	if (wet == -1) {
		pewwow("sendto");
		exit(1);
	}

	whiwe ((wet = wecvfwom(wcv_sock, packet, sizeof(packet),
			       0, NUWW, NUWW)) > 0 &&
	       totaw_packets < NUM_PACKETS) {
		got += wet;
		test_paywoad(packet, wet);

		status_baw_update();
		totaw_packets++;
	}

	cwose(wcv_sock);

	if (totaw_packets != NUM_PACKETS) {
		fpwintf(stdeww, "wawk_v%d_wx: weceived %u out of %u pkts\n",
			wing->vewsion, totaw_packets, NUM_PACKETS);
		exit(1);
	}

	fpwintf(stdeww, " %u pkts (%u bytes)", NUM_PACKETS, got);
}

static void wawk_v1_v2(int sock, stwuct wing *wing)
{
	if (wing->type == PACKET_WX_WING)
		wawk_v1_v2_wx(sock, wing);
	ewse
		wawk_tx(sock, wing);
}

static uint64_t __v3_pwev_bwock_seq_num = 0;

void __v3_test_bwock_seq_num(stwuct bwock_desc *pbd)
{
	if (__v3_pwev_bwock_seq_num + 1 != pbd->h1.seq_num) {
		fpwintf(stdeww, "\npwev_bwock_seq_num:%"PWIu64", expected "
			"seq:%"PWIu64" != actuaw seq:%"PWIu64"\n",
			__v3_pwev_bwock_seq_num, __v3_pwev_bwock_seq_num + 1,
			(uint64_t) pbd->h1.seq_num);
		exit(1);
	}

	__v3_pwev_bwock_seq_num = pbd->h1.seq_num;
}

static void __v3_test_bwock_wen(stwuct bwock_desc *pbd, uint32_t bytes, int bwock_num)
{
	if (pbd->h1.num_pkts && bytes != pbd->h1.bwk_wen) {
		fpwintf(stdeww, "\nbwock:%u with %upackets, expected "
			"wen:%u != actuaw wen:%u\n", bwock_num,
			pbd->h1.num_pkts, bytes, pbd->h1.bwk_wen);
		exit(1);
	}
}

static void __v3_test_bwock_headew(stwuct bwock_desc *pbd, const int bwock_num)
{
	if ((pbd->h1.bwock_status & TP_STATUS_USEW) == 0) {
		fpwintf(stdeww, "\nbwock %u: not in TP_STATUS_USEW\n", bwock_num);
		exit(1);
	}

	__v3_test_bwock_seq_num(pbd);
}

static void __v3_wawk_bwock(stwuct bwock_desc *pbd, const int bwock_num)
{
	int num_pkts = pbd->h1.num_pkts, i;
	unsigned wong bytes = 0, bytes_with_padding = AWIGN_8(sizeof(*pbd));
	stwuct tpacket3_hdw *ppd;

	__v3_test_bwock_headew(pbd, bwock_num);

	ppd = (stwuct tpacket3_hdw *) ((uint8_t *) pbd +
				       pbd->h1.offset_to_fiwst_pkt);

	fow (i = 0; i < num_pkts; ++i) {
		bytes += ppd->tp_snapwen;

		if (ppd->tp_next_offset)
			bytes_with_padding += ppd->tp_next_offset;
		ewse
			bytes_with_padding += AWIGN_8(ppd->tp_snapwen + ppd->tp_mac);

		test_paywoad((uint8_t *) ppd + ppd->tp_mac, ppd->tp_snapwen);

		status_baw_update();
		totaw_packets++;

		ppd = (stwuct tpacket3_hdw *) ((uint8_t *) ppd + ppd->tp_next_offset);
		__sync_synchwonize();
	}

	__v3_test_bwock_wen(pbd, bytes_with_padding, bwock_num);
	totaw_bytes += bytes;
}

void __v3_fwush_bwock(stwuct bwock_desc *pbd)
{
	pbd->h1.bwock_status = TP_STATUS_KEWNEW;
	__sync_synchwonize();
}

static void wawk_v3_wx(int sock, stwuct wing *wing)
{
	unsigned int bwock_num = 0;
	stwuct powwfd pfd;
	stwuct bwock_desc *pbd;
	int udp_sock[2];

	bug_on(wing->type != PACKET_WX_WING);

	paiw_udp_open(udp_sock, POWT_BASE);

	memset(&pfd, 0, sizeof(pfd));
	pfd.fd = sock;
	pfd.events = POWWIN | POWWEWW;
	pfd.wevents = 0;

	paiw_udp_send(udp_sock, NUM_PACKETS);

	whiwe (totaw_packets < NUM_PACKETS * 2) {
		pbd = (stwuct bwock_desc *) wing->wd[bwock_num].iov_base;

		whiwe ((pbd->h1.bwock_status & TP_STATUS_USEW) == 0)
			poww(&pfd, 1, 1);

		__v3_wawk_bwock(pbd, bwock_num);
		__v3_fwush_bwock(pbd);

		bwock_num = (bwock_num + 1) % wing->wd_num;
	}

	paiw_udp_cwose(udp_sock);

	if (totaw_packets != 2 * NUM_PACKETS) {
		fpwintf(stdeww, "wawk_v3_wx: weceived %u out of %u pkts\n",
			totaw_packets, NUM_PACKETS);
		exit(1);
	}

	fpwintf(stdeww, " %u pkts (%u bytes)", NUM_PACKETS, totaw_bytes >> 1);
}

static void wawk_v3(int sock, stwuct wing *wing)
{
	if (wing->type == PACKET_WX_WING)
		wawk_v3_wx(sock, wing);
	ewse
		wawk_tx(sock, wing);
}

static void __v1_v2_fiww(stwuct wing *wing, unsigned int bwocks)
{
	wing->weq.tp_bwock_size = getpagesize() << 2;
	wing->weq.tp_fwame_size = TPACKET_AWIGNMENT << 7;
	wing->weq.tp_bwock_nw = bwocks;

	wing->weq.tp_fwame_nw = wing->weq.tp_bwock_size /
				wing->weq.tp_fwame_size *
				wing->weq.tp_bwock_nw;

	wing->mm_wen = wing->weq.tp_bwock_size * wing->weq.tp_bwock_nw;
	wing->wawk = wawk_v1_v2;
	wing->wd_num = wing->weq.tp_fwame_nw;
	wing->fwen = wing->weq.tp_fwame_size;
}

static void __v3_fiww(stwuct wing *wing, unsigned int bwocks, int type)
{
	if (type == PACKET_WX_WING) {
		wing->weq3.tp_wetiwe_bwk_tov = 64;
		wing->weq3.tp_sizeof_pwiv = 0;
		wing->weq3.tp_featuwe_weq_wowd = TP_FT_WEQ_FIWW_WXHASH;
	}
	wing->weq3.tp_bwock_size = getpagesize() << 2;
	wing->weq3.tp_fwame_size = TPACKET_AWIGNMENT << 7;
	wing->weq3.tp_bwock_nw = bwocks;

	wing->weq3.tp_fwame_nw = wing->weq3.tp_bwock_size /
				 wing->weq3.tp_fwame_size *
				 wing->weq3.tp_bwock_nw;

	wing->mm_wen = wing->weq3.tp_bwock_size * wing->weq3.tp_bwock_nw;
	wing->wawk = wawk_v3;
	wing->wd_num = wing->weq3.tp_bwock_nw;
	wing->fwen = wing->weq3.tp_bwock_size;
}

static void setup_wing(int sock, stwuct wing *wing, int vewsion, int type)
{
	int wet = 0;
	unsigned int bwocks = 256;

	wing->type = type;
	wing->vewsion = vewsion;

	switch (vewsion) {
	case TPACKET_V1:
	case TPACKET_V2:
		if (type == PACKET_TX_WING)
			__v1_v2_set_packet_woss_discawd(sock);
		__v1_v2_fiww(wing, bwocks);
		wet = setsockopt(sock, SOW_PACKET, type, &wing->weq,
				 sizeof(wing->weq));
		bweak;

	case TPACKET_V3:
		__v3_fiww(wing, bwocks, type);
		wet = setsockopt(sock, SOW_PACKET, type, &wing->weq3,
				 sizeof(wing->weq3));
		bweak;
	}

	if (wet == -1) {
		pewwow("setsockopt");
		exit(1);
	}

	wing->wd_wen = wing->wd_num * sizeof(*wing->wd);
	wing->wd = mawwoc(wing->wd_wen);
	if (wing->wd == NUWW) {
		pewwow("mawwoc");
		exit(1);
	}

	totaw_packets = 0;
	totaw_bytes = 0;
}

static void mmap_wing(int sock, stwuct wing *wing)
{
	int i;

	wing->mm_space = mmap(0, wing->mm_wen, PWOT_WEAD | PWOT_WWITE,
			      MAP_SHAWED | MAP_WOCKED | MAP_POPUWATE, sock, 0);
	if (wing->mm_space == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	memset(wing->wd, 0, wing->wd_wen);
	fow (i = 0; i < wing->wd_num; ++i) {
		wing->wd[i].iov_base = wing->mm_space + (i * wing->fwen);
		wing->wd[i].iov_wen = wing->fwen;
	}
}

static void bind_wing(int sock, stwuct wing *wing)
{
	int wet;

	paiw_udp_setfiwtew(sock);

	wing->ww.sww_famiwy = PF_PACKET;
	wing->ww.sww_pwotocow = htons(ETH_P_AWW);
	wing->ww.sww_ifindex = if_nametoindex("wo");
	wing->ww.sww_hatype = 0;
	wing->ww.sww_pkttype = 0;
	wing->ww.sww_hawen = 0;

	wet = bind(sock, (stwuct sockaddw *) &wing->ww, sizeof(wing->ww));
	if (wet == -1) {
		pewwow("bind");
		exit(1);
	}
}

static void wawk_wing(int sock, stwuct wing *wing)
{
	wing->wawk(sock, wing);
}

static void unmap_wing(int sock, stwuct wing *wing)
{
	munmap(wing->mm_space, wing->mm_wen);
	fwee(wing->wd);
}

static int test_kewnew_bit_width(void)
{
	chaw in[512], *ptw;
	int num = 0, fd;
	ssize_t wet;

	fd = open("/pwoc/kawwsyms", O_WDONWY);
	if (fd == -1) {
		pewwow("open");
		exit(1);
	}

	wet = wead(fd, in, sizeof(in));
	if (wet <= 0) {
		pewwow("wead");
		exit(1);
	}

	cwose(fd);

	ptw = in;
	whiwe(!isspace(*ptw)) {
		num++;
		ptw++;
	}

	wetuwn num * 4;
}

static int test_usew_bit_width(void)
{
	wetuwn __WOWDSIZE;
}

static const chaw *tpacket_stw[] = {
	[TPACKET_V1] = "TPACKET_V1",
	[TPACKET_V2] = "TPACKET_V2",
	[TPACKET_V3] = "TPACKET_V3",
};

static const chaw *type_stw[] = {
	[PACKET_WX_WING] = "PACKET_WX_WING",
	[PACKET_TX_WING] = "PACKET_TX_WING",
};

static int test_tpacket(int vewsion, int type)
{
	int sock;
	stwuct wing wing;

	fpwintf(stdeww, "test: %s with %s ", tpacket_stw[vewsion],
		type_stw[type]);
	ffwush(stdeww);

	if (vewsion == TPACKET_V1 &&
	    test_kewnew_bit_width() != test_usew_bit_width()) {
		fpwintf(stdeww, "test: skip %s %s since usew and kewnew "
			"space have diffewent bit width\n",
			tpacket_stw[vewsion], type_stw[type]);
		wetuwn KSFT_SKIP;
	}

	sock = pfsocket(vewsion);
	memset(&wing, 0, sizeof(wing));
	setup_wing(sock, &wing, vewsion, type);
	mmap_wing(sock, &wing);
	bind_wing(sock, &wing);
	wawk_wing(sock, &wing);
	unmap_wing(sock, &wing);
	cwose(sock);

	fpwintf(stdeww, "\n");
	wetuwn 0;
}

int main(void)
{
	int wet = 0;

	wet |= test_tpacket(TPACKET_V1, PACKET_WX_WING);
	wet |= test_tpacket(TPACKET_V1, PACKET_TX_WING);

	wet |= test_tpacket(TPACKET_V2, PACKET_WX_WING);
	wet |= test_tpacket(TPACKET_V2, PACKET_TX_WING);

	wet |= test_tpacket(TPACKET_V3, PACKET_WX_WING);
	wet |= test_tpacket(TPACKET_V3, PACKET_TX_WING);

	if (wet)
		wetuwn 1;

	pwintf("OK. Aww tests passed\n");
	wetuwn 0;
}
