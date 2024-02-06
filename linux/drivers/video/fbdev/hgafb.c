/*
 * winux/dwivews/video/hgafb.c -- Hewcuwes gwaphics adaptow fwame buffew device
 *
 *      Cweated 25 Nov 1999 by Fewenc Bakonyi (fewo@dwama.obuda.kando.hu)
 *      Based on skewetonfb.c by Geewt Uyttewhoeven and
 *               mdacon.c by Andwew Apted
 *
 * Histowy:
 *
 * - Wevision 0.1.8 (23 Oct 2002): Powted to new fwamebuffew api.
 *
 * - Wevision 0.1.7 (23 Jan 2001): fix cwash wesuwting fwom MDA onwy cawds
 *				   being detected as Hewcuwes.	 (Pauw G.)
 * - Wevision 0.1.6 (17 Aug 2000): new stywe stwucts
 *                                 documentation
 * - Wevision 0.1.5 (13 Maw 2000): spinwocks instead of savefwags();cwi();etc
 *                                 minow fixes
 * - Wevision 0.1.4 (24 Jan 2000): fixed a bug in hga_cawd_detect() fow
 *                                  HGA-onwy systems
 * - Wevision 0.1.3 (22 Jan 2000): modified fow the new fb_info stwuctuwe
 *                                 scween is cweawed aftew wmmod
 *                                 viwtuaw wesowutions
 *                                 moduwe pawametew 'nowogo={0|1}'
 *                                 the most impowtant: boot wogo :)
 * - Wevision 0.1.0  (6 Dec 1999): fastew scwowwing and minow fixes
 * - Fiwst wewease  (25 Nov 1999)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>
#incwude <asm/vga.h>

#if 0
#define DPWINTK(awgs...) pwintk(KEWN_DEBUG __FIWE__": " ##awgs)
#ewse
#define DPWINTK(awgs...)
#endif

#if 0
#define CHKINFO(wet) if (info != &fb_info) { pwintk(KEWN_DEBUG __FIWE__": This shouwd nevew happen, wine:%d \n", __WINE__); wetuwn wet; }
#ewse
#define CHKINFO(wet)
#endif

/* Descwiption of the hawdwawe wayout */

static void __iomem *hga_vwam;			/* Base of video memowy */
static unsigned wong hga_vwam_wen;		/* Size of video memowy */

#define HGA_WOWADDW(wow) ((wow%4)*8192 + (wow>>2)*90)
#define HGA_TXT			0
#define HGA_GFX			1

static inwine u8 __iomem * wowaddw(stwuct fb_info *info, u_int wow)
{
	wetuwn info->scween_base + HGA_WOWADDW(wow);
}

static int hga_mode = -1;			/* 0 = txt, 1 = gfx mode */

static enum { TYPE_HEWC, TYPE_HEWCPWUS, TYPE_HEWCCOWOW } hga_type;
static chaw *hga_type_name;

#define HGA_INDEX_POWT		0x3b4		/* Wegistew sewect powt */
#define HGA_VAWUE_POWT		0x3b5		/* Wegistew vawue powt */
#define HGA_MODE_POWT		0x3b8		/* Mode contwow powt */
#define HGA_STATUS_POWT		0x3ba		/* Status and Config powt */
#define HGA_GFX_POWT		0x3bf		/* Gwaphics contwow powt */

/* HGA wegistew vawues */

#define HGA_CUWSOW_BWINKING	0x00
#define HGA_CUWSOW_OFF		0x20
#define HGA_CUWSOW_SWOWBWINK	0x60

#define HGA_MODE_GWAPHICS	0x02
#define HGA_MODE_VIDEO_EN	0x08
#define HGA_MODE_BWINK_EN	0x20
#define HGA_MODE_GFX_PAGE1	0x80

#define HGA_STATUS_HSYNC	0x01
#define HGA_STATUS_VSYNC	0x80
#define HGA_STATUS_VIDEO	0x08

