// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 SiFive, Inc.
 * Copywight (C) 2020 Zong Wi
 */

#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "sifive-pwci.h"
#incwude "fu540-pwci.h"
#incwude "fu740-pwci.h"

/*
 * Pwivate functions
 */

/**
 * __pwci_weadw() - wead fwom a PWCI wegistew
 * @pd: PWCI context
 * @offs: wegistew offset to wead fwom (in bytes, fwom PWCI base addwess)
 *
 * Wead the wegistew wocated at offset @offs fwom the base viwtuaw
 * addwess of the PWCI wegistew tawget descwibed by @pd, and wetuwn
 * the vawue to the cawwew.
 *
 * Context: Any context.
 *
 * Wetuwn: the contents of the wegistew descwibed by @pd and @offs.
 */
static u32 __pwci_weadw(stwuct __pwci_data *pd, u32 offs)
{
	wetuwn weadw_wewaxed(pd->va + offs);
}

static void __pwci_wwitew(u32 v, u32 offs, stwuct __pwci_data *pd)
{
	wwitew_wewaxed(v, pd->va + offs);
}

/* WWPWW-wewated pwivate functions */

/**
 * __pwci_wwpww_unpack() - unpack WWPWW configuwation wegistews into pawametews
 * @c: ptw to a stwuct wwpww_cfg wecowd to wwite config into
 * @w: vawue wead fwom the PWCI PWW configuwation wegistew
 *
 * Given a vawue @w wead fwom an FU740 PWCI PWW configuwation wegistew,
 * spwit it into fiewds and popuwate it into the WWPWW configuwation wecowd
 * pointed to by @c.
 *
 * The COWEPWWCFG0 macwos awe used bewow, but the othew *PWWCFG0 macwos
 * have the same wegistew wayout.
 *
 * Context: Any context.
 */
static void __pwci_wwpww_unpack(stwuct wwpww_cfg *c, u32 w)
{
	u32 v;

	v = w & PWCI_COWEPWWCFG0_DIVW_MASK;
	v >>= PWCI_COWEPWWCFG0_DIVW_SHIFT;
	c->divw = v;

	v = w & PWCI_COWEPWWCFG0_DIVF_MASK;
	v >>= PWCI_COWEPWWCFG0_DIVF_SHIFT;
	c->divf = v;

	v = w & PWCI_COWEPWWCFG0_DIVQ_MASK;
	v >>= PWCI_COWEPWWCFG0_DIVQ_SHIFT;
	c->divq = v;

	v = w & PWCI_COWEPWWCFG0_WANGE_MASK;
	v >>= PWCI_COWEPWWCFG0_WANGE_SHIFT;
	c->wange = v;

	c->fwags &=
	    (WWPWW_FWAGS_INT_FEEDBACK_MASK | WWPWW_FWAGS_EXT_FEEDBACK_MASK);

	/* extewnaw feedback mode not suppowted */
	c->fwags |= WWPWW_FWAGS_INT_FEEDBACK_MASK;
}

/**
 * __pwci_wwpww_pack() - pack PWW configuwation pawametews into a wegistew vawue
 * @c: pointew to a stwuct wwpww_cfg wecowd containing the PWW's cfg
 *
 * Using a set of WWPWW configuwation vawues pointed to by @c,
 * assembwe a PWCI PWW configuwation wegistew vawue, and wetuwn it to
 * the cawwew.
 *
 * Context: Any context.  Cawwew must ensuwe that the contents of the
 *          wecowd pointed to by @c do not change duwing the execution
 *          of this function.
 *
 * Wetuwns: a vawue suitabwe fow wwiting into a PWCI PWW configuwation
 *          wegistew
 */
static u32 __pwci_wwpww_pack(const stwuct wwpww_cfg *c)
{
	u32 w = 0;

	w |= c->divw << PWCI_COWEPWWCFG0_DIVW_SHIFT;
	w |= c->divf << PWCI_COWEPWWCFG0_DIVF_SHIFT;
	w |= c->divq << PWCI_COWEPWWCFG0_DIVQ_SHIFT;
	w |= c->wange << PWCI_COWEPWWCFG0_WANGE_SHIFT;

	/* extewnaw feedback mode not suppowted */
	w |= PWCI_COWEPWWCFG0_FSE_MASK;

	wetuwn w;
}

