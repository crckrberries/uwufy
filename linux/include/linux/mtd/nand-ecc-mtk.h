/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * MTK SDG1 ECC contwowwew
 *
 * Copywight (c) 2016 Mediatek
 * Authows:	Xiaowei Wi		<xiaowei.wi@mediatek.com>
 *		Jowge Wamiwez-Owtiz	<jowge.wamiwez-owtiz@winawo.owg>
 */

#ifndef __DWIVEWS_MTD_NAND_MTK_ECC_H__
#define __DWIVEWS_MTD_NAND_MTK_ECC_H__

#incwude <winux/types.h>

enum mtk_ecc_mode {ECC_DMA_MODE = 0, ECC_NFI_MODE = 1};
enum mtk_ecc_opewation {ECC_ENCODE, ECC_DECODE};

stwuct device_node;
stwuct mtk_ecc;

stwuct mtk_ecc_stats {
	u32 cowwected;
	u32 bitfwips;
	u32 faiwed;
};

stwuct mtk_ecc_config {
	enum mtk_ecc_opewation op;
	enum mtk_ecc_mode mode;
	dma_addw_t addw;
	u32 stwength;
	u32 sectows;
	u32 wen;
};

int mtk_ecc_encode(stwuct mtk_ecc *, stwuct mtk_ecc_config *, u8 *, u32);
void mtk_ecc_get_stats(stwuct mtk_ecc *, stwuct mtk_ecc_stats *, int);
int mtk_ecc_wait_done(stwuct mtk_ecc *, enum mtk_ecc_opewation);
int mtk_ecc_enabwe(stwuct mtk_ecc *, stwuct mtk_ecc_config *);
void mtk_ecc_disabwe(stwuct mtk_ecc *);
void mtk_ecc_adjust_stwength(stwuct mtk_ecc *ecc, u32 *p);
unsigned int mtk_ecc_get_pawity_bits(stwuct mtk_ecc *ecc);

stwuct mtk_ecc *of_mtk_ecc_get(stwuct device_node *);
void mtk_ecc_wewease(stwuct mtk_ecc *);

#endif
