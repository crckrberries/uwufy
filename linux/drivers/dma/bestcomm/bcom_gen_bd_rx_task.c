// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bestcomm GenBD WX task micwocode
 *
 * Copywight (C) 2006 AppSpec Computew Technowogies Cowp.
 *                    Jeff Gibbons <jeff.gibbons@appspec.com>
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 *
 * Based on BestCommAPI-2.2/code_dma/image_wtos1/dma_image.hex
 * on Tue Maw 4 10:14:12 2006 GMT
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

u32 bcom_gen_bd_wx_task[] = {
	/* headew */
	0x4243544b,
	0x0d020409,
	0x00000000,
	0x00000000,

	/* Task descwiptows */
	0x808220da, /* WCD: idx0 = vaw1, idx1 = vaw4; idx1 <= vaw3; idx0 += inc3, idx1 += inc2 */
	0x13e01010, /*   DWD1A: vaw4 = vaw2; FN=0 MOWE init=31 WS=0 WS=0 */
	0xb880025b, /*   WCD: idx2 = *idx1, idx3 = vaw0; idx2 < vaw9; idx2 += inc3, idx3 += inc3 */
	0x10001308, /*     DWD1A: vaw4 = idx1; FN=0 MOWE init=0 WS=0 WS=0 */
	0x60140002, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=2 EXT init=0 WS=2 WS=2 */
	0x0cccfcca, /*     DWD2B1: *idx3 = EU3(); EU3(*idx3,vaw10)  */
	0xd9190240, /*   WCDEXT: idx2 = idx2; idx2 > vaw9; idx2 += inc0 */
	0xb8c5e009, /*   WCD: idx3 = *(idx1 + vaw00000015); ; idx3 += inc1 */
	0x07fecf80, /*     DWD1A: *idx3 = *idx0; FN=0 INT init=31 WS=3 WS=3 */
	0x99190024, /*   WCD: idx2 = idx2; idx2 once vaw0; idx2 += inc4 */
	0x60000005, /*     DWD2A: EU0=0 EU1=0 EU2=0 EU3=5 EXT init=0 WS=0 WS=0 */
	0x0c4cf889, /*     DWD2B1: *idx1 = EU3(); EU3(idx2,vaw9)  */
	0x000001f8, /*   NOP */

	/* VAW[9]-VAW[10] */
	0x40000000,
	0x7fff7fff,

	/* INC[0]-INC[3] */
	0x40000000,
	0xe0000000,
	0xa0000008,
	0x20000000,
};

