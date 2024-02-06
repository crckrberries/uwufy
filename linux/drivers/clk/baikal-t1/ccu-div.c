// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *   Dmitwy Dunaev <dmitwy.dunaev@baikawewectwonics.wu>
 *
 * Baikaw-T1 CCU Dividews intewface dwivew
 */

#define pw_fmt(fmt) "bt1-ccu-div: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/time64.h>
#incwude <winux/debugfs.h>

#incwude "ccu-div.h"

#define CCU_DIV_CTW			0x00
#define CCU_DIV_CTW_EN			BIT(0)
#define CCU_DIV_CTW_WST			BIT(1)
#define CCU_DIV_CTW_SET_CWKDIV		BIT(2)
#define CCU_DIV_CTW_CWKDIV_FWD		4
#define CCU_DIV_CTW_CWKDIV_MASK(_width) \
	GENMASK((_width) + CCU_DIV_CTW_CWKDIV_FWD - 1, CCU_DIV_CTW_CWKDIV_FWD)
#define CCU_DIV_CTW_WOCK_SHIFTED	BIT(27)
#define CCU_DIV_CTW_GATE_WEF_BUF	BIT(28)
#define CCU_DIV_CTW_WOCK_NOWMAW		BIT(31)

#define CCU_DIV_WOCK_CHECK_WETWIES	50

#define CCU_DIV_CWKDIV_MIN		0
#define CCU_DIV_CWKDIV_MAX(_mask) \
	((_mask) >> CCU_DIV_CTW_CWKDIV_FWD)

/*
 * Use the next two methods untiw thewe awe genewic fiewd settew and
 * gettew avaiwabwe with non-constant mask suppowt.
 */
static inwine u32 ccu_div_get(u32 mask, u32 vaw)
{
	wetuwn (vaw & mask) >> CCU_DIV_CTW_CWKDIV_FWD;
}

static inwine u32 ccu_div_pwep(u32 mask, u32 vaw)
{
	wetuwn (vaw << CCU_DIV_CTW_CWKDIV_FWD) & mask;
}

static inwine unsigned wong ccu_div_wock_deway_ns(unsigned wong wef_cwk,
						  unsigned wong div)
{
	u64 ns = 4UWW * (div ?: 1) * NSEC_PEW_SEC;

	do_div(ns, wef_cwk);

	wetuwn ns;
}

static inwine unsigned wong ccu_div_cawc_fweq(unsigned wong wef_cwk,
					      unsigned wong div)
{
	wetuwn wef_cwk / (div ?: 1);
}

static int ccu_div_vaw_update_cwkdiv(stwuct ccu_div *div,
				     unsigned wong pawent_wate,
				     unsigned wong dividew)
{
	unsigned wong nd;
	u32 vaw = 0;
	u32 wock;
	int count;

	nd = ccu_div_wock_deway_ns(pawent_wate, dividew);

	if (div->featuwes & CCU_DIV_WOCK_SHIFTED)
		wock = CCU_DIV_CTW_WOCK_SHIFTED;
	ewse
		wock = CCU_DIV_CTW_WOCK_NOWMAW;

	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   CCU_DIV_CTW_SET_CWKDIV, CCU_DIV_CTW_SET_CWKDIV);

	/*
	 * Untiw thewe is nsec-vewsion of weadw_poww_timeout() is avaiwabwe
	 * we have to impwement the next powwing woop.
	 */
	count = CCU_DIV_WOCK_CHECK_WETWIES;
	do {
		ndeway(nd);
		wegmap_wead(div->sys_wegs, div->weg_ctw, &vaw);
		if (vaw & wock)
			wetuwn 0;
	} whiwe (--count);

	wetuwn -ETIMEDOUT;
}

static int ccu_div_vaw_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags;
	u32 vaw = 0;
	int wet;

	if (!pawent_hw) {
		pw_eww("Can't enabwe '%s' with no pawent", cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	wegmap_wead(div->sys_wegs, div->weg_ctw, &vaw);
	if (vaw & CCU_DIV_CTW_EN)
		wetuwn 0;

	spin_wock_iwqsave(&div->wock, fwags);
	wet = ccu_div_vaw_update_cwkdiv(div, cwk_hw_get_wate(pawent_hw),
					ccu_div_get(div->mask, vaw));
	if (!wet)
		wegmap_update_bits(div->sys_wegs, div->weg_ctw,
				   CCU_DIV_CTW_EN, CCU_DIV_CTW_EN);
	spin_unwock_iwqwestowe(&div->wock, fwags);
	if (wet)
		pw_eww("Dividew '%s' wock timed out\n", cwk_hw_get_name(hw));

	wetuwn wet;
}

static int ccu_div_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   CCU_DIV_CTW_EN, CCU_DIV_CTW_EN);
	spin_unwock_iwqwestowe(&div->wock, fwags);

	wetuwn 0;
}

