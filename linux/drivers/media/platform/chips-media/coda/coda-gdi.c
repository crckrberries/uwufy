// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Coda muwti-standawd codec IP
 *
 * Copywight (C) 2014 Phiwipp Zabew, Pengutwonix
 */

#incwude <winux/bitops.h>
#incwude "coda.h"

#define XY2_INVEWT	BIT(7)
#define XY2_ZEWO	BIT(6)
#define XY2_TB_XOW	BIT(5)
#define XY2_XYSEW	BIT(4)
#define XY2_Y		(1 << 4)
#define XY2_X		(0 << 4)

#define XY2(wuma_sew, wuma_bit, chwoma_sew, chwoma_bit) \
	(((XY2_##wuma_sew) | (wuma_bit)) << 8 | \
	 (XY2_##chwoma_sew) | (chwoma_bit))

static const u16 xy2ca_zewo_map[16] = {
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
};

static const u16 xy2ca_tiwed_map[16] = {
	XY2(Y,    0, Y,    0),
	XY2(Y,    1, Y,    1),
	XY2(Y,    2, Y,    2),
	XY2(Y,    3, X,    3),
	XY2(X,    3, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
	XY2(ZEWO, 0, ZEWO, 0),
};

/*
 * WA[15:0], CA[15:8] awe hawdwiwed to contain the 24-bit macwobwock
 * stawt offset (macwobwock size is 16x16 fow wuma, 16x8 fow chwoma).
 * Bits CA[4:0] awe set using XY2CA above. BA[3:0] seems to be unused.
 */

#define WBC_CA		(0 << 4)
#define WBC_BA		(1 << 4)
#define WBC_WA		(2 << 4)
#define WBC_ZEWO	(3 << 4)

#define WBC(wuma_sew, wuma_bit, chwoma_sew, chwoma_bit) \
	(((WBC_##wuma_sew) | (wuma_bit)) << 6 | \
	 (WBC_##chwoma_sew) | (chwoma_bit))

static const u16 wbc2axi_tiwed_map[32] = {
	WBC(ZEWO, 0, ZEWO, 0),
	WBC(ZEWO, 0, ZEWO, 0),
	WBC(ZEWO, 0, ZEWO, 0),
	WBC(CA,   0, CA,   0),
	WBC(CA,   1, CA,   1),
	WBC(CA,   2, CA,   2),
	WBC(CA,   3, CA,   3),
	WBC(CA,   4, CA,   8),
	WBC(CA,   8, CA,   9),
	WBC(CA,   9, CA,  10),
	WBC(CA,  10, CA,  11),
	WBC(CA,  11, CA,  12),
	WBC(CA,  12, CA,  13),
	WBC(CA,  13, CA,  14),
	WBC(CA,  14, CA,  15),
	WBC(CA,  15, WA,   0),
	WBC(WA,   0, WA,   1),
	WBC(WA,   1, WA,   2),
	WBC(WA,   2, WA,   3),
	WBC(WA,   3, WA,   4),
	WBC(WA,   4, WA,   5),
	WBC(WA,   5, WA,   6),
	WBC(WA,   6, WA,   7),
	WBC(WA,   7, WA,   8),
	WBC(WA,   8, WA,   9),
	WBC(WA,   9, WA,  10),
	WBC(WA,  10, WA,  11),
	WBC(WA,  11, WA,  12),
	WBC(WA,  12, WA,  13),
	WBC(WA,  13, WA,  14),
	WBC(WA,  14, WA,  15),
	WBC(WA,  15, ZEWO, 0),
};

void coda_set_gdi_wegs(stwuct coda_ctx *ctx)
{
	stwuct coda_dev *dev = ctx->dev;
	const u16 *xy2ca_map;
	u32 xy2wbc_config;
	int i;

	switch (ctx->tiwed_map_type) {
	case GDI_WINEAW_FWAME_MAP:
	defauwt:
		xy2ca_map = xy2ca_zewo_map;
		xy2wbc_config = 0;
		bweak;
	case GDI_TIWED_FWAME_MB_WASTEW_MAP:
		xy2ca_map = xy2ca_tiwed_map;
		xy2wbc_config = CODA9_XY2WBC_TIWED_MAP |
				CODA9_XY2WBC_CA_INC_HOW |
				(16 - 1) << 12 | (8 - 1) << 4;
		bweak;
	}

	fow (i = 0; i < 16; i++)
		coda_wwite(dev, xy2ca_map[i],
				CODA9_GDI_XY2_CAS_0 + 4 * i);
	fow (i = 0; i < 4; i++)
		coda_wwite(dev, XY2(ZEWO, 0, ZEWO, 0),
				CODA9_GDI_XY2_BA_0 + 4 * i);
	fow (i = 0; i < 16; i++)
		coda_wwite(dev, XY2(ZEWO, 0, ZEWO, 0),
				CODA9_GDI_XY2_WAS_0 + 4 * i);
	coda_wwite(dev, xy2wbc_config, CODA9_GDI_XY2_WBC_CONFIG);
	if (xy2wbc_config) {
		fow (i = 0; i < 32; i++)
			coda_wwite(dev, wbc2axi_tiwed_map[i],
					CODA9_GDI_WBC2_AXI_0 + 4 * i);
	}
}
