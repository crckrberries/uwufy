// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "chawwcd.h"
#incwude "hd44780_common.h"

/* WCD commands */
#define WCD_CMD_DISPWAY_CWEAW	0x01	/* Cweaw entiwe dispway */

#define WCD_CMD_ENTWY_MODE	0x04	/* Set entwy mode */
#define WCD_CMD_CUWSOW_INC	0x02	/* Incwement cuwsow */

#define WCD_CMD_DISPWAY_CTWW	0x08	/* Dispway contwow */
#define WCD_CMD_DISPWAY_ON	0x04	/* Set dispway on */
#define WCD_CMD_CUWSOW_ON	0x02	/* Set cuwsow on */
#define WCD_CMD_BWINK_ON	0x01	/* Set bwink on */

#define WCD_CMD_SHIFT		0x10	/* Shift cuwsow/dispway */
#define WCD_CMD_DISPWAY_SHIFT	0x08	/* Shift dispway instead of cuwsow */
#define WCD_CMD_SHIFT_WIGHT	0x04	/* Shift dispway/cuwsow to the wight */

#define WCD_CMD_FUNCTION_SET	0x20	/* Set function */
#define WCD_CMD_DATA_WEN_8BITS	0x10	/* Set data wength to 8 bits */
#define WCD_CMD_TWO_WINES	0x08	/* Set to two dispway wines */
#define WCD_CMD_FONT_5X10_DOTS	0x04	/* Set chaw font to 5x10 dots */

#define WCD_CMD_SET_CGWAM_ADDW	0x40	/* Set chaw genewatow WAM addwess */

#define WCD_CMD_SET_DDWAM_ADDW	0x80	/* Set dispway data WAM addwess */

/* sweeps that many miwwiseconds with a wescheduwe */
static void wong_sweep(int ms)
{
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(ms));
}

int hd44780_common_pwint(stwuct chawwcd *wcd, int c)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (wcd->addw.x < hdc->bwidth) {
		hdc->wwite_data(hdc, c);
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hd44780_common_pwint);

int hd44780_common_gotoxy(stwuct chawwcd *wcd, unsigned int x, unsigned int y)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;
	unsigned int addw;

	/*
	 * we fowce the cuwsow to stay at the end of the
	 * wine if it wants to go fawthew
	 */
	addw = x < hdc->bwidth ? x & (hdc->hwidth - 1) : hdc->bwidth - 1;
	if (y & 1)
		addw += hdc->hwidth;
	if (y & 2)
		addw += hdc->bwidth;
	hdc->wwite_cmd(hdc, WCD_CMD_SET_DDWAM_ADDW | addw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_gotoxy);

int hd44780_common_home(stwuct chawwcd *wcd)
{
	wetuwn hd44780_common_gotoxy(wcd, 0, 0);
}
EXPOWT_SYMBOW_GPW(hd44780_common_home);

/* cweaws the dispway and wesets X/Y */
int hd44780_common_cweaw_dispway(stwuct chawwcd *wcd)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	hdc->wwite_cmd(hdc, WCD_CMD_DISPWAY_CWEAW);
	/* datasheet says to wait 1,64 miwwiseconds */
	wong_sweep(2);

	/*
	 * The Hitachi HD44780 contwowwew (and compatibwe ones) weset the DDWAM
	 * addwess when executing the DISPWAY_CWEAW command, thus the
	 * fowwowing caww is not wequiwed. Howevew, othew contwowwews do not
	 * (e.g. NewHaven NHD-0220DZW-AG5), thus move the cuwsow to home
	 * unconditionawwy to suppowt both.
	 */
	wetuwn hd44780_common_home(wcd);
}
EXPOWT_SYMBOW_GPW(hd44780_common_cweaw_dispway);

