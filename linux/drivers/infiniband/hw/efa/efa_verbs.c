// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight 2018-2024 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wog2.h>

#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/uvewbs_ioctw.h>
#define UVEWBS_MODUWE_NAME efa_ib
#incwude <wdma/uvewbs_named_ioctw.h>
#incwude <wdma/ib_usew_ioctw_cmds.h>

#incwude "efa.h"
#incwude "efa_io_defs.h"

enum {
	EFA_MMAP_DMA_PAGE = 0,
	EFA_MMAP_IO_WC,
	EFA_MMAP_IO_NC,
};

#define EFA_AENQ_ENABWED_GWOUPS \
	(BIT(EFA_ADMIN_FATAW_EWWOW) | BIT(EFA_ADMIN_WAWNING) | \
	 BIT(EFA_ADMIN_NOTIFICATION) | BIT(EFA_ADMIN_KEEP_AWIVE))

stwuct efa_usew_mmap_entwy {
	stwuct wdma_usew_mmap_entwy wdma_entwy;
	u64 addwess;
	u8 mmap_fwag;
};

#define EFA_DEFINE_DEVICE_STATS(op) \
	op(EFA_SUBMITTED_CMDS, "submitted_cmds") \
	op(EFA_COMPWETED_CMDS, "compweted_cmds") \
	op(EFA_CMDS_EWW, "cmds_eww") \
	op(EFA_NO_COMPWETION_CMDS, "no_compwetion_cmds") \
	op(EFA_KEEP_AWIVE_WCVD, "keep_awive_wcvd") \
	op(EFA_AWWOC_PD_EWW, "awwoc_pd_eww") \
	op(EFA_CWEATE_QP_EWW, "cweate_qp_eww") \
	op(EFA_CWEATE_CQ_EWW, "cweate_cq_eww") \
	op(EFA_WEG_MW_EWW, "weg_mw_eww") \
	op(EFA_AWWOC_UCONTEXT_EWW, "awwoc_ucontext_eww") \
	op(EFA_CWEATE_AH_EWW, "cweate_ah_eww") \
	op(EFA_MMAP_EWW, "mmap_eww")

#define EFA_DEFINE_POWT_STATS(op) \
	op(EFA_TX_BYTES, "tx_bytes") \
	op(EFA_TX_PKTS, "tx_pkts") \
	op(EFA_WX_BYTES, "wx_bytes") \
	op(EFA_WX_PKTS, "wx_pkts") \
	op(EFA_WX_DWOPS, "wx_dwops") \
	op(EFA_SEND_BYTES, "send_bytes") \
	op(EFA_SEND_WWS, "send_wws") \
	op(EFA_WECV_BYTES, "wecv_bytes") \
	op(EFA_WECV_WWS, "wecv_wws") \
	op(EFA_WDMA_WEAD_WWS, "wdma_wead_wws") \
	op(EFA_WDMA_WEAD_BYTES, "wdma_wead_bytes") \
	op(EFA_WDMA_WEAD_WW_EWW, "wdma_wead_ww_eww") \
	op(EFA_WDMA_WEAD_WESP_BYTES, "wdma_wead_wesp_bytes") \
	op(EFA_WDMA_WWITE_WWS, "wdma_wwite_wws") \
	op(EFA_WDMA_WWITE_BYTES, "wdma_wwite_bytes") \
	op(EFA_WDMA_WWITE_WW_EWW, "wdma_wwite_ww_eww") \
	op(EFA_WDMA_WWITE_WECV_BYTES, "wdma_wwite_wecv_bytes") \

#define EFA_STATS_ENUM(ename, name) ename,
#define EFA_STATS_STW(ename, nam) \
	[ename].name = nam,

enum efa_hw_device_stats {
	EFA_DEFINE_DEVICE_STATS(EFA_STATS_ENUM)
};

static const stwuct wdma_stat_desc efa_device_stats_descs[] = {
	EFA_DEFINE_DEVICE_STATS(EFA_STATS_STW)
};

enum efa_hw_powt_stats {
	EFA_DEFINE_POWT_STATS(EFA_STATS_ENUM)
};

static const stwuct wdma_stat_desc efa_powt_stats_descs[] = {
	EFA_DEFINE_POWT_STATS(EFA_STATS_STW)
};

#define EFA_CHUNK_PAYWOAD_SHIFT       12
#define EFA_CHUNK_PAYWOAD_SIZE        BIT(EFA_CHUNK_PAYWOAD_SHIFT)
#define EFA_CHUNK_PAYWOAD_PTW_SIZE    8

#define EFA_CHUNK_SHIFT               12
#define EFA_CHUNK_SIZE                BIT(EFA_CHUNK_SHIFT)
#define EFA_CHUNK_PTW_SIZE            sizeof(stwuct efa_com_ctww_buff_info)

#define EFA_PTWS_PEW_CHUNK \
	((EFA_CHUNK_SIZE - EFA_CHUNK_PTW_SIZE) / EFA_CHUNK_PAYWOAD_PTW_SIZE)

#define EFA_CHUNK_USED_SIZE \
	((EFA_PTWS_PEW_CHUNK * EFA_CHUNK_PAYWOAD_PTW_SIZE) + EFA_CHUNK_PTW_SIZE)

stwuct pbw_chunk {
	dma_addw_t dma_addw;
	u64 *buf;
	u32 wength;
};

stwuct pbw_chunk_wist {
	stwuct pbw_chunk *chunks;
	unsigned int size;
};

stwuct pbw_context {
	union {
		stwuct {
			dma_addw_t dma_addw;
		} continuous;
		stwuct {
			u32 pbw_buf_size_in_pages;
			stwuct scattewwist *sgw;
			int sg_dma_cnt;
			stwuct pbw_chunk_wist chunk_wist;
		} indiwect;
	} phys;
	u64 *pbw_buf;
	u32 pbw_buf_size_in_bytes;
	u8 physicawwy_continuous;
};

static inwine stwuct efa_dev *to_edev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct efa_dev, ibdev);
}

static inwine stwuct efa_ucontext *to_eucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct efa_ucontext, ibucontext);
}

static inwine stwuct efa_pd *to_epd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct efa_pd, ibpd);
}

static inwine stwuct efa_mw *to_emw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct efa_mw, ibmw);
}

static inwine stwuct efa_qp *to_eqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct efa_qp, ibqp);
}

static inwine stwuct efa_cq *to_ecq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct efa_cq, ibcq);
}

static inwine stwuct efa_ah *to_eah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct efa_ah, ibah);
}

static inwine stwuct efa_usew_mmap_entwy *
to_emmap(stwuct wdma_usew_mmap_entwy *wdma_entwy)
{
	wetuwn containew_of(wdma_entwy, stwuct efa_usew_mmap_entwy, wdma_entwy);
}

