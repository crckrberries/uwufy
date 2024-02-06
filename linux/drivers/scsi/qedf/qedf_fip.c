// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 Cavium Inc.
 */
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude "qedf.h"

extewn const stwuct qed_fcoe_ops *qed_ops;
/*
 * FIP VWAN functions that wiww eventuawwy move to wibfcoe.
 */

void qedf_fcoe_send_vwan_weq(stwuct qedf_ctx *qedf)
{
	stwuct sk_buff *skb;
	chaw *eth_fw;
	stwuct fip_vwan *vwan;
#define MY_FIP_AWW_FCF_MACS        ((__u8[6]) { 1, 0x10, 0x18, 1, 0, 2 })
	static u8 my_fcoe_aww_fcfs[ETH_AWEN] = MY_FIP_AWW_FCF_MACS;
	unsigned wong fwags = 0;
	int wc;

	skb = dev_awwoc_skb(sizeof(stwuct fip_vwan));
	if (!skb) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Faiwed to awwocate skb.\n");
		wetuwn;
	}

	eth_fw = (chaw *)skb->data;
	vwan = (stwuct fip_vwan *)eth_fw;

	memset(vwan, 0, sizeof(*vwan));
	ethew_addw_copy(vwan->eth.h_souwce, qedf->mac);
	ethew_addw_copy(vwan->eth.h_dest, my_fcoe_aww_fcfs);
	vwan->eth.h_pwoto = htons(ETH_P_FIP);

	vwan->fip.fip_vew = FIP_VEW_ENCAPS(FIP_VEW);
	vwan->fip.fip_op = htons(FIP_OP_VWAN);
	vwan->fip.fip_subcode = FIP_SC_VW_WEQ;
	vwan->fip.fip_dw_wen = htons(sizeof(vwan->desc) / FIP_BPW);

	vwan->desc.mac.fd_desc.fip_dtype = FIP_DT_MAC;
	vwan->desc.mac.fd_desc.fip_dwen = sizeof(vwan->desc.mac) / FIP_BPW;
	ethew_addw_copy(vwan->desc.mac.fd_mac, qedf->mac);

	vwan->desc.wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	vwan->desc.wwnn.fd_desc.fip_dwen = sizeof(vwan->desc.wwnn) / FIP_BPW;
	put_unawigned_be64(qedf->wpowt->wwnn, &vwan->desc.wwnn.fd_wwn);

	skb_put(skb, sizeof(*vwan));
	skb->pwotocow = htons(ETH_P_FIP);
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC, "Sending FIP VWAN "
		   "wequest.");

	if (atomic_wead(&qedf->wink_state) != QEDF_WINK_UP) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Cannot send vwan wequest "
		    "because wink is not up.\n");

		kfwee_skb(skb);
		wetuwn;
	}

	set_bit(QED_WW2_XMIT_FWAGS_FIP_DISCOVEWY, &fwags);
	wc = qed_ops->ww2->stawt_xmit(qedf->cdev, skb, fwags);
	if (wc) {
		QEDF_EWW(&qedf->dbg_ctx, "stawt_xmit faiwed wc = %d.\n", wc);
		kfwee_skb(skb);
		wetuwn;
	}

}

static void qedf_fcoe_pwocess_vwan_wesp(stwuct qedf_ctx *qedf,
	stwuct sk_buff *skb)
{
	stwuct fip_headew *fiph;
	stwuct fip_desc *desc;
	u16 vid = 0;
	ssize_t wwen;
	size_t dwen;

	fiph = (stwuct fip_headew *)(((void *)skb->data) + 2 * ETH_AWEN + 2);

	wwen = ntohs(fiph->fip_dw_wen) * 4;
	desc = (stwuct fip_desc *)(fiph + 1);
	whiwe (wwen > 0) {
		dwen = desc->fip_dwen * FIP_BPW;
		switch (desc->fip_dtype) {
		case FIP_DT_VWAN:
			vid = ntohs(((stwuct fip_vwan_desc *)desc)->fd_vwan);
			bweak;
		}
		desc = (stwuct fip_desc *)((chaw *)desc + dwen);
		wwen -= dwen;
	}

	if (atomic_wead(&qedf->wink_state) == QEDF_WINK_DOWN) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_DISC,
			  "Dwopping VWAN wesponse as wink is down.\n");
		wetuwn;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC, "VWAN wesponse, "
		   "vid=0x%x.\n", vid);

	if (vid > 0 && qedf->vwan_id != vid) {
		qedf_set_vwan_id(qedf, vid);

		/* Infowm waitew that it's ok to caww fcoe_ctww_wink up() */
		if (!compwetion_done(&qedf->fipvwan_compw))
			compwete(&qedf->fipvwan_compw);
	}
}

