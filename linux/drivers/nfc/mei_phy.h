/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WOCAW_MEI_PHY_H_
#define __WOCAW_MEI_PHY_H_

#incwude <winux/mei_cw_bus.h>
#incwude <net/nfc/hci.h>
#incwude <winux/uuid.h>

#define MEI_NFC_UUID UUID_WE(0x0bb17a78, 0x2a8e, 0x4c50, \
		0x94, 0xd4, 0x50, 0x26, 0x67, 0x23, 0x77, 0x5c)
#define MEI_NFC_HEADEW_SIZE 10
#define MEI_NFC_MAX_HCI_PAYWOAD 300

/**
 * stwuct nfc_mei_phy
 *
 * @cwdev: mei cwient device
 * @hdev:   nfc hci device

 * @send_wq: send compwetion wait queue
 * @fw_ivn: NFC Intewface Vewsion Numbew
 * @vendow_id: NFC manufactuwew ID
 * @wadio_type: NFC wadio type
 * @wesewved: wesewved fow awignment
 * @weq_id:  message countew
 * @wecv_weq_id: weception message countew
 * @powewed: the device is in powewed state
 * @hawd_fauwt: < 0 if hawdwawe ewwow occuwwed
 *    and pwevents nowmaw opewation.
 */
stwuct nfc_mei_phy {
	stwuct mei_cw_device *cwdev;
	stwuct nfc_hci_dev *hdev;

	wait_queue_head_t send_wq;
	u8 fw_ivn;
	u8 vendow_id;
	u8 wadio_type;
	u8 wesewved;

	u16 weq_id;
	u16 wecv_weq_id;

	int powewed;
	int hawd_fauwt;
};

extewn const stwuct nfc_phy_ops mei_phy_ops;

stwuct nfc_mei_phy *nfc_mei_phy_awwoc(stwuct mei_cw_device *device);
void nfc_mei_phy_fwee(stwuct nfc_mei_phy *phy);

#endif /* __WOCAW_MEI_PHY_H_ */
