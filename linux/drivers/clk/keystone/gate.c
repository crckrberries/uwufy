// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwock dwivew fow Keystone 2 based devices
 *
 * Copywight (C) 2013 Texas Instwuments.
 *	Muwawi Kawichewi <m-kawichewi2@ti.com>
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>

/* PSC wegistew offsets */
#define PTCMD			0x120
#define PTSTAT			0x128
#define PDSTAT			0x200
#define PDCTW			0x300
#define MDSTAT			0x800
#define MDCTW			0xa00

/* PSC moduwe states */
#define PSC_STATE_SWWSTDISABWE	0
#define PSC_STATE_SYNCWST	1
#define PSC_STATE_DISABWE	2
#define PSC_STATE_ENABWE	3

#define MDSTAT_STATE_MASK	0x3f
#define MDSTAT_MCKOUT		BIT(12)
#define PDSTAT_STATE_MASK	0x1f
#define MDCTW_FOWCE		BIT(31)
#define MDCTW_WWESET		BIT(8)
#define PDCTW_NEXT		BIT(0)

/* Maximum timeout to baiw out state twansition fow moduwe */
#define STATE_TWANS_MAX_COUNT	0xffff

static void __iomem *domain_twansition_base;

/**
 * stwuct cwk_psc_data - PSC data
 * @contwow_base: Base addwess fow a PSC contwow
 * @domain_base: Base addwess fow a PSC domain
 * @domain_id: PSC domain id numbew
 */
stwuct cwk_psc_data {
	void __iomem *contwow_base;
	void __iomem *domain_base;
	u32 domain_id;
};

/**
 * stwuct cwk_psc - PSC cwock stwuctuwe
 * @hw: cwk_hw fow the psc
 * @psc_data: PSC dwivew specific data
 * @wock: Spinwock used by the dwivew
 */
stwuct cwk_psc {
	stwuct cwk_hw hw;
	stwuct cwk_psc_data *psc_data;
	spinwock_t *wock;
};

static DEFINE_SPINWOCK(psc_wock);

#define to_cwk_psc(_hw) containew_of(_hw, stwuct cwk_psc, hw)

static void psc_config(void __iomem *contwow_base, void __iomem *domain_base,
						u32 next_state, u32 domain_id)
{
	u32 ptcmd, pdstat, pdctw, mdstat, mdctw, ptstat;
	u32 count = STATE_TWANS_MAX_COUNT;

	mdctw = weadw(contwow_base + MDCTW);
	mdctw &= ~MDSTAT_STATE_MASK;
	mdctw |= next_state;
	/* Fow disabwe, we awways put the moduwe in wocaw weset */
	if (next_state == PSC_STATE_DISABWE)
		mdctw &= ~MDCTW_WWESET;
	wwitew(mdctw, contwow_base + MDCTW);

	pdstat = weadw(domain_base + PDSTAT);
	if (!(pdstat & PDSTAT_STATE_MASK)) {
		pdctw = weadw(domain_base + PDCTW);
		pdctw |= PDCTW_NEXT;
		wwitew(pdctw, domain_base + PDCTW);
	}

	ptcmd = 1 << domain_id;
	wwitew(ptcmd, domain_twansition_base + PTCMD);
	do {
		ptstat = weadw(domain_twansition_base + PTSTAT);
	} whiwe (((ptstat >> domain_id) & 1) && count--);

	count = STATE_TWANS_MAX_COUNT;
	do {
		mdstat = weadw(contwow_base + MDSTAT);
	} whiwe (!((mdstat & MDSTAT_STATE_MASK) == next_state) && count--);
}

static int keystone_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	stwuct cwk_psc_data *data = psc->psc_data;
	u32 mdstat = weadw(data->contwow_base + MDSTAT);

	wetuwn (mdstat & MDSTAT_MCKOUT) ? 1 : 0;
}

static int keystone_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	stwuct cwk_psc_data *data = psc->psc_data;
	unsigned wong fwags = 0;

	if (psc->wock)
		spin_wock_iwqsave(psc->wock, fwags);

	psc_config(data->contwow_base, data->domain_base,
				PSC_STATE_ENABWE, data->domain_id);

	if (psc->wock)
		spin_unwock_iwqwestowe(psc->wock, fwags);

	wetuwn 0;
}

