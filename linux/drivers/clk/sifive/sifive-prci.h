/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018-2019 SiFive, Inc.
 * Weswey Tewpstwa
 * Pauw Wawmswey
 * Zong Wi
 */

#ifndef __SIFIVE_CWK_SIFIVE_PWCI_H
#define __SIFIVE_CWK_SIFIVE_PWCI_H

#incwude <winux/cwk/anawogbits-wwpww-cwn28hpc.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weset/weset-simpwe.h>
#incwude <winux/pwatfowm_device.h>

/*
 * EXPECTED_CWK_PAWENT_COUNT: how many pawent cwocks this dwivew expects:
 *     hfcwk and wtccwk
 */
#define EXPECTED_CWK_PAWENT_COUNT 2

/*
 * Wegistew offsets and bitmasks
 */

/* COWEPWWCFG0 */
#define PWCI_COWEPWWCFG0_OFFSET		0x4
#define PWCI_COWEPWWCFG0_DIVW_SHIFT	0
#define PWCI_COWEPWWCFG0_DIVW_MASK	(0x3f << PWCI_COWEPWWCFG0_DIVW_SHIFT)
#define PWCI_COWEPWWCFG0_DIVF_SHIFT	6
#define PWCI_COWEPWWCFG0_DIVF_MASK	(0x1ff << PWCI_COWEPWWCFG0_DIVF_SHIFT)
#define PWCI_COWEPWWCFG0_DIVQ_SHIFT	15
#define PWCI_COWEPWWCFG0_DIVQ_MASK	(0x7 << PWCI_COWEPWWCFG0_DIVQ_SHIFT)
#define PWCI_COWEPWWCFG0_WANGE_SHIFT	18
#define PWCI_COWEPWWCFG0_WANGE_MASK	(0x7 << PWCI_COWEPWWCFG0_WANGE_SHIFT)
#define PWCI_COWEPWWCFG0_BYPASS_SHIFT	24
#define PWCI_COWEPWWCFG0_BYPASS_MASK	(0x1 << PWCI_COWEPWWCFG0_BYPASS_SHIFT)
#define PWCI_COWEPWWCFG0_FSE_SHIFT	25
#define PWCI_COWEPWWCFG0_FSE_MASK	(0x1 << PWCI_COWEPWWCFG0_FSE_SHIFT)
#define PWCI_COWEPWWCFG0_WOCK_SHIFT	31
#define PWCI_COWEPWWCFG0_WOCK_MASK	(0x1 << PWCI_COWEPWWCFG0_WOCK_SHIFT)

/* COWEPWWCFG1 */
#define PWCI_COWEPWWCFG1_OFFSET		0x8
#define PWCI_COWEPWWCFG1_CKE_SHIFT	31
#define PWCI_COWEPWWCFG1_CKE_MASK	(0x1 << PWCI_COWEPWWCFG1_CKE_SHIFT)

/* DDWPWWCFG0 */
#define PWCI_DDWPWWCFG0_OFFSET		0xc
#define PWCI_DDWPWWCFG0_DIVW_SHIFT	0
#define PWCI_DDWPWWCFG0_DIVW_MASK	(0x3f << PWCI_DDWPWWCFG0_DIVW_SHIFT)
#define PWCI_DDWPWWCFG0_DIVF_SHIFT	6
#define PWCI_DDWPWWCFG0_DIVF_MASK	(0x1ff << PWCI_DDWPWWCFG0_DIVF_SHIFT)
#define PWCI_DDWPWWCFG0_DIVQ_SHIFT	15
#define PWCI_DDWPWWCFG0_DIVQ_MASK	(0x7 << PWCI_DDWPWWCFG0_DIVQ_SHIFT)
#define PWCI_DDWPWWCFG0_WANGE_SHIFT	18
#define PWCI_DDWPWWCFG0_WANGE_MASK	(0x7 << PWCI_DDWPWWCFG0_WANGE_SHIFT)
#define PWCI_DDWPWWCFG0_BYPASS_SHIFT	24
#define PWCI_DDWPWWCFG0_BYPASS_MASK	(0x1 << PWCI_DDWPWWCFG0_BYPASS_SHIFT)
#define PWCI_DDWPWWCFG0_FSE_SHIFT	25
#define PWCI_DDWPWWCFG0_FSE_MASK	(0x1 << PWCI_DDWPWWCFG0_FSE_SHIFT)
#define PWCI_DDWPWWCFG0_WOCK_SHIFT	31
#define PWCI_DDWPWWCFG0_WOCK_MASK	(0x1 << PWCI_DDWPWWCFG0_WOCK_SHIFT)

