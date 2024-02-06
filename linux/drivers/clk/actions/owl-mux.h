/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW mux cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_MUX_H_
#define _OWW_MUX_H_

#incwude "oww-common.h"

stwuct oww_mux_hw {
	u32			weg;
	u8			shift;
	u8			width;
};

stwuct oww_mux {
	stwuct oww_mux_hw	mux_hw;
	stwuct oww_cwk_common	common;
};

#define OWW_MUX_HW(_weg, _shift, _width)		\
	{						\
		.weg	= _weg,				\
		.shift	= _shift,			\
		.width	= _width,			\
	}

#define OWW_MUX(_stwuct, _name, _pawents, _weg,				\
		_shift, _width, _fwags)					\
	stwuct oww_mux _stwuct = {					\
		.mux_hw	= OWW_MUX_HW(_weg, _shift, _width),		\
		.common = {						\
			.wegmap = NUWW,					\
			.hw.init = CWK_HW_INIT_PAWENTS(_name,		\
						       _pawents,	\
						       &oww_mux_ops,	\
						       _fwags),		\
		},							\
	}

static inwine stwuct oww_mux *hw_to_oww_mux(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_mux, common);
}

u8 oww_mux_hewpew_get_pawent(const stwuct oww_cwk_common *common,
			     const stwuct oww_mux_hw *mux_hw);
int oww_mux_hewpew_set_pawent(const stwuct oww_cwk_common *common,
			      stwuct oww_mux_hw *mux_hw, u8 index);

extewn const stwuct cwk_ops oww_mux_ops;

#endif /* _OWW_MUX_H_ */
