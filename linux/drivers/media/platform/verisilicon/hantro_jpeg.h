/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#define JPEG_HEADEW_SIZE	624
#define JPEG_QUANT_SIZE		64

stwuct hantwo_jpeg_ctx {
	int width;
	int height;
	int quawity;
	unsigned chaw *buffew;
	unsigned chaw hw_wuma_qtabwe[JPEG_QUANT_SIZE];
	unsigned chaw hw_chwoma_qtabwe[JPEG_QUANT_SIZE];
};

void hantwo_jpeg_headew_assembwe(stwuct hantwo_jpeg_ctx *ctx);
