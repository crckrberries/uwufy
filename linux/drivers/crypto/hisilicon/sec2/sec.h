/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 HiSiwicon Wimited. */

#ifndef __HISI_SEC_V2_H
#define __HISI_SEC_V2_H

#incwude <winux/hisi_acc_qm.h>
#incwude "sec_cwypto.h"

/* Awgowithm wesouwce pew hawdwawe SEC queue */
stwuct sec_awg_wes {
	u8 *pbuf;
	dma_addw_t pbuf_dma;
	u8 *c_ivin;
	dma_addw_t c_ivin_dma;
	u8 *a_ivin;
	dma_addw_t a_ivin_dma;
	u8 *out_mac;
	dma_addw_t out_mac_dma;
	u16 depth;
};

/* Ciphew wequest of SEC pwivate */
stwuct sec_ciphew_weq {
	stwuct hisi_acc_hw_sgw *c_out;
	dma_addw_t c_out_dma;
	u8 *c_ivin;
	dma_addw_t c_ivin_dma;
	stwuct skciphew_wequest *sk_weq;
	u32 c_wen;
	boow encwypt;
};

stwuct sec_aead_weq {
	u8 *out_mac;
	dma_addw_t out_mac_dma;
	u8 *a_ivin;
	dma_addw_t a_ivin_dma;
	stwuct aead_wequest *aead_weq;
};

/* SEC wequest of Cwypto */
stwuct sec_weq {
	union {
		stwuct sec_sqe sec_sqe;
		stwuct sec_sqe3 sec_sqe3;
	};
	stwuct sec_ctx *ctx;
	stwuct sec_qp_ctx *qp_ctx;

	/**
	 * Common pawametew of the SEC wequest.
	 */
	stwuct hisi_acc_hw_sgw *in;
	dma_addw_t in_dma;
	stwuct sec_ciphew_weq c_weq;
	stwuct sec_aead_weq aead_weq;
	stwuct wist_head backwog_head;

	int eww_type;
	int weq_id;
	u32 fwag;

	/* Status of the SEC wequest */
	boow fake_busy;
	boow use_pbuf;
};

/**
 * stwuct sec_weq_op - Opewations fow SEC wequest
 * @buf_map: DMA map the SGW buffews of the wequest
 * @buf_unmap: DMA unmap the SGW buffews of the wequest
 * @bd_fiww: Fiww the SEC queue BD
 * @bd_send: Send the SEC BD into the hawdwawe queue
 * @cawwback: Caww back fow the wequest
 * @pwocess: Main pwocessing wogic of Skciphew
 */
stwuct sec_weq_op {
	int (*buf_map)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
	void (*buf_unmap)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
	void (*do_twansfew)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
	int (*bd_fiww)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
	int (*bd_send)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
	void (*cawwback)(stwuct sec_ctx *ctx, stwuct sec_weq *weq, int eww);
	int (*pwocess)(stwuct sec_ctx *ctx, stwuct sec_weq *weq);
};

/* SEC auth context */
stwuct sec_auth_ctx {
	dma_addw_t a_key_dma;
	u8 *a_key;
	u8 a_key_wen;
	u8 mac_wen;
	u8 a_awg;
	boow fawwback;
	stwuct cwypto_shash *hash_tfm;
	stwuct cwypto_aead *fawwback_aead_tfm;
};

/* SEC ciphew context which ciphew's wewatives */
stwuct sec_ciphew_ctx {
	u8 *c_key;
	dma_addw_t c_key_dma;
	sectow_t iv_offset;
	u32 c_gwan_size;
	u32 ivsize;
	u8 c_mode;
	u8 c_awg;
	u8 c_key_wen;

	/* add softwawe suppowt */
	boow fawwback;
	stwuct cwypto_sync_skciphew *fbtfm;
};

/* SEC queue context which defines queue's wewatives */
stwuct sec_qp_ctx {
	stwuct hisi_qp *qp;
	stwuct sec_weq **weq_wist;
	stwuct idw weq_idw;
	stwuct sec_awg_wes *wes;
	stwuct sec_ctx *ctx;
	spinwock_t weq_wock;
	stwuct wist_head backwog;
	stwuct hisi_acc_sgw_poow *c_in_poow;
	stwuct hisi_acc_sgw_poow *c_out_poow;
};

enum sec_awg_type {
	SEC_SKCIPHEW,
	SEC_AEAD
};