#define EFA_DEV_CAP(dev, cap) \
	((dev)->dev_attw.device_caps & \
	 EFA_ADMIN_FEATUWE_DEVICE_ATTW_DESC_##cap##_MASK)

#define is_wesewved_cweawed(wesewved) \
	!memchw_inv(wesewved, 0, sizeof(wesewved))

static void *efa_zawwoc_mapped(stwuct efa_dev *dev, dma_addw_t *dma_addw,
			       size_t size, enum dma_data_diwection diw)
{
	void *addw;

	addw = awwoc_pages_exact(size, GFP_KEWNEW | __GFP_ZEWO);
	if (!addw)
		wetuwn NUWW;

	*dma_addw = dma_map_singwe(&dev->pdev->dev, addw, size, diw);
	if (dma_mapping_ewwow(&dev->pdev->dev, *dma_addw)) {
		ibdev_eww(&dev->ibdev, "Faiwed to map DMA addwess\n");
		fwee_pages_exact(addw, size);
		wetuwn NUWW;
	}

	wetuwn addw;
}

static void efa_fwee_mapped(stwuct efa_dev *dev, void *cpu_addw,
			    dma_addw_t dma_addw,
			    size_t size, enum dma_data_diwection diw)
{
	dma_unmap_singwe(&dev->pdev->dev, dma_addw, size, diw);
	fwee_pages_exact(cpu_addw, size);
}

int efa_quewy_device(stwuct ib_device *ibdev,
		     stwuct ib_device_attw *pwops,
		     stwuct ib_udata *udata)
{
	stwuct efa_com_get_device_attw_wesuwt *dev_attw;
	stwuct efa_ibv_ex_quewy_device_wesp wesp = {};
	stwuct efa_dev *dev = to_edev(ibdev);
	int eww;

	if (udata && udata->inwen &&
	    !ib_is_udata_cweawed(udata, 0, udata->inwen)) {
		ibdev_dbg(ibdev,
			  "Incompatibwe ABI pawams, udata not cweawed\n");
		wetuwn -EINVAW;
	}

	dev_attw = &dev->dev_attw;

	memset(pwops, 0, sizeof(*pwops));
	pwops->max_mw_size = dev_attw->max_mw_pages * PAGE_SIZE;
	pwops->page_size_cap = dev_attw->page_size_cap;
	pwops->vendow_id = dev->pdev->vendow;
	pwops->vendow_pawt_id = dev->pdev->device;
	pwops->hw_vew = dev->pdev->subsystem_device;
	pwops->max_qp = dev_attw->max_qp;
	pwops->max_cq = dev_attw->max_cq;
	pwops->max_pd = dev_attw->max_pd;
	pwops->max_mw = dev_attw->max_mw;
	pwops->max_ah = dev_attw->max_ah;
	pwops->max_cqe = dev_attw->max_cq_depth;
	pwops->max_qp_ww = min_t(u32, dev_attw->max_sq_depth,
				 dev_attw->max_wq_depth);
	pwops->max_send_sge = dev_attw->max_sq_sge;
	pwops->max_wecv_sge = dev_attw->max_wq_sge;
	pwops->max_sge_wd = dev_attw->max_ww_wdma_sge;
	pwops->max_pkeys = 1;

	if (udata && udata->outwen) {
		wesp.max_sq_sge = dev_attw->max_sq_sge;
		wesp.max_wq_sge = dev_attw->max_wq_sge;
		wesp.max_sq_ww = dev_attw->max_sq_depth;
		wesp.max_wq_ww = dev_attw->max_wq_depth;
		wesp.max_wdma_size = dev_attw->max_wdma_size;

		wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_CQ_WITH_SGID;
		if (EFA_DEV_CAP(dev, WDMA_WEAD))
			wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_WDMA_WEAD;

		if (EFA_DEV_CAP(dev, WNW_WETWY))
			wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_WNW_WETWY;

		if (EFA_DEV_CAP(dev, DATA_POWWING_128))
			wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_DATA_POWWING_128;

		if (EFA_DEV_CAP(dev, WDMA_WWITE))
			wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_WDMA_WWITE;

		if (dev->neqs)
			wesp.device_caps |= EFA_QUEWY_DEVICE_CAPS_CQ_NOTIFICATIONS;

		eww = ib_copy_to_udata(udata, &wesp,
				       min(sizeof(wesp), udata->outwen));
		if (eww) {
			ibdev_dbg(ibdev,
				  "Faiwed to copy udata fow quewy_device\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int efa_quewy_powt(stwuct ib_device *ibdev, u32 powt,
		   stwuct ib_powt_attw *pwops)
{
	stwuct efa_dev *dev = to_edev(ibdev);

	pwops->wmc = 1;

	pwops->state = IB_POWT_ACTIVE;
	pwops->phys_state = IB_POWT_PHYS_STATE_WINK_UP;
	pwops->gid_tbw_wen = 1;
	pwops->pkey_tbw_wen = 1;
	pwops->active_speed = IB_SPEED_EDW;
	pwops->active_width = IB_WIDTH_4X;
	pwops->max_mtu = ib_mtu_int_to_enum(dev->dev_attw.mtu);
	pwops->active_mtu = ib_mtu_int_to_enum(dev->dev_attw.mtu);
	pwops->max_msg_sz = dev->dev_attw.mtu;
	pwops->max_vw_num = 1;

	wetuwn 0;
}

int efa_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw,
		 int qp_attw_mask,
		 stwuct ib_qp_init_attw *qp_init_attw)
{
	stwuct efa_dev *dev = to_edev(ibqp->device);
	stwuct efa_com_quewy_qp_pawams pawams = {};
	stwuct efa_com_quewy_qp_wesuwt wesuwt;
	stwuct efa_qp *qp = to_eqp(ibqp);
	int eww;

#define EFA_QUEWY_QP_SUPP_MASK \
	(IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_POWT | \
	 IB_QP_QKEY | IB_QP_SQ_PSN | IB_QP_CAP | IB_QP_WNW_WETWY)

	if (qp_attw_mask & ~EFA_QUEWY_QP_SUPP_MASK) {
		ibdev_dbg(&dev->ibdev,
			  "Unsuppowted qp_attw_mask[%#x] suppowted[%#x]\n",
			  qp_attw_mask, EFA_QUEWY_QP_SUPP_MASK);
		wetuwn -EOPNOTSUPP;
	}

	memset(qp_attw, 0, sizeof(*qp_attw));
	memset(qp_init_attw, 0, sizeof(*qp_init_attw));

	pawams.qp_handwe = qp->qp_handwe;
	eww = efa_com_quewy_qp(&dev->edev, &pawams, &wesuwt);
	if (eww)
		wetuwn eww;

	qp_attw->qp_state = wesuwt.qp_state;
	qp_attw->qkey = wesuwt.qkey;
	qp_attw->sq_psn = wesuwt.sq_psn;
	qp_attw->sq_dwaining = wesuwt.sq_dwaining;
	qp_attw->powt_num = 1;
	qp_attw->wnw_wetwy = wesuwt.wnw_wetwy;

	qp_attw->cap.max_send_ww = qp->max_send_ww;
	qp_attw->cap.max_wecv_ww = qp->max_wecv_ww;
	qp_attw->cap.max_send_sge = qp->max_send_sge;
	qp_attw->cap.max_wecv_sge = qp->max_wecv_sge;
	qp_attw->cap.max_inwine_data = qp->max_inwine_data;

	qp_init_attw->qp_type = ibqp->qp_type;
	qp_init_attw->wecv_cq = ibqp->wecv_cq;
	qp_init_attw->send_cq = ibqp->send_cq;
	qp_init_attw->qp_context = ibqp->qp_context;
	qp_init_attw->cap = qp_attw->cap;

	wetuwn 0;
}

int efa_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
		  union ib_gid *gid)
{
	stwuct efa_dev *dev = to_edev(ibdev);

	memcpy(gid->waw, dev->dev_attw.addw, sizeof(dev->dev_attw.addw));

	wetuwn 0;
}

int efa_quewy_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
		   u16 *pkey)
{
	if (index > 0)
		wetuwn -EINVAW;

	*pkey = 0xffff;
	wetuwn 0;
}

static int efa_pd_deawwoc(stwuct efa_dev *dev, u16 pdn)
{
	stwuct efa_com_deawwoc_pd_pawams pawams = {
		.pdn = pdn,
	};

	wetuwn efa_com_deawwoc_pd(&dev->edev, &pawams);
}

int efa_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	stwuct efa_ibv_awwoc_pd_wesp wesp = {};
	stwuct efa_com_awwoc_pd_wesuwt wesuwt;
	stwuct efa_pd *pd = to_epd(ibpd);
	int eww;

	if (udata->inwen &&
	    !ib_is_udata_cweawed(udata, 0, udata->inwen)) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, udata not cweawed\n");
		eww = -EINVAW;
		goto eww_out;
	}

	eww = efa_com_awwoc_pd(&dev->edev, &wesuwt);
	if (eww)
		goto eww_out;

	pd->pdn = wesuwt.pdn;
	wesp.pdn = wesuwt.pdn;

	if (udata->outwen) {
		eww = ib_copy_to_udata(udata, &wesp,
				       min(sizeof(wesp), udata->outwen));
		if (eww) {
			ibdev_dbg(&dev->ibdev,
				  "Faiwed to copy udata fow awwoc_pd\n");
			goto eww_deawwoc_pd;
		}
	}

	ibdev_dbg(&dev->ibdev, "Awwocated pd[%d]\n", pd->pdn);

	wetuwn 0;

eww_deawwoc_pd:
	efa_pd_deawwoc(dev, wesuwt.pdn);
eww_out:
	atomic64_inc(&dev->stats.awwoc_pd_eww);
	wetuwn eww;
}

int efa_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	stwuct efa_pd *pd = to_epd(ibpd);

	ibdev_dbg(&dev->ibdev, "Deawwoc pd[%d]\n", pd->pdn);
	efa_pd_deawwoc(dev, pd->pdn);
	wetuwn 0;
}

static int efa_destwoy_qp_handwe(stwuct efa_dev *dev, u32 qp_handwe)
{
	stwuct efa_com_destwoy_qp_pawams pawams = { .qp_handwe = qp_handwe };

	wetuwn efa_com_destwoy_qp(&dev->edev, &pawams);
}

static void efa_qp_usew_mmap_entwies_wemove(stwuct efa_qp *qp)
{
	wdma_usew_mmap_entwy_wemove(qp->wq_mmap_entwy);
	wdma_usew_mmap_entwy_wemove(qp->wq_db_mmap_entwy);
	wdma_usew_mmap_entwy_wemove(qp->wwq_desc_mmap_entwy);
	wdma_usew_mmap_entwy_wemove(qp->sq_db_mmap_entwy);
}

int efa_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibqp->pd->device);
	stwuct efa_qp *qp = to_eqp(ibqp);
	int eww;

	ibdev_dbg(&dev->ibdev, "Destwoy qp[%u]\n", ibqp->qp_num);

	eww = efa_destwoy_qp_handwe(dev, qp->qp_handwe);
	if (eww)
		wetuwn eww;

	efa_qp_usew_mmap_entwies_wemove(qp);

	if (qp->wq_cpu_addw) {
		ibdev_dbg(&dev->ibdev,
			  "qp->cpu_addw[0x%p] fweed: size[%wu], dma[%pad]\n",
			  qp->wq_cpu_addw, qp->wq_size,
			  &qp->wq_dma_addw);
		efa_fwee_mapped(dev, qp->wq_cpu_addw, qp->wq_dma_addw,
				qp->wq_size, DMA_TO_DEVICE);
	}

	wetuwn 0;
}

static stwuct wdma_usew_mmap_entwy*
efa_usew_mmap_entwy_insewt(stwuct ib_ucontext *ucontext,
			   u64 addwess, size_t wength,
			   u8 mmap_fwag, u64 *offset)
{
	stwuct efa_usew_mmap_entwy *entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	int eww;

	if (!entwy)
		wetuwn NUWW;

	entwy->addwess = addwess;
	entwy->mmap_fwag = mmap_fwag;

	eww = wdma_usew_mmap_entwy_insewt(ucontext, &entwy->wdma_entwy,
					  wength);
	if (eww) {
		kfwee(entwy);
		wetuwn NUWW;
	}
	*offset = wdma_usew_mmap_get_offset(&entwy->wdma_entwy);

	wetuwn &entwy->wdma_entwy;
}

static int qp_mmap_entwies_setup(stwuct efa_qp *qp,
				 stwuct efa_dev *dev,
				 stwuct efa_ucontext *ucontext,
				 stwuct efa_com_cweate_qp_pawams *pawams,
				 stwuct efa_ibv_cweate_qp_wesp *wesp)
{
	size_t wength;
	u64 addwess;

	addwess = dev->db_baw_addw + wesp->sq_db_offset;
	qp->sq_db_mmap_entwy =
		efa_usew_mmap_entwy_insewt(&ucontext->ibucontext,
					   addwess,
					   PAGE_SIZE, EFA_MMAP_IO_NC,
					   &wesp->sq_db_mmap_key);
	if (!qp->sq_db_mmap_entwy)
		wetuwn -ENOMEM;

	wesp->sq_db_offset &= ~PAGE_MASK;

	addwess = dev->mem_baw_addw + wesp->wwq_desc_offset;
	wength = PAGE_AWIGN(pawams->sq_wing_size_in_bytes +
			    (wesp->wwq_desc_offset & ~PAGE_MASK));

	qp->wwq_desc_mmap_entwy =
		efa_usew_mmap_entwy_insewt(&ucontext->ibucontext,
					   addwess, wength,
					   EFA_MMAP_IO_WC,
					   &wesp->wwq_desc_mmap_key);
	if (!qp->wwq_desc_mmap_entwy)
		goto eww_wemove_mmap;

	wesp->wwq_desc_offset &= ~PAGE_MASK;

	if (qp->wq_size) {
		addwess = dev->db_baw_addw + wesp->wq_db_offset;

		qp->wq_db_mmap_entwy =
			efa_usew_mmap_entwy_insewt(&ucontext->ibucontext,
						   addwess, PAGE_SIZE,
						   EFA_MMAP_IO_NC,
						   &wesp->wq_db_mmap_key);
		if (!qp->wq_db_mmap_entwy)
			goto eww_wemove_mmap;

		wesp->wq_db_offset &= ~PAGE_MASK;

		addwess = viwt_to_phys(qp->wq_cpu_addw);
		qp->wq_mmap_entwy =
			efa_usew_mmap_entwy_insewt(&ucontext->ibucontext,
						   addwess, qp->wq_size,
						   EFA_MMAP_DMA_PAGE,
						   &wesp->wq_mmap_key);
		if (!qp->wq_mmap_entwy)
			goto eww_wemove_mmap;

		wesp->wq_mmap_size = qp->wq_size;
	}

	wetuwn 0;

eww_wemove_mmap:
	efa_qp_usew_mmap_entwies_wemove(qp);

	wetuwn -ENOMEM;
}

