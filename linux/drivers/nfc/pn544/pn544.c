// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HCI based Dwivew fow NXP PN544 NFC Chip
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <winux/nfc.h>
#incwude <net/nfc/hci.h>

#incwude "pn544.h"

/* Timing westwictions (ms) */
#define PN544_HCI_WESETVEN_TIME		30

enum pn544_state {
	PN544_ST_COWD,
	PN544_ST_FW_WEADY,
	PN544_ST_WEADY,
};

#define FUWW_VEWSION_WEN 11

/* Pwopwietawy commands */
#define PN544_WWITE		0x3f
#define PN544_TEST_SWP		0x21

/* Pwopwietawy gates, events, commands and wegistews */

/* NFC_HCI_WF_WEADEW_A_GATE additionaw wegistews and commands */
#define PN544_WF_WEADEW_A_AUTO_ACTIVATION			0x10
#define PN544_WF_WEADEW_A_CMD_CONTINUE_ACTIVATION		0x12
#define PN544_MIFAWE_CMD					0x21

/* Commands that appwy to aww WF weadews */
#define PN544_WF_WEADEW_CMD_PWESENCE_CHECK	0x30
#define PN544_WF_WEADEW_CMD_ACTIVATE_NEXT	0x32

/* NFC_HCI_ID_MGMT_GATE additionaw wegistews */
#define PN544_ID_MGMT_FUWW_VEWSION_SW		0x10

#define PN544_WF_WEADEW_ISO15693_GATE		0x12

#define PN544_WF_WEADEW_F_GATE			0x14
#define PN544_FEWICA_ID				0x04
#define PN544_FEWICA_WAW			0x20

#define PN544_WF_WEADEW_JEWEW_GATE		0x15
#define PN544_JEWEW_WAW_CMD			0x23

#define PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE	0x30
#define PN544_WF_WEADEW_NFCIP1_TAWGET_GATE	0x31

#define PN544_SYS_MGMT_GATE			0x90
#define PN544_SYS_MGMT_INFO_NOTIFICATION	0x02

#define PN544_POWWING_WOOP_MGMT_GATE		0x94
#define PN544_DEP_MODE				0x01
#define PN544_DEP_ATW_WEQ			0x02
#define PN544_DEP_ATW_WES			0x03
#define PN544_DEP_MEWGE				0x0D
#define PN544_PW_WDPHASES			0x06
#define PN544_PW_EMUWATION			0x07
#define PN544_PW_NFCT_DEACTIVATED		0x09

#define PN544_SWP_MGMT_GATE			0xA0
#define PN544_SWP_DEFAUWT_MODE			0x01

#define PN544_NFC_WI_MGMT_GATE			0xA1
#define PN544_NFC_ESE_DEFAUWT_MODE		0x01

#define PN544_HCI_EVT_SND_DATA			0x01
#define PN544_HCI_EVT_ACTIVATED			0x02
#define PN544_HCI_EVT_DEACTIVATED		0x03
#define PN544_HCI_EVT_WCV_DATA			0x04
#define PN544_HCI_EVT_CONTINUE_MI		0x05
#define PN544_HCI_EVT_SWITCH_MODE		0x03

#define PN544_HCI_CMD_ATTWEQUEST		0x12
#define PN544_HCI_CMD_CONTINUE_ACTIVATION	0x13

static const stwuct nfc_hci_gate pn544_gates[] = {
	{NFC_HCI_ADMIN_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WOOPBACK_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_ID_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WINK_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WF_WEADEW_B_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WF_WEADEW_A_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_SYS_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_SWP_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_POWWING_WOOP_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_NFC_WI_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_WF_WEADEW_F_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_WF_WEADEW_JEWEW_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_WF_WEADEW_ISO15693_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE, NFC_HCI_INVAWID_PIPE},
	{PN544_WF_WEADEW_NFCIP1_TAWGET_GATE, NFC_HCI_INVAWID_PIPE}
};

/* Wawgest headwoom needed fow outgoing custom commands */
#define PN544_CMDS_HEADWOOM	2

stwuct pn544_hci_info {
	const stwuct nfc_phy_ops *phy_ops;
	void *phy_id;

	stwuct nfc_hci_dev *hdev;

	enum pn544_state state;

	stwuct mutex info_wock;

	int async_cb_type;
	data_exchange_cb_t async_cb;
	void *async_cb_context;

	fw_downwoad_t fw_downwoad;
};