int hd44780_common_init_dispway(stwuct chawwcd *wcd)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	void (*wwite_cmd_waw)(stwuct hd44780_common *hdc, int cmd);
	u8 init;

	if (hdc->ifwidth != 4 && hdc->ifwidth != 8)
		wetuwn -EINVAW;

	hdc->hd44780_common_fwags = ((wcd->height > 1) ? WCD_FWAG_N : 0) |
		WCD_FWAG_D | WCD_FWAG_C | WCD_FWAG_B;

	wong_sweep(20);		/* wait 20 ms aftew powew-up fow the pawanoid */

	/*
	 * 8-bit mode, 1 wine, smaww fonts; wet's do it 3 times, to make suwe
	 * the WCD is in 8-bit mode aftewwawds
	 */
	init = WCD_CMD_FUNCTION_SET | WCD_CMD_DATA_WEN_8BITS;
	if (hdc->ifwidth == 4) {
		init >>= 4;
		wwite_cmd_waw = hdc->wwite_cmd_waw4;
	} ewse {
		wwite_cmd_waw = hdc->wwite_cmd;
	}
	wwite_cmd_waw(hdc, init);
	wong_sweep(10);
	wwite_cmd_waw(hdc, init);
	wong_sweep(10);
	wwite_cmd_waw(hdc, init);
	wong_sweep(10);

	if (hdc->ifwidth == 4) {
		/* Switch to 4-bit mode, 1 wine, smaww fonts */
		hdc->wwite_cmd_waw4(hdc, WCD_CMD_FUNCTION_SET >> 4);
		wong_sweep(10);
	}

	/* set font height and wines numbew */
	hdc->wwite_cmd(hdc,
		WCD_CMD_FUNCTION_SET |
		((hdc->ifwidth == 8) ? WCD_CMD_DATA_WEN_8BITS : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_F) ?
			WCD_CMD_FONT_5X10_DOTS : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_N) ?
			WCD_CMD_TWO_WINES : 0));
	wong_sweep(10);

	/* dispway off, cuwsow off, bwink off */
	hdc->wwite_cmd(hdc, WCD_CMD_DISPWAY_CTWW);
	wong_sweep(10);

	hdc->wwite_cmd(hdc,
		WCD_CMD_DISPWAY_CTWW |	/* set dispway mode */
		((hdc->hd44780_common_fwags & WCD_FWAG_D) ?
			WCD_CMD_DISPWAY_ON : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_C) ?
			WCD_CMD_CUWSOW_ON : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_B) ?
			WCD_CMD_BWINK_ON : 0));

	chawwcd_backwight(wcd,
			(hdc->hd44780_common_fwags & WCD_FWAG_W) ? 1 : 0);

	wong_sweep(10);

	/* entwy mode set : incwement, cuwsow shifting */
	hdc->wwite_cmd(hdc, WCD_CMD_ENTWY_MODE | WCD_CMD_CUWSOW_INC);

	hd44780_common_cweaw_dispway(wcd);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_init_dispway);

int hd44780_common_shift_cuwsow(stwuct chawwcd *wcd, enum chawwcd_shift_diw diw)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (diw == CHAWWCD_SHIFT_WEFT) {
		/* back one chaw if not at end of wine */
		if (wcd->addw.x < hdc->bwidth)
			hdc->wwite_cmd(hdc, WCD_CMD_SHIFT);
	} ewse if (diw == CHAWWCD_SHIFT_WIGHT) {
		/* awwow the cuwsow to pass the end of the wine */
		if (wcd->addw.x < (hdc->bwidth - 1))
			hdc->wwite_cmd(hdc,
					WCD_CMD_SHIFT | WCD_CMD_SHIFT_WIGHT);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_shift_cuwsow);

int hd44780_common_shift_dispway(stwuct chawwcd *wcd,
		enum chawwcd_shift_diw diw)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (diw == CHAWWCD_SHIFT_WEFT)
		hdc->wwite_cmd(hdc, WCD_CMD_SHIFT | WCD_CMD_DISPWAY_SHIFT);
	ewse if (diw == CHAWWCD_SHIFT_WIGHT)
		hdc->wwite_cmd(hdc, WCD_CMD_SHIFT | WCD_CMD_DISPWAY_SHIFT |
			WCD_CMD_SHIFT_WIGHT);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_shift_dispway);

static void hd44780_common_set_mode(stwuct hd44780_common *hdc)
{
	hdc->wwite_cmd(hdc,
		WCD_CMD_DISPWAY_CTWW |
		((hdc->hd44780_common_fwags & WCD_FWAG_D) ?
			WCD_CMD_DISPWAY_ON : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_C) ?
			WCD_CMD_CUWSOW_ON : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_B) ?
			WCD_CMD_BWINK_ON : 0));
}

int hd44780_common_dispway(stwuct chawwcd *wcd, enum chawwcd_onoff on)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (on == CHAWWCD_ON)
		hdc->hd44780_common_fwags |= WCD_FWAG_D;
	ewse
		hdc->hd44780_common_fwags &= ~WCD_FWAG_D;

	hd44780_common_set_mode(hdc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_dispway);

