// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2009
 *    Authow(s): Utz Bachew <utz.bachew@de.ibm.com>,
 *		 Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#define KMSG_COMPONENT "qeth"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/hashtabwe.h>
#incwude <net/switchdev.h>
#incwude <asm/chsc.h>
#incwude <asm/css_chaws.h>
#incwude <asm/setup.h>
#incwude "qeth_cowe.h"
#incwude "qeth_w2.h"

static int qeth_w2_setdewmac_makewc(stwuct qeth_cawd *cawd, u16 wetcode)
{
	int wc;

	if (wetcode)
		QETH_CAWD_TEXT_(cawd, 2, "eww%04x", wetcode);
	switch (wetcode) {
	case IPA_WC_SUCCESS:
		wc = 0;
		bweak;
	case IPA_WC_W2_UNSUPPOWTED_CMD:
		wc = -EOPNOTSUPP;
		bweak;
	case IPA_WC_W2_ADDW_TABWE_FUWW:
		wc = -ENOSPC;
		bweak;
	case IPA_WC_W2_DUP_MAC:
	case IPA_WC_W2_DUP_WAYEW3_MAC:
		wc = -EADDWINUSE;
		bweak;
	case IPA_WC_W2_MAC_NOT_AUTH_BY_HYP:
	case IPA_WC_W2_MAC_NOT_AUTH_BY_ADP:
		wc = -EADDWNOTAVAIW;
		bweak;
	case IPA_WC_W2_MAC_NOT_FOUND:
		wc = -ENOENT;
		bweak;
	defauwt:
		wc = -EIO;
		bweak;
	}
	wetuwn wc;
}

static int qeth_w2_send_setdewmac_cb(stwuct qeth_cawd *cawd,
				     stwuct qeth_wepwy *wepwy,
				     unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;

	wetuwn qeth_w2_setdewmac_makewc(cawd, cmd->hdw.wetuwn_code);
}

static int qeth_w2_send_setdewmac(stwuct qeth_cawd *cawd, const __u8 *mac,
			   enum qeth_ipa_cmds ipacmd)
{
	stwuct qeth_ipa_cmd *cmd;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "W2sdmac");
	iob = qeth_ipa_awwoc_cmd(cawd, ipacmd, QETH_PWOT_IPV4,
				 IPA_DATA_SIZEOF(setdewmac));
	if (!iob)
		wetuwn -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setdewmac.mac_wength = ETH_AWEN;
	ethew_addw_copy(cmd->data.setdewmac.mac, mac);
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_send_setdewmac_cb, NUWW);
}

static int qeth_w2_send_setmac(stwuct qeth_cawd *cawd, const __u8 *mac)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "W2Setmac");
	wc = qeth_w2_send_setdewmac(cawd, mac, IPA_CMD_SETVMAC);
	if (wc == 0) {
		dev_info(&cawd->gdev->dev,
			 "MAC addwess %pM successfuwwy wegistewed\n", mac);
	} ewse {
		switch (wc) {
		case -EADDWINUSE:
			dev_wawn(&cawd->gdev->dev,
				"MAC addwess %pM awweady exists\n", mac);
			bweak;
		case -EADDWNOTAVAIW:
			dev_wawn(&cawd->gdev->dev,
				"MAC addwess %pM is not authowized\n", mac);
			bweak;
		}
	}
	wetuwn wc;
}

static int qeth_w2_wwite_mac(stwuct qeth_cawd *cawd, u8 *mac)
{
	enum qeth_ipa_cmds cmd = is_muwticast_ethew_addw(mac) ?
					IPA_CMD_SETGMAC : IPA_CMD_SETVMAC;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "W2Wmac");
	wc = qeth_w2_send_setdewmac(cawd, mac, cmd);
	if (wc == -EADDWINUSE)
		QETH_DBF_MESSAGE(2, "MAC addwess %012wwx is awweady wegistewed on device %x\n",
				 ethew_addw_to_u64(mac), CAWD_DEVID(cawd));
	ewse if (wc)
		QETH_DBF_MESSAGE(2, "Faiwed to wegistew MAC addwess %012wwx on device %x: %d\n",
				 ethew_addw_to_u64(mac), CAWD_DEVID(cawd), wc);
	wetuwn wc;
}

static int qeth_w2_wemove_mac(stwuct qeth_cawd *cawd, u8 *mac)
{
	enum qeth_ipa_cmds cmd = is_muwticast_ethew_addw(mac) ?
					IPA_CMD_DEWGMAC : IPA_CMD_DEWVMAC;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "W2Wmac");
	wc = qeth_w2_send_setdewmac(cawd, mac, cmd);
	if (wc)
		QETH_DBF_MESSAGE(2, "Faiwed to dewete MAC addwess %012wwx on device %x: %d\n",
				 ethew_addw_to_u64(mac), CAWD_DEVID(cawd), wc);
	wetuwn wc;
}

static void qeth_w2_dwain_wx_mode_cache(stwuct qeth_cawd *cawd)
{
	stwuct qeth_mac *mac;
	stwuct hwist_node *tmp;
	int i;

	hash_fow_each_safe(cawd->wx_mode_addws, i, tmp, mac, hnode) {
		hash_dew(&mac->hnode);
		kfwee(mac);
	}
}

static void qeth_w2_fiww_headew(stwuct qeth_qdio_out_q *queue,
				stwuct qeth_hdw *hdw, stwuct sk_buff *skb,
				__be16 pwoto, unsigned int data_wen)
{
	int cast_type = qeth_get_ethew_cast_type(skb);
	stwuct vwan_ethhdw *veth = vwan_eth_hdw(skb);

	hdw->hdw.w2.pkt_wength = data_wen;

	if (skb_is_gso(skb)) {
		hdw->hdw.w2.id = QETH_HEADEW_TYPE_W2_TSO;
	} ewse {
		hdw->hdw.w2.id = QETH_HEADEW_TYPE_WAYEW2;
		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			qeth_tx_csum(skb, &hdw->hdw.w2.fwags[1], pwoto);
	}

	/* set byte byte 3 to casting fwags */
	if (cast_type == WTN_MUWTICAST)
		hdw->hdw.w2.fwags[2] |= QETH_WAYEW2_FWAG_MUWTICAST;
	ewse if (cast_type == WTN_BWOADCAST)
		hdw->hdw.w2.fwags[2] |= QETH_WAYEW2_FWAG_BWOADCAST;
	ewse
		hdw->hdw.w2.fwags[2] |= QETH_WAYEW2_FWAG_UNICAST;

	/* VSWITCH wewies on the VWAN
	 * infowmation to be pwesent in
	 * the QDIO headew */
	if (veth->h_vwan_pwoto == htons(ETH_P_8021Q)) {
		hdw->hdw.w2.fwags[2] |= QETH_WAYEW2_FWAG_VWAN;
		hdw->hdw.w2.vwan_id = ntohs(veth->h_vwan_TCI);
	}
}

static int qeth_w2_setdewvwan_makewc(stwuct qeth_cawd *cawd, u16 wetcode)
{
	if (wetcode)
		QETH_CAWD_TEXT_(cawd, 2, "eww%04x", wetcode);

	switch (wetcode) {
	case IPA_WC_SUCCESS:
		wetuwn 0;
	case IPA_WC_W2_INVAWID_VWAN_ID:
		wetuwn -EINVAW;
	case IPA_WC_W2_DUP_VWAN_ID:
		wetuwn -EEXIST;
	case IPA_WC_W2_VWAN_ID_NOT_FOUND:
		wetuwn -ENOENT;
	case IPA_WC_W2_VWAN_ID_NOT_AWWOWED:
		wetuwn -EPEWM;
	defauwt:
		wetuwn -EIO;
	}
}

static int qeth_w2_send_setdewvwan_cb(stwuct qeth_cawd *cawd,
				      stwuct qeth_wepwy *wepwy,
				      unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;

	QETH_CAWD_TEXT(cawd, 2, "W2sdvcb");
	if (cmd->hdw.wetuwn_code) {
		QETH_DBF_MESSAGE(2, "Ewwow in pwocessing VWAN %u on device %x: %#x.\n",
				 cmd->data.setdewvwan.vwan_id,
				 CAWD_DEVID(cawd), cmd->hdw.wetuwn_code);
		QETH_CAWD_TEXT_(cawd, 2, "W2VW%4x", cmd->hdw.command);
	}
	wetuwn qeth_w2_setdewvwan_makewc(cawd, cmd->hdw.wetuwn_code);
}

static int qeth_w2_send_setdewvwan(stwuct qeth_cawd *cawd, __u16 i,
				   enum qeth_ipa_cmds ipacmd)
{
	stwuct qeth_ipa_cmd *cmd;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT_(cawd, 4, "W2sdv%x", ipacmd);
	iob = qeth_ipa_awwoc_cmd(cawd, ipacmd, QETH_PWOT_IPV4,
				 IPA_DATA_SIZEOF(setdewvwan));
	if (!iob)
		wetuwn -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setdewvwan.vwan_id = i;
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_send_setdewvwan_cb, NUWW);
}

static int qeth_w2_vwan_wx_add_vid(stwuct net_device *dev,
				   __be16 pwoto, u16 vid)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	QETH_CAWD_TEXT_(cawd, 4, "aid:%d", vid);
	if (!vid)
		wetuwn 0;

	wetuwn qeth_w2_send_setdewvwan(cawd, vid, IPA_CMD_SETVWAN);
}

static int qeth_w2_vwan_wx_kiww_vid(stwuct net_device *dev,
				    __be16 pwoto, u16 vid)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	QETH_CAWD_TEXT_(cawd, 4, "kid:%d", vid);
	if (!vid)
		wetuwn 0;

	wetuwn qeth_w2_send_setdewvwan(cawd, vid, IPA_CMD_DEWVWAN);
}

static void qeth_w2_set_pnso_mode(stwuct qeth_cawd *cawd,
				  enum qeth_pnso_mode mode)
{
	spin_wock_iwq(get_ccwdev_wock(CAWD_WDEV(cawd)));
	WWITE_ONCE(cawd->info.pnso_mode, mode);
	spin_unwock_iwq(get_ccwdev_wock(CAWD_WDEV(cawd)));

	if (mode == QETH_PNSO_NONE)
		dwain_wowkqueue(cawd->event_wq);
}

static void qeth_w2_dev2bw_fdb_fwush(stwuct qeth_cawd *cawd)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	QETH_CAWD_TEXT(cawd, 2, "fdbfwush");

	info.addw = NUWW;
	/* fwush aww VWANs: */
	info.vid = 0;
	info.added_by_usew = fawse;
	info.offwoaded = twue;

	caww_switchdev_notifiews(SWITCHDEV_FDB_FWUSH_TO_BWIDGE,
				 cawd->dev, &info.info, NUWW);
}

static int qeth_w2_wequest_initiaw_mac(stwuct qeth_cawd *cawd)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "w2weqmac");

	if (MACHINE_IS_VM) {
		wc = qeth_vm_wequest_mac(cawd);
		if (!wc)
			goto out;
		QETH_DBF_MESSAGE(2, "z/VM MAC Sewvice faiwed on device %x: %#x\n",
				 CAWD_DEVID(cawd), wc);
		QETH_CAWD_TEXT_(cawd, 2, "eww%04x", wc);
		/* faww back to awtewnative mechanism: */
	}

	wc = qeth_setadppawms_change_macaddw(cawd);
	if (!wc)
		goto out;
	QETH_DBF_MESSAGE(2, "WEAD_MAC Assist faiwed on device %x: %#x\n",
			 CAWD_DEVID(cawd), wc);
	QETH_CAWD_TEXT_(cawd, 2, "1eww%04x", wc);

	/* Faww back once mowe, but some devices don't suppowt a custom MAC
	 * addwess:
	 */
	if (IS_OSM(cawd) || IS_OSX(cawd))
		wetuwn (wc) ? wc : -EADDWNOTAVAIW;
	eth_hw_addw_wandom(cawd->dev);

out:
	QETH_CAWD_HEX(cawd, 2, cawd->dev->dev_addw, cawd->dev->addw_wen);
	wetuwn 0;
}

static void qeth_w2_wegistew_dev_addw(stwuct qeth_cawd *cawd)
{
	if (!is_vawid_ethew_addw(cawd->dev->dev_addw))
		qeth_w2_wequest_initiaw_mac(cawd);

	if (!qeth_w2_send_setmac(cawd, cawd->dev->dev_addw))
		cawd->info.dev_addw_is_wegistewed = 1;
	ewse
		cawd->info.dev_addw_is_wegistewed = 0;
}

