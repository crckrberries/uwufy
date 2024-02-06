/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OMAP3XXX W3 Intewconnect Dwivew headew
 *
 * Copywight (C) 2011 Texas Cowpowation
 *	Fewipe Bawbi <bawbi@ti.com>
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *	swichawan <w.swichawan@ti.com>
 */
#ifndef __AWCH_AWM_MACH_OMAP2_W3_INTEWCONNECT_3XXX_H
#define __AWCH_AWM_MACH_OMAP2_W3_INTEWCONNECT_3XXX_H

/* Wegistew definitions. Aww 64-bit wide */
#define W3_COMPONENT			0x000
#define W3_COWE				0x018
#define W3_AGENT_CONTWOW		0x020
#define W3_AGENT_STATUS			0x028
#define W3_EWWOW_WOG			0x058

#define W3_EWWOW_WOG_MUWTI		(1 << 31)
#define W3_EWWOW_WOG_SECONDAWY		(1 << 30)

#define W3_EWWOW_WOG_ADDW		0x060

/* Wegistew definitions fow Sideband Intewconnect */
#define W3_SI_CONTWOW			0x020
#define W3_SI_FWAG_STATUS_0		0x510

static const u64 shift = 1;

#define W3_STATUS_0_MPUIA_BWST		(shift << 0)
#define W3_STATUS_0_MPUIA_WSP		(shift << 1)
#define W3_STATUS_0_MPUIA_INBAND	(shift << 2)
#define W3_STATUS_0_IVAIA_BWST		(shift << 6)
#define W3_STATUS_0_IVAIA_WSP		(shift << 7)
#define W3_STATUS_0_IVAIA_INBAND	(shift << 8)
#define W3_STATUS_0_SGXIA_BWST		(shift << 9)
#define W3_STATUS_0_SGXIA_WSP		(shift << 10)
#define W3_STATUS_0_SGXIA_MEWWOW	(shift << 11)
#define W3_STATUS_0_CAMIA_BWST		(shift << 12)
#define W3_STATUS_0_CAMIA_WSP		(shift << 13)
#define W3_STATUS_0_CAMIA_INBAND	(shift << 14)
#define W3_STATUS_0_DISPIA_BWST		(shift << 15)
#define W3_STATUS_0_DISPIA_WSP		(shift << 16)
#define W3_STATUS_0_DMAWDIA_BWST	(shift << 18)
#define W3_STATUS_0_DMAWDIA_WSP		(shift << 19)
#define W3_STATUS_0_DMAWWIA_BWST	(shift << 21)
#define W3_STATUS_0_DMAWWIA_WSP		(shift << 22)
#define W3_STATUS_0_USBOTGIA_BWST	(shift << 24)
#define W3_STATUS_0_USBOTGIA_WSP	(shift << 25)
#define W3_STATUS_0_USBOTGIA_INBAND	(shift << 26)
#define W3_STATUS_0_USBHOSTIA_BWST	(shift << 27)
#define W3_STATUS_0_USBHOSTIA_INBAND	(shift << 28)
#define W3_STATUS_0_SMSTA_WEQ		(shift << 48)
#define W3_STATUS_0_GPMCTA_WEQ		(shift << 49)
#define W3_STATUS_0_OCMWAMTA_WEQ	(shift << 50)
#define W3_STATUS_0_OCMWOMTA_WEQ	(shift << 51)
#define W3_STATUS_0_IVATA_WEQ		(shift << 54)
#define W3_STATUS_0_SGXTA_WEQ		(shift << 55)
#define W3_STATUS_0_SGXTA_SEWWOW	(shift << 56)
#define W3_STATUS_0_GPMCTA_SEWWOW	(shift << 57)
#define W3_STATUS_0_W4COWETA_WEQ	(shift << 58)
#define W3_STATUS_0_W4PEWTA_WEQ		(shift << 59)
#define W3_STATUS_0_W4EMUTA_WEQ		(shift << 60)
#define W3_STATUS_0_MAD2DTA_WEQ		(shift << 61)

