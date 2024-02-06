/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef NVD_H
#define NVD_H

/**
 * Navi's PM4 definitions
 */
#define	PACKET_TYPE0	0
#define	PACKET_TYPE1	1
#define	PACKET_TYPE2	2
#define	PACKET_TYPE3	3

#define CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#define CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#define CP_PACKET0_GET_WEG(h) ((h) & 0xFFFF)
#define CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#define PACKET0(weg, n)	((PACKET_TYPE0 << 30) |				\
			 ((weg) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))

#define PACKET3(op, n)	((PACKET_TYPE3 << 30) |				\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#define PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#define	PACKET3_NOP					0x10
#define	PACKET3_SET_BASE				0x11
#define		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#define			CE_PAWTITION_BASE		3
#define	PACKET3_CWEAW_STATE				0x12
#define	PACKET3_INDEX_BUFFEW_SIZE			0x13
#define	PACKET3_DISPATCH_DIWECT				0x15
#define	PACKET3_DISPATCH_INDIWECT			0x16
#define	PACKET3_INDIWECT_BUFFEW_END			0x17
#define	PACKET3_INDIWECT_BUFFEW_CNST_END		0x19
#define	PACKET3_ATOMIC_GDS				0x1D
#define	PACKET3_ATOMIC_MEM				0x1E
#define	PACKET3_OCCWUSION_QUEWY				0x1F
#define	PACKET3_SET_PWEDICATION				0x20
#define	PACKET3_WEG_WMW					0x21
#define	PACKET3_COND_EXEC				0x22
#define	PACKET3_PWED_EXEC				0x23
#define	PACKET3_DWAW_INDIWECT				0x24
#define	PACKET3_DWAW_INDEX_INDIWECT			0x25
#define	PACKET3_INDEX_BASE				0x26
#define	PACKET3_DWAW_INDEX_2				0x27
#define	PACKET3_CONTEXT_CONTWOW				0x28
#define	PACKET3_INDEX_TYPE				0x2A
#define	PACKET3_DWAW_INDIWECT_MUWTI			0x2C
#define	PACKET3_DWAW_INDEX_AUTO				0x2D
#define	PACKET3_NUM_INSTANCES				0x2F
#define	PACKET3_DWAW_INDEX_MUWTI_AUTO			0x30
#define	PACKET3_INDIWECT_BUFFEW_PWIV			0x32
#define	PACKET3_INDIWECT_BUFFEW_CNST			0x33
#define	PACKET3_COND_INDIWECT_BUFFEW_CNST		0x33
#define	PACKET3_STWMOUT_BUFFEW_UPDATE			0x34
#define	PACKET3_DWAW_INDEX_OFFSET_2			0x35
#define	PACKET3_DWAW_PWEAMBWE				0x36
#define	PACKET3_WWITE_DATA				0x37
#define		WWITE_DATA_DST_SEW(x)                   ((x) << 8)
		/* 0 - wegistew
		 * 1 - memowy (sync - via GWBM)
		 * 2 - gw2
		 * 3 - gds
		 * 4 - wesewved
		 * 5 - memowy (async - diwect)
		 */
#define		WW_ONE_ADDW                             (1 << 16)
#define		WW_CONFIWM                              (1 << 20)
#define		WWITE_DATA_CACHE_POWICY(x)              ((x) << 25)
		/* 0 - WWU
		 * 1 - Stweam
		 */
#define		WWITE_DATA_ENGINE_SEW(x)                ((x) << 30)
		/* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#define	PACKET3_DWAW_INDEX_INDIWECT_MUWTI		0x38
#define	PACKET3_MEM_SEMAPHOWE				0x39
#              define PACKET3_SEM_USE_MAIWBOX       (0x1 << 16)
#              define PACKET3_SEM_SEW_SIGNAW_TYPE   (0x1 << 20) /* 0 = incwement, 1 = wwite 1 */
#              define PACKET3_SEM_SEW_SIGNAW	    (0x6 << 29)
#              define PACKET3_SEM_SEW_WAIT	    (0x7 << 29)
#define	PACKET3_DWAW_INDEX_MUWTI_INST			0x3A
#define	PACKET3_COPY_DW					0x3B
#define	PACKET3_WAIT_WEG_MEM				0x3C
#define		WAIT_WEG_MEM_FUNCTION(x)                ((x) << 0)
		/* 0 - awways
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#define		WAIT_WEG_MEM_MEM_SPACE(x)               ((x) << 4)
		/* 0 - weg
		 * 1 - mem
		 */