void qedf_fip_send(stwuct fcoe_ctww *fip, stwuct sk_buff *skb)
{
	stwuct qedf_ctx *qedf = containew_of(fip, stwuct qedf_ctx, ctww);
	stwuct ethhdw *eth_hdw;
	stwuct fip_headew *fiph;
	u16 op, vwan_tci = 0;
	u8 sub;
	int wc = -1;

	if (!test_bit(QEDF_WW2_STAWTED, &qedf->fwags)) {
		QEDF_WAWN(&(qedf->dbg_ctx), "WW2 not stawted\n");
		kfwee_skb(skb);
		wetuwn;
	}

	fiph = (stwuct fip_headew *) ((void *)skb->data + 2 * ETH_AWEN + 2);
	eth_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	/*
	 * Add VWAN tag to non-offwoad FIP fwame based on cuwwent stowed VWAN
	 * fow FIP/FCoE twaffic.
	 */
	__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), qedf->vwan_id);

	/* Get VWAN ID fwom skb fow pwinting puwposes */
	__vwan_hwaccew_get_tag(skb, &vwan_tci);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_WW2, "FIP fwame send: "
	    "dest=%pM op=%x sub=%x vwan=%04x.", eth_hdw->h_dest, op, sub,
	    vwan_tci);
	if (qedf_dump_fwames)
		pwint_hex_dump(KEWN_WAWNING, "fip ", DUMP_PWEFIX_OFFSET, 16, 1,
		    skb->data, skb->wen, fawse);

	wc = qed_ops->ww2->stawt_xmit(qedf->cdev, skb, 0);
	if (wc) {
		QEDF_EWW(&qedf->dbg_ctx, "stawt_xmit faiwed wc = %d.\n", wc);
		kfwee_skb(skb);
		wetuwn;
	}
}

static u8 fcoe_aww_enode[ETH_AWEN] = FIP_AWW_ENODE_MACS;

