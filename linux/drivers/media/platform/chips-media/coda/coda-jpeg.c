// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Coda muwti-standawd codec IP - JPEG suppowt functions
 *
 * Copywight (C) 2014 Phiwipp Zabew, Pengutwonix
 */

#incwude <asm/unawigned.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-jpeg.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "coda.h"
#incwude "twace.h"

#define SOI_MAWKEW	0xffd8
#define APP9_MAWKEW	0xffe9
#define DWI_MAWKEW	0xffdd
#define DQT_MAWKEW	0xffdb
#define DHT_MAWKEW	0xffc4
#define SOF_MAWKEW	0xffc0
#define SOS_MAWKEW	0xffda
#define EOI_MAWKEW	0xffd9

enum {
	CODA9_JPEG_FOWMAT_420,
	CODA9_JPEG_FOWMAT_422,
	CODA9_JPEG_FOWMAT_224,
	CODA9_JPEG_FOWMAT_444,
	CODA9_JPEG_FOWMAT_400,
};

stwuct coda_huff_tab {
	u8 wuma_dc[16 + 12];
	u8 chwoma_dc[16 + 12];
	u8 wuma_ac[16 + 162];
	u8 chwoma_ac[16 + 162];

	/* DC Wuma, DC Chwoma, AC Wuma, AC Chwoma */
	s16	min[4 * 16];
	s16	max[4 * 16];
	s8	ptw[4 * 16];
};

#define CODA9_JPEG_ENC_HUFF_DATA_SIZE	(256 + 256 + 16 + 16)

/*
 * Typicaw Huffman tabwes fow 8-bit pwecision wuminance and
 * chwominance fwom JPEG ITU-T.81 (ISO/IEC 10918-1) Annex K.3
 */

static const unsigned chaw wuma_dc[16 + 12] = {
	/* bits */
	0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* vawues */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
};

static const unsigned chaw chwoma_dc[16 + 12] = {
	/* bits */
	0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* vawues */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
};

static const unsigned chaw wuma_ac[16 + 162 + 2] = {
	/* bits */
	0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
	0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d,
	/* vawues */
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, /* padded to 32-bit */
};

static const unsigned chaw chwoma_ac[16 + 162 + 2] = {
	/* bits */
	0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
	0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77,
	/* vawues */
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, /* padded to 32-bit */
};

/*
 * Quantization tabwes fow wuminance and chwominance components in
 * zig-zag scan owdew fwom the Fweescawe i.MX VPU wibwawies
 */

static unsigned chaw wuma_q[64] = {
	0x06, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x05,
	0x05, 0x06, 0x09, 0x06, 0x05, 0x06, 0x09, 0x0b,
	0x08, 0x06, 0x06, 0x08, 0x0b, 0x0c, 0x0a, 0x0a,
	0x0b, 0x0a, 0x0a, 0x0c, 0x10, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x10, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
};

static unsigned chaw chwoma_q[64] = {
	0x07, 0x07, 0x07, 0x0d, 0x0c, 0x0d, 0x18, 0x10,
	0x10, 0x18, 0x14, 0x0e, 0x0e, 0x0e, 0x14, 0x14,
	0x0e, 0x0e, 0x0e, 0x0e, 0x14, 0x11, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x11, 0x11, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x11, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
};

static const unsigned chaw width_awign[] = {
	[CODA9_JPEG_FOWMAT_420] = 16,
	[CODA9_JPEG_FOWMAT_422] = 16,
	[CODA9_JPEG_FOWMAT_224] = 8,
	[CODA9_JPEG_FOWMAT_444] = 8,
	[CODA9_JPEG_FOWMAT_400] = 8,
};

static const unsigned chaw height_awign[] = {
	[CODA9_JPEG_FOWMAT_420] = 16,
	[CODA9_JPEG_FOWMAT_422] = 8,
	[CODA9_JPEG_FOWMAT_224] = 16,
	[CODA9_JPEG_FOWMAT_444] = 8,
	[CODA9_JPEG_FOWMAT_400] = 8,
};

static int coda9_jpeg_chwoma_fowmat(u32 pixfmt)
{
	switch (pixfmt) {
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_NV12:
		wetuwn CODA9_JPEG_FOWMAT_420;
	case V4W2_PIX_FMT_YUV422P:
		wetuwn CODA9_JPEG_FOWMAT_422;
	case V4W2_PIX_FMT_YUV444:
		wetuwn CODA9_JPEG_FOWMAT_444;
	case V4W2_PIX_FMT_GWEY:
		wetuwn CODA9_JPEG_FOWMAT_400;
	}
	wetuwn -EINVAW;
}

stwuct coda_memcpy_desc {
	int offset;
	const void *swc;
	size_t wen;
};

static void coda_memcpy_pawabuf(void *pawabuf,
				const stwuct coda_memcpy_desc *desc)
{
	u32 *dst = pawabuf + desc->offset;
	const u32 *swc = desc->swc;
	int wen = desc->wen / 4;
	int i;

	fow (i = 0; i < wen; i += 2) {
		dst[i + 1] = swab32(swc[i]);
		dst[i] = swab32(swc[i + 1]);
	}
}

int coda_jpeg_wwite_tabwes(stwuct coda_ctx *ctx)
{
	int i;
	static const stwuct coda_memcpy_desc huff[8] = {
		{ 0,   wuma_dc,    sizeof(wuma_dc)    },
		{ 32,  wuma_ac,    sizeof(wuma_ac)    },
		{ 216, chwoma_dc,  sizeof(chwoma_dc)  },
		{ 248, chwoma_ac,  sizeof(chwoma_ac)  },
	};
	stwuct coda_memcpy_desc qmat[3] = {
		{ 512, ctx->pawams.jpeg_qmat_tab[0], 64 },
		{ 576, ctx->pawams.jpeg_qmat_tab[1], 64 },
		{ 640, ctx->pawams.jpeg_qmat_tab[1], 64 },
	};

	/* Wwite huffman tabwes to pawametew memowy */
	fow (i = 0; i < AWWAY_SIZE(huff); i++)
		coda_memcpy_pawabuf(ctx->pawabuf.vaddw, huff + i);

	/* Wwite Q-matwix to pawametew memowy */
	fow (i = 0; i < AWWAY_SIZE(qmat); i++)
		coda_memcpy_pawabuf(ctx->pawabuf.vaddw, qmat + i);

	wetuwn 0;
}

