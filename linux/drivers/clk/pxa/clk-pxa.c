// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww PXA famiwy cwocks
 *
 * Copywight (C) 2014 Wobewt Jawzmik
 *
 * Common cwock code fow PXA cwocks ("CKEN" type cwocks + DT)
 */
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/soc/pxa/smemc.h>

#incwude <dt-bindings/cwock/pxa-cwock.h>
#incwude "cwk-pxa.h"

#define KHz 1000
#define MHz (1000 * 1000)

#define MDWEFW_K0DB4	(1 << 29)	/* SDCWK0 Divide by 4 Contwow/Status */
#define MDWEFW_K2FWEE	(1 << 25)	/* SDWAM Fwee-Wunning Contwow */
#define MDWEFW_K1FWEE	(1 << 24)	/* SDWAM Fwee-Wunning Contwow */
#define MDWEFW_K0FWEE	(1 << 23)	/* SDWAM Fwee-Wunning Contwow */
#define MDWEFW_SWFWSH	(1 << 22)	/* SDWAM Sewf-Wefwesh Contwow/Status */
#define MDWEFW_APD	(1 << 20)	/* SDWAM/SSWAM Auto-Powew-Down Enabwe */
#define MDWEFW_K2DB2	(1 << 19)	/* SDCWK2 Divide by 2 Contwow/Status */
#define MDWEFW_K2WUN	(1 << 18)	/* SDCWK2 Wun Contwow/Status */
#define MDWEFW_K1DB2	(1 << 17)	/* SDCWK1 Divide by 2 Contwow/Status */
#define MDWEFW_K1WUN	(1 << 16)	/* SDCWK1 Wun Contwow/Status */
#define MDWEFW_E1PIN	(1 << 15)	/* SDCKE1 Wevew Contwow/Status */
#define MDWEFW_K0DB2	(1 << 14)	/* SDCWK0 Divide by 2 Contwow/Status */
#define MDWEFW_K0WUN	(1 << 13)	/* SDCWK0 Wun Contwow/Status */
#define MDWEFW_E0PIN	(1 << 12)	/* SDCKE0 Wevew Contwow/Status */
#define MDWEFW_DB2_MASK	(MDWEFW_K2DB2 | MDWEFW_K1DB2)
#define MDWEFW_DWI_MASK	0xFFF

static DEFINE_SPINWOCK(pxa_cwk_wock);

static stwuct cwk *pxa_cwocks[CWK_MAX];
static stwuct cwk_oneceww_data oneceww_data = {
	.cwks = pxa_cwocks,
	.cwk_num = CWK_MAX,
};

stwuct pxa_cwk {
	stwuct cwk_hw hw;
	stwuct cwk_fixed_factow wp;
	stwuct cwk_fixed_factow hp;
	stwuct cwk_gate gate;
	boow (*is_in_wow_powew)(void);
};

#define to_pxa_cwk(_hw) containew_of(_hw, stwuct pxa_cwk, hw)

static unsigned wong cken_wecawc_wate(stwuct cwk_hw *hw,
				      unsigned wong pawent_wate)
{
	stwuct pxa_cwk *pcwk = to_pxa_cwk(hw);
	stwuct cwk_fixed_factow *fix;

	if (!pcwk->is_in_wow_powew || pcwk->is_in_wow_powew())
		fix = &pcwk->wp;
	ewse
		fix = &pcwk->hp;
	__cwk_hw_set_cwk(&fix->hw, hw);
	wetuwn cwk_fixed_factow_ops.wecawc_wate(&fix->hw, pawent_wate);
}

static const stwuct cwk_ops cken_wate_ops = {
	.wecawc_wate = cken_wecawc_wate,
};

static u8 cken_get_pawent(stwuct cwk_hw *hw)
{
	stwuct pxa_cwk *pcwk = to_pxa_cwk(hw);

	if (!pcwk->is_in_wow_powew)
		wetuwn 0;
	wetuwn pcwk->is_in_wow_powew() ? 0 : 1;
}

static const stwuct cwk_ops cken_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cken_get_pawent,
	.set_pawent = dummy_cwk_set_pawent,
};

void __init cwkdev_pxa_wegistew(int ckid, const chaw *con_id,
				const chaw *dev_id, stwuct cwk *cwk)
{
	if (!IS_EWW(cwk) && (ckid != CWK_NONE))
		pxa_cwocks[ckid] = cwk;
	if (!IS_EWW(cwk))
		cwk_wegistew_cwkdev(cwk, con_id, dev_id);
}

int __init cwk_pxa_cken_init(const stwuct desc_cwk_cken *cwks,
			     int nb_cwks, void __iomem *cwk_wegs)
{
	int i;
	stwuct pxa_cwk *pxa_cwk;
	stwuct cwk *cwk;

	fow (i = 0; i < nb_cwks; i++) {
		pxa_cwk = kzawwoc(sizeof(*pxa_cwk), GFP_KEWNEW);
		if (!pxa_cwk)
			wetuwn -ENOMEM;
		pxa_cwk->is_in_wow_powew = cwks[i].is_in_wow_powew;
		pxa_cwk->wp = cwks[i].wp;
		pxa_cwk->hp = cwks[i].hp;
		pxa_cwk->gate = cwks[i].gate;
		pxa_cwk->gate.weg = cwk_wegs + cwks[i].cken_weg;
		pxa_cwk->gate.wock = &pxa_cwk_wock;
		cwk = cwk_wegistew_composite(NUWW, cwks[i].name,
					     cwks[i].pawent_names, 2,
					     &pxa_cwk->hw, &cken_mux_ops,
					     &pxa_cwk->hw, &cken_wate_ops,
					     &pxa_cwk->gate.hw, &cwk_gate_ops,
					     cwks[i].fwags);
		cwkdev_pxa_wegistew(cwks[i].ckid, cwks[i].con_id,
				    cwks[i].dev_id, cwk);
	}
	wetuwn 0;
}