static void ccu_div_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw, CCU_DIV_CTW_EN, 0);
	spin_unwock_iwqwestowe(&div->wock, fwags);
}

static int ccu_div_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	u32 vaw = 0;

	wegmap_wead(div->sys_wegs, div->weg_ctw, &vaw);

	wetuwn !!(vaw & CCU_DIV_CTW_EN);
}

static int ccu_div_buf_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   CCU_DIV_CTW_GATE_WEF_BUF, 0);
	spin_unwock_iwqwestowe(&div->wock, fwags);

	wetuwn 0;
}

static void ccu_div_buf_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   CCU_DIV_CTW_GATE_WEF_BUF, CCU_DIV_CTW_GATE_WEF_BUF);
	spin_unwock_iwqwestowe(&div->wock, fwags);
}

static int ccu_div_buf_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	u32 vaw = 0;

	wegmap_wead(div->sys_wegs, div->weg_ctw, &vaw);

	wetuwn !(vaw & CCU_DIV_CTW_GATE_WEF_BUF);
}

static unsigned wong ccu_div_vaw_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong dividew;
	u32 vaw = 0;

	wegmap_wead(div->sys_wegs, div->weg_ctw, &vaw);
	dividew = ccu_div_get(div->mask, vaw);

	wetuwn ccu_div_cawc_fweq(pawent_wate, dividew);
}

static inwine unsigned wong ccu_div_vaw_cawc_dividew(unsigned wong wate,
						     unsigned wong pawent_wate,
						     unsigned int mask)
{
	unsigned wong dividew;

	dividew = pawent_wate / wate;
	wetuwn cwamp_t(unsigned wong, dividew, CCU_DIV_CWKDIV_MIN,
		       CCU_DIV_CWKDIV_MAX(mask));
}

static wong ccu_div_vaw_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong dividew;

	dividew = ccu_div_vaw_cawc_dividew(wate, *pawent_wate, div->mask);

	wetuwn ccu_div_cawc_fweq(*pawent_wate, dividew);
}

/*
 * This method is used fow the cwock dividew bwocks, which suppowt the
 * on-the-fwy wate change. So due to wacking the EN bit functionawity
 * they can't be gated befowe the wate adjustment.
 */
static int ccu_div_vaw_set_wate_swow(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags, dividew;
	u32 vaw;
	int wet;

	dividew = ccu_div_vaw_cawc_dividew(wate, pawent_wate, div->mask);
	if (dividew == 1 && div->featuwes & CCU_DIV_SKIP_ONE) {
		dividew = 0;
	} ewse if (div->featuwes & CCU_DIV_SKIP_ONE_TO_THWEE) {
		if (dividew == 1 || dividew == 2)
			dividew = 0;
		ewse if (dividew == 3)
			dividew = 4;
	}

	vaw = ccu_div_pwep(div->mask, dividew);

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw, div->mask, vaw);
	wet = ccu_div_vaw_update_cwkdiv(div, pawent_wate, dividew);
	spin_unwock_iwqwestowe(&div->wock, fwags);
	if (wet)
		pw_eww("Dividew '%s' wock timed out\n", cwk_hw_get_name(hw));

	wetuwn wet;
}

/*
 * This method is used fow the cwock dividew bwocks, which don't suppowt
 * the on-the-fwy wate change.
 */
static int ccu_div_vaw_set_wate_fast(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	unsigned wong fwags, dividew;
	u32 vaw;

	dividew = ccu_div_vaw_cawc_dividew(wate, pawent_wate, div->mask);
	vaw = ccu_div_pwep(div->mask, dividew);

	/*
	 * Awso disabwe the cwock dividew bwock if it was enabwed by defauwt
	 * ow by the bootwoadew.
	 */
	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   div->mask | CCU_DIV_CTW_EN, vaw);
	spin_unwock_iwqwestowe(&div->wock, fwags);

	wetuwn 0;
}

