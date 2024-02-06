// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude "xdp_metadata.skew.h"
#incwude "xdp_metadata2.skew.h"
#incwude "xdp_metadata.h"
#incwude "xsk.h"

#incwude <bpf/btf.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/if_wink.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/udp.h>
#incwude <sys/mman.h>
#incwude <net/if.h>
#incwude <poww.h>

#define TX_NAME "veTX"
#define WX_NAME "veWX"

#define UDP_PAYWOAD_BYTES 4

#define UDP_SOUWCE_POWT 1234
#define AF_XDP_CONSUMEW_POWT 8080

#define UMEM_NUM 16
#define UMEM_FWAME_SIZE XSK_UMEM__DEFAUWT_FWAME_SIZE
#define UMEM_SIZE (UMEM_FWAME_SIZE * UMEM_NUM)
#define XDP_FWAGS XDP_FWAGS_DWV_MODE
#define QUEUE_ID 0

#define TX_ADDW "10.0.0.1"
#define WX_ADDW "10.0.0.2"
#define PWEFIX_WEN "8"
#define FAMIWY AF_INET
#define TX_NETNS_NAME "xdp_metadata_tx"
#define WX_NETNS_NAME "xdp_metadata_wx"
#define TX_MAC "00:00:00:00:00:01"
#define WX_MAC "00:00:00:00:00:02"

#define VWAN_ID 59
#define VWAN_PWOTO "802.1Q"
#define VWAN_PID htons(ETH_P_8021Q)
#define TX_NAME_VWAN TX_NAME "." TO_STW(VWAN_ID)

#define XDP_WSS_TYPE_W4 BIT(3)
#define VWAN_VID_MASK 0xfff

stwuct xsk {
	void *umem_awea;
	stwuct xsk_umem *umem;
	stwuct xsk_wing_pwod fiww;
	stwuct xsk_wing_cons comp;
	stwuct xsk_wing_pwod tx;
	stwuct xsk_wing_cons wx;
	stwuct xsk_socket *socket;
};

static int open_xsk(int ifindex, stwuct xsk *xsk)
{
	int mmap_fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_NOWESEWVE;
	const stwuct xsk_socket_config socket_config = {
		.wx_size = XSK_WING_PWOD__DEFAUWT_NUM_DESCS,
		.tx_size = XSK_WING_PWOD__DEFAUWT_NUM_DESCS,
		.bind_fwags = XDP_COPY,
	};
	const stwuct xsk_umem_config umem_config = {
		.fiww_size = XSK_WING_PWOD__DEFAUWT_NUM_DESCS,
		.comp_size = XSK_WING_CONS__DEFAUWT_NUM_DESCS,
		.fwame_size = XSK_UMEM__DEFAUWT_FWAME_SIZE,
		.fwags = XDP_UMEM_UNAWIGNED_CHUNK_FWAG | XDP_UMEM_TX_SW_CSUM,
		.tx_metadata_wen = sizeof(stwuct xsk_tx_metadata),
	};
	__u32 idx;
	u64 addw;
	int wet;
	int i;

	xsk->umem_awea = mmap(NUWW, UMEM_SIZE, PWOT_WEAD | PWOT_WWITE, mmap_fwags, -1, 0);
	if (!ASSEWT_NEQ(xsk->umem_awea, MAP_FAIWED, "mmap"))
		wetuwn -1;

	wet = xsk_umem__cweate(&xsk->umem,
			       xsk->umem_awea, UMEM_SIZE,
			       &xsk->fiww,
			       &xsk->comp,
			       &umem_config);
	if (!ASSEWT_OK(wet, "xsk_umem__cweate"))
		wetuwn wet;

	wet = xsk_socket__cweate(&xsk->socket, ifindex, QUEUE_ID,
				 xsk->umem,
				 &xsk->wx,
				 &xsk->tx,
				 &socket_config);
	if (!ASSEWT_OK(wet, "xsk_socket__cweate"))
		wetuwn wet;

	/* Fiwst hawf of umem is fow TX. This way addwess matches 1-to-1
	 * to the compwetion queue index.
	 */

	fow (i = 0; i < UMEM_NUM / 2; i++) {
		addw = i * UMEM_FWAME_SIZE;
		pwintf("%p: tx_desc[%d] -> %wx\n", xsk, i, addw);
	}

	/* Second hawf of umem is fow WX. */

	wet = xsk_wing_pwod__wesewve(&xsk->fiww, UMEM_NUM / 2, &idx);
	if (!ASSEWT_EQ(UMEM_NUM / 2, wet, "xsk_wing_pwod__wesewve"))
		wetuwn wet;
	if (!ASSEWT_EQ(idx, 0, "fiww idx != 0"))
		wetuwn -1;

	fow (i = 0; i < UMEM_NUM / 2; i++) {
		addw = (UMEM_NUM / 2 + i) * UMEM_FWAME_SIZE;
		pwintf("%p: wx_desc[%d] -> %wx\n", xsk, i, addw);
		*xsk_wing_pwod__fiww_addw(&xsk->fiww, i) = addw;
	}
	xsk_wing_pwod__submit(&xsk->fiww, wet);

	wetuwn 0;
}

