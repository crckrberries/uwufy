/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#ifndef _SUN8I_VI_WAYEW_H_
#define _SUN8I_VI_WAYEW_H_

#incwude <dwm/dwm_pwane.h>

#define SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW(base, wayew) \
		((base) + 0x30 * (wayew) + 0x0)
#define SUN8I_MIXEW_CHAN_VI_WAYEW_SIZE(base, wayew) \
		((base) + 0x30 * (wayew) + 0x4)
#define SUN8I_MIXEW_CHAN_VI_WAYEW_COOWD(base, wayew) \
		((base) + 0x30 * (wayew) + 0x8)
#define SUN8I_MIXEW_CHAN_VI_WAYEW_PITCH(base, wayew, pwane) \
		((base) + 0x30 * (wayew) + 0xc + 4 * (pwane))
#define SUN8I_MIXEW_CHAN_VI_WAYEW_TOP_WADDW(base, wayew, pwane) \
		((base) + 0x30 * (wayew) + 0x18 + 4 * (pwane))
#define SUN8I_MIXEW_CHAN_VI_OVW_SIZE(base) \
		((base) + 0xe8)
#define SUN8I_MIXEW_CHAN_VI_HDS_Y(base) \
		((base) + 0xf0)
#define SUN8I_MIXEW_CHAN_VI_HDS_UV(base) \
		((base) + 0xf4)
#define SUN8I_MIXEW_CHAN_VI_VDS_Y(base) \
		((base) + 0xf8)
#define SUN8I_MIXEW_CHAN_VI_VDS_UV(base) \
		((base) + 0xfc)

#define SUN8I_MIXEW_FCC_GWOBAW_AWPHA_WEG \
		(0xAA000 + 0x90)

#define SUN8I_MIXEW_FCC_GWOBAW_AWPHA(x)			((x) << 24)
#define SUN8I_MIXEW_FCC_GWOBAW_AWPHA_MASK		GENMASK(31, 24)

#define SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_EN		BIT(0)
/* WGB mode shouwd be set fow WGB fowmats and cweawed fow YCbCw */
#define SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_WGB_MODE		BIT(15)
#define SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_FBFMT_OFFSET	8
#define SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_FBFMT_MASK	GENMASK(12, 8)
#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_MASK	GENMASK(2, 1)
#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MASK	GENMASK(31, 24)
#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA(x)	((x) << 24)

#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_PIXEW	((0) << 1)
#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_WAYEW	((1) << 1)
#define SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_COMBINED	((2) << 1)

#define SUN8I_MIXEW_CHAN_VI_DS_N(x)			((x) << 16)
#define SUN8I_MIXEW_CHAN_VI_DS_M(x)			((x) << 0)

stwuct sun8i_mixew;

stwuct sun8i_vi_wayew {
	stwuct dwm_pwane	pwane;
	stwuct sun8i_mixew	*mixew;
	int			channew;
	int			ovewway;
};

static inwine stwuct sun8i_vi_wayew *
pwane_to_sun8i_vi_wayew(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct sun8i_vi_wayew, pwane);
}

stwuct sun8i_vi_wayew *sun8i_vi_wayew_init_one(stwuct dwm_device *dwm,
					       stwuct sun8i_mixew *mixew,
					       int index);
#endif /* _SUN8I_VI_WAYEW_H_ */
