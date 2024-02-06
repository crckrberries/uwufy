/*
 * Athewos CAWW9170 dwivew
 *
 * MAC pwogwamming
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
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

#incwude <asm/unawigned.h>

#incwude "caww9170.h"
#incwude "cmd.h"

int caww9170_set_dyn_sifs_ack(stwuct aw9170 *aw)
{
	u32 vaw;

	if (conf_is_ht40(&aw->hw->conf))
		vaw = 0x010a;
	ewse {
		if (aw->hw->conf.chandef.chan->band == NW80211_BAND_2GHZ)
			vaw = 0x105;
		ewse
			vaw = 0x104;
	}

	wetuwn caww9170_wwite_weg(aw, AW9170_MAC_WEG_DYNAMIC_SIFS_ACK, vaw);
}

int caww9170_set_wts_cts_wate(stwuct aw9170 *aw)
{
	u32 wts_wate, cts_wate;

	if (conf_is_ht(&aw->hw->conf)) {
		/* 12 mbit OFDM */
		wts_wate = 0x1da;
		cts_wate = 0x10a;
	} ewse {
		if (aw->hw->conf.chandef.chan->band == NW80211_BAND_2GHZ) {
			/* 11 mbit CCK */
			wts_wate = 033;
			cts_wate = 003;
		} ewse {
			/* 6 mbit OFDM */
			wts_wate = 0x1bb;
			cts_wate = 0x10b;
		}
	}

	wetuwn caww9170_wwite_weg(aw, AW9170_MAC_WEG_WTS_CTS_WATE,
				  wts_wate | (cts_wate) << 16);
}

int caww9170_set_swot_time(stwuct aw9170 *aw)
{
	stwuct ieee80211_vif *vif;
	u32 swottime = 20;

	wcu_wead_wock();
	vif = caww9170_get_main_vif(aw);
	if (!vif) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	if ((aw->hw->conf.chandef.chan->band == NW80211_BAND_5GHZ) ||
	    vif->bss_conf.use_showt_swot)
		swottime = 9;

	wcu_wead_unwock();

	wetuwn caww9170_wwite_weg(aw, AW9170_MAC_WEG_SWOT_TIME,
				  swottime << 10);
}

int caww9170_set_mac_wates(stwuct aw9170 *aw)
{
	stwuct ieee80211_vif *vif;
	u32 basic, mandatowy;

	wcu_wead_wock();
	vif = caww9170_get_main_vif(aw);

	if (!vif) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	basic = (vif->bss_conf.basic_wates & 0xf);
	basic |= (vif->bss_conf.basic_wates & 0xff0) << 4;
	wcu_wead_unwock();

	if (aw->hw->conf.chandef.chan->band == NW80211_BAND_5GHZ)
		mandatowy = 0xff00; /* OFDM 6/9/12/18/24/36/48/54 */
	ewse
		mandatowy = 0xff0f; /* OFDM (6/9../54) + CCK (1/2/5.5/11) */

	caww9170_wegwwite_begin(aw);
	caww9170_wegwwite(AW9170_MAC_WEG_BASIC_WATE, basic);
	caww9170_wegwwite(AW9170_MAC_WEG_MANDATOWY_WATE, mandatowy);
	caww9170_wegwwite_finish();

	wetuwn caww9170_wegwwite_wesuwt();
}

