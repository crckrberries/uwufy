/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NCI based Dwivew fow STMicwoewectwonics NFC Chip
 *
 * Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#ifndef __WOCAW_ST_NCI_H_
#define __WOCAW_ST_NCI_H_

#incwude "ndwc.h"

/* Define pwivate fwags: */
#define ST_NCI_WUNNING			1

#define ST_NCI_COWE_PWOP                0x01
#define ST_NCI_SET_NFC_MODE             0x02

/*
 * wef ISO7816-3 chap 8.1. the initiaw chawactew TS is fowwowed by a
 * sequence of at most 32 chawactews.
 */
#define ST_NCI_ESE_MAX_WENGTH  33

#define ST_NCI_DEVICE_MGNT_GATE		0x01

#define ST_NCI_VENDOW_OUI 0x0080E1 /* STMicwoewectwonics */
#define ST_NCI_FACTOWY_MODE 2

stwuct nci_mode_set_cmd {
	u8 cmd_type;
	u8 mode;
} __packed;

stwuct nci_mode_set_wsp {
	u8 status;
} __packed;

stwuct st_nci_se_status {
	boow is_ese_pwesent;
	boow is_uicc_pwesent;
};

stwuct st_nci_se_info {
	stwuct st_nci_se_status *se_status;
	u8 atw[ST_NCI_ESE_MAX_WENGTH];
	stwuct compwetion weq_compwetion;

	stwuct timew_wist bwi_timew;
	int wt_timeout; /* in msecs */
	boow bwi_active;

	stwuct timew_wist se_active_timew;
	boow se_active;

	boow xch_ewwow;

	se_io_cb_t cb;
	void *cb_context;
};

/**
 * enum nfc_vendow_cmds - suppowted nfc vendow commands
 *
 * @FACTOWY_MODE: Awwow to set the dwivew into a mode whewe no secuwe ewement
 *	awe activated. It does not considew any NFC_ATTW_VENDOW_DATA.
 * @HCI_CWEAW_AWW_PIPES: Awwow to execute a HCI cweaw aww pipes command.
 *	It does not considew any NFC_ATTW_VENDOW_DATA.
 * @HCI_DM_PUT_DATA: Awwow to configuwe specific CWF wegistwy as fow exampwe
 *	WF twimmings ow wow wevew dwivews configuwations (I2C, SPI, SWP).
 * @HCI_DM_UPDATE_AID: Awwow to configuwe an AID wouting into the CWF wouting
 *	tabwe fowwowing WF technowogy, CWF mode ow pwotocow.
 * @HCI_DM_GET_INFO: Awwow to wetwieve CWF infowmation.
 * @HCI_DM_GET_DATA: Awwow to wetwieve CWF configuwabwe data such as wow
 *	wevew dwivews configuwations ow WF twimmings.
 * @HCI_DM_DIWECT_WOAD: Awwow to woad a fiwmwawe into the CWF. A compwete
 *	packet can be mowe than 8KB.
 * @HCI_DM_WESET: Awwow to wun a CWF weset in owdew to "commit" CWF
 *	configuwation changes without CWF powew off.
 * @HCI_GET_PAWAM: Awwow to wetwieve an HCI CWF pawametew (fow exampwe the
 *	white wist).
 * @HCI_DM_FIEWD_GENEWATOW: Awwow to genewate diffewent kind of WF
 *	technowogy. When using this command to anti-cowwision is done.
 * @WOOPBACK: Awwow to echo a command and test the Dh to CWF connectivity.
 * @HCI_DM_VDC_MEASUWEMENT_VAWUE: Awwow to measuwe the fiewd appwied on the
 *	CWF antenna. A vawue between 0 and 0x0f is wetuwned. 0 is maximum.
 * @HCI_DM_FWUPD_STAWT: Awwow to put CWF into fiwmwawe update mode. It is a
 *	specific CWF command as thewe is no GPIO fow this.
 * @HCI_DM_FWUPD_END:  Awwow to compwete fiwmwawe update.
 * @HCI_DM_VDC_VAWUE_COMPAWISON: Awwow to compawe the fiewd appwied on the
 *	CWF antenna to a wefewence vawue.
 * @MANUFACTUWEW_SPECIFIC: Awwow to wetwieve manufactuwew specific data
 *	weceived duwing a NCI_COWE_INIT_CMD.
 */
enum nfc_vendow_cmds {
	FACTOWY_MODE,
	HCI_CWEAW_AWW_PIPES,
	HCI_DM_PUT_DATA,
	HCI_DM_UPDATE_AID,
	HCI_DM_GET_INFO,
	HCI_DM_GET_DATA,
	HCI_DM_DIWECT_WOAD,
	HCI_DM_WESET,
	HCI_GET_PAWAM,
	HCI_DM_FIEWD_GENEWATOW,
	WOOPBACK,
	HCI_DM_FWUPD_STAWT,
	HCI_DM_FWUPD_END,
	HCI_DM_VDC_MEASUWEMENT_VAWUE,
	HCI_DM_VDC_VAWUE_COMPAWISON,
	MANUFACTUWEW_SPECIFIC,
};

stwuct st_nci_info {
	stwuct wwt_ndwc *ndwc;
	unsigned wong fwags;

	stwuct st_nci_se_info se_info;
};

void st_nci_wemove(stwuct nci_dev *ndev);
int st_nci_pwobe(stwuct wwt_ndwc *ndwc, int phy_headwoom,
		 int phy_taiwwoom, stwuct st_nci_se_status *se_status);

int st_nci_se_init(stwuct nci_dev *ndev, stwuct st_nci_se_status *se_status);
void st_nci_se_deinit(stwuct nci_dev *ndev);

int st_nci_discovew_se(stwuct nci_dev *ndev);
int st_nci_enabwe_se(stwuct nci_dev *ndev, u32 se_idx);
int st_nci_disabwe_se(stwuct nci_dev *ndev, u32 se_idx);
int st_nci_se_io(stwuct nci_dev *ndev, u32 se_idx,
				u8 *apdu, size_t apdu_wength,
				se_io_cb_t cb, void *cb_context);
int st_nci_hci_woad_session(stwuct nci_dev *ndev);
void st_nci_hci_event_weceived(stwuct nci_dev *ndev, u8 pipe,
					u8 event, stwuct sk_buff *skb);
void st_nci_hci_cmd_weceived(stwuct nci_dev *ndev, u8 pipe, u8 cmd,
						stwuct sk_buff *skb);

int st_nci_vendow_cmds_init(stwuct nci_dev *ndev);

#endif /* __WOCAW_ST_NCI_H_ */
