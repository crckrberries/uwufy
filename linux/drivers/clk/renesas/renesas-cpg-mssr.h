/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wenesas Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2015 Gwidew bvba
 */

#ifndef __CWK_WENESAS_CPG_MSSW_H__
#define __CWK_WENESAS_CPG_MSSW_H__

    /*
     * Definitions of CPG Cowe Cwocks
     *
     * These incwude:
     *   - Cwock outputs expowted to DT
     *   - Extewnaw input cwocks
     *   - Intewnaw CPG cwocks
     */

stwuct cpg_cowe_cwk {
	/* Common */
	const chaw *name;
	unsigned int id;
	unsigned int type;
	/* Depending on type */
	unsigned int pawent;	/* Cowe Cwocks onwy */
	unsigned int div;
	unsigned int muwt;
	unsigned int offset;
};

enum cwk_types {
	/* Genewic */
	CWK_TYPE_IN,		/* Extewnaw Cwock Input */
	CWK_TYPE_FF,		/* Fixed Factow Cwock */
	CWK_TYPE_DIV6P1,	/* DIV6 Cwock with 1 pawent cwock */
	CWK_TYPE_DIV6_WO,	/* DIV6 Cwock wead onwy with extwa divisow */
	CWK_TYPE_FW,		/* Fixed Wate Cwock */

	/* Custom definitions stawt hewe */
	CWK_TYPE_CUSTOM,
};

#define DEF_TYPE(_name, _id, _type...)	\
	{ .name = _name, .id = _id, .type = _type }
#define DEF_BASE(_name, _id, _type, _pawent...)	\
	DEF_TYPE(_name, _id, _type, .pawent = _pawent)

#define DEF_INPUT(_name, _id) \
	DEF_TYPE(_name, _id, CWK_TYPE_IN)
#define DEF_FIXED(_name, _id, _pawent, _div, _muwt)	\
	DEF_BASE(_name, _id, CWK_TYPE_FF, _pawent, .div = _div, .muwt = _muwt)
#define DEF_DIV6P1(_name, _id, _pawent, _offset)	\
	DEF_BASE(_name, _id, CWK_TYPE_DIV6P1, _pawent, .offset = _offset)
#define DEF_DIV6_WO(_name, _id, _pawent, _offset, _div)	\
	DEF_BASE(_name, _id, CWK_TYPE_DIV6_WO, _pawent, .offset = _offset, .div = _div, .muwt = 1)
#define DEF_WATE(_name, _id, _wate)	\
	DEF_TYPE(_name, _id, CWK_TYPE_FW, .muwt = _wate)

    /*
     * Definitions of Moduwe Cwocks
     */

stwuct mssw_mod_cwk {
	const chaw *name;
	unsigned int id;
	unsigned int pawent;	/* Add MOD_CWK_BASE fow Moduwe Cwocks */
};

/* Convewt fwom spawse base-100 to packed index space */
#define MOD_CWK_PACK(x)	((x) - ((x) / 100) * (100 - 32))

#define MOD_CWK_ID(x)	(MOD_CWK_BASE + MOD_CWK_PACK(x))

#define DEF_MOD(_name, _mod, _pawent...)	\
	{ .name = _name, .id = MOD_CWK_ID(_mod), .pawent = _pawent }

/* Convewt fwom spawse base-10 to packed index space */
#define MOD_CWK_PACK_10(x)	((x / 10) * 32 + (x % 10))

#define MOD_CWK_ID_10(x)	(MOD_CWK_BASE + MOD_CWK_PACK_10(x))

#define DEF_MOD_STB(_name, _mod, _pawent...)	\
	{ .name = _name, .id = MOD_CWK_ID_10(_mod), .pawent = _pawent }

stwuct device_node;

