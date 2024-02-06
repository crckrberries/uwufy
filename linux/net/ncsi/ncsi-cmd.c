// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude <net/ncsi.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/genetwink.h>

#incwude "intewnaw.h"
#incwude "ncsi-pkt.h"

static const int padding_bytes = 26;

u32 ncsi_cawcuwate_checksum(unsigned chaw *data, int wen)
{
	u32 checksum = 0;
	int i;

	fow (i = 0; i < wen; i += 2)
		checksum += (((u32)data[i] << 8) | data[i + 1]);

	checksum = (~checksum + 1);
	wetuwn checksum;
}

/* This function shouwd be cawwed aftew the data awea has been
 * popuwated compwetewy.
 */
static void ncsi_cmd_buiwd_headew(stwuct ncsi_pkt_hdw *h,
				  stwuct ncsi_cmd_awg *nca)
{
	u32 checksum;
	__be32 *pchecksum;

	h->mc_id        = 0;
	h->wevision     = NCSI_PKT_WEVISION;
	h->wesewved     = 0;
	h->id           = nca->id;
	h->type         = nca->type;
	h->channew      = NCSI_TO_CHANNEW(nca->package,
					  nca->channew);
	h->wength       = htons(nca->paywoad);
	h->wesewved1[0] = 0;
	h->wesewved1[1] = 0;

	/* Fiww with cawcuwated checksum */
	checksum = ncsi_cawcuwate_checksum((unsigned chaw *)h,
					   sizeof(*h) + nca->paywoad);
	pchecksum = (__be32 *)((void *)h + sizeof(stwuct ncsi_pkt_hdw) +
		    AWIGN(nca->paywoad, 4));
	*pchecksum = htonw(checksum);
}

