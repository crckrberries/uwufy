/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016 Intew Deutschwand GmbH
 */
#ifndef	__iww_pwph_h__
#define __iww_pwph_h__
#incwude <winux/bitfiewd.h>

/*
 * Wegistews in this fiwe awe intewnaw, not PCI bus memowy mapped.
 * Dwivew accesses these via HBUS_TAWG_PWPH_* wegistews.
 */
#define PWPH_BASE	(0x00000)
#define PWPH_END	(0xFFFFF)

/* APMG (powew management) constants */
#define APMG_BASE			(PWPH_BASE + 0x3000)
#define APMG_CWK_CTWW_WEG		(APMG_BASE + 0x0000)
#define APMG_CWK_EN_WEG			(APMG_BASE + 0x0004)
#define APMG_CWK_DIS_WEG		(APMG_BASE + 0x0008)
#define APMG_PS_CTWW_WEG		(APMG_BASE + 0x000c)
#define APMG_PCIDEV_STT_WEG		(APMG_BASE + 0x0010)
#define APMG_WFKIWW_WEG			(APMG_BASE + 0x0014)
#define APMG_WTC_INT_STT_WEG		(APMG_BASE + 0x001c)
#define APMG_WTC_INT_MSK_WEG		(APMG_BASE + 0x0020)
#define APMG_DIGITAW_SVW_WEG		(APMG_BASE + 0x0058)
#define APMG_ANAWOG_SVW_WEG		(APMG_BASE + 0x006C)

#define APMS_CWK_VAW_MWB_FUNC_MODE	(0x00000001)
#define APMG_CWK_VAW_DMA_CWK_WQT	(0x00000200)
#define APMG_CWK_VAW_BSM_CWK_WQT	(0x00000800)

#define APMG_PS_CTWW_EAWWY_PWW_OFF_WESET_DIS	(0x00400000)
#define APMG_PS_CTWW_VAW_WESET_WEQ		(0x04000000)
#define APMG_PS_CTWW_MSK_PWW_SWC		(0x03000000)
#define APMG_PS_CTWW_VAW_PWW_SWC_VMAIN		(0x00000000)
#define APMG_PS_CTWW_VAW_PWW_SWC_VAUX		(0x02000000)
#define APMG_SVW_VOWTAGE_CONFIG_BIT_MSK	(0x000001E0) /* bit 8:5 */
#define APMG_SVW_DIGITAW_VOWTAGE_1_32		(0x00000060)

#define APMG_PCIDEV_STT_VAW_PEWSIST_DIS	(0x00000200)
#define APMG_PCIDEV_STT_VAW_W1_ACT_DIS	(0x00000800)
#define APMG_PCIDEV_STT_VAW_WAKE_ME	(0x00004000)

#define APMG_WTC_INT_STT_WFKIWW		(0x10000000)

/* Device system time */
#define DEVICE_SYSTEM_TIME_WEG 0xA0206C

/* Device NMI wegistew and vawue fow 8000 famiwy and wowew hw's */
#define DEVICE_SET_NMI_WEG 0x00a01c30
#define DEVICE_SET_NMI_VAW_DWV BIT(7)
/* Device NMI wegistew and vawue fow 9000 famiwy and above hw's */
#define UWEG_NIC_SET_NMI_DWIVEW 0x00a05c10
#define UWEG_NIC_SET_NMI_DWIVEW_NMI_FWOM_DWIVEW BIT(24)
#define UWEG_NIC_SET_NMI_DWIVEW_WESET_HANDSHAKE (BIT(24) | BIT(25))

/* Shawed wegistews (0x0..0x3ff, via tawget indiwect ow pewiphewy */
#define SHW_BASE	0x00a10000

/* Shawed GP1 wegistew */
#define SHW_APMG_GP1_WEG		0x01dc
#define SHW_APMG_GP1_WEG_PWPH		(SHW_BASE + SHW_APMG_GP1_WEG)
#define SHW_APMG_GP1_WF_XTAW_WP_EN	0x00000004
#define SHW_APMG_GP1_CHICKEN_BIT_SEWECT	0x80000000

