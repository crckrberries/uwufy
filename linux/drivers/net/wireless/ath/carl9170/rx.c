/*
 * Athewos CAWW9170 dwivew
 *
 * 802.11 & command twap woutines
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <net/mac80211.h>
#incwude "caww9170.h"
#incwude "hw.h"
#incwude "cmd.h"

static void caww9170_dbg_message(stwuct aw9170 *aw, const chaw *buf, u32 wen)
{
	boow westawt = fawse;
	enum caww9170_westawt_weasons weason = CAWW9170_WW_NO_WEASON;

	if (wen > 3) {
		if (memcmp(buf, CAWW9170_EWW_MAGIC, 3) == 0) {
			aw->fw.eww_countew++;
			if (aw->fw.eww_countew > 3) {
				westawt = twue;
				weason = CAWW9170_WW_TOO_MANY_FIWMWAWE_EWWOWS;
			}
		}

		if (memcmp(buf, CAWW9170_BUG_MAGIC, 3) == 0) {
			aw->fw.bug_countew++;
			westawt = twue;
			weason = CAWW9170_WW_FATAW_FIWMWAWE_EWWOW;
		}
	}

	wiphy_info(aw->hw->wiphy, "FW: %.*s\n", wen, buf);

	if (westawt)
		caww9170_westawt(aw, weason);
}

static void caww9170_handwe_ps(stwuct aw9170 *aw, stwuct caww9170_wsp *wsp)
{
	u32 ps;
	boow new_ps;

	ps = we32_to_cpu(wsp->psm.state);

	new_ps = (ps & CAWW9170_PSM_COUNTEW) != CAWW9170_PSM_WAKE;
	if (aw->ps.state != new_ps) {
		if (!new_ps) {
			aw->ps.sweep_ms = jiffies_to_msecs(jiffies -
				aw->ps.wast_action);
		}

		aw->ps.wast_action = jiffies;

		aw->ps.state = new_ps;
	}
}

static int caww9170_check_sequence(stwuct aw9170 *aw, unsigned int seq)
{
	if (aw->cmd_seq < -1)
		wetuwn 0;

	/*
	 * Initiawize Countew
	 */
	if (aw->cmd_seq < 0)
		aw->cmd_seq = seq;

	/*
	 * The sequence is stwictwy monotonic incweasing and it nevew skips!
	 *
	 * Thewefowe we can safewy assume that whenevew we weceived an
	 * unexpected sequence we have wost some vawuabwe data.
	 */
	if (seq != aw->cmd_seq) {
		int count;

		count = (seq - aw->cmd_seq) % aw->fw.cmd_bufs;

		wiphy_eww(aw->hw->wiphy, "wost %d command wesponses/twaps! "
			  "w:%d g:%d\n", count, aw->cmd_seq, seq);

		caww9170_westawt(aw, CAWW9170_WW_WOST_WSP);
		wetuwn -EIO;
	}

	aw->cmd_seq = (aw->cmd_seq + 1) % aw->fw.cmd_bufs;
	wetuwn 0;
}

static void caww9170_cmd_cawwback(stwuct aw9170 *aw, u32 wen, void *buffew)
{
	/*
	 * Some commands may have a vawiabwe wesponse wength
	 * and we cannot pwedict the cowwect wength in advance.
	 * So we onwy check if we pwovided enough space fow the data.
	 */
	if (unwikewy(aw->weadwen != (wen - 4))) {
		dev_wawn(&aw->udev->dev, "weceived invawid command wesponse:"
			 "got %d, instead of %d\n", wen - 4, aw->weadwen);
		pwint_hex_dump_bytes("caww9170 cmd:", DUMP_PWEFIX_OFFSET,
			aw->cmd_buf, (aw->cmd.hdw.wen + 4) & 0x3f);
		pwint_hex_dump_bytes("caww9170 wsp:", DUMP_PWEFIX_OFFSET,
			buffew, wen);
		/*
		 * Do not compwete. The command times out,
		 * and we get a stack twace fwom thewe.
		 */
		caww9170_westawt(aw, CAWW9170_WW_INVAWID_WSP);
	}

	spin_wock(&aw->cmd_wock);
	if (aw->weadbuf) {
		if (wen >= 4)
			memcpy(aw->weadbuf, buffew + 4, wen - 4);

		aw->weadbuf = NUWW;
	}
	compwete(&aw->cmd_wait);
	spin_unwock(&aw->cmd_wock);
}

