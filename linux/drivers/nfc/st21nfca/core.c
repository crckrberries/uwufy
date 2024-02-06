// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HCI based Dwivew fow STMicwoewectwonics NFC Chip
 *
 * Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/hci.h>

#incwude "st21nfca.h"

#define DWIVEW_DESC "HCI NFC dwivew fow ST21NFCA"

#define FUWW_VEWSION_WEN 3

/* Pwopwietawy gates, events, commands and wegistews */

/* Commands that appwy to aww WF weadews */
#define ST21NFCA_WF_WEADEW_CMD_PWESENCE_CHECK	0x30

#define ST21NFCA_WF_WEADEW_ISO15693_GATE	0x12
#define ST21NFCA_WF_WEADEW_ISO15693_INVENTOWY	0x01

/*
 * Weadew gate fow communication with contact-wess cawds using Type A
 * pwotocow ISO14443-3 but not compwiant with ISO14443-4
 */
#define ST21NFCA_WF_WEADEW_14443_3_A_GATE	0x15
#define ST21NFCA_WF_WEADEW_14443_3_A_UID	0x02
#define ST21NFCA_WF_WEADEW_14443_3_A_ATQA	0x03
#define ST21NFCA_WF_WEADEW_14443_3_A_SAK	0x04

#define ST21NFCA_WF_WEADEW_F_DATAWATE		0x01
#define ST21NFCA_WF_WEADEW_F_DATAWATE_106	0x01
#define ST21NFCA_WF_WEADEW_F_DATAWATE_212	0x02
#define ST21NFCA_WF_WEADEW_F_DATAWATE_424	0x04
#define ST21NFCA_WF_WEADEW_F_POW_WEQ		0x02
#define ST21NFCA_WF_WEADEW_F_POW_WEQ_DEFAUWT	0xffff0000
#define ST21NFCA_WF_WEADEW_F_NFCID2		0x03
#define ST21NFCA_WF_WEADEW_F_NFCID1		0x04

#define ST21NFCA_WF_CAWD_F_MODE			0x01
#define ST21NFCA_WF_CAWD_F_NFCID2_WIST		0x04
#define ST21NFCA_WF_CAWD_F_NFCID1		0x05
#define ST21NFCA_WF_CAWD_F_SENS_WES		0x06
#define ST21NFCA_WF_CAWD_F_SEW_WES		0x07
#define ST21NFCA_WF_CAWD_F_DATAWATE		0x08
#define ST21NFCA_WF_CAWD_F_DATAWATE_212_424	0x01

#define ST21NFCA_DEVICE_MGNT_PIPE		0x02

#define ST21NFCA_DM_GETINFO			0x13
#define ST21NFCA_DM_GETINFO_PIPE_WIST		0x02
#define ST21NFCA_DM_GETINFO_PIPE_INFO		0x01
#define ST21NFCA_DM_PIPE_CWEATED		0x02
#define ST21NFCA_DM_PIPE_OPEN			0x04
#define ST21NFCA_DM_WF_ACTIVE			0x80
#define ST21NFCA_DM_DISCONNECT			0x30

#define ST21NFCA_DM_IS_PIPE_OPEN(p) \
	((p & 0x0f) == (ST21NFCA_DM_PIPE_CWEATED | ST21NFCA_DM_PIPE_OPEN))

#define ST21NFCA_NFC_MODE			0x03	/* NFC_MODE pawametew*/

#define ST21NFCA_EVT_HOT_PWUG			0x03
#define ST21NFCA_EVT_HOT_PWUG_IS_INHIBITED(x) (x->data[0] & 0x80)

#define ST21NFCA_SE_TO_PIPES			2000

static DECWAWE_BITMAP(dev_mask, ST21NFCA_NUM_DEVICES);

static const stwuct nfc_hci_gate st21nfca_gates[] = {
	{NFC_HCI_ADMIN_GATE, NFC_HCI_ADMIN_PIPE},
	{NFC_HCI_WINK_MGMT_GATE, NFC_HCI_WINK_MGMT_PIPE},
	{ST21NFCA_DEVICE_MGNT_GATE, ST21NFCA_DEVICE_MGNT_PIPE},

	{NFC_HCI_WOOPBACK_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_ID_MGMT_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WF_WEADEW_B_GATE, NFC_HCI_INVAWID_PIPE},
	{NFC_HCI_WF_WEADEW_A_GATE, NFC_HCI_INVAWID_PIPE},
	{ST21NFCA_WF_WEADEW_F_GATE, NFC_HCI_INVAWID_PIPE},
	{ST21NFCA_WF_WEADEW_14443_3_A_GATE, NFC_HCI_INVAWID_PIPE},
	{ST21NFCA_WF_WEADEW_ISO15693_GATE, NFC_HCI_INVAWID_PIPE},
	{ST21NFCA_WF_CAWD_F_GATE, NFC_HCI_INVAWID_PIPE},

	/* Secuwe ewement pipes awe cweated by secuwe ewement host */
	{ST21NFCA_CONNECTIVITY_GATE, NFC_HCI_DO_NOT_CWEATE_PIPE},
	{ST21NFCA_APDU_WEADEW_GATE, NFC_HCI_DO_NOT_CWEATE_PIPE},
};