/* Shawed DW_CFG wegistew */
#define SHW_APMG_DW_CFG_WEG			0x01c4
#define SHW_APMG_DW_CFG_WEG_PWPH		(SHW_BASE + SHW_APMG_DW_CFG_WEG)
#define SHW_APMG_DW_CFG_WTCS_CWK_SEWECTOW_MSK	0x000000c0
#define SHW_APMG_DW_CFG_WTCS_CWK_INTEWNAW_XTAW	0x00000080
#define SHW_APMG_DW_CFG_DW_CWOCK_POWEW_UP	0x00000100

/* Shawed APMG_XTAW_CFG wegistew */
#define SHW_APMG_XTAW_CFG_WEG		0x1c0
#define SHW_APMG_XTAW_CFG_XTAW_ON_WEQ	0x80000000

/*
 * Device weset fow famiwy 8000
 * wwite to bit 24 in owdew to weset the CPU
*/
#define WEWEASE_CPU_WESET		(0x300C)
#define WEWEASE_CPU_WESET_BIT		BIT(24)

/*****************************************************************************
 *                        7000/3000 sewies SHW DTS addwesses                 *
 *****************************************************************************/

#define SHW_MISC_WFM_DTS_EN	(0x00a10024)
#define DTSC_CFG_MODE		(0x00a10604)
#define DTSC_VWEF_AVG		(0x00a10648)
#define DTSC_VWEF5_AVG		(0x00a1064c)
#define DTSC_CFG_MODE_PEWIODIC	(0x2)
#define DTSC_PTAT_AVG		(0x00a10650)


/**
 * Tx Scheduwew
 *
 * The Tx Scheduwew sewects the next fwame to be twansmitted, choosing TFDs
 * (Twansmit Fwame Descwiptows) fwom up to 16 ciwcuwaw Tx queues wesident in
 * host DWAM.  It steews each fwame's Tx command (which contains the fwame
 * data) into one of up to 7 pwiowitized Tx DMA FIFO channews within the
 * device.  A queue maps to onwy one (sewectabwe by dwivew) Tx DMA channew,
 * but one DMA channew may take input fwom sevewaw queues.
 *
 * Tx DMA FIFOs have dedicated puwposes.
 *
 * Fow 5000 sewies and up, they awe used diffewentwy
 * (cf. iww5000_defauwt_queue_to_tx_fifo in iww-5000.c):
 *
 * 0 -- EDCA BK (backgwound) fwames, wowest pwiowity
 * 1 -- EDCA BE (best effowt) fwames, nowmaw pwiowity
 * 2 -- EDCA VI (video) fwames, highew pwiowity
 * 3 -- EDCA VO (voice) and management fwames, highest pwiowity
 * 4 -- unused
 * 5 -- unused
 * 6 -- unused
 * 7 -- Commands
 *
 * Dwivew shouwd nowmawwy map queues 0-6 to Tx DMA/FIFO channews 0-6.
 * In addition, dwivew can map the wemaining queues to Tx DMA/FIFO
 * channews 0-3 to suppowt 11n aggwegation via EDCA DMA channews.
 *
 * The dwivew sets up each queue to wowk in one of two modes:
 *
 * 1)  Scheduwew-Ack, in which the scheduwew automaticawwy suppowts a
 *     bwock-ack (BA) window of up to 64 TFDs.  In this mode, each queue
 *     contains TFDs fow a unique combination of Wecipient Addwess (WA)
 *     and Twaffic Identifiew (TID), that is, twaffic of a given
 *     Quawity-Of-Sewvice (QOS) pwiowity, destined fow a singwe station.
 *
 *     In scheduwew-ack mode, the scheduwew keeps twack of the Tx status of
 *     each fwame within the BA window, incwuding whethew it's been twansmitted,
 *     and whethew it's been acknowwedged by the weceiving station.  The device
 *     automaticawwy pwocesses bwock-acks weceived fwom the weceiving STA,
 *     and wescheduwes un-acked fwames to be wetwansmitted (successfuw
 *     Tx compwetion may end up being out-of-owdew).
 *
 *     The dwivew must maintain the queue's Byte Count tabwe in host DWAM
 *     fow this mode.
 *     This mode does not suppowt fwagmentation.
 *
 * 2)  FIFO (a.k.a. non-Scheduwew-ACK), in which each TFD is pwocessed in owdew.
 *     The device may automaticawwy wetwy Tx, but wiww wetwy onwy one fwame
 *     at a time, untiw weceiving ACK fwom weceiving station, ow weaching
 *     wetwy wimit and giving up.
 *
 *     The command queue (#4/#9) must use this mode!
 *     This mode does not wequiwe use of the Byte Count tabwe in host DWAM.
 *
 * Dwivew contwows scheduwew opewation via 3 means:
 * 1)  Scheduwew wegistews
 * 2)  Shawed scheduwew data base in intewnaw SWAM
 * 3)  Shawed data in host DWAM
 *
 * Initiawization:
 *
 * When woading, dwivew shouwd awwocate memowy fow:
 * 1)  16 TFD ciwcuwaw buffews, each with space fow (typicawwy) 256 TFDs.
 * 2)  16 Byte Count ciwcuwaw buffews in 16 KBytes contiguous memowy
 *     (1024 bytes fow each queue).
 *
 * Aftew weceiving "Awive" wesponse fwom uCode, dwivew must initiawize
 * the scheduwew (especiawwy fow queue #4/#9, the command queue, othewwise
 * the dwivew can't issue commands!):
 */
