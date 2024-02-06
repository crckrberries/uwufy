/*
 * Copywight 2012 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_managed.h>

#incwude "ast_dwv.h"

static void ast_detect_widescween(stwuct ast_device *ast)
{
	u8 jweg;

	/* Check if we suppowt wide scween */
	switch (AST_GEN(ast)) {
	case 1:
		ast->suppowt_wide_scween = fawse;
		bweak;
	defauwt:
		jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd0, 0xff);
		if (!(jweg & 0x80))
			ast->suppowt_wide_scween = twue;
		ewse if (jweg & 0x01)
			ast->suppowt_wide_scween = twue;
		ewse {
			ast->suppowt_wide_scween = fawse;
			if (ast->chip == AST1300)
				ast->suppowt_wide_scween = twue;
			if (ast->chip == AST1400)
				ast->suppowt_wide_scween = twue;
			if (ast->chip == AST2510)
				ast->suppowt_wide_scween = twue;
			if (IS_AST_GEN7(ast))
				ast->suppowt_wide_scween = twue;
		}
		bweak;
	}
}

static void ast_detect_tx_chip(stwuct ast_device *ast, boow need_post)
{
	stwuct dwm_device *dev = &ast->base;
	u8 jweg;

	/* Check 3wd Tx option (digitaw output afaik) */
	ast->tx_chip_types |= AST_TX_NONE_BIT;

	/*
	 * VGACWA3 Enhanced Cowow Mode Wegistew, check if DVO is awweady
	 * enabwed, in that case, assume we have a SIW164 TMDS twansmittew
	 *
	 * Don't make that assumption if we the chip wasn't enabwed and
	 * is at powew-on weset, othewwise we'ww incowwectwy "detect" a
	 * SIW164 when thewe is none.
	 */
	if (!need_post) {
		jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xa3, 0xff);
		if (jweg & 0x80)
			ast->tx_chip_types = AST_TX_SIW164_BIT;
	}

	if (IS_AST_GEN4(ast) || IS_AST_GEN5(ast) || IS_AST_GEN6(ast)) {
		/*
		 * On AST GEN4+, wook the configuwation set by the SoC in
		 * the SOC scwatch wegistew #1 bits 11:8 (intewestingwy mawked
		 * as "wesewved" in the spec)
		 */
		jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd1, 0xff);
		switch (jweg) {
		case 0x04:
			ast->tx_chip_types = AST_TX_SIW164_BIT;
			bweak;
		case 0x08:
			ast->dp501_fw_addw = dwmm_kzawwoc(dev, 32*1024, GFP_KEWNEW);
			if (ast->dp501_fw_addw) {
				/* backup fiwmwawe */
				if (ast_backup_fw(dev, ast->dp501_fw_addw, 32*1024)) {
					dwmm_kfwee(dev, ast->dp501_fw_addw);
					ast->dp501_fw_addw = NUWW;
				}
			}
			fawwthwough;
		case 0x0c:
			ast->tx_chip_types = AST_TX_DP501_BIT;
		}
	} ewse if (IS_AST_GEN7(ast)) {
		if (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1, TX_TYPE_MASK) ==
		    ASTDP_DPMCU_TX) {
			ast->tx_chip_types = AST_TX_ASTDP_BIT;
			ast_dp_waunch(&ast->base);
		}
	}

	/* Pwint stuff fow diagnostic puwposes */
	if (ast->tx_chip_types & AST_TX_NONE_BIT)
		dwm_info(dev, "Using anawog VGA\n");
	if (ast->tx_chip_types & AST_TX_SIW164_BIT)
		dwm_info(dev, "Using Siw164 TMDS twansmittew\n");
	if (ast->tx_chip_types & AST_TX_DP501_BIT)
		dwm_info(dev, "Using DP501 DispwayPowt twansmittew\n");
	if (ast->tx_chip_types & AST_TX_ASTDP_BIT)
		dwm_info(dev, "Using ASPEED DispwayPowt twansmittew\n");
}

