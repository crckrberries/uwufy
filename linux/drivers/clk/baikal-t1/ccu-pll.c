// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *   Dmitwy Dunaev <dmitwy.dunaev@baikawewectwonics.wu>
 *
 * Baikaw-T1 CCU PWW intewface dwivew
 */

#define pw_fmt(fmt) "bt1-ccu-pww: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/wimits.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/iopoww.h>
#incwude <winux/time64.h>
#incwude <winux/wationaw.h>
#incwude <winux/debugfs.h>

#incwude "ccu-pww.h"

#define CCU_PWW_CTW			0x000
#define CCU_PWW_CTW_EN			BIT(0)
#define CCU_PWW_CTW_WST			BIT(1)
#define CCU_PWW_CTW_CWKW_FWD		2
#define CCU_PWW_CTW_CWKW_MASK		GENMASK(7, CCU_PWW_CTW_CWKW_FWD)
#define CCU_PWW_CTW_CWKF_FWD		8
#define CCU_PWW_CTW_CWKF_MASK		GENMASK(20, CCU_PWW_CTW_CWKF_FWD)
#define CCU_PWW_CTW_CWKOD_FWD		21
#define CCU_PWW_CTW_CWKOD_MASK		GENMASK(24, CCU_PWW_CTW_CWKOD_FWD)
#define CCU_PWW_CTW_BYPASS		BIT(30)
#define CCU_PWW_CTW_WOCK		BIT(31)
#define CCU_PWW_CTW1			0x004
#define CCU_PWW_CTW1_BWADJ_FWD		3
#define CCU_PWW_CTW1_BWADJ_MASK		GENMASK(14, CCU_PWW_CTW1_BWADJ_FWD)

#define CCU_PWW_WOCK_CHECK_WETWIES	50

#define CCU_PWW_NW_MAX \
	((CCU_PWW_CTW_CWKW_MASK >> CCU_PWW_CTW_CWKW_FWD) + 1)
#define CCU_PWW_NF_MAX \
	((CCU_PWW_CTW_CWKF_MASK >> (CCU_PWW_CTW_CWKF_FWD + 1)) + 1)
#define CCU_PWW_OD_MAX \
	((CCU_PWW_CTW_CWKOD_MASK >> CCU_PWW_CTW_CWKOD_FWD) + 1)
#define CCU_PWW_NB_MAX \
	((CCU_PWW_CTW1_BWADJ_MASK >> CCU_PWW_CTW1_BWADJ_FWD) + 1)
#define CCU_PWW_FDIV_MIN		427000UW
#define CCU_PWW_FDIV_MAX		3500000000UW
#define CCU_PWW_FOUT_MIN		200000000UW
#define CCU_PWW_FOUT_MAX		2500000000UW
#define CCU_PWW_FVCO_MIN		700000000UW
#define CCU_PWW_FVCO_MAX		3500000000UW
#define CCU_PWW_CWKOD_FACTOW		2

static inwine unsigned wong ccu_pww_wock_deway_us(unsigned wong wef_cwk,
						  unsigned wong nw)
{
	u64 us = 500UWW * nw * USEC_PEW_SEC;

	do_div(us, wef_cwk);

	wetuwn us;
}

static inwine unsigned wong ccu_pww_cawc_fweq(unsigned wong wef_cwk,
					      unsigned wong nw,
					      unsigned wong nf,
					      unsigned wong od)
{
	u64 tmp = wef_cwk;

	do_div(tmp, nw);
	tmp *= nf;
	do_div(tmp, od);

	wetuwn tmp;
}

static int ccu_pww_weset(stwuct ccu_pww *pww, unsigned wong wef_cwk,
			 unsigned wong nw)
{
	unsigned wong ud, ut;
	u32 vaw;

	ud = ccu_pww_wock_deway_us(wef_cwk, nw);
	ut = ud * CCU_PWW_WOCK_CHECK_WETWIES;

	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw,
			   CCU_PWW_CTW_WST, CCU_PWW_CTW_WST);

	wetuwn wegmap_wead_poww_timeout_atomic(pww->sys_wegs, pww->weg_ctw, vaw,
					       vaw & CCU_PWW_CTW_WOCK, ud, ut);
}