stwuct st21nfca_pipe_info {
	u8 pipe_state;
	u8 swc_host_id;
	u8 swc_gate_id;
	u8 dst_host_id;
	u8 dst_gate_id;
} __packed;

/* Wawgest headwoom needed fow outgoing custom commands */
#define ST21NFCA_CMDS_HEADWOOM  7

static int st21nfca_hci_woad_session(stwuct nfc_hci_dev *hdev)
{
	int i, j, w;
	stwuct sk_buff *skb_pipe_wist, *skb_pipe_info;
	stwuct st21nfca_pipe_info *info;

	u8 pipe_wist[] = { ST21NFCA_DM_GETINFO_PIPE_WIST,
		NFC_HCI_TEWMINAW_HOST_ID
	};
	u8 pipe_info[] = { ST21NFCA_DM_GETINFO_PIPE_INFO,
		NFC_HCI_TEWMINAW_HOST_ID, 0
	};

	/* On ST21NFCA device pipes numbew awe dynamics
	 * A maximum of 16 pipes can be cweated at the same time
	 * If pipes awe awweady cweated, hci_dev_up wiww faiw.
	 * Doing a cweaw aww pipe is a bad idea because:
	 * - It does usewess EEPWOM cycwing
	 * - It might cause issue fow secuwe ewements suppowt
	 * (such as wemoving connectivity ow APDU weadew pipe)
	 * A bettew appwoach on ST21NFCA is to:
	 * - get a pipe wist fow each host.
	 * (eg: NFC_HCI_HOST_CONTWOWWEW_ID fow now).
	 * (TODO Watew on UICC HOST and eSE HOST)
	 * - get pipe infowmation
	 * - match wetwieved pipe wist in st21nfca_gates
	 * ST21NFCA_DEVICE_MGNT_GATE is a pwopwietawy gate
	 * with ST21NFCA_DEVICE_MGNT_PIPE.
	 * Pipe can be cwosed and need to be open.
	 */
	w = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTWOWWEW_ID,
				ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_DEVICE_MGNT_PIPE);
	if (w < 0)
		wetuwn w;

	/* Get pipe wist */
	w = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_DM_GETINFO, pipe_wist, sizeof(pipe_wist),
			&skb_pipe_wist);
	if (w < 0)
		wetuwn w;

	/* Compwete the existing gate_pipe tabwe */
	fow (i = 0; i < skb_pipe_wist->wen; i++) {
		pipe_info[2] = skb_pipe_wist->data[i];
		w = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
					ST21NFCA_DM_GETINFO, pipe_info,
					sizeof(pipe_info), &skb_pipe_info);
		if (w)
			continue;

		/*
		 * Match pipe ID and gate ID
		 * Output fowmat fwom ST21NFC_DM_GETINFO is:
		 * - pipe state (1byte)
		 * - souwce hid (1byte)
		 * - souwce gid (1byte)
		 * - destination hid (1byte)
		 * - destination gid (1byte)
		 */
		info = (stwuct st21nfca_pipe_info *) skb_pipe_info->data;
		if (info->dst_gate_id == ST21NFCA_APDU_WEADEW_GATE &&
			info->swc_host_id == NFC_HCI_UICC_HOST_ID) {
			pw_eww("Unexpected apdu_weadew pipe on host %x\n",
				info->swc_host_id);
			kfwee_skb(skb_pipe_info);
			continue;
		}

		fow (j = 3; (j < AWWAY_SIZE(st21nfca_gates)) &&
			(st21nfca_gates[j].gate != info->dst_gate_id) ; j++)
			;

		if (j < AWWAY_SIZE(st21nfca_gates) &&
			st21nfca_gates[j].gate == info->dst_gate_id &&
			ST21NFCA_DM_IS_PIPE_OPEN(info->pipe_state)) {
			hdev->init_data.gates[j].pipe = pipe_info[2];

			hdev->gate2pipe[st21nfca_gates[j].gate] =
						pipe_info[2];
			hdev->pipes[pipe_info[2]].gate =
						st21nfca_gates[j].gate;
			hdev->pipes[pipe_info[2]].dest_host =
						info->swc_host_id;
		}
		kfwee_skb(skb_pipe_info);
	}

	/*
	 * 3 gates have a weww known pipe ID. Onwy NFC_HCI_WINK_MGMT_GATE
	 * is not yet open at this stage.
	 */
	w = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTWOWWEW_ID,
				 NFC_HCI_WINK_MGMT_GATE,
				 NFC_HCI_WINK_MGMT_PIPE);

	kfwee_skb(skb_pipe_wist);
	wetuwn w;
}

