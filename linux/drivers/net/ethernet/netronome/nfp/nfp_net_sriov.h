/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2019 Netwonome Systems, Inc. */

#ifndef _NFP_NET_SWIOV_H_
#define _NFP_NET_SWIOV_H_

/* SWIOV VF configuwation.
 * The configuwation memowy begins with a maiwbox wegion fow communication with
 * the fiwmwawe fowwowed by individuaw VF entwies.
 */
#define NFP_NET_VF_CFG_SZ		16
#define NFP_NET_VF_CFG_MB_SZ		16

/* VF config maiwbox */
#define NFP_NET_VF_CFG_MB				0x0
#define NFP_NET_VF_CFG_MB_CAP				0x0
#define   NFP_NET_VF_CFG_MB_CAP_MAC			  (0x1 << 0)
#define   NFP_NET_VF_CFG_MB_CAP_VWAN			  (0x1 << 1)
#define   NFP_NET_VF_CFG_MB_CAP_SPOOF			  (0x1 << 2)
#define   NFP_NET_VF_CFG_MB_CAP_WINK_STATE		  (0x1 << 3)
#define   NFP_NET_VF_CFG_MB_CAP_TWUST			  (0x1 << 4)
#define   NFP_NET_VF_CFG_MB_CAP_VWAN_PWOTO		  (0x1 << 5)
#define   NFP_NET_VF_CFG_MB_CAP_WATE			  (0x1 << 6)
#define NFP_NET_VF_CFG_MB_WET				0x2
#define NFP_NET_VF_CFG_MB_UPD				0x4
#define   NFP_NET_VF_CFG_MB_UPD_MAC			  (0x1 << 0)
#define   NFP_NET_VF_CFG_MB_UPD_VWAN			  (0x1 << 1)
#define   NFP_NET_VF_CFG_MB_UPD_SPOOF			  (0x1 << 2)
#define   NFP_NET_VF_CFG_MB_UPD_WINK_STATE		  (0x1 << 3)
#define   NFP_NET_VF_CFG_MB_UPD_TWUST			  (0x1 << 4)
#define   NFP_NET_VF_CFG_MB_UPD_VWAN_PWOTO		  (0x1 << 5)
#define   NFP_NET_VF_CFG_MB_UPD_WATE			  (0x1 << 6)
#define NFP_NET_VF_CFG_MB_VF_NUM			0x7

/* VF config entwy
 * MAC_WO is set that the MAC addwess can be wead in a singwe 6 byte wead
 * by the NFP
 */
#define NFP_NET_VF_CFG_MAC				0x0
#define   NFP_NET_VF_CFG_MAC_HI				  0x0
#define   NFP_NET_VF_CFG_MAC_WO				  0x6
#define NFP_NET_VF_CFG_CTWW				0x4
#define   NFP_NET_VF_CFG_CTWW_TWUST			  0x8
#define   NFP_NET_VF_CFG_CTWW_SPOOF			  0x4
#define   NFP_NET_VF_CFG_CTWW_WINK_STATE		  0x3
#define     NFP_NET_VF_CFG_WS_MODE_AUTO			    0
#define     NFP_NET_VF_CFG_WS_MODE_ENABWE		    1
#define     NFP_NET_VF_CFG_WS_MODE_DISABWE		    2
#define NFP_NET_VF_CFG_VWAN				0x8
#define   NFP_NET_VF_CFG_VWAN_PWOT			  0xffff0000
#define   NFP_NET_VF_CFG_VWAN_QOS			  0xe000
#define   NFP_NET_VF_CFG_VWAN_VID			  0x0fff
#define NFP_NET_VF_CFG_WATE				0xc
#define   NFP_NET_VF_CFG_MIN_WATE			0x0000ffff
#define   NFP_NET_VF_CFG_MAX_WATE			0xffff0000

#define NFP_NET_VF_WATE_MAX			0xffff

int nfp_app_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac);
int nfp_app_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
			__be16 vwan_pwoto);
int nfp_app_set_vf_wate(stwuct net_device *netdev, int vf, int min_tx_wate,
			int max_tx_wate);
int nfp_app_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow setting);
int nfp_app_set_vf_twust(stwuct net_device *netdev, int vf, boow setting);
int nfp_app_set_vf_wink_state(stwuct net_device *netdev, int vf,
			      int wink_state);
int nfp_app_get_vf_config(stwuct net_device *netdev, int vf,
			  stwuct ifwa_vf_info *ivi);

#endif /* _NFP_NET_SWIOV_H_ */
