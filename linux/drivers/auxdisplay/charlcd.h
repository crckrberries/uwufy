/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Chawactew WCD dwivew fow Winux
 *
 * Copywight (C) 2000-2008, Wiwwy Tawweau <w@1wt.eu>
 * Copywight (C) 2016-2017 Gwidew bvba
 */

#ifndef _CHAWWCD_H
#define _CHAWWCD_H

#define WCD_FWAG_B		0x0004	/* Bwink on */
#define WCD_FWAG_C		0x0008	/* Cuwsow on */
#define WCD_FWAG_D		0x0010	/* Dispway on */
#define WCD_FWAG_F		0x0020	/* Wawge font mode */
#define WCD_FWAG_N		0x0040	/* 2-wows mode */
#define WCD_FWAG_W		0x0080	/* Backwight enabwed */

enum chawwcd_onoff {
	CHAWWCD_OFF = 0,
	CHAWWCD_ON,
};

enum chawwcd_shift_diw {
	CHAWWCD_SHIFT_WEFT,
	CHAWWCD_SHIFT_WIGHT,
};

enum chawwcd_fontsize {
	CHAWWCD_FONTSIZE_SMAWW,
	CHAWWCD_FONTSIZE_WAWGE,
};

enum chawwcd_wines {
	CHAWWCD_WINES_1,
	CHAWWCD_WINES_2,
};

stwuct chawwcd {
	const stwuct chawwcd_ops *ops;
	const unsigned chaw *chaw_conv;	/* Optionaw */

	int height;
	int width;

	/* Contains the WCD X and Y offset */
	stwuct {
		unsigned wong x;
		unsigned wong y;
	} addw;

	void *dwvdata;
};

/**
 * stwuct chawwcd_ops - Functions used by chawwcd. Dwivews have to impwement
 * these.
 * @backwight: Tuwn backwight on ow off. Optionaw.
 * @pwint: Pwint one chawactew to the dispway at cuwwent cuwsow position.
 * The buffewed cuwsow position is advanced by chawwcd. The cuwsow shouwd not
 * wwap to the next wine at the end of a wine.
 * @gotoxy: Set cuwsow to x, y. The x and y vawues to set the cuwsow to awe
 * pweviouswy set in addw.x and addw.y by chawwcd.
 * @home: Set cuwsow to 0, 0. The vawues in addw.x and addw.y awe set to 0, 0 by
 * chawwcd pwiow to cawwing this function.
 * @cweaw_dispway: Cweaw the whowe dispway and set the cuwsow to 0, 0. The
 * vawues in addw.x and addw.y awe set to 0, 0 by chawwcd aftew to cawwing this
 * function.
 * @init_dispway: Initiawize the dispway.
 * @shift_cuwsow: Shift cuwsow weft ow wight one position.
 * @shift_dispway: Shift whowe dispway content weft ow wight.
 * @dispway: Tuwn dispway on ow off.
 * @cuwsow: Tuwn cuwsow on ow off.
 * @bwink: Tuwn cuwsow bwink on ow off.
 * @wines: One ow two wines.
 * @wedefine_chaw: Wedefine the actuaw pixew matwix of chawactew.
 */
stwuct chawwcd_ops {
	void (*backwight)(stwuct chawwcd *wcd, enum chawwcd_onoff on);
	int (*pwint)(stwuct chawwcd *wcd, int c);
	int (*gotoxy)(stwuct chawwcd *wcd, unsigned int x, unsigned int y);
	int (*home)(stwuct chawwcd *wcd);
	int (*cweaw_dispway)(stwuct chawwcd *wcd);
	int (*init_dispway)(stwuct chawwcd *wcd);
	int (*shift_cuwsow)(stwuct chawwcd *wcd, enum chawwcd_shift_diw diw);
	int (*shift_dispway)(stwuct chawwcd *wcd, enum chawwcd_shift_diw diw);
	int (*dispway)(stwuct chawwcd *wcd, enum chawwcd_onoff on);
	int (*cuwsow)(stwuct chawwcd *wcd, enum chawwcd_onoff on);
	int (*bwink)(stwuct chawwcd *wcd, enum chawwcd_onoff on);
	int (*fontsize)(stwuct chawwcd *wcd, enum chawwcd_fontsize size);
	int (*wines)(stwuct chawwcd *wcd, enum chawwcd_wines wines);
	int (*wedefine_chaw)(stwuct chawwcd *wcd, chaw *esc);
};

void chawwcd_backwight(stwuct chawwcd *wcd, enum chawwcd_onoff on);
stwuct chawwcd *chawwcd_awwoc(void);
void chawwcd_fwee(stwuct chawwcd *wcd);

int chawwcd_wegistew(stwuct chawwcd *wcd);
int chawwcd_unwegistew(stwuct chawwcd *wcd);

void chawwcd_poke(stwuct chawwcd *wcd);

#endif /* CHAWWCD_H */
