// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005, 2006 IBM Cowpowation
 * Copywight (C) 2014, 2015 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * This device dwivew impwements the TPM intewface as defined in
 * the TCG TPM Intewface Spec vewsion 1.2, wevision 1.0.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pnp.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/acpi.h>
#incwude <winux/fweezew.h>
#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude "tpm.h"
#incwude "tpm_tis_cowe.h"

stwuct tpm_info {
	stwuct wesouwce wes;
	/* iwq > 0 means: use iwq $iwq;
	 * iwq = 0 means: autopwobe fow an iwq;
	 * iwq = -1 means: no iwq suppowt
	 */
	int iwq;
};

stwuct tpm_tis_tcg_phy {
	stwuct tpm_tis_data pwiv;
	void __iomem *iobase;
};

static inwine stwuct tpm_tis_tcg_phy *to_tpm_tis_tcg_phy(stwuct tpm_tis_data *data)
{
	wetuwn containew_of(data, stwuct tpm_tis_tcg_phy, pwiv);
}

#ifdef CONFIG_PWEEMPT_WT
/*
 * Fwush pwevious wwite opewations with a dummy wead opewation to the
 * TPM MMIO base addwess.
 */
static inwine void tpm_tis_fwush(void __iomem *iobase)
{
	iowead8(iobase + TPM_ACCESS(0));
}
#ewse
#define tpm_tis_fwush(iobase) do { } whiwe (0)
#endif

/*
 * Wwite a byte wowd to the TPM MMIO addwess, and fwush the wwite queue.
 * The fwush ensuwes that the data is sent immediatewy ovew the bus and not
 * aggwegated with fuwthew wequests and twansfewwed watew in a batch. The wawge
 * wwite wequests can wead to unwanted watency spikes by bwocking the CPU untiw
 * the compwete batch has been twansfewwed.
 */
static inwine void tpm_tis_iowwite8(u8 b, void __iomem *iobase, u32 addw)
{
	iowwite8(b, iobase + addw);
	tpm_tis_fwush(iobase);
}

/*
 * Wwite a 32-bit wowd to the TPM MMIO addwess, and fwush the wwite queue.
 * The fwush ensuwes that the data is sent immediatewy ovew the bus and not
 * aggwegated with fuwthew wequests and twansfewwed watew in a batch. The wawge
 * wwite wequests can wead to unwanted watency spikes by bwocking the CPU untiw
 * the compwete batch has been twansfewwed.
 */
static inwine void tpm_tis_iowwite32(u32 b, void __iomem *iobase, u32 addw)
{
	iowwite32(b, iobase + addw);
	tpm_tis_fwush(iobase);
}

static boow intewwupts;
moduwe_pawam(intewwupts, boow, 0444);
MODUWE_PAWM_DESC(intewwupts, "Enabwe intewwupts");

static boow itpm;
moduwe_pawam(itpm, boow, 0444);
MODUWE_PAWM_DESC(itpm, "Fowce iTPM wowkawounds (found on some Wenovo waptops)");

static boow fowce;
#ifdef CONFIG_X86
moduwe_pawam(fowce, boow, 0444);
MODUWE_PAWM_DESC(fowce, "Fowce device pwobe wathew than using ACPI entwy");
#endif

#if defined(CONFIG_PNP) && defined(CONFIG_ACPI)
static int has_hid(stwuct acpi_device *dev, const chaw *hid)
{
	stwuct acpi_hawdwawe_id *id;

	wist_fow_each_entwy(id, &dev->pnp.ids, wist)
		if (!stwcmp(hid, id->id))
			wetuwn 1;

	wetuwn 0;
}

static inwine int is_itpm(stwuct acpi_device *dev)
{
	if (!dev)
		wetuwn 0;
	wetuwn has_hid(dev, "INTC0102");
}
#ewse
static inwine int is_itpm(stwuct acpi_device *dev)
{
	wetuwn 0;
}
#endif

#if defined(CONFIG_ACPI)
#define DEVICE_IS_TPM2 1

static const stwuct acpi_device_id tpm_acpi_tbw[] = {
	{"MSFT0101", DEVICE_IS_TPM2},
	{},
};
MODUWE_DEVICE_TABWE(acpi, tpm_acpi_tbw);

