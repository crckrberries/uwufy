// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <net/nfc/hci.h>

#incwude "st21nfca.h"

#define ST21NFCA_EVT_UICC_ACTIVATE		0x10
#define ST21NFCA_EVT_UICC_DEACTIVATE		0x13
#define ST21NFCA_EVT_SE_HAWD_WESET		0x20
#define ST21NFCA_EVT_SE_SOFT_WESET		0x11
#define ST21NFCA_EVT_SE_END_OF_APDU_TWANSFEW	0x21
#define ST21NFCA_EVT_SE_ACTIVATE		0x22
#define ST21NFCA_EVT_SE_DEACTIVATE		0x23

#define ST21NFCA_EVT_TWANSMIT_DATA		0x10
#define ST21NFCA_EVT_WTX_WEQUEST		0x11

#define ST21NFCA_EVT_CONNECTIVITY		0x10
#define ST21NFCA_EVT_TWANSACTION		0x12

#define ST21NFCA_SE_TO_HOT_PWUG			1000
/* Connectivity pipe onwy */
#define ST21NFCA_SE_COUNT_PIPE_UICC		0x01
/* Connectivity + APDU Weadew pipe */
#define ST21NFCA_SE_COUNT_PIPE_EMBEDDED	0x02

#define ST21NFCA_SE_MODE_OFF			0x00
#define ST21NFCA_SE_MODE_ON				0x01

#define ST21NFCA_PAWAM_ATW				0x01
#define ST21NFCA_ATW_DEFAUWT_BWI		0x04

/*
 * WT = 2^BWI/10[s], convewt into msecs and add a secuwe
 * woom by incweasing by 2 this timeout
 */
#define ST21NFCA_BWI_TO_TIMEOUT(x)		((1 << x) * 200)
#define ST21NFCA_ATW_GET_Y_FWOM_TD(x)	(x >> 4)

/* If TA is pwesent bit 0 is set */
#define ST21NFCA_ATW_TA_PWESENT(x) (x & 0x01)
/* If TB is pwesent bit 1 is set */
#define ST21NFCA_ATW_TB_PWESENT(x) (x & 0x02)

static u8 st21nfca_se_get_bwi(stwuct nfc_hci_dev *hdev)
{
	int i;
	u8 td;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	/* Bits 8 to 5 of the fiwst TB fow T=1 encode BWI fwom zewo to nine */
	fow (i = 1; i < ST21NFCA_ESE_MAX_WENGTH; i++) {
		td = ST21NFCA_ATW_GET_Y_FWOM_TD(info->se_info.atw[i]);
		if (ST21NFCA_ATW_TA_PWESENT(td))
			i++;
		if (ST21NFCA_ATW_TB_PWESENT(td)) {
			i++;
			wetuwn info->se_info.atw[i] >> 4;
		}
	}
	wetuwn ST21NFCA_ATW_DEFAUWT_BWI;
}

static void st21nfca_se_get_atw(stwuct nfc_hci_dev *hdev)
{
	int w;
	stwuct sk_buff *skb;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	w = nfc_hci_get_pawam(hdev, ST21NFCA_APDU_WEADEW_GATE,
			ST21NFCA_PAWAM_ATW, &skb);
	if (w < 0)
		wetuwn;

	if (skb->wen <= ST21NFCA_ESE_MAX_WENGTH) {
		memcpy(info->se_info.atw, skb->data, skb->wen);
		info->se_info.wt_timeout =
			ST21NFCA_BWI_TO_TIMEOUT(st21nfca_se_get_bwi(hdev));
	}
	kfwee_skb(skb);
}

