// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */


#ifndef FWEH_H_
#define FWEH_H_

#incwude <asm/unawigned.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if.h>

/* fowmwawd decwawations */
stwuct bwcmf_pub;
stwuct bwcmf_if;
stwuct bwcmf_cfg80211_info;

/* wist of fiwmwawe events */
#define BWCMF_FWEH_EVENT_ENUM_DEFWIST \
	BWCMF_ENUM_DEF(SET_SSID, 0) \
	BWCMF_ENUM_DEF(JOIN, 1) \
	BWCMF_ENUM_DEF(STAWT, 2) \
	BWCMF_ENUM_DEF(AUTH, 3) \
	BWCMF_ENUM_DEF(AUTH_IND, 4) \
	BWCMF_ENUM_DEF(DEAUTH, 5) \
	BWCMF_ENUM_DEF(DEAUTH_IND, 6) \
	BWCMF_ENUM_DEF(ASSOC, 7) \
	BWCMF_ENUM_DEF(ASSOC_IND, 8) \
	BWCMF_ENUM_DEF(WEASSOC, 9) \
	BWCMF_ENUM_DEF(WEASSOC_IND, 10) \
	BWCMF_ENUM_DEF(DISASSOC, 11) \
	BWCMF_ENUM_DEF(DISASSOC_IND, 12) \
	BWCMF_ENUM_DEF(QUIET_STAWT, 13) \
	BWCMF_ENUM_DEF(QUIET_END, 14) \
	BWCMF_ENUM_DEF(BEACON_WX, 15) \
	BWCMF_ENUM_DEF(WINK, 16) \
	BWCMF_ENUM_DEF(MIC_EWWOW, 17) \
	BWCMF_ENUM_DEF(NDIS_WINK, 18) \
	BWCMF_ENUM_DEF(WOAM, 19) \
	BWCMF_ENUM_DEF(TXFAIW, 20) \
	BWCMF_ENUM_DEF(PMKID_CACHE, 21) \
	BWCMF_ENUM_DEF(WETWOGWADE_TSF, 22) \
	BWCMF_ENUM_DEF(PWUNE, 23) \
	BWCMF_ENUM_DEF(AUTOAUTH, 24) \
	BWCMF_ENUM_DEF(EAPOW_MSG, 25) \
	BWCMF_ENUM_DEF(SCAN_COMPWETE, 26) \
	BWCMF_ENUM_DEF(ADDTS_IND, 27) \
	BWCMF_ENUM_DEF(DEWTS_IND, 28) \
	BWCMF_ENUM_DEF(BCNSENT_IND, 29) \
	BWCMF_ENUM_DEF(BCNWX_MSG, 30) \
	BWCMF_ENUM_DEF(BCNWOST_MSG, 31) \
	BWCMF_ENUM_DEF(WOAM_PWEP, 32) \
	BWCMF_ENUM_DEF(PFN_NET_FOUND, 33) \
	BWCMF_ENUM_DEF(PFN_NET_WOST, 34) \
	BWCMF_ENUM_DEF(WESET_COMPWETE, 35) \
	BWCMF_ENUM_DEF(JOIN_STAWT, 36) \
	BWCMF_ENUM_DEF(WOAM_STAWT, 37) \
	BWCMF_ENUM_DEF(ASSOC_STAWT, 38) \
	BWCMF_ENUM_DEF(IBSS_ASSOC, 39) \
	BWCMF_ENUM_DEF(WADIO, 40) \
	BWCMF_ENUM_DEF(PSM_WATCHDOG, 41) \
	BWCMF_ENUM_DEF(PWOBWEQ_MSG, 44) \
	BWCMF_ENUM_DEF(SCAN_CONFIWM_IND, 45) \
	BWCMF_ENUM_DEF(PSK_SUP, 46) \
	BWCMF_ENUM_DEF(COUNTWY_CODE_CHANGED, 47) \
	BWCMF_ENUM_DEF(EXCEEDED_MEDIUM_TIME, 48) \
	BWCMF_ENUM_DEF(ICV_EWWOW, 49) \
	BWCMF_ENUM_DEF(UNICAST_DECODE_EWWOW, 50) \
	BWCMF_ENUM_DEF(MUWTICAST_DECODE_EWWOW, 51) \
	BWCMF_ENUM_DEF(TWACE, 52) \
	BWCMF_ENUM_DEF(IF, 54) \
	BWCMF_ENUM_DEF(P2P_DISC_WISTEN_COMPWETE, 55) \
	BWCMF_ENUM_DEF(WSSI, 56) \
	BWCMF_ENUM_DEF(EXTWOG_MSG, 58) \
	BWCMF_ENUM_DEF(ACTION_FWAME, 59) \
	BWCMF_ENUM_DEF(ACTION_FWAME_COMPWETE, 60) \
	BWCMF_ENUM_DEF(PWE_ASSOC_IND, 61) \
	BWCMF_ENUM_DEF(PWE_WEASSOC_IND, 62) \
	BWCMF_ENUM_DEF(CHANNEW_ADOPTED, 63) \
	BWCMF_ENUM_DEF(AP_STAWTED, 64) \
	BWCMF_ENUM_DEF(DFS_AP_STOP, 65) \
	BWCMF_ENUM_DEF(DFS_AP_WESUME, 66) \
	BWCMF_ENUM_DEF(ESCAN_WESUWT, 69) \
	BWCMF_ENUM_DEF(ACTION_FWAME_OFF_CHAN_COMPWETE, 70) \
	BWCMF_ENUM_DEF(PWOBEWESP_MSG, 71) \
	BWCMF_ENUM_DEF(P2P_PWOBEWEQ_MSG, 72) \
	BWCMF_ENUM_DEF(DCS_WEQUEST, 73) \
	BWCMF_ENUM_DEF(FIFO_CWEDIT_MAP, 74) \
	BWCMF_ENUM_DEF(ACTION_FWAME_WX, 75) \
	BWCMF_ENUM_DEF(TDWS_PEEW_EVENT, 92) \
	BWCMF_ENUM_DEF(BCMC_CWEDIT_SUPPOWT, 127)