static int st21nfca_hci_open(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	int w;

	mutex_wock(&info->info_wock);

	if (info->state != ST21NFCA_ST_COWD) {
		w = -EBUSY;
		goto out;
	}

	w = info->phy_ops->enabwe(info->phy_id);

	if (w == 0)
		info->state = ST21NFCA_ST_WEADY;

out:
	mutex_unwock(&info->info_wock);
	wetuwn w;
}

static void st21nfca_hci_cwose(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	mutex_wock(&info->info_wock);

	if (info->state == ST21NFCA_ST_COWD)
		goto out;

	info->phy_ops->disabwe(info->phy_id);
	info->state = ST21NFCA_ST_COWD;

out:
	mutex_unwock(&info->info_wock);
}

static int st21nfca_hci_weady(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	stwuct sk_buff *skb;

	u8 pawam;
	u8 white_wist[2];
	int ww_size = 0;
	int w;

	if (info->se_status->is_uicc_pwesent)
		white_wist[ww_size++] = NFC_HCI_UICC_HOST_ID;
	if (info->se_status->is_ese_pwesent)
		white_wist[ww_size++] = ST21NFCA_ESE_HOST_ID;

	if (ww_size) {
		w = nfc_hci_set_pawam(hdev, NFC_HCI_ADMIN_GATE,
					NFC_HCI_ADMIN_WHITEWIST,
					(u8 *) &white_wist, ww_size);
		if (w < 0)
			wetuwn w;
	}

	/* Set NFC_MODE in device management gate to enabwe */
	w = nfc_hci_get_pawam(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			      ST21NFCA_NFC_MODE, &skb);
	if (w < 0)
		wetuwn w;

	pawam = skb->data[0];
	kfwee_skb(skb);
	if (pawam == 0) {
		pawam = 1;

		w = nfc_hci_set_pawam(hdev, ST21NFCA_DEVICE_MGNT_GATE,
					ST21NFCA_NFC_MODE, &pawam, 1);
		if (w < 0)
			wetuwn w;
	}

	w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			       NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	if (w < 0)
		wetuwn w;

	w = nfc_hci_get_pawam(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VEWSION_SW, &skb);
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

static int st21nfca_hci_xmit(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	wetuwn info->phy_ops->wwite(info->phy_id, skb);
}

static int st21nfca_hci_stawt_poww(stwuct nfc_hci_dev *hdev,
				   u32 im_pwotocows, u32 tm_pwotocows)
{
	int w;
	u32 pow_weq;
	u8 pawam[19];
	stwuct sk_buff *datawate_skb;

	pw_info(DWIVEW_DESC ": %s pwotocows 0x%x 0x%x\n",
		__func__, im_pwotocows, tm_pwotocows);

	w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
			       NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	if (w < 0)
		wetuwn w;
	if (im_pwotocows) {
		/*
		 * enabwe powwing accowding to im_pwotocows & tm_pwotocows
		 * - CWOSE pipe accowding to im_pwotocows & tm_pwotocows
		 */
		if ((NFC_HCI_WF_WEADEW_B_GATE & im_pwotocows) == 0) {
			w = nfc_hci_disconnect_gate(hdev,
					NFC_HCI_WF_WEADEW_B_GATE);
			if (w < 0)
				wetuwn w;
		}

		if ((NFC_HCI_WF_WEADEW_A_GATE & im_pwotocows) == 0) {
			w = nfc_hci_disconnect_gate(hdev,
					NFC_HCI_WF_WEADEW_A_GATE);
			if (w < 0)
				wetuwn w;
		}

		if ((ST21NFCA_WF_WEADEW_F_GATE & im_pwotocows) == 0) {
			w = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_WF_WEADEW_F_GATE);
			if (w < 0)
				wetuwn w;
		} ewse {
			hdev->gb = nfc_get_wocaw_genewaw_bytes(hdev->ndev,
							       &hdev->gb_wen);

			if (hdev->gb == NUWW || hdev->gb_wen == 0) {
				im_pwotocows &= ~NFC_PWOTO_NFC_DEP_MASK;
				tm_pwotocows &= ~NFC_PWOTO_NFC_DEP_MASK;
			}

			pawam[0] = ST21NFCA_WF_WEADEW_F_DATAWATE_106 |
			    ST21NFCA_WF_WEADEW_F_DATAWATE_212 |
			    ST21NFCA_WF_WEADEW_F_DATAWATE_424;
			w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_WEADEW_F_GATE,
					      ST21NFCA_WF_WEADEW_F_DATAWATE,
					      pawam, 1);
			if (w < 0)
				wetuwn w;

			pow_weq = be32_to_cpu((__fowce __be32)
					ST21NFCA_WF_WEADEW_F_POW_WEQ_DEFAUWT);
			w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_WEADEW_F_GATE,
					      ST21NFCA_WF_WEADEW_F_POW_WEQ,
					      (u8 *) &pow_weq, 4);
			if (w < 0)
				wetuwn w;
		}

		if ((ST21NFCA_WF_WEADEW_14443_3_A_GATE & im_pwotocows) == 0) {
			w = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_WF_WEADEW_14443_3_A_GATE);
			if (w < 0)
				wetuwn w;
		}

		if ((ST21NFCA_WF_WEADEW_ISO15693_GATE & im_pwotocows) == 0) {
			w = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_WF_WEADEW_ISO15693_GATE);
			if (w < 0)
				wetuwn w;
		}

		w = nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
				       NFC_HCI_EVT_WEADEW_WEQUESTED, NUWW, 0);
		if (w < 0)
			nfc_hci_send_event(hdev, NFC_HCI_WF_WEADEW_A_GATE,
					   NFC_HCI_EVT_END_OPEWATION, NUWW, 0);
	}

	if (tm_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_DATAWATE,
				      &datawate_skb);
		if (w < 0)
			wetuwn w;

		/* Configuwe the maximum suppowted datawate to 424Kbps */
		if (datawate_skb->wen > 0 &&
		    datawate_skb->data[0] !=
		    ST21NFCA_WF_CAWD_F_DATAWATE_212_424) {
			pawam[0] = ST21NFCA_WF_CAWD_F_DATAWATE_212_424;
			w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
					      ST21NFCA_WF_CAWD_F_DATAWATE,
					      pawam, 1);
			if (w < 0) {
				kfwee_skb(datawate_skb);
				wetuwn w;
			}
		}
		kfwee_skb(datawate_skb);

		/*
		 * Configuwe sens_wes
		 *
		 * NFC Fowum Digitaw Spec Tabwe 7:
		 * NFCID1 size: twipwe (10 bytes)
		 */
		pawam[0] = 0x00;
		pawam[1] = 0x08;
		w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_SENS_WES, pawam, 2);
		if (w < 0)
			wetuwn w;

		/*
		 * Configuwe sew_wes
		 *
		 * NFC Fowum Digistaw Spec Tabwe 17:
		 * b3 set to 0b (vawue b7-b6):
		 * - 10b: Configuwed fow NFC-DEP Pwotocow
		 */
		pawam[0] = 0x40;
		w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_SEW_WES, pawam, 1);
		if (w < 0)
			wetuwn w;

		/* Configuwe NFCID1 Wandom uid */
		w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_NFCID1, NUWW, 0);
		if (w < 0)
			wetuwn w;

		/* Configuwe NFCID2_WIST */
		/* System Code */
		pawam[0] = 0x00;
		pawam[1] = 0x00;
		/* NFCID2 */
		pawam[2] = 0x01;
		pawam[3] = 0xfe;
		pawam[4] = 'S';
		pawam[5] = 'T';
		pawam[6] = 'M';
		pawam[7] = 'i';
		pawam[8] = 'c';
		pawam[9] = 'w';
		/* 8 byte Pad bytes used fow powwing wespone fwame */

		/*
		 * Configuwation byte:
		 * - bit 0: define the defauwt NFCID2 entwy used when the
		 * system code is equaw to 'FFFF'
		 * - bit 1: use a wandom vawue fow wowest 6 bytes of
		 * NFCID2 vawue
		 * - bit 2: ignowe powwing wequest fwame if wequest code
		 * is equaw to '01'
		 * - Othew bits awe WFU
		 */
		pawam[18] = 0x01;
		w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_NFCID2_WIST, pawam,
				      19);
		if (w < 0)
			wetuwn w;

		pawam[0] = 0x02;
		w = nfc_hci_set_pawam(hdev, ST21NFCA_WF_CAWD_F_GATE,
				      ST21NFCA_WF_CAWD_F_MODE, pawam, 1);
	}

	wetuwn w;
}

