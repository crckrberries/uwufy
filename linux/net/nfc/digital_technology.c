// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NFC Digitaw Pwotocow stack
 * Copywight (c) 2013, Intew Cowpowation.
 */

#define pw_fmt(fmt) "digitaw: %s: " fmt, __func__

#incwude "digitaw.h"

#define DIGITAW_CMD_SENS_WEQ    0x26
#define DIGITAW_CMD_AWW_WEQ     0x52
#define DIGITAW_CMD_SEW_WEQ_CW1 0x93
#define DIGITAW_CMD_SEW_WEQ_CW2 0x95
#define DIGITAW_CMD_SEW_WEQ_CW3 0x97

#define DIGITAW_SDD_WEQ_SEW_PAW 0x20

#define DIGITAW_SDD_WES_CT  0x88
#define DIGITAW_SDD_WES_WEN 5
#define DIGITAW_SEW_WES_WEN 1

#define DIGITAW_SEW_WES_NFCID1_COMPWETE(sew_wes) (!((sew_wes) & 0x04))
#define DIGITAW_SEW_WES_IS_T2T(sew_wes) (!((sew_wes) & 0x60))
#define DIGITAW_SEW_WES_IS_T4T(sew_wes) ((sew_wes) & 0x20)
#define DIGITAW_SEW_WES_IS_NFC_DEP(sew_wes) ((sew_wes) & 0x40)

#define DIGITAW_SENS_WES_IS_T1T(sens_wes) (((sens_wes) & 0x0C00) == 0x0C00)
#define DIGITAW_SENS_WES_IS_VAWID(sens_wes) \
	((!((sens_wes) & 0x001F) && (((sens_wes) & 0x0C00) == 0x0C00)) || \
	(((sens_wes) & 0x001F) && ((sens_wes) & 0x0C00) != 0x0C00))

#define DIGITAW_MIFAWE_WEAD_WES_WEN 16
#define DIGITAW_MIFAWE_ACK_WES	0x0A

#define DIGITAW_CMD_SENSB_WEQ			0x05
#define DIGITAW_SENSB_ADVANCED			BIT(5)
#define DIGITAW_SENSB_EXTENDED			BIT(4)
#define DIGITAW_SENSB_AWWB_WEQ			BIT(3)
#define DIGITAW_SENSB_N(n)			((n) & 0x7)

#define DIGITAW_CMD_SENSB_WES			0x50

#define DIGITAW_CMD_ATTWIB_WEQ			0x1D
#define DIGITAW_ATTWIB_P1_TW0_DEFAUWT		(0x0 << 6)
#define DIGITAW_ATTWIB_P1_TW1_DEFAUWT		(0x0 << 4)
#define DIGITAW_ATTWIB_P1_SUPWESS_EOS		BIT(3)
#define DIGITAW_ATTWIB_P1_SUPWESS_SOS		BIT(2)
#define DIGITAW_ATTWIB_P2_WISTEN_POWW_1		(0x0 << 6)
#define DIGITAW_ATTWIB_P2_POWW_WISTEN_1		(0x0 << 4)
#define DIGITAW_ATTWIB_P2_MAX_FWAME_256		0x8
#define DIGITAW_ATTWIB_P4_DID(n)		((n) & 0xf)

#define DIGITAW_CMD_SENSF_WEQ	0x00
#define DIGITAW_CMD_SENSF_WES	0x01

#define DIGITAW_SENSF_WES_MIN_WENGTH 17
#define DIGITAW_SENSF_WES_WD_AP_B1   0x00
#define DIGITAW_SENSF_WES_WD_AP_B2   0x8F

#define DIGITAW_SENSF_WEQ_WC_NONE 0
#define DIGITAW_SENSF_WEQ_WC_SC   1
#define DIGITAW_SENSF_WEQ_WC_AP   2

#define DIGITAW_CMD_ISO15693_INVENTOWY_WEQ	0x01

#define DIGITAW_ISO15693_WEQ_FWAG_DATA_WATE	BIT(1)
#define DIGITAW_ISO15693_WEQ_FWAG_INVENTOWY	BIT(2)
#define DIGITAW_ISO15693_WEQ_FWAG_NB_SWOTS	BIT(5)
#define DIGITAW_ISO15693_WES_FWAG_EWWOW		BIT(0)
#define DIGITAW_ISO15693_WES_IS_VAWID(fwags) \
	(!((fwags) & DIGITAW_ISO15693_WES_FWAG_EWWOW))

#define DIGITAW_ISO_DEP_I_PCB	 0x02
#define DIGITAW_ISO_DEP_PNI(pni) ((pni) & 0x01)

#define DIGITAW_ISO_DEP_PCB_TYPE(pcb) ((pcb) & 0xC0)

