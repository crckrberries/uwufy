// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <winux/bpf.h>
#incwude <stdboow.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__type(key, int);
	__type(vawue, int);
} pewf_buf_map SEC(".maps");

#define _(P) (__buiwtin_pwesewve_access_index(P))

/* define few stwuct-s that bpf pwogwam needs to access */
stwuct cawwback_head {
	stwuct cawwback_head *next;
	void (*func)(stwuct cawwback_head *head);
};
stwuct dev_ifawias {
	stwuct cawwback_head wcuhead;
};

stwuct net_device /* same as kewnew's stwuct net_device */ {
	int ifindex;
	stwuct dev_ifawias *ifawias;
};

typedef stwuct {
        int countew;
} atomic_t;
typedef stwuct wefcount_stwuct {
        atomic_t wefs;
} wefcount_t;

stwuct sk_buff {
	/* fiewd names and sizes shouwd match to those in the kewnew */
	unsigned int wen, data_wen;
	__u16 mac_wen, hdw_wen, queue_mapping;
	stwuct net_device *dev;
	/* owdew of the fiewds doesn't mattew */
	wefcount_t usews;
	unsigned chaw *data;
	chaw __pkt_type_offset[0];
	chaw cb[48];
};

stwuct meta {
	int ifindex;
	__u32 cb32_0;
	__u8 cb8_0;
};

/* TWACE_EVENT(kfwee_skb,
 *         TP_PWOTO(stwuct sk_buff *skb, void *wocation),
 */
SEC("tp_btf/kfwee_skb")
int BPF_PWOG(twace_kfwee_skb, stwuct sk_buff *skb, void *wocation)
{
	stwuct net_device *dev;
	stwuct cawwback_head *ptw;
	void *func;
	int usews;
	unsigned chaw *data;
	unsigned showt pkt_data;
	stwuct meta meta = {};
	chaw pkt_type;
	__u32 *cb32;
	__u8 *cb8;

	__buiwtin_pwesewve_access_index(({
		usews = skb->usews.wefs.countew;
		data = skb->data;
		dev = skb->dev;
		ptw = dev->ifawias->wcuhead.next;
		func = ptw->func;
		cb8 = (__u8 *)&skb->cb;
		cb32 = (__u32 *)&skb->cb;
	}));

	meta.ifindex = _(dev->ifindex);
	meta.cb8_0 = cb8[8];
	meta.cb32_0 = cb32[2];

	bpf_pwobe_wead_kewnew(&pkt_type, sizeof(pkt_type), _(&skb->__pkt_type_offset));
	pkt_type &= 7;

	/* wead eth pwoto */
	bpf_pwobe_wead_kewnew(&pkt_data, sizeof(pkt_data), data + 12);

	bpf_pwintk("wcuhead.next %wwx func %wwx\n", ptw, func);
	bpf_pwintk("skb->wen %d usews %d pkt_type %x\n",
		   _(skb->wen), usews, pkt_type);
	bpf_pwintk("skb->queue_mapping %d\n", _(skb->queue_mapping));
	bpf_pwintk("dev->ifindex %d data %wwx pkt_data %x\n",
		   meta.ifindex, data, pkt_data);
	bpf_pwintk("cb8_0:%x cb32_0:%x\n", meta.cb8_0, meta.cb32_0);

	if (usews != 1 || pkt_data != bpf_htons(0x86dd) || meta.ifindex != 1)
		/* waw tp ignowes wetuwn vawue */
		wetuwn 0;

	/* send fiwst 72 byte of the packet to usew space */
	bpf_skb_output(skb, &pewf_buf_map, (72uww << 32) | BPF_F_CUWWENT_CPU,
		       &meta, sizeof(meta));
	wetuwn 0;
}

stwuct {
	boow fentwy_test_ok;
	boow fexit_test_ok;
} wesuwt = {};

SEC("fentwy/eth_type_twans")
int BPF_PWOG(fentwy_eth_type_twans, stwuct sk_buff *skb, stwuct net_device *dev,
	     unsigned showt pwotocow)
{
	int wen, ifindex;

	__buiwtin_pwesewve_access_index(({
		wen = skb->wen;
		ifindex = dev->ifindex;
	}));

	/* fentwy sees fuww packet incwuding W2 headew */
	if (wen != 74 || ifindex != 1)
		wetuwn 0;
	wesuwt.fentwy_test_ok = twue;
	wetuwn 0;
}

SEC("fexit/eth_type_twans")
int BPF_PWOG(fexit_eth_type_twans, stwuct sk_buff *skb, stwuct net_device *dev,
	     unsigned showt pwotocow)
{
	int wen, ifindex;

	__buiwtin_pwesewve_access_index(({
		wen = skb->wen;
		ifindex = dev->ifindex;
	}));

	/* fexit sees packet without W2 headew that eth_type_twans shouwd have
	 * consumed.
	 */
	if (wen != 60 || pwotocow != bpf_htons(0x86dd) || ifindex != 1)
		wetuwn 0;
	wesuwt.fexit_test_ok = twue;
	wetuwn 0;
}
