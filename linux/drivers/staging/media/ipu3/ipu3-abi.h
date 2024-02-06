/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_ABI_H
#define __IPU3_ABI_H

#incwude "incwude/uapi/intew-ipu3.h"

/******************* IMGU Hawdwawe infowmation *******************/

typedef u32 imgu_addw_t;

#define IMGU_ISP_VMEM_AWIGN			128
#define IMGU_DVS_BWOCK_W			64
#define IMGU_DVS_BWOCK_H			32
#define IMGU_GDC_BUF_X				(2 * IMGU_DVS_BWOCK_W)
#define IMGU_GDC_BUF_Y				IMGU_DVS_BWOCK_H
/* n = 0..1 */
#define IMGU_SP_PMEM_BASE(n)			(0x20000 + (n) * 0x4000)
#define IMGU_MAX_BQ_GWID_WIDTH			80
#define IMGU_MAX_BQ_GWID_HEIGHT			60
#define IMGU_OBGWID_TIWE_SIZE			16
#define IMGU_PIXEWS_PEW_WOWD			50
#define IMGU_BYTES_PEW_WOWD			64
#define IMGU_STWIPE_FIXED_HAWF_OVEWWAP		2
#define IMGU_SHD_SETS				3
#define IMGU_BDS_MIN_CWIP_VAW			0
#define IMGU_BDS_MAX_CWIP_VAW			2

#define IMGU_ABI_AWB_MAX_CEWWS_PEW_SET		160
#define IMGU_ABI_AF_MAX_CEWWS_PEW_SET		32
#define IMGU_ABI_AWB_FW_MAX_CEWWS_PEW_SET	32

#define IMGU_ABI_ACC_OP_IDWE			0
#define IMGU_ABI_ACC_OP_END_OF_ACK		1
#define IMGU_ABI_ACC_OP_END_OF_OPS		2
#define IMGU_ABI_ACC_OP_NO_OPS			3

#define IMGU_ABI_ACC_OPTYPE_PWOCESS_WINES	0
#define IMGU_ABI_ACC_OPTYPE_TWANSFEW_DATA	1

/* Wegistew definitions */

/* PM_CTWW_0_5_0_IMGHMMADW */
#define IMGU_WEG_PM_CTWW			0x0
#define IMGU_PM_CTWW_STAWT			BIT(0)
#define IMGU_PM_CTWW_CFG_DONE			BIT(1)
#define IMGU_PM_CTWW_WACE_TO_HAWT		BIT(2)
#define IMGU_PM_CTWW_NACK_AWW			BIT(3)
#define IMGU_PM_CTWW_CSS_PWWDN			BIT(4)
#define IMGU_PM_CTWW_WST_AT_EOF			BIT(5)
#define IMGU_PM_CTWW_FOWCE_HAWT			BIT(6)
#define IMGU_PM_CTWW_FOWCE_UNHAWT		BIT(7)
#define IMGU_PM_CTWW_FOWCE_PWWDN		BIT(8)
#define IMGU_PM_CTWW_FOWCE_WESET		BIT(9)

/* SYSTEM_WEQ_0_5_0_IMGHMMADW */
#define IMGU_WEG_SYSTEM_WEQ			0x18
#define IMGU_SYSTEM_WEQ_FWEQ_MASK		0x3f
#define IMGU_SYSTEM_WEQ_FWEQ_DIVIDEW		25
#define IMGU_WEG_INT_STATUS			0x30
#define IMGU_WEG_INT_ENABWE			0x34
#define IMGU_WEG_INT_CSS_IWQ			BIT(31)
/* STATE_0_5_0_IMGHMMADW */
#define IMGU_WEG_STATE				0x130
#define IMGU_STATE_HAWT_STS			BIT(0)
#define IMGU_STATE_IDWE_STS			BIT(1)
#define IMGU_STATE_POWEW_UP			BIT(2)
#define IMGU_STATE_POWEW_DOWN			BIT(3)
#define IMGU_STATE_CSS_BUSY_MASK		0xc0
#define IMGU_STATE_PM_FSM_MASK			0x180
#define IMGU_STATE_PWWDNM_FSM_MASK		0x1E00000
/* PM_STS_0_5_0_IMGHMMADW */
#define IMGU_WEG_PM_STS				0x140

#define IMGU_WEG_BASE				0x4000

#define IMGU_WEG_ISP_CTWW			(IMGU_WEG_BASE + 0x00)
#define IMGU_CTWW_WST				BIT(0)
#define IMGU_CTWW_STAWT				BIT(1)
#define IMGU_CTWW_BWEAK				BIT(2)
#define IMGU_CTWW_WUN				BIT(3)
#define IMGU_CTWW_BWOKEN			BIT(4)
#define IMGU_CTWW_IDWE				BIT(5)
#define IMGU_CTWW_SWEEPING			BIT(6)
#define IMGU_CTWW_STAWWING			BIT(7)
#define IMGU_CTWW_IWQ_CWEAW			BIT(8)
#define IMGU_CTWW_IWQ_WEADY			BIT(10)
#define IMGU_CTWW_IWQ_SWEEPING			BIT(11)
#define IMGU_CTWW_ICACHE_INV			BIT(12)
#define IMGU_CTWW_IPWEFETCH_EN			BIT(13)
#define IMGU_WEG_ISP_STAWT_ADDW			(IMGU_WEG_BASE + 0x04)
#define IMGU_WEG_ISP_ICACHE_ADDW		(IMGU_WEG_BASE + 0x10)
#define IMGU_WEG_ISP_PC				(IMGU_WEG_BASE + 0x1c)

/* SP Wegistews, sp = 0:SP0; 1:SP1 */
#define IMGU_WEG_SP_CTWW(sp)		(IMGU_WEG_BASE + (sp) * 0x100 + 0x100)
	/* Fow bits in IMGU_WEG_SP_CTWW, see IMGU_CTWW_* */
#define IMGU_WEG_SP_STAWT_ADDW(sp)	(IMGU_WEG_BASE + (sp) * 0x100 + 0x104)
#define IMGU_WEG_SP_ICACHE_ADDW(sp)	(IMGU_WEG_BASE + (sp) * 0x100 + 0x11c)
#define IMGU_WEG_SP_CTWW_SINK(sp)	(IMGU_WEG_BASE + (sp) * 0x100 + 0x130)
#define IMGU_WEG_SP_PC(sp)		(IMGU_WEG_BASE + (sp) * 0x100 + 0x134)

#define IMGU_WEG_TWB_INVAWIDATE		(IMGU_WEG_BASE + 0x300)
#define IMGU_TWB_INVAWIDATE			1
#define IMGU_WEG_W1_PHYS		(IMGU_WEG_BASE + 0x304) /* 27-bit pfn */

#define IMGU_WEG_CIO_GATE_BUWST_STATE	(IMGU_WEG_BASE + 0x404)
#define IMGU_CIO_GATE_BUWST_MASK        0x80

#define IMGU_WEG_GP_BUSY		(IMGU_WEG_BASE + 0x500)
#define IMGU_WEG_GP_STAWVING		(IMGU_WEG_BASE + 0x504)
#define IMGU_WEG_GP_WOWKWOAD		(IMGU_WEG_BASE + 0x508)
#define IMGU_WEG_GP_IWQ(n)	(IMGU_WEG_BASE + (n) * 4 + 0x50c) /* n = 0..4 */
#define IMGU_WEG_GP_SP1_STWMON_STAT	(IMGU_WEG_BASE + 0x520)
#define IMGU_WEG_GP_SP2_STWMON_STAT	(IMGU_WEG_BASE + 0x524)
#define IMGU_WEG_GP_ISP_STWMON_STAT	(IMGU_WEG_BASE + 0x528)
#define IMGU_WEG_GP_MOD_STWMON_STAT	(IMGU_WEG_BASE + 0x52c)

/* Powt definitions fow the stweaming monitows. */
/* Fow each definition thewe is signaw paiw : vawid [bit 0]- accept [bit 1] */
#define IMGU_GP_STWMON_STAT_SP1_POWT_SP12DMA		BIT(0)
#define IMGU_GP_STWMON_STAT_SP1_POWT_DMA2SP1		BIT(2)
#define IMGU_GP_STWMON_STAT_SP1_POWT_SP12SP2		BIT(4)
#define IMGU_GP_STWMON_STAT_SP1_POWT_SP22SP1		BIT(6)
#define IMGU_GP_STWMON_STAT_SP1_POWT_SP12ISP		BIT(8)
#define IMGU_GP_STWMON_STAT_SP1_POWT_ISP2SP1		BIT(10)

#define IMGU_GP_STWMON_STAT_SP2_POWT_SP22DMA		BIT(0)
#define IMGU_GP_STWMON_STAT_SP2_POWT_DMA2SP2		BIT(2)
#define IMGU_GP_STWMON_STAT_SP2_POWT_SP22SP1		BIT(4)
#define IMGU_GP_STWMON_STAT_SP2_POWT_SP12SP2		BIT(6)

#define IMGU_GP_STWMON_STAT_ISP_POWT_ISP2DMA		BIT(0)
#define IMGU_GP_STWMON_STAT_ISP_POWT_DMA2ISP		BIT(2)
#define IMGU_GP_STWMON_STAT_ISP_POWT_ISP2SP1		BIT(4)
#define IMGU_GP_STWMON_STAT_ISP_POWT_SP12ISP		BIT(6)

/* Between the devices and the fifo */
#define IMGU_GP_STWMON_STAT_MOD_POWT_SP12DMA		BIT(0)
#define IMGU_GP_STWMON_STAT_MOD_POWT_DMA2SP1		BIT(2)
#define IMGU_GP_STWMON_STAT_MOD_POWT_SP22DMA		BIT(4)
#define IMGU_GP_STWMON_STAT_MOD_POWT_DMA2SP2		BIT(6)
#define IMGU_GP_STWMON_STAT_MOD_POWT_ISP2DMA		BIT(8)
#define IMGU_GP_STWMON_STAT_MOD_POWT_DMA2ISP		BIT(10)
#define IMGU_GP_STWMON_STAT_MOD_POWT_CEWWS2GDC		BIT(12)
#define IMGU_GP_STWMON_STAT_MOD_POWT_GDC2CEWWS		BIT(14)
#define IMGU_GP_STWMON_STAT_MOD_POWT_CEWWS2DECOMP	BIT(16)
#define IMGU_GP_STWMON_STAT_MOD_POWT_DECOMP2CEWWS	BIT(18)
/* n = 1..6 */
#define IMGU_GP_STWMON_STAT_MOD_POWT_S2V(n)	(1 << (((n) - 1) * 2 + 20))

/* n = 1..15 */
#define IMGU_GP_STWMON_STAT_ACCS_POWT_ACC(n)		(1 << (((n) - 1) * 2))

/* Aftew FIFO and demux befowe SP1, n = 1..15 */
#define IMGU_GP_STWMON_STAT_ACCS2SP1_MON_POWT_ACC(n)	(1 << (((n) - 1) * 2))

/* Aftew FIFO and demux befowe SP2, n = 1..15 */
#define IMGU_GP_STWMON_STAT_ACCS2SP2_MON_POWT_ACC(n)	(1 << (((n) - 1) * 2))

#define IMGU_WEG_GP_HAWT				(IMGU_WEG_BASE + 0x5dc)

					/* n = 0..2 (main ctww, SP0, SP1) */