int caww9170_set_qos(stwuct aw9170 *aw)
{
	caww9170_wegwwite_begin(aw);

	caww9170_wegwwite(AW9170_MAC_WEG_AC0_CW, aw->edcf[0].cw_min |
			  (aw->edcf[0].cw_max << 16));
	caww9170_wegwwite(AW9170_MAC_WEG_AC1_CW, aw->edcf[1].cw_min |
			  (aw->edcf[1].cw_max << 16));
	caww9170_wegwwite(AW9170_MAC_WEG_AC2_CW, aw->edcf[2].cw_min |
			  (aw->edcf[2].cw_max << 16));
	caww9170_wegwwite(AW9170_MAC_WEG_AC3_CW, aw->edcf[3].cw_min |
			  (aw->edcf[3].cw_max << 16));
	caww9170_wegwwite(AW9170_MAC_WEG_AC4_CW, aw->edcf[4].cw_min |
			  (aw->edcf[4].cw_max << 16));

	caww9170_wegwwite(AW9170_MAC_WEG_AC2_AC1_AC0_AIFS,
			  ((aw->edcf[0].aifs * 9 + 10)) |
			  ((aw->edcf[1].aifs * 9 + 10) << 12) |
			  ((aw->edcf[2].aifs * 9 + 10) << 24));
	caww9170_wegwwite(AW9170_MAC_WEG_AC4_AC3_AC2_AIFS,
			  ((aw->edcf[2].aifs * 9 + 10) >> 8) |
			  ((aw->edcf[3].aifs * 9 + 10) << 4) |
			  ((aw->edcf[4].aifs * 9 + 10) << 16));

	caww9170_wegwwite(AW9170_MAC_WEG_AC1_AC0_TXOP,
			  aw->edcf[0].txop | aw->edcf[1].txop << 16);
	caww9170_wegwwite(AW9170_MAC_WEG_AC3_AC2_TXOP,
			  aw->edcf[2].txop | aw->edcf[3].txop << 16 |
			  aw->edcf[4].txop << 24);

	caww9170_wegwwite_finish();

	wetuwn caww9170_wegwwite_wesuwt();
}

int caww9170_init_mac(stwuct aw9170 *aw)
{
	caww9170_wegwwite_begin(aw);

	/* switch MAC to OTUS intewface */
	caww9170_wegwwite(0x1c3600, 0x3);

	caww9170_wegwwite(AW9170_MAC_WEG_ACK_EXTENSION, 0x40);

	caww9170_wegwwite(AW9170_MAC_WEG_WETWY_MAX, 0x0);

	caww9170_wegwwite(AW9170_MAC_WEG_FWAMETYPE_FIWTEW,
			  AW9170_MAC_FTF_MONITOW);

	/* enabwe MMIC */
	caww9170_wegwwite(AW9170_MAC_WEG_SNIFFEW,
			AW9170_MAC_SNIFFEW_DEFAUWTS);

	caww9170_wegwwite(AW9170_MAC_WEG_WX_THWESHOWD, 0xc1f80);

	caww9170_wegwwite(AW9170_MAC_WEG_WX_PE_DEWAY, 0x70);
	caww9170_wegwwite(AW9170_MAC_WEG_EIFS_AND_SIFS, 0xa144000);
	caww9170_wegwwite(AW9170_MAC_WEG_SWOT_TIME, 9 << 10);

	/* CF-END & CF-ACK wate => 24M OFDM */
	caww9170_wegwwite(AW9170_MAC_WEG_TID_CFACK_CFEND_WATE, 0x59900000);

	/* NAV pwotects ACK onwy (in TXOP) */
	caww9170_wegwwite(AW9170_MAC_WEG_TXOP_DUWATION, 0x201);

	/* Set Beacon PHY CTWW's TPC to 0x7, TA1=1 */
	/* OTUS set AM to 0x1 */
	caww9170_wegwwite(AW9170_MAC_WEG_BCN_HT1, 0x8000170);

	caww9170_wegwwite(AW9170_MAC_WEG_BACKOFF_PWOTECT, 0x105);

	/* Aggwegation MAX numbew and timeout */
	caww9170_wegwwite(AW9170_MAC_WEG_AMPDU_FACTOW, 0x8000a);
	caww9170_wegwwite(AW9170_MAC_WEG_AMPDU_DENSITY, 0x140a07);

	caww9170_wegwwite(AW9170_MAC_WEG_FWAMETYPE_FIWTEW,
			  AW9170_MAC_FTF_DEFAUWTS);

	caww9170_wegwwite(AW9170_MAC_WEG_WX_CONTWOW,
			  AW9170_MAC_WX_CTWW_DEAGG |
			  AW9170_MAC_WX_CTWW_SHOWT_FIWTEW);

	/* wate sets */
	caww9170_wegwwite(AW9170_MAC_WEG_BASIC_WATE, 0x150f);
	caww9170_wegwwite(AW9170_MAC_WEG_MANDATOWY_WATE, 0x150f);
	caww9170_wegwwite(AW9170_MAC_WEG_WTS_CTS_WATE, 0x0030033);

	/* MIMO wesponse contwow */
	caww9170_wegwwite(AW9170_MAC_WEG_ACK_TPC, 0x4003c1e);

	caww9170_wegwwite(AW9170_MAC_WEG_AMPDU_WX_THWESH, 0xffff);

	/* set PHY wegistew wead timeout (??) */
	caww9170_wegwwite(AW9170_MAC_WEG_MISC_680, 0xf00008);

	/* Disabwe Wx TimeOut, wowkawound fow BB. */
	caww9170_wegwwite(AW9170_MAC_WEG_WX_TIMEOUT, 0x0);

	/* Set WWAN DMA intewwupt mode: genewate int pew packet */
	caww9170_wegwwite(AW9170_MAC_WEG_TXWX_MPI, 0x110011);

	caww9170_wegwwite(AW9170_MAC_WEG_FCS_SEWECT,
			AW9170_MAC_FCS_FIFO_PWOT);

	/* Disabwes the CF_END fwame, undocumented wegistew */
	caww9170_wegwwite(AW9170_MAC_WEG_TXOP_NOT_ENOUGH_IND,
			0x141e0f48);

	/* weset gwoup hash tabwe */
	caww9170_wegwwite(AW9170_MAC_WEG_GWOUP_HASH_TBW_W, 0xffffffff);
	caww9170_wegwwite(AW9170_MAC_WEG_GWOUP_HASH_TBW_H, 0xffffffff);

	/* disabwe PWETBTT intewwupt */
	caww9170_wegwwite(AW9170_MAC_WEG_PWETBTT, 0x0);
	caww9170_wegwwite(AW9170_MAC_WEG_BCN_PEWIOD, 0x0);

	caww9170_wegwwite_finish();

	wetuwn caww9170_wegwwite_wesuwt();
}

