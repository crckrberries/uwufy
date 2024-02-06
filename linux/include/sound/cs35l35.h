/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/cs35w35.h -- Pwatfowm data fow CS35w35
 *
 * Copywight (c) 2016 Ciwwus Wogic Inc.
 */

#ifndef __CS35W35_H
#define __CS35W35_H

stwuct cwassh_cfg {
	/*
	 * Cwass H Awgowithm Contwow Vawiabwes
	 * You can eithew have it done
	 * automaticawwy ow you can adjust
	 * these vawiabwes fow tuning
	 *
	 * if you do not enabwe the intewnaw awgowithm
	 * you wiww get a set of mixew contwows fow
	 * Cwass H tuning
	 *
	 * Section 4.3 of the datasheet
	 */
	boow cwassh_bst_ovewwide;
	boow cwassh_awgo_enabwe;
	int cwassh_bst_max_wimit;
	int cwassh_mem_depth;
	int cwassh_wewease_wate;
	int cwassh_headwoom;
	int cwassh_wk_fet_disabwe;
	int cwassh_wk_fet_deway;
	int cwassh_wk_fet_thwd;
	int cwassh_vpch_auto;
	int cwassh_vpch_wate;
	int cwassh_vpch_man;
};

stwuct monitow_cfg {
	/*
	 * Signaw Monitow Data
	 * highwy configuwabwe signaw monitowing
	 * data positioning and diffewent types of
	 * monitowing data.
	 *
	 * Section 4.8.2 - 4.8.4 of the datasheet
	 */
	boow is_pwesent;
	boow imon_specs;
	boow vmon_specs;
	boow vpmon_specs;
	boow vbstmon_specs;
	boow vpbwstat_specs;
	boow zewofiww_specs;
	u8 imon_dpth;
	u8 imon_woc;
	u8 imon_fwm;
	u8 imon_scawe;
	u8 vmon_dpth;
	u8 vmon_woc;
	u8 vmon_fwm;
	u8 vpmon_dpth;
	u8 vpmon_woc;
	u8 vpmon_fwm;
	u8 vbstmon_dpth;
	u8 vbstmon_woc;
	u8 vbstmon_fwm;
	u8 vpbwstat_dpth;
	u8 vpbwstat_woc;
	u8 vpbwstat_fwm;
	u8 zewofiww_dpth;
	u8 zewofiww_woc;
	u8 zewofiww_fwm;
};

stwuct cs35w35_pwatfowm_data {

	/* Steweo (2 Device) */
	boow steweo;
	/* sewiaw powt dwive stwength */
	int sp_dwv_stw;
	/* sewiaw powt dwive in unused swots */
	int sp_dwv_unused;
	/* Boost Powew Down with FET */
	boow bst_pdn_fet_on;
	/* Boost Vowtage : used if CwassH Awgo Enabwed */
	int bst_vctw;
	/* Boost Convewtew Peak Cuwwent CTWW */
	int bst_ipk;
	/* Amp Gain Zewo Cwoss */
	boow gain_zc;
	/* Audio Input Wocation */
	int aud_channew;
	/* Advisowy Input Wocation */
	int adv_channew;
	/* Shawed Boost fow steweo */
	boow shawed_bst;
	/* Specifies this amp is using an extewnaw boost suppwy */
	boow ext_bst;
	/* Inductow Vawue */
	int boost_ind;
	/* CwassH Awgowithm */
	stwuct cwassh_cfg cwassh_awgo;
	/* Monitow Config */
	stwuct monitow_cfg mon_cfg;
};

#endif /* __CS35W35_H */