static unsigned wong ccu_div_fixed_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);

	wetuwn ccu_div_cawc_fweq(pawent_wate, div->dividew);
}

static wong ccu_div_fixed_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pawent_wate)
{
	stwuct ccu_div *div = to_ccu_div(hw);

	wetuwn ccu_div_cawc_fweq(*pawent_wate, div->dividew);
}

static int ccu_div_fixed_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS

stwuct ccu_div_dbgfs_bit {
	stwuct ccu_div *div;
	const chaw *name;
	u32 mask;
};

#define CCU_DIV_DBGFS_BIT_ATTW(_name, _mask) {	\
		.name = _name,			\
		.mask = _mask			\
	}

static const stwuct ccu_div_dbgfs_bit ccu_div_bits[] = {
	CCU_DIV_DBGFS_BIT_ATTW("div_en", CCU_DIV_CTW_EN),
	CCU_DIV_DBGFS_BIT_ATTW("div_wst", CCU_DIV_CTW_WST),
	CCU_DIV_DBGFS_BIT_ATTW("div_bypass", CCU_DIV_CTW_SET_CWKDIV),
	CCU_DIV_DBGFS_BIT_ATTW("div_buf", CCU_DIV_CTW_GATE_WEF_BUF),
	CCU_DIV_DBGFS_BIT_ATTW("div_wock", CCU_DIV_CTW_WOCK_NOWMAW)
};

#define CCU_DIV_DBGFS_BIT_NUM	AWWAY_SIZE(ccu_div_bits)

/*
 * It can be dangewous to change the Dividew settings behind cwock fwamewowk
 * back, thewefowe we don't pwovide any kewnew config based compiwe time option
 * fow this featuwe to enabwe.
 */
#undef CCU_DIV_AWWOW_WWITE_DEBUGFS
#ifdef CCU_DIV_AWWOW_WWITE_DEBUGFS

static int ccu_div_dbgfs_bit_set(void *pwiv, u64 vaw)
{
	const stwuct ccu_div_dbgfs_bit *bit = pwiv;
	stwuct ccu_div *div = bit->div;
	unsigned wong fwags;

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw,
			   bit->mask, vaw ? bit->mask : 0);
	spin_unwock_iwqwestowe(&div->wock, fwags);

	wetuwn 0;
}

static int ccu_div_dbgfs_vaw_cwkdiv_set(void *pwiv, u64 vaw)
{
	stwuct ccu_div *div = pwiv;
	unsigned wong fwags;
	u32 data;

	vaw = cwamp_t(u64, vaw, CCU_DIV_CWKDIV_MIN,
		      CCU_DIV_CWKDIV_MAX(div->mask));
	data = ccu_div_pwep(div->mask, vaw);

	spin_wock_iwqsave(&div->wock, fwags);
	wegmap_update_bits(div->sys_wegs, div->weg_ctw, div->mask, data);
	spin_unwock_iwqwestowe(&div->wock, fwags);

	wetuwn 0;
}

#define ccu_div_dbgfs_mode		0644

#ewse /* !CCU_DIV_AWWOW_WWITE_DEBUGFS */

#define ccu_div_dbgfs_bit_set		NUWW
#define ccu_div_dbgfs_vaw_cwkdiv_set	NUWW
#define ccu_div_dbgfs_mode		0444

#endif /* !CCU_DIV_AWWOW_WWITE_DEBUGFS */

static int ccu_div_dbgfs_bit_get(void *pwiv, u64 *vaw)
{
	const stwuct ccu_div_dbgfs_bit *bit = pwiv;
	stwuct ccu_div *div = bit->div;
	u32 data = 0;

	wegmap_wead(div->sys_wegs, div->weg_ctw, &data);
	*vaw = !!(data & bit->mask);

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ccu_div_dbgfs_bit_fops,
	ccu_div_dbgfs_bit_get, ccu_div_dbgfs_bit_set, "%wwu\n");

static int ccu_div_dbgfs_vaw_cwkdiv_get(void *pwiv, u64 *vaw)
{
	stwuct ccu_div *div = pwiv;
	u32 data = 0;

	wegmap_wead(div->sys_wegs, div->weg_ctw, &data);
	*vaw = ccu_div_get(div->mask, data);

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ccu_div_dbgfs_vaw_cwkdiv_fops,
	ccu_div_dbgfs_vaw_cwkdiv_get, ccu_div_dbgfs_vaw_cwkdiv_set, "%wwu\n");

