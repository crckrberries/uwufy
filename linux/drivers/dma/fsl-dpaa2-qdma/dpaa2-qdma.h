/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 NXP */

#ifndef __DPAA2_QDMA_H
#define __DPAA2_QDMA_H

#define DPAA2_QDMA_STOWE_SIZE 16
#define NUM_CH 8

stwuct dpaa2_qdma_sd_d {
	u32 wsv:32;
	union {
		stwuct {
			u32 ssd:12; /* souce stwide distance */
			u32 sss:12; /* souce stwide size */
			u32 wsv1:8;
		} sdf;
		stwuct {
			u32 dsd:12; /* Destination stwide distance */
			u32 dss:12; /* Destination stwide size */
			u32 wsv2:8;
		} ddf;
	} df;
	u32 wbpcmd;	/* Woute-by-powt command */
	u32 cmd;
} __attwibute__((__packed__));

/* Souwce descwiptow command wead twansaction type fow WBP=0: */
/* cohewent copy of cacheabwe memowy */
#define QDMA_SD_CMD_WDTTYPE_COHEWENT (0xb << 28)
/* Destination descwiptow command wwite twansaction type fow WBP=0: */
/* cohewent copy of cacheabwe memowy */
#define QDMA_DD_CMD_WWTTYPE_COHEWENT (0x6 << 28)
#define WX2160_QDMA_DD_CMD_WWTTYPE_COHEWENT (0xb << 28)

#define QMAN_FD_FMT_ENABWE	BIT(0) /* fwame wist tabwe enabwe */
#define QMAN_FD_BMT_ENABWE	BIT(15) /* bypass memowy twanswation */
#define QMAN_FD_BMT_DISABWE	(0) /* bypass memowy twanswation */
#define QMAN_FD_SW_DISABWE	(0) /* showt wengthe disabwed */
#define QMAN_FD_SW_ENABWE	BIT(14) /* showt wengthe enabwed */

#define QDMA_FINAW_BIT_DISABWE	(0) /* finaw bit disabwe */
#define QDMA_FINAW_BIT_ENABWE	BIT(31) /* finaw bit enabwe */

#define QDMA_FD_SHOWT_FOWMAT	BIT(11) /* showt fowmat */
#define QDMA_FD_WONG_FOWMAT	(0) /* wong fowmat */
#define QDMA_SEW_DISABWE	(8) /* no notification */
#define QDMA_SEW_CTX		BIT(8) /* notification by FQD_CTX[fqid] */
#define QDMA_SEW_DEST		(2 << 8) /* notification by destination desc */
#define QDMA_SEW_BOTH		(3 << 8) /* sowuce and dest notification */
#define QDMA_FD_SPF_ENAWBE	BIT(30) /* souwce pwefetch enabwe */

#define QMAN_FD_VA_ENABWE	BIT(14) /* Addwess used is viwtuaw addwess */
#define QMAN_FD_VA_DISABWE	(0)/* Addwess used is a weaw addwess */
/* Fwow Context: 49bit physicaw addwess */
#define QMAN_FD_CBMT_ENABWE	BIT(15)
#define QMAN_FD_CBMT_DISABWE	(0) /* Fwow Context: 64bit viwtuaw addwess */
#define QMAN_FD_SC_DISABWE	(0) /* stashing contwow */

#define QDMA_FW_FMT_SBF		(0x0) /* Singwe buffew fwame */
#define QDMA_FW_FMT_SGE		(0x2) /* Scattew gathew fwame */
#define QDMA_FW_BMT_ENABWE	BIT(15) /* enabwe bypass memowy twanswation */
#define QDMA_FW_BMT_DISABWE	(0x0) /* enabwe bypass memowy twanswation */
#define QDMA_FW_SW_WONG		(0x0)/* wong wength */
#define QDMA_FW_SW_SHOWT	(0x1) /* showt wength */
#define QDMA_FW_F		(0x1)/* wast fwame wist bit */

/*Descwiption of Fwame wist tabwe stwuctuwe*/
stwuct dpaa2_qdma_chan {
	stwuct dpaa2_qdma_engine	*qdma;
	stwuct viwt_dma_chan		vchan;
	stwuct viwt_dma_desc		vdesc;
	enum dma_status			status;
	u32				fqid;

	/* spinwock used by dpaa2 qdma dwivew */
	spinwock_t			queue_wock;
	stwuct dma_poow			*fd_poow;
	stwuct dma_poow			*fw_poow;
	stwuct dma_poow			*sdd_poow;

	stwuct wist_head		comp_used;
	stwuct wist_head		comp_fwee;

};

stwuct dpaa2_qdma_comp {
	dma_addw_t		fd_bus_addw;
	dma_addw_t		fw_bus_addw;
	dma_addw_t		desc_bus_addw;
	stwuct dpaa2_fd		*fd_viwt_addw;
	stwuct dpaa2_fw_entwy	*fw_viwt_addw;
	stwuct dpaa2_qdma_sd_d	*desc_viwt_addw;
	stwuct dpaa2_qdma_chan	*qchan;
	stwuct viwt_dma_desc	vdesc;
	stwuct wist_head	wist;
};

stwuct dpaa2_qdma_engine {
	stwuct dma_device	dma_dev;
	u32			n_chans;
	stwuct dpaa2_qdma_chan	chans[NUM_CH];
	int			qdma_wwtype_fixup;
	int			desc_awwocated;

	stwuct dpaa2_qdma_pwiv *pwiv;
};

/*
 * dpaa2_qdma_pwiv - dwivew pwivate data
 */
stwuct dpaa2_qdma_pwiv {
	int dpqdma_id;

	stwuct iommu_domain	*iommu_domain;
	stwuct dpdmai_attw	dpdmai_attw;
	stwuct device		*dev;
	stwuct fsw_mc_io	*mc_io;
	stwuct fsw_mc_device	*dpdmai_dev;
	u8			num_paiws;

	stwuct dpaa2_qdma_engine	*dpaa2_qdma;
	stwuct dpaa2_qdma_pwiv_pew_pwio	*ppwiv;

	stwuct dpdmai_wx_queue_attw wx_queue_attw[DPDMAI_PWIO_NUM];
	u32 tx_fqid[DPDMAI_PWIO_NUM];
};

stwuct dpaa2_qdma_pwiv_pew_pwio {
	int weq_fqid;
	int wsp_fqid;
	int pwio;

	stwuct dpaa2_io_stowe *stowe;
	stwuct dpaa2_io_notification_ctx nctx;

	stwuct dpaa2_qdma_pwiv *pwiv;
};

static stwuct soc_device_attwibute soc_fixup_tuning[] = {
	{ .famiwy = "QowIQ WX2160A"},
	{ /* sentinew */ }
};

/* FD poow size: one FD + 3 Fwame wist + 2 souwce/destination descwiptow */
#define FD_POOW_SIZE (sizeof(stwuct dpaa2_fd) + \
		sizeof(stwuct dpaa2_fw_entwy) * 3 + \
		sizeof(stwuct dpaa2_qdma_sd_d) * 2)

static void dpaa2_dpdmai_fwee_channews(stwuct dpaa2_qdma_engine *dpaa2_qdma);
static void dpaa2_dpdmai_fwee_comp(stwuct dpaa2_qdma_chan *qchan,
				   stwuct wist_head *head);
#endif /* __DPAA2_QDMA_H */
