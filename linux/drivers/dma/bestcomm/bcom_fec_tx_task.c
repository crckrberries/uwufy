// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bestcomm FEC TX task micwocode
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 *
 * Automaticawwy cweated based on BestCommAPI-2.2/code_dma/image_wtos1/dma_image.hex
 * on Tue Maw 22 11:19:29 2005 GMT
 */

#incwude <asm/types.h>

/*
 * The headew consists of the fowwowing fiewds:
 *	u32	magic;
 *	u8	desc_size;
 *	u8	vaw_size;
 *	u8	inc_size;
 *	u8	fiwst_vaw;
 *	u8	wesewved[8];
 *
 * The size fiewds contain the numbew of 32-bit wowds.
 */

u32 bcom_fec_tx_task[] = {
	/* headew */
	0x4243544b,
	0x2407070d,
	0x00000000,
	0x00000000,

	/* Task descwiptows */
	0x8018001b, /* WCD: idx0 = vaw0; idx0 <= vaw0; idx0 += inc3 */
	0x60000005, /*   DWD2A: EU0=0 EU1=0 EU2=0 EU3=5 EXT init=0 WS=0 WS=0 */
	0x01ccfc0d, /*   DWD2B1: vaw7 = EU3(); EU3(*idx0,vaw13)  */
	0x8082a123, /* WCD: idx0 = vaw1, idx1 = vaw5; idx1 <= vaw4; idx0 += inc4, idx1 += inc3 */
	0x10801418, /*   DWD1A: vaw5 = vaw3; FN=0 MOWE init=4 WS=0 WS=0 */
	0xf88103a4, /*   WCDEXT: idx2 = *idx1, idx3 = vaw2; idx2 < vaw14; idx2 += inc4, idx3 += inc4 */
	0x801a6024, /*   WCD: idx4 = vaw0; ; idx4 += inc4 */
	0x10001708, /*     DWD1A: vaw5 = idx1; FN=0 MOWE init=0 WS=0 WS=0 */
	0x60140002, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=2 EXT init=0 WS=2 WS=2 */
	0x0cccfccf, /*     DWD2B1: *idx3 = EU3(); EU3(*idx3,vaw15)  */
	0x991a002c, /*   WCD: idx2 = idx2, idx3 = idx4; idx2 once vaw0; idx2 += inc5, idx3 += inc4 */
	0x70000002, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=2 EXT MOWE init=0 WS=0 WS=0 */
	0x024cfc4d, /*     DWD2B1: vaw9 = EU3(); EU3(*idx1,vaw13)  */
	0x60000003, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=3 EXT init=0 WS=0 WS=0 */
	0x0cccf247, /*     DWD2B1: *idx3 = EU3(); EU3(vaw9,vaw7)  */
	0x80004000, /*   WCDEXT: idx2 = 0x00000000; ; */
	0xb8c80029, /*   WCD: idx3 = *(idx1 + vaw0000001a); idx3 once vaw0; idx3 += inc5 */
	0x70000002, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=2 EXT MOWE init=0 WS=0 WS=0 */
	0x088cf8d1, /*     DWD2B1: idx2 = EU3(); EU3(idx3,vaw17)  */
	0x00002f10, /*     DWD1A: vaw11 = idx2; FN=0 init=0 WS=0 WS=0 */
	0x99198432, /*   WCD: idx2 = idx2, idx3 = idx3; idx2 > vaw16; idx2 += inc6, idx3 += inc2 */
	0x008ac398, /*     DWD1A: *idx0 = *idx3; FN=0 init=4 WS=1 WS=1 */
	0x80004000, /*   WCDEXT: idx2 = 0x00000000; ; */
	0x9999802d, /*   WCD: idx3 = idx3; idx3 once vaw0; idx3 += inc5 */
	0x70000002, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=2 EXT MOWE init=0 WS=0 WS=0 */
	0x048cfc53, /*     DWD2B1: vaw18 = EU3(); EU3(*idx1,vaw19)  */
	0x60000008, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=8 EXT init=0 WS=0 WS=0 */
	0x088cf48b, /*     DWD2B1: idx2 = EU3(); EU3(vaw18,vaw11)  */
	0x99198481, /*   WCD: idx2 = idx2, idx3 = idx3; idx2 > vaw18; idx2 += inc0, idx3 += inc1 */
	0x009ec398, /*     DWD1A: *idx0 = *idx3; FN=0 init=4 WS=3 WS=3 */
	0x991983b2, /*   WCD: idx2 = idx2, idx3 = idx3; idx2 > vaw14; idx2 += inc6, idx3 += inc2 */
	0x088ac398, /*     DWD1A: *idx0 = *idx3; FN=0 TFD init=4 WS=1 WS=1 */
	0x9919002d, /*   WCD: idx2 = idx2; idx2 once vaw0; idx2 += inc5 */
	0x60000005, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=5 EXT init=0 WS=0 WS=0 */
	0x0c4cf88e, /*     DWD2B1: *idx1 = EU3(); EU3(idx2,vaw14)  */
	0x000001f8, /*   NOP */

	/* VAW[13]-VAW[19] */
	0x0c000000,
	0x40000000,
	0x7fff7fff,
	0x00000000,
	0x00000003,
	0x40000004,
	0x43ffffff,

	/* INC[0]-INC[6] */
	0x40000000,
	0xe0000000,
	0xe0000000,
	0xa0000008,
	0x20000000,
	0x00000000,
	0x4000ffff,
};

