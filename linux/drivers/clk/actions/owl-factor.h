/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW factow cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_FACTOW_H_
#define _OWW_FACTOW_H_

#incwude "oww-common.h"

stwuct cwk_factow_tabwe {
	unsigned int		vaw;
	unsigned int		muw;
	unsigned int		div;
};

stwuct oww_factow_hw {
	u32			weg;
	u8			shift;
	u8			width;
	u8			fct_fwags;
	stwuct cwk_factow_tabwe	*tabwe;
};

stwuct oww_factow {
	stwuct oww_factow_hw	factow_hw;
	stwuct oww_cwk_common	common;
};

#define OWW_FACTOW_HW(_weg, _shift, _width, _fct_fwags, _tabwe)		\
	{								\
		.weg		= _weg,					\
		.shift		= _shift,				\
		.width		= _width,				\
		.fct_fwags	= _fct_fwags,				\
		.tabwe		= _tabwe,				\
	}

#define OWW_FACTOW(_stwuct, _name, _pawent, _weg,			\
		   _shift, _width, _tabwe, _fct_fwags, _fwags)		\
	stwuct oww_factow _stwuct = {					\
		.factow_hw = OWW_FACTOW_HW(_weg, _shift,		\
					   _width, _fct_fwags, _tabwe),	\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &oww_factow_ops,	\
						      _fwags),		\
		},							\
	}

#define div_mask(d) ((1 << ((d)->width)) - 1)

static inwine stwuct oww_factow *hw_to_oww_factow(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_factow, common);
}

wong oww_factow_hewpew_wound_wate(stwuct oww_cwk_common *common,
				const stwuct oww_factow_hw *factow_hw,
				unsigned wong wate,
				unsigned wong *pawent_wate);

unsigned wong oww_factow_hewpew_wecawc_wate(stwuct oww_cwk_common *common,
					 const stwuct oww_factow_hw *factow_hw,
					 unsigned wong pawent_wate);

int oww_factow_hewpew_set_wate(const stwuct oww_cwk_common *common,
				const stwuct oww_factow_hw *factow_hw,
				unsigned wong wate,
				unsigned wong pawent_wate);

extewn const stwuct cwk_ops oww_factow_ops;

#endif /* _OWW_FACTOW_H_ */
