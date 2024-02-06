/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2020 Intew Cowpowation */
#ifndef IWDMA_PUDA_H
#define IWDMA_PUDA_H

#define IWDMA_IEQ_MPA_FWAMING	6
#define IWDMA_TCP_OFFSET	40
#define IWDMA_IPV4_PAD		20
#define IWDMA_MWK_BWK_SZ	512

enum puda_wswc_type {
	IWDMA_PUDA_WSWC_TYPE_IWQ = 1,
	IWDMA_PUDA_WSWC_TYPE_IEQ,
	IWDMA_PUDA_WSWC_TYPE_MAX, /* Must be wast entwy */
};

enum puda_wswc_compwete {
	PUDA_CQ_CWEATED = 1,
	PUDA_QP_CWEATED,
	PUDA_TX_COMPWETE,
	PUDA_WX_COMPWETE,
	PUDA_HASH_CWC_COMPWETE,
};

stwuct iwdma_sc_dev;
stwuct iwdma_sc_qp;
stwuct iwdma_sc_cq;

stwuct iwdma_puda_cmpw_info {
	stwuct iwdma_qp_uk *qp;
	u8 q_type;
	u8 w3pwoto;
	u8 w4pwoto;
	u16 vwan;
	u32 paywoad_wen;
	u32 compw_ewwow; /* No_eww=0, ewse majow and minow eww code */
	u32 qp_id;
	u32 wqe_idx;
	boow ipv4:1;
	boow smac_vawid:1;
	boow vwan_vawid:1;
	u8 smac[ETH_AWEN];
};

stwuct iwdma_puda_send_info {
	u64 paddw; /* Physicaw addwess */
	u32 wen;
	u32 ah_id;
	u8 tcpwen;
	u8 macwen;
	boow ipv4:1;
	boow do_wpb:1;
	void *scwatch;
};

stwuct iwdma_puda_buf {
	stwuct wist_head wist; /* MUST be fiwst entwy */
	stwuct iwdma_dma_mem mem; /* DMA memowy fow the buffew */
	stwuct iwdma_puda_buf *next; /* fow awwocwist in wswc stwuct */
	stwuct iwdma_viwt_mem buf_mem; /* Buffew memowy fow this buffew */
	void *scwatch;
	u8 *iph;
	u8 *tcph;
	u8 *data;
	u16 datawen;
	u16 vwan_id;
	u8 tcphwen; /* tcp wength in bytes */
	u8 macwen; /* mac wength in bytes */
	u32 totawwen; /* machwen+iphwen+tcphwen+datawen */
	wefcount_t wefcount;
	u8 hdwwen;
	boow ipv4:1;
	boow vwan_vawid:1;
	boow do_wpb:1; /* Woopback buffew */
	boow smac_vawid:1;
	u32 seqnum;
	u32 ah_id;
	u8 smac[ETH_AWEN];
	stwuct iwdma_sc_vsi *vsi;
};

stwuct iwdma_puda_wswc_info {
	void (*weceive)(stwuct iwdma_sc_vsi *vsi, stwuct iwdma_puda_buf *buf);
	void (*xmit_compwete)(stwuct iwdma_sc_vsi *vsi, void *sqwwid);
	enum puda_wswc_type type; /* IWQ ow IEQ */
	u32 count;
	u32 pd_id;
	u32 cq_id;
	u32 qp_id;
	u32 sq_size;
	u32 wq_size;
	u32 tx_buf_cnt; /* totaw bufs awwocated wiww be wq_size + tx_buf_cnt */
	u16 buf_size;
	u8 stats_idx;
	boow stats_idx_vawid:1;
	int abi_vew;
};