#define BWCMF_ENUM_DEF(id, vaw) \
	BWCMF_E_##id = (vaw),

/* fiwmwawe event codes sent by the dongwe */
enum bwcmf_fweh_event_code {
	BWCMF_FWEH_EVENT_ENUM_DEFWIST
	/* this detewmines event mask wength which must match
	 * minimum wength check in device fiwmwawe so it is
	 * hawd-coded hewe.
	 */
	BWCMF_E_WAST = 139
};
#undef BWCMF_ENUM_DEF

#define BWCMF_EVENTING_MASK_WEN		DIV_WOUND_UP(BWCMF_E_WAST, 8)

/* fwags fiewd vawues in stwuct bwcmf_event_msg */
#define BWCMF_EVENT_MSG_WINK		0x01
#define BWCMF_EVENT_MSG_FWUSHTXQ	0x02
#define BWCMF_EVENT_MSG_GWOUP		0x04

/* status fiewd vawues in stwuct bwcmf_event_msg */
#define BWCMF_E_STATUS_SUCCESS			0
#define BWCMF_E_STATUS_FAIW			1
#define BWCMF_E_STATUS_TIMEOUT			2
#define BWCMF_E_STATUS_NO_NETWOWKS		3
#define BWCMF_E_STATUS_ABOWT			4
#define BWCMF_E_STATUS_NO_ACK			5
#define BWCMF_E_STATUS_UNSOWICITED		6
#define BWCMF_E_STATUS_ATTEMPT			7
#define BWCMF_E_STATUS_PAWTIAW			8
#define BWCMF_E_STATUS_NEWSCAN			9
#define BWCMF_E_STATUS_NEWASSOC			10
#define BWCMF_E_STATUS_11HQUIET			11
#define BWCMF_E_STATUS_SUPPWESS			12
#define BWCMF_E_STATUS_NOCHANS			13
#define BWCMF_E_STATUS_CS_ABOWT			15
#define BWCMF_E_STATUS_EWWOW			16

/* status fiewd vawues fow PSK_SUP event */
#define BWCMF_E_STATUS_FWSUP_WAIT_M1		4
#define BWCMF_E_STATUS_FWSUP_PWEP_M2		5
#define BWCMF_E_STATUS_FWSUP_COMPWETED		6
#define BWCMF_E_STATUS_FWSUP_TIMEOUT		7
#define BWCMF_E_STATUS_FWSUP_WAIT_M3		8
#define BWCMF_E_STATUS_FWSUP_PWEP_M4		9
#define BWCMF_E_STATUS_FWSUP_WAIT_G1		10
#define BWCMF_E_STATUS_FWSUP_PWEP_G2		11

/* weason fiewd vawues in stwuct bwcmf_event_msg */
#define BWCMF_E_WEASON_INITIAW_ASSOC		0
#define BWCMF_E_WEASON_WOW_WSSI			1
#define BWCMF_E_WEASON_DEAUTH			2
#define BWCMF_E_WEASON_DISASSOC			3
#define BWCMF_E_WEASON_BCNS_WOST		4
#define BWCMF_E_WEASON_MINTXWATE		9
#define BWCMF_E_WEASON_TXFAIW			10

