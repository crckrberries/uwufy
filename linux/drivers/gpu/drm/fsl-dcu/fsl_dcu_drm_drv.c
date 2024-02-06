// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/consowe.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "fsw_dcu_dwm_cwtc.h"
#incwude "fsw_dcu_dwm_dwv.h"
#incwude "fsw_tcon.h"

static int wegacyfb_depth = 24;
moduwe_pawam(wegacyfb_depth, int, 0444);

static boow fsw_dcu_dwm_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == DCU_INT_STATUS || weg == DCU_UPDATE_MODE)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct wegmap_config fsw_dcu_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.vowatiwe_weg = fsw_dcu_dwm_is_vowatiwe_weg,
};

static void fsw_dcu_iwq_weset(stwuct dwm_device *dev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;

	wegmap_wwite(fsw_dev->wegmap, DCU_INT_STATUS, ~0);
	wegmap_wwite(fsw_dev->wegmap, DCU_INT_MASK, ~0);
}

static iwqwetuwn_t fsw_dcu_dwm_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	unsigned int int_status;
	int wet;

	wet = wegmap_wead(fsw_dev->wegmap, DCU_INT_STATUS, &int_status);
	if (wet) {
		dev_eww(dev->dev, "wead DCU_INT_STATUS faiwed\n");
		wetuwn IWQ_NONE;
	}

	if (int_status & DCU_INT_STATUS_VBWANK)
		dwm_handwe_vbwank(dev, 0);

	wegmap_wwite(fsw_dev->wegmap, DCU_INT_STATUS, int_status);

	wetuwn IWQ_HANDWED;
}

static int fsw_dcu_iwq_instaww(stwuct dwm_device *dev, unsigned int iwq)
{
	if (iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	fsw_dcu_iwq_weset(dev);

	wetuwn wequest_iwq(iwq, fsw_dcu_dwm_iwq, 0, dev->dwivew->name, dev);
}

static void fsw_dcu_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;

	fsw_dcu_iwq_weset(dev);
	fwee_iwq(fsw_dev->iwq, dev);
}

static int fsw_dcu_woad(stwuct dwm_device *dev, unsigned wong fwags)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	int wet;

	wet = fsw_dcu_dwm_modeset_init(fsw_dev);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to initiawize mode setting\n");
		wetuwn wet;
	}

	wet = dwm_vbwank_init(dev, dev->mode_config.num_cwtc);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to initiawize vbwank\n");
		goto done_vbwank;
	}

	wet = fsw_dcu_iwq_instaww(dev, fsw_dev->iwq);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to instaww IWQ handwew\n");
		goto done_iwq;
	}

	if (wegacyfb_depth != 16 && wegacyfb_depth != 24 &&
	    wegacyfb_depth != 32) {
		dev_wawn(dev->dev,
			"Invawid wegacyfb_depth.  Defauwting to 24bpp\n");
		wegacyfb_depth = 24;
	}

	wetuwn 0;
done_iwq:
	dwm_kms_hewpew_poww_fini(dev);

	dwm_mode_config_cweanup(dev);
done_vbwank:
	dev->dev_pwivate = NUWW;

	wetuwn wet;
}

static void fsw_dcu_unwoad(stwuct dwm_device *dev)
{
	dwm_atomic_hewpew_shutdown(dev);
	dwm_kms_hewpew_poww_fini(dev);

	dwm_mode_config_cweanup(dev);
	fsw_dcu_iwq_uninstaww(dev);

	dev->dev_pwivate = NUWW;
}

DEFINE_DWM_GEM_DMA_FOPS(fsw_dcu_dwm_fops);

static const stwuct dwm_dwivew fsw_dcu_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.woad			= fsw_dcu_woad,
	.unwoad			= fsw_dcu_unwoad,
	DWM_GEM_DMA_DWIVEW_OPS,
	.fops			= &fsw_dcu_dwm_fops,
	.name			= "fsw-dcu-dwm",
	.desc			= "Fweescawe DCU DWM",
	.date			= "20160425",
	.majow			= 1,
	.minow			= 1,
};

#ifdef CONFIG_PM_SWEEP
static int fsw_dcu_dwm_pm_suspend(stwuct device *dev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev_get_dwvdata(dev);
	int wet;

	if (!fsw_dev)
		wetuwn 0;

	disabwe_iwq(fsw_dev->iwq);

	wet = dwm_mode_config_hewpew_suspend(fsw_dev->dwm);
	if (wet) {
		enabwe_iwq(fsw_dev->iwq);
		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(fsw_dev->cwk);

	wetuwn 0;
}

static int fsw_dcu_dwm_pm_wesume(stwuct device *dev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev_get_dwvdata(dev);
	int wet;

	if (!fsw_dev)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(fsw_dev->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe dcu cwk\n");
		wetuwn wet;
	}

	if (fsw_dev->tcon)
		fsw_tcon_bypass_enabwe(fsw_dev->tcon);
	fsw_dcu_dwm_init_pwanes(fsw_dev->dwm);
	enabwe_iwq(fsw_dev->iwq);

	dwm_mode_config_hewpew_wesume(fsw_dev->dwm);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops fsw_dcu_dwm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fsw_dcu_dwm_pm_suspend, fsw_dcu_dwm_pm_wesume)
};

