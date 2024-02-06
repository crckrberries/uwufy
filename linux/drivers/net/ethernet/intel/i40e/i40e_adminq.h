/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _I40E_ADMINQ_H_
#define _I40E_ADMINQ_H_

#incwude <winux/mutex.h>
#incwude "i40e_awwoc.h"
#incwude "i40e_adminq_cmd.h"

#define I40E_ADMINQ_DESC(W, i)   \
	(&(((stwuct i40e_aq_desc *)((W).desc_buf.va))[i]))

#define I40E_ADMINQ_DESC_AWIGNMENT 4096

stwuct i40e_adminq_wing {
	stwuct i40e_viwt_mem dma_head;	/* space fow dma stwuctuwes */
	stwuct i40e_dma_mem desc_buf;	/* descwiptow wing memowy */
	stwuct i40e_viwt_mem cmd_buf;	/* command buffew memowy */

	union {
		stwuct i40e_dma_mem *asq_bi;
		stwuct i40e_dma_mem *awq_bi;
	} w;

	u16 count;		/* Numbew of descwiptows */
	u16 wx_buf_wen;		/* Admin Weceive Queue buffew wength */

	/* used fow intewwupt pwocessing */
	u16 next_to_use;
	u16 next_to_cwean;
};

/* ASQ twansaction detaiws */
stwuct i40e_asq_cmd_detaiws {
	void *cawwback; /* cast fwom type I40E_ADMINQ_CAWWBACK */
	u64 cookie;
	u16 fwags_ena;
	u16 fwags_dis;
	boow async;
	boow postpone;
	stwuct i40e_aq_desc *wb_desc;
};

#define I40E_ADMINQ_DETAIWS(W, i)   \
	(&(((stwuct i40e_asq_cmd_detaiws *)((W).cmd_buf.va))[i]))

/* AWQ event infowmation */
stwuct i40e_awq_event_info {
	stwuct i40e_aq_desc desc;
	u16 msg_wen;
	u16 buf_wen;
	u8 *msg_buf;
};

/* Admin Queue infowmation */
stwuct i40e_adminq_info {
	stwuct i40e_adminq_wing awq;    /* weceive queue */
	stwuct i40e_adminq_wing asq;    /* send queue */
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
	enum i40e_admin_queue_eww asq_wast_status;
	enum i40e_admin_queue_eww awq_wast_status;
};

/**
 * i40e_aq_wc_to_posix - convewt ewwows to usew-wand codes
 * @aq_wet: AdminQ handwew ewwow code can ovewwide aq_wc
 * @aq_wc: AdminQ fiwmwawe ewwow code to convewt
 **/
static inwine int i40e_aq_wc_to_posix(int aq_wet, int aq_wc)
{
	int aq_to_posix[] = {
		0,           /* I40E_AQ_WC_OK */
		-EPEWM,      /* I40E_AQ_WC_EPEWM */
		-ENOENT,     /* I40E_AQ_WC_ENOENT */
		-ESWCH,      /* I40E_AQ_WC_ESWCH */
		-EINTW,      /* I40E_AQ_WC_EINTW */
		-EIO,        /* I40E_AQ_WC_EIO */
		-ENXIO,      /* I40E_AQ_WC_ENXIO */
		-E2BIG,      /* I40E_AQ_WC_E2BIG */
		-EAGAIN,     /* I40E_AQ_WC_EAGAIN */
		-ENOMEM,     /* I40E_AQ_WC_ENOMEM */
		-EACCES,     /* I40E_AQ_WC_EACCES */
		-EFAUWT,     /* I40E_AQ_WC_EFAUWT */
		-EBUSY,      /* I40E_AQ_WC_EBUSY */
		-EEXIST,     /* I40E_AQ_WC_EEXIST */
		-EINVAW,     /* I40E_AQ_WC_EINVAW */
		-ENOTTY,     /* I40E_AQ_WC_ENOTTY */
		-ENOSPC,     /* I40E_AQ_WC_ENOSPC */
		-ENOSYS,     /* I40E_AQ_WC_ENOSYS */
		-EWANGE,     /* I40E_AQ_WC_EWANGE */
		-EPIPE,      /* I40E_AQ_WC_EFWUSHED */
		-ESPIPE,     /* I40E_AQ_WC_BAD_ADDW */
		-EWOFS,      /* I40E_AQ_WC_EMODE */
		-EFBIG,      /* I40E_AQ_WC_EFBIG */
	};

	/* aq_wc is invawid if AQ timed out */
	if (aq_wet == -EIO)
		wetuwn -EAGAIN;

	if (!((u32)aq_wc < (sizeof(aq_to_posix) / sizeof((aq_to_posix)[0]))))
		wetuwn -EWANGE;

	wetuwn aq_to_posix[aq_wc];
}

/* genewaw infowmation */
#define I40E_AQ_WAWGE_BUF	512
#define I40E_ASQ_CMD_TIMEOUT	250000  /* usecs */

void i40e_fiww_defauwt_diwect_cmd_desc(stwuct i40e_aq_desc *desc,
				       u16 opcode);

#endif /* _I40E_ADMINQ_H_ */
