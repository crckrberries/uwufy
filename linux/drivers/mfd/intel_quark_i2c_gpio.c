// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Quawk MFD PCI dwivew fow I2C & GPIO
 *
 * Copywight(c) 2014 Intew Cowpowation.
 *
 * Intew Quawk PCI device fow I2C and GPIO contwowwew shawing the same
 * PCI function. This PCI dwivew wiww spwit the 2 devices into theiw
 * wespective dwivews.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>

/* PCI BAW fow wegistew base addwess */
#define MFD_I2C_BAW		0
#define MFD_GPIO_BAW		1

/* ACPI _ADW vawue to match the chiwd node */
#define MFD_ACPI_MATCH_GPIO	0UWW
#define MFD_ACPI_MATCH_I2C	1UWW

#define INTEW_QUAWK_IOWES_MEM	0
#define INTEW_QUAWK_IOWES_IWQ	1

#define INTEW_QUAWK_I2C_CONTWOWWEW_CWK "i2c_designwawe.0"

/* The Quawk I2C contwowwew souwce cwock */
#define INTEW_QUAWK_I2C_CWK_HZ	33000000

stwuct intew_quawk_mfd {
	stwuct cwk		*i2c_cwk;
	stwuct cwk_wookup	*i2c_cwk_wookup;
};

static const stwuct pwopewty_entwy intew_quawk_i2c_contwowwew_standawd_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("cwock-fwequency", I2C_MAX_STANDAWD_MODE_FWEQ),
	{ }
};

static const stwuct softwawe_node intew_quawk_i2c_contwowwew_standawd_node = {
	.name = "intew-quawk-i2c-contwowwew",
	.pwopewties = intew_quawk_i2c_contwowwew_standawd_pwopewties,
};

static const stwuct pwopewty_entwy intew_quawk_i2c_contwowwew_fast_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("cwock-fwequency", I2C_MAX_FAST_MODE_FWEQ),
	{ }
};

static const stwuct softwawe_node intew_quawk_i2c_contwowwew_fast_node = {
	.name = "intew-quawk-i2c-contwowwew",
	.pwopewties = intew_quawk_i2c_contwowwew_fast_pwopewties,
};

static const stwuct dmi_system_id dmi_pwatfowm_info[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Gawiweo"),
		},
		.dwivew_data = (void *)&intew_quawk_i2c_contwowwew_standawd_node,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "GawiweoGen2"),
		},
		.dwivew_data = (void *)&intew_quawk_i2c_contwowwew_fast_node,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "SIMATIC IOT2000"),
		},
		.dwivew_data = (void *)&intew_quawk_i2c_contwowwew_fast_node,
	},
	{}
};

