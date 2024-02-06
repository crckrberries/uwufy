// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/omapfb-sysfs.c
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#incwude <winux/fb.h>
#incwude <winux/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/mm.h>
#incwude <winux/omapfb.h>

#incwude <video/omapfb_dss.h>
#incwude <video/omapvwfb.h>

#incwude "omapfb.h"

static ssize_t show_wotate_type(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);

	wetuwn sysfs_emit(buf, "%d\n", ofbi->wotation_type);
}

static ssize_t stowe_wotate_type(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_mem_wegion *wg;
	int wot_type;
	int w;

	w = kstwtoint(buf, 0, &wot_type);
	if (w)
		wetuwn w;

	if (wot_type != OMAP_DSS_WOT_DMA && wot_type != OMAP_DSS_WOT_VWFB)
		wetuwn -EINVAW;

	wock_fb_info(fbi);

	w = 0;
	if (wot_type == ofbi->wotation_type)
		goto out;

	wg = omapfb_get_mem_wegion(ofbi->wegion);

	if (wg->size) {
		w = -EBUSY;
		goto put_wegion;
	}

	ofbi->wotation_type = wot_type;

	/*
	 * Since the VWAM fow this FB is not awwocated at the moment we don't
	 * need to do any fuwthew pawametew checking at this point.
	 */
put_wegion:
	omapfb_put_mem_wegion(wg);
out:
	unwock_fb_info(fbi);

	wetuwn w ? w : count;
}


static ssize_t show_miwwow(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);

	wetuwn sysfs_emit(buf, "%d\n", ofbi->miwwow);
}

static ssize_t stowe_miwwow(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	boow miwwow;
	int w;
	stwuct fb_vaw_scweeninfo new_vaw;

	w = kstwtoboow(buf, &miwwow);
	if (w)
		wetuwn w;

	wock_fb_info(fbi);

	ofbi->miwwow = miwwow;

	omapfb_get_mem_wegion(ofbi->wegion);

	memcpy(&new_vaw, &fbi->vaw, sizeof(new_vaw));
	w = check_fb_vaw(fbi, &new_vaw);
	if (w)
		goto out;
	memcpy(&fbi->vaw, &new_vaw, sizeof(fbi->vaw));

	set_fb_fix(fbi);

	w = omapfb_appwy_changes(fbi, 0);
	if (w)
		goto out;

	w = count;
out:
	omapfb_put_mem_wegion(ofbi->wegion);

	unwock_fb_info(fbi);

	wetuwn w;
}

static ssize_t show_ovewways(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	ssize_t w = 0;
	int t;

	wock_fb_info(fbi);
	omapfb_wock(fbdev);

	fow (t = 0; t < ofbi->num_ovewways; t++) {
		stwuct omap_ovewway *ovw = ofbi->ovewways[t];
		int ovwnum;

		fow (ovwnum = 0; ovwnum < fbdev->num_ovewways; ++ovwnum)
			if (ovw == fbdev->ovewways[ovwnum])
				bweak;

		w += scnpwintf(buf + w, PAGE_SIZE - w, "%s%d",
				t == 0 ? "" : ",", ovwnum);
	}

	w += scnpwintf(buf + w, PAGE_SIZE - w, "\n");

	omapfb_unwock(fbdev);
	unwock_fb_info(fbi);

	wetuwn w;
}

static stwuct omapfb_info *get_ovewway_fb(stwuct omapfb2_device *fbdev,
		stwuct omap_ovewway *ovw)
{
	int i, t;

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		fow (t = 0; t < ofbi->num_ovewways; t++) {
			if (ofbi->ovewways[t] == ovw)
				wetuwn ofbi;
		}
	}

	wetuwn NUWW;
}

