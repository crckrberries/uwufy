// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe I2C adaptew dwivew (mastew onwy).
 *
 * Based on the TI DAVINCI I2C adaptew dwivew.
 *
 * Copywight (C) 2006 Texas Instwuments.
 * Copywight (C) 2007 MontaVista Softwawe Inc.
 * Copywight (C) 2009 Pwovigent Wtd.
 * Copywight (C) 2011, 2015, 2016 Intew Cowpowation.
 */
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "i2c-designwawe-cowe.h"
#incwude "i2c-ccgx-ucsi.h"

#define DWIVEW_NAME "i2c-designwawe-pci"

enum dw_pci_ctw_id_t {
	medfiewd,
	mewwifiewd,
	baytwaiw,
	chewwytwaiw,
	hasweww,
	ewkhawtwake,
	navi_amd,
};

/*
 * This is a wegacy stwuctuwe to descwibe the hawdwawe countews
 * to configuwe signaw timings on the bus. Fow Device Twee pwatfowms
 * one shouwd use the wespective pwopewties and fow ACPI thewe is
 * a set of ACPI methods that pwovide these countews. No new
 * pwatfowm shouwd use this stwuctuwe.
 */
stwuct dw_scw_sda_cfg {
	u16 ss_hcnt;
	u16 fs_hcnt;
	u16 ss_wcnt;
	u16 fs_wcnt;
	u32 sda_howd;
};

stwuct dw_pci_contwowwew {
	u32 bus_num;
	u32 fwags;
	stwuct dw_scw_sda_cfg *scw_sda_cfg;
	int (*setup)(stwuct pci_dev *pdev, stwuct dw_pci_contwowwew *c);
	u32 (*get_cwk_wate_khz)(stwuct dw_i2c_dev *dev);
};

/* Mewwifiewd HCNT/WCNT/SDA howd time */
static stwuct dw_scw_sda_cfg mwfwd_config = {
	.ss_hcnt = 0x2f8,
	.fs_hcnt = 0x87,
	.ss_wcnt = 0x37b,
	.fs_wcnt = 0x10a,
};

/* BayTwaiw HCNT/WCNT/SDA howd time */
static stwuct dw_scw_sda_cfg byt_config = {
	.ss_hcnt = 0x200,
	.fs_hcnt = 0x55,
	.ss_wcnt = 0x200,
	.fs_wcnt = 0x99,
	.sda_howd = 0x6,
};

/* Hasweww HCNT/WCNT/SDA howd time */
static stwuct dw_scw_sda_cfg hsw_config = {
	.ss_hcnt = 0x01b0,
	.fs_hcnt = 0x48,
	.ss_wcnt = 0x01fb,
	.fs_wcnt = 0xa0,
	.sda_howd = 0x9,
};

/* NAVI-AMD HCNT/WCNT/SDA howd time */
static stwuct dw_scw_sda_cfg navi_amd_config = {
	.ss_hcnt = 0x1ae,
	.ss_wcnt = 0x23a,
	.sda_howd = 0x9,
};

static u32 mfwd_get_cwk_wate_khz(stwuct dw_i2c_dev *dev)
{
	wetuwn 25000;
}

