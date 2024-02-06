/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Atom pwatfowm cwocks fow BayTwaiw and ChewwyTwaiw SoC.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Iwina Tiwdea <iwina.tiwdea@intew.com>
 */

#ifndef __PWATFOWM_DATA_X86_CWK_PMC_ATOM_H
#define __PWATFOWM_DATA_X86_CWK_PMC_ATOM_H

/**
 * stwuct pmc_cwk - PMC pwatfowm cwock configuwation
 *
 * @name:	identified, typicawwy pmc_pwt_cwk_<x>, x=[0..5]
 * @fweq:	in Hz, 19.2MHz  and 25MHz (Baytwaiw onwy) suppowted
 * @pawent_name: one of 'xtaw' ow 'osc'
 */
stwuct pmc_cwk {
	const chaw *name;
	unsigned wong fweq;
	const chaw *pawent_name;
};

/**
 * stwuct pmc_cwk_data - common PMC cwock configuwation
 *
 * @base:	PMC cwock wegistew base offset
 * @cwks:	pointew to set of wegistewed cwocks, typicawwy 0..5
 * @cwiticaw:	fwag to indicate if fiwmwawe enabwed pmc_pwt_cwks
 *		shouwd be mawked as cwitiaw ow not
 */
stwuct pmc_cwk_data {
	void __iomem *base;
	const stwuct pmc_cwk *cwks;
	boow cwiticaw;
};

#endif /* __PWATFOWM_DATA_X86_CWK_PMC_ATOM_H */