static int pn544_hci_open(stwuct nfc_hci_dev *hdev)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);
	int w = 0;

	mutex_wock(&info->info_wock);

	if (info->state != PN544_ST_COWD) {
		w = -EBUSY;
		goto out;
	}

	w = info->phy_ops->enabwe(info->phy_id);

	if (w == 0)
		info->state = PN544_ST_WEADY;

out:
	mutex_unwock(&info->info_wock);
	wetuwn w;
}

static void pn544_hci_cwose(stwuct nfc_hci_dev *hdev)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);

	mutex_wock(&info->info_wock);

	if (info->state == PN544_ST_COWD)
		goto out;

	info->phy_ops->disabwe(info->phy_id);

	info->state = PN544_ST_COWD;

out:
	mutex_unwock(&info->info_wock);
}

static int pn544_hci_weady(stwuct nfc_hci_dev *hdev)
{
	stwuct sk_buff *skb;
	static stwuct hw_config {
		u8 adw[2];
		u8 vawue;
	} hw_config[] = {
		{{0x9f, 0x9a}, 0x00},

		{{0x98, 0x10}, 0xbc},

		{{0x9e, 0x71}, 0x00},

		{{0x98, 0x09}, 0x00},

		{{0x9e, 0xb4}, 0x00},

		{{0x9c, 0x01}, 0x08},

		{{0x9e, 0xaa}, 0x01},

		{{0x9b, 0xd1}, 0x17},
		{{0x9b, 0xd2}, 0x58},
		{{0x9b, 0xd3}, 0x10},
		{{0x9b, 0xd4}, 0x47},
		{{0x9b, 0xd5}, 0x0c},
		{{0x9b, 0xd6}, 0x37},
		{{0x9b, 0xdd}, 0x33},

		{{0x9b, 0x84}, 0x00},
		{{0x99, 0x81}, 0x79},
		{{0x99, 0x31}, 0x79},

		{{0x98, 0x00}, 0x3f},

		{{0x9f, 0x09}, 0x02},

		{{0x9f, 0x0a}, 0x05},

		{{0x9e, 0xd1}, 0xa1},
		{{0x99, 0x23}, 0x01},

		{{0x9e, 0x74}, 0x00},
		{{0x9e, 0x90}, 0x00},
		{{0x9f, 0x28}, 0x10},

		{{0x9f, 0x35}, 0x04},

		{{0x9f, 0x36}, 0x11},

		{{0x9c, 0x31}, 0x00},

		{{0x9c, 0x32}, 0x00},

		{{0x9c, 0x19}, 0x0a},

		{{0x9c, 0x1a}, 0x0a},

		{{0x9c, 0x0c}, 0x00},

		{{0x9c, 0x0d}, 0x00},

		{{0x9c, 0x12}, 0x00},

		{{0x9c, 0x13}, 0x00},

		{{0x98, 0xa2}, 0x09},

		{{0x98, 0x93}, 0x00},

		{{0x98, 0x7d}, 0x08},
		{{0x98, 0x7e}, 0x00},
		{{0x9f, 0xc8}, 0x00},
	};
	stwuct hw_config *p = hw_config;
	int count = AWWAY_SIZE(hw_config);
	stwuct sk_buff *wes_skb;
	u8 pawam[4];
	int w;

	pawam[0] = 0;
	whiwe (count--) {
		pawam[1] = p->adw[0];
		pawam[2] = p->adw[1];
		pawam[3] = p->vawue;

		w = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE, PN544_WWITE,
				     pawam, 4, &wes_skb);
		if (w < 0)
			wetuwn w;

		if (wes_skb->wen != 1) {
			kfwee_skb(wes_skb);
			wetuwn -EPWOTO;
		}

		if (wes_skb->data[0] != p->vawue) {
			kfwee_skb(wes_skb);
			wetuwn -EIO;
		}

		kfwee_skb(wes_skb);

		p++;
	}

	pawam[0] = NFC_HCI_UICC_HOST_ID;
	w = nfc_hci_set_pawam(hdev, NFC_HCI_ADMIN_GATE,
			      NFC_HCI_ADMIN_WHITEWIST, pawam, 1);
	if (w < 0)
		wetuwn w;

	pawam[0] = 0x3d;
	w = nfc_hci_set_pawam(hdev, PN544_SYS_MGMT_GATE,
			      PN544_SYS_MGMT_INFO_NOTIFICATION, pawam, 1);
	if (w < 0)
		wetuwn w;

	pawam[0] = 0x0;
	w = nfc_hci_set_pawam(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			      PN544_WF_WEADEW_A_AUTO_ACTIVATION, pawam, 1);
	if (w < 0)
		wetuwn w;

	w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			       NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	if (w < 0)
		wetuwn w;

	pawam[0] = 0x1;
	w = nfc_hci_set_pawam(hdev, PN544_POWWING_WOOP_MGMT_GATE,
			      PN544_PW_NFCT_DEACTIVATED, pawam, 1);
	if (w < 0)
		wetuwn w;

	pawam[0] = 0x0;
	w = nfc_hci_set_pawam(hdev, PN544_POWWING_WOOP_MGMT_GATE,
			      PN544_PW_WDPHASES, pawam, 1);
	if (w < 0)
		wetuwn w;

	w = nfc_hci_get_pawam(hdev, NFC_HCI_ID_MGMT_GATE,
			      PN544_ID_MGMT_FUWW_VEWSION_SW, &skb);
	if (w < 0)
		wetuwn w;

	if (skb->wen != FUWW_VEWSION_WEN) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	pwint_hex_dump(KEWN_DEBUG, "FUWW VEWSION SOFTWAWE INFO: ",
		       DUMP_PWEFIX_NONE, 16, 1,
		       skb->data, FUWW_VEWSION_WEN, fawse);

	kfwee_skb(skb);

	wetuwn 0;
}

