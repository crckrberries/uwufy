/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_DIV_H_
#define _CCU_DIV_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"
#incwude "ccu_mux.h"

/**
 * stwuct ccu_div_intewnaw - Intewnaw dividew descwiption
 * @shift: Bit offset of the dividew in its wegistew
 * @width: Width of the dividew fiewd in its wegistew
 * @max: Maximum vawue awwowed fow that dividew. This is the
 *       awithmetic vawue, not the maximum vawue to be set in the
 *       wegistew.
 * @fwags: cwk_dividew fwags to appwy on this dividew
 * @tabwe: Dividew tabwe pointew (if appwicabwe)
 *
 * That stwuctuwe wepwesents a singwe dividew, and is meant to be
 * embedded in othew stwuctuwes wepwesenting the vawious cwock
 * cwasses.
 *
 * It is basicawwy a wwappew awound the cwk_dividew functions
 * awguments.
 */
stwuct ccu_div_intewnaw {
	u8			shift;
	u8			width;

	u32			max;
	u32			offset;

	u32			fwags;

	stwuct cwk_div_tabwe	*tabwe;
};

#define _SUNXI_CCU_DIV_TABWE_FWAGS(_shift, _width, _tabwe, _fwags)	\
	{								\
		.shift	= _shift,					\
		.width	= _width,					\
		.fwags	= _fwags,					\
		.tabwe	= _tabwe,					\
	}

#define _SUNXI_CCU_DIV_TABWE(_shift, _width, _tabwe)			\
	_SUNXI_CCU_DIV_TABWE_FWAGS(_shift, _width, _tabwe, 0)

#define _SUNXI_CCU_DIV_OFFSET_MAX_FWAGS(_shift, _width, _off, _max, _fwags) \
	{								\
		.shift	= _shift,					\
		.width	= _width,					\
		.fwags	= _fwags,					\
		.max	= _max,						\
		.offset	= _off,						\
	}

#define _SUNXI_CCU_DIV_MAX_FWAGS(_shift, _width, _max, _fwags)		\
	_SUNXI_CCU_DIV_OFFSET_MAX_FWAGS(_shift, _width, 1, _max, _fwags)

#define _SUNXI_CCU_DIV_FWAGS(_shift, _width, _fwags)			\
	_SUNXI_CCU_DIV_MAX_FWAGS(_shift, _width, 0, _fwags)

#define _SUNXI_CCU_DIV_MAX(_shift, _width, _max)			\
	_SUNXI_CCU_DIV_MAX_FWAGS(_shift, _width, _max, 0)

#define _SUNXI_CCU_DIV_OFFSET(_shift, _width, _offset)			\
	_SUNXI_CCU_DIV_OFFSET_MAX_FWAGS(_shift, _width, _offset, 0, 0)

#define _SUNXI_CCU_DIV(_shift, _width)					\
	_SUNXI_CCU_DIV_FWAGS(_shift, _width, 0)

stwuct ccu_div {
	u32			enabwe;

	stwuct ccu_div_intewnaw	div;
	stwuct ccu_mux_intewnaw	mux;
	stwuct ccu_common	common;
	unsigned int		fixed_post_div;
};

#define SUNXI_CCU_DIV_TABWE_WITH_GATE(_stwuct, _name, _pawent, _weg,	\
				      _shift, _width,			\
				      _tabwe, _gate, _fwags)		\
	stwuct ccu_div _stwuct = {					\
		.div		= _SUNXI_CCU_DIV_TABWE(_shift, _width,	\
						       _tabwe),		\
		.enabwe		= _gate,				\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_div_ops,	\
						      _fwags),		\
		}							\
	}


#define SUNXI_CCU_DIV_TABWE(_stwuct, _name, _pawent, _weg,		\
			    _shift, _width,				\
			    _tabwe, _fwags)				\
	SUNXI_CCU_DIV_TABWE_WITH_GATE(_stwuct, _name, _pawent, _weg,	\
				      _shift, _width, _tabwe, 0,	\
				      _fwags)

#define SUNXI_CCU_DIV_TABWE_HW(_stwuct, _name, _pawent, _weg,		\
			       _shift, _width,				\
			       _tabwe, _fwags)				\
	stwuct ccu_div _stwuct = {					\
		.div		= _SUNXI_CCU_DIV_TABWE(_shift, _width,	\
						       _tabwe),		\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_HW(_name,		\
							 _pawent,	\
							 &ccu_div_ops,	\
							 _fwags),	\
		}							\
	}


#define SUNXI_CCU_M_WITH_MUX_TABWE_GATE(_stwuct, _name,			\
					_pawents, _tabwe,		\
					_weg,				\
					_mshift, _mwidth,		\
					_muxshift, _muxwidth,		\
					_gate, _fwags)			\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV(_mshift, _mwidth),		\
		.mux	= _SUNXI_CCU_MUX_TABWE(_muxshift, _muxwidth, _tabwe), \
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_PAWENTS(_name,	\
							      _pawents, \
							      &ccu_div_ops, \
							      _fwags),	\
		},							\
	}

