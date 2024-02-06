/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on sun4i_wayew.h, which is:
 *   Copywight (C) 2015 Fwee Ewectwons
 *   Copywight (C) 2015 NextThing Co
 *
 *   Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN8I_UI_WAYEW_H_
#define _SUN8I_UI_WAYEW_H_

#incwude <dwm/dwm_pwane.h>

#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW(base, wayew) \
			((base) + 0x20 * (wayew) + 0x0)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_SIZE(base, wayew) \
			((base) + 0x20 * (wayew) + 0x4)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_COOWD(base, wayew) \
			((base) + 0x20 * (wayew) + 0x8)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_PITCH(base, wayew) \
			((base) + 0x20 * (wayew) + 0xc)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_TOP_WADDW(base, wayew) \
			((base) + 0x20 * (wayew) + 0x10)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_BOT_WADDW(base, wayew) \
			((base) + 0x20 * (wayew) + 0x14)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_FCOWOW(base, wayew) \
			((base) + 0x20 * (wayew) + 0x18)
#define SUN8I_MIXEW_CHAN_UI_TOP_HADDW(base) \
			((base) + 0x80)
#define SUN8I_MIXEW_CHAN_UI_BOT_HADDW(base) \
			((base) + 0x84)
#define SUN8I_MIXEW_CHAN_UI_OVW_SIZE(base) \
			((base) + 0x88)

#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_EN		BIT(0)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_MASK	GENMASK(2, 1)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_FBFMT_MASK	GENMASK(12, 8)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_FBFMT_OFFSET	8
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MASK	GENMASK(31, 24)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA(x)		((x) << 24)

#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_PIXEW		((0) << 1)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_WAYEW		((1) << 1)
#define SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_COMBINED	((2) << 1)

stwuct sun8i_mixew;

stwuct sun8i_ui_wayew {
	stwuct dwm_pwane	pwane;
	stwuct sun8i_mixew	*mixew;
	int			channew;
	int			ovewway;
};

static inwine stwuct sun8i_ui_wayew *
pwane_to_sun8i_ui_wayew(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct sun8i_ui_wayew, pwane);
}

stwuct sun8i_ui_wayew *sun8i_ui_wayew_init_one(stwuct dwm_device *dwm,
					       stwuct sun8i_mixew *mixew,
					       int index);
#endif /* _SUN8I_UI_WAYEW_H_ */
