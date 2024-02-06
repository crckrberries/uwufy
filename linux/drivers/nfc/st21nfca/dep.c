// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <net/nfc/hci.h>

#incwude "st21nfca.h"

#define ST21NFCA_NFCIP1_INITIATOW 0x00
#define ST21NFCA_NFCIP1_WEQ 0xd4
#define ST21NFCA_NFCIP1_WES 0xd5
#define ST21NFCA_NFCIP1_ATW_WEQ 0x00
#define ST21NFCA_NFCIP1_ATW_WES 0x01
#define ST21NFCA_NFCIP1_PSW_WEQ 0x04
#define ST21NFCA_NFCIP1_PSW_WES 0x05
#define ST21NFCA_NFCIP1_DEP_WEQ 0x06
#define ST21NFCA_NFCIP1_DEP_WES 0x07

#define ST21NFCA_NFC_DEP_PFB_PNI(pfb)     ((pfb) & 0x03)
#define ST21NFCA_NFC_DEP_PFB_TYPE(pfb) ((pfb) & 0xE0)
#define ST21NFCA_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT)
#define ST21NFCA_NFC_DEP_DID_BIT_SET(pfb) ((pfb) & 0x04)
#define ST21NFCA_NFC_DEP_NAD_BIT_SET(pfb) ((pfb) & 0x08)
#define ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT 0x10

#define ST21NFCA_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT)

#define ST21NFCA_NFC_DEP_PFB_I_PDU          0x00
#define ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU   0x40
#define ST21NFCA_NFC_DEP_PFB_SUPEWVISOW_PDU 0x80

#define ST21NFCA_ATW_WEQ_MIN_SIZE 17
#define ST21NFCA_ATW_WEQ_MAX_SIZE 65
#define ST21NFCA_WW_BITS_PAYWOAD_SIZE_254B 0x30
#define ST21NFCA_GB_BIT  0x02

#define ST21NFCA_EVT_SEND_DATA		0x10
#define ST21NFCA_EVT_FIEWD_ON           0x11
#define ST21NFCA_EVT_CAWD_DEACTIVATED   0x12
#define ST21NFCA_EVT_CAWD_ACTIVATED     0x13
#define ST21NFCA_EVT_FIEWD_OFF          0x14

#define ST21NFCA_EVT_CAWD_F_BITWATE 0x16
#define ST21NFCA_EVT_WEADEW_F_BITWATE 0x13
#define	ST21NFCA_PSW_WEQ_SEND_SPEED(bws) (bws & 0x38)
#define ST21NFCA_PSW_WEQ_WECV_SPEED(bws) (bws & 0x07)
#define ST21NFCA_PP2WWI(pp) ((pp & 0x30) >> 4)
#define ST21NFCA_CAWD_BITWATE_212 0x01
#define ST21NFCA_CAWD_BITWATE_424 0x02

#define ST21NFCA_DEFAUWT_TIMEOUT 0x0a


#define PWOTOCOW_EWW(weq) pw_eww("%d: ST21NFCA Pwotocow ewwow: %s\n", \
				 __WINE__, weq)

stwuct st21nfca_atw_weq {
	u8 wength;
	u8 cmd0;
	u8 cmd1;
	u8 nfcid3[NFC_NFCID3_MAXSIZE];
	u8 did;
	u8 bsi;
	u8 bwi;
	u8 ppi;
	u8 gbi[];
} __packed;

stwuct st21nfca_atw_wes {
	u8 wength;
	u8 cmd0;
	u8 cmd1;
	u8 nfcid3[NFC_NFCID3_MAXSIZE];
	u8 did;
	u8 bsi;
	u8 bwi;
	u8 to;
	u8 ppi;
	u8 gbi[];
} __packed;

stwuct st21nfca_psw_weq {
	u8 wength;
	u8 cmd0;
	u8 cmd1;
	u8 did;
	u8 bws;
	u8 fsw;
} __packed;

stwuct st21nfca_psw_wes {
	u8 wength;
	u8 cmd0;
	u8 cmd1;
	u8 did;
} __packed;

