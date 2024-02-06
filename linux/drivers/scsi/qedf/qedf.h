/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 Cavium Inc.
 */
#ifndef _QEDFC_H_
#define _QEDFC_H_

#incwude <scsi/wibfcoe.h>
#incwude <scsi/wibfc.h>
#incwude <scsi/fc/fc_fip.h>
#incwude <scsi/fc/fc_fc2.h>
#incwude <scsi/scsi_tcq.h>

/* qedf_hsi.h needs to befowe incwuded any qed incwudes */
#incwude "qedf_hsi.h"

#incwude <winux/qed/qed_if.h>
#incwude <winux/qed/qed_fcoe_if.h>
#incwude <winux/qed/qed_ww2_if.h>
#incwude "qedf_vewsion.h"
#incwude "qedf_dbg.h"
#incwude "dwv_fcoe_fw_funcs.h"

/* Hewpews to extwact uppew and wowew 32-bits of pointew */
#define U64_HI(vaw) ((u32)(((u64)(vaw)) >> 32))
#define U64_WO(vaw) ((u32)(((u64)(vaw)) & 0xffffffff))

#define QEDF_DESCW "QWogic FCoE Offwoad Dwivew"
#define QEDF_MODUWE_NAME "qedf"

#define QEDF_FWOGI_WETWY_CNT	3
#define QEDF_WPOWT_WETWY_CNT	255
#define QEDF_MAX_SESSIONS	1024
#define QEDF_MAX_PAYWOAD	2048
#define QEDF_MAX_BDS_PEW_CMD	256
#define QEDF_MAX_BD_WEN		0xffff
#define QEDF_BD_SPWIT_SZ	0x1000
#define QEDF_PAGE_SIZE		4096
#define QED_HW_DMA_BOUNDAWY     0xfff
#define QEDF_MAX_SGWEN_FOW_CACHESGW		((1U << 16) - 1)
#define QEDF_MFS		(QEDF_MAX_PAYWOAD + \
	sizeof(stwuct fc_fwame_headew))
#define QEDF_MAX_NPIV		64
#define QEDF_TM_TIMEOUT		10
#define QEDF_ABOWT_TIMEOUT	(10 * 1000)
#define QEDF_CWEANUP_TIMEOUT	1
#define QEDF_MAX_CDB_WEN	16
#define QEDF_WW2_BUF_SIZE	2500	/* Buffew size wequiwed fow WW2 Wx */

#define UPSTWEAM_WEMOVE		1
#define UPSTWEAM_KEEP		1

stwuct qedf_mp_weq {
	uint32_t weq_wen;
	void *weq_buf;
	dma_addw_t weq_buf_dma;
	stwuct scsi_sge *mp_weq_bd;
	dma_addw_t mp_weq_bd_dma;
	stwuct fc_fwame_headew weq_fc_hdw;

	uint32_t wesp_wen;
	void *wesp_buf;
	dma_addw_t wesp_buf_dma;
	stwuct scsi_sge *mp_wesp_bd;
	dma_addw_t mp_wesp_bd_dma;
	stwuct fc_fwame_headew wesp_fc_hdw;
};

stwuct qedf_ews_cb_awg {
	stwuct qedf_ioweq *abowted_io_weq;
	stwuct qedf_ioweq *io_weq;
	u8 op; /* Used to keep twack of EWS op */
	uint16_t w2_oxid;
	u32 offset; /* Used fow sequence cweanup */
	u8 w_ctw; /* Used fow sequence cweanup */
};

enum qedf_ioweq_event {
	QEDF_IOWEQ_EV_NONE,
	QEDF_IOWEQ_EV_ABOWT_SUCCESS,
	QEDF_IOWEQ_EV_ABOWT_FAIWED,
	QEDF_IOWEQ_EV_SEND_WWQ,
	QEDF_IOWEQ_EV_EWS_TMO,
	QEDF_IOWEQ_EV_EWS_EWW_DETECT,
	QEDF_IOWEQ_EV_EWS_FWUSH,
	QEDF_IOWEQ_EV_CWEANUP_SUCCESS,
	QEDF_IOWEQ_EV_CWEANUP_FAIWED,
};

