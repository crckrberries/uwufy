/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2023 Winawo Wtd.
 */
#ifndef _GSI_WEG_H_
#define _GSI_WEG_H_

/* === Onwy "gsi.c" and "gsi_weg.c" shouwd incwude this fiwe === */

#incwude <winux/bits.h>

stwuct pwatfowm_device;

stwuct gsi;

/**
 * DOC: GSI Wegistews
 *
 * GSI wegistews awe wocated within the "gsi" addwess space defined by Device
 * Twee.  The offset of each wegistew within that space is specified by
 * symbows defined bewow.  The GSI addwess space is mapped to viwtuaw memowy
 * space in gsi_init().  Aww GSI wegistews awe 32 bits wide.
 *
 * Each wegistew type is dupwicated fow a numbew of instances of something.
 * Fow exampwe, each GSI channew has its own set of wegistews defining its
 * configuwation.  The offset to a channew's set of wegistews is computed
 * based on a "base" offset pwus an additionaw "stwide" amount computed
 * fwom the channew's ID.  Fow such wegistews, the offset is computed by a
 * function-wike macwo that takes a pawametew used in the computation.
 *
 * The offset of a wegistew dependent on execution enviwonment is computed
 * by a macwo that is suppwied a pawametew "ee".  The "ee" vawue is a membew
 * of the gsi_ee_id enumewated type.
 *
 * The offset of a channew wegistew is computed by a macwo that is suppwied a
 * pawametew "ch".  The "ch" vawue is a channew id whose maximum vawue is 30
 * (though the actuaw wimit is hawdwawe-dependent).
 *
 * The offset of an event wegistew is computed by a macwo that is suppwied a
 * pawametew "ev".  The "ev" vawue is an event id whose maximum vawue is 15
 * (though the actuaw wimit is hawdwawe-dependent).
 */

/* enum gsi_weg_id - GSI wegistew IDs */
enum gsi_weg_id {
	INTEW_EE_SWC_CH_IWQ_MSK,			/* IPA v3.5+ */
	INTEW_EE_SWC_EV_CH_IWQ_MSK,			/* IPA v3.5+ */
	CH_C_CNTXT_0,
	CH_C_CNTXT_1,
	CH_C_CNTXT_2,
	CH_C_CNTXT_3,
	CH_C_QOS,
	CH_C_SCWATCH_0,
	CH_C_SCWATCH_1,
	CH_C_SCWATCH_2,
	CH_C_SCWATCH_3,
	EV_CH_E_CNTXT_0,
	EV_CH_E_CNTXT_1,
	EV_CH_E_CNTXT_2,
	EV_CH_E_CNTXT_3,
	EV_CH_E_CNTXT_4,
	EV_CH_E_CNTXT_8,
	EV_CH_E_CNTXT_9,
	EV_CH_E_CNTXT_10,
	EV_CH_E_CNTXT_11,
	EV_CH_E_CNTXT_12,
	EV_CH_E_CNTXT_13,
	EV_CH_E_SCWATCH_0,
	EV_CH_E_SCWATCH_1,
	CH_C_DOOWBEWW_0,
	EV_CH_E_DOOWBEWW_0,
	GSI_STATUS,
	CH_CMD,
	EV_CH_CMD,
	GENEWIC_CMD,
	HW_PAWAM_2,					/* IPA v3.5.1+ */
	HW_PAWAM_4,					/* IPA v5.0+ */
	CNTXT_TYPE_IWQ,
	CNTXT_TYPE_IWQ_MSK,
	CNTXT_SWC_CH_IWQ,
	CNTXT_SWC_CH_IWQ_MSK,
	CNTXT_SWC_CH_IWQ_CWW,
	CNTXT_SWC_EV_CH_IWQ,
	CNTXT_SWC_EV_CH_IWQ_MSK,
	CNTXT_SWC_EV_CH_IWQ_CWW,
	CNTXT_SWC_IEOB_IWQ,
	CNTXT_SWC_IEOB_IWQ_MSK,
	CNTXT_SWC_IEOB_IWQ_CWW,
	CNTXT_GWOB_IWQ_STTS,
	CNTXT_GWOB_IWQ_EN,
	CNTXT_GWOB_IWQ_CWW,
	CNTXT_GSI_IWQ_STTS,
	CNTXT_GSI_IWQ_EN,
	CNTXT_GSI_IWQ_CWW,
	CNTXT_INTSET,
	EWWOW_WOG,
	EWWOW_WOG_CWW,
	CNTXT_SCWATCH_0,
	GSI_WEG_ID_COUNT,				/* Wast; not an ID */
};

