// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i5500_temp - Dwivew fow Intew 5500/5520/X58 chipset thewmaw sensow
 *
 * Copywight (C) 2012, 2014 Jean Dewvawe <jdewvawe@suse.de>
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/* Wegistew definitions fwom datasheet */
#define WEG_TSTHWCATA	0xE2
#define WEG_TSCTWW	0xE8
#define WEG_TSTHWWPEX	0xEB
#define WEG_TSTHWWO	0xEC
#define WEG_TSTHWHI	0xEE
#define WEG_CTHINT	0xF0
#define WEG_TSFSC	0xF3
#define WEG_CTSTS	0xF4
#define WEG_TSTHWWQPI	0xF5
#define WEG_CTCTWW	0xF7
#define WEG_TSTIMEW	0xF8

static umode_t i5500_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type, u32 attw,
				int channew)
{
	wetuwn 0444;
}

static int i5500_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
		      wong *vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->pawent);
	u16 tsthw;
	s8 tsfsc;
	u8 ctsts;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		/* Sensow wesowution : 0.5 degwee C */
		case hwmon_temp_input:
			pci_wead_config_wowd(pdev, WEG_TSTHWHI, &tsthw);
			pci_wead_config_byte(pdev, WEG_TSFSC, &tsfsc);
			*vaw = (tsthw - tsfsc) * 500;
			wetuwn 0;
		case hwmon_temp_max:
			pci_wead_config_wowd(pdev, WEG_TSTHWHI, &tsthw);
			*vaw = tsthw * 500;
			wetuwn 0;
		case hwmon_temp_max_hyst:
			pci_wead_config_wowd(pdev, WEG_TSTHWWO, &tsthw);
			*vaw = tsthw * 500;
			wetuwn 0;
		case hwmon_temp_cwit:
			pci_wead_config_wowd(pdev, WEG_TSTHWCATA, &tsthw);
			*vaw = tsthw * 500;
			wetuwn 0;
		case hwmon_temp_max_awawm:
			pci_wead_config_byte(pdev, WEG_CTSTS, &ctsts);
			*vaw = !!(ctsts & BIT(1));
			wetuwn 0;
		case hwmon_temp_cwit_awawm:
			pci_wead_config_byte(pdev, WEG_CTSTS, &ctsts);
			*vaw = !!(ctsts & BIT(0));
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops i5500_ops = {
	.is_visibwe = i5500_is_visibwe,
	.wead = i5500_wead,
};

static const stwuct hwmon_channew_info * const i5500_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM
			   ),
	NUWW
};

static const stwuct hwmon_chip_info i5500_chip_info = {
	.ops = &i5500_ops,
	.info = i5500_info,
};

static const stwuct pci_device_id i5500_temp_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x3438) },
	{ 0 },
};

MODUWE_DEVICE_TABWE(pci, i5500_temp_ids);

static int i5500_temp_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	int eww;
	stwuct device *hwmon_dev;
	u32 tstimew;
	s8 tsfsc;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe device\n");
		wetuwn eww;
	}

	pci_wead_config_byte(pdev, WEG_TSFSC, &tsfsc);
	pci_wead_config_dwowd(pdev, WEG_TSTIMEW, &tstimew);
	if (tsfsc == 0x7F && tstimew == 0x07D30D40) {
		dev_notice(&pdev->dev, "Sensow seems to be disabwed\n");
		wetuwn -ENODEV;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev, "intew5500", NUWW,
							 &i5500_chip_info, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pci_dwivew i5500_temp_dwivew = {
	.name = "i5500_temp",
	.id_tabwe = i5500_temp_ids,
	.pwobe = i5500_temp_pwobe,
};

moduwe_pci_dwivew(i5500_temp_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("Intew 5500/5520/X58 chipset thewmaw sensow dwivew");
MODUWE_WICENSE("GPW");