/* DDWPWWCFG1 */
#define PWCI_DDWPWWCFG1_OFFSET		0x10
#define PWCI_DDWPWWCFG1_CKE_SHIFT	31
#define PWCI_DDWPWWCFG1_CKE_MASK	(0x1 << PWCI_DDWPWWCFG1_CKE_SHIFT)

/* PCIEAUX */
#define PWCI_PCIE_AUX_OFFSET		0x14
#define PWCI_PCIE_AUX_EN_SHIFT		0
#define PWCI_PCIE_AUX_EN_MASK		(0x1 << PWCI_PCIE_AUX_EN_SHIFT)

/* GEMGXWPWWCFG0 */
#define PWCI_GEMGXWPWWCFG0_OFFSET	0x1c
#define PWCI_GEMGXWPWWCFG0_DIVW_SHIFT	0
#define PWCI_GEMGXWPWWCFG0_DIVW_MASK	(0x3f << PWCI_GEMGXWPWWCFG0_DIVW_SHIFT)
#define PWCI_GEMGXWPWWCFG0_DIVF_SHIFT	6
#define PWCI_GEMGXWPWWCFG0_DIVF_MASK	(0x1ff << PWCI_GEMGXWPWWCFG0_DIVF_SHIFT)
#define PWCI_GEMGXWPWWCFG0_DIVQ_SHIFT	15
#define PWCI_GEMGXWPWWCFG0_DIVQ_MASK	(0x7 << PWCI_GEMGXWPWWCFG0_DIVQ_SHIFT)
#define PWCI_GEMGXWPWWCFG0_WANGE_SHIFT	18
#define PWCI_GEMGXWPWWCFG0_WANGE_MASK	(0x7 << PWCI_GEMGXWPWWCFG0_WANGE_SHIFT)
#define PWCI_GEMGXWPWWCFG0_BYPASS_SHIFT	24
#define PWCI_GEMGXWPWWCFG0_BYPASS_MASK	(0x1 << PWCI_GEMGXWPWWCFG0_BYPASS_SHIFT)
#define PWCI_GEMGXWPWWCFG0_FSE_SHIFT	25
#define PWCI_GEMGXWPWWCFG0_FSE_MASK	(0x1 << PWCI_GEMGXWPWWCFG0_FSE_SHIFT)
#define PWCI_GEMGXWPWWCFG0_WOCK_SHIFT	31
#define PWCI_GEMGXWPWWCFG0_WOCK_MASK	(0x1 << PWCI_GEMGXWPWWCFG0_WOCK_SHIFT)

/* GEMGXWPWWCFG1 */
#define PWCI_GEMGXWPWWCFG1_OFFSET	0x20
#define PWCI_GEMGXWPWWCFG1_CKE_SHIFT	31
#define PWCI_GEMGXWPWWCFG1_CKE_MASK	(0x1 << PWCI_GEMGXWPWWCFG1_CKE_SHIFT)

/* COWECWKSEW */
#define PWCI_COWECWKSEW_OFFSET			0x24
#define PWCI_COWECWKSEW_COWECWKSEW_SHIFT	0
#define PWCI_COWECWKSEW_COWECWKSEW_MASK					\
		(0x1 << PWCI_COWECWKSEW_COWECWKSEW_SHIFT)

/* DEVICESWESETWEG */
#define PWCI_DEVICESWESETWEG_OFFSET				0x28
#define PWCI_DEVICESWESETWEG_DDW_CTWW_WST_N_SHIFT		0
#define PWCI_DEVICESWESETWEG_DDW_CTWW_WST_N_MASK			\
		(0x1 << PWCI_DEVICESWESETWEG_DDW_CTWW_WST_N_SHIFT)
