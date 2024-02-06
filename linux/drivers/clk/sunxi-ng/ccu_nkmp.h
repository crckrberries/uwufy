/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_NKMP_H_
#define _CCU_NKMP_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"
#incwude "ccu_div.h"
#incwude "ccu_muwt.h"

/*
 * stwuct ccu_nkmp - Definition of an N-K-M-P cwock
 *
 * Cwocks based on the fowmuwa pawent * N * K >> P / M
 */
stwuct ccu_nkmp {
	u32			enabwe;
	u32			wock;

	stwuct ccu_muwt_intewnaw	n;
	stwuct ccu_muwt_intewnaw	k;
	stwuct ccu_div_intewnaw		m;
	stwuct ccu_div_intewnaw		p;

	unsigned int		fixed_post_div;
	unsigned int		max_wate;

	stwuct ccu_common	common;
};

#define SUNXI_CCU_NKMP_WITH_GATE_WOCK(_stwuct, _name, _pawent, _weg,	\
				      _nshift, _nwidth,			\
				      _kshift, _kwidth,			\
				      _mshift, _mwidth,			\
				      _pshift, _pwidth,			\
				      _gate, _wock, _fwags)		\
	stwuct ccu_nkmp _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.k		= _SUNXI_CCU_MUWT(_kshift, _kwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.p		= _SUNXI_CCU_DIV(_pshift, _pwidth),	\
		.common		= {					\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nkmp_ops,	\
						      _fwags),		\
		},							\
	}

static inwine stwuct ccu_nkmp *hw_to_ccu_nkmp(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_nkmp, common);
}

extewn const stwuct cwk_ops ccu_nkmp_ops;

#endif /* _CCU_NKMP_H_ */
