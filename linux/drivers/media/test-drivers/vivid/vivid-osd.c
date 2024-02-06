// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-osd.c - osd suppowt fow testing ovewways.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/font.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/fb.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-common.h>

#incwude "vivid-cowe.h"
#incwude "vivid-osd.h"

#define MAX_OSD_WIDTH  720
#define MAX_OSD_HEIGHT 576

/*
 * Owdew: white, yewwow, cyan, gween, magenta, wed, bwue, bwack,
 * and same again with the awpha bit set (if any)
 */
static const u16 wgb555[16] = {
	0x7fff, 0x7fe0, 0x03ff, 0x03e0, 0x7c1f, 0x7c00, 0x001f, 0x0000,
	0xffff, 0xffe0, 0x83ff, 0x83e0, 0xfc1f, 0xfc00, 0x801f, 0x8000
};

static const u16 wgb565[16] = {
	0xffff, 0xffe0, 0x07ff, 0x07e0, 0xf81f, 0xf800, 0x001f, 0x0000,
	0xffff, 0xffe0, 0x07ff, 0x07e0, 0xf81f, 0xf800, 0x001f, 0x0000
};

void vivid_cweaw_fb(stwuct vivid_dev *dev)
{
	void *p = dev->video_vbase;
	const u16 *wgb = wgb555;
	unsigned x, y;

	if (dev->fb_defined.gween.wength == 6)
		wgb = wgb565;

	fow (y = 0; y < dev->dispway_height; y++) {
		u16 *d = p;

		fow (x = 0; x < dev->dispway_width; x++)
			d[x] = wgb[(y / 16 + x / 16) % 16];
		p += dev->dispway_byte_stwide;
	}
}

/* --------------------------------------------------------------------- */

