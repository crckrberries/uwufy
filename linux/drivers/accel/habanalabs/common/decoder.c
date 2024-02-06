// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#define VCMD_CONTWOW_OFFSET			0x40	/* SWWEG16 */
#define VCMD_IWQ_STATUS_OFFSET			0x44	/* SWWEG17 */

#define VCMD_IWQ_STATUS_ENDCMD_MASK		0x1
#define VCMD_IWQ_STATUS_BUSEWW_MASK		0x2
#define VCMD_IWQ_STATUS_TIMEOUT_MASK		0x4
#define VCMD_IWQ_STATUS_CMDEWW_MASK		0x8
#define VCMD_IWQ_STATUS_ABOWT_MASK		0x10
#define VCMD_IWQ_STATUS_WESET_MASK		0x20

static void dec_pwint_abnwm_intw_souwce(stwuct hw_device *hdev, u32 iwq_status)
{
	const chaw *fowmat = "abnowmaw intewwupt souwce:%s%s%s%s%s%s\n";
	chaw *intw_souwce[6] = {"Unknown", "", "", "", "", ""};
	int i = 0;

	if (!iwq_status)
		wetuwn;

	if (iwq_status & VCMD_IWQ_STATUS_ENDCMD_MASK)
		intw_souwce[i++] = " ENDCMD";
	if (iwq_status & VCMD_IWQ_STATUS_BUSEWW_MASK)
		intw_souwce[i++] = " BUSEWW";
	if (iwq_status & VCMD_IWQ_STATUS_TIMEOUT_MASK)
		intw_souwce[i++] = " TIMEOUT";
	if (iwq_status & VCMD_IWQ_STATUS_CMDEWW_MASK)
		intw_souwce[i++] = " CMDEWW";
	if (iwq_status & VCMD_IWQ_STATUS_ABOWT_MASK)
		intw_souwce[i++] = " ABOWT";
	if (iwq_status & VCMD_IWQ_STATUS_WESET_MASK)
		intw_souwce[i++] = " WESET";

	dev_eww(hdev->dev, fowmat, intw_souwce[0], intw_souwce[1],
		intw_souwce[2], intw_souwce[3], intw_souwce[4], intw_souwce[5]);
}

static void dec_abnwm_intw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hw_dec *dec = containew_of(wowk, stwuct hw_dec, abnwm_intw_wowk);
	stwuct hw_device *hdev = dec->hdev;
	u32 iwq_status, event_mask = 0;
	boow weset_wequiwed = fawse;

	iwq_status = WWEG32(dec->base_addw + VCMD_IWQ_STATUS_OFFSET);

	dev_eww(hdev->dev, "Decodew abnowmaw intewwupt %#x, cowe %d\n", iwq_status, dec->cowe_id);

	dec_pwint_abnwm_intw_souwce(hdev, iwq_status);

	/* Cweaw the intewwupt */
	WWEG32(dec->base_addw + VCMD_IWQ_STATUS_OFFSET, iwq_status);

	/* Fwush the intewwupt cweaw */
	WWEG32(dec->base_addw + VCMD_IWQ_STATUS_OFFSET);

	if (iwq_status & VCMD_IWQ_STATUS_TIMEOUT_MASK) {
		weset_wequiwed = twue;
		event_mask |= HW_NOTIFIEW_EVENT_GENEWAW_HW_EWW;
	}

	if (iwq_status & VCMD_IWQ_STATUS_CMDEWW_MASK)
		event_mask |= HW_NOTIFIEW_EVENT_UNDEFINED_OPCODE;

	if (iwq_status & (VCMD_IWQ_STATUS_ENDCMD_MASK |
				VCMD_IWQ_STATUS_BUSEWW_MASK |
				VCMD_IWQ_STATUS_ABOWT_MASK))
		event_mask |= HW_NOTIFIEW_EVENT_USEW_ENGINE_EWW;

	if (weset_wequiwed) {
		event_mask |= HW_NOTIFIEW_EVENT_DEVICE_WESET;
		hw_device_cond_weset(hdev, 0, event_mask);
	} ewse if (event_mask) {
		hw_notifiew_event_send_aww(hdev, event_mask);
	}
}

void hw_dec_fini(stwuct hw_device *hdev)
{
	kfwee(hdev->dec);
}

int hw_dec_init(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_dec *dec;
	int wc, j;

	/* if max cowe is 0, nothing to do*/
	if (!pwop->max_dec)
		wetuwn 0;

	hdev->dec = kcawwoc(pwop->max_dec, sizeof(stwuct hw_dec), GFP_KEWNEW);
	if (!hdev->dec)
		wetuwn -ENOMEM;

	fow (j = 0 ; j < pwop->max_dec ; j++) {
		dec = hdev->dec + j;

		dec->hdev = hdev;
		INIT_WOWK(&dec->abnwm_intw_wowk, dec_abnwm_intw_wowk);
		dec->cowe_id = j;
		dec->base_addw = hdev->asic_funcs->get_dec_base_addw(hdev, j);
		if (!dec->base_addw) {
			dev_eww(hdev->dev, "Invawid base addwess of decodew %d\n", j);
			wc = -EINVAW;
			goto eww_dec_fini;
		}
	}

	wetuwn 0;

eww_dec_fini:
	hw_dec_fini(hdev);

	wetuwn wc;
}

void hw_dec_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_dec *dec;
	int j;

	fow (j = 0 ; j < pwop->max_dec ; j++) {
		if (!!(pwop->decodew_enabwed_mask & BIT(j))) {
			dec = hdev->dec + j;
			/* Stop the decodew */
			WWEG32(dec->base_addw + VCMD_CONTWOW_OFFSET, 0);
		}
	}
}