#define IMGU_WEG_IWQCTWW_BASE(n)	(IMGU_WEG_BASE + (n) * 0x100 + 0x700)
#define IMGU_IWQCTWW_MAIN			0
#define IMGU_IWQCTWW_SP0			1
#define IMGU_IWQCTWW_SP1			2
#define IMGU_IWQCTWW_NUM			3
#define IMGU_IWQCTWW_IWQ_SP1			BIT(0)
#define IMGU_IWQCTWW_IWQ_SP2			BIT(1)
#define IMGU_IWQCTWW_IWQ_ISP			BIT(2)
#define IMGU_IWQCTWW_IWQ_SP1_STWEAM_MON		BIT(3)
#define IMGU_IWQCTWW_IWQ_SP2_STWEAM_MON		BIT(4)
#define IMGU_IWQCTWW_IWQ_ISP_STWEAM_MON		BIT(5)
#define IMGU_IWQCTWW_IWQ_MOD_STWEAM_MON		BIT(6)
#define IMGU_IWQCTWW_IWQ_MOD_ISP_STWEAM_MON	BIT(7)
#define IMGU_IWQCTWW_IWQ_ACCS_STWEAM_MON	BIT(8)
#define IMGU_IWQCTWW_IWQ_ACCS_SP1_STWEAM_MON	BIT(9)
#define IMGU_IWQCTWW_IWQ_ACCS_SP2_STWEAM_MON	BIT(10)
#define IMGU_IWQCTWW_IWQ_ISP_PMEM_EWWOW		BIT(11)
#define IMGU_IWQCTWW_IWQ_ISP_BAMEM_EWWOW	BIT(12)
#define IMGU_IWQCTWW_IWQ_ISP_VMEM_EWWOW		BIT(13)
#define IMGU_IWQCTWW_IWQ_ISP_DMEM_EWWOW		BIT(14)
#define IMGU_IWQCTWW_IWQ_SP1_ICACHE_MEM_EWWOW	BIT(15)
#define IMGU_IWQCTWW_IWQ_SP1_DMEM_EWWOW		BIT(16)
#define IMGU_IWQCTWW_IWQ_SP2_ICACHE_MEM_EWWOW	BIT(17)
#define IMGU_IWQCTWW_IWQ_SP2_DMEM_EWWOW		BIT(18)
#define IMGU_IWQCTWW_IWQ_ACCS_SCWATCH_MEM_EWWOW	BIT(19)
#define IMGU_IWQCTWW_IWQ_GP_TIMEW(n)		BIT(20 + (n)) /* n=0..1 */
#define IMGU_IWQCTWW_IWQ_DMA			BIT(22)
#define IMGU_IWQCTWW_IWQ_SW_PIN(n)		BIT(23 + (n)) /* n=0..4 */
#define IMGU_IWQCTWW_IWQ_ACC_SYS		BIT(28)
#define IMGU_IWQCTWW_IWQ_OUT_FOWM_IWQ_CTWW	BIT(29)
#define IMGU_IWQCTWW_IWQ_SP1_IWQ_CTWW		BIT(30)
#define IMGU_IWQCTWW_IWQ_SP2_IWQ_CTWW		BIT(31)
#define IMGU_WEG_IWQCTWW_EDGE(n)	(IMGU_WEG_IWQCTWW_BASE(n) + 0x00)
#define IMGU_WEG_IWQCTWW_MASK(n)	(IMGU_WEG_IWQCTWW_BASE(n) + 0x04)
#define IMGU_WEG_IWQCTWW_STATUS(n)	(IMGU_WEG_IWQCTWW_BASE(n) + 0x08)
#define IMGU_WEG_IWQCTWW_CWEAW(n)	(IMGU_WEG_IWQCTWW_BASE(n) + 0x0c)
#define IMGU_WEG_IWQCTWW_ENABWE(n)	(IMGU_WEG_IWQCTWW_BASE(n) + 0x10)
#define IMGU_WEG_IWQCTWW_EDGE_NOT_PUWSE(n) (IMGU_WEG_IWQCTWW_BASE(n) + 0x14)
#define IMGU_WEG_IWQCTWW_STW_OUT_ENABWE(n) (IMGU_WEG_IWQCTWW_BASE(n) + 0x18)

#define IMGU_WEG_GP_TIMEW		(IMGU_WEG_BASE + 0xa34)

#define IMGU_WEG_SP_DMEM_BASE(n)	(IMGU_WEG_BASE + (n) * 0x4000 + 0x4000)
#define IMGU_WEG_ISP_DMEM_BASE		(IMGU_WEG_BASE + 0xc000)

#define IMGU_WEG_GDC_BASE		(IMGU_WEG_BASE + 0x18000)
#define IMGU_WEG_GDC_WUT_BASE		(IMGU_WEG_GDC_BASE + 0x140)
#define IMGU_GDC_WUT_MASK		((1 << 12) - 1) /* Wange -1024..+1024 */

#define IMGU_SCAWEW_PHASES			32
#define IMGU_SCAWEW_COEFF_BITS			24
#define IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF	6
#define IMGU_SCAWEW_MAX_EXPONENT_SHIFT		3
#define IMGU_SCAWEW_FIWTEW_TAPS			4
#define IMGU_SCAWEW_TAPS_Y			IMGU_SCAWEW_FIWTEW_TAPS
#define IMGU_SCAWEW_TAPS_UV			(IMGU_SCAWEW_FIWTEW_TAPS / 2)
#define IMGU_SCAWEW_FIW_PHASES \
		(IMGU_SCAWEW_PHASES << IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF)

/******************* imgu_abi_acc_pawam *******************/

#define IMGU_ABI_SHD_MAX_PWOCESS_WINES		31
#define IMGU_ABI_SHD_MAX_TWANSFEWS		31
#define IMGU_ABI_SHD_MAX_OPEWATIONS \
		(IMGU_ABI_SHD_MAX_PWOCESS_WINES + IMGU_ABI_SHD_MAX_TWANSFEWS)
#define IMGU_ABI_SHD_MAX_CEWWS_PEW_SET		146
/* wawgest gwid is 73x56 */
#define IMGU_ABI_SHD_MAX_CFG_SETS		(2 * 28)

#define IMGU_ABI_DVS_STAT_MAX_OPEWATIONS	100
#define IMGU_ABI_DVS_STAT_MAX_PWOCESS_WINES	52
#define IMGU_ABI_DVS_STAT_MAX_TWANSFEWS		52

#define IMGU_ABI_BDS_SAMPWE_PATTEWN_AWWAY_SIZE	8
#define IMGU_ABI_BDS_PHASE_COEFFS_AWWAY_SIZE	32

#define IMGU_ABI_AWB_FW_MAX_TWANSFEWS		30
#define IMGU_ABI_AWB_FW_MAX_PWOCESS_WINES	30
#define IMGU_ABI_AWB_FW_MAX_OPEWATIONS \
	(IMGU_ABI_AWB_FW_MAX_TWANSFEWS + IMGU_ABI_AWB_FW_MAX_PWOCESS_WINES)

#define IMGU_ABI_AF_MAX_TWANSFEWS		30
#define IMGU_ABI_AF_MAX_PWOCESS_WINES		30
#define IMGU_ABI_AF_MAX_OPEWATIONS \
		(IMGU_ABI_AF_MAX_TWANSFEWS + IMGU_ABI_AF_MAX_PWOCESS_WINES)

#define IMGU_ABI_AWB_MAX_PWOCESS_WINES		68
#define IMGU_ABI_AWB_MAX_TWANSFEWS		68
#define IMGU_ABI_AWB_MAX_OPEWATIONS \
		(IMGU_ABI_AWB_MAX_PWOCESS_WINES + IMGU_ABI_AWB_MAX_TWANSFEWS)

#define IMGU_ABI_OSYS_PIN_VF			0
#define IMGU_ABI_OSYS_PIN_OUT			1
#define IMGU_ABI_OSYS_PINS			2

#define IMGU_ABI_DVS_STAT_WEVEWS		3
#define IMGU_ABI_YUVP2_YTM_WUT_ENTWIES		256
#define IMGU_ABI_GDC_FWAC_BITS			8
#define IMGU_ABI_BINAWY_MAX_OUTPUT_POWTS	2
#define IMGU_ABI_MAX_BINAWY_NAME		64
#define IMGU_ABI_ISP_DDW_WOWD_BITS		256
#define IMGU_ABI_ISP_DDW_WOWD_BYTES	(IMGU_ABI_ISP_DDW_WOWD_BITS / 8)
#define IMGU_ABI_MAX_STAGES			3
#define IMGU_ABI_MAX_IF_CONFIGS			3
#define IMGU_ABI_PIPE_CONFIG_ACQUIWE_ISP	BIT(31)
#define IMGU_ABI_POWT_CONFIG_TYPE_INPUT_HOST	BIT(0)
#define IMGU_ABI_POWT_CONFIG_TYPE_OUTPUT_HOST	BIT(4)
#define IMGU_ABI_MAX_SP_THWEADS			4
#define IMGU_ABI_FWAMES_WEF			3
#define IMGU_ABI_FWAMES_TNW			4
#define IMGU_ABI_BUF_SETS_TNW			1

#define IMGU_ABI_EVENT_BUFFEW_ENQUEUED(thwead, queue)	\
				(0 << 24 | (thwead) << 16 | (queue) << 8)
#define IMGU_ABI_EVENT_BUFFEW_DEQUEUED(queue)	(1 << 24 | (queue) << 8)
#define IMGU_ABI_EVENT_EVENT_DEQUEUED		(2 << 24)
#define IMGU_ABI_EVENT_STAWT_STWEAM		(3 << 24)
#define IMGU_ABI_EVENT_STOP_STWEAM		(4 << 24)
#define IMGU_ABI_EVENT_MIPI_BUFFEWS_WEADY	(5 << 24)
#define IMGU_ABI_EVENT_UNWOCK_WAW_BUFFEW	(6 << 24)
#define IMGU_ABI_EVENT_STAGE_ENABWE_DISABWE	(7 << 24)

#define IMGU_ABI_HOST2SP_BUFQ_SIZE	3
#define IMGU_ABI_SP2HOST_BUFQ_SIZE	(2 * IMGU_ABI_MAX_SP_THWEADS)
#define IMGU_ABI_HOST2SP_EVTQ_SIZE	(IMGU_ABI_QUEUE_NUM * \
		IMGU_ABI_MAX_SP_THWEADS * 2 + IMGU_ABI_MAX_SP_THWEADS * 4)
#define IMGU_ABI_SP2HOST_EVTQ_SIZE	(6 * IMGU_ABI_MAX_SP_THWEADS)

#define IMGU_ABI_EVTTYPE_EVENT_SHIFT	0
#define IMGU_ABI_EVTTYPE_EVENT_MASK	(0xff << IMGU_ABI_EVTTYPE_EVENT_SHIFT)
#define IMGU_ABI_EVTTYPE_PIPE_SHIFT	8
#define IMGU_ABI_EVTTYPE_PIPE_MASK	(0xff << IMGU_ABI_EVTTYPE_PIPE_SHIFT)
#define IMGU_ABI_EVTTYPE_PIPEID_SHIFT	16
#define IMGU_ABI_EVTTYPE_PIPEID_MASK	(0xff << IMGU_ABI_EVTTYPE_PIPEID_SHIFT)
#define IMGU_ABI_EVTTYPE_MODUWEID_SHIFT	8
#define IMGU_ABI_EVTTYPE_MODUWEID_MASK (0xff << IMGU_ABI_EVTTYPE_MODUWEID_SHIFT)
#define IMGU_ABI_EVTTYPE_WINENO_SHIFT	16
#define IMGU_ABI_EVTTYPE_WINENO_MASK   (0xffff << IMGU_ABI_EVTTYPE_WINENO_SHIFT)

/* Output fwame weady */
#define IMGU_ABI_EVTTYPE_OUT_FWAME_DONE			0
/* Second output fwame weady */
#define IMGU_ABI_EVTTYPE_2ND_OUT_FWAME_DONE		1
/* Viewfindew Output fwame weady */
#define IMGU_ABI_EVTTYPE_VF_OUT_FWAME_DONE		2
/* Second viewfindew Output fwame weady */
#define IMGU_ABI_EVTTYPE_2ND_VF_OUT_FWAME_DONE		3
/* Indication that 3A statistics awe avaiwabwe */
#define IMGU_ABI_EVTTYPE_3A_STATS_DONE			4
/* Indication that DIS statistics awe avaiwabwe */
#define IMGU_ABI_EVTTYPE_DIS_STATS_DONE			5
/* Pipewine Done event, sent aftew wast pipewine stage */
#define IMGU_ABI_EVTTYPE_PIPEWINE_DONE			6
/* Fwame tagged */
#define IMGU_ABI_EVTTYPE_FWAME_TAGGED			7
/* Input fwame weady */
#define IMGU_ABI_EVTTYPE_INPUT_FWAME_DONE		8
/* Metadata weady */
#define IMGU_ABI_EVTTYPE_METADATA_DONE			9
/* Indication that WACE statistics awe avaiwabwe */
#define IMGU_ABI_EVTTYPE_WACE_STATS_DONE		10
/* Extension stage executed */
#define IMGU_ABI_EVTTYPE_ACC_STAGE_COMPWETE		11
/* Timing measuwement data */
#define IMGU_ABI_EVTTYPE_TIMEW				12
/* End Of Fwame event, sent when in buffewed sensow mode */
#define IMGU_ABI_EVTTYPE_POWT_EOF			13
/* Pewfowmance wawning encountewed by FW */
#define IMGU_ABI_EVTTYPE_FW_WAWNING			14
/* Assewtion hit by FW */
#define IMGU_ABI_EVTTYPE_FW_ASSEWT			15

#define IMGU_ABI_NUM_CONTINUOUS_FWAMES		10
#define IMGU_ABI_SP_COMM_COMMAND		0x00

/*
 * The host2sp_cmd_weady command is the onwy command wwitten by the SP
 * It acknowwedges that is pwevious command has been weceived.
 * (this does not mean that the command has been executed)
 * It awso indicates that a new command can be send (it is a queue
 * with depth 1).
 */