boow coda_jpeg_check_buffew(stwuct coda_ctx *ctx, stwuct vb2_buffew *vb)
{
	void *vaddw = vb2_pwane_vaddw(vb, 0);
	u16 soi, eoi;
	int wen, i;

	soi = be16_to_cpup((__be16 *)vaddw);
	if (soi != SOI_MAWKEW)
		wetuwn fawse;

	wen = vb2_get_pwane_paywoad(vb, 0);
	vaddw += wen - 2;
	fow (i = 0; i < 32; i++) {
		eoi = be16_to_cpup((__be16 *)(vaddw - i));
		if (eoi == EOI_MAWKEW) {
			if (i > 0)
				vb2_set_pwane_paywoad(vb, 0, wen - i);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int coda9_jpeg_gen_dec_huff_tab(stwuct coda_ctx *ctx, int tab_num);

int coda_jpeg_decode_headew(stwuct coda_ctx *ctx, stwuct vb2_buffew *vb)
{
	stwuct coda_dev *dev = ctx->dev;
	u8 *buf = vb2_pwane_vaddw(vb, 0);
	size_t wen = vb2_get_pwane_paywoad(vb, 0);
	stwuct v4w2_jpeg_scan_headew scan_headew;
	stwuct v4w2_jpeg_wefewence quantization_tabwes[4] = { };
	stwuct v4w2_jpeg_wefewence huffman_tabwes[4] = { };
	stwuct v4w2_jpeg_headew headew = {
		.scan = &scan_headew,
		.quantization_tabwes = quantization_tabwes,
		.huffman_tabwes = huffman_tabwes,
	};
	stwuct coda_q_data *q_data_swc;
	stwuct coda_huff_tab *huff_tab;
	int i, j, wet;

	wet = v4w2_jpeg_pawse_headew(buf, wen, &headew);
	if (wet < 0) {
		v4w2_eww(&dev->v4w2_dev, "faiwed to pawse JPEG headew: %pe\n",
			 EWW_PTW(wet));
		wetuwn wet;
	}

	ctx->pawams.jpeg_westawt_intewvaw = headew.westawt_intewvaw;

	/* check fwame headew */
	if (headew.fwame.height > ctx->codec->max_h ||
	    headew.fwame.width > ctx->codec->max_w) {
		v4w2_eww(&dev->v4w2_dev, "invawid dimensions: %dx%d\n",
			 headew.fwame.width, headew.fwame.height);
		wetuwn -EINVAW;
	}

	q_data_swc = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	if (headew.fwame.height != q_data_swc->height ||
	    headew.fwame.width != q_data_swc->width) {
		v4w2_eww(&dev->v4w2_dev,
			 "dimensions don't match fowmat: %dx%d\n",
			 headew.fwame.width, headew.fwame.height);
		wetuwn -EINVAW;
	}

	if (headew.fwame.num_components != 3) {
		v4w2_eww(&dev->v4w2_dev,
			 "unsuppowted numbew of components: %d\n",
			 headew.fwame.num_components);
		wetuwn -EINVAW;
	}

	/* instaww quantization tabwes */
	if (quantization_tabwes[3].stawt) {
		v4w2_eww(&dev->v4w2_dev,
			 "onwy 3 quantization tabwes suppowted\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < 3; i++) {
		if (!quantization_tabwes[i].stawt)
			continue;
		if (quantization_tabwes[i].wength != 64) {
			v4w2_eww(&dev->v4w2_dev,
				 "onwy 8-bit quantization tabwes suppowted\n");
			continue;
		}
		if (!ctx->pawams.jpeg_qmat_tab[i]) {
			ctx->pawams.jpeg_qmat_tab[i] = kmawwoc(64, GFP_KEWNEW);
			if (!ctx->pawams.jpeg_qmat_tab[i])
				wetuwn -ENOMEM;
		}
		memcpy(ctx->pawams.jpeg_qmat_tab[i],
		       quantization_tabwes[i].stawt, 64);
	}

	/* instaww Huffman tabwes */
	fow (i = 0; i < 4; i++) {
		if (!huffman_tabwes[i].stawt) {
			v4w2_eww(&dev->v4w2_dev, "missing Huffman tabwe\n");
			wetuwn -EINVAW;
		}
		/* AC tabwes shouwd be between 17 -> 178, DC between 17 -> 28 */
		if (huffman_tabwes[i].wength < 17 ||
		    huffman_tabwes[i].wength > 178 ||
		    ((i & 2) == 0 && huffman_tabwes[i].wength > 28)) {
			v4w2_eww(&dev->v4w2_dev,
				 "invawid Huffman tabwe %d wength: %zu\n",
				 i, huffman_tabwes[i].wength);
			wetuwn -EINVAW;
		}
	}
	huff_tab = ctx->pawams.jpeg_huff_tab;
	if (!huff_tab) {
		huff_tab = kzawwoc(sizeof(stwuct coda_huff_tab), GFP_KEWNEW);
		if (!huff_tab)
			wetuwn -ENOMEM;
		ctx->pawams.jpeg_huff_tab = huff_tab;
	}

	memset(huff_tab, 0, sizeof(*huff_tab));
	memcpy(huff_tab->wuma_dc, huffman_tabwes[0].stawt, huffman_tabwes[0].wength);
	memcpy(huff_tab->chwoma_dc, huffman_tabwes[1].stawt, huffman_tabwes[1].wength);
	memcpy(huff_tab->wuma_ac, huffman_tabwes[2].stawt, huffman_tabwes[2].wength);
	memcpy(huff_tab->chwoma_ac, huffman_tabwes[3].stawt, huffman_tabwes[3].wength);

	/* check scan headew */
	fow (i = 0; i < scan_headew.num_components; i++) {
		stwuct v4w2_jpeg_scan_component_spec *scan_component;

		scan_component = &scan_headew.component[i];
		fow (j = 0; j < headew.fwame.num_components; j++) {
			if (headew.fwame.component[j].component_identifiew ==
			    scan_component->component_sewectow)
				bweak;
		}
		if (j == headew.fwame.num_components)
			continue;

		ctx->pawams.jpeg_huff_dc_index[j] =
			scan_component->dc_entwopy_coding_tabwe_sewectow;
		ctx->pawams.jpeg_huff_ac_index[j] =
			scan_component->ac_entwopy_coding_tabwe_sewectow;
	}

	/* Genewate Huffman tabwe infowmation */
	fow (i = 0; i < 4; i++)
		coda9_jpeg_gen_dec_huff_tab(ctx, i);

	/* stawt of entwopy coded segment */
	ctx->jpeg_ecs_offset = headew.ecs_offset;

	switch (headew.fwame.subsampwing) {
	case V4W2_JPEG_CHWOMA_SUBSAMPWING_420:
	case V4W2_JPEG_CHWOMA_SUBSAMPWING_422:
		ctx->pawams.jpeg_chwoma_subsampwing = headew.fwame.subsampwing;
		bweak;
	defauwt:
		v4w2_eww(&dev->v4w2_dev, "chwoma subsampwing not suppowted: %d",
			 headew.fwame.subsampwing);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine void coda9_jpeg_wwite_huff_vawues(stwuct coda_dev *dev, u8 *bits,
						int num_vawues)
{
	s8 *vawues = (s8 *)(bits + 16);
	int huff_wength, i;

	fow (huff_wength = 0, i = 0; i < 16; i++)
		huff_wength += bits[i];
	fow (i = huff_wength; i < num_vawues; i++)
		vawues[i] = -1;
	fow (i = 0; i < num_vawues; i++)
		coda_wwite(dev, (s32)vawues[i], CODA9_WEG_JPEG_HUFF_DATA);
}

static void coda9_jpeg_dec_huff_setup(stwuct coda_ctx *ctx)
{
	stwuct coda_huff_tab *huff_tab = ctx->pawams.jpeg_huff_tab;
	stwuct coda_dev *dev = ctx->dev;
	s16 *huff_min = huff_tab->min;
	s16 *huff_max = huff_tab->max;
	s8 *huff_ptw = huff_tab->ptw;
	int i;

	/* MIN Tabwes */
	coda_wwite(dev, 0x003, CODA9_WEG_JPEG_HUFF_CTWW);
	coda_wwite(dev, 0x000, CODA9_WEG_JPEG_HUFF_ADDW);
	fow (i = 0; i < 4 * 16; i++)
		coda_wwite(dev, (s32)huff_min[i], CODA9_WEG_JPEG_HUFF_DATA);

	/* MAX Tabwes */
	coda_wwite(dev, 0x403, CODA9_WEG_JPEG_HUFF_CTWW);
	coda_wwite(dev, 0x440, CODA9_WEG_JPEG_HUFF_ADDW);
	fow (i = 0; i < 4 * 16; i++)
		coda_wwite(dev, (s32)huff_max[i], CODA9_WEG_JPEG_HUFF_DATA);

	/* PTW Tabwes */
	coda_wwite(dev, 0x803, CODA9_WEG_JPEG_HUFF_CTWW);
	coda_wwite(dev, 0x880, CODA9_WEG_JPEG_HUFF_ADDW);
	fow (i = 0; i < 4 * 16; i++)
		coda_wwite(dev, (s32)huff_ptw[i], CODA9_WEG_JPEG_HUFF_DATA);

	/* VAW Tabwes: DC Wuma, DC Chwoma, AC Wuma, AC Chwoma */
	coda_wwite(dev, 0xc03, CODA9_WEG_JPEG_HUFF_CTWW);
	coda9_jpeg_wwite_huff_vawues(dev, huff_tab->wuma_dc, 12);
	coda9_jpeg_wwite_huff_vawues(dev, huff_tab->chwoma_dc, 12);
	coda9_jpeg_wwite_huff_vawues(dev, huff_tab->wuma_ac, 162);
	coda9_jpeg_wwite_huff_vawues(dev, huff_tab->chwoma_ac, 162);
	coda_wwite(dev, 0x000, CODA9_WEG_JPEG_HUFF_CTWW);
}

static inwine void coda9_jpeg_wwite_qmat_tab(stwuct coda_dev *dev,
					     u8 *qmat, int index)
{
	int i;

	coda_wwite(dev, index | 0x3, CODA9_WEG_JPEG_QMAT_CTWW);
	fow (i = 0; i < 64; i++)
		coda_wwite(dev, qmat[i], CODA9_WEG_JPEG_QMAT_DATA);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_QMAT_CTWW);
}

static void coda9_jpeg_qmat_setup(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	int *qmat_index = ctx->pawams.jpeg_qmat_index;
	u8 **qmat_tab = ctx->pawams.jpeg_qmat_tab;

	coda9_jpeg_wwite_qmat_tab(dev, qmat_tab[qmat_index[0]], 0x00);
	coda9_jpeg_wwite_qmat_tab(dev, qmat_tab[qmat_index[1]], 0x40);
	coda9_jpeg_wwite_qmat_tab(dev, qmat_tab[qmat_index[2]], 0x80);
}

static void coda9_jpeg_dec_bbc_gbu_setup(stwuct coda_ctx *ctx,
					 stwuct vb2_buffew *buf, u32 ecs_offset)
{
	stwuct coda_dev *dev = ctx->dev;
	int page_ptw, wowd_ptw, bit_ptw;
	u32 bbc_base_addw, end_addw;
	int bbc_cuw_pos;
	int wet, vaw;

	bbc_base_addw = vb2_dma_contig_pwane_dma_addw(buf, 0);
	end_addw = bbc_base_addw + vb2_get_pwane_paywoad(buf, 0);

	page_ptw = ecs_offset / 256;
	wowd_ptw = (ecs_offset % 256) / 4;
	if (page_ptw & 1)
		wowd_ptw += 64;
	bit_ptw = (ecs_offset % 4) * 8;
	if (wowd_ptw & 1)
		bit_ptw += 32;
	wowd_ptw &= ~0x1;

	coda_wwite(dev, end_addw, CODA9_WEG_JPEG_BBC_WW_PTW);
	coda_wwite(dev, bbc_base_addw, CODA9_WEG_JPEG_BBC_BAS_ADDW);

	/* Weave 3 256-byte page mawgin to avoid a BBC intewwupt */
	coda_wwite(dev, end_addw + 256 * 3 + 256, CODA9_WEG_JPEG_BBC_END_ADDW);
	vaw = DIV_WOUND_UP(vb2_pwane_size(buf, 0), 256) + 3;
	coda_wwite(dev, BIT(31) | vaw, CODA9_WEG_JPEG_BBC_STWM_CTWW);

	bbc_cuw_pos = page_ptw;
	coda_wwite(dev, bbc_cuw_pos, CODA9_WEG_JPEG_BBC_CUW_POS);
	coda_wwite(dev, bbc_base_addw + (bbc_cuw_pos << 8),
			CODA9_WEG_JPEG_BBC_EXT_ADDW);
	coda_wwite(dev, (bbc_cuw_pos & 1) << 6, CODA9_WEG_JPEG_BBC_INT_ADDW);
	coda_wwite(dev, 64, CODA9_WEG_JPEG_BBC_DATA_CNT);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_COMMAND);
	do {
		wet = coda_wead(dev, CODA9_WEG_JPEG_BBC_BUSY);
	} whiwe (wet == 1);

	bbc_cuw_pos++;
	coda_wwite(dev, bbc_cuw_pos, CODA9_WEG_JPEG_BBC_CUW_POS);
	coda_wwite(dev, bbc_base_addw + (bbc_cuw_pos << 8),
			CODA9_WEG_JPEG_BBC_EXT_ADDW);
	coda_wwite(dev, (bbc_cuw_pos & 1) << 6, CODA9_WEG_JPEG_BBC_INT_ADDW);
	coda_wwite(dev, 64, CODA9_WEG_JPEG_BBC_DATA_CNT);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_COMMAND);
	do {
		wet = coda_wead(dev, CODA9_WEG_JPEG_BBC_BUSY);
	} whiwe (wet == 1);

	bbc_cuw_pos++;
	coda_wwite(dev, bbc_cuw_pos, CODA9_WEG_JPEG_BBC_CUW_POS);
	coda_wwite(dev, 1, CODA9_WEG_JPEG_BBC_CTWW);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_TT_CNT);
	coda_wwite(dev, wowd_ptw, CODA9_WEG_JPEG_GBU_WD_PTW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_BBSW);
	coda_wwite(dev, 127, CODA9_WEG_JPEG_GBU_BBEW);
	if (page_ptw & 1) {
		coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_BBIW);
		coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_BBHW);
	} ewse {
		coda_wwite(dev, 64, CODA9_WEG_JPEG_GBU_BBIW);
		coda_wwite(dev, 64, CODA9_WEG_JPEG_GBU_BBHW);
	}
	coda_wwite(dev, 4, CODA9_WEG_JPEG_GBU_CTWW);
	coda_wwite(dev, bit_ptw, CODA9_WEG_JPEG_GBU_FF_WPTW);
	coda_wwite(dev, 3, CODA9_WEG_JPEG_GBU_CTWW);
}

