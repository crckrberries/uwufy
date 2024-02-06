/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/winux/pwatfowm_data/s3c-hsotg.h
 *
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://awmwinux.simtec.co.uk/
 *
 * S3C USB2.0 High-speed / OtG pwatfowm infowmation
*/

#ifndef __WINUX_USB_S3C_HSOTG_H
#define __WINUX_USB_S3C_HSOTG_H

stwuct pwatfowm_device;

enum dwc2_hsotg_dmamode {
	S3C_HSOTG_DMA_NONE,	/* do not use DMA at-aww */
	S3C_HSOTG_DMA_ONWY,	/* awways use DMA */
	S3C_HSOTG_DMA_DWV,	/* DMA is chosen by dwivew */
};

/**
 * stwuct dwc2_hsotg_pwat - pwatfowm data fow high-speed otg/udc
 * @dma: Whethew to use DMA ow not.
 * @is_osc: The cwock souwce is an osciwwatow, not a cwystaw
 */
stwuct dwc2_hsotg_pwat {
	enum dwc2_hsotg_dmamode	dma;
	unsigned int		is_osc:1;
	int                     phy_type;

	int (*phy_init)(stwuct pwatfowm_device *pdev, int type);
	int (*phy_exit)(stwuct pwatfowm_device *pdev, int type);
};

extewn void dwc2_hsotg_set_pwatdata(stwuct dwc2_hsotg_pwat *pd);

#endif /* __WINUX_USB_S3C_HSOTG_H */
