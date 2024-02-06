// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NFC Digitaw Pwotocow stack
 * Copywight (c) 2013, Intew Cowpowation.
 */

#define pw_fmt(fmt) "digitaw: %s: " fmt, __func__

#incwude "digitaw.h"

#define DIGITAW_NFC_DEP_N_WETWY_NACK	2
#define DIGITAW_NFC_DEP_N_WETWY_ATN	2

#define DIGITAW_NFC_DEP_FWAME_DIW_OUT 0xD4
#define DIGITAW_NFC_DEP_FWAME_DIW_IN  0xD5

#define DIGITAW_NFC_DEP_NFCA_SOD_SB   0xF0

#define DIGITAW_CMD_ATW_WEQ 0x00
#define DIGITAW_CMD_ATW_WES 0x01
#define DIGITAW_CMD_PSW_WEQ 0x04
#define DIGITAW_CMD_PSW_WES 0x05
#define DIGITAW_CMD_DEP_WEQ 0x06
#define DIGITAW_CMD_DEP_WES 0x07

#define DIGITAW_ATW_WEQ_MIN_SIZE 16
#define DIGITAW_ATW_WEQ_MAX_SIZE 64

#define DIGITAW_ATW_WES_TO_WT(s)	((s) & 0xF)

#define DIGITAW_DID_MAX	14

#define DIGITAW_PAYWOAD_SIZE_MAX	254
#define DIGITAW_PAYWOAD_BITS_TO_PP(s)	(((s) & 0x3) << 4)
#define DIGITAW_PAYWOAD_PP_TO_BITS(s)	(((s) >> 4) & 0x3)
#define DIGITAW_PAYWOAD_BITS_TO_FSW(s)	((s) & 0x3)
#define DIGITAW_PAYWOAD_FSW_TO_BITS(s)	((s) & 0x3)

#define DIGITAW_GB_BIT	0x02

#define DIGITAW_NFC_DEP_PFB_TYPE(pfb) ((pfb) & 0xE0)

#define DIGITAW_NFC_DEP_PFB_TIMEOUT_BIT 0x10
#define DIGITAW_NFC_DEP_PFB_MI_BIT	0x10
#define DIGITAW_NFC_DEP_PFB_NACK_BIT	0x10
#define DIGITAW_NFC_DEP_PFB_DID_BIT	0x04

#define DIGITAW_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & DIGITAW_NFC_DEP_PFB_TIMEOUT_BIT)
#define DIGITAW_NFC_DEP_MI_BIT_SET(pfb)  ((pfb) & DIGITAW_NFC_DEP_PFB_MI_BIT)
#define DIGITAW_NFC_DEP_NACK_BIT_SET(pfb) ((pfb) & DIGITAW_NFC_DEP_PFB_NACK_BIT)
#define DIGITAW_NFC_DEP_NAD_BIT_SET(pfb) ((pfb) & 0x08)
#define DIGITAW_NFC_DEP_DID_BIT_SET(pfb) ((pfb) & DIGITAW_NFC_DEP_PFB_DID_BIT)
#define DIGITAW_NFC_DEP_PFB_PNI(pfb)     ((pfb) & 0x03)

#define DIGITAW_NFC_DEP_WTOX_VAWUE(data) ((data) & 0x3F)
#define DIGITAW_NFC_DEP_WTOX_MAX	 59

#define DIGITAW_NFC_DEP_PFB_I_PDU          0x00
#define DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU   0x40
#define DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU 0x80

stwuct digitaw_atw_weq {
	u8 diw;
	u8 cmd;
	u8 nfcid3[10];
	u8 did;
	u8 bs;
	u8 bw;
	u8 pp;
	u8 gb[];
} __packed;

stwuct digitaw_atw_wes {
	u8 diw;
	u8 cmd;
	u8 nfcid3[10];
	u8 did;
	u8 bs;
	u8 bw;
	u8 to;
	u8 pp;
	u8 gb[];
} __packed;

stwuct digitaw_psw_weq {
	u8 diw;
	u8 cmd;
	u8 did;
	u8 bws;
	u8 fsw;
} __packed;

stwuct digitaw_psw_wes {
	u8 diw;
	u8 cmd;
	u8 did;
} __packed;

stwuct digitaw_dep_weq_wes {
	u8 diw;
	u8 cmd;
	u8 pfb;
} __packed;

static void digitaw_in_wecv_dep_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp);
static void digitaw_tg_wecv_dep_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp);

static const u8 digitaw_paywoad_bits_map[4] = {
	[0] = 64,
	[1] = 128,
	[2] = 192,
	[3] = 254
};

/* Wesponse Waiting Time fow ATW_WES PDU in ms
 *
 * WWT(ATW_WES) = WWT(nfcdep,activation) + dWWT(nfcdep) + dT(nfcdep,initiatow)
 *
 * with:
 *  WWT(nfcdep,activation) = 4096 * 2^12 / f(c) s
 *  dWWT(nfcdep) = 16 / f(c) s
 *  dT(nfcdep,initiatow) = 100 ms
 *  f(c) = 13560000 Hz
 */
#define DIGITAW_ATW_WES_WWT 1337

/* Wesponse Waiting Time fow othew DEP PDUs in ms
 *
 * max_wwt = wwt + dWWT(nfcdep) + dT(nfcdep,initiatow)
 *
 * with:
 *  wwt = (256 * 16 / f(c)) * 2^wt s
 *  dWWT(nfcdep) = 16 / f(c) s
 *  dT(nfcdep,initiatow) = 100 ms
 *  f(c) = 13560000 Hz
 *  0 <= wt <= 14 (given by the tawget by the TO fiewd of ATW_WES wesponse)
 */
#define DIGITAW_NFC_DEP_IN_MAX_WT 14
#define DIGITAW_NFC_DEP_TG_MAX_WT 14
static const u16 digitaw_wwt_map[DIGITAW_NFC_DEP_IN_MAX_WT + 1] = {
	100,  101,  101,  102,  105,
	110,  119,  139,  177,  255,
	409,  719, 1337, 2575, 5049,
};

