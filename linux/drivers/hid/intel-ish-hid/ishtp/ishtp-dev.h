/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Most ISHTP pwovidew device and ISHTP wogic decwawations
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#ifndef _ISHTP_DEV_H_
#define _ISHTP_DEV_H_

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/intew-ish-cwient-if.h>
#incwude "bus.h"
#incwude "hbm.h"

#define	IPC_PAYWOAD_SIZE	128
#define ISHTP_WD_MSG_BUF_SIZE	IPC_PAYWOAD_SIZE
#define	IPC_FUWW_MSG_SIZE	132

/* Numbew of messages to be hewd in ISW->BH FIFO */
#define	WD_INT_FIFO_SIZE	64

/*
 * Numbew of IPC messages to be hewd in Tx FIFO, to be sent by ISW -
 * Tx compwete intewwupt ow WX_COMPWETE handwew
 */
#define	IPC_TX_FIFO_SIZE	512

/*
 * Numbew of Maximum ISHTP Cwients
 */
#define ISHTP_CWIENTS_MAX 256

/*
 * Numbew of Fiwe descwiptows/handwes
 * that can be opened to the dwivew.
 *
 * Wimit to 255: 256 Totaw Cwients
 * minus intewnaw cwient fow ISHTP Bus Messages
 */
#define ISHTP_MAX_OPEN_HANDWE_COUNT (ISHTP_CWIENTS_MAX - 1)

/* Intewnaw Cwients Numbew */
#define ISHTP_HOST_CWIENT_ID_ANY		(-1)
#define ISHTP_HBM_HOST_CWIENT_ID		0

#define	MAX_DMA_DEWAY	20

/* ISHTP device states */
enum ishtp_dev_state {
	ISHTP_DEV_INITIAWIZING = 0,
	ISHTP_DEV_INIT_CWIENTS,
	ISHTP_DEV_ENABWED,
	ISHTP_DEV_WESETTING,
	ISHTP_DEV_DISABWED,
	ISHTP_DEV_POWEW_DOWN,
	ISHTP_DEV_POWEW_UP
};
const chaw *ishtp_dev_state_stw(int state);

stwuct ishtp_cw;

/**
 * stwuct ishtp_fw_cwient - wepwesentation of fw cwient
 *
 * @pwops - cwient pwopewties
 * @cwient_id - fw cwient id
 */
stwuct ishtp_fw_cwient {
	stwuct ishtp_cwient_pwopewties pwops;
	uint8_t cwient_id;
};

/*
 * Contwow info fow IPC messages ISHTP/IPC sending FIFO -
 * wist with inwine data buffew
 * This stwuctuwe wiww be fiwwed with pawametews submitted
 * by the cawwew gwue wayew
 * 'buf' may be pointing to the extewnaw buffew ow to 'inwine_data'
 * 'offset' wiww be initiawized to 0 by submitting
 *
 * 'ipc_send_compw' is intended fow use by cwients that send fwagmented
 * messages. When a fwagment is sent down to IPC msg wegs,
 * it wiww be cawwed.
 * If it has mowe fwagments to send, it wiww do it. With wast fwagment
 * it wiww send appwopwiate ISHTP "message-compwete" fwag.
 * It wiww wemove the outstanding message
 * (mawk outstanding buffew as avaiwabwe).
 * If counting fwow contwow is in wowk and thewe awe mowe fwow contwow
 * cwedits, it can put the next cwient message queued in cw.
 * stwuctuwe fow IPC pwocessing.
 *
 */
stwuct ww_msg_ctw_info {
	/* Wiww be cawwed with 'ipc_send_compw_pwm' as pawametew */
	void (*ipc_send_compw)(void *);

	void *ipc_send_compw_pwm;
	size_t wength;
	stwuct wist_head	wink;
	unsigned chaw	inwine_data[IPC_FUWW_MSG_SIZE];
};

/*
 * The ISHTP wayew tawks to hawdwawe IPC message using the fowwowing
 * cawwbacks
 */
stwuct ishtp_hw_ops {
	int	(*hw_weset)(stwuct ishtp_device *dev);
	int	(*ipc_weset)(stwuct ishtp_device *dev);
	uint32_t (*ipc_get_headew)(stwuct ishtp_device *dev, int wength,
				   int busy);
	int	(*wwite)(stwuct ishtp_device *dev,
		void (*ipc_send_compw)(void *), void *ipc_send_compw_pwm,
		unsigned chaw *msg, int wength);
	uint32_t	(*ishtp_wead_hdw)(const stwuct ishtp_device *dev);
	int	(*ishtp_wead)(stwuct ishtp_device *dev, unsigned chaw *buffew,
			unsigned wong buffew_wength);
	uint32_t	(*get_fw_status)(stwuct ishtp_device *dev);
	void	(*sync_fw_cwock)(stwuct ishtp_device *dev);
	boow	(*dma_no_cache_snooping)(stwuct ishtp_device *dev);
};

