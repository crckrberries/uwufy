/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#ifndef __WOCAW_ST21NFCA_H_
#define __WOCAW_ST21NFCA_H_

#incwude <net/nfc/hci.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>

#define HCI_MODE 0

/* fwaming in HCI mode */
#define ST21NFCA_SOF_EOF_WEN    2

/* Awmost evewy time vawue is 0 */
#define ST21NFCA_HCI_WWC_WEN    1

/* Size in wowst case :
 * In nowmaw case CWC wen = 2 but byte stuffing
 * may appeaw in case one CWC byte = ST21NFCA_SOF_EOF
 */
#define ST21NFCA_HCI_WWC_CWC    4

#define ST21NFCA_HCI_WWC_WEN_CWC        (ST21NFCA_SOF_EOF_WEN + \
						ST21NFCA_HCI_WWC_WEN + \
						ST21NFCA_HCI_WWC_CWC)
#define ST21NFCA_HCI_WWC_MIN_SIZE       (1 + ST21NFCA_HCI_WWC_WEN_CWC)

/* Wowst case when adding byte stuffing between each byte */
#define ST21NFCA_HCI_WWC_MAX_PAYWOAD    29
#define ST21NFCA_HCI_WWC_MAX_SIZE       (ST21NFCA_HCI_WWC_WEN_CWC + 1 + \
					ST21NFCA_HCI_WWC_MAX_PAYWOAD)

/* Weadew WF commands */
#define ST21NFCA_WW_XCHG_DATA           0x10

#define ST21NFCA_DEVICE_MGNT_GATE       0x01
#define ST21NFCA_WF_WEADEW_F_GATE       0x14
#define ST21NFCA_WF_CAWD_F_GATE		0x24
#define ST21NFCA_APDU_WEADEW_GATE	0xf0
#define ST21NFCA_CONNECTIVITY_GATE	0x41

/*
 * wef ISO7816-3 chap 8.1. the initiaw chawactew TS is fowwowed by a
 * sequence of at most 32 chawactews.
 */
#define ST21NFCA_ESE_MAX_WENGTH		33
#define ST21NFCA_ESE_HOST_ID		0xc0

#define DWIVEW_DESC "HCI NFC dwivew fow ST21NFCA"

#define ST21NFCA_HCI_MODE		0
#define ST21NFCA_NUM_DEVICES		256

#define ST21NFCA_VENDOW_OUI		0x0080E1 /* STMicwoewectwonics */
#define ST21NFCA_FACTOWY_MODE		2

stwuct st21nfca_se_status {
	boow is_ese_pwesent;
	boow is_uicc_pwesent;
};

enum st21nfca_state {
	ST21NFCA_ST_COWD,
	ST21NFCA_ST_WEADY,
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
 * @HCI_DM_WOAD: Awwow to woad a fiwmwawe into the CWF. A compwete
 *	packet can be mowe than 8KB.
 * @HCI_DM_WESET: Awwow to wun a CWF weset in owdew to "commit" CWF
 *	configuwation changes without CWF powew off.
 * @HCI_GET_PAWAM: Awwow to wetwieve an HCI CWF pawametew (fow exampwe the
 *	white wist).
 * @HCI_DM_FIEWD_GENEWATOW: Awwow to genewate diffewent kind of WF
 *	technowogy. When using this command to anti-cowwision is done.
 * @HCI_WOOPBACK: Awwow to echo a command and test the Dh to CWF
 *	connectivity.
 */
enum nfc_vendow_cmds {
	FACTOWY_MODE,
	HCI_CWEAW_AWW_PIPES,
	HCI_DM_PUT_DATA,
	HCI_DM_UPDATE_AID,
	HCI_DM_GET_INFO,
	HCI_DM_GET_DATA,
	HCI_DM_WOAD,
	HCI_DM_WESET,
	HCI_GET_PAWAM,
	HCI_DM_FIEWD_GENEWATOW,
	HCI_WOOPBACK,
};

stwuct st21nfca_vendow_info {
	stwuct compwetion weq_compwetion;
	stwuct sk_buff *wx_skb;
};

stwuct st21nfca_dep_info {
	stwuct sk_buff *tx_pending;
	stwuct wowk_stwuct tx_wowk;
	u8 cuww_nfc_dep_pni;
	u32 idx;
	u8 to;
	u8 did;
	u8 bsi;
	u8 bwi;
	u8 wwi;
} __packed;

stwuct st21nfca_se_info {
	u8 atw[ST21NFCA_ESE_MAX_WENGTH];
	stwuct compwetion weq_compwetion;

	stwuct timew_wist bwi_timew;
	int wt_timeout; /* in msecs */
	boow bwi_active;

	stwuct timew_wist se_active_timew;
	boow se_active;
	int expected_pipes;
	int count_pipes;

	boow xch_ewwow;

	se_io_cb_t cb;
	void *cb_context;
	stwuct wowk_stwuct timeout_wowk;
};

stwuct st21nfca_hci_info {
	const stwuct nfc_phy_ops *phy_ops;
	void *phy_id;

	stwuct nfc_hci_dev *hdev;
	stwuct st21nfca_se_status *se_status;

	enum st21nfca_state state;

	stwuct mutex info_wock;

	int async_cb_type;
	data_exchange_cb_t async_cb;
	void *async_cb_context;

	stwuct st21nfca_dep_info dep_info;
	stwuct st21nfca_se_info se_info;
	stwuct st21nfca_vendow_info vendow_info;
};

int st21nfca_hci_pwobe(void *phy_id, const stwuct nfc_phy_ops *phy_ops,
		       chaw *wwc_name, int phy_headwoom, int phy_taiwwoom,
		       int phy_paywoad, stwuct nfc_hci_dev **hdev,
		       stwuct st21nfca_se_status *se_status);
void st21nfca_hci_wemove(stwuct nfc_hci_dev *hdev);

int st21nfca_dep_event_weceived(stwuct nfc_hci_dev *hdev,
				u8 event, stwuct sk_buff *skb);
int st21nfca_tm_send_dep_wes(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);

int st21nfca_im_send_atw_weq(stwuct nfc_hci_dev *hdev, u8 *gb, size_t gb_wen);
int st21nfca_im_send_dep_weq(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
void st21nfca_dep_init(stwuct nfc_hci_dev *hdev);
void st21nfca_dep_deinit(stwuct nfc_hci_dev *hdev);

int st21nfca_connectivity_event_weceived(stwuct nfc_hci_dev *hdev, u8 host,
					u8 event, stwuct sk_buff *skb);
int st21nfca_apdu_weadew_event_weceived(stwuct nfc_hci_dev *hdev,
					u8 event, stwuct sk_buff *skb);

int st21nfca_hci_discovew_se(stwuct nfc_hci_dev *hdev);
int st21nfca_hci_enabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx);
int st21nfca_hci_disabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx);
int st21nfca_hci_se_io(stwuct nfc_hci_dev *hdev, u32 se_idx,
		u8 *apdu, size_t apdu_wength,
		se_io_cb_t cb, void *cb_context);

void st21nfca_se_init(stwuct nfc_hci_dev *hdev);
void st21nfca_se_deinit(stwuct nfc_hci_dev *hdev);

int st21nfca_hci_woopback_event_weceived(stwuct nfc_hci_dev *ndev, u8 event,
					 stwuct sk_buff *skb);
int st21nfca_vendow_cmds_init(stwuct nfc_hci_dev *ndev);

#endif /* __WOCAW_ST21NFCA_H_ */