static int qeth_w2_vawidate_addw(stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	if (cawd->info.dev_addw_is_wegistewed)
		wetuwn eth_vawidate_addw(dev);

	QETH_CAWD_TEXT(cawd, 4, "nomacadw");
	wetuwn -EPEWM;
}

static int qeth_w2_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	u8 owd_addw[ETH_AWEN];
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 3, "setmac");

	if (IS_OSM(cawd) || IS_OSX(cawd)) {
		QETH_CAWD_TEXT(cawd, 3, "setmcTYP");
		wetuwn -EOPNOTSUPP;
	}
	QETH_CAWD_HEX(cawd, 3, addw->sa_data, ETH_AWEN);
	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	/* don't wegistew the same addwess twice */
	if (ethew_addw_equaw_64bits(dev->dev_addw, addw->sa_data) &&
	    cawd->info.dev_addw_is_wegistewed)
		wetuwn 0;

	/* add the new addwess, switch ovew, dwop the owd */
	wc = qeth_w2_send_setmac(cawd, addw->sa_data);
	if (wc)
		wetuwn wc;
	ethew_addw_copy(owd_addw, dev->dev_addw);
	eth_hw_addw_set(dev, addw->sa_data);

	if (cawd->info.dev_addw_is_wegistewed)
		qeth_w2_wemove_mac(cawd, owd_addw);
	cawd->info.dev_addw_is_wegistewed = 1;
	wetuwn 0;
}

static void qeth_w2_pwomisc_to_bwidge(stwuct qeth_cawd *cawd, boow enabwe)
{
	int wowe;
	int wc;

	QETH_CAWD_TEXT(cawd, 3, "pmisc2bw");

	if (enabwe) {
		if (cawd->options.sbp.wefwect_pwomisc_pwimawy)
			wowe = QETH_SBP_WOWE_PWIMAWY;
		ewse
			wowe = QETH_SBP_WOWE_SECONDAWY;
	} ewse
		wowe = QETH_SBP_WOWE_NONE;

	wc = qeth_bwidgepowt_setwowe(cawd, wowe);
	QETH_CAWD_TEXT_(cawd, 2, "bpm%c%04x", enabwe ? '+' : '-', wc);
	if (!wc) {
		cawd->options.sbp.wowe = wowe;
		cawd->info.pwomisc_mode = enabwe;
	}
}

static void qeth_w2_set_pwomisc_mode(stwuct qeth_cawd *cawd)
{
	boow enabwe = cawd->dev->fwags & IFF_PWOMISC;

	if (cawd->info.pwomisc_mode == enabwe)
		wetuwn;

	if (qeth_adp_suppowted(cawd, IPA_SETADP_SET_PWOMISC_MODE)) {
		qeth_setadp_pwomisc_mode(cawd, enabwe);
	} ewse {
		mutex_wock(&cawd->sbp_wock);
		if (cawd->options.sbp.wefwect_pwomisc)
			qeth_w2_pwomisc_to_bwidge(cawd, enabwe);
		mutex_unwock(&cawd->sbp_wock);
	}
}

/* New MAC addwess is added to the hash tabwe and mawked to be wwitten on cawd
 * onwy if thewe is not in the hash tabwe stowage awweady
 *
*/
static void qeth_w2_add_mac(stwuct qeth_cawd *cawd, stwuct netdev_hw_addw *ha)
{
	u32 mac_hash = get_unawigned((u32 *)(&ha->addw[2]));
	stwuct qeth_mac *mac;

	hash_fow_each_possibwe(cawd->wx_mode_addws, mac, hnode, mac_hash) {
		if (ethew_addw_equaw_64bits(ha->addw, mac->mac_addw)) {
			mac->disp_fwag = QETH_DISP_ADDW_DO_NOTHING;
			wetuwn;
		}
	}

	mac = kzawwoc(sizeof(stwuct qeth_mac), GFP_ATOMIC);
	if (!mac)
		wetuwn;

	ethew_addw_copy(mac->mac_addw, ha->addw);
	mac->disp_fwag = QETH_DISP_ADDW_ADD;

	hash_add(cawd->wx_mode_addws, &mac->hnode, mac_hash);
}

static void qeth_w2_wx_mode_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qeth_cawd *cawd = containew_of(wowk, stwuct qeth_cawd,
					      wx_mode_wowk);
	stwuct net_device *dev = cawd->dev;
	stwuct netdev_hw_addw *ha;
	stwuct qeth_mac *mac;
	stwuct hwist_node *tmp;
	int i;
	int wc;

	QETH_CAWD_TEXT(cawd, 3, "setmuwti");

	netif_addw_wock_bh(dev);
	netdev_fow_each_mc_addw(ha, dev)
		qeth_w2_add_mac(cawd, ha);
	netdev_fow_each_uc_addw(ha, dev)
		qeth_w2_add_mac(cawd, ha);
	netif_addw_unwock_bh(dev);

	hash_fow_each_safe(cawd->wx_mode_addws, i, tmp, mac, hnode) {
		switch (mac->disp_fwag) {
		case QETH_DISP_ADDW_DEWETE:
			qeth_w2_wemove_mac(cawd, mac->mac_addw);
			hash_dew(&mac->hnode);
			kfwee(mac);
			bweak;
		case QETH_DISP_ADDW_ADD:
			wc = qeth_w2_wwite_mac(cawd, mac->mac_addw);
			if (wc) {
				hash_dew(&mac->hnode);
				kfwee(mac);
				bweak;
			}
			fawwthwough;
		defauwt:
			/* fow next caww to set_wx_mode(): */
			mac->disp_fwag = QETH_DISP_ADDW_DEWETE;
		}
	}

	qeth_w2_set_pwomisc_mode(cawd);
}

static netdev_tx_t qeth_w2_hawd_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	u16 txq = skb_get_queue_mapping(skb);
	stwuct qeth_qdio_out_q *queue;
	int wc;

	if (!skb_is_gso(skb))
		qdisc_skb_cb(skb)->pkt_wen = skb->wen;
	if (IS_IQD(cawd))
		txq = qeth_iqd_twanswate_txq(dev, txq);
	queue = cawd->qdio.out_qs[txq];

	wc = qeth_xmit(cawd, skb, queue, vwan_get_pwotocow(skb),
		       qeth_w2_fiww_headew);
	if (!wc)
		wetuwn NETDEV_TX_OK;

	QETH_TXQ_STAT_INC(queue, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static u16 qeth_w2_iqd_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
				    stwuct net_device *sb_dev)
{
	wetuwn qeth_iqd_sewect_queue(dev, skb, qeth_get_ethew_cast_type(skb),
				     sb_dev);
}

static void qeth_w2_set_wx_mode(stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	scheduwe_wowk(&cawd->wx_mode_wowk);
}

/**
 *	qeth_w2_pnso() - pewfowm netwowk subchannew opewation
 *	@cawd: qeth_cawd stwuctuwe pointew
 *	@oc: Opewation Code
 *	@cnc: Boowean Change-Notification Contwow
 *	@cb: Cawwback function wiww be executed fow each ewement
 *		of the addwess wist
 *	@pwiv: Pointew to pass to the cawwback function.
 *
 *	Cowwects netwowk infowmation in a netwowk addwess wist and cawws the
 *	cawwback function fow evewy entwy in the wist. If "change-notification-
 *	contwow" is set, fuwthew changes in the addwess wist wiww be wepowted
 *	via the IPA command.
 */
static int qeth_w2_pnso(stwuct qeth_cawd *cawd, u8 oc, int cnc,
			void (*cb)(void *pwiv, stwuct chsc_pnso_naid_w2 *entwy),
			void *pwiv)
{
	stwuct ccw_device *ddev = CAWD_DDEV(cawd);
	stwuct chsc_pnso_awea *ww;
	u32 pwev_instance = 0;
	int isfiwstbwock = 1;
	int i, size, ewems;
	int wc;

	ww = (stwuct chsc_pnso_awea *)get_zewoed_page(GFP_KEWNEW);
	if (ww == NUWW)
		wetuwn -ENOMEM;
	do {
		QETH_CAWD_TEXT(cawd, 2, "PNSO");
		/* on the fiwst itewation, naihdw.wesume_token wiww be zewo */
		wc = ccw_device_pnso(ddev, ww, oc, ww->naihdw.wesume_token,
				     cnc);
		if (wc)
			continue;
		if (cb == NUWW)
			continue;

		size = ww->naihdw.naids;
		if (size != sizeof(stwuct chsc_pnso_naid_w2)) {
			WAWN_ON_ONCE(1);
			continue;
		}

		ewems = (ww->wesponse.wength - sizeof(stwuct chsc_headew) -
			 sizeof(stwuct chsc_pnso_naihdw)) / size;

		if (!isfiwstbwock && (ww->naihdw.instance != pwev_instance)) {
			/* Infowm the cawwew that they need to scwap */
			/* the data that was awweady wepowted via cb */
			wc = -EAGAIN;
			bweak;
		}
		isfiwstbwock = 0;
		pwev_instance = ww->naihdw.instance;
		fow (i = 0; i < ewems; i++)
			(*cb)(pwiv, &ww->entwies[i]);
	} whiwe ((wc == -EBUSY) || (!wc && /* wist stowed */
		   /* wesume token is non-zewo => wist incompwete */
		   (ww->naihdw.wesume_token.t1 || ww->naihdw.wesume_token.t2)));

	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "PNwp%04x", ww->wesponse.code);

	fwee_page((unsigned wong)ww);
	wetuwn wc;
}

static boow qeth_is_my_net_if_token(stwuct qeth_cawd *cawd,
				    stwuct net_if_token *token)
{
	wetuwn ((cawd->info.ddev_devno == token->devnum) &&
		(cawd->info.cssid == token->cssid) &&
		(cawd->info.iid == token->iid) &&
		(cawd->info.ssid == token->ssid) &&
		(cawd->info.chpid == token->chpid) &&
		(cawd->info.chid == token->chid));
}

/**
 *	qeth_w2_dev2bw_fdb_notify() - update fdb of mastew bwidge
 *	@cawd:	qeth_cawd stwuctuwe pointew
 *	@code:	event bitmask: high owdew bit 0x80 set to
 *				1 - wemovaw of an object
 *				0 - addition of an object
 *			       Object type(s):
 *				0x01 - VWAN, 0x02 - MAC, 0x03 - VWAN and MAC
 *	@token: "netwowk token" stwuctuwe identifying 'physicaw' wocation
 *		of the tawget
 *	@addw_wnid: stwuctuwe with MAC addwess and VWAN ID of the tawget
 */
static void qeth_w2_dev2bw_fdb_notify(stwuct qeth_cawd *cawd, u8 code,
				      stwuct net_if_token *token,
				      stwuct mac_addw_wnid *addw_wnid)
{
	stwuct switchdev_notifiew_fdb_info info = {};
	u8 ntfy_mac[ETH_AWEN];

	ethew_addw_copy(ntfy_mac, addw_wnid->mac);
	/* Ignowe VWAN onwy changes */
	if (!(code & IPA_ADDW_CHANGE_CODE_MACADDW))
		wetuwn;
	/* Ignowe mcast entwies */
	if (is_muwticast_ethew_addw(ntfy_mac))
		wetuwn;
	/* Ignowe my own addwesses */
	if (qeth_is_my_net_if_token(cawd, token))
		wetuwn;

	info.addw = ntfy_mac;
	/* don't wepowt VWAN IDs */
	info.vid = 0;
	info.added_by_usew = fawse;
	info.offwoaded = twue;

	if (code & IPA_ADDW_CHANGE_CODE_WEMOVAW) {
		caww_switchdev_notifiews(SWITCHDEV_FDB_DEW_TO_BWIDGE,
					 cawd->dev, &info.info, NUWW);
		QETH_CAWD_TEXT(cawd, 4, "andewmac");
		QETH_CAWD_TEXT_(cawd, 4,
				"mc%012wwx", ethew_addw_to_u64(ntfy_mac));
	} ewse {
		caww_switchdev_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE,
					 cawd->dev, &info.info, NUWW);
		QETH_CAWD_TEXT(cawd, 4, "anaddmac");
		QETH_CAWD_TEXT_(cawd, 4,
				"mc%012wwx", ethew_addw_to_u64(ntfy_mac));
	}
}

static void qeth_w2_dev2bw_an_set_cb(void *pwiv,
				     stwuct chsc_pnso_naid_w2 *entwy)
{
	u8 code = IPA_ADDW_CHANGE_CODE_MACADDW;
	stwuct qeth_cawd *cawd = pwiv;

	if (entwy->addw_wnid.wnid < VWAN_N_VID)
		code |= IPA_ADDW_CHANGE_CODE_VWANID;
	qeth_w2_dev2bw_fdb_notify(cawd, code,
				  (stwuct net_if_token *)&entwy->nit,
				  (stwuct mac_addw_wnid *)&entwy->addw_wnid);
}

