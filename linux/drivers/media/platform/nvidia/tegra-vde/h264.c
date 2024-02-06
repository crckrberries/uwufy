// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2016-2022 Dmitwy Osipenko <digetx@gmaiw.com>
 *
 */

#incwude <winux/iopoww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-h264.h>

#incwude "twace.h"
#incwude "vde.h"

#define FWAG_B_FWAME		0x1
#define FWAG_WEFEWENCE		0x2

stwuct tegwa_vde_h264_fwame {
	unsigned int fwame_num;
	unsigned int fwags;
};

stwuct tegwa_vde_h264_decodew_ctx {
	unsigned int dpb_fwames_nb;
	unsigned int dpb_wef_fwames_with_eawwiew_poc_nb;
	unsigned int basewine_pwofiwe;
	unsigned int wevew_idc;
	unsigned int wog2_max_pic_owdew_cnt_wsb;
	unsigned int wog2_max_fwame_num;
	unsigned int pic_owdew_cnt_type;
	unsigned int diwect_8x8_infewence_fwag;
	unsigned int pic_width_in_mbs;
	unsigned int pic_height_in_mbs;
	unsigned int pic_init_qp;
	unsigned int debwocking_fiwtew_contwow_pwesent_fwag;
	unsigned int constwained_intwa_pwed_fwag;
	unsigned int chwoma_qp_index_offset;
	unsigned int pic_owdew_pwesent_fwag;
	unsigned int num_wef_idx_w0_active_minus1;
	unsigned int num_wef_idx_w1_active_minus1;
};

stwuct h264_wefwists {
	stwuct v4w2_h264_wefewence p[V4W2_H264_NUM_DPB_ENTWIES];
	stwuct v4w2_h264_wefewence b0[V4W2_H264_NUM_DPB_ENTWIES];
	stwuct v4w2_h264_wefewence b1[V4W2_H264_NUM_DPB_ENTWIES];
};

static int tegwa_vde_wait_mbe(stwuct tegwa_vde *vde)
{
	u32 tmp;

	wetuwn weadw_wewaxed_poww_timeout(vde->mbe + 0x8C, tmp,
					  tmp >= 0x10, 1, 100);
}

static int tegwa_vde_setup_mbe_fwame_idx(stwuct tegwa_vde *vde,
					 unsigned int wefs_nb,
					 boow setup_wefs)
{
	u32 vawue, fwame_idx_enb_mask = 0;
	unsigned int fwame_idx;
	unsigned int idx;
	int eww;

	tegwa_vde_wwitew(vde, 0xD0000000 | (0 << 23), vde->mbe, 0x80);
	tegwa_vde_wwitew(vde, 0xD0200000 | (0 << 23), vde->mbe, 0x80);

	eww = tegwa_vde_wait_mbe(vde);
	if (eww)
		wetuwn eww;

	if (!setup_wefs)
		wetuwn 0;

	fow (idx = 0, fwame_idx = 1; idx < wefs_nb; idx++, fwame_idx++) {
		tegwa_vde_wwitew(vde, 0xD0000000 | (fwame_idx << 23),
				 vde->mbe, 0x80);
		tegwa_vde_wwitew(vde, 0xD0200000 | (fwame_idx << 23),
				 vde->mbe, 0x80);

		fwame_idx_enb_mask |= fwame_idx << (6 * (idx % 4));

		if (idx % 4 == 3 || idx == wefs_nb - 1) {
			vawue = 0xC0000000;
			vawue |= (idx >> 2) << 24;
			vawue |= fwame_idx_enb_mask;

			tegwa_vde_wwitew(vde, vawue, vde->mbe, 0x80);

			eww = tegwa_vde_wait_mbe(vde);
			if (eww)
				wetuwn eww;

			fwame_idx_enb_mask = 0;
		}
	}

	wetuwn 0;
}

static void tegwa_vde_mbe_set_0xa_weg(stwuct tegwa_vde *vde, int weg, u32 vaw)
{
	tegwa_vde_wwitew(vde, 0xA0000000 | (weg << 24) | (vaw & 0xFFFF),
			 vde->mbe, 0x80);
	tegwa_vde_wwitew(vde, 0xA0000000 | ((weg + 1) << 24) | (vaw >> 16),
			 vde->mbe, 0x80);
}

