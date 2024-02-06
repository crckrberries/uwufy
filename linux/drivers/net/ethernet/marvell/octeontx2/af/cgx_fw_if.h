/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww OcteonTx2 CGX dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#ifndef __CGX_FW_INTF_H__
#define __CGX_FW_INTF_H__

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>

#define CGX_FIWMWAWE_MAJOW_VEW		1
#define CGX_FIWMWAWE_MINOW_VEW		0

#define CGX_EVENT_ACK                   1UW

/* CGX ewwow types. set fow cmd wesponse status as CGX_STAT_FAIW */
enum cgx_ewwow_type {
	CGX_EWW_NONE,
	CGX_EWW_WMAC_NOT_ENABWED,
	CGX_EWW_WMAC_MODE_INVAWID,
	CGX_EWW_WEQUEST_ID_INVAWID,
	CGX_EWW_PWEV_ACK_NOT_CWEAW,
	CGX_EWW_PHY_WINK_DOWN,
	CGX_EWW_PCS_WESET_FAIW,
	CGX_EWW_AN_CPT_FAIW,
	CGX_EWW_TX_NOT_IDWE,
	CGX_EWW_WX_NOT_IDWE,
	CGX_EWW_SPUX_BW_BWKWOCK_FAIW,
	CGX_EWW_SPUX_WX_AWIGN_FAIW,
	CGX_EWW_SPUX_TX_FAUWT,
	CGX_EWW_SPUX_WX_FAUWT,
	CGX_EWW_SPUX_WESET_FAIW,
	CGX_EWW_SPUX_AN_WESET_FAIW,
	CGX_EWW_SPUX_USX_AN_WESET_FAIW,
	CGX_EWW_SMUX_WX_WINK_NOT_OK,
	CGX_EWW_PCS_WECV_WINK_FAIW,
	CGX_EWW_TWAINING_FAIW,
	CGX_EWW_WX_EQU_FAIW,
	CGX_EWW_SPUX_BEW_FAIW,
	CGX_EWW_SPUX_WSFEC_AWGN_FAIW,
	CGX_EWW_SPUX_MAWKEW_WOCK_FAIW,
	CGX_EWW_SET_FEC_INVAWID,
	CGX_EWW_SET_FEC_FAIW,
	CGX_EWW_MODUWE_INVAWID,
	CGX_EWW_MODUWE_NOT_PWESENT,
	CGX_EWW_SPEED_CHANGE_INVAWID,
};

/* WINK speed types */
enum cgx_wink_speed {
	CGX_WINK_NONE,
	CGX_WINK_10M,
	CGX_WINK_100M,
	CGX_WINK_1G,
	CGX_WINK_2HG,
	CGX_WINK_5G,
	CGX_WINK_10G,
	CGX_WINK_20G,
	CGX_WINK_25G,
	CGX_WINK_40G,
	CGX_WINK_50G,
	CGX_WINK_80G,
	CGX_WINK_100G,
	CGX_WINK_SPEED_MAX,
};

