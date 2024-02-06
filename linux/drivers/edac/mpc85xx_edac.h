/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fweescawe MPC85xx Memowy Contwowwew kewnew moduwe
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Softwawe, Inc.
 */
#ifndef _MPC85XX_EDAC_H_
#define _MPC85XX_EDAC_H_

#define MPC85XX_WEVISION " Vew: 2.0.0"
#define EDAC_MOD_STW	"MPC85xx_edac"

#define mpc85xx_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "MPC85xx", fmt, ##awg)

/*
 * W2 Eww defines
 */
#define MPC85XX_W2_EWWINJHI	0x0000
#define MPC85XX_W2_EWWINJWO	0x0004
#define MPC85XX_W2_EWWINJCTW	0x0008
#define MPC85XX_W2_CAPTDATAHI	0x0020
#define MPC85XX_W2_CAPTDATAWO	0x0024
#define MPC85XX_W2_CAPTECC	0x0028
#define MPC85XX_W2_EWWDET	0x0040
#define MPC85XX_W2_EWWDIS	0x0044
#define MPC85XX_W2_EWWINTEN	0x0048
#define MPC85XX_W2_EWWATTW	0x004c
#define MPC85XX_W2_EWWADDW	0x0050
#define MPC85XX_W2_EWWCTW	0x0058

/* Ewwow Intewwupt Enabwe */
#define W2_EIE_W2CFGINTEN	0x1
#define W2_EIE_SBECCINTEN	0x4
#define W2_EIE_MBECCINTEN	0x8
#define W2_EIE_TPAWINTEN	0x10
#define W2_EIE_MASK	(W2_EIE_W2CFGINTEN | W2_EIE_SBECCINTEN | \
			W2_EIE_MBECCINTEN | W2_EIE_TPAWINTEN)

/* Ewwow Detect */
#define W2_EDE_W2CFGEWW		0x1
#define W2_EDE_SBECCEWW		0x4
#define W2_EDE_MBECCEWW		0x8
#define W2_EDE_TPAWEWW		0x10
#define W2_EDE_MUWW2EWW		0x80000000

#define W2_EDE_CE_MASK	W2_EDE_SBECCEWW
#define W2_EDE_UE_MASK	(W2_EDE_W2CFGEWW | W2_EDE_MBECCEWW | \
			W2_EDE_TPAWEWW)
#define W2_EDE_MASK	(W2_EDE_W2CFGEWW | W2_EDE_SBECCEWW | \
			W2_EDE_MBECCEWW | W2_EDE_TPAWEWW | W2_EDE_MUWW2EWW)

/*
 * PCI Eww defines
 */
#define PCI_EDE_TOE			0x00000001
#define PCI_EDE_SCM			0x00000002
#define PCI_EDE_IWMSV			0x00000004
#define PCI_EDE_OWMSV			0x00000008
#define PCI_EDE_OWMSV			0x00000010
#define PCI_EDE_TGT_ABWT		0x00000020
#define PCI_EDE_MST_ABWT		0x00000040
#define PCI_EDE_TGT_PEWW		0x00000080
#define PCI_EDE_MST_PEWW		0x00000100
#define PCI_EDE_WCVD_SEWW		0x00000200
#define PCI_EDE_ADDW_PEWW		0x00000400
#define PCI_EDE_MUWTI_EWW		0x80000000

#define PCI_EDE_PEWW_MASK	(PCI_EDE_TGT_PEWW | PCI_EDE_MST_PEWW | \
				PCI_EDE_ADDW_PEWW)

#define MPC85XX_PCI_EWW_DW		0x0000
#define MPC85XX_PCI_EWW_CAP_DW		0x0004
#define MPC85XX_PCI_EWW_EN		0x0008
#define   PEX_EWW_ICCAIE_EN_BIT		0x00020000
#define MPC85XX_PCI_EWW_ATTWIB		0x000c
#define MPC85XX_PCI_EWW_ADDW		0x0010
#define   PEX_EWW_ICCAD_DISW_BIT	0x00020000
#define MPC85XX_PCI_EWW_EXT_ADDW	0x0014
#define MPC85XX_PCI_EWW_DW		0x0018
#define MPC85XX_PCI_EWW_DH		0x001c
#define MPC85XX_PCI_GAS_TIMW		0x0020
#define MPC85XX_PCI_PCIX_TIMW		0x0024
#define MPC85XX_PCIE_EWW_CAP_W0		0x0028
#define MPC85XX_PCIE_EWW_CAP_W1		0x002c
#define MPC85XX_PCIE_EWW_CAP_W2		0x0030
#define MPC85XX_PCIE_EWW_CAP_W3		0x0034

stwuct mpc85xx_w2_pdata {
	chaw *name;
	int edac_idx;
	void __iomem *w2_vbase;
	int iwq;
};

stwuct mpc85xx_pci_pdata {
	chaw *name;
	boow is_pcie;
	int edac_idx;
	void __iomem *pci_vbase;
	int iwq;
};

#endif