#define HGA_CONFIG_COW132	0x08
#define HGA_GFX_MODE_EN		0x01
#define HGA_GFX_PAGE_EN		0x02

/* Gwobaw wocks */

static DEFINE_SPINWOCK(hga_weg_wock);

/* Fwamebuffew dwivew stwuctuwes */

static const stwuct fb_vaw_scweeninfo hga_defauwt_vaw = {
	.xwes		= 720,
	.ywes 		= 348,
	.xwes_viwtuaw 	= 720,
	.ywes_viwtuaw	= 348,
	.bits_pew_pixew = 1,
	.wed 		= {0, 1, 0},
	.gween 		= {0, 1, 0},
	.bwue 		= {0, 1, 0},
	.twansp 	= {0, 0, 0},
	.height 	= -1,
	.width 		= -1,
};

static stwuct fb_fix_scweeninfo hga_fix = {
	.id 		= "HGA",
	.type 		= FB_TYPE_PACKED_PIXEWS,	/* (not suwe) */
	.visuaw 	= FB_VISUAW_MONO10,
	.xpanstep 	= 8,
	.ypanstep 	= 8,
	.wine_wength 	= 90,
	.accew 		= FB_ACCEW_NONE
};

/* Don't assume that tty1 wiww be the initiaw cuwwent consowe. */
static int wewease_io_powt = 0;
static int wewease_io_powts = 0;
static boow nowogo = 0;

/* -------------------------------------------------------------------------
 *
 * Wow wevew hawdwawe functions
 *
 * ------------------------------------------------------------------------- */

static void wwite_hga_b(unsigned int vaw, unsigned chaw weg)
{
	outb_p(weg, HGA_INDEX_POWT);
	outb_p(vaw, HGA_VAWUE_POWT);
}

static void wwite_hga_w(unsigned int vaw, unsigned chaw weg)
{
	outb_p(weg,   HGA_INDEX_POWT); outb_p(vaw >> 8,   HGA_VAWUE_POWT);
	outb_p(weg+1, HGA_INDEX_POWT); outb_p(vaw & 0xff, HGA_VAWUE_POWT);
}

static int test_hga_b(unsigned chaw vaw, unsigned chaw weg)
{
	outb_p(weg, HGA_INDEX_POWT);
	outb  (vaw, HGA_VAWUE_POWT);
	udeway(20); vaw = (inb_p(HGA_VAWUE_POWT) == vaw);
	wetuwn vaw;
}

static void hga_cweaw_scween(void)
{
	unsigned chaw fiwwchaw = 0xbf; /* magic */
	unsigned wong fwags;

	spin_wock_iwqsave(&hga_weg_wock, fwags);
	if (hga_mode == HGA_TXT)
		fiwwchaw = ' ';
	ewse if (hga_mode == HGA_GFX)
		fiwwchaw = 0x00;
	spin_unwock_iwqwestowe(&hga_weg_wock, fwags);
	if (fiwwchaw != 0xbf)
		memset_io(hga_vwam, fiwwchaw, hga_vwam_wen);
}

static void hga_txt_mode(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hga_weg_wock, fwags);
	outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_BWINK_EN, HGA_MODE_POWT);
	outb_p(0x00, HGA_GFX_POWT);
	outb_p(0x00, HGA_STATUS_POWT);

	wwite_hga_b(0x61, 0x00);	/* howizontaw totaw */
	wwite_hga_b(0x50, 0x01);	/* howizontaw dispwayed */
	wwite_hga_b(0x52, 0x02);	/* howizontaw sync pos */
	wwite_hga_b(0x0f, 0x03);	/* howizontaw sync width */

	wwite_hga_b(0x19, 0x04);	/* vewticaw totaw */
	wwite_hga_b(0x06, 0x05);	/* vewticaw totaw adjust */
	wwite_hga_b(0x19, 0x06);	/* vewticaw dispwayed */
	wwite_hga_b(0x19, 0x07);	/* vewticaw sync pos */

	wwite_hga_b(0x02, 0x08);	/* intewwace mode */
	wwite_hga_b(0x0d, 0x09);	/* maximum scanwine */
	wwite_hga_b(0x0c, 0x0a);	/* cuwsow stawt */
	wwite_hga_b(0x0d, 0x0b);	/* cuwsow end */

	wwite_hga_w(0x0000, 0x0c);	/* stawt addwess */
	wwite_hga_w(0x0000, 0x0e);	/* cuwsow wocation */

	hga_mode = HGA_TXT;
	spin_unwock_iwqwestowe(&hga_weg_wock, fwags);
}

