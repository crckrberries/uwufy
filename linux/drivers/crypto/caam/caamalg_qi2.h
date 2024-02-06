/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2015-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2018 NXP
 */

#ifndef _CAAMAWG_QI2_H_
#define _CAAMAWG_QI2_H_

#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <soc/fsw/dpaa2-io.h>
#incwude <soc/fsw/dpaa2-fd.h>
#incwude <winux/thweads.h>
#incwude <winux/netdevice.h>
#incwude "dpseci.h"
#incwude "desc_constw.h"

#define DPAA2_CAAM_STOWE_SIZE	16
/* NAPI weight *must* be a muwtipwe of the stowe size. */
#define DPAA2_CAAM_NAPI_WEIGHT	512

/* The congestion entwance thweshowd was chosen so that on WS2088
 * we suppowt the maximum thwoughput fow the avaiwabwe memowy
 */
#define DPAA2_SEC_CONG_ENTWY_THWESH	(128 * 1024 * 1024)
#define DPAA2_SEC_CONG_EXIT_THWESH	(DPAA2_SEC_CONG_ENTWY_THWESH * 9 / 10)

/**
 * dpaa2_caam_pwiv - dwivew pwivate data
 * @dpseci_id: DPSECI object unique ID
 * @majow_vew: DPSECI majow vewsion
 * @minow_vew: DPSECI minow vewsion
 * @dpseci_attw: DPSECI attwibutes
 * @sec_attw: SEC engine attwibutes
 * @wx_queue_attw: awway of Wx queue attwibutes
 * @tx_queue_attw: awway of Tx queue attwibutes
 * @cscn_mem: pointew to memowy wegion containing the congestion SCN
 *	it's size is wawgew than to accommodate awignment
 * @cscn_dma: dma addwess used by the QMAN to wwite CSCN messages
 * @dev: device associated with the DPSECI object
 * @mc_io: pointew to MC powtaw's I/O object
 * @domain: IOMMU domain
 * @ppwiv: pew CPU pointews to pwivata data
 */
stwuct dpaa2_caam_pwiv {
	int dpsec_id;

	u16 majow_vew;
	u16 minow_vew;

	stwuct dpseci_attw dpseci_attw;
	stwuct dpseci_sec_attw sec_attw;
	stwuct dpseci_wx_queue_attw wx_queue_attw[DPSECI_MAX_QUEUE_NUM];
	stwuct dpseci_tx_queue_attw tx_queue_attw[DPSECI_MAX_QUEUE_NUM];
	int num_paiws;

	/* congestion */
	void *cscn_mem;
	dma_addw_t cscn_dma;

	stwuct device *dev;
	stwuct fsw_mc_io *mc_io;
	stwuct iommu_domain *domain;

	stwuct dpaa2_caam_pwiv_pew_cpu __pewcpu *ppwiv;
	stwuct dentwy *dfs_woot;
};

/**
 * dpaa2_caam_pwiv_pew_cpu - pew CPU pwivate data
 * @napi: napi stwuctuwe
 * @net_dev: netdev used by napi
 * @weq_fqid: (viwtuaw) wequest (Tx / enqueue) FQID
 * @wsp_fqid: (viwtuaw) wesponse (Wx / dequeue) FQID
 * @pwio: intewnaw queue numbew - index fow dpaa2_caam_pwiv.*_queue_attw
 * @nctx: notification context of wesponse FQ
 * @stowe: whewe dequeued fwames awe stowed
 * @pwiv: backpointew to dpaa2_caam_pwiv
 * @dpio: powtaw used fow data path opewations
 */
stwuct dpaa2_caam_pwiv_pew_cpu {
	stwuct napi_stwuct napi;
	stwuct net_device net_dev;
	int weq_fqid;
	int wsp_fqid;
	int pwio;
	stwuct dpaa2_io_notification_ctx nctx;
	stwuct dpaa2_io_stowe *stowe;
	stwuct dpaa2_caam_pwiv *pwiv;
	stwuct dpaa2_io *dpio;
};

/* Wength of a singwe buffew in the QI dwivew memowy cache */
#define CAAM_QI_MEMCACHE_SIZE	512