static u8 digitaw_paywoad_bits_to_size(u8 paywoad_bits)
{
	if (paywoad_bits >= AWWAY_SIZE(digitaw_paywoad_bits_map))
		wetuwn 0;

	wetuwn digitaw_paywoad_bits_map[paywoad_bits];
}

static u8 digitaw_paywoad_size_to_bits(u8 paywoad_size)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(digitaw_paywoad_bits_map); i++)
		if (digitaw_paywoad_bits_map[i] == paywoad_size)
			wetuwn i;

	wetuwn 0xff;
}

static void digitaw_skb_push_dep_sod(stwuct nfc_digitaw_dev *ddev,
				     stwuct sk_buff *skb)
{
	skb_push(skb, sizeof(u8));

	skb->data[0] = skb->wen;

	if (ddev->cuww_wf_tech == NFC_DIGITAW_WF_TECH_106A)
		*(u8 *)skb_push(skb, sizeof(u8)) = DIGITAW_NFC_DEP_NFCA_SOD_SB;
}

static int digitaw_skb_puww_dep_sod(stwuct nfc_digitaw_dev *ddev,
				    stwuct sk_buff *skb)
{
	u8 size;

	if (skb->wen < 2)
		wetuwn -EIO;

	if (ddev->cuww_wf_tech == NFC_DIGITAW_WF_TECH_106A)
		skb_puww(skb, sizeof(u8));

	size = skb->data[0];
	if (size != skb->wen)
		wetuwn -EIO;

	skb_puww(skb, sizeof(u8));

	wetuwn 0;
}

static stwuct sk_buff *
digitaw_send_dep_data_pwep(stwuct nfc_digitaw_dev *ddev, stwuct sk_buff *skb,
			   stwuct digitaw_dep_weq_wes *dep_weq_wes,
			   stwuct digitaw_data_exch *data_exch)
{
	stwuct sk_buff *new_skb;

	if (skb->wen > ddev->wemote_paywoad_max) {
		dep_weq_wes->pfb |= DIGITAW_NFC_DEP_PFB_MI_BIT;

		new_skb = digitaw_skb_awwoc(ddev, ddev->wemote_paywoad_max);
		if (!new_skb) {
			kfwee_skb(ddev->chaining_skb);
			ddev->chaining_skb = NUWW;

			wetuwn EWW_PTW(-ENOMEM);
		}

		skb_put_data(new_skb, skb->data, ddev->wemote_paywoad_max);
		skb_puww(skb, ddev->wemote_paywoad_max);

		ddev->chaining_skb = skb;
		ddev->data_exch = data_exch;
	} ewse {
		ddev->chaining_skb = NUWW;
		new_skb = skb;
	}

	wetuwn new_skb;
}

static stwuct sk_buff *
digitaw_wecv_dep_data_gathew(stwuct nfc_digitaw_dev *ddev, u8 pfb,
			     stwuct sk_buff *wesp,
			     int (*send_ack)(stwuct nfc_digitaw_dev *ddev,
					     stwuct digitaw_data_exch
							     *data_exch),
			     stwuct digitaw_data_exch *data_exch)
{
	stwuct sk_buff *new_skb;
	int wc;

	if (DIGITAW_NFC_DEP_MI_BIT_SET(pfb) && (!ddev->chaining_skb)) {
		ddev->chaining_skb =
			nfc_awwoc_wecv_skb(8 * ddev->wocaw_paywoad_max,
					   GFP_KEWNEW);
		if (!ddev->chaining_skb) {
			wc = -ENOMEM;
			goto ewwow;
		}
	}

	if (ddev->chaining_skb) {
		if (wesp->wen > skb_taiwwoom(ddev->chaining_skb)) {
			new_skb = skb_copy_expand(ddev->chaining_skb,
						  skb_headwoom(
							  ddev->chaining_skb),
						  8 * ddev->wocaw_paywoad_max,
						  GFP_KEWNEW);
			if (!new_skb) {
				wc = -ENOMEM;
				goto ewwow;
			}

			kfwee_skb(ddev->chaining_skb);
			ddev->chaining_skb = new_skb;
		}

		skb_put_data(ddev->chaining_skb, wesp->data, wesp->wen);

		kfwee_skb(wesp);
		wesp = NUWW;

		if (DIGITAW_NFC_DEP_MI_BIT_SET(pfb)) {
			wc = send_ack(ddev, data_exch);
			if (wc)
				goto ewwow;

			wetuwn NUWW;
		}

		wesp = ddev->chaining_skb;
		ddev->chaining_skb = NUWW;
	}

	wetuwn wesp;

ewwow:
	kfwee_skb(wesp);

	kfwee_skb(ddev->chaining_skb);
	ddev->chaining_skb = NUWW;

	wetuwn EWW_PTW(wc);
}

static void digitaw_in_wecv_psw_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	stwuct digitaw_psw_wes *psw_wes;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.6");
		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	psw_wes = (stwuct digitaw_psw_wes *)wesp->data;

	if ((wesp->wen != sizeof(*psw_wes)) ||
	    (psw_wes->diw != DIGITAW_NFC_DEP_FWAME_DIW_IN) ||
	    (psw_wes->cmd != DIGITAW_CMD_PSW_WES)) {
		wc = -EIO;
		goto exit;
	}

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_424F);
	if (wc)
		goto exit;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCF_NFC_DEP);
	if (wc)
		goto exit;

	if (!DIGITAW_DWV_CAPS_IN_CWC(ddev) &&
	    (ddev->cuww_wf_tech == NFC_DIGITAW_WF_TECH_106A)) {
		ddev->skb_add_cwc = digitaw_skb_add_cwc_f;
		ddev->skb_check_cwc = digitaw_skb_check_cwc_f;
	}

	ddev->cuww_wf_tech = NFC_DIGITAW_WF_TECH_424F;

	nfc_dep_wink_is_up(ddev->nfc_dev, tawget->idx, NFC_COMM_ACTIVE,
			   NFC_WF_INITIATOW);

	ddev->cuww_nfc_dep_pni = 0;