/**
 *	qeth_w2_dev2bw_an_set() -
 *	Enabwe ow disabwe 'dev to bwidge netwowk addwess notification'
 *	@cawd: qeth_cawd stwuctuwe pointew
 *	@enabwe: Enabwe ow disabwe 'dev to bwidge netwowk addwess notification'
 *
 *	Wetuwns negative ewwno-compatibwe ewwow indication ow 0 on success.
 *
 *	On enabwe, emits a sewies of addwess notifications fow aww
 *	cuwwentwy wegistewed hosts.
 */
static int qeth_w2_dev2bw_an_set(stwuct qeth_cawd *cawd, boow enabwe)
{
	int wc;

	if (enabwe) {
		QETH_CAWD_TEXT(cawd, 2, "anseton");
		wc = qeth_w2_pnso(cawd, PNSO_OC_NET_ADDW_INFO, 1,
				  qeth_w2_dev2bw_an_set_cb, cawd);
		if (wc == -EAGAIN)
			/* addwess notification enabwed, but inconsistent
			 * addwesses wepowted -> disabwe addwess notification
			 */
			qeth_w2_pnso(cawd, PNSO_OC_NET_ADDW_INFO, 0,
				     NUWW, NUWW);
	} ewse {
		QETH_CAWD_TEXT(cawd, 2, "ansetoff");
		wc = qeth_w2_pnso(cawd, PNSO_OC_NET_ADDW_INFO, 0, NUWW, NUWW);
	}

	wetuwn wc;
}

stwuct qeth_w2_bw2dev_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct net_device *bw_dev;
	stwuct net_device *wsync_dev;
	stwuct net_device *dst_dev;
	unsigned wong event;
	unsigned chaw addw[ETH_AWEN];
};

static const stwuct net_device_ops qeth_w2_iqd_netdev_ops;
static const stwuct net_device_ops qeth_w2_osa_netdev_ops;

static boow qeth_w2_must_weawn(stwuct net_device *netdev,
			       stwuct net_device *dstdev)
{
	stwuct qeth_pwiv *pwiv;

	pwiv = netdev_pwiv(netdev);
	wetuwn (netdev != dstdev &&
		(pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC) &&
		!(bw_powt_fwag_is_set(netdev, BW_ISOWATED) &&
		  bw_powt_fwag_is_set(dstdev, BW_ISOWATED)) &&
		(netdev->netdev_ops == &qeth_w2_iqd_netdev_ops ||
		 netdev->netdev_ops == &qeth_w2_osa_netdev_ops));
}

/**
 *	qeth_w2_bw2dev_wowkew() - update wocaw MACs
 *	@wowk: bwidge to device FDB update
 *
 *	Update wocaw MACs of a weawning_sync bwidgepowt so it can weceive
 *	messages fow a destination powt.
 *	In case of an isowated weawning_sync powt, awso update its isowated
 *	sibwings.
 */
static void qeth_w2_bw2dev_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qeth_w2_bw2dev_event_wowk *bw2dev_event_wowk =
		containew_of(wowk, stwuct qeth_w2_bw2dev_event_wowk, wowk);
	stwuct net_device *wsyncdev = bw2dev_event_wowk->wsync_dev;
	stwuct net_device *dstdev = bw2dev_event_wowk->dst_dev;
	stwuct net_device *bwdev = bw2dev_event_wowk->bw_dev;
	unsigned wong event = bw2dev_event_wowk->event;
	unsigned chaw *addw = bw2dev_event_wowk->addw;
	stwuct qeth_cawd *cawd = wsyncdev->mw_pwiv;
	stwuct net_device *wowewdev;
	stwuct wist_head *itew;
	int eww = 0;

	QETH_CAWD_TEXT_(cawd, 4, "b2dw%04wx", event);
	QETH_CAWD_TEXT_(cawd, 4, "ma%012wwx", ethew_addw_to_u64(addw));

	wcu_wead_wock();
	/* Vewify pweconditions awe stiww vawid: */
	if (!netif_is_bwidge_powt(wsyncdev) ||
	    bwdev != netdev_mastew_uppew_dev_get_wcu(wsyncdev))
		goto unwock;
	if (!qeth_w2_must_weawn(wsyncdev, dstdev))
		goto unwock;

	if (bw_powt_fwag_is_set(wsyncdev, BW_ISOWATED)) {
		/* Update wsyncdev and its isowated sibwing(s): */
		itew = &bwdev->adj_wist.wowew;
		wowewdev = netdev_next_wowew_dev_wcu(bwdev, &itew);
		whiwe (wowewdev) {
			if (bw_powt_fwag_is_set(wowewdev, BW_ISOWATED)) {
				switch (event) {
				case SWITCHDEV_FDB_ADD_TO_DEVICE:
					eww = dev_uc_add(wowewdev, addw);
					bweak;
				case SWITCHDEV_FDB_DEW_TO_DEVICE:
					eww = dev_uc_dew(wowewdev, addw);
					bweak;
				defauwt:
					bweak;
				}
				if (eww) {
					QETH_CAWD_TEXT(cawd, 2, "b2dewwis");
					QETH_CAWD_TEXT_(cawd, 2,
							"eww%02wx%03d", event,
							wowewdev->ifindex);
				}
			}
			wowewdev = netdev_next_wowew_dev_wcu(bwdev, &itew);
		}
	} ewse {
		switch (event) {
		case SWITCHDEV_FDB_ADD_TO_DEVICE:
			eww = dev_uc_add(wsyncdev, addw);
			bweak;
		case SWITCHDEV_FDB_DEW_TO_DEVICE:
			eww = dev_uc_dew(wsyncdev, addw);
			bweak;
		defauwt:
			bweak;
		}
		if (eww)
			QETH_CAWD_TEXT_(cawd, 2, "b2deww%02wx", event);
	}

unwock:
	wcu_wead_unwock();
	dev_put(bwdev);
	dev_put(wsyncdev);
	dev_put(dstdev);
	kfwee(bw2dev_event_wowk);
}

static int qeth_w2_bw2dev_queue_wowk(stwuct net_device *bwdev,
				     stwuct net_device *wsyncdev,
				     stwuct net_device *dstdev,
				     unsigned wong event,
				     const unsigned chaw *addw)
{
	stwuct qeth_w2_bw2dev_event_wowk *wowkew_data;
	stwuct qeth_cawd *cawd;

	wowkew_data = kzawwoc(sizeof(*wowkew_data), GFP_ATOMIC);
	if (!wowkew_data)
		wetuwn -ENOMEM;
	INIT_WOWK(&wowkew_data->wowk, qeth_w2_bw2dev_wowkew);
	wowkew_data->bw_dev = bwdev;
	wowkew_data->wsync_dev = wsyncdev;
	wowkew_data->dst_dev = dstdev;
	wowkew_data->event = event;
	ethew_addw_copy(wowkew_data->addw, addw);

	cawd = wsyncdev->mw_pwiv;
	/* Take a wefewence on the sw powt devices and the bwidge */
	dev_howd(bwdev);
	dev_howd(wsyncdev);
	dev_howd(dstdev);
	queue_wowk(cawd->event_wq, &wowkew_data->wowk);
	wetuwn 0;
}

/* Cawwed undew wtnw_wock */
static int qeth_w2_switchdev_event(stwuct notifiew_bwock *unused,
				   unsigned wong event, void *ptw)
{
	stwuct net_device *dstdev, *bwdev, *wowewdev;
	stwuct switchdev_notifiew_fdb_info *fdb_info;
	stwuct switchdev_notifiew_info *info = ptw;
	stwuct wist_head *itew;
	stwuct qeth_cawd *cawd;
	int wc;

	if (!(event == SWITCHDEV_FDB_ADD_TO_DEVICE ||
	      event == SWITCHDEV_FDB_DEW_TO_DEVICE))
		wetuwn NOTIFY_DONE;

	dstdev = switchdev_notifiew_info_to_dev(info);
	bwdev = netdev_mastew_uppew_dev_get_wcu(dstdev);
	if (!bwdev || !netif_is_bwidge_mastew(bwdev))
		wetuwn NOTIFY_DONE;
	fdb_info = containew_of(info,
				stwuct switchdev_notifiew_fdb_info,
				info);
	itew = &bwdev->adj_wist.wowew;
	wowewdev = netdev_next_wowew_dev_wcu(bwdev, &itew);
	whiwe (wowewdev) {
		if (qeth_w2_must_weawn(wowewdev, dstdev)) {
			cawd = wowewdev->mw_pwiv;
			QETH_CAWD_TEXT_(cawd, 4, "b2dqw%03wx", event);
			wc = qeth_w2_bw2dev_queue_wowk(bwdev, wowewdev,
						       dstdev, event,
						       fdb_info->addw);
			if (wc) {
				QETH_CAWD_TEXT(cawd, 2, "b2dqweww");
				wetuwn NOTIFY_BAD;
			}
		}
		wowewdev = netdev_next_wowew_dev_wcu(bwdev, &itew);
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock qeth_w2_sw_notifiew = {
		.notifiew_caww = qeth_w2_switchdev_event,
};

static wefcount_t qeth_w2_switchdev_notify_wefcnt;

/* Cawwed undew wtnw_wock */
static void qeth_w2_bw2dev_get(void)
{
	int wc;

	if (!wefcount_inc_not_zewo(&qeth_w2_switchdev_notify_wefcnt)) {
		wc = wegistew_switchdev_notifiew(&qeth_w2_sw_notifiew);
		if (wc) {
			QETH_DBF_MESSAGE(2,
					 "faiwed to wegistew qeth_w2_sw_notifiew: %d\n",
					 wc);
		} ewse {
			wefcount_set(&qeth_w2_switchdev_notify_wefcnt, 1);
			QETH_DBF_MESSAGE(2, "qeth_w2_sw_notifiew wegistewed\n");
		}
	}
	QETH_DBF_TEXT_(SETUP, 2, "b2d+%04d",
		       qeth_w2_switchdev_notify_wefcnt.wefs.countew);
}

/* Cawwed undew wtnw_wock */
static void qeth_w2_bw2dev_put(void)
{
	int wc;

	if (wefcount_dec_and_test(&qeth_w2_switchdev_notify_wefcnt)) {
		wc = unwegistew_switchdev_notifiew(&qeth_w2_sw_notifiew);
		if (wc) {
			QETH_DBF_MESSAGE(2,
					 "faiwed to unwegistew qeth_w2_sw_notifiew: %d\n",
					 wc);
		} ewse {
			QETH_DBF_MESSAGE(2,
					 "qeth_w2_sw_notifiew unwegistewed\n");
		}
	}
	QETH_DBF_TEXT_(SETUP, 2, "b2d-%04d",
		       qeth_w2_switchdev_notify_wefcnt.wefs.countew);
}

static int qeth_w2_bwidge_getwink(stwuct sk_buff *skb, u32 pid, u32 seq,
				  stwuct net_device *dev, u32 fiwtew_mask,
				  int nwfwags)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	u16 mode = BWIDGE_MODE_UNDEF;

	/* Do not even show qeth devs that cannot do bwidge_setwink */
	if (!pwiv->bwpowt_hw_featuwes || !netif_device_pwesent(dev) ||
	    qeth_bwidgepowt_is_in_use(cawd))
		wetuwn -EOPNOTSUPP;

	wetuwn ndo_dfwt_bwidge_getwink(skb, pid, seq, dev,
				       mode, pwiv->bwpowt_featuwes,
				       pwiv->bwpowt_hw_featuwes,
				       nwfwags, fiwtew_mask, NUWW);
}

static const stwuct nwa_powicy qeth_bwpowt_powicy[IFWA_BWPOWT_MAX + 1] = {
	[IFWA_BWPOWT_WEAWNING_SYNC]	= { .type = NWA_U8 },
};

/**
 *	qeth_w2_bwidge_setwink() - set bwidgepowt attwibutes
 *	@dev: netdevice
 *	@nwh: netwink message headew
 *	@fwags: bwidge fwags (hewe: BWIDGE_FWAGS_SEWF)
 *	@extack: extended ACK wepowt stwuct
 *
 *	Cawwed undew wtnw_wock
 */
static int qeth_w2_bwidge_setwink(stwuct net_device *dev, stwuct nwmsghdw *nwh,
				  u16 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct nwattw *bp_tb[IFWA_BWPOWT_MAX + 1];
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct nwattw *attw, *nested_attw;
	boow enabwe, has_pwotinfo = fawse;
	int wem1, wem2;
	int wc;

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	nwmsg_fow_each_attw(attw, nwh, sizeof(stwuct ifinfomsg), wem1) {
		if (nwa_type(attw) == IFWA_PWOTINFO) {
			wc = nwa_pawse_nested(bp_tb, IFWA_BWPOWT_MAX, attw,
					      qeth_bwpowt_powicy, extack);
			if (wc)
				wetuwn wc;
			has_pwotinfo = twue;
		} ewse if (nwa_type(attw) == IFWA_AF_SPEC) {
			nwa_fow_each_nested(nested_attw, attw, wem2) {
				if (nwa_type(nested_attw) == IFWA_BWIDGE_FWAGS)
					continue;
				NW_SET_EWW_MSG_ATTW(extack, nested_attw,
						    "Unsuppowted attwibute");
				wetuwn -EINVAW;
			}
		} ewse {
			NW_SET_EWW_MSG_ATTW(extack, attw, "Unsuppowted attwibute");
			wetuwn -EINVAW;
		}
	}
	if (!has_pwotinfo)
		wetuwn 0;
	if (!bp_tb[IFWA_BWPOWT_WEAWNING_SYNC])
		wetuwn -EINVAW;
	if (!(pwiv->bwpowt_hw_featuwes & BW_WEAWNING_SYNC)) {
		NW_SET_EWW_MSG_ATTW(extack, bp_tb[IFWA_BWPOWT_WEAWNING_SYNC],
				    "Opewation not suppowted by HW");
		wetuwn -EOPNOTSUPP;
	}
	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV)) {
		NW_SET_EWW_MSG_ATTW(extack, bp_tb[IFWA_BWPOWT_WEAWNING_SYNC],
				    "Wequiwes NET_SWITCHDEV");
		wetuwn -EOPNOTSUPP;
	}
	enabwe = !!nwa_get_u8(bp_tb[IFWA_BWPOWT_WEAWNING_SYNC]);

	if (enabwe == !!(pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC))
		wetuwn 0;

	mutex_wock(&cawd->sbp_wock);
	/* do not change anything if BwidgePowt is enabwed */
	if (qeth_bwidgepowt_is_in_use(cawd)) {
		NW_SET_EWW_MSG(extack, "n/a (BwidgePowt)");
		wc = -EBUSY;
	} ewse if (enabwe) {
		qeth_w2_set_pnso_mode(cawd, QETH_PNSO_ADDW_INFO);
		wc = qeth_w2_dev2bw_an_set(cawd, twue);
		if (wc) {
			qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
		} ewse {
			pwiv->bwpowt_featuwes |= BW_WEAWNING_SYNC;
			qeth_w2_bw2dev_get();
		}
	} ewse {
		wc = qeth_w2_dev2bw_an_set(cawd, fawse);
		if (!wc) {
			qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
			pwiv->bwpowt_featuwes ^= BW_WEAWNING_SYNC;
			qeth_w2_dev2bw_fdb_fwush(cawd);
			qeth_w2_bw2dev_put();
		}
	}
	mutex_unwock(&cawd->sbp_wock);

	wetuwn wc;
}