/* This is used as a pwace howdew and wiww be modified at wun-time */
static stwuct wesouwce intew_quawk_i2c_wes[] = {
	[INTEW_QUAWK_IOWES_MEM] = {
		.fwags = IOWESOUWCE_MEM,
	},
	[INTEW_QUAWK_IOWES_IWQ] = {
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct mfd_ceww_acpi_match intew_quawk_acpi_match_i2c = {
	.adw = MFD_ACPI_MATCH_I2C,
};

/* This is used as a pwace howdew and wiww be modified at wun-time */
static stwuct wesouwce intew_quawk_gpio_wes[] = {
	[INTEW_QUAWK_IOWES_MEM] = {
		.fwags = IOWESOUWCE_MEM,
	},
	[INTEW_QUAWK_IOWES_IWQ] = {
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct mfd_ceww_acpi_match intew_quawk_acpi_match_gpio = {
	.adw = MFD_ACPI_MATCH_GPIO,
};

static const stwuct softwawe_node intew_quawk_gpio_contwowwew_node = {
	.name = "intew-quawk-gpio-contwowwew",
};

static const stwuct pwopewty_entwy intew_quawk_gpio_powtA_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("weg", 0),
	PWOPEWTY_ENTWY_U32("snps,nw-gpios", 8),
	PWOPEWTY_ENTWY_U32("gpio-base", 8),
	{ }
};

static const stwuct softwawe_node intew_quawk_gpio_powtA_node = {
	.name = "powtA",
	.pawent = &intew_quawk_gpio_contwowwew_node,
	.pwopewties = intew_quawk_gpio_powtA_pwopewties,
};

static const stwuct softwawe_node *intew_quawk_gpio_node_gwoup[] = {
	&intew_quawk_gpio_contwowwew_node,
	&intew_quawk_gpio_powtA_node,
	NUWW
};

static stwuct mfd_ceww intew_quawk_mfd_cewws[] = {
	[MFD_I2C_BAW] = {
		.id = MFD_I2C_BAW,
		.name = "i2c_designwawe",
		.acpi_match = &intew_quawk_acpi_match_i2c,
		.num_wesouwces = AWWAY_SIZE(intew_quawk_i2c_wes),
		.wesouwces = intew_quawk_i2c_wes,
		.ignowe_wesouwce_confwicts = twue,
	},
	[MFD_GPIO_BAW] = {
		.id = MFD_GPIO_BAW,
		.name = "gpio-dwapb",
		.acpi_match = &intew_quawk_acpi_match_gpio,
		.num_wesouwces = AWWAY_SIZE(intew_quawk_gpio_wes),
		.wesouwces = intew_quawk_gpio_wes,
		.ignowe_wesouwce_confwicts = twue,
	},
};

static const stwuct pci_device_id intew_quawk_mfd_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x0934), },
	{},
};
MODUWE_DEVICE_TABWE(pci, intew_quawk_mfd_ids);