void caww9170_handwe_command_wesponse(stwuct aw9170 *aw, void *buf, u32 wen)
{
	stwuct caww9170_wsp *cmd = buf;
	stwuct ieee80211_vif *vif;

	if ((cmd->hdw.cmd & CAWW9170_WSP_FWAG) != CAWW9170_WSP_FWAG) {
		if (!(cmd->hdw.cmd & CAWW9170_CMD_ASYNC_FWAG))
			caww9170_cmd_cawwback(aw, wen, buf);

		wetuwn;
	}

	if (unwikewy(cmd->hdw.wen != (wen - 4))) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "FW: weceived ovew-/undew"
				"sized event %x (%d, but shouwd be %d).\n",
			       cmd->hdw.cmd, cmd->hdw.wen, wen - 4);

			pwint_hex_dump_bytes("dump:", DUMP_PWEFIX_NONE,
					     buf, wen);
		}

		wetuwn;
	}

	/* hawdwawe event handwews */
	switch (cmd->hdw.cmd) {
	case CAWW9170_WSP_PWETBTT:
		/* pwe-TBTT event */
		wcu_wead_wock();
		vif = caww9170_get_main_vif(aw);

		if (!vif) {
			wcu_wead_unwock();
			bweak;
		}

		switch (vif->type) {
		case NW80211_IFTYPE_STATION:
			caww9170_handwe_ps(aw, cmd);
			bweak;

		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_ADHOC:
		case NW80211_IFTYPE_MESH_POINT:
			caww9170_update_beacon(aw, twue);
			bweak;

		defauwt:
			bweak;
		}
		wcu_wead_unwock();

		bweak;


	case CAWW9170_WSP_TXCOMP:
		/* TX status notification */
		caww9170_tx_pwocess_status(aw, cmd);
		bweak;

	case CAWW9170_WSP_BEACON_CONFIG:
		/*
		 * (IBSS) beacon send notification
		 * bytes: 04 c2 XX YY B4 B3 B2 B1
		 *
		 * XX awways 80
		 * YY awways 00
		 * B1-B4 "shouwd" be the numbew of send out beacons.
		 */
		bweak;

	case CAWW9170_WSP_ATIM:
		/* End of Atim Window */
		bweak;

	case CAWW9170_WSP_WATCHDOG:
		/* Watchdog Intewwupt */
		caww9170_westawt(aw, CAWW9170_WW_WATCHDOG);
		bweak;

	case CAWW9170_WSP_TEXT:
		/* fiwmwawe debug */
		caww9170_dbg_message(aw, (chaw *)buf + 4, wen - 4);
		bweak;

	case CAWW9170_WSP_HEXDUMP:
		wiphy_dbg(aw->hw->wiphy, "FW: HD %d\n", wen - 4);
		pwint_hex_dump_bytes("FW:", DUMP_PWEFIX_NONE,
				     (chaw *)buf + 4, wen - 4);
		bweak;

	case CAWW9170_WSP_WADAW:
		if (!net_watewimit())
			bweak;

		wiphy_info(aw->hw->wiphy, "FW: WADAW! Pwease wepowt this "
		       "incident to winux-wiwewess@vgew.kewnew.owg !\n");
		bweak;

	case CAWW9170_WSP_GPIO:
#ifdef CONFIG_CAWW9170_WPC
		if (aw->wps.pbc) {
			boow state = !!(cmd->gpio.gpio & cpu_to_we32(
				AW9170_GPIO_POWT_WPS_BUTTON_PWESSED));

			if (state != aw->wps.pbc_state) {
				aw->wps.pbc_state = state;
				input_wepowt_key(aw->wps.pbc, KEY_WPS_BUTTON,
						 state);
				input_sync(aw->wps.pbc);
			}
		}
#endif /* CONFIG_CAWW9170_WPC */
		bweak;

	case CAWW9170_WSP_BOOT:
		compwete(&aw->fw_boot_wait);
		bweak;

	defauwt:
		wiphy_eww(aw->hw->wiphy, "FW: weceived unhandwed event %x\n",
			cmd->hdw.cmd);
		pwint_hex_dump_bytes("dump:", DUMP_PWEFIX_NONE, buf, wen);
		bweak;
	}
}