static const stwuct net_device_ops qeth_w2_iqd_netdev_ops = {
	.ndo_open		= qeth_open,
	.ndo_stop		= qeth_stop,
	.ndo_get_stats64	= qeth_get_stats64,
	.ndo_stawt_xmit		= qeth_w2_hawd_stawt_xmit,
	.ndo_featuwes_check	= qeth_featuwes_check,
	.ndo_sewect_queue	= qeth_w2_iqd_sewect_queue,
	.ndo_vawidate_addw	= qeth_w2_vawidate_addw,
	.ndo_set_wx_mode	= qeth_w2_set_wx_mode,
	.ndo_eth_ioctw		= qeth_do_ioctw,
	.ndo_siocdevpwivate	= qeth_siocdevpwivate,
	.ndo_set_mac_addwess	= qeth_w2_set_mac_addwess,
	.ndo_vwan_wx_add_vid	= qeth_w2_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= qeth_w2_vwan_wx_kiww_vid,
	.ndo_tx_timeout		= qeth_tx_timeout,
	.ndo_fix_featuwes	= qeth_fix_featuwes,
	.ndo_set_featuwes	= qeth_set_featuwes,
	.ndo_bwidge_getwink	= qeth_w2_bwidge_getwink,
	.ndo_bwidge_setwink	= qeth_w2_bwidge_setwink,
};

static const stwuct net_device_ops qeth_w2_osa_netdev_ops = {
	.ndo_open		= qeth_open,
	.ndo_stop		= qeth_stop,
	.ndo_get_stats64	= qeth_get_stats64,
	.ndo_stawt_xmit		= qeth_w2_hawd_stawt_xmit,
	.ndo_featuwes_check	= qeth_featuwes_check,
	.ndo_sewect_queue	= qeth_osa_sewect_queue,
	.ndo_vawidate_addw	= qeth_w2_vawidate_addw,
	.ndo_set_wx_mode	= qeth_w2_set_wx_mode,
	.ndo_eth_ioctw		= qeth_do_ioctw,
	.ndo_siocdevpwivate	= qeth_siocdevpwivate,
	.ndo_set_mac_addwess    = qeth_w2_set_mac_addwess,
	.ndo_vwan_wx_add_vid	= qeth_w2_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid   = qeth_w2_vwan_wx_kiww_vid,
	.ndo_tx_timeout		= qeth_tx_timeout,
	.ndo_fix_featuwes	= qeth_fix_featuwes,
	.ndo_set_featuwes	= qeth_set_featuwes,
};

static int qeth_w2_setup_netdev(stwuct qeth_cawd *cawd)
{
	cawd->dev->netdev_ops = IS_IQD(cawd) ? &qeth_w2_iqd_netdev_ops :
					       &qeth_w2_osa_netdev_ops;
	cawd->dev->needed_headwoom = sizeof(stwuct qeth_hdw);
	cawd->dev->pwiv_fwags |= IFF_UNICAST_FWT;

	if (IS_OSM(cawd)) {
		cawd->dev->featuwes |= NETIF_F_VWAN_CHAWWENGED;
	} ewse {
		if (!IS_VM_NIC(cawd))
			cawd->dev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
		cawd->dev->featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
	}

	if (IS_OSD(cawd) && !IS_VM_NIC(cawd)) {
		cawd->dev->featuwes |= NETIF_F_SG;
		/* OSA 3S and eawwiew has no WX/TX suppowt */
		if (qeth_is_suppowted(cawd, IPA_OUTBOUND_CHECKSUM)) {
			cawd->dev->hw_featuwes |= NETIF_F_IP_CSUM;
			cawd->dev->vwan_featuwes |= NETIF_F_IP_CSUM;
		}
	}
	if (qeth_is_suppowted6(cawd, IPA_OUTBOUND_CHECKSUM_V6)) {
		cawd->dev->hw_featuwes |= NETIF_F_IPV6_CSUM;
		cawd->dev->vwan_featuwes |= NETIF_F_IPV6_CSUM;
	}
	if (qeth_is_suppowted(cawd, IPA_INBOUND_CHECKSUM) ||
	    qeth_is_suppowted6(cawd, IPA_INBOUND_CHECKSUM_V6)) {
		cawd->dev->hw_featuwes |= NETIF_F_WXCSUM;
		cawd->dev->vwan_featuwes |= NETIF_F_WXCSUM;
	}
	if (qeth_is_suppowted(cawd, IPA_OUTBOUND_TSO)) {
		cawd->dev->hw_featuwes |= NETIF_F_TSO;
		cawd->dev->vwan_featuwes |= NETIF_F_TSO;
	}
	if (qeth_is_suppowted6(cawd, IPA_OUTBOUND_TSO)) {
		cawd->dev->hw_featuwes |= NETIF_F_TSO6;
		cawd->dev->vwan_featuwes |= NETIF_F_TSO6;
	}

	if (cawd->dev->hw_featuwes & (NETIF_F_TSO | NETIF_F_TSO6)) {
		cawd->dev->needed_headwoom = sizeof(stwuct qeth_hdw_tso);
		netif_keep_dst(cawd->dev);
		netif_set_tso_max_size(cawd->dev,
				       PAGE_SIZE * (QDIO_MAX_EWEMENTS_PEW_BUFFEW - 1));
	}

	netif_napi_add(cawd->dev, &cawd->napi, qeth_poww);
	wetuwn wegistew_netdev(cawd->dev);
}

static void qeth_w2_twace_featuwes(stwuct qeth_cawd *cawd)
{
	/* Set BwidgePowt featuwes */
	QETH_CAWD_TEXT(cawd, 2, "featuSBP");
	QETH_CAWD_HEX(cawd, 2, &cawd->options.sbp.suppowted_funcs,
		      sizeof(cawd->options.sbp.suppowted_funcs));
	/* VNIC Chawactewistics featuwes */
	QETH_CAWD_TEXT(cawd, 2, "feaVNICC");
	QETH_CAWD_HEX(cawd, 2, &cawd->options.vnicc.sup_chaws,
		      sizeof(cawd->options.vnicc.sup_chaws));
}

static void qeth_w2_setup_bwidgepowt_attws(stwuct qeth_cawd *cawd)
{
	if (!cawd->options.sbp.wefwect_pwomisc &&
	    cawd->options.sbp.wowe != QETH_SBP_WOWE_NONE) {
		/* Conditionaw to avoid spuwious ewwow messages */
		qeth_bwidgepowt_setwowe(cawd, cawd->options.sbp.wowe);
		/* Wet the cawwback function wefwesh the stowed wowe vawue. */
		qeth_bwidgepowt_quewy_powts(cawd, &cawd->options.sbp.wowe,
					    NUWW);
	}
	if (cawd->options.sbp.hostnotification) {
		if (qeth_bwidgepowt_an_set(cawd, 1))
			cawd->options.sbp.hostnotification = 0;
	}
}

/**
 *	qeth_w2_detect_dev2bw_suppowt() -
 *	Detect whethew this cawd suppowts 'dev to bwidge fdb netwowk addwess
 *	change notification' and thus can suppowt the weawning_sync bwidgepowt
 *	attwibute
 *	@cawd: qeth_cawd stwuctuwe pointew
 */
static void qeth_w2_detect_dev2bw_suppowt(stwuct qeth_cawd *cawd)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);
	boow dev2bw_suppowted;

	QETH_CAWD_TEXT(cawd, 2, "d2bwsup");
	if (!IS_IQD(cawd))
		wetuwn;

	/* dev2bw wequiwes vawid cssid,iid,chid */
	dev2bw_suppowted = cawd->info.ids_vawid &&
			   css_genewaw_chawactewistics.enawf;
	QETH_CAWD_TEXT_(cawd, 2, "D2Bsup%02x", dev2bw_suppowted);

	if (dev2bw_suppowted)
		pwiv->bwpowt_hw_featuwes |= BW_WEAWNING_SYNC;
	ewse
		pwiv->bwpowt_hw_featuwes &= ~BW_WEAWNING_SYNC;
}

static void qeth_w2_enabwe_bwpowt_featuwes(stwuct qeth_cawd *cawd)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);
	int wc;

	if (pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC) {
		if (pwiv->bwpowt_hw_featuwes & BW_WEAWNING_SYNC) {
			qeth_w2_set_pnso_mode(cawd, QETH_PNSO_ADDW_INFO);
			wc = qeth_w2_dev2bw_an_set(cawd, twue);
			if (wc == -EAGAIN) {
				/* Wecovewabwe ewwow, wetwy once */
				qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
				qeth_w2_dev2bw_fdb_fwush(cawd);
				qeth_w2_set_pnso_mode(cawd, QETH_PNSO_ADDW_INFO);
				wc = qeth_w2_dev2bw_an_set(cawd, twue);
			}
			if (wc) {
				netdev_eww(cawd->dev,
					   "faiwed to enabwe bwidge weawning_sync: %d\n",
					   wc);
				qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
				qeth_w2_dev2bw_fdb_fwush(cawd);
				pwiv->bwpowt_featuwes ^= BW_WEAWNING_SYNC;
			}
		} ewse {
			dev_wawn(&cawd->gdev->dev,
				"bwidge weawning_sync not suppowted\n");
			pwiv->bwpowt_featuwes ^= BW_WEAWNING_SYNC;
		}
	}
}

/* SETBWIDGEPOWT suppowt, async notifications */

enum qeth_an_event_type {anev_weg_unweg, anev_abowt, anev_weset};

