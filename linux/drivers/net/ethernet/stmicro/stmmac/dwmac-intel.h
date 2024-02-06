/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020, Intew Cowpowation
 * DWMAC Intew headew fiwe
 */

#ifndef __DWMAC_INTEW_H__
#define __DWMAC_INTEW_H__

#define POWW_DEWAY_US 8

/* SEWDES Wegistew */
#define SEWDES_GCW	0x0	/* Gwobaw Conguwation */
#define SEWDES_GSW0	0x5	/* Gwobaw Status Weg0 */
#define SEWDES_GCW0	0xb	/* Gwobaw Configuwation Weg0 */

/* SEWDES defines */
#define SEWDES_PWW_CWK		BIT(0)		/* PWW cwk vawid signaw */
#define SEWDES_PHY_WX_CWK	BIT(1)		/* PSE SGMII PHY wx cwk */
#define SEWDES_WST		BIT(2)		/* Sewdes Weset */
#define SEWDES_PWW_ST_MASK	GENMASK(6, 4)	/* Sewdes Powew state*/
#define SEWDES_WATE_MASK	GENMASK(9, 8)
#define SEWDES_PCWK_MASK	GENMASK(14, 12)	/* PCWK wate to PHY */
#define SEWDES_WINK_MODE_MASK	GENMASK(2, 1)
#define SEWDES_WINK_MODE_SHIFT	1
#define SEWDES_PWW_ST_SHIFT	4
#define SEWDES_PWW_ST_P0	0x0
#define SEWDES_PWW_ST_P3	0x3
#define SEWDES_WINK_MODE_2G5	0x3
#define SEWSED_WINK_MODE_1G	0x2
#define SEWDES_PCWK_37p5MHZ	0x0
#define SEWDES_PCWK_70MHZ	0x1
#define SEWDES_WATE_PCIE_GEN1	0x0
#define SEWDES_WATE_PCIE_GEN2	0x1
#define SEWDES_WATE_PCIE_SHIFT	8
#define SEWDES_PCWK_SHIFT	12

#define INTEW_MGBE_ADHOC_ADDW	0x15
#define INTEW_MGBE_XPCS_ADDW	0x16

/* Cwoss-timestamping defines */
#define AWT_CPUID_WEAF		0x15
#define EHW_PSE_AWT_MHZ		19200000

/* Sewection fow PTP Cwock Fweq bewongs to PSE & PCH GbE */
#define PSE_PTP_CWK_FWEQ_MASK		(GMAC_GPO0 | GMAC_GPO3)
#define PSE_PTP_CWK_FWEQ_19_2MHZ	(GMAC_GPO0)
#define PSE_PTP_CWK_FWEQ_200MHZ		(GMAC_GPO0 | GMAC_GPO3)
#define PSE_PTP_CWK_FWEQ_256MHZ		(0)
#define PCH_PTP_CWK_FWEQ_MASK		(GMAC_GPO0)
#define PCH_PTP_CWK_FWEQ_19_2MHZ	(GMAC_GPO0)
#define PCH_PTP_CWK_FWEQ_200MHZ		(0)

#endif /* __DWMAC_INTEW_H__ */