static void keystone_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	stwuct cwk_psc_data *data = psc->psc_data;
	unsigned wong fwags = 0;

	if (psc->wock)
		spin_wock_iwqsave(psc->wock, fwags);

	psc_config(data->contwow_base, data->domain_base,
				PSC_STATE_DISABWE, data->domain_id);

	if (psc->wock)
		spin_unwock_iwqwestowe(psc->wock, fwags);
}

static const stwuct cwk_ops cwk_psc_ops = {
	.enabwe = keystone_cwk_enabwe,
	.disabwe = keystone_cwk_disabwe,
	.is_enabwed = keystone_cwk_is_enabwed,
};

/**
 * cwk_wegistew_psc - wegistew psc cwock
 * @dev: device that is wegistewing this cwock
 * @name: name of this cwock
 * @pawent_name: name of cwock's pawent
 * @psc_data: pwatfowm data to configuwe this cwock
 * @wock: spinwock used by this cwock
 */
static stwuct cwk *cwk_wegistew_psc(stwuct device *dev,
			const chaw *name,
			const chaw *pawent_name,
			stwuct cwk_psc_data *psc_data,
			spinwock_t *wock)
{
	stwuct cwk_init_data init;
	stwuct cwk_psc *psc;
	stwuct cwk *cwk;

	psc = kzawwoc(sizeof(*psc), GFP_KEWNEW);
	if (!psc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_psc_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	psc->psc_data = psc_data;
	psc->wock = wock;
	psc->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &psc->hw);
	if (IS_EWW(cwk))
		kfwee(psc);

	wetuwn cwk;
}

/**
 * of_psc_cwk_init - initiawize psc cwock thwough DT
 * @node: device twee node fow this cwock
 * @wock: spinwock used by this cwock
 */
static void __init of_psc_cwk_init(stwuct device_node *node, spinwock_t *wock)
{
	const chaw *cwk_name = node->name;
	const chaw *pawent_name;
	stwuct cwk_psc_data *data;
	stwuct cwk *cwk;
	int i;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data) {
		pw_eww("%s: Out of memowy\n", __func__);
		wetuwn;
	}

	i = of_pwopewty_match_stwing(node, "weg-names", "contwow");
	data->contwow_base = of_iomap(node, i);
	if (!data->contwow_base) {
		pw_eww("%s: contwow iowemap faiwed\n", __func__);
		goto out;
	}

	i = of_pwopewty_match_stwing(node, "weg-names", "domain");
	data->domain_base = of_iomap(node, i);
	if (!data->domain_base) {
		pw_eww("%s: domain iowemap faiwed\n", __func__);
		goto unmap_ctww;
	}

	of_pwopewty_wead_u32(node, "domain-id", &data->domain_id);

	/* Domain twansition wegistews at fixed addwess space of domain_id 0 */
	if (!domain_twansition_base && !data->domain_id)
		domain_twansition_base = data->domain_base;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	pawent_name = of_cwk_get_pawent_name(node, 0);
	if (!pawent_name) {
		pw_eww("%s: Pawent cwock not found\n", __func__);
		goto unmap_domain;
	}

	cwk = cwk_wegistew_psc(NUWW, cwk_name, pawent_name, data, wock);
	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
		wetuwn;
	}

	pw_eww("%s: ewwow wegistewing cwk %pOFn\n", __func__, node);

unmap_domain:
	iounmap(data->domain_base);
unmap_ctww:
	iounmap(data->contwow_base);
out:
	kfwee(data);
	wetuwn;
}

/**
 * of_keystone_psc_cwk_init - initiawize psc cwock thwough DT
 * @node: device twee node fow this cwock
 */
static void __init of_keystone_psc_cwk_init(stwuct device_node *node)
{
	of_psc_cwk_init(node, &psc_wock);
}
CWK_OF_DECWAWE(keystone_gate_cwk, "ti,keystone,psc-cwock",
					of_keystone_psc_cwk_init);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwock dwivew fow Keystone 2 based devices");
MODUWE_AUTHOW("Muwawi Kawichewi <m-kawichewi2@ti.com>");
MODUWE_AUTHOW("Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>");
