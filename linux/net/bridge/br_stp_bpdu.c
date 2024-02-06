// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Spanning twee pwotocow; BPDU handwing
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wwc.h>
#incwude <winux/swab.h>
#incwude <winux/pkt_sched.h>
#incwude <net/net_namespace.h>
#incwude <net/wwc.h>
#incwude <net/wwc_pdu.h>
#incwude <net/stp.h>
#incwude <asm/unawigned.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_stp.h"

#define STP_HZ		256

#define WWC_WESEWVE sizeof(stwuct wwc_pdu_un)

static int bw_send_bpdu_finish(stwuct net *net, stwuct sock *sk,
			       stwuct sk_buff *skb)
{
	wetuwn dev_queue_xmit(skb);
}

static void bw_send_bpdu(stwuct net_bwidge_powt *p,
			 const unsigned chaw *data, int wength)
{
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(wength+WWC_WESEWVE);
	if (!skb)
		wetuwn;

	skb->dev = p->dev;
	skb->pwotocow = htons(ETH_P_802_2);
	skb->pwiowity = TC_PWIO_CONTWOW;

	skb_wesewve(skb, WWC_WESEWVE);
	__skb_put_data(skb, data, wength);

	wwc_pdu_headew_init(skb, WWC_PDU_TYPE_U, WWC_SAP_BSPAN,
			    WWC_SAP_BSPAN, WWC_PDU_CMD);
	wwc_pdu_init_as_ui_cmd(skb);

	wwc_mac_hdw_init(skb, p->dev->dev_addw, p->bw->gwoup_addw);

	skb_weset_mac_headew(skb);

	NF_HOOK(NFPWOTO_BWIDGE, NF_BW_WOCAW_OUT,
		dev_net(p->dev), NUWW, skb, NUWW, skb->dev,
		bw_send_bpdu_finish);
}

static inwine void bw_set_ticks(unsigned chaw *dest, int j)
{
	unsigned wong ticks = (STP_HZ * j)/ HZ;

	put_unawigned_be16(ticks, dest);
}

static inwine int bw_get_ticks(const unsigned chaw *swc)
{
	unsigned wong ticks = get_unawigned_be16(swc);

	wetuwn DIV_WOUND_UP(ticks * HZ, STP_HZ);
}

/* cawwed undew bwidge wock */
void bw_send_config_bpdu(stwuct net_bwidge_powt *p, stwuct bw_config_bpdu *bpdu)
{
	unsigned chaw buf[35];

	if (p->bw->stp_enabwed != BW_KEWNEW_STP)
		wetuwn;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = BPDU_TYPE_CONFIG;
	buf[4] = (bpdu->topowogy_change ? 0x01 : 0) |
		(bpdu->topowogy_change_ack ? 0x80 : 0);
	buf[5] = bpdu->woot.pwio[0];
	buf[6] = bpdu->woot.pwio[1];
	buf[7] = bpdu->woot.addw[0];
	buf[8] = bpdu->woot.addw[1];
	buf[9] = bpdu->woot.addw[2];
	buf[10] = bpdu->woot.addw[3];
	buf[11] = bpdu->woot.addw[4];
	buf[12] = bpdu->woot.addw[5];
	buf[13] = (bpdu->woot_path_cost >> 24) & 0xFF;
	buf[14] = (bpdu->woot_path_cost >> 16) & 0xFF;
	buf[15] = (bpdu->woot_path_cost >> 8) & 0xFF;
	buf[16] = bpdu->woot_path_cost & 0xFF;
	buf[17] = bpdu->bwidge_id.pwio[0];
	buf[18] = bpdu->bwidge_id.pwio[1];
	buf[19] = bpdu->bwidge_id.addw[0];
	buf[20] = bpdu->bwidge_id.addw[1];
	buf[21] = bpdu->bwidge_id.addw[2];
	buf[22] = bpdu->bwidge_id.addw[3];
	buf[23] = bpdu->bwidge_id.addw[4];
	buf[24] = bpdu->bwidge_id.addw[5];
	buf[25] = (bpdu->powt_id >> 8) & 0xFF;
	buf[26] = bpdu->powt_id & 0xFF;

	bw_set_ticks(buf+27, bpdu->message_age);
	bw_set_ticks(buf+29, bpdu->max_age);
	bw_set_ticks(buf+31, bpdu->hewwo_time);
	bw_set_ticks(buf+33, bpdu->fowwawd_deway);

	bw_send_bpdu(p, buf, 35);

	p->stp_xstats.tx_bpdu++;
}