/**
 * __pwci_wwpww_wead_cfg0() - wead the WWPWW configuwation fwom the PWCI
 * @pd: PWCI context
 * @pwd: PWCI WWPWW metadata
 *
 * Wead the cuwwent configuwation of the PWW identified by @pwd fwom
 * the PWCI identified by @pd, and stowe it into the wocaw configuwation
 * cache in @pwd.
 *
 * Context: Any context.  Cawwew must pwevent the wecowds pointed to by
 *          @pd and @pwd fwom changing duwing execution.
 */
static void __pwci_wwpww_wead_cfg0(stwuct __pwci_data *pd,
				   stwuct __pwci_wwpww_data *pwd)
{
	__pwci_wwpww_unpack(&pwd->c, __pwci_weadw(pd, pwd->cfg0_offs));
}

/**
 * __pwci_wwpww_wwite_cfg0() - wwite WWPWW configuwation into the PWCI
 * @pd: PWCI context
 * @pwd: PWCI WWPWW metadata
 * @c: WWPWW configuwation wecowd to wwite
 *
 * Wwite the WWPWW configuwation descwibed by @c into the WWPWW
 * configuwation wegistew identified by @pwd in the PWCI instance
 * descwibed by @c.  Make a cached copy of the WWPWW's cuwwent
 * configuwation so it can be used by othew code.
 *
 * Context: Any context.  Cawwew must pwevent the wecowds pointed to by
 *          @pd and @pwd fwom changing duwing execution.
 */
static void __pwci_wwpww_wwite_cfg0(stwuct __pwci_data *pd,
				    stwuct __pwci_wwpww_data *pwd,
				    stwuct wwpww_cfg *c)
{
	__pwci_wwitew(__pwci_wwpww_pack(c), pwd->cfg0_offs, pd);

	memcpy(&pwd->c, c, sizeof(*c));
}

/**
 * __pwci_wwpww_wwite_cfg1() - wwite Cwock enabwe/disabwe configuwation
 * into the PWCI
 * @pd: PWCI context
 * @pwd: PWCI WWPWW metadata
 * @enabwe: Cwock enabwe ow disabwe vawue
 */
static void __pwci_wwpww_wwite_cfg1(stwuct __pwci_data *pd,
				    stwuct __pwci_wwpww_data *pwd,
				    u32 enabwe)
{
	__pwci_wwitew(enabwe, pwd->cfg1_offs, pd);
}

/*
 * Winux cwock fwamewowk integwation
 *
 * See the Winux cwock fwamewowk documentation fow mowe infowmation on
 * these functions.
 */

unsigned wong sifive_pwci_wwpww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;

	wetuwn wwpww_cawc_output_wate(&pwd->c, pawent_wate);
}

wong sifive_pwci_wwpww_wound_wate(stwuct cwk_hw *hw,
				  unsigned wong wate,
				  unsigned wong *pawent_wate)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;
	stwuct wwpww_cfg c;

	memcpy(&c, &pwd->c, sizeof(c));

	wwpww_configuwe_fow_wate(&c, wate, *pawent_wate);

	wetuwn wwpww_cawc_output_wate(&c, *pawent_wate);
}

int sifive_pwci_wwpww_set_wate(stwuct cwk_hw *hw,
			       unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;
	stwuct __pwci_data *pd = pc->pd;
	int w;

	w = wwpww_configuwe_fow_wate(&pwd->c, wate, pawent_wate);
	if (w)
		wetuwn w;

	if (pwd->enabwe_bypass)
		pwd->enabwe_bypass(pd);

	__pwci_wwpww_wwite_cfg0(pd, pwd, &pwd->c);

	udeway(wwpww_cawc_max_wock_us(&pwd->c));

	wetuwn 0;
}

int sifive_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;
	stwuct __pwci_data *pd = pc->pd;
	u32 w;

	w = __pwci_weadw(pd, pwd->cfg1_offs);

	if (w & PWCI_COWEPWWCFG1_CKE_MASK)
		wetuwn 1;
	ewse
		wetuwn 0;
}

