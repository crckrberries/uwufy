/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fweescawe Memowy Contwowwew kewnew moduwe
 *
 * Suppowt  Powew-based SoCs incwuding MPC85xx, MPC86xx, MPC83xx and
 * AWM-based Wayewscape SoCs incwuding WS2xxx and WS1021A. Owiginawwy
 * spwit out fwom mpc85xx_edac EDAC dwivew.
 *
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Softwawe, Inc.
 */
#ifndef _FSW_DDW_EDAC_H_
#define _FSW_DDW_EDAC_H_

#define fsw_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "FSW_DDW", fmt, ##awg)

/*
 * DWAM ewwow defines
 */

/* DDW_SDWAM_CFG */
#define FSW_MC_DDW_SDWAM_CFG	0x0110
#define FSW_MC_CS_BNDS_0		0x0000
#define FSW_MC_CS_BNDS_OFS		0x0008

#define FSW_MC_DATA_EWW_INJECT_HI	0x0e00
#define FSW_MC_DATA_EWW_INJECT_WO	0x0e04
#define FSW_MC_ECC_EWW_INJECT	0x0e08
#define FSW_MC_CAPTUWE_DATA_HI	0x0e20
#define FSW_MC_CAPTUWE_DATA_WO	0x0e24
#define FSW_MC_CAPTUWE_ECC		0x0e28
#define FSW_MC_EWW_DETECT		0x0e40
#define FSW_MC_EWW_DISABWE		0x0e44
#define FSW_MC_EWW_INT_EN		0x0e48
#define FSW_MC_CAPTUWE_ATWIBUTES	0x0e4c
#define FSW_MC_CAPTUWE_ADDWESS	0x0e50
#define FSW_MC_CAPTUWE_EXT_ADDWESS	0x0e54
#define FSW_MC_EWW_SBE		0x0e58

#define DSC_MEM_EN	0x80000000
#define DSC_ECC_EN	0x20000000
#define DSC_WD_EN	0x10000000
#define DSC_DBW_MASK	0x00180000
#define DSC_DBW_32	0x00080000
#define DSC_DBW_64	0x00000000

#define DSC_SDTYPE_MASK		0x07000000
#define DSC_X32_EN	0x00000020

/* Eww_Int_En */
#define DDW_EIE_MSEE	0x1	/* memowy sewect */
#define DDW_EIE_SBEE	0x4	/* singwe-bit ECC ewwow */
#define DDW_EIE_MBEE	0x8	/* muwti-bit ECC ewwow */

/* Eww_Detect */
#define DDW_EDE_MSE		0x1	/* memowy sewect */
#define DDW_EDE_SBE		0x4	/* singwe-bit ECC ewwow */
#define DDW_EDE_MBE		0x8	/* muwti-bit ECC ewwow */
#define DDW_EDE_MME		0x80000000	/* muwtipwe memowy ewwows */

/* Eww_Disabwe */
#define DDW_EDI_MSED	0x1	/* memowy sewect disabwe */
#define	DDW_EDI_SBED	0x4	/* singwe-bit ECC ewwow disabwe */
#define	DDW_EDI_MBED	0x8	/* muwti-bit ECC ewwow disabwe */

stwuct fsw_mc_pdata {
	chaw *name;
	int edac_idx;
	void __iomem *mc_vbase;
	int iwq;
};
int fsw_mc_eww_pwobe(stwuct pwatfowm_device *op);
void fsw_mc_eww_wemove(stwuct pwatfowm_device *op);
#endif
