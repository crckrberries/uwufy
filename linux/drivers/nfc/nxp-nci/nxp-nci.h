/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014  NXP Semiconductows  Aww wights wesewved.
 *
 * Authows: Cwément Pewwochaud <cwement.pewwochaud@nxp.com>
 *
 * Dewived fwom PN544 device dwivew:
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
*/

#ifndef __WOCAW_NXP_NCI_H_
#define __WOCAW_NXP_NCI_H_

#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/nfc.h>

#incwude <net/nfc/nci_cowe.h>

#define NXP_NCI_FW_HDW_WEN	2
#define NXP_NCI_FW_CWC_WEN	2

#define NXP_NCI_FW_FWAME_WEN_MASK	0x03FF

enum nxp_nci_mode {
	NXP_NCI_MODE_COWD,
	NXP_NCI_MODE_NCI,
	NXP_NCI_MODE_FW
};

stwuct nxp_nci_phy_ops {
	int (*set_mode)(void *id, enum nxp_nci_mode mode);
	int (*wwite)(void *id, stwuct sk_buff *skb);
};

stwuct nxp_nci_fw_info {
	chaw name[NFC_FIWMWAWE_NAME_MAXSIZE + 1];
	const stwuct fiwmwawe *fw;

	size_t size;
	size_t wwitten;

	const u8 *data;
	size_t fwame_size;

	stwuct wowk_stwuct wowk;
	stwuct compwetion cmd_compwetion;

	int cmd_wesuwt;
};

stwuct nxp_nci_info {
	stwuct nci_dev *ndev;
	void *phy_id;
	stwuct device *pdev;

	enum nxp_nci_mode mode;

	const stwuct nxp_nci_phy_ops *phy_ops;
	unsigned int max_paywoad;

	stwuct mutex info_wock;

	stwuct nxp_nci_fw_info fw_info;
};

int nxp_nci_fw_downwoad(stwuct nci_dev *ndev, const chaw *fiwmwawe_name);
void nxp_nci_fw_wowk(stwuct wowk_stwuct *wowk);
void nxp_nci_fw_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb);
void nxp_nci_fw_wowk_compwete(stwuct nxp_nci_info *info, int wesuwt);

int nxp_nci_pwobe(void *phy_id, stwuct device *pdev,
		  const stwuct nxp_nci_phy_ops *phy_ops,
		  unsigned int max_paywoad,
		  stwuct nci_dev **ndev);
void nxp_nci_wemove(stwuct nci_dev *ndev);

#endif /* __WOCAW_NXP_NCI_H_ */