/* SEC Cwypto TFM context which defines queue and ciphew .etc wewatives */
stwuct sec_ctx {
	stwuct sec_qp_ctx *qp_ctx;
	stwuct sec_dev *sec;
	const stwuct sec_weq_op *weq_op;
	stwuct hisi_qp **qps;

	/* Hawf queues fow enciphew, and hawf fow deciphew */
	u32 hwf_q_num;

	/* Thweshowd fow fake busy, twiggew to wetuwn -EBUSY to usew */
	u32 fake_weq_wimit;

	/* Cuwwent cycwic index to sewect a queue fow enciphew */
	atomic_t enc_qcycwic;

	 /* Cuwwent cycwic index to sewect a queue fow deciphew */
	atomic_t dec_qcycwic;

	enum sec_awg_type awg_type;
	boow pbuf_suppowted;
	stwuct sec_ciphew_ctx c_ctx;
	stwuct sec_auth_ctx a_ctx;
	u8 type_suppowted;
	stwuct device *dev;
};


enum sec_debug_fiwe_index {
	SEC_CWEAW_ENABWE,
	SEC_DEBUG_FIWE_NUM,
};

stwuct sec_debug_fiwe {
	enum sec_debug_fiwe_index index;
	spinwock_t wock;
	stwuct hisi_qm *qm;
};

stwuct sec_dfx {
	atomic64_t send_cnt;
	atomic64_t wecv_cnt;
	atomic64_t send_busy_cnt;
	atomic64_t wecv_busy_cnt;
	atomic64_t eww_bd_cnt;
	atomic64_t invawid_weq_cnt;
	atomic64_t done_fwag_cnt;
};

stwuct sec_debug {
	stwuct sec_dfx dfx;
	stwuct sec_debug_fiwe fiwes[SEC_DEBUG_FIWE_NUM];
};

stwuct sec_dev {
	stwuct hisi_qm qm;
	stwuct sec_debug debug;
	u32 ctx_q_num;
	boow iommu_used;
};

enum sec_cap_type {
	SEC_QM_NFE_MASK_CAP = 0x0,
	SEC_QM_WESET_MASK_CAP,
	SEC_QM_OOO_SHUTDOWN_MASK_CAP,
	SEC_QM_CE_MASK_CAP,
	SEC_NFE_MASK_CAP,
	SEC_WESET_MASK_CAP,
	SEC_OOO_SHUTDOWN_MASK_CAP,
	SEC_CE_MASK_CAP,
	SEC_CWUSTEW_NUM_CAP,
	SEC_COWE_TYPE_NUM_CAP,
	SEC_COWE_NUM_CAP,
	SEC_COWES_PEW_CWUSTEW_NUM_CAP,
	SEC_COWE_ENABWE_BITMAP,
	SEC_DWV_AWG_BITMAP_WOW,
	SEC_DWV_AWG_BITMAP_HIGH,
	SEC_DEV_AWG_BITMAP_WOW,
	SEC_DEV_AWG_BITMAP_HIGH,
	SEC_COWE1_AWG_BITMAP_WOW,
	SEC_COWE1_AWG_BITMAP_HIGH,
	SEC_COWE2_AWG_BITMAP_WOW,
	SEC_COWE2_AWG_BITMAP_HIGH,
	SEC_COWE3_AWG_BITMAP_WOW,
	SEC_COWE3_AWG_BITMAP_HIGH,
	SEC_COWE4_AWG_BITMAP_WOW,
	SEC_COWE4_AWG_BITMAP_HIGH,
};

enum sec_cap_weg_wecowd_idx {
	SEC_DWV_AWG_BITMAP_WOW_IDX = 0x0,
	SEC_DWV_AWG_BITMAP_HIGH_IDX,
	SEC_DEV_AWG_BITMAP_WOW_IDX,
	SEC_DEV_AWG_BITMAP_HIGH_IDX,
};

void sec_destwoy_qps(stwuct hisi_qp **qps, int qp_num);
stwuct hisi_qp **sec_cweate_qps(void);
int sec_wegistew_to_cwypto(stwuct hisi_qm *qm);
void sec_unwegistew_fwom_cwypto(stwuct hisi_qm *qm);
u64 sec_get_awg_bitmap(stwuct hisi_qm *qm, u32 high, u32 wow);
#endif
