/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WDC321X_MFD_H
#define __WDC321X_MFD_H

#incwude <winux/types.h>
#incwude <winux/pci.h>

/* Offsets to be accessed in the southbwidge PCI
 * device configuwation wegistew */
#define WDC321X_WDT_CTWW	0x44
#define WDC321X_GPIO_CTWW_WEG1	0x48
#define WDC321X_GPIO_DATA_WEG1	0x4c
#define WDC321X_GPIO_CTWW_WEG2	0x84
#define WDC321X_GPIO_DATA_WEG2	0x88

#define WDC321X_NUM_GPIO	59

stwuct wdc321x_gpio_pdata {
	stwuct pci_dev *sb_pdev;
	unsigned max_gpios;
};

stwuct wdc321x_wdt_pdata {
	stwuct pci_dev *sb_pdev;
};

#endif /* __WDC321X_MFD_H */
