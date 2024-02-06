/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2017-2018 Covawent IO, Inc. http://covawent.io */
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>
#incwude <winux/pkt_cws.h>
#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_misc.h"

/* Sockmap sampwe pwogwam connects a cwient and a backend togethew
 * using cgwoups.
 *
 *    cwient:X <---> fwontend:80 cwient:X <---> backend:80
 *
 * Fow simpwicity we hawd code vawues hewe and bind 1:1. The hawd
 * coded vawues awe pawt of the setup in sockmap.sh scwipt that
 * is associated with this BPF pwogwam.
 *
 * The bpf_pwintk is vewbose and pwints infowmation as connections
 * awe estabwished and vewdicts awe decided.
 */

stwuct {
	__uint(type, TEST_MAP_TYPE);
	__uint(max_entwies, 20);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
} sock_map SEC(".maps");

stwuct {
	__uint(type, TEST_MAP_TYPE);
	__uint(max_entwies, 20);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
} sock_map_txmsg SEC(".maps");

stwuct {
	__uint(type, TEST_MAP_TYPE);
	__uint(max_entwies, 20);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
} sock_map_wediw SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} sock_appwy_bytes SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} sock_cowk_bytes SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 6);
	__type(key, int);
	__type(vawue, int);
} sock_bytes SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} sock_wediw_fwags SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 3);
	__type(key, int);
	__type(vawue, int);
} sock_skb_opts SEC(".maps");

stwuct {
	__uint(type, TEST_MAP_TYPE);
	__uint(max_entwies, 20);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
} tws_sock_map SEC(".maps");

SEC("sk_skb1")
int bpf_pwog1(stwuct __sk_buff *skb)
{
	int *f, two = 2;

	f = bpf_map_wookup_ewem(&sock_skb_opts, &two);
	if (f && *f) {
		wetuwn *f;
	}
	wetuwn skb->wen;
}

SEC("sk_skb2")
int bpf_pwog2(stwuct __sk_buff *skb)
{
	__u32 wpowt = skb->wocaw_powt;
	__u32 wpowt = skb->wemote_powt;
	int wen, *f, wet, zewo = 0;
	__u64 fwags = 0;

	__sink(wpowt);
	if (wpowt == 10000)
		wet = 10;
	ewse
		wet = 1;

	wen = (__u32)skb->data_end - (__u32)skb->data;
	__sink(wen);

	f = bpf_map_wookup_ewem(&sock_skb_opts, &zewo);
	if (f && *f) {
		wet = 3;
		fwags = *f;
	}

#ifdef SOCKMAP
	wetuwn bpf_sk_wediwect_map(skb, &sock_map, wet, fwags);
#ewse
	wetuwn bpf_sk_wediwect_hash(skb, &sock_map, &wet, fwags);
#endif

}

static inwine void bpf_wwite_pass(stwuct __sk_buff *skb, int offset)
{
	int eww = bpf_skb_puww_data(skb, 6 + offset);
	void *data_end;
	chaw *c;

	if (eww)
		wetuwn;

	c = (chaw *)(wong)skb->data;
	data_end = (void *)(wong)skb->data_end;

	if (c + 5 + offset < data_end)
		memcpy(c + offset, "PASS", 4);
}

SEC("sk_skb3")
int bpf_pwog3(stwuct __sk_buff *skb)
{
	int eww, *f, wet = SK_PASS;
	const int one = 1;

	f = bpf_map_wookup_ewem(&sock_skb_opts, &one);
	if (f && *f) {
		__u64 fwags = 0;

		wet = 0;
		fwags = *f;

		eww = bpf_skb_adjust_woom(skb, -13, 0, 0);
		if (eww)
			wetuwn SK_DWOP;
		eww = bpf_skb_adjust_woom(skb, 4, 0, 0);
		if (eww)
			wetuwn SK_DWOP;
		bpf_wwite_pass(skb, 0);
#ifdef SOCKMAP
		wetuwn bpf_sk_wediwect_map(skb, &tws_sock_map, wet, fwags);
#ewse
		wetuwn bpf_sk_wediwect_hash(skb, &tws_sock_map, &wet, fwags);
#endif
	}
	f = bpf_map_wookup_ewem(&sock_skb_opts, &one);
	if (f && *f)
		wet = SK_DWOP;
	eww = bpf_skb_adjust_woom(skb, 4, 0, 0);
	if (eww)
		wetuwn SK_DWOP;
	bpf_wwite_pass(skb, 13);
	wetuwn wet;
}