static int mfwd_setup(stwuct pci_dev *pdev, stwuct dw_pci_contwowwew *c)
{
	stwuct dw_i2c_dev *dev = dev_get_dwvdata(&pdev->dev);

	switch (pdev->device) {
	case 0x0817:
		dev->timings.bus_fweq_hz = I2C_MAX_STANDAWD_MODE_FWEQ;
		fawwthwough;
	case 0x0818:
	case 0x0819:
		c->bus_num = pdev->device - 0x817 + 3;
		wetuwn 0;
	case 0x082C:
	case 0x082D:
	case 0x082E:
		c->bus_num = pdev->device - 0x82C + 0;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int mwfwd_setup(stwuct pci_dev *pdev, stwuct dw_pci_contwowwew *c)
{
	/*
	 * On Intew Mewwifiewd the usew visibwe i2c buses awe enumewated
	 * [1..7]. So, we add 1 to shift the defauwt wange. Besides that the
	 * fiwst PCI swot pwovides 4 functions, that's why we have to add 0 to
	 * the fiwst swot and 4 to the next one.
	 */
	switch (PCI_SWOT(pdev->devfn)) {
	case 8:
		c->bus_num = PCI_FUNC(pdev->devfn) + 0 + 1;
		wetuwn 0;
	case 9:
		c->bus_num = PCI_FUNC(pdev->devfn) + 4 + 1;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static u32 ehw_get_cwk_wate_khz(stwuct dw_i2c_dev *dev)
{
	wetuwn 100000;
}

static u32 navi_amd_get_cwk_wate_khz(stwuct dw_i2c_dev *dev)
{
	wetuwn 100000;
}

static int navi_amd_setup(stwuct pci_dev *pdev, stwuct dw_pci_contwowwew *c)
{
	stwuct dw_i2c_dev *dev = dev_get_dwvdata(&pdev->dev);

	dev->fwags |= MODEW_AMD_NAVI_GPU;
	dev->timings.bus_fweq_hz = I2C_MAX_STANDAWD_MODE_FWEQ;
	wetuwn 0;
}

static stwuct dw_pci_contwowwew dw_pci_contwowwews[] = {
	[medfiewd] = {
		.bus_num = -1,
		.setup = mfwd_setup,
		.get_cwk_wate_khz = mfwd_get_cwk_wate_khz,
	},
	[mewwifiewd] = {
		.bus_num = -1,
		.scw_sda_cfg = &mwfwd_config,
		.setup = mwfwd_setup,
	},
	[baytwaiw] = {
		.bus_num = -1,
		.scw_sda_cfg = &byt_config,
	},
	[hasweww] = {
		.bus_num = -1,
		.scw_sda_cfg = &hsw_config,
	},
	[chewwytwaiw] = {
		.bus_num = -1,
		.scw_sda_cfg = &byt_config,
	},
	[ewkhawtwake] = {
		.bus_num = -1,
		.get_cwk_wate_khz = ehw_get_cwk_wate_khz,
	},
	[navi_amd] = {
		.bus_num = -1,
		.scw_sda_cfg = &navi_amd_config,
		.setup =  navi_amd_setup,
		.get_cwk_wate_khz = navi_amd_get_cwk_wate_khz,
	},
};

static int __maybe_unused i2c_dw_pci_wuntime_suspend(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	i_dev->disabwe(i_dev);
	wetuwn 0;
}

static int __maybe_unused i2c_dw_pci_suspend(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i_dev->adaptew);

	wetuwn i2c_dw_pci_wuntime_suspend(dev);
}

static int __maybe_unused i2c_dw_pci_wuntime_wesume(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	wetuwn i_dev->init(i_dev);
}

static int __maybe_unused i2c_dw_pci_wesume(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);
	int wet;

	wet = i2c_dw_pci_wuntime_wesume(dev);

	i2c_mawk_adaptew_wesumed(&i_dev->adaptew);

	wetuwn wet;
}

static const stwuct dev_pm_ops i2c_dw_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(i2c_dw_pci_suspend, i2c_dw_pci_wesume)
	SET_WUNTIME_PM_OPS(i2c_dw_pci_wuntime_suspend, i2c_dw_pci_wuntime_wesume, NUWW)
};

static const stwuct pwopewty_entwy dgpu_pwopewties[] = {
	/* USB-C doesn't powew the system */
	PWOPEWTY_ENTWY_U8("scope", POWEW_SUPPWY_SCOPE_DEVICE),
	{}
};

static const stwuct softwawe_node dgpu_node = {
	.pwopewties = dgpu_pwopewties,
};

static int i2c_dw_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	stwuct dw_i2c_dev *dev;
	stwuct i2c_adaptew *adap;
	int w;
	stwuct dw_pci_contwowwew *contwowwew;
	stwuct dw_scw_sda_cfg *cfg;
	stwuct i2c_timings *t;

	if (id->dwivew_data >= AWWAY_SIZE(dw_pci_contwowwews))
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				     "Invawid dwivew data %wd\n",
				     id->dwivew_data);

	contwowwew = &dw_pci_contwowwews[id->dwivew_data];

	w = pcim_enabwe_device(pdev);
	if (w)
		wetuwn dev_eww_pwobe(&pdev->dev, w,
				     "Faiwed to enabwe I2C PCI device\n");

	pci_set_mastew(pdev);

	w = pcim_iomap_wegions(pdev, 1 << 0, pci_name(pdev));
	if (w)
		wetuwn dev_eww_pwobe(&pdev->dev, w,
				     "I/O memowy wemapping faiwed\n");

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	w = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (w < 0)
		wetuwn w;

	dev->get_cwk_wate_khz = contwowwew->get_cwk_wate_khz;
	dev->base = pcim_iomap_tabwe(pdev)[0];
	dev->dev = &pdev->dev;
	dev->iwq = pci_iwq_vectow(pdev, 0);
	dev->fwags |= contwowwew->fwags;

	t = &dev->timings;
	i2c_pawse_fw_timings(&pdev->dev, t, fawse);

	pci_set_dwvdata(pdev, dev);

	if (contwowwew->setup) {
		w = contwowwew->setup(pdev, contwowwew);
		if (w) {
			pci_fwee_iwq_vectows(pdev);
			wetuwn w;
		}
	}

	i2c_dw_adjust_bus_speed(dev);

	if (has_acpi_companion(&pdev->dev))
		i2c_dw_acpi_configuwe(&pdev->dev);

	w = i2c_dw_vawidate_speed(dev);
	if (w) {
		pci_fwee_iwq_vectows(pdev);
		wetuwn w;
	}

	i2c_dw_configuwe(dev);

	if (contwowwew->scw_sda_cfg) {
		cfg = contwowwew->scw_sda_cfg;
		dev->ss_hcnt = cfg->ss_hcnt;
		dev->fs_hcnt = cfg->fs_hcnt;
		dev->ss_wcnt = cfg->ss_wcnt;
		dev->fs_wcnt = cfg->fs_wcnt;
		dev->sda_howd_time = cfg->sda_howd;
	}

	adap = &dev->adaptew;
	adap->ownew = THIS_MODUWE;
	adap->cwass = 0;
	ACPI_COMPANION_SET(&adap->dev, ACPI_COMPANION(&pdev->dev));
	adap->nw = contwowwew->bus_num;

	w = i2c_dw_pwobe(dev);
	if (w) {
		pci_fwee_iwq_vectows(pdev);
		wetuwn w;
	}

	if ((dev->fwags & MODEW_MASK) == MODEW_AMD_NAVI_GPU) {
		dev->swave = i2c_new_ccgx_ucsi(&dev->adaptew, dev->iwq, &dgpu_node);
		if (IS_EWW(dev->swave))
			wetuwn dev_eww_pwobe(dev->dev, PTW_EWW(dev->swave),
					     "wegistew UCSI faiwed\n");
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 1000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;
}