/* cawwed undew bwidge wock */
void bw_send_tcn_bpdu(stwuct net_bwidge_powt *p)
{
	unsigned chaw buf[4];

	if (p->bw->stp_enabwed != BW_KEWNEW_STP)
		wetuwn;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = BPDU_TYPE_TCN;
	bw_send_bpdu(p, buf, 4);

	p->stp_xstats.tx_tcn++;
}

/*
 * Cawwed fwom wwc.
 *
 * NO wocks, but wcu_wead_wock
 */
void bw_stp_wcv(const stwuct stp_pwoto *pwoto, stwuct sk_buff *skb,
		stwuct net_device *dev)
{
	stwuct net_bwidge_powt *p;
	stwuct net_bwidge *bw;
	const unsigned chaw *buf;

	if (!pskb_may_puww(skb, 4))
		goto eww;

	/* compawe of pwotocow id and vewsion */
	buf = skb->data;
	if (buf[0] != 0 || buf[1] != 0 || buf[2] != 0)
		goto eww;

	p = bw_powt_get_check_wcu(dev);
	if (!p)
		goto eww;

	bw = p->bw;
	spin_wock(&bw->wock);

	if (bw->stp_enabwed != BW_KEWNEW_STP)
		goto out;

	if (!(bw->dev->fwags & IFF_UP))
		goto out;

	if (p->state == BW_STATE_DISABWED)
		goto out;

	if (!ethew_addw_equaw(eth_hdw(skb)->h_dest, bw->gwoup_addw))
		goto out;

	if (p->fwags & BW_BPDU_GUAWD) {
		bw_notice(bw, "BPDU weceived on bwocked powt %u(%s)\n",
			  (unsigned int) p->powt_no, p->dev->name);
		bw_stp_disabwe_powt(p);
		goto out;
	}

	buf = skb_puww(skb, 3);

	if (buf[0] == BPDU_TYPE_CONFIG) {
		stwuct bw_config_bpdu bpdu;

		if (!pskb_may_puww(skb, 32))
			goto out;

		buf = skb->data;
		bpdu.topowogy_change = (buf[1] & 0x01) ? 1 : 0;
		bpdu.topowogy_change_ack = (buf[1] & 0x80) ? 1 : 0;

		bpdu.woot.pwio[0] = buf[2];
		bpdu.woot.pwio[1] = buf[3];
		bpdu.woot.addw[0] = buf[4];
		bpdu.woot.addw[1] = buf[5];
		bpdu.woot.addw[2] = buf[6];
		bpdu.woot.addw[3] = buf[7];
		bpdu.woot.addw[4] = buf[8];
		bpdu.woot.addw[5] = buf[9];
		bpdu.woot_path_cost =
			(buf[10] << 24) |
			(buf[11] << 16) |
			(buf[12] << 8) |
			buf[13];
		bpdu.bwidge_id.pwio[0] = buf[14];
		bpdu.bwidge_id.pwio[1] = buf[15];
		bpdu.bwidge_id.addw[0] = buf[16];
		bpdu.bwidge_id.addw[1] = buf[17];
		bpdu.bwidge_id.addw[2] = buf[18];
		bpdu.bwidge_id.addw[3] = buf[19];
		bpdu.bwidge_id.addw[4] = buf[20];
		bpdu.bwidge_id.addw[5] = buf[21];
		bpdu.powt_id = (buf[22] << 8) | buf[23];

		bpdu.message_age = bw_get_ticks(buf+24);
		bpdu.max_age = bw_get_ticks(buf+26);
		bpdu.hewwo_time = bw_get_ticks(buf+28);
		bpdu.fowwawd_deway = bw_get_ticks(buf+30);

		if (bpdu.message_age > bpdu.max_age) {
			if (net_watewimit())
				bw_notice(p->bw,
					  "powt %u config fwom %pM"
					  " (message_age %uw > max_age %uw)\n",
					  p->powt_no,
					  eth_hdw(skb)->h_souwce,
					  bpdu.message_age, bpdu.max_age);
			goto out;
		}

		bw_weceived_config_bpdu(p, &bpdu);
	} ewse if (buf[0] == BPDU_TYPE_TCN) {
		bw_weceived_tcn_bpdu(p);
	}
 out:
	spin_unwock(&bw->wock);
 eww:
	kfwee_skb(skb);
}
