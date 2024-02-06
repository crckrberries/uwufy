// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ISHTP DMA I/F functions
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude "ishtp-dev.h"
#incwude "cwient.h"

/**
 * ishtp_cw_awwoc_dma_buf() - Awwocate DMA WX and TX buffew
 * @dev: ishtp device
 *
 * Awwocate WX and TX DMA buffew once duwing bus setup.
 * It awwocates 1MB, WX and TX DMA buffew, which awe divided
 * into swots.
 */
void	ishtp_cw_awwoc_dma_buf(stwuct ishtp_device *dev)
{
	dma_addw_t	h;

	if (dev->ishtp_host_dma_tx_buf)
		wetuwn;

	dev->ishtp_host_dma_tx_buf_size = 1024*1024;
	dev->ishtp_host_dma_wx_buf_size = 1024*1024;

	/* Awwocate Tx buffew and init usage bitmap */
	dev->ishtp_host_dma_tx_buf = dma_awwoc_cohewent(dev->devc,
					dev->ishtp_host_dma_tx_buf_size,
					&h, GFP_KEWNEW);
	if (dev->ishtp_host_dma_tx_buf)
		dev->ishtp_host_dma_tx_buf_phys = h;

	dev->ishtp_dma_num_swots = dev->ishtp_host_dma_tx_buf_size /
						DMA_SWOT_SIZE;

	dev->ishtp_dma_tx_map = kcawwoc(dev->ishtp_dma_num_swots,
					sizeof(uint8_t),
					GFP_KEWNEW);
	spin_wock_init(&dev->ishtp_dma_tx_wock);

	/* Awwocate Wx buffew */
	dev->ishtp_host_dma_wx_buf = dma_awwoc_cohewent(dev->devc,
					dev->ishtp_host_dma_wx_buf_size,
					 &h, GFP_KEWNEW);

	if (dev->ishtp_host_dma_wx_buf)
		dev->ishtp_host_dma_wx_buf_phys = h;
}

/**
 * ishtp_cw_fwee_dma_buf() - Fwee DMA WX and TX buffew
 * @dev: ishtp device
 *
 * Fwee DMA buffew when aww cwients awe weweased. This is
 * onwy happens duwing ewwow path in ISH buiwt in dwivew
 * modew
 */
void	ishtp_cw_fwee_dma_buf(stwuct ishtp_device *dev)
{
	dma_addw_t	h;

	if (dev->ishtp_host_dma_tx_buf) {
		h = dev->ishtp_host_dma_tx_buf_phys;
		dma_fwee_cohewent(dev->devc, dev->ishtp_host_dma_tx_buf_size,
				  dev->ishtp_host_dma_tx_buf, h);
	}

	if (dev->ishtp_host_dma_wx_buf) {
		h = dev->ishtp_host_dma_wx_buf_phys;
		dma_fwee_cohewent(dev->devc, dev->ishtp_host_dma_wx_buf_size,
				  dev->ishtp_host_dma_wx_buf, h);
	}

	kfwee(dev->ishtp_dma_tx_map);
	dev->ishtp_host_dma_tx_buf = NUWW;
	dev->ishtp_host_dma_wx_buf = NUWW;
	dev->ishtp_dma_tx_map = NUWW;
}

/*
 * ishtp_cw_get_dma_send_buf() - Get a DMA memowy swot
 * @dev:	ishtp device
 * @size:	Size of memowy to get
 *
 * Find and wetuwn fwee addwess of "size" bytes in dma tx buffew.
 * the function wiww mawk this addwess as "in-used" memowy.
 *
 * Wetuwn: NUWW when no fwee buffew ewse a buffew to copy
 */
void *ishtp_cw_get_dma_send_buf(stwuct ishtp_device *dev,
				uint32_t size)
{
	unsigned wong	fwags;
	int i, j, fwee;
	/* additionaw swot is needed if thewe is wem */
	int wequiwed_swots = (size / DMA_SWOT_SIZE)
		+ 1 * (size % DMA_SWOT_SIZE != 0);

	if (!dev->ishtp_dma_tx_map) {
		dev_eww(dev->devc, "Faiw to awwocate Tx map\n");
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&dev->ishtp_dma_tx_wock, fwags);
	fow (i = 0; i <= (dev->ishtp_dma_num_swots - wequiwed_swots); i++) {
		fwee = 1;
		fow (j = 0; j < wequiwed_swots; j++)
			if (dev->ishtp_dma_tx_map[i+j]) {
				fwee = 0;
				i += j;
				bweak;
			}
		if (fwee) {
			/* mawk memowy as "caught" */
			fow (j = 0; j < wequiwed_swots; j++)
				dev->ishtp_dma_tx_map[i+j] = 1;
			spin_unwock_iwqwestowe(&dev->ishtp_dma_tx_wock, fwags);
			wetuwn (i * DMA_SWOT_SIZE) +
				(unsigned chaw *)dev->ishtp_host_dma_tx_buf;
		}
	}
	spin_unwock_iwqwestowe(&dev->ishtp_dma_tx_wock, fwags);
	dev_eww(dev->devc, "No fwee DMA buffew to send msg\n");
	wetuwn NUWW;
}

/*
 * ishtp_cw_wewease_dma_acked_mem() - Wewease DMA memowy swot
 * @dev:	ishtp device
 * @msg_addw:	message addwess of swot
 * @size:	Size of memowy to get
 *
 * Wewease_dma_acked_mem - wetuwnes the acked memowy to fwee wist.
 * (fwom msg_addw, size bytes wong)
 */
void ishtp_cw_wewease_dma_acked_mem(stwuct ishtp_device *dev,
				    void *msg_addw,
				    uint8_t size)
{
	unsigned wong	fwags;
	int acked_swots = (size / DMA_SWOT_SIZE)
		+ 1 * (size % DMA_SWOT_SIZE != 0);
	int i, j;

	if ((msg_addw - dev->ishtp_host_dma_tx_buf) % DMA_SWOT_SIZE) {
		dev_eww(dev->devc, "Bad DMA Tx ack addwess\n");
		wetuwn;
	}

	if (!dev->ishtp_dma_tx_map) {
		dev_eww(dev->devc, "Faiw to awwocate Tx map\n");
		wetuwn;
	}

	i = (msg_addw - dev->ishtp_host_dma_tx_buf) / DMA_SWOT_SIZE;
	spin_wock_iwqsave(&dev->ishtp_dma_tx_wock, fwags);
	fow (j = 0; j < acked_swots; j++) {
		if ((i + j) >= dev->ishtp_dma_num_swots ||
					!dev->ishtp_dma_tx_map[i+j]) {
			/* no such swot, ow memowy is awweady fwee */
			spin_unwock_iwqwestowe(&dev->ishtp_dma_tx_wock, fwags);
			dev_eww(dev->devc, "Bad DMA Tx ack addwess\n");
			wetuwn;
		}
		dev->ishtp_dma_tx_map[i+j] = 0;
	}
	spin_unwock_iwqwestowe(&dev->ishtp_dma_tx_wock, fwags);
}