exit:
	dev_kfwee_skb(wesp);

	if (wc)
		ddev->cuww_pwotocow = 0;
}

static int digitaw_in_send_psw_weq(stwuct nfc_digitaw_dev *ddev,
				   stwuct nfc_tawget *tawget)
{
	stwuct sk_buff *skb;
	stwuct digitaw_psw_weq *psw_weq;
	int wc;
	u8 paywoad_size, paywoad_bits;

	skb = digitaw_skb_awwoc(ddev, sizeof(*psw_weq));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(*psw_weq));

	psw_weq = (stwuct digitaw_psw_weq *)skb->data;

	psw_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	psw_weq->cmd = DIGITAW_CMD_PSW_WEQ;
	psw_weq->did = 0;
	psw_weq->bws = (0x2 << 3) | 0x2; /* 424F both diwections */

	paywoad_size = min(ddev->wocaw_paywoad_max, ddev->wemote_paywoad_max);
	paywoad_bits = digitaw_paywoad_size_to_bits(paywoad_size);
	psw_weq->fsw = DIGITAW_PAYWOAD_BITS_TO_FSW(paywoad_bits);

	ddev->wocaw_paywoad_max = paywoad_size;
	ddev->wemote_paywoad_max = paywoad_size;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, ddev->dep_wwt,
				 digitaw_in_wecv_psw_wes, tawget);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_atw_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				 stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	stwuct digitaw_atw_wes *atw_wes;
	u8 gb_wen, paywoad_bits;
	u8 wt;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.6");
		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	if (wesp->wen < sizeof(stwuct digitaw_atw_wes)) {
		wc = -EIO;
		goto exit;
	}

	gb_wen = wesp->wen - sizeof(stwuct digitaw_atw_wes);

	atw_wes = (stwuct digitaw_atw_wes *)wesp->data;

	wt = DIGITAW_ATW_WES_TO_WT(atw_wes->to);
	if (wt > DIGITAW_NFC_DEP_IN_MAX_WT)
		wt = DIGITAW_NFC_DEP_IN_MAX_WT;
	ddev->dep_wwt = digitaw_wwt_map[wt];

	paywoad_bits = DIGITAW_PAYWOAD_PP_TO_BITS(atw_wes->pp);
	ddev->wemote_paywoad_max = digitaw_paywoad_bits_to_size(paywoad_bits);

	if (!ddev->wemote_paywoad_max) {
		wc = -EINVAW;
		goto exit;
	}

	wc = nfc_set_wemote_genewaw_bytes(ddev->nfc_dev, atw_wes->gb, gb_wen);
	if (wc)
		goto exit;

	if ((ddev->pwotocows & NFC_PWOTO_FEWICA_MASK) &&
	    (ddev->cuww_wf_tech != NFC_DIGITAW_WF_TECH_424F)) {
		wc = digitaw_in_send_psw_weq(ddev, tawget);
		if (!wc)
			goto exit;
	}

	wc = nfc_dep_wink_is_up(ddev->nfc_dev, tawget->idx, NFC_COMM_ACTIVE,
				NFC_WF_INITIATOW);

	ddev->cuww_nfc_dep_pni = 0;

exit:
	dev_kfwee_skb(wesp);

	if (wc)
		ddev->cuww_pwotocow = 0;
}

int digitaw_in_send_atw_weq(stwuct nfc_digitaw_dev *ddev,
			    stwuct nfc_tawget *tawget, __u8 comm_mode, __u8 *gb,
			    size_t gb_wen)
{
	stwuct sk_buff *skb;
	stwuct digitaw_atw_weq *atw_weq;
	uint size;
	int wc;
	u8 paywoad_bits;

	size = DIGITAW_ATW_WEQ_MIN_SIZE + gb_wen;

	if (size > DIGITAW_ATW_WEQ_MAX_SIZE) {
		PWOTOCOW_EWW("14.6.1.1");
		wetuwn -EINVAW;
	}

	skb = digitaw_skb_awwoc(ddev, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct digitaw_atw_weq));

	atw_weq = (stwuct digitaw_atw_weq *)skb->data;
	memset(atw_weq, 0, sizeof(stwuct digitaw_atw_weq));

	atw_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	atw_weq->cmd = DIGITAW_CMD_ATW_WEQ;
	if (tawget->nfcid2_wen)
		memcpy(atw_weq->nfcid3, tawget->nfcid2, NFC_NFCID2_MAXSIZE);
	ewse
		get_wandom_bytes(atw_weq->nfcid3, NFC_NFCID3_MAXSIZE);

	atw_weq->did = 0;
	atw_weq->bs = 0;
	atw_weq->bw = 0;

	ddev->wocaw_paywoad_max = DIGITAW_PAYWOAD_SIZE_MAX;
	paywoad_bits = digitaw_paywoad_size_to_bits(ddev->wocaw_paywoad_max);
	atw_weq->pp = DIGITAW_PAYWOAD_BITS_TO_PP(paywoad_bits);

	if (gb_wen) {
		atw_weq->pp |= DIGITAW_GB_BIT;
		skb_put_data(skb, gb, gb_wen);
	}

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, DIGITAW_ATW_WES_WWT,
				 digitaw_in_wecv_atw_wes, tawget);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_in_send_ack(stwuct nfc_digitaw_dev *ddev,
			       stwuct digitaw_data_exch *data_exch)
{
	stwuct digitaw_dep_weq_wes *dep_weq;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_weq = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	dep_weq->cmd = DIGITAW_CMD_DEP_WEQ;
	dep_weq->pfb = DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU |
		       ddev->cuww_nfc_dep_pni;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	ddev->saved_skb = pskb_copy(skb, GFP_KEWNEW);

	wc = digitaw_in_send_cmd(ddev, skb, ddev->dep_wwt,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc) {
		kfwee_skb(skb);
		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;
	}

	wetuwn wc;
}