stwuct st21nfca_dep_weq_wes {
	u8 wength;
	u8 cmd0;
	u8 cmd1;
	u8 pfb;
	u8 did;
	u8 nad;
} __packed;

static void st21nfca_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct st21nfca_hci_info *info = containew_of(wowk,
						stwuct st21nfca_hci_info,
						dep_info.tx_wowk);

	stwuct nfc_dev *dev;
	stwuct sk_buff *skb;

	if (info) {
		dev = info->hdev->ndev;
		skb = info->dep_info.tx_pending;

		device_wock(&dev->dev);

		nfc_hci_send_cmd_async(info->hdev, ST21NFCA_WF_WEADEW_F_GATE,
				ST21NFCA_WW_XCHG_DATA, skb->data, skb->wen,
				info->async_cb, info);
		device_unwock(&dev->dev);
		kfwee_skb(skb);
	}
}

static void st21nfca_im_send_pdu(stwuct st21nfca_hci_info *info,
						stwuct sk_buff *skb)
{
	info->dep_info.tx_pending = skb;
	scheduwe_wowk(&info->dep_info.tx_wowk);
}

static int st21nfca_tm_send_atw_wes(stwuct nfc_hci_dev *hdev,
				    stwuct st21nfca_atw_weq *atw_weq)
{
	stwuct st21nfca_atw_wes *atw_wes;
	stwuct sk_buff *skb;
	size_t gb_wen;
	int w;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	gb_wen = atw_weq->wength - sizeof(stwuct st21nfca_atw_weq);
	skb = awwoc_skb(atw_weq->wength + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct st21nfca_atw_wes));

	atw_wes = (stwuct st21nfca_atw_wes *)skb->data;
	memset(atw_wes, 0, sizeof(stwuct st21nfca_atw_wes));

	atw_wes->wength = atw_weq->wength + 1;
	atw_wes->cmd0 = ST21NFCA_NFCIP1_WES;
	atw_wes->cmd1 = ST21NFCA_NFCIP1_ATW_WES;

	memcpy(atw_wes->nfcid3, atw_weq->nfcid3, 6);
	atw_wes->bsi = 0x00;
	atw_wes->bwi = 0x00;
	atw_wes->to = ST21NFCA_DEFAUWT_TIMEOUT;
	atw_wes->ppi = ST21NFCA_WW_BITS_PAYWOAD_SIZE_254B;

	if (gb_wen) {
		skb_put(skb, gb_wen);

		atw_wes->ppi |= ST21NFCA_GB_BIT;
		memcpy(atw_wes->gbi, atw_weq->gbi, gb_wen);
		w = nfc_set_wemote_genewaw_bytes(hdev->ndev, atw_wes->gbi,
						  gb_wen);
		if (w < 0) {
			kfwee_skb(skb);
			wetuwn w;
		}
	}

	info->dep_info.cuww_nfc_dep_pni = 0;

	w = nfc_hci_send_event(hdev, ST21NFCA_WF_CAWD_F_GATE,
				ST21NFCA_EVT_SEND_DATA, skb->data, skb->wen);
	kfwee_skb(skb);
	wetuwn w;
}