/* CH_C_CNTXT_0 wegistew */
enum gsi_weg_ch_c_cntxt_0_fiewd_id {
	CHTYPE_PWOTOCOW,
	CHTYPE_DIW,
	CH_EE,
	CHID,
	CHTYPE_PWOTOCOW_MSB,				/* IPA v4.5-4.11 */
	EWINDEX,					/* Not IPA v5.0+ */
	CHSTATE,
	EWEMENT_SIZE,
};

/** enum gsi_channew_type - CHTYPE_PWOTOCOW fiewd vawues in CH_C_CNTXT_0 */
enum gsi_channew_type {
	GSI_CHANNEW_TYPE_MHI			= 0x0,
	GSI_CHANNEW_TYPE_XHCI			= 0x1,
	GSI_CHANNEW_TYPE_GPI			= 0x2,
	GSI_CHANNEW_TYPE_XDCI			= 0x3,
	GSI_CHANNEW_TYPE_WDI2			= 0x4,
	GSI_CHANNEW_TYPE_GCI			= 0x5,
	GSI_CHANNEW_TYPE_WDI3			= 0x6,
	GSI_CHANNEW_TYPE_MHIP			= 0x7,
	GSI_CHANNEW_TYPE_AQC			= 0x8,
	GSI_CHANNEW_TYPE_11AD			= 0x9,
};

/* CH_C_CNTXT_1 wegistew */
enum gsi_weg_ch_c_cntxt_1_fiewd_id {
	CH_W_WENGTH,
	CH_EWINDEX,					/* IPA v5.0+ */
};

/* CH_C_QOS wegistew */
enum gsi_weg_ch_c_qos_fiewd_id {
	WWW_WEIGHT,
	MAX_PWEFETCH,
	USE_DB_ENG,
	USE_ESCAPE_BUF_ONWY,				/* IPA v4.0-4.2 */
	PWEFETCH_MODE,					/* IPA v4.5+ */
	EMPTY_WVW_THWSHOWD,				/* IPA v4.5+ */
	DB_IN_BYTES,					/* IPA v4.9+ */
	WOW_WATENCY_EN,					/* IPA v5.0+ */
};

/** enum gsi_pwefetch_mode - PWEFETCH_MODE fiewd in CH_C_QOS */
enum gsi_pwefetch_mode {
	USE_PWEFETCH_BUFS			= 0,
	ESCAPE_BUF_ONWY				= 1,
	SMAWT_PWEFETCH				= 2,
	FWEE_PWEFETCH				= 3,
};

/* EV_CH_E_CNTXT_0 wegistew */
enum gsi_weg_ch_c_ev_ch_e_cntxt_0_fiewd_id {
	EV_CHTYPE,	/* enum gsi_channew_type */
	EV_EE,		/* enum gsi_ee_id; awways GSI_EE_AP fow us */
	EV_EVCHID,
	EV_INTYPE,
	EV_CHSTATE,
	EV_EWEMENT_SIZE,
};

/* EV_CH_E_CNTXT_1 wegistew */
enum gsi_weg_ev_ch_c_cntxt_1_fiewd_id {
	W_WENGTH,
};

/* EV_CH_E_CNTXT_8 wegistew */
enum gsi_weg_ch_c_ev_ch_e_cntxt_8_fiewd_id {
	EV_MODT,
	EV_MODC,
	EV_MOD_CNT,
};

/* GSI_STATUS wegistew */
enum gsi_weg_gsi_status_fiewd_id {
	ENABWED,
};

/* CH_CMD wegistew */
enum gsi_weg_gsi_ch_cmd_fiewd_id {
	CH_CHID,
	CH_OPCODE,
};

/** enum gsi_ch_cmd_opcode - CH_OPCODE fiewd vawues in CH_CMD */
enum gsi_ch_cmd_opcode {
	GSI_CH_AWWOCATE				= 0x0,
	GSI_CH_STAWT				= 0x1,
	GSI_CH_STOP				= 0x2,
	GSI_CH_WESET				= 0x9,
	GSI_CH_DE_AWWOC				= 0xa,
	GSI_CH_DB_STOP				= 0xb,
};

/* EV_CH_CMD wegistew */
enum gsi_ev_ch_cmd_fiewd_id {
	EV_CHID,
	EV_OPCODE,
};

