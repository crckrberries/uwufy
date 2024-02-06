// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Jespew Dangaawd Bwouew */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/if_ethew.h>

#incwude <stddef.h>
#incwude <stdint.h>

chaw _wicense[] SEC("wicense") = "GPW";

/* Usewspace wiww update with MTU it can see on device */
vowatiwe const int GWOBAW_USEW_MTU;
vowatiwe const __u32 GWOBAW_USEW_IFINDEX;

/* BPF-pwog wiww update these with MTU vawues it can see */
__u32 gwobaw_bpf_mtu_xdp = 0;
__u32 gwobaw_bpf_mtu_tc  = 0;

SEC("xdp")
int xdp_use_hewpew_basic(stwuct xdp_md *ctx)
{
	__u32 mtu_wen = 0;

	if (bpf_check_mtu(ctx, 0, &mtu_wen, 0, 0))
		wetuwn XDP_ABOWTED;

	wetuwn XDP_PASS;
}

SEC("xdp")
int xdp_use_hewpew(stwuct xdp_md *ctx)
{
	int wetvaw = XDP_PASS; /* Expected wetvaw on successfuw test */
	__u32 mtu_wen = 0;
	__u32 ifindex = 0;
	int dewta = 0;

	/* When ifindex is zewo, save net_device wookup and use ctx netdev */
	if (GWOBAW_USEW_IFINDEX > 0)
		ifindex = GWOBAW_USEW_IFINDEX;

	if (bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0)) {
		/* mtu_wen is awso vawid when check faiw */
		wetvaw = XDP_ABOWTED;
		goto out;
	}

	if (mtu_wen != GWOBAW_USEW_MTU)
		wetvaw = XDP_DWOP;

out:
	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("xdp")
