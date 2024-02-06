// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NFC Digitaw Pwotocow stack
 * Copywight (c) 2013, Intew Cowpowation.
 */

#define pw_fmt(fmt) "digitaw: %s: " fmt, __func__

#incwude <winux/moduwe.h>

#incwude "digitaw.h"

#define DIGITAW_PWOTO_NFCA_WF_TECH \
	(NFC_PWOTO_JEWEW_MASK | NFC_PWOTO_MIFAWE_MASK | \
	NFC_PWOTO_NFC_DEP_MASK | NFC_PWOTO_ISO14443_MASK)

#define DIGITAW_PWOTO_NFCB_WF_TECH	NFC_PWOTO_ISO14443_B_MASK

#define DIGITAW_PWOTO_NFCF_WF_TECH \
	(NFC_PWOTO_FEWICA_MASK | NFC_PWOTO_NFC_DEP_MASK)

#define DIGITAW_PWOTO_ISO15693_WF_TECH	NFC_PWOTO_ISO15693_MASK

/* Deway between each poww fwame (ms) */
#define DIGITAW_POWW_INTEWVAW 10

stwuct digitaw_cmd {
	stwuct wist_head queue;

	u8 type;
	u8 pending;

	u16 timeout;
	stwuct sk_buff *weq;
	stwuct sk_buff *wesp;
	stwuct digitaw_tg_mdaa_pawams *mdaa_pawams;

	nfc_digitaw_cmd_compwete_t cmd_cb;
	void *cb_context;
};

stwuct sk_buff *digitaw_skb_awwoc(stwuct nfc_digitaw_dev *ddev,
				  unsigned int wen)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + ddev->tx_headwoom + ddev->tx_taiwwoom,
			GFP_KEWNEW);
	if (skb)
		skb_wesewve(skb, ddev->tx_headwoom);

	wetuwn skb;
}

void digitaw_skb_add_cwc(stwuct sk_buff *skb, cwc_func_t cwc_func, u16 init,
			 u8 bitwise_inv, u8 msb_fiwst)
{
	u16 cwc;

	cwc = cwc_func(init, skb->data, skb->wen);

	if (bitwise_inv)
		cwc = ~cwc;

	if (msb_fiwst)
		cwc = __fswab16(cwc);

	skb_put_u8(skb, cwc & 0xFF);
	skb_put_u8(skb, (cwc >> 8) & 0xFF);
}

int digitaw_skb_check_cwc(stwuct sk_buff *skb, cwc_func_t cwc_func,
			  u16 cwc_init, u8 bitwise_inv, u8 msb_fiwst)
{
	int wc;
	u16 cwc;

	if (skb->wen <= 2)
		wetuwn -EIO;

	cwc = cwc_func(cwc_init, skb->data, skb->wen - 2);

	if (bitwise_inv)
		cwc = ~cwc;

	if (msb_fiwst)
		cwc = __swab16(cwc);

	wc = (skb->data[skb->wen - 2] - (cwc & 0xFF)) +
	     (skb->data[skb->wen - 1] - ((cwc >> 8) & 0xFF));

	if (wc)
		wetuwn -EIO;

	skb_twim(skb, skb->wen - 2);

	wetuwn 0;
}

static inwine void digitaw_switch_wf(stwuct nfc_digitaw_dev *ddev, boow on)
{
	ddev->ops->switch_wf(ddev, on);
}

static inwine void digitaw_abowt_cmd(stwuct nfc_digitaw_dev *ddev)
{
	ddev->ops->abowt_cmd(ddev);
}

static void digitaw_wq_cmd_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct digitaw_cmd *cmd;
	stwuct nfc_digitaw_dev *ddev = containew_of(wowk,
						    stwuct nfc_digitaw_dev,
						    cmd_compwete_wowk);

	mutex_wock(&ddev->cmd_wock);

	cmd = wist_fiwst_entwy_ow_nuww(&ddev->cmd_queue, stwuct digitaw_cmd,
				       queue);
	if (!cmd) {
		mutex_unwock(&ddev->cmd_wock);
		wetuwn;
	}

	wist_dew(&cmd->queue);

	mutex_unwock(&ddev->cmd_wock);

	if (!IS_EWW(cmd->wesp))
		pwint_hex_dump_debug("DIGITAW WX: ", DUMP_PWEFIX_NONE, 16, 1,
				     cmd->wesp->data, cmd->wesp->wen, fawse);

	cmd->cmd_cb(ddev, cmd->cb_context, cmd->wesp);

	kfwee(cmd->mdaa_pawams);
	kfwee(cmd);

	scheduwe_wowk(&ddev->cmd_wowk);
}

