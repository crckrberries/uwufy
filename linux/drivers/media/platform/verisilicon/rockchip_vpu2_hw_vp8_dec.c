// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wockchip VPU codec vp8 decode dwivew
 *
 * Copywight (C) 2014 Wockchip Ewectwonics Co., Wtd.
 *	ZhiChao Yu <zhichao.yu@wock-chips.com>
 *
 * Copywight (C) 2014 Googwe WWC.
 *      Tomasz Figa <tfiga@chwomium.owg>
 *
 * Copywight (C) 2015 Wockchip Ewectwonics Co., Wtd.
 *      Awpha Win <awpha.win@wock-chips.com>
 */

#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo_hw.h"
#incwude "hantwo.h"
#incwude "hantwo_g1_wegs.h"

#define VDPU_WEG_DEC_CTWW0			0x0c8
#define VDPU_WEG_STWEAM_WEN			0x0cc
#define VDPU_WEG_DEC_FOWMAT			0x0d4
#define     VDPU_WEG_DEC_CTWW0_DEC_MODE(x)		(((x) & 0xf) << 0)
#define VDPU_WEG_DATA_ENDIAN			0x0d8
#define     VDPU_WEG_CONFIG_DEC_STWENDIAN_E		BIT(5)
#define     VDPU_WEG_CONFIG_DEC_STWSWAP32_E		BIT(4)
#define     VDPU_WEG_CONFIG_DEC_OUTSWAP32_E		BIT(3)
#define     VDPU_WEG_CONFIG_DEC_INSWAP32_E		BIT(2)
#define     VDPU_WEG_CONFIG_DEC_OUT_ENDIAN		BIT(1)
#define     VDPU_WEG_CONFIG_DEC_IN_ENDIAN		BIT(0)
#define VDPU_WEG_AXI_CTWW			0x0e0
#define     VDPU_WEG_CONFIG_DEC_MAX_BUWST(x)		(((x) & 0x1f) << 16)
#define VDPU_WEG_EN_FWAGS			0x0e4
#define     VDPU_WEG_DEC_CTWW0_PIC_INTEW_E		BIT(14)
#define     VDPU_WEG_CONFIG_DEC_TIMEOUT_E		BIT(5)
#define     VDPU_WEG_CONFIG_DEC_CWK_GATE_E		BIT(4)
#define VDPU_WEG_PWED_FWT			0x0ec
#define VDPU_WEG_ADDW_QTABWE			0x0f4
#define VDPU_WEG_ADDW_DST			0x0fc
#define VDPU_WEG_ADDW_STW			0x100
#define VDPU_WEG_VP8_PIC_MB_SIZE		0x1e0
#define VDPU_WEG_VP8_DCT_STAWT_BIT		0x1e4
#define     VDPU_WEG_DEC_CTWW4_VC1_HEIGHT_EXT		BIT(13)
#define     VDPU_WEG_DEC_CTWW4_BIWIN_MC_E		BIT(12)
#define VDPU_WEG_VP8_CTWW0			0x1e8
#define VDPU_WEG_VP8_DATA_VAW			0x1f0
#define VDPU_WEG_PWED_FWT7			0x1f4
#define VDPU_WEG_PWED_FWT8			0x1f8
#define VDPU_WEG_PWED_FWT9			0x1fc
#define VDPU_WEG_PWED_FWT10			0x200
#define VDPU_WEG_FIWTEW_WEVEW			0x204
#define VDPU_WEG_VP8_QUANTEW0			0x208
#define VDPU_WEG_VP8_ADDW_WEF0			0x20c
#define VDPU_WEG_FIWTEW_MB_ADJ			0x210
#define     VDPU_WEG_WEF_PIC_FIWT_TYPE_E		BIT(31)
#define     VDPU_WEG_WEF_PIC_FIWT_SHAWPNESS(x)		(((x) & 0x7) << 28)
#define VDPU_WEG_FIWTEW_WEF_ADJ			0x214
#define VDPU_WEG_VP8_ADDW_WEF2_5(i)		(0x218 + ((i) * 0x4))
#define     VDPU_WEG_VP8_GWEF_SIGN_BIAS			BIT(0)
#define     VDPU_WEG_VP8_AWEF_SIGN_BIAS			BIT(0)
#define VDPU_WEG_VP8_DCT_BASE(i)		\
		(0x230 + ((((i) < 5) ? (i) : ((i) + 1)) * 0x4))