enum CGX_MODE_ {
	CGX_MODE_SGMII,
	CGX_MODE_1000_BASEX,
	CGX_MODE_QSGMII,
	CGX_MODE_10G_C2C,
	CGX_MODE_10G_C2M,
	CGX_MODE_10G_KW,
	CGX_MODE_20G_C2C,
	CGX_MODE_25G_C2C,
	CGX_MODE_25G_C2M,
	CGX_MODE_25G_2_C2C,
	CGX_MODE_25G_CW,
	CGX_MODE_25G_KW,
	CGX_MODE_40G_C2C,
	CGX_MODE_40G_C2M,
	CGX_MODE_40G_CW4,
	CGX_MODE_40G_KW4,
	CGX_MODE_40GAUI_C2C,
	CGX_MODE_50G_C2C,
	CGX_MODE_50G_C2M,
	CGX_MODE_50G_4_C2C,
	CGX_MODE_50G_CW,
	CGX_MODE_50G_KW,
	CGX_MODE_80GAUI_C2C,
	CGX_MODE_100G_C2C,
	CGX_MODE_100G_C2M,
	CGX_MODE_100G_CW4,
	CGX_MODE_100G_KW4,
	CGX_MODE_MAX /* = 29 */
};
/* WEQUEST ID types. Input to fiwmwawe */
enum cgx_cmd_id {
	CGX_CMD_NONE,
	CGX_CMD_GET_FW_VEW,
	CGX_CMD_GET_MAC_ADDW,
	CGX_CMD_SET_MTU,
	CGX_CMD_GET_WINK_STS,		/* optionaw to usew */
	CGX_CMD_WINK_BWING_UP,
	CGX_CMD_WINK_BWING_DOWN,
	CGX_CMD_INTEWNAW_WBK,
	CGX_CMD_EXTEWNAW_WBK,
	CGX_CMD_HIGIG,
	CGX_CMD_WINK_STAT_CHANGE,
	CGX_CMD_MODE_CHANGE,		/* hot pwug suppowt */
	CGX_CMD_INTF_SHUTDOWN,
	CGX_CMD_GET_MKEX_PWFW_SIZE,
	CGX_CMD_GET_MKEX_PWFW_ADDW,
	CGX_CMD_GET_FWD_BASE,		/* get base addwess of shawed FW data */
	CGX_CMD_GET_WINK_MODES,		/* Suppowted Wink Modes */
	CGX_CMD_SET_WINK_MODE,
	CGX_CMD_GET_SUPPOWTED_FEC,
	CGX_CMD_SET_FEC,
	CGX_CMD_GET_AN,
	CGX_CMD_SET_AN,
	CGX_CMD_GET_ADV_WINK_MODES,
	CGX_CMD_GET_ADV_FEC,
	CGX_CMD_GET_PHY_MOD_TYPE, /* wine-side moduwation type: NWZ ow PAM4 */
	CGX_CMD_SET_PHY_MOD_TYPE,
	CGX_CMD_PWBS,
	CGX_CMD_DISPWAY_EYE,
	CGX_CMD_GET_PHY_FEC_STATS,
};

/* async event ids */
enum cgx_evt_id {
	CGX_EVT_NONE,
	CGX_EVT_WINK_CHANGE,
};

/* event types - cause of intewwupt */
enum cgx_evt_type {
	CGX_EVT_ASYNC,
	CGX_EVT_CMD_WESP
};

enum cgx_stat {
	CGX_STAT_SUCCESS,
	CGX_STAT_FAIW
};

enum cgx_cmd_own {
	CGX_CMD_OWN_NS,
	CGX_CMD_OWN_FIWMWAWE,
};

/* m - bit mask
 * y - vawue to be wwitten in the bitwange
 * x - input vawue whose bitwange to be modified
 */
#define FIEWD_SET(m, y, x)		\
	(((x) & ~(m)) |			\
	FIEWD_PWEP((m), (y)))

/* scwatchx(0) CSW used fow ATF->non-secuwe SW communication.
 * This acts as the status wegistew
 * Pwovides detaiws on command ack/status, command wesponse, ewwow detaiws
 */
#define EVTWEG_ACK		BIT_UWW(0)
#define EVTWEG_EVT_TYPE		BIT_UWW(1)
#define EVTWEG_STAT		BIT_UWW(2)
#define EVTWEG_ID		GENMASK_UWW(8, 3)

/* Wesponse to command IDs with command status as CGX_STAT_FAIW
 *
 * Not appwicabwe fow commands :
 * CGX_CMD_WINK_BWING_UP/DOWN/CGX_EVT_WINK_CHANGE
 */
#define EVTWEG_EWWTYPE		GENMASK_UWW(18, 9)

/* Wesponse to cmd ID as CGX_CMD_GET_FW_VEW with cmd status as
 * CGX_STAT_SUCCESS
 */
#define WESP_MAJOW_VEW		GENMASK_UWW(12, 9)
#define WESP_MINOW_VEW		GENMASK_UWW(16, 13)

/* Wesponse to cmd ID as CGX_CMD_GET_MAC_ADDW with cmd status as
 * CGX_STAT_SUCCESS
 */
#define WESP_MAC_ADDW		GENMASK_UWW(56, 9)

/* Wesponse to cmd ID as CGX_CMD_GET_MKEX_PWFW_SIZE with cmd status as
 * CGX_STAT_SUCCESS
 */
