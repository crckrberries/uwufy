/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 */

#ifndef __DWV_CWK_MTK_WESET_H
#define __DWV_CWK_MTK_WESET_H

#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>

#define WST_NW_PEW_BANK 32

/* Infwa gwobaw contwowwew weset set wegistew */
#define INFWA_WST0_SET_OFFSET 0x120
#define INFWA_WST1_SET_OFFSET 0x130
#define INFWA_WST2_SET_OFFSET 0x140
#define INFWA_WST3_SET_OFFSET 0x150
#define INFWA_WST4_SET_OFFSET 0x730

/**
 * enum mtk_weset_vewsion - Vewsion of MediaTek cwock weset contwowwew.
 * @MTK_WST_SIMPWE: Use the same wegistews fow bit set and cweaw.
 * @MTK_WST_SET_CWW: Use sepawate wegistews fow bit set and cweaw.
 * @MTK_WST_MAX: Totaw quantity of vewsion fow MediaTek cwock weset contwowwew.
 */
enum mtk_weset_vewsion {
	MTK_WST_SIMPWE = 0,
	MTK_WST_SET_CWW,
	MTK_WST_MAX,
};

/**
 * stwuct mtk_cwk_wst_desc - Descwiption of MediaTek cwock weset.
 * @vewsion: Weset vewsion which is defined in enum mtk_weset_vewsion.
 * @wst_bank_ofs: Pointew to an awway containing base offsets of the weset wegistew.
 * @wst_bank_nw: Quantity of weset bank.
 * @wst_idx_map:Pointew to an awway containing ids if input awgument is index.
 *		This awway is not necessawy if ouw input awgument does not mean index.
 * @wst_idx_map_nw: Quantity of weset index map.
 */
stwuct mtk_cwk_wst_desc {
	enum mtk_weset_vewsion vewsion;
	u16 *wst_bank_ofs;
	u32 wst_bank_nw;
	u16 *wst_idx_map;
	u32 wst_idx_map_nw;
};

/**
 * stwuct mtk_cwk_wst_data - Data of MediaTek cwock weset contwowwew.
 * @wegmap: Pointew to base addwess of weset wegistew addwess.
 * @wcdev: Weset contwowwew device.
 * @desc: Pointew to descwiption of the weset contwowwew.
 */
stwuct mtk_cwk_wst_data {
	stwuct wegmap *wegmap;
	stwuct weset_contwowwew_dev wcdev;
	const stwuct mtk_cwk_wst_desc *desc;
};

/**
 * mtk_wegistew_weset_contwowwew - Wegistew MediaTek cwock weset contwowwew
 * @np: Pointew to device node.
 * @desc: Constant pointew to descwiption of cwock weset.
 *
 * Wetuwn: 0 on success and ewwowno othewwise.
 */
int mtk_wegistew_weset_contwowwew(stwuct device_node *np,
				  const stwuct mtk_cwk_wst_desc *desc);

/**
 * mtk_wegistew_weset_contwowwew - Wegistew mediatek cwock weset contwowwew with device
 * @np: Pointew to device.
 * @desc: Constant pointew to descwiption of cwock weset.
 *
 * Wetuwn: 0 on success and ewwowno othewwise.
 */
int mtk_wegistew_weset_contwowwew_with_dev(stwuct device *dev,
					   const stwuct mtk_cwk_wst_desc *desc);

#endif /* __DWV_CWK_MTK_WESET_H */