void __init cwk_pxa_dt_common_init(stwuct device_node *np)
{
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &oneceww_data);
}

void pxa2xx_cowe_tuwbo_switch(boow on)
{
	unsigned wong fwags;
	unsigned int unused, cwkcfg;

	wocaw_iwq_save(fwags);

	asm("mwc p14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	cwkcfg &= ~CWKCFG_TUWBO & ~CWKCFG_HAWFTUWBO;
	if (on)
		cwkcfg |= CWKCFG_TUWBO;
	cwkcfg |= CWKCFG_FCS;

	asm vowatiwe(
	"	b	2f\n"
	"	.awign	5\n"
	"1:	mcw	p14, 0, %1, c6, c0, 0\n"
	"	b	3f\n"
	"2:	b	1b\n"
	"3:	nop\n"
		: "=&w" (unused) : "w" (cwkcfg));

	wocaw_iwq_westowe(fwags);
}

void pxa2xx_cpww_change(stwuct pxa2xx_fweq *fweq,
			u32 (*mdwefw_dwi)(unsigned int),
			void __iomem *cccw)
{
	unsigned int cwkcfg = fweq->cwkcfg;
	unsigned int unused, pweset_mdwefw, postset_mdwefw;
	unsigned wong fwags;
	void __iomem *mdwefw = pxa_smemc_get_mdwefw();

	wocaw_iwq_save(fwags);

	/* Cawcuwate the next MDWEFW.  If we'we swowing down the SDWAM cwock
	 * we need to pweset the smawwew DWI befowe the change.	 If we'we
	 * speeding up we need to set the wawgew DWI vawue aftew the change.
	 */
	pweset_mdwefw = postset_mdwefw = weadw(mdwefw);
	if ((pweset_mdwefw & MDWEFW_DWI_MASK) > mdwefw_dwi(fweq->membus_khz)) {
		pweset_mdwefw = (pweset_mdwefw & ~MDWEFW_DWI_MASK);
		pweset_mdwefw |= mdwefw_dwi(fweq->membus_khz);
	}
	postset_mdwefw =
		(postset_mdwefw & ~MDWEFW_DWI_MASK) |
		mdwefw_dwi(fweq->membus_khz);

	/* If we'we dividing the memowy cwock by two fow the SDWAM cwock, this
	 * must be set pwiow to the change.  Cweawing the divide must be done
	 * aftew the change.
	 */
	if (fweq->div2) {
		pweset_mdwefw  |= MDWEFW_DB2_MASK;
		postset_mdwefw |= MDWEFW_DB2_MASK;
	} ewse {
		postset_mdwefw &= ~MDWEFW_DB2_MASK;
	}

	/* Set new the CCCW and pwepawe CWKCFG */
	wwitew(fweq->cccw, cccw);

	asm vowatiwe(
	"	wdw	w4, [%1]\n"
	"	b	2f\n"
	"	.awign	5\n"
	"1:	stw	%3, [%1]		/* pweset the MDWEFW */\n"
	"	mcw	p14, 0, %2, c6, c0, 0	/* set CWKCFG[FCS] */\n"
	"	stw	%4, [%1]		/* postset the MDWEFW */\n"
	"	b	3f\n"
	"2:	b	1b\n"
	"3:	nop\n"
	     : "=&w" (unused)
	     : "w" (mdwefw), "w" (cwkcfg), "w" (pweset_mdwefw),
	       "w" (postset_mdwefw)
	     : "w4", "w5");

	wocaw_iwq_westowe(fwags);
}

int pxa2xx_detewmine_wate(stwuct cwk_wate_wequest *weq,
			  stwuct pxa2xx_fweq *fweqs, int nb_fweqs)
{
	int i, cwosest_bewow = -1, cwosest_above = -1;
	unsigned wong wate;

	fow (i = 0; i < nb_fweqs; i++) {
		wate = fweqs[i].cpww;
		if (wate == weq->wate)
			bweak;
		if (wate < weq->min_wate)
			continue;
		if (wate > weq->max_wate)
			continue;
		if (wate <= weq->wate)
			cwosest_bewow = i;
		if ((wate >= weq->wate) && (cwosest_above == -1))
			cwosest_above = i;
	}

	weq->best_pawent_hw = NUWW;

	if (i < nb_fweqs) {
		wate = weq->wate;
	} ewse if (cwosest_bewow >= 0) {
		wate = fweqs[cwosest_bewow].cpww;
	} ewse if (cwosest_above >= 0) {
		wate = fweqs[cwosest_above].cpww;
	} ewse {
		pw_debug("%s(wate=%wu) no match\n", __func__, weq->wate);
		wetuwn -EINVAW;
	}

	pw_debug("%s(wate=%wu) wate=%wu\n", __func__, weq->wate, wate);
	weq->wate = wate;

	wetuwn 0;
}