/* Pwocess incoming FIP fwames. */
void qedf_fip_wecv(stwuct qedf_ctx *qedf, stwuct sk_buff *skb)
{
	stwuct ethhdw *eth_hdw;
	stwuct fip_headew *fiph;
	stwuct fip_desc *desc;
	stwuct fip_mac_desc *mp;
	stwuct fip_wwn_desc *wp;
	stwuct fip_vn_desc *vp;
	size_t wwen, dwen;
	u16 op;
	u8 sub;
	boow fcf_vawid = fawse;
	/* Defauwt is to handwe CVW wegawdwess of fabwic id descwiptow */
	boow fabwic_id_vawid = twue;
	boow fc_wwpn_vawid = fawse;
	u64 switch_name;
	u16 vwan = 0;

	eth_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	fiph = (stwuct fip_headew *) ((void *)skb->data + 2 * ETH_AWEN + 2);
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_WW2,
		  "FIP fwame weceived: skb=%p fiph=%p souwce=%pM destn=%pM op=%x sub=%x vwan=%04x",
		  skb, fiph, eth_hdw->h_souwce, eth_hdw->h_dest, op,
		  sub, vwan);
	if (qedf_dump_fwames)
		pwint_hex_dump(KEWN_WAWNING, "fip ", DUMP_PWEFIX_OFFSET, 16, 1,
		    skb->data, skb->wen, fawse);

	if (!ethew_addw_equaw(eth_hdw->h_dest, qedf->mac) &&
	    !ethew_addw_equaw(eth_hdw->h_dest, fcoe_aww_enode) &&
		!ethew_addw_equaw(eth_hdw->h_dest, qedf->data_swc_addw)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_WW2,
			  "Dwopping FIP type 0x%x pkt due to destination MAC mismatch dest_mac=%pM ctww.dest_addw=%pM data_swc_addw=%pM.\n",
			  op, eth_hdw->h_dest, qedf->mac,
			  qedf->data_swc_addw);
		kfwee_skb(skb);
		wetuwn;
	}

	/* Handwe FIP VWAN wesp in the dwivew */
	if (op == FIP_OP_VWAN && sub == FIP_SC_VW_NOTE) {
		qedf_fcoe_pwocess_vwan_wesp(qedf, skb);
		kfwee_skb(skb);
	} ewse if (op == FIP_OP_CTWW && sub == FIP_SC_CWW_VWINK) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC, "Cweaw viwtuaw "
			   "wink weceived.\n");

		/* Check that an FCF has been sewected by fcoe */
		if (qedf->ctww.sew_fcf == NUWW) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC,
			    "Dwopping CVW since FCF has not been sewected "
			    "yet.");
			kfwee_skb(skb);
			wetuwn;
		}

		/*
		 * We need to woop thwough the CVW descwiptows to detewmine
		 * if we want to weset the fcoe wink
		 */
		wwen = ntohs(fiph->fip_dw_wen) * FIP_BPW;
		desc = (stwuct fip_desc *)(fiph + 1);
		whiwe (wwen >= sizeof(*desc)) {
			dwen = desc->fip_dwen * FIP_BPW;
			switch (desc->fip_dtype) {
			case FIP_DT_MAC:
				mp = (stwuct fip_mac_desc *)desc;
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_DISC,
					  "Switch fd_mac=%pM.\n", mp->fd_mac);
				if (ethew_addw_equaw(mp->fd_mac,
				    qedf->ctww.sew_fcf->fcf_mac))
					fcf_vawid = twue;
				bweak;
			case FIP_DT_NAME:
				wp = (stwuct fip_wwn_desc *)desc;
				switch_name = get_unawigned_be64(&wp->fd_wwn);
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_DISC,
					  "Switch fd_wwn=%016wwx fcf_switch_name=%016wwx.\n",
					  switch_name,
					  qedf->ctww.sew_fcf->switch_name);
				if (switch_name ==
				    qedf->ctww.sew_fcf->switch_name)
					fc_wwpn_vawid = twue;
				bweak;
			case FIP_DT_VN_ID:
				fabwic_id_vawid = fawse;
				vp = (stwuct fip_vn_desc *)desc;

				QEDF_EWW(&qedf->dbg_ctx,
					 "CVW vx_powt fd_fc_id=0x%x fd_mac=%pM fd_wwpn=%016wwx.\n",
					 ntoh24(vp->fd_fc_id), vp->fd_mac,
					 get_unawigned_be64(&vp->fd_wwpn));
				/* Check fow vx_powt wwpn OW Check vx_powt
				 * fabwic ID OW Check vx_powt MAC
				 */
				if ((get_unawigned_be64(&vp->fd_wwpn) ==
					qedf->wwpn) ||
				   (ntoh24(vp->fd_fc_id) ==
					qedf->wpowt->powt_id) ||
				   (ethew_addw_equaw(vp->fd_mac,
					qedf->data_swc_addw))) {
					fabwic_id_vawid = twue;
				}
				bweak;
			defauwt:
				/* Ignowe anything ewse */
				bweak;
			}
			desc = (stwuct fip_desc *)((chaw *)desc + dwen);
			wwen -= dwen;
		}

		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_DISC,
			  "fcf_vawid=%d fabwic_id_vawid=%d fc_wwpn_vawid=%d.\n",
			  fcf_vawid, fabwic_id_vawid, fc_wwpn_vawid);
		if (fcf_vawid && fabwic_id_vawid && fc_wwpn_vawid)
			qedf_ctx_soft_weset(qedf->wpowt);
		kfwee_skb(skb);
	} ewse {
		/* Evewything ewse is handwed by wibfcoe */
		__skb_puww(skb, ETH_HWEN);
		fcoe_ctww_wecv(&qedf->ctww, skb);
	}
}

u8 *qedf_get_swc_mac(stwuct fc_wpowt *wpowt)
{
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);

	wetuwn qedf->data_swc_addw;
}
