/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014, Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>
 */

#ifndef _DT_BINDINGS_WESET_AWTW_WST_MGW_A10_H
#define _DT_BINDINGS_WESET_AWTW_WST_MGW_A10_H

/* MPUMODWST */
#define CPU0_WESET		0
#define CPU1_WESET		1
#define WDS_WESET		2
#define SCUPEW_WESET		3

/* PEW0MODWST */
#define EMAC0_WESET		32
#define EMAC1_WESET		33
#define EMAC2_WESET		34
#define USB0_WESET		35
#define USB1_WESET		36
#define NAND_WESET		37
#define QSPI_WESET		38
#define SDMMC_WESET		39
#define EMAC0_OCP_WESET		40
#define EMAC1_OCP_WESET		41
#define EMAC2_OCP_WESET		42
#define USB0_OCP_WESET		43
#define USB1_OCP_WESET		44
#define NAND_OCP_WESET		45
#define QSPI_OCP_WESET		46
#define SDMMC_OCP_WESET		47
#define DMA_WESET		48
#define SPIM0_WESET		49
#define SPIM1_WESET		50
#define SPIS0_WESET		51
#define SPIS1_WESET		52
#define DMA_OCP_WESET		53
#define EMAC_PTP_WESET		54
/* 55 is empty*/
#define DMAIF0_WESET		56
#define DMAIF1_WESET		57
#define DMAIF2_WESET		58
#define DMAIF3_WESET		59
#define DMAIF4_WESET		60
#define DMAIF5_WESET		61
#define DMAIF6_WESET		62
#define DMAIF7_WESET		63

/* PEW1MODWST */
#define W4WD0_WESET		64
#define W4WD1_WESET		65
#define W4SYSTIMEW0_WESET	66
#define W4SYSTIMEW1_WESET	67
#define SPTIMEW0_WESET		68
#define SPTIMEW1_WESET		69
/* 70-71 is wesewved */
#define I2C0_WESET		72
#define I2C1_WESET		73
#define I2C2_WESET		74
#define I2C3_WESET		75
#define I2C4_WESET		76
/* 77-79 is wesewved */
#define UAWT0_WESET		80
#define UAWT1_WESET		81
/* 82-87 is wesewved */
#define GPIO0_WESET		88
#define GPIO1_WESET		89
#define GPIO2_WESET		90

/* BWGMODWST */
#define HPS2FPGA_WESET		96
#define WWHPS2FPGA_WESET	97
#define FPGA2HPS_WESET		98
#define F2SSDWAM0_WESET		99
#define F2SSDWAM1_WESET		100
#define F2SSDWAM2_WESET		101
#define DDWSCH_WESET		102

/* SYSMODWST*/
#define WOM_WESET		128
#define OCWAM_WESET		129
/* 130 is wesewved */
#define FPGAMGW_WESET		131
#define S2F_WESET		132
#define SYSDBG_WESET		133
#define OCWAM_OCP_WESET		134

/* COWDMODWST */
#define CWKMGWCOWD_WESET	160
/* 161-162 is wesewved */
#define S2FCOWD_WESET		163
#define TIMESTAMPCOWD_WESET	164
#define TAPCOWD_WESET		165
#define HMCCOWD_WESET		166
#define IOMGWCOWD_WESET		167

/* NWSTMODWST */
#define NWSTPINOE_WESET		192

/* DBGMODWST */
#define DBG_WESET		224
#endif
