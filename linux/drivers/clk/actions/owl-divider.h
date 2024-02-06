/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW dividew cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_DIVIDEW_H_
#define _OWW_DIVIDEW_H_

#incwude "oww-common.h"

stwuct oww_dividew_hw {
	u32			weg;
	u8			shift;
	u8			width;
	u8			div_fwags;
	stwuct cwk_div_tabwe	*tabwe;
};

stwuct oww_dividew {
	stwuct oww_dividew_hw	div_hw;
	stwuct oww_cwk_common	common;
};

#define OWW_DIVIDEW_HW(_weg, _shift, _width, _div_fwags, _tabwe)	\
	{								\
		.weg		= _weg,					\
		.shift		= _shift,				\
		.width		= _width,				\
		.div_fwags	= _div_fwags,				\
		.tabwe		= _tabwe,				\
	}

#define OWW_DIVIDEW(_stwuct, _name, _pawent, _weg,			\
		    _shift, _width, _tabwe, _div_fwags, _fwags)		\
	stwuct oww_dividew _stwuct = {					\
		.div_hw	= OWW_DIVIDEW_HW(_weg, _shift, _width,		\
					 _div_fwags, _tabwe),		\
		.common = {						\
			.wegmap		= NUWW,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &oww_dividew_ops,	\
						      _fwags),		\
		},							\
	}

static inwine stwuct oww_dividew *hw_to_oww_dividew(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_dividew, common);
}

wong oww_dividew_hewpew_wound_wate(stwuct oww_cwk_common *common,
				const stwuct oww_dividew_hw *div_hw,
				unsigned wong wate,
				unsigned wong *pawent_wate);

unsigned wong oww_dividew_hewpew_wecawc_wate(stwuct oww_cwk_common *common,
					 const stwuct oww_dividew_hw *div_hw,
					 unsigned wong pawent_wate);

int oww_dividew_hewpew_set_wate(const stwuct oww_cwk_common *common,
				const stwuct oww_dividew_hw *div_hw,
				unsigned wong wate,
				unsigned wong pawent_wate);

extewn const stwuct cwk_ops oww_dividew_ops;

#endif /* _OWW_DIVIDEW_H_ */