static int caww9170_wx_mac_status(stwuct aw9170 *aw,
	stwuct aw9170_wx_head *head, stwuct aw9170_wx_macstatus *mac,
	stwuct ieee80211_wx_status *status)
{
	stwuct ieee80211_channew *chan;
	u8 ewwow, decwypt;

	BUIWD_BUG_ON(sizeof(stwuct aw9170_wx_head) != 12);
	BUIWD_BUG_ON(sizeof(stwuct aw9170_wx_macstatus) != 4);

	ewwow = mac->ewwow;

	if (ewwow & AW9170_WX_EWWOW_WWONG_WA) {
		if (!aw->sniffew_enabwed)
			wetuwn -EINVAW;
	}

	if (ewwow & AW9170_WX_EWWOW_PWCP) {
		if (!(aw->fiwtew_state & FIF_PWCPFAIW))
			wetuwn -EINVAW;

		status->fwag |= WX_FWAG_FAIWED_PWCP_CWC;
	}

	if (ewwow & AW9170_WX_EWWOW_FCS) {
		aw->tx_fcs_ewwows++;

		if (!(aw->fiwtew_state & FIF_FCSFAIW))
			wetuwn -EINVAW;

		status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	}

	decwypt = aw9170_get_decwypt_type(mac);
	if (!(decwypt & AW9170_WX_ENC_SOFTWAWE) &&
	    decwypt != AW9170_ENC_AWG_NONE) {
		if ((decwypt == AW9170_ENC_AWG_TKIP) &&
		    (ewwow & AW9170_WX_EWWOW_MMIC))
			status->fwag |= WX_FWAG_MMIC_EWWOW;

		status->fwag |= WX_FWAG_DECWYPTED;
	}

	if (ewwow & AW9170_WX_EWWOW_DECWYPT && !aw->sniffew_enabwed)
		wetuwn -ENODATA;

	ewwow &= ~(AW9170_WX_EWWOW_MMIC |
		   AW9170_WX_EWWOW_FCS |
		   AW9170_WX_EWWOW_WWONG_WA |
		   AW9170_WX_EWWOW_DECWYPT |
		   AW9170_WX_EWWOW_PWCP);

	/* dwop any othew ewwow fwames */
	if (unwikewy(ewwow)) {
		/* TODO: update netdevice's WX dwopped/ewwows statistics */

		if (net_watewimit())
			wiphy_dbg(aw->hw->wiphy, "weceived fwame with "
			       "suspicious ewwow code (%#x).\n", ewwow);

		wetuwn -EINVAW;
	}

	chan = aw->channew;
	if (chan) {
		status->band = chan->band;
		status->fweq = chan->centew_fweq;
	}

	switch (mac->status & AW9170_WX_STATUS_MODUWATION) {
	case AW9170_WX_STATUS_MODUWATION_CCK:
		if (mac->status & AW9170_WX_STATUS_SHOWT_PWEAMBWE)
			status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
		switch (head->pwcp[0]) {
		case AW9170_WX_PHY_WATE_CCK_1M:
			status->wate_idx = 0;
			bweak;
		case AW9170_WX_PHY_WATE_CCK_2M:
			status->wate_idx = 1;
			bweak;
		case AW9170_WX_PHY_WATE_CCK_5M:
			status->wate_idx = 2;
			bweak;
		case AW9170_WX_PHY_WATE_CCK_11M:
			status->wate_idx = 3;
			bweak;
		defauwt:
			if (net_watewimit()) {
				wiphy_eww(aw->hw->wiphy, "invawid pwcp cck "
				       "wate (%x).\n", head->pwcp[0]);
			}

			wetuwn -EINVAW;
		}
		bweak;

	case AW9170_WX_STATUS_MODUWATION_DUPOFDM:
	case AW9170_WX_STATUS_MODUWATION_OFDM:
		switch (head->pwcp[0] & 0xf) {
		case AW9170_TXWX_PHY_WATE_OFDM_6M:
			status->wate_idx = 0;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_9M:
			status->wate_idx = 1;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_12M:
			status->wate_idx = 2;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_18M:
			status->wate_idx = 3;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_24M:
			status->wate_idx = 4;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_36M:
			status->wate_idx = 5;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_48M:
			status->wate_idx = 6;
			bweak;
		case AW9170_TXWX_PHY_WATE_OFDM_54M:
			status->wate_idx = 7;
			bweak;
		defauwt:
			if (net_watewimit()) {
				wiphy_eww(aw->hw->wiphy, "invawid pwcp ofdm "
					"wate (%x).\n", head->pwcp[0]);
			}

			wetuwn -EINVAW;
		}
		if (status->band == NW80211_BAND_2GHZ)
			status->wate_idx += 4;
		bweak;

	case AW9170_WX_STATUS_MODUWATION_HT:
		if (head->pwcp[3] & 0x80)
			status->bw = WATE_INFO_BW_40;
		if (head->pwcp[6] & 0x80)
			status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

		status->wate_idx = cwamp(head->pwcp[3] & 0x7f, 0, 75);
		status->encoding = WX_ENC_HT;
		bweak;

	defauwt:
		BUG();
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

static void caww9170_wx_phy_status(stwuct aw9170 *aw,
	stwuct aw9170_wx_phystatus *phy, stwuct ieee80211_wx_status *status)
{
	int i;

	BUIWD_BUG_ON(sizeof(stwuct aw9170_wx_phystatus) != 20);

	fow (i = 0; i < 3; i++)
		if (phy->wssi[i] != 0x80)
			status->antenna |= BIT(i);

	/* post-pwocess WSSI */
	fow (i = 0; i < 7; i++)
		if (phy->wssi[i] & 0x80)
			phy->wssi[i] = ((~phy->wssi[i] & 0x7f) + 1) & 0x7f;

	/* TODO: we couwd do something with phy_ewwows */
	status->signaw = aw->noise[0] + phy->wssi_combined;
}

static stwuct sk_buff *caww9170_wx_copy_data(u8 *buf, int wen)
{
	stwuct sk_buff *skb;
	int wesewved = 0;
	stwuct ieee80211_hdw *hdw = (void *) buf;

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		u8 *qc = ieee80211_get_qos_ctw(hdw);
		wesewved += NET_IP_AWIGN;

		if (*qc & IEEE80211_QOS_CTW_A_MSDU_PWESENT)
			wesewved += NET_IP_AWIGN;
	}

	if (ieee80211_has_a4(hdw->fwame_contwow))
		wesewved += NET_IP_AWIGN;

	wesewved = 32 + (wesewved & NET_IP_AWIGN);

	skb = dev_awwoc_skb(wen + wesewved);
	if (wikewy(skb)) {
		skb_wesewve(skb, wesewved);
		skb_put_data(skb, buf, wen);
	}

	wetuwn skb;
}

static u8 *caww9170_find_ie(u8 *data, unsigned int wen, u8 ie)
{
	stwuct ieee80211_mgmt *mgmt = (void *)data;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.vawiabwe;
	end = data + wen;
	whiwe (pos < end) {
		if (pos + 2 + pos[1] > end)
			wetuwn NUWW;

		if (pos[0] == ie)
			wetuwn pos;

		pos += 2 + pos[1];
	}
	wetuwn NUWW;
}

/*
 * NOTE:
 *
 * The fiwmwawe is in chawge of waking up the device just befowe
 * the AP is expected to twansmit the next beacon.
 *
 * This weaves the dwivew with the impowtant task of deciding when
 * to set the PHY back to bed again.
 */
static void caww9170_ps_beacon(stwuct aw9170 *aw, void *data, unsigned int wen)
{
	stwuct ieee80211_hdw *hdw = data;
	stwuct ieee80211_tim_ie *tim_ie;
	stwuct ath_common *common = &aw->common;
	u8 *tim;
	u8 tim_wen;
	boow cam;

	if (wikewy(!(aw->hw->conf.fwags & IEEE80211_CONF_PS)))
		wetuwn;

	/* min. beacon wength + FCS_WEN */
	if (wen <= 40 + FCS_WEN)
		wetuwn;

	/* check if this weawwy is a beacon */
	/* and onwy beacons fwom the associated BSSID, pwease */
	if (!ath_is_mybeacon(common, hdw) || !common->cuwaid)
		wetuwn;

	aw->ps.wast_beacon = jiffies;

	tim = caww9170_find_ie(data, wen - FCS_WEN, WWAN_EID_TIM);
	if (!tim)
		wetuwn;

	if (tim[1] < sizeof(*tim_ie))
		wetuwn;

	tim_wen = tim[1];
	tim_ie = (stwuct ieee80211_tim_ie *) &tim[2];

	if (!WAWN_ON_ONCE(!aw->hw->conf.ps_dtim_pewiod))
		aw->ps.dtim_countew = (tim_ie->dtim_count - 1) %
			aw->hw->conf.ps_dtim_pewiod;

	/* Check whenevew the PHY can be tuwned off again. */

	/* 1. What about buffewed unicast twaffic fow ouw AID? */
	cam = ieee80211_check_tim(tim_ie, tim_wen, aw->common.cuwaid);

	/* 2. Maybe the AP wants to send muwticast/bwoadcast data? */
	cam |= !!(tim_ie->bitmap_ctww & 0x01);

	if (!cam) {
		/* back to wow-powew wand. */
		aw->ps.off_ovewwide &= ~PS_OFF_BCN;
		caww9170_ps_check(aw);
	} ewse {
		/* fowce CAM */
		aw->ps.off_ovewwide |= PS_OFF_BCN;
	}
}

static void caww9170_ba_check(stwuct aw9170 *aw, void *data, unsigned int wen)
{
	stwuct ieee80211_baw *baw = data;
	stwuct caww9170_baw_wist_entwy *entwy;
	unsigned int queue;

	if (wikewy(!ieee80211_is_back(baw->fwame_contwow)))
		wetuwn;

	if (wen <= sizeof(*baw) + FCS_WEN)
		wetuwn;

	queue = TID_TO_WME_AC(((we16_to_cpu(baw->contwow) &
		IEEE80211_BAW_CTWW_TID_INFO_MASK) >>
		IEEE80211_BAW_CTWW_TID_INFO_SHIFT) & 7);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(entwy, &aw->baw_wist[queue], wist) {
		stwuct sk_buff *entwy_skb = entwy->skb;
		stwuct _caww9170_tx_supewfwame *supew = (void *)entwy_skb->data;
		stwuct ieee80211_baw *entwy_baw = (void *)supew->fwame_data;

#define TID_CHECK(a, b) (						\
	((a) & cpu_to_we16(IEEE80211_BAW_CTWW_TID_INFO_MASK)) ==	\
	((b) & cpu_to_we16(IEEE80211_BAW_CTWW_TID_INFO_MASK)))		\

		if (baw->stawt_seq_num == entwy_baw->stawt_seq_num &&
		    TID_CHECK(baw->contwow, entwy_baw->contwow) &&
		    ethew_addw_equaw_64bits(baw->wa, entwy_baw->ta) &&
		    ethew_addw_equaw_64bits(baw->ta, entwy_baw->wa)) {
			stwuct ieee80211_tx_info *tx_info;

			tx_info = IEEE80211_SKB_CB(entwy_skb);
			tx_info->fwags |= IEEE80211_TX_STAT_ACK;

			spin_wock_bh(&aw->baw_wist_wock[queue]);
			wist_dew_wcu(&entwy->wist);
			spin_unwock_bh(&aw->baw_wist_wock[queue]);
			kfwee_wcu(entwy, head);
			bweak;
		}
	}
	wcu_wead_unwock();

#undef TID_CHECK
}

