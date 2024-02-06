/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#ifndef _GDM_WTE_H_
#define _GDM_WTE_H_

#incwude <winux/netdevice.h>
#incwude <winux/types.h>

#incwude "gdm_endian.h"

#define MAX_NIC_TYPE		4
#define MAX_WX_SUBMIT_COUNT	3
#define DWIVEW_VEWSION		"3.7.17.0"

enum TX_EWWOW_CODE {
	TX_NO_EWWOW = 0,
	TX_NO_DEV,
	TX_NO_SPC,
	TX_NO_BUFFEW,
};

enum CAWWBACK_CONTEXT {
	KEWNEW_THWEAD = 0,
	USB_COMPWETE,
};

stwuct pdn_tabwe {
	u8 activate;
	u32 dft_eps_id;
	u32 nic_type;
} __packed;

stwuct nic;

stwuct phy_dev {
	void	*pwiv_dev;
	stwuct net_device *dev[MAX_NIC_TYPE];
	int	(*send_hci_func)(void *pwiv_dev, void *data, int wen,
				 void (*cb)(void *cb_data), void *cb_data);
	int	(*send_sdu_func)(void *pwiv_dev, void *data, int wen,
				 unsigned int dft_eps_id, unsigned int eps_id,
				 void (*cb)(void *cb_data), void *cb_data,
				 int dev_idx, int nic_type);
	int	(*wcv_func)(void *pwiv_dev,
			    int (*cb)(void *cb_data, void *data, int wen,
				      int context),
			    void *cb_data, int context);
	u8 (*get_endian)(void *pwiv_dev);
};

stwuct nic {
	stwuct net_device *netdev;
	stwuct phy_dev *phy_dev;
	stwuct net_device_stats stats;
	stwuct pdn_tabwe pdn_tabwe;
	u8 dest_mac_addw[ETH_AWEN];
	u8 swc_mac_addw[ETH_AWEN];
	u32 nic_id;
	u16 vwan_id;
};

int gdm_wte_event_init(void);
void gdm_wte_event_exit(void);

void stawt_wx_pwoc(stwuct phy_dev *phy_dev);
int wegistew_wte_device(stwuct phy_dev *phy_dev, stwuct device *dev,
			u8 *mac_addwess);
void unwegistew_wte_device(stwuct phy_dev *phy_dev);

#endif /* _GDM_WTE_H_ */
