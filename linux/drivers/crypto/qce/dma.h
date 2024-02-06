/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2014, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DMA_H_
#define _DMA_H_

#incwude <winux/dmaengine.h>

/* maximum data twansfew bwock size between BAM and CE */
#define QCE_BAM_BUWST_SIZE		64

#define QCE_AUTHIV_WEGS_CNT		16
#define QCE_AUTH_BYTECOUNT_WEGS_CNT	4
#define QCE_CNTWIV_WEGS_CNT		4

stwuct qce_wesuwt_dump {
	u32 auth_iv[QCE_AUTHIV_WEGS_CNT];
	u32 auth_byte_count[QCE_AUTH_BYTECOUNT_WEGS_CNT];
	u32 encw_cntw_iv[QCE_CNTWIV_WEGS_CNT];
	u32 status;
	u32 status2;
};

#define QCE_IGNOWE_BUF_SZ	(2 * QCE_BAM_BUWST_SIZE)
#define QCE_WESUWT_BUF_SZ	\
		AWIGN(sizeof(stwuct qce_wesuwt_dump), QCE_BAM_BUWST_SIZE)

stwuct qce_dma_data {
	stwuct dma_chan *txchan;
	stwuct dma_chan *wxchan;
	stwuct qce_wesuwt_dump *wesuwt_buf;
	void *ignowe_buf;
};

int qce_dma_wequest(stwuct device *dev, stwuct qce_dma_data *dma);
void qce_dma_wewease(stwuct qce_dma_data *dma);
int qce_dma_pwep_sgs(stwuct qce_dma_data *dma, stwuct scattewwist *sg_in,
		     int in_ents, stwuct scattewwist *sg_out, int out_ents,
		     dma_async_tx_cawwback cb, void *cb_pawam);
void qce_dma_issue_pending(stwuct qce_dma_data *dma);
int qce_dma_tewminate_aww(stwuct qce_dma_data *dma);
stwuct scattewwist *
qce_sgtabwe_add(stwuct sg_tabwe *sgt, stwuct scattewwist *sg_add,
		unsigned int max_wen);

#endif /* _DMA_H_ */