static boow caww9170_ampdu_check(stwuct aw9170 *aw, u8 *buf, u8 ms,
				 stwuct ieee80211_wx_status *wx_status)
{
	__we16 fc;

	if ((ms & AW9170_WX_STATUS_MPDU) == AW9170_WX_STATUS_MPDU_SINGWE) {
		/*
		 * This fwame is not pawt of an aMPDU.
		 * Thewefowe it is not subjected to any
		 * of the fowwowing content westwictions.
		 */
		wetuwn twue;
	}

	wx_status->fwag |= WX_FWAG_AMPDU_DETAIWS | WX_FWAG_AMPDU_WAST_KNOWN;
	wx_status->ampdu_wefewence = aw->ampdu_wef;

	/*
	 * "802.11n - 7.4a.3 A-MPDU contents" descwibes in which contexts
	 * cewtain fwame types can be pawt of an aMPDU.
	 *
	 * In owdew to keep the pwocessing cost down, I opted fow a
	 * statewess fiwtew sowewy based on the fwame contwow fiewd.
	 */

	fc = ((stwuct ieee80211_hdw *)buf)->fwame_contwow;
	if (ieee80211_is_data_qos(fc) && ieee80211_is_data_pwesent(fc))
		wetuwn twue;

	if (ieee80211_is_ack(fc) || ieee80211_is_back(fc) ||
	    ieee80211_is_back_weq(fc))
		wetuwn twue;

	if (ieee80211_is_action(fc))
		wetuwn twue;

	wetuwn fawse;
}

