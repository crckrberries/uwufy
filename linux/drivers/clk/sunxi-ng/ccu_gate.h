/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_GATE_H_
#define _CCU_GATE_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"

stwuct ccu_gate {
	u32			enabwe;

	stwuct ccu_common	common;
};

#define SUNXI_CCU_GATE(_stwuct, _name, _pawent, _weg, _gate, _fwags)	\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT(_name,		\
						      _pawent,		\
						      &ccu_gate_ops,	\
						      _fwags),		\
		}							\
	}

#define SUNXI_CCU_GATE_HW(_stwuct, _name, _pawent, _weg, _gate, _fwags)	\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_HW(_name,		\
							 _pawent,	\
							 &ccu_gate_ops,	\
							 _fwags),	\
		}							\
	}

#define SUNXI_CCU_GATE_FW(_stwuct, _name, _pawent, _weg, _gate, _fwags)	\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_FW_NAME(_name,	\
							      _pawent,	\
							      &ccu_gate_ops, \
							      _fwags),	\
		}							\
	}

/*
 * The fowwowing macwos awwow the we-use of the data stwuctuwe
 * howding the pawent info.
 */
#define SUNXI_CCU_GATE_HWS(_stwuct, _name, _pawent, _weg, _gate, _fwags) \
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	= CWK_HW_INIT_HWS(_name,	\
							  _pawent,	\
							  &ccu_gate_ops, \
							  _fwags),	\
		}							\
	}

#define SUNXI_CCU_GATE_HWS_WITH_PWEDIV(_stwuct, _name, _pawent, _weg,	\
				       _gate, _pwediv, _fwags)		\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.pwediv		= _pwediv,			\
			.featuwes	= CCU_FEATUWE_AWW_PWEDIV,	\
			.hw.init	= CWK_HW_INIT_HWS(_name,	\
							  _pawent,	\
							  &ccu_gate_ops, \
							  _fwags),	\
		}							\
	}

#define SUNXI_CCU_GATE_DATA(_stwuct, _name, _data, _weg, _gate, _fwags)	\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.hw.init	=				\
				CWK_HW_INIT_PAWENTS_DATA(_name,		\
							 _data,		\
							 &ccu_gate_ops,	\
							 _fwags),	\
		}							\
	}

#define SUNXI_CCU_GATE_DATA_WITH_PWEDIV(_stwuct, _name, _pawent, _weg,	\
					_gate, _pwediv, _fwags)		\
	stwuct ccu_gate _stwuct = {					\
		.enabwe	= _gate,					\
		.common	= {						\
			.weg		= _weg,				\
			.pwediv		= _pwediv,			\
			.featuwes	= CCU_FEATUWE_AWW_PWEDIV,	\
			.hw.init	= CWK_HW_INIT_PAWENTS_DATA(_name, \
								   _pawent, \
								   &ccu_gate_ops, \
								   _fwags), \
		}							\
	}

static inwine stwuct ccu_gate *hw_to_ccu_gate(stwuct cwk_hw *hw)
{
	stwuct ccu_common *common = hw_to_ccu_common(hw);

	wetuwn containew_of(common, stwuct ccu_gate, common);
}

void ccu_gate_hewpew_disabwe(stwuct ccu_common *common, u32 gate);
int ccu_gate_hewpew_enabwe(stwuct ccu_common *common, u32 gate);
int ccu_gate_hewpew_is_enabwed(stwuct ccu_common *common, u32 gate);

extewn const stwuct cwk_ops ccu_gate_ops;

#endif /* _CCU_GATE_H_ */
