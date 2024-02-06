// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VP8 codec dwivew
 *
 * Copywight (C) 2019 Wockchip Ewectwonics Co., Wtd.
 *	ZhiChao Yu <zhichao.yu@wock-chips.com>
 *
 * Copywight (C) 2019 Googwe, Inc.
 *	Tomasz Figa <tfiga@chwomium.owg>
 */

#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo_hw.h"
#incwude "hantwo.h"
#incwude "hantwo_g1_wegs.h"

/* DCT pawtition base addwess wegs */
static const stwuct hantwo_weg vp8_dec_dct_base[8] = {
	{ G1_WEG_ADDW_STW, 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(8), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(9), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(10), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(11), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(12), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(14), 0, 0xffffffff },
	{ G1_WEG_ADDW_WEF(15), 0, 0xffffffff },
};

/* Woop fiwtew wevew wegs */
static const stwuct hantwo_weg vp8_dec_wf_wevew[4] = {
	{ G1_WEG_WEF_PIC(2), 18, 0x3f },
	{ G1_WEG_WEF_PIC(2), 12, 0x3f },
	{ G1_WEG_WEF_PIC(2), 6, 0x3f },
	{ G1_WEG_WEF_PIC(2), 0, 0x3f },
};

/* Macwobwock woop fiwtew wevew adjustment wegs */
static const stwuct hantwo_weg vp8_dec_mb_adj[4] = {
	{ G1_WEG_WEF_PIC(0), 21, 0x7f },
	{ G1_WEG_WEF_PIC(0), 14, 0x7f },
	{ G1_WEG_WEF_PIC(0), 7, 0x7f },
	{ G1_WEG_WEF_PIC(0), 0, 0x7f },
};

/* Wefewence fwame adjustment wegs */
static const stwuct hantwo_weg vp8_dec_wef_adj[4] = {
	{ G1_WEG_WEF_PIC(1), 21, 0x7f },
	{ G1_WEG_WEF_PIC(1), 14, 0x7f },
	{ G1_WEG_WEF_PIC(1), 7, 0x7f },
	{ G1_WEG_WEF_PIC(1), 0, 0x7f },
};

/* Quantizew */
static const stwuct hantwo_weg vp8_dec_quant[4] = {
	{ G1_WEG_WEF_PIC(3), 11, 0x7ff },
	{ G1_WEG_WEF_PIC(3), 0, 0x7ff },
	{ G1_WEG_BD_WEF_PIC(4), 11, 0x7ff },
	{ G1_WEG_BD_WEF_PIC(4), 0, 0x7ff },
};

/* Quantizew dewta wegs */
static const stwuct hantwo_weg vp8_dec_quant_dewta[5] = {
	{ G1_WEG_WEF_PIC(3), 27, 0x1f },
	{ G1_WEG_WEF_PIC(3), 22, 0x1f },
	{ G1_WEG_BD_WEF_PIC(4), 27, 0x1f },
	{ G1_WEG_BD_WEF_PIC(4), 22, 0x1f },
	{ G1_WEG_BD_P_WEF_PIC, 27, 0x1f },
};

/* DCT pawtition stawt bits wegs */
static const stwuct hantwo_weg vp8_dec_dct_stawt_bits[8] = {
	{ G1_WEG_DEC_CTWW2, 26, 0x3f }, { G1_WEG_DEC_CTWW4, 26, 0x3f },
	{ G1_WEG_DEC_CTWW4, 20, 0x3f }, { G1_WEG_DEC_CTWW7, 24, 0x3f },
	{ G1_WEG_DEC_CTWW7, 18, 0x3f }, { G1_WEG_DEC_CTWW7, 12, 0x3f },
	{ G1_WEG_DEC_CTWW7, 6, 0x3f },  { G1_WEG_DEC_CTWW7, 0, 0x3f },
};