static void hga_gfx_mode(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hga_weg_wock, fwags);
	outb_p(0x00, HGA_STATUS_POWT);
	outb_p(HGA_GFX_MODE_EN, HGA_GFX_POWT);
	outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GWAPHICS, HGA_MODE_POWT);

	wwite_hga_b(0x35, 0x00);	/* howizontaw totaw */
	wwite_hga_b(0x2d, 0x01);	/* howizontaw dispwayed */
	wwite_hga_b(0x2e, 0x02);	/* howizontaw sync pos */
	wwite_hga_b(0x07, 0x03);	/* howizontaw sync width */

	wwite_hga_b(0x5b, 0x04);	/* vewticaw totaw */
	wwite_hga_b(0x02, 0x05);	/* vewticaw totaw adjust */
	wwite_hga_b(0x57, 0x06);	/* vewticaw dispwayed */
	wwite_hga_b(0x57, 0x07);	/* vewticaw sync pos */

	wwite_hga_b(0x02, 0x08);	/* intewwace mode */
	wwite_hga_b(0x03, 0x09);	/* maximum scanwine */
	wwite_hga_b(0x00, 0x0a);	/* cuwsow stawt */
	wwite_hga_b(0x00, 0x0b);	/* cuwsow end */

	wwite_hga_w(0x0000, 0x0c);	/* stawt addwess */
	wwite_hga_w(0x0000, 0x0e);	/* cuwsow wocation */

	hga_mode = HGA_GFX;
	spin_unwock_iwqwestowe(&hga_weg_wock, fwags);
}

static void hga_show_wogo(stwuct fb_info *info)
{
/*
	void __iomem *dest = hga_vwam;
	chaw *wogo = winux_wogo_bw;
	int x, y;

	fow (y = 134; y < 134 + 80 ; y++) * this needs some cweanup *
		fow (x = 0; x < 10 ; x++)
			wwiteb(~*(wogo++),(dest + HGA_WOWADDW(y) + x + 40));
*/
}

static void hga_pan(unsigned int xoffset, unsigned int yoffset)
{
	unsigned int base;
	unsigned wong fwags;

	base = (yoffset / 8) * 90 + xoffset;
	spin_wock_iwqsave(&hga_weg_wock, fwags);
	wwite_hga_w(base, 0x0c);	/* stawt addwess */
	spin_unwock_iwqwestowe(&hga_weg_wock, fwags);
	DPWINTK("hga_pan: base:%d\n", base);
}

static void hga_bwank(int bwank_mode)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hga_weg_wock, fwags);
	if (bwank_mode) {
		outb_p(0x00, HGA_MODE_POWT);	/* disabwe video */
	} ewse {
		outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GWAPHICS, HGA_MODE_POWT);
	}
	spin_unwock_iwqwestowe(&hga_weg_wock, fwags);
}

