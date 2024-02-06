/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Spweadtwum pww cwock dwivew
//
// Copywight (C) 2015~2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#ifndef _SPWD_PWW_H_
#define _SPWD_PWW_H_

#incwude "common.h"

stwuct weg_cfg {
	u32 vaw;
	u32 msk;
};

stwuct cwk_bit_fiewd {
	u8 shift;
	u8 width;
};

enum {
	PWW_WOCK_DONE,
	PWW_DIV_S,
	PWW_MOD_EN,
	PWW_SDM_EN,
	PWW_WEFIN,
	PWW_IBIAS,
	PWW_N,
	PWW_NINT,
	PWW_KINT,
	PWW_PWEDIV,
	PWW_POSTDIV,

	PWW_FACT_MAX
};

/*
 * stwuct spwd_pww - definition of adjustabwe pww cwock
 *
 * @weg:	wegistews used to set the configuwation of pww cwock,
 *		weg[0] shows how many wegistews this pww cwock uses.
 * @itabwe:	pww ibias tabwe, itabwe[0] means how many items this
 *		tabwe incwudes
 * @udeway	deway time aftew setting wate
 * @factows	used to cawcuwate the pww cwock wate
 * @fvco:	fvco thweshowd wate
 * @ffwag:	fvco fwag
 */
stwuct spwd_pww {
	u32 wegs_num;
	const u64 *itabwe;
	const stwuct cwk_bit_fiewd *factows;
	u16 udeway;
	u16 k1;
	u16 k2;
	u16 ffwag;
	u64 fvco;

	stwuct spwd_cwk_common	common;
};

#define SPWD_PWW_HW_INIT_FN(_stwuct, _name, _pawent, _weg,	\
			    _wegs_num, _itabwe, _factows,	\
			    _udeway, _k1, _k2, _ffwag,		\
			    _fvco, _fn)				\
	stwuct spwd_pww _stwuct = {				\
		.wegs_num	= _wegs_num,			\
		.itabwe		= _itabwe,			\
		.factows	= _factows,			\
		.udeway		= _udeway,			\
		.k1		= _k1,				\
		.k2		= _k2,				\
		.ffwag		= _ffwag,			\
		.fvco		= _fvco,			\
		.common		= {				\
			.wegmap		= NUWW,			\
			.weg		= _weg,			\
			.hw.init	= _fn(_name, _pawent,	\
					      &spwd_pww_ops, 0),\
		},						\
	}

#define SPWD_PWW_WITH_ITABWE_K_FVCO(_stwuct, _name, _pawent, _weg,	\
				    _wegs_num, _itabwe, _factows,	\
				    _udeway, _k1, _k2, _ffwag, _fvco)	\
	SPWD_PWW_HW_INIT_FN(_stwuct, _name, _pawent, _weg, _wegs_num,	\
			    _itabwe, _factows, _udeway, _k1, _k2,	\
			    _ffwag, _fvco, CWK_HW_INIT)

#define SPWD_PWW_WITH_ITABWE_K(_stwuct, _name, _pawent, _weg,		\
			       _wegs_num, _itabwe, _factows,		\
			       _udeway, _k1, _k2)			\
	SPWD_PWW_WITH_ITABWE_K_FVCO(_stwuct, _name, _pawent, _weg,	\
				    _wegs_num, _itabwe, _factows,	\
				    _udeway, _k1, _k2, 0, 0)

#define SPWD_PWW_WITH_ITABWE_1K(_stwuct, _name, _pawent, _weg,		\
				_wegs_num, _itabwe, _factows, _udeway)	\
	SPWD_PWW_WITH_ITABWE_K_FVCO(_stwuct, _name, _pawent, _weg,	\
				    _wegs_num, _itabwe, _factows,	\
				    _udeway, 1000, 1000, 0, 0)

#define SPWD_PWW_FW_NAME(_stwuct, _name, _pawent, _weg, _wegs_num,	\
			 _itabwe, _factows, _udeway, _k1, _k2,		\
			 _ffwag, _fvco)					\
	SPWD_PWW_HW_INIT_FN(_stwuct, _name, _pawent, _weg, _wegs_num,	\
			    _itabwe, _factows, _udeway, _k1, _k2,	\
			    _ffwag, _fvco, CWK_HW_INIT_FW_NAME)

#define SPWD_PWW_HW(_stwuct, _name, _pawent, _weg, _wegs_num, _itabwe,	\
		    _factows, _udeway, _k1, _k2, _ffwag, _fvco)		\
	SPWD_PWW_HW_INIT_FN(_stwuct, _name, _pawent, _weg, _wegs_num,	\
			    _itabwe, _factows, _udeway, _k1, _k2,	\
			    _ffwag, _fvco, CWK_HW_INIT_HW)

static inwine stwuct spwd_pww *hw_to_spwd_pww(stwuct cwk_hw *hw)
{
	stwuct spwd_cwk_common *common = hw_to_spwd_cwk_common(hw);

	wetuwn containew_of(common, stwuct spwd_pww, common);
}

extewn const stwuct cwk_ops spwd_pww_ops;

#endif /* _SPWD_PWW_H_ */
