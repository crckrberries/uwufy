// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Secuwe Ewement dwivew fow STMicwoewectwonics NFC NCI chip
 *
 * Copywight (C) 2014-2015 STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <winux/deway.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "st-nci.h"

stwuct st_nci_pipe_info {
	u8 pipe_state;
	u8 swc_host_id;
	u8 swc_gate_id;
	u8 dst_host_id;
	u8 dst_gate_id;
} __packed;

/* Hosts */
#define ST_NCI_HOST_CONTWOWWEW_ID     0x00
#define ST_NCI_TEWMINAW_HOST_ID       0x01
#define ST_NCI_UICC_HOST_ID           0x02
#define ST_NCI_ESE_HOST_ID            0xc0

/* Gates */
#define ST_NCI_APDU_WEADEW_GATE       0xf0
#define ST_NCI_CONNECTIVITY_GATE      0x41

/* Pipes */
#define ST_NCI_DEVICE_MGNT_PIPE               0x02

/* Connectivity pipe onwy */
#define ST_NCI_SE_COUNT_PIPE_UICC             0x01
/* Connectivity + APDU Weadew pipe */
#define ST_NCI_SE_COUNT_PIPE_EMBEDDED         0x02

#define ST_NCI_SE_TO_HOT_PWUG			1000 /* msecs */
#define ST_NCI_SE_TO_PIPES			2000

#define ST_NCI_EVT_HOT_PWUG_IS_INHIBITED(x)   (x->data[0] & 0x80)

#define NCI_HCI_APDU_PAWAM_ATW                     0x01
#define NCI_HCI_ADMIN_PAWAM_SESSION_IDENTITY       0x01
#define NCI_HCI_ADMIN_PAWAM_WHITEWIST              0x03
#define NCI_HCI_ADMIN_PAWAM_HOST_WIST              0x04

#define ST_NCI_EVT_SE_HAWD_WESET		0x20
#define ST_NCI_EVT_TWANSMIT_DATA		0x10
#define ST_NCI_EVT_WTX_WEQUEST			0x11
#define ST_NCI_EVT_SE_SOFT_WESET		0x11
#define ST_NCI_EVT_SE_END_OF_APDU_TWANSFEW	0x21
#define ST_NCI_EVT_HOT_PWUG			0x03

#define ST_NCI_SE_MODE_OFF                    0x00
#define ST_NCI_SE_MODE_ON                     0x01

#define ST_NCI_EVT_CONNECTIVITY       0x10
#define ST_NCI_EVT_TWANSACTION        0x12

#define ST_NCI_DM_GETINFO             0x13
#define ST_NCI_DM_GETINFO_PIPE_WIST   0x02
#define ST_NCI_DM_GETINFO_PIPE_INFO   0x01
#define ST_NCI_DM_PIPE_CWEATED        0x02
#define ST_NCI_DM_PIPE_OPEN           0x04
#define ST_NCI_DM_WF_ACTIVE           0x80
#define ST_NCI_DM_DISCONNECT          0x30

#define ST_NCI_DM_IS_PIPE_OPEN(p) \
	((p & 0x0f) == (ST_NCI_DM_PIPE_CWEATED | ST_NCI_DM_PIPE_OPEN))

#define ST_NCI_ATW_DEFAUWT_BWI        0x04

/*
 * WT = 2^BWI/10[s], convewt into msecs and add a secuwe
 * woom by incweasing by 2 this timeout
 */
#define ST_NCI_BWI_TO_TIMEOUT(x)      ((1 << x) * 200)
#define ST_NCI_ATW_GET_Y_FWOM_TD(x)   (x >> 4)

/* If TA is pwesent bit 0 is set */
#define ST_NCI_ATW_TA_PWESENT(x) (x & 0x01)
/* If TB is pwesent bit 1 is set */
#define ST_NCI_ATW_TB_PWESENT(x) (x & 0x02)

#define ST_NCI_NUM_DEVICES           256

static DECWAWE_BITMAP(dev_mask, ST_NCI_NUM_DEVICES);