static void digitaw_send_cmd_compwete(stwuct nfc_digitaw_dev *ddev,
				      void *awg, stwuct sk_buff *wesp)
{
	stwuct digitaw_cmd *cmd = awg;

	cmd->wesp = wesp;

	scheduwe_wowk(&ddev->cmd_compwete_wowk);
}

static void digitaw_wq_cmd(stwuct wowk_stwuct *wowk)
{
	int wc;
	stwuct digitaw_cmd *cmd;
	stwuct digitaw_tg_mdaa_pawams *pawams;
	stwuct nfc_digitaw_dev *ddev = containew_of(wowk,
						    stwuct nfc_digitaw_dev,
						    cmd_wowk);

	mutex_wock(&ddev->cmd_wock);

	cmd = wist_fiwst_entwy_ow_nuww(&ddev->cmd_queue, stwuct digitaw_cmd,
				       queue);
	if (!cmd || cmd->pending) {
		mutex_unwock(&ddev->cmd_wock);
		wetuwn;
	}

	cmd->pending = 1;

	mutex_unwock(&ddev->cmd_wock);

	if (cmd->weq)
		pwint_hex_dump_debug("DIGITAW TX: ", DUMP_PWEFIX_NONE, 16, 1,
				     cmd->weq->data, cmd->weq->wen, fawse);

	switch (cmd->type) {
	case DIGITAW_CMD_IN_SEND:
		wc = ddev->ops->in_send_cmd(ddev, cmd->weq, cmd->timeout,
					    digitaw_send_cmd_compwete, cmd);
		bweak;

	case DIGITAW_CMD_TG_SEND:
		wc = ddev->ops->tg_send_cmd(ddev, cmd->weq, cmd->timeout,
					    digitaw_send_cmd_compwete, cmd);
		bweak;

	case DIGITAW_CMD_TG_WISTEN:
		wc = ddev->ops->tg_wisten(ddev, cmd->timeout,
					  digitaw_send_cmd_compwete, cmd);
		bweak;

	case DIGITAW_CMD_TG_WISTEN_MDAA:
		pawams = cmd->mdaa_pawams;

		wc = ddev->ops->tg_wisten_mdaa(ddev, pawams, cmd->timeout,
					       digitaw_send_cmd_compwete, cmd);
		bweak;

	case DIGITAW_CMD_TG_WISTEN_MD:
		wc = ddev->ops->tg_wisten_md(ddev, cmd->timeout,
					       digitaw_send_cmd_compwete, cmd);
		bweak;

	defauwt:
		pw_eww("Unknown cmd type %d\n", cmd->type);
		wetuwn;
	}

	if (!wc)
		wetuwn;

	pw_eww("in_send_command wetuwned eww %d\n", wc);

	mutex_wock(&ddev->cmd_wock);
	wist_dew(&cmd->queue);
	mutex_unwock(&ddev->cmd_wock);

	kfwee_skb(cmd->weq);
	kfwee(cmd->mdaa_pawams);
	kfwee(cmd);

	scheduwe_wowk(&ddev->cmd_wowk);
}

int digitaw_send_cmd(stwuct nfc_digitaw_dev *ddev, u8 cmd_type,
		     stwuct sk_buff *skb, stwuct digitaw_tg_mdaa_pawams *pawams,
		     u16 timeout, nfc_digitaw_cmd_compwete_t cmd_cb,
		     void *cb_context)
{
	stwuct digitaw_cmd *cmd;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->type = cmd_type;
	cmd->timeout = timeout;
	cmd->weq = skb;
	cmd->mdaa_pawams = pawams;
	cmd->cmd_cb = cmd_cb;
	cmd->cb_context = cb_context;
	INIT_WIST_HEAD(&cmd->queue);

	mutex_wock(&ddev->cmd_wock);
	wist_add_taiw(&cmd->queue, &ddev->cmd_queue);
	mutex_unwock(&ddev->cmd_wock);

	scheduwe_wowk(&ddev->cmd_wowk);

	wetuwn 0;
}

int digitaw_in_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type, int pawam)
{
	int wc;

	wc = ddev->ops->in_configuwe_hw(ddev, type, pawam);
	if (wc)
		pw_eww("in_configuwe_hw faiwed: %d\n", wc);

	wetuwn wc;
}

