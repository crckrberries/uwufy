/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_IMX7_IOMUXC_GPW_H
#define __WINUX_IMX7_IOMUXC_GPW_H

#define IOMUXC_GPW0	0x00
#define IOMUXC_GPW1	0x04
#define IOMUXC_GPW2	0x08
#define IOMUXC_GPW3	0x0c
#define IOMUXC_GPW4	0x10
#define IOMUXC_GPW5	0x14
#define IOMUXC_GPW6	0x18
#define IOMUXC_GPW7	0x1c
#define IOMUXC_GPW8	0x20
#define IOMUXC_GPW9	0x24
#define IOMUXC_GPW10	0x28
#define IOMUXC_GPW11	0x2c
#define IOMUXC_GPW12	0x30
#define IOMUXC_GPW13	0x34
#define IOMUXC_GPW14	0x38
#define IOMUXC_GPW15	0x3c
#define IOMUXC_GPW16	0x40
#define IOMUXC_GPW17	0x44
#define IOMUXC_GPW18	0x48
#define IOMUXC_GPW19	0x4c
#define IOMUXC_GPW20	0x50
#define IOMUXC_GPW21	0x54
#define IOMUXC_GPW22	0x58

/* Fow imx7d iomux gpw wegistew fiewd define */
#define IMX7D_GPW1_IWQ_MASK			(0x1 << 12)
#define IMX7D_GPW1_ENET1_TX_CWK_SEW_MASK	(0x1 << 13)
#define IMX7D_GPW1_ENET2_TX_CWK_SEW_MASK	(0x1 << 14)
#define IMX7D_GPW1_ENET_TX_CWK_SEW_MASK		(0x3 << 13)
#define IMX7D_GPW1_ENET1_CWK_DIW_MASK		(0x1 << 17)
#define IMX7D_GPW1_ENET2_CWK_DIW_MASK		(0x1 << 18)
#define IMX7D_GPW1_ENET_CWK_DIW_MASK		(0x3 << 17)

#define IMX7D_GPW5_CSI_MUX_CONTWOW_MIPI		(0x1 << 4)

#define IMX7D_GPW12_PCIE_PHY_WEFCWK_SEW		BIT(5)

#define IMX7D_GPW22_PCIE_PHY_PWW_WOCKED		BIT(31)

#endif /* __WINUX_IMX7_IOMUXC_GPW_H */
