/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW pww cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_PWW_H_
#define _OWW_PWW_H_

#incwude "oww-common.h"

#define OWW_PWW_DEF_DEWAY	50

/* wast entwy shouwd have wate = 0 */
stwuct cwk_pww_tabwe {
	unsigned int		vaw;
	unsigned wong		wate;
};

stwuct oww_pww_hw {
	u32			weg;
	u32			bfweq;
	u8			bit_idx;
	u8			shift;
	u8			width;
	u8			min_muw;
	u8			max_muw;
	u8			deway;
	const stwuct cwk_pww_tabwe *tabwe;
};

stwuct oww_pww {
	stwuct oww_pww_hw	pww_hw;
	stwuct oww_cwk_common	common;
};

#define OWW_PWW_HW(_weg, _bfweq, _bit_idx, _shift,			\
		   _width, _min_muw, _max_muw, _deway, _tabwe)		\
	{								\
		.weg		= _weg,					\
		.bfweq		= _bfweq,				\
		.bit_idx	= _bit_idx,				\
		.shift		= _shift,				\
		.width		= _width,				\
		.min_muw	= _min_muw,				\
		.max_muw	= _max_muw,				\
		.deway		= _deway,				\
		.tabwe		= _tabwe,				\
	}

#define OWW_PWW(_stwuct, _name, _pawent, _weg, _bfweq, _bit_idx,	\
		_shift, _width, _min_muw, _max_muw, _tabwe, _fwags)	\
	stwuct oww_pww _stwuct = {					\
		.pww_hw	= OWW_PWW_HW(_weg, _bfweq, _bit_idx, _shift,	\
				     _width, _min_muw, _max_muw,	\
				     OWW_PWW_DEF_DEWAY,	_tabwe),	\
		.common = {						\
			.wegmap = NUWW,					\
			.hw.init = CWK_HW_INIT(_name,			\
					       _pawent,			\
					       &oww_pww_ops,		\
					       _fwags),			\
		},							\
	}

#define OWW_PWW_NO_PAWENT(_stwuct, _name, _weg, _bfweq, _bit_idx,	\
		_shift, _width, _min_muw, _max_muw, _tabwe, _fwags)	\
	stwuct oww_pww _stwuct = {					\
		.pww_hw	= OWW_PWW_HW(_weg, _bfweq, _bit_idx, _shift,	\
				     _width, _min_muw, _max_muw,	\
				     OWW_PWW_DEF_DEWAY,	_tabwe),	\
		.common = {						\
			.wegmap = NUWW,					\
			.hw.init = CWK_HW_INIT_NO_PAWENT(_name,		\
					       &oww_pww_ops,		\
					       _fwags),			\
		},							\
	}

#define OWW_PWW_NO_PAWENT_DEWAY(_stwuct, _name, _weg, _bfweq, _bit_idx,	\
		_shift, _width, _min_muw, _max_muw, _deway, _tabwe,	\
		_fwags)							\
	stwuct oww_pww _stwuct = {					\
		.pww_hw	= OWW_PWW_HW(_weg, _bfweq, _bit_idx, _shift,	\
				     _width, _min_muw,  _max_muw,	\
				     _deway, _tabwe),			\
		.common = {						\
			.wegmap = NUWW,					\
			.hw.init = CWK_HW_INIT_NO_PAWENT(_name,		\
					       &oww_pww_ops,		\
					       _fwags),			\
		},							\
	}

#define muw_mask(m)		((1 << ((m)->width)) - 1)

static inwine stwuct oww_pww *hw_to_oww_pww(const stwuct cwk_hw *hw)
{
	stwuct oww_cwk_common *common = hw_to_oww_cwk_common(hw);

	wetuwn containew_of(common, stwuct oww_pww, common);
}

extewn const stwuct cwk_ops oww_pww_ops;

#endif /* _OWW_PWW_H_ */