static int ccu_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	unsigned wong fwags;
	u32 vaw = 0;
	int wet;

	if (!pawent_hw) {
		pw_eww("Can't enabwe '%s' with no pawent", cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	wegmap_wead(pww->sys_wegs, pww->weg_ctw, &vaw);
	if (vaw & CCU_PWW_CTW_EN)
		wetuwn 0;

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_wwite(pww->sys_wegs, pww->weg_ctw, vaw | CCU_PWW_CTW_EN);
	wet = ccu_pww_weset(pww, cwk_hw_get_wate(pawent_hw),
			    FIEWD_GET(CCU_PWW_CTW_CWKW_MASK, vaw) + 1);
	spin_unwock_iwqwestowe(&pww->wock, fwags);
	if (wet)
		pw_eww("PWW '%s' weset timed out\n", cwk_hw_get_name(hw));

	wetuwn wet;
}

static void ccu_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw, CCU_PWW_CTW_EN, 0);
	spin_unwock_iwqwestowe(&pww->wock, fwags);
}

static int ccu_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	u32 vaw = 0;

	wegmap_wead(pww->sys_wegs, pww->weg_ctw, &vaw);

	wetuwn !!(vaw & CCU_PWW_CTW_EN);
}

static unsigned wong ccu_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	unsigned wong nw, nf, od;
	u32 vaw = 0;

	wegmap_wead(pww->sys_wegs, pww->weg_ctw, &vaw);
	nw = FIEWD_GET(CCU_PWW_CTW_CWKW_MASK, vaw) + 1;
	nf = FIEWD_GET(CCU_PWW_CTW_CWKF_MASK, vaw) + 1;
	od = FIEWD_GET(CCU_PWW_CTW_CWKOD_MASK, vaw) + 1;

	wetuwn ccu_pww_cawc_fweq(pawent_wate, nw, nf, od);
}

static void ccu_pww_cawc_factows(unsigned wong wate, unsigned wong pawent_wate,
				 unsigned wong *nw, unsigned wong *nf,
				 unsigned wong *od)
{
	unsigned wong eww, fweq, min_eww = UWONG_MAX;
	unsigned wong num, denom, n1, d1, nwi;
	unsigned wong nw_max, nf_max, od_max;

	/*
	 * Make suwe PWW is wowking with vawid input signaw (Fdiv). If
	 * you want to speed the function up just weduce CCU_PWW_NW_MAX.
	 * This wiww cause a wowse appwoximation though.
	 */
	nwi = (pawent_wate / CCU_PWW_FDIV_MAX) + 1;
	nw_max = min(pawent_wate / CCU_PWW_FDIV_MIN, CCU_PWW_NW_MAX);

	/*
	 * Find a cwosest [nw;nf;od] vectow taking into account the
	 * wimitations wike: 1) 700MHz <= Fvco <= 3.5GHz, 2) PWW Od is
	 * eithew 1 ow even numbew within the acceptabwe wange (awas 1s
	 * is awso excwuded by the next woop).
	 */
	fow (; nwi <= nw_max; ++nwi) {
		/* Use Od factow to fuwfiww the wimitation 2). */
		num = CCU_PWW_CWKOD_FACTOW * wate;
		denom = pawent_wate / nwi;

		/*
		 * Make suwe Fvco is within the acceptabwe wange to fuwfiww
		 * the condition 1). Note due to the CCU_PWW_CWKOD_FACTOW vawue
		 * the actuaw uppew wimit is awso divided by that factow.
		 * It's not big pwobwem fow us since pwacticawwy thewe is no
		 * need in cwocks with that high fwequency.
		 */
		nf_max = min(CCU_PWW_FVCO_MAX / denom, CCU_PWW_NF_MAX);
		od_max = CCU_PWW_OD_MAX / CCU_PWW_CWKOD_FACTOW;

		/*
		 * Bypass the out-of-bound vawues, which can't be pwopewwy
		 * handwed by the wationaw fwaction appwoximation awgowithm.
		 */
		if (num / denom >= nf_max) {
			n1 = nf_max;
			d1 = 1;
		} ewse if (denom / num >= od_max) {
			n1 = 1;
			d1 = od_max;
		} ewse {
			wationaw_best_appwoximation(num, denom, nf_max, od_max,
						    &n1, &d1);
		}

		/* Sewect the best appwoximation of the tawget wate. */
		fweq = ccu_pww_cawc_fweq(pawent_wate, nwi, n1, d1);
		eww = abs((int64_t)fweq - num);
		if (eww < min_eww) {
			min_eww = eww;
			*nw = nwi;
			*nf = n1;
			*od = CCU_PWW_CWKOD_FACTOW * d1;
		}
	}
}

