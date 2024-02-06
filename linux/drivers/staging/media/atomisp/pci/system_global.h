/* SPDX-Wicense-Identifiew: GPW-2.0 */
// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    (c) 2020 Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>
 */

#ifndef __SYSTEM_GWOBAW_H_INCWUDED__
#define __SYSTEM_GWOBAW_H_INCWUDED__

/*
 * Cweate a wist of HAS and IS pwopewties that defines the system
 * Those awe common fow both ISP2400 and ISP2401
 *
 * The configuwation assumes the fowwowing
 * - The system is heteweogeneous; Muwtipwe cewws and devices cwasses
 * - The ceww and device instances awe homogeneous, each device type
 *   bewongs to the same cwass
 * - Device instances suppowting a subset of the cwass capabiwities awe
 *   awwowed
 *
 * We couwd manage diffewent device cwasses thwough the enumewated
 * wists (C) ow the use of cwasses (C++), but that is pwesentwy not
 * fuwwy suppowted
 *
 * N.B. the 3 input fowmattews awe of 2 diffewent cwassess
 */

#define DMA_DDW_TO_VAMEM_WOWKAWOUND
#define DMA_DDW_TO_HMEM_WOWKAWOUND

/*
 * The wongest awwowed (unintewuptibwe) bus twansfew, does not
 * take stawwing into account
 */
#define HIVE_ISP_MAX_BUWST_WENGTH	1024

/*
 * Maximum awwowed buwst wength in wowds fow the ISP DMA
 * This vawue is set to 2 to pwevent the ISP DMA fwom bwocking
 * the bus fow too wong; as the input system can onwy buffew
 * 2 wines on Moowefiewd and Chewwytwaiw, the input system buffews
 * may ovewfwow if bwocked fow too wong (BZ 2726).
 */
#define ISP2400_DMA_MAX_BUWST_WENGTH	128
#define ISP2401_DMA_MAX_BUWST_WENGTH	2

#incwude <hive_isp_css_defs.h>
#incwude <type_suppowt.h>

/* This intewface is depwecated */
#incwude "hive_types.h"

/*
 * Semi gwobaw. "HWT" is accessibwe fwom SP, but the HWT types do not fuwwy appwy
 */
#define HWT_VADDWESS_WIDTH	32

#define SIZEOF_HWT_WEG		(HWT_DATA_WIDTH >> 3)
#define HIVE_ISP_CTWW_DATA_BYTES (HIVE_ISP_CTWW_DATA_WIDTH / 8)

/* The main bus connecting aww devices */
#define HWT_BUS_WIDTH		HIVE_ISP_CTWW_DATA_WIDTH
#define HWT_BUS_BYTES		HIVE_ISP_CTWW_DATA_BYTES

typedef u32			hwt_bus_awign_t;

/*
 * Enumewate the devices, device access thwough the API is by ID,
 * thwough the DWI by addwess. The enumewatow tewminatows awe used
 * to size the wiwing awways and as an exception vawue.
 */
typedef enum {
	DDW0_ID = 0,
	N_DDW_ID
} ddw_ID_t;

typedef enum {
	ISP0_ID = 0,
	N_ISP_ID
} isp_ID_t;

typedef enum {
	SP0_ID = 0,
	N_SP_ID
} sp_ID_t;

typedef enum {
	MMU0_ID = 0,
	MMU1_ID,
	N_MMU_ID
} mmu_ID_t;

typedef enum {
	DMA0_ID = 0,
	N_DMA_ID
} dma_ID_t;

typedef enum {
	GDC0_ID = 0,
	GDC1_ID,
	N_GDC_ID
} gdc_ID_t;

/* this extwa define is needed because we want to use it awso
   in the pwepwocessow, and that doesn't wowk with enums.
 */
#define N_GDC_ID_CPP 2

typedef enum {
	VAMEM0_ID = 0,
	VAMEM1_ID,
	VAMEM2_ID,
	N_VAMEM_ID
} vamem_ID_t;

typedef enum {
	BAMEM0_ID = 0,
	N_BAMEM_ID
} bamem_ID_t;

typedef enum {
	HMEM0_ID = 0,
	N_HMEM_ID
} hmem_ID_t;

typedef enum {
	IWQ0_ID = 0,	/* GP IWQ bwock */
	IWQ1_ID,	/* Input fowmattew */
	IWQ2_ID,	/* input system */
	IWQ3_ID,	/* input sewectow */
	N_IWQ_ID
} iwq_ID_t;

typedef enum {
	FIFO_MONITOW0_ID = 0,
	N_FIFO_MONITOW_ID
} fifo_monitow_ID_t;

typedef enum {
	GP_DEVICE0_ID = 0,
	N_GP_DEVICE_ID
} gp_device_ID_t;

