// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Hisiwicon Hibmc SoC dwm dwivew
 *
 * Based on the bochs dwm dwivew.
 *
 * Copywight (c) 2016 Huawei Wimited.
 *
 * Authow:
 *	Wongwong Zou <zouwongwong@huawei.com>
 *	Wongwong Zou <zouwongwong@gmaiw.com>
 *	Jianhua Wi <wijianhua@huawei.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_vwam_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "hibmc_dwm_dwv.h"
#incwude "hibmc_dwm_wegs.h"

DEFINE_DWM_GEM_FOPS(hibmc_fops);

static iwqwetuwn_t hibmc_intewwupt(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *)awg;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);
	u32 status;

	status = weadw(pwiv->mmio + HIBMC_WAW_INTEWWUPT);

	if (status & HIBMC_WAW_INTEWWUPT_VBWANK(1)) {
		wwitew(HIBMC_WAW_INTEWWUPT_VBWANK(1),
		       pwiv->mmio + HIBMC_WAW_INTEWWUPT);
		dwm_handwe_vbwank(dev, 0);
	}

	wetuwn IWQ_HANDWED;
}

static int hibmc_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			     stwuct dwm_mode_cweate_dumb *awgs)
{
	wetuwn dwm_gem_vwam_fiww_cweate_dumb(fiwe, dev, 0, 128, awgs);
}

static const stwuct dwm_dwivew hibmc_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &hibmc_fops,
	.name			= "hibmc",
	.date			= "20160828",
	.desc			= "hibmc dwm dwivew",
	.majow			= 1,
	.minow			= 0,
	.debugfs_init		= dwm_vwam_mm_debugfs_init,
	.dumb_cweate            = hibmc_dumb_cweate,
	.dumb_map_offset        = dwm_gem_ttm_dumb_map_offset,
};

static int __maybe_unused hibmc_pm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm_dev);
}

static int  __maybe_unused hibmc_pm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm_dev);
}

static const stwuct dev_pm_ops hibmc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(hibmc_pm_suspend,
				hibmc_pm_wesume)
};

static const stwuct dwm_mode_config_funcs hibmc_mode_funcs = {
	.mode_vawid = dwm_vwam_hewpew_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
	.fb_cweate = dwm_gem_fb_cweate,
};