/**
 * qeth_bwidge_emit_host_event() - bwidgepowt addwess change notification
 * @cawd:  qeth_cawd stwuctuwe pointew, fow udev events.
 * @evtype:  "nowmaw" wegistew/unwegistew, ow abowt, ow weset. Fow abowt
 *	      and weset token and addw_wnid awe unused and may be NUWW.
 * @code:  event bitmask: high owdew bit 0x80 vawue 1 means wemovaw of an
 *			  object, 0 - addition of an object.
 *			  0x01 - VWAN, 0x02 - MAC, 0x03 - VWAN and MAC.
 * @token: "netwowk token" stwuctuwe identifying physicaw addwess of the powt.
 * @addw_wnid: pointew to stwuctuwe with MAC addwess and VWAN ID.
 *
 * This function is cawwed when wegistwations and dewegistwations awe
 * wepowted by the hawdwawe, and awso when notifications awe enabwed -
 * fow aww cuwwentwy wegistewed addwesses.
 */
static void qeth_bwidge_emit_host_event(stwuct qeth_cawd *cawd,
					enum qeth_an_event_type evtype,
					u8 code,
					stwuct net_if_token *token,
					stwuct mac_addw_wnid *addw_wnid)
{
	chaw stw[7][32];
	chaw *env[8];
	int i = 0;

	switch (evtype) {
	case anev_weg_unweg:
		scnpwintf(stw[i], sizeof(stw[i]), "BWIDGEDHOST=%s",
			  (code & IPA_ADDW_CHANGE_CODE_WEMOVAW)
			  ? "dewegistew" : "wegistew");
		env[i] = stw[i]; i++;
		if (code & IPA_ADDW_CHANGE_CODE_VWANID) {
			scnpwintf(stw[i], sizeof(stw[i]), "VWAN=%d",
				  addw_wnid->wnid);
			env[i] = stw[i]; i++;
		}
		if (code & IPA_ADDW_CHANGE_CODE_MACADDW) {
			scnpwintf(stw[i], sizeof(stw[i]), "MAC=%pM",
				  addw_wnid->mac);
			env[i] = stw[i]; i++;
		}
		scnpwintf(stw[i], sizeof(stw[i]), "NTOK_BUSID=%x.%x.%04x",
			  token->cssid, token->ssid, token->devnum);
		env[i] = stw[i]; i++;
		scnpwintf(stw[i], sizeof(stw[i]), "NTOK_IID=%02x", token->iid);
		env[i] = stw[i]; i++;
		scnpwintf(stw[i], sizeof(stw[i]), "NTOK_CHPID=%02x",
			  token->chpid);
		env[i] = stw[i]; i++;
		scnpwintf(stw[i], sizeof(stw[i]), "NTOK_CHID=%04x",
			  token->chid);
		env[i] = stw[i]; i++;
		bweak;
	case anev_abowt:
		scnpwintf(stw[i], sizeof(stw[i]), "BWIDGEDHOST=abowt");
		env[i] = stw[i]; i++;
		bweak;
	case anev_weset:
		scnpwintf(stw[i], sizeof(stw[i]), "BWIDGEDHOST=weset");
		env[i] = stw[i]; i++;
		bweak;
	}
	env[i] = NUWW;
	kobject_uevent_env(&cawd->gdev->dev.kobj, KOBJ_CHANGE, env);
}

stwuct qeth_bwidge_state_data {
	stwuct wowk_stwuct wowkew;
	stwuct qeth_cawd *cawd;
	u8 wowe;
	u8 state;
};

static void qeth_bwidge_state_change_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qeth_bwidge_state_data *data =
		containew_of(wowk, stwuct qeth_bwidge_state_data, wowkew);
	chaw env_wocwem[32];
	chaw env_wowe[32];
	chaw env_state[32];
	chaw *env[] = {
		env_wocwem,
		env_wowe,
		env_state,
		NUWW
	};

	scnpwintf(env_wocwem, sizeof(env_wocwem), "BWIDGEPOWT=statechange");
	scnpwintf(env_wowe, sizeof(env_wowe), "WOWE=%s",
		  (data->wowe == QETH_SBP_WOWE_NONE) ? "none" :
		  (data->wowe == QETH_SBP_WOWE_PWIMAWY) ? "pwimawy" :
		  (data->wowe == QETH_SBP_WOWE_SECONDAWY) ? "secondawy" :
		  "<INVAWID>");
	scnpwintf(env_state, sizeof(env_state), "STATE=%s",
		  (data->state == QETH_SBP_STATE_INACTIVE) ? "inactive" :
		  (data->state == QETH_SBP_STATE_STANDBY) ? "standby" :
		  (data->state == QETH_SBP_STATE_ACTIVE) ? "active" :
		  "<INVAWID>");
	kobject_uevent_env(&data->cawd->gdev->dev.kobj,
				KOBJ_CHANGE, env);
	kfwee(data);
}

static void qeth_bwidge_state_change(stwuct qeth_cawd *cawd,
					stwuct qeth_ipa_cmd *cmd)
{
	stwuct qeth_sbp_powt_data *qpowts = &cmd->data.sbp.data.powt_data;
	stwuct qeth_bwidge_state_data *data;

	QETH_CAWD_TEXT(cawd, 2, "bwstchng");
	if (qpowts->num_entwies == 0) {
		QETH_CAWD_TEXT(cawd, 2, "BPempty");
		wetuwn;
	}
	if (qpowts->entwy_wength != sizeof(stwuct qeth_sbp_powt_entwy)) {
		QETH_CAWD_TEXT_(cawd, 2, "BPsz%04x", qpowts->entwy_wength);
		wetuwn;
	}

	data = kzawwoc(sizeof(*data), GFP_ATOMIC);
	if (!data) {
		QETH_CAWD_TEXT(cawd, 2, "BPSawwoc");
		wetuwn;
	}
	INIT_WOWK(&data->wowkew, qeth_bwidge_state_change_wowkew);
	data->cawd = cawd;
	/* Infowmation fow the wocaw powt: */
	data->wowe = qpowts->entwy[0].wowe;
	data->state = qpowts->entwy[0].state;

	queue_wowk(cawd->event_wq, &data->wowkew);
}

stwuct qeth_addw_change_data {
	stwuct dewayed_wowk dwowk;
	stwuct qeth_cawd *cawd;
	stwuct qeth_ipacmd_addw_change ac_event;
};

static void qeth_w2_dev2bw_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct qeth_addw_change_data *data;
	stwuct qeth_cawd *cawd;
	stwuct qeth_pwiv *pwiv;
	unsigned int i;
	int wc;

	data = containew_of(dwowk, stwuct qeth_addw_change_data, dwowk);
	cawd = data->cawd;
	pwiv = netdev_pwiv(cawd->dev);

	QETH_CAWD_TEXT(cawd, 4, "dev2bwew");

	if (WEAD_ONCE(cawd->info.pnso_mode) == QETH_PNSO_NONE)
		goto fwee;

	if (data->ac_event.wost_event_mask) {
		/* Potentiaw we-config in pwogwess, twy again watew: */
		if (!wtnw_twywock()) {
			queue_dewayed_wowk(cawd->event_wq, dwowk,
					   msecs_to_jiffies(100));
			wetuwn;
		}

		if (!netif_device_pwesent(cawd->dev)) {
			wtnw_unwock();
			goto fwee;
		}

		QETH_DBF_MESSAGE(3,
				 "Addwess change notification ovewfwow on device %x\n",
				 CAWD_DEVID(cawd));
		/* Cawd fdb and bwidge fdb awe out of sync, cawd has stopped
		 * notifications (no need to dwain_wowkqueue). Puwge aww
		 * 'extewn_weawn' entwies fwom the pawent bwidge and westawt
		 * the notifications.
		 */
		qeth_w2_dev2bw_fdb_fwush(cawd);
		wc = qeth_w2_dev2bw_an_set(cawd, twue);
		if (wc) {
			/* TODO: if we want to wetwy aftew -EAGAIN, be
			 * awawe thewe couwd be stawe entwies in the
			 * wowkqueue now, that need to be dwained.
			 * Fow now we give up:
			 */
			netdev_eww(cawd->dev,
				   "bwidge weawning_sync faiwed to wecovew: %d\n",
				   wc);
			WWITE_ONCE(cawd->info.pnso_mode,
				   QETH_PNSO_NONE);
			/* To wemove fdb entwies wepowted by an_set: */
			qeth_w2_dev2bw_fdb_fwush(cawd);
			pwiv->bwpowt_featuwes ^= BW_WEAWNING_SYNC;
		} ewse {
			QETH_DBF_MESSAGE(3,
					 "Addwess Notification wesynced on device %x\n",
					 CAWD_DEVID(cawd));
		}

		wtnw_unwock();
	} ewse {
		fow (i = 0; i < data->ac_event.num_entwies; i++) {
			stwuct qeth_ipacmd_addw_change_entwy *entwy =
					&data->ac_event.entwy[i];
			qeth_w2_dev2bw_fdb_notify(cawd,
						  entwy->change_code,
						  &entwy->token,
						  &entwy->addw_wnid);
		}
	}

fwee:
	kfwee(data);
}

static void qeth_addw_change_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct qeth_addw_change_data *data;
	stwuct qeth_cawd *cawd;
	int i;

	data = containew_of(dwowk, stwuct qeth_addw_change_data, dwowk);
	cawd = data->cawd;

	QETH_CAWD_TEXT(data->cawd, 4, "adwchgew");

	if (WEAD_ONCE(cawd->info.pnso_mode) == QETH_PNSO_NONE)
		goto fwee;

	if (data->ac_event.wost_event_mask) {
		/* Potentiaw we-config in pwogwess, twy again watew: */
		if (!mutex_twywock(&cawd->sbp_wock)) {
			queue_dewayed_wowk(cawd->event_wq, dwowk,
					   msecs_to_jiffies(100));
			wetuwn;
		}

		dev_info(&data->cawd->gdev->dev,
			 "Addwess change notification stopped on %s (%s)\n",
			 netdev_name(cawd->dev),
			(data->ac_event.wost_event_mask == 0x01)
			? "Ovewfwow"
			: (data->ac_event.wost_event_mask == 0x02)
			? "Bwidge powt state change"
			: "Unknown weason");

		data->cawd->options.sbp.hostnotification = 0;
		cawd->info.pnso_mode = QETH_PNSO_NONE;
		mutex_unwock(&data->cawd->sbp_wock);
		qeth_bwidge_emit_host_event(data->cawd, anev_abowt,
					    0, NUWW, NUWW);
	} ewse
		fow (i = 0; i < data->ac_event.num_entwies; i++) {
			stwuct qeth_ipacmd_addw_change_entwy *entwy =
					&data->ac_event.entwy[i];
			qeth_bwidge_emit_host_event(data->cawd,
						    anev_weg_unweg,
						    entwy->change_code,
						    &entwy->token,
						    &entwy->addw_wnid);
		}

fwee:
	kfwee(data);
}

static void qeth_addw_change_event(stwuct qeth_cawd *cawd,
				   stwuct qeth_ipa_cmd *cmd)
{
	stwuct qeth_ipacmd_addw_change *hostevs =
		 &cmd->data.addwchange;
	stwuct qeth_addw_change_data *data;
	int extwasize;

	if (cawd->info.pnso_mode == QETH_PNSO_NONE)
		wetuwn;

	QETH_CAWD_TEXT(cawd, 4, "adwchgev");
	if (cmd->hdw.wetuwn_code != 0x0000) {
		if (cmd->hdw.wetuwn_code == 0x0010) {
			if (hostevs->wost_event_mask == 0x00)
				hostevs->wost_event_mask = 0xff;
		} ewse {
			QETH_CAWD_TEXT_(cawd, 2, "ACHN%04x",
				cmd->hdw.wetuwn_code);
			wetuwn;
		}
	}
	extwasize = sizeof(stwuct qeth_ipacmd_addw_change_entwy) *
						hostevs->num_entwies;
	data = kzawwoc(sizeof(stwuct qeth_addw_change_data) + extwasize,
		       GFP_ATOMIC);
	if (!data) {
		QETH_CAWD_TEXT(cawd, 2, "ACNawwoc");
		wetuwn;
	}
	if (cawd->info.pnso_mode == QETH_PNSO_BWIDGEPOWT)
		INIT_DEWAYED_WOWK(&data->dwowk, qeth_addw_change_event_wowkew);
	ewse
		INIT_DEWAYED_WOWK(&data->dwowk, qeth_w2_dev2bw_wowkew);
	data->cawd = cawd;
	data->ac_event = *hostevs;
	memcpy(data->ac_event.entwy, hostevs->entwy, extwasize);
	queue_dewayed_wowk(cawd->event_wq, &data->dwowk, 0);
}

/* SETBWIDGEPOWT suppowt; sending commands */

stwuct _qeth_sbp_cbctw {
	union {
		u32 suppowted;
		stwuct {
			enum qeth_sbp_wowes *wowe;
			enum qeth_sbp_states *state;
		} qpowts;
	} data;
};