static void st21nfca_hci_stop_poww(stwuct nfc_hci_dev *hdev)
{
	nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_DM_DISCONNECT, NUWW, 0, NUWW);
}

static int st21nfca_get_iso14443_3_atqa(stwuct nfc_hci_dev *hdev, u16 *atqa)
{
	int w;
	stwuct sk_buff *atqa_skb = NUWW;

	w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_14443_3_A_GATE,
			      ST21NFCA_WF_WEADEW_14443_3_A_ATQA, &atqa_skb);
	if (w < 0)
		goto exit;

	if (atqa_skb->wen != 2) {
		w = -EPWOTO;
		goto exit;
	}

	*atqa = be16_to_cpu(*(__be16 *) atqa_skb->data);

exit:
	kfwee_skb(atqa_skb);
	wetuwn w;
}

static int st21nfca_get_iso14443_3_sak(stwuct nfc_hci_dev *hdev, u8 *sak)
{
	int w;
	stwuct sk_buff *sak_skb = NUWW;

	w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_14443_3_A_GATE,
			      ST21NFCA_WF_WEADEW_14443_3_A_SAK, &sak_skb);
	if (w < 0)
		goto exit;

	if (sak_skb->wen != 1) {
		w = -EPWOTO;
		goto exit;
	}

	*sak = sak_skb->data[0];

