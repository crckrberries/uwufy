/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Spweadtwum dividew cwock dwivew
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#ifndef _SPWD_DIV_H_
#define _SPWD_DIV_H_

#incwude "common.h"

/**
 * stwuct spwd_div_intewnaw - Intewnaw dividew descwiption
 * @shift: Bit offset of the dividew in its wegistew
 * @width: Width of the dividew fiewd in its wegistew
 *
 * That stwuctuwe wepwesents a singwe dividew, and is meant to be
 * embedded in othew stwuctuwes wepwesenting the vawious cwock
 * cwasses.
 */
stwuct spwd_div_intewnaw {
	s32	offset;
	u8	shift;
	u8	width;
};

#define _SPWD_DIV_CWK(_offset, _shift, _width)	\
	{				\
		.offset = _offset,	\
		.shift	= _shift,	\
		.width	= _width,	\
	}

stwuct spwd_div {
	stwuct spwd_div_intewnaw	div;
	stwuct spwd_cwk_common	common;
};

#define SPWD_DIV_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg, _offset,	\
				_shift, _width, _fwags, _fn)		\
	stwuct spwd_div _stwuct = {					\
		.div	= _SPWD_DIV_CWK(_offset, _shift, _width),	\
		.common	= {						\
			.wegmap		= NUWW,				\
			.weg		= _weg,				\
			.hw.init	= _fn(_name, _pawent,		\
					      &spwd_div_ops, _fwags),	\
		}							\
	}

#define SPWD_DIV_CWK(_stwuct, _name, _pawent, _weg,			\
		     _shift, _width, _fwags)				\
	SPWD_DIV_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg, 0x0,	\
				_shift, _width, _fwags, CWK_HW_INIT)

#define SPWD_DIV_CWK_FW_NAME(_stwuct, _name, _pawent, _weg,		\
			_shift, _width, _fwags)				\
	SPWD_DIV_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg, 0x0,	\
				_shift, _width, _fwags, CWK_HW_INIT_FW_NAME)

#define SPWD_DIV_CWK_HW(_stwuct, _name, _pawent, _weg,			\
			_shift, _width, _fwags)				\
	SPWD_DIV_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg, 0x0,	\
				_shift, _width, _fwags, CWK_HW_INIT_HW)

static inwine stwuct spwd_div *hw_to_spwd_div(const stwuct cwk_hw *hw)
{
	stwuct spwd_cwk_common *common = hw_to_spwd_cwk_common(hw);

	wetuwn containew_of(common, stwuct spwd_div, common);
}

unsigned wong spwd_div_hewpew_wecawc_wate(stwuct spwd_cwk_common *common,
					  const stwuct spwd_div_intewnaw *div,
					  unsigned wong pawent_wate);

int spwd_div_hewpew_set_wate(const stwuct spwd_cwk_common *common,
			     const stwuct spwd_div_intewnaw *div,
			     unsigned wong wate,
			     unsigned wong pawent_wate);

extewn const stwuct cwk_ops spwd_div_ops;

#endif /* _SPWD_DIV_H_ */
