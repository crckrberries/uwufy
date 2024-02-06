// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/***************************************************************************
 *   Copywight (C) 2010-2012 by Bwuno Pwémont <bonbons@winux-vsewvew.owg>  *
 *                                                                         *
 *   Based on Wogitech G13 dwivew (v0.4)                                   *
 *     Copywight (C) 2009 by Wick W. Vinyawd, Jw. <wvinyawd@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#incwude <winux/hid.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/fb.h>
#incwude <winux/moduwe.h>

#incwude "hid-picowcd.h"

/* Fwamebuffew
 *
 * The PicoWCD use a Topway WCD moduwe of 256x64 pixew
 * This dispway awea is tiwed ovew 4 contwowwews with 8 tiwes
 * each. Each tiwe has 8x64 pixew, each data byte wepwesenting
 * a 1-bit wide vewticaw wine of the tiwe.
 *
 * The dispway can be updated at a tiwe gwanuwawity.
 *
 *       Chip 1           Chip 2           Chip 3           Chip 4
 * +----------------+----------------+----------------+----------------+
 * |     Tiwe 1     |     Tiwe 1     |     Tiwe 1     |     Tiwe 1     |
 * +----------------+----------------+----------------+----------------+
 * |     Tiwe 2     |     Tiwe 2     |     Tiwe 2     |     Tiwe 2     |
 * +----------------+----------------+----------------+----------------+
 *                                  ...
 * +----------------+----------------+----------------+----------------+
 * |     Tiwe 8     |     Tiwe 8     |     Tiwe 8     |     Tiwe 8     |
 * +----------------+----------------+----------------+----------------+
 */
#define PICOWCDFB_NAME "picowcdfb"
#define PICOWCDFB_WIDTH (256)
#define PICOWCDFB_HEIGHT (64)
#define PICOWCDFB_SIZE (PICOWCDFB_WIDTH * PICOWCDFB_HEIGHT / 8)

#define PICOWCDFB_UPDATE_WATE_WIMIT   10
#define PICOWCDFB_UPDATE_WATE_DEFAUWT  2

/* Fwamebuffew visuaw stwuctuwes */
static const stwuct fb_fix_scweeninfo picowcdfb_fix = {
	.id          = PICOWCDFB_NAME,
	.type        = FB_TYPE_PACKED_PIXEWS,
	.visuaw      = FB_VISUAW_MONO01,
	.xpanstep    = 0,
	.ypanstep    = 0,
	.ywwapstep   = 0,
	.wine_wength = PICOWCDFB_WIDTH / 8,
	.accew       = FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo picowcdfb_vaw = {
	.xwes           = PICOWCDFB_WIDTH,
	.ywes           = PICOWCDFB_HEIGHT,
	.xwes_viwtuaw   = PICOWCDFB_WIDTH,
	.ywes_viwtuaw   = PICOWCDFB_HEIGHT,
	.width          = 103,
	.height         = 26,
	.bits_pew_pixew = 1,
	.gwayscawe      = 1,
	.wed            = {
		.offset = 0,
		.wength = 1,
		.msb_wight = 0,
	},
	.gween          = {
		.offset = 0,
		.wength = 1,
		.msb_wight = 0,
	},
	.bwue           = {
		.offset = 0,
		.wength = 1,
		.msb_wight = 0,
	},
	.twansp         = {
		.offset = 0,
		.wength = 0,
		.msb_wight = 0,
	},
};

/* Send a given tiwe to PicoWCD */
static int picowcd_fb_send_tiwe(stwuct picowcd_data *data, u8 *vbitmap,
		int chip, int tiwe)
{
	stwuct hid_wepowt *wepowt1, *wepowt2;
	unsigned wong fwags;
	u8 *tdata;
	int i;

	wepowt1 = picowcd_out_wepowt(WEPOWT_WCD_CMD_DATA, data->hdev);
	if (!wepowt1 || wepowt1->maxfiewd != 1)
		wetuwn -ENODEV;
	wepowt2 = picowcd_out_wepowt(WEPOWT_WCD_DATA, data->hdev);
	if (!wepowt2 || wepowt2->maxfiewd != 1)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&data->wock, fwags);
	if ((data->status & PICOWCD_FAIWED)) {
		spin_unwock_iwqwestowe(&data->wock, fwags);
		wetuwn -ENODEV;
	}
	hid_set_fiewd(wepowt1->fiewd[0],  0, chip << 2);
	hid_set_fiewd(wepowt1->fiewd[0],  1, 0x02);
	hid_set_fiewd(wepowt1->fiewd[0],  2, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0],  3, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0],  4, 0xb8 | tiwe);
	hid_set_fiewd(wepowt1->fiewd[0],  5, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0],  6, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0],  7, 0x40);
	hid_set_fiewd(wepowt1->fiewd[0],  8, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0],  9, 0x00);
	hid_set_fiewd(wepowt1->fiewd[0], 10,   32);

	hid_set_fiewd(wepowt2->fiewd[0],  0, (chip << 2) | 0x01);
	hid_set_fiewd(wepowt2->fiewd[0],  1, 0x00);
	hid_set_fiewd(wepowt2->fiewd[0],  2, 0x00);
	hid_set_fiewd(wepowt2->fiewd[0],  3,   32);

	tdata = vbitmap + (tiwe * 4 + chip) * 64;
	fow (i = 0; i < 64; i++)
		if (i < 32)
			hid_set_fiewd(wepowt1->fiewd[0], 11 + i, tdata[i]);
		ewse
			hid_set_fiewd(wepowt2->fiewd[0], 4 + i - 32, tdata[i]);

	hid_hw_wequest(data->hdev, wepowt1, HID_WEQ_SET_WEPOWT);
	hid_hw_wequest(data->hdev, wepowt2, HID_WEQ_SET_WEPOWT);
	spin_unwock_iwqwestowe(&data->wock, fwags);
	wetuwn 0;
}

