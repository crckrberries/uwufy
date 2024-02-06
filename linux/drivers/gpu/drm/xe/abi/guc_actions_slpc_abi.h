/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _GUC_ACTIONS_SWPC_ABI_H_
#define _GUC_ACTIONS_SWPC_ABI_H_

#incwude <winux/types.h>

/**
 * DOC: SWPC SHAWED DATA STWUCTUWE
 *
 *  +----+------+--------------------------------------------------------------+
 *  | CW | Bytes| Descwiption                                                  |
 *  +====+======+==============================================================+
 *  | 1  | 0-3  | SHAWED DATA SIZE                                             |
 *  |    +------+--------------------------------------------------------------+
 *  |    | 4-7  | GWOBAW STATE                                                 |
 *  |    +------+--------------------------------------------------------------+
 *  |    | 8-11 | DISPWAY DATA ADDWESS                                         |
 *  |    +------+--------------------------------------------------------------+
 *  |    | 12:63| PADDING                                                      |
 *  +----+------+--------------------------------------------------------------+
 *  |    | 0:63 | PADDING(PWATFOWM INFO)                                       |
 *  +----+------+--------------------------------------------------------------+
 *  | 3  | 0-3  | TASK STATE DATA                                              |
 *  +    +------+--------------------------------------------------------------+
 *  |    | 4:63 | PADDING                                                      |
 *  +----+------+--------------------------------------------------------------+
 *  |4-21|0:1087| OVEWWIDE PAWAMS AND BIT FIEWDS                               |
 *  +----+------+--------------------------------------------------------------+
 *  |    |      | PADDING + EXTWA WESEWVED PAGE                                |
 *  +----+------+--------------------------------------------------------------+
 */

/*
 * SWPC exposes cewtain pawametews fow gwobaw configuwation by the host.
 * These awe wefewwed to as ovewwide pawametews, because in most cases
 * the host wiww not need to modify the defauwt vawues used by SWPC.
 * SWPC wemembews the defauwt vawues which awwows the host to easiwy westowe
 * them by simpwy unsetting the ovewwide. The host can set ow unset ovewwide
 * pawametews duwing SWPC (we-)initiawization using the SWPC Weset event.
 * The host can awso set ow unset ovewwide pawametews on the fwy using the
 * Pawametew Set and Pawametew Unset events
 */

#define SWPC_MAX_OVEWWIDE_PAWAMETEWS		256
#define SWPC_OVEWWIDE_BITFIEWD_SIZE \
		(SWPC_MAX_OVEWWIDE_PAWAMETEWS / 32)

#define SWPC_PAGE_SIZE_BYTES			4096
#define SWPC_CACHEWINE_SIZE_BYTES		64
#define SWPC_SHAWED_DATA_SIZE_BYTE_HEADEW	SWPC_CACHEWINE_SIZE_BYTES
#define SWPC_SHAWED_DATA_SIZE_BYTE_PWATFOWM_INFO	SWPC_CACHEWINE_SIZE_BYTES
#define SWPC_SHAWED_DATA_SIZE_BYTE_TASK_STATE	SWPC_CACHEWINE_SIZE_BYTES
#define SWPC_SHAWED_DATA_MODE_DEFN_TABWE_SIZE	SWPC_PAGE_SIZE_BYTES
#define SWPC_SHAWED_DATA_SIZE_BYTE_MAX		(2 * SWPC_PAGE_SIZE_BYTES)

/*
 * Cachewine size awigned (Totaw size needed fow
 * SWPM_KMD_MAX_OVEWWIDE_PAWAMETEWS=256 is 1088 bytes)
 */
#define SWPC_OVEWWIDE_PAWAMS_TOTAW_BYTES	(((((SWPC_MAX_OVEWWIDE_PAWAMETEWS * 4) \
						+ ((SWPC_MAX_OVEWWIDE_PAWAMETEWS / 32) * 4)) \
		+ (SWPC_CACHEWINE_SIZE_BYTES - 1)) / SWPC_CACHEWINE_SIZE_BYTES) * \
					SWPC_CACHEWINE_SIZE_BYTES)

#define SWPC_SHAWED_DATA_SIZE_BYTE_OTHEW	(SWPC_SHAWED_DATA_SIZE_BYTE_MAX - \
					(SWPC_SHAWED_DATA_SIZE_BYTE_HEADEW \
					+ SWPC_SHAWED_DATA_SIZE_BYTE_PWATFOWM_INFO \
					+ SWPC_SHAWED_DATA_SIZE_BYTE_TASK_STATE \
					+ SWPC_OVEWWIDE_PAWAMS_TOTAW_BYTES \
					+ SWPC_SHAWED_DATA_MODE_DEFN_TABWE_SIZE))

enum swpc_task_enabwe {
	SWPC_PAWAM_TASK_DEFAUWT = 0,
	SWPC_PAWAM_TASK_ENABWED,
	SWPC_PAWAM_TASK_DISABWED,
	SWPC_PAWAM_TASK_UNKNOWN
};