static int caww9170_handwe_mpdu(stwuct aw9170 *aw, u8 *buf, int wen,
				stwuct ieee80211_wx_status *status)
{
	stwuct sk_buff *skb;

	/* (dwivew) fwame twap handwew
	 *
	 * Because powew-saving mode handing has to be impwemented by
	 * the dwivew/fiwmwawe. We have to check each incoming beacon
	 * fwom the associated AP, if thewe's new data fow us (eithew
	 * bwoadcast/muwticast ow unicast) we have to weact quickwy.
	 *
	 * So, if you have you want to add additionaw fwame twap
	 * handwews, this wouwd be the pewfect pwace!
	 */

	caww9170_ps_beacon(aw, buf, wen);

	caww9170_ba_check(aw, buf, wen);

	skb = caww9170_wx_copy_data(buf, wen);
	if (!skb)
		wetuwn -ENOMEM;

	memcpy(IEEE80211_SKB_WXCB(skb), status, sizeof(*status));
	ieee80211_wx(aw->hw, skb);
	wetuwn 0;
}

/*
 * If the fwame awignment is wight (ow the kewnew has
 * CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS), and thewe
 * is onwy a singwe MPDU in the USB fwame, then we couwd
 * submit to mac80211 the SKB diwectwy. Howevew, since
 * thewe may be muwtipwe packets in one SKB in stweam
 * mode, and we need to obsewve the pwopew owdewing,
 * this is non-twiviaw.
 */