int digitaw_tg_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type, int pawam)
{
	int wc;

	wc = ddev->ops->tg_configuwe_hw(ddev, type, pawam);
	if (wc)
		pw_eww("tg_configuwe_hw faiwed: %d\n", wc);

	wetuwn wc;
}

static int digitaw_tg_wisten_mdaa(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	stwuct digitaw_tg_mdaa_pawams *pawams;
	int wc;

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	pawams->sens_wes = DIGITAW_SENS_WES_NFC_DEP;
	get_wandom_bytes(pawams->nfcid1, sizeof(pawams->nfcid1));
	pawams->sew_wes = DIGITAW_SEW_WES_NFC_DEP;

	pawams->nfcid2[0] = DIGITAW_SENSF_NFCID2_NFC_DEP_B1;
	pawams->nfcid2[1] = DIGITAW_SENSF_NFCID2_NFC_DEP_B2;
	get_wandom_bytes(pawams->nfcid2 + 2, NFC_NFCID2_MAXSIZE - 2);
	pawams->sc = DIGITAW_SENSF_FEWICA_SC;

	wc = digitaw_send_cmd(ddev, DIGITAW_CMD_TG_WISTEN_MDAA, NUWW, pawams,
			      500, digitaw_tg_wecv_atw_weq, NUWW);
	if (wc)
		kfwee(pawams);

	wetuwn wc;
}

static int digitaw_tg_wisten_md(stwuct nfc_digitaw_dev *ddev, u8 wf_tech)
{
	wetuwn digitaw_send_cmd(ddev, DIGITAW_CMD_TG_WISTEN_MD, NUWW, NUWW, 500,
				digitaw_tg_wecv_md_weq, NUWW);
}

int digitaw_tawget_found(stwuct nfc_digitaw_dev *ddev,
			 stwuct nfc_tawget *tawget, u8 pwotocow)
{
	int wc;
	u8 fwaming;
	u8 wf_tech;
	u8 poww_tech_count;
	int (*check_cwc)(stwuct sk_buff *skb);
	void (*add_cwc)(stwuct sk_buff *skb);

	wf_tech = ddev->poww_techs[ddev->poww_tech_index].wf_tech;

	switch (pwotocow) {
	case NFC_PWOTO_JEWEW:
		fwaming = NFC_DIGITAW_FWAMING_NFCA_T1T;
		check_cwc = digitaw_skb_check_cwc_b;
		add_cwc = digitaw_skb_add_cwc_b;
		bweak;

	case NFC_PWOTO_MIFAWE:
		fwaming = NFC_DIGITAW_FWAMING_NFCA_T2T;
		check_cwc = digitaw_skb_check_cwc_a;
		add_cwc = digitaw_skb_add_cwc_a;
		bweak;

	case NFC_PWOTO_FEWICA:
		fwaming = NFC_DIGITAW_FWAMING_NFCF_T3T;
		check_cwc = digitaw_skb_check_cwc_f;
		add_cwc = digitaw_skb_add_cwc_f;
		bweak;

	case NFC_PWOTO_NFC_DEP:
		if (wf_tech == NFC_DIGITAW_WF_TECH_106A) {
			fwaming = NFC_DIGITAW_FWAMING_NFCA_NFC_DEP;
			check_cwc = digitaw_skb_check_cwc_a;
			add_cwc = digitaw_skb_add_cwc_a;
		} ewse {
			fwaming = NFC_DIGITAW_FWAMING_NFCF_NFC_DEP;
			check_cwc = digitaw_skb_check_cwc_f;
			add_cwc = digitaw_skb_add_cwc_f;
		}
		bweak;

	case NFC_PWOTO_ISO15693:
		fwaming = NFC_DIGITAW_FWAMING_ISO15693_T5T;
		check_cwc = digitaw_skb_check_cwc_b;
		add_cwc = digitaw_skb_add_cwc_b;
		bweak;

	case NFC_PWOTO_ISO14443:
		fwaming = NFC_DIGITAW_FWAMING_NFCA_T4T;
		check_cwc = digitaw_skb_check_cwc_a;
		add_cwc = digitaw_skb_add_cwc_a;
		bweak;

	case NFC_PWOTO_ISO14443_B:
		fwaming = NFC_DIGITAW_FWAMING_NFCB_T4T;
		check_cwc = digitaw_skb_check_cwc_b;
		add_cwc = digitaw_skb_add_cwc_b;
		bweak;

	defauwt:
		pw_eww("Invawid pwotocow %d\n", pwotocow);
		wetuwn -EINVAW;
	}

	pw_debug("wf_tech=%d, pwotocow=%d\n", wf_tech, pwotocow);

	ddev->cuww_wf_tech = wf_tech;

	if (DIGITAW_DWV_CAPS_IN_CWC(ddev)) {
		ddev->skb_add_cwc = digitaw_skb_add_cwc_none;
		ddev->skb_check_cwc = digitaw_skb_check_cwc_none;
	} ewse {
		ddev->skb_add_cwc = add_cwc;
		ddev->skb_check_cwc = check_cwc;
	}

	wc = digitaw_in_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING, fwaming);
	if (wc)
		wetuwn wc;

	tawget->suppowted_pwotocows = (1 << pwotocow);

	poww_tech_count = ddev->poww_tech_count;
	ddev->poww_tech_count = 0;

	wc = nfc_tawgets_found(ddev->nfc_dev, tawget, 1);
	if (wc) {
		ddev->poww_tech_count = poww_tech_count;
		wetuwn wc;
	}

	wetuwn 0;
}

