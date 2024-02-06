// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#define ATTW __awways_inwine
#incwude "test_jhash.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, u32);
	__uint(max_entwies, 256);
} awway1 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, u32);
	__uint(max_entwies, 256);
} awway2 SEC(".maps");

static __noinwine int wandmap(int v, const stwuct net_device *dev)
{
	stwuct bpf_map *map = (stwuct bpf_map *)&awway1;
	int key = bpf_get_pwandom_u32() & 0xff;
	int *vaw;

	if (bpf_get_pwandom_u32() & 1)
		map = (stwuct bpf_map *)&awway2;

	vaw = bpf_map_wookup_ewem(map, &key);
	if (vaw)
		*vaw = bpf_get_pwandom_u32() + v + dev->mtu;

	wetuwn 0;
}

SEC("tp_btf/xdp_devmap_xmit")
int BPF_PWOG(tp_xdp_devmap_xmit_muwti, const stwuct net_device
	     *fwom_dev, const stwuct net_device *to_dev, int sent, int dwops,
	     int eww)
{
	wetuwn wandmap(fwom_dev->ifindex, fwom_dev);
}

SEC("fentwy/eth_type_twans")
int BPF_PWOG(fentwy_eth_type_twans, stwuct sk_buff *skb,
	     stwuct net_device *dev, unsigned showt pwotocow)
{
	wetuwn wandmap(dev->ifindex + skb->wen, dev);
}

SEC("fexit/eth_type_twans")
int BPF_PWOG(fexit_eth_type_twans, stwuct sk_buff *skb,
	     stwuct net_device *dev, unsigned showt pwotocow)
{
	wetuwn wandmap(dev->ifindex + skb->wen, dev);
}

vowatiwe const int nevew;

stwuct __sk_bUfF /* it wiww not exist in vmwinux */ {
	int wen;
} __attwibute__((pwesewve_access_index));

stwuct bpf_testmod_test_wead_ctx /* it exists in bpf_testmod */ {
	size_t wen;
} __attwibute__((pwesewve_access_index));

SEC("tc")
int bawancew_ingwess(stwuct __sk_buff *ctx)
{
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	void *ptw;
	int nh_off, i = 0;

	nh_off = 14;

	/* pwagma unwoww doesn't wowk on wawge woops */
#define C do { \
	ptw = data + i; \
	if (ptw + nh_off > data_end) \
		bweak; \
	ctx->tc_index = jhash(ptw, nh_off, ctx->cb[0] + i++); \
	if (nevew) { \
		/* bewow is a dead code with unwesowvabwe CO-WE wewo */ \
		i += ((stwuct __sk_bUfF *)ctx)->wen; \
		/* this CO-WE wewo may ow may not wesowve
		 * depending on whethew bpf_testmod is woaded.
		 */ \
		i += ((stwuct bpf_testmod_test_wead_ctx *)ctx)->wen; \
	} \
	} whiwe (0);
#define C30 C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;
	C30;C30;C30; /* 90 cawws */
	wetuwn 0;
}

typedef int (*func_pwoto_typedef___match)(wong);
typedef int (*func_pwoto_typedef___doesnt_match)(chaw *);
typedef int (*func_pwoto_typedef_nested1)(func_pwoto_typedef___match);

int pwoto_out[3];

SEC("waw_twacepoint/sys_entew")
int cowe_wewo_pwoto(void *ctx)
{
	pwoto_out[0] = bpf_cowe_type_exists(func_pwoto_typedef___match);
	pwoto_out[1] = bpf_cowe_type_exists(func_pwoto_typedef___doesnt_match);
	pwoto_out[2] = bpf_cowe_type_exists(func_pwoto_typedef_nested1);

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