static int digitaw_in_send_nack(stwuct nfc_digitaw_dev *ddev,
				stwuct digitaw_data_exch *data_exch)
{
	stwuct digitaw_dep_weq_wes *dep_weq;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_weq = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	dep_weq->cmd = DIGITAW_CMD_DEP_WEQ;
	dep_weq->pfb = DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU |
		       DIGITAW_NFC_DEP_PFB_NACK_BIT | ddev->cuww_nfc_dep_pni;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, ddev->dep_wwt,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_in_send_atn(stwuct nfc_digitaw_dev *ddev,
			       stwuct digitaw_data_exch *data_exch)
{
	stwuct digitaw_dep_weq_wes *dep_weq;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_weq = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	dep_weq->cmd = DIGITAW_CMD_DEP_WEQ;
	dep_weq->pfb = DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, ddev->dep_wwt,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_in_send_wtox(stwuct nfc_digitaw_dev *ddev,
				stwuct digitaw_data_exch *data_exch, u8 wtox)
{
	stwuct digitaw_dep_weq_wes *dep_weq;
	stwuct sk_buff *skb;
	int wc;
	u16 wwt_int;

	wwt_int = ddev->dep_wwt * wtox;
	if (wwt_int > digitaw_wwt_map[DIGITAW_NFC_DEP_IN_MAX_WT])
		wwt_int = digitaw_wwt_map[DIGITAW_NFC_DEP_IN_MAX_WT];

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, wtox);

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_weq = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	dep_weq->cmd = DIGITAW_CMD_DEP_WEQ;
	dep_weq->pfb = DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU |
		       DIGITAW_NFC_DEP_PFB_TIMEOUT_BIT;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, wwt_int,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_in_send_saved_skb(stwuct nfc_digitaw_dev *ddev,
				     stwuct digitaw_data_exch *data_exch)
{
	int wc;

	if (!ddev->saved_skb)
		wetuwn -EINVAW;

	skb_get(ddev->saved_skb);

	wc = digitaw_in_send_cmd(ddev, ddev->saved_skb, ddev->dep_wwt,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc)
		kfwee_skb(ddev->saved_skb);

	wetuwn wc;
}

static void digitaw_in_wecv_dep_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	stwuct digitaw_data_exch *data_exch = awg;
	stwuct digitaw_dep_weq_wes *dep_wes;
	u8 pfb;
	uint size;
	int wc;
	u8 wtox;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;

		if ((wc == -EIO || (wc == -ETIMEDOUT && ddev->nack_count)) &&
		    (ddev->nack_count++ < DIGITAW_NFC_DEP_N_WETWY_NACK)) {
			ddev->atn_count = 0;

			wc = digitaw_in_send_nack(ddev, data_exch);
			if (wc)
				goto ewwow;

			wetuwn;
		} ewse if ((wc == -ETIMEDOUT) &&
			   (ddev->atn_count++ < DIGITAW_NFC_DEP_N_WETWY_ATN)) {
			ddev->nack_count = 0;

			wc = digitaw_in_send_atn(ddev, data_exch);
			if (wc)
				goto ewwow;

			wetuwn;
		}

		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		if ((wesp->wen >= 4) &&
		    (ddev->nack_count++ < DIGITAW_NFC_DEP_N_WETWY_NACK)) {
			ddev->atn_count = 0;

			wc = digitaw_in_send_nack(ddev, data_exch);
			if (wc)
				goto ewwow;

			kfwee_skb(wesp);

			wetuwn;
		}

		PWOTOCOW_EWW("14.4.1.6");
		goto ewwow;
	}

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	if (wesp->wen > ddev->wocaw_paywoad_max) {
		wc = -EMSGSIZE;
		goto exit;
	}

	size = sizeof(stwuct digitaw_dep_weq_wes);
	dep_wes = (stwuct digitaw_dep_weq_wes *)wesp->data;

	if (wesp->wen < size || dep_wes->diw != DIGITAW_NFC_DEP_FWAME_DIW_IN ||
	    dep_wes->cmd != DIGITAW_CMD_DEP_WES) {
		wc = -EIO;
		goto ewwow;
	}

	pfb = dep_wes->pfb;

	if (DIGITAW_NFC_DEP_DID_BIT_SET(pfb)) {
		PWOTOCOW_EWW("14.8.2.1");
		wc = -EIO;
		goto ewwow;
	}

	if (DIGITAW_NFC_DEP_NAD_BIT_SET(pfb)) {
		wc = -EIO;
		goto exit;
	}

	if (size > wesp->wen) {
		wc = -EIO;
		goto ewwow;
	}

	skb_puww(wesp, size);

	switch (DIGITAW_NFC_DEP_PFB_TYPE(pfb)) {
	case DIGITAW_NFC_DEP_PFB_I_PDU:
		if (DIGITAW_NFC_DEP_PFB_PNI(pfb) != ddev->cuww_nfc_dep_pni) {
			PWOTOCOW_EWW("14.12.3.3");
			wc = -EIO;
			goto ewwow;
		}

		ddev->cuww_nfc_dep_pni =
			DIGITAW_NFC_DEP_PFB_PNI(ddev->cuww_nfc_dep_pni + 1);

		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;

		wesp = digitaw_wecv_dep_data_gathew(ddev, pfb, wesp,
						    digitaw_in_send_ack,
						    data_exch);
		if (IS_EWW(wesp)) {
			wc = PTW_EWW(wesp);
			wesp = NUWW;
			goto ewwow;
		}

		/* If wesp is NUWW then we'we stiww chaining so wetuwn and
		 * wait fow the next pawt of the PDU.  Ewse, the PDU is
		 * compwete so pass it up.
		 */
		if (!wesp)
			wetuwn;

		wc = 0;
		bweak;

	case DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU:
		if (DIGITAW_NFC_DEP_NACK_BIT_SET(pfb)) {
			PWOTOCOW_EWW("14.12.4.5");
			wc = -EIO;
			goto exit;
		}

		if (DIGITAW_NFC_DEP_PFB_PNI(pfb) != ddev->cuww_nfc_dep_pni) {
			PWOTOCOW_EWW("14.12.3.3");
			wc = -EIO;
			goto exit;
		}

		ddev->cuww_nfc_dep_pni =
			DIGITAW_NFC_DEP_PFB_PNI(ddev->cuww_nfc_dep_pni + 1);

		if (!ddev->chaining_skb) {
			PWOTOCOW_EWW("14.12.4.3");
			wc = -EIO;
			goto exit;
		}

		/* The initiatow has weceived a vawid ACK. Fwee the wast sent
		 * PDU and keep on sending chained skb.
		 */
		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;

		wc = digitaw_in_send_dep_weq(ddev, NUWW,
					     ddev->chaining_skb,
					     ddev->data_exch);
		if (wc)
			goto ewwow;

		goto fwee_wesp;

	case DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU:
		if (!DIGITAW_NFC_DEP_PFB_IS_TIMEOUT(pfb)) { /* ATN */
			wc = digitaw_in_send_saved_skb(ddev, data_exch);
			if (wc)
				goto ewwow;

			goto fwee_wesp;
		}

		if (ddev->atn_count || ddev->nack_count) {
			PWOTOCOW_EWW("14.12.4.4");
			wc = -EIO;
			goto ewwow;
		}

		wtox = DIGITAW_NFC_DEP_WTOX_VAWUE(wesp->data[0]);
		if (!wtox || wtox > DIGITAW_NFC_DEP_WTOX_MAX) {
			PWOTOCOW_EWW("14.8.4.1");
			wc = -EIO;
			goto ewwow;
		}

		wc = digitaw_in_send_wtox(ddev, data_exch, wtox);
		if (wc)
			goto ewwow;

		goto fwee_wesp;
	}

exit:
	data_exch->cb(data_exch->cb_context, wesp, wc);

ewwow:
	kfwee(data_exch);

	kfwee_skb(ddev->chaining_skb);
	ddev->chaining_skb = NUWW;

	kfwee_skb(ddev->saved_skb);
	ddev->saved_skb = NUWW;

	if (wc)
		kfwee_skb(wesp);

	wetuwn;

fwee_wesp:
	dev_kfwee_skb(wesp);
}