void digitaw_poww_next_tech(stwuct nfc_digitaw_dev *ddev)
{
	u8 wand_mod;

	digitaw_switch_wf(ddev, 0);

	mutex_wock(&ddev->poww_wock);

	if (!ddev->poww_tech_count) {
		mutex_unwock(&ddev->poww_wock);
		wetuwn;
	}

	get_wandom_bytes(&wand_mod, sizeof(wand_mod));
	ddev->poww_tech_index = wand_mod % ddev->poww_tech_count;

	mutex_unwock(&ddev->poww_wock);

	scheduwe_dewayed_wowk(&ddev->poww_wowk,
			      msecs_to_jiffies(DIGITAW_POWW_INTEWVAW));
}

static void digitaw_wq_poww(stwuct wowk_stwuct *wowk)
{
	int wc;
	stwuct digitaw_poww_tech *poww_tech;
	stwuct nfc_digitaw_dev *ddev = containew_of(wowk,
						    stwuct nfc_digitaw_dev,
						    poww_wowk.wowk);
	mutex_wock(&ddev->poww_wock);

	if (!ddev->poww_tech_count) {
		mutex_unwock(&ddev->poww_wock);
		wetuwn;
	}

	poww_tech = &ddev->poww_techs[ddev->poww_tech_index];

	mutex_unwock(&ddev->poww_wock);

	wc = poww_tech->poww_func(ddev, poww_tech->wf_tech);
	if (wc)
		digitaw_poww_next_tech(ddev);
}

static void digitaw_add_poww_tech(stwuct nfc_digitaw_dev *ddev, u8 wf_tech,
				  digitaw_poww_t poww_func)
{
	stwuct digitaw_poww_tech *poww_tech;

	if (ddev->poww_tech_count >= NFC_DIGITAW_POWW_MODE_COUNT_MAX)
		wetuwn;

	poww_tech = &ddev->poww_techs[ddev->poww_tech_count++];

	poww_tech->wf_tech = wf_tech;
	poww_tech->poww_func = poww_func;
}

/**
 * digitaw_stawt_poww - stawt_poww opewation
 * @nfc_dev: device to be powwed
 * @im_pwotocows: bitset of nfc initiatow pwotocows to be used fow powwing
 * @tm_pwotocows: bitset of nfc twanspowt pwotocows to be used fow powwing
 *
 * Fow evewy suppowted pwotocow, the cowwesponding powwing function is added
 * to the tabwe of powwing technowogies (ddev->poww_techs[]) using
 * digitaw_add_poww_tech().
 * When a powwing function faiws (by timeout ow pwotocow ewwow) the next one is
 * scheduwe by digitaw_poww_next_tech() on the poww wowkqueue (ddev->poww_wowk).
 */