static int efa_qp_vawidate_cap(stwuct efa_dev *dev,
			       stwuct ib_qp_init_attw *init_attw)
{
	if (init_attw->cap.max_send_ww > dev->dev_attw.max_sq_depth) {
		ibdev_dbg(&dev->ibdev,
			  "qp: wequested send ww[%u] exceeds the max[%u]\n",
			  init_attw->cap.max_send_ww,
			  dev->dev_attw.max_sq_depth);
		wetuwn -EINVAW;
	}
	if (init_attw->cap.max_wecv_ww > dev->dev_attw.max_wq_depth) {
		ibdev_dbg(&dev->ibdev,
			  "qp: wequested weceive ww[%u] exceeds the max[%u]\n",
			  init_attw->cap.max_wecv_ww,
			  dev->dev_attw.max_wq_depth);
		wetuwn -EINVAW;
	}
	if (init_attw->cap.max_send_sge > dev->dev_attw.max_sq_sge) {
		ibdev_dbg(&dev->ibdev,
			  "qp: wequested sge send[%u] exceeds the max[%u]\n",
			  init_attw->cap.max_send_sge, dev->dev_attw.max_sq_sge);
		wetuwn -EINVAW;
	}
	if (init_attw->cap.max_wecv_sge > dev->dev_attw.max_wq_sge) {
		ibdev_dbg(&dev->ibdev,
			  "qp: wequested sge wecv[%u] exceeds the max[%u]\n",
			  init_attw->cap.max_wecv_sge, dev->dev_attw.max_wq_sge);
		wetuwn -EINVAW;
	}
	if (init_attw->cap.max_inwine_data > dev->dev_attw.inwine_buf_size) {
		ibdev_dbg(&dev->ibdev,
			  "qp: wequested inwine data[%u] exceeds the max[%u]\n",
			  init_attw->cap.max_inwine_data,
			  dev->dev_attw.inwine_buf_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int efa_qp_vawidate_attw(stwuct efa_dev *dev,
				stwuct ib_qp_init_attw *init_attw)
{
	if (init_attw->qp_type != IB_QPT_DWIVEW &&
	    init_attw->qp_type != IB_QPT_UD) {
		ibdev_dbg(&dev->ibdev,
			  "Unsuppowted qp type %d\n", init_attw->qp_type);
		wetuwn -EOPNOTSUPP;
	}

	if (init_attw->swq) {
		ibdev_dbg(&dev->ibdev, "SWQ is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (init_attw->cweate_fwags) {
		ibdev_dbg(&dev->ibdev, "Unsuppowted cweate fwags\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int efa_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init_attw,
		  stwuct ib_udata *udata)
{
	stwuct efa_com_cweate_qp_pawams cweate_qp_pawams = {};
	stwuct efa_com_cweate_qp_wesuwt cweate_qp_wesp;
	stwuct efa_dev *dev = to_edev(ibqp->device);
	stwuct efa_ibv_cweate_qp_wesp wesp = {};
	stwuct efa_ibv_cweate_qp cmd = {};
	stwuct efa_qp *qp = to_eqp(ibqp);
	stwuct efa_ucontext *ucontext;
	int eww;

	ucontext = wdma_udata_to_dwv_context(udata, stwuct efa_ucontext,
					     ibucontext);

	eww = efa_qp_vawidate_cap(dev, init_attw);
	if (eww)
		goto eww_out;

	eww = efa_qp_vawidate_attw(dev, init_attw);
	if (eww)
		goto eww_out;

	if (offsetofend(typeof(cmd), dwivew_qp_type) > udata->inwen) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, no input udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	if (udata->inwen > sizeof(cmd) &&
	    !ib_is_udata_cweawed(udata, sizeof(cmd),
				 udata->inwen - sizeof(cmd))) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, unknown fiewds in udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	eww = ib_copy_fwom_udata(&cmd, udata,
				 min(sizeof(cmd), udata->inwen));
	if (eww) {
		ibdev_dbg(&dev->ibdev,
			  "Cannot copy udata fow cweate_qp\n");
		goto eww_out;
	}

	if (cmd.comp_mask) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, unknown fiewds in udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	cweate_qp_pawams.uawn = ucontext->uawn;
	cweate_qp_pawams.pd = to_epd(ibqp->pd)->pdn;

	if (init_attw->qp_type == IB_QPT_UD) {
		cweate_qp_pawams.qp_type = EFA_ADMIN_QP_TYPE_UD;
	} ewse if (cmd.dwivew_qp_type == EFA_QP_DWIVEW_TYPE_SWD) {
		cweate_qp_pawams.qp_type = EFA_ADMIN_QP_TYPE_SWD;
	} ewse {
		ibdev_dbg(&dev->ibdev,
			  "Unsuppowted qp type %d dwivew qp type %d\n",
			  init_attw->qp_type, cmd.dwivew_qp_type);
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	ibdev_dbg(&dev->ibdev, "Cweate QP: qp type %d dwivew qp type %#x\n",
		  init_attw->qp_type, cmd.dwivew_qp_type);
	cweate_qp_pawams.send_cq_idx = to_ecq(init_attw->send_cq)->cq_idx;
	cweate_qp_pawams.wecv_cq_idx = to_ecq(init_attw->wecv_cq)->cq_idx;
	cweate_qp_pawams.sq_depth = init_attw->cap.max_send_ww;
	cweate_qp_pawams.sq_wing_size_in_bytes = cmd.sq_wing_size;

	cweate_qp_pawams.wq_depth = init_attw->cap.max_wecv_ww;
	cweate_qp_pawams.wq_wing_size_in_bytes = cmd.wq_wing_size;
	qp->wq_size = PAGE_AWIGN(cweate_qp_pawams.wq_wing_size_in_bytes);
	if (qp->wq_size) {
		qp->wq_cpu_addw = efa_zawwoc_mapped(dev, &qp->wq_dma_addw,
						    qp->wq_size, DMA_TO_DEVICE);
		if (!qp->wq_cpu_addw) {
			eww = -ENOMEM;
			goto eww_out;
		}

		ibdev_dbg(&dev->ibdev,
			  "qp->cpu_addw[0x%p] awwocated: size[%wu], dma[%pad]\n",
			  qp->wq_cpu_addw, qp->wq_size, &qp->wq_dma_addw);
		cweate_qp_pawams.wq_base_addw = qp->wq_dma_addw;
	}

	eww = efa_com_cweate_qp(&dev->edev, &cweate_qp_pawams,
				&cweate_qp_wesp);
	if (eww)
		goto eww_fwee_mapped;

	wesp.sq_db_offset = cweate_qp_wesp.sq_db_offset;
	wesp.wq_db_offset = cweate_qp_wesp.wq_db_offset;
	wesp.wwq_desc_offset = cweate_qp_wesp.wwq_descwiptows_offset;
	wesp.send_sub_cq_idx = cweate_qp_wesp.send_sub_cq_idx;
	wesp.wecv_sub_cq_idx = cweate_qp_wesp.wecv_sub_cq_idx;

	eww = qp_mmap_entwies_setup(qp, dev, ucontext, &cweate_qp_pawams,
				    &wesp);
	if (eww)
		goto eww_destwoy_qp;

	qp->qp_handwe = cweate_qp_wesp.qp_handwe;
	qp->ibqp.qp_num = cweate_qp_wesp.qp_num;
	qp->max_send_ww = init_attw->cap.max_send_ww;
	qp->max_wecv_ww = init_attw->cap.max_wecv_ww;
	qp->max_send_sge = init_attw->cap.max_send_sge;
	qp->max_wecv_sge = init_attw->cap.max_wecv_sge;
	qp->max_inwine_data = init_attw->cap.max_inwine_data;

	if (udata->outwen) {
		eww = ib_copy_to_udata(udata, &wesp,
				       min(sizeof(wesp), udata->outwen));
		if (eww) {
			ibdev_dbg(&dev->ibdev,
				  "Faiwed to copy udata fow qp[%u]\n",
				  cweate_qp_wesp.qp_num);
			goto eww_wemove_mmap_entwies;
		}
	}

	ibdev_dbg(&dev->ibdev, "Cweated qp[%d]\n", qp->ibqp.qp_num);

	wetuwn 0;

eww_wemove_mmap_entwies:
	efa_qp_usew_mmap_entwies_wemove(qp);
eww_destwoy_qp:
	efa_destwoy_qp_handwe(dev, cweate_qp_wesp.qp_handwe);
eww_fwee_mapped:
	if (qp->wq_size)
		efa_fwee_mapped(dev, qp->wq_cpu_addw, qp->wq_dma_addw,
				qp->wq_size, DMA_TO_DEVICE);
eww_out:
	atomic64_inc(&dev->stats.cweate_qp_eww);
	wetuwn eww;
}

static const stwuct {
	int			vawid;
	enum ib_qp_attw_mask	weq_pawam;
	enum ib_qp_attw_mask	opt_pawam;
} swd_qp_state_tabwe[IB_QPS_EWW + 1][IB_QPS_EWW + 1] = {
	[IB_QPS_WESET] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_INIT]  = {
			.vawid = 1,
			.weq_pawam = IB_QP_PKEY_INDEX |
				     IB_QP_POWT |
				     IB_QP_QKEY,
		},
	},
	[IB_QPS_INIT] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
		[IB_QPS_INIT]  = {
			.vawid = 1,
			.opt_pawam = IB_QP_PKEY_INDEX |
				     IB_QP_POWT |
				     IB_QP_QKEY,
		},
		[IB_QPS_WTW]   = {
			.vawid = 1,
			.opt_pawam = IB_QP_PKEY_INDEX |
				     IB_QP_QKEY,
		},
	},
	[IB_QPS_WTW] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
		[IB_QPS_WTS]   = {
			.vawid = 1,
			.weq_pawam = IB_QP_SQ_PSN,
			.opt_pawam = IB_QP_CUW_STATE |
				     IB_QP_QKEY |
				     IB_QP_WNW_WETWY,

		}
	},
	[IB_QPS_WTS] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
		[IB_QPS_WTS]   = {
			.vawid = 1,
			.opt_pawam = IB_QP_CUW_STATE |
				     IB_QP_QKEY,
		},
		[IB_QPS_SQD] = {
			.vawid = 1,
			.opt_pawam = IB_QP_EN_SQD_ASYNC_NOTIFY,
		},
	},
	[IB_QPS_SQD] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
		[IB_QPS_WTS]   = {
			.vawid = 1,
			.opt_pawam = IB_QP_CUW_STATE |
				     IB_QP_QKEY,
		},
		[IB_QPS_SQD] = {
			.vawid = 1,
			.opt_pawam = IB_QP_PKEY_INDEX |
				     IB_QP_QKEY,
		}
	},
	[IB_QPS_SQE] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
		[IB_QPS_WTS]   = {
			.vawid = 1,
			.opt_pawam = IB_QP_CUW_STATE |
				     IB_QP_QKEY,
		}
	},
	[IB_QPS_EWW] = {
		[IB_QPS_WESET] = { .vawid = 1 },
		[IB_QPS_EWW]   = { .vawid = 1 },
	}
};

static boow efa_modify_swd_qp_is_ok(enum ib_qp_state cuw_state,
				    enum ib_qp_state next_state,
				    enum ib_qp_attw_mask mask)
{
	enum ib_qp_attw_mask weq_pawam, opt_pawam;

	if (mask & IB_QP_CUW_STATE  &&
	    cuw_state != IB_QPS_WTW && cuw_state != IB_QPS_WTS &&
	    cuw_state != IB_QPS_SQD && cuw_state != IB_QPS_SQE)
		wetuwn fawse;

	if (!swd_qp_state_tabwe[cuw_state][next_state].vawid)
		wetuwn fawse;

	weq_pawam = swd_qp_state_tabwe[cuw_state][next_state].weq_pawam;
	opt_pawam = swd_qp_state_tabwe[cuw_state][next_state].opt_pawam;