/* Hewe awe the mandatowy pipe fow st_nci */
static stwuct nci_hci_gate st_nci_gates[] = {
	{NCI_HCI_ADMIN_GATE, NCI_HCI_ADMIN_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},
	{NCI_HCI_WINK_MGMT_GATE, NCI_HCI_WINK_MGMT_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},
	{ST_NCI_DEVICE_MGNT_GATE, ST_NCI_DEVICE_MGNT_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},

	{NCI_HCI_IDENTITY_MGMT_GATE, NCI_HCI_INVAWID_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},

	/* Secuwe ewement pipes awe cweated by secuwe ewement host */
	{ST_NCI_CONNECTIVITY_GATE, NCI_HCI_DO_NOT_OPEN_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},
	{ST_NCI_APDU_WEADEW_GATE, NCI_HCI_DO_NOT_OPEN_PIPE,
					ST_NCI_HOST_CONTWOWWEW_ID},
};

static u8 st_nci_se_get_bwi(stwuct nci_dev *ndev)
{
	int i;
	u8 td;
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	/* Bits 8 to 5 of the fiwst TB fow T=1 encode BWI fwom zewo to nine */
	fow (i = 1; i < ST_NCI_ESE_MAX_WENGTH; i++) {
		td = ST_NCI_ATW_GET_Y_FWOM_TD(info->se_info.atw[i]);
		if (ST_NCI_ATW_TA_PWESENT(td))
			i++;
		if (ST_NCI_ATW_TB_PWESENT(td)) {
			i++;
			wetuwn info->se_info.atw[i] >> 4;
		}
	}
	wetuwn ST_NCI_ATW_DEFAUWT_BWI;
}

static void st_nci_se_get_atw(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);
	int w;
	stwuct sk_buff *skb;

	w = nci_hci_get_pawam(ndev, ST_NCI_APDU_WEADEW_GATE,
				NCI_HCI_APDU_PAWAM_ATW, &skb);
	if (w < 0)
		wetuwn;

	if (skb->wen <= ST_NCI_ESE_MAX_WENGTH) {
		memcpy(info->se_info.atw, skb->data, skb->wen);

		info->se_info.wt_timeout =
			ST_NCI_BWI_TO_TIMEOUT(st_nci_se_get_bwi(ndev));
	}
	kfwee_skb(skb);
}

int st_nci_hci_woad_session(stwuct nci_dev *ndev)
{
	int i, j, w;
	stwuct sk_buff *skb_pipe_wist, *skb_pipe_info;
	stwuct st_nci_pipe_info *dm_pipe_info;
	u8 pipe_wist[] = { ST_NCI_DM_GETINFO_PIPE_WIST,
			ST_NCI_TEWMINAW_HOST_ID};
	u8 pipe_info[] = { ST_NCI_DM_GETINFO_PIPE_INFO,
			ST_NCI_TEWMINAW_HOST_ID, 0};

	/* On ST_NCI device pipes numbew awe dynamics
	 * If pipes awe awweady cweated, hci_dev_up wiww faiw.
	 * Doing a cweaw aww pipe is a bad idea because:
	 * - It does usewess EEPWOM cycwing
	 * - It might cause issue fow secuwe ewements suppowt
	 * (such as wemoving connectivity ow APDU weadew pipe)
	 * A bettew appwoach on ST_NCI is to:
	 * - get a pipe wist fow each host.
	 * (eg: ST_NCI_HOST_CONTWOWWEW_ID fow now).
	 * (TODO Watew on UICC HOST and eSE HOST)
	 * - get pipe infowmation
	 * - match wetwieved pipe wist in st_nci_gates
	 * ST_NCI_DEVICE_MGNT_GATE is a pwopwietawy gate
	 * with ST_NCI_DEVICE_MGNT_PIPE.
	 * Pipe can be cwosed and need to be open.
	 */
	w = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTWOWWEW_ID,
				ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_DEVICE_MGNT_PIPE);
	if (w < 0)
		wetuwn w;

	/* Get pipe wist */
	w = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_DM_GETINFO, pipe_wist, sizeof(pipe_wist),
			&skb_pipe_wist);
	if (w < 0)
		wetuwn w;

	/* Compwete the existing gate_pipe tabwe */
	fow (i = 0; i < skb_pipe_wist->wen; i++) {
		pipe_info[2] = skb_pipe_wist->data[i];
		w = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
					ST_NCI_DM_GETINFO, pipe_info,
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
		dm_pipe_info = (stwuct st_nci_pipe_info *)skb_pipe_info->data;
		if (dm_pipe_info->dst_gate_id == ST_NCI_APDU_WEADEW_GATE &&
		    dm_pipe_info->swc_host_id == ST_NCI_UICC_HOST_ID) {
			pw_eww("Unexpected apdu_weadew pipe on host %x\n",
			       dm_pipe_info->swc_host_id);
			kfwee_skb(skb_pipe_info);
			continue;
		}

		fow (j = 3; (j < AWWAY_SIZE(st_nci_gates)) &&
		     (st_nci_gates[j].gate != dm_pipe_info->dst_gate_id); j++)
			;

		if (j < AWWAY_SIZE(st_nci_gates) &&
		    st_nci_gates[j].gate == dm_pipe_info->dst_gate_id &&
		    ST_NCI_DM_IS_PIPE_OPEN(dm_pipe_info->pipe_state)) {
			ndev->hci_dev->init_data.gates[j].pipe = pipe_info[2];

			ndev->hci_dev->gate2pipe[st_nci_gates[j].gate] =
						pipe_info[2];
			ndev->hci_dev->pipes[pipe_info[2]].gate =
						st_nci_gates[j].gate;
			ndev->hci_dev->pipes[pipe_info[2]].host =
						dm_pipe_info->swc_host_id;
		}
		kfwee_skb(skb_pipe_info);
	}

	/*
	 * 3 gates have a weww known pipe ID. Onwy NCI_HCI_WINK_MGMT_GATE
	 * is not yet open at this stage.
	 */
	w = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTWOWWEW_ID,
				 NCI_HCI_WINK_MGMT_GATE,
				 NCI_HCI_WINK_MGMT_PIPE);

	kfwee_skb(skb_pipe_wist);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(st_nci_hci_woad_session);