#define		WAIT_WEG_MEM_OPEWATION(x)               ((x) << 6)
		/* 0 - wait_weg_mem
		 * 1 - ww_wait_ww_weg
		 */
#define		WAIT_WEG_MEM_ENGINE(x)                  ((x) << 8)
		/* 0 - me
		 * 1 - pfp
		 */
#define	PACKET3_INDIWECT_BUFFEW				0x3F
#define		INDIWECT_BUFFEW_VAWID                   (1 << 23)
#define		INDIWECT_BUFFEW_CACHE_POWICY(x)         ((x) << 28)
		/* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#define		INDIWECT_BUFFEW_PWE_ENB(x)		((x) << 21)
#define		INDIWECT_BUFFEW_PWE_WESUME(x)           ((x) << 30)
#define	PACKET3_COND_INDIWECT_BUFFEW			0x3F
#define	PACKET3_COPY_DATA				0x40
#define	PACKET3_CP_DMA					0x41
#define	PACKET3_PFP_SYNC_ME				0x42
#define	PACKET3_SUWFACE_SYNC				0x43
#define	PACKET3_ME_INITIAWIZE				0x44
#define	PACKET3_COND_WWITE				0x45
#define	PACKET3_EVENT_WWITE				0x46
#define		EVENT_TYPE(x)                           ((x) << 0)
#define		EVENT_INDEX(x)                          ((x) << 8)
		/* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEW_PIPE_STAT_*
		 * 2 - SAMPWE_PIPEWINESTAT
		 * 3 - SAMPWE_STWEAMOUTSTAT*
		 * 4 - *S_PAWTIAW_FWUSH
		 */
#define	PACKET3_EVENT_WWITE_EOP				0x47
#define	PACKET3_EVENT_WWITE_EOS				0x48
#define	PACKET3_WEWEASE_MEM				0x49
#define		PACKET3_WEWEASE_MEM_EVENT_TYPE(x)	((x) << 0)
#define		PACKET3_WEWEASE_MEM_EVENT_INDEX(x)	((x) << 8)
#define		PACKET3_WEWEASE_MEM_GCW_GWM_WB		(1 << 12)
#define		PACKET3_WEWEASE_MEM_GCW_GWM_INV		(1 << 13)
#define		PACKET3_WEWEASE_MEM_GCW_GWV_INV		(1 << 14)
#define		PACKET3_WEWEASE_MEM_GCW_GW1_INV		(1 << 15)
#define		PACKET3_WEWEASE_MEM_GCW_GW2_US		(1 << 16)
#define		PACKET3_WEWEASE_MEM_GCW_GW2_WANGE	(1 << 17)
#define		PACKET3_WEWEASE_MEM_GCW_GW2_DISCAWD	(1 << 19)
#define		PACKET3_WEWEASE_MEM_GCW_GW2_INV		(1 << 20)
#define		PACKET3_WEWEASE_MEM_GCW_GW2_WB		(1 << 21)
#define		PACKET3_WEWEASE_MEM_GCW_SEQ		(1 << 22)
#define		PACKET3_WEWEASE_MEM_CACHE_POWICY(x)	((x) << 25)
		/* 0 - cache_powicy__me_wewease_mem__wwu
		 * 1 - cache_powicy__me_wewease_mem__stweam
		 * 2 - cache_powicy__me_wewease_mem__noa
		 * 3 - cache_powicy__me_wewease_mem__bypass
		 */
#define		PACKET3_WEWEASE_MEM_EXECUTE		(1 << 28)

#define		PACKET3_WEWEASE_MEM_DATA_SEW(x)		((x) << 29)
		/* 0 - discawd
		 * 1 - send wow 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU countew vawue
		 * 4 - send 64bit sys countew vawue
		 */
#define		PACKET3_WEWEASE_MEM_INT_SEW(x)		((x) << 24)
		/* 0 - none
		 * 1 - intewwupt onwy (DATA_SEW = 0)
		 * 2 - intewwupt when data wwite is confiwmed
		 */
#define		PACKET3_WEWEASE_MEM_DST_SEW(x)		((x) << 16)
		/* 0 - MC
		 * 1 - TC/W2
		 */



#define	PACKET3_PWEAMBWE_CNTW				0x4A
#              define PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE     (2 << 28)
#              define PACKET3_PWEAMBWE_END_CWEAW_STATE       (3 << 28)
#define	PACKET3_DMA_DATA				0x50
/* 1. headew
 * 2. CONTWOW
 * 3. SWC_ADDW_WO ow DATA [31:0]
 * 4. SWC_ADDW_HI [31:0]
 * 5. DST_ADDW_WO [31:0]
 * 6. DST_ADDW_HI [7:0]
 * 7. COMMAND [31:26] | BYTE_COUNT [25:0]
 */