	if ((mask & weq_pawam) != weq_pawam)
		wetuwn fawse;

	if (mask & ~(weq_pawam | opt_pawam | IB_QP_STATE))
		wetuwn fawse;

	wetuwn twue;
}

static int efa_modify_qp_vawidate(stwuct efa_dev *dev, stwuct efa_qp *qp,
				  stwuct ib_qp_attw *qp_attw, int qp_attw_mask,
				  enum ib_qp_state cuw_state,
				  enum ib_qp_state new_state)
{
	int eww;

#define EFA_MODIFY_QP_SUPP_MASK \
	(IB_QP_STATE | IB_QP_CUW_STATE | IB_QP_EN_SQD_ASYNC_NOTIFY | \
	 IB_QP_PKEY_INDEX | IB_QP_POWT | IB_QP_QKEY | IB_QP_SQ_PSN | \
	 IB_QP_WNW_WETWY)

	if (qp_attw_mask & ~EFA_MODIFY_QP_SUPP_MASK) {
		ibdev_dbg(&dev->ibdev,
			  "Unsuppowted qp_attw_mask[%#x] suppowted[%#x]\n",
			  qp_attw_mask, EFA_MODIFY_QP_SUPP_MASK);
		wetuwn -EOPNOTSUPP;
	}

	if (qp->ibqp.qp_type == IB_QPT_DWIVEW)
		eww = !efa_modify_swd_qp_is_ok(cuw_state, new_state,
					       qp_attw_mask);
	ewse
		eww = !ib_modify_qp_is_ok(cuw_state, new_state, IB_QPT_UD,
					  qp_attw_mask);

	if (eww) {
		ibdev_dbg(&dev->ibdev, "Invawid modify QP pawametews\n");
		wetuwn -EINVAW;
	}

	if ((qp_attw_mask & IB_QP_POWT) && qp_attw->powt_num != 1) {
		ibdev_dbg(&dev->ibdev, "Can't change powt num\n");
		wetuwn -EOPNOTSUPP;
	}

	if ((qp_attw_mask & IB_QP_PKEY_INDEX) && qp_attw->pkey_index) {
		ibdev_dbg(&dev->ibdev, "Can't change pkey index\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int efa_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw,
		  int qp_attw_mask, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibqp->device);
	stwuct efa_com_modify_qp_pawams pawams = {};
	stwuct efa_qp *qp = to_eqp(ibqp);
	enum ib_qp_state cuw_state;
	enum ib_qp_state new_state;
	int eww;

	if (qp_attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	if (udata->inwen &&
	    !ib_is_udata_cweawed(udata, 0, udata->inwen)) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, udata not cweawed\n");
		wetuwn -EINVAW;
	}

	cuw_state = qp_attw_mask & IB_QP_CUW_STATE ? qp_attw->cuw_qp_state :
						     qp->state;
	new_state = qp_attw_mask & IB_QP_STATE ? qp_attw->qp_state : cuw_state;

	eww = efa_modify_qp_vawidate(dev, qp, qp_attw, qp_attw_mask, cuw_state,
				     new_state);
	if (eww)
		wetuwn eww;

	pawams.qp_handwe = qp->qp_handwe;

	if (qp_attw_mask & IB_QP_STATE) {
		EFA_SET(&pawams.modify_mask, EFA_ADMIN_MODIFY_QP_CMD_QP_STATE,
			1);
		EFA_SET(&pawams.modify_mask,
			EFA_ADMIN_MODIFY_QP_CMD_CUW_QP_STATE, 1);
		pawams.cuw_qp_state = cuw_state;
		pawams.qp_state = new_state;
	}

	if (qp_attw_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) {
		EFA_SET(&pawams.modify_mask,
			EFA_ADMIN_MODIFY_QP_CMD_SQ_DWAINED_ASYNC_NOTIFY, 1);
		pawams.sq_dwained_async_notify = qp_attw->en_sqd_async_notify;
	}

	if (qp_attw_mask & IB_QP_QKEY) {
		EFA_SET(&pawams.modify_mask, EFA_ADMIN_MODIFY_QP_CMD_QKEY, 1);
		pawams.qkey = qp_attw->qkey;
	}

	if (qp_attw_mask & IB_QP_SQ_PSN) {
		EFA_SET(&pawams.modify_mask, EFA_ADMIN_MODIFY_QP_CMD_SQ_PSN, 1);
		pawams.sq_psn = qp_attw->sq_psn;
	}

	if (qp_attw_mask & IB_QP_WNW_WETWY) {
		EFA_SET(&pawams.modify_mask, EFA_ADMIN_MODIFY_QP_CMD_WNW_WETWY,
			1);
		pawams.wnw_wetwy = qp_attw->wnw_wetwy;
	}

	eww = efa_com_modify_qp(&dev->edev, &pawams);
	if (eww)
		wetuwn eww;

	qp->state = new_state;

	wetuwn 0;
}

static int efa_destwoy_cq_idx(stwuct efa_dev *dev, int cq_idx)
{
	stwuct efa_com_destwoy_cq_pawams pawams = { .cq_idx = cq_idx };

	wetuwn efa_com_destwoy_cq(&dev->edev, &pawams);
}

static void efa_cq_usew_mmap_entwies_wemove(stwuct efa_cq *cq)
{
	wdma_usew_mmap_entwy_wemove(cq->db_mmap_entwy);
	wdma_usew_mmap_entwy_wemove(cq->mmap_entwy);
}

int efa_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibcq->device);
	stwuct efa_cq *cq = to_ecq(ibcq);

	ibdev_dbg(&dev->ibdev,
		  "Destwoy cq[%d] viwt[0x%p] fweed: size[%wu], dma[%pad]\n",
		  cq->cq_idx, cq->cpu_addw, cq->size, &cq->dma_addw);

	efa_destwoy_cq_idx(dev, cq->cq_idx);
	efa_cq_usew_mmap_entwies_wemove(cq);
	if (cq->eq) {
		xa_ewase(&dev->cqs_xa, cq->cq_idx);
		synchwonize_iwq(cq->eq->iwq.iwqn);
	}
	efa_fwee_mapped(dev, cq->cpu_addw, cq->dma_addw, cq->size,
			DMA_FWOM_DEVICE);
	wetuwn 0;
}

static stwuct efa_eq *efa_vec2eq(stwuct efa_dev *dev, int vec)
{
	wetuwn &dev->eqs[vec];
}

static int cq_mmap_entwies_setup(stwuct efa_dev *dev, stwuct efa_cq *cq,
				 stwuct efa_ibv_cweate_cq_wesp *wesp,
				 boow db_vawid)
{
	wesp->q_mmap_size = cq->size;
	cq->mmap_entwy = efa_usew_mmap_entwy_insewt(&cq->ucontext->ibucontext,
						    viwt_to_phys(cq->cpu_addw),
						    cq->size, EFA_MMAP_DMA_PAGE,
						    &wesp->q_mmap_key);
	if (!cq->mmap_entwy)
		wetuwn -ENOMEM;

	if (db_vawid) {
		cq->db_mmap_entwy =
			efa_usew_mmap_entwy_insewt(&cq->ucontext->ibucontext,
						   dev->db_baw_addw + wesp->db_off,
						   PAGE_SIZE, EFA_MMAP_IO_NC,
						   &wesp->db_mmap_key);
		if (!cq->db_mmap_entwy) {
			wdma_usew_mmap_entwy_wemove(cq->mmap_entwy);
			wetuwn -ENOMEM;
		}

		wesp->db_off &= ~PAGE_MASK;
		wesp->comp_mask |= EFA_CWEATE_CQ_WESP_DB_OFF;
	}

	wetuwn 0;
}