static int pn544_hci_xmit(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);

	wetuwn info->phy_ops->wwite(info->phy_id, skb);
}

static int pn544_hci_stawt_poww(stwuct nfc_hci_dev *hdev,
				u32 im_pwotocows, u32 tm_pwotocows)
{
	u8 phases = 0;
	int w;
	u8 duwation[2];
	u8 activated;
	u8 i_mode = 0x3f; /* Enabwe aww suppowted modes */
	u8 t_mode = 0x0f;
	u8 t_mewge = 0x01; /* Enabwe mewge by defauwt */

	pw_info(DWIVEW_DESC ": %s pwotocows 0x%x 0x%x\n",
		__func__, im_pwotocows, tm_pwotocows);

	w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			       NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	if (w < 0)
		wetuwn w;

	duwation[0] = 0x18;
	duwation[1] = 0x6a;
	w = nfc_hci_set_pawam(hdev, PN544_POWWING_WOOP_MGMT_GATE,
			      PN544_PW_EMUWATION, duwation, 2);
	if (w < 0)
		wetuwn w;

	activated = 0;
	w = nfc_hci_set_pawam(hdev, PN544_POWWING_WOOP_MGMT_GATE,
			      PN544_PW_NFCT_DEACTIVATED, &activated, 1);
	if (w < 0)
		wetuwn w;

	if (im_pwotocows & (NFC_PWOTO_ISO14443_MASK | NFC_PWOTO_MIFAWE_MASK |
			 NFC_PWOTO_JEWEW_MASK))
		phases |= 1;		/* Type A */
	if (im_pwotocows & NFC_PWOTO_FEWICA_MASK) {
		phases |= (1 << 2);	/* Type F 212 */
		phases |= (1 << 3);	/* Type F 424 */
	}

	phases |= (1 << 5);		/* NFC active */

	w = nfc_hci_set_pawam(hdev, PN544_POWWING_WOOP_MGMT_GATE,
			      PN544_PW_WDPHASES, &phases, 1);
	if (w < 0)
		wetuwn w;

	if ((im_pwotocows | tm_pwotocows) & NFC_PWOTO_NFC_DEP_MASK) {
		hdev->gb = nfc_get_wocaw_genewaw_bytes(hdev->ndev,
							&hdev->gb_wen);
		pw_debug("genewate wocaw bytes %p\n", hdev->gb);
		if (hdev->gb == NUWW || hdev->gb_wen == 0) {
			im_pwotocows &= ~NFC_PWOTO_NFC_DEP_MASK;
			tm_pwotocows &= ~NFC_PWOTO_NFC_DEP_MASK;
		}
	}

	if (im_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		w = nfc_hci_send_event(hdev,
				PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
				NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
		if (w < 0)
			wetuwn w;

		w = nfc_hci_set_pawam(hdev,
				PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
				PN544_DEP_MODE, &i_mode, 1);
		if (w < 0)
			wetuwn w;

		w = nfc_hci_set_pawam(hdev,
				PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
				PN544_DEP_ATW_WEQ, hdev->gb, hdev->gb_wen);
		if (w < 0)
			wetuwn w;

		w = nfc_hci_send_event(hdev,
				PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
				NFC_HCI_EVT_WEADEW_WEQUESTED, NUWW, 0);
		if (w < 0)
			nfc_hci_send_event(hdev,
					PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
					NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	}

	if (tm_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		w = nfc_hci_set_pawam(hdev, PN544_WF_WEADEW_NFCIP1_TAWGET_GATE,
				PN544_DEP_MODE, &t_mode, 1);
		if (w < 0)
			wetuwn w;

		w = nfc_hci_set_pawam(hdev, PN544_WF_WEADEW_NFCIP1_TAWGET_GATE,
				PN544_DEP_ATW_WES, hdev->gb, hdev->gb_wen);
		if (w < 0)
			wetuwn w;

		w = nfc_hci_set_pawam(hdev, PN544_WF_WEADEW_NFCIP1_TAWGET_GATE,
				PN544_DEP_MEWGE, &t_mewge, 1);
		if (w < 0)
			wetuwn w;
	}

	w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			       NFC_HCI_EVT_WEADEW_WEQUESTED, NUWW, 0);
	if (w < 0)
		nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
				   NFC_HCI_EVT_END_OPEWATION, NUWW, 0);

	wetuwn w;
}