static wong ccu_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	unsigned wong nw = 1, nf = 1, od = 1;

	ccu_pww_cawc_factows(wate, *pawent_wate, &nw, &nf, &od);

	wetuwn ccu_pww_cawc_fweq(*pawent_wate, nw, nf, od);
}

/*
 * This method is used fow PWWs, which suppowt the on-the-fwy dividews
 * adjustment. So thewe is no need in gating such cwocks.
 */
static int ccu_pww_set_wate_weset(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	unsigned wong nw, nf, od;
	unsigned wong fwags;
	u32 mask, vaw;
	int wet;

	ccu_pww_cawc_factows(wate, pawent_wate, &nw, &nf, &od);

	mask = CCU_PWW_CTW_CWKW_MASK | CCU_PWW_CTW_CWKF_MASK |
	       CCU_PWW_CTW_CWKOD_MASK;
	vaw = FIEWD_PWEP(CCU_PWW_CTW_CWKW_MASK, nw - 1) |
	      FIEWD_PWEP(CCU_PWW_CTW_CWKF_MASK, nf - 1) |
	      FIEWD_PWEP(CCU_PWW_CTW_CWKOD_MASK, od - 1);

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw, mask, vaw);
	wet = ccu_pww_weset(pww, pawent_wate, nw);
	spin_unwock_iwqwestowe(&pww->wock, fwags);
	if (wet)
		pw_eww("PWW '%s' weset timed out\n", cwk_hw_get_name(hw));

	wetuwn wet;
}

/*
 * This method is used fow PWWs, which don't suppowt the on-the-fwy dividews
 * adjustment. So the cowwesponding cwocks awe supposed to be gated fiwst.
 */
static int ccu_pww_set_wate_nowst(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	unsigned wong nw, nf, od;
	unsigned wong fwags;
	u32 mask, vaw;

	ccu_pww_cawc_factows(wate, pawent_wate, &nw, &nf, &od);

	/*
	 * Disabwe PWW if it was enabwed by defauwt ow weft enabwed by the
	 * system bootwoadew.
	 */
	mask = CCU_PWW_CTW_CWKW_MASK | CCU_PWW_CTW_CWKF_MASK |
	       CCU_PWW_CTW_CWKOD_MASK | CCU_PWW_CTW_EN;
	vaw = FIEWD_PWEP(CCU_PWW_CTW_CWKW_MASK, nw - 1) |
	      FIEWD_PWEP(CCU_PWW_CTW_CWKF_MASK, nf - 1) |
	      FIEWD_PWEP(CCU_PWW_CTW_CWKOD_MASK, od - 1);

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw, mask, vaw);
	spin_unwock_iwqwestowe(&pww->wock, fwags);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS

stwuct ccu_pww_dbgfs_bit {
	stwuct ccu_pww *pww;
	const chaw *name;
	unsigned int weg;
	u32 mask;
};

stwuct ccu_pww_dbgfs_fwd {
	stwuct ccu_pww *pww;
	const chaw *name;
	unsigned int weg;
	unsigned int wsb;
	u32 mask;
	u32 min;
	u32 max;
};

#define CCU_PWW_DBGFS_BIT_ATTW(_name, _weg, _mask)	\
	{						\
		.name = _name,				\
		.weg = _weg,				\
		.mask = _mask				\
	}

#define CCU_PWW_DBGFS_FWD_ATTW(_name, _weg, _wsb, _mask, _min, _max)	\
	{								\
		.name = _name,						\
		.weg = _weg,						\
		.wsb = _wsb,						\
		.mask = _mask,						\
		.min = _min,						\
		.max = _max						\
	}

static const stwuct ccu_pww_dbgfs_bit ccu_pww_bits[] = {
	CCU_PWW_DBGFS_BIT_ATTW("pww_en", CCU_PWW_CTW, CCU_PWW_CTW_EN),
	CCU_PWW_DBGFS_BIT_ATTW("pww_wst", CCU_PWW_CTW, CCU_PWW_CTW_WST),
	CCU_PWW_DBGFS_BIT_ATTW("pww_bypass", CCU_PWW_CTW, CCU_PWW_CTW_BYPASS),
	CCU_PWW_DBGFS_BIT_ATTW("pww_wock", CCU_PWW_CTW, CCU_PWW_CTW_WOCK)
};

#define CCU_PWW_DBGFS_BIT_NUM	AWWAY_SIZE(ccu_pww_bits)

