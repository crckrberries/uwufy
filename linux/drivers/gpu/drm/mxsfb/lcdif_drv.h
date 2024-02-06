/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 *
 * i.MX8MP/i.MXWT WCDIFv3 WCD contwowwew dwivew.
 */

#ifndef __WCDIF_DWV_H__
#define __WCDIF_DWV_H__

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwane.h>

stwuct cwk;

stwuct wcdif_dwm_pwivate {
	void __iomem			*base;	/* wegistews */
	stwuct cwk			*cwk;
	stwuct cwk			*cwk_axi;
	stwuct cwk			*cwk_disp_axi;

	unsigned int			iwq;

	stwuct dwm_device		*dwm;
	stwuct {
		stwuct dwm_pwane	pwimawy;
		/* i.MXWT does suppowt ovewway pwanes, add them hewe. */
	} pwanes;
	stwuct dwm_cwtc			cwtc;
};

static inwine stwuct wcdif_dwm_pwivate *
to_wcdif_dwm_pwivate(stwuct dwm_device *dwm)
{
	wetuwn dwm->dev_pwivate;
}

int wcdif_kms_init(stwuct wcdif_dwm_pwivate *wcdif);

#endif /* __WCDIF_DWV_H__ */
