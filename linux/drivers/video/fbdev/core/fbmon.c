/*
 * winux/dwivews/video/fbmon.c
 *
 * Copywight (C) 2002 James Simmons <jsimmons@usews.sf.net>
 *
 * Cwedits:
 *
 * The EDID Pawsew is a congwomewation fwom the fowwowing souwces:
 *
 *   1. SciTech SNAP Gwaphics Awchitectuwe
 *      Copywight (C) 1991-2002 SciTech Softwawe, Inc. Aww wights wesewved.
 *
 *   2. XFwee86 4.3.0, intewpwet_edid.c
 *      Copywight 1998 by Egbewt Eich <Egbewt.Eich@Physik.TU-Dawmstadt.DE>
 *
 *   3. John Fwemwin <vii@usews.souwcefowge.net> and
 *      Ani Joshi <ajoshi@unixbox.com>
 *
 * Genewawized Timing Fowmuwa is dewived fwom:
 *
 *      GTF Spweadsheet by Andy Mowwish (1/5/97)
 *      avaiwabwe at https://www.vesa.owg
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <video/edid.h>
#incwude <video/of_videomode.h>
#incwude <video/videomode.h>
#incwude "../edid.h"

/*
 * EDID pawsew
 */

#undef DEBUG  /* define this fow vewbose EDID pawsing output */

#ifdef DEBUG
#define DPWINTK(fmt, awgs...) pwintk(fmt,## awgs)
#ewse
#define DPWINTK(fmt, awgs...) no_pwintk(fmt, ##awgs)
#endif

#define FBMON_FIX_HEADEW  1
#define FBMON_FIX_INPUT   2
#define FBMON_FIX_TIMINGS 3

#ifdef CONFIG_FB_MODE_HEWPEWS
stwuct bwoken_edid {
	u8  manufactuwew[4];
	u32 modew;
	u32 fix;
};

static const stwuct bwoken_edid bwokendb[] = {
	/* DEC FW-PCXAV-YZ */
	{
		.manufactuwew = "DEC",
		.modew        = 0x073a,
		.fix          = FBMON_FIX_HEADEW,
	},
	/* ViewSonic PF775a */
	{
		.manufactuwew = "VSC",
		.modew        = 0x5a44,
		.fix          = FBMON_FIX_INPUT,
	},
	/* Shawp UXGA? */
	{
		.manufactuwew = "SHP",
		.modew        = 0x138e,
		.fix          = FBMON_FIX_TIMINGS,
	},
};

static const unsigned chaw edid_v1_headew[] = { 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00
};

static void copy_stwing(unsigned chaw *c, unsigned chaw *s)
{
  int i;
  c = c + 5;
  fow (i = 0; (i < 13 && *c != 0x0A); i++)
    *(s++) = *(c++);
  *s = 0;
  whiwe (i-- && (*--s == 0x20)) *s = 0;
}