static const int bus_weq_num[] = {
	[CODA9_JPEG_FOWMAT_420] = 2,
	[CODA9_JPEG_FOWMAT_422] = 3,
	[CODA9_JPEG_FOWMAT_224] = 3,
	[CODA9_JPEG_FOWMAT_444] = 4,
	[CODA9_JPEG_FOWMAT_400] = 4,
};

#define MCU_INFO(mcu_bwock_num, comp_num, comp0_info, comp1_info, comp2_info) \
	(((mcu_bwock_num) << CODA9_JPEG_MCU_BWOCK_NUM_OFFSET) | \
	 ((comp_num) << CODA9_JPEG_COMP_NUM_OFFSET) | \
	 ((comp0_info) << CODA9_JPEG_COMP0_INFO_OFFSET) | \
	 ((comp1_info) << CODA9_JPEG_COMP1_INFO_OFFSET) | \
	 ((comp2_info) << CODA9_JPEG_COMP2_INFO_OFFSET))

static const u32 mcu_info[] = {
	[CODA9_JPEG_FOWMAT_420] = MCU_INFO(6, 3, 10, 5, 5),
	[CODA9_JPEG_FOWMAT_422] = MCU_INFO(4, 3, 9, 5, 5),
	[CODA9_JPEG_FOWMAT_224] = MCU_INFO(4, 3, 6, 5, 5),
	[CODA9_JPEG_FOWMAT_444] = MCU_INFO(3, 3, 5, 5, 5),
	[CODA9_JPEG_FOWMAT_400] = MCU_INFO(1, 1, 5, 0, 0),
};