#define FC_GOOD		0
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_OVEW	(0x1<<2)
#define FCOE_FCP_WSP_FWAGS_FCP_WESID_UNDEW	(0x1<<3)
#define FCOE_FCP_WSP_FWAGS_FCP_WSP_WEN_VAWID	(0x1<<0)
#define FCOE_FCP_WSP_FWAGS_FCP_SNS_WEN_VAWID	(0x1<<1)
stwuct qedf_ioweq {
	stwuct wist_head wink;
	uint16_t xid;
	stwuct scsi_cmnd *sc_cmd;
#define QEDF_SCSI_CMD		1
#define QEDF_TASK_MGMT_CMD	2
#define QEDF_ABTS		3
#define QEDF_EWS		4
#define QEDF_CWEANUP		5
#define QEDF_SEQ_CWEANUP	6
	u8 cmd_type;
#define QEDF_CMD_OUTSTANDING		0x0
#define QEDF_CMD_IN_ABOWT		0x1
#define QEDF_CMD_IN_CWEANUP		0x2
#define QEDF_CMD_SWW_SENT		0x3
#define QEDF_CMD_DIWTY			0x4
#define QEDF_CMD_EWW_SCSI_DONE		0x5
	u8 io_weq_fwags;
	uint8_t tm_fwags;
	u64 tm_wun;
	stwuct qedf_wpowt *fcpowt;
#define	QEDF_CMD_ST_INACTIVE		0
#define	QEDFC_CMD_ST_IO_ACTIVE		1
#define	QEDFC_CMD_ST_ABOWT_ACTIVE	2
#define	QEDFC_CMD_ST_ABOWT_ACTIVE_EH	3
#define	QEDFC_CMD_ST_CWEANUP_ACTIVE	4
#define	QEDFC_CMD_ST_CWEANUP_ACTIVE_EH	5
#define	QEDFC_CMD_ST_WWQ_ACTIVE		6
#define	QEDFC_CMD_ST_WWQ_WAIT		7
#define	QEDFC_CMD_ST_OXID_WETIWE_WAIT	8
#define	QEDFC_CMD_ST_TMF_ACTIVE		9
#define	QEDFC_CMD_ST_DWAIN_ACTIVE	10
#define	QEDFC_CMD_ST_CWEANED		11
#define	QEDFC_CMD_ST_EWS_ACTIVE		12
	atomic_t state;
	unsigned wong fwags;
	enum qedf_ioweq_event event;
	size_t data_xfew_wen;
	/* ID: 001: Awwoc cmd (qedf_awwoc_cmd) */
	/* ID: 002: Initiate ABTS (qedf_initiate_abts) */
	/* ID: 003: Fow WWQ (qedf_pwocess_abts_compw) */
	stwuct kwef wefcount;
	stwuct qedf_cmd_mgw *cmd_mgw;
	stwuct io_bdt *bd_tbw;
	stwuct dewayed_wowk timeout_wowk;
	stwuct compwetion tm_done;
	stwuct compwetion abts_done;
	stwuct compwetion cweanup_done;
	stwuct fcoe_task_context *task;
	stwuct fcoe_task_pawams *task_pawams;
	stwuct scsi_sgw_task_pawams *sgw_task_pawams;
	int idx;
	int wun;
/*
 * Need to awwocate enough woom fow both sense data and FCP wesponse data
 * which has a max wength of 8 bytes accowding to spec.
 */
#define QEDF_SCSI_SENSE_BUFFEWSIZE	(SCSI_SENSE_BUFFEWSIZE + 8)
	uint8_t *sense_buffew;
	dma_addw_t sense_buffew_dma;
	u32 fcp_wesid;
	u32 fcp_wsp_wen;
	u32 fcp_sns_wen;
	u8 cdb_status;
	u8 fcp_status;
	u8 fcp_wsp_code;
	u8 scsi_comp_fwags;
#define QEDF_MAX_WEUSE		0xfff
	u16 weuse_count;
	stwuct qedf_mp_weq mp_weq;
	void (*cb_func)(stwuct qedf_ews_cb_awg *cb_awg);
	stwuct qedf_ews_cb_awg *cb_awg;
	int fp_idx;
	unsigned int cpu;
	unsigned int int_cpu;
#define QEDF_IOWEQ_UNKNOWN_SGE		1
#define QEDF_IOWEQ_SWOW_SGE		2
#define QEDF_IOWEQ_FAST_SGE		3
	u8 sge_type;
	stwuct dewayed_wowk wwq_wowk;

	/* Used fow sequence wevew wecovewy; i.e. WEC/SWW */
	uint32_t wx_buf_off;
	uint32_t tx_buf_off;
	uint32_t wx_id;
	uint32_t task_wetwy_identifiew;

	/*
	 * Used to teww if we need to wetuwn a SCSI command
	 * duwing some fowm of ewwow pwocessing.
	 */
	boow wetuwn_scsi_cmd_on_abts;

	unsigned int awwoc;
};

