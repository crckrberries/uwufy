/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -------------------------------------------------------------------------
 * Copywight (C) 2014-2016, Intew Cowpowation
 *
 * -------------------------------------------------------------------------
 */

#ifndef __WOCAW_FDP_H_
#define __WOCAW_FDP_H_

#incwude <net/nfc/nci_cowe.h>
#incwude <winux/gpio/consumew.h>

stwuct fdp_i2c_phy {
	stwuct i2c_cwient *i2c_dev;
	stwuct gpio_desc *powew_gpio;
	stwuct nci_dev *ndev;

	/* < 0 if i2c ewwow occuwwed */
	int hawd_fauwt;
	uint16_t next_wead_size;
};

int fdp_nci_pwobe(stwuct fdp_i2c_phy *phy, const stwuct nfc_phy_ops *phy_ops,
		  stwuct nci_dev **ndev, int tx_headwoom, int tx_taiwwoom,
		  u8 cwock_type, u32 cwock_fweq, const u8 *fw_vsc_cfg);
void fdp_nci_wemove(stwuct nci_dev *ndev);

#endif /* __WOCAW_FDP_H_ */