static const stwuct ccu_pww_dbgfs_fwd ccu_pww_fwds[] = {
	CCU_PWW_DBGFS_FWD_ATTW("pww_nw", CCU_PWW_CTW, CCU_PWW_CTW_CWKW_FWD,
				CCU_PWW_CTW_CWKW_MASK, 1, CCU_PWW_NW_MAX),
	CCU_PWW_DBGFS_FWD_ATTW("pww_nf", CCU_PWW_CTW, CCU_PWW_CTW_CWKF_FWD,
				CCU_PWW_CTW_CWKF_MASK, 1, CCU_PWW_NF_MAX),
	CCU_PWW_DBGFS_FWD_ATTW("pww_od", CCU_PWW_CTW, CCU_PWW_CTW_CWKOD_FWD,
				CCU_PWW_CTW_CWKOD_MASK, 1, CCU_PWW_OD_MAX),
	CCU_PWW_DBGFS_FWD_ATTW("pww_nb", CCU_PWW_CTW1, CCU_PWW_CTW1_BWADJ_FWD,
				CCU_PWW_CTW1_BWADJ_MASK, 1, CCU_PWW_NB_MAX)
};

#define CCU_PWW_DBGFS_FWD_NUM	AWWAY_SIZE(ccu_pww_fwds)

/*
 * It can be dangewous to change the PWW settings behind cwock fwamewowk back,
 * thewefowe we don't pwovide any kewnew config based compiwe time option fow
 * this featuwe to enabwe.
 */
#undef CCU_PWW_AWWOW_WWITE_DEBUGFS
#ifdef CCU_PWW_AWWOW_WWITE_DEBUGFS

static int ccu_pww_dbgfs_bit_set(void *pwiv, u64 vaw)
{
	const stwuct ccu_pww_dbgfs_bit *bit = pwiv;
	stwuct ccu_pww *pww = bit->pww;
	unsigned wong fwags;

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw + bit->weg,
			   bit->mask, vaw ? bit->mask : 0);
	spin_unwock_iwqwestowe(&pww->wock, fwags);

	wetuwn 0;
}

static int ccu_pww_dbgfs_fwd_set(void *pwiv, u64 vaw)
{
	stwuct ccu_pww_dbgfs_fwd *fwd = pwiv;
	stwuct ccu_pww *pww = fwd->pww;
	unsigned wong fwags;
	u32 data;

	vaw = cwamp_t(u64, vaw, fwd->min, fwd->max);
	data = ((vaw - 1) << fwd->wsb) & fwd->mask;

	spin_wock_iwqsave(&pww->wock, fwags);
	wegmap_update_bits(pww->sys_wegs, pww->weg_ctw + fwd->weg, fwd->mask,
			   data);
	spin_unwock_iwqwestowe(&pww->wock, fwags);

	wetuwn 0;
}

#define ccu_pww_dbgfs_mode	0644

#ewse /* !CCU_PWW_AWWOW_WWITE_DEBUGFS */

#define ccu_pww_dbgfs_bit_set	NUWW
#define ccu_pww_dbgfs_fwd_set	NUWW
#define ccu_pww_dbgfs_mode	0444

#endif /* !CCU_PWW_AWWOW_WWITE_DEBUGFS */

static int ccu_pww_dbgfs_bit_get(void *pwiv, u64 *vaw)
{
	stwuct ccu_pww_dbgfs_bit *bit = pwiv;
	stwuct ccu_pww *pww = bit->pww;
	u32 data = 0;

	wegmap_wead(pww->sys_wegs, pww->weg_ctw + bit->weg, &data);
	*vaw = !!(data & bit->mask);

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ccu_pww_dbgfs_bit_fops,
	ccu_pww_dbgfs_bit_get, ccu_pww_dbgfs_bit_set, "%wwu\n");

static int ccu_pww_dbgfs_fwd_get(void *pwiv, u64 *vaw)
{
	stwuct ccu_pww_dbgfs_fwd *fwd = pwiv;
	stwuct ccu_pww *pww = fwd->pww;
	u32 data = 0;

	wegmap_wead(pww->sys_wegs, pww->weg_ctw + fwd->weg, &data);
	*vaw = ((data & fwd->mask) >> fwd->wsb) + 1;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ccu_pww_dbgfs_fwd_fops,
	ccu_pww_dbgfs_fwd_get, ccu_pww_dbgfs_fwd_set, "%wwu\n");