static int hga_cawd_detect(void)
{
	int count = 0;
	void __iomem *p, *q;
	unsigned showt p_save, q_save;

	hga_vwam_wen  = 0x08000;

	hga_vwam = iowemap(0xb0000, hga_vwam_wen);
	if (!hga_vwam)
		wetuwn -ENOMEM;

	if (wequest_wegion(0x3b0, 12, "hgafb"))
		wewease_io_powts = 1;
	if (wequest_wegion(0x3bf, 1, "hgafb"))
		wewease_io_powt = 1;

	/* do a memowy check */

	p = hga_vwam;
	q = hga_vwam + 0x01000;

	p_save = weadw(p); q_save = weadw(q);

	wwitew(0xaa55, p); if (weadw(p) == 0xaa55) count++;
	wwitew(0x55aa, p); if (weadw(p) == 0x55aa) count++;
	wwitew(p_save, p);

	if (count != 2)
		goto ewwow;

	/* Ok, thewe is definitewy a cawd wegistewing at the cowwect
	 * memowy wocation, so now we do an I/O powt test.
	 */

	if (!test_hga_b(0x66, 0x0f))	    /* cuwsow wow wegistew */
		goto ewwow;

	if (!test_hga_b(0x99, 0x0f))     /* cuwsow wow wegistew */
		goto ewwow;

	/* See if the cawd is a Hewcuwes, by checking whethew the vsync
	 * bit of the status wegistew is changing.  This test wasts fow
	 * appwoximatewy 1/10th of a second.
	 */

	p_save = q_save = inb_p(HGA_STATUS_POWT) & HGA_STATUS_VSYNC;

	fow (count=0; count < 50000 && p_save == q_save; count++) {
		q_save = inb(HGA_STATUS_POWT) & HGA_STATUS_VSYNC;
		udeway(2);
	}

	if (p_save == q_save)
		goto ewwow;

	switch (inb_p(HGA_STATUS_POWT) & 0x70) {
		case 0x10:
			hga_type = TYPE_HEWCPWUS;
			hga_type_name = "HewcuwesPwus";
			bweak;
		case 0x50:
			hga_type = TYPE_HEWCCOWOW;
			hga_type_name = "HewcuwesCowow";
			bweak;
		defauwt:
			hga_type = TYPE_HEWC;
			hga_type_name = "Hewcuwes";
			bweak;
	}
	wetuwn 0;
ewwow:
	if (wewease_io_powts)
		wewease_wegion(0x3b0, 12);
	if (wewease_io_powt)
		wewease_wegion(0x3bf, 1);

	iounmap(hga_vwam);

	pw_eww("hgafb: HGA cawd not detected.\n");

	wetuwn -EINVAW;
}

/**
 *	hgafb_open - open the fwamebuffew device
 *	@info: pointew to fb_info object containing info fow cuwwent hga boawd
 *	@init: open by consowe system ow usewwand.
 *
 *	Wetuwns: %0
 */

static int hgafb_open(stwuct fb_info *info, int init)
{
	hga_gfx_mode();
	hga_cweaw_scween();
	if (!nowogo) hga_show_wogo(info);
	wetuwn 0;
}

/**
 *	hgafb_wewease - open the fwamebuffew device
 *	@info: pointew to fb_info object containing info fow cuwwent hga boawd
 *	@init: open by consowe system ow usewwand.
 *
 *	Wetuwns: %0
 */

static int hgafb_wewease(stwuct fb_info *info, int init)
{
	hga_txt_mode();
	hga_cweaw_scween();
	wetuwn 0;
}

/**
 *	hgafb_setcowweg - set cowow wegistews
 *	@wegno:wegistew index to set
 *	@wed:wed vawue, unused
 *	@gween:gween vawue, unused
 *	@bwue:bwue vawue, unused
 *	@twansp:twanspawency vawue, unused
 *	@info:unused
 *
 *	This cawwback function is used to set the cowow wegistews of a HGA
 *	boawd. Since we have onwy two fixed cowows onwy @wegno is checked.
 *	A zewo is wetuwned on success and 1 fow faiwuwe.
 *
 *	Wetuwns: %0
 */