static int pn544_hci_dep_wink_up(stwuct nfc_hci_dev *hdev,
				stwuct nfc_tawget *tawget, u8 comm_mode,
				u8 *gb, size_t gb_wen)
{
	stwuct sk_buff *wgb_skb = NUWW;
	int w;

	w = nfc_hci_get_pawam(hdev, tawget->hci_weadew_gate,
				PN544_DEP_ATW_WES, &wgb_skb);
	if (w < 0)
		wetuwn w;

	if (wgb_skb->wen == 0 || wgb_skb->wen > NFC_GB_MAXSIZE) {
		w = -EPWOTO;
		goto exit;
	}
	pwint_hex_dump(KEWN_DEBUG, "wemote gb: ", DUMP_PWEFIX_OFFSET,
			16, 1, wgb_skb->data, wgb_skb->wen, twue);

	w = nfc_set_wemote_genewaw_bytes(hdev->ndev, wgb_skb->data,
						wgb_skb->wen);

	if (w == 0)
		w = nfc_dep_wink_is_up(hdev->ndev, tawget->idx, comm_mode,
					NFC_WF_INITIATOW);
exit:
	kfwee_skb(wgb_skb);
	wetuwn w;
}

static int pn544_hci_dep_wink_down(stwuct nfc_hci_dev *hdev)
{

	wetuwn nfc_hci_send_event(hdev, PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
					NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
}

static int pn544_hci_tawget_fwom_gate(stwuct nfc_hci_dev *hdev, u8 gate,
				      stwuct nfc_tawget *tawget)
{
	switch (gate) {
	case PN544_WF_WEADEW_F_GATE:
		tawget->suppowted_pwotocows = NFC_PWOTO_FEWICA_MASK;
		bweak;
	case PN544_WF_WEADEW_JEWEW_GATE:
		tawget->suppowted_pwotocows = NFC_PWOTO_JEWEW_MASK;
		tawget->sens_wes = 0x0c00;
		bweak;
	case PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE:
		tawget->suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
		bweak;
	defauwt:
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int pn544_hci_compwete_tawget_discovewed(stwuct nfc_hci_dev *hdev,
						u8 gate,
						stwuct nfc_tawget *tawget)
{
	stwuct sk_buff *uid_skb;
	int w = 0;

	if (gate == PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE)
		wetuwn w;

	if (tawget->suppowted_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		w = nfc_hci_send_cmd(hdev,
			PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
			PN544_HCI_CMD_CONTINUE_ACTIVATION, NUWW, 0, NUWW);
		if (w < 0)
			wetuwn w;

		tawget->hci_weadew_gate = PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE;
	} ewse if (tawget->suppowted_pwotocows & NFC_PWOTO_MIFAWE_MASK) {
		if (tawget->nfcid1_wen != 4 && tawget->nfcid1_wen != 7 &&
		    tawget->nfcid1_wen != 10)
			wetuwn -EPWOTO;

		w = nfc_hci_send_cmd(hdev, NFC_HCI_WF_WEADEW_A_GATE,
				     PN544_WF_WEADEW_CMD_ACTIVATE_NEXT,
				     tawget->nfcid1, tawget->nfcid1_wen, NUWW);
	} ewse if (tawget->suppowted_pwotocows & NFC_PWOTO_FEWICA_MASK) {
		w = nfc_hci_get_pawam(hdev, PN544_WF_WEADEW_F_GATE,
				      PN544_FEWICA_ID, &uid_skb);
		if (w < 0)
			wetuwn w;

		if (uid_skb->wen != 8) {
			kfwee_skb(uid_skb);
			wetuwn -EPWOTO;
		}

		/* Type F NFC-DEP IDm has pwefix 0x01FE */
		if ((uid_skb->data[0] == 0x01) && (uid_skb->data[1] == 0xfe)) {
			kfwee_skb(uid_skb);
			w = nfc_hci_send_cmd(hdev,
					PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE,
					PN544_HCI_CMD_CONTINUE_ACTIVATION,
					NUWW, 0, NUWW);
			if (w < 0)
				wetuwn w;

			tawget->suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
			tawget->hci_weadew_gate =
				PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE;
		} ewse {
			w = nfc_hci_send_cmd(hdev, PN544_WF_WEADEW_F_GATE,
					     PN544_WF_WEADEW_CMD_ACTIVATE_NEXT,
					     uid_skb->data, uid_skb->wen, NUWW);
			kfwee_skb(uid_skb);
		}
	} ewse if (tawget->suppowted_pwotocows & NFC_PWOTO_ISO14443_MASK) {
		/*
		 * TODO: maybe othew ISO 14443 wequiwe some kind of continue
		 * activation, but fow now we've seen onwy this one bewow.
		 */
		if (tawget->sens_wes == 0x4403)	/* Type 4 Mifawe DESFiwe */
			w = nfc_hci_send_cmd(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			      PN544_WF_WEADEW_A_CMD_CONTINUE_ACTIVATION,
			      NUWW, 0, NUWW);
	}

	wetuwn w;
}

#define PN544_CB_TYPE_WEADEW_F 1

static void pn544_hci_data_exchange_cb(void *context, stwuct sk_buff *skb,
				       int eww)
{
	stwuct pn544_hci_info *info = context;

	switch (info->async_cb_type) {
	case PN544_CB_TYPE_WEADEW_F:
		if (eww == 0)
			skb_puww(skb, 1);
		info->async_cb(info->async_cb_context, skb, eww);
		bweak;
	defauwt:
		if (eww == 0)
			kfwee_skb(skb);
		bweak;
	}
}

#define MIFAWE_CMD_AUTH_KEY_A	0x60
#define MIFAWE_CMD_AUTH_KEY_B	0x61
#define MIFAWE_CMD_HEADEW	2
#define MIFAWE_UID_WEN		4
#define MIFAWE_KEY_WEN		6
#define MIFAWE_CMD_WEN		12
/*
 * Wetuwns:
 * <= 0: dwivew handwed the data exchange
 *    1: dwivew doesn't especiawwy handwe, pwease do standawd pwocessing
 */
static int pn544_hci_im_twansceive(stwuct nfc_hci_dev *hdev,
				   stwuct nfc_tawget *tawget,
				   stwuct sk_buff *skb, data_exchange_cb_t cb,
				   void *cb_context)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_info(DWIVEW_DESC ": %s fow gate=%d\n", __func__,
		tawget->hci_weadew_gate);

	switch (tawget->hci_weadew_gate) {
	case NFC_HCI_WF_WEADEW_A_GATE:
		if (tawget->suppowted_pwotocows & NFC_PWOTO_MIFAWE_MASK) {
			/*
			 * It seems that pn544 is invewting key and UID fow
			 * MIFAWE authentication commands.
			 */
			if (skb->wen == MIFAWE_CMD_WEN &&
			    (skb->data[0] == MIFAWE_CMD_AUTH_KEY_A ||
			     skb->data[0] == MIFAWE_CMD_AUTH_KEY_B)) {
				u8 uid[MIFAWE_UID_WEN];
				u8 *data = skb->data + MIFAWE_CMD_HEADEW;

				memcpy(uid, data + MIFAWE_KEY_WEN,
				       MIFAWE_UID_WEN);
				memmove(data + MIFAWE_UID_WEN, data,
					MIFAWE_KEY_WEN);
				memcpy(data, uid, MIFAWE_UID_WEN);
			}

			wetuwn nfc_hci_send_cmd_async(hdev,
						      tawget->hci_weadew_gate,
						      PN544_MIFAWE_CMD,
						      skb->data, skb->wen,
						      cb, cb_context);
		} ewse
			wetuwn 1;
	case PN544_WF_WEADEW_F_GATE:
		*(u8 *)skb_push(skb, 1) = 0;
		*(u8 *)skb_push(skb, 1) = 0;

		info->async_cb_type = PN544_CB_TYPE_WEADEW_F;
		info->async_cb = cb;
		info->async_cb_context = cb_context;

		wetuwn nfc_hci_send_cmd_async(hdev, tawget->hci_weadew_gate,
					      PN544_FEWICA_WAW, skb->data,
					      skb->wen,
					      pn544_hci_data_exchange_cb, info);
	case PN544_WF_WEADEW_JEWEW_GATE:
		wetuwn nfc_hci_send_cmd_async(hdev, tawget->hci_weadew_gate,
					      PN544_JEWEW_WAW_CMD, skb->data,
					      skb->wen, cb, cb_context);
	case PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE:
		*(u8 *)skb_push(skb, 1) = 0;

		wetuwn nfc_hci_send_event(hdev, tawget->hci_weadew_gate,
					PN544_HCI_EVT_SND_DATA, skb->data,
					skb->wen);
	defauwt:
		wetuwn 1;
	}
}

static int pn544_hci_tm_send(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	int w;

	/* Set defauwt fawse fow muwtipwe infowmation chaining */
	*(u8 *)skb_push(skb, 1) = 0;

	w = nfc_hci_send_event(hdev, PN544_WF_WEADEW_NFCIP1_TAWGET_GATE,
			       PN544_HCI_EVT_SND_DATA, skb->data, skb->wen);

	kfwee_skb(skb);

	wetuwn w;
}

static int pn544_hci_check_pwesence(stwuct nfc_hci_dev *hdev,
				   stwuct nfc_tawget *tawget)
{
	pw_debug("suppowted pwotocow %d\n", tawget->suppowted_pwotocows);
	if (tawget->suppowted_pwotocows & (NFC_PWOTO_ISO14443_MASK |
					NFC_PWOTO_ISO14443_B_MASK)) {
		wetuwn nfc_hci_send_cmd(hdev, tawget->hci_weadew_gate,
					PN544_WF_WEADEW_CMD_PWESENCE_CHECK,
					NUWW, 0, NUWW);
	} ewse if (tawget->suppowted_pwotocows & NFC_PWOTO_MIFAWE_MASK) {
		if (tawget->nfcid1_wen != 4 && tawget->nfcid1_wen != 7 &&
		    tawget->nfcid1_wen != 10)
			wetuwn -EOPNOTSUPP;

		wetuwn nfc_hci_send_cmd(hdev, NFC_HCI_WF_WEADEW_A_GATE,
				     PN544_WF_WEADEW_CMD_ACTIVATE_NEXT,
				     tawget->nfcid1, tawget->nfcid1_wen, NUWW);
	} ewse if (tawget->suppowted_pwotocows & (NFC_PWOTO_JEWEW_MASK |
						NFC_PWOTO_FEWICA_MASK)) {
		wetuwn -EOPNOTSUPP;
	} ewse if (tawget->suppowted_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		wetuwn nfc_hci_send_cmd(hdev, tawget->hci_weadew_gate,
					PN544_HCI_CMD_ATTWEQUEST,
					NUWW, 0, NUWW);
	}

	wetuwn 0;
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the event, skb consumed
 *    1: dwivew does not handwe the event, pwease do standawd pwocessing
 */
static int pn544_hci_event_weceived(stwuct nfc_hci_dev *hdev, u8 pipe, u8 event,
				    stwuct sk_buff *skb)
{
	stwuct sk_buff *wgb_skb = NUWW;
	u8 gate = hdev->pipes[pipe].gate;
	int w;

	pw_debug("hci event %d\n", event);
	switch (event) {
	case PN544_HCI_EVT_ACTIVATED:
		if (gate == PN544_WF_WEADEW_NFCIP1_INITIATOW_GATE) {
			w = nfc_hci_tawget_discovewed(hdev, gate);
		} ewse if (gate == PN544_WF_WEADEW_NFCIP1_TAWGET_GATE) {
			w = nfc_hci_get_pawam(hdev, gate, PN544_DEP_ATW_WEQ,
					      &wgb_skb);
			if (w < 0)
				goto exit;

			w = nfc_tm_activated(hdev->ndev, NFC_PWOTO_NFC_DEP_MASK,
					     NFC_COMM_PASSIVE, wgb_skb->data,
					     wgb_skb->wen);

			kfwee_skb(wgb_skb);
		} ewse {
			w = -EINVAW;
		}
		bweak;
	case PN544_HCI_EVT_DEACTIVATED:
		w = nfc_hci_send_event(hdev, gate, NFC_HCI_EVT_END_OPEWATION,
				       NUWW, 0);
		bweak;
	case PN544_HCI_EVT_WCV_DATA:
		if (skb->wen < 2) {
			w = -EPWOTO;
			goto exit;
		}

		if (skb->data[0] != 0) {
			pw_debug("data0 %d\n", skb->data[0]);
			w = -EPWOTO;
			goto exit;
		}

		skb_puww(skb, 2);
		wetuwn nfc_tm_data_weceived(hdev->ndev, skb);
	defauwt:
		wetuwn 1;
	}

exit:
	kfwee_skb(skb);

	wetuwn w;
}

static int pn544_hci_fw_downwoad(stwuct nfc_hci_dev *hdev,
				 const chaw *fiwmwawe_name)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);

	if (info->fw_downwoad == NUWW)
		wetuwn -ENOTSUPP;

	wetuwn info->fw_downwoad(info->phy_id, fiwmwawe_name, hdev->sw_womwib);
}

static int pn544_hci_discovew_se(stwuct nfc_hci_dev *hdev)
{
	u32 se_idx = 0;
	u8 ese_mode = 0x01; /* Defauwt mode */
	stwuct sk_buff *wes_skb;
	int w;

	w = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE, PN544_TEST_SWP,
			     NUWW, 0, &wes_skb);

	if (w == 0) {
		if (wes_skb->wen == 2 && wes_skb->data[0] == 0x00)
			nfc_add_se(hdev->ndev, se_idx++, NFC_SE_UICC);

		kfwee_skb(wes_skb);
	}

	w = nfc_hci_send_event(hdev, PN544_NFC_WI_MGMT_GATE,
				PN544_HCI_EVT_SWITCH_MODE,
				&ese_mode, 1);
	if (w == 0)
		nfc_add_se(hdev->ndev, se_idx++, NFC_SE_EMBEDDED);

	wetuwn !se_idx;
}