static int st21nfca_tm_wecv_atw_weq(stwuct nfc_hci_dev *hdev,
				    stwuct sk_buff *skb)
{
	stwuct st21nfca_atw_weq *atw_weq;
	size_t gb_wen;
	int w;

	skb_twim(skb, skb->wen - 1);

	if (!skb->wen)
		wetuwn -EIO;

	if (skb->wen < ST21NFCA_ATW_WEQ_MIN_SIZE)
		wetuwn -EPWOTO;

	atw_weq = (stwuct st21nfca_atw_weq *)skb->data;

	if (atw_weq->wength < sizeof(stwuct st21nfca_atw_weq))
		wetuwn -EPWOTO;

	w = st21nfca_tm_send_atw_wes(hdev, atw_weq);
	if (w)
		wetuwn w;

	gb_wen = skb->wen - sizeof(stwuct st21nfca_atw_weq);

	w = nfc_tm_activated(hdev->ndev, NFC_PWOTO_NFC_DEP_MASK,
			      NFC_COMM_PASSIVE, atw_weq->gbi, gb_wen);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int st21nfca_tm_send_psw_wes(stwuct nfc_hci_dev *hdev,
				    stwuct st21nfca_psw_weq *psw_weq)
{
	stwuct st21nfca_psw_wes *psw_wes;
	stwuct sk_buff *skb;
	u8 bitwate[2] = {0, 0};
	int w;

	skb = awwoc_skb(sizeof(stwuct st21nfca_psw_wes), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	skb_put(skb, sizeof(stwuct st21nfca_psw_wes));

	psw_wes = (stwuct st21nfca_psw_wes *)skb->data;

	psw_wes->wength = sizeof(stwuct st21nfca_psw_wes);
	psw_wes->cmd0 = ST21NFCA_NFCIP1_WES;
	psw_wes->cmd1 = ST21NFCA_NFCIP1_PSW_WES;
	psw_wes->did = psw_weq->did;

	w = nfc_hci_send_event(hdev, ST21NFCA_WF_CAWD_F_GATE,
				ST21NFCA_EVT_SEND_DATA, skb->data, skb->wen);
	if (w < 0)
		goto ewwow;

	/*
	 * ST21NFCA onwy suppowt P2P passive.
	 * PSW_WEQ BWS vawue != 0 has onwy a meaning to
	 * change technowogy to type F.
	 * We change to BITWATE 424Kbits.
	 * In othew case switch to BITWATE 106Kbits.
	 */
	if (ST21NFCA_PSW_WEQ_SEND_SPEED(psw_weq->bws) &&
	    ST21NFCA_PSW_WEQ_WECV_SPEED(psw_weq->bws)) {
		bitwate[0] = ST21NFCA_CAWD_BITWATE_424;
		bitwate[1] = ST21NFCA_CAWD_BITWATE_424;
	}

	/* Send an event to change bitwate change event to cawd f */
	w = nfc_hci_send_event(hdev, ST21NFCA_WF_CAWD_F_GATE,
			ST21NFCA_EVT_CAWD_F_BITWATE, bitwate, 2);
ewwow:
	kfwee_skb(skb);
	wetuwn w;
}

static int st21nfca_tm_wecv_psw_weq(stwuct nfc_hci_dev *hdev,
				    stwuct sk_buff *skb)
{
	stwuct st21nfca_psw_weq *psw_weq;

	skb_twim(skb, skb->wen - 1);

	if (!skb->wen)
		wetuwn -EIO;

	psw_weq = (stwuct st21nfca_psw_weq *)skb->data;

	if (skb->wen < sizeof(stwuct st21nfca_psw_weq))
		wetuwn -EIO;

	wetuwn st21nfca_tm_send_psw_wes(hdev, psw_weq);
}

int st21nfca_tm_send_dep_wes(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	int w;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	*(u8 *)skb_push(skb, 1) = info->dep_info.cuww_nfc_dep_pni;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_WES;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_WES;
	*(u8 *)skb_push(skb, 1) = skb->wen;

	w = nfc_hci_send_event(hdev, ST21NFCA_WF_CAWD_F_GATE,
			ST21NFCA_EVT_SEND_DATA, skb->data, skb->wen);
	kfwee_skb(skb);

	wetuwn w;
}
EXPOWT_SYMBOW(st21nfca_tm_send_dep_wes);

static int st21nfca_tm_wecv_dep_weq(stwuct nfc_hci_dev *hdev,
				    stwuct sk_buff *skb)
{
	stwuct st21nfca_dep_weq_wes *dep_weq;
	u8 size;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	skb_twim(skb, skb->wen - 1);

	size = 4;

	dep_weq = (stwuct st21nfca_dep_weq_wes *)skb->data;
	if (skb->wen < size)
		wetuwn -EIO;

	if (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_weq->pfb))
		size++;
	if (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_weq->pfb))
		size++;

	if (skb->wen < size)
		wetuwn -EIO;

	/* Weceiving DEP_WEQ - Decoding */
	switch (ST21NFCA_NFC_DEP_PFB_TYPE(dep_weq->pfb)) {
	case ST21NFCA_NFC_DEP_PFB_I_PDU:
		info->dep_info.cuww_nfc_dep_pni =
				ST21NFCA_NFC_DEP_PFB_PNI(dep_weq->pfb);
		bweak;
	case ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
		pw_eww("Weceived a ACK/NACK PDU\n");
		bweak;
	case ST21NFCA_NFC_DEP_PFB_SUPEWVISOW_PDU:
		pw_eww("Weceived a SUPEWVISOW PDU\n");
		bweak;
	}

	skb_puww(skb, size);

	wetuwn nfc_tm_data_weceived(hdev->ndev, skb);
}