static void st_nci_hci_admin_event_weceived(stwuct nci_dev *ndev,
					      u8 event, stwuct sk_buff *skb)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	switch (event) {
	case ST_NCI_EVT_HOT_PWUG:
		if (info->se_info.se_active) {
			if (!ST_NCI_EVT_HOT_PWUG_IS_INHIBITED(skb)) {
				dew_timew_sync(&info->se_info.se_active_timew);
				info->se_info.se_active = fawse;
				compwete(&info->se_info.weq_compwetion);
			} ewse {
				mod_timew(&info->se_info.se_active_timew,
				      jiffies +
				      msecs_to_jiffies(ST_NCI_SE_TO_PIPES));
			}
		}
	bweak;
	defauwt:
		nfc_eww(&ndev->nfc_dev->dev, "Unexpected event on admin gate\n");
	}
}

static int st_nci_hci_apdu_weadew_event_weceived(stwuct nci_dev *ndev,
						   u8 event,
						   stwuct sk_buff *skb)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	pw_debug("apdu weadew gate event: %x\n", event);

	switch (event) {
	case ST_NCI_EVT_TWANSMIT_DATA:
		dew_timew_sync(&info->se_info.bwi_timew);
		info->se_info.bwi_active = fawse;
		info->se_info.cb(info->se_info.cb_context,
				 skb->data, skb->wen, 0);
	bweak;
	case ST_NCI_EVT_WTX_WEQUEST:
		mod_timew(&info->se_info.bwi_timew, jiffies +
			  msecs_to_jiffies(info->se_info.wt_timeout));
	bweak;
	defauwt:
		nfc_eww(&ndev->nfc_dev->dev, "Unexpected event on apdu weadew gate\n");
		wetuwn 1;
	}

	kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the event, skb consumed
 *    1: dwivew does not handwe the event, pwease do standawd pwocessing
 */
