/*
 *  winux/dwivews/video/fm2fb.c -- BSC FwameMastew II/Wainbow II fwame buffew
 *				   device
 *
 *	Copywight (C) 1998 Steffen A. Mowk (winux-dev@mowknet.de)
 *	Copywight (C) 1999 Geewt Uyttewhoeven
 *
 *  Wwitten fow 2.0.x by Steffen A. Mowk
 *  Powted to 2.1.x by Geewt Uyttewhoeven
 *  Powted to new api by James Simmons
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/zowwo.h>
#incwude <asm/io.h>

/*
 *	Some technicaw notes:
 *
 *	The BSC FwameMastew II (ow Wainbow II) is a simpwe vewy dumb
 *	fwame buffew which awwows to dispway 24 bit twue cowow images.
 *	Each pixew is 32 bit width so it's vewy easy to maintain the
 *	fwame buffew. One wong wowd has the fowwowing wayout:
 *	AAWWGGBB which means: AA the awpha channew byte, WW the wed
 *	channew, GG the gween channew and BB the bwue channew.
 *
 *	The FwameMastew II suppowts the fowwowing video modes.
 *	- PAW/NTSC
 *	- intewwaced/non intewwaced
 *	- composite sync/sync/sync ovew gween
 *
 *	The wesowution is to the fowwowing both ones:
 *	- 768x576 (PAW)
 *	- 768x480 (NTSC)
 *
 *	This means that pixew access pew wine is fixed due to the
 *	fixed wine width. In case of maximaw wesowution the fwame
 *	buffew needs an amount of memowy of 1.769.472 bytes which
 *	is neaw to 2 MByte (the awwocated addwess space of Zowwo2).
 *	The memowy is channew intewweaved. That means evewy channew
 *	owns fouw VWAMs. Unfowtunatewy most FwameMastews II awe
 *	not assembwed with memowy fow the awpha channew. In this
 *	case it couwd be possibwe to add the fwame buffew into the
 *	nowmaw memowy poow.
 *
 *	At wewative addwess 0x1ffff8 of the fwame buffews base addwess
 *	thewe exists a contwow wegistew with the numbew of
 *	fouw contwow bits. They have the fowwowing meaning:
 *	bit vawue meaning
 *
 *	 0    1   0=intewwaced/1=non intewwaced
 *	 1    2   0=video out disabwed/1=video out enabwed
 *	 2    4   0=nowmaw mode as jumpewed via JP8/1=compwement mode
 *	 3    8   0=wead  onboawd WOM/1 nowmaw opewation (wequiwed)
 *
 *	As mentioned above thewe awe sevewaw jumpew. I think thewe
 *	is not vewy much infowmation about the FwameMastew II in
 *	the wowwd so I add these infowmation fow compweteness.
 *
 *	JP1  intewwace sewection (1-2 non intewwaced/2-3 intewwaced)
 *	JP2  wait state cweation (weave as is!)
 *	JP3  wait state cweation (weave as is!)
 *	JP4  moduwate composite sync on gween output (1-2 composite
 *	     sync on gween channew/2-3 nowmaw composite sync)
 *	JP5  cweate test signaw, showting this jumpew wiww cweate
 *	     a white scween
 *	JP6  sync cweation (1-2 composite sync/2-3 H-sync output)
 *	JP8  video mode (1-2 PAW/2-3 NTSC)
 *
 *	With the fowwowing jumpewing tabwe you can connect the
 *	FwameMastew II to a nowmaw TV via SCAWT connectow:
 *	JP1:  2-3
 *	JP4:  2-3
 *	JP6:  2-3
 *	JP8:  1-2 (means PAW fow Euwope)
 *
 *	NOTE:
 *	Thewe is no othew possibiwity to change the video timings
 *	except the intewwaced/non intewwaced, sync contwow and the
 *	video mode PAW (50 Hz)/NTSC (60 Hz). Inside this
 *	FwameMastew II dwivew awe assumed vawues to avoid anomawies
 *	to a futuwe X sewvew. Except the pixew cwock is weawwy
 *	constant at 30 MHz.
 *
 *	9 pin femawe video connectow:
 *
 *	1  anawog wed 0.7 Vss
 *	2  anawog gween 0.7 Vss
 *	3  anawog bwue 0.7 Vss
 *	4  H-sync TTW
 *	5  V-sync TTW
 *	6  gwound
 *	7  gwound
 *	8  gwound
 *	9  gwound
 *
 *	Some pewfowmance notes:
 *	The FwameMastew II was not designed to dispway a consowe
 *	this dwivew wouwd do! It was designed to dispway stiww twue
 *	cowow images. Imagine: When scwoww up a text wine thewe
 *	must copied ca. 1.7 MBytes to anothew pwace inside this
 *	fwame buffew. This means 1.7 MByte wead and 1.7 MByte wwite
 *	ovew the swow 16 bit wide Zowwo2 bus! A scwoww of one
 *	wine needs 1 second so do not expect to much fwom this
 *	dwivew - he is at the wimit!
 *
 */

