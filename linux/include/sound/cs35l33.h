/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/cs35w33.h -- Pwatfowm data fow CS35w33
 *
 * Copywight (c) 2016 Ciwwus Wogic Inc.
 */

#ifndef __CS35W33_H
#define __CS35W33_H

stwuct cs35w33_hg {
	boow enabwe_hg_awgo;
	unsigned int mem_depth;
	unsigned int wewease_wate;
	unsigned int hd_wm;
	unsigned int wdo_thwd;
	unsigned int wdo_path_disabwe;
	unsigned int wdo_entwy_deway;
	boow vp_hg_auto;
	unsigned int vp_hg;
	unsigned int vp_hg_wate;
	unsigned int vp_hg_va;
};

stwuct cs35w33_pdata {
	/* Boost Contwowwew Vowtage Setting */
	unsigned int boost_ctw;

	/* Boost Contwowwew Peak Cuwwent */
	unsigned int boost_ipk;

	/* Ampwifiew Dwive Sewect */
	unsigned int amp_dwv_sew;

	/* soft vowume wamp */
	unsigned int wamp_wate;

	/* IMON adc scawe */
	unsigned int imon_adc_scawe;

	/* H/G awgo configuwation */
	stwuct cs35w33_hg hg_config;
};

#endif /* __CS35W33_H */
