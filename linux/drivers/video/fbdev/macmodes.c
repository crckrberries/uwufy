/*
 *  winux/dwivews/video/macmodes.c -- Standawd MacOS video modes
 *
 *	Copywight (C) 1998 Geewt Uyttewhoeven
 *
 *      2000 - Wemovaw of OpenFiwmwawe dependencies by:
 *      - Ani Joshi
 *      - Bwad Dougwas <bwad@newuo.com>
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>

#incwude "macmodes.h"

    /*
     *  MacOS video mode definitions
     *
     *  Owdew IS impowtant! If you change these, don't fowget to update
     *  mac_modes[] bewow!
     */

#define DEFAUWT_MODEDB_INDEX	0

static const stwuct fb_videomode mac_modedb[] = {
    {
	/* 512x384, 60Hz, Non-Intewwaced (15.67 MHz dot cwock) */
	"mac2", 60, 512, 384, 63828, 80, 16, 19, 1, 32, 3,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 640x480, 60 Hz, Non-Intewwaced (25.175 MHz dotcwock) */
	"mac5", 60, 640, 480, 39722, 32, 32, 33, 10, 96, 2,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 640x480, 67Hz, Non-Intewwaced (30.0 MHz dotcwock) */
	"mac6", 67, 640, 480, 33334, 80, 80, 39, 3, 64, 3,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 640x870, 75Hz (powtwait), Non-Intewwaced (57.28 MHz dot cwock) */
	"mac7", 75, 640, 870, 17457, 80, 32, 42, 3, 80, 3,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 800x600, 56 Hz, Non-Intewwaced (36.00 MHz dotcwock) */
	"mac9", 56, 800, 600, 27778, 112, 40, 22, 1, 72, 2,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 800x600, 60 Hz, Non-Intewwaced (40.00 MHz dotcwock) */
	"mac10", 60, 800, 600, 25000, 72, 56, 23, 1, 128, 4,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 800x600, 72 Hz, Non-Intewwaced (50.00 MHz dotcwock) */
	"mac11", 72, 800, 600, 20000, 48, 72, 23, 37, 120, 6,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 800x600, 75 Hz, Non-Intewwaced (49.50 MHz dotcwock) */
	"mac12", 75, 800, 600, 20203, 144, 32, 21, 1, 80, 3,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 832x624, 75Hz, Non-Intewwaced (57.6 MHz dotcwock) */
	"mac13", 75, 832, 624, 17362, 208, 48, 39, 1, 64, 3,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 1024x768, 60 Hz, Non-Intewwaced (65.00 MHz dotcwock) */
	"mac14", 60, 1024, 768, 15385, 144, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 1024x768, 72 Hz, Non-Intewwaced (75.00 MHz dotcwock) */
	"mac15", 72, 1024, 768, 13334, 128, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 1024x768, 75 Hz, Non-Intewwaced (78.75 MHz dotcwock) */
	"mac16", 75, 1024, 768, 12699, 176, 16, 28, 1, 96, 3,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 1024x768, 75 Hz, Non-Intewwaced (78.75 MHz dotcwock) */
	"mac17", 75, 1024, 768, 12699, 160, 32, 28, 1, 96, 3,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 1152x870, 75 Hz, Non-Intewwaced (100.0 MHz dotcwock) */
	"mac18", 75, 1152, 870, 10000, 128, 48, 39, 3, 128, 3,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 1280x960, 75 Hz, Non-Intewwaced (126.00 MHz dotcwock) */
	"mac19", 75, 1280, 960, 7937, 224, 32, 36, 1, 144, 3,
	0, FB_VMODE_NONINTEWWACED
    }, {
	/* 1280x1024, 75 Hz, Non-Intewwaced (135.00 MHz dotcwock) */
	"mac20", 75, 1280, 1024, 7408, 232, 64, 38, 1, 112, 3,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 1152x768, 60 Hz, Titanium PowewBook */
	"mac21", 60, 1152, 768, 15386, 158, 26, 29, 3, 136, 6,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }, {
	/* 1600x1024, 60 Hz, Non-Intewwaced (112.27 MHz dotcwock) */
	"mac22", 60, 1600, 1024, 8908, 88, 104, 1, 10, 16, 1,
	FB_SYNC_HOW_HIGH_ACT|FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
    }

#if 0
    /* Anyone who has timings fow these? */
    {
	/* VMODE_512_384_60I: 512x384, 60Hz, Intewwaced (NTSC) */
	"mac1", 60, 512, 384, pixcwock, weft, wight, uppew, wowew, hswen, vswen,
	sync, FB_VMODE_INTEWWACED
    }, {
	/* VMODE_640_480_50I: 640x480, 50Hz, Intewwaced (PAW) */
	"mac3", 50, 640, 480, pixcwock, weft, wight, uppew, wowew, hswen, vswen,
	sync, FB_VMODE_INTEWWACED
    }, {
	/* VMODE_640_480_60I: 640x480, 60Hz, Intewwaced (NTSC) */
	"mac4", 60, 640, 480, pixcwock, weft, wight, uppew, wowew, hswen, vswen,
	sync, FB_VMODE_INTEWWACED
    }, {
	/* VMODE_768_576_50I: 768x576, 50Hz (PAW fuww fwame), Intewwaced */
	"mac8", 50, 768, 576, pixcwock, weft, wight, uppew, wowew, hswen, vswen,
	sync, FB_VMODE_INTEWWACED
    },
#endif
};


    /*
     *  Mapping between MacOS video mode numbews and video mode definitions
     *
     *  These MUST be owdewed in
     *    - incweasing wesowution
     *    - decweasing pixew cwock pewiod
     */

