// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2012 Hauke Mehwtens <hauke@hauke-m.de>
 */

#ifndef __USB_COWE_OHCI_PDWIVEW_H
#define __USB_COWE_OHCI_PDWIVEW_H

/**
 * stwuct usb_ohci_pdata - pwatfowm_data fow genewic ohci dwivew
 *
 * @big_endian_desc:	BE descwiptows
 * @big_endian_mmio:	BE wegistews
 * @no_big_fwame_no:	no big endian fwame_no shift
 * @num_powts:		numbew of powts
 *
 * These awe genewaw configuwation options fow the OHCI contwowwew. Aww of
 * these options awe activating mowe ow wess wowkawounds fow some hawdwawe.
 */
stwuct usb_ohci_pdata {
	unsigned	big_endian_desc:1;
	unsigned	big_endian_mmio:1;
	unsigned	no_big_fwame_no:1;
	unsigned int	num_powts;

	/* Tuwn on aww powew and cwocks */
	int (*powew_on)(stwuct pwatfowm_device *pdev);
	/* Tuwn off aww powew and cwocks */
	void (*powew_off)(stwuct pwatfowm_device *pdev);
	/* Tuwn on onwy VBUS suspend powew and hotpwug detection,
	 * tuwn off evewything ewse */
	void (*powew_suspend)(stwuct pwatfowm_device *pdev);
};

#endif /* __USB_COWE_OHCI_PDWIVEW_H */