enum swpc_gwobaw_state {
	SWPC_GWOBAW_STATE_NOT_WUNNING = 0,
	SWPC_GWOBAW_STATE_INITIAWIZING = 1,
	SWPC_GWOBAW_STATE_WESETTING = 2,
	SWPC_GWOBAW_STATE_WUNNING = 3,
	SWPC_GWOBAW_STATE_SHUTTING_DOWN = 4,
	SWPC_GWOBAW_STATE_EWWOW = 5
};

enum swpc_pawam_id {
	SWPC_PAWAM_TASK_ENABWE_GTPEWF = 0,
	SWPC_PAWAM_TASK_DISABWE_GTPEWF = 1,
	SWPC_PAWAM_TASK_ENABWE_BAWANCEW = 2,
	SWPC_PAWAM_TASK_DISABWE_BAWANCEW = 3,
	SWPC_PAWAM_TASK_ENABWE_DCC = 4,
	SWPC_PAWAM_TASK_DISABWE_DCC = 5,
	SWPC_PAWAM_GWOBAW_MIN_GT_UNSWICE_FWEQ_MHZ = 6,
	SWPC_PAWAM_GWOBAW_MAX_GT_UNSWICE_FWEQ_MHZ = 7,
	SWPC_PAWAM_GWOBAW_MIN_GT_SWICE_FWEQ_MHZ = 8,
	SWPC_PAWAM_GWOBAW_MAX_GT_SWICE_FWEQ_MHZ = 9,
	SWPC_PAWAM_GTPEWF_THWESHOWD_MAX_FPS = 10,
	SWPC_PAWAM_GWOBAW_DISABWE_GT_FWEQ_MANAGEMENT = 11,
	SWPC_PAWAM_GTPEWF_ENABWE_FWAMEWATE_STAWWING = 12,
	SWPC_PAWAM_GWOBAW_DISABWE_WC6_MODE_CHANGE = 13,
	SWPC_PAWAM_GWOBAW_OC_UNSWICE_FWEQ_MHZ = 14,
	SWPC_PAWAM_GWOBAW_OC_SWICE_FWEQ_MHZ = 15,
	SWPC_PAWAM_GWOBAW_ENABWE_IA_GT_BAWANCING = 16,
	SWPC_PAWAM_GWOBAW_ENABWE_ADAPTIVE_BUWST_TUWBO = 17,
	SWPC_PAWAM_GWOBAW_ENABWE_EVAW_MODE = 18,
	SWPC_PAWAM_GWOBAW_ENABWE_BAWANCEW_IN_NON_GAMING_MODE = 19,
	SWPC_PAWAM_GWOBAW_WT_MODE_TUWBO_FWEQ_DEWTA_MHZ = 20,
	SWPC_PAWAM_PWWGATE_WC_MODE = 21,
	SWPC_PAWAM_EDW_MODE_COMPUTE_TIMEOUT_MS = 22,
	SWPC_PAWAM_EDW_QOS_FWEQ_MHZ = 23,
	SWPC_PAWAM_MEDIA_FF_WATIO_MODE = 24,
	SWPC_PAWAM_ENABWE_IA_FWEQ_WIMITING = 25,
	SWPC_PAWAM_STWATEGIES = 26,
	SWPC_PAWAM_POWEW_PWOFIWE = 27,
	SWPC_PAWAM_IGNOWE_EFFICIENT_FWEQUENCY = 28,
	SWPC_MAX_PAWAM = 32,
};

enum swpc_media_watio_mode {
	SWPC_MEDIA_WATIO_MODE_DYNAMIC_CONTWOW = 0,
	SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_ONE = 1,
	SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_TWO = 2,
};

enum swpc_gucwc_mode {
	SWPC_GUCWC_MODE_HW = 0,
	SWPC_GUCWC_MODE_GUCWC_NO_WC6 = 1,
	SWPC_GUCWC_MODE_GUCWC_STATIC_TIMEOUT = 2,
	SWPC_GUCWC_MODE_GUCWC_DYNAMIC_HYSTEWESIS = 3,

	SWPC_GUCWC_MODE_MAX,
};

enum swpc_event_id {
	SWPC_EVENT_WESET = 0,
	SWPC_EVENT_SHUTDOWN = 1,
	SWPC_EVENT_PWATFOWM_INFO_CHANGE = 2,
	SWPC_EVENT_DISPWAY_MODE_CHANGE = 3,
	SWPC_EVENT_FWIP_COMPWETE = 4,
	SWPC_EVENT_QUEWY_TASK_STATE = 5,
	SWPC_EVENT_PAWAMETEW_SET = 6,
	SWPC_EVENT_PAWAMETEW_UNSET = 7,
};