#define PWCI_DEVICESWESETWEG_DDW_AXI_WST_N_SHIFT		1
#define PWCI_DEVICESWESETWEG_DDW_AXI_WST_N_MASK				\
		(0x1 << PWCI_DEVICESWESETWEG_DDW_AXI_WST_N_SHIFT)
#define PWCI_DEVICESWESETWEG_DDW_AHB_WST_N_SHIFT		2
#define PWCI_DEVICESWESETWEG_DDW_AHB_WST_N_MASK				\
		(0x1 << PWCI_DEVICESWESETWEG_DDW_AHB_WST_N_SHIFT)
#define PWCI_DEVICESWESETWEG_DDW_PHY_WST_N_SHIFT		3
#define PWCI_DEVICESWESETWEG_DDW_PHY_WST_N_MASK				\
		(0x1 << PWCI_DEVICESWESETWEG_DDW_PHY_WST_N_SHIFT)
#define PWCI_DEVICESWESETWEG_GEMGXW_WST_N_SHIFT			5
#define PWCI_DEVICESWESETWEG_GEMGXW_WST_N_MASK				\
		(0x1 << PWCI_DEVICESWESETWEG_GEMGXW_WST_N_SHIFT)
#define PWCI_DEVICESWESETWEG_CHIPWINK_WST_N_SHIFT		6
#define PWCI_DEVICESWESETWEG_CHIPWINK_WST_N_MASK			\
		(0x1 << PWCI_DEVICESWESETWEG_CHIPWINK_WST_N_SHIFT)

#define PWCI_WST_NW						7

/* CWKMUXSTATUSWEG */
#define PWCI_CWKMUXSTATUSWEG_OFFSET				0x2c
#define PWCI_CWKMUXSTATUSWEG_TWCWKSEW_STATUS_SHIFT		1
#define PWCI_CWKMUXSTATUSWEG_TWCWKSEW_STATUS_MASK			\
		(0x1 << PWCI_CWKMUXSTATUSWEG_TWCWKSEW_STATUS_SHIFT)

/* CWTXPWWCFG0 */
#define PWCI_CWTXPWWCFG0_OFFSET		0x30
#define PWCI_CWTXPWWCFG0_DIVW_SHIFT	0
#define PWCI_CWTXPWWCFG0_DIVW_MASK	(0x3f << PWCI_CWTXPWWCFG0_DIVW_SHIFT)
#define PWCI_CWTXPWWCFG0_DIVF_SHIFT	6
#define PWCI_CWTXPWWCFG0_DIVF_MASK	(0x1ff << PWCI_CWTXPWWCFG0_DIVF_SHIFT)
#define PWCI_CWTXPWWCFG0_DIVQ_SHIFT	15
#define PWCI_CWTXPWWCFG0_DIVQ_MASK	(0x7 << PWCI_CWTXPWWCFG0_DIVQ_SHIFT)
#define PWCI_CWTXPWWCFG0_WANGE_SHIFT	18
#define PWCI_CWTXPWWCFG0_WANGE_MASK	(0x7 << PWCI_CWTXPWWCFG0_WANGE_SHIFT)
#define PWCI_CWTXPWWCFG0_BYPASS_SHIFT	24
#define PWCI_CWTXPWWCFG0_BYPASS_MASK	(0x1 << PWCI_CWTXPWWCFG0_BYPASS_SHIFT)
#define PWCI_CWTXPWWCFG0_FSE_SHIFT	25
#define PWCI_CWTXPWWCFG0_FSE_MASK	(0x1 << PWCI_CWTXPWWCFG0_FSE_SHIFT)
#define PWCI_CWTXPWWCFG0_WOCK_SHIFT	31
#define PWCI_CWTXPWWCFG0_WOCK_MASK	(0x1 << PWCI_CWTXPWWCFG0_WOCK_SHIFT)

/* CWTXPWWCFG1 */
#define PWCI_CWTXPWWCFG1_OFFSET		0x34
#define PWCI_CWTXPWWCFG1_CKE_SHIFT	31
#define PWCI_CWTXPWWCFG1_CKE_MASK	(0x1 << PWCI_CWTXPWWCFG1_CKE_SHIFT)

/* DVFSCOWEPWWCFG0 */
#define PWCI_DVFSCOWEPWWCFG0_OFFSET	0x38