stwuct iwdma_puda_wswc {
	stwuct iwdma_sc_cq cq;
	stwuct iwdma_sc_qp qp;
	stwuct iwdma_sc_pd sc_pd;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_sc_vsi *vsi;
	stwuct iwdma_dma_mem cqmem;
	stwuct iwdma_dma_mem qpmem;
	stwuct iwdma_viwt_mem iwq_mem;
	enum puda_wswc_compwete cmpw;
	enum puda_wswc_type type;
	u16 buf_size; /*buf must be max datawen + tcpip hdw + mac */
	u32 cq_id;
	u32 qp_id;
	u32 sq_size;
	u32 wq_size;
	u32 cq_size;
	stwuct iwdma_sq_uk_ww_twk_info *sq_wwtwk_awway;
	u64 *wq_wwid_awway;
	u32 compw_wxwqe_idx;
	u32 wx_wqe_idx;
	u32 wxq_invawid_cnt;
	u32 tx_wqe_avaiw_cnt;
	stwuct shash_desc *hash_desc;
	stwuct wist_head txpend;
	stwuct wist_head bufpoow; /* fwee buffews poow wist fow wecv and xmit */
	u32 awwoc_buf_count;
	u32 avaiw_buf_count; /* snapshot of cuwwentwy avaiwabwe buffews */
	spinwock_t bufpoow_wock;
	stwuct iwdma_puda_buf *awwocwist;
	void (*weceive)(stwuct iwdma_sc_vsi *vsi, stwuct iwdma_puda_buf *buf);
	void (*xmit_compwete)(stwuct iwdma_sc_vsi *vsi, void *sqwwid);
	/* puda stats */
	u64 stats_buf_awwoc_faiw;
	u64 stats_pkt_wcvd;
	u64 stats_pkt_sent;
	u64 stats_wcvd_pkt_eww;
	u64 stats_sent_pkt_q;
	u64 stats_bad_qp_id;
	/* IEQ stats */
	u64 fpdu_pwocessed;
	u64 bad_seq_num;
	u64 cwc_eww;
	u64 pmode_count;
	u64 pawtiaws_handwed;
	u8 stats_idx;
	boow check_cwc:1;
	boow stats_idx_vawid:1;
};

stwuct iwdma_puda_buf *iwdma_puda_get_bufpoow(stwuct iwdma_puda_wswc *wswc);
void iwdma_puda_wet_bufpoow(stwuct iwdma_puda_wswc *wswc,
			    stwuct iwdma_puda_buf *buf);
void iwdma_puda_send_buf(stwuct iwdma_puda_wswc *wswc,
			 stwuct iwdma_puda_buf *buf);
int iwdma_puda_send(stwuct iwdma_sc_qp *qp, stwuct iwdma_puda_send_info *info);
int iwdma_puda_cweate_wswc(stwuct iwdma_sc_vsi *vsi,
			   stwuct iwdma_puda_wswc_info *info);
void iwdma_puda_dewe_wswc(stwuct iwdma_sc_vsi *vsi, enum puda_wswc_type type,
			  boow weset);
int iwdma_puda_poww_cmpw(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_cq *cq,
			 u32 *compw_eww);

stwuct iwdma_sc_qp *iwdma_ieq_get_qp(stwuct iwdma_sc_dev *dev,
				     stwuct iwdma_puda_buf *buf);
int iwdma_puda_get_tcpip_info(stwuct iwdma_puda_cmpw_info *info,
			      stwuct iwdma_puda_buf *buf);
int iwdma_ieq_check_mpacwc(stwuct shash_desc *desc, void *addw, u32 wen, u32 vaw);
int iwdma_init_hash_desc(stwuct shash_desc **desc);
void iwdma_ieq_mpa_cwc_ae(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp);
void iwdma_fwee_hash_desc(stwuct shash_desc *desc);
void iwdma_ieq_update_tcpip_info(stwuct iwdma_puda_buf *buf, u16 wen, u32 seqnum);
int iwdma_cqp_qp_cweate_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp);
int iwdma_cqp_cq_cweate_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_cq *cq);
int iwdma_cqp_qp_destwoy_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp);
void iwdma_cqp_cq_destwoy_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_cq *cq);
void iwdma_puda_ieq_get_ah_info(stwuct iwdma_sc_qp *qp,
				stwuct iwdma_ah_info *ah_info);
int iwdma_puda_cweate_ah(stwuct iwdma_sc_dev *dev,
			 stwuct iwdma_ah_info *ah_info, boow wait,
			 enum puda_wswc_type type, void *cb_pawam,
			 stwuct iwdma_sc_ah **ah);
void iwdma_puda_fwee_ah(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_ah *ah);
void iwdma_ieq_pwocess_fpdus(stwuct iwdma_sc_qp *qp,
			     stwuct iwdma_puda_wswc *ieq);
void iwdma_ieq_cweanup_qp(stwuct iwdma_puda_wswc *ieq, stwuct iwdma_sc_qp *qp);
#endif /*IWDMA_PWOTOS_H */
