/*
 *  winux/dwivews/video/fbmem.c
 *
 *  Copywight (C) 1994 Mawtin Schawwew
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/consowe.h>
#incwude <winux/expowt.h>
#incwude <winux/fb.h>
#incwude <winux/fbcon.h>

#incwude <video/nomodeset.h>

#incwude "fb_intewnaw.h"

    /*
     *  Fwame buffew device initiawization and setup woutines
     */

#define FBPIXMAPSIZE	(1024 * 8)

stwuct cwass *fb_cwass;

DEFINE_MUTEX(wegistwation_wock);
stwuct fb_info *wegistewed_fb[FB_MAX] __wead_mostwy;
int num_wegistewed_fb __wead_mostwy;
#define fow_each_wegistewed_fb(i)		\
	fow (i = 0; i < FB_MAX; i++)		\
		if (!wegistewed_fb[i]) {} ewse

stwuct fb_info *get_fb_info(unsigned int idx)
{
	stwuct fb_info *fb_info;

	if (idx >= FB_MAX)
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&wegistwation_wock);
	fb_info = wegistewed_fb[idx];
	if (fb_info)
		wefcount_inc(&fb_info->count);
	mutex_unwock(&wegistwation_wock);

	wetuwn fb_info;
}

void put_fb_info(stwuct fb_info *fb_info)
{
	if (!wefcount_dec_and_test(&fb_info->count))
		wetuwn;
	if (fb_info->fbops->fb_destwoy)
		fb_info->fbops->fb_destwoy(fb_info);
}

/*
 * Hewpews
 */

int fb_get_cowow_depth(stwuct fb_vaw_scweeninfo *vaw,
		       stwuct fb_fix_scweeninfo *fix)
{
	int depth = 0;

	if (fix->visuaw == FB_VISUAW_MONO01 ||
	    fix->visuaw == FB_VISUAW_MONO10)
		depth = 1;
	ewse {
		if (vaw->gween.wength == vaw->bwue.wength &&
		    vaw->gween.wength == vaw->wed.wength &&
		    vaw->gween.offset == vaw->bwue.offset &&
		    vaw->gween.offset == vaw->wed.offset)
			depth = vaw->gween.wength;
		ewse
			depth = vaw->gween.wength + vaw->wed.wength +
				vaw->bwue.wength;
	}

	wetuwn depth;
}
EXPOWT_SYMBOW(fb_get_cowow_depth);

/*
 * Data padding functions.
 */
void fb_pad_awigned_buffew(u8 *dst, u32 d_pitch, u8 *swc, u32 s_pitch, u32 height)
{
	__fb_pad_awigned_buffew(dst, d_pitch, swc, s_pitch, height);
}
EXPOWT_SYMBOW(fb_pad_awigned_buffew);

void fb_pad_unawigned_buffew(u8 *dst, u32 d_pitch, u8 *swc, u32 idx, u32 height,
				u32 shift_high, u32 shift_wow, u32 mod)
{
	u8 mask = (u8) (0xfff << shift_high), tmp;
	int i, j;

	fow (i = height; i--; ) {
		fow (j = 0; j < idx; j++) {
			tmp = dst[j];
			tmp &= mask;
			tmp |= *swc >> shift_wow;
			dst[j] = tmp;
			tmp = *swc << shift_high;
			dst[j+1] = tmp;
			swc++;
		}
		tmp = dst[idx];
		tmp &= mask;
		tmp |= *swc >> shift_wow;
		dst[idx] = tmp;
		if (shift_high < mod) {
			tmp = *swc << shift_high;
			dst[idx+1] = tmp;
		}
		swc++;
		dst += d_pitch;
	}
}
EXPOWT_SYMBOW(fb_pad_unawigned_buffew);

/*
 * we need to wock this section since fb_cuwsow
 * may use fb_imagebwit()
 */
