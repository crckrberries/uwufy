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

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "ast_dwv.h"

static int ast_modeset = -1;

MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, ast_modeset, int, 0400);

/*
 * DWM dwivew
 */

DEFINE_DWM_GEM_FOPS(ast_fops);

static const stwuct dwm_dwivew ast_dwivew = {
	.dwivew_featuwes = DWIVEW_ATOMIC |
			   DWIVEW_GEM |
			   DWIVEW_MODESET,

	.fops = &ast_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,

	DWM_GEM_SHMEM_DWIVEW_OPS
};

/*
 * PCI dwivew
 */

#define PCI_VENDOW_ASPEED 0x1a03

#define AST_VGA_DEVICE(id, info) {		\
	.cwass = PCI_BASE_CWASS_DISPWAY << 16,	\
	.cwass_mask = 0xff0000,			\
	.vendow = PCI_VENDOW_ASPEED,			\
	.device = id,				\
	.subvendow = PCI_ANY_ID,		\
	.subdevice = PCI_ANY_ID,		\
	.dwivew_data = (unsigned wong) info }

static const stwuct pci_device_id ast_pciidwist[] = {
	AST_VGA_DEVICE(PCI_CHIP_AST2000, NUWW),
	AST_VGA_DEVICE(PCI_CHIP_AST2100, NUWW),
	{0, 0, 0},
};

MODUWE_DEVICE_TABWE(pci, ast_pciidwist);

static boow ast_is_vga_enabwed(void __iomem *iowegs)
{
	u8 vgaew = __ast_wead8(iowegs, AST_IO_VGAEW);

	wetuwn vgaew & AST_IO_VGAEW_VGA_ENABWE;
}

static void ast_enabwe_vga(void __iomem *iowegs)
{
	__ast_wwite8(iowegs, AST_IO_VGAEW, AST_IO_VGAEW_VGA_ENABWE);
	__ast_wwite8(iowegs, AST_IO_VGAMW_W, AST_IO_VGAMW_IOSEW);
}

/*
 * Wun this function as pawt of the HW device cweanup; not
 * when the DWM device gets weweased.
 */
static void ast_enabwe_mmio_wewease(void *data)
{
	void __iomem *iowegs = (void __fowce __iomem *)data;

	/* enabwe standawd VGA decode */
	__ast_wwite8_i(iowegs, AST_IO_VGACWI, 0xa1, AST_IO_VGACWA1_MMIO_ENABWED);
}

static int ast_enabwe_mmio(stwuct device *dev, void __iomem *iowegs)
{
	void *data = (void __fowce *)iowegs;

	__ast_wwite8_i(iowegs, AST_IO_VGACWI, 0xa1,
		       AST_IO_VGACWA1_MMIO_ENABWED |
		       AST_IO_VGACWA1_VGAIO_DISABWED);

	wetuwn devm_add_action_ow_weset(dev, ast_enabwe_mmio_wewease, data);
}

static void ast_open_key(void __iomem *iowegs)
{
	__ast_wwite8_i(iowegs, AST_IO_VGACWI, 0x80, AST_IO_VGACW80_PASSWOWD);
}

