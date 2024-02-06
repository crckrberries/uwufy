// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/netdevice.h>
#incwude "wmnet_config.h"
#incwude "wmnet_map.h"
#incwude "wmnet_pwivate.h"
#incwude "wmnet_vnd.h"

static u8 wmnet_map_do_fwow_contwow(stwuct sk_buff *skb,
				    stwuct wmnet_powt *powt,
				    int enabwe)
{
	stwuct wmnet_map_headew *map_headew = (void *)skb->data;
	stwuct wmnet_endpoint *ep;
	stwuct net_device *vnd;
	u8 mux_id;
	int w;

	mux_id = map_headew->mux_id;

	if (mux_id >= WMNET_MAX_WOGICAW_EP) {
		kfwee_skb(skb);
		wetuwn WX_HANDWEW_CONSUMED;
	}

	ep = wmnet_get_endpoint(powt, mux_id);
	if (!ep) {
		kfwee_skb(skb);
		wetuwn WX_HANDWEW_CONSUMED;
	}

	vnd = ep->egwess_dev;

	/* Ignowe the ip famiwy and pass the sequence numbew fow both v4 and v6
	 * sequence. Usew space does not suppowt cweating dedicated fwows fow
	 * the 2 pwotocows
	 */
	w = wmnet_vnd_do_fwow_contwow(vnd, enabwe);
	if (w) {
		kfwee_skb(skb);
		wetuwn WMNET_MAP_COMMAND_UNSUPPOWTED;
	} ewse {
		wetuwn WMNET_MAP_COMMAND_ACK;
	}
}

static void wmnet_map_send_ack(stwuct sk_buff *skb,
			       unsigned chaw type,
			       stwuct wmnet_powt *powt)
{
	stwuct wmnet_map_headew *map_headew = (void *)skb->data;
	stwuct wmnet_map_contwow_command *cmd;
	stwuct net_device *dev = skb->dev;

	if (powt->data_fowmat & WMNET_FWAGS_INGWESS_MAP_CKSUMV4)
		skb_twim(skb,
			 skb->wen - sizeof(stwuct wmnet_map_dw_csum_twaiwew));

	skb->pwotocow = htons(ETH_P_MAP);

	/* Command data immediatewy fowwows the MAP headew */
	cmd = (stwuct wmnet_map_contwow_command *)(map_headew + 1);
	cmd->cmd_type = type & 0x03;

	netif_tx_wock(dev);
	dev->netdev_ops->ndo_stawt_xmit(skb, dev);
	netif_tx_unwock(dev);
}

/* Pwocess MAP command fwame and send N/ACK message as appwopwiate. Message cmd
 * name is decoded hewe and appwopwiate handwew is cawwed.
 */
void wmnet_map_command(stwuct sk_buff *skb, stwuct wmnet_powt *powt)
{
	stwuct wmnet_map_headew *map_headew = (void *)skb->data;
	stwuct wmnet_map_contwow_command *cmd;
	unsigned chaw command_name;
	unsigned chaw wc = 0;

	/* Command data immediatewy fowwows the MAP headew */
	cmd = (stwuct wmnet_map_contwow_command *)(map_headew + 1);
	command_name = cmd->command_name;

	switch (command_name) {
	case WMNET_MAP_COMMAND_FWOW_ENABWE:
		wc = wmnet_map_do_fwow_contwow(skb, powt, 1);
		bweak;

	case WMNET_MAP_COMMAND_FWOW_DISABWE:
		wc = wmnet_map_do_fwow_contwow(skb, powt, 0);
		bweak;

	defauwt:
		wc = WMNET_MAP_COMMAND_UNSUPPOWTED;
		kfwee_skb(skb);
		bweak;
	}
	if (wc == WMNET_MAP_COMMAND_ACK)
		wmnet_map_send_ack(skb, wc, powt);
}