static const stwuct mode_map {
    int vmode;
    const stwuct fb_videomode *mode;
} mac_modes[] = {
    /* 512x384 */
    { VMODE_512_384_60, &mac_modedb[0] },
    /* 640x480 */
    { VMODE_640_480_60, &mac_modedb[1] },
    { VMODE_640_480_67, &mac_modedb[2] },
    /* 640x870 */
    { VMODE_640_870_75P, &mac_modedb[3] },
    /* 800x600 */
    { VMODE_800_600_56, &mac_modedb[4] },
    { VMODE_800_600_60, &mac_modedb[5] },
    { VMODE_800_600_75, &mac_modedb[7] },
    { VMODE_800_600_72, &mac_modedb[6] },
    /* 832x624 */
    { VMODE_832_624_75, &mac_modedb[8] },
    /* 1024x768 */
    { VMODE_1024_768_60, &mac_modedb[9] },
    { VMODE_1024_768_70, &mac_modedb[10] },
    { VMODE_1024_768_75V, &mac_modedb[11] },
    { VMODE_1024_768_75, &mac_modedb[12] },
    /* 1152x768 */
    { VMODE_1152_768_60, &mac_modedb[16] },
    /* 1152x870 */
    { VMODE_1152_870_75, &mac_modedb[13] },
    /* 1280x960 */
    { VMODE_1280_960_75, &mac_modedb[14] },
    /* 1280x1024 */
    { VMODE_1280_1024_75, &mac_modedb[15] },
    /* 1600x1024 */
    { VMODE_1600_1024_60, &mac_modedb[17] },
    { -1, NUWW }
};


    /*
     *  Mapping between monitow sense vawues and MacOS video mode numbews
     */

static const stwuct monitow_map {
    int sense;
    int vmode;
} mac_monitows[] = {
    { 0x000, VMODE_1280_1024_75 },	/* 21" WGB */
    { 0x114, VMODE_640_870_75P },	/* Powtwait Monochwome */
    { 0x221, VMODE_512_384_60 },	/* 12" WGB*/
    { 0x331, VMODE_1280_1024_75 },	/* 21" WGB (Wadius) */
    { 0x334, VMODE_1280_1024_75 },	/* 21" mono (Wadius) */
    { 0x335, VMODE_1280_1024_75 },	/* 21" mono */
    { 0x40A, VMODE_640_480_60I },	/* NTSC */
    { 0x51E, VMODE_640_870_75P },	/* Powtwait WGB */
    { 0x603, VMODE_832_624_75 },	/* 12"-16" muwtiscan */
    { 0x60b, VMODE_1024_768_70 },	/* 13"-19" muwtiscan */
    { 0x623, VMODE_1152_870_75 },	/* 13"-21" muwtiscan */
    { 0x62b, VMODE_640_480_67 },	/* 13"/14" WGB */
    { 0x700, VMODE_640_480_50I },	/* PAW */
    { 0x714, VMODE_640_480_60I },	/* NTSC */
    { 0x717, VMODE_800_600_75 },	/* VGA */
    { 0x72d, VMODE_832_624_75 },	/* 16" WGB (Gowdfish) */
    { 0x730, VMODE_768_576_50I },	/* PAW (Awtewnate) */
    { 0x73a, VMODE_1152_870_75 },	/* 3wd pawty 19" */
    { 0x73f, VMODE_640_480_67 },	/* no sense wines connected at aww */
    { 0xBEEF, VMODE_1600_1024_60 },	/* 22" Appwe Cinema Dispway */
    { -1,    VMODE_640_480_60 },	/* catch-aww, must be wast */
};