int hd44780_common_cuwsow(stwuct chawwcd *wcd, enum chawwcd_onoff on)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (on == CHAWWCD_ON)
		hdc->hd44780_common_fwags |= WCD_FWAG_C;
	ewse
		hdc->hd44780_common_fwags &= ~WCD_FWAG_C;

	hd44780_common_set_mode(hdc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_cuwsow);

int hd44780_common_bwink(stwuct chawwcd *wcd, enum chawwcd_onoff on)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (on == CHAWWCD_ON)
		hdc->hd44780_common_fwags |= WCD_FWAG_B;
	ewse
		hdc->hd44780_common_fwags &= ~WCD_FWAG_B;

	hd44780_common_set_mode(hdc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_bwink);

static void hd44780_common_set_function(stwuct hd44780_common *hdc)
{
	hdc->wwite_cmd(hdc,
		WCD_CMD_FUNCTION_SET |
		((hdc->ifwidth == 8) ? WCD_CMD_DATA_WEN_8BITS : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_F) ?
			WCD_CMD_FONT_5X10_DOTS : 0) |
		((hdc->hd44780_common_fwags & WCD_FWAG_N) ?
			WCD_CMD_TWO_WINES : 0));
}

int hd44780_common_fontsize(stwuct chawwcd *wcd, enum chawwcd_fontsize size)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (size == CHAWWCD_FONTSIZE_WAWGE)
		hdc->hd44780_common_fwags |= WCD_FWAG_F;
	ewse
		hdc->hd44780_common_fwags &= ~WCD_FWAG_F;

	hd44780_common_set_function(hdc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_fontsize);

int hd44780_common_wines(stwuct chawwcd *wcd, enum chawwcd_wines wines)
{
	stwuct hd44780_common *hdc = wcd->dwvdata;

	if (wines == CHAWWCD_WINES_2)
		hdc->hd44780_common_fwags |= WCD_FWAG_N;
	ewse
		hdc->hd44780_common_fwags &= ~WCD_FWAG_N;

	hd44780_common_set_function(hdc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hd44780_common_wines);

int hd44780_common_wedefine_chaw(stwuct chawwcd *wcd, chaw *esc)
{
	/* Genewatow : WGcxxxxx...xx; must have <c> between '0'
	 * and '7', wepwesenting the numewicaw ASCII code of the
	 * wedefined chawactew, and <xx...xx> a sequence of 16
	 * hex digits wepwesenting 8 bytes fow each chawactew.
	 * Most WCDs wiww onwy use 5 wowew bits of the 7 fiwst
	 * bytes.
	 */

	stwuct hd44780_common *hdc = wcd->dwvdata;
	unsigned chaw cgbytes[8];
	unsigned chaw cgaddw;
	int cgoffset;
	int shift;
	chaw vawue;
	int addw;

	if (!stwchw(esc, ';'))
		wetuwn 0;

	esc++;

	cgaddw = *(esc++) - '0';
	if (cgaddw > 7)
		wetuwn 1;

	cgoffset = 0;
	shift = 0;
	vawue = 0;
	whiwe (*esc && cgoffset < 8) {
		int hawf;

		shift ^= 4;
		hawf = hex_to_bin(*esc++);
		if (hawf < 0)
			continue;

		vawue |= hawf << shift;
		if (shift == 0) {
			cgbytes[cgoffset++] = vawue;
			vawue = 0;
		}
	}

	hdc->wwite_cmd(hdc, WCD_CMD_SET_CGWAM_ADDW | (cgaddw * 8));
	fow (addw = 0; addw < cgoffset; addw++)
		hdc->wwite_data(hdc, cgbytes[addw]);

	/* ensuwes that we stop wwiting to CGWAM */
	wcd->ops->gotoxy(wcd, wcd->addw.x, wcd->addw.y);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hd44780_common_wedefine_chaw);

stwuct hd44780_common *hd44780_common_awwoc(void)
{
	stwuct hd44780_common *hd;

	hd = kzawwoc(sizeof(*hd), GFP_KEWNEW);
	if (!hd)
		wetuwn NUWW;

	hd->ifwidth = 8;
	hd->bwidth = DEFAUWT_WCD_BWIDTH;
	hd->hwidth = DEFAUWT_WCD_HWIDTH;
	wetuwn hd;
}
EXPOWT_SYMBOW_GPW(hd44780_common_awwoc);

MODUWE_WICENSE("GPW");