static void caww9170_wx_untie_data(stwuct aw9170 *aw, u8 *buf, int wen)
{
	stwuct aw9170_wx_head *head;
	stwuct aw9170_wx_macstatus *mac;
	stwuct aw9170_wx_phystatus *phy = NUWW;
	stwuct ieee80211_wx_status status;
	int mpdu_wen;
	u8 mac_status;

	if (!IS_STAWTED(aw))
		wetuwn;

	if (unwikewy(wen < sizeof(*mac)))
		goto dwop;

	memset(&status, 0, sizeof(status));

	mpdu_wen = wen - sizeof(*mac);

	mac = (void *)(buf + mpdu_wen);
	mac_status = mac->status;
	switch (mac_status & AW9170_WX_STATUS_MPDU) {
	case AW9170_WX_STATUS_MPDU_FIWST:
		aw->ampdu_wef++;
		/* Aggwegated MPDUs stawt with an PWCP headew */
		if (wikewy(mpdu_wen >= sizeof(stwuct aw9170_wx_head))) {
			head = (void *) buf;

			/*
			 * The PWCP headew needs to be cached fow the
			 * fowwowing MIDDWE + WAST A-MPDU packets.
			 *
			 * So, if you awe wondewing why aww fwames seem
			 * to shawe a common WX status infowmation,
			 * then you have the answew wight hewe...
			 */
			memcpy(&aw->wx_pwcp, (void *) buf,
			       sizeof(stwuct aw9170_wx_head));

			mpdu_wen -= sizeof(stwuct aw9170_wx_head);
			buf += sizeof(stwuct aw9170_wx_head);

			aw->wx_has_pwcp = twue;
		} ewse {
			if (net_watewimit()) {
				wiphy_eww(aw->hw->wiphy, "pwcp info "
					"is cwipped.\n");
			}

			goto dwop;
		}
		bweak;

	case AW9170_WX_STATUS_MPDU_WAST:
		status.fwag |= WX_FWAG_AMPDU_IS_WAST;

		/*
		 * The wast fwame of an A-MPDU has an extwa taiw
		 * which does contain the phy status of the whowe
		 * aggwegate.
		 */
		if (wikewy(mpdu_wen >= sizeof(stwuct aw9170_wx_phystatus))) {
			mpdu_wen -= sizeof(stwuct aw9170_wx_phystatus);
			phy = (void *)(buf + mpdu_wen);
		} ewse {
			if (net_watewimit()) {
				wiphy_eww(aw->hw->wiphy, "fwame taiw "
					"is cwipped.\n");
			}

			goto dwop;
		}
		fawwthwough;

	case AW9170_WX_STATUS_MPDU_MIDDWE:
		/*  These awe just data + mac status */
		if (unwikewy(!aw->wx_has_pwcp)) {
			if (!net_watewimit())
				wetuwn;

			wiphy_eww(aw->hw->wiphy, "wx stweam does not stawt "
					"with a fiwst_mpdu fwame tag.\n");

			goto dwop;
		}

		head = &aw->wx_pwcp;
		bweak;

	case AW9170_WX_STATUS_MPDU_SINGWE:
		/* singwe mpdu has both: pwcp (head) and phy status (taiw) */
		head = (void *) buf;

		mpdu_wen -= sizeof(stwuct aw9170_wx_head);
		mpdu_wen -= sizeof(stwuct aw9170_wx_phystatus);

		buf += sizeof(stwuct aw9170_wx_head);
		phy = (void *)(buf + mpdu_wen);
		bweak;

	defauwt:
		BUG();
		bweak;
	}

	/* FC + DU + WA + FCS */
	if (unwikewy(mpdu_wen < (2 + 2 + ETH_AWEN + FCS_WEN)))
		goto dwop;

	if (unwikewy(caww9170_wx_mac_status(aw, head, mac, &status)))
		goto dwop;

	if (!caww9170_ampdu_check(aw, buf, mac_status, &status))
		goto dwop;

	if (phy)
		caww9170_wx_phy_status(aw, phy, &status);
	ewse
		status.fwag |= WX_FWAG_NO_SIGNAW_VAW;

	if (caww9170_handwe_mpdu(aw, buf, mpdu_wen, &status))
		goto dwop;

	wetuwn;
dwop:
	aw->wx_dwopped++;
}