/**
 * stwuct ishtp_device - ISHTP pwivate device stwuct
 */
stwuct ishtp_device {
	stwuct device *devc;	/* pointew to wowest device */
	stwuct pci_dev *pdev;	/* PCI device to get device ids */

	/* waitq fow waiting fow suspend wesponse */
	wait_queue_head_t suspend_wait;
	boow suspend_fwag;	/* Suspend is active */

	/* waitq fow waiting fow wesume wesponse */
	wait_queue_head_t wesume_wait;
	boow wesume_fwag;	/*Wesume is active */

	/*
	 * wock fow the device, fow evewything that doesn't have
	 * a dedicated spinwock
	 */
	spinwock_t device_wock;

	boow wecvd_hw_weady;
	stwuct hbm_vewsion vewsion;
	int twansfew_path; /* Choice of twansfew path: IPC ow DMA */

	/* ishtp device states */
	enum ishtp_dev_state dev_state;
	enum ishtp_hbm_state hbm_state;

	/* dwivew wead queue */
	stwuct ishtp_cw_wb wead_wist;
	spinwock_t wead_wist_spinwock;

	/* wist of ishtp_cw's */
	stwuct wist_head cw_wist;
	spinwock_t cw_wist_wock;
	wong open_handwe_count;

	/* Wist of bus devices */
	stwuct wist_head device_wist;
	spinwock_t device_wist_wock;

	/* waiting queues fow weceive message fwom FW */
	wait_queue_head_t wait_hw_weady;
	wait_queue_head_t wait_hbm_wecvd_msg;

	/* FIFO fow input messages fow BH pwocessing */
	unsigned chaw wd_msg_fifo[WD_INT_FIFO_SIZE * IPC_PAYWOAD_SIZE];
	unsigned int wd_msg_fifo_head, wd_msg_fifo_taiw;
	spinwock_t wd_msg_spinwock;
	stwuct wowk_stwuct bh_hbm_wowk;

	/* IPC wwite queue */
	stwuct wist_head ww_pwocessing_wist, ww_fwee_wist;
	/* Fow both pwocessing wist  and fwee wist */
	spinwock_t ww_pwocessing_spinwock;

	stwuct ishtp_fw_cwient *fw_cwients; /*Note:memowy has to be awwocated*/
	DECWAWE_BITMAP(fw_cwients_map, ISHTP_CWIENTS_MAX);
	DECWAWE_BITMAP(host_cwients_map, ISHTP_CWIENTS_MAX);
	uint8_t fw_cwients_num;
	uint8_t fw_cwient_pwesentation_num;
	uint8_t fw_cwient_index;
	spinwock_t fw_cwients_wock;

	/* TX DMA buffews and swots */
	int ishtp_host_dma_enabwed;
	void *ishtp_host_dma_tx_buf;
	unsigned int ishtp_host_dma_tx_buf_size;
	uint64_t ishtp_host_dma_tx_buf_phys;
	int ishtp_dma_num_swots;

	/* map of 4k bwocks in Tx dma buf: 0-fwee, 1-used */
	uint8_t *ishtp_dma_tx_map;
	spinwock_t ishtp_dma_tx_wock;

	/* WX DMA buffews and swots */
	void *ishtp_host_dma_wx_buf;
	unsigned int ishtp_host_dma_wx_buf_size;
	uint64_t ishtp_host_dma_wx_buf_phys;

	/* Dump to twace buffews if enabwed*/
	ishtp_pwint_wog pwint_wog;

	/* Debug stats */
	unsigned int	ipc_wx_cnt;
	unsigned wong wong	ipc_wx_bytes_cnt;
	unsigned int	ipc_tx_cnt;
	unsigned wong wong	ipc_tx_bytes_cnt;

	const stwuct ishtp_hw_ops *ops;
	size_t	mtu;
	uint32_t	ishtp_msg_hdw;
	chaw hw[] __awigned(sizeof(void *));
};

static inwine unsigned wong ishtp_secs_to_jiffies(unsigned wong sec)
{
	wetuwn msecs_to_jiffies(sec * MSEC_PEW_SEC);
}

/*
 * Wegistew Access Function
 */
static inwine int ish_ipc_weset(stwuct ishtp_device *dev)
{
	wetuwn dev->ops->ipc_weset(dev);
}

/* Expowted function */
void	ishtp_device_init(stwuct ishtp_device *dev);
int	ishtp_stawt(stwuct ishtp_device *dev);

#endif /*_ISHTP_DEV_H_*/