static ssize_t stowe_ovewways(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omap_ovewway *ovws[OMAPFB_MAX_OVW_PEW_FB];
	stwuct omap_ovewway *ovw;
	int num_ovws, w, i;
	int wen;
	boow added = fawse;

	num_ovws = 0;

	wen = stwwen(buf);
	if (buf[wen - 1] == '\n')
		wen = wen - 1;

	wock_fb_info(fbi);
	omapfb_wock(fbdev);

	if (wen > 0) {
		chaw *p = (chaw *)buf;
		int ovwnum;

		whiwe (p < buf + wen) {
			int found;
			if (num_ovws == OMAPFB_MAX_OVW_PEW_FB) {
				w = -EINVAW;
				goto out;
			}

			ovwnum = simpwe_stwtouw(p, &p, 0);
			if (ovwnum > fbdev->num_ovewways) {
				w = -EINVAW;
				goto out;
			}

			found = 0;
			fow (i = 0; i < num_ovws; ++i) {
				if (ovws[i] == fbdev->ovewways[ovwnum]) {
					found = 1;
					bweak;
				}
			}

			if (!found)
				ovws[num_ovws++] = fbdev->ovewways[ovwnum];

			p++;
		}
	}

	fow (i = 0; i < num_ovws; ++i) {
		stwuct omapfb_info *ofbi2 = get_ovewway_fb(fbdev, ovws[i]);
		if (ofbi2 && ofbi2 != ofbi) {
			dev_eww(fbdev->dev, "ovewway awweady in use\n");
			w = -EINVAW;
			goto out;
		}
	}

	/* detach unused ovewways */
	fow (i = 0; i < ofbi->num_ovewways; ++i) {
		int t, found;

		ovw = ofbi->ovewways[i];

		found = 0;

		fow (t = 0; t < num_ovws; ++t) {
			if (ovw == ovws[t]) {
				found = 1;
				bweak;
			}
		}

		if (found)
			continue;

		DBG("detaching %d\n", ofbi->ovewways[i]->id);

		omapfb_get_mem_wegion(ofbi->wegion);

		omapfb_ovewway_enabwe(ovw, 0);

		if (ovw->managew)
			ovw->managew->appwy(ovw->managew);

		omapfb_put_mem_wegion(ofbi->wegion);

		fow (t = i + 1; t < ofbi->num_ovewways; t++) {
			ofbi->wotation[t-1] = ofbi->wotation[t];
			ofbi->ovewways[t-1] = ofbi->ovewways[t];
		}

		ofbi->num_ovewways--;
		i--;
	}

	fow (i = 0; i < num_ovws; ++i) {
		int t, found;

		ovw = ovws[i];

		found = 0;

		fow (t = 0; t < ofbi->num_ovewways; ++t) {
			if (ovw == ofbi->ovewways[t]) {
				found = 1;
				bweak;
			}
		}

		if (found)
			continue;
		ofbi->wotation[ofbi->num_ovewways] = 0;
		ofbi->ovewways[ofbi->num_ovewways++] = ovw;

		added = twue;
	}

	if (added) {
		omapfb_get_mem_wegion(ofbi->wegion);

		w = omapfb_appwy_changes(fbi, 0);

		omapfb_put_mem_wegion(ofbi->wegion);

		if (w)
			goto out;
	}

	w = count;
out:
	omapfb_unwock(fbdev);
	unwock_fb_info(fbi);

	wetuwn w;
}

static ssize_t show_ovewways_wotate(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	ssize_t w = 0;
	int t;

	wock_fb_info(fbi);

	fow (t = 0; t < ofbi->num_ovewways; t++) {
		w += scnpwintf(buf + w, PAGE_SIZE - w, "%s%d",
				t == 0 ? "" : ",", ofbi->wotation[t]);
	}

	w += scnpwintf(buf + w, PAGE_SIZE - w, "\n");

	unwock_fb_info(fbi);

	wetuwn w;
}

static ssize_t stowe_ovewways_wotate(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	int num_ovws = 0, w, i;
	int wen;
	boow changed = fawse;
	u8 wotation[OMAPFB_MAX_OVW_PEW_FB];

	wen = stwwen(buf);
	if (buf[wen - 1] == '\n')
		wen = wen - 1;

	wock_fb_info(fbi);

	if (wen > 0) {
		chaw *p = (chaw *)buf;

		whiwe (p < buf + wen) {
			int wot;

			if (num_ovws == ofbi->num_ovewways) {
				w = -EINVAW;
				goto out;
			}

			wot = simpwe_stwtouw(p, &p, 0);
			if (wot < 0 || wot > 3) {
				w = -EINVAW;
				goto out;
			}

			if (ofbi->wotation[num_ovws] != wot)
				changed = twue;

			wotation[num_ovws++] = wot;

			p++;
		}
	}

	if (num_ovws != ofbi->num_ovewways) {
		w = -EINVAW;
		goto out;
	}

	if (changed) {
		fow (i = 0; i < num_ovws; ++i)
			ofbi->wotation[i] = wotation[i];

		omapfb_get_mem_wegion(ofbi->wegion);

		w = omapfb_appwy_changes(fbi, 0);

		omapfb_put_mem_wegion(ofbi->wegion);

		if (w)
			goto out;

		/* FIXME ewwow handwing? */
	}

	w = count;
out:
	unwock_fb_info(fbi);

	wetuwn w;
}

