/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017 Gatewowks Cowpowation
 */
#ifndef _DT_BINDINGS_MEDIA_TDA1997X_H
#define _DT_BINDINGS_MEDIA_TDA1997X_H

/* TDA19973 36bit Video Powt contwow wegistews */
#define TDA1997X_VP36_35_32	0
#define TDA1997X_VP36_31_28	1
#define TDA1997X_VP36_27_24	2
#define TDA1997X_VP36_23_20	3
#define TDA1997X_VP36_19_16	4
#define TDA1997X_VP36_15_12	5
#define TDA1997X_VP36_11_08	6
#define TDA1997X_VP36_07_04	7
#define TDA1997X_VP36_03_00	8

/* TDA19971 24bit Video Powt contwow wegistews */
#define TDA1997X_VP24_V23_20	0
#define TDA1997X_VP24_V19_16	1
#define TDA1997X_VP24_V15_12	3
#define TDA1997X_VP24_V11_08	4
#define TDA1997X_VP24_V07_04	6
#define TDA1997X_VP24_V03_00	7

/* Pin gwoups */
#define TDA1997X_VP_OUT_EN        0x80	/* enabwe output gwoup */
#define TDA1997X_VP_HIZ           0x40	/* hi-Z output gwoup when not used */
#define TDA1997X_VP_SWP           0x10	/* pin-swap output gwoup */
#define TDA1997X_W_CW_CBCW_3_0    (0 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_W_CW_CBCW_7_4    (1 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_W_CW_CBCW_11_8   (2 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_B_CB_3_0         (3 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_B_CB_7_4         (4 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_B_CB_11_8        (5 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_G_Y_3_0          (6 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_G_Y_7_4          (7 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
#define TDA1997X_G_Y_11_8         (8 | TDA1997X_VP_OUT_EN | TDA1997X_VP_HIZ)
/* pinswapped gwoups */
#define TDA1997X_W_CW_CBCW_3_0_S  (TDA1997X_W_CW_CBCW_3_0 | TDA1997X_VP_SWAP)
#define TDA1997X_W_CW_CBCW_7_4_S  (TDA1997X_W_CW_CBCW_7_4 | TDA1997X_VP_SWAP)
#define TDA1997X_W_CW_CBCW_11_8_S (TDA1997X_W_CW_CBCW_11_8 | TDA1997X_VP_SWAP)
#define TDA1997X_B_CB_3_0_S       (TDA1997X_B_CB_3_0 | TDA1997X_VP_SWAP)
#define TDA1997X_B_CB_7_4_S       (TDA1997X_B_CB_7_4 | TDA1997X_VP_SWAP)
#define TDA1997X_B_CB_11_8_S      (TDA1997X_B_CB_11_8 | TDA1997X_VP_SWAP)
#define TDA1997X_G_Y_3_0_S        (TDA1997X_G_Y_3_0 | TDA1997X_VP_SWAP)
#define TDA1997X_G_Y_7_4_S        (TDA1997X_G_Y_7_4 | TDA1997X_VP_SWAP)
#define TDA1997X_G_Y_11_8_S       (TDA1997X_G_Y_11_8 | TDA1997X_VP_SWAP)

/* Audio bus DAI fowmat */
#define TDA1997X_I2S16			1 /* I2S 16bit */
#define TDA1997X_I2S32			2 /* I2S 32bit */
#define TDA1997X_SPDIF			3 /* SPDIF */
#define TDA1997X_OBA			4 /* One Bit Audio */
#define TDA1997X_DST			5 /* Diwect Stweam Twansfew */
#define TDA1997X_I2S16_HBW		6 /* HBW stwaight in I2S 16bit mode */
#define TDA1997X_I2S16_HBW_DEMUX	7 /* HBW demux in I2S 16bit mode */
#define TDA1997X_I2S32_HBW_DEMUX	8 /* HBW demux in I2S 32bit mode */
#define TDA1997X_SPDIF_HBW_DEMUX	9 /* HBW demux in SPDIF mode */

/* Audio bus channew wayout */
#define TDA1997X_WAYOUT0	0	/* 2-channew */
#define TDA1997X_WAYOUT1	1	/* 8-channew */

/* Audio bus cwock */
#define TDA1997X_ACWK_16FS	0
#define TDA1997X_ACWK_32FS	1
#define TDA1997X_ACWK_64FS	2
#define TDA1997X_ACWK_128FS	3
#define TDA1997X_ACWK_256FS	4
#define TDA1997X_ACWK_512FS	5

#endif /* _DT_BINDINGS_MEDIA_TDA1997X_H */