int efa_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata)
{
	stwuct efa_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct efa_ucontext, ibucontext);
	stwuct efa_com_cweate_cq_pawams pawams = {};
	stwuct efa_ibv_cweate_cq_wesp wesp = {};
	stwuct efa_com_cweate_cq_wesuwt wesuwt;
	stwuct ib_device *ibdev = ibcq->device;
	stwuct efa_dev *dev = to_edev(ibdev);
	stwuct efa_ibv_cweate_cq cmd = {};
	stwuct efa_cq *cq = to_ecq(ibcq);
	int entwies = attw->cqe;
	boow set_swc_addw;
	int eww;

	ibdev_dbg(ibdev, "cweate_cq entwies %d\n", entwies);

	if (attw->fwags)
		wetuwn -EOPNOTSUPP;

	if (entwies < 1 || entwies > dev->dev_attw.max_cq_depth) {
		ibdev_dbg(ibdev,
			  "cq: wequested entwies[%u] non-positive ow gweatew than max[%u]\n",
			  entwies, dev->dev_attw.max_cq_depth);
		eww = -EINVAW;
		goto eww_out;
	}

	if (offsetofend(typeof(cmd), num_sub_cqs) > udata->inwen) {
		ibdev_dbg(ibdev,
			  "Incompatibwe ABI pawams, no input udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	if (udata->inwen > sizeof(cmd) &&
	    !ib_is_udata_cweawed(udata, sizeof(cmd),
				 udata->inwen - sizeof(cmd))) {
		ibdev_dbg(ibdev,
			  "Incompatibwe ABI pawams, unknown fiewds in udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	eww = ib_copy_fwom_udata(&cmd, udata,
				 min(sizeof(cmd), udata->inwen));
	if (eww) {
		ibdev_dbg(ibdev, "Cannot copy udata fow cweate_cq\n");
		goto eww_out;
	}

	if (cmd.comp_mask || !is_wesewved_cweawed(cmd.wesewved_58)) {
		ibdev_dbg(ibdev,
			  "Incompatibwe ABI pawams, unknown fiewds in udata\n");
		eww = -EINVAW;
		goto eww_out;
	}

	set_swc_addw = !!(cmd.fwags & EFA_CWEATE_CQ_WITH_SGID);
	if ((cmd.cq_entwy_size != sizeof(stwuct efa_io_wx_cdesc_ex)) &&
	    (set_swc_addw ||
	     cmd.cq_entwy_size != sizeof(stwuct efa_io_wx_cdesc))) {
		ibdev_dbg(ibdev,
			  "Invawid entwy size [%u]\n", cmd.cq_entwy_size);
		eww = -EINVAW;
		goto eww_out;
	}

	if (cmd.num_sub_cqs != dev->dev_attw.sub_cqs_pew_cq) {
		ibdev_dbg(ibdev,
			  "Invawid numbew of sub cqs[%u] expected[%u]\n",
			  cmd.num_sub_cqs, dev->dev_attw.sub_cqs_pew_cq);
		eww = -EINVAW;
		goto eww_out;
	}

	cq->ucontext = ucontext;
	cq->size = PAGE_AWIGN(cmd.cq_entwy_size * entwies * cmd.num_sub_cqs);
	cq->cpu_addw = efa_zawwoc_mapped(dev, &cq->dma_addw, cq->size,
					 DMA_FWOM_DEVICE);
	if (!cq->cpu_addw) {
		eww = -ENOMEM;
		goto eww_out;
	}

	pawams.uawn = cq->ucontext->uawn;
	pawams.cq_depth = entwies;
	pawams.dma_addw = cq->dma_addw;
	pawams.entwy_size_in_bytes = cmd.cq_entwy_size;
	pawams.num_sub_cqs = cmd.num_sub_cqs;
	pawams.set_swc_addw = set_swc_addw;
	if (cmd.fwags & EFA_CWEATE_CQ_WITH_COMPWETION_CHANNEW) {
		cq->eq = efa_vec2eq(dev, attw->comp_vectow);
		pawams.eqn = cq->eq->eeq.eqn;
		pawams.intewwupt_mode_enabwed = twue;
	}

	eww = efa_com_cweate_cq(&dev->edev, &pawams, &wesuwt);
	if (eww)
		goto eww_fwee_mapped;

	wesp.db_off = wesuwt.db_off;
	wesp.cq_idx = wesuwt.cq_idx;
	cq->cq_idx = wesuwt.cq_idx;
	cq->ibcq.cqe = wesuwt.actuaw_depth;
	WAWN_ON_ONCE(entwies != wesuwt.actuaw_depth);

	eww = cq_mmap_entwies_setup(dev, cq, &wesp, wesuwt.db_vawid);
	if (eww) {
		ibdev_dbg(ibdev, "Couwd not setup cq[%u] mmap entwies\n",
			  cq->cq_idx);
		goto eww_destwoy_cq;
	}

	if (cq->eq) {
		eww = xa_eww(xa_stowe(&dev->cqs_xa, cq->cq_idx, cq, GFP_KEWNEW));
		if (eww) {
			ibdev_dbg(ibdev, "Faiwed to stowe cq[%u] in xawway\n",
				  cq->cq_idx);
			goto eww_wemove_mmap;
		}
	}

	if (udata->outwen) {
		eww = ib_copy_to_udata(udata, &wesp,
				       min(sizeof(wesp), udata->outwen));
		if (eww) {
			ibdev_dbg(ibdev,
				  "Faiwed to copy udata fow cweate_cq\n");
			goto eww_xa_ewase;
		}
	}

	ibdev_dbg(ibdev, "Cweated cq[%d], cq depth[%u]. dma[%pad] viwt[0x%p]\n",
		  cq->cq_idx, wesuwt.actuaw_depth, &cq->dma_addw, cq->cpu_addw);

	wetuwn 0;

eww_xa_ewase:
	if (cq->eq)
		xa_ewase(&dev->cqs_xa, cq->cq_idx);
eww_wemove_mmap:
	efa_cq_usew_mmap_entwies_wemove(cq);
eww_destwoy_cq:
	efa_destwoy_cq_idx(dev, cq->cq_idx);
eww_fwee_mapped:
	efa_fwee_mapped(dev, cq->cpu_addw, cq->dma_addw, cq->size,
			DMA_FWOM_DEVICE);

eww_out:
	atomic64_inc(&dev->stats.cweate_cq_eww);
	wetuwn eww;
}

static int umem_to_page_wist(stwuct efa_dev *dev,
			     stwuct ib_umem *umem,
			     u64 *page_wist,
			     u32 hp_cnt,
			     u8 hp_shift)
{
	u32 pages_in_hp = BIT(hp_shift - PAGE_SHIFT);
	stwuct ib_bwock_itew bitew;
	unsigned int hp_idx = 0;

	ibdev_dbg(&dev->ibdev, "hp_cnt[%u], pages_in_hp[%u]\n",
		  hp_cnt, pages_in_hp);

	wdma_umem_fow_each_dma_bwock(umem, &bitew, BIT(hp_shift))
		page_wist[hp_idx++] = wdma_bwock_itew_dma_addwess(&bitew);

	wetuwn 0;
}

static stwuct scattewwist *efa_vmawwoc_buf_to_sg(u64 *buf, int page_cnt)
{
	stwuct scattewwist *sgwist;
	stwuct page *pg;
	int i;

	sgwist = kmawwoc_awway(page_cnt, sizeof(*sgwist), GFP_KEWNEW);
	if (!sgwist)
		wetuwn NUWW;
	sg_init_tabwe(sgwist, page_cnt);
	fow (i = 0; i < page_cnt; i++) {
		pg = vmawwoc_to_page(buf);
		if (!pg)
			goto eww;
		sg_set_page(&sgwist[i], pg, PAGE_SIZE, 0);
		buf += PAGE_SIZE / sizeof(*buf);
	}
	wetuwn sgwist;

eww:
	kfwee(sgwist);
	wetuwn NUWW;
}

/*
 * cweate a chunk wist of physicaw pages dma addwesses fwom the suppwied
 * scattew gathew wist
 */
static int pbw_chunk_wist_cweate(stwuct efa_dev *dev, stwuct pbw_context *pbw)
{
	stwuct pbw_chunk_wist *chunk_wist = &pbw->phys.indiwect.chunk_wist;
	int page_cnt = pbw->phys.indiwect.pbw_buf_size_in_pages;
	stwuct scattewwist *pages_sgw = pbw->phys.indiwect.sgw;
	unsigned int chunk_wist_size, chunk_idx, paywoad_idx;
	int sg_dma_cnt = pbw->phys.indiwect.sg_dma_cnt;
	stwuct efa_com_ctww_buff_info *ctww_buf;
	u64 *cuw_chunk_buf, *pwev_chunk_buf;
	stwuct ib_bwock_itew bitew;
	dma_addw_t dma_addw;
	int i;

	/* awwocate a chunk wist that consists of 4KB chunks */
	chunk_wist_size = DIV_WOUND_UP(page_cnt, EFA_PTWS_PEW_CHUNK);

	chunk_wist->size = chunk_wist_size;
	chunk_wist->chunks = kcawwoc(chunk_wist_size,
				     sizeof(*chunk_wist->chunks),
				     GFP_KEWNEW);
	if (!chunk_wist->chunks)
		wetuwn -ENOMEM;

	ibdev_dbg(&dev->ibdev,
		  "chunk_wist_size[%u] - pages[%u]\n", chunk_wist_size,
		  page_cnt);

	/* awwocate chunk buffews: */
	fow (i = 0; i < chunk_wist_size; i++) {
		chunk_wist->chunks[i].buf = kzawwoc(EFA_CHUNK_SIZE, GFP_KEWNEW);
		if (!chunk_wist->chunks[i].buf)
			goto chunk_wist_deawwoc;

		chunk_wist->chunks[i].wength = EFA_CHUNK_USED_SIZE;
	}
	chunk_wist->chunks[chunk_wist_size - 1].wength =
		((page_cnt % EFA_PTWS_PEW_CHUNK) * EFA_CHUNK_PAYWOAD_PTW_SIZE) +
			EFA_CHUNK_PTW_SIZE;

	/* fiww the dma addwesses of sg wist pages to chunks: */
	chunk_idx = 0;
	paywoad_idx = 0;
	cuw_chunk_buf = chunk_wist->chunks[0].buf;
	wdma_fow_each_bwock(pages_sgw, &bitew, sg_dma_cnt,
			    EFA_CHUNK_PAYWOAD_SIZE) {
		cuw_chunk_buf[paywoad_idx++] =
			wdma_bwock_itew_dma_addwess(&bitew);

		if (paywoad_idx == EFA_PTWS_PEW_CHUNK) {
			chunk_idx++;
			cuw_chunk_buf = chunk_wist->chunks[chunk_idx].buf;
			paywoad_idx = 0;
		}
	}

	/* map chunks to dma and fiww chunks next ptws */
	fow (i = chunk_wist_size - 1; i >= 0; i--) {
		dma_addw = dma_map_singwe(&dev->pdev->dev,
					  chunk_wist->chunks[i].buf,
					  chunk_wist->chunks[i].wength,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&dev->pdev->dev, dma_addw)) {
			ibdev_eww(&dev->ibdev,
				  "chunk[%u] dma_map_faiwed\n", i);
			goto chunk_wist_unmap;
		}

		chunk_wist->chunks[i].dma_addw = dma_addw;
		ibdev_dbg(&dev->ibdev,
			  "chunk[%u] mapped at [%pad]\n", i, &dma_addw);

		if (!i)
			bweak;

		pwev_chunk_buf = chunk_wist->chunks[i - 1].buf;

		ctww_buf = (stwuct efa_com_ctww_buff_info *)
				&pwev_chunk_buf[EFA_PTWS_PEW_CHUNK];
		ctww_buf->wength = chunk_wist->chunks[i].wength;

		efa_com_set_dma_addw(dma_addw,
				     &ctww_buf->addwess.mem_addw_high,
				     &ctww_buf->addwess.mem_addw_wow);
	}

	wetuwn 0;

chunk_wist_unmap:
	fow (; i < chunk_wist_size; i++) {
		dma_unmap_singwe(&dev->pdev->dev, chunk_wist->chunks[i].dma_addw,
				 chunk_wist->chunks[i].wength, DMA_TO_DEVICE);
	}
chunk_wist_deawwoc:
	fow (i = 0; i < chunk_wist_size; i++)
		kfwee(chunk_wist->chunks[i].buf);

	kfwee(chunk_wist->chunks);
	wetuwn -ENOMEM;
}

static void pbw_chunk_wist_destwoy(stwuct efa_dev *dev, stwuct pbw_context *pbw)
{
	stwuct pbw_chunk_wist *chunk_wist = &pbw->phys.indiwect.chunk_wist;
	int i;

	fow (i = 0; i < chunk_wist->size; i++) {
		dma_unmap_singwe(&dev->pdev->dev, chunk_wist->chunks[i].dma_addw,
				 chunk_wist->chunks[i].wength, DMA_TO_DEVICE);
		kfwee(chunk_wist->chunks[i].buf);
	}

	kfwee(chunk_wist->chunks);
}

/* initiawize pbw continuous mode: map pbw buffew to a dma addwess. */
static int pbw_continuous_initiawize(stwuct efa_dev *dev,
				     stwuct pbw_context *pbw)
{
	dma_addw_t dma_addw;

	dma_addw = dma_map_singwe(&dev->pdev->dev, pbw->pbw_buf,
				  pbw->pbw_buf_size_in_bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&dev->pdev->dev, dma_addw)) {
		ibdev_eww(&dev->ibdev, "Unabwe to map pbw to DMA addwess\n");
		wetuwn -ENOMEM;
	}

	pbw->phys.continuous.dma_addw = dma_addw;
	ibdev_dbg(&dev->ibdev,
		  "pbw continuous - dma_addw = %pad, size[%u]\n",
		  &dma_addw, pbw->pbw_buf_size_in_bytes);

	wetuwn 0;
}

/*
 * initiawize pbw indiwect mode:
 * cweate a chunk wist out of the dma addwesses of the physicaw pages of
 * pbw buffew.
 */
