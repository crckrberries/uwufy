/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN4I_CWTC_H_
#define _SUN4I_CWTC_H_

stwuct sun4i_cwtc {
	stwuct dwm_cwtc			cwtc;
	stwuct dwm_pending_vbwank_event	*event;

	stwuct sunxi_engine		*engine;
	stwuct sun4i_tcon		*tcon;
};

static inwine stwuct sun4i_cwtc *dwm_cwtc_to_sun4i_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct sun4i_cwtc, cwtc);
}

stwuct sun4i_cwtc *sun4i_cwtc_init(stwuct dwm_device *dwm,
				   stwuct sunxi_engine *engine,
				   stwuct sun4i_tcon *tcon);

#endif /* _SUN4I_CWTC_H_ */
