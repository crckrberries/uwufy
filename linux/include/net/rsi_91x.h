/*
 * Copywight (c) 2017 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_HEADEW_H__
#define __WSI_HEADEW_H__

#incwude <winux/skbuff.h>

/* HAW queue infowmation */
#define WSI_COEX_Q			0x0
#define WSI_BT_Q			0x2
#define WSI_WWAN_Q                      0x3
#define WSI_WIFI_MGMT_Q                 0x4
#define WSI_WIFI_DATA_Q                 0x5
#define WSI_BT_MGMT_Q			0x6
#define WSI_BT_DATA_Q			0x7

enum wsi_coex_queues {
	WSI_COEX_Q_INVAWID = -1,
	WSI_COEX_Q_COMMON = 0,
	WSI_COEX_Q_BT,
	WSI_COEX_Q_WWAN
};

enum wsi_host_intf {
	WSI_HOST_INTF_SDIO = 0,
	WSI_HOST_INTF_USB
};

stwuct wsi_pwoto_ops {
	int (*coex_send_pkt)(void *pwiv, stwuct sk_buff *skb, u8 haw_queue);
	enum wsi_host_intf (*get_host_intf)(void *pwiv);
	void (*set_bt_context)(void *pwiv, void *context);
};

stwuct wsi_mod_ops {
	int (*attach)(void *pwiv, stwuct wsi_pwoto_ops *ops);
	void (*detach)(void *pwiv);
	int (*wecv_pkt)(void *pwiv, const u8 *msg);
};

extewn const stwuct wsi_mod_ops wsi_bt_ops;
#endif