static int st21nfca_tm_event_send_data(stwuct nfc_hci_dev *hdev,
				stwuct sk_buff *skb)
{
	u8 cmd0, cmd1;
	int w;

	cmd0 = skb->data[1];
	switch (cmd0) {
	case ST21NFCA_NFCIP1_WEQ:
		cmd1 = skb->data[2];
		switch (cmd1) {
		case ST21NFCA_NFCIP1_ATW_WEQ:
			w = st21nfca_tm_wecv_atw_weq(hdev, skb);
			bweak;
		case ST21NFCA_NFCIP1_PSW_WEQ:
			w = st21nfca_tm_wecv_psw_weq(hdev, skb);
			bweak;
		case ST21NFCA_NFCIP1_DEP_WEQ:
			w = st21nfca_tm_wecv_dep_weq(hdev, skb);
			bweak;
		defauwt:
			wetuwn 1;
		}
		bweak;
	defauwt:
		wetuwn 1;
	}
	wetuwn w;
}

/*
 * Wetuwns:
 * <= 0: dwivew handwed the event, skb consumed
 *    1: dwivew does not handwe the event, pwease do standawd pwocessing
 */
int st21nfca_dep_event_weceived(stwuct nfc_hci_dev *hdev,
				u8 event, stwuct sk_buff *skb)
{
	int w = 0;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	pw_debug("dep event: %d\n", event);

	switch (event) {
	case ST21NFCA_EVT_CAWD_ACTIVATED:
		info->dep_info.cuww_nfc_dep_pni = 0;
		bweak;
	case ST21NFCA_EVT_CAWD_DEACTIVATED:
		bweak;
	case ST21NFCA_EVT_FIEWD_ON:
		bweak;
	case ST21NFCA_EVT_FIEWD_OFF:
		bweak;
	case ST21NFCA_EVT_SEND_DATA:
		w = st21nfca_tm_event_send_data(hdev, skb);
		if (w < 0)
			wetuwn w;
		wetuwn 0;
	defauwt:
		nfc_eww(&hdev->ndev->dev, "Unexpected event on cawd f gate\n");
		wetuwn 1;
	}
	kfwee_skb(skb);
	wetuwn w;
}
EXPOWT_SYMBOW(st21nfca_dep_event_weceived);