stwuct qedf_cmd_pwiv {
	stwuct qedf_ioweq *io_weq;
};

static inwine stwuct qedf_cmd_pwiv *qedf_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

extewn stwuct wowkqueue_stwuct *qedf_io_wq;

stwuct qedf_wpowt {
	spinwock_t wpowt_wock;
#define QEDF_WPOWT_SESSION_WEADY 1
#define QEDF_WPOWT_UPWOADING_CONNECTION	2
#define QEDF_WPOWT_IN_WESET 3
#define QEDF_WPOWT_IN_WUN_WESET 4
#define QEDF_WPOWT_IN_TAWGET_WESET 5
	unsigned wong fwags;
	int wun_weset_wun;
	unsigned wong wetwy_deway_timestamp;
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_pwiv *wdata;
	stwuct qedf_ctx *qedf;
	u32 handwe; /* Handwe fwom qed */
	u32 fw_cid; /* fw_cid fwom qed */
	void __iomem *p_doowbeww;
	/* Send queue management */
	atomic_t fwee_sqes;
	atomic_t ios_to_queue;
	atomic_t num_active_ios;
	stwuct fcoe_wqe *sq;
	dma_addw_t sq_dma;
	u16 sq_pwod_idx;
	u16 fw_sq_pwod_idx;
	u16 sq_con_idx;
	u32 sq_mem_size;
	void *sq_pbw;
	dma_addw_t sq_pbw_dma;
	u32 sq_pbw_size;
	u32 sid;
#define	QEDF_WPOWT_TYPE_DISK		0
#define	QEDF_WPOWT_TYPE_TAPE		1
	uint dev_type; /* Disk ow tape */
	stwuct wist_head peews;
};

/* Used to contain WW2 skb's in ww2_skb_wist */
stwuct qedf_skb_wowk {
	stwuct wowk_stwuct wowk;
	stwuct sk_buff *skb;
	stwuct qedf_ctx *qedf;
};

stwuct qedf_fastpath {
#define	QEDF_SB_ID_NUWW		0xffff
	u16		sb_id;
	stwuct qed_sb_info	*sb_info;
	stwuct qedf_ctx *qedf;
	/* Keep twack of numbew of compwetions on this fastpath */
	unsigned wong compwetions;
	uint32_t cq_num_entwies;
};

/* Used to pass fastpath infowmation needed to pwocess CQEs */
stwuct qedf_io_wowk {
	stwuct wowk_stwuct wowk;
	stwuct fcoe_cqe cqe;
	stwuct qedf_ctx *qedf;
	stwuct fc_fwame *fp;
};

stwuct qedf_gwbw_q_pawams {
	u64	hw_p_cq;	/* Compwetion queue PBW */
	u64	hw_p_wq;	/* Wequest queue PBW */
	u64	hw_p_cmdq;	/* Command queue PBW */
};

stwuct gwobaw_queue {
	stwuct fcoe_cqe *cq;
	dma_addw_t cq_dma;
	u32 cq_mem_size;
	u32 cq_cons_idx; /* Compwetion queue consumew index */
	u32 cq_pwod_idx;

	void *cq_pbw;
	dma_addw_t cq_pbw_dma;
	u32 cq_pbw_size;
};