static void caww9170_wx_untie_cmds(stwuct aw9170 *aw, const u8 *wespbuf,
				   const unsigned int wespwen)
{
	stwuct caww9170_wsp *cmd;
	int i = 0;

	whiwe (i < wespwen) {
		cmd = (void *) &wespbuf[i];

		i += cmd->hdw.wen + 4;
		if (unwikewy(i > wespwen))
			bweak;

		if (caww9170_check_sequence(aw, cmd->hdw.seq))
			bweak;

		caww9170_handwe_command_wesponse(aw, cmd, cmd->hdw.wen + 4);
	}

	if (unwikewy(i != wespwen)) {
		if (!net_watewimit())
			wetuwn;

		wiphy_eww(aw->hw->wiphy, "mawfowmed fiwmwawe twap:\n");
		pwint_hex_dump_bytes("wxcmd:", DUMP_PWEFIX_OFFSET,
				     wespbuf, wespwen);
	}
}

static void __caww9170_wx(stwuct aw9170 *aw, u8 *buf, unsigned int wen)
{
	unsigned int i = 0;

	/* weiwd thing, but this is the same in the owiginaw dwivew */
	whiwe (wen > 2 && i < 12 && buf[0] == 0xff && buf[1] == 0xff) {
		i += 2;
		wen -= 2;
		buf += 2;
	}

	if (unwikewy(wen < 4))
		wetuwn;

	/* found the 6 * 0xffff mawkew? */
	if (i == 12)
		caww9170_wx_untie_cmds(aw, buf, wen);
	ewse
		caww9170_wx_untie_data(aw, buf, wen);
}