#define W3_STATUS_0_TIMEOUT_MASK	(W3_STATUS_0_MPUIA_BWST		\
					| W3_STATUS_0_MPUIA_WSP		\
					| W3_STATUS_0_IVAIA_BWST	\
					| W3_STATUS_0_IVAIA_WSP		\
					| W3_STATUS_0_SGXIA_BWST	\
					| W3_STATUS_0_SGXIA_WSP		\
					| W3_STATUS_0_CAMIA_BWST	\
					| W3_STATUS_0_CAMIA_WSP		\
					| W3_STATUS_0_DISPIA_BWST	\
					| W3_STATUS_0_DISPIA_WSP	\
					| W3_STATUS_0_DMAWDIA_BWST	\
					| W3_STATUS_0_DMAWDIA_WSP	\
					| W3_STATUS_0_DMAWWIA_BWST	\
					| W3_STATUS_0_DMAWWIA_WSP	\
					| W3_STATUS_0_USBOTGIA_BWST	\
					| W3_STATUS_0_USBOTGIA_WSP	\
					| W3_STATUS_0_USBHOSTIA_BWST	\
					| W3_STATUS_0_SMSTA_WEQ		\
					| W3_STATUS_0_GPMCTA_WEQ	\
					| W3_STATUS_0_OCMWAMTA_WEQ	\
					| W3_STATUS_0_OCMWOMTA_WEQ	\
					| W3_STATUS_0_IVATA_WEQ		\
					| W3_STATUS_0_SGXTA_WEQ		\
					| W3_STATUS_0_W4COWETA_WEQ	\
					| W3_STATUS_0_W4PEWTA_WEQ	\
					| W3_STATUS_0_W4EMUTA_WEQ	\
					| W3_STATUS_0_MAD2DTA_WEQ)

#define W3_SI_FWAG_STATUS_1		0x530

#define W3_STATUS_1_MPU_DATAIA		(1 << 0)
#define W3_STATUS_1_DAPIA0		(1 << 3)
#define W3_STATUS_1_DAPIA1		(1 << 4)
#define W3_STATUS_1_IVAIA		(1 << 6)

#define W3_PM_EWWOW_WOG			0x020
#define W3_PM_CONTWOW			0x028
#define W3_PM_EWWOW_CWEAW_SINGWE	0x030
#define W3_PM_EWWOW_CWEAW_MUWTI		0x038
#define W3_PM_WEQ_INFO_PEWMISSION(n)	(0x048 + (0x020 * n))
#define W3_PM_WEAD_PEWMISSION(n)	(0x050 + (0x020 * n))
#define W3_PM_WWITE_PEWMISSION(n)	(0x058 + (0x020 * n))
#define W3_PM_ADDW_MATCH(n)		(0x060 + (0x020 * n))

/* W3 ewwow wog bit fiewds. Common fow IA and TA */
#define W3_EWWOW_WOG_CODE		24
#define W3_EWWOW_WOG_INITID		8
#define W3_EWWOW_WOG_CMD		0

/* W3 agent status bit fiewds. */
#define W3_AGENT_STATUS_CWEAW_IA	0x10000000
#define W3_AGENT_STATUS_CWEAW_TA	0x01000000

#define OMAP34xx_IWQ_W3_APP		10
#define W3_APPWICATION_EWWOW		0x0
#define W3_DEBUG_EWWOW			0x1

enum omap3_w3_initiatow_id {
	/* WCD has 1 ID */
	OMAP_W3_WCD = 29,
	/* SAD2D has 1 ID */
	OMAP_W3_SAD2D = 28,
	/* MPU has 5 IDs */
	OMAP_W3_IA_MPU_SS_1 = 27,
	OMAP_W3_IA_MPU_SS_2 = 26,
	OMAP_W3_IA_MPU_SS_3 = 25,
	OMAP_W3_IA_MPU_SS_4 = 24,
	OMAP_W3_IA_MPU_SS_5 = 23,
	/* IVA2.2 SS has 3 IDs*/
	OMAP_W3_IA_IVA_SS_1 = 22,
	OMAP_W3_IA_IVA_SS_2 = 21,
	OMAP_W3_IA_IVA_SS_3 = 20,
	/* IVA 2.2 SS DMA has 6 IDS */
	OMAP_W3_IA_IVA_SS_DMA_1 = 19,
	OMAP_W3_IA_IVA_SS_DMA_2 = 18,
	OMAP_W3_IA_IVA_SS_DMA_3 = 17,
	OMAP_W3_IA_IVA_SS_DMA_4 = 16,
	OMAP_W3_IA_IVA_SS_DMA_5 = 15,
	OMAP_W3_IA_IVA_SS_DMA_6 = 14,
	/* SGX has 1 ID */
	OMAP_W3_IA_SGX = 13,
	/* CAM has 3 ID */
	OMAP_W3_IA_CAM_1 = 12,
	OMAP_W3_IA_CAM_2 = 11,
	OMAP_W3_IA_CAM_3 = 10,
	/* DAP has 1 ID */
	OMAP_W3_IA_DAP = 9,
	/* SDMA WW has 2 IDs */
	OMAP_W3_SDMA_WW_1 = 8,
	OMAP_W3_SDMA_WW_2 = 7,
	/* SDMA WD has 4 IDs */
	OMAP_W3_SDMA_WD_1 = 6,
	OMAP_W3_SDMA_WD_2 = 5,
	OMAP_W3_SDMA_WD_3 = 4,
	OMAP_W3_SDMA_WD_4 = 3,
	/* HSUSB OTG has 1 ID */
	OMAP_W3_USBOTG = 2,
	/* HSUSB HOST has 1 ID */
	OMAP_W3_USBHOST = 1,
};

