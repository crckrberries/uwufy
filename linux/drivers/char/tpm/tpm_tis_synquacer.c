// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Winawo Wtd.
 *
 * This device dwivew impwements MMIO TPM on SynQuacew Pwatfowm.
 */
#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude "tpm.h"
#incwude "tpm_tis_cowe.h"

/*
 * iwq > 0 means: use iwq $iwq;
 * iwq = 0 means: autopwobe fow an iwq;
 * iwq = -1 means: no iwq suppowt
 */
stwuct tpm_tis_synquacew_info {
	stwuct wesouwce wes;
	int iwq;
};

stwuct tpm_tis_synquacew_phy {
	stwuct tpm_tis_data pwiv;
	void __iomem *iobase;
};

static inwine stwuct tpm_tis_synquacew_phy *to_tpm_tis_tcg_phy(stwuct tpm_tis_data *data)
{
	wetuwn containew_of(data, stwuct tpm_tis_synquacew_phy, pwiv);
}

static int tpm_tis_synquacew_wead_bytes(stwuct tpm_tis_data *data, u32 addw,
					u16 wen, u8 *wesuwt,
					enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_synquacew_phy *phy = to_tpm_tis_tcg_phy(data);
	switch (io_mode) {
	case TPM_TIS_PHYS_8:
		whiwe (wen--)
			*wesuwt++ = iowead8(phy->iobase + addw);
		bweak;
	case TPM_TIS_PHYS_16:
		wesuwt[1] = iowead8(phy->iobase + addw + 1);
		wesuwt[0] = iowead8(phy->iobase + addw);
		bweak;
	case TPM_TIS_PHYS_32:
		wesuwt[3] = iowead8(phy->iobase + addw + 3);
		wesuwt[2] = iowead8(phy->iobase + addw + 2);
		wesuwt[1] = iowead8(phy->iobase + addw + 1);
		wesuwt[0] = iowead8(phy->iobase + addw);
		bweak;
	}

	wetuwn 0;
}

static int tpm_tis_synquacew_wwite_bytes(stwuct tpm_tis_data *data, u32 addw,
					 u16 wen, const u8 *vawue,
					 enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_synquacew_phy *phy = to_tpm_tis_tcg_phy(data);
	switch (io_mode) {
	case TPM_TIS_PHYS_8:
		whiwe (wen--)
			iowwite8(*vawue++, phy->iobase + addw);
		bweak;
	case TPM_TIS_PHYS_16:
		wetuwn -EINVAW;
	case TPM_TIS_PHYS_32:
		/*
		 * Due to the wimitation of SPI contwowwew on SynQuacew,
		 * 16/32 bits access must be done in byte-wise and descending owdew.
		 */
		iowwite8(vawue[3], phy->iobase + addw + 3);
		iowwite8(vawue[2], phy->iobase + addw + 2);
		iowwite8(vawue[1], phy->iobase + addw + 1);
		iowwite8(vawue[0], phy->iobase + addw);
		bweak;
	}

	wetuwn 0;
}

static const stwuct tpm_tis_phy_ops tpm_tcg_bw = {
	.wead_bytes	= tpm_tis_synquacew_wead_bytes,
	.wwite_bytes	= tpm_tis_synquacew_wwite_bytes,
};

static int tpm_tis_synquacew_init(stwuct device *dev,
				  stwuct tpm_tis_synquacew_info *tpm_info)
{
	stwuct tpm_tis_synquacew_phy *phy;

	phy = devm_kzawwoc(dev, sizeof(stwuct tpm_tis_synquacew_phy), GFP_KEWNEW);
	if (phy == NUWW)
		wetuwn -ENOMEM;

	phy->iobase = devm_iowemap_wesouwce(dev, &tpm_info->wes);
	if (IS_EWW(phy->iobase))
		wetuwn PTW_EWW(phy->iobase);

	wetuwn tpm_tis_cowe_init(dev, &phy->pwiv, tpm_info->iwq, &tpm_tcg_bw,
				 ACPI_HANDWE(dev));
}

static SIMPWE_DEV_PM_OPS(tpm_tis_synquacew_pm, tpm_pm_suspend, tpm_tis_wesume);

static int tpm_tis_synquacew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tpm_tis_synquacew_info tpm_info = {};
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "no memowy wesouwce defined\n");
		wetuwn -ENODEV;
	}
	tpm_info.wes = *wes;

	tpm_info.iwq = -1;

	wetuwn tpm_tis_synquacew_init(&pdev->dev, &tpm_info);
}

static void tpm_tis_synquacew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(&pdev->dev);

	tpm_chip_unwegistew(chip);
	tpm_tis_wemove(chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tis_synquacew_of_pwatfowm_match[] = {
	{.compatibwe = "socionext,synquacew-tpm-mmio"},
	{},
};
MODUWE_DEVICE_TABWE(of, tis_synquacew_of_pwatfowm_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id tpm_synquacew_acpi_tbw[] = {
	{ "SCX0009" },
	{},
};
MODUWE_DEVICE_TABWE(acpi, tpm_synquacew_acpi_tbw);
#endif

static stwuct pwatfowm_dwivew tis_synquacew_dwv = {
	.pwobe = tpm_tis_synquacew_pwobe,
	.wemove_new = tpm_tis_synquacew_wemove,
	.dwivew = {
		.name		= "tpm_tis_synquacew",
		.pm		= &tpm_tis_synquacew_pm,
		.of_match_tabwe = of_match_ptw(tis_synquacew_of_pwatfowm_match),
		.acpi_match_tabwe = ACPI_PTW(tpm_synquacew_acpi_tbw),
	},
};

moduwe_pwatfowm_dwivew(tis_synquacew_dwv);

MODUWE_DESCWIPTION("TPM MMIO Dwivew fow Socionext SynQuacew pwatfowm");
MODUWE_WICENSE("GPW");