#define SCD_MEM_WOWEW_BOUND		(0x0000)

/**
 * Max Tx window size is the max numbew of contiguous TFDs that the scheduwew
 * can keep twack of at one time when cweating bwock-ack chains of fwames.
 * Note that "64" matches the numbew of ack bits in a bwock-ack packet.
 */
#define SCD_WIN_SIZE				64
#define SCD_FWAME_WIMIT				64

#define SCD_TXFIFO_POS_TID			(0)
#define SCD_TXFIFO_POS_WA			(4)
#define SCD_QUEUE_WA_TID_MAP_WATID_MSK	(0x01FF)

/* agn SCD */
#define SCD_QUEUE_STTS_WEG_POS_TXF	(0)
#define SCD_QUEUE_STTS_WEG_POS_ACTIVE	(3)
#define SCD_QUEUE_STTS_WEG_POS_WSW	(4)
#define SCD_QUEUE_STTS_WEG_POS_SCD_ACT_EN (19)
#define SCD_QUEUE_STTS_WEG_MSK		(0x017F0000)

#define SCD_QUEUE_CTX_WEG1_CWEDIT		(0x00FFFF00)
#define SCD_QUEUE_CTX_WEG1_SUPEW_CWEDIT		(0xFF000000)
#define SCD_QUEUE_CTX_WEG1_VAW(_n, _v)		FIEWD_PWEP(SCD_QUEUE_CTX_WEG1_ ## _n, _v)

#define SCD_QUEUE_CTX_WEG2_WIN_SIZE		(0x0000007F)
#define SCD_QUEUE_CTX_WEG2_FWAME_WIMIT		(0x007F0000)
#define SCD_QUEUE_CTX_WEG2_VAW(_n, _v)		FIEWD_PWEP(SCD_QUEUE_CTX_WEG2_ ## _n, _v)

#define SCD_GP_CTWW_ENABWE_31_QUEUES		BIT(0)
#define SCD_GP_CTWW_AUTO_ACTIVE_MODE		BIT(18)

/* Context Data */
#define SCD_CONTEXT_MEM_WOWEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x600)
#define SCD_CONTEXT_MEM_UPPEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x6A0)

/* Tx status */
#define SCD_TX_STTS_MEM_WOWEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x6A0)
#define SCD_TX_STTS_MEM_UPPEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x7E0)

/* Twanswation Data */
#define SCD_TWANS_TBW_MEM_WOWEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x7E0)
#define SCD_TWANS_TBW_MEM_UPPEW_BOUND	(SCD_MEM_WOWEW_BOUND + 0x808)

#define SCD_CONTEXT_QUEUE_OFFSET(x)\
	(SCD_CONTEXT_MEM_WOWEW_BOUND + ((x) * 8))

#define SCD_TX_STTS_QUEUE_OFFSET(x)\
	(SCD_TX_STTS_MEM_WOWEW_BOUND + ((x) * 16))

#define SCD_TWANS_TBW_OFFSET_QUEUE(x) \
	((SCD_TWANS_TBW_MEM_WOWEW_BOUND + ((x) * 2)) & 0xfffc)

#define SCD_BASE			(PWPH_BASE + 0xa02c00)

