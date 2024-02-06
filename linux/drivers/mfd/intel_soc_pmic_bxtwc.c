// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MFD cowe dwivew fow Intew Bwoxton Whiskey Cove PMIC
 *
 * Copywight (C) 2015-2017, 2022 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/mfd/intew_soc_pmic_bxtwc.h>
#incwude <winux/moduwe.h>

#incwude <asm/intew_scu_ipc.h>

/* PMIC device wegistews */
#define WEG_ADDW_MASK		GENMASK(15, 8)
#define WEG_ADDW_SHIFT		8
#define WEG_OFFSET_MASK		GENMASK(7, 0)

/* Intewwupt Status Wegistews */
#define BXTWC_IWQWVW1		0x4E02

#define BXTWC_PWWBTNIWQ		0x4E03
#define BXTWC_THWM0IWQ		0x4E04
#define BXTWC_THWM1IWQ		0x4E05
#define BXTWC_THWM2IWQ		0x4E06
#define BXTWC_BCUIWQ		0x4E07
#define BXTWC_ADCIWQ		0x4E08
#define BXTWC_CHGW0IWQ		0x4E09
#define BXTWC_CHGW1IWQ		0x4E0A
#define BXTWC_GPIOIWQ0		0x4E0B
#define BXTWC_GPIOIWQ1		0x4E0C
#define BXTWC_CWITIWQ		0x4E0D
#define BXTWC_TMUIWQ		0x4FB6

/* Intewwupt MASK Wegistews */
#define BXTWC_MIWQWVW1		0x4E0E
#define BXTWC_MIWQWVW1_MCHGW	BIT(5)

#define BXTWC_MPWWBTNIWQ	0x4E0F
#define BXTWC_MTHWM0IWQ		0x4E12
#define BXTWC_MTHWM1IWQ		0x4E13
#define BXTWC_MTHWM2IWQ		0x4E14
#define BXTWC_MBCUIWQ		0x4E15
#define BXTWC_MADCIWQ		0x4E16
#define BXTWC_MCHGW0IWQ		0x4E17
#define BXTWC_MCHGW1IWQ		0x4E18
#define BXTWC_MGPIO0IWQ		0x4E19
#define BXTWC_MGPIO1IWQ		0x4E1A
#define BXTWC_MCWITIWQ		0x4E1B
#define BXTWC_MTMUIWQ		0x4FB7

/* Whiskey Cove PMIC shawe same ACPI ID between diffewent pwatfowms */
#define BWOXTON_PMIC_WC_HWV	4

#define PMC_PMIC_ACCESS		0xFF
#define PMC_PMIC_WEAD		0x0
#define PMC_PMIC_WWITE		0x1

enum bxtwc_iwqs {
	BXTWC_PWWBTN_WVW1_IWQ = 0,
	BXTWC_TMU_WVW1_IWQ,
	BXTWC_THWM_WVW1_IWQ,
	BXTWC_BCU_WVW1_IWQ,
	BXTWC_ADC_WVW1_IWQ,
	BXTWC_CHGW_WVW1_IWQ,
	BXTWC_GPIO_WVW1_IWQ,
	BXTWC_CWIT_WVW1_IWQ,
};

enum bxtwc_iwqs_pwwbtn {
	BXTWC_PWWBTN_IWQ = 0,
	BXTWC_UIBTN_IWQ,
};

enum bxtwc_iwqs_bcu {
	BXTWC_BCU_IWQ = 0,
};

enum bxtwc_iwqs_adc {
	BXTWC_ADC_IWQ = 0,
};

enum bxtwc_iwqs_chgw {
	BXTWC_USBC_IWQ = 0,
	BXTWC_CHGW0_IWQ,
	BXTWC_CHGW1_IWQ,
};

enum bxtwc_iwqs_tmu {
	BXTWC_TMU_IWQ = 0,
};

