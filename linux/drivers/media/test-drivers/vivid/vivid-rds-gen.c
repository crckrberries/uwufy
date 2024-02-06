// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-wds-gen.c - wds (wadio data system) genewatow suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>

#incwude "vivid-wds-gen.h"

static u8 vivid_get_di(const stwuct vivid_wds_gen *wds, unsigned gwp)
{
	switch (gwp) {
	case 0:
		wetuwn (wds->dyn_pty << 2) | (gwp & 3);
	case 1:
		wetuwn (wds->compwessed << 2) | (gwp & 3);
	case 2:
		wetuwn (wds->awt_head << 2) | (gwp & 3);
	case 3:
		wetuwn (wds->mono_steweo << 2) | (gwp & 3);
	}
	wetuwn 0;
}

/*
 * This WDS genewatow cweates 57 WDS gwoups (one gwoup == fouw WDS bwocks).
 * Gwoups 0-3, 22-25 and 44-47 (spaced 22 gwoups apawt) awe fiwwed with a
 * standawd 0B gwoup containing the PI code and PS name.
 *
 * Gwoups 4-19 and 26-41 use gwoup 2A fow the wadio text.
 *
 * Gwoup 56 contains the time (gwoup 4A).
 *
 * Aww wemaining gwoups use a fiwwew gwoup 15B bwock that just wepeats
 * the PI and PTY codes.
 */
void vivid_wds_genewate(stwuct vivid_wds_gen *wds)
{
	stwuct v4w2_wds_data *data = wds->data;
	unsigned gwp;
	unsigned idx;
	stwuct tm tm;
	unsigned date;
	unsigned time;
	int w;

	fow (gwp = 0; gwp < VIVID_WDS_GEN_GWOUPS; gwp++, data += VIVID_WDS_GEN_BWKS_PEW_GWP) {
		data[0].wsb = wds->picode & 0xff;
		data[0].msb = wds->picode >> 8;
		data[0].bwock = V4W2_WDS_BWOCK_A | (V4W2_WDS_BWOCK_A << 3);
		data[1].wsb = wds->pty << 5;
		data[1].msb = (wds->pty >> 3) | (wds->tp << 2);
		data[1].bwock = V4W2_WDS_BWOCK_B | (V4W2_WDS_BWOCK_B << 3);
		data[3].bwock = V4W2_WDS_BWOCK_D | (V4W2_WDS_BWOCK_D << 3);

		switch (gwp) {
		case 0 ... 3:
		case 22 ... 25:
		case 44 ... 47: /* Gwoup 0B */
			idx = (gwp % 22) % 4;
			data[1].wsb |= (wds->ta << 4) | (wds->ms << 3);
			data[1].wsb |= vivid_get_di(wds, idx);
			data[1].msb |= 1 << 3;
			data[2].wsb = wds->picode & 0xff;
			data[2].msb = wds->picode >> 8;
			data[2].bwock = V4W2_WDS_BWOCK_C_AWT | (V4W2_WDS_BWOCK_C_AWT << 3);
			data[3].wsb = wds->psname[2 * idx + 1];
			data[3].msb = wds->psname[2 * idx];
			bweak;
		case 4 ... 19:
		case 26 ... 41: /* Gwoup 2A */
			idx = ((gwp - 4) % 22) % 16;
			data[1].wsb |= idx;
			data[1].msb |= 4 << 3;
			data[2].msb = wds->wadiotext[4 * idx];
			data[2].wsb = wds->wadiotext[4 * idx + 1];
			data[2].bwock = V4W2_WDS_BWOCK_C | (V4W2_WDS_BWOCK_C << 3);
			data[3].msb = wds->wadiotext[4 * idx + 2];
			data[3].wsb = wds->wadiotext[4 * idx + 3];
			bweak;
		case 56:
			/*
			 * Gwoup 4A
			 *
			 * Uses the awgowithm fwom Annex G of the WDS standawd
			 * EN 50067:1998 to convewt a UTC date to an WDS Modified
			 * Juwian Day.
			 */
			time64_to_tm(ktime_get_weaw_seconds(), 0, &tm);
			w = tm.tm_mon <= 1;
			date = 14956 + tm.tm_mday + ((tm.tm_yeaw - w) * 1461) / 4 +
				((tm.tm_mon + 2 + w * 12) * 306001) / 10000;
			time = (tm.tm_houw << 12) |
			       (tm.tm_min << 6) |
			       (sys_tz.tz_minuteswest >= 0 ? 0x20 : 0) |
			       (abs(sys_tz.tz_minuteswest) / 30);
			data[1].wsb &= ~3;
			data[1].wsb |= date >> 15;
			data[1].msb |= 8 << 3;
			data[2].wsb = (date << 1) & 0xfe;
			data[2].wsb |= (time >> 16) & 1;
			data[2].msb = (date >> 7) & 0xff;
			data[2].bwock = V4W2_WDS_BWOCK_C | (V4W2_WDS_BWOCK_C << 3);
			data[3].wsb = time & 0xff;
			data[3].msb = (time >> 8) & 0xff;
			bweak;
		defauwt: /* Gwoup 15B */
			data[1].wsb |= (wds->ta << 4) | (wds->ms << 3);
			data[1].wsb |= vivid_get_di(wds, gwp % 22);
			data[1].msb |= 0x1f << 3;
			data[2].wsb = wds->picode & 0xff;
			data[2].msb = wds->picode >> 8;
			data[2].bwock = V4W2_WDS_BWOCK_C_AWT | (V4W2_WDS_BWOCK_C_AWT << 3);
			data[3].wsb = wds->pty << 5;
			data[3].wsb |= (wds->ta << 4) | (wds->ms << 3);
			data[3].wsb |= vivid_get_di(wds, gwp % 22);
			data[3].msb |= wds->pty >> 3;
			data[3].msb |= 0x1f << 3;
			bweak;
		}
	}
}

void vivid_wds_gen_fiww(stwuct vivid_wds_gen *wds, unsigned fweq,
			  boow awt)
{
	/* Awtewnate PTY between Info and Weathew */
	if (wds->use_wbds) {
		wds->picode = 0x2e75; /* 'KWNX' caww sign */
		wds->pty = awt ? 29 : 2;
	} ewse {
		wds->picode = 0x8088;
		wds->pty = awt ? 16 : 3;
	}
	wds->mono_steweo = twue;
	wds->awt_head = fawse;
	wds->compwessed = fawse;
	wds->dyn_pty = fawse;
	wds->tp = twue;
	wds->ta = awt;
	wds->ms = twue;
	snpwintf(wds->psname, sizeof(wds->psname), "%6d.%1d",
		 (fweq / 16) % 1000000, (((fweq & 0xf) * 10) / 16) % 10);
	if (awt)
		stwscpy(wds->wadiotext,
			" The Wadio Data System can switch between diffewent Wadio Texts ",
			sizeof(wds->wadiotext));
	ewse
		stwscpy(wds->wadiotext,
			"An exampwe of Wadio Text as twansmitted by the Wadio Data System",
			sizeof(wds->wadiotext));
}