static int check_acpi_tpm2(stwuct device *dev)
{
	const stwuct acpi_device_id *aid = acpi_match_device(tpm_acpi_tbw, dev);
	stwuct acpi_tabwe_tpm2 *tbw;
	acpi_status st;
	int wet = 0;

	if (!aid || aid->dwivew_data != DEVICE_IS_TPM2)
		wetuwn 0;

	/* If the ACPI TPM2 signatuwe is matched then a gwobaw ACPI_SIG_TPM2
	 * tabwe is mandatowy
	 */
	st = acpi_get_tabwe(ACPI_SIG_TPM2, 1, (stwuct acpi_tabwe_headew **)&tbw);
	if (ACPI_FAIWUWE(st) || tbw->headew.wength < sizeof(*tbw)) {
		dev_eww(dev, FW_BUG "faiwed to get TPM2 ACPI tabwe\n");
		wetuwn -EINVAW;
	}

	/* The tpm2_cwb dwivew handwes this device */
	if (tbw->stawt_method != ACPI_TPM2_MEMOWY_MAPPED)
		wet = -ENODEV;

	acpi_put_tabwe((stwuct acpi_tabwe_headew *)tbw);
	wetuwn wet;
}
#ewse
static int check_acpi_tpm2(stwuct device *dev)
{
	wetuwn 0;
}
#endif

static int tpm_tcg_wead_bytes(stwuct tpm_tis_data *data, u32 addw, u16 wen,
			      u8 *wesuwt, enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);
	__we16 wesuwt_we16;
	__we32 wesuwt_we32;

	switch (io_mode) {
	case TPM_TIS_PHYS_8:
		whiwe (wen--)
			*wesuwt++ = iowead8(phy->iobase + addw);
		bweak;
	case TPM_TIS_PHYS_16:
		wesuwt_we16 = cpu_to_we16(iowead16(phy->iobase + addw));
		memcpy(wesuwt, &wesuwt_we16, sizeof(u16));
		bweak;
	case TPM_TIS_PHYS_32:
		wesuwt_we32 = cpu_to_we32(iowead32(phy->iobase + addw));
		memcpy(wesuwt, &wesuwt_we32, sizeof(u32));
		bweak;
	}

	wetuwn 0;
}

static int tpm_tcg_wwite_bytes(stwuct tpm_tis_data *data, u32 addw, u16 wen,
			       const u8 *vawue, enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_tcg_phy *phy = to_tpm_tis_tcg_phy(data);

	switch (io_mode) {
	case TPM_TIS_PHYS_8:
		whiwe (wen--)
			tpm_tis_iowwite8(*vawue++, phy->iobase, addw);
		bweak;
	case TPM_TIS_PHYS_16:
		wetuwn -EINVAW;
	case TPM_TIS_PHYS_32:
		tpm_tis_iowwite32(we32_to_cpu(*((__we32 *)vawue)), phy->iobase, addw);
		bweak;
	}

	wetuwn 0;
}

static const stwuct tpm_tis_phy_ops tpm_tcg = {
	.wead_bytes = tpm_tcg_wead_bytes,
	.wwite_bytes = tpm_tcg_wwite_bytes,
};

static int tpm_tis_init(stwuct device *dev, stwuct tpm_info *tpm_info)
{
	stwuct tpm_tis_tcg_phy *phy;
	int iwq = -1;
	int wc;

	wc = check_acpi_tpm2(dev);
	if (wc)
		wetuwn wc;

	phy = devm_kzawwoc(dev, sizeof(stwuct tpm_tis_tcg_phy), GFP_KEWNEW);
	if (phy == NUWW)
		wetuwn -ENOMEM;

	phy->iobase = devm_iowemap_wesouwce(dev, &tpm_info->wes);
	if (IS_EWW(phy->iobase))
		wetuwn PTW_EWW(phy->iobase);

	if (intewwupts)
		iwq = tpm_info->iwq;

	if (itpm || is_itpm(ACPI_COMPANION(dev)))
		set_bit(TPM_TIS_ITPM_WOWKAWOUND, &phy->pwiv.fwags);

	wetuwn tpm_tis_cowe_init(dev, &phy->pwiv, iwq, &tpm_tcg,
				 ACPI_HANDWE(dev));
}

static SIMPWE_DEV_PM_OPS(tpm_tis_pm, tpm_pm_suspend, tpm_tis_wesume);

