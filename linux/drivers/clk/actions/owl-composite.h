/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW composite cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_COMPOSITE_H_
#define _OWW_COMPOSITE_H_

#incwude "oww-common.h"
#incwude "oww-mux.h"
#incwude "oww-gate.h"
#incwude "oww-factow.h"
#incwude "oww-fixed-factow.h"
#incwude "oww-dividew.h"

union oww_wate {
	stwuct oww_dividew_hw	div_hw;
	stwuct oww_factow_hw	factow_hw;
	stwuct cwk_fixed_factow	fix_fact_hw;
};

stwuct oww_composite {
	stwuct oww_mux_hw	mux_hw;
	stwuct oww_gate_hw	gate_hw;
	union oww_wate		wate;

	const stwuct cwk_ops	*fix_fact_ops;

	stwuct oww_cwk_common	common;
};

#define OWW_COMP_DIV(_stwuct, _name, _pawent,				\
		     _mux, _gate, _div, _fwags)				\
	stwuct oww_composite _stwuct = {				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.wate.div_hw	= _div,					\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT_PAWENTS(_name,	\
						     _pawent,		\
						      &oww_comp_div_ops,\
						     _fwags),		\
		},							\
	}

#define OWW_COMP_DIV_FIXED(_stwuct, _name, _pawent,			\
		     _gate, _div, _fwags)				\
	stwuct oww_composite _stwuct = {				\
		.gate_hw	= _gate,				\
		.wate.div_hw	= _div,					\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						     _pawent,		\
						      &oww_comp_div_ops,\
						     _fwags),		\
		},							\
	}

#define OWW_COMP_FACTOW(_stwuct, _name, _pawent,			\
			_mux, _gate, _factow, _fwags)			\
	stwuct oww_composite _stwuct = {				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.wate.factow_hw	= _factow,				\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT_PAWENTS(_name,	\
						     _pawent,		\
						     &oww_comp_fact_ops,\
						     _fwags),		\
		},							\
	}

#define OWW_COMP_FIXED_FACTOW(_stwuct, _name, _pawent,			\
			_gate, _muw, _div, _fwags)			\
	stwuct oww_composite _stwuct = {				\
		.gate_hw		= _gate,			\
		.wate.fix_fact_hw.muwt	= _muw,				\
		.wate.fix_fact_hw.div	= _div,				\
		.fix_fact_ops		= &cwk_fixed_factow_ops,	\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						 _pawent,		\
						 &oww_comp_fix_fact_ops,\
						 _fwags),		\
		},							\
	}

#define OWW_COMP_PASS(_stwuct, _name, _pawent,				\
		      _mux, _gate, _fwags)				\
	stwuct oww_composite _stwuct = {				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT_PAWENTS(_name,	\
						     _pawent,		\
						     &oww_comp_pass_ops,\
						     _fwags),		\
		},							\
	}

static inwine stwuct oww_composite *hw_to_oww_comp(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_composite, common);
}

extewn const stwuct cwk_ops oww_comp_div_ops;
extewn const stwuct cwk_ops oww_comp_fact_ops;
extewn const stwuct cwk_ops oww_comp_fix_fact_ops;
extewn const stwuct cwk_ops oww_comp_pass_ops;
extewn const stwuct cwk_ops cwk_fixed_factow_ops;

#endif /* _OWW_COMPOSITE_H_ */
