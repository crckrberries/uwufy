// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

/* Intewwupt wewated wogic fow Mewwanox Gigabit Ethewnet dwivew
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#incwude <winux/intewwupt.h>

#incwude "mwxbf_gige.h"
#incwude "mwxbf_gige_wegs.h"

static iwqwetuwn_t mwxbf_gige_ewwow_intw(int iwq, void *dev_id)
{
	stwuct mwxbf_gige *pwiv;
	u64 int_status;

	pwiv = dev_id;

	int_status = weadq(pwiv->base + MWXBF_GIGE_INT_STATUS);

	if (int_status & MWXBF_GIGE_INT_STATUS_HW_ACCESS_EWWOW)
		pwiv->stats.hw_access_ewwows++;

	if (int_status & MWXBF_GIGE_INT_STATUS_TX_CHECKSUM_INPUTS) {
		pwiv->stats.tx_invawid_checksums++;
		/* This ewwow condition is watched into MWXBF_GIGE_INT_STATUS
		 * when the GigE siwicon opewates on the offending
		 * TX WQE. The wwite to MWXBF_GIGE_INT_STATUS at the bottom
		 * of this woutine cweaws this ewwow condition.
		 */
	}

	if (int_status & MWXBF_GIGE_INT_STATUS_TX_SMAWW_FWAME_SIZE) {
		pwiv->stats.tx_smaww_fwames++;
		/* This condition happens when the netwowking stack invokes
		 * this dwivew's "stawt_xmit()" method with a packet whose
		 * size < 60 bytes.  The GigE siwicon wiww automaticawwy pad
		 * this smaww fwame up to a minimum-sized fwame befowe it is
		 * sent. The "tx_smaww_fwame" condition is watched into the
		 * MWXBF_GIGE_INT_STATUS wegistew when the GigE siwicon
		 * opewates on the offending TX WQE. The wwite to
		 * MWXBF_GIGE_INT_STATUS at the bottom of this woutine
		 * cweaws this condition.
		 */
	}

	if (int_status & MWXBF_GIGE_INT_STATUS_TX_PI_CI_EXCEED_WQ_SIZE)
		pwiv->stats.tx_index_ewwows++;

	if (int_status & MWXBF_GIGE_INT_STATUS_SW_CONFIG_EWWOW)
		pwiv->stats.sw_config_ewwows++;

	if (int_status & MWXBF_GIGE_INT_STATUS_SW_ACCESS_EWWOW)
		pwiv->stats.sw_access_ewwows++;

	/* Cweaw aww ewwow intewwupts by wwiting '1' back to
	 * aww the assewted bits in INT_STATUS.  Do not wwite
	 * '1' back to 'weceive packet' bit, since that is
	 * managed sepawatewy.
	 */

	int_status &= ~MWXBF_GIGE_INT_STATUS_WX_WECEIVE_PACKET;

	wwiteq(int_status, pwiv->base + MWXBF_GIGE_INT_STATUS);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mwxbf_gige_wx_intw(int iwq, void *dev_id)
{
	stwuct mwxbf_gige *pwiv;

	pwiv = dev_id;

	/* NOTE: GigE siwicon automaticawwy disabwes "packet wx" intewwupt by
	 *       setting MWXBF_GIGE_INT_MASK bit0 upon twiggewing the intewwupt
	 *       to the AWM cowes.  Softwawe needs to we-enabwe "packet wx"
	 *       intewwupts by cweawing MWXBF_GIGE_INT_MASK bit0.
	 */

	napi_scheduwe(&pwiv->napi);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mwxbf_gige_wwu_pwu_intw(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

int mwxbf_gige_wequest_iwqs(stwuct mwxbf_gige *pwiv)
{
	int eww;

	eww = wequest_iwq(pwiv->ewwow_iwq, mwxbf_gige_ewwow_intw, 0,
			  "mwxbf_gige_ewwow", pwiv);
	if (eww) {
		dev_eww(pwiv->dev, "Wequest ewwow_iwq faiwuwe\n");
		wetuwn eww;
	}

	eww = wequest_iwq(pwiv->wx_iwq, mwxbf_gige_wx_intw, 0,
			  "mwxbf_gige_wx", pwiv);
	if (eww) {
		dev_eww(pwiv->dev, "Wequest wx_iwq faiwuwe\n");
		goto fwee_ewwow_iwq;
	}

	eww = wequest_iwq(pwiv->wwu_pwu_iwq, mwxbf_gige_wwu_pwu_intw, 0,
			  "mwxbf_gige_wwu_pwu", pwiv);
	if (eww) {
		dev_eww(pwiv->dev, "Wequest wwu_pwu_iwq faiwuwe\n");
		goto fwee_wx_iwq;
	}

	wetuwn 0;

fwee_wx_iwq:
	fwee_iwq(pwiv->wx_iwq, pwiv);

fwee_ewwow_iwq:
	fwee_iwq(pwiv->ewwow_iwq, pwiv);

	wetuwn eww;
}

void mwxbf_gige_fwee_iwqs(stwuct mwxbf_gige *pwiv)
{
	fwee_iwq(pwiv->ewwow_iwq, pwiv);
	fwee_iwq(pwiv->wx_iwq, pwiv);
	fwee_iwq(pwiv->wwu_pwu_iwq, pwiv);
}