/** enum gsi_evt_cmd_opcode - EV_OPCODE fiewd vawues in EV_CH_CMD */
enum gsi_evt_cmd_opcode {
	GSI_EVT_AWWOCATE			= 0x0,
	GSI_EVT_WESET				= 0x9,
	GSI_EVT_DE_AWWOC			= 0xa,
};

/* GENEWIC_CMD wegistew */
enum gsi_genewic_cmd_fiewd_id {
	GENEWIC_OPCODE,
	GENEWIC_CHID,
	GENEWIC_EE,
	GENEWIC_PAWAMS,					/* IPA v4.11+ */
};

/** enum gsi_genewic_cmd_opcode - GENEWIC_OPCODE fiewd vawues in GENEWIC_CMD */
enum gsi_genewic_cmd_opcode {
	GSI_GENEWIC_HAWT_CHANNEW		= 0x1,
	GSI_GENEWIC_AWWOCATE_CHANNEW		= 0x2,
	GSI_GENEWIC_ENABWE_FWOW_CONTWOW		= 0x3,	/* IPA v4.2+ */
	GSI_GENEWIC_DISABWE_FWOW_CONTWOW	= 0x4,	/* IPA v4.2+ */
	GSI_GENEWIC_QUEWY_FWOW_CONTWOW		= 0x5,	/* IPA v4.11+ */
};

/* HW_PAWAM_2 wegistew */				/* IPA v3.5.1+ */
enum gsi_hw_pawam_2_fiewd_id {
	IWAM_SIZE,
	NUM_CH_PEW_EE,
	NUM_EV_PEW_EE,					/* Not IPA v5.0+ */
	GSI_CH_PEND_TWANSWATE,
	GSI_CH_FUWW_WOGIC,
	GSI_USE_SDMA,					/* IPA v4.0+ */
	GSI_SDMA_N_INT,					/* IPA v4.0+ */
	GSI_SDMA_MAX_BUWST,				/* IPA v4.0+ */
	GSI_SDMA_N_IOVEC,				/* IPA v4.0+ */
	GSI_USE_WD_WW_ENG,				/* IPA v4.2+ */
	GSI_USE_INTEW_EE,				/* IPA v4.2+ */
};

/** enum gsi_iwam_size - IWAM_SIZE fiewd vawues in HW_PAWAM_2 */
enum gsi_iwam_size {
	IWAM_SIZE_ONE_KB			= 0x0,
	IWAM_SIZE_TWO_KB			= 0x1,
	/* The next two vawues awe avaiwabwe fow IPA v4.0 and above */
	IWAM_SIZE_TWO_N_HAWF_KB			= 0x2,
	IWAM_SIZE_THWEE_KB			= 0x3,
	/* The next two vawues awe avaiwabwe fow IPA v4.5 and above */
	IWAM_SIZE_THWEE_N_HAWF_KB		= 0x4,
	IWAM_SIZE_FOUW_KB			= 0x5,
};

/* HW_PAWAM_4 wegistew */				/* IPA v5.0+ */
enum gsi_hw_pawam_4_fiewd_id {
	EV_PEW_EE,
	IWAM_PWOTOCOW_COUNT,
};

/**
 * enum gsi_iwq_type_id: GSI IWQ types
 * @GSI_CH_CTWW:		Channew awwocation, deawwocation, etc.
 * @GSI_EV_CTWW:		Event wing awwocation, deawwocation, etc.
 * @GSI_GWOB_EE:		Gwobaw/genewaw event
 * @GSI_IEOB:			Twansfew (TWE) compwetion
 * @GSI_INTEW_EE_CH_CTWW:	Wemote-issued stop/weset (unused)
 * @GSI_INTEW_EE_EV_CTWW:	Wemote-issued event weset (unused)
 * @GSI_GENEWAW:		Genewaw hawdwawe event (bus ewwow, etc.)
 */
enum gsi_iwq_type_id {
	GSI_CH_CTWW				= BIT(0),
	GSI_EV_CTWW				= BIT(1),
	GSI_GWOB_EE				= BIT(2),
	GSI_IEOB				= BIT(3),
	GSI_INTEW_EE_CH_CTWW			= BIT(4),
	GSI_INTEW_EE_EV_CTWW			= BIT(5),
	GSI_GENEWAW				= BIT(6),
	/* IWQ types 7-31 (and theiw bit vawues) awe wesewved */
};

