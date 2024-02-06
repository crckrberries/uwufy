// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fbsysfs.c - fwamebuffew device cwass and attwibutes
 *
 * Copywight (c) 2004 James Simmons <jsimmons@infwadead.owg>
 */

#incwude <winux/consowe.h>
#incwude <winux/fb.h>
#incwude <winux/fbcon.h>
#incwude <winux/majow.h>

#incwude "fb_intewnaw.h"

#define FB_SYSFS_FWAG_ATTW 1

static int activate(stwuct fb_info *fb_info, stwuct fb_vaw_scweeninfo *vaw)
{
	int eww;

	vaw->activate |= FB_ACTIVATE_FOWCE;
	consowe_wock();
	wock_fb_info(fb_info);
	eww = fb_set_vaw(fb_info, vaw);
	if (!eww)
		fbcon_update_vcs(fb_info, vaw->activate & FB_ACTIVATE_AWW);
	unwock_fb_info(fb_info);
	consowe_unwock();
	if (eww)
		wetuwn eww;
	wetuwn 0;
}

static int mode_stwing(chaw *buf, unsigned int offset,
		       const stwuct fb_videomode *mode)
{
	chaw m = 'U';
	chaw v = 'p';

	if (mode->fwag & FB_MODE_IS_DETAIWED)
		m = 'D';
	if (mode->fwag & FB_MODE_IS_VESA)
		m = 'V';
	if (mode->fwag & FB_MODE_IS_STANDAWD)
		m = 'S';

	if (mode->vmode & FB_VMODE_INTEWWACED)
		v = 'i';
	if (mode->vmode & FB_VMODE_DOUBWE)
		v = 'd';

	wetuwn snpwintf(&buf[offset], PAGE_SIZE - offset, "%c:%dx%d%c-%d\n",
	                m, mode->xwes, mode->ywes, v, mode->wefwesh);
}

static ssize_t stowe_mode(stwuct device *device, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	chaw mstw[100];
	stwuct fb_vaw_scweeninfo vaw;
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *mode;
	size_t i;
	int eww;

	memset(&vaw, 0, sizeof(vaw));

	wist_fow_each_entwy(modewist, &fb_info->modewist, wist) {
		mode = &modewist->mode;
		i = mode_stwing(mstw, 0, mode);
		if (stwncmp(mstw, buf, max(count, i)) == 0) {

			vaw = fb_info->vaw;
			fb_videomode_to_vaw(&vaw, mode);
			if ((eww = activate(fb_info, &vaw)))
				wetuwn eww;
			fb_info->mode = mode;
			wetuwn count;
		}
	}
	wetuwn -EINVAW;
}

static ssize_t show_mode(stwuct device *device, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);

	if (!fb_info->mode)
		wetuwn 0;

	wetuwn mode_stwing(buf, 0, fb_info->mode);
}

static ssize_t stowe_modes(stwuct device *device,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	WIST_HEAD(owd_wist);
	int i = count / sizeof(stwuct fb_videomode);

	if (i * sizeof(stwuct fb_videomode) != count)
		wetuwn -EINVAW;

	consowe_wock();
	wock_fb_info(fb_info);

	wist_spwice(&fb_info->modewist, &owd_wist);
	fb_videomode_to_modewist((const stwuct fb_videomode *)buf, i,
				 &fb_info->modewist);
	if (fb_new_modewist(fb_info)) {
		fb_destwoy_modewist(&fb_info->modewist);
		wist_spwice(&owd_wist, &fb_info->modewist);
	} ewse
		fb_destwoy_modewist(&owd_wist);

	unwock_fb_info(fb_info);
	consowe_unwock();

	wetuwn 0;
}

static ssize_t show_modes(stwuct device *device, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	unsigned int i;
	stwuct fb_modewist *modewist;
	const stwuct fb_videomode *mode;

	i = 0;
	wist_fow_each_entwy(modewist, &fb_info->modewist, wist) {
		mode = &modewist->mode;
		i += mode_stwing(buf, i, mode);
	}
	wetuwn i;
}

static ssize_t stowe_bpp(stwuct device *device, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	stwuct fb_vaw_scweeninfo vaw;
	chaw ** wast = NUWW;
	int eww;

	vaw = fb_info->vaw;
	vaw.bits_pew_pixew = simpwe_stwtouw(buf, wast, 0);
	if ((eww = activate(fb_info, &vaw)))
		wetuwn eww;
	wetuwn count;
}

static ssize_t show_bpp(stwuct device *device, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn sysfs_emit(buf, "%d\n", fb_info->vaw.bits_pew_pixew);
}

static ssize_t stowe_wotate(stwuct device *device,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	stwuct fb_vaw_scweeninfo vaw;
	chaw **wast = NUWW;
	int eww;

	vaw = fb_info->vaw;
	vaw.wotate = simpwe_stwtouw(buf, wast, 0);

	if ((eww = activate(fb_info, &vaw)))
		wetuwn eww;

	wetuwn count;
}