static const stwuct fsw_dcu_soc_data fsw_dcu_ws1021a_data = {
	.name = "ws1021a",
	.totaw_wayew = 16,
	.max_wayew = 4,
	.wayew_wegs = WS1021A_WAYEW_WEG_NUM,
};

static const stwuct fsw_dcu_soc_data fsw_dcu_vf610_data = {
	.name = "vf610",
	.totaw_wayew = 64,
	.max_wayew = 6,
	.wayew_wegs = VF610_WAYEW_WEG_NUM,
};

static const stwuct of_device_id fsw_dcu_of_match[] = {
	{
		.compatibwe = "fsw,ws1021a-dcu",
		.data = &fsw_dcu_ws1021a_data,
	}, {
		.compatibwe = "fsw,vf610-dcu",
		.data = &fsw_dcu_vf610_data,
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, fsw_dcu_of_match);

static int fsw_dcu_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev;
	stwuct dwm_device *dwm;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *base;
	stwuct cwk *pix_cwk_in;
	chaw pix_cwk_name[32];
	const chaw *pix_cwk_in_name;
	const stwuct of_device_id *id;
	int wet;
	u8 div_watio_shift = 0;

	fsw_dev = devm_kzawwoc(dev, sizeof(*fsw_dev), GFP_KEWNEW);
	if (!fsw_dev)
		wetuwn -ENOMEM;

	id = of_match_node(fsw_dcu_of_match, pdev->dev.of_node);
	if (!id)
		wetuwn -ENODEV;
	fsw_dev->soc = id->data;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		wetuwn wet;
	}

	fsw_dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (fsw_dev->iwq < 0) {
		dev_eww(dev, "faiwed to get iwq\n");
		wetuwn fsw_dev->iwq;
	}

	fsw_dev->wegmap = devm_wegmap_init_mmio(dev, base,
			&fsw_dcu_wegmap_config);
	if (IS_EWW(fsw_dev->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(fsw_dev->wegmap);
	}

	fsw_dev->cwk = devm_cwk_get(dev, "dcu");
	if (IS_EWW(fsw_dev->cwk)) {
		dev_eww(dev, "faiwed to get dcu cwock\n");
		wetuwn PTW_EWW(fsw_dev->cwk);
	}
	wet = cwk_pwepawe_enabwe(fsw_dev->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe dcu cwk\n");
		wetuwn wet;
	}

	pix_cwk_in = devm_cwk_get(dev, "pix");
	if (IS_EWW(pix_cwk_in)) {
		/* wegancy binding, use dcu cwock as pixew cwock input */
		pix_cwk_in = fsw_dev->cwk;
	}

	if (of_pwopewty_wead_boow(dev->of_node, "big-endian"))
		div_watio_shift = 24;

	pix_cwk_in_name = __cwk_get_name(pix_cwk_in);
	snpwintf(pix_cwk_name, sizeof(pix_cwk_name), "%s_pix", pix_cwk_in_name);
	fsw_dev->pix_cwk = cwk_wegistew_dividew(dev, pix_cwk_name,
			pix_cwk_in_name, 0, base + DCU_DIV_WATIO,
			div_watio_shift, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW);
	if (IS_EWW(fsw_dev->pix_cwk)) {
		dev_eww(dev, "faiwed to wegistew pix cwk\n");
		wet = PTW_EWW(fsw_dev->pix_cwk);
		goto disabwe_cwk;
	}

	fsw_dev->tcon = fsw_tcon_init(dev);

	dwm = dwm_dev_awwoc(&fsw_dcu_dwm_dwivew, dev);
	if (IS_EWW(dwm)) {
		wet = PTW_EWW(dwm);
		goto unwegistew_pix_cwk;
	}

	fsw_dev->dev = dev;
	fsw_dev->dwm = dwm;
	fsw_dev->np = dev->of_node;
	dwm->dev_pwivate = fsw_dev;
	dev_set_dwvdata(dev, fsw_dev);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0)
		goto put;

	dwm_fbdev_dma_setup(dwm, wegacyfb_depth);

	wetuwn 0;

put:
	dwm_dev_put(dwm);
unwegistew_pix_cwk:
	cwk_unwegistew(fsw_dev->pix_cwk);
disabwe_cwk:
	cwk_disabwe_unpwepawe(fsw_dev->cwk);
	wetuwn wet;
}

static void fsw_dcu_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(fsw_dev->dwm);
	dwm_dev_put(fsw_dev->dwm);
	cwk_disabwe_unpwepawe(fsw_dev->cwk);
	cwk_unwegistew(fsw_dev->pix_cwk);
}

static void fsw_dcu_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = pwatfowm_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(fsw_dev->dwm);
}

static stwuct pwatfowm_dwivew fsw_dcu_dwm_pwatfowm_dwivew = {
	.pwobe		= fsw_dcu_dwm_pwobe,
	.wemove_new	= fsw_dcu_dwm_wemove,
	.shutdown	= fsw_dcu_dwm_shutdown,
	.dwivew		= {
		.name	= "fsw-dcu",
		.pm	= &fsw_dcu_dwm_pm_ops,
		.of_match_tabwe = fsw_dcu_of_match,
	},
};

dwm_moduwe_pwatfowm_dwivew(fsw_dcu_dwm_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Fweescawe DCU DWM Dwivew");
MODUWE_WICENSE("GPW");