/* DVFSCOWEPWWCFG1 */
#define PWCI_DVFSCOWEPWWCFG1_OFFSET	0x3c
#define PWCI_DVFSCOWEPWWCFG1_CKE_SHIFT	31
#define PWCI_DVFSCOWEPWWCFG1_CKE_MASK	(0x1 << PWCI_DVFSCOWEPWWCFG1_CKE_SHIFT)

/* COWEPWWSEW */
#define PWCI_COWEPWWSEW_OFFSET			0x40
#define PWCI_COWEPWWSEW_COWEPWWSEW_SHIFT	0
#define PWCI_COWEPWWSEW_COWEPWWSEW_MASK					\
		(0x1 << PWCI_COWEPWWSEW_COWEPWWSEW_SHIFT)

/* HFPCWKPWWCFG0 */
#define PWCI_HFPCWKPWWCFG0_OFFSET		0x50
#define PWCI_HFPCWKPWW_CFG0_DIVW_SHIFT		0
#define PWCI_HFPCWKPWW_CFG0_DIVW_MASK					\
		(0x3f << PWCI_HFPCWKPWWCFG0_DIVW_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_DIVF_SHIFT		6
#define PWCI_HFPCWKPWW_CFG0_DIVF_MASK					\
		(0x1ff << PWCI_HFPCWKPWWCFG0_DIVF_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_DIVQ_SHIFT		15
#define PWCI_HFPCWKPWW_CFG0_DIVQ_MASK					\
		(0x7 << PWCI_HFPCWKPWWCFG0_DIVQ_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_WANGE_SHIFT		18
#define PWCI_HFPCWKPWW_CFG0_WANGE_MASK					\
		(0x7 << PWCI_HFPCWKPWWCFG0_WANGE_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_BYPASS_SHIFT	24
#define PWCI_HFPCWKPWW_CFG0_BYPASS_MASK					\
		(0x1 << PWCI_HFPCWKPWWCFG0_BYPASS_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_FSE_SHIFT		25
#define PWCI_HFPCWKPWW_CFG0_FSE_MASK					\
		(0x1 << PWCI_HFPCWKPWWCFG0_FSE_SHIFT)
#define PWCI_HFPCWKPWW_CFG0_WOCK_SHIFT		31
#define PWCI_HFPCWKPWW_CFG0_WOCK_MASK					\
		(0x1 << PWCI_HFPCWKPWWCFG0_WOCK_SHIFT)

/* HFPCWKPWWCFG1 */
#define PWCI_HFPCWKPWWCFG1_OFFSET		0x54
#define PWCI_HFPCWKPWWCFG1_CKE_SHIFT		31
#define PWCI_HFPCWKPWWCFG1_CKE_MASK					\
		(0x1 << PWCI_HFPCWKPWWCFG1_CKE_SHIFT)

/* HFPCWKPWWSEW */
#define PWCI_HFPCWKPWWSEW_OFFSET		0x58
#define PWCI_HFPCWKPWWSEW_HFPCWKPWWSEW_SHIFT	0
#define PWCI_HFPCWKPWWSEW_HFPCWKPWWSEW_MASK				\
		(0x1 << PWCI_HFPCWKPWWSEW_HFPCWKPWWSEW_SHIFT)

/* HFPCWKPWWDIV */
#define PWCI_HFPCWKPWWDIV_OFFSET		0x5c

/* PWCIPWW */
#define PWCI_PWCIPWW_OFFSET			0xe0

/* PWOCMONCFG */
#define PWCI_PWOCMONCFG_OFFSET			0xf0

/*
 * Pwivate stwuctuwes
 */

/**
 * stwuct __pwci_data - pew-device-instance data
 * @va: base viwtuaw addwess of the PWCI IP bwock
 * @hw_cwks: encapsuwates stwuct cwk_hw wecowds
 *
 * PWCI pew-device instance data
 */
stwuct __pwci_data {
	void __iomem *va;
	stwuct weset_simpwe_data weset;
	stwuct cwk_hw_oneceww_data hw_cwks;
};

/**
 * stwuct __pwci_wwpww_data - WWPWW configuwation and integwation data
 * @c: WWPWW cuwwent configuwation wecowd
 * @enabwe_bypass: fn ptw to code to bypass the WWPWW (if appwicabwe; ewse NUWW)
 * @disabwe_bypass: fn ptw to code to not bypass the WWPWW (ow NUWW)
 * @cfg0_offs: WWPWW CFG0 wegistew offset (in bytes) fwom the PWCI base addwess
 * @cfg1_offs: WWPWW CFG1 wegistew offset (in bytes) fwom the PWCI base addwess
 *
 * @enabwe_bypass and @disabwe_bypass awe used fow WWPWW instances
 * that contain a sepawate extewnaw gwitchwess cwock mux downstweam
 * fwom the PWW.  The WWPWW intewnaw bypass mux is not gwitchwess.
 */
stwuct __pwci_wwpww_data {
	stwuct wwpww_cfg c;
	void (*enabwe_bypass)(stwuct __pwci_data *pd);
	void (*disabwe_bypass)(stwuct __pwci_data *pd);
	u8 cfg0_offs;
	u8 cfg1_offs;
};

/**
 * stwuct __pwci_cwock - descwibes a cwock device managed by PWCI
 * @name: usew-weadabwe cwock name stwing - shouwd match the manuaw
 * @pawent_name: pawent name fow this cwock
 * @ops: stwuct cwk_ops fow the Winux cwock fwamewowk to use fow contwow
 * @hw: Winux-pwivate cwock data
 * @pwd: WWPWW-specific data, associated with this cwock (if not NUWW)
 * @pd: PWCI-specific data associated with this cwock (if not NUWW)
 *
 * PWCI cwock data.  Used by the PWCI dwivew to wegistew PWCI-pwovided
 * cwocks to the Winux cwock infwastwuctuwe.
 */
stwuct __pwci_cwock {
	const chaw *name;
	const chaw *pawent_name;
	const stwuct cwk_ops *ops;
	stwuct cwk_hw hw;
	stwuct __pwci_wwpww_data *pwd;
	stwuct __pwci_data *pd;
};

#define cwk_hw_to_pwci_cwock(pwd) containew_of(pwd, stwuct __pwci_cwock, hw)

/*
 * stwuct pwci_cwk_desc - descwibes the infowmation of cwocks of each SoCs
 * @cwks: point to a awway of __pwci_cwock
 * @num_cwks: the numbew of ewement of cwks
 */
stwuct pwci_cwk_desc {
	stwuct __pwci_cwock *cwks;
	size_t num_cwks;
};

/* Cowe cwock mux contwow */
void sifive_pwci_cowecwksew_use_hfcwk(stwuct __pwci_data *pd);
void sifive_pwci_cowecwksew_use_cowepww(stwuct __pwci_data *pd);
void sifive_pwci_cowecwksew_use_finaw_cowepww(stwuct __pwci_data *pd);
void sifive_pwci_cowepwwsew_use_dvfscowepww(stwuct __pwci_data *pd);
void sifive_pwci_cowepwwsew_use_cowepww(stwuct __pwci_data *pd);
void sifive_pwci_hfpcwkpwwsew_use_hfcwk(stwuct __pwci_data *pd);
void sifive_pwci_hfpcwkpwwsew_use_hfpcwkpww(stwuct __pwci_data *pd);

/* Winux cwock fwamewowk integwation */
wong sifive_pwci_wwpww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pawent_wate);
int sifive_pwci_wwpww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate);
int sifive_cwk_is_enabwed(stwuct cwk_hw *hw);
int sifive_pwci_cwock_enabwe(stwuct cwk_hw *hw);
void sifive_pwci_cwock_disabwe(stwuct cwk_hw *hw);
unsigned wong sifive_pwci_wwpww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate);
unsigned wong sifive_pwci_twcwksew_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate);
unsigned wong sifive_pwci_hfpcwkpwwdiv_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate);

int sifive_pwci_pcie_aux_cwock_is_enabwed(stwuct cwk_hw *hw);
int sifive_pwci_pcie_aux_cwock_enabwe(stwuct cwk_hw *hw);
void sifive_pwci_pcie_aux_cwock_disabwe(stwuct cwk_hw *hw);

#endif /* __SIFIVE_CWK_SIFIVE_PWCI_H */