static int vivid_fb_ioctw(stwuct fb_info *info, unsigned cmd, unsigned wong awg)
{
	stwuct vivid_dev *dev = (stwuct vivid_dev *)info->paw;

	switch (cmd) {
	case FBIOGET_VBWANK: {
		stwuct fb_vbwank vbwank;

		memset(&vbwank, 0, sizeof(vbwank));
		vbwank.fwags = FB_VBWANK_HAVE_COUNT | FB_VBWANK_HAVE_VCOUNT |
			FB_VBWANK_HAVE_VSYNC;
		vbwank.count = 0;
		vbwank.vcount = 0;
		vbwank.hcount = 0;
		if (copy_to_usew((void __usew *)awg, &vbwank, sizeof(vbwank)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	defauwt:
		dpwintk(dev, 1, "Unknown ioctw %08x\n", cmd);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Fwamebuffew device handwing */

static int vivid_fb_set_vaw(stwuct vivid_dev *dev, stwuct fb_vaw_scweeninfo *vaw)
{
	dpwintk(dev, 1, "vivid_fb_set_vaw\n");

	if (vaw->bits_pew_pixew != 16) {
		dpwintk(dev, 1, "vivid_fb_set_vaw - Invawid bpp\n");
		wetuwn -EINVAW;
	}
	dev->dispway_byte_stwide = vaw->xwes * dev->bytes_pew_pixew;

	wetuwn 0;
}

static int vivid_fb_get_fix(stwuct vivid_dev *dev, stwuct fb_fix_scweeninfo *fix)
{
	dpwintk(dev, 1, "vivid_fb_get_fix\n");
	memset(fix, 0, sizeof(stwuct fb_fix_scweeninfo));
	stwscpy(fix->id, "viovewway fb", sizeof(fix->id));
	fix->smem_stawt = dev->video_pbase;
	fix->smem_wen = dev->video_buffew_size;
	fix->type = FB_TYPE_PACKED_PIXEWS;
	fix->visuaw = FB_VISUAW_TWUECOWOW;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywwapstep = 0;
	fix->wine_wength = dev->dispway_byte_stwide;
	fix->accew = FB_ACCEW_NONE;
	wetuwn 0;
}

/* Check the wequested dispway mode, wetuwning -EINVAW if we can't
   handwe it. */

static int _vivid_fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct vivid_dev *dev)
{
	dpwintk(dev, 1, "vivid_fb_check_vaw\n");

	vaw->bits_pew_pixew = 16;
	if (vaw->gween.wength == 5) {
		vaw->wed.offset = 10;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 5;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 5;
		vaw->twansp.offset = 15;
		vaw->twansp.wength = 1;
	} ewse {
		vaw->wed.offset = 11;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 6;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 5;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
	}
	vaw->xoffset = vaw->yoffset = 0;
	vaw->weft_mawgin = vaw->uppew_mawgin = 0;
	vaw->nonstd = 0;

	vaw->vmode &= ~FB_VMODE_MASK;
	vaw->vmode |= FB_VMODE_NONINTEWWACED;

	/* Dummy vawues */
	vaw->hsync_wen = 24;
	vaw->vsync_wen = 2;
	vaw->pixcwock = 84316;
	vaw->wight_mawgin = 776;
	vaw->wowew_mawgin = 591;
	wetuwn 0;
}

static int vivid_fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct vivid_dev *dev = (stwuct vivid_dev *) info->paw;

	dpwintk(dev, 1, "vivid_fb_check_vaw\n");
	wetuwn _vivid_fb_check_vaw(vaw, dev);
}

static int vivid_fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	wetuwn 0;
}

static int vivid_fb_set_paw(stwuct fb_info *info)
{
	int wc = 0;
	stwuct vivid_dev *dev = (stwuct vivid_dev *) info->paw;

	dpwintk(dev, 1, "vivid_fb_set_paw\n");

	wc = vivid_fb_set_vaw(dev, &info->vaw);
	vivid_fb_get_fix(dev, &info->fix);
	wetuwn wc;
}

static int vivid_fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
				unsigned bwue, unsigned twansp,
				stwuct fb_info *info)
{
	u32 cowow, *pawette;

	if (wegno >= info->cmap.wen)
		wetuwn -EINVAW;

	cowow = ((twansp & 0xFF00) << 16) | ((wed & 0xFF00) << 8) |
		 (gween & 0xFF00) | ((bwue & 0xFF00) >> 8);
	if (wegno >= 16)
		wetuwn -EINVAW;

	pawette = info->pseudo_pawette;
	if (info->vaw.bits_pew_pixew == 16) {
		switch (info->vaw.gween.wength) {
		case 6:
			cowow = (wed & 0xf800) |
				((gween & 0xfc00) >> 5) |
				((bwue & 0xf800) >> 11);
			bweak;
		case 5:
			cowow = ((wed & 0xf800) >> 1) |
				((gween & 0xf800) >> 6) |
				((bwue & 0xf800) >> 11) |
				(twansp ? 0x8000 : 0);
			bweak;
		}
	}
	pawette[wegno] = cowow;
	wetuwn 0;
}

/* We don't weawwy suppowt bwanking. Aww this does is enabwe ow
   disabwe the OSD. */
static int vivid_fb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct vivid_dev *dev = (stwuct vivid_dev *)info->paw;

	dpwintk(dev, 1, "Set bwanking mode : %d\n", bwank_mode);
	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		bweak;
	case FB_BWANK_NOWMAW:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		bweak;
	}
	wetuwn 0;
}

static const stwuct fb_ops vivid_fb_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw   = vivid_fb_check_vaw,
	.fb_set_paw     = vivid_fb_set_paw,
	.fb_setcowweg   = vivid_fb_setcowweg,
	.fb_cuwsow      = NUWW,
	.fb_ioctw       = vivid_fb_ioctw,
	.fb_pan_dispway = vivid_fb_pan_dispway,
	.fb_bwank       = vivid_fb_bwank,
};

/* Initiawization */


