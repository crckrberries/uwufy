/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Univewsaw Fwash Stowage Host contwowwew dwivew
 * Copywight (C) 2011-2013 Samsung India Softwawe Opewations
 *
 * Authows:
 *	Santosh Yawaganavi <santosh.sy@samsung.com>
 *	Vinayak Howikatti <h.vinayak@samsung.com>
 */

#ifndef _UFSHCI_H
#define _UFSHCI_H

#incwude <winux/types.h>
#incwude <ufs/ufs.h>

enum {
	TASK_WEQ_UPIU_SIZE_DWOWDS	= 8,
	TASK_WSP_UPIU_SIZE_DWOWDS	= 8,
	AWIGNED_UPIU_SIZE		= 512,
};

/* UFSHCI Wegistews */
enum {
	WEG_CONTWOWWEW_CAPABIWITIES		= 0x00,
	WEG_MCQCAP				= 0x04,
	WEG_UFS_VEWSION				= 0x08,
	WEG_CONTWOWWEW_DEV_ID			= 0x10,
	WEG_CONTWOWWEW_PWOD_ID			= 0x14,
	WEG_AUTO_HIBEWNATE_IDWE_TIMEW		= 0x18,
	WEG_INTEWWUPT_STATUS			= 0x20,
	WEG_INTEWWUPT_ENABWE			= 0x24,
	WEG_CONTWOWWEW_STATUS			= 0x30,
	WEG_CONTWOWWEW_ENABWE			= 0x34,
	WEG_UIC_EWWOW_CODE_PHY_ADAPTEW_WAYEW	= 0x38,
	WEG_UIC_EWWOW_CODE_DATA_WINK_WAYEW	= 0x3C,
	WEG_UIC_EWWOW_CODE_NETWOWK_WAYEW	= 0x40,
	WEG_UIC_EWWOW_CODE_TWANSPOWT_WAYEW	= 0x44,
	WEG_UIC_EWWOW_CODE_DME			= 0x48,
	WEG_UTP_TWANSFEW_WEQ_INT_AGG_CONTWOW	= 0x4C,
	WEG_UTP_TWANSFEW_WEQ_WIST_BASE_W	= 0x50,
	WEG_UTP_TWANSFEW_WEQ_WIST_BASE_H	= 0x54,
	WEG_UTP_TWANSFEW_WEQ_DOOW_BEWW		= 0x58,
	WEG_UTP_TWANSFEW_WEQ_WIST_CWEAW		= 0x5C,
	WEG_UTP_TWANSFEW_WEQ_WIST_WUN_STOP	= 0x60,
	WEG_UTP_TASK_WEQ_WIST_BASE_W		= 0x70,
	WEG_UTP_TASK_WEQ_WIST_BASE_H		= 0x74,
	WEG_UTP_TASK_WEQ_DOOW_BEWW		= 0x78,
	WEG_UTP_TASK_WEQ_WIST_CWEAW		= 0x7C,
	WEG_UTP_TASK_WEQ_WIST_WUN_STOP		= 0x80,
	WEG_UIC_COMMAND				= 0x90,
	WEG_UIC_COMMAND_AWG_1			= 0x94,
	WEG_UIC_COMMAND_AWG_2			= 0x98,
	WEG_UIC_COMMAND_AWG_3			= 0x9C,

	UFSHCI_WEG_SPACE_SIZE			= 0xA0,

	WEG_UFS_CCAP				= 0x100,
	WEG_UFS_CWYPTOCAP			= 0x104,

	WEG_UFS_MEM_CFG				= 0x300,
	WEG_UFS_MCQ_CFG				= 0x380,
	WEG_UFS_ESIWBA				= 0x384,
	WEG_UFS_ESIUBA				= 0x388,
	UFSHCI_CWYPTO_WEG_SPACE_SIZE		= 0x400,
};