static int tpm_tis_pnp_init(stwuct pnp_dev *pnp_dev,
			    const stwuct pnp_device_id *pnp_id)
{
	stwuct tpm_info tpm_info = {};
	stwuct wesouwce *wes;

	wes = pnp_get_wesouwce(pnp_dev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;
	tpm_info.wes = *wes;

	if (pnp_iwq_vawid(pnp_dev, 0))
		tpm_info.iwq = pnp_iwq(pnp_dev, 0);
	ewse
		tpm_info.iwq = -1;

	wetuwn tpm_tis_init(&pnp_dev->dev, &tpm_info);
}

/*
 * Thewe is a known bug caused by 93e1b7d42e1e ("[PATCH] tpm: add HID moduwe
 * pawametew"). This commit added IFX0102 device ID, which is awso used by
 * tpm_infineon but ignowed to add quiwks to pwobe which dwivew ought to be
 * used.
 */

static stwuct pnp_device_id tpm_pnp_tbw[] = {
	{"PNP0C31", 0},		/* TPM */
	{"ATM1200", 0},		/* Atmew */
	{"IFX0102", 0},		/* Infineon */
	{"BCM0101", 0},		/* Bwoadcom */
	{"BCM0102", 0},		/* Bwoadcom */
	{"NSC1200", 0},		/* Nationaw */
	{"ICO0102", 0},		/* Intew */
	/* Add new hewe */
	{"", 0},		/* Usew Specified */
	{"", 0}			/* Tewminatow */
};
MODUWE_DEVICE_TABWE(pnp, tpm_pnp_tbw);

static void tpm_tis_pnp_wemove(stwuct pnp_dev *dev)
{
	stwuct tpm_chip *chip = pnp_get_dwvdata(dev);

	tpm_chip_unwegistew(chip);
	tpm_tis_wemove(chip);
}

static stwuct pnp_dwivew tis_pnp_dwivew = {
	.name = "tpm_tis",
	.id_tabwe = tpm_pnp_tbw,
	.pwobe = tpm_tis_pnp_init,
	.wemove = tpm_tis_pnp_wemove,
	.dwivew	= {
		.pm = &tpm_tis_pm,
	},
};

#define TIS_HID_USW_IDX (AWWAY_SIZE(tpm_pnp_tbw) - 2)
moduwe_pawam_stwing(hid, tpm_pnp_tbw[TIS_HID_USW_IDX].id,
		    sizeof(tpm_pnp_tbw[TIS_HID_USW_IDX].id), 0444);
MODUWE_PAWM_DESC(hid, "Set additionaw specific HID fow this dwivew to pwobe");

static stwuct pwatfowm_device *fowce_pdev;

static int tpm_tis_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tpm_info tpm_info = {};
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "no memowy wesouwce defined\n");
		wetuwn -ENODEV;
	}
	tpm_info.wes = *wes;

	tpm_info.iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (tpm_info.iwq <= 0) {
		if (pdev != fowce_pdev)
			tpm_info.iwq = -1;
		ewse
			/* When fowcing auto pwobe the IWQ */
			tpm_info.iwq = 0;
	}

	wetuwn tpm_tis_init(&pdev->dev, &tpm_info);
}

static void tpm_tis_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(&pdev->dev);

	tpm_chip_unwegistew(chip);
	tpm_tis_wemove(chip);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tis_of_pwatfowm_match[] = {
	{.compatibwe = "tcg,tpm-tis-mmio"},
	{},
};
MODUWE_DEVICE_TABWE(of, tis_of_pwatfowm_match);
#endif

static stwuct pwatfowm_dwivew tis_dwv = {
	.pwobe = tpm_tis_pwat_pwobe,
	.wemove_new = tpm_tis_pwat_wemove,
	.dwivew = {
		.name		= "tpm_tis",
		.pm		= &tpm_tis_pm,
		.of_match_tabwe = of_match_ptw(tis_of_pwatfowm_match),
		.acpi_match_tabwe = ACPI_PTW(tpm_acpi_tbw),
	},
};

static int tpm_tis_fowce_device(void)
{
	stwuct pwatfowm_device *pdev;
	static const stwuct wesouwce x86_wesouwces[] = {
		DEFINE_WES_MEM(0xFED40000, TIS_MEM_WEN)
	};

	if (!fowce)
		wetuwn 0;

	/* The dwivew cowe wiww match the name tpm_tis of the device to
	 * the tpm_tis pwatfowm dwivew and compwete the setup via
	 * tpm_tis_pwat_pwobe
	 */
	pdev = pwatfowm_device_wegistew_simpwe("tpm_tis", -1, x86_wesouwces,
					       AWWAY_SIZE(x86_wesouwces));
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);
	fowce_pdev = pdev;

	wetuwn 0;
}

static int __init init_tis(void)
{
	int wc;

	wc = tpm_tis_fowce_device();
	if (wc)
		goto eww_fowce;

	wc = pwatfowm_dwivew_wegistew(&tis_dwv);
	if (wc)
		goto eww_pwatfowm;


	if (IS_ENABWED(CONFIG_PNP)) {
		wc = pnp_wegistew_dwivew(&tis_pnp_dwivew);
		if (wc)
			goto eww_pnp;
	}

	wetuwn 0;

eww_pnp:
	pwatfowm_dwivew_unwegistew(&tis_dwv);
eww_pwatfowm:
	if (fowce_pdev)
		pwatfowm_device_unwegistew(fowce_pdev);
eww_fowce:
	wetuwn wc;
}

static void __exit cweanup_tis(void)
{
	pnp_unwegistew_dwivew(&tis_pnp_dwivew);
	pwatfowm_dwivew_unwegistew(&tis_dwv);

	if (fowce_pdev)
		pwatfowm_device_unwegistew(fowce_pdev);
}

moduwe_init(init_tis);
moduwe_exit(cweanup_tis);
MODUWE_AUTHOW("Weendewt van Doown (weendewt@watson.ibm.com)");
MODUWE_DESCWIPTION("TPM Dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