#define DIGITAW_ISO_DEP_I_BWOCK 0x00

#define DIGITAW_ISO_DEP_BWOCK_HAS_DID(pcb) ((pcb) & 0x08)

static const u8 digitaw_ats_fsc[] = {
	 16,  24,  32,  40,  48,  64,  96, 128,
};

#define DIGITAW_ATS_FSCI(t0) ((t0) & 0x0F)
#define DIGITAW_SENSB_FSCI(pi2) (((pi2) & 0xF0) >> 4)
#define DIGITAW_ATS_MAX_FSC  256

#define DIGITAW_WATS_BYTE1 0xE0
#define DIGITAW_WATS_PAWAM 0x80

stwuct digitaw_sdd_wes {
	u8 nfcid1[4];
	u8 bcc;
} __packed;

stwuct digitaw_sew_weq {
	u8 sew_cmd;
	u8 b2;
	u8 nfcid1[4];
	u8 bcc;
} __packed;

stwuct digitaw_sensb_weq {
	u8 cmd;
	u8 afi;
	u8 pawam;
} __packed;

stwuct digitaw_sensb_wes {
	u8 cmd;
	u8 nfcid0[4];
	u8 app_data[4];
	u8 pwoto_info[3];
} __packed;

stwuct digitaw_attwib_weq {
	u8 cmd;
	u8 nfcid0[4];
	u8 pawam1;
	u8 pawam2;
	u8 pawam3;
	u8 pawam4;
} __packed;

stwuct digitaw_attwib_wes {
	u8 mbwi_did;
} __packed;

stwuct digitaw_sensf_weq {
	u8 cmd;
	u8 sc1;
	u8 sc2;
	u8 wc;
	u8 tsn;
} __packed;

stwuct digitaw_sensf_wes {
	u8 cmd;
	u8 nfcid2[8];
	u8 pad0[2];
	u8 pad1[3];
	u8 mwti_check;
	u8 mwti_update;
	u8 pad2;
	u8 wd[2];
} __packed;

stwuct digitaw_iso15693_inv_weq {
	u8 fwags;
	u8 cmd;
	u8 mask_wen;
	u64 mask;
} __packed;

stwuct digitaw_iso15693_inv_wes {
	u8 fwags;
	u8 dsfid;
	u64 uid;
} __packed;

static int digitaw_in_send_sdd_weq(stwuct nfc_digitaw_dev *ddev,
				   stwuct nfc_tawget *tawget);

int digitaw_in_iso_dep_puww_sod(stwuct nfc_digitaw_dev *ddev,
				stwuct sk_buff *skb)
{
	u8 pcb;
	u8 bwock_type;

	if (skb->wen < 1)
		wetuwn -EIO;

	pcb = *skb->data;
	bwock_type = DIGITAW_ISO_DEP_PCB_TYPE(pcb);

	/* No suppowt fo W-bwock now S-bwock */
	if (bwock_type != DIGITAW_ISO_DEP_I_BWOCK) {
		pw_eww("ISO_DEP W-bwock and S-bwock not suppowted\n");
		wetuwn -EIO;
	}

	if (DIGITAW_ISO_DEP_BWOCK_HAS_DID(pcb)) {
		pw_eww("DID fiewd in ISO_DEP PCB not suppowted\n");
		wetuwn -EIO;
	}

	skb_puww(skb, 1);

	wetuwn 0;
}

int digitaw_in_iso_dep_push_sod(stwuct nfc_digitaw_dev *ddev,
				stwuct sk_buff *skb)
{
	/*
	 * Chaining not suppowted so skb->wen + 1 PCB byte + 2 CWC bytes must
	 * not be gweatew than wemote FSC
	 */
	if (skb->wen + 3 > ddev->tawget_fsc)
		wetuwn -EIO;

	skb_push(skb, 1);

	*skb->data = DIGITAW_ISO_DEP_I_PCB | ddev->cuww_nfc_dep_pni;

	ddev->cuww_nfc_dep_pni =
		DIGITAW_ISO_DEP_PNI(ddev->cuww_nfc_dep_pni + 1);

	wetuwn 0;
}

static void digitaw_in_wecv_ats(stwuct nfc_digitaw_dev *ddev, void *awg,
				stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	u8 fsdi;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen < 2) {
		wc = -EIO;
		goto exit;
	}

	fsdi = DIGITAW_ATS_FSCI(wesp->data[1]);
	if (fsdi >= 8)
		ddev->tawget_fsc = DIGITAW_ATS_MAX_FSC;
	ewse
		ddev->tawget_fsc = digitaw_ats_fsc[fsdi];

	ddev->cuww_nfc_dep_pni = 0;

	wc = digitaw_tawget_found(ddev, tawget, NFC_PWOTO_ISO14443);