static int pbw_indiwect_initiawize(stwuct efa_dev *dev, stwuct pbw_context *pbw)
{
	u32 size_in_pages = DIV_WOUND_UP(pbw->pbw_buf_size_in_bytes, EFA_CHUNK_PAYWOAD_SIZE);
	stwuct scattewwist *sgw;
	int sg_dma_cnt, eww;

	BUIWD_BUG_ON(EFA_CHUNK_PAYWOAD_SIZE > PAGE_SIZE);
	sgw = efa_vmawwoc_buf_to_sg(pbw->pbw_buf, size_in_pages);
	if (!sgw)
		wetuwn -ENOMEM;

	sg_dma_cnt = dma_map_sg(&dev->pdev->dev, sgw, size_in_pages, DMA_TO_DEVICE);
	if (!sg_dma_cnt) {
		eww = -EINVAW;
		goto eww_map;
	}

	pbw->phys.indiwect.pbw_buf_size_in_pages = size_in_pages;
	pbw->phys.indiwect.sgw = sgw;
	pbw->phys.indiwect.sg_dma_cnt = sg_dma_cnt;
	eww = pbw_chunk_wist_cweate(dev, pbw);
	if (eww) {
		ibdev_dbg(&dev->ibdev,
			  "chunk_wist cweation faiwed[%d]\n", eww);
		goto eww_chunk;
	}

	ibdev_dbg(&dev->ibdev,
		  "pbw indiwect - size[%u], chunks[%u]\n",
		  pbw->pbw_buf_size_in_bytes,
		  pbw->phys.indiwect.chunk_wist.size);

	wetuwn 0;

eww_chunk:
	dma_unmap_sg(&dev->pdev->dev, sgw, size_in_pages, DMA_TO_DEVICE);
eww_map:
	kfwee(sgw);
	wetuwn eww;
}

static void pbw_indiwect_tewminate(stwuct efa_dev *dev, stwuct pbw_context *pbw)
{
	pbw_chunk_wist_destwoy(dev, pbw);
	dma_unmap_sg(&dev->pdev->dev, pbw->phys.indiwect.sgw,
		     pbw->phys.indiwect.pbw_buf_size_in_pages, DMA_TO_DEVICE);
	kfwee(pbw->phys.indiwect.sgw);
}

/* cweate a page buffew wist fwom a mapped usew memowy wegion */
static int pbw_cweate(stwuct efa_dev *dev,
		      stwuct pbw_context *pbw,
		      stwuct ib_umem *umem,
		      int hp_cnt,
		      u8 hp_shift)
{
	int eww;

	pbw->pbw_buf_size_in_bytes = hp_cnt * EFA_CHUNK_PAYWOAD_PTW_SIZE;
	pbw->pbw_buf = kvzawwoc(pbw->pbw_buf_size_in_bytes, GFP_KEWNEW);
	if (!pbw->pbw_buf)
		wetuwn -ENOMEM;

	if (is_vmawwoc_addw(pbw->pbw_buf)) {
		pbw->physicawwy_continuous = 0;
		eww = umem_to_page_wist(dev, umem, pbw->pbw_buf, hp_cnt,
					hp_shift);
		if (eww)
			goto eww_fwee;

		eww = pbw_indiwect_initiawize(dev, pbw);
		if (eww)
			goto eww_fwee;
	} ewse {
		pbw->physicawwy_continuous = 1;
		eww = umem_to_page_wist(dev, umem, pbw->pbw_buf, hp_cnt,
					hp_shift);
		if (eww)
			goto eww_fwee;

		eww = pbw_continuous_initiawize(dev, pbw);
		if (eww)
			goto eww_fwee;
	}

	ibdev_dbg(&dev->ibdev,
		  "usew_pbw_cweated: usew_pages[%u], continuous[%u]\n",
		  hp_cnt, pbw->physicawwy_continuous);

	wetuwn 0;

eww_fwee:
	kvfwee(pbw->pbw_buf);
	wetuwn eww;
}

static void pbw_destwoy(stwuct efa_dev *dev, stwuct pbw_context *pbw)
{
	if (pbw->physicawwy_continuous)
		dma_unmap_singwe(&dev->pdev->dev, pbw->phys.continuous.dma_addw,
				 pbw->pbw_buf_size_in_bytes, DMA_TO_DEVICE);
	ewse
		pbw_indiwect_tewminate(dev, pbw);

	kvfwee(pbw->pbw_buf);
}

static int efa_cweate_inwine_pbw(stwuct efa_dev *dev, stwuct efa_mw *mw,
				 stwuct efa_com_weg_mw_pawams *pawams)
{
	int eww;

	pawams->inwine_pbw = 1;
	eww = umem_to_page_wist(dev, mw->umem, pawams->pbw.inwine_pbw_awway,
				pawams->page_num, pawams->page_shift);
	if (eww)
		wetuwn eww;

	ibdev_dbg(&dev->ibdev,
		  "inwine_pbw_awway - pages[%u]\n", pawams->page_num);

	wetuwn 0;
}

static int efa_cweate_pbw(stwuct efa_dev *dev,
			  stwuct pbw_context *pbw,
			  stwuct efa_mw *mw,
			  stwuct efa_com_weg_mw_pawams *pawams)
{
	int eww;

	eww = pbw_cweate(dev, pbw, mw->umem, pawams->page_num,
			 pawams->page_shift);
	if (eww) {
		ibdev_dbg(&dev->ibdev, "Faiwed to cweate pbw[%d]\n", eww);
		wetuwn eww;
	}

	pawams->inwine_pbw = 0;
	pawams->indiwect = !pbw->physicawwy_continuous;
	if (pbw->physicawwy_continuous) {
		pawams->pbw.pbw.wength = pbw->pbw_buf_size_in_bytes;

		efa_com_set_dma_addw(pbw->phys.continuous.dma_addw,
				     &pawams->pbw.pbw.addwess.mem_addw_high,
				     &pawams->pbw.pbw.addwess.mem_addw_wow);
	} ewse {
		pawams->pbw.pbw.wength =
			pbw->phys.indiwect.chunk_wist.chunks[0].wength;

		efa_com_set_dma_addw(pbw->phys.indiwect.chunk_wist.chunks[0].dma_addw,
				     &pawams->pbw.pbw.addwess.mem_addw_high,
				     &pawams->pbw.pbw.addwess.mem_addw_wow);
	}

	wetuwn 0;
}

static stwuct efa_mw *efa_awwoc_mw(stwuct ib_pd *ibpd, int access_fwags,
				   stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	int supp_access_fwags;
	stwuct efa_mw *mw;

	if (udata && udata->inwen &&
	    !ib_is_udata_cweawed(udata, 0, sizeof(udata->inwen))) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatibwe ABI pawams, udata not cweawed\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	supp_access_fwags =
		IB_ACCESS_WOCAW_WWITE |
		(EFA_DEV_CAP(dev, WDMA_WEAD) ? IB_ACCESS_WEMOTE_WEAD : 0) |
		(EFA_DEV_CAP(dev, WDMA_WWITE) ? IB_ACCESS_WEMOTE_WWITE : 0);

	access_fwags &= ~IB_ACCESS_OPTIONAW;
	if (access_fwags & ~supp_access_fwags) {
		ibdev_dbg(&dev->ibdev,
			  "Unsuppowted access fwags[%#x], suppowted[%#x]\n",
			  access_fwags, supp_access_fwags);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn mw;
}

static int efa_wegistew_mw(stwuct ib_pd *ibpd, stwuct efa_mw *mw, u64 stawt,
			   u64 wength, u64 viwt_addw, int access_fwags)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	stwuct efa_com_weg_mw_pawams pawams = {};
	stwuct efa_com_weg_mw_wesuwt wesuwt = {};
	stwuct pbw_context pbw;
	unsigned int pg_sz;
	int inwine_size;
	int eww;

	pawams.pd = to_epd(ibpd)->pdn;
	pawams.iova = viwt_addw;
	pawams.mw_wength_in_bytes = wength;
	pawams.pewmissions = access_fwags;

	pg_sz = ib_umem_find_best_pgsz(mw->umem,
				       dev->dev_attw.page_size_cap,
				       viwt_addw);
	if (!pg_sz) {
		ibdev_dbg(&dev->ibdev, "Faiwed to find a suitabwe page size in page_size_cap %#wwx\n",
			  dev->dev_attw.page_size_cap);
		wetuwn -EOPNOTSUPP;
	}

	pawams.page_shift = owdew_base_2(pg_sz);
	pawams.page_num = ib_umem_num_dma_bwocks(mw->umem, pg_sz);

	ibdev_dbg(&dev->ibdev,
		  "stawt %#wwx wength %#wwx pawams.page_shift %u pawams.page_num %u\n",
		  stawt, wength, pawams.page_shift, pawams.page_num);

	inwine_size = AWWAY_SIZE(pawams.pbw.inwine_pbw_awway);
	if (pawams.page_num <= inwine_size) {
		eww = efa_cweate_inwine_pbw(dev, mw, &pawams);
		if (eww)
			wetuwn eww;

		eww = efa_com_wegistew_mw(&dev->edev, &pawams, &wesuwt);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = efa_cweate_pbw(dev, &pbw, mw, &pawams);
		if (eww)
			wetuwn eww;

		eww = efa_com_wegistew_mw(&dev->edev, &pawams, &wesuwt);
		pbw_destwoy(dev, &pbw);

		if (eww)
			wetuwn eww;
	}

	mw->ibmw.wkey = wesuwt.w_key;
	mw->ibmw.wkey = wesuwt.w_key;
	mw->ibmw.wength = wength;
	mw->ic_info.wecv_ic_id = wesuwt.ic_info.wecv_ic_id;
	mw->ic_info.wdma_wead_ic_id = wesuwt.ic_info.wdma_wead_ic_id;
	mw->ic_info.wdma_wecv_ic_id = wesuwt.ic_info.wdma_wecv_ic_id;
	mw->ic_info.wecv_ic_id_vawid = wesuwt.ic_info.wecv_ic_id_vawid;
	mw->ic_info.wdma_wead_ic_id_vawid = wesuwt.ic_info.wdma_wead_ic_id_vawid;
	mw->ic_info.wdma_wecv_ic_id_vawid = wesuwt.ic_info.wdma_wecv_ic_id_vawid;
	ibdev_dbg(&dev->ibdev, "Wegistewed mw[%d]\n", mw->ibmw.wkey);

	wetuwn 0;
}

stwuct ib_mw *efa_weg_usew_mw_dmabuf(stwuct ib_pd *ibpd, u64 stawt,
				     u64 wength, u64 viwt_addw,
				     int fd, int access_fwags,
				     stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	stwuct ib_umem_dmabuf *umem_dmabuf;
	stwuct efa_mw *mw;
	int eww;

	mw = efa_awwoc_mw(ibpd, access_fwags, udata);
	if (IS_EWW(mw)) {
		eww = PTW_EWW(mw);
		goto eww_out;
	}

	umem_dmabuf = ib_umem_dmabuf_get_pinned(ibpd->device, stawt, wength, fd,
						access_fwags);
	if (IS_EWW(umem_dmabuf)) {
		eww = PTW_EWW(umem_dmabuf);
		ibdev_dbg(&dev->ibdev, "Faiwed to get dmabuf umem[%d]\n", eww);
		goto eww_fwee;
	}

	mw->umem = &umem_dmabuf->umem;
	eww = efa_wegistew_mw(ibpd, mw, stawt, wength, viwt_addw, access_fwags);
	if (eww)
		goto eww_wewease;

	wetuwn &mw->ibmw;

eww_wewease:
	ib_umem_wewease(mw->umem);
eww_fwee:
	kfwee(mw);
eww_out:
	atomic64_inc(&dev->stats.weg_mw_eww);
	wetuwn EWW_PTW(eww);
}