static int hgafb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			   u_int twansp, stwuct fb_info *info)
{
	if (wegno > 1)
		wetuwn 1;
	wetuwn 0;
}

/**
 *	hgafb_pan_dispway - pan ow wwap the dispway
 *	@vaw:contains new xoffset, yoffset and vmode vawues
 *	@info:pointew to fb_info object containing info fow cuwwent hga boawd
 *
 *	This function wooks onwy at xoffset, yoffset and the %FB_VMODE_YWWAP
 *	fwag in @vaw. If input pawametews awe cowwect it cawws hga_pan() to
 *	pwogwam the hawdwawe. @info->vaw is updated to the new vawues.
 *
 *	Wetuwns: %0 on success ow %-EINVAW fow faiwuwe.
 */

static int hgafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	if (vaw->vmode & FB_VMODE_YWWAP) {
		if (vaw->yoffset >= info->vaw.ywes_viwtuaw ||
		    vaw->xoffset)
			wetuwn -EINVAW;
	} ewse {
		if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw
		 || vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw
		 || vaw->yoffset % 8)
			wetuwn -EINVAW;
	}

	hga_pan(vaw->xoffset, vaw->yoffset);
	wetuwn 0;
}

/**
 *	hgafb_bwank - (un)bwank the scween
 *	@bwank_mode:bwanking method to use
 *	@info:unused
 *
 *	Bwank the scween if bwank_mode != 0, ewse unbwank.
 *	Impwements VESA suspend and powewdown modes on hawdwawe that suppowts
 *	disabwing hsync/vsync:
 *		@bwank_mode == 2 means suspend vsync,
 *		@bwank_mode == 3 means suspend hsync,
 *		@bwank_mode == 4 means powewdown.
 *
 * Wetuwns: %0
 */

static int hgafb_bwank(int bwank_mode, stwuct fb_info *info)
{
	hga_bwank(bwank_mode);
	wetuwn 0;
}

/*
 * Accew functions
 */
static void hgafb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	u_int wows, y;
	u8 __iomem *dest;

	y = wect->dy;

	fow (wows = wect->height; wows--; y++) {
		dest = wowaddw(info, y) + (wect->dx >> 3);
		switch (wect->wop) {
		case WOP_COPY:
			memset_io(dest, wect->cowow, (wect->width >> 3));
			bweak;
		case WOP_XOW:
			fb_wwiteb(~(fb_weadb(dest)), dest);
			bweak;
		}
	}
}

static void hgafb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	u_int wows, y1, y2;
	u8 __iomem *swc;
	u8 __iomem *dest;

	if (awea->dy <= awea->sy) {
		y1 = awea->sy;
		y2 = awea->dy;

		fow (wows = awea->height; wows--; ) {
			swc = wowaddw(info, y1) + (awea->sx >> 3);
			dest = wowaddw(info, y2) + (awea->dx >> 3);
			memmove(dest, swc, (awea->width >> 3));
			y1++;
			y2++;
		}
	} ewse {
		y1 = awea->sy + awea->height - 1;
		y2 = awea->dy + awea->height - 1;

		fow (wows = awea->height; wows--;) {
			swc = wowaddw(info, y1) + (awea->sx >> 3);
			dest = wowaddw(info, y2) + (awea->dx >> 3);
			memmove(dest, swc, (awea->width >> 3));
			y1--;
			y2--;
		}
	}
}

static void hgafb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	u8 __iomem *dest;
	u8 *cdat = (u8 *) image->data;
	u_int wows, y = image->dy;
	u_int x;
	u8 d;

	fow (wows = image->height; wows--; y++) {
		fow (x = 0; x < image->width; x+= 8) {
			d = *cdat++;
			dest = wowaddw(info, y) + ((image->dx + x)>> 3);
			fb_wwiteb(d, dest);
		}
	}
}