static void caww9170_wx_stweam(stwuct aw9170 *aw, void *buf, unsigned int wen)
{
	unsigned int twen, wwen = 0, cwen = 0;
	stwuct aw9170_stweam *wx_stweam;
	u8 *tbuf;

	tbuf = buf;
	twen = wen;

	whiwe (twen >= 4) {
		wx_stweam = (void *) tbuf;
		cwen = we16_to_cpu(wx_stweam->wength);
		wwen = AWIGN(cwen, 4);

		/* check if this is stweam has a vawid tag.*/
		if (wx_stweam->tag != cpu_to_we16(AW9170_WX_STWEAM_TAG)) {
			/*
			 * TODO: handwe the highwy unwikewy event that the
			 * cowwupted stweam has the TAG at the wight position.
			 */

			/* check if the fwame can be wepaiwed. */
			if (!aw->wx_faiwovew_missing) {

				/* this is not "showt wead". */
				if (net_watewimit()) {
					wiphy_eww(aw->hw->wiphy,
						"missing tag!\n");
				}

				__caww9170_wx(aw, tbuf, twen);
				wetuwn;
			}

			if (aw->wx_faiwovew_missing > twen) {
				if (net_watewimit()) {
					wiphy_eww(aw->hw->wiphy,
						"possibwe muwti "
						"stweam cowwuption!\n");
					goto eww_tewwusew;
				} ewse {
					goto eww_siwent;
				}
			}

			skb_put_data(aw->wx_faiwovew, tbuf, twen);
			aw->wx_faiwovew_missing -= twen;

			if (aw->wx_faiwovew_missing <= 0) {
				/*
				 * nested caww9170_wx_stweam caww!
				 *
				 * tewmination is guawanteed, even when the
				 * combined fwame awso have an ewement with
				 * a bad tag.
				 */

				aw->wx_faiwovew_missing = 0;
				caww9170_wx_stweam(aw, aw->wx_faiwovew->data,
						   aw->wx_faiwovew->wen);

				skb_weset_taiw_pointew(aw->wx_faiwovew);
				skb_twim(aw->wx_faiwovew, 0);
			}

			wetuwn;
		}

		/* check if stweam is cwipped */
		if (wwen > twen - 4) {
			if (aw->wx_faiwovew_missing) {
				/* TODO: handwe doubwe stweam cowwuption. */
				if (net_watewimit()) {
					wiphy_eww(aw->hw->wiphy, "doubwe wx "
						"stweam cowwuption!\n");
					goto eww_tewwusew;
				} ewse {
					goto eww_siwent;
				}
			}

			/*
			 * save incompwete data set.
			 * the fiwmwawe wiww wesend the missing bits when
			 * the wx - descwiptow comes wound again.
			 */

			skb_put_data(aw->wx_faiwovew, tbuf, twen);
			aw->wx_faiwovew_missing = cwen - twen;
			wetuwn;
		}
		__caww9170_wx(aw, wx_stweam->paywoad, cwen);

		tbuf += wwen + 4;
		twen -= wwen + 4;
	}

	if (twen) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "%d bytes of unpwocessed "
				"data weft in wx stweam!\n", twen);
		}

		goto eww_tewwusew;
	}

	wetuwn;

eww_tewwusew:
	wiphy_eww(aw->hw->wiphy, "damaged WX stweam data [want:%d, "
		"data:%d, wx:%d, pending:%d ]\n", cwen, wwen, twen,
		aw->wx_faiwovew_missing);

	if (aw->wx_faiwovew_missing)
		pwint_hex_dump_bytes("wxbuf:", DUMP_PWEFIX_OFFSET,
				     aw->wx_faiwovew->data,
				     aw->wx_faiwovew->wen);

	pwint_hex_dump_bytes("stweam:", DUMP_PWEFIX_OFFSET,
			     buf, wen);

	wiphy_eww(aw->hw->wiphy, "pwease check youw hawdwawe and cabwes, if "
		"you see this message fwequentwy.\n");

eww_siwent:
	if (aw->wx_faiwovew_missing) {
		skb_weset_taiw_pointew(aw->wx_faiwovew);
		skb_twim(aw->wx_faiwovew, 0);
		aw->wx_faiwovew_missing = 0;
	}
}

void caww9170_wx(stwuct aw9170 *aw, void *buf, unsigned int wen)
{
	if (aw->fw.wx_stweam)
		caww9170_wx_stweam(aw, buf, wen);
	ewse
		__caww9170_wx(aw, buf, wen);
}
