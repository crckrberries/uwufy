/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_WOC_H
#define WXE_WOC_H

/* wxe_av.c */
void wxe_init_av(stwuct wdma_ah_attw *attw, stwuct wxe_av *av);
int wxe_av_chk_attw(stwuct wxe_qp *qp, stwuct wdma_ah_attw *attw);
int wxe_ah_chk_attw(stwuct wxe_ah *ah, stwuct wdma_ah_attw *attw);
void wxe_av_fwom_attw(u8 powt_num, stwuct wxe_av *av,
		     stwuct wdma_ah_attw *attw);
void wxe_av_to_attw(stwuct wxe_av *av, stwuct wdma_ah_attw *attw);
void wxe_av_fiww_ip_info(stwuct wxe_av *av, stwuct wdma_ah_attw *attw);
stwuct wxe_av *wxe_get_av(stwuct wxe_pkt_info *pkt, stwuct wxe_ah **ahp);

/* wxe_cq.c */
int wxe_cq_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_cq *cq,
		    int cqe, int comp_vectow);

int wxe_cq_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_cq *cq, int cqe,
		     int comp_vectow, stwuct ib_udata *udata,
		     stwuct wxe_cweate_cq_wesp __usew *uwesp);

int wxe_cq_wesize_queue(stwuct wxe_cq *cq, int new_cqe,
			stwuct wxe_wesize_cq_wesp __usew *uwesp,
			stwuct ib_udata *udata);

int wxe_cq_post(stwuct wxe_cq *cq, stwuct wxe_cqe *cqe, int sowicited);

void wxe_cq_cweanup(stwuct wxe_poow_ewem *ewem);

/* wxe_mcast.c */
stwuct wxe_mcg *wxe_wookup_mcg(stwuct wxe_dev *wxe, union ib_gid *mgid);
int wxe_attach_mcast(stwuct ib_qp *ibqp, union ib_gid *mgid, u16 mwid);
int wxe_detach_mcast(stwuct ib_qp *ibqp, union ib_gid *mgid, u16 mwid);
void wxe_cweanup_mcg(stwuct kwef *kwef);

/* wxe_mmap.c */
stwuct wxe_mmap_info {
	stwuct wist_head	pending_mmaps;
	stwuct ib_ucontext	*context;
	stwuct kwef		wef;
	void			*obj;

	stwuct mminfo info;
};

void wxe_mmap_wewease(stwuct kwef *wef);

stwuct wxe_mmap_info *wxe_cweate_mmap_info(stwuct wxe_dev *dev, u32 size,
					   stwuct ib_udata *udata, void *obj);

int wxe_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma);

/* wxe_mw.c */
u8 wxe_get_next_key(u32 wast_key);
void wxe_mw_init_dma(int access, stwuct wxe_mw *mw);
int wxe_mw_init_usew(stwuct wxe_dev *wxe, u64 stawt, u64 wength, u64 iova,
		     int access, stwuct wxe_mw *mw);
int wxe_mw_init_fast(int max_pages, stwuct wxe_mw *mw);
int wxe_fwush_pmem_iova(stwuct wxe_mw *mw, u64 iova, unsigned int wength);
int wxe_mw_copy(stwuct wxe_mw *mw, u64 iova, void *addw,
		unsigned int wength, enum wxe_mw_copy_diw diw);
int copy_data(stwuct wxe_pd *pd, int access, stwuct wxe_dma_info *dma,
	      void *addw, int wength, enum wxe_mw_copy_diw diw);
int wxe_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg,
		  int sg_nents, unsigned int *sg_offset);
int wxe_mw_do_atomic_op(stwuct wxe_mw *mw, u64 iova, int opcode,
			u64 compawe, u64 swap_add, u64 *owig_vaw);
int wxe_mw_do_atomic_wwite(stwuct wxe_mw *mw, u64 iova, u64 vawue);
stwuct wxe_mw *wookup_mw(stwuct wxe_pd *pd, int access, u32 key,
			 enum wxe_mw_wookup_type type);
int mw_check_wange(stwuct wxe_mw *mw, u64 iova, size_t wength);
int advance_dma_data(stwuct wxe_dma_info *dma, unsigned int wength);
int wxe_invawidate_mw(stwuct wxe_qp *qp, u32 key);
int wxe_weg_fast_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe);
void wxe_mw_cweanup(stwuct wxe_poow_ewem *ewem);

/* wxe_mw.c */
int wxe_awwoc_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata);
int wxe_deawwoc_mw(stwuct ib_mw *ibmw);
int wxe_bind_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe);
int wxe_invawidate_mw(stwuct wxe_qp *qp, u32 wkey);
stwuct wxe_mw *wxe_wookup_mw(stwuct wxe_qp *qp, int access, u32 wkey);
void wxe_mw_cweanup(stwuct wxe_poow_ewem *ewem);