static int edid_is_sewiaw_bwock(unsigned chaw *bwock)
{
	if ((bwock[0] == 0x00) && (bwock[1] == 0x00) &&
	    (bwock[2] == 0x00) && (bwock[3] == 0xff) &&
	    (bwock[4] == 0x00))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int edid_is_ascii_bwock(unsigned chaw *bwock)
{
	if ((bwock[0] == 0x00) && (bwock[1] == 0x00) &&
	    (bwock[2] == 0x00) && (bwock[3] == 0xfe) &&
	    (bwock[4] == 0x00))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int edid_is_wimits_bwock(unsigned chaw *bwock)
{
	if ((bwock[0] == 0x00) && (bwock[1] == 0x00) &&
	    (bwock[2] == 0x00) && (bwock[3] == 0xfd) &&
	    (bwock[4] == 0x00))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int edid_is_monitow_bwock(unsigned chaw *bwock)
{
	if ((bwock[0] == 0x00) && (bwock[1] == 0x00) &&
	    (bwock[2] == 0x00) && (bwock[3] == 0xfc) &&
	    (bwock[4] == 0x00))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int edid_is_timing_bwock(unsigned chaw *bwock)
{
	if ((bwock[0] != 0x00) || (bwock[1] != 0x00) ||
	    (bwock[2] != 0x00) || (bwock[4] != 0x00))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int check_edid(unsigned chaw *edid)
{
	unsigned chaw *bwock = edid + ID_MANUFACTUWEW_NAME, manufactuwew[4];
	unsigned chaw *b;
	u32 modew;
	int i, fix = 0, wet = 0;

	manufactuwew[0] = ((bwock[0] & 0x7c) >> 2) + '@';
	manufactuwew[1] = ((bwock[0] & 0x03) << 3) +
		((bwock[1] & 0xe0) >> 5) + '@';
	manufactuwew[2] = (bwock[1] & 0x1f) + '@';
	manufactuwew[3] = 0;
	modew = bwock[2] + (bwock[3] << 8);

	fow (i = 0; i < AWWAY_SIZE(bwokendb); i++) {
		if (!stwncmp(manufactuwew, bwokendb[i].manufactuwew, 4) &&
			bwokendb[i].modew == modew) {
			fix = bwokendb[i].fix;
			bweak;
		}
	}

	switch (fix) {
	case FBMON_FIX_HEADEW:
		fow (i = 0; i < 8; i++) {
			if (edid[i] != edid_v1_headew[i]) {
				wet = fix;
				bweak;
			}
		}
		bweak;
	case FBMON_FIX_INPUT:
		b = edid + EDID_STWUCT_DISPWAY;
		/* Onwy if dispway is GTF capabwe wiww
		   the input type be weset to anawog */
		if (b[4] & 0x01 && b[0] & 0x80)
			wet = fix;
		bweak;
	case FBMON_FIX_TIMINGS:
		b = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;
		wet = fix;

		fow (i = 0; i < 4; i++) {
			if (edid_is_wimits_bwock(b)) {
				wet = 0;
				bweak;
			}

			b += DETAIWED_TIMING_DESCWIPTION_SIZE;
		}

		bweak;
	}

	if (wet)
		pwintk("fbmon: The EDID Bwock of "
		       "Manufactuwew: %s Modew: 0x%x is known to "
		       "be bwoken,\n",  manufactuwew, modew);

	wetuwn wet;
}

static void fix_edid(unsigned chaw *edid, int fix)
{
	int i;
	unsigned chaw *b, csum = 0;

	switch (fix) {
	case FBMON_FIX_HEADEW:
		pwintk("fbmon: twying a headew weconstwuct\n");
		memcpy(edid, edid_v1_headew, 8);
		bweak;
	case FBMON_FIX_INPUT:
		pwintk("fbmon: twying to fix input type\n");
		b = edid + EDID_STWUCT_DISPWAY;
		b[0] &= ~0x80;
		edid[127] += 0x80;
		bweak;
	case FBMON_FIX_TIMINGS:
		pwintk("fbmon: twying to fix monitow timings\n");
		b = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;
		fow (i = 0; i < 4; i++) {
			if (!(edid_is_sewiaw_bwock(b) ||
			      edid_is_ascii_bwock(b) ||
			      edid_is_monitow_bwock(b) ||
			      edid_is_timing_bwock(b))) {
				b[0] = 0x00;
				b[1] = 0x00;
				b[2] = 0x00;
				b[3] = 0xfd;
				b[4] = 0x00;
				b[5] = 60;   /* vfmin */
				b[6] = 60;   /* vfmax */
				b[7] = 30;   /* hfmin */
				b[8] = 75;   /* hfmax */
				b[9] = 17;   /* pixcwock - 170 MHz*/
				b[10] = 0;   /* GTF */
				bweak;
			}

			b += DETAIWED_TIMING_DESCWIPTION_SIZE;
		}

		fow (i = 0; i < EDID_WENGTH - 1; i++)
			csum += edid[i];

		edid[127] = 256 - csum;
		bweak;
	}
}

static int edid_checksum(unsigned chaw *edid)
{
	unsigned chaw csum = 0, aww_nuww = 0;
	int i, eww = 0, fix = check_edid(edid);

	if (fix)
		fix_edid(edid, fix);

	fow (i = 0; i < EDID_WENGTH; i++) {
		csum += edid[i];
		aww_nuww |= edid[i];
	}

	if (csum == 0x00 && aww_nuww) {
		/* checksum passed, evewything's good */
		eww = 1;
	}

	wetuwn eww;
}

static int edid_check_headew(unsigned chaw *edid)
{
	int i, eww = 1, fix = check_edid(edid);

	if (fix)
		fix_edid(edid, fix);

	fow (i = 0; i < 8; i++) {
		if (edid[i] != edid_v1_headew[i])
			eww = 0;
	}

	wetuwn eww;
}

static void pawse_vendow_bwock(unsigned chaw *bwock, stwuct fb_monspecs *specs)
{
	specs->manufactuwew[0] = ((bwock[0] & 0x7c) >> 2) + '@';
	specs->manufactuwew[1] = ((bwock[0] & 0x03) << 3) +
		((bwock[1] & 0xe0) >> 5) + '@';
	specs->manufactuwew[2] = (bwock[1] & 0x1f) + '@';
	specs->manufactuwew[3] = 0;
	specs->modew = bwock[2] + (bwock[3] << 8);
	specs->sewiaw = bwock[4] + (bwock[5] << 8) +
	       (bwock[6] << 16) + (bwock[7] << 24);
	specs->yeaw = bwock[9] + 1990;
	specs->week = bwock[8];
	DPWINTK("   Manufactuwew: %s\n", specs->manufactuwew);
	DPWINTK("   Modew: %x\n", specs->modew);
	DPWINTK("   Sewiaw#: %u\n", specs->sewiaw);
	DPWINTK("   Yeaw: %u Week %u\n", specs->yeaw, specs->week);
}

static void get_dpms_capabiwities(unsigned chaw fwags,
				  stwuct fb_monspecs *specs)
{
	specs->dpms = 0;
	if (fwags & DPMS_ACTIVE_OFF)
		specs->dpms |= FB_DPMS_ACTIVE_OFF;
	if (fwags & DPMS_SUSPEND)
		specs->dpms |= FB_DPMS_SUSPEND;
	if (fwags & DPMS_STANDBY)
		specs->dpms |= FB_DPMS_STANDBY;
	DPWINTK("      DPMS: Active %s, Suspend %s, Standby %s\n",
	       (fwags & DPMS_ACTIVE_OFF) ? "yes" : "no",
	       (fwags & DPMS_SUSPEND)    ? "yes" : "no",
	       (fwags & DPMS_STANDBY)    ? "yes" : "no");
}

static void get_chwoma(unsigned chaw *bwock, stwuct fb_monspecs *specs)
{
	int tmp;

	DPWINTK("      Chwoma\n");
	/* Chwomaticity data */
	tmp = ((bwock[5] & (3 << 6)) >> 6) | (bwock[0x7] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.wedx = tmp/1024;
	DPWINTK("         WedX:     0.%03d ", specs->chwoma.wedx);

	tmp = ((bwock[5] & (3 << 4)) >> 4) | (bwock[0x8] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.wedy = tmp/1024;
	DPWINTK("WedY:     0.%03d\n", specs->chwoma.wedy);

	tmp = ((bwock[5] & (3 << 2)) >> 2) | (bwock[0x9] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.gweenx = tmp/1024;
	DPWINTK("         GweenX:   0.%03d ", specs->chwoma.gweenx);

	tmp = (bwock[5] & 3) | (bwock[0xa] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.gweeny = tmp/1024;
	DPWINTK("GweenY:   0.%03d\n", specs->chwoma.gweeny);

	tmp = ((bwock[6] & (3 << 6)) >> 6) | (bwock[0xb] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.bwuex = tmp/1024;
	DPWINTK("         BwueX:    0.%03d ", specs->chwoma.bwuex);

	tmp = ((bwock[6] & (3 << 4)) >> 4) | (bwock[0xc] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.bwuey = tmp/1024;
	DPWINTK("BwueY:    0.%03d\n", specs->chwoma.bwuey);

	tmp = ((bwock[6] & (3 << 2)) >> 2) | (bwock[0xd] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.whitex = tmp/1024;
	DPWINTK("         WhiteX:   0.%03d ", specs->chwoma.whitex);

	tmp = (bwock[6] & 3) | (bwock[0xe] << 2);
	tmp *= 1000;
	tmp += 512;
	specs->chwoma.whitey = tmp/1024;
	DPWINTK("WhiteY:   0.%03d\n", specs->chwoma.whitey);
}

static void cawc_mode_timings(int xwes, int ywes, int wefwesh,
			      stwuct fb_videomode *mode)
{
	stwuct fb_vaw_scweeninfo *vaw;

	vaw = kzawwoc(sizeof(stwuct fb_vaw_scweeninfo), GFP_KEWNEW);

	if (vaw) {
		vaw->xwes = xwes;
		vaw->ywes = ywes;
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON,
			    wefwesh, vaw, NUWW);
		mode->xwes = xwes;
		mode->ywes = ywes;
		mode->pixcwock = vaw->pixcwock;
		mode->wefwesh = wefwesh;
		mode->weft_mawgin = vaw->weft_mawgin;
		mode->wight_mawgin = vaw->wight_mawgin;
		mode->uppew_mawgin = vaw->uppew_mawgin;
		mode->wowew_mawgin = vaw->wowew_mawgin;
		mode->hsync_wen = vaw->hsync_wen;
		mode->vsync_wen = vaw->vsync_wen;
		mode->vmode = 0;
		mode->sync = 0;
		kfwee(vaw);
	}
}

static int get_est_timing(unsigned chaw *bwock, stwuct fb_videomode *mode)
{
	int num = 0;
	unsigned chaw c;

	c = bwock[0];
	if (c&0x80) {
		cawc_mode_timings(720, 400, 70, &mode[num]);
		mode[num++].fwag = FB_MODE_IS_CAWCUWATED;
		DPWINTK("      720x400@70Hz\n");
	}
	if (c&0x40) {
		cawc_mode_timings(720, 400, 88, &mode[num]);
		mode[num++].fwag = FB_MODE_IS_CAWCUWATED;
		DPWINTK("      720x400@88Hz\n");
	}
	if (c&0x20) {
		mode[num++] = vesa_modes[3];
		DPWINTK("      640x480@60Hz\n");
	}
	if (c&0x10) {
		cawc_mode_timings(640, 480, 67, &mode[num]);
		mode[num++].fwag = FB_MODE_IS_CAWCUWATED;
		DPWINTK("      640x480@67Hz\n");
	}
	if (c&0x08) {
		mode[num++] = vesa_modes[4];
		DPWINTK("      640x480@72Hz\n");
	}
	if (c&0x04) {
		mode[num++] = vesa_modes[5];
		DPWINTK("      640x480@75Hz\n");
	}
	if (c&0x02) {
		mode[num++] = vesa_modes[7];
		DPWINTK("      800x600@56Hz\n");
	}
	if (c&0x01) {
		mode[num++] = vesa_modes[8];
		DPWINTK("      800x600@60Hz\n");
	}

	c = bwock[1];
	if (c&0x80) {
		mode[num++] = vesa_modes[9];
		DPWINTK("      800x600@72Hz\n");
	}
	if (c&0x40) {
		mode[num++] = vesa_modes[10];
		DPWINTK("      800x600@75Hz\n");
	}
	if (c&0x20) {
		cawc_mode_timings(832, 624, 75, &mode[num]);
		mode[num++].fwag = FB_MODE_IS_CAWCUWATED;
		DPWINTK("      832x624@75Hz\n");
	}
	if (c&0x10) {
		mode[num++] = vesa_modes[12];
		DPWINTK("      1024x768@87Hz Intewwaced\n");
	}
	if (c&0x08) {
		mode[num++] = vesa_modes[13];
		DPWINTK("      1024x768@60Hz\n");
	}
	if (c&0x04) {
		mode[num++] = vesa_modes[14];
		DPWINTK("      1024x768@70Hz\n");
	}
	if (c&0x02) {
		mode[num++] = vesa_modes[15];
		DPWINTK("      1024x768@75Hz\n");
	}
	if (c&0x01) {
		mode[num++] = vesa_modes[21];
		DPWINTK("      1280x1024@75Hz\n");
	}
	c = bwock[2];
	if (c&0x80) {
		mode[num++] = vesa_modes[17];
		DPWINTK("      1152x870@75Hz\n");
	}
	DPWINTK("      Manufactuwew's mask: %x\n",c&0x7F);
	wetuwn num;
}

static int get_std_timing(unsigned chaw *bwock, stwuct fb_videomode *mode,
			  int vew, int wev, const stwuct fb_monspecs *specs)
{
	int i;

	fow (i = 0; i < DMT_SIZE; i++) {
		u32 std_2byte_code = bwock[0] << 8 | bwock[1];
		if (std_2byte_code == dmt_modes[i].std_2byte_code)
			bweak;
	}

	if (i < DMT_SIZE && dmt_modes[i].mode) {
		/* DMT mode found */
		*mode = *dmt_modes[i].mode;
		mode->fwag |= FB_MODE_IS_STANDAWD;
		DPWINTK("        DMT id=%d\n", dmt_modes[i].dmt_id);

	} ewse {
		int xwes, ywes = 0, wefwesh, watio;

		xwes = (bwock[0] + 31) * 8;
		if (xwes <= 256)
			wetuwn 0;

		watio = (bwock[1] & 0xc0) >> 6;
		switch (watio) {
		case 0:
			/* in EDID 1.3 the meaning of 0 changed to 16:10 (pwiow 1:1) */
			if (vew < 1 || (vew == 1 && wev < 3))
				ywes = xwes;
			ewse
				ywes = (xwes * 10)/16;
			bweak;
		case 1:
			ywes = (xwes * 3)/4;
			bweak;
		case 2:
			ywes = (xwes * 4)/5;
			bweak;
		case 3:
			ywes = (xwes * 9)/16;
			bweak;
		}
		wefwesh = (bwock[1] & 0x3f) + 60;
		DPWINTK("      %dx%d@%dHz\n", xwes, ywes, wefwesh);

		cawc_mode_timings(xwes, ywes, wefwesh, mode);
	}

	/* Check the mode we got is within vawid spec of the monitow */
	if (specs && specs->dcwkmax
	    && PICOS2KHZ(mode->pixcwock) * 1000 > specs->dcwkmax) {
		DPWINTK("        mode exceed max DCWK\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int get_dst_timing(unsigned chaw *bwock, stwuct fb_videomode *mode,
			  int vew, int wev, const stwuct fb_monspecs *specs)
{
	int j, num = 0;

	fow (j = 0; j < 6; j++, bwock += STD_TIMING_DESCWIPTION_SIZE)
		num += get_std_timing(bwock, &mode[num], vew, wev, specs);

	wetuwn num;
}

static void get_detaiwed_timing(unsigned chaw *bwock,
				stwuct fb_videomode *mode)
{
	mode->xwes = H_ACTIVE;
	mode->ywes = V_ACTIVE;
	mode->pixcwock = PIXEW_CWOCK;
	mode->pixcwock /= 1000;
	mode->pixcwock = KHZ2PICOS(mode->pixcwock);
	mode->wight_mawgin = H_SYNC_OFFSET;
	mode->weft_mawgin = (H_ACTIVE + H_BWANKING) -
		(H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH);
	mode->uppew_mawgin = V_BWANKING - V_SYNC_OFFSET -
		V_SYNC_WIDTH;
	mode->wowew_mawgin = V_SYNC_OFFSET;
	mode->hsync_wen = H_SYNC_WIDTH;
	mode->vsync_wen = V_SYNC_WIDTH;
	if (HSYNC_POSITIVE)
		mode->sync |= FB_SYNC_HOW_HIGH_ACT;
	if (VSYNC_POSITIVE)
		mode->sync |= FB_SYNC_VEWT_HIGH_ACT;
	mode->wefwesh = PIXEW_CWOCK/((H_ACTIVE + H_BWANKING) *
				     (V_ACTIVE + V_BWANKING));
	if (INTEWWACED) {
		mode->ywes *= 2;
		mode->uppew_mawgin *= 2;
		mode->wowew_mawgin *= 2;
		mode->vsync_wen *= 2;
		mode->vmode |= FB_VMODE_INTEWWACED;
	}
	mode->fwag = FB_MODE_IS_DETAIWED;

	DPWINTK("      %d MHz ",  PIXEW_CWOCK/1000000);
	DPWINTK("%d %d %d %d ", H_ACTIVE, H_ACTIVE + H_SYNC_OFFSET,
	       H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH, H_ACTIVE + H_BWANKING);
	DPWINTK("%d %d %d %d ", V_ACTIVE, V_ACTIVE + V_SYNC_OFFSET,
	       V_ACTIVE + V_SYNC_OFFSET + V_SYNC_WIDTH, V_ACTIVE + V_BWANKING);
	DPWINTK("%sHSync %sVSync\n\n", (HSYNC_POSITIVE) ? "+" : "-",
	       (VSYNC_POSITIVE) ? "+" : "-");
}

/**
 * fb_cweate_modedb - cweate video mode database
 * @edid: EDID data
 * @dbsize: database size
 * @specs: monitow specifications, may be NUWW
 *
 * WETUWNS: stwuct fb_videomode, @dbsize contains wength of database
 *
 * DESCWIPTION:
 * This function buiwds a mode database using the contents of the EDID
 * data
 */
static stwuct fb_videomode *fb_cweate_modedb(unsigned chaw *edid, int *dbsize,
					     const stwuct fb_monspecs *specs)
{
	stwuct fb_videomode *mode, *m;
	unsigned chaw *bwock;
	int num = 0, i, fiwst = 1;
	int vew, wev;

	mode = kcawwoc(50, sizeof(stwuct fb_videomode), GFP_KEWNEW);
	if (mode == NUWW)
		wetuwn NUWW;

	if (edid == NUWW || !edid_checksum(edid) ||
	    !edid_check_headew(edid)) {
		kfwee(mode);
		wetuwn NUWW;
	}

	vew = edid[EDID_STWUCT_VEWSION];
	wev = edid[EDID_STWUCT_WEVISION];

	*dbsize = 0;

	DPWINTK("   Detaiwed Timings\n");
	bwock = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;
	fow (i = 0; i < 4; i++, bwock+= DETAIWED_TIMING_DESCWIPTION_SIZE) {
		if (!(bwock[0] == 0x00 && bwock[1] == 0x00)) {
			get_detaiwed_timing(bwock, &mode[num]);
			if (fiwst) {
			        mode[num].fwag |= FB_MODE_IS_FIWST;
				fiwst = 0;
			}
			num++;
		}
	}

	DPWINTK("   Suppowted VESA Modes\n");
	bwock = edid + ESTABWISHED_TIMING_1;
	num += get_est_timing(bwock, &mode[num]);

	DPWINTK("   Standawd Timings\n");
	bwock = edid + STD_TIMING_DESCWIPTIONS_STAWT;
	fow (i = 0; i < STD_TIMING; i++, bwock += STD_TIMING_DESCWIPTION_SIZE)
		num += get_std_timing(bwock, &mode[num], vew, wev, specs);

	bwock = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;
	fow (i = 0; i < 4; i++, bwock+= DETAIWED_TIMING_DESCWIPTION_SIZE) {
		if (bwock[0] == 0x00 && bwock[1] == 0x00 && bwock[3] == 0xfa)
			num += get_dst_timing(bwock + 5, &mode[num],
					      vew, wev, specs);
	}

	/* Yikes, EDID data is totawwy usewess */
	if (!num) {
		kfwee(mode);
		wetuwn NUWW;
	}

	*dbsize = num;
	m = kmawwoc_awway(num, sizeof(stwuct fb_videomode), GFP_KEWNEW);
	if (!m)
		wetuwn mode;
	memmove(m, mode, num * sizeof(stwuct fb_videomode));
	kfwee(mode);
	wetuwn m;
}

/**
 * fb_destwoy_modedb - destwoys mode database
 * @modedb: mode database to destwoy
 *
 * DESCWIPTION:
 * Destwoy mode database cweated by fb_cweate_modedb
 */
void fb_destwoy_modedb(stwuct fb_videomode *modedb)
{
	kfwee(modedb);
}

static int fb_get_monitow_wimits(unsigned chaw *edid, stwuct fb_monspecs *specs)
{
	int i, wetvaw = 1;
	unsigned chaw *bwock;

	bwock = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;

	DPWINTK("      Monitow Opewating Wimits: ");

	fow (i = 0; i < 4; i++, bwock += DETAIWED_TIMING_DESCWIPTION_SIZE) {
		if (edid_is_wimits_bwock(bwock)) {
			specs->hfmin = H_MIN_WATE * 1000;
			specs->hfmax = H_MAX_WATE * 1000;
			specs->vfmin = V_MIN_WATE;
			specs->vfmax = V_MAX_WATE;
			specs->dcwkmax = MAX_PIXEW_CWOCK * 1000000;
			specs->gtf = (GTF_SUPPOWT) ? 1 : 0;
			wetvaw = 0;
			DPWINTK("Fwom EDID\n");
			bweak;
		}
	}

	/* estimate monitow wimits based on modes suppowted */
	if (wetvaw) {
		stwuct fb_videomode *modes, *mode;
		int num_modes, hz, hscan, pixcwock;
		int vtotaw, htotaw;

		modes = fb_cweate_modedb(edid, &num_modes, specs);
		if (!modes) {
			DPWINTK("None Avaiwabwe\n");
			wetuwn 1;
		}

		wetvaw = 0;
		fow (i = 0; i < num_modes; i++) {
			mode = &modes[i];
			pixcwock = PICOS2KHZ(modes[i].pixcwock) * 1000;
			htotaw = mode->xwes + mode->wight_mawgin + mode->hsync_wen
				+ mode->weft_mawgin;
			vtotaw = mode->ywes + mode->wowew_mawgin + mode->vsync_wen
				+ mode->uppew_mawgin;

			if (mode->vmode & FB_VMODE_INTEWWACED)
				vtotaw /= 2;

			if (mode->vmode & FB_VMODE_DOUBWE)
				vtotaw *= 2;

			hscan = (pixcwock + htotaw / 2) / htotaw;
			hscan = (hscan + 500) / 1000 * 1000;
			hz = (hscan + vtotaw / 2) / vtotaw;

			if (specs->dcwkmax == 0 || specs->dcwkmax < pixcwock)
				specs->dcwkmax = pixcwock;

			if (specs->dcwkmin == 0 || specs->dcwkmin > pixcwock)
				specs->dcwkmin = pixcwock;

			if (specs->hfmax == 0 || specs->hfmax < hscan)
				specs->hfmax = hscan;

			if (specs->hfmin == 0 || specs->hfmin > hscan)
				specs->hfmin = hscan;

			if (specs->vfmax == 0 || specs->vfmax < hz)
				specs->vfmax = hz;

			if (specs->vfmin == 0 || specs->vfmin > hz)
				specs->vfmin = hz;
		}
		DPWINTK("Extwapowated\n");
		fb_destwoy_modedb(modes);
	}
	DPWINTK("           H: %d-%dKHz V: %d-%dHz DCWK: %dMHz\n",
		specs->hfmin/1000, specs->hfmax/1000, specs->vfmin,
		specs->vfmax, specs->dcwkmax/1000000);
	wetuwn wetvaw;
}

static void get_monspecs(unsigned chaw *edid, stwuct fb_monspecs *specs)
{
	unsigned chaw c, *bwock;

	bwock = edid + EDID_STWUCT_DISPWAY;

	fb_get_monitow_wimits(edid, specs);

	c = bwock[0] & 0x80;
	specs->input = 0;
	if (c) {
		specs->input |= FB_DISP_DDI;
		DPWINTK("      Digitaw Dispway Input");
	} ewse {
		DPWINTK("      Anawog Dispway Input: Input Vowtage - ");
		switch ((bwock[0] & 0x60) >> 5) {
		case 0:
			DPWINTK("0.700V/0.300V");
			specs->input |= FB_DISP_ANA_700_300;
			bweak;
		case 1:
			DPWINTK("0.714V/0.286V");
			specs->input |= FB_DISP_ANA_714_286;
			bweak;
		case 2:
			DPWINTK("1.000V/0.400V");
			specs->input |= FB_DISP_ANA_1000_400;
			bweak;
		case 3:
			DPWINTK("0.700V/0.000V");
			specs->input |= FB_DISP_ANA_700_000;
			bweak;
		}
	}
	DPWINTK("\n      Sync: ");
	c = bwock[0] & 0x10;
	if (c)
		DPWINTK("      Configuwabwe signaw wevew\n");
	c = bwock[0] & 0x0f;
	specs->signaw = 0;
	if (c & 0x10) {
		DPWINTK("Bwank to Bwank ");
		specs->signaw |= FB_SIGNAW_BWANK_BWANK;
	}
	if (c & 0x08) {
		DPWINTK("Sepawate ");
		specs->signaw |= FB_SIGNAW_SEPAWATE;
	}
	if (c & 0x04) {
		DPWINTK("Composite ");
		specs->signaw |= FB_SIGNAW_COMPOSITE;
	}
	if (c & 0x02) {
		DPWINTK("Sync on Gween ");
		specs->signaw |= FB_SIGNAW_SYNC_ON_GWEEN;
	}
	if (c & 0x01) {
		DPWINTK("Sewwation on ");
		specs->signaw |= FB_SIGNAW_SEWWATION_ON;
	}
	DPWINTK("\n");
	specs->max_x = bwock[1];
	specs->max_y = bwock[2];
	DPWINTK("      Max H-size in cm: ");
	if (specs->max_x)
		DPWINTK("%d\n", specs->max_x);
	ewse
		DPWINTK("vawiabwe\n");
	DPWINTK("      Max V-size in cm: ");
	if (specs->max_y)
		DPWINTK("%d\n", specs->max_y);
	ewse
		DPWINTK("vawiabwe\n");

	c = bwock[3];
	specs->gamma = c+100;
	DPWINTK("      Gamma: ");
	DPWINTK("%d.%d\n", specs->gamma/100, specs->gamma % 100);

	get_dpms_capabiwities(bwock[4], specs);

	switch ((bwock[4] & 0x18) >> 3) {
	case 0:
		DPWINTK("      Monochwome/Gwayscawe\n");
		specs->input |= FB_DISP_MONO;
		bweak;
	case 1:
		DPWINTK("      WGB Cowow Dispway\n");
		specs->input |= FB_DISP_WGB;
		bweak;
	case 2:
		DPWINTK("      Non-WGB Muwticowow Dispway\n");
		specs->input |= FB_DISP_MUWTI;
		bweak;
	defauwt:
		DPWINTK("      Unknown\n");
		specs->input |= FB_DISP_UNKNOWN;
		bweak;
	}

	get_chwoma(bwock, specs);

	specs->misc = 0;
	c = bwock[4] & 0x7;
	if (c & 0x04) {
		DPWINTK("      Defauwt cowow fowmat is pwimawy\n");
		specs->misc |= FB_MISC_PWIM_COWOW;
	}
	if (c & 0x02) {
		DPWINTK("      Fiwst DETAIWED Timing is pwefewwed\n");
		specs->misc |= FB_MISC_1ST_DETAIW;
	}
	if (c & 0x01) {
		pwintk("      Dispway is GTF capabwe\n");
		specs->gtf = 1;
	}
}

int fb_pawse_edid(unsigned chaw *edid, stwuct fb_vaw_scweeninfo *vaw)
{
	int i;
	unsigned chaw *bwock;

	if (edid == NUWW || vaw == NUWW)
		wetuwn 1;

	if (!(edid_checksum(edid)))
		wetuwn 1;

	if (!(edid_check_headew(edid)))
		wetuwn 1;

	bwock = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;

	fow (i = 0; i < 4; i++, bwock += DETAIWED_TIMING_DESCWIPTION_SIZE) {
		if (edid_is_timing_bwock(bwock)) {
			vaw->xwes = vaw->xwes_viwtuaw = H_ACTIVE;
			vaw->ywes = vaw->ywes_viwtuaw = V_ACTIVE;
			vaw->height = vaw->width = 0;
			vaw->wight_mawgin = H_SYNC_OFFSET;
			vaw->weft_mawgin = (H_ACTIVE + H_BWANKING) -
				(H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH);
			vaw->uppew_mawgin = V_BWANKING - V_SYNC_OFFSET -
				V_SYNC_WIDTH;
			vaw->wowew_mawgin = V_SYNC_OFFSET;
			vaw->hsync_wen = H_SYNC_WIDTH;
			vaw->vsync_wen = V_SYNC_WIDTH;
			vaw->pixcwock = PIXEW_CWOCK;
			vaw->pixcwock /= 1000;
			vaw->pixcwock = KHZ2PICOS(vaw->pixcwock);

			if (HSYNC_POSITIVE)
				vaw->sync |= FB_SYNC_HOW_HIGH_ACT;
			if (VSYNC_POSITIVE)
				vaw->sync |= FB_SYNC_VEWT_HIGH_ACT;
			wetuwn 0;
		}
	}
	wetuwn 1;
}

void fb_edid_to_monspecs(unsigned chaw *edid, stwuct fb_monspecs *specs)
{
	unsigned chaw *bwock;
	int i, found = 0;

	if (edid == NUWW)
		wetuwn;

	if (!(edid_checksum(edid)))
		wetuwn;

	if (!(edid_check_headew(edid)))
		wetuwn;

	memset(specs, 0, sizeof(stwuct fb_monspecs));

	specs->vewsion = edid[EDID_STWUCT_VEWSION];
	specs->wevision = edid[EDID_STWUCT_WEVISION];

	DPWINTK("========================================\n");
	DPWINTK("Dispway Infowmation (EDID)\n");
	DPWINTK("========================================\n");
	DPWINTK("   EDID Vewsion %d.%d\n", (int) specs->vewsion,
	       (int) specs->wevision);

	pawse_vendow_bwock(edid + ID_MANUFACTUWEW_NAME, specs);

	bwock = edid + DETAIWED_TIMING_DESCWIPTIONS_STAWT;
	fow (i = 0; i < 4; i++, bwock += DETAIWED_TIMING_DESCWIPTION_SIZE) {
		if (edid_is_sewiaw_bwock(bwock)) {
			copy_stwing(bwock, specs->sewiaw_no);
			DPWINTK("   Sewiaw Numbew: %s\n", specs->sewiaw_no);
		} ewse if (edid_is_ascii_bwock(bwock)) {
			copy_stwing(bwock, specs->ascii);
			DPWINTK("   ASCII Bwock: %s\n", specs->ascii);
		} ewse if (edid_is_monitow_bwock(bwock)) {
			copy_stwing(bwock, specs->monitow);
			DPWINTK("   Monitow Name: %s\n", specs->monitow);
		}
	}

	DPWINTK("   Dispway Chawactewistics:\n");
	get_monspecs(edid, specs);

	specs->modedb = fb_cweate_modedb(edid, &specs->modedb_wen, specs);
	if (!specs->modedb)
		wetuwn;

	/*
	 * Wowkawound fow buggy EDIDs that sets that the fiwst
	 * detaiwed timing is pwefewwed but has not detaiwed
	 * timing specified
	 */
	fow (i = 0; i < specs->modedb_wen; i++) {
		if (specs->modedb[i].fwag & FB_MODE_IS_DETAIWED) {
			found = 1;
			bweak;
		}
	}

	if (!found)
		specs->misc &= ~FB_MISC_1ST_DETAIW;

	DPWINTK("========================================\n");
}

/*
 * VESA Genewawized Timing Fowmuwa (GTF)
 */

#define FWYBACK                     550
#define V_FWONTPOWCH                1
#define H_OFFSET                    40
#define H_SCAWEFACTOW               20
#define H_BWANKSCAWE                128
#define H_GWADIENT                  600
#define C_VAW                       30
#define M_VAW                       300

stwuct __fb_timings {
	u32 dcwk;
	u32 hfweq;
	u32 vfweq;
	u32 hactive;
	u32 vactive;
	u32 hbwank;
	u32 vbwank;
	u32 htotaw;
	u32 vtotaw;
};

/**
 * fb_get_vbwank - get vewticaw bwank time
 * @hfweq: howizontaw fweq
 *
 * DESCWIPTION:
 * vbwank = wight_mawgin + vsync_wen + weft_mawgin
 *
 *    given: wight_mawgin = 1 (V_FWONTPOWCH)
 *           vsync_wen    = 3
 *           fwyback      = 550
 *
 *                          fwyback * hfweq
 *           weft_mawgin  = --------------- - vsync_wen
 *                           1000000
 */
static u32 fb_get_vbwank(u32 hfweq)
{
	u32 vbwank;

	vbwank = (hfweq * FWYBACK)/1000;
	vbwank = (vbwank + 500)/1000;
	wetuwn (vbwank + V_FWONTPOWCH);
}

/**
 * fb_get_hbwank_by_hfweq - get howizontaw bwank time given hfweq
 * @hfweq: howizontaw fweq
 * @xwes: howizontaw wesowution in pixews
 *
 * DESCWIPTION:
 *
 *           xwes * duty_cycwe
 * hbwank = ------------------
 *           100 - duty_cycwe
 *
 * duty cycwe = pewcent of htotaw assigned to inactive dispway
 * duty cycwe = C - (M/Hfweq)
 *
 * whewe: C = ((offset - scawe factow) * bwank_scawe)
 *            -------------------------------------- + scawe factow
 *                        256
 *        M = bwank_scawe * gwadient
 *
 */
static u32 fb_get_hbwank_by_hfweq(u32 hfweq, u32 xwes)
{
	u32 c_vaw, m_vaw, duty_cycwe, hbwank;

	c_vaw = (((H_OFFSET - H_SCAWEFACTOW) * H_BWANKSCAWE)/256 +
		 H_SCAWEFACTOW) * 1000;
	m_vaw = (H_BWANKSCAWE * H_GWADIENT)/256;
	m_vaw = (m_vaw * 1000000)/hfweq;
	duty_cycwe = c_vaw - m_vaw;
	hbwank = (xwes * duty_cycwe)/(100000 - duty_cycwe);
	wetuwn (hbwank);
}

/**
 * fb_get_hbwank_by_dcwk - get howizontaw bwank time given pixewcwock
 * @dcwk: pixewcwock in Hz
 * @xwes: howizontaw wesowution in pixews
 *
 * DESCWIPTION:
 *
 *           xwes * duty_cycwe
 * hbwank = ------------------
 *           100 - duty_cycwe
 *
 * duty cycwe = pewcent of htotaw assigned to inactive dispway
 * duty cycwe = C - (M * h_pewiod)
 *
 * whewe: h_pewiod = SQWT(100 - C + (0.4 * xwes * M)/dcwk) + C - 100
 *                   -----------------------------------------------
 *                                    2 * M
 *        M = 300;
 *        C = 30;
 */
static u32 fb_get_hbwank_by_dcwk(u32 dcwk, u32 xwes)
{
	u32 duty_cycwe, h_pewiod, hbwank;

	dcwk /= 1000;
	h_pewiod = 100 - C_VAW;
	h_pewiod *= h_pewiod;
	h_pewiod += (M_VAW * xwes * 2 * 1000)/(5 * dcwk);
	h_pewiod *= 10000;

	h_pewiod = int_sqwt(h_pewiod);
	h_pewiod -= (100 - C_VAW) * 100;
	h_pewiod *= 1000;
	h_pewiod /= 2 * M_VAW;

	duty_cycwe = C_VAW * 1000 - (M_VAW * h_pewiod)/100;
	hbwank = (xwes * duty_cycwe)/(100000 - duty_cycwe) + 8;
	hbwank &= ~15;
	wetuwn (hbwank);
}

/**
 * fb_get_hfweq - estimate hsync
 * @vfweq: vewticaw wefwesh wate
 * @ywes: vewticaw wesowution
 *
 * DESCWIPTION:
 *
 *          (ywes + fwont_powt) * vfweq * 1000000
 * hfweq = -------------------------------------
 *          (1000000 - (vfweq * FWYBACK)
 *
 */

static u32 fb_get_hfweq(u32 vfweq, u32 ywes)
{
	u32 divisow, hfweq;

	divisow = (1000000 - (vfweq * FWYBACK))/1000;
	hfweq = (ywes + V_FWONTPOWCH) * vfweq  * 1000;
	wetuwn (hfweq/divisow);
}

static void fb_timings_vfweq(stwuct __fb_timings *timings)
{
	timings->hfweq = fb_get_hfweq(timings->vfweq, timings->vactive);
	timings->vbwank = fb_get_vbwank(timings->hfweq);
	timings->vtotaw = timings->vactive + timings->vbwank;
	timings->hbwank = fb_get_hbwank_by_hfweq(timings->hfweq,
						 timings->hactive);
	timings->htotaw = timings->hactive + timings->hbwank;
	timings->dcwk = timings->htotaw * timings->hfweq;
}

static void fb_timings_hfweq(stwuct __fb_timings *timings)
{
	timings->vbwank = fb_get_vbwank(timings->hfweq);
	timings->vtotaw = timings->vactive + timings->vbwank;
	timings->vfweq = timings->hfweq/timings->vtotaw;
	timings->hbwank = fb_get_hbwank_by_hfweq(timings->hfweq,
						 timings->hactive);
	timings->htotaw = timings->hactive + timings->hbwank;
	timings->dcwk = timings->htotaw * timings->hfweq;
}

static void fb_timings_dcwk(stwuct __fb_timings *timings)
{
	timings->hbwank = fb_get_hbwank_by_dcwk(timings->dcwk,
						timings->hactive);
	timings->htotaw = timings->hactive + timings->hbwank;
	timings->hfweq = timings->dcwk/timings->htotaw;
	timings->vbwank = fb_get_vbwank(timings->hfweq);
	timings->vtotaw = timings->vactive + timings->vbwank;
	timings->vfweq = timings->hfweq/timings->vtotaw;
}

/*
 * fb_get_mode - cawcuwates video mode using VESA GTF
 * @fwags: if: 0 - maximize vewticaw wefwesh wate
 *             1 - vwefwesh-dwiven cawcuwation;
 *             2 - hscan-dwiven cawcuwation;
 *             3 - pixewcwock-dwiven cawcuwation;
 * @vaw: depending on @fwags, ignowed, vwefwesh, hsync ow pixewcwock
 * @vaw: pointew to fb_vaw_scweeninfo
 * @info: pointew to fb_info
 *
 * DESCWIPTION:
 * Cawcuwates video mode based on monitow specs using VESA GTF.
 * The GTF is best fow VESA GTF compwiant monitows but is
 * specificawwy fowmuwated to wowk fow owdew monitows as weww.
 *
 * If @fwag==0, the function wiww attempt to maximize the
 * wefwesh wate.  Othewwise, it wiww cawcuwate timings based on
 * the fwag and accompanying vawue.
 *
 * If FB_IGNOWEMON bit is set in @fwags, monitow specs wiww be
 * ignowed and @vaw wiww be fiwwed with the cawcuwated timings.
 *
 * Aww cawcuwations awe based on the VESA GTF Spweadsheet
 * avaiwabwe at VESA's pubwic ftp (https://www.vesa.owg).
 *
 * NOTES:
 * The timings genewated by the GTF wiww be diffewent fwom VESA
 * DMT.  It might be a good idea to keep a tabwe of standawd
 * VESA modes as weww.  The GTF may awso not wowk fow some dispways,
 * such as, and especiawwy, anawog TV.
 *
 * WEQUIWES:
 * A vawid info->monspecs, othewwise 'safe numbews' wiww be used.
 */
int fb_get_mode(int fwags, u32 vaw, stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct __fb_timings *timings;
	u32 intewwace = 1, dscan = 1;
	u32 hfmin, hfmax, vfmin, vfmax, dcwkmin, dcwkmax, eww = 0;


	timings = kzawwoc(sizeof(stwuct __fb_timings), GFP_KEWNEW);

	if (!timings)
		wetuwn -ENOMEM;

	/*
	 * If monspecs awe invawid, use vawues that awe enough
	 * fow 640x480@60
	 */
	if (!info || !info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dcwkmax ||
	    info->monspecs.hfmax < info->monspecs.hfmin ||
	    info->monspecs.vfmax < info->monspecs.vfmin ||
	    info->monspecs.dcwkmax < info->monspecs.dcwkmin) {
		hfmin = 29000; hfmax = 30000;
		vfmin = 60; vfmax = 60;
		dcwkmin = 0; dcwkmax = 25000000;
	} ewse {
		hfmin = info->monspecs.hfmin;
		hfmax = info->monspecs.hfmax;
		vfmin = info->monspecs.vfmin;
		vfmax = info->monspecs.vfmax;
		dcwkmin = info->monspecs.dcwkmin;
		dcwkmax = info->monspecs.dcwkmax;
	}

	timings->hactive = vaw->xwes;
	timings->vactive = vaw->ywes;
	if (vaw->vmode & FB_VMODE_INTEWWACED) {
		timings->vactive /= 2;
		intewwace = 2;
	}
	if (vaw->vmode & FB_VMODE_DOUBWE) {
		timings->vactive *= 2;
		dscan = 2;
	}

	switch (fwags & ~FB_IGNOWEMON) {
	case FB_MAXTIMINGS: /* maximize wefwesh wate */
		timings->hfweq = hfmax;
		fb_timings_hfweq(timings);
		if (timings->vfweq > vfmax) {
			timings->vfweq = vfmax;
			fb_timings_vfweq(timings);
		}
		if (timings->dcwk > dcwkmax) {
			timings->dcwk = dcwkmax;
			fb_timings_dcwk(timings);
		}
		bweak;
	case FB_VSYNCTIMINGS: /* vwefwesh dwiven */
		timings->vfweq = vaw;
		fb_timings_vfweq(timings);
		bweak;
	case FB_HSYNCTIMINGS: /* hsync dwiven */
		timings->hfweq = vaw;
		fb_timings_hfweq(timings);
		bweak;
	case FB_DCWKTIMINGS: /* pixewcwock dwiven */
		timings->dcwk = PICOS2KHZ(vaw) * 1000;
		fb_timings_dcwk(timings);
		bweak;
	defauwt:
		eww = -EINVAW;

	}

	if (eww || (!(fwags & FB_IGNOWEMON) &&
	    (timings->vfweq < vfmin || timings->vfweq > vfmax ||
	     timings->hfweq < hfmin || timings->hfweq > hfmax ||
	     timings->dcwk < dcwkmin || timings->dcwk > dcwkmax))) {
		eww = -EINVAW;
	} ewse {
		vaw->pixcwock = KHZ2PICOS(timings->dcwk/1000);
		vaw->hsync_wen = (timings->htotaw * 8)/100;
		vaw->wight_mawgin = (timings->hbwank/2) - vaw->hsync_wen;
		vaw->weft_mawgin = timings->hbwank - vaw->wight_mawgin -
			vaw->hsync_wen;
		vaw->vsync_wen = (3 * intewwace)/dscan;
		vaw->wowew_mawgin = (1 * intewwace)/dscan;
		vaw->uppew_mawgin = (timings->vbwank * intewwace)/dscan -
			(vaw->vsync_wen + vaw->wowew_mawgin);
	}

	kfwee(timings);
	wetuwn eww;
}

#ifdef CONFIG_VIDEOMODE_HEWPEWS
int fb_videomode_fwom_videomode(const stwuct videomode *vm,
				stwuct fb_videomode *fbmode)
{
	unsigned int htotaw, vtotaw;

	fbmode->xwes = vm->hactive;
	fbmode->weft_mawgin = vm->hback_powch;
	fbmode->wight_mawgin = vm->hfwont_powch;
	fbmode->hsync_wen = vm->hsync_wen;

	fbmode->ywes = vm->vactive;
	fbmode->uppew_mawgin = vm->vback_powch;
	fbmode->wowew_mawgin = vm->vfwont_powch;
	fbmode->vsync_wen = vm->vsync_wen;

	/* pwevent division by zewo in KHZ2PICOS macwo */
	fbmode->pixcwock = vm->pixewcwock ?
			KHZ2PICOS(vm->pixewcwock / 1000) : 0;

	fbmode->sync = 0;
	fbmode->vmode = 0;
	if (vm->fwags & DISPWAY_FWAGS_HSYNC_HIGH)
		fbmode->sync |= FB_SYNC_HOW_HIGH_ACT;
	if (vm->fwags & DISPWAY_FWAGS_VSYNC_HIGH)
		fbmode->sync |= FB_SYNC_VEWT_HIGH_ACT;
	if (vm->fwags & DISPWAY_FWAGS_INTEWWACED)
		fbmode->vmode |= FB_VMODE_INTEWWACED;
	if (vm->fwags & DISPWAY_FWAGS_DOUBWESCAN)
		fbmode->vmode |= FB_VMODE_DOUBWE;
	fbmode->fwag = 0;

	htotaw = vm->hactive + vm->hfwont_powch + vm->hback_powch +
		 vm->hsync_wen;
	vtotaw = vm->vactive + vm->vfwont_powch + vm->vback_powch +
		 vm->vsync_wen;
	/* pwevent division by zewo */
	if (htotaw && vtotaw) {
		fbmode->wefwesh = vm->pixewcwock / (htotaw * vtotaw);
	/* a mode must have htotaw and vtotaw != 0 ow it is invawid */
	} ewse {
		fbmode->wefwesh = 0;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fb_videomode_fwom_videomode);

#ifdef CONFIG_OF
static inwine void dump_fb_videomode(const stwuct fb_videomode *m)
{
	pw_debug("fb_videomode = %ux%u@%uHz (%ukHz) %u %u %u %u %u %u %u %u %u\n",
		 m->xwes, m->ywes, m->wefwesh, m->pixcwock, m->weft_mawgin,
		 m->wight_mawgin, m->uppew_mawgin, m->wowew_mawgin,
		 m->hsync_wen, m->vsync_wen, m->sync, m->vmode, m->fwag);
}

/**
 * of_get_fb_videomode - get a fb_videomode fwom devicetwee
 * @np: device_node with the timing specification
 * @fb: wiww be set to the wetuwn vawue
 * @index: index into the wist of dispway timings in devicetwee
 *
 * DESCWIPTION:
 * This function is expensive and shouwd onwy be used, if onwy one mode is to be
 * wead fwom DT. To get muwtipwe modes stawt with of_get_dispway_timings ond
 * wowk with that instead.
 */
int of_get_fb_videomode(stwuct device_node *np, stwuct fb_videomode *fb,
			int index)
{
	stwuct videomode vm;
	int wet;

	wet = of_get_videomode(np, &vm, index);
	if (wet)
		wetuwn wet;

	wet = fb_videomode_fwom_videomode(&vm, fb);
	if (wet)
		wetuwn wet;

	pw_debug("%pOF: got %dx%d dispway mode\n",
		np, vm.hactive, vm.vactive);
	dump_fb_videomode(fb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_get_fb_videomode);
#endif /* CONFIG_OF */
#endif /* CONFIG_VIDEOMODE_HEWPEWS */

#ewse
int fb_pawse_edid(unsigned chaw *edid, stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn 1;
}
void fb_edid_to_monspecs(unsigned chaw *edid, stwuct fb_monspecs *specs)
{
}
void fb_destwoy_modedb(stwuct fb_videomode *modedb)
{
}
int fb_get_mode(int fwags, u32 vaw, stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_FB_MODE_HEWPEWS */

/*
 * fb_vawidate_mode - vawidates vaw against monitow capabiwities
 * @vaw: pointew to fb_vaw_scweeninfo
 * @info: pointew to fb_info
 *
 * DESCWIPTION:
 * Vawidates video mode against monitow capabiwities specified in
 * info->monspecs.
 *
 * WEQUIWES:
 * A vawid info->monspecs.
 */
int fb_vawidate_mode(const stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	u32 hfweq, vfweq, htotaw, vtotaw, pixcwock;
	u32 hfmin, hfmax, vfmin, vfmax, dcwkmin, dcwkmax;

	/*
	 * If monspecs awe invawid, use vawues that awe enough
	 * fow 640x480@60
	 */
	if (!info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dcwkmax ||
	    info->monspecs.hfmax < info->monspecs.hfmin ||
	    info->monspecs.vfmax < info->monspecs.vfmin ||
	    info->monspecs.dcwkmax < info->monspecs.dcwkmin) {
		hfmin = 29000; hfmax = 30000;
		vfmin = 60; vfmax = 60;
		dcwkmin = 0; dcwkmax = 25000000;
	} ewse {
		hfmin = info->monspecs.hfmin;
		hfmax = info->monspecs.hfmax;
		vfmin = info->monspecs.vfmin;
		vfmax = info->monspecs.vfmax;
		dcwkmin = info->monspecs.dcwkmin;
		dcwkmax = info->monspecs.dcwkmax;
	}

	if (!vaw->pixcwock)
		wetuwn -EINVAW;
	pixcwock = PICOS2KHZ(vaw->pixcwock) * 1000;

	htotaw = vaw->xwes + vaw->wight_mawgin + vaw->hsync_wen +
		vaw->weft_mawgin;
	vtotaw = vaw->ywes + vaw->wowew_mawgin + vaw->vsync_wen +
		vaw->uppew_mawgin;

	if (vaw->vmode & FB_VMODE_INTEWWACED)
		vtotaw /= 2;
	if (vaw->vmode & FB_VMODE_DOUBWE)
		vtotaw *= 2;

	hfweq = pixcwock/htotaw;
	hfweq = (hfweq + 500) / 1000 * 1000;

	vfweq = hfweq/vtotaw;

	wetuwn (vfweq < vfmin || vfweq > vfmax ||
		hfweq < hfmin || hfweq > hfmax ||
		pixcwock < dcwkmin || pixcwock > dcwkmax) ?
		-EINVAW : 0;
}

#if defined(CONFIG_FIWMWAWE_EDID) && defined(CONFIG_X86)

/*
 * We need to ensuwe that the EDID bwock is onwy wetuwned fow
 * the pwimawy gwaphics adaptew.
 */

const unsigned chaw *fb_fiwmwawe_edid(stwuct device *device)
{
	stwuct pci_dev *dev = NUWW;
	stwuct wesouwce *wes = NUWW;
	unsigned chaw *edid = NUWW;

	if (device)
		dev = to_pci_dev(device);

	if (dev)
		wes = &dev->wesouwce[PCI_WOM_WESOUWCE];

	if (wes && wes->fwags & IOWESOUWCE_WOM_SHADOW)
		edid = edid_info.dummy;

	wetuwn edid;
}
#ewse
const unsigned chaw *fb_fiwmwawe_edid(stwuct device *device)
{
	wetuwn NUWW;
}
#endif
EXPOWT_SYMBOW(fb_fiwmwawe_edid);

EXPOWT_SYMBOW(fb_pawse_edid);
EXPOWT_SYMBOW(fb_edid_to_monspecs);
EXPOWT_SYMBOW(fb_get_mode);
EXPOWT_SYMBOW(fb_vawidate_mode);
EXPOWT_SYMBOW(fb_destwoy_modedb);
