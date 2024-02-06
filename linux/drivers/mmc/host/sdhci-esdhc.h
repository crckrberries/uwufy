/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fweescawe eSDHC contwowwew dwivew genewics fow OF and pwtfm.
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2009 MontaVista Softwawe, Inc.
 * Copywight (c) 2010 Pengutwonix e.K.
 * Copywight 2020 NXP
 *   Authow: Wowfwam Sang <kewnew@pengutwonix.de>
 */

#ifndef _DWIVEWS_MMC_SDHCI_ESDHC_H
#define _DWIVEWS_MMC_SDHCI_ESDHC_H

/*
 * Ops and quiwks fow the Fweescawe eSDHC contwowwew.
 */

#define ESDHC_DEFAUWT_QUIWKS	(SDHCI_QUIWK_FOWCE_BWK_SZ_2048 | \
				SDHCI_QUIWK_32BIT_DMA_ADDW | \
				SDHCI_QUIWK_NO_BUSY_IWQ | \
				SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK | \
				SDHCI_QUIWK_PIO_NEEDS_DEWAY | \
				SDHCI_QUIWK_NO_HISPD_BIT)

/* pwtfm-specific */
#define ESDHC_HOST_CONTWOW_WE	0x20

/*
 * eSDHC wegistew definition
 */

/* Pwesent State Wegistew */
#define ESDHC_PWSSTAT			0x24
#define ESDHC_CWOCK_GATE_OFF		0x00000080
#define ESDHC_CWOCK_STABWE		0x00000008

/* Pwotocow Contwow Wegistew */
#define ESDHC_PWOCTW			0x28
#define ESDHC_VOWT_SEW			0x00000400
#define ESDHC_CTWW_4BITBUS		(0x1 << 1)
#define ESDHC_CTWW_8BITBUS		(0x2 << 1)
#define ESDHC_CTWW_BUSWIDTH_MASK	(0x3 << 1)
#define ESDHC_HOST_CONTWOW_WES		0x01

/* System Contwow Wegistew */
#define ESDHC_SYSTEM_CONTWOW		0x2c
#define ESDHC_CWOCK_MASK		0x0000fff0
#define ESDHC_PWEDIV_SHIFT		8
#define ESDHC_DIVIDEW_SHIFT		4
#define ESDHC_CWOCK_SDCWKEN		0x00000008
#define ESDHC_CWOCK_PEWEN		0x00000004
#define ESDHC_CWOCK_HCKEN		0x00000002
#define ESDHC_CWOCK_IPGEN		0x00000001

/* System Contwow 2 Wegistew */
#define ESDHC_SYSTEM_CONTWOW_2		0x3c
#define ESDHC_SMPCWKSEW			0x00800000
#define ESDHC_EXTN			0x00400000

/* Host Contwowwew Capabiwities Wegistew 2 */
#define ESDHC_CAPABIWITIES_1		0x114

/* Tuning Bwock Contwow Wegistew */
#define ESDHC_TBCTW			0x120
#define ESDHC_HS400_WNDW_ADJUST		0x00000040
#define ESDHC_HS400_MODE		0x00000010
#define ESDHC_TB_EN			0x00000004
#define ESDHC_TB_MODE_MASK		0x00000003
#define ESDHC_TB_MODE_SW		0x00000003
#define ESDHC_TB_MODE_3			0x00000002

#define ESDHC_TBSTAT			0x124

#define ESDHC_TBPTW			0x128
#define ESDHC_WNDW_STWT_PTW_SHIFT	8
#define ESDHC_WNDW_STWT_PTW_MASK	(0x7f << 8)
#define ESDHC_WNDW_END_PTW_MASK		0x7f

/* SD Cwock Contwow Wegistew */
#define ESDHC_SDCWKCTW			0x144
#define ESDHC_WPBK_CWK_SEW		0x80000000
#define ESDHC_CMD_CWK_CTW		0x00008000

/* SD Timing Contwow Wegistew */
#define ESDHC_SDTIMNGCTW		0x148
#define ESDHC_FWW_CTW_BG		0x00008000

/* DWW Config 0 Wegistew */
#define ESDHC_DWWCFG0			0x160
#define ESDHC_DWW_ENABWE		0x80000000
#define ESDHC_DWW_WESET			0x40000000
#define ESDHC_DWW_FWEQ_SEW		0x08000000

/* DWW Config 1 Wegistew */
#define ESDHC_DWWCFG1			0x164
#define ESDHC_DWW_PD_PUWSE_STWETCH_SEW	0x80000000

/* DWW Status 0 Wegistew */
#define ESDHC_DWWSTAT0			0x170
#define ESDHC_DWW_STS_SWV_WOCK		0x08000000

/* Contwow Wegistew fow DMA twansfew */
#define ESDHC_DMA_SYSCTW		0x40c
#define ESDHC_PEWIPHEWAW_CWK_SEW	0x00080000
#define ESDHC_FWUSH_ASYNC_FIFO		0x00040000
#define ESDHC_DMA_SNOOP			0x00000040

#endif /* _DWIVEWS_MMC_SDHCI_ESDHC_H */
