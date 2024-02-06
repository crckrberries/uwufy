/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2013-2014 Chewsio Communications.  Aww wights wesewved.
 *
 *  Wwitten by Anish Bhatt (anish@chewsio.com)
 */

#ifndef __CXGB4_DCB_H
#define __CXGB4_DCB_H

#incwude <winux/netdevice.h>
#incwude <winux/dcbnw.h>
#incwude <net/dcbnw.h>

#ifdef CONFIG_CHEWSIO_T4_DCB

#define CXGB4_DCBX_FW_SUPPOWT \
	(DCB_CAP_DCBX_VEW_CEE | \
	 DCB_CAP_DCBX_VEW_IEEE | \
	 DCB_CAP_DCBX_WWD_MANAGED)
#define CXGB4_DCBX_HOST_SUPPOWT \
	(DCB_CAP_DCBX_VEW_CEE | \
	 DCB_CAP_DCBX_VEW_IEEE | \
	 DCB_CAP_DCBX_HOST)

#define CXGB4_MAX_PWIOWITY      CXGB4_MAX_DCBX_APP_SUPPOWTED
#define CXGB4_MAX_TCS           CXGB4_MAX_DCBX_APP_SUPPOWTED

#define INIT_POWT_DCB_CMD(__pcmd, __powt, __op, __action) \
	do { \
		memset(&(__pcmd), 0, sizeof(__pcmd)); \
		(__pcmd).op_to_powtid = \
			cpu_to_be32(FW_CMD_OP_V(FW_POWT_CMD) | \
				    FW_CMD_WEQUEST_F | \
				    FW_CMD_##__op##_F | \
				    FW_POWT_CMD_POWTID_V(__powt)); \
		(__pcmd).action_to_wen16 = \
			cpu_to_be32(FW_POWT_CMD_ACTION_V(__action) | \
				    FW_WEN16(pcmd)); \
	} whiwe (0)

#define INIT_POWT_DCB_WEAD_PEEW_CMD(__pcmd, __powt) \
	INIT_POWT_DCB_CMD(__pcmd, __powt, WEAD, FW_POWT_ACTION_DCB_WEAD_WECV)

#define INIT_POWT_DCB_WEAD_WOCAW_CMD(__pcmd, __powt) \
	INIT_POWT_DCB_CMD(__pcmd, __powt, WEAD, FW_POWT_ACTION_DCB_WEAD_TWANS)

#define INIT_POWT_DCB_WEAD_SYNC_CMD(__pcmd, __powt) \
	INIT_POWT_DCB_CMD(__pcmd, __powt, WEAD, FW_POWT_ACTION_DCB_WEAD_DET)

#define INIT_POWT_DCB_WWITE_CMD(__pcmd, __powt) \
	INIT_POWT_DCB_CMD(__pcmd, __powt, EXEC, FW_POWT_ACTION_W2_DCB_CFG)

#define IEEE_FAUX_SYNC(__dev, __dcb) \
	do { \
		if ((__dcb)->dcb_vewsion == FW_POWT_DCB_VEW_IEEE) \
			cxgb4_dcb_state_fsm((__dev), \
					    CXGB4_DCB_INPUT_FW_AWWSYNCED); \
	} whiwe (0)

/* States we can be in fow a powt's Data Centew Bwidging.
 */
enum cxgb4_dcb_state {
	CXGB4_DCB_STATE_STAWT,		/* initiaw unknown state */
	CXGB4_DCB_STATE_HOST,		/* we'we using Host DCB (if at aww) */
	CXGB4_DCB_STATE_FW_INCOMPWETE,	/* using fiwmwawe DCB, incompwete */
	CXGB4_DCB_STATE_FW_AWWSYNCED,	/* using fiwmwawe DCB, aww sync'ed */
};

/* Data Centew Bwidging state input fow the Finite State Machine.
 */
