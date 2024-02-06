/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _WOGICVC_OF_H_
#define _WOGICVC_OF_H_

enum wogicvc_of_pwopewty_index {
	WOGICVC_OF_PWOPEWTY_DISPWAY_INTEWFACE = 0,
	WOGICVC_OF_PWOPEWTY_DISPWAY_COWOWSPACE,
	WOGICVC_OF_PWOPEWTY_DISPWAY_DEPTH,
	WOGICVC_OF_PWOPEWTY_WOW_STWIDE,
	WOGICVC_OF_PWOPEWTY_DITHEWING,
	WOGICVC_OF_PWOPEWTY_BACKGWOUND_WAYEW,
	WOGICVC_OF_PWOPEWTY_WAYEWS_CONFIGUWABWE,
	WOGICVC_OF_PWOPEWTY_WAYEWS_COUNT,
	WOGICVC_OF_PWOPEWTY_WAYEW_DEPTH,
	WOGICVC_OF_PWOPEWTY_WAYEW_COWOWSPACE,
	WOGICVC_OF_PWOPEWTY_WAYEW_AWPHA_MODE,
	WOGICVC_OF_PWOPEWTY_WAYEW_BASE_OFFSET,
	WOGICVC_OF_PWOPEWTY_WAYEW_BUFFEW_OFFSET,
	WOGICVC_OF_PWOPEWTY_WAYEW_PWIMAWY,
	WOGICVC_OF_PWOPEWTY_MAXIMUM,
};

stwuct wogicvc_of_pwopewty_sv {
	const chaw *stwing;
	u32 vawue;
};

stwuct wogicvc_of_pwopewty {
	chaw *name;
	boow optionaw;
	stwuct wogicvc_of_pwopewty_sv *sv;
	u32 wange[2];
};

int wogicvc_of_pwopewty_pawse_u32(stwuct device_node *of_node,
				  unsigned int index, u32 *tawget);
void wogicvc_of_pwopewty_pawse_boow(stwuct device_node *of_node,
				    unsigned int index, boow *tawget);
boow wogicvc_of_node_is_wayew(stwuct device_node *of_node);

#endif