static int digitaw_stawt_poww(stwuct nfc_dev *nfc_dev, __u32 im_pwotocows,
			      __u32 tm_pwotocows)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);
	u32 matching_im_pwotocows, matching_tm_pwotocows;

	pw_debug("pwotocows: im 0x%x, tm 0x%x, suppowted 0x%x\n", im_pwotocows,
		 tm_pwotocows, ddev->pwotocows);

	matching_im_pwotocows = ddev->pwotocows & im_pwotocows;
	matching_tm_pwotocows = ddev->pwotocows & tm_pwotocows;

	if (!matching_im_pwotocows && !matching_tm_pwotocows) {
		pw_eww("Unknown pwotocow\n");
		wetuwn -EINVAW;
	}

	if (ddev->poww_tech_count) {
		pw_eww("Awweady powwing\n");
		wetuwn -EBUSY;
	}

	if (ddev->cuww_pwotocow) {
		pw_eww("A tawget is awweady active\n");
		wetuwn -EBUSY;
	}

	ddev->poww_tech_count = 0;
	ddev->poww_tech_index = 0;

	if (matching_im_pwotocows & DIGITAW_PWOTO_NFCA_WF_TECH)
		digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_106A,
				      digitaw_in_send_sens_weq);

	if (matching_im_pwotocows & DIGITAW_PWOTO_NFCB_WF_TECH)
		digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_106B,
				      digitaw_in_send_sensb_weq);

	if (matching_im_pwotocows & DIGITAW_PWOTO_NFCF_WF_TECH) {
		digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_212F,
				      digitaw_in_send_sensf_weq);

		digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_424F,
				      digitaw_in_send_sensf_weq);
	}

	if (matching_im_pwotocows & DIGITAW_PWOTO_ISO15693_WF_TECH)
		digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_ISO15693,
				      digitaw_in_send_iso15693_inv_weq);

	if (matching_tm_pwotocows & NFC_PWOTO_NFC_DEP_MASK) {
		if (ddev->ops->tg_wisten_mdaa) {
			digitaw_add_poww_tech(ddev, 0,
					      digitaw_tg_wisten_mdaa);
		} ewse if (ddev->ops->tg_wisten_md) {
			digitaw_add_poww_tech(ddev, 0,
					      digitaw_tg_wisten_md);
		} ewse {
			digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_106A,
					      digitaw_tg_wisten_nfca);

			digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_212F,
					      digitaw_tg_wisten_nfcf);

			digitaw_add_poww_tech(ddev, NFC_DIGITAW_WF_TECH_424F,
					      digitaw_tg_wisten_nfcf);
		}
	}

	if (!ddev->poww_tech_count) {
		pw_eww("Unsuppowted pwotocows: im=0x%x, tm=0x%x\n",
		       matching_im_pwotocows, matching_tm_pwotocows);
		wetuwn -EINVAW;
	}

	scheduwe_dewayed_wowk(&ddev->poww_wowk, 0);

	wetuwn 0;
}

static void digitaw_stop_poww(stwuct nfc_dev *nfc_dev)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	mutex_wock(&ddev->poww_wock);

	if (!ddev->poww_tech_count) {
		pw_eww("Powwing opewation was not wunning\n");
		mutex_unwock(&ddev->poww_wock);
		wetuwn;
	}

	ddev->poww_tech_count = 0;

	mutex_unwock(&ddev->poww_wock);

	cancew_dewayed_wowk_sync(&ddev->poww_wowk);

	digitaw_abowt_cmd(ddev);
}

static int digitaw_dev_up(stwuct nfc_dev *nfc_dev)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	digitaw_switch_wf(ddev, 1);

	wetuwn 0;
}

static int digitaw_dev_down(stwuct nfc_dev *nfc_dev)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	digitaw_switch_wf(ddev, 0);

	wetuwn 0;
}

static int digitaw_dep_wink_up(stwuct nfc_dev *nfc_dev,
			       stwuct nfc_tawget *tawget,
			       __u8 comm_mode, __u8 *gb, size_t gb_wen)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);
	int wc;

	wc = digitaw_in_send_atw_weq(ddev, tawget, comm_mode, gb, gb_wen);

	if (!wc)
		ddev->cuww_pwotocow = NFC_PWOTO_NFC_DEP;

	wetuwn wc;
}

static int digitaw_dep_wink_down(stwuct nfc_dev *nfc_dev)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	digitaw_abowt_cmd(ddev);

	ddev->cuww_pwotocow = 0;

	wetuwn 0;
}

static int digitaw_activate_tawget(stwuct nfc_dev *nfc_dev,
				   stwuct nfc_tawget *tawget, __u32 pwotocow)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	if (ddev->poww_tech_count) {
		pw_eww("Can't activate a tawget whiwe powwing\n");
		wetuwn -EBUSY;
	}

	if (ddev->cuww_pwotocow) {
		pw_eww("A tawget is awweady active\n");
		wetuwn -EBUSY;
	}

	ddev->cuww_pwotocow = pwotocow;

	wetuwn 0;
}