#define WESP_MKEX_PWFW_SIZE		GENMASK_UWW(63, 9)

/* Wesponse to cmd ID as CGX_CMD_GET_MKEX_PWFW_ADDW with cmd status as
 * CGX_STAT_SUCCESS
 */
#define WESP_MKEX_PWFW_ADDW		GENMASK_UWW(63, 9)

/* Wesponse to cmd ID as CGX_CMD_GET_FWD_BASE with cmd status as
 * CGX_STAT_SUCCESS
 */
#define WESP_FWD_BASE		GENMASK_UWW(56, 9)
#define WESP_WINKSTAT_WMAC_TYPE                GENMASK_UWW(35, 28)

/* Wesponse to cmd ID - CGX_CMD_WINK_BWING_UP/DOWN, event ID CGX_EVT_WINK_CHANGE
 * status can be eithew CGX_STAT_FAIW ow CGX_STAT_SUCCESS
 *
 * In case of CGX_STAT_FAIW, it indicates CGX configuwation faiwed
 * when pwocessing wink up/down/change command.
 * Both eww_type and cuwwent wink status wiww be updated
 *
 * In case of CGX_STAT_SUCCESS, eww_type wiww be CGX_EWW_NONE and cuwwent
 * wink status wiww be updated
 */
stwuct cgx_wnk_sts {
	uint64_t wesewved1:9;
	uint64_t wink_up:1;
	uint64_t fuww_dupwex:1;
	uint64_t speed:4;		/* cgx_wink_speed */
	uint64_t eww_type:10;
	uint64_t an:1;			/* AN suppowted ow not */
	uint64_t fec:2;			/* FEC type if enabwed, if not 0 */
	uint64_t powt:8;
	uint64_t wesewved2:28;
};

#define WESP_WINKSTAT_UP		GENMASK_UWW(9, 9)
#define WESP_WINKSTAT_FDUPWEX		GENMASK_UWW(10, 10)
#define WESP_WINKSTAT_SPEED		GENMASK_UWW(14, 11)
#define WESP_WINKSTAT_EWWTYPE		GENMASK_UWW(24, 15)
#define WESP_WINKSTAT_AN		GENMASK_UWW(25, 25)
#define WESP_WINKSTAT_FEC		GENMASK_UWW(27, 26)
#define WESP_WINKSTAT_POWT		GENMASK_UWW(35, 28)

/* scwatchx(1) CSW used fow non-secuwe SW->ATF communication
 * This CSW acts as a command wegistew
 */
#define CMDWEG_OWN	BIT_UWW(0)
#define CMDWEG_ID	GENMASK_UWW(7, 2)

/* Any command using enabwe/disabwe as an awgument need
 * to set this bitfiewd.
 * Ex: Woopback, HiGig...
 */
#define CMDWEG_ENABWE	BIT_UWW(8)

/* command awgument to be passed fow cmd ID - CGX_CMD_SET_MTU */
#define CMDMTU_SIZE	GENMASK_UWW(23, 8)

/* command awgument to be passed fow cmd ID - CGX_CMD_WINK_CHANGE */
#define CMDWINKCHANGE_WINKUP	BIT_UWW(8)
#define CMDWINKCHANGE_FUWWDPWX	BIT_UWW(9)
#define CMDWINKCHANGE_SPEED	GENMASK_UWW(13, 10)

#define CMDSETFEC			GENMASK_UWW(9, 8)
/* command awgument to be passed fow cmd ID - CGX_CMD_MODE_CHANGE */
#define CMDMODECHANGE_SPEED		GENMASK_UWW(11, 8)
#define CMDMODECHANGE_DUPWEX		GENMASK_UWW(12, 12)
#define CMDMODECHANGE_AN		GENMASK_UWW(13, 13)
#define CMDMODECHANGE_POWT		GENMASK_UWW(21, 14)
#define CMDMODECHANGE_FWAGS		GENMASK_UWW(63, 22)

/* WINK_BWING_UP command timeout */
#define WINKCFG_TIMEOUT		GENMASK_UWW(21, 8)
#endif /* __CGX_FW_INTF_H__ */
