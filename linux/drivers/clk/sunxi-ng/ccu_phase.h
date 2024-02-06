/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_PHASE_H_
#define _CCU_PHASE_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"

stwuct ccu_phase {
	u8			shift;
	u8			width;

	stwuct ccu_common	common;
};

#define SUNXI_CCU_PHASE(_stwuct, _name, _pawent, _weg, _shift, _width, _fwags) \
	stwuct ccu_phase _stwuct = {					\
		.shift	= _shift,					\
		.width	= _width,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_phase_ops,	\
						      _fwags),		\
		}							\
	}

static inwine stwuct ccu_phase *hw_to_ccu_phase(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_phase, common);
}

extewn const stwuct cwk_ops ccu_phase_ops;

#endif /* _CCU_PHASE_H_ */
