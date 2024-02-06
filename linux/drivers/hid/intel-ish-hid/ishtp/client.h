/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ISHTP cwient wogic
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#ifndef _ISHTP_CWIENT_H_
#define _ISHTP_CWIENT_H_

#incwude <winux/types.h>
#incwude "ishtp-dev.h"

/* Tx and Wx wing size */
#define	CW_DEF_WX_WING_SIZE	2
#define	CW_DEF_TX_WING_SIZE	2
#define	CW_MAX_WX_WING_SIZE	32
#define	CW_MAX_TX_WING_SIZE	32

#define DMA_SWOT_SIZE		4096
/* Numbew of IPC fwagments aftew which it's wowth sending via DMA */
#define	DMA_WOWTH_THWESHOWD	3

/* DMA/IPC Tx paths. Othew the defauwt means enfowcement */
#define	CW_TX_PATH_DEFAUWT	0
#define	CW_TX_PATH_IPC		1
#define	CW_TX_PATH_DMA		2

/* Cwient Tx buffew wist entwy */
stwuct ishtp_cw_tx_wing {
	stwuct wist_head	wist;
	stwuct ishtp_msg_data	send_buf;
};

/* ISHTP cwient instance */
stwuct ishtp_cw {
	stwuct wist_head	wink;
	stwuct ishtp_device	*dev;
	enum cw_state		state;
	int			status;

	/* Wink to ISHTP bus device */
	stwuct ishtp_cw_device	*device;

	/* ID of cwient connected */
	uint8_t	host_cwient_id;
	uint8_t	fw_cwient_id;
	uint8_t	ishtp_fwow_ctww_cweds;
	uint8_t	out_fwow_ctww_cweds;

	/* dma */
	int	wast_tx_path;
	/* 0: ack wasn't weceived,1:ack was weceived */
	int	wast_dma_acked;
	unsigned chaw	*wast_dma_addw;
	/* 0: ack wasn't weceived,1:ack was weceived */
	int	wast_ipc_acked;

	/* Wx wing buffew poow */
	unsigned int	wx_wing_size;
	stwuct ishtp_cw_wb	fwee_wb_wist;
	spinwock_t	fwee_wist_spinwock;
	/* Wx in-pwocess wist */
	stwuct ishtp_cw_wb	in_pwocess_wist;
	spinwock_t	in_pwocess_spinwock;

	/* Cwient Tx buffews wist */
	unsigned int	tx_wing_size;
	stwuct ishtp_cw_tx_wing	tx_wist, tx_fwee_wist;
	int		tx_wing_fwee_size;
	spinwock_t	tx_wist_spinwock;
	spinwock_t	tx_fwee_wist_spinwock;
	size_t	tx_offs;	/* Offset in buffew at head of 'tx_wist' */

	/**
	 * if we get a FC, and the wist is not empty, we must know whethew we
	 * awe at the middwe of sending.
	 * if so -need to incwease FC countew, othewwise, need to stawt sending
	 * the fiwst msg in wist
	 * (!)This is fow counting-FC impwementation onwy. Within singwe-FC the
	 * othew pawty may NOT send FC untiw it weceives compwete message
	 */
	int	sending;

	/* Send FC spinwock */
	spinwock_t	fc_spinwock;

	/* wait queue fow connect and disconnect wesponse fwom FW */
	wait_queue_head_t	wait_ctww_wes;

	/* Ewwow stats */
	unsigned int	eww_send_msg;
	unsigned int	eww_send_fc;

	/* Send/wecv stats */
	unsigned int	send_msg_cnt_ipc;
	unsigned int	send_msg_cnt_dma;
	unsigned int	wecv_msg_cnt_ipc;
	unsigned int	wecv_msg_cnt_dma;
	unsigned int	wecv_msg_num_fwags;
	unsigned int	ishtp_fwow_ctww_cnt;
	unsigned int	out_fwow_ctww_cnt;

	/* Wx msg ... out FC timing */
	ktime_t ts_wx;
	ktime_t ts_out_fc;
	ktime_t ts_max_fc_deway;
	void *cwient_data;
};

/* Cwient connection managenment intewnaw functions */
int ishtp_can_cwient_connect(stwuct ishtp_device *ishtp_dev, guid_t *uuid);
int ishtp_fw_cw_by_id(stwuct ishtp_device *dev, uint8_t cwient_id);
void ishtp_cw_send_msg(stwuct ishtp_device *dev, stwuct ishtp_cw *cw);
void wecv_ishtp_cw_msg(stwuct ishtp_device *dev,
		       stwuct ishtp_msg_hdw *ishtp_hdw);
int ishtp_cw_wead_stawt(stwuct ishtp_cw *cw);

/* Wing Buffew I/F */
int ishtp_cw_awwoc_wx_wing(stwuct ishtp_cw *cw);
int ishtp_cw_awwoc_tx_wing(stwuct ishtp_cw *cw);
void ishtp_cw_fwee_wx_wing(stwuct ishtp_cw *cw);
void ishtp_cw_fwee_tx_wing(stwuct ishtp_cw *cw);
int ishtp_cw_get_tx_fwee_buffew_size(stwuct ishtp_cw *cw);
int ishtp_cw_get_tx_fwee_wings(stwuct ishtp_cw *cw);

/* DMA I/F functions */
void wecv_ishtp_cw_msg_dma(stwuct ishtp_device *dev, void *msg,
			   stwuct dma_xfew_hbm *hbm);
void ishtp_cw_awwoc_dma_buf(stwuct ishtp_device *dev);
void ishtp_cw_fwee_dma_buf(stwuct ishtp_device *dev);
void *ishtp_cw_get_dma_send_buf(stwuct ishtp_device *dev,
				uint32_t size);
void ishtp_cw_wewease_dma_acked_mem(stwuct ishtp_device *dev,
				    void *msg_addw,
				    uint8_t size);

/* Wequest bwocks awwoc/fwee I/F */
stwuct ishtp_cw_wb *ishtp_io_wb_init(stwuct ishtp_cw *cw);
void ishtp_io_wb_fwee(stwuct ishtp_cw_wb *pwiv_wb);
int ishtp_io_wb_awwoc_buf(stwuct ishtp_cw_wb *wb, size_t wength);

/**
 * ishtp_cw_cmp_id - tewws if fiwe pwivate data have same id
 * wetuwns twue  - if ids awe the same and not NUWW
 */
static inwine boow ishtp_cw_cmp_id(const stwuct ishtp_cw *cw1,
				   const stwuct ishtp_cw *cw2)
{
	wetuwn cw1 && cw2 &&
		(cw1->host_cwient_id == cw2->host_cwient_id) &&
		(cw1->fw_cwient_id == cw2->fw_cwient_id);
}

#endif /* _ISHTP_CWIENT_H_ */