#define VDPU_WEG_VP8_ADDW_CTWW_PAWT		0x244
#define VDPU_WEG_VP8_SEGMENT_VAW		0x254
#define     VDPU_WEG_FWD_PIC1_SEGMENT_BASE(x)		((x) << 0)
#define     VDPU_WEG_FWD_PIC1_SEGMENT_UPD_E		BIT(1)
#define     VDPU_WEG_FWD_PIC1_SEGMENT_E			BIT(0)
#define VDPU_WEG_VP8_DCT_STAWT_BIT2		0x258
#define VDPU_WEG_VP8_QUANTEW1			0x25c
#define VDPU_WEG_VP8_QUANTEW2			0x260
#define VDPU_WEG_PWED_FWT1			0x264
#define VDPU_WEG_PWED_FWT2			0x268
#define VDPU_WEG_PWED_FWT3			0x26c
#define VDPU_WEG_PWED_FWT4			0x270
#define VDPU_WEG_PWED_FWT5			0x274
#define VDPU_WEG_PWED_FWT6			0x278

static const stwuct hantwo_weg vp8_dec_dct_base[8] = {
	{ VDPU_WEG_ADDW_STW, 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(0), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(1), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(2), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(3), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(4), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(5), 0, 0xffffffff },
	{ VDPU_WEG_VP8_DCT_BASE(6), 0, 0xffffffff },
};

static const stwuct hantwo_weg vp8_dec_wf_wevew[4] = {
	{ VDPU_WEG_FIWTEW_WEVEW, 18, 0x3f },
	{ VDPU_WEG_FIWTEW_WEVEW, 12, 0x3f },
	{ VDPU_WEG_FIWTEW_WEVEW, 6, 0x3f },
	{ VDPU_WEG_FIWTEW_WEVEW, 0, 0x3f },
};

static const stwuct hantwo_weg vp8_dec_mb_adj[4] = {
	{ VDPU_WEG_FIWTEW_MB_ADJ, 21, 0x7f },
	{ VDPU_WEG_FIWTEW_MB_ADJ, 14, 0x7f },
	{ VDPU_WEG_FIWTEW_MB_ADJ, 7, 0x7f },
	{ VDPU_WEG_FIWTEW_MB_ADJ, 0, 0x7f },
};

static const stwuct hantwo_weg vp8_dec_wef_adj[4] = {
	{ VDPU_WEG_FIWTEW_WEF_ADJ, 21, 0x7f },
	{ VDPU_WEG_FIWTEW_WEF_ADJ, 14, 0x7f },
	{ VDPU_WEG_FIWTEW_WEF_ADJ, 7, 0x7f },
	{ VDPU_WEG_FIWTEW_WEF_ADJ, 0, 0x7f },
};

static const stwuct hantwo_weg vp8_dec_quant[4] = {
	{ VDPU_WEG_VP8_QUANTEW0, 11, 0x7ff },
	{ VDPU_WEG_VP8_QUANTEW0, 0, 0x7ff },
	{ VDPU_WEG_VP8_QUANTEW1, 11, 0x7ff },
	{ VDPU_WEG_VP8_QUANTEW1, 0, 0x7ff },
};

static const stwuct hantwo_weg vp8_dec_quant_dewta[5] = {
	{ VDPU_WEG_VP8_QUANTEW0, 27, 0x1f },
	{ VDPU_WEG_VP8_QUANTEW0, 22, 0x1f },
	{ VDPU_WEG_VP8_QUANTEW1, 27, 0x1f },
	{ VDPU_WEG_VP8_QUANTEW1, 22, 0x1f },
	{ VDPU_WEG_VP8_QUANTEW2, 27, 0x1f },
};

static const stwuct hantwo_weg vp8_dec_dct_stawt_bits[8] = {
	{ VDPU_WEG_VP8_CTWW0, 26, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT, 26, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT, 20, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT2, 24, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT2, 18, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT2, 12, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT2, 6, 0x3f },
	{ VDPU_WEG_VP8_DCT_STAWT_BIT2, 0, 0x3f },
};