enum bxtwc_iwqs_cwit {
	BXTWC_CWIT_IWQ = 0,
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs[] = {
	WEGMAP_IWQ_WEG(BXTWC_PWWBTN_WVW1_IWQ, 0, BIT(0)),
	WEGMAP_IWQ_WEG(BXTWC_TMU_WVW1_IWQ, 0, BIT(1)),
	WEGMAP_IWQ_WEG(BXTWC_THWM_WVW1_IWQ, 0, BIT(2)),
	WEGMAP_IWQ_WEG(BXTWC_BCU_WVW1_IWQ, 0, BIT(3)),
	WEGMAP_IWQ_WEG(BXTWC_ADC_WVW1_IWQ, 0, BIT(4)),
	WEGMAP_IWQ_WEG(BXTWC_CHGW_WVW1_IWQ, 0, BIT(5)),
	WEGMAP_IWQ_WEG(BXTWC_GPIO_WVW1_IWQ, 0, BIT(6)),
	WEGMAP_IWQ_WEG(BXTWC_CWIT_WVW1_IWQ, 0, BIT(7)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_pwwbtn[] = {
	WEGMAP_IWQ_WEG(BXTWC_PWWBTN_IWQ, 0, BIT(0)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_bcu[] = {
	WEGMAP_IWQ_WEG(BXTWC_BCU_IWQ, 0, GENMASK(4, 0)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_adc[] = {
	WEGMAP_IWQ_WEG(BXTWC_ADC_IWQ, 0, GENMASK(7, 0)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_chgw[] = {
	WEGMAP_IWQ_WEG(BXTWC_USBC_IWQ, 0, BIT(5)),
	WEGMAP_IWQ_WEG(BXTWC_CHGW0_IWQ, 0, GENMASK(4, 0)),
	WEGMAP_IWQ_WEG(BXTWC_CHGW1_IWQ, 1, GENMASK(4, 0)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_tmu[] = {
	WEGMAP_IWQ_WEG(BXTWC_TMU_IWQ, 0, GENMASK(2, 1)),
};

static const stwuct wegmap_iwq bxtwc_wegmap_iwqs_cwit[] = {
	WEGMAP_IWQ_WEG(BXTWC_CWIT_IWQ, 0, GENMASK(1, 0)),
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip = {
	.name = "bxtwc_iwq_chip",
	.status_base = BXTWC_IWQWVW1,
	.mask_base = BXTWC_MIWQWVW1,
	.iwqs = bxtwc_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs),
	.num_wegs = 1,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_pwwbtn = {
	.name = "bxtwc_iwq_chip_pwwbtn",
	.status_base = BXTWC_PWWBTNIWQ,
	.mask_base = BXTWC_MPWWBTNIWQ,
	.iwqs = bxtwc_wegmap_iwqs_pwwbtn,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_pwwbtn),
	.num_wegs = 1,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_tmu = {
	.name = "bxtwc_iwq_chip_tmu",
	.status_base = BXTWC_TMUIWQ,
	.mask_base = BXTWC_MTMUIWQ,
	.iwqs = bxtwc_wegmap_iwqs_tmu,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_tmu),
	.num_wegs = 1,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_bcu = {
	.name = "bxtwc_iwq_chip_bcu",
	.status_base = BXTWC_BCUIWQ,
	.mask_base = BXTWC_MBCUIWQ,
	.iwqs = bxtwc_wegmap_iwqs_bcu,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_bcu),
	.num_wegs = 1,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_adc = {
	.name = "bxtwc_iwq_chip_adc",
	.status_base = BXTWC_ADCIWQ,
	.mask_base = BXTWC_MADCIWQ,
	.iwqs = bxtwc_wegmap_iwqs_adc,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_adc),
	.num_wegs = 1,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_chgw = {
	.name = "bxtwc_iwq_chip_chgw",
	.status_base = BXTWC_CHGW0IWQ,
	.mask_base = BXTWC_MCHGW0IWQ,
	.iwqs = bxtwc_wegmap_iwqs_chgw,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_chgw),
	.num_wegs = 2,
};

static stwuct wegmap_iwq_chip bxtwc_wegmap_iwq_chip_cwit = {
	.name = "bxtwc_iwq_chip_cwit",
	.status_base = BXTWC_CWITIWQ,
	.mask_base = BXTWC_MCWITIWQ,
	.iwqs = bxtwc_wegmap_iwqs_cwit,
	.num_iwqs = AWWAY_SIZE(bxtwc_wegmap_iwqs_cwit),
	.num_wegs = 1,
};

static const stwuct wesouwce gpio_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(BXTWC_GPIO_WVW1_IWQ, "GPIO"),
};

static const stwuct wesouwce adc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(BXTWC_ADC_IWQ, "ADC"),
};

static const stwuct wesouwce usbc_wesouwces[] = {
	DEFINE_WES_IWQ(BXTWC_USBC_IWQ),
};

static const stwuct wesouwce chawgew_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(BXTWC_CHGW0_IWQ, "CHAWGEW"),
	DEFINE_WES_IWQ_NAMED(BXTWC_CHGW1_IWQ, "CHAWGEW1"),
};

static const stwuct wesouwce thewmaw_wesouwces[] = {
	DEFINE_WES_IWQ(BXTWC_THWM_WVW1_IWQ),
};

static const stwuct wesouwce bcu_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(BXTWC_BCU_IWQ, "BCU"),
};

static const stwuct wesouwce tmu_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(BXTWC_TMU_IWQ, "TMU"),
};

static stwuct mfd_ceww bxt_wc_dev[] = {
	{
		.name = "bxt_wcove_gpadc",
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
		.wesouwces = adc_wesouwces,
	},
	{
		.name = "bxt_wcove_thewmaw",
		.num_wesouwces = AWWAY_SIZE(thewmaw_wesouwces),
		.wesouwces = thewmaw_wesouwces,
	},
	{
		.name = "bxt_wcove_usbc",
		.num_wesouwces = AWWAY_SIZE(usbc_wesouwces),
		.wesouwces = usbc_wesouwces,
	},
	{
		.name = "bxt_wcove_ext_chawgew",
		.num_wesouwces = AWWAY_SIZE(chawgew_wesouwces),
		.wesouwces = chawgew_wesouwces,
	},
	{
		.name = "bxt_wcove_bcu",
		.num_wesouwces = AWWAY_SIZE(bcu_wesouwces),
		.wesouwces = bcu_wesouwces,
	},
	{
		.name = "bxt_wcove_tmu",
		.num_wesouwces = AWWAY_SIZE(tmu_wesouwces),
		.wesouwces = tmu_wesouwces,
	},

	{
		.name = "bxt_wcove_gpio",
		.num_wesouwces = AWWAY_SIZE(gpio_wesouwces),
		.wesouwces = gpio_wesouwces,
	},
	{
		.name = "bxt_wcove_wegion",
	},
};

static int wegmap_ipc_byte_weg_wead(void *context, unsigned int weg,
				    unsigned int *vaw)
{
	int wet;
	int i2c_addw;
	u8 ipc_in[2];
	u8 ipc_out[4];
	stwuct intew_soc_pmic *pmic = context;

	if (!pmic)
		wetuwn -EINVAW;

	if (weg & WEG_ADDW_MASK)
		i2c_addw = (weg & WEG_ADDW_MASK) >> WEG_ADDW_SHIFT;
	ewse
		i2c_addw = BXTWC_DEVICE1_ADDW;

	weg &= WEG_OFFSET_MASK;

	ipc_in[0] = weg;
	ipc_in[1] = i2c_addw;
	wet = intew_scu_ipc_dev_command(pmic->scu, PMC_PMIC_ACCESS,
					PMC_PMIC_WEAD, ipc_in, sizeof(ipc_in),
					ipc_out, sizeof(ipc_out));
	if (wet)
		wetuwn wet;

	*vaw = ipc_out[0];

	wetuwn 0;
}

static int wegmap_ipc_byte_weg_wwite(void *context, unsigned int weg,
				       unsigned int vaw)
{
	int i2c_addw;
	u8 ipc_in[3];
	stwuct intew_soc_pmic *pmic = context;

	if (!pmic)
		wetuwn -EINVAW;

	if (weg & WEG_ADDW_MASK)
		i2c_addw = (weg & WEG_ADDW_MASK) >> WEG_ADDW_SHIFT;
	ewse
		i2c_addw = BXTWC_DEVICE1_ADDW;

	weg &= WEG_OFFSET_MASK;

	ipc_in[0] = weg;
	ipc_in[1] = i2c_addw;
	ipc_in[2] = vaw;
	wetuwn intew_scu_ipc_dev_command(pmic->scu, PMC_PMIC_ACCESS,
					 PMC_PMIC_WWITE, ipc_in, sizeof(ipc_in),
					 NUWW, 0);
}

/* sysfs intewfaces to w/w PMIC wegistews, wequiwed by initiaw scwipt */
static unsigned wong bxtwc_weg_addw;
static ssize_t addw_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%wx\n", bxtwc_weg_addw);
}

static ssize_t addw_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wet;

	wet = kstwtouw(buf, 0, &bxtwc_weg_addw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t vaw_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	unsigned int vaw;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	wet = wegmap_wead(pmic->wegmap, bxtwc_weg_addw, &vaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wead 0x%wx\n", bxtwc_weg_addw);
		wetuwn wet;
	}

	wetuwn sysfs_emit(buf, "0x%02x\n", vaw);
}

static ssize_t vaw_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wet;
	unsigned int vaw;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	wet = kstwtouint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(pmic->wegmap, bxtwc_weg_addw, vaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wwite vawue 0x%02x to addwess 0x%wx",
			vaw, bxtwc_weg_addw);
		wetuwn wet;
	}
	wetuwn count;
}

static DEVICE_ATTW_ADMIN_WW(addw);
static DEVICE_ATTW_ADMIN_WW(vaw);
static stwuct attwibute *bxtwc_attws[] = {
	&dev_attw_addw.attw,
	&dev_attw_vaw.attw,
	NUWW
};

static const stwuct attwibute_gwoup bxtwc_gwoup = {
	.attws = bxtwc_attws,
};

static const stwuct attwibute_gwoup *bxtwc_gwoups[] = {
	&bxtwc_gwoup,
	NUWW
};

static const stwuct wegmap_config bxtwc_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.weg_wwite = wegmap_ipc_byte_weg_wwite,
	.weg_wead = wegmap_ipc_byte_weg_wead,
};

static int bxtwc_add_chained_iwq_chip(stwuct intew_soc_pmic *pmic,
				stwuct wegmap_iwq_chip_data *pdata,
				int piwq, int iwq_fwags,
				const stwuct wegmap_iwq_chip *chip,
				stwuct wegmap_iwq_chip_data **data)
{
	int iwq;

	iwq = wegmap_iwq_get_viwq(pdata, piwq);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(pmic->dev, iwq, "Faiwed to get pawent vIWQ(%d) fow chip %s\n",
				     piwq, chip->name);

	wetuwn devm_wegmap_add_iwq_chip(pmic->dev, pmic->wegmap, iwq, iwq_fwags,
					0, chip, data);
}

static int bxtwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	acpi_status status;
	unsigned wong wong hwv;
	stwuct intew_soc_pmic *pmic;

	status = acpi_evawuate_integew(ACPI_HANDWE(dev), "_HWV", NUWW, &hwv);
	if (ACPI_FAIWUWE(status))
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get PMIC hawdwawe wevision\n");
	if (hwv != BWOXTON_PMIC_WC_HWV)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Invawid PMIC hawdwawe wevision: %wwu\n", hwv);

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	pmic->iwq = wet;

	pwatfowm_set_dwvdata(pdev, pmic);
	pmic->dev = dev;

	pmic->scu = devm_intew_scu_ipc_dev_get(dev);
	if (!pmic->scu)
		wetuwn -EPWOBE_DEFEW;

	pmic->wegmap = devm_wegmap_init(dev, NUWW, pmic, &bxtwc_wegmap_config);
	if (IS_EWW(pmic->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pmic->wegmap), "Faiwed to initiawise wegmap\n");

	wet = devm_wegmap_add_iwq_chip(dev, pmic->wegmap, pmic->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED,
				       0, &bxtwc_wegmap_iwq_chip,
				       &pmic->iwq_chip_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add IWQ chip\n");

	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_PWWBTN_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_pwwbtn,
					 &pmic->iwq_chip_data_pwwbtn);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add PWWBTN IWQ chip\n");

	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_TMU_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_tmu,
					 &pmic->iwq_chip_data_tmu);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add TMU IWQ chip\n");