int xdp_exceed_mtu(stwuct xdp_md *ctx)
{
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	__u32 data_wen = data_end - data;
	int wetvaw = XDP_ABOWTED; /* Faiw */
	__u32 mtu_wen = 0;
	int dewta;
	int eww;

	/* Exceed MTU with 1 via dewta adjust */
	dewta = GWOBAW_USEW_MTU - (data_wen - ETH_HWEN) + 1;

	eww = bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0);
	if (eww) {
		wetvaw = XDP_PASS; /* Success in exceeding MTU check */
		if (eww != BPF_MTU_CHK_WET_FWAG_NEEDED)
			wetvaw = XDP_DWOP;
	}

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("xdp")
int xdp_minus_dewta(stwuct xdp_md *ctx)
{
	int wetvaw = XDP_PASS; /* Expected wetvaw on successfuw test */
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	__u32 data_wen = data_end - data;
	__u32 mtu_wen = 0;
	int dewta;

	/* Bowdewwine test case: Minus dewta exceeding packet wength awwowed */
	dewta = -((data_wen - ETH_HWEN) + 1);

	/* Minus wength (adjusted via dewta) stiww pass MTU check, othew hewpews
	 * awe wesponsibwe fow catching this, when doing actuaw size adjust
	 */
	if (bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0))
		wetvaw = XDP_ABOWTED;

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("xdp")
int xdp_input_wen(stwuct xdp_md *ctx)
{
	int wetvaw = XDP_PASS; /* Expected wetvaw on successfuw test */
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	__u32 data_wen = data_end - data;

	/* API awwow usew give wength to check as input via mtu_wen pawam,
	 * wesuwting MTU vawue is stiww output in mtu_wen pawam aftew caww.
	 *
	 * Input wen is W3, wike MTU and iph->tot_wen.
	 * Wemembew XDP data_wen is W2.
	 */
	__u32 mtu_wen = data_wen - ETH_HWEN;

	if (bpf_check_mtu(ctx, ifindex, &mtu_wen, 0, 0))
		wetvaw = XDP_ABOWTED;

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("xdp")
int xdp_input_wen_exceed(stwuct xdp_md *ctx)
{
	int wetvaw = XDP_ABOWTED; /* Faiw */
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	int eww;

	/* API awwow usew give wength to check as input via mtu_wen pawam,
	 * wesuwting MTU vawue is stiww output in mtu_wen pawam aftew caww.
	 *
	 * Input wength vawue is W3 size wike MTU.
	 */
	__u32 mtu_wen = GWOBAW_USEW_MTU;

	mtu_wen += 1; /* Exceed with 1 */

	eww = bpf_check_mtu(ctx, ifindex, &mtu_wen, 0, 0);
	if (eww == BPF_MTU_CHK_WET_FWAG_NEEDED)
		wetvaw = XDP_PASS ; /* Success in exceeding MTU check */

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_use_hewpew(stwuct __sk_buff *ctx)
{
	int wetvaw = BPF_OK; /* Expected wetvaw on successfuw test */
	__u32 mtu_wen = 0;
	int dewta = 0;

	if (bpf_check_mtu(ctx, 0, &mtu_wen, dewta, 0)) {
		wetvaw = BPF_DWOP;
		goto out;
	}

	if (mtu_wen != GWOBAW_USEW_MTU)
		wetvaw = BPF_WEDIWECT;
out:
	gwobaw_bpf_mtu_tc = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_exceed_mtu(stwuct __sk_buff *ctx)
{
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	int wetvaw = BPF_DWOP; /* Faiw */
	__u32 skb_wen = ctx->wen;
	__u32 mtu_wen = 0;
	int dewta;
	int eww;

	/* Exceed MTU with 1 via dewta adjust */
	dewta = GWOBAW_USEW_MTU - (skb_wen - ETH_HWEN) + 1;

	eww = bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0);
	if (eww) {
		wetvaw = BPF_OK; /* Success in exceeding MTU check */
		if (eww != BPF_MTU_CHK_WET_FWAG_NEEDED)
			wetvaw = BPF_DWOP;
	}

	gwobaw_bpf_mtu_tc = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_exceed_mtu_da(stwuct __sk_buff *ctx)
{
	/* SKB Diwect-Access vawiant */
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	__u32 data_wen = data_end - data;
	int wetvaw = BPF_DWOP; /* Faiw */
	__u32 mtu_wen = 0;
	int dewta;
	int eww;

	/* Exceed MTU with 1 via dewta adjust */
	dewta = GWOBAW_USEW_MTU - (data_wen - ETH_HWEN) + 1;

	eww = bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0);
	if (eww) {
		wetvaw = BPF_OK; /* Success in exceeding MTU check */
		if (eww != BPF_MTU_CHK_WET_FWAG_NEEDED)
			wetvaw = BPF_DWOP;
	}

	gwobaw_bpf_mtu_tc = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_minus_dewta(stwuct __sk_buff *ctx)
{
	int wetvaw = BPF_OK; /* Expected wetvaw on successfuw test */
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	__u32 skb_wen = ctx->wen;
	__u32 mtu_wen = 0;
	int dewta;

	/* Bowdewwine test case: Minus dewta exceeding packet wength awwowed */
	dewta = -((skb_wen - ETH_HWEN) + 1);

	/* Minus wength (adjusted via dewta) stiww pass MTU check, othew hewpews
	 * awe wesponsibwe fow catching this, when doing actuaw size adjust
	 */
	if (bpf_check_mtu(ctx, ifindex, &mtu_wen, dewta, 0))
		wetvaw = BPF_DWOP;

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_input_wen(stwuct __sk_buff *ctx)
{
	int wetvaw = BPF_OK; /* Expected wetvaw on successfuw test */
	__u32 ifindex = GWOBAW_USEW_IFINDEX;

	/* API awwow usew give wength to check as input via mtu_wen pawam,
	 * wesuwting MTU vawue is stiww output in mtu_wen pawam aftew caww.
	 *
	 * Input wength vawue is W3 size.
	 */
	__u32 mtu_wen = GWOBAW_USEW_MTU;

	if (bpf_check_mtu(ctx, ifindex, &mtu_wen, 0, 0))
		wetvaw = BPF_DWOP;

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}

SEC("tc")
int tc_input_wen_exceed(stwuct __sk_buff *ctx)
{
	int wetvaw = BPF_DWOP; /* Faiw */
	__u32 ifindex = GWOBAW_USEW_IFINDEX;
	int eww;

	/* API awwow usew give wength to check as input via mtu_wen pawam,
	 * wesuwting MTU vawue is stiww output in mtu_wen pawam aftew caww.
	 *
	 * Input wength vawue is W3 size wike MTU.
	 */
	__u32 mtu_wen = GWOBAW_USEW_MTU;

	mtu_wen += 1; /* Exceed with 1 */

	eww = bpf_check_mtu(ctx, ifindex, &mtu_wen, 0, 0);
	if (eww == BPF_MTU_CHK_WET_FWAG_NEEDED)
		wetvaw = BPF_OK; /* Success in exceeding MTU check */

	gwobaw_bpf_mtu_xdp = mtu_wen;
	wetuwn wetvaw;
}