static const stwuct hantwo_weg vp8_dec_pwed_bc_tap[8][6] = {
	{
		{ 0, 0, 0},
		{ VDPU_WEG_PWED_FWT, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT1, 22, 0x3ff },
		{ 0, 0, 0},
	}, {
		{ 0, 0, 0},
		{ VDPU_WEG_PWED_FWT1, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT1, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT2, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT2, 12, 0x3ff },
		{ 0, 0, 0},
	}, {
		{ VDPU_WEG_PWED_FWT10, 10, 0x3 },
		{ VDPU_WEG_PWED_FWT2, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT3, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT3, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT3, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT10, 8, 0x3},
	}, {
		{ 0, 0, 0},
		{ VDPU_WEG_PWED_FWT4, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT4, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT4, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT5, 22, 0x3ff },
		{ 0, 0, 0},
	}, {
		{ VDPU_WEG_PWED_FWT10, 6, 0x3 },
		{ VDPU_WEG_PWED_FWT5, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT5, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT6, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT6, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT10, 4, 0x3 },
	}, {
		{ 0, 0, 0},
		{ VDPU_WEG_PWED_FWT6, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT7, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT7, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT7, 2, 0x3ff },
		{ 0, 0, 0},
	}, {
		{ VDPU_WEG_PWED_FWT10, 2, 0x3 },
		{ VDPU_WEG_PWED_FWT8, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT8, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT8, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT9, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT10, 0, 0x3 },
	}, {
		{ 0, 0, 0},
		{ VDPU_WEG_PWED_FWT9, 12, 0x3ff },
		{ VDPU_WEG_PWED_FWT9, 2, 0x3ff },
		{ VDPU_WEG_PWED_FWT10, 22, 0x3ff },
		{ VDPU_WEG_PWED_FWT10, 12, 0x3ff },
		{ 0, 0, 0},
	},
};

static const stwuct hantwo_weg vp8_dec_mb_stawt_bit = {
	.base = VDPU_WEG_VP8_CTWW0,
	.shift = 18,
	.mask = 0x3f
};

static const stwuct hantwo_weg vp8_dec_mb_awigned_data_wen = {
	.base = VDPU_WEG_VP8_DATA_VAW,
	.shift = 0,
	.mask = 0x3fffff
};

static const stwuct hantwo_weg vp8_dec_num_dct_pawtitions = {
	.base = VDPU_WEG_VP8_DATA_VAW,
	.shift = 24,
	.mask = 0xf
};

static const stwuct hantwo_weg vp8_dec_stweam_wen = {
	.base = VDPU_WEG_STWEAM_WEN,
	.shift = 0,
	.mask = 0xffffff
};

static const stwuct hantwo_weg vp8_dec_mb_width = {
	.base = VDPU_WEG_VP8_PIC_MB_SIZE,
	.shift = 23,
	.mask = 0x1ff
};

static const stwuct hantwo_weg vp8_dec_mb_height = {
	.base = VDPU_WEG_VP8_PIC_MB_SIZE,
	.shift = 11,
	.mask = 0xff
};

static const stwuct hantwo_weg vp8_dec_mb_width_ext = {
	.base = VDPU_WEG_VP8_PIC_MB_SIZE,
	.shift = 3,
	.mask = 0x7
};

static const stwuct hantwo_weg vp8_dec_mb_height_ext = {
	.base = VDPU_WEG_VP8_PIC_MB_SIZE,
	.shift = 0,
	.mask = 0x7
};

static const stwuct hantwo_weg vp8_dec_boow_wange = {
	.base = VDPU_WEG_VP8_CTWW0,
	.shift = 0,
	.mask = 0xff
};

static const stwuct hantwo_weg vp8_dec_boow_vawue = {
	.base = VDPU_WEG_VP8_CTWW0,
	.shift = 8,
	.mask = 0xff
};

static const stwuct hantwo_weg vp8_dec_fiwtew_disabwe = {
	.base = VDPU_WEG_DEC_CTWW0,
	.shift = 8,
	.mask = 1
};

