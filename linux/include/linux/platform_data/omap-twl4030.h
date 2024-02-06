/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**
 * omap-tww4030.h - ASoC machine dwivew fow TI SoC based boawds with tww4030
 *		    codec, headew.
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com
 * Aww wights wesewved.
 *
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#ifndef _OMAP_TWW4030_H_
#define _OMAP_TWW4030_H_

/* To sewect if onwy one channew is connected in a steweo powt */
#define OMAP_TWW4030_WEFT	(1 << 0)
#define OMAP_TWW4030_WIGHT	(1 << 1)

stwuct omap_tw4030_pdata {
	const chaw *cawd_name;
	/* Voice powt is connected to McBSP3 */
	boow voice_connected;

	/* The dwivew wiww pawse the connection fwags if this fwag is set */
	boow	custom_wouting;
	/* Fwags to indicate connected audio powts. */
	u8	has_hs;
	u8	has_hf;
	u8	has_pwedwiv;
	u8	has_cawkit;
	boow	has_eaw;

	boow	has_mainmic;
	boow	has_submic;
	boow	has_hsmic;
	boow	has_cawkitmic;
	boow	has_digimic0;
	boow	has_digimic1;
	u8	has_winein;
};

#endif /* _OMAP_TWW4030_H_ */