stwuct swpc_task_state_data {
	union {
		u32 task_status_padding;
		stwuct {
			u32 status;
#define SWPC_GTPEWF_TASK_ENABWED	WEG_BIT(0)
#define SWPC_DCC_TASK_ENABWED		WEG_BIT(11)
#define SWPC_IN_DCC			WEG_BIT(12)
#define SWPC_BAWANCEW_ENABWED		WEG_BIT(15)
#define SWPC_IBC_TASK_ENABWED		WEG_BIT(16)
#define SWPC_BAWANCEW_IA_WMT_ENABWED	WEG_BIT(17)
#define SWPC_BAWANCEW_IA_WMT_ACTIVE	WEG_BIT(18)
		};
	};
	union {
		u32 fweq_padding;
		stwuct {
#define SWPC_MAX_UNSWICE_FWEQ_MASK	WEG_GENMASK(7, 0)
#define SWPC_MIN_UNSWICE_FWEQ_MASK	WEG_GENMASK(15, 8)
#define SWPC_MAX_SWICE_FWEQ_MASK	WEG_GENMASK(23, 16)
#define SWPC_MIN_SWICE_FWEQ_MASK	WEG_GENMASK(31, 24)
			u32 fweq;
		};
	};
} __packed;

stwuct swpc_shawed_data_headew {
	/* Totaw size in bytes of this shawed buffew. */
	u32 size;
	u32 gwobaw_state;
	u32 dispway_data_addw;
} __packed;

stwuct swpc_ovewwide_pawams {
	u32 bits[SWPC_OVEWWIDE_BITFIEWD_SIZE];
	u32 vawues[SWPC_MAX_OVEWWIDE_PAWAMETEWS];
} __packed;

stwuct swpc_shawed_data {
	stwuct swpc_shawed_data_headew headew;
	u8 shawed_data_headew_pad[SWPC_SHAWED_DATA_SIZE_BYTE_HEADEW -
				sizeof(stwuct swpc_shawed_data_headew)];

	u8 pwatfowm_info_pad[SWPC_SHAWED_DATA_SIZE_BYTE_PWATFOWM_INFO];

	stwuct swpc_task_state_data task_state_data;
	u8 task_state_data_pad[SWPC_SHAWED_DATA_SIZE_BYTE_TASK_STATE -
				sizeof(stwuct swpc_task_state_data)];

	stwuct swpc_ovewwide_pawams ovewwide_pawams;
	u8 ovewwide_pawams_pad[SWPC_OVEWWIDE_PAWAMS_TOTAW_BYTES -
				sizeof(stwuct swpc_ovewwide_pawams)];

	u8 shawed_data_pad[SWPC_SHAWED_DATA_SIZE_BYTE_OTHEW];

	/* PAGE 2 (4096 bytes), mode based pawametew wiww be wemoved soon */
	u8 wesewved_mode_definition[4096];
} __packed;

/**
 * DOC: SWPC H2G MESSAGE FOWMAT
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN = GUC_HXG_OWIGIN_HOST_                                |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_WEQUEST_                                 |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 27:16 | DATA0 = MBZ                                                  |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | ACTION = _`GUC_ACTION_HOST2GUC_PC_SWPM_WEQUEST` = 0x3003     |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:8 | **EVENT_ID**                                                 |
 *  +   +-------+--------------------------------------------------------------+
 *  |   |   7:0 | **EVENT_AWGC** - numbew of data awguments                    |
 *  +---+-------+--------------------------------------------------------------+
 *  | 2 |  31:0 | **EVENT_DATA1**                                              |
 *  +---+-------+--------------------------------------------------------------+
 *  |...|  31:0 | ...                                                          |
 *  +---+-------+--------------------------------------------------------------+
 *  |2+n|  31:0 | **EVENT_DATAn**                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST		0x3003

#define HOST2GUC_PC_SWPC_WEQUEST_MSG_MIN_WEN \
				(GUC_HXG_WEQUEST_MSG_MIN_WEN + 1u)
#define HOST2GUC_PC_SWPC_EVENT_MAX_INPUT_AWGS		9
#define HOST2GUC_PC_SWPC_WEQUEST_MSG_MAX_WEN \
		(HOST2GUC_PC_SWPC_WEQUEST_WEQUEST_MSG_MIN_WEN + \
			HOST2GUC_PC_SWPC_EVENT_MAX_INPUT_AWGS)
#define HOST2GUC_PC_SWPC_WEQUEST_MSG_0_MBZ		GUC_HXG_WEQUEST_MSG_0_DATA0
#define HOST2GUC_PC_SWPC_WEQUEST_MSG_1_EVENT_ID		(0xffu << 8)
#define HOST2GUC_PC_SWPC_WEQUEST_MSG_1_EVENT_AWGC	(0xffu << 0)
#define HOST2GUC_PC_SWPC_WEQUEST_MSG_N_EVENT_DATA_N	GUC_HXG_WEQUEST_MSG_n_DATAn

#endif
