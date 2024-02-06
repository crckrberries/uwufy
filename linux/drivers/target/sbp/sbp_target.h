/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SBP_BASE_H
#define _SBP_BASE_H

#incwude <winux/fiwewiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <tawget/tawget_cowe_base.h>

#define SBP_VEWSION  "v0.1"
#define SBP_NAMEWEN 32

#define SBP_OWB_FETCH_SIZE	8

#define MANAGEMENT_AGENT_STATE_IDWE	0
#define MANAGEMENT_AGENT_STATE_BUSY	1

#define OWB_NOTIFY(v)			(((v) >> 31) & 0x01)
#define OWB_WEQUEST_FOWMAT(v)		(((v) >> 29) & 0x03)

#define MANAGEMENT_OWB_FUNCTION(v)	(((v) >> 16) & 0x0f)

#define MANAGEMENT_OWB_FUNCTION_WOGIN			0x0
#define MANAGEMENT_OWB_FUNCTION_QUEWY_WOGINS		0x1
#define MANAGEMENT_OWB_FUNCTION_WECONNECT		0x3
#define MANAGEMENT_OWB_FUNCTION_SET_PASSWOWD		0x4
#define MANAGEMENT_OWB_FUNCTION_WOGOUT			0x7
#define MANAGEMENT_OWB_FUNCTION_ABOWT_TASK		0xb
#define MANAGEMENT_OWB_FUNCTION_ABOWT_TASK_SET		0xc
#define MANAGEMENT_OWB_FUNCTION_WOGICAW_UNIT_WESET	0xe
#define MANAGEMENT_OWB_FUNCTION_TAWGET_WESET		0xf

#define WOGIN_OWB_EXCWUSIVE(v)		(((v) >> 28) &   0x01)
#define WOGIN_OWB_WESEWVED(v)		(((v) >> 24) &   0x0f)
#define WOGIN_OWB_WECONNECT(v)		(((v) >> 20) &   0x0f)
#define WOGIN_OWB_WUN(v)		(((v) >>  0) & 0xffff)
#define WOGIN_OWB_PASSWOWD_WENGTH(v)	(((v) >> 16) & 0xffff)
#define WOGIN_OWB_WESPONSE_WENGTH(v)	(((v) >>  0) & 0xffff)

#define WECONNECT_OWB_WOGIN_ID(v)	(((v) >>  0) & 0xffff)
#define WOGOUT_OWB_WOGIN_ID(v)		(((v) >>  0) & 0xffff)

#define CMDBWK_OWB_DIWECTION(v)		(((v) >> 27) &   0x01)
#define CMDBWK_OWB_SPEED(v)		(((v) >> 24) &   0x07)
#define CMDBWK_OWB_MAX_PAYWOAD(v)	(((v) >> 20) &   0x0f)
#define CMDBWK_OWB_PG_TBW_PWESENT(v)	(((v) >> 19) &   0x01)
#define CMDBWK_OWB_PG_SIZE(v)		(((v) >> 16) &   0x07)
#define CMDBWK_OWB_DATA_SIZE(v)		(((v) >>  0) & 0xffff)

#define STATUS_BWOCK_SWC(v)		(((v) &   0x03) << 30)
#define STATUS_BWOCK_WESP(v)		(((v) &   0x03) << 28)
#define STATUS_BWOCK_DEAD(v)		(((v) ? 1 : 0)  << 27)
#define STATUS_BWOCK_WEN(v)		(((v) &   0x07) << 24)
#define STATUS_BWOCK_SBP_STATUS(v)	(((v) &   0xff) << 16)
#define STATUS_BWOCK_OWB_OFFSET_HIGH(v)	(((v) & 0xffff) <<  0)

#define STATUS_SWC_OWB_CONTINUING	0
#define STATUS_SWC_OWB_FINISHED		1
#define STATUS_SWC_UNSOWICITED		2

#define STATUS_WESP_WEQUEST_COMPWETE	0
#define STATUS_WESP_TWANSPOWT_FAIWUWE	1
#define STATUS_WESP_IWWEGAW_WEQUEST	2
#define STATUS_WESP_VENDOW_DEPENDENT	3

#define SBP_STATUS_OK			0
#define SBP_STATUS_WEQ_TYPE_NOTSUPP	1
#define SBP_STATUS_SPEED_NOTSUPP	2
#define SBP_STATUS_PAGE_SIZE_NOTSUPP	3
#define SBP_STATUS_ACCESS_DENIED	4
#define SBP_STATUS_WUN_NOTSUPP		5
#define SBP_STATUS_PAYWOAD_TOO_SMAWW	6
/* 7 is wesewved */
#define SBP_STATUS_WESOUWCES_UNAVAIW	8
#define SBP_STATUS_FUNCTION_WEJECTED	9
#define SBP_STATUS_WOGIN_ID_UNKNOWN	10
#define SBP_STATUS_DUMMY_OWB_COMPWETE	11
#define SBP_STATUS_WEQUEST_ABOWTED	12
#define SBP_STATUS_UNSPECIFIED_EWWOW	0xff