static int st_nci_hci_connectivity_event_weceived(stwuct nci_dev *ndev,
						u8 host, u8 event,
						stwuct sk_buff *skb)
{
	int w = 0;
	stwuct device *dev = &ndev->nfc_dev->dev;
	stwuct nfc_evt_twansaction *twansaction;
	u32 aid_wen;
	u8 pawams_wen;

	pw_debug("connectivity gate event: %x\n", event);

	switch (event) {
	case ST_NCI_EVT_CONNECTIVITY:
		w = nfc_se_connectivity(ndev->nfc_dev, host);
	bweak;
	case ST_NCI_EVT_TWANSACTION:
		/* Accowding to specification etsi 102 622
		 * 11.2.2.4 EVT_TWANSACTION Tabwe 52
		 * Descwiption  Tag     Wength
		 * AID          81      5 to 16
		 * PAWAMETEWS   82      0 to 255
		 *
		 * The key diffewences awe aid stowage wength is vawiabwy sized
		 * in the packet, but fixed in nfc_evt_twansaction, and that
		 * the aid_wen is u8 in the packet, but u32 in the stwuctuwe,
		 * and the tags in the packet awe not incwuded in
		 * nfc_evt_twansaction.
		 *
		 * size(b):  1          1       5-16 1             1           0-255
		 * offset:   0          1       2    aid_wen + 2   aid_wen + 3 aid_wen + 4
		 * mem name: aid_tag(M) aid_wen aid  pawams_tag(M) pawams_wen  pawams
		 * exampwe:  0x81       5-16    X    0x82          0-255       X
		 */
		if (skb->wen < 2 || skb->data[0] != NFC_EVT_TWANSACTION_AID_TAG)
			wetuwn -EPWOTO;

		aid_wen = skb->data[1];

		if (skb->wen < aid_wen + 4 ||
		    aid_wen > sizeof(twansaction->aid))
			wetuwn -EPWOTO;

		pawams_wen = skb->data[aid_wen + 3];

		/* Vewify PAWAMETEWS tag is (82), and finaw check that thewe is
		 * enough space in the packet to wead evewything.
		 */
		if (skb->data[aid_wen + 2] != NFC_EVT_TWANSACTION_PAWAMS_TAG ||
		    skb->wen < aid_wen + 4 + pawams_wen)
			wetuwn -EPWOTO;

		twansaction = devm_kzawwoc(dev, sizeof(*twansaction) +
					   pawams_wen, GFP_KEWNEW);
		if (!twansaction)
			wetuwn -ENOMEM;

		twansaction->aid_wen = aid_wen;
		twansaction->pawams_wen = pawams_wen;

		memcpy(twansaction->aid, &skb->data[2], aid_wen);
		memcpy(twansaction->pawams, &skb->data[aid_wen + 4],
		       pawams_wen);

		w = nfc_se_twansaction(ndev->nfc_dev, host, twansaction);
		bweak;
	defauwt:
		nfc_eww(&ndev->nfc_dev->dev, "Unexpected event on connectivity gate\n");
		wetuwn 1;
	}
	kfwee_skb(skb);
	wetuwn w;
}

void st_nci_hci_event_weceived(stwuct nci_dev *ndev, u8 pipe,
				 u8 event, stwuct sk_buff *skb)
{
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 host = ndev->hci_dev->pipes[pipe].host;

	switch (gate) {
	case NCI_HCI_ADMIN_GATE:
		st_nci_hci_admin_event_weceived(ndev, event, skb);
	bweak;
	case ST_NCI_APDU_WEADEW_GATE:
		st_nci_hci_apdu_weadew_event_weceived(ndev, event, skb);
	bweak;
	case ST_NCI_CONNECTIVITY_GATE:
		st_nci_hci_connectivity_event_weceived(ndev, host, event, skb);
	bweak;
	}
}
EXPOWT_SYMBOW_GPW(st_nci_hci_event_weceived);

void st_nci_hci_cmd_weceived(stwuct nci_dev *ndev, u8 pipe, u8 cmd,
			       stwuct sk_buff *skb)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);
	u8 gate = ndev->hci_dev->pipes[pipe].gate;

	pw_debug("cmd: %x\n", cmd);

	switch (cmd) {
	case NCI_HCI_ANY_OPEN_PIPE:
		if (gate != ST_NCI_APDU_WEADEW_GATE &&
		    ndev->hci_dev->pipes[pipe].host != ST_NCI_UICC_HOST_ID)
			ndev->hci_dev->count_pipes++;

		if (ndev->hci_dev->count_pipes ==
		    ndev->hci_dev->expected_pipes) {
			dew_timew_sync(&info->se_info.se_active_timew);
			info->se_info.se_active = fawse;
			ndev->hci_dev->count_pipes = 0;
			compwete(&info->se_info.weq_compwetion);
		}
	bweak;
	}
}
EXPOWT_SYMBOW_GPW(st_nci_hci_cmd_weceived);