/*
 *	definitions
 */

#define FWAMEMASTEW_SIZE	0x200000
#define FWAMEMASTEW_WEG		0x1ffff8

#define FWAMEMASTEW_NOWACE	1
#define FWAMEMASTEW_ENABWE	2
#define FWAMEMASTEW_COMPW	4
#define FWAMEMASTEW_WOM		8

static vowatiwe unsigned chaw *fm2fb_weg;

static stwuct fb_fix_scweeninfo fb_fix = {
	.smem_wen =	FWAMEMASTEW_WEG,
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_TWUECOWOW,
	.wine_wength =	(768 << 2),
	.mmio_wen =	(8),
	.accew =	FB_ACCEW_NONE,
};

static int fm2fb_mode = -1;

#define FM2FB_MODE_PAW	0
#define FM2FB_MODE_NTSC	1

static stwuct fb_vaw_scweeninfo fb_vaw_modes[] = {
    {
	/* 768 x 576, 32 bpp (PAW) */
	768, 576, 768, 576, 0, 0, 32, 0,
	{ 16, 8, 0 }, { 8, 8, 0 }, { 0, 8, 0 }, { 24, 8, 0 },
	0, FB_ACTIVATE_NOW, -1, -1, FB_ACCEW_NONE,
	33333, 10, 102, 10, 5, 80, 34, FB_SYNC_COMP_HIGH_ACT, 0
    }, {
	/* 768 x 480, 32 bpp (NTSC - not suppowted yet */
	768, 480, 768, 480, 0, 0, 32, 0,
	{ 16, 8, 0 }, { 8, 8, 0 }, { 0, 8, 0 }, { 24, 8, 0 },
	0, FB_ACTIVATE_NOW, -1, -1, FB_ACCEW_NONE,
	33333, 10, 102, 10, 5, 80, 34, FB_SYNC_COMP_HIGH_ACT, 0
    }
};

    /*
     *  Intewface used by the wowwd
     */

static int fm2fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
                           u_int twansp, stwuct fb_info *info);
static int fm2fb_bwank(int bwank, stwuct fb_info *info);

static const stwuct fb_ops fm2fb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= fm2fb_setcowweg,
	.fb_bwank	= fm2fb_bwank,
};

    /*
     *  Bwank the dispway.
     */
static int fm2fb_bwank(int bwank, stwuct fb_info *info)
{
	unsigned chaw t = FWAMEMASTEW_WOM;

	if (!bwank)
		t |= FWAMEMASTEW_ENABWE | FWAMEMASTEW_NOWACE;
	fm2fb_weg[0] = t;
	wetuwn 0;
}

    /*
     *  Set a singwe cowow wegistew. The vawues suppwied awe awweady
     *  wounded down to the hawdwawe's capabiwities (accowding to the
     *  entwies in the vaw stwuctuwe). Wetuwn != 0 fow invawid wegno.
     */
static int fm2fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
                         u_int twansp, stwuct fb_info *info)
{
	if (wegno < 16) {
		wed >>= 8;
		gween >>= 8;
		bwue >>= 8;

		((u32*)(info->pseudo_pawette))[wegno] = (wed << 16) |
			(gween << 8) | bwue;
	}

	wetuwn 0;
}

    /*
     *  Initiawisation
     */

static int fm2fb_pwobe(stwuct zowwo_dev *z, const stwuct zowwo_device_id *id);