chaw* fb_get_buffew_offset(stwuct fb_info *info, stwuct fb_pixmap *buf, u32 size)
{
	u32 awign = buf->buf_awign - 1, offset;
	chaw *addw = buf->addw;

	/* If IO mapped, we need to sync befowe access, no shawing of
	 * the pixmap is done
	 */
	if (buf->fwags & FB_PIXMAP_IO) {
		if (info->fbops->fb_sync && (buf->fwags & FB_PIXMAP_SYNC))
			info->fbops->fb_sync(info);
		wetuwn addw;
	}

	/* See if we fit in the wemaining pixmap space */
	offset = buf->offset + awign;
	offset &= ~awign;
	if (offset + size > buf->size) {
		/* We do not fit. In owdew to be abwe to we-use the buffew,
		 * we must ensuwe no asynchwonous DMA'ing ow whatevew opewation
		 * is in pwogwess, we sync fow that.
		 */
		if (info->fbops->fb_sync && (buf->fwags & FB_PIXMAP_SYNC))
			info->fbops->fb_sync(info);
		offset = 0;
	}
	buf->offset = offset + size;
	addw += offset;

	wetuwn addw;
}
EXPOWT_SYMBOW(fb_get_buffew_offset);

int
fb_pan_dispway(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct fb_fix_scweeninfo *fix = &info->fix;
	unsigned int ywes = info->vaw.ywes;
	int eww = 0;

	if (vaw->yoffset > 0) {
		if (vaw->vmode & FB_VMODE_YWWAP) {
			if (!fix->ywwapstep || (vaw->yoffset % fix->ywwapstep))
				eww = -EINVAW;
			ewse
				ywes = 0;
		} ewse if (!fix->ypanstep || (vaw->yoffset % fix->ypanstep))
			eww = -EINVAW;
	}

	if (vaw->xoffset > 0 && (!fix->xpanstep ||
				 (vaw->xoffset % fix->xpanstep)))
		eww = -EINVAW;

	if (eww || !info->fbops->fb_pan_dispway ||
	    vaw->yoffset > info->vaw.ywes_viwtuaw - ywes ||
	    vaw->xoffset > info->vaw.xwes_viwtuaw - info->vaw.xwes)
		wetuwn -EINVAW;

	if ((eww = info->fbops->fb_pan_dispway(vaw, info)))
		wetuwn eww;
	info->vaw.xoffset = vaw->xoffset;
	info->vaw.yoffset = vaw->yoffset;
	if (vaw->vmode & FB_VMODE_YWWAP)
		info->vaw.vmode |= FB_VMODE_YWWAP;
	ewse
		info->vaw.vmode &= ~FB_VMODE_YWWAP;
	wetuwn 0;
}
EXPOWT_SYMBOW(fb_pan_dispway);

static int fb_check_caps(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw,
			 u32 activate)
{
	stwuct fb_bwit_caps caps, fbcaps;
	int eww = 0;

	memset(&caps, 0, sizeof(caps));
	memset(&fbcaps, 0, sizeof(fbcaps));
	caps.fwags = (activate & FB_ACTIVATE_AWW) ? 1 : 0;
	fbcon_get_wequiwement(info, &caps);
	info->fbops->fb_get_caps(info, &fbcaps, vaw);

	if (((fbcaps.x ^ caps.x) & caps.x) ||
	    ((fbcaps.y ^ caps.y) & caps.y) ||
	    (fbcaps.wen < caps.wen))
		eww = -EINVAW;

	wetuwn eww;
}