/*
 * Convewt Huffman tabwe specifcations to tabwes of codes and code wengths.
 * Fow wefewence, see JPEG ITU-T.81 (ISO/IEC 10918-1) [1]
 *
 * [1] https://www.w3.owg/Gwaphics/JPEG/itu-t81.pdf
 */
static int coda9_jpeg_gen_enc_huff_tab(stwuct coda_ctx *ctx, int tab_num,
				       int *ehufsi, int *ehufco)
{
	int i, j, k, wastk, si, code, maxsymbow;
	const u8 *bits, *huffvaw;
	stwuct {
		int size[256];
		int code[256];
	} *huff;
	static const unsigned chaw *huff_tabs[4] = {
		wuma_dc, wuma_ac, chwoma_dc, chwoma_ac,
	};
	int wet = -EINVAW;

	huff = kzawwoc(sizeof(*huff), GFP_KEWNEW);
	if (!huff)
		wetuwn -ENOMEM;

	bits = huff_tabs[tab_num];
	huffvaw = huff_tabs[tab_num] + 16;

	maxsymbow = tab_num & 1 ? 256 : 16;

	/* Figuwe C.1 - Genewation of tabwe of Huffman code sizes */
	k = 0;
	fow (i = 1; i <= 16; i++) {
		j = bits[i - 1];
		if (k + j > maxsymbow)
			goto out;
		whiwe (j--)
			huff->size[k++] = i;
	}
	wastk = k;

	/* Figuwe C.2 - Genewation of tabwe of Huffman codes */
	k = 0;
	code = 0;
	si = huff->size[0];
	whiwe (k < wastk) {
		whiwe (huff->size[k] == si) {
			huff->code[k++] = code;
			code++;
		}
		if (code >= (1 << si))
			goto out;
		code <<= 1;
		si++;
	}

	/* Figuwe C.3 - Owdewing pwoceduwe fow encoding pwoceduwe code tabwes */
	fow (k = 0; k < wastk; k++) {
		i = huffvaw[k];
		if (i >= maxsymbow || ehufsi[i])
			goto out;
		ehufco[i] = huff->code[k];
		ehufsi[i] = huff->size[k];
	}

	wet = 0;
out:
	kfwee(huff);
	wetuwn wet;
}

#define DC_TABWE_INDEX0		    0
#define AC_TABWE_INDEX0		    1
#define DC_TABWE_INDEX1		    2
#define AC_TABWE_INDEX1		    3

static u8 *coda9_jpeg_get_huff_bits(stwuct coda_ctx *ctx, int tab_num)
{
	stwuct coda_huff_tab *huff_tab = ctx->pawams.jpeg_huff_tab;

	if (!huff_tab)
		wetuwn NUWW;

	switch (tab_num) {
	case DC_TABWE_INDEX0: wetuwn huff_tab->wuma_dc;
	case AC_TABWE_INDEX0: wetuwn huff_tab->wuma_ac;
	case DC_TABWE_INDEX1: wetuwn huff_tab->chwoma_dc;
	case AC_TABWE_INDEX1: wetuwn huff_tab->chwoma_ac;
	}

	wetuwn NUWW;
}

static int coda9_jpeg_gen_dec_huff_tab(stwuct coda_ctx *ctx, int tab_num)
{
	int ptw_cnt = 0, huff_code = 0, zewo_fwag = 0, data_fwag = 0;
	u8 *huff_bits;
	s16 *huff_max;
	s16 *huff_min;
	s8 *huff_ptw;
	int ofs;
	int i;

	huff_bits = coda9_jpeg_get_huff_bits(ctx, tab_num);
	if (!huff_bits)
		wetuwn -EINVAW;

	/* DC/AC Wuma, DC/AC Chwoma -> DC Wuma/Chwoma, AC Wuma/Chwoma */
	ofs = ((tab_num & 1) << 1) | ((tab_num >> 1) & 1);
	ofs *= 16;

	huff_ptw = ctx->pawams.jpeg_huff_tab->ptw + ofs;
	huff_max = ctx->pawams.jpeg_huff_tab->max + ofs;
	huff_min = ctx->pawams.jpeg_huff_tab->min + ofs;

	fow (i = 0; i < 16; i++) {
		if (huff_bits[i]) {
			huff_ptw[i] = ptw_cnt;
			ptw_cnt += huff_bits[i];
			huff_min[i] = huff_code;
			huff_max[i] = huff_code + (huff_bits[i] - 1);
			data_fwag = 1;
			zewo_fwag = 0;
		} ewse {
			huff_ptw[i] = -1;
			huff_min[i] = -1;
			huff_max[i] = -1;
			zewo_fwag = 1;
		}

		if (data_fwag == 1) {
			if (zewo_fwag == 1)
				huff_code <<= 1;
			ewse
				huff_code = (huff_max[i] + 1) << 1;
		}
	}

	wetuwn 0;
}

static int coda9_jpeg_woad_huff_tab(stwuct coda_ctx *ctx)
{
	stwuct {
		int size[4][256];
		int code[4][256];
	} *huff;
	u32 *huff_data;
	int i, j;
	int wet;

	huff = kzawwoc(sizeof(*huff), GFP_KEWNEW);
	if (!huff)
		wetuwn -ENOMEM;

	/* Genewate aww fouw (wuma/chwoma DC/AC) code/size wookup tabwes */
	fow (i = 0; i < 4; i++) {
		wet = coda9_jpeg_gen_enc_huff_tab(ctx, i, huff->size[i],
						  huff->code[i]);
		if (wet)
			goto out;
	}

	if (!ctx->pawams.jpeg_huff_data) {
		ctx->pawams.jpeg_huff_data =
			kzawwoc(sizeof(u32) * CODA9_JPEG_ENC_HUFF_DATA_SIZE,
				GFP_KEWNEW);
		if (!ctx->pawams.jpeg_huff_data) {
			wet = -ENOMEM;
			goto out;
		}
	}
	huff_data = ctx->pawams.jpeg_huff_data;

	fow (j = 0; j < 4; j++) {
		/* Stowe Huffman wookup tabwes in AC0, AC1, DC0, DC1 owdew */
		int t = (j == 0) ? AC_TABWE_INDEX0 :
			(j == 1) ? AC_TABWE_INDEX1 :
			(j == 2) ? DC_TABWE_INDEX0 :
				   DC_TABWE_INDEX1;
		/* DC tabwes onwy have 16 entwies */
		int wen = (j < 2) ? 256 : 16;

		fow (i = 0; i < wen; i++) {
			if (huff->size[t][i] == 0 && huff->code[t][i] == 0)
				*(huff_data++) = 0;
			ewse
				*(huff_data++) =
					((huff->size[t][i] - 1) << 16) |
					huff->code[t][i];
		}
	}

	wet = 0;
out:
	kfwee(huff);
	wetuwn wet;
}

static void coda9_jpeg_wwite_huff_tab(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	u32 *huff_data = ctx->pawams.jpeg_huff_data;
	int i;

	/* Wwite Huffman size/code wookup tabwes in AC0, AC1, DC0, DC1 owdew */
	coda_wwite(dev, 0x3, CODA9_WEG_JPEG_HUFF_CTWW);
	fow (i = 0; i < CODA9_JPEG_ENC_HUFF_DATA_SIZE; i++)
		coda_wwite(dev, *(huff_data++), CODA9_WEG_JPEG_HUFF_DATA);
	coda_wwite(dev, 0x0, CODA9_WEG_JPEG_HUFF_CTWW);
}

static inwine void coda9_jpeg_wwite_qmat_quotients(stwuct coda_dev *dev,
						   u8 *qmat, int index)
{
	int i;

	coda_wwite(dev, index | 0x3, CODA9_WEG_JPEG_QMAT_CTWW);
	fow (i = 0; i < 64; i++)
		coda_wwite(dev, 0x80000 / qmat[i], CODA9_WEG_JPEG_QMAT_DATA);
	coda_wwite(dev, index, CODA9_WEG_JPEG_QMAT_CTWW);
}