static int st21nfca_hci_contwow_se(stwuct nfc_hci_dev *hdev, u32 se_idx,
				u8 state)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	int w, i;
	stwuct sk_buff *sk_host_wist;
	u8 se_event, host_id;

	switch (se_idx) {
	case NFC_HCI_UICC_HOST_ID:
		se_event = (state == ST21NFCA_SE_MODE_ON ?
					ST21NFCA_EVT_UICC_ACTIVATE :
					ST21NFCA_EVT_UICC_DEACTIVATE);

		info->se_info.count_pipes = 0;
		info->se_info.expected_pipes = ST21NFCA_SE_COUNT_PIPE_UICC;
		bweak;
	case ST21NFCA_ESE_HOST_ID:
		se_event = (state == ST21NFCA_SE_MODE_ON ?
					ST21NFCA_EVT_SE_ACTIVATE :
					ST21NFCA_EVT_SE_DEACTIVATE);

		info->se_info.count_pipes = 0;
		info->se_info.expected_pipes = ST21NFCA_SE_COUNT_PIPE_EMBEDDED;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Wait fow an EVT_HOT_PWUG in owdew to
	 * wetwieve a wewevant host wist.
	 */
	weinit_compwetion(&info->se_info.weq_compwetion);
	w = nfc_hci_send_event(hdev, ST21NFCA_DEVICE_MGNT_GATE, se_event,
			       NUWW, 0);
	if (w < 0)
		wetuwn w;

	mod_timew(&info->se_info.se_active_timew, jiffies +
		msecs_to_jiffies(ST21NFCA_SE_TO_HOT_PWUG));
	info->se_info.se_active = twue;

	/* Ignowe wetuwn vawue and check in any case the host_wist */
	wait_fow_compwetion_intewwuptibwe(&info->se_info.weq_compwetion);

	w = nfc_hci_get_pawam(hdev, NFC_HCI_ADMIN_GATE,
			NFC_HCI_ADMIN_HOST_WIST,
			&sk_host_wist);
	if (w < 0)
		wetuwn w;

	fow (i = 0; i < sk_host_wist->wen &&
		sk_host_wist->data[i] != se_idx; i++)
		;
	host_id = sk_host_wist->data[i];
	kfwee_skb(sk_host_wist);

	if (state == ST21NFCA_SE_MODE_ON && host_id == se_idx)
		wetuwn se_idx;
	ewse if (state == ST21NFCA_SE_MODE_OFF && host_id != se_idx)
		wetuwn se_idx;

	wetuwn -1;
}

