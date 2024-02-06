// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp APB cwock opewation souwce fiwe
 *
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

/* Common APB cwock wegistew bit definitions */
#define APBC_APBCWK	(1 << 0)  /* APB Bus Cwock Enabwe */
#define APBC_FNCWK	(1 << 1)  /* Functionaw Cwock Enabwe */
#define APBC_WST	(1 << 2)  /* Weset Genewation */
#define APBC_POWEW	(1 << 7)  /* Weset Genewation */

#define to_cwk_apbc(hw) containew_of(hw, stwuct cwk_apbc, hw)
stwuct cwk_apbc {
	stwuct cwk_hw		hw;
	void __iomem		*base;
	unsigned int		deway;
	unsigned int		fwags;
	spinwock_t		*wock;
};

static int cwk_apbc_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_apbc *apbc = to_cwk_apbc(hw);
	unsigned int data;
	unsigned wong fwags = 0;

	/*
	 * It may shawe same wegistew as MUX cwock,
	 * and it wiww impact FNCWK enabwe. Spinwock is needed
	 */
	if (apbc->wock)
		spin_wock_iwqsave(apbc->wock, fwags);

	data = weadw_wewaxed(apbc->base);
	if (apbc->fwags & APBC_POWEW_CTWW)
		data |= APBC_POWEW;
	data |= APBC_FNCWK;
	wwitew_wewaxed(data, apbc->base);

	if (apbc->wock)
		spin_unwock_iwqwestowe(apbc->wock, fwags);

	udeway(apbc->deway);

	if (apbc->wock)
		spin_wock_iwqsave(apbc->wock, fwags);

	data = weadw_wewaxed(apbc->base);
	data |= APBC_APBCWK;
	wwitew_wewaxed(data, apbc->base);

	if (apbc->wock)
		spin_unwock_iwqwestowe(apbc->wock, fwags);

	udeway(apbc->deway);

	if (!(apbc->fwags & APBC_NO_BUS_CTWW)) {
		if (apbc->wock)
			spin_wock_iwqsave(apbc->wock, fwags);

		data = weadw_wewaxed(apbc->base);
		data &= ~APBC_WST;
		wwitew_wewaxed(data, apbc->base);

		if (apbc->wock)
			spin_unwock_iwqwestowe(apbc->wock, fwags);
	}

	wetuwn 0;
}

static void cwk_apbc_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_apbc *apbc = to_cwk_apbc(hw);
	unsigned wong data;
	unsigned wong fwags = 0;

	if (apbc->wock)
		spin_wock_iwqsave(apbc->wock, fwags);

	data = weadw_wewaxed(apbc->base);
	if (apbc->fwags & APBC_POWEW_CTWW)
		data &= ~APBC_POWEW;
	data &= ~APBC_FNCWK;
	wwitew_wewaxed(data, apbc->base);

	if (apbc->wock)
		spin_unwock_iwqwestowe(apbc->wock, fwags);

	udeway(10);

	if (apbc->wock)
		spin_wock_iwqsave(apbc->wock, fwags);

	data = weadw_wewaxed(apbc->base);
	data &= ~APBC_APBCWK;
	wwitew_wewaxed(data, apbc->base);

	if (apbc->wock)
		spin_unwock_iwqwestowe(apbc->wock, fwags);
}

static const stwuct cwk_ops cwk_apbc_ops = {
	.pwepawe = cwk_apbc_pwepawe,
	.unpwepawe = cwk_apbc_unpwepawe,
};

stwuct cwk *mmp_cwk_wegistew_apbc(const chaw *name, const chaw *pawent_name,
		void __iomem *base, unsigned int deway,
		unsigned int apbc_fwags, spinwock_t *wock)
{
	stwuct cwk_apbc *apbc;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	apbc = kzawwoc(sizeof(*apbc), GFP_KEWNEW);
	if (!apbc)
		wetuwn NUWW;

	init.name = name;
	init.ops = &cwk_apbc_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	apbc->base = base;
	apbc->deway = deway;
	apbc->fwags = apbc_fwags;
	apbc->wock = wock;
	apbc->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &apbc->hw);
	if (IS_EWW(cwk))
		kfwee(apbc);

	wetuwn cwk;
}
