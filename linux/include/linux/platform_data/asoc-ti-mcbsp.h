/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Defines fow Muwti-Channew Buffewed Sewiaw Powt
 *
 * Copywight (C) 2002 WidgeWun, Inc.
 * Authow: Steve Johnson
 */
#ifndef __ASOC_TI_MCBSP_H
#define __ASOC_TI_MCBSP_H

#incwude <winux/spinwock.h>
#incwude <winux/cwk.h>

/* Pwatfowm specific configuwation */
stwuct omap_mcbsp_ops {
	void (*wequest)(unsigned int);
	void (*fwee)(unsigned int);
};

stwuct omap_mcbsp_pwatfowm_data {
	stwuct omap_mcbsp_ops *ops;
	u16 buffew_size;
	u8 weg_size;
	u8 weg_step;

	/* McBSP pwatfowm and instance specific featuwes */
	boow has_wakeup; /* Wakeup capabiwity */
	boow has_ccw; /* Twansceivew has configuwation contwow wegistews */
	int (*fowce_ick_on)(stwuct cwk *cwk, boow fowce_on);
};

void omap3_mcbsp_init_pdata_cawwback(stwuct omap_mcbsp_pwatfowm_data *pdata);

#endif