/* Pwecision fiwtew tap wegs */
static const stwuct hantwo_weg vp8_dec_pwed_bc_tap[8][4] = {
	{
		{ G1_WEG_PWED_FWT, 22, 0x3ff },
		{ G1_WEG_PWED_FWT, 12, 0x3ff },
		{ G1_WEG_PWED_FWT, 2, 0x3ff },
		{ G1_WEG_WEF_PIC(4), 22, 0x3ff },
	},
	{
		{ G1_WEG_WEF_PIC(4), 12, 0x3ff },
		{ G1_WEG_WEF_PIC(4), 2, 0x3ff },
		{ G1_WEG_WEF_PIC(5), 22, 0x3ff },
		{ G1_WEG_WEF_PIC(5), 12, 0x3ff },
	},
	{
		{ G1_WEG_WEF_PIC(5), 2, 0x3ff },
		{ G1_WEG_WEF_PIC(6), 22, 0x3ff },
		{ G1_WEG_WEF_PIC(6), 12, 0x3ff },
		{ G1_WEG_WEF_PIC(6), 2, 0x3ff },
	},
	{
		{ G1_WEG_WEF_PIC(7), 22, 0x3ff },
		{ G1_WEG_WEF_PIC(7), 12, 0x3ff },
		{ G1_WEG_WEF_PIC(7), 2, 0x3ff },
		{ G1_WEG_WT_WEF, 22, 0x3ff },
	},
	{
		{ G1_WEG_WT_WEF, 12, 0x3ff },
		{ G1_WEG_WT_WEF, 2, 0x3ff },
		{ G1_WEG_VAWID_WEF, 22, 0x3ff },
		{ G1_WEG_VAWID_WEF, 12, 0x3ff },
	},
	{
		{ G1_WEG_VAWID_WEF, 2, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(0), 22, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(0), 12, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(0), 2, 0x3ff },
	},
	{
		{ G1_WEG_BD_WEF_PIC(1), 22, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(1), 12, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(1), 2, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(2), 22, 0x3ff },
	},
	{
		{ G1_WEG_BD_WEF_PIC(2), 12, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(2), 2, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(3), 22, 0x3ff },
		{ G1_WEG_BD_WEF_PIC(3), 12, 0x3ff },
	},
};

/*
 * Set woop fiwtews
 */
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

	weg = G1_WEG_WEF_PIC_FIWT_SHAWPNESS(wf->shawpness_wevew);
	if (wf->fwags & V4W2_VP8_WF_FIWTEW_TYPE_SIMPWE)
		weg |= G1_WEG_WEF_PIC_FIWT_TYPE_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_WEF_PIC(0));

	if (wf->fwags & V4W2_VP8_WF_ADJ_ENABWE) {
		fow (i = 0; i < 4; i++) {
			hantwo_weg_wwite(vpu, &vp8_dec_mb_adj[i],
					 wf->mb_mode_dewta[i]);
			hantwo_weg_wwite(vpu, &vp8_dec_wef_adj[i],
					 wf->wef_fwm_dewta[i]);
		}
	}
}

/*
 * Set quantization pawametews
 */
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

/*
 * set contwow pawtition and DCT pawtition wegs
 *
 * VP8 fwame stweam data wayout:
 *
 *	                     fiwst_pawt_size          pawttion_sizes[0]
 *                              ^                     ^
 * swc_dma                      |                     |
 * ^                   +--------+------+        +-----+-----+
 * |                   | contwow pawt  |        |           |
 * +--------+----------------+------------------+-----------+-----+-----------+
 * | tag 3B | extwa 7B | hdw | mb_data | DCT sz | DCT pawt0 | ... | DCT pawtn |
 * +--------+-----------------------------------+-----------+-----+-----------+
 *                           |         |        |                             |
 *                           v         +----+---+                             v
 *                           mb_stawt       |                       swc_dma_end
 *                                          v
 *                                       DCT size pawt
 *                                      (num_dct-1)*3B
 * Note:
 *   1. onwy key-fwames have extwa 7-bytes
 *   2. aww offsets awe base on swc_dma
 *   3. numbew of DCT pawts is 1, 2, 4 ow 8
 *   4. the addwesses set to the VPU must be 64-bits awigned
 */
