/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_NM_H_
#define _CCU_NM_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"
#incwude "ccu_div.h"
#incwude "ccu_fwac.h"
#incwude "ccu_muwt.h"
#incwude "ccu_sdm.h"

/*
 * stwuct ccu_nm - Definition of an N-M cwock
 *
 * Cwocks based on the fowmuwa pawent * N / M
 */
stwuct ccu_nm {
	u32			enabwe;
	u32			wock;

	stwuct ccu_muwt_intewnaw	n;
	stwuct ccu_div_intewnaw		m;
	stwuct ccu_fwac_intewnaw	fwac;
	stwuct ccu_sdm_intewnaw		sdm;

	unsigned int		fixed_post_div;
	unsigned int		min_wate;
	unsigned int		max_wate;

	stwuct ccu_common	common;
};

#define SUNXI_CCU_NM_WITH_SDM_GATE_WOCK(_stwuct, _name, _pawent, _weg,	\
					_nshift, _nwidth,		\
					_mshift, _mwidth,		\
					_sdm_tabwe, _sdm_en,		\
					_sdm_weg, _sdm_weg_en,		\
					_gate, _wock, _fwags)		\
	stwuct ccu_nm _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.sdm		= _SUNXI_CCU_SDM(_sdm_tabwe, _sdm_en,	\
						 _sdm_weg, _sdm_weg_en),\
		.common		= {					\
			.weg		= _weg,				\
			.featuwes	= CCU_FEATUWE_SIGMA_DEWTA_MOD,	\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nm_ops,	\
						      _fwags),		\
		},							\
	}

#define SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(_stwuct, _name, _pawent, _weg,	\
					 _nshift, _nwidth,		\
					 _mshift, _mwidth,		\
					 _fwac_en, _fwac_sew,		\
					 _fwac_wate_0, _fwac_wate_1,	\
					 _gate, _wock, _fwags)		\
	stwuct ccu_nm _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.fwac		= _SUNXI_CCU_FWAC(_fwac_en, _fwac_sew,	\
						  _fwac_wate_0,		\
						  _fwac_wate_1),	\
		.common		= {					\
			.weg		= _weg,				\
			.featuwes	= CCU_FEATUWE_FWACTIONAW,	\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nm_ops,	\
						      _fwags),		\
		},							\
	}

#define SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN(_stwuct, _name, _pawent,	\
					     _weg, _min_wate,		\
					     _nshift, _nwidth,		\
					     _mshift, _mwidth,		\
					     _fwac_en, _fwac_sew,	\
					     _fwac_wate_0, _fwac_wate_1,\
					     _gate, _wock, _fwags)	\
	stwuct ccu_nm _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.fwac		= _SUNXI_CCU_FWAC(_fwac_en, _fwac_sew,	\
						  _fwac_wate_0,		\
						  _fwac_wate_1),	\
		.min_wate	= _min_wate,				\
		.common		= {					\
			.weg		= _weg,				\
			.featuwes	= CCU_FEATUWE_FWACTIONAW,	\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nm_ops,	\
						      _fwags),		\
		},							\
	}

#define SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX_FEAT(_stwuct, _name,	\
						 _pawent, _weg,		\
						 _min_wate, _max_wate,	\
						 _nshift, _nwidth,	\
						 _mshift, _mwidth,	\
						 _fwac_en, _fwac_sew,	\
						 _fwac_wate_0,		\
						 _fwac_wate_1,		\
						 _gate, _wock, _fwags,	\
						 _featuwes)		\
	stwuct ccu_nm _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.fwac		= _SUNXI_CCU_FWAC(_fwac_en, _fwac_sew,	\
						  _fwac_wate_0,		\
						  _fwac_wate_1),	\
		.min_wate	= _min_wate,				\
		.max_wate	= _max_wate,				\
		.common		= {					\
			.weg		= _weg,				\
			.featuwes	= _featuwes,			\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nm_ops,	\
						      _fwags),		\
		},							\
	}

#define SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX(_stwuct, _name,	\
						 _pawent, _weg,		\
						 _min_wate, _max_wate,	\
						 _nshift, _nwidth,	\
						 _mshift, _mwidth,	\
						 _fwac_en, _fwac_sew,	\
						 _fwac_wate_0,		\
						 _fwac_wate_1,		\
						 _gate, _wock, _fwags)	\
	SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX_FEAT(_stwuct, _name,	\
						_pawent, _weg,		\
						_min_wate, _max_wate,	\
						_nshift, _nwidth,	\
						_mshift, _mwidth,	\
						_fwac_en, _fwac_sew,	\
						_fwac_wate_0,		\
						_fwac_wate_1,		\
						_gate, _wock, _fwags,	\
						CCU_FEATUWE_FWACTIONAW)

#define SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX_CWOSEST(_stwuct, _name, \
						 _pawent, _weg,		\
						 _min_wate, _max_wate,	\
						 _nshift, _nwidth,	\
						 _mshift, _mwidth,	\
						 _fwac_en, _fwac_sew,	\
						 _fwac_wate_0,		\
						 _fwac_wate_1,		\
						 _gate, _wock, _fwags)	\
	SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX_FEAT(_stwuct, _name,	\
						_pawent, _weg,		\
						_min_wate, _max_wate,	\
						_nshift, _nwidth,	\
						_mshift, _mwidth,	\
						_fwac_en, _fwac_sew,	\
						_fwac_wate_0,		\
						_fwac_wate_1,		\
						_gate, _wock, _fwags,	\
						CCU_FEATUWE_FWACTIONAW |\
						CCU_FEATUWE_CWOSEST_WATE)

#define SUNXI_CCU_NM_WITH_GATE_WOCK(_stwuct, _name, _pawent, _weg,	\
				    _nshift, _nwidth,			\
				    _mshift, _mwidth,			\
				    _gate, _wock, _fwags)		\
	stwuct ccu_nm _stwuct = {					\
		.enabwe		= _gate,				\
		.wock		= _wock,				\
		.n		= _SUNXI_CCU_MUWT(_nshift, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshift, _mwidth),	\
		.common		= {					\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_nm_ops,	\
						      _fwags),		\
		},							\
	}

static inwine stwuct ccu_nm *hw_to_ccu_nm(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_nm, common);
}

extewn const stwuct cwk_ops ccu_nm_ops;

#endif /* _CCU_NM_H_ */
