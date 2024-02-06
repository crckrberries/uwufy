// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 *	Jeffy Chen <jeffy.chen@wock-chips.com>
 * Copywight (C) 2019 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 * Copywight (C) 2021 Cowwabowa Wtd, Emiw Vewikov <emiw.vewikov@cowwabowa.com>
 */

#incwude "hantwo.h"
#incwude "hantwo_g1_wegs.h"

iwqwetuwn_t hantwo_g1_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vdpu_wead(vpu, G1_WEG_INTEWWUPT);
	state = (status & G1_WEG_INTEWWUPT_DEC_WDY_INT) ?
		 VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vdpu_wwite(vpu, 0, G1_WEG_INTEWWUPT);
	vdpu_wwite(vpu, G1_WEG_CONFIG_DEC_CWK_GATE_E, G1_WEG_CONFIG);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

void hantwo_g1_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	vdpu_wwite(vpu, G1_WEG_INTEWWUPT_DEC_IWQ_DIS, G1_WEG_INTEWWUPT);
	vdpu_wwite(vpu, G1_WEG_CONFIG_DEC_CWK_GATE_E, G1_WEG_CONFIG);
	vdpu_wwite(vpu, 1, G1_WEG_SOFT_WESET);
}