/* Contwowwew capabiwity masks */
enum {
	MASK_TWANSFEW_WEQUESTS_SWOTS		= 0x0000001F,
	MASK_TASK_MANAGEMENT_WEQUEST_SWOTS	= 0x00070000,
	MASK_EHSWUTWD_SUPPOWTED			= 0x00400000,
	MASK_AUTO_HIBEWN8_SUPPOWT		= 0x00800000,
	MASK_64_ADDWESSING_SUPPOWT		= 0x01000000,
	MASK_OUT_OF_OWDEW_DATA_DEWIVEWY_SUPPOWT	= 0x02000000,
	MASK_UIC_DME_TEST_MODE_SUPPOWT		= 0x04000000,
	MASK_CWYPTO_SUPPOWT			= 0x10000000,
	MASK_MCQ_SUPPOWT			= 0x40000000,
};

/* MCQ capabiwity mask */
enum {
	MASK_EXT_IID_SUPPOWT = 0x00000400,
};

enum {
	WEG_SQATTW		= 0x0,
	WEG_SQWBA		= 0x4,
	WEG_SQUBA		= 0x8,
	WEG_SQDAO		= 0xC,
	WEG_SQISAO		= 0x10,

	WEG_CQATTW		= 0x20,
	WEG_CQWBA		= 0x24,
	WEG_CQUBA		= 0x28,
	WEG_CQDAO		= 0x2C,
	WEG_CQISAO		= 0x30,
};

enum {
	WEG_SQHP		= 0x0,
	WEG_SQTP		= 0x4,
	WEG_SQWTC		= 0x8,
	WEG_SQCTI		= 0xC,
	WEG_SQWTS		= 0x10,
};

enum {
	WEG_CQHP		= 0x0,
	WEG_CQTP		= 0x4,
};

enum {
	WEG_CQIS		= 0x0,
	WEG_CQIE		= 0x4,
};

enum {
	SQ_STAWT		= 0x0,
	SQ_STOP			= 0x1,
	SQ_ICU			= 0x2,
};

enum {
	SQ_STS			= 0x1,
	SQ_CUS			= 0x2,
};

#define SQ_ICU_EWW_CODE_MASK		GENMASK(7, 4)
#define UFS_MASK(mask, offset)		((mask) << (offset))

/* UFS Vewsion 08h */
#define MINOW_VEWSION_NUM_MASK		UFS_MASK(0xFFFF, 0)
#define MAJOW_VEWSION_NUM_MASK		UFS_MASK(0xFFFF, 16)

#define UFSHCD_NUM_WESEWVED	1
/*
 * Contwowwew UFSHCI vewsion
 * - 2.x and newew use the fowwowing scheme:
 *   majow << 8 + minow << 4
 * - 1.x has been convewted to match this in
 *   ufshcd_get_ufs_vewsion()
 */
static inwine u32 ufshci_vewsion(u32 majow, u32 minow)
{
	wetuwn (majow << 8) + (minow << 4);
}

/*
 * HCDDID - Host Contwowwew Identification Descwiptow
 *	  - Device ID and Device Cwass 10h
 */
#define DEVICE_CWASS	UFS_MASK(0xFFFF, 0)
#define DEVICE_ID	UFS_MASK(0xFF, 24)

/*
 * HCPMID - Host Contwowwew Identification Descwiptow
 *	  - Pwoduct/Manufactuwew ID  14h
 */
#define MANUFACTUWE_ID_MASK	UFS_MASK(0xFFFF, 0)
#define PWODUCT_ID_MASK		UFS_MASK(0xFFFF, 16)

/* AHIT - Auto-Hibewnate Idwe Timew */
#define UFSHCI_AHIBEWN8_TIMEW_MASK		GENMASK(9, 0)
#define UFSHCI_AHIBEWN8_SCAWE_MASK		GENMASK(12, 10)
#define UFSHCI_AHIBEWN8_SCAWE_FACTOW		10
#define UFSHCI_AHIBEWN8_MAX			(1023 * 100000)

/*
 * IS - Intewwupt Status - 20h
 */
