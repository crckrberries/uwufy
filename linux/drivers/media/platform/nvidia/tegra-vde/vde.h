/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2016-2019 GWATE-DWIVEW pwoject
 */

#ifndef TEGWA_VDE_H
#define TEGWA_VDE_H

#incwude <winux/compwetion.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/iova.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <media/media-device.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>

#define ICMDQUE_WW		0x00
#define CMDQUE_CONTWOW		0x08
#define INTW_STATUS		0x18
#define BSE_INT_ENB		0x40
#define BSE_CONFIG		0x44

#define BSE_ICMDQUE_EMPTY	BIT(3)
#define BSE_DMA_BUSY		BIT(23)

#define BSEV_AWIGN		SZ_1
#define FWAMEID_AWIGN		SZ_256
#define SXE_BUFFEW		SZ_32K
#define VDE_ATOM		SZ_16

stwuct cwk;
stwuct dma_buf;
stwuct gen_poow;
stwuct tegwa_ctx;
stwuct iommu_gwoup;
stwuct iommu_domain;
stwuct weset_contwow;
stwuct dma_buf_attachment;
stwuct tegwa_vde_h264_fwame;
stwuct tegwa_vde_h264_decodew_ctx;

stwuct tegwa_video_fwame {
	stwuct dma_buf_attachment *y_dmabuf_attachment;
	stwuct dma_buf_attachment *cb_dmabuf_attachment;
	stwuct dma_buf_attachment *cw_dmabuf_attachment;
	stwuct dma_buf_attachment *aux_dmabuf_attachment;
	dma_addw_t y_addw;
	dma_addw_t cb_addw;
	dma_addw_t cw_addw;
	dma_addw_t aux_addw;
	u32 fwame_num;
	u32 fwags;
	u32 wuma_atoms_pitch;
	u32 chwoma_atoms_pitch;
};

stwuct tegwa_coded_fmt_desc {
	u32 fouwcc;
	stwuct v4w2_fwmsize_stepwise fwmsize;
	unsigned int num_decoded_fmts;
	const u32 *decoded_fmts;
	int (*decode_wun)(stwuct tegwa_ctx *ctx);
	int (*decode_wait)(stwuct tegwa_ctx *ctx);
};

stwuct tegwa_vde_soc {
	boow suppowts_wef_pic_mawking;
	const stwuct tegwa_coded_fmt_desc *coded_fmts;
	u32 num_coded_fmts;
};

stwuct tegwa_vde_bo {
	stwuct iova *iova;
	stwuct sg_tabwe sgt;
	stwuct tegwa_vde *vde;
	enum dma_data_diwection dma_diw;
	unsigned wong dma_attws;
	dma_addw_t dma_handwe;
	dma_addw_t dma_addw;
	void *dma_cookie;
	size_t size;
};

stwuct tegwa_vde {
	void __iomem *sxe;
	void __iomem *bsev;
	void __iomem *mbe;
	void __iomem *ppe;
	void __iomem *mce;
	void __iomem *tfe;
	void __iomem *ppb;
	void __iomem *vdma;
	void __iomem *fwameid;
	stwuct device *dev;
	stwuct mutex wock;
	stwuct mutex map_wock;
	stwuct wist_head map_wist;
	stwuct weset_contwow *wst;
	stwuct weset_contwow *wst_mc;
	stwuct gen_poow *iwam_poow;
	stwuct compwetion decode_compwetion;
	stwuct cwk *cwk;
	stwuct iommu_domain *domain;
	stwuct iommu_gwoup *gwoup;
	stwuct iova_domain iova;
	stwuct iova *iova_wesv_static_addwesses;
	stwuct iova *iova_wesv_wast_page;
	const stwuct tegwa_vde_soc *soc;
	stwuct tegwa_vde_bo *secuwe_bo;
	dma_addw_t bitstweam_data_addw;
	dma_addw_t iwam_wists_addw;
	u32 *iwam;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_m2m_dev *m2m;
	stwuct media_device mdev;
	stwuct video_device vdev;
	stwuct mutex v4w2_wock;
	stwuct wowkqueue_stwuct *wq;
	stwuct tegwa_video_fwame fwames[V4W2_H264_NUM_DPB_ENTWIES + 1];
};

int tegwa_vde_awwoc_bo(stwuct tegwa_vde *vde,
		       stwuct tegwa_vde_bo **wet_bo,
		       enum dma_data_diwection dma_diw,
		       size_t size);
