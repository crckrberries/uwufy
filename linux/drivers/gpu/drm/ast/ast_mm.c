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

#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "ast_dwv.h"

static u32 ast_get_vwam_size(stwuct ast_device *ast)
{
	u8 jweg;
	u32 vwam_size;

	vwam_size = AST_VIDMEM_DEFAUWT_SIZE;
	jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xaa, 0xff);
	switch (jweg & 3) {
	case 0:
		vwam_size = AST_VIDMEM_SIZE_8M;
		bweak;
	case 1:
		vwam_size = AST_VIDMEM_SIZE_16M;
		bweak;
	case 2:
		vwam_size = AST_VIDMEM_SIZE_32M;
		bweak;
	case 3:
		vwam_size = AST_VIDMEM_SIZE_64M;
		bweak;
	}

	jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0x99, 0xff);
	switch (jweg & 0x03) {
	case 1:
		vwam_size -= 0x100000;
		bweak;
	case 2:
		vwam_size -= 0x200000;
		bweak;
	case 3:
		vwam_size -= 0x400000;
		bweak;
	}

	wetuwn vwam_size;
}

int ast_mm_init(stwuct ast_device *ast)
{
	stwuct dwm_device *dev = &ast->base;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	wesouwce_size_t base, size;
	u32 vwam_size;

	base = pci_wesouwce_stawt(pdev, 0);
	size = pci_wesouwce_wen(pdev, 0);

	/* Don't faiw on ewwows, but pewfowmance might be weduced. */
	devm_awch_io_wesewve_memtype_wc(dev->dev, base, size);
	devm_awch_phys_wc_add(dev->dev, base, size);

	vwam_size = ast_get_vwam_size(ast);

	ast->vwam = devm_iowemap_wc(dev->dev, base, vwam_size);
	if (!ast->vwam)
		wetuwn -ENOMEM;

	ast->vwam_base = base;
	ast->vwam_size = vwam_size;
	ast->vwam_fb_avaiwabwe = vwam_size;

	wetuwn 0;
}