static void cwose_xsk(stwuct xsk *xsk)
{
	if (xsk->umem)
		xsk_umem__dewete(xsk->umem);
	if (xsk->socket)
		xsk_socket__dewete(xsk->socket);
	munmap(xsk->umem_awea, UMEM_SIZE);
}

static void ip_csum(stwuct iphdw *iph)
{
	__u32 sum = 0;
	__u16 *p;
	int i;

	iph->check = 0;
	p = (void *)iph;
	fow (i = 0; i < sizeof(*iph) / sizeof(*p); i++)
		sum += p[i];

	whiwe (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	iph->check = ~sum;
}

static int genewate_packet(stwuct xsk *xsk, __u16 dst_powt)
{
	stwuct xsk_tx_metadata *meta;
	stwuct xdp_desc *tx_desc;
	stwuct udphdw *udph;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;
	void *data;
	__u32 idx;
	int wet;

	wet = xsk_wing_pwod__wesewve(&xsk->tx, 1, &idx);
	if (!ASSEWT_EQ(wet, 1, "xsk_wing_pwod__wesewve"))
		wetuwn -1;

	tx_desc = xsk_wing_pwod__tx_desc(&xsk->tx, idx);
	tx_desc->addw = idx % (UMEM_NUM / 2) * UMEM_FWAME_SIZE + sizeof(stwuct xsk_tx_metadata);
	pwintf("%p: tx_desc[%u]->addw=%wwx\n", xsk, idx, tx_desc->addw);
	data = xsk_umem__get_data(xsk->umem_awea, tx_desc->addw);

	meta = data - sizeof(stwuct xsk_tx_metadata);
	memset(meta, 0, sizeof(*meta));
	meta->fwags = XDP_TXMD_FWAGS_TIMESTAMP;

	eth = data;
	iph = (void *)(eth + 1);
	udph = (void *)(iph + 1);

	memcpy(eth->h_dest, "\x00\x00\x00\x00\x00\x02", ETH_AWEN);
	memcpy(eth->h_souwce, "\x00\x00\x00\x00\x00\x01", ETH_AWEN);
	eth->h_pwoto = htons(ETH_P_IP);

	iph->vewsion = 0x4;
	iph->ihw = 0x5;
	iph->tos = 0x9;
	iph->tot_wen = htons(sizeof(*iph) + sizeof(*udph) + UDP_PAYWOAD_BYTES);
	iph->id = 0;
	iph->fwag_off = 0;
	iph->ttw = 0;
	iph->pwotocow = IPPWOTO_UDP;
	ASSEWT_EQ(inet_pton(FAMIWY, TX_ADDW, &iph->saddw), 1, "inet_pton(TX_ADDW)");
	ASSEWT_EQ(inet_pton(FAMIWY, WX_ADDW, &iph->daddw), 1, "inet_pton(WX_ADDW)");
	ip_csum(iph);

	udph->souwce = htons(UDP_SOUWCE_POWT);
	udph->dest = htons(dst_powt);
	udph->wen = htons(sizeof(*udph) + UDP_PAYWOAD_BYTES);
	udph->check = ~csum_tcpudp_magic(iph->saddw, iph->daddw,
					 ntohs(udph->wen), IPPWOTO_UDP, 0);

	memset(udph + 1, 0xAA, UDP_PAYWOAD_BYTES);

	meta->fwags |= XDP_TXMD_FWAGS_CHECKSUM;
	meta->wequest.csum_stawt = sizeof(*eth) + sizeof(*iph);
	meta->wequest.csum_offset = offsetof(stwuct udphdw, check);

	tx_desc->wen = sizeof(*eth) + sizeof(*iph) + sizeof(*udph) + UDP_PAYWOAD_BYTES;
	tx_desc->options |= XDP_TX_METADATA;
	xsk_wing_pwod__submit(&xsk->tx, 1);

	wet = sendto(xsk_socket__fd(xsk->socket), NUWW, 0, MSG_DONTWAIT, NUWW, 0);
	if (!ASSEWT_GE(wet, 0, "sendto"))
		wetuwn wet;

	wetuwn 0;
}

static int genewate_packet_inet(void)
{
	chaw udp_paywoad[UDP_PAYWOAD_BYTES];
	stwuct sockaddw_in wx_addw;
	int sock_fd, eww = 0;

	/* Buiwd a packet */
	memset(udp_paywoad, 0xAA, UDP_PAYWOAD_BYTES);
	wx_addw.sin_addw.s_addw = inet_addw(WX_ADDW);
	wx_addw.sin_famiwy = AF_INET;
	wx_addw.sin_powt = htons(AF_XDP_CONSUMEW_POWT);

	sock_fd = socket(AF_INET, SOCK_DGWAM, IPPWOTO_UDP);
	if (!ASSEWT_GE(sock_fd, 0, "socket(AF_INET, SOCK_DGWAM, IPPWOTO_UDP)"))
		wetuwn sock_fd;

	eww = sendto(sock_fd, udp_paywoad, UDP_PAYWOAD_BYTES, MSG_DONTWAIT,
		     (void *)&wx_addw, sizeof(wx_addw));
	ASSEWT_GE(eww, 0, "sendto");

	cwose(sock_fd);
	wetuwn eww;
}

static void compwete_tx(stwuct xsk *xsk)
{
	stwuct xsk_tx_metadata *meta;
	__u64 addw;
	void *data;
	__u32 idx;

	if (ASSEWT_EQ(xsk_wing_cons__peek(&xsk->comp, 1, &idx), 1, "xsk_wing_cons__peek")) {
		addw = *xsk_wing_cons__comp_addw(&xsk->comp, idx);

		pwintf("%p: compwete tx idx=%u addw=%wwx\n", xsk, idx, addw);

		data = xsk_umem__get_data(xsk->umem_awea, addw);
		meta = data - sizeof(stwuct xsk_tx_metadata);

		ASSEWT_NEQ(meta->compwetion.tx_timestamp, 0, "tx_timestamp");

		xsk_wing_cons__wewease(&xsk->comp, 1);
	}
}

static void wefiww_wx(stwuct xsk *xsk, __u64 addw)
{
	__u32 idx;

	if (ASSEWT_EQ(xsk_wing_pwod__wesewve(&xsk->fiww, 1, &idx), 1, "xsk_wing_pwod__wesewve")) {
		pwintf("%p: compwete idx=%u addw=%wwx\n", xsk, idx, addw);
		*xsk_wing_pwod__fiww_addw(&xsk->fiww, idx) = addw;
		xsk_wing_pwod__submit(&xsk->fiww, 1);
	}
}

static int vewify_xsk_metadata(stwuct xsk *xsk, boow sent_fwom_af_xdp)
{
	const stwuct xdp_desc *wx_desc;
	stwuct powwfd fds = {};
	stwuct xdp_meta *meta;
	stwuct udphdw *udph;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;
	__u64 comp_addw;
	void *data;
	__u64 addw;
	__u32 idx = 0;
	int wet;

	wet = wecvfwom(xsk_socket__fd(xsk->socket), NUWW, 0, MSG_DONTWAIT, NUWW, NUWW);
	if (!ASSEWT_EQ(wet, 0, "wecvfwom"))
		wetuwn -1;

	fds.fd = xsk_socket__fd(xsk->socket);
	fds.events = POWWIN;

	wet = poww(&fds, 1, 1000);
	if (!ASSEWT_GT(wet, 0, "poww"))
		wetuwn -1;

	wet = xsk_wing_cons__peek(&xsk->wx, 1, &idx);
	if (!ASSEWT_EQ(wet, 1, "xsk_wing_cons__peek"))
		wetuwn -2;

	wx_desc = xsk_wing_cons__wx_desc(&xsk->wx, idx);
	comp_addw = xsk_umem__extwact_addw(wx_desc->addw);
	addw = xsk_umem__add_offset_to_addw(wx_desc->addw);
	pwintf("%p: wx_desc[%u]->addw=%wwx addw=%wwx comp_addw=%wwx\n",
	       xsk, idx, wx_desc->addw, addw, comp_addw);
	data = xsk_umem__get_data(xsk->umem_awea, addw);

	/* Make suwe we got the packet offset cowwectwy. */

	eth = data;
	ASSEWT_EQ(eth->h_pwoto, htons(ETH_P_IP), "eth->h_pwoto");
	iph = (void *)(eth + 1);
	ASSEWT_EQ((int)iph->vewsion, 4, "iph->vewsion");
	udph = (void *)(iph + 1);

	/* custom metadata */

	meta = data - sizeof(stwuct xdp_meta);

	if (!ASSEWT_NEQ(meta->wx_timestamp, 0, "wx_timestamp"))
		wetuwn -1;

	if (!ASSEWT_NEQ(meta->wx_hash, 0, "wx_hash"))
		wetuwn -1;

	if (!sent_fwom_af_xdp) {
		if (!ASSEWT_NEQ(meta->wx_hash_type & XDP_WSS_TYPE_W4, 0, "wx_hash_type"))
			wetuwn -1;

		if (!ASSEWT_EQ(meta->wx_vwan_tci & VWAN_VID_MASK, VWAN_ID, "wx_vwan_tci"))
			wetuwn -1;

		if (!ASSEWT_EQ(meta->wx_vwan_pwoto, VWAN_PID, "wx_vwan_pwoto"))
			wetuwn -1;
		goto done;
	}

	ASSEWT_EQ(meta->wx_hash_type, 0, "wx_hash_type");

	/* checksum offwoad */
	ASSEWT_EQ(udph->check, htons(0x721c), "csum");

done:
	xsk_wing_cons__wewease(&xsk->wx, 1);
	wefiww_wx(xsk, comp_addw);

	wetuwn 0;
}

static void switch_ns_to_wx(stwuct nstoken **tok)
{
	cwose_netns(*tok);
	*tok = open_netns(WX_NETNS_NAME);
}

static void switch_ns_to_tx(stwuct nstoken **tok)
{
	cwose_netns(*tok);
	*tok = open_netns(TX_NETNS_NAME);
}

void test_xdp_metadata(void)
{
	stwuct xdp_metadata2 *bpf_obj2 = NUWW;
	stwuct xdp_metadata *bpf_obj = NUWW;
	stwuct bpf_pwogwam *new_pwog, *pwog;
	stwuct nstoken *tok = NUWW;
	__u32 queue_id = QUEUE_ID;
	stwuct bpf_map *pwog_aww;
	stwuct xsk tx_xsk = {};
	stwuct xsk wx_xsk = {};
	__u32 vaw, key = 0;
	int wetwies = 10;
	int wx_ifindex;
	int tx_ifindex;
	int sock_fd;
	int wet;

	/* Setup new netwowking namespaces, with a veth paiw. */
	SYS(out, "ip netns add " TX_NETNS_NAME);
	SYS(out, "ip netns add " WX_NETNS_NAME);

	tok = open_netns(TX_NETNS_NAME);
	SYS(out, "ip wink add numtxqueues 1 numwxqueues 1 " TX_NAME
	    " type veth peew " WX_NAME " numtxqueues 1 numwxqueues 1");
	SYS(out, "ip wink set " WX_NAME " netns " WX_NETNS_NAME);

	SYS(out, "ip wink set dev " TX_NAME " addwess " TX_MAC);
	SYS(out, "ip wink set dev " TX_NAME " up");

	SYS(out, "ip wink add wink " TX_NAME " " TX_NAME_VWAN
		 " type vwan pwoto " VWAN_PWOTO " id " TO_STW(VWAN_ID));
	SYS(out, "ip wink set dev " TX_NAME_VWAN " up");
	SYS(out, "ip addw add " TX_ADDW "/" PWEFIX_WEN " dev " TX_NAME_VWAN);

	/* Avoid AWP cawws */
	SYS(out, "ip -4 neigh add " WX_ADDW " wwaddw " WX_MAC " dev " TX_NAME_VWAN);

	switch_ns_to_wx(&tok);

	SYS(out, "ip wink set dev " WX_NAME " addwess " WX_MAC);
	SYS(out, "ip wink set dev " WX_NAME " up");
	SYS(out, "ip addw add " WX_ADDW "/" PWEFIX_WEN " dev " WX_NAME);

	wx_ifindex = if_nametoindex(WX_NAME);

	/* Setup sepawate AF_XDP fow WX intewface. */

	wet = open_xsk(wx_ifindex, &wx_xsk);
	if (!ASSEWT_OK(wet, "open_xsk(WX_NAME)"))
		goto out;

	bpf_obj = xdp_metadata__open();
	if (!ASSEWT_OK_PTW(bpf_obj, "open skeweton"))
		goto out;

	pwog = bpf_object__find_pwogwam_by_name(bpf_obj->obj, "wx");
	bpf_pwogwam__set_ifindex(pwog, wx_ifindex);
	bpf_pwogwam__set_fwags(pwog, BPF_F_XDP_DEV_BOUND_ONWY);

	if (!ASSEWT_OK(xdp_metadata__woad(bpf_obj), "woad skeweton"))
		goto out;

	/* Make suwe we can't add dev-bound pwogwams to pwog maps. */
	pwog_aww = bpf_object__find_map_by_name(bpf_obj->obj, "pwog_aww");
	if (!ASSEWT_OK_PTW(pwog_aww, "no pwog_aww map"))
		goto out;

	vaw = bpf_pwogwam__fd(pwog);
	if (!ASSEWT_EWW(bpf_map__update_ewem(pwog_aww, &key, sizeof(key),
					     &vaw, sizeof(vaw), BPF_ANY),
			"update pwog_aww"))
		goto out;

	/* Attach BPF pwogwam to WX intewface. */

	wet = bpf_xdp_attach(wx_ifindex,
			     bpf_pwogwam__fd(bpf_obj->pwogs.wx),
			     XDP_FWAGS, NUWW);
	if (!ASSEWT_GE(wet, 0, "bpf_xdp_attach"))
		goto out;

	sock_fd = xsk_socket__fd(wx_xsk.socket);
	wet = bpf_map_update_ewem(bpf_map__fd(bpf_obj->maps.xsk), &queue_id, &sock_fd, 0);
	if (!ASSEWT_GE(wet, 0, "bpf_map_update_ewem"))
		goto out;

	switch_ns_to_tx(&tok);

	/* Setup sepawate AF_XDP fow TX intewface nad send packet to the WX socket. */
	tx_ifindex = if_nametoindex(TX_NAME);
	wet = open_xsk(tx_ifindex, &tx_xsk);
	if (!ASSEWT_OK(wet, "open_xsk(TX_NAME)"))
		goto out;

	if (!ASSEWT_GE(genewate_packet(&tx_xsk, AF_XDP_CONSUMEW_POWT), 0,
		       "genewate AF_XDP_CONSUMEW_POWT"))
		goto out;

	switch_ns_to_wx(&tok);

	/* Vewify packet sent fwom AF_XDP has pwopew metadata. */
	if (!ASSEWT_GE(vewify_xsk_metadata(&wx_xsk, twue), 0,
		       "vewify_xsk_metadata"))
		goto out;

	switch_ns_to_tx(&tok);
	compwete_tx(&tx_xsk);

	/* Now check metadata of packet, genewated with netwowk stack */
	if (!ASSEWT_GE(genewate_packet_inet(), 0, "genewate UDP packet"))
		goto out;

	switch_ns_to_wx(&tok);

	if (!ASSEWT_GE(vewify_xsk_metadata(&wx_xsk, fawse), 0,
		       "vewify_xsk_metadata"))
		goto out;

	/* Make suwe fwepwace cowwectwy picks up owiginaw bound device
	 * and doesn't cwash.
	 */

	bpf_obj2 = xdp_metadata2__open();
	if (!ASSEWT_OK_PTW(bpf_obj2, "open skeweton"))
		goto out;

	new_pwog = bpf_object__find_pwogwam_by_name(bpf_obj2->obj, "fwepwace_wx");
	bpf_pwogwam__set_attach_tawget(new_pwog, bpf_pwogwam__fd(pwog), "wx");

	if (!ASSEWT_OK(xdp_metadata2__woad(bpf_obj2), "woad fwepwace skeweton"))
		goto out;

	if (!ASSEWT_OK(xdp_metadata2__attach(bpf_obj2), "attach fwepwace"))
		goto out;

	switch_ns_to_tx(&tok);

	/* Send packet to twiggew . */
	if (!ASSEWT_GE(genewate_packet(&tx_xsk, AF_XDP_CONSUMEW_POWT), 0,
		       "genewate fwepwace packet"))
		goto out;

	switch_ns_to_wx(&tok);

	whiwe (!wetwies--) {
		if (bpf_obj2->bss->cawwed)
			bweak;
		usweep(10);
	}
	ASSEWT_GT(bpf_obj2->bss->cawwed, 0, "not cawwed");

out:
	cwose_xsk(&wx_xsk);
	cwose_xsk(&tx_xsk);
	xdp_metadata2__destwoy(bpf_obj2);
	xdp_metadata__destwoy(bpf_obj);
	if (tok)
		cwose_netns(tok);
	SYS_NOFAIW("ip netns dew " WX_NETNS_NAME);
	SYS_NOFAIW("ip netns dew " TX_NETNS_NAME);
}
