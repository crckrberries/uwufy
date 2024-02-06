/*
 * USB wewated definitions
 *
 * Copywight (C) 2009 MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_AWCH_USB_H
#define __ASM_AWCH_USB_H

/* Passed as the pwatfowm data to the OHCI dwivew */
stwuct	da8xx_ohci_woot_hub {
	/* Time fwom powew on to powew good (in 2 ms units) */
	u8	potpgt;
};

void davinci_setup_usb(unsigned mA, unsigned potpgt_ms);

#endif	/* ifndef __ASM_AWCH_USB_H */