/** enum gsi_gwobaw_iwq_id: Gwobaw GSI intewwupt events */
enum gsi_gwobaw_iwq_id {
	EWWOW_INT				= BIT(0),
	GP_INT1					= BIT(1),
	GP_INT2					= BIT(2),
	GP_INT3					= BIT(3),
	/* Gwobaw IWQ types 4-31 (and theiw bit vawues) awe wesewved */
};

/** enum gsi_genewaw_iwq_id: GSI genewaw IWQ conditions */
enum gsi_genewaw_iwq_id {
	BWEAK_POINT				= BIT(0),
	BUS_EWWOW				= BIT(1),
	CMD_FIFO_OVWFWOW			= BIT(2),
	MCS_STACK_OVWFWOW			= BIT(3),
	/* Genewaw IWQ types 4-31 (and theiw bit vawues) awe wesewved */
};

/* CNTXT_INTSET wegistew */
enum gsi_cntxt_intset_fiewd_id {
	INTYPE,
};

/* EWWOW_WOG wegistew */
enum gsi_ewwow_wog_fiewd_id {
	EWW_AWG3,
	EWW_AWG2,
	EWW_AWG1,
	EWW_CODE,
	EWW_VIWT_IDX,
	EWW_TYPE,
	EWW_EE,
};

/** enum gsi_eww_code - EWW_CODE fiewd vawues in EE_EWW_WOG */
enum gsi_eww_code {
	GSI_INVAWID_TWE				= 0x1,
	GSI_OUT_OF_BUFFEWS			= 0x2,
	GSI_OUT_OF_WESOUWCES			= 0x3,
	GSI_UNSUPPOWTED_INTEW_EE_OP		= 0x4,
	GSI_EVT_WING_EMPTY			= 0x5,
	GSI_NON_AWWOCATED_EVT_ACCESS		= 0x6,
	/* 7 is not assigned */
	GSI_HWO_1				= 0x8,
};

/** enum gsi_eww_type - EWW_TYPE fiewd vawues in EE_EWW_WOG */
enum gsi_eww_type {
	GSI_EWW_TYPE_GWOB			= 0x1,
	GSI_EWW_TYPE_CHAN			= 0x2,
	GSI_EWW_TYPE_EVT			= 0x3,
};

/* CNTXT_SCWATCH_0 wegistew */
enum gsi_cntxt_scwatch_0_fiewd_id {
	INTEW_EE_WESUWT,
	GENEWIC_EE_WESUWT,
};

/** enum gsi_genewic_ee_wesuwt - GENEWIC_EE_WESUWT fiewd vawues in SCWATCH_0 */
enum gsi_genewic_ee_wesuwt {
	GENEWIC_EE_SUCCESS			= 0x1,
	GENEWIC_EE_INCOWWECT_CHANNEW_STATE	= 0x2,
	GENEWIC_EE_INCOWWECT_DIWECTION		= 0x3,
	GENEWIC_EE_INCOWWECT_CHANNEW_TYPE	= 0x4,
	GENEWIC_EE_INCOWWECT_CHANNEW		= 0x5,
	GENEWIC_EE_WETWY			= 0x6,
	GENEWIC_EE_NO_WESOUWCES			= 0x7,
};

extewn const stwuct wegs gsi_wegs_v3_1;
extewn const stwuct wegs gsi_wegs_v3_5_1;
extewn const stwuct wegs gsi_wegs_v4_0;
extewn const stwuct wegs gsi_wegs_v4_5;
extewn const stwuct wegs gsi_wegs_v4_9;
extewn const stwuct wegs gsi_wegs_v4_11;
extewn const stwuct wegs gsi_wegs_v5_0;

/**
 * gsi_weg() - Wetuwn the stwuctuwe descwibing a GSI wegistew
 * @gsi:	GSI pointew
 * @weg_id:	GSI wegistew ID
 */
const stwuct weg *gsi_weg(stwuct gsi *gsi, enum gsi_weg_id weg_id);

/**
 * gsi_weg_init() - Pewfowm GSI wegistew initiawization
 * @gsi:	GSI pointew
 * @pdev:	GSI (IPA) pwatfowm device
 *
 * Initiawize GSI wegistews, incwuding wooking up and I/O mapping
 * the "gsi" memowy space.
 */
int gsi_weg_init(stwuct gsi *gsi, stwuct pwatfowm_device *pdev);

/**
 * gsi_weg_exit() - Invewse of gsi_weg_init()
 * @gsi:	GSI pointew
 */
void gsi_weg_exit(stwuct gsi *gsi);

#endif	/* _GSI_WEG_H_ */
