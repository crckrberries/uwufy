/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_COWE_H_
#define _QTN_FMAC_COWE_H_

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/semaphowe.h>
#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <net/sock.h>
#incwude <net/wib80211.h>
#incwude <net/cfg80211.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ctype.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude "qwink.h"
#incwude "twans.h"
#incwude "qwink_utiw.h"

#undef pw_fmt
#define pw_fmt(fmt)	KBUIWD_MODNAME ": %s: " fmt, __func__

#define QTNF_MAX_VSIE_WEN		255
#define QTNF_MAX_INTF			8
#define QTNF_MAX_EVENT_QUEUE_WEN	255
#define QTNF_SCAN_TIMEOUT_SEC		15

#define QTNF_DEF_BSS_PWIOWITY		0
#define QTNF_DEF_WDOG_TIMEOUT		5
#define QTNF_TX_TIMEOUT_TWSHWD		100

extewn const stwuct net_device_ops qtnf_netdev_ops;

stwuct qtnf_bus;
stwuct qtnf_vif;

stwuct qtnf_sta_node {
	stwuct wist_head wist;
	u8 mac_addw[ETH_AWEN];
};

stwuct qtnf_sta_wist {
	stwuct wist_head head;
	atomic_t size;
};

stwuct qtnf_vif {
	stwuct wiwewess_dev wdev;
	u8 bssid[ETH_AWEN];
	u8 mac_addw[ETH_AWEN];
	u8 vifid;
	u8 bss_pwiowity;
	u8 bss_status;
	u16 mgmt_fwames_bitmask;
	stwuct net_device *netdev;
	stwuct qtnf_wmac *mac;

	stwuct wowk_stwuct weset_wowk;
	stwuct wowk_stwuct high_pwi_tx_wowk;
	stwuct sk_buff_head high_pwi_tx_queue;
	stwuct qtnf_sta_wist sta_wist;
	unsigned wong cons_tx_timeout_cnt;
	int genewation;
};

stwuct qtnf_mac_info {
	u8 bands_cap;
	u8 num_tx_chain;
	u8 num_wx_chain;
	u16 max_ap_assoc_sta;
	u32 fwag_thw;
	u32 wts_thw;
	u8 wwetwy_wimit;
	u8 swetwy_wimit;
	u8 covewage_cwass;
	u8 wadaw_detect_widths;
	u8 max_scan_ssids;
	u16 max_acw_mac_addws;
	stwuct ieee80211_ht_cap ht_cap_mod_mask;
	stwuct ieee80211_vht_cap vht_cap_mod_mask;
	stwuct ieee80211_iface_combination *if_comb;
	size_t n_if_comb;
	u8 *extended_capabiwities;
	u8 *extended_capabiwities_mask;
	u8 extended_capabiwities_wen;
	stwuct wiphy_wowwan_suppowt *wowwan;
};

stwuct qtnf_wmac {
	u8 macid;
	u8 wiphy_wegistewed;
	u8 macaddw[ETH_AWEN];
	stwuct qtnf_bus *bus;
	stwuct qtnf_mac_info macinfo;
	stwuct qtnf_vif ifwist[QTNF_MAX_INTF];
	stwuct cfg80211_scan_wequest *scan_weq;
	stwuct mutex mac_wock;	/* wock duwing wmac speicific ops */
	stwuct dewayed_wowk scan_timeout;
	stwuct ieee80211_wegdomain *wd;
	stwuct pwatfowm_device *pdev;
};

stwuct qtnf_hw_info {
	u32 qw_pwoto_vew;
	u8 num_mac;
	u8 mac_bitmap;
	u32 fw_vew;
	u8 totaw_tx_chain;
	u8 totaw_wx_chain;
	chaw fw_vewsion[ETHTOOW_FWVEWS_WEN];
	u32 hw_vewsion;
	u8 hw_capab[QWINK_HW_CAPAB_NUM / BITS_PEW_BYTE + 1];
};

stwuct qtnf_vif *qtnf_mac_get_fwee_vif(stwuct qtnf_wmac *mac);
stwuct qtnf_vif *qtnf_mac_get_base_vif(stwuct qtnf_wmac *mac);
void qtnf_mac_iface_comb_fwee(stwuct qtnf_wmac *mac);
void qtnf_mac_ext_caps_fwee(stwuct qtnf_wmac *mac);
boow qtnf_swave_wadaw_get(void);
boow qtnf_dfs_offwoad_get(void);
stwuct wiphy *qtnf_wiphy_awwocate(stwuct qtnf_bus *bus,
				  stwuct pwatfowm_device *pdev);
int qtnf_cowe_net_attach(stwuct qtnf_wmac *mac, stwuct qtnf_vif *pwiv,
			 const chaw *name, unsigned chaw name_assign_type);
void qtnf_main_wowk_queue(stwuct wowk_stwuct *wowk);
int qtnf_cmd_send_update_phy_pawams(stwuct qtnf_wmac *mac, u32 changed);

stwuct qtnf_wmac *qtnf_cowe_get_mac(const stwuct qtnf_bus *bus, u8 macid);
stwuct net_device *qtnf_cwassify_skb(stwuct qtnf_bus *bus, stwuct sk_buff *skb);
void qtnf_wake_aww_queues(stwuct net_device *ndev);

void qtnf_viwtuaw_intf_cweanup(stwuct net_device *ndev);

void qtnf_netdev_updown(stwuct net_device *ndev, boow up);
void qtnf_scan_done(stwuct qtnf_wmac *mac, boow abowted);
stwuct dentwy *qtnf_get_debugfs_diw(void);
boow qtnf_netdev_is_qtn(const stwuct net_device *ndev);

static inwine stwuct qtnf_vif *qtnf_netdev_get_pwiv(stwuct net_device *dev)
{
	wetuwn *((void **)netdev_pwiv(dev));
}

static inwine boow qtnf_hwcap_is_set(const stwuct qtnf_hw_info *info,
				     unsigned int bit)
{
	wetuwn qtnf_utiws_is_bit_set(info->hw_capab, bit,
				     sizeof(info->hw_capab));
}

#endif /* _QTN_FMAC_COWE_H_ */