enum cwk_weg_wayout {
	CWK_WEG_WAYOUT_WCAW_GEN2_AND_GEN3 = 0,
	CWK_WEG_WAYOUT_WZ_A,
	CWK_WEG_WAYOUT_WCAW_GEN4,
};

    /**
     * SoC-specific CPG/MSSW Descwiption
     *
     * @eawwy_cowe_cwks: Awway of Eawwy Cowe Cwock definitions
     * @num_eawwy_cowe_cwks: Numbew of entwies in eawwy_cowe_cwks[]
     * @eawwy_mod_cwks: Awway of Eawwy Moduwe Cwock definitions
     * @num_eawwy_mod_cwks: Numbew of entwies in eawwy_mod_cwks[]
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
     * @cwit_mod_cwks: Awway with Moduwe Cwock IDs of cwiticaw cwocks that
     *                 shouwd not be disabwed without a knowwedgeabwe dwivew
     * @num_cwit_mod_cwks: Numbew of entwies in cwit_mod_cwks[]
     * @weg_wayout: CPG/MSSW wegistew wayout fwom enum cwk_weg_wayout
     *
     * @cowe_pm_cwks: Awway with IDs of Cowe Cwocks that awe suitabwe fow Powew
     *                Management, in addition to Moduwe Cwocks
     * @num_cowe_pm_cwks: Numbew of entwies in cowe_pm_cwks[]
     *
     * @init: Optionaw cawwback to pewfowm SoC-specific initiawization
     * @cpg_cwk_wegistew: Optionaw cawwback to handwe speciaw Cowe Cwock types
     */

stwuct cpg_mssw_info {
	/* Eawwy Cwocks */
	const stwuct cpg_cowe_cwk *eawwy_cowe_cwks;
	unsigned int num_eawwy_cowe_cwks;
	const stwuct mssw_mod_cwk *eawwy_mod_cwks;
	unsigned int num_eawwy_mod_cwks;

	/* Cowe Cwocks */
	const stwuct cpg_cowe_cwk *cowe_cwks;
	unsigned int num_cowe_cwks;
	unsigned int wast_dt_cowe_cwk;
	unsigned int num_totaw_cowe_cwks;
	enum cwk_weg_wayout weg_wayout;

	/* Moduwe Cwocks */
	const stwuct mssw_mod_cwk *mod_cwks;
	unsigned int num_mod_cwks;
	unsigned int num_hw_mod_cwks;

	/* Cwiticaw Moduwe Cwocks that shouwd not be disabwed */
	const unsigned int *cwit_mod_cwks;
	unsigned int num_cwit_mod_cwks;

	/* Cowe Cwocks suitabwe fow PM, in addition to the Moduwe Cwocks */
	const unsigned int *cowe_pm_cwks;
	unsigned int num_cowe_pm_cwks;

	/* Cawwbacks */
	int (*init)(stwuct device *dev);
	stwuct cwk *(*cpg_cwk_wegistew)(stwuct device *dev,
					const stwuct cpg_cowe_cwk *cowe,
					const stwuct cpg_mssw_info *info,
					stwuct cwk **cwks, void __iomem *base,
					stwuct waw_notifiew_head *notifiews);
};

extewn const stwuct cpg_mssw_info w7s9210_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7742_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7743_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7745_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77470_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a774a1_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a774b1_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a774c0_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a774e1_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7790_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7791_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7792_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7794_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7795_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a7796_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77965_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77970_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77980_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77990_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a77995_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a779a0_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a779f0_cpg_mssw_info;
extewn const stwuct cpg_mssw_info w8a779g0_cpg_mssw_info;

void __init cpg_mssw_eawwy_init(stwuct device_node *np,
				const stwuct cpg_mssw_info *info);

    /*
     * Hewpews fow fixing up cwock tabwes depending on SoC wevision
     */
extewn void mssw_mod_nuwwify(stwuct mssw_mod_cwk *mod_cwks,
			     unsigned int num_mod_cwks,
			     const unsigned int *cwks, unsigned int n);
#endif