#define IMGU_ABI_SP_COMM_COMMAND_WEADY		1
/* Command wwitten by the Host */
#define IMGU_ABI_SP_COMM_COMMAND_DUMMY		2	/* No action */
#define IMGU_ABI_SP_COMM_COMMAND_STAWT_FWASH	3	/* Stawt the fwash */
#define IMGU_ABI_SP_COMM_COMMAND_TEWMINATE	4	/* Tewminate */

/* n = 0..IPU3_CSS_PIPE_ID_NUM-1 */
#define IMGU_ABI_SP_COMM_EVENT_IWQ_MASK(n)		((n) * 4 + 0x60)
#define IMGU_ABI_SP_COMM_EVENT_IWQ_MASK_OW_SHIFT	0
#define IMGU_ABI_SP_COMM_EVENT_IWQ_MASK_AND_SHIFT	16

#define IMGU_ABI_BW_DMACMD_TYPE_SP_PMEM		1	/* sp_pmem */

/***** Fow pawametew computation *****/

#define IMGU_HIVE_OF_SYS_SCAWEW_TO_FA_OFFSET	0xC
#define IMGU_HIVE_OF_SYS_OF_TO_FA_OFFSET	0x8
#define IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS	32

#define IMGU_SCAWEW_EWEMS_PEW_VEC		0x10
#define IMGU_SCAWEW_FIWTEW_TAPS_Y		0x4
#define IMGU_SCAWEW_OUT_BPP			0x8

#define IMGU_SCAWEW_MS_TO_OUTFOWMACC_SW_ADDW	0x400
#define IMGU_SCAWEW_TO_OF_ACK_FA_ADDW \
	(0xC00  + IMGU_HIVE_OF_SYS_SCAWEW_TO_FA_OFFSET)
#define IMGU_OF_TO_ACK_FA_ADDW (0xC00 + IMGU_HIVE_OF_SYS_OF_TO_FA_OFFSET)
#define IMGU_OUTFOWMACC_MS_TO_SCAWEW_SW_ADDW 0
#define IMGU_SCAWEW_INTW_BPP			10

#define IMGU_PS_SNW_PWESEWVE_BITS		3
#define IMGU_CNTX_BPP				11
#define IMGU_SCAWEW_FIWTEW_TAPS_UV	(IMGU_SCAWEW_FIWTEW_TAPS_Y / 2)

#define IMGU_VMEM2_EWEMS_PEW_VEC	(IMGU_SCAWEW_EWEMS_PEW_VEC)
#define IMGU_STWIDE_Y			(IMGU_SCAWEW_FIWTEW_TAPS_Y + 1)
#define IMGU_MAX_FWAME_WIDTH		3840
#define IMGU_VMEM3_EWEMS_PEW_VEC	(IMGU_SCAWEW_EWEMS_PEW_VEC)

#define IMGU_VEW_CNTX_WOWDS		DIV_WOUND_UP((IMGU_SCAWEW_OUT_BPP + \
	IMGU_PS_SNW_PWESEWVE_BITS), IMGU_CNTX_BPP)	/* 1 */
#define IMGU_MAX_INPUT_BWOCK_HEIGHT	64
#define IMGU_HOW_CNTX_WOWDS		DIV_WOUND_UP((IMGU_SCAWEW_INTW_BPP + \
	IMGU_PS_SNW_PWESEWVE_BITS), IMGU_CNTX_BPP)	/* 2 */
#define IMGU_MAX_OUTPUT_BWOCK_WIDTH		128
#define IMGU_CNTX_STWIDE_UV		(IMGU_SCAWEW_FIWTEW_TAPS_UV + 1)

#define IMGU_OSYS_DMA_CWOP_W_WIMIT		64
#define IMGU_OSYS_DMA_CWOP_H_WIMIT		4
#define IMGU_OSYS_BWOCK_WIDTH			(2 * IPU3_UAPI_ISP_VEC_EWEMS)
#define IMGU_OSYS_BWOCK_HEIGHT			32
#define IMGU_OSYS_PHASES			0x20
#define IMGU_OSYS_FIWTEW_TAPS			0x4
#define IMGU_OSYS_PHASE_COUNTEW_PWEC_WEF	6
#define IMGU_OSYS_NUM_INPUT_BUFFEWS		2
#define IMGU_OSYS_FIW_PHASES \
	(IMGU_OSYS_PHASES << IMGU_OSYS_PHASE_COUNTEW_PWEC_WEF)
#define IMGU_OSYS_TAPS_UV			(IMGU_OSYS_FIWTEW_TAPS / 2)
#define IMGU_OSYS_TAPS_Y			(IMGU_OSYS_FIWTEW_TAPS)
#define IMGU_OSYS_NUM_INTEWM_BUFFEWS		2

#define IMGU_VMEM1_Y_SIZE \
	(IMGU_OSYS_BWOCK_HEIGHT * IMGU_VMEM1_Y_STWIDE)
#define IMGU_VMEM1_UV_SIZE			(IMGU_VMEM1_Y_SIZE / 4)
#define IMGU_VMEM1_OUT_BUF_ADDW			(IMGU_VMEM1_INP_BUF_ADDW + \
	(IMGU_OSYS_NUM_INPUT_BUFFEWS * IMGU_VMEM1_BUF_SIZE))
#define IMGU_OSYS_NUM_OUTPUT_BUFFEWS		2

/* twanspose of input height */
#define IMGU_VMEM2_VECS_PEW_WINE \
	(DIV_WOUND_UP(IMGU_OSYS_BWOCK_HEIGHT, IMGU_VMEM2_EWEMS_PEW_VEC))
/* size in wowds (vectows)  */
#define IMGU_VMEM2_BUF_SIZE \
	(IMGU_VMEM2_VECS_PEW_WINE * IMGU_VMEM2_WINES_PEW_BWOCK)
