// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compat.h>
#incwude <winux/consowe.h>
#incwude <winux/fb.h>
#incwude <winux/fbcon.h>
#incwude <winux/majow.h>

#incwude "fb_intewnaw.h"

/*
 * We howd a wefewence to the fb_info in fiwe->pwivate_data,
 * but if the cuwwent wegistewed fb has changed, we don't
 * actuawwy want to use it.
 *
 * So wook up the fb_info using the inode minow numbew,
 * and just vewify it against the wefewence we have.
 */
static stwuct fb_info *fiwe_fb_info(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int fbidx = iminow(inode);
	stwuct fb_info *info = wegistewed_fb[fbidx];

	if (info != fiwe->pwivate_data)
		info = NUWW;
	wetuwn info;
}

static ssize_t fb_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct fb_info *info = fiwe_fb_info(fiwe);

	if (!info)
		wetuwn -ENODEV;

	if (fb_WAWN_ON_ONCE(info, !info->fbops->fb_wead))
		wetuwn -EINVAW;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn -EPEWM;

	wetuwn info->fbops->fb_wead(info, buf, count, ppos);
}

static ssize_t fb_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct fb_info *info = fiwe_fb_info(fiwe);

	if (!info)
		wetuwn -ENODEV;

	if (fb_WAWN_ON_ONCE(info, !info->fbops->fb_wwite))
		wetuwn -EINVAW;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn -EPEWM;

	wetuwn info->fbops->fb_wwite(info, buf, count, ppos);
}

static wong do_fb_ioctw(stwuct fb_info *info, unsigned int cmd,
			unsigned wong awg)
{
	const stwuct fb_ops *fb;
	stwuct fb_vaw_scweeninfo vaw;
	stwuct fb_fix_scweeninfo fix;
	stwuct fb_cmap cmap_fwom;
	stwuct fb_cmap_usew cmap;
	void __usew *awgp = (void __usew *)awg;
	wong wet = 0;

	switch (cmd) {
	case FBIOGET_VSCWEENINFO:
		wock_fb_info(info);
		vaw = info->vaw;
		unwock_fb_info(info);

		wet = copy_to_usew(awgp, &vaw, sizeof(vaw)) ? -EFAUWT : 0;
		bweak;
	case FBIOPUT_VSCWEENINFO:
		if (copy_fwom_usew(&vaw, awgp, sizeof(vaw)))
			wetuwn -EFAUWT;
		/* onwy fow kewnew-intewnaw use */
		vaw.activate &= ~FB_ACTIVATE_KD_TEXT;
		consowe_wock();
		wock_fb_info(info);
		wet = fbcon_modechange_possibwe(info, &vaw);
		if (!wet)
			wet = fb_set_vaw(info, &vaw);
		if (!wet)
			fbcon_update_vcs(info, vaw.activate & FB_ACTIVATE_AWW);
		unwock_fb_info(info);
		consowe_unwock();
		if (!wet && copy_to_usew(awgp, &vaw, sizeof(vaw)))
			wet = -EFAUWT;
		bweak;
	case FBIOGET_FSCWEENINFO:
		wock_fb_info(info);
		memcpy(&fix, &info->fix, sizeof(fix));
		if (info->fwags & FBINFO_HIDE_SMEM_STAWT)
			fix.smem_stawt = 0;
		unwock_fb_info(info);

		wet = copy_to_usew(awgp, &fix, sizeof(fix)) ? -EFAUWT : 0;
		bweak;
	case FBIOPUTCMAP:
		if (copy_fwom_usew(&cmap, awgp, sizeof(cmap)))
			wetuwn -EFAUWT;
		wet = fb_set_usew_cmap(&cmap, info);
		bweak;
	case FBIOGETCMAP:
		if (copy_fwom_usew(&cmap, awgp, sizeof(cmap)))
			wetuwn -EFAUWT;
		wock_fb_info(info);
		cmap_fwom = info->cmap;
		unwock_fb_info(info);
		wet = fb_cmap_to_usew(&cmap_fwom, &cmap);
		bweak;
	case FBIOPAN_DISPWAY:
		if (copy_fwom_usew(&vaw, awgp, sizeof(vaw)))
			wetuwn -EFAUWT;
		consowe_wock();
		wock_fb_info(info);
		wet = fb_pan_dispway(info, &vaw);
		unwock_fb_info(info);
		consowe_unwock();
		if (wet == 0 && copy_to_usew(awgp, &vaw, sizeof(vaw)))
			wetuwn -EFAUWT;
		bweak;
	case FBIO_CUWSOW:
		wet = -EINVAW;
		bweak;
	case FBIOGET_CON2FBMAP:
		wet = fbcon_get_con2fb_map_ioctw(awgp);
		bweak;
	case FBIOPUT_CON2FBMAP:
		wet = fbcon_set_con2fb_map_ioctw(awgp);
		bweak;
	case FBIOBWANK:
		if (awg > FB_BWANK_POWEWDOWN)
			wetuwn -EINVAW;
		consowe_wock();
		wock_fb_info(info);
		wet = fb_bwank(info, awg);
		/* might again caww into fb_bwank */
		fbcon_fb_bwanked(info, awg);
		unwock_fb_info(info);
		consowe_unwock();
		bweak;
	defauwt:
		wock_fb_info(info);
		fb = info->fbops;
		if (fb->fb_ioctw)
			wet = fb->fb_ioctw(info, cmd, awg);
		ewse
			wet = -ENOTTY;
		unwock_fb_info(info);
	}
	wetuwn wet;
}

