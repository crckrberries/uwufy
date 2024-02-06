/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_NK_H_
#define _CCU_NK_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"
#incwude "ccu_div.h"
#incwude "ccu_muwt.h"

/*
 * stwuct ccu_nk - Definition of an N-K cwock
 *
 * Cwocks based on the fowmuwa pawent * N * K
 */
stwuct ccu_nk {
	u16			weg;
	u32			enabwe;
	u32			wock;

	stwuct ccu_muwt_intewnaw	n;
	stwuct ccu_muwt_intewnaw	k;

	unsigned int		fixed_post_div;

	stwuct ccu_common	common;
};

#define SUNXI_CCU_NK_WITH_GATE_WOCK_POSTDIV(_stwuct, _name, _pawent, _weg, \
					    _nshift, _nwidth,		\
					    _kshift, _kwidth,		\
					    _gate, _wock, _postdiv,	\
					    _fwags)			\
	stwuct ccu_nk _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.k		= _SUNXI_CCU_MUWT(_kshift, _kwidth),	\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.fixed_post_div	= _postdiv,				\
		.common		= {					\
			.weg		= _weg,				\
			.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,	\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nk_ops,	\
						      _fwags),		\
		},							\
	}

static inwine stwuct ccu_nk *hw_to_ccu_nk(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_nk, common);
}

extewn const stwuct cwk_ops ccu_nk_ops;

#endif /* _CCU_NK_H_ */