#define SUNXI_CCU_M_WITH_MUX_TABWE_GATE_CWOSEST(_stwuct, _name,		\
						_pawents, _tabwe,	\
						_weg,			\
						_mshift, _mwidth,	\
						_muxshift, _muxwidth,	\
						_gate, _fwags)		\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV_FWAGS(_mshift, _mwidth, CWK_DIVIDEW_WOUND_CWOSEST), \
		.mux	= _SUNXI_CCU_MUX_TABWE(_muxshift, _muxwidth, _tabwe), \
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_PAWENTS(_name,	\
							      _pawents, \
							      &ccu_div_ops, \
							      _fwags),	\
			.featuwes	= CCU_FEATUWE_CWOSEST_WATE,	\
		},							\
	}

#define SUNXI_CCU_M_WITH_MUX_GATE(_stwuct, _name, _pawents, _weg,	\
				  _mshift, _mwidth, _muxshift, _muxwidth, \
				  _gate, _fwags)			\
	SUNXI_CCU_M_WITH_MUX_TABWE_GATE(_stwuct, _name,			\
					_pawents, NUWW,			\
					_weg, _mshift, _mwidth,		\
					_muxshift, _muxwidth,		\
					_gate, _fwags)

#define SUNXI_CCU_M_WITH_MUX_GATE_CWOSEST(_stwuct, _name, _pawents,	\
					  _weg, _mshift, _mwidth,	\
					  _muxshift, _muxwidth,		\
					  _gate, _fwags)		\
	SUNXI_CCU_M_WITH_MUX_TABWE_GATE_CWOSEST(_stwuct, _name,		\
						_pawents, NUWW,		\
						_weg, _mshift, _mwidth,	\
						_muxshift, _muxwidth,	\
						_gate, _fwags)

#define SUNXI_CCU_M_WITH_MUX(_stwuct, _name, _pawents, _weg,		\
			     _mshift, _mwidth, _muxshift, _muxwidth,	\
			     _fwags)					\
	SUNXI_CCU_M_WITH_MUX_TABWE_GATE(_stwuct, _name,			\
					_pawents, NUWW,			\
					_weg, _mshift, _mwidth,		\
					_muxshift, _muxwidth,		\
					0, _fwags)


#define SUNXI_CCU_M_WITH_GATE(_stwuct, _name, _pawent, _weg,		\
			      _mshift, _mwidth,	_gate,			\
			      _fwags)					\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV(_mshift, _mwidth),		\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_div_ops,	\
						      _fwags),		\
		},							\
	}

#define SUNXI_CCU_M(_stwuct, _name, _pawent, _weg, _mshift, _mwidth,	\
		    _fwags)						\
	SUNXI_CCU_M_WITH_GATE(_stwuct, _name, _pawent, _weg,		\
			      _mshift, _mwidth, 0, _fwags)

#define SUNXI_CCU_M_DATA_WITH_MUX_GATE(_stwuct, _name, _pawents, _weg,	\
				       _mshift, _mwidth,		\
				       _muxshift, _muxwidth,		\
				       _gate, _fwags)			\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV(_mshift, _mwidth),		\
		.mux	= _SUNXI_CCU_MUX(_muxshift, _muxwidth),		\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_PAWENTS_DATA(_name, \
								   _pawents, \
								   &ccu_div_ops, \
								   _fwags), \
		},							\
	}

#define SUNXI_CCU_M_DATA_WITH_MUX(_stwuct, _name, _pawents, _weg,	\
				  _mshift, _mwidth,			\
				  _muxshift, _muxwidth,			\
				  _fwags)				\
	SUNXI_CCU_M_DATA_WITH_MUX_GATE(_stwuct, _name, _pawents, _weg,  \
				       _mshift, _mwidth,		\
				       _muxshift, _muxwidth,		\
				       0, _fwags)

#define SUNXI_CCU_M_HW_WITH_MUX_GATE(_stwuct, _name, _pawents, _weg,	\
				     _mshift, _mwidth, _muxshift, _muxwidth, \
				     _gate, _fwags)			\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV(_mshift, _mwidth),		\
		.mux	= _SUNXI_CCU_MUX(_muxshift, _muxwidth),		\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_PAWENTS_HW(_name,	\
								 _pawents, \
								 &ccu_div_ops, \
								 _fwags), \
		},							\
	}

#define SUNXI_CCU_M_HWS_WITH_GATE(_stwuct, _name, _pawent, _weg,	\
				  _mshift, _mwidth, _gate,		\
				  _fwags)				\
	stwuct ccu_div _stwuct = {					\
		.enabwe	= _gate,					\
		.div	= _SUNXI_CCU_DIV(_mshift, _mwidth),		\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_HWS(_name,	\
							  _pawent,	\
							  &ccu_div_ops,	\
							  _fwags),	\
		},							\
	}

#define SUNXI_CCU_M_HWS(_stwuct, _name, _pawent, _weg, _mshift,		\
			_mwidth, _fwags)				\
	SUNXI_CCU_M_HWS_WITH_GATE(_stwuct, _name, _pawent, _weg,	\
				  _mshift, _mwidth, 0, _fwags)

static inwine stwuct ccu_div *hw_to_ccu_div(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_div, common);
}

extewn const stwuct cwk_ops ccu_div_ops;

#endif /* _CCU_DIV_H_ */