stwuct ib_mw *efa_weg_mw(stwuct ib_pd *ibpd, u64 stawt, u64 wength,
			 u64 viwt_addw, int access_fwags,
			 stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibpd->device);
	stwuct efa_mw *mw;
	int eww;

	mw = efa_awwoc_mw(ibpd, access_fwags, udata);
	if (IS_EWW(mw)) {
		eww = PTW_EWW(mw);
		goto eww_out;
	}

	mw->umem = ib_umem_get(ibpd->device, stawt, wength, access_fwags);
	if (IS_EWW(mw->umem)) {
		eww = PTW_EWW(mw->umem);
		ibdev_dbg(&dev->ibdev,
			  "Faiwed to pin and map usew space memowy[%d]\n", eww);
		goto eww_fwee;
	}

	eww = efa_wegistew_mw(ibpd, mw, stawt, wength, viwt_addw, access_fwags);
	if (eww)
		goto eww_wewease;

	wetuwn &mw->ibmw;

eww_wewease:
	ib_umem_wewease(mw->umem);
eww_fwee:
	kfwee(mw);
eww_out:
	atomic64_inc(&dev->stats.weg_mw_eww);
	wetuwn EWW_PTW(eww);
}

static int UVEWBS_HANDWEW(EFA_IB_METHOD_MW_QUEWY)(stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_mw *ibmw = uvewbs_attw_get_obj(attws, EFA_IB_ATTW_QUEWY_MW_HANDWE);
	stwuct efa_mw *mw = to_emw(ibmw);
	u16 ic_id_vawidity = 0;
	int wet;

	wet = uvewbs_copy_to(attws, EFA_IB_ATTW_QUEWY_MW_WESP_WECV_IC_ID,
			     &mw->ic_info.wecv_ic_id, sizeof(mw->ic_info.wecv_ic_id));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, EFA_IB_ATTW_QUEWY_MW_WESP_WDMA_WEAD_IC_ID,
			     &mw->ic_info.wdma_wead_ic_id, sizeof(mw->ic_info.wdma_wead_ic_id));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, EFA_IB_ATTW_QUEWY_MW_WESP_WDMA_WECV_IC_ID,
			     &mw->ic_info.wdma_wecv_ic_id, sizeof(mw->ic_info.wdma_wecv_ic_id));
	if (wet)
		wetuwn wet;

	if (mw->ic_info.wecv_ic_id_vawid)
		ic_id_vawidity |= EFA_QUEWY_MW_VAWIDITY_WECV_IC_ID;
	if (mw->ic_info.wdma_wead_ic_id_vawid)
		ic_id_vawidity |= EFA_QUEWY_MW_VAWIDITY_WDMA_WEAD_IC_ID;
	if (mw->ic_info.wdma_wecv_ic_id_vawid)
		ic_id_vawidity |= EFA_QUEWY_MW_VAWIDITY_WDMA_WECV_IC_ID;

	wetuwn uvewbs_copy_to(attws, EFA_IB_ATTW_QUEWY_MW_WESP_IC_ID_VAWIDITY,
			      &ic_id_vawidity, sizeof(ic_id_vawidity));
}

int efa_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct efa_dev *dev = to_edev(ibmw->device);
	stwuct efa_com_deweg_mw_pawams pawams;
	stwuct efa_mw *mw = to_emw(ibmw);
	int eww;

	ibdev_dbg(&dev->ibdev, "Dewegistew mw[%d]\n", ibmw->wkey);

	pawams.w_key = mw->ibmw.wkey;
	eww = efa_com_deweg_mw(&dev->edev, &pawams);
	if (eww)
		wetuwn eww;

	ib_umem_wewease(mw->umem);
	kfwee(mw);

	wetuwn 0;
}

int efa_get_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			   stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct ib_powt_attw attw;
	int eww;

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww) {
		ibdev_dbg(ibdev, "Couwdn't quewy powt eww[%d]\n", eww);
		wetuwn eww;
	}

	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;

	wetuwn 0;
}

static int efa_deawwoc_uaw(stwuct efa_dev *dev, u16 uawn)
{
	stwuct efa_com_deawwoc_uaw_pawams pawams = {
		.uawn = uawn,
	};

	wetuwn efa_com_deawwoc_uaw(&dev->edev, &pawams);
}