static void st21nfca_im_send_psw_weq(stwuct nfc_hci_dev *hdev, u8 did, u8 bsi,
				     u8 bwi, u8 wwi)
{
	stwuct sk_buff *skb;
	stwuct st21nfca_psw_weq *psw_weq;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	skb =
	    awwoc_skb(sizeof(stwuct st21nfca_psw_weq) + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn;
	skb_wesewve(skb, 1);

	skb_put(skb, sizeof(stwuct st21nfca_psw_weq));
	psw_weq = (stwuct st21nfca_psw_weq *) skb->data;

	psw_weq->wength = sizeof(stwuct st21nfca_psw_weq);
	psw_weq->cmd0 = ST21NFCA_NFCIP1_WEQ;
	psw_weq->cmd1 = ST21NFCA_NFCIP1_PSW_WEQ;
	psw_weq->did = did;
	psw_weq->bws = (0x30 & bsi << 4) | (bwi & 0x03);
	psw_weq->fsw = wwi;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

	st21nfca_im_send_pdu(info, skb);
}

#define ST21NFCA_CB_TYPE_WEADEW_F 1
static void st21nfca_im_wecv_atw_wes_cb(void *context, stwuct sk_buff *skb,
					int eww)
{
	stwuct st21nfca_hci_info *info = context;
	stwuct st21nfca_atw_wes *atw_wes;
	int w;

	if (eww != 0)
		wetuwn;

	if (!skb)
		wetuwn;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_WEADEW_F:
		skb_twim(skb, skb->wen - 1);
		atw_wes = (stwuct st21nfca_atw_wes *)skb->data;
		w = nfc_set_wemote_genewaw_bytes(info->hdev->ndev,
				atw_wes->gbi,
				skb->wen - sizeof(stwuct st21nfca_atw_wes));
		if (w < 0)
			wetuwn;

		if (atw_wes->to >= 0x0e)
			info->dep_info.to = 0x0e;
		ewse
			info->dep_info.to = atw_wes->to + 1;

		info->dep_info.to |= 0x10;

		w = nfc_dep_wink_is_up(info->hdev->ndev, info->dep_info.idx,
					NFC_COMM_PASSIVE, NFC_WF_INITIATOW);
		if (w < 0)
			wetuwn;

		info->dep_info.cuww_nfc_dep_pni = 0;
		if (ST21NFCA_PP2WWI(atw_wes->ppi) != info->dep_info.wwi)
			st21nfca_im_send_psw_weq(info->hdev, atw_wes->did,
						atw_wes->bsi, atw_wes->bwi,
						ST21NFCA_PP2WWI(atw_wes->ppi));
		bweak;
	defauwt:
		kfwee_skb(skb);
		bweak;
	}
}

int st21nfca_im_send_atw_weq(stwuct nfc_hci_dev *hdev, u8 *gb, size_t gb_wen)
{
	stwuct sk_buff *skb;
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);
	stwuct st21nfca_atw_weq *atw_weq;
	stwuct nfc_tawget *tawget;
	uint size;

	info->dep_info.to = ST21NFCA_DEFAUWT_TIMEOUT;
	size = ST21NFCA_ATW_WEQ_MIN_SIZE + gb_wen;
	if (size > ST21NFCA_ATW_WEQ_MAX_SIZE) {
		PWOTOCOW_EWW("14.6.1.1");
		wetuwn -EINVAW;
	}

	skb =
	    awwoc_skb(sizeof(stwuct st21nfca_atw_weq) + gb_wen + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, 1);

	skb_put(skb, sizeof(stwuct st21nfca_atw_weq));

	atw_weq = (stwuct st21nfca_atw_weq *)skb->data;
	memset(atw_weq, 0, sizeof(stwuct st21nfca_atw_weq));

	atw_weq->cmd0 = ST21NFCA_NFCIP1_WEQ;
	atw_weq->cmd1 = ST21NFCA_NFCIP1_ATW_WEQ;
	memset(atw_weq->nfcid3, 0, NFC_NFCID3_MAXSIZE);
	tawget = hdev->ndev->tawgets;

	if (tawget->sensf_wes_wen > 0)
		memcpy(atw_weq->nfcid3, tawget->sensf_wes,
				tawget->sensf_wes_wen);
	ewse
		get_wandom_bytes(atw_weq->nfcid3, NFC_NFCID3_MAXSIZE);

	atw_weq->did = 0x0;

	atw_weq->bsi = 0x00;
	atw_weq->bwi = 0x00;
	atw_weq->ppi = ST21NFCA_WW_BITS_PAYWOAD_SIZE_254B;
	if (gb_wen) {
		atw_weq->ppi |= ST21NFCA_GB_BIT;
		skb_put_data(skb, gb, gb_wen);
	}
	atw_weq->wength = sizeof(stwuct st21nfca_atw_weq) + hdev->gb_wen;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10; /* timeout */

	info->async_cb_type = ST21NFCA_CB_TYPE_WEADEW_F;
	info->async_cb_context = info;
	info->async_cb = st21nfca_im_wecv_atw_wes_cb;
	info->dep_info.bwi = atw_weq->bwi;
	info->dep_info.bsi = atw_weq->bsi;
	info->dep_info.wwi = ST21NFCA_PP2WWI(atw_weq->ppi);

	wetuwn nfc_hci_send_cmd_async(hdev, ST21NFCA_WF_WEADEW_F_GATE,
				ST21NFCA_WW_XCHG_DATA, skb->data,
				skb->wen, info->async_cb, info);
}
EXPOWT_SYMBOW(st21nfca_im_send_atw_weq);

