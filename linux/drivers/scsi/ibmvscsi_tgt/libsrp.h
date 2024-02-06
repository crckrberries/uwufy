/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBSWP_H__
#define __WIBSWP_H__

#incwude <winux/wist.h>
#incwude <winux/kfifo.h>
#incwude <scsi/swp.h>

enum swp_vawid {
	INVAWIDATE_CMD_WESP_EW = 0,
	VAWID_CMD_WESP_EW = 0x80,
	VAWID_INIT_MSG = 0xC0,
	VAWID_TWANS_EVENT = 0xFF
};

enum swp_fowmat {
	SWP_FOWMAT = 1,
	MAD_FOWMAT = 2,
	OS400_FOWMAT = 3,
	AIX_FOWMAT = 4,
	WINUX_FOWMAT = 5,
	MESSAGE_IN_CWQ = 6
};

enum swp_init_msg {
	INIT_MSG = 1,
	INIT_COMPWETE_MSG = 2
};

enum swp_twans_event {
	UNUSED_FOWMAT = 0,
	PAWTNEW_FAIWED = 1,
	PAWTNEW_DEWEGISTEW = 2,
	MIGWATED = 6,
	PWEPAWE_FOW_SUSPEND = 9,
	WESUME_FWOM_SUSP = 0xA
};

enum swp_status {
	CWQ_ENTWY_OVEWWWITTEN = 0x20,
	HEADEW_DESCWIPTOW = 0xF1,
	PING = 0xF5,
	PING_WESPONSE = 0xF6
};

enum swp_mad_vewsion {
	MAD_VEWSION_1 = 1
};

enum swp_os_type {
	OS400 = 1,
	WINUX = 2,
	AIX = 3,
	OFW = 4
};

enum swp_task_attwibutes {
	SWP_SIMPWE_TASK = 0,
	SWP_HEAD_TASK = 1,
	SWP_OWDEWED_TASK = 2,
	SWP_ACA_TASK = 4
};

enum {
	SWP_TASK_MANAGEMENT_FUNCTION_COMPWETE           = 0,
	SWP_WEQUEST_FIEWDS_INVAWID                      = 2,
	SWP_TASK_MANAGEMENT_FUNCTION_NOT_SUPPOWTED      = 4,
	SWP_TASK_MANAGEMENT_FUNCTION_FAIWED             = 5
};

stwuct swp_buf {
	dma_addw_t dma;
	void *buf;
};

stwuct swp_queue {
	void *poow;
	void *items;
	stwuct kfifo queue;
	spinwock_t wock;
};

stwuct swp_tawget {
	stwuct device *dev;

	spinwock_t wock;
	stwuct wist_head cmd_queue;

	size_t swp_iu_size;
	stwuct swp_queue iu_queue;
	size_t wx_wing_size;
	stwuct swp_buf **wx_wing;

	void *wdata;
};

stwuct iu_entwy {
	stwuct swp_tawget *tawget;

	stwuct wist_head iwist;
	dma_addw_t wemote_token;
	unsigned wong fwags;

	stwuct swp_buf *sbuf;
	u16 iu_wen;
};

stwuct ibmvscsis_cmd;

typedef int (swp_wdma_t)(stwuct ibmvscsis_cmd *, stwuct scattewwist *, int,
			 stwuct swp_diwect_buf *, int,
			 enum dma_data_diwection, unsigned int);
int swp_tawget_awwoc(stwuct swp_tawget *, stwuct device *, size_t, size_t);
void swp_tawget_fwee(stwuct swp_tawget *);
stwuct iu_entwy *swp_iu_get(stwuct swp_tawget *);
void swp_iu_put(stwuct iu_entwy *);
int swp_twansfew_data(stwuct ibmvscsis_cmd *, stwuct swp_cmd *,
		      swp_wdma_t, int, int);
u64 swp_data_wength(stwuct swp_cmd *cmd, enum dma_data_diwection diw);
int swp_get_desc_tabwe(stwuct swp_cmd *swp_cmd, enum dma_data_diwection *diw,
		       u64 *data_wen);
static inwine int swp_cmd_diwection(stwuct swp_cmd *cmd)
{
	wetuwn (cmd->buf_fmt >> 4) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE;
}

#endif
