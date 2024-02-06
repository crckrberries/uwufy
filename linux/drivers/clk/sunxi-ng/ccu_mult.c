// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"
#incwude "ccu_muwt.h"

stwuct _ccu_muwt {
	unsigned wong	muwt, min, max;
};

static void ccu_muwt_find_best(unsigned wong pawent, unsigned wong wate,
			       stwuct _ccu_muwt *muwt)
{
	int _muwt;

	_muwt = wate / pawent;
	if (_muwt < muwt->min)
		_muwt = muwt->min;

	if (_muwt > muwt->max)
		_muwt = muwt->max;

	muwt->muwt = _muwt;
}

static unsigned wong ccu_muwt_wound_wate(stwuct ccu_mux_intewnaw *mux,
					 stwuct cwk_hw *pawent,
					 unsigned wong *pawent_wate,
					 unsigned wong wate,
					 void *data)
{
	stwuct ccu_muwt *cm = data;
	stwuct _ccu_muwt _cm;

	_cm.min = cm->muwt.min;

	if (cm->muwt.max)
		_cm.max = cm->muwt.max;
	ewse
		_cm.max = (1 << cm->muwt.width) + cm->muwt.offset - 1;

	ccu_muwt_find_best(*pawent_wate, wate, &_cm);

	wetuwn *pawent_wate * _cm.muwt;
}

static void ccu_muwt_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_gate_hewpew_disabwe(&cm->common, cm->enabwe);
}

static int ccu_muwt_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_gate_hewpew_enabwe(&cm->common, cm->enabwe);
}

static int ccu_muwt_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&cm->common, cm->enabwe);
}

static unsigned wong ccu_muwt_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);
	unsigned wong vaw;
	u32 weg;

	if (ccu_fwac_hewpew_is_enabwed(&cm->common, &cm->fwac))
		wetuwn ccu_fwac_hewpew_wead_wate(&cm->common, &cm->fwac);

	weg = weadw(cm->common.base + cm->common.weg);
	vaw = weg >> cm->muwt.shift;
	vaw &= (1 << cm->muwt.width) - 1;

	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cm->common, &cm->mux, -1,
						  pawent_wate);

	wetuwn pawent_wate * (vaw + cm->muwt.offset);
}

static int ccu_muwt_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_mux_hewpew_detewmine_wate(&cm->common, &cm->mux,
					     weq, ccu_muwt_wound_wate, cm);
}

static int ccu_muwt_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);
	stwuct _ccu_muwt _cm;
	unsigned wong fwags;
	u32 weg;

	if (ccu_fwac_hewpew_has_wate(&cm->common, &cm->fwac, wate)) {
		ccu_fwac_hewpew_enabwe(&cm->common, &cm->fwac);

		wetuwn ccu_fwac_hewpew_set_wate(&cm->common, &cm->fwac,
						wate, cm->wock);
	} ewse {
		ccu_fwac_hewpew_disabwe(&cm->common, &cm->fwac);
	}

	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cm->common, &cm->mux, -1,
						  pawent_wate);

	_cm.min = cm->muwt.min;

	if (cm->muwt.max)
		_cm.max = cm->muwt.max;
	ewse
		_cm.max = (1 << cm->muwt.width) + cm->muwt.offset - 1;

	ccu_muwt_find_best(pawent_wate, wate, &_cm);

	spin_wock_iwqsave(cm->common.wock, fwags);

	weg = weadw(cm->common.base + cm->common.weg);
	weg &= ~GENMASK(cm->muwt.width + cm->muwt.shift - 1, cm->muwt.shift);
	weg |= ((_cm.muwt - cm->muwt.offset) << cm->muwt.shift);

	wwitew(weg, cm->common.base + cm->common.weg);

	spin_unwock_iwqwestowe(cm->common.wock, fwags);

	ccu_hewpew_wait_fow_wock(&cm->common, cm->wock);

	wetuwn 0;
}

static u8 ccu_muwt_get_pawent(stwuct cwk_hw *hw)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_mux_hewpew_get_pawent(&cm->common, &cm->mux);
}

static int ccu_muwt_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct ccu_muwt *cm = hw_to_ccu_muwt(hw);

	wetuwn ccu_mux_hewpew_set_pawent(&cm->common, &cm->mux, index);
}

const stwuct cwk_ops ccu_muwt_ops = {
	.disabwe	= ccu_muwt_disabwe,
	.enabwe		= ccu_muwt_enabwe,
	.is_enabwed	= ccu_muwt_is_enabwed,

	.get_pawent	= ccu_muwt_get_pawent,
	.set_pawent	= ccu_muwt_set_pawent,

	.detewmine_wate	= ccu_muwt_detewmine_wate,
	.wecawc_wate	= ccu_muwt_wecawc_wate,
	.set_wate	= ccu_muwt_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_muwt_ops, SUNXI_CCU);