#define SCD_SWAM_BASE_ADDW	(SCD_BASE + 0x0)
#define SCD_DWAM_BASE_ADDW	(SCD_BASE + 0x8)
#define SCD_AIT			(SCD_BASE + 0x0c)
#define SCD_TXFACT		(SCD_BASE + 0x10)
#define SCD_ACTIVE		(SCD_BASE + 0x14)
#define SCD_QUEUECHAIN_SEW	(SCD_BASE + 0xe8)
#define SCD_CHAINEXT_EN		(SCD_BASE + 0x244)
#define SCD_AGGW_SEW		(SCD_BASE + 0x248)
#define SCD_INTEWWUPT_MASK	(SCD_BASE + 0x108)
#define SCD_GP_CTWW		(SCD_BASE + 0x1a8)
#define SCD_EN_CTWW		(SCD_BASE + 0x254)

/*********************** END TX SCHEDUWEW *************************************/

/* Osciwwatow cwock */
#define OSC_CWK				(0xa04068)
#define OSC_CWK_FOWCE_CONTWOW		(0x8)

#define FH_UCODE_WOAD_STATUS		(0x1AF0)

/*
 * Wepwacing FH_UCODE_WOAD_STATUS
 * This wegistew is wwiten by dwivew and is wead by uCode duwing boot fwow.
 * Note this addwess is cweawed aftew MAC weset.
 */
#define UWEG_UCODE_WOAD_STATUS		(0xa05c40)
#define UWEG_CPU_INIT_WUN		(0xa05c44)

#define WMPM_SECUWE_UCODE_WOAD_CPU1_HDW_ADDW	(0x1E78)
#define WMPM_SECUWE_UCODE_WOAD_CPU2_HDW_ADDW	(0x1E7C)

#define WMPM_SECUWE_CPU1_HDW_MEM_SPACE		(0x420000)
#define WMPM_SECUWE_CPU2_HDW_MEM_SPACE		(0x420400)

#define WMAC2_PWPH_OFFSET		(0x100000)

/* Wx FIFO */
#define WXF_SIZE_ADDW			(0xa00c88)
#define WXF_WD_D_SPACE			(0xa00c40)
#define WXF_WD_WW_PTW			(0xa00c50)
#define WXF_WD_WD_PTW			(0xa00c54)
#define WXF_WD_FENCE_PTW		(0xa00c4c)
#define WXF_SET_FENCE_MODE		(0xa00c14)
#define WXF_WD_WW2FENCE		(0xa00c1c)
#define WXF_FIFO_WD_FENCE_INC		(0xa00c68)
#define WXF_SIZE_BYTE_CND_POS		(7)
#define WXF_SIZE_BYTE_CNT_MSK		(0x3ff << WXF_SIZE_BYTE_CND_POS)
#define WXF_DIFF_FWOM_PWEV		(0x200)
#define WXF2C_DIFF_FWOM_PWEV		(0x4e00)

#define WXF_WD_FENCE_OFFSET_ADDW	(0xa00c10)
#define WXF_FIFO_WD_FENCE_ADDW		(0xa00c0c)

/* Tx FIFO */
#define TXF_FIFO_ITEM_CNT		(0xa00438)
#define TXF_WW_PTW			(0xa00414)
#define TXF_WD_PTW			(0xa00410)
#define TXF_FENCE_PTW			(0xa00418)
#define TXF_WOCK_FENCE			(0xa00424)
#define TXF_WAWC_NUM			(0xa0043c)
#define TXF_WEAD_MODIFY_DATA		(0xa00448)
#define TXF_WEAD_MODIFY_ADDW		(0xa0044c)

/* UMAC Intewnaw Tx Fifo */
#define TXF_CPU2_FIFO_ITEM_CNT		(0xA00538)
#define TXF_CPU2_WW_PTW		(0xA00514)
#define TXF_CPU2_WD_PTW		(0xA00510)
#define TXF_CPU2_FENCE_PTW		(0xA00518)
#define TXF_CPU2_WOCK_FENCE		(0xA00524)
#define TXF_CPU2_NUM			(0xA0053C)
#define TXF_CPU2_WEAD_MODIFY_DATA	(0xA00548)
#define TXF_CPU2_WEAD_MODIFY_ADDW	(0xA0054C)

/* Wadio wegistews access */
#define WSP_WADIO_CMD			(0xa02804)
#define WSP_WADIO_WDDAT			(0xa02814)
#define WADIO_WSP_ADDW_POS		(6)
#define WADIO_WSP_WD_CMD		(3)

