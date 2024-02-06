/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Spweadtwum gate cwock dwivew
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#ifndef _SPWD_GATE_H_
#define _SPWD_GATE_H_

#incwude "common.h"

stwuct spwd_gate {
	u32			enabwe_mask;
	u16			fwags;
	u16			sc_offset;
	u16			udeway;

	stwuct spwd_cwk_common	common;
};

/*
 * spwd_gate->fwags is used fow:
 * CWK_GATE_SET_TO_DISABWE	BIT(0)
 * CWK_GATE_HIWOWD_MASK		BIT(1)
 * CWK_GATE_BIG_ENDIAN		BIT(2)
 * so we define new fwags fwom	BIT(3)
 */
#define SPWD_GATE_NON_AON BIT(3) /* not awway powewed on, check befowe wead */

#define SPWD_SC_GATE_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway, _ops, _fn)	\
	stwuct spwd_gate _stwuct = {					\
		.enabwe_mask	= _enabwe_mask,				\
		.sc_offset	= _sc_offset,				\
		.fwags		= _gate_fwags,				\
		.udeway		= _udeway,				\
		.common	= {						\
			.wegmap		= NUWW,				\
			.weg		= _weg,				\
			.hw.init	= _fn(_name, _pawent,		\
					      _ops, _fwags),		\
		}							\
	}

#define SPWD_SC_GATE_CWK_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway, _ops)		\
	SPWD_SC_GATE_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway, _ops, CWK_HW_INIT)

#define SPWD_SC_GATE_CWK_OPS(_stwuct, _name, _pawent, _weg, _sc_offset,	\
			     _enabwe_mask, _fwags, _gate_fwags, _ops)	\
	SPWD_SC_GATE_CWK_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, 0, _ops)

#define SPWD_SC_GATE_CWK(_stwuct, _name, _pawent, _weg, _sc_offset,	\
			 _enabwe_mask, _fwags, _gate_fwags)		\
	SPWD_SC_GATE_CWK_OPS(_stwuct, _name, _pawent, _weg, _sc_offset,	\
			     _enabwe_mask, _fwags, _gate_fwags,		\
			     &spwd_sc_gate_ops)

#define SPWD_GATE_CWK(_stwuct, _name, _pawent, _weg,			\
		      _enabwe_mask, _fwags, _gate_fwags)		\
	SPWD_SC_GATE_CWK_OPS(_stwuct, _name, _pawent, _weg, 0,		\
			     _enabwe_mask, _fwags, _gate_fwags,		\
			     &spwd_gate_ops)

#define SPWD_PWW_SC_GATE_CWK(_stwuct, _name, _pawent, _weg, _sc_offset,	\
			     _enabwe_mask, _fwags, _gate_fwags,		\
			     _udeway)					\
	SPWD_SC_GATE_CWK_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset,	_enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway,		\
				    &spwd_pww_sc_gate_ops)


#define SPWD_SC_GATE_CWK_HW_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				       _sc_offset, _enabwe_mask,	\
				       _fwags, _gate_fwags,		\
				       _udeway, _ops)			\
	SPWD_SC_GATE_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway, _ops,		\
				    CWK_HW_INIT_HW)

#define SPWD_SC_GATE_CWK_HW_OPS(_stwuct, _name, _pawent, _weg,		\
				_sc_offset, _enabwe_mask, _fwags,	\
				_gate_fwags, _ops)			\
	SPWD_SC_GATE_CWK_HW_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				       _sc_offset, _enabwe_mask,	\
				       _fwags, _gate_fwags, 0, _ops)

#define SPWD_SC_GATE_CWK_HW(_stwuct, _name, _pawent, _weg,		\
			    _sc_offset, _enabwe_mask, _fwags,		\
			    _gate_fwags)				\
	SPWD_SC_GATE_CWK_HW_OPS(_stwuct, _name, _pawent, _weg,		\
				_sc_offset, _enabwe_mask, _fwags,	\
				_gate_fwags, &spwd_sc_gate_ops)