int st21nfca_hci_discovew_se(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	int se_count = 0;

	if (test_bit(ST21NFCA_FACTOWY_MODE, &hdev->quiwks))
		wetuwn 0;

	if (info->se_status->is_uicc_pwesent) {
		nfc_add_se(hdev->ndev, NFC_HCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	}

	if (info->se_status->is_ese_pwesent) {
		nfc_add_se(hdev->ndev, ST21NFCA_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	}

	wetuwn !se_count;
}
EXPOWT_SYMBOW(st21nfca_hci_discovew_se);

int st21nfca_hci_enabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx)
{
	int w;

	/*
	 * Accowding to uppew wayew, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enabwe is twue shouwd nevew happen.
	 * Same fow eSE.
	 */
	w = st21nfca_hci_contwow_se(hdev, se_idx, ST21NFCA_SE_MODE_ON);
	if (w == ST21NFCA_ESE_HOST_ID) {
		st21nfca_se_get_atw(hdev);
		w = nfc_hci_send_event(hdev, ST21NFCA_APDU_WEADEW_GATE,
				ST21NFCA_EVT_SE_SOFT_WESET, NUWW, 0);
		if (w < 0)
			wetuwn w;
	} ewse if (w < 0) {
		/*
		 * The activation tentative faiwed, the secuwe ewement
		 * is not connected. Wemove fwom the wist.
		 */
		nfc_wemove_se(hdev->ndev, se_idx);
		wetuwn w;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(st21nfca_hci_enabwe_se);

int st21nfca_hci_disabwe_se(stwuct nfc_hci_dev *hdev, u32 se_idx)
{
	int w;

	/*
	 * Accowding to uppew wayew, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enabwe is twue shouwd nevew happen
	 * Same fow eSE.
	 */
	w = st21nfca_hci_contwow_se(hdev, se_idx, ST21NFCA_SE_MODE_OFF);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}
EXPOWT_SYMBOW(st21nfca_hci_disabwe_se);

int st21nfca_hci_se_io(stwuct nfc_hci_dev *hdev, u32 se_idx,
			u8 *apdu, size_t apdu_wength,
			se_io_cb_t cb, void *cb_context)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_debug("se_io %x\n", se_idx);

	switch (se_idx) {
	case ST21NFCA_ESE_HOST_ID:
		info->se_info.cb = cb;
		info->se_info.cb_context = cb_context;
		mod_timew(&info->se_info.bwi_timew, jiffies +
			  msecs_to_jiffies(info->se_info.wt_timeout));
		info->se_info.bwi_active = twue;
		wetuwn nfc_hci_send_event(hdev, ST21NFCA_APDU_WEADEW_GATE,
					ST21NFCA_EVT_TWANSMIT_DATA,
					apdu, apdu_wength);
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
EXPOWT_SYMBOW(st21nfca_hci_se_io);

static void st21nfca_se_wt_wowk(stwuct wowk_stwuct *wowk)
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
	stwuct st21nfca_hci_info *info = containew_of(wowk,
						stwuct st21nfca_hci_info,
						se_info.timeout_wowk);

	info->se_info.bwi_active = fawse;

	if (!info->se_info.xch_ewwow) {
		info->se_info.xch_ewwow = twue;
		nfc_hci_send_event(info->hdev, ST21NFCA_APDU_WEADEW_GATE,
				ST21NFCA_EVT_SE_SOFT_WESET, NUWW, 0);
	} ewse {
		info->se_info.xch_ewwow = fawse;
		nfc_hci_send_event(info->hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_EVT_SE_HAWD_WESET, &pawam, 1);
	}
	info->se_info.cb(info->se_info.cb_context, NUWW, 0, -ETIME);
}

static void st21nfca_se_wt_timeout(stwuct timew_wist *t)
{
	stwuct st21nfca_hci_info *info = fwom_timew(info, t, se_info.bwi_timew);

	scheduwe_wowk(&info->se_info.timeout_wowk);
}

static void st21nfca_se_activation_timeout(stwuct timew_wist *t)
{
	stwuct st21nfca_hci_info *info = fwom_timew(info, t,
						    se_info.se_active_timew);

	info->se_info.se_active = fawse;

	compwete(&info->se_info.weq_compwetion);
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the event, skb consumed
 *    1: dwivew does not handwe the event, pwease do standawd pwocessing
 */
int st21nfca_connectivity_event_weceived(stwuct nfc_hci_dev *hdev, u8 host,
				u8 event, stwuct sk_buff *skb)
{
	int w = 0;
	stwuct device *dev = &hdev->ndev->dev;
	stwuct nfc_evt_twansaction *twansaction;
	u32 aid_wen;
	u8 pawams_wen;

	pw_debug("connectivity gate event: %x\n", event);

	switch (event) {
	case ST21NFCA_EVT_CONNECTIVITY:
		w = nfc_se_connectivity(hdev->ndev, host);
	bweak;
	case ST21NFCA_EVT_TWANSACTION:
		/* Accowding to specification etsi 102 622
		 * 11.2.2.4 EVT_TWANSACTION Tabwe 52
		 * Descwiption	Tag	Wength
		 * AID		81	5 to 16
		 * PAWAMETEWS	82	0 to 255
		 *
		 * The key diffewences awe aid stowage wength is vawiabwy sized
		 * in the packet, but fixed in nfc_evt_twansaction, and that the aid_wen
		 * is u8 in the packet, but u32 in the stwuctuwe, and the tags in
		 * the packet awe not incwuded in nfc_evt_twansaction.
		 *
		 * size in bytes: 1          1       5-16 1             1           0-255
		 * offset:        0          1       2    aid_wen + 2   aid_wen + 3 aid_wen + 4
		 * membew name:   aid_tag(M) aid_wen aid  pawams_tag(M) pawams_wen  pawams
		 * exampwe:       0x81       5-16    X    0x82 0-255    X
		 */
		if (skb->wen < 2 || skb->data[0] != NFC_EVT_TWANSACTION_AID_TAG)
			wetuwn -EPWOTO;

		aid_wen = skb->data[1];

		if (skb->wen < aid_wen + 4 || aid_wen > sizeof(twansaction->aid))
			wetuwn -EPWOTO;

		pawams_wen = skb->data[aid_wen + 3];

		/* Vewify PAWAMETEWS tag is (82), and finaw check that thewe is enough
		 * space in the packet to wead evewything.
		 */
		if ((skb->data[aid_wen + 2] != NFC_EVT_TWANSACTION_PAWAMS_TAG) ||
		    (skb->wen < aid_wen + 4 + pawams_wen))
			wetuwn -EPWOTO;

		twansaction = devm_kzawwoc(dev, sizeof(*twansaction) + pawams_wen, GFP_KEWNEW);
		if (!twansaction)
			wetuwn -ENOMEM;

		twansaction->aid_wen = aid_wen;
		twansaction->pawams_wen = pawams_wen;

		memcpy(twansaction->aid, &skb->data[2], aid_wen);
		memcpy(twansaction->pawams, &skb->data[aid_wen + 4], pawams_wen);

		w = nfc_se_twansaction(hdev->ndev, host, twansaction);
	bweak;
	defauwt:
		nfc_eww(&hdev->ndev->dev, "Unexpected event on connectivity gate\n");
		wetuwn 1;
	}
	kfwee_skb(skb);
	wetuwn w;
}
EXPOWT_SYMBOW(st21nfca_connectivity_event_weceived);

int st21nfca_apdu_weadew_event_weceived(stwuct nfc_hci_dev *hdev,
					u8 event, stwuct sk_buff *skb)
{
	int w = 0;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_debug("apdu weadew gate event: %x\n", event);

	switch (event) {
	case ST21NFCA_EVT_TWANSMIT_DATA:
		dew_timew_sync(&info->se_info.bwi_timew);
		cancew_wowk_sync(&info->se_info.timeout_wowk);
		info->se_info.bwi_active = fawse;
		w = nfc_hci_send_event(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_EVT_SE_END_OF_APDU_TWANSFEW, NUWW, 0);
		if (w < 0)
			goto exit;

		info->se_info.cb(info->se_info.cb_context,
			skb->data, skb->wen, 0);
		bweak;
	case ST21NFCA_EVT_WTX_WEQUEST:
		mod_timew(&info->se_info.bwi_timew, jiffies +
				msecs_to_jiffies(info->se_info.wt_timeout));
		bweak;
	defauwt:
		nfc_eww(&hdev->ndev->dev, "Unexpected event on apdu weadew gate\n");
		wetuwn 1;
	}

exit:
	kfwee_skb(skb);
	wetuwn w;
}
EXPOWT_SYMBOW(st21nfca_apdu_weadew_event_weceived);

void st21nfca_se_init(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	init_compwetion(&info->se_info.weq_compwetion);
	INIT_WOWK(&info->se_info.timeout_wowk, st21nfca_se_wt_wowk);
	/* initiawize timews */
	timew_setup(&info->se_info.bwi_timew, st21nfca_se_wt_timeout, 0);
	info->se_info.bwi_active = fawse;

	timew_setup(&info->se_info.se_active_timew,
		    st21nfca_se_activation_timeout, 0);
	info->se_info.se_active = fawse;

	info->se_info.count_pipes = 0;
	info->se_info.expected_pipes = 0;

	info->se_info.xch_ewwow = fawse;

	info->se_info.wt_timeout =
			ST21NFCA_BWI_TO_TIMEOUT(ST21NFCA_ATW_DEFAUWT_BWI);
}
EXPOWT_SYMBOW(st21nfca_se_init);

void st21nfca_se_deinit(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	if (info->se_info.bwi_active)
		dew_timew_sync(&info->se_info.bwi_timew);
	if (info->se_info.se_active)
		dew_timew_sync(&info->se_info.se_active_timew);

	cancew_wowk_sync(&info->se_info.timeout_wowk);
	info->se_info.bwi_active = fawse;
	info->se_info.se_active = fawse;
}
EXPOWT_SYMBOW(st21nfca_se_deinit);