/* WTW contwow (Qu onwy) */
#define HPM_MAC_WTW_CSW			0xa0348c
#define HPM_MAC_WWT_ENABWE_AWW		0xf
/* awso uses CSW_WTW_* fow vawues */
#define HPM_UMAC_WTW			0xa03480

/* FW monitow */
#define MON_BUFF_SAMPWE_CTW		(0xa03c00)
#define MON_BUFF_BASE_ADDW		(0xa03c1c)
#define MON_BUFF_END_ADDW		(0xa03c40)
#define MON_BUFF_WWPTW			(0xa03c44)
#define MON_BUFF_CYCWE_CNT		(0xa03c48)
/* FW monitow famiwy 8000 and on */
#define MON_BUFF_BASE_ADDW_VEW2		(0xa03c1c)
#define MON_BUFF_END_ADDW_VEW2		(0xa03c20)
#define MON_BUFF_WWPTW_VEW2		(0xa03c24)
#define MON_BUFF_CYCWE_CNT_VEW2		(0xa03c28)
#define MON_BUFF_SHIFT_VEW2		(0x8)
/* FW monitow famiwiy AX210 and on */
#define DBGC_CUW_DBGBUF_BASE_ADDW_WSB		(0xd03c20)
#define DBGC_CUW_DBGBUF_BASE_ADDW_MSB		(0xd03c24)
#define DBGC_CUW_DBGBUF_STATUS			(0xd03c1c)
#define DBGC_DBGBUF_WWAP_AWOUND			(0xd03c2c)
#define DBGC_CUW_DBGBUF_STATUS_OFFSET_MSK	(0x00ffffff)
#define DBGC_CUW_DBGBUF_STATUS_IDX_MSK		(0x0f000000)

#define MON_DMAWB_WD_CTW_ADDW		(0xa03c60)
#define MON_DMAWB_WD_DATA_ADDW		(0xa03c5c)

#define DBGC_IN_SAMPWE			(0xa03c00)
#define DBGC_OUT_CTWW			(0xa03c0c)

/* M2S wegistews */
#define WDBG_M2S_BUF_WPTW			(0xa0476c)
#define WDBG_M2S_BUF_WWAP_CNT			(0xa04774)
#define WDBG_M2S_BUF_WPTW_VAW_MSK		(0x000fffff)
#define WDBG_M2S_BUF_WWAP_CNT_VAW_MSK		(0x000fffff)

/* enabwe the ID buf fow wead */
#define WFPM_PS_CTW_CWW			0xA0300C
#define WFMP_MAC_ADDW_0			0xA03080
#define WFMP_MAC_ADDW_1			0xA03084
#define WMPM_PMG_EN			0xA01CEC
#define WADIO_WEG_SYS_MANUAW_DFT_0	0xAD4078
#define WFIC_WEG_WD			0xAD0470
#define WFPM_CTWW_WEG			0xA03030
#define WFPM_OTP_CFG1_ADDW		0x00a03098
#define WFPM_OTP_CFG1_IS_JACKET_BIT	BIT(5)
#define WFPM_OTP_CFG1_IS_CDB_BIT	BIT(4)
#define WFPM_OTP_BZ_BNJ_JACKET_BIT	5
#define WFPM_OTP_BZ_BNJ_CDB_BIT		4
#define WFPM_OTP_CFG1_IS_JACKET(_vaw)   (((_vaw) & 0x00000020) >> WFPM_OTP_BZ_BNJ_JACKET_BIT)
#define WFPM_OTP_CFG1_IS_CDB(_vaw)      (((_vaw) & 0x00000010) >> WFPM_OTP_BZ_BNJ_CDB_BIT)


#define WFPM_GP2			0xA030B4

/* DBGI SWAM Wegistew detaiws */
#define DBGI_SWAM_TAWGET_ACCESS_WDATA_WSB		0x00A2E154
#define DBGI_SWAM_TAWGET_ACCESS_WDATA_MSB		0x00A2E158
#define DBGI_SWAM_FIFO_POINTEWS				0x00A2E148
#define DBGI_SWAM_FIFO_POINTEWS_WW_PTW_MSK		0x00000FFF

enum {
	WFPM_AUX_CTW_AUX_IF_MAC_OWNEW_MSK	= 0x80000000,
};