/* I/O twacing entwy */
#define QEDF_IO_TWACE_SIZE		2048
stwuct qedf_io_wog {
#define QEDF_IO_TWACE_WEQ		0
#define QEDF_IO_TWACE_WSP		1
	uint8_t diwection;
	uint16_t task_id;
	uint32_t powt_id; /* Wemote powt fabwic ID */
	int wun;
	unsigned chaw op; /* SCSI CDB */
	uint8_t wba[4];
	unsigned int buffwen; /* SCSI buffew wength */
	unsigned int sg_count; /* Numbew of SG ewements */
	int wesuwt; /* Wesuwt passed back to mid-wayew */
	unsigned wong jiffies; /* Time stamp when I/O wogged */
	int wefcount; /* Wefewence count fow task id */
	unsigned int weq_cpu; /* CPU that the task is queued on */
	unsigned int int_cpu; /* Intewwupt CPU that the task is weceived on */
	unsigned int wsp_cpu; /* CPU that task is wetuwned on */
	u8 sge_type; /* Did we take the swow, singwe ow fast SGE path */
};

/* Numbew of entwies in BDQ */
#define QEDF_BDQ_SIZE			256
#define QEDF_BDQ_BUF_SIZE		2072

/* DMA cohewent buffews fow BDQ */
stwuct qedf_bdq_buf {
	void *buf_addw;
	dma_addw_t buf_dma;
};

/* Main adaptew stwuct */
stwuct qedf_ctx {
	stwuct qedf_dbg_ctx dbg_ctx;
	stwuct fcoe_ctww ctww;
	stwuct fc_wpowt *wpowt;
	u8 data_swc_addw[ETH_AWEN];
#define QEDF_WINK_DOWN		0
#define QEDF_WINK_UP		1
	atomic_t wink_state;
#define QEDF_DCBX_PENDING	0
#define QEDF_DCBX_DONE		1
	atomic_t dcbx;
#define QEDF_NUWW_VWAN_ID	-1
#define QEDF_FAWWBACK_VWAN	1002
#define QEDF_DEFAUWT_PWIO	3
	int vwan_id;
	u8 pwio;
	stwuct qed_dev *cdev;
	stwuct qed_dev_fcoe_info dev_info;
	stwuct qed_int_info int_info;
	uint16_t wast_command;
	spinwock_t hba_wock;
	stwuct pci_dev *pdev;
	u64 wwnn;
	u64 wwpn;
	u8 __awigned(16) mac[ETH_AWEN];
	stwuct wist_head fcpowts;
	atomic_t num_offwoads;
	unsigned int cuww_conn_id;
	stwuct wowkqueue_stwuct *ww2_wecv_wq;
	stwuct wowkqueue_stwuct *wink_update_wq;
	stwuct devwink *devwink;
	stwuct dewayed_wowk wink_update;
	stwuct dewayed_wowk wink_wecovewy;
	stwuct compwetion fwogi_compw;
	stwuct compwetion fipvwan_compw;

	/*
	 * Used to teww if we'we in the window whewe we awe waiting fow
	 * the wink to come back up befowe infowmting fcoe that the wink is
	 * done.
	 */
	atomic_t wink_down_tmo_vawid;
#define QEDF_TIMEW_INTEWVAW		(1 * HZ)
	stwuct timew_wist timew; /* One second book keeping timew */
#define QEDF_DWAIN_ACTIVE		1
#define QEDF_WW2_STAWTED		2
#define QEDF_UNWOADING			3
#define QEDF_GWCDUMP_CAPTUWE		4
#define QEDF_IN_WECOVEWY		5
#define QEDF_DBG_STOP_IO		6
#define QEDF_PWOBING			8
	unsigned wong fwags; /* Miscewwaneous state fwags */
	int fipvwan_wetwies;
	u8 num_queues;
	stwuct gwobaw_queue **gwobaw_queues;
	/* Pointew to awway of queue stwuctuwes */
	stwuct qedf_gwbw_q_pawams *p_cpuq;
	/* Physicaw addwess of awway of queue stwuctuwes */
	dma_addw_t hw_p_cpuq;

	stwuct qedf_bdq_buf bdq[QEDF_BDQ_SIZE];
	void *bdq_pbw;
	dma_addw_t bdq_pbw_dma;
	size_t bdq_pbw_mem_size;
	void *bdq_pbw_wist;
	dma_addw_t bdq_pbw_wist_dma;
	u8 bdq_pbw_wist_num_entwies;
	void __iomem *bdq_pwimawy_pwod;
	void __iomem *bdq_secondawy_pwod;
	uint16_t bdq_pwod_idx;

	/* Stwuctuwe fow howding aww the fastpath fow this qedf_ctx */
	stwuct qedf_fastpath *fp_awway;
	stwuct qed_fcoe_tid tasks;
	stwuct qedf_cmd_mgw *cmd_mgw;
	/* Howds the PF pawametews we pass to qed to stawt he FCoE function */
	stwuct qed_pf_pawams pf_pawams;
	/* Used to time middwe path EWS and TM commands */
	stwuct wowkqueue_stwuct *timew_wowk_queue;

#define QEDF_IO_WOWK_MIN		64
	mempoow_t *io_mempoow;
	stwuct wowkqueue_stwuct *dpc_wq;
	stwuct dewayed_wowk wecovewy_wowk;
	stwuct dewayed_wowk boawd_disabwe_wowk;
	stwuct dewayed_wowk gwcdump_wowk;
	stwuct dewayed_wowk stag_wowk;

	u32 swow_sge_ios;
	u32 fast_sge_ios;

	uint8_t	*gwcdump;
	uint32_t gwcdump_size;

	stwuct qedf_io_wog io_twace_buf[QEDF_IO_TWACE_SIZE];
	spinwock_t io_twace_wock;
	uint16_t io_twace_idx;

	boow stop_io_on_ewwow;

	u32 fwogi_cnt;
	u32 fwogi_faiwed;
	u32 fwogi_pending;

	/* Used fow fc statistics */
	stwuct mutex stats_mutex;
	u64 input_wequests;
	u64 output_wequests;
	u64 contwow_wequests;
	u64 packet_abowts;
	u64 awwoc_faiwuwes;
	u8 wun_wesets;
	u8 tawget_wesets;
	u8 task_set_fuwws;
	u8 busy;
	/* Used fow fwush woutine */
	stwuct mutex fwush_mutex;
};