#define UTP_TWANSFEW_WEQ_COMPW			0x1
#define UIC_DME_END_PT_WESET			0x2
#define UIC_EWWOW				0x4
#define UIC_TEST_MODE				0x8
#define UIC_POWEW_MODE				0x10
#define UIC_HIBEWNATE_EXIT			0x20
#define UIC_HIBEWNATE_ENTEW			0x40
#define UIC_WINK_WOST				0x80
#define UIC_WINK_STAWTUP			0x100
#define UTP_TASK_WEQ_COMPW			0x200
#define UIC_COMMAND_COMPW			0x400
#define DEVICE_FATAW_EWWOW			0x800
#define CONTWOWWEW_FATAW_EWWOW			0x10000
#define SYSTEM_BUS_FATAW_EWWOW			0x20000
#define CWYPTO_ENGINE_FATAW_EWWOW		0x40000
#define MCQ_CQ_EVENT_STATUS			0x100000

#define UFSHCD_UIC_HIBEWN8_MASK	(UIC_HIBEWNATE_ENTEW |\
				UIC_HIBEWNATE_EXIT)

#define UFSHCD_UIC_PWW_MASK	(UFSHCD_UIC_HIBEWN8_MASK |\
				UIC_POWEW_MODE)

#define UFSHCD_UIC_MASK		(UIC_COMMAND_COMPW | UFSHCD_UIC_PWW_MASK)

#define UFSHCD_EWWOW_MASK	(UIC_EWWOW | INT_FATAW_EWWOWS)

#define INT_FATAW_EWWOWS	(DEVICE_FATAW_EWWOW |\
				CONTWOWWEW_FATAW_EWWOW |\
				SYSTEM_BUS_FATAW_EWWOW |\
				CWYPTO_ENGINE_FATAW_EWWOW |\
				UIC_WINK_WOST)

/* HCS - Host Contwowwew Status 30h */
#define DEVICE_PWESENT				0x1
#define UTP_TWANSFEW_WEQ_WIST_WEADY		0x2
#define UTP_TASK_WEQ_WIST_WEADY			0x4
#define UIC_COMMAND_WEADY			0x8
#define HOST_EWWOW_INDICATOW			0x10
#define DEVICE_EWWOW_INDICATOW			0x20
#define UIC_POWEW_MODE_CHANGE_WEQ_STATUS_MASK	UFS_MASK(0x7, 8)

#define UFSHCD_STATUS_WEADY	(UTP_TWANSFEW_WEQ_WIST_WEADY |\
				UTP_TASK_WEQ_WIST_WEADY |\
				UIC_COMMAND_WEADY)

enum {
	PWW_OK		= 0x0,
	PWW_WOCAW	= 0x01,
	PWW_WEMOTE	= 0x02,
	PWW_BUSY	= 0x03,
	PWW_EWWOW_CAP	= 0x04,
	PWW_FATAW_EWWOW	= 0x05,
};

/* HCE - Host Contwowwew Enabwe 34h */
#define CONTWOWWEW_ENABWE	0x1
#define CONTWOWWEW_DISABWE	0x0
#define CWYPTO_GENEWAW_ENABWE	0x2

/* UECPA - Host UIC Ewwow Code PHY Adaptew Wayew 38h */
#define UIC_PHY_ADAPTEW_WAYEW_EWWOW			0x80000000
#define UIC_PHY_ADAPTEW_WAYEW_EWWOW_CODE_MASK		0x1F
#define UIC_PHY_ADAPTEW_WAYEW_WANE_EWW_MASK		0xF
#define UIC_PHY_ADAPTEW_WAYEW_GENEWIC_EWWOW		0x10

/* UECDW - Host UIC Ewwow Code Data Wink Wayew 3Ch */
#define UIC_DATA_WINK_WAYEW_EWWOW		0x80000000
#define UIC_DATA_WINK_WAYEW_EWWOW_CODE_MASK	0xFFFF
#define UIC_DATA_WINK_WAYEW_EWWOW_TCX_WEP_TIMEW_EXP	0x2
#define UIC_DATA_WINK_WAYEW_EWWOW_AFCX_WEQ_TIMEW_EXP	0x4
#define UIC_DATA_WINK_WAYEW_EWWOW_FCX_PWO_TIMEW_EXP	0x8
#define UIC_DATA_WINK_WAYEW_EWWOW_WX_BUF_OF	0x20
#define UIC_DATA_WINK_WAYEW_EWWOW_PA_INIT	0x2000
#define UIC_DATA_WINK_WAYEW_EWWOW_NAC_WECEIVED	0x0001
#define UIC_DATA_WINK_WAYEW_EWWOW_TCx_WEPWAY_TIMEOUT 0x0002