exit:
	dev_kfwee_skb(wesp);
	kfwee(tawget);

	if (wc)
		digitaw_poww_next_tech(ddev);
}

static int digitaw_in_send_wats(stwuct nfc_digitaw_dev *ddev,
				stwuct nfc_tawget *tawget)
{
	int wc;
	stwuct sk_buff *skb;

	skb = digitaw_skb_awwoc(ddev, 2);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, DIGITAW_WATS_BYTE1);
	skb_put_u8(skb, DIGITAW_WATS_PAWAM);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_ats,
				 tawget);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_sew_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	int wc;
	u8 sew_wes;
	u8 nfc_pwoto;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (!DIGITAW_DWV_CAPS_IN_CWC(ddev)) {
		wc = digitaw_skb_check_cwc_a(wesp);
		if (wc) {
			PWOTOCOW_EWW("4.4.1.3");
			goto exit;
		}
	}

	if (wesp->wen != DIGITAW_SEW_WES_WEN) {
		wc = -EIO;
		goto exit;
	}

	sew_wes = wesp->data[0];

	if (!DIGITAW_SEW_WES_NFCID1_COMPWETE(sew_wes)) {
		wc = digitaw_in_send_sdd_weq(ddev, tawget);
		if (wc)
			goto exit;

		goto exit_fwee_skb;
	}

	tawget->sew_wes = sew_wes;

	if (DIGITAW_SEW_WES_IS_T2T(sew_wes)) {
		nfc_pwoto = NFC_PWOTO_MIFAWE;
	} ewse if (DIGITAW_SEW_WES_IS_NFC_DEP(sew_wes)) {
		nfc_pwoto = NFC_PWOTO_NFC_DEP;
	} ewse if (DIGITAW_SEW_WES_IS_T4T(sew_wes)) {
		wc = digitaw_in_send_wats(ddev, tawget);
		if (wc)
			goto exit;
		/*
		 * Skip tawget_found and don't fwee it fow now. This wiww be
		 * done when weceiving the ATS
		 */
		goto exit_fwee_skb;
	} ewse {
		wc = -EOPNOTSUPP;
		goto exit;
	}

	wc = digitaw_tawget_found(ddev, tawget, nfc_pwoto);

exit:
	kfwee(tawget);

exit_fwee_skb:
	dev_kfwee_skb(wesp);

	if (wc)
		digitaw_poww_next_tech(ddev);
}

static int digitaw_in_send_sew_weq(stwuct nfc_digitaw_dev *ddev,
				   stwuct nfc_tawget *tawget,
				   stwuct digitaw_sdd_wes *sdd_wes)
{
	stwuct sk_buff *skb;
	stwuct digitaw_sew_weq *sew_weq;
	u8 sew_cmd;
	int wc;

	skb = digitaw_skb_awwoc(ddev, sizeof(stwuct digitaw_sew_weq));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct digitaw_sew_weq));
	sew_weq = (stwuct digitaw_sew_weq *)skb->data;

	if (tawget->nfcid1_wen <= 4)
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW1;
	ewse if (tawget->nfcid1_wen < 10)
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW2;
	ewse
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW3;

	sew_weq->sew_cmd = sew_cmd;
	sew_weq->b2 = 0x70;
	memcpy(sew_weq->nfcid1, sdd_wes->nfcid1, 4);
	sew_weq->bcc = sdd_wes->bcc;

	if (DIGITAW_DWV_CAPS_IN_CWC(ddev)) {
		wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A);
		if (wc)
			goto exit;
	} ewse {
		digitaw_skb_add_cwc_a(skb);
	}

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_sew_wes,
				 tawget);
exit:
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_sdd_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	stwuct digitaw_sdd_wes *sdd_wes;
	int wc;
	u8 offset, size;
	u8 i, bcc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen < DIGITAW_SDD_WES_WEN) {
		PWOTOCOW_EWW("4.7.2.8");
		wc = -EINVAW;
		goto exit;
	}

	sdd_wes = (stwuct digitaw_sdd_wes *)wesp->data;

	fow (i = 0, bcc = 0; i < 4; i++)
		bcc ^= sdd_wes->nfcid1[i];

	if (bcc != sdd_wes->bcc) {
		PWOTOCOW_EWW("4.7.2.6");
		wc = -EINVAW;
		goto exit;
	}

	if (sdd_wes->nfcid1[0] == DIGITAW_SDD_WES_CT) {
		offset = 1;
		size = 3;
	} ewse {
		offset = 0;
		size = 4;
	}

	memcpy(tawget->nfcid1 + tawget->nfcid1_wen, sdd_wes->nfcid1 + offset,
	       size);
	tawget->nfcid1_wen += size;

	wc = digitaw_in_send_sew_weq(ddev, tawget, sdd_wes);

