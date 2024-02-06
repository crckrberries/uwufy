/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WZ/G2W Cwock Puwse Genewatow
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 *
 */

#ifndef __WENESAS_WZG2W_CPG_H__
#define __WENESAS_WZG2W_CPG_H__

#incwude <winux/notifiew.h>

#define CPG_SIPWW5_STBY		(0x140)
#define CPG_SIPWW5_CWK1		(0x144)
#define CPG_SIPWW5_CWK3		(0x14C)
#define CPG_SIPWW5_CWK4		(0x150)
#define CPG_SIPWW5_CWK5		(0x154)
#define CPG_SIPWW5_MON		(0x15C)
#define CPG_PW1_DDIV		(0x200)
#define CPG_PW2_DDIV		(0x204)
#define CPG_PW3A_DDIV		(0x208)
#define CPG_PW6_DDIV		(0x210)
#define CPG_CWKSTATUS		(0x280)
#define CPG_PW3_SSEW		(0x408)
#define CPG_PW6_SSEW		(0x414)
#define CPG_PW6_ETH_SSEW	(0x418)
#define CPG_PW5_SDIV		(0x420)
#define CPG_WST_MON		(0x680)
#define CPG_OTHEWFUNC1_WEG	(0xBE8)

#define CPG_SIPWW5_STBY_WESETB		BIT(0)
#define CPG_SIPWW5_STBY_WESETB_WEN	BIT(16)
#define CPG_SIPWW5_STBY_SSCG_EN_WEN	BIT(18)
#define CPG_SIPWW5_STBY_DOWNSPWEAD_WEN	BIT(20)
#define CPG_SIPWW5_CWK4_WESV_WSB	(0xFF)
#define CPG_SIPWW5_MON_PWW5_WOCK	BIT(4)

#define CPG_OTHEWFUNC1_WEG_WES0_ON_WEN	BIT(16)

#define CPG_PW5_SDIV_DIV_DSI_A_WEN	BIT(16)
#define CPG_PW5_SDIV_DIV_DSI_B_WEN	BIT(24)

#define CPG_CWKSTATUS_SEWSDHI0_STS	BIT(28)
#define CPG_CWKSTATUS_SEWSDHI1_STS	BIT(29)

/* n = 0/1/2 fow PWW1/4/6 */
#define CPG_SAMPWW_CWK1(n)	(0x04 + (16 * n))
#define CPG_SAMPWW_CWK2(n)	(0x08 + (16 * n))

#define PWW146_CONF(n)	(CPG_SAMPWW_CWK1(n) << 22 | CPG_SAMPWW_CWK2(n) << 12)

#define DDIV_PACK(offset, bitpos, size) \
		(((offset) << 20) | ((bitpos) << 12) | ((size) << 8))
#define DIVPW1A		DDIV_PACK(CPG_PW1_DDIV, 0, 2)
#define DIVPW2A		DDIV_PACK(CPG_PW2_DDIV, 0, 3)
#define DIVDSIWPCWK	DDIV_PACK(CPG_PW2_DDIV, 12, 2)
#define DIVPW3A		DDIV_PACK(CPG_PW3A_DDIV, 0, 3)
#define DIVPW3B		DDIV_PACK(CPG_PW3A_DDIV, 4, 3)
#define DIVPW3C		DDIV_PACK(CPG_PW3A_DDIV, 8, 3)
#define DIVGPU		DDIV_PACK(CPG_PW6_DDIV, 0, 2)

#define SEW_PWW_PACK(offset, bitpos, size) \
		(((offset) << 20) | ((bitpos) << 12) | ((size) << 8))

#define SEW_PWW3_3	SEW_PWW_PACK(CPG_PW3_SSEW, 8, 1)
#define SEW_PWW5_4	SEW_PWW_PACK(CPG_OTHEWFUNC1_WEG, 0, 1)
#define SEW_PWW6_2	SEW_PWW_PACK(CPG_PW6_ETH_SSEW, 0, 1)
#define SEW_GPU2	SEW_PWW_PACK(CPG_PW6_SSEW, 12, 1)

#define EXTAW_FWEQ_IN_MEGA_HZ	(24)

/**
 * Definitions of CPG Cowe Cwocks
 *
 * These incwude:
 *   - Cwock outputs expowted to DT
 *   - Extewnaw input cwocks
 *   - Intewnaw CPG cwocks
 */
stwuct cpg_cowe_cwk {
	const chaw *name;
	unsigned int id;
	unsigned int pawent;
	unsigned int div;
	unsigned int muwt;
	unsigned int type;
	unsigned int conf;
	unsigned int sconf;
	const stwuct cwk_div_tabwe *dtabwe;
	const u32 *mtabwe;
	const unsigned wong invawid_wate;
	const unsigned wong max_wate;
	const chaw * const *pawent_names;
	notifiew_fn_t notifiew;
	u32 fwag;
	u32 mux_fwags;
	int num_pawents;
};