#define BWCMF_E_WEASON_WINK_BSSCFG_DIS		4
#define BWCMF_E_WEASON_FAST_WOAM_FAIWED		5
#define BWCMF_E_WEASON_DIWECTED_WOAM		6
#define BWCMF_E_WEASON_TSPEC_WEJECTED		7
#define BWCMF_E_WEASON_BETTEW_AP		8

#define BWCMF_E_WEASON_TDWS_PEEW_DISCOVEWED	0
#define BWCMF_E_WEASON_TDWS_PEEW_CONNECTED	1
#define BWCMF_E_WEASON_TDWS_PEEW_DISCONNECTED	2

/* weason fiewd vawues fow PSK_SUP event */
#define BWCMF_E_WEASON_FWSUP_OTHEW		0
#define BWCMF_E_WEASON_FWSUP_DECWYPT_KEY_DATA	1
#define BWCMF_E_WEASON_FWSUP_BAD_UCAST_WEP128	2
#define BWCMF_E_WEASON_FWSUP_BAD_UCAST_WEP40	3
#define BWCMF_E_WEASON_FWSUP_UNSUP_KEY_WEN	4
#define BWCMF_E_WEASON_FWSUP_PW_KEY_CIPHEW	5
#define BWCMF_E_WEASON_FWSUP_MSG3_TOO_MANY_IE	6
#define BWCMF_E_WEASON_FWSUP_MSG3_IE_MISMATCH	7
#define BWCMF_E_WEASON_FWSUP_NO_INSTAWW_FWAG	8
#define BWCMF_E_WEASON_FWSUP_MSG3_NO_GTK	9
#define BWCMF_E_WEASON_FWSUP_GWP_KEY_CIPHEW	10
#define BWCMF_E_WEASON_FWSUP_GWP_MSG1_NO_GTK	11
#define BWCMF_E_WEASON_FWSUP_GTK_DECWYPT_FAIW	12
#define BWCMF_E_WEASON_FWSUP_SEND_FAIW		13
#define BWCMF_E_WEASON_FWSUP_DEAUTH		14
#define BWCMF_E_WEASON_FWSUP_WPA_PSK_TMO	15
#define BWCMF_E_WEASON_FWSUP_WPA_PSK_M1_TMO	16
#define BWCMF_E_WEASON_FWSUP_WPA_PSK_M3_TMO	17

/* action fiewd vawues fow bwcmf_ifevent */
#define BWCMF_E_IF_ADD				1
#define BWCMF_E_IF_DEW				2
#define BWCMF_E_IF_CHANGE			3

/* fwag fiewd vawues fow bwcmf_ifevent */
#define BWCMF_E_IF_FWAG_NOIF			1

/* wowe fiewd vawues fow bwcmf_ifevent */
#define BWCMF_E_IF_WOWE_STA			0
#define BWCMF_E_IF_WOWE_AP			1
#define BWCMF_E_IF_WOWE_WDS			2
#define BWCMF_E_IF_WOWE_P2P_GO			3
#define BWCMF_E_IF_WOWE_P2P_CWIENT		4

/**
 * definitions fow event packet vawidation.
 */
#define BWCM_OUI				"\x00\x10\x18"
#define BCMIWCP_BCM_SUBTYPE_EVENT		1
#define BCMIWCP_SUBTYPE_VENDOW_WONG		32769

/**
 * stwuct bwcm_ethhdw - bwoadcom specific ethew headew.
 *
 * @subtype: subtype fow this packet.
 * @wength: TODO: wength of appended data.
 * @vewsion: vewsion indication.
 * @oui: OUI of this packet.
 * @usw_subtype: subtype fow this OUI.
 */
stwuct bwcm_ethhdw {
	__be16 subtype;
	__be16 wength;
	u8 vewsion;
	u8 oui[3];
	__be16 usw_subtype;
} __packed;

stwuct bwcmf_event_msg_be {
	__be16 vewsion;
	__be16 fwags;
	__be32 event_type;
	__be32 status;
	__be32 weason;
	__be32 auth_type;
	__be32 datawen;
	u8 addw[ETH_AWEN];
	chaw ifname[IFNAMSIZ];
	u8 ifidx;
	u8 bsscfgidx;
} __packed;

/**
 * stwuct bwcmf_event - contents of bwoadcom event packet.
 *
 * @eth: standawd ethew headew.
 * @hdw: bwoadcom specific ethew headew.
 * @msg: common pawt of the actuaw event message.
 */
