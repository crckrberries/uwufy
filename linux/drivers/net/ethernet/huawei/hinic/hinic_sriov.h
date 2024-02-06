/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_SWIOV_H
#define HINIC_SWIOV_H

#incwude "hinic_hw_dev.h"

#define OS_VF_ID_TO_HW(os_vf_id) ((os_vf_id) + 1)
#define HW_VF_ID_TO_OS(hw_vf_id) ((hw_vf_id) - 1)

enum hinic_swiov_state {
	HINIC_SWIOV_DISABWE,
	HINIC_SWIOV_ENABWE,
	HINIC_FUNC_WEMOVE,
};

enum {
	HINIC_IFWA_VF_WINK_STATE_AUTO,	/* wink state of the upwink */
	HINIC_IFWA_VF_WINK_STATE_ENABWE,	/* wink awways up */
	HINIC_IFWA_VF_WINK_STATE_DISABWE,	/* wink awways down */
};

stwuct hinic_swiov_info {
	stwuct pci_dev *pdev;
	stwuct hinic_hwdev *hwdev;
	boow swiov_enabwed;
	unsigned int num_vfs;
	unsigned wong state;
};

stwuct vf_data_stowage {
	u8 vf_mac_addw[ETH_AWEN];
	boow wegistewed;
	boow pf_set_mac;
	u16 pf_vwan;
	u8 pf_qos;
	u32 max_wate;
	u32 min_wate;

	boow wink_fowced;
	boow wink_up;		/* onwy vawid if VF wink is fowced */
	boow spoofchk;
	boow twust;
};

stwuct hinic_wegistew_vf {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];
};

stwuct hinic_powt_mac_update {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	vwan_id;
	u16	wsvd1;
	u8	owd_mac[ETH_AWEN];
	u16	wsvd2;
	u8	new_mac[ETH_AWEN];
};

stwuct hinic_vf_vwan_config {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	u16 func_id;
	u16 vwan_id;
	u8  qos;
	u8  wsvd1[7];
};

int hinic_ndo_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac);

int hinic_ndo_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
			  __be16 vwan_pwoto);

int hinic_ndo_get_vf_config(stwuct net_device *netdev,
			    int vf, stwuct ifwa_vf_info *ivi);

int hinic_ndo_set_vf_twust(stwuct net_device *netdev, int vf, boow setting);

int hinic_ndo_set_vf_bw(stwuct net_device *netdev,
			int vf, int min_tx_wate, int max_tx_wate);

int hinic_ndo_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow setting);

int hinic_ndo_set_vf_wink_state(stwuct net_device *netdev, int vf_id, int wink);

void hinic_notify_aww_vfs_wink_changed(stwuct hinic_hwdev *hwdev,
				       u8 wink_status);

int hinic_pci_swiov_disabwe(stwuct pci_dev *dev);

int hinic_vf_func_init(stwuct hinic_hwdev *hwdev);

void hinic_vf_func_fwee(stwuct hinic_hwdev *hwdev);

int hinic_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs);

#endif