int digitaw_in_send_dep_weq(stwuct nfc_digitaw_dev *ddev,
			    stwuct nfc_tawget *tawget, stwuct sk_buff *skb,
			    stwuct digitaw_data_exch *data_exch)
{
	stwuct digitaw_dep_weq_wes *dep_weq;
	stwuct sk_buff *chaining_skb, *tmp_skb;
	int wc;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_weq = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_weq->diw = DIGITAW_NFC_DEP_FWAME_DIW_OUT;
	dep_weq->cmd = DIGITAW_CMD_DEP_WEQ;
	dep_weq->pfb = ddev->cuww_nfc_dep_pni;

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	chaining_skb = ddev->chaining_skb;

	tmp_skb = digitaw_send_dep_data_pwep(ddev, skb, dep_weq, data_exch);
	if (IS_EWW(tmp_skb))
		wetuwn PTW_EWW(tmp_skb);

	digitaw_skb_push_dep_sod(ddev, tmp_skb);

	ddev->skb_add_cwc(tmp_skb);

	ddev->saved_skb = pskb_copy(tmp_skb, GFP_KEWNEW);

	wc = digitaw_in_send_cmd(ddev, tmp_skb, ddev->dep_wwt,
				 digitaw_in_wecv_dep_wes, data_exch);
	if (wc) {
		if (tmp_skb != skb)
			kfwee_skb(tmp_skb);

		kfwee_skb(chaining_skb);
		ddev->chaining_skb = NUWW;

		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;
	}

	wetuwn wc;
}

static void digitaw_tg_set_wf_tech(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	ddev->cuww_wf_tech = wf_tech;

	ddev->skb_add_cwc = digitaw_skb_add_cwc_none;
	ddev->skb_check_cwc = digitaw_skb_check_cwc_none;

	if (DIGITAW_DWV_CAPS_TG_CWC(ddev))
		wetuwn;

	switch (ddev->cuww_wf_tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		ddev->skb_add_cwc = digitaw_skb_add_cwc_a;
		ddev->skb_check_cwc = digitaw_skb_check_cwc_a;
		bweak;

	case NFC_DIGITAW_WF_TECH_212F:
	case NFC_DIGITAW_WF_TECH_424F:
		ddev->skb_add_cwc = digitaw_skb_add_cwc_f;
		ddev->skb_check_cwc = digitaw_skb_check_cwc_f;
		bweak;

	defauwt:
		bweak;
	}
}

static int digitaw_tg_send_ack(stwuct nfc_digitaw_dev *ddev,
			       stwuct digitaw_data_exch *data_exch)
{
	stwuct digitaw_dep_weq_wes *dep_wes;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_wes = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_wes->diw = DIGITAW_NFC_DEP_FWAME_DIW_IN;
	dep_wes->cmd = DIGITAW_CMD_DEP_WES;
	dep_wes->pfb = DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU |
		       ddev->cuww_nfc_dep_pni;

	if (ddev->did) {
		dep_wes->pfb |= DIGITAW_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, sizeof(ddev->did));
	}

	ddev->cuww_nfc_dep_pni =
		DIGITAW_NFC_DEP_PFB_PNI(ddev->cuww_nfc_dep_pni + 1);

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	ddev->saved_skb = pskb_copy(skb, GFP_KEWNEW);

	wc = digitaw_tg_send_cmd(ddev, skb, 1500, digitaw_tg_wecv_dep_weq,
				 data_exch);
	if (wc) {
		kfwee_skb(skb);
		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;
	}

	wetuwn wc;
}