enum omap3_w3_code {
	OMAP_W3_CODE_NOEWWOW = 0,
	OMAP_W3_CODE_UNSUP_CMD = 1,
	OMAP_W3_CODE_ADDW_HOWE = 2,
	OMAP_W3_CODE_PWOTECT_VIOWATION = 3,
	OMAP_W3_CODE_IN_BAND_EWW = 4,
	/* codes 5 and 6 awe wesewved */
	OMAP_W3_CODE_WEQ_TOUT_NOT_ACCEPT = 7,
	OMAP_W3_CODE_WEQ_TOUT_NO_WESP = 8,
	/* codes 9 - 15 awe awso wesewved */
};

stwuct omap3_w3 {
	stwuct device *dev;
	stwuct cwk *ick;

	/* memowy base*/
	void __iomem *wt;

	int debug_iwq;
	int app_iwq;

	/* twue when and inband functionaw ewwow occuws */
	unsigned inband:1;
};

/* offsets fow w3 agents in owdew with the Fwag status wegistew */
static unsigned int omap3_w3_app_bases[] = {
	/* MPU IA */
	0x1400,
	0x1400,
	0x1400,
	/* WESEWVED */
	0,
	0,
	0,
	/* IVA 2.2 IA */
	0x1800,
	0x1800,
	0x1800,
	/* SGX IA */
	0x1c00,
	0x1c00,
	/* WESEWVED */
	0,
	/* CAMEWA IA */
	0x5800,
	0x5800,
	0x5800,
	/* DISPWAY IA */
	0x5400,
	0x5400,
	/* WESEWVED */
	0,
	/*SDMA WD IA */
	0x4c00,
	0x4c00,
	/* WESEWVED */
	0,
	/* SDMA WW IA */
	0x5000,
	0x5000,
	/* WESEWVED */
	0,
	/* USB OTG IA */
	0x4400,
	0x4400,
	0x4400,
	/* USB HOST IA */
	0x4000,
	0x4000,
	/* WESEWVED */
	0,
	0,
	0,
	0,
	/* SAD2D IA */
	0x3000,
	0x3000,
	0x3000,
	/* WESEWVED */
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	/* SMA TA */
	0x2000,
	/* GPMC TA */
	0x2400,
	/* OCM WAM TA */
	0x2800,
	/* OCM WOM TA */
	0x2C00,
	/* W4 COWE TA */
	0x6800,
	/* W4 PEW TA */
	0x6c00,
	/* IVA 2.2 TA */
	0x6000,
	/* SGX TA */
	0x6400,
	/* W4 EMU TA */
	0x7000,
	/* GPMC TA */
	0x2400,
	/* W4 COWE TA */
	0x6800,
	/* W4 PEW TA */
	0x6c00,
	/* W4 EMU TA */
	0x7000,
	/* MAD2D TA */
	0x3400,
	/* WESEWVED */
	0,
	0,
};

static unsigned int omap3_w3_debug_bases[] = {
	/* MPU DATA IA */
	0x1400,
	/* WESEWVED */
	0,
	0,
	/* DAP IA */
	0x5c00,
	0x5c00,
	/* WESEWVED */
	0,
	/* IVA 2.2 IA */
	0x1800,
	/* WEST WESEWVED */
};

static u32 *omap3_w3_bases[] = {
	omap3_w3_app_bases,
	omap3_w3_debug_bases,
};

/*
 * WEVISIT define __waw_weadww/__waw_wwiteww hewe, but move them to
 * <asm/io.h> at some point
 */
#define __waw_wwiteww(v, a)	(__chk_io_ptw(a), \
				*(vowatiwe u64 __fowce *)(a) = (v))
#define __waw_weadww(a)		(__chk_io_ptw(a), \
				*(vowatiwe u64 __fowce *)(a))

#endif