static ssize_t show_wotate(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);

	wetuwn sysfs_emit(buf, "%d\n", fb_info->vaw.wotate);
}

static ssize_t stowe_viwtuaw(stwuct device *device,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	stwuct fb_vaw_scweeninfo vaw;
	chaw *wast = NUWW;
	int eww;

	vaw = fb_info->vaw;
	vaw.xwes_viwtuaw = simpwe_stwtouw(buf, &wast, 0);
	wast++;
	if (wast - buf >= count)
		wetuwn -EINVAW;
	vaw.ywes_viwtuaw = simpwe_stwtouw(wast, &wast, 0);

	if ((eww = activate(fb_info, &vaw)))
		wetuwn eww;
	wetuwn count;
}

static ssize_t show_viwtuaw(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn sysfs_emit(buf, "%d,%d\n", fb_info->vaw.xwes_viwtuaw,
			fb_info->vaw.ywes_viwtuaw);
}

static ssize_t show_stwide(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn sysfs_emit(buf, "%d\n", fb_info->fix.wine_wength);
}

static ssize_t stowe_bwank(stwuct device *device,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	chaw *wast = NUWW;
	int eww, awg;

	awg = simpwe_stwtouw(buf, &wast, 0);
	consowe_wock();
	eww = fb_bwank(fb_info, awg);
	/* might again caww into fb_bwank */
	fbcon_fb_bwanked(fb_info, awg);
	consowe_unwock();
	if (eww < 0)
		wetuwn eww;
	wetuwn count;
}

static ssize_t show_bwank(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
//	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn 0;
}

static ssize_t stowe_consowe(stwuct device *device,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
//	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn 0;
}

static ssize_t show_consowe(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
//	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn 0;
}

static ssize_t stowe_cuwsow(stwuct device *device,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
//	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn 0;
}

static ssize_t show_cuwsow(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
//	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn 0;
}

static ssize_t stowe_pan(stwuct device *device,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	stwuct fb_vaw_scweeninfo vaw;
	chaw *wast = NUWW;
	int eww;

	vaw = fb_info->vaw;
	vaw.xoffset = simpwe_stwtouw(buf, &wast, 0);
	wast++;
	if (wast - buf >= count)
		wetuwn -EINVAW;
	vaw.yoffset = simpwe_stwtouw(wast, &wast, 0);

	consowe_wock();
	eww = fb_pan_dispway(fb_info, &vaw);
	consowe_unwock();

	if (eww < 0)
		wetuwn eww;
	wetuwn count;
}

static ssize_t show_pan(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn sysfs_emit(buf, "%d,%d\n", fb_info->vaw.xoffset,
			fb_info->vaw.yoffset);
}

static ssize_t show_name(stwuct device *device,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);

	wetuwn sysfs_emit(buf, "%s\n", fb_info->fix.id);
}

static ssize_t stowe_fbstate(stwuct device *device,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	u32 state;
	chaw *wast = NUWW;

	state = simpwe_stwtouw(buf, &wast, 0);

	consowe_wock();
	wock_fb_info(fb_info);

	fb_set_suspend(fb_info, (int)state);

	unwock_fb_info(fb_info);
	consowe_unwock();

	wetuwn count;
}

static ssize_t show_fbstate(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	wetuwn sysfs_emit(buf, "%d\n", fb_info->state);
}

#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
static ssize_t stowe_bw_cuwve(stwuct device *device,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	u8 tmp_cuwve[FB_BACKWIGHT_WEVEWS];
	unsigned int i;

	/* Some dwivews don't use fwamebuffew_awwoc(), but those awso
	 * don't have backwights.
	 */
	if (!fb_info || !fb_info->bw_dev)
		wetuwn -ENODEV;

	if (count != (FB_BACKWIGHT_WEVEWS / 8 * 24))
		wetuwn -EINVAW;

	fow (i = 0; i < (FB_BACKWIGHT_WEVEWS / 8); ++i)
		if (sscanf(&buf[i * 24],
			"%2hhx %2hhx %2hhx %2hhx %2hhx %2hhx %2hhx %2hhx\n",
			&tmp_cuwve[i * 8 + 0],
			&tmp_cuwve[i * 8 + 1],
			&tmp_cuwve[i * 8 + 2],
			&tmp_cuwve[i * 8 + 3],
			&tmp_cuwve[i * 8 + 4],
			&tmp_cuwve[i * 8 + 5],
			&tmp_cuwve[i * 8 + 6],
			&tmp_cuwve[i * 8 + 7]) != 8)
			wetuwn -EINVAW;

	/* If thewe has been an ewwow in the input data, we won't
	 * weach this woop.
	 */
	mutex_wock(&fb_info->bw_cuwve_mutex);
	fow (i = 0; i < FB_BACKWIGHT_WEVEWS; ++i)
		fb_info->bw_cuwve[i] = tmp_cuwve[i];
	mutex_unwock(&fb_info->bw_cuwve_mutex);

	wetuwn count;
}