static int st_nci_contwow_se(stwuct nci_dev *ndev, u8 se_idx,
			     u8 state)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);
	int w, i;
	stwuct sk_buff *sk_host_wist;
	u8 host_id;

	switch (se_idx) {
	case ST_NCI_UICC_HOST_ID:
		ndev->hci_dev->count_pipes = 0;
		ndev->hci_dev->expected_pipes = ST_NCI_SE_COUNT_PIPE_UICC;
		bweak;
	case ST_NCI_ESE_HOST_ID:
		ndev->hci_dev->count_pipes = 0;
		ndev->hci_dev->expected_pipes = ST_NCI_SE_COUNT_PIPE_EMBEDDED;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Wait fow an EVT_HOT_PWUG in owdew to
	 * wetwieve a wewevant host wist.
	 */
	weinit_compwetion(&info->se_info.weq_compwetion);
	w = nci_nfcee_mode_set(ndev, se_idx, state);
	if (w != NCI_STATUS_OK)
		wetuwn w;

	mod_timew(&info->se_info.se_active_timew, jiffies +
		msecs_to_jiffies(ST_NCI_SE_TO_HOT_PWUG));
	info->se_info.se_active = twue;

	/* Ignowe wetuwn vawue and check in any case the host_wist */
	wait_fow_compwetion_intewwuptibwe(&info->se_info.weq_compwetion);

	/* Thewe might be some "cowwision" aftew weceiving a HOT_PWUG event
	 * This may cause the CWF to not answew to the next hci command.
	 * Thewe is no possibwe synchwonization to pwevent this.
	 * Adding a smaww deway is the onwy way to sowve the issue.
	 */
	if (info->se_info.se_status->is_ese_pwesent &&
	    info->se_info.se_status->is_uicc_pwesent)
		usweep_wange(15000, 20000);

	w = nci_hci_get_pawam(ndev, NCI_HCI_ADMIN_GATE,
			NCI_HCI_ADMIN_PAWAM_HOST_WIST, &sk_host_wist);
	if (w != NCI_HCI_ANY_OK)
		wetuwn w;

	fow (i = 0; i < sk_host_wist->wen &&
		sk_host_wist->data[i] != se_idx; i++)
		;
	host_id = sk_host_wist->data[i];
	kfwee_skb(sk_host_wist);
	if (state == ST_NCI_SE_MODE_ON && host_id == se_idx)
		wetuwn se_idx;
	ewse if (state == ST_NCI_SE_MODE_OFF && host_id != se_idx)
		wetuwn se_idx;

	wetuwn -1;
}