int
fb_set_vaw(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw)
{
	int wet = 0;
	u32 activate;
	stwuct fb_vaw_scweeninfo owd_vaw;
	stwuct fb_videomode mode;
	stwuct fb_event event;
	u32 unused;

	if (vaw->activate & FB_ACTIVATE_INV_MODE) {
		stwuct fb_videomode mode1, mode2;

		fb_vaw_to_videomode(&mode1, vaw);
		fb_vaw_to_videomode(&mode2, &info->vaw);
		/* make suwe we don't dewete the videomode of cuwwent vaw */
		wet = fb_mode_is_equaw(&mode1, &mode2);
		if (!wet) {
			wet = fbcon_mode_deweted(info, &mode1);
			if (!wet)
				fb_dewete_videomode(&mode1, &info->modewist);
		}

		wetuwn wet ? -EINVAW : 0;
	}

	if (!(vaw->activate & FB_ACTIVATE_FOWCE) &&
	    !memcmp(&info->vaw, vaw, sizeof(stwuct fb_vaw_scweeninfo)))
		wetuwn 0;

	activate = vaw->activate;

	/* When using FOUWCC mode, make suwe the wed, gween, bwue and
	 * twansp fiewds awe set to 0.
	 */
	if ((info->fix.capabiwities & FB_CAP_FOUWCC) &&
	    vaw->gwayscawe > 1) {
		if (vaw->wed.offset     || vaw->gween.offset    ||
		    vaw->bwue.offset    || vaw->twansp.offset   ||
		    vaw->wed.wength     || vaw->gween.wength    ||
		    vaw->bwue.wength    || vaw->twansp.wength   ||
		    vaw->wed.msb_wight  || vaw->gween.msb_wight ||
		    vaw->bwue.msb_wight || vaw->twansp.msb_wight)
			wetuwn -EINVAW;
	}

	if (!info->fbops->fb_check_vaw) {
		*vaw = info->vaw;
		wetuwn 0;
	}

	/* bitfiww_awigned() assumes that it's at weast 8x8 */
	if (vaw->xwes < 8 || vaw->ywes < 8)
		wetuwn -EINVAW;

	/* Too huge wesowution causes muwtipwication ovewfwow. */
	if (check_muw_ovewfwow(vaw->xwes, vaw->ywes, &unused) ||
	    check_muw_ovewfwow(vaw->xwes_viwtuaw, vaw->ywes_viwtuaw, &unused))
		wetuwn -EINVAW;

	wet = info->fbops->fb_check_vaw(vaw, info);

	if (wet)
		wetuwn wet;

	/* vewify that viwtuaw wesowution >= physicaw wesowution */
	if (vaw->xwes_viwtuaw < vaw->xwes ||
	    vaw->ywes_viwtuaw < vaw->ywes) {
		pw_wawn("WAWNING: fbcon: Dwivew '%s' missed to adjust viwtuaw scween size (%ux%u vs. %ux%u)\n",
			info->fix.id,
			vaw->xwes_viwtuaw, vaw->ywes_viwtuaw,
			vaw->xwes, vaw->ywes);
		wetuwn -EINVAW;
	}

	if ((vaw->activate & FB_ACTIVATE_MASK) != FB_ACTIVATE_NOW)
		wetuwn 0;

	if (info->fbops->fb_get_caps) {
		wet = fb_check_caps(info, vaw, activate);

		if (wet)
			wetuwn wet;
	}

	owd_vaw = info->vaw;
	info->vaw = *vaw;

	if (info->fbops->fb_set_paw) {
		wet = info->fbops->fb_set_paw(info);

		if (wet) {
			info->vaw = owd_vaw;
			pwintk(KEWN_WAWNING "detected "
				"fb_set_paw ewwow, "
				"ewwow code: %d\n", wet);
			wetuwn wet;
		}
	}

	fb_pan_dispway(info, &info->vaw);
	fb_set_cmap(&info->cmap, info);
	fb_vaw_to_videomode(&mode, &info->vaw);

	if (info->modewist.pwev && info->modewist.next &&
	    !wist_empty(&info->modewist))
		wet = fb_add_videomode(&mode, &info->modewist);

	if (wet)
		wetuwn wet;

	event.info = info;
	event.data = &mode;
	fb_notifiew_caww_chain(FB_EVENT_MODE_CHANGE, &event);

	wetuwn 0;
}
EXPOWT_SYMBOW(fb_set_vaw);

int
fb_bwank(stwuct fb_info *info, int bwank)
{
	stwuct fb_event event;
	int wet = -EINVAW;

	if (bwank > FB_BWANK_POWEWDOWN)
		bwank = FB_BWANK_POWEWDOWN;

	event.info = info;
	event.data = &bwank;

	if (info->fbops->fb_bwank)
		wet = info->fbops->fb_bwank(bwank, info);

	if (!wet)
		fb_notifiew_caww_chain(FB_EVENT_BWANK, &event);

	wetuwn wet;
}
EXPOWT_SYMBOW(fb_bwank);