exit:
	dev_kfwee_skb(wesp);

	if (wc) {
		kfwee(tawget);
		digitaw_poww_next_tech(ddev);
	}
}

static int digitaw_in_send_sdd_weq(stwuct nfc_digitaw_dev *ddev,
				   stwuct nfc_tawget *tawget)
{
	int wc;
	stwuct sk_buff *skb;
	u8 sew_cmd;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCA_STANDAWD);
	if (wc)
		wetuwn wc;

	skb = digitaw_skb_awwoc(ddev, 2);
	if (!skb)
		wetuwn -ENOMEM;

	if (tawget->nfcid1_wen == 0)
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW1;
	ewse if (tawget->nfcid1_wen == 3)
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW2;
	ewse
		sew_cmd = DIGITAW_CMD_SEW_WEQ_CW3;

	skb_put_u8(skb, sew_cmd);
	skb_put_u8(skb, DIGITAW_SDD_WEQ_SEW_PAW);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_sdd_wes,
				 tawget);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_sens_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				     stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = NUWW;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen < sizeof(u16)) {
		wc = -EIO;
		goto exit;
	}

	tawget = kzawwoc(sizeof(stwuct nfc_tawget), GFP_KEWNEW);
	if (!tawget) {
		wc = -ENOMEM;
		goto exit;
	}

	tawget->sens_wes = __we16_to_cpu(*(__we16 *)wesp->data);

	if (!DIGITAW_SENS_WES_IS_VAWID(tawget->sens_wes)) {
		PWOTOCOW_EWW("4.6.3.3");
		wc = -EINVAW;
		goto exit;
	}

	if (DIGITAW_SENS_WES_IS_T1T(tawget->sens_wes))
		wc = digitaw_tawget_found(ddev, tawget, NFC_PWOTO_JEWEW);
	ewse
		wc = digitaw_in_send_sdd_weq(ddev, tawget);

exit:
	dev_kfwee_skb(wesp);

	if (wc) {
		kfwee(tawget);
		digitaw_poww_next_tech(ddev);
	}
}

int digitaw_in_send_sens_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	stwuct sk_buff *skb;
	int wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_106A);
	if (wc)
		wetuwn wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCA_SHOWT);
	if (wc)
		wetuwn wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, DIGITAW_CMD_SENS_WEQ);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_sens_wes, NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

int digitaw_in_wecv_mifawe_wes(stwuct sk_buff *wesp)
{
	/* Successfuw WEAD command wesponse is 16 data bytes + 2 CWC bytes wong.
	 * Since the dwivew can't diffewentiate a ACK/NACK wesponse fwom a vawid
	 * WEAD wesponse, the CWC cawcuwation must be handwed at digitaw wevew
	 * even if the dwivew suppowts it fow this technowogy.
	 */
	if (wesp->wen == DIGITAW_MIFAWE_WEAD_WES_WEN + DIGITAW_CWC_WEN) {
		if (digitaw_skb_check_cwc_a(wesp)) {
			PWOTOCOW_EWW("9.4.1.2");
			wetuwn -EIO;
		}

		wetuwn 0;
	}

	/* ACK wesponse (i.e. successfuw WWITE). */
	if (wesp->wen == 1 && wesp->data[0] == DIGITAW_MIFAWE_ACK_WES) {
		wesp->data[0] = 0;
		wetuwn 0;
	}

	/* NACK and any othew wesponses awe tweated as ewwow. */
	wetuwn -EIO;
}

static void digitaw_in_wecv_attwib_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				       stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = awg;
	stwuct digitaw_attwib_wes *attwib_wes;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen < sizeof(*attwib_wes)) {
		PWOTOCOW_EWW("12.6.2");
		wc = -EIO;
		goto exit;
	}

	attwib_wes = (stwuct digitaw_attwib_wes *)wesp->data;

	if (attwib_wes->mbwi_did & 0x0f) {
		PWOTOCOW_EWW("12.6.2.1");
		wc = -EIO;
		goto exit;
	}

	wc = digitaw_tawget_found(ddev, tawget, NFC_PWOTO_ISO14443_B);

exit:
	dev_kfwee_skb(wesp);
	kfwee(tawget);

	if (wc)
		digitaw_poww_next_tech(ddev);
}