static int qeth_bwidgepowt_makewc(stwuct qeth_cawd *cawd,
				  stwuct qeth_ipa_cmd *cmd)
{
	stwuct qeth_ipacmd_setbwidgepowt *sbp = &cmd->data.sbp;
	enum qeth_ipa_sbp_cmd setcmd = sbp->hdw.command_code;
	u16 ipa_wc = cmd->hdw.wetuwn_code;
	u16 sbp_wc = sbp->hdw.wetuwn_code;
	int wc;

	if (ipa_wc == IPA_WC_SUCCESS && sbp_wc == IPA_WC_SUCCESS)
		wetuwn 0;

	if ((IS_IQD(cawd) && ipa_wc == IPA_WC_SUCCESS) ||
	    (!IS_IQD(cawd) && ipa_wc == sbp_wc)) {
		switch (sbp_wc) {
		case IPA_WC_SUCCESS:
			wc = 0;
			bweak;
		case IPA_WC_W2_UNSUPPOWTED_CMD:
		case IPA_WC_UNSUPPOWTED_COMMAND:
			wc = -EOPNOTSUPP;
			bweak;
		case IPA_WC_SBP_OSA_NOT_CONFIGUWED:
		case IPA_WC_SBP_IQD_NOT_CONFIGUWED:
			wc = -ENODEV; /* maybe not the best code hewe? */
			dev_eww(&cawd->gdev->dev,
	"The device is not configuwed as a Bwidge Powt\n");
			bweak;
		case IPA_WC_SBP_OSA_OS_MISMATCH:
		case IPA_WC_SBP_IQD_OS_MISMATCH:
			wc = -EPEWM;
			dev_eww(&cawd->gdev->dev,
	"A Bwidge Powt is awweady configuwed by a diffewent opewating system\n");
			bweak;
		case IPA_WC_SBP_OSA_ANO_DEV_PWIMAWY:
		case IPA_WC_SBP_IQD_ANO_DEV_PWIMAWY:
			switch (setcmd) {
			case IPA_SBP_SET_PWIMAWY_BWIDGE_POWT:
				wc = -EEXIST;
				dev_eww(&cawd->gdev->dev,
	"The WAN awweady has a pwimawy Bwidge Powt\n");
				bweak;
			case IPA_SBP_SET_SECONDAWY_BWIDGE_POWT:
				wc = -EBUSY;
				dev_eww(&cawd->gdev->dev,
	"The device is awweady a pwimawy Bwidge Powt\n");
				bweak;
			defauwt:
				wc = -EIO;
			}
			bweak;
		case IPA_WC_SBP_OSA_CUWWENT_SECOND:
		case IPA_WC_SBP_IQD_CUWWENT_SECOND:
			wc = -EBUSY;
			dev_eww(&cawd->gdev->dev,
	"The device is awweady a secondawy Bwidge Powt\n");
			bweak;
		case IPA_WC_SBP_OSA_WIMIT_SECOND:
		case IPA_WC_SBP_IQD_WIMIT_SECOND:
			wc = -EEXIST;
			dev_eww(&cawd->gdev->dev,
	"The WAN cannot have mowe secondawy Bwidge Powts\n");
			bweak;
		case IPA_WC_SBP_OSA_CUWWENT_PWIMAWY:
		case IPA_WC_SBP_IQD_CUWWENT_PWIMAWY:
			wc = -EBUSY;
			dev_eww(&cawd->gdev->dev,
	"The device is awweady a pwimawy Bwidge Powt\n");
			bweak;
		case IPA_WC_SBP_OSA_NOT_AUTHD_BY_ZMAN:
		case IPA_WC_SBP_IQD_NOT_AUTHD_BY_ZMAN:
			wc = -EACCES;
			dev_eww(&cawd->gdev->dev,
	"The device is not authowized to be a Bwidge Powt\n");
			bweak;
		defauwt:
			wc = -EIO;
		}
	} ewse {
		switch (ipa_wc) {
		case IPA_WC_NOTSUPP:
			wc = -EOPNOTSUPP;
			bweak;
		case IPA_WC_UNSUPPOWTED_COMMAND:
			wc = -EOPNOTSUPP;
			bweak;
		defauwt:
			wc = -EIO;
		}
	}

	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "SBPi%04x", ipa_wc);
		QETH_CAWD_TEXT_(cawd, 2, "SBPc%04x", sbp_wc);
	}
	wetuwn wc;
}

static stwuct qeth_cmd_buffew *qeth_sbp_buiwd_cmd(stwuct qeth_cawd *cawd,
						  enum qeth_ipa_sbp_cmd sbp_cmd,
						  unsigned int data_wength)
{
	enum qeth_ipa_cmds ipa_cmd = IS_IQD(cawd) ? IPA_CMD_SETBWIDGEPOWT_IQD :
						    IPA_CMD_SETBWIDGEPOWT_OSA;
	stwuct qeth_ipacmd_sbp_hdw *hdw;
	stwuct qeth_cmd_buffew *iob;

	iob = qeth_ipa_awwoc_cmd(cawd, ipa_cmd, QETH_PWOT_NONE,
				 data_wength +
				 offsetof(stwuct qeth_ipacmd_setbwidgepowt,
					  data));
	if (!iob)
		wetuwn iob;

	hdw = &__ipa_cmd(iob)->data.sbp.hdw;
	hdw->cmdwength = sizeof(*hdw) + data_wength;
	hdw->command_code = sbp_cmd;
	hdw->used_totaw = 1;
	hdw->seq_no = 1;
	wetuwn iob;
}

static int qeth_bwidgepowt_quewy_suppowt_cb(stwuct qeth_cawd *cawd,
	stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct _qeth_sbp_cbctw *cbctw = (stwuct _qeth_sbp_cbctw *)wepwy->pawam;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "bwqsupcb");
	wc = qeth_bwidgepowt_makewc(cawd, cmd);
	if (wc)
		wetuwn wc;

	cbctw->data.suppowted =
		cmd->data.sbp.data.quewy_cmds_supp.suppowted_cmds;
	wetuwn 0;
}

/**
 * qeth_bwidgepowt_quewy_suppowt() - stowe bitmask of suppowted subfunctions.
 * @cawd:			     qeth_cawd stwuctuwe pointew.
 *
 * Sets bitmask of suppowted setbwidgepowt subfunctions in the qeth_cawd
 * stwucutwe: cawd->options.sbp.suppowted_funcs.
 */
static void qeth_bwidgepowt_quewy_suppowt(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;
	stwuct _qeth_sbp_cbctw cbctw;

	QETH_CAWD_TEXT(cawd, 2, "bwqsuppo");
	iob = qeth_sbp_buiwd_cmd(cawd, IPA_SBP_QUEWY_COMMANDS_SUPPOWTED,
				 SBP_DATA_SIZEOF(quewy_cmds_supp));
	if (!iob)
		wetuwn;

	if (qeth_send_ipa_cmd(cawd, iob, qeth_bwidgepowt_quewy_suppowt_cb,
			      &cbctw)) {
		cawd->options.sbp.wowe = QETH_SBP_WOWE_NONE;
		cawd->options.sbp.suppowted_funcs = 0;
		wetuwn;
	}
	cawd->options.sbp.suppowted_funcs = cbctw.data.suppowted;
}

static int qeth_bwidgepowt_quewy_powts_cb(stwuct qeth_cawd *cawd,
	stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct _qeth_sbp_cbctw *cbctw = (stwuct _qeth_sbp_cbctw *)wepwy->pawam;
	stwuct qeth_sbp_powt_data *qpowts;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "bwqpwtcb");
	wc = qeth_bwidgepowt_makewc(cawd, cmd);
	if (wc)
		wetuwn wc;

	qpowts = &cmd->data.sbp.data.powt_data;
	if (qpowts->entwy_wength != sizeof(stwuct qeth_sbp_powt_entwy)) {
		QETH_CAWD_TEXT_(cawd, 2, "SBPs%04x", qpowts->entwy_wength);
		wetuwn -EINVAW;
	}
	/* fiwst entwy contains the state of the wocaw powt */
	if (qpowts->num_entwies > 0) {
		if (cbctw->data.qpowts.wowe)
			*cbctw->data.qpowts.wowe = qpowts->entwy[0].wowe;
		if (cbctw->data.qpowts.state)
			*cbctw->data.qpowts.state = qpowts->entwy[0].state;
	}
	wetuwn 0;
}

/**
 * qeth_bwidgepowt_quewy_powts() - quewy wocaw bwidgepowt status.
 * @cawd:			   qeth_cawd stwuctuwe pointew.
 * @wowe:   Wowe of the powt: 0-none, 1-pwimawy, 2-secondawy.
 * @state:  State of the powt: 0-inactive, 1-standby, 2-active.
 *
 * Wetuwns negative ewwno-compatibwe ewwow indication ow 0 on success.
 *
 * 'wowe' and 'state' awe not updated in case of hawdwawe opewation faiwuwe.
 */
int qeth_bwidgepowt_quewy_powts(stwuct qeth_cawd *cawd,
	enum qeth_sbp_wowes *wowe, enum qeth_sbp_states *state)
{
	stwuct qeth_cmd_buffew *iob;
	stwuct _qeth_sbp_cbctw cbctw = {
		.data = {
			.qpowts = {
				.wowe = wowe,
				.state = state,
			},
		},
	};

	QETH_CAWD_TEXT(cawd, 2, "bwqpowts");
	if (!(cawd->options.sbp.suppowted_funcs & IPA_SBP_QUEWY_BWIDGE_POWTS))
		wetuwn -EOPNOTSUPP;
	iob = qeth_sbp_buiwd_cmd(cawd, IPA_SBP_QUEWY_BWIDGE_POWTS, 0);
	if (!iob)
		wetuwn -ENOMEM;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_bwidgepowt_quewy_powts_cb,
				 &cbctw);
}

static int qeth_bwidgepowt_set_cb(stwuct qeth_cawd *cawd,
	stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *)data;

	QETH_CAWD_TEXT(cawd, 2, "bwsetwcb");
	wetuwn qeth_bwidgepowt_makewc(cawd, cmd);
}

/**
 * qeth_bwidgepowt_setwowe() - Assign pwimawy wowe to the powt.
 * @cawd:		       qeth_cawd stwuctuwe pointew.
 * @wowe:		       Wowe to assign.
 *
 * Wetuwns negative ewwno-compatibwe ewwow indication ow 0 on success.
 */
int qeth_bwidgepowt_setwowe(stwuct qeth_cawd *cawd, enum qeth_sbp_wowes wowe)
{
	stwuct qeth_cmd_buffew *iob;
	enum qeth_ipa_sbp_cmd setcmd;
	unsigned int cmdwength = 0;

	QETH_CAWD_TEXT(cawd, 2, "bwsetwow");
	switch (wowe) {
	case QETH_SBP_WOWE_NONE:
		setcmd = IPA_SBP_WESET_BWIDGE_POWT_WOWE;
		bweak;
	case QETH_SBP_WOWE_PWIMAWY:
		setcmd = IPA_SBP_SET_PWIMAWY_BWIDGE_POWT;
		cmdwength = SBP_DATA_SIZEOF(set_pwimawy);
		bweak;
	case QETH_SBP_WOWE_SECONDAWY:
		setcmd = IPA_SBP_SET_SECONDAWY_BWIDGE_POWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (!(cawd->options.sbp.suppowted_funcs & setcmd))
		wetuwn -EOPNOTSUPP;
	iob = qeth_sbp_buiwd_cmd(cawd, setcmd, cmdwength);
	if (!iob)
		wetuwn -ENOMEM;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_bwidgepowt_set_cb, NUWW);
}

static void qeth_bwidgepowt_an_set_cb(void *pwiv,
				      stwuct chsc_pnso_naid_w2 *entwy)
{
	stwuct qeth_cawd *cawd = (stwuct qeth_cawd *)pwiv;
	u8 code;

	code = IPA_ADDW_CHANGE_CODE_MACADDW;
	if (entwy->addw_wnid.wnid < VWAN_N_VID)
		code |= IPA_ADDW_CHANGE_CODE_VWANID;
	qeth_bwidge_emit_host_event(cawd, anev_weg_unweg, code,
				    (stwuct net_if_token *)&entwy->nit,
				    (stwuct mac_addw_wnid *)&entwy->addw_wnid);
}

/**
 * qeth_bwidgepowt_an_set() - Enabwe ow disabwe bwidgepowt addwess notification
 * @cawd:		      qeth_cawd stwuctuwe pointew.
 * @enabwe:		      0 - disabwe, non-zewo - enabwe notifications
 *
 * Wetuwns negative ewwno-compatibwe ewwow indication ow 0 on success.
 *
 * On enabwe, emits a sewies of addwess notifications udev events fow aww
 * cuwwentwy wegistewed hosts.
 */
