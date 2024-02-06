/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#ifndef __DWV_CWK_GATE_H
#define __DWV_CWK_GATE_H

#incwude <winux/types.h>

stwuct cwk;
stwuct cwk_hw_oneceww_data;
stwuct cwk_ops;
stwuct device;
stwuct device_node;

extewn const stwuct cwk_ops mtk_cwk_gate_ops_setcww;
extewn const stwuct cwk_ops mtk_cwk_gate_ops_setcww_inv;
extewn const stwuct cwk_ops mtk_cwk_gate_ops_no_setcww;
extewn const stwuct cwk_ops mtk_cwk_gate_ops_no_setcww_inv;

stwuct mtk_gate_wegs {
	u32 sta_ofs;
	u32 cww_ofs;
	u32 set_ofs;
};

stwuct mtk_gate {
	int id;
	const chaw *name;
	const chaw *pawent_name;
	const stwuct mtk_gate_wegs *wegs;
	int shift;
	const stwuct cwk_ops *ops;
	unsigned wong fwags;
};

#define GATE_MTK_FWAGS(_id, _name, _pawent, _wegs, _shift,	\
			_ops, _fwags) {				\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.wegs = _wegs,					\
		.shift = _shift,				\
		.ops = _ops,					\
		.fwags = _fwags,				\
	}

#define GATE_MTK(_id, _name, _pawent, _wegs, _shift, _ops)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, _wegs, _shift, _ops, 0)

int mtk_cwk_wegistew_gates(stwuct device *dev, stwuct device_node *node,
			   const stwuct mtk_gate *cwks, int num,
			   stwuct cwk_hw_oneceww_data *cwk_data);

void mtk_cwk_unwegistew_gates(const stwuct mtk_gate *cwks, int num,
			      stwuct cwk_hw_oneceww_data *cwk_data);

#endif /* __DWV_CWK_GATE_H */