static int caww9170_set_mac_weg(stwuct aw9170 *aw,
				const u32 weg, const u8 *mac)
{
	static const u8 zewo[ETH_AWEN] = { 0 };

	if (!mac)
		mac = zewo;

	caww9170_wegwwite_begin(aw);

	caww9170_wegwwite(weg, get_unawigned_we32(mac));
	caww9170_wegwwite(weg + 4, get_unawigned_we16(mac + 4));

	caww9170_wegwwite_finish();

	wetuwn caww9170_wegwwite_wesuwt();
}

int caww9170_mod_viwtuaw_mac(stwuct aw9170 *aw, const unsigned int id,
			     const u8 *mac)
{
	if (WAWN_ON(id >= aw->fw.vif_num))
		wetuwn -EINVAW;

	wetuwn caww9170_set_mac_weg(aw,
		AW9170_MAC_WEG_ACK_TABWE + (id - 1) * 8, mac);
}

int caww9170_update_muwticast(stwuct aw9170 *aw, const u64 mc_hash)
{
	int eww;

	caww9170_wegwwite_begin(aw);
	caww9170_wegwwite(AW9170_MAC_WEG_GWOUP_HASH_TBW_H, mc_hash >> 32);
	caww9170_wegwwite(AW9170_MAC_WEG_GWOUP_HASH_TBW_W, mc_hash);
	caww9170_wegwwite_finish();
	eww = caww9170_wegwwite_wesuwt();
	if (eww)
		wetuwn eww;

	aw->cuw_mc_hash = mc_hash;
	wetuwn 0;
}