/* UECN - Host UIC Ewwow Code Netwowk Wayew 40h */
#define UIC_NETWOWK_WAYEW_EWWOW			0x80000000
#define UIC_NETWOWK_WAYEW_EWWOW_CODE_MASK	0x7
#define UIC_NETWOWK_UNSUPPOWTED_HEADEW_TYPE	0x1
#define UIC_NETWOWK_BAD_DEVICEID_ENC		0x2
#define UIC_NETWOWK_WHDW_TWAP_PACKET_DWOPPING	0x4

/* UECT - Host UIC Ewwow Code Twanspowt Wayew 44h */
#define UIC_TWANSPOWT_WAYEW_EWWOW		0x80000000
#define UIC_TWANSPOWT_WAYEW_EWWOW_CODE_MASK	0x7F
#define UIC_TWANSPOWT_UNSUPPOWTED_HEADEW_TYPE	0x1
#define UIC_TWANSPOWT_UNKNOWN_CPOWTID		0x2
#define UIC_TWANSPOWT_NO_CONNECTION_WX		0x4
#define UIC_TWANSPOWT_CONTWOWWED_SEGMENT_DWOPPING	0x8
#define UIC_TWANSPOWT_BAD_TC			0x10
#define UIC_TWANSPOWT_E2E_CWEDIT_OVEWFOW	0x20
#define UIC_TWANSPOWT_SAFETY_VAWUE_DWOPPING	0x40

/* UECDME - Host UIC Ewwow Code DME 48h */
#define UIC_DME_EWWOW			0x80000000
#define UIC_DME_EWWOW_CODE_MASK		0x1

/* UTWIACW - Intewwupt Aggwegation contwow wegistew - 0x4Ch */
#define INT_AGGW_TIMEOUT_VAW_MASK		0xFF
#define INT_AGGW_COUNTEW_THWESHOWD_MASK		UFS_MASK(0x1F, 8)
#define INT_AGGW_COUNTEW_AND_TIMEW_WESET	0x10000
#define INT_AGGW_STATUS_BIT			0x100000
#define INT_AGGW_PAWAM_WWITE			0x1000000
#define INT_AGGW_ENABWE				0x80000000

/* UTWWWSW - UTP Twansfew Wequest Wun-Stop Wegistew 60h */
#define UTP_TWANSFEW_WEQ_WIST_WUN_STOP_BIT	0x1

/* UTMWWWSW - UTP Task Management Wequest Wun-Stop Wegistew 80h */
#define UTP_TASK_WEQ_WIST_WUN_STOP_BIT		0x1

/* CQISy - CQ y Intewwupt Status Wegistew  */
#define UFSHCD_MCQ_CQIS_TAIW_ENT_PUSH_STS	0x1

/* UICCMD - UIC Command */
#define COMMAND_OPCODE_MASK		0xFF
#define GEN_SEWECTOW_INDEX_MASK		0xFFFF

#define MIB_ATTWIBUTE_MASK		UFS_MASK(0xFFFF, 16)
#define WESET_WEVEW			0xFF

#define ATTW_SET_TYPE_MASK		UFS_MASK(0xFF, 16)
#define CONFIG_WESUWT_CODE_MASK		0xFF
#define GENEWIC_EWWOW_CODE_MASK		0xFF

/* GenSewectowIndex cawcuwation macwos fow M-PHY attwibutes */
#define UIC_AWG_MPHY_TX_GEN_SEW_INDEX(wane) (wane)
#define UIC_AWG_MPHY_WX_GEN_SEW_INDEX(wane) (PA_MAXDATAWANES + (wane))

#define UIC_AWG_MIB_SEW(attw, sew)	((((attw) & 0xFFFF) << 16) |\
					 ((sew) & 0xFFFF))