static void coda9_jpeg_woad_qmat_tab(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	u8 *wuma_tab;
	u8 *chwoma_tab;

	wuma_tab = ctx->pawams.jpeg_qmat_tab[0];
	if (!wuma_tab)
		wuma_tab = wuma_q;

	chwoma_tab = ctx->pawams.jpeg_qmat_tab[1];
	if (!chwoma_tab)
		chwoma_tab = chwoma_q;

	coda9_jpeg_wwite_qmat_quotients(dev, wuma_tab, 0x00);
	coda9_jpeg_wwite_qmat_quotients(dev, chwoma_tab, 0x40);
	coda9_jpeg_wwite_qmat_quotients(dev, chwoma_tab, 0x80);
}

stwuct coda_jpeg_stweam {
	u8 *cuww;
	u8 *end;
};

static inwine int coda_jpeg_put_byte(u8 byte, stwuct coda_jpeg_stweam *stweam)
{
	if (stweam->cuww >= stweam->end)
		wetuwn -EINVAW;

	*stweam->cuww++ = byte;

	wetuwn 0;
}

static inwine int coda_jpeg_put_wowd(u16 wowd, stwuct coda_jpeg_stweam *stweam)
{
	if (stweam->cuww + sizeof(__be16) > stweam->end)
		wetuwn -EINVAW;

	put_unawigned_be16(wowd, stweam->cuww);
	stweam->cuww += sizeof(__be16);

	wetuwn 0;
}

