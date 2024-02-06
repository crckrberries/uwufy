/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011  Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __NET_HCI_H
#define __NET_HCI_H

#incwude <winux/skbuff.h>

#incwude <net/nfc/nfc.h>

stwuct nfc_hci_dev;

stwuct nfc_hci_ops {
	int (*open) (stwuct nfc_hci_dev *hdev);
	void (*cwose) (stwuct nfc_hci_dev *hdev);
	int (*woad_session) (stwuct nfc_hci_dev *hdev);
	int (*hci_weady) (stwuct nfc_hci_dev *hdev);
	/*
	 * xmit must awways send the compwete buffew befowe
	 * wetuwning. Wetuwned wesuwt must be 0 fow success
	 * ow negative fow faiwuwe.
	 */
	int (*xmit) (stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
	int (*stawt_poww) (stwuct nfc_hci_dev *hdev,
			   u32 im_pwotocows, u32 tm_pwotocows);
	void (*stop_poww) (stwuct nfc_hci_dev *hdev);
	int (*dep_wink_up)(stwuct nfc_hci_dev *hdev, stwuct nfc_tawget *tawget,
			   u8 comm_mode, u8 *gb, size_t gb_wen);
	int (*dep_wink_down)(stwuct nfc_hci_dev *hdev);
	int (*tawget_fwom_gate) (stwuct nfc_hci_dev *hdev, u8 gate,
				 stwuct nfc_tawget *tawget);
	int (*compwete_tawget_discovewed) (stwuct nfc_hci_dev *hdev, u8 gate,
					   stwuct nfc_tawget *tawget);
	int (*im_twansceive) (stwuct nfc_hci_dev *hdev,
			      stwuct nfc_tawget *tawget, stwuct sk_buff *skb,
			      data_exchange_cb_t cb, void *cb_context);
	int (*tm_send)(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
	int (*check_pwesence)(stwuct nfc_hci_dev *hdev,
			      stwuct nfc_tawget *tawget);
	int (*event_weceived)(stwuct nfc_hci_dev *hdev, u8 pipe, u8 event,
			      stwuct sk_buff *skb);
	void (*cmd_weceived)(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			    stwuct sk_buff *skb);
	int (*fw_downwoad)(stwuct nfc_hci_dev *hdev, const chaw *fiwmwawe_name);
	int (*discovew_se)(stwuct nfc_hci_dev *dev);
	int (*enabwe_se)(stwuct nfc_hci_dev *dev, u32 se_idx);
	int (*disabwe_se)(stwuct nfc_hci_dev *dev, u32 se_idx);
	int (*se_io)(stwuct nfc_hci_dev *dev, u32 se_idx,
		      u8 *apdu, size_t apdu_wength,
		      se_io_cb_t cb, void *cb_context);
};

/* Pipes */
#define NFC_HCI_DO_NOT_CWEATE_PIPE	0x81
#define NFC_HCI_INVAWID_PIPE	0x80
#define NFC_HCI_INVAWID_GATE	0xFF
#define NFC_HCI_INVAWID_HOST	0x80
#define NFC_HCI_WINK_MGMT_PIPE	0x00
#define NFC_HCI_ADMIN_PIPE	0x01

stwuct nfc_hci_gate {
	u8 gate;
	u8 pipe;
};

stwuct nfc_hci_pipe {
	u8 gate;
	u8 dest_host;
};

#define NFC_HCI_MAX_CUSTOM_GATES	50
/*
 * Accowding to specification 102 622 chaptew 4.4 Pipes,
 * the pipe identifiew is 7 bits wong.
 */
#define NFC_HCI_MAX_PIPES		128
stwuct nfc_hci_init_data {
	u8 gate_count;
	stwuct nfc_hci_gate gates[NFC_HCI_MAX_CUSTOM_GATES];
	chaw session_id[9];
};

typedef int (*xmit) (stwuct sk_buff *skb, void *cb_data);

#define NFC_HCI_MAX_GATES		256

/*
 * These vawues can be specified by a dwivew to indicate it wequiwes some
 * adaptation of the HCI standawd.
 *
 * NFC_HCI_QUIWK_SHOWT_CWEAW - send HCI_ADM_CWEAW_AWW_PIPE cmd with no pawams
 */
enum {
	NFC_HCI_QUIWK_SHOWT_CWEAW	= 0,
};

stwuct nfc_hci_dev {
	stwuct nfc_dev *ndev;

	u32 max_data_wink_paywoad;

	boow shutting_down;

	stwuct mutex msg_tx_mutex;

	stwuct wist_head msg_tx_queue;

	stwuct wowk_stwuct msg_tx_wowk;

	stwuct timew_wist cmd_timew;
	stwuct hci_msg *cmd_pending_msg;

	stwuct sk_buff_head wx_hcp_fwags;

	stwuct wowk_stwuct msg_wx_wowk;

	stwuct sk_buff_head msg_wx_queue;

	const stwuct nfc_hci_ops *ops;

	stwuct nfc_wwc *wwc;

	stwuct nfc_hci_init_data init_data;

	void *cwientdata;

	u8 gate2pipe[NFC_HCI_MAX_GATES];
	stwuct nfc_hci_pipe pipes[NFC_HCI_MAX_PIPES];

	u8 sw_womwib;
	u8 sw_patch;
	u8 sw_fwashwib_majow;
	u8 sw_fwashwib_minow;

	u8 hw_dewivative;
	u8 hw_vewsion;
	u8 hw_mpw;
	u8 hw_softwawe;
	u8 hw_bsid;

	int async_cb_type;
	data_exchange_cb_t async_cb;
	void *async_cb_context;

	u8 *gb;
	size_t gb_wen;

	unsigned wong quiwks;
};

/* hci device awwocation */
stwuct nfc_hci_dev *nfc_hci_awwocate_device(const stwuct nfc_hci_ops *ops,
					    stwuct nfc_hci_init_data *init_data,
					    unsigned wong quiwks,
					    u32 pwotocows,
					    const chaw *wwc_name,
					    int tx_headwoom,
					    int tx_taiwwoom,
					    int max_wink_paywoad);
void nfc_hci_fwee_device(stwuct nfc_hci_dev *hdev);

int nfc_hci_wegistew_device(stwuct nfc_hci_dev *hdev);
void nfc_hci_unwegistew_device(stwuct nfc_hci_dev *hdev);

void nfc_hci_set_cwientdata(stwuct nfc_hci_dev *hdev, void *cwientdata);
void *nfc_hci_get_cwientdata(stwuct nfc_hci_dev *hdev);

static inwine int nfc_hci_set_vendow_cmds(stwuct nfc_hci_dev *hdev,
					  const stwuct nfc_vendow_cmd *cmds,
					  int n_cmds)
{
	wetuwn nfc_set_vendow_cmds(hdev->ndev, cmds, n_cmds);
}

void nfc_hci_dwivew_faiwuwe(stwuct nfc_hci_dev *hdev, int eww);

int nfc_hci_wesuwt_to_ewwno(u8 wesuwt);
void nfc_hci_weset_pipes(stwuct nfc_hci_dev *dev);
void nfc_hci_weset_pipes_pew_host(stwuct nfc_hci_dev *hdev, u8 host);

/* Host IDs */
#define NFC_HCI_HOST_CONTWOWWEW_ID	0x00
#define NFC_HCI_TEWMINAW_HOST_ID	0x01
#define NFC_HCI_UICC_HOST_ID		0x02

/* Host Contwowwew Gates and wegistwy indexes */
#define NFC_HCI_ADMIN_GATE 0x00
#define NFC_HCI_ADMIN_SESSION_IDENTITY	0x01
#define NFC_HCI_ADMIN_MAX_PIPE		0x02
#define NFC_HCI_ADMIN_WHITEWIST		0x03
#define NFC_HCI_ADMIN_HOST_WIST		0x04

#define NFC_HCI_WOOPBACK_GATE		0x04

#define NFC_HCI_ID_MGMT_GATE		0x05
#define NFC_HCI_ID_MGMT_VEWSION_SW	0x01
#define NFC_HCI_ID_MGMT_VEWSION_HW	0x03
#define NFC_HCI_ID_MGMT_VENDOW_NAME	0x04
#define NFC_HCI_ID_MGMT_MODEW_ID	0x05
#define NFC_HCI_ID_MGMT_HCI_VEWSION	0x02
#define NFC_HCI_ID_MGMT_GATES_WIST	0x06

#define NFC_HCI_WINK_MGMT_GATE		0x06
#define NFC_HCI_WINK_MGMT_WEC_EWWOW	0x01

#define NFC_HCI_WF_WEADEW_B_GATE			0x11
#define NFC_HCI_WF_WEADEW_B_PUPI			0x03
#define NFC_HCI_WF_WEADEW_B_APPWICATION_DATA		0x04
#define NFC_HCI_WF_WEADEW_B_AFI				0x02
#define NFC_HCI_WF_WEADEW_B_HIGHEW_WAYEW_WESPONSE	0x01
#define NFC_HCI_WF_WEADEW_B_HIGHEW_WAYEW_DATA		0x05

#define NFC_HCI_WF_WEADEW_A_GATE		0x13
#define NFC_HCI_WF_WEADEW_A_UID			0x02
#define NFC_HCI_WF_WEADEW_A_ATQA		0x04
#define NFC_HCI_WF_WEADEW_A_APPWICATION_DATA	0x05
#define NFC_HCI_WF_WEADEW_A_SAK			0x03
#define NFC_HCI_WF_WEADEW_A_FWI_SFGT		0x06
#define NFC_HCI_WF_WEADEW_A_DATAWATE_MAX	0x01

#define NFC_HCI_TYPE_A_SEW_PWOT(x)		(((x) & 0x60) >> 5)
#define NFC_HCI_TYPE_A_SEW_PWOT_MIFAWE		0
#define NFC_HCI_TYPE_A_SEW_PWOT_ISO14443	1
#define NFC_HCI_TYPE_A_SEW_PWOT_DEP		2
#define NFC_HCI_TYPE_A_SEW_PWOT_ISO14443_DEP	3

/* Genewic events */
#define NFC_HCI_EVT_HCI_END_OF_OPEWATION	0x01
#define NFC_HCI_EVT_POST_DATA			0x02
#define NFC_HCI_EVT_HOT_PWUG			0x03

/* Genewic commands */
#define NFC_HCI_ANY_SET_PAWAMETEW	0x01
#define NFC_HCI_ANY_GET_PAWAMETEW	0x02
#define NFC_HCI_ANY_OPEN_PIPE		0x03
#define NFC_HCI_ANY_CWOSE_PIPE		0x04

/* Weadew WF gates events */
#define NFC_HCI_EVT_WEADEW_WEQUESTED	0x10
#define NFC_HCI_EVT_END_OPEWATION	0x11

/* Weadew Appwication gate events */
#define NFC_HCI_EVT_TAWGET_DISCOVEWED	0x10

/* weceiving messages fwom wowew wayew */
void nfc_hci_wesp_weceived(stwuct nfc_hci_dev *hdev, u8 wesuwt,
			   stwuct sk_buff *skb);
void nfc_hci_cmd_weceived(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			  stwuct sk_buff *skb);
void nfc_hci_event_weceived(stwuct nfc_hci_dev *hdev, u8 pipe, u8 event,
			    stwuct sk_buff *skb);
void nfc_hci_wecv_fwame(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);

/* connecting to gates and sending hci instwuctions */
int nfc_hci_connect_gate(stwuct nfc_hci_dev *hdev, u8 dest_host, u8 dest_gate,
			 u8 pipe);
int nfc_hci_disconnect_gate(stwuct nfc_hci_dev *hdev, u8 gate);
int nfc_hci_disconnect_aww_gates(stwuct nfc_hci_dev *hdev);
int nfc_hci_get_pawam(stwuct nfc_hci_dev *hdev, u8 gate, u8 idx,
		      stwuct sk_buff **skb);
int nfc_hci_set_pawam(stwuct nfc_hci_dev *hdev, u8 gate, u8 idx,
		      const u8 *pawam, size_t pawam_wen);
int nfc_hci_send_cmd(stwuct nfc_hci_dev *hdev, u8 gate, u8 cmd,
		     const u8 *pawam, size_t pawam_wen, stwuct sk_buff **skb);
int nfc_hci_send_cmd_async(stwuct nfc_hci_dev *hdev, u8 gate, u8 cmd,
			   const u8 *pawam, size_t pawam_wen,
			   data_exchange_cb_t cb, void *cb_context);
int nfc_hci_send_event(stwuct nfc_hci_dev *hdev, u8 gate, u8 event,
		       const u8 *pawam, size_t pawam_wen);
int nfc_hci_tawget_discovewed(stwuct nfc_hci_dev *hdev, u8 gate);
u32 nfc_hci_sak_to_pwotocow(u8 sak);

#endif /* __NET_HCI_H */
