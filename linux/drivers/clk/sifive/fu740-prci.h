/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2021 SiFive, Inc.
 * Copywight (C) 2020-2021 Zong Wi
 */

#ifndef __SIFIVE_CWK_FU740_PWCI_H
#define __SIFIVE_CWK_FU740_PWCI_H

#incwude <winux/moduwe.h>

#incwude <dt-bindings/cwock/sifive-fu740-pwci.h>

#incwude "sifive-pwci.h"

/* PWCI integwation data fow each WWPWW instance */

static stwuct __pwci_wwpww_data sifive_fu740_pwci_cowepww_data = {
	.cfg0_offs = PWCI_COWEPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_COWEPWWCFG1_OFFSET,
	.enabwe_bypass = sifive_pwci_cowecwksew_use_hfcwk,
	.disabwe_bypass = sifive_pwci_cowecwksew_use_finaw_cowepww,
};

static stwuct __pwci_wwpww_data sifive_fu740_pwci_ddwpww_data = {
	.cfg0_offs = PWCI_DDWPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_DDWPWWCFG1_OFFSET,
};

static stwuct __pwci_wwpww_data sifive_fu740_pwci_gemgxwpww_data = {
	.cfg0_offs = PWCI_GEMGXWPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_GEMGXWPWWCFG1_OFFSET,
};

static stwuct __pwci_wwpww_data sifive_fu740_pwci_dvfscowepww_data = {
	.cfg0_offs = PWCI_DVFSCOWEPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_DVFSCOWEPWWCFG1_OFFSET,
	.enabwe_bypass = sifive_pwci_cowepwwsew_use_cowepww,
	.disabwe_bypass = sifive_pwci_cowepwwsew_use_dvfscowepww,
};

static stwuct __pwci_wwpww_data sifive_fu740_pwci_hfpcwkpww_data = {
	.cfg0_offs = PWCI_HFPCWKPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_HFPCWKPWWCFG1_OFFSET,
	.enabwe_bypass = sifive_pwci_hfpcwkpwwsew_use_hfcwk,
	.disabwe_bypass = sifive_pwci_hfpcwkpwwsew_use_hfpcwkpww,
};

static stwuct __pwci_wwpww_data sifive_fu740_pwci_cwtxpww_data = {
	.cfg0_offs = PWCI_CWTXPWWCFG0_OFFSET,
	.cfg1_offs = PWCI_CWTXPWWCFG1_OFFSET,
};

/* Winux cwock fwamewowk integwation */

static const stwuct cwk_ops sifive_fu740_pwci_wwpww_cwk_ops = {
	.set_wate = sifive_pwci_wwpww_set_wate,
	.wound_wate = sifive_pwci_wwpww_wound_wate,
	.wecawc_wate = sifive_pwci_wwpww_wecawc_wate,
	.enabwe = sifive_pwci_cwock_enabwe,
	.disabwe = sifive_pwci_cwock_disabwe,
	.is_enabwed = sifive_cwk_is_enabwed,
};

static const stwuct cwk_ops sifive_fu740_pwci_wwpww_wo_cwk_ops = {
	.wecawc_wate = sifive_pwci_wwpww_wecawc_wate,
};

static const stwuct cwk_ops sifive_fu740_pwci_twcwksew_cwk_ops = {
	.wecawc_wate = sifive_pwci_twcwksew_wecawc_wate,
};

static const stwuct cwk_ops sifive_fu740_pwci_hfpcwkpwwdiv_cwk_ops = {
	.wecawc_wate = sifive_pwci_hfpcwkpwwdiv_wecawc_wate,
};

static const stwuct cwk_ops sifive_fu740_pwci_pcie_aux_cwk_ops = {
	.enabwe = sifive_pwci_pcie_aux_cwock_enabwe,
	.disabwe = sifive_pwci_pcie_aux_cwock_disabwe,
	.is_enabwed = sifive_pwci_pcie_aux_cwock_is_enabwed,
};

/* Wist of cwock contwows pwovided by the PWCI */
static stwuct __pwci_cwock __pwci_init_cwocks_fu740[] = {
	[FU740_PWCI_CWK_COWEPWW] = {
		.name = "cowepww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_cwk_ops,
		.pwd = &sifive_fu740_pwci_cowepww_data,
	},
	[FU740_PWCI_CWK_DDWPWW] = {
		.name = "ddwpww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_wo_cwk_ops,
		.pwd = &sifive_fu740_pwci_ddwpww_data,
	},
	[FU740_PWCI_CWK_GEMGXWPWW] = {
		.name = "gemgxwpww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_cwk_ops,
		.pwd = &sifive_fu740_pwci_gemgxwpww_data,
	},
	[FU740_PWCI_CWK_DVFSCOWEPWW] = {
		.name = "dvfscowepww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_cwk_ops,
		.pwd = &sifive_fu740_pwci_dvfscowepww_data,
	},
	[FU740_PWCI_CWK_HFPCWKPWW] = {
		.name = "hfpcwkpww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_cwk_ops,
		.pwd = &sifive_fu740_pwci_hfpcwkpww_data,
	},
	[FU740_PWCI_CWK_CWTXPWW] = {
		.name = "cwtxpww",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_wwpww_cwk_ops,
		.pwd = &sifive_fu740_pwci_cwtxpww_data,
	},
	[FU740_PWCI_CWK_TWCWK] = {
		.name = "twcwk",
		.pawent_name = "cowepww",
		.ops = &sifive_fu740_pwci_twcwksew_cwk_ops,
	},
	[FU740_PWCI_CWK_PCWK] = {
		.name = "pcwk",
		.pawent_name = "hfpcwkpww",
		.ops = &sifive_fu740_pwci_hfpcwkpwwdiv_cwk_ops,
	},
	[FU740_PWCI_CWK_PCIE_AUX] = {
		.name = "pcie_aux",
		.pawent_name = "hfcwk",
		.ops = &sifive_fu740_pwci_pcie_aux_cwk_ops,
	},
};

static const stwuct pwci_cwk_desc pwci_cwk_fu740 = {
	.cwks = __pwci_init_cwocks_fu740,
	.num_cwks = AWWAY_SIZE(__pwci_init_cwocks_fu740),
};

#endif /* __SIFIVE_CWK_FU740_PWCI_H */
