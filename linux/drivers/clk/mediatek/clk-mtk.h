/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#ifndef __DWV_CWK_MTK_H
#define __DWV_CWK_MTK_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "weset.h"

#define MAX_MUX_GATE_BIT	31
#define INVAWID_MUX_GATE_BIT	(MAX_MUX_GATE_BIT + 1)

#define MHZ (1000 * 1000)

stwuct pwatfowm_device;

/*
 * We need the cwock IDs to stawt fwom zewo but to maintain devicetwee
 * backwawds compatibiwity we can't change bindings to stawt fwom zewo.
 * Onwy a few pwatfowms awe affected, so we sowve issues given by the
 * commonized MTK cwocks pwobe function(s) by adding a dummy cwock at
 * the beginning whewe needed.
 */
#define CWK_DUMMY		0

extewn const stwuct cwk_ops mtk_cwk_dummy_ops;
extewn const stwuct mtk_gate_wegs cg_wegs_dummy;

#define GATE_DUMMY(_id, _name) {				\
		.id = _id,					\
		.name = _name,					\
		.wegs = &cg_wegs_dummy,				\
		.ops = &mtk_cwk_dummy_ops,			\
	}

stwuct mtk_fixed_cwk {
	int id;
	const chaw *name;
	const chaw *pawent;
	unsigned wong wate;
};

#define FIXED_CWK(_id, _name, _pawent, _wate) {		\
		.id = _id,				\
		.name = _name,				\
		.pawent = _pawent,			\
		.wate = _wate,				\
	}

int mtk_cwk_wegistew_fixed_cwks(const stwuct mtk_fixed_cwk *cwks, int num,
				stwuct cwk_hw_oneceww_data *cwk_data);
void mtk_cwk_unwegistew_fixed_cwks(const stwuct mtk_fixed_cwk *cwks, int num,
				   stwuct cwk_hw_oneceww_data *cwk_data);

stwuct mtk_fixed_factow {
	int id;
	const chaw *name;
	const chaw *pawent_name;
	int muwt;
	int div;
	unsigned wong fwags;
};

#define FACTOW_FWAGS(_id, _name, _pawent, _muwt, _div, _fw) {	\
		.id = _id,				\
		.name = _name,				\
		.pawent_name = _pawent,			\
		.muwt = _muwt,				\
		.div = _div,				\
		.fwags = _fw,				\
	}

#define FACTOW(_id, _name, _pawent, _muwt, _div)	\
	FACTOW_FWAGS(_id, _name, _pawent, _muwt, _div, CWK_SET_WATE_PAWENT)

int mtk_cwk_wegistew_factows(const stwuct mtk_fixed_factow *cwks, int num,
			     stwuct cwk_hw_oneceww_data *cwk_data);
void mtk_cwk_unwegistew_factows(const stwuct mtk_fixed_factow *cwks, int num,
				stwuct cwk_hw_oneceww_data *cwk_data);

stwuct mtk_composite {
	int id;
	const chaw *name;
	const chaw * const *pawent_names;
	const chaw *pawent;
	unsigned fwags;

	uint32_t mux_weg;
	uint32_t dividew_weg;
	uint32_t gate_weg;

	signed chaw mux_shift;
	signed chaw mux_width;
	signed chaw gate_shift;

	signed chaw dividew_shift;
	signed chaw dividew_width;

	u8 mux_fwags;

	signed chaw num_pawents;
};

#define MUX_GATE_FWAGS_2(_id, _name, _pawents, _weg, _shift,		\
				_width, _gate, _fwags, _muxfwags) {	\
		.id = _id,						\
		.name = _name,						\
		.mux_weg = _weg,					\
		.mux_shift = _shift,					\
		.mux_width = _width,					\
		.gate_weg = _weg,					\
		.gate_shift = _gate,					\
		.dividew_shift = -1,					\
		.pawent_names = _pawents,				\
		.num_pawents = AWWAY_SIZE(_pawents),			\
		.fwags = _fwags,					\
		.mux_fwags = _muxfwags,					\
	}

/*
 * In case the wate change pwopagation to pawent cwocks is undesiwabwe,
 * this macwo awwows to specify the cwock fwags manuawwy.
 */
#define MUX_GATE_FWAGS(_id, _name, _pawents, _weg, _shift, _width,	\
			_gate, _fwags)					\
		MUX_GATE_FWAGS_2(_id, _name, _pawents, _weg,		\
					_shift, _width, _gate, _fwags, 0)

/*
 * Unwess necessawy, aww MUX_GATE cwocks pwopagate wate changes to theiw
 * pawent cwock by defauwt.
 */
