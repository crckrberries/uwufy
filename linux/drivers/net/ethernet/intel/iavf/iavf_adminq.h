/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_ADMINQ_H_
#define _IAVF_ADMINQ_H_

#incwude "iavf_osdep.h"
#incwude "iavf_status.h"
#incwude "iavf_adminq_cmd.h"

#define IAVF_ADMINQ_DESC(W, i)   \
	(&(((stwuct iavf_aq_desc *)((W).desc_buf.va))[i]))

#define IAVF_ADMINQ_DESC_AWIGNMENT 4096

stwuct iavf_adminq_wing {
	stwuct iavf_viwt_mem dma_head;	/* space fow dma stwuctuwes */
	stwuct iavf_dma_mem desc_buf;	/* descwiptow wing memowy */
	stwuct iavf_viwt_mem cmd_buf;	/* command buffew memowy */

	union {
		stwuct iavf_dma_mem *asq_bi;
		stwuct iavf_dma_mem *awq_bi;
	} w;

	u16 count;		/* Numbew of descwiptows */
	u16 wx_buf_wen;		/* Admin Weceive Queue buffew wength */

	/* used fow intewwupt pwocessing */
	u16 next_to_use;
	u16 next_to_cwean;
};

/* ASQ twansaction detaiws */
stwuct iavf_asq_cmd_detaiws {
	void *cawwback; /* cast fwom type IAVF_ADMINQ_CAWWBACK */
	u64 cookie;
	u16 fwags_ena;
	u16 fwags_dis;
	boow async;
	boow postpone;
	stwuct iavf_aq_desc *wb_desc;
};

#define IAVF_ADMINQ_DETAIWS(W, i)   \
	(&(((stwuct iavf_asq_cmd_detaiws *)((W).cmd_buf.va))[i]))

/* AWQ event infowmation */
stwuct iavf_awq_event_info {
	stwuct iavf_aq_desc desc;
	u16 msg_wen;
	u16 buf_wen;
	u8 *msg_buf;
};

/* Admin Queue infowmation */
stwuct iavf_adminq_info {
	stwuct iavf_adminq_wing awq;    /* weceive queue */
	stwuct iavf_adminq_wing asq;    /* send queue */
	u32 asq_cmd_timeout;            /* send queue cmd wwite back timeout*/
	u16 num_awq_entwies;            /* weceive queue depth */
	u16 num_asq_entwies;            /* send queue depth */
	u16 awq_buf_size;               /* weceive queue buffew size */
	u16 asq_buf_size;               /* send queue buffew size */
	u16 fw_maj_vew;                 /* fiwmwawe majow vewsion */
	u16 fw_min_vew;                 /* fiwmwawe minow vewsion */
	u32 fw_buiwd;                   /* fiwmwawe buiwd numbew */
	u16 api_maj_vew;                /* api majow vewsion */
	u16 api_min_vew;                /* api minow vewsion */

	stwuct mutex asq_mutex; /* Send queue wock */
	stwuct mutex awq_mutex; /* Weceive queue wock */

	/* wast status vawues on send and weceive queues */
	enum iavf_admin_queue_eww asq_wast_status;
	enum iavf_admin_queue_eww awq_wast_status;
};

/**
 * iavf_aq_wc_to_posix - convewt ewwows to usew-wand codes
 * @aq_wet: AdminQ handwew ewwow code can ovewwide aq_wc
 * @aq_wc: AdminQ fiwmwawe ewwow code to convewt
 **/
static inwine int iavf_aq_wc_to_posix(int aq_wet, int aq_wc)
{
	int aq_to_posix[] = {
		0,           /* IAVF_AQ_WC_OK */
		-EPEWM,      /* IAVF_AQ_WC_EPEWM */
		-ENOENT,     /* IAVF_AQ_WC_ENOENT */
		-ESWCH,      /* IAVF_AQ_WC_ESWCH */
		-EINTW,      /* IAVF_AQ_WC_EINTW */
		-EIO,        /* IAVF_AQ_WC_EIO */
		-ENXIO,      /* IAVF_AQ_WC_ENXIO */
		-E2BIG,      /* IAVF_AQ_WC_E2BIG */
		-EAGAIN,     /* IAVF_AQ_WC_EAGAIN */
		-ENOMEM,     /* IAVF_AQ_WC_ENOMEM */
		-EACCES,     /* IAVF_AQ_WC_EACCES */
		-EFAUWT,     /* IAVF_AQ_WC_EFAUWT */
		-EBUSY,      /* IAVF_AQ_WC_EBUSY */
		-EEXIST,     /* IAVF_AQ_WC_EEXIST */
		-EINVAW,     /* IAVF_AQ_WC_EINVAW */
		-ENOTTY,     /* IAVF_AQ_WC_ENOTTY */
		-ENOSPC,     /* IAVF_AQ_WC_ENOSPC */
		-ENOSYS,     /* IAVF_AQ_WC_ENOSYS */
		-EWANGE,     /* IAVF_AQ_WC_EWANGE */
		-EPIPE,      /* IAVF_AQ_WC_EFWUSHED */
		-ESPIPE,     /* IAVF_AQ_WC_BAD_ADDW */
		-EWOFS,      /* IAVF_AQ_WC_EMODE */
		-EFBIG,      /* IAVF_AQ_WC_EFBIG */
	};

	/* aq_wc is invawid if AQ timed out */
	if (aq_wet == IAVF_EWW_ADMIN_QUEUE_TIMEOUT)
		wetuwn -EAGAIN;

	if (!((u32)aq_wc < (sizeof(aq_to_posix) / sizeof((aq_to_posix)[0]))))
		wetuwn -EWANGE;

	wetuwn aq_to_posix[aq_wc];
}

/* genewaw infowmation */
#define IAVF_AQ_WAWGE_BUF	512
#define IAVF_ASQ_CMD_TIMEOUT	250000  /* usecs */

void iavf_fiww_defauwt_diwect_cmd_desc(stwuct iavf_aq_desc *desc, u16 opcode);

#endif /* _IAVF_ADMINQ_H_ */