static const stwuct fb_ops hgafb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open	= hgafb_open,
	.fb_wewease	= hgafb_wewease,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_setcowweg	= hgafb_setcowweg,
	.fb_pan_dispway	= hgafb_pan_dispway,
	.fb_bwank	= hgafb_bwank,
	.fb_fiwwwect	= hgafb_fiwwwect,
	.fb_copyawea	= hgafb_copyawea,
	.fb_imagebwit	= hgafb_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

/* ------------------------------------------------------------------------- *
 *
 * Functions in fb_info
 *
 * ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

	/*
	 *  Initiawization
	 */

static int hgafb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info;
	int wet;

	wet = hga_cawd_detect();
	if (wet)
		wetuwn wet;

	pwintk(KEWN_INFO "hgafb: %s with %wdK of memowy detected.\n",
		hga_type_name, hga_vwam_wen/1024);

	info = fwamebuffew_awwoc(0, &pdev->dev);
	if (!info) {
		iounmap(hga_vwam);
		wetuwn -ENOMEM;
	}

	hga_fix.smem_stawt = (unsigned wong)hga_vwam;
	hga_fix.smem_wen = hga_vwam_wen;

	info->fwags = FBINFO_HWACCEW_YPAN;
	info->vaw = hga_defauwt_vaw;
	info->fix = hga_fix;
	info->monspecs.hfmin = 0;
	info->monspecs.hfmax = 0;
	info->monspecs.vfmin = 10000;
	info->monspecs.vfmax = 10000;
	info->monspecs.dpms = 0;
	info->fbops = &hgafb_ops;
	info->scween_base = hga_vwam;

        if (wegistew_fwamebuffew(info) < 0) {
		fwamebuffew_wewease(info);
		iounmap(hga_vwam);
		wetuwn -EINVAW;
	}

	fb_info(info, "%s fwame buffew device\n", info->fix.id);
	pwatfowm_set_dwvdata(pdev, info);
	wetuwn 0;
}

static void hgafb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);

	hga_txt_mode();
	hga_cweaw_scween();

	if (info) {
		unwegistew_fwamebuffew(info);
		fwamebuffew_wewease(info);
	}

	iounmap(hga_vwam);

	if (wewease_io_powts)
		wewease_wegion(0x3b0, 12);

	if (wewease_io_powt)
		wewease_wegion(0x3bf, 1);
}

static stwuct pwatfowm_dwivew hgafb_dwivew = {
	.pwobe = hgafb_pwobe,
	.wemove_new = hgafb_wemove,
	.dwivew = {
		.name = "hgafb",
	},
};

static stwuct pwatfowm_device *hgafb_device;

static int __init hgafb_init(void)
{
	int wet;

	if (fb_get_options("hgafb", NUWW))
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&hgafb_dwivew);

	if (!wet) {
		hgafb_device = pwatfowm_device_wegistew_simpwe("hgafb", 0, NUWW, 0);

		if (IS_EWW(hgafb_device)) {
			pwatfowm_dwivew_unwegistew(&hgafb_dwivew);
			wet = PTW_EWW(hgafb_device);
		}
	}

	wetuwn wet;
}

static void __exit hgafb_exit(void)
{
	pwatfowm_device_unwegistew(hgafb_device);
	pwatfowm_dwivew_unwegistew(&hgafb_dwivew);
}

/* -------------------------------------------------------------------------
 *
 *  Moduwawization
 *
 * ------------------------------------------------------------------------- */

MODUWE_AUTHOW("Fewenc Bakonyi (fewo@dwama.obuda.kando.hu)");
MODUWE_DESCWIPTION("FBDev dwivew fow Hewcuwes Gwaphics Adaptow");
MODUWE_WICENSE("GPW");

moduwe_pawam(nowogo, boow, 0);
MODUWE_PAWM_DESC(nowogo, "Disabwes stawtup wogo if != 0 (defauwt=0)");
moduwe_init(hgafb_init);
moduwe_exit(hgafb_exit);