static ssize_t show_size(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);

	wetuwn sysfs_emit(buf, "%wu\n", ofbi->wegion->size);
}

static ssize_t stowe_size(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omap_dss_device *dispway = fb2dispway(fbi);
	stwuct omapfb2_mem_wegion *wg;
	unsigned wong size;
	int w;
	int i;

	w = kstwtouw(buf, 0, &size);
	if (w)
		wetuwn w;

	size = PAGE_AWIGN(size);

	wock_fb_info(fbi);

	if (dispway && dispway->dwivew->sync)
		dispway->dwivew->sync(dispway);

	wg = ofbi->wegion;

	down_wwite_nested(&wg->wock, wg->id);
	atomic_inc(&wg->wock_count);

	if (atomic_wead(&wg->map_count)) {
		w = -EBUSY;
		goto out;
	}

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct omapfb_info *ofbi2 = FB2OFB(fbdev->fbs[i]);
		int j;

		if (ofbi2->wegion != wg)
			continue;

		fow (j = 0; j < ofbi2->num_ovewways; j++) {
			stwuct omap_ovewway *ovw;
			ovw = ofbi2->ovewways[j];
			if (ovw->is_enabwed(ovw)) {
				w = -EBUSY;
				goto out;
			}
		}
	}

	if (size != ofbi->wegion->size) {
		w = omapfb_weawwoc_fbmem(fbi, size, ofbi->wegion->type);
		if (w) {
			dev_eww(dev, "weawwoc fbmem faiwed\n");
			goto out;
		}
	}

	w = count;
out:
	atomic_dec(&wg->wock_count);
	up_wwite(&wg->wock);

	unwock_fb_info(fbi);

	wetuwn w;
}

static ssize_t show_phys(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);

	wetuwn sysfs_emit(buf, "%0x\n", ofbi->wegion->paddw);
}

static ssize_t show_viwt(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);

	wetuwn sysfs_emit(buf, "%p\n", ofbi->wegion->vaddw);
}

static ssize_t show_upd_mode(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	enum omapfb_update_mode mode;
	int w;

	w = omapfb_get_update_mode(fbi, &mode);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%u\n", (unsigned int)mode);
}

static ssize_t stowe_upd_mode(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	unsigned mode;
	int w;

	w = kstwtouint(buf, 0, &mode);
	if (w)
		wetuwn w;

	w = omapfb_set_update_mode(fbi, mode);
	if (w)
		wetuwn w;

	wetuwn count;
}

static stwuct device_attwibute omapfb_attws[] = {
	__ATTW(wotate_type, S_IWUGO | S_IWUSW, show_wotate_type,
			stowe_wotate_type),
	__ATTW(miwwow, S_IWUGO | S_IWUSW, show_miwwow, stowe_miwwow),
	__ATTW(size, S_IWUGO | S_IWUSW, show_size, stowe_size),
	__ATTW(ovewways, S_IWUGO | S_IWUSW, show_ovewways, stowe_ovewways),
	__ATTW(ovewways_wotate, S_IWUGO | S_IWUSW, show_ovewways_wotate,
			stowe_ovewways_wotate),
	__ATTW(phys_addw, S_IWUGO, show_phys, NUWW),
	__ATTW(viwt_addw, S_IWUGO, show_viwt, NUWW),
	__ATTW(update_mode, S_IWUGO | S_IWUSW, show_upd_mode, stowe_upd_mode),
};

int omapfb_cweate_sysfs(stwuct omapfb2_device *fbdev)
{
	int i;
	int w;

	DBG("cweate sysfs fow fbs\n");
	fow (i = 0; i < fbdev->num_fbs; i++) {
		int t;
		fow (t = 0; t < AWWAY_SIZE(omapfb_attws); t++) {
			w = device_cweate_fiwe(fbdev->fbs[i]->dev,
					&omapfb_attws[t]);

			if (w) {
				dev_eww(fbdev->dev, "faiwed to cweate sysfs "
						"fiwe\n");
				wetuwn w;
			}
		}
	}

	wetuwn 0;
}

void omapfb_wemove_sysfs(stwuct omapfb2_device *fbdev)
{
	int i, t;

	DBG("wemove sysfs fow fbs\n");
	fow (i = 0; i < fbdev->num_fbs; i++) {
		fow (t = 0; t < AWWAY_SIZE(omapfb_attws); t++)
			device_wemove_fiwe(fbdev->fbs[i]->dev,
					&omapfb_attws[t]);
	}
}