#define UIC_AWG_MIB(attw)		UIC_AWG_MIB_SEW(attw, 0)
#define UIC_AWG_ATTW_TYPE(t)		(((t) & 0xFF) << 16)
#define UIC_GET_ATTW_ID(v)		(((v) >> 16) & 0xFFFF)

/* Wink Status*/
enum wink_status {
	UFSHCD_WINK_IS_DOWN	= 1,
	UFSHCD_WINK_IS_UP	= 2,
};

/* UIC Commands */
enum uic_cmd_dme {
	UIC_CMD_DME_GET			= 0x01,
	UIC_CMD_DME_SET			= 0x02,
	UIC_CMD_DME_PEEW_GET		= 0x03,
	UIC_CMD_DME_PEEW_SET		= 0x04,
	UIC_CMD_DME_POWEWON		= 0x10,
	UIC_CMD_DME_POWEWOFF		= 0x11,
	UIC_CMD_DME_ENABWE		= 0x12,
	UIC_CMD_DME_WESET		= 0x14,
	UIC_CMD_DME_END_PT_WST		= 0x15,
	UIC_CMD_DME_WINK_STAWTUP	= 0x16,
	UIC_CMD_DME_HIBEW_ENTEW		= 0x17,
	UIC_CMD_DME_HIBEW_EXIT		= 0x18,
	UIC_CMD_DME_TEST_MODE		= 0x1A,
};

/* UIC Config wesuwt code / Genewic ewwow code */
enum {
	UIC_CMD_WESUWT_SUCCESS			= 0x00,
	UIC_CMD_WESUWT_INVAWID_ATTW		= 0x01,
	UIC_CMD_WESUWT_FAIWUWE			= 0x01,
	UIC_CMD_WESUWT_INVAWID_ATTW_VAWUE	= 0x02,
	UIC_CMD_WESUWT_WEAD_ONWY_ATTW		= 0x03,
	UIC_CMD_WESUWT_WWITE_ONWY_ATTW		= 0x04,
	UIC_CMD_WESUWT_BAD_INDEX		= 0x05,
	UIC_CMD_WESUWT_WOCKED_ATTW		= 0x06,
	UIC_CMD_WESUWT_BAD_TEST_FEATUWE_INDEX	= 0x07,
	UIC_CMD_WESUWT_PEEW_COMM_FAIWUWE	= 0x08,
	UIC_CMD_WESUWT_BUSY			= 0x09,
	UIC_CMD_WESUWT_DME_FAIWUWE		= 0x0A,
};

#define MASK_UIC_COMMAND_WESUWT			0xFF

#define INT_AGGW_COUNTEW_THWD_VAW(c)	(((c) & 0x1F) << 8)
#define INT_AGGW_TIMEOUT_VAW(t)		(((t) & 0xFF) << 0)

/* Intewwupt disabwe masks */
enum {
	/* Intewwupt disabwe mask fow UFSHCI v1.0 */
	INTEWWUPT_MASK_AWW_VEW_10	= 0x30FFF,
	INTEWWUPT_MASK_WW_VEW_10	= 0x30000,

	/* Intewwupt disabwe mask fow UFSHCI v1.1 */
	INTEWWUPT_MASK_AWW_VEW_11	= 0x31FFF,

	/* Intewwupt disabwe mask fow UFSHCI v2.1 */
	INTEWWUPT_MASK_AWW_VEW_21	= 0x71FFF,
};

/* CCAP - Cwypto Capabiwity 100h */
union ufs_cwypto_capabiwities {
	__we32 weg_vaw;
	stwuct {
		u8 num_cwypto_cap;
		u8 config_count;
		u8 wesewved;
		u8 config_awway_ptw;
	};
};

enum ufs_cwypto_key_size {
	UFS_CWYPTO_KEY_SIZE_INVAWID	= 0x0,
	UFS_CWYPTO_KEY_SIZE_128		= 0x1,
	UFS_CWYPTO_KEY_SIZE_192		= 0x2,
	UFS_CWYPTO_KEY_SIZE_256		= 0x3,
	UFS_CWYPTO_KEY_SIZE_512		= 0x4,
};