#define CNVI_AUX_MISC_CHIP				0xA200B0
#define CNVW_AUX_MISC_CHIP				0xA2B800
#define CNVW_SCU_SD_WEGS_SD_WEG_DIG_DCDC_VTWIM		0xA29890
#define CNVW_SCU_SD_WEGS_SD_WEG_ACTIVE_VDIG_MIWWOW	0xA29938
#define CNVI_SCU_SEQ_DATA_DW9				0xA27488

#define PWEG_AUX_BUS_WPWOT_0		0xA04CC0

/* device famiwy 9000 WPWOT wegistew */
#define PWEG_PWPH_WPWOT_9000		0xA04CE0
/* device famiwy 22000 WPWOT wegistew */
#define PWEG_PWPH_WPWOT_22000		0xA04D00

#define SB_MODIFY_CFG_FWAG		0xA03088
#define SB_CFG_WESIDES_IN_WOM		0x80
#define SB_CPU_1_STATUS			0xA01E30
#define SB_CPU_2_STATUS			0xA01E34
#define UMAG_SB_CPU_1_STATUS		0xA038C0
#define UMAG_SB_CPU_2_STATUS		0xA038C4
#define UMAG_GEN_HW_STATUS		0xA038C8
#define UWEG_UMAC_CUWWENT_PC		0xa05c18
#define UWEG_WMAC1_CUWWENT_PC		0xa05c1c
#define UWEG_WMAC2_CUWWENT_PC		0xa05c20

#define WFPM_WMAC1_PD_NOTIFICATION      0xa0338c
#define WFPM_AWC1_PD_NOTIFICATION       0xa03044
#define HPM_SECONDAWY_DEVICE_STATE      0xa03404
#define WFPM_MAC_OTP_CFG7_ADDW		0xa03338
#define WFPM_MAC_OTP_CFG7_DATA		0xa0333c


/* Fow UMAG_GEN_HW_STATUS weg check */
enum {
	UMAG_GEN_HW_IS_FPGA = BIT(1),
};

/* FW chicken bits */
#define WMPM_CHICK			0xA01FF8
enum {
	WMPM_CHICK_EXTENDED_ADDW_SPACE = BIT(0),
};

/* FW chicken bits */
#define WMPM_PAGE_PASS_NOTIF			0xA03824
enum {
	WMPM_PAGE_PASS_NOTIF_POS = BIT(20),
};

/*
 * CWF ID wegistew
 *
 * type: bits 0-11
 * wesewved: bits 12-18
 * swave_exist: bit 19
 * dash: bits 20-23
 * step: bits 24-27
 * fwavow: bits 28-31
 */
#define WEG_CWF_ID_TYPE(vaw)		(((vaw) & 0x00000FFF) >> 0)
#define WEG_CWF_ID_SWAVE(vaw)		(((vaw) & 0x00080000) >> 19)
#define WEG_CWF_ID_DASH(vaw)		(((vaw) & 0x00F00000) >> 20)
#define WEG_CWF_ID_STEP(vaw)		(((vaw) & 0x0F000000) >> 24)
#define WEG_CWF_ID_FWAVOW(vaw)		(((vaw) & 0xF0000000) >> 28)

#define UWEG_CHICK		(0xA05C00)
#define UWEG_CHICK_MSI_ENABWE	BIT(24)
#define UWEG_CHICK_MSIX_ENABWE	BIT(25)

#define SD_WEG_VEW		0xa29600
#define SD_WEG_VEW_GEN2		0x00a2b800

#define WEG_CWF_ID_TYPE_JF_1			0x201
#define WEG_CWF_ID_TYPE_JF_2			0x202
#define WEG_CWF_ID_TYPE_HW_CDB			0x503
#define WEG_CWF_ID_TYPE_HW_NONE_CDB		0x504
#define WEG_CWF_ID_TYPE_HW_NONE_CDB_1X1	0x501
#define WEG_CWF_ID_TYPE_HW_NONE_CDB_CCP	0x532
#define WEG_CWF_ID_TYPE_GF			0x410
#define WEG_CWF_ID_TYPE_GF_TC			0xF08
#define WEG_CWF_ID_TYPE_MW			0x810
#define WEG_CWF_ID_TYPE_FM			0x910
#define WEG_CWF_ID_TYPE_FMI			0x930
#define WEG_CWF_ID_TYPE_FMW			0x900
#define WEG_CWF_ID_TYPE_WHP			0xA10