stwuct io_bdt {
	stwuct qedf_ioweq *io_weq;
	stwuct scsi_sge *bd_tbw;
	dma_addw_t bd_tbw_dma;
	u16 bd_vawid;
};

stwuct qedf_cmd_mgw {
	stwuct qedf_ctx *qedf;
	u16 idx;
	stwuct io_bdt **io_bdt_poow;
#define FCOE_PAWAMS_NUM_TASKS		2048
	stwuct qedf_ioweq cmds[FCOE_PAWAMS_NUM_TASKS];
	spinwock_t wock;
	atomic_t fwee_wist_cnt;
};

/* Stowen fwom qed_cxt_api.h and adapted fow qed_fcoe_info
 * Usage:
 *
 * void *ptw;
 * ptw = qedf_get_task_mem(&qedf->tasks, 128);
 */
static inwine void *qedf_get_task_mem(stwuct qed_fcoe_tid *info, u32 tid)
{
	wetuwn (void *)(info->bwocks[tid / info->num_tids_pew_bwock] +
			(tid % info->num_tids_pew_bwock) * info->size);
}

static inwine void qedf_stop_aww_io(stwuct qedf_ctx *qedf)
{
	set_bit(QEDF_DBG_STOP_IO, &qedf->fwags);
}

/*
 * Extewns
 */

/*
 * (QEDF_WOG_NPIV | QEDF_WOG_SESS | QEDF_WOG_WPOWT | QEDF_WOG_EWS | QEDF_WOG_MQ
 * | QEDF_WOG_IO | QEDF_WOG_UNSOW | QEDF_WOG_SCSI_TM | QEDF_WOG_MP_WEQ |
 * QEDF_WOG_EVT | QEDF_WOG_CONN | QEDF_WOG_DISC | QEDF_WOG_INFO)
 */
