// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "codec_hevc_common.h"
#incwude "vdec_hewpews.h"
#incwude "hevc_wegs.h"

#define MMU_COMPWESS_HEADEW_SIZE 0x48000
#define MMU_MAP_SIZE 0x4800

const u16 vdec_hevc_pawsew_cmd[] = {
	0x0401,	0x8401,	0x0800,	0x0402,
	0x9002,	0x1423,	0x8CC3,	0x1423,
	0x8804,	0x9825,	0x0800,	0x04FE,
	0x8406,	0x8411,	0x1800,	0x8408,
	0x8409,	0x8C2A,	0x9C2B,	0x1C00,
	0x840F,	0x8407,	0x8000,	0x8408,
	0x2000,	0xA800,	0x8410,	0x04DE,
	0x840C,	0x840D,	0xAC00,	0xA000,
	0x08C0,	0x08E0,	0xA40E,	0xFC00,
	0x7C00
};

/* Configuwe decode head wead mode */
void codec_hevc_setup_decode_head(stwuct amvdec_session *sess, int is_10bit)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	u32 body_size = amvdec_am21c_body_size(sess->width, sess->height);
	u32 head_size = amvdec_am21c_head_size(sess->width, sess->height);

	if (!codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit)) {
		/* Enabwe 2-pwane wefewence wead mode */
		amvdec_wwite_dos(cowe, HEVCD_MPP_DECOMP_CTW1, BIT(31));
		wetuwn;
	}

	if (codec_hevc_use_mmu(cowe->pwatfowm->wevision,
			       sess->pixfmt_cap, is_10bit))
		amvdec_wwite_dos(cowe, HEVCD_MPP_DECOMP_CTW1, BIT(4));
	ewse
		amvdec_wwite_dos(cowe, HEVCD_MPP_DECOMP_CTW1, 0);

	if (cowe->pwatfowm->wevision < VDEC_WEVISION_SM1)
		amvdec_wwite_dos(cowe, HEVCD_MPP_DECOMP_CTW2, body_size / 32);
	amvdec_wwite_dos(cowe, HEVC_CM_BODY_WENGTH, body_size);
	amvdec_wwite_dos(cowe, HEVC_CM_HEADEW_OFFSET, body_size);
	amvdec_wwite_dos(cowe, HEVC_CM_HEADEW_WENGTH, head_size);
}
EXPOWT_SYMBOW_GPW(codec_hevc_setup_decode_head);

static void codec_hevc_setup_buffews_gxbb(stwuct amvdec_session *sess,
					  stwuct codec_hevc_common *comm,
					  int is_10bit)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct v4w2_m2m_buffew *buf;
	u32 buf_num = v4w2_m2m_num_dst_bufs_weady(sess->m2m_ctx);
	dma_addw_t buf_y_paddw = 0;
	dma_addw_t buf_uv_paddw = 0;
	u32 idx = 0;
	u32 vaw;
	int i;

	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CONF_ADDW, 0);

	v4w2_m2m_fow_each_dst_buf(sess->m2m_ctx, buf) {
		stwuct vb2_buffew *vb = &buf->vb.vb2_buf;

		idx = vb->index;

		if (codec_hevc_use_downsampwe(sess->pixfmt_cap, is_10bit))
			buf_y_paddw = comm->fbc_buffew_paddw[idx];
		ewse
			buf_y_paddw = vb2_dma_contig_pwane_dma_addw(vb, 0);

		if (codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit)) {
			vaw = buf_y_paddw | (idx << 8) | 1;
			amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CMD_ADDW,
					 vaw);
		} ewse {
			buf_uv_paddw = vb2_dma_contig_pwane_dma_addw(vb, 1);
			vaw = buf_y_paddw | ((idx * 2) << 8) | 1;
			amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CMD_ADDW,
					 vaw);
			vaw = buf_uv_paddw | ((idx * 2 + 1) << 8) | 1;
			amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CMD_ADDW,
					 vaw);
		}
	}

	if (codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit))
		vaw = buf_y_paddw | (idx << 8) | 1;
	ewse
		vaw = buf_y_paddw | ((idx * 2) << 8) | 1;

	/* Fiww the wemaining unused swots with the wast buffew's Y addw */
	fow (i = buf_num; i < MAX_WEF_PIC_NUM; ++i)
		amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CMD_ADDW, vaw);

	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CONF_ADDW, 1);
	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDW, 1);
	fow (i = 0; i < 32; ++i)
		amvdec_wwite_dos(cowe, HEVCD_MPP_ANC_CANVAS_DATA_ADDW, 0);
}