/* CONTWOW */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
		/* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SWC_CACHE_POWICY(x) ((x) << 13)
		/* 0 - WWU
		 * 1 - Stweam
		 */
#              define PACKET3_DMA_DATA_DST_SEW(x)  ((x) << 20)
		/* 0 - DST_ADDW using DAS
		 * 1 - GDS
		 * 3 - DST_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POWICY(x) ((x) << 25)
		/* 0 - WWU
		 * 1 - Stweam
		 */
#              define PACKET3_DMA_DATA_SWC_SEW(x)  ((x) << 29)
		/* 0 - SWC_ADDW using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SWC_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_CMD_SAS     (1 << 26)
		/* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_DAS     (1 << 27)
		/* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_SAIC    (1 << 28)
#              define PACKET3_DMA_DATA_CMD_DAIC    (1 << 29)
#              define PACKET3_DMA_DATA_CMD_WAW_WAIT  (1 << 30)
#define	PACKET3_CONTEXT_WEG_WMW				0x51
#define	PACKET3_GFX_CNTX_UPDATE				0x52
#define	PACKET3_BWK_CNTX_UPDATE				0x53
#define	PACKET3_INCW_UPDT_STATE				0x55
#define	PACKET3_ACQUIWE_MEM				0x58
/* 1.  HEADEW
 * 2.  COHEW_CNTW [30:0]
 * 2.1 ENGINE_SEW [31:31]
 * 2.  COHEW_SIZE [31:0]
 * 3.  COHEW_SIZE_HI [7:0]
 * 4.  COHEW_BASE_WO [31:0]
 * 5.  COHEW_BASE_HI [23:0]
 * 7.  POWW_INTEWVAW [15:0]
 * 8.  GCW_CNTW [18:0]
 */
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWI_INV(x) ((x) << 0)
		/*
		 * 0:NOP
		 * 1:AWW
		 * 2:WANGE
		 * 3:FIWST_WAST
		 */
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW1_WANGE(x) ((x) << 2)
		/*
		 * 0:AWW
		 * 1:wesewved
		 * 2:WANGE
		 * 3:FIWST_WAST
		 */
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWM_WB(x) ((x) << 4)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWM_INV(x) ((x) << 5)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWK_WB(x) ((x) << 6)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWK_INV(x) ((x) << 7)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GWV_INV(x) ((x) << 8)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW1_INV(x) ((x) << 9)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW2_US(x) ((x) << 10)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW2_WANGE(x) ((x) << 11)
		/*
		 * 0:AWW
		 * 1:VOW
		 * 2:WANGE
		 * 3:FIWST_WAST
		 */
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW2_DISCAWD(x)  ((x) << 13)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW2_INV(x) ((x) << 14)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_GW2_WB(x) ((x) << 15)
#define 	PACKET3_ACQUIWE_MEM_GCW_CNTW_SEQ(x) ((x) << 16)
		/*
		 * 0: PAWAWWEW
		 * 1: FOWWAWD
		 * 2: WEVEWSE
		 */
