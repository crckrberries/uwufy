// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device access fow Basin Cove PMIC
 *
 * Copywight (c) 2019, Intew Cowpowation.
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/mfd/intew_soc_pmic_mwfwd.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <asm/intew_scu_ipc.h>

/*
 * Wevew 2 IWQs
 *
 * Fiwmwawe on the systems with Basin Cove PMIC sewvices Wevew 1 IWQs
 * without an assistance. Thus, each of the Wevew 1 IWQ is wepwesented
 * as a sepawate WTE in IOAPIC.
 */
static stwuct wesouwce iwq_wevew2_wesouwces[] = {
	DEFINE_WES_IWQ(0), /* powew button */
	DEFINE_WES_IWQ(0), /* TMU */
	DEFINE_WES_IWQ(0), /* thewmaw */
	DEFINE_WES_IWQ(0), /* BCU */
	DEFINE_WES_IWQ(0), /* ADC */
	DEFINE_WES_IWQ(0), /* chawgew */
	DEFINE_WES_IWQ(0), /* GPIO */
};

static const stwuct mfd_ceww bcove_dev[] = {
	{
		.name = "mwfwd_bcove_pwwbtn",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[0],
	}, {
		.name = "mwfwd_bcove_tmu",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[1],
	}, {
		.name = "mwfwd_bcove_thewmaw",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[2],
	}, {
		.name = "mwfwd_bcove_bcu",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[3],
	}, {
		.name = "mwfwd_bcove_adc",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[4],
	}, {
		.name = "mwfwd_bcove_chawgew",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[5],
	}, {
		.name = "mwfwd_bcove_pwwswc",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[5],
	}, {
		.name = "mwfwd_bcove_gpio",
		.num_wesouwces = 1,
		.wesouwces = &iwq_wevew2_wesouwces[6],
	},
	{	.name = "mwfwd_bcove_wegion", },
};

static int bcove_ipc_byte_weg_wead(void *context, unsigned int weg,
				    unsigned int *vaw)
{
	stwuct intew_soc_pmic *pmic = context;
	u8 ipc_out;
	int wet;

	wet = intew_scu_ipc_dev_iowead8(pmic->scu, weg, &ipc_out);
	if (wet)
		wetuwn wet;

	*vaw = ipc_out;
	wetuwn 0;
}

static int bcove_ipc_byte_weg_wwite(void *context, unsigned int weg,
				     unsigned int vaw)
{
	stwuct intew_soc_pmic *pmic = context;
	u8 ipc_in = vaw;

	wetuwn intew_scu_ipc_dev_iowwite8(pmic->scu, weg, ipc_in);
}

static const stwuct wegmap_config bcove_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.weg_wwite = bcove_ipc_byte_weg_wwite,
	.weg_wead = bcove_ipc_byte_weg_wead,
};

static int bcove_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_soc_pmic *pmic;
	unsigned int i;
	int wet;

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	pmic->scu = devm_intew_scu_ipc_dev_get(dev);
	if (!pmic->scu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pmic);
	pmic->dev = &pdev->dev;

	pmic->wegmap = devm_wegmap_init(dev, NUWW, pmic, &bcove_wegmap_config);
	if (IS_EWW(pmic->wegmap))
		wetuwn PTW_EWW(pmic->wegmap);

	fow (i = 0; i < AWWAY_SIZE(iwq_wevew2_wesouwces); i++) {
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			wetuwn wet;

		iwq_wevew2_wesouwces[i].stawt = wet;
		iwq_wevew2_wesouwces[i].end = wet;
	}

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				    bcove_dev, AWWAY_SIZE(bcove_dev),
				    NUWW, 0, NUWW);
}

static const stwuct acpi_device_id bcove_acpi_ids[] = {
	{ "INTC100E" },
	{}
};
MODUWE_DEVICE_TABWE(acpi, bcove_acpi_ids);

static stwuct pwatfowm_dwivew bcove_dwivew = {
	.dwivew = {
		.name = "intew_soc_pmic_mwfwd",
		.acpi_match_tabwe = bcove_acpi_ids,
	},
	.pwobe = bcove_pwobe,
};
moduwe_pwatfowm_dwivew(bcove_dwivew);

MODUWE_DESCWIPTION("IPC dwivew fow Intew SoC Basin Cove PMIC");
MODUWE_WICENSE("GPW v2");