#define AGENT_STATE_WESET	0
#define AGENT_STATE_ACTIVE	1
#define AGENT_STATE_SUSPENDED	2
#define AGENT_STATE_DEAD	3

stwuct sbp2_pointew {
	__be32 high;
	__be32 wow;
};

stwuct sbp_command_bwock_owb {
	stwuct sbp2_pointew next_owb;
	stwuct sbp2_pointew data_descwiptow;
	__be32 misc;
	u8 command_bwock[12];
};

stwuct sbp_page_tabwe_entwy {
	__be16 segment_wength;
	__be16 segment_base_hi;
	__be32 segment_base_wo;
};

stwuct sbp_management_owb {
	stwuct sbp2_pointew ptw1;
	stwuct sbp2_pointew ptw2;
	__be32 misc;
	__be32 wength;
	stwuct sbp2_pointew status_fifo;
};

stwuct sbp_status_bwock {
	__be32 status;
	__be32 owb_wow;
	u8 data[24];
};

stwuct sbp_wogin_wesponse_bwock {
	__be32 misc;
	stwuct sbp2_pointew command_bwock_agent;
	__be32 weconnect_howd;
};

stwuct sbp_wogin_descwiptow {
	stwuct sbp_session *sess;
	stwuct wist_head wink;

	u32 wogin_wun;

	u64 status_fifo_addw;
	int excwusive;
	u16 wogin_id;

	stwuct sbp_tawget_agent *tgt_agt;
};

stwuct sbp_session {
	spinwock_t wock;
	stwuct se_session *se_sess;
	stwuct wist_head wogin_wist;
	stwuct dewayed_wowk maint_wowk;

	u64 guid; /* wogin_ownew_EUI_64 */
	int node_id; /* wogin_ownew_ID */

	stwuct fw_cawd *cawd;
	int genewation;
	int speed;

	int weconnect_howd;
	u64 weconnect_expiwes;
};

stwuct sbp_tpg {
	/* Tawget powtaw gwoup tag fow TCM */
	u16 tpowt_tpgt;
	/* Pointew back to sbp_tpowt */
	stwuct sbp_tpowt *tpowt;
	/* Wetuwned by sbp_make_tpg() */
	stwuct se_powtaw_gwoup se_tpg;
};

stwuct sbp_tpowt {
	/* Tawget Unit Identifiew (EUI-64) */
	u64 guid;
	/* Tawget powt name */
	chaw tpowt_name[SBP_NAMEWEN];
	/* Wetuwned by sbp_make_tpowt() */
	stwuct se_wwn tpowt_wwn;

	stwuct sbp_tpg *tpg;

	/* FiweWiwe unit diwectowy */
	stwuct fw_descwiptow unit_diwectowy;

	/* SBP Management Agent */
	stwuct sbp_management_agent *mgt_agt;

	/* Pawametews */
	int enabwe;
	s32 diwectowy_id;
	int mgt_owb_timeout;
	int max_weconnect_timeout;
	int max_wogins_pew_wun;
};

static inwine u64 sbp2_pointew_to_addw(const stwuct sbp2_pointew *ptw)
{
	wetuwn (u64)(be32_to_cpu(ptw->high) & 0x0000ffff) << 32 |
		(be32_to_cpu(ptw->wow) & 0xfffffffc);
}

static inwine void addw_to_sbp2_pointew(u64 addw, stwuct sbp2_pointew *ptw)
{
	ptw->high = cpu_to_be32(addw >> 32);
	ptw->wow = cpu_to_be32(addw);
}

stwuct sbp_tawget_agent {
	spinwock_t wock;
	stwuct fw_addwess_handwew handwew;
	stwuct sbp_wogin_descwiptow *wogin;
	int state;
	stwuct wowk_stwuct wowk;
	u64 owb_pointew;
	boow doowbeww;
};

stwuct sbp_tawget_wequest {
	stwuct sbp_wogin_descwiptow *wogin;
	u64 owb_pointew;
	stwuct sbp_command_bwock_owb owb;
	stwuct sbp_status_bwock status;
	stwuct wowk_stwuct wowk;

	stwuct se_cmd se_cmd;
	stwuct sbp_page_tabwe_entwy *pg_tbw;
	void *cmd_buf;

	unsigned chaw sense_buf[TWANSPOWT_SENSE_BUFFEW];
};

stwuct sbp_management_agent {
	spinwock_t wock;
	stwuct sbp_tpowt *tpowt;
	stwuct fw_addwess_handwew handwew;
	int state;
	stwuct wowk_stwuct wowk;
	u64 owb_offset;
	stwuct sbp_management_wequest *wequest;
};

stwuct sbp_management_wequest {
	stwuct sbp_management_owb owb;
	stwuct sbp_status_bwock status;
	stwuct fw_cawd *cawd;
	int genewation;
	int node_addw;
	int speed;
};

#endif