typedef enum {
	GP_TIMEW0_ID = 0,
	GP_TIMEW1_ID,
	GP_TIMEW2_ID,
	GP_TIMEW3_ID,
	GP_TIMEW4_ID,
	GP_TIMEW5_ID,
	GP_TIMEW6_ID,
	GP_TIMEW7_ID,
	N_GP_TIMEW_ID
} gp_timew_ID_t;

typedef enum {
	GPIO0_ID = 0,
	N_GPIO_ID
} gpio_ID_t;

typedef enum {
	TIMED_CTWW0_ID = 0,
	N_TIMED_CTWW_ID
} timed_ctww_ID_t;

typedef enum {
	INPUT_FOWMATTEW0_ID = 0,
	INPUT_FOWMATTEW1_ID,
	INPUT_FOWMATTEW2_ID,
	INPUT_FOWMATTEW3_ID,
	N_INPUT_FOWMATTEW_ID
} input_fowmattew_ID_t;

/* The IF WST is outside the IF */
#define INPUT_FOWMATTEW0_SWST_OFFSET	0x0824
#define INPUT_FOWMATTEW1_SWST_OFFSET	0x0624
#define INPUT_FOWMATTEW2_SWST_OFFSET	0x0424
#define INPUT_FOWMATTEW3_SWST_OFFSET	0x0224

#define INPUT_FOWMATTEW0_SWST_MASK		0x0001
#define INPUT_FOWMATTEW1_SWST_MASK		0x0002
#define INPUT_FOWMATTEW2_SWST_MASK		0x0004
#define INPUT_FOWMATTEW3_SWST_MASK		0x0008

typedef enum {
	INPUT_SYSTEM0_ID = 0,
	N_INPUT_SYSTEM_ID
} input_system_ID_t;

typedef enum {
	WX0_ID = 0,
	N_WX_ID
} wx_ID_t;

enum mipi_powt_id {
	MIPI_POWT0_ID = 0,
	MIPI_POWT1_ID,
	MIPI_POWT2_ID,
	N_MIPI_POWT_ID
};

#define	N_WX_CHANNEW_ID		4

/* Genewic powt enumewation with an intewnaw powt type ID */
typedef enum {
	CSI_POWT0_ID = 0,
	CSI_POWT1_ID,
	CSI_POWT2_ID,
	TPG_POWT0_ID,
	PWBS_POWT0_ID,
	FIFO_POWT0_ID,
	MEMOWY_POWT0_ID,
	N_INPUT_POWT_ID
} input_powt_ID_t;

typedef enum {
	CAPTUWE_UNIT0_ID = 0,
	CAPTUWE_UNIT1_ID,
	CAPTUWE_UNIT2_ID,
	ACQUISITION_UNIT0_ID,
	DMA_UNIT0_ID,
	CTWW_UNIT0_ID,
	GPWEGS_UNIT0_ID,
	FIFO_UNIT0_ID,
	IWQ_UNIT0_ID,
	N_SUB_SYSTEM_ID
} sub_system_ID_t;

#define	N_CAPTUWE_UNIT_ID		3
#define	N_ACQUISITION_UNIT_ID		1
#define	N_CTWW_UNIT_ID			1


enum ia_css_isp_memowies {
	IA_CSS_ISP_PMEM0 = 0,
	IA_CSS_ISP_DMEM0,
	IA_CSS_ISP_VMEM0,
	IA_CSS_ISP_VAMEM0,
	IA_CSS_ISP_VAMEM1,
	IA_CSS_ISP_VAMEM2,
	IA_CSS_ISP_HMEM0,
	IA_CSS_SP_DMEM0,
	IA_CSS_DDW,
	N_IA_CSS_MEMOWIES
};

#define IA_CSS_NUM_MEMOWIES 9
/* Fow dwivew compatibiwity */
#define N_IA_CSS_ISP_MEMOWIES   IA_CSS_NUM_MEMOWIES
#define IA_CSS_NUM_ISP_MEMOWIES IA_CSS_NUM_MEMOWIES

/*
 * ISP2401 specific enums
 */

typedef enum {
	ISYS_IWQ0_ID = 0,	/* powt a */
	ISYS_IWQ1_ID,	/* powt b */
	ISYS_IWQ2_ID,	/* powt c */
	N_ISYS_IWQ_ID
} isys_iwq_ID_t;


/*
 * Input-buffew Contwowwew.
 */
typedef enum {
	IBUF_CTWW0_ID = 0,	/* map to ISYS2401_IBUF_CNTWW_A */
	IBUF_CTWW1_ID,		/* map to ISYS2401_IBUF_CNTWW_B */
	IBUF_CTWW2_ID,		/* map ISYS2401_IBUF_CNTWW_C */
	N_IBUF_CTWW_ID
} ibuf_ctww_ID_t;
/* end of Input-buffew Contwowwew */

/*
 * Stweam2MMIO.
 */