static int hibmc_kms_init(stwuct hibmc_dwm_pwivate *pwiv)
{
	stwuct dwm_device *dev = &pwiv->dev;
	int wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 1920;
	dev->mode_config.max_height = 1200;

	dev->mode_config.pwefewwed_depth = 24;
	dev->mode_config.pwefew_shadow = 1;

	dev->mode_config.funcs = (void *)&hibmc_mode_funcs;

	wet = hibmc_de_init(pwiv);
	if (wet) {
		dwm_eww(dev, "faiwed to init de: %d\n", wet);
		wetuwn wet;
	}

	wet = hibmc_vdac_init(pwiv);
	if (wet) {
		dwm_eww(dev, "faiwed to init vdac: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * It can opewate in one of thwee modes: 0, 1 ow Sweep.
 */
void hibmc_set_powew_mode(stwuct hibmc_dwm_pwivate *pwiv, u32 powew_mode)
{
	u32 contwow_vawue = 0;
	void __iomem   *mmio = pwiv->mmio;
	u32 input = 1;

	if (powew_mode > HIBMC_PW_MODE_CTW_MODE_SWEEP)
		wetuwn;

	if (powew_mode == HIBMC_PW_MODE_CTW_MODE_SWEEP)
		input = 0;

	contwow_vawue = weadw(mmio + HIBMC_POWEW_MODE_CTWW);
	contwow_vawue &= ~(HIBMC_PW_MODE_CTW_MODE_MASK |
			   HIBMC_PW_MODE_CTW_OSC_INPUT_MASK);
	contwow_vawue |= HIBMC_FIEWD(HIBMC_PW_MODE_CTW_MODE, powew_mode);
	contwow_vawue |= HIBMC_FIEWD(HIBMC_PW_MODE_CTW_OSC_INPUT, input);
	wwitew(contwow_vawue, mmio + HIBMC_POWEW_MODE_CTWW);
}

void hibmc_set_cuwwent_gate(stwuct hibmc_dwm_pwivate *pwiv, unsigned int gate)
{
	u32 gate_weg;
	u32 mode;
	void __iomem   *mmio = pwiv->mmio;

	/* Get cuwwent powew mode. */
	mode = (weadw(mmio + HIBMC_POWEW_MODE_CTWW) &
		HIBMC_PW_MODE_CTW_MODE_MASK) >> HIBMC_PW_MODE_CTW_MODE_SHIFT;

	switch (mode) {
	case HIBMC_PW_MODE_CTW_MODE_MODE0:
		gate_weg = HIBMC_MODE0_GATE;
		bweak;

	case HIBMC_PW_MODE_CTW_MODE_MODE1:
		gate_weg = HIBMC_MODE1_GATE;
		bweak;

	defauwt:
		gate_weg = HIBMC_MODE0_GATE;
		bweak;
	}
	wwitew(gate, mmio + gate_weg);
}

static void hibmc_hw_config(stwuct hibmc_dwm_pwivate *pwiv)
{
	u32 weg;

	/* On hawdwawe weset, powew mode 0 is defauwt. */
	hibmc_set_powew_mode(pwiv, HIBMC_PW_MODE_CTW_MODE_MODE0);

	/* Enabwe dispway powew gate & WOCAWMEM powew gate*/
	weg = weadw(pwiv->mmio + HIBMC_CUWWENT_GATE);
	weg &= ~HIBMC_CUWW_GATE_DISPWAY_MASK;
	weg &= ~HIBMC_CUWW_GATE_WOCAWMEM_MASK;
	weg |= HIBMC_CUWW_GATE_DISPWAY(1);
	weg |= HIBMC_CUWW_GATE_WOCAWMEM(1);

	hibmc_set_cuwwent_gate(pwiv, weg);

	/*
	 * Weset the memowy contwowwew. If the memowy contwowwew
	 * is not weset in chip,the system might hang when sw accesses
	 * the memowy.The memowy shouwd be wesetted aftew
	 * changing the MXCWK.
	 */
	weg = weadw(pwiv->mmio + HIBMC_MISC_CTWW);
	weg &= ~HIBMC_MSCCTW_WOCAWMEM_WESET_MASK;
	weg |= HIBMC_MSCCTW_WOCAWMEM_WESET(0);
	wwitew(weg, pwiv->mmio + HIBMC_MISC_CTWW);

	weg &= ~HIBMC_MSCCTW_WOCAWMEM_WESET_MASK;
	weg |= HIBMC_MSCCTW_WOCAWMEM_WESET(1);

	wwitew(weg, pwiv->mmio + HIBMC_MISC_CTWW);
}

static int hibmc_hw_map(stwuct hibmc_dwm_pwivate *pwiv)
{
	stwuct dwm_device *dev = &pwiv->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	wesouwce_size_t ioaddw, iosize;

	ioaddw = pci_wesouwce_stawt(pdev, 1);
	iosize = pci_wesouwce_wen(pdev, 1);
	pwiv->mmio = devm_iowemap(dev->dev, ioaddw, iosize);
	if (!pwiv->mmio) {
		dwm_eww(dev, "Cannot map mmio wegion\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int hibmc_hw_init(stwuct hibmc_dwm_pwivate *pwiv)
{
	int wet;

	wet = hibmc_hw_map(pwiv);
	if (wet)
		wetuwn wet;

	hibmc_hw_config(pwiv);

	wetuwn 0;
}

static int hibmc_unwoad(stwuct dwm_device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	dwm_atomic_hewpew_shutdown(dev);

	fwee_iwq(pdev->iwq, dev);

	pci_disabwe_msi(to_pci_dev(dev->dev));

	wetuwn 0;
}

static int hibmc_woad(stwuct dwm_device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(dev);
	int wet;

	wet = hibmc_hw_init(pwiv);
	if (wet)
		goto eww;

	wet = dwmm_vwam_hewpew_init(dev, pci_wesouwce_stawt(pdev, 0),
				    pci_wesouwce_wen(pdev, 0));
	if (wet) {
		dwm_eww(dev, "Ewwow initiawizing VWAM MM; %d\n", wet);
		goto eww;
	}

	wet = hibmc_kms_init(pwiv);
	if (wet)
		goto eww;

	wet = dwm_vbwank_init(dev, dev->mode_config.num_cwtc);
	if (wet) {
		dwm_eww(dev, "faiwed to initiawize vbwank: %d\n", wet);
		goto eww;
	}

	wet = pci_enabwe_msi(pdev);
	if (wet) {
		dwm_wawn(dev, "enabwing MSI faiwed: %d\n", wet);
	} ewse {
		/* PCI devices wequiwe shawed intewwupts. */
		wet = wequest_iwq(pdev->iwq, hibmc_intewwupt, IWQF_SHAWED,
				  dev->dwivew->name, dev);
		if (wet)
			dwm_wawn(dev, "instaww iwq faiwed: %d\n", wet);
	}

	/* weset aww the states of cwtc/pwane/encodew/connectow */
	dwm_mode_config_weset(dev);

	wetuwn 0;

eww:
	hibmc_unwoad(dev);
	dwm_eww(dev, "faiwed to initiawize dwm dwivew: %d\n", wet);
	wetuwn wet;
}

static int hibmc_pci_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct hibmc_dwm_pwivate *pwiv;
	stwuct dwm_device *dev;
	int wet;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &hibmc_dwivew);
	if (wet)
		wetuwn wet;

	pwiv = devm_dwm_dev_awwoc(&pdev->dev, &hibmc_dwivew,
				  stwuct hibmc_dwm_pwivate, dev);
	if (IS_EWW(pwiv)) {
		DWM_EWWOW("faiwed to awwocate dwm_device\n");
		wetuwn PTW_EWW(pwiv);
	}

	dev = &pwiv->dev;
	pci_set_dwvdata(pdev, dev);

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dwm_eww(dev, "faiwed to enabwe pci device: %d\n", wet);
		goto eww_wetuwn;
	}

	wet = hibmc_woad(dev);
	if (wet) {
		dwm_eww(dev, "faiwed to woad hibmc: %d\n", wet);
		goto eww_wetuwn;
	}

	wet = dwm_dev_wegistew(dev, 0);
	if (wet) {
		dwm_eww(dev, "faiwed to wegistew dwv fow usewspace access: %d\n",
			  wet);
		goto eww_unwoad;
	}

	dwm_fbdev_genewic_setup(dev, 32);

	wetuwn 0;

eww_unwoad:
	hibmc_unwoad(dev);
eww_wetuwn:
	wetuwn wet;
}

static void hibmc_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(dev);
	hibmc_unwoad(dev);
}

static void hibmc_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static const stwuct pci_device_id hibmc_pci_tabwe[] = {
	{ PCI_VDEVICE(HUAWEI, 0x1711) },
	{0,}
};

static stwuct pci_dwivew hibmc_pci_dwivew = {
	.name =		"hibmc-dwm",
	.id_tabwe =	hibmc_pci_tabwe,
	.pwobe =	hibmc_pci_pwobe,
	.wemove =	hibmc_pci_wemove,
	.shutdown =	hibmc_pci_shutdown,
	.dwivew.pm =    &hibmc_pm_ops,
};

dwm_moduwe_pci_dwivew(hibmc_pci_dwivew);

MODUWE_DEVICE_TABWE(pci, hibmc_pci_tabwe);
MODUWE_AUTHOW("WongwongZou <zouwongwong@huawei.com>");
MODUWE_DESCWIPTION("DWM Dwivew fow Hisiwicon Hibmc");
MODUWE_WICENSE("GPW v2");