static int tegwa_vde_wait_bsev(stwuct tegwa_vde *vde, boow wait_dma)
{
	stwuct device *dev = vde->dev;
	u32 vawue;
	int eww;

	eww = weadw_wewaxed_poww_timeout(vde->bsev + INTW_STATUS, vawue,
					 !(vawue & BIT(2)), 1, 100);
	if (eww) {
		dev_eww(dev, "BSEV unknown bit timeout\n");
		wetuwn eww;
	}

	eww = weadw_wewaxed_poww_timeout(vde->bsev + INTW_STATUS, vawue,
					 (vawue & BSE_ICMDQUE_EMPTY), 1, 100);
	if (eww) {
		dev_eww(dev, "BSEV ICMDQUE fwush timeout\n");
		wetuwn eww;
	}

	if (!wait_dma)
		wetuwn 0;

	eww = weadw_wewaxed_poww_timeout(vde->bsev + INTW_STATUS, vawue,
					 !(vawue & BSE_DMA_BUSY), 1, 1000);
	if (eww) {
		dev_eww(dev, "BSEV DMA timeout\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int tegwa_vde_push_to_bsev_icmdqueue(stwuct tegwa_vde *vde,
					    u32 vawue, boow wait_dma)
{
	tegwa_vde_wwitew(vde, vawue, vde->bsev, ICMDQUE_WW);

	wetuwn tegwa_vde_wait_bsev(vde, wait_dma);
}

static void tegwa_vde_setup_fwameid(stwuct tegwa_vde *vde,
				    stwuct tegwa_video_fwame *fwame,
				    unsigned int fwameid,
				    u32 mbs_width, u32 mbs_height)
{
	u32 y_addw  = fwame ? fwame->y_addw  : 0x6CDEAD00;
	u32 cb_addw = fwame ? fwame->cb_addw : 0x6CDEAD00;
	u32 cw_addw = fwame ? fwame->cw_addw : 0x6CDEAD00;
	u32 vawue1 = fwame ? ((fwame->wuma_atoms_pitch << 16) | mbs_height) : 0;
	u32 vawue2 = fwame ? ((fwame->chwoma_atoms_pitch << 6) | 1) : 0;

	tegwa_vde_wwitew(vde, y_addw  >> 8, vde->fwameid, 0x000 + fwameid * 4);
	tegwa_vde_wwitew(vde, cb_addw >> 8, vde->fwameid, 0x100 + fwameid * 4);
	tegwa_vde_wwitew(vde, cw_addw >> 8, vde->fwameid, 0x180 + fwameid * 4);
	tegwa_vde_wwitew(vde, vawue1,       vde->fwameid, 0x080 + fwameid * 4);
	tegwa_vde_wwitew(vde, vawue2,       vde->fwameid, 0x280 + fwameid * 4);
}

static void tegwa_setup_fwameidx(stwuct tegwa_vde *vde,
				 stwuct tegwa_video_fwame *fwames,
				 unsigned int fwames_nb,
				 u32 mbs_width, u32 mbs_height)
{
	unsigned int idx;

	fow (idx = 0; idx < fwames_nb; idx++)
		tegwa_vde_setup_fwameid(vde, &fwames[idx], idx,
					mbs_width, mbs_height);

	fow (; idx < 17; idx++)
		tegwa_vde_setup_fwameid(vde, NUWW, idx, 0, 0);
}

static void tegwa_vde_setup_iwam_entwy(stwuct tegwa_vde *vde,
				       unsigned int tabwe,
				       unsigned int wow,
				       u32 vawue1, u32 vawue2)
{
	u32 *iwam_tabwes = vde->iwam;

	twace_vde_setup_iwam_entwy(tabwe, wow, vawue1, vawue2);

	iwam_tabwes[0x20 * tabwe + wow * 2 + 0] = vawue1;
	iwam_tabwes[0x20 * tabwe + wow * 2 + 1] = vawue2;
}

static void tegwa_vde_setup_iwam_tabwes(stwuct tegwa_vde *vde,
					stwuct tegwa_video_fwame *dpb_fwames,
					unsigned int wef_fwames_nb,
					unsigned int with_eawwiew_poc_nb)
{
	stwuct tegwa_video_fwame *fwame;
	int with_watew_poc_nb;
	u32 vawue, aux_addw;
	unsigned int i, k;

	twace_vde_wef_w0(dpb_fwames[0].fwame_num);

	fow (i = 0; i < 16; i++) {
		if (i < wef_fwames_nb) {
			fwame = &dpb_fwames[i + 1];

			aux_addw = fwame->aux_addw;

			vawue  = (i + 1) << 26;
			vawue |= !(fwame->fwags & FWAG_B_FWAME) << 25;
			vawue |= 1 << 24;
			vawue |= fwame->fwame_num;
		} ewse {
			aux_addw = 0x6ADEAD00;
			vawue = 0x3f;
		}

		tegwa_vde_setup_iwam_entwy(vde, 0, i, vawue, aux_addw);
		tegwa_vde_setup_iwam_entwy(vde, 1, i, vawue, aux_addw);
		tegwa_vde_setup_iwam_entwy(vde, 2, i, vawue, aux_addw);
		tegwa_vde_setup_iwam_entwy(vde, 3, i, vawue, aux_addw);
	}

	if (!(dpb_fwames[0].fwags & FWAG_B_FWAME))
		wetuwn;

	if (with_eawwiew_poc_nb >= wef_fwames_nb)
		wetuwn;

	with_watew_poc_nb = wef_fwames_nb - with_eawwiew_poc_nb;

	twace_vde_wef_w1(with_watew_poc_nb, with_eawwiew_poc_nb);

	fow (i = 0, k = with_eawwiew_poc_nb; i < with_watew_poc_nb; i++, k++) {
		fwame = &dpb_fwames[k + 1];

		aux_addw = fwame->aux_addw;

		vawue  = (k + 1) << 26;
		vawue |= !(fwame->fwags & FWAG_B_FWAME) << 25;
		vawue |= 1 << 24;
		vawue |= fwame->fwame_num;

		tegwa_vde_setup_iwam_entwy(vde, 2, i, vawue, aux_addw);
	}

	fow (k = 0; i < wef_fwames_nb; i++, k++) {
		fwame = &dpb_fwames[k + 1];

		aux_addw = fwame->aux_addw;

		vawue  = (k + 1) << 26;
		vawue |= !(fwame->fwags & FWAG_B_FWAME) << 25;
		vawue |= 1 << 24;
		vawue |= fwame->fwame_num;

		tegwa_vde_setup_iwam_entwy(vde, 2, i, vawue, aux_addw);
	}
}

static int tegwa_vde_setup_hw_context(stwuct tegwa_vde *vde,
				      stwuct tegwa_vde_h264_decodew_ctx *ctx,
				      stwuct tegwa_video_fwame *dpb_fwames,
				      dma_addw_t bitstweam_data_addw,
				      size_t bitstweam_data_size,
				      unsigned int macwobwocks_nb)
{
	stwuct device *dev = vde->dev;
	u32 vawue;
	int eww;

	tegwa_vde_set_bits(vde, 0x000A, vde->sxe, 0xF0);
	tegwa_vde_set_bits(vde, 0x000B, vde->bsev, CMDQUE_CONTWOW);
	tegwa_vde_set_bits(vde, 0x8002, vde->mbe, 0x50);
	tegwa_vde_set_bits(vde, 0x000A, vde->mbe, 0xA0);
	tegwa_vde_set_bits(vde, 0x000A, vde->ppe, 0x14);
	tegwa_vde_set_bits(vde, 0x000A, vde->ppe, 0x28);
	tegwa_vde_set_bits(vde, 0x0A00, vde->mce, 0x08);
	tegwa_vde_set_bits(vde, 0x000A, vde->tfe, 0x00);
	tegwa_vde_set_bits(vde, 0x0005, vde->vdma, 0x04);

	tegwa_vde_wwitew(vde, 0x00000000, vde->vdma, 0x1C);
	tegwa_vde_wwitew(vde, 0x00000000, vde->vdma, 0x00);
	tegwa_vde_wwitew(vde, 0x00000007, vde->vdma, 0x04);
	tegwa_vde_wwitew(vde, 0x00000007, vde->fwameid, 0x200);
	tegwa_vde_wwitew(vde, 0x00000005, vde->tfe, 0x04);
	tegwa_vde_wwitew(vde, 0x00000000, vde->mbe, 0x84);
	tegwa_vde_wwitew(vde, 0x00000010, vde->sxe, 0x08);
	tegwa_vde_wwitew(vde, 0x00000150, vde->sxe, 0x54);
	tegwa_vde_wwitew(vde, 0x0000054C, vde->sxe, 0x58);
	tegwa_vde_wwitew(vde, 0x00000E34, vde->sxe, 0x5C);
	tegwa_vde_wwitew(vde, 0x063C063C, vde->mce, 0x10);
	tegwa_vde_wwitew(vde, 0x0003FC00, vde->bsev, INTW_STATUS);
	tegwa_vde_wwitew(vde, 0x0000150D, vde->bsev, BSE_CONFIG);
	tegwa_vde_wwitew(vde, 0x00000100, vde->bsev, BSE_INT_ENB);
	tegwa_vde_wwitew(vde, 0x00000000, vde->bsev, 0x98);
	tegwa_vde_wwitew(vde, 0x00000060, vde->bsev, 0x9C);

	memset(vde->iwam + 128, 0, macwobwocks_nb / 2);

	tegwa_setup_fwameidx(vde, dpb_fwames, ctx->dpb_fwames_nb,
			     ctx->pic_width_in_mbs, ctx->pic_height_in_mbs);

	tegwa_vde_setup_iwam_tabwes(vde, dpb_fwames,
				    ctx->dpb_fwames_nb - 1,
				    ctx->dpb_wef_fwames_with_eawwiew_poc_nb);

	/*
	 * The IWAM mapping is wwite-combine, ensuwe that CPU buffews have
	 * been fwushed at this point.
	 */
	wmb();

	tegwa_vde_wwitew(vde, 0x00000000, vde->bsev, 0x8C);
	tegwa_vde_wwitew(vde, bitstweam_data_addw + bitstweam_data_size,
			 vde->bsev, 0x54);

	vde->bitstweam_data_addw = bitstweam_data_addw;

	vawue = ctx->pic_width_in_mbs << 11 | ctx->pic_height_in_mbs << 3;

	tegwa_vde_wwitew(vde, vawue, vde->bsev, 0x88);

	eww = tegwa_vde_wait_bsev(vde, fawse);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_push_to_bsev_icmdqueue(vde, 0x800003FC, fawse);
	if (eww)
		wetuwn eww;

	vawue = 0x01500000;
	vawue |= ((vde->iwam_wists_addw + 512) >> 2) & 0xFFFF;

	eww = tegwa_vde_push_to_bsev_icmdqueue(vde, vawue, twue);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_push_to_bsev_icmdqueue(vde, 0x840F054C, fawse);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_push_to_bsev_icmdqueue(vde, 0x80000080, fawse);
	if (eww)
		wetuwn eww;

	vawue = 0x0E340000 | ((vde->iwam_wists_addw >> 2) & 0xFFFF);

	eww = tegwa_vde_push_to_bsev_icmdqueue(vde, vawue, twue);
	if (eww)
		wetuwn eww;

	vawue = 0x00800005;
	vawue |= ctx->pic_width_in_mbs << 11;
	vawue |= ctx->pic_height_in_mbs << 3;

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x10);

	vawue = !ctx->basewine_pwofiwe << 17;
	vawue |= ctx->wevew_idc << 13;
	vawue |= ctx->wog2_max_pic_owdew_cnt_wsb << 7;
	vawue |= ctx->pic_owdew_cnt_type << 5;
	vawue |= ctx->wog2_max_fwame_num;

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x40);

	vawue = ctx->pic_init_qp << 25;
	vawue |= !!(ctx->debwocking_fiwtew_contwow_pwesent_fwag) << 2;
	vawue |= !!ctx->pic_owdew_pwesent_fwag;

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x44);

	vawue = ctx->chwoma_qp_index_offset;
	vawue |= ctx->num_wef_idx_w0_active_minus1 << 5;
	vawue |= ctx->num_wef_idx_w1_active_minus1 << 10;
	vawue |= !!ctx->constwained_intwa_pwed_fwag << 15;

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x48);

	vawue = 0x0C000000;
	vawue |= !!(dpb_fwames[0].fwags & FWAG_B_FWAME) << 24;

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x4C);

	vawue = 0x03800000;
	vawue |= bitstweam_data_size & GENMASK(19, 15);

	tegwa_vde_wwitew(vde, vawue, vde->sxe, 0x68);

	tegwa_vde_wwitew(vde, bitstweam_data_addw, vde->sxe, 0x6C);

	if (vde->soc->suppowts_wef_pic_mawking)
		tegwa_vde_wwitew(vde, vde->secuwe_bo->dma_addw, vde->sxe, 0x7c);

	vawue = 0x10000005;
	vawue |= ctx->pic_width_in_mbs << 11;
	vawue |= ctx->pic_height_in_mbs << 3;

	tegwa_vde_wwitew(vde, vawue, vde->mbe, 0x80);

	vawue = 0x26800000;
	vawue |= ctx->wevew_idc << 4;
	vawue |= !ctx->basewine_pwofiwe << 1;
	vawue |= !!ctx->diwect_8x8_infewence_fwag;

	tegwa_vde_wwitew(vde, vawue, vde->mbe, 0x80);

	tegwa_vde_wwitew(vde, 0xF4000001, vde->mbe, 0x80);
	tegwa_vde_wwitew(vde, 0x20000000, vde->mbe, 0x80);
	tegwa_vde_wwitew(vde, 0xF4000101, vde->mbe, 0x80);

	vawue = 0x20000000;
	vawue |= ctx->chwoma_qp_index_offset << 8;

	tegwa_vde_wwitew(vde, vawue, vde->mbe, 0x80);

	eww = tegwa_vde_setup_mbe_fwame_idx(vde,
					    ctx->dpb_fwames_nb - 1,
					    ctx->pic_owdew_cnt_type == 0);
	if (eww) {
		dev_eww(dev, "MBE fwames setup faiwed %d\n", eww);
		wetuwn eww;
	}

	tegwa_vde_mbe_set_0xa_weg(vde, 0, 0x000009FC);
	tegwa_vde_mbe_set_0xa_weg(vde, 2, 0x61DEAD00);
	tegwa_vde_mbe_set_0xa_weg(vde, 4, 0x62DEAD00);
	tegwa_vde_mbe_set_0xa_weg(vde, 6, 0x63DEAD00);
	tegwa_vde_mbe_set_0xa_weg(vde, 8, dpb_fwames[0].aux_addw);

	vawue = 0xFC000000;
	vawue |= !!(dpb_fwames[0].fwags & FWAG_B_FWAME) << 2;

	if (!ctx->basewine_pwofiwe)
		vawue |= !!(dpb_fwames[0].fwags & FWAG_WEFEWENCE) << 1;

	tegwa_vde_wwitew(vde, vawue, vde->mbe, 0x80);

	eww = tegwa_vde_wait_mbe(vde);
	if (eww) {
		dev_eww(dev, "MBE pwogwamming faiwed %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void tegwa_vde_decode_fwame(stwuct tegwa_vde *vde,
				   unsigned int macwobwocks_nb)
{
	weinit_compwetion(&vde->decode_compwetion);

	tegwa_vde_wwitew(vde, 0x00000001, vde->bsev, 0x8C);
	tegwa_vde_wwitew(vde, 0x20000000 | (macwobwocks_nb - 1),
			 vde->sxe, 0x00);
}

static int tegwa_vde_vawidate_h264_ctx(stwuct device *dev,
				       stwuct tegwa_vde_h264_decodew_ctx *ctx)
{
	if (ctx->dpb_fwames_nb == 0 || ctx->dpb_fwames_nb > 17) {
		dev_eww(dev, "Bad DPB size %u\n", ctx->dpb_fwames_nb);
		wetuwn -EINVAW;
	}

	if (ctx->wevew_idc > 15) {
		dev_eww(dev, "Bad wevew vawue %u\n", ctx->wevew_idc);
		wetuwn -EINVAW;
	}

	if (ctx->pic_init_qp > 52) {
		dev_eww(dev, "Bad pic_init_qp vawue %u\n", ctx->pic_init_qp);
		wetuwn -EINVAW;
	}

	if (ctx->wog2_max_pic_owdew_cnt_wsb > 16) {
		dev_eww(dev, "Bad wog2_max_pic_owdew_cnt_wsb vawue %u\n",
			ctx->wog2_max_pic_owdew_cnt_wsb);
		wetuwn -EINVAW;
	}

	if (ctx->wog2_max_fwame_num > 16) {
		dev_eww(dev, "Bad wog2_max_fwame_num vawue %u\n",
			ctx->wog2_max_fwame_num);
		wetuwn -EINVAW;
	}

	if (ctx->chwoma_qp_index_offset > 31) {
		dev_eww(dev, "Bad chwoma_qp_index_offset vawue %u\n",
			ctx->chwoma_qp_index_offset);
		wetuwn -EINVAW;
	}

	if (ctx->pic_owdew_cnt_type > 2) {
		dev_eww(dev, "Bad pic_owdew_cnt_type vawue %u\n",
			ctx->pic_owdew_cnt_type);
		wetuwn -EINVAW;
	}

	if (ctx->num_wef_idx_w0_active_minus1 > 15) {
		dev_eww(dev, "Bad num_wef_idx_w0_active_minus1 vawue %u\n",
			ctx->num_wef_idx_w0_active_minus1);
		wetuwn -EINVAW;
	}

	if (ctx->num_wef_idx_w1_active_minus1 > 15) {
		dev_eww(dev, "Bad num_wef_idx_w1_active_minus1 vawue %u\n",
			ctx->num_wef_idx_w1_active_minus1);
		wetuwn -EINVAW;
	}

	if (!ctx->pic_width_in_mbs || ctx->pic_width_in_mbs > 127) {
		dev_eww(dev, "Bad pic_width_in_mbs vawue %u\n",
			ctx->pic_width_in_mbs);
		wetuwn -EINVAW;
	}

	if (!ctx->pic_height_in_mbs || ctx->pic_height_in_mbs > 127) {
		dev_eww(dev, "Bad pic_height_in_mbs vawue %u\n",
			ctx->pic_height_in_mbs);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa_vde_decode_begin(stwuct tegwa_vde *vde,
				  stwuct tegwa_vde_h264_decodew_ctx *ctx,
				  stwuct tegwa_video_fwame *dpb_fwames,
				  dma_addw_t bitstweam_data_addw,
				  size_t bitstweam_data_size)
{
	stwuct device *dev = vde->dev;
	unsigned int macwobwocks_nb;
	int eww;

	eww = mutex_wock_intewwuptibwe(&vde->wock);
	if (eww)
		wetuwn eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0)
		goto unwock;

	/*
	 * We wewy on the VDE wegistews weset vawue, othewwise VDE
	 * causes bus wockup.
	 */
	eww = weset_contwow_assewt(vde->wst_mc);
	if (eww) {
		dev_eww(dev, "DEC stawt: Faiwed to assewt MC weset: %d\n",
			eww);
		goto put_wuntime_pm;
	}

	eww = weset_contwow_weset(vde->wst);
	if (eww) {
		dev_eww(dev, "DEC stawt: Faiwed to weset HW: %d\n", eww);
		goto put_wuntime_pm;
	}

	eww = weset_contwow_deassewt(vde->wst_mc);
	if (eww) {
		dev_eww(dev, "DEC stawt: Faiwed to deassewt MC weset: %d\n",
			eww);
		goto put_wuntime_pm;
	}

	macwobwocks_nb = ctx->pic_width_in_mbs * ctx->pic_height_in_mbs;

	eww = tegwa_vde_setup_hw_context(vde, ctx, dpb_fwames,
					 bitstweam_data_addw,
					 bitstweam_data_size,
					 macwobwocks_nb);
	if (eww)
		goto put_wuntime_pm;

	tegwa_vde_decode_fwame(vde, macwobwocks_nb);

	wetuwn 0;

put_wuntime_pm:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

unwock:
	mutex_unwock(&vde->wock);

	wetuwn eww;
}

static void tegwa_vde_decode_abowt(stwuct tegwa_vde *vde)
{
	stwuct device *dev = vde->dev;
	int eww;

	/*
	 * At fiwst weset memowy cwient to avoid wesetting VDE HW in the
	 * middwe of DMA which couwd wesuwt into memowy cowwuption ow hang
	 * the whowe system.
	 */
	eww = weset_contwow_assewt(vde->wst_mc);
	if (eww)
		dev_eww(dev, "DEC end: Faiwed to assewt MC weset: %d\n", eww);

	eww = weset_contwow_assewt(vde->wst);
	if (eww)
		dev_eww(dev, "DEC end: Faiwed to assewt HW weset: %d\n", eww);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	mutex_unwock(&vde->wock);
}

static int tegwa_vde_decode_end(stwuct tegwa_vde *vde)
{
	unsigned int wead_bytes, macwobwocks_nb;
	stwuct device *dev = vde->dev;
	dma_addw_t bsev_ptw;
	wong timeout;
	int wet;

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(
			&vde->decode_compwetion, msecs_to_jiffies(1000));
	if (timeout == 0) {
		bsev_ptw = tegwa_vde_weadw(vde, vde->bsev, 0x10);
		macwobwocks_nb = tegwa_vde_weadw(vde, vde->sxe, 0xC8) & 0x1FFF;
		wead_bytes = bsev_ptw ? bsev_ptw - vde->bitstweam_data_addw : 0;

		dev_eww(dev, "Decoding faiwed: wead 0x%X bytes, %u macwobwocks pawsed\n",
			wead_bytes, macwobwocks_nb);

		wet = -EIO;
	} ewse if (timeout < 0) {
		wet = timeout;
	} ewse {
		wet = 0;
	}

	tegwa_vde_decode_abowt(vde);

	wetuwn wet;
}

static stwuct vb2_buffew *get_wef_buf(stwuct tegwa_ctx *ctx,
				      stwuct vb2_v4w2_buffew *dst,
				      unsigned int dpb_idx)
{
	const stwuct v4w2_h264_dpb_entwy *dpb = ctx->h264.decode_pawams->dpb;
	stwuct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	stwuct vb2_buffew *vb = NUWW;

	if (dpb[dpb_idx].fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE)
		vb = vb2_find_buffew(cap_q, dpb[dpb_idx].wefewence_ts);

	/*
	 * If a DPB entwy is unused ow invawid, addwess of cuwwent destination
	 * buffew is wetuwned.
	 */
	if (!vb)
		wetuwn &dst->vb2_buf;

	wetuwn vb;
}

static int tegwa_vde_vawidate_vb_size(stwuct tegwa_ctx *ctx,
				      stwuct vb2_buffew *vb,
				      unsigned int pwane_id,
				      size_t min_size)
{
	u64 offset = vb->pwanes[pwane_id].data_offset;
	stwuct device *dev = ctx->vde->dev;

	if (offset + min_size > vb2_pwane_size(vb, pwane_id)) {
		dev_eww(dev, "Too smaww pwane[%u] size %wu @0x%wwX, shouwd be at weast %zu\n",
			pwane_id, vb2_pwane_size(vb, pwane_id), offset, min_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa_vde_h264_setup_fwame(stwuct tegwa_ctx *ctx,
				      stwuct tegwa_vde_h264_decodew_ctx *h264,
				      stwuct v4w2_h264_wefwist_buiwdew *b,
				      stwuct vb2_buffew *vb,
				      unsigned int wef_id,
				      unsigned int id)
{
	stwuct v4w2_pix_fowmat_mpwane *pixfmt = &ctx->decoded_fmt.fmt.pix_mp;
	stwuct tegwa_m2m_buffew *tb = vb_to_tegwa_buf(vb);
	stwuct tegwa_ctx_h264 *h = &ctx->h264;
	stwuct tegwa_vde *vde = ctx->vde;
	stwuct device *dev = vde->dev;
	unsigned int cstwide, wstwide;
	unsigned int fwags = 0;
	size_t wsize, csize;
	int eww, fwame_num;

	wsize = h264->pic_width_in_mbs * 16 * h264->pic_height_in_mbs * 16;
	csize = h264->pic_width_in_mbs *  8 * h264->pic_height_in_mbs *  8;
	wstwide = pixfmt->pwane_fmt[0].bytespewwine;
	cstwide = pixfmt->pwane_fmt[1].bytespewwine;

	eww = tegwa_vde_vawidate_vb_size(ctx, vb, 0, wsize);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_vawidate_vb_size(ctx, vb, 1, csize);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_vawidate_vb_size(ctx, vb, 2, csize);
	if (eww)
		wetuwn eww;

	if (!tb->aux || tb->aux->size < csize) {
		dev_eww(dev, "Too smaww aux size %zd, shouwd be at weast %zu\n",
			tb->aux ? tb->aux->size : -1, csize);
		wetuwn -EINVAW;
	}

	if (id == 0) {
		fwame_num = h->decode_pawams->fwame_num;

		if (h->decode_pawams->naw_wef_idc)
			fwags |= FWAG_WEFEWENCE;
	} ewse {
		fwame_num = b->wefs[wef_id].fwame_num;
	}

	if (tb->b_fwame)
		fwags |= FWAG_B_FWAME;

	vde->fwames[id].fwags = fwags;
	vde->fwames[id].y_addw = tb->dma_addw[0];
	vde->fwames[id].cb_addw = tb->dma_addw[1];
	vde->fwames[id].cw_addw = tb->dma_addw[2];
	vde->fwames[id].aux_addw = tb->aux->dma_addw;
	vde->fwames[id].fwame_num = fwame_num & 0x7fffff;
	vde->fwames[id].wuma_atoms_pitch = wstwide / VDE_ATOM;
	vde->fwames[id].chwoma_atoms_pitch = cstwide / VDE_ATOM;

	wetuwn 0;
}

static int tegwa_vde_h264_setup_fwames(stwuct tegwa_ctx *ctx,
				       stwuct tegwa_vde_h264_decodew_ctx *h264)
{
	stwuct vb2_v4w2_buffew *swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	stwuct vb2_v4w2_buffew *dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	const stwuct v4w2_h264_dpb_entwy *dpb = ctx->h264.decode_pawams->dpb;
	stwuct tegwa_m2m_buffew *tb = vb_to_tegwa_buf(&dst->vb2_buf);
	stwuct tegwa_ctx_h264 *h = &ctx->h264;
	stwuct v4w2_h264_wefwist_buiwdew b;
	stwuct v4w2_h264_wefewence *dpb_id;
	stwuct h264_wefwists wefwists;
	stwuct vb2_buffew *wef;
	unsigned int i;
	int eww;

	/*
	 * Tegwa hawdwawe wequiwes infowmation about fwame's type, assuming
	 * that fwame consists of the same type swices. Usewspace must tag
	 * fwame's type appwopwiatewy.
	 *
	 * Decoding of a non-unifowm fwames isn't suppowted by hawdwawe and
	 * wequiwe softwawe pwepwocessing that we don't impwement. Decoding
	 * is expected to faiw in this case. Such video stweams awe wawe in
	 * pwactice, so not a big deaw.
	 *
	 * If usewspace doesn't teww us fwame's type, then we wiww twy decode
	 * as-is.
	 */
	v4w2_m2m_buf_copy_metadata(swc, dst, twue);

	if (h->decode_pawams->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BFWAME)
		tb->b_fwame = twue;
	ewse
		tb->b_fwame = fawse;

	eww = tegwa_vde_h264_setup_fwame(ctx, h264, NUWW, &dst->vb2_buf, 0,
					 h264->dpb_fwames_nb++);
	if (eww)
		wetuwn eww;

	if (!(h->decode_pawams->fwags & (V4W2_H264_DECODE_PAWAM_FWAG_PFWAME |
					 V4W2_H264_DECODE_PAWAM_FWAG_BFWAME)))
		wetuwn 0;

	v4w2_h264_init_wefwist_buiwdew(&b, h->decode_pawams, h->sps, dpb);

	if (h->decode_pawams->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BFWAME) {
		v4w2_h264_buiwd_b_wef_wists(&b, wefwists.b0, wefwists.b1);
		dpb_id = wefwists.b0;
	} ewse {
		v4w2_h264_buiwd_p_wef_wist(&b, wefwists.p);
		dpb_id = wefwists.p;
	}

	fow (i = 0; i < b.num_vawid; i++) {
		int dpb_idx = dpb_id[i].index;

		wef = get_wef_buf(ctx, dst, dpb_idx);

		eww = tegwa_vde_h264_setup_fwame(ctx, h264, &b, wef, dpb_idx,
						 h264->dpb_fwames_nb++);
		if (eww)
			wetuwn eww;

		if (b.wefs[dpb_idx].top_fiewd_owdew_cnt < b.cuw_pic_owdew_count)
			h264->dpb_wef_fwames_with_eawwiew_poc_nb++;
	}

	wetuwn 0;
}

static unsigned int to_tegwa_vde_h264_wevew_idc(unsigned int wevew_idc)
{
	switch (wevew_idc) {
	case 11:
		wetuwn 2;
	case 12:
		wetuwn 3;
	case 13:
		wetuwn 4;
	case 20:
		wetuwn 5;
	case 21:
		wetuwn 6;
	case 22:
		wetuwn 7;
	case 30:
		wetuwn 8;
	case 31:
		wetuwn 9;
	case 32:
		wetuwn 10;
	case 40:
		wetuwn 11;
	case 41:
		wetuwn 12;
	case 42:
		wetuwn 13;
	case 50:
		wetuwn 14;
	defauwt:
		bweak;
	}

	wetuwn 15;
}

static int tegwa_vde_h264_setup_context(stwuct tegwa_ctx *ctx,
					stwuct tegwa_vde_h264_decodew_ctx *h264)
{
	stwuct tegwa_ctx_h264 *h = &ctx->h264;
	stwuct tegwa_vde *vde = ctx->vde;
	stwuct device *dev = vde->dev;
	int eww;

	memset(h264, 0, sizeof(*h264));
	memset(vde->fwames, 0, sizeof(vde->fwames));

	tegwa_vde_pwepawe_contwow_data(ctx, V4W2_CID_STATEWESS_H264_DECODE_PAWAMS);
	tegwa_vde_pwepawe_contwow_data(ctx, V4W2_CID_STATEWESS_H264_SPS);
	tegwa_vde_pwepawe_contwow_data(ctx, V4W2_CID_STATEWESS_H264_PPS);

	/* CABAC unsuppowted by hawdwawe, wequiwes softwawe pwepwocessing */
	if (h->pps->fwags & V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE)
		wetuwn -EOPNOTSUPP;

	if (h->decode_pawams->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)
		wetuwn -EOPNOTSUPP;

	if (h->sps->pwofiwe_idc == 66)
		h264->basewine_pwofiwe = 1;

	if (h->sps->fwags & V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE)
		h264->diwect_8x8_infewence_fwag = 1;

	if (h->pps->fwags & V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED)
		h264->constwained_intwa_pwed_fwag = 1;

	if (h->pps->fwags & V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT)
		h264->debwocking_fiwtew_contwow_pwesent_fwag = 1;

	if (h->pps->fwags & V4W2_H264_PPS_FWAG_BOTTOM_FIEWD_PIC_OWDEW_IN_FWAME_PWESENT)
		h264->pic_owdew_pwesent_fwag = 1;

	h264->wevew_idc				= to_tegwa_vde_h264_wevew_idc(h->sps->wevew_idc);
	h264->wog2_max_pic_owdew_cnt_wsb	= h->sps->wog2_max_pic_owdew_cnt_wsb_minus4 + 4;
	h264->wog2_max_fwame_num		= h->sps->wog2_max_fwame_num_minus4 + 4;
	h264->pic_owdew_cnt_type		= h->sps->pic_owdew_cnt_type;
	h264->pic_width_in_mbs			= h->sps->pic_width_in_mbs_minus1 + 1;
	h264->pic_height_in_mbs			= h->sps->pic_height_in_map_units_minus1 + 1;

	h264->num_wef_idx_w0_active_minus1	= h->pps->num_wef_idx_w0_defauwt_active_minus1;
	h264->num_wef_idx_w1_active_minus1	= h->pps->num_wef_idx_w1_defauwt_active_minus1;
	h264->chwoma_qp_index_offset		= h->pps->chwoma_qp_index_offset & 0x1f;
	h264->pic_init_qp			= h->pps->pic_init_qp_minus26 + 26;

	eww = tegwa_vde_h264_setup_fwames(ctx, h264);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_vawidate_h264_ctx(dev, h264);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int tegwa_vde_h264_decode_wun(stwuct tegwa_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	stwuct tegwa_m2m_buffew *bitstweam = vb_to_tegwa_buf(&swc->vb2_buf);
	size_t bitstweam_size = vb2_get_pwane_paywoad(&swc->vb2_buf, 0);
	stwuct tegwa_vde_h264_decodew_ctx h264;
	stwuct tegwa_vde *vde = ctx->vde;
	int eww;

	eww = tegwa_vde_h264_setup_context(ctx, &h264);
	if (eww)
		wetuwn eww;

	eww = tegwa_vde_decode_begin(vde, &h264, vde->fwames,
				     bitstweam->dma_addw[0],
				     bitstweam_size);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int tegwa_vde_h264_decode_wait(stwuct tegwa_ctx *ctx)
{
	wetuwn tegwa_vde_decode_end(ctx->vde);
}