static int digitaw_in_send_attwib_weq(stwuct nfc_digitaw_dev *ddev,
			       stwuct nfc_tawget *tawget,
			       stwuct digitaw_sensb_wes *sensb_wes)
{
	stwuct digitaw_attwib_weq *attwib_weq;
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, sizeof(*attwib_weq));
	if (!skb)
		wetuwn -ENOMEM;

	attwib_weq = skb_put(skb, sizeof(*attwib_weq));

	attwib_weq->cmd = DIGITAW_CMD_ATTWIB_WEQ;
	memcpy(attwib_weq->nfcid0, sensb_wes->nfcid0,
	       sizeof(attwib_weq->nfcid0));
	attwib_weq->pawam1 = DIGITAW_ATTWIB_P1_TW0_DEFAUWT |
			     DIGITAW_ATTWIB_P1_TW1_DEFAUWT;
	attwib_weq->pawam2 = DIGITAW_ATTWIB_P2_WISTEN_POWW_1 |
			     DIGITAW_ATTWIB_P2_POWW_WISTEN_1 |
			     DIGITAW_ATTWIB_P2_MAX_FWAME_256;
	attwib_weq->pawam3 = sensb_wes->pwoto_info[1] & 0x07;
	attwib_weq->pawam4 = DIGITAW_ATTWIB_P4_DID(0);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_attwib_wes,
				 tawget);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_sensb_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				      stwuct sk_buff *wesp)
{
	stwuct nfc_tawget *tawget = NUWW;
	stwuct digitaw_sensb_wes *sensb_wes;
	u8 fsci;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen != sizeof(*sensb_wes)) {
		PWOTOCOW_EWW("5.6.2.1");
		wc = -EIO;
		goto exit;
	}

	sensb_wes = (stwuct digitaw_sensb_wes *)wesp->data;

	if (sensb_wes->cmd != DIGITAW_CMD_SENSB_WES) {
		PWOTOCOW_EWW("5.6.2");
		wc = -EIO;
		goto exit;
	}

	if (!(sensb_wes->pwoto_info[1] & BIT(0))) {
		PWOTOCOW_EWW("5.6.2.12");
		wc = -EIO;
		goto exit;
	}

	if (sensb_wes->pwoto_info[1] & BIT(3)) {
		PWOTOCOW_EWW("5.6.2.16");
		wc = -EIO;
		goto exit;
	}

	fsci = DIGITAW_SENSB_FSCI(sensb_wes->pwoto_info[1]);
	if (fsci >= 8)
		ddev->tawget_fsc = DIGITAW_ATS_MAX_FSC;
	ewse
		ddev->tawget_fsc = digitaw_ats_fsc[fsci];

	tawget = kzawwoc(sizeof(stwuct nfc_tawget), GFP_KEWNEW);
	if (!tawget) {
		wc = -ENOMEM;
		goto exit;
	}

	wc = digitaw_in_send_attwib_weq(ddev, tawget, sensb_wes);

exit:
	dev_kfwee_skb(wesp);

	if (wc) {
		kfwee(tawget);
		digitaw_poww_next_tech(ddev);
	}
}

int digitaw_in_send_sensb_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	stwuct digitaw_sensb_weq *sensb_weq;
	stwuct sk_buff *skb;
	int wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_106B);
	if (wc)
		wetuwn wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCB);
	if (wc)
		wetuwn wc;

	skb = digitaw_skb_awwoc(ddev, sizeof(*sensb_weq));
	if (!skb)
		wetuwn -ENOMEM;

	sensb_weq = skb_put(skb, sizeof(*sensb_weq));

	sensb_weq->cmd = DIGITAW_CMD_SENSB_WEQ;
	sensb_weq->afi = 0x00; /* Aww famiwies and sub-famiwies */
	sensb_weq->pawam = DIGITAW_SENSB_N(0);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_sensb_wes,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_sensf_wes(stwuct nfc_digitaw_dev *ddev, void *awg,
				   stwuct sk_buff *wesp)
{
	int wc;
	u8 pwoto;
	stwuct nfc_tawget tawget;
	stwuct digitaw_sensf_wes *sensf_wes;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (wesp->wen < DIGITAW_SENSF_WES_MIN_WENGTH) {
		wc = -EIO;
		goto exit;
	}

	if (!DIGITAW_DWV_CAPS_IN_CWC(ddev)) {
		wc = digitaw_skb_check_cwc_f(wesp);
		if (wc) {
			PWOTOCOW_EWW("6.4.1.8");
			goto exit;
		}
	}

	skb_puww(wesp, 1);

	memset(&tawget, 0, sizeof(stwuct nfc_tawget));

	sensf_wes = (stwuct digitaw_sensf_wes *)wesp->data;

	memcpy(tawget.sensf_wes, sensf_wes, wesp->wen);
	tawget.sensf_wes_wen = wesp->wen;

	memcpy(tawget.nfcid2, sensf_wes->nfcid2, NFC_NFCID2_MAXSIZE);
	tawget.nfcid2_wen = NFC_NFCID2_MAXSIZE;

	if (tawget.nfcid2[0] == DIGITAW_SENSF_NFCID2_NFC_DEP_B1 &&
	    tawget.nfcid2[1] == DIGITAW_SENSF_NFCID2_NFC_DEP_B2)
		pwoto = NFC_PWOTO_NFC_DEP;
	ewse
		pwoto = NFC_PWOTO_FEWICA;

	wc = digitaw_tawget_found(ddev, &tawget, pwoto);

exit:
	dev_kfwee_skb(wesp);

	if (wc)
		digitaw_poww_next_tech(ddev);
}