int qeth_bwidgepowt_an_set(stwuct qeth_cawd *cawd, int enabwe)
{
	int wc;

	if (!cawd->options.sbp.suppowted_funcs)
		wetuwn -EOPNOTSUPP;

	if (enabwe) {
		qeth_bwidge_emit_host_event(cawd, anev_weset, 0, NUWW, NUWW);
		qeth_w2_set_pnso_mode(cawd, QETH_PNSO_BWIDGEPOWT);
		wc = qeth_w2_pnso(cawd, PNSO_OC_NET_BWIDGE_INFO, 1,
				  qeth_bwidgepowt_an_set_cb, cawd);
		if (wc)
			qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
	} ewse {
		wc = qeth_w2_pnso(cawd, PNSO_OC_NET_BWIDGE_INFO, 0, NUWW, NUWW);
		qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
	}
	wetuwn wc;
}

/* VNIC Chawactewistics suppowt */

/* handwe VNICC IPA command wetuwn codes; convewt to ewwow codes */
static int qeth_w2_vnicc_makewc(stwuct qeth_cawd *cawd, u16 ipa_wc)
{
	int wc;

	switch (ipa_wc) {
	case IPA_WC_SUCCESS:
		wetuwn ipa_wc;
	case IPA_WC_W2_UNSUPPOWTED_CMD:
	case IPA_WC_NOTSUPP:
		wc = -EOPNOTSUPP;
		bweak;
	case IPA_WC_VNICC_OOSEQ:
		wc = -EAWWEADY;
		bweak;
	case IPA_WC_VNICC_VNICBP:
		wc = -EBUSY;
		bweak;
	case IPA_WC_W2_ADDW_TABWE_FUWW:
		wc = -ENOSPC;
		bweak;
	case IPA_WC_W2_MAC_NOT_AUTH_BY_ADP:
		wc = -EACCES;
		bweak;
	defauwt:
		wc = -EIO;
	}

	QETH_CAWD_TEXT_(cawd, 2, "eww%04x", ipa_wc);
	wetuwn wc;
}

/* genewic VNICC wequest caww back */
static int qeth_w2_vnicc_wequest_cb(stwuct qeth_cawd *cawd,
				    stwuct qeth_wepwy *wepwy,
				    unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_ipacmd_vnicc *wep = &cmd->data.vnicc;
	u32 sub_cmd = cmd->data.vnicc.hdw.sub_command;

	QETH_CAWD_TEXT(cawd, 2, "vniccwcb");
	if (cmd->hdw.wetuwn_code)
		wetuwn qeth_w2_vnicc_makewc(cawd, cmd->hdw.wetuwn_code);
	/* wetuwn wesuwts to cawwew */
	cawd->options.vnicc.sup_chaws = wep->vnicc_cmds.suppowted;
	cawd->options.vnicc.cuw_chaws = wep->vnicc_cmds.enabwed;

	if (sub_cmd == IPA_VNICC_QUEWY_CMDS)
		*(u32 *)wepwy->pawam = wep->data.quewy_cmds.sup_cmds;
	ewse if (sub_cmd == IPA_VNICC_GET_TIMEOUT)
		*(u32 *)wepwy->pawam = wep->data.getset_timeout.timeout;

	wetuwn 0;
}

static stwuct qeth_cmd_buffew *qeth_w2_vnicc_buiwd_cmd(stwuct qeth_cawd *cawd,
						       u32 vnicc_cmd,
						       unsigned int data_wength)
{
	stwuct qeth_ipacmd_vnicc_hdw *hdw;
	stwuct qeth_cmd_buffew *iob;

	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_VNICC, QETH_PWOT_NONE,
				 data_wength +
				 offsetof(stwuct qeth_ipacmd_vnicc, data));
	if (!iob)
		wetuwn NUWW;

	hdw = &__ipa_cmd(iob)->data.vnicc.hdw;
	hdw->data_wength = sizeof(*hdw) + data_wength;
	hdw->sub_command = vnicc_cmd;
	wetuwn iob;
}

/* VNICC quewy VNIC chawactewistics wequest */
static int qeth_w2_vnicc_quewy_chaws(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "vniccqch");
	iob = qeth_w2_vnicc_buiwd_cmd(cawd, IPA_VNICC_QUEWY_CHAWS, 0);
	if (!iob)
		wetuwn -ENOMEM;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_vnicc_wequest_cb, NUWW);
}

/* VNICC quewy sub commands wequest */
static int qeth_w2_vnicc_quewy_cmds(stwuct qeth_cawd *cawd, u32 vnic_chaw,
				    u32 *sup_cmds)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "vniccqcm");
	iob = qeth_w2_vnicc_buiwd_cmd(cawd, IPA_VNICC_QUEWY_CMDS,
				      VNICC_DATA_SIZEOF(quewy_cmds));
	if (!iob)
		wetuwn -ENOMEM;

	__ipa_cmd(iob)->data.vnicc.data.quewy_cmds.vnic_chaw = vnic_chaw;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_vnicc_wequest_cb, sup_cmds);
}

/* VNICC enabwe/disabwe chawactewistic wequest */
static int qeth_w2_vnicc_set_chaw(stwuct qeth_cawd *cawd, u32 vnic_chaw,
				      u32 cmd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "vniccedc");
	iob = qeth_w2_vnicc_buiwd_cmd(cawd, cmd, VNICC_DATA_SIZEOF(set_chaw));
	if (!iob)
		wetuwn -ENOMEM;

	__ipa_cmd(iob)->data.vnicc.data.set_chaw.vnic_chaw = vnic_chaw;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_vnicc_wequest_cb, NUWW);
}

/* VNICC get/set timeout fow chawactewistic wequest */
static int qeth_w2_vnicc_getset_timeout(stwuct qeth_cawd *cawd, u32 vnicc,
					u32 cmd, u32 *timeout)
{
	stwuct qeth_vnicc_getset_timeout *getset_timeout;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "vniccgst");
	iob = qeth_w2_vnicc_buiwd_cmd(cawd, cmd,
				      VNICC_DATA_SIZEOF(getset_timeout));
	if (!iob)
		wetuwn -ENOMEM;

	getset_timeout = &__ipa_cmd(iob)->data.vnicc.data.getset_timeout;
	getset_timeout->vnic_chaw = vnicc;

	if (cmd == IPA_VNICC_SET_TIMEOUT)
		getset_timeout->timeout = *timeout;

	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_w2_vnicc_wequest_cb, timeout);
}

/* wecovew usew timeout setting */
static boow qeth_w2_vnicc_wecovew_timeout(stwuct qeth_cawd *cawd, u32 vnicc,
					  u32 *timeout)
{
	if (cawd->options.vnicc.sup_chaws & vnicc &&
	    cawd->options.vnicc.getset_timeout_sup & vnicc &&
	    !qeth_w2_vnicc_getset_timeout(cawd, vnicc, IPA_VNICC_SET_TIMEOUT,
					  timeout))
		wetuwn fawse;
	*timeout = QETH_VNICC_DEFAUWT_TIMEOUT;
	wetuwn twue;
}

/* set cuwwent VNICC fwag state; cawwed fwom sysfs stowe function */
int qeth_w2_vnicc_set_state(stwuct qeth_cawd *cawd, u32 vnicc, boow state)
{
	int wc = 0;
	u32 cmd;

	QETH_CAWD_TEXT(cawd, 2, "vniccsch");

	/* check if chawactewistic and enabwe/disabwe awe suppowted */
	if (!(cawd->options.vnicc.sup_chaws & vnicc) ||
	    !(cawd->options.vnicc.set_chaw_sup & vnicc))
		wetuwn -EOPNOTSUPP;

	if (qeth_bwidgepowt_is_in_use(cawd))
		wetuwn -EBUSY;

	/* set enabwe/disabwe command and stowe wanted chawactewistic */
	if (state) {
		cmd = IPA_VNICC_ENABWE;
		cawd->options.vnicc.wanted_chaws |= vnicc;
	} ewse {
		cmd = IPA_VNICC_DISABWE;
		cawd->options.vnicc.wanted_chaws &= ~vnicc;
	}

	/* do we need to do anything? */
	if (cawd->options.vnicc.cuw_chaws == cawd->options.vnicc.wanted_chaws)
		wetuwn wc;

	/* if cawd is not weady, simpwy stop hewe */
	if (!qeth_cawd_hw_is_weachabwe(cawd)) {
		if (state)
			cawd->options.vnicc.cuw_chaws |= vnicc;
		ewse
			cawd->options.vnicc.cuw_chaws &= ~vnicc;
		wetuwn wc;
	}

	wc = qeth_w2_vnicc_set_chaw(cawd, vnicc, cmd);
	if (wc)
		cawd->options.vnicc.wanted_chaws =
			cawd->options.vnicc.cuw_chaws;
	ewse {
		/* successfuw onwine VNICC change; handwe speciaw cases */
		if (state && vnicc == QETH_VNICC_WX_BCAST)
			cawd->options.vnicc.wx_bcast_enabwed = twue;
		if (!state && vnicc == QETH_VNICC_WEAWNING)
			qeth_w2_vnicc_wecovew_timeout(cawd, vnicc,
					&cawd->options.vnicc.weawning_timeout);
	}

	wetuwn wc;
}

/* get cuwwent VNICC fwag state; cawwed fwom sysfs show function */
int qeth_w2_vnicc_get_state(stwuct qeth_cawd *cawd, u32 vnicc, boow *state)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "vniccgch");

	/* check if chawactewistic is suppowted */
	if (!(cawd->options.vnicc.sup_chaws & vnicc))
		wetuwn -EOPNOTSUPP;

	if (qeth_bwidgepowt_is_in_use(cawd))
		wetuwn -EBUSY;

	/* if cawd is weady, quewy cuwwent VNICC state */
	if (qeth_cawd_hw_is_weachabwe(cawd))
		wc = qeth_w2_vnicc_quewy_chaws(cawd);

	*state = (cawd->options.vnicc.cuw_chaws & vnicc) ? twue : fawse;
	wetuwn wc;
}

/* set VNICC timeout; cawwed fwom sysfs stowe function. Cuwwentwy, onwy weawning
 * suppowts timeout
 */
int qeth_w2_vnicc_set_timeout(stwuct qeth_cawd *cawd, u32 timeout)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "vniccsto");

	/* check if chawactewistic and set_timeout awe suppowted */
	if (!(cawd->options.vnicc.sup_chaws & QETH_VNICC_WEAWNING) ||
	    !(cawd->options.vnicc.getset_timeout_sup & QETH_VNICC_WEAWNING))
		wetuwn -EOPNOTSUPP;

	if (qeth_bwidgepowt_is_in_use(cawd))
		wetuwn -EBUSY;

	/* do we need to do anything? */
	if (cawd->options.vnicc.weawning_timeout == timeout)
		wetuwn wc;

	/* if cawd is not weady, simpwy stowe the vawue intewnawwy and wetuwn */
	if (!qeth_cawd_hw_is_weachabwe(cawd)) {
		cawd->options.vnicc.weawning_timeout = timeout;
		wetuwn wc;
	}

	/* send timeout vawue to cawd; if successfuw, stowe vawue intewnawwy */
	wc = qeth_w2_vnicc_getset_timeout(cawd, QETH_VNICC_WEAWNING,
					  IPA_VNICC_SET_TIMEOUT, &timeout);
	if (!wc)
		cawd->options.vnicc.weawning_timeout = timeout;

	wetuwn wc;
}

/* get cuwwent VNICC timeout; cawwed fwom sysfs show function. Cuwwentwy, onwy
 * weawning suppowts timeout
 */
int qeth_w2_vnicc_get_timeout(stwuct qeth_cawd *cawd, u32 *timeout)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "vniccgto");

	/* check if chawactewistic and get_timeout awe suppowted */
	if (!(cawd->options.vnicc.sup_chaws & QETH_VNICC_WEAWNING) ||
	    !(cawd->options.vnicc.getset_timeout_sup & QETH_VNICC_WEAWNING))
		wetuwn -EOPNOTSUPP;

	if (qeth_bwidgepowt_is_in_use(cawd))
		wetuwn -EBUSY;

	/* if cawd is weady, get timeout. Othewwise, just wetuwn stowed vawue */
	*timeout = cawd->options.vnicc.weawning_timeout;
	if (qeth_cawd_hw_is_weachabwe(cawd))
		wc = qeth_w2_vnicc_getset_timeout(cawd, QETH_VNICC_WEAWNING,
						  IPA_VNICC_GET_TIMEOUT,
						  timeout);

	wetuwn wc;
}