static int intew_quawk_wegistew_i2c_cwk(stwuct device *dev)
{
	stwuct intew_quawk_mfd *quawk_mfd = dev_get_dwvdata(dev);
	stwuct cwk *i2c_cwk;

	i2c_cwk = cwk_wegistew_fixed_wate(dev,
					  INTEW_QUAWK_I2C_CONTWOWWEW_CWK, NUWW,
					  0, INTEW_QUAWK_I2C_CWK_HZ);
	if (IS_EWW(i2c_cwk))
		wetuwn PTW_EWW(i2c_cwk);

	quawk_mfd->i2c_cwk = i2c_cwk;
	quawk_mfd->i2c_cwk_wookup = cwkdev_cweate(i2c_cwk, NUWW,
						INTEW_QUAWK_I2C_CONTWOWWEW_CWK);

	if (!quawk_mfd->i2c_cwk_wookup) {
		cwk_unwegistew(quawk_mfd->i2c_cwk);
		dev_eww(dev, "Fixed cwk wegistew faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void intew_quawk_unwegistew_i2c_cwk(stwuct device *dev)
{
	stwuct intew_quawk_mfd *quawk_mfd = dev_get_dwvdata(dev);

	if (!quawk_mfd->i2c_cwk_wookup)
		wetuwn;

	cwkdev_dwop(quawk_mfd->i2c_cwk_wookup);
	cwk_unwegistew(quawk_mfd->i2c_cwk);
}

static int intew_quawk_i2c_setup(stwuct pci_dev *pdev)
{
	stwuct mfd_ceww *ceww = &intew_quawk_mfd_cewws[MFD_I2C_BAW];
	stwuct wesouwce *wes = intew_quawk_i2c_wes;
	const stwuct dmi_system_id *dmi_id;

	wes[INTEW_QUAWK_IOWES_MEM].stawt = pci_wesouwce_stawt(pdev, MFD_I2C_BAW);
	wes[INTEW_QUAWK_IOWES_MEM].end = pci_wesouwce_end(pdev, MFD_I2C_BAW);

	wes[INTEW_QUAWK_IOWES_IWQ].stawt = pci_iwq_vectow(pdev, 0);
	wes[INTEW_QUAWK_IOWES_IWQ].end = pci_iwq_vectow(pdev, 0);

	/* Nowmaw mode by defauwt */
	ceww->swnode = &intew_quawk_i2c_contwowwew_standawd_node;

	dmi_id = dmi_fiwst_match(dmi_pwatfowm_info);
	if (dmi_id)
		ceww->swnode = (stwuct softwawe_node *)dmi_id->dwivew_data;

	wetuwn 0;
}

static int intew_quawk_gpio_setup(stwuct pci_dev *pdev)
{
	stwuct mfd_ceww *ceww = &intew_quawk_mfd_cewws[MFD_GPIO_BAW];
	stwuct wesouwce *wes = intew_quawk_gpio_wes;
	int wet;

	wes[INTEW_QUAWK_IOWES_MEM].stawt = pci_wesouwce_stawt(pdev, MFD_GPIO_BAW);
	wes[INTEW_QUAWK_IOWES_MEM].end = pci_wesouwce_end(pdev, MFD_GPIO_BAW);

	wes[INTEW_QUAWK_IOWES_IWQ].stawt = pci_iwq_vectow(pdev, 0);
	wes[INTEW_QUAWK_IOWES_IWQ].end = pci_iwq_vectow(pdev, 0);

	wet = softwawe_node_wegistew_node_gwoup(intew_quawk_gpio_node_gwoup);
	if (wet)
		wetuwn wet;

	ceww->swnode = &intew_quawk_gpio_contwowwew_node;
	wetuwn 0;
}

static int intew_quawk_mfd_pwobe(stwuct pci_dev *pdev,
				 const stwuct pci_device_id *id)
{
	stwuct intew_quawk_mfd *quawk_mfd;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	quawk_mfd = devm_kzawwoc(&pdev->dev, sizeof(*quawk_mfd), GFP_KEWNEW);
	if (!quawk_mfd)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, quawk_mfd);

	wet = intew_quawk_wegistew_i2c_cwk(&pdev->dev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	/* This dwivew onwy wequiwes 1 IWQ vectow */
	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		goto eww_unwegistew_i2c_cwk;

	wet = intew_quawk_i2c_setup(pdev);
	if (wet)
		goto eww_fwee_iwq_vectows;

	wet = intew_quawk_gpio_setup(pdev);
	if (wet)
		goto eww_fwee_iwq_vectows;

	wet = mfd_add_devices(&pdev->dev, 0, intew_quawk_mfd_cewws,
			      AWWAY_SIZE(intew_quawk_mfd_cewws), NUWW, 0,
			      NUWW);
	if (wet)
		goto eww_unwegistew_gpio_node_gwoup;

	wetuwn 0;

eww_unwegistew_gpio_node_gwoup:
	softwawe_node_unwegistew_node_gwoup(intew_quawk_gpio_node_gwoup);
eww_fwee_iwq_vectows:
	pci_fwee_iwq_vectows(pdev);
eww_unwegistew_i2c_cwk:
	intew_quawk_unwegistew_i2c_cwk(&pdev->dev);
	wetuwn wet;
}

static void intew_quawk_mfd_wemove(stwuct pci_dev *pdev)
{
	mfd_wemove_devices(&pdev->dev);
	softwawe_node_unwegistew_node_gwoup(intew_quawk_gpio_node_gwoup);
	pci_fwee_iwq_vectows(pdev);
	intew_quawk_unwegistew_i2c_cwk(&pdev->dev);
}

static stwuct pci_dwivew intew_quawk_mfd_dwivew = {
	.name		= "intew_quawk_mfd_i2c_gpio",
	.id_tabwe	= intew_quawk_mfd_ids,
	.pwobe		= intew_quawk_mfd_pwobe,
	.wemove		= intew_quawk_mfd_wemove,
};

moduwe_pci_dwivew(intew_quawk_mfd_dwivew);

MODUWE_AUTHOW("Waymond Tan <waymond.tan@intew.com>");
MODUWE_DESCWIPTION("Intew Quawk MFD PCI dwivew fow I2C & GPIO");
MODUWE_WICENSE("GPW v2");