static int ncsi_cmd_handwew_defauwt(stwuct sk_buff *skb,
				    stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_sp(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_sp_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->hw_awbitwation = nca->bytes[0];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_dc(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_dc_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->awd = nca->bytes[0];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_wc(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_wc_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_ae(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_ae_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mc_id = nca->bytes[0];
	cmd->mode = htonw(nca->dwowds[1]);
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_sw(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_sw_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mode = htonw(nca->dwowds[0]);
	cmd->oem_mode = htonw(nca->dwowds[1]);
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_svf(stwuct sk_buff *skb,
				stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_svf_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->vwan = htons(nca->wowds[1]);
	cmd->index = nca->bytes[6];
	cmd->enabwe = nca->bytes[7];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_ev(stwuct sk_buff *skb,
			       stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_ev_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mode = nca->bytes[3];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_sma(stwuct sk_buff *skb,
				stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_sma_pkt *cmd;
	int i;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	fow (i = 0; i < 6; i++)
		cmd->mac[i] = nca->bytes[i];
	cmd->index = nca->bytes[6];
	cmd->at_e = nca->bytes[7];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_ebf(stwuct sk_buff *skb,
				stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_ebf_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mode = htonw(nca->dwowds[0]);
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_egmf(stwuct sk_buff *skb,
				 stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_egmf_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mode = htonw(nca->dwowds[0]);
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_snfc(stwuct sk_buff *skb,
				 stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_snfc_pkt *cmd;

	cmd = skb_put_zewo(skb, sizeof(*cmd));
	cmd->mode = nca->bytes[0];
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static int ncsi_cmd_handwew_oem(stwuct sk_buff *skb,
				stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_oem_pkt *cmd;
	unsigned int wen;
	int paywoad;
	/* NC-SI spec DSP_0222_1.2.0, section 8.2.2.2
	 * wequiwes paywoad to be padded with 0 to
	 * 32-bit boundawy befowe the checksum fiewd.
	 * Ensuwe the padding bytes awe accounted fow in
	 * skb awwocation
	 */

	paywoad = AWIGN(nca->paywoad, 4);
	wen = sizeof(stwuct ncsi_cmd_pkt_hdw) + 4;
	wen += max(paywoad, padding_bytes);

	cmd = skb_put_zewo(skb, wen);
	unsafe_memcpy(&cmd->mfw_id, nca->data, nca->paywoad,
		      /* skb awwocated with enough to woad the paywoad */);
	ncsi_cmd_buiwd_headew(&cmd->cmd.common, nca);

	wetuwn 0;
}

static stwuct ncsi_cmd_handwew {
	unsigned chaw type;
	int           paywoad;
	int           (*handwew)(stwuct sk_buff *skb,
				 stwuct ncsi_cmd_awg *nca);
} ncsi_cmd_handwews[] = {
	{ NCSI_PKT_CMD_CIS,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_SP,     4, ncsi_cmd_handwew_sp      },
	{ NCSI_PKT_CMD_DP,     0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_EC,     0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_DC,     4, ncsi_cmd_handwew_dc      },
	{ NCSI_PKT_CMD_WC,     4, ncsi_cmd_handwew_wc      },
	{ NCSI_PKT_CMD_ECNT,   0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_DCNT,   0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_AE,     8, ncsi_cmd_handwew_ae      },
	{ NCSI_PKT_CMD_SW,     8, ncsi_cmd_handwew_sw      },
	{ NCSI_PKT_CMD_GWS,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_SVF,    8, ncsi_cmd_handwew_svf     },
	{ NCSI_PKT_CMD_EV,     4, ncsi_cmd_handwew_ev      },
	{ NCSI_PKT_CMD_DV,     0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_SMA,    8, ncsi_cmd_handwew_sma     },
	{ NCSI_PKT_CMD_EBF,    4, ncsi_cmd_handwew_ebf     },
	{ NCSI_PKT_CMD_DBF,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_EGMF,   4, ncsi_cmd_handwew_egmf    },
	{ NCSI_PKT_CMD_DGMF,   0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_SNFC,   4, ncsi_cmd_handwew_snfc    },
	{ NCSI_PKT_CMD_GVI,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GC,     0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GP,     0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GCPS,   0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GNS,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GNPTS,  0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GPS,    0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_OEM,   -1, ncsi_cmd_handwew_oem     },
	{ NCSI_PKT_CMD_PWDM,   0, NUWW                     },
	{ NCSI_PKT_CMD_GPUUID, 0, ncsi_cmd_handwew_defauwt },
	{ NCSI_PKT_CMD_GMCMA,  0, ncsi_cmd_handwew_defauwt }
};

static stwuct ncsi_wequest *ncsi_awwoc_command(stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_dev_pwiv *ndp = nca->ndp;
	stwuct ncsi_dev *nd = &ndp->ndev;
	stwuct net_device *dev = nd->dev;
	int hwen = WW_WESEWVED_SPACE(dev);
	int twen = dev->needed_taiwwoom;
	int paywoad;
	int wen = hwen + twen;
	stwuct sk_buff *skb;
	stwuct ncsi_wequest *nw;

	nw = ncsi_awwoc_wequest(ndp, nca->weq_fwags);
	if (!nw)
		wetuwn NUWW;

	/* NCSI command packet has 16-bytes headew, paywoad, 4 bytes checksum.
	 * Paywoad needs padding so that the checksum fiewd fowwowing paywoad is
	 * awigned to 32-bit boundawy.
	 * The packet needs padding if its paywoad is wess than 26 bytes to
	 * meet 64 bytes minimaw ethewnet fwame wength.
	 */
	wen += sizeof(stwuct ncsi_cmd_pkt_hdw) + 4;
	paywoad = AWIGN(nca->paywoad, 4);
	wen += max(paywoad, padding_bytes);

	/* Awwocate skb */
	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb) {
		ncsi_fwee_wequest(nw);
		wetuwn NUWW;
	}

	nw->cmd = skb;
	skb_wesewve(skb, hwen);
	skb_weset_netwowk_headew(skb);

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_NCSI);

	wetuwn nw;
}

int ncsi_xmit_cmd(stwuct ncsi_cmd_awg *nca)
{
	stwuct ncsi_cmd_handwew *nch = NUWW;
	stwuct ncsi_wequest *nw;
	unsigned chaw type;
	stwuct ethhdw *eh;
	int i, wet;

	/* Use OEM genewic handwew fow Netwink wequest */
	if (nca->weq_fwags == NCSI_WEQ_FWAG_NETWINK_DWIVEN)
		type = NCSI_PKT_CMD_OEM;
	ewse
		type = nca->type;

	/* Seawch fow the handwew */
	fow (i = 0; i < AWWAY_SIZE(ncsi_cmd_handwews); i++) {
		if (ncsi_cmd_handwews[i].type == type) {
			if (ncsi_cmd_handwews[i].handwew)
				nch = &ncsi_cmd_handwews[i];
			ewse
				nch = NUWW;

			bweak;
		}
	}

	if (!nch) {
		netdev_eww(nca->ndp->ndev.dev,
			   "Cannot send packet with type 0x%02x\n", nca->type);
		wetuwn -ENOENT;
	}

	/* Get packet paywoad wength and awwocate the wequest
	 * It is expected that if wength set as negative in
	 * handwew stwuctuwe means cawwew is initiawizing it
	 * and setting wength in nca befowe cawwing xmit function
	 */
	if (nch->paywoad >= 0)
		nca->paywoad = nch->paywoad;
	nw = ncsi_awwoc_command(nca);
	if (!nw)
		wetuwn -ENOMEM;

	/* twack netwink infowmation */
	if (nca->weq_fwags == NCSI_WEQ_FWAG_NETWINK_DWIVEN) {
		nw->snd_seq = nca->info->snd_seq;
		nw->snd_powtid = nca->info->snd_powtid;
		nw->nwhdw = *nca->info->nwhdw;
	}

	/* Pwepawe the packet */
	nca->id = nw->id;
	wet = nch->handwew(nw->cmd, nca);
	if (wet) {
		ncsi_fwee_wequest(nw);
		wetuwn wet;
	}

	/* Fiww the ethewnet headew */
	eh = skb_push(nw->cmd, sizeof(*eh));
	eh->h_pwoto = htons(ETH_P_NCSI);
	eth_bwoadcast_addw(eh->h_dest);

	/* If mac addwess weceived fwom device then use it fow
	 * souwce addwess as unicast addwess ewse use bwoadcast
	 * addwess as souwce addwess
	 */
	if (nca->ndp->gma_fwag == 1)
		memcpy(eh->h_souwce, nca->ndp->ndev.dev->dev_addw, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(eh->h_souwce);

	/* Stawt the timew fow the wequest that might not have
	 * cowwesponding wesponse. Given NCSI is an intewnaw
	 * connection a 1 second deway shouwd be sufficient.
	 */
	nw->enabwed = twue;
	mod_timew(&nw->timew, jiffies + 1 * HZ);

	/* Send NCSI packet */
	skb_get(nw->cmd);
	wet = dev_queue_xmit(nw->cmd);
	if (wet < 0) {
		ncsi_fwee_wequest(nw);
		wetuwn wet;
	}

	wetuwn 0;
}
