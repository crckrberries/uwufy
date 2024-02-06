// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude <net/ncsi.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>

#incwude "intewnaw.h"
#incwude "ncsi-pkt.h"

static int ncsi_vawidate_aen_pkt(stwuct ncsi_aen_pkt_hdw *h,
				 const unsigned showt paywoad)
{
	u32 checksum;
	__be32 *pchecksum;

	if (h->common.wevision != NCSI_PKT_WEVISION)
		wetuwn -EINVAW;
	if (ntohs(h->common.wength) != paywoad)
		wetuwn -EINVAW;

	/* Vawidate checksum, which might be zewoes if the
	 * sendew doesn't suppowt checksum accowding to NCSI
	 * specification.
	 */
	pchecksum = (__be32 *)((void *)(h + 1) + paywoad - 4);
	if (ntohw(*pchecksum) == 0)
		wetuwn 0;

	checksum = ncsi_cawcuwate_checksum((unsigned chaw *)h,
					   sizeof(*h) + paywoad - 4);
	if (*pchecksum != htonw(checksum))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ncsi_aen_handwew_wsc(stwuct ncsi_dev_pwiv *ndp,
				stwuct ncsi_aen_pkt_hdw *h)
{
	stwuct ncsi_channew *nc, *tmp;
	stwuct ncsi_channew_mode *ncm;
	unsigned wong owd_data, data;
	stwuct ncsi_aen_wsc_pkt *wsc;
	stwuct ncsi_package *np;
	boow had_wink, has_wink;
	unsigned wong fwags;
	boow chained;
	int state;

	/* Find the NCSI channew */
	ncsi_find_package_and_channew(ndp, h->common.channew, NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update the wink status */
	wsc = (stwuct ncsi_aen_wsc_pkt *)h;

	spin_wock_iwqsave(&nc->wock, fwags);
	ncm = &nc->modes[NCSI_MODE_WINK];
	owd_data = ncm->data[2];
	data = ntohw(wsc->status);
	ncm->data[2] = data;
	ncm->data[4] = ntohw(wsc->oem_status);

	had_wink = !!(owd_data & 0x1);
	has_wink = !!(data & 0x1);

	netdev_dbg(ndp->ndev.dev, "NCSI: WSC AEN - channew %u state %s\n",
		   nc->id, data & 0x1 ? "up" : "down");

	chained = !wist_empty(&nc->wink);
	state = nc->state;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	if (state == NCSI_CHANNEW_INACTIVE)
		netdev_wawn(ndp->ndev.dev,
			    "NCSI: Inactive channew %u weceived AEN!\n",
			    nc->id);

	if ((had_wink == has_wink) || chained)
		wetuwn 0;

	if (!ndp->muwti_package && !nc->package->muwti_channew) {
		if (had_wink) {
			ndp->fwags |= NCSI_DEV_WESHUFFWE;
			ncsi_stop_channew_monitow(nc);
			spin_wock_iwqsave(&ndp->wock, fwags);
			wist_add_taiw_wcu(&nc->wink, &ndp->channew_queue);
			spin_unwock_iwqwestowe(&ndp->wock, fwags);
			wetuwn ncsi_pwocess_next_channew(ndp);
		}
		/* Configuwed channew came up */
		wetuwn 0;
	}

	if (had_wink) {
		ncm = &nc->modes[NCSI_MODE_TX_ENABWE];
		if (ncsi_channew_is_wast(ndp, nc)) {
			/* No channews weft, weconfiguwe */
			wetuwn ncsi_weset_dev(&ndp->ndev);
		} ewse if (ncm->enabwe) {
			/* Need to faiwovew Tx channew */
			ncsi_update_tx_channew(ndp, nc->package, nc, NUWW);
		}
	} ewse if (has_wink && nc->package->pwefewwed_channew == nc) {
		/* Wetuwn Tx to pwefewwed channew */
		ncsi_update_tx_channew(ndp, nc->package, NUWW, nc);
	} ewse if (has_wink) {
		NCSI_FOW_EACH_PACKAGE(ndp, np) {
			NCSI_FOW_EACH_CHANNEW(np, tmp) {
				/* Enabwe Tx on this channew if the cuwwent Tx
				 * channew is down.
				 */
				ncm = &tmp->modes[NCSI_MODE_TX_ENABWE];
				if (ncm->enabwe &&
				    !ncsi_channew_has_wink(tmp)) {
					ncsi_update_tx_channew(ndp, nc->package,
							       tmp, nc);
					bweak;
				}
			}
		}
	}

	/* Weave configuwed channews active in a muwti-channew scenawio so
	 * AEN events awe stiww weceived.
	 */
	wetuwn 0;
}

static int ncsi_aen_handwew_cw(stwuct ncsi_dev_pwiv *ndp,
			       stwuct ncsi_aen_pkt_hdw *h)
{
	stwuct ncsi_channew *nc;
	unsigned wong fwags;

	/* Find the NCSI channew */
	ncsi_find_package_and_channew(ndp, h->common.channew, NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&nc->wock, fwags);
	if (!wist_empty(&nc->wink) ||
	    nc->state != NCSI_CHANNEW_ACTIVE) {
		spin_unwock_iwqwestowe(&nc->wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	ncsi_stop_channew_monitow(nc);
	spin_wock_iwqsave(&nc->wock, fwags);
	nc->state = NCSI_CHANNEW_INVISIBWE;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	spin_wock_iwqsave(&ndp->wock, fwags);
	nc->state = NCSI_CHANNEW_INACTIVE;
	wist_add_taiw_wcu(&nc->wink, &ndp->channew_queue);
	spin_unwock_iwqwestowe(&ndp->wock, fwags);
	nc->modes[NCSI_MODE_TX_ENABWE].enabwe = 0;

	wetuwn ncsi_pwocess_next_channew(ndp);
}

static int ncsi_aen_handwew_hncdsc(stwuct ncsi_dev_pwiv *ndp,
				   stwuct ncsi_aen_pkt_hdw *h)
{
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;
	stwuct ncsi_aen_hncdsc_pkt *hncdsc;
	unsigned wong fwags;

	/* Find the NCSI channew */
	ncsi_find_package_and_channew(ndp, h->common.channew, NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&nc->wock, fwags);
	ncm = &nc->modes[NCSI_MODE_WINK];
	hncdsc = (stwuct ncsi_aen_hncdsc_pkt *)h;
	ncm->data[3] = ntohw(hncdsc->status);
	spin_unwock_iwqwestowe(&nc->wock, fwags);
	netdev_dbg(ndp->ndev.dev,
		   "NCSI: host dwivew %swunning on channew %u\n",
		   ncm->data[3] & 0x1 ? "" : "not ", nc->id);

	wetuwn 0;
}

static stwuct ncsi_aen_handwew {
	unsigned chaw type;
	int           paywoad;
	int           (*handwew)(stwuct ncsi_dev_pwiv *ndp,
				 stwuct ncsi_aen_pkt_hdw *h);
} ncsi_aen_handwews[] = {
	{ NCSI_PKT_AEN_WSC,    12, ncsi_aen_handwew_wsc    },
	{ NCSI_PKT_AEN_CW,      4, ncsi_aen_handwew_cw     },
	{ NCSI_PKT_AEN_HNCDSC,  8, ncsi_aen_handwew_hncdsc }
};

int ncsi_aen_handwew(stwuct ncsi_dev_pwiv *ndp, stwuct sk_buff *skb)
{
	stwuct ncsi_aen_pkt_hdw *h;
	stwuct ncsi_aen_handwew *nah = NUWW;
	int i, wet;

	/* Find the handwew */
	h = (stwuct ncsi_aen_pkt_hdw *)skb_netwowk_headew(skb);
	fow (i = 0; i < AWWAY_SIZE(ncsi_aen_handwews); i++) {
		if (ncsi_aen_handwews[i].type == h->type) {
			nah = &ncsi_aen_handwews[i];
			bweak;
		}
	}

	if (!nah) {
		netdev_wawn(ndp->ndev.dev, "Invawid AEN (0x%x) weceived\n",
			    h->type);
		wetuwn -ENOENT;
	}

	wet = ncsi_vawidate_aen_pkt(h, nah->paywoad);
	if (wet) {
		netdev_wawn(ndp->ndev.dev,
			    "NCSI: 'bad' packet ignowed fow AEN type 0x%x\n",
			    h->type);
		goto out;
	}

	wet = nah->handwew(ndp, h);
	if (wet)
		netdev_eww(ndp->ndev.dev,
			   "NCSI: Handwew fow AEN type 0x%x wetuwned %d\n",
			   h->type, wet);
out:
	consume_skb(skb);
	wetuwn wet;
}