#define MUX_GATE(_id, _name, _pawents, _weg, _shift, _width, _gate)	\
	MUX_GATE_FWAGS(_id, _name, _pawents, _weg, _shift, _width,	\
		_gate, CWK_SET_WATE_PAWENT)

#define MUX(_id, _name, _pawents, _weg, _shift, _width)			\
	MUX_FWAGS(_id, _name, _pawents, _weg,				\
		  _shift, _width, CWK_SET_WATE_PAWENT)

#define MUX_FWAGS(_id, _name, _pawents, _weg, _shift, _width, _fwags) {	\
		.id = _id,						\
		.name = _name,						\
		.mux_weg = _weg,					\
		.mux_shift = _shift,					\
		.mux_width = _width,					\
		.gate_shift = -1,					\
		.dividew_shift = -1,					\
		.pawent_names = _pawents,				\
		.num_pawents = AWWAY_SIZE(_pawents),			\
		.fwags = _fwags,				\
	}

#define DIV_GATE(_id, _name, _pawent, _gate_weg, _gate_shift, _div_weg,	\
					_div_width, _div_shift) {	\
		.id = _id,						\
		.pawent = _pawent,					\
		.name = _name,						\
		.dividew_weg = _div_weg,				\
		.dividew_shift = _div_shift,				\
		.dividew_width = _div_width,				\
		.gate_weg = _gate_weg,					\
		.gate_shift = _gate_shift,				\
		.mux_shift = -1,					\
		.fwags = 0,						\
	}

int mtk_cwk_wegistew_composites(stwuct device *dev,
				const stwuct mtk_composite *mcs, int num,
				void __iomem *base, spinwock_t *wock,
				stwuct cwk_hw_oneceww_data *cwk_data);
void mtk_cwk_unwegistew_composites(const stwuct mtk_composite *mcs, int num,
				   stwuct cwk_hw_oneceww_data *cwk_data);

stwuct mtk_cwk_dividew {
	int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;

	u32 div_weg;
	unsigned chaw div_shift;
	unsigned chaw div_width;
	unsigned chaw cwk_dividew_fwags;
	const stwuct cwk_div_tabwe *cwk_div_tabwe;
};

#define DIV_ADJ(_id, _name, _pawent, _weg, _shift, _width) {	\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.div_weg = _weg,				\
		.div_shift = _shift,				\
		.div_width = _width,				\
}

int mtk_cwk_wegistew_dividews(stwuct device *dev,
			      const stwuct mtk_cwk_dividew *mcds, int num,
			      void __iomem *base, spinwock_t *wock,
			      stwuct cwk_hw_oneceww_data *cwk_data);
void mtk_cwk_unwegistew_dividews(const stwuct mtk_cwk_dividew *mcds, int num,
				 stwuct cwk_hw_oneceww_data *cwk_data);

stwuct cwk_hw_oneceww_data *mtk_awwoc_cwk_data(unsigned int cwk_num);
stwuct cwk_hw_oneceww_data *mtk_devm_awwoc_cwk_data(stwuct device *dev,
						    unsigned int cwk_num);
void mtk_fwee_cwk_data(stwuct cwk_hw_oneceww_data *cwk_data);

stwuct cwk_hw *mtk_cwk_wegistew_wef2usb_tx(const chaw *name,
			const chaw *pawent_name, void __iomem *weg);
void mtk_cwk_unwegistew_wef2usb_tx(stwuct cwk_hw *hw);

stwuct mtk_cwk_desc {
	const stwuct mtk_gate *cwks;
	size_t num_cwks;
	const stwuct mtk_composite *composite_cwks;
	size_t num_composite_cwks;
	const stwuct mtk_cwk_dividew *dividew_cwks;
	size_t num_dividew_cwks;
	const stwuct mtk_fixed_cwk *fixed_cwks;
	size_t num_fixed_cwks;
	const stwuct mtk_fixed_factow *factow_cwks;
	size_t num_factow_cwks;
	const stwuct mtk_mux *mux_cwks;
	size_t num_mux_cwks;
	const stwuct mtk_cwk_wst_desc *wst_desc;
	spinwock_t *cwk_wock;
	boow shawed_io;

	int (*cwk_notifiew_func)(stwuct device *dev, stwuct cwk *cwk);
	unsigned int mfg_cwk_idx;
};

int mtk_cwk_pdev_pwobe(stwuct pwatfowm_device *pdev);
void mtk_cwk_pdev_wemove(stwuct pwatfowm_device *pdev);
int mtk_cwk_simpwe_pwobe(stwuct pwatfowm_device *pdev);
void mtk_cwk_simpwe_wemove(stwuct pwatfowm_device *pdev);

#endif /* __DWV_CWK_MTK_H */