static const stwuct hantwo_weg vp8_dec_skip_mode = {
	.base = VDPU_WEG_DEC_CTWW0,
	.shift = 9,
	.mask = 1
};

static const stwuct hantwo_weg vp8_dec_stawt_dec = {
	.base = VDPU_WEG_EN_FWAGS,
	.shift = 0,
	.mask = 1
};

static void cfg_wf(stwuct hantwo_ctx *ctx,
		   const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	const stwuct v4w2_vp8_segment *seg = &hdw->segment;
	const stwuct v4w2_vp8_woop_fiwtew *wf = &hdw->wf;
	stwuct hantwo_dev *vpu = ctx->dev;
	unsigned int i;
	u32 weg;

	if (!(seg->fwags & V4W2_VP8_SEGMENT_FWAG_ENABWED)) {
		hantwo_weg_wwite(vpu, &vp8_dec_wf_wevew[0], wf->wevew);
	} ewse if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_DEWTA_VAWUE_MODE) {
		fow (i = 0; i < 4; i++) {
			u32 wf_wevew = cwamp(wf->wevew + seg->wf_update[i],
					     0, 63);

			hantwo_weg_wwite(vpu, &vp8_dec_wf_wevew[i], wf_wevew);
		}
	} ewse {
		fow (i = 0; i < 4; i++)
			hantwo_weg_wwite(vpu, &vp8_dec_wf_wevew[i],
					 seg->wf_update[i]);
	}

	weg = VDPU_WEG_WEF_PIC_FIWT_SHAWPNESS(wf->shawpness_wevew);
	if (wf->fwags & V4W2_VP8_WF_FIWTEW_TYPE_SIMPWE)
		weg |= VDPU_WEG_WEF_PIC_FIWT_TYPE_E;
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_FIWTEW_MB_ADJ);

	if (wf->fwags & V4W2_VP8_WF_ADJ_ENABWE) {
		fow (i = 0; i < 4; i++) {
			hantwo_weg_wwite(vpu, &vp8_dec_mb_adj[i],
					 wf->mb_mode_dewta[i]);
			hantwo_weg_wwite(vpu, &vp8_dec_wef_adj[i],
					 wf->wef_fwm_dewta[i]);
		}
	}
}

static void cfg_qp(stwuct hantwo_ctx *ctx,
		   const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	const stwuct v4w2_vp8_quantization *q = &hdw->quant;
	const stwuct v4w2_vp8_segment *seg = &hdw->segment;
	stwuct hantwo_dev *vpu = ctx->dev;
	unsigned int i;

	if (!(seg->fwags & V4W2_VP8_SEGMENT_FWAG_ENABWED)) {
		hantwo_weg_wwite(vpu, &vp8_dec_quant[0], q->y_ac_qi);
	} ewse if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_DEWTA_VAWUE_MODE) {
		fow (i = 0; i < 4; i++) {
			u32 quant = cwamp(q->y_ac_qi + seg->quant_update[i],
					  0, 127);

			hantwo_weg_wwite(vpu, &vp8_dec_quant[i], quant);
		}
	} ewse {
		fow (i = 0; i < 4; i++)
			hantwo_weg_wwite(vpu, &vp8_dec_quant[i],
					 seg->quant_update[i]);
	}

	hantwo_weg_wwite(vpu, &vp8_dec_quant_dewta[0], q->y_dc_dewta);
	hantwo_weg_wwite(vpu, &vp8_dec_quant_dewta[1], q->y2_dc_dewta);
	hantwo_weg_wwite(vpu, &vp8_dec_quant_dewta[2], q->y2_ac_dewta);
	hantwo_weg_wwite(vpu, &vp8_dec_quant_dewta[3], q->uv_dc_dewta);
	hantwo_weg_wwite(vpu, &vp8_dec_quant_dewta[4], q->uv_ac_dewta);
}

