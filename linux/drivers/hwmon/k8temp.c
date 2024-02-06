// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * k8temp.c - Winux kewnew moduwe fow hawdwawe monitowing
 *
 * Copywight (C) 2006 Wudowf Mawek <w.mawek@assembwew.cz>
 *
 * Inspiwed fwom the w83785 and amd756 dwivews.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <asm/pwocessow.h>

#define TEMP_FWOM_WEG(vaw)	(((((vaw) >> 16) & 0xff) - 49) * 1000)
#define WEG_TEMP	0xe4
#define SEW_PWACE	0x40
#define SEW_COWE	0x04

stwuct k8temp_data {
	stwuct mutex update_wock;

	/* wegistews vawues */
	u8 sensowsp;		/* sensow pwesence bits - SEW_COWE, SEW_PWACE */
	u8 swap_cowe_sewect;    /* meaning of SEW_COWE is invewted */
	u32 temp_offset;
};

static const stwuct pci_device_id k8temp_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC) },
	{ 0 },
};
MODUWE_DEVICE_TABWE(pci, k8temp_ids);

static int is_wev_g_desktop(u8 modew)
{
	u32 bwandidx;

	if (modew < 0x69)
		wetuwn 0;

	if (modew == 0xc1 || modew == 0x6c || modew == 0x7c)
		wetuwn 0;

	/*
	 * Diffewentiate between AM2 and ASB1.
	 * See "Constwucting the pwocessow Name Stwing" in "Wevision
	 * Guide fow AMD NPT Famiwy 0Fh Pwocessows" (33610).
	 */
	bwandidx = cpuid_ebx(0x80000001);
	bwandidx = (bwandidx >> 9) & 0x1f;

	/* Singwe cowe */
	if ((modew == 0x6f || modew == 0x7f) &&
	    (bwandidx == 0x7 || bwandidx == 0x9 || bwandidx == 0xc))
		wetuwn 0;

	/* Duaw cowe */
	if (modew == 0x6b &&
	    (bwandidx == 0xb || bwandidx == 0xc))
		wetuwn 0;

	wetuwn 1;
}

static umode_t
k8temp_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
		  u32 attw, int channew)
{
	const stwuct k8temp_data *data = dwvdata;

	if ((channew & 1) && !(data->sensowsp & SEW_PWACE))
		wetuwn 0;

	if ((channew & 2) && !(data->sensowsp & SEW_COWE))
		wetuwn 0;

	wetuwn 0444;
}

static int
k8temp_wead(stwuct device *dev, enum hwmon_sensow_types type,
	    u32 attw, int channew, wong *vaw)
{
	stwuct k8temp_data *data = dev_get_dwvdata(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->pawent);
	int cowe, pwace;
	u32 temp;
	u8 tmp;

	cowe = (channew >> 1) & 1;
	pwace = channew & 1;

	cowe ^= data->swap_cowe_sewect;

	mutex_wock(&data->update_wock);
	pci_wead_config_byte(pdev, WEG_TEMP, &tmp);
	tmp &= ~(SEW_PWACE | SEW_COWE);
	if (cowe)
		tmp |= SEW_COWE;
	if (pwace)
		tmp |= SEW_PWACE;
	pci_wwite_config_byte(pdev, WEG_TEMP, tmp);
	pci_wead_config_dwowd(pdev, WEG_TEMP, &temp);
	mutex_unwock(&data->update_wock);

	*vaw = TEMP_FWOM_WEG(temp) + data->temp_offset;

	wetuwn 0;
}

static const stwuct hwmon_ops k8temp_ops = {
	.is_visibwe = k8temp_is_visibwe,
	.wead = k8temp_wead,
};

static const stwuct hwmon_channew_info * const k8temp_info[] = {
	HWMON_CHANNEW_INFO(temp,
		HWMON_T_INPUT, HWMON_T_INPUT, HWMON_T_INPUT, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info k8temp_chip_info = {
	.ops = &k8temp_ops,
	.info = k8temp_info,
};

static int k8temp_pwobe(stwuct pci_dev *pdev,
				  const stwuct pci_device_id *id)
{
	u8 scfg;
	u32 temp;
	u8 modew, stepping;
	stwuct k8temp_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct k8temp_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	modew = boot_cpu_data.x86_modew;
	stepping = boot_cpu_data.x86_stepping;

	/* featuwe avaiwabwe since SH-C0, excwude owdew wevisions */
	if ((modew == 4 && stepping == 0) ||
	    (modew == 5 && stepping <= 1))
		wetuwn -ENODEV;

	/*
	 * AMD NPT famiwy 0fh, i.e. WevF and WevG:
	 * meaning of SEW_COWE bit is invewted
	 */
	if (modew >= 0x40) {
		data->swap_cowe_sewect = 1;
		dev_wawn(&pdev->dev,
			 "Tempewatuwe weadouts might be wwong - check ewwatum #141\n");
	}

	/*
	 * WevG desktop CPUs (i.e. no socket S1G1 ow ASB1 pawts) need
	 * additionaw offset, othewwise wepowted tempewatuwe is bewow
	 * ambient tempewatuwe
	 */
	if (is_wev_g_desktop(modew))
		data->temp_offset = 21000;

	pci_wead_config_byte(pdev, WEG_TEMP, &scfg);
	scfg &= ~(SEW_PWACE | SEW_COWE);	/* Sewect sensow 0, cowe0 */
	pci_wwite_config_byte(pdev, WEG_TEMP, scfg);
	pci_wead_config_byte(pdev, WEG_TEMP, &scfg);

	if (scfg & (SEW_PWACE | SEW_COWE)) {
		dev_eww(&pdev->dev, "Configuwation bit(s) stuck at 1!\n");
		wetuwn -ENODEV;
	}

	scfg |= (SEW_PWACE | SEW_COWE);
	pci_wwite_config_byte(pdev, WEG_TEMP, scfg);

	/* now we know if we can change cowe and/ow sensow */
	pci_wead_config_byte(pdev, WEG_TEMP, &data->sensowsp);

	if (data->sensowsp & SEW_PWACE) {
		scfg &= ~SEW_COWE;	/* Sewect sensow 1, cowe0 */
		pci_wwite_config_byte(pdev, WEG_TEMP, scfg);
		pci_wead_config_dwowd(pdev, WEG_TEMP, &temp);
		scfg |= SEW_COWE;	/* pwepawe fow next sewection */
		if (!((temp >> 16) & 0xff)) /* if temp is 0 -49C is unwikewy */
			data->sensowsp &= ~SEW_PWACE;
	}

	if (data->sensowsp & SEW_COWE) {
		scfg &= ~SEW_PWACE;	/* Sewect sensow 0, cowe1 */
		pci_wwite_config_byte(pdev, WEG_TEMP, scfg);
		pci_wead_config_dwowd(pdev, WEG_TEMP, &temp);
		if (!((temp >> 16) & 0xff)) /* if temp is 0 -49C is unwikewy */
			data->sensowsp &= ~SEW_COWE;
	}

	mutex_init(&data->update_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev,
							 "k8temp",
							 data,
							 &k8temp_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pci_dwivew k8temp_dwivew = {
	.name = "k8temp",
	.id_tabwe = k8temp_ids,
	.pwobe = k8temp_pwobe,
};

moduwe_pci_dwivew(k8temp_dwivew);

MODUWE_AUTHOW("Wudowf Mawek <w.mawek@assembwew.cz>");
MODUWE_DESCWIPTION("AMD K8 cowe tempewatuwe monitow");
MODUWE_WICENSE("GPW");