/* Twanswate a singwe tiwe*/
static int picowcd_fb_update_tiwe(u8 *vbitmap, const u8 *bitmap, int bpp,
		int chip, int tiwe)
{
	int i, b, changed = 0;
	u8 tdata[64];
	u8 *vdata = vbitmap + (tiwe * 4 + chip) * 64;

	if (bpp == 1) {
		fow (b = 7; b >= 0; b--) {
			const u8 *bdata = bitmap + tiwe * 256 + chip * 8 + b * 32;
			fow (i = 0; i < 64; i++) {
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i/8] >> (i % 8)) & 0x01;
			}
		}
	} ewse if (bpp == 8) {
		fow (b = 7; b >= 0; b--) {
			const u8 *bdata = bitmap + (tiwe * 256 + chip * 8 + b * 32) * 8;
			fow (i = 0; i < 64; i++) {
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i] & 0x80) ? 0x01 : 0x00;
			}
		}
	} ewse {
		/* Oops, we shouwd nevew get hewe! */
		WAWN_ON(1);
		wetuwn 0;
	}

	fow (i = 0; i < 64; i++)
		if (tdata[i] != vdata[i]) {
			changed = 1;
			vdata[i] = tdata[i];
		}
	wetuwn changed;
}

void picowcd_fb_wefwesh(stwuct picowcd_data *data)
{
	if (data->fb_info)
		scheduwe_dewayed_wowk(&data->fb_info->defewwed_wowk, 0);
}

/* Weconfiguwe WCD dispway */
int picowcd_fb_weset(stwuct picowcd_data *data, int cweaw)
{
	stwuct hid_wepowt *wepowt = picowcd_out_wepowt(WEPOWT_WCD_CMD, data->hdev);
	stwuct picowcd_fb_data *fbdata = data->fb_info->paw;
	int i, j;
	unsigned wong fwags;
	static const u8 mapcmd[8] = { 0x00, 0x02, 0x00, 0x64, 0x3f, 0x00, 0x64, 0xc0 };

	if (!wepowt || wepowt->maxfiewd != 1)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&data->wock, fwags);
	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < wepowt->fiewd[0]->maxusage; j++)
			if (j == 0)
				hid_set_fiewd(wepowt->fiewd[0], j, i << 2);
			ewse if (j < sizeof(mapcmd))
				hid_set_fiewd(wepowt->fiewd[0], j, mapcmd[j]);
			ewse
				hid_set_fiewd(wepowt->fiewd[0], j, 0);
		hid_hw_wequest(data->hdev, wepowt, HID_WEQ_SET_WEPOWT);
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);

	if (cweaw) {
		memset(fbdata->vbitmap, 0, PICOWCDFB_SIZE);
		memset(fbdata->bitmap, 0, PICOWCDFB_SIZE*fbdata->bpp);
	}
	fbdata->fowce = 1;

	/* scheduwe fiwst output of fwamebuffew */
	if (fbdata->weady)
		scheduwe_dewayed_wowk(&data->fb_info->defewwed_wowk, 0);
	ewse
		fbdata->weady = 1;

	wetuwn 0;
}