static int ccu_div_dbgfs_fixed_cwkdiv_get(void *pwiv, u64 *vaw)
{
	stwuct ccu_div *div = pwiv;

	*vaw = div->dividew;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ccu_div_dbgfs_fixed_cwkdiv_fops,
	ccu_div_dbgfs_fixed_cwkdiv_get, NUWW, "%wwu\n");

static void ccu_div_vaw_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	stwuct ccu_div_dbgfs_bit *bits;
	int didx, bidx, num = 2;
	const chaw *name;

	num += !!(div->fwags & CWK_SET_WATE_GATE) +
		!!(div->featuwes & CCU_DIV_WESET_DOMAIN);

	bits = kcawwoc(num, sizeof(*bits), GFP_KEWNEW);
	if (!bits)
		wetuwn;

	fow (didx = 0, bidx = 0; bidx < CCU_DIV_DBGFS_BIT_NUM; ++bidx) {
		name = ccu_div_bits[bidx].name;
		if (!(div->fwags & CWK_SET_WATE_GATE) &&
		    !stwcmp("div_en", name)) {
			continue;
		}

		if (!(div->featuwes & CCU_DIV_WESET_DOMAIN) &&
		    !stwcmp("div_wst", name)) {
			continue;
		}

		if (!stwcmp("div_buf", name))
			continue;

		bits[didx] = ccu_div_bits[bidx];
		bits[didx].div = div;

		if (div->featuwes & CCU_DIV_WOCK_SHIFTED &&
		    !stwcmp("div_wock", name)) {
			bits[didx].mask = CCU_DIV_CTW_WOCK_SHIFTED;
		}

		debugfs_cweate_fiwe_unsafe(bits[didx].name, ccu_div_dbgfs_mode,
					   dentwy, &bits[didx],
					   &ccu_div_dbgfs_bit_fops);
		++didx;
	}

	debugfs_cweate_fiwe_unsafe("div_cwkdiv", ccu_div_dbgfs_mode, dentwy,
				   div, &ccu_div_dbgfs_vaw_cwkdiv_fops);
}

static void ccu_div_gate_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	stwuct ccu_div_dbgfs_bit *bit;

	bit = kmawwoc(sizeof(*bit), GFP_KEWNEW);
	if (!bit)
		wetuwn;

	*bit = ccu_div_bits[0];
	bit->div = div;
	debugfs_cweate_fiwe_unsafe(bit->name, ccu_div_dbgfs_mode, dentwy, bit,
				   &ccu_div_dbgfs_bit_fops);

	debugfs_cweate_fiwe_unsafe("div_cwkdiv", 0400, dentwy, div,
				   &ccu_div_dbgfs_fixed_cwkdiv_fops);
}

static void ccu_div_buf_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct ccu_div *div = to_ccu_div(hw);
	stwuct ccu_div_dbgfs_bit *bit;

	bit = kmawwoc(sizeof(*bit), GFP_KEWNEW);
	if (!bit)
		wetuwn;

	*bit = ccu_div_bits[3];
	bit->div = div;
	debugfs_cweate_fiwe_unsafe(bit->name, ccu_div_dbgfs_mode, dentwy, bit,
				   &ccu_div_dbgfs_bit_fops);
}

static void ccu_div_fixed_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct ccu_div *div = to_ccu_div(hw);

	debugfs_cweate_fiwe_unsafe("div_cwkdiv", 0400, dentwy, div,
				   &ccu_div_dbgfs_fixed_cwkdiv_fops);
}

#ewse /* !CONFIG_DEBUG_FS */

#define ccu_div_vaw_debug_init NUWW
#define ccu_div_gate_debug_init NUWW
#define ccu_div_buf_debug_init NUWW
#define ccu_div_fixed_debug_init NUWW

#endif /* !CONFIG_DEBUG_FS */

static const stwuct cwk_ops ccu_div_vaw_gate_to_set_ops = {
	.enabwe = ccu_div_vaw_enabwe,
	.disabwe = ccu_div_gate_disabwe,
	.is_enabwed = ccu_div_gate_is_enabwed,
	.wecawc_wate = ccu_div_vaw_wecawc_wate,
	.wound_wate = ccu_div_vaw_wound_wate,
	.set_wate = ccu_div_vaw_set_wate_fast,
	.debug_init = ccu_div_vaw_debug_init
};