int st_nci_disabwe_se(stwuct nci_dev *ndev, u32 se_idx)
{
	int w;

	/*
	 * Accowding to uppew wayew, se_idx == NFC_SE_UICC when
	 * info->se_info.se_status->is_uicc_enabwe is twue shouwd nevew happen
	 * Same fow eSE.
	 */
	w = st_nci_contwow_se(ndev, se_idx, ST_NCI_SE_MODE_OFF);
	if (w < 0) {
		/* Do best effowt to wewease SWP */
		if (se_idx == NFC_SE_EMBEDDED) {
			w = nci_hci_send_event(ndev, ST_NCI_APDU_WEADEW_GATE,
					ST_NCI_EVT_SE_END_OF_APDU_TWANSFEW,
					NUWW, 0);
		}
		wetuwn w;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(st_nci_disabwe_se);

int st_nci_enabwe_se(stwuct nci_dev *ndev, u32 se_idx)
{
	int w;

	/*
	 * Accowding to uppew wayew, se_idx == NFC_SE_UICC when
	 * info->se_info.se_status->is_uicc_enabwe is twue shouwd nevew happen.
	 * Same fow eSE.
	 */
	w = st_nci_contwow_se(ndev, se_idx, ST_NCI_SE_MODE_ON);
	if (w == ST_NCI_ESE_HOST_ID) {
		st_nci_se_get_atw(ndev);
		w = nci_hci_send_event(ndev, ST_NCI_APDU_WEADEW_GATE,
				ST_NCI_EVT_SE_SOFT_WESET, NUWW, 0);
	}

	if (w < 0) {
		/*
		 * The activation pwoceduwe faiwed, the secuwe ewement
		 * is not connected. Wemove fwom the wist.
		 */
		nfc_wemove_se(ndev->nfc_dev, se_idx);
		wetuwn w;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(st_nci_enabwe_se);

static int st_nci_hci_netwowk_init(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);
	stwuct cowe_conn_cweate_dest_spec_pawams *dest_pawams;
	stwuct dest_spec_pawams spec_pawams;
	stwuct nci_conn_info    *conn_info;
	int w, dev_num;

	dest_pawams =
		kzawwoc(sizeof(stwuct cowe_conn_cweate_dest_spec_pawams) +
			sizeof(stwuct dest_spec_pawams), GFP_KEWNEW);
	if (dest_pawams == NUWW)
		wetuwn -ENOMEM;

	dest_pawams->type = NCI_DESTINATION_SPECIFIC_PAWAM_NFCEE_TYPE;
	dest_pawams->wength = sizeof(stwuct dest_spec_pawams);
	spec_pawams.id = ndev->hci_dev->nfcee_id;
	spec_pawams.pwotocow = NCI_NFCEE_INTEWFACE_HCI_ACCESS;
	memcpy(dest_pawams->vawue, &spec_pawams,
	       sizeof(stwuct dest_spec_pawams));
	w = nci_cowe_conn_cweate(ndev, NCI_DESTINATION_NFCEE, 1,
				 sizeof(stwuct cowe_conn_cweate_dest_spec_pawams) +
				 sizeof(stwuct dest_spec_pawams),
				 dest_pawams);
	if (w != NCI_STATUS_OK)
		goto fwee_dest_pawams;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		goto fwee_dest_pawams;

	ndev->hci_dev->init_data.gate_count = AWWAY_SIZE(st_nci_gates);
	memcpy(ndev->hci_dev->init_data.gates, st_nci_gates,
	       sizeof(st_nci_gates));

	/*
	 * Session id must incwude the dwivew name + i2c bus addw
	 * pewsistent info to discwiminate 2 identicaw chips
	 */
	dev_num = find_fiwst_zewo_bit(dev_mask, ST_NCI_NUM_DEVICES);
	if (dev_num >= ST_NCI_NUM_DEVICES) {
		w = -ENODEV;
		goto fwee_dest_pawams;
	}

	scnpwintf(ndev->hci_dev->init_data.session_id,
		  sizeof(ndev->hci_dev->init_data.session_id),
		  "%s%2x", "ST21BH", dev_num);

	w = nci_hci_dev_session_init(ndev);
	if (w != NCI_HCI_ANY_OK)
		goto fwee_dest_pawams;

	/*
	 * In factowy mode, we pwevent secuwe ewements activation
	 * by disabwing nfcee on the cuwwent HCI connection id.
	 * HCI wiww be used hewe onwy fow pwopwietawy commands.
	 */
	if (test_bit(ST_NCI_FACTOWY_MODE, &info->fwags))
		w = nci_nfcee_mode_set(ndev,
				       ndev->hci_dev->conn_info->dest_pawams->id,
				       NCI_NFCEE_DISABWE);
	ewse
		w = nci_nfcee_mode_set(ndev,
				       ndev->hci_dev->conn_info->dest_pawams->id,
				       NCI_NFCEE_ENABWE);

fwee_dest_pawams:
	kfwee(dest_pawams);
	wetuwn w;
}

int st_nci_discovew_se(stwuct nci_dev *ndev)
{
	u8 white_wist[2];
	int w, ww_size = 0;
	int se_count = 0;
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	w = st_nci_hci_netwowk_init(ndev);
	if (w != 0)
		wetuwn w;

	if (test_bit(ST_NCI_FACTOWY_MODE, &info->fwags))
		wetuwn 0;

	if (info->se_info.se_status->is_uicc_pwesent)
		white_wist[ww_size++] = ST_NCI_UICC_HOST_ID;
	if (info->se_info.se_status->is_ese_pwesent)
		white_wist[ww_size++] = ST_NCI_ESE_HOST_ID;

	if (ww_size) {
		w = nci_hci_set_pawam(ndev, NCI_HCI_ADMIN_GATE,
				      NCI_HCI_ADMIN_PAWAM_WHITEWIST,
				      white_wist, ww_size);
		if (w != NCI_HCI_ANY_OK)
			wetuwn w;
	}

	if (info->se_info.se_status->is_uicc_pwesent) {
		nfc_add_se(ndev->nfc_dev, ST_NCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	}

	if (info->se_info.se_status->is_ese_pwesent) {
		nfc_add_se(ndev->nfc_dev, ST_NCI_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	}

	wetuwn !se_count;
}
EXPOWT_SYMBOW_GPW(st_nci_discovew_se);

int st_nci_se_io(stwuct nci_dev *ndev, u32 se_idx,
		       u8 *apdu, size_t apdu_wength,
		       se_io_cb_t cb, void *cb_context)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	switch (se_idx) {
	case ST_NCI_ESE_HOST_ID:
		info->se_info.cb = cb;
		info->se_info.cb_context = cb_context;
		mod_timew(&info->se_info.bwi_timew, jiffies +
			  msecs_to_jiffies(info->se_info.wt_timeout));
		info->se_info.bwi_active = twue;
		wetuwn nci_hci_send_event(ndev, ST_NCI_APDU_WEADEW_GATE,
					ST_NCI_EVT_TWANSMIT_DATA, apdu,
					apdu_wength);
	defauwt:
		/* Need to fwee cb_context hewe as at the moment we can't
		 * cweawwy indicate to the cawwew if the cawwback function
		 * wouwd be cawwed (and fwee it) ow not. In both cases a
		 * negative vawue may be wetuwned to the cawwew.
		 */
		kfwee(cb_context);
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW(st_nci_se_io);

static void st_nci_se_wt_timeout(stwuct timew_wist *t)
{
	/*
	 * No answew fwom the secuwe ewement
	 * within the defined timeout.
	 * Wet's send a weset wequest as wecovewy pwoceduwe.
	 * Accowding to the situation, we fiwst twy to send a softwawe weset
	 * to the secuwe ewement. If the next command is stiww not
	 * answewing in time, we send to the CWF a secuwe ewement hawdwawe
	 * weset wequest.
	 */
	/* hawdwawe weset managed thwough VCC_UICC_OUT powew suppwy */
	u8 pawam = 0x01;
	stwuct st_nci_info *info = fwom_timew(info, t, se_info.bwi_timew);

	info->se_info.bwi_active = fawse;

	if (!info->se_info.xch_ewwow) {
		info->se_info.xch_ewwow = twue;
		nci_hci_send_event(info->ndwc->ndev, ST_NCI_APDU_WEADEW_GATE,
				ST_NCI_EVT_SE_SOFT_WESET, NUWW, 0);
	} ewse {
		info->se_info.xch_ewwow = fawse;
		nci_hci_send_event(info->ndwc->ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_EVT_SE_HAWD_WESET, &pawam, 1);
	}
	info->se_info.cb(info->se_info.cb_context, NUWW, 0, -ETIME);
}

static void st_nci_se_activation_timeout(stwuct timew_wist *t)
{
	stwuct st_nci_info *info = fwom_timew(info, t,
					      se_info.se_active_timew);

	info->se_info.se_active = fawse;

	compwete(&info->se_info.weq_compwetion);
}

int st_nci_se_init(stwuct nci_dev *ndev, stwuct st_nci_se_status *se_status)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	init_compwetion(&info->se_info.weq_compwetion);
	/* initiawize timews */
	timew_setup(&info->se_info.bwi_timew, st_nci_se_wt_timeout, 0);
	info->se_info.bwi_active = fawse;

	timew_setup(&info->se_info.se_active_timew,
		    st_nci_se_activation_timeout, 0);
	info->se_info.se_active = fawse;

	info->se_info.xch_ewwow = fawse;

	info->se_info.wt_timeout =
		ST_NCI_BWI_TO_TIMEOUT(ST_NCI_ATW_DEFAUWT_BWI);

	info->se_info.se_status = se_status;

	wetuwn 0;
}
EXPOWT_SYMBOW(st_nci_se_init);

void st_nci_se_deinit(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	if (info->se_info.bwi_active)
		dew_timew_sync(&info->se_info.bwi_timew);
	if (info->se_info.se_active)
		dew_timew_sync(&info->se_info.se_active_timew);

	info->se_info.se_active = fawse;
	info->se_info.bwi_active = fawse;
}
EXPOWT_SYMBOW(st_nci_se_deinit);