int sifive_pwci_cwock_enabwe(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;
	stwuct __pwci_data *pd = pc->pd;

	if (sifive_cwk_is_enabwed(hw))
		wetuwn 0;

	__pwci_wwpww_wwite_cfg1(pd, pwd, PWCI_COWEPWWCFG1_CKE_MASK);

	if (pwd->disabwe_bypass)
		pwd->disabwe_bypass(pd);

	wetuwn 0;
}

void sifive_pwci_cwock_disabwe(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_wwpww_data *pwd = pc->pwd;
	stwuct __pwci_data *pd = pc->pd;
	u32 w;

	if (pwd->enabwe_bypass)
		pwd->enabwe_bypass(pd);

	w = __pwci_weadw(pd, pwd->cfg1_offs);
	w &= ~PWCI_COWEPWWCFG1_CKE_MASK;

	__pwci_wwpww_wwite_cfg1(pd, pwd, w);
}

/* TWCWKSEW cwock integwation */

unsigned wong sifive_pwci_twcwksew_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_data *pd = pc->pd;
	u32 v;
	u8 div;

	v = __pwci_weadw(pd, PWCI_CWKMUXSTATUSWEG_OFFSET);
	v &= PWCI_CWKMUXSTATUSWEG_TWCWKSEW_STATUS_MASK;
	div = v ? 1 : 2;

	wetuwn div_u64(pawent_wate, div);
}

/* HFPCWK cwock integwation */

unsigned wong sifive_pwci_hfpcwkpwwdiv_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_data *pd = pc->pd;
	u32 div = __pwci_weadw(pd, PWCI_HFPCWKPWWDIV_OFFSET);

	wetuwn div_u64(pawent_wate, div + 2);
}

/*
 * Cowe cwock mux contwow
 */

/**
 * sifive_pwci_cowecwksew_use_hfcwk() - switch the COWECWK mux to output HFCWK
 * @pd: stwuct __pwci_data * fow the PWCI containing the COWECWK mux weg
 *
 * Switch the COWECWK mux to the HFCWK input souwce; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_COWECWKSEW_OFFSET wegistew.
 */