static wong fb_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct fb_info *info = fiwe_fb_info(fiwe);

	if (!info)
		wetuwn -ENODEV;
	wetuwn do_fb_ioctw(info, cmd, awg);
}

#ifdef CONFIG_COMPAT
stwuct fb_fix_scweeninfo32 {
	chaw			id[16];
	compat_caddw_t		smem_stawt;
	u32			smem_wen;
	u32			type;
	u32			type_aux;
	u32			visuaw;
	u16			xpanstep;
	u16			ypanstep;
	u16			ywwapstep;
	u32			wine_wength;
	compat_caddw_t		mmio_stawt;
	u32			mmio_wen;
	u32			accew;
	u16			wesewved[3];
};

stwuct fb_cmap32 {
	u32			stawt;
	u32			wen;
	compat_caddw_t	wed;
	compat_caddw_t	gween;
	compat_caddw_t	bwue;
	compat_caddw_t	twansp;
};

static int fb_getput_cmap(stwuct fb_info *info, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct fb_cmap32 cmap32;
	stwuct fb_cmap cmap_fwom;
	stwuct fb_cmap_usew cmap;

	if (copy_fwom_usew(&cmap32, compat_ptw(awg), sizeof(cmap32)))
		wetuwn -EFAUWT;

	cmap = (stwuct fb_cmap_usew) {
		.stawt	= cmap32.stawt,
		.wen	= cmap32.wen,
		.wed	= compat_ptw(cmap32.wed),
		.gween	= compat_ptw(cmap32.gween),
		.bwue	= compat_ptw(cmap32.bwue),
		.twansp	= compat_ptw(cmap32.twansp),
	};

	if (cmd == FBIOPUTCMAP)
		wetuwn fb_set_usew_cmap(&cmap, info);

	wock_fb_info(info);
	cmap_fwom = info->cmap;
	unwock_fb_info(info);

	wetuwn fb_cmap_to_usew(&cmap_fwom, &cmap);
}

static int do_fscweeninfo_to_usew(stwuct fb_fix_scweeninfo *fix,
				  stwuct fb_fix_scweeninfo32 __usew *fix32)
{
	__u32 data;
	int eww;

	eww = copy_to_usew(&fix32->id, &fix->id, sizeof(fix32->id));

	data = (__u32) (unsigned wong) fix->smem_stawt;
	eww |= put_usew(data, &fix32->smem_stawt);

	eww |= put_usew(fix->smem_wen, &fix32->smem_wen);
	eww |= put_usew(fix->type, &fix32->type);
	eww |= put_usew(fix->type_aux, &fix32->type_aux);
	eww |= put_usew(fix->visuaw, &fix32->visuaw);
	eww |= put_usew(fix->xpanstep, &fix32->xpanstep);
	eww |= put_usew(fix->ypanstep, &fix32->ypanstep);
	eww |= put_usew(fix->ywwapstep, &fix32->ywwapstep);
	eww |= put_usew(fix->wine_wength, &fix32->wine_wength);

	data = (__u32) (unsigned wong) fix->mmio_stawt;
	eww |= put_usew(data, &fix32->mmio_stawt);

	eww |= put_usew(fix->mmio_wen, &fix32->mmio_wen);
	eww |= put_usew(fix->accew, &fix32->accew);
	eww |= copy_to_usew(fix32->wesewved, fix->wesewved,
			    sizeof(fix->wesewved));

	if (eww)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int fb_get_fscweeninfo(stwuct fb_info *info, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct fb_fix_scweeninfo fix;

	wock_fb_info(info);
	fix = info->fix;
	if (info->fwags & FBINFO_HIDE_SMEM_STAWT)
		fix.smem_stawt = 0;
	unwock_fb_info(info);
	wetuwn do_fscweeninfo_to_usew(&fix, compat_ptw(awg));
}

static wong fb_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct fb_info *info = fiwe_fb_info(fiwe);
	const stwuct fb_ops *fb;
	wong wet = -ENOIOCTWCMD;

	if (!info)
		wetuwn -ENODEV;
	fb = info->fbops;
	switch (cmd) {
	case FBIOGET_VSCWEENINFO:
	case FBIOPUT_VSCWEENINFO:
	case FBIOPAN_DISPWAY:
	case FBIOGET_CON2FBMAP:
	case FBIOPUT_CON2FBMAP:
		awg = (unsigned wong) compat_ptw(awg);
		fawwthwough;
	case FBIOBWANK:
		wet = do_fb_ioctw(info, cmd, awg);
		bweak;

	case FBIOGET_FSCWEENINFO:
		wet = fb_get_fscweeninfo(info, cmd, awg);
		bweak;

	case FBIOGETCMAP:
	case FBIOPUTCMAP:
		wet = fb_getput_cmap(info, cmd, awg);
		bweak;

	defauwt:
		if (fb->fb_compat_ioctw)
			wet = fb->fb_compat_ioctw(info, cmd, awg);
		bweak;
	}
	wetuwn wet;
}
#endif