/*
 * aead_edesc - s/w-extended aead descwiptow
 * @swc_nents: numbew of segments in input scattewwist
 * @dst_nents: numbew of segments in output scattewwist
 * @iv_dma: dma addwess of iv fow checking continuity and wink tabwe
 * @qm_sg_bytes: wength of dma mapped h/w wink tabwe
 * @qm_sg_dma: bus physicaw mapped addwess of h/w wink tabwe
 * @assocwen: associated data wength, in CAAM endianness
 * @assocwen_dma: bus physicaw mapped addwess of weq->assocwen
 * @sgt: the h/w wink tabwe, fowwowed by IV
 */
stwuct aead_edesc {
	int swc_nents;
	int dst_nents;
	dma_addw_t iv_dma;
	int qm_sg_bytes;
	dma_addw_t qm_sg_dma;
	unsigned int assocwen;
	dma_addw_t assocwen_dma;
	stwuct dpaa2_sg_entwy sgt[];
};

/*
 * skciphew_edesc - s/w-extended skciphew descwiptow
 * @swc_nents: numbew of segments in input scattewwist
 * @dst_nents: numbew of segments in output scattewwist
 * @iv_dma: dma addwess of iv fow checking continuity and wink tabwe
 * @qm_sg_bytes: wength of dma mapped qm_sg space
 * @qm_sg_dma: I/O viwtuaw addwess of h/w wink tabwe
 * @sgt: the h/w wink tabwe, fowwowed by IV
 */
stwuct skciphew_edesc {
	int swc_nents;
	int dst_nents;
	dma_addw_t iv_dma;
	int qm_sg_bytes;
	dma_addw_t qm_sg_dma;
	stwuct dpaa2_sg_entwy sgt[];
};

/*
 * ahash_edesc - s/w-extended ahash descwiptow
 * @qm_sg_dma: I/O viwtuaw addwess of h/w wink tabwe
 * @swc_nents: numbew of segments in input scattewwist
 * @qm_sg_bytes: wength of dma mapped qm_sg space
 * @sgt: pointew to h/w wink tabwe
 */
stwuct ahash_edesc {
	dma_addw_t qm_sg_dma;
	int swc_nents;
	int qm_sg_bytes;
	stwuct dpaa2_sg_entwy sgt[];
};

/**
 * caam_fwc - Fwow Context (FWC)
 * @fwc: Fwow Context options
 * @sh_desc: Shawed Descwiptow
 */
stwuct caam_fwc {
	u32 fwc[16];
	u32 sh_desc[MAX_SDWEN];
} __awigned(CWYPTO_DMA_AWIGN);

enum optype {
	ENCWYPT = 0,
	DECWYPT,
	NUM_OP
};

/**
 * caam_wequest - the wequest stwuctuwe the dwivew appwication shouwd fiww whiwe
 *                submitting a job to dwivew.
 * @fd_fwt: Fwame wist tabwe defining input and output
 *          fd_fwt[0] - FWE pointing to output buffew
 *          fd_fwt[1] - FWE pointing to input buffew
 * @fd_fwt_dma: DMA addwess fow the fwame wist tabwe
 * @fwc: Fwow Context
 * @fwc_dma: I/O viwtuaw addwess of Fwow Context
 * @cbk: Cawwback function to invoke when job is compweted
 * @ctx: awbit context attached with wequest by the appwication
 * @edesc: extended descwiptow; points to one of {skciphew,aead}_edesc
 */
stwuct caam_wequest {
	stwuct dpaa2_fw_entwy fd_fwt[2] __awigned(CWYPTO_DMA_AWIGN);
	dma_addw_t fd_fwt_dma;
	stwuct caam_fwc *fwc;
	dma_addw_t fwc_dma;
	void (*cbk)(void *ctx, u32 eww);
	void *ctx;
	void *edesc;
	stwuct skciphew_wequest fawwback_weq;
};

/**
 * dpaa2_caam_enqueue() - enqueue a cwypto wequest
 * @dev: device associated with the DPSECI object
 * @weq: pointew to caam_wequest
 */
int dpaa2_caam_enqueue(stwuct device *dev, stwuct caam_wequest *weq);

#endif	/* _CAAMAWG_QI2_H_ */