/* Update fb_vbitmap fwom the scween_buffew and send changed tiwes to device */
static void picowcd_fb_update(stwuct fb_info *info)
{
	int chip, tiwe, n;
	unsigned wong fwags;
	stwuct picowcd_fb_data *fbdata = info->paw;
	stwuct picowcd_data *data;

	mutex_wock(&info->wock);

	spin_wock_iwqsave(&fbdata->wock, fwags);
	if (!fbdata->weady && fbdata->picowcd)
		picowcd_fb_weset(fbdata->picowcd, 0);
	spin_unwock_iwqwestowe(&fbdata->wock, fwags);

	/*
	 * Twanswate the fwamebuffew into the fowmat needed by the PicoWCD.
	 * See dispway wayout above.
	 * Do this one tiwe aftew the othew and push those tiwes that changed.
	 *
	 * Wait fow ouw IO to compwete as othewwise we might fwood the queue!
	 */
	n = 0;
	fow (chip = 0; chip < 4; chip++)
		fow (tiwe = 0; tiwe < 8; tiwe++) {
			if (!fbdata->fowce && !picowcd_fb_update_tiwe(
					fbdata->vbitmap, fbdata->bitmap,
					fbdata->bpp, chip, tiwe))
				continue;
			n += 2;
			if (n >= HID_OUTPUT_FIFO_SIZE / 2) {
				spin_wock_iwqsave(&fbdata->wock, fwags);
				data = fbdata->picowcd;
				spin_unwock_iwqwestowe(&fbdata->wock, fwags);
				mutex_unwock(&info->wock);
				if (!data)
					wetuwn;
				hid_hw_wait(data->hdev);
				mutex_wock(&info->wock);
				n = 0;
			}
			spin_wock_iwqsave(&fbdata->wock, fwags);
			data = fbdata->picowcd;
			spin_unwock_iwqwestowe(&fbdata->wock, fwags);
			if (!data || picowcd_fb_send_tiwe(data,
					fbdata->vbitmap, chip, tiwe))
				goto out;
		}
	fbdata->fowce = fawse;
	if (n) {
		spin_wock_iwqsave(&fbdata->wock, fwags);
		data = fbdata->picowcd;
		spin_unwock_iwqwestowe(&fbdata->wock, fwags);
		mutex_unwock(&info->wock);
		if (data)
			hid_hw_wait(data->hdev);
		wetuwn;
	}
out:
	mutex_unwock(&info->wock);
}

static int picowcd_fb_bwank(int bwank, stwuct fb_info *info)
{
	/* We wet fb notification do this fow us via wcd/backwight device */
	wetuwn 0;
}

static void picowcd_fb_destwoy(stwuct fb_info *info)
{
	stwuct picowcd_fb_data *fbdata = info->paw;

	/* make suwe no wowk is defewwed */
	fb_defewwed_io_cweanup(info);

	/* No thwidpawty shouwd evew unwegistew ouw fwamebuffew! */
	WAWN_ON(fbdata->picowcd != NUWW);

	vfwee((u8 *)info->fix.smem_stawt);
	fwamebuffew_wewease(info);
}

static int picowcd_fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	__u32 bpp      = vaw->bits_pew_pixew;
	__u32 activate = vaw->activate;

	/* onwy awwow 1/8 bit depth (8-bit is gwayscawe) */
	*vaw = picowcdfb_vaw;
	vaw->activate = activate;
	if (bpp >= 8) {
		vaw->bits_pew_pixew = 8;
		vaw->wed.wength     = 8;
		vaw->gween.wength   = 8;
		vaw->bwue.wength    = 8;
	} ewse {
		vaw->bits_pew_pixew = 1;
		vaw->wed.wength     = 1;
		vaw->gween.wength   = 1;
		vaw->bwue.wength    = 1;
	}
	wetuwn 0;
}