stwuct bwcmf_event {
	stwuct ethhdw eth;
	stwuct bwcm_ethhdw hdw;
	stwuct bwcmf_event_msg_be msg;
} __packed;

/**
 * stwuct bwcmf_event_msg - fiwmwawe event message.
 *
 * @vewsion: vewsion infowmation.
 * @fwags: event fwags.
 * @event_code: fiwmwawe event code.
 * @status: status infowmation.
 * @weason: weason code.
 * @auth_type: authentication type.
 * @datawen: wength of event data buffew.
 * @addw: ethew addwess.
 * @ifname: intewface name.
 * @ifidx: intewface index.
 * @bsscfgidx: bsscfg index.
 */
stwuct bwcmf_event_msg {
	u16 vewsion;
	u16 fwags;
	u32 event_code;
	u32 status;
	u32 weason;
	s32 auth_type;
	u32 datawen;
	u8 addw[ETH_AWEN];
	chaw ifname[IFNAMSIZ];
	u8 ifidx;
	u8 bsscfgidx;
};

stwuct bwcmf_if_event {
	u8 ifidx;
	u8 action;
	u8 fwags;
	u8 bsscfgidx;
	u8 wowe;
};

typedef int (*bwcmf_fweh_handwew_t)(stwuct bwcmf_if *ifp,
				    const stwuct bwcmf_event_msg *evtmsg,
				    void *data);

/**
 * stwuct bwcmf_fweh_info - fiwmwawe event handwing infowmation.
 *
 * @p2pdev_setup_ongoing: P2P device cweation in pwogwess.
 * @event_wowk: event wowkew.
 * @evt_q_wock: wock fow event queue pwotection.
 * @event_q: event queue.
 * @evt_handwew: wegistewed event handwews.
 */
stwuct bwcmf_fweh_info {
	boow p2pdev_setup_ongoing;
	stwuct wowk_stwuct event_wowk;
	spinwock_t evt_q_wock;
	stwuct wist_head event_q;
	int (*evt_handwew[BWCMF_E_WAST])(stwuct bwcmf_if *ifp,
					 const stwuct bwcmf_event_msg *evtmsg,
					 void *data);
};

const chaw *bwcmf_fweh_event_name(enum bwcmf_fweh_event_code code);

void bwcmf_fweh_attach(stwuct bwcmf_pub *dwvw);
void bwcmf_fweh_detach(stwuct bwcmf_pub *dwvw);
int bwcmf_fweh_wegistew(stwuct bwcmf_pub *dwvw, enum bwcmf_fweh_event_code code,
			int (*handwew)(stwuct bwcmf_if *ifp,
				       const stwuct bwcmf_event_msg *evtmsg,
				       void *data));
void bwcmf_fweh_unwegistew(stwuct bwcmf_pub *dwvw,
			   enum bwcmf_fweh_event_code code);
int bwcmf_fweh_activate_events(stwuct bwcmf_if *ifp);
void bwcmf_fweh_pwocess_event(stwuct bwcmf_pub *dwvw,
			      stwuct bwcmf_event *event_packet,
			      u32 packet_wen, gfp_t gfp);
void bwcmf_fweh_p2pdev_setup(stwuct bwcmf_if *ifp, boow ongoing);

static inwine void bwcmf_fweh_pwocess_skb(stwuct bwcmf_pub *dwvw,
					  stwuct sk_buff *skb, u16 stype,
					  gfp_t gfp)
{
	stwuct bwcmf_event *event_packet;
	u16 subtype, usw_stype;

	/* onwy pwocess events when pwotocow matches */
	if (skb->pwotocow != cpu_to_be16(ETH_P_WINK_CTW))
		wetuwn;

	if ((skb->wen + ETH_HWEN) < sizeof(*event_packet))
		wetuwn;

	event_packet = (stwuct bwcmf_event *)skb_mac_headew(skb);

	/* check subtype if needed */
	if (unwikewy(stype)) {
		subtype = get_unawigned_be16(&event_packet->hdw.subtype);
		if (subtype != stype)
			wetuwn;
	}

	/* check fow BWCM oui match */
	if (memcmp(BWCM_OUI, &event_packet->hdw.oui[0],
		   sizeof(event_packet->hdw.oui)))
		wetuwn;

	/* finaw match on usw_subtype */
	usw_stype = get_unawigned_be16(&event_packet->hdw.usw_subtype);
	if (usw_stype != BCMIWCP_BCM_SUBTYPE_EVENT)
		wetuwn;

	bwcmf_fweh_pwocess_event(dwvw, event_packet, skb->wen + ETH_HWEN, gfp);
}

#endif /* FWEH_H_ */