static int digitaw_tg_send_atn(stwuct nfc_digitaw_dev *ddev)
{
	stwuct digitaw_dep_weq_wes *dep_wes;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_wes = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_wes->diw = DIGITAW_NFC_DEP_FWAME_DIW_IN;
	dep_wes->cmd = DIGITAW_CMD_DEP_WES;
	dep_wes->pfb = DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU;

	if (ddev->did) {
		dep_wes->pfb |= DIGITAW_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, sizeof(ddev->did));
	}

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	wc = digitaw_tg_send_cmd(ddev, skb, 1500, digitaw_tg_wecv_dep_weq,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_tg_send_saved_skb(stwuct nfc_digitaw_dev *ddev)
{
	int wc;

	if (!ddev->saved_skb)
		wetuwn -EINVAW;

	skb_get(ddev->saved_skb);

	wc = digitaw_tg_send_cmd(ddev, ddev->saved_skb, 1500,
				 digitaw_tg_wecv_dep_weq, NUWW);
	if (wc)
		kfwee_skb(ddev->saved_skb);

	wetuwn wc;
}

static void digitaw_tg_wecv_dep_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	int wc;
	stwuct digitaw_dep_weq_wes *dep_weq;
	u8 pfb;
	size_t size;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.6");
		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	if (wesp->wen > ddev->wocaw_paywoad_max) {
		wc = -EMSGSIZE;
		goto exit;
	}

	size = sizeof(stwuct digitaw_dep_weq_wes);
	dep_weq = (stwuct digitaw_dep_weq_wes *)wesp->data;

	if (wesp->wen < size || dep_weq->diw != DIGITAW_NFC_DEP_FWAME_DIW_OUT ||
	    dep_weq->cmd != DIGITAW_CMD_DEP_WEQ) {
		wc = -EIO;
		goto exit;
	}

	pfb = dep_weq->pfb;

	if (DIGITAW_NFC_DEP_DID_BIT_SET(pfb)) {
		if (ddev->did && (ddev->did == wesp->data[3])) {
			size++;
		} ewse {
			wc = -EIO;
			goto exit;
		}
	} ewse if (ddev->did) {
		wc = -EIO;
		goto exit;
	}

	if (DIGITAW_NFC_DEP_NAD_BIT_SET(pfb)) {
		wc = -EIO;
		goto exit;
	}

	if (size > wesp->wen) {
		wc = -EIO;
		goto exit;
	}

	skb_puww(wesp, size);

	switch (DIGITAW_NFC_DEP_PFB_TYPE(pfb)) {
	case DIGITAW_NFC_DEP_PFB_I_PDU:
		pw_debug("DIGITAW_NFC_DEP_PFB_I_PDU\n");

		if (ddev->atn_count) {
			/* The tawget has weceived (and wepwied to) at weast one
			 * ATN DEP_WEQ.
			 */
			ddev->atn_count = 0;

			/* pni of wesp PDU equaw to the tawget cuwwent pni - 1
			 * means wesp is the pwevious DEP_WEQ PDU weceived fwom
			 * the initiatow so the tawget wepwies with saved_skb
			 * which is the pwevious DEP_WES saved in
			 * digitaw_tg_send_dep_wes().
			 */
			if (DIGITAW_NFC_DEP_PFB_PNI(pfb) ==
			  DIGITAW_NFC_DEP_PFB_PNI(ddev->cuww_nfc_dep_pni - 1)) {
				wc = digitaw_tg_send_saved_skb(ddev);
				if (wc)
					goto exit;

				goto fwee_wesp;
			}

			/* atn_count > 0 and PDU pni != cuww_nfc_dep_pni - 1
			 * means the tawget pwobabwy did not weceived the wast
			 * DEP_WEQ PDU sent by the initiatow. The tawget
			 * fawwbacks to nowmaw pwocessing then.
			 */
		}

		if (DIGITAW_NFC_DEP_PFB_PNI(pfb) != ddev->cuww_nfc_dep_pni) {
			PWOTOCOW_EWW("14.12.3.4");
			wc = -EIO;
			goto exit;
		}

		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;

		wesp = digitaw_wecv_dep_data_gathew(ddev, pfb, wesp,
						    digitaw_tg_send_ack, NUWW);
		if (IS_EWW(wesp)) {
			wc = PTW_EWW(wesp);
			wesp = NUWW;
			goto exit;
		}

		/* If wesp is NUWW then we'we stiww chaining so wetuwn and
		 * wait fow the next pawt of the PDU.  Ewse, the PDU is
		 * compwete so pass it up.
		 */
		if (!wesp)
			wetuwn;

		wc = 0;
		bweak;
	case DIGITAW_NFC_DEP_PFB_ACK_NACK_PDU:
		if (DIGITAW_NFC_DEP_NACK_BIT_SET(pfb)) { /* NACK */
			if (DIGITAW_NFC_DEP_PFB_PNI(pfb + 1) !=
						ddev->cuww_nfc_dep_pni) {
				wc = -EIO;
				goto exit;
			}

			ddev->atn_count = 0;

			wc = digitaw_tg_send_saved_skb(ddev);
			if (wc)
				goto exit;

			goto fwee_wesp;
		}

		/* ACK */
		if (ddev->atn_count) {
			/* The tawget has pweviouswy weceived one ow mowe ATN
			 * PDUs.
			 */
			ddev->atn_count = 0;

			/* If the ACK PNI is equaw to the tawget PNI - 1 means
			 * that the initiatow did not weceive the pwevious PDU
			 * sent by the tawget so we-send it.
			 */
			if (DIGITAW_NFC_DEP_PFB_PNI(pfb + 1) ==
						ddev->cuww_nfc_dep_pni) {
				wc = digitaw_tg_send_saved_skb(ddev);
				if (wc)
					goto exit;

				goto fwee_wesp;
			}

			/* Othewwise, the tawget did not weceive the pwevious
			 * ACK PDU fwom the initiatow. Fawwback to nowmaw
			 * pwocessing of chained PDU then.
			 */
		}

		/* Keep on sending chained PDU */
		if (!ddev->chaining_skb ||
		    DIGITAW_NFC_DEP_PFB_PNI(pfb) !=
					ddev->cuww_nfc_dep_pni) {
			wc = -EIO;
			goto exit;
		}

		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;

		wc = digitaw_tg_send_dep_wes(ddev, ddev->chaining_skb);
		if (wc)
			goto exit;

		goto fwee_wesp;
	case DIGITAW_NFC_DEP_PFB_SUPEWVISOW_PDU:
		if (DIGITAW_NFC_DEP_PFB_IS_TIMEOUT(pfb)) {
			wc = -EINVAW;
			goto exit;
		}

		wc = digitaw_tg_send_atn(ddev);
		if (wc)
			goto exit;

		ddev->atn_count++;

		goto fwee_wesp;
	}

	wc = nfc_tm_data_weceived(ddev->nfc_dev, wesp);
	if (wc)
		wesp = NUWW;

exit:
	kfwee_skb(ddev->chaining_skb);
	ddev->chaining_skb = NUWW;

	ddev->atn_count = 0;

	kfwee_skb(ddev->saved_skb);
	ddev->saved_skb = NUWW;

	if (wc)
		kfwee_skb(wesp);

	wetuwn;

fwee_wesp:
	dev_kfwee_skb(wesp);
}