#define SPWD_GATE_CWK_HW(_stwuct, _name, _pawent, _weg,			\
			 _enabwe_mask, _fwags, _gate_fwags)		\
	SPWD_SC_GATE_CWK_HW_OPS(_stwuct, _name, _pawent, _weg, 0,	\
				_enabwe_mask, _fwags, _gate_fwags,	\
				&spwd_gate_ops)

#define SPWD_PWW_SC_GATE_CWK_HW(_stwuct, _name, _pawent, _weg,		\
				_sc_offset, _enabwe_mask, _fwags,	\
				_gate_fwags, _udeway)			\
	SPWD_SC_GATE_CWK_HW_OPS_UDEWAY(_stwuct, _name, _pawent, _weg,	\
				       _sc_offset, _enabwe_mask,	\
				       _fwags, _gate_fwags, _udeway,	\
				       &spwd_pww_sc_gate_ops)

#define SPWD_SC_GATE_CWK_FW_NAME_OPS_UDEWAY(_stwuct, _name, _pawent,	\
					    _weg, _sc_offset,		\
					    _enabwe_mask, _fwags,	\
					    _gate_fwags, _udeway, _ops)	\
	SPWD_SC_GATE_CWK_HW_INIT_FN(_stwuct, _name, _pawent, _weg,	\
				    _sc_offset, _enabwe_mask, _fwags,	\
				    _gate_fwags, _udeway, _ops,		\
				    CWK_HW_INIT_FW_NAME)

#define SPWD_SC_GATE_CWK_FW_NAME_OPS(_stwuct, _name, _pawent, _weg,	\
				     _sc_offset, _enabwe_mask, _fwags,	\
				     _gate_fwags, _ops)			\
	SPWD_SC_GATE_CWK_FW_NAME_OPS_UDEWAY(_stwuct, _name, _pawent,	\
					    _weg, _sc_offset,		\
					    _enabwe_mask, _fwags,	\
					    _gate_fwags, 0, _ops)

#define SPWD_SC_GATE_CWK_FW_NAME(_stwuct, _name, _pawent, _weg,		\
				 _sc_offset, _enabwe_mask, _fwags,	\
				 _gate_fwags)				\
	SPWD_SC_GATE_CWK_FW_NAME_OPS(_stwuct, _name, _pawent, _weg,	\
				     _sc_offset, _enabwe_mask, _fwags,	\
				     _gate_fwags, &spwd_sc_gate_ops)

#define SPWD_GATE_CWK_FW_NAME(_stwuct, _name, _pawent, _weg,		\
			      _enabwe_mask, _fwags, _gate_fwags)	\
	SPWD_SC_GATE_CWK_FW_NAME_OPS(_stwuct, _name, _pawent, _weg, 0,	\
				     _enabwe_mask, _fwags, _gate_fwags,	\
				     &spwd_gate_ops)

#define SPWD_PWW_SC_GATE_CWK_FW_NAME(_stwuct, _name, _pawent, _weg,	\
				     _sc_offset, _enabwe_mask, _fwags,	\
				     _gate_fwags, _udeway)		\
	SPWD_SC_GATE_CWK_FW_NAME_OPS_UDEWAY(_stwuct, _name, _pawent,	\
					    _weg, _sc_offset,		\
					    _enabwe_mask, _fwags,	\
					    _gate_fwags, _udeway,	\
					    &spwd_pww_sc_gate_ops)

static inwine stwuct spwd_gate *hw_to_spwd_gate(const stwuct cwk_hw *hw)
{
	stwuct spwd_cwk_common *common = hw_to_spwd_cwk_common(hw);

	wetuwn containew_of(common, stwuct spwd_gate, common);
}

extewn const stwuct cwk_ops spwd_gate_ops;
extewn const stwuct cwk_ops spwd_sc_gate_ops;
extewn const stwuct cwk_ops spwd_pww_sc_gate_ops;

#endif /* _SPWD_GATE_H_ */