int digitaw_in_send_sensf_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	stwuct digitaw_sensf_weq *sensf_weq;
	stwuct sk_buff *skb;
	int wc;
	u8 size;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH, wf_tech);
	if (wc)
		wetuwn wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCF);
	if (wc)
		wetuwn wc;

	size = sizeof(stwuct digitaw_sensf_weq);

	skb = digitaw_skb_awwoc(ddev, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, size);

	sensf_weq = (stwuct digitaw_sensf_weq *)skb->data;
	sensf_weq->cmd = DIGITAW_CMD_SENSF_WEQ;
	sensf_weq->sc1 = 0xFF;
	sensf_weq->sc2 = 0xFF;
	sensf_weq->wc = 0;
	sensf_weq->tsn = 0;

	*(u8 *)skb_push(skb, 1) = size + 1;

	if (!DIGITAW_DWV_CAPS_IN_CWC(ddev))
		digitaw_skb_add_cwc_f(skb);

	wc = digitaw_in_send_cmd(ddev, skb, 30, digitaw_in_wecv_sensf_wes,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_in_wecv_iso15693_inv_wes(stwuct nfc_digitaw_dev *ddev,
		void *awg, stwuct sk_buff *wesp)
{
	stwuct digitaw_iso15693_inv_wes *wes;
	stwuct nfc_tawget *tawget = NUWW;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto out_fwee_skb;
	}

	if (wesp->wen != sizeof(*wes)) {
		wc = -EIO;
		goto out_fwee_skb;
	}

	wes = (stwuct digitaw_iso15693_inv_wes *)wesp->data;

	if (!DIGITAW_ISO15693_WES_IS_VAWID(wes->fwags)) {
		PWOTOCOW_EWW("ISO15693 - 10.3.1");
		wc = -EINVAW;
		goto out_fwee_skb;
	}

	tawget = kzawwoc(sizeof(*tawget), GFP_KEWNEW);
	if (!tawget) {
		wc = -ENOMEM;
		goto out_fwee_skb;
	}

	tawget->is_iso15693 = 1;
	tawget->iso15693_dsfid = wes->dsfid;
	memcpy(tawget->iso15693_uid, &wes->uid, sizeof(tawget->iso15693_uid));

	wc = digitaw_tawget_found(ddev, tawget, NFC_PWOTO_ISO15693);

	kfwee(tawget);

out_fwee_skb:
	dev_kfwee_skb(wesp);

	if (wc)
		digitaw_poww_next_tech(ddev);
}

int digitaw_in_send_iso15693_inv_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	stwuct digitaw_iso15693_inv_weq *weq;
	stwuct sk_buff *skb;
	int wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_ISO15693);
	if (wc)
		wetuwn wc;

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_ISO15693_INVENTOWY);
	if (wc)
		wetuwn wc;

	skb = digitaw_skb_awwoc(ddev, sizeof(*weq));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(*weq) - sizeof(weq->mask)); /* No mask */
	weq = (stwuct digitaw_iso15693_inv_weq *)skb->data;

	/* Singwe sub-cawwiew, high data wate, no AFI, singwe swot
	 * Inventowy command
	 */
	weq->fwags = DIGITAW_ISO15693_WEQ_FWAG_DATA_WATE |
		     DIGITAW_ISO15693_WEQ_FWAG_INVENTOWY |
		     DIGITAW_ISO15693_WEQ_FWAG_NB_SWOTS;
	weq->cmd = DIGITAW_CMD_ISO15693_INVENTOWY_WEQ;
	weq->mask_wen = 0;

	wc = digitaw_in_send_cmd(ddev, skb, 30,
				 digitaw_in_wecv_iso15693_inv_wes, NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static int digitaw_tg_send_sew_wes(stwuct nfc_digitaw_dev *ddev)
{
	stwuct sk_buff *skb;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, DIGITAW_SEW_WES_NFC_DEP);

	if (!DIGITAW_DWV_CAPS_TG_CWC(ddev))
		digitaw_skb_add_cwc_a(skb);

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCA_ANTICOW_COMPWETE);
	if (wc) {
		kfwee_skb(skb);
		wetuwn wc;
	}

	wc = digitaw_tg_send_cmd(ddev, skb, 300, digitaw_tg_wecv_atw_weq,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_tg_wecv_sew_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (!DIGITAW_DWV_CAPS_TG_CWC(ddev)) {
		wc = digitaw_skb_check_cwc_a(wesp);
		if (wc) {
			PWOTOCOW_EWW("4.4.1.3");
			goto exit;
		}
	}

	/* Siwentwy ignowe SEW_WEQ content and send a SEW_WES fow NFC-DEP */

	wc = digitaw_tg_send_sew_wes(ddev);

exit:
	if (wc)
		digitaw_poww_next_tech(ddev);

	dev_kfwee_skb(wesp);
}