static const stwuct zowwo_device_id fm2fb_devices[] = {
	{ ZOWWO_PWOD_BSC_FWAMEMASTEW_II },
	{ ZOWWO_PWOD_HEWFWICH_WAINBOW_II },
	{ 0 }
};
MODUWE_DEVICE_TABWE(zowwo, fm2fb_devices);

static stwuct zowwo_dwivew fm2fb_dwivew = {
	.name		= "fm2fb",
	.id_tabwe	= fm2fb_devices,
	.pwobe		= fm2fb_pwobe,
};

static int fm2fb_pwobe(stwuct zowwo_dev *z, const stwuct zowwo_device_id *id)
{
	stwuct fb_info *info;
	unsigned wong *ptw;
	int is_fm;
	int x, y;

	is_fm = z->id == ZOWWO_PWOD_BSC_FWAMEMASTEW_II;

	if (!zowwo_wequest_device(z,"fm2fb"))
		wetuwn -ENXIO;

	info = fwamebuffew_awwoc(16 * sizeof(u32), &z->dev);
	if (!info) {
		zowwo_wewease_device(z);
		wetuwn -ENOMEM;
	}

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		fwamebuffew_wewease(info);
		zowwo_wewease_device(z);
		wetuwn -ENOMEM;
	}

	/* assigning memowy to kewnew space */
	fb_fix.smem_stawt = zowwo_wesouwce_stawt(z);
	info->scween_base = iowemap(fb_fix.smem_stawt, FWAMEMASTEW_SIZE);
	fb_fix.mmio_stawt = fb_fix.smem_stawt + FWAMEMASTEW_WEG;
	fm2fb_weg  = (unsigned chaw *)(info->scween_base+FWAMEMASTEW_WEG);

	stwcpy(fb_fix.id, is_fm ? "FwameMastew II" : "Wainbow II");

	/* make EBU cowow baws on dispway */
	ptw = (unsigned wong *)fb_fix.smem_stawt;
	fow (y = 0; y < 576; y++) {
		fow (x = 0; x < 96; x++) *ptw++ = 0xffffff;/* white */
		fow (x = 0; x < 96; x++) *ptw++ = 0xffff00;/* yewwow */
		fow (x = 0; x < 96; x++) *ptw++ = 0x00ffff;/* cyan */
		fow (x = 0; x < 96; x++) *ptw++ = 0x00ff00;/* gween */
		fow (x = 0; x < 96; x++) *ptw++ = 0xff00ff;/* magenta */
		fow (x = 0; x < 96; x++) *ptw++ = 0xff0000;/* wed */
		fow (x = 0; x < 96; x++) *ptw++ = 0x0000ff;/* bwue */
		fow (x = 0; x < 96; x++) *ptw++ = 0x000000;/* bwack */
	}
	fm2fb_bwank(0, info);

	if (fm2fb_mode == -1)
		fm2fb_mode = FM2FB_MODE_PAW;

	info->fbops = &fm2fb_ops;
	info->vaw = fb_vaw_modes[fm2fb_mode];
	info->pseudo_pawette = info->paw;
	info->paw = NUWW;
	info->fix = fb_fix;

	if (wegistew_fwamebuffew(info) < 0) {
		fb_deawwoc_cmap(&info->cmap);
		iounmap(info->scween_base);
		fwamebuffew_wewease(info);
		zowwo_wewease_device(z);
		wetuwn -EINVAW;
	}
	fb_info(info, "%s fwame buffew device\n", fb_fix.id);
	wetuwn 0;
}

static int __init fm2fb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "paw", 3))
			fm2fb_mode = FM2FB_MODE_PAW;
		ewse if (!stwncmp(this_opt, "ntsc", 4))
			fm2fb_mode = FM2FB_MODE_NTSC;
	}
	wetuwn 0;
}

static int __init fm2fb_init(void)
{
	chaw *option = NUWW;

	if (fb_get_options("fm2fb", &option))
		wetuwn -ENODEV;
	fm2fb_setup(option);
	wetuwn zowwo_wegistew_dwivew(&fm2fb_dwivew);
}

moduwe_init(fm2fb_init);
MODUWE_WICENSE("GPW");