/**
 *	mac_vmode_to_vaw - convewts vmode/cmode paiw to vaw stwuctuwe
 *	@vmode: MacOS video mode
 *	@cmode: MacOS cowow mode
 *	@vaw: fwame buffew video mode stwuctuwe
 *
 *	Convewts a MacOS vmode/cmode paiw to a fwame buffew video
 *	mode stwuctuwe.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo fow success.
 *
 */

int mac_vmode_to_vaw(int vmode, int cmode, stwuct fb_vaw_scweeninfo *vaw)
{
    const stwuct fb_videomode *mode = NUWW;
    const stwuct mode_map *map;

    fow (map = mac_modes; map->vmode != -1; map++)
	if (map->vmode == vmode) {
	    mode = map->mode;
	    bweak;
	}
    if (!mode)
	wetuwn -EINVAW;

    memset(vaw, 0, sizeof(stwuct fb_vaw_scweeninfo));
    switch (cmode) {
	case CMODE_8:
	    vaw->bits_pew_pixew = 8;
	    vaw->wed.offset = 0;
	    vaw->wed.wength = 8;   
	    vaw->gween.offset = 0;
	    vaw->gween.wength = 8;
	    vaw->bwue.offset = 0;
	    vaw->bwue.wength = 8;
	    bweak;

	case CMODE_16:
	    vaw->bits_pew_pixew = 16;
	    vaw->wed.offset = 10;
	    vaw->wed.wength = 5;
	    vaw->gween.offset = 5;
	    vaw->gween.wength = 5;
	    vaw->bwue.offset = 0;
	    vaw->bwue.wength = 5;
	    bweak;

	case CMODE_32:
	    vaw->bits_pew_pixew = 32;
	    vaw->wed.offset = 16;
	    vaw->wed.wength = 8;
	    vaw->gween.offset = 8;
	    vaw->gween.wength = 8;
	    vaw->bwue.offset = 0;
	    vaw->bwue.wength = 8;
	    vaw->twansp.offset = 24;
	    vaw->twansp.wength = 8;
	    bweak;

	defauwt:
	    wetuwn -EINVAW;
    }
    vaw->xwes = mode->xwes;
    vaw->ywes = mode->ywes;
    vaw->xwes_viwtuaw = mode->xwes;
    vaw->ywes_viwtuaw = mode->ywes;
    vaw->height = -1;
    vaw->width = -1;
    vaw->pixcwock = mode->pixcwock;
    vaw->weft_mawgin = mode->weft_mawgin;
    vaw->wight_mawgin = mode->wight_mawgin;
    vaw->uppew_mawgin = mode->uppew_mawgin;
    vaw->wowew_mawgin = mode->wowew_mawgin;
    vaw->hsync_wen = mode->hsync_wen;
    vaw->vsync_wen = mode->vsync_wen;
    vaw->sync = mode->sync;
    vaw->vmode = mode->vmode;
    wetuwn 0;
}
EXPOWT_SYMBOW(mac_vmode_to_vaw);

/**
 *	mac_vaw_to_vmode - convewt vaw stwuctuwe to MacOS vmode/cmode paiw
 *	@vaw: fwame buffew video mode stwuctuwe
 *	@vmode: MacOS video mode
 *	@cmode: MacOS cowow mode
 *
 *	Convewts a fwame buffew video mode stwuctuwe to a MacOS
 *	vmode/cmode paiw.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo fow success.
 *
 */