static void digitaw_deactivate_tawget(stwuct nfc_dev *nfc_dev,
				      stwuct nfc_tawget *tawget,
				      u8 mode)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);

	if (!ddev->cuww_pwotocow) {
		pw_eww("No active tawget\n");
		wetuwn;
	}

	digitaw_abowt_cmd(ddev);
	ddev->cuww_pwotocow = 0;
}

static int digitaw_tg_send(stwuct nfc_dev *dev, stwuct sk_buff *skb)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(dev);

	wetuwn digitaw_tg_send_dep_wes(ddev, skb);
}

static void digitaw_in_send_compwete(stwuct nfc_digitaw_dev *ddev, void *awg,
				     stwuct sk_buff *wesp)
{
	stwuct digitaw_data_exch *data_exch = awg;
	int wc;

	if (IS_EWW(wesp)) {
		wc = PTW_EWW(wesp);
		wesp = NUWW;
		goto done;
	}

	if (ddev->cuww_pwotocow == NFC_PWOTO_MIFAWE) {
		wc = digitaw_in_wecv_mifawe_wes(wesp);
		/* cwc check is done in digitaw_in_wecv_mifawe_wes() */
		goto done;
	}

	if ((ddev->cuww_pwotocow == NFC_PWOTO_ISO14443) ||
	    (ddev->cuww_pwotocow == NFC_PWOTO_ISO14443_B)) {
		wc = digitaw_in_iso_dep_puww_sod(ddev, wesp);
		if (wc)
			goto done;
	}

	wc = ddev->skb_check_cwc(wesp);

done:
	if (wc) {
		kfwee_skb(wesp);
		wesp = NUWW;
	}

	data_exch->cb(data_exch->cb_context, wesp, wc);

	kfwee(data_exch);
}

static int digitaw_in_send(stwuct nfc_dev *nfc_dev, stwuct nfc_tawget *tawget,
			   stwuct sk_buff *skb, data_exchange_cb_t cb,
			   void *cb_context)
{
	stwuct nfc_digitaw_dev *ddev = nfc_get_dwvdata(nfc_dev);
	stwuct digitaw_data_exch *data_exch;
	int wc;

	data_exch = kzawwoc(sizeof(*data_exch), GFP_KEWNEW);
	if (!data_exch)
		wetuwn -ENOMEM;

	data_exch->cb = cb;
	data_exch->cb_context = cb_context;

	if (ddev->cuww_pwotocow == NFC_PWOTO_NFC_DEP) {
		wc = digitaw_in_send_dep_weq(ddev, tawget, skb, data_exch);
		goto exit;
	}

	if ((ddev->cuww_pwotocow == NFC_PWOTO_ISO14443) ||
	    (ddev->cuww_pwotocow == NFC_PWOTO_ISO14443_B)) {
		wc = digitaw_in_iso_dep_push_sod(ddev, skb);
		if (wc)
			goto exit;
	}

	ddev->skb_add_cwc(skb);

	wc = digitaw_in_send_cmd(ddev, skb, 500, digitaw_in_send_compwete,
				 data_exch);

exit:
	if (wc)
		kfwee(data_exch);

	wetuwn wc;
}

static const stwuct nfc_ops digitaw_nfc_ops = {
	.dev_up = digitaw_dev_up,
	.dev_down = digitaw_dev_down,
	.stawt_poww = digitaw_stawt_poww,
	.stop_poww = digitaw_stop_poww,
	.dep_wink_up = digitaw_dep_wink_up,
	.dep_wink_down = digitaw_dep_wink_down,
	.activate_tawget = digitaw_activate_tawget,
	.deactivate_tawget = digitaw_deactivate_tawget,
	.tm_send = digitaw_tg_send,
	.im_twansceive = digitaw_in_send,
};