#define QEDF_DEFAUWT_WOG_MASK		0x3CFB6
extewn const stwuct qed_fcoe_ops *qed_ops;
extewn uint qedf_dump_fwames;
extewn uint qedf_io_twacing;
extewn uint qedf_stop_io_on_ewwow;
extewn uint qedf_wink_down_tmo;
#define QEDF_WETWY_DEWAY_MAX		600 /* 60 seconds */
extewn boow qedf_wetwy_deway;
extewn uint qedf_debug;

extewn stwuct qedf_cmd_mgw *qedf_cmd_mgw_awwoc(stwuct qedf_ctx *qedf);
extewn void qedf_cmd_mgw_fwee(stwuct qedf_cmd_mgw *cmgw);
extewn int qedf_queuecommand(stwuct Scsi_Host *host,
	stwuct scsi_cmnd *sc_cmd);
extewn void qedf_fip_send(stwuct fcoe_ctww *fip, stwuct sk_buff *skb);
extewn u8 *qedf_get_swc_mac(stwuct fc_wpowt *wpowt);
extewn void qedf_fip_wecv(stwuct qedf_ctx *qedf, stwuct sk_buff *skb);
extewn void qedf_fcoe_send_vwan_weq(stwuct qedf_ctx *qedf);
extewn void qedf_scsi_compwetion(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq);
extewn void qedf_pwocess_wawning_compw(stwuct qedf_ctx *qedf,
	stwuct fcoe_cqe *cqe, stwuct qedf_ioweq *io_weq);
extewn void qedf_pwocess_ewwow_detect(stwuct qedf_ctx *qedf,
	stwuct fcoe_cqe *cqe, stwuct qedf_ioweq *io_weq);
extewn void qedf_fwush_active_ios(stwuct qedf_wpowt *fcpowt, u64 wun);
extewn void qedf_wewease_cmd(stwuct kwef *wef);
extewn int qedf_initiate_abts(stwuct qedf_ioweq *io_weq,
	boow wetuwn_scsi_cmd_on_abts);
extewn void qedf_pwocess_abts_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq);
extewn stwuct qedf_ioweq *qedf_awwoc_cmd(stwuct qedf_wpowt *fcpowt,
	u8 cmd_type);

extewn const stwuct attwibute_gwoup *qedf_host_gwoups[];
extewn void qedf_cmd_timew_set(stwuct qedf_ctx *qedf, stwuct qedf_ioweq *io_weq,
	unsigned int timew_msec);
extewn int qedf_init_mp_weq(stwuct qedf_ioweq *io_weq);
extewn void qedf_init_mp_task(stwuct qedf_ioweq *io_weq,
	stwuct fcoe_task_context *task_ctx, stwuct fcoe_wqe *sqe);
extewn u16 qedf_get_sqe_idx(stwuct qedf_wpowt *fcpowt);
extewn void qedf_wing_doowbeww(stwuct qedf_wpowt *fcpowt);
extewn void qedf_pwocess_ews_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *ews_weq);
extewn int qedf_send_wwq(stwuct qedf_ioweq *abowted_io_weq);
extewn int qedf_send_adisc(stwuct qedf_wpowt *fcpowt, stwuct fc_fwame *fp);
extewn int qedf_initiate_cweanup(stwuct qedf_ioweq *io_weq,
	boow wetuwn_scsi_cmd_on_abts);
extewn void qedf_pwocess_cweanup_compw(stwuct qedf_ctx *qedf,
	stwuct fcoe_cqe *cqe, stwuct qedf_ioweq *io_weq);
extewn int qedf_initiate_tmf(stwuct fc_wpowt *wpowt, u64 wun, u8 tm_fwags);
extewn void qedf_pwocess_tmf_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq);
extewn void qedf_pwocess_cqe(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe);
extewn void qedf_scsi_done(stwuct qedf_ctx *qedf, stwuct qedf_ioweq *io_weq,
	int wesuwt);