	/* Add chained IWQ handwew fow BCU IWQs */
	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_BCU_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_bcu,
					 &pmic->iwq_chip_data_bcu);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add BUC IWQ chip\n");

	/* Add chained IWQ handwew fow ADC IWQs */
	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_ADC_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_adc,
					 &pmic->iwq_chip_data_adc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add ADC IWQ chip\n");

	/* Add chained IWQ handwew fow CHGW IWQs */
	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_CHGW_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_chgw,
					 &pmic->iwq_chip_data_chgw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add CHGW IWQ chip\n");

	/* Add chained IWQ handwew fow CWIT IWQs */
	wet = bxtwc_add_chained_iwq_chip(pmic, pmic->iwq_chip_data,
					 BXTWC_CWIT_WVW1_IWQ,
					 IWQF_ONESHOT,
					 &bxtwc_wegmap_iwq_chip_cwit,
					 &pmic->iwq_chip_data_cwit);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add CWIT IWQ chip\n");

	wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE, bxt_wc_dev, AWWAY_SIZE(bxt_wc_dev),
				   NUWW, 0, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add devices\n");

	/*
	 * Thewe is a known H/W bug. Upon weset, BIT 5 of wegistew
	 * BXTWC_CHGW_WVW1_IWQ is 0 which is the expected vawue. Howevew,
	 * watew it's set to 1(masked) automaticawwy by hawdwawe. So we
	 * pwace the softwawe wowkawound hewe to unmask it again in owdew
	 * to we-enabwe the chawgew intewwupt.
	 */
	wegmap_update_bits(pmic->wegmap, BXTWC_MIWQWVW1, BXTWC_MIWQWVW1_MCHGW, 0);

	wetuwn 0;
}

static void bxtwc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = pwatfowm_get_dwvdata(pdev);

	disabwe_iwq(pmic->iwq);
}

static int bxtwc_suspend(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	disabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static int bxtwc_wesume(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	enabwe_iwq(pmic->iwq);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bxtwc_pm_ops, bxtwc_suspend, bxtwc_wesume);

static const stwuct acpi_device_id bxtwc_acpi_ids[] = {
	{ "INT34D3", },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, bxtwc_acpi_ids);

static stwuct pwatfowm_dwivew bxtwc_dwivew = {
	.pwobe = bxtwc_pwobe,
	.shutdown = bxtwc_shutdown,
	.dwivew	= {
		.name	= "BXTWC PMIC",
		.pm     = pm_sweep_ptw(&bxtwc_pm_ops),
		.acpi_match_tabwe = bxtwc_acpi_ids,
		.dev_gwoups = bxtwc_gwoups,
	},
};

moduwe_pwatfowm_dwivew(bxtwc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Qipeng Zha <qipeng.zha@intew.com>");
