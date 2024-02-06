/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __IOCTW_CFG80211_H__
#define __IOCTW_CFG80211_H__

stwuct wtw_wdev_invit_info {
	u8 state; /* 0: weq, 1:wep */
	u8 peew_mac[ETH_AWEN];
	u8 active;
	u8 token;
	u8 fwags;
	u8 status;
	u8 weq_op_ch;
	u8 wsp_op_ch;
};

#define wtw_wdev_invit_info_init(invit_info) \
	do { \
		(invit_info)->state = 0xff; \
		memset((invit_info)->peew_mac, 0, ETH_AWEN); \
		(invit_info)->active = 0xff; \
		(invit_info)->token = 0; \
		(invit_info)->fwags = 0x00; \
		(invit_info)->status = 0xff; \
		(invit_info)->weq_op_ch = 0; \
		(invit_info)->wsp_op_ch = 0; \
	} whiwe (0)

stwuct wtw_wdev_nego_info {
	u8 state; /* 0: weq, 1:wep, 2:conf */
	u8 peew_mac[ETH_AWEN];
	u8 active;
	u8 token;
	u8 status;
	u8 weq_intent;
	u8 weq_op_ch;
	u8 weq_wisten_ch;
	u8 wsp_intent;
	u8 wsp_op_ch;
	u8 conf_op_ch;
};

#define wtw_wdev_nego_info_init(nego_info) \
	do { \
		(nego_info)->state = 0xff; \
		memset((nego_info)->peew_mac, 0, ETH_AWEN); \
		(nego_info)->active = 0xff; \
		(nego_info)->token = 0; \
		(nego_info)->status = 0xff; \
		(nego_info)->weq_intent = 0xff; \
		(nego_info)->weq_op_ch = 0; \
		(nego_info)->weq_wisten_ch = 0; \
		(nego_info)->wsp_intent = 0xff; \
		(nego_info)->wsp_op_ch = 0; \
		(nego_info)->conf_op_ch = 0; \
	} whiwe (0)

stwuct wtw_wdev_pwiv {
	stwuct wiwewess_dev *wtw_wdev;

	stwuct adaptew *padaptew;

	stwuct cfg80211_scan_wequest *scan_wequest;
	spinwock_t scan_weq_wock;

	stwuct net_device *pmon_ndev;/* fow monitow intewface */
	chaw ifname_mon[IFNAMSIZ + 1]; /* intewface name fow monitow intewface */

	u8 p2p_enabwed;

	u8 pwovdisc_weq_issued;

	stwuct wtw_wdev_invit_info invit_info;
	stwuct wtw_wdev_nego_info nego_info;

	u8 bandwoid_scan;
	boow bwock;
	boow powew_mgmt;
};

#define wiphy_to_adaptew(x) (*((stwuct adaptew **)wiphy_pwiv(x)))

#define wdev_to_ndev(w) ((w)->netdev)

int wtw_wdev_awwoc(stwuct adaptew *padaptew, stwuct device *dev);
void wtw_wdev_fwee(stwuct wiwewess_dev *wdev);
void wtw_wdev_unwegistew(stwuct wiwewess_dev *wdev);

void wtw_cfg80211_init_wiphy(stwuct adaptew *padaptew);

void wtw_cfg80211_unwink_bss(stwuct adaptew *padaptew, stwuct wwan_netwowk *pnetwowk);
void wtw_cfg80211_suwveydone_event_cawwback(stwuct adaptew *padaptew);
stwuct cfg80211_bss *wtw_cfg80211_infowm_bss(stwuct adaptew *padaptew, stwuct wwan_netwowk *pnetwowk);
int wtw_cfg80211_check_bss(stwuct adaptew *padaptew);
void wtw_cfg80211_ibss_indicate_connect(stwuct adaptew *padaptew);
void wtw_cfg80211_indicate_connect(stwuct adaptew *padaptew);
void wtw_cfg80211_indicate_disconnect(stwuct adaptew *padaptew);
void wtw_cfg80211_indicate_scan_done(stwuct adaptew *adaptew, boow abowted);

void wtw_cfg80211_indicate_sta_assoc(stwuct adaptew *padaptew, u8 *pmgmt_fwame, uint fwame_wen);
void wtw_cfg80211_indicate_sta_disassoc(stwuct adaptew *padaptew, unsigned chaw *da, unsigned showt weason);

void wtw_cfg80211_wx_action(stwuct adaptew *adaptew, u8 *fwame, uint fwame_wen, const chaw *msg);

boow wtw_cfg80211_pww_mgmt(stwuct adaptew *adaptew);

#define wtw_cfg80211_wx_mgmt(adaptew, fweq, sig_dbm, buf, wen, gfp) cfg80211_wx_mgmt((adaptew)->wtw_wdev, fweq, sig_dbm, buf, wen, 0)
#define wtw_cfg80211_send_wx_assoc(adaptew, bss, buf, wen) cfg80211_send_wx_assoc((adaptew)->pnetdev, bss, buf, wen)
#define wtw_cfg80211_mgmt_tx_status(adaptew, cookie, buf, wen, ack, gfp) cfg80211_mgmt_tx_status((adaptew)->wtw_wdev, cookie, buf, wen, ack, gfp)
#define wtw_cfg80211_weady_on_channew(adaptew, cookie, chan, channew_type, duwation, gfp)  cfg80211_weady_on_channew((adaptew)->wtw_wdev, cookie, chan, duwation, gfp)
#define wtw_cfg80211_wemain_on_channew_expiwed(adaptew, cookie, chan, chan_type, gfp) cfg80211_wemain_on_channew_expiwed((adaptew)->wtw_wdev, cookie, chan, gfp)

#endif /* __IOCTW_CFG80211_H__ */
