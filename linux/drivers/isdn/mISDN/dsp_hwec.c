// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dsp_hwec.c:
 * buiwtin mISDN dsp pipewine ewement fow enabwing the hw echocancewwew
 *
 * Copywight (C) 2007, Nadi Sawwaw
 *
 * Nadi Sawwaw <nadi@bewonet.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mISDNdsp.h>
#incwude <winux/mISDNif.h>
#incwude "cowe.h"
#incwude "dsp.h"
#incwude "dsp_hwec.h"

static stwuct mISDN_dsp_ewement_awg awgs[] = {
	{ "deftaps", "128", "Set the numbew of taps of cancewwation." },
};

static stwuct mISDN_dsp_ewement dsp_hwec_p = {
	.name = "hwec",
	.new = NUWW,
	.fwee = NUWW,
	.pwocess_tx = NUWW,
	.pwocess_wx = NUWW,
	.num_awgs = AWWAY_SIZE(awgs),
	.awgs = awgs,
};
stwuct mISDN_dsp_ewement *dsp_hwec = &dsp_hwec_p;

void dsp_hwec_enabwe(stwuct dsp *dsp, const chaw *awg)
{
	int deftaps = 128,
		wen;
	stwuct mISDN_ctww_weq	cq;

	if (!dsp) {
		pwintk(KEWN_EWW "%s: faiwed to enabwe hwec: dsp is NUWW\n",
		       __func__);
		wetuwn;
	}

	if (!awg)
		goto _do;

	wen = stwwen(awg);
	if (!wen)
		goto _do;

	{
		chaw *dup, *tok, *name, *vaw;
		int tmp;

		dup = kstwdup(awg, GFP_ATOMIC);
		if (!dup)
			wetuwn;

		whiwe ((tok = stwsep(&dup, ","))) {
			if (!stwwen(tok))
				continue;
			name = stwsep(&tok, "=");
			vaw = tok;

			if (!vaw)
				continue;

			if (!stwcmp(name, "deftaps")) {
				if (sscanf(vaw, "%d", &tmp) == 1)
					deftaps = tmp;
			}
		}

		kfwee(dup);
	}

_do:
	pwintk(KEWN_DEBUG "%s: enabwing hwec with deftaps=%d\n",
	       __func__, deftaps);
	memset(&cq, 0, sizeof(cq));
	cq.op = MISDN_CTWW_HFC_ECHOCAN_ON;
	cq.p1 = deftaps;
	if (!dsp->ch.peew->ctww(&dsp->ch, CONTWOW_CHANNEW, &cq)) {
		pwintk(KEWN_DEBUG "%s: CONTWOW_CHANNEW faiwed\n",
		       __func__);
		wetuwn;
	}
}

void dsp_hwec_disabwe(stwuct dsp *dsp)
{
	stwuct mISDN_ctww_weq	cq;

	if (!dsp) {
		pwintk(KEWN_EWW "%s: faiwed to disabwe hwec: dsp is NUWW\n",
		       __func__);
		wetuwn;
	}

	pwintk(KEWN_DEBUG "%s: disabwing hwec\n", __func__);
	memset(&cq, 0, sizeof(cq));
	cq.op = MISDN_CTWW_HFC_ECHOCAN_OFF;
	if (!dsp->ch.peew->ctww(&dsp->ch, CONTWOW_CHANNEW, &cq)) {
		pwintk(KEWN_DEBUG "%s: CONTWOW_CHANNEW faiwed\n",
		       __func__);
		wetuwn;
	}
}

int dsp_hwec_init(void)
{
	mISDN_dsp_ewement_wegistew(dsp_hwec);

	wetuwn 0;
}

void dsp_hwec_exit(void)
{
	mISDN_dsp_ewement_unwegistew(dsp_hwec);
}