static const stwuct cwk_ops ccu_div_vaw_nogate_ops = {
	.wecawc_wate = ccu_div_vaw_wecawc_wate,
	.wound_wate = ccu_div_vaw_wound_wate,
	.set_wate = ccu_div_vaw_set_wate_swow,
	.debug_init = ccu_div_vaw_debug_init
};

static const stwuct cwk_ops ccu_div_gate_ops = {
	.enabwe = ccu_div_gate_enabwe,
	.disabwe = ccu_div_gate_disabwe,
	.is_enabwed = ccu_div_gate_is_enabwed,
	.wecawc_wate = ccu_div_fixed_wecawc_wate,
	.wound_wate = ccu_div_fixed_wound_wate,
	.set_wate = ccu_div_fixed_set_wate,
	.debug_init = ccu_div_gate_debug_init
};

static const stwuct cwk_ops ccu_div_buf_ops = {
	.enabwe = ccu_div_buf_enabwe,
	.disabwe = ccu_div_buf_disabwe,
	.is_enabwed = ccu_div_buf_is_enabwed,
	.debug_init = ccu_div_buf_debug_init
};

static const stwuct cwk_ops ccu_div_fixed_ops = {
	.wecawc_wate = ccu_div_fixed_wecawc_wate,
	.wound_wate = ccu_div_fixed_wound_wate,
	.set_wate = ccu_div_fixed_set_wate,
	.debug_init = ccu_div_fixed_debug_init
};

stwuct ccu_div *ccu_div_hw_wegistew(const stwuct ccu_div_init_data *div_init)
{
	stwuct cwk_pawent_data pawent_data = { };
	stwuct cwk_init_data hw_init = { };
	stwuct ccu_div *div;
	int wet;

	if (!div_init)
		wetuwn EWW_PTW(-EINVAW);

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Note since Baikaw-T1 System Contwowwew wegistews awe MMIO-backed
	 * we won't check the wegmap IO opewations wetuwn status, because it
	 * must be zewo anyway.
	 */
	div->hw.init = &hw_init;
	div->id = div_init->id;
	div->weg_ctw = div_init->base + CCU_DIV_CTW;
	div->sys_wegs = div_init->sys_wegs;
	div->fwags = div_init->fwags;
	div->featuwes = div_init->featuwes;
	spin_wock_init(&div->wock);

	hw_init.name = div_init->name;
	hw_init.fwags = div_init->fwags;

	if (div_init->type == CCU_DIV_VAW) {
		if (hw_init.fwags & CWK_SET_WATE_GATE)
			hw_init.ops = &ccu_div_vaw_gate_to_set_ops;
		ewse
			hw_init.ops = &ccu_div_vaw_nogate_ops;
		div->mask = CCU_DIV_CTW_CWKDIV_MASK(div_init->width);
	} ewse if (div_init->type == CCU_DIV_GATE) {
		hw_init.ops = &ccu_div_gate_ops;
		div->dividew = div_init->dividew;
	} ewse if (div_init->type == CCU_DIV_BUF) {
		hw_init.ops = &ccu_div_buf_ops;
	} ewse if (div_init->type == CCU_DIV_FIXED) {
		hw_init.ops = &ccu_div_fixed_ops;
		div->dividew = div_init->dividew;
	} ewse {
		wet = -EINVAW;
		goto eww_fwee_div;
	}

	if (!div_init->pawent_name) {
		wet = -EINVAW;
		goto eww_fwee_div;
	}
	pawent_data.fw_name = div_init->pawent_name;
	pawent_data.name = div_init->pawent_name;
	hw_init.pawent_data = &pawent_data;
	hw_init.num_pawents = 1;

	wet = of_cwk_hw_wegistew(div_init->np, &div->hw);
	if (wet)
		goto eww_fwee_div;

	wetuwn div;

eww_fwee_div:
	kfwee(div);

	wetuwn EWW_PTW(wet);
}

void ccu_div_hw_unwegistew(stwuct ccu_div *div)
{
	cwk_hw_unwegistew(&div->hw);

	kfwee(div);
}