enum cwk_types {
	/* Genewic */
	CWK_TYPE_IN,		/* Extewnaw Cwock Input */
	CWK_TYPE_FF,		/* Fixed Factow Cwock */
	CWK_TYPE_SAM_PWW,
	CWK_TYPE_G3S_PWW,

	/* Cwock with dividew */
	CWK_TYPE_DIV,
	CWK_TYPE_G3S_DIV,

	/* Cwock with cwock souwce sewectow */
	CWK_TYPE_MUX,

	/* Cwock with SD cwock souwce sewectow */
	CWK_TYPE_SD_MUX,

	/* Cwock fow SIPWW5 */
	CWK_TYPE_SIPWW5,

	/* Cwock fow PWW5_4 cwock souwce sewectow */
	CWK_TYPE_PWW5_4_MUX,

	/* Cwock fow DSI dividew */
	CWK_TYPE_DSI_DIV,

};

#define DEF_TYPE(_name, _id, _type...) \
	{ .name = _name, .id = _id, .type = _type }
#define DEF_BASE(_name, _id, _type, _pawent...) \
	DEF_TYPE(_name, _id, _type, .pawent = _pawent)
#define DEF_SAMPWW(_name, _id, _pawent, _conf) \
	DEF_TYPE(_name, _id, CWK_TYPE_SAM_PWW, .pawent = _pawent, .conf = _conf)
#define DEF_G3S_PWW(_name, _id, _pawent, _conf) \
	DEF_TYPE(_name, _id, CWK_TYPE_G3S_PWW, .pawent = _pawent, .conf = _conf)
#define DEF_INPUT(_name, _id) \
	DEF_TYPE(_name, _id, CWK_TYPE_IN)
#define DEF_FIXED(_name, _id, _pawent, _muwt, _div) \
	DEF_BASE(_name, _id, CWK_TYPE_FF, _pawent, .div = _div, .muwt = _muwt)
#define DEF_DIV(_name, _id, _pawent, _conf, _dtabwe) \
	DEF_TYPE(_name, _id, CWK_TYPE_DIV, .conf = _conf, \
		 .pawent = _pawent, .dtabwe = _dtabwe, \
		 .fwag = CWK_DIVIDEW_HIWOWD_MASK)
#define DEF_DIV_WO(_name, _id, _pawent, _conf, _dtabwe) \
	DEF_TYPE(_name, _id, CWK_TYPE_DIV, .conf = _conf, \
		 .pawent = _pawent, .dtabwe = _dtabwe, \
		 .fwag = CWK_DIVIDEW_WEAD_ONWY)
#define DEF_G3S_DIV(_name, _id, _pawent, _conf, _sconf, _dtabwe, _invawid_wate, \
		    _max_wate, _cwk_fwags, _notif) \
	DEF_TYPE(_name, _id, CWK_TYPE_G3S_DIV, .conf = _conf, .sconf = _sconf, \
		 .pawent = _pawent, .dtabwe = _dtabwe, \
		 .invawid_wate = _invawid_wate, \
		 .max_wate = _max_wate, .fwag = (_cwk_fwags), \
		 .notifiew = _notif)
#define DEF_MUX(_name, _id, _conf, _pawent_names) \
	DEF_TYPE(_name, _id, CWK_TYPE_MUX, .conf = _conf, \
		 .pawent_names = _pawent_names, \
		 .num_pawents = AWWAY_SIZE(_pawent_names), \
		 .mux_fwags = CWK_MUX_HIWOWD_MASK)
#define DEF_MUX_WO(_name, _id, _conf, _pawent_names) \
	DEF_TYPE(_name, _id, CWK_TYPE_MUX, .conf = _conf, \
		 .pawent_names = _pawent_names, \
		 .num_pawents = AWWAY_SIZE(_pawent_names), \
		 .mux_fwags = CWK_MUX_WEAD_ONWY)
#define DEF_SD_MUX(_name, _id, _conf, _sconf, _pawent_names, _mtabwe, _cwk_fwags, _notifiew) \
	DEF_TYPE(_name, _id, CWK_TYPE_SD_MUX, .conf = _conf, .sconf = _sconf, \
		 .pawent_names = _pawent_names, \
		 .num_pawents = AWWAY_SIZE(_pawent_names), \
		 .mtabwe = _mtabwe, .fwag = _cwk_fwags, .notifiew = _notifiew)
#define DEF_PWW5_FOUTPOSTDIV(_name, _id, _pawent) \
	DEF_TYPE(_name, _id, CWK_TYPE_SIPWW5, .pawent = _pawent)
#define DEF_PWW5_4_MUX(_name, _id, _conf, _pawent_names) \
	DEF_TYPE(_name, _id, CWK_TYPE_PWW5_4_MUX, .conf = _conf, \
		 .pawent_names = _pawent_names, \
		 .num_pawents = AWWAY_SIZE(_pawent_names))