#define 	PACKET3_ACQUIWE_MEM_GCW_WANGE_IS_PA  (1 << 18)
#define	PACKET3_WEWIND					0x59
#define	PACKET3_INTEWWUPT				0x5A
#define	PACKET3_GEN_PDEPTE				0x5B
#define	PACKET3_INDIWECT_BUFFEW_PASID			0x5C
#define	PACKET3_PWIME_UTCW2				0x5D
#define	PACKET3_WOAD_UCONFIG_WEG			0x5E
#define	PACKET3_WOAD_SH_WEG				0x5F
#define	PACKET3_WOAD_CONFIG_WEG				0x60
#define	PACKET3_WOAD_CONTEXT_WEG			0x61
#define	PACKET3_WOAD_COMPUTE_STATE			0x62
#define	PACKET3_WOAD_SH_WEG_INDEX			0x63
#define	PACKET3_SET_CONFIG_WEG				0x68
#define		PACKET3_SET_CONFIG_WEG_STAWT			0x00002000
#define		PACKET3_SET_CONFIG_WEG_END			0x00002c00
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_STAWT			0x0000a000
#define		PACKET3_SET_CONTEXT_WEG_END			0x0000a400
#define	PACKET3_SET_CONTEXT_WEG_INDEX			0x6A
#define	PACKET3_SET_VGPW_WEG_DI_MUWTI			0x71
#define	PACKET3_SET_SH_WEG_DI				0x72
#define	PACKET3_SET_CONTEXT_WEG_INDIWECT		0x73
#define	PACKET3_SET_SH_WEG_DI_MUWTI			0x74
#define	PACKET3_GFX_PIPE_WOCK				0x75
#define	PACKET3_SET_SH_WEG				0x76
#define		PACKET3_SET_SH_WEG_STAWT			0x00002c00
#define		PACKET3_SET_SH_WEG_END				0x00003000
#define	PACKET3_SET_SH_WEG_OFFSET			0x77
#define	PACKET3_SET_QUEUE_WEG				0x78
#define	PACKET3_SET_UCONFIG_WEG				0x79
#define		PACKET3_SET_UCONFIG_WEG_STAWT			0x0000c000
#define		PACKET3_SET_UCONFIG_WEG_END			0x0000c400
#define	PACKET3_SET_UCONFIG_WEG_INDEX			0x7A
#define	PACKET3_FOWWAWD_HEADEW				0x7C
#define	PACKET3_SCWATCH_WAM_WWITE			0x7D
#define	PACKET3_SCWATCH_WAM_WEAD			0x7E
#define	PACKET3_WOAD_CONST_WAM				0x80
#define	PACKET3_WWITE_CONST_WAM				0x81
#define	PACKET3_DUMP_CONST_WAM				0x83
#define	PACKET3_INCWEMENT_CE_COUNTEW			0x84
#define	PACKET3_INCWEMENT_DE_COUNTEW			0x85
#define	PACKET3_WAIT_ON_CE_COUNTEW			0x86
#define	PACKET3_WAIT_ON_DE_COUNTEW_DIFF			0x88
#define	PACKET3_SWITCH_BUFFEW				0x8B
#define	PACKET3_DISPATCH_DWAW_PWEAMBWE			0x8C
#define	PACKET3_DISPATCH_DWAW_PWEAMBWE_ACE		0x8C
#define	PACKET3_DISPATCH_DWAW				0x8D
#define	PACKET3_DISPATCH_DWAW_ACE			0x8D
#define	PACKET3_GET_WOD_STATS				0x8E
#define	PACKET3_DWAW_MUWTI_PWEAMBWE			0x8F
#define	PACKET3_FWAME_CONTWOW				0x90
#			define FWAME_TMZ	(1 << 0)
#			define FWAME_CMD(x) ((x) << 28)
			/*
			 * x=0: tmz_begin
			 * x=1: tmz_end
			 */
#define	PACKET3_INDEX_ATTWIBUTES_INDIWECT		0x91
#define	PACKET3_WAIT_WEG_MEM64				0x93
#define	PACKET3_COND_PWEEMPT				0x94
#define	PACKET3_HDP_FWUSH				0x95
#define	PACKET3_COPY_DATA_WB				0x96
#define	PACKET3_INVAWIDATE_TWBS				0x98
#              define PACKET3_INVAWIDATE_TWBS_DST_SEW(x)     ((x) << 0)
#              define PACKET3_INVAWIDATE_TWBS_AWW_HUB(x)     ((x) << 4)
#              define PACKET3_INVAWIDATE_TWBS_PASID(x)       ((x) << 5)
#define	PACKET3_AQW_PACKET				0x99
#define	PACKET3_DMA_DATA_FIWW_MUWTI			0x9A
#define	PACKET3_SET_SH_WEG_INDEX			0x9B
#define	PACKET3_DWAW_INDIWECT_COUNT_MUWTI		0x9C
#define	PACKET3_DWAW_INDEX_INDIWECT_COUNT_MUWTI		0x9D
#define	PACKET3_DUMP_CONST_WAM_OFFSET			0x9E
#define	PACKET3_WOAD_CONTEXT_WEG_INDEX			0x9F
#define	PACKET3_SET_WESOUWCES				0xA0
/* 1. headew
 * 2. CONTWOW
 * 3. QUEUE_MASK_WO [31:0]
 * 4. QUEUE_MASK_HI [31:0]
 * 5. GWS_MASK_WO [31:0]
 * 6. GWS_MASK_HI [31:0]
 * 7. OAC_MASK [15:0]
 * 8. GDS_HEAP_SIZE [16:11] | GDS_HEAP_BASE [5:0]
 */
