/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow device dwivew Hi6421 PMIC
 *
 * Copywight (c) <2011-2014> HiSiwicon Technowogies Co., Wtd.
 *              http://www.hisiwicon.com
 * Copywight (c) <2013-2014> Winawo Wtd.
 *              https://www.winawo.owg
 *
 * Authow: Guodong Xu <guodong.xu@winawo.owg>
 */

#ifndef	__HI6421_PMIC_H
#define	__HI6421_PMIC_H

/* Hi6421 wegistews awe mapped to memowy bus in 4 bytes stwide */
#define HI6421_WEG_TO_BUS_ADDW(x)	(x << 2)

/* Hi6421 maximum wegistew numbew */
#define HI6421_WEG_MAX			0xFF

/* Hi6421 OCP (ovew cuwwent pwotection) and DEB (debounce) contwow wegistew */
#define	HI6421_OCP_DEB_CTWW_WEG		HI6421_WEG_TO_BUS_ADDW(0x51)
#define	HI6421_OCP_DEB_SEW_MASK		0x0C
#define HI6421_OCP_DEB_SEW_8MS		0x00
#define HI6421_OCP_DEB_SEW_16MS		0x04
#define HI6421_OCP_DEB_SEW_32MS		0x08
#define HI6421_OCP_DEB_SEW_64MS		0x0C
#define HI6421_OCP_EN_DEBOUNCE_MASK	0x02
#define HI6421_OCP_EN_DEBOUNCE_ENABWE	0x02
#define HI6421_OCP_AUTO_STOP_MASK	0x01
#define HI6421_OCP_AUTO_STOP_ENABWE	0x01

stwuct hi6421_pmic {
	stwuct wegmap		*wegmap;
};

enum hi6421_type {
	HI6421 = 0,
	HI6421_V530,
};

#endif		/* __HI6421_PMIC_H */