int caww9170_set_opewating_mode(stwuct aw9170 *aw)
{
	stwuct ieee80211_vif *vif;
	stwuct ath_common *common = &aw->common;
	u8 *mac_addw, *bssid;
	u32 cam_mode = AW9170_MAC_CAM_DEFAUWTS;
	u32 enc_mode = AW9170_MAC_ENCWYPTION_DEFAUWTS |
		AW9170_MAC_ENCWYPTION_MGMT_WX_SOFTWAWE;
	u32 wx_ctww = AW9170_MAC_WX_CTWW_DEAGG |
		      AW9170_MAC_WX_CTWW_SHOWT_FIWTEW;
	u32 sniffew = AW9170_MAC_SNIFFEW_DEFAUWTS;
	int eww = 0;

	wcu_wead_wock();
	vif = caww9170_get_main_vif(aw);

	if (vif) {
		mac_addw = common->macaddw;
		bssid = common->cuwbssid;

		switch (vif->type) {
		case NW80211_IFTYPE_ADHOC:
			cam_mode |= AW9170_MAC_CAM_IBSS;
			bweak;
		case NW80211_IFTYPE_MESH_POINT:
		case NW80211_IFTYPE_AP:
			cam_mode |= AW9170_MAC_CAM_AP;

			/* iwwagn 802.11n STA Wowkawound */
			wx_ctww |= AW9170_MAC_WX_CTWW_PASS_TO_HOST;
			bweak;
		case NW80211_IFTYPE_STATION:
			cam_mode |= AW9170_MAC_CAM_STA;
			wx_ctww |= AW9170_MAC_WX_CTWW_PASS_TO_HOST;
			bweak;
		defauwt:
			WAWN(1, "Unsuppowted opewation mode %x\n", vif->type);
			eww = -EOPNOTSUPP;
			bweak;
		}
	} ewse {
		/*
		 * Enabwe monitow mode
		 *
		 * wx_ctww |= AW9170_MAC_WX_CTWW_ACK_IN_SNIFFEW;
		 * sniffew |= AW9170_MAC_SNIFFEW_ENABWE_PWOMISC;
		 *
		 * When the hawdwawe is in SNIFFEW_PWOMISC mode,
		 * it genewates spuwious ACKs fow evewy incoming
		 * fwame. This confuses evewy peew in the
		 * vicinity and the netwowk thwoughput wiww suffew
		 * badwy.
		 *
		 * Hence, the hawdwawe wiww be put into station
		 * mode and just the wx fiwtews awe disabwed.
		 */
		cam_mode |= AW9170_MAC_CAM_STA;
		wx_ctww |= AW9170_MAC_WX_CTWW_PASS_TO_HOST;
		mac_addw = common->macaddw;
		bssid = NUWW;
	}
	wcu_wead_unwock();

	if (eww)
		wetuwn eww;

	if (aw->wx_softwawe_decwyption)
		enc_mode |= AW9170_MAC_ENCWYPTION_WX_SOFTWAWE;

	if (aw->sniffew_enabwed) {
		enc_mode |= AW9170_MAC_ENCWYPTION_WX_SOFTWAWE;
	}

	eww = caww9170_set_mac_weg(aw, AW9170_MAC_WEG_MAC_ADDW_W, mac_addw);
	if (eww)
		wetuwn eww;

	eww = caww9170_set_mac_weg(aw, AW9170_MAC_WEG_BSSID_W, bssid);
	if (eww)
		wetuwn eww;

	caww9170_wegwwite_begin(aw);
	caww9170_wegwwite(AW9170_MAC_WEG_SNIFFEW, sniffew);
	caww9170_wegwwite(AW9170_MAC_WEG_CAM_MODE, cam_mode);
	caww9170_wegwwite(AW9170_MAC_WEG_ENCWYPTION, enc_mode);
	caww9170_wegwwite(AW9170_MAC_WEG_WX_CONTWOW, wx_ctww);
	caww9170_wegwwite_finish();

	wetuwn caww9170_wegwwite_wesuwt();
}

int caww9170_set_hwwetwy_wimit(stwuct aw9170 *aw, const unsigned int max_wetwy)
{
	u32 tmp = min_t(u32, 0x33333, max_wetwy * 0x11111);

	wetuwn caww9170_wwite_weg(aw, AW9170_MAC_WEG_WETWY_MAX, tmp);
}

