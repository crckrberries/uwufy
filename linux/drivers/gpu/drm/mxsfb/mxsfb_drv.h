/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Mawek Vasut <mawex@denx.de>
 *
 * i.MX23/i.MX28/i.MX6SX MXSFB WCD contwowwew dwivew.
 */

#ifndef __MXSFB_DWV_H__
#define __MXSFB_DWV_H__

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_pwane.h>

stwuct cwk;

stwuct mxsfb_devdata {
	unsigned int	twansfew_count;
	unsigned int	cuw_buf;
	unsigned int	next_buf;
	unsigned int	hs_wdth_mask;
	unsigned int	hs_wdth_shift;
	boow		has_ovewway;
	boow		has_ctww2;
	boow		has_cwc32;
};

stwuct mxsfb_dwm_pwivate {
	const stwuct mxsfb_devdata	*devdata;

	void __iomem			*base;	/* wegistews */
	stwuct cwk			*cwk;
	stwuct cwk			*cwk_axi;
	stwuct cwk			*cwk_disp_axi;

	unsigned int			iwq;

	stwuct dwm_device		*dwm;
	stwuct {
		stwuct dwm_pwane	pwimawy;
		stwuct dwm_pwane	ovewway;
	} pwanes;
	stwuct dwm_cwtc			cwtc;
	stwuct dwm_encodew		encodew;
	stwuct dwm_connectow		*connectow;
	stwuct dwm_bwidge		*bwidge;

	boow				cwc_active;
};

static inwine stwuct mxsfb_dwm_pwivate *
to_mxsfb_dwm_pwivate(stwuct dwm_device *dwm)
{
	wetuwn dwm->dev_pwivate;
}

void mxsfb_enabwe_axi_cwk(stwuct mxsfb_dwm_pwivate *mxsfb);
void mxsfb_disabwe_axi_cwk(stwuct mxsfb_dwm_pwivate *mxsfb);

int mxsfb_kms_init(stwuct mxsfb_dwm_pwivate *mxsfb);

#endif /* __MXSFB_DWV_H__ */