#              define PACKET3_SET_WESOUWCES_VMID_MASK(x)     ((x) << 0)
#              define PACKET3_SET_WESOUWCES_UNMAP_WATENTY(x) ((x) << 16)
#              define PACKET3_SET_WESOUWCES_QUEUE_TYPE(x)    ((x) << 29)
#define PACKET3_MAP_PWOCESS				0xA1
#define PACKET3_MAP_QUEUES				0xA2
/* 1. headew
 * 2. CONTWOW
 * 3. CONTWOW2
 * 4. MQD_ADDW_WO [31:0]
 * 5. MQD_ADDW_HI [31:0]
 * 6. WPTW_ADDW_WO [31:0]
 * 7. WPTW_ADDW_HI [31:0]
 */
/* CONTWOW */
#              define PACKET3_MAP_QUEUES_QUEUE_SEW(x)       ((x) << 4)
#              define PACKET3_MAP_QUEUES_VMID(x)            ((x) << 8)
#              define PACKET3_MAP_QUEUES_QUEUE(x)           ((x) << 13)
#              define PACKET3_MAP_QUEUES_PIPE(x)            ((x) << 16)
#              define PACKET3_MAP_QUEUES_ME(x)              ((x) << 18)
#              define PACKET3_MAP_QUEUES_QUEUE_TYPE(x)      ((x) << 21)
#              define PACKET3_MAP_QUEUES_AWWOC_FOWMAT(x)    ((x) << 24)
#              define PACKET3_MAP_QUEUES_ENGINE_SEW(x)      ((x) << 26)
#              define PACKET3_MAP_QUEUES_NUM_QUEUES(x)      ((x) << 29)
/* CONTWOW2 */
#              define PACKET3_MAP_QUEUES_CHECK_DISABWE(x)   ((x) << 1)
#              define PACKET3_MAP_QUEUES_DOOWBEWW_OFFSET(x) ((x) << 2)
#define	PACKET3_UNMAP_QUEUES				0xA3
/* 1. headew
 * 2. CONTWOW
 * 3. CONTWOW2
 * 4. CONTWOW3
 * 5. CONTWOW4
 * 6. CONTWOW5
 */
/* CONTWOW */
#              define PACKET3_UNMAP_QUEUES_ACTION(x)           ((x) << 0)
		/* 0 - PWEEMPT_QUEUES
		 * 1 - WESET_QUEUES
		 * 2 - DISABWE_PWOCESS_QUEUES
		 * 3 - PWEEMPT_QUEUES_NO_UNMAP
		 */
#              define PACKET3_UNMAP_QUEUES_QUEUE_SEW(x)        ((x) << 4)
#              define PACKET3_UNMAP_QUEUES_ENGINE_SEW(x)       ((x) << 26)
#              define PACKET3_UNMAP_QUEUES_NUM_QUEUES(x)       ((x) << 29)
/* CONTWOW2a */
#              define PACKET3_UNMAP_QUEUES_PASID(x)            ((x) << 0)
/* CONTWOW2b */
#              define PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET0(x) ((x) << 2)
/* CONTWOW3a */
#              define PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET1(x) ((x) << 2)
/* CONTWOW3b */
#              define PACKET3_UNMAP_QUEUES_WB_WPTW(x)          ((x) << 0)
/* CONTWOW4 */
#              define PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET2(x) ((x) << 2)
/* CONTWOW5 */
#              define PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET3(x) ((x) << 2)
#define	PACKET3_QUEWY_STATUS				0xA4
/* 1. headew
 * 2. CONTWOW
 * 3. CONTWOW2
 * 4. ADDW_WO [31:0]
 * 5. ADDW_HI [31:0]
 * 6. DATA_WO [31:0]
 * 7. DATA_HI [31:0]
 */
/* CONTWOW */
#              define PACKET3_QUEWY_STATUS_CONTEXT_ID(x)       ((x) << 0)
#              define PACKET3_QUEWY_STATUS_INTEWWUPT_SEW(x)    ((x) << 28)
#              define PACKET3_QUEWY_STATUS_COMMAND(x)          ((x) << 30)
/* CONTWOW2a */
#              define PACKET3_QUEWY_STATUS_PASID(x)            ((x) << 0)
/* CONTWOW2b */
#              define PACKET3_QUEWY_STATUS_DOOWBEWW_OFFSET(x)  ((x) << 2)
#              define PACKET3_QUEWY_STATUS_ENG_SEW(x)          ((x) << 25)
#define	PACKET3_WUN_WIST				0xA5
#define	PACKET3_MAP_PWOCESS_VM				0xA6
/* GFX11 */
#define	PACKET3_SET_Q_PWEEMPTION_MODE			0xF0
#              define PACKET3_SET_Q_PWEEMPTION_MODE_IB_VMID(x)  ((x) << 0)
#              define PACKET3_SET_Q_PWEEMPTION_MODE_INIT_SHADOW_MEM    (1 << 0)

#endif