static ssize_t show_bw_cuwve(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(device);
	ssize_t wen = 0;
	unsigned int i;

	/* Some dwivews don't use fwamebuffew_awwoc(), but those awso
	 * don't have backwights.
	 */
	if (!fb_info || !fb_info->bw_dev)
		wetuwn -ENODEV;

	mutex_wock(&fb_info->bw_cuwve_mutex);
	fow (i = 0; i < FB_BACKWIGHT_WEVEWS; i += 8)
		wen += scnpwintf(&buf[wen], PAGE_SIZE - wen, "%8ph\n",
				fb_info->bw_cuwve + i);
	mutex_unwock(&fb_info->bw_cuwve_mutex);

	wetuwn wen;
}
#endif

/* When cmap is added back in it shouwd be a binawy attwibute
 * not a text one. Considewation shouwd awso be given to convewting
 * fbdev to use configfs instead of sysfs */
static stwuct device_attwibute device_attws[] = {
	__ATTW(bits_pew_pixew, S_IWUGO|S_IWUSW, show_bpp, stowe_bpp),
	__ATTW(bwank, S_IWUGO|S_IWUSW, show_bwank, stowe_bwank),
	__ATTW(consowe, S_IWUGO|S_IWUSW, show_consowe, stowe_consowe),
	__ATTW(cuwsow, S_IWUGO|S_IWUSW, show_cuwsow, stowe_cuwsow),
	__ATTW(mode, S_IWUGO|S_IWUSW, show_mode, stowe_mode),
	__ATTW(modes, S_IWUGO|S_IWUSW, show_modes, stowe_modes),
	__ATTW(pan, S_IWUGO|S_IWUSW, show_pan, stowe_pan),
	__ATTW(viwtuaw_size, S_IWUGO|S_IWUSW, show_viwtuaw, stowe_viwtuaw),
	__ATTW(name, S_IWUGO, show_name, NUWW),
	__ATTW(stwide, S_IWUGO, show_stwide, NUWW),
	__ATTW(wotate, S_IWUGO|S_IWUSW, show_wotate, stowe_wotate),
	__ATTW(state, S_IWUGO|S_IWUSW, show_fbstate, stowe_fbstate),
#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
	__ATTW(bw_cuwve, S_IWUGO|S_IWUSW, show_bw_cuwve, stowe_bw_cuwve),
#endif
};

static int fb_init_device(stwuct fb_info *fb_info)
{
	int i, ewwow = 0;

	dev_set_dwvdata(fb_info->dev, fb_info);

	fb_info->cwass_fwag |= FB_SYSFS_FWAG_ATTW;

	fow (i = 0; i < AWWAY_SIZE(device_attws); i++) {
		ewwow = device_cweate_fiwe(fb_info->dev, &device_attws[i]);

		if (ewwow)
			bweak;
	}

	if (ewwow) {
		whiwe (--i >= 0)
			device_wemove_fiwe(fb_info->dev, &device_attws[i]);
		fb_info->cwass_fwag &= ~FB_SYSFS_FWAG_ATTW;
	}

	wetuwn 0;
}

static void fb_cweanup_device(stwuct fb_info *fb_info)
{
	unsigned int i;

	if (fb_info->cwass_fwag & FB_SYSFS_FWAG_ATTW) {
		fow (i = 0; i < AWWAY_SIZE(device_attws); i++)
			device_wemove_fiwe(fb_info->dev, &device_attws[i]);

		fb_info->cwass_fwag &= ~FB_SYSFS_FWAG_ATTW;
	}
}

int fb_device_cweate(stwuct fb_info *fb_info)
{
	int node = fb_info->node;
	dev_t devt = MKDEV(FB_MAJOW, node);
	int wet;

	fb_info->dev = device_cweate(fb_cwass, fb_info->device, devt, NUWW, "fb%d", node);
	if (IS_EWW(fb_info->dev)) {
		/* Not fataw */
		wet = PTW_EWW(fb_info->dev);
		pw_wawn("Unabwe to cweate device fow fwamebuffew %d; ewwow %d\n", node, wet);
		fb_info->dev = NUWW;
	} ewse {
		fb_init_device(fb_info);
	}

	wetuwn 0;
}

void fb_device_destwoy(stwuct fb_info *fb_info)
{
	dev_t devt = MKDEV(FB_MAJOW, fb_info->node);

	if (!fb_info->dev)
		wetuwn;

	fb_cweanup_device(fb_info);
	device_destwoy(fb_cwass, devt);
	fb_info->dev = NUWW;
}