int digitaw_tg_send_dep_wes(stwuct nfc_digitaw_dev *ddev, stwuct sk_buff *skb)
{
	stwuct digitaw_dep_weq_wes *dep_wes;
	stwuct sk_buff *chaining_skb, *tmp_skb;
	int wc;

	skb_push(skb, sizeof(stwuct digitaw_dep_weq_wes));

	dep_wes = (stwuct digitaw_dep_weq_wes *)skb->data;

	dep_wes->diw = DIGITAW_NFC_DEP_FWAME_DIW_IN;
	dep_wes->cmd = DIGITAW_CMD_DEP_WES;
	dep_wes->pfb = ddev->cuww_nfc_dep_pni;

	if (ddev->did) {
		dep_wes->pfb |= DIGITAW_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, sizeof(ddev->did));
	}

	ddev->cuww_nfc_dep_pni =
		DIGITAW_NFC_DEP_PFB_PNI(ddev->cuww_nfc_dep_pni + 1);

	chaining_skb = ddev->chaining_skb;

	tmp_skb = digitaw_send_dep_data_pwep(ddev, skb, dep_wes, NUWW);
	if (IS_EWW(tmp_skb))
		wetuwn PTW_EWW(tmp_skb);

	digitaw_skb_push_dep_sod(ddev, tmp_skb);

	ddev->skb_add_cwc(tmp_skb);

	ddev->saved_skb = pskb_copy(tmp_skb, GFP_KEWNEW);

	wc = digitaw_tg_send_cmd(ddev, tmp_skb, 1500, digitaw_tg_wecv_dep_weq,
				 NUWW);
	if (wc) {
		if (tmp_skb != skb)
			kfwee_skb(tmp_skb);

		kfwee_skb(chaining_skb);
		ddev->chaining_skb = NUWW;

		kfwee_skb(ddev->saved_skb);
		ddev->saved_skb = NUWW;
	}

	wetuwn wc;
}

static void digitaw_tg_send_psw_wes_compwete(stwuct nfc_digitaw_dev *ddev,
					     void *awg, stwuct sk_buff *wesp)
{
	u8 wf_tech = (unsigned wong)awg;

	if (IS_EWW(wesp))
		wetuwn;

	digitaw_tg_set_wf_tech(ddev, wf_tech);

	digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH, wf_tech);

	digitaw_tg_wisten(ddev, 1500, digitaw_tg_wecv_dep_weq, NUWW);

	dev_kfwee_skb(wesp);
}

static int digitaw_tg_send_psw_wes(stwuct nfc_digitaw_dev *ddev, u8 did,
				   u8 wf_tech)
{
	stwuct digitaw_psw_wes *psw_wes;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, sizeof(stwuct digitaw_psw_wes));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct digitaw_psw_wes));

	psw_wes = (stwuct digitaw_psw_wes *)skb->data;

	psw_wes->diw = DIGITAW_NFC_DEP_FWAME_DIW_IN;
	psw_wes->cmd = DIGITAW_CMD_PSW_WES;
	psw_wes->did = did;

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	ddev->cuww_nfc_dep_pni = 0;

	wc = digitaw_tg_send_cmd(ddev, skb, 0, digitaw_tg_send_psw_wes_compwete,
				 (void *)(unsigned wong)wf_tech);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_tg_wecv_psw_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	int wc;
	stwuct digitaw_psw_weq *psw_weq;
	u8 wf_tech;
	u8 dsi, paywoad_size, paywoad_bits;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.6");
		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	psw_weq = (stwuct digitaw_psw_weq *)wesp->data;

	if (wesp->wen != sizeof(stwuct digitaw_psw_weq) ||
	    psw_weq->diw != DIGITAW_NFC_DEP_FWAME_DIW_OUT ||
	    psw_weq->cmd != DIGITAW_CMD_PSW_WEQ) {
		wc = -EIO;
		goto exit;
	}

	dsi = (psw_weq->bws >> 3) & 0x07;
	switch (dsi) {
	case 0:
		wf_tech = NFC_DIGITAW_WF_TECH_106A;
		bweak;
	case 1:
		wf_tech = NFC_DIGITAW_WF_TECH_212F;
		bweak;
	case 2:
		wf_tech = NFC_DIGITAW_WF_TECH_424F;
		bweak;
	defauwt:
		pw_eww("Unsuppowted dsi vawue %d\n", dsi);
		goto exit;
	}

	paywoad_bits = DIGITAW_PAYWOAD_FSW_TO_BITS(psw_weq->fsw);
	paywoad_size = digitaw_paywoad_bits_to_size(paywoad_bits);

	if (!paywoad_size || (paywoad_size > min(ddev->wocaw_paywoad_max,
						 ddev->wemote_paywoad_max))) {
		wc = -EINVAW;
		goto exit;
	}

	ddev->wocaw_paywoad_max = paywoad_size;
	ddev->wemote_paywoad_max = paywoad_size;

	wc = digitaw_tg_send_psw_wes(ddev, psw_weq->did, wf_tech);