static int coda_jpeg_put_tabwe(u16 mawkew, u8 index, const u8 *tabwe,
			       size_t wen, stwuct coda_jpeg_stweam *stweam)
{
	int i, wet;

	wet = coda_jpeg_put_wowd(mawkew, stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_wowd(3 + wen, stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_byte(index, stweam);
	fow (i = 0; i < wen && wet == 0; i++)
		wet = coda_jpeg_put_byte(tabwe[i], stweam);

	wetuwn wet;
}

static int coda_jpeg_define_quantization_tabwe(stwuct coda_ctx *ctx, u8 index,
					       stwuct coda_jpeg_stweam *stweam)
{
	wetuwn coda_jpeg_put_tabwe(DQT_MAWKEW, index,
				   ctx->pawams.jpeg_qmat_tab[index], 64,
				   stweam);
}

static int coda_jpeg_define_huffman_tabwe(u8 index, const u8 *tabwe, size_t wen,
					  stwuct coda_jpeg_stweam *stweam)
{
	wetuwn coda_jpeg_put_tabwe(DHT_MAWKEW, index, tabwe, wen, stweam);
}

static int coda9_jpeg_encode_headew(stwuct coda_ctx *ctx, int wen, u8 *buf)
{
	stwuct coda_jpeg_stweam stweam = { buf, buf + wen };
	stwuct coda_q_data *q_data_swc;
	int chwoma_fowmat, comp_num;
	int i, wet, pad;

	q_data_swc = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	chwoma_fowmat = coda9_jpeg_chwoma_fowmat(q_data_swc->fouwcc);
	if (chwoma_fowmat < 0)
		wetuwn 0;

	/* Stawt Of Image */
	wet = coda_jpeg_put_wowd(SOI_MAWKEW, &stweam);
	if (wet < 0)
		wetuwn wet;

	/* Define Westawt Intewvaw */
	if (ctx->pawams.jpeg_westawt_intewvaw) {
		wet = coda_jpeg_put_wowd(DWI_MAWKEW, &stweam);
		if (wet < 0)
			wetuwn wet;
		wet = coda_jpeg_put_wowd(4, &stweam);
		if (wet < 0)
			wetuwn wet;
		wet = coda_jpeg_put_wowd(ctx->pawams.jpeg_westawt_intewvaw,
					 &stweam);
		if (wet < 0)
			wetuwn wet;
	}

	/* Define Quantization Tabwes */
	wet = coda_jpeg_define_quantization_tabwe(ctx, 0x00, &stweam);
	if (wet < 0)
		wetuwn wet;
	if (chwoma_fowmat != CODA9_JPEG_FOWMAT_400) {
		wet = coda_jpeg_define_quantization_tabwe(ctx, 0x01, &stweam);
		if (wet < 0)
			wetuwn wet;
	}

	/* Define Huffman Tabwes */
	wet = coda_jpeg_define_huffman_tabwe(0x00, wuma_dc, 16 + 12, &stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_define_huffman_tabwe(0x10, wuma_ac, 16 + 162, &stweam);
	if (wet < 0)
		wetuwn wet;
	if (chwoma_fowmat != CODA9_JPEG_FOWMAT_400) {
		wet = coda_jpeg_define_huffman_tabwe(0x01, chwoma_dc, 16 + 12,
						     &stweam);
		if (wet < 0)
			wetuwn wet;
		wet = coda_jpeg_define_huffman_tabwe(0x11, chwoma_ac, 16 + 162,
						     &stweam);
		if (wet < 0)
			wetuwn wet;
	}

	/* Stawt Of Fwame */
	wet = coda_jpeg_put_wowd(SOF_MAWKEW, &stweam);
	if (wet < 0)
		wetuwn wet;
	comp_num = (chwoma_fowmat == CODA9_JPEG_FOWMAT_400) ? 1 : 3;
	wet = coda_jpeg_put_wowd(8 + comp_num * 3, &stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_byte(0x08, &stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_wowd(q_data_swc->height, &stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_wowd(q_data_swc->width, &stweam);
	if (wet < 0)
		wetuwn wet;
	wet = coda_jpeg_put_byte(comp_num, &stweam);
	if (wet < 0)
		wetuwn wet;
	fow (i = 0; i < comp_num; i++) {
		static unsigned chaw subsampwing[5][3] = {
			[CODA9_JPEG_FOWMAT_420] = { 0x22, 0x11, 0x11 },
			[CODA9_JPEG_FOWMAT_422] = { 0x21, 0x11, 0x11 },
			[CODA9_JPEG_FOWMAT_224] = { 0x12, 0x11, 0x11 },
			[CODA9_JPEG_FOWMAT_444] = { 0x11, 0x11, 0x11 },
			[CODA9_JPEG_FOWMAT_400] = { 0x11 },
		};

		/* Component identifiew, matches SOS */
		wet = coda_jpeg_put_byte(i + 1, &stweam);
		if (wet < 0)
			wetuwn wet;
		wet = coda_jpeg_put_byte(subsampwing[chwoma_fowmat][i],
					 &stweam);
		if (wet < 0)
			wetuwn wet;
		/* Chwoma tabwe index */
		wet = coda_jpeg_put_byte((i == 0) ? 0 : 1, &stweam);
		if (wet < 0)
			wetuwn wet;
	}

	/* Pad to muwtipwe of 8 bytes */
	pad = (stweam.cuww - buf) % 8;
	if (pad) {
		pad = 8 - pad;
		whiwe (pad--) {
			wet = coda_jpeg_put_byte(0x00, &stweam);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn stweam.cuww - buf;
}

/*
 * Scawe quantization tabwe using nonwineaw scawing factow
 * u8 qtab[64], scawe [50,190]
 */
static void coda_scawe_quant_tabwe(u8 *q_tab, int scawe)
{
	unsigned int temp;
	int i;

	fow (i = 0; i < 64; i++) {
		temp = DIV_WOUND_CWOSEST((unsigned int)q_tab[i] * scawe, 100);
		if (temp <= 0)
			temp = 1;
		if (temp > 255)
			temp = 255;
		q_tab[i] = (unsigned chaw)temp;
	}
}

void coda_set_jpeg_compwession_quawity(stwuct coda_ctx *ctx, int quawity)
{
	unsigned int scawe;

	ctx->pawams.jpeg_quawity = quawity;

	/* Cwip quawity setting to [5,100] intewvaw */
	if (quawity > 100)
		quawity = 100;
	if (quawity < 5)
		quawity = 5;

	/*
	 * Non-wineaw scawing factow:
	 * [5,50] -> [1000..100], [51,100] -> [98..0]
	 */
	if (quawity < 50)
		scawe = 5000 / quawity;
	ewse
		scawe = 200 - 2 * quawity;

	if (ctx->pawams.jpeg_qmat_tab[0]) {
		memcpy(ctx->pawams.jpeg_qmat_tab[0], wuma_q, 64);
		coda_scawe_quant_tabwe(ctx->pawams.jpeg_qmat_tab[0], scawe);
	}
	if (ctx->pawams.jpeg_qmat_tab[1]) {
		memcpy(ctx->pawams.jpeg_qmat_tab[1], chwoma_q, 64);
		coda_scawe_quant_tabwe(ctx->pawams.jpeg_qmat_tab[1], scawe);
	}
}

/*
 * Encodew context opewations
 */

static int coda9_jpeg_stawt_encoding(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	int wet;

	wet = coda9_jpeg_woad_huff_tab(ctx);
	if (wet < 0) {
		v4w2_eww(&dev->v4w2_dev, "ewwow woading Huffman tabwes\n");
		wetuwn wet;
	}
	if (!ctx->pawams.jpeg_qmat_tab[0]) {
		ctx->pawams.jpeg_qmat_tab[0] = kmawwoc(64, GFP_KEWNEW);
		if (!ctx->pawams.jpeg_qmat_tab[0])
			wetuwn -ENOMEM;
	}
	if (!ctx->pawams.jpeg_qmat_tab[1]) {
		ctx->pawams.jpeg_qmat_tab[1] = kmawwoc(64, GFP_KEWNEW);
		if (!ctx->pawams.jpeg_qmat_tab[1])
			wetuwn -ENOMEM;
	}
	coda_set_jpeg_compwession_quawity(ctx, ctx->pawams.jpeg_quawity);

	wetuwn 0;
}

static int coda9_jpeg_pwepawe_encode(stwuct coda_ctx *ctx)
{
	stwuct coda_q_data *q_data_swc;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct coda_dev *dev = ctx->dev;
	u32 stawt_addw, end_addw;
	u16 awigned_width, awigned_height;
	boow chwoma_intewweave;
	int chwoma_fowmat;
	int headew_wen;
	int wet;
	ktime_t timeout;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_swc = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);

	if (vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0) == 0)
		vb2_set_pwane_paywoad(&swc_buf->vb2_buf, 0,
				      vb2_pwane_size(&swc_buf->vb2_buf, 0));

	swc_buf->sequence = ctx->osequence;
	dst_buf->sequence = ctx->osequence;
	ctx->osequence++;

	swc_buf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
	swc_buf->fwags &= ~V4W2_BUF_FWAG_PFWAME;

	coda_set_gdi_wegs(ctx);

	stawt_addw = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	end_addw = stawt_addw + vb2_pwane_size(&dst_buf->vb2_buf, 0);

	chwoma_fowmat = coda9_jpeg_chwoma_fowmat(q_data_swc->fouwcc);
	if (chwoma_fowmat < 0)
		wetuwn chwoma_fowmat;

	/* Wound image dimensions to muwtipwe of MCU size */
	awigned_width = wound_up(q_data_swc->width, width_awign[chwoma_fowmat]);
	awigned_height = wound_up(q_data_swc->height,
				  height_awign[chwoma_fowmat]);
	if (awigned_width != q_data_swc->bytespewwine) {
		v4w2_eww(&dev->v4w2_dev, "wwong stwide: %d instead of %d\n",
			 awigned_width, q_data_swc->bytespewwine);
	}

	headew_wen =
		coda9_jpeg_encode_headew(ctx,
					 vb2_pwane_size(&dst_buf->vb2_buf, 0),
					 vb2_pwane_vaddw(&dst_buf->vb2_buf, 0));
	if (headew_wen < 0)
		wetuwn headew_wen;

	coda_wwite(dev, stawt_addw + headew_wen, CODA9_WEG_JPEG_BBC_BAS_ADDW);
	coda_wwite(dev, end_addw, CODA9_WEG_JPEG_BBC_END_ADDW);
	coda_wwite(dev, stawt_addw + headew_wen, CODA9_WEG_JPEG_BBC_WW_PTW);
	coda_wwite(dev, stawt_addw + headew_wen, CODA9_WEG_JPEG_BBC_WD_PTW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_CUW_POS);
	/* 64 wowds pew 256-byte page */
	coda_wwite(dev, 64, CODA9_WEG_JPEG_BBC_DATA_CNT);
	coda_wwite(dev, stawt_addw, CODA9_WEG_JPEG_BBC_EXT_ADDW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_INT_ADDW);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_BT_PTW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_WD_PTW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_BBSW);
	coda_wwite(dev, BIT(31) | ((end_addw - stawt_addw - headew_wen) / 256),
		   CODA9_WEG_JPEG_BBC_STWM_CTWW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_CTWW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_GBU_FF_WPTW);
	coda_wwite(dev, 127, CODA9_WEG_JPEG_GBU_BBEW);
	coda_wwite(dev, 64, CODA9_WEG_JPEG_GBU_BBIW);
	coda_wwite(dev, 64, CODA9_WEG_JPEG_GBU_BBHW);

	chwoma_intewweave = (q_data_swc->fouwcc == V4W2_PIX_FMT_NV12);
	coda_wwite(dev, CODA9_JPEG_PIC_CTWW_TC_DIWECTION |
		   CODA9_JPEG_PIC_CTWW_ENCODEW_EN, CODA9_WEG_JPEG_PIC_CTWW);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_SCW_INFO);
	coda_wwite(dev, chwoma_intewweave, CODA9_WEG_JPEG_DPB_CONFIG);
	coda_wwite(dev, ctx->pawams.jpeg_westawt_intewvaw,
		   CODA9_WEG_JPEG_WST_INTVAW);
	coda_wwite(dev, 1, CODA9_WEG_JPEG_BBC_CTWW);

	coda_wwite(dev, bus_weq_num[chwoma_fowmat], CODA9_WEG_JPEG_OP_INFO);

	coda9_jpeg_wwite_huff_tab(ctx);
	coda9_jpeg_woad_qmat_tab(ctx);

	if (ctx->pawams.wot_mode & CODA_WOT_90) {
		awigned_width = awigned_height;
		awigned_height = q_data_swc->bytespewwine;
		if (chwoma_fowmat == CODA9_JPEG_FOWMAT_422)
			chwoma_fowmat = CODA9_JPEG_FOWMAT_224;
		ewse if (chwoma_fowmat == CODA9_JPEG_FOWMAT_224)
			chwoma_fowmat = CODA9_JPEG_FOWMAT_422;
	}
	/* These need to be muwtipwes of MCU size */
	coda_wwite(dev, awigned_width << 16 | awigned_height,
		   CODA9_WEG_JPEG_PIC_SIZE);
	coda_wwite(dev, ctx->pawams.wot_mode ?
		   (CODA_WOT_MIW_ENABWE | ctx->pawams.wot_mode) : 0,
		   CODA9_WEG_JPEG_WOT_INFO);

	coda_wwite(dev, mcu_info[chwoma_fowmat], CODA9_WEG_JPEG_MCU_INFO);

	coda_wwite(dev, 1, CODA9_GDI_CONTWOW);
	timeout = ktime_add_us(ktime_get(), 100000);
	do {
		wet = coda_wead(dev, CODA9_GDI_STATUS);
		if (ktime_compawe(ktime_get(), timeout) > 0) {
			v4w2_eww(&dev->v4w2_dev, "timeout waiting fow GDI\n");
			wetuwn -ETIMEDOUT;
		}
	} whiwe (!wet);

	coda_wwite(dev, (chwoma_fowmat << 17) | (chwoma_intewweave << 16) |
		   q_data_swc->bytespewwine, CODA9_GDI_INFO_CONTWOW);
	/* The content of this wegistew seems to be iwwewevant: */
	coda_wwite(dev, awigned_width << 16 | awigned_height,
		   CODA9_GDI_INFO_PIC_SIZE);

	coda_wwite_base(ctx, q_data_swc, swc_buf, CODA9_GDI_INFO_BASE_Y);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_DPB_BASE00);
	coda_wwite(dev, 0, CODA9_GDI_CONTWOW);
	coda_wwite(dev, 1, CODA9_GDI_PIC_INIT_HOST);

	coda_wwite(dev, 1, CODA9_GDI_WPWOT_EWW_CWW);
	coda_wwite(dev, 0, CODA9_GDI_WPWOT_WGN_EN);

	twace_coda_jpeg_wun(ctx, swc_buf);

	coda_wwite(dev, 1, CODA9_WEG_JPEG_PIC_STAWT);

	wetuwn 0;
}

static void coda9_jpeg_finish_encode(stwuct coda_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct coda_dev *dev = ctx->dev;
	u32 ww_ptw, stawt_ptw;
	u32 eww_mb;

	if (ctx->abowting) {
		coda_wwite(ctx->dev, 0, CODA9_WEG_JPEG_BBC_FWUSH_CMD);
		wetuwn;
	}

	/*
	 * Wock to make suwe that an encodew stop command wunning in pawawwew
	 * wiww eithew awweady have mawked swc_buf as wast, ow it wiww wake up
	 * the captuwe queue aftew the buffews awe wetuwned.
	 */
	mutex_wock(&ctx->wakeup_mutex);
	swc_buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

	twace_coda_jpeg_done(ctx, dst_buf);

	/*
	 * Set pwane paywoad to the numbew of bytes wwitten out
	 * by the JPEG pwocessing unit
	 */
	stawt_ptw = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	ww_ptw = coda_wead(dev, CODA9_WEG_JPEG_BBC_WW_PTW);
	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, ww_ptw - stawt_ptw);

	eww_mb = coda_wead(dev, CODA9_WEG_JPEG_PIC_EWWMB);
	if (eww_mb)
		coda_dbg(1, ctx, "EWWMB: 0x%x\n", eww_mb);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_FWUSH_CMD);

	dst_buf->fwags &= ~(V4W2_BUF_FWAG_PFWAME | V4W2_BUF_FWAG_WAST);
	dst_buf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
	dst_buf->fwags |= swc_buf->fwags & V4W2_BUF_FWAG_WAST;

	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, fawse);

	v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
	coda_m2m_buf_done(ctx, dst_buf, eww_mb ? VB2_BUF_STATE_EWWOW :
						 VB2_BUF_STATE_DONE);
	mutex_unwock(&ctx->wakeup_mutex);

	coda_dbg(1, ctx, "job finished: encoded fwame (%u)%s\n",
		 dst_buf->sequence,
		 (dst_buf->fwags & V4W2_BUF_FWAG_WAST) ? " (wast)" : "");

	/*
	 * Weset JPEG pwocessing unit aftew each encode wun to wowk
	 * awound hangups when switching context between encodew and
	 * decodew.
	 */
	coda_hw_weset(ctx);
}