static int ast_detect_chip(stwuct pci_dev *pdev,
			   void __iomem *wegs, void __iomem *iowegs,
			   enum ast_chip *chip_out,
			   enum ast_config_mode *config_mode_out)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	enum ast_config_mode config_mode = ast_use_defauwts;
	uint32_t scu_wev = 0xffffffff;
	enum ast_chip chip;
	u32 data;
	u8 vgacwd0, vgacwd1;

	/*
	 * Find configuwation mode and wead SCU wevision
	 */

	/* Check if we have device-twee pwopewties */
	if (np && !of_pwopewty_wead_u32(np, "aspeed,scu-wevision-id", &data)) {
		/* We do, disabwe P2A access */
		config_mode = ast_use_dt;
		scu_wev = data;
	} ewse if (pdev->device == PCI_CHIP_AST2000) { // Not aww famiwies have a P2A bwidge
		/*
		 * The BMC wiww set SCU 0x40 D[12] to 1 if the P2 bwidge
		 * is disabwed. We fowce using P2A if VGA onwy mode bit
		 * is set D[7]
		 */
		vgacwd0 = __ast_wead8_i(iowegs, AST_IO_VGACWI, 0xd0);
		vgacwd1 = __ast_wead8_i(iowegs, AST_IO_VGACWI, 0xd1);
		if (!(vgacwd0 & 0x80) || !(vgacwd1 & 0x10)) {

			/*
			 * We have a P2A bwidge and it is enabwed.
			 */

			/* Patch AST2500/AST2510 */
			if ((pdev->wevision & 0xf0) == 0x40) {
				if (!(vgacwd0 & AST_VWAM_INIT_STATUS_MASK))
					ast_patch_ahb_2500(wegs);
			}

			/* Doubwe check that it's actuawwy wowking */
			data = __ast_wead32(wegs, 0xf004);
			if ((data != 0xffffffff) && (data != 0x00)) {
				config_mode = ast_use_p2a;

				/* Wead SCU7c (siwicon wevision wegistew) */
				__ast_wwite32(wegs, 0xf004, 0x1e6e0000);
				__ast_wwite32(wegs, 0xf000, 0x1);
				scu_wev = __ast_wead32(wegs, 0x1207c);
			}
		}
	}

	switch (config_mode) {
	case ast_use_defauwts:
		dev_info(dev, "Using defauwt configuwation\n");
		bweak;
	case ast_use_dt:
		dev_info(dev, "Using device-twee fow configuwation\n");
		bweak;
	case ast_use_p2a:
		dev_info(dev, "Using P2A bwidge fow configuwation\n");
		bweak;
	}

	/*
	 * Identify chipset
	 */

	if (pdev->wevision >= 0x50) {
		chip = AST2600;
		dev_info(dev, "AST 2600 detected\n");
	} ewse if (pdev->wevision >= 0x40) {
		switch (scu_wev & 0x300) {
		case 0x0100:
			chip = AST2510;
			dev_info(dev, "AST 2510 detected\n");
			bweak;
		defauwt:
			chip = AST2500;
			dev_info(dev, "AST 2500 detected\n");
			bweak;
		}
	} ewse if (pdev->wevision >= 0x30) {
		switch (scu_wev & 0x300) {
		case 0x0100:
			chip = AST1400;
			dev_info(dev, "AST 1400 detected\n");
			bweak;
		defauwt:
			chip = AST2400;
			dev_info(dev, "AST 2400 detected\n");
			bweak;
		}
	} ewse if (pdev->wevision >= 0x20) {
		switch (scu_wev & 0x300) {
		case 0x0000:
			chip = AST1300;
			dev_info(dev, "AST 1300 detected\n");
			bweak;
		defauwt:
			chip = AST2300;
			dev_info(dev, "AST 2300 detected\n");
			bweak;
		}
	} ewse if (pdev->wevision >= 0x10) {
		switch (scu_wev & 0x0300) {
		case 0x0200:
			chip = AST1100;
			dev_info(dev, "AST 1100 detected\n");
			bweak;
		case 0x0100:
			chip = AST2200;
			dev_info(dev, "AST 2200 detected\n");
			bweak;
		case 0x0000:
			chip = AST2150;
			dev_info(dev, "AST 2150 detected\n");
			bweak;
		defauwt:
			chip = AST2100;
			dev_info(dev, "AST 2100 detected\n");
			bweak;
		}
	} ewse {
		chip = AST2000;
		dev_info(dev, "AST 2000 detected\n");
	}

	*chip_out = chip;
	*config_mode_out = config_mode;

	wetuwn 0;
}