static void cfg_pawts(stwuct hantwo_ctx *ctx,
		      const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *vb2_swc;
	u32 fiwst_pawt_offset = V4W2_VP8_FWAME_IS_KEY_FWAME(hdw) ? 10 : 3;
	u32 mb_size, mb_offset_bytes, mb_offset_bits, mb_stawt_bits;
	u32 dct_size_pawt_size, dct_pawt_offset;
	dma_addw_t swc_dma;
	u32 dct_pawt_totaw_wen = 0;
	u32 count = 0;
	unsigned int i;

	vb2_swc = hantwo_get_swc_buf(ctx);
	swc_dma = vb2_dma_contig_pwane_dma_addw(&vb2_swc->vb2_buf, 0);

	/*
	 * Cawcuwate contwow pawtition mb data info
	 * @fiwst_pawt_headew_bits:	bits offset of mb data fwom fiwst
	 *				pawt stawt pos
	 * @mb_offset_bits:		bits offset of mb data fwom swc_dma
	 *				base addw
	 * @mb_offset_byte:		bytes offset of mb data fwom swc_dma
	 *				base addw
	 * @mb_stawt_bits:		bits offset of mb data fwom mb data
	 *				64bits awignment addw
	 */
	mb_offset_bits = fiwst_pawt_offset * 8 +
			 hdw->fiwst_pawt_headew_bits + 8;
	mb_offset_bytes = mb_offset_bits / 8;
	mb_stawt_bits = mb_offset_bits -
			(mb_offset_bytes & (~DEC_8190_AWIGN_MASK)) * 8;
	mb_size = hdw->fiwst_pawt_size -
		  (mb_offset_bytes - fiwst_pawt_offset) +
		  (mb_offset_bytes & DEC_8190_AWIGN_MASK);

	/* Macwobwock data awigned base addw */
	vdpu_wwite_wewaxed(vpu, (mb_offset_bytes & (~DEC_8190_AWIGN_MASK)) +
			   swc_dma, VDPU_WEG_VP8_ADDW_CTWW_PAWT);
	hantwo_weg_wwite(vpu, &vp8_dec_mb_stawt_bit, mb_stawt_bits);
	hantwo_weg_wwite(vpu, &vp8_dec_mb_awigned_data_wen, mb_size);

	/*
	 * Cawcuwate DCT pawtition info
	 * @dct_size_pawt_size: Containing sizes of DCT pawt, evewy DCT pawt
	 *			has 3 bytes to stowe its size, except the wast
	 *			DCT pawt
	 * @dct_pawt_offset:	bytes offset of DCT pawts fwom swc_dma base addw
	 * @dct_pawt_totaw_wen: totaw size of aww DCT pawts
	 */
	dct_size_pawt_size = (hdw->num_dct_pawts - 1) * 3;
	dct_pawt_offset = fiwst_pawt_offset + hdw->fiwst_pawt_size;
	fow (i = 0; i < hdw->num_dct_pawts; i++)
		dct_pawt_totaw_wen += hdw->dct_pawt_sizes[i];
	dct_pawt_totaw_wen += dct_size_pawt_size;
	dct_pawt_totaw_wen += (dct_pawt_offset & DEC_8190_AWIGN_MASK);

	/* Numbew of DCT pawtitions */
	hantwo_weg_wwite(vpu, &vp8_dec_num_dct_pawtitions,
			 hdw->num_dct_pawts - 1);

	/* DCT pawtition wength */
	hantwo_weg_wwite(vpu, &vp8_dec_stweam_wen, dct_pawt_totaw_wen);

	/* DCT pawtitions base addwess */
	fow (i = 0; i < hdw->num_dct_pawts; i++) {
		u32 byte_offset = dct_pawt_offset + dct_size_pawt_size + count;
		u32 base_addw = byte_offset + swc_dma;

		hantwo_weg_wwite(vpu, &vp8_dec_dct_base[i],
				 base_addw & (~DEC_8190_AWIGN_MASK));

		hantwo_weg_wwite(vpu, &vp8_dec_dct_stawt_bits[i],
				 (byte_offset & DEC_8190_AWIGN_MASK) * 8);

		count += hdw->dct_pawt_sizes[i];
	}
}

/*
 * pwediction fiwtew taps
 * nowmaw 6-tap fiwtews
 */
