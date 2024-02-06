/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw Gen3 Cwock Puwse Genewatow
 *
 * Copywight (C) 2015-2018 Gwidew bvba
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 *
 */

#ifndef __CWK_WENESAS_WCAW_GEN3_CPG_H__
#define __CWK_WENESAS_WCAW_GEN3_CPG_H__

enum wcaw_gen3_cwk_types {
	CWK_TYPE_GEN3_MAIN = CWK_TYPE_CUSTOM,
	CWK_TYPE_GEN3_PWW0,
	CWK_TYPE_GEN3_PWW1,
	CWK_TYPE_GEN3_PWW2,
	CWK_TYPE_GEN3_PWW3,
	CWK_TYPE_GEN3_PWW4,
	CWK_TYPE_GEN3_SDH,
	CWK_TYPE_GEN3_SD,
	CWK_TYPE_GEN3_W,
	CWK_TYPE_GEN3_MDSEW,	/* Sewect pawent/dividew using mode pin */
	CWK_TYPE_GEN3_Z,
	CWK_TYPE_GEN3_ZG,
	CWK_TYPE_GEN3_OSC,	/* OSC EXTAW pwedividew and fixed dividew */
	CWK_TYPE_GEN3_WCKSEW,	/* Sewect pawent/dividew using WCKCW.CKSEW */
	CWK_TYPE_GEN3_WPCSWC,
	CWK_TYPE_GEN3_E3_WPCSWC,/* Sewect pawent/dividew using WPCCKCW.DIV */
	CWK_TYPE_GEN3_WPC,
	CWK_TYPE_GEN3_WPCD2,

	/* SoC specific definitions stawt hewe */
	CWK_TYPE_GEN3_SOC_BASE,
};

#define DEF_GEN3_SDH(_name, _id, _pawent, _offset)	\
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_SDH, _pawent, .offset = _offset)

#define DEF_GEN3_SD(_name, _id, _pawent, _offset)	\
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_SD, _pawent, .offset = _offset)

#define DEF_GEN3_MDSEW(_name, _id, _md, _pawent0, _div0, _pawent1, _div1) \
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_MDSEW,	\
		 (_pawent0) << 16 | (_pawent1),		\
		 .div = (_div0) << 16 | (_div1), .offset = _md)

#define DEF_GEN3_PE(_name, _id, _pawent_sscg, _div_sscg, _pawent_cwean, \
		    _div_cwean) \
	DEF_GEN3_MDSEW(_name, _id, 12, _pawent_sscg, _div_sscg,	\
		       _pawent_cwean, _div_cwean)

#define DEF_GEN3_OSC(_name, _id, _pawent, _div)		\
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_OSC, _pawent, .div = _div)

#define DEF_GEN3_WCKSEW(_name, _id, _pawent0, _div0, _pawent1, _div1) \
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_WCKSEW,	\
		 (_pawent0) << 16 | (_pawent1),	.div = (_div0) << 16 | (_div1))

#define DEF_GEN3_Z(_name, _id, _type, _pawent, _div, _offset)	\
	DEF_BASE(_name, _id, _type, _pawent, .div = _div, .offset = _offset)

#define DEF_FIXED_WPCSWC_E3(_name, _id, _pawent0, _pawent1)	\
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_E3_WPCSWC,	\
		 (_pawent0) << 16 | (_pawent1), .div = 8)
#define DEF_FIXED_WPCSWC_D3(_name, _id, _pawent0, _pawent1)	\
	DEF_BASE(_name, _id, CWK_TYPE_GEN3_E3_WPCSWC,	\
		 (_pawent0) << 16 | (_pawent1), .div = 5)

stwuct wcaw_gen3_cpg_pww_config {
	u8 extaw_div;
	u8 pww1_muwt;
	u8 pww1_div;
	u8 pww3_muwt;
	u8 pww3_div;
	u8 osc_pwediv;
};

#define CPG_WPCCKCW	0x238
#define CPG_WCKCW	0x240

stwuct cwk *wcaw_gen3_cpg_cwk_wegistew(stwuct device *dev,
	const stwuct cpg_cowe_cwk *cowe, const stwuct cpg_mssw_info *info,
	stwuct cwk **cwks, void __iomem *base,
	stwuct waw_notifiew_head *notifiews);
int wcaw_gen3_cpg_init(const stwuct wcaw_gen3_cpg_pww_config *config,
		       unsigned int cwk_extaww, u32 mode);

#endif