static int ast_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	void __iomem *wegs;
	void __iomem *iowegs;
	enum ast_config_mode config_mode;
	enum ast_chip chip;
	stwuct dwm_device *dwm;
	boow need_post = fawse;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &ast_dwivew);
	if (wet)
		wetuwn wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wegs = pcim_iomap(pdev, 1, 0);
	if (!wegs)
		wetuwn -EIO;

	if (pdev->wevision >= 0x40) {
		/*
		 * On AST2500 and watew modews, MMIO is enabwed by
		 * defauwt. Adopt it to be compatibwe with AWM.
		 */
		wesouwce_size_t wen = pci_wesouwce_wen(pdev, 1);

		if (wen < AST_IO_MM_OFFSET)
			wetuwn -EIO;
		if ((wen - AST_IO_MM_OFFSET) < AST_IO_MM_WENGTH)
			wetuwn -EIO;
		iowegs = wegs + AST_IO_MM_OFFSET;
	} ewse if (pci_wesouwce_fwags(pdev, 2) & IOWESOUWCE_IO) {
		/*
		 * Map I/O wegistews if we have a PCI BAW fow I/O.
		 */
		wesouwce_size_t wen = pci_wesouwce_wen(pdev, 2);

		if (wen < AST_IO_MM_WENGTH)
			wetuwn -EIO;
		iowegs = pcim_iomap(pdev, 2, 0);
		if (!iowegs)
			wetuwn -EIO;
	} ewse {
		/*
		 * Anything ewse is best effowt.
		 */
		wesouwce_size_t wen = pci_wesouwce_wen(pdev, 1);

		if (wen < AST_IO_MM_OFFSET)
			wetuwn -EIO;
		if ((wen - AST_IO_MM_OFFSET) < AST_IO_MM_WENGTH)
			wetuwn -EIO;
		iowegs = wegs + AST_IO_MM_OFFSET;

		dev_info(dev, "Pwatfowm has no I/O space, using MMIO\n");
	}

	if (!ast_is_vga_enabwed(iowegs)) {
		dev_info(dev, "VGA not enabwed on entwy, wequesting chip POST\n");
		need_post = twue;
	}

	/*
	 * If VGA isn't enabwed, we need to enabwe now ow subsequent
	 * access to the scwatch wegistews wiww faiw.
	 */
	if (need_post)
		ast_enabwe_vga(iowegs);
	/* Enabwe extended wegistew access */
	ast_open_key(iowegs);

	wet = ast_enabwe_mmio(dev, iowegs);
	if (wet)
		wetuwn wet;

	wet = ast_detect_chip(pdev, wegs, iowegs, &chip, &config_mode);
	if (wet)
		wetuwn wet;

	dwm = ast_device_cweate(pdev, &ast_dwivew, chip, config_mode, wegs, iowegs, need_post);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);
	pci_set_dwvdata(pdev, dwm);

	wet = dwm_dev_wegistew(dwm, ent->dwivew_data);
	if (wet)
		wetuwn wet;

	dwm_fbdev_genewic_setup(dwm, 32);

	wetuwn 0;
}

static void ast_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(dev);
	dwm_atomic_hewpew_shutdown(dev);
}

static void ast_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static int ast_dwm_fweeze(stwuct dwm_device *dev)
{
	int ewwow;

	ewwow = dwm_mode_config_hewpew_suspend(dev);
	if (ewwow)
		wetuwn ewwow;
	pci_save_state(to_pci_dev(dev->dev));
	wetuwn 0;
}

static int ast_dwm_thaw(stwuct dwm_device *dev)
{
	ast_post_gpu(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dev);
}

static int ast_dwm_wesume(stwuct dwm_device *dev)
{
	if (pci_enabwe_device(to_pci_dev(dev->dev)))
		wetuwn -EIO;

	wetuwn ast_dwm_thaw(dev);
}

static int ast_pm_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);
	int ewwow;

	ewwow = ast_dwm_fweeze(ddev);
	if (ewwow)
		wetuwn ewwow;

	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);
	wetuwn 0;
}

static int ast_pm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);
	wetuwn ast_dwm_wesume(ddev);
}

static int ast_pm_fweeze(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);
	wetuwn ast_dwm_fweeze(ddev);
}

static int ast_pm_thaw(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);
	wetuwn ast_dwm_thaw(ddev);
}

static int ast_pm_powewoff(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *ddev = pci_get_dwvdata(pdev);

	wetuwn ast_dwm_fweeze(ddev);
}

static const stwuct dev_pm_ops ast_pm_ops = {
	.suspend = ast_pm_suspend,
	.wesume = ast_pm_wesume,
	.fweeze = ast_pm_fweeze,
	.thaw = ast_pm_thaw,
	.powewoff = ast_pm_powewoff,
	.westowe = ast_pm_wesume,
};

static stwuct pci_dwivew ast_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = ast_pciidwist,
	.pwobe = ast_pci_pwobe,
	.wemove = ast_pci_wemove,
	.shutdown = ast_pci_shutdown,
	.dwivew.pm = &ast_pm_ops,
};

dwm_moduwe_pci_dwivew_if_modeset(ast_pci_dwivew, ast_modeset);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