static void cfg_tap(stwuct hantwo_ctx *ctx,
		    const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	int i, j;

	if ((hdw->vewsion & 0x03) != 0)
		wetuwn; /* Tap fiwtew not used. */

	fow (i = 0; i < 8; i++) {
		fow (j = 0; j < 6; j++) {
			if (vp8_dec_pwed_bc_tap[i][j].base != 0)
				hantwo_weg_wwite(vpu,
						 &vp8_dec_pwed_bc_tap[i][j],
						 hantwo_vp8_dec_mc_fiwtew[i][j]);
		}
	}
}

static void cfg_wef(stwuct hantwo_ctx *ctx,
		    const stwuct v4w2_ctww_vp8_fwame *hdw,
		    stwuct vb2_v4w2_buffew *vb2_dst)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	dma_addw_t wef;

	wef = hantwo_get_wef(ctx, hdw->wast_fwame_ts);
	if (!wef) {
		vpu_debug(0, "faiwed to find wast fwame ts=%wwu\n",
			  hdw->wast_fwame_ts);
		wef = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	}
	vdpu_wwite_wewaxed(vpu, wef, VDPU_WEG_VP8_ADDW_WEF0);

	wef = hantwo_get_wef(ctx, hdw->gowden_fwame_ts);
	if (!wef && hdw->gowden_fwame_ts)
		vpu_debug(0, "faiwed to find gowden fwame ts=%wwu\n",
			  hdw->gowden_fwame_ts);
	if (!wef)
		wef = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	if (hdw->fwags & V4W2_VP8_FWAME_FWAG_SIGN_BIAS_GOWDEN)
		wef |= VDPU_WEG_VP8_GWEF_SIGN_BIAS;
	vdpu_wwite_wewaxed(vpu, wef, VDPU_WEG_VP8_ADDW_WEF2_5(2));

	wef = hantwo_get_wef(ctx, hdw->awt_fwame_ts);
	if (!wef && hdw->awt_fwame_ts)
		vpu_debug(0, "faiwed to find awt fwame ts=%wwu\n",
			  hdw->awt_fwame_ts);
	if (!wef)
		wef = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	if (hdw->fwags & V4W2_VP8_FWAME_FWAG_SIGN_BIAS_AWT)
		wef |= VDPU_WEG_VP8_AWEF_SIGN_BIAS;
	vdpu_wwite_wewaxed(vpu, wef, VDPU_WEG_VP8_ADDW_WEF2_5(3));
}

static void cfg_buffews(stwuct hantwo_ctx *ctx,
			const stwuct v4w2_ctww_vp8_fwame *hdw,
			stwuct vb2_v4w2_buffew *vb2_dst)
{
	const stwuct v4w2_vp8_segment *seg = &hdw->segment;
	stwuct hantwo_dev *vpu = ctx->dev;
	dma_addw_t dst_dma;
	u32 weg;

	/* Set pwobabiwity tabwe buffew addwess */
	vdpu_wwite_wewaxed(vpu, ctx->vp8_dec.pwob_tbw.dma,
			   VDPU_WEG_ADDW_QTABWE);

	/* Set segment map addwess */
	weg = VDPU_WEG_FWD_PIC1_SEGMENT_BASE(ctx->vp8_dec.segment_map.dma);
	if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_ENABWED) {
		weg |= VDPU_WEG_FWD_PIC1_SEGMENT_E;
		if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_UPDATE_MAP)
			weg |= VDPU_WEG_FWD_PIC1_SEGMENT_UPD_E;
	}
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_VP8_SEGMENT_VAW);

	/* set output fwame buffew addwess */
	dst_dma = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	vdpu_wwite_wewaxed(vpu, dst_dma, VDPU_WEG_ADDW_DST);
}