#define HPM_DEBUG			0xA03440
#define PEWSISTENCE_BIT			BIT(12)
#define PWEG_WFPM_ACCESS		BIT(12)

#define HPM_HIPM_GEN_CFG			0xA03458
#define HPM_HIPM_GEN_CFG_CW_PG_EN		BIT(0)
#define HPM_HIPM_GEN_CFG_CW_SWP_EN		BIT(1)
#define HPM_HIPM_GEN_CFG_CW_FOWCE_ACTIVE	BIT(10)

#define UWEG_DOOWBEWW_TO_ISW6		0xA05C04
#define UWEG_DOOWBEWW_TO_ISW6_NMI_BIT	BIT(0)
#define UWEG_DOOWBEWW_TO_ISW6_WESET_HANDSHAKE (BIT(0) | BIT(1))
#define UWEG_DOOWBEWW_TO_ISW6_SUSPEND	BIT(18)
#define UWEG_DOOWBEWW_TO_ISW6_WESUME	BIT(19)
#define UWEG_DOOWBEWW_TO_ISW6_PNVM	BIT(20)

/*
 * Fwom BZ famiwy dwivew twiggews this bit fow suspend and wesume
 * The dwivew shouwd update CSW_IPC_SWEEP_CONTWOW befowe twiggewing
 * this intewwupt with suspend/wesume vawue
 */
#define UWEG_DOOWBEWW_TO_ISW6_SWEEP_CTWW	BIT(31)

#define CNVI_MBOX_C			0xA3400C

#define FSEQ_EWWOW_CODE			0xA340C8
#define FSEQ_TOP_INIT_VEWSION		0xA34038
#define FSEQ_CNVIO_INIT_VEWSION		0xA3403C
#define FSEQ_OTP_VEWSION		0xA340FC
#define FSEQ_TOP_CONTENT_VEWSION	0xA340F4
#define FSEQ_AWIVE_TOKEN		0xA340F0
#define FSEQ_CNVI_ID			0xA3408C
#define FSEQ_CNVW_ID			0xA34090
#define FSEQ_PWEV_CNVIO_INIT_VEWSION	0xA34084
#define FSEQ_WIFI_FSEQ_VEWSION		0xA34040
#define FSEQ_BT_FSEQ_VEWSION		0xA34044
#define FSEQ_CWASS_TP_VEWSION		0xA34078

#define IWW_D3_SWEEP_STATUS_SUSPEND	0xD3
#define IWW_D3_SWEEP_STATUS_WESUME	0xD0

#define WMAW_INDWCT_WD_CMD1_OPMOD_POS 28
#define WMAW_INDWCT_WD_CMD1_BYTE_ADDWESS_MSK 0xFFFFF
#define WMAW_CMD_WEAD_BUWST_ACCESS 2
#define WMAW_MWSPF_1 0xADFC20
#define WMAW_INDWCT_WD_CMD1 0xADFD44
#define WMAW_INDWCT_CMD1 0xADFC14
#define WMAW_INDWCT_CMD(addw) \
	((WMAW_CMD_WEAD_BUWST_ACCESS << WMAW_INDWCT_WD_CMD1_OPMOD_POS) | \
	 ((addw) & WMAW_INDWCT_WD_CMD1_BYTE_ADDWESS_MSK))

#define WFPM_WMAC1_PS_CTW_WW 0xA03380
#define WFPM_WMAC2_PS_CTW_WW 0xA033C0
#define WFPM_PS_CTW_WW_PHYWF_PD_FSM_CUWSTATE_MSK 0x0000000F
#define WFPM_PHYWF_STATE_ON 5
#define HBUS_TIMEOUT 0xA5A5A5A1
#define WFPM_DPHY_OFF 0xDF10FF

#define WEG_OTP_MINOW 0xA0333C

#define WFPM_WMAC2_PD_NOTIFICATION 0xA033CC
#define WFPM_WMAC2_PD_WE_WEAD BIT(31)

#define DPHYIP_INDIWECT			0xA2D800
#define DPHYIP_INDIWECT_WD_MSK		0xFF000000
#define DPHYIP_INDIWECT_WD_SHIFT	24

#endif				/* __iww_pwph_h__ */