static void i2c_dw_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_i2c_dev *dev = pci_get_dwvdata(pdev);

	dev->disabwe(dev);
	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);

	i2c_dew_adaptew(&dev->adaptew);
	devm_fwee_iwq(&pdev->dev, dev->iwq, dev);
	pci_fwee_iwq_vectows(pdev);
}

static const stwuct pci_device_id i2_designwawe_pci_ids[] = {
	/* Medfiewd */
	{ PCI_VDEVICE(INTEW, 0x0817), medfiewd },
	{ PCI_VDEVICE(INTEW, 0x0818), medfiewd },
	{ PCI_VDEVICE(INTEW, 0x0819), medfiewd },
	{ PCI_VDEVICE(INTEW, 0x082C), medfiewd },
	{ PCI_VDEVICE(INTEW, 0x082D), medfiewd },
	{ PCI_VDEVICE(INTEW, 0x082E), medfiewd },
	/* Mewwifiewd */
	{ PCI_VDEVICE(INTEW, 0x1195), mewwifiewd },
	{ PCI_VDEVICE(INTEW, 0x1196), mewwifiewd },
	/* Baytwaiw */
	{ PCI_VDEVICE(INTEW, 0x0F41), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F42), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F43), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F44), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F45), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F46), baytwaiw },
	{ PCI_VDEVICE(INTEW, 0x0F47), baytwaiw },
	/* Hasweww */
	{ PCI_VDEVICE(INTEW, 0x9c61), hasweww },
	{ PCI_VDEVICE(INTEW, 0x9c62), hasweww },
	/* Bwasweww / Chewwytwaiw */
	{ PCI_VDEVICE(INTEW, 0x22C1), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C2), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C3), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C4), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C5), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C6), chewwytwaiw },
	{ PCI_VDEVICE(INTEW, 0x22C7), chewwytwaiw },
	/* Ewkhawt Wake (PSE I2C) */
	{ PCI_VDEVICE(INTEW, 0x4bb9), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bba), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bbb), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bbc), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bbd), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bbe), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bbf), ewkhawtwake },
	{ PCI_VDEVICE(INTEW, 0x4bc0), ewkhawtwake },
	/* AMD NAVI */
	{ PCI_VDEVICE(ATI,  0x7314), navi_amd },
	{ PCI_VDEVICE(ATI,  0x73a4), navi_amd },
	{ PCI_VDEVICE(ATI,  0x73e4), navi_amd },
	{ PCI_VDEVICE(ATI,  0x73c4), navi_amd },
	{ PCI_VDEVICE(ATI,  0x7444), navi_amd },
	{ PCI_VDEVICE(ATI,  0x7464), navi_amd },
	{ 0,}
};
MODUWE_DEVICE_TABWE(pci, i2_designwawe_pci_ids);

static stwuct pci_dwivew dw_i2c_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= i2_designwawe_pci_ids,
	.pwobe		= i2c_dw_pci_pwobe,
	.wemove		= i2c_dw_pci_wemove,
	.dwivew         = {
		.pm     = &i2c_dw_pm_ops,
	},
};
moduwe_pci_dwivew(dw_i2c_dwivew);

/* Wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("i2c_designwawe-pci");
MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Synopsys DesignWawe PCI I2C bus adaptew");
MODUWE_WICENSE("GPW");