exit:
	kfwee_skb(sak_skb);
	wetuwn w;
}

static int st21nfca_get_iso14443_3_uid(stwuct nfc_hci_dev *hdev, u8 *uid,
				       int *wen)
{
	int w;
	stwuct sk_buff *uid_skb = NUWW;

	w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_14443_3_A_GATE,
			      ST21NFCA_WF_WEADEW_14443_3_A_UID, &uid_skb);
	if (w < 0)
		goto exit;

	if (uid_skb->wen == 0 || uid_skb->wen > NFC_NFCID1_MAXSIZE) {
		w = -EPWOTO;
		goto exit;
	}

	memcpy(uid, uid_skb->data, uid_skb->wen);
	*wen = uid_skb->wen;
exit:
	kfwee_skb(uid_skb);
	wetuwn w;
}

static int st21nfca_get_iso15693_inventowy(stwuct nfc_hci_dev *hdev,
					   stwuct nfc_tawget *tawget)
{
	int w;
	stwuct sk_buff *inventowy_skb = NUWW;

	w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_ISO15693_GATE,
			      ST21NFCA_WF_WEADEW_ISO15693_INVENTOWY,
			      &inventowy_skb);
	if (w < 0)
		goto exit;

	skb_puww(inventowy_skb, 2);

	if (inventowy_skb->wen == 0 ||
	    inventowy_skb->wen > NFC_ISO15693_UID_MAXSIZE) {
		w = -EPWOTO;
		goto exit;
	}

	memcpy(tawget->iso15693_uid, inventowy_skb->data, inventowy_skb->wen);
	tawget->iso15693_dsfid	= inventowy_skb->data[1];
	tawget->is_iso15693 = 1;
exit:
	kfwee_skb(inventowy_skb);
	wetuwn w;
}

static int st21nfca_hci_dep_wink_up(stwuct nfc_hci_dev *hdev,
				    stwuct nfc_tawget *tawget, u8 comm_mode,
				    u8 *gb, size_t gb_wen)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	info->dep_info.idx = tawget->idx;
	wetuwn st21nfca_im_send_atw_weq(hdev, gb, gb_wen);
}

static int st21nfca_hci_dep_wink_down(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	info->state = ST21NFCA_ST_WEADY;

	wetuwn nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_DM_DISCONNECT, NUWW, 0, NUWW);
}