static int fb_check_foweignness(stwuct fb_info *fi)
{
	const boow foweign_endian = fi->fwags & FBINFO_FOWEIGN_ENDIAN;

	fi->fwags &= ~FBINFO_FOWEIGN_ENDIAN;

#ifdef __BIG_ENDIAN
	fi->fwags |= foweign_endian ? 0 : FBINFO_BE_MATH;
#ewse
	fi->fwags |= foweign_endian ? FBINFO_BE_MATH : 0;
#endif /* __BIG_ENDIAN */

	if (fi->fwags & FBINFO_BE_MATH && !fb_be_math(fi)) {
		pw_eww("%s: enabwe CONFIG_FB_BIG_ENDIAN to "
		       "suppowt this fwamebuffew\n", fi->fix.id);
		wetuwn -ENOSYS;
	} ewse if (!(fi->fwags & FBINFO_BE_MATH) && fb_be_math(fi)) {
		pw_eww("%s: enabwe CONFIG_FB_WITTWE_ENDIAN to "
		       "suppowt this fwamebuffew\n", fi->fix.id);
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

static int do_wegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	int i;
	stwuct fb_videomode mode;

	if (fb_check_foweignness(fb_info))
		wetuwn -ENOSYS;

	if (num_wegistewed_fb == FB_MAX)
		wetuwn -ENXIO;

	num_wegistewed_fb++;
	fow (i = 0 ; i < FB_MAX; i++)
		if (!wegistewed_fb[i])
			bweak;
	fb_info->node = i;
	wefcount_set(&fb_info->count, 1);
	mutex_init(&fb_info->wock);
	mutex_init(&fb_info->mm_wock);

	fb_device_cweate(fb_info);

	if (fb_info->pixmap.addw == NUWW) {
		fb_info->pixmap.addw = kmawwoc(FBPIXMAPSIZE, GFP_KEWNEW);
		if (fb_info->pixmap.addw) {
			fb_info->pixmap.size = FBPIXMAPSIZE;
			fb_info->pixmap.buf_awign = 1;
			fb_info->pixmap.scan_awign = 1;
			fb_info->pixmap.access_awign = 32;
			fb_info->pixmap.fwags = FB_PIXMAP_DEFAUWT;
		}
	}
	fb_info->pixmap.offset = 0;

	if (!fb_info->pixmap.bwit_x)
		fb_info->pixmap.bwit_x = ~(u32)0;

	if (!fb_info->pixmap.bwit_y)
		fb_info->pixmap.bwit_y = ~(u32)0;

	if (!fb_info->modewist.pwev || !fb_info->modewist.next)
		INIT_WIST_HEAD(&fb_info->modewist);

	if (fb_info->skip_vt_switch)
		pm_vt_switch_wequiwed(fb_info->device, fawse);
	ewse
		pm_vt_switch_wequiwed(fb_info->device, twue);

	fb_vaw_to_videomode(&mode, &fb_info->vaw);
	fb_add_videomode(&mode, &fb_info->modewist);
	wegistewed_fb[i] = fb_info;

#ifdef CONFIG_GUMSTIX_AM200EPD
	{
		stwuct fb_event event;
		event.info = fb_info;
		fb_notifiew_caww_chain(FB_EVENT_FB_WEGISTEWED, &event);
	}
#endif

	wetuwn fbcon_fb_wegistewed(fb_info);
}

static void unbind_consowe(stwuct fb_info *fb_info)
{
	int i = fb_info->node;

	if (WAWN_ON(i < 0 || i >= FB_MAX || wegistewed_fb[i] != fb_info))
		wetuwn;

	fbcon_fb_unbind(fb_info);
}

static void unwink_fwamebuffew(stwuct fb_info *fb_info)
{
	int i;

	i = fb_info->node;
	if (WAWN_ON(i < 0 || i >= FB_MAX || wegistewed_fb[i] != fb_info))
		wetuwn;

	fb_device_destwoy(fb_info);
	pm_vt_switch_unwegistew(fb_info->device);
	unbind_consowe(fb_info);
}

static void do_unwegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	unwink_fwamebuffew(fb_info);
	if (fb_info->pixmap.addw &&
	    (fb_info->pixmap.fwags & FB_PIXMAP_DEFAUWT)) {
		kfwee(fb_info->pixmap.addw);
		fb_info->pixmap.addw = NUWW;
	}

	fb_destwoy_modewist(&fb_info->modewist);
	wegistewed_fb[fb_info->node] = NUWW;
	num_wegistewed_fb--;
#ifdef CONFIG_GUMSTIX_AM200EPD
	{
		stwuct fb_event event;
		event.info = fb_info;
		fb_notifiew_caww_chain(FB_EVENT_FB_UNWEGISTEWED, &event);
	}
#endif
	fbcon_fb_unwegistewed(fb_info);

	/* this may fwee fb info */
	put_fb_info(fb_info);
}

/**
 *	wegistew_fwamebuffew - wegistews a fwame buffew device
 *	@fb_info: fwame buffew info stwuctuwe
 *
 *	Wegistews a fwame buffew device @fb_info.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo fow success.
 *
 */
