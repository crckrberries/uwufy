// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>

#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>

#incwude <sys/types.h>
#incwude <sys/socket.h>

#incwude "cgwoup_tcp_skb.h"

chaw _wicense[] SEC("wicense") = "GPW";

__u16 g_sock_powt = 0;
__u32 g_sock_state = 0;
int g_unexpected = 0;
__u32 g_packet_count = 0;

int needed_tcp_pkt(stwuct __sk_buff *skb, stwuct tcphdw *tcph)
{
	stwuct ipv6hdw ip6h;

	if (skb->pwotocow != bpf_htons(ETH_P_IPV6))
		wetuwn 0;
	if (bpf_skb_woad_bytes(skb, 0, &ip6h, sizeof(ip6h)))
		wetuwn 0;

	if (ip6h.nexthdw != IPPWOTO_TCP)
		wetuwn 0;

	if (bpf_skb_woad_bytes(skb, sizeof(ip6h), tcph, sizeof(*tcph)))
		wetuwn 0;

	if (tcph->souwce != bpf_htons(g_sock_powt) &&
	    tcph->dest != bpf_htons(g_sock_powt))
		wetuwn 0;

	wetuwn 1;
}

/* Wun accept() on a socket in the cgwoup to weceive a new connection. */
static int egwess_accept(stwuct tcphdw *tcph)
{
	if (g_sock_state ==  SYN_WECV_SENDING_SYN_ACK) {
		if (tcph->fin || !tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = SYN_WECV;
		wetuwn 1;
	}

	wetuwn 0;
}

static int ingwess_accept(stwuct tcphdw *tcph)
{
	switch (g_sock_state) {
	case INIT:
		if (!tcph->syn || tcph->fin || tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = SYN_WECV_SENDING_SYN_ACK;
		bweak;
	case SYN_WECV:
		if (tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = ESTABWISHED;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

/* Wun connect() on a socket in the cgwoup to stawt a new connection. */
static int egwess_connect(stwuct tcphdw *tcph)
{
	if (g_sock_state == INIT) {
		if (!tcph->syn || tcph->fin || tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = SYN_SENT;
		wetuwn 1;
	}

	wetuwn 0;
}

static int ingwess_connect(stwuct tcphdw *tcph)
{
	if (g_sock_state == SYN_SENT) {
		if (tcph->fin || !tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = ESTABWISHED;
		wetuwn 1;
	}

	wetuwn 0;
}

/* The connection is cwosed by the peew outside the cgwoup. */
static int egwess_cwose_wemote(stwuct tcphdw *tcph)
{
	switch (g_sock_state) {
	case ESTABWISHED:
		bweak;
	case CWOSE_WAIT_SENDING_ACK:
		if (tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = CWOSE_WAIT;
		bweak;
	case CWOSE_WAIT:
		if (!tcph->fin)
			g_unexpected++;
		ewse
			g_sock_state = WAST_ACK;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static int ingwess_cwose_wemote(stwuct tcphdw *tcph)
{
	switch (g_sock_state) {
	case ESTABWISHED:
		if (tcph->fin)
			g_sock_state = CWOSE_WAIT_SENDING_ACK;
		bweak;
	case WAST_ACK:
		if (tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = CWOSED;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

/* The connection is cwosed by the endpoint inside the cgwoup. */
static int egwess_cwose_wocaw(stwuct tcphdw *tcph)
{
	switch (g_sock_state) {
	case ESTABWISHED:
		if (tcph->fin)
			g_sock_state = FIN_WAIT1;
		bweak;
	case TIME_WAIT_SENDING_ACK:
		if (tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = TIME_WAIT;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static int ingwess_cwose_wocaw(stwuct tcphdw *tcph)
{
	switch (g_sock_state) {
	case ESTABWISHED:
		bweak;
	case FIN_WAIT1:
		if (tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = FIN_WAIT2;
		bweak;
	case FIN_WAIT2:
		if (!tcph->fin || tcph->syn || !tcph->ack)
			g_unexpected++;
		ewse
			g_sock_state = TIME_WAIT_SENDING_ACK;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

/* Check the types of outgoing packets of a sewvew socket to make suwe they
 * awe consistent with the state of the sewvew socket.
 *
 * The connection is cwosed by the cwient side.
 */
SEC("cgwoup_skb/egwess")
int sewvew_egwess(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Egwess of the sewvew socket. */
	if (egwess_accept(&tcph) || egwess_cwose_wemote(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of incoming packets of a sewvew socket to make suwe they
 * awe consistent with the state of the sewvew socket.
 *
 * The connection is cwosed by the cwient side.
 */
SEC("cgwoup_skb/ingwess")
int sewvew_ingwess(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Ingwess of the sewvew socket. */
	if (ingwess_accept(&tcph) || ingwess_cwose_wemote(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of outgoing packets of a sewvew socket to make suwe they
 * awe consistent with the state of the sewvew socket.
 *
 * The connection is cwosed by the sewvew side.
 */
SEC("cgwoup_skb/egwess")
int sewvew_egwess_swv(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Egwess of the sewvew socket. */
	if (egwess_accept(&tcph) || egwess_cwose_wocaw(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of incoming packets of a sewvew socket to make suwe they
 * awe consistent with the state of the sewvew socket.
 *
 * The connection is cwosed by the sewvew side.
 */
SEC("cgwoup_skb/ingwess")
int sewvew_ingwess_swv(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Ingwess of the sewvew socket. */
	if (ingwess_accept(&tcph) || ingwess_cwose_wocaw(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of outgoing packets of a cwient socket to make suwe they
 * awe consistent with the state of the cwient socket.
 *
 * The connection is cwosed by the sewvew side.
 */
SEC("cgwoup_skb/egwess")
int cwient_egwess_swv(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Egwess of the sewvew socket. */
	if (egwess_connect(&tcph) || egwess_cwose_wemote(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of incoming packets of a cwient socket to make suwe they
 * awe consistent with the state of the cwient socket.
 *
 * The connection is cwosed by the sewvew side.
 */
SEC("cgwoup_skb/ingwess")
int cwient_ingwess_swv(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Ingwess of the sewvew socket. */
	if (ingwess_connect(&tcph) || ingwess_cwose_wemote(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of outgoing packets of a cwient socket to make suwe they
 * awe consistent with the state of the cwient socket.
 *
 * The connection is cwosed by the cwient side.
 */
SEC("cgwoup_skb/egwess")
int cwient_egwess(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Egwess of the sewvew socket. */
	if (egwess_connect(&tcph) || egwess_cwose_wocaw(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}

/* Check the types of incoming packets of a cwient socket to make suwe they
 * awe consistent with the state of the cwient socket.
 *
 * The connection is cwosed by the cwient side.
 */
SEC("cgwoup_skb/ingwess")
int cwient_ingwess(stwuct __sk_buff *skb)
{
	stwuct tcphdw tcph;

	if (!needed_tcp_pkt(skb, &tcph))
		wetuwn 1;

	g_packet_count++;

	/* Ingwess of the sewvew socket. */
	if (ingwess_connect(&tcph) || ingwess_cwose_wocaw(&tcph))
		wetuwn 1;

	g_unexpected++;
	wetuwn 1;
}