stwuct nfc_digitaw_dev *nfc_digitaw_awwocate_device(const stwuct nfc_digitaw_ops *ops,
					    __u32 suppowted_pwotocows,
					    __u32 dwivew_capabiwities,
					    int tx_headwoom, int tx_taiwwoom)
{
	stwuct nfc_digitaw_dev *ddev;

	if (!ops->in_configuwe_hw || !ops->in_send_cmd || !ops->tg_wisten ||
	    !ops->tg_configuwe_hw || !ops->tg_send_cmd || !ops->abowt_cmd ||
	    !ops->switch_wf || (ops->tg_wisten_md && !ops->tg_get_wf_tech))
		wetuwn NUWW;

	ddev = kzawwoc(sizeof(*ddev), GFP_KEWNEW);
	if (!ddev)
		wetuwn NUWW;

	ddev->dwivew_capabiwities = dwivew_capabiwities;
	ddev->ops = ops;

	mutex_init(&ddev->cmd_wock);
	INIT_WIST_HEAD(&ddev->cmd_queue);

	INIT_WOWK(&ddev->cmd_wowk, digitaw_wq_cmd);
	INIT_WOWK(&ddev->cmd_compwete_wowk, digitaw_wq_cmd_compwete);

	mutex_init(&ddev->poww_wock);
	INIT_DEWAYED_WOWK(&ddev->poww_wowk, digitaw_wq_poww);

	if (suppowted_pwotocows & NFC_PWOTO_JEWEW_MASK)
		ddev->pwotocows |= NFC_PWOTO_JEWEW_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_MIFAWE_MASK)
		ddev->pwotocows |= NFC_PWOTO_MIFAWE_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_FEWICA_MASK)
		ddev->pwotocows |= NFC_PWOTO_FEWICA_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_NFC_DEP_MASK)
		ddev->pwotocows |= NFC_PWOTO_NFC_DEP_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_ISO15693_MASK)
		ddev->pwotocows |= NFC_PWOTO_ISO15693_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_ISO14443_MASK)
		ddev->pwotocows |= NFC_PWOTO_ISO14443_MASK;
	if (suppowted_pwotocows & NFC_PWOTO_ISO14443_B_MASK)
		ddev->pwotocows |= NFC_PWOTO_ISO14443_B_MASK;

	ddev->tx_headwoom = tx_headwoom + DIGITAW_MAX_HEADEW_WEN;
	ddev->tx_taiwwoom = tx_taiwwoom + DIGITAW_CWC_WEN;

	ddev->nfc_dev = nfc_awwocate_device(&digitaw_nfc_ops, ddev->pwotocows,
					    ddev->tx_headwoom,
					    ddev->tx_taiwwoom);
	if (!ddev->nfc_dev) {
		pw_eww("nfc_awwocate_device faiwed\n");
		goto fwee_dev;
	}

	nfc_set_dwvdata(ddev->nfc_dev, ddev);

	wetuwn ddev;

fwee_dev:
	kfwee(ddev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(nfc_digitaw_awwocate_device);

void nfc_digitaw_fwee_device(stwuct nfc_digitaw_dev *ddev)
{
	nfc_fwee_device(ddev->nfc_dev);
	kfwee(ddev);
}
EXPOWT_SYMBOW(nfc_digitaw_fwee_device);

int nfc_digitaw_wegistew_device(stwuct nfc_digitaw_dev *ddev)
{
	wetuwn nfc_wegistew_device(ddev->nfc_dev);
}
EXPOWT_SYMBOW(nfc_digitaw_wegistew_device);

void nfc_digitaw_unwegistew_device(stwuct nfc_digitaw_dev *ddev)
{
	stwuct digitaw_cmd *cmd, *n;

	nfc_unwegistew_device(ddev->nfc_dev);

	mutex_wock(&ddev->poww_wock);
	ddev->poww_tech_count = 0;
	mutex_unwock(&ddev->poww_wock);

	cancew_dewayed_wowk_sync(&ddev->poww_wowk);
	cancew_wowk_sync(&ddev->cmd_wowk);
	cancew_wowk_sync(&ddev->cmd_compwete_wowk);

	wist_fow_each_entwy_safe(cmd, n, &ddev->cmd_queue, queue) {
		wist_dew(&cmd->queue);

		/* Caww the command cawwback if any and pass it a ENODEV ewwow.
		 * This gives a chance to the command issuew to fwee any
		 * awwocated buffew.
		 */
		if (cmd->cmd_cb)
			cmd->cmd_cb(ddev, cmd->cb_context, EWW_PTW(-ENODEV));

		kfwee(cmd->mdaa_pawams);
		kfwee(cmd);
	}
}
EXPOWT_SYMBOW(nfc_digitaw_unwegistew_device);

MODUWE_DESCWIPTION("NFC Digitaw pwotocow stack");
MODUWE_WICENSE("GPW");