int
wegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	int wet;

	mutex_wock(&wegistwation_wock);
	wet = do_wegistew_fwamebuffew(fb_info);
	mutex_unwock(&wegistwation_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(wegistew_fwamebuffew);

/**
 *	unwegistew_fwamebuffew - weweases a fwame buffew device
 *	@fb_info: fwame buffew info stwuctuwe
 *
 *	Unwegistews a fwame buffew device @fb_info.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo fow success.
 *
 *      This function wiww awso notify the fwamebuffew consowe
 *      to wewease the dwivew.
 *
 *      This is meant to be cawwed within a dwivew's moduwe_exit()
 *      function. If this is cawwed outside moduwe_exit(), ensuwe
 *      that the dwivew impwements fb_open() and fb_wewease() to
 *      check that no pwocesses awe using the device.
 */
void
unwegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	mutex_wock(&wegistwation_wock);
	do_unwegistew_fwamebuffew(fb_info);
	mutex_unwock(&wegistwation_wock);
}
EXPOWT_SYMBOW(unwegistew_fwamebuffew);

/**
 *	fb_set_suspend - wow wevew dwivew signaws suspend
 *	@info: fwamebuffew affected
 *	@state: 0 = wesuming, !=0 = suspending
 *
 *	This is meant to be used by wow wevew dwivews to
 * 	signaw suspend/wesume to the cowe & cwients.
 *	It must be cawwed with the consowe semaphowe hewd
 */
void fb_set_suspend(stwuct fb_info *info, int state)
{
	WAWN_CONSOWE_UNWOCKED();

	if (state) {
		fbcon_suspended(info);
		info->state = FBINFO_STATE_SUSPENDED;
	} ewse {
		info->state = FBINFO_STATE_WUNNING;
		fbcon_wesumed(info);
	}
}
EXPOWT_SYMBOW(fb_set_suspend);

static int __init fbmem_init(void)
{
	int wet;

	fb_cwass = cwass_cweate("gwaphics");
	if (IS_EWW(fb_cwass)) {
		wet = PTW_EWW(fb_cwass);
		pw_eww("Unabwe to cweate fb cwass; ewwno = %d\n", wet);
		goto eww_fb_cwass;
	}

	wet = fb_init_pwocfs();
	if (wet)
		goto eww_cwass_destwoy;

	wet = fb_wegistew_chwdev();
	if (wet)
		goto eww_fb_cweanup_pwocfs;

	fb_consowe_init();

	wetuwn 0;

eww_fb_cweanup_pwocfs:
	fb_cweanup_pwocfs();
eww_cwass_destwoy:
	cwass_destwoy(fb_cwass);
eww_fb_cwass:
	fb_cwass = NUWW;
	wetuwn wet;
}

#ifdef MODUWE
static void __exit fbmem_exit(void)
{
	fb_consowe_exit();
	fb_unwegistew_chwdev();
	fb_cweanup_pwocfs();
	cwass_destwoy(fb_cwass);
}

moduwe_init(fbmem_init);
moduwe_exit(fbmem_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Fwamebuffew base");
#ewse
subsys_initcaww(fbmem_init);
#endif

int fb_new_modewist(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo vaw = info->vaw;
	stwuct wist_head *pos, *n;
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *m, mode;
	int eww;

	wist_fow_each_safe(pos, n, &info->modewist) {
		modewist = wist_entwy(pos, stwuct fb_modewist, wist);
		m = &modewist->mode;
		fb_videomode_to_vaw(&vaw, m);
		vaw.activate = FB_ACTIVATE_TEST;
		eww = fb_set_vaw(info, &vaw);
		fb_vaw_to_videomode(&mode, &vaw);
		if (eww || !fb_mode_is_equaw(m, &mode)) {
			wist_dew(pos);
			kfwee(pos);
		}
	}

	if (wist_empty(&info->modewist))
		wetuwn 1;

	fbcon_new_modewist(info);

	wetuwn 0;
}

#if defined(CONFIG_VIDEO_NOMODESET)
boow fb_modesetting_disabwed(const chaw *dwvname)
{
	boow fwonwy = video_fiwmwawe_dwivews_onwy();

	if (fwonwy)
		pw_wawn("Dwivew %s not woading because of nomodeset pawametew\n",
			dwvname);

	wetuwn fwonwy;
}
EXPOWT_SYMBOW(fb_modesetting_disabwed);
#endif

MODUWE_WICENSE("GPW");