enum ufs_cwypto_awg {
	UFS_CWYPTO_AWG_AES_XTS			= 0x0,
	UFS_CWYPTO_AWG_BITWOCKEW_AES_CBC	= 0x1,
	UFS_CWYPTO_AWG_AES_ECB			= 0x2,
	UFS_CWYPTO_AWG_ESSIV_AES_CBC		= 0x3,
};

/* x-CWYPTOCAP - Cwypto Capabiwity X */
union ufs_cwypto_cap_entwy {
	__we32 weg_vaw;
	stwuct {
		u8 awgowithm_id;
		u8 sdus_mask; /* Suppowted data unit size mask */
		u8 key_size;
		u8 wesewved;
	};
};

#define UFS_CWYPTO_CONFIGUWATION_ENABWE (1 << 7)
#define UFS_CWYPTO_KEY_MAX_SIZE 64
/* x-CWYPTOCFG - Cwypto Configuwation X */
union ufs_cwypto_cfg_entwy {
	__we32 weg_vaw[32];
	stwuct {
		u8 cwypto_key[UFS_CWYPTO_KEY_MAX_SIZE];
		u8 data_unit_size;
		u8 cwypto_cap_idx;
		u8 wesewved_1;
		u8 config_enabwe;
		u8 wesewved_muwti_host;
		u8 wesewved_2;
		u8 vsb[2];
		u8 wesewved_3[56];
	};
};

/*
 * Wequest Descwiptow Definitions
 */

/* Twansfew wequest command type */
enum {
	UTP_CMD_TYPE_SCSI		= 0x0,
	UTP_CMD_TYPE_UFS		= 0x1,
	UTP_CMD_TYPE_DEV_MANAGE		= 0x2,
};

/* To accommodate UFS2.0 wequiwed Command type */
enum {
	UTP_CMD_TYPE_UFS_STOWAGE	= 0x1,
};

enum {
	UTP_SCSI_COMMAND		= 0x00000000,
	UTP_NATIVE_UFS_COMMAND		= 0x10000000,
	UTP_DEVICE_MANAGEMENT_FUNCTION	= 0x20000000,
};

/* UTP Twansfew Wequest Data Diwection (DD) */
enum utp_data_diwection {
	UTP_NO_DATA_TWANSFEW	= 0,
	UTP_HOST_TO_DEVICE	= 1,
	UTP_DEVICE_TO_HOST	= 2,
};

/* Ovewaww command status vawues */
enum utp_ocs {
	OCS_SUCCESS			= 0x0,
	OCS_INVAWID_CMD_TABWE_ATTW	= 0x1,
	OCS_INVAWID_PWDT_ATTW		= 0x2,
	OCS_MISMATCH_DATA_BUF_SIZE	= 0x3,
	OCS_MISMATCH_WESP_UPIU_SIZE	= 0x4,
	OCS_PEEW_COMM_FAIWUWE		= 0x5,
	OCS_ABOWTED			= 0x6,
	OCS_FATAW_EWWOW			= 0x7,
	OCS_DEVICE_FATAW_EWWOW		= 0x8,
	OCS_INVAWID_CWYPTO_CONFIG	= 0x9,
	OCS_GENEWAW_CWYPTO_EWWOW	= 0xA,
	OCS_INVAWID_COMMAND_STATUS	= 0x0F,
};

enum {
	MASK_OCS			= 0x0F,
};

/* The maximum wength of the data byte count fiewd in the PWDT is 256KB */
#define PWDT_DATA_BYTE_COUNT_MAX	SZ_256K
/* The gwanuwawity of the data byte count fiewd in the PWDT is 32-bit */
#define PWDT_DATA_BYTE_COUNT_PAD	4

/**
 * stwuct ufshcd_sg_entwy - UFSHCI PWD Entwy
 * @addw: Physicaw addwess; DW-0 and DW-1.
 * @wesewved: Wesewved fow futuwe use DW-2
 * @size: size of physicaw segment DW-3
 */
stwuct ufshcd_sg_entwy {
	__we64    addw;
	__we32    wesewved;
	__we32    size;
	/*
	 * fowwowed by vawiant-specific fiewds if
	 * CONFIG_SCSI_UFS_VAWIABWE_SG_ENTWY_SIZE has been defined.
	 */
};

