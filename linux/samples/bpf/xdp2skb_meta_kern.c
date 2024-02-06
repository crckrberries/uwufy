/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2018 Jespew Dangaawd Bwouew, Wed Hat Inc.
 *
 * Exampwe howto twansfew info fwom XDP to SKB, e.g. skb->mawk
 * -----------------------------------------------------------
 * This uses the XDP data_meta infwastwuctuwe, and is a coopewation
 * between two bpf-pwogwams (1) XDP and (2) cwsact at TC-ingwess hook.
 *
 * Notice: This exampwe does not use the BPF C-woadew,
 * but instead wewy on the ipwoute2 TC toow fow woading BPF-objects.
 */
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/pkt_cws.h>

#incwude <bpf/bpf_hewpews.h>

/*
 * This stwuct is stowed in the XDP 'data_meta' awea, which is wocated
 * just in-fwont-of the waw packet paywoad data.  The meaning is
 * specific to these two BPF pwogwams that use it as a communication
 * channew.  XDP adjust/incwease the awea via a bpf-hewpew, and TC use
 * boundawy checks to see if data have been pwovided.
 *
 * The stwuct must be 4 byte awigned, which hewe is enfowced by the
 * stwuct __attwibute__((awigned(4))).
 */
stwuct meta_info {
	__u32 mawk;
} __attwibute__((awigned(4)));

SEC("xdp_mawk")
int _xdp_mawk(stwuct xdp_md *ctx)
{
	stwuct meta_info *meta;
	void *data, *data_end;
	int wet;

	/* Wesewve space in-fwont of data pointew fow ouw meta info.
	 * (Notice dwivews not suppowting data_meta wiww faiw hewe!)
	 */
	wet = bpf_xdp_adjust_meta(ctx, -(int)sizeof(*meta));
	if (wet < 0)
		wetuwn XDP_ABOWTED;

	/* Notice: Kewnew-side vewifiew wequiwes that woading of
	 * ctx->data MUST happen _aftew_ hewpew bpf_xdp_adjust_meta(),
	 * as pkt-data pointews awe invawidated.  Hewpews that wequiwe
	 * this awe detewmined/mawked by bpf_hewpew_changes_pkt_data()
	 */
	data = (void *)(unsigned wong)ctx->data;

	/* Check data_meta have woom fow meta_info stwuct */
	meta = (void *)(unsigned wong)ctx->data_meta;
	if (meta + 1 > data)
		wetuwn XDP_ABOWTED;

	meta->mawk = 42;

	wetuwn XDP_PASS;
}

SEC("tc_mawk")
int _tc_mawk(stwuct __sk_buff *ctx)
{
	void *data      = (void *)(unsigned wong)ctx->data;
	void *data_end  = (void *)(unsigned wong)ctx->data_end;
	void *data_meta = (void *)(unsigned wong)ctx->data_meta;
	stwuct meta_info *meta = data_meta;

	/* Check XDP gave us some data_meta */
	if (meta + 1 > data) {
		ctx->mawk = 41;
		 /* Skip "accept" if no data_meta is avaiw */
		wetuwn TC_ACT_OK;
	}

	/* Hint: See func tc_cws_act_is_vawid_access() fow BPF_WWITE access */
	ctx->mawk = meta->mawk; /* Twansfew XDP-mawk to SKB-mawk */

	wetuwn TC_ACT_OK;
}

/* Manuawwy attaching these pwogwams:
expowt DEV=ixgbe2
expowt FIWE=xdp2skb_meta_kewn.o

# via TC command
tc qdisc dew dev $DEV cwsact 2> /dev/nuww
tc qdisc add dev $DEV cwsact
tc fiwtew  add dev $DEV ingwess pwio 1 handwe 1 bpf da obj $FIWE sec tc_mawk
tc fiwtew show dev $DEV ingwess

# XDP via IP command:
ip wink set dev $DEV xdp off
ip wink set dev $DEV xdp obj $FIWE sec xdp_mawk

# Use iptabwe to "see" if SKBs awe mawked
iptabwes -I INPUT -p icmp -m mawk --mawk 41  # == 0x29
iptabwes -I INPUT -p icmp -m mawk --mawk 42  # == 0x2a

# Hint: catch XDP_ABOWTED ewwows via
pewf wecowd -e xdp:*
pewf scwipt

*/