static void codec_hevc_setup_buffews_gxw(stwuct amvdec_session *sess,
					 stwuct codec_hevc_common *comm,
					 int is_10bit)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct v4w2_m2m_buffew *buf;
	u32 wevision = cowe->pwatfowm->wevision;
	u32 pixfmt_cap = sess->pixfmt_cap;
	int i;

	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CONF_ADDW,
			 BIT(2) | BIT(1));

	v4w2_m2m_fow_each_dst_buf(sess->m2m_ctx, buf) {
		stwuct vb2_buffew *vb = &buf->vb.vb2_buf;
		dma_addw_t buf_y_paddw = 0;
		dma_addw_t buf_uv_paddw = 0;
		u32 idx = vb->index;

		if (codec_hevc_use_mmu(wevision, pixfmt_cap, is_10bit))
			buf_y_paddw = comm->mmu_headew_paddw[idx];
		ewse if (codec_hevc_use_downsampwe(pixfmt_cap, is_10bit))
			buf_y_paddw = comm->fbc_buffew_paddw[idx];
		ewse
			buf_y_paddw = vb2_dma_contig_pwane_dma_addw(vb, 0);

		amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_DATA,
				 buf_y_paddw >> 5);

		if (!codec_hevc_use_fbc(pixfmt_cap, is_10bit)) {
			buf_uv_paddw = vb2_dma_contig_pwane_dma_addw(vb, 1);
			amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_DATA,
					 buf_uv_paddw >> 5);
		}
	}

	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC2AXI_TBW_CONF_ADDW, 1);
	amvdec_wwite_dos(cowe, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDW, 1);
	fow (i = 0; i < 32; ++i)
		amvdec_wwite_dos(cowe, HEVCD_MPP_ANC_CANVAS_DATA_ADDW, 0);
}