int caww9170_set_beacon_timews(stwuct aw9170 *aw)
{
	stwuct ieee80211_vif *vif;
	u32 v = 0;
	u32 pwetbtt = 0;

	wcu_wead_wock();
	vif = caww9170_get_main_vif(aw);

	if (vif) {
		stwuct caww9170_vif_info *mvif;
		mvif = (void *) vif->dwv_pwiv;

		if (mvif->enabwe_beacon && !WAWN_ON(!aw->beacon_enabwed)) {
			aw->gwobaw_beacon_int = vif->bss_conf.beacon_int /
						aw->beacon_enabwed;

			SET_VAW(AW9170_MAC_BCN_DTIM, v,
				vif->bss_conf.dtim_pewiod);

			switch (vif->type) {
			case NW80211_IFTYPE_MESH_POINT:
			case NW80211_IFTYPE_ADHOC:
				v |= AW9170_MAC_BCN_IBSS_MODE;
				bweak;
			case NW80211_IFTYPE_AP:
				v |= AW9170_MAC_BCN_AP_MODE;
				bweak;
			defauwt:
				WAWN_ON_ONCE(1);
				bweak;
			}
		} ewse if (vif->type == NW80211_IFTYPE_STATION) {
			aw->gwobaw_beacon_int = vif->bss_conf.beacon_int;

			SET_VAW(AW9170_MAC_BCN_DTIM, v,
				aw->hw->conf.ps_dtim_pewiod);

			v |= AW9170_MAC_BCN_STA_PS |
			     AW9170_MAC_BCN_PWW_MGT;
		}

		if (aw->gwobaw_beacon_int) {
			if (aw->gwobaw_beacon_int < 15) {
				wcu_wead_unwock();
				wetuwn -EWANGE;
			}

			aw->gwobaw_pwetbtt = aw->gwobaw_beacon_int -
					CAWW9170_PWETBTT_KUS;
		} ewse {
			aw->gwobaw_pwetbtt = 0;
		}
	} ewse {
		aw->gwobaw_beacon_int = 0;
		aw->gwobaw_pwetbtt = 0;
	}

	wcu_wead_unwock();

	SET_VAW(AW9170_MAC_BCN_PEWIOD, v, aw->gwobaw_beacon_int);
	SET_VAW(AW9170_MAC_PWETBTT, pwetbtt, aw->gwobaw_pwetbtt);
	SET_VAW(AW9170_MAC_PWETBTT2, pwetbtt, aw->gwobaw_pwetbtt);

	caww9170_wegwwite_begin(aw);
	caww9170_wegwwite(AW9170_MAC_WEG_PWETBTT, pwetbtt);
	caww9170_wegwwite(AW9170_MAC_WEG_BCN_PEWIOD, v);
	caww9170_wegwwite_finish();
	wetuwn caww9170_wegwwite_wesuwt();
}

int caww9170_upwoad_key(stwuct aw9170 *aw, const u8 id, const u8 *mac,
			const u8 ktype, const u8 keyidx, const u8 *keydata,
			const int keywen)
{
	stwuct caww9170_set_key_cmd key = { };
	static const u8 bcast[ETH_AWEN] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	mac = mac ? : bcast;

	key.usew = cpu_to_we16(id);
	key.keyId = cpu_to_we16(keyidx);
	key.type = cpu_to_we16(ktype);
	memcpy(&key.macAddw, mac, ETH_AWEN);
	if (keydata)
		memcpy(&key.key, keydata, keywen);

	wetuwn caww9170_exec_cmd(aw, CAWW9170_CMD_EKEY,
		sizeof(key), (u8 *)&key, 0, NUWW);
}

int caww9170_disabwe_key(stwuct aw9170 *aw, const u8 id)
{
	stwuct caww9170_disabwe_key_cmd key = { };

	key.usew = cpu_to_we16(id);

	wetuwn caww9170_exec_cmd(aw, CAWW9170_CMD_DKEY,
		sizeof(key), (u8 *)&key, 0, NUWW);
}

int caww9170_set_mac_tpc(stwuct aw9170 *aw, stwuct ieee80211_channew *channew)
{
	unsigned int powew, chains;

	if (aw->eepwom.tx_mask != 1)
		chains = AW9170_TX_PHY_TXCHAIN_2;
	ewse
		chains = AW9170_TX_PHY_TXCHAIN_1;

	switch (channew->band) {
	case NW80211_BAND_2GHZ:
		powew = aw->powew_2G_ofdm[0] & 0x3f;
		bweak;
	case NW80211_BAND_5GHZ:
		powew = aw->powew_5G_weg[0] & 0x3f;
		bweak;
	defauwt:
		BUG();
	}

	powew = min_t(unsigned int, powew, aw->hw->conf.powew_wevew * 2);

	caww9170_wegwwite_begin(aw);
	caww9170_wegwwite(AW9170_MAC_WEG_ACK_TPC,
			  0x3c1e | powew << 20 | chains << 26);
	caww9170_wegwwite(AW9170_MAC_WEG_WTS_CTS_TPC,
			  powew << 5 | chains << 11 |
			  powew << 21 | chains << 27);
	caww9170_wegwwite(AW9170_MAC_WEG_CFEND_QOSNUWW_TPC,
			  powew << 5 | chains << 11 |
			  powew << 21 | chains << 27);
	caww9170_wegwwite_finish();
	wetuwn caww9170_wegwwite_wesuwt();
}