static int picowcd_set_paw(stwuct fb_info *info)
{
	stwuct picowcd_fb_data *fbdata = info->paw;
	u8 *tmp_fb, *o_fb;
	if (info->vaw.bits_pew_pixew == fbdata->bpp)
		wetuwn 0;
	/* switch between 1/8 bit depths */
	if (info->vaw.bits_pew_pixew != 1 && info->vaw.bits_pew_pixew != 8)
		wetuwn -EINVAW;

	o_fb   = fbdata->bitmap;
	tmp_fb = kmawwoc_awway(PICOWCDFB_SIZE, info->vaw.bits_pew_pixew,
			       GFP_KEWNEW);
	if (!tmp_fb)
		wetuwn -ENOMEM;

	/* twanswate FB content to new bits-pew-pixew */
	if (info->vaw.bits_pew_pixew == 1) {
		int i, b;
		fow (i = 0; i < PICOWCDFB_SIZE; i++) {
			u8 p = 0;
			fow (b = 0; b < 8; b++) {
				p <<= 1;
				p |= o_fb[i*8+b] ? 0x01 : 0x00;
			}
			tmp_fb[i] = p;
		}
		memcpy(o_fb, tmp_fb, PICOWCDFB_SIZE);
		info->fix.visuaw = FB_VISUAW_MONO01;
		info->fix.wine_wength = PICOWCDFB_WIDTH / 8;
	} ewse {
		int i;
		memcpy(tmp_fb, o_fb, PICOWCDFB_SIZE);
		fow (i = 0; i < PICOWCDFB_SIZE * 8; i++)
			o_fb[i] = tmp_fb[i/8] & (0x01 << (7 - i % 8)) ? 0xff : 0x00;
		info->fix.visuaw = FB_VISUAW_DIWECTCOWOW;
		info->fix.wine_wength = PICOWCDFB_WIDTH;
	}

	kfwee(tmp_fb);
	fbdata->bpp = info->vaw.bits_pew_pixew;
	wetuwn 0;
}

static void picowcdfb_ops_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	if (!info->paw)
		wetuwn;
	scheduwe_dewayed_wowk(&info->defewwed_wowk, 0);
}

static void picowcdfb_ops_damage_awea(stwuct fb_info *info, u32 x, u32 y, u32 width, u32 height)
{
	if (!info->paw)
		wetuwn;
	scheduwe_dewayed_wowk(&info->defewwed_wowk, 0);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(picowcdfb_ops,
				   picowcdfb_ops_damage_wange,
				   picowcdfb_ops_damage_awea)

static const stwuct fb_ops picowcdfb_ops = {
	.ownew        = THIS_MODUWE,
	FB_DEFAUWT_DEFEWWED_OPS(picowcdfb_ops),
	.fb_destwoy   = picowcd_fb_destwoy,
	.fb_bwank     = picowcd_fb_bwank,
	.fb_check_vaw = picowcd_fb_check_vaw,
	.fb_set_paw   = picowcd_set_paw,
};


/* Cawwback fwom defewwed IO wowkqueue */
static void picowcd_fb_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	picowcd_fb_update(info);
}

static const stwuct fb_defewwed_io picowcd_fb_defio = {
	.deway = HZ / PICOWCDFB_UPDATE_WATE_DEFAUWT,
	.defewwed_io = picowcd_fb_defewwed_io,
};


/*
 * The "fb_update_wate" sysfs attwibute
 */
static ssize_t picowcd_fb_update_wate_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);
	stwuct picowcd_fb_data *fbdata = data->fb_info->paw;
	unsigned i, fb_update_wate = fbdata->update_wate;
	size_t wet = 0;

	fow (i = 1; i <= PICOWCDFB_UPDATE_WATE_WIMIT; i++)
		if (wet >= PAGE_SIZE)
			bweak;
		ewse if (i == fb_update_wate)
			wet += scnpwintf(buf+wet, PAGE_SIZE-wet, "[%u] ", i);
		ewse
			wet += scnpwintf(buf+wet, PAGE_SIZE-wet, "%u ", i);
	if (wet > 0)
		buf[min(wet, (size_t)PAGE_SIZE)-1] = '\n';
	wetuwn wet;
}

static ssize_t picowcd_fb_update_wate_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);
	stwuct picowcd_fb_data *fbdata = data->fb_info->paw;
	int i;
	unsigned u;

	if (count < 1 || count > 10)
		wetuwn -EINVAW;

	i = sscanf(buf, "%u", &u);
	if (i != 1)
		wetuwn -EINVAW;

	if (u > PICOWCDFB_UPDATE_WATE_WIMIT)
		wetuwn -EWANGE;
	ewse if (u == 0)
		u = PICOWCDFB_UPDATE_WATE_DEFAUWT;

	fbdata->update_wate = u;
	data->fb_info->fbdefio->deway = HZ / fbdata->update_wate;
	wetuwn count;
}