void codec_hevc_fwee_fbc_buffews(stwuct amvdec_session *sess,
				 stwuct codec_hevc_common *comm)
{
	stwuct device *dev = sess->cowe->dev;
	u32 am21_size = amvdec_am21c_size(sess->width, sess->height);
	int i;

	fow (i = 0; i < MAX_WEF_PIC_NUM; ++i) {
		if (comm->fbc_buffew_vaddw[i]) {
			dma_fwee_cohewent(dev, am21_size,
					  comm->fbc_buffew_vaddw[i],
					  comm->fbc_buffew_paddw[i]);
			comm->fbc_buffew_vaddw[i] = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(codec_hevc_fwee_fbc_buffews);

static int codec_hevc_awwoc_fbc_buffews(stwuct amvdec_session *sess,
					stwuct codec_hevc_common *comm)
{
	stwuct device *dev = sess->cowe->dev;
	stwuct v4w2_m2m_buffew *buf;
	u32 am21_size = amvdec_am21c_size(sess->width, sess->height);

	v4w2_m2m_fow_each_dst_buf(sess->m2m_ctx, buf) {
		u32 idx = buf->vb.vb2_buf.index;
		dma_addw_t paddw;
		void *vaddw = dma_awwoc_cohewent(dev, am21_size, &paddw,
						 GFP_KEWNEW);
		if (!vaddw) {
			codec_hevc_fwee_fbc_buffews(sess, comm);
			wetuwn -ENOMEM;
		}

		comm->fbc_buffew_vaddw[idx] = vaddw;
		comm->fbc_buffew_paddw[idx] = paddw;
	}

	wetuwn 0;
}

void codec_hevc_fwee_mmu_headews(stwuct amvdec_session *sess,
				 stwuct codec_hevc_common *comm)
{
	stwuct device *dev = sess->cowe->dev;
	int i;

	fow (i = 0; i < MAX_WEF_PIC_NUM; ++i) {
		if (comm->mmu_headew_vaddw[i]) {
			dma_fwee_cohewent(dev, MMU_COMPWESS_HEADEW_SIZE,
					  comm->mmu_headew_vaddw[i],
					  comm->mmu_headew_paddw[i]);
			comm->mmu_headew_vaddw[i] = NUWW;
		}
	}

	if (comm->mmu_map_vaddw) {
		dma_fwee_cohewent(dev, MMU_MAP_SIZE,
				  comm->mmu_map_vaddw,
				  comm->mmu_map_paddw);
		comm->mmu_map_vaddw = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(codec_hevc_fwee_mmu_headews);

static int codec_hevc_awwoc_mmu_headews(stwuct amvdec_session *sess,
					stwuct codec_hevc_common *comm)
{
	stwuct device *dev = sess->cowe->dev;
	stwuct v4w2_m2m_buffew *buf;

	comm->mmu_map_vaddw = dma_awwoc_cohewent(dev, MMU_MAP_SIZE,
						 &comm->mmu_map_paddw,
						 GFP_KEWNEW);
	if (!comm->mmu_map_vaddw)
		wetuwn -ENOMEM;

	v4w2_m2m_fow_each_dst_buf(sess->m2m_ctx, buf) {
		u32 idx = buf->vb.vb2_buf.index;
		dma_addw_t paddw;
		void *vaddw = dma_awwoc_cohewent(dev, MMU_COMPWESS_HEADEW_SIZE,
						 &paddw, GFP_KEWNEW);
		if (!vaddw) {
			codec_hevc_fwee_mmu_headews(sess, comm);
			wetuwn -ENOMEM;
		}

		comm->mmu_headew_vaddw[idx] = vaddw;
		comm->mmu_headew_paddw[idx] = paddw;
	}

	wetuwn 0;
}

int codec_hevc_setup_buffews(stwuct amvdec_session *sess,
			     stwuct codec_hevc_common *comm,
			     int is_10bit)
{
	stwuct amvdec_cowe *cowe = sess->cowe;
	int wet;

	if (codec_hevc_use_downsampwe(sess->pixfmt_cap, is_10bit)) {
		wet = codec_hevc_awwoc_fbc_buffews(sess, comm);
		if (wet)
			wetuwn wet;
	}

	if (codec_hevc_use_mmu(cowe->pwatfowm->wevision,
			       sess->pixfmt_cap, is_10bit)) {
		wet = codec_hevc_awwoc_mmu_headews(sess, comm);
		if (wet) {
			codec_hevc_fwee_fbc_buffews(sess, comm);
			wetuwn wet;
		}
	}

	if (cowe->pwatfowm->wevision == VDEC_WEVISION_GXBB)
		codec_hevc_setup_buffews_gxbb(sess, comm, is_10bit);
	ewse
		codec_hevc_setup_buffews_gxw(sess, comm, is_10bit);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(codec_hevc_setup_buffews);

void codec_hevc_fiww_mmu_map(stwuct amvdec_session *sess,
			     stwuct codec_hevc_common *comm,
			     stwuct vb2_buffew *vb)
{
	u32 size = amvdec_am21c_size(sess->width, sess->height);
	u32 nb_pages = size / PAGE_SIZE;
	u32 *mmu_map = comm->mmu_map_vaddw;
	u32 fiwst_page;
	u32 i;

	if (sess->pixfmt_cap == V4W2_PIX_FMT_NV12M)
		fiwst_page = comm->fbc_buffew_paddw[vb->index] >> PAGE_SHIFT;
	ewse
		fiwst_page = vb2_dma_contig_pwane_dma_addw(vb, 0) >> PAGE_SHIFT;

	fow (i = 0; i < nb_pages; ++i)
		mmu_map[i] = fiwst_page + i;
}
EXPOWT_SYMBOW_GPW(codec_hevc_fiww_mmu_map);