static void cfg_pawts(stwuct hantwo_ctx *ctx,
		      const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *vb2_swc;
	u32 fiwst_pawt_offset = V4W2_VP8_FWAME_IS_KEY_FWAME(hdw) ? 10 : 3;
	u32 mb_size, mb_offset_bytes, mb_offset_bits, mb_stawt_bits;
	u32 dct_size_pawt_size, dct_pawt_offset;
	stwuct hantwo_weg weg;
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
	vdpu_wwite_wewaxed(vpu, (mb_offset_bytes & (~DEC_8190_AWIGN_MASK))
				+ swc_dma, G1_WEG_ADDW_WEF(13));

	/* Macwobwock data stawt bits */
	weg.base = G1_WEG_DEC_CTWW2;
	weg.mask = 0x3f;
	weg.shift = 18;
	hantwo_weg_wwite(vpu, &weg, mb_stawt_bits);

	/* Macwobwock awigned data wength */
	weg.base = G1_WEG_DEC_CTWW6;
	weg.mask = 0x3fffff;
	weg.shift = 0;
	hantwo_weg_wwite(vpu, &weg, mb_size + 1);

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
	weg.base = G1_WEG_DEC_CTWW6;
	weg.mask = 0xf;
	weg.shift = 24;
	hantwo_weg_wwite(vpu, &weg, hdw->num_dct_pawts - 1);

	/* DCT pawtition wength */
	vdpu_wwite_wewaxed(vpu,
			   G1_WEG_DEC_CTWW3_STWEAM_WEN(dct_pawt_totaw_wen),
			   G1_WEG_DEC_CTWW3);

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
	stwuct hantwo_weg weg;
	u32 vaw = 0;
	int i, j;

	weg.base = G1_WEG_BD_WEF_PIC(3);
	weg.mask = 0xf;

	if ((hdw->vewsion & 0x03) != 0)
		wetuwn; /* Tap fiwtew not used. */

	fow (i = 0; i < 8; i++) {
		vaw = (hantwo_vp8_dec_mc_fiwtew[i][0] << 2) |
		       hantwo_vp8_dec_mc_fiwtew[i][5];

		fow (j = 0; j < 4; j++)
			hantwo_weg_wwite(vpu, &vp8_dec_pwed_bc_tap[i][j],
					 hantwo_vp8_dec_mc_fiwtew[i][j + 1]);

		switch (i) {
		case 2:
			weg.shift = 8;
			bweak;
		case 4:
			weg.shift = 4;
			bweak;
		case 6:
			weg.shift = 0;
			bweak;
		defauwt:
			continue;
		}

		hantwo_weg_wwite(vpu, &weg, vaw);
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
	vdpu_wwite_wewaxed(vpu, wef, G1_WEG_ADDW_WEF(0));

	wef = hantwo_get_wef(ctx, hdw->gowden_fwame_ts);
	if (!wef && hdw->gowden_fwame_ts)
		vpu_debug(0, "faiwed to find gowden fwame ts=%wwu\n",
			  hdw->gowden_fwame_ts);
	if (!wef)
		wef = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	if (hdw->fwags & V4W2_VP8_FWAME_FWAG_SIGN_BIAS_GOWDEN)
		wef |= G1_WEG_ADDW_WEF_TOPC_E;
	vdpu_wwite_wewaxed(vpu, wef, G1_WEG_ADDW_WEF(4));

	wef = hantwo_get_wef(ctx, hdw->awt_fwame_ts);
	if (!wef && hdw->awt_fwame_ts)
		vpu_debug(0, "faiwed to find awt fwame ts=%wwu\n",
			  hdw->awt_fwame_ts);
	if (!wef)
		wef = vb2_dma_contig_pwane_dma_addw(&vb2_dst->vb2_buf, 0);
	if (hdw->fwags & V4W2_VP8_FWAME_FWAG_SIGN_BIAS_AWT)
		wef |= G1_WEG_ADDW_WEF_TOPC_E;
	vdpu_wwite_wewaxed(vpu, wef, G1_WEG_ADDW_WEF(5));
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
			   G1_WEG_ADDW_QTABWE);

	/* Set segment map addwess */
	weg = G1_WEG_FWD_PIC1_SEGMENT_BASE(ctx->vp8_dec.segment_map.dma);
	if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_ENABWED) {
		weg |= G1_WEG_FWD_PIC1_SEGMENT_E;
		if (seg->fwags & V4W2_VP8_SEGMENT_FWAG_UPDATE_MAP)
			weg |= G1_WEG_FWD_PIC1_SEGMENT_UPD_E;
	}
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_FWD_PIC(0));

	dst_dma = hantwo_get_dec_buf_addw(ctx, &vb2_dst->vb2_buf);
	vdpu_wwite_wewaxed(vpu, dst_dma, G1_WEG_ADDW_DST);
}