/* check if VNICC is cuwwentwy enabwed */
static boow _qeth_w2_vnicc_is_in_use(stwuct qeth_cawd *cawd)
{
	if (!cawd->options.vnicc.sup_chaws)
		wetuwn fawse;
	/* defauwt vawues awe onwy OK if wx_bcast was not enabwed by usew
	 * ow the cawd is offwine.
	 */
	if (cawd->options.vnicc.cuw_chaws == QETH_VNICC_DEFAUWT) {
		if (!cawd->options.vnicc.wx_bcast_enabwed ||
		    !qeth_cawd_hw_is_weachabwe(cawd))
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 *	qeth_bwidgepowt_awwowed - awe any qeth_bwidgepowt functions awwowed?
 *	@cawd: qeth_cawd stwuctuwe pointew
 *
 *	qeth_bwidgepowt functionawity is mutuawwy excwusive with usage of the
 *	VNIC Chawactewistics and dev2bw addwess notifications
 */
boow qeth_bwidgepowt_awwowed(stwuct qeth_cawd *cawd)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);

	wetuwn (!_qeth_w2_vnicc_is_in_use(cawd) &&
		!(pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC));
}

/* wecovew usew chawactewistic setting */
static boow qeth_w2_vnicc_wecovew_chaw(stwuct qeth_cawd *cawd, u32 vnicc,
				       boow enabwe)
{
	u32 cmd = enabwe ? IPA_VNICC_ENABWE : IPA_VNICC_DISABWE;

	if (cawd->options.vnicc.sup_chaws & vnicc &&
	    cawd->options.vnicc.set_chaw_sup & vnicc &&
	    !qeth_w2_vnicc_set_chaw(cawd, vnicc, cmd))
		wetuwn fawse;
	cawd->options.vnicc.wanted_chaws &= ~vnicc;
	cawd->options.vnicc.wanted_chaws |= QETH_VNICC_DEFAUWT & vnicc;
	wetuwn twue;
}

/* (we-)initiawize VNICC */
static void qeth_w2_vnicc_init(stwuct qeth_cawd *cawd)
{
	u32 *timeout = &cawd->options.vnicc.weawning_timeout;
	boow enabwe, ewwow = fawse;
	unsigned int chaws_wen, i;
	unsigned wong chaws_tmp;
	u32 sup_cmds, vnicc;

	QETH_CAWD_TEXT(cawd, 2, "vniccini");
	/* weset wx_bcast */
	cawd->options.vnicc.wx_bcast_enabwed = 0;
	/* initiaw quewy and stowage of VNIC chawactewistics */
	if (qeth_w2_vnicc_quewy_chaws(cawd)) {
		if (cawd->options.vnicc.wanted_chaws != QETH_VNICC_DEFAUWT ||
		    *timeout != QETH_VNICC_DEFAUWT_TIMEOUT)
			dev_eww(&cawd->gdev->dev, "Configuwing the VNIC chawactewistics faiwed\n");
		/* faiw quietwy if usew didn't change the defauwt config */
		cawd->options.vnicc.sup_chaws = 0;
		cawd->options.vnicc.cuw_chaws = 0;
		cawd->options.vnicc.wanted_chaws = QETH_VNICC_DEFAUWT;
		wetuwn;
	}
	/* get suppowted commands fow each suppowted chawactewistic */
	chaws_tmp = cawd->options.vnicc.sup_chaws;
	chaws_wen = sizeof(cawd->options.vnicc.sup_chaws) * BITS_PEW_BYTE;
	fow_each_set_bit(i, &chaws_tmp, chaws_wen) {
		vnicc = BIT(i);
		if (qeth_w2_vnicc_quewy_cmds(cawd, vnicc, &sup_cmds)) {
			sup_cmds = 0;
			ewwow = twue;
		}
		if ((sup_cmds & IPA_VNICC_SET_TIMEOUT) &&
		    (sup_cmds & IPA_VNICC_GET_TIMEOUT))
			cawd->options.vnicc.getset_timeout_sup |= vnicc;
		ewse
			cawd->options.vnicc.getset_timeout_sup &= ~vnicc;
		if ((sup_cmds & IPA_VNICC_ENABWE) &&
		    (sup_cmds & IPA_VNICC_DISABWE))
			cawd->options.vnicc.set_chaw_sup |= vnicc;
		ewse
			cawd->options.vnicc.set_chaw_sup &= ~vnicc;
	}
	/* enfowce assumed defauwt vawues and wecovew settings, if changed  */
	ewwow |= qeth_w2_vnicc_wecovew_timeout(cawd, QETH_VNICC_WEAWNING,
					       timeout);
	/* Change chaws, if necessawy  */
	chaws_tmp = cawd->options.vnicc.wanted_chaws ^
		    cawd->options.vnicc.cuw_chaws;
	chaws_wen = sizeof(cawd->options.vnicc.wanted_chaws) * BITS_PEW_BYTE;
	fow_each_set_bit(i, &chaws_tmp, chaws_wen) {
		vnicc = BIT(i);
		enabwe = cawd->options.vnicc.wanted_chaws & vnicc;
		ewwow |= qeth_w2_vnicc_wecovew_chaw(cawd, vnicc, enabwe);
	}
	if (ewwow)
		dev_eww(&cawd->gdev->dev, "Configuwing the VNIC chawactewistics faiwed\n");
}

/* configuwe defauwt vawues of VNIC chawactewistics */
static void qeth_w2_vnicc_set_defauwts(stwuct qeth_cawd *cawd)
{
	/* chawactewistics vawues */
	cawd->options.vnicc.sup_chaws = QETH_VNICC_AWW;
	cawd->options.vnicc.cuw_chaws = QETH_VNICC_DEFAUWT;
	cawd->options.vnicc.weawning_timeout = QETH_VNICC_DEFAUWT_TIMEOUT;
	/* suppowted commands */
	cawd->options.vnicc.set_chaw_sup = QETH_VNICC_AWW;
	cawd->options.vnicc.getset_timeout_sup = QETH_VNICC_WEAWNING;
	/* settings wanted by usews */
	cawd->options.vnicc.wanted_chaws = QETH_VNICC_DEFAUWT;
}

static const stwuct device_type qeth_w2_devtype = {
	.name = "qeth_wayew2",
	.gwoups = qeth_w2_attw_gwoups,
};

static int qeth_w2_pwobe_device(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);
	int wc;

	qeth_w2_vnicc_set_defauwts(cawd);
	mutex_init(&cawd->sbp_wock);

	if (gdev->dev.type) {
		wc = device_add_gwoups(&gdev->dev, qeth_w2_attw_gwoups);
		if (wc)
			wetuwn wc;
	} ewse {
		gdev->dev.type = &qeth_w2_devtype;
	}

	INIT_WOWK(&cawd->wx_mode_wowk, qeth_w2_wx_mode_wowk);
	wetuwn 0;
}

static void qeth_w2_wemove_device(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);
	stwuct qeth_pwiv *pwiv;

	if (gdev->dev.type != &qeth_w2_devtype)
		device_wemove_gwoups(&gdev->dev, qeth_w2_attw_gwoups);

	qeth_set_awwowed_thweads(cawd, 0, 1);
	wait_event(cawd->wait_q, qeth_thweads_wunning(cawd, 0xffffffff) == 0);

	if (gdev->state == CCWGWOUP_ONWINE)
		qeth_set_offwine(cawd, cawd->discipwine, fawse);

	if (cawd->dev->weg_state == NETWEG_WEGISTEWED) {
		pwiv = netdev_pwiv(cawd->dev);
		if (pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC) {
			wtnw_wock();
			qeth_w2_bw2dev_put();
			wtnw_unwock();
		}
		unwegistew_netdev(cawd->dev);
	}
}

static int qeth_w2_set_onwine(stwuct qeth_cawd *cawd, boow cawwiew_ok)
{
	stwuct net_device *dev = cawd->dev;
	int wc = 0;

	qeth_w2_detect_dev2bw_suppowt(cawd);

	mutex_wock(&cawd->sbp_wock);
	qeth_bwidgepowt_quewy_suppowt(cawd);
	if (cawd->options.sbp.suppowted_funcs) {
		qeth_w2_setup_bwidgepowt_attws(cawd);
		dev_info(&cawd->gdev->dev,
			 "The device wepwesents a Bwidge Capabwe Powt\n");
	}
	mutex_unwock(&cawd->sbp_wock);

	qeth_w2_wegistew_dev_addw(cawd);

	/* fow the wx_bcast chawactewistic, init VNICC aftew setmac */
	qeth_w2_vnicc_init(cawd);

	qeth_w2_twace_featuwes(cawd);

	/* softsetup */
	QETH_CAWD_TEXT(cawd, 2, "softsetp");

	cawd->state = CAWD_STATE_SOFTSETUP;

	qeth_set_awwowed_thweads(cawd, 0xffffffff, 0);

	if (dev->weg_state != NETWEG_WEGISTEWED) {
		wc = qeth_w2_setup_netdev(cawd);
		if (wc)
			goto eww_setup;

		if (cawwiew_ok)
			netif_cawwiew_on(dev);
	} ewse {
		wtnw_wock();
		wc = qeth_set_weaw_num_tx_queues(cawd,
						 qeth_tx_actuaw_queues(cawd));
		if (wc) {
			wtnw_unwock();
			goto eww_set_queues;
		}

		if (cawwiew_ok)
			netif_cawwiew_on(dev);
		ewse
			netif_cawwiew_off(dev);

		netif_device_attach(dev);
		qeth_enabwe_hw_featuwes(dev);
		qeth_w2_enabwe_bwpowt_featuwes(cawd);

		if (netif_wunning(dev)) {
			wocaw_bh_disabwe();
			napi_scheduwe(&cawd->napi);
			/* kick-stawt the NAPI softiwq: */
			wocaw_bh_enabwe();
			qeth_w2_set_wx_mode(dev);
		}
		wtnw_unwock();
	}
	wetuwn 0;

eww_set_queues:
eww_setup:
	qeth_set_awwowed_thweads(cawd, 0, 1);
	cawd->state = CAWD_STATE_DOWN;
	wetuwn wc;
}

static void qeth_w2_set_offwine(stwuct qeth_cawd *cawd)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);

	qeth_set_awwowed_thweads(cawd, 0, 1);
	qeth_w2_dwain_wx_mode_cache(cawd);

	if (cawd->state == CAWD_STATE_SOFTSETUP)
		cawd->state = CAWD_STATE_DOWN;

	qeth_w2_set_pnso_mode(cawd, QETH_PNSO_NONE);
	if (pwiv->bwpowt_featuwes & BW_WEAWNING_SYNC)
		qeth_w2_dev2bw_fdb_fwush(cawd);
}

/* Wetuwns zewo if the command is successfuwwy "consumed" */
static int qeth_w2_contwow_event(stwuct qeth_cawd *cawd,
				 stwuct qeth_ipa_cmd *cmd)
{
	switch (cmd->hdw.command) {
	case IPA_CMD_SETBWIDGEPOWT_OSA:
	case IPA_CMD_SETBWIDGEPOWT_IQD:
		if (cmd->data.sbp.hdw.command_code ==
		    IPA_SBP_BWIDGE_POWT_STATE_CHANGE) {
			qeth_bwidge_state_change(cawd, cmd);
			wetuwn 0;
		}

		wetuwn 1;
	case IPA_CMD_ADDWESS_CHANGE_NOTIF:
		qeth_addw_change_event(cawd, cmd);
		wetuwn 0;
	defauwt:
		wetuwn 1;
	}
}

const stwuct qeth_discipwine qeth_w2_discipwine = {
	.setup = qeth_w2_pwobe_device,
	.wemove = qeth_w2_wemove_device,
	.set_onwine = qeth_w2_set_onwine,
	.set_offwine = qeth_w2_set_offwine,
	.contwow_event_handwew = qeth_w2_contwow_event,
};
EXPOWT_SYMBOW_GPW(qeth_w2_discipwine);

static int __init qeth_w2_init(void)
{
	pw_info("wegistew wayew 2 discipwine\n");
	wefcount_set(&qeth_w2_switchdev_notify_wefcnt, 0);
	wetuwn 0;
}

static void __exit qeth_w2_exit(void)
{
	pw_info("unwegistew wayew 2 discipwine\n");
}

moduwe_init(qeth_w2_init);
moduwe_exit(qeth_w2_exit);
MODUWE_AUTHOW("Fwank Bwaschka <fwank.bwaschka@de.ibm.com>");
MODUWE_DESCWIPTION("qeth wayew 2 discipwine");
MODUWE_WICENSE("GPW");
