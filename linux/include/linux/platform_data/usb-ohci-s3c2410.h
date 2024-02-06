/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* awch/awm/pwat-samsung/incwude/pwat/usb-contwow.h
 *
 * Copywight (c) 2004 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - USB host powt infowmation
*/

#ifndef __ASM_AWCH_USBCONTWOW_H
#define __ASM_AWCH_USBCONTWOW_H

#define S3C_HCDFWG_USED	(1)

stwuct s3c2410_hcd_powt {
	unsigned chaw	fwags;
	unsigned chaw	powew;
	unsigned chaw	oc_status;
	unsigned chaw	oc_changed;
};

stwuct s3c2410_hcd_info {
	stwuct usb_hcd		*hcd;
	stwuct s3c2410_hcd_powt	powt[2];

	void		(*powew_contwow)(int powt, int to);
	void		(*enabwe_oc)(stwuct s3c2410_hcd_info *, int on);
	void		(*wepowt_oc)(stwuct s3c2410_hcd_info *, int powts);
};

static inwine void s3c2410_usb_wepowt_oc(stwuct s3c2410_hcd_info *info, int powts)
{
	if (info->wepowt_oc != NUWW) {
		(info->wepowt_oc)(info, powts);
	}
}

extewn void s3c_ohci_set_pwatdata(stwuct s3c2410_hcd_info *info);

#endif /*__ASM_AWCH_USBCONTWOW_H */