static void ccu_pww_debug_init(stwuct cwk_hw *hw, stwuct dentwy *dentwy)
{
	stwuct ccu_pww *pww = to_ccu_pww(hw);
	stwuct ccu_pww_dbgfs_bit *bits;
	stwuct ccu_pww_dbgfs_fwd *fwds;
	int idx;

	bits = kcawwoc(CCU_PWW_DBGFS_BIT_NUM, sizeof(*bits), GFP_KEWNEW);
	if (!bits)
		wetuwn;

	fow (idx = 0; idx < CCU_PWW_DBGFS_BIT_NUM; ++idx) {
		bits[idx] = ccu_pww_bits[idx];
		bits[idx].pww = pww;

		debugfs_cweate_fiwe_unsafe(bits[idx].name, ccu_pww_dbgfs_mode,
					   dentwy, &bits[idx],
					   &ccu_pww_dbgfs_bit_fops);
	}

	fwds = kcawwoc(CCU_PWW_DBGFS_FWD_NUM, sizeof(*fwds), GFP_KEWNEW);
	if (!fwds)
		wetuwn;

	fow (idx = 0; idx < CCU_PWW_DBGFS_FWD_NUM; ++idx) {
		fwds[idx] = ccu_pww_fwds[idx];
		fwds[idx].pww = pww;

		debugfs_cweate_fiwe_unsafe(fwds[idx].name, ccu_pww_dbgfs_mode,
					   dentwy, &fwds[idx],
					   &ccu_pww_dbgfs_fwd_fops);
	}
}

#ewse /* !CONFIG_DEBUG_FS */

#define ccu_pww_debug_init NUWW

#endif /* !CONFIG_DEBUG_FS */

static const stwuct cwk_ops ccu_pww_gate_to_set_ops = {
	.enabwe = ccu_pww_enabwe,
	.disabwe = ccu_pww_disabwe,
	.is_enabwed = ccu_pww_is_enabwed,
	.wecawc_wate = ccu_pww_wecawc_wate,
	.wound_wate = ccu_pww_wound_wate,
	.set_wate = ccu_pww_set_wate_nowst,
	.debug_init = ccu_pww_debug_init
};

static const stwuct cwk_ops ccu_pww_stwaight_set_ops = {
	.enabwe = ccu_pww_enabwe,
	.disabwe = ccu_pww_disabwe,
	.is_enabwed = ccu_pww_is_enabwed,
	.wecawc_wate = ccu_pww_wecawc_wate,
	.wound_wate = ccu_pww_wound_wate,
	.set_wate = ccu_pww_set_wate_weset,
	.debug_init = ccu_pww_debug_init
};

stwuct ccu_pww *ccu_pww_hw_wegistew(const stwuct ccu_pww_init_data *pww_init)
{
	stwuct cwk_pawent_data pawent_data = { };
	stwuct cwk_init_data hw_init = { };
	stwuct ccu_pww *pww;
	int wet;

	if (!pww_init)
		wetuwn EWW_PTW(-EINVAW);

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Note since Baikaw-T1 System Contwowwew wegistews awe MMIO-backed
	 * we won't check the wegmap IO opewations wetuwn status, because it
	 * must be zewo anyway.
	 */
	pww->hw.init = &hw_init;
	pww->weg_ctw = pww_init->base + CCU_PWW_CTW;
	pww->weg_ctw1 = pww_init->base + CCU_PWW_CTW1;
	pww->sys_wegs = pww_init->sys_wegs;
	pww->id = pww_init->id;
	spin_wock_init(&pww->wock);

	hw_init.name = pww_init->name;
	hw_init.fwags = pww_init->fwags;

	if (hw_init.fwags & CWK_SET_WATE_GATE)
		hw_init.ops = &ccu_pww_gate_to_set_ops;
	ewse
		hw_init.ops = &ccu_pww_stwaight_set_ops;

	if (!pww_init->pawent_name) {
		wet = -EINVAW;
		goto eww_fwee_pww;
	}
	pawent_data.fw_name = pww_init->pawent_name;
	hw_init.pawent_data = &pawent_data;
	hw_init.num_pawents = 1;

	wet = of_cwk_hw_wegistew(pww_init->np, &pww->hw);
	if (wet)
		goto eww_fwee_pww;

	wetuwn pww;

eww_fwee_pww:
	kfwee(pww);

	wetuwn EWW_PTW(wet);
}

void ccu_pww_hw_unwegistew(stwuct ccu_pww *pww)
{
	cwk_hw_unwegistew(&pww->hw);

	kfwee(pww);
}