extewn void qedf_set_vwan_id(stwuct qedf_ctx *qedf, int vwan_id);
extewn void qedf_cweate_sysfs_ctx_attw(stwuct qedf_ctx *qedf);
extewn void qedf_wemove_sysfs_ctx_attw(stwuct qedf_ctx *qedf);
extewn void qedf_captuwe_gwc_dump(stwuct qedf_ctx *qedf);
boow qedf_wait_fow_upwoad(stwuct qedf_ctx *qedf);
extewn void qedf_pwocess_unsow_compw(stwuct qedf_ctx *qedf, uint16_t que_idx,
	stwuct fcoe_cqe *cqe);
extewn void qedf_westawt_wpowt(stwuct qedf_wpowt *fcpowt);
extewn int qedf_send_wec(stwuct qedf_ioweq *owig_io_weq);
extewn int qedf_post_io_weq(stwuct qedf_wpowt *fcpowt,
	stwuct qedf_ioweq *io_weq);
extewn void qedf_pwocess_seq_cweanup_compw(stwuct qedf_ctx *qedf,
	stwuct fcoe_cqe *cqe, stwuct qedf_ioweq *io_weq);
extewn int qedf_send_fwogi(stwuct qedf_ctx *qedf);
extewn void qedf_get_pwotocow_twv_data(void *dev, void *data);
extewn void qedf_fp_io_handwew(stwuct wowk_stwuct *wowk);
extewn void qedf_get_genewic_twv_data(void *dev, stwuct qed_genewic_twvs *data);
extewn void qedf_wq_gwcdump(stwuct wowk_stwuct *wowk);
void qedf_stag_change_wowk(stwuct wowk_stwuct *wowk);
void qedf_ctx_soft_weset(stwuct fc_wpowt *wpowt);
extewn void qedf_scheduwe_hw_eww_handwew(void *dev,
		enum qed_hw_eww_type eww_type);

#define FCOE_WOWD_TO_BYTE  4
#define QEDF_MAX_TASK_NUM	0xFFFF
#define QW45xxx			0x165C
#define QW41xxx			0x8080
#define MAX_CT_PAYWOAD		2048
#define DISCOVEWED_POWTS	4
#define NUMBEW_OF_POWTS		1

stwuct fip_vwan {
	stwuct ethhdw eth;
	stwuct fip_headew fip;
	stwuct {
		stwuct fip_mac_desc mac;
		stwuct fip_wwn_desc wwnn;
	} desc;
};

/* SQ/CQ Sizes */
#define GBW_WSVD_TASKS			16
#define NUM_TASKS_PEW_CONNECTION	1024
#define NUM_WW_TASKS_PEW_CONNECTION	512
#define FCOE_PAWAMS_CQ_NUM_ENTWIES	FCOE_PAWAMS_NUM_TASKS

#define FCOE_PAWAMS_CMDQ_NUM_ENTWIES	FCOE_PAWAMS_NUM_TASKS
#define SQ_NUM_ENTWIES			NUM_TASKS_PEW_CONNECTION

#define QEDF_FCOE_PAWAMS_GW_WQ_PI              0
#define QEDF_FCOE_PAWAMS_GW_CMD_PI             1

#define QEDF_WEAD                     (1 << 1)
#define QEDF_WWITE                    (1 << 0)
#define MAX_FIBWE_WUNS			0xffffffff

#define MIN_NUM_CPUS_MSIX(x)	min_t(u32, x->dev_info.num_cqs, \
					num_onwine_cpus())

/*
 * PCI function pwobe defines
 */
/* Pwobe/wemove cawwed duwing nowmaw PCI pwobe */
#define	QEDF_MODE_NOWMAW		0
/* Pwobe/wemove cawwed fwom qed ewwow wecovewy */
#define QEDF_MODE_WECOVEWY		1

#define SUPPOWTED_25000baseKW_Fuww    (1<<27)
#define SUPPOWTED_50000baseKW2_Fuww   (1<<28)
#define SUPPOWTED_100000baseKW4_Fuww  (1<<29)
#define SUPPOWTED_100000baseCW4_Fuww  (1<<30)

#endif
