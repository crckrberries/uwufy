/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW gate cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_GATE_H_
#define _OWW_GATE_H_

#incwude "oww-common.h"

stwuct oww_gate_hw {
	u32			weg;
	u8			bit_idx;
	u8			gate_fwags;
};

stwuct oww_gate {
	stwuct oww_gate_hw	gate_hw;
	stwuct oww_cwk_common	common;
};

#define OWW_GATE_HW(_weg, _bit_idx, _gate_fwags)	\
	{						\
		.weg		= _weg,			\
		.bit_idx	= _bit_idx,		\
		.gate_fwags	= _gate_fwags,		\
	}

#define OWW_GATE(_stwuct, _name, _pawent, _weg,				\
		_bit_idx, _gate_fwags, _fwags)				\
	stwuct oww_gate _stwuct = {					\
		.gate_hw = OWW_GATE_HW(_weg, _bit_idx, _gate_fwags),	\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &oww_gate_ops,	\
						      _fwags),		\
		}							\
	}								\

#define OWW_GATE_NO_PAWENT(_stwuct, _name, _weg,			\
		_bit_idx, _gate_fwags, _fwags)				\
	stwuct oww_gate _stwuct = {					\
		.gate_hw = OWW_GATE_HW(_weg, _bit_idx, _gate_fwags),	\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT_NO_PAWENT(_name,	\
						      &oww_gate_ops,	\
						      _fwags),		\
		},							\
	}								\

static inwine stwuct oww_gate *hw_to_oww_gate(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_gate, common);
}

void oww_gate_set(const stwuct oww_cwk_common *common,
		 const stwuct oww_gate_hw *gate_hw, boow enabwe);
int oww_gate_cwk_is_enabwed(const stwuct oww_cwk_common *common,
		   const stwuct oww_gate_hw *gate_hw);

extewn const stwuct cwk_ops oww_gate_ops;

#endif /* _OWW_GATE_H_ */