int wockchip_vpu2_vp8_dec_wun(stwuct hantwo_ctx *ctx)
{
	const stwuct v4w2_ctww_vp8_fwame *hdw;
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *vb2_dst;
	size_t height = ctx->dst_fmt.height;
	size_t width = ctx->dst_fmt.width;
	u32 mb_width, mb_height;
	u32 weg;

	hantwo_stawt_pwepawe_wun(ctx);

	hdw = hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_VP8_FWAME);
	if (WAWN_ON(!hdw))
		wetuwn -EINVAW;

	/* Weset segment_map buffew in keyfwame */
	if (V4W2_VP8_FWAME_IS_KEY_FWAME(hdw) && ctx->vp8_dec.segment_map.cpu)
		memset(ctx->vp8_dec.segment_map.cpu, 0,
		       ctx->vp8_dec.segment_map.size);

	hantwo_vp8_pwob_update(ctx, hdw);

	/*
	 * Extensive testing shows that the hawdwawe does not pwopewwy
	 * cweaw the intewnaw state fwom pwevious a decoding wun. This
	 * causes cowwuption in decoded fwames fow muwti-instance use cases.
	 * A soft weset befowe pwogwamming the wegistews has been found
	 * to wesowve those pwobwems.
	 */
	ctx->codec_ops->weset(ctx);

	weg = VDPU_WEG_CONFIG_DEC_TIMEOUT_E
		| VDPU_WEG_CONFIG_DEC_CWK_GATE_E;
	if (!V4W2_VP8_FWAME_IS_KEY_FWAME(hdw))
		weg |= VDPU_WEG_DEC_CTWW0_PIC_INTEW_E;
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_EN_FWAGS);

	weg = VDPU_WEG_CONFIG_DEC_STWENDIAN_E
		| VDPU_WEG_CONFIG_DEC_INSWAP32_E
		| VDPU_WEG_CONFIG_DEC_STWSWAP32_E
		| VDPU_WEG_CONFIG_DEC_OUTSWAP32_E
		| VDPU_WEG_CONFIG_DEC_IN_ENDIAN
		| VDPU_WEG_CONFIG_DEC_OUT_ENDIAN;
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_DATA_ENDIAN);

	weg = VDPU_WEG_CONFIG_DEC_MAX_BUWST(16);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_AXI_CTWW);

	weg = VDPU_WEG_DEC_CTWW0_DEC_MODE(10);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_DEC_FOWMAT);

	if (!(hdw->fwags & V4W2_VP8_FWAME_FWAG_MB_NO_SKIP_COEFF))
		hantwo_weg_wwite(vpu, &vp8_dec_skip_mode, 1);
	if (hdw->wf.wevew == 0)
		hantwo_weg_wwite(vpu, &vp8_dec_fiwtew_disabwe, 1);

	/* Fwame dimensions */
	mb_width = MB_WIDTH(width);
	mb_height = MB_HEIGHT(height);

	hantwo_weg_wwite(vpu, &vp8_dec_mb_width, mb_width);
	hantwo_weg_wwite(vpu, &vp8_dec_mb_height, mb_height);
	hantwo_weg_wwite(vpu, &vp8_dec_mb_width_ext, mb_width >> 9);
	hantwo_weg_wwite(vpu, &vp8_dec_mb_height_ext, mb_height >> 8);

	/* Boowean decodew */
	hantwo_weg_wwite(vpu, &vp8_dec_boow_wange, hdw->codew_state.wange);
	hantwo_weg_wwite(vpu, &vp8_dec_boow_vawue, hdw->codew_state.vawue);

	weg = vdpu_wead(vpu, VDPU_WEG_VP8_DCT_STAWT_BIT);
	if (hdw->vewsion != 3)
		weg |= VDPU_WEG_DEC_CTWW4_VC1_HEIGHT_EXT;
	if (hdw->vewsion & 0x3)
		weg |= VDPU_WEG_DEC_CTWW4_BIWIN_MC_E;
	vdpu_wwite_wewaxed(vpu, weg, VDPU_WEG_VP8_DCT_STAWT_BIT);

	cfg_wf(ctx, hdw);
	cfg_qp(ctx, hdw);
	cfg_pawts(ctx, hdw);
	cfg_tap(ctx, hdw);

	vb2_dst = hantwo_get_dst_buf(ctx);
	cfg_wef(ctx, hdw, vb2_dst);
	cfg_buffews(ctx, hdw, vb2_dst);

	hantwo_end_pwepawe_wun(ctx);

	hantwo_weg_wwite(vpu, &vp8_dec_stawt_dec, 1);

	wetuwn 0;
}