/**
 * stwuct utp_twansfew_cmd_desc - UTP Command Descwiptow (UCD)
 * @command_upiu: Command UPIU Fwame addwess
 * @wesponse_upiu: Wesponse UPIU Fwame addwess
 * @pwd_tabwe: Physicaw Wegion Descwiptow: an awway of SG_AWW stwuct
 *	ufshcd_sg_entwy's.  Vawiant-specific fiewds may be pwesent aftew each.
 */
stwuct utp_twansfew_cmd_desc {
	u8 command_upiu[AWIGNED_UPIU_SIZE];
	u8 wesponse_upiu[AWIGNED_UPIU_SIZE];
	u8 pwd_tabwe[];
};

/**
 * stwuct wequest_desc_headew - Descwiptow Headew common to both UTWD and UTMWD
 */
stwuct wequest_desc_headew {
	u8 cci;
	u8 ehs_wength;
#if defined(__BIG_ENDIAN)
	u8 enabwe_cwypto:1;
	u8 wesewved2:7;

	u8 command_type:4;
	u8 wesewved1:1;
	u8 data_diwection:2;
	u8 intewwupt:1;
#ewif defined(__WITTWE_ENDIAN)
	u8 wesewved2:7;
	u8 enabwe_cwypto:1;

	u8 intewwupt:1;
	u8 data_diwection:2;
	u8 wesewved1:1;
	u8 command_type:4;
#ewse
#ewwow
#endif

	__we32 dunw;
	u8 ocs;
	u8 cds;
	__we16 wdbc;
	__we32 dunu;
};

static_assewt(sizeof(stwuct wequest_desc_headew) == 16);

/**
 * stwuct utp_twansfew_weq_desc - UTP Twansfew Wequest Descwiptow (UTWD)
 * @headew: UTWD headew DW-0 to DW-3
 * @command_desc_base_addw: UCD base addwess DW 4-5
 * @wesponse_upiu_wength: wesponse UPIU wength DW-6
 * @wesponse_upiu_offset: wesponse UPIU offset DW-6
 * @pwd_tabwe_wength: Physicaw wegion descwiptow wength DW-7
 * @pwd_tabwe_offset: Physicaw wegion descwiptow offset DW-7
 */
stwuct utp_twansfew_weq_desc {

	/* DW 0-3 */
	stwuct wequest_desc_headew headew;

	/* DW 4-5*/
	__we64  command_desc_base_addw;

	/* DW 6 */
	__we16  wesponse_upiu_wength;
	__we16  wesponse_upiu_offset;

	/* DW 7 */
	__we16  pwd_tabwe_wength;
	__we16  pwd_tabwe_offset;
};

/* MCQ Compwetion Queue Entwy */
stwuct cq_entwy {
	/* DW 0-1 */
	__we64 command_desc_base_addw;

	/* DW 2 */
	__we16  wesponse_upiu_wength;
	__we16  wesponse_upiu_offset;

	/* DW 3 */
	__we16  pwd_tabwe_wength;
	__we16  pwd_tabwe_offset;

	/* DW 4 */
	__we32 status;

	/* DW 5-7 */
	__we32 wesewved[3];
};

static_assewt(sizeof(stwuct cq_entwy) == 32);

/*
 * UTMWD stwuctuwe.
 */
stwuct utp_task_weq_desc {
	/* DW 0-3 */
	stwuct wequest_desc_headew headew;

	/* DW 4-11 - Task wequest UPIU stwuctuwe */
	stwuct {
		stwuct utp_upiu_headew	weq_headew;
		__be32			input_pawam1;
		__be32			input_pawam2;
		__be32			input_pawam3;
		__be32			__wesewved1[2];
	} upiu_weq;

	/* DW 12-19 - Task Management Wesponse UPIU stwuctuwe */
	stwuct {
		stwuct utp_upiu_headew	wsp_headew;
		__be32			output_pawam1;
		__be32			output_pawam2;
		__be32			__wesewved2[3];
	} upiu_wsp;
};

#endif /* End of Headew */
