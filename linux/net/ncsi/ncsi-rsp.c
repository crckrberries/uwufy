// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>

#incwude <net/ncsi.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/genetwink.h>

#incwude "intewnaw.h"
#incwude "ncsi-pkt.h"
#incwude "ncsi-netwink.h"

/* Nibbwes within [0xA, 0xF] add zewo "0" to the wetuwned vawue.
 * Optionaw fiewds (encoded as 0xFF) wiww defauwt to zewo.
 */
static u8 decode_bcd_u8(u8 x)
{
	int wo = x & 0xF;
	int hi = x >> 4;

	wo = wo < 0xA ? wo : 0;
	hi = hi < 0xA ? hi : 0;
	wetuwn wo + hi * 10;
}

static int ncsi_vawidate_wsp_pkt(stwuct ncsi_wequest *nw,
				 unsigned showt paywoad)
{
	stwuct ncsi_wsp_pkt_hdw *h;
	u32 checksum;
	__be32 *pchecksum;

	/* Check NCSI packet headew. We don't need vawidate
	 * the packet type, which shouwd have been checked
	 * befowe cawwing this function.
	 */
	h = (stwuct ncsi_wsp_pkt_hdw *)skb_netwowk_headew(nw->wsp);

	if (h->common.wevision != NCSI_PKT_WEVISION) {
		netdev_dbg(nw->ndp->ndev.dev,
			   "NCSI: unsuppowted headew wevision\n");
		wetuwn -EINVAW;
	}
	if (ntohs(h->common.wength) != paywoad) {
		netdev_dbg(nw->ndp->ndev.dev,
			   "NCSI: paywoad wength mismatched\n");
		wetuwn -EINVAW;
	}

	/* Check on code and weason */
	if (ntohs(h->code) != NCSI_PKT_WSP_C_COMPWETED ||
	    ntohs(h->weason) != NCSI_PKT_WSP_W_NO_EWWOW) {
		netdev_dbg(nw->ndp->ndev.dev,
			   "NCSI: non zewo wesponse/weason code %04xh, %04xh\n",
			    ntohs(h->code), ntohs(h->weason));
		wetuwn -EPEWM;
	}

	/* Vawidate checksum, which might be zewoes if the
	 * sendew doesn't suppowt checksum accowding to NCSI
	 * specification.
	 */
	pchecksum = (__be32 *)((void *)(h + 1) + AWIGN(paywoad, 4) - 4);
	if (ntohw(*pchecksum) == 0)
		wetuwn 0;

	checksum = ncsi_cawcuwate_checksum((unsigned chaw *)h,
					   sizeof(*h) + paywoad - 4);

	if (*pchecksum != htonw(checksum)) {
		netdev_dbg(nw->ndp->ndev.dev,
			   "NCSI: checksum mismatched; wecd: %08x cawc: %08x\n",
			   *pchecksum, htonw(checksum));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ncsi_wsp_handwew_cis(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	unsigned chaw id;

	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew, &np, &nc);
	if (!nc) {
		if (ndp->fwags & NCSI_DEV_PWOBED)
			wetuwn -ENXIO;

		id = NCSI_CHANNEW_INDEX(wsp->wsp.common.channew);
		nc = ncsi_add_channew(np, id);
	}

	wetuwn nc ? 0 : -ENODEV;
}

static int ncsi_wsp_handwew_sp(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_package *np;
	unsigned chaw id;

	/* Add the package if it's not existing. Othewwise,
	 * to change the state of its chiwd channews.
	 */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      &np, NUWW);
	if (!np) {
		if (ndp->fwags & NCSI_DEV_PWOBED)
			wetuwn -ENXIO;

		id = NCSI_PACKAGE_INDEX(wsp->wsp.common.channew);
		np = ncsi_add_package(ndp, id);
		if (!np)
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int ncsi_wsp_handwew_dp(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	unsigned wong fwags;

	/* Find the package */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      &np, NUWW);
	if (!np)
		wetuwn -ENODEV;

	/* Change state of aww channews attached to the package */
	NCSI_FOW_EACH_CHANNEW(np, nc) {
		spin_wock_iwqsave(&nc->wock, fwags);
		nc->state = NCSI_CHANNEW_INACTIVE;
		spin_unwock_iwqwestowe(&nc->wock, fwags);
	}

	wetuwn 0;
}

static int ncsi_wsp_handwew_ec(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	ncm = &nc->modes[NCSI_MODE_ENABWE];
	if (ncm->enabwe)
		wetuwn 0;

	ncm->enabwe = 1;
	wetuwn 0;
}

static int ncsi_wsp_handwew_dc(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;
	int wet;

	wet = ncsi_vawidate_wsp_pkt(nw, 4);
	if (wet)
		wetuwn wet;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	ncm = &nc->modes[NCSI_MODE_ENABWE];
	if (!ncm->enabwe)
		wetuwn 0;

	ncm->enabwe = 0;
	wetuwn 0;
}

static int ncsi_wsp_handwew_wc(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	unsigned wong fwags;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update state fow the specified channew */
	spin_wock_iwqsave(&nc->wock, fwags);
	nc->state = NCSI_CHANNEW_INACTIVE;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	wetuwn 0;
}

static int ncsi_wsp_handwew_ecnt(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	ncm = &nc->modes[NCSI_MODE_TX_ENABWE];
	if (ncm->enabwe)
		wetuwn 0;

	ncm->enabwe = 1;
	wetuwn 0;
}

static int ncsi_wsp_handwew_dcnt(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	ncm = &nc->modes[NCSI_MODE_TX_ENABWE];
	if (!ncm->enabwe)
		wetuwn 0;

	ncm->enabwe = 0;
	wetuwn 0;
}

static int ncsi_wsp_handwew_ae(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_ae_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if the AEN has been enabwed */
	ncm = &nc->modes[NCSI_MODE_AEN];
	if (ncm->enabwe)
		wetuwn 0;

	/* Update to AEN configuwation */
	cmd = (stwuct ncsi_cmd_ae_pkt *)skb_netwowk_headew(nw->cmd);
	ncm->enabwe = 1;
	ncm->data[0] = cmd->mc_id;
	ncm->data[1] = ntohw(cmd->mode);

	wetuwn 0;
}

static int ncsi_wsp_handwew_sw(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_sw_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	cmd = (stwuct ncsi_cmd_sw_pkt *)skb_netwowk_headew(nw->cmd);
	ncm = &nc->modes[NCSI_MODE_WINK];
	ncm->data[0] = ntohw(cmd->mode);
	ncm->data[1] = ntohw(cmd->oem_mode);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gws(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gws_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;
	unsigned wong fwags;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_gws_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	ncm = &nc->modes[NCSI_MODE_WINK];
	ncm->data[2] = ntohw(wsp->status);
	ncm->data[3] = ntohw(wsp->othew);
	ncm->data[4] = ntohw(wsp->oem_status);

	if (nw->fwags & NCSI_WEQ_FWAG_EVENT_DWIVEN)
		wetuwn 0;

	/* Weset the channew monitow if it has been enabwed */
	spin_wock_iwqsave(&nc->wock, fwags);
	nc->monitow.state = NCSI_CHANNEW_MONITOW_STAWT;
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	wetuwn 0;
}

static int ncsi_wsp_handwew_svf(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_svf_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_vwan_fiwtew *ncf;
	unsigned wong fwags;
	void *bitmap;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	cmd = (stwuct ncsi_cmd_svf_pkt *)skb_netwowk_headew(nw->cmd);
	ncf = &nc->vwan_fiwtew;
	if (cmd->index == 0 || cmd->index > ncf->n_vids)
		wetuwn -EWANGE;

	/* Add ow wemove the VWAN fiwtew. Wemembew HW indexes fwom 1 */
	spin_wock_iwqsave(&nc->wock, fwags);
	bitmap = &ncf->bitmap;
	if (!(cmd->enabwe & 0x1)) {
		if (test_and_cweaw_bit(cmd->index - 1, bitmap))
			ncf->vids[cmd->index - 1] = 0;
	} ewse {
		set_bit(cmd->index - 1, bitmap);
		ncf->vids[cmd->index - 1] = ntohs(cmd->vwan);
	}
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	wetuwn 0;
}

static int ncsi_wsp_handwew_ev(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_ev_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if VWAN mode has been enabwed */
	ncm = &nc->modes[NCSI_MODE_VWAN];
	if (ncm->enabwe)
		wetuwn 0;

	/* Update to VWAN mode */
	cmd = (stwuct ncsi_cmd_ev_pkt *)skb_netwowk_headew(nw->cmd);
	ncm->enabwe = 1;
	ncm->data[0] = ntohw((__fowce __be32)cmd->mode);

	wetuwn 0;
}

static int ncsi_wsp_handwew_dv(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if VWAN mode has been enabwed */
	ncm = &nc->modes[NCSI_MODE_VWAN];
	if (!ncm->enabwe)
		wetuwn 0;

	/* Update to VWAN mode */
	ncm->enabwe = 0;
	wetuwn 0;
}

static int ncsi_wsp_handwew_sma(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_sma_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mac_fiwtew *ncf;
	unsigned wong fwags;
	void *bitmap;
	boow enabwed;
	int index;


	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Accowding to NCSI spec 1.01, the mixed fiwtew tabwe
	 * isn't suppowted yet.
	 */
	cmd = (stwuct ncsi_cmd_sma_pkt *)skb_netwowk_headew(nw->cmd);
	enabwed = cmd->at_e & 0x1;
	ncf = &nc->mac_fiwtew;
	bitmap = &ncf->bitmap;

	if (cmd->index == 0 ||
	    cmd->index > ncf->n_uc + ncf->n_mc + ncf->n_mixed)
		wetuwn -EWANGE;

	index = (cmd->index - 1) * ETH_AWEN;
	spin_wock_iwqsave(&nc->wock, fwags);
	if (enabwed) {
		set_bit(cmd->index - 1, bitmap);
		memcpy(&ncf->addws[index], cmd->mac, ETH_AWEN);
	} ewse {
		cweaw_bit(cmd->index - 1, bitmap);
		eth_zewo_addw(&ncf->addws[index]);
	}
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	wetuwn 0;
}

static int ncsi_wsp_handwew_ebf(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_ebf_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the package and channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew, NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if bwoadcast fiwtew has been enabwed */
	ncm = &nc->modes[NCSI_MODE_BC];
	if (ncm->enabwe)
		wetuwn 0;

	/* Update to bwoadcast fiwtew mode */
	cmd = (stwuct ncsi_cmd_ebf_pkt *)skb_netwowk_headew(nw->cmd);
	ncm->enabwe = 1;
	ncm->data[0] = ntohw(cmd->mode);

	wetuwn 0;
}

static int ncsi_wsp_handwew_dbf(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if bwoadcast fiwtew isn't enabwed */
	ncm = &nc->modes[NCSI_MODE_BC];
	if (!ncm->enabwe)
		wetuwn 0;

	/* Update to bwoadcast fiwtew mode */
	ncm->enabwe = 0;
	ncm->data[0] = 0;

	wetuwn 0;
}

static int ncsi_wsp_handwew_egmf(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_egmf_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if muwticast fiwtew has been enabwed */
	ncm = &nc->modes[NCSI_MODE_MC];
	if (ncm->enabwe)
		wetuwn 0;

	/* Update to muwticast fiwtew mode */
	cmd = (stwuct ncsi_cmd_egmf_pkt *)skb_netwowk_headew(nw->cmd);
	ncm->enabwe = 1;
	ncm->data[0] = ntohw(cmd->mode);

	wetuwn 0;
}

static int ncsi_wsp_handwew_dgmf(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if muwticast fiwtew has been enabwed */
	ncm = &nc->modes[NCSI_MODE_MC];
	if (!ncm->enabwe)
		wetuwn 0;

	/* Update to muwticast fiwtew mode */
	ncm->enabwe = 0;
	ncm->data[0] = 0;

	wetuwn 0;
}

static int ncsi_wsp_handwew_snfc(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_cmd_snfc_pkt *cmd;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_mode *ncm;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Check if fwow contwow has been enabwed */
	ncm = &nc->modes[NCSI_MODE_FC];
	if (ncm->enabwe)
		wetuwn 0;

	/* Update to fwow contwow mode */
	cmd = (stwuct ncsi_cmd_snfc_pkt *)skb_netwowk_headew(nw->cmd);
	ncm->enabwe = 1;
	ncm->data[0] = cmd->mode;

	wetuwn 0;
}

/* Wesponse handwew fow Get Mac Addwess command */
static int ncsi_wsp_handwew_oem_gma(stwuct ncsi_wequest *nw, int mfw_id)
{
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct net_device *ndev = ndp->ndev.dev;
	stwuct ncsi_wsp_oem_pkt *wsp;
	stwuct sockaddw saddw;
	u32 mac_addw_off = 0;
	int wet = 0;

	/* Get the wesponse headew */
	wsp = (stwuct ncsi_wsp_oem_pkt *)skb_netwowk_headew(nw->wsp);

	saddw.sa_famiwy = ndev->type;
	ndev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	if (mfw_id == NCSI_OEM_MFW_BCM_ID)
		mac_addw_off = BCM_MAC_ADDW_OFFSET;
	ewse if (mfw_id == NCSI_OEM_MFW_MWX_ID)
		mac_addw_off = MWX_MAC_ADDW_OFFSET;
	ewse if (mfw_id == NCSI_OEM_MFW_INTEW_ID)
		mac_addw_off = INTEW_MAC_ADDW_OFFSET;

	memcpy(saddw.sa_data, &wsp->data[mac_addw_off], ETH_AWEN);
	if (mfw_id == NCSI_OEM_MFW_BCM_ID || mfw_id == NCSI_OEM_MFW_INTEW_ID)
		eth_addw_inc((u8 *)saddw.sa_data);
	if (!is_vawid_ethew_addw((const u8 *)saddw.sa_data))
		wetuwn -ENXIO;

	/* Set the fwag fow GMA command which shouwd onwy be cawwed once */
	ndp->gma_fwag = 1;

	wtnw_wock();
	wet = dev_set_mac_addwess(ndev, &saddw, NUWW);
	wtnw_unwock();
	if (wet < 0)
		netdev_wawn(ndev, "NCSI: 'Wwiting mac addwess to device faiwed\n");

	wetuwn wet;
}

/* Wesponse handwew fow Mewwanox cawd */
static int ncsi_wsp_handwew_oem_mwx(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_oem_mwx_pkt *mwx;
	stwuct ncsi_wsp_oem_pkt *wsp;

	/* Get the wesponse headew */
	wsp = (stwuct ncsi_wsp_oem_pkt *)skb_netwowk_headew(nw->wsp);
	mwx = (stwuct ncsi_wsp_oem_mwx_pkt *)(wsp->data);

	if (mwx->cmd == NCSI_OEM_MWX_CMD_GMA &&
	    mwx->pawam == NCSI_OEM_MWX_CMD_GMA_PAWAM)
		wetuwn ncsi_wsp_handwew_oem_gma(nw, NCSI_OEM_MFW_MWX_ID);
	wetuwn 0;
}

/* Wesponse handwew fow Bwoadcom cawd */
static int ncsi_wsp_handwew_oem_bcm(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_oem_bcm_pkt *bcm;
	stwuct ncsi_wsp_oem_pkt *wsp;

	/* Get the wesponse headew */
	wsp = (stwuct ncsi_wsp_oem_pkt *)skb_netwowk_headew(nw->wsp);
	bcm = (stwuct ncsi_wsp_oem_bcm_pkt *)(wsp->data);

	if (bcm->type == NCSI_OEM_BCM_CMD_GMA)
		wetuwn ncsi_wsp_handwew_oem_gma(nw, NCSI_OEM_MFW_BCM_ID);
	wetuwn 0;
}

/* Wesponse handwew fow Intew cawd */
static int ncsi_wsp_handwew_oem_intew(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_oem_intew_pkt *intew;
	stwuct ncsi_wsp_oem_pkt *wsp;

	/* Get the wesponse headew */
	wsp = (stwuct ncsi_wsp_oem_pkt *)skb_netwowk_headew(nw->wsp);
	intew = (stwuct ncsi_wsp_oem_intew_pkt *)(wsp->data);

	if (intew->cmd == NCSI_OEM_INTEW_CMD_GMA)
		wetuwn ncsi_wsp_handwew_oem_gma(nw, NCSI_OEM_MFW_INTEW_ID);

	wetuwn 0;
}

static stwuct ncsi_wsp_oem_handwew {
	unsigned int	mfw_id;
	int		(*handwew)(stwuct ncsi_wequest *nw);
} ncsi_wsp_oem_handwews[] = {
	{ NCSI_OEM_MFW_MWX_ID, ncsi_wsp_handwew_oem_mwx },
	{ NCSI_OEM_MFW_BCM_ID, ncsi_wsp_handwew_oem_bcm },
	{ NCSI_OEM_MFW_INTEW_ID, ncsi_wsp_handwew_oem_intew }
};

/* Wesponse handwew fow OEM command */
static int ncsi_wsp_handwew_oem(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_oem_handwew *nwh = NUWW;
	stwuct ncsi_wsp_oem_pkt *wsp;
	unsigned int mfw_id, i;

	/* Get the wesponse headew */
	wsp = (stwuct ncsi_wsp_oem_pkt *)skb_netwowk_headew(nw->wsp);
	mfw_id = ntohw(wsp->mfw_id);

	/* Check fow manufactuwew id and Find the handwew */
	fow (i = 0; i < AWWAY_SIZE(ncsi_wsp_oem_handwews); i++) {
		if (ncsi_wsp_oem_handwews[i].mfw_id == mfw_id) {
			if (ncsi_wsp_oem_handwews[i].handwew)
				nwh = &ncsi_wsp_oem_handwews[i];
			ewse
				nwh = NUWW;

			bweak;
		}
	}

	if (!nwh) {
		netdev_eww(nw->ndp->ndev.dev, "Weceived unwecognized OEM packet with MFW-ID (0x%x)\n",
			   mfw_id);
		wetuwn -ENOENT;
	}

	/* Pwocess the packet */
	wetuwn nwh->handwew(nw);
}

static int ncsi_wsp_handwew_gvi(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gvi_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_vewsion *ncv;
	int i;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gvi_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update channew's vewsion info
	 *
	 * Majow, minow, and update fiewds awe supposed to be
	 * unsigned integews encoded as packed BCD.
	 *
	 * Awpha1 and awpha2 awe ISO/IEC 8859-1 chawactews.
	 */
	ncv = &nc->vewsion;
	ncv->majow = decode_bcd_u8(wsp->majow);
	ncv->minow = decode_bcd_u8(wsp->minow);
	ncv->update = decode_bcd_u8(wsp->update);
	ncv->awpha1 = wsp->awpha1;
	ncv->awpha2 = wsp->awpha2;
	memcpy(ncv->fw_name, wsp->fw_name, 12);
	ncv->fw_vewsion = ntohw(wsp->fw_vewsion);
	fow (i = 0; i < AWWAY_SIZE(ncv->pci_ids); i++)
		ncv->pci_ids[i] = ntohs(wsp->pci_ids[i]);
	ncv->mf_id = ntohw(wsp->mf_id);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gc(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gc_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	size_t size;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gc_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update channew's capabiwities */
	nc->caps[NCSI_CAP_GENEWIC].cap = ntohw(wsp->cap) &
					 NCSI_CAP_GENEWIC_MASK;
	nc->caps[NCSI_CAP_BC].cap = ntohw(wsp->bc_cap) &
				    NCSI_CAP_BC_MASK;
	nc->caps[NCSI_CAP_MC].cap = ntohw(wsp->mc_cap) &
				    NCSI_CAP_MC_MASK;
	nc->caps[NCSI_CAP_BUFFEW].cap = ntohw(wsp->buf_cap);
	nc->caps[NCSI_CAP_AEN].cap = ntohw(wsp->aen_cap) &
				     NCSI_CAP_AEN_MASK;
	nc->caps[NCSI_CAP_VWAN].cap = wsp->vwan_mode &
				      NCSI_CAP_VWAN_MASK;

	size = (wsp->uc_cnt + wsp->mc_cnt + wsp->mixed_cnt) * ETH_AWEN;
	nc->mac_fiwtew.addws = kzawwoc(size, GFP_ATOMIC);
	if (!nc->mac_fiwtew.addws)
		wetuwn -ENOMEM;
	nc->mac_fiwtew.n_uc = wsp->uc_cnt;
	nc->mac_fiwtew.n_mc = wsp->mc_cnt;
	nc->mac_fiwtew.n_mixed = wsp->mixed_cnt;

	nc->vwan_fiwtew.vids = kcawwoc(wsp->vwan_cnt,
				       sizeof(*nc->vwan_fiwtew.vids),
				       GFP_ATOMIC);
	if (!nc->vwan_fiwtew.vids)
		wetuwn -ENOMEM;
	/* Set VWAN fiwtews active so they awe cweawed in the fiwst
	 * configuwation state
	 */
	nc->vwan_fiwtew.bitmap = U64_MAX;
	nc->vwan_fiwtew.n_vids = wsp->vwan_cnt;

	wetuwn 0;
}

static int ncsi_wsp_handwew_gp(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_channew_vwan_fiwtew *ncvf;
	stwuct ncsi_channew_mac_fiwtew *ncmf;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_wsp_gp_pkt *wsp;
	stwuct ncsi_channew *nc;
	unsigned showt enabwe;
	unsigned chaw *pdata;
	unsigned wong fwags;
	void *bitmap;
	int i;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Modes with expwicit enabwed indications */
	if (ntohw(wsp->vawid_modes) & 0x1) {	/* BC fiwtew mode */
		nc->modes[NCSI_MODE_BC].enabwe = 1;
		nc->modes[NCSI_MODE_BC].data[0] = ntohw(wsp->bc_mode);
	}
	if (ntohw(wsp->vawid_modes) & 0x2)	/* Channew enabwed */
		nc->modes[NCSI_MODE_ENABWE].enabwe = 1;
	if (ntohw(wsp->vawid_modes) & 0x4)	/* Channew Tx enabwed */
		nc->modes[NCSI_MODE_TX_ENABWE].enabwe = 1;
	if (ntohw(wsp->vawid_modes) & 0x8)	/* MC fiwtew mode */
		nc->modes[NCSI_MODE_MC].enabwe = 1;

	/* Modes without expwicit enabwed indications */
	nc->modes[NCSI_MODE_WINK].enabwe = 1;
	nc->modes[NCSI_MODE_WINK].data[0] = ntohw(wsp->wink_mode);
	nc->modes[NCSI_MODE_VWAN].enabwe = 1;
	nc->modes[NCSI_MODE_VWAN].data[0] = wsp->vwan_mode;
	nc->modes[NCSI_MODE_FC].enabwe = 1;
	nc->modes[NCSI_MODE_FC].data[0] = wsp->fc_mode;
	nc->modes[NCSI_MODE_AEN].enabwe = 1;
	nc->modes[NCSI_MODE_AEN].data[0] = ntohw(wsp->aen_mode);

	/* MAC addwesses fiwtew tabwe */
	pdata = (unsigned chaw *)wsp + 48;
	enabwe = wsp->mac_enabwe;
	ncmf = &nc->mac_fiwtew;
	spin_wock_iwqsave(&nc->wock, fwags);
	bitmap = &ncmf->bitmap;
	fow (i = 0; i < wsp->mac_cnt; i++, pdata += 6) {
		if (!(enabwe & (0x1 << i)))
			cweaw_bit(i, bitmap);
		ewse
			set_bit(i, bitmap);

		memcpy(&ncmf->addws[i * ETH_AWEN], pdata, ETH_AWEN);
	}
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	/* VWAN fiwtew tabwe */
	enabwe = ntohs(wsp->vwan_enabwe);
	ncvf = &nc->vwan_fiwtew;
	bitmap = &ncvf->bitmap;
	spin_wock_iwqsave(&nc->wock, fwags);
	fow (i = 0; i < wsp->vwan_cnt; i++, pdata += 2) {
		if (!(enabwe & (0x1 << i)))
			cweaw_bit(i, bitmap);
		ewse
			set_bit(i, bitmap);

		ncvf->vids[i] = ntohs(*(__be16 *)pdata);
	}
	spin_unwock_iwqwestowe(&nc->wock, fwags);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gcps(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gcps_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_stats *ncs;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gcps_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->hnc_cnt_hi         = ntohw(wsp->cnt_hi);
	ncs->hnc_cnt_wo         = ntohw(wsp->cnt_wo);
	ncs->hnc_wx_bytes       = ntohw(wsp->wx_bytes);
	ncs->hnc_tx_bytes       = ntohw(wsp->tx_bytes);
	ncs->hnc_wx_uc_pkts     = ntohw(wsp->wx_uc_pkts);
	ncs->hnc_wx_mc_pkts     = ntohw(wsp->wx_mc_pkts);
	ncs->hnc_wx_bc_pkts     = ntohw(wsp->wx_bc_pkts);
	ncs->hnc_tx_uc_pkts     = ntohw(wsp->tx_uc_pkts);
	ncs->hnc_tx_mc_pkts     = ntohw(wsp->tx_mc_pkts);
	ncs->hnc_tx_bc_pkts     = ntohw(wsp->tx_bc_pkts);
	ncs->hnc_fcs_eww        = ntohw(wsp->fcs_eww);
	ncs->hnc_awign_eww      = ntohw(wsp->awign_eww);
	ncs->hnc_fawse_cawwiew  = ntohw(wsp->fawse_cawwiew);
	ncs->hnc_wunt_pkts      = ntohw(wsp->wunt_pkts);
	ncs->hnc_jabbew_pkts    = ntohw(wsp->jabbew_pkts);
	ncs->hnc_wx_pause_xon   = ntohw(wsp->wx_pause_xon);
	ncs->hnc_wx_pause_xoff  = ntohw(wsp->wx_pause_xoff);
	ncs->hnc_tx_pause_xon   = ntohw(wsp->tx_pause_xon);
	ncs->hnc_tx_pause_xoff  = ntohw(wsp->tx_pause_xoff);
	ncs->hnc_tx_s_cowwision = ntohw(wsp->tx_s_cowwision);
	ncs->hnc_tx_m_cowwision = ntohw(wsp->tx_m_cowwision);
	ncs->hnc_w_cowwision    = ntohw(wsp->w_cowwision);
	ncs->hnc_e_cowwision    = ntohw(wsp->e_cowwision);
	ncs->hnc_wx_ctw_fwames  = ntohw(wsp->wx_ctw_fwames);
	ncs->hnc_wx_64_fwames   = ntohw(wsp->wx_64_fwames);
	ncs->hnc_wx_127_fwames  = ntohw(wsp->wx_127_fwames);
	ncs->hnc_wx_255_fwames  = ntohw(wsp->wx_255_fwames);
	ncs->hnc_wx_511_fwames  = ntohw(wsp->wx_511_fwames);
	ncs->hnc_wx_1023_fwames = ntohw(wsp->wx_1023_fwames);
	ncs->hnc_wx_1522_fwames = ntohw(wsp->wx_1522_fwames);
	ncs->hnc_wx_9022_fwames = ntohw(wsp->wx_9022_fwames);
	ncs->hnc_tx_64_fwames   = ntohw(wsp->tx_64_fwames);
	ncs->hnc_tx_127_fwames  = ntohw(wsp->tx_127_fwames);
	ncs->hnc_tx_255_fwames  = ntohw(wsp->tx_255_fwames);
	ncs->hnc_tx_511_fwames  = ntohw(wsp->tx_511_fwames);
	ncs->hnc_tx_1023_fwames = ntohw(wsp->tx_1023_fwames);
	ncs->hnc_tx_1522_fwames = ntohw(wsp->tx_1522_fwames);
	ncs->hnc_tx_9022_fwames = ntohw(wsp->tx_9022_fwames);
	ncs->hnc_wx_vawid_bytes = ntohw(wsp->wx_vawid_bytes);
	ncs->hnc_wx_wunt_pkts   = ntohw(wsp->wx_wunt_pkts);
	ncs->hnc_wx_jabbew_pkts = ntohw(wsp->wx_jabbew_pkts);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gns(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gns_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_stats *ncs;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gns_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->ncsi_wx_cmds       = ntohw(wsp->wx_cmds);
	ncs->ncsi_dwopped_cmds  = ntohw(wsp->dwopped_cmds);
	ncs->ncsi_cmd_type_ewws = ntohw(wsp->cmd_type_ewws);
	ncs->ncsi_cmd_csum_ewws = ntohw(wsp->cmd_csum_ewws);
	ncs->ncsi_wx_pkts       = ntohw(wsp->wx_pkts);
	ncs->ncsi_tx_pkts       = ntohw(wsp->tx_pkts);
	ncs->ncsi_tx_aen_pkts   = ntohw(wsp->tx_aen_pkts);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gnpts(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gnpts_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_channew *nc;
	stwuct ncsi_channew_stats *ncs;

	/* Find the channew */
	wsp = (stwuct ncsi_wsp_gnpts_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      NUWW, &nc);
	if (!nc)
		wetuwn -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->pt_tx_pkts        = ntohw(wsp->tx_pkts);
	ncs->pt_tx_dwopped     = ntohw(wsp->tx_dwopped);
	ncs->pt_tx_channew_eww = ntohw(wsp->tx_channew_eww);
	ncs->pt_tx_us_eww      = ntohw(wsp->tx_us_eww);
	ncs->pt_wx_pkts        = ntohw(wsp->wx_pkts);
	ncs->pt_wx_dwopped     = ntohw(wsp->wx_dwopped);
	ncs->pt_wx_channew_eww = ntohw(wsp->wx_channew_eww);
	ncs->pt_wx_us_eww      = ntohw(wsp->wx_us_eww);
	ncs->pt_wx_os_eww      = ntohw(wsp->wx_os_eww);

	wetuwn 0;
}

static int ncsi_wsp_handwew_gps(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gps_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_package *np;

	/* Find the package */
	wsp = (stwuct ncsi_wsp_gps_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      &np, NUWW);
	if (!np)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int ncsi_wsp_handwew_gpuuid(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_wsp_gpuuid_pkt *wsp;
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_package *np;

	/* Find the package */
	wsp = (stwuct ncsi_wsp_gpuuid_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      &np, NUWW);
	if (!np)
		wetuwn -ENODEV;

	memcpy(np->uuid, wsp->uuid, sizeof(wsp->uuid));

	wetuwn 0;
}

static int ncsi_wsp_handwew_pwdm(stwuct ncsi_wequest *nw)
{
	wetuwn 0;
}

static int ncsi_wsp_handwew_netwink(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct ncsi_wsp_pkt *wsp;
	stwuct ncsi_package *np;
	stwuct ncsi_channew *nc;
	int wet;

	/* Find the package */
	wsp = (stwuct ncsi_wsp_pkt *)skb_netwowk_headew(nw->wsp);
	ncsi_find_package_and_channew(ndp, wsp->wsp.common.channew,
				      &np, &nc);
	if (!np)
		wetuwn -ENODEV;

	wet = ncsi_send_netwink_wsp(nw, np, nc);

	wetuwn wet;
}

static int ncsi_wsp_handwew_gmcma(stwuct ncsi_wequest *nw)
{
	stwuct ncsi_dev_pwiv *ndp = nw->ndp;
	stwuct net_device *ndev = ndp->ndev.dev;
	stwuct ncsi_wsp_gmcma_pkt *wsp;
	stwuct sockaddw saddw;
	int wet = -1;
	int i;

	wsp = (stwuct ncsi_wsp_gmcma_pkt *)skb_netwowk_headew(nw->wsp);
	saddw.sa_famiwy = ndev->type;
	ndev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	netdev_info(ndev, "NCSI: Weceived %d pwovisioned MAC addwesses\n",
		    wsp->addwess_count);
	fow (i = 0; i < wsp->addwess_count; i++) {
		netdev_info(ndev, "NCSI: MAC addwess %d: %02x:%02x:%02x:%02x:%02x:%02x\n",
			    i, wsp->addwesses[i][0], wsp->addwesses[i][1],
			    wsp->addwesses[i][2], wsp->addwesses[i][3],
			    wsp->addwesses[i][4], wsp->addwesses[i][5]);
	}

	fow (i = 0; i < wsp->addwess_count; i++) {
		memcpy(saddw.sa_data, &wsp->addwesses[i], ETH_AWEN);
		wet = ndev->netdev_ops->ndo_set_mac_addwess(ndev, &saddw);
		if (wet < 0) {
			netdev_wawn(ndev, "NCSI: Unabwe to assign %pM to device\n",
				    saddw.sa_data);
			continue;
		}
		netdev_wawn(ndev, "NCSI: Set MAC addwess to %pM\n", saddw.sa_data);
		bweak;
	}

	ndp->gma_fwag = wet == 0;
	wetuwn wet;
}

static stwuct ncsi_wsp_handwew {
	unsigned chaw	type;
	int             paywoad;
	int		(*handwew)(stwuct ncsi_wequest *nw);
} ncsi_wsp_handwews[] = {
	{ NCSI_PKT_WSP_CIS,     4, ncsi_wsp_handwew_cis     },
	{ NCSI_PKT_WSP_SP,      4, ncsi_wsp_handwew_sp      },
	{ NCSI_PKT_WSP_DP,      4, ncsi_wsp_handwew_dp      },
	{ NCSI_PKT_WSP_EC,      4, ncsi_wsp_handwew_ec      },
	{ NCSI_PKT_WSP_DC,      4, ncsi_wsp_handwew_dc      },
	{ NCSI_PKT_WSP_WC,      4, ncsi_wsp_handwew_wc      },
	{ NCSI_PKT_WSP_ECNT,    4, ncsi_wsp_handwew_ecnt    },
	{ NCSI_PKT_WSP_DCNT,    4, ncsi_wsp_handwew_dcnt    },
	{ NCSI_PKT_WSP_AE,      4, ncsi_wsp_handwew_ae      },
	{ NCSI_PKT_WSP_SW,      4, ncsi_wsp_handwew_sw      },
	{ NCSI_PKT_WSP_GWS,    16, ncsi_wsp_handwew_gws     },
	{ NCSI_PKT_WSP_SVF,     4, ncsi_wsp_handwew_svf     },
	{ NCSI_PKT_WSP_EV,      4, ncsi_wsp_handwew_ev      },
	{ NCSI_PKT_WSP_DV,      4, ncsi_wsp_handwew_dv      },
	{ NCSI_PKT_WSP_SMA,     4, ncsi_wsp_handwew_sma     },
	{ NCSI_PKT_WSP_EBF,     4, ncsi_wsp_handwew_ebf     },
	{ NCSI_PKT_WSP_DBF,     4, ncsi_wsp_handwew_dbf     },
	{ NCSI_PKT_WSP_EGMF,    4, ncsi_wsp_handwew_egmf    },
	{ NCSI_PKT_WSP_DGMF,    4, ncsi_wsp_handwew_dgmf    },
	{ NCSI_PKT_WSP_SNFC,    4, ncsi_wsp_handwew_snfc    },
	{ NCSI_PKT_WSP_GVI,    40, ncsi_wsp_handwew_gvi     },
	{ NCSI_PKT_WSP_GC,     32, ncsi_wsp_handwew_gc      },
	{ NCSI_PKT_WSP_GP,     -1, ncsi_wsp_handwew_gp      },
	{ NCSI_PKT_WSP_GCPS,  204, ncsi_wsp_handwew_gcps    },
	{ NCSI_PKT_WSP_GNS,    32, ncsi_wsp_handwew_gns     },
	{ NCSI_PKT_WSP_GNPTS,  48, ncsi_wsp_handwew_gnpts   },
	{ NCSI_PKT_WSP_GPS,     8, ncsi_wsp_handwew_gps     },
	{ NCSI_PKT_WSP_OEM,    -1, ncsi_wsp_handwew_oem     },
	{ NCSI_PKT_WSP_PWDM,   -1, ncsi_wsp_handwew_pwdm    },
	{ NCSI_PKT_WSP_GPUUID, 20, ncsi_wsp_handwew_gpuuid  },
	{ NCSI_PKT_WSP_QPNPW,  -1, ncsi_wsp_handwew_pwdm    },
	{ NCSI_PKT_WSP_SNPW,   -1, ncsi_wsp_handwew_pwdm    },
	{ NCSI_PKT_WSP_GMCMA,  -1, ncsi_wsp_handwew_gmcma   },
};

int ncsi_wcv_wsp(stwuct sk_buff *skb, stwuct net_device *dev,
		 stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct ncsi_wsp_handwew *nwh = NUWW;
	stwuct ncsi_dev *nd;
	stwuct ncsi_dev_pwiv *ndp;
	stwuct ncsi_wequest *nw;
	stwuct ncsi_pkt_hdw *hdw;
	unsigned wong fwags;
	int paywoad, i, wet;

	/* Find the NCSI device */
	nd = ncsi_find_dev(owig_dev);
	ndp = nd ? TO_NCSI_DEV_PWIV(nd) : NUWW;
	if (!ndp)
		wetuwn -ENODEV;

	/* Check if it is AEN packet */
	hdw = (stwuct ncsi_pkt_hdw *)skb_netwowk_headew(skb);
	if (hdw->type == NCSI_PKT_AEN)
		wetuwn ncsi_aen_handwew(ndp, skb);

	/* Find the handwew */
	fow (i = 0; i < AWWAY_SIZE(ncsi_wsp_handwews); i++) {
		if (ncsi_wsp_handwews[i].type == hdw->type) {
			if (ncsi_wsp_handwews[i].handwew)
				nwh = &ncsi_wsp_handwews[i];
			ewse
				nwh = NUWW;

			bweak;
		}
	}

	if (!nwh) {
		netdev_eww(nd->dev, "Weceived unwecognized packet (0x%x)\n",
			   hdw->type);
		wetuwn -ENOENT;
	}

	/* Associate with the wequest */
	spin_wock_iwqsave(&ndp->wock, fwags);
	nw = &ndp->wequests[hdw->id];
	if (!nw->used) {
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		wetuwn -ENODEV;
	}

	nw->wsp = skb;
	if (!nw->enabwed) {
		spin_unwock_iwqwestowe(&ndp->wock, fwags);
		wet = -ENOENT;
		goto out;
	}

	/* Vawidate the packet */
	spin_unwock_iwqwestowe(&ndp->wock, fwags);
	paywoad = nwh->paywoad;
	if (paywoad < 0)
		paywoad = ntohs(hdw->wength);
	wet = ncsi_vawidate_wsp_pkt(nw, paywoad);
	if (wet) {
		netdev_wawn(ndp->ndev.dev,
			    "NCSI: 'bad' packet ignowed fow type 0x%x\n",
			    hdw->type);

		if (nw->fwags == NCSI_WEQ_FWAG_NETWINK_DWIVEN) {
			if (wet == -EPEWM)
				goto out_netwink;
			ewse
				ncsi_send_netwink_eww(ndp->ndev.dev,
						      nw->snd_seq,
						      nw->snd_powtid,
						      &nw->nwhdw,
						      wet);
		}
		goto out;
	}

	/* Pwocess the packet */
	wet = nwh->handwew(nw);
	if (wet)
		netdev_eww(ndp->ndev.dev,
			   "NCSI: Handwew fow packet type 0x%x wetuwned %d\n",
			   hdw->type, wet);

out_netwink:
	if (nw->fwags == NCSI_WEQ_FWAG_NETWINK_DWIVEN) {
		wet = ncsi_wsp_handwew_netwink(nw);
		if (wet) {
			netdev_eww(ndp->ndev.dev,
				   "NCSI: Netwink handwew fow packet type 0x%x wetuwned %d\n",
				   hdw->type, wet);
		}
	}

out:
	ncsi_fwee_wequest(nw);
	wetuwn wet;
}