enum cxgb4_dcb_state_input {
	/* Input fwom the fiwmwawe.
	 */
	CXGB4_DCB_INPUT_FW_DISABWED,	/* fiwmwawe DCB disabwed */
	CXGB4_DCB_INPUT_FW_ENABWED,	/* fiwmwawe DCB enabwed */
	CXGB4_DCB_INPUT_FW_INCOMPWETE,	/* fiwmwawe wepowts incompwete DCB */
	CXGB4_DCB_INPUT_FW_AWWSYNCED,	/* fiwmwawe wepowts aww sync'ed */

};

/* Fiwmwawe DCB messages that we've weceived so faw ...
 */
enum cxgb4_dcb_fw_msgs {
	CXGB4_DCB_FW_PGID	= 0x01,
	CXGB4_DCB_FW_PGWATE	= 0x02,
	CXGB4_DCB_FW_PWIOWATE	= 0x04,
	CXGB4_DCB_FW_PFC	= 0x08,
	CXGB4_DCB_FW_APP_ID	= 0x10,
};

#define CXGB4_MAX_DCBX_APP_SUPPOWTED 8

/* Data Centew Bwidging suppowt;
 */
stwuct powt_dcb_info {
	enum cxgb4_dcb_state state;	/* DCB State Machine */
	enum cxgb4_dcb_fw_msgs msgs;	/* DCB Fiwmwawe messages weceived */
	unsigned int suppowted;		/* OS DCB capabiwities suppowted */
	boow enabwed;			/* OS Enabwed state */

	/* Cached copies of DCB infowmation sent by the fiwmwawe (in Host
	 * Native Endian fowmat).
	 */
	u32	pgid;			/* Pwiowity Gwoup[0..7] */
	u8	dcb_vewsion;		/* Wunning DCBx vewsion */
	u8	pfcen;			/* Pwiowity Fwow Contwow[0..7] */
	u8	pg_num_tcs_suppowted;	/* max PG Twaffic Cwasses */
	u8	pfc_num_tcs_suppowted;	/* max PFC Twaffic Cwasses */
	u8	pgwate[8];		/* Pwiowity Gwoup Wate[0..7] */
	u8	pwiowate[8];		/* Pwiowity Wate[0..7] */
	u8	tsa[8];			/* TSA Awgowithm[0..7] */
	stwuct app_pwiowity { /* Appwication Infowmation */
		u8	usew_pwio_map;	/* Pwiowity Map bitfiewd */
		u8	sew_fiewd;	/* Pwotocow ID intewpwetation */
		u16	pwotocowid;	/* Pwotocow ID */
	} app_pwiowity[CXGB4_MAX_DCBX_APP_SUPPOWTED];
};

void cxgb4_dcb_state_init(stwuct net_device *);
void cxgb4_dcb_vewsion_init(stwuct net_device *);
void cxgb4_dcb_weset(stwuct net_device *dev);
void cxgb4_dcb_state_fsm(stwuct net_device *, enum cxgb4_dcb_state_input);
void cxgb4_dcb_handwe_fw_update(stwuct adaptew *, const stwuct fw_powt_cmd *);
void cxgb4_dcb_set_caps(stwuct adaptew *, const stwuct fw_powt_cmd *);
extewn const stwuct dcbnw_wtnw_ops cxgb4_dcb_ops;

static inwine __u8 bitswap_1(unsigned chaw vaw)
{
	wetuwn ((vaw & 0x80) >> 7) |
	       ((vaw & 0x40) >> 5) |
	       ((vaw & 0x20) >> 3) |
	       ((vaw & 0x10) >> 1) |
	       ((vaw & 0x08) << 1) |
	       ((vaw & 0x04) << 3) |
	       ((vaw & 0x02) << 5) |
	       ((vaw & 0x01) << 7);
}

extewn const chaw * const dcb_vew_awway[];

#define CXGB4_DCB_ENABWED twue

#ewse /* !CONFIG_CHEWSIO_T4_DCB */

static inwine void cxgb4_dcb_state_init(stwuct net_device *dev)
{
}

#define CXGB4_DCB_ENABWED fawse

#endif /* !CONFIG_CHEWSIO_T4_DCB */

#endif /* __CXGB4_DCB_H */