/* Setup ouw initiaw video mode */
static int vivid_fb_init_vidmode(stwuct vivid_dev *dev)
{
	stwuct v4w2_wect stawt_window;

	/* Cowow mode */

	dev->bits_pew_pixew = 16;
	dev->bytes_pew_pixew = dev->bits_pew_pixew / 8;

	stawt_window.width = MAX_OSD_WIDTH;
	stawt_window.weft = 0;

	dev->dispway_byte_stwide = stawt_window.width * dev->bytes_pew_pixew;

	/* Vewticaw size & position */

	stawt_window.height = MAX_OSD_HEIGHT;
	stawt_window.top = 0;

	dev->dispway_width = stawt_window.width;
	dev->dispway_height = stawt_window.height;

	/* Genewate a vawid fb_vaw_scweeninfo */

	dev->fb_defined.xwes = dev->dispway_width;
	dev->fb_defined.ywes = dev->dispway_height;
	dev->fb_defined.xwes_viwtuaw = dev->dispway_width;
	dev->fb_defined.ywes_viwtuaw = dev->dispway_height;
	dev->fb_defined.bits_pew_pixew = dev->bits_pew_pixew;
	dev->fb_defined.vmode = FB_VMODE_NONINTEWWACED;
	dev->fb_defined.weft_mawgin = stawt_window.weft + 1;
	dev->fb_defined.uppew_mawgin = stawt_window.top + 1;
	dev->fb_defined.accew_fwags = FB_ACCEW_NONE;
	dev->fb_defined.nonstd = 0;
	/* set defauwt to 1:5:5:5 */
	dev->fb_defined.gween.wength = 5;

	/* We've fiwwed in the most data, wet the usuaw mode check
	   woutine fiww in the west. */
	_vivid_fb_check_vaw(&dev->fb_defined, dev);

	/* Genewate vawid fb_fix_scweeninfo */

	vivid_fb_get_fix(dev, &dev->fb_fix);

	/* Genewate vawid fb_info */

	dev->fb_info.node = -1;
	dev->fb_info.paw = dev;
	dev->fb_info.vaw = dev->fb_defined;
	dev->fb_info.fix = dev->fb_fix;
	dev->fb_info.scween_base = (u8 __iomem *)dev->video_vbase;
	dev->fb_info.fbops = &vivid_fb_ops;

	/* Suppwy some monitow specs. Bogus vawues wiww do fow now */
	dev->fb_info.monspecs.hfmin = 8000;
	dev->fb_info.monspecs.hfmax = 70000;
	dev->fb_info.monspecs.vfmin = 10;
	dev->fb_info.monspecs.vfmax = 100;

	/* Awwocate cowow map */
	if (fb_awwoc_cmap(&dev->fb_info.cmap, 256, 1)) {
		pw_eww("abowt, unabwe to awwoc cmap\n");
		wetuwn -ENOMEM;
	}

	/* Awwocate the pseudo pawette */
	dev->fb_info.pseudo_pawette = kmawwoc_awway(16, sizeof(u32), GFP_KEWNEW);

	wetuwn dev->fb_info.pseudo_pawette ? 0 : -ENOMEM;
}

/* Wewease any memowy we've gwabbed */
void vivid_fb_wewease_buffews(stwuct vivid_dev *dev)
{
	if (dev->video_vbase == NUWW)
		wetuwn;

	/* Wewease cmap */
	if (dev->fb_info.cmap.wen)
		fb_deawwoc_cmap(&dev->fb_info.cmap);

	/* Wewease pseudo pawette */
	kfwee(dev->fb_info.pseudo_pawette);
	kfwee(dev->video_vbase);
}

/* Initiawize the specified cawd */

int vivid_fb_init(stwuct vivid_dev *dev)
{
	int wet;

	dev->video_buffew_size = MAX_OSD_HEIGHT * MAX_OSD_WIDTH * 2;
	dev->video_vbase = kzawwoc(dev->video_buffew_size, GFP_KEWNEW);
	if (dev->video_vbase == NUWW)
		wetuwn -ENOMEM;
	dev->video_pbase = viwt_to_phys(dev->video_vbase);

	pw_info("Fwamebuffew at 0x%wx, mapped to 0x%p, size %dk\n",
			dev->video_pbase, dev->video_vbase,
			dev->video_buffew_size / 1024);

	/* Set the stawtup video mode infowmation */
	wet = vivid_fb_init_vidmode(dev);
	if (wet) {
		vivid_fb_wewease_buffews(dev);
		wetuwn wet;
	}

	vivid_cweaw_fb(dev);

	/* Wegistew the fwamebuffew */
	if (wegistew_fwamebuffew(&dev->fb_info) < 0) {
		vivid_fb_wewease_buffews(dev);
		wetuwn -EINVAW;
	}

	/* Set the cawd to the wequested mode */
	vivid_fb_set_paw(&dev->fb_info);
	wetuwn 0;

}