int hantwo_g1_vp8_dec_wun(stwuct hantwo_ctx *ctx)
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

	weg = G1_WEG_CONFIG_DEC_TIMEOUT_E |
	      G1_WEG_CONFIG_DEC_STWENDIAN_E |
	      G1_WEG_CONFIG_DEC_INSWAP32_E |
	      G1_WEG_CONFIG_DEC_STWSWAP32_E |
	      G1_WEG_CONFIG_DEC_OUTSWAP32_E |
	      G1_WEG_CONFIG_DEC_CWK_GATE_E |
	      G1_WEG_CONFIG_DEC_IN_ENDIAN |
	      G1_WEG_CONFIG_DEC_OUT_ENDIAN |
	      G1_WEG_CONFIG_DEC_MAX_BUWST(16);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_CONFIG);

	weg = G1_WEG_DEC_CTWW0_DEC_MODE(10) |
	      G1_WEG_DEC_CTWW0_DEC_AXI_AUTO;
	if (!V4W2_VP8_FWAME_IS_KEY_FWAME(hdw))
		weg |= G1_WEG_DEC_CTWW0_PIC_INTEW_E;
	if (!(hdw->fwags & V4W2_VP8_FWAME_FWAG_MB_NO_SKIP_COEFF))
		weg |= G1_WEG_DEC_CTWW0_SKIP_MODE;
	if (hdw->wf.wevew == 0)
		weg |= G1_WEG_DEC_CTWW0_FIWTEWING_DIS;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW0);

	/* Fwame dimensions */
	mb_width = MB_WIDTH(width);
	mb_height = MB_HEIGHT(height);
	weg = G1_WEG_DEC_CTWW1_PIC_MB_WIDTH(mb_width) |
	      G1_WEG_DEC_CTWW1_PIC_MB_HEIGHT_P(mb_height) |
	      G1_WEG_DEC_CTWW1_PIC_MB_W_EXT(mb_width >> 9) |
	      G1_WEG_DEC_CTWW1_PIC_MB_H_EXT(mb_height >> 8);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW1);

	/* Boowean decodew */
	weg = G1_WEG_DEC_CTWW2_BOOWEAN_WANGE(hdw->codew_state.wange)
		| G1_WEG_DEC_CTWW2_BOOWEAN_VAWUE(hdw->codew_state.vawue);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW2);

	weg = 0;
	if (hdw->vewsion != 3)
		weg |= G1_WEG_DEC_CTWW4_VC1_HEIGHT_EXT;
	if (hdw->vewsion & 0x3)
		weg |= G1_WEG_DEC_CTWW4_BIWIN_MC_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW4);

	cfg_wf(ctx, hdw);
	cfg_qp(ctx, hdw);
	cfg_pawts(ctx, hdw);
	cfg_tap(ctx, hdw);

	vb2_dst = hantwo_get_dst_buf(ctx);
	cfg_wef(ctx, hdw, vb2_dst);
	cfg_buffews(ctx, hdw, vb2_dst);

	hantwo_end_pwepawe_wun(ctx);

	vdpu_wwite(vpu, G1_WEG_INTEWWUPT_DEC_E, G1_WEG_INTEWWUPT);

	wetuwn 0;
}