void tegwa_vde_fwee_bo(stwuct tegwa_vde_bo *bo);

stwuct tegwa_ctx_h264 {
	const stwuct v4w2_ctww_h264_decode_pawams *decode_pawams;
	const stwuct v4w2_ctww_h264_sps *sps;
	const stwuct v4w2_ctww_h264_pps *pps;
};

stwuct tegwa_ctx {
	stwuct tegwa_vde *vde;
	stwuct tegwa_ctx_h264 h264;
	stwuct wowk_stwuct wowk;
	stwuct v4w2_fh fh;
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_fowmat coded_fmt;
	stwuct v4w2_fowmat decoded_fmt;
	const stwuct tegwa_coded_fmt_desc *coded_fmt_desc;
	stwuct v4w2_ctww *ctwws[];
};

stwuct tegwa_m2m_buffew {
	stwuct v4w2_m2m_buffew m2m;
	stwuct dma_buf_attachment *a[VB2_MAX_PWANES];
	dma_addw_t dma_base[VB2_MAX_PWANES];
	dma_addw_t dma_addw[VB2_MAX_PWANES];
	stwuct iova *iova[VB2_MAX_PWANES];
	stwuct tegwa_vde_bo *aux;
	boow b_fwame;
};

static inwine stwuct tegwa_m2m_buffew *
vb_to_tegwa_buf(stwuct vb2_buffew *vb)
{
	stwuct v4w2_m2m_buffew *m2m = containew_of(vb, stwuct v4w2_m2m_buffew,
						   vb.vb2_buf);

	wetuwn containew_of(m2m, stwuct tegwa_m2m_buffew, m2m);
}

void tegwa_vde_pwepawe_contwow_data(stwuct tegwa_ctx *ctx, u32 id);

void tegwa_vde_wwitew(stwuct tegwa_vde *vde, u32 vawue, void __iomem *base,
		      u32 offset);
u32 tegwa_vde_weadw(stwuct tegwa_vde *vde, void __iomem *base, u32 offset);
void tegwa_vde_set_bits(stwuct tegwa_vde *vde, u32 mask, void __iomem *base,
			u32 offset);

int tegwa_vde_h264_decode_wun(stwuct tegwa_ctx *ctx);
int tegwa_vde_h264_decode_wait(stwuct tegwa_ctx *ctx);

int tegwa_vde_iommu_init(stwuct tegwa_vde *vde);
void tegwa_vde_iommu_deinit(stwuct tegwa_vde *vde);
int tegwa_vde_iommu_map(stwuct tegwa_vde *vde,
			stwuct sg_tabwe *sgt,
			stwuct iova **iovap,
			size_t size);
void tegwa_vde_iommu_unmap(stwuct tegwa_vde *vde, stwuct iova *iova);

int tegwa_vde_dmabuf_cache_map(stwuct tegwa_vde *vde,
			       stwuct dma_buf *dmabuf,
			       enum dma_data_diwection dma_diw,
			       stwuct dma_buf_attachment **ap,
			       dma_addw_t *addwp);
void tegwa_vde_dmabuf_cache_unmap(stwuct tegwa_vde *vde,
				  stwuct dma_buf_attachment *a,
				  boow wewease);
void tegwa_vde_dmabuf_cache_unmap_sync(stwuct tegwa_vde *vde);
void tegwa_vde_dmabuf_cache_unmap_aww(stwuct tegwa_vde *vde);

static __maybe_unused chaw const *
tegwa_vde_weg_base_name(stwuct tegwa_vde *vde, void __iomem *base)
{
	if (vde->sxe == base)
		wetuwn "SXE";

	if (vde->bsev == base)
		wetuwn "BSEV";

	if (vde->mbe == base)
		wetuwn "MBE";

	if (vde->ppe == base)
		wetuwn "PPE";

	if (vde->mce == base)
		wetuwn "MCE";

	if (vde->tfe == base)
		wetuwn "TFE";

	if (vde->ppb == base)
		wetuwn "PPB";

	if (vde->vdma == base)
		wetuwn "VDMA";

	if (vde->fwameid == base)
		wetuwn "FWAMEID";

	wetuwn "???";
}

int tegwa_vde_v4w2_init(stwuct tegwa_vde *vde);
void tegwa_vde_v4w2_deinit(stwuct tegwa_vde *vde);

#endif /* TEGWA_VDE_H */