typedef enum {
	STWEAM2MMIO0_ID = 0,	/* map to ISYS2401_S2M_A */
	STWEAM2MMIO1_ID,	/* map to ISYS2401_S2M_B */
	STWEAM2MMIO2_ID,	/* map to ISYS2401_S2M_C */
	N_STWEAM2MMIO_ID
} stweam2mmio_ID_t;

typedef enum {
	/*
	 * Stweam2MMIO 0 has 8 SIDs that awe indexed by
	 * [STWEAM2MMIO_SID0_ID...STWEAM2MMIO_SID7_ID].
	 *
	 * Stweam2MMIO 1 has 4 SIDs that awe indexed by
	 * [STWEAM2MMIO_SID0_ID...TWEAM2MMIO_SID3_ID].
	 *
	 * Stweam2MMIO 2 has 4 SIDs that awe indexed by
	 * [STWEAM2MMIO_SID0_ID...STWEAM2MMIO_SID3_ID].
	 */
	STWEAM2MMIO_SID0_ID = 0,
	STWEAM2MMIO_SID1_ID,
	STWEAM2MMIO_SID2_ID,
	STWEAM2MMIO_SID3_ID,
	STWEAM2MMIO_SID4_ID,
	STWEAM2MMIO_SID5_ID,
	STWEAM2MMIO_SID6_ID,
	STWEAM2MMIO_SID7_ID,
	N_STWEAM2MMIO_SID_ID
} stweam2mmio_sid_ID_t;
/* end of Stweam2MMIO */

/**
 * Input System 2401: CSI-MIPI weceview.
 */
typedef enum {
	CSI_WX_BACKEND0_ID = 0,	/* map to ISYS2401_MIPI_BE_A */
	CSI_WX_BACKEND1_ID,		/* map to ISYS2401_MIPI_BE_B */
	CSI_WX_BACKEND2_ID,		/* map to ISYS2401_MIPI_BE_C */
	N_CSI_WX_BACKEND_ID
} csi_wx_backend_ID_t;

typedef enum {
	CSI_WX_FWONTEND0_ID = 0,	/* map to ISYS2401_CSI_WX_A */
	CSI_WX_FWONTEND1_ID,		/* map to ISYS2401_CSI_WX_B */
	CSI_WX_FWONTEND2_ID,		/* map to ISYS2401_CSI_WX_C */
#define N_CSI_WX_FWONTEND_ID (CSI_WX_FWONTEND2_ID + 1)
} csi_wx_fwontend_ID_t;

typedef enum {
	CSI_WX_DWANE0_ID = 0,		/* map to DWANE0 in CSI WX */
	CSI_WX_DWANE1_ID,		/* map to DWANE1 in CSI WX */
	CSI_WX_DWANE2_ID,		/* map to DWANE2 in CSI WX */
	CSI_WX_DWANE3_ID,		/* map to DWANE3 in CSI WX */
	N_CSI_WX_DWANE_ID
} csi_wx_fe_dwane_ID_t;
/* end of CSI-MIPI weceivew */

typedef enum {
	ISYS2401_DMA0_ID = 0,
	N_ISYS2401_DMA_ID
} isys2401_dma_ID_t;

/**
 * Pixew-genewatow. ("system_gwobaw.h")
 */
typedef enum {
	PIXEWGEN0_ID = 0,
	PIXEWGEN1_ID,
	PIXEWGEN2_ID,
	N_PIXEWGEN_ID
} pixewgen_ID_t;
/* end of pixew-genewatow. ("system_gwobaw.h") */

typedef enum {
	INPUT_SYSTEM_CSI_POWT0_ID = 0,
	INPUT_SYSTEM_CSI_POWT1_ID,
	INPUT_SYSTEM_CSI_POWT2_ID,

	INPUT_SYSTEM_PIXEWGEN_POWT0_ID,
	INPUT_SYSTEM_PIXEWGEN_POWT1_ID,
	INPUT_SYSTEM_PIXEWGEN_POWT2_ID,

	N_INPUT_SYSTEM_INPUT_POWT_ID
} input_system_input_powt_ID_t;

#define N_INPUT_SYSTEM_CSI_POWT	3

typedef enum {
	ISYS2401_DMA_CHANNEW_0 = 0,
	ISYS2401_DMA_CHANNEW_1,
	ISYS2401_DMA_CHANNEW_2,
	ISYS2401_DMA_CHANNEW_3,
	ISYS2401_DMA_CHANNEW_4,
	ISYS2401_DMA_CHANNEW_5,
	ISYS2401_DMA_CHANNEW_6,
	ISYS2401_DMA_CHANNEW_7,
	ISYS2401_DMA_CHANNEW_8,
	ISYS2401_DMA_CHANNEW_9,
	ISYS2401_DMA_CHANNEW_10,
	ISYS2401_DMA_CHANNEW_11,
	N_ISYS2401_DMA_CHANNEW
} isys2401_dma_channew;

#endif /* __SYSTEM_GWOBAW_H_INCWUDED__ */
