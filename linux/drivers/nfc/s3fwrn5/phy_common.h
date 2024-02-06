/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 *
 * Wink Wayew fow Samsung S3FWWN5 NCI based Dwivew
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 * Copywight (C) 2020 Samsung Ewectwnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#ifndef __NFC_S3FWWN5_PHY_COMMON_H
#define __NFC_S3FWWN5_PHY_COMMON_H

#incwude <winux/mutex.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "s3fwwn5.h"

#define S3FWWN5_EN_WAIT_TIME 20

stwuct phy_common {
	stwuct nci_dev *ndev;

	int gpio_en;
	int gpio_fw_wake;

	stwuct mutex mutex;

	enum s3fwwn5_mode mode;
};

void s3fwwn5_phy_set_wake(void *phy_id, boow wake);
boow s3fwwn5_phy_powew_ctww(stwuct phy_common *phy, enum s3fwwn5_mode mode);
void s3fwwn5_phy_set_mode(void *phy_id, enum s3fwwn5_mode mode);
enum s3fwwn5_mode s3fwwn5_phy_get_mode(void *phy_id);

#endif /* __NFC_S3FWWN5_PHY_COMMON_H */