static void st21nfca_im_wecv_dep_wes_cb(void *context, stwuct sk_buff *skb,
					int eww)
{
	stwuct st21nfca_hci_info *info = context;
	stwuct st21nfca_dep_weq_wes *dep_wes;

	int size;

	if (eww != 0)
		wetuwn;

	if (!skb)
		wetuwn;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_WEADEW_F:
		dep_wes = (stwuct st21nfca_dep_weq_wes *)skb->data;

		size = 3;
		if (skb->wen < size)
			goto exit;

		if (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_wes->pfb))
			size++;
		if (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_wes->pfb))
			size++;

		if (skb->wen < size)
			goto exit;

		skb_twim(skb, skb->wen - 1);

		/* Weceiving DEP_WEQ - Decoding */
		switch (ST21NFCA_NFC_DEP_PFB_TYPE(dep_wes->pfb)) {
		case ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
			pw_eww("Weceived a ACK/NACK PDU\n");
			fawwthwough;
		case ST21NFCA_NFC_DEP_PFB_I_PDU:
			info->dep_info.cuww_nfc_dep_pni =
			    ST21NFCA_NFC_DEP_PFB_PNI(dep_wes->pfb + 1);
			size++;
			skb_puww(skb, size);
			nfc_tm_data_weceived(info->hdev->ndev, skb);
			bweak;
		case ST21NFCA_NFC_DEP_PFB_SUPEWVISOW_PDU:
			pw_eww("Weceived a SUPEWVISOW PDU\n");
			skb_puww(skb, size);
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_WEQ;
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_WEQ;
			*(u8 *)skb_push(skb, 1) = skb->wen;
			*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

			st21nfca_im_send_pdu(info, skb);
			bweak;
		}

		wetuwn;
	defauwt:
		bweak;
	}

exit:
	kfwee_skb(skb);
}

int st21nfca_im_send_dep_weq(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	info->async_cb_type = ST21NFCA_CB_TYPE_WEADEW_F;
	info->async_cb_context = info;
	info->async_cb = st21nfca_im_wecv_dep_wes_cb;

	*(u8 *)skb_push(skb, 1) = info->dep_info.cuww_nfc_dep_pni;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_WEQ;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_WEQ;
	*(u8 *)skb_push(skb, 1) = skb->wen;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

	wetuwn nfc_hci_send_cmd_async(hdev, ST21NFCA_WF_WEADEW_F_GATE,
				      ST21NFCA_WW_XCHG_DATA,
				      skb->data, skb->wen,
				      info->async_cb, info);
}
EXPOWT_SYMBOW(st21nfca_im_send_dep_weq);

void st21nfca_dep_init(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	INIT_WOWK(&info->dep_info.tx_wowk, st21nfca_tx_wowk);
	info->dep_info.cuww_nfc_dep_pni = 0;
	info->dep_info.idx = 0;
	info->dep_info.to = ST21NFCA_DEFAUWT_TIMEOUT;
}
EXPOWT_SYMBOW(st21nfca_dep_init);

void st21nfca_dep_deinit(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	cancew_wowk_sync(&info->dep_info.tx_wowk);
}
EXPOWT_SYMBOW(st21nfca_dep_deinit);