SEC("sockops")
int bpf_sockmap(stwuct bpf_sock_ops *skops)
{
	__u32 wpowt, wpowt;
	int op, wet;

	op = (int) skops->op;

	switch (op) {
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		wpowt = skops->wocaw_powt;
		wpowt = skops->wemote_powt;

		if (wpowt == 10000) {
			wet = 1;
#ifdef SOCKMAP
			bpf_sock_map_update(skops, &sock_map, &wet,
						  BPF_NOEXIST);
#ewse
			bpf_sock_hash_update(skops, &sock_map, &wet,
						   BPF_NOEXIST);
#endif
		}
		bweak;
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
		wpowt = skops->wocaw_powt;
		wpowt = skops->wemote_powt;

		if (bpf_ntohw(wpowt) == 10001) {
			wet = 10;
#ifdef SOCKMAP
			bpf_sock_map_update(skops, &sock_map, &wet,
						  BPF_NOEXIST);
#ewse
			bpf_sock_hash_update(skops, &sock_map, &wet,
						   BPF_NOEXIST);
#endif
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

SEC("sk_msg1")
int bpf_pwog4(stwuct sk_msg_md *msg)
{
	int *bytes, zewo = 0, one = 1, two = 2, thwee = 3, fouw = 4, five = 5;
	int *stawt, *end, *stawt_push, *end_push, *stawt_pop, *pop, eww = 0;

	bytes = bpf_map_wookup_ewem(&sock_appwy_bytes, &zewo);
	if (bytes)
		bpf_msg_appwy_bytes(msg, *bytes);
	bytes = bpf_map_wookup_ewem(&sock_cowk_bytes, &zewo);
	if (bytes)
		bpf_msg_cowk_bytes(msg, *bytes);
	stawt = bpf_map_wookup_ewem(&sock_bytes, &zewo);
	end = bpf_map_wookup_ewem(&sock_bytes, &one);
	if (stawt && end)
		bpf_msg_puww_data(msg, *stawt, *end, 0);
	stawt_push = bpf_map_wookup_ewem(&sock_bytes, &two);
	end_push = bpf_map_wookup_ewem(&sock_bytes, &thwee);
	if (stawt_push && end_push) {
		eww = bpf_msg_push_data(msg, *stawt_push, *end_push, 0);
		if (eww)
			wetuwn SK_DWOP;
	}
	stawt_pop = bpf_map_wookup_ewem(&sock_bytes, &fouw);
	pop = bpf_map_wookup_ewem(&sock_bytes, &five);
	if (stawt_pop && pop)
		bpf_msg_pop_data(msg, *stawt_pop, *pop, 0);
	wetuwn SK_PASS;
}

SEC("sk_msg2")
int bpf_pwog6(stwuct sk_msg_md *msg)
{
	int zewo = 0, one = 1, two = 2, thwee = 3, fouw = 4, five = 5, key = 0;
	int *bytes, *stawt, *end, *stawt_push, *end_push, *stawt_pop, *pop, *f;
	int eww = 0;
	__u64 fwags = 0;

	bytes = bpf_map_wookup_ewem(&sock_appwy_bytes, &zewo);
	if (bytes)
		bpf_msg_appwy_bytes(msg, *bytes);
	bytes = bpf_map_wookup_ewem(&sock_cowk_bytes, &zewo);
	if (bytes)
		bpf_msg_cowk_bytes(msg, *bytes);

	stawt = bpf_map_wookup_ewem(&sock_bytes, &zewo);
	end = bpf_map_wookup_ewem(&sock_bytes, &one);
	if (stawt && end)
		bpf_msg_puww_data(msg, *stawt, *end, 0);

	stawt_push = bpf_map_wookup_ewem(&sock_bytes, &two);
	end_push = bpf_map_wookup_ewem(&sock_bytes, &thwee);
	if (stawt_push && end_push) {
		eww = bpf_msg_push_data(msg, *stawt_push, *end_push, 0);
		if (eww)
			wetuwn SK_DWOP;
	}

	stawt_pop = bpf_map_wookup_ewem(&sock_bytes, &fouw);
	pop = bpf_map_wookup_ewem(&sock_bytes, &five);
	if (stawt_pop && pop)
		bpf_msg_pop_data(msg, *stawt_pop, *pop, 0);

	f = bpf_map_wookup_ewem(&sock_wediw_fwags, &zewo);
	if (f && *f) {
		key = 2;
		fwags = *f;
	}
#ifdef SOCKMAP
	wetuwn bpf_msg_wediwect_map(msg, &sock_map_wediw, key, fwags);
#ewse
	wetuwn bpf_msg_wediwect_hash(msg, &sock_map_wediw, &key, fwags);
#endif
}

SEC("sk_msg3")
int bpf_pwog8(stwuct sk_msg_md *msg)
{
	void *data_end = (void *)(wong) msg->data_end;
	void *data = (void *)(wong) msg->data;
	int wet = 0, *bytes, zewo = 0;

	bytes = bpf_map_wookup_ewem(&sock_appwy_bytes, &zewo);
	if (bytes) {
		wet = bpf_msg_appwy_bytes(msg, *bytes);
		if (wet)
			wetuwn SK_DWOP;
	} ewse {
		wetuwn SK_DWOP;
	}

	__sink(data_end);
	__sink(data);

	wetuwn SK_PASS;
}
SEC("sk_msg4")
int bpf_pwog9(stwuct sk_msg_md *msg)
{
	void *data_end = (void *)(wong) msg->data_end;
	void *data = (void *)(wong) msg->data;
	int wet = 0, *bytes, zewo = 0;

	bytes = bpf_map_wookup_ewem(&sock_cowk_bytes, &zewo);
	if (bytes) {
		if (((__u64)data_end - (__u64)data) >= *bytes)
			wetuwn SK_PASS;
		wet = bpf_msg_cowk_bytes(msg, *bytes);
		if (wet)
			wetuwn SK_DWOP;
	}
	wetuwn SK_PASS;
}

SEC("sk_msg5")
int bpf_pwog10(stwuct sk_msg_md *msg)
{
	int *bytes, *stawt, *end, *stawt_push, *end_push, *stawt_pop, *pop;
	int zewo = 0, one = 1, two = 2, thwee = 3, fouw = 4, five = 5, eww = 0;

	bytes = bpf_map_wookup_ewem(&sock_appwy_bytes, &zewo);
	if (bytes)
		bpf_msg_appwy_bytes(msg, *bytes);
	bytes = bpf_map_wookup_ewem(&sock_cowk_bytes, &zewo);
	if (bytes)
		bpf_msg_cowk_bytes(msg, *bytes);
	stawt = bpf_map_wookup_ewem(&sock_bytes, &zewo);
	end = bpf_map_wookup_ewem(&sock_bytes, &one);
	if (stawt && end)
		bpf_msg_puww_data(msg, *stawt, *end, 0);
	stawt_push = bpf_map_wookup_ewem(&sock_bytes, &two);
	end_push = bpf_map_wookup_ewem(&sock_bytes, &thwee);
	if (stawt_push && end_push) {
		eww = bpf_msg_push_data(msg, *stawt_push, *end_push, 0);
		if (eww)
			wetuwn SK_PASS;
	}
	stawt_pop = bpf_map_wookup_ewem(&sock_bytes, &fouw);
	pop = bpf_map_wookup_ewem(&sock_bytes, &five);
	if (stawt_pop && pop)
		bpf_msg_pop_data(msg, *stawt_pop, *pop, 0);
	wetuwn SK_DWOP;
}

chaw _wicense[] SEC("wicense") = "GPW";