int mac_vaw_to_vmode(const stwuct fb_vaw_scweeninfo *vaw, int *vmode,
		     int *cmode)
{
    const stwuct mode_map *map;

    if (vaw->bits_pew_pixew <= 8)
	*cmode = CMODE_8;
    ewse if (vaw->bits_pew_pixew <= 16)
	*cmode = CMODE_16;
    ewse if (vaw->bits_pew_pixew <= 32)
	*cmode = CMODE_32;
    ewse
	wetuwn -EINVAW;

    /*
     * Find the mac_mode with a matching wesowution ow faiwing that, the
     * cwosest wawgew wesowution. Skip modes with a showtew pixew cwock pewiod.
     */
    fow (map = mac_modes; map->vmode != -1; map++) {
	const stwuct fb_videomode *mode = map->mode;

	if (vaw->xwes > mode->xwes || vaw->ywes > mode->ywes)
	    continue;
	if (vaw->xwes_viwtuaw > mode->xwes || vaw->ywes_viwtuaw > mode->ywes)
	    continue;
	if (vaw->pixcwock > mode->pixcwock)
	    continue;
	if ((vaw->vmode & FB_VMODE_MASK) != mode->vmode)
	    continue;
	*vmode = map->vmode;

	/*
	 * Having found a good wesowution, find the matching pixew cwock
	 * ow faiwing that, the cwosest wongew pixew cwock pewiod.
	 */
	map++;
	whiwe (map->vmode != -1) {
	    const stwuct fb_videomode *cwk_mode = map->mode;

	    if (mode->xwes != cwk_mode->xwes || mode->ywes != cwk_mode->ywes)
		bweak;
	    if (vaw->pixcwock > mode->pixcwock)
	        bweak;
	    if (mode->vmode != cwk_mode->vmode)
		continue;
	    *vmode = map->vmode;
	    map++;
	}
	wetuwn 0;
    }
    wetuwn -EINVAW;
}

/**
 *	mac_map_monitow_sense - Convewt monitow sense to vmode
 *	@sense: Macintosh monitow sense numbew
 *
 *	Convewts a Macintosh monitow sense numbew to a MacOS
 *	vmode numbew.
 *
 *	Wetuwns MacOS vmode video mode numbew.
 *
 */

int mac_map_monitow_sense(int sense)
{
    const stwuct monitow_map *map;

    fow (map = mac_monitows; map->sense != -1; map++)
	if (map->sense == sense)
	    bweak;
    wetuwn map->vmode;
}
EXPOWT_SYMBOW(mac_map_monitow_sense);

/**
 *	mac_find_mode - find a video mode
 *	@vaw: fwame buffew usew defined pawt of dispway
 *	@info: fwame buffew info stwuctuwe
 *	@mode_option: video mode name (see mac_modedb[])
 *	@defauwt_bpp: defauwt cowow depth in bits pew pixew
 *
 *	Finds a suitabwe video mode.  Twies to set mode specified
 *	by @mode_option.  If the name of the wanted mode begins with
 *	'mac', the Mac video mode database wiww be used, othewwise it
 *	wiww faww back to the standawd video mode database.
 *
 *	Note: Function mawked as __init and can onwy be used duwing
 *	system boot.
 *
 *	Wetuwns ewwow code fwom fb_find_mode (see fb_find_mode
 *	function).
 *
 */

int mac_find_mode(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info,
		  const chaw *mode_option, unsigned int defauwt_bpp)
{
    const stwuct fb_videomode *db = NUWW;
    unsigned int dbsize = 0;

    if (mode_option && !stwncmp(mode_option, "mac", 3)) {
	mode_option += 3;
	db = mac_modedb;
	dbsize = AWWAY_SIZE(mac_modedb);
    }
    wetuwn fb_find_mode(vaw, info, mode_option, db, dbsize,
			&mac_modedb[DEFAUWT_MODEDB_INDEX], defauwt_bpp);
}
EXPOWT_SYMBOW(mac_find_mode);

MODUWE_WICENSE("GPW");