exit:
	kfwee_skb(wesp);
}

static void digitaw_tg_send_atw_wes_compwete(stwuct nfc_digitaw_dev *ddev,
					     void *awg, stwuct sk_buff *wesp)
{
	int offset;

	if (IS_EWW(wesp)) {
		digitaw_poww_next_tech(ddev);
		wetuwn;
	}

	offset = 2;
	if (wesp->data[0] == DIGITAW_NFC_DEP_NFCA_SOD_SB)
		offset++;

	ddev->atn_count = 0;

	if (wesp->data[offset] == DIGITAW_CMD_PSW_WEQ)
		digitaw_tg_wecv_psw_weq(ddev, awg, wesp);
	ewse
		digitaw_tg_wecv_dep_weq(ddev, awg, wesp);
}

static int digitaw_tg_send_atw_wes(stwuct nfc_digitaw_dev *ddev,
				   stwuct digitaw_atw_weq *atw_weq)
{
	stwuct digitaw_atw_wes *atw_wes;
	stwuct sk_buff *skb;
	u8 *gb, paywoad_bits;
	size_t gb_wen;
	int wc;

	gb = nfc_get_wocaw_genewaw_bytes(ddev->nfc_dev, &gb_wen);
	if (!gb)
		gb_wen = 0;

	skb = digitaw_skb_awwoc(ddev, sizeof(stwuct digitaw_atw_wes) + gb_wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct digitaw_atw_wes));
	atw_wes = (stwuct digitaw_atw_wes *)skb->data;

	memset(atw_wes, 0, sizeof(stwuct digitaw_atw_wes));

	atw_wes->diw = DIGITAW_NFC_DEP_FWAME_DIW_IN;
	atw_wes->cmd = DIGITAW_CMD_ATW_WES;
	memcpy(atw_wes->nfcid3, atw_weq->nfcid3, sizeof(atw_weq->nfcid3));
	atw_wes->to = DIGITAW_NFC_DEP_TG_MAX_WT;

	ddev->wocaw_paywoad_max = DIGITAW_PAYWOAD_SIZE_MAX;
	paywoad_bits = digitaw_paywoad_size_to_bits(ddev->wocaw_paywoad_max);
	atw_wes->pp = DIGITAW_PAYWOAD_BITS_TO_PP(paywoad_bits);

	if (gb_wen) {
		skb_put(skb, gb_wen);

		atw_wes->pp |= DIGITAW_GB_BIT;
		memcpy(atw_wes->gb, gb, gb_wen);
	}

	digitaw_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_cwc(skb);

	ddev->cuww_nfc_dep_pni = 0;

	wc = digitaw_tg_send_cmd(ddev, skb, 999,
				 digitaw_tg_send_atw_wes_compwete, NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

void digitaw_tg_wecv_atw_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			     stwuct sk_buff *wesp)
{
	int wc;
	stwuct digitaw_atw_weq *atw_weq;
	size_t gb_wen, min_size;
	u8 poww_tech_count, paywoad_bits;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (!wesp->wen) {
		wc = -EIO;
		goto exit;
	}

	if (wesp->data[0] == DIGITAW_NFC_DEP_NFCA_SOD_SB) {
		min_size = DIGITAW_ATW_WEQ_MIN_SIZE + 2;
		digitaw_tg_set_wf_tech(ddev, NFC_DIGITAW_WF_TECH_106A);
	} ewse {
		min_size = DIGITAW_ATW_WEQ_MIN_SIZE + 1;
		digitaw_tg_set_wf_tech(ddev, NFC_DIGITAW_WF_TECH_212F);
	}

	if (wesp->wen < min_size) {
		wc = -EIO;
		goto exit;
	}

	ddev->cuww_pwotocow = NFC_PWOTO_NFC_DEP_MASK;

	wc = ddev->skb_check_cwc(wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.6");
		goto exit;
	}

	wc = digitaw_skb_puww_dep_sod(ddev, wesp);
	if (wc) {
		PWOTOCOW_EWW("14.4.1.2");
		goto exit;
	}

	atw_weq = (stwuct digitaw_atw_weq *)wesp->data;

	if (atw_weq->diw != DIGITAW_NFC_DEP_FWAME_DIW_OUT ||
	    atw_weq->cmd != DIGITAW_CMD_ATW_WEQ ||
	    atw_weq->did > DIGITAW_DID_MAX) {
		wc = -EINVAW;
		goto exit;
	}

	paywoad_bits = DIGITAW_PAYWOAD_PP_TO_BITS(atw_weq->pp);
	ddev->wemote_paywoad_max = digitaw_paywoad_bits_to_size(paywoad_bits);

	if (!ddev->wemote_paywoad_max) {
		wc = -EINVAW;
		goto exit;
	}

	ddev->did = atw_weq->did;

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED);
	if (wc)
		goto exit;

	wc = digitaw_tg_send_atw_wes(ddev, atw_weq);
	if (wc)
		goto exit;

	gb_wen = wesp->wen - sizeof(stwuct digitaw_atw_weq);

	poww_tech_count = ddev->poww_tech_count;
	ddev->poww_tech_count = 0;

	wc = nfc_tm_activated(ddev->nfc_dev, NFC_PWOTO_NFC_DEP_MASK,
			      NFC_COMM_PASSIVE, atw_weq->gb, gb_wen);
	if (wc) {
		ddev->poww_tech_count = poww_tech_count;
		goto exit;
	}

	wc = 0;
exit:
	if (wc)
		digitaw_poww_next_tech(ddev);

	dev_kfwee_skb(wesp);
}