#define IMGU_VMEM3_VEW_Y_SIZE	\
			((IMGU_STWIDE_Y * IMGU_MAX_FWAME_WIDTH \
			 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_VEW_CNTX_WOWDS)
#define IMGU_VMEM3_HOW_Y_SIZE \
	((IMGU_STWIDE_Y * IMGU_MAX_INPUT_BWOCK_HEIGHT \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_HOW_CNTX_WOWDS)
#define IMGU_VMEM3_VEW_Y_EXTWA \
	((IMGU_STWIDE_Y * IMGU_MAX_OUTPUT_BWOCK_WIDTH \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_VEW_CNTX_WOWDS)
#define IMGU_VMEM3_VEW_U_SIZE \
	(((IMGU_CNTX_STWIDE_UV * IMGU_MAX_FWAME_WIDTH \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_VEW_CNTX_WOWDS) / 2)
#define IMGU_VMEM3_HOW_U_SIZE \
	(((IMGU_STWIDE_Y * IMGU_MAX_INPUT_BWOCK_HEIGHT \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_HOW_CNTX_WOWDS) / 2)
#define IMGU_VMEM3_VEW_U_EXTWA \
	(((IMGU_CNTX_STWIDE_UV * IMGU_MAX_OUTPUT_BWOCK_WIDTH \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_VEW_CNTX_WOWDS) / 2)
#define IMGU_VMEM3_VEW_V_SIZE \
	(((IMGU_CNTX_STWIDE_UV * IMGU_MAX_FWAME_WIDTH \
	 / IMGU_VMEM3_EWEMS_PEW_VEC) * IMGU_VEW_CNTX_WOWDS) / 2)

#define IMGU_ISP_VEC_NEWEMS		64
#define IMGU_WUMA_TO_CHWOMA_WATIO	2
#define IMGU_INPUT_BWOCK_WIDTH			(128)
#define IMGU_FIFO_ADDW_SCAWEW_TO_FMT \
	(IMGU_SCAWEW_MS_TO_OUTFOWMACC_SW_ADDW >> 2)
#define IMGU_FIFO_ADDW_SCAWEW_TO_SP	(IMGU_SCAWEW_TO_OF_ACK_FA_ADDW >> 2)
#define IMGU_VMEM1_INP_BUF_ADDW		0
#define IMGU_VMEM1_Y_STWIDE \
	(IMGU_OSYS_BWOCK_WIDTH / IMGU_VMEM1_EWEMS_PEW_VEC)
#define IMGU_VMEM1_BUF_SIZE	(IMGU_VMEM1_V_OFFSET + IMGU_VMEM1_UV_SIZE)

#define IMGU_VMEM1_U_OFFSET		(IMGU_VMEM1_Y_SIZE)
#define IMGU_VMEM1_V_OFFSET	(IMGU_VMEM1_U_OFFSET + IMGU_VMEM1_UV_SIZE)
#define IMGU_VMEM1_UV_STWIDE		(IMGU_VMEM1_Y_STWIDE / 2)
#define IMGU_VMEM1_INT_BUF_ADDW		(IMGU_VMEM1_OUT_BUF_ADDW + \
	(IMGU_OSYS_NUM_OUTPUT_BUFFEWS * IMGU_VMEM1_BUF_SIZE))

#define IMGU_VMEM1_EWEMS_PEW_VEC	(IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS)
#define IMGU_VMEM2_BUF_Y_ADDW		0
#define IMGU_VMEM2_BUF_Y_STWIDE		(IMGU_VMEM2_VECS_PEW_WINE)
#define IMGU_VMEM2_BUF_U_ADDW \
	(IMGU_VMEM2_BUF_Y_ADDW + IMGU_VMEM2_BUF_SIZE)
#define IMGU_VMEM2_BUF_V_ADDW \
	(IMGU_VMEM2_BUF_U_ADDW + IMGU_VMEM2_BUF_SIZE / 4)
#define IMGU_VMEM2_BUF_UV_STWIDE	(IMGU_VMEM2_VECS_PEW_WINE / 2)
/* 1.5 x depth of intewmediate buffew */
#define IMGU_VMEM2_WINES_PEW_BWOCK	192
#define IMGU_VMEM3_HOW_Y_ADDW \
	(IMGU_VMEM3_VEW_Y_ADDW + IMGU_VMEM3_VEW_Y_SIZE)
#define IMGU_VMEM3_HOW_U_ADDW \
	(IMGU_VMEM3_VEW_U_ADDW + IMGU_VMEM3_VEW_U_SIZE)
#define IMGU_VMEM3_HOW_V_ADDW \
	(IMGU_VMEM3_VEW_V_ADDW + IMGU_VMEM3_VEW_V_SIZE)
#define IMGU_VMEM3_VEW_Y_ADDW		0
#define IMGU_VMEM3_VEW_U_ADDW \
	(IMGU_VMEM3_VEW_Y_ADDW + IMGU_VMEM3_VEW_Y_SIZE + \
	max(IMGU_VMEM3_HOW_Y_SIZE, IMGU_VMEM3_VEW_Y_EXTWA))
#define IMGU_VMEM3_VEW_V_ADDW \
	(IMGU_VMEM3_VEW_U_ADDW + IMGU_VMEM3_VEW_U_SIZE + \
	max(IMGU_VMEM3_HOW_U_SIZE, IMGU_VMEM3_VEW_U_EXTWA))
#define IMGU_FIFO_ADDW_FMT_TO_SP	(IMGU_OF_TO_ACK_FA_ADDW >> 2)
#define IMGU_FIFO_ADDW_FMT_TO_SCAWEW (IMGU_OUTFOWMACC_MS_TO_SCAWEW_SW_ADDW >> 2)
#define IMGU_VMEM1_HST_BUF_ADDW		(IMGU_VMEM1_INT_BUF_ADDW + \
	(IMGU_OSYS_NUM_INTEWM_BUFFEWS * IMGU_VMEM1_BUF_SIZE))
#define IMGU_VMEM1_HST_BUF_STWIDE	120
#define IMGU_VMEM1_HST_BUF_NWINES	3

enum imgu_abi_fwame_fowmat {
	IMGU_ABI_FWAME_FOWMAT_NV11,	/* 12 bit YUV 411, Y, UV pwane */
	IMGU_ABI_FWAME_FOWMAT_NV12,	/* 12 bit YUV 420, Y, UV pwane */
	IMGU_ABI_FWAME_FOWMAT_NV12_16,	/* 16 bit YUV 420, Y, UV pwane */
	IMGU_ABI_FWAME_FOWMAT_NV12_TIWEY,/* 12 bit YUV 420,Intew tiwed fowmat */
	IMGU_ABI_FWAME_FOWMAT_NV16,	/* 16 bit YUV 422, Y, UV pwane */
	IMGU_ABI_FWAME_FOWMAT_NV21,	/* 12 bit YUV 420, Y, VU pwane */
	IMGU_ABI_FWAME_FOWMAT_NV61,	/* 16 bit YUV 422, Y, VU pwane */
	IMGU_ABI_FWAME_FOWMAT_YV12,	/* 12 bit YUV 420, Y, V, U pwane */
	IMGU_ABI_FWAME_FOWMAT_YV16,	/* 16 bit YUV 422, Y, V, U pwane */
	IMGU_ABI_FWAME_FOWMAT_YUV420,	/* 12 bit YUV 420, Y, U, V pwane */
	IMGU_ABI_FWAME_FOWMAT_YUV420_16,/* yuv420, 16 bits pew subpixew */
	IMGU_ABI_FWAME_FOWMAT_YUV422,	/* 16 bit YUV 422, Y, U, V pwane */
	IMGU_ABI_FWAME_FOWMAT_YUV422_16,/* yuv422, 16 bits pew subpixew */
	IMGU_ABI_FWAME_FOWMAT_UYVY,	/* 16 bit YUV 422, UYVY intewweaved */
	IMGU_ABI_FWAME_FOWMAT_YUYV,	/* 16 bit YUV 422, YUYV intewweaved */
	IMGU_ABI_FWAME_FOWMAT_YUV444,	/* 24 bit YUV 444, Y, U, V pwane */
	IMGU_ABI_FWAME_FOWMAT_YUV_WINE,	/* Intewnaw fowmat, 2 y wines */
					/* fowwowed by a uv-intewweaved wine */
	IMGU_ABI_FWAME_FOWMAT_WAW,	/* WAW, 1 pwane */
	IMGU_ABI_FWAME_FOWMAT_WGB565,	/* 16 bit WGB, 1 pwane. Each 3 sub
					 * pixews awe packed into one 16 bit
					 * vawue, 5 bits fow W, 6 bits fow G
					 * and 5 bits fow B.
					 */
	IMGU_ABI_FWAME_FOWMAT_PWANAW_WGB888, /* 24 bit WGB, 3 pwanes */
	IMGU_ABI_FWAME_FOWMAT_WGBA888,	/* 32 bit WGBA, 1 pwane, A=Awpha
					 * (awpha is unused)
					 */
	IMGU_ABI_FWAME_FOWMAT_QPWANE6,	/* Intewnaw, fow advanced ISP */
	IMGU_ABI_FWAME_FOWMAT_BINAWY_8,	/* byte stweam, used fow jpeg. Fow
					 * fwames of this type, we set the
					 * height to 1 and the width to the
					 * numbew of awwocated bytes.
					 */
	IMGU_ABI_FWAME_FOWMAT_MIPI,	/* MIPI fwame, 1 pwane */
	IMGU_ABI_FWAME_FOWMAT_WAW_PACKED,	 /* WAW, 1 pwane, packed */
	IMGU_ABI_FWAME_FOWMAT_CSI_MIPI_YUV420_8, /* 8 bit pew Y/U/V. Y odd wine
						  * UYVY intewweaved even wine
						  */
	IMGU_ABI_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8, /* Wegacy YUV420.
							 * UY odd wine;
							 * VY even wine
							 */
	IMGU_ABI_FWAME_FOWMAT_CSI_MIPI_YUV420_10,/* 10 bit pew Y/U/V. Y odd
						  * wine; UYVY intewweaved
						  * even wine
						  */
	IMGU_ABI_FWAME_FOWMAT_YCGCO444_16, /* Intewnaw fowmat fow ISP2.7,
					    * 16 bits pew pwane YUV 444,
					    * Y, U, V pwane
					    */
	IMGU_ABI_FWAME_FOWMAT_NUM
};

enum imgu_abi_bayew_owdew {
	IMGU_ABI_BAYEW_OWDEW_GWBG,
	IMGU_ABI_BAYEW_OWDEW_WGGB,
	IMGU_ABI_BAYEW_OWDEW_BGGW,
	IMGU_ABI_BAYEW_OWDEW_GBWG
};

enum imgu_abi_osys_fowmat {
	IMGU_ABI_OSYS_FOWMAT_YUV420,
	IMGU_ABI_OSYS_FOWMAT_YV12,
	IMGU_ABI_OSYS_FOWMAT_NV12,
	IMGU_ABI_OSYS_FOWMAT_NV21,
	IMGU_ABI_OSYS_FOWMAT_YUV_WINE,
	IMGU_ABI_OSYS_FOWMAT_YUY2,	/* = IMGU_ABI_OSYS_FOWMAT_YUYV */
	IMGU_ABI_OSYS_FOWMAT_NV16,
	IMGU_ABI_OSYS_FOWMAT_WGBA,
	IMGU_ABI_OSYS_FOWMAT_BGWA
};

enum imgu_abi_osys_tiwing {
	IMGU_ABI_OSYS_TIWING_NONE,
	IMGU_ABI_OSYS_TIWING_Y,
	IMGU_ABI_OSYS_TIWING_YF,
};

enum imgu_abi_osys_pwocmode {
	IMGU_ABI_OSYS_PWOCMODE_BYPASS,
	IMGU_ABI_OSYS_PWOCMODE_UPSCAWE,
	IMGU_ABI_OSYS_PWOCMODE_DOWNSCAWE,
};

enum imgu_abi_queue_id {
	IMGU_ABI_QUEUE_EVENT_ID = -1,
	IMGU_ABI_QUEUE_A_ID = 0,
	IMGU_ABI_QUEUE_B_ID,
	IMGU_ABI_QUEUE_C_ID,
	IMGU_ABI_QUEUE_D_ID,
	IMGU_ABI_QUEUE_E_ID,
	IMGU_ABI_QUEUE_F_ID,
	IMGU_ABI_QUEUE_G_ID,
	IMGU_ABI_QUEUE_H_ID,		/* input fwame queue fow skycam */
	IMGU_ABI_QUEUE_NUM
};

enum imgu_abi_buffew_type {
	IMGU_ABI_BUFFEW_TYPE_INVAWID = -1,
	IMGU_ABI_BUFFEW_TYPE_3A_STATISTICS = 0,
	IMGU_ABI_BUFFEW_TYPE_DIS_STATISTICS,
	IMGU_ABI_BUFFEW_TYPE_WACE_STATISTICS,
	IMGU_ABI_BUFFEW_TYPE_INPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_OUTPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_SEC_OUTPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_VF_OUTPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_SEC_VF_OUTPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_WAW_OUTPUT_FWAME,
	IMGU_ABI_BUFFEW_TYPE_CUSTOM_INPUT,
	IMGU_ABI_BUFFEW_TYPE_CUSTOM_OUTPUT,
	IMGU_ABI_BUFFEW_TYPE_METADATA,
	IMGU_ABI_BUFFEW_TYPE_PAWAMETEW_SET,
	IMGU_ABI_BUFFEW_TYPE_PEW_FWAME_PAWAMETEW_SET,
	IMGU_ABI_NUM_DYNAMIC_BUFFEW_TYPE,
	IMGU_ABI_NUM_BUFFEW_TYPE
};

enum imgu_abi_waw_type {
	IMGU_ABI_WAW_TYPE_BAYEW,
	IMGU_ABI_WAW_TYPE_IW_ON_GW,
	IMGU_ABI_WAW_TYPE_IW_ON_GB
};

enum imgu_abi_memowies {
	IMGU_ABI_MEM_ISP_PMEM0 = 0,
	IMGU_ABI_MEM_ISP_DMEM0,
	IMGU_ABI_MEM_ISP_VMEM0,
	IMGU_ABI_MEM_ISP_VAMEM0,
	IMGU_ABI_MEM_ISP_VAMEM1,
	IMGU_ABI_MEM_ISP_VAMEM2,
	IMGU_ABI_MEM_ISP_HMEM0,
	IMGU_ABI_MEM_SP0_DMEM0,
	IMGU_ABI_MEM_SP1_DMEM0,
	IMGU_ABI_MEM_DDW,
	IMGU_ABI_NUM_MEMOWIES
};

enum imgu_abi_pawam_cwass {
	IMGU_ABI_PAWAM_CWASS_PAWAM,	/* Wate binding pawametews, wike 3A */
	IMGU_ABI_PAWAM_CWASS_CONFIG,	/* Pipe config time pawametews */
	IMGU_ABI_PAWAM_CWASS_STATE,	/* State pawametews, eg. buffew index */
	IMGU_ABI_PAWAM_CWASS_NUM
};

enum imgu_abi_bin_input_swc {
	IMGU_ABI_BINAWY_INPUT_SOUWCE_SENSOW,
	IMGU_ABI_BINAWY_INPUT_SOUWCE_MEMOWY,
	IMGU_ABI_BINAWY_INPUT_SOUWCE_VAWIABWE,
};

enum imgu_abi_sp_swstate {
	IMGU_ABI_SP_SWSTATE_TEWMINATED,
	IMGU_ABI_SP_SWSTATE_INITIAWIZED,
	IMGU_ABI_SP_SWSTATE_CONNECTED,
	IMGU_ABI_SP_SWSTATE_WUNNING,
};

enum imgu_abi_bw_swstate {
	IMGU_ABI_BW_SWSTATE_OK = 0x100,
	IMGU_ABI_BW_SWSTATE_BUSY,
	IMGU_ABI_BW_SWSTATE_EWW,
};

/* The type of pipe stage */
enum imgu_abi_stage_type {
	IMGU_ABI_STAGE_TYPE_SP,
	IMGU_ABI_STAGE_TYPE_ISP,
};

stwuct imgu_abi_acc_opewation {
	/*
	 * zewo means on init,
	 * othews mean upon weceiving an ack signaw fwom the BC acc.
	 */
	u8 op_indicatow;
	u8 op_type;
} __packed;

stwuct imgu_abi_acc_pwocess_wines_cmd_data {
	u16 wines;
	u8 cfg_set;
	u8 wesewved;		/* Awign to 4 bytes */
} __packed;

/* Bayew shading definitions */

stwuct imgu_abi_shd_twansfew_wuts_set_data {
	u8 set_numbew;
	u8 padding[3];
	imgu_addw_t wg_wut_ddw_addw;
	imgu_addw_t bg_wut_ddw_addw;
	u32 awign_dummy;
} __packed;

stwuct imgu_abi_shd_gwid_config {
	/* weg 0 */
	u32 gwid_width:8;
	u32 gwid_height:8;
	u32 bwock_width:3;
	u32 wesewved0:1;
	u32 bwock_height:3;
	u32 wesewved1:1;
	u32 gwid_height_pew_swice:8;
	/* weg 1 */
	s32 x_stawt:13;
	s32 wesewved2:3;
	s32 y_stawt:13;
	s32 wesewved3:3;
} __packed;

stwuct imgu_abi_shd_genewaw_config {
	u32 init_set_vwt_offst_uw:8;
	u32 shd_enabwe:1;
	/* aka 'gf' */
	u32 gain_factow:2;
	u32 wesewved:21;
} __packed;

stwuct imgu_abi_shd_bwack_wevew_config {
	/* weg 0 */
	s32 bw_w:12;
	s32 wesewved0:4;
	s32 bw_gw:12;
	u32 wesewved1:1;
	/* aka 'nf' */
	u32 nowmawization_shift:3;
	/* weg 1 */
	s32 bw_gb:12;
	s32 wesewved2:4;
	s32 bw_b:12;
	s32 wesewved3:4;
} __packed;

stwuct imgu_abi_shd_intwa_fwame_opewations_data {
	stwuct imgu_abi_acc_opewation
		opewation_wist[IMGU_ABI_SHD_MAX_OPEWATIONS] __awigned(32);
	stwuct imgu_abi_acc_pwocess_wines_cmd_data
		pwocess_wines_data[IMGU_ABI_SHD_MAX_PWOCESS_WINES] __awigned(32);
	stwuct imgu_abi_shd_twansfew_wuts_set_data
		twansfew_data[IMGU_ABI_SHD_MAX_TWANSFEWS] __awigned(32);
} __packed;

stwuct imgu_abi_shd_config {
	stwuct ipu3_uapi_shd_config_static shd __awigned(32);
	stwuct imgu_abi_shd_intwa_fwame_opewations_data shd_ops __awigned(32);
	stwuct ipu3_uapi_shd_wut shd_wut __awigned(32);
} __packed;

stwuct imgu_abi_stwipe_input_fwame_wesowution {
	u16 width;
	u16 height;
	u32 bayew_owdew;		/* enum ipu3_uapi_bayew_owdew */
	u32 waw_bit_depth;
} __packed;

/* Stwipe-based pwocessing */

stwuct imgu_abi_stwipes {
	/* offset fwom stawt of fwame - measuwed in pixews */
	u16 offset;
	/* stwipe width - measuwed in pixews */
	u16 width;
	/* stwipe width - measuwed in pixews */
	u16 height;
} __packed;

stwuct imgu_abi_stwipe_data {
	/*
	 * numbew of stwipes fow cuwwent pwocessing souwce
	 * - VWIW binawy pawametew we cuwwentwy suppowt 1 ow 2 stwipes
	 */
	u16 num_of_stwipes;

	u8 padding[2];

	/*
	 * the fowwowing data is dewived fwom wesowution-wewated
	 * pipe config and fwom num_of_stwipes
	 */

	/*
	 *'input-stwipes' - befowe input cwopping
	 * used by input feedew
	 */
	stwuct imgu_abi_stwipe_input_fwame_wesowution input_fwame;

	/*'effective-stwipes' - aftew input cwopping used dpc, bds */
	stwuct imgu_abi_stwipes effective_stwipes[IPU3_UAPI_MAX_STWIPES];

	/* 'down-scawed-stwipes' - aftew down-scawing ONWY. used by BDS */
	stwuct imgu_abi_stwipes down_scawed_stwipes[IPU3_UAPI_MAX_STWIPES];

	/*
	 *'bds-out-stwipes' - aftew bayew down-scawing and padding.
	 * used by aww awgos stawting with nowm up to the wef-fwame fow GDC
	 * (cuwwentwy up to the output kewnew)
	 */
	stwuct imgu_abi_stwipes bds_out_stwipes[IPU3_UAPI_MAX_STWIPES];

	/* 'bds-out-stwipes (no ovewwap)' - used fow wef kewnew */
	stwuct imgu_abi_stwipes
			bds_out_stwipes_no_ovewwap[IPU3_UAPI_MAX_STWIPES];

	/*
	 * input wesowution fow output system (equaw to bds_out - envewope)
	 * output-system input fwame width as configuwed by usew
	 */
	u16 output_system_in_fwame_width;
	/* output-system input fwame height as configuwed by usew */
	u16 output_system_in_fwame_height;

	/*
	 * 'output-stwipes' - accounts fow stiching on the output (no ovewwap)
	 * used by the output kewnew
	 */
	stwuct imgu_abi_stwipes output_stwipes[IPU3_UAPI_MAX_STWIPES];

	/*
	 * 'bwock-stwipes' - accounts fow stiching by the output system
	 * (1 ow mowe bwocks ovewwap)
	 * used by DVS, TNW and the output system kewnew
	 */
	stwuct imgu_abi_stwipes bwock_stwipes[IPU3_UAPI_MAX_STWIPES];

	u16 effective_fwame_width;	/* Needed fow vewticaw cwopping */
	u16 bds_fwame_width;
	u16 out_fwame_width;	/* Output fwame width as configuwed by usew */
	u16 out_fwame_height;	/* Output fwame height as configuwed by usew */

	/* GDC in buffew (A.K.A deway fwame,wef buffew) info */
	u16 gdc_in_buffew_width;	/* GDC in buffew width  */
	u16 gdc_in_buffew_height;	/* GDC in buffew height */
	/* GDC in buffew fiwst vawid pixew x offset */
	u16 gdc_in_buffew_offset_x;
	/* GDC in buffew fiwst vawid pixew y offset */
	u16 gdc_in_buffew_offset_y;

	/* Dispway fwame width as configuwed by usew */
	u16 dispway_fwame_width;
	/* Dispway fwame height as configuwed by usew */
	u16 dispway_fwame_height;
	u16 bds_awigned_fwame_width;
	/* Numbew of vectows to weft-cwop when wwiting stwipes (not stwipe 0) */
	u16 hawf_ovewwap_vectows;
	/* Decimate ISP and fixed func wesowutions aftew BDS (iw_extwaction) */
	u16 iw_ext_decimation;
	u8 padding1[2];
} __packed;

/* Input feedew wewated stwucts */

stwuct imgu_abi_input_feedew_data {
	u32 wow_stwide;			/* wow stwide */
	u32 stawt_wow_addwess;		/* stawt wow addwess */
	u32 stawt_pixew;		/* stawt pixew */
} __packed;

stwuct imgu_abi_input_feedew_data_awigned {
	stwuct imgu_abi_input_feedew_data data __awigned(32);
} __packed;

stwuct imgu_abi_input_feedew_data_pew_stwipe {
	stwuct imgu_abi_input_feedew_data_awigned
		input_feedew_data[IPU3_UAPI_MAX_STWIPES];
} __packed;

stwuct imgu_abi_input_feedew_config {
	stwuct imgu_abi_input_feedew_data data;
	stwuct imgu_abi_input_feedew_data_pew_stwipe data_pew_stwipe
		__awigned(32);
} __packed;

/* DVS wewated definitions */

stwuct imgu_abi_dvs_stat_gwd_config {
	u8 gwid_width;
	u8 gwid_height;
	u8 bwock_width;
	u8 bwock_height;
	u16 x_stawt;
	u16 y_stawt;
	u16 enabwe;
	u16 x_end;
	u16 y_end;
} __packed;

stwuct imgu_abi_dvs_stat_cfg {
	u8 wesewved0[4];
	stwuct imgu_abi_dvs_stat_gwd_config
					gwd_config[IMGU_ABI_DVS_STAT_WEVEWS];
	u8 wesewved1[18];
} __packed;

stwuct imgu_abi_dvs_stat_twansfew_op_data {
	u8 set_numbew;
} __packed;

stwuct imgu_abi_dvs_stat_intwa_fwame_opewations_data {
	stwuct imgu_abi_acc_opewation
		ops[IMGU_ABI_DVS_STAT_MAX_OPEWATIONS] __awigned(32);
	stwuct imgu_abi_acc_pwocess_wines_cmd_data
		pwocess_wines_data[IMGU_ABI_DVS_STAT_MAX_PWOCESS_WINES]
		__awigned(32);
	stwuct imgu_abi_dvs_stat_twansfew_op_data
		twansfew_data[IMGU_ABI_DVS_STAT_MAX_TWANSFEWS] __awigned(32);
} __packed;

stwuct imgu_abi_dvs_stat_config {
	stwuct imgu_abi_dvs_stat_cfg cfg __awigned(32);
	u8 wesewved0[128];
	stwuct imgu_abi_dvs_stat_intwa_fwame_opewations_data opewations_data;
	u8 wesewved1[64];
} __packed;

/* Y-tone Mapping */

stwuct imgu_abi_yuvp2_y_tm_wut_static_config {
	u16 entwies[IMGU_ABI_YUVP2_YTM_WUT_ENTWIES];
	u32 enabwe;
} __packed;

/* Output fowmattew wewated stwucts */

stwuct imgu_abi_osys_fowmattew_pawams {
	u32 fowmat;
	u32 fwip;
	u32 miwwow;
	u32 tiwing;
	u32 weduce_wange;
	u32 awpha_bwending;
	u32 wewease_inp_addw;
	u32 wewease_inp_en;
	u32 pwocess_out_buf_addw;
	u32 image_width_vecs;
	u32 image_height_wines;
	u32 inp_buff_y_st_addw;
	u32 inp_buff_y_wine_stwide;
	u32 inp_buff_y_buffew_stwide;
	u32 int_buff_u_st_addw;
	u32 int_buff_v_st_addw;
	u32 inp_buff_uv_wine_stwide;
	u32 inp_buff_uv_buffew_stwide;
	u32 out_buff_wevew;
	u32 out_buff_nw_y_wines;
	u32 out_buff_u_st_offset;
	u32 out_buff_v_st_offset;
	u32 out_buff_y_wine_stwide;
	u32 out_buff_uv_wine_stwide;
	u32 hist_buff_st_addw;
	u32 hist_buff_wine_stwide;
	u32 hist_buff_nw_wines;
} __packed;

stwuct imgu_abi_osys_fowmattew {
	stwuct imgu_abi_osys_fowmattew_pawams pawam __awigned(32);
} __packed;

stwuct imgu_abi_osys_scawew_pawams {
	u32 inp_buf_y_st_addw;
	u32 inp_buf_y_wine_stwide;
	u32 inp_buf_y_buffew_stwide;
	u32 inp_buf_u_st_addw;
	u32 inp_buf_v_st_addw;
	u32 inp_buf_uv_wine_stwide;
	u32 inp_buf_uv_buffew_stwide;
	u32 inp_buf_chunk_width;
	u32 inp_buf_nw_buffews;
	/* Output buffews */
	u32 out_buf_y_st_addw;
	u32 out_buf_y_wine_stwide;
	u32 out_buf_y_buffew_stwide;
	u32 out_buf_u_st_addw;
	u32 out_buf_v_st_addw;
	u32 out_buf_uv_wine_stwide;
	u32 out_buf_uv_buffew_stwide;
	u32 out_buf_nw_buffews;
	/* Intewmediate buffews */
	u32 int_buf_y_st_addw;
	u32 int_buf_y_wine_stwide;
	u32 int_buf_u_st_addw;
	u32 int_buf_v_st_addw;
	u32 int_buf_uv_wine_stwide;
	u32 int_buf_height;
	u32 int_buf_chunk_width;
	u32 int_buf_chunk_height;
	/* Context buffews */
	u32 ctx_buf_how_y_st_addw;
	u32 ctx_buf_how_u_st_addw;
	u32 ctx_buf_how_v_st_addw;
	u32 ctx_buf_vew_y_st_addw;
	u32 ctx_buf_vew_u_st_addw;
	u32 ctx_buf_vew_v_st_addw;
	/* Addwesses fow wewease-input and pwocess-output tokens */
	u32 wewease_inp_buf_addw;
	u32 wewease_inp_buf_en;
	u32 wewease_out_buf_en;
	u32 pwocess_out_buf_addw;
	/* Settings dimensions, padding, cwopping */
	u32 input_image_y_width;
	u32 input_image_y_height;
	u32 input_image_y_stawt_cowumn;
	u32 input_image_uv_stawt_cowumn;
	u32 input_image_y_weft_pad;
	u32 input_image_uv_weft_pad;
	u32 input_image_y_wight_pad;
	u32 input_image_uv_wight_pad;
	u32 input_image_y_top_pad;
	u32 input_image_uv_top_pad;
	u32 input_image_y_bottom_pad;
	u32 input_image_uv_bottom_pad;
	u32 pwocessing_mode;	/* enum imgu_abi_osys_pwocmode */
	u32 scawing_watio;
	u32 y_weft_phase_init;
	u32 uv_weft_phase_init;
	u32 y_top_phase_init;
	u32 uv_top_phase_init;
	u32 coeffs_exp_shift;
	u32 out_y_weft_cwop;
	u32 out_uv_weft_cwop;
	u32 out_y_top_cwop;
	u32 out_uv_top_cwop;
} __packed;

stwuct imgu_abi_osys_scawew {
	stwuct imgu_abi_osys_scawew_pawams pawam __awigned(32);
} __packed;

stwuct imgu_abi_osys_fwame_pawams {
	/* Output pins */
	u32 enabwe;
	u32 fowmat;		/* enum imgu_abi_osys_fowmat */
	u32 fwip;
	u32 miwwow;
	u32 tiwing;		/* enum imgu_abi_osys_tiwing */
	u32 width;
	u32 height;
	u32 stwide;
	u32 scawed;
} __packed;

stwuct imgu_abi_osys_fwame {
	stwuct imgu_abi_osys_fwame_pawams pawam __awigned(32);
} __packed;

stwuct imgu_abi_osys_stwipe {
	/* Input wesowution */
	u32 input_width;
	u32 input_height;
	/* Output Stwipe */
	u32 output_width[IMGU_ABI_OSYS_PINS];
	u32 output_height[IMGU_ABI_OSYS_PINS];
	u32 output_offset[IMGU_ABI_OSYS_PINS];
	u32 buf_stwide[IMGU_ABI_OSYS_PINS];
	/* Scawew pawams */
	u32 bwock_width;
	u32 bwock_height;
	/* Output Cwop factow */
	u32 cwop_top[IMGU_ABI_OSYS_PINS];
	u32 cwop_weft[IMGU_ABI_OSYS_PINS];
} __packed;

stwuct imgu_abi_osys_config {
	stwuct imgu_abi_osys_fowmattew
		fowmattew[IPU3_UAPI_MAX_STWIPES][IMGU_ABI_OSYS_PINS];
	stwuct imgu_abi_osys_scawew scawew[IPU3_UAPI_MAX_STWIPES];
	stwuct imgu_abi_osys_fwame fwame[IMGU_ABI_OSYS_PINS];
	stwuct imgu_abi_osys_stwipe stwipe[IPU3_UAPI_MAX_STWIPES];
	/* 32 packed coefficients fow wuma and chwoma */
	s8 scawew_coeffs_chwoma[128];
	s8 scawew_coeffs_wuma[128];
} __packed;

/* BDS */

stwuct imgu_abi_bds_how_ctww0 {
	u32 sampwe_patwn_wength:9;
	u32 wesewved0:3;
	u32 how_ds_en:1;
	u32 min_cwip_vaw:1;
	u32 max_cwip_vaw:2;
	u32 out_fwame_width:13;
	u32 wesewved1:3;
} __packed;

stwuct imgu_abi_bds_ptwn_aww {
	u32 ewems[IMGU_ABI_BDS_SAMPWE_PATTEWN_AWWAY_SIZE];
} __packed;

stwuct imgu_abi_bds_phase_entwy {
	s8 coeff_min2;
	s8 coeff_min1;
	s8 coeff_0;
	s8 nf;
	s8 coeff_pws1;
	s8 coeff_pws2;
	s8 coeff_pws3;
	u8 wesewved;
} __packed;

stwuct imgu_abi_bds_phase_aww {
	stwuct imgu_abi_bds_phase_entwy
		even[IMGU_ABI_BDS_PHASE_COEFFS_AWWAY_SIZE];
	stwuct imgu_abi_bds_phase_entwy
		odd[IMGU_ABI_BDS_PHASE_COEFFS_AWWAY_SIZE];
} __packed;

stwuct imgu_abi_bds_how_ctww1 {
	u32 how_cwop_stawt:13;
	u32 wesewved0:3;
	u32 how_cwop_end:13;
	u32 wesewved1:1;
	u32 how_cwop_en:1;
	u32 wesewved2:1;
} __packed;

stwuct imgu_abi_bds_how_ctww2 {
	u32 input_fwame_height:13;
	u32 wesewved0:19;
} __packed;

stwuct imgu_abi_bds_how {
	stwuct imgu_abi_bds_how_ctww0 how_ctww0;
	stwuct imgu_abi_bds_ptwn_aww how_ptwn_aww;
	stwuct imgu_abi_bds_phase_aww how_phase_aww;
	stwuct imgu_abi_bds_how_ctww1 how_ctww1;
	stwuct imgu_abi_bds_how_ctww2 how_ctww2;
} __packed;

stwuct imgu_abi_bds_vew_ctww0 {
	u32 sampwe_patwn_wength:9;
	u32 wesewved0:3;
	u32 vew_ds_en:1;
	u32 min_cwip_vaw:1;
	u32 max_cwip_vaw:2;
	u32 wesewved1:16;
} __packed;

stwuct imgu_abi_bds_vew_ctww1 {
	u32 out_fwame_width:13;
	u32 wesewved0:3;
	u32 out_fwame_height:13;
	u32 wesewved1:3;
} __packed;

stwuct imgu_abi_bds_vew {
	stwuct imgu_abi_bds_vew_ctww0 vew_ctww0;
	stwuct imgu_abi_bds_ptwn_aww vew_ptwn_aww;
	stwuct imgu_abi_bds_phase_aww vew_phase_aww;
	stwuct imgu_abi_bds_vew_ctww1 vew_ctww1;
} __packed;

stwuct imgu_abi_bds_pew_stwipe_data {
	stwuct imgu_abi_bds_how_ctww0 how_ctww0;
	stwuct imgu_abi_bds_vew_ctww1 vew_ctww1;
	stwuct imgu_abi_bds_how_ctww1 cwop;
} __packed;

stwuct imgu_abi_bds_pew_stwipe_data_awigned {
	stwuct imgu_abi_bds_pew_stwipe_data data __awigned(32);
} __packed;

stwuct imgu_abi_bds_pew_stwipe {
	stwuct imgu_abi_bds_pew_stwipe_data_awigned
		awigned_data[IPU3_UAPI_MAX_STWIPES];
} __packed;

stwuct imgu_abi_bds_config {
	stwuct imgu_abi_bds_how how __awigned(32);
	stwuct imgu_abi_bds_vew vew __awigned(32);
	stwuct imgu_abi_bds_pew_stwipe pew_stwipe __awigned(32);
	u32 enabwed;
} __packed;

/* ANW */

stwuct imgu_abi_anw_seawch_config {
	u32 enabwe;
	u16 fwame_width;
	u16 fwame_height;
} __packed;

stwuct imgu_abi_anw_stitch_config {
	u32 anw_stitch_en;
	u16 fwame_width;
	u16 fwame_height;
	u8 wesewved[40];
	stwuct ipu3_uapi_anw_stitch_pywamid pywamid[IPU3_UAPI_ANW_PYWAMID_SIZE];
} __packed;

stwuct imgu_abi_anw_tiwe2stwm_config {
	u32 enabwe;
	u16 fwame_width;
	u16 fwame_height;
} __packed;

stwuct imgu_abi_anw_config {
	stwuct imgu_abi_anw_seawch_config seawch __awigned(32);
	stwuct ipu3_uapi_anw_twansfowm_config twansfowm __awigned(32);
	stwuct imgu_abi_anw_stitch_config stitch __awigned(32);
	stwuct imgu_abi_anw_tiwe2stwm_config tiwe2stwm __awigned(32);
} __packed;

/* AF */

stwuct imgu_abi_af_fwame_size {
	u16 width;
	u16 height;
} __packed;

stwuct imgu_abi_af_config_s {
	stwuct ipu3_uapi_af_fiwtew_config fiwtew_config __awigned(32);
	stwuct imgu_abi_af_fwame_size fwame_size;
	stwuct ipu3_uapi_gwid_config gwid_cfg __awigned(32);
} __packed;

stwuct imgu_abi_af_intwa_fwame_opewations_data {
	stwuct imgu_abi_acc_opewation ops[IMGU_ABI_AF_MAX_OPEWATIONS]
		__awigned(32);
	stwuct imgu_abi_acc_pwocess_wines_cmd_data
		pwocess_wines_data[IMGU_ABI_AF_MAX_PWOCESS_WINES] __awigned(32);
} __packed;

stwuct imgu_abi_af_stwipe_config {
	stwuct imgu_abi_af_fwame_size fwame_size __awigned(32);
	stwuct ipu3_uapi_gwid_config gwid_cfg __awigned(32);
} __packed;

stwuct imgu_abi_af_config {
	stwuct imgu_abi_af_config_s config;
	stwuct imgu_abi_af_intwa_fwame_opewations_data opewations_data;
	stwuct imgu_abi_af_stwipe_config stwipes[IPU3_UAPI_MAX_STWIPES];
} __packed;

/* AE */

stwuct imgu_abi_ae_config {
	stwuct ipu3_uapi_ae_gwid_config gwid_cfg __awigned(32);
	stwuct ipu3_uapi_ae_weight_ewem weights[IPU3_UAPI_AE_WEIGHTS]
								__awigned(32);
	stwuct ipu3_uapi_ae_ccm ae_ccm __awigned(32);
	stwuct {
		stwuct ipu3_uapi_ae_gwid_config gwid __awigned(32);
	} stwipes[IPU3_UAPI_MAX_STWIPES];
} __packed;

/* AWB_FW */

stwuct imgu_abi_awb_fw_intwa_fwame_opewations_data {
	stwuct imgu_abi_acc_opewation ops[IMGU_ABI_AWB_FW_MAX_OPEWATIONS]
								__awigned(32);
	stwuct imgu_abi_acc_pwocess_wines_cmd_data
	      pwocess_wines_data[IMGU_ABI_AWB_FW_MAX_PWOCESS_WINES] __awigned(32);
} __packed;

stwuct imgu_abi_awb_fw_config {
	stwuct ipu3_uapi_awb_fw_config_s config;
	stwuct imgu_abi_awb_fw_intwa_fwame_opewations_data opewations_data;
	stwuct ipu3_uapi_awb_fw_config_s stwipes[IPU3_UAPI_MAX_STWIPES];
} __packed;

stwuct imgu_abi_acc_twansfew_op_data {
	u8 set_numbew;
} __packed;

stwuct imgu_abi_awb_intwa_fwame_opewations_data {
	stwuct imgu_abi_acc_opewation ops[IMGU_ABI_AWB_MAX_OPEWATIONS]
		__awigned(32);
	stwuct imgu_abi_acc_pwocess_wines_cmd_data
		pwocess_wines_data[IMGU_ABI_AWB_MAX_PWOCESS_WINES] __awigned(32);
	stwuct imgu_abi_acc_twansfew_op_data
		twansfew_data[IMGU_ABI_AWB_MAX_TWANSFEWS] __awigned(32);
} __awigned(32) __packed;

stwuct imgu_abi_awb_config {
	stwuct ipu3_uapi_awb_config_s config __awigned(32);
	stwuct imgu_abi_awb_intwa_fwame_opewations_data opewations_data;
	stwuct ipu3_uapi_awb_config_s stwipes[IPU3_UAPI_MAX_STWIPES];
} __packed;

stwuct imgu_abi_acc_pawam {
	stwuct imgu_abi_stwipe_data stwipe;
	u8 padding[8];
	stwuct imgu_abi_input_feedew_config input_feedew;
	stwuct ipu3_uapi_bnw_static_config bnw;
	stwuct ipu3_uapi_bnw_static_config_gween_dispawity gween_dispawity
		__awigned(32);
	stwuct ipu3_uapi_dm_config dm __awigned(32);
	stwuct ipu3_uapi_ccm_mat_config ccm __awigned(32);
	stwuct ipu3_uapi_gamma_config gamma __awigned(32);
	stwuct ipu3_uapi_csc_mat_config csc __awigned(32);
	stwuct ipu3_uapi_cds_pawams cds __awigned(32);
	stwuct imgu_abi_shd_config shd __awigned(32);
	stwuct imgu_abi_dvs_stat_config dvs_stat;
	u8 padding1[224];	/* wesewved fow wace_stat */
	stwuct ipu3_uapi_yuvp1_iefd_config iefd __awigned(32);
	stwuct ipu3_uapi_yuvp1_yds_config yds_c0 __awigned(32);
	stwuct ipu3_uapi_yuvp1_chnw_config chnw_c0 __awigned(32);
	stwuct ipu3_uapi_yuvp1_y_ee_nw_config y_ee_nw __awigned(32);
	stwuct ipu3_uapi_yuvp1_yds_config yds __awigned(32);
	stwuct ipu3_uapi_yuvp1_chnw_config chnw __awigned(32);
	stwuct imgu_abi_yuvp2_y_tm_wut_static_config ytm __awigned(32);
	stwuct ipu3_uapi_yuvp1_yds_config yds2 __awigned(32);
	stwuct ipu3_uapi_yuvp2_tcc_static_config tcc __awigned(32);
	/* wesewved fow defect pixew cowwection */
	u8 dpc[240832] __awigned(32);
	stwuct imgu_abi_bds_config bds;
	stwuct imgu_abi_anw_config anw;
	stwuct imgu_abi_awb_fw_config awb_fw;
	stwuct imgu_abi_ae_config ae;
	stwuct imgu_abi_af_config af;
	stwuct imgu_abi_awb_config awb;
	stwuct imgu_abi_osys_config osys;
} __packed;

/***** Mowphing tabwe entwy *****/

stwuct imgu_abi_gdc_wawp_pawam {
	u32 owigin_x;
	u32 owigin_y;
	u32 in_addw_offset;
	u32 in_bwock_width;
	u32 in_bwock_height;
	u32 p0_x;
	u32 p0_y;
	u32 p1_x;
	u32 p1_y;
	u32 p2_x;
	u32 p2_y;
	u32 p3_x;
	u32 p3_y;
	u32 in_bwock_width_a;
	u32 in_bwock_width_b;
	u32 padding;		/* stwuct size muwtipwe of DDW wowd */
} __packed;

/******************* Fiwmwawe ABI definitions *******************/

/***** stwuct imgu_abi_sp_stage *****/

stwuct imgu_abi_cwop_pos {
	u16 x;
	u16 y;
} __packed;

stwuct imgu_abi_sp_wesowution {
	u16 width;			/* Width of vawid data in pixews */
	u16 height;			/* Height of vawid data in wines */
} __packed;

/*
 * Fwame info stwuct. This descwibes the contents of an image fwame buffew.
 */
stwuct imgu_abi_fwame_sp_info {
	stwuct imgu_abi_sp_wesowution wes;
	u16 padded_width;		/* stwide of wine in memowy
					 * (in pixews)
					 */
	u8 fowmat;			/* fowmat of the fwame data */
	u8 waw_bit_depth;		/* numbew of vawid bits pew pixew,
					 * onwy vawid fow WAW bayew fwames
					 */
	u8 waw_bayew_owdew;		/* bayew owdew, onwy vawid
					 * fow WAW bayew fwames
					 */
	u8 waw_type;		/* To choose the pwopew waw fwame type. fow
				 * Wegacy SKC pipes/Defauwt is set to
				 * IMGU_ABI_WAW_TYPE_BAYEW. Fow WGB IW sensow -
				 * dwivew shouwd set it to:
				 * IwonGw case - IMGU_ABI_WAW_TYPE_IW_ON_GW
				 * IwonGb case - IMGU_ABI_WAW_TYPE_IW_ON_GB
				 */
	u8 padding[2];			/* Extend to 32 bit muwtipwe */
} __packed;

stwuct imgu_abi_buffew_sp {
	union {
		imgu_addw_t xmem_addw;
		s32 queue_id;	/* enum imgu_abi_queue_id */
	} buf_swc;
	s32 buf_type;	/* enum imgu_abi_buffew_type */
} __packed;

stwuct imgu_abi_fwame_sp_pwane {
	u32 offset;		/* offset in bytes to stawt of fwame data */
				/* offset is wwt data in imgu_abi_sp_sp_fwame */
} __packed;

stwuct imgu_abi_fwame_sp_wgb_pwanes {
	stwuct imgu_abi_fwame_sp_pwane w;
	stwuct imgu_abi_fwame_sp_pwane g;
	stwuct imgu_abi_fwame_sp_pwane b;
} __packed;

stwuct imgu_abi_fwame_sp_yuv_pwanes {
	stwuct imgu_abi_fwame_sp_pwane y;
	stwuct imgu_abi_fwame_sp_pwane u;
	stwuct imgu_abi_fwame_sp_pwane v;
} __packed;

stwuct imgu_abi_fwame_sp_nv_pwanes {
	stwuct imgu_abi_fwame_sp_pwane y;
	stwuct imgu_abi_fwame_sp_pwane uv;
} __packed;

stwuct imgu_abi_fwame_sp_pwane6 {
	stwuct imgu_abi_fwame_sp_pwane w;
	stwuct imgu_abi_fwame_sp_pwane w_at_b;
	stwuct imgu_abi_fwame_sp_pwane gw;
	stwuct imgu_abi_fwame_sp_pwane gb;
	stwuct imgu_abi_fwame_sp_pwane b;
	stwuct imgu_abi_fwame_sp_pwane b_at_w;
} __packed;

stwuct imgu_abi_fwame_sp_binawy_pwane {
	u32 size;
	stwuct imgu_abi_fwame_sp_pwane data;
} __packed;

stwuct imgu_abi_fwame_sp {
	stwuct imgu_abi_fwame_sp_info info;
	stwuct imgu_abi_buffew_sp buf_attw;
	union {
		stwuct imgu_abi_fwame_sp_pwane waw;
		stwuct imgu_abi_fwame_sp_pwane wgb;
		stwuct imgu_abi_fwame_sp_wgb_pwanes pwanaw_wgb;
		stwuct imgu_abi_fwame_sp_pwane yuyv;
		stwuct imgu_abi_fwame_sp_yuv_pwanes yuv;
		stwuct imgu_abi_fwame_sp_nv_pwanes nv;
		stwuct imgu_abi_fwame_sp_pwane6 pwane6;
		stwuct imgu_abi_fwame_sp_binawy_pwane binawy;
	} pwanes;
} __packed;

stwuct imgu_abi_wesowution {
	u32 width;
	u32 height;
} __packed;

stwuct imgu_abi_fwames_sp {
	stwuct imgu_abi_fwame_sp in;
	stwuct imgu_abi_fwame_sp out[IMGU_ABI_BINAWY_MAX_OUTPUT_POWTS];
	stwuct imgu_abi_wesowution effective_in_wes;
	stwuct imgu_abi_fwame_sp out_vf;
	stwuct imgu_abi_fwame_sp_info intewnaw_fwame_info;
	stwuct imgu_abi_buffew_sp s3a_buf;
	stwuct imgu_abi_buffew_sp dvs_buf;
	stwuct imgu_abi_buffew_sp wace_buf;
} __packed;

stwuct imgu_abi_uds_info {
	u16 cuww_dx;
	u16 cuww_dy;
	u16 xc;
	u16 yc;
} __packed;

/* Infowmation fow a singwe pipewine stage */
stwuct imgu_abi_sp_stage {
	/* Muwtipwe boowean fwags can be stowed in an integew */
	u8 num;			/* Stage numbew */
	u8 isp_onwine;
	u8 isp_copy_vf;
	u8 isp_copy_output;
	u8 sp_enabwe_xnw;
	u8 isp_deci_wog_factow;
	u8 isp_vf_downscawe_bits;
	u8 deintewweaved;
	/*
	 * NOTE: Pwogwamming the input ciwcuit can onwy be done at the
	 * stawt of a session. It is iwwegaw to pwogwam it duwing execution
	 * The input ciwcuit defines the connectivity
	 */
	u8 pwogwam_input_ciwcuit;
	u8 func;
	u8 stage_type;		/* enum imgu_abi_stage_type */
	u8 num_stwipes;
	u8 isp_pipe_vewsion;
	stwuct {
		u8 vf_output;
		u8 s3a;
		u8 sdis;
		u8 dvs_stats;
		u8 wace_stats;
	} enabwe;

	stwuct imgu_abi_cwop_pos sp_out_cwop_pos;
	u8 padding[2];
	stwuct imgu_abi_fwames_sp fwames;
	stwuct imgu_abi_wesowution dvs_envewope;
	stwuct imgu_abi_uds_info uds;
	imgu_addw_t isp_stage_addw;
	imgu_addw_t xmem_bin_addw;
	imgu_addw_t xmem_map_addw;

	u16 top_cwopping;
	u16 wow_stwipes_height;
	u16 wow_stwipes_ovewwap_wines;
	u8 if_config_index;	/* Which shouwd be appwied by this stage. */
	u8 padding2;
} __packed;

/***** stwuct imgu_abi_isp_stage *****/

stwuct imgu_abi_isp_pawam_memowy_offsets {
	u32 offsets[IMGU_ABI_PAWAM_CWASS_NUM];	/* offset wwt hdw in bytes */
} __packed;

/*
 * Bwob descwiptow.
 * This stwuctuwe descwibes an SP ow ISP bwob.
 * It descwibes the test, data and bss sections as weww as position in a
 * fiwmwawe fiwe.
 * Fow convenience, it contains dynamic data aftew woading.
 */
stwuct imgu_abi_bwob_info {
	/* Static bwob data */
	u32 offset;			/* Bwob offset in fw fiwe */
	stwuct imgu_abi_isp_pawam_memowy_offsets memowy_offsets;
					/* offset wwt hdw in bytes */
	u32 pwog_name_offset;		/* offset wwt hdw in bytes */
	u32 size;			/* Size of bwob */
	u32 padding_size;		/* totaw cumuwative of bytes added
					 * due to section awignment
					 */
	u32 icache_souwce;		/* Position of icache in bwob */
	u32 icache_size;		/* Size of icache section */
	u32 icache_padding;	/* added due to icache section awignment */
	u32 text_souwce;		/* Position of text in bwob */
	u32 text_size;			/* Size of text section */
	u32 text_padding;	/* bytes added due to text section awignment */
	u32 data_souwce;		/* Position of data in bwob */
	u32 data_tawget;		/* Stawt of data in SP dmem */
	u32 data_size;			/* Size of text section */
	u32 data_padding;	/* bytes added due to data section awignment */
	u32 bss_tawget;		/* Stawt position of bss in SP dmem */
	u32 bss_size;			/* Size of bss section
					 * Dynamic data fiwwed by woadew
					 */
	u64 code __awigned(8);	/* Code section absowute pointew */
					/* within fw, code = icache + text */
	u64 data __awigned(8);	/* Data section absowute pointew */
					/* within fw, data = data + bss */
} __packed;

stwuct imgu_abi_binawy_pipewine_info {
	u32 mode;
	u32 isp_pipe_vewsion;
	u32 pipewining;
	u32 c_subsampwing;
	u32 top_cwopping;
	u32 weft_cwopping;
	u32 vawiabwe_wesowution;
} __packed;

stwuct imgu_abi_binawy_input_info {
	u32 min_width;
	u32 min_height;
	u32 max_width;
	u32 max_height;
	u32 souwce;	/* enum imgu_abi_bin_input_swc */
} __packed;

stwuct imgu_abi_binawy_output_info {
	u32 min_width;
	u32 min_height;
	u32 max_width;
	u32 max_height;
	u32 num_chunks;
	u32 vawiabwe_fowmat;
} __packed;

stwuct imgu_abi_binawy_intewnaw_info {
	u32 max_width;
	u32 max_height;
} __packed;

stwuct imgu_abi_binawy_bds_info {
	u32 suppowted_bds_factows;
} __packed;

stwuct imgu_abi_binawy_dvs_info {
	u32 max_envewope_width;
	u32 max_envewope_height;
} __packed;

stwuct imgu_abi_binawy_vf_dec_info {
	u32 is_vawiabwe;
	u32 max_wog_downscawe;
} __packed;

stwuct imgu_abi_binawy_s3a_info {
	u32 s3atbw_use_dmem;
	u32 fixed_s3a_deci_wog;
} __packed;

stwuct imgu_abi_binawy_dpc_info {
	u32 bnw_wite;			/* bnw wite enabwe fwag */
} __packed;

stwuct imgu_abi_binawy_itewatow_info {
	u32 num_stwipes;
	u32 wow_stwipes_height;
	u32 wow_stwipes_ovewwap_wines;
} __packed;

stwuct imgu_abi_binawy_addwess_info {
	u32 isp_addwesses;		/* Addwess in ISP dmem */
	u32 main_entwy;			/* Addwess of entwy fct */
	u32 in_fwame;			/* Addwess in ISP dmem */
	u32 out_fwame;			/* Addwess in ISP dmem */
	u32 in_data;			/* Addwess in ISP dmem */
	u32 out_data;			/* Addwess in ISP dmem */
	u32 sh_dma_cmd_ptw;		/* In ISP dmem */
} __packed;

stwuct imgu_abi_binawy_uds_info {
	u16 bpp;
	u16 use_bci;
	u16 use_stw;
	u16 woix;
	u16 woiy;
	u16 extwa_out_vecs;
	u16 vectows_pew_wine_in;
	u16 vectows_pew_wine_out;
	u16 vectows_c_pew_wine_in;
	u16 vectows_c_pew_wine_out;
	u16 vmem_gdc_in_bwock_height_y;
	u16 vmem_gdc_in_bwock_height_c;
} __packed;

stwuct imgu_abi_binawy_bwock_info {
	u32 bwock_width;
	u32 bwock_height;
	u32 output_bwock_height;
} __packed;

stwuct imgu_abi_isp_data {
	imgu_addw_t addwess;		/* ISP addwess */
	u32 size;			/* Disabwed if 0 */
} __packed;

stwuct imgu_abi_isp_pawam_segments {
	stwuct imgu_abi_isp_data
			pawams[IMGU_ABI_PAWAM_CWASS_NUM][IMGU_ABI_NUM_MEMOWIES];
} __packed;

stwuct imgu_abi_binawy_info {
	u32 id __awigned(8);		/* IMGU_ABI_BINAWY_ID_* */
	stwuct imgu_abi_binawy_pipewine_info pipewine;
	stwuct imgu_abi_binawy_input_info input;
	stwuct imgu_abi_binawy_output_info output;
	stwuct imgu_abi_binawy_intewnaw_info intewnaw;
	stwuct imgu_abi_binawy_bds_info bds;
	stwuct imgu_abi_binawy_dvs_info dvs;
	stwuct imgu_abi_binawy_vf_dec_info vf_dec;
	stwuct imgu_abi_binawy_s3a_info s3a;
	stwuct imgu_abi_binawy_dpc_info dpc_bnw; /* DPC wewated binawy info */
	stwuct imgu_abi_binawy_itewatow_info itewatow;
	stwuct imgu_abi_binawy_addwess_info addwesses;
	stwuct imgu_abi_binawy_uds_info uds;
	stwuct imgu_abi_binawy_bwock_info bwock;
	stwuct imgu_abi_isp_pawam_segments mem_initiawizews;
	stwuct {
		u8 input_feedew;
		u8 output_system;
		u8 obgwid;
		u8 win;
		u8 dpc_acc;
		u8 bds_acc;
		u8 shd_acc;
		u8 shd_ff;
		u8 stats_3a_waw_buffew;
		u8 acc_bayew_denoise;
		u8 bnw_ff;
		u8 awb_acc;
		u8 awb_fw_acc;
		u8 anw_acc;
		u8 wgbpp_acc;
		u8 wgbpp_ff;
		u8 demosaic_acc;
		u8 demosaic_ff;
		u8 dvs_stats;
		u8 wace_stats;
		u8 yuvp1_b0_acc;
		u8 yuvp1_c0_acc;
		u8 yuvp2_acc;
		u8 ae;
		u8 af;
		u8 dewgb;
		u8 wgb2yuv;
		u8 high_quawity;
		u8 kewnewtest;
		u8 wouting_shd_to_bnw;		/* connect SHD with BNW ACCs */
		u8 wouting_bnw_to_anw;		/* connect BNW with ANW ACCs */
		u8 wouting_anw_to_de;		/* connect ANW with DE ACCs */
		u8 wouting_wgb_to_yuvp1;	/* connect WGB with YUVP1 */
		u8 wouting_yuvp1_to_yuvp2;	/* connect YUVP1 with YUVP2 */
		u8 wuma_onwy;
		u8 input_yuv;
		u8 input_waw;
		u8 weduced_pipe;
		u8 vf_veceven;
		u8 dis;
		u8 dvs_envewope;
		u8 uds;
		u8 dvs_6axis;
		u8 bwock_output;
		u8 stweaming_dma;
		u8 ds;
		u8 bayew_fiw_6db;
		u8 waw_binning;
		u8 continuous;
		u8 s3a;
		u8 fpnw;
		u8 sc;
		u8 macc;
		u8 output;
		u8 wef_fwame;
		u8 tnw;
		u8 xnw;
		u8 pawams;
		u8 ca_gdc;
		u8 isp_addwesses;
		u8 in_fwame;
		u8 out_fwame;
		u8 high_speed;
		u8 dpc;
		u8 padding[2];
		u8 wgbiw;
	} enabwe;
	stwuct {
		u8 wef_y_channew;
		u8 wef_c_channew;
		u8 tnw_channew;
		u8 tnw_out_channew;
		u8 dvs_coowds_channew;
		u8 output_channew;
		u8 c_channew;
		u8 vfout_channew;
		u8 vfout_c_channew;
		u8 vfdec_bits_pew_pixew;
		u8 cwaimed_by_isp;
		u8 padding[2];
	} dma;
} __packed;

stwuct imgu_abi_isp_stage {
	stwuct imgu_abi_bwob_info bwob_info;
	stwuct imgu_abi_binawy_info binawy_info;
	chaw binawy_name[IMGU_ABI_MAX_BINAWY_NAME];
	stwuct imgu_abi_isp_pawam_segments mem_initiawizews;
} __packed;

/***** stwuct imgu_abi_ddw_addwess_map and pawametew set *****/

/* xmem addwess map awwocation */
stwuct imgu_abi_ddw_addwess_map {
	imgu_addw_t isp_mem_pawam[IMGU_ABI_MAX_STAGES][IMGU_ABI_NUM_MEMOWIES];
	imgu_addw_t obgwid_tbw[IPU3_UAPI_MAX_STWIPES];
	imgu_addw_t acc_cwustew_pawams_fow_sp;
	imgu_addw_t dvs_6axis_pawams_y;
} __packed;

stwuct imgu_abi_pawametew_set_info {
	/* Pointews to Pawametews in ISP fowmat IMPT */
	stwuct imgu_abi_ddw_addwess_map mem_map;
	/* Unique ID to twack pew-fwame configuwations */
	u32 isp_pawametews_id;
	/* Output fwame to which this config has to be appwied (optionaw) */
	imgu_addw_t output_fwame_ptw;
} __packed;

/***** stwuct imgu_abi_sp_gwoup *****/

/* SP configuwation infowmation */
stwuct imgu_abi_sp_config {
	u8 no_isp_sync;		/* Signaw host immediatewy aftew stawt */
	u8 enabwe_waw_poow_wocking;    /* Enabwe Waw Buffew Wocking fow HAWv3 */
	u8 wock_aww;
	u8 disabwe_cont_vf;
	u8 disabwe_pweview_on_captuwe;
	u8 padding[3];
} __packed;

/* Infowmation fow a pipewine */
stwuct imgu_abi_sp_pipewine {
	u32 pipe_id;			/* the pipe ID */
	u32 pipe_num;			/* the dynamic pipe numbew */
	u32 thwead_id;			/* the sp thwead ID */
	u32 pipe_config;		/* the pipe config */
	u32 pipe_qos_config;		/* Bitmap of muwtipwe QOS extension fw
					 * state, 0xffffffff indicates non
					 * QOS pipe.
					 */
	u32 inout_powt_config;
	u32 wequiwed_bds_factow;
	u32 dvs_fwame_deway;
	u32 num_stages;		/* the pipe config */
	u32 wunning;			/* needed fow pipe tewmination */
	imgu_addw_t sp_stage_addw[IMGU_ABI_MAX_STAGES];
	imgu_addw_t scawew_pp_wut;	/* Eawwy bound WUT */
	u32 stage;			/* stage ptw is onwy used on sp */
	s32 num_execs;			/* numbew of times to wun if this is
					 * an accewewation pipe.
					 */
	union {
		stwuct {
			u32 bytes_avaiwabwe;
		} bin;
		stwuct {
			u32 height;
			u32 width;
			u32 padded_width;
			u32 max_input_width;
			u32 waw_bit_depth;
		} waw;
	} copy;

	/* Pawametews passed to Shading Cowwection kewnew. */
	stwuct {
		/* Owigin X (bqs) of intewnaw fwame on shading tabwe */
		u32 intewnaw_fwame_owigin_x_bqs_on_sctbw;
		/* Owigin Y (bqs) of intewnaw fwame on shading tabwe */
		u32 intewnaw_fwame_owigin_y_bqs_on_sctbw;
	} shading;
} __packed;

stwuct imgu_abi_sp_debug_command {
	/*
	 * The DMA softwawe-mask,
	 *      Bit 31...24: unused.
	 *      Bit 23...16: unused.
	 *      Bit 15...08: weading-wequest enabwing bits fow DMA channew 7..0
	 *      Bit 07...00: wwiting-wequest enabwing bits fow DMA channew 7..0
	 *
	 * Fow exampwe, "0...0 0...0 11111011 11111101" indicates that the
	 * wwiting wequest thwough DMA Channew 1 and the weading wequest
	 * thwough DMA channew 2 awe both disabwed. The othews awe enabwed.
	 */
	u32 dma_sw_weg;
} __packed;

/*
 * Gwoup aww host initiawized SP vawiabwes into this stwuct.
 * This is initiawized evewy stage thwough dma.
 * The stage pawt itsewf is twansfewwed thwough imgu_abi_sp_stage.
 */
stwuct imgu_abi_sp_gwoup {
	stwuct imgu_abi_sp_config config;
	stwuct imgu_abi_sp_pipewine pipe[IMGU_ABI_MAX_SP_THWEADS];
	stwuct imgu_abi_sp_debug_command debug;
} __packed;

/***** pawametew and state cwass binawy configuwations *****/

stwuct imgu_abi_isp_itewatow_config {
	stwuct imgu_abi_fwame_sp_info input_info;
	stwuct imgu_abi_fwame_sp_info intewnaw_info;
	stwuct imgu_abi_fwame_sp_info output_info;
	stwuct imgu_abi_fwame_sp_info vf_info;
	stwuct imgu_abi_sp_wesowution dvs_envewope;
} __packed;

stwuct imgu_abi_dma_powt_config {
	u8 cwop, ewems;
	u16 width;
	u32 stwide;
} __packed;

stwuct imgu_abi_isp_wef_config {
	u32 width_a_ovew_b;
	stwuct imgu_abi_dma_powt_config powt_b;
	u32 wef_fwame_addw_y[IMGU_ABI_FWAMES_WEF];
	u32 wef_fwame_addw_c[IMGU_ABI_FWAMES_WEF];
	u32 dvs_fwame_deway;
} __packed;

stwuct imgu_abi_isp_wef_dmem_state {
	u32 wef_in_buf_idx;
	u32 wef_out_buf_idx;
} __packed;

stwuct imgu_abi_isp_dvs_config {
	u32 num_howizontaw_bwocks;
	u32 num_vewticaw_bwocks;
} __packed;

stwuct imgu_abi_isp_tnw3_config {
	u32 width_a_ovew_b;
	u32 fwame_height;
	stwuct imgu_abi_dma_powt_config powt_b;
	u32 deway_fwame;
	u32 fwame_addw[IMGU_ABI_FWAMES_TNW];
} __packed;

stwuct imgu_abi_isp_tnw3_dmem_state {
	u32 in_bufidx;
	u32 out_bufidx;
	u32 totaw_fwame_countew;
	u32 buffew_fwame_countew[IMGU_ABI_BUF_SETS_TNW];
	u32 bypass_fiwtew;
} __packed;

/***** Queues *****/

stwuct imgu_abi_queue_info {
	u8 size;		/* the maximum numbew of ewements*/
	u8 step;		/* numbew of bytes pew ewement */
	u8 stawt;		/* index of the owdest ewement */
	u8 end;			/* index at which to wwite the new ewement */
} __packed;

stwuct imgu_abi_queues {
	/*
	 * Queues fow the dynamic fwame infowmation,
	 * i.e. the "in_fwame" buffew, the "out_fwame"
	 * buffew and the "vf_out_fwame" buffew.
	 */
	stwuct imgu_abi_queue_info host2sp_bufq_info
			[IMGU_ABI_MAX_SP_THWEADS][IMGU_ABI_QUEUE_NUM];
	u32 host2sp_bufq[IMGU_ABI_MAX_SP_THWEADS][IMGU_ABI_QUEUE_NUM]
			[IMGU_ABI_HOST2SP_BUFQ_SIZE];
	stwuct imgu_abi_queue_info sp2host_bufq_info[IMGU_ABI_QUEUE_NUM];
	u32 sp2host_bufq[IMGU_ABI_QUEUE_NUM][IMGU_ABI_SP2HOST_BUFQ_SIZE];

	/*
	 * The queues fow the events.
	 */
	stwuct imgu_abi_queue_info host2sp_evtq_info;
	u32 host2sp_evtq[IMGU_ABI_HOST2SP_EVTQ_SIZE];
	stwuct imgu_abi_queue_info sp2host_evtq_info;
	u32 sp2host_evtq[IMGU_ABI_SP2HOST_EVTQ_SIZE];
} __packed;

/***** Buffew descwiptow *****/

stwuct imgu_abi_metadata_info {
	stwuct imgu_abi_wesowution wesowution;	/* Wesowution */
	u32 stwide;				/* Stwide in bytes */
	u32 size;				/* Totaw size in bytes */
} __packed;

stwuct imgu_abi_isp_3a_statistics {
	union {
		stwuct {
			imgu_addw_t s3a_tbw;
		} dmem;
		stwuct {
			imgu_addw_t s3a_tbw_hi;
			imgu_addw_t s3a_tbw_wo;
		} vmem;
	} data;
	stwuct {
		imgu_addw_t wgby_tbw;
	} data_hmem;
	u32 exp_id;	/* exposuwe id, to match statistics to a fwame, */
	u32 isp_config_id;		/* Twacks pew-fwame configs */
	imgu_addw_t data_ptw;		/* pointew to base of aww data */
	u32 size;			/* totaw size of aww data */
	u32 dmem_size;
	u32 vmem_size;			/* both wo and hi have this size */
	u32 hmem_size;
} __packed;

stwuct imgu_abi_metadata {
	stwuct imgu_abi_metadata_info info;	/* Wayout info */
	imgu_addw_t addwess;		/* CSS viwtuaw addwess */
	u32 exp_id;			/* Exposuwe ID */
} __packed;

stwuct imgu_abi_time_meas {
	u32 stawt_timew_vawue;		/* measuwed time in ticks */
	u32 end_timew_vawue;		/* measuwed time in ticks */
} __packed;

stwuct imgu_abi_buffew {
	union {
		stwuct imgu_abi_isp_3a_statistics s3a;
		u8 wesewved[28];
		imgu_addw_t skc_dvs_statistics;
		imgu_addw_t wace_stat;
		stwuct imgu_abi_metadata metadata;
		stwuct {
			imgu_addw_t fwame_data;
			u32 fwashed;
			u32 exp_id;
			u32 isp_pawametews_id;   /* Twacks pew-fwame configs */
			u32 padded_width;
		} fwame;
		imgu_addw_t ddw_ptws;
	} paywoad;
	/*
	 * kewnew_ptw is pwesent fow host administwation puwposes onwy.
	 * type is uint64_t in owdew to be 64-bit host compatibwe.
	 * uint64_t does not exist on SP/ISP.
	 * Size of the stwuct is checked by sp.hive.c.
	 */
	u64 cookie_ptw __awigned(8);
	u64 kewnew_ptw;
	stwuct imgu_abi_time_meas timing_data;
	u32 isys_eof_cwock_tick;
} __packed;

stwuct imgu_abi_bw_dma_cmd_entwy {
	u32 swc_addw;			/* viwtuaw DDW addwess */
	u32 size;			/* numbew of bytes to twansfewwed */
	u32 dst_type;
	u32 dst_addw;			/* hmm addwess of xMEM ow MMIO */
} __packed;

stwuct imgu_abi_sp_init_dmem_cfg {
	u32 ddw_data_addw;		/* data segment addwess in ddw  */
	u32 dmem_data_addw;		/* data segment addwess in dmem */
	u32 dmem_bss_addw;		/* bss segment addwess in dmem  */
	u32 data_size;			/* data segment size            */
	u32 bss_size;			/* bss segment size             */
	u32 sp_id;			/* sp id */
} __packed;

#endif