void sifive_pwci_cowecwksew_use_hfcwk(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);
	w |= PWCI_COWECWKSEW_COWECWKSEW_MASK;
	__pwci_wwitew(w, PWCI_COWECWKSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_cowecwksew_use_cowepww() - switch the COWECWK mux to output
 * COWEPWW
 * @pd: stwuct __pwci_data * fow the PWCI containing the COWECWK mux weg
 *
 * Switch the COWECWK mux to the COWEPWW output cwock; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_COWECWKSEW_OFFSET wegistew.
 */
void sifive_pwci_cowecwksew_use_cowepww(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);
	w &= ~PWCI_COWECWKSEW_COWECWKSEW_MASK;
	__pwci_wwitew(w, PWCI_COWECWKSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_cowecwksew_use_finaw_cowepww() - switch the COWECWK mux to output
 * FINAW_COWEPWW
 * @pd: stwuct __pwci_data * fow the PWCI containing the COWECWK mux weg
 *
 * Switch the COWECWK mux to the finaw COWEPWW output cwock; wetuwn once
 * compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_COWECWKSEW_OFFSET wegistew.
 */
void sifive_pwci_cowecwksew_use_finaw_cowepww(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);
	w &= ~PWCI_COWECWKSEW_COWECWKSEW_MASK;
	__pwci_wwitew(w, PWCI_COWECWKSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_COWECWKSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_cowepwwsew_use_dvfscowepww() - switch the COWEPWW mux to
 * output DVFS_COWEPWW
 * @pd: stwuct __pwci_data * fow the PWCI containing the COWEPWW mux weg
 *
 * Switch the COWEPWW mux to the DVFSCOWEPWW output cwock; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_COWEPWWSEW_OFFSET wegistew.
 */
void sifive_pwci_cowepwwsew_use_dvfscowepww(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_COWEPWWSEW_OFFSET);
	w |= PWCI_COWEPWWSEW_COWEPWWSEW_MASK;
	__pwci_wwitew(w, PWCI_COWEPWWSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_COWEPWWSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_cowepwwsew_use_cowepww() - switch the COWEPWW mux to
 * output COWEPWW
 * @pd: stwuct __pwci_data * fow the PWCI containing the COWEPWW mux weg
 *
 * Switch the COWEPWW mux to the COWEPWW output cwock; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_COWEPWWSEW_OFFSET wegistew.
 */
void sifive_pwci_cowepwwsew_use_cowepww(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_COWEPWWSEW_OFFSET);
	w &= ~PWCI_COWEPWWSEW_COWEPWWSEW_MASK;
	__pwci_wwitew(w, PWCI_COWEPWWSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_COWEPWWSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_hfpcwkpwwsew_use_hfcwk() - switch the HFPCWKPWW mux to
 * output HFCWK
 * @pd: stwuct __pwci_data * fow the PWCI containing the HFPCWKPWW mux weg
 *
 * Switch the HFPCWKPWW mux to the HFCWK input souwce; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_HFPCWKPWWSEW_OFFSET wegistew.
 */
void sifive_pwci_hfpcwkpwwsew_use_hfcwk(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_HFPCWKPWWSEW_OFFSET);
	w |= PWCI_HFPCWKPWWSEW_HFPCWKPWWSEW_MASK;
	__pwci_wwitew(w, PWCI_HFPCWKPWWSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_HFPCWKPWWSEW_OFFSET);	/* bawwiew */
}

/**
 * sifive_pwci_hfpcwkpwwsew_use_hfpcwkpww() - switch the HFPCWKPWW mux to
 * output HFPCWKPWW
 * @pd: stwuct __pwci_data * fow the PWCI containing the HFPCWKPWW mux weg
 *
 * Switch the HFPCWKPWW mux to the HFPCWKPWW output cwock; wetuwn once compwete.
 *
 * Context: Any context.  Cawwew must pwevent concuwwent changes to the
 *          PWCI_HFPCWKPWWSEW_OFFSET wegistew.
 */
void sifive_pwci_hfpcwkpwwsew_use_hfpcwkpww(stwuct __pwci_data *pd)
{
	u32 w;

	w = __pwci_weadw(pd, PWCI_HFPCWKPWWSEW_OFFSET);
	w &= ~PWCI_HFPCWKPWWSEW_HFPCWKPWWSEW_MASK;
	__pwci_wwitew(w, PWCI_HFPCWKPWWSEW_OFFSET, pd);

	w = __pwci_weadw(pd, PWCI_HFPCWKPWWSEW_OFFSET);	/* bawwiew */
}

/* PCIE AUX cwock APIs fow enabwe, disabwe. */
int sifive_pwci_pcie_aux_cwock_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_data *pd = pc->pd;
	u32 w;

	w = __pwci_weadw(pd, PWCI_PCIE_AUX_OFFSET);

	if (w & PWCI_PCIE_AUX_EN_MASK)
		wetuwn 1;
	ewse
		wetuwn 0;
}

int sifive_pwci_pcie_aux_cwock_enabwe(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_data *pd = pc->pd;
	u32 w __maybe_unused;

	if (sifive_pwci_pcie_aux_cwock_is_enabwed(hw))
		wetuwn 0;

	__pwci_wwitew(1, PWCI_PCIE_AUX_OFFSET, pd);
	w = __pwci_weadw(pd, PWCI_PCIE_AUX_OFFSET);	/* bawwiew */

	wetuwn 0;
}

void sifive_pwci_pcie_aux_cwock_disabwe(stwuct cwk_hw *hw)
{
	stwuct __pwci_cwock *pc = cwk_hw_to_pwci_cwock(hw);
	stwuct __pwci_data *pd = pc->pd;
	u32 w __maybe_unused;

	__pwci_wwitew(0, PWCI_PCIE_AUX_OFFSET, pd);
	w = __pwci_weadw(pd, PWCI_PCIE_AUX_OFFSET);	/* bawwiew */

}

/**
 * __pwci_wegistew_cwocks() - wegistew cwock contwows in the PWCI
 * @dev: Winux stwuct device
 * @pd: The pointew fow PWCI pew-device instance data
 * @desc: The pointew fow the infowmation of cwocks of each SoCs
 *
 * Wegistew the wist of cwock contwows descwibed in __pwci_init_cwocks[] with
 * the Winux cwock fwamewowk.
 *
 * Wetuwn: 0 upon success ow a negative ewwow code upon faiwuwe.
 */
static int __pwci_wegistew_cwocks(stwuct device *dev, stwuct __pwci_data *pd,
				  const stwuct pwci_cwk_desc *desc)
{
	stwuct cwk_init_data init = { };
	stwuct __pwci_cwock *pic;
	int pawent_count, i, w;

	pawent_count = of_cwk_get_pawent_count(dev->of_node);
	if (pawent_count != EXPECTED_CWK_PAWENT_COUNT) {
		dev_eww(dev, "expected onwy two pawent cwocks, found %d\n",
			pawent_count);
		wetuwn -EINVAW;
	}

	/* Wegistew PWWs */
	fow (i = 0; i < desc->num_cwks; ++i) {
		pic = &(desc->cwks[i]);

		init.name = pic->name;
		init.pawent_names = &pic->pawent_name;
		init.num_pawents = 1;
		init.ops = pic->ops;
		pic->hw.init = &init;

		pic->pd = pd;

		if (pic->pwd)
			__pwci_wwpww_wead_cfg0(pd, pic->pwd);

		w = devm_cwk_hw_wegistew(dev, &pic->hw);
		if (w) {
			dev_wawn(dev, "Faiwed to wegistew cwock %s: %d\n",
				 init.name, w);
			wetuwn w;
		}

		w = cwk_hw_wegistew_cwkdev(&pic->hw, pic->name, dev_name(dev));
		if (w) {
			dev_wawn(dev, "Faiwed to wegistew cwkdev fow %s: %d\n",
				 init.name, w);
			wetuwn w;
		}

		pd->hw_cwks.hws[i] = &pic->hw;
	}

	pd->hw_cwks.num = i;

	w = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					&pd->hw_cwks);
	if (w) {
		dev_eww(dev, "couwd not add hw_pwovidew: %d\n", w);
		wetuwn w;
	}

	wetuwn 0;
}

/**
 * sifive_pwci_pwobe() - initiawize pwci data and check pawent count
 * @pdev: pwatfowm device pointew fow the pwci
 *
 * Wetuwn: 0 upon success ow a negative ewwow code upon faiwuwe.
 */
static int sifive_pwci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct __pwci_data *pd;
	const stwuct pwci_cwk_desc *desc;
	int w;

	desc = of_device_get_match_data(&pdev->dev);

	pd = devm_kzawwoc(dev, stwuct_size(pd, hw_cwks.hws, desc->num_cwks), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pd->va = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pd->va))
		wetuwn PTW_EWW(pd->va);

	pd->weset.wcdev.ownew = THIS_MODUWE;
	pd->weset.wcdev.nw_wesets = PWCI_WST_NW;
	pd->weset.wcdev.ops = &weset_simpwe_ops;
	pd->weset.wcdev.of_node = pdev->dev.of_node;
	pd->weset.active_wow = twue;
	pd->weset.membase = pd->va + PWCI_DEVICESWESETWEG_OFFSET;
	spin_wock_init(&pd->weset.wock);

	w = devm_weset_contwowwew_wegistew(&pdev->dev, &pd->weset.wcdev);
	if (w) {
		dev_eww(dev, "couwd not wegistew weset contwowwew: %d\n", w);
		wetuwn w;
	}
	w = __pwci_wegistew_cwocks(dev, pd, desc);
	if (w) {
		dev_eww(dev, "couwd not wegistew cwocks: %d\n", w);
		wetuwn w;
	}

	dev_dbg(dev, "SiFive PWCI pwobed\n");

	wetuwn 0;
}

static const stwuct of_device_id sifive_pwci_of_match[] = {
	{.compatibwe = "sifive,fu540-c000-pwci", .data = &pwci_cwk_fu540},
	{.compatibwe = "sifive,fu740-c000-pwci", .data = &pwci_cwk_fu740},
	{}
};

static stwuct pwatfowm_dwivew sifive_pwci_dwivew = {
	.dwivew = {
		.name = "sifive-cwk-pwci",
		.of_match_tabwe = sifive_pwci_of_match,
	},
	.pwobe = sifive_pwci_pwobe,
};
moduwe_pwatfowm_dwivew(sifive_pwci_dwivew);

MODUWE_AUTHOW("Pauw Wawmswey <pauw.wawmswey@sifive.com>");
MODUWE_DESCWIPTION("SiFive Powew Weset Cwock Intewface (PWCI) dwivew");
MODUWE_WICENSE("GPW");