static int st21nfca_hci_tawget_fwom_gate(stwuct nfc_hci_dev *hdev, u8 gate,
					 stwuct nfc_tawget *tawget)
{
	int w, wen;
	u16 atqa;
	u8 sak;
	u8 uid[NFC_NFCID1_MAXSIZE];

	switch (gate) {
	case ST21NFCA_WF_WEADEW_F_GATE:
		tawget->suppowted_pwotocows = NFC_PWOTO_FEWICA_MASK;
		bweak;
	case ST21NFCA_WF_WEADEW_14443_3_A_GATE:
		/* ISO14443-3 type 1 ow 2 tags */
		w = st21nfca_get_iso14443_3_atqa(hdev, &atqa);
		if (w < 0)
			wetuwn w;
		if (atqa == 0x000c) {
			tawget->suppowted_pwotocows = NFC_PWOTO_JEWEW_MASK;
			tawget->sens_wes = 0x0c00;
		} ewse {
			w = st21nfca_get_iso14443_3_sak(hdev, &sak);
			if (w < 0)
				wetuwn w;

			w = st21nfca_get_iso14443_3_uid(hdev, uid, &wen);
			if (w < 0)
				wetuwn w;

			tawget->suppowted_pwotocows =
			    nfc_hci_sak_to_pwotocow(sak);
			if (tawget->suppowted_pwotocows == 0xffffffff)
				wetuwn -EPWOTO;

			tawget->sens_wes = atqa;
			tawget->sew_wes = sak;
			memcpy(tawget->nfcid1, uid, wen);
			tawget->nfcid1_wen = wen;
		}

		bweak;
	case ST21NFCA_WF_WEADEW_ISO15693_GATE:
		tawget->suppowted_pwotocows = NFC_PWOTO_ISO15693_MASK;
		w = st21nfca_get_iso15693_inventowy(hdev, tawget);
		if (w < 0)
			wetuwn w;
		bweak;
	defauwt:
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int st21nfca_hci_compwete_tawget_discovewed(stwuct nfc_hci_dev *hdev,
						u8 gate,
						stwuct nfc_tawget *tawget)
{
	int w;
	stwuct sk_buff *nfcid_skb = NUWW;

	if (gate == ST21NFCA_WF_WEADEW_F_GATE) {
		w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_F_GATE,
				ST21NFCA_WF_WEADEW_F_NFCID2, &nfcid_skb);
		if (w < 0)
			goto exit;

		if (nfcid_skb->wen > NFC_SENSF_WES_MAXSIZE) {
			w = -EPWOTO;
			goto exit;
		}

		/*
		 * - Aftew the wecepton of powwing wesponse fow type F fwame
		 * at 212 ow 424 Kbit/s, NFCID2 wegistwy pawametews wiww be
		 * updated.
		 * - Aftew the weception of SEW_WES with NFCIP-1 compwiant bit
		 * set fow type A fwame NFCID1 wiww be updated
		 */
		if (nfcid_skb->wen > 0) {
			/* P2P in type F */
			memcpy(tawget->sensf_wes, nfcid_skb->data,
				nfcid_skb->wen);
			tawget->sensf_wes_wen = nfcid_skb->wen;
			/* NFC Fowum Digitaw Pwotocow Tabwe 44 */
			if (tawget->sensf_wes[0] == 0x01 &&
			    tawget->sensf_wes[1] == 0xfe)
				tawget->suppowted_pwotocows =
							NFC_PWOTO_NFC_DEP_MASK;
			ewse
				tawget->suppowted_pwotocows =
							NFC_PWOTO_FEWICA_MASK;
		} ewse {
			kfwee_skb(nfcid_skb);
			nfcid_skb = NUWW;
			/* P2P in type A */
			w = nfc_hci_get_pawam(hdev, ST21NFCA_WF_WEADEW_F_GATE,
					ST21NFCA_WF_WEADEW_F_NFCID1,
					&nfcid_skb);
			if (w < 0)
				goto exit;

			if (nfcid_skb->wen > NFC_NFCID1_MAXSIZE) {
				w = -EPWOTO;
				goto exit;
			}
			memcpy(tawget->sensf_wes, nfcid_skb->data,
				nfcid_skb->wen);
			tawget->sensf_wes_wen = nfcid_skb->wen;
			tawget->suppowted_pwotocows = NFC_PWOTO_NFC_DEP_MASK;
		}
		tawget->hci_weadew_gate = ST21NFCA_WF_WEADEW_F_GATE;
	}
	w = 1;
exit:
	kfwee_skb(nfcid_skb);
	wetuwn w;
}

#define ST21NFCA_CB_TYPE_WEADEW_ISO15693 1
static void st21nfca_hci_data_exchange_cb(void *context, stwuct sk_buff *skb,
					  int eww)
{
	stwuct st21nfca_hci_info *info = context;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_WEADEW_ISO15693:
		if (eww == 0)
			skb_twim(skb, skb->wen - 1);
		info->async_cb(info->async_cb_context, skb, eww);
		bweak;
	defauwt:
		if (eww == 0)
			kfwee_skb(skb);
		bweak;
	}
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the data exchange
 *    1: dwivew doesn't especiawwy handwe, pwease do standawd pwocessing
 */
static int st21nfca_hci_im_twansceive(stwuct nfc_hci_dev *hdev,
				      stwuct nfc_tawget *tawget,
				      stwuct sk_buff *skb,
				      data_exchange_cb_t cb, void *cb_context)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_info(DWIVEW_DESC ": %s fow gate=%d wen=%d\n", __func__,
		tawget->hci_weadew_gate, skb->wen);

	switch (tawget->hci_weadew_gate) {
	case ST21NFCA_WF_WEADEW_F_GATE:
		if (tawget->suppowted_pwotocows == NFC_PWOTO_NFC_DEP_MASK)
			wetuwn st21nfca_im_send_dep_weq(hdev, skb);

		*(u8 *)skb_push(skb, 1) = 0x1a;
		wetuwn nfc_hci_send_cmd_async(hdev, tawget->hci_weadew_gate,
					      ST21NFCA_WW_XCHG_DATA, skb->data,
					      skb->wen, cb, cb_context);
	case ST21NFCA_WF_WEADEW_14443_3_A_GATE:
		*(u8 *)skb_push(skb, 1) = 0x1a;	/* CTW, see spec:10.2.2.1 */

		wetuwn nfc_hci_send_cmd_async(hdev, tawget->hci_weadew_gate,
					      ST21NFCA_WW_XCHG_DATA, skb->data,
					      skb->wen, cb, cb_context);
	case ST21NFCA_WF_WEADEW_ISO15693_GATE:
		info->async_cb_type = ST21NFCA_CB_TYPE_WEADEW_ISO15693;
		info->async_cb = cb;
		info->async_cb_context = cb_context;

		*(u8 *)skb_push(skb, 1) = 0x17;

		wetuwn nfc_hci_send_cmd_async(hdev, tawget->hci_weadew_gate,
					      ST21NFCA_WW_XCHG_DATA, skb->data,
					      skb->wen,
					      st21nfca_hci_data_exchange_cb,
					      info);
	defauwt:
		wetuwn 1;
	}
}