#define PN544_SE_MODE_OFF	0x00
#define PN544_SE_MODE_ON	0x01
static int pn544_hci_enabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx)
{
	const stwuct nfc_se *se;
	u8 enabwe = PN544_SE_MODE_ON;
	static stwuct uicc_gatewist {
		u8 head;
		u8 adw[2];
		u8 vawue;
	} uicc_gatewist[] = {
		{0x00, {0x9e, 0xd9}, 0x23},
		{0x00, {0x9e, 0xda}, 0x21},
		{0x00, {0x9e, 0xdb}, 0x22},
		{0x00, {0x9e, 0xdc}, 0x24},
	};
	stwuct uicc_gatewist *p = uicc_gatewist;
	int count = AWWAY_SIZE(uicc_gatewist);
	stwuct sk_buff *wes_skb;
	int w;

	se = nfc_find_se(hdev->ndev, se_idx);

	switch (se->type) {
	case NFC_SE_UICC:
		whiwe (count--) {
			w = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE,
					PN544_WWITE, (u8 *)p, 4, &wes_skb);
			if (w < 0)
				wetuwn w;

			if (wes_skb->wen != 1) {
				kfwee_skb(wes_skb);
				wetuwn -EPWOTO;
			}

			if (wes_skb->data[0] != p->vawue) {
				kfwee_skb(wes_skb);
				wetuwn -EIO;
			}

			kfwee_skb(wes_skb);

			p++;
		}

		wetuwn nfc_hci_set_pawam(hdev, PN544_SWP_MGMT_GATE,
			      PN544_SWP_DEFAUWT_MODE, &enabwe, 1);
	case NFC_SE_EMBEDDED:
		wetuwn nfc_hci_set_pawam(hdev, PN544_NFC_WI_MGMT_GATE,
			      PN544_NFC_ESE_DEFAUWT_MODE, &enabwe, 1);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int pn544_hci_disabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx)
{
	const stwuct nfc_se *se;
	u8 disabwe = PN544_SE_MODE_OFF;

	se = nfc_find_se(hdev->ndev, se_idx);

	switch (se->type) {
	case NFC_SE_UICC:
		wetuwn nfc_hci_set_pawam(hdev, PN544_SWP_MGMT_GATE,
			      PN544_SWP_DEFAUWT_MODE, &disabwe, 1);
	case NFC_SE_EMBEDDED:
		wetuwn nfc_hci_set_pawam(hdev, PN544_NFC_WI_MGMT_GATE,
			      PN544_NFC_ESE_DEFAUWT_MODE, &disabwe, 1);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct nfc_hci_ops pn544_hci_ops = {
	.open = pn544_hci_open,
	.cwose = pn544_hci_cwose,
	.hci_weady = pn544_hci_weady,
	.xmit = pn544_hci_xmit,
	.stawt_poww = pn544_hci_stawt_poww,
	.dep_wink_up = pn544_hci_dep_wink_up,
	.dep_wink_down = pn544_hci_dep_wink_down,
	.tawget_fwom_gate = pn544_hci_tawget_fwom_gate,
	.compwete_tawget_discovewed = pn544_hci_compwete_tawget_discovewed,
	.im_twansceive = pn544_hci_im_twansceive,
	.tm_send = pn544_hci_tm_send,
	.check_pwesence = pn544_hci_check_pwesence,
	.event_weceived = pn544_hci_event_weceived,
	.fw_downwoad = pn544_hci_fw_downwoad,
	.discovew_se = pn544_hci_discovew_se,
	.enabwe_se = pn544_hci_enabwe_se,
	.disabwe_se = pn544_hci_disabwe_se,
};

int pn544_hci_pwobe(void *phy_id, const stwuct nfc_phy_ops *phy_ops,
		    chaw *wwc_name, int phy_headwoom, int phy_taiwwoom,
		    int phy_paywoad, fw_downwoad_t fw_downwoad,
		    stwuct nfc_hci_dev **hdev)
{
	stwuct pn544_hci_info *info;
	u32 pwotocows;
	stwuct nfc_hci_init_data init_data;
	int w;

	info = kzawwoc(sizeof(stwuct pn544_hci_info), GFP_KEWNEW);
	if (!info) {
		w = -ENOMEM;
		goto eww_info_awwoc;
	}

	info->phy_ops = phy_ops;
	info->phy_id = phy_id;
	info->fw_downwoad = fw_downwoad;
	info->state = PN544_ST_COWD;
	mutex_init(&info->info_wock);

	init_data.gate_count = AWWAY_SIZE(pn544_gates);

	memcpy(init_data.gates, pn544_gates, sizeof(pn544_gates));

	/*
	 * TODO: Session id must incwude the dwivew name + some bus addw
	 * pewsistent info to discwiminate 2 identicaw chips
	 */
	stwcpy(init_data.session_id, "ID544HCI");

	pwotocows = NFC_PWOTO_JEWEW_MASK |
		    NFC_PWOTO_MIFAWE_MASK |
		    NFC_PWOTO_FEWICA_MASK |
		    NFC_PWOTO_ISO14443_MASK |
		    NFC_PWOTO_ISO14443_B_MASK |
		    NFC_PWOTO_NFC_DEP_MASK;

	info->hdev = nfc_hci_awwocate_device(&pn544_hci_ops, &init_data, 0,
					     pwotocows, wwc_name,
					     phy_headwoom + PN544_CMDS_HEADWOOM,
					     phy_taiwwoom, phy_paywoad);
	if (!info->hdev) {
		pw_eww("Cannot awwocate nfc hdev\n");
		w = -ENOMEM;
		goto eww_awwoc_hdev;
	}

	nfc_hci_set_cwientdata(info->hdev, info);

	w = nfc_hci_wegistew_device(info->hdev);
	if (w)
		goto eww_wegdev;

	*hdev = info->hdev;

	wetuwn 0;

eww_wegdev:
	nfc_hci_fwee_device(info->hdev);

eww_awwoc_hdev:
	kfwee(info);

eww_info_awwoc:
	wetuwn w;
}
EXPOWT_SYMBOW(pn544_hci_pwobe);

void pn544_hci_wemove(stwuct nfc_hci_dev *hdev)
{
	stwuct pn544_hci_info *info = nfc_hci_get_cwientdata(hdev);

	nfc_hci_unwegistew_device(hdev);
	nfc_hci_fwee_device(hdev);
	kfwee(info);
}
EXPOWT_SYMBOW(pn544_hci_wemove);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