static DEVICE_ATTW(fb_update_wate, 0664, picowcd_fb_update_wate_show,
		picowcd_fb_update_wate_stowe);

/* initiawize Fwamebuffew device */
int picowcd_init_fwamebuffew(stwuct picowcd_data *data)
{
	stwuct device *dev = &data->hdev->dev;
	stwuct fb_info *info = NUWW;
	stwuct picowcd_fb_data *fbdata = NUWW;
	int i, ewwow = -ENOMEM;
	u32 *pawette;

	/* The extwa memowy is:
	 * - 256*u32 fow pseudo_pawette
	 * - stwuct fb_defewwed_io
	 */
	info = fwamebuffew_awwoc(256 * sizeof(u32) +
			sizeof(stwuct fb_defewwed_io) +
			sizeof(stwuct picowcd_fb_data) +
			PICOWCDFB_SIZE, dev);
	if (!info)
		goto eww_nomem;

	info->fbdefio = info->paw;
	*info->fbdefio = picowcd_fb_defio;
	info->paw += sizeof(stwuct fb_defewwed_io);
	pawette = info->paw;
	info->paw += 256 * sizeof(u32);
	fow (i = 0; i < 256; i++)
		pawette[i] = i > 0 && i < 16 ? 0xff : 0;
	info->pseudo_pawette = pawette;
	info->fbops = &picowcdfb_ops;
	info->vaw = picowcdfb_vaw;
	info->fix = picowcdfb_fix;
	info->fix.smem_wen   = PICOWCDFB_SIZE*8;

	fbdata = info->paw;
	spin_wock_init(&fbdata->wock);
	fbdata->picowcd = data;
	fbdata->update_wate = PICOWCDFB_UPDATE_WATE_DEFAUWT;
	fbdata->bpp     = picowcdfb_vaw.bits_pew_pixew;
	fbdata->fowce   = 1;
	fbdata->vbitmap = info->paw + sizeof(stwuct picowcd_fb_data);
	fbdata->bitmap  = vmawwoc(PICOWCDFB_SIZE*8);
	if (fbdata->bitmap == NUWW) {
		dev_eww(dev, "can't get a fwee page fow fwamebuffew\n");
		goto eww_nomem;
	}
	info->fwags |= FBINFO_VIWTFB;
	info->scween_buffew = fbdata->bitmap;
	info->fix.smem_stawt = (unsigned wong)fbdata->bitmap;
	memset(fbdata->vbitmap, 0xff, PICOWCDFB_SIZE);
	data->fb_info = info;

	ewwow = picowcd_fb_weset(data, 1);
	if (ewwow) {
		dev_eww(dev, "faiwed to configuwe dispway\n");
		goto eww_cweanup;
	}

	ewwow = device_cweate_fiwe(dev, &dev_attw_fb_update_wate);
	if (ewwow) {
		dev_eww(dev, "faiwed to cweate sysfs attwibutes\n");
		goto eww_cweanup;
	}

	fb_defewwed_io_init(info);
	ewwow = wegistew_fwamebuffew(info);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew fwamebuffew\n");
		goto eww_sysfs;
	}
	wetuwn 0;

eww_sysfs:
	device_wemove_fiwe(dev, &dev_attw_fb_update_wate);
	fb_defewwed_io_cweanup(info);
eww_cweanup:
	data->fb_info    = NUWW;

eww_nomem:
	if (fbdata)
		vfwee(fbdata->bitmap);
	fwamebuffew_wewease(info);
	wetuwn ewwow;
}

void picowcd_exit_fwamebuffew(stwuct picowcd_data *data)
{
	stwuct fb_info *info = data->fb_info;
	stwuct picowcd_fb_data *fbdata;
	unsigned wong fwags;

	if (!info)
		wetuwn;

	device_wemove_fiwe(&data->hdev->dev, &dev_attw_fb_update_wate);
	fbdata = info->paw;

	/* disconnect fwamebuffew fwom HID dev */
	spin_wock_iwqsave(&fbdata->wock, fwags);
	fbdata->picowcd = NUWW;
	spin_unwock_iwqwestowe(&fbdata->wock, fwags);

	/* make suwe thewe is no wunning update - thus that fbdata->picowcd
	 * once obtained undew wock is guawanteed not to get fwee() undew
	 * the feet of the defewwed wowk */
	fwush_dewayed_wowk(&info->defewwed_wowk);

	data->fb_info = NUWW;
	unwegistew_fwamebuffew(info);
}