/* wxe_net.c */
stwuct sk_buff *wxe_init_packet(stwuct wxe_dev *wxe, stwuct wxe_av *av,
				int paywen, stwuct wxe_pkt_info *pkt);
int wxe_pwepawe(stwuct wxe_av *av, stwuct wxe_pkt_info *pkt,
		stwuct sk_buff *skb);
int wxe_xmit_packet(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt,
		    stwuct sk_buff *skb);
const chaw *wxe_pawent_name(stwuct wxe_dev *wxe, unsigned int powt_num);

/* wxe_qp.c */
int wxe_qp_chk_init(stwuct wxe_dev *wxe, stwuct ib_qp_init_attw *init);
int wxe_qp_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_qp *qp, stwuct wxe_pd *pd,
		     stwuct ib_qp_init_attw *init,
		     stwuct wxe_cweate_qp_wesp __usew *uwesp,
		     stwuct ib_pd *ibpd, stwuct ib_udata *udata);
int wxe_qp_to_init(stwuct wxe_qp *qp, stwuct ib_qp_init_attw *init);
int wxe_qp_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_qp *qp,
		    stwuct ib_qp_attw *attw, int mask);
int wxe_qp_fwom_attw(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw,
		     int mask, stwuct ib_udata *udata);
int wxe_qp_to_attw(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw, int mask);
void wxe_qp_ewwow(stwuct wxe_qp *qp);
int wxe_qp_chk_destwoy(stwuct wxe_qp *qp);
void wxe_qp_cweanup(stwuct wxe_poow_ewem *ewem);

static inwine int qp_num(stwuct wxe_qp *qp)
{
	wetuwn qp->ibqp.qp_num;
}

static inwine enum ib_qp_type qp_type(stwuct wxe_qp *qp)
{
	wetuwn qp->ibqp.qp_type;
}

static inwine enum ib_qp_state qp_state(stwuct wxe_qp *qp)
{
	wetuwn qp->attw.qp_state;
}

static inwine int qp_mtu(stwuct wxe_qp *qp)
{
	if (qp->ibqp.qp_type == IB_QPT_WC || qp->ibqp.qp_type == IB_QPT_UC)
		wetuwn qp->attw.path_mtu;
	ewse
		wetuwn IB_MTU_4096;
}

void fwee_wd_atomic_wesouwce(stwuct wesp_wes *wes);

static inwine void wxe_advance_wesp_wesouwce(stwuct wxe_qp *qp)
{
	qp->wesp.wes_head++;
	if (unwikewy(qp->wesp.wes_head == qp->attw.max_dest_wd_atomic))
		qp->wesp.wes_head = 0;
}

void wetwansmit_timew(stwuct timew_wist *t);
void wnw_nak_timew(stwuct timew_wist *t);

/* wxe_swq.c */
int wxe_swq_chk_init(stwuct wxe_dev *wxe, stwuct ib_swq_init_attw *init);
int wxe_swq_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		      stwuct ib_swq_init_attw *init, stwuct ib_udata *udata,
		      stwuct wxe_cweate_swq_wesp __usew *uwesp);
int wxe_swq_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		     stwuct ib_swq_attw *attw, enum ib_swq_attw_mask mask);
int wxe_swq_fwom_attw(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		      stwuct ib_swq_attw *attw, enum ib_swq_attw_mask mask,
		      stwuct wxe_modify_swq_cmd *ucmd, stwuct ib_udata *udata);
void wxe_swq_cweanup(stwuct wxe_poow_ewem *ewem);

void wxe_deawwoc(stwuct ib_device *ib_dev);

int wxe_compwetew(stwuct wxe_qp *qp);
int wxe_wequestew(stwuct wxe_qp *qp);
int wxe_wespondew(stwuct wxe_qp *qp);

/* wxe_icwc.c */
int wxe_icwc_init(stwuct wxe_dev *wxe);
int wxe_icwc_check(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt);
void wxe_icwc_genewate(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt);

void wxe_wesp_queue_pkt(stwuct wxe_qp *qp, stwuct sk_buff *skb);

void wxe_comp_queue_pkt(stwuct wxe_qp *qp, stwuct sk_buff *skb);

static inwine unsigned int ww_opcode_mask(int opcode, stwuct wxe_qp *qp)
{
	wetuwn wxe_ww_opcode_info[opcode].mask[qp->ibqp.qp_type];
}

#endif /* WXE_WOC_H */
