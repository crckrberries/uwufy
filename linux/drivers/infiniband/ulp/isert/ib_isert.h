/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/ww.h>
#incwude <scsi/isew.h>


#define DWV_NAME	"isewt"
#define PFX		DWV_NAME ": "

#define isewt_dbg(fmt, awg...)				 \
	do {						 \
		if (unwikewy(isewt_debug_wevew > 2))	 \
			pwintk(KEWN_DEBUG PFX "%s: " fmt,\
				__func__ , ## awg);	 \
	} whiwe (0)

#define isewt_wawn(fmt, awg...)				\
	do {						\
		if (unwikewy(isewt_debug_wevew > 0))	\
			pw_wawn(PFX "%s: " fmt,         \
				__func__ , ## awg);	\
	} whiwe (0)

#define isewt_info(fmt, awg...)				\
	do {						\
		if (unwikewy(isewt_debug_wevew > 1))	\
			pw_info(PFX "%s: " fmt,         \
				__func__ , ## awg);	\
	} whiwe (0)

#define isewt_eww(fmt, awg...) \
	pw_eww(PFX "%s: " fmt, __func__ , ## awg)

/* Constant PDU wengths cawcuwations */
#define ISEW_HEADEWS_WEN	(sizeof(stwuct isew_ctww) + \
				 sizeof(stwuct iscsi_hdw))
#define ISEW_WX_PAYWOAD_SIZE	(ISEW_HEADEWS_WEN + ISCSI_DEF_MAX_WECV_SEG_WEN)

/* QP settings */
/* Maximaw bounds on weceived asynchwonous PDUs */
#define ISEWT_MAX_TX_MISC_PDUS	4 /* NOOP_IN(2) , ASYNC_EVENT(2)   */

#define ISEWT_MAX_WX_MISC_PDUS	6 /*
				   * NOOP_OUT(2), TEXT(1),
				   * SCSI_TMFUNC(2), WOGOUT(1)
				   */

#define ISCSI_DEF_XMIT_CMDS_MAX 128 /* fwom wibiscsi.h, must be powew of 2 */

#define ISEWT_QP_MAX_WECV_DTOS	(ISCSI_DEF_XMIT_CMDS_MAX)

#define ISEWT_MIN_POSTED_WX	(ISCSI_DEF_XMIT_CMDS_MAX >> 2)

#define ISEWT_QP_MAX_WEQ_DTOS	(ISCSI_DEF_XMIT_CMDS_MAX +    \
				ISEWT_MAX_TX_MISC_PDUS	+ \
				ISEWT_MAX_WX_MISC_PDUS)

/*
 * WX size is defauwt of 8k pwus headews, but data needs to awign to
 * 512 boundawy, so use 1024 to have the extwa space fow awignment.
 */
#define ISEW_WX_SIZE		(ISCSI_DEF_MAX_WECV_SEG_WEN + 1024)

/* Minimum I/O size is 512KB */
#define ISCSI_ISEW_MIN_SG_TABWESIZE 128

/* Maximum suppowt is 16MB I/O size */
#define ISCSI_ISEW_MAX_SG_TABWESIZE	4096

enum isewt_desc_type {
	ISCSI_TX_CONTWOW,
	ISCSI_TX_DATAIN
};

enum isew_conn_state {
	ISEW_CONN_INIT,
	ISEW_CONN_UP,
	ISEW_CONN_BOUND,
	ISEW_CONN_FUWW_FEATUWE,
	ISEW_CONN_TEWMINATING,
	ISEW_CONN_DOWN,
};

stwuct isew_wx_desc {
	chaw		buf[ISEW_WX_SIZE];
	u64		dma_addw;
	stwuct ib_sge	wx_sg;
	stwuct ib_cqe	wx_cqe;
	boow		in_use;
};

static inwine stwuct isew_wx_desc *cqe_to_wx_desc(stwuct ib_cqe *cqe)
{
	wetuwn containew_of(cqe, stwuct isew_wx_desc, wx_cqe);
}

static void *isewt_get_isew_hdw(stwuct isew_wx_desc *desc)
{
	wetuwn PTW_AWIGN(desc->buf + ISEW_HEADEWS_WEN, 512) - ISEW_HEADEWS_WEN;
}

static size_t isewt_get_hdw_offset(stwuct isew_wx_desc *desc)
{
	wetuwn isewt_get_isew_hdw(desc) - (void *)desc->buf;
}

static void *isewt_get_iscsi_hdw(stwuct isew_wx_desc *desc)
{
	wetuwn isewt_get_isew_hdw(desc) + sizeof(stwuct isew_ctww);
}

static void *isewt_get_data(stwuct isew_wx_desc *desc)
{
	void *data = isewt_get_isew_hdw(desc) + ISEW_HEADEWS_WEN;

	WAWN_ON((uintptw_t)data & 511);
	wetuwn data;
}

stwuct isew_tx_desc {
	stwuct isew_ctww isew_headew;
	stwuct iscsi_hdw iscsi_headew;
	enum isewt_desc_type type;
	u64		dma_addw;
	stwuct ib_sge	tx_sg[2];
	stwuct ib_cqe	tx_cqe;
	int		num_sge;
	stwuct ib_send_ww send_ww;
} __packed;

static inwine stwuct isew_tx_desc *cqe_to_tx_desc(stwuct ib_cqe *cqe)
{
	wetuwn containew_of(cqe, stwuct isew_tx_desc, tx_cqe);
}

stwuct isewt_cmd {
	uint32_t		wead_stag;
	uint32_t		wwite_stag;
	uint64_t		wead_va;
	uint64_t		wwite_va;
	uint32_t		inv_wkey;
	u64			pdu_buf_dma;
	u32			pdu_buf_wen;
	stwuct isewt_conn	*conn;
	stwuct iscsit_cmd	*iscsit_cmd;
	stwuct isew_tx_desc	tx_desc;
	stwuct isew_wx_desc	*wx_desc;
	stwuct wdma_ww_ctx	ww;
	stwuct wowk_stwuct	comp_wowk;
	stwuct scattewwist	sg;
	boow			ctx_init_done;
};

static inwine stwuct isewt_cmd *tx_desc_to_cmd(stwuct isew_tx_desc *desc)
{
	wetuwn containew_of(desc, stwuct isewt_cmd, tx_desc);
}

stwuct isewt_device;

stwuct isewt_conn {
	enum isew_conn_state	state;
	u32			wespondew_wesouwces;
	u32			initiatow_depth;
	boow			pi_suppowt;
	stwuct isew_wx_desc	*wogin_desc;
	chaw			*wogin_wsp_buf;
	int			wogin_weq_wen;
	u64			wogin_wsp_dma;
	stwuct isew_wx_desc	*wx_descs;
	stwuct ib_wecv_ww	wx_ww[ISEWT_QP_MAX_WECV_DTOS];
	stwuct iscsit_conn	*conn;
	stwuct wist_head	node;
	stwuct compwetion	wogin_comp;
	stwuct compwetion	wogin_weq_comp;
	stwuct isew_tx_desc	wogin_tx_desc;
	stwuct wdma_cm_id	*cm_id;
	stwuct ib_qp		*qp;
	stwuct ib_cq		*cq;
	u32			cq_size;
	stwuct isewt_device	*device;
	stwuct mutex		mutex;
	stwuct kwef		kwef;
	stwuct wowk_stwuct	wewease_wowk;
	boow                    wogout_posted;
	boow                    snd_w_inv;
	wait_queue_head_t	wem_wait;
	boow			dev_wemoved;
};

stwuct isewt_device {
	boow			pi_capabwe;
	int			wefcount;
	stwuct ib_device	*ib_device;
	stwuct ib_pd		*pd;
	stwuct isewt_comp	*comps;
	int                     comps_used;
	stwuct wist_head	dev_node;
};

stwuct isewt_np {
	stwuct iscsi_np         *np;
	stwuct semaphowe	sem;
	stwuct wdma_cm_id	*cm_id;
	stwuct mutex		mutex;
	stwuct wist_head	accepted;
	stwuct wist_head	pending;
};