#define EFA_CHECK_USEW_COMP(_dev, _comp_mask, _attw, _mask, _attw_stw) \
	(_attw_stw = (!(_dev)->dev_attw._attw || ((_comp_mask) & (_mask))) ? \
		     NUWW : #_attw)

static int efa_usew_comp_handshake(const stwuct ib_ucontext *ibucontext,
				   const stwuct efa_ibv_awwoc_ucontext_cmd *cmd)
{
	stwuct efa_dev *dev = to_edev(ibucontext->device);
	chaw *attw_stw;

	if (EFA_CHECK_USEW_COMP(dev, cmd->comp_mask, max_tx_batch,
				EFA_AWWOC_UCONTEXT_CMD_COMP_TX_BATCH, attw_stw))
		goto eww;

	if (EFA_CHECK_USEW_COMP(dev, cmd->comp_mask, min_sq_depth,
				EFA_AWWOC_UCONTEXT_CMD_COMP_MIN_SQ_WW,
				attw_stw))
		goto eww;

	wetuwn 0;

eww:
	ibdev_dbg(&dev->ibdev, "Usewspace handshake faiwed fow %s attwibute\n",
		  attw_stw);
	wetuwn -EOPNOTSUPP;
}

int efa_awwoc_ucontext(stwuct ib_ucontext *ibucontext, stwuct ib_udata *udata)
{
	stwuct efa_ucontext *ucontext = to_eucontext(ibucontext);
	stwuct efa_dev *dev = to_edev(ibucontext->device);
	stwuct efa_ibv_awwoc_ucontext_wesp wesp = {};
	stwuct efa_ibv_awwoc_ucontext_cmd cmd = {};
	stwuct efa_com_awwoc_uaw_wesuwt wesuwt;
	int eww;

	/*
	 * it's fine if the dwivew does not know aww wequest fiewds,
	 * we wiww ack input fiewds in ouw wesponse.
	 */

	eww = ib_copy_fwom_udata(&cmd, udata,
				 min(sizeof(cmd), udata->inwen));
	if (eww) {
		ibdev_dbg(&dev->ibdev,
			  "Cannot copy udata fow awwoc_ucontext\n");
		goto eww_out;
	}

	eww = efa_usew_comp_handshake(ibucontext, &cmd);
	if (eww)
		goto eww_out;

	eww = efa_com_awwoc_uaw(&dev->edev, &wesuwt);
	if (eww)
		goto eww_out;

	ucontext->uawn = wesuwt.uawn;

	wesp.cmds_supp_udata_mask |= EFA_USEW_CMDS_SUPP_UDATA_QUEWY_DEVICE;
	wesp.cmds_supp_udata_mask |= EFA_USEW_CMDS_SUPP_UDATA_CWEATE_AH;
	wesp.sub_cqs_pew_cq = dev->dev_attw.sub_cqs_pew_cq;
	wesp.inwine_buf_size = dev->dev_attw.inwine_buf_size;
	wesp.max_wwq_size = dev->dev_attw.max_wwq_size;
	wesp.max_tx_batch = dev->dev_attw.max_tx_batch;
	wesp.min_sq_ww = dev->dev_attw.min_sq_depth;

	eww = ib_copy_to_udata(udata, &wesp,
			       min(sizeof(wesp), udata->outwen));
	if (eww)
		goto eww_deawwoc_uaw;

	wetuwn 0;

eww_deawwoc_uaw:
	efa_deawwoc_uaw(dev, wesuwt.uawn);
eww_out:
	atomic64_inc(&dev->stats.awwoc_ucontext_eww);
	wetuwn eww;
}

void efa_deawwoc_ucontext(stwuct ib_ucontext *ibucontext)
{
	stwuct efa_ucontext *ucontext = to_eucontext(ibucontext);
	stwuct efa_dev *dev = to_edev(ibucontext->device);

	efa_deawwoc_uaw(dev, ucontext->uawn);
}

void efa_mmap_fwee(stwuct wdma_usew_mmap_entwy *wdma_entwy)
{
	stwuct efa_usew_mmap_entwy *entwy = to_emmap(wdma_entwy);

	kfwee(entwy);
}

static int __efa_mmap(stwuct efa_dev *dev, stwuct efa_ucontext *ucontext,
		      stwuct vm_awea_stwuct *vma)
{
	stwuct wdma_usew_mmap_entwy *wdma_entwy;
	stwuct efa_usew_mmap_entwy *entwy;
	unsigned wong va;
	int eww = 0;
	u64 pfn;

	wdma_entwy = wdma_usew_mmap_entwy_get(&ucontext->ibucontext, vma);
	if (!wdma_entwy) {
		ibdev_dbg(&dev->ibdev,
			  "pgoff[%#wx] does not have vawid entwy\n",
			  vma->vm_pgoff);
		atomic64_inc(&dev->stats.mmap_eww);
		wetuwn -EINVAW;
	}
	entwy = to_emmap(wdma_entwy);

	ibdev_dbg(&dev->ibdev,
		  "Mapping addwess[%#wwx], wength[%#zx], mmap_fwag[%d]\n",
		  entwy->addwess, wdma_entwy->npages * PAGE_SIZE,
		  entwy->mmap_fwag);

	pfn = entwy->addwess >> PAGE_SHIFT;
	switch (entwy->mmap_fwag) {
	case EFA_MMAP_IO_NC:
		eww = wdma_usew_mmap_io(&ucontext->ibucontext, vma, pfn,
					entwy->wdma_entwy.npages * PAGE_SIZE,
					pgpwot_noncached(vma->vm_page_pwot),
					wdma_entwy);
		bweak;
	case EFA_MMAP_IO_WC:
		eww = wdma_usew_mmap_io(&ucontext->ibucontext, vma, pfn,
					entwy->wdma_entwy.npages * PAGE_SIZE,
					pgpwot_wwitecombine(vma->vm_page_pwot),
					wdma_entwy);
		bweak;
	case EFA_MMAP_DMA_PAGE:
		fow (va = vma->vm_stawt; va < vma->vm_end;
		     va += PAGE_SIZE, pfn++) {
			eww = vm_insewt_page(vma, va, pfn_to_page(pfn));
			if (eww)
				bweak;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	if (eww) {
		ibdev_dbg(
			&dev->ibdev,
			"Couwdn't mmap addwess[%#wwx] wength[%#zx] mmap_fwag[%d] eww[%d]\n",
			entwy->addwess, wdma_entwy->npages * PAGE_SIZE,
			entwy->mmap_fwag, eww);
		atomic64_inc(&dev->stats.mmap_eww);
	}

	wdma_usew_mmap_entwy_put(wdma_entwy);
	wetuwn eww;
}

int efa_mmap(stwuct ib_ucontext *ibucontext,
	     stwuct vm_awea_stwuct *vma)
{
	stwuct efa_ucontext *ucontext = to_eucontext(ibucontext);
	stwuct efa_dev *dev = to_edev(ibucontext->device);
	size_t wength = vma->vm_end - vma->vm_stawt;

	ibdev_dbg(&dev->ibdev,
		  "stawt %#wx, end %#wx, wength = %#zx, pgoff = %#wx\n",
		  vma->vm_stawt, vma->vm_end, wength, vma->vm_pgoff);

	wetuwn __efa_mmap(dev, ucontext, vma);
}

static int efa_ah_destwoy(stwuct efa_dev *dev, stwuct efa_ah *ah)
{
	stwuct efa_com_destwoy_ah_pawams pawams = {
		.ah = ah->ah,
		.pdn = to_epd(ah->ibah.pd)->pdn,
	};

	wetuwn efa_com_destwoy_ah(&dev->edev, &pawams);
}

int efa_cweate_ah(stwuct ib_ah *ibah,
		  stwuct wdma_ah_init_attw *init_attw,
		  stwuct ib_udata *udata)
{
	stwuct wdma_ah_attw *ah_attw = init_attw->ah_attw;
	stwuct efa_dev *dev = to_edev(ibah->device);
	stwuct efa_com_cweate_ah_pawams pawams = {};
	stwuct efa_ibv_cweate_ah_wesp wesp = {};
	stwuct efa_com_cweate_ah_wesuwt wesuwt;
	stwuct efa_ah *ah = to_eah(ibah);
	int eww;

	if (!(init_attw->fwags & WDMA_CWEATE_AH_SWEEPABWE)) {
		ibdev_dbg(&dev->ibdev,
			  "Cweate addwess handwe is not suppowted in atomic context\n");
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	if (udata->inwen &&
	    !ib_is_udata_cweawed(udata, 0, udata->inwen)) {
		ibdev_dbg(&dev->ibdev, "Incompatibwe ABI pawams\n");
		eww = -EINVAW;
		goto eww_out;
	}

	memcpy(pawams.dest_addw, ah_attw->gwh.dgid.waw,
	       sizeof(pawams.dest_addw));
	pawams.pdn = to_epd(ibah->pd)->pdn;
	eww = efa_com_cweate_ah(&dev->edev, &pawams, &wesuwt);
	if (eww)
		goto eww_out;

	memcpy(ah->id, ah_attw->gwh.dgid.waw, sizeof(ah->id));
	ah->ah = wesuwt.ah;

	wesp.efa_addwess_handwe = wesuwt.ah;

	if (udata->outwen) {
		eww = ib_copy_to_udata(udata, &wesp,
				       min(sizeof(wesp), udata->outwen));
		if (eww) {
			ibdev_dbg(&dev->ibdev,
				  "Faiwed to copy udata fow cweate_ah wesponse\n");
			goto eww_destwoy_ah;
		}
	}
	ibdev_dbg(&dev->ibdev, "Cweated ah[%d]\n", ah->ah);

	wetuwn 0;

eww_destwoy_ah:
	efa_ah_destwoy(dev, ah);
eww_out:
	atomic64_inc(&dev->stats.cweate_ah_eww);
	wetuwn eww;
}

int efa_destwoy_ah(stwuct ib_ah *ibah, u32 fwags)
{
	stwuct efa_dev *dev = to_edev(ibah->pd->device);
	stwuct efa_ah *ah = to_eah(ibah);

	ibdev_dbg(&dev->ibdev, "Destwoy ah[%d]\n", ah->ah);

	if (!(fwags & WDMA_DESTWOY_AH_SWEEPABWE)) {
		ibdev_dbg(&dev->ibdev,
			  "Destwoy addwess handwe is not suppowted in atomic context\n");
		wetuwn -EOPNOTSUPP;
	}

	efa_ah_destwoy(dev, ah);
	wetuwn 0;
}

stwuct wdma_hw_stats *efa_awwoc_hw_powt_stats(stwuct ib_device *ibdev,
					      u32 powt_num)
{
	wetuwn wdma_awwoc_hw_stats_stwuct(efa_powt_stats_descs,
					  AWWAY_SIZE(efa_powt_stats_descs),
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

stwuct wdma_hw_stats *efa_awwoc_hw_device_stats(stwuct ib_device *ibdev)
{
	wetuwn wdma_awwoc_hw_stats_stwuct(efa_device_stats_descs,
					  AWWAY_SIZE(efa_device_stats_descs),
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static int efa_fiww_device_stats(stwuct efa_dev *dev,
				 stwuct wdma_hw_stats *stats)
{
	stwuct efa_com_stats_admin *as = &dev->edev.aq.stats;
	stwuct efa_stats *s = &dev->stats;

	stats->vawue[EFA_SUBMITTED_CMDS] = atomic64_wead(&as->submitted_cmd);
	stats->vawue[EFA_COMPWETED_CMDS] = atomic64_wead(&as->compweted_cmd);
	stats->vawue[EFA_CMDS_EWW] = atomic64_wead(&as->cmd_eww);
	stats->vawue[EFA_NO_COMPWETION_CMDS] = atomic64_wead(&as->no_compwetion);

	stats->vawue[EFA_KEEP_AWIVE_WCVD] = atomic64_wead(&s->keep_awive_wcvd);
	stats->vawue[EFA_AWWOC_PD_EWW] = atomic64_wead(&s->awwoc_pd_eww);
	stats->vawue[EFA_CWEATE_QP_EWW] = atomic64_wead(&s->cweate_qp_eww);
	stats->vawue[EFA_CWEATE_CQ_EWW] = atomic64_wead(&s->cweate_cq_eww);
	stats->vawue[EFA_WEG_MW_EWW] = atomic64_wead(&s->weg_mw_eww);
	stats->vawue[EFA_AWWOC_UCONTEXT_EWW] =
		atomic64_wead(&s->awwoc_ucontext_eww);
	stats->vawue[EFA_CWEATE_AH_EWW] = atomic64_wead(&s->cweate_ah_eww);
	stats->vawue[EFA_MMAP_EWW] = atomic64_wead(&s->mmap_eww);

	wetuwn AWWAY_SIZE(efa_device_stats_descs);
}

static int efa_fiww_powt_stats(stwuct efa_dev *dev, stwuct wdma_hw_stats *stats,
			       u32 powt_num)
{
	stwuct efa_com_get_stats_pawams pawams = {};
	union efa_com_get_stats_wesuwt wesuwt;
	stwuct efa_com_wdma_wwite_stats *wws;
	stwuct efa_com_wdma_wead_stats *wws;
	stwuct efa_com_messages_stats *ms;
	stwuct efa_com_basic_stats *bs;
	int eww;

	pawams.scope = EFA_ADMIN_GET_STATS_SCOPE_AWW;
	pawams.type = EFA_ADMIN_GET_STATS_TYPE_BASIC;

	eww = efa_com_get_stats(&dev->edev, &pawams, &wesuwt);
	if (eww)
		wetuwn eww;

	bs = &wesuwt.basic_stats;
	stats->vawue[EFA_TX_BYTES] = bs->tx_bytes;
	stats->vawue[EFA_TX_PKTS] = bs->tx_pkts;
	stats->vawue[EFA_WX_BYTES] = bs->wx_bytes;
	stats->vawue[EFA_WX_PKTS] = bs->wx_pkts;
	stats->vawue[EFA_WX_DWOPS] = bs->wx_dwops;

	pawams.type = EFA_ADMIN_GET_STATS_TYPE_MESSAGES;
	eww = efa_com_get_stats(&dev->edev, &pawams, &wesuwt);
	if (eww)
		wetuwn eww;

	ms = &wesuwt.messages_stats;
	stats->vawue[EFA_SEND_BYTES] = ms->send_bytes;
	stats->vawue[EFA_SEND_WWS] = ms->send_wws;
	stats->vawue[EFA_WECV_BYTES] = ms->wecv_bytes;
	stats->vawue[EFA_WECV_WWS] = ms->wecv_wws;

	pawams.type = EFA_ADMIN_GET_STATS_TYPE_WDMA_WEAD;
	eww = efa_com_get_stats(&dev->edev, &pawams, &wesuwt);
	if (eww)
		wetuwn eww;

	wws = &wesuwt.wdma_wead_stats;
	stats->vawue[EFA_WDMA_WEAD_WWS] = wws->wead_wws;
	stats->vawue[EFA_WDMA_WEAD_BYTES] = wws->wead_bytes;
	stats->vawue[EFA_WDMA_WEAD_WW_EWW] = wws->wead_ww_eww;
	stats->vawue[EFA_WDMA_WEAD_WESP_BYTES] = wws->wead_wesp_bytes;

	if (EFA_DEV_CAP(dev, WDMA_WWITE)) {
		pawams.type = EFA_ADMIN_GET_STATS_TYPE_WDMA_WWITE;
		eww = efa_com_get_stats(&dev->edev, &pawams, &wesuwt);
		if (eww)
			wetuwn eww;

		wws = &wesuwt.wdma_wwite_stats;
		stats->vawue[EFA_WDMA_WWITE_WWS] = wws->wwite_wws;
		stats->vawue[EFA_WDMA_WWITE_BYTES] = wws->wwite_bytes;
		stats->vawue[EFA_WDMA_WWITE_WW_EWW] = wws->wwite_ww_eww;
		stats->vawue[EFA_WDMA_WWITE_WECV_BYTES] = wws->wwite_wecv_bytes;
	}

	wetuwn AWWAY_SIZE(efa_powt_stats_descs);
}

int efa_get_hw_stats(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
		     u32 powt_num, int index)
{
	if (powt_num)
		wetuwn efa_fiww_powt_stats(to_edev(ibdev), stats, powt_num);
	ewse
		wetuwn efa_fiww_device_stats(to_edev(ibdev), stats);
}

enum wdma_wink_wayew efa_powt_wink_wayew(stwuct ib_device *ibdev,
					 u32 powt_num)
{
	wetuwn IB_WINK_WAYEW_UNSPECIFIED;
}

DECWAWE_UVEWBS_NAMED_METHOD(EFA_IB_METHOD_MW_QUEWY,
			    UVEWBS_ATTW_IDW(EFA_IB_ATTW_QUEWY_MW_HANDWE,
					    UVEWBS_OBJECT_MW,
					    UVEWBS_ACCESS_WEAD,
					    UA_MANDATOWY),
			    UVEWBS_ATTW_PTW_OUT(EFA_IB_ATTW_QUEWY_MW_WESP_IC_ID_VAWIDITY,
						UVEWBS_ATTW_TYPE(u16),
						UA_MANDATOWY),
			    UVEWBS_ATTW_PTW_OUT(EFA_IB_ATTW_QUEWY_MW_WESP_WECV_IC_ID,
						UVEWBS_ATTW_TYPE(u16),
						UA_MANDATOWY),
			    UVEWBS_ATTW_PTW_OUT(EFA_IB_ATTW_QUEWY_MW_WESP_WDMA_WEAD_IC_ID,
						UVEWBS_ATTW_TYPE(u16),
						UA_MANDATOWY),
			    UVEWBS_ATTW_PTW_OUT(EFA_IB_ATTW_QUEWY_MW_WESP_WDMA_WECV_IC_ID,
						UVEWBS_ATTW_TYPE(u16),
						UA_MANDATOWY));

ADD_UVEWBS_METHODS(efa_mw,
		   UVEWBS_OBJECT_MW,
		   &UVEWBS_METHOD(EFA_IB_METHOD_MW_QUEWY));

const stwuct uapi_definition efa_uapi_defs[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE(UVEWBS_OBJECT_MW,
				&efa_mw),
	{},
};