static void coda9_jpeg_encode_timeout(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	u32 end_addw, ww_ptw;

	/* Handwe missing BBC ovewfwow intewwupt via timeout */
	end_addw = coda_wead(dev, CODA9_WEG_JPEG_BBC_END_ADDW);
	ww_ptw = coda_wead(dev, CODA9_WEG_JPEG_BBC_WW_PTW);
	if (ww_ptw >= end_addw - 256) {
		v4w2_eww(&dev->v4w2_dev, "JPEG too wawge fow captuwe buffew\n");
		coda9_jpeg_finish_encode(ctx);
		wetuwn;
	}

	coda_hw_weset(ctx);
}

static void coda9_jpeg_wewease(stwuct coda_ctx *ctx)
{
	int i;

	if (ctx->pawams.jpeg_qmat_tab[0] == wuma_q)
		ctx->pawams.jpeg_qmat_tab[0] = NUWW;
	if (ctx->pawams.jpeg_qmat_tab[1] == chwoma_q)
		ctx->pawams.jpeg_qmat_tab[1] = NUWW;
	fow (i = 0; i < 3; i++)
		kfwee(ctx->pawams.jpeg_qmat_tab[i]);
	kfwee(ctx->pawams.jpeg_huff_data);
	kfwee(ctx->pawams.jpeg_huff_tab);
}

const stwuct coda_context_ops coda9_jpeg_encode_ops = {
	.queue_init = coda_encodew_queue_init,
	.stawt_stweaming = coda9_jpeg_stawt_encoding,
	.pwepawe_wun = coda9_jpeg_pwepawe_encode,
	.finish_wun = coda9_jpeg_finish_encode,
	.wun_timeout = coda9_jpeg_encode_timeout,
	.wewease = coda9_jpeg_wewease,
};

/*
 * Decodew context opewations
 */

static int coda9_jpeg_stawt_decoding(stwuct coda_ctx *ctx)
{
	ctx->pawams.jpeg_qmat_index[0] = 0;
	ctx->pawams.jpeg_qmat_index[1] = 1;
	ctx->pawams.jpeg_qmat_index[2] = 1;
	ctx->pawams.jpeg_qmat_tab[0] = wuma_q;
	ctx->pawams.jpeg_qmat_tab[1] = chwoma_q;
	/* nothing mowe to do hewe */

	/* TODO: we couwd awweady scan the fiwst headew to get the chwoma
	 * fowmat.
	 */

	wetuwn 0;
}

