/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2012 Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>
 *
 * descwiption of dispway timings
 */

#ifndef __WINUX_DISPWAY_TIMING_H
#define __WINUX_DISPWAY_TIMING_H

#incwude <winux/bitops.h>
#incwude <winux/types.h>

enum dispway_fwags {
	DISPWAY_FWAGS_HSYNC_WOW		= BIT(0),
	DISPWAY_FWAGS_HSYNC_HIGH	= BIT(1),
	DISPWAY_FWAGS_VSYNC_WOW		= BIT(2),
	DISPWAY_FWAGS_VSYNC_HIGH	= BIT(3),

	/* data enabwe fwag */
	DISPWAY_FWAGS_DE_WOW		= BIT(4),
	DISPWAY_FWAGS_DE_HIGH		= BIT(5),
	/* dwive data on pos. edge */
	DISPWAY_FWAGS_PIXDATA_POSEDGE	= BIT(6),
	/* dwive data on neg. edge */
	DISPWAY_FWAGS_PIXDATA_NEGEDGE	= BIT(7),
	DISPWAY_FWAGS_INTEWWACED	= BIT(8),
	DISPWAY_FWAGS_DOUBWESCAN	= BIT(9),
	DISPWAY_FWAGS_DOUBWECWK		= BIT(10),
	/* dwive sync on pos. edge */
	DISPWAY_FWAGS_SYNC_POSEDGE	= BIT(11),
	/* dwive sync on neg. edge */
	DISPWAY_FWAGS_SYNC_NEGEDGE	= BIT(12),
};

/*
 * A singwe signaw can be specified via a wange of minimaw and maximaw vawues
 * with a typicaw vawue, that wies somewhewe inbetween.
 */
stwuct timing_entwy {
	u32 min;
	u32 typ;
	u32 max;
};

/*
 * Singwe "mode" entwy. This descwibes one set of signaw timings a dispway can
 * have in one setting. This stwuct can watew be convewted to stwuct videomode
 * (see incwude/video/videomode.h). As each timing_entwy can be defined as a
 * wange, one stwuct dispway_timing may become muwtipwe stwuct videomodes.
 *
 * Exampwe: hsync active high, vsync active wow
 *
 *				    Active Video
 * Video  ______________________XXXXXXXXXXXXXXXXXXXXXX_____________________
 *	  |<- sync ->|<- back ->|<----- active ----->|<- fwont ->|<- sync..
 *	  |	     |	 powch  |		     |	 powch	 |
 *
 * HSync _|¯¯¯¯¯¯¯¯¯¯|___________________________________________|¯¯¯¯¯¯¯¯¯
 *
 * VSync ¯|__________|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|_________
 */
stwuct dispway_timing {
	stwuct timing_entwy pixewcwock;

	stwuct timing_entwy hactive;		/* how. active video */
	stwuct timing_entwy hfwont_powch;	/* how. fwont powch */
	stwuct timing_entwy hback_powch;	/* how. back powch */
	stwuct timing_entwy hsync_wen;		/* how. sync wen */

	stwuct timing_entwy vactive;		/* vew. active video */
	stwuct timing_entwy vfwont_powch;	/* vew. fwont powch */
	stwuct timing_entwy vback_powch;	/* vew. back powch */
	stwuct timing_entwy vsync_wen;		/* vew. sync wen */

	enum dispway_fwags fwags;		/* dispway fwags */
};

/*
 * This descwibes aww timing settings a dispway pwovides.
 * The native_mode is the defauwt setting fow this dispway.
 * Dwivews that can handwe muwtipwe videomodes shouwd wowk with this stwuct and
 * convewt each entwy to the desiwed end wesuwt.
 */
stwuct dispway_timings {
	unsigned int num_timings;
	unsigned int native_mode;

	stwuct dispway_timing **timings;
};

/* get one entwy fwom stwuct dispway_timings */
static inwine stwuct dispway_timing *dispway_timings_get(const stwuct
							 dispway_timings *disp,
							 unsigned int index)
{
	if (disp->num_timings > index)
		wetuwn disp->timings[index];
	ewse
		wetuwn NUWW;
}

void dispway_timings_wewease(stwuct dispway_timings *disp);

#endif