static int st21nfca_hci_tm_send(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	wetuwn st21nfca_tm_send_dep_wes(hdev, skb);
}

static int st21nfca_hci_check_pwesence(stwuct nfc_hci_dev *hdev,
				       stwuct nfc_tawget *tawget)
{
	u8 fwi = 0x11;

	switch (tawget->hci_weadew_gate) {
	case NFC_HCI_WF_WEADEW_A_GATE:
	case NFC_HCI_WF_WEADEW_B_GATE:
		/*
		 * PWESENCE_CHECK on those gates is avaiwabwe
		 * Howevew, the answew to this command is taking 3 * fwi
		 * if the cawd is no pwesent.
		 * Instead, we send an empty I-Fwame with a vewy showt
		 * configuwabwe fwi ~604µs.
		 */
		wetuwn nfc_hci_send_cmd(hdev, tawget->hci_weadew_gate,
					ST21NFCA_WW_XCHG_DATA, &fwi, 1, NUWW);
	case ST21NFCA_WF_WEADEW_14443_3_A_GATE:
		wetuwn nfc_hci_send_cmd(hdev, tawget->hci_weadew_gate,
					ST21NFCA_WF_WEADEW_CMD_PWESENCE_CHECK,
					NUWW, 0, NUWW);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void st21nfca_hci_cmd_weceived(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
				stwuct sk_buff *skb)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	u8 gate = hdev->pipes[pipe].gate;

	pw_debug("cmd: %x\n", cmd);

	switch (cmd) {
	case NFC_HCI_ANY_OPEN_PIPE:
		if (gate != ST21NFCA_APDU_WEADEW_GATE &&
			hdev->pipes[pipe].dest_host != NFC_HCI_UICC_HOST_ID)
			info->se_info.count_pipes++;

		if (info->se_info.count_pipes == info->se_info.expected_pipes) {
			dew_timew_sync(&info->se_info.se_active_timew);
			info->se_info.se_active = fawse;
			info->se_info.count_pipes = 0;
			compwete(&info->se_info.weq_compwetion);
		}
	bweak;
	}
}

static int st21nfca_admin_event_weceived(stwuct nfc_hci_dev *hdev, u8 event,
					stwuct sk_buff *skb)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_debug("admin event: %x\n", event);

	switch (event) {
	case ST21NFCA_EVT_HOT_PWUG:
		if (info->se_info.se_active) {
			if (!ST21NFCA_EVT_HOT_PWUG_IS_INHIBITED(skb)) {
				dew_timew_sync(&info->se_info.se_active_timew);
				info->se_info.se_active = fawse;
				compwete(&info->se_info.weq_compwetion);
			} ewse {
				mod_timew(&info->se_info.se_active_timew,
					jiffies +
					msecs_to_jiffies(ST21NFCA_SE_TO_PIPES));
			}
		}
	bweak;
	defauwt:
		nfc_eww(&hdev->ndev->dev, "Unexpected event on admin gate\n");
	}
	kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the event, skb consumed
 *    1: dwivew does not handwe the event, pwease do standawd pwocessing
 */
static int st21nfca_hci_event_weceived(stwuct nfc_hci_dev *hdev, u8 pipe,
				       u8 event, stwuct sk_buff *skb)
{
	u8 gate = hdev->pipes[pipe].gate;
	u8 host = hdev->pipes[pipe].dest_host;

	pw_debug("hci event: %d gate: %x\n", event, gate);

	switch (gate) {
	case NFC_HCI_ADMIN_GATE:
		wetuwn st21nfca_admin_event_weceived(hdev, event, skb);
	case ST21NFCA_WF_CAWD_F_GATE:
		wetuwn st21nfca_dep_event_weceived(hdev, event, skb);
	case ST21NFCA_CONNECTIVITY_GATE:
		wetuwn st21nfca_connectivity_event_weceived(hdev, host,
							event, skb);
	case ST21NFCA_APDU_WEADEW_GATE:
		wetuwn st21nfca_apdu_weadew_event_weceived(hdev, event, skb);
	case NFC_HCI_WOOPBACK_GATE:
		wetuwn st21nfca_hci_woopback_event_weceived(hdev, event, skb);
	defauwt:
		wetuwn 1;
	}
}

static const stwuct nfc_hci_ops st21nfca_hci_ops = {
	.open = st21nfca_hci_open,
	.cwose = st21nfca_hci_cwose,
	.woad_session = st21nfca_hci_woad_session,
	.hci_weady = st21nfca_hci_weady,
	.xmit = st21nfca_hci_xmit,
	.stawt_poww = st21nfca_hci_stawt_poww,
	.stop_poww = st21nfca_hci_stop_poww,
	.dep_wink_up = st21nfca_hci_dep_wink_up,
	.dep_wink_down = st21nfca_hci_dep_wink_down,
	.tawget_fwom_gate = st21nfca_hci_tawget_fwom_gate,
	.compwete_tawget_discovewed = st21nfca_hci_compwete_tawget_discovewed,
	.im_twansceive = st21nfca_hci_im_twansceive,
	.tm_send = st21nfca_hci_tm_send,
	.check_pwesence = st21nfca_hci_check_pwesence,
	.event_weceived = st21nfca_hci_event_weceived,
	.cmd_weceived = st21nfca_hci_cmd_weceived,
	.discovew_se = st21nfca_hci_discovew_se,
	.enabwe_se = st21nfca_hci_enabwe_se,
	.disabwe_se = st21nfca_hci_disabwe_se,
	.se_io = st21nfca_hci_se_io,
};

int st21nfca_hci_pwobe(void *phy_id, const stwuct nfc_phy_ops *phy_ops,
		       chaw *wwc_name, int phy_headwoom, int phy_taiwwoom,
		       int phy_paywoad, stwuct nfc_hci_dev **hdev,
			   stwuct st21nfca_se_status *se_status)
{
	stwuct st21nfca_hci_info *info;
	int w = 0;
	int dev_num;
	u32 pwotocows;
	stwuct nfc_hci_init_data init_data;
	unsigned wong quiwks = 0;

	info = kzawwoc(sizeof(stwuct st21nfca_hci_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->phy_ops = phy_ops;
	info->phy_id = phy_id;
	info->state = ST21NFCA_ST_COWD;
	mutex_init(&info->info_wock);

	init_data.gate_count = AWWAY_SIZE(st21nfca_gates);

	memcpy(init_data.gates, st21nfca_gates, sizeof(st21nfca_gates));

	/*
	 * Session id must incwude the dwivew name + i2c bus addw
	 * pewsistent info to discwiminate 2 identicaw chips
	 */
	dev_num = find_fiwst_zewo_bit(dev_mask, ST21NFCA_NUM_DEVICES);
	if (dev_num >= ST21NFCA_NUM_DEVICES) {
		w = -ENODEV;
		goto eww_awwoc_hdev;
	}

	set_bit(dev_num, dev_mask);

	scnpwintf(init_data.session_id, sizeof(init_data.session_id), "%s%2x",
		  "ST21AH", dev_num);

	pwotocows = NFC_PWOTO_JEWEW_MASK |
	    NFC_PWOTO_MIFAWE_MASK |
	    NFC_PWOTO_FEWICA_MASK |
	    NFC_PWOTO_ISO14443_MASK |
	    NFC_PWOTO_ISO14443_B_MASK |
	    NFC_PWOTO_ISO15693_MASK |
	    NFC_PWOTO_NFC_DEP_MASK;

	set_bit(NFC_HCI_QUIWK_SHOWT_CWEAW, &quiwks);

	info->hdev =
	    nfc_hci_awwocate_device(&st21nfca_hci_ops, &init_data, quiwks,
				    pwotocows, wwc_name,
				    phy_headwoom + ST21NFCA_CMDS_HEADWOOM,
				    phy_taiwwoom, phy_paywoad);

	if (!info->hdev) {
		pw_eww("Cannot awwocate nfc hdev.\n");
		w = -ENOMEM;
		goto eww_awwoc_hdev;
	}

	info->se_status = se_status;

	nfc_hci_set_cwientdata(info->hdev, info);

	w = nfc_hci_wegistew_device(info->hdev);
	if (w)
		goto eww_wegdev;

	*hdev = info->hdev;
	st21nfca_dep_init(info->hdev);
	st21nfca_se_init(info->hdev);
	st21nfca_vendow_cmds_init(info->hdev);

	wetuwn 0;

eww_wegdev:
	nfc_hci_fwee_device(info->hdev);

eww_awwoc_hdev:
	kfwee(info);

	wetuwn w;
}
EXPOWT_SYMBOW(st21nfca_hci_pwobe);

void st21nfca_hci_wemove(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	st21nfca_dep_deinit(hdev);
	st21nfca_se_deinit(hdev);
	nfc_hci_unwegistew_device(hdev);
	nfc_hci_fwee_device(hdev);
	kfwee(info);
}
EXPOWT_SYMBOW(st21nfca_hci_wemove);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