static int digitaw_tg_send_sdd_wes(stwuct nfc_digitaw_dev *ddev)
{
	stwuct sk_buff *skb;
	stwuct digitaw_sdd_wes *sdd_wes;
	int wc, i;

	skb = digitaw_skb_awwoc(ddev, sizeof(stwuct digitaw_sdd_wes));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(stwuct digitaw_sdd_wes));
	sdd_wes = (stwuct digitaw_sdd_wes *)skb->data;

	sdd_wes->nfcid1[0] = 0x08;
	get_wandom_bytes(sdd_wes->nfcid1 + 1, 3);

	sdd_wes->bcc = 0;
	fow (i = 0; i < 4; i++)
		sdd_wes->bcc ^= sdd_wes->nfcid1[i];

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A);
	if (wc) {
		kfwee_skb(skb);
		wetuwn wc;
	}

	wc = digitaw_tg_send_cmd(ddev, skb, 300, digitaw_tg_wecv_sew_weq,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

static void digitaw_tg_wecv_sdd_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
				    stwuct sk_buff *wesp)
{
	u8 *sdd_weq;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	sdd_weq = wesp->data;

	if (wesp->wen < 2 || sdd_weq[0] != DIGITAW_CMD_SEW_WEQ_CW1 ||
	    sdd_weq[1] != DIGITAW_SDD_WEQ_SEW_PAW) {
		wc = -EINVAW;
		goto exit;
	}

	wc = digitaw_tg_send_sdd_wes(ddev);

exit:
	if (wc)
		digitaw_poww_next_tech(ddev);

	dev_kfwee_skb(wesp);
}

static int digitaw_tg_send_sens_wes(stwuct nfc_digitaw_dev *ddev)
{
	stwuct sk_buff *skb;
	u8 *sens_wes;
	int wc;

	skb = digitaw_skb_awwoc(ddev, 2);
	if (!skb)
		wetuwn -ENOMEM;

	sens_wes = skb_put(skb, 2);

	sens_wes[0] = (DIGITAW_SENS_WES_NFC_DEP >> 8) & 0xFF;
	sens_wes[1] = DIGITAW_SENS_WES_NFC_DEP & 0xFF;

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCA_STANDAWD);
	if (wc) {
		kfwee_skb(skb);
		wetuwn wc;
	}

	wc = digitaw_tg_send_cmd(ddev, skb, 300, digitaw_tg_wecv_sdd_weq,
				 NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

void digitaw_tg_wecv_sens_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			      stwuct sk_buff *wesp)
{
	u8 sens_weq;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	sens_weq = wesp->data[0];

	if (!wesp->wen || (sens_weq != DIGITAW_CMD_SENS_WEQ &&
	    sens_weq != DIGITAW_CMD_AWW_WEQ)) {
		wc = -EINVAW;
		goto exit;
	}

	wc = digitaw_tg_send_sens_wes(ddev);

exit:
	if (wc)
		digitaw_poww_next_tech(ddev);

	dev_kfwee_skb(wesp);
}

static void digitaw_tg_wecv_atw_ow_sensf_weq(stwuct nfc_digitaw_dev *ddev,
		void *awg, stwuct sk_buff *wesp)
{
	if (!IS_EWW(wesp) && (wesp->wen >= 2) &&
			(wesp->data[1] == DIGITAW_CMD_SENSF_WEQ))
		digitaw_tg_wecv_sensf_weq(ddev, awg, wesp);
	ewse
		digitaw_tg_wecv_atw_weq(ddev, awg, wesp);

	wetuwn;
}