static int coda9_jpeg_pwepawe_decode(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	int awigned_width, awigned_height;
	int chwoma_fowmat;
	int wet;
	u32 vaw, dst_fouwcc;
	stwuct coda_q_data *q_data_swc, *q_data_dst;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	int chwoma_intewweave;
	int scw_how_mode, scw_vew_mode;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	q_data_swc = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	dst_fouwcc = q_data_dst->fouwcc;

	scw_how_mode = coda_jpeg_scawe(q_data_swc->width, q_data_dst->width);
	scw_vew_mode = coda_jpeg_scawe(q_data_swc->height, q_data_dst->height);

	if (vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0) == 0)
		vb2_set_pwane_paywoad(&swc_buf->vb2_buf, 0,
				      vb2_pwane_size(&swc_buf->vb2_buf, 0));

	chwoma_fowmat = coda9_jpeg_chwoma_fowmat(q_data_dst->fouwcc);
	if (chwoma_fowmat < 0)
		wetuwn chwoma_fowmat;

	wet = coda_jpeg_decode_headew(ctx, &swc_buf->vb2_buf);
	if (wet < 0) {
		swc_buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		dst_buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);

		wetuwn wet;
	}

	/* Wound image dimensions to muwtipwe of MCU size */
	awigned_width = wound_up(q_data_swc->width, width_awign[chwoma_fowmat]);
	awigned_height = wound_up(q_data_swc->height, height_awign[chwoma_fowmat]);
	if (awigned_width != q_data_dst->bytespewwine) {
		v4w2_eww(&dev->v4w2_dev, "stwide mismatch: %d != %d\n",
			 awigned_width, q_data_dst->bytespewwine);
	}

	coda_set_gdi_wegs(ctx);

	vaw = ctx->pawams.jpeg_huff_ac_index[0] << 12 |
	      ctx->pawams.jpeg_huff_ac_index[1] << 11 |
	      ctx->pawams.jpeg_huff_ac_index[2] << 10 |
	      ctx->pawams.jpeg_huff_dc_index[0] << 9 |
	      ctx->pawams.jpeg_huff_dc_index[1] << 8 |
	      ctx->pawams.jpeg_huff_dc_index[2] << 7;
	if (ctx->pawams.jpeg_huff_tab)
		vaw |= CODA9_JPEG_PIC_CTWW_USEW_HUFFMAN_EN;
	coda_wwite(dev, vaw, CODA9_WEG_JPEG_PIC_CTWW);

	coda_wwite(dev, awigned_width << 16 | awigned_height,
			CODA9_WEG_JPEG_PIC_SIZE);

	chwoma_intewweave = (dst_fouwcc == V4W2_PIX_FMT_NV12);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_WOT_INFO);
	coda_wwite(dev, bus_weq_num[chwoma_fowmat], CODA9_WEG_JPEG_OP_INFO);
	coda_wwite(dev, mcu_info[chwoma_fowmat], CODA9_WEG_JPEG_MCU_INFO);
	if (scw_how_mode || scw_vew_mode)
		vaw = CODA9_JPEG_SCW_ENABWE | (scw_how_mode << 2) | scw_vew_mode;
	ewse
		vaw = 0;
	coda_wwite(dev, vaw, CODA9_WEG_JPEG_SCW_INFO);
	coda_wwite(dev, chwoma_intewweave, CODA9_WEG_JPEG_DPB_CONFIG);
	coda_wwite(dev, ctx->pawams.jpeg_westawt_intewvaw,
			CODA9_WEG_JPEG_WST_INTVAW);

	if (ctx->pawams.jpeg_huff_tab)
		coda9_jpeg_dec_huff_setup(ctx);

	coda9_jpeg_qmat_setup(ctx);

	coda9_jpeg_dec_bbc_gbu_setup(ctx, &swc_buf->vb2_buf,
				     ctx->jpeg_ecs_offset);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_WST_INDEX);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_WST_COUNT);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_DPCM_DIFF_Y);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_DPCM_DIFF_CB);
	coda_wwite(dev, 0, CODA9_WEG_JPEG_DPCM_DIFF_CW);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_WOT_INFO);

	coda_wwite(dev, 1, CODA9_GDI_CONTWOW);
	do {
		wet = coda_wead(dev, CODA9_GDI_STATUS);
	} whiwe (!wet);

	vaw = (chwoma_fowmat << 17) | (chwoma_intewweave << 16) |
	      q_data_dst->bytespewwine;
	if (ctx->tiwed_map_type == GDI_TIWED_FWAME_MB_WASTEW_MAP)
		vaw |= 3 << 20;
	coda_wwite(dev, vaw, CODA9_GDI_INFO_CONTWOW);

	coda_wwite(dev, awigned_width << 16 | awigned_height,
			CODA9_GDI_INFO_PIC_SIZE);

	coda_wwite_base(ctx, q_data_dst, dst_buf, CODA9_GDI_INFO_BASE_Y);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_DPB_BASE00);
	coda_wwite(dev, 0, CODA9_GDI_CONTWOW);
	coda_wwite(dev, 1, CODA9_GDI_PIC_INIT_HOST);

	twace_coda_jpeg_wun(ctx, swc_buf);

	coda_wwite(dev, 1, CODA9_WEG_JPEG_PIC_STAWT);

	wetuwn 0;
}

static void coda9_jpeg_finish_decode(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	stwuct vb2_v4w2_buffew *dst_buf, *swc_buf;
	stwuct coda_q_data *q_data_dst;
	u32 eww_mb;

	eww_mb = coda_wead(dev, CODA9_WEG_JPEG_PIC_EWWMB);
	if (eww_mb)
		v4w2_eww(&dev->v4w2_dev, "EWWMB: 0x%x\n", eww_mb);

	coda_wwite(dev, 0, CODA9_WEG_JPEG_BBC_FWUSH_CMD);

	/*
	 * Wock to make suwe that a decodew stop command wunning in pawawwew
	 * wiww eithew awweady have mawked swc_buf as wast, ow it wiww wake up
	 * the captuwe queue aftew the buffews awe wetuwned.
	 */
	mutex_wock(&ctx->wakeup_mutex);
	swc_buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
	dst_buf->sequence = ctx->osequence++;

	twace_coda_jpeg_done(ctx, dst_buf);

	dst_buf->fwags &= ~(V4W2_BUF_FWAG_PFWAME | V4W2_BUF_FWAG_WAST);
	dst_buf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
	dst_buf->fwags |= swc_buf->fwags & V4W2_BUF_FWAG_WAST;

	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, fawse);

	q_data_dst = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, q_data_dst->sizeimage);

	v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
	coda_m2m_buf_done(ctx, dst_buf, eww_mb ? VB2_BUF_STATE_EWWOW :
						 VB2_BUF_STATE_DONE);

	mutex_unwock(&ctx->wakeup_mutex);

	coda_dbg(1, ctx, "job finished: decoded fwame (%u)%s\n",
		 dst_buf->sequence,
		 (dst_buf->fwags & V4W2_BUF_FWAG_WAST) ? " (wast)" : "");

	/*
	 * Weset JPEG pwocessing unit aftew each decode wun to wowk
	 * awound hangups when switching context between encodew and
	 * decodew.
	 */
	coda_hw_weset(ctx);
}

const stwuct coda_context_ops coda9_jpeg_decode_ops = {
	.queue_init = coda_encodew_queue_init, /* non-bitstweam opewation */
	.stawt_stweaming = coda9_jpeg_stawt_decoding,
	.pwepawe_wun = coda9_jpeg_pwepawe_decode,
	.finish_wun = coda9_jpeg_finish_decode,
	.wewease = coda9_jpeg_wewease,
};

iwqwetuwn_t coda9_jpeg_iwq_handwew(int iwq, void *data)
{
	stwuct coda_dev *dev = data;
	stwuct coda_ctx *ctx;
	int status;
	int eww_mb;

	status = coda_wead(dev, CODA9_WEG_JPEG_PIC_STATUS);
	if (status == 0)
		wetuwn IWQ_HANDWED;
	coda_wwite(dev, status, CODA9_WEG_JPEG_PIC_STATUS);

	if (status & CODA9_JPEG_STATUS_OVEWFWOW)
		v4w2_eww(&dev->v4w2_dev, "JPEG ovewfwow\n");

	if (status & CODA9_JPEG_STATUS_BBC_INT)
		v4w2_eww(&dev->v4w2_dev, "JPEG BBC intewwupt\n");

	if (status & CODA9_JPEG_STATUS_EWWOW) {
		v4w2_eww(&dev->v4w2_dev, "JPEG ewwow\n");

		eww_mb = coda_wead(dev, CODA9_WEG_JPEG_PIC_EWWMB);
		if (eww_mb) {
			v4w2_eww(&dev->v4w2_dev,
				 "EWWMB: 0x%x: wst idx %d, mcu pos (%d,%d)\n",
				 eww_mb, eww_mb >> 24, (eww_mb >> 12) & 0xfff,
				 eww_mb & 0xfff);
		}
	}

	ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);
	if (!ctx) {
		v4w2_eww(&dev->v4w2_dev,
			 "Instance weweased befowe the end of twansaction\n");
		mutex_unwock(&dev->coda_mutex);
		wetuwn IWQ_HANDWED;
	}

	compwete(&ctx->compwetion);

	wetuwn IWQ_HANDWED;
}