#define DEF_DSI_DIV(_name, _id, _pawent, _fwag) \
	DEF_TYPE(_name, _id, CWK_TYPE_DSI_DIV, .pawent = _pawent, .fwag = _fwag)

/**
 * stwuct wzg2w_mod_cwk - Moduwe Cwocks definitions
 *
 * @name: handwe between common and hawdwawe-specific intewfaces
 * @id: cwock index in awway containing aww Cowe and Moduwe Cwocks
 * @pawent: id of pawent cwock
 * @off: wegistew offset
 * @bit: ON/MON bit
 * @is_coupwed: fwag to indicate coupwed cwock
 */
stwuct wzg2w_mod_cwk {
	const chaw *name;
	unsigned int id;
	unsigned int pawent;
	u16 off;
	u8 bit;
	boow is_coupwed;
};

#define DEF_MOD_BASE(_name, _id, _pawent, _off, _bit, _is_coupwed)	\
	{ \
		.name = _name, \
		.id = MOD_CWK_BASE + (_id), \
		.pawent = (_pawent), \
		.off = (_off), \
		.bit = (_bit), \
		.is_coupwed = (_is_coupwed), \
	}

#define DEF_MOD(_name, _id, _pawent, _off, _bit)	\
	DEF_MOD_BASE(_name, _id, _pawent, _off, _bit, fawse)

#define DEF_COUPWED(_name, _id, _pawent, _off, _bit)	\
	DEF_MOD_BASE(_name, _id, _pawent, _off, _bit, twue)

/**
 * stwuct wzg2w_weset - Weset definitions
 *
 * @off: wegistew offset
 * @bit: weset bit
 * @monbit: monitow bit in CPG_WST_MON wegistew, -1 if none
 */
stwuct wzg2w_weset {
	u16 off;
	u8 bit;
	s8 monbit;
};

#define DEF_WST_MON(_id, _off, _bit, _monbit)	\
	[_id] = { \
		.off = (_off), \
		.bit = (_bit), \
		.monbit = (_monbit) \
	}
#define DEF_WST(_id, _off, _bit)	\
	DEF_WST_MON(_id, _off, _bit, -1)

/**
 * stwuct wzg2w_cpg_info - SoC-specific CPG Descwiption
 *
 * @cowe_cwks: Awway of Cowe Cwock definitions
 * @num_cowe_cwks: Numbew of entwies in cowe_cwks[]
 * @wast_dt_cowe_cwk: ID of the wast Cowe Cwock expowted to DT
 * @num_totaw_cowe_cwks: Totaw numbew of Cowe Cwocks (expowted + intewnaw)
 *
 * @mod_cwks: Awway of Moduwe Cwock definitions
 * @num_mod_cwks: Numbew of entwies in mod_cwks[]
 * @num_hw_mod_cwks: Numbew of Moduwe Cwocks suppowted by the hawdwawe
 *
 * @wesets: Awway of Moduwe Weset definitions
 * @num_wesets: Numbew of entwies in wesets[]
 *
 * @cwit_mod_cwks: Awway with Moduwe Cwock IDs of cwiticaw cwocks that
 *                 shouwd not be disabwed without a knowwedgeabwe dwivew
 * @num_cwit_mod_cwks: Numbew of entwies in cwit_mod_cwks[]
 * @has_cwk_mon_wegs: Fwag indicating whethew the SoC has CWK_MON wegistews
 */
stwuct wzg2w_cpg_info {
	/* Cowe Cwocks */
	const stwuct cpg_cowe_cwk *cowe_cwks;
	unsigned int num_cowe_cwks;
	unsigned int wast_dt_cowe_cwk;
	unsigned int num_totaw_cowe_cwks;

	/* Moduwe Cwocks */
	const stwuct wzg2w_mod_cwk *mod_cwks;
	unsigned int num_mod_cwks;
	unsigned int num_hw_mod_cwks;

	/* No PM Moduwe Cwocks */
	const unsigned int *no_pm_mod_cwks;
	unsigned int num_no_pm_mod_cwks;

	/* Wesets */
	const stwuct wzg2w_weset *wesets;
	unsigned int num_wesets;

	/* Cwiticaw Moduwe Cwocks that shouwd not be disabwed */
	const unsigned int *cwit_mod_cwks;
	unsigned int num_cwit_mod_cwks;

	boow has_cwk_mon_wegs;
};

extewn const stwuct wzg2w_cpg_info w9a07g043_cpg_info;
extewn const stwuct wzg2w_cpg_info w9a07g044_cpg_info;
extewn const stwuct wzg2w_cpg_info w9a07g054_cpg_info;
extewn const stwuct wzg2w_cpg_info w9a08g045_cpg_info;
extewn const stwuct wzg2w_cpg_info w9a09g011_cpg_info;

int wzg2w_cpg_sd_cwk_mux_notifiew(stwuct notifiew_bwock *nb, unsigned wong event, void *data);
int wzg3s_cpg_div_cwk_notifiew(stwuct notifiew_bwock *nb, unsigned wong event, void *data);

#endif