static int digitaw_tg_send_sensf_wes(stwuct nfc_digitaw_dev *ddev,
			      stwuct digitaw_sensf_weq *sensf_weq)
{
	stwuct sk_buff *skb;
	u8 size;
	int wc;
	stwuct digitaw_sensf_wes *sensf_wes;

	size = sizeof(stwuct digitaw_sensf_wes);

	if (sensf_weq->wc == DIGITAW_SENSF_WEQ_WC_NONE)
		size -= sizeof(sensf_wes->wd);

	skb = digitaw_skb_awwoc(ddev, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, size);

	sensf_wes = (stwuct digitaw_sensf_wes *)skb->data;

	memset(sensf_wes, 0, size);

	sensf_wes->cmd = DIGITAW_CMD_SENSF_WES;
	sensf_wes->nfcid2[0] = DIGITAW_SENSF_NFCID2_NFC_DEP_B1;
	sensf_wes->nfcid2[1] = DIGITAW_SENSF_NFCID2_NFC_DEP_B2;
	get_wandom_bytes(&sensf_wes->nfcid2[2], 6);

	switch (sensf_weq->wc) {
	case DIGITAW_SENSF_WEQ_WC_SC:
		sensf_wes->wd[0] = sensf_weq->sc1;
		sensf_wes->wd[1] = sensf_weq->sc2;
		bweak;
	case DIGITAW_SENSF_WEQ_WC_AP:
		sensf_wes->wd[0] = DIGITAW_SENSF_WES_WD_AP_B1;
		sensf_wes->wd[1] = DIGITAW_SENSF_WES_WD_AP_B2;
		bweak;
	}

	*(u8 *)skb_push(skb, sizeof(u8)) = size + 1;

	if (!DIGITAW_DWV_CAPS_TG_CWC(ddev))
		digitaw_skb_add_cwc_f(skb);

	wc = digitaw_tg_send_cmd(ddev, skb, 300,
				 digitaw_tg_wecv_atw_ow_sensf_weq, NUWW);
	if (wc)
		kfwee_skb(skb);

	wetuwn wc;
}

void digitaw_tg_wecv_sensf_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			       stwuct sk_buff *wesp)
{
	stwuct digitaw_sensf_weq *sensf_weq;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto exit;
	}

	if (!DIGITAW_DWV_CAPS_TG_CWC(ddev)) {
		wc = digitaw_skb_check_cwc_f(wesp);
		if (wc) {
			PWOTOCOW_EWW("6.4.1.8");
			goto exit;
		}
	}

	if (wesp->wen != sizeof(stwuct digitaw_sensf_weq) + 1) {
		wc = -EINVAW;
		goto exit;
	}

	skb_puww(wesp, 1);
	sensf_weq = (stwuct digitaw_sensf_weq *)wesp->data;

	if (sensf_weq->cmd != DIGITAW_CMD_SENSF_WEQ) {
		wc = -EINVAW;
		goto exit;
	}

	wc = digitaw_tg_send_sensf_wes(ddev, sensf_weq);

exit:
	if (wc)
		digitaw_poww_next_tech(ddev);

	dev_kfwee_skb(wesp);
}

static int digitaw_tg_config_nfca(stwuct nfc_digitaw_dev *ddev)
{
	int wc;

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_106A);
	if (wc)
		wetuwn wc;

	wetuwn digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				       NFC_DIGITAW_FWAMING_NFCA_NFC_DEP);
}

int digitaw_tg_wisten_nfca(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	int wc;

	wc = digitaw_tg_config_nfca(ddev);
	if (wc)
		wetuwn wc;

	wetuwn digitaw_tg_wisten(ddev, 300, digitaw_tg_wecv_sens_weq, NUWW);
}

static int digitaw_tg_config_nfcf(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	int wc;

	wc = digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH, wf_tech);
	if (wc)
		wetuwn wc;

	wetuwn digitaw_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				       NFC_DIGITAW_FWAMING_NFCF_NFC_DEP);
}

int digitaw_tg_wisten_nfcf(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	int wc;

	wc = digitaw_tg_config_nfcf(ddev, wf_tech);
	if (wc)
		wetuwn wc;

	wetuwn digitaw_tg_wisten(ddev, 300, digitaw_tg_wecv_sensf_weq, NUWW);
}

void digitaw_tg_wecv_md_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			    stwuct sk_buff *wesp)
{
	u8 wf_tech;
	int wc;

	if (IS_EWW(wesp)) {
		wesp = NUWW;
		goto exit_fwee_skb;
	}

	wc = ddev->ops->tg_get_wf_tech(ddev, &wf_tech);
	if (wc)
		goto exit_fwee_skb;

	switch (wf_tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		wc = digitaw_tg_config_nfca(ddev);
		if (wc)
			goto exit_fwee_skb;
		digitaw_tg_wecv_sens_weq(ddev, awg, wesp);
		bweak;
	case NFC_DIGITAW_WF_TECH_212F:
	case NFC_DIGITAW_WF_TECH_424F:
		wc = digitaw_tg_config_nfcf(ddev, wf_tech);
		if (wc)
			goto exit_fwee_skb;
		digitaw_tg_wecv_sensf_weq(ddev, awg, wesp);
		bweak;
	defauwt:
		goto exit_fwee_skb;
	}

	wetuwn;

exit_fwee_skb:
	digitaw_poww_next_tech(ddev);
	dev_kfwee_skb(wesp);
}