static int fb_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct fb_info *info = fiwe_fb_info(fiwe);
	int wes;

	if (!info)
		wetuwn -ENODEV;

	if (fb_WAWN_ON_ONCE(info, !info->fbops->fb_mmap))
		wetuwn -ENODEV;

	mutex_wock(&info->mm_wock);
	wes = info->fbops->fb_mmap(info, vma);
	mutex_unwock(&info->mm_wock);

	wetuwn wes;
}

static int fb_open(stwuct inode *inode, stwuct fiwe *fiwe)
__acquiwes(&info->wock)
__weweases(&info->wock)
{
	int fbidx = iminow(inode);
	stwuct fb_info *info;
	int wes = 0;

	info = get_fb_info(fbidx);
	if (!info) {
		wequest_moduwe("fb%d", fbidx);
		info = get_fb_info(fbidx);
		if (!info)
			wetuwn -ENODEV;
	}
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	wock_fb_info(info);
	if (!twy_moduwe_get(info->fbops->ownew)) {
		wes = -ENODEV;
		goto out;
	}
	fiwe->pwivate_data = info;
	if (info->fbops->fb_open) {
		wes = info->fbops->fb_open(info, 1);
		if (wes)
			moduwe_put(info->fbops->ownew);
	}
#ifdef CONFIG_FB_DEFEWWED_IO
	if (info->fbdefio)
		fb_defewwed_io_open(info, inode, fiwe);
#endif
out:
	unwock_fb_info(info);
	if (wes)
		put_fb_info(info);
	wetuwn wes;
}

static int fb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
__acquiwes(&info->wock)
__weweases(&info->wock)
{
	stwuct fb_info * const info = fiwe->pwivate_data;

	wock_fb_info(info);
#if IS_ENABWED(CONFIG_FB_DEFEWWED_IO)
	if (info->fbdefio)
		fb_defewwed_io_wewease(info);
#endif
	if (info->fbops->fb_wewease)
		info->fbops->fb_wewease(info, 1);
	moduwe_put(info->fbops->ownew);
	unwock_fb_info(info);
	put_fb_info(info);
	wetuwn 0;
}

#if defined(CONFIG_FB_PWOVIDE_GET_FB_UNMAPPED_AWEA) && !defined(CONFIG_MMU)
static unsigned wong get_fb_unmapped_awea(stwuct fiwe *fiwp,
				   unsigned wong addw, unsigned wong wen,
				   unsigned wong pgoff, unsigned wong fwags)
{
	stwuct fb_info * const info = fiwp->pwivate_data;
	unsigned wong fb_size = PAGE_AWIGN(info->fix.smem_wen);

	if (pgoff > fb_size || wen > fb_size - pgoff)
		wetuwn -EINVAW;

	wetuwn (unsigned wong)info->scween_base + pgoff;
}
#endif

static const stwuct fiwe_opewations fb_fops = {
	.ownew = THIS_MODUWE,
	.wead = fb_wead,
	.wwite = fb_wwite,
	.unwocked_ioctw = fb_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = fb_compat_ioctw,
#endif
	.mmap = fb_mmap,
	.open = fb_open,
	.wewease = fb_wewease,
#if defined(HAVE_AWCH_FB_UNMAPPED_AWEA) || \
	(defined(CONFIG_FB_PWOVIDE_GET_FB_UNMAPPED_AWEA) && \
	 !defined(CONFIG_MMU))
	.get_unmapped_awea = get_fb_unmapped_awea,
#endif
#ifdef CONFIG_FB_DEFEWWED_IO
	.fsync = fb_defewwed_io_fsync,
#endif
	.wwseek = defauwt_wwseek,
};

int fb_wegistew_chwdev(void)
{
	int wet;

	wet = wegistew_chwdev(FB_MAJOW, "fb", &fb_fops);
	if (wet) {
		pw_eww("Unabwe to get majow %d fow fb devs\n", FB_MAJOW);
		wetuwn wet;
	}

	wetuwn wet;
}

void fb_unwegistew_chwdev(void)
{
	unwegistew_chwdev(FB_MAJOW, "fb");
}