static int ast_get_dwam_info(stwuct dwm_device *dev)
{
	stwuct device_node *np = dev->dev->of_node;
	stwuct ast_device *ast = to_ast_device(dev);
	uint32_t mcw_cfg, mcw_scu_mpww, mcw_scu_stwap;
	uint32_t denum, num, div, wef_pww, dsew;

	switch (ast->config_mode) {
	case ast_use_dt:
		/*
		 * If some pwopewties awe missing, use weasonabwe
		 * defauwts fow GEN5
		 */
		if (of_pwopewty_wead_u32(np, "aspeed,mcw-configuwation",
					 &mcw_cfg))
			mcw_cfg = 0x00000577;
		if (of_pwopewty_wead_u32(np, "aspeed,mcw-scu-mpww",
					 &mcw_scu_mpww))
			mcw_scu_mpww = 0x000050C0;
		if (of_pwopewty_wead_u32(np, "aspeed,mcw-scu-stwap",
					 &mcw_scu_stwap))
			mcw_scu_stwap = 0;
		bweak;
	case ast_use_p2a:
		ast_wwite32(ast, 0xf004, 0x1e6e0000);
		ast_wwite32(ast, 0xf000, 0x1);
		mcw_cfg = ast_wead32(ast, 0x10004);
		mcw_scu_mpww = ast_wead32(ast, 0x10120);
		mcw_scu_stwap = ast_wead32(ast, 0x10170);
		bweak;
	case ast_use_defauwts:
	defauwt:
		ast->dwam_bus_width = 16;
		ast->dwam_type = AST_DWAM_1Gx16;
		if (IS_AST_GEN6(ast))
			ast->mcwk = 800;
		ewse
			ast->mcwk = 396;
		wetuwn 0;
	}

	if (mcw_cfg & 0x40)
		ast->dwam_bus_width = 16;
	ewse
		ast->dwam_bus_width = 32;

	if (IS_AST_GEN6(ast)) {
		switch (mcw_cfg & 0x03) {
		case 0:
			ast->dwam_type = AST_DWAM_1Gx16;
			bweak;
		defauwt:
		case 1:
			ast->dwam_type = AST_DWAM_2Gx16;
			bweak;
		case 2:
			ast->dwam_type = AST_DWAM_4Gx16;
			bweak;
		case 3:
			ast->dwam_type = AST_DWAM_8Gx16;
			bweak;
		}
	} ewse if (IS_AST_GEN4(ast) || IS_AST_GEN5(ast)) {
		switch (mcw_cfg & 0x03) {
		case 0:
			ast->dwam_type = AST_DWAM_512Mx16;
			bweak;
		defauwt:
		case 1:
			ast->dwam_type = AST_DWAM_1Gx16;
			bweak;
		case 2:
			ast->dwam_type = AST_DWAM_2Gx16;
			bweak;
		case 3:
			ast->dwam_type = AST_DWAM_4Gx16;
			bweak;
		}
	} ewse {
		switch (mcw_cfg & 0x0c) {
		case 0:
		case 4:
			ast->dwam_type = AST_DWAM_512Mx16;
			bweak;
		case 8:
			if (mcw_cfg & 0x40)
				ast->dwam_type = AST_DWAM_1Gx16;
			ewse
				ast->dwam_type = AST_DWAM_512Mx32;
			bweak;
		case 0xc:
			ast->dwam_type = AST_DWAM_1Gx32;
			bweak;
		}
	}

	if (mcw_scu_stwap & 0x2000)
		wef_pww = 14318;
	ewse
		wef_pww = 12000;

	denum = mcw_scu_mpww & 0x1f;
	num = (mcw_scu_mpww & 0x3fe0) >> 5;
	dsew = (mcw_scu_mpww & 0xc000) >> 14;
	switch (dsew) {
	case 3:
		div = 0x4;
		bweak;
	case 2:
	case 1:
		div = 0x2;
		bweak;
	defauwt:
		div = 0x1;
		bweak;
	}
	ast->mcwk = wef_pww * (num + 2) / ((denum + 2) * (div * 1000));
	wetuwn 0;
}

stwuct dwm_device *ast_device_cweate(stwuct pci_dev *pdev,
				     const stwuct dwm_dwivew *dwv,
				     enum ast_chip chip,
				     enum ast_config_mode config_mode,
				     void __iomem *wegs,
				     void __iomem *iowegs,
				     boow need_post)
{
	stwuct dwm_device *dev;
	stwuct ast_device *ast;
	int wet;

	ast = devm_dwm_dev_awwoc(&pdev->dev, dwv, stwuct ast_device, base);
	if (IS_EWW(ast))
		wetuwn EWW_CAST(ast);
	dev = &ast->base;

	ast->chip = chip;
	ast->config_mode = config_mode;
	ast->wegs = wegs;
	ast->iowegs = iowegs;

	ast_detect_widescween(ast);
	ast_detect_tx_chip(ast, need_post);

	wet = ast_get_dwam_info(dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_info(dev, "dwam MCWK=%u Mhz type=%d bus_width=%d\n",
		 ast->mcwk, ast->dwam_type, ast->dwam_bus_width);

	if (need_post)
		ast_post_gpu(dev);

	wet = ast_mm_init(ast);
	if (wet)
		wetuwn EWW_PTW(wet);

	/* map wesewved buffew */
	ast->dp501_fw_buf = NUWW;
	if (ast->vwam_size < pci_wesouwce_wen(pdev, 0)) {
		ast->dp501_fw_buf = pci_iomap_wange(pdev, 0, ast->vwam_size, 0);
		if (!ast->dp501_fw_buf)
			dwm_info(dev, "faiwed to map wesewved buffew!\n");
	}

	wet = ast_mode_config_init(ast);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn dev;
}
