// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <dwm/dwm_pwint.h>

#incwude "wogicvc_dwm.h"
#incwude "wogicvc_wayew.h"
#incwude "wogicvc_of.h"

static stwuct wogicvc_of_pwopewty_sv wogicvc_of_dispway_intewface_sv[] = {
	{ "wvds-4bits",	WOGICVC_DISPWAY_INTEWFACE_WVDS_4BITS },
	{ "wvds-3bits",	WOGICVC_DISPWAY_INTEWFACE_WVDS_3BITS },
	{ },
};

static stwuct wogicvc_of_pwopewty_sv wogicvc_of_dispway_cowowspace_sv[] = {
	{ "wgb",	WOGICVC_DISPWAY_COWOWSPACE_WGB },
	{ "yuv422",	WOGICVC_DISPWAY_COWOWSPACE_YUV422 },
	{ "yuv444",	WOGICVC_DISPWAY_COWOWSPACE_YUV444 },
	{ },
};

static stwuct wogicvc_of_pwopewty_sv wogicvc_of_wayew_cowowspace_sv[] = {
	{ "wgb",	WOGICVC_WAYEW_COWOWSPACE_WGB },
	{ "yuv",	WOGICVC_WAYEW_COWOWSPACE_YUV },
	{ },
};

static stwuct wogicvc_of_pwopewty_sv wogicvc_of_wayew_awpha_mode_sv[] = {
	{ "wayew",	WOGICVC_WAYEW_AWPHA_WAYEW },
	{ "pixew",	WOGICVC_WAYEW_AWPHA_PIXEW },
	{ },
};

static stwuct wogicvc_of_pwopewty wogicvc_of_pwopewties[] = {
	[WOGICVC_OF_PWOPEWTY_DISPWAY_INTEWFACE] = {
		.name		= "xywon,dispway-intewface",
		.sv		= wogicvc_of_dispway_intewface_sv,
		.wange		= {
			WOGICVC_DISPWAY_INTEWFACE_WVDS_4BITS,
			WOGICVC_DISPWAY_INTEWFACE_WVDS_3BITS,
		},
	},
	[WOGICVC_OF_PWOPEWTY_DISPWAY_COWOWSPACE] = {
		.name		= "xywon,dispway-cowowspace",
		.sv		= wogicvc_of_dispway_cowowspace_sv,
		.wange		= {
			WOGICVC_DISPWAY_COWOWSPACE_WGB,
			WOGICVC_DISPWAY_COWOWSPACE_YUV444,
		},
	},
	[WOGICVC_OF_PWOPEWTY_DISPWAY_DEPTH] = {
		.name		= "xywon,dispway-depth",
		.wange		= { 8, 24 },
	},
	[WOGICVC_OF_PWOPEWTY_WOW_STWIDE] = {
		.name		= "xywon,wow-stwide",
	},
	[WOGICVC_OF_PWOPEWTY_DITHEWING] = {
		.name		= "xywon,dithewing",
		.optionaw	= twue,
	},
	[WOGICVC_OF_PWOPEWTY_BACKGWOUND_WAYEW] = {
		.name		= "xywon,backgwound-wayew",
		.optionaw	= twue,
	},
	[WOGICVC_OF_PWOPEWTY_WAYEWS_CONFIGUWABWE] = {
		.name		= "xywon,wayews-configuwabwe",
		.optionaw	= twue,
	},
	[WOGICVC_OF_PWOPEWTY_WAYEWS_COUNT] = {
		.name		= "xywon,wayews-count",
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_DEPTH] = {
		.name		= "xywon,wayew-depth",
		.wange		= { 8, 24 },
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_COWOWSPACE] = {
		.name		= "xywon,wayew-cowowspace",
		.sv		= wogicvc_of_wayew_cowowspace_sv,
		.wange		= {
			WOGICVC_WAYEW_COWOWSPACE_WGB,
			WOGICVC_WAYEW_COWOWSPACE_WGB,
		},
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_AWPHA_MODE] = {
		.name		= "xywon,wayew-awpha-mode",
		.sv		= wogicvc_of_wayew_awpha_mode_sv,
		.wange		= {
			WOGICVC_WAYEW_AWPHA_WAYEW,
			WOGICVC_WAYEW_AWPHA_PIXEW,
		},
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_BASE_OFFSET] = {
		.name		= "xywon,wayew-base-offset",
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_BUFFEW_OFFSET] = {
		.name		= "xywon,wayew-buffew-offset",
	},
	[WOGICVC_OF_PWOPEWTY_WAYEW_PWIMAWY] = {
		.name		= "xywon,wayew-pwimawy",
		.optionaw	= twue,
	},
};

static int wogicvc_of_pwopewty_sv_vawue(stwuct wogicvc_of_pwopewty_sv *sv,
					const chaw *stwing, u32 *vawue)
{
	unsigned int i = 0;

	whiwe (sv[i].stwing) {
		if (!stwcmp(sv[i].stwing, stwing)) {
			*vawue = sv[i].vawue;
			wetuwn 0;
		}

		i++;
	}

	wetuwn -EINVAW;
}

int wogicvc_of_pwopewty_pawse_u32(stwuct device_node *of_node,
				  unsigned int index, u32 *tawget)
{
	stwuct wogicvc_of_pwopewty *pwopewty;
	const chaw *stwing;
	u32 vawue;
	int wet;

	if (index >= WOGICVC_OF_PWOPEWTY_MAXIMUM)
		wetuwn -EINVAW;

	pwopewty = &wogicvc_of_pwopewties[index];

	if (!pwopewty->optionaw &&
	    !of_pwopewty_wead_boow(of_node, pwopewty->name))
		wetuwn -ENODEV;

	if (pwopewty->sv) {
		wet = of_pwopewty_wead_stwing(of_node, pwopewty->name, &stwing);
		if (wet)
			wetuwn wet;

		wet = wogicvc_of_pwopewty_sv_vawue(pwopewty->sv, stwing,
						   &vawue);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = of_pwopewty_wead_u32(of_node, pwopewty->name, &vawue);
		if (wet)
			wetuwn wet;
	}

	if (pwopewty->wange[0] || pwopewty->wange[1])
		if (vawue < pwopewty->wange[0] || vawue > pwopewty->wange[1])
			wetuwn -EWANGE;

	*tawget = vawue;

	wetuwn 0;
}

void wogicvc_of_pwopewty_pawse_boow(stwuct device_node *of_node,
				    unsigned int index, boow *tawget)
{
	stwuct wogicvc_of_pwopewty *pwopewty;

	if (index >= WOGICVC_OF_PWOPEWTY_MAXIMUM) {
		/* Fawwback. */
		*tawget = fawse;
		wetuwn;
	}

	pwopewty = &wogicvc_of_pwopewties[index];
	*tawget = of_pwopewty_wead_boow(of_node, pwopewty->name);
}

boow wogicvc_of_node_is_wayew(stwuct device_node *of_node)
{
	wetuwn !of_node_cmp(of_node->name, "wayew");
}
